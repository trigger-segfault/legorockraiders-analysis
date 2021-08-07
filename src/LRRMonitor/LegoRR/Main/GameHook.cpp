// GameHook.cpp : Defines functions for hooking the WinMain
//                game loop up to the LegoRR game engine.

#include "GameHook.h"
#include "../Model/Model.h"
#include "../../resource.h"
#include "../DllMain.h"
#include "../Model/External.h"

//#include "Main.h"

//'#include "../Testing/Testing.h"


using namespace lego::game;
using namespace external;


static int spawnLevel = 0;

static const char* ObjectSpawnList[20 * 15];
static int ObjectSpawnCount = 0;
//static const char* spawnObjName = "SmallSpider";
static int spawnObjID = 0;
/*// Keys use the same numbering as used by DirectInput's "DIK_*" enums.
enum Keys : unsigned char
{
    KEY_NONE            = 0,   // Not a real KEY enum name

    KEY_ESCAPE          = 1,   // ESC
    KEY_ONE             = 2,   // '1'
    KEY_TWO             = 3,   // '2'
    KEY_THREE           = 4,   // '3'
    KEY_FOUR            = 5,   // '4'
    KEY_FIVE            = 6,   // '5'
    KEY_SIX             = 7,   // '6'
    KEY_SEVEN           = 8,   // '7'
    KEY_EIGHT           = 9,   // '8'
    KEY_NINE            = 10,  // '9'
    KEY_ZERO            = 11,  // '0'
    KEY_MINUS           = 12,  // '-'
    KEY_EQUALS          = 13,  // '='
    KEY_BACKSPACE       = 14,  // BACK
    KEY_TAB             = 15,  // '\t'
    KEY_Q               = 16,  // 'Q'
    KEY_W               = 17,  // 'W'
    KEY_E               = 18,  // 'E'
    KEY_R               = 19,  // 'R'
    KEY_T               = 20,  // 'T'
    KEY_Y               = 21,  // 'Y'
    KEY_U               = 22,  // 'U'
    KEY_I               = 23,  // 'I'
    KEY_O               = 24,  // 'O'
    KEY_P               = 25,  // 'P'
    KEY_LEFTBRACE       = 26,  // '{'
    KEY_RIGHTBRACE      = 27,  // '}'
    KEY_RETURN          = 28,  // Enter
    KEY_LEFTCTRL        = 29,  // LCtrl
    KEY_A               = 30,  // 'A'
    KEY_S               = 31,  // 'S'
    KEY_D               = 32,  // 'D'
    KEY_F               = 33,  // 'F'
    KEY_G               = 34,  // 'G'
    KEY_H               = 35,  // 'H'
    KEY_J               = 36,  // 'J'
    KEY_K               = 37,  // 'K'
    KEY_L               = 38,  // 'L'
    KEY_SEMICOLON       = 39,  // ';'
    KEY_AT              = 40,  // '"' [English U.S.], '@' [English U.K. ...I think]
    KEY_RSINGLEQUOTE    = 41,  // '~' [English U.S.], ??? [English U.K. ...could be '`' or '\'']
    KEY_LEFTSHIFT       = 42,  // LShift key
    KEY_HASH            = 43,  // '|' [English U.S.], '#' [English U.K. ...I think]
    KEY_Z               = 44,  // 'Z'
    KEY_X               = 45,  // 'X'
    KEY_C               = 46,  // 'C'
    KEY_V               = 47,  // 'V'
    KEY_B               = 48,  // 'B'
    KEY_N               = 49,  // 'N'
    KEY_M               = 50,  // 'M'
    KEY_LEFTARROW       = 51,  // '<'
    KEY_RIGHTARROW      = 52,  // '>'
    KEY_QUESTIONMARK    = 53,  // '?'
    KEY_RIGHTSHIFT      = 54,  // RShift
    KEYPAD_ASTERISK     = 55,  // Numpad '*' (Multiply)
    KEY_ALT             = 56,  // LAlt (LMenu)
    KEY_SPACE           = 57,  // ' ' Space bar
    KEY_CAPLOCK         = 58,  // CAPS lock
    KEY_F1              = 59,  // F1
    KEY_F2              = 60,  // F2
    KEY_F3              = 61,  // F3
    KEY_F4              = 62,  // F4
    KEY_F5              = 63,  // F5
    KEY_F6              = 64,  // F6
    KEY_F7              = 65,  // F7
    KEY_F8              = 66,  // F8
    KEY_F9              = 67,  // F9
    KEY_F10             = 68,  // F10
    KEYPAD_NUMLOCK      = 69,  // NUM lock key
    KEY_SCROLLLOCK      = 70,  // SCR lock key
    KEYPAD_7            = 71,  // Numpad '7'
    KEYPAD_8            = 72,  // Numpad '8'
    KEYPAD_9            = 73,  // Numpad '9'
    KEYPAD_MINUS        = 74,  // Numpad '-' (Subtract)
    KEYPAD_4            = 75,  // Numpad '4'
    KEYPAD_5            = 76,  // Numpad '5'
    KEYPAD_6            = 77,  // Numpad '6'
    KEYPAD_PLUS         = 78,  // Numpad '+' (Add)
    KEYPAD_1            = 79,  // Numpad '1'
    KEYPAD_2            = 80,  // Numpad '2'
    KEYPAD_3            = 81,  // Numpad '3'
    KEYPAD_0            = 82,  // Numpad '0'
    KEYPAD_DELETE       = 83,  // Numpad '.' (Decimal, DEL)
    KEY_BACKSLASH       = 86,  // OEM_102: <> or \| on RT 102-key keyboard (Non-U.S.)
    KEY_F11             = 87,  // F11
    KEY_F12             = 88,  // F12
    KEYPAD_ENTER        = 156, // Numpad Enter (Return)
    KEY_RIGHTCTRL       = 157, // RCtrl
    KEYPAD_FORWARDSLASH = 181, // Numpad '/' (Divide)
    KEY_PRINTSCREEN     = 183, // PRNT SCR
    KEY_ALTGR           = 184, // RAlt (RMenu): Non-English modifier key for foreign characters 
    KEY_HOME            = 199, // Home
    KEY_CURSORUP        = 200, // Up arrow key
    KEY_PGUP            = 201, // Page up (Prior)
    KEY_CURSORLEFT      = 203, // Left arrow key
    KEY_CURSORRIGHT     = 205, // Right arrow key
    KEY_END             = 207, // End
    KEY_CURSORDOWN      = 208, // Down arrow key
    KEY_PGDN            = 209, // Page down (Next)
    KEY_INSERT          = 210, // INS
    KEY_DELETE          = 211, // DEL
};*/



/*makeGlob(0076bb3c, BOOL*, g_LeftButtonState);
makeGlob(0076bb40, BOOL*, g_RightButtonState);
makeGlob(0076bb4c, BOOL*, BOOL_0076bb4c);
makeGlob(0076bb50, BOOL*, BOOL_0076bb50);
makeGlob(0076bb54, BOOL*, BOOL_0076bBOOL_0076bb54b4c);
makeGlob(0076bb58, BOOL*, g_RightButtonDoubleClicked);

makeGlob(0076ba00, bool*, g_KeyboardState_Current_TABLE);
makeGlob(0076bb80, bool*, g_KeyboardState_Previous_TABLE);

makeGlob(00506804, HINSTANCE*, g_hInstance);
makeGlob(00506800, HWND*, g_hWnd);
makeGlob(00506810, char**, g_WindowClassName);*/


