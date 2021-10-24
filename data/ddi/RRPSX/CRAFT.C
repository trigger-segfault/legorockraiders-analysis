//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// craft handler For <LEGO [Rock Raiders]>
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

#include	"globals.h"


#define	SHADOWS

/*

	HMD models need some attention. Vehicles really should have
	the animation data stripped, because we don't use it. The minfigures
	driving the vehicles need combining into one section, for easy manipulation.




*/

int	Boulder_AddRandomBoulder(int x, int y, int z, int scale, int direction, int speed, int zSpeed, int time, int creationFlags);
int	Boulder_AddBoulder(int x, int y, int z, int scale, int direction, int speed, int zSpeed, int time, int creationFlags);
int	Boulder_AddSmoke(int x, int y, int z, int scale, int scaleDelta, int zSpeed, int startAlpha, int alphaDelta, int red, int green, int blue);






#define		ROTOR_IDLE_SPEED		(256)
#define		ROTOR_FLY_SPEED		(512)
#define		ROTOR_SPEED_DELTA		(16)

#define		HOVER_HEIGHT_TURN_CUTOFF	(128<<12)			//altitude at which turning will take effect
#define		HOVER_HEIGHT_MOVE_CUTOFF	(128<<12)			//altitude at which movement will take effect

#define		ENGINE_VOLUME_DELTA			(4)
#define		HELI_VOLUME_DELTA				(2)



/* this is used for null input to uncontrolled craft */
CONTROL				nullControlSet[MAX_CONTROLS];


#define	CONCEAL_HMD_BLOCK(c,b)	HMD_SetBlock(Container_Mesh_GetModel(c),b,0)
#define	REVEAL_HMD_BLOCK(c,b)	HMD_SetBlock(Container_Mesh_GetModel(c),b,1)

enum
{
	TURN_LEFT,
	TURN_RIGHT,
};



OBJECT_GLOBS	objectGlobs;				/* the unified object list */

#define		DEFAULT_MODEL_SCALE			(0.35)


CRAFT_SETUP	craftSetupData[]=
{

/*--------------------------------------------------------------------------------*/
/*- The ground craft -------------------------------------------------------------*/
/*--------------------------------------------------------------------------------*/

/* the large digger */

	{
		"LDIGGER",
		ToFIXED(DEFAULT_MODEL_SCALE),
		Craft_UpdateGroundCraft,
		ToFIXED(2.4),		/* acceleration delta forwards */
		ToFIXED(2.0),		/* acceleration delta backwards */ 
		ToFIXED(0.44),		/* deceleration delta */
		ToFIXED(38.0),		/* forward speed cap */
		ToFIXED(30.0),	/* reverse speed cap */

		8,						/* turn rate delta */
		64,					/* turn rate cap */

		ToFIXED(1.0),		/* turn force move delta */
		ToFIXED(12.0),		/* turn force move speed cap */
		0,
		0,
		ToFIXED(1000.0),	/* object mass, not used at present */

		300,					/* orientation plane radius */
		256,					/* angle spread for above */
		64,					/* clip size */

		48,
		56,

		ToFIXED(31.0),		/* zdeltadelta (fudged gravity) */

		40,20,				/* engine sound parameters, base, offset */

		CF_CAN_DRILL|CF_DRIVEABLE|CF_LIFTABLE,		/* attribute flags */
		4,						/* drill speed delta */
		127,
		Lego_SurfaceType_Hard,						/* max rock type drillable */		
		350,
		-256,
		-1,
		0,0,
	},




/* the big laser */

	{
		"BIGLASER",
		ToFIXED(DEFAULT_MODEL_SCALE),
		Craft_UpdateGroundCraft,
		ToFIXED(2.4),		/* acceleration delta forwards */
		ToFIXED(2.0),		/* acceleration delta backwards */ 
		ToFIXED(0.44),		/* deceleration delta */
		ToFIXED(38.0),		/* forward speed cap */
		ToFIXED(30.0),	/* reverse speed cap */

		8,						/* turn rate delta */
		64,					/* turn rate cap */

		ToFIXED(1.0),		/* turn force move delta */
		ToFIXED(12.0),		/* turn force move speed cap */
		0,
		0,

		ToFIXED(1000.0),	/* object mass, not used at present */

		200,					/* orientation plane radius */
		128,					/* angle spread for above */
		64,					/* clip size */

		48,
		56,

		ToFIXED(31.0),		/* zdeltadelta */

		40,20,				/* engine sound parameters, base, offset */

		CF_DRIVEABLE,
		0,
		0,
		0,
		0,
		0,
		-1,
		0,0,
	},


/* the bulldozer */

	{
		"BULLDOZE",
		ToFIXED(DEFAULT_MODEL_SCALE),
		Craft_UpdateGroundCraft,
		ToFIXED(2.4),		/* acceleration delta forwards */
		ToFIXED(2.0),		/* acceleration delta backwards */ 
		ToFIXED(0.44),		/* deceleration delta */
		ToFIXED(38.0),		/* forward speed cap */
		ToFIXED(30.0),	/* reverse speed cap */

		8,						/* turn rate delta */
		64,					/* turn rate cap */

		ToFIXED(1.0),		/* turn force move delta */
		ToFIXED(12.0),		/* turn force move speed cap */
		0,
		0,

		ToFIXED(1000.0),	/* object mass, not used at present */

		250,					/* orientation plane radius */
		256,					/* angle spread for above */
		48,					/* clip size */

		45,
		50,

		ToFIXED(31.0),		/* zdeltadelta */

		40,20,				/* engine sound parameters, base, offset */

		CF_DRIVEABLE,						/* flags */
		0,
		0,
		0,
		0,
		0,
		-1,
		0,0,
	},


/* the small truck */

	{
		"STRUCK",
		ToFIXED(DEFAULT_MODEL_SCALE),
		Craft_UpdateGroundCraft,
		ToFIXED(2.4),		/* acceleration delta forwards */
		ToFIXED(2.0),		/* acceleration delta backwards */ 
		ToFIXED(0.44),		/* deceleration delta */
		ToFIXED(30.0),		/* forward speed cap */
		ToFIXED(25.0),	/* reverse speed cap */

		8,						/* turn rate delta */
		64,					/* turn rate cap */

		ToFIXED(1.0),		/* turn force move delta */
		ToFIXED(12.0),		/* turn force move speed cap */
		0,
		0,

		ToFIXED(1000.0),	/* object mass, not used at present */

		100,					/* orientation plane radius */
		256,					/* angle spread for above */
		40,					/* clip size */

		25,
		35,

		ToFIXED(31),		/* zdeltadelta */

		40,20,				/* engine sound parameters, base, offset */

		CF_DRIVEABLE|CF_LIFTABLE,
		0,
		0,
		0,
		0,
		0,
		-1,
		0,0,
	},


/* the small laser */

	{
		"LASER",
		ToFIXED(DEFAULT_MODEL_SCALE),
		Craft_UpdateGroundCraft,
		ToFIXED(2.4),		/* acceleration delta forwards */
		ToFIXED(2.0),		/* acceleration delta backwards */ 
		ToFIXED(0.44),		/* deceleration delta */
		ToFIXED(30.0),		/* forward speed cap */
		ToFIXED(25.0),		/* reverse speed cap */

		8,						/* turn rate delta */
		64,					/* turn rate cap */

		ToFIXED(1.0),		/* turn force move delta */
		ToFIXED(12.0),		/* turn force move speed cap */
		0,
		0,

		ToFIXED(1000.0),	/* object mass, not used at present */

		100,					/* orientation plane radius */
		256,					/* angle spread for above */
		40,					/* clip size */


		30,
		45,

		ToFIXED(31.0),		/* zdeltadelta */

		40,20,				/* engine sound parameters, base, offset */


		CF_DRIVEABLE,
		0,
		0,
		0,
		0,
		0,
		-1,
		0,0,
	},


/* the small digger */

	{
		"SDIGGER",
		ToFIXED(DEFAULT_MODEL_SCALE),
		Craft_UpdateGroundCraft,
		ToFIXED(2.4),		/* acceleration delta forwards */
		ToFIXED(2.0),		/* acceleration delta backwards */ 
		ToFIXED(0.44),		/* deceleration delta */
		ToFIXED(30.0),		/* forward speed cap */
		ToFIXED(25.0),		/* reverse speed cap */

		8,						/* turn rate delta */
		64,					/* turn rate cap */

		ToFIXED(1.0),		/* turn force move delta */
		ToFIXED(12.0),		/* turn force move speed cap */
		0,
		0,

		ToFIXED(1000.0),	/* object mass, not used at present */

		100,					/* orientation plane radius */
		256,					/* angle spread for above */
		40,					/* clip size */


		25,
		35,

		ToFIXED(31.0),		/* zdeltadelta */

		40,20,				/* engine sound parameters, base, offset */

		CF_CAN_DRILL|CF_DRIVEABLE|CF_LIFTABLE,			/* attribute flags */
		8,															/* drill speed delta */
		127,
		Lego_SurfaceType_Loose,
		120,
		0,
		-1,
		0,0,
		
	},

/*--------------------------------------------------------------------------------*/
/*- The air craft ----------------------------------------------------------------*/
/*--------------------------------------------------------------------------------*/



/* the large helicopter (the ladies love a big chopper, don't they sir?) */

	{
		"HELICOPT",
		ToFIXED(DEFAULT_MODEL_SCALE),
		Craft_UpdateAirCraft,
		ToFIXED(3.0),		/* acceleration delta forwards */
		ToFIXED(2.0),		/* acceleration delta backwards */ 
		ToFIXED(0.34),		/* deceleration delta */
		ToFIXED(50.0),		/* forward speed cap */
		ToFIXED(30.0),		/* reverse speed cap */

		8,						/* turn rate delta */
		64,					/* turn rate cap */

		ToFIXED(1.0),		/* turn force move delta */
		ToFIXED(15.0),		/* turn force move speed cap */
		ToFIXED(512),		/* cruising altitude */
		ToFIXED(16),		/* climb rate */

		ToFIXED(1000.0),	/* object mass, not used at present */

		0,
		0,
		64,					/* clip size */

		48,
		56,

		ToFIXED(31.0),		/* zdeltadelta */

		50,20,

		CF_DRIVEABLE|CF_CAN_LIFT,						/* attribute flags */
		0,					/* drill speed delta */
		0,
		0,
		0,
		0,
		0,					/* shadow type */
		ToFIXED(200),
		ToFIXED(320),
	},


/* the small helicopter */

	{
		"SHELICOP",
		ToFIXED(DEFAULT_MODEL_SCALE),
		Craft_UpdateAirCraft,
		ToFIXED(4.0),		/* acceleration delta forwards */
		ToFIXED(3.0),		/* acceleration delta backwards */ 
		ToFIXED(0.34),		/* deceleration delta */
		ToFIXED(40.0),		/* forward speed cap */
		ToFIXED(25.0),		/* reverse speed cap */

		16,						/* turn rate delta */
		96,					/* turn rate cap */

		ToFIXED(1.0),		/* turn force move delta */
		ToFIXED(15.0),		/* turn force move speed cap */
		ToFIXED(384),		/* cruising altitude */
		ToFIXED(32),		/* climb rate */

		ToFIXED(1000.0),	/* object mass, not used at present */

		0,
		0,
		32,					/* clip size */


		25,
		35,

		ToFIXED(31.0),		/* zdeltadelta */

		55,25,

		CF_DRIVEABLE,
		0,
		0,
		0,
		0,
		0,
		1,					/* shadow type */
		ToFIXED(90),
		ToFIXED(90),
	},


/* the hoverboard */

	{
		"HOVBOARD",
		ToFIXED(DEFAULT_MODEL_SCALE),
		Craft_UpdateAirCraft,
		ToFIXED(6.0),		/* acceleration delta forwards */
		ToFIXED(3.0),		/* acceleration delta backwards */ 
		ToFIXED(0.34),		/* deceleration delta */
		ToFIXED(48.0),		/* forward speed cap */
		ToFIXED(35.0),		/* reverse speed cap */

		24,						/* turn rate delta */
		128,					/* turn rate cap */

		ToFIXED(1.0),		/* turn force move delta */
		ToFIXED(15.0),		/* turn force move speed cap */
		ToFIXED(256),		/* cruising altitude */
		ToFIXED(32),		/* climb rate */

		ToFIXED(1000.0),	/* object mass, not used at present */

		0,
		0,
		32,					/* clip size */

		25,
		40,

		ToFIXED(31.0),		/* zdeltadelta */

		100,30,				/* engine sound parameters, base, offset */

		CF_DRIVEABLE,
		0,
		0,
		0,
		0,
		0,
		5,					/* shadow type */
		ToFIXED(64),
		ToFIXED(64),
	},


/*--------------------------------------------------------------------------------*/
/*- The non craft ----------------------------------------------------------------*/
/*--------------------------------------------------------------------------------*/



/* a crate */
	{
		"CRATE",
		ToFIXED(0.5),
		Craft_UpdateNonCraft,
		ToFIXED(2.4),		/* acceleration delta forwards */
		ToFIXED(2.0),		/* acceleration delta backwards */ 
		ToFIXED(0.44),		/* deceleration delta */
		ToFIXED(38.0),		/* forward speed cap */
		ToFIXED(30.0),	/* reverse speed cap */

		8,						/* turn rate delta */
		64,					/* turn rate cap */

		ToFIXED(1.0),		/* turn force move delta */
		ToFIXED(12.0),		/* turn force move speed cap */
		0,
		0,
		ToFIXED(1000.0),	/* object mass, not used at present */

		300,					/* orientation plane radius */
		256,					/* angle spread for above */
		64,					/* clip size */

		25,
		35,

		ToFIXED(31.0),		/* zdeltadelta (fudged gravity) */

		40,20,				/* engine sound parameters, base, offset */

		CF_LIFTABLE,		/* attribute flags */
		0,						/* drill speed delta */
		127,
		Lego_SurfaceType_Hard,						/* max rock type drillable */		
		350,
		-256,
		3,
		ToFIXED(80),
		ToFIXED(80),
	},


/* a water scoop */
	{
		"SCOOP",
		ToFIXED(0.5),
		Craft_UpdateNonCraft,
		ToFIXED(0.0),		/* acceleration delta forwards */
		ToFIXED(0.0),		/* acceleration delta backwards */ 
		ToFIXED(0.44),		/* deceleration delta */
		ToFIXED(38.0),		/* forward speed cap */
		ToFIXED(30.0),		/* reverse speed cap */

		8,						/* turn rate delta */
		64,					/* turn rate cap */

		ToFIXED(1.0),		/* turn force move delta */
		ToFIXED(12.0),		/* turn force move speed cap */
		0,
		0,
		ToFIXED(1000.0),	/* object mass, not used at present */

		300,					/* orientation plane radius */
		256,					/* angle spread for above */
		64,					/* clip size */

		25,
		35,

		ToFIXED(31.0),		/* zdeltadelta (fudged gravity) */

		40,20,				/* engine sound parameters, base, offset */

		CF_LIFTABLE,		/* attribute flags */
		0,						/* drill speed delta */
		127,
		Lego_SurfaceType_Hard,						/* max rock type drillable */		
		350,
		-256,
		4,
		ToFIXED(80),
		ToFIXED(144),

	},

};

extern	SMOOTH		cameraSmooth;













