//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// SFX File For <LEGO [Rock Raiders]>
//
// Started:	10-07-98
// Coding:	Glenn Benson
// Graphics:
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Include all Header Files
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
#include	"globals.h"


SFX_Globs sfxGlobs = {-1,0};



VOID SFX_Initialise(VOID)
{
}


/*
	loads a .vh/.vb pair to sound ram
*/
BOOL	Sfx_LoadSoundBank(char *bankName)
{
	ULONG					size;
	unsigned char		*soundVH,*soundVB;
	char					vbName[64],vhName[64];
	
	sprintf(vbName,"SFX\\%s.VB",bankName);
	sprintf(vhName,"SFX\\%s.VH",bankName);

	soundVH=File_LoadBinary(vhName, &size);
	soundVB=File_LoadBinary(vbName, &size);

	sfxGlobs.vab=-1;

	if (soundVH && soundVB)
	{ 
		Sfx_SoundBankInit(soundVH,soundVB);
	}
	else
	{
		/* sfx not available */

		RELEASE(soundVH);
		RELEASE(soundVB);
	}

	if (sfxGlobs.vab!=-1)
		return	TRUE;

	return	FALSE;		/* some sort of failure */
}


/*
	initialise the sound bank
*/
long	Sfx_SoundBankInit(unsigned char *vh, unsigned char *vb)
{
	SsInit();
	SsSetTickMode(SS_TICK50);
	//SsSetTickMode(SS_NOTICK);

	sfxGlobs.vab=SsVabOpenHead(vh,-1);
	if (sfxGlobs.vab<0)
	{
		return FALSE;
	}

	if (SsVabTransBody(vb,sfxGlobs.vab)!=sfxGlobs.vab)
	{
		return FALSE;
	}

	SsStart();
	SsSetMVol(127,127);
	SsSetSerialAttr(SS_SERIAL_A, SS_MIX, SS_SON);

	return TRUE;
}



/*
	play a mono sound effect at the passed frequency and volume
	return the voice used to play the effect
*/
int	Sfx_PlayEffect(int	sfx,int freq, int volume)
{
	if (sfxGlobs.vab==-1)
		return;		/* no sfx loaded */

	return	SsUtKeyOn(sfxGlobs.vab,sfx,0,freq,0,volume,volume);

}
/*
	play a mono sound effect at the passed frequency and volume
	return the voice used to play the effect
	separate volume levels for left/right
*/
int	Sfx_PlayEffectPan(int	sfx,int freq, int left, int right)
{
	if (sfxGlobs.vab==-1)
		return;		/* no sfx loaded */

	return	SsUtKeyOn(sfxGlobs.vab,sfx,0,freq,0,left,right);

}


/*
	stop a sound effect playing on the passed voice
*/
int	Sfx_StopEffect(int	voice)
{
	if (sfxGlobs.vab==-1)
		return;		/* no sfx loaded */

	return	SsUtKeyOffV(voice);

}


/*
	weird way of changing the pitch. Why the old frequency?
*/
void	Sfx_ChangePitch(int	voice, int sampleNum, int oldFrequency, int newFrequency)
{
	SsUtChangePitch(voice,0,sampleNum,oldFrequency,0,(newFrequency>>7),(newFrequency&127));
}



























BOOL SFX_FindSFXID(LPUCHAR name, LPULONG id)
{
	return TRUE;
}

VOID SFX_LoadSamples(LPUCHAR fname, ULONG type, ...)
{
}

VOID SFX_PlaySample(ULONG sample, ULONG mode)
{
	if (sfxGlobs.flags & SFX_ENABLED)
		{
		Sound_Play(sample, mode);
		}
}

VOID SFX_StopSample(ULONG sample)
{
}

VOID SFX_Enable(BOOL enable)
{
}

									   
