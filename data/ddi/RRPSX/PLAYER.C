//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// player and minifigures For <LEGO [Rock Raiders]>
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

#include	"globals.h"




#define		MINIFIGURE_FORWARD_SPEED_CAP		(ToFIXED(20.0))
#define		MINIFIGURE_ACCEL_DELTA_FORWARD	(ToFIXED(3.0))
#define		MINIFIGURE_BACKWARD_SPEED_CAP		(ToFIXED(15.0))
#define		MINIFIGURE_ACCEL_DELTA_BACKWARD	(ToFIXED(3.0))
#define		MINIFIGURE_DECEL_DELTA				(ToFIXED(2.5))
#define		MINIFIGURE_TURN_RATE_CAP			(64)
#define		MINIFIGURE_GRADIENT_LIMIT			(3)




#define		MINIFIGURE_FORCETURN_DELTA			(32)		/* this is used when in collision, to force the minifigure
																			to turn in the direction that will bring it out of collision  */

#define		MINIFIGURE_MAX_DRILL_SPEED				(127)
#define		MINIFIGURE_MAX_DRILL_DELTA				(16)
#define		MINIFIGURE_DRILL_FREQUENCY				(60)
#define		ROCKFALL_FREQUENCY						(50)

#define		MINIFIGURE_FOOTSTEP_FREQUENCY			(50)
#define		MINIFIGURE_FOOTSTEP_VOLUME				(30)


#define		MINIFIGURE_PUSHER_GUN_AMMO_START		(10)
#define		MINIFIGURE_PUSHER_GUN_AMMO_MAX		(100)
#define		MINIFIGURE_DYNAMITE_STICKS_START		(0)
#define		MINIFIGURE_DYNAMITE_STICKS_MAX		(10)

#define		MINIFIGURE_START_HEALTH					(256)
#define		MINIFIGURE_HEALTH_DELTA_IN_WATER		(8)
#define		MINIFIGURE_HEALTH_DELTA_IN_LAVA		(32)


/*
	initialise player, and assign minifigure
*/
void	Player_CreatePlayer(int playerId, int minifigureIndex)
{
	lpContainer		tempCont;
	int				n;
	lpPLAYER			player=&objectGlobs.playerList[playerId];
	lpOBJECT			object=&objectGlobs.objectList[minifigureIndex];
	lpMINIFIGURE	minifigure;

	minifigure=object->objectData;

	player->flags=0;
	player->reticulePulseIndex=0;
	player->reticuleAlpha=0;
	player->id=playerId;


	player->minifigureObject=object;
	player->minifigure=minifigure;

/* initialise control set for player */

	Control_initialiseControlSet(player->controlSet);
	player->controllerConnected=TRUE;

/* initialise some minifigure data for this player */


	minifigure->drillSfxVoice=-1;
	minifigure->travel=0;
	minifigure->lastTravel=0;
	minifigure->maxRockType=Lego_SurfaceType_Hard;
	minifigure->dynamiteSticks=MINIFIGURE_DYNAMITE_STICKS_START;
	minifigure->pusherGunAmmo=MINIFIGURE_PUSHER_GUN_AMMO_START;
	minifigure->health=MINIFIGURE_START_HEALTH;
/* and make him active */

	player->flags|=PLAYER_FLAG_MINIFIGURE_ACTIVE;

	objectGlobs.numPlayers++;

}


