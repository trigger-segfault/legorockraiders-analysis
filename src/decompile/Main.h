// Main.h : Declares WinMain, the game loop, and other common accessor/update functions.
//
/// STATUS: [Usable, but still being refactored]
/// PURPOSE: 
///
/// NAMESPACE: lego::main
/// INITIALIZE: automatic on `WinMain` entry.
///             (no cleanup)
/// GLOBALS: public | private (but probably accessible)

#pragma once

#include "Common.h"
#include "DirectDraw.h"


#pragma region Globals
namespace lego::globals {

/// PUBLIC:
// <LegoRR.exe @00506800>
extern HWND g_hWnd;
// <LegoRR.exe @00506804>
extern HINSTANCE g_hInstance;
// <LegoRR.exe @00506808>
extern BOOL g_IsFocused;

/// PRIVATE:
// <LegoRR.exe @0050680c>
extern BOOL g_IsClosing;
// <LegoRR.exe @00506810>
extern const char* g_WindowClassName;
// <LegoRR.exe @00506814>
extern char g_ExeName[256];

/// PUBLIC:
// <LegoRR.exe @00506914>
extern IDirect3DRM3* g_IDirect3DRM3;
// <LegoRR.exe @00506918>
extern IDirect3DRMDevice3* g_IDirect3DRMDevice3;
// <LegoRR.exe @0050691c>
extern IDirect3DDevice3* g_IDirect3DDevice3;
// D3DRMFOGMETHOD_VERTEX = 0x1,
// D3DRMFOGMETHOD_TABLE  = 0x2,
// D3DRMFOGMETHOD_ANY    = 0x4,
// <LegoRR.exe @00506920>
extern unsigned int g_SceneFogMethod;
// <LegoRR.exe @00506924>
extern Size2I g_RESOLUTION;

/// PRIVATE:
// <LegoRR.exe @0050692c>
extern GameFunctions g_GameFunctions;
// <LegoRR.exe @00506938>
extern BOOL g_GameFunctions_ISINIT;

/// PUBLIC:
// <LegoRR.exe @0050693c>
extern float g_FPSLock;

/// PRIVATE:
// <LegoRR.exe @00506940>
extern D3DStateItem g_RenderStates_TABLE[200];
// <LegoRR.exe @00506f80>
extern DWORD g_WindowStyle;

/// PUBLIC:
// <LegoRR.exe @00506f84>
extern CmdlineFlags g_CMDLINE_FLAGS;
// <LegoRR.exe @00506f88>
extern ProgrammerMode g_PROGRAMMER_MODE;

/// PRIVATE:
// <LegoRR.exe @00506f8c>
extern char g_StartLevel[256];
// <LegoRR.exe @0050708c>
extern FeatureFlags g_FeatureFlags; // 0x8000 (block fade)

} /* namespace logo::globals */
#pragma endregion


// <LegoRR.exe @00477a60>
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);

#pragma region Functions
namespace lego::main {

// <LegoRR.exe @00477e90>
void __cdecl DisableTextureManagement_NonVoodoo2(void);
// <LegoRR.exe @00477eb0>
void __cdecl ParseCmdlineOptions(char* args, BOOL* out_nosound, BOOL* out_insistOnCD);
// <LegoRR.exe @004781f0>
void __cdecl UpdateAndRender(BOOL doFillSurface);
// <LegoRR.exe @00478230>
FeatureFlags __cdecl GetFeatureFlags(void);
// <LegoRR.exe @00478240>
int __cdecl GetDeviceBitsPerPixel(void);
// <LegoRR.exe @00478260>
void __cdecl UpdateDirect3DRM(void);
// <LegoRR.exe @00478290>
BOOL __cdecl Main_SetGameFunctions(GameFunctions* gameFuncs);
// <LegoRR.exe @004782c0>
//DWORD __stdcall timeGetTime(void);
// <LegoRR.exe @004782d0>
BOOL __cdecl ShouldHandleWinMessage(MSG* msg);
// <LegoRR.exe @00478300>
void __cdecl HandleWinMessageQueue(void);
// <LegoRR.exe @00478370>
void __cdecl ShowMainWindow(BOOL isFullScreen, int windowedX, int windowedY, int screenWidth, int screenHeight);
// <LegoRR.exe @00478490>
BOOL __cdecl InitDirect3DRM(const DeviceMode* device, IDirectDraw* ddraw1, IDirectDrawSurface4* ddSurface4, BOOL isFullScreen);
// <LegoRR.exe @004785d0>
void __cdecl AdjustMainWindowedRect(RECT* lpRect);
// <LegoRR.exe @004785f0>
void __cdecl SetD3DRMGraphicsQuality(GraphicsQuality quality, BOOL dither, BOOL filter, BOOL mipmap, BOOL linearmipmap, BOOL blend, BOOL sort);
// <LegoRR.exe @00478690>
BOOL __cdecl SetMainWindowTitle(LPCSTR title);
// <LegoRR.exe @004786b0>
BOOL __cdecl CreateMainWindow(HINSTANCE hInstance);
// <LegoRR.exe @00478780>
LRESULT CALLBACK WindowProc__FullScreen(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
// <LegoRR.exe @00478980>
LRESULT CALLBACK WindowProc__Windowed(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
// <LegoRR.exe @00478b40>
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
// <LegoRR.exe @00478b90>
void __cdecl D3D_SetRenderState(unsigned int renderStateType, unsigned int renderStateValue);
// <LegoRR.exe @00478c00>
void __cdecl D3D_CleanupRenderStates(void);
// // <LegoRR.exe @00478c40>
// BOOL __cdecl SFX_UnkCallsMixer_FUN_00478c40(float param_1, float param_2);
// // <LegoRR.exe @00478c60>
// BOOL __cdecl SFX_UnkCallsMixer_FUN_00478c60(float* param_1, float* param_2);
// // <LegoRR.exe @00478c80>
// BOOL __cdecl SFX_UnkMixer_FUN_00478c80(float* param_1, float* param_2, BOOL param_3);

} /* namespace lego::main */
#pragma endregion

