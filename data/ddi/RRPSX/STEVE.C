//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Steve's File For <LEGO [Rock Raiders]>
//
// Started:	10-07-98
// Coding:	Glenn Benson
// Graphics:
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Include all Header Files
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
#include	"globals.h"


//#define		TWO_PLAYERS

#define		SCOTTS_EDITOR


extern	SURFACE_GLOBS	surfaceGlobs;
extern	short	cosTable[];

/* some horrible prototypes for test routines */

short	mask_brightness=128;
int		screen_toggle=0;
int		map_xoffset=152;
int		map_yoffset=65457;
int		radar_toggle=1;
int		lm_index=0;


int		pauseFlag=FALSE;

void	Steve_MapEdit(void);

long sound_init(unsigned char *vh, unsigned char *vb);
void	update_mouse(Uint16 pad);
void	move_destination_cursor(void);
void	move_all_vehicles(void);
void	set_new_route(void);

void	rebuild_world_mesh(lpContainer cam_cont);
void	simple_clip_vehicles(int tmapx, int tmapy);
void	get_altitude_forward_back(int *forward, int *centre, int *back);
BOOL	get_dig_block(int *x, int *y);
void	draw_current_block_highlight(int x, int y);
void	show_vram(void);
void show_texture_page(void);
BOOL	get_dig_block_from_position(int *x, int *y);
void	transform_test(void);
int	getHeight(lpLego_Level current_level, int x, int z);

BOOL Image_LoadActivityFromConfig(lpSPR_ACTIVITY_SET *activitySet, LPUCHAR fpath, LPUCHAR gameName);

void	qrebuildRadarQuadList(Sint16 mx, Sint16 my);
void	rebuildRadarQuadList(lpLego_Level current_level, Sint16 mx, Sint16 my);

void update_rockfall(void);
void	Boulder_ServiceBoulderPool(int time);
BOOL	Boulder_CreateBoulderPool(void);
BOOL	Boulder_CreateSmokePool(void);
int	Boulder_AddBoulder(int x, int y, int z, int scale, int direction, int speed, int zSpeed, int time, int creationFlags);
int	Boulder_AddSmoke(int x, int y, int z, int scale, int scaleDelta, int zSpeed, int startAlpha, int alphaDelta, int red, int green, int blue);

void	Trigger_TestTriggerSetup(void);
void	Trigger_TestTriggerRun(void);
void Trigger_displayGameStatus(void);
void	Trigger_ResetGameController(void);

lpLego_Block	Surface_GetBlock(int x, int y);



BOOL		Creature_RockWhaleTurnRight(lpOBJECT rockWhaleObject);
BOOL		Creature_RockWhaleTurnLeft(lpOBJECT rockWhaleObject);
BOOL		Creature_RockWhaleStartMoving(lpOBJECT rockWhaleObject);


extern	Sint16				old_mx,old_my;



int		lastUpdate;


//#define		LOAD_OBJECT_LIST

TRIGGER_ENTITY	objectList[]=
{
/* first player */
	{UOT_CREATE_MINIFIGURE(20480,6528,2048,0)},
	{UOT_CREATE_MINIFIGURE(9984,1280,2048,2)},
#ifdef TWO_PLAYERS
	{UOT_CREATE_MINIFIGURE(12224,1664,2048,1)},
#endif

#ifndef LOAD_OBJECT_LIST
	//{UOT_CREATE_CREATURE_FLAGS(TR_CREATURE_SCORPION, 17000, 3392, 2048,0)},
	//{UOT_CREATE_CRAFT(TR_CRAFT_LARGE_HELICOPTER,	(21*512), (5*512), 2048)},
#endif

	//{UOT_CREATE_CREATURE(TR_CREATURE_SNAKE, 12032, 1664, 2048)},
	//{UOT_CREATE_CREATURE(TR_CREATURE_SPIDER, 12928, 3008, 2048)},
	//{UOT_CREATE_CRAFT(TR_CRAFT_LARGE_DIGGER, 11584, 1024, 2048)},


/* some test vehicles */

	{UOT_CREATE_CRAFT(TR_CRAFT_HOVERBOARD,	(16512-700), (3464), 3072)},
	{UOT_CREATE_CRAFT(TR_CRAFT_SMALL_TRUCK,		15616, 	5376, 	3072)},
	{UOT_CREATE_CRAFT(TR_CRAFT_SCOOP,				12864, 	3648, 	1536)},
	{UOT_CREATE_CRAFT(TR_CRAFT_CRATE,				13504, 	5440, 	256)},
	//{UOT_CREATE_CRAFT(TR_CRAFT_BIG_LASER,			18560, 	7872, 	1536)},
	{UOT_CREATE_CRAFT(TR_CRAFT_SMALL_HELICOPTER,	17024,4480,	2500)},
	//{UOT_CREATE_CRAFT(TR_CRAFT_SMALL_LASER,		11712, 	9920,		2048)},
	//{UOT_CREATE_CRAFT(TR_CRAFT_LARGE_DIGGER,		10560, 	7616,		1536)},
	{UOT_CREATE_CRAFT(TR_CRAFT_LARGE_HELICOPTER,			10752, 	2560,		1536)},


/* some test creatures */

	{UOT_CREATE_CREATURE(TR_CREATURE_ROCKWHALE, 18240, 3136, 2048)},
	//{UOT_CREATE_CREATURE(TR_CREATURE_SNAKE, 8960, 1856, 2048)},
	//{UOT_CREATE_CREATURE(TR_CREATURE_SPIDER, 12288, 2304, 2048)},



	{TRIGGER_LIST_END},
};



#define		MAX_LM		(30)
#define		MAX_OTHER	(10)

typedef struct lm_st
{
	lpContainer	cont;	
	int			xd;
	int			yd;
	int			angle;
	int			speed;
	int			activity;
	int			time;
	int			class;

}	LM;

LM	lmlist[MAX_LM+MAX_OTHER];
int	lmcreated=0;
int	lmcreate_time=0;


lpSPR_ACTIVITY_SET		creatureActivitySet[3];

int			legoman_frame=0;
int			rotate=0;



int				cam_pos_x=0;
int				cam_pos_y=3000;
int				cam_pos_z=2750;

int				cam_look_x=0;
int				cam_look_y=7500;
int				cam_look_z=7500;


int				mcam_pos_x=0;
int				mcam_pos_y=3000;
int				mcam_pos_z=2750;

int				mcam_look_x=0;
int				mcam_look_y=8000;
int				mcam_look_z=8000;



typedef struct	test_rf
{
	lpContainer		container;
	int				x;
	int				y;
	int				time;
	int				action;

}	TEST_RF;

TEST_RF			rockfall;





enum
{
	CLASS_SPIDER,
	CLASS_SNAKE,
	CLASS_SCORPION,
	CLASS_MAXCREATURES,
};


enum
{
	ACTIVITY_WALK,
	ACTIVITY_RUN,
	ACTIVITY_CARRY,
	ACTIVITY_DIG,
	ACTIVITY_DRILL,
	ACTIVITY_HAMMER,

};



#ifdef MAPEDIT

MAPEDITGLOBS		mapeditGlobs={16384,3072,0,""};

#endif











void	Overlay_DrawFilledRectangle(int x, int y, int w, int h, int r, int g, int b, int attribute, int priority)
{
	GsBOXF		box;

	box.r=r;
	box.g=g;
	box.b=b;
	box.attribute=attribute;
	box.x=x-(gfxGlobs.scrW>>1);
	box.y=y-(gfxGlobs.scrH>>1);
	box.w=w;
	box.h=h;
	GsSortBoxFill(&box, &gfxGlobs.Wot[gfxGlobs.bufID], priority);
}



