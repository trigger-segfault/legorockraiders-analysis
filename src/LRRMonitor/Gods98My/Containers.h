#pragma once

#include "../framework.h"
#include "Maths.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Forward Declarations
 **********************************************************************************/

#pragma region Forward Declarations

struct Container;
struct Container_CloneData;
struct AnimClone;
struct Mesh;
struct Sound3D_SoundFrameRecord;

#pragma endregion

/**********************************************************************************
 ******** Function Typedefs
 **********************************************************************************/

#pragma region Function Typedefs

typedef void (__cdecl* ContainerActivityCallback)(Container* cont, void* data);
typedef void (__cdecl* ContainerSoundTriggerCallback)(const char* sampleName, Container* cont, void* data);
typedef void (__cdecl* ContainerTriggerFrameCallback)(Container* cont, void* data);
typedef BOOL (__cdecl* ContainerWalkTreeCallback)(IDirect3DRMFrame3* frame, void* data);

#pragma endregion

/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define CONTAINER_DEBUG_NOTREQUIRED	NULL

#define CONTAINER_DDSFILEMAGIC			0x20534444

#define CONTAINER_FRAMENAMELEN			20
#define CONTAINER_ACTIVITYFRAMEPREFIX	"ActFrame"
#define CONTAINER_SCALESTRING			"SCALE"

#define CONTAINER_MAXLISTS				20			// Maximum of 2^20 - 1 containers
#define CONTAINER_MAXTEXTURES			1000
#define CONTAINER_MESHGROUPBLOCKSIZE	20
//#define CONTAINER_MAXROTATION			100

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

#define CONTAINER_MAXVISUALS			4

#pragma endregion

/**********************************************************************************
 ******** Enumerations
 **********************************************************************************/

#pragma region Enums

#define CONTAINER_FLAG_INITIALISED		0x00000001
#define CONTAINER_FLAG_TRIGGERSAMPLE	0x00000002
#define CONTAINER_FLAG_MESHSWAPPED		0x00000004
#define CONTAINER_FLAG_HIDDEN			0x00000008
#define CONTAINER_FLAG_DEADREFERENCE	0x00000010
#define CONTAINER_FLAG_ANIMATIONSKIPPED	0x00000020
#define CONTAINER_FLAG_TRIGGERENABLED	0x00000040
#define CONTAINER_FLAG_HIDDEN2			0x00000080


#define CONTAINER_TEXTURE_NOLOAD		0x00000001


