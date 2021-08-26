/**********************************************************************************
 **
 ** Viewport.c: Viewport Object Code For GODS
 **
 ** Copyright (C) Data Design Interactive.
 **
 **
 ** Written by Robert Wilson
 **
 **********************************************************************************/

#include <d3drm.h>

#include "..\inc\Standard.h"

#include "..\inc\Errors.h"
#include "..\inc\Memory.h"
#include "..\inc\Main.h"
#include "..\inc\Mesh.h"
#include "..\inc\Containers.h"
#include "..\inc\Viewports.h"
#include "..\inc\Maths.h"
#include "..\inc\DirectDraw.h"

#include "..\inc\dxbug.h"

/**********************************************************************************
 ******** Viewport Global Data
 **********************************************************************************/

Viewport_Globs viewportGlobs;

/**********************************************************************************
 ******** Viewport Global Library Functions
 **********************************************************************************/

VOID Viewport_Initialise(VOID){
	
	ULONG loop;

	for (loop=0 ; loop<VIEWPORT_MAXLISTS ; loop++){
		viewportGlobs.listSet[loop] = NULL;
	}

	viewportGlobs.freeList = NULL;
	viewportGlobs.listCount = 0;
	viewportGlobs.flags = VIEWPORT_FLAG_INITIALISED;

}

VOID Viewport_Shutdown(VOID){

	ULONG loop;

	Viewport_RemoveAll();

	for (loop=0 ; loop<VIEWPORT_MAXLISTS ; loop++){
		if (viewportGlobs.listSet[loop]) Mem_Free(viewportGlobs.listSet[loop]);
	}

	viewportGlobs.freeList = NULL;
	viewportGlobs.flags = 0x00000000;
}

Viewport *Viewport_Create(REAL xPos, REAL yPos, REAL width, REAL height, lpContainer camera){

	ULONG actWidth, actHeight, actXPos, actYPos;
	ULONG devWidth, devHeight;

	devWidth = lpDevice()->lpVtbl->GetWidth(lpDevice());
	devHeight = lpDevice()->lpVtbl->GetHeight(lpDevice());
	
	actXPos = (ULONG) (xPos * devWidth);
	actYPos = (ULONG) (yPos * devHeight);
	actWidth = (ULONG) (width * devWidth);
	actHeight = (ULONG) (height * devHeight);

	return Viewport_CreatePixel(actXPos, actYPos, actWidth, actHeight, camera);
}

Viewport *Viewport_CreatePixel(SLONG xPos, SLONG yPos, ULONG width, ULONG height, lpContainer camera){

	lpViewport newViewport;
	ULONG devWidth = lpDevice()->lpVtbl->GetWidth(lpDevice());
	ULONG devHeight = lpDevice()->lpVtbl->GetHeight(lpDevice());

	Viewport_CheckInit();

	if (xPos < 0) xPos = devWidth + xPos;
	if (yPos < 0) yPos = devHeight + yPos;

	if (xPos + width > devWidth || yPos + height > devHeight) {
		Error_Warn(TRUE, "Invalid sizes provided to Viewport_CreatePixel()");
		return NULL;
	}

	if (NULL == viewportGlobs.freeList) Viewport_AddList();
	
	newViewport = viewportGlobs.freeList;
	viewportGlobs.freeList = newViewport->nextFree;
	newViewport->nextFree = NULL;

	if (lpD3DRM()->lpVtbl->CreateViewport(lpD3DRM(), lpDevice(), camera->masterFrame, xPos, yPos, width, height, &newViewport->lpVP) == D3DRM_OK){

		newViewport->lpVP->lpVtbl->SetAppData(newViewport->lpVP, (ULONG) newViewport);

		newViewport->smoothFOV = 0.0f;
		return newViewport;

	} else Error_Warn(TRUE, "CreateViewport() call failed");

	return NULL;
}

