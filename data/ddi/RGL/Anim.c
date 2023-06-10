
#include "Standard.h"
#include "Errors.h"
#include "Sound.h"
#include "Lists.h"
#include "Lws.h"
#include "Anim.h"

static lpAnimLink __cdecl Anim_FindLink(lpAnim anim, ULONG uid);

struct AnimGlobs {

	lpList list;
	lpList linkList;

} animGlobs = { 0 };

VOID Anim_Initialise(VOID) {

	animGlobs.list = List_Create(sizeof(struct Anim));
	animGlobs.linkList = List_Create(sizeof(struct AnimLink));
}

#ifdef _DEBUG
BOOL Anim_ShutdownCallback(lpLws lws, LPVOID data) {

	Error_Fatal(TRUE, "Unremoved Anim");

	return FALSE;
}
#endif // _DEBUG

VOID Anim_Shutdown(VOID) {

#ifdef _DEBUG
	List_RunThrough(animGlobs.list, Anim_ShutdownCallback, NULL);
#endif // _DEBUG
	List_Remove(animGlobs.list);
	List_Remove(animGlobs.linkList);
}

lpAnim Anim_Create(lpFrame frame) {

	lpAnim anim = List_ObtainItem(animGlobs.list);

	anim->rootFrame = Frame_Create(frame);

	return anim;
}

lpAnimLink Anim_AddLws(lpAnim anim, lpLws lws, lpFrame frame, ULONG uid) {

	lpAnimLink newLink;

	List_CheckItem(animGlobs.list, anim);

	newLink = List_ObtainItem(animGlobs.linkList);
	newLink->next = anim->chain;
	anim->chain = newLink;
	newLink->frame = frame;
	newLink->uid = uid;
	newLink->lws = lws;

	Frame_SetFlags(newLink->frame, FRAME_FLAG_TERMINATE, TRUE);

	return newLink;
}

VOID Anim_LoadLws(lpAnim anim, LPUCHAR fname, ULONG loadFlags, BOOL useShared, ULONG uid) {

	lpFrame frame = Frame_Create(anim->rootFrame);
	lpAnimLink link;
	lpLws lws;

	Error_Fatal(NULL == anim, "NULL passed as Anim to Anim_LoadLws()");
	List_CheckItem(animGlobs.list, anim);

	if (lws = Lws_Load(fname, frame, loadFlags, useShared)) {

		link = Anim_AddLws(anim, lws, frame, uid);
		link->flags |= ANIMLINK_FLAG_LOADED;
		Lws_ClearSetup(lws);

	} else Frame_Remove(frame, TRUE);	
}

VOID Anim_SetSound(lpAnim anim, ULONG uid, lpSound sound) {

	lpAnimLink animLink;

	Error_Fatal(NULL == anim, "NULL passed as Anim to Anim_SetSound()");
	
	if (animLink = Anim_FindLink(anim, uid)) {
		animLink->sound = sound;
	}
}

lpFrame Anim_GetCamera(lpAnim anim, LPREAL fov) {

	Error_Fatal(NULL == anim, "NULL passed as Anim to Anim_GetCamera()");

	if (anim->currLink) return Lws_GetCamera(anim->currLink->lws, fov);
	else return NULL;
}

__inline lpFrame Anim_GetFrame(lpAnim anim) {

	Error_Fatal(NULL == anim, "NULL passed as Anim to Anim_GetFrame()");

	return anim->rootFrame;
}


lpFrame Anim_FindFrame(lpAnim anim, LPUCHAR name, ULONG instance) {

	Error_Fatal(NULL == anim, "NULL passed as Anim to Anim_FindFrame()");

	if (anim->currLink) return Lws_FindFrame(anim->currLink->lws, name, instance);
	else return NULL;
}

lpFrame Anim_FindFrame2(lpAnim anim, LPUCHAR name, ULONG checkLength, ULONG occurance) {

	Error_Fatal(NULL == anim, "NULL passed as Anim to Anim_FindFrame2()");

	if (anim->currLink) return Lws_FindFrame2(anim->currLink->lws, name, checkLength, occurance);
	else return NULL;
}

static lpAnimLink Anim_FindLink(lpAnim anim, ULONG uid) {

	lpAnimLink link;

	for (link=anim->chain ; link ; link=link->next) {

		if (link->uid == uid) return link;
	}

	return NULL;
}

VOID Anim_UnSet(lpAnim anim) {

	Error_Fatal(NULL == anim, "NULL passed as Anim to Anim_UnSet()");
	List_CheckItem(animGlobs.list, anim);

	if (anim->currLink) {
		Frame_SetFlags(anim->currLink->frame, FRAME_FLAG_TERMINATE, TRUE);
		anim->currLink = NULL;
	}
}

__inline ULONG Anim_Get(lpAnim anim) {

	Error_Fatal(NULL == anim, "NULL passed as Anim to Anim_Get()");

	return anim->currLink->uid;
}

BOOL Anim_Set(lpAnim anim, ULONG uid) {

	Error_Fatal(NULL == anim, "NULL passed as Anim to Anim_Set()");
	List_CheckItem(animGlobs.list, anim);

	if (anim->currLink) Frame_SetFlags(anim->currLink->frame, FRAME_FLAG_TERMINATE, TRUE);

	if (anim->currLink = Anim_FindLink(anim, uid)) {

		Frame_SetFlags(anim->currLink->frame, FRAME_FLAG_TERMINATE, FALSE);

		return TRUE;
	}

	return FALSE;
}

VOID Anim_TriggerSound(lpAnim anim) {

	if (anim->currLink && anim->currLink->sound) {
		lpSound sound = Sound_Play(anim->currLink->sound, FALSE, FALSE);
		Sound_SetFrame(sound, anim->currLink->frame);
	}
}

VOID Anim_SetTime(lpAnim anim, REAL time) {

	Error_Fatal(NULL == anim, "NULL passed as Anim to Anim_SetTime()");
	List_CheckItem(animGlobs.list, anim);

	if (anim->currLink) {
		Lws_SetTime(anim->currLink->lws, time);
	}
}

ULONG Anim_GetFrameCount(lpAnim anim) {

	Error_Fatal(NULL == anim, "NULL passed as Anim to Anim_GetFrameCount()");
	List_CheckItem(animGlobs.list, anim);

	if (anim->currLink) {
		return Lws_GetFrameCount(anim->currLink->lws);
	}

	return 0;
}

REAL Anim_GetTime(lpAnim anim) {

	Error_Fatal(NULL == anim, "NULL passed as Anim to Anim_GetTime()");
	List_CheckItem(animGlobs.list, anim);
	
	if (anim->currLink) {
		return Lws_GetTime(anim->currLink->lws);
	}

	return 0.0f;
}

VOID Anim_Remove(lpAnim anim) {

	lpAnimLink link, next;

	Error_Fatal(NULL == anim, "NULL passed as Anim to Anim_Remove()");
	List_CheckItem(animGlobs.list, anim);

	for (link=anim->chain ; link ; link=next) {

		next = link->next;

		if (link->flags & ANIMLINK_FLAG_LOADED) {
			Lws_Remove(link->lws);
			Frame_Remove(link->frame, FALSE);
		}

		List_ReturnItem(animGlobs.linkList, link);
	}

	Frame_Remove(anim->rootFrame, FALSE);

	List_ReturnItem(animGlobs.list, anim);
}
