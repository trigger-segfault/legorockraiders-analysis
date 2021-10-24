//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Main File For <LEGO [Rock Raiders]>
//
// Started:	10-07-98
// Coding:	Glenn Benson
// Graphics:
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Include all Header Files
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
#include	"globals.h"



#define		RAINBOW_BLOCKS
//#define		UNEVEN_BLOCKS			/* not completely square */



extern	Viewport_Globs viewportGlobs;

void Surface_SetLightPoint(int mapX, int mapY, int lightScaleRed, int lightScaleGreen, int lightScaleBlue);


BOOL	Lego_LoadModMap(LPUCHAR modmap);
void	Lego_InitialiseLights(void);
void	Lego_MakeLandingPad(lpLego_Level level, int x, int y, int offset);





LPUCHAR		_DEBUGPATH = "D:\\LEGONEW";
//LPUCHAR		_DEBUGPATH = "C:\\LEGONEW";

Lego_Globs	legoGlobs;

lpContainer rockAnimCont, rockAnimCornerCont;
lpContainer boulderCont;
//lpSelectionBox selBox;

extern	short	mask_brightness;
extern	int	radar_toggle;

void	transform_test(void);

void	set_load_flag(int flag);
void set_alternate_path_flag(int flag);
void	draw_current_world(void);
void	new_demo_display();
void new_demo_update(void);
void	draw_selected(void);
void	Lego_ShowMask(void);
BOOL Lego_ProcessAltMap(lpLego_Level level, LPULONG surfMap);
VOID Lego_ProcessWaterLava(lpLego_Level level);


int	global_ret=99;

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Start the system and tell the GODS lib
// where the game functions are
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
void	Gods_Go(void)
{
	Main_State	state;

#ifdef	__CDVERSION
	set_load_flag(FROM_CD);
#else
	set_load_flag(FROM_PC);
#endif

	memset((Uint8*)&legoGlobs, NULL, sizeof(Lego_Globs));
	state.Initialise = Lego_Initialise;
	state.MainLoop = Lego_MainLoop;
	state.Shutdown = Lego_Shutdown;

#ifdef	__PAL		// sX   sY  oX oY FPS OTZ  F  PACKETBUFFER
	Main_SetEnvironment(384, 256, 0, 20, 50, 14, 2, 24*5000);
#else
	Main_SetEnvironment(384, 240, 8, 0, 60, 14, 2, 24*5000);
#endif

	legoGlobs.gameName="Lego007";

	Main_SetState(&state);

	Surface_initialiseWorldQuadList();
}



//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// This function is called from the GODS lib
// to initialise the game.
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
BOOL	Lego_Initialise(void)
{
	lpConfig	conf;
	REAL		maxDist, minDist, maxTilt, minTilt;
	char		levelID[64];

	Viewport_Initialise();
	Image_Initialise();
	TextWindow_Initialise();

	#ifdef	__PAL
	SetVideoMode(MODE_PAL);
	#endif

	/* this will have been set previously by the mode selector */

	legoGlobs.level=1;



	legoGlobs.stdFont = Font_Load("INTRFACE\\FONTS\\PSXFONT.TIM",0,8,10,10);
	{
		AREA2D area = { 8-(Gfx_GetWidth()>>1), 8-(Gfx_GetHeight()>>1), 224, 35 };
		legoGlobs.messageWin = TextWindow_Create(legoGlobs.stdFont, &area, 1024);
	}

#ifdef DEBUG_CONSOLE
	Console_InitialiseConsole(8,96);
#endif


	if(legoGlobs.rootCont = Container_Initialise(legoGlobs.gameName))
	{

		Camera_InitSmoothing();

#ifdef __PAL
		Loader_Initialise("INTRFACE\\LOADING.TIM", legoGlobs.stdFont);
#else
		Loader_Initialise("INTRFACE\\LOADNTSC.TIM", legoGlobs.stdFont);
#endif
		reset_file_total();
		Loader_Enable(TRUE);

		if (legoGlobs.mainView = Viewport_Create(0, 0, ONE, ONE, cameraSmooth.cont))
		{
			if (conf = legoGlobs.config = Config_Load(LEGO_CONFIG_FILENAME))
			{
				sprintf(levelID,"levels::level%d",legoGlobs.level);

				if (Lego_LoadLevel(levelID))
				{
					Sfx_LoadSoundBank("ROCK_R");
					legoGlobs.lastUpdate=0;
					legoGlobs.vblankCount=0;
					Steve_InitialiseGameData();
					Lego_InitialiseLights();
					Loader_Enable(FALSE);
					gfxGlobs.flags|=GFX_FLAG_CLEARSCREEN;
					Gfx_SetVBlankCallback(Control_serviceMainControlSet);

#ifdef DEBUG_CONSOLE
					Console_FlushConsole();
#endif
					return TRUE;
				}
				Config_Free(conf);
			}
		}
		Container_Shutdown();
	}
	Loader_Enable(FALSE);
	return FALSE;
}


//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// This function is called from the GODS lib

// to shut down the game.
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
void	Lego_Shutdown(void)
{
}



lpContainer Lego_GetCamera(VOID)
{
}





/*
	display various game stats
*/
void	displayStats(void)
{

#ifndef __CDVERSION

	char				string[64];

	sprintf(string, "%d", gfxGlobs.last_fps);
	Font_PrintF(legoGlobs.stdFont,8,8,string);

	sprintf(string, "m=%d s=%d", viewportGlobs.models_drawn,viewportGlobs.sprites_drawn);
	Font_PrintF(legoGlobs.stdFont,8,16,string);

#endif

}






