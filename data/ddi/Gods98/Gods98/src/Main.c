
#include <d3drmwin.h>

#include "..\inc\Standard.h"
#include "..\inc\Errors.h"
#include "..\inc\Memory.h"
#include "..\inc\Input.h"
#include "..\inc\Utils.h"
#include "..\inc\DirectDraw.h"
#include "..\inc\Draw.h"
#include "..\inc\Main.h"
#include "..\inc\Config.h"
#include "..\inc\Files.h"
#include "..\inc\Sound.h"
#include "..\inc\dxbug.h"
#include "..\inc\Animation.h"
#include "..\inc\Registry.h"
#include "..\inc\Fonts.h"

#pragma comment ( lib , "d3drm" )
#pragma comment ( lib , "ddraw" )
#pragma comment ( lib , "dxguid" )
#pragma comment ( lib , "winmm" )

// Yes, does exactly what it says...
//#define MAIN_MERGEMOUSEBUTTONS

Main_Globs mainGlobs = { NULL };

extern VOID Gods_Go(LPUCHAR programName);
extern BOOL Init_Initialise(BOOL setup, BOOL debug, BOOL best, BOOL window, LPUCHAR noHALMsg);
static VOID Main_ParseCommandLine(LPUCHAR lpszCmdLine, LPBOOL nosound, LPBOOL insistOnCD);

#ifdef _TESTCODE
ULONG Main_StartTime, Main_StartClock;
#endif // _TESTCODE


/*************************************************************************************************************************
 ****
 **** Command Line Options:
 ****
 **** -nosound					-	Disable all sound.
 **** -debug					-	Allow higher screen resolutions/debug functions
 **** -nm						-	Disable texture management and use texture handles instead.
 **** -ftm						-	Force the use of texture management.
 **** -fvf						-	Force the use of vertex fogging.
 **** -best						-	Choose the best device/driver instead of opening dialog box.
 **** -window					-	If used with the above, pick a windowed mode.
 **** -langdump					-	Write a list of tags that are not specified in the language file to "<file>.untranslated"
 **** -langsuffix [suffix]		-	Write out a language parsed file to "<file>.<suffix>"
 **** -langfile [file]			-	Specify which language convertion file to use.
 **** -CharTable [file]			-	Character conversion file (cct) to use.
 **** -charconvertfile [file]	-	Character convert this file then exit.
 **** -startlevel [level]		-	The starting level for the game.
 **** -cleansaves				-	Wipes the save files.  Will be needed when the save file changes version.
 **** -fpslock [fps]			-	Lock the update to a given framerate.
 ****
 *************************************************************************************************************************/

VOID Test(VOID) {

//		[  1  0  0  ]		[  c1 0 s1 ]		[ c2 -s2 0 ]
//	mX=	[  0 c0 -s0 ]	mY=	[  0  1 0  ]	mZ=	[ s2  c2 0 ]
//		[  0 s0 c0  ]		[ -s1 0 c1 ]		[ 0   0  1 ]

	Util_StringMatrix pivot = 
	{
		{ "1.0f", NULL, NULL, NULL },
		{ NULL, "1.0f", NULL, NULL },
		{ NULL, NULL, "1.0f", NULL },
		{ "pVx", "pVy", "pVz", "1.0f" }
	};
	Util_StringMatrix scale =
	{
		{ "scale->x", NULL, NULL, NULL },
		{ NULL, "scale->y", NULL, NULL },
		{ NULL, NULL, "scale->z", NULL },
		{ NULL, NULL, NULL, "1.0f" }
	};
	Util_StringMatrix rotx = 
	{
		{ "1.0f", NULL, NULL, NULL },
		{ NULL, " Cx", "-Sx", NULL },
		{ NULL, " Sx", " Cx", NULL },
		{ NULL, NULL, NULL, "1.0f" }
	};
	Util_StringMatrix roty = 
	{
		{ " Cy", NULL, " Sy", NULL },
		{ NULL, "1.0f", NULL, NULL },
		{ "-Sy", NULL, " Cy", NULL },
		{ NULL, NULL, NULL, "1.0f" }
	};
	Util_StringMatrix rotz = 
	{
		{ " Cz", "-Sz", NULL, NULL },
		{ " Sz", " Cz", NULL, NULL },
		{ NULL, NULL, "1.0f", NULL },
		{ NULL, NULL, NULL, "1.0f" }
	};
	Util_StringMatrix trans = 
	{
		{ "1.0f", NULL, NULL, NULL },
		{ NULL, "1.0f", NULL, NULL },
		{ NULL, NULL, "1.0f", NULL },
		{ "pos->x", "pos->y", "pos->z", "1.0f" }
	};

	Util_StringMatrix r1 = { NULL };
	Util_StringMatrix r2 = { NULL };
	Util_StringMatrix r3 = { NULL };
	Util_StringMatrix r4 = { NULL };
	Util_StringMatrix r5 = { NULL };

	Util_TransposeStringMatrix(pivot);
	Util_TransposeStringMatrix(scale);
	Util_TransposeStringMatrix(rotx);
	Util_TransposeStringMatrix(roty);
	Util_TransposeStringMatrix(rotz);
	Util_TransposeStringMatrix(trans);

	Util_MultiplyStringMatrix(r1, pivot, scale);
	Util_MultiplyStringMatrix(r2, r1, rotz);
	Util_MultiplyStringMatrix(r3, r2, rotx);
	Util_MultiplyStringMatrix(r4, r3, roty);
	Util_MultiplyStringMatrix(r5, r4, trans);

	Util_PrintStringMatrix(r5);

	Util_FreeStringMatrix(r1);
	Util_FreeStringMatrix(r2);
	Util_FreeStringMatrix(r3);
	Util_FreeStringMatrix(r4);
	Util_FreeStringMatrix(r5);
	Util_FreeStringMatrix(pivot);
	Util_FreeStringMatrix(scale);
	Util_FreeStringMatrix(rotx);
	Util_FreeStringMatrix(roty);
	Util_FreeStringMatrix(rotz);
	Util_FreeStringMatrix(trans);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int cmdShow){

	BOOL setup = FALSE, nosound = FALSE, insistOnCD = FALSE;
	LPUCHAR cl, s;
	LPUCHAR productName = NULL;
	LPUCHAR productRegistry = NULL;
	UCHAR mutexName[128];
	UCHAR noHALMsg[1024];

	CoInitialize(NULL);

//	Test();
//	{
//		extern VOID __cdecl Init_Init(LPUCHAR cmdLine);
//		Init_Init(lpszCmdLine);
//	}

	for (s=cl=GetCommandLine() ; '\0'!=*cl ; cl++) if ('\\' == *cl) s = cl+1;		// Find the last backslash.
	strcpy(mainGlobs.programName, s);
	for (s=mainGlobs.programName ; '\0'!=*s ; s++) if ('"' == *s) *s = '\0';		// Terminate at any '"'.
	for (s=cl=mainGlobs.programName ; '\0'!=*cl ; cl++) if ('.' == *cl) s = cl+1;	// Find the last dot.

	if (s != mainGlobs.programName) {
		strupr(s);																	// Ensure .exe is in upper case.
		if (s = strstr(mainGlobs.programName, ".EXE")) *s = '\0';					// Strip off .EXE
	}

	productName = mainGlobs.programName;
	productRegistry = "SOFTWARE\\LEGO Media\\Games\\Rock Raiders";

	if (productName) {

		sprintf(mutexName, "%s Mutex", productName);
		CreateMutex(0, TRUE, mutexName);
		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			return 0;									// App is already running
		}
	}

	// Setup the default globals
	mainGlobs.className = mainGlobs.programName;
	mainGlobs.active = FALSE;
	mainGlobs.exit = FALSE;
	mainGlobs.stateSet = FALSE;
	mainGlobs.hInst = hInstance;
	mainGlobs.fixedFrameTiming = 0.0f;
	mainGlobs.flags = 0;

	{
		UCHAR commandLine[1024];
		UCHAR tempStr[1024];

		if (Registry_GetValue(productRegistry, "StandardParameters", REGISTRY_STRING_VALUE, tempStr, 1024)) {
			sprintf(commandLine, "%s %s", lpszCmdLine, tempStr);
		} else sprintf(commandLine, "%s", lpszCmdLine);

//		mainGlobs.flags |= MAIN_FLAG_BEST;
		mainGlobs.flags |= MAIN_FLAG_DUALMOUSE;
		Main_ParseCommandLine(commandLine, &nosound, &insistOnCD);
	}

	if (!Registry_GetValue(productRegistry, "NoHALMessage", REGISTRY_STRING_VALUE, noHALMsg, 1024)) {
		sprintf(noHALMsg, "No DirectX 3D accelerator could be found.");
	}

	// Initialise everything (memory, window, DirectDraw, etc.)
	Error_Initialise();
	Mem_Initialise();
	File_Initialise(mainGlobs.programName, insistOnCD, productRegistry);
	Config_Initialise();
	Font_Initialise();

	
	//	if (Util_StrIStr(lpszCmdLine, "-setup")) setup = TRUE;
