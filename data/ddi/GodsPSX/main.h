//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Main.c - [Startup Code]
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#define MAIN_FLAG_UPDATED		0x00000001

typedef struct Main_State
{
	BOOL			(*FrontEnd)(void);
	BOOL			(*Initialise)(void);
	BOOL			(*MainLoop)(REAL elapsedTime);
	void			(*Shutdown)(void);
} Main_State, *lpMain_State;

typedef struct Main_Globs
{
	BOOL			active, exit;
	Main_State	currState;
	BOOL			stateSet;
	ULONG			flags;
} Main_Globs, *lpMain_Globs;

ext	Main_Globs	mainGlobs;



#ifndef	LINKED_NONE2
void		main( void );
#else
Sint32	main(Sint32 argc, Sint8 **argv);
#endif

void	Main_Finalise3D( void );
BOOL	Main_SetState(lpMain_State state);
void	Main_HandleIO(void);
void	Main_SetEnvironment( Uint16 w, Uint16 h, Uint16 x, Uint16 y, Uint16 f, Uint16 l, Uint16 v, Uint32 p);
BOOL	Main_Initialise(BOOL setup);

REAL	timeGetTime(void);
