
#include "..\Inc\Standard.h"
#include "..\Inc\Memory.h"
#include "..\Inc\Fonts.h"
#include "..\Inc\TextWindow.h"

int TextWindow_GetDrawPos(lpTextWindow window, ULONG chrPos, ULONG line, ULONG xpos, BOOL check);
//int TextWindow_GetDrawPos(lpTextWindow window, ULONG chrPos, ULONG line);
int TextWindow_GetNearestFromXpos(lpTextWindow window, int xPos, ULONG line);

VOID TextWindow_Initialise(VOID){


}

VOID TextWindow_Shutdown(VOID){


}

lpTextWindow TextWindow_Create(lpFont font, LPAREA2D size, ULONG bufferSize){

	lpTextWindow window;

	if (window = Mem_Alloc(sizeof(TextWindow))){
		memset(window, 0, sizeof(TextWindow));
		window->font = font;
		window->windowSize = *size;
		window->windowBuffer = Mem_Alloc(bufferSize);
		window->windowBufferSize = bufferSize;
		TextWindow_EnableCentering(window, TRUE);
	}

	return window;
}

VOID TextWindow_EnableCentering(lpTextWindow window, BOOL enable) {

	if (enable) window->flags |= TEXTWINDOW_FLAG_CENTERED;
	else window->flags &= ~TEXTWINDOW_FLAG_CENTERED;
}

VOID TextWindow_SetFont(lpTextWindow window, lpFont font)
{
	// will need  TextWindow_Update for it to take affect
	if (font == NULL)	return;
	window->font = font;
}

VOID TextWindow_Remove(lpTextWindow window){

	Mem_Free(window->windowBuffer);
	Mem_Free(window);
}

VOID TextWindow_ChangePosition( lpTextWindow window, SLONG xPos, SLONG yPos )
{
	window->windowSize.x = (REAL)xPos;
	window->windowSize.y = (REAL)yPos;

}

VOID TextWindow_ChangeSize( lpTextWindow window, ULONG width, ULONG height )
{
	window->windowSize.width = (REAL)width;
	window->windowSize.height = (REAL)height;

}

VOID TextWindow_PagePrintF(lpTextWindow window, ULONG page, LPUCHAR msg, ...) {

	va_list args;

	va_start(args, msg);
	TextWindow_VPrintF(window, page, msg, args);
	va_end(args);
}

VOID TextWindow_PrintF(lpTextWindow window, LPUCHAR msg, ...) {

	va_list args;

	va_start(args, msg);
	TextWindow_VPrintF(window, 0, msg, args);
	va_end(args);
}

VOID TextWindow_VPrintF(lpTextWindow window, ULONG page, LPUCHAR msg, va_list args) {

	UCHAR line[TEXTWINDOW_MAXSTRINGLEN];
	ULONG count, loop, onPage = 0;

	count = vsprintf(line, msg, args);

	for (loop=0 ; loop<count ; loop++) {
		if (onPage == page) break;
		if ('\a' == line[loop]) onPage++;
	}
	if (loop == count) return;			// Couldn't find the page...

	for ( ; loop<count ; loop++){
		window->windowBuffer[window->windowBufferEnd++] = line[loop];
		if (window->windowBufferEnd == window->windowBufferSize) {
			window->windowBufferEnd = 0;
			window->flags |= TEXTWINDOW_FLAG_WINDOWWRAPPED;
		}
	}

}

