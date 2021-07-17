// ModeSelection.cpp : Defines the functions used to present the Mode Selection dialog.
//

#include "ModeSelection.h"
#include "Main.h"
#include "../Drawing/DirectDraw.h"


#pragma region Globals
namespace lego {
namespace dialog {
namespace globals {
	// <LegoRR.exe @005590a0>
	static int g_DriverModes_COUNT;
	// <LegoRR.exe @005590a4>
	static int g_DeviceModes_COUNT;
	// <LegoRR.exe @005590a8>
	static int g_ScreenModes_COUNT;
	// <LegoRR.exe @005590ac>
	static draw::DriverMode g_DriverModes_TABLE[20];
	// <LegoRR.exe @0055a63c>
	static draw::DeviceMode g_DeviceModes_TABLE[20];
	// <LegoRR.exe @0055bbcc>
	static draw::ScreenMode g_ScreenModes_TABLE[200]; // yup... 10 times the other two
	// <LegoRR.exe @0056904c>
	draw::DriverMode* g_CurrentDriverMode;
	// <LegoRR.exe @00569050>
	draw::DeviceMode* g_CurrentDeviceMode;
	// <LegoRR.exe @00569054>
	draw::ScreenMode* g_CurrentScreenMode;
	// <LegoRR.exe @00569058>
	static BOOL g_IsFullScreen;
	// Used when the Windowed mode Radio Button is disable
	//  (basically keep the state even if it's forcefully changed)
	// <LegoRR.exe @0056905c>
	static BOOL g_IsFullScreen_Backup;
	// <LegoRR.exe @00569060>
	static draw::ScreenMode g_RegisteredScreenModes_TABLE[200]; // yup... 10 times the other two
	// <LegoRR.exe @005764e0>
	static int g_RegisteredScreenModes_COUNT;
} /* namespace globals */


/*// <LegoRR.exe @0049d5b0>
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
void __cdecl UpdateRadioButtons(HWND hDlg);*/

} /* namespace setup */
} /* namespace lego */
#pragma endregion


using namespace lego;
using namespace lego::dialog;


#pragma region Functions