/*
	new craft creation routine for trigger list
*/
BOOL	Craft_CreateCraft(int craftType,int x, int y, int direction)
{
	lpCRAFT 			craft;
	lpOBJECT			newObject;
	int				n;

	if (objectGlobs.craftContList[craftType])
	{
		/* find free object */

		for (n=CRAFT_LIST_START; n<(CRAFT_LIST_START+MAX_CRAFT); n++)
		{
			if (!(objectGlobs.objectList[n].cont))
			{
				newObject=&objectGlobs.objectList[n];

				craft=&objectGlobs.craftList[objectGlobs.numCraft];
				newObject->x=x<<12;
				newObject->y=y<<12;
				newObject->angleY=direction;
				newObject->objectData=craft;
				Craft_CreateCraftData(newObject,craftType);
				Container_SetParent(legoGlobs.rootCont, craft->refCont);
				objectGlobs.numCraft++;
				return	TRUE;
			}
		}
	}
	return	FALSE;
}


void Craft_CreateCraftData(lpOBJECT object, int vehicleType)
{
	VECTOR3D		position,rotation;
	lpCRAFT 		craft=object->objectData;

	craft->typeID=vehicleType;
                   
/* cache container */

	craft->refCont=Container_Clone(objectGlobs.craftContList[vehicleType]);
	object->cont=craft->refCont;

/* scale the model */

	Container_SetScale(craft->refCont,craftSetupData[vehicleType].modelScale);


	craft->controlledBy=-1;		/* default to uncontrolled */


/* get height and orientation from new position */

	Surface_GetHeight(legoGlobs.currLevel,object->x>>12,object->y>>12,&object->zSurface);
	object->z=ToFIXED(object->zSurface);
	object->zSurface=object->z;
	object->class=OC_CRAFT;
	object->type=vehicleType;

	craft->zDelta=0;
	object->speed=0;
	craft->wheelSpin=0;
	craft->turnRate=0;

	craft->turnRateCap=					craftSetupData[vehicleType].turnRateCap;							/* maximum rate of turn */
	craft->turnRateDelta=				craftSetupData[vehicleType].turnRateDelta;						/* delta for rate, this is fixed for a joypad */

	craft->accelDeltaForward=			craftSetupData[vehicleType].accelDeltaForward;
	craft->accelDeltaBackward=			craftSetupData[vehicleType].accelDeltaBackward;
	craft->decelDelta=					craftSetupData[vehicleType].decelDelta;
	craft->forwardSpeedCap=				craftSetupData[vehicleType].forwardSpeedCap;
	craft->backwardSpeedCap=			craftSetupData[vehicleType].backwardSpeedCap;

	craft->turnForceMoveDelta=			craftSetupData[vehicleType].turnForceMoveDelta;
	craft->turnForceMoveCap=			craftSetupData[vehicleType].turnForceMoveCap;

	craft->radius=							craftSetupData[vehicleType].radius;
	craft->spread=							craftSetupData[vehicleType].spread;

	craft->mass=							craftSetupData[vehicleType].mass;
	craft->craftHandler=					(void*) craftSetupData[vehicleType].craftHandler;

	craft->refCont->clipSize=			craftSetupData[vehicleType].clipSize;
	object->collisionRadius=				craftSetupData[vehicleType].collisionRadius;
	object->activationRadius=			craftSetupData[vehicleType].activationRadius;

	object->collisionRadiusProduct=object->collisionRadius*object->collisionRadius*object->collisionRadius;		
	object->activationRadiusProduct=object->activationRadius*object->activationRadius*object->activationRadius;		

	craft->zDeltaDelta=					craftSetupData[vehicleType].zDeltaDelta;

	craft->engineBaseFrequency=		craftSetupData[vehicleType].engineBaseFrequency;
	craft->engineOffsetFrequency=		craftSetupData[vehicleType].engineOffsetFrequency;

	Container_SetWorldPosition(craft->refCont,object->x>>12,object->y>>12,object->z>>12);

	craft->drillSfxVoice=-1;
	craft->engineVolume=0;

	craft->flags=							craftSetupData[vehicleType].flags;
	craft->drillSpeedDelta=				craftSetupData[vehicleType].drillSpeedDelta;
	craft->drillSpeedCap=				craftSetupData[vehicleType].drillSpeedCap;
	craft->drillSpeed=0;
	craft->drillPos=0;					/* used for setting drill rotation */
	craft->drillRadius=					craftSetupData[vehicleType].drillRadius;
	craft->drillAngleOffset=			craftSetupData[vehicleType].drillAngleOffset;

	craft->maxRockType=					craftSetupData[vehicleType].maxRockType;
	
/* stuff for aircraft - ignored by ground craft */

	craft->climbRate=				craftSetupData[vehicleType].climbRate;
	craft->altitudeReference=	craftSetupData[vehicleType].cruisingaltitude;

	craft->rotorSpeed=ROTOR_IDLE_SPEED;
	craft->hoverHeightTarget=object->zSurface;
	craft->hoverHeight=object->zSurface;
	craft->loopingSfxVoice=-1;


#ifdef SHADOWS
	if (craftSetupData[vehicleType].shadowType!=-1)
	{
		craft->shadowType=craftSetupData[vehicleType].shadowType;
		craft->shadowCont=Container_CreateFloorSprite(legoGlobs.rootCont,objectGlobs.craftShadowSet);
		craft->shadowW=craftSetupData[vehicleType].shadowW;
		craft->shadowH=craftSetupData[vehicleType].shadowH;
		Container_SetScale(craft->shadowCont,ONE);
		Container_Hide(craft->shadowCont, TRUE);
	}
	else
#endif
		craft->shadowCont=NULL;


/* stuff for drill control etc. here... */



}




/*
	update SFX for drilling vehicles
*/
void		Craft_SetVolumeAndFrequencyDrillSfx(lpOBJECT object, int sample, int baseFrequency, int frequencyAdjust, int rockType)
{
	lpCRAFT	craft=object->objectData;
	int		speedOffset=craft->drillSpeed;



	if (craft->drillSfxVoice==-1)		/* not currently playing */
	{
		if (craft->drillSpeed>0) 
			craft->drillSfxVoice=Sfx_PlayEffect(sample,baseFrequency,0);		/* start looping SFX */
	}
	else			/* adjust currently playing sound */
	{
		if (craft->drillSpeed==0)
		{
			Sfx_StopEffect(craft->drillSfxVoice);		/* voice is unused now, release it */
			craft->drillSfxVoice=-1;
		}
		else		/* modulate volume and pitch */
		{
			if (legoGlobs.pauseFlag)
			{
				SsUtSetVVol(craft->drillSfxVoice,0,0);
				return;
			}
			else
				SsUtSetVVol(craft->drillSfxVoice,craft->drillSpeed>>1,craft->drillSpeed>>1);

		/* pitch will key off type, from fastest to slowest (0==thin air) */

			Sfx_ChangePitch(craft->drillSfxVoice,sample,baseFrequency,(baseFrequency-(rockType<<1)+frequencyAdjust)<<7);

		}
	}
}



//#define	PRINT_INFO

/*
	-------------------------------------------------------------------------
	new craft handler for land based vehicles

	there will be a separate handler for air vehicles. They could be combined
	but it will be neater to have them separate, since they will have quite
	different functionality.

	to do:
		altitude handling

	support for analogue controller		
	data for different types of craft
	
	-------------------------------------------------------------------------
*/
BOOL	Craft_UpdateGroundCraft(lpPLAYER player, lpOBJECT object, int time)
{
	lpCRAFT 			craft=object->objectData; 
	VECTOR			v1,v2,v3;
	int				nextX,nextY,nextZ;
	int				xd,yd;
	int				turnSpeed;
	int				turning=FALSE,inAir=FALSE;
	int				tempSurface;
	lpCONTROL 		control;
	int				rockType=0;

	unsigned char	*padBuffer;
	int				padType;

	REAL				turnScale=0;
	REAL				moveScale=0;
	lpLego_Block	block;



	if (craft->refCont->renderFlags & RENDER_FLAGS_CLIPPED)
	{
		
		if (++craft->sleepTimer>10)
			return FALSE;			
	}
	else
		craft->sleepTimer=0;

	if (craft->flags & CF_LIFTED)
		return	FALSE;


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
		
		turnScale=(padBuffer[LEFT_STICK_HORIZONTAL]<<5)-((127<<5)+16);


/* toggle for player leaving craft */

		if (PAD_EVENT(control,CONTROL_ACTIVATION_TOGGLE))
		{
			CLEAR_EVENT_RELEASE(control,CONTROL_ACTIVATION_TOGGLE);

			if (object->speed==0)		/* can't exit until the vehicle has stopped moving */
			{
				if (Player_SetMinifigureToCraftPosition(player,512,TRUE))
				{
					player->flags|=PLAYER_FLAG_MINIFIGURE_ACTIVE;
					craft->controlledBy=-1;
				}
				else
				{
					/* some sort of beep here */
					CONSOLE_STRING("Couldn't position player");
				}
			}
		}			


		craft->engineVolume+=ENGINE_VOLUME_DELTA;
		if (craft->engineVolume>127)
			craft->engineVolume=127;


	}
	else
	{
		control=nullControlSet;		/* uncontrolled craft need to idle, but they don't want input */
		padType=4;

		craft->engineVolume-=ENGINE_VOLUME_DELTA;
		if (craft->engineVolume<0)
			craft->engineVolume=0;

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
		craft->forwardSpeedCapScaled=Asm_MulFIX(moveScale,craft->forwardSpeedCap);
		craft->backwardSpeedCapScaled=Asm_MulFIX(moveScale,craft->backwardSpeedCap);
	}
	else
	{
		craft->forwardSpeedCapScaled=craft->forwardSpeedCap;
		craft->backwardSpeedCapScaled=craft->backwardSpeedCap;
	}


#ifdef PRINT_INFO
/*-----------------------------------------------------------------------------------------------------------------*/
{
	char	string[64];

	sprintf(string, "turnScale=%d, moveScale=%d", turnScale,moveScale);
	Font_PrintF(legoGlobs.stdFont,8,80,string);

	sprintf(string, "fscs=%d, bscs=%d", craft->forwardSpeedCapScaled,craft->backwardSpeedCapScaled);
	Font_PrintF(legoGlobs.stdFont,8,88,string);

}	
/*-----------------------------------------------------------------------------------------------------------------*/
#endif

/* craft rotation */

	turnSpeed=(object->speed>>6);


	if (padType==STANDARD_JOYPAD)
	{
		if (PAD_EVENT(control,CONTROL_TURN_LEFT))
		{
			craft->turnRate-=craft->turnRateDelta;
			if (craft->turnRate<-craft->turnRateCap)
				craft->turnRate=-craft->turnRateCap;

			object->angleY+=Asm_MulFIX(craft->turnRate,turnSpeed);

			CLEAR_EVENT_IMMEDIATE(control,CONTROL_TURN_LEFT);
			turning=TRUE;
		}
		else
		{
			if (PAD_EVENT(control,CONTROL_TURN_RIGHT))
			{

				craft->turnRate+=craft->turnRateDelta;
				if (craft->turnRate>craft->turnRateCap)
					craft->turnRate=craft->turnRateCap;

				object->angleY+=Asm_MulFIX(craft->turnRate,turnSpeed);
				CLEAR_EVENT_IMMEDIATE(control,CONTROL_TURN_RIGHT);
				turning=TRUE;
			}
			else		/* neither direction, re-centre */
			{
				if (craft->turnRate>0)
				{
					craft->turnRate-=craft->turnRateDelta;
					if (craft->turnRate<craft->turnRateDelta)
						craft->turnRate=0;
				}
				else if (craft->turnRate<0)
				{
					craft->turnRate+=craft->turnRateDelta;
					if (craft->turnRate>-craft->turnRateDelta)
						craft->turnRate=0;
				}

			}
		}
	}
	else
	{
		craft->turnRate=Asm_MulFIX(turnScale,craft->turnRateCap);
		object->angleY+=Asm_MulFIX(craft->turnRate,turnSpeed);
	}


/* moving */

/*
	get delta between current altitude and a point further on in the current direction,
	and use that to modify the speed of the craft
*/


	xd=rsin(object->angleY);
	yd=rcos(object->angleY);

	nextX=object->x-Asm_MulFIX((craft->forwardSpeedCap>>1),xd);
	nextY=object->y+Asm_MulFIX((craft->forwardSpeedCap>>1),yd);

	if (!Surface_GetHeight(legoGlobs.currLevel,nextX>>12,nextY>>12, &nextZ))
		nextZ=FromFIXED(object->zSurface);

/* probably need a cap check here */

 	if ((object->speed<craft->forwardSpeedCapScaled) && (object->speed>-craft->backwardSpeedCapScaled)) 
		object->speed+=(nextZ-(FromFIXED(object->zSurface)))<<10;		//9




#ifdef PRINT_INFO
/*-----------------------------------------------------------------------------------------------------------------*/
	{
		char	string[64];

		sprintf(string, "|3deltaZ=%d, speed=%d", (nextZ-(FromFIXED(object->zSurface))),object->speed>>12);
		Font_PrintF(legoGlobs.stdFont,8,32,string);
	}	
/*-----------------------------------------------------------------------------------------------------------------*/
#endif

	if (padType==STANDARD_JOYPAD)
	{
		if (PAD_EVENT(control,CONTROL_FORWARD))
		{
			CLEAR_EVENT_IMMEDIATE(control,CONTROL_FORWARD);
			if (object->speed<craft->forwardSpeedCap)
				object->speed+=craft->accelDeltaForward;
		}
		else
		{
			if (PAD_EVENT(control,CONTROL_REVERSE))
			{
				CLEAR_EVENT_IMMEDIATE(control,CONTROL_REVERSE);
				if (object->speed>-craft->backwardSpeedCap)
					object->speed-=craft->accelDeltaBackward;
			}
			else
			{
				if ((turning) && (object->speed<craft->turnForceMoveCap))
					object->speed+=craft->turnForceMoveDelta;
			}
		}
	}
	else
	{
		if (moveScale>0)
		{
		 	if (object->speed<craft->forwardSpeedCapScaled)
				object->speed+=Asm_MulFIX(moveScale,craft->accelDeltaForward);
		}
		else
		{
			if (object->speed>(craft->backwardSpeedCapScaled))
				object->speed+=Asm_MulFIX(moveScale,craft->accelDeltaBackward);
		}
	}


