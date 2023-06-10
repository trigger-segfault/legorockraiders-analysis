
#ifndef _RGL_SOUND_H
#define _RGL_SOUND_H

#define SOUND_VOLUME_MIN				-10000
#define SOUND_VOLUME_MAX				0
#define SOUND_PAN_LEFT					-10000
#define SOUND_PAN_RIGHT					10000
#define SOUND_FREQUENCY_ORIGINAL		0
#define SOUND_FREQUENCY_MIN				100
#define SOUND_FREQUENCY_MAX				100000

#define SOUNDLOAD_FLAG_USESHARED		0x00000001
#define SOUNDLOAD_FLAG_ENABLE3D			0x00000002
#define SOUNDLOAD_FLAG_STREAMED			0x00000004
#define SOUNDLOAD_FLAG_STREAMEDLOOP		(0x00000008|SOUNDLOAD_FLAG_STREAMED)

#ifdef _RGL

#include "Files.h"

#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>

#define SOUND_DRIVERNAMELENGTH			128

#define SOUND_FLAG_ORIGINAL				0x00000001
#define SOUND_FLAG_LOOPING				0x00000002
#define SOUND_FLAG_PAUSED				0x00000004
#define SOUND_FLAG_NEWFRAME				0x00000008
#define SOUND_FLAG_3DENABLED			0x00000010
#define SOUND_FLAG_PLAYNEXTUPDATE		0x00000020
#define SOUND_FLAG_SECONDHALF			0x00000040
#define SOUND_FLAG_STREAMEDLOOP			0x00000080
#define SOUND_FLAG_BUFFERFULL			0x00000100
#define SOUND_FLAG_STREAMSTARTED		0x00000200

struct SoundDriver {

	GUID guid;
	UCHAR name[SOUND_DRIVERNAMELENGTH];
	BOOL nullGuid;
};

struct SoundStreamData {

	HMMIO hmmio;
	MMCKINFO mmckinfoData;
	MMCKINFO mmckinfoParent;
	ULONG bufferEnd, lastPos;

	ULONG threadID;
	HANDLE threadHandle;
};

struct Sound {

	struct SoundStreamData *streamData;

	LPDIRECTSOUNDBUFFER buffer;
	LPDIRECTSOUND3DBUFFER buffer3D;
	struct Frame *frame;
	DS3DBUFFER params;
	ULONG flags;
	REAL blockTimeout;

	LPVOID userData;

#ifdef _DEBUG
	UCHAR fname[FILE_MAXPATH];
	LPUCHAR file;
	ULONG line;
#endif // _DEBUG

	struct Sound *removeListNext;
	struct Sound *removeListPrev;
};

#endif // _RGL

typedef struct Sound				*lpSound;
typedef struct SoundDriver			*lpSoundDriver;
typedef struct SoundStreamData		*lpSoundStreamData;

#ifdef _DEBUG
#define Sound_Load(fi,fl)			Sound_Debug_Load((fi),(fl),__FILE__,__LINE__)
#endif // _DEBUG


extern VOID __cdecl Sound_Initialise(VOID);
extern VOID __cdecl Sound_Shutdown(VOID);
extern BOOL __cdecl Sound_IsInitialised(VOID);
#ifdef _DEBUG
extern lpSound __cdecl Sound_Debug_Load(LPUCHAR fname, ULONG loadFlags, LPUCHAR file, ULONG line);
#else // _DEBUG
extern lpSound __cdecl Sound_Load(LPUCHAR fname, ULONG loadFlags);
#endif // _DEBUG
extern VOID __cdecl Sound_Block(lpSound sound, REAL timeout);
extern SLONG __cdecl Sound_GetTime(lpSound sound);
extern VOID __cdecl Sound_Pause(lpSound sound, BOOL pause);
extern VOID __cdecl Sound_StopAll(VOID (*callback)(lpSound sound, LPVOID data), LPVOID data);
extern VOID __cdecl Sound_RunThroughList(BOOL originals, BOOL (*callback)(lpSound sound, LPVOID data), LPVOID data);
extern VOID __cdecl Sound_Remove(lpSound sound);
extern VOID __cdecl Sound_SetGlobalVolume(REAL volume);
extern REAL __cdecl Sound_GetGlobalVolume(VOID);
extern VOID __cdecl Sound_SetFinishedCallback(BOOL (*finishedCallback)(lpSound sound, LPVOID data), LPVOID data);
extern ULONG __cdecl Sound_Update(REAL delta);
extern VOID __cdecl Sound_PlayStream(lpSound streamedSound, BOOL nextUpdate);
extern lpSound __cdecl Sound_Play(lpSound original, BOOL looping, BOOL nextUpdate);
extern VOID __cdecl Sound_SetFrame(lpSound sound, struct Frame * frame);
extern VOID __cdecl Sound_SetDistances(lpSound sound, REAL minDistance, REAL maxDistance);
extern VOID __cdecl Sound_SetListenerFrame(struct Frame * frame);
extern VOID __cdecl Sound_SetListenerRolloffFactor(REAL factor);
extern VOID __cdecl Sound_SetListenerDistanceFactor(REAL factor);
extern VOID __cdecl Sound_SetListenerDopplerFactor(REAL factor);
extern VOID __cdecl Sound_SetVolume(lpSound sound, REAL value);
extern VOID __cdecl Sound_SetPan(lpSound sound, REAL pan);
extern VOID __cdecl Sound_SetFrequency(lpSound sound, SLONG frequency);
extern REAL __cdecl Sound_GetVolume(lpSound sound);
extern REAL __cdecl Sound_GetPan(lpSound sound);
extern SLONG __cdecl Sound_GetFrequency(lpSound sound);
extern VOID __cdecl Sound_SetUserData(lpSound sound, LPVOID data);
extern LPVOID __cdecl Sound_GetUserData(lpSound sound);

#endif // _RGL_SOUND_H
