
#include <d3d.h>

#include "Standard.h"
#include "DirectX.h"
#include "Lights.h"
#include "Errors.h"
#include "Frames.h"
#include "Lists.h"
#include "Mem.h"
#include "Render.h"
#include "ModelClip.h"
#include "Viewports.h"

struct ViewportGlobs {

	struct Viewport viewList[VIEWPORT_MAX];

} viewportGlobs = { 0 };

lpViewport Viewport_Create(REAL x, REAL y, REAL width, REAL height) {

	lpViewport vp;

	Error_Fatal(width < 0.0f || height < 0.0f, "Width and height must of viewport must be positive");
	Error_Fatal(x < 0.0f || x > 1.0f || y < 0.0f || y > 1.0f ||
		x + width > 1.0f || y + height > 1.0f, "Viewport dimensions cannot exceed the screen size");

	if (vp = Viewport_CreatePixel(0, 0, 0, 0)) {
		
		vp->frontClip = 1.0f;
		vp->backClip = 100.0f;
		vp->fov = 0.5f;
		vp->flags |= VIEWPORT_FLAG_RELATIVE;

		vp->shape.x = x;
		vp->shape.y = y;
		vp->shape.width = width;
		vp->shape.height = height;

		Viewport_Setup(vp);
	}

	return vp;
}

lpList Viewport_GetModelClipList(lpViewport vp) {

	if (vp->modelClipList) return vp->modelClipList;
	else return vp->modelClipList = List_Create(sizeof(struct ModelClip));
}

VOID Viewport_UseModelClipList(lpViewport vp, lpViewport from) {

	Error_Fatal(NULL != vp->modelClipList, "Viewport already has its own ModelClip list");

	vp->modelClipList = from->modelClipList;
}

lpViewport Viewport_CreatePixel(ULONG x, ULONG y, ULONG width, ULONG height) {

	lpViewport vp = NULL;
	ULONG loop;

	for (loop=0 ; loop<VIEWPORT_MAX ; loop++) {
		if (!(viewportGlobs.viewList[loop].flags & VIEWPORT_FLAG_USED)) {
			vp = &viewportGlobs.viewList[loop];
			vp->flags |= VIEWPORT_FLAG_USED;
			break;
		}
	}

	if (vp) {

		vp->shape.x = (REAL) x;
		vp->shape.y = (REAL) y;
		vp->shape.width = (REAL) width;
		vp->shape.height = (REAL) height;

		vp->frontClip = 1.0f;
		vp->backClip = 100.0f;
		vp->fov = 0.5f;

		Viewport_Setup(vp);

	} else Error_Fatal(TRUE, "Run out of viewports");

	return vp;
}

static VOID Viewport_Setup(lpViewport vp) {

	LPD3DVIEWPORT7 viewport = &vp->viewport;

	if (vp->flags & VIEWPORT_FLAG_RELATIVE) {
		viewport->dwX = (ULONG) (vp->shape.x * DirectX_GetWidth());
		viewport->dwY = (ULONG) (vp->shape.y * DirectX_GetHeight());
		viewport->dwWidth = (ULONG) (vp->shape.width * DirectX_GetWidth());
		viewport->dwHeight = (ULONG) (vp->shape.height * DirectX_GetHeight());
	} else {
		viewport->dwX = (ULONG) vp->shape.x;
		viewport->dwY = (ULONG) vp->shape.y;
		viewport->dwWidth = (ULONG) vp->shape.width;
		viewport->dwHeight = (ULONG) vp->shape.height;

		Error_Fatal(viewport->dwX + viewport->dwWidth > DirectX_GetWidth() ||
			viewport->dwY + viewport->dwHeight > DirectX_GetHeight(), "Viewport exceeds screen boundry");
	}

	viewport->dvMinZ = 0.0f;
	viewport->dvMaxZ = 1.0f;

	vp->aspect = (REAL) vp->viewport.dwHeight / (REAL) vp->viewport.dwWidth;
	Viewport_SetProjectionMatrix(vp);
}

BOOL Viewport_ReconfigureCallback(lpViewport vp, LPVOID data) {

	Viewport_Setup(vp);

	return FALSE;
}