// <LegoRR.exe @0049d2f0>
BOOL __cdecl lego::dialog::ChooseScreenMode(BOOL showDialog, BOOL isDebug, BOOL isBest, BOOL isWindow, const char* errorMessage)
{
	INT_PTR idResult = (INT_PTR)IDOK /*1*/;
	globals::g_CurrentDriverMode = nullptr;
	globals::g_CurrentDeviceMode = nullptr;
	globals::g_CurrentScreenMode = nullptr;
	globals::g_IsFullScreen_Backup = !DEFAULTWINDOWED /*FALSE*/;
	globals::g_IsFullScreen        = !DEFAULTWINDOWED /*FALSE*/;
	globals::g_RegisteredScreenModes_COUNT = 0;

	RegisterScreenMode(640, 480, 16);
	#ifdef DEBUG_INCLUDE32BIT
	RegisterScreenMode(640, 480, 32); /// DEBUG
	#endif

	if (isDebug) {
		RegisterScreenMode(800, 600, 16);
		#ifdef DEBUG_INCLUDE32BIT
		RegisterScreenMode(800, 600, 32); /// DEBUG
		#endif

		RegisterScreenMode(1024, 768, 16);
		#ifdef DEBUG_INCLUDE32BIT
		RegisterScreenMode(1024, 768, 32); /// DEBUG
		#endif
	}

	draw::PopulateDriverModes(globals::g_DriverModes_TABLE, &globals::g_DriverModes_COUNT);
	if (globals::g_DriverModes_COUNT < 0)
		return FALSE;  // good luck running this on a potato

	globals::g_CurrentDriverMode = &globals::g_DriverModes_TABLE[0];

	if (!isBest && showDialog) {
		// Let the user choose what driver/device/screen mode to use
		idResult = DialogBoxParamA(main::globals::g_hInstance, MAKEINTRESOURCEA(IDD_MODESELECTION) /*101*/,
			main::globals::g_hWnd, DialogProc, 0);
	}
	else {
		// Auto-select the best-fitting driver/device/screen mode (aka the first valid one)
		// This is a bit of a nasty triple-nested for loop, but it's a lot better than what Ghidra was spitting out

		BOOL modeFound = FALSE; // use this to exit the triple-nested for loop
		globals::g_IsFullScreen = !isWindow; // it seems the -window argument only works if -best is specified...

		for (int i = globals::g_DriverModes_COUNT - 1; i >= 0 && !modeFound; i--) {
			draw::DriverMode* driverMode = &globals::g_DriverModes_TABLE[i];
			// SANITY: If you have a driver with no device modes that appears farther down in the list,
			//         it'll prevent valid drivers from being selected(?)
			if (!draw::PopulateDeviceModes(driverMode, globals::g_DeviceModes_TABLE, &globals::g_DeviceModes_COUNT)) {
				MessageBoxA(nullptr, "Please install DirectX version 6 or later", "Error", MB_OK /*0*/);
				return FALSE;
			}
			if (globals::g_DeviceModes_COUNT < 0)
				continue;

			draw::PopulateScreenModes(driverMode, globals::g_IsFullScreen, globals::g_ScreenModes_TABLE, &globals::g_ScreenModes_COUNT);
			// Unlike the drivers for loop, this list increments
			for (int j = 0; j < globals::g_ScreenModes_COUNT && !modeFound; j++) {
				if (!HasRegisteredScreenMode(j))
					continue;

				// Back to decrementing... go through all device modes now
				for (int k = globals::g_DeviceModes_COUNT - 1; k >= 0 && !modeFound; k--) {
					if (!(globals::g_DeviceModes_TABLE[k].flags & draw::DEVICEMODE_HARDWARE /*0x2000*/))
						continue; // no hardware support, no "best" mode(?)

					// OKAY! We've finally found something, set our globals and break out of here!
					globals::g_CurrentScreenMode = &globals::g_ScreenModes_TABLE[j];
					globals::g_CurrentDeviceMode = &globals::g_DeviceModes_TABLE[k];
					globals::g_CurrentDriverMode = driverMode;
					modeFound = TRUE; // break out of the triple-nested for loop
				}
			}
		}

		if (!modeFound) {
			MessageBoxA(nullptr, errorMessage, "Error", MB_OK /*0*/);
			return FALSE;
		}
	}

	// always true if we didn't take the dialog route
	if (idResult == (INT_PTR)IDOK /*1*/) { // this isn't a BOOL! check to make sure the user didn't cancel
		if (globals::g_IsFullScreen) {
			// does this ignore some user choices for fullscreen/windowed mode?
			return draw::StartScreenMode(TRUE, globals::g_CurrentDriverMode, globals::g_CurrentDeviceMode, globals::g_CurrentScreenMode,
				0, 0, 320, 200);
		}
		else if (globals::g_CurrentScreenMode == nullptr) {
			return draw::StartScreenMode(FALSE, nullptr, globals::g_CurrentDeviceMode, nullptr, 40, 40, 640, 480);
		}
		else {
			return draw::StartScreenMode(FALSE, nullptr, globals::g_CurrentDeviceMode, nullptr, 100, 100,
				globals::g_CurrentScreenMode->screenWidth, globals::g_CurrentScreenMode->screenHeight);
		}
	}
	return FALSE;
}


