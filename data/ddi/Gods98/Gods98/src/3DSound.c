
#include <d3drm.h>
#include <dsound.h>
#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>


#include "..\inc\Standard.h"
#include "..\inc\Sound.h"
#include "..\inc\Errors.h"
#include "..\inc\Memory.h"
#include "..\inc\Containers.h"
#include "..\inc\3DSound.h"
#include "..\inc\Files.h"

/*
VOID Sound3D_Update(VOID) {

}

VOID Sound3D_SetMaxDist(REAL dist) {

}

VOID Sound3D_StopSound(ULONG id) {

}

BOOL Sound3D_Initialise(HWND hWnd) {

	return TRUE;
}

BOOL Sound3D_Initialised(VOID) {
	
	return FALSE;
}

REAL Sound3D_SetRollOffFactor(REAL r) {

	return 1.0f;
}

VOID Sound3D_MakeContainerListener(lpContainer cont) {

}

VOID Sound3D_SetMinDistForAtten(REAL r) {

}

VOID Sound3D_UpdateListener(VOID) {

}

VOID Sound3D_ShutDown(VOID) {

}

VOID Sound3D_StopAllSounds(VOID) {

}

VOID Sound3D_Stream_Stop(BOOL b) {

}

VOID Sound3D_SetGlobalVolumePrescaled(SLONG l) {

}

SLONG Sound3D_Load(LPUCHAR c, BOOL b1, BOOL b2, SLONG l) {

	return 0;
}

VOID Sound3D_Remove(SLONG l) {

}

SLONG Sound3D_PlayNormal(SLONG l, BOOL b) {

	return 0;
}

REAL Sound3D_GetSamplePlayTime(SLONG l) {

	return 1.0f;
}

VOID Sound3D_SetBufferVolume(signed long l1, signed long l2) {

}

signed long Sound3D_GetBufferVolume(signed long l1) {

	return 1;
}

signed long Sound3D_PlayOnFrame(LPVOID v, signed long l, BOOL b) {

	return 0;
}

signed long Sound3D_PlayOnPos(signed long l, BOOL loop, LPVOID v) {

	return 0;
}
*/


static VOID Sound3D_RegisterUpdateFrame(LPDIRECT3DRMFRAME3 frame);
static VOID Sound3D_RemoveUpdateFrame(LPDIRECT3DRMFRAME3 frame);
static VOID Sound3D_UpdateFrames(VOID);

Sound3D_Globs sound3DGlobs = { NULL };



BOOL Sound3D_Initialise( HWND hwndParent )
{
	DSBUFFERDESC dsbd;
    SLONG ret = IDRETRY;


	sound3DGlobs.intialised = FALSE;

	sound3DGlobs.listenerFrame = NULL;

	// Try to create the Directsound objects until we either do it, are told to ignore it, or are told to abort
	while( ret == IDRETRY )
	{
		// Create the directsound object
		if( DS_OK == DirectSoundCreate(NULL, &sound3DGlobs.lpDSnd, NULL) )
		{	// Set cooperative level - NEEDS TO BE 'DSSCL_PRIORITY' OR HIGHER TO DO 'SetFormat'
			if( DS_OK == lpDSnd()->lpVtbl->SetCooperativeLevel(lpDSnd(), hwndParent, DSSCL_PRIORITY) )
			{
				// Create a primary buffer so we can query for a 3D Listener interface
				memset( &dsbd, 0, sizeof(DSBUFFERDESC) );
				dsbd.dwSize = sizeof(DSBUFFERDESC);
				dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D | DSBCAPS_CTRLVOLUME;
				if( DS_OK == lpDSnd()->lpVtbl->CreateSoundBuffer(lpDSnd(), &dsbd, &sound3DGlobs.lpDSBuff, NULL) )
				{					
					// Make the primary 44.1 KHz so that it sounds better
					WAVEFORMATEX wfx;
					wfx.wFormatTag = WAVE_FORMAT_PCM;
					wfx.nChannels = 2;
					wfx.wBitsPerSample = 16;
					wfx.nSamplesPerSec = 22050;
					wfx.nBlockAlign = wfx.wBitsPerSample / 8 * wfx.nChannels;
					wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign; 
					//wfx.nBlockAlign = 4;
					//wfx.nAvgBytesPerSec = 44100*2*2;
					wfx.cbSize = 0;
					if( DS_OK != lpDSBuff()->lpVtbl->SetFormat(lpDSBuff(), &wfx) )
						Error_Warn( TRUE, "Could not set format on primary buffer - low quality output will be used." );
					
					// Get the 3D listener information
					if( DS_OK == lpDSBuff()->lpVtbl->QueryInterface(lpDSBuff(), &IID_IDirectSound3DListener, (void**) &sound3DGlobs.lp3DListenerInfo) )
						sound3DGlobs.lp3DListenerInfo->lpVtbl->SetDopplerFactor( sound3DGlobs.lp3DListenerInfo, D3DVAL(100.0), DS3D_IMMEDIATE );
					else 
					{
						Error_Warn( TRUE, "DirectSound 3D failed to get listener info." );
						lpDSBuff()->lpVtbl->Release( lpDSBuff() );
						lpDSnd()->lpVtbl->Release( lpDSnd() );
						sound3DGlobs.lpDSnd = NULL;
					}
				}
				else
				{	
					Error_Warn( TRUE, "DirectSound 3D failed to create a primary buffer." );
					lpDSnd()->lpVtbl->Release( lpDSnd() );
					sound3DGlobs.lpDSnd = NULL;
				}
			}
			else
			{	
				Error_Warn( TRUE, "DirectSound 3D failed to set cooperative level." );
				lpDSnd()->lpVtbl->Release( lpDSnd() );
				sound3DGlobs.lpDSnd = NULL;
			}
		}

		if( !lpDSnd() )
		{	
			Error_Warn( TRUE, "DirectSound 3D could not initialize." );
//			ret = MessageBox( hwndParent, "DirectSound 3D could not initialize", "Warning", MB_APPLMODAL|MB_ICONWARNING|MB_ABORTRETRYIGNORE );
//			if (ret == IDABORT)
//				return FALSE;
			ret = IDIGNORE;
		}
		else
		{	
			ret = IDOK;

			sound3DGlobs.intialised = TRUE;
		}
	}
	
	if( Sound3D_Initialised() )
	{
		//SET THE PRIMARY BUFFER TO CONTINUOUSLY PLAY - OPTIMISATION FOR FREQUENT STARTING AND STOPPING OF PLAYBACK
		lpDSBuff()->lpVtbl->Play( lpDSBuff(), 0,0,DSBPLAY_LOOPING );

		//DEFAULT VALUES
		lp3DListenerInfo()->lpVtbl->SetRolloffFactor( lp3DListenerInfo(), 1, DS3D_DEFERRED );
		//DISABLE DOPPLER - DONT NEED TO SET VELOCITY ON SOUNDS
		lp3DListenerInfo()->lpVtbl->SetDopplerFactor( lp3DListenerInfo(), 0, DS3D_DEFERRED );
		
		if( DS_OK != lp3DListenerInfo()->lpVtbl->CommitDeferredSettings(lp3DListenerInfo()) )
			Error_Warn( TRUE, "DirectSound 3D failed commit listener info settings." );

		sound3DGlobs.minDistanceForAttentuation = 1;//DS3D_DEFAULTMINDISTANCE;
		sound3DGlobs.maxDistance = 800;//DS3D_DEFAULTMAXDISTANCE;

		lpDSBuff()->lpVtbl->GetVolume( lpDSBuff(), &sound3DGlobs.windowsVolume );

		Sound3D_SetVolumeToDefault();
	}

	return TRUE;
}


