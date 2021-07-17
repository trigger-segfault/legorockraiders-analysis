// SurfaceLock.cpp : 
//

#include "SurfaceLock.h"
#include "DirectDraw.h"
#include "Images.h"
#include "../Main/Main.h"


namespace lego {
namespace draw {
namespace globals {
	/*
	// define these because I'm too lazy to deal with linker errors
	static IID IID_IDirect3D3 = { 0xbb223240, 0xe72b, 0x11d0, 0xa9, 0xb4, 0x00, 0xaa, 0x00, 0xc0, 0x99, 0x3e };

	static IID IID_IDirectDraw4 = { 0x9c59509a, 0x39bd, 0x11d1, 0x8c, 0x4a, 0x00, 0xc0, 0x4f, 0xd9, 0x30, 0xc5 };
*/

	// <LegoRR.exe @005417e8>
	SetPixelBPPFunction g_SurfaceLock_SetPixelFunction;
	// <LegoRR.exe @005417ec>
	Rect2F g_SurfaceLock_Translation;
	/*unsigned int DAT_005417ec;
	// <LegoRR.exe @005417f0>
	unsigned int DAT_005417f0;
	// <LegoRR.exe @005417f4>
	float FLOAT_005417f4;
	// <LegoRR.exe @005417f8>
	float FLOAT_005417f8;*/

	// <LegoRR.exe @0054180c>
	unsigned char* g_SurfaceLock_Pixels;
	// <LegoRR.exe @00541810>
	int g_SurfaceLock_Stride;
	// <LegoRR.exe @00541814>
	int g_SurfaceLock_BPP;
	// <LegoRR.exe @00541818>
	unsigned int g_SurfaceLock_RBitMask;
	// <LegoRR.exe @0054181c>
	unsigned int g_SurfaceLock_GBitMask;
	// <LegoRR.exe @00541820>
	unsigned int g_SurfaceLock_BBitMask;
	// <LegoRR.exe @00541824>
	int g_SurfaceLock_RBitCount;
	// <LegoRR.exe @00541828>
	int g_SurfaceLock_GBitCount;
	// <LegoRR.exe @0054182c>
	int g_SurfaceLock_BBitCount;
	// <LegoRR.exe @00541830>
	unsigned int FLAGS_00541830;

} /* namespace globals */
} /* namespace draw */
} /* namespace lego */




using namespace lego;
using namespace lego::draw;



// <LegoRR.exe @00486140>
void __cdecl lego::draw::Draw_SurfaceLockRect(const Rect2F* surfaceRect)
{
	globals::FLAGS_00541830 |= 1;
	Draw_SurfaceLock_Translate(surfaceRect);
}

// <LegoRR.exe @00486160>
void __cdecl lego::draw::Draw_SurfaceLock_Translate(const Rect2F* translation)
{
	globals::g_SurfaceLock_Translation.x = 0.0;
	globals::g_SurfaceLock_Translation.y = 0.0;
	if (translation) {
		if (translation->x > 0.0f)
			globals::g_SurfaceLock_Translation.x = translation->x;

		if (translation->y > 0.0f)
			globals::g_SurfaceLock_Translation.y = translation->y;
	}

	DDSURFACEDESC2 surf;
	memset(&surf, 0, sizeof(surf));
	surf.dwSize = sizeof(surf);

	if (globals::g_IDirectDrawSurface4_DrawTarget->GetSurfaceDesc(&surf) == 0) {
		globals::g_SurfaceLock_Translation.width = (float)(unsigned long long)surf.dwWidth;
		globals::g_SurfaceLock_Translation.height = (float)(unsigned long long)surf.dwHeight;
		if (translation) {
			float x2 = translation->width + translation->x;
			if (x2 < globals::g_SurfaceLock_Translation.width)
				globals::g_SurfaceLock_Translation.width = x2;

			float y2 = translation->height + translation->y;
			if (y2 < globals::g_SurfaceLock_Translation.height)
				globals::g_SurfaceLock_Translation.height = y2;
		}
	}
}


// <LegoRR.exe @00486270>
void __cdecl lego::draw::Draw_SurfaceLock_GetTranslation(Rect2F* translation)
{
	translation->x      = globals::g_SurfaceLock_Translation.x;
	translation->y      = globals::g_SurfaceLock_Translation.y;
	translation->width  = globals::g_SurfaceLock_Translation.width  - globals::g_SurfaceLock_Translation.x;
	translation->height = globals::g_SurfaceLock_Translation.height - globals::g_SurfaceLock_Translation.y;
}



