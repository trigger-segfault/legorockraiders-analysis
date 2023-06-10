
#include <ddraw.h>
#include <d3d.h>

#include "Standard.h"
#include "Mem.h"
#include "Files.h"
#include "Lists.h"
#include "Utils.h"
#include "Errors.h"
#include "DirectX.h"
#include "Surfaces.h"
#include "GfxFile.h"

LPDIRECTDRAWSURFACE7 GfxFile_LoadSurface(LPUCHAR fname, BOOL useShared) {

	LPDIRECTDRAWSURFACE7 surf = NULL;
	LPUCHAR imageData;
	LPUCHAR suffix = File_GetSuffix(fname);
	ULONG width, height, depth;

	Error_Fatal(NULL==suffix, "Unknown file type - no suffix");

	if (FALSE == useShared || NULL == (surf = Surface_GetShared(fname))) {
		if (0 == stricmp(suffix, "bmp")) {
			imageData = GfxFile_ParseBMP(fname, &width, &height, &depth, NULL);
		} else Error_Fatal(TRUE, Error_Format("Unsupported file type '%s'", suffix));

		if (imageData) {
			Error_Fatal(24!=depth, Error_Format("File %s should be a 24bit image, as it is used as a plane surface", fname));
			surf = GfxFile_CreatePlaneSurface(imageData, width, height);
			Mem_Free(imageData);
			if (useShared) Surface_RegisterShared(fname, surf);
		}
	}

	return surf;
}

//LPDIRECTDRAWSURFACE7 GfxFile_GetSharedTextureSurface(LPUCHAR fname) {
//
//	return File_FindSharedObject(fname, FileObjectType_TextureSurface);
//}

LPDIRECTDRAWSURFACE7 GfxFile_LoadTextureSurface(LPUCHAR fname, BOOL registerShared, ULONG depth, LPULONG colourKey) {

	LPDIRECTDRAWSURFACE7 surf = NULL;
	LPUCHAR suffix = File_GetSuffix(fname);
	LPUCHAR imageData;
	PALETTEENTRY palette[256];
	ULONG width, height, srcDepth;
	
	if (suffix && 0 == stricmp(suffix, "bmp")) {
		if (imageData = GfxFile_ParseBMP(fname, &width, &height, &srcDepth, palette)) {
			surf = GfxFile_CreateTextureSurface(imageData, width, height, srcDepth, palette, depth, colourKey);
			Mem_Free(imageData);
//			if (registerShared) File_RegisterSharedObject(fname, surf, FileObjectType_TextureSurface);
		}
	}

	return surf;
}

LPUCHAR GfxFile_ParseBMP(LPUCHAR fname, LPULONG width, LPULONG height, LPULONG depth, PALETTEENTRY palette[256]) {

	LPBITMAPINFO bitmap;
	LPUCHAR buffer, image = NULL;
	LPUWORD uwBuffer;
	ULONG loop, size, byteDepth, surfaceByteDepth;
	LPUCHAR imageData;
	ULONG coloursUsed;
	SLONG y;

	if (buffer = File_LoadBinary(fname, &size)) {
		uwBuffer = (LPUWORD) buffer;
		Error_Fatal(GFXFILE_BMPMAGIC != uwBuffer[0], Error_Format("File is not a BMP (%s)", fname));
		Error_Fatal(size != ((LPULONG) &uwBuffer[1])[0], Error_Format("BMP file has invalid length (%s)", fname));

		imageData = &buffer[((LPULONG) &uwBuffer[5])[0]];
		bitmap = (LPBITMAPINFO) &uwBuffer[7];
		byteDepth = bitmap->bmiHeader.biBitCount / 8;
		surfaceByteDepth = DirectX_GetRenderSurfaceBitDepth() / 8;
		coloursUsed = bitmap->bmiHeader.biClrUsed;
		if (0 == coloursUsed) coloursUsed = 256;

		Error_Fatal(8 != bitmap->bmiHeader.biBitCount && 24 != bitmap->bmiHeader.biBitCount, Error_Format("Unsupported colour depth of %i bits (%s)", bitmap->bmiHeader.biBitCount, fname));

		if (NULL != palette && 8 == bitmap->bmiHeader.biBitCount) {
			memset(palette, 0, sizeof(palette[0]) * 256);
			for (loop=0 ; loop<coloursUsed ; loop++) {
				palette[loop].peBlue = bitmap->bmiColors[loop].rgbBlue;
				palette[loop].peGreen = bitmap->bmiColors[loop].rgbGreen;
				palette[loop].peRed = bitmap->bmiColors[loop].rgbRed;
			}
		}
		
		*width = bitmap->bmiHeader.biWidth;
		*height = bitmap->bmiHeader.biHeight;
		*depth = bitmap->bmiHeader.biBitCount;

		image = Mem_Alloc(bitmap->bmiHeader.biWidth * bitmap->bmiHeader.biHeight * byteDepth);

		for (y=0 ; y<bitmap->bmiHeader.biHeight ; y++) {
			Mem_Copy(
				&image[(bitmap->bmiHeader.biHeight - (y+1)) * bitmap->bmiHeader.biWidth * byteDepth],
				&imageData[y * bitmap->bmiHeader.biWidth * byteDepth],
				bitmap->bmiHeader.biWidth * byteDepth);
		}

		Mem_Free(buffer);
	}

	return image;
}

