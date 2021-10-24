//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// boulder File For <LEGO [Rock Raiders]>
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Include all Header Files
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
#include	"globals.h"

extern	Viewport_Globs viewportGlobs;



/*
	boulders will be handled by a pool, this will allow control of their generation,
	which should keep the frame-rate stable.

	They will have motion, spin and scale.
	They will bounce slightly.
	
	There could also be a sprite based pool for small boulders to reduce overhead,
	possibly switching from model based to sprite based at some suitable cut-off scale.

*/


BOULDERGLOBS	boulderGlobs;
SMOKEGLOBS		smokeGlobs;


enum		/* enumeration for sprite sequences for smoke/explosions */
{
	ST_NORMAL_SMOKE,
	ST_EXPLOSION,
};


/*
	create the boulder pool, assign models, etc
*/
BOOL	Boulder_CreateBoulderPool(void)
{
	int		n;

	if (boulderGlobs.boulderCont = Container_LoadHMDModel(legoGlobs.rootCont, "ROCKFALL\\BOULDER"))
	{

		boulderGlobs.refBoulderCont = Container_Create(legoGlobs.rootCont);
		boulderGlobs.refBoulderCont->type=TYPE_INTERNAL_DECAL;
		Container_SetParent(legoGlobs.rootCont,boulderGlobs.refBoulderCont);

/* these should really be a sequence, since we will need four types for the different level types... */

		boulderGlobs.boulderSpriteSet=Image_LoadSpriteSequence("SPRITES\\IBOULDER.TIM",1,1,32,32,-16,-16,FALSE, "NONE","DEFAULT",1);

		for (n=0; n<MAX_MODEL_BOULDERS; n++)
		{
			if (boulderGlobs.list[n].cont=Container_Clone(boulderGlobs.boulderCont))
			{
				boulderGlobs.list[n].scale=0;		/* free for use */
				Container_Hide(boulderGlobs.list[n].cont, TRUE);
			}
			else
				return	FALSE;		/* boulder pool creation failed */
		}

		/* the rest of the list are sprites, so we don't clone the boulder model for these */



		Container_SetRenderCallback(boulderGlobs.refBoulderCont,Boulder_RenderBoulderPool);

		return	TRUE;
	}

	return	FALSE;
}

#define		BOULDER_RANDOM_XY_OFFSET			(63)			/* ==(offset*2)-1 */
#define		BOULDER_RAMDOM_ANGLE_OFFSET		(1023)

#define		BOULDER_RANDOM_SPEED_OFFSET		(255)			/* power of 2-1 mask */
#define		BOULDER_RANDOM_SCALE_OFFSET		(255)

#define		BOULDER_MODEL_TO_SPRITE_CUT_OFF	(ToFIXED(0.25))		/* the scale below which a sprite is used instead of a model */

