//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// trigger handler For <LEGO [Rock Raiders]>
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

#include	"globals.h"




GAME_CONTROL	gameControlGlobs;




/*
	a test trigger list for a demo level
	- collect 10 crystals and return to base
*/
TRIGGER_ENTITY	testList[]=
{
	{UST_CREATE_OBJECTIVE_COUNTER(0,0)},
	{UST_CREATE_OBJECTIVE_COUNTER(1,3)},
	{UST_CREATE_OBJECTIVE_COUNTER(2,0)},

/* create 2 AND flags... */
	{UST_CREATE_OBJECTIVE_AND_FLAG(0)},
	{UST_CREATE_OBJECTIVE_AND_FLAG(1)},

/* ...and one OR flag */

	{UST_CREATE_OBJECTIVE_OR_FLAG(0)},
	{UST_SET_WIN_RATING_FOR_AND_COMPLETION(2)},
	{UST_SET_WIN_RATING_FOR_OR_COMPLETION(3)},
	{UST_SET_WIN_MESSAGE(2,199)},
	{UST_SET_WIN_MESSAGE(3,200)},


/* don't forget this... */
	{TRIGGER_LIST_END},
};


/*
	a test system list
*/
TRIGGER_ENTITY	systemList[]=
{
	{UST_SET_OBJECTIVE_AND_FLAG_WHEN_COUNTER_EQUALS(0,0,10)},
	{UST_SET_OBJECTIVE_AND_FLAG_WHEN_COUNTER_EQUALS(1,1,5)},
	{UST_SET_OBJECTIVE_OR_FLAG_WHEN_COUNTER_EQUALS(0,2,2)},
	{TRIGGER_LIST_END},
};



/*
	load a trigger list and store pointer to it

	name can be anything, correct path is pre-pended to it.

*/
BOOL	Trigger_LoadTriggerList(char *name, lpTRIGGER_ENTITY *listPtr)
{
	char						triggerPath[256];
	lpTRIGGER_ENTITY		tempTrigger;


	sprintf(triggerPath,"%s%s",legoGlobs.levelPath,name);
	if (tempTrigger = File_LoadBinary(triggerPath, NULL))
	{
		*listPtr=tempTrigger;
		return	TRUE;
	}
	return	FALSE;
}


/*
	this will set up a test for the triggers
*/
void	Trigger_TestTriggerSetup(void)
{

	Trigger_ParseTriggerList(testList);

}




void Trigger_ScanSystemTriggerList(lpTRIGGER_ENTITY triggerList)
{
	BOOL	status;

	while (triggerList->triggerType!=-1)
	{
		status=Trigger_CreateFromTrigger(triggerList);
		if (status)
			triggerList->triggerType=TT_TRIGGERED;
		triggerList++;
	}
}


void	Trigger_TestTriggerRun(void)
{
	Trigger_CheckConditionsAndScanTriggers();
	Trigger_ScanSystemTriggerList(systemList);
}



#define		DGSY			(100)
/*
	display debug status
*/
void Trigger_DisplayGameStatus(void)
{
#ifdef 0
	char			string[128];

	sprintf(string,"complete=%d",gameControlGlobs.levelComplete);
	Font_PrintF(legoGlobs.stdFont,8,DGSY,string);

	sprintf(string,"flagsAND=%d,%d,%d,%d",gameControlGlobs.flagsAND[0],gameControlGlobs.flagsAND[1],gameControlGlobs.flagsAND[2],gameControlGlobs.flagsAND[3]);
	Font_PrintF(legoGlobs.stdFont,8,DGSY+8,string);

	sprintf(string,"flagsOR=%d,%d,%d,%d",gameControlGlobs.flagsOR[0],gameControlGlobs.flagsOR[1],gameControlGlobs.flagsOR[2],gameControlGlobs.flagsOR[3]);
	Font_PrintF(legoGlobs.stdFont,8,DGSY+16,string);

	sprintf(string,"counters=%d,%d,%d,%d",gameControlGlobs.objectiveCounter[0],gameControlGlobs.objectiveCounter[1],gameControlGlobs.objectiveCounter[2],gameControlGlobs.objectiveCounter[3]);
	Font_PrintF(legoGlobs.stdFont,8,DGSY+24,string);
		
#endif
}


/*
	clear game controller structure, prior to trigger list parsing
*/