/* test lighting */
void	Lego_InitialiseLights(void)
{
	GsF_LIGHT	light;

	static	int	lr=0xff,lg=0xff,lb=0xff;
	static	int	lvx=61440,lvy=100,lvz=-57344;
	static	int	ambient=2048;

	light.vx=lvx,light.vy=lvy,light.vz=lvz;
	light.r=lr,light.g=lg,light.b=lb;
	GsSetFlatLight(0,&light);
	GsSetLightMode(0);
	GsSetAmbient(ambient,ambient,ambient);
}



//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// This function is called from the GODS lib
// to actually run the game.
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
BOOL	Lego_MainLoop(REAL time)
{
	BOOL teleportMode, reinforceMode, addSelMode;
	Uint16	pad;


	{
		Viewport_Render(legoGlobs.mainView, legoGlobs.rootCont, time);
//---------------------------------------------------------------
		new_demo_update();
//---------------------------------------------------------------

		new_demo_display();

		displayStats();

		Surface_addPrimList();
	}

	Font_update_flash(legoGlobs.stdFont);
	Font_update_flash(legoGlobs.stdFont);



	return TRUE;
}























/*
	mask tim has been repositioned now, it was overlapping the font.
	should be split into 2 sprites per quarter, it would save draw time
*/
void	Lego_ShowMask(void)
{
	GsSPRITE	s;
	unsigned short	tpage=getTPage(1,2,768,256);

	if (mask_brightness==0)
		return;

	s.w = 192;
	s.h = 128;
	s.u = 0;
	s.v = 128;	//92;
	s.tpage=tpage;
	s.cx = 512;
	s.cy = 511;
	s.mx = s.my = s.rotate = NULL;
	s.scalex = s.scaley = ONE;

	s.r = s.g = s.b = mask_brightness;
	s.x = -192;
	s.y = -128;
	s.attribute = 0x61000000;
	GsSortFastSprite(&s, &gfxGlobs.Wot[gfxGlobs.bufID], 11);
	s.x = NULL;
	s.attribute = 0x61800000;
	GsSortSprite(&s, &gfxGlobs.Wot[gfxGlobs.bufID], 11);
	s.x = -192;
	s.y = NULL;
	s.attribute = 0x61400000;
	GsSortSprite(&s, &gfxGlobs.Wot[gfxGlobs.bufID], 11);
	s.x = NULL;
	s.attribute = 0x61c00000;
	GsSortSprite(&s, &gfxGlobs.Wot[gfxGlobs.bufID], 11);


}

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// All Setup Functions Here
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ






BOOL Lego_LoadLevel(LPUCHAR levelName)
{
	lpLego_Level 	level;
	lpConfig 		conf = legoGlobs.config;
	LPUCHAR 			textname;
	BOOL 				res = FALSE;
	char				levelPath[128];


	sprintf(legoGlobs.levelPath,"levels\\level%d\\",legoGlobs.level);
	
	if (level = Mem_Alloc(sizeof(Lego_Level)))
	{
		legoGlobs.currLevel = level;
		legoGlobs.flags |= LEGO_FLAG_RESETTIME;

		if (level->blockSize = Config_GetRealValue(conf, Config_BuildStringID(legoGlobs.gameName, levelName, "blocksize", NULL)))
		{
			if (level->digDepth = Config_GetRealValue(conf, Config_BuildStringID(legoGlobs.gameName, levelName, "digdepth", NULL)))
			{
				
				if (textname = Config_GetTempStringValue(conf, Config_BuildStringID(legoGlobs.gameName, levelName, "textureset", NULL)))
				{
					level->name = levelName;
					level->nextLevel = Config_GetStringValue(conf, Config_BuildStringID(legoGlobs.gameName, levelName, "nextlevel", NULL));
									
					if (Lego_LoadMapSet(level,textname))
						return	TRUE;
				}
			}
		}
		Mem_Free(level);
	}
	legoGlobs.currLevel = NULL;
	return FALSE;
}