VOID Viewport_Reconfigure(VOID) {

	Viewport_RunThrough(Viewport_ReconfigureCallback, NULL);
}

VOID Viewport_SetBackgroundColourAlpha(lpViewport vp, REAL r, REAL g, REAL b, REAL a) {

	vp->bgColour = COLOUR_FROMREALA(a, r, g, b);
}

VOID Viewport_Clear(lpViewport vp, BOOL backGround, BOOL zBuffer) {

	D3DRECT rect = { (ULONG) vp->viewport.dwX, (ULONG) vp->viewport.dwY, (ULONG) (vp->viewport.dwX + vp->viewport.dwWidth), (ULONG) (vp->viewport.dwY + vp->viewport.dwHeight) };
	DWORD flags = 0;

	if (backGround) flags |= D3DCLEAR_TARGET;
	if (zBuffer) flags |= D3DCLEAR_ZBUFFER;
	DirectX_Device()->lpVtbl->Clear(DirectX_Device(), 1, &rect, flags, vp->bgColour, 1.0f, 0);
}

VOID Viewport_SetFOV(lpViewport vp, REAL fov) {

	vp->fov = fov;
	Viewport_SetProjectionMatrix(vp);
}

VOID Viewport_SetClip(lpViewport vp, REAL front, REAL back) {

	Error_Fatal(front <= M_EPSILON, "Front clipping plane value is too small");

	vp->frontClip = front;
	vp->backClip = back;
	Viewport_SetProjectionMatrix(vp);
}

__inline REAL Viewport_GetBackClip(lpViewport vp) {

	return vp->backClip;
}

static VOID Viewport_SetProjectionMatrix(lpViewport vp) {
	
//	(D3DMATRIX& mat, FLOAT fFOV, FLOAT fAspect, FLOAT fNearPlane, FLOAT fFarPlane)

	REAL w, h, Q, halffov = vp->fov / 2.0f;

	Error_Fatal(fabs(vp->backClip - vp->frontClip) < 0.01f, "Clipping volume too narrow.");
	Error_Fatal(fabs(sin(halffov)) < 0.01f, "Field of view out of bounds.");

	w = vp->aspect * Maths_Cot(halffov);
	h = Maths_Cot(halffov);
	Q = vp->backClip / (vp->backClip - vp->frontClip);

	memset(vp->projMat, 0, sizeof(MATRIX4D));
	vp->projMat[0][0] = w;
	vp->projMat[1][1] = h;
	vp->projMat[2][2] = Q;
	vp->projMat[2][3] = 1.0f;
	vp->projMat[3][2] = -Q * vp->frontClip;

}

/*
VOID Viewport_AddLight(lpViewport vp) {

	LPDIRECT3DLIGHT lightObject;
	D3DLIGHT2 light;

	Direct3D_Direct3D()->lpVtbl->CreateLight(Direct3D_Direct3D(), &lightObject, NULL);
	memset(&light, 0, sizeof(D3DLIGHT2));
	light.dwSize = sizeof(D3DLIGHT2);
	light.dltType = D3DLIGHT_DIRECTIONAL;
	light.dwFlags = D3DLIGHT_ACTIVE;
	light.dcvColor.r = 1.0f;
	light.dcvColor.g = 1.0f;
	light.dcvColor.b = 1.0f;
	light.dvDirection.x = -1.0f;
	light.dvDirection.y = -1.0f;
	light.dvDirection.z = 1.0f;
	lightObject->lpVtbl->SetLight(lightObject, &light);
	vp->view->lpVtbl->AddLight(vp->view, lightObject);
}
*/

