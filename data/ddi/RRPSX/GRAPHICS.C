//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Draw File For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹



/* SteveD:
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

	added support for multiple order tables,
	since we must have a separate OT for each
	viewport.

//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
*/


// Include all Header Files

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
#include	"libgods.h"
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

Gfx_Globs	gfxGlobs;

void	Gfx_Initialise(void)
{
	int		n;

//	Gfx_Display(OFF);
	VSync(0);
	ResetGraph(NULL);

	gfxGlobs.flags |= GFX_FLAG_INITIALISED;
	gfxGlobs.otSize = 1<<gfxGlobs.otLength;
	gfxGlobs.outPacket[0]=(lpPACKET)Mem_Alloc(gfxGlobs.packetMax*sizeof(PACKET));
	gfxGlobs.outPacket[1]=(lpPACKET)Mem_Alloc(gfxGlobs.packetMax*sizeof(PACKET));


/* create double buffered order tables for each viewport */

	for (n=0; n<MAX_VIEWPORTS; n++)
	{
		gfxGlobs.zSortTable[(0*MAX_VIEWPORTS)+n]=(lpGsOT_TAG)Mem_Alloc(gfxGlobs.otSize*sizeof(GsOT_TAG));
		gfxGlobs.zSortTable[(1*MAX_VIEWPORTS)+n]=(lpGsOT_TAG)Mem_Alloc(gfxGlobs.otSize*sizeof(GsOT_TAG));
		gfxGlobs.Wot[(0*MAX_VIEWPORTS)+n].length = gfxGlobs.otLength;
		gfxGlobs.Wot[(1*MAX_VIEWPORTS)+n].length = gfxGlobs.otLength;
		gfxGlobs.Wot[(0*MAX_VIEWPORTS)+n].org = gfxGlobs.zSortTable[(0*MAX_VIEWPORTS)+n];
		gfxGlobs.Wot[(1*MAX_VIEWPORTS)+n].org = gfxGlobs.zSortTable[(1*MAX_VIEWPORTS)+n];
	}

	GsInitGraph(gfxGlobs.scrW, gfxGlobs.scrH, 4, NULL, NULL);		/* 3rd param was NULL */
	GsInit3D();
	GsDefDispBuff(NULL, NULL, NULL, gfxGlobs.scrH);
	GsDISPENV.screen.x=gfxGlobs.scrX;
	GsDISPENV.screen.y=gfxGlobs.scrY;
	GsDISPENV.screen.w=gfxGlobs.scrW;
	GsDISPENV.screen.h=gfxGlobs.scrH;
	gfxGlobs.bufID = NULL;
	gfxGlobs.fadeLevel = NULL;
	gfxGlobs.vblankCallback=NULL;
	gfxGlobs.vblankCallback2=NULL;
	Gfx_ClearVRAM();
//	Gfx_Display(ON);
}

void	Gfx_ClearVRAM( void )
{
	RECT		rect;
	Uint16	*blank, i;

	blank = (LPUWORD)Mem_Alloc(1024*2*32);
	memset((Uint8*)blank, 0, 1024*2*32);

	setRECT(&rect, 0, 0, 1024, 32);
	for(i=0; i<16; i++)
	{
		rect.y = i*32;
		LoadImage(&rect, (Uint32*)&blank[0]);
		DrawSync(0);
	}
	RELEASE(blank);
}

void	Gfx_StartDraw( void )
{
	int		n;

	gfxGlobs.bufID = GsGetActiveBuff();
	GsSetWorkBase((PACKET*)gfxGlobs.outPacket[gfxGlobs.bufID]);
	gfxGlobs.bufID*=MAX_VIEWPORTS;

/* re-initialise order tables */
	for (n=0; n<MAX_VIEWPORTS; n++)
		GsClearOt(0, MAX_VIEWPORTS-n, &gfxGlobs.Wot[gfxGlobs.bufID+n]);
//	DrawSync(0);

}

void	Gfx_ScreenFlip( void )
{
	int		base_buffer_id=GsGetActiveBuff()*MAX_VIEWPORTS;
	int		n;

	gfxGlobs.game_frames++;
	DrawSync(0);
	VSync(gfxGlobs.frames);
	//ResetGraph(1);
	GsSwapDispBuff();
	Image_ResetQuadPool();

/* gfxGlobs.bufID will have changed if extra viewports are drawn, hence we must get the base again */

	if (gfxGlobs.flags & GFX_FLAG_CLEARSCREEN)
		GsSortClear(0, 0, 0, &gfxGlobs.Wot[base_buffer_id]);

/* now we must check for used viewports and combine*/
	for (n=1; n<MAX_VIEWPORTS; n++)
	{
		/* don't know yet */

		GsSortOt(&gfxGlobs.Wot[base_buffer_id+n],&gfxGlobs.Wot[base_buffer_id]);
	}
	GsDrawOt(&gfxGlobs.Wot[base_buffer_id]);
}

void	Gfx_ShowVRAM(void)
{
	Uint16	slidex,slidey;

	slidex=0;
	slidey=0;

	DrawSync(0);
	VSync(0);

	GsInitGraph(320,256,2,0,0);		/* SET THE MODE */
	//SetVideoMode(MODE_PAL);
	GsDISPENV.screen.x = 0;
	GsDISPENV.screen.w = 320;
	GsDISPENV.screen.y = 20;
	GsDISPENV.screen.h = 256;
	Gfx_Display(ON);
	while(1)
	{
		Input_PadRead(0);
	  	GsDefDispBuff(slidex,slidey,slidex,slidey);

		if(Input_PadData(0) & PAD_LL) slidex=MAX(slidex-8, 0);
		if(Input_PadData(0) & PAD_LR) slidex=MIN(slidex+8, 1024-320);

		VSync(0);					/* WAIT FOR VBLANK */
		GsSwapDispBuff();			/* EXCHANGE DISPLAY AND DRAWING BUFFER */
		ResetGraph(1);				/* RESET GPU */
	}
}



void	Gfx_SetClearScreenFlag(BOOL	value)
{
	if (value)
		gfxGlobs.flags |=	GFX_FLAG_CLEARSCREEN;
	else
		gfxGlobs.flags &=	~GFX_FLAG_CLEARSCREEN;
}


/*
	set up a vblank call back routine
*/
void Gfx_SetVBlankCallback(void (*Callback)(void))
{
	gfxGlobs.vblankCallback=Callback;
}


/*
	set up another vblank call back routine
*/
void Gfx_SetVBlankCallback2(void (*Callback)(void))
{
	gfxGlobs.vblankCallback2=Callback;
}
