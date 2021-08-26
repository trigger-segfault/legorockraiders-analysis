/*
#ifndef _GODS98_SOUND3D_H_
#define _GODS98_SOUND3D_H_

#define SOUND3D_VOLUME_MAX		1.0f
#define SOUND3D_VOLUME_MIN		1.0f

VOID Sound3D_Update(VOID);
float Sound3D_SetRollOffFactor(float);
VOID Sound3D_MakeContainerListener(struct Container *cont);
VOID Sound3D_SetMinDistForAtten(REAL);
VOID Sound3D_UpdateListener(VOID);
VOID Sound3D_ShutDown(VOID);
VOID Sound3D_StopAllSounds(VOID);
VOID Sound3D_Stream_Stop(BOOL);
VOID Sound3D_SetGlobalVolumePrescaled(signed long);
signed long Sound3D_Load(unsigned char *, BOOL, BOOL, signed long);
VOID Sound3D_Remove(signed long);
signed long Sound3D_PlayNormal(signed long, BOOL);
float Sound3D_GetSamplePlayTime(signed long l);
VOID Sound3D_SetBufferVolume(signed long, signed long);
signed long Sound3D_GetBufferVolume(signed long);
signed long Sound3D_PlayOnFrame(LPVOID v, signed long l, BOOL b);
signed long Sound3D_PlayOnPos(signed long l, BOOL loop, LPVOID v);
VOID Sound3D_StopSound(ULONG);

#ifdef _GODS98COMPILE

VOID Sound3D_SetMaxDist(REAL);
BOOL Sound3D_Initialise(HWND hWnd);
BOOL Sound3D_Initialised(VOID);

#endif // _GODS98COMPILE

#endif // _GODS98_SOUND3D_H_
*/


#ifndef _GODS98_SOUND3D_H_
#define _GODS98_SOUND3D_H_

#ifdef _GODS98COMPILE

#include "Standard.h"



#define SOUND3D_MAXSAMPLES						600

#define SOUND3D_MAXSIMULTANEOUS					3

#define SOUND3D_MAXUPDATEFRAMES					20

#define	SOUND3D_DEFAULTSOUNDVOLUME				-300


#define SOUND3D_FLAG_USED						0x00000001
#define SOUND3D_FLAG_ACTIVE						0x00000002
#define SOUND3D_FLAG_MULTI						0x00000004
#define SOUND3D_FLAG_STREAM						0x00000008

#define SOUND3D_NUMOFPLAYNOTIFICATIONS			4



typedef struct Sound3D_WaveDataTAG
{
    WAVEFORMATEX         *pwfx;		    // Wave Format data structure
    HMMIO                hmmio;		    // MM I/O handle for the WAVE
    MMCKINFO             mmck;		    // Multimedia RIFF chunk
    MMCKINFO             mmckInRIFF;	    // Use in opening a WAVE file
    //LPDIRECTSOUNDBUFFER  lpDSBStreamBuffer; // Points to DirectSoundBuffer
    DWORD                dwBufferSize;	    // Size of the entire buffer
	DWORD				 dwNotifySize;		// size of each notification period.
    DWORD                dwNextWriteOffset; // Offset to next buffer segment
    DWORD                dwProgress;	    // Used with above to show prog. 
	DWORD				dwNextProgressCheck;
	DWORD				 dwLastPos;			// the last play position returned by GetCurrentPos().
    //DWORD                dwBytesRemaining;  // Bytes 'til timer shutdown 
    BOOL                 bDonePlaying;	    // Signals early abort to timer 
    BOOL                 bLoopFile;	    // Should we loop playback? 
    BOOL                 bFoundEnd;	    // Timer found file end
} Sound3D_WaveData, *lpSound3D_WaveData;


typedef struct Sound3D_StreamDataTAG
{
	BOOL fileOpen;

	Sound3D_WaveData wiWave;

	//DWORD dsbCheckPos[NUM_PLAY_NOTIFICATIONS + 1];

	BOOL playing;

} Sound3D_StreamData, *lpSound3D_StreamData;


typedef struct Sound3D_SoundRecordTAG
{
	LPDIRECT3DRMFRAME3 frame;

	LPDIRECTSOUNDBUFFER soundBuff;
	LPDIRECTSOUND3DBUFFER sound3DBuff;

	struct Sound3D_SoundRecordTAG* next;

} Sound3D_SoundRecord, *lpSound3D_SoundRecord;