/*
	slimmed down mapset loader
*/
BOOL Lego_LoadMapSet(lpLego_Level level, LPUCHAR textureset)
{
	ULONG 			x, y;
	LPULONG			surfMap;
	char				smap[64],pdmap[64],terrmap[64],modmap[64];
	

	sprintf(smap,"%saltmap.map",legoGlobs.levelPath);
	sprintf(pdmap,"%spredug.map",legoGlobs.levelPath);
	sprintf(terrmap,"%sterrain.map",legoGlobs.levelPath);
	sprintf(modmap,"%sterrain.mod",legoGlobs.levelPath);

	if (!(surfMap = File_LoadBinary(smap, NULL)))
		return	FALSE;

	if (level->map = Map3D_Create(legoGlobs.rootCont, surfMap, level->blockSize))
	{
		level->width = level->map->gridWidth;
		level->height = level->map->gridHeight;

		if (Lego_LoadTextureSet(level, textureset))
		{
			if (level->blockData = Mem_Alloc(sizeof(Lego_Block) * level->width * level->height))
			{
				level->map->blockData=level->blockData;		/* cache pointer for modified routines */

				memset((LPUCHAR)level->blockData, 0, sizeof(Lego_Block) * level->width * level->height);

				for (y=0 ; y<level->height ; y++)
				{
					for (x=0 ; x<level->width ; x++)
					{
						blockValue(level,x,y).blockTexture = 0x00;
						blockValue(level,x,y).surfaceType = 0;
						blockValue(level,x,y).flags = 0x00;
						blockValue(level,x,y).direction = 0;
						blockValue(level,x,y).damage = 0;
						blockValue(level,x,y).topLeftAlt = 512;		//level->digDepth;
						blockValue(level,x,y).wobble = 0;

#ifdef UNEVEN_BLOCKS
						blockValue(level,x,y).xoff=(-x<<9)+(rand()&127)-64;
						blockValue(level,x,y).yoff=(y<<9)+(rand()&127)-64;
#else
						blockValue(level,x,y).xoff=-x<<9;
						blockValue(level,x,y).yoff=y<<9;
#endif
	
#ifndef RAINBOW_BLOCKS
						blockValue(level,x,y).red=255;
						blockValue(level,x,y).green=255;
						blockValue(level,x,y).blue=255;
						blockValue(level,x,y).lightSetting=128;
						Surface_SetLightPoint(x,y,0,0,0);
#else
						blockValue(level,x,y).lightSetting=0;
						blockValue(level,x,y).red=(rand()&127)+128;
						blockValue(level,x,y).green=(rand()&127)+128;
						blockValue(level,x,y).blue=(rand()&127)+128;
						Surface_SetLightPoint(x,y,0,0,0);
#endif

						blockValue(level,x,y).flags |= LEGOBLOCK_FLAG_SURVEYED;

					}
				}

			/* new altitude map done here */

				Lego_ProcessAltMap(level,surfMap);

				if (Lego_LoadPreDug(level, pdmap))
				{
					if (Lego_LoadTerrain(level, terrmap))
					{
						/* run through the map and setup the blocks */

						for (y=0 ; y<level->height ; y++)
						{
							for (x=0 ; x<level->width ; x++)
								Lego_CorrectBlock(level, x, y);
						}

						Lego_ProcessWaterLava(level);


			/* attempt to load a modmap, not a problem if we don't find one. */

						Lego_LoadModMap(modmap);				

			/* FIXME: get landing pad position from terrain map */

						Lego_MakeLandingPad(level,20,4,128);


						Lego_RecalculateVertexAngles();

						Mem_Free(surfMap);
						return TRUE;

					}
				}
			}
		}
	}
}



/*
	make a landing pad at passed position, using offset to
	determine height above ground.
*/
void	Lego_MakeLandingPad(lpLego_Level level, int x, int y, int offset)
{
	int	w,h;

/* set textures for pad */

	Map3D_SetBlockTexture(level->map, x, y, 0x11, 0);
	Map3D_SetBlockTexture(level->map, x+1, y, 0x11, 3);
	Map3D_SetBlockTexture(level->map, x, y+1, 0x11, 1);
	Map3D_SetBlockTexture(level->map, x+1, y+1, 0x11, 2);

/* reset the non-corners to neutral colour/light */

	Surface_SetColourPoint(x+1,y,80,80,80);
	Surface_SetColourPoint(x+1,y+2,80,80,80);
	Surface_SetColourPoint(x,y+1,80,80,80);
	Surface_SetColourPoint(x+2,y+1,80,80,80);
	Surface_SetLightPoint(x+1,y,80,80,80);
	Surface_SetLightPoint(x+1,y+2,80,80,80);
	Surface_SetLightPoint(x,y+1,80,80,80);
	Surface_SetLightPoint(x+2,y+1,80,80,80);

	Surface_SetColourPoint(x,y,0,255,0);
	Surface_SetColourPoint(x+2,y,0,255,0);
	Surface_SetColourPoint(x,y+2,0,255,0);
	Surface_SetColourPoint(x+2,y+2,0,255,0);

	Surface_SetColourPoint(x,y,80,80,80);
	Surface_SetColourPoint(x+2,y,80,80,80);
	Surface_SetColourPoint(x,y+2,80,80,80);
	Surface_SetColourPoint(x+2,y+2,80,80,80);
	Surface_SetColourPoint(x+1,y+1,80,80,80);

	Surface_SetLightPoint(20,4,128,128,128);
	Surface_SetLightPoint(22,4,128,128,128);
	Surface_SetLightPoint(20,6,128,128,128);
	Surface_SetLightPoint(22,6,128,128,128);
	Surface_SetLightPoint(21,5,128,128,128);

/* set split directions, to improve look */

	mapBlockValue(level->map, x, y).flags |= MAP3DBLOCK_FLAGROTATED;
	mapBlockValue(level->map, x+1, y).flags &= ~MAP3DBLOCK_FLAGROTATED;
	mapBlockValue(level->map, x, y+1).flags &= ~MAP3DBLOCK_FLAGROTATED;
	mapBlockValue(level->map, x+1, y+1).flags |= MAP3DBLOCK_FLAGROTATED;

/* set the offset and the grid positions (to remove variation) */

	for (h=y; h<(y+3); h++)
	{
		for (w=x; w<(x+3); w++)
		{
			blockValue(level,w,h).topLeftAlt += offset;
			blockValue(level,w,h).xoff=-w<<9;
			blockValue(level,w,h).yoff=h<<9;
		}
	}
}

