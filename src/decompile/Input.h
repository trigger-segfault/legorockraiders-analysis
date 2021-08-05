#pragma once


// <LegoRR.exe @0047f050>
BOOL Main_DirectInputCreate(void);
// <LegoRR.exe @0047f1b0>
void Input_UpdateKeyboardState(void);
// <LegoRR.exe @0047f270>
int Input_GetNumKeysPressed(void);
// <LegoRR.exe @0047f290>
void Input_DirectInputCleanup(void);
// <LegoRR.exe @0047f2d0>
void Input_UpdateMousePosition(void);
// <LegoRR.exe @0047f390>
undefined Input_SetMousePosition(int x, int y);

