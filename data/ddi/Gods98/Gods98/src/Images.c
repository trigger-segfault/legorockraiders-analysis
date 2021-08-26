/**********************************************************************************
 **
 ** Image.c: Image Object Code For GODS
 **
 ** Copyright (C) Data Design Interactive.
 **
 **
 ** Written by
 **
 **********************************************************************************/

#include <ddraw.h>
#include <d3drm.h>

#include "..\inc\Standard.h"

#include "..\inc\Errors.h"
#include "..\inc\Memory.h"
#include "..\inc\Maths.h"
#include "..\inc\DirectDraw.h"
#include "..\inc\Containers.h"
#include "..\inc\Viewports.h"
#include "..\inc\Main.h"
#include "..\inc\Images.h"
#include "..\inc\Files.h"
#include "..\inc\BMP.h"
#include "..\inc\dxbug.h"

static HBITMAP Bitmap_Load(const char *fName);
static BOOL Bitmap_Parse(const char *fName, BITMAPINFOHEADER *bi, void **data, RGBQUAD **palette);

extern int __cdecl DirectDraw_SaveBMP(LPDIRECTDRAWSURFACE4 surface, LPUCHAR fname);

/**********************************************************************************
 ******** Image Global Data
 **********************************************************************************/

Image_Globs imageGlobs = { 0 };

/**********************************************************************************
 ******** Image Global Library Functions
 **********************************************************************************/

VOID Image_Initialise(VOID){

	ULONG loop;
//	LPDIRECT3D3 d3d;

	if (imageGlobs.flags & IMAGE_FLAG_INITIALISED) Error_Fatal(TRUE, "Images already initialised");

	for (loop=0 ; loop<IMAGE_MAXLISTS ; loop++){
		imageGlobs.listSet[loop] = NULL;
	}

//	if (D3D_OK == lpIMDevice()->lpVtbl->GetDirect3D(lpIMDevice(), &d3d)) {
//		if (D3D_OK == d3d->lpVtbl->CreateMaterial(d3d, &imageGlobs.textureMaterial, NULL)) {
//			imageGlobs.mat.dwSize = sizeof(imageGlobs.mat);
//			imageGlobs.textureMaterial->lpVtbl->GetHandle(imageGlobs.textureMaterial, lpIMDevice(), &imageGlobs.textureMaterialHandle);
//		} else imageGlobs.textureMaterialHandle = 0;
//		d3d->lpVtbl->Release(d3d);
//	}

	// Global Initialisation here...

	imageGlobs.alphaIntensity = 1.0f;
	imageGlobs.flags = IMAGE_FLAG_INITIALISED;
}

VOID Image_Shutdown(VOID){

	ULONG loop;

	Image_RemoveAll();

	for (loop=0 ; loop<IMAGE_MAXLISTS ; loop++){
		if (imageGlobs.listSet[loop]) Mem_Free(imageGlobs.listSet[loop]);
	}

	imageGlobs.freeList = NULL;
	imageGlobs.flags = 0x00000000;
}

VOID Image_Remove(lpImage dead){

	Image_CheckInit();
	Error_Fatal(!dead, "NULL passed to Image_Remove()");

	dead->surface->lpVtbl->Release(dead->surface);

	dead->nextFree = imageGlobs.freeList;
	imageGlobs.freeList = dead;
}

/*
lpImage Image_LoadBMP(LPUCHAR filename){

	DDSURFACEDESC ddsd, desc;
	LPDIRECTDRAWSURFACE pdds;
	LPDIRECTDRAWSURFACE3 surf3;
	LPDIRECTDRAWPALETTE pal = NULL;
	D3DRMIMAGE image;
	LPVOID buffer;
	ULONG size;

	if (buffer = File_LoadBinary(filename, &size)){

		BMP_Parse(buffer, size, &image);

		// create a DirectDrawSurface for this bitmap
		memset(&ddsd, 0, sizeof(DDSURFACEDESC));
		ddsd.dwSize = sizeof(DDSURFACEDESC);
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
		ddsd.dwWidth = image.width;
		ddsd.dwHeight = image.height;
		ddsd.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
		ddsd.ddpfPixelFormat.dwRGBBitCount = image.depth;
		ddsd.ddpfPixelFormat.dwFlags = DDPF_RGB;
		ddsd.ddpfPixelFormat.dwRBitMask = image.red_mask;
		ddsd.ddpfPixelFormat.dwGBitMask = image.green_mask;
		ddsd.ddpfPixelFormat.dwBBitMask = image.blue_mask;

		if (!image.rgb) {
			ddsd.ddpfPixelFormat.dwFlags |= DDPF_PALETTEINDEXED8;
			if (DD_OK != DDraw()->lpVtbl->CreatePalette(DDraw(), DDPCAPS_8BIT, image.palette, &pal, NULL)){
				Error_Fatal(TRUE, "Cannot create palette");
			}
		}

		if (DD_OK == DDraw()->lpVtbl->CreateSurface(DDraw(), &ddsd, &pdds, NULL)){
			if (DD_OK == pdds->lpVtbl->QueryInterface(pdds, &IID_IDirectDrawSurface3, (LPVOID*)&surf3)){

				if (pal) surf3->lpVtbl->SetPalette(surf3, pal);

				memset(&desc, 0, sizeof(DDSURFACEDESC));
				desc.dwSize = sizeof(DDSURFACEDESC);
				if (DD_OK == surf3->lpVtbl->Lock(surf3, NULL, &desc, DDLOCK_WAIT, NULL)){

					lpImage newImage;
					ULONG y;
					LPUCHAR srcLine, destLine;
					
					// Copy the image...
					for (y=0 ; y<desc.dwHeight ; y++){
						destLine = &((LPUCHAR)desc.lpSurface)[y*desc.lPitch];
						srcLine = &((LPUCHAR)image.buffer1)[y*image.bytes_per_line];
						memcpy(destLine, srcLine, image.bytes_per_line);
					}
					surf3->lpVtbl->Unlock(surf3, NULL);
				
					if (newImage = Image_Create(surf3, desc.dwWidth, desc.dwHeight, 0, 0)){

						Mem_Free(buffer);
						pdds->lpVtbl->Release(pdds);
						return newImage;

					} else Error_Warn(TRUE, "Cannot create image");
				} else Error_Warn(TRUE, "Cannot lock surface");
			} else Error_Warn(TRUE, "Cannot obtain surface3");
			pdds->lpVtbl->Release(pdds);
		} else Error_Warn(TRUE, "Cannot create surface");
		Mem_Free(buffer);
	} else Error_Warn(TRUE, Error_Format("Cannot load bitmap \"%s\"", filename));

	return NULL;
}
*/

