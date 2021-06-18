
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>  // for extended case-insensitive str API?


/// TYPES ////////////////////////////////
enum CmdlineFlags : unsigned int
{
	// Assigned by FUN_00478370 when param_1 != 0
	// if (param_1 != 0) {
    //   g_CMDLINE_FLAGS |= 2;
  	// }
	// I think this specifies that the Window setup function has been called once.
	//CMD_UNK_2           = 0x2,  // Non-zero to adjust window rect?


	CMD_NM              = 0x20, // -nm
	CMD_BEST            = 0x40, // -best
	CMD_WINDOW          = 0x100, // -window
	CMD_STARTLEVEL      = 0x200, // -startlevel
	CMD_CLEANSAVES      = 0x400, // -cleansaves
	CMD_DEBUG           = 0x2000, // -debug
	CMD_DUALMOUSE       = 0x4000, // -dualmouse
	CMD_DEBUGCOMPLETE   = 0x8000, // -debugcomplete
	CMD_TESTERCALL      = 0x10000, // -testercall
	CMD_TESTLEVELS      = 0x20000, // -testlevels
	CMD_FTM             = 0x40000, // -ftm
	CMD_FVF             = 0x80000, // -fvf
	CMD_REDUCESAMPLES   = 0x100000, // -reducesamples
	CMD_SHOWVERSION     = 0x200000, // -showversion
	CMD_REDUCEANIMATION = 0x400000, // -reduceanimation
	CMD_REDUCEPROMESHES = 0x800000, // -reducepromeshes
	CMD_REDUCEFLICS     = 0x1000000, // -reduceflics
	CMD_REDUCEIMAGES    = 0x2000000, // -reduceimages

	// These are parsed, but do not assign a flag
	// CMD_FLAGS           = ??, // -flags      (set as global g_DEBUG_FLAGS)
	// CMD_FPSLOCK         = ??, // -fpslock    (set as global g_FPSLOCK_VSYNC)
	// CMD_PROGRAMMER      = ??, // -programmer (set as global g_PROGRAMMER_MODE)
	// CMD_NOSOUND         = ??, // -nosound    (set as exclusive bool out-value)
	// CMD_INSISTONCD      = ??, // -insistOnCD (set as exclusive bool out-value)
};

// enum ProgrammerMode : unsigned int
// {
// 	PROGRAMMER_OFF = 0,
// 	PROGRAMMER_MODE_1 = 1,
// 	PROGRAMMER_MODE_2 = 2,
// 	// more values exist, at least up to and including 10?
// };


/// GLOBALS //////////////////////////////
// <LegoRR.exe @00506f84>
static CmdlineFlags g_CMDLINE_FLAGS = 0;
// <LegoRR.exe @00506f88>
static unsigned int g_PROGRAMMER_MODE = 0;

// <LegoRR.exe @00506f8c>
static char g_STARTLEVEL[256];
// <LegoRR.exe @0050693c>
static float g_FPSLOCK_VSYNC = 0.0f;
// <LegoRR.exe @0050708c>
static unsigned int g_DEBUG_FLAGS = 0;


/// HELPERS //////////////////////////////

// Because there's no non-WINAPI implementation for this(?)
// <LegoRR.exe @004778d0>
char* __cdecl strstri(char* str, const char* strSearch)
{
	size_t strLength = strlen(str);
	size_t searchLength = strlen(strSearch);

	if (searchLength != 0) {
		for (size_t i = 0; i < strLength; i++, str++) {

			if (_strnicmp(str, strSearch, searchLength) == 0)
				return str;
		}
	}
	return NULL;
}


/// CMD FUNCTIONS ////////////////////////

