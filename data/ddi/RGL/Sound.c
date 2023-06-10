
#include <dsound.h>

#include "Standard.h"
#include "DirectX.h"
#include "Frames.h"
#include "Errors.h"
#include "Files.h"
#include "Lists.h"
#include "Main.h"
#include "Mem.h"
#include "Sound.h"

#pragma comment ( lib, "dsound" )

#define SOUND_STREAMBUFFERTIME			8

//#ifdef _DEBUG
//#define SOUND_NOTHREADS
//#endif // _DEBUG

static BOOL __cdecl Sound_Start(lpSound sound);
static VOID __cdecl Sound_UpdateListener(REAL delta);
static BOOL __cdecl Sound_UpdatePositionCallback(lpSound sound, LPREAL delta);
static BOOL __cdecl Sound_ReadMMIO(HMMIO hmmioIn, WAVEFORMATEX **ppwfxInfo, MMCKINFO *pckInRIFF);
static BOOL __cdecl Sound_WaveOpenFile(LPUCHAR fname, HMMIO *hmmioIn, WAVEFORMATEX **ppwfxInfo, MMCKINFO *pckInRIFF);
static BOOL __cdecl Sound_WaveStartDataRead(HMMIO phmmioIn, MMCKINFO* pckIn, MMCKINFO* pckInRIFF);
static BOOL __cdecl Sound_WaveReadFile(HMMIO hmmioIn, UINT cbRead, LPUCHAR pbDest, MMCKINFO *pckIn, LPULONG cbActualRead);
static SLONG __cdecl Sound_GetDirectSoundVolume(REAL volume);
static REAL __cdecl Sound_GetRealVolume(SLONG dsVolume);

#define SOUNDGLOBS_FLAG_NEWLISTENER		0x00000001

struct SoundGlobs {

	struct List *list;
	struct List *streamDataList;
	struct List *sharedObjectList;

	struct SoundDriver *driverList;
	ULONG driverCount;
	LPDIRECTSOUND directSound;
	LPDIRECTSOUNDBUFFER primaryBuffer;
	DSCAPS primaryBufferCaps;
	LPDIRECTSOUND3DLISTENER listener;
	DS3DLISTENER listenerParams;
	lpFrame listenerFrame;
	lpSound removeList;

	BOOL (*finishedCallback)(lpSound sound, LPVOID data);
	LPVOID finishedCallbackData;

	SLONG volumeConvertionTable[256];

	REAL globalVolume;

	ULONG flags;

} soundGlobs = { 0 };

BOOL CALLBACK Sound_DSEnumCallback(LPGUID lpGuid, LPCSTR description, LPCSTR module, LPVOID data) {

	lpSoundDriver driver;

	soundGlobs.driverList = Mem_ReAllocClear(soundGlobs.driverList, sizeof(soundGlobs.driverList[0]) * (soundGlobs.driverCount + 1));
	driver = &soundGlobs.driverList[soundGlobs.driverCount];

	if (lpGuid) driver->guid = *lpGuid;
	else driver->nullGuid = TRUE;

	Error_Fatal(strlen(description) + 1 > SOUND_DRIVERNAMELENGTH, "SOUND_DRIVERNAMELENGTH too small");
	sprintf(driver->name, "%s", description);

	soundGlobs.driverCount++;

	return TRUE;
}

__inline BOOL Sound_IsInitialised(VOID) {

	return (NULL != soundGlobs.primaryBuffer);
}

VOID Sound_Initialise(VOID) {

	HRESULT r;
	ULONG loop, resolution = sizeof(soundGlobs.volumeConvertionTable) / sizeof(soundGlobs.volumeConvertionTable[0]);

	for (loop=0 ; loop<resolution ; loop++) {

		REAL f = (REAL) pow(2, 8 * (1.0f - (loop / (REAL) resolution)));
		soundGlobs.volumeConvertionTable[loop] = (SLONG) ((10240.0f / f) - 40.0f);
	}

//	DirectSoundEnumerate(Sound_DSEnumCallback, NULL);

	if (SUCCEEDED(r = DirectSoundCreate(NULL, &soundGlobs.directSound, NULL))) {

		soundGlobs.list = List_Create(sizeof(struct Sound));
		soundGlobs.streamDataList = List_Create(sizeof(struct SoundStreamData));
		soundGlobs.sharedObjectList = File_CreateSharedObjectList();

		DirectX_InitStruct(&soundGlobs.primaryBufferCaps);

		r = soundGlobs.directSound->lpVtbl->GetCaps(soundGlobs.directSound, &soundGlobs.primaryBufferCaps);
		Error_DirectX(r, "GetCaps");

		if (SUCCEEDED(r = soundGlobs.directSound->lpVtbl->SetCooperativeLevel(soundGlobs.directSound, Main_hWnd(), DSSCL_PRIORITY))) {
			
			DSBUFFERDESC desc;

			DirectX_InitStruct(&desc);

			desc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;

			if (SUCCEEDED(soundGlobs.directSound->lpVtbl->CreateSoundBuffer(soundGlobs.directSound, &desc, &soundGlobs.primaryBuffer, NULL))) {

				WAVEFORMATEX format = { 0 };

				format.wFormatTag = WAVE_FORMAT_PCM;
				format.nChannels = 2;
				format.nSamplesPerSec = 44100;
				format.wBitsPerSample = 16;
				format.nBlockAlign = format.nChannels * (format.wBitsPerSample / 8);
				format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;

				if (SUCCEEDED(r = soundGlobs.primaryBuffer->lpVtbl->SetFormat(soundGlobs.primaryBuffer, &format))) {
					if (SUCCEEDED(r = soundGlobs.primaryBuffer->lpVtbl->QueryInterface(soundGlobs.primaryBuffer, &IID_IDirectSound3DListener, &soundGlobs.listener))) {

						DirectX_InitStruct(&soundGlobs.listenerParams);

						if (SUCCEEDED(r = soundGlobs.listener->lpVtbl->GetAllParameters(soundGlobs.listener, &soundGlobs.listenerParams))) {

							SLONG volume;

							soundGlobs.primaryBuffer->lpVtbl->GetVolume(soundGlobs.primaryBuffer, &volume);
							soundGlobs.globalVolume = 1.0f + Sound_GetRealVolume(volume);

							return;

						} else Error_DirectX(r, "GetAllParameters");
					} else Error_DirectX(r, "QueryInterface");
				} else Error_DirectX(r, "SetFormat");
			} else Error_DirectX(r, "CreateSoundBuffer");
		} else Error_DirectX(r, "SetCooperativeLevel");
	} else Error_Warn(TRUE, "Cannot initalise DirectSound");

	Main_ReportError(MainErrorType_SoundInitialise);
}

