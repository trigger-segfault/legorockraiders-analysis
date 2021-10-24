//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// PSX GODS '98 test code
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Include all Header Files
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
#include	"..\inc\globals.h"


#include "libpad.h"






#define		XCOUNT	(100)
#define		YCOUNT	(800)


LPUCHAR		_DEBUGPATH = "D:\\TESTBED";
#define		__PAL

void	shock_test(void);
int setup_shock_test(void);

void	draw_line(int	x1,int y1, int x2, int y2);
void	init_star_field(void);
void	update_star_field(void);
void show_texture_page(void);
int	play_sfx(int	sfx_num,int freq, int volume);
void initialise_test_sound(void);

DR_AREA	draw_areap1;
DR_AREA	draw_areap2;
RECT		clip1={0,0,100,100};
RECT		clip2={100,100,100,100};

GsFOGPARAM	fog;

#define			MAX_WQ	(5)
#define			VERTEXSPAN			(6)
#define			WORLDVERTICES		(VERTEXSPAN*(6))

POLY_FT4		worldQuadList[2][MAX_WQ*MAX_WQ];
POLY_F4			worldQuadListFlat[2][MAX_WQ*MAX_WQ];

/*
	these are now global to allow optimization
*/
DVECTOR			outputList[WORLDVERTICES];
long				szList[WORLDVERTICES];


void	initialiseWorldQuadList(void);
void	rebuildRadarQuadList(Sint16 mx, Sint16 my);
VOID	rebuildVertexBuffer(Sint16 mx, Sint16 my);

void	test_gte_function(void);


unsigned char	padBuffer1[34];
unsigned char	padBuffer2[34];


lpImage	test_texture;

typedef	struct
{
	ANGLE		angle;
	REAL		x;	
	REAL		y;	
	REAL		z;
	REAL		speed;
	ANGLE		wheel_spin;

}	VEHICLE_DATA;


VEHICLE_DATA	demo_vehicle;

void	init_demo_vehicle(void)
{
	demo_vehicle.x=0;
	demo_vehicle.y=0;
	demo_vehicle.z=0;
	demo_vehicle.speed=0;
	demo_vehicle.wheel_spin=0;
}






SPR_ACTIVITY_SET		*minifigure_activites;
SPR_ACTIVITY_SET		*snake_activites;
SPR_ACTIVITY_SET		*spider_activites;
SPR_ACTIVITY_SET		*scorpion_activites;

int			legoman_frame=0;
int			rotate=0;
int			frame_size=256;

