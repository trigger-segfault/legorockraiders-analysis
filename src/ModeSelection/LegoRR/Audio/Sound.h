// Sound.h : 
//

#pragma once

#include "../Common.h"


namespace lego {
namespace sound {

#pragma region Types

typedef void(__cdecl* MusicCallbackFunction)(void);

#pragma endregion


#pragma region Globals

namespace globals {

	// <LegoRR.exe @005075b8>
	extern IDirectSound* g_IDirectSound;
	// <LegoRR.exe @005075bc>
	extern IDirectSoundBuffer* g_IDirectSoundBuffer;
	// <LegoRR.exe @005075c0>
	extern IDirectSound3DListener* g_IDirectSound3DListener;
	// <LegoRR.exe @005075c4>
	extern IDirectSoundBuffer* g_IDirectSoundBuffer_Unk1;
	// <LegoRR.exe @005075c8>
	extern IDirectSoundBuffer* g_IDirectSoundBuffer_Unk2;

	// <LegoRR.exe @005075cc>
    // big global struct: AudioPlaybackData (size: 0x5c)
	extern unsigned int g_AudioPlaybackData_Unk1;
	// <LegoRR.exe @00507628>
    // big global struct: AudioPlaybackData (size: 0x5c)
	extern unsigned int g_AudioPlaybackData_Unk2;


	// <LegoRR.exe @00507684>
	extern void* PTR_00507684;
	// <LegoRR.exe @00507688>
	extern unsigned int DAT_00507688;
	// <LegoRR.exe @0050768c>
	extern float FLOAT_0050768c;
	// <LegoRR.exe @00507690>
	extern float FLOAT_00507690;
	// <LegoRR.exe @00507694>
	extern long g_SndUnkVolume;

	// <LegoRR.exe @00507698>
	/// SAMPLEDATATABLE:

	// <LegoRR.exe @00534878>
	extern BOOL g_DirectSoundEnabled;
	// <LegoRR.exe @0053487c>
	extern long DAT_0053487c;

	// <LegoRR.exe @0054586c>
	extern BOOL g_SoundEnabled;

	// <LegoRR.exe @00545a00>
	extern int g_MusicTrackIndex;
	// <LegoRR.exe @00545a04>
	extern int g_MusicState;
	// <LegoRR.exe @00545a08>
	extern MusicCallbackFunction g_MusicCallback;

	// <LegoRR.exe @00545a10>
	extern unsigned int g_MusicUpdateTime;

	// <LegoRR.exe @00545a1c>
	extern int g_mciLastError;

	// <LegoRR.exe @00577500>
	extern char g_mciErrorText[200];

	// <LegoRR.exe @00557f0c>
	extern unsigned int g_CDStartTrack;
	// <LegoRR.exe @00557f10>
	extern unsigned int g_CDTracks;
} /* namespace globals */

#pragma endregion


#pragma region Functions

// <LegoRR.exe @00488e10>
BOOL __cdecl InitSoundSystem(BOOL nosound);

// <LegoRR.exe @0047a900>
BOOL __cdecl InitDirectSound(HWND hWnd);

// <LegoRR.exe @0047b810>
void __cdecl SFX_SetIDirectSoundBufferVolume(void);


// <https://docs.microsoft.com/en-us/previous-versions/dd757161(v=vs.85)>
// <https://docs.microsoft.com/en-us/previous-versions/dd757158(v=vs.85)>


// <LegoRR.exe @00489520>
BOOL __cdecl Music_UpdateErrorString(void);

// <LegoRR.exe @00488e70>
void __cdecl Music_PlayTrack(int trackIndex, int musicState, MusicCallbackFunction callback);

// <LegoRR.exe @004895f0>
BOOL __cdecl Music_CDAudio_Open(int trackIndex);

// <LegoRR.exe @00489540>
BOOL __cdecl Music_IsTrackPlaying(int trackIndex);

// <LegoRR.exe @00488ec0>
void __cdecl Music_Update(BOOL isMusicOn);

// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-wsprintfa>
// 
// <LegoRR.exe @004894d0>
BOOL __cdecl Music_CDAudio_Play(int trackIndex);

// <LegoRR.exe @00488eb0>
BOOL __cdecl Music_CDAudio_Close(void);

// <LegoRR.exe @004296d0>
void __cdecl Music_CDAudio_PlayNextCallback(void);

// <LegoRR.exe @00414dd0>
void __cdecl Music_PlayNext_Not(BOOL isMusicOff);

// <LegoRR.exe @004296e0>
void __cdecl Music_PlayNext(BOOL isMusicOn);

// <LegoRR.exe @0047aac0>
void __cdecl CleanupDirectSound(void);

#pragma endregion


} /* namespace sound */
} /* namespace lego */
