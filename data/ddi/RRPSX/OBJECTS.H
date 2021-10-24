
//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// object structures For <LEGO Rock Raiders>
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#ifndef	__OBJECTS_H

#define MAX_MINIFIGURES				4
#define	MAX_CRAFT						16
#define	MAX_ROCKMONSTERS				8
#define	MAX_ROCKWHALES					2
#define	MAX_SPRITECREATURES			30				//scorpion/spiders/snakes
#define	MAX_CREATURES					(MAX_ROCKMONSTERS+MAX_ROCKWHALES+MAX_SPRITECREATURES)

#define	MAX_CRATEPICKUPS				5
#define	MAX_PICKUPS						15		/* sprite pickups - crystal,ammo, etc., */

#define	MINIFIGURE_START				(0)
#define	CRAFT_LIST_START				(MAX_MINIFIGURES)
#define	ROCKMONSTER_START				(CRAFT_LIST_START+MAX_CRAFT)
#define	ROCKWHALE_START				(ROCKMONSTER_START+MAX_ROCKMONSTERS)
#define	SPRITECREATURE_START			(ROCKWHALE_START+MAX_ROCKWHALES)
#define	PICKUP_START					(SPRITECREATURE_START+MAX_SPRITECREATURES)
#define	SPRITEPICKUP_START			(PICKUP_START+MAX_CRATEPICKUPS)
#define	MAX_OBJECTS						(SPRITEPICKUP_START+MAX_PICKUPS)


#define	MAX_SPRITE_PICKUP_TYPES		(4)

typedef struct CRAFT
{
	int				typeID;
	int				id;
	int				controlledBy;
	int				flags;

	int				zDeltaDelta;
	int				zDelta;
	ANGLE				wheelSpin;

	int				turnRateCap;
	int				turnRate;
	int				turnRateDelta;

	int				accelDeltaForward;
	int				accelDeltaBackward;
	int				decelDelta;
	int				forwardSpeedCap;
	int				backwardSpeedCap;

	int				forwardSpeedCapScaled;
	int				backwardSpeedCapScaled;

	int				turnForceMoveDelta;
	int				turnForceMoveCap;
	int				mass;


	int				drillSfxVoice;			/* some craft may require a looping voice */
	int				drillSpeed;
	int				drillSpeedCap;
	int				drillSpeedDelta;
	int				drillPos;
	int				maxRockType;			/* highest level of rock that craft can drill */
	int				drillRadius;
	int				drillAngleOffset;

/* angle smoothing */
	int				targetXr;
	int				targetZr;
	int				currentXr;
	int				currentZr;

	int				engineVolume;			/* applies to both types */
	int				engineBaseFrequency;
	int				engineOffsetFrequency;

/* aircraft stuff */

	int				loopingSfxVoice;
	int				flightFlag;
	int				altitudeReference;
	int				rotorRotation;
	int				rotorSpeed;
	int				hoverHeight;
	int				hoverHeightTarget;
	int				climbRate;
	int				radius;
	int				spread;

	int				carryHeightTarget;
	int				carryHeight;
	int				carryOffsetX;
	int				carryOffsetY;
	int				carrySwing;
	int				carryCycle;
	int				carryScale;

	int				scoopFilled;

	void				*carryObject;		/* if non-NULL, points to object being carried */

	int				sleepTimer;

	BOOL				(*craftHandler)(void *player, void *object, int time);

	lpContainer		refCont;
	lpContainer		shadowCont;
	int				shadowType;
	int				shadowW;
	int				shadowH;

}	CRAFT, *lpCRAFT;






typedef struct MINIFIGURE
{
	int				id;
	int				controlledBy;
	int				flags;
	int				travel;
	int				lastTravel;
	int				activity;
	int				drillSfxVoice;
	int				drillSpeed;
	int				maxRockType;			/* maxiumum surface type this minifigure can drill */
	int				health;
	int				dynamiteSticks;
	int				pusherGunAmmo;

	lpContainer		refCont;		

} MINIFIGURE, *lpMINIFIGURE;


typedef struct PICKUP
{
	int				animSpeed;
	int				clipTime;
	int				errSomeStuffHere;

}	PICKUP, *lpPICKUP;


enum
{
	OF_SLEEPING,
};

typedef struct obj_st
{
	int			class;
	int			type;
	int			x;
	int			y;
	int			z;
	int			zSurface;
	int			angleY;
	int			targetAngleY;
	int			speed;
	int			zSpeed;
	int			collisionRadiusProduct;
	int			activationRadiusProduct;
	int			collisionRadius;
	int			activationRadius;
	int			flags;
	lpContainer	cont;
	void			*objectData;		/* pointer to specific data for object class */

} OBJECT, *lpOBJECT;


typedef struct creature_st
{
	short						type;
	short						activity;
	short						clipTime;			/* cycle count of clipped time */
	short						directionTime;
	short						flags;
	int						id;
	int						health;
	int						lastDirChange;
	int						targetTime;			/* time to spend chasing a target */
	int						moveSteps;

	lpContainer				refCont;		
	void						*target;				/* pointer to craft or minifigure */
	void						(*handler)(struct obj_st *creatureObject, int time);

} CREATURE, *lpCREATURE;