static ULONG GfxFile_ConvertColourKey(ULONG colour, LPDDSURFACEDESC2 desc, PALETTEENTRY palette[256]) {

	ULONG loop;
	UCHAR a, r, g, b;

	a = (UCHAR) (colour >> 24);
	r = (UCHAR) ((colour >> 16) & 0xff);
	g = (UCHAR) ((colour >> 8) & 0xff);
	b = (UCHAR) (colour & 0xff);

	if (desc->ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED8) {

		ULONG diffList[256];
		ULONG nearest = 0;
		
		for (loop=0 ; loop<255 ; loop++) {
			if (palette[loop].peRed == r && palette[loop].peGreen == g && palette[loop].peBlue == b) {
				return loop;
			} else {
				diffList[loop] = abs(palette[loop].peRed - r) + abs(palette[loop].peGreen - g) + abs(palette[loop].peBlue - b);
			}
		}

		for (loop=1 ; loop<256 ; loop++) {
			if (diffList[loop] < diffList[nearest]) nearest = loop;
		}

		return nearest;

	} else {

		UCHAR aBits, rBits, gBits, bBits;

		switch (desc->ddpfPixelFormat.dwRGBBitCount) {
		case 32:
		case 24:	return colour;
		case 16:
			DirectX_GetBitCounts(&desc->ddpfPixelFormat, &aBits, &rBits, &gBits, &bBits);
			a >>= (8 - aBits);
			r >>= (8 - rBits);
			g >>= (8 - gBits);
			b >>= (8 - bBits);
			return (a << (rBits + gBits + bBits)) | (r << (gBits + bBits)) | (g << bBits) | (b);

		default:
			Error_Fatal(TRUE, Error_Format("No support for non-palettised %d bit textures", desc->ddpfPixelFormat.dwRGBBitCount));
			return 0;
		}
	}
}

