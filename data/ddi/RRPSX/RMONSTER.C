//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// rockmonster File For <LEGO [Rock Raiders]>
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

#include	"globals.h"


/* ------------------------------------------------------
		initialise a rockmonster
   ------------------------------------------------------ */
void	Creature_InitialiseRockMonster(lpOBJECT rockMonsterObject)
{
	Container_StartAnimation(rockMonsterObject->cont,0,HMD_LOOP,0);
 	rockMonsterObject->cont->clipSize=32;
}


#define		ROCKMONSTER_BACKOFF_TIME				(50)
#define		ROCKMONSTER_JUMP_DELTA					(ToFIXED(-40.0))
#define		CF_JUMP										(1)

/* ------------------------------------------------------
		handle a rockmonster
   ------------------------------------------------------ */
void	Creature_ServiceRockMonster(lpOBJECT rockMonsterObject, int time)
{
	lpCREATURE			rockMonster=rockMonsterObject->objectData;
	int					deltaX,deltaY,angle;
	int					range,angleDelta;
	int					xd,yd,nextX,nextY,nextZ;
	unsigned char		brightness;
	lpLego_Block		block;

	rockMonsterObject->flags&=~OF_SLEEPING;

	if (rockMonster->refCont->renderFlags & RENDER_FLAGS_CLIPPED)
	{
		rockMonster->clipTime++;
		if (rockMonster->flags & CREATURE_KILL_IF_CLIPPED)
		{
			if (rockMonster->clipTime>ROCKMONSTER_CLIPPED_TIMEOUT)
			{
				Creature_KillCreature(rockMonsterObject);
				return;
			}
		}

		if (!(rockMonster->flags & CREATURE_PROCESS_IF_CLIPPED))
		{
			rockMonsterObject->flags|=OF_SLEEPING;
			return;
		}
	}
	else
		rockMonster->clipTime=0;


	rockMonster->target=Creature_GetMinifigureTarget(rockMonsterObject,ROCKMONSTER_TARGET_RANGE,&deltaX,&deltaY);
	if (rockMonster->directionTime>0)
		rockMonster->target=NULL;

if (!(rockMonster->flags & CF_JUMP))
{
	if (rockMonster->target)
	{
		if (rockMonster->directionTime==0)
		{
			/* re-acquire the targets direction */

			rockMonsterObject->targetAngleY=(ratan2(deltaY,deltaX)+1024);
			rockMonster->directionTime=ROCKMONSTER_REACQUIRE_TARGET_TIME;

		/* put a random skew on it */
			rockMonsterObject->targetAngleY+=((rand()&127)-64);
			rockMonsterObject->targetAngleY&=4095;

		}
		rockMonster->directionTime--;
	}
	else
	{
		if (rockMonster->directionTime==0)
		{
			rockMonsterObject->targetAngleY+=((rand()&1023)-512);
			rockMonsterObject->targetAngleY&=4095;
			rockMonster->directionTime=ROCKMONSTER_WANDER_TIME;
		}
		rockMonster->directionTime--;
	}
}

/* move current angleY to targetAngleY */

	angleDelta=rockMonsterObject->targetAngleY-rockMonsterObject->angleY;

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

	rockMonsterObject->angleY+=angleDelta>>4;
	rockMonsterObject->angleY&=4095;

/* move to target */

	range=(deltaX*deltaX)+(deltaY*deltaY);

	if (range>ROCKMONSTER_COLLISION_RANGE || rockMonsterObject->speed<0)
	{
		if (rockMonsterObject->speed<ROCKMONSTER_MAX_SPEED)
			rockMonsterObject->speed+=ROCKMONSTER_SPEED_DELTA;

		
		xd=rsin(rockMonsterObject->angleY);
		yd=rcos(rockMonsterObject->angleY);

		nextX=rockMonsterObject->x-Asm_MulFIX(rockMonsterObject->speed,xd);
		nextY=rockMonsterObject->y+Asm_MzulFIX(rockMonsterObject->speed,yd);

	/* test here for collision with undug areas... */

		block=&blockValue(legoGlobs.currLevel,nextX>>(12+9),nextY>>(12+9));

		if ((block->flags & LEGOBLOCK_FLAG_BLOCK_DUG) && (!(block->flags & (MAP3DBLOCK_VERTEXWOBBLES|MAP3DBLOCK_UVWOBBLES))))
		{
			rockMonsterObject->x=nextX;
			rockMonsterObject->y=nextY;
			rockMonster->lastDirChange=0;
		}
		else
		{
			if (rockMonster->target==NULL)
			{
				if (rockMonster->lastDirChange==0)
				{

				/* pick a direction to get us away from collision */
					if (rand()&1)
						rockMonster->lastDirChange=ROCKMONSTER_TURN_DELTA;
					else
						rockMonster->lastDirChange=-ROCKMONSTER_TURN_DELTA;

				}
				rockMonsterObject->targetAngleY+=rockMonster->lastDirChange;
				rockMonsterObject->targetAngleY&=4095;
				rockMonsterObject->speed=0;
				rockMonster->directionTime=ROCKMONSTER_WANDER_TIME;
			}
		}
	}
	else
	{
		rockMonsterObject->speed=0;
		//rockMonsterObject->targetAngleY+=((rand()&2047)-1024);
		//rockMonsterObject->targetAngleY&=4095;
		//Creature_DamagePlayer(rockMonster->target,ROCKMONSTER_PLAYER_DAMAGE);

		if (!(rockMonster->flags & CF_JUMP) && rockMonster->directionTime==0)
		{
			rockMonster->flags|=CF_JUMP;
			rockMonsterObject->zSpeed=ROCKMONSTER_JUMP_DELTA;
			rockMonster->directionTime=ROCKMONSTER_BACKOFF_TIME;


		}
		
	}	



	if (Surface_GetHeightAndBrightness(legoGlobs.currLevel,rockMonsterObject->x>>12,rockMonsterObject->y>>12, &nextZ, &brightness))
	{
		Container_SpriteSetSpriteBrightness(rockMonster->refCont,(brightness>>2)+80);
		nextZ<<=12;
	}
	else
		nextZ=rockMonsterObject->zSurface;

	rockMonsterObject->zSurface=nextZ;

	rockMonsterObject->zSpeed+=ToFIXED(3.6);
	rockMonsterObject->z+=rockMonsterObject->zSpeed;

	if (rockMonsterObject->z>=rockMonsterObject->zSurface)
	{
		rockMonsterObject->z=rockMonsterObject->zSurface;
		rockMonsterObject->zSpeed=0;	

		if (rockMonster->flags & CF_JUMP)
		{
			rockMonster->flags &=~CF_JUMP;
			Camera_SetShakeTimer(20);

			xd=rsin(rockMonsterObject->angleY+1024);
			yd=rcos(rockMonsterObject->angleY+1024);

			nextX=rockMonsterObject->x-Asm_MulFIX(70<<12,xd);
			nextY=rockMonsterObject->y+Asm_MulFIX(70<<12,yd);

			Boulder_AddSmoke(nextX>>12,nextY>>12 ,rockMonsterObject->z>>12 ,
				((3072+(rand()&1023))<<1), 0, -3<<12, ((240+(rand()&15))<<12), ToFIXED(-2.8), 255, 200, 100);

			xd=rsin(rockMonsterObject->angleY-1024);
			yd=rcos(rockMonsterObject->angleY-1024);

			nextX=rockMonsterObject->x-Asm_MulFIX(70<<12,xd);
			nextY=rockMonsterObject->y+Asm_MulFIX(70<<12,yd);

			Boulder_AddSmoke(nextX>>12,nextY>>12 ,rockMonsterObject->z>>12 ,
				((3072+(rand()&1023))<<1), 0, -3<<12, ((240+(rand()&15))<<12), ToFIXED(-2.8), 255, 200, 100);

		}
	}

	Container_SetAnimSpeed(rockMonster->refCont,rockMonsterObject->speed>>11);
	Container_SetRotation(rockMonster->refCont,0,rockMonsterObject->angleY,0);
	Container_SetWorldPosition(rockMonster->refCont,rockMonsterObject->x>>12,rockMonsterObject->y>>12,rockMonsterObject->z>>12);
}


