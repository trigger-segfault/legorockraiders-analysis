//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// rockwhale File For <LEGO [Rock Raiders]>
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ


#include	"globals.h"


/* ------------------------------------------------------
		initialise a rockwhale
   ------------------------------------------------------ */
void		Creature_InitialiseRockWhale(lpOBJECT rockWhaleObject)
{
	int	x,y,z;


/*
	we jimmy the coordinates to ensure the rockwhale sits in the centre
	of a block, since he must do that to work properly
*/

	x=rockWhaleObject->x>>(12+9);
	y=rockWhaleObject->y>>(12+9);
	x<<=9;
	y<<=9;
	x+=256;
	y+=256;

/* now we re-calculate the z for the new position */

	if (!Surface_GetHeight(legoGlobs.currLevel,x,y, &z))
		z=0;

	rockWhaleObject->x=x<<12;
	rockWhaleObject->y=y<<12;
	rockWhaleObject->z=rockWhaleObject->zSurface=z<<12;
		
	Container_StartAnimation(rockWhaleObject->cont,0,HMD_LOOP,32);
 	rockWhaleObject->cont->clipSize=32;
}



enum
{
	RW_ACTIVITY_NONE,
	RW_TURN_LEFT,
	RW_TURN_RIGHT,
	RW_MOVE,
};

int		moveSteps;
int		activity;
int		test=0;

#define		ROCK_WHALE_TURN_DELTA			(16)
#define		ROCK_WHALE_SIT_TIMER				(30)
#define		ROCK_WHALE_MOVE_STEPS			(128)
#define		ROCK_WHALE_MOVE_DELTA			((512/ROCK_WHALE_MOVE_STEPS)<<12)


BOOL		Creature_RockWhaleTurnLeft(lpOBJECT rockWhaleObject)
{
	lpCREATURE			rockWhale=rockWhaleObject->objectData;

	if (activity==RW_ACTIVITY_NONE)
	{
		rockWhaleObject->targetAngleY-=1024;
		rockWhaleObject->targetAngleY&=4095;
		activity=RW_TURN_LEFT;
		return	TRUE;
	}
	return	FALSE;
}


BOOL		Creature_RockWhaleTurnRight(lpOBJECT rockWhaleObject)
{
	lpCREATURE			rockWhale=rockWhaleObject->objectData;

	if (activity==RW_ACTIVITY_NONE)
	{
		rockWhaleObject->targetAngleY+=1024;
		rockWhaleObject->targetAngleY&=4095;
		activity=RW_TURN_RIGHT;
		return	TRUE;
	}
	return	FALSE;
}

BOOL		Creature_RockWhaleStartMoving(lpOBJECT rockWhaleObject)
{
	lpCREATURE			rockWhale=rockWhaleObject->objectData;

	if (activity==RW_ACTIVITY_NONE)
	{
		moveSteps=ROCK_WHALE_MOVE_STEPS;
		activity=RW_MOVE;
		return	TRUE;
	}
	return	FALSE;
}


/* ------------------------------------------------------
		handle a rockwhale
   ------------------------------------------------------ */
void		Creature_ServiceRockWhale(lpOBJECT rockWhaleObject, int time)
{
	lpCREATURE			rockWhale=rockWhaleObject->objectData;
	int					xd,yd,delta,z;

	if (test==1)
	{
		Creature_RockWhaleTurnLeft(rockWhaleObject);
		test=0;
	}

	if (test==2)
	{
		Creature_RockWhaleTurnRight(rockWhaleObject);
		test=0;
	}

	if (test==3)
	{
		Creature_RockWhaleStartMoving(rockWhaleObject);
		test=0;
	}

	if (rockWhaleObject->angleY!=rockWhaleObject->targetAngleY)
	{
		if (activity==RW_TURN_LEFT)
			rockWhaleObject->angleY-=ROCK_WHALE_TURN_DELTA;
		else
			rockWhaleObject->angleY+=ROCK_WHALE_TURN_DELTA;
		rockWhaleObject->angleY&=4095;

		delta=rockWhaleObject->angleY-rockWhaleObject->targetAngleY;
		if (delta<0)
		{
			delta=-delta;
			if (delta>2048)
				delta-=4096;
			if (delta<0)
				delta=-delta;
		}

		if (delta<ROCK_WHALE_TURN_DELTA)
		{
			rockWhaleObject->angleY=rockWhaleObject->targetAngleY;
			activity=RW_ACTIVITY_NONE;
		}
	}
	else
	{
		if (moveSteps>0)
		{
			moveSteps--;
			xd=rsin(rockWhaleObject->angleY);
			yd=rcos(rockWhaleObject->angleY);
			rockWhaleObject->x-=Asm_MulFIX(ROCK_WHALE_MOVE_DELTA,xd);
			rockWhaleObject->y+=Asm_MulFIX(ROCK_WHALE_MOVE_DELTA,yd);
	
			if (!Surface_GetHeight(legoGlobs.currLevel,rockWhaleObject->x>>12,rockWhaleObject->y>>12, &z))
				z=0;
			rockWhaleObject->z=z<<12;
			if (moveSteps==0)
				activity=RW_ACTIVITY_NONE;
		}
	}

	Container_SetRotation(rockWhale->refCont,0,rockWhaleObject->angleY,0);
	Container_SetWorldPosition(rockWhale->refCont,rockWhaleObject->x>>12,rockWhaleObject->y>>12,rockWhaleObject->z>>12);
	if (activity==RW_ACTIVITY_NONE)
		Container_SetAnimSpeed(rockWhale->refCont,0);
	else
		Container_SetAnimSpeed(rockWhale->refCont,32);
		
	
}




