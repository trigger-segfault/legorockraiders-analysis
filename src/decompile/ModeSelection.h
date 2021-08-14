// ModeSelection.h : Declares functions to present the Mode Selection dialog and start the game engine.
//
/// STATUS: [Usable, but still being refactored]
/// PURPOSE: The Mode Selection dialog determines or allows the user to select the graphics
///          driver/device/screen mode configuration to use on startup. This is an essential
///          step in booting the game engine.
///
/// NAMESPACE: lego::setup

#pragma once

#include "Common.h"
#include "DirectDraw.h"


#pragma pack(push, 1)

#pragma region Globals
namespace lego::setup {

/// PRIVATE:
// <LegoRR.exe @005590a0 - 005764e4>
struct ModeSelectionManager
{
	// <LegoRR.exe @005590a0>
	/*00000,4*/ int DriverModes_COUNT;
	// <LegoRR.exe @005590a4>
	/*00004,4*/ int DeviceModes_COUNT;
	// <LegoRR.exe @005590a8>
	/*00008,4*/ int ScreenModes_COUNT;
	// <LegoRR.exe @005590ac>
	/*0000c,1590*/ DriverMode DriverModes_TABLE[20];
	// <LegoRR.exe @0055a63c>
	/*0159c,1590*/ DeviceMode DeviceModes_TABLE[20];
	// <LegoRR.exe @0055bbcc>
	/*02b2c,d480*/ ScreenMode ScreenModes_TABLE[200]; // yup... 10 times bigger than the other two
	// <LegoRR.exe @0056904c>
	/*0ffac,4*/ const DriverMode* CurrentDriverMode;
	// <LegoRR.exe @00569050>
	/*0ffb0,4*/ const DeviceMode* CurrentDeviceMode;
	// <LegoRR.exe @00569054>
	/*0ffb4,4*/ const ScreenMode* CurrentScreenMode;
	// <LegoRR.exe @00569058>
	/*0ffb8,4*/ BOOL IsFullScreen;
	// Used when the Windowed mode Radio Button is disable
	//  (basically keep the state even if it's forcefully changed)
	// <LegoRR.exe @0056905c>
	/*0ffbc,4*/ BOOL IsFullScreen_Backup;
	// <LegoRR.exe @00569060>
	/*0ffc0,d480*/ ScreenMode RegisteredScreenModes_TABLE[200]; // yup... *still* 10 times bigger than the other two
	// <LegoRR.exe @005764e0>
	/*1d440,4*/ int RegisteredScreenModes_COUNT;
	/*1d444*/
};
static_assert(sizeof(ModeSelectionManager) == 0x1d444, "");
	
} /* namespace lego::setup */
namespace lego::globals {

/// PRIVATE:
// <LegoRR.exe @005590a0 - 005764e4>
extern lego::setup::ModeSelectionManager g_ModeSel;

// /// PRIVATE:
// // <LegoRR.exe @005590a0>
// extern int g_DriverModes_COUNT;
// // <LegoRR.exe @005590a4>
// extern int g_DeviceModes_COUNT;
// // <LegoRR.exe @005590a8>
// extern int g_ScreenModes_COUNT;
// // <LegoRR.exe @005590ac>
// extern DriverMode g_DriverModes_TABLE[20];
// // <LegoRR.exe @0055a63c>
// extern DeviceMode g_DeviceModes_TABLE[20];
// // <LegoRR.exe @0055bbcc>
// extern ScreenMode g_ScreenModes_TABLE[200]; // yup... 10 times bigger than the other two
// // <LegoRR.exe @0056904c>
// extern const DriverMode* g_CurrentDriverMode;
// // <LegoRR.exe @00569050>
// extern const DeviceMode* g_CurrentDeviceMode;
// // <LegoRR.exe @00569054>
// extern const ScreenMode* g_CurrentScreenMode;
// // <LegoRR.exe @00569058>
// extern BOOL g_IsFullScreen;
// // Used when the Windowed mode Radio Button is disable
// //  (basically keep the state even if it's forcefully changed)
// // <LegoRR.exe @0056905c>
// extern BOOL g_IsFullScreen_Backup;
// // <LegoRR.exe @00569060>
// extern ScreenMode g_RegisteredScreenModes_TABLE[200]; // yup... *still* 10 times bigger than the other two
// // <LegoRR.exe @005764e0>
// extern int g_RegisteredScreenModes_COUNT;

} /* namespace lego::globals */
#pragma endregion

#pragma pack(pop)


#pragma region Functions
namespace lego::setup {

/// PUBLIC:
// <LegoRR.exe @0049d2f0>
BOOL __cdecl ChooseScreenMode(BOOL showDialog, BOOL isDebug, BOOL isBest, BOOL isWindow, const char* errorMessage);

/// PRIVATE:
// <LegoRR.exe @0049d5b0>
INT_PTR CALLBACK ModeSel_DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
// <LegoRR.exe @0049d8a0>
void __cdecl ModeSel_ChangeFullScreenMode(HWND hDlg, BOOL isFullScreen);
// <LegoRR.exe @0049d8f0>
void __cdecl ModeSel_RebuildScreenModes(HWND hDlg);
// <LegoRR.exe @0049da40>
void __cdecl ModeSel_RebuildDeviceModes(HWND hDlg);
// <LegoRR.exe @0049db30>
void __cdecl ModeSel_RegisterScreenMode(int screenWidth, int screenHeight, int bitDepth);
// <LegoRR.exe @0049db90>
BOOL __cdecl ModeSel_HasRegisteredScreenMode(int selIndex);
// <LegoRR.exe @0049dc10>
BOOL __cdecl ModeSel_GetScreenMode(const char* displayName, int* out_index);
// <LegoRR.exe @0049dc90>
void __cdecl ModeSel_UpdateRadioButtons(HWND hDlg);

} /* namespace lego::setup */
#pragma endregion

