//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// trigger Include For <LEGO [Rock Raiders]>
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#ifndef	__TRIGGER_H

typedef enum
{
	OC_CRAFT,
	OC_PICKUP,
	OC_CREATURE,
	OC_MINIFIGURE,
	OC_SYSTEM,

	OC_MAX_CLASS,

} OBJECT_CLASS;



typedef enum
{

/* ground */
	TR_CRAFT_LARGE_DIGGER,
	TR_CRAFT_BIG_LASER,
	TR_CRAFT_BULLDOZER,
	TR_CRAFT_SMALL_TRUCK,
	TR_CRAFT_SMALL_LASER,
	TR_CRAFT_SMALL_DIGGER,
/* air */
	TR_CRAFT_LARGE_HELICOPTER,
	TR_CRAFT_SMALL_HELICOPTER,
	TR_CRAFT_HOVERBOARD,
/* dumb */
	TR_CRAFT_CRATE,			/* not actually driveable, but handled like a craft */
	TR_CRAFT_SCOOP,			/* ditto */

	TR_CRAFT_MAX_TYPES,

}	CRAFT_TYPES;


typedef enum
{
	TR_PICKUP_FREEZER_AMMO,
	TR_PICKUP_PUSHER_AMMO,
	TR_PICKUP_DYNAMITE,
	TR_PICKUP_SUPER_DYNAMITE,
	TR_PICKUP_POWER_CRYSTAL,
	TR_PICKUP_BONUS_CRYSTAL,
	TR_PICKUP_FUEL,
	TR_PICKUP_CRATE,

	TR_PICKUP_MAX_TYPES,
	
} PICKUP_TYPES;


typedef enum
{
	TR_CREATURE_ROCKMONSTER,	
	TR_CREATURE_ROCKWHALE,	
	TR_CREATURE_SNAKE,
	TR_CREATURE_SPIDER,
	TR_CREATURE_SCORPION,

	TR_MAX_CREATURE_TYPES,

} CREATURE_TYPES;


/*
	these control the game
*/
typedef enum															// extra parameters
{

/* create */
	SYSTEM_CREATE_OBJECTIVE_AND_FLAG,							// [AND flag uid]
	SYSTEM_CREATE_OBJECTIVE_OR_FLAG,								// [OR flag uid]
	SYSTEM_CREATE_OBJECTIVE_COUNTER,								// [counter uid] [counter value]	
	SYSTEM_DISPLAY_MESSAGE,											// [message id] [time in seconds]

/* set */
	SYSTEM_INCREMENT_OBJECTIVE_COUNTER,							// [counter uid] [increment value]
	SYSTEM_SET_LEVEL_COMPLETED,									// [rating] i.e. there could be multiple win situations, this indicates rating
	SYSTEM_SET_LEVEL_FAILED,
	SYSTEM_SET_WIN_RATING_FOR_AND_COMPLETION,					// [rating]
	SYSTEM_SET_WIN_RATING_FOR_OR_COMPLETION,					// [rating]
	SYSTEM_SET_WIN_MESSAGE,											// [rating] [message id]
	SYSTEM_SET_LOSE_MESSAGE,										// [rating] [message id]

/* test and set */
	SYSTEM_SET_OBJECTIVE_AND_FLAG_WHEN_COUNTER_EQUALS,		// [AND flag uid] [counter uid] [counter value]
	SYSTEM_SET_OBJECTIVE_OR_FLAG_WHEN_COUNTER_EQUALS,		// [OR flag uid] [counter uid] [counter value]
	

} SYSTEM_TYPES;



/* trigger data definition macros */

#define	NO_POS									0,0,0,0
#define UNCONDITIONAL_SYSTEM_TRIGGER		TT_NO_CONDITION,0, 0,0,0,0
#define TRIGGER_LIST_END						-1,0, 0,0,0,0, 0,0,0, 0,0,0,0, 0,0,0,0, 0


/* unconditional system trigger definition macros */

