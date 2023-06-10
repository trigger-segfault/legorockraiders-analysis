
#include <d3d.h>

#include "Standard.h"
#include "DirectX.h"
#include "Viewports.h"
#include "Lists.h"
#include "Errors.h"
#include "Frames.h"
#include "Lights.h"

struct LightGlobs {

	struct Light lightList[LIGHT_MAX];

} lightGlobs = { 0 };

VOID Light_Initialise(VOID) {

}

lpLight Light_Obtain(VOID) {

	ULONG loop;
	lpLight light;

	for (loop=0 ; loop<LIGHT_MAX ; loop++) {
		light = &lightGlobs.lightList[loop];
		if (!(light->flags & LIGHT_FLAG_USED)) {
			memset(light, 0, sizeof(*light));
			light->index = loop;
			light->flags |= LIGHT_FLAG_USED;
			return light;
		}
	}

	Error_Fatal(TRUE, "Run out lights");

	return NULL;
}

lpLight Light_Create(lpFrame frame, enum Light_Type type) {

	lpLight light;
	
	if (light = Light_Obtain()) {

		LPD3DLIGHT7 lightDesc = &light->lightDesc;

		Frame_SetLight(frame, light);
		light->frame = frame;

		lightDesc->dltType = type;

		lightDesc->dcvDiffuse.r = lightDesc->dcvDiffuse.g = lightDesc->dcvDiffuse.b = 1.0f;
		lightDesc->dcvDiffuse.a = 1.0f;

		lightDesc->dcvSpecular.r = lightDesc->dcvSpecular.g = lightDesc->dcvSpecular.b = 0.0f;
		lightDesc->dcvSpecular.a = 0.0f;

		lightDesc->dcvAmbient.r = lightDesc->dcvAmbient.g = lightDesc->dcvAmbient.b = 0.0f;
		lightDesc->dcvAmbient.a = 0.0f;

		lightDesc->dvPosition.x = lightDesc->dvPosition.y = lightDesc->dvPosition.z = 0.0f;
		lightDesc->dvDirection.x = lightDesc->dvDirection.y = 0.0f;
		lightDesc->dvDirection.z = 1.0f;

		lightDesc->dvRange = D3DLIGHT_RANGE_MAX;
		lightDesc->dvFalloff = 1.0f;
		lightDesc->dvAttenuation0 = 1.0f;
		lightDesc->dvAttenuation1 = lightDesc->dvAttenuation2 = 0.0f;
		lightDesc->dvTheta = 0.5f;
		lightDesc->dvPhi = 1.0f;

		DirectX_Device()->lpVtbl->SetLight(DirectX_Device(), light->index, lightDesc);
		DirectX_Device()->lpVtbl->LightEnable(DirectX_Device(), light->index, FALSE);

		Light_Switch(light, TRUE);
	}

	return light;
}

VOID Light_ViewportEnable(lpLight light, lpViewport vp, BOOL enable) {

	Error_Fatal(NULL==light&&enable, "NULL passes as light to enable on viewport");
	Error_Fatal(NULL==vp, "NULL passed as viewport");

	if (light) {
		if (enable) Viewport_AddLight(vp, light);
		else Viewport_DeleteLight(vp, light);
	} else {
		lpLight l;
		Viewport_NextLight(vp, NULL, &l, D3DNEXT_HEAD);
		while(l) {
			Viewport_DeleteLight(vp, l);
			Viewport_NextLight(vp, l, &l, D3DNEXT_NEXT);
		}
	}
}

VOID Light_PreRender(lpLight light) {

	// Adjust the light's position/direction before the rendering begins...

	LPD3DLIGHT7 lightDesc = &light->lightDesc;
	lpFrame frame = light->frame;
	VECTOR3D pos, dir;
	HRESULT r;

	if (LightType_Directional == lightDesc->dltType || LightType_Spot == lightDesc->dltType) {

		Frame_GetWorldOrientation(frame, &dir, NULL);

		lightDesc->dvDirection.x = dir.x;
		lightDesc->dvDirection.y = dir.y;
		lightDesc->dvDirection.z = dir.z;
	}

	if (LightType_Directional != lightDesc->dltType) {

		Frame_GetWorldPosition(frame, &pos);

		lightDesc->dvPosition.x = pos.x;
		lightDesc->dvPosition.y = pos.y;
		lightDesc->dvPosition.z = pos.z;
	}

	r = DirectX_Device()->lpVtbl->SetLight(DirectX_Device(), light->index, lightDesc);
	Error_DirectX(r, "SetLight");
}

