
#include <windows.h>
#include <windowsx.h>

#include "Standard.h"
#include "DirectInput.h"
#include "Projectiles.h"
#include "Collision.h"
#include "ModelClip.h"
#include "Viewports.h"
#include "Surfaces.h"
#include "DirectX.h"
#include "Render.h"
#include "Config.h"
#include "Images.h"
#include "Lights.h"
#include "Errors.h"
#include "Frames.h"
#include "States.h"
#include "Sound.h"
#include "Media.h"
#include "Utils.h"
#include "Fonts.h"
#include "Files.h"
#include "Lists.h"
#include "Mesh.h"
#include "Anim.h"
#include "Lwo.h"
#include "Lws.h"
#include "Mem.h"
#include "Wad.h"
#include "DXT.h"
#include "Main.h"

struct MainGlobs {

	LPUCHAR exeName;
	HWND hWnd;
	HINSTANCE hInstance;

	LPUCHAR errorMessage[MainErrorType_Count];
	LPUCHAR errorMessageCaption;

	struct MainSelectModeData modeData;

	BOOL appActive;

	struct List *stateList;

	BOOL (*funcReportError)(enum MainErrorType type);
	BOOL (*funcSelectMode)(struct MainSelectModeData *data);
	VOID (*flipCallback)(REAL delta, LPVOID data);
	LPVOID flipCallbackData;

	ULONG desiredFrameTime;

	ULONG flags;

} mainGlobs = { NULL };

__inline HWND Main_hWnd(VOID)				{ return mainGlobs.hWnd; }
__inline HINSTANCE Main_hInstance(VOID)		{ return mainGlobs.hInstance; }
__inline VOID Main_ShowWindow(BOOL on)		{ ShowWindow(mainGlobs.hWnd, on); }
__inline BOOL Main_AppActive(VOID)			{ return mainGlobs.appActive; }

#pragma comment ( lib , "winmm" )

VOID Main_Abort(VOID) {

	State_Abort();
	CoUninitialize();
	exit(0);
}

VOID Main_ReportError(ULONG type) {

	BOOL abort;

	Error_Fatal(type > MainErrorType_Count, "Invalid error message type");

	if (mainGlobs.funcReportError) abort = mainGlobs.funcReportError(type);
	else abort = (IDCANCEL == MessageBox(NULL, mainGlobs.errorMessage[type], mainGlobs.errorMessageCaption, MB_OKCANCEL));

	if (abort) Main_Abort();
}

VOID Main_SetSelectModeFunction(BOOL (*funcSelectMode)(struct MainSelectModeData *data)) {

	mainGlobs.funcSelectMode = funcSelectMode;
}

VOID Main_SetReportErrorFunction(BOOL (*funcReportError)(enum MainErrorType type)) {

	mainGlobs.funcReportError = funcReportError;
}

VOID Main_SetFlipCallback(VOID (*flipCallback)(REAL delta, LPVOID data), LPVOID data) {

	mainGlobs.flipCallback = flipCallback;
	mainGlobs.flipCallbackData = data;
}