#pragma message ("Defaulting to setup mode")
	setup = TRUE;

	if (Main_InitApp(hInstance)) {
		DirectDraw_Initialise(mainGlobs.hWnd);
		if (Sound_Initialise(nosound) && Init_Initialise(setup, mainGlobs.flags & MAIN_FLAG_DEBUGMODE, mainGlobs.flags & MAIN_FLAG_BEST, mainGlobs.flags & MAIN_FLAG_WINDOW, noHALMsg)){

			Animation_Initialise(DirectDraw());
			Draw_Initialise(NULL);
			Image_Initialise();
			Input_InitKeysAndDI();

			// Call the Gods_Go() funtion in the application
			Gods_Go(mainGlobs.programName);

			// If the game wants to run in state mode...
			if (mainGlobs.stateSet){

				// Run their initialisation code (if required)...
				if (NULL != mainGlobs.currState.Initialise) {
					if (!mainGlobs.currState.Initialise()){

						// Initialisation failed so drop out...
						Error_Warn(TRUE, "Initialisation function failed...");
						mainGlobs.currState.Initialise = NULL;
						mainGlobs.currState.MainLoop = NULL;
						mainGlobs.currState.Shutdown = NULL;

					}
				}

#ifdef _DEBUG
			{
				lpFile logFile = File_Open("notthere.dat", "rb");		// Log a failed file open in FileMon
			}
#endif // _DEBUG


				// If? a main loop is specified then run it until it returns false...
				if (mainGlobs.currState.MainLoop){
					
					// Use the MultiMedia timer to give a 'realtime passed' value
					// per frame to the main loop (in 25th's of a second)
					REAL time = 1.0f;
					ULONG lastTime, currTime;

					lastTime = timeGetTime();

					while(!mainGlobs.exit){
						
						// Handle windows messages and input...
						INPUT.lClicked = FALSE;
						INPUT.rClicked = FALSE;
						INPUT.lDoubleClicked = FALSE;
						INPUT.rDoubleClicked = FALSE;

						Main_HandleIO();
						// In fullscreen mode we will always be the active application or I will eat my hat.
						if (mainGlobs.flags & MAIN_FLAG_FULLSCREEN) mainGlobs.active = TRUE;
						Input_ReadKeys();
						Input_ReadMouse2();

						// Run the main loop (pass 1.0f as the initial timing value)
						if (!mainGlobs.currState.MainLoop(time)) mainGlobs.exit = TRUE;

						// Update the device and flip the surfaces...
						Main_Finalise3D();
						DirectDraw_Flip();
						mainGlobs.flags &= ~MAIN_FLAG_UPDATED;

						if (mainGlobs.flags & MAIN_FLAG_DUMPMODE) {

							time = STANDARD_FRAMERATE / 30.0f;

						} else if (mainGlobs.flags & MAIN_FLAG_PAUSED) {
							time = 0.0f;
							lastTime = timeGetTime();
						} else if (0.0f == mainGlobs.fixedFrameTiming) {
							// Measure the time taken over the last frame (to be passed next loop)
							currTime = timeGetTime();
							time = ((REAL)(currTime - lastTime)) / (1000.0f / STANDARD_FRAMERATE);
							lastTime = currTime;
#ifndef _UNLIMITEDUPDATETIME
							if (time > 3.0f) {
								time = 3.0f;
							}
#endif // _UNLIMITEDUPDATETIME

						} else {
							time = mainGlobs.fixedFrameTiming;
							lastTime = timeGetTime();
						}
					}
				}

#ifdef _DEBUG
			{
				lpFile logFile = File_Open("notthere.dat", "rb");
			}
#endif // _DEBUG

			/*
#ifdef CONFIG_DEVELOPMENTMODE
			{
				LPUCHAR loc;
				if (loc = Util_StrIStr(lpszCmdLine, "-languagedump")) {
					LPUCHAR s;
					ULONG index = 0;
					UCHAR file[FILE_MAXPATH];
					for (s=&loc[strlen("-languagedump")] ; '\0'!=*s ; s++) if (' ' != *s) break;
					for ( ; '\0' != *s ; s++) {
						if (' ' == *s) break;
						else file[index++] = *s;
					}
					file[index] = '\0';
					Config_DumpUnknownPhrases(file);
				}
			}
#endif // CONFIG_DEVELOPMENTMODE
			*/

				// Shutdown if required...
				if (NULL != mainGlobs.currState.Shutdown) mainGlobs.currState.Shutdown();
				
			} else Error_Warn(TRUE, "No State Set: Exiting...");
		} else Error_Warn(TRUE, "Initialisation Failed: Exiting...");
		DirectDraw_Shutdown();
		DestroyWindow(mainGlobs.hWnd);
	} else Error_Warn(TRUE, "Unable to initialise window");

	Input_ReleaseKeysAndDI();
	Config_Shutdown();

