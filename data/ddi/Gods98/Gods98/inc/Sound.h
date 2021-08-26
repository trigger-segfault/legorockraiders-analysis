
#ifndef _GODS98_SOUND_H_
#define _GODS98_SOUND_H_

#include "Standard.h"

#ifdef _GODS98COMPILE
#include <windows.h>
#include <dsound.h>
#include <mmsystem.h>
#endif //_GODS98COMPILE

#define WAVEVERSION 1

#ifndef ER_MEM
#define ER_MEM 				0xe000
#endif

#ifndef ER_CANNOTOPEN
#define ER_CANNOTOPEN 		0xe100
#endif

#ifndef ER_NOTWAVEFILE
#define ER_NOTWAVEFILE 		0xe101
#endif

#ifndef ER_CANNOTREAD
#define ER_CANNOTREAD 		0xe102
#endif

#ifndef ER_CORRUPTWAVEFILE
#define ER_CORRUPTWAVEFILE	0xe103
#endif

#ifndef ER_CANNOTWRITE
#define ER_CANNOTWRITE		0xe104
#endif

#define SAMP_MULTI 2
#define SAMP_LOOP 1
#define SAMP_ONCE 0

#ifdef _GODS98COMPILE

/*
void Sample_Frequency(int n, float r);
void Sample_Volume(int n, float r);
void Sample_Stop(int n);

BOOL Play_Sample(int n, int f);
BOOL CreateSoundBuffer(int n);
BOOL SendSoundToBuffer(int n);

BOOL InitSound(HWND hwnd);
char *dsError(HRESULT hr);

int WaveStartDataRead(HMMIO *, MMCKINFO *, MMCKINFO *);
int WaveReadFile(HMMIO, UINT, BYTE *, MMCKINFO *, UINT *);

int WaveOpenFile(
	TCHAR*pszFileName,                              // (IN)
	HMMIO *phmmioIn,                                // (OUT)
	WAVEFORMATEX **ppwfxInfo,                       // (OUT)
	MMCKINFO *pckInRIFF                             // (OUT)
			);
*/
#endif // _GODS98COMPILE


#define MAX_SAMPLES 100

#define MULTI_SOUND 5

#ifdef _GODS98COMPILE

#ifndef SND_DEF
#define SND_DEF
typedef struct
{
	char sName[128];
	int sSize;
	int cFreq;
	int cVolume;
	int sOffset;
	int sActive;
	char *sData;
	WAVEFORMATEX *pwf;
	LPDIRECTSOUNDBUFFER lpDsb;
	LPDIRECTSOUNDBUFFER lpDsb3D;
#ifdef MULTI_SOUND
	LPDIRECTSOUNDBUFFER lpDsbM[MULTI_SOUND];
	LPDIRECTSOUNDBUFFER lpDsbM3D[MULTI_SOUND];
	int sVoice;
	int sVoice3D;
#endif
} SND;
#endif
extern SND sndTbl[MAX_SAMPLES];

#endif // _GODS98COMPILE

///Game Specific Stuff


enum
{
	SND_ENGINE,
	SND_SKID,
	SND_MUSIC1,
	SND_BRAKE,
	SND_BUMP,
	SND_SPLAT,
	SND_SPEEDUP,
	SND_REVERSE,
	SND_BESTTIME,
	SND_TUNNEL,
	SND_PICKUP,
	SND_INCIDENT1,
	SND_INCIDENT2,
	SND_INCIDENT3,
	SND_INCIDENT4,
	SND_VICTORY,
	SND_USESPEED,
	SND_POWERSLIDE,
	SND_LAND,
	SND_PICKUP2,
	SND_GRASS,
	SND_SAND,
	SND_OFFROAD,
	SND_RUMBLE,
	SND_MAX

};


#ifdef SNDPRC
char *sndName[]={
	{"SND_ENGINE"},
	{"SND_SKID"},
	{"SND_MUSIC1"},
	{"SND_BRAKE"},
	{"SND_BUMP"},
	{"SND_SPLAT"},
	{"SND_SPEEDUP"},
	{"SND_REVERSE"},
	{"SND_BESTTIME"},
	{"SND_TUNNEL"},
	{"SND_PICKUP"},
	{"SND_INCIDENT1"},
	{"SND_INCIDENT2"},
	{"SND_INCIDENT3"},
	{"SND_INCIDENT4"},
	{"SND_VICTORY"},
	{"SND_USESPEED"},
	{"SND_POWERSLIDE"},
	{"SND_LAND"},
	{"SND_PICKUP2"},
	{"SND_GRASS"},
	{"SND_SAND"},
	{"SND_OFFROAD"},
	{"SND_RUMBLE"},
};
#else
extern char *sndName[SND_MAX];
#endif

#define MCI_RETURN_SIZE 200


BOOL InitSamples(void);
void EngineSound(char *w1, char *w2, char *w3, char *w4);
void DisableSkidSound(void);
BOOL Play_CDTrack(long track);
BOOL Stop_CDTrack(void);
BOOL Status_CDTrack(long track);
BOOL Restart_CDTrack(long track);
BOOL Close_Sound(void);
void PlayPickupSound(int pickup);
void StopAllSounds(void);
int Load_Sample(int n, char *name);
BOOL InitSampleList(void);
void ReportCDError(void);
void ReportSoundError(void);

enum {
	Sound_Multi = SAMP_MULTI,
	Sound_Loop = SAMP_LOOP,
	Sound_Once = SAMP_ONCE
};

typedef struct Sound {

	ULONG handle;

} Sound, *lpSound;

typedef struct Sound_Globs {

	ULONG useSound;
	BOOL initialised;
	Sound soundList[MAX_SAMPLES];
	SLONG currTrack;
	BOOL loopCDTrack;
	VOID (*CDStopCallback)(VOID);
	BOOL updateCDTrack;

} Sound_Globs, *lpSound_Globs;

#ifndef _GENPROTFILE
#include "..\Src\Sound.prot"
#endif // _GENPROTFILE

#endif // _GODS98_SOUND_H_
