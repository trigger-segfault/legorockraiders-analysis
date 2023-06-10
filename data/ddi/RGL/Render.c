
#include "Standard.h"
#include "DirectX.h"
#include "Mesh.h"
#include "Mem.h"
#include "Frames.h"
#include "Sprites.h"
#include "Errors.h"
#include "Lights.h"
#include "Render.h"

struct RenderGlobs {

	LPDIRECTDRAWSURFACE7 currTexture[D3DDP_MAXTEXCOORD];
	struct RenderEntry *entryList;
	ULONG entryListSize, entryListCount;

	ULONG beginSceneCount;

} renderGlobs = { 0 };

VOID Render_Initialise(VOID) {

	ULONG loop;

	for (loop=0 ; loop<8 ; loop++) {
		Render_SetTextureStageState(loop, D3DTSS_MINFILTER, D3DTFN_LINEAR);
		Render_SetTextureStageState(loop, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
	}
}

VOID Render_DarkenScreen(COLOUR colour) {

	D3DVIEWPORT7 viewport;
	struct LocalVertex { VECTOR4D position; COLOUR colour; } vertexList[4];
	HRESULT r;

	vertexList[0].position.x = 0.0f;
	vertexList[0].position.y = 0.0f;
	vertexList[0].position.z = 0.0f;
	vertexList[0].position.w = 1.0f;
	vertexList[0].colour = colour;
	vertexList[1].position.x = (REAL) DirectX_GetWidth();
	vertexList[1].position.y = 0.0f;
	vertexList[1].position.z = 0.0f;
	vertexList[1].position.w = 1.0f;
	vertexList[1].colour = colour;
	vertexList[2].position.x = (REAL) DirectX_GetWidth();
	vertexList[2].position.y = (REAL) DirectX_GetHeight();
	vertexList[2].position.z = 0.0f;
	vertexList[2].position.w = 1.0f;
	vertexList[2].colour = colour;
	vertexList[3].position.x = 0.0f;
	vertexList[3].position.y = (REAL) DirectX_GetHeight();
	vertexList[3].position.z = 0.0f;
	vertexList[3].position.w = 1.0f;
	vertexList[3].colour = colour;

	viewport.dwX = 0;
	viewport.dwY = 0;
	viewport.dwWidth = DirectX_GetWidth();
	viewport.dwHeight = DirectX_GetHeight();
	viewport.dvMinZ = 0.0f;
	viewport.dvMaxZ = 1.0f;

	DirectX_Device()->lpVtbl->SetViewport(DirectX_Device(), &viewport);

	Render_BeginScene();

	Render_SetState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
	Render_SetState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ZERO);
	Render_SetState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCCOLOR);
	Render_SetState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
	Render_SetState(D3DRENDERSTATE_ZENABLE, D3DZB_FALSE);
	Render_SetState(D3DRENDERSTATE_LIGHTING, FALSE);
	
	Render_SetTexture(0, NULL);

	r = DirectX_Device()->lpVtbl->DrawPrimitive(DirectX_Device(), D3DPT_TRIANGLEFAN, D3DFVF_XYZRHW|D3DFVF_DIFFUSE, vertexList, 4, 0);
	Error_DirectX(r, "DrawPrimitive");

	Render_EndScene();
}

VOID Render_BeginScene(VOID) {

	HRESULT r;

	if (0 == renderGlobs.beginSceneCount) {
		r = DirectX_Device()->lpVtbl->BeginScene(DirectX_Device());
		Error_DirectX(r, "BeginScene");
	}

	renderGlobs.beginSceneCount++;
}

VOID Render_EndScene(VOID) {

	HRESULT r;

	Error_Fatal(0 == renderGlobs.beginSceneCount, "Render_EndScene() called too many time");

	renderGlobs.beginSceneCount--;

	if (0 == renderGlobs.beginSceneCount) {
		r = DirectX_Device()->lpVtbl->EndScene(DirectX_Device());
		Error_DirectX(r, "EndScene");
	}
}

