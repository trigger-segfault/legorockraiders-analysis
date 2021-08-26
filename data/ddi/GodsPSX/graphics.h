//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Graphics.c - [Graphics Code]
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#define GFX_FLAG_INITIALISED		0x00000001
#define GFX_FLAG_CLEARSCREEN		0x00000002			/* if set we do a clear screen */

#define	Gfx_Display	SetDispMask

#define	MAX_VIEWPORTS	(1)

typedef	struct	Gfx_Globs
{
	Uint16		otSize;
	Uint16		frames;
	Uint16		framesPerSecond;
	GsOT			Wot[2*MAX_VIEWPORTS];
	lpGsOT_TAG	zSortTable[2*MAX_VIEWPORTS];
	lpPACKET		outPacket[2];
	Uint32		bufID;
	Uint32		fadeLevel;
	Uint16		scrW;
	Uint16		scrH;
	Uint16		scrX;
	Uint16		scrY;
	Uint16		otLength;
	Uint32		packetMax;
	Uint32		flags;
	Uint8		RedClear;
	Uint8		GreenClear;
	Uint8		BlueClear;

	void			(*vblankCallback)();
	void			(*vblankCallback2)();

	short			last_fps;
	short			game_frames;
	short			vblank_frames;

} Gfx_Globs, *lpGfx_Globs;

#define	Gfx_GetWidth()		gfxGlobs.scrW
#define	Gfx_GetHeight()	gfxGlobs.scrH


ext	Gfx_Globs	gfxGlobs;

void	Gfx_Initialise(void);
void	Gfx_ClearVRAM( void );
void	Gfx_StartDraw( void );
void	Gfx_ScreenFlip( void );
void	Gfx_SetClearScreenFlag(BOOL	value);
void Gfx_SetVBlankCallback(void (*Callback)(void));