/*
	add a boulder at a position with a random x/y offset, direction with random offset,
	and a scale with a random offset
*/
int	Boulder_AddRandomBoulder(int x, int y, int z, int scale, int direction, int speed, int zSpeed, int time, int creationFlags)
{
	int				n;
	lpBOULDER		boulder=boulderGlobs.list;


	scale+=((rand()&BOULDER_RANDOM_SCALE_OFFSET)<<1);

	if (scale>BOULDER_MODEL_TO_SPRITE_CUT_OFF)
	{

		for (n=0; n<MAX_MODEL_BOULDERS; n++)			/* find a free one */
		{
			if (boulder->scale<=0)
			{
				boulder->x=(x+((rand()&BOULDER_RANDOM_XY_OFFSET)-(BOULDER_RANDOM_XY_OFFSET>>1)))<<12;
				boulder->y=(y+((rand()&BOULDER_RANDOM_XY_OFFSET)-(BOULDER_RANDOM_XY_OFFSET>>1)))<<12;
				boulder->z=z<<12;
				boulder->scale=scale;

				boulder->time=time;
				boulder->flags=creationFlags;

				boulder->speed=speed+((rand()&BOULDER_RANDOM_SPEED_OFFSET)<<7);
				boulder->yRot=direction+((rand()&BOULDER_RAMDOM_ANGLE_OFFSET)-(BOULDER_RAMDOM_ANGLE_OFFSET>>1));

			/* clear the clipped flag to make sure we don't kill boulder before processing first time */

				Container_SetScale(boulder->cont,scale);

				boulder->zSpeed=zSpeed;
				Boulder_SetStartState(boulder);
				
				return	n;
			}
			boulder++;
		}
	}
	else			/* look for one in the sprite section */
	{
		boulder=&boulderGlobs.list[MAX_MODEL_BOULDERS];

		for (n=MAX_MODEL_BOULDERS; n<MAX_BOULDERS; n++)
		{
			if (boulder->scale<=0)
			{
				boulder->x=(x+((rand()&BOULDER_RANDOM_XY_OFFSET)-(BOULDER_RANDOM_XY_OFFSET>>1)))<<12;
				boulder->y=(y+((rand()&BOULDER_RANDOM_XY_OFFSET)-(BOULDER_RANDOM_XY_OFFSET>>1)))<<12;
				boulder->z=z<<12;
				boulder->scale=scale;

				boulder->time=time;
				boulder->flags=creationFlags;

				boulder->speed=speed+((rand()&BOULDER_RANDOM_SPEED_OFFSET)<<7);
				boulder->yRot=direction+((rand()&BOULDER_RAMDOM_ANGLE_OFFSET)-(BOULDER_RAMDOM_ANGLE_OFFSET>>1));

				boulder->zSpeed=zSpeed;
				Boulder_SetStartState(boulder);
				
				return	n;
			}
			boulder++;
		}
	}

	return	-1;		/* whoop whoop, couldn't create a boulder */
}



/*
	add a boulder at x,y,z size scale, time game frames
	returns index to boulder if created , else -1 indicates failure
*/
int	Boulder_AddBoulder(int x, int y, int z, int scale, int direction, int speed, int zSpeed, int time, int creationFlags)
{
	int				n;
	lpBOULDER		boulder=boulderGlobs.list;


	if (scale>BOULDER_MODEL_TO_SPRITE_CUT_OFF)
	{
		for (n=0; n<MAX_MODEL_BOULDERS-5; n++)				/* -5 to ensure that some rockfall spaces are always available */
		{
			if (boulder->scale<=0)
			{
				boulder->x=x<<12;
				boulder->y=y<<12;
				boulder->z=z<<12;
				boulder->scale=scale;
				boulder->time=time;
				boulder->flags=creationFlags;
				boulder->speed=speed;
				boulder->yRot=direction;
				Container_SetScale(boulder->cont,scale);
				boulder->zSpeed=zSpeed;
				Boulder_SetStartState(boulder);
				return	n;
			}
			boulder++;
		}
	}
	else
	{
		boulder=&boulderGlobs.list[MAX_MODEL_BOULDERS];

		for (n=MAX_MODEL_BOULDERS; n<MAX_BOULDERS; n++)
		{
			if (boulder->scale<=0)
			{
				boulder->x=x<<12;
				boulder->y=y<<12;
				boulder->z=z<<12;
				boulder->scale=scale;
				boulder->time=time;
				boulder->flags=creationFlags;
				boulder->speed=speed;
				boulder->yRot=direction;
				boulder->zSpeed=zSpeed;
				Boulder_SetStartState(boulder);
				
				return	n;
			}
			boulder++;
		}
	}	

	return	-1;		/* whoop whoop, couldn't create a boulder */
}