Uint16	testclut1[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
Uint16	testclut2[16]={31<<10,31<<10,31<<10,31<<10,31<<10,31<<10,31<<10,31<<10,31<<10,31<<10,31<<10,31<<10,31<<10,31<<10,31<<10,31<<10};


#define		MAX_LM	(2)

typedef struct lm_st
{
	lpContainer	cont;	
	int	xd;
	int	yd;
	int	angle;
	int	speed;

}	LM;

LM	lmlist[MAX_LM];

lpContainer test_flat;
lpContainer test_flat2;
lpContainer test_flat3;


test_Globs			testGlobs;
lpContainer		test_container=NULL;
lpContainer		child_container=NULL;
int					ambient=512;

lpViewport		main_viewport=NULL;
lpViewport		miniview_viewport=NULL;
lpContainer	main_camera=NULL;
lpContainer	miniview_camera=NULL;


/* test vars for container object manipulation */
REAL				mod_x=0,mod_y=0,mod_z=0;
REAL				rot_x=0,rot_y=0,rot_z=0;
int				anim_speed=HMD_NORMAL;
int				anim_toggle=0;

int				cam_pos_x=0;
int				cam_pos_y=-7600;
int				cam_pos_z=-200;

int				cam_look_x=0;
int				cam_look_y=0;
int				cam_look_z=0;

int				cam_y_rot=0;
int				cam_distance=6000;

#define	MAX_STARS	(256)

typedef struct
{
	long	x;
	long	y;
	long	z;

}	STAR;



STAR		star_field[MAX_STARS];

/* MOVE THESE LATER */

void	clut_change_test(void)
{
	static	int	frame_count=0;
				int	n;

	frame_count++;

	for (n=0; n<16; n++)
		testclut1[n]=frame_count;


		LoadClut2((ULONG*) &testclut1,832,249);
	//LoadClut2((ULONG*) &testclut2,832,249);
}




//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Start the system and tell the GODS lib
// where the game functions are
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
void	Gods_Go(void)
{
	Main_State	state;
	set_load_flag(FROM_PC);

	memset((Uint8*)&testGlobs, NULL, sizeof(test_Globs));
	state.Initialise = test_Initialise;
	state.MainLoop = test_MainLoop;
	state.Shutdown = test_Shutdown;

	#ifdef	__PAL		// sX   sY  oX oY FPS OTZ  F  PACKETBUFFER
	Main_SetEnvironment(384, 256, 0, 20, 50, 14, 1, 60000);
	#else
	Main_SetEnvironment(320, 240, 0, 14, 60, 10, 2, 60000);
	#endif

	testGlobs.gameName="hmd test";

	Main_SetState(&state);


	Gfx_SetClearScreenFlag(TRUE);

}


//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// This function is called from the GODS lib
// to initialise the game.
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹


BOOL	test_Initialise(void)
{



	Viewport_Initialise();
	Image_Initialise();
	TextWindow_Initialise();

	#ifdef	__PAL
	SetVideoMode(MODE_PAL);
	#endif

	testGlobs.stdFont = Font_Load("INTRFACE\\FONTS\\PSXFONT.TIM",0,8,10,10);
	{

/* we have to dick about with the text window 'cos it's now got an origin in the centre of the screen */

		AREA2D area = { 8-(gfxGlobs.scrW>>1), 8-(gfxGlobs.scrH>>1), 320-16, 200 };
		testGlobs.messageWin = TextWindow_Create(testGlobs.stdFont, &area, 4096);
 		TextWindow_PrintF(testGlobs.messageWin, "%s %s %s\n\n",testGlobs.gameName, __DATE__, __TIME__);
	}

	Image_LoadTIM("MASK.TIM");

	if(testGlobs.rootCont = Container_Initialise(testGlobs.gameName))
	{
		unsigned long	*load_file=NULL;	
		unsigned long	*load_file2=NULL;	
		void				*hmd_model=NULL;
		void				*hmd_model2=NULL;
		ULONG				file_size;

		load_file=File_LoadBinary("B_TICK.HMD",&file_size);
		//load_file=File_LoadBinary("WALKTEST.HMD",&file_size);



/* main camera */
		main_camera=Container_CreateCameraContainer(testGlobs.rootCont);
		main_viewport=Viewport_CreatePixel(0,0,384,256,main_camera);

/* miniview camera */
		miniview_camera=Container_CreateCameraContainer(testGlobs.rootCont);
		miniview_viewport=Viewport_CreatePixel(384-110,10,100,100,main_camera);


		if (load_file)
		{
			hmd_model=HMD_InitModel(load_file,NULL);

			if ((test_container=Container_ApplyMesh(testGlobs.rootCont,hmd_model,TYPE_HMD)))
			{
				LPDIRECT3DRMMESH  mesh = (LPDIRECT3DRMMESH)test_container->modelData;

				Container_SetParent(testGlobs.rootCont,test_container);
				printf("test container made");
				HMD_StartAnim(mesh->model,1,HMD_LOOP,anim_speed);

			}
			init_star_field();

			init_demo_vehicle();


			initialiseWorldQuadList();

			Gfx_SetVBlankCallback(clut_change_test);

			initialise_test_sound();


			setup_shock_test();

			return	TRUE;
		}
	}
	return FALSE;
}



void	update_lm(void)
{
				int				n;
				REAL				xd,zd;
				GsCOORDINATE2	coord;
				MATRIX			mat;
				short				coords[3];
				long				depth=14,flag;
				SVECTOR			vector;
				int				z;
				int				scale;
				int				set_flag;
				VECTOR3D			pos;
				Uint16			pad;

	static	int				frame=0;
	static 	Uint16 			old_pad;
	static	int				activity=0;
	static	int				brightness=255;

	static int freq=30,prog=0,last_voice=-1;
	char	string[64];


	pad=Input_PadData(0);

	set_flag=FALSE;

/*
	if (pad & PAD_START)
		Gfx_SetClearScreenFlag(TRUE);
	else
		Gfx_SetClearScreenFlag(FALSE);
*/

	if (pad!=old_pad)
	{


		old_pad=pad;
		if (pad & PAD_START)
		{
			/* change activity */

			activity++;
			if (activity==6)
				activity=0;
			set_flag=TRUE;
		}		



		if (pad & PAD_RU)
		{
			last_voice=play_sfx(prog,freq,127);
		}


		if (pad & PAD_RL)
			prog--;

		if (pad & PAD_RR)
			prog++;


		if (pad & PAD_FRT)
			freq++;

		if (pad & PAD_FRB)
			freq--;


	}



	if (pad & PAD_RU)
		frame_size+=8;

	if (pad & PAD_RD)
		frame_size-=8;
		

	for (n=0; n<MAX_LM; n++)
	{

		if (set_flag)
			Container_SetActivityByType(lmlist[n].cont,activity);

		Container_GetPosition(lmlist[n].cont,&pos);

		lmlist[n].angle+=32;
		lmlist[n].angle&=4095;


		xd=csin(lmlist[n].angle);
		zd=ccos(lmlist[n].angle);



		if (pad & PAD_SEL)
		{
			pos.x-=Asm_MulFIX(lmlist[n].speed,xd);
			pos.y-=Asm_MulFIX(lmlist[n].speed,zd);
		}

		if (pos.x<=-1600)
		{
			pos.x=-1600;
			lmlist[n].angle+=(rand()&1023)+64;
			lmlist[n].angle&=4095;
			
		}
		else if (pos.x>=1600)
		{
			pos.x=1600;
			lmlist[n].angle+=(rand()&1023)+64;
			lmlist[n].angle&=4095;
		}		

		if (pos.y<=-1600)
		{
			pos.y=-1600;
			lmlist[n].angle+=(rand()&1023)+64;
			lmlist[n].angle&=4095;
		}
		else if (pos.y>=1600)
		{
			pos.y=1600;
			lmlist[n].angle+=(rand()&1023)+64;
			lmlist[n].angle&=4095;
		}		

		lmlist[n].cont->scale=ONE<<2;

		Container_SetPosition(lmlist[n].cont,pos.x,pos.y,pos.z);
		Container_SetRotation(lmlist[n].cont,0,demo_vehicle.angle,0);
		Container_SpriteSetSpriteBrightness(lmlist[n].cont,brightness);
		Container_UpdateAnimation(lmlist[n].cont,1);
	}

	test_flat2->scale=ONE<<4;


	Container_SetRotation(test_flat,0,demo_vehicle.angle,0);
	Container_SetRotation(test_flat2,0,demo_vehicle.angle,0);
	Container_SetRotation(test_flat3,0,demo_vehicle.angle,0);
	Container_UpdateAnimation(test_flat,2);
	Container_UpdateAnimation(test_flat2,2);
	Container_UpdateAnimation(test_flat3,2);



	brightness++;
	brightness&=255;


	{
		GsSPRITE	s;
		unsigned short	tpage=getTPage(1,0,768,256);

		static int 					mask_brightness=128;
		static unsigned long		mask_attr=0x61000000;
		static unsigned short	tpage_attr=0;

		s.w = 192;
		s.h = 128;
		s.u = 0;
		s.v = 128;	//92;
		s.tpage=tpage;
		s.cx = 512;
		s.cy = 511;
	
		s.tpage=7;
		s.v=0;
		s.tpage|=tpage_attr;
		//s.cy = 509;
	
 		s.mx = s.my = s.rotate = NULL;
		s.scalex = s.scaley = ONE;


		//s.scalex = s.scaley = ONE<<2;

		s.r = s.g = s.b = mask_brightness;
		s.x = -192;
		s.y = -128;
		s.attribute = 0x00000000;
		s.attribute|= mask_attr;
		GsSortFastSprite(&s, &gfxGlobs.Wot[gfxGlobs.bufID], 11);
		s.x = NULL;
		s.attribute = 0x00800000;
		s.attribute|= mask_attr;
	  //	GsSortSprite(&s, &gfxGlobs.Wot[gfxGlobs.bufID], 11);
		s.x = -192;
		s.y = NULL;
		s.attribute = 0x00400000;
		s.attribute|= mask_attr;
	//	GsSortSprite(&s, &gfxGlobs.Wot[gfxGlobs.bufID], 11);
		s.x = NULL;
		s.attribute = 0x00c00000;
		s.attribute|= mask_attr;
//		GsSortSprite(&s, &gfxGlobs.Wot[gfxGlobs.bufID], 11);
	}

}

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// This function is called from the GODS lib
// to shut down the game.
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
void	test_Shutdown(void)
{
}



//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// This function is called from the GODS lib
// to actually run the game.
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
BOOL	test_MainLoop(REAL time)
{
	static	Uint16		old_pad;
				Uint16		pad;
				int			delta=0;

//	TextWindow_PrintF(testGlobs.messageWin, "mod_x=%d\n",mod_x);
	//TextWindow_Update(testGlobs.messageWin);
	gfxGlobs.fadeLevel=128;




	/* test setup of camera */

#ifdef 0
	{
					GsRVIEWUNIT	view;
					GsF_LIGHT	light;
		static	int			lr=0xd0,lg=0xd0,lb=0xd0;

		view.vpx=0,view.vpy=-1000,view.vpz=15000;
		view.vrx=0,view.vry=0,view.vrz=0;
		view.rz=0;
		view.super=WORLD;
//		GsSetRefViewUnit(&view);

		light.vx=100,light.vy=100,light.vz=-100;
		light.r=lr,light.g=lg,light.b=lb;
		GsSetFlatLight(0,&light);
		GsSetAmbient(512,512,512);
		GsSetLightMode(0);

		lb++;

	}

#endif


 	{
		GsF_LIGHT	light;

		static	int	lr=0xd0,lg=0xd0,lb=0xd0;
		static	int	lvx=100,lvy=100,lvz=-100;

		light.vx=lvx,light.vy=lvy,light.vz=lvz;
		light.r=lr,light.g=lg,light.b=lb;
		GsSetFlatLight(0,&light);
		GsSetLightMode(0);
		GsSetAmbient(ambient,ambient,ambient);

	}


#ifdef 0
 	{
		GsF_LIGHT	light;

		light.vx=100,light.vy=100,light.vz=100;
		light.r=0xd0,light.g=0xd0,light.b=0xd0;
		GsSetFlatLight(0,&light);
		GsSetLightMode(1);

		fog.rfc=255;
		fog.gfc=255;
		fog.bfc=255;
		GsSetFogParam(&fog);
		GsSetAmbient(ambient,ambient,ambient);

	}
#endif

	Viewport_Render(main_viewport, test_container, 1);
		
	show_world_grid();
	//show_lego_man();


	//Viewport_Render(miniview_viewport, test_container, 1);
	show_world_grid();

	rebuildVertexBuffer(-2,-2);
	//rebuildRadarQuadList(0,0);



	Font_PrintF(testGlobs.stdFont,8,226,"FPS: %d",gfxGlobs.last_fps);

	shock_test();


//	update_lm();
	rotate+=16384;

	pad=Input_PadData(0);
	if (pad!=old_pad)
	{
		old_pad=pad;
		if (pad & PAD_SEL)
		{
			legoman_frame++;
			legoman_frame&=7;
		}
	}




 	update_demo_vehicle();

//	update_star_field();

	pad=Input_PadData(0);

	pad=0;

	if (pad & PAD_SEL)
		delta=256;
	else
		delta=128;


	//if (pad & PAD_START)
	  //	show_texture_page();

/* camera look */

	if (pad & PAD_RL)
		fog.dqa-=8;
//		cam_look_x+=delta;

	if (pad & PAD_RR)
		fog.dqa+=8;
//		cam_look_x-=delta;

	if (pad & PAD_RU)
		fog.dqb-=64;
//		ambient+=32;
//		cam_look_z+=delta;

	if (pad & PAD_RD)
		fog.dqb+=64;
//		ambient-=32;
//		cam_look_z-=delta;




	if (pad & PAD_FRT)
		cam_look_y-=delta;

	if (pad & PAD_FRB)
		cam_look_y+=delta;

/* camera position */

	if (pad & PAD_LL)
		cam_pos_x+=delta;

	if (pad & PAD_LR)
		cam_pos_x-=delta;

	if (pad & PAD_LU)
		cam_pos_z-=delta;

	if (pad & PAD_LD)
		cam_pos_z+=delta;


/*
	if (pad & PAD_LL)
	{
		cam_y_rot+=delta>>4;
	}

	if (pad & PAD_LR)
	{
		cam_y_rot-=delta>>4;
	}


	if (pad & PAD_LU)
	{
		cam_distance-=delta;
	}

	if (pad & PAD_LD)
	{
		cam_distance+=delta;
	}
*/


//	cam_pos_x=cam_look_x+FromFIXED(Asm_MulFIX(rsin(cam_y_rot),ToFIXED(cam_distance)));
//	cam_pos_z=cam_look_x+FromFIXED(Asm_MulFIX(rcos(cam_y_rot),ToFIXED(cam_distance)));


	if (pad & PAD_FLT)
		cam_pos_y-=delta;

	if (pad & PAD_FLB)
		cam_pos_y+=delta;

	//demo_vehicle.angle+=64;
	//Container_SetPosition(test_container,NULL,demo_vehicle.x,demo_vehicle.y,demo_vehicle.z);
	//Container_SetRotation(test_container,NULL,0,demo_vehicle.angle,0,0);


/* set the camera position and viewpoint */

	//Container_SetCamera(main_camera,cam_pos_x,cam_pos_y,cam_pos_z,demo_vehicle.x,demo_vehicle.y, demo_vehicle.z);


#ifdef 0
/* show x/z line */
	draw_line(-4,0,4,0);
	draw_line(0,-4,0,4);
	draw_line(-(cam_look_x>>8), (cam_look_z>>8), -(cam_pos_x>>8), (cam_pos_z>>8));

	{
		int	cpx=-(cam_pos_x>>8),cpz=cam_pos_z>>8;

		draw_line(cpx-2,cpz-2,cpx+2,cpz+2);
		draw_line(cpx-2,cpz+2,cpx+2,cpz-2);
	}



/* show y line */

	draw_line(8-160,(cam_pos_y>>8), 64-160,(cam_look_y>>8));
	{
		int	cpy=(cam_pos_y>>8);

		draw_line(8-2-160,cpy-2,8+2-160,cpy+2);
		draw_line(8-2-160,cpy+2,8+2-160,cpy-2);
	}
#endif


//	test_gte_function();


	testSound();

	return TRUE;
}


/* draw white lines */
void	draw_line(int	x1,int y1, int x2, int y2)
{
	GsLINE	line;

	line.attribute=0;
	line.x0=x1;
	line.y0=y1;
	line.x1=x2;
	line.y1=y2;
	line.r=255;
	line.g=255;
	line.b=255;

	GsSortLine(&line,&gfxGlobs.Wot[gfxGlobs.bufID],0);
}


#define	FRACTION_SHIFT		(8)

long	global_z;


void	init_star_field(void)
{
	int	n;

	for (n=0; n<MAX_STARS; n++)
	{
		star_field[n].x=((rand()&511)-256)<<FRACTION_SHIFT;
		star_field[n].y=((rand()&511)-256)<<FRACTION_SHIFT;
		star_field[n].z=(rand()&255)+1;
	}


	global_z=1;
}


void	update_star_field(void)
{
	int		n,x1,y1,x2,y2;
	int		tz1,tz2;
	Uint16	pad=Input_PadData(0);


	if (pad & PAD_FRT)
		global_z++;

	if (pad & PAD_FRB)
	{
		global_z--;
		if (global_z<=0)
			global_z=1;
	}
		
	for (n=0; n<MAX_STARS; n++)
	{
		star_field[n].z+=1;


		tz1=star_field[n].z;	//+global_z;
		tz2=tz1+1;
		if (star_field[n].z>=(1<<8))
		{
			star_field[n].x=((rand()&511)-256)<<FRACTION_SHIFT;
			star_field[n].y=((rand()&511)-256)<<FRACTION_SHIFT;
			star_field[n].z=1;
		}

		x1=(star_field[n].x/tz1)>>FRACTION_SHIFT;
		y1=(star_field[n].y/tz1)>>FRACTION_SHIFT;

		x2=(star_field[n].x/tz2)>>FRACTION_SHIFT;
		y2=(star_field[n].y/tz2)>>FRACTION_SHIFT;

		//draw_line(x1,y1,x2,y2);
	}
}


#define		SLIDE_DELTA		(128)
#define		SPEED_DELTA		(8)
#define		MAX_SPEED		(128)
#define		TURN_DELTA		(32)
#define		SLOW_RATE		(4)

void	update_demo_vehicle(void)
{
	Uint16	pad=Input_PadData(0);
	int		delta;
	static	last_pad=0,index=1;

	if (pad & PAD_SEL)
		delta=256;
	else
		delta=128;


/* camera position */


/*
	if (pad & PAD_LL)
		cam_pos_x+=delta;

	if (pad & PAD_LR)
		cam_pos_x-=delta;

	if (pad & PAD_LU)
		cam_pos_z-=delta;

	if (pad & PAD_LD)
		cam_pos_z+=delta;

	if (pad & PAD_FLT)
		cam_pos_y-=delta;

	if (pad & PAD_FLB)
		cam_pos_y+=delta;
*/


	if (pad & PAD_LL)
		demo_vehicle.angle-=TURN_DELTA;

	if (pad & PAD_LR)
		demo_vehicle.angle+=TURN_DELTA;



	if (pad & PAD_LU)
	{
		demo_vehicle.speed+=SPEED_DELTA;
		if (demo_vehicle.speed>MAX_SPEED)
			demo_vehicle.speed=MAX_SPEED;
	}
 	if (pad & PAD_LD)
	{
		demo_vehicle.speed-=SPEED_DELTA;
		if (demo_vehicle.speed<-MAX_SPEED)
			demo_vehicle.speed=-MAX_SPEED;
	}

	if (demo_vehicle.speed>0)
	{
		demo_vehicle.speed-=SLOW_RATE;
		if (demo_vehicle.speed<0)
			demo_vehicle.speed=0;
	}
	else
	{
		demo_vehicle.speed+=SLOW_RATE;
		if (demo_vehicle.speed>0)
			demo_vehicle.speed=0;
	}
	
	if (demo_vehicle.speed!=0)
	{
		REAL	xd,zd;
		
		xd=csin(demo_vehicle.angle);
		zd=ccos(demo_vehicle.angle);
		demo_vehicle.x+=Asm_MulFIX(demo_vehicle.speed,xd);
		demo_vehicle.z+=Asm_MulFIX(demo_vehicle.speed,zd);
		demo_vehicle.wheel_spin+=demo_vehicle.speed;
	}	

	if (pad!=last_pad)
	{
		if (pad & PAD_FRT)
			index++;

		if (pad & PAD_FRB)
			index--;

		last_pad=pad;
	}

	Container_SetRotationIndex(test_container,12,-demo_vehicle.wheel_spin,0,0);
	Container_SetRotationIndex(test_container,13,-demo_vehicle.wheel_spin,0,0);
	Container_SetRotationIndex(test_container,14,-demo_vehicle.wheel_spin,0,0);
	Container_SetRotationIndex(test_container,15,-demo_vehicle.wheel_spin,0,0);

	Container_SetPosition(test_container,-demo_vehicle.x,demo_vehicle.z,demo_vehicle.y);
	Container_SetRotation(test_container,0,demo_vehicle.angle,0);
	
//set_camera_on_container(main_camera,test_container);


	Container_SetCamera(main_camera,cam_pos_x,cam_pos_y,cam_pos_z,0,0,0);

}



/* make camera look at container */
void	set_camera_on_container(lpContainer camera_container, lpContainer viewed_container)
{
	VECTOR3D		pos;
	LPVECTOR3D	cam=camera_container->modelData;

	Container_GetPosition(viewed_container,&pos);
	G3D_SetVector(&camera_container->coords.pos,cam_pos_x,cam_pos_y,cam_pos_z);
	G3D_SetVector(cam,-pos.x,pos.z,pos.y);
}


#define	SHIFT		(10)
#define	SPREAD	(2048)

void	show_world_grid(void)
{
	VECTOR2D	line_test[4];
	AREA2D	box_test[4];
	VECTOR3D	world_test[5];
	static	angle=0;
	int		size,n;

/* make a grid on the 'floor' */
	for (n=-5; n<5; n++)
	{

	/* horizontal */
		world_test[0].x=(-SPREAD);
		world_test[0].y=(0.0);
		world_test[0].z=-(n<<SHIFT);

		world_test[1].x=(SPREAD);
		world_test[1].y=(0.0);
		world_test[1].z=-(n<<SHIFT);
		Draw_WorldLineListEx(NULL,&world_test[0],&world_test[1],1, ToFIXED(1.0),ToFIXED(1.0),ToFIXED(1.0),DrawEffect_HalfTrans);

	/* vertical */
		world_test[0].x=(n<<SHIFT);
		world_test[0].y=(0.0);
		world_test[0].z=-SPREAD;

		world_test[1].x=(n<<SHIFT);
		world_test[1].y=(0.0);
		world_test[1].z=SPREAD;
		Draw_WorldLineListEx(NULL,&world_test[0],&world_test[1],1, ToFIXED(1.0),ToFIXED(1.0),ToFIXED(1.0),DrawEffect_HalfTrans);
	}
}



/* display area of vram as a sprite */
void show_texture_page(void)
{
	long			tx,ty,cx,cy,x,y;
	unsigned 	short	tpage;
	Uint16		old_pad,delta,mode=1;
	GsSPRITE		s;
	GsBOXF		box;

	tx=0;
	ty=0;

	cx=512;
	cy=495;

	//Image_LoadTIM("loading.tim");


	DrawSync(0);
	VSync(0);

	while(1)
	{
		Gfx_StartDraw();

		Input_PadRead(0);

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
			tx=MAX(tx-delta, 0);

		if (Input_PadData(0) & PAD_LR)
			tx=MIN(tx+delta, 1024-256);

		if (Input_PadData(0) & PAD_LU)
			ty=MAX(ty-delta, 0);

		if (Input_PadData(0) & PAD_LD)
			ty=MIN(ty+delta, 512-(256-64));

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
					
		Font_PrintF(testGlobs.stdFont,10,8,"texture x=%d,y=%d",tx,ty);
		Font_PrintF(testGlobs.stdFont,10,16,"clut x=%d,y=%d",cx,cy);
		if (mode==0)
			Font_PrintF(testGlobs.stdFont,10,32,"mode:  16 colours");
		else
			Font_PrintF(testGlobs.stdFont,10,32,"mode: 256 colours");

		for (y=0; y<2; y++)
		{
			for (x=0; x<4; x++)
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
				s.x = (-tx+(x*256))-192;
				s.y = (-ty+(y*256))-64;
				if (mode==0)
					s.attribute = 0x00000000;
				else
					s.attribute = 0x01000000;

				GsSortFastSprite(&s, &gfxGlobs.Wot[gfxGlobs.bufID], 11);
			}
		}

		Gfx_ScreenFlip();
		Viewport_SetActive(testGlobs.mainView);
	}
}



















