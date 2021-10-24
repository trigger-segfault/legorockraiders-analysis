
//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// spider File For <LEGO [Rock Raiders]>
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

#include	"globals.h"


/* ------------------------------------------------------
		initialse a snake
   ------------------------------------------------------ */
void		Creature_InitialiseSnake(lpOBJECT snakeObject)
{
//	snake->cont->clipSize=16;
}




/* ------------------------------------------------------
		handle a snake
   ------------------------------------------------------ */
void		Creature_ServiceSnake(lpOBJECT snakeObject, int time)
{
#ifdef 0
	lpCREATURE_GLOBS	cg=&creatureGlobs;
	int					deltaX,deltaY,angle;
	int					range,angleDelta;
	int					xd,yd,nextX,nextY,nextZ;
	unsigned char		brightness;
	lpLego_Block		block;



	if (snake->cont->renderFlags & RENDER_FLAGS_CLIPPED)
	{
		snake->clipTime++;
		if (snake->flags & CREATURE_KILL_IF_CLIPPED)
		{
			if (snake->clipTime>SNAKE_CLIPPED_TIMEOUT)
			{
				Creature_KillCreature(snake);
				return;
			}
		}

		if (!(snake->flags & CREATURE_PROCESS_IF_CLIPPED))
		{
			return;
		}
	}
	else
		snake->clipTime=0;


	snake->target=Creature_GetMinifigureTarget(snake,SNAKE_TARGET_RANGE,&deltaX,&deltaY);
	if (snake->directionTime>0)
		snake->target=NULL;

	if (snake->target)
	{
		if (snake->directionTime==0)
		{
			/* re-acquire the targets direction */

			snake->targetAngleY=(ratan2(deltaY,deltaX)+1024);
			snake->directionTime=SNAKE_REACQUIRE_TARGET_TIME;

		/* put a random skew on it */
			snake->targetAngleY+=((rand()&511)-256);
			snake->targetAngleY&=4095;

		}
		snake->directionTime--;
	}
	else
	{
		if (snake->directionTime==0)
		{
			snake->targetAngleY+=((rand()&2047)-1024);
			snake->targetAngleY&=4095;
			snake->directionTime=SNAKE_WANDER_TIME;
		}
		snake->directionTime--;
	}


/* move current angleY to targetAngleY */

	angleDelta=snake->targetAngleY-snake->angleY;

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

	snake->angleY+=angleDelta>>3;
	snake->angleY&=4095;

/* move to target */

	range=(deltaX*deltaX)+(deltaY*deltaY);

	if (range>SNAKE_COLLISION_RANGE || snake->speed<0)
	{
		if (snake->speed<SNAKE_MAX_SPEED)
			snake->speed+=SNAKE_SPEED_DELTA;

		
		xd=rsin(snake->angleY);
		yd=rcos(snake->angleY);

		nextX=snake->x-Asm_MulFIX(snake->speed,xd);
		nextY=snake->y+Asm_MulFIX(snake->speed,yd);

	/* test here for collision with undug areas... */

		block=&blockValue(legoGlobs.currLevel,nextX>>(12+9),nextY>>(12+9));

		if ((block->flags & LEGOBLOCK_FLAG_BLOCK_DUG) && (!(block->flags & (MAP3DBLOCK_VERTEXWOBBLES|MAP3DBLOCK_UVWOBBLES))))
		{
			snake->x=nextX;
			snake->y=nextY;
			snake->lastDirChange=0;
		}
		else
		{
			if (snake->target==NULL)
			{
				if (snake->lastDirChange==0)
				{

				/* pick a direction to get us away from collision */
					if (rand()&1)
						snake->lastDirChange=SNAKE_TURN_DELTA;
					else
						snake->lastDirChange=-SNAKE_TURN_DELTA;

				}
				snake->targetAngleY+=snake->lastDirChange;
				snake->targetAngleY&=4095;
				snake->speed=0;
				snake->directionTime=SNAKE_WANDER_TIME;
			}
		}
	}
	else
	{
		snake->speed=SNAKE_BACKOFF_SPEED;
		snake->directionTime=SNAKE_BACKOFF_TIME;
		snake->targetAngleY+=((rand()&2047)-1024);
		snake->targetAngleY&=4095;
		Creature_DamagePlayer(snake->target,SNAKE_PLAYER_DAMAGE);
	}	


	if (Surface_GetHeightAndBrightness(legoGlobs.currLevel,snake->x>>12,snake->y>>12, &nextZ, &brightness))
	{
		Container_SpriteSetSpriteBrightness(snake->cont,(brightness>>2)+80);
		nextZ<<=12;
	}
	else
		nextZ=snake->zSurface;

	snake->zSurface=nextZ;
	snake->z=snake->zSurface;

	if (snake->speed==0)
		Container_UpdateAnimation(snake->cont,angleDelta<<4);
	else
		Container_UpdateAnimation(snake->cont,snake->speed>>3);

	Container_SetRotation(snake->cont,0,snake->angleY,0);
	Container_SetWorldPosition(snake->cont,snake->x>>12,snake->y>>12,snake->z>>12);
#endif
}

