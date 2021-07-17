// Main.cpp : Defines the entry point for the application.
//

#include "Main.h"
#include "ModeSelection.h"
#include "GameHook.h"
#include "../Drawing/DirectDraw.h"
#include "../Helpers/Registry.h"
#include "../Helpers/Utils.h"

#include "../IO/Files.h"
#include "../Controls/Input.h"

#ifndef DEBUG_REMOVEUNUSED
#include "../Audio/AVI.h"
#include "../Audio/Sound.h"
#include "../IO/CFG.h"
#include "../Drawing/SurfaceLock.h"
#endif


#pragma region Defines

#define s_Dev_SourceSafe__Main_c "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Main.c"

#pragma endregion


#pragma region Globals
namespace lego {
namespace main {
namespace globals {

    // [INCLUSIVE]: WinMain functions, Input.c function, GetDeviceBitsPerPixel
    // <LegoRR.exe @00506800>
    HWND g_hWnd;
    // [INCLUSIVE]: WinMain, ChooseScreenMode, Input.c function
    // <LegoRR.exe @00506804>
    HINSTANCE g_hInstance;
    // [INCLUSIVE]: WinMain functions, Input.c function
    // <LegoRR.exe @00506808>
    BOOL g_IsFocused;
    // [EXCLUSIVE]: WinMain, GameWindowProc functions
    // <LegoRR.exe @0050680c>
    BOOL g_IsClosing;
    // [EXCLUSIVE]: WinMain, CreateMainWindow
    // <LegoRR.exe @00506810>
    const char* g_WindowClassName;
    // [EXCLUSIVE]: WinMain
    // <LegoRR.exe @00506814>
    char g_ExeName[256];

    // [UNKNOWN]:
    // <LegoRR.exe @00506914>
    IDirect3DRM3* g_IDirect3DRM3;
    // [UNKNOWN]:
    // <LegoRR.exe @00506918>
    IDirect3DRMDevice3* g_IDirect3DRMDevice3;
    // [UNKNOWN]:
    // <LegoRR.exe @0050691c>
    IDirect3DDevice3* g_IDirect3DDevice3;
    // D3DRMFOGMETHOD_VERTEX = 0x1,
    // D3DRMFOGMETHOD_TABLE  = 0x2,
    // D3DRMFOGMETHOD_ANY    = 0x4,
    // [EXCLUSIVE]: Direct3DRMCreate, SetRootSceneFodMode
    // <LegoRR.exe @00506920>  XREF[3]
    unsigned int g_SceneFogMethod;
    // [INCLUSIVE]:
    // <LegoRR.exe @00506924>  XREF[15,12=27]
    Size2I g_RESOLUTION;
    // [EXCLUSIVE]: WinMain, SetGameFunctions
    // <LegoRR.exe @0050692c>  XREF[3,7]
    GameFunctions g_GameFunctions;
    // [EXCLUSIVE]: WinMain, SetGameFunctions
    // <LegoRR.exe @00506938>  XREF[3]
    BOOL g_GameFunctions_ISINIT;
    // [INCLUSIVE]:
    // <LegoRR.exe @0050693c>  XREF[5]
    float g_FPSLOCK_VSYNC;
    // [EXCLUSIVE]: SetRenderState, Cleanup(Update?)RenderStates
    // <LegoRR.exe @00506940>  XREF[3,7]
    RenderStateItem g_RenderStates_TABLE[200];
    // <LegoRR.exe @00506f80>  XREF[3]
    // [EXCLUSIVE]: AdjustGameWindowedRect, ShowGameWindow
    DWORD g_WindowStyle;
    /*
    // [INCLUSIVE]:
    // <LegoRR.exe @00506f84>  XREF[82]
    CmdlineFlags g_CMDLINE_FLAGS;
    // [INCLUSIVE/ACCESSOR]: ParseCmdFlags, WinMain functions, game functions, GetProgrammerMode (accessor)
    // <LegoRR.exe @00506f88>  XREF[17]
    ProgrammerMode g_PROGRAMMER_MODE;
    // [EXCLUSIVE/ACCESSOR]: ParseCmdFlags, GetStartLevel (accessor)
    // <LegoRR.exe @00506f8c>  XREF[3,1]
    char g_STARTLEVEL[256];
    // [EXCLUSIVE/ACCESSOR]: ParseCmdFlags, GetDebugFlags (accessor)
    // <LegoRR.exe @0050708c>  XREF[2]
    DebugFlags g_DEBUG_FLAGS; // 0x8000 (block fade)
    */

    // <LegoRR.exe @0054155c>
    unsigned int COUNT_0054155c;
    // <LegoRR.exe @00541560>
    unsigned int COUNT_00541560;
    // <LegoRR.exe @00541564>
    DWORD g_Direct3D_TextureHandle_New;
    // <LegoRR.exe @00541568>
    DWORD g_Direct3D_LightState_New;
    // <LegoRR.exe @0054156c>
    IDirect3DTexture2* g_IDirect3DTexture2_New;
    // <LegoRR.exe @00541570>
    DWORD g_Direct3D_TextureHandle_Old;
    // <LegoRR.exe @00541574>
    DWORD g_Direct3D_LightState_Old;
    // <LegoRR.exe @00541578>
    IDirect3DTexture2* g_IDirect3DTexture2_Old;
    // <LegoRR.exe @0054157c>
    DWORD g_Direct3D_MaterialHandle;
    // <LegoRR.exe @00541580>
    IDirect3DMaterial3* g_IDirect3DMaterial3;
    // <LegoRR.exe @00541584>
    //ReservedPool<Struct_34> start

    // <LegoRR.exe @005774f4>
    static BOOL g_IsFullScreen;
} /* namespace globals */
} /* namespace main */
} /* namespace lego */
#pragma endregion


