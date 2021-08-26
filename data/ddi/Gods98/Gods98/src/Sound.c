
#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <d3drm.h>
#include <mmsystem.h>
#include <dsound.h>
#include <process.h>

#include "..\Inc\Standard.h"
#include "..\Inc\Main.h"
#include "..\Inc\Errors.h"
#include "..\Inc\Memory.h"
#include "..\Inc\Sound.h"
#include "..\Inc\Files.h"
#include "..\Inc\3DSound.h"

#pragma comment ( lib, "dsound" )

Sound_Globs soundGlobs = { 0 };
SND sndTbl[MAX_SAMPLES];

// My mapping of the sound functions...

BOOL Sound_Initialise(BOOL nosound){

	soundGlobs.initialised = (FALSE == nosound);
	soundGlobs.loopCDTrack = -1;

	if (nosound)
		return TRUE;

	if( Sound3D_Initialise(Main_hWnd()) )
		return TRUE;

	return FALSE;
}

BOOL Sound_IsInitialised(VOID) {

	return (soundGlobs.initialised && Sound3D_Initialised());
}

/*
BOOL Sound_Initialise(VOID){

	ULONG loop;

	if (InitSound(Main_hWnd())){
		if( Sound3D_Initialise(Main_hWnd()) ){

			for (loop=0 ; loop<MAX_SAMPLES ; loop++){
				soundGlobs.soundList[loop].handle = -1;
			}
			soundGlobs.useSound = 0;
			soundGlobs.initialised = TRUE;
			soundGlobs.loopCDTrack = -1;
			return TRUE;

		}
	}
	soundGlobs.initialised = FALSE;
	return FALSE;
}
*/
lpSound Sound_Load(LPUCHAR fname){

	if (soundGlobs.initialised){
		lpSound sound = NULL;

		Error_Fatal(soundGlobs.useSound == MAX_SAMPLES, "Run out of samples");
	
		if (Load_Sample(soundGlobs.useSound, fname)){
			sound = &soundGlobs.soundList[soundGlobs.useSound];
			sound->handle = soundGlobs.useSound;
			soundGlobs.useSound++;
		} else Error_Warn(TRUE, "Cannot load sound...");

		return sound;
	}

	return FALSE;
}

VOID Sound_Play(lpSound sound, ULONG mode){

	if (soundGlobs.initialised){
		if (sound) Play_Sample(sound->handle, mode);
	}
}

VOID Sound_Stop(lpSound sound){

	if (soundGlobs.initialised){
		if (sound) Sample_Stop(sound->handle);
	}
}

BOOL Sound_PlayCDTrack(ULONG track, ULONG mode, VOID (*StopCallback)(VOID)){

	if (soundGlobs.initialised){
		if (Sound_Loop == mode) soundGlobs.loopCDTrack = TRUE;
		soundGlobs.currTrack = track;
		soundGlobs.CDStopCallback = StopCallback;
		return Play_CDTrack(track);
	}

	return FALSE;
}

BOOL Sound_StopCD(VOID){

	if (soundGlobs.initialised){
		return Stop_CDTrack();
	}

	return FALSE;
}

/*
VOID Sound_CDThread(LPVOID data) {

	while(1) {
		if (soundGlobs.updateCDTrack) {
			if (!Status_CDTrack(soundGlobs.currTrack)) {
				if (soundGlobs.loopCDTrack) Restart_CDTrack(soundGlobs.currTrack);
				if (soundGlobs.CDStopCallback) soundGlobs.CDStopCallback();
			}
		}
		Sleep(10);
	}

}

VOID Sound_Update(BOOL cdtrack) {

	if (soundGlobs.initialised){
		static BOOL threadStarted = FALSE;
		soundGlobs.updateCDTrack = cdtrack;
		if (!threadStarted) {
			_beginthread(Sound_CDThread, 0, NULL);
			threadStarted = TRUE;
		}
	}
}
*/

VOID Sound_Update(BOOL cdtrack) {

	if (soundGlobs.initialised){
		static ULONG lastUpdate = 0;
		ULONG time = timeGetTime();

		if (time > (lastUpdate + 4000)) {
			if (cdtrack) {
				if (!Status_CDTrack(soundGlobs.currTrack)) {
					if (soundGlobs.loopCDTrack) Restart_CDTrack(soundGlobs.currTrack);
					if (soundGlobs.CDStopCallback) soundGlobs.CDStopCallback();
				}
			}
			lastUpdate = time;
		}
	}
}

