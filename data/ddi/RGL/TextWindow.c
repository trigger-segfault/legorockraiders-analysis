
#include <string.h>
#include <ctype.h>
#include <d3drmwin.h>

#include "Standard.h"

#include "Errors.h"
#include "Mem.h"
#include "Maths.h"
#include "Utils.h"
#include "Files.h"
#include "Config.h"
#include "Main.h"
#include "Fonts.h"
#include "TextWindow.h"

// *******************************************************************************************************************
void TextWindow_Clear(lpTextWindow window)
{
}

// *******************************************************************************************************************
void TextWindow_PrintF(lpTextWindow window, LPUCHAR msg, ...) 
{
}

// *******************************************************************************************************************
BOOL TextWindow_Update(lpTextWindow window, ULONG posFromEnd, REAL time, LPSLONG lpLowestPoint)
{
return FALSE;
}

// *******************************************************************************************************************
lpTextWindow TextWindow_Create(lpFont font, LPAREA2Dr size, ULONG bufferSize)
{
lpTextWindow window;

	if (window = Mem_Alloc(sizeof(window)))
	{
		memset(window, 0, sizeof(window));
	}

return window;
}

// *******************************************************************************************************************
void TextWindow_SetFont(lpTextWindow window, lpFont font)
{
	if (font == NULL)	return;
}

// *******************************************************************************************************************
int TextWindow_GetRow(lpTextWindow window, int chrPos, int dir)
{
return 0;
}

// *******************************************************************************************************************
void TextWindow_EnableCentering(lpTextWindow window, BOOL enable) 
{
}

// *******************************************************************************************************************
void TextWindow_Remove(lpTextWindow window)
{
}

// *******************************************************************************************************************
// *******************************************************************************************************************
// *******************************************************************************************************************