BOOL Viewport_Configure(lpViewport vp, REAL xPos, REAL yPos, REAL width, REAL height){

	ULONG actWidth, actHeight, actXPos, actYPos;
	ULONG devWidth, devHeight;

	devWidth = lpDevice()->lpVtbl->GetWidth(lpDevice());
	devHeight = lpDevice()->lpVtbl->GetHeight(lpDevice());
	
	actXPos = (ULONG) (xPos * devWidth);
	actYPos = (ULONG) (yPos * devHeight);
	actWidth = (ULONG) (width * devWidth);
	actHeight = (ULONG) (height * devHeight);

	return Viewport_ConfigurePixel(vp, actXPos, actYPos, actWidth, actHeight);
}

BOOL Viewport_ConfigurePixel(lpViewport vp, ULONG xPos, ULONG yPos, ULONG width, ULONG height){

	Viewport_CheckInit();

	Error_Fatal(!vp, "NULL passed as viewport to Viewport_Configure()");

	if (vp->lpVP->lpVtbl->Configure(vp->lpVP, xPos, yPos, width, height) == D3DRM_OK){
		return TRUE;
	} else Error_Warn(TRUE, "Invalid values passed to Viewport_Configure()");

	return FALSE;
}

VOID Viewport_GetSize(lpViewport vp, LPULONG width, LPULONG height){

	Viewport_CheckInit();

	Error_Fatal(!vp, "NULL passed as viewport to Viewport_Configure()");

	if (width) *width = vp->lpVP->lpVtbl->GetWidth(vp->lpVP);
	if (height) *height = vp->lpVP->lpVtbl->GetHeight(vp->lpVP);
}

VOID Viewport_SetCamera(lpViewport vp, lpContainer cont){

	Viewport_CheckInit();

	Error_Fatal(!vp||!cont, "NULL passed as viewport or container to Viewport_SetCamera()");

	// Does it matter that a non-camera container can be used as a camera????

	if (vp->lpVP->lpVtbl->SetCamera(vp->lpVP, cont->masterFrame) == D3DRM_OK){

	} else Error_Warn(TRUE, "Cannot set container as camera");
}

lpContainer Viewport_GetCamera(lpViewport vp){

	LPDIRECT3DRMFRAME3 frame;
	lpContainer camera = NULL;

	Viewport_CheckInit();

	Error_Fatal(!vp, "NULL passed as viewport or container to Viewport_SetCamera()");

	// Does it matter that a non-camera container can be used as a camera????

	if (vp->lpVP->lpVtbl->GetCamera(vp->lpVP, &frame) == D3DRM_OK){
		Container_AppData *appData = (Container_AppData*) frame->lpVtbl->GetAppData(frame);
		if (appData) camera = appData->ownerContainer;
		frame->lpVtbl->Release(frame);
	} else Error_Warn(TRUE, "Cannot set container as camera");

	return camera;
}

VOID Viewport_SetBackClip(lpViewport vp, REAL dist){

	Viewport_CheckInit();

	if (vp->lpVP->lpVtbl->SetBack(vp->lpVP, dist) == D3DRM_OK){

	} else Error_Warn(TRUE, "Cannot set back clipping plane distance");
}

VOID Viewport_SetFrontClip(lpViewport vp, REAL dist){

	Viewport_CheckInit();

	if (vp->lpVP->lpVtbl->SetFront(vp->lpVP, dist) == D3DRM_OK){

	} else Error_Warn(TRUE, "Cannot set front clipping plane distance");
}

REAL Viewport_GetBackClip(lpViewport vp){

	Viewport_CheckInit();

	return vp->lpVP->lpVtbl->GetBack(vp->lpVP);
}

REAL Viewport_GetFrontClip(lpViewport vp){

	Viewport_CheckInit();

	return vp->lpVP->lpVtbl->GetFront(vp->lpVP);
}

