// Images.cpp : 
//

#include "Images.h"


#pragma region Defines

#define s_Dev_SourceSafe__Images_c "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Images.c"

#pragma endregion


using namespace lego;
using namespace lego::image;


#pragma region Functions

// <LegoRR.exe @0047d590>
unsigned int __cdecl lego::image::packNativeRGB(IDirectDrawSurface4* ddSurface, unsigned int rgbColor)
{
	PALETTEENTRY palEntries[256];

	unsigned int r = rgbColor & 0xff;
	unsigned int g = (rgbColor >> 8) & 0xff;
	unsigned int b = (rgbColor >> 16) & 0xff;
	/*local_428 = rgbColor >> 0x10 & 0xff;
	uVar6 = rgbColor >> 8 & 0xff;
	pIVar1 = param_1->lpVtbl;*/
	//unsigned char r, g, b;
	//unpackRGB(rgbColor, &r, &g, &b);

	DDPIXELFORMAT pixFmt;
	std::memset(&pixFmt, 0, sizeof(pixFmt));
	pixFmt.dwSize = sizeof(pixFmt);

	ddSurface->GetPixelFormat(&pixFmt);
	//(*pIVar1->GetPixelFormat)(param_1, &pixFmt);
	if (pixFmt.dwFlags & DDPF_RGB /*0x40*/) {
		int rbits = countBits2(pixFmt.dwRBitMask);
		int gbits = countBits2(pixFmt.dwGBitMask);
		int bbits = countBits2(pixFmt.dwBBitMask);
		return	((r >> (8U - (rbits & 0x1f))) << ((bbits & 0x1f) + (gbits & 0x1f))) |
				((g >> (8U - (gbits & 0x1f))) <<  (bbits & 0x1f)) |
				 (b >> (8U - (bbits & 0x1f)));
	}
	else {
		IDirectDrawPalette* ddPal;
		ddSurface->GetPalette(&ddPal);
		ddPal->GetEntries(0, 0, 256, palEntries);
		for (int i = 0; i < 256; i++) {
			if (palEntries[i].peRed == r && palEntries[i].peGreen == r && palEntries[i].peBlue == r)
				return i;
		}
		return 256;
	}
}

// <LegoRR.exe @0047d6b0>
int __cdecl lego::image::countBits2(unsigned int value)
{
	int count = 0;
	while (value != 0) {
		value &= value - 1;
		count++;
	}
	return count;
}

// <LegoRR.exe @0047d9c0>
int __cdecl lego::image::countBits(unsigned int value)
{
	int count = 0;
	for (int k = 0; k < 32; k++) {
		if ((value & 0x1) << k)
			count++;
	}
	return count;
}

// <LegoRR.exe @0047d9e0>
int __cdecl lego::image::firstBit(unsigned int value)
{
	for (int k = 0; k < 32; k++) {
		if ((value & 0x1) << k)
			return k;
	}
	return -1;
}


// <LegoRR.exe @0047de50>
unsigned int __cdecl lego::image::packRGB(unsigned char red, unsigned char green, unsigned char blue)
{
	return ((unsigned int)red | ((unsigned int)green << 8) | ((unsigned int)blue << 16));
}

// <LegoRR.exe @0047e450>
unsigned int __cdecl lego::image::unpackNativeRGB(IDirectDrawSurface4* ddSurface, unsigned int rgbColor)
{
	unsigned int value = 0;

	DDSURFACEDESC2 surf;
	std::memset(&surf, 0, sizeof(DDSURFACEDESC2));
	surf.dwSize = sizeof(DDSURFACEDESC2);

	unsigned char out_red, out_green, out_blue;
	unpackRGB(rgbColor, &out_red, &out_green, &out_blue);

	if (ddSurface->Lock(nullptr, &surf, DDLOCK_WAIT /*0x1*/, nullptr) == 0) {
		DWORD dwRBitMask = surf.ddpfPixelFormat.dwRBitMask;
		DWORD dwGBitMask = surf.ddpfPixelFormat.dwGBitMask;
		DWORD dwBBitMask = surf.ddpfPixelFormat.dwBBitMask;
		value =
			((out_green & 0xff) >> (8U - countBits(dwGBitMask))) << firstBit(dwGBitMask) |
			((out_blue  & 0xff) >> (8U - countBits(dwRBitMask))) << firstBit(dwRBitMask) |
			((out_red   & 0xff) >> (8U - countBits(dwBBitMask))) << firstBit(dwBBitMask);
		
		if (surf.ddpfPixelFormat.dwRGBBitCount < 32) {
			unsigned int mask = (1 << (surf.ddpfPixelFormat.dwRGBBitCount & 0x1f)) - 1U;
			value &= mask;
		}

		ddSurface->Unlock(nullptr);
	}
	return value;
}

// <LegoRR.exe @0047e590>
void __cdecl lego::image::unpackRGB(unsigned int rgbColor, unsigned char* out_red, unsigned char* out_green, unsigned char* out_blue)
{
	if (out_red)
		*out_red = (unsigned char)rgbColor;

	if (out_green)
		*out_green = (unsigned char)(rgbColor >> 8);

	if (out_blue)
		*out_blue = (unsigned char)(rgbColor >> 16);
}

#pragma endregion
