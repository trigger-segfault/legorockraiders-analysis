//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// general object For <LEGO [Rock Raiders]>
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#include	"globals.h"




/*
	create craft and minifigure pools
*/
void	Object_InitialiseLists(void)
{
	int				n;
	char				path[128];
	lpContainer		tempCont;

	objectGlobs.numCraft=0;
	objectGlobs.numPlayers=0;
	objectGlobs.playerList[0].craft=NULL;
	objectGlobs.playerList[1].craft=NULL;
	objectGlobs.playerList[0].flags=0;
	objectGlobs.playerList[1].flags=0;

/* prepare the NULL control set */
	Control_initialiseControlSet(nullControlSet);

/* load the HMD models, change later to selection as necessary */

	for (n=0; n<TR_CRAFT_MAX_TYPES; n++)
	{
		sprintf(path,"VEHICLES\\%s",craftSetupData[n].modelName);
		objectGlobs.craftContList[n]=Container_LoadHMDModel(legoGlobs.rootCont, path);
	}


/* load the sprite sequences for the minifigure */

	Image_LoadActivityFromConfig(&objectGlobs.minifigureActivitySet,"FIGURES\\MINIFIG",legoGlobs.gameName);

/* load sprites for pickups */

	//Image_LoadActivityFromConfig(&objectGlobs.minifigureActivitySet,"FIGURES\\MINIFIG",legoGlobs.gameName);


/* create minifigure pool */

	for (n=0; n<MAX_MINIFIGURES; n++)
	{	
		if (tempCont=Container_CreateSprite(legoGlobs.rootCont,objectGlobs.minifigureActivitySet))
		{
			objectGlobs.minifigureList[n].refCont=tempCont;
			Container_SetParent(legoGlobs.rootCont,tempCont);
			Container_SetScale(tempCont,ONE);
			Container_Hide(tempCont, TRUE);
		}
		else
		{
			/* error creating minifigure pool */
		}
	}


/* initialise the main object list */


	for (n=0; n<MAX_OBJECTS; n++)
	{
		objectGlobs.objectList[n].cont=NULL;		/* mark as unused */
	}

}
