
#ifndef _RGL_LWS_H_
#define _RGL_LWS_H_

#include "Frames.h"
#include "Lights.h"

enum LwsLight_Type {
	LwsLight_Distant = 0,
	LwsLight_Point = 1,
	LwsLight_Spot = 2,
};

#define LWS_HEADER1							"LWSC"
#define LWS_HEADER2							"1"
#define LWS_FILESUFFIX						".lws"
#define LWS_MAXLINELEN						1024
#define LWS_BLOCKSIZE						10			// How much to increse lists by when Mem_Realloc() is called.
#define LWS_MAXARGS							20
#define LWS_SOUNDTRIGGERPREFIX				"SFX"
#define LWS_SOUNDTRIGGERSEPERATOR			","
#define LWS_MAXSTATICDISSOLVES				10
#define LWS_CAMERANAME						"Camera"
#define LWS_LIGHTNAME						"Light"
#define LWS_MAXBONEDEPTH					100
#define LWS_MAXBONES						100

#define LWS_FLAG_LOOPING					0x01
#define LWS_FLAG_HASLIGHT					0x02

#define LWSNODE_FLAG_NULL					0x01
#define LWSNODE_FLAG_SOUNDTRIGGER			0x02
#define LWSNODE_FLAG_CAMERA					0x04
#define LWSNODE_FLAG_LIGHT					0x08

#define LWSBONE_FLAG_ACTIVE					0x01
#define LWSBONE_FLAG_SCALESTRENGTH			0x02

#define LWSLOAD_FLAG_LOOPING				0x00000001
#define LWSLOAD_FLAG_USENORMALS				0x00000002
#define LWSLOAD_FLAG_ADDCAMERA				0x00000004
#define LWSLOAD_FLAG_ADDLIGHTS				0x00000008
#define LWSLOAD_FLAG_OPTIMISE				0x00000010

struct Lws {

	UWORD firstFrame, lastFrame;
	LPUCHAR filePath;
	REAL fps, lastTime, time;

	lpFrame *frameList;
	lpLight *lightList;

	struct LwsNode *nodeList;
//	struct LwsNode *cameraNode;
//	struct LwsNode *lightChain;
	ULONG cameraNodeIndex;
	struct LwsNodeSetupInfo *nodeSetupList;
	struct LwsNodeSetupInfo *masterNodeSetup;

	struct LwsBone *boneList;
	struct LwsKeyInfo *keyList;
	MATRIX4D *boneMatrixList;

	REAL cameraZoom;

	UWORD nodeCount, nodeListSize, triggerCount;
	UWORD boneCount;//, boneListSize;
	UWORD keyCount, keyListSize;

	struct Lws *clonedFrom;
	ULONG referenceCount;

	UCHAR flags;

};

struct LwsBone {

	ULONG index;

	VECTOR3D restPosition, restDirection;
	REAL restLength, strength;

	struct LwsKeyInfo *keyList;
	UWORD keyCount;
	ULONG rootFrameIndex;
	
#ifdef LWS_OWNBONES
	LPREAL vertexInfluenceList;
	MATRIX4D subWorldMatrix;
#else  // LWS_OWNBONES
	ULONG blendIndex;
	MATRIX4D restMatrix;
//	MATRIX4D boneMatrix;
#endif // LWS_OWNBONES
	
	struct LwsBone *children;
	union {
		struct LwsBone *next;
		struct LwsBone *nextSibling;
	};

	UCHAR flags;
};

struct LwsNodeSetupInfo {			// Data required only during setup that may be freed...

	LPUCHAR name;
	UWORD reference;

	COLOUR lightColour;
	ULONG lightType;
	REAL lightIntensity, lightRange, lightConeAngle, lightEdgeAngle;
	BOOL lightFalloff;

	struct LwsNodeSetupInfo *childList;
	struct LwsNodeSetupInfo *next;
	struct LwsNode *node;
};

struct LwsNode {					// Data reqired for the normal operation of the scene...

	UWORD frameIndex;
	UCHAR triggerIndex;

	VECTOR3D pivotVector;
	struct LwsKeyInfo *keyList;

	LPREAL dissolveLevel;
	LPUWORD dissolveFrame;

	UWORD keyCount, dissolveCount;

	struct LwsBone *boneList;
	REAL boneFalloffPower;

	UCHAR flags;

//	struct LwsNode *chainNext;
};

struct LwsKeyInfo {

	VECTOR3D position;
	VECTOR3D hpb;
	VECTOR3D scale;
	REAL tension;
	UWORD frame;
};

typedef struct Lws					*lpLws;
typedef struct LwsNode				*lpLwsNode;
typedef struct LwsBone				*lpLwsBone;
typedef struct LwsKeyInfo			*lpLwsKeyInfo;
typedef struct LwsNodeSetupInfo		*lpLwsNodeSetupInfo;

