
#ifndef _RGL_FRAMES_H_
#define _RGL_FRAMES_H_

#include "Maths.h"
#include "Mesh.h"

/************************************************************************************************************************
 **** Constants and enumerations available outside the library...
 ************************************************************************************************************************/

#define FRAME_MAXDEPTH			10

#define FRAME_FLAG_HIDDEN				0x0001		// Hide the visual, but still process hierarchy.
#define FRAME_FLAG_ABSOLUTEPRIORITY		0x0002
#define FRAME_FLAG_TERMINATE			0x0004		// Abort render at this frame for all decendants

#define FRAME_FLAG_INTERNALMASK			0xff00		// Mask for internally used flags.
#define FRAME_FLAG_DIRTY				0x8000
#define FRAME_FLAG_CLIPTERMINATE		0x4000		// Same as FRAME_FLAG_TERMINATE, but only set by clipping routines.

#ifdef _RGL
#define Frame_SetFlags(fr,fl,s)			Frame_SetFlags_Internal((fr),(fl),(s))
#define Frame_TestFlags(fr,fl,a)		Frame_TestFlags_Internal((fr),(fl),(a))
#else // _RGL
#define Frame_SetFlags(fr,fl,s)			Frame_SetFlags_External((fr),(fl),(s))
#define Frame_TestFlags(fr,fl,a)		Frame_TestFlags_External((fr),(fl),(a))
#endif // _RGL

enum FrameAttachmentType {

	FrameAttachmentType_None = 0,
	FrameAttachmentType_Mesh,
	FrameAttachmentType_Light,

	FrameAttachmentType_Count
};

#ifdef _RGL

/************************************************************************************************************************
 **** Internal library structures
 ************************************************************************************************************************/

struct Frame {

	LPUCHAR name;

	MATRIX4D localMatrix;
	MATRIX4D worldMatrix;

	LPVOID attachment;
	enum FrameAttachmentType attachmentType;
	ULONG enabledLights;

	UWORD flags;
	SWORD priority;

	struct Frame *parent, *children;			// Hierachy pointers...
	struct Frame *prevSibling, *nextSibling;
};

#endif // _RGL

/************************************************************************************************************************
 **** Typedefs available outside the library...
 ************************************************************************************************************************/

typedef struct Frame				*lpFrame;

#ifdef _DEBUG
#define Frame_Create(p)				Frame_Debug_Create((p),__FILE__,__LINE__)
#endif // _DEBUG

