//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// creature File For <LEGO [Rock Raiders]>
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹


#include	"globals.h"


void	draw_world_line(LPVECTOR3D	pos,LPVECTOR3D	pos2, int red, int green, int blue);




int		creatureHealth[TR_MAX_CREATURE_TYPES]={250,500,50,80,100};


/*
	create the containers for the creatures.
	For efficiency we split the creature list into sections
	for rockmonsters and rockwhales (HMD models), and the sprite
	based creatures.

	

*/
BOOL	Creature_InitialiseLists(void)
{
	lpCREATURE			creature=objectGlobs.creatureList;
	int					n;


/* purge all the sprite lists... */

	for (n=0; n<TR_MAX_CREATURE_TYPES; n++)
		objectGlobs.creatureActivitySet[n]=NULL;

/* ...and then load the known sprite types */

	Image_LoadActivityFromConfig(&objectGlobs.creatureActivitySet[TR_CREATURE_SNAKE], "CREATURE\\SNAKE", legoGlobs.gameName);
	Image_LoadActivityFromConfig(&objectGlobs.creatureActivitySet[TR_CREATURE_SPIDER], "CREATURE\\SPIDER", legoGlobs.gameName);
	Image_LoadActivityFromConfig(&objectGlobs.creatureActivitySet[TR_CREATURE_SCORPION], "CREATURE\\SCORPION", legoGlobs.gameName);

/* load the rockmonster and rockwhale hmd models... */

	objectGlobs.rockmonsterRefCont=Container_LoadHMDModel(legoGlobs.rootCont, "CREATURE\\RMONSTER\\RM_WALKT");
	objectGlobs.rockwhaleRefCont=Container_LoadHMDModel(legoGlobs.rootCont, "CREATURE\\RWHALE\\RWHALE");


/* create the rockmonster containers */

	for (n=0; n<MAX_ROCKMONSTERS; n++)
	{
		creature->type=-1;
		creature->refCont=Container_Clone(objectGlobs.rockmonsterRefCont);
	
		Container_SetScale(creature->refCont,ONE>>1);
		Container_SetParent(legoGlobs.rootCont,creature->refCont);
		Container_Hide(creature->refCont, TRUE);
		creature++;
	}

/* now the rockwhales */

	for (; n<(MAX_ROCKMONSTERS+MAX_ROCKWHALES); n++)
	{
		creature->type=-1;
		creature->refCont=Container_Clone(objectGlobs.rockwhaleRefCont);
		Container_SetScale(creature->refCont,ToFIXED(0.49));
		Container_SetParent(legoGlobs.rootCont,creature->refCont);
		Container_Hide(creature->refCont, TRUE);
		creature++;
	}


/* and finally, the sprite creatures */

	for (; n<MAX_CREATURES; n++)
	{
		creature->type=-1;

/* create with a known sprite type */
				
		creature->refCont=Container_CreateFloorSprite(legoGlobs.rootCont,objectGlobs.creatureActivitySet[TR_CREATURE_SNAKE]);
		Container_SetScale(creature->refCont,ONE);
		Container_SetParent(legoGlobs.rootCont,creature->refCont);
		Container_Hide(creature->refCont, TRUE);
		creature++;
	}
	return	TRUE;
}


/*
	this defines list start an end points for creature insertion, as well as
	routine pointers for initialisation and execution.

MOVEME: to header
*/	
typedef struct creature_setup
{
	int	start;
	int	end;
	int	objectStart;
	int	objectEnd;
	void	(*initialiser)(struct obj_st *creatureObject);
	void	(*handler)(struct obj_st *creatureObject, int time);

} CREATURE_SETUP;

CREATURE_SETUP	creatureSetup[]=
{
	{
		0,MAX_ROCKMONSTERS,ROCKMONSTER_START,
		(ROCKMONSTER_START+MAX_ROCKMONSTERS),
		Creature_InitialiseRockMonster,Creature_ServiceRockMonster
	},	

	{
		MAX_ROCKMONSTERS,(MAX_ROCKMONSTERS+MAX_ROCKWHALES),
		ROCKWHALE_START,(ROCKWHALE_START+MAX_ROCKWHALES),
		Creature_InitialiseRockWhale,Creature_ServiceRockWhale
	},	

	{
		(MAX_ROCKMONSTERS+MAX_ROCKWHALES),MAX_CREATURES,
		SPRITECREATURE_START,(SPRITECREATURE_START+MAX_SPRITECREATURES),
		Creature_InitialiseSnake,Creature_ServiceSnake
	},	

	{
		(MAX_ROCKMONSTERS+MAX_ROCKWHALES),MAX_CREATURES,
		SPRITECREATURE_START,(SPRITECREATURE_START+MAX_SPRITECREATURES),
		Creature_InitialiseSpider,Creature_ServiceSpider
	},	

	{
		(MAX_ROCKMONSTERS+MAX_ROCKWHALES),MAX_CREATURES,
		SPRITECREATURE_START,(SPRITECREATURE_START+MAX_SPRITECREATURES),
		Creature_InitialiseScorpion,Creature_ServiceScorpion
	},	
};


