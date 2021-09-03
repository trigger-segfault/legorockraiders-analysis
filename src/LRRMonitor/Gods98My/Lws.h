#pragma once

#include "../framework.h"
#include "Maths.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Forward Declarations
 **********************************************************************************/

#pragma region Forward Declarations

struct Mesh;

#pragma endregion

/**********************************************************************************
 ******** Function Typedefs
 **********************************************************************************/

#pragma region Function Typedefs

typedef BOOL (__cdecl* LwsFindSFXIDFunc)(const char* name, OUT unsigned long* sfxID);
typedef BOOL (__cdecl* LwsSoundEnabledFunc)(void);
typedef long (__cdecl* LwsPlaySample3DFunc)(void* frame, unsigned long type, BOOL loop, BOOL onCont, const VECTOR3D* wPos);

#pragma endregion

/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define LWS_FILESUFFIX				"lws"
#define LWS_HEADER1					"LWSC"
#define LWS_HEADER2					"1"
#define LWS_SOUNDTRIGGERPREFIX		"SFX"
#define LWS_SOUNDTRIGGERSEPERATOR	","

#define LWS_MAXLINELEN				1024
#define LWS_MAXARGS					20
#define LWS_NODELISTBLOCKSIZE		10
#define LWS_MAXMESHFILES			1000
#define LWS_MAXSTATICDISSOLVES		100
#define LWS_MAXTRIGGERKEYS			25

#pragma endregion

/**********************************************************************************
 ******** Enumerations
 **********************************************************************************/

#pragma region Enums

#define LWS_FLAG_LOOPING			0x01

#define LWSNODE_FLAG_NULL			0x01
#define LWSNODE_FLAG_SOUNDTRIGGER	0x02
#define LWSNODE_FLAG_FACECAMERA		0x04

#pragma endregion

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

typedef struct Lws_SoundTrigger
{
	//	Sound* sound;
	/*00,4*/ unsigned long sfxID;
	/*04,32*/ unsigned short frameStartList[LWS_MAXTRIGGERKEYS];
	/*36,32*/ unsigned short frameEndList[LWS_MAXTRIGGERKEYS];
	/*68,64*/ unsigned long loopUID[LWS_MAXTRIGGERKEYS];
	/*cc,2*/ unsigned short count;
	/*ce,2*/ unsigned short padding1;
	/*d0*/
} Lws_SoundTrigger, *lpLws_SoundTrigger;
static_assert(sizeof(Lws_SoundTrigger) == 0xd0, "");


typedef struct Lws_KeyInfo
{
	/*00,c*/ VECTOR3D position;
	/*0c,c*/ VECTOR3D hpb;
	/*18,c*/ VECTOR3D scale;
	/*24,2*/ unsigned short frame;
	/*26,2*/ unsigned short padding1;
	/*28*/
} Lws_KeyInfo, *lpLws_KeyInfo;
static_assert(sizeof(Lws_KeyInfo) == 0x28, "");


typedef struct Lws_Node
{
	/*00,4*/ char* name;
	/*04,2*/ unsigned short reference;
	/*06,2*/ unsigned short frameIndex;
	/*08,1*/ unsigned char triggerIndex;
	/*09,3*/ unsigned char padding1[3];
	/*0c,c*/ VECTOR3D pivotVector;
	/*18,4*/ Lws_KeyInfo* keyList;
	/*1c,4*/ float* dissolveLevel;
	/*20,4*/ unsigned short* dissolveFrame;
	/*24,2*/ unsigned short keyCount;
	/*26,2*/ unsigned short dissolveCount;
	/*28,1*/ unsigned char flags;
	/*29,3*/ unsigned char padding2[3];
	/*2c,4*/ Lws_Node *childList;
	/*30,4*/ Lws_Node *next;
	/*34*/
} Lws_Node, *lpLws_Node;
static_assert(sizeof(Lws_Node) == 0x34, "");


typedef struct Lws_Info
{
	/*00,2*/ unsigned short firstFrame;
	/*02,2*/ unsigned short lastFrame;
	/*04,4*/ float fps;
	/*08,4*/ char* filePath;
	/*0c,4*/ float lastTime;
	/*10,4*/ float time;
	/*14,4*/ IDirect3DRMFrame3* frameList;
	/*18,4*/ Lws_SoundTrigger* triggerList;
	/*1c,4*/ Lws_Node* masterNode;
	/*20,4*/ Lws_Node* nodeList;
	/*24,2*/ unsigned short nodeCount;
	/*26,2*/ unsigned short nodeListSize;
	/*28,2*/ unsigned short triggerCount;
	/*2a,2*/ unsigned short padding1;
	/*2c,4*/ Lws_Info* clonedFrom;
	/*30,4*/ unsigned long referenceCount;
	/*34,1*/ unsigned char flags;
	/*35,3*/ unsigned char padding2[3];
	/*38*/
} Lws_Info, *lpLws_Info;
static_assert(sizeof(Lws_Info) == 0x38, "");


typedef struct Lws_MeshPath
{
	/*0,4*/ char* path;
	/*4,4*/ Mesh* mesh;
	/*8*/
} Lws_MeshPath, *lpLws_MeshPath;
static_assert(sizeof(Lws_MeshPath) == 0x8, "");


