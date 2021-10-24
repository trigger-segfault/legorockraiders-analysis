/*

		Invaders with FMV in the background

		Steve Deacon, October 1998


		The FMV is decoded in the main loop at whatever speed it can manage.
		The game runs in the vertical blank, so always runs in a frame, no matter
		what the speed of the FMV.
		FMV seems to screw up occasionally, maybe because of the vblank
		over running.

		Currently it will only work from the emulator since file handling for
		GFX/SFX are not in.
		
*/



#include "..\inc\globals.h"

#include <r3000.h>
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include "libpad.h"
#include <kernel.h>


LPVOID	File_LoadBinary(LPUCHAR name, LPULONG size);


int			mode=MENU_MODE;
int			menu_id=MENU_ID_DIFFICULTY;
u_long		old_pad=0;



BEASTIES	beasties;
PLAYER		player;
BASE			bases[MAX_BASES];




BULLET	bullet_list[MAX_BULLETS];
int		new_sheet_timer;
int		game_over_timer;
int		game_over;
int		max_bases=MAX_BASES;
int		skill_level=EASY;
int		max_lives=MIN_LIVES;
int		file_system_flag;
long		vab;






DB	db[2];	/* double buffer with allocated primitive lists */
DB	*cdb;		/* current primitive buffer pointer */

u_short	tpage[4];	/* texture page ID (4pages) */
u_short	clut[4];	/* texture CLUT ID */

short	play_fmv=FALSE;
short	toggle_bounce=FALSE;
u_long	old_pad;
int		frame_delay;
int		game_initialised=FALSE;
int		frame=0;

int		frame_width=QUAD_WIDTH,frame_height=QUAD_HEIGHT;

u_char	*Sound_Vh,
			*Sound_Vb;

short	Sound_Vab;



#include "spr_tex.c"