typedef struct Sound3D_SoundFrameRecordTAG
{
	LPDIRECTSOUND3DBUFFER sound3DBuff;

	D3DVECTOR pos;

	struct Sound3D_SoundFrameRecordTAG* next;

} Sound3D_SoundFrameRecord, *lpSound3D_SoundFrameRecord;


typedef struct Sound3D_SoundDataTAG
{
	UCHAR fName[MAX_PATH];
	ULONG size;
	ULONG avgBytesPerSec;				//ONLY SET FOR STREAMING BUFFERS
	ULONG freq;
	SLONG volume;
	ULONG offset;
	UCHAR *data;
	WAVEFORMATEX *pwf;
	LPDIRECTSOUNDBUFFER lpDsb3D[SOUND3D_MAXSIMULTANEOUS];
	ULONG voice;

	ULONG flags;

} Sound3D_SoundData, *lpSound3D_SoundData;


typedef struct Sound3D_GlobsTAG
{
	LPDIRECTSOUND lpDSnd;
	LPDIRECTSOUNDBUFFER lpDSBuff;
	LPDIRECTSOUND3DLISTENER lp3DListenerInfo;
	LPDIRECTSOUNDBUFFER lpDSStreamBuff;
	LPDIRECTSOUNDBUFFER lpDSLoopStreamBuff;

	Sound3D_StreamData streamData;
	Sound3D_StreamData loopStreamData;

	lpSound3D_SoundRecord soundRecord;

	LPDIRECT3DRMFRAME3 listenerFrame;

	REAL minDistanceForAttentuation;
	REAL maxDistance;
	SLONG volume;

	Sound3D_SoundData soundTable[SOUND3D_MAXSAMPLES];
	
	BOOL intialised;

	SLONG windowsVolume;

	ULONG flags;

	LPDIRECT3DRMFRAME3 updateFrameList[SOUND3D_MAXUPDATEFRAMES];

} Sound3D_Globs, *lpSound3D_Globs;



extern Sound3D_Globs sound3DGlobs;


__inline LPDIRECTSOUND lpDSnd()								{ return sound3DGlobs.lpDSnd; }
__inline LPDIRECTSOUNDBUFFER lpDSBuff()						{ return sound3DGlobs.lpDSBuff; }
__inline LPDIRECTSOUND3DLISTENER lp3DListenerInfo()			{ return sound3DGlobs.lp3DListenerInfo; }
__inline LPDIRECTSOUNDBUFFER lpDSStreamBuff(BOOL looping)	{ return looping?sound3DGlobs.lpDSLoopStreamBuff:sound3DGlobs.lpDSStreamBuff; }

#define Sound3D_Initialised()								sound3DGlobs.intialised

#else

typedef LPVOID lpSound3D_SoundFrameRecord;

#endif // _GODS98COMPILE

enum Sound3D_PlayTAG
{
	Sound3D_Play_OnFrame,
	Sound3D_Play_OnPos,
	Sound3D_Play_Normal

} Sound3D_Play;



#define Sound3D_PlayOnFrame( frame, sound, loop )			Sound3D_Play2( Sound3D_Play_OnFrame, (frame), (sound), (loop), NULL )
#define Sound3D_PlayOnCont( cont, sound, loop )				Sound3D_Play2( Sound3D_Play_OnFrame, (cont)->masterFrame, (sound), (loop), NULL )
#define Sound3D_PlayOnPos( sound, loop, wPos )				Sound3D_Play2( Sound3D_Play_OnPos, NULL, (sound), (loop), (wPos) )
#define Sound3D_PlayNormal( sound, loop )					Sound3D_Play2( Sound3D_Play_Normal, NULL, (sound), (loop), NULL )
#define Sound3D_MakeContainerListener( cont )				Sound3D_MakeListener( (cont)->masterFrame )
#define Sound3D_StopContainerSounds( cont )					Sound3D_StopFrameSounds( (cont)->masterFrame )
#define SOUND3D_VOLUME_MAX		Sound3D_MaxVolume()
#define SOUND3D_VOLUME_MIN		Sound3D_MinVolume()

REAL Sound3D_GetSamplePlayTime( SLONG handle );
BOOL Sound3D_Remove( SLONG soundTableIndex );
VOID Sound3D_SetBufferVolume(SLONG handle, SLONG newvolume);
SLONG Sound3D_GetBufferVolume(SLONG handle);
SLONG Sound3D_MaxVolume();
SLONG Sound3D_MinVolume();

#ifndef _GENPROTFILE
#include "..\Src\3DSound.prot"
#endif // _GENPROTFILE



#endif // _GODS98_SOUND3D_H_


