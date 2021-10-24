//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// spider File For <LEGO [Rock Raiders]>
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

#include	"globals.h"


/* ------------------------------------------------------
		initialse a spider
   ------------------------------------------------------ */
void		Creature_InitialiseSpider(lpOBJECT spiderObject)
{
	//spider->cont->clipSize=16;
}


/* ------------------------------------------------------
		handle a spider
   ------------------------------------------------------ */
void		Creature_ServiceSpider(lpOBJECT spiderObject, int time)
{
#ifdef 0
	lpCREATURE_GLOBS	cg=&creatureGlobs;
	int					deltaX,deltaY,angle;
	int					range,angleDelta;
	int					xd,yd,nextX,nextY,nextZ;
	unsigned char		brightness;
	lpLego_Block		block;



	if (spider->cont->renderFlags & RENDER_FLAGS_CLIPPED)
	{
		spider->clipTime++;
		if (spider->flags & CREATURE_KILL_IF_CLIPPED)
		{
			if (spider->clipTime>SPIDER_CLIPPED_TIMEOUT)
			{
				Creature_KillCreature(spider);
				return;
			}
		}

		if (!(spider->flags & CREATURE_PROCESS_IF_CLIPPED))
		{
			return;
		}
	}
	else
		spider->clipTime=0;


	spider->target=Creature_GetMinifigureTarget(spider,SPIDER_TARGET_RANGE,&deltaX,&deltaY);
	if (spider->directionTime>0)
		spider->target=NULL;

	if (spider->target)
	{
		if (spider->directionTime==0)
		{
			/* re-acquire the targets direction */

			spider->targetAngleY=(ratan2(deltaY,deltaX)+1024);
			spider->directionTime=SPIDER_REACQUIRE_TARGET_TIME;

		/* put a random skew on it */
			spider->targetAngleY+=((rand()&511)-256);
			spider->targetAngleY&=4095;

		}
		spider->directionTime--;
	}
	else
	{
		if (spider->directionTime==0)
		{
			spider->targetAngleY+=((rand()&2047)-1024);
			spider->targetAngleY&=4095;
			spider->directionTime=SPIDER_WANDER_TIME;
		}
		spider->directionTime--;
	}


/* move current angleY to targetAngleY */

	angleDelta=spider->targetAngleY-spider->angleY;

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

	spider->angleY+=angleDelta>>3;
	spider->angleY&=4095;

/* move to target */

	range=(deltaX*deltaX)+(deltaY*deltaY);

	if (range>SPIDER_COLLISION_RANGE || spider->speed<0)
	{
		if (spider->speed<SPIDER_MAX_SPEED)
			spider->speed+=SPIDER_SPEED_DELTA;

		
		xd=rsin(spider->angleY);
		yd=rcos(spider->angleY);

		nextX=spider->x-Asm_MulFIX(spider->speed,xd);
		nextY=spider->y+Asm_MulFIX(spider->speed,yd);

	/* test here for collision with undug areas... */

		block=&blockValue(legoGlobs.currLevel,nextX>>(12+9),nextY>>(12+9));

		if ((block->flags & LEGOBLOCK_FLAG_BLOCK_DUG) && (!(block->flags & (MAP3DBLOCK_VERTEXWOBBLES|MAP3DBLOCK_UVWOBBLES))))
		{
			spider->x=nextX;
			spider->y=nextY;
			spider->lastDirChange=0;
		}
		else
		{
			if (spider->target==NULL)
			{
				if (spider->lastDirChange==0)
				{

				/* pick a direction to get us away from collision */
					if (rand()&1)
						spider->lastDirChange=SPIDER_TURN_DELTA;
					else
						spider->lastDirChange=-SPIDER_TURN_DELTA;

				}
				spider->targetAngleY+=spider->lastDirChange;
				spider->targetAngleY&=4095;
				spider->speed=0;
				spider->directionTime=SPIDER_WANDER_TIME;
			}
		}
	}
	else
	{
		spider->speed=SPIDER_BACKOFF_SPEED;
		spider->directionTime=SPIDER_BACKOFF_TIME;
		spider->targetAngleY+=((rand()&2047)-1024);
		spider->targetAngleY&=4095;
		Creature_DamagePlayer(spider->target,SPIDER_PLAYER_DAMAGE);
	}	


	if (Surface_GetHeightAndBrightness(legoGlobs.currLevel,spider->x>>12,spider->y>>12, &nextZ, &brightness))
	{
		Container_SpriteSetSpriteBrightness(spider->cont,(brightness>>2)+80);
		nextZ<<=12;
	}
	else
		nextZ=spider->zSurface;

	spider->zSurface=nextZ;
	spider->z=spider->zSurface;

	if (spider->speed==0)
		Container_UpdateAnimation(spider->cont,angleDelta<<4);
	else
		Container_UpdateAnimation(spider->cont,spider->speed>>3);

	Container_SetRotation(spider->cont,0,spider->angleY,0);
	Container_SetWorldPosition(spider->cont,spider->x>>12,spider->y>>12,spider->z>>12);
#endif
}