HOLE holes[]=
{


/* player's bullet hole */

	{
		{

			{0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
			{0,1,2,2,2,1,0,0,0,0,0,0,0,0,0,0},
			{1,2,3,8,3,2,1,0,0,0,0,0,0,0,0,0},
			{1,2,8,8,8,2,1,0,0,0,0,0,0,0,0,0},
			{1,2,3,8,3,2,1,0,0,0,0,0,0,0,0,0},
			{0,1,2,2,2,1,0,0,0,0,0,0,0,0,0,0},
			{0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		},
		7,
		7,
	},	


/* invader bullet hole */

	{
		{

			{0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0},
			{0,0,0,1,2,2,2,2,2,1,0,0,0,0,0,0},
			{0,0,1,2,2,2,3,3,2,2,1,0,0,0,0,0},
			{0,1,2,3,3,3,8,8,3,2,1,0,0,0,0,0},
			{1,2,3,3,3,2,8,8,8,3,2,1,0,0,0,0},
			{1,2,3,3,8,8,8,8,8,8,3,2,1,0,0,0},
			{1,2,3,3,8,8,8,8,8,3,3,2,1,0,0,0},
			{1,2,3,3,8,8,8,8,8,8,3,2,1,0,0,0},
			{0,1,2,3,3,8,8,8,8,3,3,2,1,0,0,0},
			{0,1,2,3,3,3,3,8,3,3,2,1,0,0,0,0},
			{0,0,1,2,3,3,2,3,3,2,1,1,0,0,0,0},
			{0,0,0,1,2,2,1,2,2,1,0,0,0,0,0,0},
			{0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		},
		13,
		13,
	}	



};



int main2()
{
	int	 	buffer;
	/* double buffer:*/
	//DB	db[2];		
	
	/* current double buffer:*/
	//DB	*cdb;		

	
	int	x, y;	/* work */


	/* reset PAD:*/
	PadInit(0);
	
	

	frame_delay=FRAME_DELAY;

	/* reset graphics sysmtem (0:cold,1:warm);*/
	ResetGraph(0);		
	SetVideoMode(MODE_PAL);
	file_system_flag=PCinit();
	initialise_test_sound();


	/* set debug mode (0:off,1:monitor,2:dump): */
	SetGraphDebug(0);	
	
	/* set callback: */
	VSyncCallback(cbvsync);	

	/* initialize environment for double buffer */

	SetDefDrawEnv(&db[0].draw, 0,   0, 320, 240);
	SetDefDrawEnv(&db[1].draw, 0, 240, 320, 240);

/* set texture page for sprites */
	db[0].draw.tpage=getTPage(0,0,320,0);
	db[1].draw.tpage=getTPage(0,0,320,0);


	/* set auto clear screen and colour */
	db[0].draw.isbg = 1;
	setRGB0(&db[0].draw, 0, 0, 0);

	db[1].draw.isbg = 1;
	setRGB0(&db[1].draw, 0, 0, 0);



	SetDefDispEnv(&db[0].disp, 0, 240, 320, 240);
	SetDefDispEnv(&db[1].disp, 0,   0, 320, 240);
	db[0].disp.screen.y=20;
	db[1].disp.screen.y=20;

	/* init font environment; */
#ifdef KANJI	/* KANJI */
	KanjiFntOpen(160, 16, 256, 200, 704, 0, 768, 256, 0, 512);
#endif	
	FntLoad(960, 256);	
	
	//SetDumpFnt(FntOpen(16, 16, 256, 200, 0, 512));	


	for (buffer=0; buffer<2; buffer++)
	{
		for (x=0; x<BW; x++)
		{
			for (y=0 ;y<BH; y++)
			{

#ifdef FIXED_SPRITE16
				SetDrawMode(&db[buffer].beastie_poly[x][y].draw_mode,1,0,0,0);
				SetSprt16(&db[buffer].beastie_poly[x][y].sprite);

#else
				SetSprt(&db[buffer].beastie_poly[x][y]);		
#endif
				SetShadeTex(&db[buffer].beastie_poly[x][y], 1);		/* ShadeTex disable */

			}
		}


		/* general quads */
		for (x=0; x<MAX_QUADS; x++)
		{
		 	SetPolyF4(&db[buffer].quad_list[x]);		
		}

		for (x=0; x<MAX_LINES; x++)
		{
		 	SetLineG2(&db[buffer].line_list[x]);		
		}

		for (x=0; x<MAX_BASES; x++)
		{
			SetPolyFT4(&db[buffer].base_quad[x]);		
			SetShadeTex(&db[buffer].base_quad[x], 1);		/* ShadeTex disable */
		}


		SetPolyFT4(&db[buffer].ship_quad);
		SetShadeTex(&db[buffer].ship_quad, 1);		/* ShadeTex disable */

		SetPolyFT4(&db[buffer].ufo_quad);
		SetShadeTex(&db[buffer].ufo_quad, 1);		/* ShadeTex disable */

		/* fmv quads */

		SetPolyGT4(&db[buffer].fmv_frame);
		//SetShadeTex(&db[buffer].fmv_frame, 1);		/* ShadeTex disable */

		SetPolyGT4(&db[buffer].fmv_frame2);
		//SetShadeTex(&db[buffer].fmv_frame2, 1);		/* ShadeTex disable */

	}




	/* enable to display: */
	SetDispMask(1);		/* 0:inhibit,1:enable:*/



	initialise_bases();
	init_beasties_and_stuff_new_game();
									
	player.high_score=0;	

#ifdef FMV_ON

	/* initialise CD/FMV stuff */

	if (frame_delay==1)
	{

		RECT		fmv_rect;
		CdlFILE	fl;
		CdlFILE	*fl_ptr;
		int		ret=9999;
		unsigned char	*test_load=NULL;
		unsigned long	file_length;

		fmv_rect.x=320+64;
		fmv_rect.y=0;
		fmv_rect.w=320;
		fmv_rect.h=192;

		/* initialise cd system */

		ret=CdInit();


		if (ret==0)
			printf("cd is bad");
		if (ret==1)
			printf("cd is initialised");


		test_load=File_LoadBinary("LEGO.CFG",&file_length);
		if (test_load)
			printf("Woof Woof!");


		//fl_ptr=CdSearchFile(&fl,"\\VIDEO\\DEMO.STR;1");
		fl_ptr=CdSearchFile(&fl,"\\DATA\\LEGO.CFG;1");
		if (fl_ptr!=NULL)
		{
			FMV_Init(&fmv_rect,FMV16,&fl.pos,0,522,FALSE);
			play_fmv=TRUE;
		}
	}

#endif


/* main loop */

	game_initialised=TRUE;

	while (TRUE)
	{

		if (play_fmv)
		{

			FMV_GetFrame();
			FMV_LoadFrame();	/* should double buffer the frame really */
		}
	}


	if (play_fmv)
		FMV_Stop();

	PadStop();
	StopCallback();
	return(0);
}



/* vblank callback */
static void cbvsync(void)
{
	if (game_initialised)
	{
		if (mode==GAME_MODE)
			handle_game_mode();
		else
			handle_menu_mode();
	}
}


void	handle_game_mode(void)
{
	/* swap double buffer ID: */
	cdb  = (cdb==db)? db+1: db;	

		/* clear ordering table:  */
	ClearOTag(cdb->ot, OTSIZE);

	cdb->next_quad=0;
	cdb->next_line=0;
	cdb->next_sprite=0;



	update_game(frame);
	draw_all_stuff(frame);
	process_all_particles();


	if (play_fmv)
	{
		draw_fmv_frame();
	}

	{

		char	string[80];

		sprintf(string,"sc:|2%06d    |7hi:|3%06d    |7lives:|6%02d",player.score,player.high_score,player.lives);
		dump_string(0,0,string);
	}

	//FntPrint("score %05d   lives %d   sheet %02d\n",player.score,player.lives,player.sheets);
	//FntFlush(-1);


	PutDispEnv(&cdb->disp); 
	PutDrawEnv(&cdb->draw); 
	DrawOTag(cdb->ot);
	frame+=frame_delay;
}

void	handle_menu_mode(void)
{
	/* swap double buffer ID: */
	cdb  = (cdb==db)? db+1: db;	

		/* clear ordering table:  */
	ClearOTag(cdb->ot, OTSIZE);

	cdb->next_quad=0;
	cdb->next_line=0;
	cdb->next_sprite=0;


	process_menu();
	display_menu();

	if (play_fmv)
	{
		draw_fmv_frame();
	}

	FntFlush(-1);


	PutDispEnv(&cdb->disp); 
	PutDrawEnv(&cdb->draw); 
	DrawOTag(cdb->ot);
	frame+=frame_delay;
}


/* process menu */
void	process_menu(void)
{
	u_long		new_pad;

	new_pad = PadRead(1);

	if (new_pad!=old_pad)
	{
		old_pad=new_pad;

		if (new_pad & PADstart)
		{
			mode=GAME_MODE;
			init_beasties_and_stuff_new_game();
			reset_bases();			
		}

		if (new_pad & PADLup)
		{
			menu_id--;
			if (menu_id==-1)
				menu_id=MENU_ID_BASES;
		}

		if (new_pad & PADLdown)
		{
			menu_id++;
			if (menu_id==MENU_ID_BASES+1)
				menu_id=MENU_ID_DIFFICULTY;
		}


/* skill level */
		if (menu_id==MENU_ID_DIFFICULTY)
		{
			if (new_pad & PADLleft)
			{
				skill_level--;
				if (skill_level==-1)
					skill_level=HARD;
			}

			if (new_pad & PADLright)
			{
				skill_level++;
				if (skill_level==HARD+1)
					skill_level=EASY;
			}

		}


/* lives */
		if (menu_id==MENU_ID_LIVES)
		{
			if (new_pad & PADLleft)
			{
				max_lives--;
				if (max_lives==MIN_LIVES-1)
					max_lives=MAX_LIVES;
			}

			if (new_pad & PADLright)
			{
				max_lives++;
				if (max_lives==MAX_LIVES+1)
					max_lives=MIN_LIVES;
			}

		}


		if (menu_id==MENU_ID_BASES)
		{
			if (new_pad & PADLleft)
			{
				max_bases--;
				if (max_bases==-1)
					max_bases=4;
			}

			if (new_pad & PADLright)
			{
				max_bases++;
				if (max_bases==MAX_BASES+1)
					max_bases=0;
			}
		}

	}

}

#define	HIGHLIGHT_W		(144)		
#define	HIGHLIGHT_H		(16)
#define	HIGHLIGHT_X		(160-(HIGHLIGHT_W>>1))
#define	HIGHLIGHT_Y		(91-(HIGHLIGHT_H>>1))

void	display_menu(void)
{
	static		char	difficulty[3][8]={"EASY","MEDIUM","HARD"};
	POLY_F4		*highlight_quad;
	int			highlight_y=HIGHLIGHT_Y+(24*menu_id);
	char			string[80];



/* difficulty */

	sprintf(string,"            SKILL: |3%s",difficulty[skill_level]);
	dump_string(0,11*8,string);

/* lives */

	sprintf(string,"            LIVES: |3%d",max_lives);
	dump_string(0,14*8,string);

/* bases */

	if (max_bases==0)
		dump_string(0,17*8,"            BASES: |3OFF");
	else
	{
		sprintf(string,"            BASES: |3%d",max_bases);
		dump_string(0,17*8,string);
	}

	if ((frame&8)==8)	
		dump_string(0,21*8,"|cPRESS START TO PLAY");

	highlight_quad=&(cdb->quad_list[cdb->next_quad++]);
	setXY4(highlight_quad,
							HIGHLIGHT_X,highlight_y,
							HIGHLIGHT_X,highlight_y+HIGHLIGHT_H,
							HIGHLIGHT_X+HIGHLIGHT_W,highlight_y,
							HIGHLIGHT_X+HIGHLIGHT_W,highlight_y+HIGHLIGHT_H);

	setRGB0(highlight_quad,0,0,128);
	setSemiTrans(highlight_quad,TRUE);
	
 	AddPrim(cdb->ot,highlight_quad);
		
}


/*
 * Read control-pad
 */
static int pad_read(int	n)		
{
	u_long	padd = PadRead(1);

	if(padd & PADLup)	n += 4;
	if(padd & PADLdown)	n -= 4;

	if (padd & PADL1) 			/*: pause */
		while (PadRead(1)&PADL1);

	if(padd & PADselect) 	return(-1);

	limitRange(n, 1, MAXOBJ-1);
					/* see libgpu.h */
	return(n);
}




/* new invader stuff added here */


void	init_beasties_and_stuff(void)
{
	short	x,y,n;

	game_over_timer=-1;
	new_sheet_timer=-1;
	game_over=FALSE;

	beasties.x=LEFT_EXTENT;		/* group position */
	beasties.y=FLOOR_EXTENT-(DROP_STEP*24);

/* increase y on sheet modulo every 8 sheets */
	beasties.y+=((player.sheets&7)*DROP_STEP);

	//beasties.y=FLOOR_EXTENT-(DROP_STEP*18);
	beasties.speed=(SPEED<<3)*(skill_level+1);
	beasties.direction=RIGHT;

	beasties.anim_delay=0;
	beasties.last_frame=0;	

	for (n=1; n<MAX_BULLETS; n++)
	{
		bullet_list[n].x=0;
		bullet_list[n].y=-1;
	}

	for (x=0; x<BW; x++)
	{
		for (y=0; y<BH; y++)
		{
			beasties.grid[x][y]=1;
		}
	}

	player.sheets++;
	beasties.next_fire_counter=50+(rand()&31);
	flush_particle_list();

}


void	init_beasties_and_stuff_new_game(void)
{
	init_beasties_and_stuff();
 	player.x=PLAYER_START_X;
	player.y=PLAYER_START_Y;
	player.score=0;
	player.extra_life_score=0;
	player.death_timer=0;
	player.sheets=1;
	player.lives=max_lives;
	player.last_fired=0;

	beasties.ufo_y=FLOOR_EXTENT-(DROP_STEP*26);
	beasties.ufo_x=-32;
	beasties.next_ufo_timer=100;
	beasties.ufo_hit_timer=0;

	bullet_list[PLAYER_BULLET].x=0;
	bullet_list[PLAYER_BULLET].y=-1;

}


void	draw_all_stuff(int frame)
{
	draw_all_bases();
	draw_ufo();
	draw_bases();
	draw_beastie_grid(frame);
	draw_bullets();
	if (player.death_timer==0)
		draw_ship();



}


void	draw_bases(void)
{
}




void	draw_ship(void)
{


/* position and size */

	setXYWH(&cdb->ship_quad, player.x,player.y-PLAYER_H,PLAYER_W,16);


/* set texture pages and clut */
	cdb->ship_quad.tpage=invader_tpage_info.tpage;
	cdb->ship_quad.clut=invader_tpage_info.clut;

/* set texture point (u,v) */
	setUVWH(&cdb->ship_quad, (((player.x>>1)&3)*16), 16, 15, 15);
 	AddPrim(cdb->ot,&cdb->ship_quad);



}

static unsigned char colour_table[8][3]=
{
	{0,0,0},
	{255,0,0},
	{0,255,0},
	{255,255,},
	{0,0,255},
	{255,0,255},
	{0,255,255},
	{255,255,255},
};

enum
{
	RED,
	GREEN,
	BLUE,
};

void	dump_string(int x, int y, unsigned char *string)
{
	int					n;
	unsigned char		code;
	TSPRT_8				*char_sprite;
	int					char_tpage=getTPage(0,0,960,256);
	int					char_clut=getClut(960,256+128);
	int					u,v;
	int					len=strlen(string);
	int					colour=7;
	int					type;

	for (; code=*string++ ;)
	{
		if (code==' ')
		{
			x+=8;
			continue;
		}

		if (code=='|')
		{
			type=*string++;
			if ((type>='0') && (type<='7'))
			{
				colour=type-='0';
				continue;
			}
			if (type=='c')
			{
				x=(320-((len-2)<<3))>>1;
				continue;
			}
			continue;
		}

		if (cdb->next_sprite==MAX_SPRITES)
			return;

		char_sprite=&(cdb->sprite_8_list[cdb->next_sprite++]);
		SetTSprt_8(char_sprite,char_tpage);
		SetShadeTex(&(char_sprite->sprite), 0);		/* ShadeTex disable */
		char_sprite->sprite.clut=char_clut;

		if (code>96)
			code-=32;

		code-=32;
		u=(code&15)<<3;
		v=(code>>4)<<3;
		setUV0(&(char_sprite->sprite),u,v);
		setXY0(&(char_sprite->sprite), x,y);

		setRGB0(&(char_sprite->sprite),colour_table[colour][0],colour_table[colour][1],colour_table[colour][2]);

		AddPrim(cdb->ot,&(char_sprite->draw_mode));
		x+=8;		
	}
}


#define UFO_WIDTH	24
#define UFO_HEIGHT	16

/* draw ufo from two quads */
void	draw_ufo(void)
{

/* position and size */

	setXYWH(&cdb->ufo_quad, beasties.ufo_x,beasties.ufo_y,UFO_WIDTH,UFO_HEIGHT);


/* set texture pages and clut */
	cdb->ufo_quad.tpage=invader_tpage_info.tpage;
	cdb->ufo_quad.clut=invader_tpage_info.clut;

/* set texture point (u,v) */
	setUVWH(&cdb->ufo_quad, (((beasties.ufo_x>>1)&3)*24)+64, 16, 23, 15);
 	AddPrim(cdb->ot,&cdb->ufo_quad);

/* draw score for hit ufo */

	if (beasties.ufo_hit_timer>0)
	{
		char	string[10];

		beasties.ufo_hit_timer--;

		sprintf(string,"%d",beasties.ufo_hit_value);
		dump_string(beasties.ufo_hit_x,beasties.ufo_y,string);
	}


}


/* return the index of the leftmost beastie */
int		leftmost_beastie(void)
{
	int	x,y;

	for (x=0; x<BW; x++)
	{
		for (y=0; y<BH; y++)
		{
			if (beasties.grid[x][y]!=0)
				return	x;
		}
	}
	return	-1;			/* grid is empty */
}

/* return the index of the rightmost beastie */
int		rightmost_beastie(void)
{
	int	x,y;

	for (x=BW-1; x>=0; x--)
	{
		for (y=BH-1; y>=0; y--)
		{
			if (beasties.grid[x][y]!=0)
				return	x;
		}
	}
	return	-1;			/* grid is empty */
}

/* return the index of the rightmost beastie */
int		lowest_beastie(void)
{
	int	x,y;

	for (y=BH-1; y>=0; y--)
	{
		for (x=0; x<BW; x++)
		{
			if (beasties.grid[x][y]!=0)
				return	y;
		}
	}
	return	-1;			/* grid is empty */
}



/* random beastie fires */
void beastie_fires(void)
{
	int		start_column,n,y;

	start_column=rand()%BW;
	beasties.next_fire_counter=50-(player.sheets*10)+(rand()&31);
	if (beasties.next_fire_counter<10)
		beasties.next_fire_counter=10;


	for (n=0; n<BW; n++)
	{

		for (y=BH-1; y>=0; y--)
		{
			if (beasties.grid[start_column][y]!=0)
			{
				for (n=1; n<MAX_BULLETS; n++)		/* skip 0 'cos it's the player's */
				{
					if (bullet_list[n].y==-1)
					{
						bullet_list[n].x=(beasties.x>>FRACTION_SHIFT)+(start_column*XSPACING)+(BEASTIE_W>>1);
						bullet_list[n].y=beasties.y+(y*YSPACING)+(BEASTIE_H>>1);
						if (y==0)
							bullet_list[n].type=PIERCING_BULLET;
						else
							bullet_list[n].type=NORMAL_BULLET;
		
					 	return;
					}
				}
				return;
			}
		}
		start_column++;
		if (start_column==BW)
			start_column=0;

	}

	/* if we get here then something has screwed up,
		since the beastie array must be empty			*/


}

/* update all objects */
void	update_game(int frame)
{
	int			extent_pos,lowest_extent;
	int			n;
	u_long		padd;		/* work */

	/* the beasties first */


	if (beasties.next_ufo_timer==0)
	{
		if (beasties.ufo_direction==0)
		{
			/* going right */

			beasties.ufo_x+=FRAME_DELAY;
			if (beasties.ufo_x>=320)
			 	beasties.next_ufo_timer=300+(rand()&127);
		}
		else	/* going left */
		{		
			beasties.ufo_x-=FRAME_DELAY;
			if (beasties.ufo_x<=-32)
			 	beasties.next_ufo_timer=300+(rand()&127);
		}
	}
	else
	{
		beasties.next_ufo_timer-=FRAME_DELAY;
		if (beasties.next_ufo_timer<=0)
		{
			beasties.next_ufo_timer=0;
			beasties.ufo_direction=rand()&1;
			if (beasties.ufo_direction==0)
				beasties.ufo_x=-32;
			else
				beasties.ufo_x=320;
		}
	}

	if (new_sheet_timer==-1)
	{
		if (lowest_beastie()==-1)
		{
			new_sheet_timer=2*50;
			return;
		}
	}
	else
	{
		new_sheet_timer--;
		if (new_sheet_timer==0)
		{
			init_beasties_and_stuff();
			reset_bases();
		}
	}

	if (beasties.alive>0 && game_over_timer==-1)
	{
		beasties.next_fire_counter-=FRAME_DELAY;
		if (beasties.next_fire_counter<=0)
		{
			beastie_fires();
		}
	}


	beasties.anim_delay+=beasties.speed;

	lowest_extent=((lowest_beastie()+1)*YSPACING)+beasties.y;

	if (lowest_extent<FLOOR_EXTENT)
	{
		if (beasties.direction==LEFT)
		{
			beasties.x-=(beasties.speed);
			extent_pos=(leftmost_beastie()*XSPACING)+(beasties.x>>FRACTION_SHIFT);
			if (extent_pos<=LEFT_EXTENT)
			{
				beasties.direction=RIGHT;
				beasties.y+=DROP_STEP;

			/* shave off top of bases if necessary */

				if ((lowest_extent)>=bases[0].y)
				{
					int	shave_offset;

					shave_offset=((lowest_extent)-bases[0].y) & 0xfff8;
					nibble_all_bases(shave_offset);
				}
			}
		}	
		else							/* going right */
		{
			beasties.x+=(beasties.speed);
			extent_pos=((rightmost_beastie()+1)*XSPACING)+(beasties.x>>FRACTION_SHIFT);
			if (extent_pos>=RIGHT_EXTENT)
			{
				beasties.direction=LEFT;
				beasties.y+=DROP_STEP;


			/* shave off top of bases if necessary */

				if ((lowest_extent)>=bases[0].y)
				{
					int	shave_offset;

					shave_offset=((lowest_extent)-bases[0].y) & 0xfff8;
					nibble_all_bases(shave_offset);
				}


			}

		}


/* the player */

		padd = PadRead(1);


		if (padd & PADselect)
		{
			mode=MENU_MODE;
			return;
		}

		if (padd & PADL1)
		{
		 	frame_width--;
			if (frame_width<1)
				frame_width=1;
		}

		if (padd & PADL2)
		{
		 	frame_width++;
			if (frame_width>160)
				frame_width=160;
		}


		if (padd & PADR1)
		{
		 	frame_height--;
			if (frame_height<1)
				frame_height=1;
		}

		if (padd & PADR2
)
		{
		 	frame_height++;
			if (frame_height>120)
				frame_height=120;
		}


	/* refire count down */
		if (player.last_fired>0)
			player.last_fired--;

		if (!(padd & PADRdown))
			player.last_fired=0;		/* instant release */
			

		if (player.death_timer==0)
		{


			if (padd & PADLleft)
			{
			 	player.x-=PLAYER_MOVE_DELTA;
				if (player.x<LEFT_EXTENT)
					player.x=LEFT_EXTENT;

			}

			if (padd & PADLright)
			{
				if ((player.x+PLAYER_W)<RIGHT_EXTENT)
			 		player.x+=PLAYER_MOVE_DELTA;

			}


			/* firing */
			if ((padd & PADRdown) && player.last_fired==0)
			{

			/* player always has bullet 0 */
				if (bullet_list[PLAYER_BULLET].y==-1)
				{
					bullet_list[PLAYER_BULLET].x=player.x+(PLAYER_W>>1);
					bullet_list[PLAYER_BULLET].y=player.y-10;
					bullet_list[PLAYER_BULLET].type=TANK_BULLET;

					play_sfx(4,36,15);
					player.last_fired=PLAYER_REFIRE_TIME;
				}
			}		

		}
		else
		{
			player.death_timer-=FRAME_DELAY;
			if (player.death_timer<=0)
			{
				player.death_timer=0;
				player.x=PLAYER_START_X;
			}
		}



	/* update bullet list */
		for (n=0; n<MAX_BULLETS; n++)
		{
			if (bullet_list[n].y!=-1)
			{
				if (n==PLAYER_BULLET)
				{
					bullet_list[n].y+=PLAYER_BULLET_DELTA;
					if (check_player_bullet())
						continue;					/* hit base */
					if (bullet_list[n].y<0)
						bullet_list[n].y=-1;
					else
						check_beastie_collision();
				}
				else
				{
					if (bullet_list[n].type==PIERCING_BULLET || skill_level==HARD)
						bullet_list[n].y+=(BEASTIE_BULLET_DELTA<<1);
					else
						bullet_list[n].y+=BEASTIE_BULLET_DELTA;

					if (bullet_hit_base(n,0))
						continue;
					if (player.death_timer==0)
		  				check_player_collision(n);

					if ((bullet_list[n].y)>FLOOR_EXTENT)
						bullet_list[n].y=-1;
				}
			}
		}
	}
	else	/* game over - invaders at bottom */
	{
		
		if (game_over_timer==-1)
		{
			game_over=TRUE;
			game_over_timer=(5*50);		/* five seconds */
		}
	}

	if (game_over_timer!=-1)
	{
		game_over_timer-=FRAME_DELAY;
		if (game_over_timer<=0)
		{
			mode=MENU_MODE;
			return;
			game_over_timer=-1;
			game_over=FALSE;
			init_beasties_and_stuff_new_game();
			reset_bases();
		}
	}
}


int	bullet_hit_base(int index,int offset)
{

	int		n,j;
	int		base_offset_x,base_offset_y;
	

	if (bullet_list[index].y+offset<bases[0].y)
		return	FALSE;
	if (bullet_list[index].y+offset>=bases[0].y+BASE_HEIGHT)
		return	FALSE;
	
	for (n=0; n<max_bases; n++)
	{
		if (bullet_list[index].x<bases[n].x)
			continue;
		if (bullet_list[index].x>=bases[n].x+BASE_WIDTH)
			continue;

		/* now check for a hit within the base */


		base_offset_x=bullet_list[index].x-bases[n].x;
		base_offset_y=bullet_list[index].y+offset-bases[n].y;
		if ((*(bases[n].base_frame+(base_offset_y*BASE_WIDTH)+base_offset_x))>0)
		{
			if (index==PLAYER_BULLET)
			{
				damage_base(n,base_offset_x,base_offset_y,PLAYER_BULLET_HOLE);
				for (j=0; j<3; j++)
					add_particle(	bullet_list[index].x,
										bullet_list[index].y,
										(rand()&63)-32,
										(rand()&15),
										0,255,0);


			}
			else
			{
				if (bullet_list[index].type==NORMAL_BULLET)
				{
				damage_base(n,base_offset_x,base_offset_y,INVADER_BULLET_HOLE);
				play_sfx(4,4,10);
				
				for (j=0; j<3; j++)
					add_particle(	bullet_list[index].x,
										bullet_list[index].y,
										(rand()&63)-32,
										-((rand()&63)+80),
										0,255,0);
				}
				else
 				{
					if ((frame&3)==0)
						play_sfx(4,4,10);

					damage_base(n,base_offset_x,base_offset_y,PLAYER_BULLET_HOLE); /* smaller hole 'cos it goes right through */
					for (j=0; j<1; j++)
						add_particle(	bullet_list[index].x,
											bullet_list[index].y,
											(rand()&63)-32,
											-((rand()&63)+80),
											0,255,0);
					return	FALSE;					/* this bullet doesn't stop */
				}
	
			}

			bullet_list[index].y=-1;		/* kill bullet */
			return	TRUE;
		}

	}
	return	FALSE;
}

int	check_player_bullet(void)
{
	
	if (bullet_hit_base(PLAYER_BULLET,-(BULLET_H>>1)))
		return	TRUE;
	return	FALSE;
}


void	check_beastie_collision(void)
{

	int		cell_x,cell_y,n,j;
	int		cell_xpos,cell_ypos;
	int		hit_value;

	cell_x=(bullet_list[PLAYER_BULLET].x-(beasties.x>>FRACTION_SHIFT))/XSPACING;
	cell_y=(bullet_list[PLAYER_BULLET].y-beasties.y)/YSPACING;



	if ((cell_x>=0) && (cell_x<=BW-1) && cell_y>=0 && (cell_y<=BH-1))
	{

		cell_xpos=(beasties.x>>FRACTION_SHIFT)+(cell_x*XSPACING);
		cell_ypos=beasties.y+(cell_y*XSPACING);

		if (bullet_list[PLAYER_BULLET].x>=cell_xpos && bullet_list[PLAYER_BULLET].x<(cell_xpos+XSPACING))
		{

			if (beasties.grid[cell_x][cell_y]!=0)
			{
				beasties.grid[cell_x][cell_y]=0;
				bullet_list[PLAYER_BULLET].y=-1;
				increment_score((BH-cell_y)*10);

				play_sfx(4,15,20);
			
				for (n=0; n<10; n++)
				{
					add_particle(	(beasties.x>>FRACTION_SHIFT)+(cell_x*XSPACING)+(BEASTIE_W>>1)+((rand()&7)-4),
										beasties.y+(cell_y*YSPACING)+(BEASTIE_H>>1)+((rand()&7)-4),
										(rand()&127)-64,
										(rand()&127)-64,
										255,128,0);
				}

				beasties.speed+=3;
				if (beasties.alive==3)
					beasties.speed+=256;
				if (beasties.alive==2)
					beasties.speed+=256;
	

				return;
			}
		}
	}


	/* check ufo */

	if (bullet_list[PLAYER_BULLET].x<beasties.ufo_x)
		return;
	if (bullet_list[PLAYER_BULLET].x>(beasties.ufo_x+UFO_WIDTH))
		return;
	if (bullet_list[PLAYER_BULLET].y<beasties.ufo_y)
		return;
	if (bullet_list[PLAYER_BULLET].y>(beasties.ufo_y+UFO_HEIGHT))
		return;


	hit_value=(beasties.ufo_x+(UFO_WIDTH>>1)-bullet_list[PLAYER_BULLET].x);

	if (hit_value<0)
		hit_value=-hit_value;
	hit_value>>=2;
	if (hit_value>2)
		hit_value=2;
	hit_value=3-hit_value;
	hit_value*=150;

	beasties.next_ufo_timer=300+(rand()&127);
	increment_score(hit_value);
	beasties.ufo_hit_timer=60;
	beasties.ufo_hit_value=hit_value;
	beasties.ufo_hit_x=beasties.ufo_x+(UFO_WIDTH>>1)-12;
	play_sfx(4,12,50);

	for (j=0; j<2; j++)
	{
		for (n=0; n<6; n++)
		{	
		 	add_particle(	beasties.ufo_x+(j*(UFO_WIDTH>>1))+(UFO_WIDTH>>2),
		 						beasties.ufo_y,
		 						(rand()&127)-64,
		 						(rand()&127)-64,
		 						0,255,255);
		}
	}		
	beasties.ufo_x=-32;		/* place off screen */
	bullet_list[PLAYER_BULLET].y=-1;
	return;

}

void	check_player_collision(int bullet_index)
{
	int		n;


	if (bullet_list[bullet_index].y!=-1)
	{
		if (bullet_list[bullet_index].x<player.x)
			return;
		if (bullet_list[bullet_index].x>(player.x+PLAYER_W))
			return;
		if (bullet_list[bullet_index].y<player.y)
			return;

		bullet_list[bullet_index].y=-1;	/* kill bullet */
		
		for (n=0; n<25; n++)
		{
			add_particle(	player.x+(PLAYER_W>>1),
								player.y,
								(rand()&255)-127,
								-((rand()&127)+160),
								0,255,0);
		}

		play_sfx(4,4,50);
		player.death_timer=100;
		player.lives--;
		if (player.lives==0)
		{
			game_over=TRUE;
			game_over_timer=(5*50);		/* five seconds */
			player.death_timer=1000;
		}
	}
}


void	draw_beastie_grid(int frame_count)
{

	int			x,y;
	short			frame=0;
	int			u,v;
	int			new_frame;

	new_frame=((beasties.anim_delay>>(FRACTION_SHIFT+2))&1);
	if (new_frame!=beasties.last_frame)
	{
		beasties.last_frame=new_frame;
		//play_sfx(4);
		
	}

	beasties.alive=0;

	for (x=0; x<BW; x++)
	{
		for (y=0; y<BH; y++)
		{
			frame=(y*2)+((beasties.anim_delay>>(FRACTION_SHIFT+2))&1);
			if (beasties.grid[x][y]!=0)
			{
				beasties.alive++;

			/* set texture pages and clut */

				SetTSprt_16(&cdb->beastie_poly[x][y],invader_tpage_info.tpage);
				SetShadeTex(&cdb->beastie_poly[x][y].sprite, 1);		/* ShadeTex disable */


				cdb->beastie_poly[x][y].sprite.clut=invader_tpage_info.clut;

			/* set texture point (u,v) */
				u = frame*16;
				v = 0;
				//setUVWH(&cdb->beastie_poly[x][y],u,v, 15, 15);
				setUV0(&cdb->beastie_poly[x][y].sprite,u,v);

			/* calculate sprite position */
				//setXYWH(&cdb->beastie_poly[x][y], (beasties.x>>FRACTION_SHIFT)+(x*XSPACING), beasties.y+(y*YSPACING), BEASTIE_W, BEASTIE_H);
				setXY0(&cdb->beastie_poly[x][y].sprite, (beasties.x>>FRACTION_SHIFT)+(x*XSPACING), beasties.y+(y*YSPACING));
				AddPrim(cdb->ot,&cdb->beastie_poly[x][y].draw_mode);
			}
		}
	}

}

void	draw_bullets(void)
{
	int			n;
	POLY_F4		*bullet_quad;
	TSPRT_8		*bullet_sprite;

	for (n=0; n<MAX_BULLETS; n++)
	{
		if (bullet_list[n].y!=-1)
		{
			bullet_sprite=&(cdb->sprite_8_list[cdb->next_sprite++]);
			SetTSprt_8(bullet_sprite,invader_tpage_info.tpage);
			SetShadeTex(&(bullet_sprite->sprite), 1);		/* ShadeTex disable */
			bullet_sprite->sprite.clut=invader_tpage_info.clut;

			if (n==0)
				setUV0(&(bullet_sprite->sprite),0,32);
			else
			{
				if (bullet_list[n].type==NORMAL_BULLET)
					setUV0(&(bullet_sprite->sprite),8,32);
				else
					setUV0(&(bullet_sprite->sprite),(((bullet_list[n].y>>2)&1)<<3)+16,32);
			}
			setXY0(&(bullet_sprite->sprite), bullet_list[n].x,bullet_list[n].y-BULLET_H);
			AddPrim(cdb->ot,&(bullet_sprite->draw_mode));
		}
	}
}


/* add a sprite for the fmv frame */
void	draw_fmv_frame(void)
{
#ifdef	ONE_QUAD_FMV


	int	frame_brightness=70;

	cdb->fmv_frame.tpage=getTPage(2,0,384,0);
	//cdb->fmv_frame.clut=getClut(0,500);

	setUVWH(&cdb->fmv_frame, 0, 0, 255, 192);

	/* calculate frame position */
	//setXYWH(&cdb->fmv_frame, ((320-QUAD_WIDTH)>>1),((240-QUAD_HEIGHT)>>1), QUAD_WIDTH,QUAD_HEIGHT);


	setXYWH(&cdb->fmv_frame, (160-frame_width),(120-frame_height), frame_width*2,frame_height*2);




	setRGB0(&cdb->fmv_frame,frame_brightness,frame_brightness,frame_brightness);
	setRGB1(&cdb->fmv_frame,frame_brightness,frame_brightness,frame_brightness);
	setRGB2(&cdb->fmv_frame,frame_brightness,frame_brightness,frame_brightness);
	setRGB3(&cdb->fmv_frame,frame_brightness,frame_brightness,frame_brightness);

	AddPrim(cdb->ot,&cdb->fmv_frame);


#else

	cdb->fmv_frame.tpage=getTPage(2,0,384,0);

	setUVWH(&cdb->fmv_frame, 0, 0, 255, 192);

	/* calculate frame position */
	setXYWH(&cdb->fmv_frame, 0,0, 256, 240);
	AddPrim(cdb->ot,&cdb->fmv_frame);


/* right hand side of frame */

	cdb->fmv_frame2.tpage=getTPage(2,0,384+256,0);

	setUVWH(&cdb->fmv_frame2, 0, 0, 63, 192);

	/* calculate frame position */
	setXYWH(&cdb->fmv_frame2, 256,0, 64, 240);
	AddPrim(cdb->ot,&cdb->fmv_frame2);

#endif	
	
}




/*
 * load texture pattern to VRAM
 */
static void load_texture4(u_short tpage[4], u_short clut[4])
{
	/* mat0, mat1, mat2, mat3 are Sprite animation image patterns.
	 * Animation patterns use 4 texture pages, and each page contains
	 * 64 patterns (64x64 size)
	 * Image format here is;
	 *	0x000-0x07f	CLUT  (256x2byte entry)
	 *	0x200-		INDEX (4bit mode, size=256x256)
	 */

	/* load 4 texture pages.
	 * Since each texture pattern is 4bit mode, it uses 64x256 area
	 * (not 256x256) of the frame buffer. 
	 */
	tpage[0] = LoadTPage(texture_page+0x80,	0, 0, 320,  0, 256,256);

	/* load the same data to another texture page as a test */

	/* load 4 texture CLUT */
	clut[0] = LoadClut(texture_page, 0,500);
}





#define			PARTICLE_DECAY		(16)

void	flush_particle_list(void)
{
	int		n;

 	for (n=0; n<MAX_PARTICLES; n++)
	{
		particle_list[n].size=0;
	}
}

void	add_particle(int x, int y, int xv, int yv, int red, int green, int blue)
{
	int		n;

 	for (n=0; n<MAX_PARTICLES; n++)
	{
		if (particle_list[n].size==0)
		{
			particle_list[n].x=x<<FRACTION_SHIFT;
			particle_list[n].y=y<<FRACTION_SHIFT;

			particle_list[n].ox[0]=x<<FRACTION_SHIFT;
			particle_list[n].oy[0]=y<<FRACTION_SHIFT;
			particle_list[n].ox[1]=x<<FRACTION_SHIFT;
			particle_list[n].oy[1]=y<<FRACTION_SHIFT;
			particle_list[n].ox[2]=x<<FRACTION_SHIFT;
			particle_list[n].oy[2]=y<<FRACTION_SHIFT;
			particle_list[n].ox[3]=x<<FRACTION_SHIFT;
			particle_list[n].oy[3]=y<<FRACTION_SHIFT;


			particle_list[n].xv=xv;
			particle_list[n].yv=yv;
			particle_list[n].size=5<<FRACTION_SHIFT;
			particle_list[n].red=red;
			particle_list[n].green=green;
			particle_list[n].blue=blue;
			return;
		}
	}

	/* no space in list, ignore */
}

#define	COL_DECAY		(3)

void process_all_particles(void)
{
#ifdef LINE_PARTICLES
	LINE_G2		*particle_line;
#else
	POLY_F4		*particle_quad;
#endif
	int			n;
	

/* move them all */

 	for (n=0; n<MAX_PARTICLES; n++)
	{
		if (particle_list[n].size>0)
		{
			particle_list[n].ox[3]=particle_list[n].ox[2];
			particle_list[n].oy[3]=particle_list[n].oy[2];
			particle_list[n].ox[2]=particle_list[n].ox[1];
			particle_list[n].oy[2]=particle_list[n].oy[1];
			particle_list[n].ox[1]=particle_list[n].ox[0];
			particle_list[n].oy[1]=particle_list[n].oy[0];
			particle_list[n].ox[0]=particle_list[n].x;
			particle_list[n].oy[0]=particle_list[n].y;


			particle_list[n].x+=particle_list[n].xv*FRAME_DELAY;
			particle_list[n].yv+=3*FRAME_DELAY;
			particle_list[n].y+=particle_list[n].yv*FRAME_DELAY;

			particle_list[n].red-=FRAME_DELAY*COL_DECAY;
			if (particle_list[n].red<0)
				particle_list[n].red=0;

			particle_list[n].green-=FRAME_DELAY*COL_DECAY;
			if (particle_list[n].green<0)
				particle_list[n].green=0;

			particle_list[n].blue-=FRAME_DELAY*COL_DECAY;
			if (particle_list[n].blue<0)
				particle_list[n].blue=0;


			particle_list[n].size-=PARTICLE_DECAY*FRAME_DELAY;
			if (particle_list[n].size<=0)
				particle_list[n].size=0;
			else
			{

		/* add poly */
				

#ifdef LINE_PARTICLES

				particle_line=&(cdb->line_list[cdb->next_line++]);

				setXY2(particle_line,(particle_list[n].ox[3]>>FRACTION_SHIFT),(particle_list[n].oy[3]>>FRACTION_SHIFT),
											(particle_list[n].x>>FRACTION_SHIFT),(particle_list[n].y>>FRACTION_SHIFT));
										
				setRGB0(particle_line,0,0,0);
				setRGB1(particle_line,particle_list[n].red,particle_list[n].green,particle_list[n].blue);
 				AddPrim(cdb->ot,particle_line);

#else
				particle_quad=&(cdb->quad_list[cdb->next_quad++]);
				int_size=1;	//particle_list[n].size>>(FRACTION_SHIFT+1);

				setXY4(particle_quad,(particle_list[n].x>>FRACTION_SHIFT)-int_size,(particle_list[n].y>>FRACTION_SHIFT)-int_size,
											(particle_list[n].x>>FRACTION_SHIFT)+int_size,(particle_list[n].y>>FRACTION_SHIFT)-int_size,
											(particle_list[n].x>>FRACTION_SHIFT)-int_size,(particle_list[n].y>>FRACTION_SHIFT)+int_size,
											(particle_list[n].x>>FRACTION_SHIFT)+int_size,(particle_list[n].y>>FRACTION_SHIFT)+int_size);
										
				setRGB0(particle_quad,particle_list[n].red,particle_list[n].green,particle_list[n].blue);
 				AddPrim(cdb->ot,particle_quad);
#endif

			}
		}
	}

}




void initialise_test_sound(void)
{

	Sound_Vh=file_load("D:\\STEVE\\SFX\\WORM2.VH");
	Sound_Vb=file_load("D:\\STEVE\\SFX\\WORM2.VB");

	Sound_Vab = Sound_Initialise(Sound_Vh, Sound_Vb);

	load_tim("D:\\STEVE\\GFX\\INVADERS.TIM", &invader_tpage_info);
}


void *file_load(unsigned char *name)
{
  unsigned long  handle,
           		length,
           		read;

  unsigned char	*addr;

  if((handle = PCopen(name, NULL, NULL))<0)
  {
     return NULL;
  }

  length = PClseek(handle, NULL, 2);

  addr = malloc(length);

  PClseek(handle, NULL, NULL);

  if((read=PCread(handle, addr, length))<0)
  {
     PCclose(handle);
		free(addr);
     return NULL;
  }

  PCclose(handle);
  return addr;

}



void load_tim(unsigned char *tim_name,TPAGE_INFO *tpage_info)
{
	unsigned long	*tim=NULL;
	TIM_IMAGE		tim_header;


	tim=file_load(tim_name);
	if (tim)
	{
		OpenTIM(tim);
		if (ReadTIM(&tim_header))
		{
//			tpage_info->tpage=LoadTPage(tim_header.paddr,	0, 0, tim_header.prect->x, tim_header.prect->y , tim_header.prect->w, tim_header.prect->h);
			tpage_info->tpage=LoadTPage(tim_header.paddr,	0, 0, tim_header.prect->x, tim_header.prect->y , 320, tim_header.prect->h);
			tpage_info->clut=LoadClut(tim_header.caddr, tim_header.crect->x, tim_header.crect->y);
		}
	}


}



void	play_sfx(int	sfx_num,int freq, int volume)
{
	if (vab==-1)
		return;		/* no sfx loaded */

	SsUtKeyOn(vab,sfx_num,0,freq,0,volume,volume);

}





/* sound initialisation cobbled from worms demo, cheers Glenn */



long	Sound_Initialise(unsigned char *vh, unsigned char *vb)
{

	vab=-1;		/* mark as unavailable */

	SsInit();								// RESET SOUND SYSTEM AND CLEAR MEMORY
//	SsSetTableSize(seq_table,2,2);	// SET TABLE SIZE
	//SsSetTickMode(SS_NOTICK);			// SET TICK MODE = NOTICK, USER VBL UPDATE
	SsSetTickMode(SS_TICK50);			// SET TICK MODE = NOTICK, USER VBL UPDATE

	vab =SsVabOpenHead(vh,-1);	// SEARCH FOR EMPTY VAB
	if (vab<0)
	{
		return FALSE;		// SsVabOpenHead Failed
	}

	if (SsVabTransBody(vb,vab)!=vab)
	{
		return FALSE;		// SsVabTransBody Failed
	}

	SsStart();					// START SOUND
	SsSetMVol(127,127);		// SET MAIN VOLUME
	SsSetSerialAttr(SS_SERIAL_A, SS_MIX, SS_SON);

	return TRUE;
}





void reset_bases(void)
{
	int				n;
	int				x,y;
	int				base_x_start,base_x_step;

	unsigned char	*data_ptr;

	RECT				vram_dest;

/* reset coordinates */

	base_x_step=(320-(max_bases*BASE_WIDTH))/(max_bases+1);
	base_x_start=base_x_step;
	for (n=0; n<MAX_BASES; n++)
		bases[n].x=base_x_start+(n*(base_x_step+BASE_WIDTH));
	

	for (n=0; n<max_bases; n++)
	{

	/* make some test data for this frame */

		if ((data_ptr=bases[n].base_frame)!=NULL)
		{
			for (y=0; y<BASE_HEIGHT; y++)
			{
			 	for (x=0; x<BASE_WIDTH; x++)
				{
					*data_ptr++=(4);
				}
			}


		/* nibble off the corners */

			for (y=0; y<8; y++)
			{
				data_ptr=bases[n].base_frame+(y*BASE_WIDTH);
			 	for (x=0; x<(8-y); x++)
				{
					*data_ptr++=0;
				}

				data_ptr=bases[n].base_frame+((y+1)*BASE_WIDTH)-(8-y);
			 	for (x=0; x<(8-y); x++)
				{
					*data_ptr++=0;
				}
			}


		/* nibble out a bit at the bottom */

			for (y=0; y<8; y++)
			{

				data_ptr=bases[n].base_frame+((y+(BASE_HEIGHT-8))*BASE_WIDTH)+16-y;
				for (x=0; x<((y<<1)+7); x++)
					*data_ptr++=0;
			}
		


		/* transfer this frame to VRAM */


		/* width/2 'cos it's 256 colour */

			vram_dest.x=320+(n*BASE_WIDTH>>1);
			vram_dest.y=256;
			vram_dest.w=BASE_WIDTH>>1;
			vram_dest.h=BASE_HEIGHT;
			//ret=LoadImage2(&vram_dest,(unsigned long*) bases[n].base_frame);
			//bases[n].tpage=GetTPage(1,0, vram_dest.x, vram_dest.y);

		/* loadTpage doesn't seem to work */
			bases[n].tpage = LoadTPage((unsigned long*) bases[n].base_frame,	1, 0, 320+(n*BASE_WIDTH>>1),  256, (BASE_WIDTH),BASE_HEIGHT);

		}

	}
}


/* 	initialise the bases with some test data
		The bases are 256 colour textures for ease of updating
*/
void initialise_bases(void)
{
	int				n;
	int				base_x_start,base_x_step;
	unsigned short	palette[256],clut;

	base_x_step=(320-(MAX_BASES*BASE_WIDTH))/(MAX_BASES+1);
	base_x_start=base_x_step;

	for (n=0; n<MAX_BASES; n++)
	{

		bases[n].x=base_x_start+(n*(base_x_step+BASE_WIDTH));
		bases[n].y=BASE_Y;
		bases[n].width=BASE_WIDTH;
		bases[n].height=BASE_HEIGHT;
		bases[n].base_frame=NULL;
		bases[n].base_frame=malloc(BASE_WIDTH*BASE_HEIGHT);
	}
	reset_bases();

	/* now we make a test palette */



	for (n=1; n<256; n++)
	{
		int	r,g,b;


		r=((rand()&15)+4);
		g=((rand()&15)+4)<<5;
		b=((rand()&15)+4)<<10;

		palette[n]=r|g|b;

	}

/* green scale */

	palette[0]=0;
	palette[1]=4<<5;
	palette[2]=8<<5;
	palette[3]=16<<5;
	palette[4]=31<<5;


	clut=LoadClut((unsigned long*) palette, 0, 501);

	for (n=0; n<MAX_BASES; n++)
		bases[n].clut=clut;


}



#define	EXPLO_WIDTH			(7)
#define	EXPLO_HEIGHT		(7)
#define	EXPLO_OFFSET_X		(EXPLO_WIDTH>>1)
#define	EXPLO_OFFSET_Y		(EXPLO_HEIGHT>>1)

void damage_base(int base_index, int x, int y, int hole_type)
{

	int	 			dest_x,dest_y,width,height;
	int				src_x=0,src_y=0;
	int				hole_col;
	unsigned char	*dest_ptr;

	width=holes[hole_type].width;
	height=holes[hole_type].height;

	if ((rand()&3)==0)
	{
		if ((rand()&1)==0)
			x++;
		else
			x--;
	}

/* x clipping */

	dest_x=x-(width>>1);
	if (dest_x<0)	/* clip left */
	{
		width+=dest_x;		/* REDUCE width */
		if (width<1)
			return;			/* clipped out, shouldn't happen but test anyway */

		src_x-=dest_x;		/* INCREASE data start in x */
		dest_x=0;
	}
	else	/* don't need to clip in both directions unless explosion is wider than base, and it isn't */
	{
		if (dest_x+width>=BASE_WIDTH)
			width=BASE_WIDTH-dest_x;
	}


/* y clipping */

	dest_y=y-(height>>1);
	if (dest_y<0)	/* clip top */
	{
		height+=dest_y;	/* REDUCE height */
		if (height<1)
			return;			/* clipped out, shouldn't happen but test anyway */

		src_y-=dest_y;		/* INCREASE data start in y */
		dest_y=0;
	}
	else	/* don't need to clip in both directions unless explosion is wider than base, and it isn't */
	{
		if (dest_y+height>=BASE_HEIGHT)
			height=BASE_HEIGHT-dest_y;		/* new height is difference */
	}

	for (y=0; y<height; y++)
	{
		dest_ptr=bases[base_index].base_frame+((dest_y+y)*BASE_WIDTH)+dest_x;
		for (x=0; x<width; x++)
		{
			hole_col=(*dest_ptr)-holes[hole_type].hole_data[x+src_x][y+src_y];
			if (hole_col<0)
				hole_col=0;
			*dest_ptr++=hole_col;
		}
	}

/* transfer to VRAM, we have to transfer a slice of the whole width */


	dest_ptr=bases[base_index].base_frame+(dest_y*BASE_WIDTH);

	LoadTPage((unsigned long*) dest_ptr,	1, 0, 320+(base_index*BASE_WIDTH>>1), 256+dest_y, BASE_WIDTH,height);


}

/* removes 8 lines from all bases from y_offset down */
void nibble_all_bases(int y_offset)
{
	int				n,x,y;
	unsigned char	*dest_ptr;
	int				colour;

	if (y_offset>=BASE_HEIGHT)
		return;

	for (n=0; n<max_bases; n++)
	{
		dest_ptr=bases[n].base_frame+(y_offset*BASE_WIDTH);

	/* clear the top 8 lines */
		for (y=0; y<8; y++)
		{
			for (x=0; x<BASE_WIDTH; x++)
			{
				*dest_ptr++=0;
			}
		}

		if (y_offset<(BASE_HEIGHT-8))
		{

		/* darken the last 3 lines */

			for (y=0; y<3; y++)
			{
				for (x=0; x<BASE_WIDTH; x++)
				{
					colour=*dest_ptr;
					colour-=(3-y);
					if (colour<0)
						*dest_ptr++=0;
					else
						*dest_ptr++=colour;
				}
			}
		}

	/* transfer the updated slice */

		dest_ptr=bases[n].base_frame+(y_offset*BASE_WIDTH);

		LoadTPage((unsigned long*) dest_ptr,	1, 0, 320+(n*BASE_WIDTH>>1), 256+y_offset, BASE_WIDTH,11);
		//LoadTPage((unsigned long*) bases[n].base_frame,	1, 0, 320+(n*BASE_WIDTH>>1), 256, BASE_WIDTH,BASE_HEIGHT);


	}

}


void draw_all_bases(void)
{

	int		n;


	for (n=0 ;n<max_bases; n++)
	{

	/* set texture pages and clut */
		cdb->base_quad[n].tpage=bases[0].tpage;		/* texture page referenced from the first base */
		cdb->base_quad[n].clut=bases[n].clut;

		setUVWH(&cdb->base_quad[n], n*BASE_WIDTH, 0, BASE_WIDTH-1, BASE_HEIGHT-1);

	/* calculate sprite position */

		setXYWH(&cdb->base_quad[n], bases[n].x, bases[n].y,BASE_WIDTH,BASE_HEIGHT);
		AddPrim(cdb->ot,&cdb->base_quad[n]);
	
	}

}

static int SetTSprt_16(TSPRT_16 *tsprt,int tpage)
{

	/* Merge 2 primitives to one */

 	SetSprt16(&tsprt->sprite);

 	SetDrawMode(&tsprt->draw_mode, 1, 1, tpage, NULL);

	if (MargePrim(&tsprt->draw_mode, &tsprt->sprite) != 0) {
		printf("Marge failed!\n");
		return(-1);
	}
	return(0);
}



static int SetTSprt_8(TSPRT_8 *tsprt,int tpage)
{

	/* Merge 2 primitives to one */

 	SetSprt8(&tsprt->sprite);

 	SetDrawMode(&tsprt->draw_mode, 1, 1, tpage, NULL);

	if (MargePrim(&tsprt->draw_mode, &tsprt->sprite) != 0) {
		printf("Marge failed!\n");
		return(-1);
	}
	return(0);
}


void	increment_score(int score_delta)
{
	player.score+=score_delta;
	if (player.score>player.high_score)
		player.high_score=player.score;
	player.extra_life_score+=score_delta;
	if (player.extra_life_score>=EXTRA_LIFE_AT)
	{
		player.lives++;
		player.extra_life_score-=EXTRA_LIFE_AT;
	}
}








/*
		file load routine from GODS
*/
LPVOID	File_LoadBinary(LPUCHAR name, LPULONG size)
{
	Sint32	handle, read, length;
	LPUCHAR	addr;
	UCHAR		result,pathname[1024];


  CdlFILE  fp;

/* files are pathed differently for CD */

	sprintf(pathname, "%s%s;1", "\\DATA\\", name);

  if(!CdSearchFile(&fp, pathname))
  {
     return NULL;
	}

  addr =malloc(fp.size);

  if(!(read=CdReadFile(pathname, (void*) addr, NULL)))
  {
    #ifdef DEBUG
     printf("Error Trying To Read %s\n", pathname);
    #endif
		free(addr);
     return (void*)FAIL;
  }

  CdReadSync(NULL, &result);

	*size=fp.size;
  return addr;


}













/*
	analogue test code

*/











typedef struct
{
	DRAWENV		draw;		/* drawing environment */
	DISPENV		disp;		/* display environment */
} DB2;

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
//void sprintf();
void *bzero(unsigned char *, int);
int PadChkMtap(int);


/*#main--- main routine */
int main()
{
	DB2 db[2],*cdb=0;

	bzero((unsigned char *)history, sizeof(history));
	bzero((unsigned char *)padbuff, sizeof(padbuff));

	ResetCallback();

#if MultiTap
	PadInitMtap(padbuff[0],padbuff[1]);
#else
	PadInitDirect(padbuff[0],padbuff[1]);
#endif
	//PadInitGun((unsigned char *)&gunPos, 10);
	PadStartCom();

	ResetGraph(0);		
	SetGraphDebug(0);	

	SetDefDrawEnv(&db[0].draw, 0,   0, 320, 240);
	SetDefDrawEnv(&db[1].draw, 0, 240, 320, 240);
	SetDefDispEnv(&db[0].disp, 0, 240, 320, 240);
	SetDefDispEnv(&db[1].disp, 0,   0, 320, 240);

	FntLoad(960, 256);	
	SetDumpFnt(FntOpen(4, 20, 312, 240, 0, 1024));	

	db[0].draw.isbg = 1;
	setRGB0(&db[0].draw, 60, 120, 120);
	db[1].draw.isbg = 1;
	setRGB0(&db[1].draw, 60, 120, 120);
	SetDispMask(1);

	pollhost();
	VSync(0);
	while (TRUE)
	{
		cdb  = (cdb==db)? db+1: db;	

		//setPad(0,padbuff[0]);
		//setPad(0x10,padbuff[1]);

		/* display controller state on port 1 */
		dispPad(0,padbuff[0]);

		/* display controller state on port 2 */
		dispPad(0x10,padbuff[1]);

		VSync(0);		/* wait for V-BLNK (1/60) */

		/* alternate double buffers */
		PutDispEnv(&cdb->disp);
		PutDrawEnv(&cdb->draw); 
		FntFlush(-1);
	}
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
x				hist->Motor1 -= 1;
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

	/*
		Specify actuator alignment parameter (it should be decided  
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

	if(initlevel==PadStateDiscon)
	{
		return;
	}

	if(PadInfoMode(port,InfoModeCurExID,0))
	{
		PadInfoMode(port,InfoModeCurExID,0);
	}
	else	/* non-expanded */
	{
		PadInfoMode(port,InfoModeCurID,0);
	}


	if(initlevel == PadStateFindPad)
	{
		hist->Send = 0;
	}

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
			/* set flag when accepted */
			if(PadSetActAlign(port,align))
			{
				hist->Send = 1;
			}
		}
	}

	if(initlevel < PadStateStable)
		return;

	maxnum = PadInfoAct(port,-1,0);
	for(count=0;count<maxnum;++count)
	{
			PadInfoAct(port,count,InfoActFunc);
			PadInfoAct(port,count,InfoActSub);
			PadInfoAct(port,count,InfoActSize);
			PadInfoAct(port,count,InfoActCurr);
	}


}

















































































































