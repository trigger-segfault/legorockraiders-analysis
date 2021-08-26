
#include <ddraw.h>
#include <d3drm.h>			// For Viewports.h

#include "..\Inc\Standard.h"
#include "..\Inc\DirectDraw.h"
#include "..\Inc\Draw.h"
#include "..\Inc\Errors.h"
#include "..\Inc\Mesh.h"
#include "..\Inc\Main.h"
#include "..\Inc\Viewports.h"

Draw_Globs drawGlobs = { NULL };

VOID Draw_Initialise(LPAREA2D window) {

	drawGlobs.flags |= DRAW_FLAG_INITIALISED;
	Draw_SetClipWindow(window);
}

VOID Draw_SetClipWindow(LPAREA2D window) {

	LPDIRECTDRAWSURFACE4 surf = DirectDraw_bSurf();
	DDSURFACEDESC2 desc;

	Error_Fatal(!(drawGlobs.flags & DRAW_FLAG_INITIALISED), "Draw not initialised");

	drawGlobs.clipStart.x = 0;
	drawGlobs.clipStart.y = 0;

	if (window) {
		if (window->x > 0) drawGlobs.clipStart.x = window->x;
		if (window->y > 0) drawGlobs.clipStart.y = window->y;
	}

	memset(&desc, 0, sizeof(DDSURFACEDESC2));
	desc.dwSize = sizeof(DDSURFACEDESC2);
	if (DD_OK == surf->lpVtbl->GetSurfaceDesc(surf, &desc)){
		drawGlobs.clipEnd.x = (REAL) desc.dwWidth;
		drawGlobs.clipEnd.y = (REAL) desc.dwHeight;
		if (window) {
			if (window->x + window->width < desc.dwWidth) drawGlobs.clipEnd.x = window->x + window->width;
			if (window->y + window->height < desc.dwHeight) drawGlobs.clipEnd.y = window->y + window->height;
		}
	}

//	drawGlobs.lockRect.left = (ULONG) drawGlobs.clipStart.x;
//	drawGlobs.lockRect.top = (ULONG) drawGlobs.clipStart.y;
//	drawGlobs.lockRect.right = (ULONG) drawGlobs.clipEnd.x;
//	drawGlobs.lockRect.bottom = (ULONG) drawGlobs.clipEnd.y;
}

VOID Draw_GetClipWindow(LPAREA2D window){

	window->x = drawGlobs.clipStart.x;
	window->y = drawGlobs.clipStart.y;
	window->width = drawGlobs.clipEnd.x - drawGlobs.clipStart.x;
	window->height = drawGlobs.clipEnd.y - drawGlobs.clipStart.y;
}

VOID Draw_PixelListEx(LPVECTOR2D pointList, ULONG count, REAL r, REAL g, REAL b, ULONG effect){

	LPDIRECTDRAWSURFACE4 surf = DirectDraw_bSurf();
	LPVECTOR2D point;
	ULONG loop, colour;

	Error_Fatal(!(drawGlobs.flags & DRAW_FLAG_INITIALISED), "Draw not initialised");

	if (Draw_LockSurface(surf, effect)) {

		colour = Draw_GetColour(r, g, b);

		for (loop=0 ; loop<count ; loop++){
			point = &pointList[loop];

			if (point->x >= drawGlobs.clipStart.x && point->y >= drawGlobs.clipStart.y && point->x < drawGlobs.clipEnd.x && point->y < drawGlobs.clipEnd.y){
				drawGlobs.drawPixelFunc((SLONG) point->x, (SLONG) point->y, colour);
			}
		}
		Draw_UnlockSurface(surf);
	}
}

VOID Draw_LineListEx(LPVECTOR2D fromList, LPVECTOR2D toList, ULONG count, REAL r, REAL g, REAL b, ULONG effect){

	LPDIRECTDRAWSURFACE4 surf = DirectDraw_bSurf();
	LPVECTOR2D from, to;
	ULONG loop, colour;

	Error_Fatal(!(drawGlobs.flags & DRAW_FLAG_INITIALISED), "Draw not initialised");

	if (Draw_LockSurface(surf, effect)) {
		
		colour = Draw_GetColour(r, g, b);
		
		for (loop=0 ; loop<count ; loop++){			
			from = &fromList[loop];
			to = &toList[loop];
			Draw_LineActual((SLONG) from->x, (SLONG) from->y, (SLONG) to->x, (SLONG) to->y, colour);
		}
		Draw_UnlockSurface(surf);
	}

}