/*
	rebuild the vertex buffer
*/
VOID	rebuildVertexBuffer(Sint16 mx, Sint16 my)
{

	int					x,y,index=0;
	long					*next=(long*) outputList;
	GsCOORDINATE2		coord;
	MATRIX				mat;
	long					depth=14,flag;
	SVECTOR				vector;
	static	int		s=0,ts;

	GsInitCoordinate2(WORLD, &coord);
	GsGetLs(&coord, &mat);
	GsSetLsMatrix(&mat);


	ts=s;

	for(y=0; y<6; y++)
	{					 
		for(x=0; x<6; x++)
		{
			vector.vx=-((x+mx)<<9);
			vector.vy=csin(ts)>>3;
			vector.vz=(y+my)<<9;
			//szList[index]=RotTransPers(&vector,next,&depth,&flag);
			gte_RotTransPers(&vector,next,&depth,&flag,&szList[index]);

			index++;
			next++;
			ts+=128;
		}
		ts+=1024;
	}

	//if (Input_PadData(0) & PAD_FRT)
		s+=128;
}







#define	RADAR_SCALE		(0)

/*

	new radar display using vertex buffer
	generates a filled display, using different colours for floor/wall

*/

void	rebuildRadarQuadList(Sint16 mx, Sint16 my)
{

	int				x,y,id;
	int				this_vertex_y,next_vertex_y;
	POLY_FT4			*quad;
	POLY_F4			*fquad;
	Uint32			*ot=(Uint32*)gfxGlobs.Wot[gfxGlobs.bufID].org;
	int				use_texture=FALSE;

	int				u=0;

	quad=&worldQuadList[0][GsGetActiveBuff()];
	fquad=&worldQuadListFlat[0][GsGetActiveBuff()];
	
	Input_PadRead(0);

	if (Input_PadData(0) & PAD_SEL)		/* speed of movement */
		use_texture=TRUE;
	
	for(y=0; y<5; y++)
	{
		this_vertex_y=next_vertex_y=y*VERTEXSPAN;
		next_vertex_y+=VERTEXSPAN;

		for(x=0; x<5; x++)
		{



		if (use_texture)
		{
			quad->r0=128;
			quad->g0=128;
			quad->b0=128;

			quad->x0=outputList[this_vertex_y+x].vx >> RADAR_SCALE;
			quad->y0=outputList[this_vertex_y+x].vy >> RADAR_SCALE;

			quad->x1=outputList[this_vertex_y+(x+1)].vx >> RADAR_SCALE;
			quad->y1=outputList[this_vertex_y+(x+1)].vy >> RADAR_SCALE;

			quad->x2=outputList[next_vertex_y+x].vx >> RADAR_SCALE;
			quad->y2=outputList[next_vertex_y+x].vy >> RADAR_SCALE;

			quad->x3=outputList[next_vertex_y+(x+1)].vx >> RADAR_SCALE;
			quad->y3=outputList[next_vertex_y+(x+1)].vy >> RADAR_SCALE;

			quad->u0=u;
			quad->v0=64;

			quad->u1=u+63;
			quad->v1=64;

			quad->u2=u;
			quad->v2=64+63;

			quad->u3=u+63;
			quad->v3=64+63;


			quad->clut=getClut(test_texture->cx,test_texture->cy);
			quad->tpage=test_texture->tPage;
			quad->tpage=getTPage(1,0,704,64);

			AddPrim(ot+(gfxGlobs.otSize-1),quad);

			quad++;
		}
		else
		{
			fquad->r0=0;
			fquad->g0=128+(x*8);			/* floors are green */
			fquad->b0=(y*32);

			fquad->x0=outputList[this_vertex_y+x].vx >> RADAR_SCALE;
			fquad->y0=outputList[this_vertex_y+x].vy >> RADAR_SCALE;

			fquad->x1=outputList[this_vertex_y+(x+1)].vx >> RADAR_SCALE;
			fquad->y1=outputList[this_vertex_y+(x+1)].vy >> RADAR_SCALE;

			fquad->x2=outputList[next_vertex_y+x].vx >> RADAR_SCALE;
			fquad->y2=outputList[next_vertex_y+x].vy >> RADAR_SCALE;

			fquad->x3=outputList[next_vertex_y+(x+1)].vx >> RADAR_SCALE;
			fquad->y3=outputList[next_vertex_y+(x+1)].vy >> RADAR_SCALE;
			AddPrim(ot+(gfxGlobs.otSize-1),fquad);
			fquad++;
		}


		}
	}
}



