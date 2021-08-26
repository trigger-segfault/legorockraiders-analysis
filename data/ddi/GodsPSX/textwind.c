//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Text Window File For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

// Include all Header Files

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
#include	"libgods.h"
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

TextWindow	textWindowGlobs;

void	TextWindow_Initialise(void)
{
}

lpTextWindow TextWindow_Create(lpFont font, LPAREA2D size, ULONG bufferSize)
{
	lpTextWindow window;

	if (window = Mem_Malloc(sizeof(TextWindow)))
		{
		memset((LPUCHAR)window, 0, sizeof(TextWindow));
		window->font = font;
		window->windowSize = *size;
		window->windowBuffer = Mem_Malloc(bufferSize);
		window->windowBufferSize = bufferSize;
		}
	return window;
}

void TextWindow_PrintF(lpTextWindow window, LPUCHAR msg, ...)
{
	UCHAR line[TEXTWINDOW_MAXSTRINGLEN];
	ULONG count, loop;
	va_list args;

	va_start(args, msg);
	count = vsprintf(line, msg, args);
//	count = sprintf(line, msg, args);
	va_end(args);

	for (loop=0 ; loop<count ; loop++)
		{
		window->windowBuffer[window->windowBufferEnd++] = line[loop];
		if (window->windowBufferEnd == window->windowBufferSize)
			{
			window->windowBufferEnd = 0;
			window->flags |= TEXTWINDOW_FLAG_WINDOWWRAPPED;
			}
		}
}


Uint32	vsprintf(LPUCHAR buf, LPUCHAR msg, va_list args)
{
	Uint32	len, size=0;
	UCHAR		c;
	LPUCHAR	temp;
	UCHAR		string[64];

//	va_start(args, msg);

	while(c = *msg++)
		{
		if(c!='%') buf[size++]=c;
		else
			{
			c = *msg++;
			switch(c)
				{
				case	's':
						temp=va_arg(args, LPUCHAR);
						len = strlen(temp);
						memcpy(&buf[size], temp, len);
						size+=len;
						break;

				case	'd':
						len=va_arg(args, ULONG);
						sprintf(string,"%d",len);
						len = strlen(string);
						memcpy(&buf[size], string, len);
						size+=len;
						break;

				case	'x':
						len=va_arg(args, ULONG);
						sprintf(string,"%x",len);
						len = strlen(string);
						memcpy(&buf[size], string, len);
						size+=len;
						break;
				}
			}
		}
	va_end(args);
	return size;
}

VOID TextWindow_Update(lpTextWindow window)
{

	ULONG loop, firstLine=0, currWidth=0, currHeight, sub;
	ULONG maxLines = (ULONG) window->windowSize.height / window->font->height;
	SLONG over, maxOver;
	UCHAR c;

	maxOver = window->windowBufferSize;

	if (window->flags & TEXTWINDOW_FLAG_WINDOWWRAPPED)
		{
		// Find the first line after the buffer end...
		for (loop=0 ; loop<window->usedLines ; loop++)
			{
			over = window->lineList[loop] - window->windowBufferEnd;
			if (over > 0 && over < maxOver)
				{
				firstLine = window->lineList[loop];
				maxOver = over;
				}
			}
		}

	// Rebuild the line list from the new start point...
	window->usedLines = 0;
	window->lineList[window->usedLines++] = loop = firstLine;

	while (loop != window->windowBufferEnd)
		{
		c = window->windowBuffer[loop];
		
		if ('\n' == c)
			{
			window->lineList[window->usedLines++] = (loop + 1) % window->windowBufferSize;
			currWidth = 0;
			}
		else
			{
			if (isspace(c)) window->lineList[window->usedLines] = (loop + 1) % window->windowBufferSize;
			currWidth += Font_GetCharWidth(window->font, c);
			if (currWidth > window->windowSize.width)
				{
				currWidth = 0;
				window->usedLines++;
				}
			}
		if (++loop == window->windowBufferSize) loop = 0;
		}

	if ('\n' != c) window->usedLines++;

	// Display the required lines...

	for (loop=0 ; loop<(window->usedLines-1) ; loop++)
		{
		currWidth = (ULONG) window->windowSize.x;
		if (window->usedLines > maxLines && loop >= (window->usedLines-1) - maxLines)
			{
//			currHeight = (ULONG) (window->windowSize.y + window->windowSize.height) - (((window->usedLines-1) - loop) * window->font->height);
			currHeight = (ULONG) window->windowSize.y + ((loop - ((window->usedLines-1) - maxLines)) * window->font->height);
			}
		else if (window->usedLines <= maxLines)
			{
			currHeight = (ULONG) window->windowSize.y + (loop * window->font->height);
			}
		else currHeight = 0;

		if (currHeight)
			{
			sub = window->lineList[loop];
			while (sub != window->lineList[loop+1])
				{
				c = window->windowBuffer[sub];
				currWidth += Font_OutputChar(window->font, currWidth, currHeight, c, TRUE);
				if (++sub == window->windowBufferSize) sub = 0;
				}
			}
		}
}

