/*
VOID Viewport_TestCode(lpViewport vp, lpFrame camera, lpFrame frame) {

	MATRIX4D result, world, view, temp;
//	VECTOR4D testvec = {  -73.91f,  0.0f,   30.61f, 1.0f };
//	VECTOR4D testvec = {  80.0f, -5.0f, 0.0f, 1.0f };
	VECTOR4D vec1, vec2, vec3;
	VECTOR4D testvec;

	{
		extern lpMesh mesh;
		VECTOR3D shape[3];
		Mesh_GetPolyShape(mesh, 0, shape);
		testvec.x = shape[0].x;
		testvec.y = shape[0].y;
		testvec.z = shape[0].z;
		testvec.w = 1.0f;
	}

	Frame_GetTransform(frame, world);
	Frame_GetTransform(camera, temp);
	Maths_InvertMatrix(view, temp);

	Maths_MultiplyVector4DByMatrix(&vec1, &testvec, world);
	Maths_MultiplyVector4DByMatrix(&vec2, &vec1, view);
	Maths_MultiplyVector4DByMatrix(&vec3, &vec2, vp->projMat);

	vec3.x /= vec3.w;
	vec3.y /= vec3.w;
	vec3.z /= vec3.w;

	{
		D3DVIEWPORT2 vpdata;
		memset(&vpdata, 0, sizeof(vpdata));
		vpdata.dwSize = sizeof(vpdata);
		vp->view->lpVtbl->GetViewport2(vp->view, &vpdata);

		vec3.x *= 320.0f;
		vec3.y *= 240.0f;

//		vec3.x /= vp->aspect;
//		vec3.y /= vp->aspect;

		vec3.x += 320.0f;
		vec3.y = 240.0f - vec3.y;

		{
			extern lpMesh mesh;
			VECTOR3D shape[3];			
			VECTOR3D dest, back;

			Mesh_GetPolyShape(mesh, 0, shape);
			Viewport_Transform(vp, frame, camera, &dest, &shape[0]);
			Viewport_InverseTransform(vp, frame, camera, &back, &dest);

			back.x = shape[0].x;
			back.y = shape[0].y;
			back.z = shape[0].z;
		}
	}

	{
		DDSURFACEDESC2 desc;
		memset(&desc, 0, sizeof(desc));
		desc.dwSize = sizeof(desc);
		if (DD_OK == Direct3D_BackSurf()->lpVtbl->Lock(Direct3D_BackSurf(), NULL, &desc, DDLOCK_WAIT, NULL)) {

			ULONG pixelWidth = desc.ddpfPixelFormat.dwRGBBitCount / 8;
			ULONG x = (ULONG) vec3.x;
			ULONG y = (ULONG) vec3.y;

			if (x < desc.dwWidth && y < desc.dwHeight) {
				((LPUCHAR) desc.lpSurface)[(desc.lPitch*y)+(x*pixelWidth)] = 0xff;
			}

			((LPUCHAR) desc.lpSurface)[(desc.lPitch*20)+(20*pixelWidth)] = 0xff;
			Direct3D_BackSurf()->lpVtbl->Unlock(Direct3D_BackSurf(), NULL);
		}
	}
}
*/

__inline ULONG Viewport_GetX(lpViewport vp) {

	LPD3DVIEWPORT7 viewport = &vp->viewport;

	return viewport->dwX;
}

__inline ULONG Viewport_GetY(lpViewport vp) {

	LPD3DVIEWPORT7 viewport = &vp->viewport;

	return viewport->dwY;
}

__inline ULONG Viewport_GetWidth(lpViewport vp) {

	LPD3DVIEWPORT7 viewport = &vp->viewport;

	return viewport->dwWidth;
}

__inline ULONG Viewport_GetHeight(lpViewport vp) {

	LPD3DVIEWPORT7 viewport = &vp->viewport;

	return viewport->dwHeight;
}

VOID Viewport_SetupBatchTransform(lpViewport vp, lpFrame frame, lpFrame camera) {

	MATRIX4D world, view, temp;

	if (frame) Frame_GetWorldTransform(frame, world);
	else Maths_IdentityMatrix(world);

	Frame_GetWorldTransform(camera, temp);
	Maths_InvertMatrixQuick(view, temp);

	Maths_MultiplyMatrix(temp, world, view);
	Maths_MultiplyMatrix(vp->batchMatrix, temp, vp->projMat);

	vp->halfWidth = vp->viewport.dwWidth / 2.0f;
	vp->halfHeight = vp->viewport.dwHeight / 2.0f;
}