// <LegoRR.exe @0049d5b0>
INT_PTR CALLBACK dialog::DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	char screenModeText[1024];

	switch (message) {
	case WM_INITDIALOG /*0x110*/: {
		// position the dialog at the center of the screen
		RECT desktopRect, dlgRect;
		HWND hDesktopWnd = GetDesktopWindow();
		GetWindowRect(hDesktopWnd, &desktopRect);
		GetWindowRect(hDlg, &dlgRect);
		MoveWindow(hDlg, (desktopRect.right / 2) - ((dlgRect.right - dlgRect.left) / 2),
			(desktopRect.bottom / 2) - ((dlgRect.bottom - dlgRect.top) / 2),
			dlgRect.right - dlgRect.left,
			dlgRect.bottom - dlgRect.top,
			TRUE /*repaint*/);

		int idRadioButton;
		if (!globals::g_IsFullScreen)
			idRadioButton = IDC_WINDOW_RADIOBUTTON /*1005*/;
		else
			idRadioButton = IDC_FULLSCREEN_RADIOBUTTON /*1004*/;

		HWND hCtrl_RadioButton = GetDlgItem(hDlg, idRadioButton);
		SendMessageA(hCtrl_RadioButton, BM_SETCHECK /*0xf1*/, BST_CHECKED /*1*/, 0);

		HWND hCtrl_Drivers = GetDlgItem(hDlg, IDC_DRIVER_LISTBOX /*1000*/);
		for (int i = 0; i < globals::g_DriverModes_COUNT; i++) {
			SendMessageA(hCtrl_Drivers, LB_ADDSTRING /*0x180*/, 0, (LPARAM)globals::g_DriverModes_TABLE[i].displayName);
		}
		SendMessageA(hCtrl_Drivers, LB_SETCURSEL /*0x186*/, 0, 0);
		SetFocus(hCtrl_Drivers); // set initial focus to the drivers listbox
								 // (despite it being much less-used than the screen modes :P)

		UpdateRadioButtons(hDlg);
		RebuildDeviceModes(hDlg);
		RebuildScreenModes(hDlg);
		return (INT_PTR)FALSE;
	}
	case WM_COMMAND /*0x111*/: {
		WORD msgSource = HIWORD(wParam);
		WORD idCaller  = LOWORD(wParam);

		if (msgSource == 1 /*message from Accelerator*/) {
			if (idCaller == IDC_DEVICE_LISTBOX /*1002*/) {
				int selIndex = (int)SendMessageA((HWND)lParam, LB_GETCURSEL /*0x188*/, 0, 0);
				globals::g_CurrentDeviceMode = &globals::g_DeviceModes_TABLE[selIndex];
			}
			else if (idCaller == IDC_SCREENMODES_LISTBOX /*1003*/) {
				int selIndex = (int)SendMessageA((HWND)lParam, LB_GETCURSEL /*0x188*/, 0, 0);
				SendMessageA((HWND)lParam, LB_GETTEXT /*0x189*/, selIndex, (LPARAM)screenModeText);

				int availableIndex;
				if (GetScreenMode(screenModeText, &availableIndex)) {
					globals::g_CurrentScreenMode = &globals::g_ScreenModes_TABLE[availableIndex];
				}
			}
			else if (idCaller == IDC_DRIVER_LISTBOX /*1000*/) {
				int selIndex = (int)SendMessageA((HWND)lParam, LB_GETCURSEL /*0x188*/, 0, 0);
				globals::g_CurrentDriverMode = &globals::g_DriverModes_TABLE[selIndex];

				UpdateRadioButtons(hDlg);
				RebuildScreenModes(hDlg);
				RebuildDeviceModes(hDlg);
			}
		}
		else if (msgSource == 0 /*message from Menu*/) {
			if (idCaller == IDC_WINDOW_RADIOBUTTON /*1005*/) {
				ChangeFullScreenMode(hDlg, FALSE);
			}
			else if (idCaller == IDC_FULLSCREEN_RADIOBUTTON /*1004*/) {
				ChangeFullScreenMode(hDlg, TRUE);
			}
			else if (idCaller == IDOK /*1*/ || idCaller == IDCANCEL /*2*/) {
				EndDialog(hDlg, LOWORD(wParam) /* end dialog with OK or Cancel button as argument*/);
			}
		}
		return (INT_PTR)TRUE;
	}
	default:
		return (INT_PTR)FALSE;
	}
}

// Change the full screen mode setting, and update the "Screen Mode" / "Window Size" label text.
// <LegoRR.exe @0049d8a0>
void __cdecl lego::dialog::ChangeFullScreenMode(HWND hDlg, BOOL isFullScreen)
{
	globals::g_IsFullScreen = isFullScreen;
	RebuildScreenModes(hDlg);

	// update label next to screen modes listbox
	HWND hCtrl = GetDlgItem(hDlg, IDC_SCREENMODES_LABEL /*1006*/);
	SendMessageA(hCtrl, WM_SETTEXT /*0xc*/, 0, (LPARAM)(isFullScreen ? "Screen Mode" : "Window Size"));
}



