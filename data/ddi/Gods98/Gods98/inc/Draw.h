
#ifndef _GODS98_DRAW_H
#define _GODS98_DRAW_H

#include "Maths.h"

#define DRAW_MAXLINES			200
#define DRAW_FLAG_INITIALISED	0x00000001

enum {

	DrawEffect_None,
	DrawEffect_XOR,
	DrawEffect_HalfTrans

};

typedef struct Draw_Rect {

	AREA2D rect;
	REAL r, g, b;

} Draw_Rect, *lpDraw_Rect;

#ifdef _GODS98COMPILE

#define DRAW_VERTEXFLAGS			(D3DFVF_DIFFUSE|D3DFVF_XYZ)

typedef struct DrawLineVertex {

	VECTOR3D position;
	ULONG colour;

} DrawLineVertex, *lpDrawLineVertex;

typedef struct Draw_Globs {

	VOID (*drawPixelFunc)(SLONG x, SLONG y, ULONG value);
	VECTOR2D clipStart, clipEnd;
	RECT lockRect;
	LPVOID buffer;
	ULONG pitch, bpp;

	ULONG redMask, greenMask, blueMask;
	ULONG redBits, greenBits, blueBits;

	struct DrawLineVertex vertexList[DRAW_MAXLINES * 2];

	ULONG flags;

} Draw_Globs, *lpDraw_Globs;

#endif // _GODS98COMPILE

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

#ifndef _GENPROTFILE
#include "..\Src\Draw.prot"
#endif // !_GENPROTFILE

#endif // !_GODS98_DRAW_H
