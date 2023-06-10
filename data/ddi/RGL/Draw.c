
#include "Standard.h"
#include "Viewports.h"
#include "DirectX.h"
#include "Render.h"
#include "Frames.h"
#include "Errors.h"
#include "Mem.h"
#include "Draw.h"

#define DRAW_MAXCOORDS			100

struct DrawGlobs {

	struct DrawCoord coordList[DRAW_MAXCOORDS];

} drawGlobs = { 0 };

VOID Draw_LineListEx(lpViewport vp, MATRIX4D worldMatrix, lpFrame camera, lpDrawCoord coordList, ULONG coordCount, LPUWORD indexList, ULONG indexCount) {

	ULONG loop;

	Viewport_Set(vp, camera);

	DirectX_Device()->lpVtbl->SetTransform(DirectX_Device(), D3DTRANSFORMSTATE_WORLD, Maths_GetD3DMATRIX(worldMatrix));

//	DirectX_Device()->lpVtbl->BeginScene(DirectX_Device());
	Render_BeginScene();

	for (loop=0 ; loop<D3DDP_MAXTEXCOORD ; loop++) {
//		DirectX_Device()->lpVtbl->SetTexture(DirectX_Device(), loop, NULL);
		Render_SetTexture(loop, NULL);
	}

	DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
	DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_COLORVERTEX, TRUE);
	DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_LIGHTING, FALSE);
	DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);
	DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ZWRITEENABLE, FALSE);

	DirectX_Device()->lpVtbl->DrawIndexedPrimitive(DirectX_Device(), D3DPT_LINELIST, D3DFVF_DIFFUSE|D3DFVF_XYZ, coordList, coordCount, indexList, indexCount, 0);

//	DirectX_Device()->lpVtbl->EndScene(DirectX_Device());
	Render_EndScene();
}

__inline VOID Draw_LineList(lpViewport vp, lpFrame frame, lpFrame camera, lpDrawCoord coordList, ULONG coordCount, LPUWORD indexList, ULONG indexCount) {

	MATRIX4D mat;

	Frame_GetWorldTransform(frame, mat);
	Draw_LineListEx(vp, mat, camera, coordList, coordCount, indexList, indexCount);
}

__inline VOID Draw_WorldLineList(lpViewport vp, lpFrame camera, lpDrawCoord coordList, ULONG coordCount, LPUWORD indexList, ULONG indexCount) {

	MATRIX4D mat;

	Maths_IdentityMatrix(mat);
	Draw_LineListEx(vp, mat, camera, coordList, coordCount, indexList, indexCount);
}

/*
VOID Draw_WorldLineList(lpViewport vp, lpFrame camera, lpDrawCoord primaryList, lpDrawCoord toList, ULONG count) {

	D3DPRIMITIVETYPE primType;
	lpDrawCoord lineList = NULL;
	MATRIX4D identity;
	ULONG loop;

	if (toList) {
		
		primType = D3DPT_LINELIST;

		Error_Overflow(count * 2, DRAW_MAXCOORDS);
		lineList = drawGlobs.coordList;
		
		for (loop=0 ; loop<count ; loop++) {
			lineList[(loop * 2) + 0] = primaryList[loop];
			lineList[(loop * 2) + 1] = toList[loop];
		}

	} else primType = D3DPT_LINESTRIP;

	Viewport_Set(vp, camera);
	Maths_IdentityMatrix(identity);

	DirectX_Device()->lpVtbl->SetTransform(DirectX_Device(), D3DTRANSFORMSTATE_WORLD, Maths_GetD3DMATRIX(identity));

//	DirectX_Device()->lpVtbl->BeginScene(DirectX_Device());
	Render_BeginScene();
	
	DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
	DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_COLORVERTEX, TRUE);
	DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_LIGHTING, FALSE);

	if (lineList) {
		DirectX_Device()->lpVtbl->DrawPrimitive(DirectX_Device(), primType, D3DFVF_DIFFUSE|D3DFVF_XYZ, lineList, count * 2, 0);
	} else {
		DirectX_Device()->lpVtbl->DrawPrimitive(DirectX_Device(), primType, D3DFVF_DIFFUSE|D3DFVF_XYZ, primaryList, count, 0);
	}

	DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_LIGHTING, TRUE);
	DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_COLORVERTEX, FALSE);

//	DirectX_Device()->lpVtbl->EndScene(DirectX_Device());
	Render_EndScene();
}
*/

