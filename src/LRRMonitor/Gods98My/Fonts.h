#pragma once

#include "../framework.h"
#include "Image.h"
#include "Maths.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Forward Declarations
 **********************************************************************************/

#pragma region Forward Declarations

#pragma endregion

/**********************************************************************************
 ******** Function Typedefs
 **********************************************************************************/

#pragma region Function Typedefs

typedef void (__cdecl* FontRunThroughListsCallback)(Font* font, void* data);

#pragma endregion
	
/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define FONT_MAXLISTS			32			// 2^32 - 1 possible fonts...

#define FONT_LASTCHARACTER		202			// Last character in the font image.


#define FONT_GRIDWIDTH			10
#define FONT_GRIDHEIGHT			19
#define FONT_MAXSTRINGLEN		1024
#define FONT_MAXIMAGEPERSTRING	10

#pragma endregion

/**********************************************************************************
 ******** Enumerations
 **********************************************************************************/

#pragma region Enums

#define FONT_FLAG_INITIALISED	0x00000001
#define FONT_FLAG_WINDOWSET		0x00000002
#define FONT_FLAG_WINDOWWRAPPED	0x00000004

#pragma endregion

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

typedef struct Font
{
	/*000,4*/ Image* image;
	/*000,be0*/ AREA2D posSet[FONT_GRIDWIDTH][FONT_GRIDHEIGHT];
	/*be4,4*/ unsigned long fontHeight;
	/*be8,4*/ unsigned long tabWidth;
	/*bec,4*/ unsigned long flags;
	/*bf0,4*/ Font* nextFree;
	/*bf4*/
} Font, *lpFont;
static_assert(sizeof(Font) == 0xbf4, "");


typedef struct Font_Globs
{
	/*00,80*/ Font* listSet[FONT_MAXLISTS];		// Fonts list
	/*80,4*/ Font* freeList;
	/*84,4*/ unsigned long listCount;						// number of lists.
	/*88,4*/ unsigned long flags;
	/*8c*/
} Font_Globs;
static_assert(sizeof(Font_Globs) == 0x8c, "");

#pragma endregion

/**********************************************************************************
 ******** Globals
 **********************************************************************************/

#pragma region Globals

// <LegoRR.exe @00507528>
extern Font_Globs fontGlobs;

#pragma endregion

/**********************************************************************************
 ******** Macros
 **********************************************************************************/

#ifdef DEBUG
	#define Font_CheckInit()			if (!(fontGlobs.flags & FONT_FLAG_INITIALISED)) Error_Fatal(TRUE, "Error: Font_Intitialise() Has Not Been Called");
#else
	#define Font_CheckInit()
#endif

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @00401b90>
unsigned long __cdecl Font_GetStringWidth(Font* font, const char* msg, ...);

// <LegoRR.exe @00401bc0>
void __cdecl Font_GetStringInfo(Font* font, OPTIONAL OUT unsigned long* width,
								OPTIONAL OUT unsigned long* lineCount, const char* msg, ...);

// <LegoRR.exe @0047a1a0>
Font* __cdecl Font_Load(const char* fname);

// <LegoRR.exe @0047a410>
void __cdecl Font_VGetStringInfo(const Font* font, OPTIONAL OUT unsigned long* width,
								OPTIONAL OUT unsigned long* lineCount, const char* msg, std::va_list args);


// <LegoRR.exe @0047a440>
unsigned long __cdecl Font_PrintF(const Font* font, long x, long y, const char* msg, ...);

// <LegoRR.exe @0047a470>
unsigned long __cdecl Font_VPrintF(const Font* font, long x, long y, const char* msg, std::va_list args);

// <LegoRR.exe @0047a4a0>
unsigned long __cdecl Font_VPrintF2(const Font* font, long x, long y, int render,
									OPTIONAL OUT unsigned long* lineCount, const char* msg, std::va_list args);

// <LegoRR.exe @0047a730>
unsigned long __cdecl Font_OutputChar(const Font* font, long x, long y, char c, BOOL render);

// <LegoRR.exe @0047a7e0>
unsigned long __cdecl Font_GetCharWidth(const Font* font, char c);

// <LegoRR.exe @0047a800>
unsigned long __cdecl Font_GetHeight(const Font* font);

// <LegoRR.exe @0047a810>
void __cdecl Font_Remove(Font* dead);

// <LegoRR.exe @0047a840>
Font* __cdecl Font_Create(Image* image);

// <LegoRR.exe @0047a880>
void __cdecl Font_AddList(void);


/*unsigned long __cdecl Font_GetLineCount(Font* font, const char* msg, ...);
void __cdecl Font_Initialise(void);
void __cdecl Font_Shutdown(void);
void __cdecl Font_SetTabWidth(const Font* font, unsigned long width, int spaces);

void __cdecl Font_GetBackgroundColour(Font* font, OUT float* r, OUT float* g, OUT float* b);
void __cdecl Font_RemoveCallback(Font* font, void* data);
void __cdecl Font_RunThroughLists(FontRunThroughListsCallback Callback, void* data);*/

#pragma endregion

}
