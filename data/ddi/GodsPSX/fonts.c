//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Font File For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

// Include all Header Files

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
#include	"libgods.h"
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

Font_Globs fontGlobs;


#define		FLASH_MASK		(0x8)

/* SteveD

	added support for:
			proportional fonts
			variable sized grids
			colour selection
			flashing
	to do:
			alpha	control

	removed variable length list stuff.

*/

	static	COLOUR_BANK colour_bank[]=
	{
		{0,0,0},						/* black */
		{255,0,0},					/* red */
		{0,255,0},					/* green */
		{255,255,0},				/* yellow */
		{0,0,255},					/* blue */
		{255,0,255},				/* magenta */
		{0,255,255},				/* cyan */
		{255,255,255},				/* white */

		{0,0,0},						/* half bright */
		{128,0,0},
		{0,128,0},
		{128,128,0},
		{0,0,128},
		{128,0,128},
		{0,128,128},
		{128,128,128},
	};

/*
	set fonts colour at fade level
*/
void	Font_set_colour_fade(lpFont font, Uint16 red, Uint16 green, Uint16 blue)
{
	REAL	fade=gfxGlobs.fadeLevel<<4;

	font->red=FromFIXED(Asm_MulFIX(ToFIXED(red),fade));
	font->green=FromFIXED(Asm_MulFIX(ToFIXED(green),fade));
	font->blue=FromFIXED(Asm_MulFIX(ToFIXED(blue),fade));

}

/* set colour ignoring fade level */
void	Font_set_colour(lpFont font, Uint16 red, Uint16 green, Uint16 blue)
{
	font->red=red;
	font->green=green;
	font->blue=blue;
}

/*
	set fonts colour at fade level
*/
void	Font_set_colourbank_fade(lpFont font, Uint16 bank)
{
	REAL	fade=gfxGlobs.fadeLevel<<4;

	font->red=FromFIXED(Asm_MulFIX(ToFIXED(colour_bank[bank].red),fade));
	font->green=FromFIXED(Asm_MulFIX(ToFIXED(colour_bank[bank].green),fade));
	font->blue=FromFIXED(Asm_MulFIX(ToFIXED(colour_bank[bank].blue),fade));

}

/* set colour ignoring fade level */
void	Font_set_colourbank(lpFont font, Uint16 bank)
{
	font->red=colour_bank[bank].red;
	font->green=colour_bank[bank].green;
	font->blue=colour_bank[bank].blue;
}



void Font_Initialise(void)
{
	ULONG loop;

	for (loop=0 ; loop<FONT_MAXFONTS ; loop++)
	{
		fontGlobs.listSet[loop] = NULL;
	}

	fontGlobs.listCount = 0;
	fontGlobs.flags = FONT_FLAG_INITIALISED;
}

/*
	this has to reload the image data at present, though it could
	be read back from VRAM I  suppose

	To do:	check for .wid file of the same name, and load instead of
				calculating the table.

*/
void	generate_width_table(LPUCHAR fname, lpFont font, int gridwidth, int gridheight)
{

	LPUCHAR		buffer;
	TIM_IMAGE	tim;
	Uint32		size;
	UCHAR			*char_start;
	char			new_name[128];
	int			next_char=0;
	int			image_width,image_height;
	int			sprite_width,sprite_height;
	int			x,y,cx,cy;
	char			width;

	strcpy(new_name,fname);
	strcpy(new_name+(strlen(fname)-3),"WID");

	if(buffer = File_LoadBinary(fname, &size))
	{
		OpenTIM((Uint32*)buffer);
		ReadTIM(&tim);

		if ((tim.mode&7)==0)
			image_width=tim.prect->w*4;
		else
			image_width=tim.prect->w*2;

		image_height=tim.prect->h;

		sprite_width=image_width/gridwidth;
		sprite_height=image_height/gridheight;

		for (y=0; y<gridheight; y++)
		{
			for (x=0; x<gridwidth; x++)
			{
				char_start=(UCHAR*) tim.paddr;
				char_start+=((y*sprite_height)*(image_width>>1))+(x*(sprite_width>>1));

				width=0;
				for (cy=0; cy<sprite_height; cy++)
				{
					for (cx=0; cx<(sprite_width>>1); cx++)
					{
						if (char_start[cx]&0x0f)
						{
							if ((cx*2)+1>width)
								width=(cx*2)+1;
						}
						else if (char_start[cx]&0xf0)
						{
							if ((cx*2)>width)
								width=(cx*2);
						}
					}
					char_start+=(image_width>>1);
				}

				if (width==0)		/* space char, give it a default width */
					width=4;

				font->width_table[next_char++]=width+2;
			}
		}

		Mem_Free(buffer);
	}
}