#ifdef _GODS98_USEWAD_
//	if (mainGlobs.wad != WAD_ERROR) File_CloseWad(mainGlobs.wad);
#endif // _GODS98_USEWAD_

	// The very last things...
	Mem_Shutdown(FALSE);

	Error_CloseLog();

	Error_Shutdown();

	CoUninitialize();

	return 0;
}

VOID Main_Exit(VOID) {

	CoUninitialize();
	exit(0);

}

/*
#ifdef _TESTCODE
VOID Main_ResetClockRatio(VOID) {

	Main_StartTime = timeGetTime();
	Main_StartClock = clock();
}

REAL Main_GetClockRatio(VOID) {
	
	return (REAL) (clock() - Main_StartClock) / (timeGetTime() - Main_StartTime);
}
#endif // _TESTCODE
*/

VOID Main_DisableTextureManagement(VOID) {

	if (!(mainGlobs.flags & MAIN_FLAG_FORCETEXTUREMANAGEMENT)) {
		mainGlobs.flags |= MAIN_FLAG_DONTMANAGETEXTURES;
	}
}

static VOID Main_ParseCommandLine(LPUCHAR lpszCmdLine, LPBOOL nosound, LPBOOL insistOnCD) {

	LPUCHAR loc;
	UCHAR langDir[128];

	if (Util_StrIStr(lpszCmdLine, "-insistOnCD")) *insistOnCD = TRUE;
	if (Util_StrIStr(lpszCmdLine, "-nosound")) *nosound = TRUE;
	if (Util_StrIStr(lpszCmdLine, "-debug")) mainGlobs.flags |= MAIN_FLAG_DEBUGMODE;
	if (Util_StrIStr(lpszCmdLine, "-nm")) mainGlobs.flags |= MAIN_FLAG_DONTMANAGETEXTURES;
	if (Util_StrIStr(lpszCmdLine, "-ftm")) mainGlobs.flags |= MAIN_FLAG_FORCETEXTUREMANAGEMENT;
	if (Util_StrIStr(lpszCmdLine, "-fvf")) mainGlobs.flags |= MAIN_FLAG_FORCEVERTEXFOG;
	if (Util_StrIStr(lpszCmdLine, "-best")) mainGlobs.flags |= MAIN_FLAG_BEST;
	if (Util_StrIStr(lpszCmdLine, "-window")) mainGlobs.flags |= MAIN_FLAG_WINDOW;
	if (Util_StrIStr(lpszCmdLine, "-nodualmouse")) mainGlobs.flags &= ~MAIN_FLAG_DUALMOUSE;
	if (Util_StrIStr(lpszCmdLine, "-debugcomplete")) mainGlobs.flags |= MAIN_FLAG_DEBUGCOMPLETE;
	if (Util_StrIStr(lpszCmdLine, "-testercall")) { mainGlobs.flags |= MAIN_FLAG_TESTERCALL; mainGlobs.programmerLevel=2; }
	if (Util_StrIStr(lpszCmdLine, "-testlevels")) mainGlobs.flags |= MAIN_FLAG_LEVELSOPEN;
	if (Util_StrIStr(lpszCmdLine, "-reducesamples")) mainGlobs.flags |= MAIN_FLAG_REDUCESAMPLES;
	if (Util_StrIStr(lpszCmdLine, "-showversion")) mainGlobs.flags |= MAIN_FLAG_SHOWVERSION;
	if (Util_StrIStr(lpszCmdLine, "-reduceanimation")) mainGlobs.flags |= MAIN_FLAG_REDUCEANIMATION;
	if (Util_StrIStr(lpszCmdLine, "-reducepromeshes")) mainGlobs.flags |= MAIN_FLAG_REDUCEPROMESHES;
	if (Util_StrIStr(lpszCmdLine, "-reduceflics")) mainGlobs.flags |= MAIN_FLAG_REDUCEFLICS;
	if (Util_StrIStr(lpszCmdLine, "-reduceimages")) mainGlobs.flags |= MAIN_FLAG_REDUCEIMAGES;
#ifdef CONFIG_DEVELOPMENTMODE
	if (Util_StrIStr(lpszCmdLine, "-langdump")) mainGlobs.flags |= MAIN_FLAG_LANGDUMPUNKNOWN;
	if (loc = Util_StrIStr(lpszCmdLine, "-langsuffix")) {
		LPUCHAR s;
		ULONG index = 0;
		for (s=&loc[strlen("-langsuffix")] ; '\0'!=*s ; s++) if (' ' != *s) break;
		for ( ; '\0' != *s ; s++) {
			if (' ' == *s) break;
			else mainGlobs.languageName[index++] = *s;
		}
		mainGlobs.languageName[index] = '\0';
		mainGlobs.flags |= MAIN_FLAG_SAVELANGFILE;
	}
	// *** Tony wos here

	fileGlobs.langCheck = FALSE;
	ZeroMemory(fileGlobs.langDir,_MAX_PATH);

#define NUM_LANG 8

	{
		LPUCHAR langTable[NUM_LANG]={"040c-french","0007-german","000a-spanish",
			"0010-italian","0013-dutch","0006-danish","001d-swedish","0014-norwegian"};

		UCHAR langLine[30];
		LPUCHAR lp, lp2;
		ULONG i;

		for(i=0;i<NUM_LANG;i++)
		{
			lp2=langTable[i];
			lp2+=5;
			sprintf(langLine,"-%s",lp2);
			if (loc = Util_StrIStr(lpszCmdLine, langLine)) {
				lp=lp2;
				sprintf(fileGlobs.langDir,"languages\\%s",langTable[i]);
				sprintf(langDir,"@languages\\%s\\%s",langTable[i],lp);
				fileGlobs.langCheck = TRUE;
			}
		}
	}
	if(fileGlobs.langCheck) {
		UCHAR temp[128];
		sprintf(temp,"%s.new.lang",langDir);
		Config_SetLanguageDatabase(temp);
		sprintf(temp,"%s.cct",langDir);
		Config_SetCharacterTable(temp);
	}

	//
	if (loc = Util_StrIStr(lpszCmdLine, "-langfile")) {
		LPUCHAR s;
		ULONG index = 0;
		UCHAR file[FILE_MAXPATH];
		for (s=&loc[strlen("-langfile")] ; '\0'!=*s ; s++) if (' ' != *s) break;
		for ( ; '\0' != *s ; s++) {
			if (' ' == *s) break;
			else file[index++] = *s;
		}
		file[index] = '\0';
		Config_SetLanguageDatabase(file);
	}
	if (loc = Util_StrIStr(lpszCmdLine, "-CharTable")) {
		LPUCHAR s;
		ULONG index = 0;
		UCHAR file[FILE_MAXPATH];
		for (s=&loc[strlen("-CharTable")] ; '\0'!=*s ; s++) if (' ' != *s) break;
		for ( ; '\0' != *s ; s++) {
			if (' ' == *s) break;
			else file[index++] = *s;
		}
		file[index] = '\0';
		Config_SetCharacterTable(file);
	}
	if (loc = Util_StrIStr(lpszCmdLine, "-charconvertfile")) {
		LPUCHAR s;
		ULONG index = 0;
		UCHAR file[FILE_MAXPATH];
		for (s=&loc[strlen("-charconvertfile")] ; '\0'!=*s ; s++) if (' ' != *s) break;
		for ( ; '\0' != *s ; s++) {
			if (' ' == *s) break;
			else file[index++] = *s;
		}
		file[index] = '\0';
		Config_SetCharacterConvertFile(file);
	}
#endif // CONFIG_DEVELOPMENTMODE
	if (loc = Util_StrIStr(lpszCmdLine, "-startlevel")) {
		LPUCHAR s;
		ULONG index = 0;
		for (s=&loc[strlen("-startlevel")] ; '\0'!=*s ; s++) if (' ' != *s) break;
		for ( ; '\0' != *s ; s++) {
			if (' ' == *s) break;
			else mainGlobs.startLevel[index++] = *s;
		}
		mainGlobs.startLevel[index] = '\0';
		mainGlobs.flags |= MAIN_FLAG_STARTLEVEL;
	}
	if (loc = Util_StrIStr(lpszCmdLine, "-flags")) mainGlobs.clFlags = atoi(&loc[strlen("-flags")]);
	if (loc = Util_StrIStr(lpszCmdLine, "-fpslock")) {
		ULONG fps = atoi(&loc[strlen("-fpslock")]);
		if (fps) mainGlobs.fixedFrameTiming = STANDARD_FRAMERATE / (REAL) fps;
	}
	if (loc = Util_StrIStr(lpszCmdLine, "-programmer")) {
		mainGlobs.programmerLevel = atoi(&loc[strlen("-programmer")]);
		if (0 == mainGlobs.programmerLevel) mainGlobs.programmerLevel = 1;
	} else mainGlobs.programmerLevel = 0;
	// Set this to cause reinitialisation of the save games.
	if (Util_StrIStr(lpszCmdLine, "-cleansaves")) mainGlobs.flags |= MAIN_FLAG_CLEANSAVES;
}

