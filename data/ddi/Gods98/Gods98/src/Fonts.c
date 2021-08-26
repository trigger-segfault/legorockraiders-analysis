/**********************************************************************************
 **
 ** Font.c: Font Object Code For GODS
 **
 ** Copyright (C) Data Design Interactive.
 **
 **
 ** Written by Robert Wilson 20/01/98
 **
 **********************************************************************************/


#include "..\inc\Standard.h"

#include "..\inc\Errors.h"
#include "..\inc\Memory.h"
#include "..\inc\Fonts.h"

/**********************************************************************************
 ******** Font Global Data
 **********************************************************************************/

static Font_Globs fontGlobs;

/**********************************************************************************
 ******** Font Global Library Functions
 **********************************************************************************/

VOID Font_Initialise(VOID){
	
	ULONG loop;

	for (loop=0 ; loop<FONT_MAXLISTS ; loop++){
		fontGlobs.listSet[loop] = NULL;
	}

	fontGlobs.freeList = NULL;
	fontGlobs.listCount = 0;
	fontGlobs.flags = FONT_FLAG_INITIALISED;
}

VOID Font_Shutdown(VOID){

	ULONG loop;

	Font_RunThroughLists(Font_RemoveCallback, NULL);

	for (loop=0 ; loop<FONT_MAXLISTS ; loop++){
		if (fontGlobs.listSet[loop]) Mem_Free(fontGlobs.listSet[loop]);
	}

	fontGlobs.freeList = NULL;
	fontGlobs.flags = 0x00000000;
}

lpFont Font_Load(LPUCHAR fname){

	lpImage image;
	lpFont font;
	ULONG x, y, width, height, pitch, bpp;
	LPAREA2D pos;
	LPUCHAR buffer;
	ULONG pen255, mask, xBack, dw, loc;

	if (image = Image_LoadBMP(fname)){
		if (font = Font_Create(image)){
			Image_SetPenZeroTrans(image);
			width = Image_GetWidth(image) / FONT_GRIDWIDTH;
			height = Image_GetHeight(image) / FONT_GRIDHEIGHT;

			pen255 = Image_GetPen255(image);
			mask = Image_GetPixelMask(image);

			if (buffer = Image_LockSurface(image, &pitch, &bpp)){
				for (y=0 ; y<FONT_GRIDHEIGHT ; y++){
					for (x=0 ; x<FONT_GRIDWIDTH ; x++){
						pos = &font->posSet[x][y];
						pos->x = (REAL) (width * x);
						pos->y = (REAL) (height * y);
						pos->width = (REAL) width;
						pos->height = (REAL) height;

						// Pull back the width while the pixel on the end is pen255...

						for (xBack=width-1 ; xBack ; xBack--){
							loc = pitch * (ULONG) pos->y;					// Get the start of the line...
							loc += (ULONG) (pos->x+xBack) * (bpp/8);		// Get the end of the current character	
							dw = buffer[loc] << 24;
							dw |= buffer[loc+1] << 16;
							dw |= buffer[loc+2] << 8;
							dw |= buffer[loc+3];
							if ((dw & mask) == pen255)
								pos->width--;
							else break;
						}
					}
				}

				font->fontHeight = (ULONG) font->posSet[0][0].height;
				font->tabWidth = (ULONG) font->posSet[0][0].width * 8;

				// Clean up an return...
				Image_UnlockSurface(image);
				return font;

			}
			Font_Remove(font);
		}
		Image_Remove(image);
	}

	return NULL;
}

VOID Font_SetTabWidth(lpFont font, ULONG width, BOOL spaces){

	if (spaces) font->tabWidth = (ULONG) font->posSet[0][0].width * width;
	else font->tabWidth = width;
}

VOID Font_VGetStringInfo(lpFont font, LPULONG width, LPULONG lineCount, LPUCHAR msg, va_list args){

	ULONG w = Font_VPrintF2(font, 0, 0, FALSE, lineCount, msg, args);
	if (width) *width = w;
}

ULONG Font_PrintF(lpFont font, SLONG x, SLONG y, LPUCHAR msg, ...){

	va_list args;
	ULONG width;

	va_start(args, msg);
	width = Font_VPrintF2(font, x, y, TRUE, NULL, msg, args);
	va_end(args);

	return width;
}

ULONG Font_VPrintF(lpFont font, SLONG x, SLONG y, LPUCHAR msg, va_list args){

	return Font_VPrintF2(font, x, y, TRUE, NULL, msg, args);
}