LPDIRECTSOUND lpDS = NULL;
HRESULT hr;
DSCAPS dsCaps;

int sMult=1;
int sDiv=1;
int sOffs=0;
//int cdDisable = 0;

MCIERROR mciErr=0;
UINT dwReturn;

char mciReturn[MCI_RETURN_SIZE];
char cdDev[]="cdaudio";


BOOL InitSampleList(void)
{

	return TRUE;
}

static BOOL InitSound(HWND hwnd)
{
	memset (&sndTbl, 0 , SND_MAX * sizeof(SND));

	InitSampleList();

	hr = DirectSoundCreate(NULL, &lpDS, NULL);
	if (hr != DS_OK)
	{
		Error_Warn(TRUE,"Could not create Direct Sound Interface");
		return FALSE;
	}
	hr = lpDS->lpVtbl->SetCooperativeLevel(lpDS, hwnd, DSSCL_NORMAL);
	if (hr !=DS_OK)
	{
		Error_Warn(TRUE,"Could not set cooperative level for sound");
		return FALSE;
	}

	dsCaps.dwSize=sizeof(DSCAPS);
	hr = lpDS->lpVtbl->GetCaps(lpDS, &dsCaps);
	if (hr !=DS_OK)
	{
		Error_Warn(TRUE,"Could not get sound capabilities");
		return FALSE;
	}

	return TRUE;
}


static void StopAllSounds(void)
{
#ifdef MULTI_SOUND
	int i,j;
#else
	int i;
#endif

	for(i=0;i<SND_MAX;i++)
	{
		if(sndTbl[i].sActive)
		{
			hr=sndTbl[i].lpDsb->lpVtbl->Stop(sndTbl[i].lpDsb);
#ifdef MULTI_SOUND
			for(j=0;j<MULTI_SOUND;j++)
			{
				hr=sndTbl[i].lpDsbM[j]->lpVtbl->Stop(sndTbl[i].lpDsbM[j]);
			}
#endif
		}
	}
}


static BOOL Close_Sound(void)
{
#ifdef MULTI_SOUND
	int i,j;
#else
	int i;
#endif
	for(i=0;i<SND_MAX;i++)
	{
		if(sndTbl[i].sActive)
		{
			hr=sndTbl[i].lpDsb->lpVtbl->Release(sndTbl[i].lpDsb);
#ifdef MULTI_SOUND
			for(j=0;j<MULTI_SOUND;j++)
			{
				hr=sndTbl[i].lpDsbM[j]->lpVtbl->Release(sndTbl[i].lpDsbM[j]);
			}
#endif
		}
	}
	if(hr != DS_OK) goto err;

	return TRUE;
err:
	return FALSE;

}

static void Sample_Frequency(int n, float r)
{
	int freq;

	if(sndTbl[n].sActive)
	{
		freq = (int )(sndTbl[n].cFreq * r);
		hr = sndTbl[n].lpDsb->lpVtbl->SetFrequency(sndTbl[n].lpDsb, freq);
	}
}

static void Sample_Volume(int n, float r)
{
	int vol;
	float rc;
	int max=DSBVOLUME_MIN;

	if(sndTbl[n].sActive)
	{
		rc=r;
		if (rc>=1.0) rc=1.0;
		vol = (int)((1-rc) / max);

		hr = sndTbl[n].lpDsb->lpVtbl->SetVolume(sndTbl[n].lpDsb, vol);
	}
}

void Sample_Stop(int n)
{
	if(sndTbl[n].sActive)
	{
		hr = sndTbl[n].lpDsb->lpVtbl->Stop(sndTbl[n].lpDsb);
	}
}


static BOOL Play_Sample(int n, int f)
{
	int loop=0;
#ifdef MULTI_SOUND
	int voice;
#endif

	if(sndTbl[n].sActive)
	{
		if(f&SAMP_LOOP)
			loop=DSBPLAY_LOOPING;
		else
			loop=0;
#ifdef MULTI_SOUND
		if(f&SAMP_MULTI)
		{
	 		voice=sndTbl[n].sVoice;
			hr = sndTbl[n].lpDsbM[voice]->lpVtbl->Play(sndTbl[n].lpDsbM[voice], 0, 0, loop);
			voice++;
			if(voice>=MULTI_SOUND) voice = 0;
			sndTbl[n].sVoice=voice;
		}
		else
			hr = sndTbl[n].lpDsb->lpVtbl->Play(sndTbl[n].lpDsb, 0, 0, loop);
#else
		hr = sndTbl[n].lpDsb->lpVtbl->Play(sndTbl[n].lpDsb, 0, 0, loop);
#endif
	}
	return TRUE;
}