void	initialiseWorldQuadList(void)
{
	int	n;

	for (n=0; n<(MAX_WQ*MAX_WQ); n++)
	{
		SetPolyFT4(&worldQuadList[0][n]);
		SetPolyFT4(&worldQuadList[1][n]);

		SetPolyF4(&worldQuadListFlat[0][n]);
		SetPolyF4(&worldQuadListFlat[1][n]);

	}

	test_texture=Image_LoadTIM("BADTEX2.TIM");

}



/*
	these are now global to allow optimization
*/
DVECTOR			goutputList[XCOUNT*YCOUNT];
long				gszList[XCOUNT*YCOUNT];


void	test_gte_function(void)
{

	int					x,y,index=0;
	long					*next=(long*) goutputList;
	GsCOORDINATE2		coord;
	MATRIX				mat;
	long					depth=14,flag;
	SVECTOR				vector;

	GsInitCoordinate2(WORLD, &coord);
	GsGetLs(&coord, &mat);
	GsSetLsMatrix(&mat);


	if (Input_PadData(0) & PAD_RU)
	{
		for(y=0; y<YCOUNT; y++)
		{					 
			for(x=0; x<XCOUNT; x++)
			{
				vector.vx=-((x)<<9);
				vector.vy=0;
				vector.vz=(y)<<9;
				gszList[index]=RotTransPers(&vector,next,&depth,&flag);
				index++;
				next++;
			}
		}
	}
	else
	{
		for(y=0; y<YCOUNT; y++)
		{					 
			for(x=0; x<XCOUNT; x++)
			{
				vector.vx=-((x)<<9);
				vector.vy=0;
				vector.vz=(y)<<9;
				gte_RotTransPers(&vector,next,&depth,&flag,&gszList[index]);
				index++;
				next++;
			}
		}
	}
}
















