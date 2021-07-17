// Main.h : 
//

#pragma once

#include "../Common.h"
#include "../Drawing/DirectDraw.h"


namespace lego {
namespace main {
	
#pragma region Types

// Lego.cfg "Main::Quality" option
enum GraphicsQuality : int
{
	QUALITY_WIREFRAME = 0, // D3DRMRENDER_WIREFRAME = 0x40 = (D3DRMSHADE_FLAT | D3DRMLIGHT_OFF | D3DRMFILL_WIREFRAME) /*0x0 | 0x0 | 0x40*/
	QUALITY_UNLITFLAT = 1, // D3DRMRENDER_UNLITFLAT = 0x80 = (D3DRMSHADE_FLAT | D3DRMLIGHT_OFF | D3DRMFILL_SOLID)     /*0x0 | 0x0 | 0x80*/
	                       // not parsable (anything other than the other 3 names will return an error)
	                       // however this value is still checked when actually setting graphics quality
	QUALITY_FLAT      = 2, // D3DRMRENDER_FLAT      = 0x88 = (D3DRMSHADE_FLAT    | D3DRMLIGHT_ON | D3DRMFILL_SOLID)   /*0x0 | 0x8 | 0x80*/
	QUALITY_GOURAUD   = 3, // D3DRMRENDER_GOURAUD   = 0x89 = (D3DRMSHADE_GOURAUD | D3DRMLIGHT_ON | D3DRMFILL_SOLID)   /*0x1 | 0x8 | 0x80*/
};

// [INTERNAL]
struct RenderStateItem
{
	/*0,4*/ unsigned int value; // not guaranteed to be uint, sometimes signed int, sometimes BOOL, etc...
	/*4,4*/ BOOL isUsed;
	/*8*/
};

typedef BOOL(__cdecl* GameInitFunction)(void);
typedef BOOL(__cdecl* GameUpdateFunction)(float ellapsed); // float argument is ellapsed game time units since last update
typedef void(__cdecl* GameCleanupFunction)(void);

struct GameFunctions
{
	/*0,4*/ GameInitFunction Init;
	/*4,4*/ GameUpdateFunction Update;
	/*8,4*/ GameCleanupFunction Cleanup;
	/*c*/
};

#pragma endregion


#pragma region Globals

namespace globals {

	// [INCLUSIVE]: WinMain functions, Input.c function, GetDeviceBitsPerPixel
	// <LegoRR.exe @00506800>
	extern HWND g_hWnd;
	// [INCLUSIVE]: WinMain, ChooseScreenMode, Input.c function
	// <LegoRR.exe @00506804>
	extern HINSTANCE g_hInstance;
	// [INCLUSIVE]: WinMain functions, Input.c function
	// <LegoRR.exe @00506808>
	extern BOOL g_IsFocused;
	// [EXCLUSIVE]: WinMain, GameWindowProc functions
	// <LegoRR.exe @0050680c>
	extern BOOL g_IsClosing;
	// [EXCLUSIVE]: WinMain, CreateMainWindow
	// <LegoRR.exe @00506810>
	extern const char* g_WindowClassName;
	// [EXCLUSIVE]: WinMain
	// <LegoRR.exe @00506814>
	extern char g_ExeName[256];

	// [UNKNOWN]:
	// <LegoRR.exe @00506914>
	extern IDirect3DRM3* g_IDirect3DRM3;
	// [UNKNOWN]:
	// <LegoRR.exe @00506918>
	extern IDirect3DRMDevice3* g_IDirect3DRMDevice3;
	// [UNKNOWN]:
	// <LegoRR.exe @0050691c>
	extern IDirect3DDevice3* g_IDirect3DDevice3;
	// D3DRMFOGMETHOD_VERTEX = 0x1,
	// D3DRMFOGMETHOD_TABLE  = 0x2,
	// D3DRMFOGMETHOD_ANY    = 0x4,
	// [EXCLUSIVE]: Direct3DRMCreate, SetRootSceneFodMode
	// <LegoRR.exe @00506920>  XREF[3]
	extern unsigned int g_SceneFogMethod;
	// [INCLUSIVE]:
	// <LegoRR.exe @00506924>  XREF[15,12=27]
	extern Size2I g_RESOLUTION;
	// [EXCLUSIVE]: WinMain, SetGameFunctions
	// <LegoRR.exe @0050692c>  XREF[3,7]
	extern GameFunctions g_GameFunctions;
	// [EXCLUSIVE]: WinMain, SetGameFunctions
	// <LegoRR.exe @00506938>  XREF[3]
	extern BOOL g_GameFunctions_ISINIT;
	// [INCLUSIVE]:
	// <LegoRR.exe @0050693c>  XREF[5]
	extern float g_FPSLOCK_VSYNC;
	// [EXCLUSIVE]: SetRenderState, Cleanup(Update?)RenderStates
	// <LegoRR.exe @00506940>  XREF[3,7]
	extern RenderStateItem g_RenderStates_TABLE[200];
	// <LegoRR.exe @00506f80>  XREF[3]
	// [EXCLUSIVE]: AdjustGameWindowedRect, ShowGameWindow
	extern DWORD g_WindowStyle;
	/*
	// [INCLUSIVE]:
	// <LegoRR.exe @00506f84>  XREF[82]
	extern CmdlineFlags g_CMDLINE_FLAGS;
	// [INCLUSIVE/ACCESSOR]: ParseCmdFlags, WinMain functions, game functions, GetProgrammerMode (accessor)
	// <LegoRR.exe @00506f88>  XREF[17]
	extern ProgrammerMode g_PROGRAMMER_MODE;
	// [EXCLUSIVE/ACCESSOR]: ParseCmdFlags, GetStartLevel (accessor)
	// <LegoRR.exe @00506f8c>  XREF[3,1]
	extern char g_STARTLEVEL[256];
	// [EXCLUSIVE/ACCESSOR]: ParseCmdFlags, GetDebugFlags (accessor)
	// <LegoRR.exe @0050708c>  XREF[2]
	extern DebugFlags g_DEBUG_FLAGS; // 0x8000 (block fade)
	*/

