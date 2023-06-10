
#ifndef _RGL_TEXTWINDOW_H_
#define _RGL_TEXTWINDOW_H_

#include "Standard.h"

// *****************************************************************************************************************
struct TextWindow {


	AREA2Dr		windowSize;

};


// *****************************************************************************************************************
typedef struct TextWindow							*lpTextWindow;


// *****************************************************************************************************************
void			TextWindow_Clear(lpTextWindow window);
void			TextWindow_PrintF(lpTextWindow window, LPUCHAR msg, ...) ;
BOOL			TextWindow_Update(lpTextWindow window, ULONG posFromEnd, REAL time, LPSLONG lpLowestPoint);
lpTextWindow	TextWindow_Create(lpFont font, LPAREA2Dr size, ULONG bufferSize);
void			TextWindow_SetFont(lpTextWindow window, lpFont font);
int				TextWindow_GetRow(lpTextWindow window, int chrPos, int dir);
void			TextWindow_EnableCentering(lpTextWindow window, BOOL enable);
void			TextWindow_Remove(lpTextWindow window);


// *****************************************************************************************************************
// *****************************************************************************************************************
// *****************************************************************************************************************

#endif // _RGL_TEXTWINDOW_H_