bool IsKeyUp(Keys key) {
    return !g_KeyboardState_Current_TABLE[key];
}
bool IsKeyReleased(Keys key) {
    return !g_KeyboardState_Current_TABLE[key] && g_KeyboardState_Previous_TABLE[key];
}
bool IsKeyDown(Keys key) {
    return g_KeyboardState_Current_TABLE[key];
}
bool IsKeyPressed(Keys key) {
    return g_KeyboardState_Current_TABLE[key] && !g_KeyboardState_Previous_TABLE[key];
}

// [EXCLUSIVE]: WinMain, SetGameFunctions
// <LegoRR.exe @0050692c>  XREF[3,7]
//GameFunctions g_GameFunctions;
//#define g_GameFunctions defineGlobPtr(0050692c,  GameFunctions)
//,  g_GameFunctions)

// [EXCLUSIVE]: WinMain, SetGameFunctions
// <LegoRR.exe @00506938>  XREF[3]
//BOOL g_GameFunctions_ISINIT;
///#define g_GameFunctions_ISINIT defineGlobPtr(00506938,  BOOL)
//,  g_GameFunctions_ISINIT)

/*makeGlob(0050692c,  GameFunctions*, g_GameFunctions);
makeGlob(00506938,  BOOL*,          g_GameFunctions_ISINIT);
makeGlob(005570d4,  void**,  g_Game_level);

makeGlob(004df790,  LiveObject**,  g_LiveObjects_POOL);
makeGlob(004df810,  LiveObject**,  g_LiveObjects_NEXT);
makeGlob(004dfe10,  unsigned int*, g_LiveObjects_COUNT);
makeGlob(004dfe14,  unsigned int*,  g_LiveObjects_INITFLAGS);


makeGlob(004b41c8, AITaskData**, g_AITasks_TABLE);
makeGlob(004b41f8, AITaskData**, g_AITasks_NEXT);
makeGlob(004b41fc, unsigned int*, g_AITasks_COUNT);
makeGlob(004b9060, unsigned int*, g_AITasks_INITFLAGS);

makeGlob(0076bd80, ResourceData**, g_Resources_TABLE);
makeGlob(0076bdd0, ResourceData**, g_Resources_NEXT);
makeGlob(0076dd90, unsigned int*, g_Resources_COUNT);
makeGlob(0076dd94, unsigned int*, g_Resources_INITFLAGS);*/

static const char* ObjectNames[] = {
    "TVCamera",
    "None",
    "Vehicle",
    "Mini-Figure",
    "Creature",
    "Building",
    "Boulder",
    "Crystal",
    "Ore",
    "Dynamite",
    "Barrier",
    "Upgrade Part",
    "Electric Fence",
    "Spider Web",
    "Sonic Blaster",
    "Electric Fence Stud",
    "Path",
    "Pusher Shot",
    "Freezer Shot",
    "Ice Cube",
    "Laser Shot",
    "Unknown",
};
static const char* ResourceNames[] = {
    "Invalid",
    "NULL",
    "MESH  (.x)",
    "FRAME (.x)",
    "ANIM  (.x)",
    "ACT   (.ae)",
    "LIGHT",
    "unassigned",
    "LWS",
    "LWO",
    "Unknown",
};
/*enum class ResourceType : int
{
    Invalid = -1,

    Null = 0, // "NULL"  (ext: "")
    Mesh = 1, // "MESH"  (ext: "x")
    Frame = 2, // "FRAME" (ext: "x")
    Anim = 3, // "ANIM"  (ext: "x")
    Act = 4, // "ACT"   (ext: "ae") (loads "ae"-extension CFG file : g_FILEEXT_AE)
    empty = 5, // NULL    (ext: "")   (explicit)
    unassigned = 6, // NULL    (ext: NULL) (implicit)
    Lws = 7, // "LWS"   (ext: NULL)
    Lwo = 8, // "LWO"   (ext: NULL)
};*/
/*makeFunc(00478780,  LRESULT, WindowProc_FullScreen, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
makeFunc(00478980,  LRESULT, WindowProc_Windowed,   HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

makeGlob(00506f84, lego::CmdlineFlags*, g_CMDLINE_FLAGS);*/

//#define defCdecl(ADDR, RETURN, NAME, ...) RETURN (__cdecl* NAME) __VA_ARGS__ ;

//defCdecl(0x004ebd60, LRESULT, WindowProc_FullScreen2, (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam));

/*namespace external {
    LRESULT (__cdecl* WindowProc_FullScreen)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = *(LRESULT(__cdecl*)(HWND, UINT, WPARAM, LPARAM)) 0x00478780;

    LRESULT (__cdecl* WindowProc_Windowed)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = *(LRESULT(__cdecl*)(HWND, UINT, WPARAM, LPARAM)) 0x00478980;
}*/
/*typedef lego::CmdlineFlags __based(g_CMDLINE_FLAGS) gg_CMDLINE_FLAGS;
#define makeGlob(addr, type, name) static type name = (( type ) 0x ##addr )

#define makeBased(addr, type, name) namespace internalstatic type name = (( type ) 0x ##addr )*/

/*// <LegoRR.exe @00478780>
LRESULT __cdecl lego::main::WindowProc_FullScreen(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// <LegoRR.exe @00478980>
LRESULT __cdecl lego::main::WindowProc_Windowed(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);*/

// <LegoRR.exe @00478b40>
LRESULT CALLBACK lego::game::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_SETCURSOR)
    {
        if (LOWORD(lParam) == HTCLIENT)
        {
            SetCursor(NULL);
            return TRUE;
        }

        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    if (g_CMDLINE_FLAGS & CMD_FULLSCREEN) {
        return external::WindowProc_FullScreen(hWnd, message, wParam, lParam);
    }
    else {
        return external::WindowProc_Windowed(hWnd, message, wParam, lParam);
    }
}

// <LegoRR.exe @004786b0>
BOOL __cdecl lego::game::CreateMainWindow(HINSTANCE hInstance, int nCmdShow)
{
    WNDCLASSA wc;
    std::memset(&wc, 0, sizeof(wc));

    wc.style = CS_DBLCLKS; //CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC)WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    if (FindResourceA(hInstance, MAKEINTRESOURCEA(114), MAKEINTRESOURCEA(RT_GROUP_ICON))) {
        wc.hIcon = LoadIconA(hInstance, MAKEINTRESOURCEA(114));
    }
    if (wc.hIcon == nullptr) {
        wc.hIcon = LoadIconA(hInstance, MAKEINTRESOURCEA(113) /*MAINICON*/); // nullptr;
    }
    wc.hCursor = nullptr; //LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = nullptr; //(HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_MODESELECTION);
    wc.lpszClassName = const_cast<LPSTR>(g_WindowClassName);

    ATOM atom = RegisterClassA(&wc);
    if (!atom) {
        MessageBoxA(nullptr, "Unable to register window class", "Fatal Error", MB_OK /*0*/);
        return FALSE;
    }
    g_hWnd = CreateWindowExA(WS_EX_APPWINDOW,
        const_cast<LPSTR>(g_WindowClassName),
        ""/*EMPTYSTR*/,
        WS_POPUP | WS_SYSMENU,
        0, 0, 100, 100,
        nullptr, nullptr,
        hInstance, nullptr);

    if (!g_hWnd) {
        MessageBoxA(nullptr, "Unable to Create Main Window", "Fatal Error", MB_OK /*0*/);
        return FALSE;
    }

    SetFocus(g_hWnd);
    return TRUE;
}

