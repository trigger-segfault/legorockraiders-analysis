// ****************************************************************************************************
// Main Header File For <LEGO Rock Raiders>
//
// Started:	10-07-98
// Coding:	Glenn Benson
// ****************************************************************************************************

#ifndef	__SFX_H


// ****************************************************************************************************
#define SFX_ENABLED			0x00000001
#define SFX_RegisterName(n)	(sfxNames[n]=#n)


// ****************************************************************************************************
enum
{
	SFX_SAMPLE_TELEPORT				= 0,
	SFX_SAMPLE_LASER_GUN_FIRE		= 1,
	

	SFX_SAMPLE_MAX_SAMPLES,
};


// ****************************************************************************************************
typedef struct SFX_Globs
{
	long	vab;
	char	*vh;
	ULONG 	flags;

} SFX_Globs, *lpSFX_Globs;

extern SFX_Globs sfxGlobs;


// ****************************************************************************************************
void	Sfx_Initialise(void);															

void*	Sfx_LoadSoundBank(char *bankName, char *vh);									

long	Sfx_SoundBankInit(unsigned char *vh, unsigned char *vb);						

int		Sfx_PlayEffect(int sfx,int freq, int volume);

int		Sfx_PlayEffectPan(int	sfx,int freq, int left, int right);

int		Sfx_StopEffect(int voice);

void	Sfx_ChangePitch(int	voice, int sampleNum, int oldFrequency, int newFrequency);

BOOL	Sfx_ReleaseSoundBank(void *vh);

void	Sfx_ChangeVolume(int voice, int volume);

void	Sfx_StopAllEffects(void);

void	Sfx_LowerVolume(int voice);

// ****************************************************************************************************
// ****************************************************************************************************
// ****************************************************************************************************
// ****************************************************************************************************


#define	__SFX_H
#endif




