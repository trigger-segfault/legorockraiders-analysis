//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Main File For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

// Include all Header Files

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
#include	"..\inc\libgods.h"
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

// Variables Defined Here
// Required By Demo CDs
#ifdef	LINKED_NONE2
Sint32	TimeOut,
			GameMode,
			StartTrk,
			TrkCount;
#endif


Main_Globs	mainGlobs;

ext	void			Gods_Go( void );
ext	Gfx_Globs	gfxGlobs;

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Functions Go Here
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

#ifndef	LINKED_NONE2
void		main( void )
#else
Sint32	main(Sint32 argc, Sint8 **argv)
#endif
{
	BOOL	setup = FALSE;

	// Required For Demo CDs
	#ifdef	LINKED_NONE2
	GameMode = ((Sint32*)argv)[0];
	TimeOut  = ((Sint32*)argv)[1];
	StartTrk = ((Sint32*)argv)[2];
	TrkCount = ((Sint32*)argv)[3];
	#endif

	ScreenOff();

	mainGlobs.active = FALSE;
	mainGlobs.exit = FALSE;
	mainGlobs.stateSet = FALSE;


	// Initialise the PSX
	ResetCallback();
//	Error_Initialise();
	Mem_Initialise();
	File_Initialise();
	Config_Initialise();
	Input_InitPad();

	setup=TRUE;

	Sound_Initialise();

	if(Main_Initialise(setup))
		{
		// Call The application 
		Gods_Go();

		// Initialise the drawing environment
		Gfx_Initialise();

		SetScreen(ON);

		// If the game wants to run in state mode
		if(mainGlobs.stateSet)
			{
			if(mainGlobs.currState.Initialise)
				{
				// Run the application initialisation code
				if(!mainGlobs.currState.Initialise())
					{
					// Initialisation Failed So Drop Out
					mainGlobs.currState.Initialise = NULL;
					mainGlobs.currState.MainLoop = NULL;
					mainGlobs.currState.Shutdown = NULL;
					}
				}


			// If a main loop is specified then run it until it returns false...
			if(mainGlobs.currState.MainLoop)
			{
				REAL	time=ONE;
				while(!mainGlobs.exit)
				{
					Gfx_StartDraw();

					Main_HandleIO();
					Input_ReadPad(-1);
//					Input_ReadMouse();

					if(!mainGlobs.currState.MainLoop(time))
						mainGlobs.exit=TRUE;

					Gfx_ScreenFlip();
					mainGlobs.flags &= ~MAIN_FLAG_UPDATED;
				}
			}

			if(mainGlobs.currState.Shutdown)
				mainGlobs.currState.Shutdown();
		}
	}
}


void	Main_LoopUpdate(BOOL clear)
{
	mainGlobs.flags &= ~MAIN_FLAG_UPDATED;
}

/* ? */
void	Main_Finalise3D( void )
{
/* what the hell was this supposed to do? */
}

BOOL	Main_SetState(lpMain_State state)
{
	if(state)
		{
		mainGlobs.currState = *state;
		mainGlobs.stateSet = TRUE;
		return TRUE;
		}
	return FALSE;
}

void	Main_HandleIO(void)
{
}



static void	gods_vblank(void)
{

/*
	calculate actual frame rate, so we can compare it to the
	fiction of the setup rate.
*/

	gfxGlobs.vblank_frames++;
	if (gfxGlobs.vblank_frames>=gfxGlobs.framesPerSecond)
	{
		gfxGlobs.last_fps=gfxGlobs.game_frames;
		gfxGlobs.vblank_frames=0;
		gfxGlobs.game_frames=0;
	}

/* application vblank callback */

	if (gfxGlobs.vblankCallback)
			gfxGlobs.vblankCallback();

	if (gfxGlobs.vblankCallback2)
			gfxGlobs.vblankCallback2();

}

void	Main_SetEnvironment( Uint16 w, Uint16 h, Uint16 x, Uint16 y, Uint16 f, Uint16 l, Uint16 v, Uint32 p)
{
	if(v==1) v=NULL;
	gfxGlobs.scrW = w;
	gfxGlobs.scrH = h;
	gfxGlobs.scrX = x;
	gfxGlobs.scrY = y;
	gfxGlobs.framesPerSecond = f;
	gfxGlobs.otLength = l;
	gfxGlobs.frames = v;
	gfxGlobs.packetMax = p;

	gfxGlobs.last_fps=0;
	gfxGlobs.game_frames=0;
	gfxGlobs.vblank_frames=0;

	VSyncCallback(gods_vblank);	

}

BOOL	Main_Initialise(BOOL setup)
{
	if(!setup) return TRUE;
	return TRUE;
}

REAL	timeGetTime(void)
{
	return ONE;
}
