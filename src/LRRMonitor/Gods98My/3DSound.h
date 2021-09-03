#pragma once

#include "../framework.h"
#include "Maths.h"


namespace Gods98
{; // !<---
	
/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define SOUND3D_MAXSAMPLES						600

#define SOUND3D_MAXSIMULTANEOUS					3

#define SOUND3D_MAXUPDATEFRAMES					20

#define	SOUND3D_DEFAULTSOUNDVOLUME				-300

#define SOUND3D_NUMOFPLAYNOTIFICATIONS			4

#pragma endregion
	
/**********************************************************************************
 ******** Enumerations
 **********************************************************************************/

#pragma region Enums

#define SOUND3D_FLAG_USED						0x00000001
#define SOUND3D_FLAG_ACTIVE						0x00000002
#define SOUND3D_FLAG_MULTI						0x00000004
#define SOUND3D_FLAG_STREAM						0x00000008


typedef enum Sound3D_PlayTAG
{
	Sound3D_Play_OnFrame,
	Sound3D_Play_OnPos,
	Sound3D_Play_Normal

} Sound3D_Play;
static_assert(sizeof(Sound3D_Play) == 0x4, "");

#pragma endregion

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

typedef struct Sound3D_WaveDataTAG
{
    /*00,4*/ WAVEFORMATEX*		 pwfx;		    // Wave Format data structure
	/*04,4*/ HMMIO                hmmio;		    // MM I/O handle for the WAVE
	/*08,14*/ MMCKINFO             mmck;		    // Multimedia RIFF chunk
	/*1c,14*/ MMCKINFO             mmckInRIFF;	    // Use in opening a WAVE file
    //LPDIRECTSOUNDBUFFER  lpDSBStreamBuffer; // Points to DirectSoundBuffer
	/*30,4*/ DWORD                dwBufferSize;	    // Size of the entire buffer
	/*34,4*/ DWORD				 dwNotifySize;		// size of each notification period.
	/*38,4*/ DWORD                dwNextWriteOffset; // Offset to next buffer segment
	/*3c,4*/ DWORD                dwProgress;	    // Used with above to show prog. 
	/*40,4*/ DWORD				dwNextProgressCheck;
	/*44,4*/ DWORD				 dwLastPos;			// the last play position returned by GetCurrentPos().
    //DWORD                dwBytesRemaining;  // Bytes 'til timer shutdown 
	/*48,4*/ BOOL                 bDonePlaying;	    // Signals early abort to timer 
	/*4c,4*/ BOOL                 bLoopFile;	    // Should we loop playback? 
	/*50,4*/ BOOL                 bFoundEnd;	    // Timer found file end
	/*54*/
} Sound3D_WaveData, *lpSound3D_WaveData;
static_assert(sizeof(Sound3D_WaveData) == 0x54, "");


typedef struct Sound3D_StreamDataTAG
{
	/*00,4*/ BOOL fileOpen;
	/*04,54*/ Sound3D_WaveData wiWave;
	//DWORD dsbCheckPos[NUM_PLAY_NOTIFICATIONS + 1];
	/*58,4*/ BOOL playing;
	/*c*/
} Sound3D_StreamData, *lpSound3D_StreamData;
static_assert(sizeof(Sound3D_StreamData) == 0x5c, "");


typedef struct Sound3D_SoundRecordTAG
{
	/*00,4*/ IDirect3DRMFrame3* frame;
	/*04,4*/ IDirectSoundBuffer* soundBuff;
	/*08,4*/ IDirectSound3DBuffer* sound3DBuff;
	/*0c,4*/ Sound3D_SoundRecord* next;
	/*10*/
} Sound3D_SoundRecord, *lpSound3D_SoundRecord;
static_assert(sizeof(Sound3D_SoundRecord) == 0x10, "");


typedef struct Sound3D_SoundFrameRecordTAG
{
	/*00,4*/ IDirectSound3DBuffer* sound3DBuff;
	/*04,c*/ D3DVECTOR pos;
	/*10,4*/ Sound3D_SoundFrameRecord* next;
	/*14*/
} Sound3D_SoundFrameRecord, *lpSound3D_SoundFrameRecord;
static_assert(sizeof(Sound3D_SoundFrameRecord) == 0x14, "");


typedef struct Sound3D_SoundDataTAG
{
	/*000,104*/ char fName[MAX_PATH];
	/*104,4*/ unsigned long size;
	/*108,4*/ unsigned long avgBytesPerSec;				//ONLY SET FOR STREAMING BUFFERS
	/*10c,4*/ unsigned long freq;
	/*110,4*/ long volume;
	/*114,4*/ unsigned long offset;
	/*118,4*/ unsigned char* data;
	/*11c,4*/ WAVEFORMATEX* pwf;
	/*120,c*/ IDirectSoundBuffer* lpDsb3D[SOUND3D_MAXSIMULTANEOUS];
	/*12c,4*/ unsigned long voice;
	/*130,4*/ unsigned long flags;
	/*134*/
} Sound3D_SoundData, *lpSound3D_SoundData;
static_assert(sizeof(Sound3D_SoundData) == 0x134, "");


typedef struct Sound3D_GlobsTAG
{
	/*00000,4*/ IDirectSound* lpDSnd;
	/*00004,4*/ IDirectSoundBuffer* lpDSBuff;
	/*00008,4*/ IDirectSound3DListener* lp3DListenerInfo;
	/*0000c,4*/ IDirectSoundBuffer* lpDSStreamBuff;
	/*00010,4*/ IDirectSoundBuffer* lpDSLoopStreamBuff;
	/*00014,5c*/ Sound3D_StreamData streamData;
	/*00070,5c*/ Sound3D_StreamData loopStreamData;
	/*000cc,4*/ Sound3D_SoundRecord* soundRecord;
	/*000d0,4*/ IDirect3DRMFrame3* listenerFrame;
	/*000d4,4*/ float minDistanceForAttentuation;
	/*000d8,4*/ float maxDistance;
	/*000dc,4*/ long volume;
	/*000e0,2d1e0*/ Sound3D_SoundData soundTable[SOUND3D_MAXSAMPLES];
	/*2d2c0,4*/ BOOL intialised;
	/*2d2c4,4*/ long windowsVolume;
	/*2d2c8,4*/ unsigned long flags;
	/*2d2cc,50*/ IDirect3DRMFrame3* updateFrameList[SOUND3D_MAXUPDATEFRAMES];
	/*2d31c,4*/ unsigned long reserved1;
	/*2d320,c*/ VECTOR3D s_ListenerCallback_oldPos;
	/*2d32c,4*/ unsigned long reserved2;
	/*2d330,c*/ VECTOR3D s_ListenerCallback_oldOrien;
	/*2d33c,4*/ unsigned long reserved3;
	/*2d340,c*/ VECTOR3D s_ListenerCallback_oldOrienUp;
	/*2d34c*/
} Sound3D_Globs;
static_assert(sizeof(Sound3D_Globs) == 0x2d34c, "");

#pragma endregion

/**********************************************************************************
 ******** Globals
 **********************************************************************************/

#pragma region Globals

// <LegoRR.exe @005075b8>
extern Sound3D_Globs sound3DGlobs;

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @0047a900>
BOOL __cdecl Sound3D_Initialise(HWND hwndParent);

// <LegoRR.exe @0047aac0>
void __cdecl Sound3D_ShutDown(void);

// <LegoRR.exe @0047ab10>
BOOL __cdecl Sound3D_CheckVolumeLimits(long vol);

// <LegoRR.exe @0047ab30>
long __cdecl Sound3D_Load(const char* fName, BOOL stream, BOOL simultaneous, long volume);

// <LegoRR.exe @0047ad90>
BOOL __cdecl Sound3D_GetFreeSoundIndex(OUT unsigned long* soundTableIndex);

// <LegoRR.exe @0047adc0>
BOOL __cdecl Sound3D_Remove(long soundTableIndex);

// <LegoRR.exe @0047ae40>
void __cdecl Sound3D_MakeListener(IDirect3DRMFrame3* frame);

// <LegoRR.exe @0047ae60>
void __cdecl Sound3D_UpdateListener(void);

// <LegoRR.exe @0047ae80>
void __cdecl Sound3D_ListenerCallback(LPDIRECT3DRMFRAME3 obj, void* arg, D3DVALUE delta);

// <LegoRR.exe @0047afd0>
void __cdecl Sound3D_SetWorldPos(IDirectSound3DBuffer* sound3DBuff, const VECTOR3D* wPos, const VECTOR3D* vel);

// <LegoRR.exe @0047aff0>
BOOL __cdecl Sound3D_CheckAlreadyExists(IDirect3DRMFrame3* frame, IDirectSound3DBuffer* sound3DBuff);

// <LegoRR.exe @0047b030>
long __cdecl Sound3D_Play2(Sound3D_Play play, IDirect3DRMFrame3* frame, long soundTableIndex, BOOL loop, OPTIONAL const VECTOR3D* wPos);

// <LegoRR.exe @0047b2e0>
void __cdecl Sound3D_AddSoundRecord(IDirect3DRMFrame3* frame, IDirectSoundBuffer* soundBuff, IDirectSound3DBuffer* sound3DBuff);

// <LegoRR.exe @0047b310>
void __cdecl Sound3D_SetBufferVolume(long handle, long newvolume);

// <LegoRR.exe @0047b390>
long __cdecl Sound3D_GetBufferVolume(long handle);

// <LegoRR.exe @0047b3b0>
IDirectSoundBuffer* __cdecl Sound3D_GetSoundBuffer(long soundHandle);

// <LegoRR.exe @0047b3f0>
void __cdecl Sound3D_StopSound(long soundHandle);

// <LegoRR.exe @0047b420>
void __cdecl Sound3D_StopAllSounds(void);

// <LegoRR.exe @0047b460>
void __cdecl Sound3D_AttachSound(IDirect3DRMFrame3* frame, IDirectSound3DBuffer* sound3DBuff);

// <LegoRR.exe @0047b4e0>
void __cdecl Sound3D_RemoveSound(IDirect3DRMFrame3* owner, IDirectSound3DBuffer* sound3DBuff);

// <LegoRR.exe @0047b560>
void __cdecl Sound3D_RemoveSoundRecord(IDirect3DRMFrame3* frame, IDirectSound3DBuffer* sound3DBuff);

// <LegoRR.exe @0047b5a0>
BOOL __cdecl Sound3D_RecurseRemoveSoundRecord(IDirect3DRMFrame3* owner, IDirectSound3DBuffer* sound3DBuff, Sound3D_SoundRecord* record);

// <LegoRR.exe @0047b5f0>
BOOL __cdecl Sound3D_RecurseRemoveSound(IDirect3DRMFrame3* owner, IDirectSound3DBuffer* sound3DBuff, Sound3D_SoundFrameRecord* record);

// <LegoRR.exe @0047b650>
void __cdecl Sound3D_Update(void);

// <LegoRR.exe @0047b6d0>
void __cdecl Sound3D_SoundCallback(LPDIRECT3DRMFRAME3 tFrame, void* arg, D3DVALUE delay);

// <LegoRR.exe @0047b760>
void __cdecl Sound3D_SetMinDistForAtten(float dist);

// <LegoRR.exe @0047b790>
void __cdecl Sound3D_SetMaxDist(float dist);

// <LegoRR.exe @0047b7c0>
void __cdecl Sound3D_SetGlobalVolume(long vol);

// <LegoRR.exe @0047b7f0>
void __cdecl Sound3D_SetGlobalVolumePrescaled(long vol);

// <LegoRR.exe @0047b810>
void __cdecl Sound3D_SetVolumeToDefault(void);

// <LegoRR.exe @0047b840>
BOOL __cdecl Sound3D_LoadSample(OUT Sound3D_SoundData* sound, const char* fName, BOOL simultaneous);

// <LegoRR.exe @0047b980>
BOOL __cdecl Sound3D_CreateSoundBuffer(Sound3D_SoundData* sound, BOOL simultaneous);

// <LegoRR.exe @0047ba50>
BOOL __cdecl Sound3D_SendSoundToBuffer(Sound3D_SoundData* sound);

// <LegoRR.exe @0047bba0>
float __cdecl Sound3D_GetSamplePlayTime(long handle);

// <LegoRR.exe @0047bc30>
BOOL __cdecl Sound3D_Stream_Play(const char* fName, BOOL loop, long volume);

// <LegoRR.exe @0047bce0>
BOOL __cdecl Sound3D_Stream_Stop(BOOL looping);

// <LegoRR.exe @0047bd60>
BOOL __cdecl Sound3D_Stream_BufferSetup(const char* waveFName, BOOL loop, long volume);

// <LegoRR.exe @0047bef0>
BOOL __cdecl Sound3D_Stream_FillDataBuffer(BOOL looping);

// <LegoRR.exe @0047c070>
void __cdecl Sound3D_Stream_CheckPosition(BOOL looping);

// <LegoRR.exe @0047c380>
BOOL __cdecl Sound3D_D3DVectorEqual(const D3DVECTOR* a, const D3DVECTOR* b);

// <LegoRR.exe @0047c3c0>
float __cdecl Sound3D_SetRollOffFactor(float rollOff);

// <LegoRR.exe @0047c420>
long __cdecl Sound3D_MinVolume(void);


// (shared)
//long __cdecl Sound3D_MaxVolume(void); // return 0;










__inline LPDIRECTSOUND lpDSnd()								{ return sound3DGlobs.lpDSnd; }
__inline LPDIRECTSOUNDBUFFER lpDSBuff()						{ return sound3DGlobs.lpDSBuff; }
__inline LPDIRECTSOUND3DLISTENER lp3DListenerInfo()			{ return sound3DGlobs.lp3DListenerInfo; }
__inline LPDIRECTSOUNDBUFFER lpDSStreamBuff(BOOL looping)	{ return looping?sound3DGlobs.lpDSLoopStreamBuff:sound3DGlobs.lpDSStreamBuff; }

#define Sound3D_Initialised()								sound3DGlobs.intialised


#define Sound3D_PlayOnFrame( frame, sound, loop )			Sound3D_Play2( Sound3D_Play_OnFrame, (frame), (sound), (loop), NULL )
#define Sound3D_PlayOnCont( cont, sound, loop )				Sound3D_Play2( Sound3D_Play_OnFrame, (cont)->masterFrame, (sound), (loop), NULL )
#define Sound3D_PlayOnPos( sound, loop, wPos )				Sound3D_Play2( Sound3D_Play_OnPos, NULL, (sound), (loop), (wPos) )
#define Sound3D_PlayNormal( sound, loop )					Sound3D_Play2( Sound3D_Play_Normal, NULL, (sound), (loop), NULL )
#define Sound3D_MakeContainerListener( cont )				Sound3D_MakeListener( (cont)->masterFrame )
#define Sound3D_StopContainerSounds( cont )					Sound3D_StopFrameSounds( (cont)->masterFrame )
#define SOUND3D_VOLUME_MAX		Sound3D_MaxVolume()
#define SOUND3D_VOLUME_MIN		Sound3D_MinVolume()

/*REAL Sound3D_GetSamplePlayTime( SLONG handle );
BOOL Sound3D_Remove( SLONG soundTableIndex );
VOID Sound3D_SetBufferVolume(SLONG handle, SLONG newvolume);
SLONG Sound3D_GetBufferVolume(SLONG handle);
SLONG Sound3D_MaxVolume();
SLONG Sound3D_MinVolume();*/

#pragma endregion

}