VOID Main_SetFlags(ULONG flags, BOOL set) {

	Error_Fatal(flags & ~MAIN_FLAG_USERMASK, "Invalid flags");
	Error_Fatal(!(mainGlobs.flags & MAIN_FLAG_REGISTER), "Cannot call this function outside of Game_Register()");

	if (mainGlobs.flags & MAIN_FLAG_REGISTER) {

		if (set) mainGlobs.flags |= (flags & MAIN_FLAG_USERMASK);
		else mainGlobs.flags &= ~(flags & MAIN_FLAG_USERMASK);

	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	MSG msg;
	WNDCLASS wClass;

	CoInitialize(NULL);

	Main_SetupName(GetCommandLine());
	mainGlobs.errorMessageCaption = mainGlobs.exeName;
	mainGlobs.errorMessage[MainErrorType_InvalidPixelFormat] = "Please select a desktop bit depth that your graphics card can support for 3D acceleration";
	mainGlobs.errorMessage[MainErrorType_SoundInitialise] = "Could not initialise sound";

	State_Initialise();
	mainGlobs.flags |= MAIN_FLAG_REGISTER;
	Game_Register();
	mainGlobs.flags &= ~MAIN_FLAG_REGISTER;

	File_Initialise();
	Wad_Initialise();
	Lws_Initialise();
	Anim_Initialise();
	Error_Initialise();
	Frame_Initialise();
	Mesh_Initialise();
	Font_Initialise();
	Light_Initialise();
	Image_Initialise();
	Config_Initialise();
	Surface_Initialise();
	ModelClip_Initialise();
	Collision_Initialise();
	Projectile_Initialise();
	Media_Initialise();

	mainGlobs.flags |= MAIN_FLAG_CENTERWINDOW;

	wClass.cbClsExtra		= 0;
	wClass.cbWndExtra		= 0;
	wClass.hbrBackground	= NULL;
	wClass.hCursor			= NULL;
	wClass.hIcon			= NULL;
	wClass.hInstance		= hInstance;
	wClass.lpfnWndProc		= Main_WndProc;
	wClass.lpszClassName	= mainGlobs.exeName;
	wClass.lpszMenuName		= NULL;
	wClass.style			= 0;
	
	RegisterClass(&wClass);
	
	if (Main_InitWindow(hInstance, mainGlobs.exeName, nCmdShow)){

		ULONG mode, argc;
		LPUCHAR line, argv[MAIN_MAXARGS];

		DirectInput_Initialise();
		Texture_Initialise();
		DirectX_Initialise();
		DXT_Initialise();

//#pragma message ( "REINSTATE ME..." )
		DirectX_FindHardwareMode(&mainGlobs.modeData.driverIndex, &mainGlobs.modeData.deviceIndex);

		line = Mem_CopyString(lpCmdLine);
		argc = Util_WSTokenise(line, argv, MAIN_MAXARGS, TRUE);
		Main_ProcessArguments(argc, argv);
		Mem_Free(line);

		File_LoadStatusIO(TRUE);

		if (!(mainGlobs.flags & MAIN_FLAG_NOSOUND)) Sound_Initialise();

		if (0 == mainGlobs.modeData.width) mainGlobs.modeData.width = 640;
		if (0 == mainGlobs.modeData.height) mainGlobs.modeData.height = 480;
		if (0 == mainGlobs.modeData.depth) mainGlobs.modeData.depth = 16;

		if (NULL == mainGlobs.funcSelectMode || mainGlobs.funcSelectMode(&mainGlobs.modeData)) {
			if (DirectX_FindMode(mainGlobs.modeData.driverIndex, mainGlobs.modeData.width, mainGlobs.modeData.height, mainGlobs.modeData.depth, &mode)) {
//				if (!mainGlobs.modeData.fullScreen) Main_SetWindowSize(mainGlobs.modeData.width, mainGlobs.modeData.height, FALSE);
				if (DirectX_Setup(mainGlobs.modeData.fullScreen, mainGlobs.modeData.driverIndex, mainGlobs.modeData.deviceIndex, mode, mainGlobs.flags & MAIN_FLAG_EMULATIONMODE)) {

					REAL time = 1.0f;
					ULONG lastTime, currTime, frameTime;

					Main_ShowWindow(TRUE);
					ShowCursor(FALSE);
					DirectX_ClearBackBuffer(COLOUR_FROMCHAR(0, 0, 0));
					DirectX_Flip();

	//				Game_Initialise();
					Render_Initialise();

					lastTime = timeGetTime();

					while (!(mainGlobs.flags & MAIN_FLAG_EXIT)) {
						
						// Handle window messages...
						if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
							TranslateMessage(&msg);
							DispatchMessage(&msg);
						}

						if (mainGlobs.flags & MAIN_FLAG_MINIMIZED) {

							WaitMessage();

						} else {

							DirectInput_Update();

//							if (FALSE == Game_Loop_Old(time)) {
							if (FALSE == State_Loop(time)) {
								mainGlobs.flags |= MAIN_FLAG_EXIT;
								break;
							}

							if (mainGlobs.flipCallback) mainGlobs.flipCallback(time, mainGlobs.flipCallbackData);
							Sound_Update(time);
							DirectX_Flip();
						}

						currTime = timeGetTime();
						frameTime = currTime - lastTime;
						lastTime = currTime;

						time = (REAL) frameTime / (1000.0f / STANDARD_FRAMERATE);
					}

					State_Abort();

					ShowCursor(TRUE);

					Error_Warn(TRUE, "***********************************************************");
					Error_Warn(TRUE, "**** Shutting down");
					Error_Warn(TRUE, "***********************************************************");

//					Game_Shutdown();
					Light_RemoveAll();
					Viewport_RemoveAll();
					Collision_Shutdown();
					Config_Shutdown();
					Anim_Shutdown();
					Lws_Shutdown();
					Mesh_Shutdown();
					Texture_Shutdown();
					Frame_Shutdown();
					Font_Shutdown();
					Image_Shutdown();
					Sound_Shutdown();
					Surface_Shutdown();

#ifdef _DEBUG
					Wad_Debug_Dump("waddump.txt");
#endif // _DEBUG

					File_LoadStatusIO(FALSE);

#ifdef _WAD_BUILD
					Wad_SaveHeaderFile();
#endif // _WAD_BUILD

					File_FreeBuffers();
					File_Shutdown();
					List_Shutdown();
					DirectX_CloseDown(TRUE);
				}
			} else Error_Fatal(TRUE, Error_Format("Cannot find a %ix%ix%i screen mode", mainGlobs.modeData.width, mainGlobs.modeData.height, mainGlobs.modeData.depth));
		}
	}

	DestroyWindow(mainGlobs.hWnd);
	Mem_Free(mainGlobs.exeName);

	Mem_Dump(NULL);
     
	Error_Shutdown();

	CoUninitialize();

	return msg.wParam;
}

