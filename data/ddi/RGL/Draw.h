
#ifndef _RGL_DRAW_H
#define _RGL_DRAW_H

#include "Maths.h"

#define DRAW_FLAG_ADDITIVE			0x00000001
#define DRAW_FLAG_COLOURKEYED		0x00000002
#define DRAW_FLAG_SUBTRACTIVE		0x00000004

struct DrawCoord {

	VECTOR3D position;
	ULONG colour;
};

struct DrawScreenCoord {

	VECTOR4D position;
	ULONG colour;
	VECTOR2D uv;
};

struct DrawPrimitiveCoord {

	struct DrawCoord coord;
	REAL size, angle;
};

struct DrawTriangleCoord {
	VECTOR3D	position[3];
	VECTOR2D	UVlist[3];
	ULONG		colour[3];
};

struct DrawScreenTriangleCoord {
	VECTOR2D	position[3];
	VECTOR2D	UVlist[3];
	COLOUR		colour[3];

	LPVOID		texture;
	ULONG		flags;
};




typedef struct DrawCoord				DrawCoord, *lpDrawCoord;
typedef struct DrawScreenCoord			DrawScreenCoord, *lpDrawScreenCoord;
typedef struct DrawPrimitiveCoord		DrawPrimitiveCoord, *lpDrawPrimitiveCoord;
typedef struct DrawTriangleCoord		DrawTriangleCoord, *lpDrawTriangleCoord;
typedef struct DrawScreenTriangleCoord	DrawScreenTriangleCoord, *lpDrawScreenTriangleCoord;

// Auto Prototypes
extern unsigned __int64 __stdcall Int64ShllMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern __int64 __stdcall Int64ShraMod32(__int64 Value,unsigned long ShiftCount);
extern unsigned __int64 __stdcall Int64ShrlMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern void *__cdecl GetFiberData(void );
extern void *__cdecl GetCurrentFiber(void );
extern void __cdecl Draw_LineList(struct Viewport *vp,struct Frame *frame,struct Frame *camera,struct DrawCoord *coordList,unsigned long coordCount,unsigned short *indexList,unsigned long indexCount);
extern VOID __cdecl Draw_WorldPrimitiveList(lpViewport vp, lpFrame camera, lpDrawPrimitiveCoord primList, ULONG primCount, lpTexture texture, ULONG flags);
extern VOID __cdecl Draw_WorldPrimitiveListUV(lpViewport vp, lpFrame camera, lpDrawPrimitiveCoord primList, ULONG primCount, lpTexture texture, VECTOR2D uvList[4], ULONG flags);
extern VOID __cdecl Draw_WorldLineList(lpViewport vp, lpFrame camera, lpDrawCoord coordList, ULONG coordCount, LPUWORD indexList, ULONG indexCount);
extern VOID __cdecl Draw_WorldPrimitiveTriangleListUV(lpViewport vp, lpFrame camera, lpDrawTriangleCoord primList, ULONG primCount, lpTexture texture, ULONG flags);

extern VOID __cdecl Draw_ScreenOverlayPrimitive(lpDrawScreenTriangleCoord coord);
extern VOID __cdecl Draw_ScreenOverlayPrimitiveList(lpDrawScreenTriangleCoord coord, ULONG numPrims);

// Auto Prototypes

#endif // !_RGL_DRAW_H
