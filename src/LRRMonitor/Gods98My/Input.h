#pragma once

#include "../framework.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

// looked at the win98 joystick stuff and it doesn't let you have more than 4 buttons
#define						MAX_JOYSTICK_BUTTONS		4

#pragma endregion

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

typedef struct
{
	/*00,4*/ BOOL					found;
	/*04,4*/ IDirectInputDevice2A*	dev;
	/*08,10*/ BOOL					buttons[MAX_JOYSTICK_BUTTONS];
	/*18,4*/ int						xaxis;
	/*1c,4*/ int						yaxis;
	/*20*/
} joystickType, *lpjoystickType;
static_assert(sizeof(joystickType) == 0x20, "");


struct DIcallbackData
{
	/*0,4*/ IDirectInputA* di;
	/*4,4*/ HWND hWnd;
	/*8,4*/ joystickType* joystick;
	/*c*/
};
static_assert(sizeof(DIcallbackData) == 0xc, "");


typedef struct _Input_Globs
{
	// Keyboard state
	/*000,100*/ bool prevKey_Map[256];
	/*100,4*/ IDirectInputA* lpdi;
	/*104,4*/ IDirectInputDeviceA* lpdiKeyboard;
	/*108,4*/ IDirectInputDeviceA* lpdiMouse;		// (unused)
	/*10c,4*/ BOOL fKeybdAcquired;
	/*110,4*/ BOOL fMouseAcquired;							// (unused)
	/*114,10*/ RECT MouseBounds;						// Bounding box in which mouse may move
	/*124,4*/ int msx;
	/*128,4*/ int msy;
	/*12c,4*/ int prev_msx;
	/*130,4*/ int prev_msy;		// Current and previous positions of the mouse
	/*134,4*/ int diffx;
	/*138,4*/ int diffy;						// Relative movement of mouse cursor
	/*13c,4*/ BOOL mslb;
	/*140,4*/ BOOL msrb;						// Mouse buttons
	/*144,4*/ BOOL mslblast;
	/*148,4*/ BOOL mslbheld;
	/*14c,4*/ BOOL lClicked;
	/*150,4*/ BOOL rClicked;
	/*154,4*/ BOOL lDoubleClicked;
	/*158,4*/ BOOL rDoubleClicked;
	/*15c,4*/ BOOL caps;
	/*160,10*/ DIMOUSESTATE dims;
	/*170,c*/ DIcallbackData cbd;
	/*17c,1*/ char Input_KeyTemp;
	/*17d,3*/ unsigned char padding1[3];
	/*180,100*/ bool Key_Map[256];
	/*280*/
} Input_Globs;
static_assert(sizeof(Input_Globs) == 0x280, "");

#pragma endregion

/**********************************************************************************
 ******** Globals
 **********************************************************************************/

#pragma region Globals

// <LegoRR.exe @0076ba00>
extern Input_Globs INPUT;

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// External Function Prototypes

// Mouse data
// <LegoRR.exe @00410a60>
__inline int __cdecl msx() { return INPUT.msx; }		// Mouse positions

// <LegoRR.exe @00410a70>
__inline int __cdecl msy() { return INPUT.msy; }

// <LegoRR.exe @00410a80>
__inline BOOL __cdecl mslb() { return INPUT.mslb; }		// Left and right ouse buttons




// Initialise direct input and the key board
// <LegoRR.exe @0047f050>
BOOL __cdecl Input_InitKeysAndDI(void);

// Read the key board (called from message peek)
// <LegoRR.exe @0047f1b0>
void __cdecl Input_ReadKeys(void);

// Any key pressed
// <LegoRR.exe @0047f270>
unsigned long __cdecl Input_AnyKeyPressed(void);

// Release the keys and direct input
// <LegoRR.exe @0047f290>
void __cdecl Input_ReleaseKeysAndDI(void);

// Read the mouse state
// <LegoRR.exe @0047f2d0>
void __cdecl Input_ReadMouse2(void);

// <LegoRR.exe @0047f390>
BOOL __cdecl Input_SetCursorPos(int x, int y);



//__inline int __cdecl msxr() { return INPUT.diffx; }		// Relative mouse movement
//__inline int __cdecl msyr() { return INPUT.diffy; }

/*__inline BOOL __cdecl msrb() { return INPUT.msrb; }
__inline BOOL __cdecl mslbheld() { return INPUT.mslbheld; }
__inline BOOL __cdecl Input_LClicked() { return INPUT.lClicked; }*/


// Initialize the mouse
BOOL __cdecl Input_InitMouse(BOOL GrabExclusiveAccess, int sx, int sy, RECT Bounds);

/*// Release the mouse
void __cdecl Input_ReleaseMouse(void);


extern	BOOL			ReadJoystickInput(lpjoystickType	joystick);
extern	BOOL			InitJoystick(HINSTANCE hInst, HWND hWnd, lpjoystickType joystick);

extern	HRESULT			SetDIDwordProperty(LPDIRECTINPUTDEVICE pdev, REFGUID guidProperty, DWORD dwObject, DWORD dwHow, DWORD dwValue);
extern	BOOL CALLBACK	InitJoystickInput(LPCDIDEVICEINSTANCE pdinst, LPVOID pvRef);

extern	BOOL			ReacquireInput(lpjoystickType joystick);
extern	void			CleanupJoystickInput(lpjoystickType joystick);

extern	BOOL			IsJoystickInitialised(lpjoystickType joystick);
extern	void			Input_ClearClicked(void);
extern	UCHAR			Input_GetAsciiFromScanCode(ULONG i);


VOID Input_ReadMouse2(VOID);*/

// Static Function Prototypes


//extern UCHAR Input_KeyTemp;
//#define Input_KeyHit(k)			(Input_KeyTemp=prevKey_Map[(k)],prevKey_Map[(k)]=Key_Map[(k)],Key_Map[(k)]&&(Key_Map[(k)]^Input_KeyTemp))
//#define Input_KeyReleased(k)	(Input_KeyTemp=prevKey_Map[(k)],prevKey_Map[(k)]=Key_Map[(k)],(!Key_Map[(k)])&&(Key_Map[(k)]^Input_KeyTemp))
#define Input_KeyHit(k)			(INPUT.Key_Map[(k)]&&(INPUT.Key_Map[(k)]^INPUT.prevKey_Map[(k)]))
#define Input_KeyReleased(k)	((!INPUT.Key_Map[(k)])&&(INPUT.Key_Map[(k)]^INPUT.prevKey_Map[(k)]))
#define Input_KeyIsDown(k)		INPUT.Key_Map[(k)]
#define Input_ClearAllKeys()	std::memset(INPUT.Key_Map, 0, sizeof(INPUT.Key_Map));

#pragma endregion

}