BOOL Sound_ShutdownCallback(lpSound sound, LPVOID data) {

	Sound_Remove(sound);

	return FALSE;
}

VOID Sound_Shutdown(VOID) {

	if (soundGlobs.directSound) {

		List_RunThrough(soundGlobs.list, Sound_ShutdownCallback, NULL);	
		List_Remove(soundGlobs.list);
		soundGlobs.list = NULL;

		List_Remove(soundGlobs.streamDataList);
		soundGlobs.streamDataList = NULL;

		File_RemoveSharedObjectList(soundGlobs.sharedObjectList);
		soundGlobs.sharedObjectList = NULL;

		if (soundGlobs.primaryBuffer) soundGlobs.primaryBuffer->lpVtbl->Release(soundGlobs.primaryBuffer);
		soundGlobs.primaryBuffer = NULL;
		if (soundGlobs.listener) soundGlobs.listener->lpVtbl->Release(soundGlobs.listener);
		soundGlobs.listener = NULL;
		if (soundGlobs.directSound) soundGlobs.directSound->lpVtbl->Release(soundGlobs.directSound);
		soundGlobs.directSound = NULL;

	}
}

__inline static SLONG Sound_GetDirectSoundVolume(REAL volume) {

	SLONG resolution = sizeof(soundGlobs.volumeConvertionTable) / sizeof(soundGlobs.volumeConvertionTable[0]);
	SLONG index;
	BOOL negative;

	if (volume < 0.0f) {
		volume = -volume;
		negative = TRUE;
	} else negative = FALSE;

	index = (ULONG) (volume * (REAL) (resolution - 1));
	index = min(index, resolution - 1);
	index = max(index, 0);

	return negative?-soundGlobs.volumeConvertionTable[index]:soundGlobs.volumeConvertionTable[index];
}

__inline static REAL Sound_GetRealVolume(SLONG dsVolume) {

	SLONG resolution = sizeof(soundGlobs.volumeConvertionTable) / sizeof(soundGlobs.volumeConvertionTable[0]);
	SLONG loop;
	REAL value;
	BOOL negative;

	if (dsVolume < 0) {
		dsVolume = -dsVolume;
		negative = TRUE;
	} else negative = FALSE;

	for (loop=0 ; loop<resolution-1 ; loop++) {
		if (soundGlobs.volumeConvertionTable[loop] >= dsVolume) break;
	}

	value = loop / (resolution - 1.0f);

	return negative?-value:value;
}

static VOID Sound_Enable3D(lpSound sound) {

	HRESULT r;

	Error_Fatal(NULL == sound, "NULL passed as sound to Sound_Enable3D()");
	List_CheckItem(soundGlobs.list, sound);

	if (SUCCEEDED(r = sound->buffer->lpVtbl->QueryInterface(sound->buffer, &IID_IDirectSound3DBuffer, &sound->buffer3D))) {

		DirectX_InitStruct(&sound->params);

		r = sound->buffer3D->lpVtbl->GetAllParameters(sound->buffer3D, &sound->params);
		Error_DirectX(r, "GetAllParameters");

		sound->flags |= SOUND_FLAG_3DENABLED;

	} else Error_DirectX(r, "QueryInterface");
}

static BOOL Sound_FillBuffer(lpSound sound, HMMIO hmmio, LPMMCKINFO mmckinfoData, LPMMCKINFO mmckinfoParent) {

	HRESULT r;
	ULONG flags;
	LPVOID data;
	ULONG length;
	DSBCAPS caps;
	ULONG bytesRead = 0;
	ULONG lockStart, lockSize;

	Error_Fatal(NULL == sound, "NULL passed as sound to Sound_FillBuffer()");
	List_CheckItem(soundGlobs.list, sound);

	DirectX_InitStruct(&caps);

	if (SUCCEEDED(r = sound->buffer->lpVtbl->GetCaps(sound->buffer, &caps))) {

		if (sound->streamData) {

			lockSize = caps.dwBufferBytes / 2;

			if (sound->flags & SOUND_FLAG_SECONDHALF) {

				lockStart = caps.dwBufferBytes / 2;
				sound->flags &= ~SOUND_FLAG_SECONDHALF;

			} else {
			
				lockStart = 0;
				sound->flags |= SOUND_FLAG_SECONDHALF;

			}
			
			flags = 0;

		} else {

			lockStart = 0;
			lockSize = caps.dwBufferBytes;
			flags = DSBLOCK_ENTIREBUFFER;

		}

		if (SUCCEEDED(r = sound->buffer->lpVtbl->Lock(sound->buffer, lockStart, lockSize, &data, &length, NULL, NULL, flags))) {

			if (Sound_WaveReadFile(hmmio, length, data, mmckinfoData, &bytesRead)) {

				if (sound->streamData) {
					if (bytesRead < length) {

						if (sound->flags & SOUND_FLAG_STREAMEDLOOP) {

							Sound_WaveStartDataRead(hmmio, mmckinfoData, mmckinfoParent);
							Sound_WaveReadFile(hmmio, length - bytesRead, &((LPUCHAR) data)[bytesRead], mmckinfoData, &bytesRead);

						} else {

							sound->streamData->bufferEnd = lockStart + bytesRead;
							sound->flags |= SOUND_FLAG_BUFFERFULL;

						}
					}
				}

				if (SUCCEEDED(r = sound->buffer->lpVtbl->Unlock(sound->buffer, data, length, NULL, 0))) {

					return TRUE;

				} else Error_DirectX(r, "Unlock");
			}

			r = sound->buffer->lpVtbl->Unlock(sound->buffer, data, length, NULL, 0);
			Error_DirectX(r, "Unlock");

		} else Error_DirectX(r, "Lock");

	} else Error_DirectX(r, "GetCaps");

	return FALSE;
}