VOID Main_Sleep(ULONG time) {

	Sleep(time);
}

VOID Main_ProcessArguments(ULONG argc, LPUCHAR *argv) {

	BOOL primary = FALSE, fullScreen = FALSE, emulationMode = FALSE;
	BOOL buildLoadStatus = FALSE, noSound = FALSE;
#ifdef _WAD_BUILD
	LPUCHAR wadHeader = NULL, buildWad = NULL, extractWad = NULL;
#endif // _WAD_BUILD
	LPUCHAR loadWad = NULL;
	BOOL wadLoaded;

	Util_GetArguments_BOOL(argc, argv, "primary", &primary, "fullscreen", &mainGlobs.modeData.fullScreen, "emulationmode", &emulationMode, "buildloadstatus", &buildLoadStatus, "nosound", &noSound, NULL);
	Util_GetArguments_ULONG(argc, argv, "device", &mainGlobs.modeData.deviceIndex, "width", &mainGlobs.modeData.width, "height", &mainGlobs.modeData.height, "driver", &mainGlobs.modeData.driverIndex, "depth", &mainGlobs.modeData.depth, NULL);
#ifdef _WAD_BUILD
	Util_GetArguments_LPUCHAR(argc, argv, "wadheader", &wadHeader, "buildwad", &buildWad, "extractwad", &extractWad, NULL);
#endif // _WAD_BUILD
	Util_GetArguments_LPUCHAR(argc, argv, "loadwad", &loadWad, NULL);

#ifdef _WAD_BUILD

	if (wadHeader) {

		Error_Fatal(NULL != loadWad, "Cannot load a wad when -wadheader [header file] is specified");
	
		Wad_SetBuild("header.wad");

		if (buildWad) {
			if (Wad_Build(buildWad)) MessageBox(NULL, "Wad build complete", "Wad Build", MB_OK);
			else MessageBox(NULL, "Wad build failed", "Wad Build Error", MB_OK);
			exit(0);
		}

	} else {

		Error_Fatal(NULL != buildWad, "Cannot build a wad without -wadheader [header file] specified");

#endif // _WAD_BUILD

		if (loadWad) wadLoaded = Wad_Load(loadWad, TRUE);
		else {

			UCHAR defaultWadFile[FILE_MAXPATH];

			sprintf(defaultWadFile, "%s.wad", mainGlobs.exeName);
			wadLoaded = Wad_Load(defaultWadFile, TRUE);
		}

#ifdef _WAD_BUILD

		if (wadLoaded && extractWad) {
			
			Wad_Extract(extractWad);
			MessageBox(NULL, "Wad extract complete", "Wad builder", MB_OK);
			exit(0);
		}

		Error_Fatal(NULL != extractWad && !wadLoaded, "Cannot extract wad - no wad loaded");
	}

#endif // _WAD_BUILD

	if (buildLoadStatus) File_SetBuildLoadStatus(TRUE);
	if (primary) mainGlobs.modeData.driverIndex = 0;
	if (emulationMode) mainGlobs.flags |= MAIN_FLAG_EMULATIONMODE;
	if (noSound) mainGlobs.flags |= MAIN_FLAG_NOSOUND;
}

