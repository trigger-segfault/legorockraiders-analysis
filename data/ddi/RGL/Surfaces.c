
#include <ddraw.h>

#include "Standard.h"
#include "Mem.h"
#include "Files.h"
#include "Lists.h"
#include "Errors.h"
#include "DirectX.h"
#include "Quantizer.h"
#include "Surfaces.h"

struct SurfaceGlobs {

	struct List *sharedObjectList;

} surfaceGlobs = { 0 };

VOID Surface_Initialise(VOID) {

	surfaceGlobs.sharedObjectList = File_CreateSharedObjectList();
}

VOID Surface_Shutdown(VOID) {

	File_RemoveSharedObjectList(surfaceGlobs.sharedObjectList);
	surfaceGlobs.sharedObjectList = NULL;
}

LPDIRECTDRAWSURFACE7 Surface_GetShared(LPUCHAR fname) {

	// NOT for texture surfaces...

	return File_FindSharedObject(surfaceGlobs.sharedObjectList, fname);
}

VOID Surface_RegisterShared(LPUCHAR fname, LPDIRECTDRAWSURFACE7 surface) {

	// NOT for texture surfaces...

	File_RegisterSharedObject(surfaceGlobs.sharedObjectList, fname, surface);
}

VOID Surface_Remove(LPDIRECTDRAWSURFACE7 surface) {

	ULONG count;

	// NOT for texture surfaces...
	
	if (File_ReleaseSharedObject(surfaceGlobs.sharedObjectList, surface)) {
		count = surface->lpVtbl->Release(surface);
		Error_Fatal(count, "Surface was not removed");
	}
}

/*
BOOL Surface_QuarterScale(LPDIRECTDRAWSURFACE7 src, ULONG level) {

	ULONG width, height;
	DDSURFACEDESC2 desc;
	BOOL result = TRUE;
	HRESULT r;

	DirectX_InitStruct(&desc);

	if (DD_OK == (r = src->lpVtbl->Lock(src, NULL, &desc, DDLOCK_WAIT, NULL))) {
	
		width = desc.dwWidth >> level;
		height = desc.dwHeight >> level;

		if (width && height) {

			if (8 == desc.ddpfPixelFormat.dwRGBBitCount) {
			} else {
				Surface_QuarterScale_Masked(&desc);
			}

		} else result = FALSE;

		r = src->lpVtbl->Unlock(src, NULL);

	} else {

		Error_DirectX(r, "Lock");
		result = FALSE;

	}

	return result;
}

static VOID Surface_QuarterScale_Masked(LPDDSURFACEDESC2 sDesc) {

	ULONG x, y, sByteDepth;
	LPULONG pixel[4];
	ULONG r, g, b;
	UCHAR sRBits, sGBits, sBBits;
	ULONG loop;
	const ULONG offset[4][2] = { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 } };
	
	sByteDepth = sDesc->ddpfPixelFormat.dwRGBBitCount / 8;
	DirectX_GetBitCounts(&sDesc->ddpfPixelFormat, NULL, &sRBits, &sGBits, &sBBits);

	for (y=0 ; y<sDesc->dwHeight ; y++) {
		for (x=0 ; x<sDesc->dwWidth ; x++) {

			r = g = b = 0;

			for (loop=0 ; loop<4 ; loop++) {
				pixel[loop] = (LPULONG) &((LPUCHAR) sDesc->lpSurface)[((y + offset[loop][1]) * sDesc->lPitch) + ((x + offset[loop][0]) * sByteDepth)];
				r += (UCHAR) (0xff & (*pixel >> 16)) >> (8 - sRBits);
				g += (UCHAR) (0xff & (*pixel >> 8)) >> (8 - sGBits);
				b += (UCHAR) (0xff & *pixel) >> (8 - sBBits);
			}


		}
	}
}
*/

