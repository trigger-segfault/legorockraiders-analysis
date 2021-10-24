//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Loader File For <LEGO [Rock Raiders]>
//
// Started:	10-07-98
// Coding:	Glenn Benson
// Graphics:
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Include all Header Files
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
#include	"globals.h"

Loader_Globs loaderGlobs;

void	Loader_Initialise(LPUCHAR screen, lpFont font)
{
	memset((LPUCHAR)&loaderGlobs, 0, sizeof(Loader_Globs));
	loaderGlobs.loadImage = Image_LoadTIM(screen);
	loaderGlobs.font = font;
	loaderGlobs.count=0;
	File_SetLoadCallback(Loader_FileLoadCallback, NULL);
}

void Loader_Enable(BOOL enable)
{
	if (enable)
	{
		loaderGlobs.flags |= LOADER_FLAG_ENABLED;
		Loader_FileLoadCallback(NULL, 0, NULL);
	}
	else
		loaderGlobs.flags &= ~LOADER_FLAG_ENABLED;
}



#define	LOADING_BAR_X	(120-(384>>1))
#ifdef __PAL
 #define	LOADING_BAR_Y	(237-(256>>1))
#else
 #define	LOADING_BAR_Y	(222-(240>>1))
#endif

#define LOADING_BAR_W	(144)
#define LOADING_BAR_H	(2)


/*
	total size of files per level.
	zero will show a full bar immediately,
	indicating the size has not been set
*/
int	level_size[]={608941,608941,608941,0,0,0,0,0,0,0,0,0,0,0,0};

/* display loading bar (how original) */
void Loader_display_loading_bar(void)
{

	GsBOXF	loading_bar;
	REAL		max,loaded;


	loaded=get_file_total();
	if (loaded>=level_size[legoGlobs.level-1])
		loading_bar.w=LOADING_BAR_W;
	else
	{
		loaded<<=8;
		max=level_size[0];
		if (max!=0)
		{
			loaded/=max;
			loaded*=LOADING_BAR_W;
			loading_bar.w=(loaded>>8);
		}
		else
			loading_bar.w=0;

		if (loading_bar.w>LOADING_BAR_W)
			loading_bar.w=LOADING_BAR_W;
			
	}

/* the bar */
 	loading_bar.attribute=0;
	loading_bar.x=LOADING_BAR_X;
	loading_bar.y=LOADING_BAR_Y;
	loading_bar.h=LOADING_BAR_H;
	loading_bar.r=255;
	loading_bar.g=0;
	loading_bar.b=0;
	GsSortBoxFill(&loading_bar, &gfxGlobs.Wot[gfxGlobs.bufID], 1);

/* white border */
 	loading_bar.attribute=0;
	loading_bar.x=LOADING_BAR_X-1;
	loading_bar.y=LOADING_BAR_Y-1;
	loading_bar.w=LOADING_BAR_W+2;
	loading_bar.h=LOADING_BAR_H+2;
	loading_bar.r=255;
	loading_bar.g=255;
	loading_bar.b=255;
	GsSortBoxFill(&loading_bar, &gfxGlobs.Wot[gfxGlobs.bufID], 1);
}



void Loader_FileLoadCallback(LPUCHAR fname, ULONG size, LPVOID data)
{
	int	loop;

	gfxGlobs.fadeLevel = 128;

	if (loaderGlobs.flags & LOADER_FLAG_ENABLED)
	{
		CONSOLE_STRING(fname);

		for(loop=0; loop<2; loop++)
		{
			Gfx_StartDraw();
			if (loaderGlobs.count++<2)
				Image_Display(loaderGlobs.loadImage, NULL);		

#ifdef DEBUG_CONSOLE
			Console_DisplayConsole(TRUE);
#endif

			Main_LoopUpdate(FALSE);
			Loader_display_loading_bar();
			Gfx_ScreenFlip();
		}
	}
}



void Loader_Shutdown(void)
{
	Image_Remove(loaderGlobs.loadImage);
}


