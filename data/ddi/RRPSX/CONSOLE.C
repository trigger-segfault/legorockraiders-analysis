//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// console stuff
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Include all Header Files
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
#include	"globals.h"



#ifdef DEBUG_CONSOLE

CONSOLE	consoleGlobs;

/*
	various routines for a text console, may be used in the
	final version, but it will be useful for debugging this
	rats nest.

*/
BOOL	Console_InitialiseConsole(void)
{
	int	n;

	consoleGlobs.text_base=Mem_Malloc(CONSOLE_MAX_LINES*CONSOLE_LINE_LENGTH);
	
	for (n=0; n<CONSOLE_MAX_LINES; n++)
	{
		consoleGlobs.text[n]=consoleGlobs.text_base+(n*CONSOLE_LINE_LENGTH);
		*(consoleGlobs.text[n])=0;
	}

	consoleGlobs.print_char=0;
	consoleGlobs.print_delay=0;
	consoleGlobs.displayed_lines=0;
	consoleGlobs.console_x=0;
	consoleGlobs.console_y=248-(8*CONSOLE_MAX_LINES);
	consoleGlobs.console_y_spacing=8;


#ifdef 0
	{
		char	string[64];
		sprintf(string, "|2Rock Raiders |7(%s)", __DATE__);
		CONSOLE_STRING(string);
		CONSOLE_STRING("-----------------------------");
	}	
#endif

	return	TRUE;

}


void	Console_SetConsolePosition(int x, int y)
{
	consoleGlobs.console_x=x;
	consoleGlobs.console_y=y;
}


/*
	add a string to the console
*/
void	Console_AddConsoleString(char	*string)
{
	char		*temp;
 	int		n;

	if (strlen(string)>CONSOLE_LINE_LENGTH-1)
		string[CONSOLE_LINE_LENGTH]=0;

	if (consoleGlobs.displayed_lines<CONSOLE_MAX_LINES)
	{
		strcpy(consoleGlobs.text[consoleGlobs.displayed_lines++],string);
	}
	else	/* shuffle pointers and add string at the end */
	{
		temp=consoleGlobs.text[0];
		for (n=0; n<CONSOLE_MAX_LINES-1; n++)
			consoleGlobs.text[n]=consoleGlobs.text[n+1];
		consoleGlobs.text[n]=temp;
		strcpy(consoleGlobs.text[CONSOLE_MAX_LINES-1],string);
	}
}


/*
	display the console
*/
void	Console_DisplayConsole(void)
{
	int		n;

	for (n=0; n<consoleGlobs.displayed_lines; n++)
	{
		Font_PrintF(legoGlobs.stdFont,consoleGlobs.console_x,consoleGlobs.console_y+(n*consoleGlobs.console_y_spacing),consoleGlobs.text[n]);
	}

}


/*
	flush console
*/
void	Console_FlushConsole(void)
{
	consoleGlobs.displayed_lines=0;
}

#endif



void Console_DebugPrint(int x, int y, LPUCHAR msg, ...)
{
	va_list	args;
	char		string[64];

	va_start(args, msg);
	vsprintf(string, msg, args);
	va_end(args);
	Font_PrintF(legoGlobs.stdFont,x,y,string);
}
