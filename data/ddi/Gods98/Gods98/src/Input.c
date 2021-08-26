////////////////////////////////////////////////////
// Input handling routines
////////////////////////////////////////////////////

#include <d3drmwin.h>

#define _JOYSTICK_MODULE

#include "..\Inc\Standard.h"
#include "..\Inc\Input.h"
#include "..\Inc\Main.h"
#include "..\Inc\Errors.h"
#include "..\Inc\dxbug.h"

#pragma comment ( lib, "dinput" )

UCHAR Input_KeyTemp;
UCHAR Key_Map[256], prevKey_Map[256];
Input_Globs INPUT;

// this table is used for keys WITHOUT shift
SLONG Input_scanToAsciiText[256] = 
{
	 0,													// 0x00
	 0, // KEY_ESCAPE			0x001
	'1',// KEY_ONE				0x002
	'2',// KEY_TWO				0x003
	'3',// KEY_THREE			0x004
	'4',// KEY_FOUR				0x005
	'5',// KEY_FIVE				0x006
	'6',// KEY_SIX				0x007
	'7',// KEY_SEVEN			0x008
	'8',// KEY_EIGHT			0x009
	'9',// KEY_NINE				0x00A
	'0',// KEY_ZERO				0x00B
	'-',// KEY_MINUS			0x00C
	'=',// KEY_EQUALS			0x00D
	 0, // KEY_BACKSPACE		0x00E
	 0, // KEY_TAB				0x00F
	'q',// KEY_Q				0x010
	'w',// KEY_W				0x011
	'e',// KEY_E				0x012
	'r',// KEY_R				0x013
	't',// KEY_T				0x014
	'y',// KEY_Y				0x015
	'u',// KEY_U				0x016
	'i',// KEY_I				0x017
	'o',// KEY_O				0x018
	'p',// KEY_P				0x019
	 0, // KEY_LEFTBRACE		0x01A
	 0, // KEY_RIGHTBRACE		0x01B
	13, // KEY_RETURN			0x01C
	 0, // KEY_LEFTCTRL			0x01D
	'a',// KEY_A				0x01E
	's',// KEY_S				0x01F
	'd',// KEY_D				0x020
	'f',// KEY_F				0x021
	'g',// KEY_G				0x022
	'h',// KEY_H				0x023
	'j',// KEY_J				0x024
	'k',// KEY_K				0x025
	'l',// KEY_L				0x026
	';',// KEY_SEMICOLON		0x027
	0x27,// KEY_AT				0x028
	 0, // KEY_RSINGLEQUOTE		0x029
	 0, // KEY_LEFTSHIFT		0x02A
	 0, // KEY_HASH				0x02B
	'z',// KEY_Z				0x02C
	'x',// KEY_X				0x02D
	'c',// KEY_C				0x02E
	'v',// KEY_V				0x02F
	'b',// KEY_B				0x030
	'n',// KEY_N				0x031
	'm',// KEY_M				0x032
	',',// KEY_LEFTARROW		0x033
	'.',// KEY_RIGHTARROW		0x034
	'/',// KEY_QUESTIONMARK		0x035
	 0, // KEY_RIGHTSHIFT		0x036
	'*',// KEYPAD_ASTERISK		0x037
	 0, // KEY_ALT				0x038
	' ',// KEY_SPACE			0x039
	 0, // KEY_CAPLOCK			0x03A
	 0, // KEY_F1				0x03B
	 0, // KEY_F2				0x03C
	 0, // KEY_F3				0x03D
	 0, // KEY_F4				0x03E
	 0, // KEY_F5				0x03F
	 0, // KEY_F6				0x040
	 0, // KEY_F7				0x041
	 0, // KEY_F8				0x042
	 0, // KEY_F9				0x043
	 0, // KEY_F10				0x044
	 0, // KEYPAD_NUMLOCK		0x045
	 0, // KEY_SCROLLLOCK		0x046
	'7',// KEYPAD_7				0x047
	'8',// KEYPAD_8				0x048
	'9',// KEYPAD_9				0x049
	'-',// KEYPAD_MINUS			0x04A
	'4',// KEYPAD_4				0x04B
	'5',// KEYPAD_5				0x04C
	'6',// KEYPAD_6				0x04D
	'+',// KEYPAD_PLUS			0x04E
	'1',// KEYPAD_1				0x04F
	'2',// KEYPAD_2				0x050
	'3',// KEYPAD_3				0x051
	'0',// KEYPAD_0				0x052
	 0, // KEYPAD_DELETE		0x053
	0x5c, // KEY_BACKSLASH		0x056
	 0, // KEY_F11				0x057
	 0, // KEY_F12				0x058
	 0, 0, 0, 0, 0, 0, 0,								// 0x59-0x5F
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 0x60-0x6F
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 0x70-0x7F
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 0x80-0x8F
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,				// 0x90-0x9B
	 0, // KEYPAD_ENTER			0x09C
	 0, // KEY_RIGHTCTRL		0x09D
	 0, 0,												// 0x9E-0x9F
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 0xA0-0xAF
	 0, 0, 0, 0, 0,										// 0xB0-0xB4
	'/', // KEYPAD_FORWARDSLASH	0x0B5
	 0,													// 0xB6
	 0, // KEY_PRINTSCREEN		0x0B7
	 0, // KEY_ALTGR			0x0B8
	 0, 0, 0, 0, 0, 0, 0,								// 0XB9-0XBF
	 0, 0, 0, 0, 0, 0, 0,								// 0XC0-0XC6
	 0, // KEY_HOME				0x0C7
	 0, // KEY_CURSORUP			0x0C8
	 0, // KEY_PGUP				0x0C9
	 0,													// 0xCA
	 0, // KEY_CURSORLEFT		0x0CB
	 0,													// 0xCC
	 0, // KEY_CURSORRIGHT		0x0CD
	 0,													// 0xCE
	 0, // KEY_END				0x0CF
	 0, // KEY_CURSORDOWN		0x0D0
	 0, // KEY_PGDN				0x0D1
	 0, // KEY_INSERT			0x0D2
	 0,  // KEY_DELETE			0x0D3
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,				// 0xD4-0xDF
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 0xE0-0xEF
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0		// 0xF0-0xFF
};

