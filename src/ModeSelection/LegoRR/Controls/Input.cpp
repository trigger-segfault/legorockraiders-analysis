// Input.cpp : 
//

#include "Input.h"
#include "../Main/Main.h"


#pragma region Defines

#define s_Dev_SourceSafe__Input_c "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Input.c"

#pragma endregion


#pragma region Globals
namespace lego {
namespace input {
namespace globals {
	// define these because I'm too lazy to deal with linker errors
	//static IID IID_IDirect3D3 = { 0xbb223240, 0xe72b, 0x11d0, 0xa9, 0xb4, 0x00, 0xaa, 0x00, 0xc0, 0x99, 0x3e };

	//static IID IID_IDirectDraw4 = { 0x9c59509a, 0x39bd, 0x11d1, 0x8c, 0x4a, 0x00, 0xc0, 0x4f, 0xd9, 0x30, 0xc5 };
    static IID IID_IDirectInput8A = { 0xbf798030, 0x483a, 0x4da2, 0xaa, 0x99, 0x5d, 0x64, 0xed, 0x36, 0x97, 0x00 }; // __uuidof(IDirectInput8A);// "BF798030-483A-4DA2-AA99-5D64ED369700");
    static GUID GUID_SysKeyboard = { 0x6f1d2b61, 0xd5a0, 0x11cf, 0xbf, 0xc7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 };
        /* GUID_SysKeyboard {6F1D2B61-D5A0-11CF-BFC7-444553540000} */
    /*guidSysKeyboard._4_4_ = 0x11cfd5a0;
    guidSysKeyboard._0_4_ = 0x6f1d2b61;
    guidSysKeyboard._8_4_ = 0x4544c7bf;
    guidSysKeyboard._12_4_ = 0x5453;*/

	/*// <LegoRR.exe @0076bc80>
	static HWND g_DirectX_hWnd;
	// <LegoRR.exe @0076bc84>
	static IDirectDraw4* g_IDirectDraw4;
	// <LegoRR.exe @0076bc88>
	static IDirectDrawSurface4* g_IDirectDrawSurface4_RenderTarget;
	// <LegoRR.exe @0076bc8c>
	static IDirectDrawSurface4* g_IDirectDrawSurface4_DrawTarget;
	// <LegoRR.exe @0076bc90>
	static unsigned int DAT_0076bc90;
	// <LegoRR.exe @0076bc94>
	static IDirectDrawClipper* g_IDirectDrawClipper_RenderTarget;
	// <LegoRR.exe @0076bc98>
	static IDirectDrawClipper* g_IDirectDrawClipper_DrawTarget;*/


    // <LegoRR.exe @0076ba00>
    unsigned char g_KeyboardState_Previous_TABLE[256];
    // <LegoRR.exe @0076bb00>
    static IDirectInput8A* g_IDirectInputA;
    // <LegoRR.exe @0076bb04>
    static IDirectInputDevice8A* g_IDirectInputDeviceA;

    // <LegoRR.exe @0076bb0c>
    static BOOL g_IsDirectInputAcquired;

    // <LegoRR.exe @0076bb24>
    Point2I g_MousePosition;

    // <LegoRR.exe @0076bb34>
    Point2I g_MouseDeltaPosition;

    // <LegoRR.exe @0076bb3c>
    BOOL g_LeftButtonState;
    // <LegoRR.exe @0076bb40>
    BOOL g_RightButtonState;

    // <LegoRR.exe @0076bb4c>
    BOOL BOOL_0076bb4c;
    // <LegoRR.exe @0076bb50>
    BOOL BOOL_0076bb50;
    // <LegoRR.exe @0076bb54>
    BOOL BOOL_0076bb54;
    // <LegoRR.exe @0076bb58>
    BOOL g_RightButtonDoubleClicked;

    // <LegoRR.exe @0076bb80>
    unsigned char g_KeyboardState_Current_TABLE[256];

} /* namespace globals */
} /* namespace input */
} /* namespace lego */
#pragma endregion


using namespace lego::input;


#pragma region Functions

// <LegoRR.exe @0047f050>
BOOL __cdecl lego::input::InitDirectInput(void)
{
    //GUID_SysKeyboard

    if (DirectInput8Create(main::globals::g_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8A, (LPVOID*)&globals::g_IDirectInputA, nullptr) != 0) {
        debugf("FAILED: DirectInput8Create\n");
        return FALSE;
    }
    if (globals::g_IDirectInputA->CreateDevice(GUID_SysKeyboard, &globals::g_IDirectInputDeviceA, nullptr) != 0) {
        debugf("FAILED: IDirectInput8A::CreateDevice\n");
        return FALSE;
    }

    if (globals::g_IDirectInputDeviceA->SetDataFormat(&c_dfDIKeyboard) != 0) {
        debugf("FAILED: IDirectInputDevice8A::SetDataFormat\n");
        return FALSE;
    }
    if (globals::g_IDirectInputDeviceA->SetCooperativeLevel(main::globals::g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE /*0x4 | 0x2*/) != 0) {
        debugf("FAILED: IDirectInputDevice8A::SetCooperativeLevel\n");
        return FALSE;
    }

    globals::g_IsDirectInputAcquired = (globals::g_IDirectInputDeviceA->Acquire() == 0);
    return TRUE;
}