LPUCHAR Main_GetLanguage(VOID) {

	if (mainGlobs.flags & MAIN_FLAG_SAVELANGFILE) return mainGlobs.languageName;
	return NULL;
}

BOOL Main_DumpUnknownPhrases(VOID) {

	return mainGlobs.flags & MAIN_FLAG_LANGDUMPUNKNOWN;
}

VOID Main_LoopUpdate(BOOL clear){

	Main_HandleIO();
	Input_ReadKeys();
	Input_ReadMouse2();

	// Update the device and flip the surfaces...
	Main_Finalise3D();
	DirectDraw_Flip();

	if (clear) DirectDraw_Clear(NULL, 0);
	mainGlobs.flags &= ~MAIN_FLAG_UPDATED;
}

ULONG Main_GetCLFlags(VOID) {
	
	return mainGlobs.clFlags;
}

ULONG Main_GetWindowsBitDepth(VOID){

	return GetDeviceCaps(GetDC(Main_hWnd()), BITSPIXEL);
}

VOID Main_Finalise3D(VOID){

	if (!(mainGlobs.flags & MAIN_FLAG_UPDATED)) {
		mainGlobs.device->lpVtbl->Update(mainGlobs.device);
		mainGlobs.flags |= MAIN_FLAG_UPDATED;
	}
}

BOOL Main_SetState(Main_State *state){
	
	if (NULL != state){
		mainGlobs.currState = *state;
		mainGlobs.stateSet = TRUE;
		return TRUE;
	}
	return FALSE;
}

ULONG Main_GetTime(VOID) {

	return timeGetTime();
}

VOID Main_SetFixedFrameTiming(REAL time){

	mainGlobs.fixedFrameTiming = time;
}

BOOL Main_DispatchMessage(MSG *msg)
{
	if ((mainGlobs.flags & MAIN_FLAG_FULLSCREEN) && 
		(msg->message == WM_ACTIVATEAPP || msg->message == WM_SYSKEYDOWN || msg->message == WM_SYSKEYUP)) return FALSE;
	else return TRUE;
}

VOID Main_HandleIO(VOID){

	MSG msg;
	
	// Look at windows messages (if there are any)

	if (mainGlobs.accels != NULL)
	{
		while (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (!TranslateAccelerator (Main_hWnd(), mainGlobs.accels, &msg))
			{
				TranslateMessage (&msg);
				DispatchMessage (&msg);
			}
		}
	}
	else
	{
		while (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (Main_DispatchMessage(&msg))
			{
				TranslateMessage (&msg);
				DispatchMessage (&msg);
			}
		}
	}
}

VOID Main_SetupDisplay(BOOL fullScreen, ULONG xPos, ULONG yPos, ULONG width, ULONG height){
		
	mainGlobs.appWidth = width;
	mainGlobs.appHeight = height;
	if (fullScreen) mainGlobs.flags |= MAIN_FLAG_FULLSCREEN;

	Error_FullScreen(fullScreen);

	if (!fullScreen) {
		
		// Adjust the window to any new settings...
		
		RECT rect;
		mainGlobs.style = WS_POPUP | WS_SYSMENU | WS_CAPTION;
		
		rect.left = xPos;
		rect.top = yPos;
		rect.right = xPos + width;
		rect.bottom = yPos + height;
		
		Main_AdjustWindowRect(&rect);
		
		SetWindowLong(mainGlobs.hWnd, GWL_STYLE, mainGlobs.style);
		SetWindowPos(mainGlobs.hWnd, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);

		ShowCursor(FALSE);

	} else {

		RECT rect;
		HWND hWndDesktop = GetDesktopWindow();

		GetWindowRect(hWndDesktop, &rect);
		SetWindowPos(mainGlobs.hWnd, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);

		SetCursor(FALSE);
	}

	ShowWindow(mainGlobs.hWnd, SW_SHOW);
	SetActiveWindow(mainGlobs.hWnd);
}