void	Trigger_ResetGameController(void)
{
	int	n;

	gameControlGlobs.levelComplete=0;
	gameControlGlobs.ratingAND=1;
	gameControlGlobs.ratingOR=1;				/* default rating */

	gameControlGlobs.numANDFlagsUsed=0;
	gameControlGlobs.numORFlagsUsed=0;

	for (n=0; n<MAX_WIN_RATINGS; n++)
		gameControlGlobs.completionMessages[n]=0;

	for (n=0; n<MAX_LOSE_RATINGS; n++)
		gameControlGlobs.failureMessages[n]=0;

/* mark all flags an counters as unused */

	for (n=0; n<MAX_AND_FLAGS; n++)
		gameControlGlobs.flagsAND[n]=-1;

	for (n=0; n<MAX_AND_FLAGS; n++)
		gameControlGlobs.flagsOR[n]=-1;

	for (n=0; n<MAX_OBJECTIVE_COUNTERS; n++)
		gameControlGlobs.objectiveCounter[n]=-1;

/* 
	now create 2 objective counters that are always
	present, counter zero for crystals collected, and counter
	one for minifigures rescued.
*/

	gameControlGlobs.objectiveCounter[SOC_CRYSTALS_COLLECTED]=0;
	gameControlGlobs.objectiveCounter[SOC_MINIFIGURES_RESCUED]=0;

	gameControlGlobs.numObjectiveCounters=2;

}


/*
	check for win/lose conditions, and scan triggers
*/
void	Trigger_CheckConditionsAndScanTriggers(void)
{
	int		n,totalAND=0;

	if (gameControlGlobs.levelComplete==LEVEL_INCOMPLETE)		/* we stop once a win/lose has been set */
	{
		/* any of the OR conditions can generate a win */

		for (n=0; n<MAX_OR_FLAGS; n++)
		{
			if (gameControlGlobs.flagsOR[n]==1)
			{
				gameControlGlobs.levelComplete=gameControlGlobs.ratingOR;
				return;													/* we can bug out now */
			}
		}

		/* now the AND flags, obviously we must have all of them for a win */

		for (n=0; n<MAX_OR_FLAGS; n++)
		{
			if (gameControlGlobs.flagsAND[n]==1)
				totalAND++;
		}

		if ((totalAND==gameControlGlobs.numANDFlagsUsed) && totalAND>0)
			gameControlGlobs.levelComplete=gameControlGlobs.ratingAND;

	}
}


/*
	scan the trigger list for initial triggers, 
*/
void Trigger_ParseTriggerList(lpTRIGGER_ENTITY triggerList)
{
	int						timedCount=0;
	lpTRIGGER_ENTITY 		triggerListBase=triggerList;

/*
	scan the list, process the triggers which take effect immediately, and create
	a sorted list of triggers for the game. Sorting by time means we scan less triggers
	needlessly. An immediate trigger is one which has an elapsed time of zero.
*/

	while (triggerList->triggerType!=-1)
	{
		if (triggerList->elapsedTime==0)
		{
			Trigger_CreateFromTrigger(triggerList);
			triggerList->triggerType=TT_TRIGGERED;
		}
		else
			timedCount++;

		triggerList++;
	}


	return;


/* now create the sorted trigger list  */

	
	triggerList=triggerListBase;


	while (triggerList->triggerType!=-1)
	{
		if (triggerList->elapsedTime==0)
		{
			Trigger_CreateFromTrigger(triggerList);
			triggerList->triggerType=TT_TRIGGERED;
		}
		else
			timedCount++;

		triggerList++;
	}

}




/*
	-----------------------------------------------------------------------

	These are the conditional tests for trigger firing

	-----------------------------------------------------------------------
*/


/*
	no condition, obviously, more of an error since all unconditional
	triggers should have been accounted for prior to this
*/
BOOL Trigger_TestNoCondition(lpTRIGGER_ENTITY trigger,void *data)
{
	return	TRUE;
}


/*
	again this will be handled by the timed list, so shouldn't get
	called from here.
*/
BOOL Trigger_TestAtTime(lpTRIGGER_ENTITY trigger,void *data)
{
	if (trigger->elapsedTime>=legoGlobs.elapsedTime)
		return	TRUE;
	else
		return	FALSE;
}


	