VOID Draw_WorldPrimitiveListUV(lpViewport vp, lpFrame camera, lpDrawPrimitiveCoord primList, ULONG primCount, lpTexture texture, VECTOR2D uvList[4], ULONG flags) {

	struct DrawScreenCoord coordList[4];
	VECTOR3D offset, center, pos[2], camDir, camUp, camCP;
	ULONG loop, sub;
	REAL size;
	BOOL add = (flags & DRAW_FLAG_ADDITIVE)?TRUE:FALSE;
	BOOL subtractive = (flags & DRAW_FLAG_SUBTRACTIVE)?TRUE:FALSE;

	Viewport_SetupBatchTransform(vp, NULL, camera);
	Frame_GetWorldOrientation(camera, &camDir, &camUp);
	Maths_Vector3DCrossProduct(&camCP, &camDir, &camUp);

//	DirectX_Device()->lpVtbl->BeginScene(DirectX_Device());
	Render_BeginScene();

	for (loop=0 ; loop<primCount ; loop++) {

		pos[0].x = primList[loop].coord.position.x;
		pos[0].y = primList[loop].coord.position.y;
		pos[0].z = primList[loop].coord.position.z;

		Maths_Vector3DScale(&pos[1], &camCP, primList[loop].size);
		Maths_Vector3DAdd(&pos[1], &pos[0], &pos[1]);

		Viewport_BatchTransform(vp, &center, &pos[0]);
		Viewport_BatchTransform(vp, &offset, &pos[1]);

		size = Maths_Vector3DDistance(&offset, &center);
	
		for (sub=0 ; sub<4 ; sub++) {
			coordList[sub].uv = uvList[sub];
			coordList[sub].colour = primList[loop].coord.colour;
			coordList[sub].position.x = size * Maths_Sin(M_PI + (M_PI / 4.0f) + (primList[loop].angle - ((M_PI / 2.0f) * sub)));
			coordList[sub].position.y = size * Maths_Cos(M_PI + (M_PI / 4.0f) + (primList[loop].angle - ((M_PI / 2.0f) * sub)));
			coordList[sub].position.x += center.x;
			coordList[sub].position.y += center.y;
			coordList[sub].position.z = center.z;
			coordList[sub].position.w = 1.0f;
		}

		DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);
		if (add) {
//			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
//			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ZWRITEENABLE, FALSE);
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);

//			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_SRCBLEND, D3DBLEND_INVSRCCOLOR);
//			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);

//			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
//			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);

			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);		
		}
		else if (subtractive) {
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ZWRITEENABLE, FALSE);
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_SRCBLEND, D3DBLEND_ZERO);
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCCOLOR);	
		}
		else {
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ZWRITEENABLE, TRUE);
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
		}


		if (flags & DRAW_FLAG_COLOURKEYED) DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_COLORKEYENABLE, TRUE);
		else DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_COLORKEYENABLE, FALSE);

//		if (texture) DirectX_Device()->lpVtbl->SetTexture(DirectX_Device(), 0, texture->surface);
//		else DirectX_Device()->lpVtbl->SetTexture(DirectX_Device(), 0, NULL);
		if (texture) Texture_Set(texture, 0);
		else Texture_Set(NULL, 0);

		if (texture && Texture_AllFlagsSet(texture, TEXTURE_FLAG_COLOURKEYED)) {
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_COLORKEYENABLE, TRUE);
		} else {
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_COLORKEYENABLE, FALSE);
		}

		DirectX_Device()->lpVtbl->DrawPrimitive(DirectX_Device(), D3DPT_TRIANGLEFAN, D3DFVF_DIFFUSE|D3DFVF_XYZRHW|D3DFVF_TEX1, coordList, 4, 0);

//		DirectX_Device()->lpVtbl->SetTexture(DirectX_Device(), 0, NULL);
	}

//	DirectX_Device()->lpVtbl->EndScene(DirectX_Device());
	Render_EndScene();
}