BOOL Main_SetupDirect3D(lpDirectDraw_Device dev, LPDIRECTDRAW ddraw1, LPDIRECTDRAWSURFACE4 backSurf, BOOL doubleBuffered){

	LPGUID guid = NULL;
	LPDIRECT3DRM lpD3DRM1;
//	LPDIRECT3D3 d3d3;
//	LPDIRECT3DDEVICE3 d3ddev3;
	HRESULT r;
	LPDIRECTDRAWSURFACE surf1;
	
	if (dev) {
		guid = &dev->guid;
		if (dev->flags & DIRECTDRAW_FLAG_DEVICE_VIDEOTEXTURE) mainGlobs.flags |= MAIN_FLAG_VIDEOTEXTURE;
	}

#pragma message ( "CAPS testing is a complete waste of time for this" )
	if (!(mainGlobs.flags & MAIN_FLAG_FORCEVERTEXFOG) && (dev->flags & DIRECTDRAW_FLAG_DEVICE_HARDWARE)) Main_SetFogMethod(D3DRMFOGMETHOD_TABLE);
	else Main_SetFogMethod(D3DRMFOGMETHOD_VERTEX);

	// Create D3DRM and the device...
	
	if (Direct3DRMCreate(&lpD3DRM1) == D3DRM_OK){
		if (lpD3DRM1->lpVtbl->QueryInterface(lpD3DRM1, &IID_IDirect3DRM3, &mainGlobs.lpD3DRM) == D3DRM_OK){
			backSurf->lpVtbl->QueryInterface(backSurf, &IID_IDirectDrawSurface, &surf1);
			if ((r = mainGlobs.lpD3DRM->lpVtbl->CreateDeviceFromSurface(mainGlobs.lpD3DRM, guid, ddraw1, surf1, 0, &mainGlobs.device)) == D3DRM_OK){

				LPDIRECT3DDEVICE2 imdev2;

				mainGlobs.device->lpVtbl->GetDirect3DDevice2(mainGlobs.device, &imdev2 );
				imdev2->lpVtbl->QueryInterface( imdev2, &IID_IDirect3DDevice3, &mainGlobs.imDevice );
				imdev2->lpVtbl->Release(imdev2);


//			if ((r = mainGlobs.lpD3DRM->lpVtbl->CreateDeviceFromSurface(mainGlobs.lpD3DRM, NULL, ddraw1, surf1, 0, &mainGlobs.device)) == D3DRM_OK){
//			if (D3DRM_OK == ddraw1->lpVtbl->QueryInterface(ddraw1, &IID_IDirect3D3, &d3d3)){
//				r = 1;
//				if (0 == memcmp(guid, &IID_IDirect3DRGBDevice, sizeof(GUID))){
//					r = d3d3->lpVtbl->CreateDevice(d3d3, &IID_IDirect3DMMXDevice, backSurf, &d3ddev3, NULL);
//				}
//				if (r != D3DRM_OK) {
//					r = d3d3->lpVtbl->CreateDevice(d3d3, guid, backSurf, &d3ddev3, NULL);
//				}

//				if (D3DRM_OK == r){

//					LPDIRECT3D2 d3d2;
//					LPDIRECT3DDEVICE2 d3ddev2;
//					d3d3->lpVtbl->QueryInterface(d3d3, &IID_IDirect3D2, &d3d2);
//					d3ddev3->lpVtbl->QueryInterface(d3ddev3, &IID_IDirect3DDevice2, &d3ddev2);
//					mainGlobs.lpD3DRM->lpVtbl->CreateDeviceFromD3D(mainGlobs.lpD3DRM, d3d2, d3ddev2, &mainGlobs.device);
//					d3ddev3->lpVtbl->Release(d3ddev3);
//					d3ddev2->lpVtbl->Release(d3ddev2);
//					d3d2->lpVtbl->Release(d3d2);

//					d3d3->lpVtbl->Release(d3d3);

					if (doubleBuffered) mainGlobs.device->lpVtbl->SetBufferCount(mainGlobs.device, 2);
					return TRUE;
					
			} else {
				CHKDD(r);
				Error_Warn(TRUE, "Unable to create Device");
			}
//				d3d3->lpVtbl->Release(d3d3);
//			} else Error_Warn(TRUE, "Unable to obtain Direct3D3");
		} else Error_Warn(TRUE, "Failed query for IID_IDirect3DRM3");
	} else Error_Warn(TRUE, "Unable to create lpD3DRM1");

	CHKRM(r);

	return FALSE;
}

VOID Main_AdjustWindowRect(LPRECT rect){

	if (!(mainGlobs.flags & MAIN_FLAG_FULLSCREEN)) AdjustWindowRect(rect, mainGlobs.style, FALSE);
}

VOID Main_Setup3D(ULONG renderQuality, BOOL dither, BOOL linearFilter, BOOL mipMap, BOOL mipMapLinear, BOOL blendTransparency, BOOL sortTransparency){

	ULONG quality = D3DRMRENDER_WIREFRAME, renderMode = 0, textureMode;

	if (WIREFRAME == renderQuality) quality = D3DRMRENDER_WIREFRAME;
	if (FLATSHADE == renderQuality) quality = D3DRMRENDER_FLAT;
	if (UNLITFLATSHADE == renderQuality) quality = D3DRMRENDER_UNLITFLAT;
	if (GOURAUDSHADE == renderQuality) quality = D3DRMRENDER_GOURAUD;

	if (blendTransparency) renderMode |= D3DRMRENDERMODE_BLENDEDTRANSPARENCY;
	if (sortTransparency) renderMode |= D3DRMRENDERMODE_SORTEDTRANSPARENCY;

	if (linearFilter) {
		if (mipMap) {
			if (mipMapLinear) textureMode = D3DRMTEXTURE_LINEARMIPLINEAR;
			else textureMode = D3DRMTEXTURE_MIPLINEAR;
			mainGlobs.flags |= MAIN_FLAG_MIPMAPENABLED;
		} else textureMode = D3DRMTEXTURE_LINEAR;
	} else textureMode = D3DRMTEXTURE_NEAREST;

	if (mainGlobs.device){

		// Should check device caps here...

		mainGlobs.device->lpVtbl->SetDither(mainGlobs.device, dither);
		mainGlobs.device->lpVtbl->SetQuality(mainGlobs.device, quality);
		mainGlobs.device->lpVtbl->SetTextureQuality(mainGlobs.device, textureMode);
//		mainGlobs.device->lpVtbl->SetRenderMode(mainGlobs.device, D3DRMRENDERMODE_BLENDEDTRANSPARENCY|D3DRMRENDERMODE_SORTEDTRANSPARENCY |D3DRMRENDERMODE_DISABLESORTEDALPHAZWRITE);
//		mainGlobs.device->lpVtbl->SetRenderMode(mainGlobs.device, renderMode);

	} else Error_Fatal(TRUE, "Device not initialised");
}