LPDIRECTDRAWSURFACE7 GfxFile_CreateTextureSurface(LPUCHAR imageData, ULONG width, ULONG height, ULONG depth, PALETTEENTRY palette[256], ULONG textureDepth, LPULONG colourKey) {

	LPDIRECTDRAWSURFACE7 cSurf, tSurf;
	DDSURFACEDESC2 cDesc, tDesc;
	LPDIRECTDRAWPALETTE pal;
	LPUCHAR surfaceLine, imageLine;
	ULONG byteDepth = depth / 8;
	ULONG textureWidth, textureHeight;
	ULONG y;
	HRESULT r;

	// Create a surface of the same width/depth/height of the source bitmap to load the image onto...
	DirectX_InitStruct(&cDesc);
	cDesc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_PIXELFORMAT | DDSD_WIDTH;
	cDesc.dwWidth = width;
	cDesc.dwHeight = height;
	cDesc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	cDesc.ddpfPixelFormat.dwSize = sizeof(cDesc.ddpfPixelFormat);
	cDesc.ddpfPixelFormat.dwFlags = DDPF_RGB;
	cDesc.ddpfPixelFormat.dwRGBBitCount = depth;
	if (24 == depth) {
		cDesc.ddpfPixelFormat.dwRBitMask = 0x00ff0000;
		cDesc.ddpfPixelFormat.dwGBitMask = 0x0000ff00;
		cDesc.ddpfPixelFormat.dwBBitMask = 0x000000ff;
	} else if (8 == depth) {
		cDesc.ddpfPixelFormat.dwFlags |= DDPF_PALETTEINDEXED8;
	} else Error_Fatal(TRUE, "Unsupported colour depth");

	r = DirectX_DirectDraw()->lpVtbl->CreateSurface(DirectX_DirectDraw(), &cDesc, &cSurf, NULL);
	Error_DirectX(r, "CreateSurface");

	if (8 == depth) {
		r = DirectX_DirectDraw()->lpVtbl->CreatePalette(DirectX_DirectDraw(), DDPCAPS_8BIT|DDPCAPS_ALLOW256|DDPCAPS_INITIALIZE, palette, &pal, NULL);
		Error_DirectX(r, "CreatePalette");
		r = cSurf->lpVtbl->SetPalette(cSurf, pal);
		Error_DirectX(r, "SetPalette");
	}

	// Copy the image data out of the bitmap into the new surface...
	DirectX_InitStruct(&cDesc);
	if (DD_OK == (r = cSurf->lpVtbl->Lock(cSurf, NULL, &cDesc, DDLOCK_WAIT, NULL))){
			
		for (y=0 ; y<height ; y++) {
			surfaceLine = &((LPUCHAR) cDesc.lpSurface)[cDesc.lPitch * y];
			imageLine = &imageData[width * byteDepth * y];
			Mem_Copy(surfaceLine, imageLine, width * byteDepth);
		}
		
		r = cSurf->lpVtbl->Unlock(cSurf, NULL);
		Error_DirectX(r, "Unlock");

	} else Error_DirectX(r, "Lock");

	// Ensure the texture width and height are powers of two...
	textureWidth = Util_RoundToPower(width);
	textureHeight = Util_RoundToPower(height);

	// Create the texture surface...
	DirectX_InitStruct(&tDesc);
	tDesc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_PIXELFORMAT | DDSD_WIDTH;// | DDSD_MIPMAPCOUNT;
//	tDesc.dwMipMapCount = 3;
	tDesc.dwWidth = textureWidth;
	tDesc.dwHeight = textureHeight;
	tDesc.ddsCaps.dwCaps = DDSCAPS_TEXTURE;// | DDSCAPS_MIPMAP | DDSCAPS_COMPLEX;
	tDesc.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
	tDesc.ddpfPixelFormat.dwSize = sizeof(tDesc.ddpfPixelFormat);
	tDesc.ddpfPixelFormat.dwFlags = DDPF_RGB;
	tDesc.ddpfPixelFormat.dwRGBBitCount = textureDepth;
	
	if (24 == textureDepth) {
		tDesc.ddpfPixelFormat.dwRBitMask = 0x00ff0000;
		tDesc.ddpfPixelFormat.dwGBitMask = 0x0000ff00;
		tDesc.ddpfPixelFormat.dwBBitMask = 0x000000ff;
	} else if (16 == textureDepth) {
		tDesc.ddpfPixelFormat.dwRBitMask = 0x0000f800;
		tDesc.ddpfPixelFormat.dwGBitMask = 0x000007e0;
		tDesc.ddpfPixelFormat.dwBBitMask = 0x0000001f;
	} else if (8 == textureDepth) {
		tDesc.ddpfPixelFormat.dwFlags |= DDPF_PALETTEINDEXED8;
	} else Error_Fatal(TRUE, "Unsupported texture depth");

	if (colourKey) {
		tDesc.dwFlags |= DDSD_CKSRCBLT;
		tDesc.ddckCKSrcBlt.dwColorSpaceLowValue = tDesc.ddckCKSrcBlt.dwColorSpaceHighValue = GfxFile_ConvertColourKey(*colourKey, &tDesc, palette);
	}
	
	r = DirectX_DirectDraw()->lpVtbl->CreateSurface(DirectX_DirectDraw(), &tDesc, &tSurf, NULL);
	Error_DirectX(r, "CreateSurface");

	// Convert the surface format (This will generate a palette for us if neccessary)...
	Surface_Convert(cSurf, tSurf);
/*
	{
		DDSCAPS2 caps = { 0 };
		LPDIRECTDRAWSURFACE7 nextSurf = tSurf;

		caps.dwCaps = DDSCAPS_TEXTURE;

		do {

			Surface_Convert(cSurf, nextSurf);

			r = nextSurf->lpVtbl->GetAttachedSurface(nextSurf, &caps, &nextSurf);
			if (nextSurf) nextSurf->lpVtbl->Release(nextSurf);

		} while (DD_OK == r);
	}
*/
	// Clean up...
	if (8 == depth) {
		r = cSurf->lpVtbl->SetPalette(cSurf, NULL);
		Error_DirectX(r, "SetPalette");
		pal->lpVtbl->Release(pal);
	}
	r = cSurf->lpVtbl->Release(cSurf);

	return tSurf;
}