VOID Render_ResetTextures(VOID) {

	ULONG loop;

	for (loop=0 ; loop<D3DDP_MAXTEXCOORD ; loop++) {
		DirectX_Device()->lpVtbl->SetTexture(DirectX_Device(), loop, NULL);
		renderGlobs.currTexture[loop] = NULL;
	}
}

BOOL Render_SetupAlphaStates(UWORD renderFlags) {

	if (renderFlags & RENDER_FLAG_SUBTRACTIVE) {

		Render_SetState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		Render_SetState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ZERO);
		Render_SetState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCCOLOR);

	} else if (renderFlags & RENDER_FLAG_ADDITIVE) {

		Render_SetState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		Render_SetState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
		Render_SetState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);

	} else if (renderFlags & RENDER_FLAG_TRANSPARENT) {

		Render_SetState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		Render_SetState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
		Render_SetState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

	} else return FALSE;
		
	Render_SetState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
	Render_SetState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);

	return TRUE;
}

__inline VOID Render_SetTextureStageState(ULONG index, D3DTEXTURESTAGESTATETYPE state, ULONG value) { 

	HRESULT r = DirectX_Device()->lpVtbl->SetTextureStageState(DirectX_Device(), index, state, value);
	Error_DirectX(r, "SetRenderState");
}

__inline VOID Render_SetState(D3DRENDERSTATETYPE type, ULONG value) {

	HRESULT r = DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), type, value);
	Error_DirectX(r, "SetRenderState");
}

__inline VOID Render_SetTexture(ULONG index, LPDIRECTDRAWSURFACE7 texture) {

	if (texture != renderGlobs.currTexture[index]) {
		DirectX_Device()->lpVtbl->SetTexture(DirectX_Device(), index, texture);
		renderGlobs.currTexture[index] = texture;
	}
}

__inline lpRenderEntry Render_GetEntry(VOID) {

	if (renderGlobs.entryListCount == renderGlobs.entryListSize) {
		renderGlobs.entryListSize += 10;
		renderGlobs.entryList = Mem_ReAlloc(renderGlobs.entryList, sizeof(renderGlobs.entryList[0]) * renderGlobs.entryListSize);
	}

	return &renderGlobs.entryList[renderGlobs.entryListCount++];
}

__inline VOID Render_AddMeshEntry(lpMesh mesh, lpMeshGroup group, lpFrame frame) {

	lpRenderEntry entry = Render_GetEntry();

	entry->type = RenderEntryType_Mesh;
	entry->mesh = mesh;
	entry->meshGroup = group;
	entry->frame = frame;
}

__inline VOID Render_AddSpriteEntry(lpTestSprite sprite) {

	lpRenderEntry entry = Render_GetEntry();

	entry->type = RenderEntryType_Sprite;
	entry->sprite = sprite;
	entry->frame = sprite->frame;
}

__inline lpTexture Render_GetEntryTexture(lpRenderEntry entry, ULONG index) {

	switch (entry->type) {
	case RenderEntryType_Mesh:		return entry->meshGroup->texture[index];			break;
	case RenderEntryType_Sprite:	return (0==index)?entry->sprite->texture:NULL;		break;
	}

	Error_Fatal(TRUE, "Unknown RenderEntryType");

	return NULL;
}

__inline ULONG Render_GetEntryFlags(lpRenderEntry entry) {

	switch (entry->type) {
	case RenderEntryType_Mesh:		return entry->meshGroup->renderFlags;				break;
	case RenderEntryType_Sprite:	return entry->sprite->renderFlags;					break;
	}

	Error_Fatal(TRUE, "Unknown RenderEntryType");

	return 0;
}