/*
	set the minifigure associated with the passed player to the position of the vehicle
	associated with the player

	returns TRUE if we could set the minifigure down without collision, else FALSE

	if flag is TRUE we actually re-position the minifigure, else we just validate that we
	could set him down at the craft's current position if necessary.
*/
BOOL	Player_SetMinifigureToCraftPosition(lpPLAYER player, int angle, BOOL flag)
{
	int					height;
	unsigned char		brightness;
	int					xOff,yOff,n;
	static	const		angleOffset[4]={512,-512,(2048-512),(2048+512)};			/* angle offsets to apply */

	for (n=0; n<4; n++)
	{

		xOff=rsin(player->craftObject->angleY+angleOffset[n])*(player->craftObject->activationRadius*6);
		yOff=rcos(player->craftObject->angleY+angleOffset[n])*(player->craftObject->activationRadius*6);

		if (PlayerCheckCollisionAtPoint(player->craftObject->x-xOff,player->craftObject->y+yOff))
		{
			if (flag)
			{
				player->minifigureObject->x=(player->craftObject->x)-(xOff);
				player->minifigureObject->y=(player->craftObject->y)+(yOff);

				if (!Surface_GetHeightAndBrightness(legoGlobs.currLevel,player->minifigureObject->x>>12,player->minifigureObject->y>>12, &height,&brightness))
					height=0;
				Container_SpriteSetSpriteBrightness(player->minifigure->refCont,128);
				player->minifigureObject->z=height<<12;
				player->minifigureObject->zSurface=height<<12;
				player->minifigureObject->angleY=player->craftObject->angleY+256;
				Container_Hide(player->minifigure->refCont, FALSE);
				Container_Hide(player->minifigure->shadowCont, FALSE);
			}
			return	TRUE;
		}
	}
	return	FALSE;
}



/*
	check for suitablity of placement for a minifigure
*/
BOOL	PlayerCheckCollisionAtPoint(int x, int y)
{
	lpLego_Block	block;


	x>>=12;
	y>>=12;

	block=&blockValue(legoGlobs.currLevel,x>>9,y>>9);
	if (!(block->flags & LEGOBLOCK_FLAG_BLOCK_DUG))
		return	FALSE;												/* not dug, bug out */	

	if (block->flags & (MAP3DBLOCK_VERTEXWOBBLES|MAP3DBLOCK_UVWOBBLES))
		return	FALSE;												/* water or lava */

	return	TRUE;
}


/*
	create minifigure at position and rotation
*/	
BOOL	Player_CreateMinifigure(int x, int y, int rotation, int minifigureIndex)
{
	int					height,n;
	lpMINIFIGURE		minifigure;
	lpOBJECT				newObject;
	lpContainer			shadowCont;

	if (minifigureIndex<MAX_MINIFIGURES)
	{
		newObject=&objectGlobs.objectList[minifigureIndex];
		//for (n=MINIFIGURE_START; n<(MINIFIGURE_START+MAX_MINIFIGURES); n++)
		{
			if (!(newObject->cont))
			{
				minifigure=&objectGlobs.minifigureList[minifigureIndex];
				if (!Surface_GetHeight(legoGlobs.currLevel,x,y, &height))
					height=0;

				Container_SpriteSetSpriteBrightness(minifigure->refCont,128);

				newObject->x=x<<12;
				newObject->y=y<<12;
				newObject->z=height<<12;
				newObject->zSurface=height<<12;
				newObject->angleY=rotation;
				Container_Hide(minifigure->refCont, FALSE);
				newObject->cont=minifigure->refCont;
				newObject->objectData=minifigure;
				newObject->class=OC_MINIFIGURE;
				newObject->type=0;						/* presently only one type */
				newObject->cont->clipSize=16;
				Container_SetWorldPosition(newObject->cont,newObject->x>>12,newObject->y>>12,newObject->z>>12);


			/* create a render callback container to draw the shadows */


				shadowCont=Container_Create(legoGlobs.rootCont);
				if (shadowCont)
				{
					minifigure->shadowCont=shadowCont;
					shadowCont->type=TYPE_INTERNAL_DECAL;
					Container_SetParent(legoGlobs.rootCont,shadowCont);
					Container_SetRenderCallback(shadowCont,Player_RenderShadow);
					shadowCont->owner=newObject;
				}

				return	TRUE;
			}
		}
	}
	return	FALSE;
}


/*
	Update a controlled minifigure.
	minifigures turn and walk, they can walk through dug areas only.
	button (X) makes them enter a vehicle if they are near enough.
	passing through an object they can collect, eg a crystal will cause collection
*/