VOID Viewport_ClearZBuffer(lpViewport vp) {

	LPDIRECT3DVIEWPORT view1;
	LPDIRECT3DVIEWPORT3 view3;
	HRESULT r;
	D3DRECT rect = {
		vp->lpVP->lpVtbl->GetX(vp->lpVP),
		vp->lpVP->lpVtbl->GetY(vp->lpVP),
		vp->lpVP->lpVtbl->GetX(vp->lpVP) + vp->lpVP->lpVtbl->GetWidth(vp->lpVP),
		vp->lpVP->lpVtbl->GetY(vp->lpVP) + vp->lpVP->lpVtbl->GetHeight(vp->lpVP)
	};

	Viewport_CheckInit();

	r = vp->lpVP->lpVtbl->GetDirect3DViewport(vp->lpVP, &view1);
	r = view1->lpVtbl->QueryInterface(view1, &IID_IDirect3DViewport3, &view3);
	view1->lpVtbl->Release(view1);
	r = view3->lpVtbl->Clear2(view3, 1, &rect, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
	view3->lpVtbl->Release(view3);
}

VOID Viewport_Clear(lpViewport vp, BOOL full){

	Viewport_CheckInit();

	if (full) {

		LPDIRECT3DRMFRAME3 scene = Viewport_GetScene(vp);
		D3DCOLOR colour = 0;
		AREA2D area = {
			(REAL) vp->lpVP->lpVtbl->GetX(vp->lpVP),
			(REAL) vp->lpVP->lpVtbl->GetY(vp->lpVP),
			(REAL) vp->lpVP->lpVtbl->GetWidth(vp->lpVP),
			(REAL) vp->lpVP->lpVtbl->GetHeight(vp->lpVP)
		};

		if (scene) colour = scene->lpVtbl->GetSceneBackground(scene);
//		DirectDraw_Clear(&area, colour);
//		vp->lpVP->lpVtbl->Clear(vp->lpVP, D3DRMCLEAR_ZBUFFER);

		{
			LPDIRECT3DVIEWPORT view1;
			LPDIRECT3DVIEWPORT3 view3;
			HRESULT r;
			D3DRECT rect = { (ULONG) area.x, (ULONG) area.y, (ULONG) (area.x + area.width), (ULONG) (area.y + area.height) };
			r = vp->lpVP->lpVtbl->GetDirect3DViewport(vp->lpVP, &view1);
			r = view1->lpVtbl->QueryInterface(view1, &IID_IDirect3DViewport3, &view3);
			view1->lpVtbl->Release(view1);
			r = view3->lpVtbl->Clear2(view3, 1, &rect, D3DCLEAR_ZBUFFER|D3DCLEAR_TARGET, colour, 1.0f, 0);
			view3->lpVtbl->Release(view3);
		}

	} else {

		vp->lpVP->lpVtbl->Clear(vp->lpVP, D3DRMCLEAR_ALL);

	}
}

VOID Viewport_Darken(lpViewport vp, REAL level) {

	ULONG colour;

	level = max(level, 0.0f);
	level = min(level, 1.0f);
	colour = (ULONG) ((1.0f - level) * 255.0f) << 24;

	Viewport_RenderGradient(vp, 1.0f, colour, 0.0f, colour, TRUE);
}

VOID Viewport_RenderGradient(lpViewport vp, REAL bottom, ULONG bottomColour, REAL top, ULONG topColour, BOOL sub) {

	LPDIRECT3DVIEWPORT view1;
	LPDIRECT3DVIEWPORT3 view3;
	struct { VECTOR4D position; ULONG colour; } vertices[4];

	vertices[0].position.z = vertices[1].position.z = vertices[2].position.z = vertices[3].position.z = 0.0f;
	vertices[0].position.w = vertices[1].position.w = vertices[2].position.w = vertices[3].position.w = 1.0f;
	vertices[0].colour = vertices[1].colour = topColour;
	vertices[2].colour = vertices[3].colour = bottomColour;

	vertices[0].position.x = 0.0f;
	vertices[0].position.y = (REAL) vp->lpVP->lpVtbl->GetHeight(vp->lpVP) * top;
	vertices[1].position.x = (REAL) vp->lpVP->lpVtbl->GetWidth(vp->lpVP);
	vertices[1].position.y = (REAL) vp->lpVP->lpVtbl->GetHeight(vp->lpVP) * top;
	vertices[3].position.x = (REAL) vp->lpVP->lpVtbl->GetWidth(vp->lpVP);
	vertices[3].position.y = (REAL) vp->lpVP->lpVtbl->GetHeight(vp->lpVP) * bottom;
	vertices[2].position.x = 0.0f;
	vertices[2].position.y = (REAL) vp->lpVP->lpVtbl->GetHeight(vp->lpVP) * bottom;

	vp->lpVP->lpVtbl->GetDirect3DViewport(vp->lpVP, &view1);
	view1->lpVtbl->QueryInterface(view1, &IID_IDirect3DViewport3, &view3);
	view1->lpVtbl->Release(view1);

	if (mainGlobs.flags & MAIN_FLAG_DONTMANAGETEXTURES) {
		lpIMDevice()->lpVtbl->SetRenderState(lpIMDevice(), D3DRENDERSTATE_TEXTUREHANDLE, 0);
	} else {
		lpIMDevice()->lpVtbl->SetTexture(lpIMDevice(), 0, NULL);
	}

	Main_ChangeRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
	if (sub) {
		Main_ChangeRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
		Main_ChangeRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
	} else {
		Main_ChangeRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
		Main_ChangeRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
	}

	Main_ChangeRenderState(D3DRENDERSTATE_ZENABLE, FALSE);
	Main_ChangeRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);

	lpIMDevice()->lpVtbl->BeginScene(lpIMDevice());
	lpIMDevice()->lpVtbl->DrawPrimitive(lpIMDevice(), D3DPT_TRIANGLESTRIP, D3DFVF_DIFFUSE|D3DFVF_XYZRHW, vertices, 4, D3DDP_DONOTLIGHT|D3DDP_WAIT);
	lpIMDevice()->lpVtbl->EndScene(lpIMDevice());

	Main_ChangeRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
	Main_ChangeRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);

	view3->lpVtbl->Release(view3);
}

