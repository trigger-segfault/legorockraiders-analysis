
#ifndef _GODS98_FONTS_H
#define _GODS98_FONTS_H

#include "Images.h"
#include "Maths.h"

/********************************************************************************** **
 ** Fonts.h: Font Object Header for GODS
 **
 ** Copyright (C) Data Design Interactive.
 **
 **
 ** Written by Robert Wilson 28/05/98
 **
 **********************************************************************************/

/**********************************************************************************
 ******** Font Defaults and Enumeration
 **********************************************************************************/

#define FONT_MAXLISTS			32			// 2^32 - 1 possible fonts...

#define FONT_LASTCHARACTER		202			// Last character in the font image.

#define FONT_FLAG_INITIALISED	0x00000001
#define FONT_FLAG_WINDOWSET		0x00000002
#define FONT_FLAG_WINDOWWRAPPED	0x00000004

#define FONT_GRIDWIDTH			10
#define FONT_GRIDHEIGHT			19
#define FONT_MAXSTRINGLEN		1024
#define FONT_MAXIMAGEPERSTRING	10

/**********************************************************************************
 ******** Font Macros
 **********************************************************************************/

#ifdef DEBUG
	#define Font_CheckInit()			if (!(fontGlobs.flags & FONT_FLAG_INITIALISED)) Error_Fatal(TRUE, "Error: Font_Intitialise() Has Not Been Called");
#else
	#define Font_CheckInit()
#endif

/**********************************************************************************
 ******** Font Structure
 **********************************************************************************/

typedef struct Font {

	lpImage image;
	AREA2D posSet[FONT_GRIDWIDTH][FONT_GRIDHEIGHT];
	ULONG fontHeight, tabWidth;

	ULONG flags;

	struct Font *nextFree;

} Font, *lpFont;

typedef struct Font_Globs {

	Font *listSet[FONT_MAXLISTS];
	Font *freeList;

	// Global data here...

	ULONG listCount;
	ULONG flags;

} Font_Globs, *lpFont_Globs;

/**********************************************************************************
 ******** Font Prototypes
 **********************************************************************************/

#ifndef _GENPROTFILE
#include "..\Src\Fonts.prot"
#endif // _GENPROTFILE

__inline ULONG Font_GetStringWidth(lpFont font, LPUCHAR msg, ...)									{ ULONG width; va_list args; va_start(args, msg); Font_VGetStringInfo(font, &width, NULL, msg, args); va_end(args); return width; }
__inline ULONG Font_GetLineCount(lpFont font, LPUCHAR msg, ...)										{ ULONG lineCount; va_list args; va_start(args, msg); Font_VGetStringInfo(font, NULL, &lineCount, msg, args); va_end(args); return lineCount; }
__inline VOID Font_GetStringInfo(lpFont font, LPULONG width, LPULONG lineCount, LPUCHAR msg, ...)	{ va_list args; va_start(args, msg); Font_VGetStringInfo(font, width, lineCount, msg, args); va_end(args); }

#endif // _GODS98_FONTS_H