VOID Sound3D_ShutDown( VOID )
{
	if( Sound3D_Initialised() )
	{
		Sound3D_SetGlobalVolume( sound3DGlobs.windowsVolume );

		lpDSBuff()->lpVtbl->Stop( lpDSBuff() );

		lpDSBuff()->lpVtbl->Release( lpDSBuff() );
		lpDSnd()->lpVtbl->Release( lpDSnd() );
		sound3DGlobs.lpDSnd = NULL;

		sound3DGlobs.intialised = FALSE;
	}
}


BOOL Sound3D_CheckVolumeLimits( SLONG vol )
{
	if( (vol > DSBVOLUME_MAX) || (vol < DSBVOLUME_MIN) )
	{
		Error_Warn( TRUE, "Invalid volume specified." );

		return FALSE;
	}

	return TRUE;
}


static BOOL Sound3D_GetFreeSoundIndex( LPULONG soundTableIndex )
{
	ULONG loopSound;


	for( loopSound = 0; loopSound < SOUND3D_MAXSAMPLES; loopSound++ )
	{
		if( !(sound3DGlobs.soundTable[loopSound].flags & SOUND3D_FLAG_USED) )
		{
			*soundTableIndex = loopSound;

			return TRUE;
		}
	}

	Error_Fatal( TRUE, "Run out of samples - SOUND3D_MAXSAMPLES too small." );

	return FALSE;
}


SLONG Sound3D_Load( LPUCHAR fName, BOOL stream, BOOL simultaneous, SLONG volume )
{
	BOOL okay = FALSE;
	UCHAR buffer[MAX_PATH];
	FILE *file;
	ULONG freeSoundIndex;


	if (Sound3D_Initialised()) {

		if (Sound3D_GetFreeSoundIndex(&freeSoundIndex)) {

			sound3DGlobs.soundTable[freeSoundIndex].flags = 0;
			sprintf(buffer, "%s.wav", fName);

			if (stream) {

				LPUCHAR hdFileName = File_VerifyFilename(buffer);
				LPUCHAR useFile = NULL;
				UCHAR cdFileName[FILE_MAXPATH];
				FILE *mfp;

				if (mfp = fopen(hdFileName, "r")) {
					useFile = hdFileName;
					fclose(mfp);
				} else {
					if (File_GetCDFilePath(cdFileName, buffer)) {
						useFile = cdFileName;
					}
				}

				if (useFile) {

					Error_Fatal(simultaneous, "Cannot have a multi streaming sound!");

					//NEED TO FIND THE SIZE OF THE FILE FOR 'Sound3D_GetSamplePlayTime'
					if (file = fopen(useFile, "r")) {

						fseek(file, 0, SEEK_END);

						sound3DGlobs.soundTable[freeSoundIndex].size = ftell(file);
						sound3DGlobs.soundTable[freeSoundIndex].avgBytesPerSec = GetWaveAvgBytesPerSec(useFile);
						sound3DGlobs.soundTable[freeSoundIndex].flags |= SOUND3D_FLAG_STREAM;

						fclose(file);
						
						okay = TRUE;
					}
				}
			}
			else if( Sound3D_LoadSample(&sound3DGlobs.soundTable[freeSoundIndex], buffer, simultaneous) )
			{
				sound3DGlobs.soundTable[freeSoundIndex].flags &= ~SOUND3D_FLAG_STREAM;
				if( simultaneous )
					sound3DGlobs.soundTable[freeSoundIndex].flags |= SOUND3D_FLAG_MULTI;
				
				okay = TRUE;
			}
			
			if( okay )
			{
				strcpy( sound3DGlobs.soundTable[freeSoundIndex].fName, buffer );
				
				if( Sound3D_CheckVolumeLimits(volume) )
					sound3DGlobs.soundTable[freeSoundIndex].volume = volume;
				else
					sound3DGlobs.soundTable[freeSoundIndex].volume = DSBVOLUME_MAX;
				
				sound3DGlobs.soundTable[freeSoundIndex].flags |= SOUND3D_FLAG_ACTIVE;
				sound3DGlobs.soundTable[freeSoundIndex].flags |= SOUND3D_FLAG_USED;

				return freeSoundIndex;
			}
		}
		else
			Error_Warn( TRUE, "Could not get free sound." );

		Error_Warn( TRUE, Error_Format("Cannot load sound \"%s\".", fName) );
	}

	return -1;
}


BOOL Sound3D_Remove( SLONG soundTableIndex )
{
	ULONG loopBuffer;
	lpSound3D_SoundData soundData;


	if( Sound3D_Initialised() && (-1 != soundTableIndex) )
	{
		soundData = &sound3DGlobs.soundTable[soundTableIndex];

		soundData->flags &= ~SOUND3D_FLAG_USED;

		if( soundData->pwf )
		{
			GlobalFree( soundData->pwf );
			soundData->pwf = NULL;
		}

		for( loopBuffer = 0; loopBuffer < SOUND3D_MAXSIMULTANEOUS; loopBuffer++ )
		{
			if( soundData->lpDsb3D[loopBuffer] )
			{
				soundData->lpDsb3D[loopBuffer]->lpVtbl->Release( soundData->lpDsb3D[loopBuffer] );
				soundData->lpDsb3D[loopBuffer] = NULL;
			}
		}

		return TRUE;
	}

	return FALSE;
}


VOID Sound3D_MakeListener( LPDIRECT3DRMFRAME3 frame )
{
	if( Sound3D_Initialised() )
	{
		//if( sound3DGlobs.listenerFrame )
		//	sound3DGlobs.listenerFrame->lpVtbl->DeleteMoveCallback( sound3DGlobs.listenerFrame, Sound3D_ListenerCallback, NULL );
		
		//frame->lpVtbl->AddMoveCallback( frame, Sound3D_ListenerCallback, NULL, D3DRMCALLBACK_PREORDER );

		sound3DGlobs.listenerFrame = frame;
	}
}


VOID Sound3D_UpdateListener( VOID )
{
	if( Sound3D_Initialised() && sound3DGlobs.listenerFrame )
		Sound3D_ListenerCallback( sound3DGlobs.listenerFrame, NULL, 0.0f );
}


static VOID Sound3D_ListenerCallback( LPDIRECT3DRMFRAME3 obj, void* arg, D3DVALUE delta )
{	
	D3DVECTOR rlvCameraInfo, rlvCameraUp;
	LPDIRECT3DRMFRAME3 root;
	static D3DVECTOR oldPos = { 0, 0, 0 };
	static D3DVECTOR oldOrien = { 0, 0, 0 };
	static D3DVECTOR oldOrienUp = { 0, 0, 0 };
	BOOL change = FALSE;


	obj->lpVtbl->GetScene( obj, &root );
	
	obj->lpVtbl->GetPosition( obj, root, &rlvCameraInfo );
	if( !Sound3D_D3DVectorEqual(&rlvCameraInfo, &oldPos) )
	{	
		lp3DListenerInfo()->lpVtbl->SetPosition(lp3DListenerInfo(),
			rlvCameraInfo.x, rlvCameraInfo.y, rlvCameraInfo.z, DS3D_DEFERRED );

		oldPos = rlvCameraInfo;
		change = TRUE;
	}

	obj->lpVtbl->GetOrientation( obj, root, &rlvCameraInfo, &rlvCameraUp );
	if( !Sound3D_D3DVectorEqual(&rlvCameraInfo, &oldOrien) || !Sound3D_D3DVectorEqual(&rlvCameraUp, &oldOrienUp) )
	{	
		lp3DListenerInfo()->lpVtbl->SetOrientation( lp3DListenerInfo(),
			rlvCameraInfo.x, rlvCameraInfo.y, rlvCameraInfo.z,
			rlvCameraUp.x, rlvCameraUp.y, rlvCameraUp.z, DS3D_DEFERRED);

		oldOrien = rlvCameraInfo;
		oldOrienUp = rlvCameraUp;
		change = TRUE;
	}
	
	if( change )
	{
		if( DS_OK != lp3DListenerInfo()->lpVtbl->CommitDeferredSettings(lp3DListenerInfo()) )
			Error_Warn( TRUE, "DirectSound 3D failed commit listener info settings." );
	}

	root->lpVtbl->Release( root );
}

