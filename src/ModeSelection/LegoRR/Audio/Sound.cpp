// Sound.cpp : 
//

#include "Sound.h"
#include "../Main/Main.h"


#pragma region Globals
namespace lego {
namespace sound {
namespace globals {

	// <LegoRR.exe @005075b8>
    IDirectSound* g_IDirectSound;
    // <LegoRR.exe @005075bc>
    IDirectSoundBuffer* g_IDirectSoundBuffer;
    // <LegoRR.exe @005075c0>
    IDirectSound3DListener* g_IDirectSound3DListener;
    // <LegoRR.exe @005075c4>
    IDirectSoundBuffer* g_IDirectSoundBuffer_Unk1;
    // <LegoRR.exe @005075c8>
    IDirectSoundBuffer* g_IDirectSoundBuffer_Unk2;

    // <LegoRR.exe @005075cc>
    // big global struct: AudioPlaybackData (size: 0x5c)
    unsigned int g_AudioPlaybackData_Unk1;
    // <LegoRR.exe @00507628>
    // big global struct: AudioPlaybackData (size: 0x5c)
    unsigned int g_AudioPlaybackData_Unk2;


    // <LegoRR.exe @00507684>
    void* PTR_00507684;
    // <LegoRR.exe @00507688>
    unsigned int DAT_00507688;
    // <LegoRR.exe @0050768c>
    float FLOAT_0050768c;
    // <LegoRR.exe @00507690>
    float FLOAT_00507690;
    // <LegoRR.exe @00507694>
    long g_SndUnkVolume;

    // <LegoRR.exe @00507698>
    /// SFXDATATABLE:

    // <LegoRR.exe @00534878>
    BOOL g_DirectSoundEnabled;
    // <LegoRR.exe @0053487c>
    long DAT_0053487c;

    // <LegoRR.exe @0054586c>
    BOOL g_SoundEnabled;

    // <LegoRR.exe @00545a00>
    int g_MusicTrackIndex = 0;
    // <LegoRR.exe @00545a04>
    int g_MusicState = 0;
    // <LegoRR.exe @00545a08>
    MusicCallbackFunction g_MusicCallback = nullptr;

    // <LegoRR.exe @00545a10>
    unsigned int g_MusicUpdateTime = 0;

    // <LegoRR.exe @00545a1c>
    int g_mciLastError = 0;

    // <LegoRR.exe @00577500>
    char g_mciErrorText[200] = { 0 };

    // <LegoRR.exe @00557f0c>
    unsigned int g_CDStartTrack = 2;
    // <LegoRR.exe @00557f10>
    unsigned int g_CDTracks = 3;
} /* namespace globals */
} /* namespace sound */
} /* namespace lego */
#pragma endregion


#pragma region Functions (custom)

#ifdef DEBUG_IGNORECD

/// for use with DEBUG_IGNORECD preprocessor
static BOOL g_HasLocalCDAudio;

BOOL __cdecl CheckForLocalCDAudio(void)
{
    char filepath[MAX_PATH /*260*/];
    _finddata32_t fileinfo;
    
    g_HasLocalCDAudio = FALSE;

    _getcwd(filepath, sizeof(filepath));
    if (filepath[0] != '\0' && filepath[std::strlen(filepath) - 1] == '\\') {
        filepath[std::strlen(filepath) - 1] = '\0';
    }
    std::strcat(filepath, "\\Music\\Track*.*");
    
    intptr_t handle = _findfirst32(filepath, &fileinfo);
    if (handle != -1) { // -1 for failure
        do {
            if (!(fileinfo.attrib & FILE_ATTRIBUTE_DIRECTORY) && _strnicmp(fileinfo.name, "Track", 5) == 0) {
                g_HasLocalCDAudio = TRUE;
                break;
            }
        } while (_findnext32(handle, &fileinfo) == 0);
        _findclose(handle);
    }

    return g_HasLocalCDAudio;
}
#endif

#pragma endregion


#pragma region Functions (real)

// <LegoRR.exe @00488e10>
BOOL __cdecl lego::sound::InitSoundSystem(BOOL nosound)
{
    globals::g_SoundEnabled = !nosound;
    debugf("g_SoundEnabled = %i\n", (int)globals::g_SoundEnabled);
    #ifdef DEBUG_IGNORECD
    CheckForLocalCDAudio();
    #endif
    globals::g_MusicState = -1;
    if (nosound) {
        globals::g_MusicState = -1;
        return TRUE;
    }

    /// DEBUG:
    //return TRUE;
    return InitDirectSound(main::globals::g_hWnd);
}