LPDIRECTDRAWSURFACE7 GfxFile_CreatePlaneSurface(LPUCHAR imageData, ULONG width, ULONG height) {

	LPDIRECTDRAWSURFACE7 surf, surface;
	LPUCHAR surfaceLine, imageLine;
	DDSURFACEDESC2 desc;
	HRESULT r;
	ULONG y;

	// Create a compatible surface to copy the data into...

	DirectX_InitStruct(&desc);
	desc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_PIXELFORMAT | DDSD_WIDTH;
	desc.dwWidth = width;
	desc.dwHeight = height;
	desc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	desc.ddpfPixelFormat.dwSize = sizeof(desc.ddpfPixelFormat);
	desc.ddpfPixelFormat.dwFlags = DDPF_RGB;
	desc.ddpfPixelFormat.dwRGBBitCount = 24;
	desc.ddpfPixelFormat.dwRBitMask = 0x00ff0000;
	desc.ddpfPixelFormat.dwGBitMask = 0x0000ff00;
	desc.ddpfPixelFormat.dwBBitMask = 0x000000ff;

	r = DirectX_DirectDraw()->lpVtbl->CreateSurface(DirectX_DirectDraw(), &desc, &surf, NULL);
	Error_DirectX(r, "CreateSurface");
	
	// Copy the image data into the new surface...
	DirectX_InitStruct(&desc);
	if (DD_OK == (r = surf->lpVtbl->Lock(surf, NULL, &desc, DDLOCK_WAIT, NULL))){
			
		for (y=0 ; y<height ; y++) {
			surfaceLine = &((LPUCHAR) desc.lpSurface)[desc.lPitch * y];
			imageLine = &imageData[width * 3 * y];
			Mem_Copy(surfaceLine, imageLine, width * 3);
		}
		
		r = surf->lpVtbl->Unlock(surf, NULL);
		Error_DirectX(r, "Unlock");
	} else  Error_DirectX(r, "Lock");

	// Create the desired surface type for the display...
	DirectX_InitStruct(&desc);
	desc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_PIXELFORMAT | DDSD_WIDTH;
	desc.dwWidth = width;
	desc.dwHeight = height;
	desc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	desc.ddpfPixelFormat.dwSize = sizeof(desc.ddpfPixelFormat);
	r = DirectX_BackSurf()->lpVtbl->GetPixelFormat(DirectX_BackSurf(), &desc.ddpfPixelFormat);
	Error_DirectX(r, "GetPixelFormat");

	r = DirectX_DirectDraw()->lpVtbl->CreateSurface(DirectX_DirectDraw(), &desc, &surface, NULL);
	Error_DirectX(r, "CreateSurface");

	// Blit the image...
	Surface_Convert(surf, surface);
	
	// Free the temporary surface...
	r = surf->lpVtbl->Release(surf);

	return surface;
}