VOID Surface_Convert(LPDIRECTDRAWSURFACE7 src, LPDIRECTDRAWSURFACE7 dest) {

	DDSURFACEDESC2 sDesc, dDesc;
	HRESULT r = DD_OK;
	BOOL incorrectSize = FALSE;
	LPDIRECTDRAWPALETTE pal = NULL;
	LPDIRECTDRAWPALETTE srcPal = NULL;
	PALETTEENTRY palette[256];

	DirectX_InitStruct(&sDesc);
	DirectX_InitStruct(&dDesc);

	src->lpVtbl->GetPalette(src, &srcPal);
	if (srcPal) srcPal->lpVtbl->GetEntries(srcPal, 0, 0, 256, palette);

	if (DD_OK == (r = src->lpVtbl->Lock(src, NULL, &sDesc, DDLOCK_WAIT, NULL))) {
		if (DD_OK == (r = dest->lpVtbl->Lock(dest, NULL, &dDesc, DDLOCK_WAIT, NULL))) {

			if (dDesc.dwWidth <= sDesc.dwWidth && dDesc.dwHeight <= sDesc.dwHeight) {

				if (8 == dDesc.ddpfPixelFormat.dwRGBBitCount) {
					if (8 == sDesc.ddpfPixelFormat.dwRGBBitCount) Surface_CopyData_8Bit(&sDesc, &dDesc);
					else pal = Surface_GeneratePalettizedSurface(&sDesc, &dDesc, 256);
				} else {
					if (8 == sDesc.ddpfPixelFormat.dwRGBBitCount) Surface_GenerateFromPalettizedSurface(&sDesc, &dDesc, palette);
					else Surface_CopyData_Masked(&sDesc, &dDesc);
				}

			} else incorrectSize = TRUE;
			
			dest->lpVtbl->Unlock(dest, NULL);
		}
		src->lpVtbl->Unlock(src, NULL);
	}

	if (incorrectSize) Error_Fatal(TRUE, "Surface size mismatch");
	else Error_DirectX(r, "Lock");

	if (8 == dDesc.ddpfPixelFormat.dwRGBBitCount && 8 == sDesc.ddpfPixelFormat.dwRGBBitCount) {

		PALETTEENTRY palette[256];

		r = srcPal->lpVtbl->GetEntries(srcPal, 0, 0, 256, palette);
		Error_DirectX(r, "GetEntries");
		r = DirectX_DirectDraw()->lpVtbl->CreatePalette(DirectX_DirectDraw(), DDPCAPS_8BIT|DDPCAPS_ALLOW256|DDPCAPS_INITIALIZE, palette, &pal, NULL);
		Error_DirectX(r, "CreatePalette");
	}

	if (pal) {
		r = dest->lpVtbl->SetPalette(dest, pal);
		Error_DirectX(r, "SetPalette");
	}
}

static VOID Surface_CopyData_8Bit(LPDDSURFACEDESC2 sDesc, LPDDSURFACEDESC2 dDesc) {

	ULONG y;

	for (y=0 ; y<dDesc->dwHeight ; y++) {
		Mem_Copy(&((LPUCHAR) dDesc->lpSurface)[y * dDesc->lPitch], &((LPUCHAR) sDesc->lpSurface)[y * sDesc->lPitch], dDesc->dwWidth);
	}
}

static VOID Surface_CopyData_Masked(LPDDSURFACEDESC2 sDesc, LPDDSURFACEDESC2 dDesc) {

	ULONG x, y, sByteDepth, dByteDepth;
	LPULONG pixel;
	ULONG r, g, b;
	UCHAR sRBits, sGBits, sBBits;
	UCHAR dRBits, dGBits, dBBits;
	UCHAR rShift, gShift, bShift;
	
	sByteDepth = sDesc->ddpfPixelFormat.dwRGBBitCount / 8;
	dByteDepth = dDesc->ddpfPixelFormat.dwRGBBitCount / 8;
	DirectX_GetBitCounts(&sDesc->ddpfPixelFormat, NULL, &sRBits, &sGBits, &sBBits);
	DirectX_GetBitCounts(&dDesc->ddpfPixelFormat, NULL, &dRBits, &dGBits, &dBBits);

	// Clear the destination surface memory...
	for (y=0 ; y<dDesc->dwHeight ; y++) {
		memset(&((LPUCHAR) dDesc->lpSurface)[y * dDesc->lPitch], 0, dDesc->dwWidth * dByteDepth);
	}

	rShift = ((SCHAR) dRBits - (SCHAR) sRBits) + dBBits + dGBits;
	gShift = ((SCHAR) dGBits - (SCHAR) sGBits) + dBBits;
	bShift = ((SCHAR) dBBits - (SCHAR) sBBits) + 8;

	for (y=0 ; y<dDesc->dwHeight ; y++) {
		for (x=0 ; x<dDesc->dwWidth ; x++) {

			pixel = (LPULONG) &((LPUCHAR) sDesc->lpSurface)[(y * sDesc->lPitch) + (x * sByteDepth)];
			r = (UCHAR) (0xff & (*pixel >> 16)) >> (8 - sRBits);
			g = (UCHAR) (0xff & (*pixel >> 8)) >> (8 - sGBits);
			b = (UCHAR) (0xff & *pixel) >> (8 - sBBits);

			pixel = (LPULONG) &((LPUCHAR) dDesc->lpSurface)[(y * dDesc->lPitch) + (x * dByteDepth)];

			*pixel |= ((r << rShift) & dDesc->ddpfPixelFormat.dwRBitMask);
			*pixel |= ((g << gShift) & dDesc->ddpfPixelFormat.dwGBitMask);
			*pixel |= (((b << bShift) >> 8) & dDesc->ddpfPixelFormat.dwBBitMask);
		}
	}
}

