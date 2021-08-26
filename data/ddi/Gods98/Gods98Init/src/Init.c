
#include <ddraw.h>

#include "..\..\Gods98\inc\Standard.h"
#include "..\..\Gods98\inc\Errors.h"
#include "..\..\Gods98\inc\Main.h"
#include "..\..\Gods98\inc\DirectDraw.h"
#include "..\..\Gods98\inc\Input.h"

#include "..\Inc\Init.h"

#include "..\Resources\resource.h"

Init_Globs initGlobs;

BOOL Init_Initialise(BOOL setup, BOOL debug, BOOL best, BOOL window, LPUCHAR noHALMsg){

	SLONG rval = IDOK;
	BOOL ok;

	initGlobs.selDriver = NULL;
	initGlobs.selDevice = NULL;
	initGlobs.selMode = NULL;
	initGlobs.selFullScreen = initGlobs.wasFullScreen = FALSE;
	initGlobs.validModeCount = 0;

//	Init_AddValidMode(0, 0, 8);
//	Init_AddValidMode(0, 0, 16);			// Any 16bit mode
//	Init_AddValidMode(0, 0, 24);
//	Init_AddValidMode(0, 0, 32);

//	Init_AddValidMode(640, 400, 16);
//	Init_AddValidMode(640, 400, 32);
//	if (debug) Init_AddValidMode(640, 480, 8);
	Init_AddValidMode(640, 480, 16);
//	Init_AddValidMode(640, 480, 24);
	Init_AddValidMode(800, 600, 16);
	Init_AddValidMode(1024, 768, 16);

	if (debug) {
		Init_AddValidMode(800, 600, 16);
		Init_AddValidMode(1024, 768, 16);
	}
//	Init_AddValidMode(640, 480, 32);

	DirectDraw_EnumDrivers(initGlobs.drivers, &initGlobs.driverCount);
	if (initGlobs.driverCount) {

		initGlobs.selDriver = &initGlobs.drivers[0];

		if (best) {

			SLONG loop, sub;
			ULONG mode;
			BOOL found = FALSE;

			initGlobs.selFullScreen = !window;
			rval = IDOK;

			for (loop=initGlobs.driverCount-1 ; loop>=0 ; loop--) {
				if (DirectDraw_EnumDevices(&initGlobs.drivers[loop], initGlobs.devices, &initGlobs.deviceCount)) {
					DirectDraw_EnumModes(&initGlobs.drivers[loop], initGlobs.selFullScreen, initGlobs.modes, &initGlobs.modeCount);
					for (mode=0 ; mode<initGlobs.modeCount ; mode++) {
						if (Init_IsValidMode(mode)) {
							for (sub=initGlobs.deviceCount-1 ; sub>=0 ; sub--) {
//								if ((initGlobs.devices[sub].flags & DIRECTDRAW_FLAG_DEVICE_HARDWARE) || 0 == loop) {
								if (initGlobs.devices[sub].flags & DIRECTDRAW_FLAG_DEVICE_HARDWARE) {
									initGlobs.selDriver = &initGlobs.drivers[loop];
									initGlobs.selDevice = &initGlobs.devices[sub];
									initGlobs.selMode = &initGlobs.modes[mode];
									found = TRUE;
									break;
								}
							}
							break;
						}
					}
				} else {
					MessageBox(NULL, "Please install DirectX version 6 or later", "Error", MB_OK);
					return FALSE;
				}
				if (TRUE == found) break;
			}

			if (!found) {
				MessageBox(NULL, noHALMsg, "Error", MB_OK);
				return FALSE;
			}

		} else {
			if (setup) rval = DialogBox(Main_hInst(), MAKEINTRESOURCE(IDD_MODEDIALOG), Main_hWnd(), (DLGPROC)Init_DialogProc);
		}

		if (IDOK == rval){

			if (initGlobs.selFullScreen) ok = DirectDraw_SetupFullScreen(initGlobs.selDriver, initGlobs.selDevice, initGlobs.selMode);
			else if (initGlobs.selMode) ok = DirectDraw_SetupWindowed(initGlobs.selDevice, 100, 100, initGlobs.selMode->width, initGlobs.selMode->height);
			else ok = DirectDraw_SetupWindowed(initGlobs.selDevice, 40, 40, 640, 480);

			return ok;

		} else if (-1 == rval) Error_Warn(TRUE, "Cannot create dialog box");

	} else Error_Warn(TRUE, "Cannot Enumerate Drivers");
	
	return FALSE;
}