/*
	attempt to load a mod map for a level if it exists, but it doesn't have to find one.
	we don't check that the mod map is the right size for the loaded level.
*/
BOOL	Lego_LoadModMap(LPUCHAR modmap)
{
	MODBLOCK2		*modMap,*modBlock;
	int				mapWidth,mapHeight,x,y;
	lpLego_Block	legoBlock;


	if (!(modMap = File_LoadBinary(modmap, NULL)))
		return	FALSE;

	mapWidth=legoGlobs.currLevel->width;
	mapHeight=legoGlobs.currLevel->height;
	legoBlock=legoGlobs.currLevel->blockData;
	modBlock=modMap;

	for (y=0; y<mapHeight; y++)
	{
		for (x=0; x<mapWidth; x++)
		{
			legoBlock->red=modBlock->red;
			legoBlock->green=modBlock->green;
			legoBlock->blue=modBlock->blue;
			legoBlock->lightSetting=modBlock->lightSetting;
			legoBlock->xoff=modBlock->xoff;
			legoBlock->yoff=modBlock->yoff;

			legoBlock->topLeftAlt=modBlock->zoff;
			legoBlock->direction=modBlock->direction;
//			legoBlock->flags&=0xffff0000;
//			legoBlock->flags|=modBlock->flags;
			Surface_SetLightPoint(x,y,0,0,0);
			modBlock++;
			legoBlock++;
		}
	}

	Mem_Free(modMap);

}


/*
	recalculate the angles to adjacent vertices for collision detection.
	these are pre-stored for speed
*/
void Lego_RecalculateVertexAngles(void)
{
	lpLego_Block	cb,db;
	int				x,y;
	int				mapWidth=legoGlobs.currLevel->width;
	int				mapHeight=legoGlobs.currLevel->height;

	cb=legoGlobs.currLevel->blockData;

	for (y=0; y<mapHeight; y++)
	{
		for (x=0; x<mapWidth; x++)
		{
			cb->north=0;
			cb->east=0;
			cb->south=0;
			cb->west=0;

			if (y>0)
			{
				db=cb-mapWidth;
				cb->north=(ratan2((cb->yoff-db->yoff),((-cb->xoff)-(-db->xoff)))+1024)&4095;
			}			

			if (x<(mapWidth-1))
			{
				db=cb+1;
				cb->east=(ratan2((cb->yoff-db->yoff),((-cb->xoff)-(-db->xoff)))+1024)&4095;
			}			

			if (y<(mapHeight-1))
			{
				db=cb+mapWidth;
				cb->south=(ratan2((cb->yoff-db->yoff),((-cb->xoff)-(-db->xoff)))+1024)&4095;
			}			


			if (x>0)
			{
				db=cb-1;
				cb->west=(ratan2((cb->yoff-db->yoff),((-cb->xoff)-(-db->xoff)))+1024)&4095;
			}			

			cb++;
		}
	}

}



/*
	This scans the maps and flags appropriate vertices for undulation.
	i.e. water or lava vertices which are surrounded by water or lava.

	uv undulation allowed if tile is lava or water
	
*/
VOID Lego_ProcessWaterLava(lpLego_Level level)
{
	int				n,x,y,id;
	Lego_Block		*blockData;

	for (y=0 ; y<(level->height-1) ; y++)
	{
		for (x=0 ; x<(level->width-1) ; x++)
		{
			blockData=level->blockData;
			id=(y*level->width)+x;
			if (blockData[id].blockTexture==LEGO_TEXTURE_FLOOR_LAVA)
			{
				blockData[id].flags|=MAP3DBLOCK_UVWOBBLES;
				blockData[id].flags|=MAP3DBLOCK_REDWOBBLES;

				if ((blockData[id-1].blockTexture==LEGO_TEXTURE_FLOOR_LAVA) &&
					 (blockData[id-level->width].blockTexture==LEGO_TEXTURE_FLOOR_LAVA) &&
					 (blockData[id-(level->width+1)].blockTexture==LEGO_TEXTURE_FLOOR_LAVA))
				{
					blockData[id].xoff=-x<<9;	/* offset in lava area not really desirable */
					blockData[id].yoff=y<<9;
					blockData[id].flags|=MAP3DBLOCK_VERTEXWOBBLES;


				/* set lighting to allow colour modulation red->orange */
					blockData[id].red=255;
					blockData[id].green=90;
					blockData[id].blue=0;
					blockData[id].lightSetting=100;

				}
				else		/* lava at edges, unmodulated, so leave more red, gives a better effect on surrounding land */
				{
					blockData[id].red=255;
					blockData[id].green=0;
					blockData[id].blue=0;
					blockData[id].lightSetting=100;
				}

				Surface_SetLightPoint(x,y,0,0,0);

			}
			else if (blockData[id].blockTexture==LEGO_TEXTURE_FLOOR_WATER)
			{
				blockData[id].flags|=MAP3DBLOCK_UVWOBBLES;
				if ((blockData[id-1].blockTexture==LEGO_TEXTURE_FLOOR_WATER) &&
					 (blockData[id-level->width].blockTexture==LEGO_TEXTURE_FLOOR_WATER) &&
					 (blockData[id-(level->width+1)].blockTexture==LEGO_TEXTURE_FLOOR_WATER))
				{
					blockData[id].flags|=MAP3DBLOCK_VERTEXWOBBLES;

					blockData[id].red=128;
					blockData[id].green=128;
					blockData[id].blue=255;
					blockData[id].lightSetting=160;

					Surface_SetLightPoint(x,y,0,0,0);
					blockData[id].direction=0;

				}

			}
			else		/* normal land */
			{
				if ((blockData[id-1].blockTexture==LEGO_TEXTURE_FLOOR_LAVA) ||
					 (blockData[id-level->width].blockTexture==LEGO_TEXTURE_FLOOR_LAVA) ||
					 (blockData[id-(level->width+1)].blockTexture==LEGO_TEXTURE_FLOOR_LAVA))

				{
					/* tinted by lava */

					blockData[id].flags|=MAP3DBLOCK_REDWOBBLES;

					blockData[id].red=255;
					blockData[id].green=0;
					blockData[id].blue=0;

					blockData[id].lightSetting=100;

					Surface_SetLightPoint(x,y,0,0,0);


				}
				else
				{

#ifdef RAINBOW_BLOCKS
					blockData[id].lightSetting=(rand()&127)+30;
#else
					blockData[id].lightSetting=128;
#endif
					Surface_SetLightPoint(x,y,0,0,0);


				}

			}
			
		}	
	}
}