BOOL Trigger_TestObjectiveANDFlagSet(lpTRIGGER_ENTITY trigger,void *data)
{
	return	
}

BOOL Trigger_TestObjectiveORFlagSet(lpTRIGGER_ENTITY trigger,void *data)
{
	return	
}

BOOL Trigger_TestObjectiveCounterEqualsValue(lpTRIGGER_ENTITY trigger,void *data)
{
	return	
}

BOOL Trigger_TestCreatureOfIdDestroyed(lpTRIGGER_ENTITY trigger,void *data)
{
	return	
}

BOOL Trigger_TestCreatureOfTypeDestroyed(lpTRIGGER_ENTITY trigger,void *data)
{
	return	
}

BOOL Trigger_TestObjectOfIdCollected(lpTRIGGER_ENTITY trigger,void *data)
{
	return	
}

BOOL Trigger_TestObjectOfTypeCollected(lpTRIGGER_ENTITY trigger,void *data)
{
	return	
}

BOOL Trigger_TestMinifgureArrived(lpTRIGGER_ENTITY trigger,void *data)
{
	return	
}

BOOL Trigger_TestCraftArrived(lpTRIGGER_ENTITY trigger,void *data)
{
	return	
}

BOOL Trigger_TestCreatureArrived(lpTRIGGER_ENTITY trigger,void *data)
{
	return	
}


/*
	return true if block at x/y is dug
*/
BOOL Trigger_TestBlockDug(lpTRIGGER_ENTITY trigger, void *data)
{
	lpLego_Block	block;
	
	block=&blockValue(legoGlobs.currLevel,trigger->trigParameter1,trigger->trigParameter2);
	if (block->flags & LEGOBLOCK_FLAG_BLOCK_DUG)
		return	TRUE;
	else
		return	FALSE;
}


BOOL (lpTRIGGER_ENTITY trigger,void *data)
{
	return	
}

BOOL (lpTRIGGER_ENTITY trigger,void *data)
{
	return	
}

BOOL (lpTRIGGER_ENTITY trigger,void *data)
{
	return	
}

BOOL (lpTRIGGER_ENTITY trigger,void *data)
{
	return	
}



/*
	jump table for the trigger test routines
*/
BOOL (*triggerTest[])(lpTRIGGER_ENTITY trigger,void *data)=
{
	Trigger_TestNoCondition,
	Trigger_TestAtTime,

/* system tests */
	Trigger_TestObjectiveANDFlagSet,
	Trigger_TestObjectiveORFlagSet,
	Trigger_TestObjectiveCounterEqualsValue,

/* object destroyed */
	Trigger_TestCreatureOfIdDestroyed,
	Trigger_TestCreatureOfTypeDestroyed,

/* object collected */
	Trigger_TestObjectOfIdCollected,
	Trigger_TestObjectOfTypeCollected,

/* object at location */
	Trigger_TestMinifgureArrived,
	Trigger_TestCraftArrived,
	Trigger_TestCreatureArrived,

/* block tests */
	Trigger_TestBlockDug,
	Trigger_TestLavaToRock,
	Trigger_TestBlockIsRock,
	Trigger_TestBlockIsLava,
	Trigger_TestBlockIsWater,
		
};





/*
	test a conditional trigger, and generate appropriate response
	data can be a pointer to an object, depending on the context.
*/
BOOL Trigger_TestTrigger(lpTRIGGER_ENTITY trigger, void *data)
{
	BOOL	status;
	if (trigger->triggerType>=0 && trigger->triggerType<TT_MAX_TRIGGER_TYPES)
	{
		if (status=triggerTest[trigger->triggerType](trigger,data))
			Trigger_CreateFromTrigger(trigger);

		return	status;
	}
	return	FALSE;			/* bad trigger type */
}