using namespace lego;
using namespace lego::main;


#pragma region WinMain (namespace wrapper)

// <LegoRR.exe @00477a60>
int APIENTRY WinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPSTR     lpCmdLine,
                     _In_ int       nCmdShow)
{
    // namespace wrapper?
    return lego::main::WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

#pragma endregion

#pragma region WinMain (real)

// <LegoRR.exe @00477a60>
int APIENTRY lego::main::WinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPSTR     lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);

    char mutexName[1024];
    char fullCmdLine[1024];
    char errorMessage[1024];
    char standardParameters[1024];

    /// DEBUG:
    CoInitialize(nullptr);


    BOOL nosound = FALSE, insistOnCD = FALSE;

    if (USEMUTEX /*true*/) {
        std::sprintf(mutexName, "%s Mutex", MUTEX_NAME /*"Lego Rock Raiders (Mode Selection)"*/);
        CreateMutexA(nullptr, TRUE, mutexName);
        if (GetLastError() == ERROR_ALREADY_EXISTS /*0xb7*/)
            return FALSE;
    }


    char* cmdLine = GetCommandLineA();
    debugf("%s\n", cmdLine);
    char* exeName = cmdLine;
    for (char* cmdPtr = cmdLine; *cmdPtr != '\0'; cmdPtr++) {
        if (*cmdPtr == '\\')
            exeName = cmdPtr + 1; // name after '\\' path separator
    }
    std::strcpy(globals::g_ExeName, exeName);
    // zero-out double quote '\"' characters (hopefully it's impossible for it to start with a quote character)
    for (char* exePtr = globals::g_ExeName; *exePtr != '\0'; exePtr++) {
        if (*exePtr == '\"')
            *exePtr = '\0';
    }
    // find the last '.' for file extension
    char* exeExtension = globals::g_ExeName;
    for (char* exePtr = globals::g_ExeName; *exePtr != '\0'; exePtr++) {
        if (*exePtr == '.')
            exeExtension = exePtr + 1;
    }
    if (exeExtension != globals::g_ExeName) {
        _strupr(exeExtension); // to upper
        exeExtension = std::strstr(globals::g_ExeName, ".EXE");
        if (exeExtension != nullptr) {
            // separate executable name from extension,
            // this name without extension will be the basis for many constant lookups
            *exeExtension = '\0';
        }
    }


    globals::g_WindowClassName = globals::g_ExeName; // "LegoRR";
    globals::g_IsFocused = FALSE;
    globals::g_IsClosing = FALSE;
    globals::g_GameFunctions_ISINIT = FALSE;
    globals::g_hInstance = hInstance;
    globals::g_FPSLOCK_VSYNC = 0.0f;
    lego::globals::g_CMDLINE_FLAGS = CMD_NONE /*0*/;

    // Add StandardParameters to command line arguments, then parse command line arguments
    BOOL regResult = registry::QueryValueOnLocalMachine("SOFTWARE\\LEGO Media\\Games\\Rock Raiders", "StandardParameters", registry::REGISTRY_STRING /*0*/, standardParameters, sizeof(standardParameters));
    if (regResult && !IGNORESTANDARDPARAMETERS) {
        std::sprintf(fullCmdLine, "%s %s", lpCmdLine, standardParameters);
    }
    else {
        std::sprintf(fullCmdLine, "%s", lpCmdLine);
    }
    ParseCmdlineFlags(fullCmdLine, &nosound, &insistOnCD);


    regResult = registry::QueryValueOnLocalMachine("SOFTWARE\\LEGO Media\\Games\\Rock Raiders", "NoHALMessage", registry::REGISTRY_STRING /*0*/, errorMessage, sizeof(errorMessage));
    if (!regResult) {
        std::sprintf(errorMessage, "No DirectX 3D accelerator could be found.");
    }

    #ifndef DEBUG_REMOVEUNUSED
    file::InitFileScanning();
    #endif

    file::InitSharedFileBuffers();
    file::InitFileSystem(globals::g_ExeName, insistOnCD, "SOFTWARE\\LEGO Media\\Games\\Rock Raiders");

    #ifndef DEBUG_REMOVEUNUSED
    CFG::Pool.Init();
    #endif

    input::InitDirectInput();

    if (!CreateMainWindow(hInstance, nCmdShow))
        goto WinMain_Cleanup;


    draw::InitDirectDraw(globals::g_hWnd);
    #ifndef DEBUG_REMOVEUNUSED
    sound::InitSoundSystem(nosound);
    #endif

    if (!dialog::ChooseScreenMode(TRUE /*showDialog*/, // likely preprocessor-defined
                                lego::globals::g_CMDLINE_FLAGS & CMD_DEBUG  /*isDebug*/,
                                lego::globals::g_CMDLINE_FLAGS & CMD_BEST   /*isBest*/,
                                lego::globals::g_CMDLINE_FLAGS & CMD_WINDOW /*isWindow*/,
                                errorMessage))
    {
        debugf("FAILED: ChooseScreenMode\n");
        goto WinMain_DestroyWindow;
    }

    #ifndef DEBUG_REMOVEUNUSED
    avi::InitAVIFile(draw::globals::g_IDirectDraw4); // DAT_0076bc84
    draw::Draw_SurfaceLockRect(nullptr);
    #endif

    game::InitGameFunctions(globals::g_ExeName);
    if (!globals::g_GameFunctions_ISINIT) {
        debugf("FAILED: SetGameFunctions\n");
        goto WinMain_DestroyWindow;
    }

    #pragma region ////// INIT / LOOP / CLEANUP //////

    if (globals::g_GameFunctions.Init != nullptr) {
        ////// GAME INIT //////
        if (!globals::g_GameFunctions.Init()) {
            debugf("FAILED: g_GameFunctions.Init()\n");
            globals::g_GameFunctions.Init    = nullptr;
            globals::g_GameFunctions.Update  = nullptr;
            globals::g_GameFunctions.Cleanup = nullptr;
            goto WinMain_DestroyWindow; // (optional, control flow already takes us there)
        }
    }
    else {
        debugf("FAILED: g_GameFunctions.Init == nullptr\n");
    }

    if (globals::g_GameFunctions.Update != nullptr) {
        float ellapsed = 1.0f; // ellapsed game time units since last update
        unsigned int lastTime = timeGetTime();

        ////// GAME LOOP //////
        while (!globals::g_IsClosing) {
            input::globals::BOOL_0076bb4c = 0;
            input::globals::BOOL_0076bb50 = 0;
            input::globals::BOOL_0076bb54 = 0;
            input::globals::g_RightButtonDoubleClicked = 0;
            HandleMessageQueue();

            if (lego::globals::g_CMDLINE_FLAGS & CMD_FULLSCREEN)
                globals::g_IsFocused = TRUE;

            input::UpdateKeyboardState();
            input::UpdateMousePosition();

            if (!globals::g_GameFunctions.Update(ellapsed)) {
                debugf("FAILED: g_GameFunctions.Update(float)\n");
                globals::g_IsClosing = TRUE;
            }
            
            #ifndef DEBUG_REMOVEUNUSED
            UpdateDirect3DRM();
            #endif
            draw::Render();

            lego::globals::g_CMDLINE_FLAGS &= ~CMD_D3DRMUPDATED /*~0x1*/ /*0xfffffffe*/;
            if (lego::globals::g_CMDLINE_FLAGS & CMD_FPSLOCK30) {
                ellapsed = (25.0f / 30.0f) /*0.8333333f*/;
            }
            else if (lego::globals::g_CMDLINE_FLAGS & CMD_NOFPSLOCK) {
                ellapsed = 0.0;
                lastTime = timeGetTime();
            }
            else if (globals::g_FPSLOCK_VSYNC != 0.0f) {
                ellapsed = globals::g_FPSLOCK_VSYNC;
                lastTime = timeGetTime();
            }
            else {
                unsigned int currentTime = timeGetTime();

                ellapsed = (float)(unsigned long long)(currentTime - lastTime) * 0.025f /*(25.0f / 1000.0f)*/;
                lastTime = currentTime;
                // // what the hell is this??
                // if ((ushort)((ushort)(fpsSync < 3.0) << 8 | (ushort)(fpsSync == 3.0) << 0xe) == 0) {
                // 	fpsSync = 3.0;
                // }
                // REAALLLY!???
                if (ellapsed > 3.0f)
                    ellapsed = 3.0f;
            }
        }
    }
    else {
        debugf("FAILED: g_GameFunctions.Update == nullptr\n");
    }

    if (globals::g_GameFunctions.Cleanup != nullptr) {
        ////// GAME CLEANUP //////
        globals::g_GameFunctions.Cleanup();
    }
    else {
        debugf("FAILED: g_GameFunctions.Cleanup == nullptr\n");
    }

    #pragma endregion