/*
	update all active boulders in pool
	boulders are removed when their time reaches zero, or they are
	clipped from the viewpoint.
*/
void	Boulder_ServiceBoulderPool(int time)
{
	int				n,zSurface;
	int				xd,yd;
	int				newX,newY;

	lpBOULDER		boulder;
	lpLego_Block	block;

	static int genTime=0;

	genTime++;

	for (n=0; n<MAX_BOULDERS; n++)
	{
		boulder=&boulderGlobs.list[n];

		if (boulder->scale>0)
		{

			//boulder->scale+=boulder->scaleDelta;
			//if (boulder->scale<=0)
			//	continue;

			boulder->time--;
			if (boulder->time<=0)
			{
				boulder->scale=0;		/* terminate */
				Container_Hide(boulder->cont, TRUE);
				continue;
			}				

		/* new position */

			xd=rsin(boulder->yRot);
			yd=rcos(boulder->yRot);

			
			newX=boulder->x-Asm_MulFIX(Asm_MulFIX(boulder->speed,time),xd);
			newY=boulder->y+Asm_MulFIX(Asm_MulFIX(boulder->speed,time),yd);



			if (Boulder_CheckCollision(boulder,boulder->x,boulder->y,newX,newY,&boulder->yRot))
			{

			/* slow boulder after collision */

			/* ... */

			}
			else
			{
				boulder->x=newX;
				boulder->y=newY;
			}

		/* get new surface z position */

	 		if (Surface_GetHeight(legoGlobs.currLevel,boulder->x>>12,boulder->y>>12, &zSurface))
			{
				boulder->zSurface=zSurface<<12;
			}

			boulder->zSpeed+=Asm_MulFIX(BOULDER_GRAVITY_ACCELERATION,time);
			boulder->z+=Asm_MulFIX(boulder->zSpeed,time);

			if (boulder->z>=boulder->zSurface)
			{
				boulder->z=boulder->zSurface;

			/* bounce is proportional to scale, big things don't bounce as much as small things do
				obviously this is not a universal law ;ª}															 */

				boulder->zSpeed=-Asm_MulFIX(boulder->zSpeed,ONE-boulder->scale);

	
			/* deceleration is also proportional */

				boulder->speed-=(boulder->scale);
				if (boulder->speed<0)
					boulder->speed=0;

				if (boulder->flags & BOULDER_SPLIT_IN_TWO)
				{
					int				j;
					lpBOULDER		boulder2;
					

					/* re-scale this boulder */

					boulder->scale>>=1;
					boulder->yRot+=1024;
					boulder->flags&=~BOULDER_SPLIT_IN_TWO;					
					Container_SetScale(boulder->cont,boulder->scale);
					boulder->time=40+(rand()&15);


					Boulder_AddSmoke(boulder->x>>12, boulder->y>>12, (boulder->z>>12)-(boulder->scale>>4), (ONE<<1)+(rand()&4095), 0, -4, 255<<12, ToFIXED(-5.0), 255, 200, 200);

				/* ...and add another of the same scale, these will always be models, since splitters are large */

					boulder2=boulderGlobs.list;
					for (j=0; j<MAX_MODEL_BOULDERS; j++)
					{
						if (boulder2->scale<=0)
						{
							boulder2->x=boulder->x;
							boulder2->y=boulder->y;
							boulder2->z=boulder->z;
							boulder2->speed=boulder->speed;
							boulder2->zSpeed=boulder->zSpeed;
							boulder2->yRot=boulder->yRot-2048;
							boulder2->scale=boulder->scale;
							boulder2->time=30+(rand()&15);
							Container_SetScale(boulder2->cont,boulder2->scale);

						/* set position if before current processing index, otherwise it might display oddly */

							if (j<n)
							{
								Container_SetPosition(boulder2->cont,boulder2->x>>12,boulder2->y>>12,(boulder2->z>>12)-(boulder2->scale>>4));
								Container_SetRotation(boulder2->cont,boulder2->xRot,boulder2->yRot,boulder2->zRot);
							}
							break;

						}
						boulder2++;
					}
				}

			}


			boulder->xRot-=Asm_MulFIX(boulder->speed,time)>>8;

			Container_SetRotation(boulder->cont,boulder->xRot,boulder->yRot,boulder->zRot);

		//	set container position - note we have to offset the height to allow for the origin of the boulder
		//	which is in the centre of the model. A suitable fudge factor using the scale will achieve this.

			Container_SetPosition(boulder->cont,boulder->x>>12,boulder->y>>12,(boulder->z>>12)-(boulder->scale>>4));

			if (boulder->flags & BOULDER_FLAGS_GENERATE_SMOKE)
			{
				if (((genTime+n)&1)==0)
					Boulder_AddSmoke(boulder->x>>12,boulder->y>>12,(boulder->z>>12)-(boulder->scale>>4),(boulder->scale<<1)+0x400,0,-7,255<<12,ToFIXED(-25.5),255,128,0);
			}
							
		}
	}
}


