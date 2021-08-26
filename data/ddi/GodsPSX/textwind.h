//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// TextWind.c - [Text Window Code]
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#define TEXTWINDOW_MAXSTRINGLEN			1024
#define TEXTWINDOW_MAXLINES				256

#define TEXTWINDOW_FLAG_WINDOWWRAPPED	0x00000001

typedef struct TextWindow
{
	lpFont	font;
	AREA2D	windowSize;
	LPUCHAR	windowBuffer;
	ULONG		windowBufferSize, windowBufferEnd;
	ULONG		lineList[TEXTWINDOW_MAXLINES];
	ULONG		usedLines;

	ULONG		flags;

} TextWindow, *lpTextWindow;


lpTextWindow	TextWindow_Create(lpFont font, LPAREA2D size, ULONG bufferSize);
void				TextWindow_PrintF(lpTextWindow window, LPUCHAR msg, ...);
Uint32			vsprintf(LPUCHAR buf, LPUCHAR msg, va_list args);
VOID 			TextWindow_Update(lpTextWindow window);

