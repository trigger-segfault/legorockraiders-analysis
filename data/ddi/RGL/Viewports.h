
#ifndef _RGL_VIEWPORTS_H_
#define _RGL_VIEWPORTS_H_

#ifdef _RGL

#include <d3d.h>
#include "Maths.h"

#define VIEWPORT_MAX					10

#define VIEWPORT_FLAG_USED				0x00000001
#define VIEWPORT_FLAG_RELATIVE			0x00000002
#define VIEWPORT_FLAG_TABLEFOGENABLED	0x00000004
#define VIEWPORT_FLAG_VERTEXFOGENABLED	0x00000008

struct Viewport {

	D3DVIEWPORT7 viewport;
	AREA2Dr shape;

	REAL fov, frontClip, backClip, aspect;
	MATRIX4D projMat;

	MATRIX4D batchMatrix;
	REAL halfWidth, halfHeight;

	ULONG bgColour, ambientColour;
	REAL fogStart, fogEnd;
	COLOUR fogColour;

	ULONG flags;

	struct Light *lightList;
	struct List *modelClipList;
};

#endif // _RGL

typedef struct Viewport						*lpViewport;

// Auto Prototypes
extern unsigned __int64 __stdcall Int64ShllMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern __int64 __stdcall Int64ShraMod32(__int64 Value,unsigned long ShiftCount);
extern unsigned __int64 __stdcall Int64ShrlMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern void *__cdecl GetFiberData(void );
extern void *__cdecl GetCurrentFiber(void );
extern struct List *__cdecl Viewport_GetModelClipList(struct Viewport *vp);
extern struct Viewport *__cdecl Viewport_Create(float x,float y,float width,float height);
extern struct Viewport *__cdecl Viewport_CreatePixel(unsigned long x,unsigned long y,unsigned long width,unsigned long height);
static void __cdecl Viewport_Setup(struct Viewport *vp);
extern int __cdecl Viewport_ReconfigureCallback(struct Viewport *vp,void *data);
extern void __cdecl Viewport_Reconfigure(void );
extern void __cdecl Viewport_SetBackgroundColourAlpha(struct Viewport *vp,float r,float g,float b,float a);
extern void __cdecl Viewport_Clear(struct Viewport *vp,int backGround,int zBuffer);
extern void __cdecl Viewport_SetFOV(struct Viewport *vp,float fov);
extern void __cdecl Viewport_SetClip(struct Viewport *vp,float front,float back);
extern float __cdecl Viewport_GetBackClip(struct Viewport *vp);
static void __cdecl Viewport_SetProjectionMatrix(struct Viewport *vp);
extern unsigned long __cdecl Viewport_GetX(struct Viewport *vp);
extern unsigned long __cdecl Viewport_GetY(struct Viewport *vp);
extern unsigned long __cdecl Viewport_GetWidth(struct Viewport *vp);
extern unsigned long __cdecl Viewport_GetHeight(struct Viewport *vp);
extern void __cdecl Viewport_SetupBatchTransform(struct Viewport *vp,struct Frame *frame,struct Frame *camera);
extern void __cdecl Viewport_BatchTransform(struct Viewport *vp,struct VECTOR3D *dest,struct VECTOR3D *src);
extern void __cdecl Viewport_BatchTransform4D(struct Viewport *vp,struct VECTOR4D *dest,struct VECTOR4D *src);
extern void __cdecl Viewport_Transform(struct Viewport *vp,struct Frame *frame,struct Frame *camera,struct VECTOR3D *dest,struct VECTOR3D *src);
extern void __cdecl Viewport_InverseTransform(struct Viewport *vp,struct Frame *frame,struct Frame *camera,struct VECTOR3D *dest,struct VECTOR3D *src);
extern struct DirectXBufferDump *__cdecl Viewport_GrabZBuffer(struct Viewport *vp);
extern void __cdecl Viewport_Set(struct Viewport *vp,struct Frame *camera);
extern unsigned long __cdecl Viewport_Render(struct Viewport *vp,struct Frame *scene,struct Frame *camera);
extern void __cdecl Viewport_Remove(struct Viewport *dead);
extern void __cdecl Viewport_RemoveAll(void );
extern int __cdecl Viewport_RunThrough(int (*Callback)(struct Viewport *,void *),void *data);
extern void __cdecl Viewport_AddLight(struct Viewport *vp,struct Light *light);
extern void __cdecl Viewport_DeleteLight(struct Viewport *vp,struct Light *light);
extern void __cdecl Viewport_NextLight(struct Viewport *vp,struct Light *light,struct Light **result ,unsigned long flags);
extern VOID __cdecl Viewport_SetAmbientLight(struct Viewport *vp, REAL r, REAL g, REAL b);
extern BOOL __cdecl Viewport_EnableFog(lpViewport vp, BOOL enabled);
extern VOID __cdecl Viewport_SetFogRange(lpViewport vp, REAL start, REAL end);
extern VOID __cdecl Viewport_SetFogColour(lpViewport vp, COLOUR colour);
// Auto Prototypes

#endif // !_RGL_VIEWPORTS_H_