VOID Viewport_BatchTransform(lpViewport vp, LPVECTOR3D dest, LPVECTOR3D src) {

	VECTOR3D vec;
	Maths_MultiplyVectorByMatrix(&vec, src, vp->batchMatrix);

	dest->x = vec.x * vp->halfWidth;
	dest->y = vec.y * vp->halfHeight;
	dest->z = vec.z;

	dest->x += vp->halfWidth;
	dest->y = vp->halfHeight - dest->y;
}

VOID Viewport_BatchTransform4D(lpViewport vp, LPVECTOR4D dest, LPVECTOR4D src) {

	Maths_MultiplyVector4DByMatrix(dest, src, vp->batchMatrix);

	dest->x *= vp->halfWidth;
	dest->y *= vp->halfHeight;

	dest->x += vp->halfWidth;
	dest->y = vp->halfHeight - dest->y;
}

VOID Viewport_Transform(lpViewport vp, lpFrame frame, lpFrame camera, LPVECTOR3D dest, LPVECTOR3D src) {

	MATRIX4D world, view, temp;
	VECTOR4D vec1, vec2, vec3, vec4;

	Frame_GetWorldTransform(frame, world);
	Frame_GetWorldTransform(camera, temp);
	Maths_InvertMatrixQuick(view, temp);

	vec1.x = src->x;
	vec1.y = src->y;
	vec1.z = src->z;
	vec1.w = 1.0f;

	Maths_MultiplyVector4DByMatrix(&vec2, &vec1, world);
	Maths_MultiplyVector4DByMatrix(&vec3, &vec2, view);
	Maths_MultiplyVector4DByMatrix(&vec4, &vec3, vp->projMat);

	vec4.x /= vec4.w;
	vec4.y /= vec4.w;
	vec4.z /= vec4.w;

	dest->x = vec4.x * (vp->viewport.dwWidth / 2.0f);
	dest->y = vec4.y * (vp->viewport.dwHeight / 2.0f);
	dest->z = vec4.z;

	dest->x += (vp->viewport.dwWidth / 2.0f);
	dest->y = (vp->viewport.dwHeight / 2.0f) - dest->y;

}

VOID Viewport_InverseTransform(lpViewport vp, lpFrame frame, lpFrame camera, LPVECTOR3D dest, LPVECTOR3D src) {

	MATRIX4D world, view, temp, temp2, mat;
	VECTOR4D vec, dest4D;

	Frame_GetWorldTransform(frame, world);
	Frame_GetWorldTransform(camera, temp);
	Maths_InvertMatrixQuick(view, temp);

	Maths_MultiplyMatrix(temp, world, view);
	Maths_MultiplyMatrix(temp2, temp, vp->projMat);

	Maths_InvertMatrixFull(mat, temp2);

	vec.x = src->x - (vp->viewport.dwWidth / 2.0f);
	vec.y = (vp->viewport.dwHeight / 2.0f) - src->y;
	vec.z = src->z;
	vec.w = 1.0f;

	vec.x /= (vp->viewport.dwWidth / 2.0f);
	vec.y /= (vp->viewport.dwHeight / 2.0f);

	Maths_MultiplyVector4DByMatrix(&dest4D, &vec, mat);

	dest->x = dest4D.x / dest4D.w;
	dest->y = dest4D.y / dest4D.w;
	dest->z = dest4D.z / dest4D.w;
}

lpDirectXBufferDump Viewport_GrabZBuffer(lpViewport vp) {

	AREA2Di area;

	area.x = vp->viewport.dwX;
	area.y = vp->viewport.dwY;
	area.width = vp->viewport.dwWidth;
	area.height = vp->viewport.dwHeight;

	return DirectX_DumpBuffer(DirectXSurfaceType_Z, &area);
}

VOID Viewport_Set(lpViewport vp, lpFrame camera) {

	MATRIX4D cameraMatrix;
	MATRIX4D viewMat;

	Error_Fatal(NULL == vp, "NULL passed as viewport to Viewport_Set()");
	Error_Fatal(NULL == camera, "NULL passed as camera to Viewport_Set()");

	Frame_GetWorldTransform(camera, cameraMatrix);
	Maths_InvertMatrixQuick(viewMat, cameraMatrix);

	DirectX_Device()->lpVtbl->SetViewport(DirectX_Device(), &vp->viewport);
	DirectX_Device()->lpVtbl->SetTransform(DirectX_Device(), D3DTRANSFORMSTATE_PROJECTION, Maths_GetD3DMATRIX(vp->projMat));
	DirectX_Device()->lpVtbl->SetTransform(DirectX_Device(), D3DTRANSFORMSTATE_VIEW, Maths_GetD3DMATRIX(viewMat));
}

