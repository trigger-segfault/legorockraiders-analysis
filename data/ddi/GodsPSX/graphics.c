//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Draw File For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#define USE_PROFILER

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
	int		n, size;
	lpGsOT_TAG zSort;

	Gfx_Display(OFF);
	VSync(0);
	// Turned screen off and changed to partial reset to avoid screen disturbance	-ADRIAN-
	ResetGraph(3);

	gfxGlobs.flags |= GFX_FLAG_INITIALISED;
	gfxGlobs.otSize = 1<<gfxGlobs.otLength;
	gfxGlobs.outPacket[0]=(lpPACKET)Mem_Alloc(gfxGlobs.packetMax*sizeof(PACKET));
	gfxGlobs.outPacket[1]=(lpPACKET)Mem_Alloc(gfxGlobs.packetMax*sizeof(PACKET));


/* create double buffered order tables for each viewport */
	size = gfxGlobs.otSize*sizeof(GsOT_TAG);
	for (n=0; n<MAX_VIEWPORTS; n++)
	{
		zSort = (lpGsOT_TAG)Mem_Alloc(size);
		if(!zSort)
			printf("memory alloc failed size %d\n",size);
		gfxGlobs.zSortTable[(0*MAX_VIEWPORTS)+n]=zSort;
		zSort = (lpGsOT_TAG)Mem_Alloc(size);
		if(!zSort)
			printf("memory alloc failed size %d\n",size);
		gfxGlobs.zSortTable[(1*MAX_VIEWPORTS)+n]=zSort;
		gfxGlobs.Wot[(0*MAX_VIEWPORTS)+n].length = gfxGlobs.otLength;
		gfxGlobs.Wot[(1*MAX_VIEWPORTS)+n].length = gfxGlobs.otLength;
		gfxGlobs.Wot[(0*MAX_VIEWPORTS)+n].org = gfxGlobs.zSortTable[(0*MAX_VIEWPORTS)+n];
		gfxGlobs.Wot[(1*MAX_VIEWPORTS)+n].org = gfxGlobs.zSortTable[(1*MAX_VIEWPORTS)+n];
	}

	GsInitGraph(gfxGlobs.scrW, gfxGlobs.scrH, 4|16|32, NULL, NULL);		/* 3rd param was NULL */
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
// Variable colour screen clear added by julian
	gfxGlobs.RedClear = gfxGlobs.BlueClear = gfxGlobs.GreenClear = 0;

}

void	Gfx_ClearVRAM( void )
{
	// Much nicer clear -ADRIAN-
	RECT rect;
	
	rect.x=0, rect.y=0, rect.w=1024, rect.h=256;
	ClearImage(&rect,0,0,0);
	rect.x=0, rect.y=256, rect.w=1024, rect.h=256;
	ClearImage(&rect,0,0,0);
	DrawSync(0);

/*	RECT		rect;
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
	RELEASE(blank);*/
}

void	Gfx_ShutDown(void)
{
	int n;
	
	Mem_Free(gfxGlobs.outPacket[0]);
	Mem_Free(gfxGlobs.outPacket[1]);
	
	for (n=0; n<MAX_VIEWPORTS; n++)
	{
		Mem_Free(gfxGlobs.zSortTable[(0*MAX_VIEWPORTS)+n]);
		Mem_Free(gfxGlobs.zSortTable[(1*MAX_VIEWPORTS)+n]);
	}
}

void	Gfx_StartDraw( void )
{
	int		n;

	gfxGlobs.bufID = GsGetActiveBuff();
	GsSetWorkBase((PACKET*)gfxGlobs.outPacket[gfxGlobs.bufID]);
	gfxGlobs.bufID*=MAX_VIEWPORTS;
/* re-initialise order tables */
	for (n=0; n<MAX_VIEWPORTS; n++)
	{
		GsClearOt(0, MAX_VIEWPORTS-n, &gfxGlobs.Wot[gfxGlobs.bufID+n]);
	}
//	DrawSync(0);

}