VOID Main_SetupName(LPUCHAR cmdLine) {

	LPUCHAR line = Mem_CopyString(cmdLine);
	LPUCHAR s, t;
	BOOL inquotes = FALSE;

	// Terminate after the executable path name...
	for (s=line ; '\0'!=*s ; s++) {
		if ('\"' == *s) inquotes = !inquotes;
		else if (!inquotes && ' ' == *s) {
			*s = '\0';
			break;
		}
	}

	// Find the start of the filename...
	for (s=t=line ; '\0'!=*s ; s++) if ('\\' == *s) t=(s+1);

	// Remove the end quote...
	if ('\"' == t[strlen(t)-1]) t[strlen(t)-1] = '\0';

	// Strip the '.exe' from then end...
	if (s = Util_StrIStr(t, ".exe")) *s = '\0';

	mainGlobs.exeName = Mem_CopyString(t);

	Mem_Free(line);
}

__inline static ULONG Main_GetWindowedStyle(VOID) {

	ULONG style = WS_OVERLAPPED | WS_CAPTION;
	
	if (mainGlobs.flags & MAIN_FLAG_RESIZABLE) style |= WS_SIZEBOX;

	return style;
}

BOOL Main_InitWindow(HINSTANCE hInstance, LPUCHAR title, int nCmdShow) {

	if (mainGlobs.hWnd = CreateWindow(title, title, Main_GetWindowedStyle(),
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL)){

		mainGlobs.hInstance = hInstance;

		ShowWindow(mainGlobs.hWnd, FALSE);
		UpdateWindow(mainGlobs.hWnd);
	
		return TRUE;
	}

	return FALSE;
}

VOID Main_SetTitle(LPUCHAR title) {

	SetWindowText(Main_hWnd(), title);
}

VOID Main_SetWindowSize(ULONG width, ULONG height, BOOL fullscreen) {

	RECT desktopRect, newRect;
	POINT cPos;
	ULONG style = 0;

	if (fullscreen) {

		GetWindowRect(GetDesktopWindow(), &newRect);

	} else {

		style = Main_GetWindowedStyle();

		GetWindowRect(GetDesktopWindow(), &desktopRect);

		if (mainGlobs.flags & MAIN_FLAG_CENTERWINDOW) {
		
			cPos.x = (desktopRect.right - desktopRect.left) / 2;
			cPos.y = (desktopRect.bottom - desktopRect.top) / 2;
			
			newRect.left = cPos.x - (width / 2);
			newRect.top = cPos.y - (height / 2);

			mainGlobs.flags &= ~MAIN_FLAG_CENTERWINDOW;
		
		} else {

			RECT offset = { 0 };

			AdjustWindowRect(&offset, style, FALSE);
			GetWindowRect(Main_hWnd(), &newRect);
			newRect.left -= offset.left;
			newRect.top -= offset.top;
		}
		
		newRect.right = newRect.left + width;
		newRect.bottom = newRect.top + height;

		AdjustWindowRect(&newRect, style, FALSE);
	}

	SetWindowPos(mainGlobs.hWnd, NULL, newRect.left, newRect.top, newRect.right - newRect.left, newRect.bottom - newRect.top, SWP_NOZORDER);
	SetWindowLong(mainGlobs.hWnd, GWL_STYLE, style);
	ShowWindow(mainGlobs.hWnd, SW_SHOW);

	SetActiveWindow(mainGlobs.hWnd);
}

