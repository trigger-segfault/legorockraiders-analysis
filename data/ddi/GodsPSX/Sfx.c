// ****************************************************************************************************
// SFX File For <LEGO [Rock Raiders]>
//
// Started:	10-07-98
// Coding:	Glenn Benson
// Graphics:
// ****************************************************************************************************

#include	"libgods.h"


// ****************************************************************************************************

SFX_Globs sfxGlobs = {-1,0,0};


// a list of how many tones for each sfx - there should be a better way of doing this
short	tone_table[] =
{
	3,3,2,3,3,4,3,1,4,1,
	1,1,3,1,1,2,3,2,1,1,
	1,2,2,2,1,3,1,4,1,3,
	2,4,2,2,1,1,1,3,1,1,
	1,1,1,2,1,1,1,1,1,1,
	1,4,2,1,1,4,1,4,2,4,
	-1
};

// a list of which sfx are looped (0=non-looped, 1=looped, 2=looped but can be turned off)
char	loop_table[] =
{
	0,0,0,0,0,0,0,1,0,0,
	0,0,0,2,1,0,0,0,0,0,
	0,0,0,0,1,0,1,0,1,0,
	0,0,0,0,1,0,0,0,0,2,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,0,
	-1
};


// ****************************************************************************************************
// A simple caching system to keep track of sound channels, and solve all our sfx problems!!	-ADRIAN-
enum
{
	SFXCACHE_FREE,
	SFXCACHE_USED,
	SFXCACHE_LOOP,
	SFXCACHE_ALOOP	// available looping
};

typedef struct Sfx_CacheEntry_t
{
	int age;
	int	flag;
	int sfx;
}
Sfx_CacheEntry;

Sfx_CacheEntry Sfx_Cache[24];

// Clear the cache
// ****************************************************************************************************
void Sfx_ClearCache(void)
{
	int n;
	Sfx_CacheEntry *entry=Sfx_Cache;

	for (n=0;n<24;n++)
	{
		entry->flag=SFXCACHE_FREE;
		entry->age=0;
		entry->sfx=-1;
		entry++;
	}
}

// Try to find a free voice
// ****************************************************************************************************
int Sfx_GetVoice(int sfx)
{
int n,flag;
int score,v=0,max=0;
int loop=loop_table[sfx];
Sfx_CacheEntry *entry=Sfx_Cache;

	for (n=0;n<24;n++)
	{
		entry->age++;

		score=0;
		flag=entry->flag;

		if (flag == SFXCACHE_FREE)
			score+=0xFFFF;
		else if (flag == SFXCACHE_ALOOP)
			score+=entry->age;
		else if (flag == SFXCACHE_LOOP)
			score-=0xFFFF;
		else if (flag == SFXCACHE_USED)
			score+=entry->age + 0x7777;

		if (score>max) max=score,v=n;

		entry++;
	}

	entry=&Sfx_Cache[v];

	if (!loop) 
		entry->flag=SFXCACHE_USED;
	else if (loop==1)
		entry->flag=SFXCACHE_LOOP;
	else
		entry->flag=SFXCACHE_ALOOP;

	entry->age=1;
	entry->sfx=sfx;

return v;
}


// ****************************************************************************************************
void Sfx_FreeVoice(int v)
{
	Sfx_CacheEntry *entry;
	
	if ((v < 0) || (v > 23))		return;			// invalid voice
	
	entry=&Sfx_Cache[v];

	entry->flag=SFXCACHE_FREE;
	entry->age=0;
	entry->sfx=-1;
}


// ****************************************************************************************************
void	Sfx_Initialise(void)
{
	Sfx_ClearCache();
}


// ****************************************************************************************************
void	*Sfx_LoadSoundBank(char *bankName, char *vh)
{
ULONG					size;
unsigned char			*soundVH=NULL,*soundVB=NULL;
char					vbName[64],vhName[64];

	sprintf(vbName,"SFX\\%s.VB",bankName);
	sprintf(vhName,"SFX\\%s.VH",bankName);

	Sfx_ClearCache();

	sfxGlobs.vab = -1;

	soundVH =	File_LoadBinary(vhName, &size);
	soundVB	=	File_LoadBinary(vbName, &size);

	
	if ((soundVH) && (soundVB))
	{ 
		Sfx_SoundBankInit(soundVH,soundVB);
	}
	else
	{
		// sfx not available
		if(vh)						RELEASE(soundVH);
	}
	
	RELEASE(soundVB);
	
return	soundVH;
}

// ****************************************************************************************************
BOOL	Sfx_ReleaseSoundBank(void *vh)
{
	if(vh)		Mem_Free(vh);

	SsVabClose(sfxGlobs.vab);
	SsEnd();
}