// <LegoRR.exe @0047a900>
BOOL __cdecl lego::sound::InitDirectSound(HWND hWnd)
{

    globals::g_DirectSoundEnabled = FALSE;
    globals::DAT_00507688 = 0;
    do {
        if (DirectSoundCreate(nullptr, &globals::g_IDirectSound, nullptr) == 0) {
            if (globals::g_IDirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY /*0x2*/) == 0) {

                DSBUFFERDESC dsBuffer;
                dsBuffer.dwSize = 0;
                dsBuffer.dwFlags = 0;

                dsBuffer.dwSize = sizeof(DSBUFFERDESC);// 0x14;
                // Is this actually supposed to be DSBCAPS???
                dsBuffer.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER /*0x91*/;
                dsBuffer.dwBufferBytes = 0;
                dsBuffer.dwReserved = 0;
                dsBuffer.lpwfxFormat = nullptr;
                /*local_20 = 0x14;
                local_1c = 0x91;
                local_18 = iVar2;
                local_14 = iVar2;
                local_10 = iVar2;*/
                /*DWORD           dwSize;
                DWORD           dwFlags;
                DWORD           dwBufferBytes;
                DWORD           dwReserved;
                LPWAVEFORMATEX  lpwfxFormat;
#if DIRECTSOUND_VERSION >= 0x0700
                GUID            guid3DAlgorithm;*/
                if (globals::g_IDirectSound->CreateSoundBuffer(&dsBuffer, &globals::g_IDirectSoundBuffer, nullptr) == 0) {
                    WAVEFORMATEX waveFmt;
                    waveFmt.wFormatTag = 0x1; // PCM?
                    waveFmt.nChannels = 2;
                    waveFmt.nSamplesPerSec = 22050; // DWORD
                    waveFmt.nAvgBytesPerSec = 88200; // DWORD
                    waveFmt.nBlockAlign = 4;
                    waveFmt.wBitsPerSample = 16;
                    waveFmt.cbSize = 0;
                    globals::g_IDirectSoundBuffer->SetFormat(&waveFmt);
                    if (globals::g_IDirectSoundBuffer->QueryInterface(IID_IDirectSound3DListener, (void**)&globals::g_IDirectSound3DListener) == 0) {
                        globals::g_IDirectSound3DListener->SetDopplerFactor(100.0f, 0);
                        goto LAB_0047aa15;
                    }
                    globals::g_IDirectSoundBuffer->Release();
                    goto LAB_0047aa04;
                    /*if (HVar1 == 0) {
                        (*(code*)globals::g_IDirectSound3DListener->lpVtbl->SetDopplerFactor)
                            (globals::g_IDirectSound3DListener, &DAT_42c80000, 0);
                        goto LAB_0047aa15;
                    }
                    (*globals::g_IDirectSoundBuffer->lpVtbl->Release)
                        ((IUnknown*)globals::g_IDirectSoundBuffer);*/
                }
                globals::g_IDirectSound->Release();
            }
            else {
            LAB_0047aa04:
                globals::g_IDirectSound->Release();
            }
            globals::g_IDirectSound = nullptr;
        }
    LAB_0047aa15:
        DWORD playFlags;
        if (globals::g_IDirectSound == nullptr) {
            playFlags = DSBPLAY_LOCSOFTWARE | DSBPLAY_LOOPING /*0x5*/;
        }
        else {
            playFlags = DSBPLAY_LOOPING /*0x1*/;
            globals::g_DirectSoundEnabled = TRUE;
        }
        if (playFlags != DSBPLAY_LOCSOFTWARE /*0x4*/) {
            if (globals::g_DirectSoundEnabled) {
                // <http://doc.51windows.net/Directx9_SDK/htm/directsoundinterfaces.htm>
                globals::g_IDirectSoundBuffer->Play(0, 0, playFlags);
                // DS3D_DEFERRED (0x1) or DS3D_IMMEDIATE (0x0)
                globals::g_IDirectSound3DListener->SetRolloffFactor(1.0f, DS3D_DEFERRED /*0x1*/);
                globals::g_IDirectSound3DListener->SetDopplerFactor(0.0f, DS3D_DEFERRED /*0x1*/);
                globals::g_IDirectSound3DListener->CommitDeferredSettings();
                globals::FLOAT_0050768c = 1.0;
                globals::FLOAT_00507690 = 800.0;
                globals::g_IDirectSoundBuffer->GetVolume(&globals::DAT_0053487c);
                SFX_SetIDirectSoundBufferVolume();
            }
            return TRUE;
        }
    } while (true);
}