static COLORREF Image_RGB2CR(unsigned char r, unsigned char g, unsigned char b) {

	COLORREF cr;
	unsigned char *ptr = (unsigned char*)&cr;
	ptr[0] = r;
	ptr[1] = g;
	ptr[2] = b;
	ptr[3] = 0;
	return cr;
}

static VOID Image_CR2RGB(COLORREF cr, unsigned char *r, unsigned char *g, unsigned char *b)
{
	unsigned char *ptr = (unsigned char *) &cr;
	if (r) *r = ptr[0];
	if (g) *g = ptr[1];
	if (b) *b = ptr[2];
}

static ULONG Image_CountMaskBits(ULONG mask)
{
	ULONG i, count=0;

	for (i=0; i<(sizeof(mask) * 8); i++)
	{
		if (0 != (mask & (1<<i))) count++;
	}

	return count;
}

static ULONG Image_CountMaskBitShift(ULONG mask)
{
	ULONG i;
	for (i=0; i<(sizeof(mask) * 8); i++)
	{
		if (0 != (mask & (1<<i))) return i;
	}
	return 0xffffffff;
}

static VOID Image_FlipSurface(LPDDSURFACEDESC2 desc)
{
	ULONG h;
	ULONG shortsPerLine = desc->lPitch / 2;
	ULONG height = desc->dwHeight;
	LPUWORD start = (LPUWORD) desc->lpSurface;
	LPUWORD end = (LPUWORD) desc->lpSurface + ((height-1) * shortsPerLine);
	LPVOID temp = Mem_Alloc(sizeof(UWORD) * shortsPerLine);

	for (h=0; h<desc->dwHeight/2; h++)
	{
		memcpy(temp, start, sizeof(UWORD) * shortsPerLine);
		memcpy(start, end, sizeof(UWORD) * shortsPerLine);
		memcpy(end, temp, sizeof(UWORD) * shortsPerLine);
		start += shortsPerLine;
		end -= shortsPerLine;
	}
	Mem_Free(temp);
}

static BOOL Image_8BitSourceCopy(LPDDSURFACEDESC2 desc, LPD3DRMIMAGE image)
{
	if (desc->ddpfPixelFormat.dwRGBBitCount == 8)
	{
		Error_Warn(TRUE, "Why have I got an 8 bit surface");
		return FALSE;
	}
	else if (desc->ddpfPixelFormat.dwRGBBitCount == 16)
	{
		ULONG bmpLineLength = image->bytes_per_line;
		ULONG surfaceLineLength = ((ULONG) desc->lPitch) / 2;
		LPUCHAR bmpPtr;
		LPUWORD surfPtr;
		LPD3DRMPALETTEENTRY pal = image->palette;
		ULONG rMask, gMask, bMask;
		ULONG rBitCount, gBitCount, bBitCount;
		ULONG rBitShift, gBitShift, bBitShift;
		SLONG h, w;

		bmpPtr =  (LPUCHAR)  image->buffer1;
		surfPtr = (LPUWORD) desc->lpSurface;

		rMask = desc->ddpfPixelFormat.dwRBitMask;
		gMask = desc->ddpfPixelFormat.dwGBitMask;
		bMask = desc->ddpfPixelFormat.dwBBitMask;

		rBitCount = Image_CountMaskBits(rMask);
		gBitCount = Image_CountMaskBits(gMask);
		bBitCount = Image_CountMaskBits(bMask);

		rBitShift = Image_CountMaskBitShift(rMask);
		gBitShift = Image_CountMaskBitShift(gMask);
		bBitShift = Image_CountMaskBitShift(bMask);

		for (h=0; h<image->height; h++)
		{
			for (w=0; w<image->width; w++)
			{
				UCHAR r, g, b;
				USHORT surfaceValue;

				r = pal[*bmpPtr].red;
				g = pal[*bmpPtr].green;
				b = pal[*(bmpPtr++)].blue;

				// Mix the colours
				surfaceValue = 
					((r >> (8 - rBitCount)) << rBitShift) |
					((g >> (8 - gBitCount)) << gBitShift) |
					((b >> (8 - bBitCount)) << bBitShift) ;
				*(surfPtr++) = surfaceValue;
			}
			// Do the pitch thing
			bmpPtr += bmpLineLength - image->width;
			surfPtr += surfaceLineLength - image->width;
		}
		Image_FlipSurface(desc);
	}
	else if (desc->ddpfPixelFormat.dwRGBBitCount == 24)
	{
		Error_Warn(TRUE, "Why have I got an 24 bit surface");
		return FALSE;
	}
	else if (desc->ddpfPixelFormat.dwRGBBitCount == 32)
	{
		Error_Warn(TRUE, "Why have I got a 32 bit surface");
		return FALSE;
	}

	return TRUE;
}

static BOOL Image_24BitSourceCopy(LPDDSURFACEDESC2 desc, LPD3DRMIMAGE image)
{
	if (desc->ddpfPixelFormat.dwRGBBitCount == 8)
	{
		Error_Warn(TRUE, "Why have I got an 8 bit surface");
		return FALSE;
	}
	else if (desc->ddpfPixelFormat.dwRGBBitCount == 16)
	{
		// Not convinced that this is correct as it does 
		// not round up properly unless we have even sizes.
		ULONG bmpLineLength = image->bytes_per_line;
		ULONG surfaceLineLength = ((ULONG) desc->lPitch) / 2;
		LPUCHAR bmpPtr;
		LPUWORD surfPtr;
		ULONG rMask, gMask, bMask;
		ULONG rBitCount, gBitCount, bBitCount;
		ULONG rBitShift, gBitShift, bBitShift;
		SLONG h, w;

		bmpPtr =  (LPUCHAR)  image->buffer1;
		surfPtr = (LPUWORD) desc->lpSurface;

		rMask = desc->ddpfPixelFormat.dwRBitMask;
		gMask = desc->ddpfPixelFormat.dwGBitMask;
		bMask = desc->ddpfPixelFormat.dwBBitMask;

		rBitCount = Image_CountMaskBits(rMask);
		gBitCount = Image_CountMaskBits(gMask);
		bBitCount = Image_CountMaskBits(bMask);

		rBitShift = Image_CountMaskBitShift(rMask);
		gBitShift = Image_CountMaskBitShift(gMask);
		bBitShift = Image_CountMaskBitShift(bMask);

		for (h=0; h<image->height; h++)
		{
			for (w=0; w<image->width; w++)
			{
				UCHAR r, g, b;
				USHORT surfaceValue;

				b = *bmpPtr; bmpPtr++;
				g = *bmpPtr; bmpPtr++;
				r = *bmpPtr; bmpPtr++;

				// Mix the colours
				surfaceValue = 
					((r >> (8 - rBitCount)) << rBitShift) |
					((g >> (8 - gBitCount)) << gBitShift) |
					((b >> (8 - bBitCount)) << bBitShift) ;
				*(surfPtr++) = surfaceValue;
			}
			// Do the pitch thing
			bmpPtr += bmpLineLength - (image->width*3);
			surfPtr += surfaceLineLength - image->width;
		}
		Image_FlipSurface(desc);
	}
	else if (desc->ddpfPixelFormat.dwRGBBitCount == 24)
	{
		Error_Warn(TRUE, "Why have I got an 24 bit surface");
		return FALSE;
	}
	else if (desc->ddpfPixelFormat.dwRGBBitCount == 32)
	{
		Error_Warn(TRUE, "Why have I got a 32 bit surface");
		return FALSE;
	}

	return TRUE;
}