VOID Draw_WorldLineListEx(lpViewport vp, LPVECTOR3D fromList, LPVECTOR3D toList, ULONG count, REAL r, REAL g, REAL b, REAL a, ULONG effect) {

	ULONG loop;
	LPDIRECT3DVIEWPORT viewport1;
	LPDIRECT3DVIEWPORT3 viewport3;
	D3DMATRIX m = { 0.0f };

	m._11 = m._22 = m._33 = m._44 = 1.0f;

	Error_Fatal(count > DRAW_MAXLINES, "DRAW_MAXLINES too small");

	for (loop=0 ; loop<count ; loop++) {
		drawGlobs.vertexList[(loop*2)+0].position = fromList[loop];
		drawGlobs.vertexList[(loop*2)+0].colour = Container_GetRGBAColour(r, g, b, a);
		drawGlobs.vertexList[(loop*2)+1].position = toList[loop];
		drawGlobs.vertexList[(loop*2)+1].colour = Container_GetRGBAColour(r, g, b, a);
	}

	vp->lpVP->lpVtbl->GetDirect3DViewport(vp->lpVP, &viewport1);
	viewport1->lpVtbl->QueryInterface(viewport1, &IID_IDirect3DViewport3, &viewport3);
	viewport1->lpVtbl->Release(viewport1);
	lpIMDevice()->lpVtbl->SetCurrentViewport(lpIMDevice(), viewport3);
	lpIMDevice()->lpVtbl->SetTexture(lpIMDevice(), 0, NULL);
	lpIMDevice()->lpVtbl->SetLightState(lpIMDevice(), D3DLIGHTSTATE_MATERIAL, 0);
	lpIMDevice()->lpVtbl->SetLightState(lpIMDevice(), D3DLIGHTSTATE_COLORVERTEX, TRUE);
	lpIMDevice()->lpVtbl->SetTransform(lpIMDevice(), D3DTRANSFORMSTATE_WORLD, &m);

	lpIMDevice()->lpVtbl->BeginScene(lpIMDevice());

	Main_ChangeRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
	Main_ChangeRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
	Main_ChangeRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
	Main_ChangeRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
//	Main_ChangeRenderState(D3DRENDERSTATE_ZBIAS, 2);

	lpIMDevice()->lpVtbl->DrawPrimitive(lpIMDevice(), D3DPT_LINELIST, DRAW_VERTEXFLAGS, drawGlobs.vertexList, count * 2, D3DDP_WAIT);

	lpIMDevice()->lpVtbl->SetLightState(lpIMDevice(), D3DLIGHTSTATE_COLORVERTEX, FALSE);
	Main_ChangeRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
//	Main_ChangeRenderState(D3DRENDERSTATE_ZBIAS, 0);

	Main_RestoreStates(FALSE);
	lpIMDevice()->lpVtbl->EndScene(lpIMDevice());

	viewport3->lpVtbl->Release(viewport3);
}

