//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Sound.c - [Sound Code]
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#define SAMP_MULTI 2
#define SAMP_LOOP 1
#define SAMP_ONCE 0

enum
{
	Sound_Multi = SAMP_MULTI,
	Sound_Loop = SAMP_LOOP,
	Sound_Once = SAMP_ONCE
};

typedef struct Sound
{
	ULONG handle;

} Sound, *lpSound;


typedef struct Sound_Globs
{
	ULONG		useSound, vabID;
	BOOL		initialised, enableCDMusic, loopCDTrack;
	Uint8		vol, trackPlaying, lastTrack;
	CdlLOC		trackPositions[20];
} Sound_Globs, *lpSound_Globs;

extern Sound_Globs soundGlobs;

void	Sound_Initialise(void);
void	Sound_Play(Uint8 sound, ULONG mode);
BOOL	Sound_PlayCDTrack(ULONG track, ULONG mode);
BOOL	Sound_StopCD(VOID);
BOOL	Play_CDTrack(Uint32 track);
BOOL	Stop_CDTrack(void);
void	Sound_Update(BOOL cdtrack);
long	Sound_PlayProgram(u_char vabId, u_char programId, u_char note, u_char fine, u_char leftVol, u_char rightVol);
long	Sound_StopProgram(u_char vabId, u_char programId, u_char note, u_char fine);
long	Sound_StopProgramVoices(long voices);


// ************************************************************************************************************
// ************************************************************************************************************
// ************************************************************************************************************
// ************************************************************************************************************
// ************************************************************************************************************
// ************************************************************************************************************