WinMain_DestroyWindow:
    draw::CleanupDirectDraw();
    DestroyWindow(globals::g_hWnd);

WinMain_Cleanup:
    input::CleanupDirectInput();

    #ifndef DEBUG_REMOVEUNUSED
    CFG::Pool.Cleanup();
    #endif

    //other::logf_removed(nullptr);

    #ifndef DEBUG_REMOVEUNUSED
    file::Scan_Cleanup();
    file::Scan_WriteDataDirList();
    #endif

    /// DEBUG:
    CoUninitialize();

    return 0;
}

#pragma endregion


#pragma region Functions

// Assigns the CMD_NM flag to g_CMDLINE_FLAGS if CMD_FTM is not set.
//  (CMD_FTM is generally supposed to be set for Voodoo2)
// <LegoRR.exe @00477e90>
void __cdecl lego::main::DisableTextureManagement_NonVoodoo2(void)
{
    if (!(lego::globals::g_CMDLINE_FLAGS & CMD_FTM))
        lego::globals::g_CMDLINE_FLAGS |= CMD_NM;
}

// <LegoRR.exe @00477eb0>
void __cdecl lego::main::ParseCmdlineFlags(const char* args, BOOL* out_nosound, BOOL* out_insistOnCD)
{
    // Output settings
    if (lego::util::strstri(args, "-insistOnCD"))
        *out_insistOnCD = TRUE;

    if (lego::util::strstri(args, "-nosound"))
        *out_nosound = TRUE;

    // Flags
    if (lego::util::strstri(args, "-debug"))
        lego::globals::g_CMDLINE_FLAGS |= CMD_DEBUG;

    if (lego::util::strstri(args, "-nm")) // "no texture management"
        lego::globals::g_CMDLINE_FLAGS |= CMD_NM;

    if (lego::util::strstri(args, "-ftm")) // graphical option
        lego::globals::g_CMDLINE_FLAGS |= CMD_FTM;

    if (lego::util::strstri(args, "-fvf")) // graphical option
        lego::globals::g_CMDLINE_FLAGS |= CMD_FVF;

    if (lego::util::strstri(args, "-best")) // "best fit" (first screen mode, last driver, last device)
        lego::globals::g_CMDLINE_FLAGS |= CMD_BEST;

    if (lego::util::strstri(args, "-window")) // "windowed mode"
        lego::globals::g_CMDLINE_FLAGS |= CMD_WINDOW; // Only used in unison "-best" argument

    if (lego::util::strstri(args, "-dualmouse"))
        lego::globals::g_CMDLINE_FLAGS |= CMD_DUALMOUSE;

    // This argument will also trigger "-debug", because there's no checking for whitespace after the match
    // (this may be intentional)
    if (lego::util::strstri(args, "-debugcomplete"))
        lego::globals::g_CMDLINE_FLAGS |= CMD_DEBUGCOMPLETE;

    if (lego::util::strstri(args, "-testercall")) {
        lego::globals::g_PROGRAMMER_MODE = PROGRAMMER_MODE_2 /*2*/;
        lego::globals::g_CMDLINE_FLAGS |= CMD_TESTERCALL;
    }

    if (lego::util::strstri(args, "-testlevels"))
        lego::globals::g_CMDLINE_FLAGS |= CMD_TESTLEVELS;

    if (lego::util::strstri(args, "-reducesamples"))
        lego::globals::g_CMDLINE_FLAGS |= CMD_REDUCESAMPLES;

    if (lego::util::strstri(args, "-showversion"))
        lego::globals::g_CMDLINE_FLAGS |= CMD_SHOWVERSION;

    if (lego::util::strstri(args, "-reduceanimation"))
        lego::globals::g_CMDLINE_FLAGS |= CMD_REDUCEANIMATION;

    if (lego::util::strstri(args, "-reducepromeshes"))
        lego::globals::g_CMDLINE_FLAGS |= CMD_REDUCEPROMESHES;

    if (lego::util::strstri(args, "-reduceflics"))
        lego::globals::g_CMDLINE_FLAGS |= CMD_REDUCEFLICS;

    if (lego::util::strstri(args, "-reduceimages"))
        lego::globals::g_CMDLINE_FLAGS |= CMD_REDUCEIMAGES;

    // (moved, originally at bottom of function)
    if (lego::util::strstri(args, "-cleansaves"))
        lego::globals::g_CMDLINE_FLAGS |= CMD_CLEANSAVES;


    // Fields
    const char* strfind;
    strfind = lego::util::strstri(args, "-startlevel"); // "-startlevel <Levels::Name>"
    if (strfind) {
        strfind += (sizeof("-startlevel") - 1); // skip length of "-startlevel" (no spaces)

        // skip whitespace
        while (*strfind != '\0' && *strfind == ' ')
            strfind++;

        // read non-whitespace into start level buffer
        int length = 0;
        while (*strfind != '\0' && *strfind != ' ')
            lego::globals::g_STARTLEVEL[length++] = *strfind++;
        
        lego::globals::g_STARTLEVEL[length] = '\0'; // null-terminate buffer
        lego::globals::g_CMDLINE_FLAGS |= CMD_STARTLEVEL;
    }

    strfind = lego::util::strstri(args, "-flags"); // "-fpslock <integer>"
    if (strfind) {
        // debug flags are in decimal... terrifying...
        // skip length of "-flags" (no spaces), atoi skips whitespace on its own
        lego::globals::g_DEBUG_FLAGS = (DebugFlags)std::atoi(strfind + (sizeof("-flags") - 1));
    }

    strfind = lego::util::strstri(args, "-fpslock"); // "-fpslock <integer>"
    if (strfind) {
        // skip length of "-fpslock" (no spaces), atoi skips whitespace on its own
        unsigned int fpslock = (unsigned int)std::atoi(strfind + 8);
        if (fpslock != 0) { // parse failed or 0, don't divide by 0 dummy!
            // 25.0f is the default "time unit" for the game, or something like that, see the header of Lego.cfg for more info
            globals::g_FPSLOCK_VSYNC = 25.0f / (float)(unsigned long long)fpslock;
        }
    }

    strfind = lego::util::strstri(args, "-programmer"); // "-programmer [integer]"
    if (strfind) {
        lego::globals::g_PROGRAMMER_MODE = (ProgrammerMode)std::atoi(strfind + (sizeof("-programmer") - 1));
        // skip length of "-programmer" (no spaces), atoi skips whitespace on its own
        if (lego::globals::g_PROGRAMMER_MODE == 0) // parse failed or 0, set to 1 as default 'mode'
            lego::globals::g_PROGRAMMER_MODE = PROGRAMMER_MODE_1 /*1*/;
    }
    else {
        lego::globals::g_PROGRAMMER_MODE = PROGRAMMER_OFF /*0*/; // mode when "-programmer" not specified
    }
}


