//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// control handler:
//
// game level pad control code
// multiple event types from the same button
// user definable etc.
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Include all Header Files
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
#include	"globals.h"


#define		MPOINTER_SIZE	(16)

Uint16	padMasks[MAX_CONTROLS]=
{
	PAD_RL,
	PAD_RR,
	PAD_RU,
	PAD_RD,				/* right symbol cluster */

	PAD_FLT,
	PAD_FLB,								/* shoulder buttons */
	PAD_FRT,
	PAD_FRB,	

	PAD_DS_L,										/* the extra dual shock buttons */
	PAD_DS_R,

/* system controls, not redefinable */

	PAD_LL,
	PAD_LR,
	PAD_LU,
	PAD_LD,				/* left direction cluster */

	PAD_SEL,											/* select and start */
	PAD_START,

	PAD_RL,
	PAD_RR,
	PAD_RU,
	PAD_RD,				/* right symbol cluster */

	PAD_FLT,
	PAD_FLB,								/* shoulder buttons */

	PAD_FRT,
	PAD_FRB,	

};


lpImage			selectImage;


/*
	flush array of controls ready for use 
*/
void	Control_initialiseControlSet(lpCONTROL control)
{
	int	n;

	for (n=0; n<MAX_CONTROLS; n++)
	{
		control->mask=padMasks[n];			/* this will setup for the default controller arrangement */
		control->event=FALSE;
		control->transient=FALSE;
		control->held_time=0;
		control->repeat=WAIT_RELEASE;
		control++;
	}
}



/*
	this is called from the vblank
*/
void	Control_serviceMainControlSet(void)
{
	craftGlobs.playerList[0].controllerConnected=Control_serviceControlSet(craftGlobs.playerList[0].controlSet,0);
	craftGlobs.playerList[1].controllerConnected=Control_serviceControlSet(craftGlobs.playerList[1].controlSet,1);


	legoGlobs.vblankCount++;
	if (!legoGlobs.pauseFlag)
		legoGlobs.vblankCycles++;
	if (legoGlobs.vblankCycles>=gfxGlobs.framesPerSecond)
	{
		legoGlobs.elapsedTime++;
		legoGlobs.vblankCycles=0;
	}
}


/*
	update control set.

	This should be called from the vblank ideally, since
	we want to maintain a sense of real elapsed time

	The mask for each control is stored within the control, so re-definition
	is simply a matter of swapping these masks between suitable controls.

	Part of the ontrol set is fixed, to allow for 'system' operations, such
	as menu control/CD audio manipulation.

*/
BOOL	Control_serviceControlSet(lpCONTROL control,int padIndex)
{
	Uint16	*buffer=(Uint16*) &craftGlobs.playerList[padIndex].padBuffer[2];
	Uint16	n,padData;
	BOOL		connected=TRUE;

	if (craftGlobs.playerList[padIndex].padBuffer[0]==0)
	{
		padData=(craftGlobs.playerList[padIndex].padBuffer[3]<<8)+craftGlobs.playerList[padIndex].padBuffer[2];		
		padData^=0xffff;
	}
	else		/* bad data/not connected */
	{
		padData=0;
		if (craftGlobs.playerList[padIndex].padBuffer[1]==0)
		{
			connected=FALSE;

		/* reset the analogue entries, in case they contain something spurious */ 

			craftGlobs.playerList[padIndex].padBuffer[4]=0x80;		/* dead centre */
			craftGlobs.playerList[padIndex].padBuffer[5]=0x80;
			craftGlobs.playerList[padIndex].padBuffer[6]=0x80;
			craftGlobs.playerList[padIndex].padBuffer[7]=0x80;

		}
	}

	for (n=0; n<MAX_CONTROLS; n++)
	{
		if (padData & control->mask)
		{
			control->held_time++;
			control->transient=TRUE;

			if (control->repeat>0)
			{
				control->repeat--;			/* decrease repeat delay */
			}
			else
			{
				if (control->repeat==0)
					control->event=TRUE;
			}
		}
		else		/* button released */
		{
			control->transient=0;
			control->repeat=0;
			control->held_time=0;
		}
		control++;
	}
	return	connected;
}