#define	DRAW_SEMI_TRANS_GREY_BOX(x,y,w,h)		Overlay_DrawFilledRectangle(x,y,w,h,32,32,32,(GsALON),10)


#define	SPEED_THRESHOLD	(12)
/*
	current demo:
	player controls a minifigure who walks about, when near enough to
	a vehicle/aircraft, a pulsing reticule appears and the craft can
	be entered. aircraft take off on entry and hover. When  

*/
void new_demo_update(void)
{
				VECTOR3D		camera_pos,camera_look;
				Uint16		pad=Input_PadData(0);
				int			blockx,blocky;
				lpCRAFT		craft;
				int			n;

	static	int			rad_y=25000,rad_z=25000<<1;
	static	int			main_y=2616,main_z=3646<<1;
	static	Uint16		old_pad;
	static	int			playerUsing=0;
				CdlLOC		toc[100];		


				int				radius,radius2;
				lpMINIFIGURE	minifigure,minifigure2;
				lpCRAFT			craft2=objectGlobs.playerList[1].craft;
				lpContainer		playerCont=NULL;
				lpContainer		player2Cont=NULL;


	static	int	landingLight=32;


				int	track;
				int	update,timeUpdate;


				unsigned char	returnedParameters[8];
	static	int				playTrack=1;

				lpCONTROL		control=objectGlobs.playerList[0].controlSet;

				lpOBJECT			craftObject,craftObject2;

//	Surface_SetLightPoint(21,5,(cosTable[landingLight]>>1)+64,64,64);



#ifndef __CDVERSION
/* test for line collision on blocks */
	Surface_GetBlock(objectGlobs.playerList[0].minifigureObject->x>>12,objectGlobs.playerList[0].minifigureObject->y>>12);
#endif


/* test rockwhale movement */

#ifndef __CDVERSION
 #ifdef SKIP_IT
	if (mapeditGlobs.mode==EM_OFF)
	{
		if (PAD_EVENT(control,CONTROL_SYS_SQUARE))
		{
			Creature_RockWhaleTurnLeft(&objectGlobs.objectList[ROCKWHALE_START]);
		 	CLEAR_EVENT_RELEASE(control,CONTROL_SYS_SQUARE);
		}

		if (PAD_EVENT(control,CONTROL_SYS_TRIANGLE))
		{
			Creature_RockWhaleStartMoving(&objectGlobs.objectList[ROCKWHALE_START]);
		 	CLEAR_EVENT_RELEASE(control,CONTROL_SYS_TRIANGLE);
		}

		if (PAD_EVENT(control,CONTROL_SYS_CIRCLE))
		{
			Creature_RockWhaleTurnRight(&objectGlobs.objectList[ROCKWHALE_START]);
		 	CLEAR_EVENT_RELEASE(control,CONTROL_SYS_CIRCLE);
		}
	}
 #endif
#endif

	landingLight++;
	landingLight&=31;


	update=legoGlobs.vblankCount-legoGlobs.lastUpdate;
	legoGlobs.lastUpdate=legoGlobs.vblankCount;
	if (update<1)		/* could be zero at startup */
		update=1;
	if (update>4)		/* cap large updates, bigger than this is very bad indeed */
		update=4;


/*
	make into a suitable FIXED update delta. We will assume timings are for PAL
	and therefore multiply the delta accordingly

	Note: we shift by 11 instead of 12 because the original data
			was created assuming a fixed 2 frame update.
*/


#ifdef __PAL
	timeUpdate=update<<11;

#else
	timeUpdate=Asm_MulFIX(update<<11,ToFIXED(0.83));		// == 50/60
#endif



/* force for demo, check later */

	timeUpdate=update<<11;


	legoGlobs.updateTime=timeUpdate;		/* cache for use by render callbacks */


#ifndef __CDVERSION
/*-----------------------------------------------------------------------------------------------------------------*/
	{
		char	string[64];

		sprintf(string, "td=%d (%d)", timeUpdate,update);
		Font_PrintF(legoGlobs.stdFont,8,24,string);
		sprintf(string, "%d:%02d", legoGlobs.elapsedTime/60,legoGlobs.elapsedTime%60);
		Font_PrintF(legoGlobs.stdFont,340,8,string);

		sprintf(string, "%d", sizeof(TRIGGER_ENTITY));
		Font_PrintF(legoGlobs.stdFont,340,16,string);
			
	}
/*-----------------------------------------------------------------------------------------------------------------*/


#endif

#ifndef __CDVERSION
#ifdef MAPEDIT
	if (mapeditGlobs.mode)
	{

#ifdef SCOTTS_EDITOR
		if (mapeditGlobs.mode == EM_OBJ_EDITOR)
		{
			EDITOR_ObjectEditor();
			Camera_SetCameraOnVelocityObject(playerCont, player2Cont, radius,radius2);
			rebuild_world_mesh(cameraSmooth.cont);
			return;
		}
		else
#endif

		{
			Steve_MapEdit();
			Camera_SetCameraOnVelocityObject(playerCont, player2Cont, radius,radius2);
			rebuild_world_mesh(cameraSmooth.cont);
			return;
		}
	}		
	else
	{
		if (PAD_EVENT(control,CONTROL_SELECT))
		{
			CLEAR_EVENT_RELEASE(control,CONTROL_SELECT);
			mapeditGlobs.mode++;
		}
	}
#endif
#endif

	if (!legoGlobs.pauseFlag)
	{
		static int	dripTime=60;

		if ((legoGlobs.frameCount&127)==dripTime)
		{
			dripTime=60+(rand()&31);

			Sfx_PlayEffectPan(SFX_SAMPLE_DRIPS,60+(rand()&7),32+(rand()&31),32+(rand()&31));
		}
			

#ifdef 0
/*---------------------------------------------------------------------------------------------------------------------*/
/*--- frame rate toggle -------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
	if (PAD_EVENT(control,CONTROL_SYS_CIRCLE))
	{
	 	CLEAR_EVENT_RELEASE(control,CONTROL_SYS_CIRCLE);
		if (gfxGlobs.frames==2)
			gfxGlobs.frames=4;
		else
			gfxGlobs.frames=2;
	}
#endif


		//	We check here for pause since it gives one pass through the craft list,
		//	with the pause flag set, allowing the SFX to be muted.

		if (PAD_EVENT(control,CONTROL_START))
		{
			CLEAR_EVENT_RELEASE(control,CONTROL_START);
			legoGlobs.pauseFlag=TRUE;
		}


		// also check for controller 1 having been removed, since this will
		//	generate a pause


		if (!objectGlobs.playerList[0].controllerConnected)
			legoGlobs.pauseFlag=TRUE;



/* scan craft area of object list, run controller for them */

		for (n=CRAFT_LIST_START; n<(CRAFT_LIST_START+objectGlobs.numCraft); n++)
		{
			craftObject=&objectGlobs.objectList[n];
			craft=craftObject->objectData;

		/* visibility check here */

			if (craft->controlledBy!=-1)
				craft->craftHandler(&objectGlobs.playerList[craft->controlledBy],craftObject,timeUpdate);
			else			
				craft->craftHandler(NULL,craftObject,timeUpdate);		/* null control input */
		}


		/* check for active minifigures */

		if (objectGlobs.playerList[0].flags & PLAYER_FLAG_MINIFIGURE_ACTIVE)
			Player_UpdateMinifigure(objectGlobs.playerList[0].minifigureObject,&objectGlobs.playerList[0],timeUpdate);


		if (objectGlobs.playerList[1].flags & PLAYER_FLAG_MINIFIGURE_ACTIVE)
			Player_UpdateMinifigure(objectGlobs.playerList[1].minifigureObject,&objectGlobs.playerList[1],timeUpdate);


		Creature_ServiceCreatureList(timeUpdate);

	}
	else		/* do pause menu stuff here */
	{
		char	string[32];

		DRAW_SEMI_TRANS_GREY_BOX(192-48,128-16,96,32);

		Font_PrintF(legoGlobs.stdFont,172,128-4,"Paused");
		

		CD_UpdateCDPlayer();

		if (PAD_EVENT(control,CONTROL_START))
		{
			CLEAR_EVENT_RELEASE(control,CONTROL_START);
			//CD_HandleResumeFromPause();
			legoGlobs.pauseFlag=FALSE;
		}
	}


	Camera_HandleCameraInteraction(timeUpdate);


/* setup main camera for display */

	camera_pos.x=0;
	camera_pos.y=main_y;
	camera_pos.z=main_z;



	if (objectGlobs.playerList[0].flags & PLAYER_FLAG_MINIFIGURE_ACTIVE)
	{
		radius=0;
		minifigure=objectGlobs.playerList[0].minifigure;	
		playerCont=minifigure->refCont;
	}
	else	/* player controlling ground/air craft */
	{
		lpOBJECT	craftObject=objectGlobs.playerList[0].craftObject;

		//craft=objectGlobs.playerList[0].craft;

		if (craftObject->speed>0)
			radius=(craftObject->speed>>9)+200;
		else
			radius=200;
		playerCont=craftObject->cont;
	}


/* test for player 2 active */
	if (objectGlobs.numPlayers==2)
	{
		if (objectGlobs.playerList[1].flags & PLAYER_FLAG_MINIFIGURE_ACTIVE)
		{
			radius2=0;
			minifigure2=objectGlobs.playerList[1].minifigure;	
			player2Cont=minifigure2->refCont;
		}
		else	/* player controlling ground/air craft */
		{
			lpOBJECT	craftObject2=objectGlobs.playerList[1].craftObject;


			if (craftObject2->speed>0)
				radius2=(craftObject2->speed>>9)+200;
			else
				radius2=200;
			player2Cont=craftObject2->cont;
		}
	}


	Camera_SetCameraOnVelocityObject(playerCont, player2Cont, radius,radius2);

	rebuild_world_mesh(cameraSmooth.cont);
	Boulder_ServiceBoulderPool(timeUpdate);


/* general purpose frame counter for cycling/pulsing control etc. */

	legoGlobs.frameCount++;

	Trigger_TestTriggerRun();
	Trigger_DisplayGameStatus();

#ifdef DEBUG_CONSOLE
	Console_DisplayConsole(FALSE);
#endif


}