// <LegoRR.exe @004781f0>
void __cdecl lego::main::UpdateAndRender(BOOL doFillSurface)
{
    HandleMessageQueue();
    input::UpdateKeyboardState();
    input::UpdateMousePosition();
    UpdateDirect3DRM();
    draw::Render();

    if (doFillSurface)
        draw::FillSurface(nullptr, 0 /*rgb black*/);

    lego::globals::g_CMDLINE_FLAGS &= ~CMD_D3DRMUPDATED;
}

/*
// <LegoRR.exe @00478230>
DebugFlags __cdecl lego::main::GetDebugFlags(void)
{
    return lego::globals::g_DEBUG_FLAGS;
}
*/

// <LegoRR.exe @00478240>
int __cdecl lego::main::GetDeviceBitsPerPixel(void)
{
    HDC hdc = GetDC(globals::g_hWnd);
    return GetDeviceCaps(hdc, BITSPIXEL /*0xc*/);
}

// <LegoRR.exe @00478260>
void __cdecl lego::main::UpdateDirect3DRM(void)
{
    if (!(lego::globals::g_CMDLINE_FLAGS & CMD_D3DRMUPDATED)) {
        globals::g_IDirect3DRMDevice3->Update();
        lego::globals::g_CMDLINE_FLAGS |= CMD_D3DRMUPDATED;
    }
}