// <LegoRR.exe @0047f1b0>
void __cdecl lego::input::UpdateKeyboardState(void)
{
    /*IDirectInputDeviceA* This;
    HRESULT HVar1;
    int iVar2;
    undefined4* puVar3;
    undefined4* puVar4;

    This = globals::g_IDirectInputDeviceA;
    iVar2 = 1;
    if (!(lego::globals::g_CMDLINE_FLAGS & lego::CMD_FULLSCREEN)) {
        iVar2 = globals::wnd::g_IsFocused;
    }*/
    if (!(lego::globals::g_CMDLINE_FLAGS & lego::CMD_FULLSCREEN) && !main::globals::g_IsFocused) {
        std::memset(globals::g_KeyboardState_Current_TABLE, 0, sizeof(globals::g_KeyboardState_Current_TABLE));
        std::memset(globals::g_KeyboardState_Previous_TABLE, 0, sizeof(globals::g_KeyboardState_Previous_TABLE));
        globals::g_IDirectInputDeviceA->Unacquire();
        return;
    }
    if (globals::g_IDirectInputDeviceA != nullptr) {
        HRESULT result;// = 1;
        if (!globals::g_IsDirectInputAcquired) {
            result = 0x8007001e; // probably some specific HRESULT
        }
        else {
            std::memcpy(globals::g_KeyboardState_Previous_TABLE, globals::g_KeyboardState_Current_TABLE, sizeof(globals::g_KeyboardState_Previous_TABLE));
            std::memset(globals::g_KeyboardState_Current_TABLE, 0, sizeof(globals::g_KeyboardState_Current_TABLE));

            result = globals::g_IDirectInputDeviceA->GetDeviceState(sizeof(globals::g_KeyboardState_Current_TABLE), globals::g_KeyboardState_Current_TABLE);
        }
        if (result != 0) {
            globals::g_IsDirectInputAcquired = FALSE;
            if (globals::g_IDirectInputDeviceA->Acquire() == 0) {
                globals::g_IsDirectInputAcquired = TRUE;
            }
        }
    }
}

// <LegoRR.exe @0047f2d0>
void __cdecl lego::input::UpdateMousePosition(void)
{
    RECT clientRect;
    if (GetClientRect(main::globals::g_hWnd, &clientRect)) {
        POINT clientPos = { 0, 0 };
        ClientToScreen(main::globals::g_hWnd, &clientPos);

        POINT mousePos;
        GetCursorPos(&mousePos);
        mousePos.x -= clientPos.x;
        mousePos.y -= clientPos.y;

        if (mousePos.x >= main::globals::g_RESOLUTION.width)
            mousePos.x = main::globals::g_RESOLUTION.width - 1;
        if (mousePos.y >= main::globals::g_RESOLUTION.height)
            mousePos.y = main::globals::g_RESOLUTION.height - 1;

        if (mousePos.x < 0)
            mousePos.x = 0;
        if (mousePos.y < 0)
            mousePos.y = 0;

        globals::g_MouseDeltaPosition.x = mousePos.x - globals::g_MousePosition.x;
        globals::g_MouseDeltaPosition.y = mousePos.y - globals::g_MousePosition.y;
        globals::g_MousePosition.x = mousePos.x;
        globals::g_MousePosition.y = mousePos.y;
    }
}


// <LegoRR.exe @00410a60>
int __cdecl lego::input::GetMousePositionX(void)
{
    return globals::g_MousePosition.x;
}

// <LegoRR.exe @00410a70>
int __cdecl lego::input::GetMousePositionY(void)
{
    return globals::g_MousePosition.y;
}

// <LegoRR.exe @0047f390>
void __cdecl lego::input::SetMousePosition(int x, int y)
{
    POINT client = { 0, 0 };

    ClientToScreen(main::globals::g_hWnd, &client);
    globals::g_MousePosition.y = y;
    globals::g_MousePosition.x = x;
    globals::g_MouseDeltaPosition.x = 0;
    globals::g_MouseDeltaPosition.y = 0;
    SetCursorPos(client.x + x, client.y + y);
    return;
}

// <LegoRR.exe @00410a80>
BOOL __cdecl lego::input::GetBool_0076bb3c(void)
{
    return globals::g_LeftButtonState;
}


// <LegoRR.exe @0047f270>
int __cdecl lego::input::GetNumKeysPressed(void)
{
    int count = 0;
    for (int i = 0; i < 256; i++) {
        if (globals::g_KeyboardState_Current_TABLE[i])
            count++;
    }
    return count;
}

// <LegoRR.exe @0047f290>
void __cdecl lego::input::CleanupDirectInput(void)
{
    if (globals::g_IsDirectInputAcquired) {
        globals::g_IDirectInputDeviceA->Unacquire();
        globals::g_IsDirectInputAcquired = FALSE;
    }

    if (globals::g_IDirectInputDeviceA != nullptr)
        globals::g_IDirectInputDeviceA->Release();

    if (globals::g_IDirectInputA != nullptr)
        globals::g_IDirectInputA->Release();
}

#pragma endregion
