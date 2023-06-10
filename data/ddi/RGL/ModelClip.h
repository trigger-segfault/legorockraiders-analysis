
#ifndef _RGL_MODELCLIP_H_
#define _RGL_MODELCLIP_H_

#include "Maths.h"

struct ModelClip {

	BOX3D box;
	VECTOR3D vectorList[8];
	struct Frame *frame;
};

typedef struct ModelClip		*lpModelClip;

#ifndef _AUTOPROTOTYPES
// Auto Prototypes
extern VOID __cdecl ModelClip_Initialise(VOID);
extern lpModelClip __cdecl ModelClip_Create(struct Frame *frame, struct Viewport *vp);
extern VOID __cdecl ModelClip_Remove(struct ModelClip *modelClip, struct Viewport *vp);
extern VOID __cdecl ModelClip_SetBox(struct ModelClip *modelClip, LPBOX3D box);
extern LPBOX3D __cdecl ModelClip_GetBox(struct ModelClip *modelClip);
extern struct Frame *__cdecl ModelClip_GetFrame(struct ModelClip *modelClip);
extern VOID __cdecl ModelClip_Enable(struct ModelClip *modelClip, BOOL enable);
extern VOID __cdecl ModelClip_Process(struct Viewport *vp, struct Frame *camera, REAL safeDistance);
extern BOOL __cdecl ModelClip_IsClipped(struct ModelClip *modelClip);
// Auto Prototypes
#endif // !_AUTOPROTOTYPES

#endif // _RGL_MODELCLIP_H_