/*
	purge object lists, and read trigger lists
*/
void	Steve_InitialiseGameData(void)
{


	int			n;
	VECTOR3D		pos;

	CD_initialiseCDAudio();


	Object_InitialiseLists();
	Creature_InitialiseLists();

/* new stuff for analogue pad */
  PadInitDirect(objectGlobs.playerList[0].padBuffer,objectGlobs.playerList[1].padBuffer);
	PadStartCom();


/* boulder and smoke stuff */
	Boulder_CreateBoulderPool();
	Boulder_CreateSmokePool();


	Trigger_ParseTriggerList(objectList);


#ifdef LOAD_OBJECT_LIST
	{
		lpTRIGGER_ENTITY	temp;
		char					triggerPath[128];

		if (Trigger_LoadTriggerList("objects.trg",&temp))
		{
			Trigger_ParseTriggerList(temp);
			Mem_Free(temp);
		}
	}
#endif

	Player_CreatePlayer(0,0);						/* player0, minifigure 0 */

#ifdef TWO_PLAYERS
	Player_CreatePlayer(1,1);
#else
	objectGlobs.playerList[1].craft=NULL;		/* player 2 inactive */
#endif

	Lego_ResetGameClock();

	Trigger_ResetGameController();
 	Trigger_TestTriggerSetup();

#ifdef MAPEDIT
#ifdef SCOTTS_EDITOR
	EDITOR_Initialise();
#endif
#endif

}









#define		CURSOR_DELTA		(64)		//(128)

/*
	move vehicle destination cursor
*/
void	move_destination_cursor(void)
{

}

#define					BLOCK_GAP		(512)
#define					STAGES			(8)
#define					STAGE_DELTA		(BLOCK_GAP/STAGES)

/*
		move all the vehicles with active routes

		for this demo we will use some of the bezier variables
		since they're not used at present

		bezlen			= number of steps to next block;
		xMove/yMove		= delta for movement
*/
void	move_all_vehicles(void)
{
}



/*
		start new route for vehicle
		NOTE: a new route can only be set if the previous one has finished
*/
void	set_new_route(void)
{
#ifdef 0
	lpLegoObject	lego_obj;
	Uint16			pad=Input_PadData(0);
	int				vx,vy,tx,ty,n;
	VECTOR3D			position;
	LPUCHAR			xpos=NULL,ypos=NULL;
	ULONG				rlength;

	lego_obj=demo_vehicle.obj_list[demo_vehicle.object_index];
	if (lego_obj->routeList)
		return;		/* route in use, drop out */

	if (Input_PadData(0) & PAD_START)
	{
		Container_GetWorldPosition(demo_vehicle.obj_list[demo_vehicle.object_index]->vehicle->bodyCont,&position);
		vx=(position.x)/BLOCK_GAP;
		vy=position.y/BLOCK_GAP;

		tx=demo_vehicle.x/BLOCK_GAP;
		ty=demo_vehicle.y/BLOCK_GAP;

		if (tx==vx && ty==vy)
			return;						/* not much of a route, is it?  */

		if (!Lego_CanGo(demo_vehicle.obj_list[demo_vehicle.object_index], tx, ty))
			return;						/* destination is illegal */

		if (LegoObject_RouteFind(lego_obj,vx,vy,tx,ty,&xpos,&ypos,&rlength))
		{
			lego_obj->routeList=Mem_Malloc(rlength*sizeof(LegoObject_Route));


			for (n=0; n<rlength; n++)
			{
				lego_obj->routeList[n].xBlock=xpos[n];
				lego_obj->routeList[n].yBlock=ypos[n];
			}
			lego_obj->routeLength=rlength;
			lego_obj->routeStage=1;					/* skip the first entry as it is the start position */
			Mem_Free(xpos);
			Mem_Free(ypos);
		}
	}
#endif
}





/*
	display cursor and text for new demo
*/
void	new_demo_display(void)
{
	//draw_current_block_highlight(demo_vehicle.x,demo_vehicle.y);

	//display_console();

}


/*
	transform a world coordinate point and draw a small cross
*/
void	draw_world_cross(LPVECTOR3D	pos, int red, int green, int blue)
{
	GsLINE	line;
	GsCOORDINATE2	coord;
	MATRIX	mat;
	short		coords[3];
	long		depth,flag,sort;
	SVECTOR	vector;

	GsInitCoordinate2(WORLD, &coord);
	GsGetLs(&coord, &mat);
	GsSetLsMatrix(&mat);

	vector.vx=-pos->x;
	vector.vy=pos->z;
	vector.vz=pos->y;
	gte_RotTransPers(&vector,(long*)&coords[0],&depth,&flag,&sort);

	line.attribute=0;
	line.r=red;
	line.g=green;
	line.b=blue;

	line.x0=coords[0]-1;
	line.y0=coords[1];
	line.x1=coords[0]+1;
	line.y1=coords[1];
	GsSortLine(&line,&gfxGlobs.Wot[gfxGlobs.bufID],10);

	line.x0=coords[0];
	line.y0=coords[1]-1;
	line.x1=coords[0];
	line.y1=coords[1]+1;
	GsSortLine(&line,&gfxGlobs.Wot[gfxGlobs.bufID],10);
}