/*static FILE* logFile = nullptr;
static BOOL isDone = false;
static void* addr_SetMainWindowTitle = (void*)0x00478690;*/

static const char* lp_title_dummy = nullptr;

//static int updateCount = 0;
//#define UPDATE_INTERVAL 25.0f
//static float lastUpdate = 0.0f;// UPDATE_INTERVAL;

// <LegoRR.exe @00478690>
void __cdecl lego::game::SetMainWindowTitle(const char* title)
{
    logmsg("SetMainWindowTitle\n");
    lp_title_dummy = title;
    /*if (logFile) {
        std::fprintf(logFile, "SetMainWindowTitle [called]\n");
        std::fflush(logFile);
    }*/
    //std::fprintf(logFile, "globals::gp_hWnd -> %08x\n", (unsigned int)*globals::gp_hWnd);
    //std::fflush(logFile);
    //GetWindow()
    char buffer[1024];
    std::sprintf(buffer, "%s (Monitor Debugging)", title);
    BOOL result = SetWindowTextA(g_hWnd, buffer); // "LRRCE-TITLEREPLACE");// , title);
    //BOOL result = SetWindowTextA(*((HWND*)0x00506800), buffer); // "LRRCE-TITLEREPLACE");// , title);
    //BOOL result = SetWindowTextA(*globals::gp_hWnd, "LRRCE-TITLEREPLACE");// , title);
    /*if (logFile) {
        std::fclose(logFile);
        logFile = nullptr;
    }*/
    //return result;
}

#pragma region Functions

/*// This function is the hook that links the base engine setup to the actual gameplay and game configurations.
// Everything called by this (or functions passed by this) is the only time any of the game-relevant variables are used.
// <LegoRR.exe @0041f950>
BOOL __cdecl lego::game::InitGameFunctions(const char* gameName)
{
    // GameData struct
    //std::memset(&globals::g_Game, 0, sizeof(GameData));
    //globals::g_Game.CfgRootName = exeName;

    main::SetMainWindowTitle(gameName);

    GameFunctions gameFuncs = {
        testing::MyGameInitFunction,
        testing::MyGameUpdateFunction,
        testing::MyGameCleanupFunction
    };*/

    /// We're not actually setting up anything that's part of the game... this is just a skeleton
    /*GameFunctions gameFuncs;
    gameFuncs.Init = Main_loadLegoCFG;
    gameFuncs.Update = Main_GameUpdate;
    gameFuncs.Cleanup = Main_GameCleanup;

    if (globals::g_PROGRAMMER_MODE != PROGRAMMER_MODE_10) {
        gameFuncs.Cleanup = Game_Exit;
    }*/

//    return SetGameFunctions(&gameFuncs);
//}

static GameFunctions g_origGameFunctions;


// <LegoRR.exe @0049d5b0>
INT_PTR CALLBACK DialogProc2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    //sizeof(LiveObject)
	char screenModeText[1024];

	switch (message) {
	case WM_INITDIALOG /*0x110*/: {
        logmsg("WM_INITDIALOG\n");

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
#if 0
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
#endif
		return (INT_PTR)FALSE;
	}
	case WM_COMMAND /*0x111*/: {
		WORD msgSource = HIWORD(wParam);
		WORD idCaller  = LOWORD(wParam);

		if (msgSource == 1 /*message from Accelerator*/) {
#if 0
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
#endif
		}
		else if (msgSource == 0 /*message from Menu*/) {
#if 0
			if (idCaller == IDC_WINDOW_RADIOBUTTON /*1005*/) {
				ChangeFullScreenMode(hDlg, FALSE);
			}
			else if (idCaller == IDC_FULLSCREEN_RADIOBUTTON /*1004*/) {
				ChangeFullScreenMode(hDlg, TRUE);
			}
			else
#endif
            if (idCaller == IDOK /*1*/ || idCaller == IDCANCEL /*2*/) {
				EndDialog(hDlg, LOWORD(wParam) /* end dialog with OK or Cancel button as argument*/);
			}
		}
		return (INT_PTR)TRUE;
	}
	default:
		return (INT_PTR)FALSE;
	}
}

//static HWND g_hDlg = nullptr;


//#define UPDATE_INTERVAL 25.0f
class LiveObjectsMonitor
{
    HWND m_hDlg = nullptr;
    int updateCount = 0;
    float lastUpdate = 0.0f;// UPDATE_INTERVAL;
    //static LiveObjectsMonitor* g_singleton;
    float updateInterval = 25.0f;

public:
    const char* Name() const
    {
        return "Live Objects Monitor";
    }

    bool IsOpen() const
    {
        return this->m_hDlg != nullptr;
    }

    bool Open()
    {
        if (this->m_hDlg == nullptr) {
            logmsg("this = 0x%08x\n", (unsigned int)this);
            this->m_hDlg = CreateDialogParamA(g_hDllInstance, MAKEINTRESOURCEA(IDD_LIVEOBJECTS),
                g_hWnd, LiveObjectsMonitor::DialogProc, (LPARAM)this);// nullptr);
            if (this->m_hDlg == nullptr) {
                logmsg("CreateDialogParamA failed\n");
            }
            else {
                logmsg("CreateDialogParamA success\n");
                RECT desktopRect, dlgRect;
                HWND hDesktopWnd = GetDesktopWindow();
                GetWindowRect(hDesktopWnd, &desktopRect);
                GetWindowRect(this->m_hDlg, &dlgRect);
                MoveWindow(this->m_hDlg, (desktopRect.right / 2)  - ((dlgRect.right - dlgRect.left) / 2),
                                         (desktopRect.bottom / 2) - ((dlgRect.bottom - dlgRect.top) / 2),
                    dlgRect.right - dlgRect.left,
                    dlgRect.bottom - dlgRect.top,
                    TRUE /*repaint*/);
                ShowWindow(this->m_hDlg, SW_SHOW);
                //ShowWindow(this->m_hDlg, SW_SHOW);
            }
        }
        return this->m_hDlg != nullptr;
    }
    bool Close()
    {
        if (this->m_hDlg != nullptr) {
            logmsg("Close() begin\n");
            EndDialog(this->m_hDlg, (INT_PTR)IDOK);
            //DestroyWindow(this->m_hDlg);
            logmsg("Close() end\n");
            this->m_hDlg = nullptr;
        }
        return this->m_hDlg == nullptr;
    }

