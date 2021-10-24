
//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// CD audio File For <LEGO [Rock Raiders]>
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Include all Header Files
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
#include	"globals.h"


CD_Globs	CDGlobs;



#define		CD_DISPLAY_X					(8)
#define		CD_DISPLAY_Y					(16)		/* offset from screen bottom (to allow for PAL/NTSC) */
#define		CD_DISPLAY_X_STEP				(19)
#define		CD_DISPLAY_X_SIZE				(17)
#define		CD_DISPLAY_Y_SIZE				(7)
#define		CD_DISPLAY_VOLUME_Y_OFFSET	(8)

/*
	display cd tracks selected, plus current selection
*/
void	CD_DisplayInfo(void)
{
	int				n;
	GsBOXF			box;
	static			int	jiffy;
	char				string[32];
	unsigned char	returnedParameters[8];
	int				playingTrack;
	int				CDStatus=0;

	if (CdControl(CdlNop,NULL,returnedParameters)==1)
		CDStatus=returnedParameters[0];


	if (CdControl(CdlGetlocP,NULL,returnedParameters)==1)
	{
		if ((CDStatus & CdlStatPlay)==0)
		{
			//Font_PrintF(legoGlobs.stdFont,CD_DISPLAY_X+2,(gfxGlobs.scrH)-CD_DISPLAY_Y-8,"Not Playing");
			Font_PrintF(legoGlobs.stdFont,CD_DISPLAY_X+2,(gfxGlobs.scrH)-CD_DISPLAY_Y-8,"--:--");
			playingTrack=-1;
		}
		else
		{
			sprintf(string,"%d%d:%d%d",(returnedParameters[2]>>4),(returnedParameters[2]&0xf),(returnedParameters[3]>>4),(returnedParameters[3]&0xf));
			Font_PrintF(legoGlobs.stdFont,CD_DISPLAY_X+2,(gfxGlobs.scrH)-CD_DISPLAY_Y-8,string);
			playingTrack=((returnedParameters[0]>>4)*10)+(returnedParameters[0]&0xf)-1;
		}
	}


	
	box.attribute=(GsALON | GsAONE);		/* semi trans enabled, blend of 100% background + 100% foreground */


	box.y=(gfxGlobs.scrH>>1)-CD_DISPLAY_Y;
	box.w=CD_DISPLAY_X_SIZE;
	box.h=CD_DISPLAY_Y_SIZE;


	for (n=0; n<CDGlobs.maxTracks; n++)
	{
		box.x=CD_DISPLAY_X-(gfxGlobs.scrW>>1)+(n*CD_DISPLAY_X_STEP);
		if (CDGlobs.virtualPlayList[n])
		{
			box.r=0;
			box.g=128;
			box.b=0;
		}
		else
		{
			box.r=128;
			box.g=0;
			box.b=0;
		}

		GsSortBoxFill(&box, &gfxGlobs.Wot[gfxGlobs.bufID], 10);

		if (playingTrack==n)
			sprintf(string,"|7%02d",n+1);
		else
			sprintf(string,"|0%02d",n+1);
		Font_PrintF(legoGlobs.stdFont,CD_DISPLAY_X+(n*CD_DISPLAY_X_STEP)+2,(gfxGlobs.scrH)-CD_DISPLAY_Y,string);

	}

	jiffy++;

/* show highlighted track index */
	if ((jiffy&4)==4)
	{
		if (CDGlobs.maxTracks==0)
		{
			Font_PrintF(legoGlobs.stdFont,CD_DISPLAY_X+2,(gfxGlobs.scrH)-CD_DISPLAY_Y-8,"No CD present");
		}
		else
		{
			box.y=((gfxGlobs.scrH>>1)-CD_DISPLAY_Y)-1;
			box.x=(CD_DISPLAY_X-(gfxGlobs.scrW>>1)+(CDGlobs.selectionIndex*CD_DISPLAY_X_STEP))-1;
			box.w=CD_DISPLAY_X_SIZE+2;
			box.h=CD_DISPLAY_Y_SIZE+2;

			box.r=100;
			box.g=100;
			box.b=0;
			GsSortBoxFill(&box, &gfxGlobs.Wot[gfxGlobs.bufID], 20);
		}
	}
}