// <LegoRR.exe @00478290>
BOOL __cdecl lego::main::SetGameFunctions(GameFunctions* gameFuncs)
{
    if (gameFuncs != nullptr) {
        globals::g_GameFunctions.Init    = gameFuncs->Init;
        globals::g_GameFunctions.Update  = gameFuncs->Update;
        globals::g_GameFunctions.Cleanup = gameFuncs->Cleanup;
        globals::g_GameFunctions_ISINIT  = TRUE;
        return TRUE;
    }
    return FALSE;
}


// <https://wiki.winehq.org/List_Of_Windows_Messages>
// Why is Microsoft SO BAD at making constants easily available and accessible!!??
//
// When focus is taken away by another window:
// WM_ACTIVATEAPP (0x001c): <https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-activateapp>
// 
// when F10 or Alt+_ key combo is pressed:
// WM_SYSKEYDOWN  (0x0104): <https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-syskeydown>
// WM_SYSKEYUP    (0x0105): <https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-syskeyup>
// 
// 
// <LegoRR.exe @004782d0>
BOOL __cdecl lego::main::ShouldHandleMessage(MSG* msg)
{
    if (lego::globals::g_CMDLINE_FLAGS & CMD_FULLSCREEN) {
        //unsigned int wm = msg->message;
        if (msg->message == WM_ACTIVATEAPP /*0x1c*/ || msg->message == WM_SYSKEYDOWN /*0x104*/ || msg->message == WM_SYSKEYUP /*0x105*/)
            return FALSE;
    }
    return TRUE;
}

// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-peekmessagea>
// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-translatemessage>
// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-dispatchmessagea>