BOOL Viewport_EnableFog(lpViewport vp, BOOL enabled) {

	if (enabled) {

		HRESULT r;
		D3DDEVICEDESC7 devDesc = { 0 };

		r = DirectX_Device()->lpVtbl->GetCaps(DirectX_Device(), &devDesc);
		Error_DirectX(r, "GetCaps");

		if (devDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_FOGTABLE) vp->flags |= VIEWPORT_FLAG_TABLEFOGENABLED;
		else if (devDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_FOGVERTEX) vp->flags |= VIEWPORT_FLAG_VERTEXFOGENABLED;
		else {
			vp->flags &= ~(VIEWPORT_FLAG_TABLEFOGENABLED|VIEWPORT_FLAG_VERTEXFOGENABLED);
			return FALSE;
		}

	} else vp->flags &= ~(VIEWPORT_FLAG_TABLEFOGENABLED|VIEWPORT_FLAG_VERTEXFOGENABLED);

	return TRUE;
}

__inline VOID Viewport_SetFogColour(lpViewport vp, COLOUR colour) {

	vp->fogColour = colour;
}

VOID Viewport_SetFogRange(lpViewport vp, REAL start, REAL end) {

	// Set the fog start and end position in camera space...

	HRESULT r;
	D3DDEVICEDESC7 devDesc = { 0 };

	r = DirectX_Device()->lpVtbl->GetCaps(DirectX_Device(), &devDesc);
	Error_DirectX(r, "GetCaps");

	if ((devDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_WFOG)) {

		vp->fogStart = start;
		vp->fogEnd = end;

	} else {

		VECTOR3D dest[2], src[2] = { { 0.0f, 0.0f, start }, { 0.0f, 0.0f, end } };

		Maths_MultiplyVectorByMatrix(&dest[0], &src[0], vp->projMat);
		Maths_MultiplyVectorByMatrix(&dest[1], &src[1], vp->projMat);

		vp->fogStart = dest[0].z;
		vp->fogEnd = dest[1].z;
	}
}

VOID Viewport_SetAmbientLight(lpViewport vp, REAL r, REAL g, REAL b) {

//	vp->ambientColour = ((ULONG) (r * 255.0f) << 16) | ((ULONG) (g * 255.0f) << 8) | ((ULONG) (b * 255.0f));
	vp->ambientColour = COLOUR_FROMREAL(r, g, b);
}

static VOID Viewport_SetupFog(lpViewport vp) {

	if ((vp->flags & VIEWPORT_FLAG_TABLEFOGENABLED) || 
		(vp->flags & VIEWPORT_FLAG_VERTEXFOGENABLED)) {
	
		DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_FOGENABLE, TRUE);
		
		if (vp->flags & VIEWPORT_FLAG_TABLEFOGENABLED) {
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_FOGTABLEMODE, D3DFOG_LINEAR);
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_FOGVERTEXMODE, D3DFOG_NONE);
		} else {
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_FOGTABLEMODE, D3DFOG_NONE);
			DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_FOGVERTEXMODE, D3DFOG_LINEAR);
		}

		DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_FOGSTART, REALASULONG(vp->fogStart));
		DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_FOGEND, REALASULONG(vp->fogEnd));
		DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_FOGCOLOR, vp->fogColour);

	} else {
	
		DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_FOGENABLE, FALSE);

	}
}

ULONG Viewport_Render(lpViewport vp, lpFrame scene, lpFrame camera) {

	MATRIX4D identityMat;
	lpLight light;

	Error_Fatal(NULL == scene, "NULL passed as scene to Viewport_Render()");

	Viewport_Set(vp, camera);

	// Set the position/direction of the lights on this viewport...
	for (light=vp->lightList ; light ; light=light->viewportNext) Light_PreRender(light);

	Maths_IdentityMatrix(identityMat);
	Frame_BuildRenderList(scene, identityMat);

#pragma message ( "Fogging disabled" )
//	Viewport_SetupFog(vp);

//	return Mesh_RenderList(vp->ambientColour);
	return Render_ProcessList(vp->ambientColour);
}