#define		ALTMAP_SCALE_FACTOR		(256)
/*
	process altitude map

	heights are 0-15 in the map, we scale by ALTMAP_SCALE_FACTOR as a test

*/
BOOL Lego_ProcessAltMap(lpLego_Level level, LPULONG surfMap)
{
	ULONG 		w, h, x, y;
	lpMAPhead	mapHandle=(MAPhead*) surfMap;
	lpMap3D 		map = level->map;
	int			test;

	Lego_MapGetSpecs(mapHandle, &w, &h);
	if (w == level->width && h == level->height)
	{
		for (y=0 ; y<(h) ; y++)
		{
			for (x=0 ; x<(w) ; x++)
			{
				test=Lego_MapBlockValue(mapHandle, x, y)*ALTMAP_SCALE_FACTOR;
				blockValue(level,x,y).topLeftAlt+=Lego_MapBlockValue(mapHandle, x, y)*ALTMAP_SCALE_FACTOR;
			}
		}
		return TRUE;
	}
	return FALSE;
}



BOOL Lego_LoadPreDug(lpLego_Level level, LPUCHAR fname)
{
	ULONG 		w, h, x, y;
	lpMAPhead	mapHandle;
	lpMap3D 		map = level->map;

	if ((lpMAPhead)-1 != (mapHandle = File_LoadBinary(fname, NULL)))
	{
		Lego_MapGetSpecs(mapHandle, &w, &h);
		if (w == level->width && h == level->height)
		{
			for (y=1 ; y<(h-1) ; y++)
			{
				for (x=1 ; x<(w-1) ; x++)
				{
					if (1 == Lego_MapBlockValue(mapHandle, x, y))
					{
						Lego_DigBlockSetup(level, x, y);
					}
					else if (2 == Lego_MapBlockValue(mapHandle, x, y))
					{
						// This line was replaced by the one below
						// for test purposes only *****************
//						blockValue(level, x, y).flags |= LEGOBLOCK_FLAG_DELAYDIG;
						Lego_DigBlockSetup(level, x, y);
					}
				}
			}

			Mem_Free(mapHandle);
			return TRUE;
		}
		// Error Invalid Map
	}
	// Error Load Error

	Mem_Free(mapHandle);

	return FALSE;
}



short	damageLevels[]={0,200,400,500,700,1000};


BOOL Lego_LoadTerrain(lpLego_Level level, LPUCHAR fname)
{
	lpMAPhead terrainHandle;
	ULONG w, h, x, y;
	lpMap3D map = level->map;

	if ((lpMAPhead)-1 != (terrainHandle = File_LoadBinary(fname, NULL)))
	{
		Lego_MapGetSpecs(terrainHandle, &w, &h);
		if (w == level->width && h == level->height)
		{
			for (y=0 ; y<h ; y++)
			{
				for (x=0 ; x<w ; x++)
				{
					blockValue(level, x, y).surfaceType = (UCHAR) Lego_MapBlockValue(terrainHandle, x, y);
					blockValue(level, x, y).damage = damageLevels[(UCHAR) Lego_MapBlockValue(terrainHandle, x, y)];
				}
			}
			Mem_Free(terrainHandle);
			return TRUE;

		}
		// Error Invalid Map
	}
	// Error Load Error

	Mem_Free(terrainHandle);

	return FALSE;
}

BOOL Lego_LoadTextureSet(lpLego_Level level, LPUCHAR textname)
{
	lpConfig conf = legoGlobs.config;
	LPUCHAR surfname, roofname;
	BOOL res = FALSE;
	LPUCHAR meshBaseName, textureBaseName;
	ULONG width=8, height=8;
	
	level->tWidth = 8;
	level->tHeight = 8;
				
	if (textureBaseName = Config_GetTempStringValue(conf, Config_BuildStringID(legoGlobs.gameName, textname, "texturebasename", NULL)))
	{
		if (level->detailTSet = Surface_LoadTextureSet(textureBaseName, level->tWidth, level->tHeight))
		{
			level->map->textureData=(level->detailTSet->table);		/* point to texture data */
			res=TRUE;
		}
	}
	return res;
}




lpLego_Level Lego_GetLevel(VOID)
{

	return legoGlobs.currLevel;
}