// Auto Prototypes
extern unsigned __int64 __stdcall Int64ShllMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern __int64 __stdcall Int64ShraMod32(__int64 Value,unsigned long ShiftCount);
extern unsigned __int64 __stdcall Int64ShrlMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern void *__cdecl GetFiberData(void );
extern void *__cdecl GetCurrentFiber(void );
extern float __cdecl LWO_REAL(unsigned long n);
extern void __cdecl Lws_Initialise(void);
extern void __cdecl Lws_SetAddObjectCallback(int (*addObjectCallback)(unsigned char *command, unsigned char *name, void *data), void *addObjectCallbackData);
extern struct Lws *__cdecl Lws_Clone(struct Lws *scene, struct Frame *parent);
extern struct Lws *__cdecl Lws_Load(unsigned char *fname,struct Frame *parentFrame,unsigned long loadFlags,int useShared);
extern void __cdecl Lws_SetBoneTransforms(struct Lws *scene,struct LwsBone *firstChild, unsigned long *count);
static void __cdecl Lws_BuildBoneInfluenceList(struct Lws *scene,struct Frame *rootFrame,struct LwsNode *node);
extern struct Frame *__cdecl Lws_GetBoneFrame(struct Lws *lws,struct LwsBone *bone);
static void __cdecl Lws_SetupBones(struct Lws *scene,struct Frame *rootFrame,unsigned long *parentList);
static void __cdecl Lws_SetupFrames(struct Lws *scene,struct Frame *parent);
extern unsigned long __cdecl Lws_GetFrameCount(struct Lws *scene);
extern struct Frame *__cdecl Lws_GetCamera(struct Lws *scene,float *fov);
static void __cdecl Lws_SetupSoundTriggers(struct Lws *scene);
static void __cdecl Lws_LoadMeshes(struct Lws *scene,int useNormals,int optimise);
extern void __cdecl Lws_EnableLights(struct Lws *scene,struct Frame *enableFrame,struct Viewport *vp);
extern void __cdecl Lws_CreateLights(struct Lws *scene);
static void __cdecl Lws_CreateFrames(struct Lws *scene,struct LwsNodeSetupInfo *nodeSetup,struct Frame *parent,unsigned short *frameCount);
static void __cdecl Lws_LoadNodes(struct Lws *scene,struct LwsNodeSetupInfo *nodeSetup,int useNormals,int optimise);
extern void __cdecl Lws_ClearSetup(struct Lws *scene);
static void __cdecl Lws_SetupRestMatrices(struct Lws *scene,struct LwsBone *firstBone,struct VECTOR3D *positionOffset,struct VECTOR3D *directionOffset);
static void __cdecl Lws_SetupRestMatrices2(struct Lws *scene,struct LwsBone *firstBone,MATRIX4D parentMatrix);
static void __cdecl Lws_UpdateBoneHierarchy2(struct Lws *scene,struct LwsBone *firstBone);
static void __cdecl Lws_SetBoneTime(struct Lws *scene,float time);
extern void __cdecl Lws_SetTime(struct Lws *scene,float time);
static void __cdecl Lws_SetAbsoluteKey(struct Frame *frame,struct LwsKeyInfo *keyList,unsigned short key,struct VECTOR3D *pivot);
static void __cdecl Lws_GenerateMatrix(float (*m)[4],struct VECTOR3D *pos,struct VECTOR3D *hpb,struct VECTOR3D *scale,struct VECTOR3D *pivot);
static void __cdecl Lws_GenerateRestMatrix(float (*m)[4],struct VECTOR3D *pos,struct VECTOR3D *hpb);
static void __cdecl Lws_SetDissolveLevel(struct Lws *scene,struct LwsNode *node,float level);
static float __cdecl Lws_FindPrevDissolve(struct LwsNode *node,float time,unsigned short *prev);
static void __cdecl Lws_InterpolateDissolve(struct Lws *scene,struct LwsNode *node,unsigned short prev,float delta);
static float __cdecl Lws_FindPrevKey(struct LwsKeyInfo *keyList,unsigned short keyCount,float time,unsigned short *prev);
static void __cdecl Lws_InterpolateKeys(struct Frame *frame,struct LwsKeyInfo *keyList,unsigned short key,float delta,struct VECTOR3D *pivot);
extern REAL __cdecl Lws_GetKeyInfo(lpLws scene, lpLwsNode node, REAL time, lpLwsKeyInfo *prevKey, lpLwsKeyInfo *nextKey);
extern REAL __cdecl Lws_GetTime(lpLws scene);
extern VOID __cdecl Lws_Remove(lpLws lws);
extern VOID __cdecl Lws_Shutdown(VOID);
extern lpLwsNode __cdecl Lws_FindNode(lpLws scene, lpFrame frame);
extern lpFrame __cdecl Lws_FindFrame(lpLws lws, LPUCHAR name, ULONG instance);
extern lpFrame __cdecl Lws_FindFrame2(lpLws lws, LPUCHAR name, ULONG compareLength, ULONG occurance);
// Auto Prototypes

#endif // !_RGL_LWS_H_