void	Player_UpdateMinifigure(lpOBJECT object,lpPLAYER player, int time)
{
	lpMINIFIGURE 	minifigure=object->objectData;

	VECTOR			v1,v2,v3;
	int				nextX,nextY,nextZ;
	int				xd,yd;
	int				turnSpeed;
	int				turning=FALSE,inAir=FALSE;
	int				tempSurface;
	lpCONTROL 		control;

	unsigned char	*padBuffer;
	int				padType;

	REAL				turnScale=0;
	REAL				moveScale=0;
	int				forwardSpeedCapScaled;
	int				backwardSpeedCapScaled;
	int				forceTurn;
	lpOBJECT			craftObject;


	time=ONE;

	if (player)
	{
		control=player->controlSet;
		padBuffer=player->padBuffer;
		padType=padBuffer[MODE_AND_SIZE]>>4;

	/* toggle combined/separated analogue control */

		if (PAD_EVENT(control,CONTROL_DS_LEFT))
		{
			player->flags^=PLAYER_FLAG_COMBINE_ANALOGUE;
			CLEAR_EVENT_RELEASE(control,CONTROL_DS_LEFT);
		}


		if (player->flags & PLAYER_FLAG_COMBINE_ANALOGUE)
			moveScale=((255-padBuffer[LEFT_STICK_VERTICAL])<<5)-((127<<5)+16);
		else
			moveScale=((255-padBuffer[RIGHT_STICK_VERTICAL])<<5)-((127<<5)+16);

		moveScale=Asm_MulFIX(moveScale,time);
		
		turnScale=(padBuffer[LEFT_STICK_HORIZONTAL]<<5)-((127<<5)+16);
		turnScale=Asm_MulFIX(turnScale,time);

#ifndef __CDVERSION
/*-----------------------------------------------------------------------------------------------------------------*/
{
	char	string[64];

	sprintf(string, "ms=%d, ts=%d", moveScale,turnScale);
	Font_PrintF(legoGlobs.stdFont,8,40,string);
}
/*-----------------------------------------------------------------------------------------------------------------*/
#endif


	}
	else
	{
		control=nullControlSet;		/* uncontrolled craft need to idle, but they don't want input */
		padType=4;

	}

	if (moveScale>0)
	{
		if (moveScale<THRESHOLD)
			moveScale=0;
	}
	else
	{
		if (moveScale>-THRESHOLD)
			moveScale=0;
	}

	if (turnScale>0)
	{
		if (turnScale<THRESHOLD)
			turnScale=0;
	}
	else
	{
		if (turnScale>-THRESHOLD)
			turnScale=0;
	}

/* adjust ceiling on maximum speeds based on stick position */

	if (padType==DUAL_SHOCK)
	{
		forwardSpeedCapScaled=Asm_MulFIX(moveScale,MINIFIGURE_FORWARD_SPEED_CAP);
		backwardSpeedCapScaled=Asm_MulFIX(moveScale,MINIFIGURE_BACKWARD_SPEED_CAP);
	}
	else
	{
		forwardSpeedCapScaled=MINIFIGURE_FORWARD_SPEED_CAP;
		backwardSpeedCapScaled=MINIFIGURE_BACKWARD_SPEED_CAP;
	}


/* minifigure rotation, no inertia on turning, though dual shock control allows slow rotation of course */

	if (padType==STANDARD_JOYPAD)
	{
		if (PAD_EVENT(control,CONTROL_TURN_LEFT))
		{
			object->angleY-=(Asm_MulFIX(MINIFIGURE_TURN_RATE_CAP<<12,time))>>12;
			CLEAR_EVENT_IMMEDIATE(control,CONTROL_TURN_LEFT);
			turning=TRUE;
		}
		else
		{
			if (PAD_EVENT(control,CONTROL_TURN_RIGHT))
			{
				object->angleY+=(Asm_MulFIX(MINIFIGURE_TURN_RATE_CAP<<12,time))>>12;
				CLEAR_EVENT_IMMEDIATE(control,CONTROL_TURN_RIGHT);
				turning=TRUE;
			}
		}
	}
	else
	{
		object->angleY+=Asm_MulFIX(turnScale,MINIFIGURE_TURN_RATE_CAP);
	}



	xd=rsin(object->angleY);
	yd=rcos(object->angleY);


/* probably need a cap check here */

//	minifigure->speed+=(nextZ-(FromFIXED(craft->zSurface)))<<9;


	if (padType==STANDARD_JOYPAD)
	{
		if (PAD_EVENT(control,CONTROL_FORWARD))
		{
			CLEAR_EVENT_IMMEDIATE(control,CONTROL_FORWARD);
			if (object->speed<MINIFIGURE_FORWARD_SPEED_CAP)
				object->speed+=Asm_MulFIX(MINIFIGURE_ACCEL_DELTA_FORWARD,time);
		}
		else if (PAD_EVENT(control,CONTROL_REVERSE))
		{
			CLEAR_EVENT_IMMEDIATE(control,CONTROL_REVERSE);
			if (object->speed>-MINIFIGURE_BACKWARD_SPEED_CAP)
				object->speed-=Asm_MulFIX(MINIFIGURE_ACCEL_DELTA_BACKWARD,time);
		}
		else
		{
			/* make minifigure decelerate */

			if (object->speed<0)
				object->speed+=Asm_MulFIX(MINIFIGURE_DECEL_DELTA,time);
			else if(object->speed>0)
				object->speed-=Asm_MulFIX(MINIFIGURE_DECEL_DELTA,time);
		}
	}
	else	/* dual shock */
	{
		if (moveScale>0)
		{
		 	if (object->speed<forwardSpeedCapScaled)
				object->speed+=Asm_MulFIX(moveScale,MINIFIGURE_ACCEL_DELTA_FORWARD);
		}
		else if (moveScale<0)
		{
			if (object->speed>backwardSpeedCapScaled)
				object->speed+=Asm_MulFIX(moveScale,MINIFIGURE_ACCEL_DELTA_BACKWARD);
		}
		else
		{
			/* make minifigure decelerate */

			if (object->speed<0)
				object->speed+=Asm_MulFIX(MINIFIGURE_DECEL_DELTA,time);
			else if(object->speed>0)
				object->speed-=Asm_MulFIX(MINIFIGURE_DECEL_DELTA,time);
		}
	}


#define		MINIFIGURE_FOOTSTEP_GENERATION		(2)

	{
		unsigned char 	brightness;
		int				width=((legoGlobs.currLevel->width-1)<<(9+12))-1;
		int				height=((legoGlobs.currLevel->height-1)<<(9+12))-1;
		lpLego_Block	block;
		int				speed;

		static int	temp=0;

		nextX=object->x;
		nextY=object->y;

		if (object->speed!=0)
		{
			speed=Asm_MulFIX(object->speed,time);

			nextX-=Asm_MulFIX(speed,xd);
			nextY+=Asm_MulFIX(speed,yd);

			/* travel is a counter of absolute speed, used for animation and footstep SFX generation */

			if (object->speed>0)
				minifigure->travel+=speed;
			else
				minifigure->travel-=speed;


			if (((minifigure->travel>>16)-minifigure->lastTravel)>=MINIFIGURE_FOOTSTEP_GENERATION)
			{
				minifigure->lastTravel+=MINIFIGURE_FOOTSTEP_GENERATION;

				Container_UpdateAnimation(minifigure->refCont,object->speed>>4);

				if (temp++==4)
				{
					Sfx_PlayEffect(SFX_SAMPLE_FOOTSTEP,MINIFIGURE_FOOTSTEP_FREQUENCY+(rand()&1),MINIFIGURE_FOOTSTEP_VOLUME);
					temp=0;
				}
			}
		}

	 	if (Surface_GetHeightAndBrightness(legoGlobs.currLevel,nextX>>12,nextY>>12, &nextZ, &brightness))
		{
			Container_SpriteSetSpriteBrightness(minifigure->refCont,(brightness>>2)+80);
			nextZ<<=12;
		}
		else
			nextZ=object->zSurface;

#ifdef 0
/*-----------------------------------------------------------------------------------------------------------------*/
{
	char	string[64];

	sprintf(string, "hd=%d", (minifigure->zSurface-nextZ));
	Font_PrintF(legoGlobs.stdFont,8,24,string);
}
/*-----------------------------------------------------------------------------------------------------------------*/
#endif

//test removed for now
		//if ((minifigure->zSurface-nextZ)<MINIFIGURE_GRADIENT_LIMIT)
		{
			int		collisionType;
			lpCRAFT	craft;

			if (nextX<0)
				nextX=0;

			if (nextY<0)
				nextY=0;

			if (nextX>width)
				nextX=width;																  					

			if (nextY>height)
				nextY=height;


//			block=&blockValue(legoGlobs.currLevel,nextX>>(12+9),nextY>>(12+9));


			block=Surface_GetBlock(nextX>>12,nextY>>12);



/* test for water/lava */

			minifigure->refCont->renderFlags&=~RENDER_FLAGS_CLIP_BOTTOM;
			if (object->z>=object->zSurface)
			{
				if (block->flags & MAP3DBLOCK_UVWOBBLES)
				{
					minifigure->refCont->renderFlags |=RENDER_FLAGS_CLIP_BOTTOM;

					if (block->flags & MAP3DBLOCK_REDWOBBLES)
						Creature_DamagePlayer(object,MINIFIGURE_HEALTH_DELTA_IN_LAVA);
					else
						Creature_DamagePlayer(object,MINIFIGURE_HEALTH_DELTA_IN_WATER);
				}
			}


			craft=NULL;
			craftObject=Craft_GetCraftInRangeOfMinifigure(minifigure, nextX, nextY, nextZ, &collisionType);
 			if (craftObject)
			{
				player->craftObject=craftObject;
				player->craft=craftObject->objectData;
				craft=craftObject->objectData;
			}

			forceTurn=FALSE;

			if (collisionType!=COLLISION_RADIUS)
			{
				if (block->flags & LEGOBLOCK_FLAG_BLOCK_DUG)
				{
					object->x=nextX;
					object->y=nextY;
				}
				else
					object->speed=0;
			}
			else
			{
				int	forceDirection;

				object->speed=0;
				forceTurn=TRUE;
				if (Craft_GetDirectionNotInCollisionWithMinifigure(object, craftObject, 1024, 100, &forceDirection))
				{
					if (forceDirection)
						object->angleY+=MINIFIGURE_FORCETURN_DELTA;
					else
						object->angleY-=MINIFIGURE_FORCETURN_DELTA;
				}
				else	/* couldn't determine direction, shouldn't happen, but hey, default to left */
				{
						object->angleY+=MINIFIGURE_FORCETURN_DELTA;
				}
			}

	/* test for drilling */

			{
				int 					drillX,drillY;
				int					rockType=0;
				int					canDrill;
				lpLego_Block		drillBlock=NULL;

				static int rockGen=20;


				drillX=object->x;
				drillY=object->y;

				drillX-=Asm_MulFIX(10<<12,xd);
				drillY+=Asm_MulFIX(10<<12,yd);

				drillX>>=12;
				drillY>>=12;

				Craft_GetDigBlockAndSurface(&drillX,&drillY,&drillBlock);

#ifdef 0
/*--- dig block info ----------------------------------------------------------------------------------------------*/
{
	char	string[64],string2[64];

	if (drillBlock)
	{
		sprintf(string, "block %02d,%02d", drillX,drillY);

		if (drillBlock->flags & LEGOBLOCK_FLAG_BLOCK_DUG)
			strcat(string, ": dug");
		else
		{
			sprintf(string2, "d=%03d", drillBlock->damage);
			strcat(string, ": undug  ");
			strcat(string,string2);
		}
		Font_PrintF(legoGlobs.stdFont,8,64,string);

	}
}
/*-----------------------------------------------------------------------------------------------------------------*/
#endif
				if (drillBlock)
				{
					if (!(drillBlock->flags & LEGOBLOCK_FLAG_BLOCK_DUG))
						rockType=drillBlock->surfaceType;
				}
				else
					rockType=Lego_SurfaceType_Immovable+3;			/* edge walls undrillable */


				//if ((drillBlock->flags & LEGOBLOCK_FLAG_BLOCK_DUG))

				if (PAD_EVENT(control,CONTROL_DIG))
				{
					CLEAR_EVENT_IMMEDIATE(control,CONTROL_DIG);

					minifigure->drillSpeed+=MINIFIGURE_MAX_DRILL_DELTA;
					if (minifigure->drillSpeed>MINIFIGURE_MAX_DRILL_SPEED)
						minifigure->drillSpeed=MINIFIGURE_MAX_DRILL_SPEED;
					

					//if (canDrill)
					{

						if (!(drillBlock->flags & LEGOBLOCK_FLAG_BLOCK_DUG))
						{
							if (drillBlock->surfaceType>minifigure->maxRockType)
								rockType=Lego_SurfaceType_Immovable+3;						/* walls are too hard for this minifigure */
							else
							{
								drillBlock->damage-=(minifigure->drillSpeed>>5);

							/* generate drill stones */

								if ((legoGlobs.frameCount & 7)==4)
								//if (drillBlock->damage & 63)>rockGen)
								{
									int 	yAngle=object->angleY+2048-512;

									yAngle+=rand()&1023;



									Boulder_AddBoulder(object->x>>12,object->y>>12,(object->zSurface>>12)-128,
										(rand()&255)+128, yAngle, (((rand()&127)+128)<<9), -(((rand()&15)+50)<<12), 100, 0);

									rockGen=(rand()&31)+16;

									Boulder_AddSmoke((object->x>>12)+((rand()&63)-32), (object->y>>12)+((rand()&63)-32), (object->zSurface>>12)-128,
										 ((256+(rand()&511))<<1), 0, -(4+(rand()&3))<<12, ((128+(rand()&63))<<12), ToFIXED(-3.0), 255, 255, 255);

								}

							/* check for block destruction */

								if (drillBlock->damage<=0)
								{
									int 	yAngle=object->angleY+2048-512;

									yAngle+=rand()&1023;
									Lego_DigBlock(legoGlobs.currLevel,drillX,drillY,FALSE);
									Sfx_PlayEffect(SFX_SAMPLE_ROCKFALL,ROCKFALL_FREQUENCY+(rand()&3),127);
									Boulder_CreateRockFall(drillX,drillY,yAngle);
									Camera_SetShakeTimer(25);
								}
							}
						}
					}
				}
				else
				{
					minifigure->drillSpeed-=MINIFIGURE_MAX_DRILL_DELTA;
					if (minifigure->drillSpeed<0)
						minifigure->drillSpeed=0;
				}

				if (rockType!=Lego_SurfaceType_floor)
					rockType+=2;

			/* handle sfx */

				if (minifigure->drillSfxVoice==-1)		/* not currently playing */
				{
					if (minifigure->drillSpeed>0) 
						minifigure->drillSfxVoice=Sfx_PlayEffect(SFX_SAMPLE_MF_DRILL,MINIFIGURE_DRILL_FREQUENCY,0);		/* start looping SFX */
				}
				else			/* adjust currently playing sound */
				{
					if (minifigure->drillSpeed==0)
					{
						Sfx_StopEffect(minifigure->drillSfxVoice);		/* voice is unused now, release it */
						minifigure->drillSfxVoice=-1;
					}
					else		/* modulate volume and pitch */
					{
						if (legoGlobs.pauseFlag)
						{
							SsUtSetVVol(minifigure->drillSfxVoice,0,0);
							return;
						}
						else
							SsUtSetVVol(minifigure->drillSfxVoice,minifigure->drillSpeed>>1,minifigure->drillSpeed>>1);

					/* pitch will key off type, from fastest to slowest (0==thin air) */

						Sfx_ChangePitch(minifigure->drillSfxVoice,SFX_SAMPLE_MF_DRILL,MINIFIGURE_DRILL_FREQUENCY,(MINIFIGURE_DRILL_FREQUENCY-(rockType*3))<<7);

					}
				}
			}

			object->zSurface=nextZ;


			if (collisionType!=-1 && craft->controlledBy==-1 && (craft->flags & CF_DRIVEABLE))
			{
				if (player->reticuleAlpha<128)
					player->reticuleAlpha+=8;
				Craft_DrawActivationReticule(craftObject,player);
			}
 			else
			{
				if (player->reticuleAlpha>0)
				{
					Craft_DrawActivationReticule(player->craftObject,player);
					player->reticuleAlpha-=8;
				}
			}
	

			if (PAD_EVENT(control,CONTROL_ACTIVATION_TOGGLE))
			{
				CLEAR_EVENT_RELEASE(control,CONTROL_ACTIVATION_TOGGLE);
				if (collisionType!=-1)
				{
					if (craft->controlledBy==-1 && (craft->flags & CF_DRIVEABLE))
					{
						player->flags&=~PLAYER_FLAG_MINIFIGURE_ACTIVE;
						craft->controlledBy=player->id;
						craft->flightFlag=TRUE;
						Container_Hide(minifigure->refCont, TRUE);
						Container_Hide(minifigure->shadowCont, TRUE);

					/* stop drilling SFX */

						if (minifigure->drillSfxVoice!=-1)
						{
							Sfx_StopEffect(minifigure->drillSfxVoice);
							minifigure->drillSpeed=0;
							minifigure->drillSfxVoice=-1;
						}
					}
					else
					{
#ifndef __CDVERSION
						/* PLAY SFX FOR FAILURE TO ENTER CRAFT */
		
						//CONSOLE_STRING("Can't enter craft, already in use.");
#endif					
					}

				}
			}			
		}
	}

#ifndef __CDVERSION
//#define	COLLISION_TEST
#endif

#ifdef COLLISION_TEST

	if (PAD_EVENT(control,CONTROL_SYS_SQUARE))
	{
		object->x-=(16<<12);
	 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_SQUARE);
	}

	if (PAD_EVENT(control,CONTROL_SYS_TRIANGLE))
	{
		object->y-=(16<<12);
	 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_TRIANGLE);
	}

	if (PAD_EVENT(control,CONTROL_SYS_CIRCLE))
	{
		object->x+=(16<<12);
	 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_CIRCLE);
	}

	if (PAD_EVENT(control,CONTROL_SYS_CROSS))
	{
		object->y+=(16<<12);
		CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_CROSS);
	}