/*
	handle player input, display tracks etc.
*/
void	CD_UpdateCDPlayer(void)
{
	CdlLOC		toc[100];		
	int			numTracks;

	lpCONTROL		control=craftGlobs.playerList[0].controlSet;

	if (PAD_EVENT(control,CONTROL_TURN_LEFT))
	{
		CLEAR_EVENT_RELEASE(control,CONTROL_TURN_LEFT);
		if (CDGlobs.selectionIndex>0)
			CDGlobs.selectionIndex--;
	}

	if (PAD_EVENT(control,CONTROL_TURN_RIGHT))
	{
		CLEAR_EVENT_RELEASE(control,CONTROL_TURN_RIGHT);
		if (CDGlobs.selectionIndex<CDGlobs.maxTracks-1)
			CDGlobs.selectionIndex++;
	}

	if (PAD_EVENT(control,CONTROL_SYS_CIRCLE))
	{
		CLEAR_EVENT_RELEASE(control,CONTROL_SYS_CIRCLE);
		CDGlobs.virtualPlayList[CDGlobs.selectionIndex]^=1;
	}


/* re-start a playlist from the CD control */
	if (PAD_EVENT(control,CONTROL_SYS_TRIANGLE))
	{
		CLEAR_EVENT_RELEASE(control,CONTROL_SYS_TRIANGLE);
		CD_StopCDAudio();
		CD_RemakePhysicalPlayList();
		CD_StartCDAudio();
	}


/* stop playlist */
	if (PAD_EVENT(control,CONTROL_SYS_SQUARE))
	{
		CLEAR_EVENT_RELEASE(control,CONTROL_SYS_SQUARE);
		CD_StopCDAudio();
	}

//	numTracks=CdGetToc(toc);
//	if (numTracks==0)
//		CDGlobs.maxTracks=0;

/*
	if the number of tracks returned becomes zero, then we will need to 
	re-acquire the CD if another is loaded. The trouble is knowing when,
	if we poll constantly it will slow pause mode down, not tragic, but
	certainly unappealing. The best strategy would probably be to check
	every n seconds.
*/

	//if (CdGetDiskType()==CdlStatShellOpen || CdGetDiskType()==CdlStatNoDisk)
//		CDGlobs.maxTracks=0;

	if (CDGlobs.maxTracks==0)
	{
		/* re-acquire TOC? */
	}

	CD_DisplayInfo();
}



/*
	handle resumption of CD audio after pause

	stop audio if no tracks active
	do nothing if current track hasn't changed
	else restart new playlist
*/ 
void	CD_HandleResumeFromPause(void)
{
	CD_StopCDAudio();
	CD_RemakePhysicalPlayList();
	CD_StartCDAudio();
}

/*
	remake the playlist from the active selections
*/
void	CD_RemakePhysicalPlayList(void)
{
	int	n,index=0;

	for (n=0; n<CDGlobs.maxTracks; n++)
	{
		if (CDGlobs.virtualPlayList[n])
		{
			CDGlobs.physicalPlayList[index++]=n+1;
			if (n==CDGlobs.selectionIndex)
				CDGlobs.currentTrack=index-1;
		}
	}

/* if the selector was left on an unselected track, default to the first selected track */

	if (!CDGlobs.virtualPlayList[CDGlobs.selectionIndex])
		CDGlobs.currentTrack=0;

	CDGlobs.physicalPlayList[index++]=0;			/* terminate play list */
}


/*
	start CD audio playback of play list
*/
void	CD_StartCDAudio(void)
{
	if (CDGlobs.maxTracks>0)
		CdPlay(1,CDGlobs.physicalPlayList,CDGlobs.currentTrack);		
}

/*
	stop CD audio playback of play list
*/
void	CD_StopCDAudio(void)
{
	if (CDGlobs.maxTracks>0)
		CdPlay(0,CDGlobs.physicalPlayList,CDGlobs.currentTrack);		
}


/*
	pause CD audio
*/
void	CD_PauseCDAudio(void)
{
	unsigned char	returnedParameters[8];

	if (!CDGlobs.pauseFlag)
	{
		CDGlobs.pauseFlag=CdControl(CdlPause,NULL,returnedParameters);
	}
}

/*
	resume CD audio
*/
void	CD_ResumeCDAudio(void)
{
	unsigned char	returnedParameters[8];

	if (CDGlobs.pauseFlag)
	{
		if (CdControl(CdlPause,NULL,returnedParameters)==1)
			CDGlobs.pauseFlag=0;
	}
}


/*
	initialise CD audio system
*/
BOOL	CD_initialiseCDAudio(void)
{
	CdlLOC		toc[100];		
	int			n;

	CdInit();
	CDGlobs.maxTracks=CdGetToc(toc);

/* mark all virtual tracks as playable */

	for (n=0; n<CDGlobs.maxTracks; n++)
		CDGlobs.virtualPlayList[n]=TRUE;
	CD_RemakePhysicalPlayList();

	CDGlobs.currentTrack=0;
	CDGlobs.volume=127;
	CDGlobs.menuIndex=0;
	CDGlobs.selectionIndex=0;
	CDGlobs.pauseFlag=FALSE;
	CDGlobs.searchFlag=0;

	return	TRUE;
}