// Rebuild (enumerate through) and repopulate the list of screen modes.
// Only screen modes registered as supported by the game will appear in the listbox.
// <LegoRR.exe @0049d8f0>
void __cdecl lego::dialog::RebuildScreenModes(HWND hDlg)
{
	char unsupportedMessage[256];
	HWND hCtrl = GetDlgItem(hDlg, IDC_SCREENMODES_LISTBOX /*1003*/);

	// remove all items from the listbox
	while (SendMessageA(hCtrl, LB_DELETESTRING /*0x182*/, 0, 0) != -1);

	draw::PopulateScreenModes(globals::g_CurrentDriverMode, globals::g_IsFullScreen, globals::g_ScreenModes_TABLE, &globals::g_ScreenModes_COUNT);

	BOOL noSupportedModes = TRUE;
	for (int i = 0; i < globals::g_ScreenModes_COUNT; i++) {
		if (HasRegisteredScreenMode(i)) {
			SendMessageA(hCtrl, LB_ADDSTRING /*0x180*/, 0, (LPARAM)globals::g_ScreenModes_TABLE[i].displayName);

			if (noSupportedModes) {
				globals::g_CurrentScreenMode = &globals::g_ScreenModes_TABLE[i];
				noSupportedModes = FALSE;
			}
		}
	}

	if (noSupportedModes) {
		if (!globals::g_IsFullScreen) {
			int bpp = main::GetDeviceBitsPerPixel();
			std::sprintf(unsupportedMessage, "No supported %i bit modes found", bpp);
		}
		else {
			std::sprintf(unsupportedMessage, "No supported screen modes found");
		}
		SendMessageA(hCtrl, LB_ADDSTRING /*0x180*/, 0, (LPARAM)unsupportedMessage);
	}
	// enable the OK button if we have supported screen modes
	HWND hCtrl_OK = GetDlgItem(hDlg, IDOK /*1*/);
	EnableWindow(hCtrl_OK, !noSupportedModes);
	SendMessageA(hCtrl, LB_SETCURSEL /*0x186*/, 0, 0); // always select the first screen mode on rebuild
}

// Rebuild (enumerate through) and repopulate the list of device modes.
// <LegoRR.exe @0049da40>
void __cdecl lego::dialog::RebuildDeviceModes(HWND hDlg)
{
	HWND hCtrl = GetDlgItem(hDlg, IDC_DEVICE_LISTBOX /*1002*/);

	// remove all items from the listbox
	while (SendMessageA(hCtrl, LB_DELETESTRING /*0x182*/, 0, 0) != -1);

	int selIndex = 0;
	if (draw::PopulateDeviceModes(globals::g_CurrentDriverMode, globals::g_DeviceModes_TABLE, &globals::g_DeviceModes_COUNT)) {

		for (int i = 0; i < globals::g_DeviceModes_COUNT; i++) {
			if (globals::g_DeviceModes_TABLE[i].flags & draw::DEVICEMODE_HARDWARE /*0x2000*/) {
				selIndex = i;
			}
			SendMessageA(hCtrl, LB_ADDSTRING /*0x180*/, 0, (LPARAM)globals::g_DeviceModes_TABLE[i].displayName);
		}
		globals::g_CurrentDeviceMode = &globals::g_DeviceModes_TABLE[selIndex];
	}
	else {
		// no device modes found, put up an error instead
		SendMessageA(hCtrl, LB_ADDSTRING /*0x180*/, 0, (LPARAM)"Error: DirectX6 not installed.");
	}
	SendMessageA(hCtrl, LB_SETCURSEL /*0x186*/, (WPARAM)selIndex, 0);
}

// Register a screen mode that the game supports.
// Although this assigns to a table using the same ScreenMode structure,
//  only the width, height, and bit depth fields are assigned.
// <LegoRR.exe @0049db30>
void __cdecl lego::dialog::RegisterScreenMode(int screenWidth, int screenHeight, int bitDepth)
{
	globals::g_RegisteredScreenModes_TABLE[globals::g_RegisteredScreenModes_COUNT].screenWidth = screenWidth;
	globals::g_RegisteredScreenModes_TABLE[globals::g_RegisteredScreenModes_COUNT].screenHeight = screenHeight;
	globals::g_RegisteredScreenModes_TABLE[globals::g_RegisteredScreenModes_COUNT].bitDepth = bitDepth;
	globals::g_RegisteredScreenModes_COUNT++;
}