/* make craft decelerate */

	if (object->speed<0)
		object->speed+=craft->decelDelta;
	else if(object->speed>0)
		object->speed-=craft->decelDelta;
	else
		object->speed=0;

	if (object->speed!=0)
	{
		{
			int	width=((legoGlobs.currLevel->width-1)<<(9+12))-1;
			int	height=((legoGlobs.currLevel->height-1)<<(9+12))-1;

			int	newX,newY,newZ;

			newX=object->x-Asm_MulFIX(object->speed,xd);
			newY=object->y+Asm_MulFIX(object->speed,yd);


			if (!Craft_GetCraftInCollisionWithCraft(object, newX, newY, object->z))
			{

			/*
				this test is not very good, it's maybe too severe at present, if used it should
			 	be coupled with a force rotation to steer the vehicle out of collision.
			*/	
	
				block=&blockValue(legoGlobs.currLevel,newX>>(12+9),newY>>(12+9));

				if (block->flags & LEGOBLOCK_FLAG_BLOCK_DUG)
				{
					object->x=newX;
					object->y=newY;
				}
				else
				{
					object->speed=FromFIXED(Asm_MulFIX(ToFIXED(object->speed),ToFIXED(0.7)));
					object->x=newX;
					object->y=newY;

				}
			}
			else	/* bounce off */
			{
				object->speed=FromFIXED(Asm_MulFIX(ToFIXED(object->speed),ToFIXED(0.25)));
				object->speed=-(object->speed);
			}

#ifdef PRINT_INFO
/*-----------------------------------------------------------------------------------------------------------------*/
{
	char	string[64];

	sprintf(string, "|2deltaX=%d, deltaY=%d", Asm_MulFIX(craft->speed,xd),Asm_MulFIX(craft->speed,xd));
	Font_PrintF(legoGlobs.stdFont,8,40,string);

	sprintf(string, "b=%d",(craftGlobs.playerList[0].padBuffer[2]<<8)+craftGlobs.playerList[0].padBuffer[3]);
	Font_PrintF(legoGlobs.stdFont,8,100,string);
}	
/*-----------------------------------------------------------------------------------------------------------------*/
#endif

			if (object->x<0)
			{
				object->x=0;
			}

			if (object->y<0)
			{
				object->y=0;
			}

			if (object->x>width)
			{
				object->x=width;
			}

			if (object->y>height)
			{
				object->y=height;
			}

			craft->wheelSpin+=(object->speed>>8);
		}
		//else		/* bounce off */
		//{
		//	object->speed=FromFIXED(Asm_MulFIX(ToFIXED(object->speed),ToFIXED(0.75)));
		//	object->speed=-(object->speed);
		//}

		if (object->speed<0)
		{
			if (object->speed>craft->decelDelta)
				object->speed=0;
		}
		else
		{
			if (object->speed<craft->decelDelta)
				object->speed=0;
		}

	}	

/* vertices from object */

	if (Surface_SetUpVerticesFromContainer(craft->refCont,&v1,&v2,&v3,&tempSurface,object->angleY, craft->radius,craft->spread))
	{
		object->zSurface=tempSurface;
		Surface_GetOrientation(&v1,&v2,&v3,&craft->targetXr,object->angleY,&craft->targetZr);
	}
	else	/* off the edge, default to flat orientation */
	{
		object->zSurface=(object->z>>12);
	}


/* ----------------------------------------------------------------------------------------- */
/* REMOVEME:																											 */
/* ----------------------------------------------------------------------------------------- */
//	if (PAD_EVENT(control,CONTROL_CIRCLE_NO_ACTION))
//	{
//	craft->z-=(2048<<12);
//			CLEAR_EVENT_RELEASE(control,CONTROL_CIRCLE_NO_ACTION);
//			Sfx_PlayEffect(2,60,127);		/* start looping SFX */
//	}
/* ----------------------------------------------------------------------------------------- */


	craft->zDelta-=craft->zDeltaDelta;
	object->z-=craft->zDelta;

	object->zSurface<<=12;


	if (object->zSurface<object->z)
	{
		object->z=object->zSurface;
		craft->zDelta=0;		//-(craft->zDelta>>3);
	}
	else
		inAir=TRUE;

/* ------------------------------------- */
/* force on ground */

	//inAir=FALSE;	
	//craft->z=craft->zSurface;

/* ------------------------------------- */
	
	Container_SetWorldPosition(craft->refCont,object->x>>12,object->y>>12,object->z>>12);


	if (inAir)
	{
		craft->currentXr+=((craft->targetXr-craft->currentXr)>>6);
		craft->currentZr+=((craft->targetZr-craft->currentZr)>>6);
	}
	else
	{
		craft->currentXr+=((craft->targetXr-craft->currentXr)>>2);
		craft->currentZr+=((craft->targetZr-craft->currentZr)>>2);
	}

/* FORCE TO ACTUAL FOR TESTING */

