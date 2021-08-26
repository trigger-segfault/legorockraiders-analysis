//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Main File For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

// Include all Header Files

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
#include	"libgods.h"
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
int loopCount;


/************************************************************************************************************************************************
		Define up some cool data cache based variables based on 68k registers
************************************************************************************************************************************************/
int d0 __attribute__ ((section("cachedata"))) = 0;
int d1 __attribute__ ((section("cachedata"))) = 0;
int d2 __attribute__ ((section("cachedata"))) = 0;
int d3 __attribute__ ((section("cachedata"))) = 0;
int d4 __attribute__ ((section("cachedata"))) = 0;
int d5 __attribute__ ((section("cachedata"))) = 0;
int d6 __attribute__ ((section("cachedata"))) = 0;
int d7 __attribute__ ((section("cachedata"))) = 0;

long a0 __attribute__ ((section("cachedata"))) = 0;
long a1 __attribute__ ((section("cachedata"))) = 0;
long a2 __attribute__ ((section("cachedata"))) = 0;
long a3 __attribute__ ((section("cachedata"))) = 0;
long a4 __attribute__ ((section("cachedata"))) = 0;
long a5 __attribute__ ((section("cachedata"))) = 0;
long a6 __attribute__ ((section("cachedata"))) = 0;
long a7 __attribute__ ((section("cachedata"))) = 0;

CVECTOR Dcvec1 __attribute__ ((section("cachedata"))) = {0,0,0};
VECTOR Dvec1 __attribute__ ((section("cachedata"))) = {0,0,0};
VECTOR Dvec2 __attribute__ ((section("cachedata"))) = {0,0,0};
SVECTOR Dsvec1 __attribute__ ((section("cachedata"))) = {0,0,0};
SVECTOR Dsvec2 __attribute__ ((section("cachedata"))) = {0,0,0};


//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Functions Go Here
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

#ifndef	LINKED_NONE2
void		main( void )
#else
Sint32	main(Sint32 argc, Sint8 **argv)
#endif
{
	int i;
	BOOL	setup = FALSE;
///	printf ("START\n");
	// Required For Demo CDs
	#ifdef	LINKED_NONE2
	GameMode = ((Sint32*)argv)[0];
	TimeOut  = ((Sint32*)argv)[1];
	StartTrk = ((Sint32*)argv)[2];
	TrkCount = ((Sint32*)argv)[3];
	#endif

	Mem_Reset(0);
	ScreenOff();

	mainGlobs.active = FALSE;
	mainGlobs.exit = FALSE;
	mainGlobs.stateSet = FALSE;

// Initialise the PSX
	ResetCallback();

	ResetGraph(0);

//	Error_Initialise();
	Mem_Initialise();
	File_Initialise();

#ifdef	__CDVERSION
	set_load_flag(FROM_CD);
#else
	set_load_flag(FROM_PC);
#endif

	setup=TRUE;
//	printf ("Frontend loading\n");
//	Front_Loading();

	Sound_Initialise();


	if(Main_Initialise(setup))
	{
		// Call The application 
		Gods_Go();
//		Input_InitPad();-ADRIAN-

		Gfx_Initialise();
		Container2_Initialise();


		//Mem_Reset(1);
//		SetScreen(OFF);
//		Front_DoIntro();	// This goes here (after gfx_initialize) to avoid screen disturbance between intro & menu

//		SetScreen(ON);

		Sfx_Initialise();
		sfxGlobs.vh = Sfx_LoadSoundBank("TJ", NULL);
		printf("sfxGlobs.vh = 0x%x\n", sfxGlobs.vh);
	
/* removed for demo */
		loopCount=1;
		while(1)
		{	
//			printf(" ---------------------- LOOP %d ------------------------------\n",loopCount);
			loopCount++;
			//Mem_Reset(1);
			Font_Initialise();
//			Config_Initialise();
//			LANG_Initialise();



			if(mainGlobs.currState.FrontEnd)
			{
				mainGlobs.currState.FrontEnd();
			}

/* moved for demo */
			// If the game wants to run in state mode
			if(mainGlobs.stateSet)
			{
				if(mainGlobs.currState.Initialise)
				{
					mainGlobs.exit=FALSE;
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
						u_long pk;

//						printf ("loop\n");
						Gfx_StartDraw();
//						printf ("Done start draw");

						pk=((u_long)GsOUT_PACKET_P);						
		
						Main_HandleIO();
						//Input_ReadPad(-1);-ADRIAN-
//						printf ("Done IO\n");

						if(mainGlobs.currState.MainLoop(time))
							mainGlobs.exit=TRUE;
						
//						printf ("Finished Main function\n");
						pk=((u_long)GsOUT_PACKET_P) - pk;
//						printf ("%d\n",pk);
						if (pk>gfxGlobs.packetMax) 
							printf("WARNING: Packet buffer overflow! Increase packet buffer size\n");

						Gfx_ScreenFlip();
//						printf ("Flipped Screen\n");
						mainGlobs.flags &= ~MAIN_FLAG_UPDATED;
					}
				}

				if(mainGlobs.currState.Shutdown)
				{
					//Gfx_ShutDown();
					mainGlobs.currState.Shutdown();
//					printf ("MyShutdown\n");
				}
			}

			Container_Shutdown();
//			printf ("Container Shutdown\n");
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