VOID Light_FrameEnable(lpLight light, lpFrame frame, BOOL enable, BOOL recursive) {

	if (enable) frame->enabledLights |= (0x0000001 << light->index);
	else frame->enabledLights &= ~(0x0000001 << light->index);

	if (recursive) {
		for (frame=Frame_GetChildren(frame) ; frame ; frame=Frame_GetNextChild(frame)) {
			Light_FrameEnable(light, frame, enable, recursive);
		}
	}
}

VOID Light_Switch(lpLight light, BOOL on) {

	if (on) light->flags |= LIGHT_FLAG_ON;
	else light->flags &= ~LIGHT_FLAG_ON;
}

VOID Light_EnableLights(lpFrame frame, BOOL enable) {

	lpLight light;
	ULONG loop;

	for (loop=0 ; loop<LIGHT_MAX ; loop++) {
		light = &lightGlobs.lightList[loop];
		if (light->flags & LIGHT_FLAG_ON) {
			if (frame->enabledLights & (0x00000001 << loop)) {
				DirectX_Device()->lpVtbl->LightEnable(DirectX_Device(), light->index, enable);
			}
		}
	}
}

/*
VOID Light_ActivateChain(lpFrame frame) {

	lpLight light;

	for (light=frame->lightChain ; light ; light=light->next) {
		DirectX_Device()->lpVtbl->LightEnable(DirectX_Device(), light->index, TRUE);
	}
}

VOID Light_DeactivateAll(VOID) {

	lpLight light;
	ULONG loop;

	for (loop=0 ; loop<lightGlobs.lightCount ; loop++) {
		light = &lightGlobs.lightList[loop];
		DirectX_Device()->lpVtbl->LightEnable(DirectX_Device(), light->index, FALSE);
	}

}
*/

VOID Light_SetDiffuse(lpLight light, LPNCOLOUR colour) {

	LPD3DLIGHT7 lightDesc = &light->lightDesc;

	lightDesc->dcvDiffuse.r = colour->r;
	lightDesc->dcvDiffuse.g = colour->g;
	lightDesc->dcvDiffuse.b = colour->b;
	lightDesc->dcvDiffuse.a = 0.0f;
}

VOID Light_SetSpot(lpLight light, REAL innerAngle, REAL outerAngle, REAL falloff) {

	LPD3DLIGHT7 lightDesc = &light->lightDesc;
	
	Error_Fatal(LightType_Spot!=lightDesc->dltType, "Light is not a spotlight");
	Error_Fatal(innerAngle>outerAngle, "Inner angle must be <= outer angle");
	Error_Fatal(outerAngle>M_PI||outerAngle<0.0f, "Outer must be between 0 and PI");
	lightDesc->dvTheta = innerAngle;
	lightDesc->dvPhi = outerAngle;
	lightDesc->dvFalloff = falloff;
}

VOID Light_RemoveAll(VOID) {

	lpLight light;
	ULONG loop;

	for (loop=0 ; loop<LIGHT_MAX ; loop++) {
		light = &lightGlobs.lightList[loop];
		if (light->flags & LIGHT_FLAG_USED) {
			Light_Remove(light);
		}
	}
}

VOID Light_Remove(lpLight light) {

	Viewport_RunThrough(Light_RemoveCallback, light);
	DirectX_Device()->lpVtbl->LightEnable(DirectX_Device(), light->index, FALSE);
	light->flags &= ~LIGHT_FLAG_USED;
}

static BOOL Light_RemoveCallback(lpViewport vp, LPVOID data) {

	lpLight light = data;

	Light_ViewportEnable(light, vp, FALSE);

	return FALSE;
}