VOID Draw_WorldPrimitiveList(lpViewport vp, lpFrame camera, lpDrawPrimitiveCoord primList, ULONG primCount, lpTexture texture, ULONG flags) {

	VECTOR2D uvList[4];

	uvList[0].x = 0.0f;
	uvList[0].y = 0.0f;
	uvList[1].x = 1.0f;
	uvList[1].y = 0.0f;
	uvList[2].x = 1.0f;
	uvList[2].y = 1.0f;
	uvList[3].x = 0.0f;
	uvList[3].y = 1.0f;

	Draw_WorldPrimitiveListUV(vp, camera, primList, primCount, texture, uvList, flags);
}

VOID Draw_WorldPrimitiveTriangleListUV(lpViewport vp, lpFrame camera, lpDrawTriangleCoord primList, ULONG primCount, lpTexture texture, ULONG flags) {
	struct DrawScreenCoord coordList[3];
	VECTOR3D offset, center, pos[2], camDir, camUp, camCP;
	ULONG loop, sub;
	REAL size;
	BOOL add = (flags & DRAW_FLAG_ADDITIVE)?TRUE:FALSE;
	BOOL subtractive = (flags & DRAW_FLAG_SUBTRACTIVE)?TRUE:FALSE;

	Viewport_SetupBatchTransform(vp, NULL, camera);
	Frame_GetWorldOrientation(camera, &camDir, &camUp);
	Maths_Vector3DCrossProduct(&camCP, &camDir, &camUp);

	Render_BeginScene();

	for (loop=0 ; loop<primCount ; loop++) {

		for (sub=0 ; sub<3 ; sub++) {
			pos[0].x = primList[loop].position[sub].x;
			pos[0].y = primList[loop].position[sub].y;
			pos[0].z = primList[loop].position[sub].z;
	
			Maths_Vector3DScale(&pos[1], &camCP, 1.0f);
			Maths_Vector3DAdd(&pos[1], &pos[0], &pos[1]);
	
			Viewport_BatchTransform(vp, &center, &pos[0]);
			Viewport_BatchTransform(vp, &offset, &pos[1]);
	
			size = Maths_Vector3DDistance(&offset, &center);
	
			coordList[sub].uv = primList[loop].UVlist[sub];
			coordList[sub].colour = primList[loop].colour[sub];
			coordList[sub].position.x = center.x;
			coordList[sub].position.y = center.y;
			coordList[sub].position.z = center.z;
			coordList[sub].position.w = 1.0f;
		}

		DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);
		if (add) {
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ZWRITEENABLE, FALSE);
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
		}
		else if (subtractive) {
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ZWRITEENABLE, FALSE);
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_SRCBLEND, D3DBLEND_ZERO);
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCCOLOR);	
		}
		else {
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ZWRITEENABLE, TRUE);
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
		}


		if (flags & DRAW_FLAG_COLOURKEYED) DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_COLORKEYENABLE, TRUE);
		else DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_COLORKEYENABLE, FALSE);

		if (texture) Texture_Set(texture, 0);
		else Texture_Set(NULL, 0);

		if (texture && Texture_AllFlagsSet(texture, TEXTURE_FLAG_COLOURKEYED)) {
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_COLORKEYENABLE, TRUE);
		} else {
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_COLORKEYENABLE, FALSE);
		}

		DirectX_Device()->lpVtbl->DrawPrimitive(DirectX_Device(), D3DPT_TRIANGLEFAN, D3DFVF_DIFFUSE|D3DFVF_XYZRHW|D3DFVF_TEX1, coordList, 3, 0);
	}
	Render_EndScene();
}


static D3DVIEWPORT7 overlayViewport;
static float overlayWidth,overlayHeight;

VOID __inline Draw_ScreenStart(VOID)
{
	overlayViewport.dwX = 0;
	overlayViewport.dwY = 0;
	overlayViewport.dwWidth = DirectX_GetWidth();
	overlayViewport.dwHeight = DirectX_GetHeight();
	overlayViewport.dvMinZ = 0.0f;
	overlayViewport.dvMaxZ = 1.0f;

	DirectX_Device()->lpVtbl->SetViewport(DirectX_Device(), &overlayViewport);

	Render_BeginScene();

	overlayWidth = (float)DirectX_GetWidth();
	overlayHeight = (float)DirectX_GetHeight();
}