// <LegoRR.exe @0047b810>
void __cdecl lego::sound::SFX_SetIDirectSoundBufferVolume(void)
{
    if (globals::g_DirectSoundEnabled) {
        globals::g_SndUnkVolume = -300;
        globals::g_IDirectSoundBuffer->SetVolume(-300);
    }
}


// <https://docs.microsoft.com/en-us/previous-versions/dd757161(v=vs.85)>
// <https://docs.microsoft.com/en-us/previous-versions/dd757158(v=vs.85)>


// <LegoRR.exe @00489520>
BOOL __cdecl lego::sound::Music_UpdateErrorString(void)
{
	return mciGetErrorStringA(globals::g_mciLastError, globals::g_mciErrorText, sizeof(globals::g_mciErrorText));
}

// <LegoRR.exe @00488e70>
void __cdecl lego::sound::Music_PlayTrack(int trackIndex, int musicState, MusicCallbackFunction callback)
{
    debugf("Music_PlayTrack\n");
    #ifdef DEBUG_IGNORECD
    if (globals::g_SoundEnabled && g_HasLocalCDAudio)
    #else
	if (globals::g_SoundEnabled)
    #endif
    {
        debugf("globals::g_SoundEnabled = 1\n");
		if (musicState == 1) {
            globals::g_MusicState = 1; // TRUE;
		}
        globals::g_MusicTrackIndex = trackIndex;
        globals::g_MusicCallback = callback;
		Music_CDAudio_Open(trackIndex);
	}
}

// <LegoRR.exe @004895f0>
BOOL __cdecl lego::sound::Music_CDAudio_Open(int trackIndex)
{
    debugf("Music_CDAudio_Open\n");
    globals::g_mciLastError = mciSendStringA("open cdaudio", globals::g_mciErrorText, sizeof(globals::g_mciErrorText), nullptr);
	if (globals::g_mciLastError == 0) {
        globals::g_mciLastError = mciSendStringA("set cdaudio time format tmsf", globals::g_mciErrorText, sizeof(globals::g_mciErrorText), nullptr);
		if (globals::g_mciLastError == 0) {
			Music_CDAudio_Play(trackIndex);
			if (globals::g_mciLastError == 0) {
                debugf("Music_CDAudio_Open success\n");
				return TRUE;
			}
		}
	}
	Music_UpdateErrorString();
    debugf("Music_CDAudio_Open: mci error [%i] %s\n", globals::g_mciLastError, (char*)globals::g_mciErrorText);
	return FALSE;
}

// <LegoRR.exe @00489540>
BOOL __cdecl lego::sound::Music_IsTrackPlaying(int trackIndex)
{
	// int currentTrack;
	char buffer[100];

	// get audio mode
	std::sprintf(buffer, "status cdaudio mode");
    globals::g_mciLastError = mciSendStringA(buffer, globals::g_mciErrorText, sizeof(globals::g_mciErrorText), nullptr);
	if (_stricmp(globals::g_mciErrorText, "stopped") != 0) { // audio is playing (/paused?)

		// get current audio track
		std::sprintf(buffer, "status cdaudio current track");
        globals::g_mciLastError = mciSendStringA(buffer, globals::g_mciErrorText, sizeof(globals::g_mciErrorText), nullptr);
		int currentTrack = std::atoi(globals::g_mciErrorText);

		if (currentTrack <= trackIndex + 1)
			return TRUE;
	}
	Music_UpdateErrorString();
    debugf("Music_IsTrackPlaying: mci error [%i] %s\n", globals::g_mciLastError, (char*)globals::g_mciErrorText);
	return FALSE;
}

// <LegoRR.exe @00488ec0>
void __cdecl lego::sound::Music_Update(BOOL isMusicOn)
{
    #ifdef DEBUG_IGNORECD
    if (!globals::g_SoundEnabled || !g_HasLocalCDAudio)
    #else
	if (!globals::g_SoundEnabled)
    #endif
		return;

	unsigned int currentTime = timeGetTime();
	unsigned int lastTime = globals::g_MusicUpdateTime; // keeping this in-case there's some awkward multithreading race condition...
	if (currentTime > lastTime + 4000) {
		unsigned int nextTime = currentTime; // current time is updated even when isMusicOn is false

		if (isMusicOn && !Music_IsTrackPlaying(globals::g_MusicTrackIndex)) {
			if (globals::g_MusicState != 0)
				Music_CDAudio_Play(globals::g_MusicTrackIndex);

			if (globals::g_MusicCallback != nullptr)
				(*globals::g_MusicCallback)();
		}
		globals::g_MusicUpdateTime = nextTime;
	}
}

// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-wsprintfa>
// 
// <LegoRR.exe @004894d0>
BOOL __cdecl lego::sound::Music_CDAudio_Play(int trackIndex)
{
	char buffer[100];
    debugf("Music_CDAudio_Play\n");

	wsprintfA(buffer, "play cdaudio from %i", trackIndex + 1);
    globals::g_mciLastError = mciSendStringA(buffer, globals::g_mciErrorText, sizeof(globals::g_mciErrorText), nullptr);
	if (globals::g_mciLastError != 0) {
		Music_UpdateErrorString();
        debugf("Music_CDAudio_Play: mci error [%i] %s\n", globals::g_mciLastError, (char*)globals::g_mciErrorText);
		return FALSE;
	}
	return TRUE;
}

// <LegoRR.exe @00488eb0>
BOOL __cdecl lego::sound::Music_CDAudio_Close(void)
{
    #ifdef DEBUG_IGNORECD
    if (!globals::g_SoundEnabled || !g_HasLocalCDAudio)
    #else
	if (!globals::g_SoundEnabled)
    #endif
		return TRUE;

	globals::g_mciLastError = mciSendStringA("stop cdaudio", globals::g_mciErrorText, sizeof(globals::g_mciErrorText), nullptr);
	if (globals::g_mciLastError == 0 /*success*/) {
        globals::g_mciLastError = mciSendStringA("close cdaudio", globals::g_mciErrorText, sizeof(globals::g_mciErrorText), nullptr);
		if (globals::g_mciLastError == 0 /*success*/) {
			return TRUE;
		}
	}
	Music_UpdateErrorString();
    debugf("Music_CDAudio_Close: mci error [%i] %s\n", globals::g_mciLastError, (char*)globals::g_mciErrorText);
	return FALSE;
}

// <LegoRR.exe @004296d0>
void __cdecl lego::sound::Music_CDAudio_PlayNextCallback(void)
{
	Music_CDAudio_Close();
	Music_PlayNext(TRUE);
}

// <LegoRR.exe @00414dd0>
void __cdecl lego::sound::Music_PlayNext_Not(BOOL isMusicOff)
{
	Music_PlayNext(!isMusicOff);
}

// <LegoRR.exe @004296e0>
void __cdecl lego::sound::Music_PlayNext(BOOL isMusicOn)
{
	if (isMusicOn) {
        debugf("Music_PlayNext\n");
        short sVar1 = (short)std::rand(); // randomInt16();
		//g_GAME_GameFlags1 |= 8; // CDTrack playing?
		Music_PlayTrack(((unsigned int)(int)sVar1 % globals::g_CDTracks - 1) + globals::g_CDStartTrack, 0, Music_CDAudio_PlayNextCallback);
	}
	else {
		//globals::g_GAME_GameFlags1 &= ~0x8 /*0xfffffff7*/; // CDTrack not playing?
		Music_CDAudio_Close();
		Music_Update(FALSE);
	}
}

/*// <LegoRR.exe @0047aac0>
void __cdecl lego::sound::FUN_0047b7c0(int param_1)
{
    BOOL BVar1;

    if (globals::g_DirectSoundEnabled) {
        BVar1 = SFX_IsValidVolumeModifier(param_1);
        if (BVar1 != 0) {
            globals::g_SndUnkVolume = param_1;
            (globals::g_IDirectSoundBuffer->lpVtbl->SetVolume)
                (globals::g_IDirectSoundBuffer, param_1);
        }
    }
    return;
}*/

// <LegoRR.exe @0047aac0>
void __cdecl lego::sound::CleanupDirectSound(void)
{
	if (globals::g_DirectSoundEnabled) {
        //FUN_0047b7c0(DAT_0053487c);
        globals::g_IDirectSoundBuffer->Stop();
        globals::g_IDirectSoundBuffer->Release();
        globals::g_IDirectSound->Release();
        globals::g_IDirectSound = nullptr;
        globals::g_DirectSoundEnabled = FALSE;
	}
}

#pragma endregion