VOID TextWindow_PrintFOverlay( lpTextWindow window, BOOL oneFrame, LPUCHAR msg, ... )
{	UCHAR line[TEXTWINDOW_MAXSTRINGLEN];
	ULONG count;
	va_list args;


	va_start(args, msg);
	count = vsprintf(line, msg, args);
	va_end(args);

/*	if( window->secondaryBuffer )
		Mem_Free( window->secondaryBuffer );
	window->secondaryBuffer = Mem_Alloc( (sizeof(UCHAR)*count) + 1 );
*/
	strcpy( window->secondaryBuffer, line );

	if( oneFrame )
		window->displayDelay = 0;
	else
		window->displayDelay = TEXTWINDOW_DISPLAYDELAY;

	window->flags |= TEXTWINDOW_FLAG_OVERLAY;

}
/*
VOID TextWindow_Update(lpTextWindow window){

	ULONG lines = (ULONG) window->windowSize.height / window->font->fontHeight;
	ULONG used = 0, currWidth=0, currHeight, loop;
	SLONG startPoint[256] = { 0 }, start, startPos = 0, sub;
	UCHAR c;

	if (window->flags & TEXTWINDOW_FLAG_WINDOWWRAPPED) startPos = window->windowBufferEnd - window->windowBufferSize;

	for (start=window->windowBufferEnd ; start>=startPos ; start--){

		if (start > 0) c = window->windowBuffer[start-1];
		else c = window->windowBuffer[window->windowBufferSize + start - 1];

		if ('\n' == c) {
			currWidth = 0;
			startPoint[used] = start;
			if (used++ == lines) break;
		} else {
			if (isspace(c)) startPoint[used] = start;
			currWidth += Font_GetCharWidth(window->font, c);
			if (currWidth > window->windowSize.width){
				currWidth = 0;
				used++;
			}
		}
	}
	startPoint[used] = start;

	for (loop=1 ; loop<=lines ; loop++){
		currWidth = (ULONG) window->windowSize.x;
		currHeight = (ULONG) window->windowSize.y + ((lines-loop) * window->font->fontHeight);
		for (sub=startPoint[loop] ; sub<startPoint[loop-1] ; sub++){
			if (sub < 0) c = window->windowBuffer[window->windowBufferSize + sub];
			else c = window->windowBuffer[sub];
			currWidth += Font_OutputChar(window->font, currWidth, currHeight, c, TRUE);
		}
	}
}
*/

BOOL TextWindow_Update(lpTextWindow window, ULONG posFromEnd, REAL time, LPSLONG lpLowestPoint){

	ULONG loop, firstLine=0, sub;
	SLONG currWidth=0, currHeight;
	SLONG over, maxOver;
	UCHAR c;
	ULONG charWidth, wordWidth = 0;
	ULONG lineWidthList[TEXTWINDOW_MAXLINES];
	BOOL  caretFlag;

	if (lpLowestPoint) *lpLowestPoint = 0;

#pragma message( "  Slightly rarer crash bug? - to do with buffer wrap and going over buffer end?" )
	// This may be fixed, it was caused if the text size was EXACTLY 1024 bytes
	// this was messing up because it would slip past one of the == checks below.

	window->maxLines = (ULONG) window->windowSize.height / window->font->fontHeight;

	if (!(window->flags & TEXTWINDOW_FLAG_OVERLAY)) {

		maxOver = window->windowBufferSize;

		if (window->flags & TEXTWINDOW_FLAG_WINDOWWRAPPED){
			// Find the first line after the buffer end...
			for (loop=0 ; loop<window->usedLines ; loop++){
				over = window->lineList[loop] - window->windowBufferEnd;
				if (over > 0 && over < maxOver){
					firstLine = window->lineList[loop];
					maxOver = over;
				}
			}
		}

		// Rebuild the line list from the new start point...
		window->usedLines = 0;
		window->lineList[window->usedLines++] = loop = firstLine;

		while (loop != window->windowBufferEnd){
			c = window->windowBuffer[loop];
			
			if ('\a' == c) {			// use \a as a page end.
				break;
			} else if ('\n' == c) {
				window->lineList[window->usedLines] = loop + 1;
				lineWidthList[window->usedLines-1] = currWidth;
				window->usedLines++;
				currWidth = 0;
				wordWidth = 0;
			} else {
				if (isspace(c)) {
					window->lineList[window->usedLines] = loop + 1;
					lineWidthList[window->usedLines-1] = currWidth;
					wordWidth = 0;
				}
				charWidth = Font_GetCharWidth(window->font, c);
				if (c == 203) charWidth = 0;
				currWidth += charWidth;
				wordWidth += charWidth;
				if (currWidth >= window->windowSize.width) {
					// Check to see if the word is longer than the line
					if (wordWidth >= window->windowSize.width) {
						// If so, split the word onto the next line
						window->lineList[window->usedLines] = loop;
						lineWidthList[window->usedLines-1] = currWidth-charWidth;
						window->usedLines++;
						currWidth = charWidth;
						wordWidth = charWidth;
					} else {
						currWidth = wordWidth;
						window->usedLines++;
					}
				}
			}

			if (++loop >= window->windowBufferSize) loop = 0;
		}

		window->lineList[window->usedLines] = loop;
		lineWidthList[window->usedLines-1] = currWidth;

		// Display the required lines...
		if ((window->usedLines - window->maxLines + 1) > 0) posFromEnd = posFromEnd % ( window->usedLines - window->maxLines + 1 );
		else posFromEnd = 0;

		for (loop=0 ; loop<window->usedLines ; loop++){

			currWidth = (SLONG) window->windowSize.x;

			if (window->flags & TEXTWINDOW_FLAG_CENTERED) {
				currWidth += (SLONG) ((window->windowSize.width - lineWidthList[loop]) / 2);
			}

			if (window->usedLines > window->maxLines && 
				loop >= window->usedLines - window->maxLines - posFromEnd &&
				loop < window->usedLines - posFromEnd) {

				currHeight = (SLONG) window->windowSize.y + ((loop - (window->usedLines - window->maxLines - posFromEnd)) * window->font->fontHeight);
			} else if (window->usedLines <= window->maxLines) {
				currHeight = (SLONG) window->windowSize.y + (loop * window->font->fontHeight);
			} else currHeight = 0;

			if (lpLowestPoint) {
				if (currHeight > *lpLowestPoint) *lpLowestPoint = currHeight;
			}

			if (currHeight) {
			
				sub = window->lineList[loop];
				while (sub != window->lineList[loop+1]) {
					c = window->windowBuffer[sub];

					// errrrkkk!  crowbar some code in here so we can ignore the caret till the next char
					if (c == 203) 
					{
						// if we're at the caret position flag it and carry on
						caretFlag = TRUE;
					}
					else
					{
						// if caretFlag is TRUE then the char before was the caret, safe to draw it now
						if (caretFlag == TRUE)
						{
							int temp;
							// reset the caretFlag
							temp = Font_OutputChar(window->font, currWidth, currHeight, c, TRUE);
							Font_OutputChar(window->font, currWidth-4, currHeight, 203, TRUE);
							currWidth+=temp;
							caretFlag = FALSE;
						}
						else
						{
							// output our normal char
							currWidth += Font_OutputChar(window->font, currWidth, currHeight, c, TRUE);
						}
					}

					if ( ++sub == (window->windowBufferSize+1) ) sub = 0;

					if ((sub == window->lineList[loop+1]) && (caretFlag == TRUE))
					{
						Font_OutputChar(window->font, currWidth-4, currHeight, 203, TRUE);
						caretFlag = FALSE;
					}

				}

			}

		}

		if (lpLowestPoint) *lpLowestPoint += window->font->fontHeight;

		//A NON OVERLAY TEXT WINDOW CANNOT OVER RUN, IT JUST WRAPS. SO RETURN FALSE
		return FALSE;

	} else return TextWindow_UpdateOverlay( window, time, lpLowestPoint );

	//return posFromEnd;
	//return lowestPoint + window->font->fontHeight;
}