//	craft->currentXr=craft->targetXr;
//	craft->currentZr=craft->targetZr;




	Container_SetRotation(craft->refCont,craft->currentXr,object->angleY,craft->currentZr);


	/* test for drilling */

	{
		int					dxd,dyd;
		int 					drillX,drillY;
		int					smokeX,smokeY;
		int					canDrill;
		lpLego_Block		drillBlock=NULL;

		static int rockGen=20;

		dxd=rsin(object->angleY+craft->drillAngleOffset);
		dyd=rcos(object->angleY+craft->drillAngleOffset);

		drillX=object->x;
		drillY=object->y;

		drillX-=Asm_MulFIX(craft->drillRadius<<12,dxd);
		drillY+=Asm_MulFIX(craft->drillRadius<<12,dyd);

		drillX>>=12;
		drillY>>=12;

		smokeX=drillX;
		smokeY=drillY;


#ifdef 0
	{
		VECTOR3D	v1;

		v1.x=drillX;
		v1.y=drillY;
		v1.z=object->zSurface>>12;
		draw_world_cross(&v1,255,255,255);
	}
#endif

		Craft_GetDigBlockAndSurface(&drillX,&drillY,&drillBlock);

#ifdef PRINT_INFO

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


		if (PAD_EVENT(control,CONTROL_DIG))
		{
			CLEAR_EVENT_IMMEDIATE(control,CONTROL_DIG);

			craft->drillSpeed+=craft->drillSpeedDelta;
			if (craft->drillSpeed>craft->drillSpeedCap)
				craft->drillSpeed=craft->drillSpeedCap;
			

			//if (canDrill)
			{

				if (!(drillBlock->flags & LEGOBLOCK_FLAG_BLOCK_DUG))
				{
					if (drillBlock->surfaceType>craft->maxRockType)
						rockType=Lego_SurfaceType_Immovable+3;						/* walls are too hard for this vehicle */
					else
					{
						drillBlock->damage-=(craft->drillSpeed>>5);

					/* generate drill stones */

						if ((legoGlobs.frameCount & 7)==4)
						{
							int 	yAngle=object->angleY+2048-512;
							int	smokeZ;
							
							if (!Surface_GetHeight(legoGlobs.currLevel,smokeX,smokeY, &smokeZ))
					,*.,*.,*.,0850850850850:70:70:70:7+,*,-++,*,-+*%$*%$*%$*%$,41,41,41,41/:50:6/95/950:70:70:70:7+/.+/.+/.+/./95/95/95/95-84-84-84-84*65*65*65*65$%%%&&$%%$%%*52*52*52*52*52*52*52*52'30(41'30'30!$!!$!!$!!$!%,)$+($+($+($+($+($+($+(# # # # )*()*()*(*+){~{~{~{~‚…‰„ˆ‚…‰„ˆ€ƒ‡‚†€ƒ‡‚†‚†€ƒ‡‚†‚†‚†‚†€ƒ‡‚†‚…‰„ˆ„ˆ‚…‰€„‡…ˆ€„‡…ˆ„ˆ„ˆ€ƒ‡€ƒ‡…‰…ˆŒ†‰†‰jjnjjnkkojjn%#"&$#&$#%#"$'&$'&$'&%('&,*&,*&,*&,*$'&$'&%('$'&()&()&()&()&,41,41-52,41/62.51.51.51*.,*.,*.,*.,+,*+,*+,*+,*3;73;74<83;7196196196196086/75/75/75*.,*.,*.,*.,.:6.:6.:6.:61:91:91:91:9*1/+20*1/*1/,&#-'$,&#,&#*1/*1/*1/*1/1:91:91:91:92;:1:91:92;:*-,*-,+.-*-,+/.+/.+/.+/.4;:5<;4;:4;:4;:4;:5<;4;:),+(+*(+*(+*)-,)-,*.-)-,.63.63.63.63064064175064)*()*()*(*+))-,)-,)-,)-,2752752752751961961962:7+,*+,*+,*+,**.,*.,+/-*.,0850850850850:70;71;80:7+,*+,*,-+,-+*%$*%$*%$*%$-52,41-52,41/95/95/95/950:70:70:70:7+/.+/.+/.+/./95/950:6/95-84.95-84-84*65*65*65*65%&&$%%$%%$%%*52*52*52*52*52*52*52*52'30'30(41'30!$!!$!!$!!$!$+($+($+($+($+($+($+($+(# # # # *+))*()*()*(z}€z}€{~{~‚…‰‚…‰„ˆ‚…‰‚†€ƒ‡€ƒ‡‚†€ƒ‡€ƒ‡‚†‚†€ƒ‡€ƒ‡€ƒ‡€ƒ‡„ˆ„ˆ„ˆ€ƒ‡€ƒ‡€ƒ‡„ˆ€ƒ‡„ˆ€ƒ‡„ˆ€ƒ‡†Š‡‹†Š†Šllpllpllpllp&#"&#"'$#'$#&#!&#!&#!&#!&#"&#"&#"&#"'$"'$"'$"'$"(%#'$"(%#'$"'$"(%#(%#'$"&#"&#"&#"&#"'$"(%#'$"'$"'$"'$"'$"'$"'$"'$"'$"(%#'$"'$"'$"(%#(%#'$"'$"'$"'$"&#!&#!&#!&#"&#"&#"'$#'$"'$"(%#(%##"!#"!$#"#"!.)&-(%-(%-(%#"!#"!#"!#"!(%#(%#(%#(%#'$"'$"'$"'$"'$"'$"'$"'$"'$"'$"'$"'$"'$#&#"&#"&#"(%#(%#'$"'$"'$"'$"'$"'$"'$"(%#(%#'$"&#!&#!&#!&#!&#"&#"&#"&#"'$"'$"'$"'$"'$"'$"'$"'$"&#"&#"&#"&#"'$#&#"&#"&#"'$"'$"'$"(%#'$"'$"'$"'$"'$"'$"'$"(%#'$"(%#'$"(%#%#!%#!%#!%#!,(%,(%,(%,(%%#!&$"%#!%#!'$"'$"'$"(%#&#"&#"&#"&#"&#"&#"&#"&#"'$"(%#(%#(%#&#"&#"&#"&#"'$"(%#'$"'$"&#"&#"&#"&#"'$"'$"'$"'$"'$"'$"'$"'$")&$(%#(%#(%#(%#(%#(%#(%#(%#(%#(%#(%#'$"(%#'$"'$"&#!&#!&#!&#!,+*,+*,+*,+*{~z}€{~{~‚…‰‚…‰ƒ†Š‚…‰€ƒ‡€ƒ‡„ˆ„ˆ€ƒ‡„ˆ„ˆ€ƒ‡„ˆ‚…‰„ˆ‚…‰„ˆ€ƒ‡„ˆ„ˆ„ˆ€ƒ‡„ˆ€ƒ‡€ƒ‡€ƒ‡„ˆ€ƒ‡‡‹†Š†Š‡‹kkokkokkokko&#"&#"'$#&#"&#!&#!'$"&#!'$#&#"'$#&#"'$"'$"'$"(%#'$"'$"'$"'$"(%#'$"'$"'$"&#"&#"&#"&#"'$"'$"(%#'$"'$"'$"'$"'$"'$"'$"'$"'$"(%#'$"'$"'$"'$"'$"'$"(%#'$"&#!&#!'$"&#"&#"'$#&#"'$"'$"'$"'$"#"!#"!#"!$#"-(%-(%-(%-(%#"!#"!$#"$#"(%#(%#(%#(%#'$"'$"'$"'$"'$"'$"'$"'$"'$"'$"'$"'$"&#"&#"&#"'$#'$"'$"(%#'$"'$"'$"'$"(%#'$"'$"'$"'$"&#!&#!&#!&#!&#"&#"&#"&#"(%#'$"'$"'$"'$"'$"'$"'$"&#"&#"&#"&#"&#"&#"&#"&#"'$"'$"'$"'$"'$"'$"'$"'$"'$"'$"'$"'$"'$"'$"'$"'$"%#!%#!%#!%#!,(%,(%,(%,(%%#!%#!&$"%#!'$"'$"'$"'$"&#"&#"&#"&#"&#"&#"&#"&#"'$"'$"'$"'$"&#"&#"&#"&#"'$"'$"(%#'$"&#"'$#&#"'$#'$"'$"'$"'$"'$"'$"'$"'$")%#(%#(%#(%#)&$)&$(%#(%#(%#(%#(%#(%#'$"'$"'$"'$"&#!&#!&#!&#!,+*,+*,+*,+*{~{~{~z}€ƒ†Š‚…‰ƒ†Š‚…‰„ˆ€ƒ‡„ˆ€ƒ‡€ƒ‡€ƒ‡€ƒ‡€ƒ‡‚…‰‚…‰‚…‰„ˆ„ˆ„ˆ„ˆ€ƒ‡€ƒ‡€ƒ‡€ƒ‡„ˆ€ƒ‡€ƒ‡„ˆ€ƒ‡†Š‡‹†Š‡‹kkollpkkollp&#"&#"'$#&#"&#!&#!&#!&#!&#"&#"&#"&#"'$"'$"'$"'$"(%#'$"'$"'$"'$"'$"'$"'$"&#"'$#&#"&#"(%#'$"'$"'$"'$"'$"'$"'$"'$"'$"'$"'$"(%#'$"'$"(%#'$"'$"'$"'$"&#!&#!&#!&#!&#"&#"&#"&#"'$"'$"'$"'$"#"!$#"$#"#"!-(%-(%.)%-(%#"!#"!#"!#"!(%#(%#(%#(%#'$"'$"'$"'$"(%#'$"'$"'$"'$"(%#'$"'$"&#"&#"&#"&#"'$"'$"'$"'$"'$"'$"'$"'$"'$"'$"'$"'$"&#!'$"'$"&#!'$#&#"&#"&#"(%#'$"'$"'$"'$"'$"'$"'$"&#"'$#&#"&#"&#"&#"&#"'$#'$"'$"'$"'$"'$"'$"'$"'$"(%#'$"'$"'$"'$"'$"'$"'$"%#!&$"%#!%#!,(%,(%,(%-)%%#!%#!%#!%#!'$"'$"'$"'$"'$#&#"&#"&#"&#"'$#&#"'$#'$"'$"'$"'$"&#"&#"'$#'$#'$"'$"'$"'$"&#"&#"&#"&#"'$"'$"'$"'$"'$"'$"(%#'$"(%#(%#(%#(%#(%#(%#(%#(%#(%#(%#(%#(%#'$"'$"'$"'$"&#!&#!&#!&#!,+*,+*,+*,+*z}€z}€z}€{~ƒ†Šƒ†Š‚…‰ƒ†Š„ˆ„ˆ„ˆ€ƒ‡„ˆ€ƒ‡€ƒ‡€ƒ‡„ˆ„ˆ„ˆ„ˆ„ˆ€ƒ‡€ƒ‡€ƒ‡„ˆ€ƒ‡„ˆ€ƒ‡„ˆ€ƒ‡€ƒ‡€ƒ‡†Š‡‹†Š‡‹llpkkokkokko&#"&#"&#"&#"&#!&#!&#!'$"&#"&#"&#"&#"'$"'$"'$"(%#(%#'$"'$"'$"'$"'$"'$"'$"&#"&#"&#"&#"'$"'$"'$"(%#'$"'$"'$"'$"'$"(%#'$"(%#'$"'$"(%#'$"'$"'$"'$"'$"&#!&#!'$"&#!'$#&#"&#"&#"(%#'$"'$"'$"#"!#"!#"!$#"-(%-(%-(%-(%#"!#"!#"!#"!(%#(%#(%#)&$'$"(%#'$"'$"'$"'$"'$"'$"(%#'$"'$"'$"&#"'$#'$#&#"(%#(%#(%#'$"'$"'$"'$"'$"'$"(%#'$"'$"&#!&#!'$"&#!&#"&#"&#"&#"'$"(%#'$"'$"'$"'$"'$"'$"'$#&#"&#"&#"&#"&#"&#"&#"'$"'$"(%#'$"'$"'$"'$"(%#'$"'$"'$"'$"'$"'$"'$"'$"%#!%#!%#!&$",(%,(%,(%,(%&$"%#!%#!%#!'$"'$"'$"'$"&#"&#"&#"&#"&#"&#"&#"&#"(%#'$"'$"(%#&#"&#"&#"&#"'$"'$"'$"'$"&#"&#"&#"&#"'$"'$"'$"'$"'$"'$"'$"'$"(%#(%#(%#(%#(%#(%#(%#(%#(%#(%#(%#(%#'$"'$"(%#'$"'$"&#!&#!&#!-,+,+*,+*,+*z}€z}{~z}€‚…Š‚…‰ƒ†Šƒ†Š„ˆ€ƒ‡„ˆ„ˆ„ˆ„ˆ€ƒ‡„ˆ„ˆ‚…‰‚…‰„ˆ{~ƒ|„{~ƒ{~„}€„}€„~…~…‚†€ƒ‡‚†ƒ‡…ˆŒ†‰…ˆŒ†‰kkokkojjnjjn(&%(&%(&%(&%)*()*()*()*(+/-,0.+/-+/-&*('+)&*(&*(**'**'**'**'.43.43.43.43064064064064,.,,.,,.,-/-+,*+,*+,*+,*5<86=96=95<85<85<85<85<8275275275386-0,-0,-0,-0,5<85<85<85<85<86=95<85<8+/.+/.,0/+/.,&#,&#,&#,&#)-,)-,)-,*.-275386275386275275275275+,*+,*+,*+,*+/.,0/+/.+/.275275386275387387387387+,*+,*+,*+,*-1/-1/-1/-2/498387387498275275275275)('*)()(')('(,)(,)(,)(,),52,41,41,41*5/*5/*6/*5/)*()*()*()*((+*(+*(+*(+*/75/75/75/751=81=81=82>9*+)*+)*+)*+)*%$*%$*%$*%$,41,41,41,41/95/950:6/95/950:6/95/95+,*+,*,-++,*-84-95-84-84-84-84-84.95+83+83+83+83&'$%&#%&#%&#,41,41,41,41-84-84-84-84,63,63,63,63%'%&(&%'%%'%'0.'0.'0.'0.*1/*1/*1/*1/ '$ '$ '$ '$-.+./,-.+./,{~|‚{~{~ƒ†‹ƒ†‹ƒ†‹„‡Œ‚…‰ƒ†Šƒ†Š‚…‰„ˆ„ˆ„ˆ„ˆ„ˆ‚…‰„ˆ„ˆ|„{~ƒ|„{~ƒ~…~…}€„~…‚†‚†ƒ‡€ƒ‡…ˆŒ†‰†‰…ˆŒjjnjjnjjnkko(&%(&%(&%(&%)*()*()*()*(+/-+/-+/-+/-&*(&*(&*(&*(**'**'++(**'/54/54.43.43064175064175,.,,.,-/-,.,+,*+,*+,*+,*5<85<85<85<85<85<85<85=9386386275386-0,-0,-0,-0,5<85<85<85<85<85<86=95<8+/.+/.+/.+/.-&#,&#-'$-'$)-,)-,)-,)-,386386275275275275275275+,*+,*+,*,-+,0/+/.+/.+/.275275275275387387387387+,*+,*+,*+,*.20-1/-1/-1/387498387387275275386275)(')(')(')('(,))-*(,)(,)-52,41,41,41+60*5/*5/*5/)*()*(*+))*((+*(+*(+*(+*/75/750860861=82>91=81=8*+)*+)*+)*+)*%$*%$*%$+&%,41-52,41,41/95/95/950:6/95/950:6/95+,*+,*,-++,*-84-84-94-94.95-84.95-84+83+83+83+83%&#%&#%&#%&#,41,41,41,41-84.95.95-84,63,63,63,63%'%&(&%'%%'%'0.(1/'0.'0.+20*1/*1/*1/ '$ '$ '$ '$-.+-.+-.+-.+{~{~{~{~„‡Œ„‡Œƒ†‹„‡Œ‚…‰‚…‰ƒ†Šƒ†Š€ƒ‡„ˆ€ƒ‡„ˆ„ˆ‚…‰‚…‰‚…‰{~ƒ{~ƒ{~ƒ|„}€„~…~…}€„‚†‚†‚†€ƒ‡†‰†‰…ˆŒ…ˆŒkkojjnkkokko(&%(&%(&%(&%*+)*+))*()*(+/-+/-+/-+/-&*(&*(&*(&*(**'++(**'++(.43.43.43.43175175064064,.,,.,,.,,.,,-+,-++,*+,*5<85<85<85<85<85<85<85<8275275275275-0,-0,-0,-0,5<85<85<85<85<86=95<85<8+/.+/.+/.+/.,&#,&#,&#,&#)-,)-,)-,)-,386275275275275275275275+,*+,*+,*+,*+/.+/.+/.,0/275275275275387498387387+,*+,*,-+,-+-1/-1/-1/-1/387387397498275275386275*)(*)()(')('(,)(,))-*(,),41,41,41,41*5/*5/*5/*6/)*()*()*()*((+*(+*(+*(+*/75086/75/751=81=81=81=8*+)*+)*+)*+)*%$+&%*%$*%$,41,41,52-52/95/95/95/95/95/95/95/:5+,*+,*+,*+,*-84-94-84.95-84-84-84-84+83+83+83+83%&#&'$%&#%&#,41,41,41,41.95.95-84-84,63,63,63,63&(&%'%&(&%'%'0.'0.'0.'0.*1/*1/*1/*1/ '$ '$ '$ '$-.+-.+-.+-.+|‚{~{~|‚ƒ†‹ƒ†‹„‡Œƒ†‹‚…‰‚…‰ƒ†Š‚…‰€ƒ‡€ƒ‡€ƒ‡€ƒ‡„ˆ„ˆ„ˆ„ˆ{~ƒ|„{~ƒ|„~…}€„}€„}€„‚†‚†€ƒ‡‚††‰†‰†‰†‰jjnjjnjjnjjn(&%(&%(&%(&%)*(*+))*()*(+/-+/-+/-+/-&*(&*('+)&*(**'**'**'**'.43.43/54.43064175175064,.,,.,,.,,.,,-++,*,-++,*5<85<85<85<85<85<85<85<8275275386275.1-.1--0,-0,5<85<85<85<85<85<86=95<8+/.+/.+/.+/.,&#,&#,&#-'$)-,)-,)-,)-,386275386275275275275275,-++,*+,*+,*+/.+/.+/.+/.275275386275498387387387+,*+,*+,*+,*-1/-1/-2/-1/387387387387275386275275*)()(')('*)()-*(,)(,)(,),41,41,41,41*6/*5/*5/*5/)*()*()*()*((+*),+(+*(+*/75/75/75/751=82>92>91=8*+)*+)*+)*+)+&%*%$*%$+&%,52,41,41,41/95/950:6/95/:5/95/95/95+,*+,*+,*+,*-84-84.95.95-84-84.95-84+83+83,94+83%&#%&#&'$%&#,41,41,41,41-84-84-84-84,63,63,63,63%'%%'%%'%%'%'0.'1.'0.'0.*1/*1/*1/*1/ '$ '$ '$ '$-.+-.+-.+./,{~{~{~{~„‡Œƒ†‹„‡Œ„‡Œ‚…‰ƒ†Š‚…‰ƒ†Š€ƒ‡„ˆ€ƒ‡„ˆ„‰‚…‰‚…‰‚…‰‚†‚†‚†‚†|‚|‚{~{~}€„}€„}€„~…„‡‹…ˆŒ„‡‹…ˆŒjjnjjnjjnkko%#"%#"%#"%#"%&&$%%$%%$%%&,*&,*&,*&,*%)&%)&%)&%)&()&()&()&()&.74.63.63.63/54/54.43.54)-,)-,)-,)-,*+)*+)*+)+,*086/75/86/75.63/74.63.74.51.51/62.51-0,-0,-0,-0,3;73;73;73;70:70:70:70:7*/.).-).-).-,&#,&#-'$,&#+/-,0.,0.+/-275275275386386275275386+,*+,*+,*+,**-,+.-*-,*-,064064175064175064175064)*()*()*()*(+/-,0.+/-+/-386275275386275275275275((%((%((%((%&*('+)&*(&*(*1/*1/+20*1/)..*//)..)..()&()&()&()&(,))-*(,)(,).43.43.43.43196196196196+,*+,*+,*+,*($!($!($!($!+21+21+21+21/86/75/75/75/75/75/86/75+/-+/-+/-+/-,43,43,43,43+21+21,32+21+21,32,32,32$%%$%%%&&$%%(41'30'30'41'30(41(41'30%2,%3-%2,%2,"%"!$!!$!!$!"/("/("/(#0)#0)"/("/("/(( ( )!( +,*+,*+,*+,*z}€z}€z}€z}€‚…‰‚…‰‚…‰„‰€ƒ‡„ˆ€ƒ‡€ƒ‡~…~…‚†‚†€ƒ‡€ƒ‡€ƒ‡€ƒ‡‚†‚†‚†‚†{~{~|‚{~}€„}€„}€„~……ˆŒ„‡‹…ˆŒ„‡‹jjnkkojjnjjn%#"%#"%#"%#"$%%$%%$%%$%%&,*&,*&,*&,*%)&%)&%)&%)&()&()&()&()&.63.63.63.63.43.54.43.43)-,*.-)-,)-,*+)+,**+)+,*086086/75086.63.63/74.63.51.51.51.51-0,-0,-0,-0,3;74<84<83;70:70:70:71;8).-).-).-).-,&#,&#,&#,&#+/-+/-+/-+/-275275275386275275275275+,*+,*+,*+,**-,*-,*-,+.-064064064064175175064175)*()*()*()*(+/-+/-+/-+/-386275275275275275275275((%((%))%))&'+)&*(&*(&+)*1/*1/+20+20)..)..)..)..()&()&()&()&)-*(,)(,)(,).43.43/54.43196196196196+,*+,*+,*+,*($!($!($!($!,32+21+21+21/75/75086/75/75/75/75086+/-+/-+/-+/-,43,43,43,43+21+21+21,32+21,32+21,32%&&$%%$%%$%%(41'30(41'30'30'30'30'30%2,%2,%3,%2,"%"!$!!$!!$!#0)"/("/("/("/("/("0)"/(( ( ( ( +,*,-++,*+,*z}€z}€z}€z}€‚…‰„ˆ„ˆ‚…‰„ˆ€ƒ‡€ƒ‡€ƒ‡~…~…‚†~…‚†‚†€ƒ‡‚†~…~…‚†~…{~|‚{~|‚}€„~…~…}€„…ˆŒ„‡‹…ˆŒ…ˆŒjjnkkojjnkko%#"%#"%#"%#"$%%%&&$%%$%%&,*&,*&,*&,*%)&%)&%)&%)&()&()&()&()&.63.63.74.63.43.43/54.43)-,*.-)-,)-,*+)+,**+)*+)/75/75/75086.63.63/74.63.51/62.51.51-0,-0,-0,-0,3;73;73;73;70:70:70;71;8).-).-).-).--'$,&#,&#,&#+/-+/-+/-,0.386275275275275275275386+,*+,*+,*+,**-,+.-*-,*-,064064064175175064064064)*()*()*()*(+/-+/-+/-+/-275386275275275386275275((%((%((%((%&*(&*(&*(&*(*1/*1/*1/*1/)..)..)..)..()&()&()&()&(,)(,)(,)(,).54/54/54.43196196196196+,*+,*+,*+,*($!($!)%"($!+21+21+21+21/75/75086/75/75/75/75/75+/-+/-+/-+/-,43,54,54,43+21+21+21,32+21+21+21+21$%%$%%$%%$%%(41'30(41'30'41'30'30'30&3-%2,&3-&3-!$!!$!!$!!$!"/("/("/(#0)#0)"/("/("/(( ( ( ( +,*+,*+,*+,*{~z}€z}€z}€‚…‰„ˆ‚…‰‚…‰„ˆ€ƒ‡€ƒ‡„ˆ~…~…‚†‚†€ƒ‡‚†€ƒ‡‚†~…~…~…‚†{~|‚|‚|‚}€„}€„}€„~…„‡‹…ˆŒ„‡‹„‡‹jjnkkojjnjjn%#"%#"&$#%#"$%%$%%$%%$%%&,*'-+&,*&,*%)&%)&%)&&*'()&()&()&()&.63.63/74.63.43.43.43/54)-,)-,)-,)-,*+)*+)*+)*+)086/75/75/75.63.63.63.63/62.51.51.62-0,-0,-0,-0,3;73;73;73;70:70:70:71;8*/.).-).-*/.-&#,&#,&#,&#+/-+/-+/-+/-275275275275275386275275,-++,*+,*+,**-,*-,*-,*-,064064064064064064064175)*()*()*()*(+/-+/-,0.+/-275275275275275275275386((%((%))&((%&*(&*(&*(&*(*1/*1/*1/*1/)..)..)..*//()&()&()&)*'(,)(,)(,)(,).43.43.43.43196196196196+,*+,*+,*+,*($!($!($!($!+21+21+32,32/75/75/75/75/75/75/75/75+/-+/-+/-+/-,43-54,43,43+21+21,32+21+21,32+21,32$%%$%%$%%$%%'30'30'30'30'30'30'30'30&3-&3-%2,%2,"%"!$!"%"!$!"/("/("/("/("/(#0)"/("/(( ( ( ( +,*+,*+,*+,*z}z}€{~{~‚…‰‚…‰‚…‰„ˆ„ˆ€ƒ‡„ˆ€ƒ‡~…~…‚†~…€ƒ‡€ƒ‡‚†€ƒ‡€ƒ‡‚†€ƒ‡‚†}€„}€„}€„~…~…}€„~…}€„ƒ†‹ƒ†‹„‡Œƒ†‹kkojjnkkokko%#"%#"%#"%#"%&#%&#%&#%&#&*(&*(&*('+)$%%$%%$%%$%%((%((%))%((%+60*5/*6/+60*1/*1/+20*1/(,))-*(,)(,))*()*()*()*(.63.63.63.63.63.63.63.63,41,41,41,41,.,,.,,.,,.,0:70:70:71;8-84-84-94-84)-,)-,)-,)-,+%"+%"+%"+%"-1/-1/-1/-1/6=95<85<85<8275275275386,+*,+*,+*,+**-,),+),+),+064175064175275275275275)*(*+))*(*+)*-,*-,*-,*-,064064064064064064175175()&()&()&()&&*(&*('+)&*(-0,.1--0,-0,-2/-2/-1/-1/)*()*()*()*(),+*-,),+),+.63.63.63.63387387387387+,*+,*+,*+,*($!($!($!($!+21+21,32+21-64-64-64-64(1/'0.'0.'1.),+),+),+),+,43-54,43,43,43-54,54,43-64-64-64.75%'%%'%%'%%'%*52+63*52*52'30'30'30'30'30'30'30'30#$"$%##$"#$"%2,%2,&3-%2,%2,%2,%2,%2,( ( ( ( *,)*,)*,)*,)z}€{~z}€z}€‚…‰‚…‰‚…Š‚…‰‚‡‚‡‚‡~†‚†‚†‚†€ƒ‡‚†‚†‚†€ƒ‡€ƒ‡€ƒ‡‚†€ƒ‡}€„}€„~…}€„~…}€„}€„~…ƒ†‹„‡Œƒ†‹ƒ†‹jjnkkokkokko%#"&$#%#"%#"%&#%&#%&#%&#&*(&*(&*(&*($%%$%%$%%%&&))%((%((%))%*5/*5/*5/*5/*1/*1/*1/*1/(,))-*(,)(,))*(*+))*(*+).63.63/74.63.63.63.74.63,41,41,41,41,.,,.,,.,,.,0:70:70:70:7-84-84.95-84)-,*.-*.-*.-+%",&#+%",&#-1/-1/-1/-1/5<86=96=95<8275386275275,+*,+*,+*,+*),+),+*-,),+064064064175275275275386*+))*()*()*(*-,*-,*-,+.-064064064064064064064064)*&()&()&()&&*('+)&*(&*(-0,-0,-0,-0,-1/-1/.20-1/)*()*()*()*(*-,*-,),+),+.74.63.63.63498387387387+,*+,*+,*+,*($!($!)%")%"+21+21+21+21-64.75-64.75'0.'0.'0.'0.),+),+),+),+,43,43,43,43-54,43-54,43-64-64-64-64&(&%'%%'%%'%*52+63+63*63'30(41'30'30(41'30'30'30#$"#$"#$"#$"&3-%2,%2,%2,%2,%2,%2,%2,( ( ( ( *,)*,)+-**,)z}€z}€{~{~ƒ†Š‚…‰‚…‰ƒ†Š‚‡‚‡‚‡~†‚†€ƒ‡‚†€ƒ‡‚†‚†‚†€ƒ‡‚†‚†‚†€ƒ‡}€„~…}€„}€„~…}€„}€„~…ƒ†‹ƒ†‹ƒ†‹ƒ†‹kkokkojjnjjn%#"%#"%#"%#"%&#%&#%&#%&#&*(&*('+)&*($%%$%%$%%$%%((%((%((%((%*5/*5/*5/*5/*1/*1/+20*1/(,)(,)(,)(,))*()*()*()*(.63.63/74.63/74.74.63.63,41,41-52,41,.,,.,,.,,.,0:70:70:70:7-84-84-84-84)-,)-,)-,)-,+%"+%"+%"+%"-1/-1/-1/.205<85<86=95<8386275386275,+*,+*,+*,+*),+),+),+),+064175064175386275275275)*(*+))*(*+)*-,*-,*-,*-,064064175064064064064064()&()&()&()&&*(&*(&+)&+)-0,.1--0,-0,-2/-1/-1/-1/)*()*()*()*(),+),+),+),+.63.63.63.63498498387387+,*+,*+,*+,*($!($!($!($!+21+21+21+21.75-64.75-64'0.'0.'0.'0.*-,),+),+*-,,43,43,43-54,43,43,43,43-64-64-64-64&(&&(&%'%%'%*52*52+63*52'30'30'30'30'30'30'30'30#$"#$"#$"#$"%2,%2,%2,%2,%2,&3-%2,&3-( ( )!( *,)*,)*,)*,){~{~{~{~‚…‰ƒ†Š‚…‰ƒ†Š~†~†~†‚‡‚†€ƒ‡‚†‚†‚†‚†‚†€ƒ‡‚†‚†€ƒ‡‚†}€„}€„~…}€„}€„}€„~…}€„ƒ†‹ƒ†‹„‡Œ„‡Œkkojjnkkojjn&$#%#"%#"%#"%&#&'$%&#%&#&*(&*(&*(&*($%%$%%%&&$%%((%((%((%((%*5/*5/*6/+60*1/*1/*1/*2/)-*(,)(,)(,)*+))*()*()*(.63.63.63.63.63.63.63.63,41,41,41,41,.,,.,,.,,.,0:70:70:71;8-84-84.95-84)-,)-,*.-)-,+%",&#,%"+%"-1/-1/.20-1/5<85<85<85<8275275275275,+*,+*,+*-,+),+),+),+),+064064064064275275275275)*()*(*+))*(*-,*-,*-,*-,064064064064175064064064()&()&()&)*'&*(&*(&*('+)-0,-0,-0,-0,-1/-1/-1/-1/)*()*()*(*+)),+),+),+),+.63.63/74.63498387498387+,*+,*+,*+,*($!($!($!($!+21+21,32+21-64-64-64.75'0.'0.'1/'0.),+*-,),+),+,43,43-54,43,43-54,43,43-64-64-64-64%'%%'%%'%&(&+63*52*52*52(41'30(41'30'30'30'30'30#$"#$"#$"#$"%2,%2,%2,%2,%2,%2,%2,%2,( ( ( ( *,)*,)*,)*,){~z}€{~{~‚…‰‚…‰ƒ†Š‚…‰‚‡~†~†‚‡‚†‚†‚†€ƒ‡‚†‚†€ƒ‡‚†‚†€ƒ‡‚†‚†}€„~…}€„~…~…‚†‚†‚††‰†‰†‰†‰jjnjjnjjnjjn&%$'&%&%$&%$)(')(')(')('),+),+),+),+%'%%'%%'%%'%)''*(()'')''*1/*1/*1/*1/*1/+20+20*1/(,)(,)(,))-**+)*+)*+)*+)/86/75/75/75/62.51.51.51,41,52,41,41,.,,.,,.,,.,1962:7196196196196196196*/.).-).-*/.+%"+%"+%"+%"*-,+.-*-,*-,064064064175.43.43.43.43*+)*+)*+)*+)*.,*.,*.,*.,064064064064275275275275*+))*()*()*(*-,*-,*-,*-,064064175064064064064064()&()&()&()&&*(&*(&*(&*(-1/-1/-1/-1/-1/-1/-1/-1/**'**'**'**')-*(,)(,)(,).62.51.62/62/75/75/75/75+,**+)*+)*+)($!($!($!($!*1/*1/+20+20,41,41,41,41(1/'0.'0.'0.),+*-,),+),+.43/54.43.43-64-64-64-64/75/75/75/75&'&'('&'&&'&/87/87/87/87+83+83+93,94-84-84-84-84&(&%'%%'%%'%*5/*5/*5/*6/*5/*5/*5/*6/&-&&-&&-&&-&./,-.+-.+-.+wy|xz}xz}wy|„ˆ€ƒ‡€ƒ‡„ˆ}„~€…~€…~€…~…}€„}…~…€ƒ‡‚†€ƒ‡€ƒ‡‚†€ƒ‡€ƒ‡ƒ‡}€„}€„~…}€„~…~‚†‚†‚†…ˆŒ†‰…ˆŒ†‰jjnjjnjjnkko&%$&%$&%$&%$)(')(')(')('),+),+),+),+%'%%'%%'%%'%)''*((*(()''*1/*1/*1/+20*1/*1/*1/*1/(,))-*(,))-**+)*+)*+)*+)/75/75/75/75.51.51.51.51,41,41,41,41,.,-/-,.,,.,1961962:72:71961961962:7*/.*/.).-).-+%"+%",%"+%"*-,*-,*-,*-,064064064064.43/54.43.43*+)*+)*+)*+)*.,*.,+/-*.,064064064064386275275275)*(*+))*()*(*-,*-,*-,+.-064175064175175175064064()&()&)*'()&&*(&*(&*(&*(.20-1/-1/-1/-1/-1/.20-1/**'**'**'**'(,)(,)(,))-*.51.51.51.51/75/75/75/75*+)*+)+,**+))$!($!($!($!*1/*1/*1/*1/,41,41-52,41'0.'0.'1/'0.),+),+),+),+.43.43.43.43-64-64-64-64/75/75/75/75&'&&'&&'&&'&/87/87/87/87+83+83+94+83-84-84-84-94%'%%'%%'%&(&*5/*5/*5/*5/*5/+60*5/*5/&-&&-&&-&'.'-.+./,-.+./,wy|wy|wy|xz}€ƒ‡€ƒ‡„ˆ€ƒ‡~€…}„~€…}„~…~…~…}…€ƒ‡‚†‚†€ƒ‡€ƒ‡€ƒ‡€ƒ‡€ƒ‡}€„}€„}€„}€„~…~…~…~…†‰†‰…ˆŒ†‰kkojjnjjnjjn&%$&%$&%$&%$)(')(')(')('),+),+),+),+%'%%'%%'%&(&)'')'')'')''*1/*1/*1/*1/*1/*1/+20*1/)-*(,)(,)(,)*+)+,**+)*+)086/75/75/75.51.51.51.51,41,41,41,41,.,,.,,.,,.,1961961961961962:7196196).-).-*/.).-,&#,&#+%",&#*-,*-,*-,*-,175064064064.43.43.43.43*+)*+)*+)*+)*.,+/-*.,*.,064064064064275275275275*+))*()*()*(*-,*-,*-,*-,064064064064064175064064()&)*&()&()&'+)&*(&*(&*(-1/-1/.20-1/-1/-1/-1/.20++(**'**'**'(,)(,)(,))-*.51.51.51/62086086086/75*+)*+)*+)*+)($!($!($!($!*1/+20*1/*1/,52,41,41,41'0.'0.'0.'0.*-,),+),+),+.54.43.43/54-64.75-75-64/75/75/75/75&'&&'&&'&&'&/87/87/87/87+83+93+83+83-84-84-84-84%'%%'%%'%&(&*5/*6/+60*5/*5/*5/*5/+60&-&&-&&-&'.'./,-.+./,-.+wy|wy|wy|xz}€ƒ‡€ƒ‡„ˆ„ˆ~€…}„}„~€…~…~…~…}€„‚†€ƒ‡‚†€ƒ‡‚†‚†€ƒ‡‚†}€„~…~…}€„~…~…‚†~……ˆŒ†‰†‰†‰jjnjjnkkojjn&%$&%$'&%'&%)(')(')(')('),+),+*-,),+&(&&(&%'%&(&*'')'')''*((*1/*1/*1/*1/+20*1/*1/*1/)-*(,)(,))-**+)*+)*+)*+)/75/75086/75.51.51.51.51,41,41,41,41,.,,.,,.,,.,1962:72:7196196196196196).-).-).-*/.+%"+%"+%"+%"+.-+.-*-,*-,064064064064/54/54.43.43*+)*+)+,**+)*.,*.,*.,*.,175064064064275275275275)*()*()*()*(*-,*-,*-,*-,064064064064064064064064()&()&)*&()&&*(&*('+)&*(.20-1/-1/-1/.20-1/-1/-1/**'**'**'**'(,)(,))-*(,).51.51.51.51/75/75/75/75*+)*+)*+)*+)($!($!($!($!+20*1/*1/*1/-52,41,41,41'0.'0.'1.(1/),+),+),+),+.43.43.43.43-64-64-64-64/75/75/75/86&'&&'&&'&'('/87/87098/87+93+83+83+83-84-84-84-84%'%%'%%'%&(&*5/*5/*5/*5/*5/*5/*5/*6/&-&&-&'.'&-&-.+./,-.+-.+xz}wz}xz}xz}„ˆ€ƒ‡€ƒ‡€ƒ‡}„}„}„~€…}€„}…}€„}€„€ƒ‡€ƒ‡€ƒ‡€ƒ‡€ƒ‡€ƒ‡‚†‚†‚†‚†€ƒ‡‚†‚†‚†€ƒ‡‚†…ˆŒ†‰†‰…ˆŒkkojjnkkojjn%#"&$#%#"%#"$%%$%%$%%$%%(,)(,))-*(,)%'%%'%&(&%'%&'&&'&&'&&'&+21+21+21+21.21-10-10-10),+(+*(+*(+**))*))*))*)).43.43.43.43.51/62.51.51-1/-1/-1/-1/-.+./,-.+-.+196196196196085196085085*/.).-).-*/.+&#+&#+&#+&#(,)(,)(,)(,),41,41,41,41/62.51/62.51*+)*+)*+)+,**.,*.,*.,+/-.63.63.63.63.63.74.63.74&*(&+)&*(&*()-*)-*(,)(,).63.63.63.63064064064064)*()*()*(*+))-*(,)(,)(,).51.51/62/62072183072072+,*+,*+,*+,*)-*(,)(,)(,).5..5..5..5.072072072072*+)*+)*+)*+))#!)#!)#!)#!*1/*1/*1/*1/-74,63-74-74,41,41,41,41+.-+.-*-,+.-,41-52,41,41.43.43.43.43/75/75/75/75'(''('&'&'('4;:4;:5<;4;:1=81=81=82>92>91=81=82>9''$''$''$''$,71,71,82,71,71-82,71,71*0**0**0*+1+-.+-.+-.+./,wy|xz}xz}xz}€ƒˆ€ƒˆ„‰„‰‚†~…‚†~…‚†‚†€ƒ‡‚†„ˆ€ƒ‡„ˆ€ƒ‡‚†€ƒ‡€ƒ‡‚†‚†€ƒ‡‚†€ƒ‡‚†€ƒ‡‚†‚††‰…ˆŒ…ˆŒ…ˆŒjjnkkojjnjjn&$#%#"%#"%#"$%%$%%$%%$%%(,)(,)(,)(,)%'%%'%%'%%'%&'&&'&&'&'('+21,32+21+21-10-10.21-10(+*(+*(+*),++***))*))*)).43.43.43.43.51.51/62.51-2/-1/-1/-1/-.+-.+-.+./,2:7196196196085085085085).-).-*/.).-,'$+&#+&#,&#(,)(,))-*)-*,41,41,41,41.51.51.51.51*+)*+)*+)*+)+/-*.,*.,+/-.63.63.74.63/74.63.63.63'+)'+)&*(&*()-*(,)(,)(,).63.63.63.63064064175064)*()*()*()*((,))-*(,)(,).51.51.51.51183072072072+,*+,*+,*+,*(,)(,)(,)(,).5..6..5..5.072072072072*+)*+)*+)*+))#!)#!)#!*$"*1/*1/*1/*1/,63,63,63-74,41-52,41,41*-,*-,*-,*-,,41,41,41-52/54.43/54.43/75/75086/75&'&&'&&'&&'&5<;4;:4;:4;:2>91=81=81=81=81=81=81=8((%''$''$''$,71-82-82,71,71,71-82,71+1+*0**0*+1+-.+-.+-.+-.+wy|xz}wy|wy|„‰„‰€ƒˆ„‰~…~…~…‚†‚†‚†€ƒ‡‚†€ƒ‡„ˆ€ƒ‡„ˆ‚†‚†€ƒ‡‚†€ƒ‡‚†€ƒ‡€ƒ‡‚†‚†€ƒ‡‚††‰…ˆŒ…ˆŒ†‰kkojjnkkojjn%#"%#"%#"%#"$%%$%%$%%$%%(,)(,)(,)(,)%'%%'%%'%%'%&'&&'&&'&'('+21+21,32+21.21-10-10.21(+*(+*(+*(+**))+***))+**.43.43.43.43.51.51.62.51-1/.20-2/-1/-.+-.+-.+./,2:7196196196085085085085).-).-).-).-+&#+&#+&#+&#)-*(,))-*(,),41,52,41-52.51.51.51.51*+)*+)*+)*+)*.,*.,*.,+/-.63.63.63.63.63/74.63.63&*(&*(&*('+)(,))-*(,)(,).63.63/74/74175064064175)*()*()*()*((,)(,)(,)(,).51.51.51.51072072072072,-++,*+,*,-+(,)(,))-*(,).5..5..5..5.072072183072+,**+)*+)+,*)#!)#!)#!)#!*1/*1/*1/*1/,63,63,63,63,41,41,41,41*-,*-,*-,+.-,52,41-52,41.43.43.43.54/75/75086/75&'&'('&'&&'&4;:4;:4;:5<;1=82>91=81=81>91=82>91=8''$''$''$''$,71,71,71,71,71,71,71,71+1+*0**0**0*-.+-.+-.+-.+wy|wz}wy|xz}€ƒˆ„‰€ƒˆ€ƒˆ‚†~…~…‚†‚†‚†‚†‚†€ƒ‡€ƒ‡€ƒ‡„ˆ‚†€ƒ‡€ƒ‡‚†€ƒ‡€ƒ‡‚†‚†€ƒ‡€ƒ‡‚†‚††‰†‰†‰…ˆŒkkojjnjjnjjn%#"%#"%#"&$#$%%$%%$%%$%%(,))-*)-*(,)%'%%'%%'%%'%&'&&'&&'&&'&+21,32+21,32-10-10-10.21(+*(+*(+*(+**))*))*))*)).43.43/54.43/62/62.51.51-1/-1/-1/-1/-.+-.+-.+-.+1961962:72:7085085095085).-).-*/.).-+&#+&#+&#+&#(,)(,)(,)(,)-52,41,41,41/62.51.51.51*+)*+)*+)*+)*.,+/-*.,+/-.74.63.74.63.63.63/74.63'+)&*(&*(&*()-*(,)(,))-*.63.63.63.63064064064064)*()*()*(*+)(,))-*(,)(,).51/62.51.51072072183183+,*+,*,-+,-+(,)(,)(,)(,).5..5..5..5.072072183183*+)*+)*+)*+)*$")#!)#!)#!*1/+20*1/*1/,63-74,63,63,41,41,41,41+.-*-,*-,*-,,41,41-52,41.43.43.43/54/75086/75086&'&&'&&'&&'&4;:4;:4;:4;:1=81=82>91=81=82>92>91=8''$''$((%''$,71,71,71,71,71,71,71,71*0**0**0**0*-.+./,-.+-.+wy|wy|wy|xz}€ƒˆ€ƒˆ€ƒˆ€ƒˆ‚†‚†‚†‚†‚†‚†‚†‚†€ƒ‡„ˆ„ˆ„ˆ‚…‰ƒ†Š‚…‰‚…‰‚†‚†‚†‚†€ƒ‡„ˆ€ƒ‡€ƒ‡…ˆŒ…ˆŒ†‰…ˆŒkkokkokkojjn" " " #! $%##$"$%##$""#!!" !" !" %#"%#"%#"%#"&*(&*(&*(&*(&*(&*(&*(&*($'&$'&$'&$'&&'&&'&'('&'&(/+(/+(/+(/+).-).-*/.).-*.,*.,*.,*.,*+)*+)+,**+)+20*1/*1/*1/*1/*1/*1/*1/&*(&*(&*(&*(,&#,&#-&#,&#&,*&,*'-+&,*,52-52,41-52-84-84.95-84*,)*,)*,)*,)),+),+),+*-,.63.63.63.63.63/74/74/74%)&&*'%)&&*''+)&*(&*(&*(,41-52,41,41-52,41-52,41%)&%)&%)&%)&(,)(,)(,)(,).5..5..5..5..5..5./6/.5.*,'*,'*,'*,'$+($+($+(%,).20.20-1/-1/,41,41,41-52)*')*')*')*')#!)#!)#!)#!&3-%2,%2,%2,*5/+60*5/*5/'0.'0.(1/(1/),+),+),+),+,41,41,41-52,32+21+21+21,14,14,14,14&'&&'&&'&'('1:91:91:92;:.:4.:4.:4.:4.;4.;4.<4.;4&'$&'$&'$%&#/:3.92.92.92.92.92.92.92)/)(.((.((.(-.+-.+-.+-.+{~z}€z}€{~„ˆ‚…‰‚…‰‚…‰~‚†~…~…~…€ƒ‡„ˆ€ƒ‡€ƒ‡€ƒ‡„ˆ„ˆ„ˆƒ†Š‚…‰ƒ†Š‚…‰€ƒ‡‚†€ƒ‡‚†€ƒ‡„ˆ€ƒ‡€ƒ‡…ˆŒ†‰†‰†‰jjnjjnjjnkko" " #!" #$"#$"#$"#$""#!!" "#!!" %#"%#"%#"%#"&+)&*('+)&*(&*(&*(&*(&*($'&$'&$'&$'&&'&&'&&'&&'&(/+(/+(/+(/+*/.).-).-).-*.,*.,*.,*.,*+)*+)*+)+,*+20*1/+20*1/*1/*1/*1/*1/&*(&*(&*(&*(-&#,&#,&#-'$&,*&,*&,*&,*-52,41-52,41-84-84-84-84*,)*,)+-**,)),+),+),+),+.63.63.63.63.63.63.63.63%)&%)&%)&%)&&*(&*(&*(&*(,41,41,41,41,41,41,41,41%)&%)&%)&%)&(,)(,)(,))-*.5..5..5./6/.5..5..5..5.*,'*,'*,'+-($+($+($+($+(-1/-1/-1/.20,52,41,52,41)*')*')*')*')#!*$"*$")#!%2,%2,%2,&3-*5/*5/*6/*5/'0.'0.'0.'0.),+),+),+*-,,41,41,41,41+21+21+21,32,14,25,14,14&'&&'&&'&&'&1:91:91:91:9.:4.:4.:4.:4.;4.<4.;4.;4%&#%&#%&#%&#.92.92.92.92.92.92.92.92(.((.()/)(.(-.+./,-.+-.+z}€{~z}{~‚…‰‚…‰„ˆ‚…‰‚†~…~…~…€ƒ‡€ƒ‡€ƒ‡„ˆ„ˆ€ƒ‡€ƒ‡€ƒ‡‚…‰ƒ†Š‚…Šƒ†Š€ƒ‡€ƒ‡‚†ƒ‡„ˆ„ˆ„ˆ„ˆ†‰…ˆŒ†‰†‰jjnjjnjjnkko" " " " #$"$%##$"#$"!" !" !" !" %#"%#"%#"%#"&*('+)&*(&*(&*('+)'+)'+)$'&$'&$'&$'&&'&&'&&'&&'&(/+(/+(/+(/+).-).-*/.).-*.,*.,*.,*.,*+)*+)*+)*+)*1/+20+20*1/*1/*1/+20+20&*(&*(&*('+)-&#,&#,&#,&#'-+&,*'-+&,*,41,41,41,41-84-84-84.95*,)*,)*,)*,)),+*-,),+),+/74.63.63.63.63.63.63.63%)&&*'&*'%)&&*(&*(&*(&*(,41,41,41,41,41-52,41,41%)&%)&%)&%)&(,)(,)(,)(,).5..5..5..5..5..5..5..5.*,'*,'*,'+-($+($+($+($+(-1/-1/-1/-1/,41,41,41,41*+()*')*')*')#!)#!)#!)#!%2,&3-%2,%2,+60*5/*5/*5/'0.'0.'0.'0.),+*-,),+),+,41,41,41,41,32+21+21+21,14-25,14,14&'&&'&'('&'&2;:1:91:92;:.:4.;5.:4.:4/<5/<5.;4.;4%&#&'$%&#%&#.92.92.92.92.92.92.92.92(.((.((.((.(-.+-.+-.+-.+z}€z}€z}€z}€‚…‰‚…‰„ˆ„ˆ‚†‚†‚†~…€ƒ‡„ˆ€ƒ‡„ˆ„ˆ€ƒ‡„ˆ„ˆƒ†Š‚…Šƒ†Šƒ†Š‚†‚†‚†‚†„ˆ€ƒ‡„ˆ„ˆ…ˆŒ†‰…ˆŒ…ˆŒkkokkokkojjn" " " " #$"#$"#$"$%#!" !" "#!"#!%#"%#"&$#%#"&+)&*('+)&*(&+)&*('+)&*($'&$'&$'&$'&'('&'&&'&&'&)0,(/+(/+(/+).-).-).-).-*.,*.,+/-*.,*+)*+)*+)*+)*1/*1/*1/*1/*1/*1/+20*1/'+)&*(&*(&*(,&#,&#-'$,&#&,*&,*&,*&,*,41-52,41,41-84.95-84.95*,)*,)*,)+-*),+*-,),+),+.63.63.63.63/74.63.63.63%)&%)&&*'%)&&*(&*(&*(&*(,41,41,41-52,41,41-52,41%)&%)&%)&%)&(,))-*(,)(,).5./6/.5..5..5..5..5..5.+-'*,'*,'*,'$+(%,)$+($+(-1/-1/-1/-1/,41,41,41,41)*')*'*+()*')#!)#!)#!*$"%2,%2,%2,%2,+60*5/*5/*5/'0.'0.(1/'0.),+),+),+),+,41,41,41,41+21+21+21,32-25,14,14,14&'&&'&'('&'&1;:1:91:91:9/;5/;5.:4.:4.;4.;4.;4.;4%&#%&#%&#%&#.92/:3.92.92.92.92.92.92(.((.()/))/)-.+-.+-.+-.+{~z}€{~{~„ˆ„ˆ„ˆ‚…‰~…‚†~…‚†„ˆ„ˆ„ˆ€ƒ‡€ƒ‡€ƒ‡€ƒ‡„ˆƒ‡ƒ‡€„ˆƒ‡€ƒ‡„ˆ„ˆ€ƒ‡~…‚†‚†~……ˆŒ…ˆŒ„‡‹…ˆŒkkokkokkokko)%$)%$)%$*&%%#"%#"%#"%#"(%#(%#(%#(%#(%#(%#(%#)&$)%$*&%)%$)%$(&%(&%(&%(&%(&%)&%(&%(&%''$''$''$''$)%$)%$)%$)%$(&%(&%(&%(&%)(')('*)()(')(')(')(')(',(%+'$+'$+'$(&%(&%(&%(&%)(')(')('*)(&%$&%$&%$&%$/*'/*'/*'/*'''$''$''$''$()&()&)*'()&()&()&()&()&(&%(&%(&%(&%))&((%((%((%)*'*+()*')*')*')*')*')*'(&%(&%(&%(&%(&%(&%(&%(&%)*')*')*')*')*'*+')*')*'(&%(&%(&%(&%((%((%((%((%**'**'**'**'*,'*,'*,'*,'+(%+(%+(%+(%(&%(&%(&%(&%)*%)*%*+&)*%()&()&)*&()&+'$+'$+'$+'$-(%-(%-(%-(%((%((%''$((%)*%)*%)*%)*%()&()&()&()&)'&)'&(&%(&%**'++(**'++()(')(')('*)')(')('*)')('(&%(&%(&%(&%+,*+,*+,*+,*()&()&()&)*')*%)*%)*%)*%(&%(&%(&%(&%)*')*')*')*')*%)*%)*%)*%'&"'&"'&"('#,+*,+*,+*,+*xz}wy|xz}xz}‚…‰„ˆ‚…‰„ˆ}€„}€„~…}€„‚†€ƒ‡€ƒ‡‚†„ˆ€ƒ‡€ƒ‡„ˆƒ‡ƒ‡ƒ‡ƒ‡€ƒ‡€ƒ‡„ˆ€ƒ‡‚†~…~…~……ˆŒ„‡‹„‡‹…ˆŒkkokkokkokko)%$)%$)%$)%$%#"%#"%#"%#"(%#(%#(%#(%#(%#(%#)&$(%#)%$*&%)%$)%$(&%(&%)'&(&%(&%(&%(&%(&%''$((%''$''$)%$)%$)%$)%$)'&(&%(&%(&%)(')(')('*)()(')(')(')(',(%+'$+'$+'$(&%(&%(&%(&%)(')(')(')('&%$&%$&%$&%$/*'/*'/*'/*'''$''$''$''$()&()&()&()&()&()&()&()&(&%(&%(&%(&%((%((%((%))&)*')*')*')*')*')*')*')*')&%(&%(&%(&%(&%(&%(&%(&%)*')*'*+()*'*+()*')*')*'(&%(&%(&%)'&((%))%((%((%**'**'**'**'*,'*,'*,'*,'+(%+(%+(%+(%(&%(&%(&%(&%)*%)*%)*%*+&()&()&()&()&+'$,'$+'$+'$-(%-(%-(%.)&''$''$''$((%)*%)*%*+&)*%()&()&()&()&(&%(&%)'&(&%**'**'**'**'*)()(')(')('*)')(')(')('(&%(&%)'&(&%,-++,*+,*+,*()&()&()&()&)*%)*%)*%)*%(&%)&%)'&(&%)*')*')*')*')*%)*%)*%)*%'&"'&"'&"'&",+*-,+,+*,+*wy|xz}wy|xz}‚…‰„ˆ„ˆ‚…‰~…}€„}€„}€„€ƒ‡‚†€ƒ‡€ƒ‡„ˆ€ƒ‡„ˆ„ˆƒ‡ƒ‡ƒ‡€„ˆ€ƒ‡€ƒ‡€ƒ‡„ˆ~‚†~…‚†‚†„‡Œ„‡‹„‡‹„‡‹kkollpkkokko)%$)%$)%$)%$%#"%#"%#"%#"(%#(%#(%#(%#(%#(%#(%#(%#)%$)%$)%$)%$(&%(&%)'&(&%(&%(&%(&%(&%''$''$''$''$)%$)%$*&%)%$(&%(&%(&%(&%)(')('*)')(')(')(')(')('+'$+'$+'$+'$(&%(&%(&%(&%*)()(')(')('&%$&%$&%$&%$0+(0+(/*'/*'''$((%''$''$()&()&)*'()&()&()&()&()&(&%(&%(&%(&%))&((%((%((%*+()*')*')*')*')*'*+')*')'&(&%(&%)'&(&%(&%(&%)'&)*'*+()*')*')*')*')*')*'(&%(&%(&%(&%((%((%((%((%**'**'++'++(*,'*,'*,'*,'+(%+(%+(%+(%(&%(&%(&%(&%)*%*+&)*%)*%()&()&()&()&+'$+'$+'$+'$.)&-(%-(%-(%''$''$''$''$)*%)*%)*%*+&()&)*')*'()&(&%(&%(&%(&%**'**'++(**')(')(')(')(')(')(')(')('(&%)'&(&%(&%+,*,-++,*+,*)*'()&()&)*')*%)*%)*%)*%)'&(&%(&%(&%)*'*+()*')*')*%)*%)*%)*%'&"'&"'&"('#,+*-,+-,+,+*wy|wy|wy|xz}‚…‰‚…‰„ˆ„ˆ}€„}€„~…~…‚†€ƒ‡€ƒ‡‚†€ƒ‡€ƒ‡€ƒ‡€ƒ‡ƒ‡ƒ‡ƒ‡ƒ‡€ƒ‡„ˆ€ƒ‡„ˆ‚†~…~…~…„‡‹„‡‹…ˆŒ„‡‹kkokkokkokko*&%)%$)%$)%$%#"%#"%#"%#"(%#(%#(%#)&$)%#(%#(%#(%#)%$)%$)%$)%$(&%(&%(&%)&%(&%(&%(&%(&%''$''$''$''$)%$)%$)%$)%$(&%)'&(&%(&%)(')(')(')(')('*)()(')(',(%+'$+'$,(%(&%(&%(&%(&%)(')(')(')('&%$&%$&%$&%$0+(/*'/*'0+(''$''$''$''$()&()&()&()&()&()&()&()&(&%(&%(&%(&%((%((%((%((%*+()*')*')*')*'*+()*'*+((&%(&%(&%(&%(&%(&%(&%(&%)*')*')*')*'*+()*'*+(*+'(&%(&%(&%)'&((%((%))&((%**'**'**'**'*,'*,'*,'*,'+(%+(%+(%+(%(&%(&%(&%(&%)*%)*%*+&)*%()&()&()&()&+'$+'$+'$+'$-(%-(%-(%-(%''$''$''$''$)*%)*%)*%)*%()&)*'()&)*'(&%(&%(&%(&%**'**'++(**')('*)()(')(')(')(')(')('(&%(&%)'&(&%+,*+,*+,*+,*()&()&)*&()&)*%)*%)*%)*%(&%(&%(&%)'&)*')*')*')*')*%*+&)*%)*%('#'&"'&"'&"-,+,+*-,+-,+wy|wy|wy|wy|‚…‰‚…‰„ˆ‚…‰}€„~…}…}€„€ƒ‡‚†‚†€ƒ‡€ƒ‡„ˆ„ˆ„ˆ‚‡~†~†‚‡€„ˆ€„ˆ€„ˆ€„ˆ‚†‚†€ƒ‡€ƒ‡…‰…ˆŒ…ˆŒ…ˆŒjjnjjnkkojjn0+(/*'/*'/*'3-*3-*3-*3-*3-*3-*3-*3-*4.+3-*3-*3-*3-*3-*3-*3-*3,)3,)3,)3,)3-*3-*3-*3-*4.+3-*3-*3-*4.+3-*3-*4.+3,)4,)3,)3,)3,)3,)3,)3,)3,)4-*3,)3,)4-*4-*3,)4-*3,)3,)3,)4-*4-*3-*3-*3-*/*'/*'0+(/*'1*(1*(1*(1*(/*'/*'/*'/*'4-*4-*5.+4-*3,)3,)3,)3,)3-*3-*3-*3-*3,)3,)3,)3,)3,)4-*4-*4-*3,)3,)3,)3,)3-*3-*3-*3-*3-*3-*3-*4.+3,)3,)3,)3,)3,)4,)3,)3,)3-*3-*3-*4.+4.+3-*4.+3-*3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)3-*3-*3-*4-*3,)3,)3,)4,)3,)3,)3,)3,)/*'/*'0+'/*'/*'/*'/*'/*'1*(2+)1*(1*(3-*4.+3-*3-*3,)3,)3,)3,)4-*3,)3,)3,)3,)3,)3,)3,)3,)4-*4-*3,)4,)3,)4-*3,)3,)3,)3,)4-*3,)4-*3,)3,)4-*3,)3,)3,)4-*3,)3,)3,)3-*3-*3-*3-*4-*4-*3,)3,)3,)3,)3,)3,)3,)3,)4,)3,)30.30.30.30.x{~y|x{~y|ƒ†Š‚…Š‚…‰ƒ†Š‚†~…~…~…„ˆ‚…‰„ˆ„ˆ€ƒ‡„ˆ„ˆ„ˆ‚‡~†‚‡~†ƒ‡ƒ‡€„ˆƒ‡‚†€ƒ‡ƒ‡‚††‰…ˆŒ†‰…ˆŒkkokkojjnjjn/*'0+(/*'/*'3-*4.+3-*3-*3-*3-*3-*3-*3-*3-*3-*4.+3-*3-*3-*3-*3,)3,)3,)3,)4.+3-*3-*3-*4.+4.+3-*3-*3-*4.+3-*3-*3,)4-*3,)3,)3,)3,)4-*3,)3,)3,)3,)3,)3,)3,)4-*3,)3,)3,)4-*3,)3-*3-*3-*3-*/*'/*'/*'/*'2+)2+)1*(1*(/*'/*'/*'/*'4-*4-*4-*4-*3,)3,)4,)3,)3-*3-*3-*3-*3,)3,)3,)3,)3,)4-*4-*3,)3,)4-*3,)4-*4.+3-*3-*3-*3-*3-*3-*3-*3,)3,)3,)3,)3,)4-*3,)3,)3-*3-*3-*3-*3-*4.+3-*3-*3,)3,)4-*3,)3,)3,)3,)3,)4-*3,)3,)3,)4.+3-*3-*3-*3,)4-*3,)3,)3,)3,)3,)3,)/*'/*'/*'/*'/*'/*'/*'/*'2+)2+)2*(1*(4.+3-*3-*3-*3,)3,)3,)3,)4-*3,)4-*3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)4,)3,)3,)3,)3,)4-*3,)4-*3,)3,)3,)3,)3,)3,)3-*3-*3-*3-*3,)3,)3,)3,)3,)3,)3,)3,)4-*3,)3,)3,)30.41.30.30.x{~y|y|y|‚…‰ƒ†Šƒ†Š‚…‰‚†~…‚†~…‚…‰‚…‰„ˆ‚…‰€ƒ‡€ƒ‡„ˆ„ˆ‚‡~†~†‚‡€„ˆ€„ˆƒ‡€„ˆ€ƒ‡‚†€ƒ‡€ƒ‡†‰†‰…ˆŒ†‰jjnjjnjjnjjn0+(0+(/*'/*'3-*3-*3-*4.+4.+3-*3-*4-*3-*3-*3-*3-*3-*3-*3-*4.+3,)3,)3,)3,)3-*3-*4.+3-*4.+3-*3-*4.+3-*4-*4.+3-*3,)3,)3,)3,)3,)3,)3,)3,)4-*3,)3,)3,)3,)4-*3,)4-*3,)3,)4,)3,)3-*3-*3-*3-*0+(/*'0+(/*'1*(1*(1*(1*(/*'/*'/*'/*'4-*4-*5.+4-*3,)3,)3,)3,)3-*3-*3-*3-*3,)4-*3,)3,)3,)4-*3,)4-*3,)3,)4-*3,)3-*3-*3-*3-*4.+4-*3-*3-*3,)3,)3,)3,)3,)4,)4-*3,)4.+3-*3-*3-*4.+4.+3-*3-*3,)3,)3,)3,)3,)3,)3,)4,)3,)3,)3,)3,)3-*3-*4.+3-*3,)3,)3,)3,)3,)3,)3,)3,)/*'/*'/*'/*'/*'/*'0+(/*'1*(2+)1*(1*(4.+4.+3-*3-*3,)3,)4-*3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)4-*3,)3,)4-*3,)3,)4-*3,)3,)3,)3,)3,)3,)4,)3,)3,)3,)3,)4,)3,)3-*3-*3-*3-*3,)3,)3,)3,)3,)3,)3,)3,)3,)4-*3,)3,)30.30.30.30.y|y|y|y|ƒ†Š‚…‰ƒ†Š‚…‰~‚†~…~…‚†‚…‰‚…‰‚…‰„ˆ€ƒ‡„ˆ„ˆ„ˆ~†~†~†~†ƒ‡ƒ‡ƒ‡€„ˆ€ƒ‡‚†€ƒ‡‚†…ˆŒ†‰†‰…ˆŒkkojjnkkojjn/*'/*'/*'/*'3-*3-*4.+3-*3-*3-*3-*3-*3-*3-*3-*4.+3-*3-*3-*3-*3,)4-*3,)4-*3-*3-*4.+3-*3-*4-*4.+4-*3-*3-*3-*3-*3,)3,)3,)3,)3,)3,)3,)4-*4-*3,)3,)3,)3,)4-*3,)4-*3,)3,)3,)4,)3-*3-*3-*3-*/*'/*'/*'/*'1*(1*(1*(2+)/*'/*'/*'0+(4-*4-*4-*4-*3,)4-*3,)4-*3-*3-*3-*3-*3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)4-*3-*3-*3-*3-*4.+3-*3-*4.+4-*3,)3,)3,)3,)3,)3,)4-*3-*3-*3-*3-*3-*3-*3-*3-*3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)4.+4.+3-*3-*3,)4,)3,)4-*3,)3,)3,)3,)/*'/*'/*'/*'/*'/*'/*'/*'1*(2*(1*(1*(4-*3-*3-*3-*3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)3,)4-*3,)3,)3,)4-*3,)3,)4-*3,)3,)3,)3,)4-*3,)4-*3,)3,)3,)3,)3,)3,)3,)3-*3-*3-*3-*3,)3,)3,)3,)3,)4-*3,)3,)3,)3,)3,)3,)41/30.30.41.x{~y|y|x{~‚…‰ƒ†Šƒ†Šƒ†Š‚†‚†~…~…‚…‰„ˆ„ˆ„ˆ„ˆ€ƒ‡„ˆ€ƒ‡~…~‚†~…~…}„~€…}„}„‚†‚†‚†‚†„‡Œƒ†‹ƒ†‹„‡Œjjnkkojjnkko$ $ $ $ $"$"$"$")'&(&%(&%(&%#$"#$"#$"#$"%#!%#!%#!%#!)*')*'*+()*'*,'*,'*,'*,'%'%%'%%'%%'%((%''$''$''$*.(*.(*.(*.(*,)*,)*,)*,)+-(*,'*,'*,'()&()&)*'()&(.((.()/)(.((/+(/+(/+(/+%)&%)&&*'%)&-(%-(%-(%-(%%)&%*&%)&%)&(/+)0,(/+(/+*0**0**0*+1+()&)*')*'()&%'%&(&&(&%'%*.(*.(*.(*.(*.(*.(*.(*.(%&#%&#%&#%&#%'%%'%%'%%'%+1+*0**0**0*-0,-0,-0,-0,''$''$''$''$%'%%'%%'%%'%(.()/)(.((.()/)(.()/)(.(%'%%'%%'%%'%%'%%'%%'%&(&(/+(/+(/+(/+*1/*1/*1/*1/)*'()&()&()&,'$+&#+&#+&#&*(&*(&*(&*()-,)-,)-,)-,&,*&,*&,*&-+()&()&()&()&*.,+/-+/-*.,),+),+),+),+*+*+,+*+**+*&$#%#"%#"%#"&,*&,*&,*&,*"+%"+%#,&"+%"+%#,&"+%"+%!"!"!"!")!( ( ( ( ( ( ( ))())(**)**){~z}€{~z}€ƒ‡Š‚†‰ƒ‡Šƒ‡Š€ƒ‡‚†€ƒ‡‚†€ƒ‡€ƒ‡‚†€ƒ‡‚†€ƒ‡€ƒ‡ƒ‡~…~…‚†‚†~€…~€…}…~€…~…~…~…‚†ƒ†‹„‡Œ„‡Œ„‡Œjjnjjnkkokko$ $ $ %! $"$"$"$"(&%(&%(&%)&%#$"#$"#$"#$"%#!&$"%#!%#!)*'*+')*')*'*,'+-(*,'*,'&(&%'%%'%%'%''$''$((%''$*.(*.(*.(*.(*,)*,)*,)*,)*,'*,'*,'*,'()&()&()&()&(.((.((.((.((/+)0,(/+(/+&*'%)&%)&&*'-(%-(%-(%-(%%)&%)&%)&%)&(/+(/+)0,(/++1+*0**0**0*()&()&()&()&%'%%'%%'%%'%*.(*.(*.(*.(*.(+/)*.(*.(%&#%&#&'$%&#&(&%'%%'%%'%+1+*1**0**0*-0,-0,-0,-0,''$''$((%''$%'%%'%%'%%'%(.((.()/)(.((.((.()/)(.(%'%%'%%'%%'%%'%%'%%'%%'%(/+(/+(/+(/+*1/*1/*1/*1/()&()&()&()&+&#,'$+&#,'$'+)&*(&*(&*()-,)-,)-,)-,'-+&,*&,*&,*()&()&()&)*'+/-+/-*.,+/-*-,),+),+),+*+**+**+**+*%#"%#"%#"%#"&,*&,*&,*&,*"+%"+%"+%"+%"+%"+%#,&"+%!"!""# !"( ) ( )!( ( ( ( ))())())())(z}€z}€{~z}€ƒ‡Šƒ‡Š‚†‰ƒ‡Š‚†€ƒ‡‚†€ƒ‡€ƒ‡‚†‚†‚†€ƒ‡€ƒ‡€ƒ‡€ƒ‡~…‚†~…‚†}„}„~€…~€…‚†~…‚†~…ƒ†‹ƒ†‹ƒ†‹„‡Œjjnjjnjjnjjn$ $ $ $ $"$"$"$"(&%(&%(&%(&%$%##$"#$"#$"%#!%#!%#!&$")*')*')*')*'+-(*,'*,'*,'%'%%'%%'%%'%''$((%''$''$*.(*.(*.(*.(+-**,)+-**,)*,'*,'*,'+-(()&()&()&()&(.((.()/)(.((/+)0,(/+(/+&*'%)&%)&%)&-(%.)&-(%-(%%)&%)&%)&%)&(/+)0,(/+(/+*0**0**0**0*()&)*'()&()&%'%%'%%'%%'%*.(+/)*.(*.(*.(*.(*.(*.(%&#%&#&'$&'$&(&%'%%'%%'%*0**0**0*+1+-0,.1--0,.1-((%''$''$((%%'%%'%%'%%'%(.((.()/)(.((.()/)(.((.(%'%%'%%'%%'%%'%%'%%'%%'%(/+(/+(/+(/+*1/*1/*1/*1/()&()&()&()&+&#+&#,'$,&#&*(&*(&*(&*()-,)-,)-,)-,&,*&,*&,*&,*)*'()&)*'()&*.,+/-*.,*.,),+),+),+),+*+**+*+,+*+*%#"&$#%#"&$#&,*&,*&,*&,*"+%#,&"+%"+%"+%",%"+%"+%!"!"!"!"( ( ) ( ( ( ( ( **)))())())(z}€{~{~{~ƒ‡Š‚†‰ƒ‡Šƒ‡Š€ƒ‡‚†€ƒ‡‚†‚†‚†€ƒ‡‚†‚†‚†€ƒ‡€ƒ‡~…‚†~…~…~€…}„~€…~€…~…‚†‚†~…„‡Œ„‡Œƒ†‹ƒ†‹jjnkkokkokko$ $ $ $ $"$"$"$"(&%(&%(&%(&%$%##$"#$"#$"%#!&$"%#!%#!)*')*')*')*'*,'*,'*,'*,'%'%%'%%'%%'%''$''$''$''$*.(*.(*.(*.(*,)*,)+-**,)+-(*,'+-'*,'()&()&)*&()&(.((.((.((.((/+)0,(/+(/+%)&%)&%)&%)&-(%-(%-(%-(%%*&%)&%)&%)&(/+(/+(/+(/+*0**0**0*+1+)*'()&()&()&%'%%'%%'%%'%*.(*.(*.(*.(*.(+/)*.(*.(%&#%&#%&#%&#%'%%'%%'%&(&*0**0**0**0*-0,-0,-0,-0,''$''$''$((%%'%%'%%'%%'%(.((.((.()/)(.((.((.((.(%'%%'%%'%%'%%'%%'%%'%%'%(/+(/+(/+(/+*2/*1/*1/*1/)*'()&)*'()&+&#+&#+&#,'$&*(&*(&*(&*(*.-)-,)-,)-,&,*&,*&,*&,*)*'()&)*'()&+/-*.,+/-*.,),+),+),+),+*+**+**+**+*%#"&$#%#"&$#&,*&,*&,*&,*"+%"+%"+%"+%#,&"+%"+%"+%"# !"!"!"( ( ( ( ( ( )!( ))())())())({~z}€z}€{~ƒ‡Šƒ‡Šƒ‡Š‚†‰‚†‚†‚†‚†€ƒ‡‚†€ƒ‡‚†‚†‚†€ƒ‡‚†‚†~…~…~…~…~…‚†~…~€…}„}„~€…‚…‰„ˆ„ˆ‚…‰kkojjnjjnjjn$! %"!$! $! $ $ $ $ ''!(("''!''!%#!%#!&$"%#!%#!%#!&$"%#!))&((%((%((%*+%)*%)*%)*%''$''$''$((%((%((%))&((%*.(*.(*.(*.(*.(*.(*.(*.(*.(*.(*.(*.(**'**'**'++(*.(*.(*.(*.(+/)*.(+/)*.(%'%%'%%'%%'%,&#-'$,&#,&#%)&%)&&*'%)&*0**0**0**0*-0,.1--0,-0,**'**'++(**'%'%&(&%'%%'%*,'+-(*,'+-'*.(*.(+/)*.(%&!%&!%&!%&!''$''$''$((%*.(*.(*.(*.(-.+-.+-.+-.+''$''$''$''$%'%%'%%'%%'%*.(+/)*.(*.((.((.((.()/)))&((%((%((%%'%&(&%'%%'%*0**0*+1+*0**0**0**0**0*((%((%((%((%)%$)%$)%$*&%&*(&*('+)&*((/+)0,(/+(/+)-*)-*)-*(,))*()*()*(*+)+/-+/-+/-+/-*-,*-,*-,+.-*-,*-,*-,+.-%$#%$#%$#%$#(,)(,))-*)-*$+($+($+($+("+%"+%#,&#,&!"!"!"!"!$!!$!!$!!$!( ( )!( *))+***))*))y|y|y|x{~€ƒˆ€ƒˆ„‰„‰€ƒ‡€ƒ‡€ƒ‡€ƒ‡‚…‰„ˆ„ˆ‚…‰‚…‰„ˆ„ˆ‚…‰~…‚†‚†‚†~…~…‚†~…}„~€…~€…~€…‚…‰„ˆ„ˆ„ˆjjnjjnkkojjn%"!%"!$! $! $ $ $ $ ''!''!''!''!%#!%#!%#!%#!%#!%#!%#!&$"((%((%((%))&)*%*+&)*%)*%''$''$''$''$((%((%((%((%*.(*.(*.(*.(*.(+/)*.(*.(*.(*.(*.(*			smokeZ=(object->zSurface>>12)-128;
							
							yAngle+=rand()&1023;

							Boulder_AddBoulder(smokeX,smokeY,smokeZ,
								(rand()&255)+128, yAngle, (((rand()&127)+128)<<9), -(((rand()&15)+50)<<12), 100, 0);

							//rockGen=(rand()&31)+16;

							Boulder_AddSmoke(smokeX+RR(63), smokeY+RR(63), smokeZ,
								 ((800+(rand()&511))<<2), 0, -(6+(rand()&3))<<12, ((128+(rand()&63))<<12), ToFIXED(-3.0), 255, 255, 255);

						}

					/* check for block destruction */

						if (drillBlock->damage<=0)
						{
							int 	yAngle=object->angleY+2048-512;

							yAngle+=rand()&1023;
							Lego_DigBlock(legoGlobs.currLevel,drillX,drillY,FALSE);
							Sfx_PlayEffect(SFX_SAMPLE_ROCKFALL,50+(rand()&3),127);
							Boulder_CreateRockFall(drillX,drillY,yAngle);
							Camera_SetShakeTimer(25);
						}
					}
				}
			}
		}
		else
		{
			craft->drillSpeed-=craft->drillSpeedDelta;
			if (craft->drillSpeed<0)
				craft->drillSpeed=0;
		}

		if (rockType!=Lego_SurfaceType_floor)
			rockType+=2;

	}


/* this stuff needs a general purpose handler, but for now we will fudge it */

	switch (craft->typeID)
	{

		case	TR_CRAFT_LARGE_DIGGER:
		{

		/* the wheels */
			Container_SetRotationIndex(craft->refCont,17,-craft->wheelSpin,(craft->turnRate<<2),0);
			Container_SetRotationIndex(craft->refCont,19,craft->wheelSpin,(craft->turnRate<<2),0);
			Container_SetRotationIndex(craft->refCont,21,craft->wheelSpin,-(craft->turnRate<<1),0);
			Container_SetRotationIndex(craft->refCont,23,-craft->wheelSpin,-(craft->turnRate<<1),0);

		/* the drills */

			craft->drillPos+=craft->drillSpeed;
			Container_SetRotationIndex(craft->refCont,5,0,0,craft->drillPos<<3);


		/* hide front drill and one of the lasers */

			CONCEAL_HMD_BLOCK(craft->refCont,8);
			CONCEAL_HMD_BLOCK(craft->refCont,6);


		/* drill SFX */

			Craft_SetVolumeAndFrequencyDrillSfx(object, SFX_SAMPLE_VE_DRILL, 70, -((craft->drillSpeedCap-craft->drillSpeed)>>3),rockType);

			break;
		}


		case	TR_CRAFT_BIG_LASER:
		{

		/* front wheels */
			Container_SetRotationIndex(craft->refCont,15,-craft->wheelSpin,(craft->turnRate<<2),0);
			Container_SetRotationIndex(craft->refCont,17,-craft->wheelSpin,(craft->turnRate<<2),0);

		/* middle, don't steer */
			Container_SetRotationIndex(craft->refCont,25,-craft->wheelSpin,0,0);
			Container_SetRotationIndex(craft->refCont,19,-craft->wheelSpin,0,0);
		
		/* rear wheels, half steer */
			Container_SetRotationIndex(craft->refCont,23,-craft->wheelSpin,-(craft->turnRate<<1),0);
			Container_SetRotationIndex(craft->refCont,21,-craft->wheelSpin,-(craft->turnRate<<1),0);


			break;
		}


		case	TR_CRAFT_BULLDOZER:
		{

			static int fb=35;

		/* front wheels */
			Container_SetRotationIndex(craft->refCont,16,-craft->wheelSpin,(craft->turnRate<<2),0);
			Container_SetRotationIndex(craft->refCont,18,-craft->wheelSpin,(craft->turnRate<<2),0);

		/* rear wheels, no steering */
			Container_SetRotationIndex(craft->refCont,22,-craft->wheelSpin,0,0);
			Container_SetRotationIndex(craft->refCont,20,-craft->wheelSpin,0,0);



			CONCEAL_HMD_BLOCK(craft->refCont,10);		/* the blanks under the buckets */
			break;
		}

		case	TR_CRAFT_SMALL_TRUCK:
		{

		/* turn off driver if not controlled */

			if (craft->controlledBy==-1)
				CONCEAL_HMD_BLOCK(craft->refCont,14);
			else
				REVEAL_HMD_BLOCK(craft->refCont,14);


		/* front wheels */
			Container_SetRotationIndex(craft->refCont,20,-craft->wheelSpin,(craft->turnRate<<2),0);
			Container_SetRotationIndex(craft->refCont,22,-craft->wheelSpin,(craft->turnRate<<2),0);

		/* rear wheels, no steering */
			Container_SetRotationIndex(craft->refCont,26,-craft->wheelSpin,0,0);
			Container_SetRotationIndex(craft->refCont,24,-craft->wheelSpin,0,0);

		/* turn off unwanted parts */

			//HMD_SetBlock(Container_Mesh_GetModel(craft->refCont),4,0);		/* middle bucket */
			CONCEAL_HMD_BLOCK(craft->refCont,4);
			break;


		}


		case	TR_CRAFT_SMALL_LASER:
		{

		/* turn off driver if not controlled */

			if (craft->controlledBy==-1)
				CONCEAL_HMD_BLOCK(craft->refCont,8);
			else
				REVEAL_HMD_BLOCK(craft->refCont,8);

		/* front wheels */
			Container_SetRotationIndex(craft->refCont,14,-craft->wheelSpin,(craft->turnRate<<2),0);
			Container_SetRotationIndex(craft->refCont,16,-craft->wheelSpin,(craft->turnRate<<2),0);

		/* middle, don't steer */
			Container_SetRotationIndex(craft->refCont,24,-craft->wheelSpin,0,0);
			Container_SetRotationIndex(craft->refCont,18,-craft->wheelSpin,0,0);
		
		/* rear wheels, half steer */
			Container_SetRotationIndex(craft->refCont,22,-craft->wheelSpin,-(craft->turnRate<<1),0);
			Container_SetRotationIndex(craft->refCont,20,-craft->wheelSpin,-(craft->turnRate<<1),0);

			break;
		}


		case	TR_CRAFT_SMALL_DIGGER:
		{
			int 	offset;

			craft->drillPos+=craft->drillSpeed;
			offset=rsin(craft->drillPos<<1)>>6;


		/* turn off driver if not controlled */

			if (craft->controlledBy==-1)
				CONCEAL_HMD_BLOCK(craft->refCont,15);
			else
				REVEAL_HMD_BLOCK(craft->refCont,15);

		/* front wheels */
			Container_SetRotationIndex(craft->refCont,19,-craft->wheelSpin,(craft->turnRate<<2),0);
			Container_SetRotationIndex(craft->refCont,21,-craft->wheelSpin,(craft->turnRate<<2),0);

		/* middle, don't steer */
			Container_SetRotationIndex(craft->refCont,27,-craft->wheelSpin,0,0);
			Container_SetRotationIndex(craft->refCont,29,-craft->wheelSpin,0,0);
		
		/* rear wheels, half steer */
			Container_SetRotationIndex(craft->refCont,26,-craft->wheelSpin,-(craft->turnRate<<1),0);
			Container_SetRotationIndex(craft->refCont,23,-craft->wheelSpin,-(craft->turnRate<<1),0);


			Craft_SetVolumeAndFrequencyDrillSfx(object, SFX_SAMPLE_VE_DRILL, 60, -((craft->drillSpeedCap-craft->drillSpeed)>>3),rockType);

		/* set position of drills */

			Container_SetPositionIndex(craft->refCont,14,0,0,50+offset);
			Container_SetPositionIndex(craft->refCont,13,0,0,50-offset);
			Container_SetPositionIndex(craft->refCont,12,0,0,50-offset);


			break;
		}

	}

	Craft_SetVolumeAndFrequencyEngineSfx(object,SFX_SAMPLE_ENGINE,craft->engineBaseFrequency,craft->engineOffsetFrequency);

	return	TRUE;

}