static BOOL CreateSoundBuffer(int n)
{
	DSBUFFERDESC	dsbuf;

#ifdef MULTI_SOUND
	int i;
#endif
	if(sndTbl[n].pwf->nSamplesPerSec>44000)
	{
//		sndTbl[n].ppwfxInfo->nSamplesPerSec/=2;
	}
	//Set up DSBUFFERDESC structure

	memset(&dsbuf, 0, sizeof(DSBUFFERDESC));
	dsbuf.dwSize = sizeof(DSBUFFERDESC);

	//Default controls

	dsbuf.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY;

	// time buffer
	dsbuf.dwBufferBytes =  (sndTbl[n].sSize);


//	dsbuf.lpwfxFormat = (LPWAVEFORMATEX)&pcmwf;
	dsbuf.lpwfxFormat = sndTbl[n].pwf;


	//Create buffer
	hr = lpDS->lpVtbl->CreateSoundBuffer(lpDS, &dsbuf, &sndTbl[n].lpDsb, NULL);
	if(hr != DS_OK)	goto err;
#ifdef MULTI_SOUND
	sndTbl[n].sVoice = 0;
	for (i=0;i<MULTI_SOUND;i++)
	{
		hr = lpDS->lpVtbl->DuplicateSoundBuffer(lpDS, sndTbl[n].lpDsb, &sndTbl[n].lpDsbM[i]);
		if(hr != DS_OK)	goto err;
	}
#endif
	goto OK;
err:
	ReportSoundError();

	return FALSE;
OK:
	return TRUE;
}



static void ReportCDError(void)
{
	mciGetErrorString(mciErr, mciReturn, MCI_RETURN_SIZE);

	Error_Warn(TRUE, mciReturn);
}



static void ReportSoundError(void)
{
	char buff[200];

	strcpy(buff,dsError(hr));
	Error_Warn(TRUE, buff);
}


static BOOL SendSoundToBuffer(int n)
{

	LPVOID	lpvPtr1;
	DWORD	dwBytes1=0;
	LPVOID	lpvPtr2;
	DWORD	dwBytes2=0;

	hr = sndTbl[n].lpDsb->lpVtbl->Lock(sndTbl[n].lpDsb,sndTbl[n].sOffset, sndTbl[n].sSize, &lpvPtr1,
		&dwBytes1, &lpvPtr2, &dwBytes2, 0);

	if( hr == DSERR_BUFFERLOST)
	{
		sndTbl[n].lpDsb->lpVtbl->Restore(sndTbl[n].lpDsb);
		hr = sndTbl[n].lpDsb->lpVtbl->Lock(sndTbl[n].lpDsb,sndTbl[n].sOffset, sndTbl[n].sSize, &lpvPtr1,
			&dwBytes1, &lpvPtr2, &dwBytes2, 0);
	}

	if(hr != DS_OK) goto err;

	CopyMemory(lpvPtr1, sndTbl[n].sData , dwBytes1);

	if( lpvPtr2  != NULL )
	{
		CopyMemory(lpvPtr2, sndTbl[n].sData+dwBytes1, dwBytes2);
	}

	hr = sndTbl[n].lpDsb->lpVtbl->Unlock(sndTbl[n].lpDsb, lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);
	if(hr != DS_OK) goto err;


	hr = sndTbl[n].lpDsb->lpVtbl->GetFrequency(sndTbl[n].lpDsb, &sndTbl[n].cFreq);
	if(hr != DS_OK) goto err;

	hr = sndTbl[n].lpDsb->lpVtbl->GetVolume(sndTbl[n].lpDsb, &sndTbl[n].cVolume);
	if(hr != DS_OK) goto err;

	return TRUE;

err:
	ReportSoundError();

	return FALSE;

 
}