/*
lpLight Light_Create(lpFrame frame, enum Light_Type type, REAL range) {

	lpLight light = List_ObtainItem(lightGlobs.listID);

	Frame_SetLight(frame, light);
	light->frame = frame;

	light->type = type;
#ifdef _OWNLIGHTING
	light->colour.r = light->colour.g = light->colour.b = 1.0f;
	light->position.x = light->position.y = light->position.z = 0.0f;
	light->direction.z = light->direction.z = 0.0f;
	light->direction.y = 1.0f;
#else // _OWNLIGHTING
	light->data.dwSize = sizeof(D3DLIGHT2);
	light->data.dltType = type;
	light->data.dcvColor.r = 1.0f;
	light->data.dcvColor.g = 1.0f;
	light->data.dcvColor.b = 1.0f;
	light->data.dvPosition.x = 0.0f;
	light->data.dvPosition.y = 0.0f;
	light->data.dvPosition.z = 0.0f;
	light->data.dvDirection.x = 0.0f;
	light->data.dvDirection.y = 1.0f;
	light->data.dvDirection.z = 0.0f;
	light->data.dvRange = range;
	light->data.dvFalloff = 1.0f;
	light->data.dvAttenuation0 = 0.0f;
	light->data.dvAttenuation1 = 1.0f;
	light->data.dvAttenuation2 = 0.0f;
	light->data.dvTheta = 0.5f;
	light->data.dvPhi = 1.0f;

	DirectX_Direct3D()->lpVtbl->CreateLight(DirectX_Direct3D(), &light->object, NULL);
	light->object->lpVtbl->SetLight(light->object, (LPD3DLIGHT) &light->data);
#endif // _OWNLIGHTING

	return light;
}

VOID Light_ViewportEnable(lpLight light, lpViewport vp, BOOL enable) {

	Error_Fatal(NULL==light&&enable, "NULL passes as light to enable on viewport");
	Error_Fatal(NULL==vp, "NULL passed as viewport");

	if (light) {
#ifdef _OWNLIGHTING
		if (enable) Viewport_AddLight(vp, light);
		else Viewport_DeleteLight(vp, light);
#else // _OWNLIGHTING
		vp->view->lpVtbl->DeleteLight(vp->view, light->object);
		if (enable) vp->view->lpVtbl->AddLight(vp->view, light->object);
#endif // _OWNLIGHTING
	} else {
#ifdef _OWNLIGHTING
		lpLight l;
		Viewport_NextLight(vp, NULL, &l, D3DNEXT_HEAD);
#else // _OWNLIGHTING
		LPDIRECT3DLIGHT l;
		vp->view->lpVtbl->NextLight(vp->view, NULL, &l, D3DNEXT_HEAD);
#endif // _OWNLIGHTING
		while(l) {
#ifdef _OWNLIGHTING
			Viewport_DeleteLight(vp, l);
			Viewport_NextLight(vp, l, &l, D3DNEXT_NEXT);
#else // _OWNLIGHTING
			vp->view->lpVtbl->DeleteLight(vp->view, l);
			vp->view->lpVtbl->NextLight(vp->view, l, &l, D3DNEXT_NEXT);
#endif // _OWNLIGHTING
		}
	}
}

VOID Light_SetColour(lpLight light, LPNCOLOUR colour) {

#ifdef _OWNLIGHTING
	light->colour = *colour;
#else // _OWNLIGHTING
	light->data.dcvColor.r = colour->r;
	light->data.dcvColor.g = colour->g;
	light->data.dcvColor.b = colour->b;
	light->object->lpVtbl->SetLight(light->object, (LPD3DLIGHT) &light->data);
#endif // _OWNLIGHTING
}

VOID Light_SetSpot(lpLight light, REAL innerAngle, REAL outerAngle, REAL falloff) {

#ifdef _OWNLIGHTING
#else // _OWNLIGHTING
	Error_Fatal(Light_Type_Spot!=light->type, "Light is not a spotlight");
	Error_Fatal(innerAngle>outerAngle, "Inner angle must be <= outer angle");
	Error_Fatal(outerAngle>M_PI||outerAngle<0.0f, "Outer must be between 0 and PI");
	light->data.dvTheta = innerAngle;
	light->data.dvPhi = outerAngle;
	light->data.dvFalloff = falloff;
#endif // _OWNLIGHTING
}

VOID Light_Enable(lpLight light, lpFrame enableFrame) {

	lpLight other, next, last = NULL;

	List_CheckItem(lightGlobs.listID, light);

	if (light->enableFrame != enableFrame) {
		if (light->enableFrame) {
			for (other=light->enableFrame->lightChain ; other ; other=next) {
				next = other->next;
				if (other == light) {
					if (last) last->next = next;
					else light->enableFrame->lightChain = next;
					light->next = NULL;
				} else last = other;
			}
		}

		if (enableFrame) {
			light->enableFrame = enableFrame;
			light->next = enableFrame->lightChain;
			enableFrame->lightChain = light;
		} else light->enableFrame = NULL;
	}
}

VOID Light_FrameRemoved(lpFrame dead) {

	lpLight light, next;

	for (light=dead->lightChain ; light ; light=next) {
		next = light->next;
		Light_Enable(light, NULL);
	}
}

VOID Light_ActivateChain(lpFrame frame) {

	lpLight light;

	for (light=frame->lightChain ; light ; light=light->next) {

		List_CheckItem(lightGlobs.listID, light);

#ifdef _OWNLIGHTING
		light->flags |= LIGHT_FLAG_ACTIVE;
#else // _OWNLIGHTING
		light->data.dwFlags |= D3DLIGHT_ACTIVE;
		light->object->lpVtbl->SetLight(light->object, (LPD3DLIGHT) &light->data);
#endif // _OWNLIGHTING
	}
}

VOID Light_PreRender(VOID) {

	List_RunThrough(lightGlobs.listID, Light_PreRenderCallback, NULL);
}

static BOOL Light_PreRenderCallback(LPVOID object, LPVOID data) {

	lpLight light = object;
	lpFrame frame = light->frame;
	VECTOR3D pos, dir;

	if (Light_Type_Directional == light->type || Light_Type_Spot == light->type) {
		Frame_GetWorldOrientation(frame, &dir, NULL);
#ifdef _OWNLIGHTING
		light->direction = dir;
#else // _OWNLIGHTING
		light->data.dvDirection.x = dir.x;
		light->data.dvDirection.y = dir.y;
		light->data.dvDirection.z = dir.z;
#endif // _OWNLIGHTING
	}
	if (Light_Type_Directional != light->type) {
		Frame_GetWorldPosition(frame, &pos);
#ifdef _OWNLIGHTING
		light->position = pos;
#else // _OWNLIGHTING
		light->data.dvPosition.x = pos.x;
		light->data.dvPosition.y = pos.y;
		light->data.dvPosition.z = pos.z;
#endif // _OWNLIGHTING
	}

#ifndef _OWNLIGHTING
	light->object->lpVtbl->SetLight(light->object, (LPD3DLIGHT) &light->data);
#endif // _OWNLIGHTING

	return FALSE;
}

VOID Light_PostRender(VOID) {

	List_RunThrough(lightGlobs.listID, Light_PostRenderCallback, NULL);
}

static BOOL Light_PostRenderCallback(LPVOID object, LPVOID data) {

	lpLight light = object;

#ifdef _OWNLIGHTING
	light->flags &= ~LIGHT_FLAG_ACTIVE;
#else // _OWNLIGHTING
	if (light->data.dwFlags & D3DLIGHT_ACTIVE) {
		light->data.dwFlags &= ~D3DLIGHT_ACTIVE;
		light->object->lpVtbl->SetLight(light->object, (LPD3DLIGHT) &light->data);
	}
#endif // _OWNLIGHTING

	return FALSE;
}

static BOOL Light_RemoveCallback(lpViewport vp, LPVOID data) {

	lpLight light = data;
	Light_ViewportEnable(light, vp, FALSE);
	List_ReturnItem(lightGlobs.listID, light);

	return FALSE;
}

VOID Light_Remove(lpLight light) {

	LPDIRECT3DLIGHT deadLight = light->object;

//	Viewport_RemoveLight(NULL, light);
	Viewport_RunThrough(Light_RemoveCallback, light);
#ifndef _OWNLIGHTING
	deadLight->lpVtbl->Release(deadLight);
#endif // _OWNLIGHTING
}




VOID Light_RemoveAll(VOID) {

	List_RunThrough(lightGlobs.listID, Light_RemoveAllCallback, NULL);
}

static BOOL Light_RemoveAllCallback(LPVOID object, LPVOID data) {

	lpLight light = object;
	Light_Remove(light);
	return FALSE;
}
*/