#define	UST_CREATE_OBJECTIVE_AND_FLAG(flagID)														UNCONDITIONAL_SYSTEM_TRIGGER,OC_SYSTEM,SYSTEM_CREATE_OBJECTIVE_AND_FLAG, 0,flagID,0,0, 0,0,0,0, 0
#define	UST_CREATE_OBJECTIVE_OR_FLAG(flagID)														UNCONDITIONAL_SYSTEM_TRIGGER,OC_SYSTEM,SYSTEM_CREATE_OBJECTIVE_OR_FLAG, 0,flagID,0,0, 0,0,0,0, 0
#define	UST_CREATE_OBJECTIVE_COUNTER(counterID,initialValue)									UNCONDITIONAL_SYSTEM_TRIGGER,OC_SYSTEM,SYSTEM_CREATE_OBJECTIVE_COUNTER, 0,counterID,initialValue,0, 0,0,0,0, 0
#define	UST_DISPLAY_MESSAGE(messageID,displayTime)												UNCONDITIONAL_SYSTEM_TRIGGER,OC_SYSTEM,SYSTEM_DISPLAY_MESSAGE, 0,messageID,displayTime,0, 0,0,0,0, 0
#define	UST_INCREMENT_OBJECTIVE_COUNTER(counterID,incrementValue)							UNCONDITIONAL_SYSTEM_TRIGGER,OC_SYSTEM,SYSTEM_INCREMENT_OBJECTIVE_COUNTER, 0,counterID,incrementValue,0, 0,0,0,0, 0
#define	UST_SET_LEVEL_COMPLETED(rating)																UNCONDITIONAL_SYSTEM_TRIGGER,OC_SYSTEM,SYSTEM_SET_LEVEL_COMPLETED, 0,rating,0,0, 0,0,0,0, 0
#define	UST_SET_LEVEL_FAILED(rating)																	UNCONDITIONAL_SYSTEM_TRIGGER,OC_SYSTEM,SYSTEM_SET_LEVEL_FAILED, 0,rating,0,0, 0,0,0,0, 0
#define	UST_SET_WIN_RATING_FOR_AND_COMPLETION(rating)											UNCONDITIONAL_SYSTEM_TRIGGER,OC_SYSTEM,SYSTEM_SET_WIN_RATING_FOR_AND_COMPLETION, 0,rating,0,0, 0,0,0,0, 0
#define	UST_SET_WIN_RATING_FOR_OR_COMPLETION(rating)												UNCONDITIONAL_SYSTEM_TRIGGER,OC_SYSTEM,SYSTEM_SET_WIN_RATING_FOR_OR_COMPLETION, 0,rating,0,0, 0,0,0,0, 0
#define	UST_SET_WIN_MESSAGE(rating,messageID)														UNCONDITIONAL_SYSTEM_TRIGGER,OC_SYSTEM,SYSTEM_SET_WIN_MESSAGE, 0,rating,messageID,0, 0,0,0,0, 0
#define	UST_SET_LOSE_MESSAGE(rating,messageID)														UNCONDITIONAL_SYSTEM_TRIGGER,OC_SYSTEM,SYSTEM_SET_LOSE_MESSAGE, 0,rating,messageID,0, 0,0,0,0, 0
#define	UST_SET_OBJECTIVE_AND_FLAG_WHEN_COUNTER_EQUALS(flagID,counterID,value)			UNCONDITIONAL_SYSTEM_TRIGGER,OC_SYSTEM,SYSTEM_SET_OBJECTIVE_AND_FLAG_WHEN_COUNTER_EQUALS, 0,flagID,counterID,value, 0,0,0,0, 0
#define	UST_SET_OBJECTIVE_OR_FLAG_WHEN_COUNTER_EQUALS(flagID,counterID,value)			UNCONDITIONAL_SYSTEM_TRIGGER,OC_SYSTEM,SYSTEM_SET_OBJECTIVE_OR_FLAG_WHEN_COUNTER_EQUALS, 0,flagID,counterID,value, 0,0,0,0, 0


/* unconditional object creation triggers */
#define UOT_CREATE_OBJECT(class,type,x,y,rotation)										TT_NO_CONDITION,0, x,y,0,rotation, class,type,0, 0,0,0,0, 0,0,0,0, 0
#define UOT_CREATE_CRAFT(type,x,y,rotation)													TT_NO_CONDITION,0, x,y,0,rotation, OC_CRAFT,type,0, 0,0,0,0, 0,0,0,0, 0
#define UOT_CREATE_CREATURE(type,x,y,rotation)												TT_NO_CONDITION,0, x,y,0,rotation, OC_CREATURE,type,0, 0,0,0,0, 0,0,0,0, 0
#define UOT_CREATE_MINIFIGURE(x,y,rotation,id)												TT_NO_CONDITION,0, x,y,0,rotation, OC_MINIFIGURE,0,0, id,0,0,0, 0,0,0,0, 0

#define UOT_CREATE_CREATURE_FLAGS(type,x,y,rotation,flags)								TT_NO_CONDITION,0, x,y,0,rotation, OC_CREATURE,type,0, 0,0,0,0, 0,0,0,0, flags