static BOOL CALLBACK Init_DialogProc(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam){

	ULONG loop;

	if (WM_INITDIALOG == uMsg){

		HWND hWndList, hWndButton, hWndDesktop;
		RECT deskRect, dlgRect;
		ULONG xPos, yPos;

		hWndDesktop = GetDesktopWindow();
		GetWindowRect(hWndDesktop, &deskRect);
		GetWindowRect(hWndDlg, &dlgRect);
		xPos = (deskRect.right / 2) - ((dlgRect.right - dlgRect.left) / 2);
		yPos = (deskRect.bottom / 2) - ((dlgRect.bottom - dlgRect.top) / 2);
		MoveWindow(hWndDlg, xPos, yPos, dlgRect.right - dlgRect.left, dlgRect.bottom - dlgRect.top, TRUE);

		if (initGlobs.selFullScreen) hWndButton = GetDlgItem(hWndDlg, IDC_FULLSCREEN);
		else hWndButton = GetDlgItem(hWndDlg, IDC_WINDOW);
		SendMessage(hWndButton, BM_SETCHECK, BST_CHECKED, 0);

		hWndList = GetDlgItem(hWndDlg, IDC_DRIVER);
		for (loop=0 ; loop<initGlobs.driverCount ; loop++) SendMessage(hWndList, LB_ADDSTRING, 0, (LPARAM) initGlobs.drivers[loop].desc);
		SendMessage(hWndList, LB_SETCURSEL, 0, 0);
		SetFocus(hWndList);

		Init_HandleWindowButton(hWndDlg);
		Init_SetDeviceList(hWndDlg);
		Init_SetModeList(hWndDlg);

		return FALSE;

	} else if (WM_COMMAND == uMsg){

		if (LBN_SELCHANGE == HIWORD(wParam)){
//			Error_Debug(Error_Format("Selection changed on list box #%i (hWnd == 0x%x)\n", LOWORD(wParam), lParam));
			
			if (IDC_DEVICE == LOWORD(wParam)){

				initGlobs.selDevice = &initGlobs.devices[SendMessage((HWND)lParam, LB_GETCURSEL, 0, 0)];
	
			} else if (IDC_MODE == LOWORD(wParam)){

				ULONG num;
				UCHAR desc[1024];
				ULONG mode;

				num = SendMessage((HWND)lParam, LB_GETCURSEL, 0, 0);
				SendMessage((HWND)lParam, LB_GETTEXT, num, (LPARAM) desc);
				if (Init_GetMode(desc, &mode)) initGlobs.selMode = &initGlobs.modes[mode];

			} else if (IDC_DRIVER == LOWORD(wParam)){

				initGlobs.selDriver = &initGlobs.drivers[SendMessage((HWND)lParam, LB_GETCURSEL, 0, 0)];

				Init_HandleWindowButton(hWndDlg);
				Init_SetModeList(hWndDlg);
				Init_SetDeviceList(hWndDlg);
				
			}

		} else if (BN_CLICKED == HIWORD(wParam)){

			if (IDC_WINDOW == LOWORD(wParam)) Init_SetFullScreen(hWndDlg, FALSE);
			if (IDC_FULLSCREEN == LOWORD(wParam)) Init_SetFullScreen(hWndDlg, TRUE);
			else if (IDOK == LOWORD(wParam)) EndDialog(hWndDlg, wParam);
			else if (IDCANCEL == LOWORD(wParam)) EndDialog(hWndDlg, wParam);
		}

		return TRUE;
	}

	return FALSE;
}


static VOID Init_SetFullScreen(HWND hWndDlg, BOOL on){

	HWND hWndText;

	initGlobs.selFullScreen = on;
	Init_SetModeList(hWndDlg);
	hWndText = GetDlgItem(hWndDlg, IDC_MODELISTTEXT);
	if (on) SendMessage(hWndText, WM_SETTEXT, 0, (LPARAM) "Screen Mode");
	else SendMessage(hWndText, WM_SETTEXT, 0, (LPARAM) "Window Size");
}	

static VOID Init_SetModeList(HWND hWndDlg){

	ULONG loop;
	HWND hWndList, hWndButton;
	BOOL first = TRUE;

	hWndList = GetDlgItem(hWndDlg, IDC_MODE);
	
	// Clear the existing list (if any)...
	while (-1 != SendMessage(hWndList, LB_DELETESTRING, 0, 0)) ;

	DirectDraw_EnumModes(initGlobs.selDriver, initGlobs.selFullScreen, initGlobs.modes, &initGlobs.modeCount);
	for (loop=0 ; loop<initGlobs.modeCount ; loop++) {
		if (Init_IsValidMode(loop)) {
			SendMessage(hWndList, LB_ADDSTRING, 0, (LPARAM) initGlobs.modes[loop].desc);
			if (first) {
				initGlobs.selMode = &initGlobs.modes[loop];
				first = FALSE;
			}
		}
	}

	hWndButton = GetDlgItem(hWndDlg, IDOK);

	if (first) {
		UCHAR msg[256];
		if (!initGlobs.selFullScreen) sprintf(msg, "No supported %i bit modes found", Main_GetWindowsBitDepth());
		else sprintf(msg, "No supported screen modes found");
		SendMessage(hWndList, LB_ADDSTRING, 0, (LPARAM) msg);
		EnableWindow(hWndButton, FALSE);
	} else EnableWindow(hWndButton, TRUE);

	SendMessage(hWndList, LB_SETCURSEL, 0, 0);
}