/*
	added width/height parameters
	width==0 means use proportional settings
*/
lpFont	Font_Load(LPUCHAR fname, int width, int height, int gridwidth, int gridheight)
{
	lpImage	image;
	lpFont	font;
	LPPOS2D	pos;
	Uint16	x, y;
	Uint8		u, v;
	Uint16	sprite_width,sprite_height;

	if (image = Image_LoadTIM(fname))
	{
		if (font = Font_Create(image))
		{
			font->uvTable=(POS2D*) Mem_Malloc(gridwidth*gridheight*sizeof(POS2D));
			pos=font->uvTable;
			sprite_width=image->width/gridwidth;
			sprite_height=image->height/gridheight;

			for (y=0; y<gridheight; y++)
			{
				for (x=0; x<gridwidth; x++)
				{
					pos->x=(image->u+(x*sprite_width));
					pos->y=(image->v+(y*sprite_height));
					pos++;
				}
			}

			font->width = width;
			font->height = height;
			font->tabWidth = sprite_width*8;

			/* if the font width is zero then we generate width data */

			if (width==0)
			{
				font->width_table=Mem_Malloc(gridwidth*gridheight);
				font->width = sprite_width;
				font->flags|=FONT_FLAG_PROPORTIONAL;
				generate_width_table(fname,font,gridwidth,gridheight);				
			}
		}
	}
	return font;
}


lpFont	Font_Create(lpImage image)
{
	lpFont	newFont;
	int		n;

	for (n=0; n<FONT_MAXFONTS; n++)
	{
		if (!fontGlobs.listSet[n])
		{
			newFont=fontGlobs.listSet[n]=Mem_Malloc(sizeof(Font));
			memset((LPUCHAR)newFont, NULL, sizeof(Font));
			newFont->image=image;
			return newFont;
		}
	}
	printf("No space for a font in Font_Create\n");
	return	NULL;		/* no space for font */
}

void Font_Remove(lpFont font)
{
	int n;
	
	for (n=0; n<FONT_MAXFONTS; n++)
	{
		if (fontGlobs.listSet[n] == font)
		{
			Image_Remove(font->image);
			Mem_Free(font->uvTable);
			Mem_Free(font->width_table);
			Mem_Free(font);
			fontGlobs.listSet[n]=NULL;
			return;
		}
	}
}

ULONG	Font_GetStringWidth(lpFont font, ULONG x, ULONG y, LPUCHAR msg, ...)
{
	UCHAR line[TEXTWINDOW_MAXSTRINGLEN];
	ULONG count;
	va_list args;

	va_start(args, msg);
	count = Font_VPrintF(font, x, y, FALSE, msg, args);
	va_end(args);

	return count;
}


ULONG	Font_PrintF(lpFont font, ULONG x, ULONG y, LPUCHAR msg, ...)
{
	UCHAR line[TEXTWINDOW_MAXSTRINGLEN];
	ULONG count;
	va_list args;

	va_start(args, msg);
	count = Font_VPrintF(font, x, y, TRUE, msg, args);
	va_end(args);

	return count;
}

BOOL	FONT_DebugPrint(BOOL flag)
{
	fontGlobs.debugPrint = flag;
}

ULONG	Font_PrintFD(lpFont font, ULONG x, ULONG y, LPUCHAR msg, ...)
{
	ULONG ret = 0;
	if(fontGlobs.debugPrint)
		ret = Font_PrintF(font, x, y, msg);
	return ret;
}

ULONG Font_VPrintF(lpFont font, ULONG x, ULONG y, BOOL render, LPUCHAR msg, va_list args)
{
	UCHAR 	line[FONT_MAXSTRINGLEN];
	ULONG 	xPos = 0, xMax = 0, width, loop;
	Uint16	bank;
	Uint8		code;

	width = vsprintf(line, msg, args);

/* this should be adjusted for the current viewport */

	x-=(gfxGlobs.scrW>>1);
	y-=(gfxGlobs.scrH>>1);

	Font_set_colourbank_fade(font,CB_WHITE);
	font->flash_flag=FALSE;

	for (loop=0 ; loop<width ; loop++)
	{
		if ('\n' == line[loop])
		{
			if (xPos > xMax) xMax = xPos;
			xPos = 0;
			y += font->height;
		}
		else if ('\t' == line[loop])
		{
			xPos += font->tabWidth - (xPos % font->tabWidth);
		}
		else
		{
			if (line[loop]=='|')
			{
				loop++;
				code=line[loop];

				if (code=='f')
					font->flash_flag^=1;
				else
				{
					Font_set_colourbank_fade(font,code-'0');
				}							
			}
			else
				xPos += Font_OutputChar(font, x + xPos, y, line[loop], render);
		}
	}
	return xPos>xMax?xPos:xMax;
}


/*
	new char output routine
*/
ULONG Font_OutputChar(lpFont font, ULONG x, ULONG y, UCHAR c, BOOL render)
{
	GsSPRITE	s;

	if ((!font->flash_flag) || (font->flash_count & FLASH_MASK))
	{

		c -= 32;
		/* modify for colour change */
		s.r = font->red;
		s.g = font->green;
		s.b = font->blue;

		s.x = x;
		s.y = y;
		s.u = font->uvTable[c].x;
		s.v = font->uvTable[c].y;
		s.w = font->width;
		s.h = font->height;
		s.tpage = font->image->tPage;
		s.cx = font->image->cx;
		s.cy = font->image->cy;
		s.mx = s.my = s.rotate = NULL;
		s.scalex = s.scaley = ONE;
		s.attribute = font->image->attribute;
		GsSortFastSprite(&s, &gfxGlobs.Wot[gfxGlobs.bufID], 9);
	}
	if (font->flags & FONT_FLAG_PROPORTIONAL)
		return (ULONG) font->width_table[c];
	else
		return (ULONG) font->width;
}


