#pragma once
#include "DirectDraw.h"


// <LegoRR.exe @00477a60>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
// <LegoRR.exe @00477e90>
void Main_DisableTextureManagement_NonVoodoo2(void);
// <LegoRR.exe @00477eb0>
void Boot_ParseCmdFlags(char * args, BOOL * out_nosound, BOOL * out_insistOnCD);
// <LegoRR.exe @004781f0>
void Main_UpdateAndRender__004781f0(BOOL doFillSurface);
// <LegoRR.exe @00478230>
DebugFlags Config_GetDebugFlags(void);
// <LegoRR.exe @00478240>
int Setup_GetDeviceBitsPerPixel(void);
// <LegoRR.exe @00478260>
void Main_DoDirect3DRMUpdate(void);
// <LegoRR.exe @00478290>
BOOL Main_SetGameFunctions(GameFunctions * gameFuncs);
// <LegoRR.exe @004782c0>
DWORD timeGetTime(void);
// <LegoRR.exe @004782d0>
BOOL Win_ShouldHandleMessage(MSG * msg);
// <LegoRR.exe @00478300>
void Win_HandleMessageQueue(void);
// <LegoRR.exe @00478370>
void Win_ShowGameWindow(BOOL isFullScreen, int windowedX, int windowedY, int screenWidth, int screenHeight);
// <LegoRR.exe @00478490>
BOOL Main_Direct3DRMCreate(DeviceMode * device, IUnknown * ddraw1, IDirectDrawSurface4 * ddSurface, BOOL isFullScreen);
// <LegoRR.exe @004785d0>
void Win_AdjustMainWindowedRect(LPRECT lpRect);
// <LegoRR.exe @004785f0>
void Draw_SetDirectXGraphicsQuality(GraphicsQuality quality, BOOL dither, BOOL filter, BOOL mipmap, BOOL linearmipmap, BOOL blend, BOOL sort);
// <LegoRR.exe @00478690>
BOOL Win_SetMainWindowTitle(LPCSTR title);
// <LegoRR.exe @004786b0>
BOOL Win_CreateMainWindow(HINSTANCE hInstance);
// <LegoRR.exe @00478780>
LRESULT Win_WindowProc__FullScreen(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
// <LegoRR.exe @00478980>
LRESULT Win_WindowProc__Windowed(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
// <LegoRR.exe @00478b40>
LRESULT Win_WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
// <LegoRR.exe @00478b90>
void Draw_SetRenderState(uint renderStateType, undefined4 renderStateValue);
// <LegoRR.exe @00478c00>
void Draw_CleanupRenderStates(void);
// <LegoRR.exe @00478c40>
undefined SFX_UNKCallsMixer__00478c40(undefined1 param_1, undefined1 param_2);
// <LegoRR.exe @00478c60>
undefined FUN_00478c60(float * param_1, float * param_2);
// <LegoRR.exe @00478c80>
undefined4 SFX_UnkMixer__00478c80(float * param_1, float * param_2, int param_3);