VOID Viewport_Remove(lpViewport dead) {
	
	List_Remove(dead->modelClipList);
	dead->modelClipList = NULL;
	dead->flags &= ~VIEWPORT_FLAG_USED;
}

VOID Viewport_RemoveAll(VOID) {

	ULONG loop;
	lpViewport vp;

	for (loop=0 ; loop<VIEWPORT_MAX ; loop++) {
		vp = &viewportGlobs.viewList[loop];
		vp->flags &= ~VIEWPORT_FLAG_USED;
	}
}

/*
VOID Viewport_CloseDown(VOID) {

	lpViewport vp;
	ULONG loop;

	for (loop=0 ; loop<VIEWPORT_MAX ; loop++) {
		vp = &viewportGlobs.viewList[loop];
		if (vp->flags & VIEWPORT_FLAG_USED) {
			Viewport_Remove(vp);
			vp->flags |= VIEWPORT_FLAG_RELEASED;
		} else vp->flags &= ~VIEWPORT_FLAG_RELEASED;
	}
}

VOID Viewport_Remove(lpViewport vp) {

	HRESULT r;
	Light_ViewportEnable(NULL, vp, FALSE);
	r = DirectX_Device()->lpVtbl->DeleteViewport(DirectX_Device(), vp->view);
	r = vp->view->lpVtbl->Release(vp->view);
	vp->view = NULL;
	vp->flags &= ~VIEWPORT_FLAG_USED;
}
*/

BOOL Viewport_RunThrough(BOOL (*Callback)(lpViewport vp, LPVOID data), LPVOID data) {

	ULONG loop;
	lpViewport vp;

	for (loop=0 ; loop<VIEWPORT_MAX ; loop++) {
		vp = &viewportGlobs.viewList[loop];
		if (vp->flags & VIEWPORT_FLAG_USED) {
			if (Callback(vp, data)) return TRUE;
		}
	}

	return FALSE;
}

/*
VOID Viewport_RemoveLight(lpViewport vp, lpLight light) {

	if (vp) vp->view->lpVtbl->DeleteLight(vp->view, light->object);
	else {
		ULONG loop;
		for (loop=0 ; loop<VIEWPORT_MAX ; loop++) {
			if (viewportGlobs.viewList[loop].flags & VIEWPORT_FLAG_USED) {
				vp = &viewportGlobs.viewList[loop];
				vp->view->lpVtbl->DeleteLight(vp->view, light->object);
			}
		}
	}
}
*/

VOID Viewport_AddLight(lpViewport vp, lpLight light) {

	lpLight link = vp->lightList;

	Error_Fatal(NULL==light||NULL==vp, "Viewport or light passed as NULL to Viewport_AddLight()");

	Viewport_DeleteLight(vp, light);

	vp->lightList = light;
	vp->lightList->viewportNext = link;
}

VOID Viewport_DeleteLight(lpViewport vp, lpLight light) {

	lpLight entry, prev = NULL, next = NULL;

	Error_Fatal(NULL==light||NULL==vp, "Viewport or light passed as NULL to Viewport_DeleteLight()");

	for (entry=vp->lightList ; entry ; entry=next) {
		next = entry->viewportNext;

		if (entry == light) {
			if (prev) prev->viewportNext = next;
			else vp->lightList = next;
			entry->viewportNext = NULL;
		} else prev = entry;
	}
}

VOID Viewport_NextLight(lpViewport vp, lpLight light, lpLight *result, ULONG flags) {

	Error_Fatal(NULL==light&&D3DNEXT_NEXT==flags, "NULL passed as light to Viewport_NextLight()");

	if (D3DNEXT_HEAD == flags) *result = vp->lightList;
	else if (D3DNEXT_NEXT == flags) *result = light->viewportNext;
	else if (D3DNEXT_TAIL == flags) {
		for (light=vp->lightList ; light ; light=light->viewportNext) ;
		*result = light;
	}
}