VOID Sound3D_FrameRemoveCallback(LPDIRECT3DRMOBJECT lpD3DRMobj, LPVOID lpArg) {

	LPDIRECT3DRMFRAME3 frame = lpArg;		// "LPDIRECT3DRMOBJECT" pah!
	
	Sound3D_RemoveUpdateFrame(frame);
}

__inline static VOID Sound3D_RegisterUpdateFrame(LPDIRECT3DRMFRAME3 frame) {

	ULONG loop;

	for (loop=0 ; loop<SOUND3D_MAXUPDATEFRAMES ; loop++) {
		if (NULL == sound3DGlobs.updateFrameList[loop]) {
			sound3DGlobs.updateFrameList[loop] = frame;
//			frame->lpVtbl->AddDestroyCallback(frame, Sound3D_FrameRemoveCallback, frame);
			break;
		}
	}
}

__inline static VOID Sound3D_RemoveUpdateFrame(LPDIRECT3DRMFRAME3 frame) {

	ULONG loop;

	for (loop=0 ; loop<SOUND3D_MAXUPDATEFRAMES ; loop++) {
		if (frame == sound3DGlobs.updateFrameList[loop]) {
			sound3DGlobs.updateFrameList[loop] = NULL;
		}
	}
}

__inline static VOID Sound3D_UpdateFrames(VOID) {

	ULONG loop;

	for (loop=0 ; loop<SOUND3D_MAXUPDATEFRAMES ; loop++) {
		if (sound3DGlobs.updateFrameList[loop]) {
			Sound3D_SoundCallback(sound3DGlobs.updateFrameList[loop], NULL, 0.0f);
		}
	}
}

static VOID Sound3D_SoundCallback(LPDIRECT3DRMFRAME3 tFrame, void* arg, D3DVALUE delay)
{	
	Container_AppData *data = (Container_AppData *)tFrame->lpVtbl->GetAppData(tFrame);
	D3DVECTOR rlvVisualInfo;
	LPDIRECT3DRMFRAME3 root;
	lpSound3D_SoundFrameRecord temp = data->soundList;


	tFrame->lpVtbl->GetScene(tFrame, &root);
	
	while(temp)
	{
		//GET POSITION OF THE 3D SOUND WHEN IT WAS LAST SET, THEN COMPARE IT WITH THE POSITION OF ITS FRAME
		//IF DIFFERENT, UPDATE THE SOUND POSITION
		tFrame->lpVtbl->GetPosition(tFrame, root, &rlvVisualInfo);
		if (!Sound3D_D3DVectorEqual(&rlvVisualInfo, &temp->pos)) {
			temp->sound3DBuff->lpVtbl->SetPosition( temp->sound3DBuff, rlvVisualInfo.x, rlvVisualInfo.y,rlvVisualInfo.z, DS3D_IMMEDIATE );
			temp->pos = rlvVisualInfo;
		}

		temp = temp->next;
	}

	root->lpVtbl->Release( root );
}


static VOID Sound3D_SetWorldPos( LPDIRECTSOUND3DBUFFER sound3DBuff, LPVECTOR3D wPos, LPVECTOR3D vel )
{	
	sound3DBuff->lpVtbl->SetPosition( sound3DBuff, wPos->x, wPos->y, wPos->z, DS3D_IMMEDIATE );
}


VOID Sound3D_Move( SLONG soundHandle, LPVECTOR3D wPos )
{	
	LPDIRECTSOUND3DBUFFER sound3DBuff;
	LPDIRECTSOUNDBUFFER soundBuff;
	VECTOR3D temp;


	if (soundBuff = Sound3D_GetSoundBuffer(soundHandle)) {
		soundBuff->lpVtbl->QueryInterface( soundBuff, &IID_IDirectSound3DBuffer, (void**)&sound3DBuff );
		Sound3D_SetWorldPos( sound3DBuff, wPos, &temp );
		sound3DBuff->lpVtbl->Release(sound3DBuff);
	}
}


static BOOL Sound3D_RecurseRemoveSoundRecord( LPDIRECT3DRMFRAME3 owner, LPDIRECTSOUND3DBUFFER sound3DBuff, lpSound3D_SoundRecord record )
{	
	lpSound3D_SoundRecord temp;
	

	if( NULL == record )
		return FALSE;

	if( Sound3D_RecurseRemoveSoundRecord(owner, sound3DBuff, record->next) )
	{	
		temp = record->next;
		record->next = temp->next;
		Mem_Free( temp );
	}

	//if( (owner == record->frame) && (sound3DBuff == record->sound3DBuff) )
	if( sound3DBuff == record->sound3DBuff )
		return TRUE;

	return FALSE;
}


static VOID Sound3D_RemoveSoundRecord( LPDIRECT3DRMFRAME3 frame, LPDIRECTSOUND3DBUFFER sound3DBuff )
{	
	lpSound3D_SoundRecord temp;
	

	if( Sound3D_RecurseRemoveSoundRecord(frame, sound3DBuff, sound3DGlobs.soundRecord) )
	{
		temp = sound3DGlobs.soundRecord;
		sound3DGlobs.soundRecord = sound3DGlobs.soundRecord->next;
		Mem_Free( temp );
	}
}


static VOID Sound3D_AddSoundRecord( LPDIRECT3DRMFRAME3 frame, LPDIRECTSOUNDBUFFER soundBuff, LPDIRECTSOUND3DBUFFER sound3DBuff )
{	
	lpSound3D_SoundRecord temp;


	temp = Mem_Alloc( sizeof(Sound3D_SoundRecord) );
	temp->next = sound3DGlobs.soundRecord;
	temp->frame = frame;
	temp->sound3DBuff = sound3DBuff;
	temp->soundBuff = soundBuff;
	sound3DGlobs.soundRecord = temp;
	// Set default values for this sound
//	temp->sound3DBuff->lpVtbl->SetMode(temp->sound3DBuff, DS3DMODE_HEADRELATIVE, DS3D_IMMEDIATE);
//	temp->sound3DBuff->lpVtbl->SetMinDistance(temp->sound3DBuff, 80, DS3D_IMMEDIATE);
//	temp->sound3DBuff->lpVtbl->SetMaxDistance(temp->sound3DBuff, 800, DS3D_IMMEDIATE);
//	temp->sound3DBuff->lpVtbl->SetConeAngles(temp->sound3DBuff, 360, 360, DS3D_IMMEDIATE);
}



BOOL Sound3D_CheckAlreadyExists( LPDIRECT3DRMFRAME3 frame, LPDIRECTSOUND3DBUFFER sound3DBuff )
{
	lpSound3D_SoundRecord check = sound3DGlobs.soundRecord;
	

	while( check )
	{
		if( sound3DBuff == check->sound3DBuff )
		{
			//REMOVE THE SOUND BECAUSE IT WILL BE USED ELSEWHERE
			Sound3D_RemoveSound( check->frame, check->sound3DBuff );

			return TRUE;
		}

		check = check->next;
	}

	return FALSE;
}