#define			VIEWPORT_HW_PLUS_BC		(192+16)
#define			VIEWPORT_HH_PLUS_BC		(128+16)

/*
	render call-back for the boulder pool, split into two parts,
	models first, then sprites.
*/
void	Boulder_RenderBoulderPool(lpContainer callbackCont)
{
	int						n;
	MATRIX					mat;
	GsCOORDINATE2			coord;
	short						coords[3];
	long						depth=14,flag;
	SVECTOR					vector;
	lpBOULDER				boulder;

	VECTOR					pos;
	SVECTOR					rot;
	MATRIX					matLS, matLW;
	
	SPRITE_SET				*set;
	lpContainer				cont;
	int						z;


	GsInitCoordinate2(WORLD, &coord);
	GsGetLs(&coord, &mat);

	boulder=boulderGlobs.list;


/* should change these over to PMD models really... */

	for (n=0; n<MAX_MODEL_BOULDERS; n++)
	{

		if (boulder->scale)
		{

				LPDIRECT3DRMMESH		mesh = (LPDIRECT3DRMMESH)boulder->cont->modelData;

				cont=boulder->cont;
				vector.vx=-cont->coords.pos.vx;
				vector.vy=cont->coords.pos.vz;
				vector.vz=cont->coords.pos.vy;
				GsSetLsMatrix(&mat);

				RotTransPers(&vector,(long*)&coords[0],&depth,&flag);

				if (coords[0]<-(VIEWPORT_HW_PLUS_BC) || coords[0]>(VIEWPORT_HW_PLUS_BC) || coords[1]<-(VIEWPORT_HH_PLUS_BC) || coords[1]>(VIEWPORT_HH_PLUS_BC))
				{
					if (!(boulder->flags & BOULDER_FLAGS_DONT_CLIP))
						boulder->scale=0;		/* clip it */
				}
				else
				{

					G3D_IntVector(&pos, &cont->coords.pos);
					G3D_IntSVector(&rot, &cont->coords.rot);
					RotMatrix_gte(&rot, &cont->coords.coord.matrix);
					TransMatrix(&cont->coords.coord.matrix, &pos);
					cont->coords.coord.flg = NULL;
					GsGetLwsUnit(&cont->coords.coord, &matLW, &matLS);
					GsSetLightMatrix(&matLW);
					GsSetLsMatrix(&matLS);

					viewportGlobs.models_drawn++;
					HMD_AddModel(mesh->model, &gfxGlobs.Wot[gfxGlobs.bufID]);
				}

		}
		boulder++;
	}


	/* now the sprites */

	set=(SPRITE_SET*) boulderGlobs.boulderSpriteSet;


	for (;n<MAX_BOULDERS; n++)
	{

		/* later */
		if (boulder->scale)
		{
			GsSetLsMatrix(&mat);

			vector.vx=-boulder->x>>12;
			vector.vy=boulder->z>>12;
			vector.vz=boulder->y>>12;
			z=RotTransPers(&vector,(long*)&coords[0],&depth,&flag);


			if (coords[0]<-(VIEWPORT_HW_PLUS_BC) || coords[0]>(VIEWPORT_HW_PLUS_BC) || coords[1]<-(VIEWPORT_HH_PLUS_BC) || coords[1]>(VIEWPORT_HH_PLUS_BC))
			{
				if (!(boulder->flags & BOULDER_FLAGS_DONT_CLIP))
					boulder->scale=0;		/* clip it */
			}
			else
			{
				Image_DisplaySpriteIndex(set, 0, coords[0], coords[1], boulder->scale<<1,z, 0, 48);
				viewportGlobs.sprites_drawn++;
			}
		}
	
		boulder++;
	}


}