static ULONG Font_VPrintF2(lpFont font, SLONG x, SLONG y, BOOL render, LPULONG lineCount, LPUCHAR msg, va_list args){

	UCHAR line[FONT_MAXSTRINGLEN], line2[FONT_MAXSTRINGLEN];
	ULONG width, loop, lines = 1;
	ULONG xPos = 0, xMax = 0, yIncrease = font->fontHeight;
	lpImage image;
	LPUCHAR s, t;

	// '%b' in the string refers to an image...
	// Change '%b' to the sequence @[0x<address>]...
	for (t=line2,s=msg ; '\0'!=*s ; s++,t++) {
		Error_Fatal('@'==*s&&'['==*(s+1), "Invalid character sequence in string");
		if ('%' == *s && 'b' == *(s+1)) {
			*t++ = '@';	*t++ = '[';	*t++ = '0';	*t++ = 'x';	*t++ = '%';
			*t++ = '0';	*t++ = '.';	*t++ = '8';	*t++ = 'x';	*t = ']';
			s++;
		} else *t = *s;
	}
	*t = '\0';

	width = vsprintf(line, line2, args);

	for (loop=0 ; loop<width ; loop++) {
		if ('\n' == line[loop]){
			if (xPos > xMax) xMax = xPos;
			xPos = 0;
			y += yIncrease;
			yIncrease = font->fontHeight; 
			lines++;
		} else if ('\t' == line[loop]) {
			xPos += font->tabWidth - (xPos % font->tabWidth);
		} else if (loop < width - 12 && '@' == line[loop] && '[' == line[loop+1] && '0' == line[loop+2] && 'x' == line[loop+3] && ']' == line[loop+12]) {
			ULONG addr = 0, sub;
			VECTOR2D pos;
			for (sub=0 ; sub<8 ; sub++) addr |= (line[loop+4+sub] - (isdigit(line[loop+4+sub])?'0':('a'-10))) << (28 - (sub * 4));
			if (image = (lpImage) addr) {
				pos.x = (REAL) (x + xPos);
				pos.y = (REAL) y;

				if (line[loop] != 203)		xPos += image->width;

				if (image->height > yIncrease) yIncrease = image->height;
				Image_Display(image, &pos);
			}
			loop += 12;
		} else {
			ULONG fontWidth = Font_OutputChar(font, x + xPos, y, line[loop], render);

			if (line[loop] != 203)
			{
				xPos+=fontWidth;
			}
		}
	}
	if (lineCount) *lineCount = lines;
	return xPos>xMax?xPos:xMax;
}

ULONG Font_OutputChar(lpFont font, SLONG x, SLONG y, UCHAR c, BOOL render){

	ULONG gx, gy;
	VECTOR2D pos = { (REAL) x, (REAL) y };

	c -= 32;
	gy = c / FONT_GRIDWIDTH;
	gx = c % FONT_GRIDWIDTH;

	if (gy < FONT_GRIDHEIGHT){
		if (render) Image_DisplayScaled(font->image, &font->posSet[gx][gy], &pos, NULL);
		return (ULONG) font->posSet[gx][gy].width;
	}

	return 0;
}

ULONG Font_GetCharWidth(lpFont font, UCHAR c){

	return Font_OutputChar(font, 0, 0, c, FALSE);
}

ULONG Font_GetHeight(lpFont font){

	return font->fontHeight;
}

VOID Font_Remove(lpFont dead){

	Font_CheckInit();
	Error_Fatal(!dead, "NULL passed to Font_Remove()");

	Image_Remove(dead->image);

	dead->nextFree = fontGlobs.freeList;
	fontGlobs.freeList = dead;
}

VOID Font_GetBackgroundColour(lpFont font, LPREAL r, LPREAL g, LPREAL b){

	Image_GetPenZero(font->image, r, g, b);
}

/**********************************************************************************
 ******** Font Static Functions
 **********************************************************************************/

static lpFont Font_Create(lpImage image){

	lpFont newFont;

	Font_CheckInit();

	if (NULL == fontGlobs.freeList) Font_AddList();
	
	newFont = fontGlobs.freeList;
	fontGlobs.freeList = newFont->nextFree;
	memset(newFont, 0, sizeof(Font));
	newFont->nextFree = newFont;

	newFont->image = image;

	return newFont;
}

static VOID Font_RemoveCallback(lpFont font, LPVOID data){

	Font_Remove(font);
}

static VOID Font_AddList(VOID){

	lpFont list;
	ULONG loop, count;

	Font_CheckInit();

	Error_Fatal(fontGlobs.listCount+1 >= FONT_MAXLISTS, "Run out of lists");

	count = 0x00000001 << fontGlobs.listCount;

	if (list = fontGlobs.listSet[fontGlobs.listCount] = 
		Mem_Alloc(sizeof(Font) * count)){

		fontGlobs.listCount++;

		for (loop=1 ; loop<count ; loop++){

			list[loop-1].nextFree = &list[loop];
		}
		list[count-1].nextFree = fontGlobs.freeList;
		fontGlobs.freeList = list;

	} else Error_Fatal(TRUE, Error_Format("Unable to allocate %d bytes of memory for new list.\n", sizeof(Font) * count));
}

static VOID Font_RunThroughLists(VOID (*Callback)(lpFont font, LPVOID data), LPVOID data){

	ULONG list, count, loop;
	lpFont tempFont;

	for (list=0 ; list<fontGlobs.listCount ; list++){
		if (fontGlobs.listSet[list]){
			count = 0x00000001 << list;
			for (loop=0 ; loop<count ; loop++){
				if (tempFont = &fontGlobs.listSet[list][loop]){
					if (tempFont->nextFree == tempFont){

						// This is a valid unremoved font....
						Callback(tempFont, data);
	
					}
				}
			}
		}
	}
}