u_char	*Sound_Vh,
			*Sound_Vb;

short	Sound_Vab;
long		vab;










/* foul and depraved sound code */
long	sound_init(unsigned char *vh, unsigned char *vb)
{

	vab=-1;		/* mark as unavailable */

	SsInit();										// RESET SOUND SYSTEM AND CLEAR MEMORY
	SsSetTickMode(SS_TICK50);					// SET TICK MODE = NOTICK, USER VBL UPDATE

	vab =SsVabOpenHead(vh,-1);					// SEARCH FOR EMPTY VAB
	if (vab<0)
	{
		return FALSE;								// SsVabOpenHead Failed
	}

	if (SsVabTransBody(vb,vab)!=vab)
	{
		return FALSE;								// SsVabTransBody Failed
	}

	SsStart();										// START SOUND
	SsSetMVol(127,127);							// SET MAIN VOLUME
	SsSetSerialAttr(SS_SERIAL_A, SS_MIX, SS_SON);

	return TRUE;
}


int	play_sfx(int	sfx_num,int freq, int volume)
{
	if (vab==-1)
		return;		/* no sfx loaded */

	return	SsUtKeyOn(vab,sfx_num,0,freq,0,volume,volume);

}




/*
		initialise test sound
*/
void initialise_test_sound(void)
{
	ULONG	size;
	
	Sound_Vh=NULL;
	Sound_Vb=NULL;

	Sound_Vh=File_LoadBinary("ROCK_R.VH", &size);
	Sound_Vb=File_LoadBinary("ROCK_R.VB", &size);

//	Sound_Vh=File_LoadBinary("INTRO.VH", &size);
//	Sound_Vb=File_LoadBinary("INTRO.VB", &size);
	Sound_Vab = sound_init(Sound_Vh, Sound_Vb);

	RELEASE(Sound_Vh);		/* don't need these now */
	RELEASE(Sound_Vb);

  PadInitDirect(padBuffer1,padBuffer2);
	PadStartCom();
}