// <LegoRR.exe @00486790>
unsigned int __cdecl lego::draw::Draw_SurfaceFloatToRGB(float red, float green, float blue)
{
	if (globals::g_SurfaceLock_BPP != 8) {
		unsigned int r = (unsigned int)(long long)(red   * 255.0);
		unsigned int g = (unsigned int)(long long)(green * 255.0);
		unsigned int b = (unsigned int)(long long)(blue  * 255.0);
		unsigned char rbits = (unsigned char)globals::g_SurfaceLock_RBitCount;
		unsigned char gbits = (unsigned char)globals::g_SurfaceLock_GBitCount;
		unsigned char bbits = (unsigned char)globals::g_SurfaceLock_BBitCount;
		return  (r >> (8U - rbits & 0x1f)) << (gbits + bbits & 0x1f) |
				(g >> (8U - gbits & 0x1f)) << (bbits & 0x1f) |
				(b >> (8U - bbits & 0x1f));
	}
	return 0;
}


// <LegoRR.exe @00486810>
BOOL __cdecl lego::draw::Draw_SurfaceLock(IDirectDrawSurface4* ddSurface, int mode)
{
	DDSURFACEDESC2 surf;
	memset(&surf, 0, sizeof(surf));
	surf.dwSize = sizeof(surf);

	if (ddSurface->Lock(nullptr, &surf, DDLOCK_WAIT /*0x1*/, nullptr) == 0) {
		globals::g_SurfaceLock_Pixels	= (unsigned char*)surf.lpSurface;

		globals::g_SurfaceLock_Stride	= surf.dwLinearSize;
		globals::g_SurfaceLock_RBitMask = surf.ddpfPixelFormat.dwRBitMask;
		globals::g_SurfaceLock_GBitMask = surf.ddpfPixelFormat.dwGBitMask;
		globals::g_SurfaceLock_BBitMask = surf.ddpfPixelFormat.dwBBitMask;
		globals::g_SurfaceLock_BPP		= surf.ddpfPixelFormat.dwRGBBitCount;

		globals::g_SurfaceLock_RBitCount = 0;
		globals::g_SurfaceLock_GBitCount = 0;
		globals::g_SurfaceLock_BBitCount = 0;
		for (unsigned int i = 0; i < surf.ddpfPixelFormat.dwRGBBitCount; i++) {
			unsigned int bit = 1 << i;

			if (bit & surf.ddpfPixelFormat.dwRBitMask)
				globals::g_SurfaceLock_RBitCount++;

			if (bit & surf.ddpfPixelFormat.dwGBitMask)
				globals::g_SurfaceLock_GBitCount++;

			if (bit & surf.ddpfPixelFormat.dwBBitMask)
				globals::g_SurfaceLock_BBitCount++;
		}

		if (Draw_SurfaceSetPixelFunction(mode))
			return TRUE;

		Draw_SurfaceUnlock(ddSurface);
	}
	return FALSE;
}

// <LegoRR.exe @00486910>
void __cdecl lego::draw::Draw_SurfaceUnlock(IDirectDrawSurface4* ddSurface)
{
	ddSurface->Unlock(nullptr);
	globals::g_SurfaceLock_SetPixelFunction = nullptr;
	globals::g_SurfaceLock_Pixels = nullptr;
	globals::g_SurfaceLock_Stride = 0;
	globals::g_SurfaceLock_BPP = 0;
	globals::g_SurfaceLock_RBitMask = 0;
	globals::g_SurfaceLock_GBitMask = 0;
	globals::g_SurfaceLock_BBitMask = 0;
}

// <LegoRR.exe @00486950>
BOOL __cdecl lego::draw::Draw_SurfaceSetPixelFunction(int mode)
{
	switch (globals::g_SurfaceLock_BPP) {
	case 8:
		globals::g_SurfaceLock_SetPixelFunction = Draw_SetPixel8;
		return TRUE;
	case 16: {
		switch (mode) {
		case 1:
			globals::g_SurfaceLock_SetPixelFunction = Draw_SetPixel16_Mode1;
			return TRUE;
		case 2:
			globals::g_SurfaceLock_SetPixelFunction = Draw_SetPixel16_Mode2;
			return TRUE;
		default:
			globals::g_SurfaceLock_SetPixelFunction = Draw_SetPixel16_Mode0;
			return TRUE;
		}
	}
	case 24:
		globals::g_SurfaceLock_SetPixelFunction = Draw_SetPixel24;
		return TRUE;
	case 32:
		globals::g_SurfaceLock_SetPixelFunction = Draw_SetPixel32;
		return TRUE;
	default:
		return FALSE;
	}
}



// <LegoRR.exe @00486b40>
void __cdecl lego::draw::Draw_SetPixel8(int x, int y, unsigned int color)
{
	globals::g_SurfaceLock_Pixels[x + y * globals::g_SurfaceLock_Stride] = (unsigned char)color;
}

// <LegoRR.exe @00486b60>
void __cdecl lego::draw::Draw_SetPixel16_Mode0(int x, int y, unsigned int color)
{
	*(unsigned short*)(globals::g_SurfaceLock_Pixels + (x * 2 + y * globals::g_SurfaceLock_Stride)) = (unsigned short)color;
}