/*
	create object or whatever, from trigger entity
*/
BOOL	Trigger_CreateFromTrigger(lpTRIGGER_ENTITY entity)
{
	BOOL	status;

	if (entity->triggerType<0)
		return	FALSE;
	if (entity->triggerType>=TT_MAX_TRIGGER_TYPES)
	{
		/* invalid trigger type */
		return	FALSE;
	}

	switch (entity->objectClass)
	{
		case	OC_CRAFT:
		{
			Craft_CreateCraft(entity->objectType,entity->x, entity->y, entity->rotation);
			break;			
		}

		case	OC_PICKUP:
		{

			break;			
		}

		case	OC_CREATURE:
		{
			Creature_CreateCreature(entity);
			break;			
		}

		case	OC_MINIFIGURE:
		{
			Player_CreateMinifigure(entity->x, entity->y, entity->rotation,entity->parameter1);
			break;			
		}

		case	OC_SYSTEM:
		{
			status=Trigger_SystemEntity(entity);
			break;			
		}

	}

	return	status;
}



	
/*
	create a system entity
*/
BOOL	Trigger_SystemEntity(lpTRIGGER_ENTITY entity)
{
	BOOL		status=FALSE;

	switch (entity->objectType)
	{
		case	SYSTEM_CREATE_OBJECTIVE_AND_FLAG:
	 	{
			status=Trigger_SystemCreateObjectiveANDFlag(entity);
			break;
		}

		case	SYSTEM_CREATE_OBJECTIVE_OR_FLAG:
	 	{
			status=Trigger_SystemCreateObjectiveORFlag(entity);
			break;
		}

		case	SYSTEM_CREATE_OBJECTIVE_COUNTER:
	 	{
			status=Trigger_SystemCreateObjectiveCounter(entity);
			break;
		}

/* set */

		case	SYSTEM_DISPLAY_MESSAGE:
	 	{
			status=Trigger_SystemDisplayMessage(entity);
			break;
		}

		case	SYSTEM_INCREMENT_OBJECTIVE_COUNTER:
	 	{
			status=Trigger_SystemIncrementObjectiveCounter(entity);
			break;
		}

		case	SYSTEM_SET_LEVEL_COMPLETED:
		{
			status=Trigger_SystemSetLevelCompleted(entity);
			break;
		}

		case	SYSTEM_SET_LEVEL_FAILED:
		{
			status=Trigger_SystemSetLevelFailed(entity);
			break;
		}


		case	SYSTEM_SET_WIN_RATING_FOR_AND_COMPLETION:
		{
			status=Trigger_SystemSetWinRatingForANDCompletion(entity);
			break;
		}

		case	SYSTEM_SET_WIN_RATING_FOR_OR_COMPLETION:
		{
			status=Trigger_SystemSetWinRatingForORCompletion(entity);
			break;
		}

		case	SYSTEM_SET_WIN_MESSAGE:
		{
			status=Trigger_SystemSetWinMessage(entity);
			break;
		}

		case	SYSTEM_SET_LOSE_MESSAGE:
		{
			status=Trigger_SystemSetLoseMessage(entity);
			break;
		}



/* test and set */

		case	SYSTEM_SET_OBJECTIVE_OR_FLAG_WHEN_COUNTER_EQUALS:
		{
			status=Trigger_SystemSetObjectiveORFlagWhenCounterEquals(entity);
			break;
		}

		case	SYSTEM_SET_OBJECTIVE_AND_FLAG_WHEN_COUNTER_EQUALS:
		{
			status=Trigger_SystemSetObjectiveANDFlagWhenCounterEquals(entity);
			break;
		}

	}

	return	status;
}



/*
	create an objective AND flag
*/
BOOL	Trigger_SystemCreateObjectiveANDFlag(lpTRIGGER_ENTITY entity)
{
	if (entity->parameter1>=MAX_AND_FLAGS)
		return	FALSE;										/* bad uid */


	if (gameControlGlobs.flagsAND[entity->parameter1]!=-1)
		return	FALSE;										/* flag already in use */

	gameControlGlobs.flagsAND[entity->parameter1]=0;
	gameControlGlobs.numANDFlagsUsed++;

	return	TRUE;
}


/*
	create an objective OR flag
*/
BOOL	Trigger_SystemCreateObjectiveORFlag(lpTRIGGER_ENTITY entity)
{
	if (entity->parameter1>=MAX_OR_FLAGS)
		return	FALSE;										/* bad uid */


	if (gameControlGlobs.flagsOR[entity->parameter1]!=-1)
		return	FALSE;										/* flag already in use */

	gameControlGlobs.flagsOR[entity->parameter1]=0;
	gameControlGlobs.numORFlagsUsed++;

	return	TRUE;
}