    bool Update(float elapsed, bool force = false)
    {
        if (!this->IsOpen())
            return true;

        this->lastUpdate += elapsed;
        if (this->m_hDlg != nullptr && (this->updateCount <= 1 || this->lastUpdate >= this->updateInterval || force)) {
            if (this->updateCount == 1) {
                logmsg("MyGameUpdate [second] [0x%08x]\n", (unsigned int)g_LiveObjects_POOL);
                /*float trainF = Level_GetTrainTimeF();
                double trainD = Level_GetTrainTimeD();
                long double trainLD = Level_GetTrainTimeLD();
                float speedF = Game_GetGameSpeedF();
                double speedD = Game_GetGameSpeedD();
                long double speedLD = Game_GetGameSpeedLD();
                logmsg("trainF  = %f\n", (double)trainF);
                logmsg("trainD  = %f\n", (double)trainD);
                logmsg("trainLD = %f\n", (double)trainLD);
                logmsg("l->TrainTime  = %f\n", (double)g_Game.level->TrainTime);
                logmsg("l->RoughLevel = %f\n", (double)g_Game.level->RoughLevel);
                logmsg("speedF  = %f\n", (double)speedF);
                logmsg("speedD  = %f\n", (double)speedD);
                logmsg("speedLD = %f\n", (double)speedLD);
                logmsg("g->gameSpeed = %f\n", (double)g_Game.gameSpeed);*/
                //logmsg("l->TrainTime  = %f\n", (double)g_Game_level->TrainTime);
                //logmsg("l->RoughLevel = %f\n", (double)g_Game_level->RoughLevel);
            }

            this->lastUpdate = 0.0f;
            this->updateCount++;

            //return TRUE;
            char buffer[2048];
            std::memset(buffer, 0, sizeof(buffer));
            unsigned int objCounts[22];
            std::memset(objCounts, 0, sizeof(objCounts));
            unsigned int cryoreLevels[3][16];
            std::memset(cryoreLevels, 0, sizeof(cryoreLevels));
            unsigned int resCounts[11];
            std::memset(resCounts, 0, sizeof(resCounts));
            std::map<int, int> unkObjectTypes;
            std::map<int, int> unkResourceTypes;
            unsigned int total = 0, total2 = 0, total3 = 0;
            bool enabled = ((g_LiveObjects_INITFLAGS & 1) != 0) && (g_LiveObjects_COUNT >= 0 && g_LiveObjects_COUNT <= 32) && g_Game_level != nullptr;
            unsigned int capacity = 0, capacity2 = 0, capacity3 = 0;
            if (enabled) {
                for (unsigned int i = 0; i < g_LiveObjects_COUNT; i++) {
                    unsigned int curCount = (1 << i);
                    capacity += curCount;
                    for (unsigned int j = 0; j < curCount; j++) {
                        volatile LiveObject* liveObj = &g_LiveObjects_POOL[i][j];
                        if (liveObj->pool_m_next != liveObj)
                            continue; // not alive

                        total++;
                        if ((int)liveObj->objType > 0 && (int)liveObj->objType <= 19) {// && (int)liveObj->objType != 0) {
                            objCounts[(int)liveObj->objType + 1]++;
                            if (liveObj->objType == ObjectType::PowerCrystal)
                                cryoreLevels[0][liveObj->objLevel]++;
                            else if (liveObj->objType == ObjectType::Ore)
                                cryoreLevels[1 + liveObj->objIndex][liveObj->objLevel]++;
                        }
                        else {
                            objCounts[21]++;
                            if (unkObjectTypes.find((int)liveObj->objType) == unkObjectTypes.end()) {
                                unkObjectTypes[(int)liveObj->objType] = 0;
                            }
                            unkObjectTypes[(int)liveObj->objType] += 1;
                        }
                    }
                }
            }
            bool enabled2 = ((g_AITasks_INITFLAGS & 1) != 0) && (g_AITasks_COUNT >= 0 && g_AITasks_COUNT <= 12) && g_Game_level != nullptr;
            if (enabled2) {
                for (unsigned int i = 0; i < g_AITasks_COUNT; i++) {
                    unsigned int curCount = (1 << i);
                    capacity2 += curCount;
                    for (unsigned int j = 0; j < curCount; j++) {
                        volatile AITaskData* aiTask = &g_AITasks_TABLE[i][j];
                        if (aiTask->pool_m_next != aiTask)
                            continue; // not alive

                        total2++;
                    }
                }
            }
            bool enabled3 = ((g_Resources_INITFLAGS & 1) != 0) && (g_Resources_COUNT >= 0 && g_Resources_COUNT <= 20) && g_Game_level != nullptr;
            if (enabled3) {
                for (unsigned int i = 0; i < g_Resources_COUNT; i++) {
                    unsigned int curCount = (1 << i);
                    capacity3 += curCount;
                    for (unsigned int j = 0; j < curCount; j++) {
                        volatile ResourceData* resData = &g_Resources_TABLE[i][j];
                        if (resData->pool_m_next != resData)
                            continue; // not alive

                        total3++;
                        if ((int)resData->resType > -1 && (int)resData->resType <= 8) {
                            resCounts[(int)resData->resType + 1]++;
                        }
                        else {
                            resCounts[10]++;
                            if (unkResourceTypes.find((int)resData->resType) == unkResourceTypes.end()) {
                                unkResourceTypes[(int)resData->resType] = 0;
                            }
                            unkResourceTypes[(int)resData->resType] += 1;
                        }
                    }
                }
            }
            //SendMessageA(this->m_hDlg, WM_SETREDRAW, (WPARAM)FALSE, (LPARAM)nullptr);

            if (enabled) {
                std::sprintf(buffer, "LiveObjects [ %6i / %6i ]", (int)total, (int)capacity);
            }
            else {
                std::sprintf(buffer, "LiveObjects [unused]");
            }
            HWND hCtrlLabel = GetDlgItem(this->m_hDlg, IDC_LABEL);
            SendMessageA(hCtrlLabel, WM_SETTEXT, (WPARAM)0, (LPARAM)buffer);

            HWND hCtrlListbox = GetDlgItem(this->m_hDlg, IDC_LISTBOX);
            while (SendMessageA(hCtrlListbox, LB_DELETESTRING /*0x182*/, 0, 0) != -1);

            char buffer2[512];
            std::memset(buffer, 0, sizeof(buffer2));
            for (int i = -1; i <= 19; i++) {
                if (i <= 0)
                    continue;
                if (objCounts[i + 1] && enabled) {
                    std::sprintf(buffer, "[%4i] : %s", (int)objCounts[i + 1], ObjectNames[i + 1]);
                    for (int j = 1; j < 4 && buffer[j] != '\0'; j++) {
                        //if (buffer[j] == ' ')
                            //buffer[j] = '\xa0';
                    }
                    if (i == (int)ObjectType::PowerCrystal || i == (int)ObjectType::Ore) {
                        int idx = (i - (int)ObjectType::PowerCrystal);
                        std::strcat(buffer, " (");
                        int bufPos = std::strlen(buffer);// , , (int)objCounts[21], ObjectNames[21]);
                        int ii = 0;
                        for (int j = 0; j < 16; j++) {
                            if (cryoreLevels[idx][j] == 0)
                                continue;

                            if (j != 0) {
                                bufPos += std::sprintf(&buffer[bufPos], ", ");
                            }
                            bufPos += std::sprintf(&buffer[bufPos], "L%i=%i", j, cryoreLevels[idx][j]);
                        }
                        bufPos += std::sprintf(&buffer[bufPos], ")");
                    }
                }
                else {
                    std::sprintf(buffer, " ----  : %s", ObjectNames[i + 1]);
                }
                SendMessageA(hCtrlListbox, LB_ADDSTRING, (WPARAM)0, (LPARAM)buffer);
            }
            if (objCounts[21] != 0) {
                int bufPos = std::sprintf(buffer, "[%4i] : %s (", (int)objCounts[21], ObjectNames[21]);
                int ii = 0;
                for (std::map<int, int>::iterator iter = unkObjectTypes.begin(); iter != unkObjectTypes.end(); ++iter) {
                    if (ii++ != 0) {
                        bufPos += std::sprintf(&buffer[bufPos], ", ");
                    }
                    bufPos += std::sprintf(&buffer[bufPos], "%i=%i", (int)iter->first, (int)iter->second);
                }
                bufPos += std::sprintf(&buffer[bufPos], ")");
            }
            else {
                std::sprintf(buffer, " ----  : %s", ObjectNames[21]);
            }
            SendMessageA(hCtrlListbox, LB_ADDSTRING, (WPARAM)0, (LPARAM)buffer);
            if (enabled2) {
                std::sprintf(buffer, "AITasks   [ %6i / %6i ]", (int)total2, (int)capacity2);
            }
            else {
                std::sprintf(buffer, "AITasks   [unused]");
            }
            SendMessageA(hCtrlListbox, LB_ADDSTRING, (WPARAM)0, (LPARAM)buffer);
            if (enabled3) {
                std::sprintf(buffer, "Resources [ %6i / %6i ]", (int)total3, (int)capacity3);
            }
            else {
                std::sprintf(buffer, "Resources [unused]");
            }
            SendMessageA(hCtrlListbox, LB_ADDSTRING, (WPARAM)0, (LPARAM)buffer);
            for (int i = 0; i <= 8; i++) {
                if (i < 0)
                    continue;
                if (resCounts[i + 1] && enabled) {
                    std::sprintf(buffer, "[%4i] : %s", (int)resCounts[i + 1], ResourceNames[i + 1]);
                    for (int j = 1; j < 4 && buffer[j] != '\0'; j++) {
                        //if (buffer[j] == ' ')
                            //buffer[j] = '\xa0';
                    }
                }
                else {
                    std::sprintf(buffer, " ----  : %s", ResourceNames[i + 1]);
                }
                SendMessageA(hCtrlListbox, LB_ADDSTRING, (WPARAM)0, (LPARAM)buffer);
            }
            if (resCounts[10] != 0) {
                int bufPos = std::sprintf(buffer, "[%4i] : %s ...", (int)resCounts[10], ResourceNames[10]);
                int ii = 0;
                for (std::map<int, int>::iterator iter = unkResourceTypes.begin(); iter != unkResourceTypes.end(); ++iter) {
                    if (ii++ != 0) {
                        bufPos += std::sprintf(&buffer[bufPos], ", ");
                    }
                    bufPos += std::sprintf(&buffer[bufPos], "%i=%i", (int)iter->first, (int)iter->second);
                }
                //bufPos += std::sprintf(&buffer[bufPos], ")");
            }
            else {
                std::sprintf(buffer, " ----  : %s", ResourceNames[10]);
            }
            SendMessageA(hCtrlListbox, LB_ADDSTRING, (WPARAM)0, (LPARAM)buffer);

            std::sprintf(buffer, "WallSpawn: %s (LV%i)", ObjectSpawnList[spawnObjID], spawnLevel);
            SendMessageA(hCtrlListbox, LB_ADDSTRING, (WPARAM)0, (LPARAM)buffer);

            //SendMessageA(this->m_hDlg, WM_SETREDRAW, (WPARAM)TRUE, (LPARAM)nullptr);
        }
        return true;
    }