BOOL Image_CopyToDataToSurface(LPDIRECTDRAWSURFACE4 surface, LPD3DRMIMAGE image)
{
	DDSURFACEDESC2 desc = {0};
	desc.dwSize = sizeof(desc);

	if (DD_OK == surface->lpVtbl->Lock(surface, 0, &desc, DDLOCK_WAIT | DDLOCK_WRITEONLY, 0))
	{
		if (image->depth < 8)
		{
			Error_Warn(TRUE, "Please use 8/24 bit surfaces");
		}
		else if (8 == image->depth)
		{
			Image_8BitSourceCopy(&desc, image);
		}
		else if (16 == image->depth)
		{
			Error_Warn(TRUE, "16 bit image specified - surely BMP's cant do that");
		}
		else if (24 == image->depth)
		{
			Image_24BitSourceCopy(&desc, image);
		}
		else if (32 == image->depth)
		{
			Error_Warn(TRUE, "32 bit images are no fun - 8 and 24 only please");
		}
		
		surface->lpVtbl->Unlock(surface, 0);

		return TRUE;
	}
	else Error_Warn(TRUE, "Could not lock surface");

	return FALSE;
}

#ifndef _USE_WINDOWS_BMP_LOADER

lpImage Image_LoadBMPTexture(LPUCHAR fileName) {

	BOOL trans;
	ULONG width, height, size;
	LPDIRECTDRAWSURFACE4 surface;
	COLORREF penZero, pen255;
	D3DRMIMAGE d3drmimage;
	LPUCHAR buffer;
	lpImage image = NULL;

	if (buffer = File_LoadBinary(fileName, &size)) {

		BMP_Parse(buffer, size, &d3drmimage);
		if (FALSE == d3drmimage.rgb) {
			penZero = Image_RGB2CR(d3drmimage.palette[0].red, d3drmimage.palette[0].green, d3drmimage.palette[0].blue);
			pen255 = Image_RGB2CR(d3drmimage.palette[255].red, d3drmimage.palette[255].green, d3drmimage.palette[255].blue);
		}
		Mem_Free(buffer);

		if (surface = Container_LoadTextureSurface(fileName, TRUE, &width, &height, &trans)) {
			if (image = Image_Create(surface, width, height, penZero, pen255)) {
				if (DD_OK == surface->lpVtbl->QueryInterface(surface, &IID_IDirect3DTexture2, &image->texture)) {

					LPDIRECT3DDEVICE2 device2;

					if (mainGlobs.flags & MAIN_FLAG_DONTMANAGETEXTURES) {
						if (D3D_OK == lpIMDevice()->lpVtbl->QueryInterface(lpIMDevice(), &IID_IDirect3DDevice2, &device2)) {
							image->texture->lpVtbl->GetHandle(image->texture, device2, &image->textureHandle);
							device2->lpVtbl->Release(device2);
						}
					}

					image->flags |= IMAGE_FLAG_TEXTURE;
					return image;
				}
			}
			surface->lpVtbl->Release(surface);
		}
	}

	return NULL;
}

lpImage Image_LoadBMPScaled(LPUCHAR fileName, ULONG width, ULONG height)
{
	LPVOID buffer=0;
	ULONG size=0;
	D3DRMIMAGE image={0};
	DDSURFACEDESC2 ddsd={0};
	LPDIRECTDRAWSURFACE4 surface=0;
	COLORREF penZero, pen255;
	UCHAR name[1024];

	penZero = pen255 = Image_RGB2CR(0, 0, 0);

	if (buffer = File_LoadBinary(fileName, &size))
	{
/*		{
#include <stdio.h>
			FILE *dumpFile = fopen("ImageLoad.txt", "a");
			fprintf(dumpFile, "Data\\%s\n", fileName);
			fclose(dumpFile);
		}*/


		BMP_Parse(buffer, size, &image);
		if (FALSE == image.rgb) 
		{
			penZero = Image_RGB2CR(image.palette[0].red, image.palette[0].green, image.palette[0].blue);
			pen255 = Image_RGB2CR(image.palette[255].red, image.palette[255].green, image.palette[255].blue);
		}
	}
	else return NULL;

	sprintf(name, "Data\\%s", fileName);

	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	ddsd.dwWidth = image.width;
	ddsd.dwHeight = image.height;

	if (DD_OK == DirectDraw()->lpVtbl->CreateSurface(DirectDraw(), &ddsd, &surface, NULL))
	{
		lpImage newImage;

		if (Image_CopyToDataToSurface(surface, &image))
		{

			if (newImage = Image_Create(surface, image.width, image.height, penZero, pen255))
			{
				BMP_Cleanup(&image);

				if (buffer) Mem_Free(buffer);
				return newImage;
			}
			else Error_Warn(TRUE, "Could not create image");
			
		}
		else Error_Warn(TRUE, "Could not copy image to surface");

	}
	else Error_Warn(TRUE, "Could not create surface");

	if (surface) surface->lpVtbl->Release(surface);
	BMP_Cleanup(&image);
	if (buffer) Mem_Free(buffer);
	return 0;
}

#else //!_USE_WINDOWS_BMP_LOADER