// Evaluate all command line arguments in one go. The order you specify arguments in doesn't matter,
//   but the parser will give precedence based on the order it checks them in.
// <LegoRR.exe @00477eb0>
void __cdecl Main_parseCmdFlags(char* args, bool* out_nosound, bool* out_insistOnCD)
{
	char* strMatch;

	// Out settings
	if (strstri(args, "-insistOnCD") != NULL)
		*out_insistOnCD = true;
	
	if (strstri(args, "-nosound") != NULL)
		*out_nosound = true;

	// Flags
	if (strstri(args, "-debug") != NULL)
		g_CMDLINE_FLAGS |= CmdlineFlags::CMD_DEBUG;
	
	if (strstri(args, "-nm") != NULL)
		g_CMDLINE_FLAGS |= CmdlineFlags::CMD_NM;
	
	if (strstri(args, "-ftm") != NULL)
		g_CMDLINE_FLAGS |= CmdlineFlags::CMD_FTM;
	
	if (strstri(args, "-fvf") != NULL)
		g_CMDLINE_FLAGS |= CmdlineFlags::CMD_FVF;
	
	if (strstri(args, "-best") != NULL)
		g_CMDLINE_FLAGS |= CmdlineFlags::CMD_BEST;
	
	if (strstri(args, "-window") != NULL)
		g_CMDLINE_FLAGS |= CmdlineFlags::CMD_WINDOW;
	
	if (strstri(args, "-dualmouse") != NULL)
		g_CMDLINE_FLAGS |= CmdlineFlags::CMD_DUALMOUSE;
	
	// This argument will also trigger "-debug", because there's no checking for whitespace after the match
	if (strstri(args, "-debugcomplete") != NULL)
		g_CMDLINE_FLAGS |= CmdlineFlags::CMD_DEBUGCOMPLETE;
	
	if (strstri(args, "-testercall") != NULL) {
		g_PROGRAMMER_MODE = 2;
		g_CMDLINE_FLAGS |= CmdlineFlags::CMD_TESTERCALL;
	}

	if (strstri(args, "-testlevels") != NULL)
		g_CMDLINE_FLAGS |= CmdlineFlags::CMD_TESTLEVELS;
	
	if (strstri(args, "-reducesamples") != NULL)
		g_CMDLINE_FLAGS |= CmdlineFlags::CMD_REDUCESAMPLES;
	
	if (strstri(args, "-showversion") != NULL)
		g_CMDLINE_FLAGS |= CmdlineFlags::CMD_SHOWVERSION;
	
	if (strstri(args, "-reduceanimation") != NULL)
		g_CMDLINE_FLAGS |= CmdlineFlags::CMD_REDUCEANIMATION;
	
	if (strstri(args, "-reducepromeshes") != NULL)
		g_CMDLINE_FLAGS |= CmdlineFlags::CMD_REDUCEPROMESHES;
	
	if (strstri(args, "-reduceflics") != NULL)
		g_CMDLINE_FLAGS |= CmdlineFlags::CMD_REDUCEFLICS;
	
	if (strstri(args, "-reduceimages") != NULL)
		g_CMDLINE_FLAGS |= CmdlineFlags::CMD_REDUCEIMAGES;
	
	strMatch = strstri(args, "-startlevel");
	if (strMatch != NULL) {
		strMatch += 11; // skip length of "-startlevel" (no spaces)

		// skip whitespace
		while (*strMatch != '\0' && *strMatch == ' ') {
			strMatch++;
		}
		
		// read non-whitespace into global g_STARTLEVEL buffer
		int i = 0;
		while (*strMatch != '\0' && strMatch != ' ') {
			g_STARTLEVEL[i++] = *strMatch++;
		}
		g_STARTLEVEL[i] = '\0'; // null-terminate buffer
		g_CMDLINE_FLAGS |= CmdlineFlags::CMD_STARTLEVEL;
	}

	strMatch = strstri(args, "-flags");
	if (strMatch != NULL) // debug flags are in decimal... terrifying...
		g_DEBUG_FLAGS = atoi(strMatch + 6); // skip length of "-flags" (no spaces), atoi skips whitespace on its own
	
	strMatch = strstri(args, "-fpslock");
	if (strMatch != NULL) {
		int value = atoi(strMatch + 8); // skip length of "-fpslock" (no spaces), atoi skips whitespace on its own
		if (value != 0) { // parse failed or 0, don't divide by 0
			// 25.0f is the default "time unit" for the game, or something like that, see the header of Lego.cfg for more info
			g_FPSLOCK_VSYNC = 25.0f / (float)(unsigned long long)value; // what a weird cast...
		}
	}
	
	strMatch = strstri(args, "-programmer");
	if (strMatch != NULL) {
		g_PROGRAMMER_MODE = atoi(strMatch + 11); // skip length of "-programmer" (no spaces), atoi skips whitespace on its own
		if (g_PROGRAMMER_MODE == 0) // parse failed or 0, set to 1 as default 'mode'
			g_PROGRAMMER_MODE = 1;
	}
	else {
		g_PROGRAMMER_MODE = 0; // mode when "-programmer" not specified
	}
	
	if (strstri(args, "-cleansaves") != NULL)
		g_CMDLINE_FLAGS |= CmdlineFlags::CMD_CLEANSAVES;
}