    static INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        LiveObjectsMonitor* self;
        if (message == WM_INITDIALOG) {
            self = (LiveObjectsMonitor*)lParam;
            SetWindowLongA(hDlg, DWLP_USER, lParam);
        }
        else {
            self = (LiveObjectsMonitor*)GetWindowLongA(hDlg, DWLP_USER);
        }
        //sizeof(LiveObject)
        char screenModeText[1024];

        switch (message) {
        /*case WM_SETCURSOR: {
            WORD ht = LOWORD(lparam);
            static bool hiddencursor = false;
            if (HTCLIENT == ht && !hiddencursor)
            {
                hiddencursor = true;
                ShowCursor(false);
            }
            else if (HTCLIENT != ht && hiddencursor)
            {
                hiddencursor = false;
                ShowCursor(true);
            }
        }
                         break;*/
            /*if ((HWND)wParam == GetDlgItem(hwnd, 4000))
            {
                SetCursor(MAKEINTRESOURCEA(IDC_ARROW));
                return TRUE;
            }
            return DefWindowProcA(hwnd, uMsg, wParam, lParam);*/
        case WM_DESTROY:
            logmsg("WM_DESTROY\n");
            if (self->m_hDlg == hDlg) {
                logmsg("WM_DESTROY m_hDlg == hDlg\n");
                self->m_hDlg = nullptr;
            }
            break;
        case WM_CLOSE:
            logmsg("WM_CLOSE\n");
            logmsg("self = 0x%08x\n", (unsigned int)self);
            if (self->m_hDlg == hDlg) {
                logmsg("WM_CLOSE m_hDlg == hDlg\n");
                self->m_hDlg = nullptr;
            }
            break;
        case WM_INITDIALOG /*0x110*/: {
            logmsg("WM_INITDIALOG\n");
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
#if 0
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
#endif
            return (INT_PTR)FALSE;
        }
        case WM_COMMAND /*0x111*/: {
            WORD msgSource = HIWORD(wParam);
            WORD idCaller = LOWORD(wParam);

            if (msgSource == 1 /*message from Accelerator*/) {
#if 0
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
#endif
            }
            else if (msgSource == 0 /*message from Menu*/) {
#if 0
                if (idCaller == IDC_WINDOW_RADIOBUTTON /*1005*/) {
                    ChangeFullScreenMode(hDlg, FALSE);
                }
                else if (idCaller == IDC_FULLSCREEN_RADIOBUTTON /*1004*/) {
                    ChangeFullScreenMode(hDlg, TRUE);
                }
                else
#endif
                    if (idCaller == IDOK /*1*/ || idCaller == IDCANCEL /*2*/) {
                        logmsg("EndDialog\n");
                        EndDialog(hDlg, LOWORD(wParam) /* end dialog with OK or Cancel button as argument*/);
                    }
            }
            return (INT_PTR)TRUE;
        }
        default:
            return (INT_PTR)FALSE;
        }
        return (INT_PTR)FALSE;
    }
};

static LiveObjectsMonitor liveObjMonitor = LiveObjectsMonitor();



//makeFunc(004752e0, void, Res_SetMeshColorMultiplier, ResourceData* resData, int index, DWORD r, DWORD g, DWORD b, DWORD unkMultiplier);
//makeFunc(004752b0, void, Res_SetMeshColorUnk, ResourceData* resData, int index, DWORD r, DWORD g, DWORD b);


//typedef unsigned int ObjArrayIndexes[15];
//typedef unsigned int ObjArrayLevels[15][16];

#define SetColor(r,g,b) do { colorf.red = ((float)(r)) / 255.0f; colorf.green = ((float)(g)) / 255.0f; colorf.blue = ((float)(b)) / 255.0f; } while (0)

#define SetColorh(rgb) do { colorf.red = ((float)((0x ##rgb)>>16&0xff)) / 255.0f; colorf.green = ((float)((0x ##rgb)>>8&0xff)) / 255.0f; colorf.blue = ((float)((0x ##rgb)&0xff)) / 255.0f; } while (0)
#define SetColorH(rgb) do { colorf.red = ((float)((0x ##rgb)>>16&0xff)) / 255.0f; colorf.green = ((float)((0x ##rgb)>>8&0xff)) / 255.0f; colorf.blue = ((float)((0x ##rgb)&0xff)) / 255.0f; } while (0); break