lpImage Image_LoadBMPScaled(LPUCHAR filename, ULONG width, ULONG height){

	HBITMAP hbm;
	BITMAP bm;
	DDSURFACEDESC2 ddsd;
//	LPDIRECTDRAWSURFACE pdds;
	LPDIRECTDRAWSURFACE4 surface;
	COLORREF penZero, pen255;
	UCHAR name[1024];
	
#pragma message ("TODO: Load bitmap from memory")

	penZero = pen255 = Image_RGB2CR(0, 0, 0);

	{
		LPVOID buffer;
		ULONG size;
		D3DRMIMAGE image;
		if (buffer = File_LoadBinary(filename, &size)){
			BMP_Parse(buffer, size, &image);
			if (FALSE == image.rgb) penZero = Image_RGB2CR(image.palette[0].red, image.palette[0].green, image.palette[0].blue);
			if (FALSE == image.rgb) pen255 = Image_RGB2CR(image.palette[255].red, image.palette[255].green, image.palette[255].blue);
			BMP_Cleanup(&image);
			Mem_Free(buffer);
		}
	}


	sprintf(name, "Data\\%s", filename);


	if (hbm = (HBITMAP) LoadImage(NULL, name, IMAGE_BITMAP, width, height, LR_LOADFROMFILE|LR_CREATEDIBSECTION))
	{

		// get size of the bitmap
		GetObject(hbm, sizeof(bm), &bm);

		// create a DirectDrawSurface for this bitmap
		ZeroMemory(&ddsd, sizeof(ddsd));
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
		ddsd.dwWidth = bm.bmWidth;
		ddsd.dwHeight = bm.bmHeight;

		if (DD_OK == DirectDraw()->lpVtbl->CreateSurface(DirectDraw(), &ddsd, &surface, NULL)){
//			if (DD_OK == pdds->lpVtbl->QueryInterface(pdds, &IID_IDirectDrawSurface3, (LPVOID*)&surf3)){

				if (Image_CopyBMP(surface, hbm, 0, 0, 0, 0)){

					lpImage newImage;
					
					if (newImage = Image_Create(surface, bm.bmWidth, bm.bmHeight, penZero, pen255)){

//						pdds->lpVtbl->Release(pdds);
						DeleteObject(hbm);
						return newImage;

					} else Error_Warn(TRUE, "Cannot create image");
				} else Error_Warn(TRUE, "Cannot copy bitmap");
		//	} else Error_Warn(TRUE, "Cannot obtain surface3");
		//	pdds->lpVtbl->Release(pdds);
		} else Error_Warn(TRUE, "Cannot create surface");
		DeleteObject(hbm);
	} else Error_Warn(TRUE, Error_Format("Cannot load bitmap \"%s\"", filename));

	return NULL;
}

#endif //!_USE_WINDOWS_BMP_LOADER

VOID Image_SetPenZeroTrans(lpImage image){

	DDCOLORKEY ColourKey;

	Error_Fatal(!image, "NULL passed as image to Image_SetupTrans()");

	ColourKey.dwColorSpaceLowValue = image->penZero;
	ColourKey.dwColorSpaceHighValue = image->penZero;
	
	image->surface->lpVtbl->SetColorKey(image->surface, DDCKEY_SRCBLT, &ColourKey);
	image->flags |= IMAGE_FLAG_TRANS;
}

VOID Image_GetPenZero(lpImage image, LPREAL r, LPREAL g, LPREAL b){

	if (r) *r = (REAL)(image->penZeroRGB>>16) / 255.0f;
	if (g) *g = (REAL)((image->penZeroRGB>>8)&0x000000ff) / 255.0f;
	if (b) *b = (REAL)(image->penZeroRGB&0x000000ff) / 255.0f;
}

VOID Image_SetupTrans(lpImage image, REAL lowr, REAL lowg, REAL lowb, REAL highr, REAL highg, REAL highb){

	DDCOLORKEY ColourKey;
	COLORREF low, high;

	Error_Fatal(!image, "NULL passed as image to Image_SetupTrans()");

	low = Image_RGB2CR((UCHAR)(lowr*255), (UCHAR)(lowg*255), (UCHAR)(lowb*255));
	high = Image_RGB2CR((UCHAR)(highr*255), (UCHAR)(highg*255), (UCHAR)(highb*255));

	ColourKey.dwColorSpaceLowValue = Image_DDColorMatch(image->surface, low);
	ColourKey.dwColorSpaceHighValue = Image_DDColorMatch(image->surface, high);
	
	image->surface->lpVtbl->SetColorKey(image->surface, DDCKEY_SRCBLT, &ColourKey);
	image->flags |= IMAGE_FLAG_TRANS;

}
/*
VOID Image_DisplayScaled(lpImage image, LPAREA2D src, LPVECTOR2D destPos, LPVECTOR2D destSize){

	RECT r_src, r_dst;

	Error_Fatal(!image, "NULL passed as image to Image_DisplayScaled()");

	if (src){
		r_src.left = (ULONG) src->x; r_src.top = (ULONG) src->y;
		r_src.right = (ULONG) (src->x + src->width);
		r_src.bottom = (ULONG) (src->y + src->height);
	}

	if (destPos){

//		if (destPos->x < 0) destPos->x = appWidth() + destPos->x;
//		if (destPos->y < 0) destPos->y = appHeight() + destPos->y;

		r_dst.left = (ULONG) destPos->x; r_dst.top = (ULONG) destPos->y;
		if (destSize){
			r_dst.right = (ULONG) (destPos->x + destSize->x);
			r_dst.bottom = (ULONG) (destPos->y + destSize->y);
		} else if (src) {
			r_dst.right = (ULONG) (destPos->x + src->width);
			r_dst.bottom = (ULONG) (destPos->y + src->height);			
		} else {
			r_dst.right = (ULONG) destPos->x + image->width;
			r_dst.bottom = (ULONG) destPos->y + image->height;
		}
	}

	if (image->flags & IMAGE_FLAG_TRANS) DirectDraw_bSurf()->lpVtbl->Blt(DirectDraw_bSurf(), (destPos)?&r_dst:NULL, image->surface, (src)?&r_src:NULL, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
	else DirectDraw_bSurf()->lpVtbl->Blt(DirectDraw_bSurf(), (destPos)?&r_dst:NULL, image->surface, (src)?&r_src:NULL, DDBLT_WAIT, NULL);
}
*/

VOID Image_SetMainViewport(lpViewport vp) {

	LPDIRECT3DVIEWPORT useViewport1;

	if (imageGlobs.useViewport) imageGlobs.useViewport->lpVtbl->Release(imageGlobs.useViewport);

	vp->lpVP->lpVtbl->GetDirect3DViewport(vp->lpVP, &useViewport1);

	useViewport1->lpVtbl->QueryInterface(useViewport1, &IID_IDirect3DViewport3, &imageGlobs.useViewport);
	useViewport1->lpVtbl->Release(useViewport1);
}

VOID Image_SetAlphaIntensity(REAL level) {

	imageGlobs.alphaIntensity = level;
}