/*
	mark whether boulder is generated inside a dug or non dug block 
*/
void	Boulder_SetStartState(lpBOULDER boulder)
{
	lpLego_Block	block;

	block=&blockValue(legoGlobs.currLevel,(boulder->x>>(12+9)),(boulder->y>>(12+9)));
	if ((block->flags & LEGOBLOCK_FLAG_BLOCK_DUG))
		boulder->startState=TRUE;
	else
		boulder->startState=FALSE;
}
		

/*
	check for collision with non-dug blocks, if in collision generate new angle
	to bounce off block
*/
BOOL	Boulder_CheckCollision(lpBOULDER boulder, int oldX, int oldY, int newX, int newY, int *angle)
{
	lpLego_Block	block;
	int				oldBx,oldBy;
	int				newBx,newBy;
	int				xd,yd;
	int				oldAngle;
	int				newAngle;

	newBx=newX>>(12+9);			/* >>12 = int >>9 ==/512 */
	newBy=newY>>(12+9);

	block=&blockValue(legoGlobs.currLevel,newBx,newBy);
	if (!(block->flags & LEGOBLOCK_FLAG_BLOCK_DUG))
	{
		if (!boulder->startState)		
			return	FALSE;				/* carry on until we reach a dug block first */

		oldBx=oldX>>(12+9);
		oldBy=oldY>>(12+9);
		xd=newBx-oldBx;
		yd=newBy-oldBy;

		oldAngle=(*angle & 4095);

		if ((xd&1)==(yd&1))
		{
			*angle+=2048;			/* must be a diagonal so bounce back the way we came */
			return	TRUE;
		}

		if (xd==0)
		{
			if (yd==-1)		/* north */
			{
				*angle=(2048-oldAngle);
				return	TRUE;
			}

			/* south */

			if (oldAngle>2048)
				*angle=2048+(4096-oldAngle);
			else
				*angle=2048-oldAngle;

			return	TRUE;
		}

		if (xd==-1)		/* west */
		{

			*angle=3072+(1024-oldAngle);
			return	TRUE;
		}


		/* well it bloody well better be east after all this */

		*angle=1024+(3072-oldAngle);

		return	TRUE;
	}

	boulder->startState=TRUE;

	return	FALSE;

}





/*
	Mmm, cleanup code for boulder pool.
	Not sure there would be any point to this.
	Probably better to allocate and leave them,
	since they would be required for every level,
	and texture changes would be automatic anyway.
*/
BOOL	Boulder_DestroyBoulderPool(void)
{
	return	TRUE;
}