VOID Viewport_Render(lpViewport vp, lpContainer root, REAL delta){

	HRESULT r;

	Viewport_CheckInit();

	Error_Fatal(!vp||!root, "NULL passed as viewport or container to Viewport_Render()");

	vp->rendering = TRUE;

	if (0.0f != vp->smoothFOV){

		REAL coef, fov = vp->lpVP->lpVtbl->GetField(vp->lpVP);

		coef = 4.0f * (1.0f / delta);
		fov *= coef;
		fov += vp->smoothFOV;
		fov *= 1.0f / (1.0f + coef);

		vp->lpVP->lpVtbl->SetField(vp->lpVP, fov);
		if (fov == vp->smoothFOV) vp->smoothFOV = 0.0f;
	}

	if ((r = vp->lpVP->lpVtbl->Render(vp->lpVP, root->masterFrame)) == D3DRM_OK){

		Mesh_PostRenderAll(vp);

	} else {
		Error_Warn(TRUE, "Cannot render viewport");
		CHKRM(r);
	}

	vp->rendering = FALSE;
}

VOID Viewport_Remove(lpViewport dead){

	HRESULT r;

	Viewport_CheckInit();
	Error_Fatal(!dead, "NULL passed to Viewport_Remove()");

	dead->nextFree = viewportGlobs.freeList;
	viewportGlobs.freeList = dead;

	r = dead->lpVP->lpVtbl->Release(dead->lpVP);
}

VOID Viewport_SmoothSetField(lpViewport vp, REAL fov){

	vp->smoothFOV = fov;
}

VOID Viewport_SetField(lpViewport vp, REAL fov){

	Viewport_CheckInit();
	Error_Fatal(!vp, "NULL passed to Viewport_SetField()");

	vp->lpVP->lpVtbl->SetField(vp->lpVP, fov);
	vp->smoothFOV = 0.0f;
}

REAL Viewport_GetField(lpViewport vp){

	Viewport_CheckInit();
	Error_Fatal(!vp, "NULL passed to Viewport_GetField()");

	return vp->lpVP->lpVtbl->GetField(vp->lpVP);
}

__inline VOID Viewport_InverseTransform(lpViewport vp, LPVECTOR3D dest, LPVECTOR4D src){

	Viewport_CheckInit();
	Error_Fatal(!vp, "NULL passed to Viewport_InverseTransform()");
	
	vp->lpVP->lpVtbl->InverseTransform(vp->lpVP, (LPD3DVECTOR) dest, (LPD3DRMVECTOR4D) src);
}