/*
LPDIRECTDRAWSURFACE4 GfxFile_LoadSurface(LPUCHAR fname, BOOL useShared) {

	LPDIRECTDRAWSURFACE4 surf = NULL;
	LPUCHAR suffix = File_GetSuffix(fname);
	ULONG depth = 0;

	if (texture) depth = 8;

	Error_Fatal(NULL==suffix, "Unknown file type - no suffix");

	if (FALSE == useShared || NULL == (surf = File_FindSharedObject(fname, File_ObjectType_Surface))) {
		if (0 == stricmp(suffix, "bmp")) {
			surf = GfxFile_ParseBMP(fname, texture, depth);
		} else Error_Fatal(TRUE, Error_Format("Unsupported file type '%s'", suffix));
		Error_Fatal(NULL==surf, Error_Format("Could not load graphic from \"%s\"", fname));
	}

	return surf;
}

LPDIRECT3DTEXTURE2 GfxFile_LoadTexture(LPUCHAR fname, BOOL useShared) {

	LPDIRECT3DTEXTURE2 texture = NULL;
	LPDIRECTDRAWSURFACE4 surf;
	
	if (FALSE == useShared || NULL == (texture = File_FindSharedObject(fname, File_ObjectType_Texture))) {
		if (surf = GfxFile_LoadSurface(fname, FALSE, TRUE)) {
			HRESULT r = surf->lpVtbl->QueryInterface(surf, &IID_IDirect3DTexture2, &texture);
			surf->lpVtbl->Release(surf);
			Error_Fatal(D3D_OK!=r, "Error querying surface for texture");
		}
	}

	return texture;
}
*/




/*
static LPDIRECTDRAWSURFACE4 GfxFile_CreateSurface(ULONG width, ULONG height, BOOL texture, ULONG depth) {

	LPDIRECTDRAWSURFACE4 surf = NULL;
	DDSURFACEDESC2 desc;
	HRESULT r;

	memset(&desc, 0, sizeof(desc));
	desc.dwSize = sizeof(desc);
	desc.dwFlags = DDSD_CAPS|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_WIDTH;
	desc.dwWidth = width;
	desc.dwHeight = height;

	desc.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);

	if (texture) {
		desc.ddpfPixelFormat.dwFlags = DDPF_RGB;
		desc.ddpfPixelFormat.dwRGBBitCount = depth;
		if (8 == depth) desc.ddpfPixelFormat.dwFlags |= DDPF_PALETTEINDEXED8;
		else if (24 == depth) {
			desc.ddpfPixelFormat.dwRBitMask = 0x00ff0000;
			desc.ddpfPixelFormat.dwGBitMask = 0x0000ff00;
			desc.ddpfPixelFormat.dwBBitMask = 0x000000ff;
		}
		desc.ddsCaps.dwCaps = DDSCAPS_TEXTURE;
		desc.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
	} else {
		desc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
		r = Direct3D_BackSurf()->lpVtbl->GetPixelFormat(Direct3D_BackSurf(), &desc.ddpfPixelFormat);
		Error_DirectX(r, "GetPixelFormat");
	}

	r = Direct3D_DirectDraw()->lpVtbl->CreateSurface(Direct3D_DirectDraw(), &desc, &surf, NULL);
	Error_DirectX(r, "CreateSurface");

	return surf;
}
*/