static int Load_Sample(int n, char *name)
{

	HMMIO                           hmmioIn;        
	MMCKINFO                        ckInRiff;
	MMCKINFO                        ckIn;
	int                                     nError;
	UINT                            cbActualRead;
	char		buff[100];

	LPVOID fileData;
	ULONG fileSize;

	memset(&sndTbl[n], 0, sizeof(SND));

	sndTbl[n].sActive = 0;

	strcpy(sndTbl[n].sName, name);

	sprintf(buff, "%s.wav",sndTbl[n].sName);

	if (fileData = File_LoadBinary(buff, &fileSize)){

		if ((nError = WaveOpenFile(fileData, fileSize, &hmmioIn, &sndTbl[n].pwf, &ckInRiff)) != 0)
			{
			goto err;
			}

		if ((nError = WaveStartDataRead(&hmmioIn, &ckIn, &ckInRiff)) != 0)
			{
			goto err;
			}

		// Ok, size of wave data is in ckIn, allocate that buffer.
		if ((sndTbl[n].sData = (BYTE *)GlobalAlloc(GMEM_FIXED, ckIn.cksize)) == NULL)
			{
			nError = ER_MEM;
			goto err;
			}

		if ((nError = WaveReadFile(hmmioIn, ckIn.cksize, sndTbl[n].sData, &ckIn, &cbActualRead)) != 0)
			{
			goto err;
			}        
		
		sndTbl[n].sSize = cbActualRead;

		// Close the wave file. 
		if (hmmioIn != NULL)
			{
			mmioClose(hmmioIn, 0);
			hmmioIn = NULL;
			}


		if(CreateSoundBuffer(n) == FALSE) goto err;
		if(SendSoundToBuffer(n) == FALSE) goto err;

		if (sndTbl[n].sData != NULL)
			{
			GlobalFree(sndTbl[n].sData);
			sndTbl[n].sData = NULL;
			}

		sndTbl[n].sActive = 1;

		Mem_Free(fileData);

		return TRUE;

	} else return FALSE;


err:
	ReportSoundError();
	if (sndTbl[n].sData != NULL)
		{
		GlobalFree(sndTbl[n].sData);
		sndTbl[n].sData = NULL;
		}

	return FALSE;
}