/*
	create creature from entity trigger
*/
BOOL	Creature_CreateCreature(lpTRIGGER_ENTITY entity)
{
	lpCREATURE		newCreature;
	lpOBJECT			newCreatureObject;
	int				start,end,n;
	int				zSurface;


/* we find an object slot based on type */

	start=creatureSetup[entity->objectType].start;
	end=creatureSetup[entity->objectType].end;

	newCreature=&objectGlobs.creatureList[start];

	for (n=start; n<end; n++)
	{
		if (newCreature->type==-1)
		{
			/* now we must find a generic object */

			start=creatureSetup[entity->objectType].objectStart;
			end=creatureSetup[entity->objectType].objectEnd;

			newCreatureObject=&objectGlobs.objectList[start];
			for (n=start; n<end; n++)
			{
				if (newCreatureObject->cont==NULL)
				{
					newCreature->type=entity->objectType;
					newCreature->id=entity->objectId;
					newCreature->flags=entity->flags;
					newCreature->handler=creatureSetup[entity->objectType].handler;
					newCreatureObject->x=entity->x<<12;
					newCreatureObject->y=entity->y<<12;
					if (!Surface_GetHeight(legoGlobs.currLevel,entity->x,entity->y, &zSurface))
						zSurface=0;
					newCreatureObject->z=newCreatureObject->zSurface=zSurface<<12;
					newCreatureObject->angleY=entity->rotation;
					newCreatureObject->targetAngleY=entity->rotation;
					newCreatureObject->speed=0;
					newCreatureObject->zSpeed=0;
					newCreatureObject->cont=newCreature->refCont;
					newCreatureObject->type=entity->objectType;
					newCreatureObject->objectData=newCreature;

					newCreature->health=creatureHealth[entity->objectType];
					newCreature->activity=0;

					if (entity->objectType>=TR_CREATURE_SNAKE)	/* set activitySet for sprite type creatures */
					{
						Container_SetSpriteActivitySet(newCreature->refCont,objectGlobs.creatureActivitySet[entity->objectType]);
					}

					Container_SetPosition(newCreature->refCont,entity->x,entity->y,zSurface);
					Container_SetRotation(newCreature->refCont,0,newCreatureObject->angleY,0);
					Container_Hide(newCreature->refCont, FALSE);

					newCreature->target=NULL;
					newCreature->directionTime=n;

				/* call specific initialisation routine for creature */

					creatureSetup[entity->objectType].initialiser(newCreatureObject); 

					return	TRUE;
				}
				newCreatureObject++;
			}
		}
		newCreature++;
	}
	return	FALSE;		/* couldn't create an object */

}









/*
	handle creature list
*/
void	Creature_ServiceCreatureList(int time)
{
	lpCREATURE		creature;
	lpOBJECT			creatureObject=&objectGlobs.objectList[ROCKMONSTER_START];
	int				n;

#ifndef __CDVERSION
	for (n=0; n<TR_MAX_CREATURE_TYPES; n++)
		objectGlobs.activeCreatures[n]=0;			/* used for count of active creatures */
#endif

/* cache the active player pointers for craft and minifigures because they'll all be using them. */


	/* player 1 is always present of course */

	if (objectGlobs.playerList[PLAYER_ONE].flags & PLAYER_FLAG_MINIFIGURE_ACTIVE)
	{
		objectGlobs.playerMinifigureObject[PLAYER_ONE]=objectGlobs.playerList[PLAYER_ONE].minifigureObject;
		objectGlobs.playerCraftObject[PLAYER_ONE]=NULL;
	}
	else
	{
		objectGlobs.playerMinifigureObject[PLAYER_ONE]=NULL;
		objectGlobs.playerCraftObject[PLAYER_ONE]=objectGlobs.playerList[PLAYER_ONE].craftObject;
	}

	/* player 2 is optional */

	if (objectGlobs.numPlayers>1)
	{
		if (objectGlobs.playerList[PLAYER_TWO].flags & PLAYER_FLAG_MINIFIGURE_ACTIVE)
		{
			objectGlobs.playerMinifigureObject[PLAYER_TWO]=objectGlobs.playerList[PLAYER_TWO].minifigureObject;
			objectGlobs.playerCraftObject[PLAYER_TWO]=NULL;
		}
		else
		{
			objectGlobs.playerMinifigureObject[PLAYER_TWO]=NULL;
			objectGlobs.playerCraftObject[PLAYER_TWO]=objectGlobs.playerList[PLAYER_TWO].craftObject;
		}
	}
	else
	{
		objectGlobs.playerMinifigureObject[PLAYER_TWO]=NULL;
		objectGlobs.playerCraftObject[PLAYER_TWO]=NULL;
	}




	for (n=0; n<MAX_CREATURES; n++)
	{
		if (creatureObject->cont)
		{
			creature=creatureObject->objectData;

#ifndef __CDVERSION
		objectGlobs.activeCreatures[creatureObject->type]++;
#endif

			creature->handler(creatureObject,time);

		}
		creatureObject++;
	}

#ifndef __CDVERSION
	{
		char	string[128];

		sprintf(string, "rm=%d, rw=%d, sn=%d, sp=%d, sc=%d",objectGlobs.activeCreatures[0],objectGlobs.activeCreatures[1],objectGlobs.activeCreatures[2],objectGlobs.activeCreatures[3],objectGlobs.activeCreatures[4]);
		Font_PrintF(legoGlobs.stdFont,100,8,string);
	}
#endif


}