lpMap3D Lego_GetMap(VOID)
{

	return Lego_GetLevel()->map;
}


BOOL Lego_IsFloor(ULONG x, ULONG y)
{

	lpLego_Level level = legoGlobs.currLevel;

	if (x > 0 && y > 0 && x < level->width-1 && y < level->height-1)
{
		return (blockValue(level, x, y).flags & LEGOBLOCK_FLAG_FLOOR);
	}
	return FALSE;

}

BOOL Lego_IsWall(ULONG x, ULONG y)
{

	lpLego_Level level = legoGlobs.currLevel;

	if (x > 0 && y > 0 && x < level->width-1 && y < level->height-1)
{
		return ((blockValue(level, x, y).flags & LEGOBLOCK_FLAG_WALL) &&
			!(blockValue(level, x, y).flags & LEGOBLOCK_FLAG_FLOOR));
	}
	return FALSE;

}

BOOL Lego_IsSurface(ULONG x, ULONG y)
{

	lpLego_Level level = legoGlobs.currLevel;

	if (x > 0 && y > 0 && x < level->width-1 && y < level->height-1)
{
		return !(blockValue(level, x, y).flags & (LEGOBLOCK_FLAG_WALL|LEGOBLOCK_FLAG_FLOOR));
	}
	return TRUE;

}





#define	IC		(3)
#define	OC		(5)
#define WALL	(0)
#define	VS		(6)
#define	UNEX	(7)
#define	FLOOR (8)

#define	NORTH	(0)
#define WEST	(1)
#define	SOUTH	(2)
#define EAST	(3)
#define NORTH_EAST	(3)
#define	NORTH_WEST	(0)
#define	SOUTH_EAST	(2)
#define SOUTH_WEST	(1)


typedef struct correct_st
{
	int	wallType;
	int	direction;
	int	split;
} CORRECT_BLOCK;


/*
	This data specifies how blocks are defined when vertices change
*/
CORRECT_BLOCK	correctionList[16]=
{
	{UNEX,NORTH,FALSE},			/* 00: nothing dug, show unexplored texture */
	{IC,SOUTH_EAST,TRUE},		/* 01: inside corner/south east */
	{IC,SOUTH_WEST,FALSE},		/* 02: inside corner/south west */
	{WALL,SOUTH,FALSE},			/* 03: wall/south */

	{IC,NORTH_WEST,TRUE},		/* 04: inside corner/north west */
	{VS,NORTH_EAST,TRUE},		/* 05: v-shape/north east */
	{WALL,WEST,FALSE},			/* 06: wall/west */
	{OC,SOUTH_WEST,FALSE},		/* 07: outside corner/south west */

	{IC,NORTH_EAST,FALSE},		/* 08: inside corner/north east */
	{WALL,EAST,FALSE},			/* 09: wall/east */
	{VS,NORTH_WEST,FALSE},		/* 10: v-shape/north west */
	{OC,SOUTH_EAST,TRUE},		/* 11: outside corner/south east */

	{WALL,NORTH,FALSE},			/* 12: wall/south */
	{OC,NORTH_EAST,FALSE},		/* 13: outside corner/north east */
	{OC,NORTH_WEST,TRUE},		/* 14: outside corner/north west */
	{FLOOR,0,FALSE},				/* 15: all dug - floor / */

};


/*
	new version of correctBlock
*/
VOID Lego_CorrectBlock(lpLego_Level level, ULONG bx, ULONG by)
{

	lpLego_Block	block;
	int	 			x, y, width=level->width;
	int				cornerMask=0,surfaceType,blockType;

	block=&blockValue(level,bx,by);


/* create a mask for the various vertex positions */

	if (block->flags & MAP3DBLOCK_VERTEXMOVED)
		cornerMask=1;
	if ((block+1)->flags & MAP3DBLOCK_VERTEXMOVED)
		cornerMask|=2;
	if ((block+width+1)->flags & MAP3DBLOCK_VERTEXMOVED)
		cornerMask|=4;
	if ((block+width)->flags & MAP3DBLOCK_VERTEXMOVED)
		cornerMask|=8;

	if (cornerMask==15)		/* all dug, set as floor */
	{
		block->flags|=LEGOBLOCK_FLAG_BLOCK_DUG;				/* mark as dug */
		if (block->surfaceType==LEGO_TEXTURE_FLOOR_WATER)
		{
			Map3D_SetBlockTexture(level->map, bx, by, LEGO_TEXTURE_FLOOR_WATER, NORTH);
			return;
		}

		if (block->surfaceType==LEGO_TEXTURE_FLOOR_LAVA)
		{
			Map3D_SetBlockTexture(level->map, bx, by, LEGO_TEXTURE_FLOOR_LAVA, NORTH);
			return;
		}

		block->surfaceType=Lego_SurfaceType_floor;
		if (block->blockTexture==LEGO_TEXTURE_FLOOR_STD)		/* if it's already floor, don't disturb the direction */
			return;

		Map3D_SetBlockTexture(level->map, bx, by, LEGO_TEXTURE_FLOOR_STD, (rand()&3));
	}
	else
	{
		surfaceType=block->surfaceType;
		blockType=correctionList[cornerMask].wallType;
		if (blockType==VS || blockType==UNEX)
			surfaceType=0;
		block->blockTexture=(blockType<<3)+surfaceType;
		block->direction=correctionList[cornerMask].direction;
		if (correctionList[cornerMask].split)
			block->flags|= MAP3DBLOCK_FLAGROTATED;
		else
			block->flags&= ~MAP3DBLOCK_FLAGROTATED;
	}
}