BOOL TextWindow_UpdateOverlay(lpTextWindow window, REAL time, LPSLONG lpLowestPoint) {

	ULONG sub, loop = 0, usedLines = 0;
	ULONG lineList[TEXTWINDOW_MAXLINES];
	UCHAR c;
	SLONG currWidth = 0, currHeight;
	ULONG charWidth, wordWidth = 0;
	BOOL overRun = FALSE;
	ULONG lineWidthList[TEXTWINDOW_MAXLINES];

	lineList[usedLines++] = loop;

	while ( '\0' != (c = window->secondaryBuffer[loop]) ){

		if ('\n' == c) {
			lineWidthList[usedLines-1] = currWidth;
			lineList[usedLines] = loop + 1;
			usedLines++;
			currWidth = 0;
			wordWidth = 0;
		} else {
			if (isspace(c)) {
				lineWidthList[usedLines-1] = currWidth;
				lineList[usedLines] = loop + 1;
				wordWidth = 0;
			}
			charWidth = Font_GetCharWidth(window->font, c);
			currWidth += charWidth;
			wordWidth += charWidth;
			if (currWidth > window->windowSize.width) {
				currWidth = wordWidth;
				usedLines++;
			}
		}

		loop++;

	}

	lineWidthList[usedLines-1] = currWidth;
	lineList[usedLines] = loop;

	for (loop=0 ; loop<usedLines ; loop++){

		currWidth = (SLONG) window->windowSize.x;
		if (window->flags & TEXTWINDOW_FLAG_CENTERED) {
			currWidth += (SLONG) ((window->windowSize.width - lineWidthList[loop]) / 2);
		}

		if (usedLines > window->maxLines && 
			loop >= usedLines - window->maxLines &&
			loop < usedLines )
		{
			currHeight = (SLONG) window->windowSize.y + ((loop - (usedLines - window->maxLines)) * window->font->fontHeight);
			overRun = TRUE;
		}
		else if (usedLines <= window->maxLines)
			currHeight = (SLONG) window->windowSize.y + (loop * window->font->fontHeight);
		else currHeight = 0;

		if( lpLowestPoint )
		{
			if( currHeight > *lpLowestPoint )
				*lpLowestPoint = currHeight;
		}

		if (currHeight) {
		
			sub = lineList[loop];
			while (sub != lineList[loop+1]) {
				c = window->secondaryBuffer[sub++];
				currWidth += Font_OutputChar(window->font, currWidth, currHeight, c, TRUE);
			}

		}

	}

	if( (window->displayDelay -= time) < 0 )
		window->flags &= ~TEXTWINDOW_FLAG_OVERLAY;

	return overRun;
}