VOID Image_DisplayScaled2(lpImage image, LPAREA2D src, LPVECTOR2D destPos, LPVECTOR2D destSize, enum Image_TextureMode textureMode, REAL level, VECTOR2D uvs[4]) {

	if (image->flags & IMAGE_FLAG_TEXTURE) {
		if (imageGlobs.useViewport) {

			ImageVertex vertices[4];
			LPDIRECT3DVIEWPORT3 oldViewport;
			HRESULT getViewportResult;
			ULONG loop;

			switch (textureMode) {
			case Image_TextureMode_Fixed_Subtractive:	textureMode = Image_TextureMode_Subtractive;	break;
			case Image_TextureMode_Fixed_Additive:		textureMode = Image_TextureMode_Additive;		break;
			case Image_TextureMode_Fixed_Transparent:	textureMode = Image_TextureMode_Transparent;	break;
			default: level *= imageGlobs.alphaIntensity;
			}

			if (level > 1.0f) level = 1.0f;
			if (level < 0.0f) level = 0.0f;

			getViewportResult = lpIMDevice()->lpVtbl->GetCurrentViewport(lpIMDevice(), &oldViewport);
			lpIMDevice()->lpVtbl->SetCurrentViewport(lpIMDevice(), imageGlobs.useViewport);

			Error_Fatal(NULL==src&&NULL==uvs, "'src' must be specified for texture images");
			Error_Fatal(NULL==destPos, "'destPos' must be specified for texture images");
			Error_Fatal(NULL==destSize, "'destSize' must be specified for texture images");

			vertices[0].position.x = destPos->x;
			vertices[0].position.y = destPos->y;
			vertices[0].position.z = 0.0f;
			vertices[0].position.w = 1.0f;
			if (uvs) {
				vertices[0].tu = uvs[0].x;
				vertices[0].tv = uvs[0].y;
			} else {
				vertices[0].tu = src->x / image->width;
				vertices[0].tv = (src->y + src->height) / image->height;
			}
			vertices[1].position.x = destPos->x + destSize->x;
			vertices[1].position.y = destPos->y;
			vertices[1].position.z = 0.0f;
			vertices[1].position.w = 1.0f;
			if (uvs) {
				vertices[1].tu = uvs[1].x;
				vertices[1].tv = uvs[1].y;
			} else {
				vertices[1].tu = (src->x + src->width) / image->width;
				vertices[1].tv = (src->y + src->height) / image->height;
			}
			vertices[3].position.x = destPos->x + destSize->x;
			vertices[3].position.y = destPos->y + destSize->y;
			vertices[3].position.z = 0.0f;
			vertices[3].position.w = 1.0f;
			if (uvs) {
				vertices[3].tu = uvs[2].x;
				vertices[3].tv = uvs[2].y;
			} else {
				vertices[3].tu = (src->x + src->width) / image->width;
				vertices[3].tv = src->y / image->height;
			}
			vertices[2].position.x = destPos->x;
			vertices[2].position.y = destPos->y + destSize->y;
			vertices[2].position.z = 0.0f;
			vertices[2].position.w = 1.0f;
			if (uvs) {
				vertices[2].tu = uvs[3].x;
				vertices[2].tv = uvs[3].y;
			} else {
				vertices[2].tu = src->x / image->width;
				vertices[2].tv = src->y / image->height;
			}

			for (loop=0 ; loop<4 ; loop++) {
				switch (textureMode) {
				case Image_TextureMode_Additive:
				case Image_TextureMode_Transparent:
					vertices[loop].colour = 0x00ffffff | ((ULONG) (level * 255.0f) << 24);
					break;
				case Image_TextureMode_Subtractive:
					vertices[loop].colour = (ULONG) (level * 255.0f);
					vertices[loop].colour |= vertices[loop].colour << 8;
					vertices[loop].colour |= vertices[loop].colour << 16;
					break;
				default:
					vertices[loop].colour = 0x00ffffff;
					break;
				}
			}

			lpIMDevice()->lpVtbl->BeginScene(lpIMDevice());

			if (mainGlobs.flags & MAIN_FLAG_DONTMANAGETEXTURES) {
				lpIMDevice()->lpVtbl->SetRenderState(lpIMDevice(), D3DRENDERSTATE_TEXTUREHANDLE, image->textureHandle);
			} else {
				lpIMDevice()->lpVtbl->SetTexture(lpIMDevice(), 0, image->texture);
			}

			Main_ChangeRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, Image_TextureMode_Normal != textureMode);

			switch (textureMode) {
			case Image_TextureMode_Subtractive:
				Main_ChangeRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ZERO);
				Main_ChangeRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCCOLOR);
				break;
			case Image_TextureMode_Additive:
				Main_ChangeRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
				Main_ChangeRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
				break;
			case Image_TextureMode_Transparent:
				Main_ChangeRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
				Main_ChangeRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
				break;
			}

			Main_ChangeRenderState(D3DRENDERSTATE_ZENABLE, FALSE);
			Main_ChangeRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
			
			lpIMDevice()->lpVtbl->DrawPrimitive(lpIMDevice(), D3DPT_TRIANGLESTRIP, IMAGE_VERTEXFLAGS, vertices, 4, D3DDP_DONOTLIGHT|D3DDP_WAIT);

			Main_RestoreStates(FALSE);
			if (D3D_OK == getViewportResult) lpIMDevice()->lpVtbl->SetCurrentViewport(lpIMDevice(), oldViewport);

			lpIMDevice()->lpVtbl->EndScene(lpIMDevice());
		}

	} else {

		RECT r_src, r_dst;

		Error_Fatal(!image, "NULL passed as image to Image_DisplayScaled()");

		if (src){
			r_src.left = (ULONG) src->x;
			r_src.top = (ULONG) src->y;
			r_src.right = (ULONG) (src->x + src->width);
			r_src.bottom = (ULONG) (src->y + src->height);
		}

		if (destPos){
	/*
			if (destPos->x < 0) destPos->x = appWidth() + destPos->x;
			if (destPos->y < 0) destPos->y = appHeight() + destPos->y;
	*/
			r_dst.left = (ULONG) destPos->x;
			r_dst.top = (ULONG) destPos->y;
			if (destSize){
				r_dst.right = (ULONG) (destPos->x + destSize->x);
				r_dst.bottom = (ULONG) (destPos->y + destSize->y);
			} else if (src) {
				r_dst.right = (ULONG) (destPos->x + src->width);
				r_dst.bottom = (ULONG) (destPos->y + src->height);			
			} else {
				r_dst.right = (ULONG) (destPos->x + image->width);
				r_dst.bottom = (ULONG) (destPos->y + image->height);
			}
		}

		if (image->flags & IMAGE_FLAG_TRANS) DirectDraw_bSurf()->lpVtbl->Blt(DirectDraw_bSurf(), (destPos)?&r_dst:NULL, image->surface, (src)?&r_src:NULL, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
		else DirectDraw_bSurf()->lpVtbl->Blt(DirectDraw_bSurf(), (destPos)?&r_dst:NULL, image->surface, (src)?&r_src:NULL, DDBLT_WAIT, NULL);
	}
}

