// SurfaceLock.h : 
//

#pragma once

#include "../Common.h"


namespace lego {
namespace draw {

#pragma region Types

typedef void(__cdecl* SetPixelBPPFunction)(int x, int y, unsigned int color);

#pragma endregion


#pragma region Globals

namespace globals {

	// <LegoRR.exe @005417e8>
	extern SetPixelBPPFunction g_SurfaceLock_SetPixelFunction;
	// <LegoRR.exe @005417ec>
	extern Rect2F g_SurfaceLock_Translation;
	/*extern unsigned int DAT_005417ec;
	// <LegoRR.exe @005417f0>
	extern unsigned int DAT_005417f0;
	// <LegoRR.exe @005417f4>
	extern float FLOAT_005417f4;
	// <LegoRR.exe @005417f8>
	extern float FLOAT_005417f8;*/

	// <LegoRR.exe @0054180c>
	extern unsigned char* g_SurfaceLock_Pixels;
	// <LegoRR.exe @00541810>
	extern int g_SurfaceLock_Stride;
	// <LegoRR.exe @00541814>
	extern int g_SurfaceLock_BPP;
	// <LegoRR.exe @00541818>
	extern unsigned int g_SurfaceLock_RBitMask;
	// <LegoRR.exe @0054181c>
	extern unsigned int g_SurfaceLock_GBitMask;
	// <LegoRR.exe @00541820>
	extern unsigned int g_SurfaceLock_BBitMask;
	// <LegoRR.exe @00541824>
	extern int g_SurfaceLock_RBitCount;
	// <LegoRR.exe @00541828>
	extern int g_SurfaceLock_GBitCount;
	// <LegoRR.exe @0054182c>
	extern int g_SurfaceLock_BBitCount;
	// <LegoRR.exe @00541830>
	extern unsigned int FLAGS_00541830;

} /* namespace globals */

#pragma endregion


#pragma region Functions

// <LegoRR.exe @00486140>
void __cdecl Draw_SurfaceLockRect(const Rect2F* surfaceRect);

// <LegoRR.exe @00486160>
void __cdecl Draw_SurfaceLock_Translate(const Rect2F* translation);

// <LegoRR.exe @00486270>
void __cdecl Draw_SurfaceLock_GetTranslation(Rect2F* translation);

// <LegoRR.exe @004862b0>
void __cdecl Draw_SurfaceLock_FUN_004862b0(int param_1, float* param_2, int param_3, float param_4, float param_5, float param_6, int param_7);

// <LegoRR.exe @00486350>
float __cdecl Draw_SurfaceLock_FUN_00486350(float* param_1, int param_2, unsigned int param_3, unsigned int param_4, int param_5, float* param_6);

// <LegoRR.exe @004864d0>
void __cdecl Draw_SurfaceLock_FUN_004864d0(int param_1, int param_2, int param_3);

// <LegoRR.exe @00486650>
float __cdecl Draw_SurfaceLock_FUN_00486650(float* param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4, unsigned int param_5, unsigned int param_6, int param_7);

// <LegoRR.exe @00486790>
unsigned int __cdecl Draw_SurfaceFloatToRGB(float red, float green, float blue);

// <LegoRR.exe @00486810>
BOOL __cdecl Draw_SurfaceLock(IDirectDrawSurface4* ddSurface, int mode);

// <LegoRR.exe @00486910>
void __cdecl Draw_SurfaceUnlock(IDirectDrawSurface4* ddSurface);

// <LegoRR.exe @00486950>
BOOL __cdecl Draw_SurfaceSetPixelFunction(int mode);

// <LegoRR.exe @004869e0>
void __cdecl Draw_SurfaceLock_FUN_004869e0(unsigned int param_1, unsigned int param_2, int x, int y, unsigned int nativeColor);

// <LegoRR.exe @00486b40>
void __cdecl Draw_SetPixel8(int x, int y, unsigned int nativeColor);
// <LegoRR.exe @00486b60>
void __cdecl Draw_SetPixel16_Mode0(int x, int y, unsigned int nativeColor);
// <LegoRR.exe @00486b90>
void __cdecl Draw_SetPixel16_Mode1(int x, int y, unsigned int nativeColor);
// <LegoRR.exe @00486bc0>
void __cdecl Draw_SetPixel16_Mode2(int x, int y, unsigned int nativeColor);
// <LegoRR.exe @00486c60>
void __cdecl Draw_SetPixel24(int x, int y, unsigned int nativeColor);
// <LegoRR.exe @00486c90>
void __cdecl Draw_SetPixel32(int x, int y, unsigned int nativeColor);

#pragma endregion


#pragma region Custom Functions

/// CUSTOM:
void __cdecl Draw_SetSurfacePixel(int x, int y, unsigned int color);

#pragma endregion


} /* namespace draw */
} /* namespace lego */
