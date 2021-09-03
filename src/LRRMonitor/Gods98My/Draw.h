#pragma once

#include "../framework.h"
#include "Maths.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Function Typedefs
 **********************************************************************************/

#pragma region Function Typedefs

typedef void (__cdecl* DrawPixelFunc)(long x, long y, unsigned long value);

#pragma endregion

/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define DRAW_MAXLINES			200

#pragma endregion

/**********************************************************************************
 ******** Enumerations
 **********************************************************************************/

#pragma region Enums

#define DRAW_FLAG_INITIALISED	0x00000001

#define DRAW_VERTEXFLAGS			(D3DFVF_DIFFUSE|D3DFVF_XYZ)

enum
{
	DrawEffect_None,
	DrawEffect_XOR,
	DrawEffect_HalfTrans
};

#pragma endregion

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

typedef struct Draw_Rect
{
	/*00,10*/ AREA2D rect;
	/*10,4*/ float r;
	/*14,4*/ float g;
	/*18,4*/ float b;
	/*1c*/
} Draw_Rect, *lpDraw_Rect;
static_assert(sizeof(Draw_Rect) == 0x1c, "");


typedef struct DrawLineVertex
{
	/*00,c*/ VECTOR3D position;
	/*0c,4*/ unsigned long colour;
	/*10*/
} DrawLineVertex, *lpDrawLineVertex;
static_assert(sizeof(DrawLineVertex) == 0x10, "");


typedef struct Draw_Globs
{
	/*00,4*/ DrawPixelFunc drawPixelFunc;
	/*04,8*/ VECTOR2D clipStart;
	/*0c,8*/ VECTOR2D clipEnd;
	/*14,10*/ RECT lockRect;
	/*24,4*/ void* buffer;
	/*28,4*/ unsigned long pitch;
	/*2c,4*/ unsigned long bpp;
	/*30,4*/ unsigned long redMask;
	/*34,4*/ unsigned long greenMask;
	/*38,4*/ unsigned long blueMask;
	/*3c,4*/ unsigned long redBits;
	/*40,4*/ unsigned long greenBits;
	/*44,4*/ unsigned long blueBits;
	//DrawLineVertex vertexList[DRAW_MAXLINES * 2];
	/*48,4*/ unsigned long flags;
	/*4c*/
} Draw_Globs;
static_assert(sizeof(Draw_Globs) == 0x4c, "");

#pragma endregion

/**********************************************************************************
 ******** Globals
 **********************************************************************************/

#pragma region Globals

// <LegoRR.exe @005417e8>
extern Draw_Globs drawGlobs;

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

#define Draw_PixelList(p,c,r,g,b)					Draw_PixelListEx((p),(c),(r),(g),(b),DrawEffect_None)
#define Draw_LineList(f,t,c,r,g,b)					Draw_LineListEx((f),(t),(c),(r),(g),(b),DrawEffect_None)
#define Draw_WorldLineList(v,f,t,c,r,g,b,a)			Draw_WorldLineListEx((v),(f),(t),(c),(r),(g),(b),(a),DrawEffect_None)
#define Draw_RectList(a,c,r,g,b)					Draw_RectListEx((a),(c),(r),(g),(b),DrawEffect_None)

#define Draw_PixelListXOR(p,c,r,g,b)				Draw_PixelListEx((p),(c),(r),(g),(b),DrawEffect_XOR)
#define Draw_LineListXOR(f,t,c,r,g,b)				Draw_LineListEx((f),(t),(c),(r),(g),(b),DrawEffect_XOR)
	//#define Draw_WorldLineListXOR(v,f,t,c,r,g,b,a)		Draw_WorldLineListEx((v),(f),(t),(c),(r),(g),(b),(a),DrawEffect_XOR)
#define Draw_RectListXOR(a,c,r,g,b)					Draw_RectListEx((a),(c),(r),(g),(b),DrawEffect_XOR)

#define Draw_PixelListHalfTrans(p,c,r,g,b)			Draw_PixelListEx((p),(c),(r),(g),(b),DrawEffect_HalfTrans)
#define Draw_LineListHalfTrans(f,t,c,r,g,b)			Draw_LineListEx((f),(t),(c),(r),(g),(b),DrawEffect_HalfTrans)
//#define Draw_WorldLineListHalfTrans(v,f,t,c,r,g,b,a)	Draw_WorldLineListEx((v),(f),(t),(c),(r),(g),(b),(a),DrawEffect_HalfTrans)
#define Draw_RectListHalfTrans(a,c,r,g,b)			Draw_RectListEx((a),(c),(r),(g),(b),DrawEffect_HalfTrans)


// <LegoRR.exe @00486140>
void __cdecl Draw_Initialise(const AREA2D* window);

// <LegoRR.exe @00486160>
void __cdecl Draw_SetClipWindow(const AREA2D* window);

// <LegoRR.exe @00486270>
void __cdecl Draw_GetClipWindow(OUT AREA2D* window);

//void __cdecl Draw_PixelListEx(const VECTOR2D* pointList, unsigned long count, float r, float g, float b, unsigned long effect);

// <LegoRR.exe @004862b0>
void __cdecl Draw_LineListEx(const VECTOR2D* fromList, const VECTOR2D* toList, unsigned long count, float r, float g, float b, unsigned long effect);

//void __cdecl Draw_WorldLineListEx(Viewport* vp, const VECTOR3D* fromList, const VECTOR3D* toList, unsigned long count, float r, float g, float b, float a, unsigned long effect);

// <LegoRR.exe @00486350>
void __cdecl Draw_RectListEx(const AREA2D* rectList, unsigned long count, float r, float g, float b, unsigned long effect);

// <LegoRR.exe @004864d0>
void __cdecl Draw_RectList2Ex(const Draw_Rect* rectList, unsigned long count, unsigned long effect);

// <LegoRR.exe @00486650>
void __cdecl Draw_DotCircle(const VECTOR2D* pos, unsigned long radius, unsigned long dots, float r, float g, float b, unsigned long effect);

// <LegoRR.exe @00486790>
unsigned long __cdecl Draw_GetColour(float r, float g, float b);

// <LegoRR.exe @00486810>
BOOL __cdecl Draw_LockSurface(IDirectDrawSurface4* surf, unsigned long effect);

// <LegoRR.exe @00486910>
void __cdecl Draw_UnlockSurface(IDirectDrawSurface4* surf);

// <LegoRR.exe @00486950>
BOOL __cdecl Draw_SetDrawPixelFunc(unsigned long effect);

// <LegoRR.exe @004869e0>
void __cdecl Draw_LineActual(long x1, long y1, long x2, long y2, unsigned long colour);

// <LegoRR.exe @00486b40>
void __cdecl Draw_Pixel8(long x, long y, unsigned long value);

// <LegoRR.exe @00486b60>
void __cdecl Draw_Pixel16(long x, long y, unsigned long value);

// <LegoRR.exe @00486b90>
void __cdecl Draw_Pixel16XOR(long x, long y, unsigned long value);

// <LegoRR.exe @00486bc0>
void __cdecl Draw_Pixel16HalfTrans(long x, long y, unsigned long value);

// <LegoRR.exe @00486c60>
void __cdecl Draw_Pixel24(long x, long y, unsigned long value);

// <LegoRR.exe @00486c90>
void __cdecl Draw_Pixel32(long x, long y, unsigned long value);

#pragma endregion

}