#else

/* jump test */

	if (PAD_EVENT(control,CONTROL_SQUARE_NO_ACTION))
	{
		Lego_ResetGameClock();
		CLEAR_EVENT_RELEASE(control,CONTROL_SQUARE_NO_ACTION);
		if (object->z==object->zSurface)
			object->zSpeed=ToFIXED(-40);
	}

#endif


	object->zSpeed+=ToFIXED(2.6);
	object->z+=object->zSpeed;

	if (object->z>=object->zSurface)
	{
		object->z=object->zSurface;
		object->zSpeed=0;	
	}

	Container_SetWorldPosition(minifigure->refCont,object->x>>12,object->y>>12,object->z>>12);


/* bring to rest if inside decel delta */

	if (object->speed<0)
	{
		if (object->speed>MINIFIGURE_DECEL_DELTA)
			object->speed=0;
	}
	else
	{
		if (object->speed<MINIFIGURE_DECEL_DELTA)
			object->speed=0;
	}


#ifndef __CDVERSION
#ifdef SKIP_IT
	{
		VECTOR3D	v1;

		v1.x=object->x>>12;
		v1.y=object->y>>12;
		v1.z=object->zSurface>>12;
		draw_world_cross(&v1,255,255,255);
	}
#endif
#endif


#ifdef SKIP_IT
/*-----------------------------------------------------------------------------------------------------------------*/
{
	char	string[64];

	sprintf(string, "mf_ay=%d", object->angleY);
	Font_PrintF(legoGlobs.stdFont,8,92,string);
}
/*-----------------------------------------------------------------------------------------------------------------*/
#endif

	Container_SetRotation(minifigure->refCont,0,object->angleY,0);
}