int Render_SortEntryListCallback(const void *a, const void *b) {

	ULONG loop;
	lpRenderEntry aEntry = (lpRenderEntry) a;
	lpRenderEntry bEntry = (lpRenderEntry) b;
	ULONG aFlags = Render_GetEntryFlags(aEntry);
	ULONG bFlags = Render_GetEntryFlags(bEntry);
	lpTexture aTexture;
	lpTexture bTexture;

	if ((aFlags & RENDER_FLAG_RENDERFIRST) && !(bFlags & RENDER_FLAG_RENDERFIRST)) return -1;
	if (!(aFlags & RENDER_FLAG_RENDERFIRST) && (bFlags & RENDER_FLAG_RENDERFIRST)) return 1;

//	if ((aFlags & RENDER_FLAG_ADDITIVE) && !(bFlags & RENDER_FLAG_ADDITIVE)) return 1;
//	if (!(aFlags & RENDER_FLAG_ADDITIVE) && (bFlags & RENDER_FLAG_ADDITIVE)) return -1;

//	if ((aFlags & RENDER_FLAG_SUBTRACTIVE) && !(bFlags & RENDER_FLAG_SUBTRACTIVE)) return 1;
//	if (!(aFlags & RENDER_FLAG_SUBTRACTIVE) && (bFlags & RENDER_FLAG_SUBTRACTIVE)) return -1;

	if ((aFlags & RENDER_FLAG_ALPHAMASK) && !(bFlags & RENDER_FLAG_ALPHAMASK)) return 1;
	if (!(aFlags & RENDER_FLAG_ALPHAMASK) && (bFlags & RENDER_FLAG_ALPHAMASK)) return -1;

	for (loop=0 ; loop<D3DDP_MAXTEXCOORD ; loop++) {
		
		aTexture = Render_GetEntryTexture(aEntry, loop);
		bTexture = Render_GetEntryTexture(bEntry, loop);

		if (aTexture != bTexture) {

			if (NULL == aTexture) return -1;
			if (NULL == bTexture) return 1;

			if (Texture_GetPriority(aTexture) > Texture_GetPriority(bTexture)) return -1;
			if (Texture_GetPriority(aTexture) < Texture_GetPriority(bTexture)) return 1;

			if (aTexture > bTexture) return -1;
			if (aTexture < bTexture) return 1;
		}
	}

	if (aEntry->frame > bEntry->frame) return -1;
	if (aEntry->frame < bEntry->frame) return 1;

	return 0;
}

ULONG Render_ProcessList(ULONG ambientColour) {

	ULONG loop, polysDrawn = 0;
	lpRenderEntry entry;
	lpFrame lastRenderedFrame = NULL;

	qsort(renderGlobs.entryList, renderGlobs.entryListCount, sizeof(renderGlobs.entryList[0]), Render_SortEntryListCallback);

	Render_BeginScene();

	for (loop=0 ; loop<renderGlobs.entryListCount ; loop++) {
	
		entry = &renderGlobs.entryList[loop];

		// Enable the lights that affect this frame...

		if (lastRenderedFrame != entry->frame) {
			if (lastRenderedFrame) Light_EnableLights(lastRenderedFrame, FALSE);
			Light_EnableLights(entry->frame, TRUE);
		}

		switch (entry->type) {
		case RenderEntryType_Mesh:
			
			polysDrawn += Mesh_RenderGroup(entry->mesh, entry->meshGroup, entry->frame, lastRenderedFrame);
			break;

		case RenderEntryType_Sprite:

			polysDrawn += Sprite_Render(entry->sprite);
			break;

		}

		lastRenderedFrame = entry->frame;
	}

//	r = DirectX_Device()->lpVtbl->EndScene(DirectX_Device());
//	Error_DirectX(r, "EndScene");
	Render_EndScene();

	if (lastRenderedFrame) Light_EnableLights(lastRenderedFrame, FALSE);

	for (loop=0 ; loop<renderGlobs.entryListCount ; loop++) {

		entry = &renderGlobs.entryList[loop];

		switch (entry->type) {
		case RenderEntryType_Mesh:			Mesh_Reset(entry->mesh);			break;
		}
	}

	renderGlobs.entryListCount = 0;

	return polysDrawn;
}