typedef enum
{
	PLAYER_FLAG_COMBINE_ANALOGUE	=	1,			/* if set analogue control is combined on left stick, else left is direction right is speed */
	PLAYER_FLAG_MINIFIGURE_ACTIVE,				/* if set minifigure is active, else craft is active */
	PLAYER_FLAG_,

} PlayerFlags;

typedef enum
{
	PLAYER_ONE,
	PLAYER_TWO,

} PLAYERS;



typedef	struct player_st
{
	int					id;
	PlayerFlags			flags;
	lpCRAFT				craft;
	lpOBJECT				craftObject;
	lpMINIFIGURE		minifigure;
	lpOBJECT				minifigureObject;
	CONTROL				controlSet[MAX_CONTROLS];
	unsigned char		padBuffer[34];

/* other stuff */

	int					reticulePulseIndex;
	int					reticuleAlpha;
	lpOBJECT				lastTarget;

	int					score;
	int					controllerConnected;

}	PLAYER, *lpPLAYER;




/*
	objects are handled with a common structure for position
	direction, and speed, and a private section for specific
	data pertaining to the object class.
*/
typedef struct objectGlobs_st
{
	int						numPlayers;
	PLAYER					playerList[2];
	OBJECT					objectList[MAX_OBJECTS];

/* data for specific classes */

/* -------------------------------------------------------------------------------------------------------------------*/
/* creatures 																																			  */
/* -------------------------------------------------------------------------------------------------------------------*/

	CREATURE					creatureList[MAX_CREATURES];

	lpSPR_ACTIVITY_SET	creatureActivitySet[TR_MAX_CREATURE_TYPES];		/* not all creature will have these set */
	lpContainer				rockmonsterRefCont;										/* reference containers to clone from */
	lpContainer				rockwhaleRefCont;


/* cached pointers to avoid repetitive lookups */

	lpOBJECT					playerMinifigureObject[2];				/* these are set if player is active, and on foot, else NULL */
	lpOBJECT					playerCraftObject[2];					/* these are set if player is active and in craft */

#ifndef __CDVERSION
	int						activeCreatures[TR_MAX_CREATURE_TYPES];
#endif

/* -------------------------------------------------------------------------------------------------------------------*/


/* -------------------------------------------------------------------------------------------------------------------*/
/* craft 																																				  */
/* -------------------------------------------------------------------------------------------------------------------*/

	lpSPR_ACTIVITY_SET	craftShadowSet;
	CRAFT						craftList[MAX_CRAFT];
	lpContainer				craftContList[TR_CRAFT_MAX_TYPES];			/* containers for the HMD models, NULL will indicate not loaded for this level */
	int						numCraft;

/* -------------------------------------------------------------------------------------------------------------------*/


/* -------------------------------------------------------------------------------------------------------------------*/
/* minifigures 																																		  */
/* -------------------------------------------------------------------------------------------------------------------*/

	MINIFIGURE				minifigureList[MAX_MINIFIGURES];
	int						numMinifigures;
	lpSPR_ACTIVITY_SET	minifigureActivitySet;
/* -------------------------------------------------------------------------------------------------------------------*/



/* -------------------------------------------------------------------------------------------------------------------*/
/* pickups 																																		  */
/* -------------------------------------------------------------------------------------------------------------------*/

	PICKUP					pickupList[MAX_PICKUPS];
	lpSPRITE_SET			pickupSpriteSet[MAX_SPRITE_PICKUP_TYPES];
	lpContainer				crateRefCont;
/* -------------------------------------------------------------------------------------------------------------------*/

} OBJECT_GLOBS;




/* the craft data setup structure */
typedef struct craft_setup_st
{
	char			modelName[16];
	int			modelScale;
	BOOL			(*craftHandler)(lpPLAYER player, lpOBJECT object, int time);
	int			accelDeltaForward;
	int			accelDeltaBackward;
	int			decelDelta;
	int			forwardSpeedCap;
	int			backwardSpeedCap;
	int			turnRateDelta;
	int			turnRateCap;
	int			turnForceMoveDelta;
	int			turnForceMoveCap;
	int			cruisingaltitude;
	int			climbRate;
	int			mass;
	int			radius;
	int			spread;
	int			clipSize;

	int			collisionRadius;
	int			activationRadius;
	int			zDeltaDelta;

	int			engineBaseFrequency;
	int			engineOffsetFrequency;

	int			flags;
	int			drillSpeedDelta;
	int			drillSpeedCap;
	int			maxRockType;
	int			drillRadius;
	int			drillAngleOffset;
	int			shadowType;
	int			shadowW;
	int			shadowH;

}	CRAFT_SETUP, *lpCRAFT_SETUP;



extern OBJECT_GLOBS		objectGlobs;



void	Object_InitialiseLists(void);


#define	__OBJECTS_H

#endif
