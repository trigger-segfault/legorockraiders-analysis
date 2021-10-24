//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// scorpion File For <LEGO [Rock Raiders]>
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ


#include	"globals.h"





/* ------------------------------------------------------
		initialise a scorpion
   ------------------------------------------------------ */
void		Creature_InitialiseScorpion(lpOBJECT scorpionObject)
{
	scorpionObject->cont->clipSize=16;
	Container_SetRGB(scorpionObject->cont,90,80,80);
}



/* ------------------------------------------------------
		handle a scorpion
   ------------------------------------------------------ */
void		Creature_ServiceScorpion(lpOBJECT scorpionObject, int time)
{
	lpCREATURE 			scorpion=scorpionObject->objectData;

	int					deltaX,deltaY,angle;
	int					range,angleDelta;
	int					xd,yd,nextX,nextY,nextZ;
	unsigned char		brightness;
	lpLego_Block		block;


	if (scorpion->refCont->renderFlags & RENDER_FLAGS_CLIPPED)
	{
		scorpion->clipTime++;
		if (scorpion->flags & CREATURE_KILL_IF_CLIPPED)
		{
			if (scorpion->clipTime>SCORPION_CLIPPED_TIMEOUT)
			{
				Creature_KillCreature(scorpionObject);
				return;
			}
		}

		if (!(scorpion->flags & CREATURE_PROCESS_IF_CLIPPED))
		{
			return;
		}
	}
	else
		scorpion->clipTime=0;


	scorpion->target=Creature_GetMinifigureTarget(scorpionObject,SCORPION_TARGET_RANGE,&deltaX,&deltaY);
	if (scorpion->directionTime>0)
		scorpion->target=NULL;


	if (scorpion->target)
	{
		if (scorpion->directionTime==0)
		{
			/* re-acquire the targets direction */

			scorpionObject->targetAngleY=(ratan2(deltaY,deltaX)+1024);
			scorpion->directionTime=SCORPION_REACQUIRE_TARGET_TIME;

		/* put a random skew on it */
			scorpionObject->targetAngleY+=((rand()&511)-256);
			scorpionObject->targetAngleY&=4095;

		}
		scorpion->directionTime--;
	}
	else
	{
		if (scorpion->directionTime==0)
		{
			scorpionObject->targetAngleY+=((rand()&2047)-1024);
			scorpionObject->targetAngleY&=4095;
			scorpion->directionTime=SCORPION_WANDER_TIME;
		}
		scorpion->directionTime--;
	}


/* move current angleY to targetAngleY */

	angleDelta=scorpionObject->targetAngleY-scorpionObject->angleY;

	if (angleDelta<0)
	{
		if (angleDelta<-2048)
			angleDelta+=4096;
	}
	else
	{
		if (angleDelta>2048)
			angleDelta-=4096;
	}

	scorpionObject->angleY+=angleDelta>>3;
	scorpionObject->angleY&=4095;

/* move to target */

	range=(deltaX*deltaX)+(deltaY*deltaY);

	if (range>SCORPION_COLLISION_RANGE || scorpionObject->speed<0)
	{
		if (scorpionObject->speed<SCORPION_MAX_SPEED)
			scorpionObject->speed+=SCORPION_SPEED_DELTA;

		
		xd=rsin(scorpionObject->angleY);
		yd=rcos(scorpionObject->angleY);

		nextX=scorpionObject->x-Asm_MulFIX(scorpionObject->speed,xd);
		nextY=scorpionObject->y+Asm_MulFIX(scorpionObject->speed,yd);

	/* test here for collision with undug areas... */

		block=&blockValue(legoGlobs.currLevel,nextX>>(12+9),nextY>>(12+9));

		if ((block->flags & LEGOBLOCK_FLAG_BLOCK_DUG) && (!(block->flags & (MAP3DBLOCK_VERTEXWOBBLES|MAP3DBLOCK_UVWOBBLES))))
		{
			scorpionObject->x=nextX;
			scorpionObject->y=nextY;
			scorpion->lastDirChange=0;
		}
		else
		{
			if (scorpion->target==NULL)
			{
				if (scorpion->lastDirChange==0)
				{

				/* pick a direction to get us away from collision */
					if (rand()&1)
						scorpion->lastDirChange=SCORPION_TURN_DELTA;
					else
						scorpion->lastDirChange=-SCORPION_TURN_DELTA;

				}
				scorpionObject->targetAngleY+=scorpion->lastDirChange;
				scorpionObject->targetAngleY&=4095;
				scorpionObject->speed=0;
				scorpion->directionTime=SCORPION_WANDER_TIME;
			}
		}
	}
	else
	{
		scorpionObject->speed=SCORPION_BACKOFF_SPEED;
		scorpion->directionTime=SCORPION_BACKOFF_TIME;
		scorpionObject->targetAngleY+=((rand()&2047)-1024);
		scorpionObject->targetAngleY&=4095;
		Creature_DamagePlayer(scorpion->target,SCORPION_PLAYER_DAMAGE);
	}	


	if (Surface_GetHeightAndBrightness(legoGlobs.currLevel,scorpionObject->x>>12,scorpionObject->y>>12, &nextZ, &brightness))
	{
		Container_SpriteSetSpriteBrightness(scorpion->refCont,(brightness>>2)+80);
		nextZ<<=12;
	}
	else
		nextZ=scorpionObject->zSurface;

	scorpionObject->zSurface=nextZ;
	scorpionObject->z=scorpionObject->zSurface;



#ifdef SKIP_IT				/* show target angle */
	{
		VECTOR3D				v1,v2;

		v1.x=scorpionObject->x>>12;
		v1.y=scorpionObject->y>>12;
		v1.z=scorpionObject->zSurface>>12;

		{
			char	string[64];

			sprintf(string, "tay=%d, ay=%d", scorpionObject->targetAngleY,scorpionObject->angleY);
			Font_PrintF(legoGlobs.stdFont,8,100,string);
		}	


		v2.x=v1.x-((Asm_MulFIX(200<<12,rsin(scorpionObject->targetAngleY)))>>12);
		v2.y=v1.y+((Asm_MulFIX(200<<12,rcos(scorpionObject->targetAngleY)))>>12);
		v2.z=v1.z;

		draw_world_line(&v1,&v2,255,255,255);

	}	
#endif

	if (scorpionObject->speed==0)
		Container_UpdateAnimation(scorpion->refCont,angleDelta<<4);
	else
		Container_UpdateAnimation(scorpion->refCont,scorpionObject->speed>>3);

	Container_SetRotation(scorpion->refCont,0,scorpionObject->angleY,0);
	Container_SetWorldPosition(scorpion->refCont,scorpionObject->x>>12,scorpionObject->y>>12,scorpionObject->z>>12);
}