// <LegoRR.exe @00478300>
void __cdecl lego::main::HandleMessageQueue(void)
{
    MSG msg;
    while (PeekMessageA(&msg, nullptr, 0, 0, 1)) {
        if (ShouldHandleMessage(&msg)) {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
    }
}


// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowlonga>
// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow>
// 
// <LegoRR.exe @00478370>
void __cdecl lego::main::ShowGameWindow(BOOL isFullScreen, int x, int y, int width, int height)
{
    //SetGameWindowTitle("YES YES YES");
    globals::g_RESOLUTION.width = width;
    globals::g_RESOLUTION.height = height;
    if (isFullScreen)
        lego::globals::g_CMDLINE_FLAGS |= CMD_FULLSCREEN;


    file::Scan_SetIsFullScreen(isFullScreen);

    if (!isFullScreen) {
        RECT rect = { x, y, (width + x), (height + y) };
        //rect.left = x;
        //rect.top = y;
        //rect.right = width + x;
        //rect.bottom = height + y;
        //              /* WS_POPUPWINDOW | WS_CAPTION (0x80880000 | 0xc00000)*/
        //                         /* WS_CAPTION  0xc00000*/
        // g_WindowStyle = WS_POPUP | WS_BORDER | WS_DLGFRAME | WS_SYSMENU /*0x80c80000 = 0x80000000 | 0x800000 | 0x400000 | 0x80000*/;
        globals::g_WindowStyle = WS_POPUPWINDOW | WS_CAPTION /*0x80880000 | 0xc00000*/;
        AdjustMainWindowedRect(&rect);
        SetWindowLongA(globals::g_hWnd, GWL_STYLE /*-16*/, globals::g_WindowStyle);
        SetWindowPos(globals::g_hWnd, HWND_TOP /*0x0*/,
            rect.left, rect.top,
            rect.right - rect.left,
            rect.bottom - rect.top,
            SWP_NOZORDER /*0x4*/);
        ShowCursor(SHOWCURSOR /*FALSE*/);
    }
    else {
        HWND hDesktopWnd = GetDesktopWindow();
        RECT rect;
        GetWindowRect(hDesktopWnd, &rect);
        SetWindowPos(globals::g_hWnd, HWND_TOP /*0x0*/,
            rect.left, rect.top,
            rect.right - rect.left,
            rect.bottom - rect.top,
            SWP_NOZORDER /*0x4*/);

        #if SHOWCURSOR
        ShowCursor(SHOWCURSOR);
        #else
        SetCursor(nullptr);
        #endif
    }
    ShowWindow(globals::g_hWnd, SW_SHOW /*5*/);
    SetActiveWindow(globals::g_hWnd);
}


// <LegoRR.exe @00478490>
BOOL __cdecl lego::main::InitDirect3DRM(draw::DeviceMode* device, IDirectDraw* ddraw1, IDirectDrawSurface4* ddSurface, BOOL isFullScreen)
{
	if (device != nullptr && (device->flags & draw::DEVICEMODE_TEXTUREVIDEOMEMORY)) {
		lego::globals::g_CMDLINE_FLAGS |= CMD_TEXTUREVIDEOMEMORY;
	}

	if (lego::globals::g_CMDLINE_FLAGS & CMD_FVF) {
		globals::g_SceneFogMethod = 2;
		if (!(device->flags & draw::DEVICEMODE_HARDWARE)) {
			globals::g_SceneFogMethod = 1;
		}
	}
	/*IUnknown*/ IDirect3DRM* d3dRM;
	if (Direct3DRMCreate(&d3dRM) == 0) {
		if (d3dRM->QueryInterface(IID_IDirect3DRM3, (void**)&globals::g_IDirect3DRM3) == 0) {

			IDirectDrawSurface* ddSurface1 = NULL; // dummy init
			if (ddSurface->QueryInterface(IID_IDirectDrawSurface, (void**)&ddSurface1) != 0)
				debugf("FAILED: QueryInterface IID_IDirectDrawSurface\n");

			if (globals::g_IDirect3DRM3->CreateDeviceFromSurface(&device->guid, ddraw1, ddSurface1, 0,
				&globals::g_IDirect3DRMDevice3) == 0)
			{
				IDirect3DDevice2* d3dDevice2 = NULL; // dummy init
				globals::g_IDirect3DRMDevice3->GetDirect3DDevice2(&d3dDevice2);

				d3dDevice2->QueryInterface(IID_IDirect3DDevice3, (void**)&globals::g_IDirect3DDevice3);
				//if (lego::globals::g_IDirect3DDevice3 != nullptr)
				if (isFullScreen)
					globals::g_IDirect3DRMDevice3->SetBufferCount(2);

				return TRUE;
			}
			debugf("FAILED: g_IDirect3DRM3->CreateDeviceFromSurface\n");
			// (* Create a Windows Device using DirectDraw surfaces *)
			//function CreateDeviceFromSurface(lpGUID: PGUID; lpDD: IDirectDraw;
			// lpDDSBack: IDirectDrawSurface; var lplpD3DRMDevice : IDirect3DRMDevice3)
		}
		debugf("FAILED: QueryInterface IID_IDirect3D3\n");
		//report error hresult
	}
	debugf("FAILED: Direct3DRMCreate\n");
	//if hresult != 0 report error hresult
	return FALSE;

	/*HRESULT HVar1;
	DeviceMode* result;
	DeviceMode* pDVar2;
	code*** ppvObject;
	DeviceMode** ppDVar3;
	IUnknown* local_8;
	code** local_4;

	pDVar2 = (DeviceMode*)0x0;
	if ((device != (DeviceMode*)0x0) &&
		(pDVar2 = device, (device->flags & DEVICEMODE_TEXTUREVIDEOMEMORY) != DEVICEMODE_NONE)) {
		globals::g_CMDLINE_FLAGS |= 4;
	}
	if (((globals::g_CMDLINE_FLAGS & CMD_FVF) != CMD_NONE) ||
		(g_SceneFogMethod = 2, (device->flags & DEVICEMODE_HARDWARE) == DEVICEMODE_NONE)) {
		g_SceneFogMethod = 1;
	}
	HVar1 = Direct3DRMCreate(&local_8);
	result = device;
	if ((HVar1 == 0) &&
		(HVar1 = (*local_8->QueryInterface(IID_IDirect3DRM3, &lego::globals::g_IDirect3DRM3),
			result = device, HVar1 == 0))) {
		ppvObject = &local_4;
		ddSurface->QueryInterface(IID_IDirectDrawSurface, ppvObject);
		result = (DeviceMode*)
			lego::globals::g_IDirect3DRM3->CreateDeviceFromSurface(pDVar2, local_4, ppvObject, 0,
				&globals::g_IDirect3DRMDevice3);
		if (result == (DeviceMode*)0x0) {
			ppDVar3 = &device;
			lego::globals::g_IDirect3DRMDevice3->GetDirect3DDevice2(globals::g_IDirect3DRMDevice3);
			(**(code**)*local_4)
				(local_4, &directx::iid::IID_IDirect3DDevice3, &globals::g_IDirect3DDevice3);
			(**(code**)((*ppDVar3)->guid).Data4)(ppDVar3);
			if (local_8 != (IUnknown*)0x0) {
				(*(code*)globals::g_IDirect3DRMDevice3->SetBufferCount)
					(globals::g_IDirect3DRMDevice3, 2);
			}
			return 1;
		}
		directx::DirectX_Error
		((HRESULT)result, 3, "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Main.c", 568);
	}
	if (result != (DeviceMode*)0x0) {
		directx::DirectX_Error
		((HRESULT)result, 1, "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Main.c", 576);
	}
	return 0;*/
}


// <LegoRR.exe @004785d0>
void __cdecl lego::main::AdjustMainWindowedRect(RECT* lpRect)
{
    if (!(lego::globals::g_CMDLINE_FLAGS & CMD_FULLSCREEN)) { // not fullscreen
        AdjustWindowRect(lpRect, globals::g_WindowStyle, FALSE);
    }
}

// <LegoRR.exe @004785f0>
void __cdecl lego::main::SetGraphicsQuality(GraphicsQuality quality, BOOL dither, BOOL filter, BOOL mipmap, BOOL linearmipmap, BOOL blend, BOOL sort)
{
    D3DRMRENDERQUALITY renderQuality;
    D3DRMTEXTUREQUALITY textureQuality;

    // D3DRMRENDER_WIREFRAME 0x40 (D3DRMSHADE_FLAT|D3DRMLIGHT_OFF|D3DRMFILL_WIREFRAME)
    renderQuality = D3DRMRENDER_WIREFRAME /*0x40*/;
    if (quality == QUALITY_FLAT) {
        // D3DRMRENDER_FLAT 0x88 (D3DRMSHADE_FLAT|D3DRMLIGHT_ON|D3DRMFILL_SOLID)
        renderQuality = D3DRMRENDER_FLAT /*0x88*/;
    }
    else if (quality == QUALITY_UNLITFLAT) {
        // D3DRMRENDER_UNLITFLAT 0x80 (D3DRMSHADE_FLAT|D3DRMLIGHT_OFF|D3DRMFILL_SOLID)
        renderQuality = D3DRMRENDER_UNLITFLAT /*0x80*/;
    }
    else if (quality == QUALITY_GOURAUD) {
        // D3DRMRENDER_GOURAUD 0x89 (D3DRMSHADE_GOURAUD|D3DRMLIGHT_ON|D3DRMFILL_SOLID)
        renderQuality = D3DRMRENDER_GOURAUD /*0x89*/;
    }

    if (!filter) {
        textureQuality = D3DRMTEXTURE_NEAREST /*0*/;
    }
    else if (!mipmap) {
        textureQuality = D3DRMTEXTURE_LINEAR /*1*/;
    }
    else {
        //textureQuality = (-(linearmipmap != 0) & 2U) + 3;
        if (!linearmipmap) {
            textureQuality = D3DRMTEXTURE_MIPLINEAR /*3*/;
        }
        else {
            textureQuality = D3DRMTEXTURE_LINEARMIPLINEAR /*5*/;
        }
        lego::globals::g_CMDLINE_FLAGS |= CMD_MIPMAP;
    }
    
    if (globals::g_IDirect3DRMDevice3 != nullptr) {
        globals::g_IDirect3DRMDevice3->SetDither(dither);
        globals::g_IDirect3DRMDevice3->SetQuality(renderQuality);
        globals::g_IDirect3DRMDevice3->SetTextureQuality(textureQuality);
    }
}

// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowtexta>
// 
// <LegoRR.exe @00478690>
BOOL __cdecl lego::main::SetMainWindowTitle(const char* title)
{
    return SetWindowTextA(globals::g_hWnd, title);
}

// <LegoRR.exe @004786b0>
BOOL __cdecl lego::main::CreateMainWindow(HINSTANCE hInstance, int nCmdShow)
{
    WNDCLASSA wc;
    std::memset(&wc, 0, sizeof(wc));

    wc.style            = CS_DBLCLKS; //CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc      = WindowProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = hInstance;
    wc.hIcon            = LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_MAINICON)); // nullptr;
    wc.hCursor          = nullptr; //LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground    = nullptr; //(HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName     = nullptr; //MAKEINTRESOURCEW(IDC_MODESELECTION);
    wc.lpszClassName    = globals::g_WindowClassName;

    ATOM atom = RegisterClassA(&wc);
    if (!atom) {
        MessageBoxA(nullptr, "Unable to register window class", "Fatal Error", MB_OK /*0*/);
        return FALSE;
    }
    globals::g_hWnd = CreateWindowExA(WS_EX_APPWINDOW,
                                     globals::g_WindowClassName,
                                     ""/*EMPTYSTR*/,
                                     WS_POPUP | WS_SYSMENU,
                                     0, 0, 100, 100,
                                     nullptr, nullptr,
                                     hInstance, nullptr);

    if (!globals::g_hWnd) {
        MessageBoxA(nullptr, "Unable to Create Main Window", "Fatal Error", MB_OK /*0*/);
        return FALSE;
    }

    SetFocus(globals::g_hWnd);
    return TRUE;
}