/*
LPDIRECTDRAWSURFACE4 GfxFile_ParseBMP(LPUCHAR fname, BOOL texture, ULONG depth) {

	LPDIRECTDRAWSURFACE4 surf, surface = NULL;
	DDSURFACEDESC2 desc;
	LPBITMAPINFO bitmap;
	HRESULT r;
	LPUCHAR buffer;
	LPUWORD uwBuffer;
	ULONG loop, size, byteDepth, surfaceByteDepth;
	LPUCHAR imageData, imageLine, surfaceLine;
	SLONG y;

	if (buffer = File_LoadBinary(fname, &size)) {
		uwBuffer = (LPUWORD) buffer;
		Error_Fatal(GFXFILE_BMPMAGIC != uwBuffer[0], Error_Format("File is not a BMP (%s)", fname));
		Error_Fatal(size != ((LPULONG) &uwBuffer[1])[0], Error_Format("BMP file has invalid length (%s)", fname));

		imageData = &buffer[((LPULONG) &uwBuffer[5])[0]];
		bitmap = (LPBITMAPINFO) &uwBuffer[7];
		byteDepth = bitmap->bmiHeader.biBitCount / 8;
		surfaceByteDepth = Direct3D_GetRenderSurfaceBitDepth() / 8;

		Error_Fatal(8!=bitmap->bmiHeader.biBitCount&&24!=bitmap->bmiHeader.biBitCount, Error_Format("Unsupported colour depth of %i bits (%s)", bitmap->bmiHeader.biBitCount, fname));
		
		// Convert the palette data from bgr to rgb...
		if (8 == bitmap->bmiHeader.biBitCount) {
			UCHAR swap;
			if (0 == bitmap->bmiHeader.biClrUsed) bitmap->bmiHeader.biClrUsed = 256;
			for (loop=0 ; loop<bitmap->bmiHeader.biClrUsed ; loop++) {
				swap = bitmap->bmiColors[loop].rgbBlue;
				bitmap->bmiColors[loop].rgbBlue = bitmap->bmiColors[loop].rgbRed;
				bitmap->bmiColors[loop].rgbRed = swap;
			}
		}
		
		// Create a compatible surface to copy the data into...
		memset(&desc, 0, sizeof(desc));
		desc.dwSize = sizeof(desc);
		desc.dwFlags = DDSD_CAPS|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_WIDTH;
		desc.dwWidth = bitmap->bmiHeader.biWidth;
		desc.dwHeight = bitmap->bmiHeader.biHeight;
		desc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
		desc.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
		desc.ddpfPixelFormat.dwFlags = DDPF_RGB;
		desc.ddpfPixelFormat.dwRGBBitCount = bitmap->bmiHeader.biBitCount;
		if (8 == bitmap->bmiHeader.biBitCount) desc.ddpfPixelFormat.dwFlags |= DDPF_PALETTEINDEXED8;
		else if (24 == bitmap->bmiHeader.biBitCount) {
			desc.ddpfPixelFormat.dwRBitMask = 0x00ff0000;
			desc.ddpfPixelFormat.dwGBitMask = 0x0000ff00;
			desc.ddpfPixelFormat.dwBBitMask = 0x000000ff;
		}
		r = Direct3D_DirectDraw()->lpVtbl->CreateSurface(Direct3D_DirectDraw(), &desc, &surf, NULL);
		Error_DirectX(r, "CreateSurface");
		if (8 == bitmap->bmiHeader.biBitCount) {		// Create a palette...
			PALETTEENTRY palette[256];
			LPDIRECTDRAWPALETTE pal;
			memset(palette, 0, sizeof(PALETTEENTRY) * 256);
			for (loop=0 ; loop<bitmap->bmiHeader.biClrUsed ; loop++) {
				palette[loop].peRed = bitmap->bmiColors[loop].rgbRed;
				palette[loop].peGreen = bitmap->bmiColors[loop].rgbGreen;
				palette[loop].peBlue = bitmap->bmiColors[loop].rgbBlue;
			}
			r = Direct3D_DirectDraw()->lpVtbl->CreatePalette(Direct3D_DirectDraw(), DDPCAPS_8BIT, palette, &pal, NULL);
			Error_DirectX(r, "CreatePalette");
			r = surf->lpVtbl->SetPalette(surf, pal);
			Error_DirectX(r, "SetPalette");
			r = pal->lpVtbl->Release(pal);
		}
		
		// Copy the image data into the new surface (upside down)...
		
		memset(&desc, 0, sizeof(desc));
		desc.dwSize = sizeof(desc);
		if (DD_OK == (r = surf->lpVtbl->Lock(surf, NULL, &desc, DDLOCK_WAIT, NULL))) {
			
			for (y=0 ; y<bitmap->bmiHeader.biHeight ; y++) {
				surfaceLine = &((LPUCHAR) desc.lpSurface)[desc.lPitch * (bitmap->bmiHeader.biHeight - (y + 1))];
				imageLine = &imageData[bitmap->bmiHeader.biWidth * byteDepth * y];
				Mem_Copy(surfaceLine, imageLine, bitmap->bmiHeader.biWidth * byteDepth);
			}
			
			r = surf->lpVtbl->Unlock(surf, NULL);
			Error_DirectX(r, "Unlock");
			
			// Create the desired surface type and blit the image to it...
			surface = GfxFile_CreateSurface(bitmap->bmiHeader.biWidth, bitmap->bmiHeader.biHeight, texture, depth);
			r = surface->lpVtbl->Blt(surface, NULL, surf, NULL, DDBLT_WAIT, NULL);
			Error_DirectX(r, "Blt");
			
			// Free the temporary surface...
			r = surf->lpVtbl->Release(surf);
			
		} else Error_DirectX(r, "Lock");

		Mem_Free(buffer);
	}

	return surface;
}
*/
/*
LPDIRECTDRAWSURFACE4 GfxFile_ParseBMP(LPUCHAR fname, BOOL texture) {

	LPDIRECTDRAWSURFACE4 surf = NULL;
	LPBITMAPINFO bitmap;
	LPUCHAR buffer;
	LPUWORD uwBuffer;
	ULONG size, byteDepth, surfaceByteDepth;
	SLONG loop, x, y;
	LPUCHAR imageData, imageLine, surfaceLine;

	if (buffer = File_LoadBinary(fname, &size)) {
		uwBuffer = (LPUWORD) buffer;
		Error_Fatal(GFXFILE_BMPMAGIC != uwBuffer[0], Error_Format("File is not a BMP (%s)", fname));
		Error_Fatal(size != ((LPULONG) &uwBuffer[1])[0], Error_Format("BMP file has invalid length (%s)", fname));

		imageData = &buffer[((LPULONG) &uwBuffer[5])[0]];
		bitmap = (LPBITMAPINFO) &uwBuffer[7];
		byteDepth = bitmap->bmiHeader.biBitCount / 8;
		surfaceByteDepth = Direct3D_GetRenderSurfaceBitDepth() / 8;

		Error_Fatal(8!=bitmap->bmiHeader.biBitCount&&24!=bitmap->bmiHeader.biBitCount, Error_Format("Unsupported colour depth of %i bits (%s)", bitmap->bmiHeader.biBitCount, fname));

		if (surf = GfxFile_CreateSurface(bitmap->bmiHeader.biWidth, bitmap->bmiHeader.biHeight, bitmap->bmiHeader.biBitCount, texture)) {
			DDSURFACEDESC2 desc;
			HRESULT r;

			// Convert the palette data from bgr to rgb...
			if (8 == bitmap->bmiHeader.biBitCount) {
				UCHAR swap;
				if (0 == bitmap->bmiHeader.biClrUsed) bitmap->bmiHeader.biClrUsed = 256;
				for (loop=0 ; loop<(SLONG) bitmap->bmiHeader.biClrUsed ; loop++) {
					swap = bitmap->bmiColors[loop].rgbBlue;
					bitmap->bmiColors[loop].rgbBlue = bitmap->bmiColors[loop].rgbRed;
					bitmap->bmiColors[loop].rgbRed = swap;
				}
			}

			memset(&desc, 0, sizeof(desc));
			desc.dwSize = sizeof(desc);
			if (DD_OK == (r = surf->lpVtbl->Lock(surf, NULL, &desc, DDLOCK_WAIT, NULL))) {

				// Copy the data in upside down??!!?!
				if (2 == surfaceByteDepth) {
					for (y=0 ; y<bitmap->bmiHeader.biHeight ; y++) {
						surfaceLine = &((LPUCHAR) desc.lpSurface)[desc.lPitch * (bitmap->bmiHeader.biHeight - (y + 1))];
						imageLine = &imageData[bitmap->bmiHeader.biWidth * byteDepth * y];
						for (x=0 ; x<bitmap->bmiHeader.biWidth ; x++) {
							*((LPUWORD) &surfaceLine[x * surfaceByteDepth]) = (UWORD) Direct3D_ColourMatchPacked(*((LPULONG) &imageLine[x * 3]));
						}
					}
				} else if (3 == surfaceByteDepth) {
					for (y=0 ; y<bitmap->bmiHeader.biHeight ; y++) {
						surfaceLine = &((LPUCHAR) desc.lpSurface)[desc.lPitch * (bitmap->bmiHeader.biHeight - (y + 1))];
						imageLine = &imageData[bitmap->bmiHeader.biWidth * byteDepth * y];
						Mem_Copy(surfaceLine, imageLine, bitmap->bmiHeader.biWidth * byteDepth);
					}
				} else if (4 == surfaceByteDepth) {
					for (y=0 ; y<bitmap->bmiHeader.biHeight ; y++) {
						surfaceLine = &((LPUCHAR) desc.lpSurface)[desc.lPitch * (bitmap->bmiHeader.biHeight - (y + 1))];
						imageLine = &imageData[bitmap->bmiHeader.biWidth * byteDepth * y];
						for (x=0 ; x<bitmap->bmiHeader.biWidth ; x++) {
							*((LPULONG) &surfaceLine[x * surfaceByteDepth]) = Direct3D_ColourMatchPacked(*((LPULONG) &imageLine[x * 3]));
						}
					}
				} else Error_Fatal(TRUE, "Unsupported render surface bit depth");

				r = surf->lpVtbl->Unlock(surf, NULL);
				Error_DirectX(r, "Unlock");
			} else Error_DirectX(r, "Lock");
		}
		Mem_Free(buffer);
	}

	return surf;
}
*/