#define	MAX_VERTICES	(25)

void	transform_test(void)
{
	SVECTOR			vertexList[MAX_VERTICES];
	DVECTOR			outputList[MAX_VERTICES];
	unsigned short	szList[MAX_VERTICES];
	unsigned short	pList[MAX_VERTICES];
	unsigned short	flag[MAX_VERTICES];
	
	GsCOORDINATE2	coord;
	MATRIX			mat;

	int				n,x,y,index;
	GsLINE			line;


	GsInitCoordinate2(WORLD, &coord);
	GsGetLs(&coord, &mat);
	GsSetLsMatrix(&mat);


/* create test vertices */


	for (y=0; y<5; y++)
	{
		for (x=0; x<5; x++)
		{
			vertexList[index].vx=-((x<<7)+1024);
			vertexList[index].vy=-600;
			vertexList[index].vz=y<<7;
			index++;
		}
	}


	RotTransPersN(vertexList,outputList,szList,pList,flag,MAX_VERTICES);


	
	for (n=0; n<MAX_VERTICES; n++)
	{
		line.attribute=0;
		line.r=255;
		line.g=255;
		line.b=255;

		line.x0=outputList[n].vx-1;
		line.y0=outputList[n].vy;
		line.x1=outputList[n].vx+1;
		line.y1=outputList[n].vy;
		GsSortLine(&line,&gfxGlobs.Wot[gfxGlobs.bufID],10);

		line.x0=outputList[n].vx;
		line.y0=outputList[n].vy-1;
		line.x1=outputList[n].vx;
		line.y1=outputList[n].vy+1;
		GsSortLine(&line,&gfxGlobs.Wot[gfxGlobs.bufID],10);


	}
}



/*
	draw an arrow pointer over selected vehicle
*/
void	draw_selected(void)
{
}


VOID qDraw_WorldLineListEx(lpViewport vp, LPVECTOR3D fromList, LPVECTOR3D toList, ULONG count, REAL r, REAL g, REAL b, ULONG effect)
{
	GsLINE	line;
	int		n;
	ULONG		attribute=0;							/* default to draw/solid */
	SVECTOR	vector;
	short		coords[3];
	long		depth=14,flag,sort;
	GsCOORDINATE2	coord;
	MATRIX	mat;
	int		colour_table[]={16,32,64,96,96,64,32,16,8};

	GsInitCoordinate2(WORLD, &coord);
	GsGetLs(&coord, &mat);
	GsSetLsMatrix(&mat);

	if (effect==DrawEffect_HalfTrans)
		attribute=(GsALON | GsAONE);		/* semi trans enabled, blend of 100% background + 100% foreground */
	//	attribute=((1<<30)|1<<29);		/* semi trans enabled, blend of 100% background + 100% foreground */


	
//	r>>=4;
//	if (r>0)
//		r--;			
//	line.r=r;

//	g>>=4;
//	if (g>0)
//		g--;			
//	line.g=g;

//	b>>=4;
//	if (b>0)
//		b--;			
//	line.b=b;


	for (n=0; n<count; n++)
	{
		vector.vx=fromList[n].x;
		vector.vy=fromList[n].y;
		vector.vz=fromList[n].z;
		gte_RotTransPers(&vector,(long*)&coords[0],&depth,&flag,&sort);

		line.attribute=attribute;
		line.x0=(coords[0]);		//+map_xoffset;
		line.y0=(coords[1]);		//+map_yoffset;

		vector.vx=toList[n].x;
		vector.vy=toList[n].y;
		vector.vz=toList[n].z;


		gte_RotTransPers(&vector,(long*)&coords[0],&depth,&flag,&sort);

		line.x1=(coords[0]);		//+map_xoffset;
		line.y1=(coords[1]);		//+map_yoffset;


/*
		line.r=line.g=line.b=colour_table[n];
		if (line.r>r)
		{
			line.r=line.g=line.b=r;
		}
*/
		line.r=line.g=line.b=32;

		GsSortLine(&line,&gfxGlobs.Wot[gfxGlobs.bufID],sort);
	}

}



/* draw a highlight box for the block currently on */
void	draw_current_block_highlight(int x, int y)
{
#ifdef 0
	static	int				flash=0;

				VECTOR3D			highlight_block[5];
				VECTOR3D			position;
				int				map_x,map_y,vbx,vby;

				lpVehicle3D		vehicle=demo_vehicle.obj_list[demo_vehicle.object_index]->vehicle;
				lpMap3D 			map=legoGlobs.currLevel->map;
				int				block_size=FromFIXED(legoGlobs.currLevel->blockSize);
				int				red,green;


	Container_GetWorldPosition(vehicle->bodyCont,&position);
	vbx=position.x/block_size;
	vby=position.y/block_size;
	map_x=x/block_size;
	map_y=y/block_size;

	if (Lego_CanGo(demo_vehicle.obj_list[demo_vehicle.object_index], map_x, map_y))
	{
		green=ONE;
		red=0;
	}
	else
	{
		red=ONE;
		green=0;
	}

	flash++;
	if (vbx==map_x && vby==map_y)
	{
		if ((flash&4)==4)
		{
			red=0;			/* red should be zero at this point since a vehicle should be on flat ground */
			green=0;
		}
	}

	highlight_block[0].x=highlight_block[4].x=-FromFIXED(map->xPhysicalOrigin+((map_x)*map->blockSize));

	highlight_block[0].y=highlight_block[4].y=-(mapBlockValue(map, map_x, map_y).topLeftAlt);
	highlight_block[0].z=highlight_block[4].z=FromFIXED(map->yPhysicalOrigin+((map_y)*map->blockSize));

	highlight_block[1].x=-FromFIXED(map->xPhysicalOrigin+((map_x+1)*map->blockSize));
	highlight_block[1].y=-mapBlockValue(map, map_x+1, map_y).topLeftAlt;
	highlight_block[1].z=FromFIXED(map->yPhysicalOrigin+((map_y)*map->blockSize));

	highlight_block[2].x=-FromFIXED(map->xPhysicalOrigin+((map_x+1)*map->blockSize));
	highlight_block[2].y=-mapBlockValue(map, map_x+1, map_y+1).topLeftAlt;
	highlight_block[2].z=FromFIXED(map->yPhysicalOrigin+((map_y+1)*map->blockSize));

	highlight_block[3].x=-FromFIXED(map->xPhysicalOrigin+((map_x)*map->blockSize));
	highlight_block[3].y=-mapBlockValue(map, map_x, map_y+1).topLeftAlt;
	highlight_block[3].z=FromFIXED(map->yPhysicalOrigin+((map_y+1)*map->blockSize));

	qDraw_WorldLineListEx(NULL,&highlight_block[0],&highlight_block[1],4, red,green,0,0);
#endif

#ifdef 0
/* mark selected vehicle with a flashing triangle */

	{
		SVECTOR	vector;
		short		coords[3];
		long		depth,flag;

		vector.vx=position.x;
		vector.vy=position.y;
		vector.vz=position.z;
		RotTransPers(&vector,(long*)&coords[0],&depth,&flag);


		/* a sprite here */

	}
#endif

}


/*
	draw a fake vector display wire-frame
	normally called after setting a new viewport

*/
void	draw_current_world(void)
{
}