SLONG Sound3D_Play2( enum Sound3D_Play play, LPDIRECT3DRMFRAME3 frame, SLONG soundTableIndex, BOOL loop, LPVECTOR3D wPos )
{	
	LPDIRECTSOUNDBUFFER soundBuff;
	LPDIRECTSOUND3DBUFFER sound3DBuff;
	LPDIRECT3DRMFRAME3 root;
	VECTOR3D cPos;
	lpSound3D_SoundData sound;


	if (Sound3D_Initialised() && (-1 != soundTableIndex)) {
		
		sound = &sound3DGlobs.soundTable[soundTableIndex];

		if (sound->flags & SOUND3D_FLAG_ACTIVE) {
			// Play a streamed sound
			if (sound->flags & SOUND3D_FLAG_STREAM) {
				LPUCHAR hdFileName = File_VerifyFilename(sound->fName);
				LPUCHAR useFile = NULL;
				UCHAR cdFileName[FILE_MAXPATH];
				FILE *mfp;
				Error_Fatal(Sound3D_Play_Normal != play, "Can only play a streaming sound noramlly, not 3D.");
				if (mfp = fopen(hdFileName, "r")) {
					useFile = hdFileName;
					fclose(mfp);
				} else {
					if (File_GetCDFilePath(cdFileName, sound->fName)) {
						useFile = cdFileName;
					}
				}
				if (useFile) {
					Sound3D_Stream_Play(useFile, loop, sound->volume);
					//STREAM SOUNDS CANNOT BE PLAYED MULTI SO RETURN FIRST VOICE
					return (soundTableIndex * SOUND3D_MAXSIMULTANEOUS);
				} else return -1;
			}

			// If this is a multisound, select alternate sound buffer from list
			if( sound->flags & SOUND3D_FLAG_MULTI ) {	
				//NOTE A LOOPING/PLAYING SOUND MAY GET OVERWRITTEN IF MORE THAN 'SOUND3D_MAXSIMULTANEOUS', 'soundTableIndex' SOUNDS ARE PLAYED BEFORE THE SOUND IS STOPPED...
				if( ++sound->voice >= SOUND3D_MAXSIMULTANEOUS )
					sound->voice = 0;
				soundBuff = sound->lpDsb3D[ sound->voice ];
			}
			else
				soundBuff = sound->lpDsb3D[0];

			soundBuff->lpVtbl->QueryInterface( soundBuff, &IID_IDirectSound3DBuffer, (void**)&sound3DBuff );
			
			//DEFAULT SETTINGS
			{
				SLONG volume = sound->volume;
				if (Sound3D_Play_Normal == play) volume += -800;
				soundBuff->lpVtbl->SetVolume(soundBuff, volume);
			}

			sound3DBuff->lpVtbl->SetMinDistance( sound3DBuff, sound3DGlobs.minDistanceForAttentuation, DS3D_DEFERRED );
			sound3DBuff->lpVtbl->SetMaxDistance( sound3DBuff, sound3DGlobs.maxDistance, DS3D_DEFERRED );

			if (Sound3D_Play_OnFrame == play) {	
				sound3DBuff->lpVtbl->SetMode(sound3DBuff, DS3DMODE_NORMAL, DS3D_DEFERRED);			
				frame->lpVtbl->GetScene(frame, &root);		
				Sound3D_CheckAlreadyExists(frame, sound3DBuff );
				Sound3D_AttachSound(frame, sound3DBuff );
				Sound3D_AddSoundRecord(frame, soundBuff, sound3DBuff );
				frame->lpVtbl->GetPosition(frame, root, (LPD3DVECTOR) &cPos);
				//Sound3D_SetWorldPos(sound3DBuff, &cPos, NULL);
				sound3DBuff->lpVtbl->SetPosition(sound3DBuff, cPos.x, cPos.y, cPos.z, DS3D_DEFERRED);
				root->lpVtbl->Release(root);
			}
			else if (Sound3D_Play_OnPos == play) {	
				sound3DBuff->lpVtbl->SetMode( sound3DBuff, DS3DMODE_NORMAL, DS3D_DEFERRED);
				Sound3D_SetWorldPos( sound3DBuff, wPos, NULL );
				Sound3D_CheckAlreadyExists( NULL, sound3DBuff );
				Sound3D_AddSoundRecord( NULL, soundBuff, sound3DBuff );
			}
			else if (Sound3D_Play_Normal == play) {	
				sound3DBuff->lpVtbl->SetMode( sound3DBuff, DS3DMODE_DISABLE, DS3D_DEFERRED);

				Sound3D_CheckAlreadyExists( NULL, sound3DBuff );

				Sound3D_AddSoundRecord( NULL, soundBuff, sound3DBuff );
			}

			if( DS_OK != lp3DListenerInfo()->lpVtbl->CommitDeferredSettings(lp3DListenerInfo()) )
				Error_Warn( TRUE, "DirectSound 3D failed commit listener info settings." );

			soundBuff->lpVtbl->SetCurrentPosition(soundBuff, 0);
			if (loop)
				soundBuff->lpVtbl->Play(soundBuff, 0, 0, DSBPLAY_LOOPING);
			else
				soundBuff->lpVtbl->Play(soundBuff, 0, 0, 0);

			//RETURN THE INDEX OF THE BUFFER IN THE ARRAY OF DUPLICATED BUFFERS OF SOUND TYPE 'soundTableIndex'
			//JUST RETURN THE FIRST BUFFER INDEX IF THE SAMPLE IS NOT MULTI - DUPLICATES DONT EXIST
			return ((soundTableIndex*SOUND3D_MAXSIMULTANEOUS) + sound->voice);
		}
	}

	return -1;
}



VOID Sound3D_SetBufferVolume(SLONG handle, SLONG newvolume) {
	LPDIRECTSOUNDBUFFER soundBuff;
	lpSound3D_SoundData sound;
	sound = &sound3DGlobs.soundTable[handle];
	sound->volume=Sound3D_CheckVolumeLimits(newvolume)?newvolume:0;
	// Now set the volume to the buffer
	if (sound->flags & SOUND3D_FLAG_MULTI) {
		ULONG i;
		for (i=0; i<SOUND3D_MAXSIMULTANEOUS; i++) {
			if (soundBuff=sound->lpDsb3D[i]) {
				soundBuff->lpVtbl->SetVolume(soundBuff, sound->volume);
			}
		}
	} else if (soundBuff=sound->lpDsb3D[0]) {
		soundBuff->lpVtbl->SetVolume(soundBuff, sound->volume);
	}
}

SLONG Sound3D_GetBufferVolume(SLONG handle) {
	lpSound3D_SoundData sound;
	sound = &sound3DGlobs.soundTable[handle];
	return sound->volume;
}


static LPDIRECTSOUNDBUFFER Sound3D_GetSoundBuffer( SLONG soundHandle )
{	
	ULONG remainder;


	if( -1 == soundHandle )
		return NULL;

	remainder = soundHandle % SOUND3D_MAXSIMULTANEOUS;

	return sound3DGlobs.soundTable[ (soundHandle - remainder) / SOUND3D_MAXSIMULTANEOUS ].lpDsb3D[ remainder ];
}


VOID Sound3D_StopSound( SLONG soundHandle )
{	
	LPDIRECTSOUNDBUFFER soundBuff = Sound3D_GetSoundBuffer( soundHandle );
	

	if( Sound3D_Initialised() && (-1 != soundHandle) )
	{
		if( soundBuff )
			soundBuff->lpVtbl->Stop( soundBuff );
	}
}


