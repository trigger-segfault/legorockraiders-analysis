// Input.h : 
//

#pragma once

#include "../Common.h"


namespace lego {
namespace input {

#pragma region Globals

namespace globals {

    // <LegoRR.exe @0076ba00>
    extern unsigned char g_KeyboardState_Previous_TABLE[256];
    // <LegoRR.exe @0076bb00>
    //static IDirectInput8A* g_IDirectInputA;
    // <LegoRR.exe @0076bb04>
    //static IDirectInputDevice8A* g_IDirectInputDeviceA;

    // <LegoRR.exe @0076bb0c>
    //static BOOL g_IsDirectInputAcquired;

    // <LegoRR.exe @0076bb24>
    extern Point2I g_MousePosition;

    // <LegoRR.exe @0076bb34>
    extern Point2I g_MouseDeltaPosition;

    // <LegoRR.exe @0076bb3c>
    extern BOOL g_LeftButtonState;
    // <LegoRR.exe @0076bb40>
    extern BOOL g_RightButtonState;

    // <LegoRR.exe @0076bb4c>
    extern BOOL BOOL_0076bb4c;
    // <LegoRR.exe @0076bb50>
    extern BOOL BOOL_0076bb50;
    // <LegoRR.exe @0076bb54>
    extern BOOL BOOL_0076bb54;
    // <LegoRR.exe @0076bb58>
    extern BOOL g_RightButtonDoubleClicked;

    // <LegoRR.exe @0076bb80>
    extern unsigned char g_KeyboardState_Current_TABLE[256];
} /* namespace globals */

#pragma endregion


#pragma region Functions

// <LegoRR.exe @0047f050>
BOOL __cdecl InitDirectInput(void);

// <LegoRR.exe @0047f290>
void __cdecl CleanupDirectInput(void);

// <LegoRR.exe @0047f1b0>
void __cdecl UpdateKeyboardState(void);
// <LegoRR.exe @0047f2d0>
void __cdecl UpdateMousePosition(void);

// <LegoRR.exe @00410a80>
BOOL __cdecl GetBool_0076bb3c(void);


// <LegoRR.exe @00410a60>
int __cdecl GetMousePositionX(void);

// <LegoRR.exe @00410a70>
int __cdecl GetMousePositionY(void);


// <LegoRR.exe @0047f390>
void __cdecl SetMousePosition(int x, int y);

// <LegoRR.exe @0047f270>
int __cdecl GetNumKeysPressed(void);

#pragma endregion


} /* namespace input */
} /* namespace lego */