/*
	generate some boulders and smoke for a dug block
*/
void	Boulder_CreateRockFall(int blockX, int blockY, int yAngle)
{
	int 				bbX,bbY;
	lpLego_Block	block=&blockValue(legoGlobs.currLevel,blockX,blockY);
	int				width=legoGlobs.currLevel->width;

	bbX=blockX<<9;
	bbY=blockY<<9;


 

	Boulder_AddRandomBoulder(bbX+256,bbY+128,-128,
		ONE>>1, yAngle, (((rand()&127)+128)<<6), -74<<12, 50+(rand()&15), BOULDER_FLAGS_DONT_CLIP|BOULDER_SPLIT_IN_TWO);


	Boulder_AddRandomBoulder(bbX+128,bbY+512-128,-128,
		ONE>>1, yAngle, (((rand()&127)+128)<<6), -71<<12, 50+(rand()&15), BOULDER_FLAGS_DONT_CLIP|BOULDER_SPLIT_IN_TWO);

	Boulder_AddRandomBoulder(bbX+512-128,bbY+512-128,-128,
		ONE>>1, yAngle, (((rand()&127)+128)<<6), -73<<12, 50+(rand()&15), BOULDER_FLAGS_DONT_CLIP|BOULDER_SPLIT_IN_TWO);



/* smoke gen test */
	Boulder_AddRandomBoulder(bbX+448,bbY+300,block->topLeftAlt-64,
		ONE>>2, yAngle, (((rand()&127)+128)<<8), -70<<12, 70+(rand()&31), BOULDER_FLAGS_DONT_CLIP|BOULDER_FLAGS_GENERATE_SMOKE);

	Boulder_AddRandomBoulder(bbX+448,bbY+300,block->topLeftAlt-64,
		ONE>>2, yAngle, (((rand()&127)+128)<<8), -65<<12, 70+(rand()&31), BOULDER_FLAGS_DONT_CLIP|BOULDER_FLAGS_GENERATE_SMOKE);



/* put some smoke in each corner, and one in the middle, but with random offsets */


	Boulder_AddSmoke(bbX+RRO(63,64), bbY+RRO(63,64), block->topLeftAlt-350,
		 ((ONE+(rand()&2047))<<1), 0, -3<<12, ((240+(rand()&15))<<12), ToFIXED(-1.8), 255, 200, 100);

	Boulder_AddSmoke(bbX+RRO(63,512-64), bbY+RRO(63,64), block[1].topLeftAlt-350,
		 ((ONE+(rand()&2047))<<1), 0, -3<<12, ((240+(rand()&15))<<12), ToFIXED(-1.8), 255, 200, 100);

	Boulder_AddSmoke(bbX+RRO(63,64), bbY+RRO(63,512-64), block[width].topLeftAlt-350,
		 ((ONE+(rand()&2047))<<1), 0, -3<<12, ((240+(rand()&15))<<12), ToFIXED(-1.8), 255, 200, 100);

	Boulder_AddSmoke(bbX+RRO(63,512-64), bbY+RRO(63,512-64), block[width+1].topLeftAlt-350,
		 ((ONE+(rand()&2047))<<1), 0, -3<<12, ((240+(rand()&15))<<12), ToFIXED(-1.8), 255, 200, 100);

	Boulder_AddSmoke(bbX+RRO(63,256), bbY+RRO(63,256), block->topLeftAlt-350,
		 ((ONE+1024+(rand()&2047))<<1), 0, -4<<12, (255<<12), ToFIXED(-2.3), 255, 255, 255);
	

}






/* ---------------------------------------------------*/
/* --- Smoke/explosions handling ---------------------*/
/* ---------------------------------------------------*/


#define		SMOKE_CLIP_SIZEX	(192+32)
#define		SMOKE_CLIP_SIZEY	(128+32)