/*
	render callback for player shadows
*/
void Player_RenderShadow(lpContainer callbackCont)
{
	lpOBJECT	object=callbackCont->owner;

	if (callbackCont->Hidden==FALSE)
		Object_DisplayShadow(object,2,0x400-((object->zSurface-object->z)>>12));
}


/*
	general shadow display for objects, simplified from craft
	shadow, since we don't deform for corner points, as these objects
	won't travel over floor/wall junctions
*/
BOOL	Object_DisplayShadow(lpOBJECT object, int frame, int scale)
{
	SPRITE_SET 				*set=objectGlobs.craftShadowSet->seq_list[0];

	POLY_FT4					*display_quad;
	Uint32				 	*ot=(Uint32*)gfxGlobs.Wot[gfxGlobs.bufID].org;

	GsCOORDINATE2			coord;
	MATRIX					mat;
	short						coords[3];
	long						depth=14,flag;
	SVECTOR					vector;
	int						z;
	VECTOR3D					pos,rot;
	SPR_FRAME				*seq_frame;
	int						width;
	int						dx,dy;	
	REAL						stheta,ctheta;
	int						sizex,sizey;

  GsLINE   				l;
	int						tx[4],ty[4],n;
	REAL						xstheta,xctheta,ystheta,yctheta;

	int						halfScreenW=200;
	int						halfScreenH=136;


	if (!(display_quad=Image_GetFreeQuad()))
		return	FALSE;									/* out of quads, whoops. */

	seq_frame=set->frames;
	seq_frame+=frame;

	GsInitCoordinate2(WORLD, &coord);
	GsGetLs(&coord, &mat);
	GsSetLsMatrix(&mat);

	rot.y=object->angleY;
	pos.x=object->x>>12;
	pos.y=object->y>>12;
	pos.z=object->zSurface>>12;

	sizex=FromFIXED(Asm_MulFIX((seq_frame->w<<14),scale));
	sizey=FromFIXED(Asm_MulFIX((seq_frame->h<<14),scale));


	stheta=csin(4095-rot.y);
	ctheta=ccos(4095-rot.y);
	dx=FromFIXED((sizex*ctheta)-(sizey*stheta));
	dy=FromFIXED((sizex*stheta)+(sizey*ctheta));
	vector.vx=-pos.x+dx;
	vector.vy=pos.z;
	vector.vz=pos.y+dy;
	z=RotTransPers(&vector,(long*)&coords[0],&depth,&flag);


	display_quad->x1=coords[0];
	display_quad->y1=coords[1];

	vector.vx=-pos.x-dx;
	vector.vy=pos.z;
	vector.vz=pos.y-dy;
	z=RotTransPers(&vector,(long*)&coords[0],&depth,&flag);
	display_quad->x2=coords[0];
	display_quad->y2=coords[1];

	dx=FromFIXED((sizex*ctheta)-(-sizey*stheta));
	dy=FromFIXED((sizex*stheta)+(-sizey*ctheta));
	vector.vx=-pos.x+dx;
	vector.vy=pos.z;
	vector.vz=pos.y+dy;
	z=RotTransPers(&vector,(long*)&coords[0],&depth,&flag);
	display_quad->x3=coords[0];
	display_quad->y3=coords[1];

	vector.vx=-pos.x-dx;
	vector.vy=pos.z;
	vector.vz=pos.y-dy;
	z=RotTransPers(&vector,(long*)&coords[0],&depth,&flag);
	display_quad->x0=coords[0];
	display_quad->y0=coords[1];

	width=seq_frame->w;
	if (width<0)
		width=-width;
	width-=1;

	display_quad->tpage=set->tpage;
	display_quad->tpage|=0x40;		/* set to colour subtraction */
	display_quad->clut=getClut(set->cx,set->cy);
	display_quad->u0=seq_frame->u;
	display_quad->v0=seq_frame->v;
	display_quad->u1=seq_frame->u+width;
	display_quad->v1=seq_frame->v;
	display_quad->u2=seq_frame->u;
	display_quad->v2=seq_frame->v+seq_frame->h-1;
	display_quad->u3=seq_frame->u+width;
	display_quad->v3=seq_frame->v+seq_frame->h-1;
		
	display_quad->r0=display_quad->g0=display_quad->b0=32;
	setSemiTrans(display_quad,1);
	AddPrim(ot+(gfxGlobs.otSize-100),display_quad);

	return	TRUE;

}
