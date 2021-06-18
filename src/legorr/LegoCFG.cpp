
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>  // for extended case-insensitive str API?

//#include <CFG.h>


// Flags at <LegoRR.exe @00557ecc>
enum GameFlags : unsigned int
{
	GAME_UNK_4                = 0x4, // Set when loading level?
	GAME_HAS_FOGCOLOURRGB     = 0x8000, // FogColourRGB property found
	GAME_HAS_HIGHFOGCOLOURRGB = 0x10000, // HighFogColourRGB property found

	GAME_SOUNDON          = 0x10,     // Lego*::Main::SoundOn           TRUE
	GAME_ONLYBUILDONPATHS = 0x400000, // Lego*::Main::OnlyBuildOnPaths  TRUE
	GAME_ALWAYSROCKFALL   = 0x800000, // Lego*::Main::AlwaysRockFall    TRUE

	GAME_STREAMNERPSSPEACH = 0x4000000, // Lego*::Main::StreamNERPSSpeach   TRUE

	GAME_UNK_FLAGS_GROUP_A = 0x80c20, // unconditionally set in Game_loadLegoCFG
};
// Flags at <LegoRR.exe @00557ed0>
enum GameFlags2 : unsigned int
{
	GAME2_SHOWDEBUGTOOLTIPS   = 0x8, // Lego*::Main::ShowDebugToolTips   TRUE  ; if ProgrammerMode != 0
	GAME2_ALLOWDEBUGKEYS      = 0x10, // Lego*::Main::AllowDebugKeys   TRUE  ; if ProgrammerMode != 0
	GAME2_ALLOWEDITMODE       = 0x20, // Lego*::Main::AllowEditMode   TRUE  ; if ProgrammerMode != 0
	GAME2_MUSICON             = 0x800, // Lego*::Main::MusicOn           TRUE

	GAME2_NOMULTISELECT       = 0x2000, // NoMultiSelect
	GAME2_ALLOWRENAME         = 0x20000, // AllowRename
	GAME2_RECALLOLOBJECTS     = 0x40000, // RecallOLObjects
	GAME2_GENERATESPIDERS     = 0x80000, // GenerateSpiders
	GAME2_DISABLETOOLTIPSOUND = 0x100000, // DisableToolTipSound
	GAME2_NOAUTOEAT           = 0x200000, // NoAutoEat
};

// ???
enum MiscObjectType : int
{
	TVCAMERA = -1, // tvcamera

	BOULDER  = 5, // Boulder
	POWERCRYSTAL = 6, // PowerCrystal
	ORE = 7, // Ore (7,0) | ProcessedOre (7,1)
	DYNAMITE = 8, // Dynamite
	BARRIER = 9, // Barrier
	
	ELECTRICFENCE = 11, // ElectricFence
	SPIDERWEB = 12, // SpiderWeb
	OOHSCARY = 13, // OohScary

	PATH = 15, // Path
	PUSHER = 16, // Pusher
	FREEZER = 17, // Freezer

	LASERSHOT == 19, // LaserShot  (NOTE: "S" not "Z", unlike other usages of name "Laser")

};

// LEVEL?
struct LEVEL_STRUCTPTR_SIZE_284__005570d4
{
	/*1fc,4*/ float float_1fc;
};

/// GLOBALS //////////////////////////////
// Not exactly known how it's used
// <LegoRR.exe @005570c4>
static void* g_CFG_ROOTPATH = NULL;
// <LegoRR.exe @005570c0>
static CFGProperty* g_LegoCfgRoot = NULL;

// <LegoRR.exe @004b9a14>
static LPCSTR lpWindowName_004b9a14;


// <LegoRR.exe @00557ec4>
static float g_GAME_MinDistFor3DSoundsOnTopView = 150.0f; // defaults to this on some failure?

// <LegoRR.exe @00557ec8>
static BOOL DAT_00557ec8; // unconditionally set to 1 in Main_loadLegoCFG

// <LegoRR.exe @00557ecc>
static unsigned int DAT_00557ecc = 0; // Lego Game flags taken from Lego*::Main block
// <LegoRR.exe @00557ed0>
static unsigned int DAT_00557ed0 = 0; // Even more Lego Game taken from Lego*::Main block

// <LegoRR.exe @00557f50>
static char* g_GAME_CreditsTextFile; // Lego*::Main::CreditsTextFile
// <LegoRR.exe @00557f54>
static char* g_GAME_CreditsBackAVI; // Lego*::Main::CreditsBackAVI

// Stored in BGR order... neat
// Lego*::Main::PowerCrystalRGB   ###:###:###
// <LegoRR.exe @00557428>
static float g_GAME_PowerCrystalRGB_b;
// <LegoRR.exe @0055742c>
static float g_GAME_PowerCrystalRGB_g;
// <LegoRR.exe @00557430>
static float g_GAME_PowerCrystalRGB_r;

