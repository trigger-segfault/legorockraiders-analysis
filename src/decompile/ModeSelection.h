#pragma once
#include "DirectDraw.h"


namespace lego {

#pragma region Globals
namespace globals {

	/// INTERNAL:
	// <LegoRR.exe @005590a0>
	extern int g_DriverModes_COUNT;
	// <LegoRR.exe @005590a4>
	extern int g_DeviceModes_COUNT;
	// <LegoRR.exe @005590a8>
	extern int g_ScreenModes_COUNT;
	// <LegoRR.exe @005590ac>
	extern DriverMode g_DriverModes_TABLE[20];
	// <LegoRR.exe @0055a63c>
	extern DeviceMode g_DeviceModes_TABLE[20];
	// <LegoRR.exe @0055bbcc>
	extern ScreenMode g_ScreenModes_TABLE[200]; // yup... 10 times the other two
	// <LegoRR.exe @0056904c>
	extern const DriverMode* g_CurrentDriverMode;
	// <LegoRR.exe @00569050>
	extern const DeviceMode* g_CurrentDeviceMode;
	// <LegoRR.exe @00569054>
	extern const ScreenMode* g_CurrentScreenMode;
	// <LegoRR.exe @00569058>
	extern BOOL g_IsFullScreen;
	// Used when the Windowed mode Radio Button is disable
	//  (basically keep the state even if it's forcefully changed)
	// <LegoRR.exe @0056905c>
	extern BOOL g_IsFullScreen_Backup;
	// <LegoRR.exe @00569060>
	extern ScreenMode g_RegisteredScreenModes_TABLE[200]; // yup... 10 times the other two
	// <LegoRR.exe @005764e0>
	extern int g_RegisteredScreenModes_COUNT;
} /* namespace globals */
#pragma endregion


#pragma region Functions
namespace wnd {

/// PUBLIC:
// <LegoRR.exe @0049d2f0>
BOOL ChooseScreenMode(BOOL showDialog, BOOL isDebug, BOOL isBest, BOOL isWindow, const char * errorMessage);

/// INTERNAL:
// <LegoRR.exe @0049d5b0>
INT_PTR ModeSel_ModeDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
// <LegoRR.exe @0049d8a0>
void ModeSel_ChangeFullScreenMode(HWND hDlg, BOOL isFullScreen);
// <LegoRR.exe @0049d8f0>
void ModeSel_RebuildScreenModes(HWND hDlg);
// <LegoRR.exe @0049da40>
void ModeSel_RebuildDeviceModes(HWND hDlg);
// <LegoRR.exe @0049db30>
void ModeSel_RegisterScreenMode(int screenWidth, int screenHeight, int bitDepth);
// <LegoRR.exe @0049db90>
BOOL ModeSel_HasRegisteredScreenMode(int selIndex);
// <LegoRR.exe @0049dc10>
BOOL ModeSel_GetScreenMode(const char * displayName, uint * out_index);
// <LegoRR.exe @0049dc90>
void ModeSel_UpdateRadioButtons(HWND hDlg);

} /* namespace wnd */
#pragma endregion


} /* namespace lego */