// Check if the selected system-available screen mode is supported by the game.
// <LegoRR.exe @0049db90>
BOOL __cdecl lego::dialog::HasRegisteredScreenMode(int selIndex)
{
	///DEBUG:
#ifdef DEBUG_IGNOREREGISTERED
	return TRUE;
#endif

	if (globals::g_RegisteredScreenModes_COUNT == 0)
		return TRUE;

	const draw::ScreenMode* selected = &globals::g_ScreenModes_TABLE[selIndex];

	// check the selected screen mode against all supported screen modes registered by the game
	for (int i = 0; i < globals::g_RegisteredScreenModes_COUNT; i++) {
		const draw::ScreenMode* registered = &globals::g_RegisteredScreenModes_TABLE[i];
		if ((registered->screenWidth == 0 || registered->screenWidth == selected->screenWidth) &&
			(registered->screenHeight == 0 || registered->screenHeight == selected->screenHeight) &&
			(registered->bitDepth == 0 || registered->bitDepth == selected->bitDepth))
		{
			return TRUE;
		}
	}
	return FALSE;
}

// Get the index of a system-available screen mode from the display name used in the listbox.
// <LegoRR.exe @0049dc10>
BOOL __cdecl lego::dialog::GetScreenMode(const char* displayName, int* out_index)
{
	// unlike Setup_HasRegisteredScreenMode, this returns false when COUNT == 0

	for (int i = 0; i < globals::g_ScreenModes_COUNT; i++) {
		// no case-insensitive check, since these are exact names taken from the structures
		if (std::strcmp(globals::g_ScreenModes_TABLE[0].displayName, displayName) == 0) {
			*out_index = i;
			return TRUE;
		}
	}
	return FALSE;
}

// Update FullScreen/Window radio buttons depending on whether
// the currently selected driver allows windowed mode.
// <LegoRR.exe @0049dc90>
void __cdecl lego::dialog::UpdateRadioButtons(HWND hDlg)
{
	HWND hCtrl_Window, hCtrl_FullScreen;
	if (!(globals::g_CurrentDriverMode->flags & draw::DRIVERMODE_NOGUID_20 /*0x20*/)) {
		globals::g_IsFullScreen_Backup = globals::g_IsFullScreen; // store the original full screen mode, we can
																  // revert this when windowed mode is supported again.
		ChangeFullScreenMode(hDlg, TRUE);

		hCtrl_Window = GetDlgItem(hDlg, IDC_WINDOW_RADIOBUTTON /*1005*/);
		SendMessageA(hCtrl_Window, BM_SETCHECK /*0xf1*/, BST_UNCHECKED /*0*/, 0);
		EnableWindow(hCtrl_Window, FALSE); // disable Window radio button

		hCtrl_FullScreen = GetDlgItem(hDlg, IDC_FULLSCREEN_RADIOBUTTON /*1004*/);
		SendMessageA(hCtrl_FullScreen, BM_SETCHECK /*0xf1*/, BST_CHECKED   /*1*/, 0);
	}
	else {
		hCtrl_Window = GetDlgItem(hDlg, IDC_WINDOW_RADIOBUTTON /*1005*/);
		EnableWindow(hCtrl_Window, TRUE); // re-enable the Window radio button if previously disabled

		// was previous state before disabling Windowed? if so, change it back
		if (!globals::g_IsFullScreen_Backup) {
			ChangeFullScreenMode(hDlg, FALSE);

			hCtrl_FullScreen = GetDlgItem(hDlg, IDC_FULLSCREEN_RADIOBUTTON /*1004*/);
			SendMessageA(hCtrl_FullScreen, BM_SETCHECK /*0xf1*/, BST_UNCHECKED /*0*/, 0);

			// No need to fetch this again?
			hCtrl_Window = GetDlgItem(hDlg, IDC_WINDOW_RADIOBUTTON /*1005*/);
			SendMessageA(hCtrl_Window, BM_SETCHECK /*0xf1*/, BST_CHECKED   /*1*/, 0);
		}
	}
}

#pragma endregion
