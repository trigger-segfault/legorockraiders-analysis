#pragma once

#include "../framework.h"
#include "Fonts.h"
#include "Maths.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define TEXTWINDOW_MAXSTRINGLEN			1024
#define TEXTWINDOW_MAXLINES				256

#define	TEXTWINDOW_DISPLAYDELAY			25

#pragma endregion

/**********************************************************************************
 ******** Enumerations
 **********************************************************************************/

#pragma region Enums

#define TEXTWINDOW_FLAG_WINDOWWRAPPED	0x00000001
#define TEXTWINDOW_FLAG_OVERLAY			0x00000002
#define TEXTWINDOW_FLAG_CENTERED		0x00000004

#pragma endregion

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

typedef struct TextWindow
{
	/*000,4*/ Font* font;
	/*004,10*/ AREA2D windowSize;
	/*014,4*/ char* windowBuffer;
	/*018,400*/ char secondaryBuffer[TEXTWINDOW_MAXSTRINGLEN];
	/*418,4*/ unsigned long windowBufferSize;
	/*41c,4*/ unsigned long windowBufferEnd;
	/*420,400*/ unsigned long lineList[TEXTWINDOW_MAXLINES];
	/*820,4*/ unsigned long usedLines; // (count)
	/*824,4*/ unsigned long maxLines;  // (capacity)
	/*828,4*/ float displayDelay;
	/*82c,4*/ unsigned long flags;
	/*830*/
} TextWindow, *lpTextWindow;
static_assert(sizeof(TextWindow) == 0x830, "");

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @004853b0>
TextWindow* __cdecl TextWindow_Create(Font* font, const AREA2D* size, unsigned long bufferSize);

// <LegoRR.exe @00485420>
void __cdecl TextWindow_EnableCentering(TextWindow* window, BOOL enable);

// <LegoRR.exe @00485450>
void __cdecl TextWindow_Remove(TextWindow* window);

// <LegoRR.exe @00485470>
void __cdecl TextWindow_ChangePosition(TextWindow* window, long xPos, long yPos);

// <LegoRR.exe @00485490>
void __cdecl TextWindow_ChangeSize(TextWindow* window, unsigned long width, unsigned long height);

// <LegoRR.exe @004854d0>
void __cdecl TextWindow_PagePrintF(TextWindow* window, unsigned long page, const char* msg, ...);

// <LegoRR.exe @004854f0>
void __cdecl TextWindow_PrintF(TextWindow* window, const char* msg, ...);

// <LegoRR.exe @00485510>
void __cdecl TextWindow_VPrintF(TextWindow* window, unsigned long page, const char* msg, std::va_list args);

// <LegoRR.exe @004855c0>
void __cdecl TextWindow_PrintFOverlay(TextWindow* window, BOOL oneFrame, const char* msg, ...);

// <LegoRR.exe @00485650>
BOOL __cdecl TextWindow_Update(TextWindow* window, unsigned long posFromEnd, float time, OUT long* lpLowestPoint);

// <LegoRR.exe @004859d0>
BOOL __cdecl TextWindow_UpdateOverlay(TextWindow* window, float time, OUT long* lpLowestPoint);

// <LegoRR.exe @00485c70>
void __cdecl TextWindow_Clear(TextWindow* window);

// <LegoRR.exe @00485cc0>
void __cdecl TextWindow_GetInfo(TextWindow* window, OUT unsigned long* linesUsed, OUT unsigned long* linesInWindow);


//int __cdecl TextWindow_GetRow(TextWindow* window, int chrPos, int dir);
//void __cdecl TextWindow_SetFont(TextWindow* window, Font* font);

#pragma endregion

}