int	dx[3];
int	num;



void testSound(void)
{
		pad_read();
}


#define	PROGNO	(1)
#define	TONENO	(0)
#define	NOTE		(60)
#define	FINE		(0)
#define	VOL		(127)
#define	PANSTART	(0)
#define	PANEND	(127)
#define	AUTOTIME	(64)
#define	VOLSTART	(0)
#define	VOLEND	(127)
#define	VOICENUM	(0)
#define	PLUS		(4)

#define WIDTH		320		/* screen width */
#define HEIGHT		240		/* screen height */
#define CENTER		200		/* screen center */
#define OTSIZE		16		/* ot size */
#define FTSIZE		64		/* number of font spirtes */
#define BARNUM		3		/* number of bar */
#define TSIZE		5		/* tile size */
#define BSIZE		80		/* bar size / 2 */
#define YS		84
#define YE		94
#define YW		16

#define MAXBAR		CENTER+BSIZE	/* bar right */
#define MIDBAR		CENTER-TSIZE/2	/* bar center */
#define MINBAR		CENTER-BSIZE	/* bar left */



/* Read controll-pad */
int pad_read()
{
	char *autopan = "autopan";
	char *autovol = "autovol";
	char *clear = "";
	static int key_on = 0;
	static int count_lu = 0;
	static int count_ld = 0;
	short pbend;
	short svol;
	short voll, volr;
	short spitch;
 	int ret = 0;
	int vc=0;

	Uint16 padd=0;


	padd=padBuffer1[2];		
	padd|=(padBuffer1[3]<<8);
	padd^=0xffff;


        if (((padd & PADselect) > 0) && ((padd & PADstart) > 0)) {
		if (key_on) {
#ifdef VOICE_SET_MODE
			SsUtKeyOffV(1);
#else
			SsUtKeyOff(vc, vab, PROGNO, TONENO, NOTE);
#endif /* VOICE_SET_MODE */
			ret = -1;
		}
	}
	
	if ((padd & PAD_START) )
	{
		if (!key_on)
		{
#ifdef VOICE_SET_MODE
			vc = SsUtKeyOnV(1, vab1, PROGNO, TONENO, NOTE, FINE, VOL, VOL);
#else
			vc = SsUtKeyOn(vab, PROGNO, TONENO, NOTE, FINE, VOL, VOL);
#endif /* VOICE_SET_MODE */
			if (vc != -1)
			    key_on = 1;
		}
	}
	
	if ((padd & PAD_SEL))
	{
		if (key_on)
		{
#ifdef VOICE_SET_MODE
			SsUtKeyOffV(1);
#else
			SsUtKeyOff(vc, vab, PROGNO, TONENO, NOTE);
#endif /* VOICE_SET_MODE */
			key_on = 0;
		}
	}
	
	if ((padd & PADRdown) > 0) {
		SsUtAutoPan(vc, PANSTART, PANEND, AUTOTIME);
	}
	if ((padd & PADRup) > 0) {
		SsUtAutoVol(vc, VOLSTART, VOLEND, AUTOTIME);
	}
	
	if ((padd & PAD_FLT)) {
		if (key_on) {
			if ((dx[num] -= PLUS) < MINBAR)
			    dx[num] = MINBAR;
			switch(num) {
			      case 0:	
				pbend = (dx[num] - 32) / 2;
				SsUtPitchBend(vc, vab, PROGNO, NOTE, pbend);
				break;
			      case 1:
				svol = (dx[num] - 32) / 2;
				SsUtSetVVol(vc, svol, svol); 
				break;
			      case 2:
				spitch = (dx[num] - 32) / 4;
				SsUtChangePitch(vc, vab, PROGNO, NOTE,
						FINE, spitch, FINE); 
				break;
			      default:
				break;
			}
		}
	}
	
	if ((padd & PAD_FRT)) {
		if (key_on) {
			if ((dx[num] += PLUS) > MAXBAR-TSIZE)
			    dx[num] = MAXBAR-TSIZE;
			switch(num) {
			      case 0:
				pbend = (dx[num] - 32) / 2;
				SsUtPitchBend(vc, vab, PROGNO, NOTE, pbend);
				break;
			      case 1:
				svol = (dx[num] - 32) / 2;
				SsUtSetVVol(vc, svol, svol); 
				break;
			      case 2:
				spitch = (dx[num] - 32) / 4;
				SsUtChangePitch(vc, vab, PROGNO, NOTE,
						FINE, spitch, FINE); 
				break;
			      default:
				break;
			}
		}
	}


	spitch=(padBuffer1[5]>>2);

	if (key_on)
		SsUtChangePitch(vc, vab, PROGNO, NOTE,FINE, spitch, FINE); 


	pbend=(padBuffer1[5]-128);

	//if (key_on)
	//	SsUtPitchBend(vc, vab, PROGNO, NOTE, pbend);

	
	if ((padd & PAD_LU)) {
		if (++count_lu > 10) {
			if (--num < 0) 
			    num = 0;
			//setRGB0(&db[0].tile[num+1], 0xff, 0xff, 0xff);
			//setRGB0(&db[1].tile[num+1], 0xff, 0xff, 0xff);
			//setRGB0(&db[0].tile[num], 0xff, 0x0, 0x0);
			//setRGB0(&db[1].tile[num], 0xff, 0x0, 0x0);
			count_lu = 0;
		}
	}
	
	if ((padd & PAD_LD)) {
		if (++count_ld > 10) {
			if (++num > BARNUM-1) 
			    num = BARNUM-1;
			//setRGB0(&db[0].tile[num-1], 0xff, 0xff, 0xff);
			//setRGB0(&db[1].tile[num-1], 0xff, 0xff, 0xff);
			//setRGB0(&db[0].tile[num], 0xff, 0x0, 0x0);
			//setRGB0(&db[1].tile[num], 0xff, 0x0, 0x0);
			count_ld = 0;
		}
	}
        if (((padd & PADselect) > 0) && ((padd & PADstart) > 0)) {
		ret = -1;
	}

	{
		char	 string[64];

		if (num==0)
			sprintf(string, "pbend=%d |2vol=%d pitch=%d",pbend,svol,spitch);
		else if (num==1)
			sprintf(string, "|2pbend=%d |7vol=%d|2 pitch=%d",pbend,svol,spitch);
		else
			sprintf(string, "|2pbend=%d vol=%d |7pitch=%d",pbend,svol,spitch);

		Font_PrintF(testGlobs.stdFont,8,16,string);
	}
	return(ret);
}


