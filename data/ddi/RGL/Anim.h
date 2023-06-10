
#ifndef _RGL_ANIM_H
#define _RGL_ANIM_H

#define ANIMLINK_FLAG_LOADED		0x00000001

struct Anim {

	struct AnimLink *chain;
	struct Frame *rootFrame;
	struct AnimLink *currLink;
	REAL lastTime;
};

struct AnimLink {

	ULONG uid;
	struct Lws *lws;
	struct Sound *sound;
	struct Frame *frame;
	struct AnimLink *next;
	ULONG flags;
};

typedef struct Anim				*lpAnim;
typedef struct AnimLink			*lpAnimLink;

// Autoprototypes
#ifndef _PROTOTYPES
extern ULONG __cdecl Anim_GetFrameCount(lpAnim anim);
extern VOID __cdecl Anim_Initialise(VOID);
extern VOID __cdecl Anim_Shutdown(VOID);
extern lpAnim __cdecl Anim_Create(struct Frame *frame);
extern lpAnimLink __cdecl Anim_AddLws(lpAnim anim, struct Lws *lws, struct Frame *frame, ULONG uid);
extern VOID __cdecl Anim_LoadLws(lpAnim anim, LPUCHAR fname, ULONG loadFlags, BOOL useShared, ULONG uid);
extern ULONG __cdecl Anim_Get(lpAnim anim);
extern BOOL __cdecl Anim_Set(lpAnim anim, ULONG uid);
extern VOID __cdecl Anim_UnSet(lpAnim anim);
extern VOID __cdecl Anim_SetTime(lpAnim anim, REAL time);
extern REAL __cdecl Anim_GetTime(lpAnim anim);
extern VOID __cdecl Anim_Remove(lpAnim anim);
extern VOID __cdecl Anim_SetSound(lpAnim anim, ULONG uid, struct Sound *sound);
extern struct Frame * __cdecl Anim_GetCamera(lpAnim anim, LPREAL fov);
extern struct Frame * __cdecl Anim_FindFrame(lpAnim anim, LPUCHAR name, ULONG instance);
extern struct Frame * __cdecl Anim_FindFrame2(lpAnim anim, LPUCHAR name, ULONG matchCount, ULONG occurance);
extern struct Frame *__cdecl Anim_GetFrame(struct Anim *anim);
extern VOID __cdecl Anim_TriggerSound(struct Anim *anim);
#endif // !_PROTOTYPES
// Autoprototypes



#endif // _RGL_ANIM_H
