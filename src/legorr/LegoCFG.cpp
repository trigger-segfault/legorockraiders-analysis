
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>  // for extended case-insensitive str API?

//#include <CFG.h>

/// GLOBALS //////////////////////////////
// Not exactly known how it's used
// <LegoRR.exe @005570c4>
static void* g_CFG_ROOTPATH = NULL;
// <LegoRR.exe @005570c0>
static CFGProperty* g_CFG_ROOT_A = NULL;

// <LegoRR.exe @004b9a14>
static LPCSTR lpWindowName_004b9a14;


/// LEGO CFG FUNCTIONS ///////////////////

// <LegoRR.exe @00415840>
void __cdecl Boot_loadAVIProperty(const char* keyName, bool skippable)
{
	if (keyName != NULL) {
		const char* keyPath = CFG_joinPath(g_CFG_ROOTPATH, "Main", keyName, NULL);
		char* keyValue = CFG_copyPropertyValue(g_CFG_ROOT_A, keyPath);
		if (keyValue != NULL && FUN_0047fe20(keyValue)) {
			int** ppiVar2 = FUN_00472820(keyValue);
			FUN_00415630(ppiVar2, skippable);
			FUN_004729b0(ppiVar2);
			free(keyValue);
		}
	}
}

// <LegoRR.exe @004156f0>
void __cdecl Boot_loadSplashProperty(const char* keyName, bool skippable, const char* timeKeyName)
{
	const char* timeKeyValue;
	const char* keyPath = CFG_joinPath(g_CFG_ROOTPATH, "Main", timeKeyName, NULL);
	const char* timeKeyValue = CFG_getPropertyValue(g_CFG_ROOT_A, keyPath);
	if (timeKeyValue == NULL) {
		timeKeyValue = &lpWindowName_004b9a14;
	}
	else {
		// what is going on here....?
		keyPath = CFG_joinPath(g_CFG_ROOTPATH, "Main", timeKeyName, NULL);
		timeKeyValue = CFG_getPropertyValue(g_CFG_ROOT_A, keyPath);
	}
	FUN_0048dc40(timeKeyValue); // probably atof(), return should actually be assigned somewhere
	
	unsigned int DVar3 = timeGetTime();
	int iVar1 = __ftol(); // timer var, down below is the loop that checks until the splash timer has finished
	if (keyName != NULL) {
		keyPath = CFG_joinPath(g_CFG_ROOTPATH, "Main", keyName, NULL);
		char* keyValue = CFG_copyPropertyValue(g_CFG_ROOT_A, keyPath);
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
					if (skippable && (FUN_0047f270() != 0 || DAT_0076bb40 != 0 || DAT_0076bb3c != 0))
						break;
				}
				FUN_0047d730(ppiVar4); // probably a cleanup function
			}
		}
	}
}

// <LegoRR.exe @0041fa80>
undefined4 Main_loadLegoCFG(void)
{
	// ...

	// <LegoRR.exe -> Main_loadLegoCFG @004201f6>
	// SNIPPET FOR LOADING AVI'S AND SPLASH SCREENS
	int iVar4 = FUN_00416c30();
	if (iVar4 != 0 && cfg_unk__ProgrammerMode__FUN_00414c10() != 0) {
		iVar4 = FUN_00401b30();
		Boot_loadAVIProperty("LegoAvi", (iVar4 != 0));
		Boot_loadSplashProperty("DDILogo", true);
		Boot_loadAVIProperty("DDIAvi", true);
		Boot_loadAVIProperty("RRAvi", true);
		iVar4 = FUN_00401b30();
		Boot_loadSplashProperty("LMILogo", (iVar4 != 0));
	}

	// ...
}