ULONG Font_GetCharWidth(lpFont font, UCHAR c)
{

	if (font->flags & FONT_FLAG_PROPORTIONAL)
		return font->width_table[c-32];
	else
		return font->width;
}




void	Font_update_flash(lpFont font)
{
	font->flash_count++;
}

// added by ScottN
ULONG FONT_GetStringWidth(lpFont font, UCHAR *text)
{
UCHAR 	line[FONT_MAXSTRINGLEN];
ULONG 	xPos = 0, xMax = 0, width, loop;
Uint16	bank;
Uint8	code;

	// eeeek!  don't bother error checking here.  Hope text is not longer the FONT_MAXSTRINGLEN
	width = strlen(text);
	strcpy(line, text);

	for (loop=0 ; loop<width ; loop++)
	{
		if ('\n' == line[loop])
		{
		}
		else if ('\t' == line[loop])
		{
			xPos += font->tabWidth - (xPos % font->tabWidth);
		}
		else
		{
			if (line[loop]=='|')
			{
				loop++;
				code=line[loop];

				if (code=='f')
					font->flash_flag^=1;
				else
				{
					Font_set_colourbank_fade(font,code-'0');
				}							
			}
			else
				xPos += Font_GetCharWidth(font,  line[loop]);

		}
	}
return xPos;
}

// BEGIN ScottN
// Need a Font function that will output an r,g,b colour char
// *******************************************************************************************************
ULONG	Font_RGBPrintF(lpFont font, ULONG x, ULONG y, UCHAR r, UCHAR g, UCHAR b, ULONG s, LPUCHAR msg, ...)
{
	UCHAR line[TEXTWINDOW_MAXSTRINGLEN];
	ULONG count;
	va_list args;

	va_start(args, msg);
	count = Font_RGBVPrintF(font, x, y, TRUE, msg, args, r, g, b, s);
	va_end(args);

	return count;
}

// *******************************************************************************************************
ULONG Font_RGBVPrintF(lpFont font, ULONG x, ULONG y, BOOL render, LPUCHAR msg, va_list args, UCHAR r, UCHAR g, UCHAR b, ULONG s)
{
	UCHAR 	line[FONT_MAXSTRINGLEN];
	ULONG 	xPos = 0, xMax = 0, width, loop;
	Uint16	bank;
	Uint8		code;

	width = vsprintf(line, msg, args);

/* this should be adjusted for the current viewport */

	x-=(gfxGlobs.scrW>>1);
	y-=(gfxGlobs.scrH>>1);

	Font_set_colourbank_fade(font,CB_WHITE);
	font->flash_flag=FALSE;

	for (loop=0 ; loop<width ; loop++)
	{
		if ('\n' == line[loop])
		{
			if (xPos > xMax) xMax = xPos;
			xPos = 0;
			y += font->height;
		}
		else if ('\t' == line[loop])
		{
			xPos += font->tabWidth - (xPos % font->tabWidth);
		}
		else
		{
			if (line[loop]=='|')
			{
				loop++;
				code=line[loop];

				if (code=='f')
					font->flash_flag^=1;
				else
				{
					Font_set_colourbank_fade(font,code-'0');
				}							
			}
			else
				xPos += Font_OutputRGBChar(font, x + xPos, y, line[loop], render, r, g, b, s);
		}
	}
	return xPos>xMax?xPos:xMax;
}

// *******************************************************************************************************
ULONG Font_OutputRGBChar(lpFont font, ULONG x, ULONG y, UCHAR c, BOOL render, UCHAR r, UCHAR g, UCHAR b, UCHAR scale)
{
	GsSPRITE	s;

	if ((!font->flash_flag) || (font->flash_count & FLASH_MASK))
	{

		c -= 32;
		/* modify for colour change */
		s.r = r;
		s.g = g;
		s.b = b;

		s.x = x;
		s.y = y;
		s.u = font->uvTable[c].x;
		s.v = font->uvTable[c].y;
		s.w = font->width;
		s.h = font->height;
		s.tpage = font->image->tPage;
		s.cx = font->image->cx;
		s.cy = font->image->cy;
		s.mx = s.my = s.rotate = NULL;
		s.scalex = s.scaley = scale;
		// s.attribute = font->image->attribute;
		// I know what attribute I want
		s.attribute = (GsALON | GsAONE);

		GsSortFastSprite(&s, &gfxGlobs.Wot[gfxGlobs.bufID], 9);
	}
	if (font->flags & FONT_FLAG_PROPORTIONAL)
		return (ULONG) font->width_table[c];
	else
		return (ULONG) font->width;
}
// END ScottN



