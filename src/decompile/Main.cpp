// Main.cpp : Defines WinMain, the game loop, and other common accessor/update functions.
//
/// STATUS: [Usable, but still being refactored]

#include "Main.h"
#include "AVIPlayer.h"
#include "CFG.h"
#include "DirectDraw.h"
#include "Files.h"
#include "Input.h"
#include "ModeSelection.h"
#include "Registry.h"
#include "SharedBuffers.h"
#include "StringUtils.h"


using namespace lego;
using namespace lego::main;


#pragma region Globals

/// PUBLIC:
// <LegoRR.exe @00506800>
HWND lego::globals::g_hWnd;
// <LegoRR.exe @00506804>
HINSTANCE lego::globals::g_hInstance;
// <LegoRR.exe @00506808>
BOOL lego::globals::g_IsFocused;

/// PRIVATE:
// <LegoRR.exe @0050680c>
BOOL lego::globals::g_IsClosing;
// <LegoRR.exe @00506810>
const char* lego::globals::g_WindowClassName;
// <LegoRR.exe @00506814>
char lego::globals::g_ExeName[256];

/// PUBLIC:
// <LegoRR.exe @00506914>
IDirect3DRM3* lego::globals::g_IDirect3DRM3;
// <LegoRR.exe @00506918>
IDirect3DRMDevice3* lego::globals::g_IDirect3DRMDevice3;
// <LegoRR.exe @0050691c>
IDirect3DDevice3* lego::globals::g_IDirect3DDevice3;
// D3DRMFOGMETHOD_VERTEX = 0x1,
// D3DRMFOGMETHOD_TABLE  = 0x2,
// D3DRMFOGMETHOD_ANY    = 0x4,
// <LegoRR.exe @00506920>
unsigned int lego::globals::g_SceneFogMethod;
// <LegoRR.exe @00506924>
Size2I lego::globals::g_RESOLUTION;

/// PRIVATE:
// <LegoRR.exe @0050692c>
GameFunctions lego::globals::g_GameFunctions;
// <LegoRR.exe @00506938>
BOOL lego::globals::g_GameFunctions_ISINIT;

/// PUBLIC:
// <LegoRR.exe @0050693c>
float lego::globals::g_FPSLock;

/// PRIVATE:
// <LegoRR.exe @00506940>
D3DStateItem lego::globals::g_RenderStates_TABLE[200];
// <LegoRR.exe @00506f80>
DWORD lego::globals::g_WindowStyle;

/// PUBLIC:
// <LegoRR.exe @00506f84>
CmdlineFlags lego::globals::g_CMDLINE_FLAGS;
// <LegoRR.exe @00506f88>
ProgrammerMode lego::globals::g_PROGRAMMER_MODE;

/// PRIVATE:
// <LegoRR.exe @00506f8c>
char lego::globals::g_StartLevel[256];
// <LegoRR.exe @0050708c>
FeatureFlags lego::globals::g_FeatureFlags; // 0x8000 (block fade)

#pragma endregion


#pragma region WinMain Function