/*
	if block is not dug ahead of vehicle, return TRUE and block coords, else return FALSE
*/
BOOL	get_dig_block(int *x, int *y)
{
#ifdef 0
	lpMap3D 			map=legoGlobs.currLevel->map;
	lpVehicle3D		vehicle=demo_vehicle.obj_list[demo_vehicle.object_index]->vehicle;
	VECTOR3D			position;
	int				block_size=FromFIXED(legoGlobs.currLevel->blockSize);
	int				mapx,mapy;
	int				centre_height;
	int				left,below;
	REAL				xd,yd;
	int				dug;
	int				forward_rad[4]={300,80,200,80};

/* forward position */


	Container_GetWorldPosition(vehicle->bodyCont,&position);
	xd=csin(demo_vehicle.angle);
	yd=ccos(demo_vehicle.angle);
	position.x-=FromFIXED(Asm_MulFIX(ToFIXED(forward_rad[vehicle->id]),xd));
	position.y+=FromFIXED(Asm_MulFIX(ToFIXED(forward_rad[vehicle->id]),yd));
	mapx=position.x/block_size;
	mapy=position.y/block_size;


/* use cursor position for now */

//	mapx=demo_vehicle.x/block_size;
//	mapy=demo_vehicle.y/block_size;


	if (mapx==0 || mapy==0)
		return	FALSE;

	dug=blockValue(legoGlobs.currLevel, mapx, mapy).flags & LEGOBLOCK_FLAG_BLOCK_DUG;

	if (!(blockValue(legoGlobs.currLevel, mapx, mapy).flags & LEGOBLOCK_FLAG_BLOCK_DUG))
	{
		*x=mapx;
		*y=mapy;

		return	TRUE;
	}
#endif

	return	FALSE;

}


BOOL	get_dig_block_from_position(int *x, int *y)
{
	lpMap3D 			map=legoGlobs.currLevel->map;
	VECTOR3D			position;
	int				mapx,mapy;


	mapx=*x>>9;
	mapy=*y>>9;

	if (mapx==0 || mapy==0 || mapx==map->blocksWide-1 || mapy==map->blocksHigh-1)
		return	FALSE;

	if (!(blockValue(legoGlobs.currLevel, mapx, mapy).flags & LEGOBLOCK_FLAG_BLOCK_DUG))
	{
		*x=mapx;
		*y=mapy;

		return	TRUE;
	}

	return	FALSE;

}






/* make camera look at container */
void	set_camera_on_container(lpContainer camera_container, lpContainer viewed_container, VECTOR3D *cpos)
{
	VECTOR3D		pos, prj;
	LPVECTOR3D	cam=camera_container->modelData;
	LPDIRECT3DRMMESH	mesh = viewed_container->modelData;

	Container_GetWorldPosition(viewed_container,&pos);

/* where camera is looking */
	G3D_SetVector(cam, -pos.x,pos.z,pos.y);


/* camera is looking at position of object */

	cam_look_x=pos.x;
	cam_look_z=pos.y;
	cam_look_y=pos.z;

/* camera position (offset from cam_look) */

	G3D_SetVector(&camera_container->coords.pos, -(pos.x+cpos->x),pos.z-cpos->z,pos.y+cpos->y);

}


/*
	set camera at pos, looking at look_pos
*/
void	set_camera_on_position(lpContainer camera_container, VECTOR3D *pos, VECTOR3D *look_pos)
{
	LPVECTOR3D			cam=camera_container->modelData;

/* where camera is looking */

	G3D_SetVector(cam, -look_pos->x,look_pos->z,look_pos->y);

/* where camera is positioned (offset from look_pos) */

	G3D_SetVector(&camera_container->coords.pos, -(look_pos->x+pos->x),look_pos->z-pos->z,look_pos->y+pos->y);

}






/*
		determine new world mesh from position of camera viewpoint
*/
void	rebuild_world_mesh(lpContainer cam_cont)
{
				int				tmap_x,tmap_y;
				int				block_size;
				LPVECTOR3D		cam=cam_cont->modelData;
				BOOL				changed=FALSE;
	static	VECTOR3D			old_cam;


	if ((cam->x!=old_cam.x) || (cam->y!=old_cam.y) || (cam->z!=old_cam.z))
	{
		changed=TRUE;
		old_cam.x=cam->x;		/* cache camera position */
		old_cam.y=cam->y;
		old_cam.z=cam->z;
	}

	block_size=FromFIXED(legoGlobs.currLevel->blockSize);
	tmap_x=(-cam->x)/block_size;	
	tmap_y=cam->z/block_size;

	tmap_x-=((surfaceGlobs.vertexSpan-1)>>1);
	tmap_y-=((surfaceGlobs.vertexSpan-1)>>1);

	if (tmap_x<0)
		tmap_x=0;
	if (tmap_x>legoGlobs.currLevel->width-(surfaceGlobs.vertexSpan))
		tmap_x=legoGlobs.currLevel->width-(surfaceGlobs.vertexSpan);

	if (tmap_y<0)
		tmap_y=0;
	if (tmap_y>legoGlobs.currLevel->height-(surfaceGlobs.vertexSpan))
		tmap_y=legoGlobs.currLevel->height-(surfaceGlobs.vertexSpan);

	Surface_rebuildWorldQuadList(legoGlobs.currLevel, tmap_x,tmap_y,changed);

	//rebuildVertexBuffer(legoGlobs.currLevel,tmap_x,tmap_y,TRUE);		/* full re-build for now */
	//rebuildRadarQuadList(legoGlobs.currLevel,tmap_x,tmap_y);

	//simple_clip_vehicles(tmap_x,tmap_y);

}



/*
		a quick and dirty clip to turn off
		vehicles that aren't on the world grid
*/
void	simple_clip_vehicles(int tmapx, int tmapy)
{
#ifdef 0
	int				n,mapx,mapy;
	VECTOR3D			position;
	lpVehicle3D		vehicle;
	int				block_size;
	int				mwidth,mheight;

	block_size=FromFIXED(legoGlobs.currLevel->blockSize);
	mwidth=legoGlobs.currLevel->width-surfaceGlobs.vertexSpan-1;
	mheight=legoGlobs.currLevel->height-surfaceGlobs.vertexSpan-1;

	for (n=0; n<craftGlobs.craftPool.numCraft; n++)
	{
		if (vehicle=craftGlobs.craftPool.list[n]->vehicle)
		{
			Container_GetWorldPosition(vehicle->bodyCont,&position);
			mapx=position.x/block_size-tmapx;
			mapy=position.y/block_size-tmapy;

		 	if (mapx<0 || mapx>=(surfaceGlobs.vertexSpan-1) || mapy<0 || mapy>=(surfaceGlobs.vertexSpan-1))
				Container_Hide(vehicle->bodyCont, TRUE);
			else
				Container_Hide(vehicle->bodyCont, FALSE);		/* on the map */
		}
	}

	for (n=0; n<MAX_LM; n++)
	{
		Container_GetWorldPosition(lmlist[n].cont,&position);
		mapx=position.x/block_size-tmapx;
		mapy=position.y/block_size-tmapy;

		if (mapx<0 || mapx>=(surfaceGlobs.vertexSpan-1) || mapy<0 || mapy>=(surfaceGlobs.vertexSpan-1))
			Container_Hide(lmlist[n].cont, TRUE);
		else
			Container_Hide(lmlist[n].cont, FALSE);		/* on the map */

	}
#endif
}