/*
VOID Draw_WorldLineListEx(lpViewport vp, LPVECTOR3D fromList, LPVECTOR3D toList, ULONG count, REAL r, REAL g, REAL b, REAL a, ULONG effect){

	LPDIRECTDRAWSURFACE4 surf = DirectDraw_bSurf();
	VECTOR2D from, to;
	ULONG loop, colour;

	Error_Fatal(!(drawGlobs.flags & DRAW_FLAG_INITIALISED), "Draw not initialised");

	if (Draw_LockSurface(surf, effect)) {
		
		colour = Draw_GetColour(r, g, b);
		
		for (loop=0 ; loop<count ; loop++){
			Viewport_WorldToScreen(vp, &from, &fromList[loop]);
			Viewport_WorldToScreen(vp, &to, &toList[loop]);
			Draw_LineActual((SLONG) from.x, (SLONG) from.y, (SLONG) to.x, (SLONG) to.y, colour);
		}
		Draw_UnlockSurface(surf);
	}

}
*/
VOID Draw_RectListEx(LPAREA2D rectList, ULONG count, REAL r, REAL g, REAL b, ULONG effect){

	LPDIRECTDRAWSURFACE4 surf = DirectDraw_bSurf();
	ULONG loop, colour;
	SLONG x, y, ex, ey;
	AREA2D rect;
	VECTOR2D end;

	Error_Fatal(!(drawGlobs.flags & DRAW_FLAG_INITIALISED), "Draw not initialised");

	if (Draw_LockSurface(surf, effect)) {

		colour = Draw_GetColour(r, g, b);

		for (loop=0 ; loop<count ; loop++){
			rect = rectList[loop];
			end.x = rect.x + rect.width;
			end.y = rect.y + rect.height;
			if (rect.x < drawGlobs.clipStart.x) rect.x = (REAL) drawGlobs.clipStart.x;
			if (rect.y < drawGlobs.clipStart.y) rect.y = (REAL) drawGlobs.clipStart.y;
			if (end.x >= drawGlobs.clipEnd.x) end.x = (REAL) (drawGlobs.clipEnd.x-1);
			if (end.y >= drawGlobs.clipEnd.y) end.y = (REAL) (drawGlobs.clipEnd.y-1);
			ex = (SLONG) end.x;
			ey = (SLONG) end.y;
			for (y=(SLONG)rect.y ; y<ey ; y++){
				for (x=(SLONG)rect.x ; x<ex ; x++){
					drawGlobs.drawPixelFunc(x, y, colour);
				}
			}
		}
		Draw_UnlockSurface(surf);
	}
}

VOID Draw_RectList2Ex(lpDraw_Rect rectList, ULONG count, ULONG effect){

	LPDIRECTDRAWSURFACE4 surf = DirectDraw_bSurf();
	ULONG loop, colour;
	SLONG x, y, ex, ey;
	AREA2D rect;
	VECTOR2D end;

	Error_Fatal(!(drawGlobs.flags & DRAW_FLAG_INITIALISED), "Draw not initialised");

	if (Draw_LockSurface(surf, effect)) {

		for (loop=0 ; loop<count ; loop++){

			rect = rectList[loop].rect;
			colour = Draw_GetColour(rectList[loop].r, rectList[loop].g, rectList[loop].b);

			end.x = rect.x + rect.width;
			end.y = rect.y + rect.height;
			if (rect.x < drawGlobs.clipStart.x) rect.x = (REAL) drawGlobs.clipStart.x;
			if (rect.y < drawGlobs.clipStart.y) rect.y = (REAL) drawGlobs.clipStart.y;
			if (end.x >= drawGlobs.clipEnd.x) end.x = (REAL) (drawGlobs.clipEnd.x-1);
			if (end.y >= drawGlobs.clipEnd.y) end.y = (REAL) (drawGlobs.clipEnd.y-1);
			ex = (SLONG) end.x;
			ey = (SLONG) end.y;
			for (y=(SLONG)rect.y ; y<ey ; y++){
				for (x=(SLONG)rect.x ; x<ex ; x++){
					drawGlobs.drawPixelFunc(x, y, colour);

				}
			}
		}
		Draw_UnlockSurface(surf);
	}
}

VOID Draw_DotCircle(LPVECTOR2D pos, ULONG radius, ULONG dots, REAL r, REAL g, REAL b, ULONG effect) {

	LPDIRECTDRAWSURFACE4 surf = DirectDraw_bSurf();
	ULONG loop, x, y, colour;
	REAL angle, step = (2.0f * M_PI) / dots;

	Error_Fatal(!(drawGlobs.flags & DRAW_FLAG_INITIALISED), "Draw not initialised");

	if (Draw_LockSurface(surf, effect)) {

		colour = Draw_GetColour(r, g, b);

		for (loop=0 ; loop<dots ; loop++){
			angle = step * loop;
			x = (ULONG) (pos->x + (Maths_Sin(angle) * radius));
			y = (ULONG) (pos->y + (Maths_Cos(angle) * radius));
			if (x >= drawGlobs.clipStart.x && y >= drawGlobs.clipStart.y && x < drawGlobs.clipEnd.x && y < drawGlobs.clipEnd.y){
				drawGlobs.drawPixelFunc(x, y, colour);
			}
		}
		Draw_UnlockSurface(surf);
	}
}

/**************************************************************************************************
 ******* Static functions...
 **************************************************************************************************/