static VOID Init_SetDeviceList(HWND hWndDlg){

	ULONG loop, best = 0;
	HWND hWndList;

	hWndList = GetDlgItem(hWndDlg, IDC_DEVICE);
	
	// Clear the existing list (if any)...
	while (-1 != (loop = SendMessage(hWndList, LB_DELETESTRING, 0, 0))) ;

	if (DirectDraw_EnumDevices(initGlobs.selDriver, initGlobs.devices, &initGlobs.deviceCount)) {

		for (loop=0 ; loop<initGlobs.deviceCount ; loop++) {
			if (initGlobs.devices[loop].flags & DIRECTDRAW_FLAG_DEVICE_HARDWARE) best = loop;
			SendMessage(hWndList, LB_ADDSTRING, 0, (LPARAM) initGlobs.devices[loop].desc);
		}
		initGlobs.selDevice = &initGlobs.devices[best];

	} else {
		SendMessage(hWndList, LB_ADDSTRING, 0, (LPARAM) "Error: DirectX6 not installed.");
	}

	SendMessage(hWndList, LB_SETCURSEL, best, 0);
}

static VOID Init_AddValidMode(ULONG width, ULONG height, ULONG depth){

	initGlobs.validModes[initGlobs.validModeCount].width = width;
	initGlobs.validModes[initGlobs.validModeCount].height = height;
	initGlobs.validModes[initGlobs.validModeCount].bitDepth = depth;

	initGlobs.validModeCount++;
}

static BOOL Init_IsValidMode(ULONG mode){

	if (initGlobs.validModeCount){

		ULONG loop;

		for (loop=0 ; loop<initGlobs.validModeCount ; loop++){
			if ((0 == initGlobs.validModes[loop].width || initGlobs.validModes[loop].width == initGlobs.modes[mode].width) &&
				(0 == initGlobs.validModes[loop].height || initGlobs.validModes[loop].height == initGlobs.modes[mode].height) &&
				(0 == initGlobs.validModes[loop].bitDepth || initGlobs.validModes[loop].bitDepth == initGlobs.modes[mode].bitDepth)){

				return TRUE;
			}
		}

		return FALSE;

	} else return TRUE;
}

static BOOL Init_GetMode(LPUCHAR name, LPULONG mode){

	ULONG loop;

	for (loop=0 ; loop<initGlobs.modeCount ; loop++){
		if (0 == strcmp(initGlobs.modes[loop].desc, name)) {

			*mode = loop;
			return TRUE;
		}
	}

	return FALSE;
}

VOID Init_HandleWindowButton(HWND hWndDlg){

	HWND hWndButton;

	if (initGlobs.selDriver->flags & DIRECTDRAW_FLAG_DRIVER_WINDOWOK){

		hWndButton = GetDlgItem(hWndDlg, IDC_WINDOW);
		EnableWindow(hWndButton, TRUE);
		if (!initGlobs.wasFullScreen){
			Init_SetFullScreen(hWndDlg, FALSE);
			hWndButton = GetDlgItem(hWndDlg, IDC_FULLSCREEN);
			SendMessage(hWndButton, BM_SETCHECK, BST_UNCHECKED, 0);
			hWndButton = GetDlgItem(hWndDlg, IDC_WINDOW);
			SendMessage(hWndButton, BM_SETCHECK, BST_CHECKED, 0);
		}

	} else {

		initGlobs.wasFullScreen = initGlobs.selFullScreen;
		Init_SetFullScreen(hWndDlg, TRUE);
		hWndButton = GetDlgItem(hWndDlg, IDC_WINDOW);
		SendMessage(hWndButton, BM_SETCHECK, BST_UNCHECKED, 0);
		EnableWindow(hWndButton, FALSE);
		hWndButton = GetDlgItem(hWndDlg, IDC_FULLSCREEN);
		SendMessage(hWndButton, BM_SETCHECK, BST_CHECKED, 0);

	}
}