typedef struct Lws_Globs
{
	/*0000,1f40*/ Lws_MeshPath meshPathList[LWS_MAXMESHFILES];			// For full path to files...
	/*1f40,1f40*/ Lws_MeshPath meshPathListShared[LWS_MAXMESHFILES];	// For shared files...
	/*3e80,4*/ char* sharedDir;
	/*3e84,4*/ unsigned long meshPathCount;
	/*3e88,4*/ unsigned long meshPathCountShared;
	/*3e8c,190*/ float staticDissolveLevel[LWS_MAXSTATICDISSOLVES];
	/*401c,4*/ unsigned long staticDissolveCount;
	/*4020,4*/ LwsFindSFXIDFunc FindSFXIDFunc;
	/*4024,4*/ LwsSoundEnabledFunc SoundEnabledFunc;
	/*4028,4*/ LwsPlaySample3DFunc PlaySample3DFunc;
	/*402c*/
} Lws_Globs;
static_assert(sizeof(Lws_Globs) == 0x402c, "");

#pragma endregion

/**********************************************************************************
 ******** Globals
 **********************************************************************************/

#pragma region Globals

// <LegoRR.exe @00541838>
extern Lws_Globs lwsGlobs;

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @00486cb0>
Lws_Info* __cdecl Lws_Parse(const char* fname, BOOL looping);

// <LegoRR.exe @00487980>
Lws_Info* __cdecl Lws_Initialise(const char* sharedDir, LwsFindSFXIDFunc FindSFXID,
								LwsPlaySample3DFunc PlaySample3D, LwsSoundEnabledFunc SoundEnabled);

// <LegoRR.exe @00487a20>
void __cdecl Lws_Shutdown(void);

// <LegoRR.exe @00487a90>
unsigned long __cdecl Lws_GetFrameCount(Lws_Info* scene);

// <LegoRR.exe @00487aa0>
void __cdecl Lws_SetupSoundTriggers(Lws_Info* scene);

// <LegoRR.exe @00487c50>
void __cdecl Lws_LoadMeshes(Lws_Info* scene, IDirect3DRMFrame3* parent);

// <LegoRR.exe @00487cc0>
Lws_Info* __cdecl Lws_Clone(Lws_Info* scene, IDirect3DRMFrame3* parent);

// <LegoRR.exe @00487e60>
void __cdecl Lws_SetTime(Lws_Info* scene, float time);

// <LegoRR.exe @00487f70>
float __cdecl Lws_FindPrevKey(Lws_Node* node, float time, unsigned short* prev);

// <LegoRR.exe @00488010>
void __cdecl Lws_AnimateTextures(Lws_Info* scene, Lws_Node* node);

// <LegoRR.exe @004880a0>
void __cdecl Lws_HandleTrigger(Lws_Info* scene, Lws_Node* node);

// <LegoRR.exe @00488190>
BOOL __cdecl Lws_KeyPassed(Lws_Info* scene, unsigned long key);

// <LegoRR.exe @00488280>
float __cdecl Lws_FindPrevDissolve(Lws_Node* node, float time, unsigned short* prev);

// <LegoRR.exe @00488330>
void __cdecl Lws_InterpolateDissolve(Lws_Info* scene, Lws_Node* node, unsigned short prev, float delta);

// <LegoRR.exe @00488390>
void __cdecl Lws_SetDissolveLevel(Lws_Info* scene, Lws_Node* node, float level);

// <LegoRR.exe @00488430>
void __cdecl Lws_InterpolateKeys(Lws_Info* scene, Lws_Node* node, unsigned short key, float delta);

// <LegoRR.exe @004885a0>
void __cdecl Lws_SetupNodeTransform(Lws_Info* scene, Lws_Node* node, const VECTOR3D* pos, const VECTOR3D* hpb, const VECTOR3D* scale);

// <LegoRR.exe @00488880>
Mesh* __cdecl Lws_LoadMesh(const char* baseDir, const char* fname, IDirect3DRMFrame3* frame, BOOL noTextures);

// <LegoRR.exe @004889f0>
Mesh* __cdecl Lws_SearchMeshPathList(Lws_MeshPath* list, unsigned long count, const char* path);

// <LegoRR.exe @00488a50>
void __cdecl Lws_AddMeshPathEntry(Lws_MeshPath* list, unsigned long count, const char* path, Mesh* mesh);

// <LegoRR.exe @00488a80>
void __cdecl Lws_CreateFrames(Lws_Info* scene, Lws_Node* node, IDirect3DRMFrame3* parent, IN OUT unsigned short* frameCount);

// <LegoRR.exe @00488bc0>
void __cdecl Lws_LoadNodes(Lws_Info* scene, Lws_Node* node);

// <LegoRR.exe @00488c60>
void __cdecl Lws_SetAbsoluteKey(Lws_Info* scene, Lws_Node* node, unsigned short key);

// <LegoRR.exe @00488c90>
void __cdecl Lws_Free(Lws_Info* scene);

// <LegoRR.exe @00488d30>
void __cdecl Lws_FreeNode(Lws_Info* scene, Lws_Node* node);

#pragma endregion

}