// use this one if you're holding SHIFT down
SLONG Input_scanToAsciiTextWithShift[256] = 
{
	 0,													// 0x00
	 0, // KEY_ESCAPE			0x001
	'!',// KEY_ONE				0x002
	'"',// KEY_TWO				0x003
	'£',// KEY_THREE			0x004
	'$',// KEY_FOUR				0x005
	'%',// KEY_FIVE				0x006
	'^',// KEY_SIX				0x007
	'&',// KEY_SEVEN			0x008
	'*',// KEY_EIGHT			0x009
	'(',// KEY_NINE				0x00A
	')',// KEY_ZERO				0x00B
	'_',// KEY_MINUS			0x00C
	'+',// KEY_EQUALS			0x00D
	 0, // KEY_BACKSPACE		0x00E
	 0, // KEY_TAB				0x00F
	'Q',// KEY_Q				0x010
	'W',// KEY_W				0x011
	'E',// KEY_E				0x012
	'R',// KEY_R				0x013
	'T',// KEY_T				0x014
	'Y',// KEY_Y				0x015
	'U',// KEY_U				0x016
	'I',// KEY_I				0x017
	'O',// KEY_O				0x018
	'P',// KEY_P				0x019
	 0, // KEY_LEFTBRACE		0x01A
	 0, // KEY_RIGHTBRACE		0x01B
	13, // KEY_RETURN			0x01C
	 0, // KEY_LEFTCTRL			0x01D
	'A',// KEY_A				0x01E
	'S',// KEY_S				0x01F
	'D',// KEY_D				0x020
	'F',// KEY_F				0x021
	'G',// KEY_G				0x022
	'H',// KEY_H				0x023
	'J',// KEY_J				0x024
	'K',// KEY_K				0x025
	'L',// KEY_L				0x026
	':',// KEY_SEMICOLON		0x027
	'@',// KEY_AT				0x028
	 0, // KEY_RSINGLEQUOTE		0x029
	 0, // KEY_LEFTSHIFT		0x02A
	 0, // KEY_HASH				0x02B
	'Z',// KEY_Z				0x02C
	'X',// KEY_X				0x02D
	'C',// KEY_C				0x02E
	'V',// KEY_V				0x02F
	'B',// KEY_B				0x030
	'N',// KEY_N				0x031
	'M',// KEY_M				0x032
	'<',// KEY_LEFTARROW		0x033
	'>',// KEY_RIGHTARROW		0x034
	'?',// KEY_QUESTIONMARK		0x035
	 0, // KEY_RIGHTSHIFT		0x036
	'*',// KEYPAD_ASTERISK		0x037
	 0, // KEY_ALT				0x038
	' ',// KEY_SPACE			0x039
	 0, // KEY_CAPLOCK			0x03A
	 0, // KEY_F1				0x03B
	 0, // KEY_F2				0x03C
	 0, // KEY_F3				0x03D
	 0, // KEY_F4				0x03E
	 0, // KEY_F5				0x03F
	 0, // KEY_F6				0x040
	 0, // KEY_F7				0x041
	 0, // KEY_F8				0x042
	 0, // KEY_F9				0x043
	 0, // KEY_F10				0x044
	 0, // KEYPAD_NUMLOCK		0x045
	 0, // KEY_SCROLLLOCK		0x046
	'7',// KEYPAD_7				0x047
	'8',// KEYPAD_8				0x048
	'9',// KEYPAD_9				0x049
	'-',// KEYPAD_MINUS			0x04A
	'4',// KEYPAD_4				0x04B
	'5',// KEYPAD_5				0x04C
	'6',// KEYPAD_6				0x04D
	'+',// KEYPAD_PLUS			0x04E
	'1',// KEYPAD_1				0x04F
	'2',// KEYPAD_2				0x050
	'3',// KEYPAD_3				0x051
	'0',// KEYPAD_0				0x052
	 0, // KEYPAD_DELETE		0x053
	'\\',// KEY_BACKSLASH		0x056
	 0, // KEY_F11				0x057
	 0, // KEY_F12				0x058
	 0, 0, 0, 0, 0, 0, 0,								// 0x59-0x5F
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 0x60-0x6F
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 0x70-0x7F
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 0x80-0x8F
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,				// 0x90-0x9B
	 0, // KEYPAD_ENTER			0x09C
	 0, // KEY_RIGHTCTRL		0x09D
	 0, 0,												// 0x9E-0x9F
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 0xA0-0xAF
	 0, 0, 0, 0, 0,										// 0xB0-0xB4
	'/', // KEYPAD_FORWARDSLASH	0x0B5
	 0,													// 0xB6
	 0, // KEY_PRINTSCREEN		0x0B7
	 0, // KEY_ALTGR			0x0B8
	 0, 0, 0, 0, 0, 0, 0,								// 0XB9-0XBF
	 0, 0, 0, 0, 0, 0, 0,								// 0XC0-0XC6
	 0, // KEY_HOME				0x0C7
	 0, // KEY_CURSORUP			0x0C8
	 0, // KEY_PGUP				0x0C9
	 0,													// 0xCA
	 0, // KEY_CURSORLEFT		0x0CB
	 0,													// 0xCC
	 0, // KEY_CURSORRIGHT		0x0CD
	 0,													// 0xCE
	 0, // KEY_END				0x0CF
	 0, // KEY_CURSORDOWN		0x0D0
	 0, // KEY_PGDN				0x0D1
	 0, // KEY_INSERT			0x0D2
	 0,  // KEY_DELETE			0x0D3
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,				// 0xD4-0xDF
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 0xE0-0xEF
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0		// 0xF0-0xFF
};