VOID Lego_MapGetSpecs(lpMAPhead map, ULONG *w, ULONG *h)
{

	ULONG *mapaddr = (ULONG *) (&map->width);

	*w = *mapaddr;
	mapaddr++;
	*h = *mapaddr;
}

ULONG Lego_MapBlockValue(lpMAPhead map, ULONG x, ULONG y)
{

	UWORD *mapaddr = (UWORD *) &map[1];
	ULONG width, height;
	
	Lego_MapGetSpecs(map, &width, &height);

	return mapaddr[(width * y) + x];
}


/*
	new dig block routine, + new cleanup stuff
*/
VOID Lego_DigBlock(lpLego_Level level,ULONG bx, ULONG by, BOOL setup)
{

	lpMap3D 			map=level->map;
	lpLego_Block	block;
	int	 			x, y, width=level->width;

	if (bx > 0 && by > 0 && bx < (level->width-2) && by < (level->height-2))
	{
		block=&blockValue(level,bx,by);


		if (!(block->flags & LEGOBLOCK_FLAG_FLOOR) &&
			(Lego_SurfaceType_Immovable != blockValue(level, bx, by).surfaceType || setup))
		{

			if (!(block->flags & LEGOBLOCK_FLAG_BLOCK_DUG))
			{
				Map3D_MoveVertex(map, bx, by, level->digDepth);
				block->flags|=LEGOBLOCK_FLAG_BLOCK_DUG;
			}

		/* set surveyed flag for blocks around block just dug */

			(block-width-1)->flags|=LEGOBLOCK_FLAG_SURVEYED;
			(block-width+1)->flags|=LEGOBLOCK_FLAG_SURVEYED;
			(block-1)->flags|=LEGOBLOCK_FLAG_SURVEYED;
			(block+1)->flags|=LEGOBLOCK_FLAG_SURVEYED;
			(block+width-1)->flags|=LEGOBLOCK_FLAG_SURVEYED;
			(block+width+1)->flags|=LEGOBLOCK_FLAG_SURVEYED;

			Lego_SetBlockType(level, bx, by, LEGOBLOCK_FLAG_FLOOR|LEGOBLOCK_FLAG_SURVEYED);



			blockValue(level, bx, by).flags &= ~LEGOBLOCK_FLAG_DIGSELECTED;
			blockValue(level, bx, by).flags &= ~LEGOBLOCK_FLAG_REINFORCED;


			for (y=by-1 ; y<by+2 ; y++)
			{
				for (x=bx-1 ; x<bx+2 ; x++)
					Lego_CorrectBlock(level, x, y);
			}

		}
	}

}


VOID Lego_SetBlockType(lpLego_Level level, ULONG bx, ULONG by, ULONG type)
{

	lpMap3D map = level->map;
	BOOL corner = type & LEGOBLOCK_FLAG_INNERCORNER;
	type &= ~LEGOBLOCK_FLAG_INNERCORNER;

	if (bx >= 0 && by >= 0 && bx < (level->width-1) && by < (level->height-1))
	{
		// If it's not ALREADY a floor block (Never overwrite with walls)...

		if (!(blockValue(level, bx, by).flags & LEGOBLOCK_FLAG_FLOOR))
		{
			if (corner)
			{
				if (!(blockValue(level, bx, by).flags & LEGOBLOCK_FLAG_WALL))
				{
					blockValue(level, bx, by).flags |= LEGOBLOCK_FLAG_INNERCORNER;
				}
			}
			else
				blockValue(level, bx, by).flags &= ~LEGOBLOCK_FLAG_INNERCORNER;
			blockValue(level, bx, by).flags |= type;
		}

		if (type & LEGOBLOCK_FLAG_FLOOR)
		{
			blockValue(level, bx, by).flags &= ~(LEGOBLOCK_FLAG_WALL|LEGOBLOCK_FLAG_INNERCORNER);
		}
	}
}

ULONG Lego_GetBlockType(ULONG x, ULONG y)
{

	lpLego_Level level = legoGlobs.currLevel;

	return blockValue(level, x, y).surfaceType;
}



VOID Lego_FloodOpenArea(ULONG bx, ULONG by)
{
	lpLego_Level level = legoGlobs.currLevel;
	LPVECTOR2D endlist[2];
	VECTOR2D pos;
	ULONG endlistcount[2] = { 0, 0 };
	ULONG listsize = (level->width * 2) + (level->height * 2);
	ULONG currlist = 0, loop;
	SLONG x, y;

	if (endlist[0] = Mem_Alloc(sizeof(VECTOR2D) * listsize * 2))
		{
		endlist[1] = &endlist[0][listsize];

		endlist[currlist][0].x = (REAL) bx;
		endlist[currlist][0].y = (REAL) by;
		endlistcount[currlist] = 1;

		while (endlistcount[currlist])
			{
			for (loop=0 ; loop<endlistcount[currlist] ; loop++)
				{
				pos = endlist[currlist][loop];

				for (y=(SLONG) pos.y-1 ; y<= (SLONG) pos.y+1 ; y++)
					{
					for (x= (SLONG) pos.x-1 ; x<= (SLONG) pos.x+1 ; x++)
						{
						if (blockValue(level, x, y).flags & LEGOBLOCK_FLAG_DELAYDIG)
							{
							Lego_DigBlockSetup(level, x, y);
							blockValue(level, x, y).flags &= ~LEGOBLOCK_FLAG_DELAYDIG;

							if (pos.x != x || pos.y != y)
								{
								endlist[!currlist][endlistcount[!currlist]].x = (REAL) x;
								endlist[!currlist][endlistcount[!currlist]].y = (REAL) y;
								endlistcount[!currlist]++;
								}
							}
						}
					}
				}

			endlistcount[currlist] = 0;
			currlist = !currlist;
			}
		
		Mem_Free(endlist[0]);
		}
}