#ifdef _DEBUG
lpSound Sound_Debug_Load(LPUCHAR fname, ULONG loadFlags, LPUCHAR file, ULONG line) {
#else // _DEBUG
lpSound Sound_Load(LPUCHAR fname, ULONG loadFlags) {
#endif // _DEBUG

	lpSound sound = NULL;
	BOOL useShared = (SOUNDLOAD_FLAG_USESHARED == (loadFlags & SOUNDLOAD_FLAG_USESHARED));
	BOOL enable3D = (SOUNDLOAD_FLAG_ENABLE3D == (loadFlags & SOUNDLOAD_FLAG_ENABLE3D));
	BOOL streamed = (SOUNDLOAD_FLAG_STREAMED == (loadFlags & SOUNDLOAD_FLAG_STREAMED));
	BOOL streamedLoop = (SOUNDLOAD_FLAG_STREAMEDLOOP == (loadFlags & SOUNDLOAD_FLAG_STREAMEDLOOP));

	if (NULL == soundGlobs.directSound) return NULL;

	if (!useShared || (NULL == (sound = File_FindSharedObject(soundGlobs.sharedObjectList, fname)))) {

		HMMIO hmmio;
		MMCKINFO mmckinfoData;
		MMCKINFO mmckinfoParent;
		WAVEFORMATEX *pwfx = NULL;
		HRESULT r;

		if (Sound_WaveOpenFile(fname, &hmmio, &pwfx, &mmckinfoParent)) {

			if (Sound_WaveStartDataRead(hmmio, &mmckinfoData, &mmckinfoParent)) {
				
				if (sound = List_ObtainItem(soundGlobs.list)) {

					DSBUFFERDESC dsbd;
					ULONG soundBufferSize;

					if (streamed) {

						sound->streamData = List_ObtainItem(soundGlobs.streamDataList);

						soundBufferSize = pwfx->nAvgBytesPerSec * SOUND_STREAMBUFFERTIME;
						Error_Fatal(mmckinfoData.cksize <= soundBufferSize, Error_Format("Sound is shorter than SOUND_STREAMBUFFERTIME (%d seconds). No need to stream", SOUND_STREAMBUFFERTIME));

						sound->flags |= SOUND_FLAG_LOOPING;
						if (streamedLoop) sound->flags |= SOUND_FLAG_STREAMEDLOOP;

						sound->streamData->hmmio = hmmio;
						sound->streamData->mmckinfoData = mmckinfoData;
						sound->streamData->mmckinfoParent = mmckinfoParent;

					} else soundBufferSize = mmckinfoData.cksize;

					DirectX_InitStruct(&dsbd);

					dsbd.dwFlags = (DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_STATIC);
					if (enable3D) dsbd.dwFlags |= (DSBCAPS_CTRL3D | DSBCAPS_MUTE3DATMAXDISTANCE);
					dsbd.dwBufferBytes = soundBufferSize;
					dsbd.lpwfxFormat = pwfx;

					if (SUCCEEDED(r = soundGlobs.directSound->lpVtbl->CreateSoundBuffer(soundGlobs.directSound, &dsbd, &sound->buffer, NULL))) {

						if (streamed || Sound_FillBuffer(sound, hmmio, &mmckinfoData, &mmckinfoParent)) {

							if (enable3D) Sound_Enable3D(sound);

							sound->flags |= SOUND_FLAG_ORIGINAL;

							if (useShared) File_RegisterSharedObject(soundGlobs.sharedObjectList, fname, sound);

#ifdef _DEBUG
							sprintf(sound->fname, "%s", fname);
							sound->file = file;
							sound->line = line;
#endif // _DEBUG

							Mem_Free(pwfx);
							pwfx = NULL;

							return sound;

						}

					} else Error_DirectX(r, "CreateSoundBuffer");

					List_ReturnItem(soundGlobs.list, sound);
					sound = NULL;

				}
			}

			Mem_Free(pwfx);
			pwfx = NULL;
		}
	}
	
	return NULL;
}

VOID Sound_SetUserData(lpSound sound, LPVOID data) {

	Error_Fatal(NULL == sound, "NULL passed as sound to Sound_SetUserData()");
	List_CheckItem(soundGlobs.list, sound);

	sound->userData = data;
}

LPVOID Sound_GetUserData(lpSound sound) {

	Error_Fatal(NULL == sound, "NULL passed as sound to Sound_GetUserData()");
	List_CheckItem(soundGlobs.list, sound);

	return sound->userData;
}

SLONG Sound_GetTime(lpSound sound) {

	ULONG position;
	HRESULT r;

	Error_Fatal(NULL == sound, "NULL passed as sound to Sound_GetTime()");
	List_CheckItem(soundGlobs.list, sound);

	if (soundGlobs.directSound) {

		if (SUCCEEDED(r = sound->buffer->lpVtbl->GetCurrentPosition(sound->buffer, &position, NULL))) {
			return position;
		} else Error_DirectX(r, "GetCurrentPosition");
	}

	return -1;
}

VOID Sound_Pause(lpSound sound, BOOL pause) {

	if (soundGlobs.directSound) {

		HRESULT r;

		Error_Fatal(NULL == sound, "NULL passed as sound to Sound_Pause()");
		List_CheckItem(soundGlobs.list, sound);

		if (pause) {

			if (SUCCEEDED(r = sound->buffer->lpVtbl->Stop(sound->buffer))) {

				sound->flags |= SOUND_FLAG_PAUSED;

			} else Error_DirectX(r, "Stop");

		} else {

			if (sound->flags & SOUND_FLAG_PAUSED) {

				BOOL looping = (SOUND_FLAG_LOOPING == (sound->flags & SOUND_FLAG_LOOPING));

				if (SUCCEEDED(r = sound->buffer->lpVtbl->Play(sound->buffer, 0, 0, looping?DSBPLAY_LOOPING:0))) {

					sound->flags &= ~SOUND_FLAG_PAUSED;

				} else Error_DirectX(r, "Play");
			}
		}
	}
}

static BOOL Sound_StopAllCallback(lpSound sound, lpStandardCallback callback) {

	if (!(sound->flags & SOUND_FLAG_ORIGINAL)) {

		if (callback->function) callback->function(sound, callback->data);

		if (!(sound->flags & SOUND_FLAG_PAUSED)) {
			Sound_Remove(sound);
		}
	}

	return FALSE;
}

VOID Sound_StopAll(VOID (*callback)(lpSound sound, LPVOID data), LPVOID data) {

	if (soundGlobs.directSound) {

		struct StandardCallback callbackData;

		callbackData.function = callback;
		callbackData.data = data;

		List_RunThrough(soundGlobs.list, Sound_StopAllCallback, &callbackData);

	}
}

static BOOL Sound_RunThroughOriginalsCallback(lpSound sound, lpStandardCallback callback) {

	if (sound->flags & SOUND_FLAG_ORIGINAL) {
		if (callback->function) callback->function(sound, callback->data);
	}

	return FALSE;
}

static BOOL Sound_RunThroughDuplicatesCallback(lpSound sound, lpStandardCallback callback) {

	if (!(sound->flags & SOUND_FLAG_ORIGINAL)) {
		if (callback->function) callback->function(sound, callback->data);
	}

	return FALSE;
}

VOID Sound_RunThroughList(BOOL originals, BOOL (*callback)(lpSound sound, LPVOID data), LPVOID data) {

	if (soundGlobs.directSound) {

		struct StandardCallback callbackData;

		callbackData.function = callback;
		callbackData.data = data;

		if (originals) List_RunThrough(soundGlobs.list, Sound_RunThroughOriginalsCallback, &callbackData);
		else List_RunThrough(soundGlobs.list, Sound_RunThroughDuplicatesCallback, &callbackData);
	}
}

VOID Sound_Remove(lpSound sound) {

	if (soundGlobs.directSound) {

		Error_Fatal(NULL == sound, "NULL passed as sound to Sound_Remove()");
		List_CheckItem(soundGlobs.list, sound);

		if (sound->streamData && sound->streamData->threadHandle) {

			HANDLE handle = sound->streamData->threadHandle;

			sound->streamData->threadHandle = NULL;

			// As soon as this sound's update thread detects that its handle has been set to NULL
			// it will remove the sound and terminate itself, so wait until this happens...
			ResumeThread(handle);
			WaitForSingleObject(handle, INFINITE);

		} else {

			ULONG count;
			BOOL release;

			Error_Fatal(NULL == sound, "NULL passed as sound to Sound_Remove()");
			List_CheckItem(soundGlobs.list, sound);

			if (sound->flags & SOUND_FLAG_ORIGINAL) {

				if (File_ReleaseSharedObject(soundGlobs.sharedObjectList, sound)) release = TRUE;
				else release = FALSE;

			} else {

				if (sound->removeListPrev) sound->removeListPrev->removeListNext = sound->removeListNext;
				else soundGlobs.removeList = sound->removeListNext;
				if (sound->removeListNext) sound->removeListNext->removeListPrev = sound->removeListPrev;

				release = TRUE;
			}

			if (release) {

				if (sound->streamData) List_ReturnItem(soundGlobs.streamDataList, sound->streamData);

				if (sound->buffer3D) count = sound->buffer3D->lpVtbl->Release(sound->buffer3D);
				count = sound->buffer->lpVtbl->Release(sound->buffer);
				List_ReturnItem(soundGlobs.list, sound);
			}
		}
	}
}

// Block the sound from being played for the specified time
VOID Sound_Block(lpSound sound, REAL timeout) {

	Error_Fatal(NULL == sound, "NULL passed as sound to Sound_Block()");
	List_CheckItem(soundGlobs.list, sound);

	sound->blockTimeout = timeout;
}

ULONG WINAPI Sound_FillBuffer_ThreadProc(lpSound sound) {

	Error_Fatal(NULL == sound, "NULL passed as sound to Sound_FillBuffer_ThreadProc()");
	List_CheckItem(soundGlobs.list, sound);

	while (sound->streamData->threadHandle) {

		Sound_FillBuffer(sound, sound->streamData->hmmio, &sound->streamData->mmckinfoData, &sound->streamData->mmckinfoParent);

		// The sound may have been removed during Sound_FillBuffer()
		if (sound->streamData->threadHandle) SuspendThread(sound->streamData->threadHandle);
	}

	Sound_Remove(sound);

	return 0;
}

VOID Sound_FillBuffer_Thread(lpSound sound) {

	Error_Fatal(NULL == sound, "NULL passed as sound to Sound_FillBuffer_Thread()");
	List_CheckItem(soundGlobs.list, sound);

	if (sound->streamData->threadHandle) {
		ResumeThread(sound->streamData->threadHandle);
	} else {
		sound->streamData->threadHandle = CreateThread(NULL, 0, Sound_FillBuffer_ThreadProc, sound, 0, &sound->streamData->threadID);
	}
}

static VOID Sound_UpdateStream(lpSound sound, LPREAL delta) {

	ULONG currPos, writePos;
	ULONG status;
	HRESULT r;

	Error_Fatal(NULL == sound, "NULL passed as sound to Sound_UpdateStream()");
	List_CheckItem(soundGlobs.list, sound);

	if (SUCCEEDED(r = sound->buffer->lpVtbl->GetStatus(sound->buffer, &status))) {

		if (status & DSBSTATUS_PLAYING) {

			if (SUCCEEDED(r = sound->buffer->lpVtbl->GetCurrentPosition(sound->buffer, &currPos, &writePos))) {

				if (sound->flags & SOUND_FLAG_BUFFERFULL) {

					if ((sound->streamData->lastPos > currPos || sound->streamData->lastPos < sound->streamData->bufferEnd) &&
						currPos >= sound->streamData->bufferEnd) {

						r = sound->buffer->lpVtbl->Stop(sound->buffer);
						Error_DirectX(r, "Stop");

						if (soundGlobs.finishedCallback) {
							if (soundGlobs.finishedCallback(sound, soundGlobs.finishedCallbackData)) {
								Sound_Remove(sound);
							}
						}
					}

				} else {

					DSBCAPS caps;

					DirectX_InitStruct(&caps);

					if (SUCCEEDED(r = sound->buffer->lpVtbl->GetCaps(sound->buffer, &caps))) {

						ULONG half = caps.dwBufferBytes / 2;

						if (((sound->flags & SOUND_FLAG_SECONDHALF) && currPos < half && writePos < half) ||
							(!(sound->flags & SOUND_FLAG_SECONDHALF) && currPos > half && writePos > half)) { 
							
#ifdef SOUND_NOTHREADS
							Sound_FillBuffer(sound, sound->streamData->hmmio, &sound->streamData->mmckinfoData, &sound->streamData->mmckinfoParent);
#else // SOUND_NOTHREADS
							Sound_FillBuffer_Thread(sound);
#endif // SOUND_NOTHREADS

						}

					} else Error_DirectX(r, "GetCaps");
				}

				sound->streamData->lastPos = currPos;

			} else Error_DirectX(r, "GetCurrentPosition");
		} else Error_DirectX(r, "GetStatus");
	}
}

static BOOL Sound_UpdateAllCallback(lpSound sound, LPREAL delta) {

	if (sound->blockTimeout > 0.0f) sound->blockTimeout -= *delta;
	else sound->blockTimeout = 0.0f;

	if (sound->flags & SOUND_FLAG_PLAYNEXTUPDATE) {
		if (Sound_Start(sound)) {
			sound->flags &= ~SOUND_FLAG_PLAYNEXTUPDATE;
		}
	}

	if (sound->streamData) Sound_UpdateStream(sound, delta);

	return Sound_UpdatePositionCallback(sound, delta);
}

VOID Sound_SetGlobalVolume(REAL volume) {

	soundGlobs.globalVolume = volume;

	if (soundGlobs.directSound) {

		soundGlobs.primaryBuffer->lpVtbl->SetVolume(soundGlobs.primaryBuffer, Sound_GetDirectSoundVolume(-1.0f + volume));

	}
}

REAL Sound_GetGlobalVolume(VOID) {

	return soundGlobs.globalVolume;
}

// If 'finishedCallback' is specified as NULL, then the default action will be taken when the sample
// reached the end of the buffer/stream. Non-streamed sounds are removed, streamed sounds are not removed.
// If 'finishedCallback' points to a function, then the return value of this function determines whether
// or not the sound is removed, regardless of type.
// The callback is never called for looping sounds/streams.
VOID Sound_SetFinishedCallback(BOOL (*finishedCallback)(lpSound sound, LPVOID data), LPVOID data) {

	soundGlobs.finishedCallback = finishedCallback;
	soundGlobs.finishedCallbackData = data;
}

ULONG Sound_Update(REAL delta) {

	if (soundGlobs.directSound) {

		lpSound sound, next, prev = NULL;
		ULONG status, count = 0;
		HRESULT r;

		for (sound=soundGlobs.removeList ; sound ; sound=next) {

			next = sound->removeListNext;

			if (SUCCEEDED(r = sound->buffer->lpVtbl->GetStatus(sound->buffer, &status))) {

				if ((status & DSBSTATUS_PLAYING) || (sound->flags & SOUND_FLAG_PAUSED)) count++;
				else {
					if (NULL == soundGlobs.finishedCallback || soundGlobs.finishedCallback(sound, soundGlobs.finishedCallbackData)) {

						Sound_Remove(sound);
					}
				}
			} else Error_DirectX(r, "GetStatus");

			prev = sound;
		}

		List_RunThrough(soundGlobs.list, Sound_UpdateAllCallback, &delta);
		Sound_UpdateListener(delta);

		return count;

	}
	
	return 0;
}

static BOOL Sound_Start(lpSound sound) {

	if (soundGlobs.directSound) {

		HRESULT r;
		BOOL looping = (SOUND_FLAG_LOOPING == (sound->flags & SOUND_FLAG_LOOPING));

		Error_Fatal(NULL == sound, "NULL passed as sound to Sound_Start()");
		List_CheckItem(soundGlobs.list, sound);

		if (sound->streamData) {

			if (Sound_WaveStartDataRead(sound->streamData->hmmio, &sound->streamData->mmckinfoData, &sound->streamData->mmckinfoParent)) {

				sound->flags |= SOUND_FLAG_STREAMSTARTED;
				sound->flags &= ~SOUND_FLAG_SECONDHALF;
				sound->flags &= ~SOUND_FLAG_BUFFERFULL;

				Sound_FillBuffer(sound, sound->streamData->hmmio, &sound->streamData->mmckinfoData, &sound->streamData->mmckinfoParent);

			} else return FALSE;
		}

		if (SUCCEEDED(r = sound->buffer->lpVtbl->Play(sound->buffer, 0, 0, looping?DSBPLAY_LOOPING:0))) {

			if (NULL == sound->streamData) {

				if (soundGlobs.removeList) soundGlobs.removeList->removeListPrev = sound;
				sound->removeListNext = soundGlobs.removeList;
				soundGlobs.removeList = sound;

			}

			return TRUE;

		} else Error_DirectX(r, "Play");
	}

	return FALSE;
}

VOID Sound_PlayStream(lpSound streamedSound, BOOL nextUpdate) {

	if (soundGlobs.directSound) {

		Error_Fatal(NULL == streamedSound, "NULL passed as sound to Sound_PlayStream()");
		List_CheckItem(soundGlobs.list, streamedSound);
		Error_Fatal(NULL == streamedSound->streamData, "Sound is not a stream, use Sound_Play()");
		Error_Fatal((streamedSound->flags & SOUND_FLAG_STREAMSTARTED), "Sound is already playing");

		if (nextUpdate) streamedSound->flags |= SOUND_FLAG_PLAYNEXTUPDATE;
		else {
			if (!Sound_Start(streamedSound)) {
				streamedSound->flags |= SOUND_FLAG_PLAYNEXTUPDATE;
			}
		}
	}
}

lpSound Sound_Play(lpSound original, BOOL looping, BOOL nextUpdate) {

	if (soundGlobs.directSound && 0.0f == original->blockTimeout) {

		HRESULT r;
		lpSound sound;

		Error_Fatal(NULL != original->streamData, "Sound is a stream, use Sound_PlayStream()");
		Error_Fatal(NULL == original, "NULL passed as sound to Sound_Play()");
		List_CheckItem(soundGlobs.list, original);
		Error_Fatal(!(original->flags & SOUND_FLAG_ORIGINAL), "'original' is not a loaded sound");

		if (sound = List_ObtainItem(soundGlobs.list)) {
			if (SUCCEEDED(r = soundGlobs.directSound->lpVtbl->DuplicateSoundBuffer(soundGlobs.directSound, original->buffer, &sound->buffer))) {

				if (original->flags & SOUND_FLAG_3DENABLED) {

					if (SUCCEEDED(r = sound->buffer->lpVtbl->QueryInterface(sound->buffer, &IID_IDirectSound3DBuffer, &sound->buffer3D))) {

						sound->params = original->params;
						sound->flags |= SOUND_FLAG_3DENABLED;
					}
				}

/*				{
					SLONG volume;

					if (SUCCEEDED(r = original->buffer->lpVtbl->GetVolume(original->buffer, &volume))) {
						r = sound->buffer->lpVtbl->SetVolume(sound->buffer, volume);
						Error_DirectX(r, "SetVolume");
					} else Error_DirectX(r, "GetVolume");

				}
*/
				if (looping) sound->flags |= SOUND_FLAG_LOOPING;
				if (nextUpdate) sound->flags |= SOUND_FLAG_PLAYNEXTUPDATE;
				else {
					if (!Sound_Start(sound)) {
						sound->flags |= SOUND_FLAG_PLAYNEXTUPDATE;
					}
				}

#ifdef _DEBUG
				sprintf(sound->fname, "%s", original->fname);
				sound->file = original->file;
				sound->line = original->line;
#endif // _DEBUG

				return sound;

			} else Error_DirectX(r, "DuplicateSoundBuffer");

			List_ReturnItem(soundGlobs.list, sound);
		}
	}

	return NULL;
}

__inline VOID Sound_SetVolume(lpSound sound, REAL volume) {

	if (soundGlobs.directSound) {

		Error_Fatal(NULL == sound, "NULL passed as sound to Sound_SetVolume()");
		List_CheckItem(soundGlobs.list, sound);

		sound->buffer->lpVtbl->SetVolume(sound->buffer, Sound_GetDirectSoundVolume(-1.0f + volume));
	}
}

__inline VOID Sound_SetPan(lpSound sound, REAL pan) {

	if (soundGlobs.directSound) {

		Error_Fatal(NULL == sound, "NULL passed as sound to Sound_SetPan()");
		List_CheckItem(soundGlobs.list, sound);

		sound->buffer->lpVtbl->SetPan(sound->buffer, Sound_GetDirectSoundVolume(pan));
	}
}

__inline VOID Sound_SetFrequency(lpSound sound, SLONG frequency) {

	if (soundGlobs.directSound) {

		Error_Fatal(NULL == sound, "NULL passed as sound to Sound_SetFrequency()");
		List_CheckItem(soundGlobs.list, sound);

		sound->buffer->lpVtbl->SetFrequency(sound->buffer, frequency);
	}
}

__inline REAL Sound_GetVolume(lpSound sound) {
	
	if (soundGlobs.directSound) {

		SLONG volume = 0;

		Error_Fatal(NULL == sound, "NULL passed as sound to Sound_GetVolume()");
		List_CheckItem(soundGlobs.list, sound);

		sound->buffer->lpVtbl->GetVolume(sound->buffer, &volume);

		return Sound_GetRealVolume(volume) + 1.0f;
	}

	return 0;
}

__inline REAL Sound_GetPan(lpSound sound) {

	SLONG pan = 0;

	if (soundGlobs.directSound) {
	
		Error_Fatal(NULL == sound, "NULL passed as sound to Sound_GetPan()");
		List_CheckItem(soundGlobs.list, sound);

		sound->buffer->lpVtbl->GetPan(sound->buffer, &pan);

		return Sound_GetRealVolume(pan);
	}

	return 0;
}

__inline SLONG Sound_GetFrequency(lpSound sound) {

	SLONG frequency = 0;

	if (soundGlobs.directSound) {

		Error_Fatal(NULL == sound, "NULL passed as sound to Sound_GetFrequency()");
		List_CheckItem(soundGlobs.list, sound);

		sound->buffer->lpVtbl->GetFrequency(sound->buffer, &frequency);
	}
	
	return frequency;
}

/*****************************************************************************************
 ***** 3D Stuff
 *****************************************************************************************/

static VOID Sound_UpdateListener(REAL delta) {

	if (soundGlobs.listenerFrame) {

		VECTOR3D pos, dir, up;

		Frame_GetWorldPosition(soundGlobs.listenerFrame, &pos);
		Frame_GetWorldOrientation(soundGlobs.listenerFrame, &dir, &up);

		if (soundGlobs.flags & SOUNDGLOBS_FLAG_NEWLISTENER) {

			VECTOR3D zero = { 0.0f, 0.0f, 0.0f };

			Maths_SetD3DVECTOR(&soundGlobs.listenerParams.vVelocity, &zero);
			soundGlobs.flags &= ~SOUNDGLOBS_FLAG_NEWLISTENER;

		} else {

			VECTOR3D oldPos, velocity;

			Maths_GetD3DVECTOR(&oldPos, &soundGlobs.listenerParams.vPosition);
			Maths_Vector3DSubtract(&velocity, &pos, &oldPos);
			Maths_Vector3DScale(&velocity, &velocity, 1.0f / (delta / STANDARD_FRAMERATE));
			Maths_SetD3DVECTOR(&soundGlobs.listenerParams.vVelocity, &velocity);
		}

		Maths_SetD3DVECTOR(&soundGlobs.listenerParams.vPosition, &pos);
		Maths_SetD3DVECTOR(&soundGlobs.listenerParams.vOrientFront, &dir);
		Maths_SetD3DVECTOR(&soundGlobs.listenerParams.vOrientTop, &up);

		soundGlobs.listener->lpVtbl->SetAllParameters(soundGlobs.listener, &soundGlobs.listenerParams, DS3D_DEFERRED);
		soundGlobs.listener->lpVtbl->CommitDeferredSettings(soundGlobs.listener);
	}
}

VOID Sound_SetListenerDistanceFactor(REAL factor) {

	if (soundGlobs.directSound) {

		soundGlobs.listenerParams.flDistanceFactor = factor;

	}
}

VOID Sound_SetListenerDopplerFactor(REAL factor) {

	if (soundGlobs.directSound) {

		soundGlobs.listenerParams.flDopplerFactor = factor;

	}
}

VOID Sound_SetListenerRolloffFactor(REAL factor) {

	if (soundGlobs.directSound) {

		soundGlobs.listenerParams.flRolloffFactor = factor;
	}
}

VOID Sound_SetListenerFrame(lpFrame frame) {

	if (soundGlobs.directSound) {
		if (soundGlobs.listenerFrame != frame) {
			soundGlobs.flags |= SOUNDGLOBS_FLAG_NEWLISTENER;
			soundGlobs.listenerFrame = frame;
		}
	}
}

static BOOL Sound_UpdatePositionCallback(lpSound sound, LPREAL delta) {

	if (sound->flags & SOUND_FLAG_3DENABLED) {

		if (sound->frame) {

			VECTOR3D pos, dir, up;

			Frame_GetWorldPosition(sound->frame, &pos);
			Frame_GetWorldOrientation(sound->frame, &dir, &up);

			{
				REAL dist;
				VECTOR3D listenerPos;

				Maths_GetD3DVECTOR(&listenerPos, &soundGlobs.listenerParams.vPosition);
				dist = Maths_Vector3DDistance(&listenerPos, &pos);
			}


			if (sound->flags & SOUND_FLAG_NEWFRAME) {

				VECTOR3D zero = { 0.0f, 0.0f, 0.0f };

				Maths_SetD3DVECTOR(&sound->params.vVelocity, &zero);
				sound->flags &= ~SOUND_FLAG_NEWFRAME;

			} else {

				VECTOR3D oldPos, velocity;

				Maths_GetD3DVECTOR(&oldPos, &sound->params.vPosition);
				Maths_Vector3DSubtract(&velocity, &pos, &oldPos);
				Maths_Vector3DScale(&velocity, &velocity, 1.0f / ((*delta) / STANDARD_FRAMERATE));
				Maths_SetD3DVECTOR(&sound->params.vVelocity, &velocity);
			}

			Maths_SetD3DVECTOR(&sound->params.vPosition, &pos);
			Maths_SetD3DVECTOR(&sound->params.vConeOrientation, &dir);

			sound->params.dwMode = DS3DMODE_NORMAL;

		} else sound->params.dwMode = DS3DMODE_DISABLE;

		sound->buffer3D->lpVtbl->SetAllParameters(sound->buffer3D, &sound->params, DS3D_DEFERRED);
	}

	return FALSE;
}

VOID Sound_SetDistances(lpSound sound, REAL minDistance, REAL maxDistance) {

	if (soundGlobs.directSound) {

		Error_Fatal(NULL == sound, "NULL passed as sound to Sound_SetDistances()");
		List_CheckItem(soundGlobs.list, sound);

		sound->params.flMinDistance = minDistance;
		sound->params.flMaxDistance = maxDistance;
	}
}

VOID Sound_SetFrame(lpSound sound, lpFrame frame) {

	if (soundGlobs.directSound) {

		Error_Fatal(NULL == sound, "NULL passed as sound to Sound_SetFrame()");
		List_CheckItem(soundGlobs.list, sound);
		Error_Fatal(NULL == sound->buffer3D, "Cannot set the frame on a non-3d sound");

		if (sound->frame != frame) {
			sound->flags |= SOUND_FLAG_NEWFRAME;
			sound->frame = frame;
		}
	}
}

/**************************************************************************************
 ***** WAV file loading functions...
 **************************************************************************************/

static BOOL Sound_ReadMMIO(HMMIO hmmioIn, WAVEFORMATEX **ppwfxInfo, MMCKINFO *pckInRIFF) {

	MMCKINFO ckIn;
	PCMWAVEFORMAT pcmWaveFormat;

	(*ppwfxInfo) = NULL;

	if (0 == mmioDescend(hmmioIn, pckInRIFF, NULL, 0)) {
		if ((pckInRIFF->ckid == FOURCC_RIFF) && (pckInRIFF->fccType == mmioFOURCC('W', 'A', 'V', 'E'))) {

			ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
			
			if (0 == mmioDescend(hmmioIn, &ckIn, pckInRIFF, MMIO_FINDCHUNK)) {
				if (ckIn.cksize >= sizeof(PCMWAVEFORMAT)) {
					if (sizeof(pcmWaveFormat) == mmioRead(hmmioIn, (LPUCHAR) &pcmWaveFormat, sizeof(pcmWaveFormat))) {
	
						if (WAVE_FORMAT_PCM  == pcmWaveFormat.wf.wFormatTag) {

							(*ppwfxInfo) = Mem_Alloc(sizeof(WAVEFORMATEX));
		
							memcpy((*ppwfxInfo), &pcmWaveFormat, sizeof(*(*ppwfxInfo)));
							(*ppwfxInfo)->cbSize = 0;

						} else {

							SWORD cbExtraBytes = 0;

							if (sizeof(SWORD) == mmioRead(hmmioIn, (LPUCHAR) &cbExtraBytes, sizeof(SWORD))) {
		
								(*ppwfxInfo) = Mem_Alloc(sizeof(WAVEFORMATEX) + cbExtraBytes);
								memcpy((*ppwfxInfo), &pcmWaveFormat, sizeof(pcmWaveFormat));
								(*ppwfxInfo)->cbSize = cbExtraBytes;
		
								if (cbExtraBytes == mmioRead(hmmioIn, &((LPUCHAR) &((*ppwfxInfo)->cbSize))[sizeof(WORD)], cbExtraBytes)) {
									Mem_Free((*ppwfxInfo));
									return FALSE;
								}
							}
						}

						if (0 != mmioAscend(hmmioIn, &ckIn, 0)) {

							Mem_Free((*ppwfxInfo));
							(*ppwfxInfo) = NULL;
							return FALSE;
						}

						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}

static LRESULT CALLBACK Sound_MMIOProc(LPSTR lpmmioinfo, UINT uMsg, LPARAM lParam1, LPARAM lParam2) {

	LPMMIOINFO info = (LPMMIOINFO) lpmmioinfo;

	switch (uMsg) {
	case MMIOM_OPEN:
		{
			LPUCHAR fname = (LPUCHAR) lParam1;
			lpFile fp;

			if (fp = File_Open(fname, "rb")) {

				info->adwInfo[0] = (ULONG) fp;

				return MMSYSERR_NOERROR;

			}
			
			return -1;
		}
	case MMIOM_CLOSE:
		{
			lpFile fp = (lpFile) info->adwInfo[0];

			Error_Fatal(NULL == fp, "No file pointer");
			File_Close(fp);
			info->adwInfo[0] = 0;

			return 0;
		}
	case MMIOM_READ:
		{
			LPVOID buffer = (LPVOID) lParam1;
			ULONG readSize, size = (ULONG) lParam2;
			lpFile fp = (lpFile) info->adwInfo[0];

			Error_Fatal(NULL == fp, "No file pointer");
			Error_Fatal(NULL == buffer, "No buffer");

			readSize = File_Read(buffer, 1, size, fp);
			info->lDiskOffset += readSize;

			return readSize;
		}
	case MMIOM_WRITE:

		Error_Fatal(TRUE, "Cannot write to file");
		
		break;

	case MMIOM_SEEK:
		{
			SLONG position = (SLONG) lParam1;
			SLONG flags = (SLONG) lParam2;
			lpFile fp = (lpFile) info->adwInfo[0];

			Error_Fatal(NULL == fp, "No file pointer");
			if (0 == File_Seek(fp, position, flags)) {
				return (info->lDiskOffset = File_Tell(fp));
			}

			return -1;
		}
	}

	return 0;
}

static BOOL Sound_WaveOpenFile(LPUCHAR fname, HMMIO *hmmioIn, WAVEFORMATEX **ppwfxInfo, MMCKINFO *pckInRIFF) {

	MMIOINFO info = { 0 };

	info.pIOProc = Sound_MMIOProc;

	if ((*hmmioIn) = mmioOpen(fname, &info, MMIO_READ|MMIO_ALLOCBUF)) {

		if (Sound_ReadMMIO((*hmmioIn), ppwfxInfo, pckInRIFF)) {

			return TRUE;

		}
		mmioClose((*hmmioIn), 0);
	}

	return FALSE;
}

static BOOL Sound_WaveStartDataRead(HMMIO phmmioIn, MMCKINFO* pckIn, MMCKINFO* pckInRIFF) {

	if (-1 != mmioSeek(phmmioIn, pckInRIFF->dwDataOffset + sizeof(FOURCC), SEEK_SET)) {

		pckIn->ckid = mmioFOURCC('d', 'a', 't', 'a');

		if (0 == mmioDescend(phmmioIn, pckIn, pckInRIFF, MMIO_FINDCHUNK)) {

			return TRUE;

		}
	}

	return FALSE;
}

static BOOL Sound_WaveReadFile(HMMIO hmmioIn, UINT cbRead, LPUCHAR pbDest, MMCKINFO *pckIn, LPULONG cbActualRead) {

	MMIOINFO mmioinfoIn;
	ULONG loop;
	
	*cbActualRead = 0;
	
	if (0 == mmioGetInfo(hmmioIn, &mmioinfoIn, 0)) {
	
		UINT cbDataIn = cbRead;
	
		cbDataIn = min(cbDataIn, pckIn->cksize);

		pckIn->cksize -= cbDataIn;
	
		for (loop=0 ; loop<cbDataIn ; loop++) {

			if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead) {

				if (0 != mmioAdvance(hmmioIn, &mmioinfoIn, MMIO_READ)) break;
				if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead) break;

			}

			((LPUCHAR) pbDest)[loop] = *((LPUCHAR) mmioinfoIn.pchNext);
			mmioinfoIn.pchNext++;
		}

		if (loop == cbDataIn) {
			if (0 == mmioSetInfo(hmmioIn, &mmioinfoIn, 0)) {

				*cbActualRead = cbDataIn;
				return TRUE;
		
			}
		}
	}

	return FALSE;
}