VOID Sound3D_StopAllSounds(VOID) {	

	lpSound3D_SoundRecord temp = sound3DGlobs.soundRecord;

	while (temp) {
		temp->soundBuff->lpVtbl->Stop(temp->soundBuff);
		temp = temp->next;
	}

	Sound3D_Stream_Stop(FALSE);
	Sound3D_Stream_Stop(TRUE);
}


VOID Sound3D_RemoveAllSounds(VOID) {	

	lpSound3D_SoundRecord temp = sound3DGlobs.soundRecord;
	
	while (temp) Sound3D_RemoveSound(temp->frame, temp->sound3DBuff);

	Sound3D_Stream_Stop(FALSE);
	Sound3D_Stream_Stop(TRUE);
}


static VOID Sound3D_AttachSound( LPDIRECT3DRMFRAME3 frame, LPDIRECTSOUND3DBUFFER sound3DBuff )
{	
	Container_AppData *data = (Container_AppData *)frame->lpVtbl->GetAppData( frame );
	lpSound3D_SoundFrameRecord temp;


	temp = Mem_Alloc( sizeof(Sound3D_SoundFrameRecord) );
	if( data )
		temp->next = data->soundList;
	else
		temp->next = NULL;
	temp->sound3DBuff = sound3DBuff;

	temp->pos.x = 0;
	temp->pos.y = 0;
	temp->pos.z = 0;

	Container_Frame_SetAppData( frame, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, temp, NULL);

	Sound3D_RegisterUpdateFrame(frame);

	//NOTE REMOVING THIS LINE MEANS SOUNDS WILL NEVER MOVE IF A FRAME IS MOVED
	//THEREFORE A SOUND WILL PLAY IN ITS ENTIRITY FROM WHERE IT WAS ACTIVATED
	//frame->lpVtbl->AddMoveCallback( frame, Sound3D_SoundCallback, NULL, D3DRMCALLBACK_PREORDER );
}


static BOOL Sound3D_RecurseRemoveSound( LPDIRECT3DRMFRAME3 owner, LPDIRECTSOUND3DBUFFER sound3DBuff, lpSound3D_SoundFrameRecord record )
{	
	lpSound3D_SoundFrameRecord temp;
	

	if( !record )
		return FALSE;

	if( Sound3D_RecurseRemoveSound(owner, sound3DBuff, record->next) )
	{	
		Sound3D_RemoveSoundRecord( owner, sound3DBuff );

		temp = record->next;
		record->next = temp->next;
		Mem_Free( temp );
	}

	if( sound3DBuff == record->sound3DBuff )
		return TRUE;

	return FALSE;
}


static VOID Sound3D_RemoveSound( LPDIRECT3DRMFRAME3 owner, LPDIRECTSOUND3DBUFFER sound3DBuff )
{	
	lpSound3D_SoundFrameRecord temp;
	Container_AppData *data;
	

	sound3DBuff->lpVtbl->Release( sound3DBuff );

	if( !owner )
	{	
		Sound3D_RemoveSoundRecord( NULL, sound3DBuff );

		return;
	}

	data = (Container_AppData *)owner->lpVtbl->GetAppData( owner );

	if( Sound3D_RecurseRemoveSound(owner, sound3DBuff, data->soundList) )
	{	
		Sound3D_RemoveSoundRecord( owner, sound3DBuff );

		temp = data->soundList;
		data->soundList = data->soundList->next;
	 Mem_Free( temp );
	}

	Sound3D_RemoveUpdateFrame(owner);

	//if( NULL == data->soundList )
		//owner->lpVtbl->DeleteMoveCallback( owner, Sound3D_SoundCallback, NULL );
}


VOID Sound3D_Update(VOID) {	

	lpSound3D_SoundRecord next, temp = sound3DGlobs.soundRecord;
	DWORD status;

	Sound3D_UpdateFrames();

	while (temp) {

		next = temp->next;

		temp->soundBuff->lpVtbl->GetStatus(temp->soundBuff, &status);

		if (!(DSBSTATUS_PLAYING & status)) Sound3D_RemoveSound(temp->frame, temp->sound3DBuff);
	
		temp = next;
	}

	Sound3D_Stream_CheckPosition(FALSE);
	Sound3D_Stream_CheckPosition(TRUE);
}


VOID Sound3D_SetMinDistForAtten( REAL dist )
{	
	lpSound3D_SoundRecord temp = sound3DGlobs.soundRecord;
	

	sound3DGlobs.minDistanceForAttentuation = dist;

	while( temp )
	{	
		temp->sound3DBuff->lpVtbl->SetMinDistance( temp->sound3DBuff, dist, DS3D_IMMEDIATE );
		
		temp = temp->next;
	}
}


VOID Sound3D_SetMaxDist( REAL dist )
{	
	lpSound3D_SoundRecord temp = sound3DGlobs.soundRecord;
	

	sound3DGlobs.maxDistance = dist;

	while( temp )
	{	
		temp->sound3DBuff->lpVtbl->SetMaxDistance( temp->sound3DBuff, dist, DS3D_IMMEDIATE );
		
		temp = temp->next;
	}
}


/*
VOID Sound3D_SetGlobalVolume( SLONG vol )
{
	lpSound3D_SoundRecord temp = sound3DGlobs.soundRecord;
	

	if( Sound3D_CheckVolumeLimits(vol) )
	{	
		sound3DGlobs.volume = vol;

		while( temp )
		{	
			temp->soundBuff->lpVtbl->SetVolume( temp->soundBuff, vol );
			
			temp = temp->next;
		}
	}
}
*/


VOID Sound3D_SetGlobalVolume( SLONG vol )
{
	if( Sound3D_Initialised() )
	{
		if( Sound3D_CheckVolumeLimits(vol) )
		{
			sound3DGlobs.volume = vol;

			lpDSBuff()->lpVtbl->SetVolume( lpDSBuff(), vol );

			//if( sound3DGlobs.streamData.playing && sound3DGlobs.streamData.fileOpen )
			//	lpDSStreamBuff()->lpVtbl->SetVolume( lpDSStreamBuff(), vol );
		}
	}
}

VOID Sound3D_SetGlobalVolumePrescaled( SLONG vol )
{
	static SLONG realVol[11] = {
		-10000, -5000, -3500, -2000, -1500, -1000, -700, -400, -200, -80, 0
	};

	if (vol < 0 || vol > 10) return;

	Sound3D_SetGlobalVolume(realVol[vol]);
}


VOID Sound3D_SetVolumeToDefault( VOID )
{
	if( Sound3D_Initialised() )
	{
		sound3DGlobs.volume = SOUND3D_DEFAULTSOUNDVOLUME;

		lpDSBuff()->lpVtbl->SetVolume( lpDSBuff(), SOUND3D_DEFAULTSOUNDVOLUME );

		//if( sound3DGlobs.streamData.playing && sound3DGlobs.streamData.fileOpen )
		//	lpDSStreamBuff()->lpVtbl->SetVolume( lpDSStreamBuff(), SOUND3D_DEFAULTSOUNDVOLUME );
	}
}