/*
static VOID GfxFile_ConvertImage(LPUCHAR surfaceMem, ULONG surfaceByteDepth, ULONG surfacePitch, LPUCHAR imageMem, lpGfxFilePaletteEntry palette, ULONG width, ULONG height) {

	// Unoptimised, compatible loadtime convertion...

	ULONG x, y, colour;

	for (y=0 ; y<height ; y++) {
		for (x=0 ; x<width ; x++) {
			colour = GfxFile_GetPixel(imageMem, palette, width, x, y);
			colour = Direct3D_ColourMatchPacked(colour);
			surfaceMem[(y * surfacePitch) + x + 0] = colour
		}
	}	
}

__inline static ULONG GfxFile_GetPixel(LPUCHAR imageMem, lpGfxFilePaletteEntry palette, ULONG width, ULONG x, ULONG y) {

	// Assumes that if palette is NULL then the image data is 24bit...
	// The fact that the 'if' is called for every pixel is silly, but this function is only called during load time...

	ULONG colour;

	if (palette) colour = palette[imageMem[(width * y) + x]];
	else colour = *((LPULONG) &imageMem[(width * y * 3) + (x * 3)]) & 0x00ffffff;
}
*/

/*
static LPDIRECTDRAWSURFACE4 GfxFile_CreateSurface(ULONG width, ULONG height, ULONG depth, BOOL texture) {

	LPDIRECTDRAWSURFACE4 surf = NULL;
	DDSURFACEDESC2 desc;
	HRESULT r;

	memset(&desc, 0, sizeof(desc));
	desc.dwSize = sizeof(desc);
	desc.dwFlags = DDSD_CAPS|DDSD_HEIGHT|DDSD_PIXELFORMAT|DDSD_WIDTH;
	desc.dwWidth = width;
	desc.dwHeight = height;
	desc.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
	desc.ddpfPixelFormat.dwFlags = DDPF_RGB;
	desc.ddpfPixelFormat.dwRGBBitCount = depth;
	if (8 == depth) desc.ddpfPixelFormat.dwFlags |= DDPF_PALETTEINDEXED8;
	else if (24 == depth) {
		desc.ddpfPixelFormat.dwRBitMask = 0x00ff0000;
		desc.ddpfPixelFormat.dwGBitMask = 0x0000ff00;
		desc.ddpfPixelFormat.dwBBitMask = 0x000000ff;
	}

	if (texture) {
		desc.ddsCaps.dwCaps = DDSCAPS_TEXTURE;
		desc.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
	} else desc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

	r = Direct3D_DirectDraw()->lpVtbl->CreateSurface(Direct3D_DirectDraw(), &desc, &surf, NULL);
	Error_DirectX(r, "CreateSurface");

	return surf;
}
*/