/* display area of vram as a sprite */
void show_texture_page(void)
{
#ifdef 0
	long			tx,ty,cx,cy,x,y;
	unsigned 	short	tpage;
	Uint16		old_pad,delta,mode=1;
	GsSPRITE		s;
	GsBOXF		box;

	tx=0;
	ty=-64;

	cx=512;
	cy=495;

	while(1)
	{
		Input_PadRead(0);
		if (!(Input_PadData(0) & PAD_START))
			break;
	}


	DrawSync(0);
	VSync(0);

	while(1)
	{
		Gfx_StartDraw();

		Input_PadRead(0);

		if (Input_PadData(0) & PAD_START)		/* exit */
			break;


		if (Input_PadData(0) & PAD_SEL)		/* speed of movement */
			delta=8;
		else
			delta=1;

		if (Input_PadData(0) & PAD_FLT)
		{
			if (Input_PadData(0)!=old_pad)
			{
		 		old_pad=Input_PadData(0);
				mode++;
				mode&=1;
			}
		}
		else
			old_pad=0;

/* texture */

		if (Input_PadData(0) & PAD_LL)
			tx-=delta;

		if (Input_PadData(0) & PAD_LR)
			tx+=delta;

		if (Input_PadData(0) & PAD_LU)
			ty-=delta;

		if (Input_PadData(0) & PAD_LD)
			ty+=delta;

/* CLUT */

		if (Input_PadData(0) & PAD_RL)
			cx=MAX(cx-16, gfxGlobs.scrW);

		if (Input_PadData(0) & PAD_RR)
			cx=MIN(cx+16, 1024-16);

		if (Input_PadData(0) & PAD_RU)
			cy=MAX(cy-delta, 0);

		if (Input_PadData(0) & PAD_RD)
			cy=MIN(cy+delta, 511);


		box.x=-(gfxGlobs.scrW>>1);
		box.y=-(gfxGlobs.scrH>>1);
		box.w=gfxGlobs.scrW;
		box.h=64;
		box.r=box.g=box.g=0;
		box.attribute=(GsALON);	// | GsAONE);		/* semi trans enabled, blend of 100% background + 100% foreground */
		GsSortBoxFill(&box, &gfxGlobs.Wot[gfxGlobs.bufID], 10);
					
		Font_PrintF(legoGlobs.stdFont,10,8,"texture x=%d,y=%d",tx,ty);
		Font_PrintF(legoGlobs.stdFont,10,16,"clut x=%d,y=%d",cx,cy);
		if (mode==0)
			Font_PrintF(legoGlobs.stdFont,10,32,"mode:  16 colours");
		else
			Font_PrintF(legoGlobs.stdFont,10,32,"mode: 256 colours");

		for (y=0; y<2; y++)
		{
			for (x=0; x<5; x++)
			{
				s.w = 256;
				s.h = 256;
				s.u = 0;
				s.v = 0;
				s.tpage=getTPage(mode,1,384+(x*128),y*256);

				s.cx = cx;
				s.cy = cy;
				s.mx = s.my = s.rotate = NULL;
				s.scalex = s.scaley = ONE;

				s.r = s.g = s.b = 128;
				s.x = (-tx+(x*256))-(gfxGlobs.scrW>>1);
				s.y = (-ty+(y*256))-(gfxGlobs.scrH>>1);
				if (mode==0)
					s.attribute = 0x00000000;
				else
					s.attribute = 0x01000000;

				GsSortFastSprite(&s, &gfxGlobs.Wot[gfxGlobs.bufID], 11);
			}
		}

		Gfx_ScreenFlip();
		Viewport_SetActive(legoGlobs.mainView);
	}

	while(1)
	{
		Input_PadRead(0);
		if (!(Input_PadData(0) & PAD_START))
			break;
	}

#endif
}


/* display vram in low res */

void	show_vram(void)
{
	static Uint16	slidex=0,slidey=0;

#ifdef 0
	DrawSync(0);
	VSync(0);

	while(1)
	{
		Input_PadRead(0);
	  	GsDefDispBuff(slidex,slidey,slidex,slidey);

		if (Input_PadData(0) & PAD_LL)
			slidex=MAX(slidex-8, 0);

		if (Input_PadData(0) & PAD_LR)
			slidex=MIN(slidex+8, 1024-gfxGlobs.scrW);

		if (Input_PadData(0) & PAD_LU)
			slidey=MAX(slidey-8, 0);

		if (Input_PadData(0) & PAD_LD)
			slidey=MIN(slidey+8, 512-gfxGlobs.scrH);


		VSync(0);					/* WAIT FOR VBLANK */
		GsSwapDispBuff();			/* EXCHANGE DISPLAY AND DRAWING BUFFER */
		ResetGraph(1);				/* RESET GPU */


		if (Input_PadData(0) & PAD_START)
			break;
	}
#endif
}



void	display_box(int x, int y)
{
	GsLINE	l;


	l.attribute=0;
	l.x0=(x*6)-(gfxGlobs.scrW>>1);
	l.y0=(y*6)-(gfxGlobs.scrH>>1);
	l.x1=((x+1)*6-1)-(gfxGlobs.scrW>>1);
	l.y1=(y*6)-(gfxGlobs.scrH>>1);
		
	if (!(blockValue(legoGlobs.currLevel, x, y).flags & LEGOBLOCK_FLAG_FLOOR))
	{
		l.r=255;
		l.g=0;
		l.b=0;
	}
	else
	{
		l.r=255;
		l.g=255;
		l.b=255;
	}
	GsSortLine(&l, &gfxGlobs.Wot[gfxGlobs.bufID], 10);
	l.x0=l.x1;
	l.y0=l.y1;
	l.y1+=5;
	GsSortLine(&l, &gfxGlobs.Wot[gfxGlobs.bufID], 10);
	l.x0=l.x1;
	l.y0=l.y1;
	l.x1-=5;
	GsSortLine(&l, &gfxGlobs.Wot[gfxGlobs.bufID], 10);
	l.x0=l.x1;
	l.y0=l.y1;
	l.y1-=5;		
	GsSortLine(&l, &gfxGlobs.Wot[gfxGlobs.bufID], 10);
}



void	display_cross(int x, int y)
{
	GsLINE	l;


	l.attribute=0;
	l.x0=(x*6)-(gfxGlobs.scrW>>1);
	l.y0=(y*6)-(gfxGlobs.scrH>>1);
	l.x1=((x+1)*6-1)-(gfxGlobs.scrW>>1);
	l.y1=((y+1)*6-1)-(gfxGlobs.scrH>>1);
		
	if (!(blockValue(legoGlobs.currLevel, x, y).flags & LEGOBLOCK_FLAG_FLOOR))
	{
		l.r=255;
		l.g=0;
		l.b=0;
	}
	else
	{
		l.r=255;
		l.g=255;
		l.b=255;
	}

	GsSortLine(&l, &gfxGlobs.Wot[gfxGlobs.bufID], 10);
	l.x0+=5;
	l.x1-=5;
	GsSortLine(&l, &gfxGlobs.Wot[gfxGlobs.bufID], 10);

}
	