VOID Main_SetTitle(LPUCHAR title){
	
	SetWindowText(mainGlobs.hWnd, title);
}

ULONG Main_GetTrianglesDrawn(BOOL total){

	static ULONG last = 0;
	ULONG curr, count;

	curr = mainGlobs.device->lpVtbl->GetTrianglesDrawn(mainGlobs.device);
	if (!total) count = curr - last;
	else count = curr;

	last = curr;
	return count;
}

static BOOL Main_InitApp(HINSTANCE hInstance){
	
	WNDCLASS wc;
	//	DWORD WIN_STYLE;
	
	// Register the window style
	wc.style = CS_DBLCLKS;
	wc.lpfnWndProc = Main_WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
//	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
//	wc.hbrBackground = GetStockObject(BLACK_BRUSH);
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName =  NULL;
	wc.lpszClassName = mainGlobs.className;
	
	// Check to ensure the class was actually registered
	if (RegisterClass(&wc)) {
		
		// Create the main window
		
		if (mainGlobs.hWnd = CreateWindowEx(WS_EX_APPWINDOW, mainGlobs.className, "",
			WS_POPUP | WS_SYSMENU,
			0, 0, 100, 100,
			NULL, NULL, hInstance, NULL)){
			
			SetFocus(mainGlobs.hWnd);
			
			return TRUE;
			
		} else MessageBox(NULL, "Unable to Create Main Window", "Fatal Error", MB_OK);
	} else MessageBox(NULL, "Unable to register window class", "Fatal Error", MB_OK);
	
	return FALSE;
}