static BOOL Sound3D_LoadSample( lpSound3D_SoundData sound, LPUCHAR fName, BOOL simultaneous )
{	
	HMMIO hmmioIn;        
	MMCKINFO ckInRiff, ckIn;
	int nError;
	UINT cbActualRead;
	LPVOID fileData;
	ULONG fileSize;


	memset( sound, 0, sizeof(Sound3D_SoundData) );

	if( fileData = File_LoadBinary(fName, &fileSize) )
	{
		if( (nError = WaveOpenFile(fileData, fileSize, &hmmioIn, &sound->pwf, &ckInRiff)) != 0 )
			goto err;

		if( (nError = WaveStartDataRead(&hmmioIn, &ckIn, &ckInRiff)) != 0 )
			goto err;

		// Ok, size of wave data is in ckIn, allocate that buffer.
		if( (sound->data = (BYTE *)GlobalAlloc(GMEM_FIXED, ckIn.cksize)) == NULL )
		{	
			nError = ER_MEM;
			goto err;
		}

		if( (nError = WaveReadFile(hmmioIn, ckIn.cksize, sound->data, &ckIn, &cbActualRead)) != 0 )
			goto err;
		
		sound->size = cbActualRead;

		// Close the wave file. 
		if( hmmioIn != NULL )
		{	mmioClose( hmmioIn, 0 );
			hmmioIn = NULL;
		}

		if( Sound3D_CreateSoundBuffer(sound, simultaneous) == FALSE )
			goto err;
		if( Sound3D_SendSoundToBuffer(sound) == FALSE )
			goto err;

		if( sound->data != NULL )
		{	
			GlobalFree(sound->data);
			sound->data = NULL;
		}

		Mem_Free( fileData );

		return TRUE;
	}

err:
	Error_Warn( TRUE, "Error loading sample." );

	if( sound->data != NULL )
	{	
		GlobalFree( sound->data );
		sound->data = NULL;
	}

	return FALSE;
}


BOOL Sound3D_CreateSoundBuffer( lpSound3D_SoundData sound, BOOL simultaneous )
{	
	DSBUFFERDESC dsbuf;
	ULONG soundNum;


	memset( &dsbuf, 0, sizeof(DSBUFFERDESC) );
	dsbuf.dwSize = sizeof(DSBUFFERDESC);
	dsbuf.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRL3D | DSBCAPS_STATIC | DSBCAPS_MUTE3DATMAXDISTANCE;
	dsbuf.dwBufferBytes = sound->size;
	dsbuf.lpwfxFormat = sound->pwf;

	if( DS_OK != lpDSnd()->lpVtbl->CreateSoundBuffer(lpDSnd(), &dsbuf, &sound->lpDsb3D[0], NULL) )
	{	
		Error_Warn( TRUE, "Cannot create sound buffer." );
		
		return FALSE;
	}

	sound->voice = 0;

	if( simultaneous )
	{			
		for( soundNum = 1; soundNum < SOUND3D_MAXSIMULTANEOUS; soundNum++ )
		{
			if( DS_OK != lpDSnd()->lpVtbl->DuplicateSoundBuffer(lpDSnd(), sound->lpDsb3D[0], &sound->lpDsb3D[ soundNum ]) )
			{
				Error_Warn( TRUE, "Cannot duplicate sound buffer." );

				return FALSE;
			}
		}
	}
	
	return TRUE;
}


BOOL Sound3D_SendSoundToBuffer( lpSound3D_SoundData sound )
{	
	LPVOID	lpvPtr1;
	DWORD	dwBytes1=0;
	LPVOID	lpvPtr2;
	DWORD	dwBytes2=0;
	HRESULT hr;


	hr = sound->lpDsb3D[0]->lpVtbl->Lock( sound->lpDsb3D[0], sound->offset, sound->size, &lpvPtr1,
		&dwBytes1, &lpvPtr2, &dwBytes2, 0);

	if( hr == DSERR_BUFFERLOST )
	{	
		sound->lpDsb3D[0]->lpVtbl->Restore( sound->lpDsb3D[0] );
		hr = sound->lpDsb3D[0]->lpVtbl->Lock( sound->lpDsb3D[0], sound->offset, sound->size, &lpvPtr1,
			&dwBytes1, &lpvPtr2, &dwBytes2, 0 );
	}
	else if( hr != DS_OK)
	{	
		Error_Warn( TRUE, "Error locking sound buffer." );

		return FALSE;
	}

	CopyMemory( lpvPtr1, sound->data , dwBytes1 );

	if( lpvPtr2 != NULL )
		CopyMemory( lpvPtr2, sound->data+dwBytes1, dwBytes2 );
	
	if( DS_OK != sound->lpDsb3D[0]->lpVtbl->Unlock(sound->lpDsb3D[0], lpvPtr1, dwBytes1, lpvPtr2, dwBytes2) )
	{	
		Error_Warn( TRUE, "Error unlocking sound buffer." );

		return FALSE;
	}	

	if( DS_OK != sound->lpDsb3D[0]->lpVtbl->GetFrequency(sound->lpDsb3D[0], &sound->freq) )
	{	
		Error_Warn( TRUE, "Error getting sound frequency buffer." );

		return FALSE;
	}

	if( DS_OK != sound->lpDsb3D[0]->lpVtbl->GetVolume(sound->lpDsb3D[0], &sound->volume) )
	{	
		Error_Warn( TRUE, "Error getting sound volume buffer." );

		return FALSE;
	}

	return TRUE;
}


REAL Sound3D_GetSamplePlayTime( SLONG handle )
{
	lpSound3D_SoundData soundData;
	

	if( -1 == handle )
		return 0.0f;

	soundData = &sound3DGlobs.soundTable[handle];

	if( soundData->flags & SOUND3D_FLAG_STREAM )
		return ( (REAL)soundData->size / (REAL)soundData->avgBytesPerSec );
	else
		return ( (REAL)soundData->size / (REAL)soundData->pwf->nAvgBytesPerSec );
}

BOOL Sound3D_Stream_Play(LPUCHAR fName, BOOL loop, SLONG volume) {

	lpSound3D_StreamData streamData;

	if (loop) streamData = &sound3DGlobs.loopStreamData;
	else streamData = &sound3DGlobs.streamData;

	if (streamData->playing || streamData->fileOpen) Sound3D_Stream_Stop(loop);

	if (Sound3D_Stream_BufferSetup(fName, loop, volume)) {

		// Ensure that position is at 0, ready to go
		lpDSStreamBuff(loop)->lpVtbl->SetCurrentPosition(lpDSStreamBuff(loop), 0);

		//MUST BE PLAYED LOOPING ON STREAM BUFFER
		lpDSStreamBuff(loop)->lpVtbl->Play(lpDSStreamBuff(loop), 0, 0, DSBPLAY_LOOPING);

		streamData->playing = TRUE;
		return TRUE;

	} else {

		streamData->playing = FALSE;
		return FALSE;
	}
}

BOOL Sound3D_Stream_Stop(BOOL looping) {

	lpSound3D_StreamData streamData;

	if (looping) streamData = &sound3DGlobs.loopStreamData;
	else streamData = &sound3DGlobs.streamData;

	streamData->playing = FALSE;

	if (streamData->fileOpen) {

		lpDSStreamBuff(looping)->lpVtbl->Stop(lpDSStreamBuff(looping));
		WaveCloseReadFile(&streamData->wiWave.hmmio, &streamData->wiWave.pwfx);
		lpDSStreamBuff(looping)->lpVtbl->Release(lpDSStreamBuff(looping));

		streamData->fileOpen = FALSE;
	}

	return TRUE;
}