#define	CARRY_LENGTH								(256)
#define	CARRY_LENGTH_FOR_MINIFIGURE			(32)



/*
	-------------------------------------------------------------------------




	craft handler for air units




	-------------------------------------------------------------------------
*/	
BOOL	Craft_UpdateAirCraft(lpPLAYER player, lpOBJECT object, int time)
{
	lpCRAFT 			craft=object->objectData;
	VECTOR			v1,v2,v3;
	int				nextX,nextY,nextZ;
	int				xd,yd;
	int				turnSpeed;
	int				old_speed;
	int				turning=FALSE,inAir=FALSE;
	lpCONTROL 		control;
	lpLego_Block	block;

	unsigned char	*padBuffer;
	int				padType;

	REAL				turnScale=0;
	REAL				moveScale;
	int				heightDelta;
	int				hoverAlt;
	int				strafeRate=0;
	int				absDelta;


	lpOBJECT			carryObject;
	lpCRAFT			carryObjectCraft;


	if (craft->refCont->renderFlags & RENDER_FLAGS_CLIPPED)
	{
		
		if (++craft->sleepTimer>10)
			return FALSE;			
	}
	else
		craft->sleepTimer=0;

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
			
		turnScale=(padBuffer[LEFT_STICK_HORIZONTAL]<<5)-((127<<5)+16);


/* prevent movement if winching not complete */

		if ((craft->carryObject && craft->carryHeight>craft->carryHeightTarget) || (!craft->flightFlag))
		{
			CLEAR_EVENT_IMMEDIATE(control,CONTROL_TURN_LEFT);
			CLEAR_EVENT_IMMEDIATE(control,CONTROL_TURN_RIGHT);
			CLEAR_EVENT_IMMEDIATE(control,CONTROL_FORWARD);
			CLEAR_EVENT_IMMEDIATE(control,CONTROL_REVERSE);
			moveScale=0;
			turnScale=0;
		}
	}
	else
	{
		control=nullControlSet;		/* uncontrolled craft need to idle, but they don't want input */
		padType=4;
	}


	carryObject=NULL;
	if (!craft->carryObject)
	{
		int	absSpeed=object->speed;

		if (absSpeed<0)
			absSpeed=-absSpeed;
		/* craft must be at rest before we can winch */

		if ((craft->flags & CF_CAN_LIFT) && (absSpeed<ToFIXED(10.0)))
		{
			carryObject=Craft_GetLiftableCraft(object,object->x>>12,object->y>>12);
			if (carryObject)
			{
				player->lastTarget=carryObject;

				if (player->reticuleAlpha<224)
					player->reticuleAlpha+=8;

				Craft_DrawLiftReticule(carryObject,player);
			}
		}
		else
		{
			if (player->reticuleAlpha>0 && player->lastTarget)
			{
				Craft_DrawLiftReticule(player->lastTarget,player);
				player->reticuleAlpha-=8;
			}
		}
	}