#pragma region WindowProc
#pragma region WindowProc (FullScreen)

// <LegoRR.exe @00478780>
LRESULT __cdecl lego::main::WindowProc_FullScreen(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_MOVE:
    case WM_SIZE:
    case WM_ACTIVATE:
    case WM_NCACTIVATE:
    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYDOWN:
    case WM_MOUSEMOVE:
    case WM_ENTERMENULOOP:
    case WM_EXITMENULOOP:
        return 0;

    case WM_WINDOWPOSCHANGING:
        /// DIFFERENCE: No `WM_WINDOWPOSCHANGING` in Windowed
        *(unsigned int*)((unsigned char*)lParam + 0x18) &= ~0x200 /*0xfffffdff*/;
        return 0;

    case WM_ACTIVATEAPP:
        // TRUE if this window is being activated
        globals::g_IsFocused = (BOOL)wParam;
        return 0;

    case WM_DESTROY:
    case WM_CLOSE:
    case WM_QUIT:
        globals::g_IsClosing = TRUE;
        return 0;

    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
        if (!(lego::globals::g_CMDLINE_FLAGS & CMD_DUALMOUSE)) {
            // surrounded by an if (true) {}, probably a preprocessor
            switch (message) {
            case WM_LBUTTONDOWN:
            case WM_RBUTTONDOWN:
                /// DIFFERENCE: No `SetCapture(hWnd)` in FullScreen
                if (!input::globals::g_LeftButtonState) { // LBUTTON current state
                    input::globals::BOOL_0076bb4c = TRUE;
                    input::globals::BOOL_0076bb50 = TRUE;
                }
                input::globals::g_LeftButtonState = TRUE; // LBUTTON current state
                input::globals::g_RightButtonState = TRUE;
                input::globals::BOOL_0076bb54 = TRUE;
                break;
            case WM_LBUTTONUP:
            case WM_RBUTTONUP:
                /// DIFFERENCE: No `ReleaseCapture()` in FullScreen
                input::globals::BOOL_0076bb4c = FALSE;
                input::globals::BOOL_0076bb50 = FALSE;
                input::globals::g_LeftButtonState = FALSE; // LBUTTON current state
                input::globals::g_RightButtonState = FALSE;
                input::globals::BOOL_0076bb54 = TRUE;
                break;
            }
        }
        else {
            // surrounded by an if (true) {}, probably a preprocessor
            switch (message) {
            case WM_LBUTTONDOWN:
                /// DIFFERENCE: No `SetCapture(hWnd)` in FullScreen
                input::globals::g_LeftButtonState = TRUE; // LBUTTON current state
                input::globals::BOOL_0076bb4c = TRUE;
                /// DIFFERENCE: No `input::globals::BOOL_0076bb54 = TRUE` in FullScreen
                break;
            case WM_LBUTTONUP:
                /// DIFFERENCE: No `ReleaseCapture()` in FullScreen
                input::globals::g_LeftButtonState = FALSE; // LBUTTON current state
                input::globals::BOOL_0076bb4c = FALSE;
                /// DIFFERENCE: No `input::globals::BOOL_0076bb54 = TRUE` in FullScreen
                break;
            case WM_RBUTTONDOWN:
                input::globals::g_RightButtonState = TRUE;
                input::globals::BOOL_0076bb50 = TRUE;
                /// DIFFERENCE: No `input::globals::BOOL_0076bb54 = TRUE` in FullScreen
                break;
            case WM_RBUTTONUP:
                input::globals::g_RightButtonState = FALSE;
                input::globals::BOOL_0076bb50 = FALSE;
                /// DIFFERENCE: No `input::globals::BOOL_0076bb54 = TRUE` in FullScreen
                break;
            }
        }
        return 0;

    case WM_LBUTTONDBLCLK:
        input::globals::BOOL_0076bb54 = TRUE;
        return 0;

    case WM_RBUTTONDBLCLK:
        input::globals::g_RightButtonDoubleClicked = TRUE;
        return 0;

    default:
        return DefWindowProcA(hWnd, message, wParam, lParam);
    }
}