BOOL Sound3D_Stream_BufferSetup( LPUCHAR waveFName, BOOL loop, SLONG volume )
{
	DSBUFFERDESC dsbd;
    int nChkErr;
	int nRem;
	lpSound3D_StreamData streamData;
	
	if (loop) streamData = &sound3DGlobs.loopStreamData;
	else streamData = &sound3DGlobs.streamData;

    if(( nChkErr = WaveOpenFile2( waveFName, &streamData->wiWave.hmmio, &streamData->wiWave.pwfx, &streamData->wiWave.mmckInRIFF )) != 0 )
    {
		Error_Warn( TRUE, "Error opening wave file." );
		return FALSE;
	}

    if( streamData->wiWave.pwfx->wFormatTag != WAVE_FORMAT_PCM )
    {
		Error_Warn( TRUE, "Wave file not PCM." );
		WaveCloseReadFile( &streamData->wiWave.hmmio, &streamData->wiWave.pwfx );
		return FALSE;
	}
	
	// Seek to the data chunk. mmck.ckSize will be the size of all the data in the file.
    if(( nChkErr = WaveStartDataRead( &streamData->wiWave.hmmio, &streamData->wiWave.mmck, &streamData->wiWave.mmckInRIFF )) != 0 )
	{
		Error_Warn( TRUE, "Seek failed." );
		WaveCloseReadFile( &streamData->wiWave.hmmio, &streamData->wiWave.pwfx );
		return FALSE;
	}

    // Calculate a buffer length 3 sec. long. This should be an integral number of the
	// number of bytes in one notification period. 
	streamData->wiWave.dwNotifySize = streamData->wiWave.pwfx->nSamplesPerSec * 3 * (DWORD)streamData->wiWave.pwfx->nBlockAlign;
	streamData->wiWave.dwNotifySize = streamData->wiWave.dwNotifySize / SOUND3D_NUMOFPLAYNOTIFICATIONS;
	// the notify size should be an intergral multiple of the nBlockAlignvalue.
	if ((nRem = streamData->wiWave.dwNotifySize % (DWORD)streamData->wiWave.pwfx->nBlockAlign) != 0)
		streamData->wiWave.dwNotifySize += (streamData->wiWave.pwfx->nBlockAlign - nRem);
	streamData->wiWave.dwBufferSize = streamData->wiWave.dwNotifySize * SOUND3D_NUMOFPLAYNOTIFICATIONS;	

    //Create the secondary DirectSoundBuffer object to receive our sound data.
    memset( &dsbd, 0, sizeof( DSBUFFERDESC ));
    dsbd.dwSize = sizeof( DSBUFFERDESC );
    // Use new GetCurrentPosition() accuracy (DirectX 2 feature)
    dsbd.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GETCURRENTPOSITION2;
    dsbd.dwBufferBytes = streamData->wiWave.dwBufferSize;

    //Set Format properties according to the WAVE file we just opened
    dsbd.lpwfxFormat = streamData->wiWave.pwfx;
    
	{
		LPDIRECTSOUNDBUFFER newBuffer;
		if (DS_OK != lpDSnd()->lpVtbl->CreateSoundBuffer(lpDSnd(), &dsbd, &newBuffer, NULL)) {
			Error_Warn( TRUE, "Cannot create sound buffer." );
			return FALSE;
		}

		if (loop) sound3DGlobs.lpDSLoopStreamBuff = newBuffer;
		else sound3DGlobs.lpDSStreamBuff = newBuffer;

	}

	lpDSStreamBuff(loop)->lpVtbl->SetVolume(lpDSStreamBuff(loop), volume);
			
    streamData->wiWave.bFoundEnd = FALSE;
	streamData->wiWave.dwNextWriteOffset = 0;
	//KEEP STREAM WRITE 2 NOTIFICATIONS BEHIND PLAY
	//AND WRITE SINGLE NOTIFICATION BLOCKS OF DATA
	streamData->wiWave.dwNextProgressCheck = streamData->wiWave.dwNotifySize * 2;

	//ADD LOOP CAP HERE
    streamData->wiWave.bLoopFile = loop;

	// Fill data in the buffer.
    Sound3D_Stream_FillDataBuffer(loop);

	// we're set to play now.
    streamData->wiWave.bDonePlaying = FALSE;

	streamData->fileOpen = TRUE;

    return TRUE;
}

BOOL Sound3D_Stream_FillDataBuffer(BOOL looping) {

    lpSound3D_StreamData streamData;
	LPBYTE  lpWrite1, lpWrite2;
    DWORD	dwLen1, dwLen2;
    UINT	uActualBytesWritten;
    DWORD dwBytes;

	if (looping) streamData = &sound3DGlobs.loopStreamData;
	else streamData = &sound3DGlobs.streamData;

	dwBytes = streamData->wiWave.dwBufferSize;

	// This is the initial read. So we fill the entire buffer.
	// This will not wrap around so the 2nd pointers will be NULL.
    if (DS_OK != lpDSStreamBuff(looping)->lpVtbl->Lock(lpDSStreamBuff(looping), 0, dwBytes, &((LPVOID)lpWrite1), &dwLen1, &(LPVOID)lpWrite2, &dwLen2, 0) ) {

		Error_Warn(TRUE, "Cannot lock stream buffer.");
		return FALSE;
	}

    WaveReadFile(streamData->wiWave.hmmio, (UINT)dwLen1, lpWrite1, &streamData->wiWave.mmck, &uActualBytesWritten);
	
	// if the number of bytes written is less than the 
	// amount we requested, we have a short file.
	if (uActualBytesWritten < dwLen1) {
		if (!streamData->wiWave.bLoopFile) {

			// we set the bFoundEnd flag if the length is less than
			// one notify period long which is when the first notification comes in.
			// The next notification will then call send a message to process a stop. 
			if (uActualBytesWritten < streamData->wiWave.dwNotifySize) streamData->wiWave.bFoundEnd = TRUE;
			// Fill in silence for the rest of the buffer.
			FillMemory(lpWrite1+uActualBytesWritten, dwLen1-uActualBytesWritten, (BYTE)(streamData->wiWave.pwfx->wBitsPerSample == 8 ? 128 : 0));

		} else {

			// we are looping.
			UINT uWritten = uActualBytesWritten;	// from previous call above.

			while (uWritten < dwLen1) {	

				// this will keep reading in until the buffer is full. For very short files.
				WaveStartDataRead(&streamData->wiWave.hmmio, &streamData->wiWave.mmck, &streamData->wiWave.mmckInRIFF);
				WaveReadFile(streamData->wiWave.hmmio, (UINT)dwLen1-uWritten, lpWrite1 + uWritten, &streamData->wiWave.mmck, &uActualBytesWritten);
				uWritten += uActualBytesWritten;
			}
		}
	}

	// now unlock the buffer.
	
	lpDSStreamBuff(looping)->lpVtbl->Unlock(lpDSStreamBuff(looping), (LPVOID)lpWrite1, dwLen1, NULL, 0);
                                                                        
	streamData->wiWave.dwNextWriteOffset += dwLen1;	
	// this is a circular buffer. Do mod buffersize.
	if (streamData->wiWave.dwNextWriteOffset >= streamData->wiWave.dwBufferSize) streamData->wiWave.dwNextWriteOffset -= streamData->wiWave.dwBufferSize; 

	streamData->wiWave.dwProgress = 0;
	streamData->wiWave.dwLastPos = 0;

	return TRUE;
}

/*

BOOL Sound3D_Stream_SetupCheckPositions( VOID )
{
	lpSound3D_StreamData streamData = &sound3DGlobs.streamData;
	int hr = DS_OK;
	DWORD dwSize = streamData->wiWave.dwNotifySize;	
	int i;


	// setup the first one.
	streamData->dsbCheckPos[0] = dwSize;
	
	for( i = 1; i < SOUND3D_NUMOFPLAYNOTIFICATIONS; i++ )
		streamData->dsbCheckPos[i] = streamData->dsbCheckPos[i - 1] + dwSize;
	
	streamData->dsbCheckPos[i - 1] -= 1;
	// set the stop notification.
	streamData->dsbCheckPos[i] = DSBPN_OFFSETSTOP;
	
	return TRUE;
}

*/