// Lego*::Main::UnpoweredCrystalRGB   ###:###:###
// <LegoRR.exe @00557434>
static float g_GAME_UnpoweredCrystalRGB_b;
// <LegoRR.exe @00557438>
static float g_GAME_UnpoweredCrystalRGB_g;
// <LegoRR.exe @0055743c>
static float g_GAME_UnpoweredCrystalRGB_r;

// GHIDRA STRING CONST TO STRING
//REGEX:   \bs_([^\t\n\r ]*?)_[0-9a-f]{8}\b
//REPLACE: "$1"

/// LEGO CFG FUNCTIONS ///////////////////

// <LegoRR.exe @00415840>
void __cdecl Boot_loadAVIProperty(const char* keyName, bool isSkippable)
{
	if (keyName != NULL) {
		const char* keyPath = CFG_joinPath(g_CFG_ROOTPATH, "Main", keyName, NULL);
		char* keyValue = CFG_copyPropertyValue(g_LegoCfgRoot, keyPath);
		if (keyValue != NULL && FUN_0047fe20(keyValue)) {
			int** ppiVar2 = FUN_00472820(keyValue);
			FUN_00415630(ppiVar2, isSkippable);
			FUN_004729b0(ppiVar2);
			free(keyValue);
		}
	}
}

// <LegoRR.exe @004156f0>
void __cdecl Boot_loadSplashProperty(const char* keyName, bool isSkippable, const char* timeKeyName)
{
	const char* timeKeyValue;
	const char* keyPath = CFG_joinPath(g_CFG_ROOTPATH, "Main", timeKeyName, NULL);
	const char* timeKeyValue = CFG_getPropertyValue(g_LegoCfgRoot, keyPath);
	if (timeKeyValue == NULL) {
		timeKeyValue = &lpWindowName_004b9a14;
	}
	else {
		// what is going on here....?
		keyPath = CFG_joinPath(g_CFG_ROOTPATH, "Main", timeKeyName, NULL);
		timeKeyValue = CFG_getPropertyValue(g_LegoCfgRoot, keyPath);
	}
	atof(timeKeyValue); // probably atof(), return should actually be assigned somewhere
	
	unsigned int DVar3 = timeGetTime();
	int iVar1 = __ftol(); // timer var, down below is the loop that checks until the splash timer has finished
	if (keyName != NULL) {
		keyPath = CFG_joinPath(g_CFG_ROOTPATH, "Main", keyName, NULL);
		char* keyValue = CFG_copyPropertyValue(g_LegoCfgRoot, keyPath);
		if (keyValue != NULL) {
			int** ppiVar4 = FUN_0047dc90(keyValue); // open/allocate image file?
			if (ppiVar4 != NULL) {
				// play the splash logo for duration
				while( true ) {
					FUN_0047df70(ppiVar4, (float*)NULL, (float*)NULL, (float*)NULL);
					FUN_004781f0(0);
					Sleep(100);
					unsigned int DVar5 = timeGetTime();
					if (DVar3 - iVar1 <= DVar5) break;
					if (isSkippable && (FUN_0047f270() != 0 || DAT_0076bb40 != 0 || DAT_0076bb3c != 0))
						break;
				}
				FUN_0047d730(ppiVar4); // probably a cleanup function
			}
		}
	}
}

// <LegoRR.exe @00401b30>
uint __cdecl Game_getProgrammerMode(void)
{
	return g_PROGRAMMER_MODE;
}

// <LegoRR.exe @00416c30>
bool __cdecl Game_isFrontEndEnabled(void)
{
	const char* keyPath = CFG_joinPath(g_CFG_ROOTPATH, "Main", "FrontEnd", NULL);
	uint boolValue = CFG_getPropertyBool(g_LegoCfgRoot, keyPath);
	// Very important to check == 1 here, incase there was an error locating/or parsing the bool property (which returns 2)
	if (boolValue == 1 && g_PROGRAMMER_MODE < 3) {
		return true;
	}
	return false;
}

// <LegoRR.exe @0041fa80>
undefined4 Main_loadLegoCFG(void)
{
	// ...

	// <LegoRR.exe -> Main_loadLegoCFG @004201f6>
	// SNIPPET FOR LOADING AVI'S AND SPLASH SCREENS
	//int iVar4 = ;
	if (Game_isFrontEndEnabled() && cfg_unk__ProgrammerMode__FUN_00414c10() != 0) {
		bool importantSkippable = Game_getProgrammerMode() != 0;
		Boot_loadAVIProperty("LegoAvi", importantSkippable);
		Boot_loadSplashProperty("DDILogo", true, "DDILogoTime");
		Boot_loadAVIProperty("DDIAvi", true);
		Boot_loadAVIProperty("RRAvi", true);
		// Removed redundancy
		//importantSkippable = Game_getProgrammerMode() != 0;
		Boot_loadSplashProperty("LMILogo", importantSkippable, "LMILogoTime");
	}

	// ...
}

