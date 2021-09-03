#pragma once

#include "../framework.h"
#include "DirectDraw.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

typedef struct Init_Globs
{
	/*00000,4*/ unsigned long driverCount;
	/*00004,4*/ unsigned long deviceCount;
	/*00008,4*/ unsigned long modeCount;
	/*0000c,1590*/ DirectDraw_Driver drivers[DIRECTDRAW_MAXDRIVERS];
	/*0159c,1590*/ DirectDraw_Device devices[DIRECTDRAW_MAXDEVICES];
	/*02b2c,d480*/ DirectDraw_Mode modes[DIRECTDRAW_MAXMODES];
	/*0ffac,4*/ const DirectDraw_Driver* selDriver;
	/*0ffb0,4*/ const DirectDraw_Device* selDevice;
	/*0ffb4,4*/ const DirectDraw_Mode* selMode;
	/*0ffb8,4*/ BOOL selFullScreen;
	/*0ffbc,4*/ BOOL wasFullScreen;
	/*0ffc0,d480*/ DirectDraw_Mode validModes[DIRECTDRAW_MAXMODES];
	/*1d440,4*/ unsigned long validModeCount;
	/*1d444*/
} Init_Globs;
static_assert(sizeof(Init_Globs) == 0x1d444, "");

#pragma endregion

/**********************************************************************************
 ******** Globals
 **********************************************************************************/

#pragma region Globals

// <LegoRR.exe @005590a0>
extern Init_Globs initGlobs;

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @0049d2f0>
BOOL __cdecl Init_Initialise(BOOL setup, BOOL debug, BOOL best, BOOL window, const char* noHALMsg);

// <LegoRR.exe @0049d5b0>
BOOL CALLBACK Init_DialogProc(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

// <LegoRR.exe @0049d8a0>
void __cdecl Init_SetFullScreen(HWND hWndDlg, BOOL on);

// <LegoRR.exe @0049d8f0>
void __cdecl Init_SetModeList(HWND hWndDlg);

// <LegoRR.exe @0049da40>
void __cdecl Init_SetDeviceList(HWND hWndDlg);

// <LegoRR.exe @0049db30>
void __cdecl Init_AddValidMode(unsigned long width, unsigned long height, unsigned long depth);

// <LegoRR.exe @0049db90>
BOOL __cdecl Init_IsValidMode(unsigned long mode);

// <LegoRR.exe @0049dc10>
BOOL __cdecl Init_GetMode(const char* name, OUT unsigned long* mode);

// <LegoRR.exe @0049dc90>
void __cdecl Init_HandleWindowButton(HWND hWndDlg);

#pragma endregion

}
