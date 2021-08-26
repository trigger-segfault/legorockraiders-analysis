
//#define _LWSLOADER

#ifndef _GODS98_CONTAINERS_H_
#define _GODS98_CONTAINERS_H_

#include "..\Inc\Standard.h"
#include "..\Inc\Sound.h"
#include "..\Inc\AnimClone.h"
#include "..\Inc\3DSound.h"

/**********************************************************************************
 **
 ** Containers.h:
 **
 ** Copyright (C) Data Design Interactive
 **
 **
 ** Written by Robert Wilson 20/01/98
 **
 **********************************************************************************/

/**********************************************************************************
 ******** Defaults and Enumerations
 **********************************************************************************/

#ifdef _DEBUG
	#define CONTAINER_DEBUG_NOTREQUIRED	1
#else
	#define CONTAINER_DEBUG_NOTREQUIRED	NULL
#endif

#define CONTAINER_DDSFILEMAGIC			0x20534444

#define CONTAINER_FRAMENAMELEN			20
#define CONTAINER_ACTIVITYFRAMEPREFIX	"ActFrame"
#define CONTAINER_SCALESTRING			"SCALE"

#define CONTAINER_MAXLISTS				20			// Maximum of 2^20 - 1 containers
#define CONTAINER_MAXTEXTURES			1000
#define CONTAINER_MESHGROUPBLOCKSIZE	20
//#define CONTAINER_MAXROTATION			100

#define CONTAINER_FLAG_INITIALISED		0x00000001
#define CONTAINER_FLAG_TRIGGERSAMPLE	0x00000002
#define CONTAINER_FLAG_MESHSWAPPED		0x00000004
#define CONTAINER_FLAG_HIDDEN			0x00000008
#define CONTAINER_FLAG_DEADREFERENCE	0x00000010
#define CONTAINER_FLAG_ANIMATIONSKIPPED	0x00000020
#define CONTAINER_FLAG_TRIGGERENABLED	0x00000040
#define CONTAINER_FLAG_HIDDEN2			0x00000080

#define CONTAINER_NULLSTRING			"NULL"
#define CONTAINER_MESHSTRING			"MESH"
#define CONTAINER_MESHNOTEXTURESTRING	"MESH:NOTEXTURE"
#define CONTAINER_FRAMESTRING			"FRAME"
#define CONTAINER_ANIMSTRING			"ANIM"
#define CONTAINER_LWSSTRING				"LWS"
#define CONTAINER_LWOSTRING				"LWO"
#define CONTAINER_LWONOTEXTURESTRING	"LWO:NOTEXTURE"
#define CONTAINER_ACTIVITYSTRING		"ACT"

#define CONTAINER_ULONG_NULL			-1

#define CONTAINER_TRASHVALUE			0xdeaddead

#define CONTAINER_TEXTURE_NOLOAD		0x00000001

#define CONTAINER_MAXVISUALS			4

enum Container_Type {
	Container_Invalid = -1,
	Container_Null,				// #0
	Container_Mesh,				// #1
	Container_Frame,			// #2
	Container_Anim,				// #3
	Container_FromActivity,		// #4
	Container_Light,			// #5
	Container_Reference,		// #6
	Container_LWS,
	Container_LWO,

	Container_TypeCount
};

enum Container_Light {
	Container_Light_Ambient,
	Container_Light_Point,
	Container_Light_Spot,
	Container_Light_Directional,
	Container_Light_ParallelPoint
};

enum Container_Combine_Type {
	Container_Combine_Replace,
	Container_Combine_Before,
	Container_Combine_After
};

enum Container_Quality {
	Container_Quality_Wireframe,
	Container_Quality_UnlitFlat,
	Container_Quality_Flat,
	Container_Quality_Gouraud
};

enum Container_FogType {
	Container_Fog_None=0,
	Container_Fog_Exponential,
	Container_Fog_ExponentialSquared,
	Container_Fog_Linear,
};

enum Container_MeshType {
    Container_MeshType_Normal,
    Container_MeshType_SeperateMeshes,
    Container_MeshType_Immediate,
    Container_MeshType_Transparent,
    Container_MeshType_Additive,
    Container_MeshType_Subtractive
};

enum Container_SearchMode {
	Container_SearchMode_FirstMatch,
	Container_SearchMode_MatchCount,
	Container_SearchMode_NthMatch
};

/**********************************************************************************
 ******** Macros
 **********************************************************************************/

#ifdef _DEBUG
	#define Container_DebugCheckOK(c)			{Error_Fatal(!(containerGlobs.flags&CONTAINER_FLAG_INITIALISED),"Container_Initialise() Has Not Been Called");Error_Fatal(!(c),"Error: NULL Passed as Argument to function"); if(1!=(ULONG)(c)) { Error_Fatal(CONTAINER_TRASHVALUE==((lpContainer)(c))->type, "Container used after own destruction");} }