VOID Image_DisplayScaled(lpImage image, LPAREA2D src, LPVECTOR2D destPos, LPVECTOR2D destSize) {

	Image_DisplayScaled2(image, src, destPos, destSize, Image_TextureMode_Normal, 0.0f, NULL);
}

LPVOID Image_LockSurface(lpImage image, LPULONG pitch, LPULONG bpp){

	DDSURFACEDESC2 desc;

	memset(&desc, 0, sizeof(DDSURFACEDESC2));
	desc.dwSize = sizeof(DDSURFACEDESC2);
	if (DD_OK == image->surface->lpVtbl->Lock(image->surface, NULL, &desc, DDLOCK_WAIT, NULL)){
		*pitch = desc.lPitch;
		*bpp = desc.ddpfPixelFormat.dwRGBBitCount;
		return desc.lpSurface;
	}

	return NULL;
}

VOID Image_UnlockSurface(lpImage image){

	image->surface->lpVtbl->Unlock(image->surface, NULL);
}

ULONG Image_GetPen255(lpImage image){

	DDPIXELFORMAT pf;
	ULONG pen = 0;
	LPUCHAR s, t;

	memset(&pf, 0, sizeof(DDPIXELFORMAT));
	pf.dwSize = sizeof(DDPIXELFORMAT);

	if (DD_OK == image->surface->lpVtbl->GetPixelFormat(image->surface, &pf)){
//		if (8 == pf.dwRGBBitCount) return 0xff000000;
		s = (LPUCHAR) &pen;
		t = (LPUCHAR) &image->pen255;
		s[0] = t[3];
		s[1] = t[2];
		s[2] = t[1];
		s[3] = t[0];
//		return image->pen255 << (32 - pf.dwRGBBitCount);
		return pen;
	}

	return 0;
}

ULONG Image_GetPixelMask(lpImage image){

	DDPIXELFORMAT pf;

	memset(&pf, 0, sizeof(DDPIXELFORMAT));
	pf.dwSize = sizeof(DDPIXELFORMAT);

	if (DD_OK == image->surface->lpVtbl->GetPixelFormat(image->surface, &pf)){
		return 0xffffffff << (32 - pf.dwRGBBitCount);
	}
	return 0;
}

BOOL Image_GetPixel(lpImage image, ULONG x, ULONG y, LPULONG colour) {

	ULONG col, bpp;
	DDSURFACEDESC2 desc;
	memset(&desc, 0, sizeof(DDSURFACEDESC2));
	desc.dwSize = sizeof(DDSURFACEDESC2);

	if (x < image->width && y < image->height) {
		if (DD_OK == image->surface->lpVtbl->Lock(image->surface, NULL, &desc, DDLOCK_WAIT|DDLOCK_READONLY, NULL)){
			bpp = desc.ddpfPixelFormat.dwRGBBitCount;
			col = *((LPULONG) &((LPUCHAR) desc.lpSurface)[(y * desc.lPitch) + (x * (bpp / 8))]);
 			*colour = col >> (32 - bpp);
			image->surface->lpVtbl->Unlock(image->surface, NULL);
			return TRUE;
		}
	}

	return FALSE;
}

/*
lpImage_Texture Image_CreateTexture(lpImage image, LPAREA2D area, LPULONG status){

	LPDIRECT3DRMTEXTURE2 texture = NULL;
	LPDIRECTDRAWSURFACE surf1 = NULL;
	LPDIRECTDRAWSURFACE3 surface;

	Error_Fatal(!image, "NULL passed as image to Image_CreateTexture()");

	if (status) *status = 1;

	surface = image->surface;
	surface->lpVtbl->QueryInterface(surface, &IID_IDirectDrawSurface, &surf1);

	if (videoTexture()){

		DDSURFACEDESC origDesc;
		DDSURFACEDESC newDesc;
		LPDIRECTDRAWSURFACE newSurf = NULL;
		HRESULT r;

		ZeroMemory(&origDesc, sizeof(origDesc));
		origDesc.dwSize = sizeof(origDesc);
		surface->lpVtbl->GetSurfaceDesc(surface, &origDesc);

		ZeroMemory(&newDesc, sizeof(newDesc));
		newDesc.dwSize = sizeof(newDesc);
		newDesc.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
		newDesc.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_TEXTURE;

		if (area){
			newDesc.dwWidth = (ULONG) (area->width * origDesc.dwWidth);
			newDesc.dwHeight = (ULONG) (area->height * origDesc.dwHeight);
		} else {
			newDesc.dwWidth = origDesc.dwWidth;
			newDesc.dwHeight = origDesc.dwHeight;
		}

		CHKDD((r = DDraw()->lpVtbl->CreateSurface(DDraw(), &newDesc, &newSurf, NULL)));

		if (DD_OK != r) {
			newDesc.ddsCaps.dwCaps = DDSCAPS_TEXTURE;		// Don't force it into video memory...
			CHKDD((r = DDraw()->lpVtbl->CreateSurface(DDraw(), &newDesc, &newSurf, NULL)));
			if (status) *status = 2;
		}

		if (DD_OK == r){
			// Copy the image...

			if (area){

				RECT sRect;

				sRect.left = (ULONG) (area->x * origDesc.dwWidth);
				sRect.top = (ULONG) (area->y * origDesc.dwHeight);
				sRect.right = sRect.left + newDesc.dwWidth;
				sRect.bottom = sRect.top + newDesc.dwHeight;

//				CHKDD(newSurf->lpVtbl->Blt(newSurf, NULL, surf1, &sRect, DDBLT_WAIT, NULL));

				Image_MyBlt(newSurf, surface, sRect.left, sRect.top);


			//	DDraw_bSurf()->lpVtbl->Blt(DDraw_bSurf(), NULL, newSurf, NULL, DDBLT_WAIT, NULL);
			//	DDraw_Flip();
			//	Sleep(500);

				Error_Debug(Error_Format("newDesc.dwWidth == %i newDesc.dwHeight == %i sRect.left == %i sRect.top == %i sRect.right == %i sRect.bottom == %i\n", newDesc.dwWidth, newDesc.dwHeight, sRect.left, sRect.top, sRect.right, sRect.bottom));

			} else {
				CHKDD(newSurf->lpVtbl->Blt(newSurf, NULL, surf1, NULL, DDBLT_WAIT, NULL));
			}
			surf1->lpVtbl->Release(surf1);
			surf1 = newSurf;
			
			{
				ULONG total, avail;
				DDraw_GetAvailTextureMem(&total, &avail);
				Error_Debug(Error_Format("%ix%ix%i Texture mem: %i avail: %i used: %i\n", newDesc.dwWidth, newDesc.dwHeight, newDesc.ddpfPixelFormat.dwRGBBitCount, total, avail, total-avail));
				DDraw_GetAvailVideoMem(&total, &avail);
				Error_Debug(Error_Format("Video mem: %i avail: %i used: %i\n", total, avail, total-avail));
			}			
			
		} else {
			Error_Warn(TRUE, "Cannot create surface");
			if (status) *status = 0;
			surf1->lpVtbl->Release(surf1);
			return NULL;
		}
	}

	if (D3DRM_OK != lpD3DRM()->lpVtbl->CreateTextureFromSurface(lpD3DRM(), surf1, &texture)) {
		texture = NULL;
		if (status) *status = 0;
	}
	Error_Debug(Error_Format("release -> %i\n", surf1->lpVtbl->Release(surf1)));

	return (lpImage_Texture) texture;
}

VOID Image_FreeTexture(lpImage_Texture dead){

	LPDIRECT3DRMTEXTURE2 texture = (LPDIRECT3DRMTEXTURE2) dead;

	if (texture->lpVtbl->Release(texture)) Error_Warn(TRUE, "Image_FreeTexture() didn't free the texture");
}
*/