print_name(int id)
{
}







/* dual shock test code */




typedef struct
{
	DRAWENV		draw;		/* drawing environment */
	DISPENV		disp;		/* display environment */
} DB;

#define MultiTap	1
#define CtrlTypeMtap	8
#define PortPerMtap	4

#define BtnM0		1
#define BtnM1		2
#define BtnMode		4
#define BtnStart	8
#define BtnEnable	0x10


typedef struct
{
	/* button state at last V-Sync*/
	unsigned char Button;

	/* lock/unlock mode for setting terminal type alternation button
 */
	unsigned char Lock;

	/* value for setting actuators*/
	unsigned char Motor0,Motor1;

	/* flag for "already called PadSetActAlign()"
 */
	unsigned char Send;

	/* target coordinate of gun (which use interrupt)
 */
	int X,Y;
} HISTORY;


static HISTORY history[2][4];
static unsigned char padbuff[2][34];
int padEnable = 3;

typedef struct
{
	short Vert;
	short Horz;
} POINT;

typedef struct
{
	unsigned char Port;
	unsigned char Size;
	POINT Pos[10];
} GUNDATA;

GUNDATA gunPos;


void dispPad(int, unsigned char *);
void setPad(int, unsigned char *);
void *bzero(unsigned char *, int);
int PadChkMtap(int);


/*#main--- main routine */
int setup_shock_test(void)
{
	//bzero((unsigned char *)history, sizeof(history));
	//bzero((unsigned char *)padbuff, sizeof(padbuff));

	//ResetCallback();

#if MultiTap
	//PadInitMtap(padbuff[0],padbuff[1]);
#else
//	PadInitDirect(padbuff[0],padbuff[1]);
#endif
	//PadInitGun((unsigned char *)&gunPos, 10);
//	PadStartCom();

}



void	shock_test(void)
{
	setPad(0,padBuffer1);
	setPad(0x10,padBuffer2);

	dispPad(0,padbuff[0]);
	dispPad(0x10,padbuff[1]);

}






/*#setPad : analyze button state to act expanded-protocol controller functions
 */
void setPad(int port, unsigned char *rxbuf)
{
	HISTORY *hist;
	int button,count;

	if(rxbuf[1]>>4 == CtrlTypeMtap)
	{
		for(count=0;count<PortPerMtap;++count)
		{
			setPad(port+count, rxbuf + 2 +count*8);
		}
		return;
	}

	/* ignore received data when communication failed
 */
	if(*rxbuf)
	{
		return;
	}

	button = ~((rxbuf[2]<<8) | rxbuf[3]);
	hist = &history[port>>4][port & 3];

#if 0
	/* suspend/resume opposite port of communication
 */
	if(!(hist->Button & BtnEnable) && button & PADRleft)
	{
		padEnable ^= (1 << (!(port>>4)));
		PadEnableCom(padEnable);
	}
#endif

	/* Confirmation for reloading controller information by calling 
         PadStopCom(), PadStartCom()
 */
	if(!(hist->Button & BtnStart) && button & PADstart)
	{
		PadStopCom();
		PadStartCom();
	}

	if(PadInfoMode(port,InfoModeCurExID,0))
	{
		/* set actuator 0 level of expanded-protocol controller
 */
		if(!(hist->Button & BtnM0))
		{
			if(button & PADL1 && hist->Motor0)
			{
				hist->Motor0 -= 1;
			}
			else if(button & PADL2 && hist->Motor0 < 255)
			{
				hist->Motor0 += 1;
			}
		}

		/* set actuator 1 level of expanded-protocol controller
 */
		if(!(hist->Button & BtnM1))
		{
			if(button & PADR1 && hist->Motor1)
			{
				hist->Motor1 -= 10;
			}
			else if(button & PADR2 && hist->Motor1 < 246)
			{
				hist->Motor1 += 10;
			}
		}
		/* alternate terminal type and lock/unlock switch state
 */
		if(!(hist->Button & BtnMode))
		{
			if(button & PADLleft)
			{
				PadSetMainMode(port,0,hist->Lock);
			}
			else if(button & PADLright)
			{
				PadSetMainMode(port,1,hist->Lock);
			}
			else if(button & PADRright)
			{
				switch(hist->Lock)
				{
					case 0:
					case 2:
						hist->Lock = 3;
						break;
					case 3:
						hist->Lock = 2;
						break;
				}
				PadSetMainMode(port,
					PadInfoMode(port,InfoModeCurExOffs,0),
					hist->Lock);
			}
		}
	}
	else
	{
		/* set actuator level of SCPH-1150
 */
		if(!(hist->Button & BtnM0))
		{
			if(button & PADL1 && hist->Motor0)
			{
				hist->Motor0 = 0x40;
				hist->Motor1 -= 1;
			}
			else if(button & PADL2 && hist->Motor0 < 255)
			{
				hist->Motor0 = 0x40;
				hist->Motor1 += 1;
			}
		}
	}

	/*store button state of this V-Sync period*/
	if(button & (PADLright|PADLleft|PADRright))
		hist->Button |= BtnMode; else hist->Button &= ~BtnMode;
	if(button & (PADL1 | PADL2))
		hist->Button |= BtnM0; else hist->Button &= ~BtnM0;
	if(button & (PADR1 | PADR2))
		hist->Button |= BtnM1; else hist->Button &= ~BtnM1;
	if(button & PADRleft)
		hist->Button |= BtnEnable; else hist->Button &= ~BtnEnable;
	if(button & PADstart)
		hist->Button |= BtnStart; else hist->Button &= ~BtnStart;
}


