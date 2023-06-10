
#include "Standard.h"
#include "Errors.h"
#include "Images.h"
#include "Files.h"
#include "Lists.h"
#include "Utils.h"
#include "Fonts.h"

#define FONT_BLINKTIME			5.0f

struct FontGlobs {

	struct List *list;
	REAL blinkTime;
	BOOL blinkOn;

} fontGlobs = { 0 };

VOID Font_Initialise(VOID) {

	fontGlobs.list = List_Create(sizeof(struct Font));
}

#ifdef _DEBUG
BOOL Font_ShutdownCallback(lpFont font, LPVOID data) {

	Error_Warn(TRUE, "Unremoved font");

	return FALSE;
}
#endif // _DEBUG

VOID Font_Shutdown(VOID) {

#ifdef _DEBUG
	List_RunThrough(fontGlobs.list, Font_ShutdownCallback, NULL);
#endif // _DEBUG
	List_Remove(fontGlobs.list);
	fontGlobs.list = NULL;
}

VOID Font_Update(REAL time) {

	fontGlobs.blinkTime += time;

	if (fontGlobs.blinkTime > FONT_BLINKTIME) {
		fontGlobs.blinkOn = !fontGlobs.blinkOn;
		fontGlobs.blinkTime -= FONT_BLINKTIME;
	}
}

VOID Font_Remove(lpFont font) {

	Image_Remove(font->image);
	List_ReturnItem(fontGlobs.list, font);
}

lpFont Font_Load(LPUCHAR fname, LPCOLOUR keyColour, BOOL texture, BOOL useShared) {

	lpFont font = List_ObtainItem(fontGlobs.list);
	ULONG width, height, loop, sub, fileSize, lineNum = 0;
	UCHAR fileName[FILE_MAXPATH];

	if (font->image = Image_Load(fname, texture, useShared)) {

		Image_GetSize(font->image, &width, &height);

		if (keyColour) Image_SetColourKey(font->image, *keyColour);

		for (loop=0 ; loop<256 ; loop++) {
			for (sub=0 ; sub<256 ; sub++) {
				font->xOffset[loop][sub] = (SCHAR) (width / 16);
			}
		}

		sprintf(fileName, "%s.dat", fname);
#ifdef _DEBUG
		sprintf(font->datFileName, "%s", fileName);
#endif // _DEBUG

		if (File_LoadBinaryTo(fileName, &fileSize, font->xOffset, sizeof(font->xOffset))) {
			Error_Fatal(fileSize != sizeof(font->xOffset), "Invalid font data file");
		}

	} else {

		List_ReturnItem(fontGlobs.list, font);
		font = NULL;

	}

	return font;
}

VOID Font_DrawCharacter(lpFont font, SLONG x, SLONG y, UCHAR c) {

	AREA2Dr srcArea, destArea;
	ULONG charWidth, charHeight;

	Image_GetSize(font->image, &charWidth, &charHeight);
	charWidth /= 16;
	charHeight /= 16;

	srcArea.x = (REAL) (charWidth * (c % 16));
	srcArea.y = (REAL) (charHeight * (c / 16));
	srcArea.width = (REAL) charWidth;
	srcArea.height = (REAL) charHeight;

	destArea.x = (REAL) x;
	destArea.y = (REAL) y;
	destArea.width = (REAL) charWidth;
	destArea.height = (REAL) charHeight;

	Image_DisplayArea(font->image, &srcArea, &destArea);
}

#ifdef _DEBUG
VOID Font_Debug_AdjustOffset(lpFont font, UCHAR aChar, UCHAR bChar, SCHAR offset) {

	font->xOffset[aChar][bChar] += offset;
}

VOID Font_Debug_SetOffset(lpFont font, UCHAR aChar, UCHAR bChar, SCHAR offset) {

	font->xOffset[aChar][bChar] = offset;
}

VOID Font_Debug_WriteDataFile(lpFont font) {

	File_SaveBinary(font->datFileName, font->xOffset, sizeof(font->xOffset));
}
#endif // _DEBUG

SLONG Font_VPrintFEx(lpFont font, ULONG x, ULONG y, SLONG cursorPos, LPUCHAR line, va_list args) {

	UCHAR buffer[1024];
	SLONG loop, length, xOffset = 0;

	Error_Fatal(NULL == font, "NULL passed as font to Font_VPrintF()");

	length = vsprintf(buffer, line, args);

	for (loop=0 ; loop<length ; loop++) {

		if (loop != cursorPos || fontGlobs.blinkOn) Font_DrawCharacter(font, x + xOffset, y, buffer[loop]);

		xOffset += font->xOffset[buffer[loop]][buffer[loop + 1]];
	}

	return length;
}

SLONG Font_VPrintF(lpFont font, SLONG x, SLONG y, LPUCHAR line, va_list args) {

	return Font_VPrintFEx(font, x, y, -1, line, args);
}

__inline SLONG Font_PrintFEx(lpFont font, SLONG x, SLONG y, SLONG cursorPos, LPUCHAR line, ...) {

	va_list args;

	va_start(args, line);
	return Font_VPrintFEx(font, x, y, cursorPos, line, args);
	va_end(args);
}

__inline SLONG Font_PrintF(lpFont font, SLONG x, SLONG y, LPUCHAR line, ...) {

	va_list args;

	va_start(args, line);
	return Font_VPrintF(font, x, y, line, args);
	va_end(args);
}


// get the height of the font
ULONG Font_GetHeight(lpFont font) {

	return (Image_GetHeight(font->image) / 16);
}


// return what the length of the text in pixels will be
ULONG Font_GetStringWidth(lpFont font, LPUCHAR line) {

	return Font_VPrintFExNoPrint(font, 0, 0, -1, line, "");
}


// same as the other print routine (nearly) - I've commented the differences
SLONG Font_VPrintFExNoPrint(lpFont font, SLONG x, SLONG y, SLONG cursorPos, LPUCHAR line, va_list args) {

	UCHAR buffer[1024];
	SLONG loop, length, xOffset = 0;

	Error_Fatal(NULL == font, "NULL passed as font to Font_GetStringWidth");

	length = vsprintf(buffer, line, args);

	for (loop=0 ; loop<length ; loop++) {

		// commented the line below out as we don't want to print the text
		//if (loop != cursorPos || fontGlobs.blinkOn) Font_DrawCharacter(font, x + xOffset, y, buffer[loop]);

		xOffset += font->xOffset[buffer[loop]][buffer[loop + 1]];
	}

	// return the xOffset instead, this gives us the total length
	return xOffset;
}