/**********************************************************************************
 ******** Image Static Functions
 **********************************************************************************/

static lpImage Image_Create(LPDIRECTDRAWSURFACE4 surface, ULONG width, ULONG height, COLORREF penZero, COLORREF pen255){

	Image *newImage;

	Image_CheckInit();

	if (NULL == imageGlobs.freeList) Image_AddList();
	
	newImage = imageGlobs.freeList;
	imageGlobs.freeList = newImage->nextFree;
	newImage->nextFree = newImage;

	newImage->flags = 0x00000000;
	newImage->width = width;
	newImage->height = height;
	newImage->surface = surface;
	newImage->penZeroRGB = penZero;
	newImage->penZero = Image_DDColorMatch(surface, penZero);
	newImage->pen255 = Image_DDColorMatch(surface, pen255);

	/*
	// Flip the texture (if required)

	if (flip) {
		ULONG y, byteWidth;
		LPUCHAR buffer, topline, bottomline;
		DDSURFACEDESC sd;
		memset(&sd, 0, sizeof(sd));
		sd.dwSize = sizeof(sd);

		if (DD_OK == surface->lpVtbl->Lock(surface, NULL, &sd, DDLOCK_WAIT, NULL)){

			byteWidth = (sd.ddpfPixelFormat.dwRGBBitCount / 8) * sd.dwWidth;
			buffer = Mem_Alloc(byteWidth);
			topline = (LPUCHAR) sd.lpSurface;
			bottomline = &((LPUCHAR) sd.lpSurface)[(sd.dwHeight-1) * sd.lPitch];
			
			for (y=0 ; y<sd.dwHeight/2 ; y++){
				memcpy(buffer, bottomline, byteWidth);
				memcpy(bottomline, topline, byteWidth);
				memcpy(topline, buffer, byteWidth);
				topline += sd.lPitch;
				bottomline -= sd.lPitch;
			}

			surface->lpVtbl->Unlock(surface, NULL);
			Mem_Free(buffer);
		}
	}
*/
	return newImage;
}

static VOID Image_InitFromSurface(lpImage newImage, LPDIRECTDRAWSURFACE4 surface, ULONG width, ULONG height, COLORREF penZero, COLORREF pen255){

	Image_CheckInit();

	if (NULL == imageGlobs.freeList) Image_AddList();
	
	newImage->nextFree = newImage;
	newImage->flags = 0x00000000;
	newImage->width = width;
	newImage->height = height;
	newImage->surface = surface;
	newImage->penZeroRGB = penZero;
	newImage->penZero = Image_DDColorMatch(surface, penZero);
	newImage->pen255 = Image_DDColorMatch(surface, pen255);
}

static VOID Image_AddList(VOID){

	Image *list;
	ULONG loop, count;

	Image_CheckInit();

	Error_Fatal(imageGlobs.listCount+1 >= IMAGE_MAXLISTS, "Run out of lists");

	count = 0x00000001 << imageGlobs.listCount;

	if (list = imageGlobs.listSet[imageGlobs.listCount] = 
		Mem_Alloc(sizeof(Image) * count)){

		imageGlobs.listCount++;

		for (loop=1 ; loop<count ; loop++){

			list[loop-1].nextFree = &list[loop];
		}
		list[count-1].nextFree = imageGlobs.freeList;
		imageGlobs.freeList = list;

	} else Error_Fatal(TRUE, Error_Format("Unable to allocate %d bytes of memory for new list.\n", sizeof(Image) * count));
}

static VOID Image_RemoveAll(VOID){

	ULONG list, count, loop;
	lpImage tempImage;

	for (list=0 ; list<imageGlobs.listCount ; list++){
		if (imageGlobs.listSet[list]){
			count = 0x00000001 << list;
			for (loop=0 ; loop<count ; loop++){
				if (tempImage = &imageGlobs.listSet[list][loop]){
					if (tempImage->nextFree == tempImage){

						Image_Remove(tempImage);

					}
				}
			}
		}
	}
}

static BOOL Image_CopyBMP(LPDIRECTDRAWSURFACE4 pdds, HBITMAP hbm, ULONG x, ULONG y, ULONG dx, ULONG dy){

    HDC hdcImage;
    HDC hdc;
    BITMAP bm;
    DDSURFACEDESC2 ddsd;

    if (hbm && pdds) {

		//  select bitmap into a memoryDC so we can use it.
		if (hdcImage = CreateCompatibleDC(NULL)){
	
			SelectObject(hdcImage, hbm);

			// get size of the bitmap
			GetObject(hbm, sizeof(bm), &bm);    // get size of bitmap
			dx = dx == 0 ? bm.bmWidth  : dx;    // use the passed size, unless zero
			dy = dy == 0 ? bm.bmHeight : dy;

			// get size of surface.
			ddsd.dwSize = sizeof(ddsd);
			ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
			if (DD_OK == pdds->lpVtbl->GetSurfaceDesc(pdds, &ddsd)){

				if (DD_OK == pdds->lpVtbl->GetDC(pdds, &hdc)){

					StretchBlt(hdc, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, x, y, dx, dy, SRCCOPY);
					pdds->lpVtbl->ReleaseDC(pdds, hdc);

					return TRUE;
				}

			} else Error_Warn(TRUE, "Unable to get surface description");

			DeleteDC(hdcImage);
		}
	}

    return FALSE;
}