VOID TextWindow_Clear( lpTextWindow window )
{
	memset( window->windowBuffer, 0, window->windowBufferSize );
	memset( window->secondaryBuffer,0,TEXTWINDOW_MAXSTRINGLEN);
	window->usedLines = 0;
	window->windowBufferEnd = 0;
	window->flags &= ~TEXTWINDOW_FLAG_WINDOWWRAPPED;

}


VOID TextWindow_GetInfo( lpTextWindow window, LPULONG linesUsed, LPULONG linesInWindow )
{
	*linesUsed = window->usedLines;
	*linesInWindow = window->maxLines;

}


int TextWindow_GetRow(lpTextWindow window, int chrPos, int dir)
{
ULONG loop, newRow;
int xpos1, xpos2;

	for (loop = 0 ; loop < window->maxLines-1 ; loop++)
	{
		if (((ULONG)chrPos >= window->lineList[loop]) && ((ULONG)chrPos < window->lineList[loop+1]))
		{
			newRow = loop+dir;

			if (newRow < 0)						return chrPos;
			if (newRow >= window->maxLines)	return chrPos;

			// I know what row we want.  Need to find out the drawPos of the 2 rows.
			xpos1 = TextWindow_GetDrawPos(window, chrPos, loop, 0, TRUE);
			xpos2 = TextWindow_GetDrawPos(window, chrPos, newRow, xpos1, FALSE);

			if (dir > 0) return xpos2-1;
			return xpos2;
		}
	}
return 0;
}

int TextWindow_GetDrawPos(lpTextWindow window, ULONG chrPos, ULONG line, ULONG xpos, BOOL check)
{
ULONG firstLine=0, sub;
SLONG currWidth=0, currHeight;
UCHAR c;
ULONG wordWidth = 0;
ULONG lineWidthList[TEXTWINDOW_MAXLINES];
ULONG posFromEnd = 0;
int		diff = 9999999;
int		charPos = 0;

	// Display the required lines...
	if ((window->usedLines - window->maxLines + 1) > 0) posFromEnd = posFromEnd % ( window->usedLines - window->maxLines + 1 );
	else posFromEnd = 0;

	currWidth = (SLONG) window->windowSize.x;

	if (window->flags & TEXTWINDOW_FLAG_CENTERED) 
	{
		currWidth += (SLONG) ((window->windowSize.width - lineWidthList[line]) / 2);
	}

	if (window->usedLines > window->maxLines && 
		line >= window->usedLines - window->maxLines - posFromEnd &&
		line < window->usedLines - posFromEnd) 
	{
		currHeight = (SLONG) window->windowSize.y + ((line - (window->usedLines - window->maxLines - posFromEnd)) * window->font->fontHeight);
	} else if (window->usedLines <= window->maxLines) {
		currHeight = (SLONG) window->windowSize.y + (line * window->font->fontHeight);
	} else currHeight = 0;

	if (currHeight) 
	{
		sub = window->lineList[line];
		while (sub != window->lineList[line+1]) 
		{
			c = window->windowBuffer[sub];

			if (check == TRUE)
			{
				if (sub == chrPos)	return currWidth;
			}
			else
			{
				if (abs(currWidth-xpos) < diff) 
				{
					diff = abs(currWidth-xpos);
					charPos = sub;
				}
			}

			currWidth += Font_GetCharWidth(window->font, c);

			if ( ++sub == (window->windowBufferSize+1) ) sub = 0;
		}
	}
return charPos;
}