	// <LegoRR.exe @0054155c>
	extern unsigned int COUNT_0054155c;
	// <LegoRR.exe @00541560>
	extern unsigned int COUNT_00541560;
	// <LegoRR.exe @00541564>
	extern DWORD g_Direct3D_TextureHandle_New;
	// <LegoRR.exe @00541568>
	extern DWORD g_Direct3D_LightState_New;
	// <LegoRR.exe @0054156c>
	extern IDirect3DTexture2* g_IDirect3DTexture2_New;
	// <LegoRR.exe @00541570>
	extern DWORD g_Direct3D_TextureHandle_Old;
	// <LegoRR.exe @00541574>
	extern DWORD g_Direct3D_LightState_Old;
	// <LegoRR.exe @00541578>
	extern IDirect3DTexture2* g_IDirect3DTexture2_Old;
	// <LegoRR.exe @0054157c>
	extern DWORD g_Direct3D_MaterialHandle;
	// <LegoRR.exe @00541580>
	extern IDirect3DMaterial3* g_IDirect3DMaterial3;
	// <LegoRR.exe @00541584>
	//ReservedPool<Struct_34> start

} /* namespace globals */

#pragma endregion


#pragma region WinMain

// <LegoRR.exe @00477a60>
int APIENTRY WinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPSTR     lpCmdLine,
                     _In_ int       nCmdShow);

#pragma endregion


#pragma region Functions

// Assigns the CMD_NM flag to g_CMDLINE_FLAGS if CMD_FTM is not set.
//  (CMD_FTM is generally supposed to be set for Voodoo2)
// <LegoRR.exe @00477e90>
void __cdecl DisableTextureManagement_NonVoodoo2(void);

// <LegoRR.exe @00477eb0>
void __cdecl ParseCmdlineFlags(const char* args, BOOL* out_nosound, BOOL* out_insistOnCD);

// <LegoRR.exe @004781f0>
void __cdecl UpdateAndRender(BOOL doFillSurface);
/*
// <LegoRR.exe @00478230>
DebugFlags __cdecl GetDebugFlags(void);
*/
// <LegoRR.exe @00478240>
int __cdecl GetDeviceBitsPerPixel(void);

// <LegoRR.exe @00478260>
void __cdecl UpdateDirect3DRM(void);

// <LegoRR.exe @00478290>
BOOL __cdecl SetGameFunctions(GameFunctions* gameFuncs);

// <LegoRR.exe @004782d0>
BOOL __cdecl ShouldHandleMessage(MSG* msg);

// <LegoRR.exe @00478300>
void __cdecl HandleMessageQueue(void);

// <LegoRR.exe @00478370>
void __cdecl ShowGameWindow(BOOL isFullScreen, int x, int y, int width, int height);

// <LegoRR.exe @00478490>
BOOL __cdecl InitDirect3DRM(draw::DeviceMode* device, IDirectDraw* ddraw1, IDirectDrawSurface4* ddSurface, BOOL isFullScreen);

// <LegoRR.exe @004785d0>
void __cdecl AdjustMainWindowedRect(RECT* lpRect);

// <LegoRR.exe @004785f0>
void __cdecl SetGraphicsQuality(GraphicsQuality quality, BOOL dither, BOOL filter, BOOL mipmap, BOOL linearmipmap, BOOL blend, BOOL sort);

// <LegoRR.exe @00478690>
BOOL __cdecl SetMainWindowTitle(const char* title);

// <LegoRR.exe @004786b0>
BOOL __cdecl CreateMainWindow(HINSTANCE hInstance, int nCmdShow);

// <LegoRR.exe @00478780>
LRESULT __cdecl WindowProc_FullScreen(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// <LegoRR.exe @00478980>
LRESULT __cdecl WindowProc_Windowed(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// <LegoRR.exe @00478b40>
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// <LegoRR.exe @00478b90>
void __cdecl SetRenderState(unsigned int renderType, unsigned int newState);

// <LegoRR.exe @00478c00>
void __cdecl CleanupRenderStates(void);

#pragma endregion


} /* namespace main */
} /* namespace lego */