/*
	create an objective counter, and initialise to passed value
*/
BOOL	Trigger_SystemCreateObjectiveCounter(lpTRIGGER_ENTITY entity)
{
	if (entity->parameter1>=MAX_OBJECTIVE_COUNTERS)
		return	FALSE;										/* bad uid */


	if (gameControlGlobs.objectiveCounter[entity->parameter1]!=-1)
		return	FALSE;										/* counter already in use */

	gameControlGlobs.objectiveCounter[entity->parameter1]=entity->parameter2;
	gameControlGlobs.numObjectiveCounters++;

	return	TRUE;
}


/*
	display a message with the supplied ID for specified time
*/
BOOL	Trigger_SystemDisplayMessage(lpTRIGGER_ENTITY entity)
{

//	if (Language_AddSystemString(entity->parameter1))
	{
		return	TRUE;
	}

	return	FALSE;
}



BOOL Trigger_SystemIncrementObjectiveCounter(lpTRIGGER_ENTITY entity)
{
	if (gameControlGlobs.objectiveCounter[entity->parameter1]!=-1)
	{
		gameControlGlobs.objectiveCounter[entity->parameter1]+=entity->parameter2;
		return	TRUE;
	}
	return	FALSE;		/* attempt to increment unassigned counter */
}


/*
	set level complete with status
*/
BOOL	Trigger_SystemSetLevelCompleted(lpTRIGGER_ENTITY entity)
{
	if (gameControlGlobs.levelComplete==LEVEL_INCOMPLETE)
	{
		gameControlGlobs.levelComplete=entity->parameter1;
		return	TRUE;
	}

	return	FALSE;		/* already set */
}


/*
	set level failed with status
*/
BOOL	Trigger_SystemSetLevelFailed(lpTRIGGER_ENTITY entity)
{
	if (gameControlGlobs.levelComplete==LEVEL_INCOMPLETE)
	{
		gameControlGlobs.levelComplete=-entity->parameter1;
		return	TRUE;
	}
	return	FALSE;
}



/*
	set win rating for AND completion
*/
BOOL	Trigger_SystemSetWinRatingForANDCompletion(lpTRIGGER_ENTITY entity)
{
	gameControlGlobs.ratingAND=entity->parameter1;
	return	TRUE;
}

/*
	set win rating for OR completion
*/
BOOL	Trigger_SystemSetWinRatingForORCompletion(lpTRIGGER_ENTITY entity)
{
	gameControlGlobs.ratingOR=entity->parameter1;
	return	TRUE;
}

/*
	set message id for win rating
*/
BOOL	Trigger_SystemSetWinMessage(lpTRIGGER_ENTITY entity)
{
	if (entity->parameter1<=MAX_WIN_RATINGS)
	{
		gameControlGlobs.completionMessages[entity->parameter1-1]=entity->parameter2;
		return	TRUE;
	}
	return	FALSE;
}

/*
	set message id for lose rating
*/
BOOL	Trigger_SystemSetLoseMessage(lpTRIGGER_ENTITY entity)
{
	if (entity->parameter1<=MAX_LOSE_RATINGS)
	{
		gameControlGlobs.failureMessages[entity->parameter1-1]=entity->parameter2;
		return	TRUE;
	}
	return	FALSE;
}


/*
	set an object AND flag if a counter equals passed value
*/
BOOL	Trigger_SystemSetObjectiveANDFlagWhenCounterEquals(lpTRIGGER_ENTITY entity)
{
	if (gameControlGlobs.objectiveCounter[entity->parameter2]==entity->parameter3)
	{
		gameControlGlobs.flagsAND[entity->parameter1]=TRUE;
		return	TRUE;
	}
	return	FALSE;
}


/*
	set an object OR flag if a counter equals passed value
*/
BOOL	Trigger_SystemSetObjectiveORFlagWhenCounterEquals(lpTRIGGER_ENTITY entity)
{
	if (gameControlGlobs.objectiveCounter[entity->parameter2]==entity->parameter3)
	{
		gameControlGlobs.flagsOR[entity->parameter1]=TRUE;
		return	TRUE;
	}
	return	FALSE;
}



void	Trigger_IncrementCrystalsCollected(void)
{
	gameControlGlobs.objectiveCounter[SOC_CRYSTALS_COLLECTED]++;
}

void	Trigger_IncrementMinifiguresRescued(void)
{
	gameControlGlobs.objectiveCounter[SOC_MINIFIGURES_RESCUED]++;
}