//	#define Container_DebugCheckOK(c)			{Error_Fatal(!(containerGlobs.flags&CONTAINER_FLAG_INITIALISED),"Container_Initialise() Has Not Been Called");Error_Fatal(!(c),"Error: NULL Passed as Argument to function"); if(1!=(ULONG)(c)) { Error_Fatal(CONTAINER_TRASHVALUE==((lpContainer)(c))->type, "Container used after own destruction");Error_Warn(((lpContainer)(c))->flags&CONTAINER_FLAG_DEADREFERENCE,"Reference container's master frame has been removed");} }
	#define Container_Mesh_DebugCheckOK(c,g)	Container_Debug_CheckMesh((c),(g))
#else
	#define Container_DebugCheckOK(c)			(c)
	#define Container_Mesh_DebugCheckOK(c,g)
#endif // _DEBUG

#ifdef _HIERARCHY_DEBUG
	#define Container_NoteCreation(o)	Container_Debug_NoteCreation((LPDIRECT3DRMOBJECT) (o), __LINE__)
#else
	#define Container_NoteCreation(o)
#endif // _HIERARCHY_DEBUG

#define CDF(f)	Container_Frame_CastDown(f)
#define CUF(f)	Container_Frame_CastUp(f)

#define Container_SetWorldRotation(c,x,y,z,a)				Container_SetRotation((c),NULL,(x),(y),(z),(a))
#define Container_SetWorldPosition(c,x,y,z)					Container_SetPosition((c),NULL,(x),(y),(z))
#define Container_SetWorldOrientation(c,dx,dy,dz,ux,uy,uz)	Container_SetOrientation((c),NULL,(dx),(dy),(dz),(ux),(uy),(uz))
#define Container_GetWorldRotation(c,ax,a)					Container_GetRotation((c),NULL,(ax),(a))
#define Container_GetWorldPosition(c,p)						Container_GetPosition((c),NULL,(p))
#define Container_GetWorldOrientation(c,d,u)				Container_GetOrientation((c),NULL,(d),(u))

#define Container_MakePointLight(c,r,g,b)					Container_MakeLight((c),Container_Light_Point,(r),(g),(b));
#define Container_MakeSpotLight(c,r,g,b)					Container_MakeLight((c),Container_Light_Spot,(r),(g),(b));
#define Container_MakeAmbientLight(c,r,g,b)					Container_MakeLight((c),Container_Light_Ambient,(r),(g),(b));
#define Container_MakeDirectionalLight(c,r,g,b)				Container_MakeLight((c),Container_Light_Directional,(r),(g),(b));
#define Container_MakeParallelPointLight(c,r,g,b)			Container_MakeLight((c),Container_Light_ParallelPoint,(r),(g),(b));

#ifdef _DEBUG
#define Container_MakeCamera(p)								Container_Debug_MakeCamera((p))
#else
#define Container_MakeCamera(p)								Container_Create((p))
#endif // _DEBUG

#define Container_SetColour(c,r,g,b)						Container_SetColourAlpha((c),(r),(g),(b),1.0f)
#define Container_GetColour(c,r,g,b)						Container_GetColourAlpha((c),(r),(g),(b),NULL)
#define Container_Mesh_SetColour(c,i,r,g,b)					Container_Mesh_SetColourAlpha((c),(i),(r),(g),(b),1.0f)
#define Container_Mesh_GetColour(c,i,r,g,b)					Container_Mesh_GetColourAlpha((c),(i),(r),(g),(b),NULL)

#define Container_MakeMesh(r)								Container_MakeMesh2((r),Container_MeshType_Normal)
#define Container_MakeMeshSeperateGroups(r)					Container_MakeMesh2((r),Container_MeshType_SeperateMeshes)
#define Container_MakeMeshImmediate(r)						Container_MakeMesh2((r),Container_MeshType_Immediate)
#define Container_MakeMeshTrans(r)							Container_MakeMesh2((r),Container_MeshType_Transparent)
#define Container_MakeMeshAdditive(r)						Container_MakeMesh2((r),Container_MeshType_Additive)
#define Container_MakeMeshSubtractive(r)					Container_MakeMesh2((r),Container_MeshType_Subtractive)

#define Container_LoadTexture(f,w,h)						Container_LoadTexture2((f),FALSE,(w),(h))
#define Container_LoadTextureImmediate(f,w,h)				Container_LoadTexture2((f),TRUE,(w),(h))

/**********************************************************************************
 ******** Structure
 **********************************************************************************/

#ifdef _GODS98COMPILE

typedef struct Container_TypeData {

	LPUCHAR name;
	LPDIRECT3DRMLIGHT light;
	LPDIRECT3DRMMESH mesh;
	struct Mesh *transMesh;

} Container_TypeData, *lpContainer_TypeData;

#else 

typedef struct Container_TypeData *lpContainer_TypeData;
typedef LPVOID LPDIRECT3DRMFRAME3;
typedef LPVOID LPDIRECTDRAWSURFACE4;
typedef LPVOID LPDIRECT3DRMTEXTURE3;

