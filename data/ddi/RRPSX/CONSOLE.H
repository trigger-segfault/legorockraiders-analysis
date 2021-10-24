//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Console Include File For <LEGO [Rock Raiders]>
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹


#ifndef	__CONSOLE_H

#define	DEBUG_CONSOLE




#ifdef DEBUG_CONSOLE

#define		CONSOLE_MAX_LINES		(15)
#define		CONSOLE_LINE_LENGTH	(64)
#define		CONSOLE_PRINT_DELAY	(16)
typedef struct console_st
{
	unsigned char	*text[CONSOLE_MAX_LINES];	
	unsigned char	*text_base;
	Uint16			displayed_lines;
	Uint16			console_x;
	Uint16			console_y;
	Uint16			console_y_spacing;

	Uint16			print_char;
	Uint16			print_line;
	Uint16			print_delay;

}	CONSOLE, *LPCONSOLE;

void	Console_AddConsoleString(char	*string);
BOOL	Console_InitialiseConsole(int x, int y);
void	Console_DisplayConsole(BOOL background);
void	Console_SetConsolePosition(int x, int y);
void	Console_FlushConsole(void);

#define	CONSOLE_STRING(x) 			Console_AddConsoleString(x)
#define	CONSOLE_FLUSH					Console_FlushConsole()
#define	CONSOLE_LOAD_STRING(x)		Loader_FileLoadCallback(x,0,NULL)

#else

#define	CONSOLE_STRING(x)



#endif


void Console_DebugPrint(int x, int y, LPUCHAR msg, ...);


#ifdef __CDVERSION

 //#define	DEBUG_PRINT(x,y,s,v)

#else

 //#define	DEBUG_PRINT(x,y,s,v) 	Console_DebugPrint(x,y,s,v)

#endif

#define	__CONSOLE_H
#endif
























