static VOID Surface_GenerateFromPalettizedSurface(LPDDSURFACEDESC2 sDesc, LPDDSURFACEDESC2 dDesc, PALETTEENTRY palette[256]) {

	UCHAR rBits, gBits, bBits;
	ULONG byteDepth;
	LPULONG pixel;
	UCHAR index;
	ULONG x, y;

	DirectX_GetBitCounts(&dDesc->ddpfPixelFormat, NULL, &rBits, &gBits, &bBits);

	byteDepth = dDesc->ddpfPixelFormat.dwRGBBitCount / 8;
	for (y=0 ; y<dDesc->dwHeight ; y++) {
		memset(&((LPUCHAR) dDesc->lpSurface)[y * dDesc->lPitch], 0, dDesc->dwWidth * byteDepth);
	}

	for (y=0 ; y<dDesc->dwHeight ; y++) {
		for (x=0 ; x<dDesc->dwWidth ; x++) {
			index = ((LPUCHAR) sDesc->lpSurface)[(y * sDesc->lPitch) + x];
			pixel = (LPULONG) &((LPUCHAR) dDesc->lpSurface)[(y * dDesc->lPitch) + (x * byteDepth)];
			*pixel |= (palette[index].peRed >> (8 - rBits)) << (gBits + bBits);
			*pixel |= (palette[index].peGreen >> (8 - gBits)) << (bBits);
			*pixel |= (palette[index].peBlue >> (8 - bBits));
		}
	}
}

static LPDIRECTDRAWPALETTE Surface_GeneratePalettizedSurface(LPDDSURFACEDESC2 sDesc, LPDDSURFACEDESC2 dDesc, ULONG colourCount) {

	ULONG pixel, x, y, loop, entryCount = 0, byteDepth;
	LPUCHAR list, rList, gList, bList;
	UCHAR rBits, gBits, bBits;
	LPULONG colourList;
	PALETTEENTRY palette[256];
	LPDIRECTDRAWPALETTE pal = NULL;
	HRESULT r;

	byteDepth = sDesc->ddpfPixelFormat.dwRGBBitCount / 8;
	DirectX_GetBitCounts(&sDesc->ddpfPixelFormat, NULL, &rBits, &gBits, &bBits);

	// Use the destination image width and height for the source colour data...
	list = Mem_Alloc(dDesc->dwWidth * dDesc->dwHeight * 3);
	rList = &list[dDesc->dwWidth * dDesc->dwHeight * 0];
	gList = &list[dDesc->dwWidth * dDesc->dwHeight * 1];
	bList = &list[dDesc->dwWidth * dDesc->dwHeight * 2];

	// Fill in the colour data up to the destination width/height...
	for (y=0 ; y<dDesc->dwHeight ; y++) {
		for (x=0 ; x<dDesc->dwWidth ; x++) {

			pixel = ((LPULONG) &((LPUCHAR) sDesc->lpSurface)[(y * sDesc->lPitch) + (x * byteDepth)])[0];

			rList[(y * dDesc->dwWidth) + x] = (UCHAR) (0xff & (pixel >> 16)) >> (8 - rBits);
			gList[(y * dDesc->dwWidth) + x] = (UCHAR) (0xff & (pixel >> 8)) >> (8 - gBits);
			bList[(y * dDesc->dwWidth) + x] = (UCHAR) (0xff & pixel) >> (8 - bBits);

		}
	}

	colourList = Quantizer_Generate(rList, gList, bList, dDesc->dwWidth, dDesc->dwHeight, dDesc->lpSurface, dDesc->lPitch, &colourCount);

	for (loop=0 ; loop<colourCount ; loop++) {
		palette[loop].peRed = (UCHAR) (colourList[loop] >> 16);
		palette[loop].peGreen = (UCHAR) (colourList[loop] >> 8);
		palette[loop].peBlue = (UCHAR) (colourList[loop]);
		palette[loop].peFlags = 0;
	}
	for (loop=colourCount ; loop<256 ; loop++) palette[loop].peRed = palette[loop].peGreen = palette[loop].peBlue = palette[loop].peFlags = 0;

	r = DirectX_DirectDraw()->lpVtbl->CreatePalette(DirectX_DirectDraw(), DDPCAPS_8BIT|DDPCAPS_ALLOW256|DDPCAPS_INITIALIZE, palette, &pal, NULL);
	Error_DirectX(r, "CreatePalette");

	Mem_Free(list);
	Mem_Free(colourList);

	return pal;
}
