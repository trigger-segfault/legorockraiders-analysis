//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Input File For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ


// Include all Header Files

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
#include	"..\inc\libgods.h"
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

Input_Globs inputGlobs;

void	Input_InitPad( void )
{
	inputGlobs.flags |= GFX_FLAG_INITIALISED;
	InitPAD(&inputGlobs.Pad1, MAX_CONTROLLER_BYTES, &inputGlobs.Pad2, MAX_CONTROLLER_BYTES);
	StartPAD();
}

void	Input_ReadPad(Sint16 pad)
{
	if(pad == -1)
		{
		Input_PadRead(0x00);
		Input_PadRead(0x01);
		}
	else
		{
		Input_PadRead(pad);
		}
}

void	Input_PadRead(Sint16 pad)
{
	Uint16	tmp;

	tmp = ((pad>>4)<<2)+(pad&3);
	inputGlobs.lastPad[tmp] = inputGlobs.padData[tmp];
	if ((pad&3) == PAD_SOCKET1)
	{
		if(GoodData(&inputGlobs.Pad1) && GetType(&inputGlobs.Pad1)==STD_PAD)
		{
			inputGlobs.padData[tmp]=inputGlobs.Pad1.data.pad ^ 0xffff;
			inputGlobs.deBounce[tmp]=(inputGlobs.padData[tmp]&inputGlobs.lastPad[tmp])^inputGlobs.padData[tmp];
		}
	}
	else
	{
		if(GoodData(&inputGlobs.Pad2) && GetType(&inputGlobs.Pad2)==STD_PAD)
		{
			inputGlobs.padData[tmp]=inputGlobs.Pad2.data.pad ^ 0xffff;
			inputGlobs.deBounce[tmp]=(inputGlobs.padData[tmp]&inputGlobs.lastPad[tmp])^inputGlobs.padData[tmp];
		}
	}
}

Uint16	Input_PadData(Sint16 pad)
{
	Uint16	tmp;

	tmp = ((pad>>4)<<2)+(pad&3);
	return inputGlobs.padData[tmp];
}

Uint16	Input_PadDebounce(Sint16 pad)
{
	Uint16	tmp;

	tmp = ((pad>>4)<<2)+(pad&3);
	return inputGlobs.deBounce[tmp];
}

Uint16	msx(void)
{
	return inputGlobs.mouseX;
}

Uint16	msy(void)
{
	return inputGlobs.mouseY;
}