/*
	returns a suitable minifigure target, (and the deltaX/deltaY or NULL if
	nothing found within range (delta squared)
*/
lpOBJECT	Creature_GetMinifigureTarget(lpOBJECT creatureObject, int range, int *deltaX, int *deltaY)
{
	lpCREATURE 		creature=creatureObject->objectData;
	lpOBJECT			test,target=NULL;
	int				deltaSquared=(5120*512)+(5120*5120),deltaSquared2,dx,dy;



/* FIXME: need to check player 2, if present */

	test=objectGlobs.playerMinifigureObject[PLAYER_ONE];
	if (test)
	{	
		dx=(creatureObject->x-(test->x))>>12;
		dy=(creatureObject->y-(test->y))>>12;
		*deltaX=dx;
		*deltaY=dy;

		deltaSquared=(dx*dx)+(dy*dy);
		if (deltaSquared<range)
			target=test;
	}
	else
	{
		*deltaX=5120;			/* return a large delta for non targets */
		*deltaY=5120;
	}

	test=objectGlobs.playerMinifigureObject[PLAYER_TWO];
	if (test)
	{
		dx=(creatureObject->x-(test->x))>>12;
		dy=(creatureObject->y-(test->y))>>12;

		deltaSquared2=(dx*dx)+(dy*dy);
		if (deltaSquared2<deltaSquared && deltaSquared2<range)
		{
			*deltaX=dx;
			*deltaY=dy;
			target=test;
		}
	}
	

	return	target;


}


/*
	returns a suitable craft target, or NULL if
	nothing found within range (delta squared)
*/
lpOBJECT	Creature_GetCraftTarget(lpOBJECT creatureObject, int range, int *deltaX, int *deltaY)
{
#ifdef SKIP_IT

	lpCREATURE 		creature=creatureObject->objectData;
	lpCRAFT			testCraft=craftGlobs.craftPool.craftList,target=NULL;
	int				dx,dy;


	for (n=0; n<craftGlobs.craftPool.numCraft; n++)
	{

	/* test only non clipped craft

		if (!(testCraft->cont->renderFlags & RENDER_FLAGS_CLIPPED))
		{


		}
		testCraft++;
	}


/* FIXME: need to check player 2, if present */

	test=creatureGlobs.playerCraft[PLAYER_ONE];			/* NULL will indicate player is not on foot */

	if (test)
	{
		dx=(creature->x-(test->x))>>12;
		dy=(creature->y-(test->y))>>12;
		*deltaX=dx;
		*deltaY=dy;

		if (((dx*dx)+(dy*dy))<range)
			target=test;
	}
	else
	{
		*deltaX=5120;			/* return a large delta for non-targets */
		*deltaY=5120;
	}

/* force to player 1 for now */


	return	target;
#endif


	return	NULL;

}


/*
	kill a creature, and trip any associated triggers
*/
void	Creature_KillCreature(lpOBJECT	creatureObject)
{
	lpCREATURE	creature=creatureObject->objectData;

/* -------------------------------------------------- */
/* some stuff for triggers here, trigger on death etc */
/* -------------------------------------------------- */
/* -------------------------------------------------- */
/* -------------------------------------------------- */
/* -------------------------------------------------- */

	creatureObject->cont=NULL;								/* release object */
	creature->type=-1;										/* release creature */
	Container_Hide(creature->refCont, TRUE);
}





/*
	inflict damage on minifigure
*/
void	Creature_DamagePlayer(lpOBJECT minifigureObject, int damage)
{
	
	if (minifigureObject)
	{
		lpMINIFIGURE	minifigure=minifigureObject->objectData;

		minifigure->health-=damage;
		if (minifigure->health<0)
			minifigure->health=0;

#ifdef DEBUG_CONSOLE
		{
			char	string[64];
			sprintf(string,"health=%d",minifigure->health);
			CONSOLE_STRING(string);
		}
#endif

	}
}












/*
	draw a line between two world points
*/
void	draw_world_line(LPVECTOR3D	pos,LPVECTOR3D	pos2, int red, int green, int blue)
{
	GsLINE	line;
	GsCOORDINATE2	coord;
	MATRIX	mat;
	short		coords[4];
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
	line.x0=coords[0];
	line.y0=coords[1];

	vector.vx=-pos2->x;
	vector.vy=pos2->z;
	vector.vz=pos2->y;
	gte_RotTransPers(&vector,(long*)&coords[0],&depth,&flag,&sort);

	line.x1=coords[0];
	line.y1=coords[1];

	GsSortLine(&line,&gfxGlobs.Wot[gfxGlobs.bufID],sort);

}
