//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Fonts.c - [Fonts Code]
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#define FONT_MAXFONTS			(4)			// variable list stuff dumped again

#define FONT_FLAG_INITIALISED	0x00000001
#define FONT_FLAG_WINDOWSET		0x00000002
#define FONT_FLAG_WINDOWWRAPPED	0x00000004

/* added by SteveD */
#define	FONT_FLAG_PROPORTIONAL	0x00000008


#define FONT_GRIDWIDTH			16
#define FONT_GRIDHEIGHT		12

#define FONT_MAXSTRINGLEN		1024

typedef struct		colour_b
{
	Uint16	red;
	Uint16	green;
	Uint16	blue;

}	COLOUR_BANK, *LPCOLOUR_BANK;

typedef enum
{
	CB_BLACK,
	CB_RED,
	CB_GREEN,
	CB_YELLOW,
	CB_BLUE,
	CB_MAGENTA,
	CB_CYAN,
	CB_WHITE,

	CB_DBLACK,
	CB_DRED,
	CB_DGREEN,
	CB_DYELLOW,
	CB_DBLUE,
	CB_DMAGENTA,
	CB_DCYAN,
	CB_DWHITE,

}	COLOUR_TYPE;


typedef	struct	POS2D
{
	Uint8	x, y;
} POS2D, *LPPOS2D;

typedef struct Font
{
	lpImage	image;
	UCHAR		*width_table;
	POS2D		*uvTable;
	Uint16	width, height;
	Uint16	tabWidth;
	ULONG 	flags;
	Uint16	red,green,blue;		/* current colour at fadeLevel */
	Uint16	flash_flag;
	Uint16	flash_count;

} Font, *lpFont;

typedef struct Font_Globs
{

	Font *listSet[FONT_MAXFONTS];

	// Global data here...
	BOOL debugPrint;
	ULONG listCount;
	ULONG flags;

} Font_Globs, *lpFont_Globs;

void		Font_Initialise(void);
lpFont	Font_Load(LPUCHAR fname, int width, int height, int gridwidth, int gridheight);
lpFont	Font_Create(lpImage image);
void		Font_AddList(void);
ULONG	Font_PrintF(lpFont font, ULONG x, ULONG y, LPUCHAR msg, ...);
ULONG	Font_PrintFD(lpFont font, ULONG x, ULONG y, LPUCHAR msg, ...);
ULONG	Font_VPrintF(lpFont font, ULONG x, ULONG y, BOOL render, LPUCHAR msg, va_list args);
ULONG	Font_OutputChar(lpFont font, ULONG x, ULONG y, UCHAR c, BOOL render);
ULONG 	Font_GetCharWidth(lpFont font, UCHAR c);


/* added by SteveD */


void	Font_set_colour_fade(lpFont font, Uint16 red, Uint16 green, Uint16 blue);
void	Font_set_colour(lpFont font, Uint16 red, Uint16 green, Uint16 blue);
void	Font_set_colourbank_fade(lpFont font, Uint16 bank);
void	Font_set_colourbank(lpFont font, Uint16 bank);
void	Font_update_flash(lpFont font);

BOOL	FONT_DebugPrint(BOOL flag);

// added by ScottN
ULONG FONT_GetStringWidth(lpFont font, UCHAR *text);

// BEGIN ScottN
// Prototypes for a font print that uses your own r,g,b values
ULONG Font_RGBPrintF(lpFont font, ULONG x, ULONG y, UCHAR r, UCHAR g, UCHAR b, ULONG s, LPUCHAR msg, ...);
ULONG Font_RGBVPrintF(lpFont font, ULONG x, ULONG y, BOOL render, LPUCHAR msg, va_list args, UCHAR r, UCHAR g, UCHAR b, ULONG s);
ULONG Font_OutputRGBChar(lpFont font, ULONG x, ULONG y, UCHAR c, BOOL render, UCHAR r, UCHAR g, UCHAR b, UCHAR scale);

// END ScottN

