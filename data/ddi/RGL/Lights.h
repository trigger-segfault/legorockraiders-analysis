
#ifndef _RGL_LIGHTS_H_
#define _RGL_LIGHTS_H_

enum LightType {

	LightType_Point = 1,
	LightType_Spot = 2,
	LightType_Directional = 3,
};

#ifdef _RGL 

#include <d3d.h>

#define LIGHT_MAX				32				// One ULONG per frame to describe which lights effect it

#define LIGHT_FLAG_USED			0x0000001
#define LIGHT_FLAG_ON			0x0000002

/*
#ifdef _OWNLIGHTING
#else // _OWNLIGHTING
#endif // _OWNLIGHTING
*/

struct Light {

	ULONG index;
	D3DLIGHT7 lightDesc;

	struct Frame *frame, *enableFrame;
	struct Light *next, *viewportNext;

	ULONG flags;
};

/*

#define LIGHT_FLAG_ACTIVE		0x0001

struct Light {

	enum Light_Type type;
	
#ifdef _OWNLIGHTING
	NCOLOUR colour;
	VECTOR3D position, direction;
	struct Light *viewportNext;
#else // _OWNLIGHTING
	LPDIRECT3DLIGHT object;
	D3DLIGHT2 data;
#endif // _OWNLIGHTING
	
	struct Light *next;
	struct Frame *enableFrame;
	struct Frame *frame;

	UWORD flags;
};
*/

#endif // _RGL

typedef struct Light				*lpLight;

// Auto Prototypes
extern unsigned __int64 __stdcall Int64ShllMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern __int64 __stdcall Int64ShraMod32(__int64 Value,unsigned long ShiftCount);
extern unsigned __int64 __stdcall Int64ShrlMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern void *__cdecl GetFiberData(void );
extern void *__cdecl GetCurrentFiber(void );
extern void __cdecl Light_Initialise(void );
extern struct Light *__cdecl Light_Obtain(void );
extern struct Light *__cdecl Light_Create(struct Frame *frame,int type);
extern void __cdecl Light_ViewportEnable(struct Light *light,struct Viewport *vp,int enable);
extern void __cdecl Light_PreRender(struct Light *light);
extern void __cdecl Light_FrameEnable(struct Light *light,struct Frame *frame,int enable,int recursive);
extern void __cdecl Light_Switch(struct Light *light,int on);
extern void __cdecl Light_EnableLights(struct Frame *frame,int enable);
extern void __cdecl Light_SetDiffuse(struct Light *light,struct NCOLOUR *colour);
extern void __cdecl Light_SetSpot(struct Light *light,float innerAngle,float outerAngle,float falloff);
extern void __cdecl Light_RemoveAll(void );
extern void __cdecl Light_Remove(struct Light *light);
static int __cdecl Light_RemoveCallback(struct Viewport *vp,void *data);
// Auto Prototypes

#endif // !_RGL_LIGHTS_H_