void	test_routefind(void)
{
#ifdef 0
	int				startx=1,starty=1;
	int				endx=2 ,endy=2;
	int				width=legoGlobs.currLevel->map->blocksWide;
	int				height=legoGlobs.currLevel->map->blocksHigh;
	lpLegoObject	object=demo_vehicle.obj_list[demo_vehicle.object_index];
	ULONG				rlength;

	while(1)
	{
		Input_PadRead(0);
		if (!(Input_PadData(0) & PAD_START))
			break;
	}


	DrawSync(0);
	VSync(0);

	while(1)
	{
		Gfx_StartDraw();

		Input_PadRead(0);


/* start */

		if (Input_PadData(0) & PAD_LL)
		{
			startx--;
			if (startx<0)
				startx=0;
		}

		if (Input_PadData(0) & PAD_LR)
		{
			startx++;
			if (startx>width)
				startx=width;
		}

		if (Input_PadData(0) & PAD_LU)
		{
			starty--;
			if (starty<0)
				starty=0;
		}

		if (Input_PadData(0) & PAD_LD)
		{
			starty++;
			if (starty>height)
				starty=height;
		}



/* end */

		if (Input_PadData(0) & PAD_RL)
		{
			endx--;
			if (endx<0)
				endx=0;
		}

		if (Input_PadData(0) & PAD_RR)
		{
			endx++;
			if (endx>width)
				endx=width;
		}

		if (Input_PadData(0) & PAD_RU)
		{
			endy--;
			if (endy<0)
				endy=0;
		}

		if (Input_PadData(0) & PAD_RD)
		{
			endy++;
			if (endy>height)
				endy=height;
		}






		if (Input_PadData(0) & PAD_START)		/* exit */
			break;


		if ((Input_PadData(0) & PAD_SEL))		/* exit */
		{
			LPUCHAR	xpos,ypos;
			ULONG		n;

			if (LegoObject_RouteFind(object,startx,starty,endx,endy,&xpos,&ypos,&rlength)==FALSE)
				rlength=0;

			/* now we can fill in the new test route */

			if (rlength>0)
			{
				if (object->routeList)
					Mem_Free(object->routeList);
				object->routeList=Mem_Malloc(rlength*sizeof(LegoObject_Route));

				for (n=0; n<rlength; n++)
				{
					object->routeList[n].xBlock=xpos[n];
					object->routeList[n].yBlock=ypos[n];
				}
				object->routeLength=rlength;
				Mem_Free(xpos);
				Mem_Free(ypos);
			}

			while(1)			/* wait for select release */
			{
				Input_PadRead(0);
				if (!(Input_PadData(0) & PAD_SEL))
					break;
			}

		}

		display_box(startx,starty);
		display_cross(endx,endy);
		display_map(object);

		Gfx_ScreenFlip();
		Viewport_SetActive(legoGlobs.mainView);
	}

	while(1)
	{
		Input_PadRead(0);
		if (!(Input_PadData(0) & PAD_START))
			break;
	}

#endif
}









#define		SLIDE_DELTA			(128)
#define		SPEED_DELTA			(8)
#define		MAX_SPEED			(128)
#define		TURN_DELTA			(64)
#define		SLOW_RATE			(4)
#define		MAX_DRILL_SPEED	(1024)
#define		DRILL_SPEED_DELTA	(32)
#define		DRILL_SLOW_DELTA	(16)



#ifdef MAPEDIT

#define		ME_BLOCK_DELTA		(64)

/*
	allow various tweaks of the map in order to beautify it somewhat.

	vertex offset manipulation
	vertex colour and lightvalue

*/
void	Steve_MapEdit(void)
{
	int					blockX,blockY;
	lpLego_Block		block;
	lpCONTROL			control=objectGlobs.playerList[0].controlSet;
	char					string[128];
	int					speed=ME_BLOCK_DELTA;




	if (PAD_EVENT(control,CONTROL_START))
	{
		CLEAR_EVENT_IMMEDIATE(control,CONTROL_START);
		speed<<=1;
	}

	if (PAD_EVENT(control,CONTROL_SELECT))
	{
		CLEAR_EVENT_RELEASE(control,CONTROL_SELECT);
		
#ifdef SCOTTS_EDITOR
		mapeditGlobs.mode = EM_OBJ_EDITOR;
#else
		mapeditGlobs.mode = EM_OFF;
#endif
	
	/* clear all joypad events */
		Control_initialiseControlSet(objectGlobs.playerList[0].controlSet);

		return;
	}


	if (PAD_EVENT(control,CONTROL_SYS_LEFT_TOP_SHOULDER))
	{
		CLEAR_EVENT_RELEASE(control,CONTROL_SYS_LEFT_TOP_SHOULDER);
		if (mapeditGlobs.mode>EM_VERTEX_OFFSET)
			mapeditGlobs.mode--;
	}

	if (PAD_EVENT(control,CONTROL_SYS_LEFT_BOTTOM_SHOULDER))
	{
		CLEAR_EVENT_RELEASE(control,CONTROL_SYS_LEFT_BOTTOM_SHOULDER);
		if (mapeditGlobs.mode<EM_SAVE)
			mapeditGlobs.mode++;
	}




	if (PAD_EVENT(control,CONTROL_TURN_LEFT))
	{
	 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_TURN_LEFT);
		mapeditGlobs.vx-=speed;
		if (mapeditGlobs.vx<0)
			mapeditGlobs.vx=0;
	}

	if (PAD_EVENT(control,CONTROL_TURN_RIGHT))
	{
	 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_TURN_RIGHT);
		mapeditGlobs.vx+=speed;

		/* cap for size here... */
	}

	if (PAD_EVENT(control,CONTROL_FORWARD))
	{
	 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_FORWARD);
		mapeditGlobs.vy-=speed;
		if (mapeditGlobs.vy<0)
			mapeditGlobs.vy=0;
	}

	if (PAD_EVENT(control,CONTROL_REVERSE))
	{
	 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_REVERSE);
		mapeditGlobs.vy+=speed;

		/* cap for size here... */
	}


	blockX=mapeditGlobs.vx>>9;
	blockY=mapeditGlobs.vy>>9;
	block=&blockValue(legoGlobs.currLevel,blockX,blockY);


	if (mapeditGlobs.mode==EM_VERTEX_OFFSET)
	{
		if (PAD_EVENT(control,CONTROL_SYS_SQUARE))
		{
		 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_SQUARE);
			block->xoff+=4;				
			Lego_RecalculateVertexAngles();
		}

		if (PAD_EVENT(control,CONTROL_SYS_CIRCLE))
		{
		 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_CIRCLE);
			block->xoff-=4;				
			Lego_RecalculateVertexAngles();
		}

		if (PAD_EVENT(control,CONTROL_SYS_TRIANGLE))
		{
		 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_TRIANGLE);
			block->yoff-=4;				
			Lego_RecalculateVertexAngles();
	}

		if (PAD_EVENT(control,CONTROL_SYS_CROSS))
		{
		 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_CROSS);
			block->yoff+=4;				
			Lego_RecalculateVertexAngles();
		}

/* height adjustment - just for testing as it's not saved at present */

		if (PAD_EVENT(control,CONTROL_SYS_RIGHT_TOP_SHOULDER))
		{
		 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_RIGHT_TOP_SHOULDER);
			block->topLeftAlt+=16;
		}

		if (PAD_EVENT(control,CONTROL_SYS_RIGHT_BOTTOM_SHOULDER))
		{
		 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_RIGHT_BOTTOM_SHOULDER);
			block->topLeftAlt-=16;
		}



	}


	if (mapeditGlobs.mode==EM_COLOUR_LIGHT)
	{
		int delta=0,colour;

		if (PAD_EVENT(control,CONTROL_SYS_RIGHT_TOP_SHOULDER))
		{
		 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_RIGHT_TOP_SHOULDER);
			delta=1;
		}

		if (PAD_EVENT(control,CONTROL_SYS_RIGHT_BOTTOM_SHOULDER))
		{
		 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_RIGHT_BOTTOM_SHOULDER);
			delta=-1;
		}


/* red */
		if (PAD_EVENT(control,CONTROL_SYS_SQUARE))
		{
		 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_SQUARE);
			colour=block->red;
			colour+=delta;
			if (colour<0)
				colour=0;
			if (colour>255)
				colour=255;
			block->red=colour;
		}

