
#ifndef _GODS98_DRAW_H
#define _GODS98_DRAW_H

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

typedef struct Draw_Globs {

	VOID (*drawPixelFunc)(SLONG x, SLONG y, ULONG value);
	VECTOR2D clipStart, clipEnd;
	LPVOID buffer;
	ULONG pitch, bpp;

	ULONG redMask, greenMask, blueMask;
	ULONG redBits, greenBits, blueBits;

	ULONG flags;

} Draw_Globs, *lpDraw_Globs;

#define Draw_PixelList(p,c,r,g,b)					Draw_PixelListEx((p),(c),(r),(g),(b),DrawEffect_None)
#define Draw_LineList(f,t,c,r,g,b)					Draw_LineListEx((f),(t),(c),(r),(g),(b),DrawEffect_None)
#define Draw_WorldLineList(v,f,t,c,r,g,b)			Draw_WorldLineListEx((v),(f),(t),(c),(r),(g),(b),DrawEffect_None)
#define Draw_RectList(a,c,r,g,b)					Draw_RectListEx((a),(c),(r),(g),(b),DrawEffect_None)

#define Draw_PixelListXOR(p,c,r,g,b)				Draw_PixelListEx((p),(c),(r),(g),(b),DrawEffect_XOR)
#define Draw_LineListXOR(f,t,c,r,g,b)				Draw_LineListEx((f),(t),(c),(r),(g),(b),DrawEffect_XOR)
#define Draw_WorldLineListXOR(v,f,t,c,r,g,b)		Draw_WorldLineListEx((v),(f),(t),(c),(r),(g),(b),DrawEffect_XOR)
#define Draw_RectListXOR(a,c,r,g,b)					Draw_RectListEx((a),(c),(r),(g),(b),DrawEffect_XOR)

#define Draw_PixelListHalfTrans(p,c,r,g,b)			Draw_PixelListEx((p),(c),(r),(g),(b),DrawEffect_HalfTrans)
#define Draw_LineListHalfTrans(f,t,c,r,g,b)			Draw_LineListEx((f),(t),(c),(r),(g),(b),DrawEffect_HalfTrans)
#define Draw_WorldLineListHalfTrans(v,f,t,c,r,g,b)	Draw_WorldLineListEx((v),(f),(t),(c),(r),(g),(b),DrawEffect_HalfTrans)
#define Draw_RectListHalfTrans(a,c,r,g,b)			Draw_RectListEx((a),(c),(r),(g),(b),DrawEffect_HalfTrans)

VOID Draw_Initialise(LPAREA2D window);
VOID Draw_SetClipWindow(LPAREA2D window);
VOID Draw_PixelListEx(LPVECTOR2D pointList, ULONG count, REAL r, REAL g, REAL b, ULONG effect);
VOID Draw_LineListEx(LPVECTOR2D fromList, LPVECTOR2D toList, ULONG count, REAL r, REAL g, REAL b, ULONG effect);
VOID Draw_WorldLineListEx(lpViewport vp, LPVECTOR3D fromList, LPVECTOR3D toList, ULONG count, REAL r, REAL g, REAL b, ULONG effect);
VOID Draw_RectListEx(LPAREA2D rectList, ULONG count, REAL r, REAL g, REAL b, ULONG effect);
VOID Draw_DotCircle(LPVECTOR2D pos, ULONG radius, ULONG dots, REAL r, REAL g, REAL b, ULONG effect);


#endif // !_GODS98_DRAW_H