#define UOT_CREATE_OBJECT_WITH_ID(class,type,x,y,rotation,id)							TT_NO_CONDITION,0, x,y,0,rotation, class,type,id, 0,0,0,0, 0,0,0,0, 0
#define UOT_CREATE_CRAFT_WITH_ID(type,x,y,rotation,id)									TT_NO_CONDITION,0, x,y,0,rotation, OC_CRAFT,type,id, 0,0,0,0, 0,0,0,0, 0
#define UOT_CREATE_CREATURE_WITH_ID(type,x,y,rotation,id)								TT_NO_CONDITION,0, x,y,0,rotation, OC_CREATURE,type,id, 0,0,0,0, 0,0,0,0, 0
#define UOT_CREATE_MINIFIGURE_WITH_ID(x,y,rotation,num,id)								TT_NO_CONDITION,0, x,y,0,rotation, OC_MINIFIGURE,0,id, num,0,0,0, 0,0,0,0, 0


#define UOT_CREATE_OBJECT_AT_TIME(time,class,type,x,y,rotation)						TT_AT_TIME,time, x,y,0,rotation, class,type,0, 0,0,0,0, 0,0,0,0, 0
#define UOT_CREATE_CRAFT_AT_TIME(time,type,x,y,rotation)								TT_AT_TIME,time, x,y,0,rotation, OC_CRAFT,type,0, 0,0,0,0, 0,0,0,0, 0
#define UOT_CREATE_CREATURE_AT_TIME(time,type,x,y,rotation)							TT_AT_TIME,time, x,y,0,rotation, OC_CREATURE,type,0, 0,0,0,0, 0,0,0,0, 0
#define UOT_CREATE_MINIFIGURE_AT_TIME(time,x,y,rotation,id)							TT_AT_TIME,time, x,y,0,rotation, OC_MINIFIGURE,0,0, id,0,0,0, 0,0,0,0, 0

#define UOT_CREATE_OBJECT_AT_TIME_WITH_ID(time,class,type,x,y,rotation,id)		TT_AT_TIME,time, x,y,0,rotation, class,type,id, 0,0,0,0, 0,0,0,0, 0
#define UOT_CREATE_CRAFT_AT_TIME_WITH_ID(time,type,x,y,rotation,id)					TT_AT_TIME,time, x,y,0,rotation, OC_CRAFT,type,id, 0,0,0,0, 0,0,0,0, 0
#define UOT_CREATE_CREATURE_AT_TIME_WITH_ID(time,type,x,y,rotation,id)				TT_AT_TIME,time, x,y,0,rotation, OC_CREATURE,type,id, 0,0,0,0, 0,0,0,0, 0
#define UOT_CREATE_MINIFIGURE_AT_TIME_WITH_ID(time,x,y,rotation,num,id)			TT_AT_TIME,time, x,y,0,rotation, OC_MINIFIGURE,0,id, num,0,0,0, 0,0,0,0, 0




typedef enum										/* extra parameters			*/
{
	TT_TRIGGERED=-2,
	TT_END_OF_LIST,

	TT_NO_CONDITION,								// NONE
	TT_AT_TIME,										// elapsed time (seconds?)

/* flag tests */

	TT_OBJECTIVE_AND_FLAG_SET					// AND flag number,
	TT_OBJECTIVE_OR_FLAG_SET					// OR flag number,
	TT_OBJECTIVE_COUNTER_EQUALS_VALUE		// counter number,value

/* object destruction */

	TT_CREATURE_OF_ID_DESTROYED,				// object ID (unique)
	TT_CREATURE_OF_TYPE_DESTROYED,			// creature type

/* object collection */

	TT_OBJECT_OF_ID_COLLECTED,					// object ID (unique)
	TT_OBJECT_OF_TYPE_COLLECTED,				// pickup type

/* object at location */

	TT_MINIFIGURE_ARRIVED,						// at block x/y
	TT_CRAFT_ARRIVED,								// [id] at block x/y
	TT_CREATURE_ARRIVED,							// at block x/y

/* block attached triggers */

	TT_BLOCK_DUG,									// at block x/y
	TT_BLOCK_IS_ROCK,								// block x/y
	TT_BLOCK_IS_LAVA,								// block x,y	
	TT_BLOCK_IS_WATER,


	TT_MAX_TRIGGER_TYPES,

} TRIGGER_TYPE;