// Auto Prototypes
extern unsigned __int64 __stdcall Int64ShllMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern __int64 __stdcall Int64ShraMod32(__int64 Value,unsigned long ShiftCount);
extern unsigned __int64 __stdcall Int64ShrlMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern void *__cdecl GetFiberData(void );
extern void *__cdecl GetCurrentFiber(void );
extern void __cdecl Frame_Initialise(void );
extern struct Frame *__cdecl Frame_Debug_Create(struct Frame *parent, unsigned char *file, unsigned long line);
#ifndef _DEBUG
extern struct Frame *__cdecl Frame_Create(struct Frame *parent);
#endif // !_DEBUG
extern struct Frame *__cdecl Frame_Find(struct Frame *frame,unsigned char *name);
extern unsigned char *__cdecl Frame_GetName(struct Frame *frame);
extern void __cdecl Frame_SetName(struct Frame *frame,unsigned char *name);
extern void __cdecl Frame_Remove(struct Frame *dead,int recursive);
//extern void __cdecl Frame_SetWorldPosition(struct Frame *frame,struct VECTOR3D *pos);
static void __cdecl Frame_SetLocalTransform(struct Frame *frame,float (*mat)[4]);
extern void __cdecl Frame_SetPriority(struct Frame *frame, signed short priority, int absolute);
extern void __cdecl Frame_MakeIdentity(struct Frame *frame);
extern void __cdecl Frame_SetPosition(struct Frame *frame,struct VECTOR3D *pos);
extern void __cdecl Frame_SetWorldPosition(struct Frame *frame,struct VECTOR3D *pos);
extern void __cdecl Frame_AddTranslation(struct Frame *frame,struct VECTOR3D *offset);
extern void __cdecl Frame_SetScale(struct Frame *frame,struct VECTOR3D *scale);
extern void __cdecl Frame_AddRotation(struct Frame *frame,struct VECTOR3D *vec,float angle,int before);
extern void __cdecl Frame_SetRotation(struct Frame *frame,struct VECTOR3D *vec,float angle);
extern void __cdecl Frame_SetOrientation(struct Frame *frame,struct VECTOR3D *dir,struct VECTOR3D *up);
extern void __cdecl Frame_SetWorldOrientation(struct Frame *frame,struct VECTOR3D *dir,struct VECTOR3D *up);
extern void __cdecl Frame_GetRelativeTransform(struct Frame *frame,struct Frame *reference,float (*mat)[4]);
extern void __cdecl Frame_GetWorldTransform(struct Frame *frame,float (*mat)[4]);
extern void __cdecl Frame_SetTransform(struct Frame *frame,float (*mat)[4]);
extern void __cdecl Frame_GetRelativePosition(struct Frame *frame,struct Frame *reference,struct VECTOR3D *pos);
extern void __cdecl Frame_GetWorldOffset(struct Frame *frame,struct VECTOR3D *pos,struct VECTOR3D *offset);
extern void __cdecl Frame_GetRelativeOffset(struct Frame *frame,struct Frame *reference,struct VECTOR3D *pos,struct VECTOR3D *offset);
extern void __cdecl Frame_GetWorldPosition(struct Frame *frame,struct VECTOR3D *pos);
extern void __cdecl Frame_GetPosition(struct Frame *frame,struct VECTOR3D *pos);
extern void __cdecl Frame_GetOrientation(struct Frame *frame,struct VECTOR3D *dir,struct VECTOR3D *up);
extern void __cdecl Frame_GetRelativeOrientation(struct Frame *frame,struct Frame *reference,struct VECTOR3D *dir,struct VECTOR3D *up);
extern void __cdecl Frame_GetWorldOrientation(struct Frame *frame,struct VECTOR3D *dir,struct VECTOR3D *up);
extern struct Mesh *__cdecl Frame_GetMesh(struct Frame *frame);
extern void __cdecl Frame_SetMesh(struct Frame *frame,struct Mesh *mesh);
extern void __cdecl Frame_SetLight(struct Frame *frame,struct Light *light);
extern void __cdecl Frame_RemoveAttachment(lpFrame frame);
static void __cdecl Frame_UpdateWorldMatrix(struct Frame *frame);
static void __cdecl Frame_MultiplyMatrix(struct Frame *frame,float (*a)[4],float (*b)[4]);
extern void __cdecl Frame_BuildRenderList(struct Frame *frame,float (*mat)[4]);
extern void __cdecl Frame_SetParent(struct Frame *frame,struct Frame *parent);
extern struct Frame *__cdecl Frame_GetParent(struct Frame *frame);
extern void __cdecl Frame_IdentityCheck(struct Frame *frame);
extern int __cdecl Frame_IsDecendant(struct Frame *frame,struct Frame *ancestor);
extern struct Frame *__cdecl Frame_GetChildren(struct Frame *frame);
extern struct Frame *__cdecl Frame_GetNextChild(struct Frame *frame);
extern BOOL __cdecl Frame_Recurse(lpFrame start, BOOL (*Callback)(lpFrame frame, LPVOID data), LPVOID data);
extern void __cdecl Frame_DumpHierarchy(struct Frame *root,unsigned long level,struct _iobuf *ofp);
static void __cdecl Frame_MarkDirty(struct Frame *frame,int first);
static void __cdecl Frame_Link(struct Frame *frame,struct Frame *parent);
static void __cdecl Frame_Unlink(struct Frame *frame);
extern void __cdecl Frame_WorldInverseTransform(struct Frame *frame, LPVECTOR3D result, LPVECTOR3D worldPos);
extern void __cdecl Frame_SetFlags_Internal(lpFrame frame, ULONG flags, BOOL set);
extern BOOL __cdecl Frame_TestFlags_Internal(lpFrame frame, ULONG flags, BOOL all);
extern BOOL __cdecl Frame_IsClipped(lpFrame frame);
extern void __cdecl Frame_SetFlags_External(lpFrame frame, ULONG flags, BOOL set);
extern BOOL __cdecl Frame_TestFlags_External(lpFrame frame, ULONG flags, BOOL all);
extern VOID __cdecl Frame_Shutdown(VOID);
// Auto Prototypes

#endif // !_RGL_FRAMES_H_
