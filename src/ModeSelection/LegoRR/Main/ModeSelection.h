// ModeSelection.h : Declares the functions used to present the Mode Selection dialog.
//

#pragma once

#include "../Common.h"
#include "../Drawing/DirectDraw.h"


namespace lego {
namespace dialog {

#pragma region Globals

namespace globals {

	// <LegoRR.exe @0056904c>
	extern draw::DriverMode* g_CurrentDriverMode;
	// <LegoRR.exe @00569050>
	extern draw::DeviceMode* g_CurrentDeviceMode;
	// <LegoRR.exe @00569054>
	extern draw::ScreenMode* g_CurrentScreenMode;

} /* namespace globals */

#pragma endregion


#pragma region Functions

// <LegoRR.exe @0049d2f0>
BOOL __cdecl ChooseScreenMode(BOOL showDialog, BOOL isDebug, BOOL isBest, BOOL isWindow, const char* errorMessage);

// <LegoRR.exe @0049d5b0>
INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

// Change the full screen mode setting, and update the "Screen Mode" / "Window Size" label text.
// <LegoRR.exe @0049d8a0>
void __cdecl ChangeFullScreenMode(HWND hDlg, BOOL isFullScreen);

// Rebuild (enumerate through) and repopulate the list of screen modes.
// Only screen modes registered as supported by the game will appear in the listbox.
// <LegoRR.exe @0049d8f0>
void __cdecl RebuildScreenModes(HWND hDlg);

// Rebuild (enumerate through) and repopulate the list of device modes.
// <LegoRR.exe @0049da40>
void __cdecl RebuildDeviceModes(HWND hDlg);

// Register a screen mode that the game supports.
// Although this assigns to a table using the same ScreenMode structure,
//  only the width, height, and bit depth fields are assigned.
// <LegoRR.exe @0049db30>
void __cdecl RegisterScreenMode(int screenWidth, int screenHeight, int bitDepth);

// Check if the selected system-available screen mode is supported by the game.
// <LegoRR.exe @0049db90>
BOOL __cdecl HasRegisteredScreenMode(int selIndex);

// Get the index of a system-available screen mode from the display name used in the listbox.
// <LegoRR.exe @0049dc10>
BOOL __cdecl GetScreenMode(const char* displayName, int* out_index);

// Update FullScreen/Window radio buttons depending on whether
// the currently selected driver allows windowed mode.
// <LegoRR.exe @0049dc90>
void __cdecl UpdateRadioButtons(HWND hDlg);

// <LegoRR.exe @0049d5b0>
//INT_PTR __stdcall Setup_DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

// Change the full screen mode setting, and update the "Screen Mode" / "Window Size" label text.
// <LegoRR.exe @0049d8a0>
//void __cdecl Setup_ChangeFullScreenMode(HWND hDlg, BOOL isFullScreen);

// Rebuild (enumerate through) and repopulate the list of screen modes.
// Only screen modes registered as supported by the game will appear in the listbox.
// <LegoRR.exe @0049d8f0>
//void __cdecl Setup_RebuildScreenModes(HWND hDlg);

// Rebuild (enumerate through) and repopulate the list of device modes.
// <LegoRR.exe @0049da40>
//void __cdecl Setup_RebuildDeviceModes(HWND hDlg);

// Register a screen mode that the game supports.
// Although this assigns to a table using the same ScreenMode structure,
//  only the width, height, and bit depth fields are assigned.
// <LegoRR.exe @0049db30>
//void __cdecl Setup_RegisterScreenMode(int screenWidth, int screenHeight, int bitDepth);

// Check if the selected system-available screen mode is supported by the game.
// <LegoRR.exe @0049db90>
//BOOL __cdecl Setup_HasRegisteredScreenMode(int selIndex);

// Get the index of a system-available screen mode from the display name used in the listbox.
// <LegoRR.exe @0049dc10>
//BOOL __cdecl Setup_GetScreenMode(const char* displayName, int* out_index);

// Update FullScreen/Window radio buttons depending on whether
// the currently selected driver allows windowed mode.
// <LegoRR.exe @0049dc90>
//void __cdecl UpdateRadioButtons(HWND hDlg);

#pragma endregion


} /* namespace globals */
} /* namespace lego */
