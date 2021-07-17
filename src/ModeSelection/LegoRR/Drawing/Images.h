// Images.h : 
//

#pragma once

#include "../Common.h"
#include "DirectDraw.h"
#include "../Helpers/Pool.h"


namespace lego {
namespace image {

#pragma region Types

struct ImageBMP
{
	/*00,4*/ IDirectDrawSurface4* ddSurface;
	/*04,8*/ Size2I dimensions;
	/*0c,4*/ unsigned int firstColor24;
	/*10,4*/ unsigned int lastColor24;
	/*14,4*/ unsigned int firstColorNative;
	/*18,4*/ unsigned int flags; // 2 is font?
	///*1c,4*/ pool::PoolItem<ImageBMP>* pool_m_next;
	/*20*/
};

extern pool::ReservedPool<ImageBMP, 32> Pool;

#pragma endregion


#pragma region Globals

namespace globals {
} /* namespace globals */

#pragma endregion


#pragma region Functions

/*// <LegoRR.exe @0047cbb0>
int __cdecl Image_FUN_0047cbb0(int* param_1, char* param_2);

// <LegoRR.exe @0047d2c0>
void __cdecl FUN_0047d2c0(unsigned int param_1, int* param_2);*/

// <LegoRR.exe @0047d590>
unsigned int __cdecl packNativeRGB(IDirectDrawSurface4* ddSurface, unsigned int rgbColor);

// <LegoRR.exe @0047d6b0>
int __cdecl countBits2(unsigned int value);

// <LegoRR.exe @0047d750>
BOOL __cdecl Image_FUN_0047d750(IDirectDrawSurface4* ddSurface, DDSURFACEDESC2* surfaceDesc);

// <LegoRR.exe @0047d7e0>
BOOL __cdecl Image_FUN_0047d7e0(int param_1, DDSURFACEDESC2* surfaceDesc);

// <LegoRR.exe @0047d9c0>
int __cdecl countBits(unsigned int value);

// <LegoRR.exe @0047d9e0>
int __cdecl firstBit(unsigned int value);

// <LegoRR.exe @0047da00>
void __cdecl Image_ReorderPixelsBPP(DDSURFACEDESC2* surfaceDesc);

// <LegoRR.exe @0047dac0>
BOOL __cdecl Image_FUN_0047dac0(int param_1, DDSURFACEDESC2* surfaceDesc);

// <LegoRR.exe @0047dc90>
ImageBMP* __cdecl Image_LoadBMP(char* filename, unsigned int unused_2, unsigned int unused_3);

// <LegoRR.exe @0047de50>
unsigned int __cdecl packRGB(unsigned char red, unsigned char green, unsigned char blue);

// <LegoRR.exe @0047de80>
void __cdecl Image_SetFirstColorAsKey(ImageBMP* image);

// <LegoRR.exe @0047deb0>
void __cdecl Image_unkFogFromFloat__0047deb0(ImageBMP* image, float red_low, float green_low, float blue_low, float red_high, float green_high, float blue_high);

// <LegoRR.exe @0047df70>
void __cdecl Image_Blt__0047df70(ImageBMP* bitmap, float* param_2, float* param_3, float* param_4);

// <LegoRR.exe @0047e120>
void* __cdecl Image_Lock(ImageBMP* image, unsigned int* out_length, unsigned int* out_bitsPerPixel);

// <LegoRR.exe @0047e190>
void __cdecl Image_Unlock(ImageBMP* image);

// <LegoRR.exe @0047e1b0>
unsigned int __cdecl Image_GetLastColor24(ImageBMP* image);

// <LegoRR.exe @0047e210>
unsigned int __cdecl Image_GetUpperBitMask(ImageBMP* image);

// <LegoRR.exe @0047e260>
BOOL __cdecl Image_FUN_0047e260(ImageBMP* image, int param_2, int param_3);


// <LegoRR.exe @0047e3f0>
void __cdecl Image_Cleanup_FUN_0047e3f0(void);

// <LegoRR.exe @0047e450>
unsigned int __cdecl unpackNativeRGB(IDirectDrawSurface4* ddSurface, unsigned int rgbColor);

// <LegoRR.exe @0047e590>
void __cdecl unpackRGB(unsigned int rgbColor, unsigned char* out_red, unsigned char* out_green, unsigned char* out_blue);

// <LegoRR.exe @0047e5c0>
void __cdecl Image_CreateCapture(ImageBMP* param_1, int captureWidth, int captureHeight);

#pragma endregion


} /* namespace image */
} /* namespace lego */