LRESULT Main_WndProc_Fullscreen(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	INPUT.lClicked = FALSE;
	INPUT.rClicked = FALSE;

	if (mainGlobs.windowCallback != NULL) mainGlobs.windowCallback(hWnd, message, wParam, lParam);

	switch (message)  
	{

	// Key board messages
	case WM_KEYDOWN:
	case WM_KEYUP:
		return 0;

	// Mouse
	case WM_MOUSEMOVE:
		return 0;

	// Handle single or dual mouse
	case WM_LBUTTONDOWN:		
	case WM_LBUTTONUP:			
	case WM_RBUTTONDOWN:		
	case WM_RBUTTONUP:
		{
			if (mainGlobs.flags & MAIN_FLAG_DUALMOUSE)
			{
				// Both buttons valid
				switch (message)
				{
				case WM_LBUTTONDOWN:		
					INPUT.mslb		= TRUE;
					INPUT.lClicked	= FALSE;		
					return 0;

				case WM_LBUTTONUP:			
					INPUT.mslb		= FALSE;
					INPUT.lClicked	= TRUE;	
					return 0;

				case WM_RBUTTONDOWN:		
					INPUT.msrb		= TRUE;
					INPUT.rClicked	= FALSE;
					return 0;

				case WM_RBUTTONUP:			
					INPUT.msrb		= FALSE;
					INPUT.rClicked	= TRUE;	
					return 0;
				}
			}
			else
			{
				// Merged buttons
				switch (message)
				{
				case WM_LBUTTONDOWN:
				case WM_RBUTTONDOWN:
					if (!INPUT.mslb) {
						INPUT.lClicked = FALSE;
						INPUT.rClicked = FALSE;
					}
					INPUT.mslb = INPUT.msrb = TRUE;
					break;
				case WM_LBUTTONUP:
				case WM_RBUTTONUP:
					INPUT.lClicked = TRUE;
					INPUT.rClicked = TRUE;
					INPUT.mslb = INPUT.msrb = FALSE;
					break;
				}
			}
		}

/*#ifdef MAIN_MERGEMOUSEBUTTONS

	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		if (!INPUT.mslb) {
			INPUT.lClicked = TRUE;
			INPUT.rClicked = TRUE;
		}
		INPUT.mslb = INPUT.msrb = TRUE;
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		INPUT.lClicked = FALSE;
		INPUT.rClicked = FALSE;
		INPUT.mslb = INPUT.msrb = FALSE;
		break;
#else

	case WM_LBUTTONDOWN:		
		INPUT.mslb = INPUT.lClicked = TRUE;		
		return 0;
	case WM_LBUTTONUP:			
		INPUT.mslb = INPUT.lClicked = FALSE;	
		return 0;
	case WM_RBUTTONDOWN:		
		INPUT.msrb = INPUT.rClicked = TRUE;		
		return 0;
	case WM_RBUTTONUP:			
		INPUT.msrb = INPUT.rClicked = FALSE;	
		return 0;
#endif*/

	case WM_LBUTTONDBLCLK:		
		INPUT.lDoubleClicked = TRUE;			
		return 0;
	case WM_RBUTTONDBLCLK:		
		INPUT.rDoubleClicked = TRUE;			
		return 0;

	// Exit messages
	case WM_CLOSE:
	case WM_QUIT:
	case WM_DESTROY:
		mainGlobs.exit = TRUE;
		break;

	// Window messages
	case WM_SIZE:
	case WM_MOVE:
		return 0;

	case WM_ACTIVATE:
		return 0;

	case WM_ACTIVATEAPP:
		mainGlobs.active = (BOOL) wParam;
		return 0;

	case WM_PAINT:
	case WM_CREATE:
	case WM_COMMAND:
		break;

	case WM_WINDOWPOSCHANGING:
		{
			WINDOWPOS *pos = (WINDOWPOS *) lParam;
			pos->flags &= ~(SWP_NOOWNERZORDER);
			return 0;
		}

	case WM_ENTERMENULOOP:
		return 0;

    case WM_EXITMENULOOP:
		return 0;

	case WM_NCACTIVATE:
		return 0;

	case WM_SYSKEYDOWN:
		return 0;

	default:
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT Main_WndProc_Windowed(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (mainGlobs.windowCallback != NULL) mainGlobs.windowCallback(hWnd, message, wParam, lParam);

	switch (message)  {
		
		// Exit messages
	case WM_CLOSE:
		mainGlobs.exit = TRUE;
		break;
	case WM_QUIT:
		mainGlobs.exit = TRUE;
		break;
	case WM_DESTROY:
		mainGlobs.exit = TRUE;
		break;

	// Handle single or dual mouse
	case WM_LBUTTONDOWN:		
	case WM_LBUTTONUP:			
	case WM_RBUTTONDOWN:		
	case WM_RBUTTONUP:
		{
			if (mainGlobs.flags & MAIN_FLAG_DUALMOUSE)
			{
				/*
				// Both buttons valid
				switch (message)
				{
				case WM_LBUTTONDOWN:
					SetCapture(hWnd);
					INPUT.mslb = INPUT.lClicked = TRUE;
					break;
				case WM_LBUTTONUP:
					ReleaseCapture();
					INPUT.mslb = INPUT.lClicked = FALSE;
					break;
				case WM_RBUTTONDOWN:		INPUT.msrb = INPUT.rClicked = TRUE;		break;
				case WM_RBUTTONUP:			INPUT.msrb = INPUT.rClicked = FALSE;	break;
				}
				 */

				switch (message)
				{
				case WM_LBUTTONDOWN:		
					SetCapture(hWnd);
					INPUT.mslb		= TRUE;
					INPUT.lClicked	= FALSE;		
					return 0;

				case WM_LBUTTONUP:			
					ReleaseCapture();
					INPUT.mslb		= FALSE;
					INPUT.lClicked	= TRUE;	
					return 0;

				case WM_RBUTTONDOWN:		
					SetCapture(hWnd);
					INPUT.msrb		= TRUE;
					INPUT.rClicked	= FALSE;
					return 0;

				case WM_RBUTTONUP:			
					ReleaseCapture();
					INPUT.msrb		= FALSE;
					INPUT.rClicked	= TRUE;	
					return 0;
				}

			}
			else
			{
				// Merged buttons
				switch (message)
				{
				case WM_LBUTTONDOWN:
				case WM_RBUTTONDOWN:
					SetCapture(hWnd);
					if (!INPUT.mslb) {
						INPUT.lClicked = FALSE;
						INPUT.rClicked = FALSE;
					}
					INPUT.mslb = INPUT.msrb = TRUE;
					break;
				case WM_LBUTTONUP:
				case WM_RBUTTONUP:
					ReleaseCapture();
					INPUT.lClicked = TRUE;
					INPUT.rClicked = TRUE;
					INPUT.mslb = INPUT.msrb = FALSE;
					break;
				}
			}
		}

/*#ifdef MAIN_MERGEMOUSEBUTTONS

	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		SetCapture(hWnd);
		if (!INPUT.mslb) {
			INPUT.lClicked = TRUE;
			INPUT.rClicked = TRUE;
		}
		INPUT.mslb = INPUT.msrb = TRUE;
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		ReleaseCapture();
		INPUT.lClicked = FALSE;
		INPUT.rClicked = FALSE;
		INPUT.mslb = INPUT.msrb = FALSE;
		break;
#else


	case WM_LBUTTONDOWN:
		SetCapture(hWnd);
		INPUT.mslb = INPUT.lClicked = TRUE;
		break;
	case WM_LBUTTONUP:
		ReleaseCapture();
		INPUT.mslb = INPUT.lClicked = FALSE;
		break;
	case WM_RBUTTONDOWN:		INPUT.msrb = INPUT.rClicked = TRUE;		break;
	case WM_RBUTTONUP:			INPUT.msrb = INPUT.rClicked = FALSE;	break;

#endif*/
	
	case WM_LBUTTONDBLCLK:		INPUT.lDoubleClicked = TRUE;			break;
	case WM_RBUTTONDBLCLK:		INPUT.rDoubleClicked = TRUE;			break;

	case WM_ACTIVATEAPP:
		mainGlobs.active = (BOOL) wParam;
		return 0;

	case WM_ACTIVATE:
		break;

	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0L;
}

LRESULT CALLBACK Main_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (mainGlobs.flags & MAIN_FLAG_FULLSCREEN)
	{
		return Main_WndProc_Fullscreen(hWnd, message, wParam, lParam);
	}
	else
	{
		return Main_WndProc_Windowed(hWnd, message, wParam, lParam);
	}

}

VOID Main_ChangeRenderState(D3DRENDERSTATETYPE dwRenderStateType, DWORD dwRenderState){

	lpMain_StateChangeData data;
	DWORD currValue;
	HRESULT r;

	Error_Fatal(dwRenderStateType>=MAIN_MAXRENDERSTATES, "RenderState type is out of range");

	data = &mainGlobs.renderStateData[dwRenderStateType];
	r = mainGlobs.imDevice->lpVtbl->GetRenderState(mainGlobs.imDevice, dwRenderStateType, &currValue);
	Error_Fatal(D3D_OK!=r, Error_Format("Failed to GetRenderState(%i)", dwRenderStateType));

	if (currValue != dwRenderState){

//		if( D3D_OK ==
		mainGlobs.imDevice->lpVtbl->SetRenderState(mainGlobs.imDevice, dwRenderStateType, dwRenderState);
			// )
		{	
			if (data->changed) {
				if (data->origValue == currValue) data->changed = FALSE;
			} else {
				data->origValue = currValue;
				data->changed = TRUE;
			}

		}
			
	}
}

VOID Main_RestoreStates(BOOL force) {

	if (force) {

		ULONG loop;
		lpMain_StateChangeData data;

		for (loop=0 ; loop<MAIN_MAXRENDERSTATES ; loop++){
			data = &mainGlobs.renderStateData[loop];
			if (data->changed) {
				mainGlobs.imDevice->lpVtbl->SetRenderState(mainGlobs.imDevice, loop, data->origValue);
				data->changed = FALSE;
			}
		}
	}
}

VOID Main_PauseApp( BOOL pause )
{
	if( pause )
		mainGlobs.flags |= MAIN_FLAG_PAUSED;
	else
		mainGlobs.flags &= ~MAIN_FLAG_PAUSED;

}

BOOL Main_IsPaused( VOID )
{
	return (mainGlobs.flags & MAIN_FLAG_PAUSED);

}

/*
BOOL Main_SetCDVolume(REAL leftVolume, REAL rightVolume) {

	ULONG loop, deviceCount = auxGetNumDevs();
	ULONG volume;
	AUXCAPS caps;
	BOOL result = FALSE;

	volume = (UWORD) (rightVolume * 0xffff) << 16;
	volume |= (UWORD) (leftVolume * 0xffff);

	for (loop=0 ; loop<deviceCount ; loop++) {
		memset(&caps, 0, sizeof(caps));
		auxGetDevCaps(loop, &caps, sizeof(caps));
		if (AUXCAPS_CDAUDIO == caps.wTechnology) {
			auxSetVolume(loop, volume);
			result = TRUE;
		}
	}

	return result;
}

BOOL Main_GetCDVolume(LPREAL leftVolume, LPREAL rightVolume) {

	ULONG loop, deviceCount = auxGetNumDevs();
	ULONG volume;
	AUXCAPS caps;

	for (loop=0 ; loop<deviceCount ; loop++) {
		memset(&caps, 0, sizeof(caps));
		auxGetDevCaps(loop, &caps, sizeof(caps));
		if (AUXCAPS_CDAUDIO == caps.wTechnology) {

			auxGetVolume(loop, &volume);
			if (rightVolume) *rightVolume = (REAL) (volume >> 16) / 0xffff;
			if (leftVolume) *leftVolume = (REAL) volume / 0xffff;

			return TRUE;
		}
	}

	return FALSE;
}
*/

__inline BOOL Main_SetCDVolume(REAL leftVolume, REAL rightVolume) {

	return Main_CDVolume(&leftVolume, &rightVolume, TRUE);
}

__inline BOOL Main_GetCDVolume(LPREAL leftVolume, LPREAL rightVolume) {

	return Main_CDVolume(leftVolume, rightVolume, FALSE);
}

static BOOL Main_CDVolume(LPREAL leftVolume, LPREAL rightVolume, BOOL set) {

	ULONG deviceCount = mixerGetNumDevs();
	ULONG loop, sub, conn, controlLoop;
	MIXERCAPS caps;
	MIXERLINE mixerLine;
	HMIXER mixer;
	ULONG cConnections;
	ULONG uwVolumeL, uwVolumeR;
	BOOL result = FALSE;

	if (set) {
		if (*leftVolume > 1.0f) *leftVolume = 1.0f;
		if (*leftVolume < 0.0f) *leftVolume = 0.0f;
		if (*rightVolume > 1.0f) *rightVolume = 1.0f;
		if (*rightVolume < 0.0f) *rightVolume = 0.0f;
	}

	for (loop=0 ; loop<deviceCount ; loop++) {

		if (MMSYSERR_NOERROR == mixerOpen(&mixer, loop, 0, 0, MIXER_OBJECTF_MIXER)) {

			memset(&caps, 0, sizeof(caps));
			mixerGetDevCaps(loop, &caps, sizeof(caps));

			for (sub=0 ; sub<caps.cDestinations ; sub++) {

				memset(&mixerLine, 0, sizeof(mixerLine));
				mixerLine.cbStruct = sizeof(mixerLine);
				mixerLine.dwDestination = sub;

				if (MMSYSERR_NOERROR == mixerGetLineInfo(mixer, &mixerLine, MIXER_GETLINEINFOF_DESTINATION)) {

					cConnections = mixerLine.cConnections;

					for (conn=0 ; conn<cConnections ; conn++) {

						mixerLine.cbStruct = sizeof(mixerLine);
						mixerLine.dwDestination = sub;
						mixerLine.dwSource = conn;

						if (MMSYSERR_NOERROR == mixerGetLineInfo(mixer, &mixerLine, MIXER_GETLINEINFOF_SOURCE)) {
							if (mixerLine.dwComponentType == MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC) {

								MIXERLINECONTROLS controls;
								LPMIXERCONTROL controlList;

								memset(&controls, 0, sizeof(controls));
								controls.cbStruct = sizeof(controls);
								controls.dwLineID = mixerLine.dwLineID;
								controls.cControls = mixerLine.cControls;
								controls.cbmxctrl = sizeof(*controlList);

								controlList = Mem_Alloc(sizeof(*controlList) * controls.cControls);
								controls.pamxctrl = controlList;

								if (MMSYSERR_NOERROR == mixerGetLineControls(mixer, &controls, MIXER_GETLINECONTROLSF_ALL)) {
									for (controlLoop=0 ; controlLoop<mixerLine.cControls ; controlLoop++) {
										if ((controlList[controlLoop].dwControlType & MIXERCONTROL_CT_CLASS_FADER) &&
											(controlList[controlLoop].dwControlType & MIXERCONTROL_CONTROLTYPE_VOLUME)) {

											MIXERCONTROLDETAILS details;
											LPMIXERCONTROLDETAILS_UNSIGNED valueList;
											ULONG vLoop;

											memset(&details, 0, sizeof(details));
											details.cbStruct = sizeof(details);
											details.dwControlID = controlList[controlLoop].dwControlID;
											details.cbDetails = sizeof(*valueList);
											details.cChannels = mixerLine.cChannels;
											details.cMultipleItems = 0;

											valueList = Mem_Alloc(sizeof(*valueList) * mixerLine.cChannels);
											details.paDetails = valueList;

											if (set) {
												uwVolumeL = controlList[controlLoop].Bounds.dwMinimum + (ULONG) (*leftVolume * (controlList[controlLoop].Bounds.dwMaximum - controlList[controlLoop].Bounds.dwMinimum));
												uwVolumeR = controlList[controlLoop].Bounds.dwMinimum + (ULONG) (*rightVolume * (controlList[controlLoop].Bounds.dwMaximum - controlList[controlLoop].Bounds.dwMinimum));
												if (2 == mixerLine.cChannels) {
													valueList[0].dwValue = uwVolumeL;
													valueList[1].dwValue = uwVolumeR;
												} else {
													for (vLoop=0 ; vLoop<mixerLine.cChannels ; vLoop++) valueList[vLoop].dwValue = (uwVolumeL + uwVolumeR) / 2;
												}
												if (MMSYSERR_NOERROR == mixerSetControlDetails(mixer, &details, MIXER_GETCONTROLDETAILSF_VALUE)) {
													result = TRUE;
												}
											} else {
												if (MMSYSERR_NOERROR == mixerGetControlDetails(mixer, &details, MIXER_GETCONTROLDETAILSF_VALUE)) {

													*leftVolume = (REAL) (valueList[0].dwValue - controlList[controlLoop].Bounds.dwMinimum) / (controlList[controlLoop].Bounds.dwMaximum - controlList[controlLoop].Bounds.dwMinimum);
													if (2 == mixerLine.cChannels) {
														*rightVolume = (REAL) (valueList[1].dwValue - controlList[controlLoop].Bounds.dwMinimum) / (controlList[controlLoop].Bounds.dwMaximum - controlList[controlLoop].Bounds.dwMinimum);
													} else {
														*rightVolume = *leftVolume;
													}
													result = TRUE;
												}
											}

											Mem_Free(valueList);
										}
									}
								}
								Mem_Free(controlList);
							}
						}
					}
				}
			}

			mixerClose(mixer);
		}
	}

	return result;
}

void Main_SetWindowCallback(  void(*callback)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) )
{
	mainGlobs.windowCallback = callback;
}

void Main_SetAccel(HACCEL accels)
{
	mainGlobs.accels = accels;
}

