
#ifndef _GODS98_TEXTWINDOW_H
#define _GODS98_TEXTWINDOW_H

#include "..\Inc\Fonts.h"

#define TEXTWINDOW_MAXSTRINGLEN			1024
#define TEXTWINDOW_MAXLINES				256

#define	TEXTWINDOW_DISPLAYDELAY			25

#define TEXTWINDOW_FLAG_WINDOWWRAPPED	0x00000001
#define TEXTWINDOW_FLAG_OVERLAY			0x00000002
#define TEXTWINDOW_FLAG_CENTERED		0x00000004

typedef struct TextWindow {

	lpFont font;
	AREA2D windowSize;
	LPUCHAR windowBuffer;
	UCHAR secondaryBuffer[TEXTWINDOW_MAXSTRINGLEN];
	ULONG windowBufferSize, windowBufferEnd;
	ULONG lineList[TEXTWINDOW_MAXLINES];
	ULONG usedLines;
	ULONG maxLines;

	REAL displayDelay;

	ULONG flags;

} TextWindow, *lpTextWindow;

int TextWindow_GetRow(lpTextWindow window, int chrPos, int dir);
VOID TextWindow_SetFont(lpTextWindow window, lpFont font);

#ifndef _GENPROTFILE
#include "..\Src\TextWindow.prot"
#endif // !_GENPROTFILE

#endif // !_GODS98_TEXTWINDOW_H