/*#dispPad : display controller state */
void dispPad(int port, unsigned char *rxbuf)
{
	unsigned char buff[20];
	int count,pos,initlevel,maxnum;
	HISTORY *hist;

	/* Specify actuator alignment parameter (it should be decided  
          after checking the actuator primitives, but for simplicity 
          pre-defined data is used)
 */
	static unsigned char align[6]={0,1,0xFF,0xFF,0xFF,0xFF};

	if(rxbuf[1]>>4 == CtrlTypeMtap)
	{
		for(count=0;count<PortPerMtap;++count)
		{
			dispPad(port+count, rxbuf + 2 +count*8);
		}
		return;
	}

	hist = &history[port>>4][port & 3];
	initlevel = PadGetState(port);

	/* ------------------------------------------------------------ */
	/*              display multitap/direct connection 
 */
	/* ------------------------------------------------------------ */

	if(!(port & 0xF))
	{
		if(PadChkMtap(port))
		{
			//FntPrint("[~c686multi tap~c888]");
		}
		else
		{
			//FntPrint("[~c686direct~c888]");
		}
		if( ( !(port & 0x10) && !(padEnable & 1) ) ||
		    (  (port & 0x10) && !(padEnable & 2) ) )
		{
			//FntPrint("~c866 suspend~c888");
		}
	}

	//FntPrint("\n");

	/* ------------------------------------------------------------ */
	/*             display port number */
	/* ------------------------------------------------------------ */

	if(PadChkMtap(port))
	{
		//FntPrint("%d%c",(port>>4)+1,'A'+ (port & 0xF));
	}
	else
	{
		//FntPrint("%d",(port>>4)+1);
	}

	/* ------------------------------------------------------------ */
	/* display controller type and ID */
	/* ------------------------------------------------------------ */

	/* no controller connected */
	if(initlevel==PadStateDiscon)
	{
		//FntPrint("[~c866none~c888]\n\n\n");
		return;
	}

	if(PadInfoMode(port,InfoModeCurExID,0))
	{
		/* expanded-protocol controller connected
 */
			PadInfoMode(port,InfoModeCurExID,0);
	}
	else
	{
		/* controller (not expanded-protocol) connected
 */
		PadInfoMode(port,InfoModeCurID,0);
	}

	/* ------------------------------------------------------------ */
	/* To the controller, set buffer pointer for setting actuator level,
	   and set data alignment of actuator level(only for 
           expanded-protocol)
 */
	/* ------------------------------------------------------------ */

	/* clear flag "already called PadSetActAlign" when reloading 
	   actuator information due to terminal type switch or
	   connected controller change
 */
	if(initlevel == PadStateFindPad)
	{
		hist->Send = 0;
	}

	/* Set buffer pointer for setting actuator level and data alignment
	   of actuator level, upon completion of actuator information 
           loading 
 */
	if(!hist->Send)
	{
		PadSetAct(port,&hist->Motor0,2);

		/* for non-expanded protocol */
		if(initlevel == PadStateFindCTP1)
		{
			hist->Send = 1;
		}
		/* for expanded controller (wait until finish loading 
		   actuator information) */
		else if(initlevel == PadStateStable)
		{
			/* set flag when accepted
 */
			if(PadSetActAlign(port,align))
			{
				hist->Send = 1;
			}
		}
	}

	/* ------------------------------------------------------------ */
	/*            display coordinate of gun target
 */
	/* ------------------------------------------------------------ */

	if(PadInfoMode(port, InfoModeCurID, 0) == 3)
	{
		if(gunPos.Port == port && gunPos.Size)
		{
			hist->X = hist->Y = 0;
			for(count=0; count<gunPos.Size; ++count)
			{
				hist->X += gunPos.Pos[count].Horz;
				hist->Y += gunPos.Pos[count].Vert;
			}
			hist->X /= gunPos.Size;
			hist->Y /= gunPos.Size;
		}
		sprintf(buff,"%04d,%03d",hist->X,hist->Y);
		//FntPrint("g=~c686%s~c888 ",buff);
	}

	/* ------------------------------------------------------------ */
	/*    display button state and level of analog channels
 */
	/* ------------------------------------------------------------ */

	//FntPrint("b=~c686%x~c888 ", rxbuf[2] << 8 | rxbuf[3]);
	switch(PadInfoMode(port,InfoModeCurID,0))
	{
		case 1:
			sprintf(buff,"%02x,%02x",rxbuf[4],rxbuf[5]);
			//FntPrint("m=~c686%s~c888\n",buff);
			break;
		case 2:
			sprintf(buff,"%02x,%02x,%02x,%02x",
				rxbuf[4],rxbuf[5],rxbuf[6],rxbuf[7]);
			//FntPrint("a=~c686%s~c888\n",buff);
			break;
		case 6:
			sprintf(buff,"%3d,%3d",
				rxbuf[4]+rxbuf[5]*256,rxbuf[6]+rxbuf[7]*256);
			//FntPrint("g=~c686%s~c888\n",buff);
			break;
		case 5:
		case 7:
			sprintf(buff,"%02x,%02x,%02x,%02x",
				rxbuf[6],rxbuf[7],rxbuf[4],rxbuf[5]);
			//FntPrint("a=~c686%s~c888\n",buff);
			break;
		default:
			//FntPrint("\n");
	}

	/* ------------------------------------------------------------ */
	/*   display actuator information */
	/* ------------------------------------------------------------ */

	/* access actuator information after load completion
 */
	if(initlevel < PadStateStable)
	{
		//FntPrint("\n\n");
		return;
	}

	/* display actuator information */
	//FntPrint(" ac");
	maxnum = PadInfoAct(port,-1,0);
	for(count=0;count<maxnum;++count)
	{
		//FntPrint("(~c866%d,%d,%d,%d~c888)=~c686%d~c888 ",
			PadInfoAct(port,count,InfoActFunc);
			PadInfoAct(port,count,InfoActSub);
			PadInfoAct(port,count,InfoActSize);
			PadInfoAct(port,count,InfoActCurr);
		//	*(&hist->Motor0+count));
	}

	/* display terminal type IDs supported by the controller
 */
	//FntPrint("\n ID(~c866");
	maxnum = PadInfoMode(port,InfoModeIdTable,-1);
	for(count=0;count<maxnum;++count)
	{
		PadInfoMode(port,InfoModeIdTable,count);
		if(count != maxnum-1)
		{
			//FntPrint(",");
		}
	}

	/* display the list of actuator combinations which can 
	   concurrently operate
 */
	//FntPrint("~c888) cm");
	maxnum = PadInfoComb(port,-1,0);
	for(count=0;count<maxnum;++count)
	{
		//FntPrint("(~c866");
		for(pos=0;pos<PadInfoComb(port,count,-1);++pos)
		{
			//FntPrint("%x",PadInfoComb(port,count,pos));
			if(pos != PadInfoComb(port,count,-1)-1)
			{
				//FntPrint(",");
			}
		}
		//FntPrint("~c888) ");
	}

	/* display lock/unlock mode of terminal type alternation switch
 */
	//FntPrint("sw(~c686");
	switch(hist->Lock)
	{
		case 0:
		case 2:
			//FntPrint("unlock");
			break;
		case 3:			
			//FntPrint(" lock ");
			break;
	}
	//FntPrint("~c888)\n");
}








