/* This function will open a wave input file and prepare it for reading,
 * so the data can be easily
 * read with WaveReadFile. Returns 0 if successful, the error code if not.
 *      pszFileName - Input filename to load.
 *      phmmioIn    - Pointer to handle which will be used
 *          for further mmio routines.
 *      ppwfxInfo   - Ptr to ptr to WaveFormatEx structure
 *          with all info about the file.                        
 *      
*/
int WaveOpenFile(LPVOID fileData, ULONG fileSize,

//	TCHAR*pszFileName,                              // (IN)
	HMMIO *phmmioIn,                                // (OUT)
	WAVEFORMATEX **ppwfxInfo,                       // (OUT)
	MMCKINFO *pckInRIFF                             // (OUT)
			)
{
	HMMIO           hmmioIn;
	MMCKINFO        ckIn;           // chunk info. for general use.
	PCMWAVEFORMAT   pcmWaveFormat;  // Temp PCM structure to load in.       
	WORD            cbExtraAlloc;   // Extra bytes for waveformatex 
	int             nError;         // Return value.
	MMIOINFO		mmioInfo;		// For loading from memory...


	// Initialization...
	*ppwfxInfo = NULL;
	nError = 0;
	hmmioIn = NULL;

	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	mmioInfo.fccIOProc = FOURCC_MEM;
	mmioInfo.pchBuffer = fileData;
	mmioInfo.cchBuffer = fileSize;
	
	//	if ((hmmioIn = mmioOpen(pszFileName, NULL, MMIO_ALLOCBUF | MMIO_READ)) == NULL)
	if ((hmmioIn = mmioOpen(NULL, &mmioInfo, MMIO_ALLOCBUF | MMIO_READ)) == NULL)
	{
		nError = ER_CANNOTOPEN;
		goto ERROR_READING_WAVE;
	}
	
	if ((nError = (int)mmioDescend(hmmioIn, pckInRIFF, NULL, 0)) != 0)
	{
		goto ERROR_READING_WAVE;
	}
	
	
	if ((pckInRIFF->ckid != FOURCC_RIFF) || (pckInRIFF->fccType != mmioFOURCC('W', 'A', 'V', 'E')))
	{
		nError = ER_NOTWAVEFILE;
		goto ERROR_READING_WAVE;
	}
	
	/* Search the input file for for the 'fmt ' chunk.     */
	ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if ((nError = (int)mmioDescend(hmmioIn, &ckIn, pckInRIFF, MMIO_FINDCHUNK)) != 0)
	{
		goto ERROR_READING_WAVE;                
	}
	
	/* Expect the 'fmt' chunk to be at least as large as <PCMWAVEFORMAT>;
	* if there are extra parameters at the end, we'll ignore them */
	
	if (ckIn.cksize < (long) sizeof(PCMWAVEFORMAT))
	{
		nError = ER_NOTWAVEFILE;
		goto ERROR_READING_WAVE;
	}
	
	/* Read the 'fmt ' chunk into <pcmWaveFormat>.*/     
	if (mmioRead(hmmioIn, (HPSTR) &pcmWaveFormat, (long) sizeof(pcmWaveFormat)) != (long) sizeof(pcmWaveFormat))
	{
		nError = ER_CANNOTREAD;
		goto ERROR_READING_WAVE;
	}
	
	
	// Ok, allocate the waveformatex, but if its not pcm
	// format, read the next word, and thats how many extra
	// bytes to allocate.
	if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
		cbExtraAlloc = 0;                               
	
	else
	{
		// Read in length of extra bytes.
		if (mmioRead(hmmioIn, (LPTSTR) &cbExtraAlloc,
			(long) sizeof(cbExtraAlloc)) != (long) sizeof(cbExtraAlloc))
		{
			nError = ER_CANNOTREAD;
			goto ERROR_READING_WAVE;
		}
		
	}
	
	// Ok, now allocate that waveformatex structure.
	if ((*ppwfxInfo = GlobalAlloc(GMEM_FIXED, sizeof(WAVEFORMATEX)+cbExtraAlloc)) == NULL)
	{
		nError = ER_MEM;
		goto ERROR_READING_WAVE;
	}
	
	// Copy the bytes from the pcm structure to the waveformatex structure
	memcpy(*ppwfxInfo, &pcmWaveFormat, sizeof(pcmWaveFormat));
	(*ppwfxInfo)->cbSize = cbExtraAlloc;
	
	// Now, read those extra bytes into the structure, if cbExtraAlloc != 0.
	if (cbExtraAlloc != 0)
	{
		if (mmioRead(hmmioIn, (LPTSTR) (((BYTE*)&((*ppwfxInfo)->cbSize))+sizeof(cbExtraAlloc)),
			(long) (cbExtraAlloc)) != (long) (cbExtraAlloc))
		{
			nError = ER_NOTWAVEFILE;
			goto ERROR_READING_WAVE;
		}
	}
	
	/* Ascend the input file out of the 'fmt ' chunk. */                                                            
	if ((nError = mmioAscend(hmmioIn, &ckIn, 0)) != 0)
	{
		goto ERROR_READING_WAVE;
		
	}
	
	goto TEMPCLEANUP;               

ERROR_READING_WAVE:
	if (*ppwfxInfo != NULL)
		{
		GlobalFree(*ppwfxInfo);
		*ppwfxInfo = NULL;
		}               

	if (hmmioIn != NULL)
	{
	mmioClose(hmmioIn, 0);
		hmmioIn = NULL;
		}
	
TEMPCLEANUP:
	*phmmioIn = hmmioIn;

	return(nError);

}
#pragma message( "  Err" )
ULONG GetWaveAvgBytesPerSec( char *pszFileName )
{
	HMMIO           hmmioIn;
	MMCKINFO        ckIn;           // chunk info. for general use.
	PCMWAVEFORMAT   pcmWaveFormat;  // Temp PCM structure to load in.       
	int             nError;
	ULONG avgBytesPerSec = 0;
	MMCKINFO		pckInRIFF;


	// Initialization...
	nError = 0;
	hmmioIn = NULL;
	
	if ((hmmioIn = mmioOpen(pszFileName, NULL, MMIO_READ)) == NULL)
		{
		nError = ER_CANNOTOPEN;
		goto ERROR_READING_WAVE;
		}

	if ((nError = (int)mmioDescend(hmmioIn, &pckInRIFF, NULL, 0)) != 0)
		{
		goto ERROR_READING_WAVE;
		}

	if ((pckInRIFF.ckid != FOURCC_RIFF) || (pckInRIFF.fccType != mmioFOURCC('W', 'A', 'V', 'E')))
		{
		nError = ER_NOTWAVEFILE;
		goto ERROR_READING_WAVE;
		}
			
	/* Search the input file for for the 'fmt ' chunk.     */
    ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
    if ((nError = (int)mmioDescend(hmmioIn, &ckIn, &pckInRIFF, MMIO_FINDCHUNK)) != 0)
		{
		goto ERROR_READING_WAVE;
		}
					
	/* Expect the 'fmt' chunk to be at least as large as <PCMWAVEFORMAT>;
    * if there are extra parameters at the end, we'll ignore them */
    
    if (ckIn.cksize < (long) sizeof(PCMWAVEFORMAT))
		{
		nError = ER_NOTWAVEFILE;
		goto ERROR_READING_WAVE;
		}
															
	/* Read the 'fmt ' chunk into <pcmWaveFormat>.*/     
    if (mmioRead(hmmioIn, (HPSTR) &pcmWaveFormat, (long) sizeof(pcmWaveFormat)) != (long) sizeof(pcmWaveFormat))
		{
		nError = ER_CANNOTREAD;
		goto ERROR_READING_WAVE;
		}
	
	avgBytesPerSec = pcmWaveFormat.wf.nAvgBytesPerSec;

ERROR_READING_WAVE:
	if (hmmioIn != NULL)
	{
		mmioClose(hmmioIn, 0);
		hmmioIn = NULL;
	}

	return avgBytesPerSec;
}