__inline VOID Viewport_Transform(lpViewport vp, LPVECTOR4D dest, LPVECTOR3D src){

	Viewport_CheckInit();
	Error_Fatal(!vp, "NULL passed to Viewport_InverseTransform()");
	
	vp->lpVP->lpVtbl->Transform(vp->lpVP, (LPD3DRMVECTOR4D) dest, (LPD3DVECTOR) src);
}

LPVECTOR2D Viewport_WorldToScreen(lpViewport vp, LPVECTOR2D screen, LPVECTOR3D world){

	VECTOR4D v4d;

	Viewport_Transform(vp, &v4d, world);
	screen->x = v4d.x / v4d.w;
	screen->y = v4d.y / v4d.w;

	return screen;
}

LPVECTOR2D Viewport_WorldToScreenXYZ(lpViewport vp, LPVECTOR2D screen, REAL x, REAL y, REAL z){

	VECTOR4D v4d;
	VECTOR3D world = { x, y, z };

	Viewport_Transform(vp, &v4d, &world);
	screen->x = v4d.x / v4d.w;
	screen->y = v4d.y / v4d.w;

	return screen;
}

lpViewport_Pick Viewport_MakePick(lpViewport vp, ULONG x, ULONG y){

	lpViewport_Pick pick;

	if (pick = Mem_Alloc(sizeof(Viewport_Pick))){
		
		LPDIRECT3DRMPICKEDARRAY pickarray;
		ULONG numpicks, loop;
		BOOL found = FALSE;

		pick->pickArray = NULL;
	
		if (D3DRM_OK == vp->lpVP->lpVtbl->Pick(vp->lpVP, x, y, &pickarray)){

			LPDIRECT3DRMVISUAL visual;
			LPDIRECT3DRMFRAMEARRAY framearray;
			D3DRMPICKDESC pickdesc;

			pick->pickCount = numpicks = pickarray->lpVtbl->GetSize(pickarray);

			if (numpicks){
				if (pick->pickArray = Mem_Alloc(sizeof(Viewport_PickInfo) * numpicks)){

					for (loop=0 ; loop<numpicks ; loop++){
						if (D3DRM_OK == pickarray->lpVtbl->GetPick(pickarray, loop, (IDirect3DRMVisual **) &visual, &framearray, &pickdesc)){

							ULONG framecount, sub;
							LPDIRECT3DRMFRAME frame1;
							LPDIRECT3DRMFRAME3 frame3;
							lpContainer cont;
							LPDIRECT3DRMMESH mesh;
							VECTOR4D v4d;
							
							pick->pickArray[loop].group = pickdesc.lGroupIdx;
							pick->pickArray[loop].face = pickdesc.ulFaceIdx;
//							pick->pickArray[loop].position.x = pickdesc.vPosition.x;
//							pick->pickArray[loop].position.y = pickdesc.vPosition.y;
//							pick->pickArray[loop].position.z = pickdesc.vPosition.z;

							// Return the world coordinate in .position...
							v4d.x = pickdesc.vPosition.x;
							v4d.y = pickdesc.vPosition.y;
							v4d.z = pickdesc.vPosition.z;
							v4d.w = 1.0f;
							Viewport_InverseTransform(vp, &pick->pickArray[loop].position, &v4d);

							framecount = framearray->lpVtbl->GetSize(framearray);
							for (sub=0 ; sub<framecount ; sub++){
								framearray->lpVtbl->GetElement(framearray, sub, &frame1);
								frame1->lpVtbl->QueryInterface(frame1, &IID_IDirect3DRMFrame3, &frame3);
								frame1->lpVtbl->Release(frame1);

								if (cont = Container_SearchOwner(frame3)) {
									if (cont != containerGlobs.rootContainer){

										// Find any old container...
										pick->pickArray[loop].pickCont = cont;
										break;
		
									}
								}

								frame3->lpVtbl->Release(frame3);
							}

							if (Container_Mesh == cont->type){
								if (D3DRM_OK == visual->lpVtbl->QueryInterface(visual, &IID_IDirect3DRMMesh, &mesh)){
									if (cont->typeData->mesh != mesh){
										ULONG realGroup;
										if (realGroup = mesh->lpVtbl->GetAppData(mesh)){

											// The msb denotes that the group is hidden...
											realGroup &= 0x7FFFFFFF;

											pick->pickArray[loop].group = realGroup;
										}
									}
									mesh->lpVtbl->Release(mesh);
								}
							}

							visual->lpVtbl->Release(visual);
							framearray->lpVtbl->Release(framearray);

							if (found) break;
						}
					}
				}
			}
			pickarray->lpVtbl->Release(pickarray);
		}
	}

	return pick;
}

