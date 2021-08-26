////////////////////////////////////////////////////
// Input handling routines
////////////////////////////////////////////////////

#ifndef _INPUT_H
#define _INPUT_H

#include "Standard.h"
#include "Main.h"
#include "Keys.h"

#ifdef _GODS98COMPILE
#include <dinput.h>
#else
typedef LPVOID LPDIRECTINPUT;
typedef LPVOID LPDIRECTINPUTDEVICE;
typedef LPVOID LPDIRECTINPUTDEVICE2;
typedef LPVOID LPCDIDEVICEINSTANCE;

typedef struct _DIMOUSESTATE {
    ULONG    lX;
    ULONG    lY;
    ULONG    lZ;
    UCHAR    rgbButtons[4];
} DIMOUSESTATE, *LPDIMOUSESTATE;

#endif // _GODS98COMPILE

//#ifndef CHKDI_F
//#define CHKDI_F(e)	(e)
//#endif // CHKDI_F

#ifdef __cplusplus
extern "C" {
#endif

// Defines

// looked at the win98 joystick stuff and it doesn't let you have more than 4 buttons
#define						MAX_JOYSTICK_BUTTONS		4		


// Types
typedef struct
{
	BOOL					found;
	LPDIRECTINPUTDEVICE2	dev;
	BOOL					buttons[MAX_JOYSTICK_BUTTONS];
	int						xaxis;
	int						yaxis;

}joystickType, *lpjoystickType;


typedef struct _Input_Globs
{
	LPDIRECTINPUT lpdi;
	LPDIRECTINPUTDEVICE lpdiKeyboard;
	LPDIRECTINPUTDEVICE lpdiMouse;
	BOOL fKeybdAcquired, fMouseAcquired;
	RECT MouseBounds;						// Bounding box in which mouse may move
	int msx, msy, prev_msx, prev_msy;		// Current and previous positions of the mouse
	int diffx, diffy;						// Relative movement of mouse cursor
	BOOL mslb, msrb;						// Mouse buttons
	BOOL mslblast, mslbheld;
	BOOL lClicked, rClicked;
	BOOL lDoubleClicked, rDoubleClicked;
	BOOL caps;
	DIMOUSESTATE dims;
} Input_Globs;

extern Input_Globs INPUT;

// Variables

// Keyboard state
extern UCHAR Key_Map[256];
extern UCHAR prevKey_Map[256];
// Input vars

// External Function Prototypes

// Initialise direct input and the key board
extern BOOL Input_InitKeysAndDI(void);
// Read the key board (called from message peek)
extern void Input_ReadKeys(void);
// Release the keys and direct input
extern void Input_ReleaseKeysAndDI(void);
// Read the mouse state
extern void Input_ReadMouse(void);
// Initialize the mouse
extern BOOL Input_InitMouse(BOOL GrabExclusiveAccess, int sx, int sy, RECT Bounds);
// Release the mouse
extern void Input_ReleaseMouse(void);
// Any key pressed
extern ULONG Input_AnyKeyPressed(void);

extern BOOL Input_SetCursorPos( int x, int y );



extern	BOOL			ReadJoystickInput(lpjoystickType	joystick);
extern	BOOL			InitJoystick(HINSTANCE hInst, HWND hWnd, lpjoystickType joystick);

extern	HRESULT			SetDIDwordProperty(LPDIRECTINPUTDEVICE pdev, REFGUID guidProperty, DWORD dwObject, DWORD dwHow, DWORD dwValue);
extern	BOOL CALLBACK	InitJoystickInput(LPCDIDEVICEINSTANCE pdinst, LPVOID pvRef);

extern	BOOL			ReacquireInput(lpjoystickType joystick);
extern	void			CleanupJoystickInput(lpjoystickType joystick);

extern	BOOL			IsJoystickInitialised(lpjoystickType joystick);
extern	void			Input_ClearClicked(void);
extern	UCHAR			Input_GetAsciiFromScanCode(ULONG i);


VOID Input_ReadMouse2(VOID);

// Mouse data
__inline int msx()				{ return INPUT.msx; }		// Mouse positions
__inline int msy()				{ return INPUT.msy; }
__inline int msxr()				{ return INPUT.diffx; }		// Relative mouse movement
__inline int msyr()				{ return INPUT.diffy; }
__inline BOOL mslb()			{ return INPUT.mslb; }		// Left and right ouse buttons
__inline BOOL msrb()			{ return INPUT.msrb; }
__inline BOOL mslbheld()		{ return INPUT.mslbheld; }
__inline BOOL Input_LClicked()	{ return INPUT.lClicked; }

// Static Function Prototypes

#ifdef __cplusplus
}
#endif

extern UCHAR Input_KeyTemp;
//#define Input_KeyHit(k)			(Input_KeyTemp=prevKey_Map[(k)],prevKey_Map[(k)]=Key_Map[(k)],Key_Map[(k)]&&(Key_Map[(k)]^Input_KeyTemp))
//#define Input_KeyReleased(k)	(Input_KeyTemp=prevKey_Map[(k)],prevKey_Map[(k)]=Key_Map[(k)],(!Key_Map[(k)])&&(Key_Map[(k)]^Input_KeyTemp))
#define Input_KeyHit(k)			(Key_Map[(k)]&&(Key_Map[(k)]^prevKey_Map[(k)]))
#define Input_KeyReleased(k)	((!Key_Map[(k)])&&(Key_Map[(k)]^prevKey_Map[(k)]))
#define Input_KeyIsDown(k)		Key_Map[(k)]
#define Input_ClearAllKeys()	memset(Key_Map, 0, sizeof(Key_Map));

#endif
