// ****************************************************************************************************
// Sound File For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
// ****************************************************************************************************

// Include all Header Files

// ****************************************************************************************************
#include	"libgods.h"
// ****************************************************************************************************

Sound_Globs soundGlobs;



// ****************************************************************************************************
void	Sound_Initialise(void)
{
	soundGlobs.useSound = FALSE;
	soundGlobs.initialised = TRUE;
	soundGlobs.loopCDTrack = NULL;
	soundGlobs.vol = 127;

	SsInit();											// RESET SOUND SYSTEM AND CLEAR MEMORY
	SsSetTickMode(SS_TICKVSYNC);							// SET TICK MODE = NOTICK, USER VBL UPDATE
	SsStart();											// START SOUND
	SsSetMVol(soundGlobs.vol,soundGlobs.vol);			// SET MAIN VOLUME
}


// ****************************************************************************************************
BOOL Sound_PlayCDTrack(ULONG track, ULONG mode)
{
	if (soundGlobs.initialised)
	{
		if (Sound_Loop == mode) soundGlobs.loopCDTrack = track;
		return Play_CDTrack(track);
	}

return FALSE;
}

// ****************************************************************************************************
BOOL Sound_StopCD(VOID)
{
	if (soundGlobs.initialised)
	{
		return Stop_CDTrack();
	}

return FALSE;
}

// ****************************************************************************************************
BOOL	Play_CDTrack(Uint32 track)
{
	if(!soundGlobs.enableCDMusic) return TRUE;

	if(track < 1) return FALSE;
	if(track > soundGlobs.lastTrack) track = soundGlobs.lastTrack;
	soundGlobs.trackPlaying = track;
	CdControl(CdlPlay, (LPUCHAR) &soundGlobs.trackPositions[track], NULL);

return TRUE;
}

// ****************************************************************************************************
BOOL	Stop_CDTrack(void)
{
	if(!soundGlobs.trackPlaying) return TRUE;

	CdControl(CdlPause, NULL, NULL);
	soundGlobs.trackPlaying = NULL;

return TRUE;
}


// ****************************************************************************************************
// ****************************************************************************************************
// ****************************************************************************************************
// ****************************************************************************************************
// ****************************************************************************************************
// ****************************************************************************************************
// ****************************************************************************************************