VOID Viewport_FreePick(lpViewport_Pick pick){

	if (pick){
		if (pick->pickArray) Mem_Free(pick->pickArray);
		Mem_Free(pick);
	}
}

BOOL Viewport_PickFind(lpViewport_Pick pick, lpContainer findCont, LPULONG group, LPULONG face, LPVECTOR3D position){

	if (pick){
		ULONG loop;
		lpViewport_PickInfo pinfo;

		for (loop=0 ; loop<pick->pickCount ; loop++){
			pinfo = &pick->pickArray[loop];
			if (pinfo->pickCont == findCont){
				if (group) *group = pinfo->group;
				if (face) *face = pinfo->face;
				if (position) *position = pinfo->position;
				return TRUE;
			}
		}
	}

	return FALSE;
}

lpContainer Viewport_PickSearch(lpViewport_Pick pick, BOOL (*SearchCallback)(lpContainer match, ULONG group, ULONG face, LPVECTOR3D position, LPVOID data), LPVOID data){

	if (pick){
		ULONG loop;

		for (loop=0 ; loop<pick->pickCount ; loop++){
			if (SearchCallback(pick->pickArray[loop].pickCont, pick->pickArray[loop].group, pick->pickArray[loop].face, &pick->pickArray[loop].position, data)){
				return pick->pickArray[loop].pickCont;
			}
		}
	}

	return NULL;
}

/**********************************************************************************
 ******** Viewport Static Functions
 **********************************************************************************/

static LPDIRECT3DRMFRAME3 Viewport_GetScene(lpViewport vp) {

	LPDIRECT3DRMFRAME3 camera = NULL, scene = NULL;

	vp->lpVP->lpVtbl->GetCamera(vp->lpVP, &camera);
	if (camera) {
		camera->lpVtbl->Release(camera);
		camera->lpVtbl->GetScene(camera, &scene);
		scene->lpVtbl->Release(scene);
	}

	return scene;
}

static VOID Viewport_AddList(VOID){

	Viewport *list;
	ULONG loop, count;

	Viewport_CheckInit();

	Error_Fatal(viewportGlobs.listCount+1 >= VIEWPORT_MAXLISTS, "Run out of lists");

	count = 0x00000001 << viewportGlobs.listCount;

	if (list = viewportGlobs.listSet[viewportGlobs.listCount] = 
		Mem_Alloc(sizeof(Viewport) * count)){

		viewportGlobs.listCount++;

		for (loop=1 ; loop<count ; loop++){

			list[loop-1].nextFree = &list[loop];
		}
		list[count-1].nextFree = viewportGlobs.freeList;
		viewportGlobs.freeList = list;

	} else Error_Fatal(TRUE, Error_Format("Unable to allocate %d bytes of memory for new list.\n", sizeof(Viewport) * count));
}

static VOID Viewport_RemoveAll(VOID){

	ULONG list, count, loop;
	lpViewport tempViewport;

	for (list=0 ; list<viewportGlobs.listCount ; list++){
		if (viewportGlobs.listSet[list]){
			count = 0x00000001 << list;
			for (loop=0 ; loop<count ; loop++){
				if (tempViewport = &viewportGlobs.listSet[list][loop]){
					if (tempViewport->nextFree == tempViewport){

						tempViewport->lpVP->lpVtbl->Release(tempViewport->lpVP);
	
					}
				}
			}
		}
	}
}