/*
	clear elapsed game time
*/
void Lego_ResetGameClock(void)
{
	legoGlobs.vblankCycles=0;
	legoGlobs.elapsedTime=0;
}


/*
	set elapsed time in seconds
*/
void Lego_SetGameClock(int time)
{
	legoGlobs.vblankCycles=0;
	legoGlobs.elapsedTime=0;
}





/*
	duplicate final path section
*/
BOOL	GetFinalPath(char *from,char *to)
{
	int	n=strlen(from);
	char	c;

	if (n>0)
	{
		while (n>0)
		{
			c=from[n];
			if (from[n]=='\\')
				break;
			n--;
		}

		if (from[n]=='\\')
			n++;

		while (from[n]!=0)
			*to++=from[n++];
		*to=0;

		return	TRUE;
	}
	return	FALSE;
}





/*
	Generic load to activitySet from an .AE file for minifigures/snakes/etc
	move to image.c later

	fname is complete path/ to .ae/.tim files
	final part of path is duplicated to form the .ae name
*/
BOOL Image_LoadActivityFromConfig(lpSPR_ACTIVITY_SET *activitySet, LPUCHAR fpath, LPUCHAR gameName)
{
	lpConfig rootConf;
	UCHAR 	aePath[256];
	LPUCHAR 	argv[100];
	ULONG 	count, loop;
	BOOL 		res = FALSE;
	int		created=0;
	char		aefname[16];


	GetFinalPath(fpath,aefname);


	if (!(Image_ActivitySetCreate(activitySet)))
		return	FALSE;

	sprintf(aePath, "%s\\%s.AE", fpath,aefname);

	if (rootConf = Config_Load(aePath))
	{
		lpConfig activity_list;
		ULONG 	id;

		char		*timFile,*cloneFile,*startList,*loopList;
		char		*cloneFrom;
		char		timPath[128];
		int		numFrames,numDirections;
		int		cellWidth,cellHeight;
		int		xOffset,yOffset;
		int		createFlips,animDelay;

	/* scan the activity list, processing only timFile references  */

		if (activity_list = Config_FindArray(rootConf, Config_BuildStringID(legoGlobs.gameName, "Activities", NULL)))
		{
			while (activity_list)
			{
				if (timFile=Config_GetTempStringValue(rootConf,  Config_BuildStringID(legoGlobs.gameName, activity_list->dataString, "timFile", NULL)))
				{
					numDirections=	Config_GetIntValue(rootConf,  Config_BuildStringID(legoGlobs.gameName, activity_list->dataString, "numDirections", NULL));
					numFrames=		Config_GetIntValue(rootConf,  Config_BuildStringID(legoGlobs.gameName, activity_list->dataString, "numFrames", NULL));
					cellWidth=		Config_GetIntValue(rootConf,  Config_BuildStringID(legoGlobs.gameName, activity_list->dataString, "cellWidth", NULL));
					cellHeight=		Config_GetIntValue(rootConf,  Config_BuildStringID(legoGlobs.gameName, activity_list->dataString, "cellHeight", NULL));
					xOffset=			Config_GetIntValue(rootConf,  Config_BuildStringID(legoGlobs.gameName, activity_list->dataString, "xOffset", NULL));
					yOffset=			Config_GetIntValue(rootConf,  Config_BuildStringID(legoGlobs.gameName, activity_list->dataString, "yOffset", NULL));
					createFlips=	Config_GetBoolValue(rootConf,  Config_BuildStringID(legoGlobs.gameName, activity_list->dataString, "createFlips", NULL));
					startList=		Config_GetTempStringValue(rootConf,  Config_BuildStringID(legoGlobs.gameName, activity_list->dataString, "startSeq", NULL));
					loopList=		Config_GetTempStringValue(rootConf,  Config_BuildStringID(legoGlobs.gameName, activity_list->dataString, "loopSeq", NULL));
					animDelay=		Config_GetIntValue(rootConf,  Config_BuildStringID(legoGlobs.gameName, activity_list->dataString, "animDelay", NULL));

					sprintf(timPath,"%s\\%s.TIM",fpath,timFile);
					if ((Image_LoadToActivitySet(*activitySet,timPath,activity_list->dataString,numDirections,numFrames,cellWidth,cellHeight,xOffset,yOffset,createFlips,startList,loopList,animDelay))!=-1)
						created++;2-									41/30.30.30.







				



752752752752								-2-.3.-2--2-		
	30.30.30.30.	0,-1-.1-.1,-







					30.41/30.30.



610610610721











				-2--2-.3.-2-								41.30.41/41.







				



752752752752	
			
		-2--2-.3.-2-				30.30.30.41/