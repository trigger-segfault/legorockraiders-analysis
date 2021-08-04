// Input.h : 
//

#pragma once

#include "../Common.h"


namespace lego {
namespace input {

#pragma region Tools

// Keys use the same numbering as used by DirectInput's "DIK_*" enums.
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
};

#pragma endregion


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

makeGlob(0076bb3c, BOOL*, g_LeftButtonState);
makeGlob(0076bb40, BOOL*, g_RightButtonState);
makeGlob(0076bb4c, BOOL*, BOOL_0076bb4c);
makeGlob(0076bb50, BOOL*, BOOL_0076bb50);
makeGlob(0076bb54, BOOL*, BOOL_0076bBOOL_0076bb54b4c);
makeGlob(0076bb58, BOOL*, g_RightButtonDoubleClicked);

makeGlob(0076ba00, bool*, g_KeyboardState_Current_TABLE);
makeGlob(0076bb80, bool*, g_KeyboardState_Previous_TABLE);


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