// <LegoRR.exe @00486b90>
void __cdecl lego::draw::Draw_SetPixel16_Mode1(int x, int y, unsigned int color)
{
	*(unsigned short*)(globals::g_SurfaceLock_Pixels + (x * 2 + y * globals::g_SurfaceLock_Stride)) ^= (unsigned short)color;
	//*(ushort*)(globals::g_SurfaceLock_Pixels + x * 2 + y * globals::g_SurfaceLock_Stride) =
	//	*(ushort*)(globals::g_SurfaceLock_Pixels + x * 2 + y * globals::g_SurfaceLock_Stride) ^
	//	(ushort)color;
}

// <LegoRR.exe @00486bc0>
void __cdecl lego::draw::Draw_SetPixel16_Mode2(int x, int y, unsigned int color)
{
	unsigned short uPixel = *(unsigned short*)(globals::g_SurfaceLock_Pixels + (x * 2 + y * globals::g_SurfaceLock_Stride));
	unsigned short uColor = (unsigned short)color;
	*(unsigned short*)(globals::g_SurfaceLock_Pixels + (x * 2 + y * globals::g_SurfaceLock_Stride)) =
		(((unsigned short)globals::g_SurfaceLock_GBitMask & uPixel) >> 1 & 0x7fe0) +
		(((unsigned short)globals::g_SurfaceLock_GBitMask & uColor) >> 1 & 0x7fe0) &
		(unsigned short)globals::g_SurfaceLock_GBitMask |
		(((unsigned short)globals::g_SurfaceLock_BBitMask & uColor) >> 1) +
		(((unsigned short)globals::g_SurfaceLock_BBitMask & uPixel) >> 1) &
		(unsigned short)globals::g_SurfaceLock_BBitMask |
		(uColor >> 1 & 0x7800) +
		(uPixel >> 1 & 0x7800) &
		(unsigned short)globals::g_SurfaceLock_RBitMask;
	/*ushort uVar1;
	ushort uVar2;

	uVar1 = *(ushort*)(globals::g_SurfaceLock_Pixels + x * 2 + y * globals::g_SurfaceLock_Stride);
	uVar2 = (ushort)color;
	*(ushort*)(globals::g_SurfaceLock_Pixels + x * 2 + y * globals::g_SurfaceLock_Stride) =
		(((ushort)globals::g_SurfaceLock_GBitMask & uVar1) >> 1 & 0x7fe0) +
		(((ushort)globals::g_SurfaceLock_GBitMask & uVar2) >> 1 & 0x7fe0) &
		(ushort)globals::g_SurfaceLock_GBitMask |
		((uVar2 & (ushort)globals::g_SurfaceLock_BBitMask) >> 1) +
		((uVar1 & (ushort)globals::g_SurfaceLock_BBitMask) >> 1) &
		(ushort)globals::g_SurfaceLock_BBitMask |
		(uVar2 >> 1 & 0x7800) + (uVar1 >> 1 & 0x7800) & (ushort)globals::g_SurfaceLock_RBitMask;
	return;*/
}

// <LegoRR.exe @00486c60>
void __cdecl lego::draw::Draw_SetPixel24(int x, int y, unsigned int color)
{
	*(unsigned int*)(globals::g_SurfaceLock_Pixels + (x * 3 + y * globals::g_SurfaceLock_Stride)) = color | 0xff000000;// << 8 |
	//	(*(unsigned int*)(globals::g_SurfaceLock_Pixels + (x * 3 + y * globals::g_SurfaceLock_Stride)) & 0xff);
	//*(unsigned int*)(globals::g_SurfaceLock_Pixels + (x * 3 + y * globals::g_SurfaceLock_Stride)) = color << 8 |
	//	(*(unsigned int*)(globals::g_SurfaceLock_Pixels + (x * 3 + y * globals::g_SurfaceLock_Stride)) & 0xff);

	//*(uint*)(globals::g_SurfaceLock_Pixels + x * 3 + y * globals::g_SurfaceLock_Stride) =
	//	color << 8 |
	//	*(uint*)(globals::g_SurfaceLock_Pixels + x * 3 + y * globals::g_SurfaceLock_Stride) & 0xff;
}

// <LegoRR.exe @00486c90>
void __cdecl lego::draw::Draw_SetPixel32(int x, int y, unsigned int color)
{
	*(unsigned int*)(globals::g_SurfaceLock_Pixels + x * 4 + y * globals::g_SurfaceLock_Stride) = color;
}





/// CUSTOM:
void __cdecl lego::draw::Draw_SetSurfacePixel(int x, int y, unsigned int color)
{
	globals::g_SurfaceLock_SetPixelFunction(x, y, color);
}