/*
	sprites for the smoke particles are drawn here for speed
*/
void	Boulder_ServiceSmokePool(void)
{
	int						n;
	lpSMOKE					smoke,lastSmoke;

	GsCOORDINATE2			coord;
	MATRIX					mat;
	short						coords[3];
	long						depth=14,flag;
	SVECTOR					vector;
	int						z;
	VECTOR3D					pos;
	VECTOR3D					rot;
	lpSPRITE_SET			set;
	int						frame_num,frame,rotation;
	int						first=TRUE;
	int						alphaScale;
	int						time;
	
	GsSPRITE		*s;							/* make this a pointer to the appropriate one */
	GsSPRITE		smokeSprite;			/* pre-set this one for the smoke which is used most frequently, and doesn't animate */
	GsSPRITE		scratchSprite;			/* this is the general one */

	SPR_FRAME	*seq_frame;

	static unsigned long		staticAttr=0x50000000;
	static int	staticAlpha=128;


	time=legoGlobs.updateTime;
	

	set=(SPRITE_SET*) smokeGlobs.smokeSpriteSet[ST_NORMAL_SMOKE];
	seq_frame=set->frames;
	smokeSprite.u=seq_frame->u;
	smokeSprite.v=seq_frame->v;
	smokeSprite.tpage=set->tpage;
	smokeSprite.cx=set->cx;
	smokeSprite.cy=set->cy;
	smokeSprite.w=seq_frame->w;
	smokeSprite.h=seq_frame->h;
	smokeSprite.mx=-set->off_x;
	smokeSprite.my=-set->off_y;
	smokeSprite.attribute=0x50000000;


	/* check later */
		GsInitCoordinate2(WORLD, &coord);
		GsGetLs(&coord, &mat);

	for (n=0; n<MAX_SMOKE_PARTICLES; n++)
	{
		smoke=&smokeGlobs.list[n];
		if (smoke->scaleDelta)
		{
			smoke->scale+=smoke->scaleDelta;
			if (smoke->scale<=0)
			{
				smoke->scaleDelta=0;
				continue;
			}	
		}

		smoke->alpha+=Asm_MulFIX(smoke->alphaDelta,time);

		if (smoke->alpha<=0)
		{
			smoke->scale=0;
			smoke->scaleDelta=0;
			continue;
		}

		set=(SPRITE_SET*) smokeGlobs.smokeSpriteSet[smoke->type];


		if (smoke->animSpeed!=0)
		{
			smoke->animTotal+=smoke->animSpeed;
			smoke->animFrame=smoke->animTotal>>12;	


		/* we assume these sequences don't loop, or go backwards */

			if (smoke->animFrame>=set->loop_seq_len)
			{
				smoke->scale=0;
				smoke->scaleDelta=0;
				continue;
			}
		}

		
		smoke->z+=Asm_MulFIX(smoke->zSpeed,time);

		smoke->rotation+=smoke->rotationDelta;
		vector.vx=-smoke->x;
		vector.vy=smoke->z>>12;
		vector.vz=smoke->y;

		GsSetLsMatrix(&mat);
		z=RotTransPers(&vector,(long*)&coords[0],&depth,&flag);

/* fudged, 'cos I can't look up the viewport size, but I know what size it is. */

		if (coords[0]<-(SMOKE_CLIP_SIZEX) || coords[0]>(SMOKE_CLIP_SIZEX) || coords[1]<-(SMOKE_CLIP_SIZEY) || coords[1]>(SMOKE_CLIP_SIZEY))
		{
			smoke->scale=0;
			smoke->scaleDelta=0;
			continue;
		}



		seq_frame=set->frames;
		seq_frame+=smoke->animFrame;


		if (smoke->type==ST_NORMAL_SMOKE)		/* pre-cached data */
		{
			s=&smokeSprite;
		}
		else
		{
			s=&scratchSprite;

			s->u=seq_frame->u;
			s->v=seq_frame->v;
			s->tpage=set->tpage;

			s->cx=set->cx;
			s->cy=set->cy;	//+clutIndex;
			s->w=seq_frame->w;
			s->h=seq_frame->h;
			s->mx=-set->off_x;
			s->my=-set->off_y;
			s->attribute=0x50000000;
		}

		alphaScale=smoke->alpha>>8;		/* convert to 255==1.0 */
		s->r=(Asm_MulFIX(alphaScale,smoke->red))>>4;
		s->g=(Asm_MulFIX(alphaScale,smoke->green))>>4;
		s->b=(Asm_MulFIX(alphaScale,smoke->blue))>>4;

/* position and offset */
		s->x=coords[0];
		s->y=coords[1];

/* scale */
		s->scalex=s->scaley=smoke->scale;

		s->rotate=smoke->rotation;

		GsSortSprite(s, &gfxGlobs.Wot[gfxGlobs.bufID], z);
		viewportGlobs.sprites_drawn++;


	}
}