enum Container_Type
{
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
static_assert(sizeof(Container_Type) == 0x4, "");


enum Container_Light
{
	Container_Light_Ambient,
	Container_Light_Point,
	Container_Light_Spot,
	Container_Light_Directional,
	Container_Light_ParallelPoint
};
static_assert(sizeof(Container_Light) == 0x4, "");


enum Container_Combine_Type
{
	Container_Combine_Replace,
	Container_Combine_Before,
	Container_Combine_After
};
static_assert(sizeof(Container_Combine_Type) == 0x4, "");


enum Container_Quality
{
	Container_Quality_Wireframe,
	Container_Quality_UnlitFlat,
	Container_Quality_Flat,
	Container_Quality_Gouraud
};
static_assert(sizeof(Container_Quality) == 0x4, "");


enum Container_FogType
{
	Container_Fog_None=0,
	Container_Fog_Exponential,
	Container_Fog_ExponentialSquared,
	Container_Fog_Linear,
};
static_assert(sizeof(Container_FogType) == 0x4, "");


enum Container_MeshType
{
    Container_MeshType_Normal,
    Container_MeshType_SeperateMeshes,
    Container_MeshType_Immediate,
    Container_MeshType_Transparent,
    Container_MeshType_Additive,
    Container_MeshType_Subtractive
};
static_assert(sizeof(Container_MeshType) == 0x4, "");


enum Container_SearchMode
{
	Container_SearchMode_FirstMatch,
	Container_SearchMode_MatchCount,
	Container_SearchMode_NthMatch
};
static_assert(sizeof(Container_SearchMode) == 0x4, "");

#pragma endregion

/**********************************************************************************
 ******** Macros
 **********************************************************************************/

#pragma region Macros

#define Container_DebugCheckOK(c)			(c)
#define Container_Mesh_DebugCheckOK(c,g)


#define Container_NoteCreation(o)


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

#define Container_MakeCamera(p)								Container_Create((p))

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

#pragma endregion

/**********************************************************************************
 ******** Structure
 **********************************************************************************/

#pragma region Structs

typedef struct Container_TypeData
{
	/*00,4*/ char* name;
	/*04,4*/ IDirect3DRMLight* light;
	/*08,4*/ IDirect3DRMMesh* mesh;
	/*0c,4*/ Mesh* transMesh;
	/*10*/
} Container_TypeData, *lpContainer_TypeData;
static_assert(sizeof(Container_TypeData) == 0x10, "");


//typedef struct Container_CloneData;


//typedef struct Container_RotationData
//{
//	/*00,4*/ Container* container;
//	/*04,4*/ Container_Combine_Type combine;
//	/*08,c*/ VECTOR3D vector;
//	/*14,4*/ float angle;
//	/*18*/
//} Container_RotationData, *lpContainer_RotationData;
//static_assert(sizeof(Container_RotationData) == 0x18, "");


typedef struct Container
{
	/*00,4*/ IDirect3DRMFrame3* masterFrame;
	/*04,4*/ IDirect3DRMFrame3* activityFrame;
	/*08,4*/ IDirect3DRMFrame3* hiddenFrame;
	/*0c,4*/ Container_TypeData* typeData;
	/*10,4*/ Container_Type type;
	/*14,4*/ unsigned long flags;
	/*18,4*/ ContainerActivityCallback activityCallback;
	/*1c,4*/ void* activityCallbackData;
	/*20,4*/ void* userData;
	/*24,4*/ Container_CloneData* cloneData;			// Only used by animsets.
	/*28,4*/ Container* nextFree;
	/*2c*/
} Container, *lpContainer;
static_assert(sizeof(Container) == 0x2c, "");


typedef struct Container_CloneData
{
	/*00,4*/ Container* clonedFrom;				// NULL if this is the original
	/*04,4*/ Container** cloneTable;			// List of clones (NULL for unused elements)
	/*08,4*/ unsigned long cloneCount;
	/*0c,4*/ unsigned long cloneNumber;		// Total number of clones made and clone's number in the list.
	/*10,4*/ BOOL used;
	/*14*/
} Container_CloneData, *lpContainer_CloneData;
static_assert(sizeof(Container_CloneData) == 0x14, "");


typedef struct Container_AppData
{
	/*00,4*/ Container* ownerContainer;
	//IDirect3DRMAnimationSet2* animSet;
	/*04,4*/ char* animSetFileName;			// For the dodgy Animation Set clone stuff...
	/*08,4*/ char* frameName;					// For freeing the allocation for SetName...
	/*0c,4*/ unsigned long frameCount;
	/*10,4*/ float currTime;
	/*14,4*/ float transCo;						// Standard translation during amimset loop.
	/*18,4*/ char* activitySample;				// Sample to play when activity is called...
	/*1c,4*/ AnimClone* animClone;
	/*20,4*/ unsigned long trigger;
	/*24,4*/ Sound3D_SoundFrameRecord* soundList;		// For 'Sound3D'
	/*28*/
} Container_AppData;
static_assert(sizeof(Container_AppData) == 0x28, "");


typedef struct Container_MeshAppData
{
	/*00,4*/ IDirect3DRMMesh** meshList;
	/*04,4*/ unsigned long usedCount;
	/*08,4*/ unsigned long  listSize;
	/*0c,4*/ BOOL groupZeroHidden;
	/*10,4*/ BOOL firstAddGroup;
	/*14*/
} Container_MeshAppData, *lpContainer_MeshAppData;
static_assert(sizeof(Container_MeshAppData) == 0x14, "");


typedef struct Container_SearchData
{
	/*00,4*/ char* string;
	/*04,4*/ unsigned long stringLen;
	/*08,4*/ BOOL caseSensitive;
	/*0c,4*/ IDirect3DRMFrame3* resultFrame;
	/*10,4*/ unsigned long count;
	/*14,4*/ unsigned long mode;
	/*18,4*/ unsigned long matchNumber;
	/*1c*/
} Container_SearchData, *lpContainer_SearchData;
static_assert(sizeof(Container_SearchData) == 0x1c, "");


typedef struct Container_TextureRef
{
	/*0,4*/ char* fileName;
	/*4,4*/ IDirect3DRMTexture3* texture;
	/*8*/
} Container_TextureRef, *lpContainer_TextureRef;
static_assert(sizeof(Container_TextureRef) == 0x8, "");


typedef struct Container_TextureData
{
	/*0,4*/ char* xFileName;
	/*4,4*/ unsigned long flags;
	/*8*/
} Container_TextureData, *lpContainer_TextureData;
static_assert(sizeof(Container_TextureData) == 0x8, "");


//typedef struct Container_DummyTexture
//{
//	/*0,4*/ unsigned long dummy;
//	/*4*/
//} Container_DummyTexture, *lpContainer_Texture;
//static_assert(sizeof(Container_DummyTexture) == 0x4, "");


typedef struct Container_Texture
{
	/*0,4*/ IDirectDrawSurface4* surface;
	/*4,4*/ IDirect3DRMTexture3* texture;
	/*8,4*/ BOOL colourKey;
	/*c*/
} Container_Texture, *lpContainer_Texture;
static_assert(sizeof(Container_Texture) == 0xc, "");


//typedef struct Container_DummyMaterial
//{
//	/*0,4*/ unsigned long dummy;
//	/*4*/
//} Container_DummyMaterial, *lpContainer_Material;
//static_assert(sizeof(Container_DummyMaterial) == 0x4, "");


typedef struct Container_Globs
{
	/*0000,50*/ Container* listSet[CONTAINER_MAXLISTS];
	/*0050,4*/ Container* freeList;
	/*0054,4*/ Container* rootContainer;
	/*0058,24*/ const char* typeName[Container_TypeCount];
	/*007c,24*/ const char* extensionName[Container_TypeCount];
	/*00a0,4*/ const char* gameName;
	/*00a4,10*/ IDirect3DRMVisual* visualArray[CONTAINER_MAXVISUALS];
	/*00b4,1f40*/ Container_TextureRef textureSet[CONTAINER_MAXTEXTURES];
	/*1ff4,4*/ unsigned long textureCount;
	/*1ff8,4*/ ContainerSoundTriggerCallback soundTriggerCallback;
	/*1ffc,4*/ void* soundTriggerData;
	/*2000,4*/ ContainerTriggerFrameCallback triggerFrameCallback;
	/*2004,4*/ void* triggerFrameData;
	/*2008,4*/ char* sharedDir;
	/*200c,4*/ unsigned long fogColour;
	/*2010,4*/ unsigned long listCount;
	/*2014,4*/ unsigned long flags;
	/*2018*/

} Container_Globs;
static_assert(sizeof(Container_Globs) == 0x2018, "");

#pragma endregion

/**********************************************************************************
 ******** Globals
 **********************************************************************************/

#pragma region Globals

// <LegoRR.exe @0076bd80>
extern Container_Globs containerGlobs;

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

//__inline LPDIRECT3DRMFRAME3 Debug_Scene() { return containerGlobs.rootContainer->masterFrame; }

/**********************************************************************************
 ******** Prototypes
 **********************************************************************************/

//extern ULONG __cdecl Container_GetRGBAColour(float r, float g, float b, float a);
//extern ULONG __cdecl Container_GetRGBColour(float r, float g, float b);


// <LegoRR.exe @004729d0>
Container* __cdecl Container_Initialise(const char* gameName);

// <LegoRR.exe @00472ac0>
void __cdecl Container_Shutdown(void);

// <LegoRR.exe @00472b80>
void __cdecl Container_SetSharedTextureDirectory(const char* path);

// <LegoRR.exe @00472ba0>
void __cdecl Container_EnableSoundTriggers(BOOL on);

// <LegoRR.exe @00472bc0>
void __cdecl Container_SetTriggerFrameCallback(ContainerTriggerFrameCallback Callback, void* data);

// <LegoRR.exe @00472be0>
void __cdecl Container_SetSoundTriggerCallback(ContainerSoundTriggerCallback Callback, void* data);

// <LegoRR.exe @00472c00>
Container* __cdecl Container_GetRoot(void);

// <LegoRR.exe @00472c10>
Container* __cdecl Container_Create(Container* parent);

// <LegoRR.exe @00472d00>
void __cdecl Container_Remove(Container* dead);

// <LegoRR.exe @00472d10>
void __cdecl Container_Remove2(Container* dead, BOOL kill);

// <LegoRR.exe @00472f90>
Container* __cdecl Container_Load(Container* parent, const char* filename, const char* typestr, BOOL looping);

// <LegoRR.exe @00473600>
BOOL __cdecl Container_IsCurrentActivity(Container* cont, const char* actname);

// <LegoRR.exe @00473630>
BOOL __cdecl Container_SetActivity(Container* cont, const char* actname);

// <LegoRR.exe @00473720>
BOOL __cdecl Container_Light_SetSpotPenumbra(Container* spotlight, float angle);

// <LegoRR.exe @00473740>
BOOL __cdecl Container_Light_SetSpotUmbra(Container* spotlight, float angle);

// <LegoRR.exe @00473760>
BOOL __cdecl Container_Light_SetSpotRange(Container* spotlight, float dist);

// <LegoRR.exe @00473780>
void __cdecl Container_Light_SetEnableContainer(Container* light, Container* enable);

// <LegoRR.exe @004737b0>
Container* __cdecl Container_MakeLight(Container* parent, unsigned long type, float r, float g, float b);

// <LegoRR.exe @00473820>
Container* __cdecl Container_MakeMesh2(Container* parent, unsigned long type);

// <LegoRR.exe @00473940>
IDirect3DRMFrame3* __cdecl Container_GetMasterFrame(Container* cont);

// <LegoRR.exe @00473950>
Container* __cdecl Container_Clone(Container* orig);

// <LegoRR.exe @00473de0>
void __cdecl Container_Hide2(Container* cont, BOOL hide);

// <LegoRR.exe @00473e00>
void __cdecl Container_Hide(Container* cont, BOOL hide);

// <LegoRR.exe @00473e60>
BOOL __cdecl Container_IsHidden(Container* cont);

// <LegoRR.exe @00473e80>
Container* __cdecl Container_SearchTree(Container* root, const char* name, Container_SearchMode mode, IN OUT unsigned long* count);

// <LegoRR.exe @00473f20>
const char* __cdecl Container_FormatPartName(Container* cont, const char* partname, OPTIONAL unsigned long* instance);

// <LegoRR.exe @00474060>
void __cdecl Container_SetUserData(Container* cont, void* data);

// <LegoRR.exe @00474070>
void* __cdecl Container_GetUserData(Container* cont);

// <LegoRR.exe @00474080>
void __cdecl Container_EnableFog(BOOL on);

// <LegoRR.exe @004740d0>
void __cdecl Container_SetFogColour(float r, float g, float b);

// <LegoRR.exe @00474130>
void __cdecl Container_SetFogMode(unsigned long mode);

// <LegoRR.exe @00474160>
void __cdecl Container_SetFogParams(float start, float end, float density);

// <LegoRR.exe @00474160>
void __cdecl Container_SetPerspectiveCorrection(Container* cont, BOOL on);

// <LegoRR.exe @00474230>
BOOL __cdecl Container_SetPerspectiveCorrectionCallback(IDirect3DRMFrame3* frame, void* data);

// <LegoRR.exe @00474310>
IDirectDrawSurface4* __cdecl Container_LoadTextureSurface(const char* fname, BOOL managed,
								OUT unsigned long* width, OUT unsigned long* height, OUT BOOL* trans);

// <LegoRR.exe @004746d0>
BOOL __cdecl Container_GetDecalColour(const char* fname, OUT unsigned long* colour);

// <LegoRR.exe @004747b0>
Container_Texture* __cdecl Container_LoadTexture2(const char* fname, BOOL immediate,
								OUT unsigned long* width, OUT unsigned long* height);

// <LegoRR.exe @004749d0>
void __cdecl Container_FreeTexture(Container_Texture* text);

// <LegoRR.exe @00474a20>
void __cdecl Container_Mesh_Swap(Container* target, Container* origin, BOOL restore);

// <LegoRR.exe @00474bb0>
unsigned long __cdecl Container_Mesh_AddGroup(Container* cont, unsigned long vertexCount,
								unsigned long faceCount, unsigned long vPerFace, const unsigned long* faceData);

// <LegoRR.exe @00474ce0>
unsigned long __cdecl Container_Mesh_GetGroupCount(Container* cont);

// <LegoRR.exe @00474d20>
void __cdecl Container_Mesh_SetQuality(Container* cont, unsigned long groupID, unsigned long quality);

// <LegoRR.exe @00474da0>
BOOL __cdecl Container_Mesh_IsGroupHidden(Container* cont, unsigned long group);

// <LegoRR.exe @00474df0>
void __cdecl Container_Mesh_HideGroup(Container* cont, unsigned long group, BOOL hide);

// <LegoRR.exe @00474ec0>
BOOL __cdecl Container_Mesh_HandleSeperateMeshGroups(IN OUT IDirect3DRMMesh** mesh, IN OUT unsigned long* group);

// <LegoRR.exe @00474f00>
BOOL __cdecl Container_Mesh_GetGroup(Container* cont, unsigned long groupID,
								OUT unsigned long* vertexCount, OUT unsigned long* faceCount,
								OUT unsigned long* vPerFace, OUT unsigned long* faceDataSize,
								OUT unsigned long* faceData);

// <LegoRR.exe @00474f00>
unsigned long __cdecl Container_Mesh_GetVertices(Container* cont, unsigned long groupID, unsigned long index,
								unsigned long count, OUT VERTEX3D* retArray);

// <LegoRR.exe @00474ff0>
unsigned long __cdecl Container_Mesh_SetVertices(Container* cont, unsigned long groupID, unsigned long index,
								unsigned long count, const VERTEX3D* values);

// <LegoRR.exe @00475060>
void __cdecl Container_Mesh_SetTexture(Container* cont, unsigned long groupID, Container_Texture* itext);

// <LegoRR.exe @004750f0>
void __cdecl Container_Mesh_SetPerspectiveCorrection(Container* cont, unsigned long groupID, BOOL on);

// <LegoRR.exe @00475150>
BOOL __cdecl Container_Mesh_Scale(Container* cont, float x, float y, float z);

// <LegoRR.exe @004751d0>
BOOL __cdecl Container_Mesh_GetBox(Container* cont, OUT BOX3D* box);

// <LegoRR.exe @004752b0>
void __cdecl Container_Mesh_SetEmissive(Container* cont, unsigned long groupID,
								float r, float g, float b);

// <LegoRR.exe @004752e0>
void __cdecl Container_Mesh_SetColourAlpha(Container* cont, unsigned long groupID,
								float r, float g, float b, float a);

// <LegoRR.exe @00475330>
void __cdecl Container_Transform(Container* cont, OUT VECTOR3D* dest, const VECTOR3D* src);

// <LegoRR.exe @00475350>
void __cdecl Container_InverseTransform(Container* cont, OUT VECTOR3D* dest, const VECTOR3D* src);

// <LegoRR.exe @00475370>
void __cdecl Container_SetColourAlpha(Container* cont, float r, float g, float b, float a);

// <LegoRR.exe @004753e0>
float __cdecl Container_MoveAnimation(Container* cont, float delta);

// <LegoRR.exe @00475400>
float __cdecl Container_SetAnimationTime(Container* cont, float time);

// <LegoRR.exe @004755c0>
void __cdecl Container_ForceAnimationUpdate(Container* cont);

// <LegoRR.exe @00475650>
float __cdecl Container_GetAnimationTime(Container* cont);

// <LegoRR.exe @004756b0>
unsigned long __cdecl Container_GetAnimationFrames(Container* cont);

// <LegoRR.exe @004756f0>
void __cdecl Container_SetPosition(Container* cont, OPTIONAL Container* ref,
								float x, float y, float z);

// <LegoRR.exe @00475730>
void __cdecl Container_SetPosition(Container* cont, OPTIONAL Container* ref,
								float dirx, float diry, float dirz, float upx, float upy, float upz);

// <LegoRR.exe @00475780>
void __cdecl Container_GetPosition(Container* cont, OPTIONAL Container* ref, OUT VECTOR3D* pos);

// <LegoRR.exe @004757c0>
void __cdecl Container_GetOrientation(Container* cont, OPTIONAL Container* ref, OUT VECTOR3D* dir, OUT VECTOR3D* up);

// <LegoRR.exe @00475840>
void __cdecl Container_AddRotation(Container* cont, unsigned long combine,
								float x, float y, float z, float angle);

// <LegoRR.exe @00475870>
void __cdecl Container_AddScale(Container* cont, unsigned long combine,
								float x, float y, float z);

// <LegoRR.exe @004758a0>
void __cdecl Container_AddTranslation(Container* cont, unsigned long combine,
								float x, float y, float z);

// <LegoRR.exe @004758d0>
void __cdecl Container_ClearTransform(Container* cont);

// <LegoRR.exe @00475970>
void __cdecl Container_AddTransform(Container* cont, unsigned long combine, const MATRIX4D mat);

// <LegoRR.exe @00475990>
float __cdecl Container_GetZXRatio(Container* cont);

// <LegoRR.exe @004759d0>
void __cdecl Container_SetParent(Container* child, OPTIONAL Container* parent);

// <LegoRR.exe @00475a60>
Container* __cdecl Container_GetParent(Container* child);

// <LegoRR.exe @00475ab0>
float __cdecl Container_GetTransCoef(Container* cont);

// <LegoRR.exe @00475af0>
Container* __cdecl Container_SearchOwner(IDirect3DRMFrame3* frame);

// <LegoRR.exe @00475b40>
Container* __cdecl Container_Frame_GetContainer(IDirect3DRMFrame3* frame);

// <LegoRR.exe @00475bc0>
void __cdecl Container_GetFrames(Container* cont, OPTIONAL Container* ref, OUT IDirect3DRMFrame3** contFrame, OUT IDirect3DRMFrame3** refFrame);


// <LegoRR.exe @00475bf0>
Container_Type __cdecl Container_ParseTypeString(const char* str, OUT BOOL* noTexture);

// <LegoRR.exe @00475cb0>
void __cdecl Container_AddList(void);

// <LegoRR.exe @00475d30>
unsigned long __cdecl Container_GetActivities(Container* cont, OUT IDirect3DRMFrame3** frameList, OUT AnimClone** acList, OUT char** nameList);

// <LegoRR.exe @00475ec0>
void __cdecl Container_SetTypeData(Container* cont, OPTIONAL const char* name, OPTIONAL IDirect3DRMLight* light, OPTIONAL IDirect3DRMMesh* mesh, OPTIONAL Mesh* transMesh);

// <LegoRR.exe @00475f40>
void __cdecl Container_FreeTypeData(Container* cont);


// <LegoRR.exe @00475fd0>
BOOL __cdecl Container_AddActivity2(Container* cont, const char* filename, const char* actname, float transCo, unsigned long trigger, const char* sample, AnimClone* origClone, BOOL lws, BOOL looping);

// <LegoRR.exe @004760d0>
void __cdecl Container_Frame_ReferenceDestroyCallback(LPDIRECT3DRMOBJECT lpD3DRMobj, LPVOID lpArg);

// <LegoRR.exe @00476100>
IDirect3DRMFrame3* __cdecl Container_Frame_Find(Container* cont, const char* findName, BOOL /*unsigned long*/ hidden);

// <LegoRR.exe @00476230>
void __cdecl Container_Frame_SetAppData(IDirect3DRMFrame3* frame, Container* owner,
	OPTIONAL AnimClone* animClone, OPTIONAL const char* asfname, OPTIONAL unsigned long* frameCount,
	OPTIONAL const char* frameName, OPTIONAL float* currTime, OPTIONAL float* transCo,
	OPTIONAL const char* actSample, OPTIONAL void* soundRecord, OPTIONAL unsigned long* trigger);

// <LegoRR.exe @004763a0>
void __cdecl Container_Frame_RemoveAppData(IDirect3DRMFrame3* frame);

// <LegoRR.exe @004763a0>
Container* __cdecl Container_Frame_GetOwner(IDirect3DRMFrame3* frame);


// <LegoRR.exe @00476400>
const char* __cdecl Container_Frame_GetAnimSetFileName(IDirect3DRMFrame3* frame);

// <LegoRR.exe @00476420>
AnimClone* __cdecl Container_Frame_GetAnimClone(IDirect3DRMFrame3* frame);

// <LegoRR.exe @00476440>
unsigned long __cdecl Container_Frame_GetFrameCount(IDirect3DRMFrame3* frame);

// <LegoRR.exe @00476460>
float __cdecl Container_Frame_GetCurrTime(IDirect3DRMFrame3* frame);

// <LegoRR.exe @00476480>
float __cdecl Container_Frame_GetTransCo(IDirect3DRMFrame3* frame);

// <LegoRR.exe @004764a0>
const char* __cdecl Container_Frame_GetSample(IDirect3DRMFrame3* frame);

// <LegoRR.exe @004764c0>
unsigned long __cdecl Container_Frame_GetTrigger(IDirect3DRMFrame3* frame);

// <LegoRR.exe @004764e0>
void __cdecl Container_Frame_SafeAddChild(IDirect3DRMFrame3* parent, IDirect3DRMFrame3* child);

// <LegoRR.exe @00476530>
void __cdecl Container_Frame_FormatName(IDirect3DRMFrame3* frame, const char* msg, ...);

// <LegoRR.exe @004765b0>
void __cdecl Container_Frame_FreeName(IDirect3DRMFrame3* frame);

// <LegoRR.exe @004765d0>
const char* __cdecl Container_Frame_GetName(IDirect3DRMFrame3* frame);

// <LegoRR.exe @004765f0>
BOOL __cdecl Container_Frame_WalkTree(IDirect3DRMFrame3* frame, unsigned long level,
									ContainerWalkTreeCallback Callback, void* data);

// <LegoRR.exe @004766d0>
BOOL __cdecl Container_Frame_SearchCallback(IDirect3DRMFrame3* frame, void* data);

// <LegoRR.exe @00476880>
AnimClone* __cdecl Container_LoadAnimSet(const char* fname, IDirect3DRMFrame3* frame, OUT unsigned long* frameCount, BOOL lws, BOOL looping);

// <LegoRR.exe @00476a30>
unsigned long __cdecl Container_GetAnimFileFrameCount(const unsigned char* fileData);

// <LegoRR.exe @00476aa0>
BOOL __cdecl Container_FrameLoad(const char* fname, IDirect3DRMFrame3* frame);

// <LegoRR.exe @00476b10>
IDirect3DRMMesh* __cdecl Container_MeshLoad(void* file_data, unsigned long file_size, const char* file_name, IDirect3DRMFrame3* frame, BOOL noTexture);

// <LegoRR.exe @00476bc0>
HRESULT __cdecl Container_TextureLoadCallback(char* name, void* data, LPDIRECT3DRMTEXTURE3* texture);

// <LegoRR.exe @00476eb0>
void __cdecl Container_YFlipTexture(IDirect3DRMTexture3* texture);

// <LegoRR.exe @00476fa0>
int __cdecl Container_TextureSetSort(const void* a, const void* b);
//int __cdecl Container_TextureSetSort(Container_TextureRef* a, Container_TextureRef* b);

// <LegoRR.exe @00476fd0>
void __cdecl Container_TextureDestroyCallback(LPDIRECT3DRMOBJECT lpD3DRMobj, LPVOID lpArg);

#pragma endregion

}