/*makeFunc(00474ce0, int,  Res_GetMeshGroupCount,      ResourceData* resData);
makeFunc(004752e0, void, Res_SetMeshColorMultiplier, ResourceData* resData, int index, float r, float g, float b, float multiplier);
makeFunc(004752b0, void, Res_SetMeshColorUnk,        ResourceData* resData, int index, float r, float g, float b);

makeGlob(00557428, lego::ColourRGBF*, g_PowerCrystalRGB);
makeGlob(00557434, lego::ColourRGBF*, g_UnpoweredCrystalRGB);
makeGlob(00503c28, ObjArrayIndexes*,  g_ObjectLevels_TABLE);              // [20][15]
makeGlob(004e4944, ObjArrayLevels*,   g_LiveObjectLevels_Previous_TABLE); // [20][15][16]
makeGlob(004dfe44, ObjArrayLevels*,   g_LiveObjectLevels_Current_TABLE);  // [20][15][16]
makeGlob(00503bd8, ObjectStats***,    g_ObjectStats_TABLE);               // [20][*][*]*/

// <LegoRR.exe @00438670>
void __cdecl lego::game::LiveObject_SetIsCrystalPowered(LiveObject* liveObj, BOOL isPowered)
{
    if (liveObj->objType == ObjectType::PowerCrystal) {// || (liveObj->other != nullptr && ((void**)liveObj->other->subdata_c)[2] != nullptr && ((void**)liveObj->other->subdata_c)[3] != nullptr)) {
        lego::ColourRGBF colorf;
        if (liveObj->objLevel >= 1 && liveObj->objType == ObjectType::PowerCrystal) {
            if (!isPowered && liveObj->objType == ObjectType::PowerCrystal) {
                //SetColorh(FF0000);
				colorf.red   = 1.0f;
                colorf.green = 0.0f;
                colorf.blue  = 0.0f;
			}
            else {
                /*switch ((rand() % 12) + 3) {
                //case  0: SetColorH(FFFFFF);
                //case  15: SetColorH(C0C0C0);
                //case  1: SetColorH(808080);
                //case  2: SetColorH(000000);
                case  3: SetColorH(800000);
                case  4: SetColorH(FF8000);
                case  5: SetColorH(FFFF00);
                case  6: SetColorH(808000);
                case  7: SetColorH(008000);
                case  8: SetColorH(00FFFF);
                case  9: SetColorH(008080);
                case 10: SetColorH(0000FF);
                case 11: SetColorH(000080);
                case 12: SetColorH(00FF00);
                case 13: SetColorH(FF00FF);
                case 14: SetColorH(800080);
                default: SetColorH(000000);
                }*/
                /*colorf.red   = 1.0f;
                colorf.green = 0.0f;
                colorf.blue  = 0.0f;
                SetColor(255, 255, 255);*/
                colorf.red   = 0.0f;
                colorf.green = 1.0f;
                colorf.blue  = 1.0f;
            }
        }
        else {
            if (!isPowered)
                colorf = *const_cast<ColourRGBF*>(&g_UnpoweredCrystalRGB);
            else
                colorf = *const_cast<ColourRGBF*>(&g_PowerCrystalRGB);
            /*if (!isPowered)
                colorf = *g_UnpoweredCrystalRGB;
            else
                colorf = *g_PowerCrystalRGB;*/
        }
        for (int index = 0; index < Res_GetMeshGroupCount(liveObj->other); index++) {
            Res_SetMeshColorMultiplier(liveObj->other, index, colorf.red, colorf.green, colorf.blue, 1.0f);
            Res_SetMeshColorUnk(liveObj->other, index, colorf.red, colorf.green, colorf.blue);
        }
    }
}
static void __cdecl SetResDataColor(ResourceData* resData, LiveObject* liveObj)
{
    if (liveObj->objType != ObjectType::PowerCrystal && (liveObj->other != nullptr && ((void**)liveObj->other->subdata_c)[0x8/4] != nullptr && ((void**)liveObj->other->subdata_c)[0xc/4] != nullptr)) {
        lego::ColourRGBF colorf;
        switch ((rand() % 12) + 3) {
            //case  0: SetColorH(FFFFFF);
            //case  15: SetColorH(C0C0C0);
            //case  1: SetColorH(808080);
            //case  2: SetColorH(000000);
        case  3: SetColorH(800000);
        case  4: SetColorH(FF8000);
        case  5: SetColorH(FFFF00);
        case  6: SetColorH(808000);
        case  7: SetColorH(008000);
        case  8: SetColorH(00FFFF);
        case  9: SetColorH(008080);
        case 10: SetColorH(0000FF);
        case 11: SetColorH(000080);
        case 12: SetColorH(00FF00);
        case 13: SetColorH(FF00FF);
        case 14: SetColorH(800080);
        default: SetColorH(000000);
        }
        for (int index = 0; index < Res_GetMeshGroupCount(resData); index++) {
            Res_SetMeshColorMultiplier(resData, index, colorf.red, colorf.green, colorf.blue, 1.0f);
            Res_SetMeshColorUnk(resData, index, colorf.red, colorf.green, colorf.blue);
        }
    }
}

// <LegoRR.exe @00469ed0>
BOOL __cdecl lego::game::LiveObject_SetLevel(LiveObject* liveObj, unsigned int level)
{
    if (level < g_ObjectLevels_TABLE[(int)liveObj->objType][liveObj->objIndex]) {
        if (level != liveObj->objLevel) {
            g_LiveObjectLevels_Previous_TABLE[(int)liveObj->objType][liveObj->objIndex][liveObj->objLevel]++; // old lvl state
            g_LiveObjectLevels_Current_TABLE[(int)liveObj->objType][liveObj->objIndex][level]++; // new lvl state
        }
        liveObj->objLevel = level;
        liveObj->stats = const_cast<ObjectStats*>(&g_ObjectStats_TABLE[(int)liveObj->objType][liveObj->objIndex][level]); // update the lvl'ed stats
        // Crystal color is automatically set on creation (but before Level is set to non-zero).
        //  So we have to hijack this function just to handle recoloring.
        if (liveObj->objType == ObjectType::PowerCrystal && level >= 1)
            LiveObject_SetIsCrystalPowered(liveObj, !(liveObj->flags3_3e8 & 0x80000000) /* unpowered flag*/);

        return TRUE;
    }
    return FALSE;
}

// <LegoRR.exe @00474060>
void __cdecl lego::game::Res_SetOwnerObject(ResourceData* resData, LiveObject* liveObj)
{
    ((LiveObject**)resData)[0x20/4] = liveObj; // field_20
    //LiveObject_SetIsCrystalPowered(liveObj, !(liveObj->flags_3e8 & 0x80000000) /* unpowered flag*/);
    
	// SetResDataColor(resData, liveObj);
    
	//((LiveObject**)resData->ownerObj)[0x20/4] = liveObj;
    return;
}

/*
                colorf.red   = UnpoweredCrystalRGB->red;
                colorf.green = UnpoweredCrystalRGB->green;
                colorf.blue  = UnpoweredCrystalRGB->blue;
                colorf.red   = PowerCrystalRGB->red;
                colorf.green = PowerCrystalRGB->green;
                colorf.blue  = PowerCrystalRGB->blue;
                
                colorf.alpha = 1.0f;
lego::ColourRGBAF color;
std::memcpy(&color, &colorf, sizeof(color));*/