#ifndef _USE_WINDOWS_BMP_LOADER

DWORD Image_DDColorMatch(LPDIRECTDRAWSURFACE4 pdds, DWORD rgb)
{
    DDSURFACEDESC2 ddsd = {0};
	UCHAR r, g, b;
	DWORD dw = 0;

	ddsd.dwSize = sizeof(ddsd);

	Image_CR2RGB(rgb, &r, &g, &b);

	if (DD_OK == pdds->lpVtbl->Lock(pdds, NULL, &ddsd, DDLOCK_WAIT, NULL))
	{
		ULONG rMask, gMask, bMask;
		ULONG rBitCount, gBitCount, bBitCount;
		ULONG rBitShift, gBitShift, bBitShift;

		rMask = ddsd.ddpfPixelFormat.dwRBitMask;
		gMask = ddsd.ddpfPixelFormat.dwGBitMask;
		bMask = ddsd.ddpfPixelFormat.dwBBitMask;

		rBitCount = Image_CountMaskBits(rMask);
		gBitCount = Image_CountMaskBits(gMask);
		bBitCount = Image_CountMaskBits(bMask);

		rBitShift = Image_CountMaskBitShift(rMask);
		gBitShift = Image_CountMaskBitShift(gMask);
		bBitShift = Image_CountMaskBitShift(bMask);

		dw = ((r >> (8 - rBitCount)) << rBitShift) |
			 ((g >> (8 - gBitCount)) << gBitShift) |
			 ((b >> (8 - bBitCount)) << bBitShift);

        if (ddsd.ddpfPixelFormat.dwRGBBitCount < 32) 
			dw &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount)-1;

		pdds->lpVtbl->Unlock(pdds, 0);
	}

	return dw;
}

#else //!_USE_WINDOWS_BMP_LOADER

DWORD Image_DDColorMatch(LPDIRECTDRAWSURFACE4 pdds, DWORD rgb)
{
	// DDColorMatch
	// convert a RGB color to a pysical color.
	// we do this by leting GDI SetPixel() do the color matching
	// then we lock the memory and see what it got mapped to.

    COLORREF rgbT;
    HDC hdc;
    DWORD dw = CLR_INVALID;
    DDSURFACEDESC2 ddsd;

    //  use GDI SetPixel to color match for us
    if (rgb != CLR_INVALID && pdds->lpVtbl->GetDC(pdds, &hdc) == DD_OK) {
		rgbT = GetPixel(hdc, 0, 0);             // save current pixel value
		SetPixel(hdc, 0, 0, rgb);               // set our value
		pdds->lpVtbl->ReleaseDC(pdds, hdc);
    }

    // now lock the surface so we can read back the converted color
    ddsd.dwSize = sizeof(ddsd);
 //   while ((hres = pdds->lpVtbl->Lock(pdds, NULL, &ddsd, 0, NULL)) == DDERR_WASSTILLDRAWING);
//    if (hres == DD_OK)

	if (DD_OK == pdds->lpVtbl->Lock(pdds, NULL, &ddsd, DDLOCK_WAIT, NULL)){
		dw  = *((DWORD *)ddsd.lpSurface);                     // get DWORD
        if (ddsd.ddpfPixelFormat.dwRGBBitCount < 32) dw &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount)-1;  // mask it to bpp
		pdds->lpVtbl->Unlock(pdds, NULL);
    }

    //  now put the color that was there back.
    if (rgb != CLR_INVALID && pdds->lpVtbl->GetDC(pdds, &hdc) == DD_OK){
		SetPixel(hdc, 0, 0, rgbT);
		pdds->lpVtbl->ReleaseDC(pdds, hdc);
    }

    return dw;
}

#endif //!_USE_WINDOWS_BMP_LOADER

static VOID Image_MyBlt(LPDIRECTDRAWSURFACE dest, LPDIRECTDRAWSURFACE src, ULONG sx, ULONG sy){

	DDSURFACEDESC sDesc, dDesc;
	ULONG byteWidth, y;
	LPUCHAR sLine, dLine;

	if (DD_OK == src->lpVtbl->Lock(src, NULL, &sDesc, DDLOCK_WAIT, NULL)){
		if (DD_OK == dest->lpVtbl->Lock(dest, NULL, &dDesc, DDLOCK_WAIT, NULL)){
			if (sDesc.ddpfPixelFormat.dwRGBBitCount == dDesc.ddpfPixelFormat.dwRGBBitCount){

				byteWidth = (sDesc.ddpfPixelFormat.dwRGBBitCount / 8) * sDesc.dwWidth;
				sLine = (LPUCHAR) sDesc.lpSurface;
				dLine = (LPUCHAR) dDesc.lpSurface;

				sLine += (sy * sDesc.lPitch) + (sx * sDesc.ddpfPixelFormat.dwRGBBitCount);
				
				for (y=0 ; y<sDesc.dwHeight ; y++){
					memcpy(dLine, sLine, byteWidth);
					sLine += sDesc.lPitch;
					dLine -= dDesc.lPitch;
				}

				src->lpVtbl->Unlock(src, NULL);
				dest->lpVtbl->Unlock(dest, NULL);
			}
		}
	}
}


VOID Image_GetScreenshot(lpImage image, ULONG xsize, ULONG ysize)
{
	HRESULT hr;
	LPDIRECTDRAWSURFACE4 surf;
	// Create surface
	DDSURFACEDESC2 desc;
	memset(&desc, 0, sizeof(DDSURFACEDESC2));
	desc.dwSize=sizeof(DDSURFACEDESC2);
	desc.dwWidth=xsize;
	desc.dwHeight=ysize;
	desc.ddsCaps.dwCaps=DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	desc.dwFlags=DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
	if (hr=DirectDraw()->lpVtbl->CreateSurface(DirectDraw(), &desc, &surf, NULL))
	{
		CHKDD(hr);
		return;
	}
	// Blit back buffer onto here.
	{
		RECT dest;
		dest.left=0;
		dest.top=0;
		dest.right=xsize;
		dest.bottom=ysize;
		surf->lpVtbl->Blt(surf, &dest, DirectDraw_bSurf(), NULL, 0, 0);
	}
	// Create image
	Image_InitFromSurface(image, surf, xsize, ysize, 0, 0);
}

BOOL Image_SaveBMP(lpImage image, LPUCHAR fname) {

	return DirectDraw_SaveBMP(image->surface, fname);
}
