#pragma once

#include "../framework.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Function Typedefs
 **********************************************************************************/

#pragma region Function Typedefs

typedef void (__cdecl* SoundCDStopCallback)(void);

#pragma endregion

/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define WAVEVERSION 1

/*#ifndef ER_MEM
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
#endif*/

#define SAMP_MULTI 2
#define SAMP_LOOP 1
#define SAMP_ONCE 0

#define MAX_SAMPLES 100

#define MULTI_SOUND 5

#define MCI_RETURN_SIZE 200

#pragma endregion

/**********************************************************************************
 ******** Enumerations
 **********************************************************************************/

#pragma region Enums

enum
{
	Sound_Multi = SAMP_MULTI,
	Sound_Loop = SAMP_LOOP,
	Sound_Once = SAMP_ONCE
};

#pragma endregion

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

// (unused)
typedef struct
{
	char sName[128];
	int sSize;
	int cFreq;
	int cVolume;
	int sOffset;
	int sActive;
	char* sData;
	WAVEFORMATEX* pwf;
	IDirectSoundBuffer* lpDsb;
	IDirectSoundBuffer* lpDsb3D;
#ifdef MULTI_SOUND
	IDirectSoundBuffer* lpDsbM[MULTI_SOUND];
	IDirectSoundBuffer* lpDsbM3D[MULTI_SOUND];
	int sVoice;
	int sVoice3D;
#endif
} SND;


typedef struct Sound
{
	/*0,4*/ unsigned long handle;
	/*4*/
} Sound, *lpSound;
static_assert(sizeof(Sound) == 0x4, "");


typedef struct Sound_Globs
{
	/*000,4*/ unsigned long useSound;		// Number of sounds in soundList
	/*004,4*/ BOOL initialised;
	/*008,190*/ Sound soundList[MAX_SAMPLES];
	/*198,4*/ long currTrack;
	/*19c,4*/ BOOL loopCDTrack;
	/*1a0,4*/ SoundCDStopCallback CDStopCallback;
	/*1a4,4*/ BOOL updateCDTrack;
	/*1a8,4*/ unsigned long s_Update_lastUpdate;
	/*1ac,8*/ unsigned long reserved1[2];
	/*1b4,4*/ MCIERROR mciErr;
	/*1b8*/
} Sound_Globs;
static_assert(sizeof(Sound_Globs) == 0x1b8, "");

#pragma endregion

/**********************************************************************************
 ******** Globals
 **********************************************************************************/

#pragma region Globals

//extern SND sndTbl[MAX_SAMPLES];

// <LegoRR.exe @00545868>
extern Sound_Globs soundGlobs;

// <LegoRR.exe @mciReturn>
extern char mciReturn[MCI_RETURN_SIZE];

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @00488e10>
BOOL __cdecl Sound_Initialise(BOOL nosound);

// <LegoRR.exe @00488e50>
BOOL __cdecl Sound_IsInitialised(void);

// <LegoRR.exe @00488e70>
BOOL __cdecl Sound_PlayCDTrack(unsigned long track, unsigned long mode, SoundCDStopCallback StopCallback);

// <LegoRR.exe @00488eb0>
BOOL __cdecl Sound_StopCD(void);

// <LegoRR.exe @00488ec0>
void __cdecl Sound_Update(BOOL cdtrack);

// <LegoRR.exe @00488f30>
int __cdecl WaveOpenFile(void* fileData, unsigned long fileSize,
				OUT HMMIO* phmmioIn, OUT WAVEFORMATEX** ppwfxInfo, OUT MMCKINFO* pckInRIFF);

// <LegoRR.exe @00489130>
unsigned long __cdecl GetWaveAvgBytesPerSec(const char* pszFileName);

// <LegoRR.exe @004891d0>
int __cdecl WaveOpenFile2(IN const char* pszFileName,
				OUT HMMIO* phmmioIn, OUT WAVEFORMATEX** ppwfxInfo, OUT MMCKINFO* pckInRIFF);

// <LegoRR.exe @00489380>
int __cdecl WaveStartDataRead(HMMIO* phmmioIn, MMCKINFO* pckIn, MMCKINFO* pckInRIFF);

// <LegoRR.exe @004893c0>
int __cdecl WaveReadFile(IN HMMIO hmmioIn, IN unsigned int cbRead, IN unsigned char* pbDest,
				IN MMCKINFO* pckIn, OUT unsigned int* cbActualRead);

// <LegoRR.exe @00489490>
int __cdecl WaveCloseReadFile(IN HMMIO* phmmio, IN WAVEFORMATEX** ppwfxSrc);

// <LegoRR.exe @004894d0>
BOOL __cdecl Restart_CDTrack(long track);

// <LegoRR.exe @00489520>
void __cdecl ReportCDError(void);

// <LegoRR.exe @00489540>
BOOL __cdecl Status_CDTrack(long track);

// <LegoRR.exe @004895f0>
BOOL __cdecl Play_CDTrack(long track);

// <LegoRR.exe @00489660>
BOOL __cdecl Stop_CDTrack(void);

#pragma endregion

}