// <LegoRR.exe @00477a60>
int APIENTRY WinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPSTR     lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);

    char mutexName[1024];
    char fullCmdLine[1024];
    char errorMessage[1024];
    char standardParameters[1024];

    BOOL nosound = false, insistOnCD = false;

    if (true /*USEMUTEX*/) {
        std::sprintf(mutexName, "%s Mutex", "Lego Rock Raiders" /*MUTEX_NAME*/);
        ::CreateMutexA(nullptr, true, mutexName);
        if (::GetLastError() == ERROR_ALREADY_EXISTS /*0xb7*/)
            return false;
    }

    char* cmdLine = ::GetCommandLineA();
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
        ::_strupr(exeExtension); // to upper
        exeExtension = std::strstr(globals::g_ExeName, ".EXE");
        if (exeExtension != nullptr) {
            // separate executable name from extension,
            // this name without extension will be the basis for many constant lookups
            *exeExtension = '\0';
        }
    }


    globals::g_WindowClassName = globals::g_ExeName; // "LegoRR";
    globals::g_IsFocused = false;
    globals::g_IsClosing = false;
    globals::g_GameFunctions_ISINIT = false;
    globals::g_hInstance = hInstance;
    globals::g_FPSLock = 0.0f;
    globals::g_CMDLINE_FLAGS = CMD_NONE /*0*/;

    // Add StandardParameters to command line arguments, then parse command line arguments
    BOOL regResult = registry::Registry_QueryValueOnLM("SOFTWARE\\LEGO Media\\Games\\Rock Raiders",
		"StandardParameters", REGISTRY_STRING /*0*/, standardParameters, sizeof(standardParameters));
    if (regResult && !IGNORESTANDARDPARAMETERS) {
        std::sprintf(fullCmdLine, "%s %s", lpCmdLine, standardParameters);
    }
    else {
        std::sprintf(fullCmdLine, "%s", lpCmdLine);
    }
    main::ParseCmdlineFlags(fullCmdLine, &nosound, &insistOnCD);


    regResult = registry::Registry_QueryValueOnLM("SOFTWARE\\LEGO Media\\Games\\Rock Raiders",
		"NoHALMessage", REGISTRY_STRING /*0*/, errorMessage, sizeof(errorMessage));
    if (!regResult) {
        std::sprintf(errorMessage, "No DirectX 3D accelerator could be found.");
    }

    file::InitFileScanning();

    file::InitSharedFileBuffers();
    file::InitFileSystem(globals::g_ExeName, insistOnCD, "SOFTWARE\\LEGO Media\\Games\\Rock Raiders");

    cfg::ReservedPool_CFGProperty___Init();

    input::InitDirectInput();

    if (!main::CreateMainWindow(hInstance, nCmdShow))
        goto WinMain_Cleanup;


    ddraw::InitDirectDraw(globals::g_hWnd);
    audio::InitSoundSystem(nosound);

    if (!setup::ChooseScreenMode(true /*showDialog*/, // likely preprocessor-defined
                                globals::g_CMDLINE_FLAGS & CMD_DEBUG  /*isDebug*/,
                                globals::g_CMDLINE_FLAGS & CMD_BEST   /*isBest*/,
                                globals::g_CMDLINE_FLAGS & CMD_WINDOW /*isWindow*/,
                                errorMessage))
    {
        goto WinMain_DestroyWindow;
    }

    video::InitAVIFile(globals::g_IDirectDraw4);
    ddraw::Draw_SurfaceLockRect(nullptr);

    game::InitGameFunctions(globals::g_ExeName);
    if (!globals::g_GameFunctions_ISINIT) {
        goto WinMain_DestroyWindow;
    }

    #pragma region ////// INIT / LOOP / CLEANUP //////

    if (globals::g_GameFunctions.Init != nullptr) {
        ////// GAME INIT //////
        if (!globals::g_GameFunctions.Init()) {
            globals::g_GameFunctions.Init    = nullptr;
            globals::g_GameFunctions.Update  = nullptr;
            globals::g_GameFunctions.Cleanup = nullptr;
            goto WinMain_DestroyWindow; // (optional, control flow already takes us there)
        }
    }

    if (globals::g_GameFunctions.Update != nullptr) {
        float ellapsed = 1.0f; // ellapsed game time units since last update
        unsigned int lastTime = ::timeGetTime();

        ////// GAME LOOP //////
        while (!globals::g_IsClosing) {
            globals::BOOL_0076bb4c = 0;
            globals::BOOL_0076bb50 = 0;
            globals::BOOL_0076bb54 = 0;
            globals::g_RightButtonDoubleClicked = 0;
            main::HandleWinMessageQueue();

            if (globals::g_CMDLINE_FLAGS & CMD_FULLSCREEN)
                globals::g_IsFocused = true;

            input::UpdateKeyboardState();
            input::UpdateMousePosition();

            if (!globals::g_GameFunctions.Update(ellapsed)) {
                // debugf("FAILED: g_GameFunctions.Update(float)\n");
                globals::g_IsClosing = true;
            }
            
            main::UpdateDirect3DRM();
            ddraw::DDraw_Render();

            globals::g_CMDLINE_FLAGS &= ~CMD_D3DRMUPDATED /*~0x1*/ /*0xfffffffe*/;
            if (globals::g_CMDLINE_FLAGS & CMD_FPSLOCK30) {
                ellapsed = (25.0f / 30.0f) /*0.8333333f*/;
            }
            else if (globals::g_CMDLINE_FLAGS & CMD_NOFPSLOCK) {
                ellapsed = 0.0;
                lastTime = ::timeGetTime();
            }
            else if (globals::g_FPSLock != 0.0f) {
                ellapsed = globals::g_FPSLock;
                lastTime = ::timeGetTime();
            }
            else {
                unsigned int currentTime = ::timeGetTime();

                ellapsed = (float)(unsigned long long)(currentTime - lastTime) * 0.025f /*(25.0f / 1000.0f)*/;
                lastTime = currentTime;
                if (ellapsed > 3.0f)
                    ellapsed = 3.0f;
            }
        }
    }

    if (globals::g_GameFunctions.Cleanup != nullptr) {
        ////// GAME CLEANUP //////
        globals::g_GameFunctions.Cleanup();
    }

    #pragma endregion


WinMain_DestroyWindow:
    ddraw::CleanupDirectDraw();
    ::DestroyWindow(globals::g_hWnd);

WinMain_Cleanup:
    input::CleanupDirectInput();
    cfg::ReservedPool_CFGProperty___Cleanup();
    lego::logf_removed(nullptr);
    file::CleanupFileScanning();
    file::Scan_WriteDataDirList();

    return 0;
}

#pragma endregion


#pragma region Functions

// Sets the "-nm" commandline option only if the "-ftm" option is not set.
//  (The "-ftm" option is intended to be set when running on Voodoo2-based graphics cards, as is shown by CLGen.exe)
// This is called when Lego.cfg/Lego*::Main::TextureUsage (units in pixels)
//  is valid and <= available video memory.
// <LegoRR.exe @00477e90>
void __cdecl lego::main::DisableTextureManagement_NonVoodoo2(void)
{
	if (!(globals::g_CMDLINE_FLAGS & CMD_FTM)) {
		globals::g_CMDLINE_FLAGS |= CMD_NM;
	}
}

// <LegoRR.exe @00477eb0>
void __cdecl lego::main::ParseCmdlineOptions(char* args, BOOL* out_nosound, BOOL* out_insistOnCD)
{
	
}


#pragma endregion