static ULONG Draw_GetColour(REAL r, REAL g, REAL b){

	ULONG colour = 0;

	Error_Fatal(NULL==drawGlobs.buffer, "Must be called after Draw_LockSurface()");
	
	if (8 == drawGlobs.bpp) {

	} else {
		colour |= (ULONG) (r * 255.0) >> (8 - drawGlobs.redBits) << (drawGlobs.greenBits + drawGlobs.blueBits);
		colour |= (ULONG) (g * 255.0) >> (8 - drawGlobs.greenBits) << drawGlobs.blueBits;
		colour |= (ULONG) (b * 255.0) >> (8 - drawGlobs.blueBits);
	}

	return colour;
}

static BOOL Draw_LockSurface(LPDIRECTDRAWSURFACE4 surf, ULONG effect){

	DDSURFACEDESC2 desc;
	HRESULT r;

	memset(&desc, 0, sizeof(DDSURFACEDESC2));
	desc.dwSize = sizeof(DDSURFACEDESC2);
//	if (DD_OK == (r = surf->lpVtbl->Lock(surf, &drawGlobs.lockRect, &desc, DDLOCK_WAIT, NULL))){
	if (DD_OK == (r = surf->lpVtbl->Lock(surf, NULL, &desc, DDLOCK_WAIT, NULL))){

		ULONG loop;

		drawGlobs.buffer = desc.lpSurface;
		drawGlobs.pitch = desc.lPitch;
		drawGlobs.redMask = desc.ddpfPixelFormat.dwRBitMask;
		drawGlobs.greenMask = desc.ddpfPixelFormat.dwGBitMask;
		drawGlobs.blueMask = desc.ddpfPixelFormat.dwBBitMask;
		drawGlobs.bpp = desc.ddpfPixelFormat.dwRGBBitCount;

		drawGlobs.redBits = drawGlobs.greenBits = drawGlobs.blueBits = 0;
		for (loop=0 ; loop<drawGlobs.bpp ; loop++) {
			if (drawGlobs.redMask & (1 << loop)) drawGlobs.redBits++;
			if (drawGlobs.greenMask & (1 << loop)) drawGlobs.greenBits++;
			if (drawGlobs.blueMask & (1 << loop)) drawGlobs.blueBits++;
		}

		if (Draw_SetDrawPixelFunc(effect)) {
			return TRUE;
		}
		Draw_UnlockSurface(surf);
	}

	return FALSE;
}

static VOID Draw_UnlockSurface(LPDIRECTDRAWSURFACE4 surf){

//	surf->lpVtbl->Unlock(surf, &drawGlobs.lockRect);
	surf->lpVtbl->Unlock(surf, NULL);
	drawGlobs.buffer = NULL;
	drawGlobs.pitch = 0;
	drawGlobs.redMask = 0;
	drawGlobs.greenMask = 0;
	drawGlobs.blueMask = 0;
	drawGlobs.drawPixelFunc = NULL;
	drawGlobs.bpp = 0;
}

static BOOL Draw_SetDrawPixelFunc(ULONG effect){

	if (8 == drawGlobs.bpp) {
		drawGlobs.drawPixelFunc = Draw_Pixel8;
	} else if (16 == drawGlobs.bpp) {
		if (DrawEffect_XOR == effect) drawGlobs.drawPixelFunc = Draw_Pixel16XOR;
		else if (DrawEffect_HalfTrans == effect) drawGlobs.drawPixelFunc = Draw_Pixel16HalfTrans;
		else drawGlobs.drawPixelFunc = Draw_Pixel16;
	} else if (24 == drawGlobs.bpp) {
		drawGlobs.drawPixelFunc = Draw_Pixel24;
	} else if (32 == drawGlobs.bpp) {
		drawGlobs.drawPixelFunc = Draw_Pixel32;
	} else {
		drawGlobs.drawPixelFunc = NULL;
		return FALSE;
	}

	return TRUE;
}