VOID __inline Draw_ScreenEnd(VOID)
{
	Render_EndScene();
}

VOID __inline Draw_ScreenOverlayPrimitive(lpDrawScreenTriangleCoord coord)
{
HRESULT r;
struct LocalVertex { VECTOR4D position; COLOUR colour; } vertexList[4];
struct DrawScreenCoord TexVertexList[3];

	Render_SetState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
	Render_SetState(D3DRENDERSTATE_ZENABLE, D3DZB_FALSE);
	Render_SetState(D3DRENDERSTATE_LIGHTING, FALSE);

	if (coord->flags & DRAW_FLAG_COLOURKEYED) DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_COLORKEYENABLE, TRUE);
	else									  DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_COLORKEYENABLE, FALSE);

	if (coord->flags == DRAW_FLAG_ADDITIVE) {
		DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
		DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
	}
	else if (coord->flags == DRAW_FLAG_SUBTRACTIVE) {
		DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_SRCBLEND, D3DBLEND_ZERO);
		DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCCOLOR);	
	}
	else {
		DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
	}

	if(coord->texture)	
	{
		TexVertexList[0].position.x = coord->position[0].x * overlayWidth;
		TexVertexList[0].position.y = coord->position[0].y * overlayHeight;
		TexVertexList[0].position.z = 0.0f;
		TexVertexList[0].position.w = 1.0f;
		TexVertexList[0].colour = coord->colour[0];
		TexVertexList[0].uv = coord->UVlist[0];
		TexVertexList[1].position.x = coord->position[1].x * overlayWidth; 
		TexVertexList[1].position.y = coord->position[1].y * overlayHeight;
		TexVertexList[1].position.z = 0.0f;
		TexVertexList[1].position.w = 1.0f;
		TexVertexList[1].colour = coord->colour[1];
		TexVertexList[1].uv = coord->UVlist[1];
		TexVertexList[2].position.x = coord->position[2].x * overlayWidth; 
		TexVertexList[2].position.y = coord->position[2].y * overlayHeight;
		TexVertexList[2].position.z = 0.0f;
		TexVertexList[2].position.w = 1.0f;
		TexVertexList[2].colour = coord->colour[2];
		TexVertexList[2].uv = coord->UVlist[2];

		Texture_Set(((lpTexture)coord->texture), 0);

		r = DirectX_Device()->lpVtbl->DrawPrimitive(DirectX_Device(), D3DPT_TRIANGLEFAN, D3DFVF_DIFFUSE|D3DFVF_XYZRHW|D3DFVF_TEX1, TexVertexList, 3, 0);
		Error_DirectX(r, "DrawPrimitive Textured");
	}
	else
	{
		vertexList[0].position.x = coord->position[0].x * overlayWidth;
		vertexList[0].position.y = coord->position[0].y * overlayHeight;
		vertexList[0].position.z = 0.0f;
		vertexList[0].position.w = 1.0f;
		vertexList[0].colour = coord->colour[0];
		vertexList[1].position.x = coord->position[1].x * overlayWidth; 
		vertexList[1].position.y = coord->position[1].y * overlayHeight;
		vertexList[1].position.z = 0.0f;
		vertexList[1].position.w = 1.0f;
		vertexList[1].colour = coord->colour[1];
		vertexList[2].position.x = coord->position[2].x * overlayWidth; 
		vertexList[2].position.y = coord->position[2].y * overlayHeight;
		vertexList[2].position.z = 0.0f;
		vertexList[2].position.w = 1.0f;
		vertexList[2].colour = coord->colour[2];

		Render_SetTexture(0, NULL);

		r = DirectX_Device()->lpVtbl->DrawPrimitive(DirectX_Device(), D3DPT_TRIANGLEFAN, D3DFVF_XYZRHW|D3DFVF_DIFFUSE, vertexList, 3, 0);
		Error_DirectX(r, "DrawPrimitive");
	}

}

VOID Draw_ScreenOverlayPrimitiveList(lpDrawScreenTriangleCoord coord, ULONG count)
{
ULONG	i;
lpDrawScreenTriangleCoord c = coord;

	Draw_ScreenStart();

	for(i=0;i<count;i++)
	{
		Draw_ScreenOverlayPrimitive(c);
		c++;
	}

	Draw_ScreenEnd();
}