#pragma endregion

#pragma region WindowProc (Windowed)

// <LegoRR.exe @00478980>
LRESULT __cdecl lego::main::WindowProc_Windowed(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_ACTIVATE:
        return 0;

    case WM_ACTIVATEAPP:
        // TRUE if this window is being activated
        globals::g_IsFocused = (BOOL)wParam;
        return 0;

    case WM_DESTROY:
    case WM_CLOSE:
    case WM_QUIT:
        globals::g_IsClosing = TRUE;
        return 0;

    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
        if (!(lego::globals::g_CMDLINE_FLAGS & CMD_DUALMOUSE)) {
            // surrounded by an if (true) {}, probably a preprocessor
            switch (message) {
            case WM_LBUTTONDOWN:
            case WM_RBUTTONDOWN:
                SetCapture(hWnd);
                if (!input::globals::g_LeftButtonState) { // LBUTTON current state
                    input::globals::BOOL_0076bb4c = TRUE;
                    input::globals::BOOL_0076bb50 = TRUE;
                }
                input::globals::g_LeftButtonState = TRUE; // LBUTTON current state
                input::globals::g_RightButtonState = TRUE;
                input::globals::BOOL_0076bb54 = TRUE;
                break;
            case WM_LBUTTONUP:
            case WM_RBUTTONUP:
                ReleaseCapture();
                input::globals::BOOL_0076bb4c = FALSE;
                input::globals::BOOL_0076bb50 = FALSE;
                input::globals::g_LeftButtonState = FALSE; // LBUTTON current state
                input::globals::g_RightButtonState = FALSE;
                input::globals::BOOL_0076bb54 = TRUE;
                break;
            }
        }
        else {
            // surrounded by an if (true) {}, probably a preprocessor
            switch (message) {
            case WM_LBUTTONDOWN:
                SetCapture(hWnd);
                input::globals::g_LeftButtonState = TRUE; // LBUTTON current state
                input::globals::BOOL_0076bb4c = TRUE;
                input::globals::BOOL_0076bb54 = TRUE;
                break;
            case WM_LBUTTONUP:
                ReleaseCapture();
                input::globals::g_LeftButtonState = FALSE; // LBUTTON current state
                input::globals::BOOL_0076bb4c = FALSE;
                input::globals::BOOL_0076bb54 = TRUE;
                break;
            case WM_RBUTTONDOWN:
                input::globals::g_RightButtonState = TRUE;
                input::globals::BOOL_0076bb50 = TRUE;
                input::globals::BOOL_0076bb54 = TRUE;
                break;
            case WM_RBUTTONUP:
                input::globals::g_RightButtonState = FALSE;
                input::globals::BOOL_0076bb50 = FALSE;
                input::globals::BOOL_0076bb54 = TRUE;
                break;
            }
        }
        return 0;

    case WM_LBUTTONDBLCLK:
        input::globals::BOOL_0076bb54 = TRUE;
        return 0;

    case WM_RBUTTONDBLCLK:
        input::globals::g_RightButtonDoubleClicked = TRUE;
        return 0;

    default:
        return DefWindowProcA(hWnd, message, wParam, lParam);
    }
}

#pragma endregion

#pragma region WindowProc (base)

// <LegoRR.exe @00478b40>
LRESULT CALLBACK lego::main::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (lego::globals::g_CMDLINE_FLAGS & CMD_FULLSCREEN) {
        return WindowProc_FullScreen(hWnd, message, wParam, lParam);
    }
    else {
        return WindowProc_Windowed(hWnd, message, wParam, lParam);
    }
}

#pragma endregion
#pragma endregion


// <LegoRR.exe @00478b90>
void __cdecl lego::main::SetRenderState(unsigned int type, unsigned int newState)
{
	DWORD currentState = 0; // dummy init to prevent compiler from complaining
	globals::g_IDirect3DDevice3->GetRenderState((D3DRENDERSTATETYPE)type, &currentState);

	if (newState != currentState) {
		globals::g_IDirect3DDevice3->SetRenderState((D3DRENDERSTATETYPE)type, (DWORD)newState);

		if (!globals::g_RenderStates_TABLE[type].isUsed) {
			globals::g_RenderStates_TABLE[type].isUsed = TRUE;
			globals::g_RenderStates_TABLE[type].value = newState;
		}
		else if (globals::g_RenderStates_TABLE[type].value == newState) {
			// kind of weird, but this is how you "turn" off the state...
			globals::g_RenderStates_TABLE[type].isUsed = FALSE;
		}
	}
}

// <LegoRR.exe @00478c00>
void __cdecl lego::main::CleanupRenderStates(void)
{
	for (unsigned int type = 0; type < 200; type++) {
		if (globals::g_RenderStates_TABLE[type].isUsed) {
			globals::g_IDirect3DDevice3->SetRenderState((D3DRENDERSTATETYPE)type,
				(DWORD)globals::g_RenderStates_TABLE[type].value);
			globals::g_RenderStates_TABLE[type].isUsed = FALSE;
		}
	}
}

#pragma endregion