static VOID Draw_LineActual(SLONG x1, SLONG y1, SLONG x2, SLONG y2, ULONG colour) {
	
	SLONG deltax, deltay, numpixels;
	SLONG d, dinc1, dinc2;
	SLONG x, xinc1, xinc2;
	SLONG y, yinc1, yinc2;
	SLONG loop;

	deltax = abs(x2 - x1);
	deltay = abs(y2 - y1);
	if (deltax >= deltay) {
		numpixels = deltax + 1;
		d = 2 * deltay - deltax;
		dinc1 = deltay << 1;
		dinc2 = (deltay - deltax) << 1;
		xinc1 = 1;
		xinc2 = 1;
		yinc1 = 0;
		yinc2 = 1;
	} else {
		numpixels = deltay + 1;
		d = (2 * deltax) - deltay;
		dinc1 = deltax << 1;
		dinc2 = (deltax - deltay) << 1;
		xinc1 = 0;
		xinc2 = 1;
		yinc1 = 1;
		yinc2 = 1;
	}
	
	if (x1>x2) {
		xinc1 = -xinc1;
		xinc2 = -xinc2;
	}
	if (y1>y2) {
		yinc1 = -yinc1;
		yinc2 = -yinc2;
	}
	x = x1;
	y = y1;
	
	for (loop=1 ; loop<=numpixels ; loop++) {
		
		if (x >= drawGlobs.clipStart.x && y >= drawGlobs.clipStart.y && x < drawGlobs.clipEnd.x && y < drawGlobs.clipEnd.y){
			drawGlobs.drawPixelFunc(x, y, colour);
		}
		
		if (d < 0) {
			d = d + dinc1;
			x = x + xinc1;
			y = y + yinc1;
		} else {
			d = d + dinc2;
			x = x + xinc2;
			y = y + yinc2;
		}
	}
}

/**********************************************************************************************************************
 ******** 8bit Pixel Routines
 **********************************************************************************************************************/

static VOID Draw_Pixel8(SLONG x, SLONG y, ULONG value){

	LPUCHAR addr = &((LPUCHAR)drawGlobs.buffer)[(y*drawGlobs.pitch)+x];
	*addr = (UCHAR) value;
}

/**********************************************************************************************************************
 ******** 16bit (565) Pixel Routines
 **********************************************************************************************************************/

static VOID Draw_Pixel16(SLONG x, SLONG y, ULONG value){

	LPUWORD addr = (LPUWORD) &((LPUCHAR)drawGlobs.buffer)[(y*drawGlobs.pitch)+(x*2)];
	*addr = (UWORD) value;
}

static VOID Draw_Pixel16XOR(SLONG x, SLONG y, ULONG value){

	LPUWORD addr = (LPUWORD) &((LPUCHAR)drawGlobs.buffer)[(y*drawGlobs.pitch)+(x*2)];
	*addr = *addr ^((UWORD) value);
}

static VOID Draw_Pixel16HalfTrans(SLONG x, SLONG y, ULONG value){

	LPUWORD addr = (LPUWORD) &((LPUCHAR)drawGlobs.buffer)[(y*drawGlobs.pitch)+(x*2)];
	UWORD r, g, b;

	r = (((*addr >> 12) + ((UWORD) value >> 12)) << 11) & (UWORD) drawGlobs.redMask;
	g = ((((*addr & (UWORD) drawGlobs.greenMask) >> 6) + (((UWORD) value & (UWORD) drawGlobs.greenMask) >> 6)) << 5) & (UWORD) drawGlobs.greenMask;
	b = (((*addr & (UWORD) drawGlobs.blueMask) >> 1) + (((UWORD) value & (UWORD) drawGlobs.blueMask) >> 1)) & (UWORD) drawGlobs.blueMask;

	*addr = (r|g|b);
}

/**********************************************************************************************************************
 ******** 24bit Pixel Routines
 **********************************************************************************************************************/

static VOID Draw_Pixel24(SLONG x, SLONG y, ULONG value){

	LPULONG addr = (LPULONG) &((LPUCHAR)drawGlobs.buffer)[(y*drawGlobs.pitch)+(x*3)];

	*addr &= 0x000000ff;
	*addr |= value << 8;
}

/**********************************************************************************************************************
 ******** 32bit Pixel Routines
 **********************************************************************************************************************/

static VOID Draw_Pixel32(SLONG x, SLONG y, ULONG value){

	LPULONG addr = (LPULONG) &((LPUCHAR)drawGlobs.buffer)[(y*drawGlobs.pitch)+(x*4)];
	*addr = (ULONG) value;
}