VOID Sound3D_Stream_CheckPosition(BOOL looping) {

	lpSound3D_StreamData streamData;
	DWORD hr = DS_OK;
	DWORD hRet = 0;
	DWORD dwPlayPos, dwWritePos, dwPlayed;
	BOOL sameLoop;

	if (looping) streamData = &sound3DGlobs.loopStreamData;
	else streamData = &sound3DGlobs.streamData;

	if (streamData->playing && streamData->fileOpen) {

		lpDSStreamBuff(looping)->lpVtbl->GetCurrentPosition(lpDSStreamBuff(looping), &dwPlayPos, &dwWritePos);

		if (dwPlayPos < streamData->wiWave.dwLastPos) dwPlayed = streamData->wiWave.dwBufferSize - streamData->wiWave.dwLastPos + dwPlayPos;
		else dwPlayed = dwPlayPos - streamData->wiWave.dwLastPos;
		
		streamData->wiWave.dwProgress += dwPlayed;
		streamData->wiWave.dwLastPos = dwPlayPos;	
		sameLoop = FALSE;

		while (streamData->wiWave.dwProgress > streamData->wiWave.dwNextProgressCheck) {

			// A play notification has been received.
			LPBYTE lpWrite1;
			DWORD dwWrite1;
			UINT cbActual = 0;
			
			//ON NEXT NOTIFICATION, IF DONE PLAYING IS SET STOP THE SOUND
			if (streamData->wiWave.bDonePlaying && !sameLoop) {
				Sound3D_Stream_Stop(looping);
				break;
			}

			sameLoop = TRUE;

			// If the entire file has been read into the buffer, bFoundEnd will be TRUE.
			if (!streamData->wiWave.bFoundEnd) {	
				// read in more of the file.
				
				Error_Debug( Error_Format("Next write pos =	%i\n", streamData->wiWave.dwNextWriteOffset) );
				Error_Debug( Error_Format("Write size =	%i\n\n", streamData->wiWave.dwNotifySize) );

				// Lock the buffer.
				if (DS_OK != lpDSStreamBuff(looping)->lpVtbl->Lock(lpDSStreamBuff(looping), streamData->wiWave.dwNextWriteOffset, streamData->wiWave.dwNotifySize, &lpWrite1, &dwWrite1, NULL, NULL, 0)) {
					Error_Warn( TRUE, "Cannot lock stream buffer." );
					return;
				}
				
				// now read the file. 
				WaveReadFile(streamData->wiWave.hmmio, dwWrite1, lpWrite1, &streamData->wiWave.mmck, &cbActual);

				//	if cbActual is less than the amount asked for, we may have
				//	reached end of file. If we are looping, we will simply read the 
				//	file in again until we have written dwWrite1 bytes into the buffer.
				//	If not looping we fill with silence.
				if ((DWORD)cbActual < dwWrite1) {
					if (!streamData->wiWave.bLoopFile) {

						streamData->wiWave.bFoundEnd = TRUE;
						// fill up the rest of the buffer with silence.
						FillMemory(lpWrite1+cbActual, (UINT)dwWrite1-cbActual, (BYTE)(streamData->wiWave.pwfx->wBitsPerSample == 8 ? 128 : 0));

					} else {
						
						// we're looping. Read in the file again.
						int nChkErr = 0;
						UINT cbWritten = cbActual;	// from previous call above.
						
						while (cbWritten < (UINT)dwWrite1) {	// write only one notification worth.

							// this will keep reading in until the buffer is full. For very short files.
							WaveStartDataRead( &streamData->wiWave.hmmio, &streamData->wiWave.mmck, &streamData->wiWave.mmckInRIFF );
							WaveReadFile( streamData->wiWave.hmmio, (UINT)dwWrite1-cbWritten, 
													lpWrite1 + cbWritten, &streamData->wiWave.mmck, &cbActual );
							cbWritten += cbActual;
						}
					}
				}

				//unlock now
				lpDSStreamBuff(looping)->lpVtbl->Unlock(lpDSStreamBuff(looping), (LPVOID)lpWrite1, dwWrite1,  NULL, 0);
				// setup the nextwrite offset.
				streamData->wiWave.dwNextWriteOffset += dwWrite1;
				//check += dwWrite1;
				streamData->wiWave.dwNextProgressCheck += dwWrite1;
				//if (check >= streamData->wiWave.dwBufferSize)
				//	lastCheckWrap = TRUE;
				if (streamData->wiWave.dwNextWriteOffset >= streamData->wiWave.dwBufferSize) streamData->wiWave.dwNextWriteOffset -= streamData->wiWave.dwBufferSize;

			} else {

				// We have read in the whole file. We will keep filling in silence
				// in the buffer to allow the remaining sound bytes filled earlier 
				// to be played. 
				
				// Allow the rest of the bytes to be played and fill here
				// with silence. The next notification will quit the while loop.
				lpDSStreamBuff(looping)->lpVtbl->Lock(lpDSStreamBuff(looping), streamData->wiWave.dwNextWriteOffset, streamData->wiWave.dwNotifySize, &lpWrite1, &dwWrite1, NULL, NULL, 0 );
				FillMemory( lpWrite1, dwWrite1, (BYTE)(streamData->wiWave.pwfx->wBitsPerSample == 8 ? 128 : 0) );

				hr = lpDSStreamBuff(looping)->lpVtbl->Unlock(lpDSStreamBuff(looping), (LPVOID)lpWrite1, dwWrite1,  NULL, 0);
				
				// We don't want to cut off the sound before it's done playing.
				//ON NEXT NOTIFICATION, IF DONE PLAYING IS SET STOP THE SOUND
				if (streamData->wiWave.mmckInRIFF.cksize > streamData->wiWave.dwNotifySize &&
					streamData->wiWave.dwProgress >= streamData->wiWave.mmckInRIFF.cksize - streamData->wiWave.dwNotifySize) {

					streamData->wiWave.bDonePlaying = TRUE;

				} else if (streamData->wiWave.dwProgress >= streamData->wiWave.mmckInRIFF.cksize) {
					// for short files.
					streamData->wiWave.bDonePlaying = TRUE;
				}
				
				streamData->wiWave.dwNextProgressCheck += dwWrite1;
			}
		}
	}
}


static BOOL Sound3D_D3DVectorEqual( LPD3DVECTOR a, LPD3DVECTOR b )
{
	if( (a->x == b->x) &&
		(a->y == b->y) &&
		(a->z == b->z) )
		return TRUE;

	return FALSE;
}


REAL Sound3D_SetRollOffFactor( REAL rollOff )
{

	if (Sound3D_Initialised()) {

		if( rollOff < DS3D_MINROLLOFFFACTOR )
			rollOff = DS3D_MINROLLOFFFACTOR;

		if( rollOff > DS3D_MAXROLLOFFFACTOR )
			rollOff = DS3D_MAXROLLOFFFACTOR;
		
		lp3DListenerInfo()->lpVtbl->SetRolloffFactor( lp3DListenerInfo(), rollOff, DS3D_IMMEDIATE );
	}

	return rollOff;
}

SLONG Sound3D_MaxVolume() {
	return DSBVOLUME_MAX;
}

SLONG Sound3D_MinVolume() {
	return DSBVOLUME_MIN;
}