/*
	create the smoke/explosion pool.
*/
BOOL	Boulder_CreateSmokePool(void)
{
	int		n;


	if (smokeGlobs.smokeCont = Container_Create(legoGlobs.rootCont))
	{
		smokeGlobs.smokeCont->type=TYPE_INTERNAL_DECAL;
		Container_SetParent(legoGlobs.rootCont,smokeGlobs.smokeCont);
				
		for (n=0; n<MAX_SMOKE_PARTICLES; n++)
		{
			smokeGlobs.list[n].scale=0;				/* free for use */
			smokeGlobs.list[n].red=255;
			smokeGlobs.list[n].green=255;
			smokeGlobs.list[n].blue=255;
			smokeGlobs.list[n].scaleDelta=0;
		}

		Container_SetRenderCallback(smokeGlobs.smokeCont,Boulder_ServiceSmokePool);
		smokeGlobs.smokeSpriteSet[ST_NORMAL_SMOKE]=Image_LoadSpriteSequence("SPRITES\\SMOKE1.TIM",1,1,32,32,-16,-16,FALSE, "NONE","DEFAULT",1);

/* more sequences go here... */
//		smokeGlobs.smokeSpriteSet[ST_EXPLOSION]=Image_LoadSpriteSequence("CREATURE\\SCORPION\\SCORPION.TIM",1,8,32,32,-16,-16,FALSE, "NONE","DEFAULT",1);

		return	TRUE;
	}

	return	FALSE;
}

/*
		add a smoke particle
*/
int	Boulder_AddSmoke(int x, int y, int z, int scale, int scaleDelta, int zSpeed, int startAlpha, int alphaDelta, int red, int green, int blue)
{
	int			n;
	lpSMOKE		smoke=smokeGlobs.list;

	for (n=0; n<MAX_SMOKE_PARTICLES; n++)
	{
		if (smoke->scale<=0)
		{
			smoke->type=ST_NORMAL_SMOKE;
			smoke->animSpeed=0;
			smoke->flags=0;
			smoke->animTotal=0;
			smoke->animFrame=0;
			smoke->x=x;
			smoke->y=y;
			smoke->z=z<<12;
			smoke->scale=scale;
			smoke->zSpeed=zSpeed;
			smoke->alpha=startAlpha;
			smoke->alphaDelta=alphaDelta;

		/* pre-shift colours */

			smoke->red=red<<4;
			smoke->green=green<<4;
			smoke->blue=blue<<4;
			smoke->rotation=rand();
			smoke->rotationDelta=(rand()&2047)+2048;
			return	n;
		}
		smoke++;
	}

	return	-1;		/* whoop whoop, couldn't create a smoke particle */
}

int	Boulder_AddEffect(int x, int y, int z, int scale, int scaleDelta, int zSpeed, int startAlpha, int alphaDelta, int red, int green, int blue, int sequence, int animSpeed)
{
	int			n;
	lpSMOKE		smoke=smokeGlobs.list;

	for (n=0; n<MAX_SMOKE_PARTICLES; n++)
	{
		if (smoke->scale<=0)
		{
			smoke->type=sequence;
			smoke->animSpeed=animSpeed;
			smoke->flags=0;
			smoke->animTotal=0;
			smoke->animFrame=0;
			smoke->x=x;
			smoke->y=y;
			smoke->z=z<<12;
			smoke->scale=scale;
			smoke->zSpeed=zSpeed;
			smoke->alpha=startAlpha;
			smoke->alphaDelta=alphaDelta;

		/* pre-shift colours */

			smoke->red=red<<4;
			smoke->green=green<<4;
			smoke->blue=blue<<4;
			smoke->rotation=rand();
			smoke->rotationDelta=(rand()&2047)+2048;
			return	n;
		}
		smoke++;
	}

	return	-1;		/* whoop whoop, couldn't create an effect particle */
}