// <LegoRR.exe @00474ce0>
//int __cdecl Res_GetMeshGroupCount(ResourceData* resData);

// <LegoRR.exe @004752e0>
//void __cdecl Res_SetMeshColorMultiplier(ResourceData* resData, int index, float r, float g, float b, float unkMultiplier);

// <LegoRR.exe @004752b0>
//void __cdecl Res_SetMeshColorUnk(ResourceData* resData, int index, float r, float g, float b);

//static ObjectType spawnObj = ObjectType::RockMonster;
//static int spawnIndex;
//g_ObjectLevels_TABLE[]
BOOL __cdecl MyGameInit(void)
{
    ShowCursor(TRUE);
    logmsg("MyGameInit\n");
    if (g_origGameFunctions.Init != nullptr) {
        if (!g_origGameFunctions.Init()) {
            logmsg("MyGameInit [internal failed]\n");
            return FALSE;
        }
    }
    //void* dummy;
    //Game_GetObjectByName("SmallSpider", &spawnObj, &spawnIndex, (ResourceData**)&dummy);
    std::memset(ObjectSpawnList, 0, sizeof(ObjectSpawnList));

    for (int i = 0; i < g_Game.RockMonsterTypes_COUNT; i++) {
        ObjectSpawnList[ObjectSpawnCount++] = g_Game.RockMonsterTypes_TABLE[i];
        if (::_stricmp(g_Game.RockMonsterTypes_TABLE[i], "SmallSpider") == 0)
            spawnObjID = ObjectSpawnCount - 1;
    }
    for (int i = 0; i < g_Game.MiniFigureTypes_COUNT; i++)
        ObjectSpawnList[ObjectSpawnCount++] = g_Game.MiniFigureTypes_TABLE[i];
    for (int i = 0; i < g_Game.VehicleTypes_COUNT; i++)
        ObjectSpawnList[ObjectSpawnCount++] = g_Game.VehicleTypes_TABLE[i];
    for (int i = 0; i < g_Game.BuildingTypes_COUNT; i++)
        ObjectSpawnList[ObjectSpawnCount++] = g_Game.BuildingTypes_TABLE[i];
    ObjectSpawnList[ObjectSpawnCount++] = "PowerCrystal";
    ObjectSpawnList[ObjectSpawnCount++] = "Ore";
    ObjectSpawnList[ObjectSpawnCount++] = "ProcessedOre";
    ObjectSpawnList[ObjectSpawnCount++] = "Dynamite";
    ObjectSpawnList[ObjectSpawnCount++] = "OohScary";
    ObjectSpawnList[ObjectSpawnCount++] = "ElectricFence";
    ObjectSpawnList[ObjectSpawnCount++] = "Barrier";
    ObjectSpawnList[ObjectSpawnCount++] = "Boulder";
    ObjectSpawnList[ObjectSpawnCount++] = "Pusher";
    ObjectSpawnList[ObjectSpawnCount++] = "Pusher";
    ObjectSpawnList[ObjectSpawnCount++] = "LaserShot";
    ObjectSpawnList[ObjectSpawnCount++] = "Freezer";
    /*ObjectSpawnList[0] = "SmallSpider";
    ObjectSpawnList[0] = "Bat";
    ObjectSpawnList[0] = "Bat";*/

    liveObjMonitor.Open();
    /*g_hDlg = CreateDialogParamA(g_hDllInstance, MAKEINTRESOURCEA(IDD_LIVEOBJECTS),
        *g_hWnd,
        DialogProc, (LPARAM)&g_hDlg);// nullptr);
    if (g_hDlg == nullptr || (int)g_hDlg == -1) {
        logmsg("CreateDialogParamA failed\n");
    }
    else {
        logmsg("CreateDialogParamA success\n");
        RECT desktopRect, dlgRect;
        HWND hDesktopWnd = GetDesktopWindow();
        GetWindowRect(hDesktopWnd, &desktopRect);
        GetWindowRect(g_hDlg, &dlgRect);
        MoveWindow(g_hDlg, (desktopRect.right / 2) - ((dlgRect.right - dlgRect.left) / 2),
            (desktopRect.bottom / 2) - ((dlgRect.bottom - dlgRect.top) / 2),
            dlgRect.right - dlgRect.left,
            dlgRect.bottom - dlgRect.top,
            TRUE); //repaint
        ShowWindow(g_hDlg, SW_SHOW);
        //ShowWindow(g_hDlg, SW_SHOW);
    }*/
    /*    HINSTANCE hInstance,
        LPCSTR    lpTemplateName,
        HWND      hWndParent,
        DLGPROC   lpDialogFunc,
        LPARAM    dwInitParam
    );*/

    return TRUE;
}