typedef struct trig_entity_st
{
	short				triggerType;					/* -1 == end of list, -2== previously triggered */
	int				elapsedTime;					/* trigger list will be sorted by time */ 

	int				x;
	int				y;
	int				z;									/* most will go at floor height, but some pick-ups could float */
	short				rotation;						/* y-rotation */

	short				objectClass;
	short				objectType;
	short				objectId;

	short				parameter1;
	short				parameter2;
	short				parameter3;
	short				parameter4;

	unsigned char	trigParameter1;
	unsigned char	trigParameter2;
	unsigned char	trigParameter3;
	unsigned char	trigParameter4;
	
	short				flags;

} TRIGGER_ENTITY, *lpTRIGGER_ENTITY;


#define		MAX_AND_FLAGS					(8)
#define		MAX_OR_FLAGS					(8)
#define		MAX_OBJECTIVE_COUNTERS		(10)
#define		MAX_WIN_RATINGS				(4)
#define		MAX_LOSE_RATINGS				(4)


enum
{
	SOC_CRYSTALS_COLLECTED,
	SOC_MINIFIGURES_RESCUED,
};	

enum
{
	LEVEL_FAILED4=-4,
	LEVEL_FAILED3,
	LEVEL_FAILED2,
	LEVEL_FAILED1,
	LEVEL_INCOMPLETE,
	LEVEL_COMPLETE1,
	LEVEL_COMPLETE2,
	LEVEL_COMPLETE3,
	LEVEL_COMPLETE4,
};

typedef struct gamecontrol_st
{
	int						levelComplete;												// -1==failed 0==not complete, else rating
	char						flagsAND[MAX_AND_FLAGS];
	char						flagsOR[MAX_OR_FLAGS];
	int						numANDFlagsUsed;
	int						numORFlagsUsed;
	int						ratingAND;
	int						ratingOR;
	int						numObjectiveCounters;
	int						objectiveCounter[MAX_OBJECTIVE_COUNTERS];
	int						completionMessages[MAX_WIN_RATINGS];
	int						failureMessages[MAX_LOSE_RATINGS];
	lpTRIGGER_ENTITY		timedTriggerListBase;
	lpTRIGGER_ENTITY		timedTriggerList;
	lpTRIGGER_ENTITY		systemTriggerList;

} GAME_CONTROL, *lpGAME_CONTROL;


extern	GAME_CONTROL	gameControlGlobs;





/* prototypes */

BOOL Trigger_TestTrigger(lpTRIGGER_ENTITY trigger, void *data);
BOOL	Trigger_CreateFromTrigger(lpTRIGGER_ENTITY trigger);
void Trigger_ParseTriggerList(lpTRIGGER_ENTITY triggerList);
void	Trigger_ResetGameController(void);
void	Trigger_CheckConditionsAndScanTriggers(void);
BOOL	Trigger_LoadTriggerList(char *name, lpTRIGGER_ENTITY *listPtr);
BOOL	Trigger_SystemEntity(lpTRIGGER_ENTITY entity);
BOOL	Trigger_SystemCreateObjectiveANDFlag(lpTRIGGER_ENTITY entity);
BOOL	Trigger_SystemCreateObjectiveORFlag(lpTRIGGER_ENTITY entity);
BOOL	Trigger_SystemCreateObjectiveCounter(lpTRIGGER_ENTITY entity);
BOOL	Trigger_SystemDisplayMessage(lpTRIGGER_ENTITY entity);
BOOL Trigger_SystemIncrementObjectiveCounter(lpTRIGGER_ENTITY entity);
BOOL	Trigger_SystemSetLevelCompleted(lpTRIGGER_ENTITY entity);
BOOL	Trigger_SystemSetLevelFailed(lpTRIGGER_ENTITY entity);
BOOL	Trigger_SystemSetWinRatingForANDCompletion(lpTRIGGER_ENTITY entity);
BOOL	Trigger_SystemSetWinRatingForORCompletion(lpTRIGGER_ENTITY entity);
BOOL	Trigger_SystemSetWinMessage(lpTRIGGER_ENTITY entity);
BOOL	Trigger_SystemSetLoseMessage(lpTRIGGER_ENTITY entity);
BOOL	Trigger_SystemSetObjectiveANDFlagWhenCounterEquals(lpTRIGGER_ENTITY entity);
BOOL	Trigger_SystemSetObjectiveORFlagWhenCounterEquals(lpTRIGGER_ENTITY entity);

void	Trigger_IncrementCrystalsCollected(void);
void	Trigger_IncrementMinifiguresRescued(void);


#define	__TRIGGER_H
#endif