void	Gfx_ScreenFlip( void )
{
	int		base_buffer_id=GsGetActiveBuff()*MAX_VIEWPORTS;
	int		n;
Uint32 	 	*ot=(Uint32*)gfxGlobs.Wot[gfxGlobs.bufID].org;


	gfxGlobs.game_frames++;
#ifdef USE_PROFILER
	ProfileReadCount();	  			/* for CPU time bar */
	ProfileAddOT( ot+1 );		/* adds top bar to screen */
#endif

	DrawSync(0);

#ifdef USE_PROFILER
	ProfileAddDrawOT( ot+1 );/* adds bottom bar to screen */
#endif

	VSync(2);//gfxGlobs.frames);
//	ResetGraph(1);
	GsSwapDispBuff();
	Image_ResetQuadPool();

/* gfxGlobs.bufID will have changed if extra viewports are drawn, hence we must get the base again */

	if (gfxGlobs.flags & GFX_FLAG_CLEARSCREEN)
	{
//		printf ("Clearing");
		GsSortClear(gfxGlobs.RedClear, gfxGlobs.GreenClear, gfxGlobs.BlueClear, &gfxGlobs.Wot[base_buffer_id]);
	}
/* now we must check for used viewports and combine*/
	//for (n=1; n<MAX_VIEWPORTS; n++)
//	{
		/* don't know yet */

	//	GsSortOt(&gfxGlobs.Wot[base_buffer_id+n],&gfxGlobs.Wot[base_buffer_id]);
//	}

	GsDrawOt(&gfxGlobs.Wot[base_buffer_id]);
	FntFlush(-1);

#ifdef USE_PROFILER
	ProfileStartCount();		     
#endif

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
/****** THIS NEEDS CHANGING BECAUSE WE CAN'T USE INITPAD WITH PADINITDIRECT ******/
//		Input_PadRead(0);
	  	GsDefDispBuff(slidex,slidey,slidex,slidey);

//		if(Input_PadData(0) & PAD_LL) slidex=MAX(slidex-8, 0);
//		if(Input_PadData(0) & PAD_LR) slidex=MIN(slidex+8, 1024-320);

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

/********************************************************************
	A rather handy screen grabber -ADRIAN-
********************************************************************/
typedef	struct	_TGAHEAD
{
	Uint16	pp1;
	Uint16	BPP;
	Uint16	pp3;
	Uint16	pp4;
	Uint16	pp5;
	Uint16	pp6;
	Uint16	Width;
	Uint16	Height;
	Uint16	pp9;
} TGAHEAD;

TGAHEAD	TgaHeader=
{
	0x0000,
	0x0002,
	0x0000,
	0x0000,
	0x0000,
	0x0000,
	384,
	256,
	16
};

#define	RGB16(r, g, b)		(b<<10)|(g<<5)|(r)

void Gfx_GrabScreen(void)
{
	static	Uint16	saves =0;
	char		name[256];
	Sint32	handle;
	Uint32	i, y;
	Uint16	*addr, *buf, *line, r, g, b, c;
	RECT		rect;

	setRECT(&rect, 0, 0, 384, 1);

	sprintf(name,"%s\\RR%04d.TGA",_DEBUGPATH, saves++);

	addr = Mem_Malloc(384*2);
	buf = Mem_Malloc(384*2);
	
	DrawSync(0);

	if((handle = PCcreat(name, NULL))<0)
	{
		return;
	}

	PCwrite(handle, (char *)&TgaHeader, 18);

	for(y=0; y<256; y++)
	{
		rect.y=256-y;
		StoreImage2(&rect, (Uint32*)addr);
		line=addr;
		for(i=0; i<384; i++)
		{
			c=line[i];
			r=(c&31);
			g=(c&0x3e0)>>5;
			b=(c&0x7c00)>>10;
			buf[i]=RGB16(b, g, r);
		}
		PCwrite(handle, (char *)buf, 384*2);
	}


	RELEASE(addr);
	RELEASE(buf);

	PCclose(handle);
}