int WaveOpenFile2(
	char *pszFileName,                              // (IN)
	HMMIO *phmmioIn,                                // (OUT)
	WAVEFORMATEX **ppwfxInfo,                       // (OUT)
	MMCKINFO *pckInRIFF                             // (OUT)
			)
{
	HMMIO           hmmioIn;
	MMCKINFO        ckIn;           // chunk info. for general use.
	PCMWAVEFORMAT   pcmWaveFormat;  // Temp PCM structure to load in.       
	WORD            cbExtraAlloc;   // Extra bytes for waveformatex 
	int             nError;         // Return value.


	// Initialization...
	*ppwfxInfo = NULL;
	nError = 0;
	hmmioIn = NULL;
	
	if ((hmmioIn = mmioOpen(pszFileName, NULL, MMIO_ALLOCBUF | MMIO_READ)) == NULL)
		{
		nError = ER_CANNOTOPEN;
		goto ERROR_READING_WAVE;
		}

	if ((nError = (int)mmioDescend(hmmioIn, pckInRIFF, NULL, 0)) != 0)
		{
		goto ERROR_READING_WAVE;
		}


	if ((pckInRIFF->ckid != FOURCC_RIFF) || (pckInRIFF->fccType != mmioFOURCC('W', 'A', 'V', 'E')))
		{
		nError = ER_NOTWAVEFILE;
		goto ERROR_READING_WAVE;
		}
			
	/* Search the input file for for the 'fmt ' chunk.     */
    ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
    if ((nError = (int)mmioDescend(hmmioIn, &ckIn, pckInRIFF, MMIO_FINDCHUNK)) != 0)
		{
		goto ERROR_READING_WAVE;                
		}
					
	/* Expect the 'fmt' chunk to be at least as large as <PCMWAVEFORMAT>;
    * if there are extra parameters at the end, we'll ignore them */
    
    if (ckIn.cksize < (long) sizeof(PCMWAVEFORMAT))
		{
		nError = ER_NOTWAVEFILE;
		goto ERROR_READING_WAVE;
		}
															
	/* Read the 'fmt ' chunk into <pcmWaveFormat>.*/     
    if (mmioRead(hmmioIn, (HPSTR) &pcmWaveFormat, (long) sizeof(pcmWaveFormat)) != (long) sizeof(pcmWaveFormat))
		{
		nError = ER_CANNOTREAD;
		goto ERROR_READING_WAVE;
		}
							

	// Ok, allocate the waveformatex, but if its not pcm
	// format, read the next word, and thats how many extra
	// bytes to allocate.
	if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
		cbExtraAlloc = 0;                               
							
	else
		{
		// Read in length of extra bytes.
		if (mmioRead(hmmioIn, (LPSTR) &cbExtraAlloc,
			(long) sizeof(cbExtraAlloc)) != (long) sizeof(cbExtraAlloc))
			{
			nError = ER_CANNOTREAD;
			goto ERROR_READING_WAVE;
			}

		}
							
	// Ok, now allocate that waveformatex structure.
	if ((*ppwfxInfo = GlobalAlloc(GMEM_FIXED, sizeof(WAVEFORMATEX)+cbExtraAlloc)) == NULL)
		{
		nError = ER_MEM;
		goto ERROR_READING_WAVE;
		}

	// Copy the bytes from the pcm structure to the waveformatex structure
	memcpy(*ppwfxInfo, &pcmWaveFormat, sizeof(pcmWaveFormat));
	(*ppwfxInfo)->cbSize = cbExtraAlloc;

	// Now, read those extra bytes into the structure, if cbExtraAlloc != 0.
	if (cbExtraAlloc != 0)
		{
		if (mmioRead(hmmioIn, (LPSTR) (((BYTE*)&((*ppwfxInfo)->cbSize))+sizeof(cbExtraAlloc)),
			(long) (cbExtraAlloc)) != (long) (cbExtraAlloc))
			{
			nError = ER_NOTWAVEFILE;
			goto ERROR_READING_WAVE;
			}
		}

	/* Ascend the input file out of the 'fmt ' chunk. */                                                            
	if ((nError = mmioAscend(hmmioIn, &ckIn, 0)) != 0)
		{
		goto ERROR_READING_WAVE;

		}
	

	goto TEMPCLEANUP;               

ERROR_READING_WAVE:
	if (*ppwfxInfo != NULL)
		{
		GlobalFree(*ppwfxInfo);
		*ppwfxInfo = NULL;
		}               

	if (hmmioIn != NULL)
	{
	mmioClose(hmmioIn, 0);
		hmmioIn = NULL;
		}
	
TEMPCLEANUP:
	*phmmioIn = hmmioIn;

	return(nError);

}