/* take-off/land toggle */

	if (!craft->flightFlag)		/* on the ground */
	{
		if (PAD_EVENT(control,CONTROL_ACTIVATION_TOGGLE))
		{
			CLEAR_EVENT_RELEASE(control,CONTROL_ACTIVATION_TOGGLE);
			craft->flightFlag=TRUE;
		}		
	}
	else		/* in the air */
	{
		/* need to check if landing is allowed - ground should be roughly flat? */
		if (PAD_EVENT(control,CONTROL_ACTIVATION_TOGGLE))
		{
			CLEAR_EVENT_RELEASE(control,CONTROL_ACTIVATION_TOGGLE);

			if (carryObject)
			{
				craft->carryObject=carryObject;
				craft->carryHeight=(carryObject->z-object->z)>>12;
				craft->carryCycle=0;
				craft->carryScale=0;				

				if (carryObject->class==OC_CRAFT)
				{
					carryObjectCraft=carryObject->objectData;
					carryObjectCraft->flags|=CF_LIFTED;				/* mark as lifted */
					craft->carryHeightTarget=CARRY_LENGTH;
				}
				else	/* minifigure */
				{
					craft->carryHeightTarget=CARRY_LENGTH_FOR_MINIFIGURE;
				}
			}
			else
			{
				if (craft->carryObject)
				{
					lpOBJECT		carriedObject=craft->carryObject;

					/* release the object carried (but not minifigures) */

					if (carriedObject->class==OC_CRAFT)
					{
						carryObjectCraft=carriedObject->objectData;
						carryObjectCraft->flags&=~CF_LIFTED;
						carryObjectCraft->zDelta=0;
				
						carriedObject->zSpeed=0;
						carriedObject->angleY=0;
						craft->carryObject=NULL;
					}
				}
				else	/* attempting to land, so validate landing position */
				{
					/* can't land until at rest and valid position for minifigure */

					if ((object->speed==0) && (Player_SetMinifigureToCraftPosition(player,512,FALSE)))
					{
						craft->flightFlag=FALSE;
					}
					else
					{
						/* --- beep for can't land here? --- */
					}
				}
			}
		}
	}


	craft->hoverHeightTarget=object->zSurface;
	if (craft->flightFlag)
	{
		craft->hoverHeightTarget-=craft->altitudeReference;
		craft->engineVolume+=HELI_VOLUME_DELTA;
		if (craft->engineVolume>127)
			craft->engineVolume=127;
	}
	else
	{
		craft->engineVolume-=HELI_VOLUME_DELTA;
		if (craft->engineVolume<0)
			craft->engineVolume=0;
	}