// ****************************************************************************************************
long	Sfx_SoundBankInit(unsigned char *vh, unsigned char *vb)
{
int	retryCount = 0;



	do
	{
		printf("%d\n", retryCount);

		sfxGlobs.vab = SsVabTransfer (vh, vb, -1, SS_WAIT_COMPLETED);

		if(sfxGlobs.vab < 0)
		{
			printf("Failed to load VAB - retrying.\n");
		}
		else
		{
			printf("Loaded VAB - ID = %d\n", sfxGlobs.vab);
		}

		if(retryCount == 5)			return FALSE;

		retryCount++;
	}
	while(sfxGlobs.vab < 0);


	SsSetMVol(127,127);
	SsSetSerialAttr(SS_SERIAL_A, SS_MIX, SS_SON);

return TRUE;
}


// ****************************************************************************************************
int		Sfx_PlayEffect(int	sfx,int freq, int volume)
{
int l, v;
int	adjustedVolume;
  
	if (sfxGlobs.vab==-1)		
	{
		printf("no sfx loaded\n");
		return;		// no sfx loaded
	}


	/* Adjust the volume in relation to global volume */
	//adjustedVolume = volume * commonData->sfxVolume;
	adjustedVolume = volume * 127;
	adjustedVolume /= 6;


	adjustedVolume = 127;

	v = -1;

	if (tone_table[sfx] != -1)
	{
		if (tone_table[sfx] == 1)
		{
  			return	SsUtKeyOnV(Sfx_GetVoice(sfx),sfxGlobs.vab, sfx, 0, freq, 0, adjustedVolume, adjustedVolume);
		}

		for (l = 0 ; l < tone_table[sfx] ; l++)
		{
			v = SsUtKeyOnV(Sfx_GetVoice(sfx),sfxGlobs.vab, sfx, l, freq, 0, adjustedVolume, adjustedVolume);
		}

		return v;		// return the last one
	}

return -1;
}


// ****************************************************************************************************
int		Sfx_PlayEffectPan(int sfx, int freq, int left, int right)
{
	if (sfxGlobs.vab==-1)		return;		// no sfx loaded


return	SsUtKeyOnV(Sfx_GetVoice(sfx),sfxGlobs.vab,sfx,0,freq,0,left,right);
}


// ****************************************************************************************************
int		Sfx_StopEffect(int	voice)
{
int l;

	if (sfxGlobs.vab==-1)		return;		// no sfx loaded

	Sfx_FreeVoice(voice);

return	SsUtKeyOffV(voice);
}


// ****************************************************************************************************
void	Sfx_ChangePitch(int	voice, int sampleNum, int oldFrequency, int newFrequency)
{
	if (sfxGlobs.vab==-1)		return;

	SsUtChangePitch(voice,0,sampleNum,oldFrequency,0,(newFrequency>>7),(newFrequency&127));
}


// ****************************************************************************************************
void	Sfx_ChangeVolume(int voice, int volume)
{
int	adjustedVolume;
	
	if (sfxGlobs.vab==-1)		return;		// no sfx loaded 

	// Adjust the volume in relation to global volume 
	//adjustedVolume = volume * commonData->sfxVolume;
	adjustedVolume = volume * 127;
	adjustedVolume /= 6;


	SsUtSetVVol(voice, adjustedVolume, adjustedVolume);
}


// ****************************************************************************************************
void	Sfx_LowerVolume(int voice)
{
short left_volume, right_volume;

	if (sfxGlobs.vab==-1)		return;		// no sfx loaded 
	if (voice == -1)			return;		// invalid voice

	left_volume = right_volume = 0;

	SsUtGetVVol(voice, &left_volume, &right_volume);

	left_volume-=10;						// reduce the volume
	right_volume-=10;						// could pass this through as a parameter


	if (left_volume < 0) left_volume = 0;
	if (right_volume < 0) right_volume = 0;

	SsUtSetVVol(voice, left_volume, right_volume);
}


// ****************************************************************************************************
void	Sfx_StopAllEffects(void)
{
int		n;

	if (sfxGlobs.vab == -1)	return;		// no sfx loaded


	for (n = 0 ; n < 24 ; n++)
	{
		Sfx_FreeVoice(n);
		SsUtKeyOffV(n);
	}
}


// ****************************************************************************************************
void	Sfx_SetReverb(int depth)
{
/*
	SpuReverbAttr attr;

	attr.mask=SPU_REV_DEPTHL | SPU_REV_DEPTHR;
	attr.depth.left=depth;
	attr.depth.right=depth;
	SpuSetReverbDepth(&attr);
*/
}






