/* blue */
		if (PAD_EVENT(control,CONTROL_SYS_CIRCLE))
		{
		 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_CIRCLE);
			colour=block->blue;
			colour+=delta;
			if (colour<0)
				colour=0;
			if (colour>255)
				colour=255;
			block->blue=colour;
		}

/* green */
		if (PAD_EVENT(control,CONTROL_SYS_TRIANGLE))
		{
		 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_TRIANGLE);
			colour=block->green;
			colour+=delta;
			if (colour<0)
				colour=0;
			if (colour>255)
				colour=255;
			block->green=colour;
		}

/* lighting value */

		if (PAD_EVENT(control,CONTROL_SYS_CROSS))
		{
		 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_CROSS);
			colour=block->lightSetting;
			colour+=delta;
			if (colour<0)
				colour=0;
			if (colour>255)
				colour=255;
			block->lightSetting=colour;
		}

		Surface_SetLightPoint(blockX, blockY, 0,0,0);


	}


/* miscellaneous settings */

	if (mapeditGlobs.mode==EM_MISC)
	{


	/* texture direction */

		if (PAD_EVENT(control,CONTROL_SYS_SQUARE))
		{	
		 	CLEAR_EVENT_RELEASE(control,CONTROL_SYS_SQUARE);
			block->direction++;			
			block->direction&=3;			
		}


	/* quad split direction */

		if (PAD_EVENT(control,CONTROL_SYS_TRIANGLE))
		{	
		 	CLEAR_EVENT_RELEASE(control,CONTROL_SYS_TRIANGLE);
			if (block->flags & MAP3DBLOCK_FLAGROTATED)
				block->flags &=~MAP3DBLOCK_FLAGROTATED;
			else
				block->flags |=MAP3DBLOCK_FLAGROTATED;
		}

	/* use transform z toggle */

		if (PAD_EVENT(control,CONTROL_SYS_CIRCLE))
		{	
		 	CLEAR_EVENT_RELEASE(control,CONTROL_SYS_CIRCLE);
			if (block->flags & LEGOBLOCK_FLAG_USE_TRANS_Z)
				block->flags &=~LEGOBLOCK_FLAG_USE_TRANS_Z;
			else
				block->flags |=LEGOBLOCK_FLAG_USE_TRANS_Z;
		}


	}




	if (mapeditGlobs.mode==EM_LOAD)
	{
		if (PAD_EVENT(control,CONTROL_SYS_CIRCLE))
		{
		 	CLEAR_EVENT_RELEASE(control,CONTROL_SYS_CIRCLE);
			if (PAD_EVENT(control,CONTROL_SYS_SQUARE))
			{	
				char	modMapName[128];
			 	CLEAR_EVENT_RELEASE(control,CONTROL_SYS_SQUARE);

				sprintf(modMapName,"%sterrain.mod",legoGlobs.levelPath);
				Lego_LoadModMap(modMapName);
			}
		}
	}

	if (mapeditGlobs.mode==EM_SAVE)
	{
		char				pathname[128];
		int				handle;
		int				count;
		lpLego_Block	legoBlock;
		MODBLOCK2		*modBlock2,*tempModBlock2;

		int				mapWidth,mapHeight,x,y;

		if (PAD_EVENT(control,CONTROL_SYS_CIRCLE))
		{
		 	CLEAR_EVENT_RELEASE(control,CONTROL_SYS_CIRCLE);
			if (PAD_EVENT(control,CONTROL_SYS_SQUARE))
			{	
			 	CLEAR_EVENT_RELEASE(control,CONTROL_SYS_SQUARE);

				mapWidth=legoGlobs.currLevel->width;
				mapHeight=legoGlobs.currLevel->height;

				modBlock2=Mem_Malloc(mapWidth*mapHeight*sizeof(MODBLOCK2));
				if (modBlock2)
				{
					tempModBlock2=modBlock2;
					legoBlock=legoGlobs.currLevel->blockData;


				/* make the mod map */

					for (y=0; y<mapHeight; y++)
					{
						for (x=0; x<mapWidth; x++)
						{
							tempModBlock2->red=legoBlock->red;
							tempModBlock2->green=legoBlock->green;
							tempModBlock2->blue=legoBlock->blue;
							tempModBlock2->lightSetting=legoBlock->lightSetting;
							tempModBlock2->xoff=legoBlock->xoff;
							tempModBlock2->yoff=legoBlock->yoff;
							tempModBlock2->zoff=legoBlock->topLeftAlt;
							tempModBlock2->direction=legoBlock->direction;
							tempModBlock2->flags=legoBlock->flags;
							tempModBlock2++;

							legoBlock++;
						}
					}

					PCinit();

					sprintf(pathname, "%s\\%s\\%sterrain.mod", _DEBUGPATH, "CD_ROOT\\DATA",legoGlobs.levelPath);
					handle=PCcreat(pathname,0);
					if (handle!=-1)
					{
						count=PCwrite(handle,(void*) modBlock2,(mapWidth*mapHeight*sizeof(MODBLOCK2)));
						PCclose(handle);
					}

					Mem_Free(modBlock2);
				}
			}
		}
	}




#define ME_PDY	(192)

/* print details */

	sprintf(string, "block: %02d, %02d  (%d,%d)", blockX,blockY,mapeditGlobs.vx,mapeditGlobs.vy);
	Font_PrintF(legoGlobs.stdFont,8,ME_PDY-12,string);

	sprintf(string, "vertex offset: %d, %d, %d", block->xoff,block->yoff,block->topLeftAlt);
	Font_PrintF(legoGlobs.stdFont,16,ME_PDY,string);
	
	sprintf(string, "colour: |1%03d |2%03d |6%03d |7%03d", block->red,block->green,block->blue,block->lightSetting);
	Font_PrintF(legoGlobs.stdFont,16,ME_PDY+8,string);

	sprintf(string, "dir:%d  split:",block->direction);
	if (block->flags & MAP3DBLOCK_FLAGROTATED)
		strcat(string,"\\ tsz:");
	else
		strcat(string,"/ tsz:");

	if (block->flags & LEGOBLOCK_FLAG_USE_TRANS_Z)
		strcat(string,"Yes");
	else
		strcat(string,"No");
						
	Font_PrintF(legoGlobs.stdFont,16,ME_PDY+16,string);
	
	Font_PrintF(legoGlobs.stdFont,16,ME_PDY+24,"Load modmap");
	Font_PrintF(legoGlobs.stdFont,16,ME_PDY+32,"Save modmap");

	sprintf(string, "File: %sterrain.mod", legoGlobs.levelPath);
	Font_PrintF(legoGlobs.stdFont,16,ME_PDY+48,string);

	if ((legoGlobs.vblankCount & 8)==8)
		Font_PrintF(legoGlobs.stdFont,8,ME_PDY+((mapeditGlobs.mode-1)*8),">");



	sprintf(string,"N=%d",block->north);
	Font_PrintF(legoGlobs.stdFont,224,ME_PDY+16,string);

	sprintf(string,"W=%d",block->west);
	Font_PrintF(legoGlobs.stdFont,192,ME_PDY+24,string);

	sprintf(string,"E=%d",block->east);
	Font_PrintF(legoGlobs.stdFont,260,ME_PDY+24,string);

	sprintf(string,"S=%d",block->south);
	Font_PrintF(legoGlobs.stdFont,224,ME_PDY+32,string);


	DRAW_SEMI_TRANS_GREY_BOX(0,ME_PDY-16,384,75);

}


#endif /* <MAP_EDIT> */