#endif // _GODS98COMPILE

typedef struct Container_CloneData;

/*
typedef struct Container_RotationData {

	struct Container *container;
	enum Container_Combine_Type combine;
	VECTOR3D vector;
	REAL angle;

} Container_RotationData, *lpContainer_RotationData;
*/

typedef struct Container {

	LPDIRECT3DRMFRAME3 masterFrame, activityFrame, hiddenFrame;
	lpContainer_TypeData typeData;
	enum Container_Type type;
	ULONG flags;
	VOID (*activityCallback)(struct Container *cont, LPVOID data);
	LPVOID activityCallbackData;
	LPVOID userData;

	struct Container_CloneData *cloneData;			// Only used by animsets.

	struct Container *nextFree;

} Container, *lpContainer;

#ifdef _GODS98COMPILE

typedef struct Container_CloneData {

	lpContainer clonedFrom;				// NULL if this is the original
	lpContainer *cloneTable;			// List of clones (NULL for unused elements)
	ULONG cloneCount, cloneNumber;		// Total number of clones made and clone's number in the list.
	BOOL used;

} Container_CloneData, *lpContainer_CloneData;

typedef struct Container_AppData {

	lpContainer ownerContainer;
//	LPDIRECT3DRMANIMATIONSET animSet;

	LPUCHAR animSetFileName;			// For the dodgy Animation Set clone stuff...
	LPUCHAR frameName;					// For freeing the allocation for SetName...

	ULONG frameCount;
	REAL currTime;
	REAL transCo;						// Standard translation during amimset loop.
	LPUCHAR activitySample;				// Sample to play when activity is called...
	lpAnimClone animClone;
	ULONG trigger;

	lpSound3D_SoundFrameRecord soundList;		// For 'Sound3D'

} Container_AppData;

typedef struct Container_MeshAppData {

	LPDIRECT3DRMMESH *meshList;
	ULONG usedCount, listSize;
	BOOL groupZeroHidden, firstAddGroup;

} Container_MeshAppData, *lpContainer_MeshAppData;

typedef struct Container_SearchData {

	LPUCHAR string;
	ULONG stringLen;
	BOOL caseSensitive;
	LPDIRECT3DRMFRAME3 resultFrame;
	ULONG count, mode, matchNumber;

} Container_SearchData, *lpContainer_SearchData;

#ifdef _GODS98COMPILE

typedef struct Container_TextureRef {

	LPUCHAR fileName;
	LPDIRECT3DRMTEXTURE3 texture;

} Container_TextureRef, *lpContainer_TextureRef;

typedef struct Container_TextureData {

	LPUCHAR xFileName;
	ULONG flags;

} Container_TextureData, *lpContainer_TextureData;

#endif // _GODS98COMPILE

typedef struct Container_Globs {

	lpContainer listSet[CONTAINER_MAXLISTS];
	lpContainer freeList, rootContainer;

	LPUCHAR typeName[Container_TypeCount];
	LPUCHAR extensionName[Container_TypeCount];
	LPUCHAR gameName;

	LPDIRECT3DRMVISUAL visualArray[CONTAINER_MAXVISUALS];

	Container_TextureRef textureSet[CONTAINER_MAXTEXTURES];
	ULONG textureCount;

	VOID (*soundTriggerCallback)(LPUCHAR sampleName, lpContainer cont, LPVOID data);
	LPVOID soundTriggerData;

	VOID (*triggerFrameCallback)(lpContainer cont, LPVOID data);
	LPVOID triggerFrameData;

	LPUCHAR sharedDir;

	ULONG fogColour;

	ULONG listCount;
	ULONG flags;

//	struct Container_RotationData rotationList[CONTAINER_MAXROTATION];
//	ULONG rotationCount;

} Container_Globs;

extern Container_Globs containerGlobs;
__inline LPDIRECT3DRMFRAME3 Debug_Scene() { return containerGlobs.rootContainer->masterFrame; }

#endif // _GODS98COMPILE

/*
typedef struct Container_DummyTexture {
	
	ULONG dummy;

} *lpContainer_Texture;
*/

typedef struct Container_Texture {

	LPDIRECTDRAWSURFACE4 surface;
	LPDIRECT3DRMTEXTURE3 texture;

	BOOL colourKey;

} Container_Texture, *lpContainer_Texture;

/*
typedef struct Container_DummyMaterial {
	
	ULONG dummy;

} *lpContainer_Material;


/**********************************************************************************
 ******** Prototypes
 **********************************************************************************/
extern ULONG __cdecl Container_GetRGBAColour(REAL r, REAL g, REAL b, REAL a);
extern ULONG __cdecl Container_GetRGBColour(REAL r, REAL g, REAL b);


#ifndef _GENPROTFILE
#include "..\src\Containers.prot"
#endif // _GENPROTFILE

#endif // _GODS98_CONTAINERS_H_