BOOL __cdecl MyGameUpdate(float elapsed)
{

    bool change = true;
    if (IsKeyPressed(Keys::KEY_SEMICOLON)) {
        if (IsKeyDown(Keys::KEY_LEFTSHIFT))
            spawnLevel = max(0, spawnLevel - 2);
        else
            spawnLevel = max(0, spawnLevel - 1);
    }
    else if (IsKeyPressed(Keys::KEY_AT)) {
        if (IsKeyDown(Keys::KEY_LEFTSHIFT))
            spawnLevel = min(15, spawnLevel + 2);
        else
            spawnLevel = min(15, spawnLevel + 1);
    }
    else if (IsKeyPressed(Keys::KEY_LEFTBRACE)) {
        if (IsKeyDown(Keys::KEY_LEFTSHIFT))
            spawnObjID = max(0, (int)spawnObjID - 10);
        else
            spawnObjID = max(0, (int)spawnObjID - 1);
    }
    else if (IsKeyPressed(Keys::KEY_RIGHTBRACE)) {
        if (IsKeyDown(Keys::KEY_LEFTSHIFT))
            spawnObjID = min(ObjectSpawnCount - 1, (int)spawnObjID + 10);
        else
            spawnObjID = min(ObjectSpawnCount - 1, (int)spawnObjID + 1);
    }
    else {
        change = false;
    }
    if (change) {
        ObjectType spawnObjType = (ObjectType)0;
        int spawnObjIndex = 0;
        ResourceData* dummyResData = nullptr;
        unsigned int maxLevel = external::g_ObjectLevels_TABLE[(int)spawnObjType][spawnObjIndex];
        Game_GetObjectByName(ObjectSpawnList[spawnObjID], &spawnObjType, &spawnObjIndex, &dummyResData);
        spawnLevel = max(maxLevel, spawnLevel);
    }
    //float elapsed = *(float*)&dwElapsed;
    /*if (!updateCount) {
        logmsg("MyGameUpdate [first]\n");
        updateCount++;
    }*/
    if (g_origGameFunctions.Update != nullptr) {
        if (!g_origGameFunctions.Update(elapsed)) {
            logmsg("MyGameUpdate [internal failed]\n");
            return FALSE;
        }
    }

    if (liveObjMonitor.IsOpen()) {
        if (!liveObjMonitor.Update(elapsed, change /*force*/))
            return FALSE;
    }
    else if (IsKeyPressed(KEY_HOME)) {
        liveObjMonitor.Open();
    }

    /*lastUpdate += elapsed;
    if (g_hDlg != nullptr && (updateCount <= 1 || lastUpdate >= UPDATE_INTERVAL)) {
        if (updateCount == 1)
            logmsg("MyGameUpdate [second] [0x%08x]\n", (unsigned int)g_LiveObjects_POOL);

        lastUpdate = 0.0f;
        updateCount++;

        //return TRUE;
        char buffer[2048];
        unsigned int objCounts[21];
        std::memset(objCounts, 0, sizeof(objCounts));
        std::memset(buffer, 0, sizeof(buffer));
        unsigned int total = 0;
        bool enabled = ((*g_LiveObjects_INITFLAGS & 1) != 0) && (*g_LiveObjects_COUNT  >= 0 && *g_LiveObjects_COUNT <= 32) && *g_Game_level != nullptr;
        unsigned int capacity = 0;
        if (enabled) {
            for (unsigned int i = 0; i < *g_LiveObjects_COUNT; i++) {
                unsigned int curCount = (1 << i);
                capacity += curCount;
                for (unsigned int j = 0; j < curCount; j++) {
                    LiveObject* liveObj = &g_LiveObjects_POOL[i][j];
                    if (liveObj->pool_m_next != liveObj)
                        continue; // not alive

                    if ((int)liveObj->objType >= -1 && (int)liveObj->objType <= 19) {
                        total++;
                        objCounts[(int)liveObj->objType + 1]++;
                    }
                }
            }
        }
        //SendMessageA(g_hDlg, WM_SETREDRAW, (WPARAM)FALSE, (LPARAM)nullptr);

        if (enabled) {
            std::sprintf(buffer, "LiveObjects [ %6i / %6i ]", (int)total, (int)capacity);
        }
        else {
            std::sprintf(buffer, "LiveObjects [unused]");
        }
        HWND hCtrlLabel = GetDlgItem(g_hDlg, IDC_LABEL);
        SendMessageA(hCtrlLabel, WM_SETTEXT, (WPARAM)0, (LPARAM)buffer);

        HWND hCtrlListbox = GetDlgItem(g_hDlg, IDC_LISTBOX);
        while (SendMessageA(hCtrlListbox, LB_DELETESTRING //0x182
            , 0, 0) != -1);

        for (int i = -1; i <= 19; i++) {
            if (i == 0)
                continue;
            if (objCounts[i + 1] && enabled) {
                std::sprintf(buffer, "[%4i] : %s", (int)objCounts[i + 1], ObjectNames[i + 1]);
                for (int j = 1; j < 4 && buffer[j] != '\0'; j++) {
                    //if (buffer[j] == ' ')
                        //buffer[j] = '\xa0';
                }
            }
            else {
                std::sprintf(buffer, " ----  : %s", ObjectNames[i + 1]);
            }
            SendMessageA(hCtrlListbox, LB_ADDSTRING, (WPARAM)0, (LPARAM)buffer);
        }

        //SendMessageA(g_hDlg, WM_SETREDRAW, (WPARAM)TRUE, (LPARAM)nullptr);
    }*/

    return TRUE;
}

void __cdecl MyGameCleanup(void)
{
    logmsg("MyGameCleanup\n");
    if (liveObjMonitor.IsOpen())
        liveObjMonitor.Close();

    //if (g_hDlg != nullptr)
    //    EndDialog(g_hDlg, (INT_PTR)IDOK);

    if (g_origGameFunctions.Cleanup != nullptr)
        g_origGameFunctions.Cleanup();
}

// <LegoRR.exe @00478290>
BOOL __cdecl lego::game::SetGameFunctions(GameFunctions* gameFuncs)
{
    logmsg("SetGameFunctions\n");
    if (gameFuncs != nullptr) {
        g_origGameFunctions.Init = gameFuncs->Init;
        g_origGameFunctions.Update = gameFuncs->Update;
        g_origGameFunctions.Cleanup = gameFuncs->Cleanup;
        /*g_GameFunctions->Init = MyGameInit; // gameFuncs->Init;
        g_GameFunctions->Update = MyGameUpdate;// gameFuncs->Update;
        g_GameFunctions->Cleanup = MyGameCleanup;// gameFuncs->Cleanup;
        *g_GameFunctions_ISINIT = TRUE;*/
        g_GameFunctions.Init = MyGameInit; // gameFuncs->Init;
        g_GameFunctions.Update = MyGameUpdate;// gameFuncs->Update;
        g_GameFunctions.Cleanup = MyGameCleanup;// gameFuncs->Cleanup;
        g_GameFunctions_ISINIT = TRUE;
        return TRUE;
    }
    return FALSE;
}

// <LegoRR.exe @0044b400>
void __cdecl lego::game::Level_GenerateSmallSpiders(unsigned int x, unsigned int y, unsigned int randSeed)
{
    /*short sVar1;
    BOOL BVar2;
    LevelSurfaceMap* surfMap;
    LiveObject* pLVar3;
    int iVar4;
    float10 fVar5;
    Point2F* pPVar6;*/
    //Point2F genPos;
    //Point2F local_30;
    //Point2F local_18;

    ObjectType objType = ObjectType::None;
    int objIndex = 0;
    ResourceData* objRes = nullptr;
    const char* objTypeName = "SmallSpider";
    objTypeName = "Bat";
    objTypeName = "Pilot";
    objTypeName = ObjectSpawnList[spawnObjID];
    int objLevel = spawnLevel;

    //if (external::Game_GetObjectByName("SmallSpider", &objType, &objIndex, &objRes)) {
    if (external::Game_GetObjectByName(objTypeName, &objType, &objIndex, &objRes)) {
        //pPVar6 = &local_30;
        Point2F data[6];
        std::memset(data, 0, sizeof(data));
        external::FUN_00450390(external::GetSurfaceMap(), x, y, (void*)data);
        int randCount = 2 + (randSeed & 3); // range: [2,5]
        /// CUSTOM:
        //randCount += 4 + ((unsigned short)external::randomInt16() % 20);
        for (int i = randCount; i > 0; i--) {
            //int rngTheta = (int)external::randomInt16();
            // this is the laziest rounding for radians I've ever seen XD
            float genTheta = (float)((int)external::randomInt16() % 7);
            Point2F genPos = {
                external::Game_ChooseRandomRange(data[0].x + 1.0, data[3].x - 1.0),
                external::Game_ChooseRandomRange(data[0].y - 1.0, data[3].y + 1.0)
            };
            //genPos.x = external::Game_ChooseRandomRange(data[0].x + 1.0, data[3].x - 1.0);
            //genPos.y = external::Game_ChooseRandomRange(data[0].y - 1.0, data[3].y + 1.0);
            //genPos.x = external::Game_ChooseRandomRange(local_30.x - -1.0, local_18.x - 1.0);
            //genPos.y = external::Game_ChooseRandomRange(local_30.y - 1.0, local_18.y - -1.0);
            //LiveObject* spider = external::Game_CreateLiveResourceObject(objRes, objType, objIndex, 0 /*lv0*/, genPos.x, genPos.y, genTheta);
            LiveObject* spider = external::Game_CreateLiveResourceObject(objRes, objType, objIndex, objLevel /*lv0*/, genPos.x, genPos.y, genTheta);
            spider->flags1_3e0 |= (LiveFlags1)0x10000;
        }
    }
    return; // may return last spider, but never used
}

#pragma endregion
