
#ifndef _RGL_FONTS_H_
#define _RGL_FONTS_H_

#include "Files.h"

struct Font {

	struct Image *image;
	SCHAR xOffset[256][256];

#ifdef _DEBUG
	UCHAR datFileName[FILE_MAXPATH];
#endif // _DEBUG
};

typedef struct Font			*lpFont;


#ifndef _AUTOPROTOTYPES
// Auto Prototypes
extern VOID __cdecl Font_Initialise(VOID);
extern VOID __cdecl Font_Update(REAL time);
extern lpFont __cdecl Font_Load(LPUCHAR fname, LPCOLOUR keyColour, BOOL texture, BOOL useShared);
extern VOID __cdecl Font_Debug_AdjustOffset(lpFont font, UCHAR aChar, UCHAR bChar, SCHAR offset);
extern VOID __cdecl Font_Debug_SetOffset(lpFont font, UCHAR aChar, UCHAR bChar, SCHAR offset);
extern VOID __cdecl Font_Debug_WriteDataFile(lpFont font);
extern VOID __cdecl Font_DrawCharacter(lpFont font, SLONG x, SLONG y, UCHAR c);
extern SLONG __cdecl Font_VPrintF(lpFont font, SLONG x, SLONG y, LPUCHAR line, va_list args);
extern SLONG __cdecl Font_PrintF(lpFont font, SLONG x, SLONG y, LPUCHAR line, ...);
extern SLONG __cdecl Font_PrintFEx(lpFont font, SLONG x, SLONG y, SLONG cursorPos, LPUCHAR line, ...);
extern void __cdecl Font_Remove(lpFont font);
extern ULONG __cdecl Font_GetHeight(lpFont font);
extern ULONG __cdecl Font_GetStringWidth(lpFont font, LPUCHAR line);
extern SLONG __cdecl Font_VPrintFExNoPrint(lpFont font, SLONG x, SLONG y, SLONG cursorPos, LPUCHAR line, ...);
extern VOID __cdecl Font_Shutdown(VOID);
// Auto Prototypes
#endif // !_AUTOPROTOTYPES

#endif // !_RGL_FONTS_H_