/*      This routine has to be called before WaveReadFile as it searchs for the chunk to descend into for
	reading, that is, the 'data' chunk.  For simplicity, this used to be in the open routine, but was
	taken out and moved to a separate routine so there was more control on the chunks that are before
	the data chunk, such as 'fact', etc... */

int WaveStartDataRead(
					HMMIO *phmmioIn,
					MMCKINFO *pckIn,
					MMCKINFO *pckInRIFF
					)
{
	int                     nError;

	nError = 0;
	
	// Do a nice little seek...
	if ((nError = mmioSeek(*phmmioIn, pckInRIFF->dwDataOffset + sizeof(FOURCC), SEEK_SET)) == -1)
		{
			nError = 1;
		}

	nError = 0;
	//      Search the input file for for the 'data' chunk.
	pckIn->ckid = mmioFOURCC('d', 'a', 't', 'a');
	if ((nError = mmioDescend(*phmmioIn, pckIn, pckInRIFF, MMIO_FINDCHUNK)) != 0)
		{
		goto ERROR_READING_WAVE;
		}

	goto CLEANUP;

ERROR_READING_WAVE:

CLEANUP:        
	return(nError);
}


/*      This will read wave data from the wave file.  Makre sure we're descended into
	the data chunk, else this will fail bigtime!
	hmmioIn         - Handle to mmio.
	cbRead          - # of bytes to read.   
	pbDest          - Destination buffer to put bytes.
	cbActualRead- # of bytes actually read.

		

*/


int WaveReadFile(
		HMMIO hmmioIn,                          // IN
		UINT cbRead,                            // IN           
		BYTE *pbDest,                           // IN
		MMCKINFO *pckIn,                        // IN.
		UINT *cbActualRead                      // OUT.
		
		)
{

	MMIOINFO    mmioinfoIn;         // current status of <hmmioIn>
	int                     nError;
	UINT            cT, cbDataIn;

	nError = 0;

	if (nError = mmioGetInfo(hmmioIn, &mmioinfoIn, 0) != 0)
		{
		goto ERROR_CANNOT_READ;
		}
				
	cbDataIn = cbRead;
	if (cbDataIn > pckIn->cksize) 
		cbDataIn = pckIn->cksize;       

	pckIn->cksize -= cbDataIn;
	
	for (cT = 0; cT < cbDataIn; cT++)
		{
		/* Copy the bytes from the io to the buffer. */
		if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
			{
	    if ((nError = mmioAdvance(hmmioIn, &mmioinfoIn, MMIO_READ)) != 0)
				{
		goto ERROR_CANNOT_READ;
				} 
	    if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
				{
				nError = ER_CORRUPTWAVEFILE;
		goto ERROR_CANNOT_READ;
				}
			}
			
		// Actual copy.
		*((BYTE*)pbDest+cT) = *((BYTE*)mmioinfoIn.pchNext)++;                                                                                                   
		}

	if ((nError = mmioSetInfo(hmmioIn, &mmioinfoIn, 0)) != 0)
		{
		goto ERROR_CANNOT_READ;
		}

	*cbActualRead = cbDataIn;
	goto FINISHED_READING;

ERROR_CANNOT_READ:
	*cbActualRead = 0;

FINISHED_READING:
	return(nError);

}

/*      This will close the wave file openned with WaveOpenFile.  
	phmmioIn - Pointer to the handle to input MMIO.
	ppwfxSrc - Pointer to pointer to WaveFormatEx structure.

	Returns 0 if successful, non-zero if there was a warning.

*/
int WaveCloseReadFile(
			HMMIO *phmmio,                                  // IN
			WAVEFORMATEX **ppwfxSrc                 // IN
			)
{

	if (*ppwfxSrc != NULL)
		{
		GlobalFree(*ppwfxSrc);
		*ppwfxSrc = NULL;
		}

	if (*phmmio != NULL)
		{
		mmioClose(*phmmio, 0);
		*phmmio = NULL;
		}

	return(0);

}