VOID Main_HandleResize(WPARAM wParam, LPARAM lParam) {

	ULONG mode;

	switch (wParam) {
	case SIZE_MAXIMIZED:

		mainGlobs.flags &= ~MAIN_FLAG_MINIMIZED;
		if (DirectX_FindMode(mainGlobs.modeData.driverIndex, mainGlobs.modeData.width, mainGlobs.modeData.height, mainGlobs.modeData.depth, &mode)) {
			DirectX_Setup(TRUE, mainGlobs.modeData.driverIndex, mainGlobs.modeData.deviceIndex, mode, mainGlobs.flags & MAIN_FLAG_EMULATIONMODE);
		}

		break;

	case SIZE_MINIMIZED:

		mainGlobs.flags |= MAIN_FLAG_MINIMIZED;
		
		break;

	default:

		if ((mainGlobs.flags & MAIN_FLAG_MINIMIZED) && DirectX_FullScreen()) Main_HandleResize(SIZE_MAXIMIZED, 0);
		else DirectX_Setup(FALSE, mainGlobs.modeData.driverIndex, mainGlobs.modeData.deviceIndex, DirectX_FindWindowedMode(mainGlobs.hWnd), mainGlobs.flags & MAIN_FLAG_EMULATIONMODE);

		mainGlobs.flags &= ~MAIN_FLAG_MINIMIZED;

		break;
	}
}

VOID Main_HandleMove(WPARAM wParam, LPARAM lParam) {

	DirectX_SetFrontRect();
}

VOID Main_HandleKey(WPARAM wParam, LPARAM lParam) {

	switch (wParam) {

	case VK_RETURN:

		mainGlobs.flags &= ~MAIN_FLAG_MINIMIZED;

		if (DirectX_FullScreen()) {
			DirectX_RestoreDisplayMode();
			mainGlobs.flags |= MAIN_FLAG_CENTERWINDOW;
			Main_SetWindowSize(mainGlobs.modeData.width, mainGlobs.modeData.height, FALSE);
		} else Main_HandleResize(SIZE_MAXIMIZED, 0);

		break;
	}
}

LRESULT CALLBACK Main_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	if (!(mainGlobs.flags & MAIN_FLAG_EXIT)) {

		switch (message) {
		case WM_ACTIVATEAPP:	mainGlobs.appActive = (BOOL) wParam;				break;
		case WM_SIZE:			Main_HandleResize(wParam, lParam);					break;
		case WM_MOVE:			Main_HandleMove(wParam, lParam);					break;
		case WM_SYSKEYUP:		Main_HandleKey(wParam, lParam);						break;
		case WM_MOUSEMOVE:		Main_HandleMouseMove(wParam, lParam);				break;
		case WM_LBUTTONDOWN:	Main_HandleLeftButtonDown(wParam, lParam);			break;
		case WM_LBUTTONUP:		Main_HandleLeftButtonUp(wParam, lParam);			break;
		case WM_RBUTTONDOWN:	Main_HandleRightButtonDown(wParam, lParam);			break;
		case WM_RBUTTONUP:		Main_HandleRightButtonUp(wParam, lParam);			break;
		case WM_CLOSE:
		case WM_QUIT:
		case WM_DESTROY:
		
			if (!(mainGlobs.flags & MAIN_FLAG_DISABLEALTF4)) {
				mainGlobs.flags |= MAIN_FLAG_EXIT;
			}

			return 0;			
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

// gets the position of the mouse and passes it on to the ouse handler in DirectInput
VOID Main_HandleMouseMove(WPARAM wParam, LPARAM lParam) {

	ULONG	xPos, yPos;

	xPos = GET_X_LPARAM(lParam); 
	yPos = GET_Y_LPARAM(lParam); 

	DirectInput_SetMousePos(xPos, yPos);

}

// set the flag for the left button down (TRUE = it is down)
VOID Main_HandleLeftButtonDown(WPARAM wParam, LPARAM lParam) {

	DirectInput_SetLeftButtonDown(TRUE);
}

// tell it we've released the mouse button
VOID Main_HandleLeftButtonUp(WPARAM wParam, LPARAM lParam) {

	DirectInput_SetLeftButtonDown(FALSE);
}

// set the flag for the right button down (TRUE = it is down)
VOID Main_HandleRightButtonDown(WPARAM wParam, LPARAM lParam) {

	DirectInput_SetRightButtonDown(TRUE);
}

// tell it we've released the mouse button
VOID Main_HandleRightButtonUp(WPARAM wParam, LPARAM lParam) {

	DirectInput_SetRightButtonDown(FALSE);
}
