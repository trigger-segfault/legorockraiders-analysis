
#ifndef _GODS98_LWS_H_
#define _GODS98_LWS_H_

#include "..\inc\Maths.h"
#include "..\inc\Mesh.h"

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

#define LWS_FLAG_LOOPING			0x01

#define LWSNODE_FLAG_NULL			0x01
#define LWSNODE_FLAG_SOUNDTRIGGER	0x02
#define LWSNODE_FLAG_FACECAMERA		0x04

typedef struct Lws_SoundTrigger {

//	lpSound sound;
	ULONG sfxID;
	UWORD frameStartList[LWS_MAXTRIGGERKEYS];
	UWORD frameEndList[LWS_MAXTRIGGERKEYS];
	ULONG loopUID[LWS_MAXTRIGGERKEYS];
	UWORD count;

} Lws_SoundTrigger, *lpLws_SoundTrigger;

typedef struct Lws_KeyInfo {

	VECTOR3D position;
	VECTOR3D hpb;
	VECTOR3D scale;
	UWORD frame;

} Lws_KeyInfo, *lpLws_KeyInfo;

typedef struct Lws_Node {

	LPUCHAR name;
	UWORD reference, frameIndex;
	UCHAR triggerIndex;

	VECTOR3D pivotVector;
	struct Lws_KeyInfo *keyList;

	LPREAL dissolveLevel;
	LPUWORD dissolveFrame;

	UWORD keyCount, dissolveCount;

	UCHAR flags;

	struct Lws_Node *childList;
	struct Lws_Node *next;

} Lws_Node, *lpLws_Node;

typedef struct Lws_Info {

	UWORD firstFrame, lastFrame;
	REAL fps;
	LPUCHAR filePath;

	REAL lastTime, time;

	LPDIRECT3DRMFRAME3 *frameList;
	struct Lws_SoundTrigger *triggerList;

	struct Lws_Node *masterNode;
	struct Lws_Node *nodeList;

	UWORD nodeCount, nodeListSize, triggerCount;

	struct Lws_Info *clonedFrom;
	ULONG referenceCount;

	UCHAR flags;

} Lws_Info, *lpLws_Info;

typedef struct Lws_MeshPath {

	LPUCHAR path;
	lpMesh mesh;

} Lws_MeshPath, *lpLws_MeshPath;

typedef struct Lws_Globs {

	struct Lws_MeshPath meshPathList[LWS_MAXMESHFILES];			// For full path to files...
	struct Lws_MeshPath meshPathListShared[LWS_MAXMESHFILES];	// For shared files...
	LPUCHAR sharedDir;
	ULONG meshPathCount, meshPathCountShared;
	REAL staticDissolveLevel[LWS_MAXSTATICDISSOLVES];
	ULONG staticDissolveCount;

//	BOOL (*FindSoundFunc)(LPUCHAR name, lpSound *sound);
	BOOL (*FindSFXIDFunc)(LPUCHAR name, LPULONG sfxID);
	BOOL (*SoundEnabledFunc)(VOID);
	SLONG (*PlaySample3DFunc)(LPVOID frame, ULONG type, BOOL loop, BOOL onCont, LPVECTOR3D wPos);

//	SLONG (*GetSoundFunc)(ULONG id);
//	ULONG (*FindSFXIDFunc)(LPUCHAR name, LPULONG id);
//	ULONG (*PlaySFXFunc)(ULONG id, BOOL loop, LPVECTOR3D pos);
//	VOID (*StopSFXFunc)(ULONG uid);

#ifdef _DEBUG
	BOOL initialised;
#endif // _DEBUG

} Lws_Globs, *lpLws_Globs;

#ifndef _GENPROTFILE
#include "..\Src\Lws.prot"
#endif // !_GENPROTFILE

#endif // !_GODS98_LWS_H_