BOOL Restart_CDTrack(long track)
{
	char buff[100];

//	if(cdDisable)
//		return FALSE;

	track++;
	wsprintf(buff,"play cdaudio from %i",track);
	mciErr = mciSendString(buff, mciReturn,MCI_RETURN_SIZE, NULL);
	if(mciErr) goto err;

	return TRUE;
err:
//	cdDisable=1;
	ReportCDError();
	return FALSE;
}

static BOOL Status_CDTrack(long track)
{
	char buff[100];

//	if(cdDisable)
//		return TRUE;
	track++;

	sprintf(buff, "status cdaudio mode");
	mciErr = mciSendString(buff, (LPTSTR )mciReturn, MCI_RETURN_SIZE, NULL);
	if(!stricmp(mciReturn,"stopped")) goto err;

	sprintf(buff, "status cdaudio current track");
	mciErr = mciSendString(buff, (LPTSTR )mciReturn, MCI_RETURN_SIZE, NULL);
	if(atoi(mciReturn)>track) goto err;

	return TRUE;
err:
//	cdDisable=1;
	ReportCDError();
	return FALSE;
}


static BOOL Play_CDTrack(long track)
{
//	if(cdDisable)
//		return FALSE;

	mciErr = mciSendString("open cdaudio", mciReturn,MCI_RETURN_SIZE, NULL);
	if(mciErr) goto err;

	mciErr = mciSendString("set cdaudio time format tmsf", mciReturn,MCI_RETURN_SIZE, NULL);
	if(mciErr) goto err;

	Restart_CDTrack(track);
	if(mciErr) goto err;

	return TRUE;

err:
//	cdDisable=1;
	ReportCDError();

	return FALSE;

}

BOOL Stop_CDTrack(void)
{
//	if(cdDisable)
//		return FALSE;

	mciErr = mciSendString("stop cdaudio", mciReturn, 
		MCI_RETURN_SIZE, NULL);
	if(mciErr) goto err;

	mciErr = mciSendString("close cdaudio", mciReturn, 
		MCI_RETURN_SIZE, NULL);
	if(mciErr) goto err;
	return TRUE;

err:
//	cdDisable=1;
	ReportCDError();
	return FALSE;
}

char dserr[100];

static char *dsError(HRESULT hr)
{
    switch (hr) 
    { 
        case DSERR_ALLOCATED : sprintf(dserr, "DSERR_ALLOCATED"); break; 
        case DSERR_CONTROLUNAVAIL : sprintf(dserr, "DSERR_CONTROLUNAVAIL"); break; 
        case DSERR_INVALIDPARAM : sprintf(dserr, "DSERR_INVALIDPARAM"); break; 
        case DSERR_INVALIDCALL : sprintf(dserr, "DSERR_INVALIDCALL"); break; 
        case DSERR_GENERIC : sprintf(dserr, "DSERR_GENERIC"); break; 
        case DSERR_PRIOLEVELNEEDED : sprintf(dserr, "DSERR_PRIOLEVELNEEDED"); break; 
        case DSERR_OUTOFMEMORY : sprintf(dserr, "DSERR_OUTOFMEMORY"); break; 
        case DSERR_BADFORMAT : sprintf(dserr, "DSERR_BADFORMAT"); break; 
        case DSERR_UNSUPPORTED : sprintf(dserr, "DSERR_UNSUPPORTED"); break; 
        case DSERR_NODRIVER : sprintf(dserr, "DSERR_NODRIVER"); break; 
        case DSERR_ALREADYINITIALIZED : sprintf(dserr, "DSERR_ALREADYINITIALIZED"); break; 
        case DSERR_NOAGGREGATION : sprintf(dserr, "DSERR_NOAGGREGATION"); break; 
        case DSERR_BUFFERLOST : sprintf(dserr, "DSERR_BUFFERLOST"); break; 
        case DSERR_OTHERAPPHASPRIO : sprintf(dserr, "DSERR_OTHERAPPHASPRIO"); break; 
        case DSERR_UNINITIALIZED : sprintf(dserr, "DSERR_UNINITIALIZED"); break; 
 
        default : sprintf(dserr, "Unknown Error"); break; 
    } 

	return dserr;
}
