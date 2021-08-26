//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Error Handler For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

// Include all Header Files

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
#include	"libgods.h"
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

Uint8	ErrorMessage[1024];

void		Error_Warn(BOOL flg, LPUCHAR msg)
{
	Error_Show(flg, msg);
}

void		Error_Debug(LPUCHAR msg)
{
	Error_Show(YES, msg);
}

void		Error_Fatal(BOOL flg, LPUCHAR msg)
{
	if(!flg) return;

	Error_Show(NO, msg);
}

Uint8*	Error_Format(LPUCHAR msg, ...)
{
	va_list	args;

	va_start	(args, msg);
	vsprintf(ErrorMessage, msg, args);
	va_end(args);
	return ErrorMessage;
}

void		Error_Show(BOOL flg, LPUCHAR msg)
{
	BOOL		wait = YES;
	Uint16	pad;

	if(!gfxGlobs.flags & GFX_FLAG_INITIALISED)
		{
		Gfx_Initialise();
		}

	while(wait)
		{
		Gfx_StartDraw();
//		Error_Box();
//		Error_Text();
		Gfx_ScreenFlip();
		if(flg)
			{
			Input_ReadPad(0);
			pad=Input_PadDebounce(0);
			if(pad & PAD_START) wait = NO;
			}
		}
}