UCHAR Input_GetAsciiFromScanCode(ULONG i) 
{
	// don't forget to check for shift being down

	if ((Input_KeyIsDown(KEY_LEFTSHIFT)) || (Input_KeyIsDown(KEY_RIGHTSHIFT)))
	{
		return (UCHAR)Input_scanToAsciiTextWithShift[i];		
	}
	else
	{
		return (UCHAR)Input_scanToAsciiText[i];
	}

return (UCHAR) 0;
}

BOOL Input_InitMouse(BOOL GrabExclusiveAccess, int sx, int sy, RECT Bounds)
{
	GUID guid = GUID_SysMouse;

	// Check for the direct input object and the correctness of the input parameters.
	if (!INPUT.lpdi) return FALSE;
	if (sx < Bounds.left || sx > Bounds.right || sy < Bounds.top || sy > Bounds.bottom) return FALSE;

	// Create the mouse
	if (INPUT.lpdi->lpVtbl->CreateDevice(INPUT.lpdi, &guid, &INPUT.lpdiMouse, NULL) != DI_OK) return FALSE;

	// Set the mouse data format
	if (INPUT.lpdiMouse->lpVtbl->SetDataFormat(INPUT.lpdiMouse, &c_dfDIMouse) != DI_OK) return FALSE;

	// Set cooperative level for mouse
	if (GrabExclusiveAccess)
	{
		if (INPUT.lpdiMouse->lpVtbl->SetCooperativeLevel(INPUT.lpdiMouse, Main_hWnd(), DISCL_EXCLUSIVE | DISCL_FOREGROUND) != DI_OK) return FALSE;
	}
	else
	{
		if (INPUT.lpdiMouse->lpVtbl->SetCooperativeLevel(INPUT.lpdiMouse, Main_hWnd(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND) != DI_OK) return FALSE;
	}

    // try to acquire the mouse
   if (INPUT.lpdiMouse->lpVtbl->Acquire(INPUT.lpdiMouse) != DI_OK) INPUT.fMouseAcquired = TRUE;
   else INPUT.fMouseAcquired = FALSE;

   // Fill out initial data about the mouse
   INPUT.msx			= sx;
   INPUT.prev_msx		= sx;
   INPUT.msy			= sy;
   INPUT.prev_msy		= sy;
   INPUT.MouseBounds	= Bounds;

	INPUT.mslblast = FALSE;

   return TRUE;
}

void Input_ReadMouse(void)
{
	// Is the mouse object setup?
	if (!INPUT.lpdiMouse) return;
	
	// If we have the mouse then read its state
	if (INPUT.fMouseAcquired)
	{
		if (INPUT.lpdiMouse->lpVtbl->GetDeviceState(INPUT.lpdiMouse, sizeof(DIMOUSESTATE), &INPUT.dims) == DI_OK)
		{
			// Read mouse positon data and correct it to the bounding box
			INPUT.diffx = INPUT.dims.lX;
			INPUT.diffy = INPUT.dims.lY;
			INPUT.prev_msx = INPUT.msx;
			INPUT.prev_msy = INPUT.msy;
			INPUT.msx += INPUT.dims.lX;
			INPUT.msy += INPUT.dims.lY;
			if (INPUT.msx > INPUT.MouseBounds.right)	INPUT.msx = INPUT.MouseBounds.right;
			if (INPUT.msy > INPUT.MouseBounds.bottom)	INPUT.msy = INPUT.MouseBounds.bottom;
			if (INPUT.msx < INPUT.MouseBounds.left)		INPUT.msx = INPUT.MouseBounds.left;
			if (INPUT.msy < INPUT.MouseBounds.top)		INPUT.msy = INPUT.MouseBounds.top;

			// Read the button press data
			INPUT.mslb = INPUT.dims.rgbButtons[0] ? TRUE : FALSE;
			INPUT.msrb = INPUT.dims.rgbButtons[1] ? TRUE : FALSE;


			if (INPUT.mslblast && INPUT.mslb) INPUT.mslbheld = TRUE;
			else INPUT.mslbheld = FALSE;
			INPUT.mslblast = INPUT.mslb;
		}
		else INPUT.fMouseAcquired = FALSE;
	} 
	else 
	{
		HRESULT r;
		if ((r = INPUT.lpdiMouse->lpVtbl->Acquire(INPUT.lpdiMouse)) == DI_OK) INPUT.fMouseAcquired = TRUE;
		else INPUT.fMouseAcquired = FALSE;
	}
}

void Input_ClearClicked(void)
{
	INPUT.lClicked = FALSE;
	INPUT.rClicked = FALSE;
}


void Input_ReleaseMouse(void)
{
	// If we have control over the mouse then release it first
	if(INPUT.fMouseAcquired)
	{
		INPUT.lpdiMouse->lpVtbl->Unacquire(INPUT.lpdiMouse);
		INPUT.fMouseAcquired = FALSE;
	}
	
	// If the mouse object exsits then release it
	if(INPUT.lpdiMouse != NULL) INPUT.lpdiMouse->lpVtbl->Release(INPUT.lpdiMouse);
}

BOOL Input_InitKeysAndDI(void)
{
	GUID guid = GUID_SysKeyboard;
	HRESULT  hRes;

	// Try to create DI object
	CHKDI_F(DirectInputCreate(Main_hInst(), DIRECTINPUT_VERSION, &INPUT.lpdi, NULL));

	// Try to create keyboard device
	CHKDI_F(INPUT.lpdi->lpVtbl->CreateDevice(INPUT.lpdi, &guid, &INPUT.lpdiKeyboard, NULL));

	// Tell DirectInput that we want to receive data in keyboard format
	CHKDI_F(INPUT.lpdiKeyboard->lpVtbl->SetDataFormat(INPUT.lpdiKeyboard, &c_dfDIKeyboard));

	// set cooperative level for keyboard
	CHKDI_F(INPUT.lpdiKeyboard->lpVtbl->SetCooperativeLevel(INPUT.lpdiKeyboard, Main_hWnd(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND));

	// Try to acquire the keyboard
	hRes = INPUT.lpdiKeyboard->lpVtbl->Acquire(INPUT.lpdiKeyboard);
	if (hRes == DI_OK) INPUT.fKeybdAcquired = TRUE;
	else INPUT.fKeybdAcquired = FALSE;

	// if we get here, all objects were created successfully
	return TRUE;
}

void Input_ReadKeys()
{
	HRESULT hRes;
	USHORT us = 0;

	if (!(Main_FullScreen() ? TRUE : Main_AppActive()))
	{
		// Zero out the keymaps.
		memset(Key_Map, 0, 256);
		memset(prevKey_Map, 0, 256);
		INPUT.lpdiKeyboard->lpVtbl->Unacquire(INPUT.lpdiKeyboard);
		return;
	}

	// Is the key device set up?
	if (!INPUT.lpdiKeyboard) return;

	if (INPUT.fKeybdAcquired)
	{
		// Zero key map entries
		memcpy(prevKey_Map, Key_Map, 256);
		memset(Key_Map, 0, 256);
		hRes = INPUT.lpdiKeyboard->lpVtbl->GetDeviceState(INPUT.lpdiKeyboard, sizeof(Key_Map), Key_Map);
	}
	else hRes = DIERR_INPUTLOST;

	if (hRes != DI_OK)
	{
		// Opps, we lost control of the keyboard, reacquire
		INPUT.fKeybdAcquired = FALSE;
		if (INPUT.lpdiKeyboard->lpVtbl->Acquire(INPUT.lpdiKeyboard) == DI_OK) INPUT.fKeybdAcquired = TRUE;
	}

	// failed to read the keyboard, so just return and hope it comes back!
	return;
}

ULONG Input_AnyKeyPressed(void)
{
	ULONG ret, i, l;
	LPUCHAR lp;
	ret = 0;
	
	l=sizeof(Key_Map);
	lp = Key_Map;
	for (i=0;i<l;i++)
	{
		if(*lp)
			ret++;
		lp++;
	}
	return ret;
}
void Input_ReleaseKeysAndDI(void)
{
	// If we have control over the keyboard then release it first
	if(INPUT.fKeybdAcquired)
	{
		INPUT.lpdiKeyboard->lpVtbl->Unacquire(INPUT.lpdiKeyboard);
		INPUT.fKeybdAcquired = FALSE;
	}
	
	// If the keyboard object exsits then release it
	if(INPUT.lpdiKeyboard != NULL) INPUT.lpdiKeyboard->lpVtbl->Release(INPUT.lpdiKeyboard);

	// If the direct input object exsits then release it
	if(INPUT.lpdi != NULL) INPUT.lpdi->lpVtbl->Release(INPUT.lpdi);	
}

VOID Input_ReadMouse2(VOID){
	
	RECT rect;
	POINT clientPos, cursorPos;
		
	if (GetClientRect(Main_hWnd(), &rect)){

		clientPos.x = clientPos.y = 0;
		ClientToScreen(Main_hWnd(), &clientPos);
		GetCursorPos(&cursorPos);

		cursorPos.x -= clientPos.x;
		cursorPos.y -= clientPos.y;
	
		if (cursorPos.x >= appWidth()) cursorPos.x = appWidth() - 1;
		if (cursorPos.y >= appHeight()) cursorPos.y = appHeight() - 1;
		if (cursorPos.x < 0) cursorPos.x = 0;
		if (cursorPos.y < 0) cursorPos.y = 0;

		INPUT.diffx = cursorPos.x - INPUT.msx;
		INPUT.diffy = cursorPos.y - INPUT.msy;
		INPUT.msx = cursorPos.x;
		INPUT.msy = cursorPos.y;

	}
}


BOOL Input_SetCursorPos( int x, int y )
{
	POINT clientPos;


	clientPos.x = clientPos.y = 0;
	ClientToScreen(Main_hWnd(), &clientPos );

	INPUT.msx = x;
	INPUT.msy = y;
	INPUT.diffx = 0;
	INPUT.diffy = 0;

	x += clientPos.x;
	y += clientPos.y;

	return SetCursorPos( x, y );

}




/*--------------------------------------------------------------------------
|
| joytick code here
|
*-------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
|
| SetDIDwordProperty
|
| Set a DWORD property on a DirectInputDevice.
|
*-------------------------------------------------------------------------*/

HRESULT SetDIDwordProperty(LPDIRECTINPUTDEVICE pdev, REFGUID guidProperty,
						   DWORD dwObject, DWORD dwHow, DWORD dwValue)
{
	DIPROPDWORD dipdw;
	
	dipdw.diph.dwSize		= sizeof(dipdw);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
	dipdw.diph.dwObj		= dwObject;
	dipdw.diph.dwHow		= dwHow;
	dipdw.dwData			= dwValue;
	
	return pdev->lpVtbl->SetProperty(pdev, guidProperty, &dipdw.diph);
}

/*--------------------------------------------------------------------------
| ReacquireInput
|
| Reacquires the current input device.	If Acquire() returns S_FALSE,
| that means
| that we are already acquired and that DirectInput did nothing.
*-------------------------------------------------------------------------*/
BOOL ReacquireInput(lpjoystickType joystick)
{
	HRESULT hRes;
	
	// Is there actually a joystick
	if (!joystick->found) return FALSE;
	
	// if we have a current device
	if(joystick->dev)
	{
		// acquire the device
		hRes = IDirectInputDevice_Acquire(joystick->dev);
		if(SUCCEEDED(hRes))
		{
			// acquisition successful
			return TRUE;
		}
		else
		{
			// acquisition failed
			return FALSE;
		}
	}
	else
	{
		// we don't have a current device
		return FALSE;
	}
	
}

/*--------------------------------------------------------------------------
| InitJoystickInput
|
| Initializes DirectInput for an enumerated joystick device.
| Creates the device, device, sets the standard joystick data format,
| sets the cooperative level and adds it to the menu.
|
| If any step fails, just skip the device and go on to the next one.
|
*-------------------------------------------------------------------------*/

struct DIcallbackData
{
	LPDIRECTINPUT di;
	HWND hWnd;
	lpjoystickType joystick;
};

struct DIcallbackData cbd;

BOOL CALLBACK InitJoystickInput(LPCDIDEVICEINSTANCE pdinst, LPVOID pvRef)
{
	LPDIRECTINPUT pdi = ((struct DIcallbackData *)pvRef)->di;
	LPDIRECTINPUTDEVICE pdev;
	DIPROPRANGE diprg;
	
	lpjoystickType joystick=((struct DIcallbackData *)pvRef)->joystick;

	// create the DirectInput joystick device
	if(pdi->lpVtbl->CreateDevice(pdi, &pdinst->guidInstance, &pdev, NULL) != DI_OK)
	{
//		DBUG_WARN(TRUE, "IDirectInput::CreateDevice FAILED");
		return DIENUM_CONTINUE;
	}
	
	// set joystick data format
	if(pdev->lpVtbl->SetDataFormat(pdev, &c_dfDIJoystick) != DI_OK)
	{
//		DBUG_WARN(TRUE, "IDirectInputDevice::SetDataFormat FAILED");
		pdev->lpVtbl->Release(pdev);
		return DIENUM_CONTINUE;
	}
	
	// set the cooperative level
	if(pdev->lpVtbl->SetCooperativeLevel(pdev, ((struct DIcallbackData *)pvRef)->hWnd,
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND) != DI_OK)
	{
//		DBUG_WARN(TRUE, "IDirectInputDevice::SetCooperativeLevel FAILED");
		pdev->lpVtbl->Release(pdev);
		return DIENUM_CONTINUE;
	}
	
	// set X-axis range to (-1000 ... +1000)
	// This lets us test against 0 to see which way the stick is pointed.
	
	diprg.diph.dwSize		= sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwObj		= DIJOFS_X;
	diprg.diph.dwHow		= DIPH_BYOFFSET;
	diprg.lMin				= -1000;
	diprg.lMax				= +1000;
	
	if(pdev->lpVtbl->SetProperty(pdev, DIPROP_RANGE, &diprg.diph) != DI_OK)
	{
//		DBUG_WARN(TRUE, "IDirectInputDevice::SetProperty(DIPH_RANGE) FAILED");
		pdev->lpVtbl->Release(pdev);
		return FALSE;
	}
	
	//
	// And again for Y-axis range
	//
	diprg.diph.dwObj		= DIJOFS_Y;
	
	if(pdev->lpVtbl->SetProperty(pdev, DIPROP_RANGE, &diprg.diph) != DI_OK)
	{
//		DBUG_WARN(TRUE, "IDirectInputDevice::SetProperty(DIPH_RANGE) FAILED");
			pdev->lpVtbl->Release(pdev);
		return FALSE;
	}
	
	// set X axis dead zone to something very very small
	if (SetDIDwordProperty(pdev, DIPROP_DEADZONE, DIJOFS_X, DIPH_BYOFFSET, 1) != DI_OK)
	{
//		DBUG_WARN(TRUE, "IDirectInputDevice::SetProperty(DIPH_DEADZONE) FAILED");
		pdev->lpVtbl->Release(pdev);
		return FALSE;
	}
	
	
	// set Y axis dead zone to something very very small.
	if (SetDIDwordProperty(pdev, DIPROP_DEADZONE, DIJOFS_Y, DIPH_BYOFFSET, 1) != DI_OK)
	{
//		DBUG_WARN(TRUE, "IDirectInputDevice::SetProperty(DIPH_DEADZONE) FAILED");
		pdev->lpVtbl->Release(pdev);
		return FALSE;
	}
	
	// Record the joystick
	joystick->dev = NULL;
	pdev->lpVtbl->QueryInterface(pdev, &IID_IDirectInputDevice2, &joystick->dev);
	if (joystick->dev)
	{
		joystick->found = TRUE;
//		joystick.found = FALSE;
		pdev->lpVtbl->Release(pdev);
		return DIENUM_STOP;
	}
	else 
	{
		pdev->lpVtbl->Release(pdev);
		return DIENUM_CONTINUE;
	}
}

/*--------------------------------------------------------------------------
| ReadJoystickInput
|
| Requests joystick data and performs any needed processing.
|
*-------------------------------------------------------------------------*/

BOOL ReadJoystickInput(lpjoystickType	joystick)
{
	HRESULT 				hRes;
	DIJOYSTATE				js;

	if (!joystick->found) return FALSE;

	// poll the joystick to read the current state
	hRes = IDirectInputDevice2_Poll(joystick->dev);
	
	// get data from the joystick
	hRes = IDirectInputDevice_GetDeviceState(joystick->dev, sizeof(DIJOYSTATE), &js);
	
	if(hRes != DI_OK)
	{
		// did the read fail because we lost input for some reason?
		// if so, then attempt to reacquire.  If the second acquire
		// fails, then the error from GetDeviceData will be
		// DIERR_NOTACQUIRED, so we won't get stuck an infinite loop.
		if(hRes == DIERR_INPUTLOST)			ReacquireInput(joystick);
		
		// return the fact that we did not read any data
		return FALSE;
	}
	
	//
	// Now study the position of the stick and the buttons.
	//
	
	joystick->xaxis = js.lX;
	joystick->yaxis = -js.lY;
	
	if (js.rgbButtons[0] & 0x80) 
		joystick->buttons[0] = TRUE;
	else
		joystick->buttons[0] = FALSE;
	
	if (js.rgbButtons[1] & 0x80) 
		joystick->buttons[1] = TRUE;
	else
		joystick->buttons[1] = FALSE;	

	return TRUE;
}

BOOL InitJoystick(HINSTANCE hInst, HWND hWnd, lpjoystickType joystick)
{
   LPDIRECTINPUT pdi;

	// create the DirectInput 5.0 interface object
	if(DirectInputCreate(hInst, DIRECTINPUT_VERSION, &pdi, NULL) == DI_OK)
	{
		// Fill out the enumeration structure
		cbd.di = pdi;
		cbd.hWnd = hWnd;
		cbd.joystick=joystick;
		pdi->lpVtbl->EnumDevices(pdi, DIDEVTYPE_JOYSTICK,
								 InitJoystickInput, &cbd, DIEDFL_ATTACHEDONLY);
		pdi->lpVtbl->Release(pdi);    // Finished with DX 5.0.
		// Did we find a joystick?
		if (joystick->found) 
		{
			ReacquireInput(joystick);
			return TRUE;
		}
		else return FALSE;
	}
	else 
	{
//		DBUG_WARN(TRUE, "No joystick support.  At least DirectInput V5 needed.");
		return FALSE;
	}
}

/*--------------------------------------------------------------------------
| CleanupInput
|
| Cleans up all DirectInput objects.
*-------------------------------------------------------------------------*/
void CleanupJoystickInput(lpjoystickType joystick)
{
	// make sure the device is unacquired
	// it doesn't harm to unacquire a device that isn't acquired
	if (joystick->dev) IDirectInputDevice_Unacquire(joystick->dev);

	if (joystick->dev) joystick->dev->lpVtbl->Release(joystick->dev);
}

BOOL IsJoystickInitialised(lpjoystickType joystick)
{
//	return FALSE;
	return joystick->found;
}

float xaxis(lpjoystickType joystick) { return joystick->found ? (float)joystick->xaxis / 1000.0f : 0.0f; }
float yaxis(lpjoystickType joystick) { return joystick->found ? (float)joystick->yaxis / 1000.0f : 0.0f; }

