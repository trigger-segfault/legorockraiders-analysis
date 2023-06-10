
#include <dinput.h>

#pragma comment ( lib, "dinput" )

#include "Standard.h"
#include "Main.h"
#include "Errors.h"
#include "DirectInput.h"

#define	MAX_DIRECTINPUT_JOYSTICKS		8
#define	DIJ_RANGEMIN		-1000
#define	DIJ_RANGEMAX		1000
#define	DIJ_DEADZONE		2000		//1000 = 10%

typedef struct {

	ULONG					x;							// x position of the mouse
	ULONG					y;							// y position of the mouse
	ULONG					deltaX;						// the difference between the last x mouse position and the current one
	ULONG					deltaY;						// the difference between the last y mouse position and the current one
	ULONG					oldX;						// the x position of the mouse in the last frame
	ULONG					oldY;						// the y position of the mouse in the last frame
	BOOL					leftButtonDown;				// true if the left mouse button is down
	BOOL					rightButtonDown;			// true if the right mouse button is down
	BOOL					leftButtonClicked;			// true if the mouse has just been clicked
	BOOL					rightButtonClicked;			// true if the mouse has just been clicked

} mouseInputGlobs, *lpMouseInputGlobs;

typedef struct {
	LPDIRECTINPUTDEVICE7	controller;

	UCHAR	mapping[DINPUTACTION_END];
	float	posData[DINPUTACTION_END];

} controllerGlobs, *lpControllerGlobs;

typedef struct {
	LPDIRECTINPUTDEVICE7	lpDIJoystickDevice;
	UCHAR					ProductName[MAX_PATH];
	UCHAR					InstanceName[MAX_PATH];
	DWORD					deviceType;
	DIDEVCAPS				devCaps;
}joystickDevice, *lpJoystickDevice;

struct DirectInputGlobs {
	
	LPDIRECTINPUT7			lpDI;
	LPDIRECTINPUTDEVICE7	lpDIKeyboardDevice;
	LPDIRECTINPUTDEVICE		lpDIMouseDevice;
	UCHAR					buffer[2][256];
	ULONG					flags;
	
	mouseInputGlobs			mouse;

	joystickDevice			JoystickDevices[MAX_DIRECTINPUT_JOYSTICKS];
	UCHAR					numJoystickDevices;

	controllerGlobs			controllerData;
} directInputGlobs = { 0 };


Config2DInput	remapGlobs[] = {"KEY_0"				,DIK_0,							"0",
								"KEY_1"				,DIK_1,							"1",
								"KEY_2"				,DIK_2,							"2",
								"KEY_3"				,DIK_3,							"3",
								"KEY_4"				,DIK_4,							"4",
								"KEY_5"				,DIK_5,							"5",
								"KEY_6"				,DIK_6,							"6",
								"KEY_7"				,DIK_7,							"7",
								"KEY_8"				,DIK_8,							"8",
								"KEY_9"				,DIK_9,							"9",
								"KEY_A" 			,DIK_A,							"A",
								"KEY_B"	   			,DIK_B,							"B",
								"KEY_C"	   			,DIK_C,							"C",
								"KEY_D"	   			,DIK_D,							"D",
								"KEY_E"	   			,DIK_E,							"E",
								"KEY_F"	   			,DIK_F,							"F",
								"KEY_G"	   			,DIK_G,							"G",
								"KEY_H"	   			,DIK_H,							"H",
								"KEY_I"	   			,DIK_I,							"I",
								"KEY_J"	   			,DIK_J,							"J",
								"KEY_K"	   			,DIK_K,							"K",
								"KEY_L"	   			,DIK_L,							"L",
								"KEY_M"	   			,DIK_M,							"M",
								"KEY_N"	   			,DIK_N,							"N",
								"KEY_O"	   			,DIK_O,							"O",
								"KEY_P"	   			,DIK_P,							"P",
								"KEY_Q"	   			,DIK_Q,							"Q",
								"KEY_R"	   			,DIK_R,							"R",
								"KEY_S"	   			,DIK_S,							"S",
								"KEY_T"	   			,DIK_T,							"T",
								"KEY_U"	   			,DIK_U,							"U",
								"KEY_V"	   			,DIK_V,							"V",
								"KEY_W"	   			,DIK_W,							"W",
								"KEY_X"	   			,DIK_X,							"X",
								"KEY_Y"	   			,DIK_Y,							"Y",
								"KEY_Z"	   			,DIK_Z,							"Z",
								"KEY_RETURN"		,DIK_RETURN,					"Return",
								"KEY_LSHIFT"		,DIK_LSHIFT,					"Left Shift",
								"KEY_RSHIFT"		,DIK_RSHIFT,					"Right Shift",
								"KEY_LCTRL"			,DIK_LCONTROL,					"Left Control",
								"KEY_RCTRL"			,DIK_RCONTROL,					"Right Control",
								"KEY_LALT"			,DIK_LALT,						"Left Alt",
								"KEY_RALT"			,DIK_RALT,						"Right Alt",
								"KEY_SPACE"			,DIK_SPACE,						"Space",
								"KEY_NUMPAD0"		,DIK_NUMPAD0,					"Numpad 0",
								"KEY_NUMPAD1"		,DIK_NUMPAD1,					"Numpad 1",
								"KEY_NUMPAD2"		,DIK_NUMPAD2,					"Numpad 2",
								"KEY_NUMPAD3"		,DIK_NUMPAD3,					"Numpad 3",
								"KEY_NUMPAD4"		,DIK_NUMPAD4,					"Numpad 4",
								"KEY_NUMPAD5"		,DIK_NUMPAD5,					"Numpad 5",
								"KEY_NUMPAD6"		,DIK_NUMPAD6,					"Numpad 6",
								"KEY_NUMPAD7"		,DIK_NUMPAD7,					"Numpad 7",
								"KEY_NUMPAD8"		,DIK_NUMPAD8,					"Numpad 8",
								"KEY_NUMPAD9"		,DIK_NUMPAD9,					"Numpad 9",
								"KEY_ESC"			,DIK_ESCAPE,					"Esc",
								"KEY_MINUS"			,DIK_MINUS,						"Minus",
								"KEY_EQUALS"		,DIK_EQUALS,					"Equals",
								"KEY_BACKSPACE"		,DIK_BACK,						"Backspace",
								"KEY_TAB"			,DIK_TAB,	 					"Tab",
								"KEY_LBRACKET"		,DIK_LBRACKET,					"Open Bracket",
								"KEY_RBRACKET"		,DIK_RBRACKET,					"Close Bracket",
								"KEY_SEMICOLON"		,DIK_SEMICOLON,					"Semi Colon",
								"KEY_APOSTROPHE"	,DIK_APOSTROPHE,				"Apostrophe",
								"KEY_GRAVE"			,DIK_GRAVE,						"Tilde",
								"KEY_BACKSLASH"		,DIK_BACKSLASH,					"Back Slash",
								"KEY_COMMA"			,DIK_COMMA,   					"Comma",
								"KEY_FULLSTOP"		,DIK_PERIOD,  					"Period",
								"KEY_SLASH"			,DIK_SLASH,   					"Forward Slash",
								"KEY_MULTIPLY"		,DIK_MULTIPLY,					"Multiply",
								"KEY_LMENU"			,DIK_LMENU,   					"Left Menu",
								"KEY_CAPSLOCK"		,DIK_CAPITAL, 					"Caps Lock",
								"KEY_F1"			,DIK_F1,						"F1",
								"KEY_F2"			,DIK_F2,						"F2",
								"KEY_F3"			,DIK_F3,						"F3",
								"KEY_F4"			,DIK_F4,						"F4",
								"KEY_F5"			,DIK_F5,						"F5",
								"KEY_F6"			,DIK_F6,						"F6",
								"KEY_F7"			,DIK_F7,						"F7",
								"KEY_F8"			,DIK_F8,						"F8",
								"KEY_F9"			,DIK_F9,						"F9",
								"KEY_F10"			,DIK_F10,						"F10",
								"KEY_F11"			,DIK_F11,						"F11",
								"KEY_F12"			,DIK_F12,						"F12",
								"KEY_NUMLOCK"		,DIK_NUMLOCK,					"Num Lock",
								"KEY_SCROLLOCK"		,DIK_SCROLL, 					"Scroll Lock",
								"KEY_SUBTRACT"		,DIK_SUBTRACT,					"Subtract",
								"KEY_ADDITION"		,DIK_ADD,    					"Add",
								"KEY_DECIMALPOINT"	,DIK_DECIMAL,					"Decimal",
								"KEY_RMENU"			,DIK_RMENU,						"Right Menu",
								"KEY_PAUSE"			,DIK_PAUSE,						"Pause",
								"KEY_HOME"			,DIK_HOME,						"Home",
								"KEY_END"			,DIK_END,						"End",
								"KEY_PAGEUP"		,DIK_PRIOR,						"Page Up",
								"KEY_PAGEDOWN"		,DIK_NEXT,						"Page Down",
								"KEY_INSERT"		,DIK_INSERT,					"Insert",
								"KEY_DELETE"		,DIK_DELETE,					"Delete",
								"KEY_LWIN"			,DIK_LWIN,						"Left Windows",
								"KEY_RWIN"			,DIK_RWIN,						"Right Windows",
								"KEY_LEFT"			,DIK_LEFT,						"Left Arrow",
								"KEY_RIGHT"			,DIK_RIGHT,						"Right Arrow",
								"KEY_UP"			,DIK_UP,						"Up Arrow",
								"KEY_DOWN"			,DIK_DOWN,						"Down Arrow",
							     "\0",0,"\0"};





BOOL FAR PASCAL DirectInput_JoystickEnumerateCallback(LPCDIDEVICEINSTANCE devInstance, LPVOID data) {

LPDIRECTINPUTDEVICE7	lpJoystick;
DIPROPRANGE				diprg;
DIPROPDWORD				dipdw;

	if(FAILED( directInputGlobs.lpDI->lpVtbl->CreateDeviceEx(directInputGlobs.lpDI, &devInstance->guidInstance, &IID_IDirectInputDevice7,(void**)&lpJoystick, NULL)))
	{
		Error_Warn(TRUE,"Failed To Create a DirectInput Device For a Joystick. Enumeration Will Continue");
		return DIENUM_CONTINUE;
	}

	if(FAILED (lpJoystick->lpVtbl->SetDataFormat(lpJoystick,&c_dfDIJoystick)))
	{
		Error_Warn(TRUE,"Failed To Set the Data format for this device");
		lpJoystick->lpVtbl->Release(lpJoystick);
		return DIENUM_CONTINUE;
	}

	if(FAILED (lpJoystick->lpVtbl->SetCooperativeLevel(lpJoystick,Main_hWnd(),DISCL_FOREGROUND|DISCL_NONEXCLUSIVE)))
	{
		Error_Warn(TRUE,"Failed To Set The Cooperative Level On a Joystick");
		lpJoystick->lpVtbl->Release(lpJoystick);

	}

	// Get Joystick Capabilities
	directInputGlobs.JoystickDevices[directInputGlobs.numJoystickDevices].devCaps.dwSize = sizeof(DIDEVCAPS);
	if(lpJoystick->lpVtbl->GetCapabilities(lpJoystick,&directInputGlobs.JoystickDevices[directInputGlobs.numJoystickDevices].devCaps) != DI_OK)
	{
		Error_Fatal(TRUE,"Failed to get this devices Capabilities");
		lpJoystick->lpVtbl->Release(lpJoystick);
	}

	// Set the Joyticks Properties (X and Y)
	diprg.diph.dwSize       = sizeof(diprg); 
	diprg.diph.dwHeaderSize = sizeof(diprg.diph); 
	diprg.diph.dwObj        = DIJOFS_X; 
	diprg.diph.dwHow        = DIPH_BYOFFSET; 
	diprg.lMin              = DIJ_RANGEMIN; 
	diprg.lMax              = DIJ_RANGEMAX;  

	if(FAILED(lpJoystick->lpVtbl->SetProperty(lpJoystick, DIPROP_RANGE, &diprg.diph))) 
	{																				  
		Error_Warn(TRUE,"Failed To SetProperty DIPH_RANGE On a Joystick");
		lpJoystick->lpVtbl->Release(lpJoystick);		
		return DIENUM_CONTINUE;
	}

	diprg.diph.dwObj = DIJOFS_Y;
	if(FAILED(lpJoystick->lpVtbl->SetProperty(lpJoystick, DIPROP_RANGE, &diprg.diph))) 
	{																				  
		Error_Warn(TRUE,"Failed To SetProperty DIPH_RANGE On a Joystick");
		lpJoystick->lpVtbl->Release(lpJoystick);		
		return DIENUM_CONTINUE;
	}

	// set X axis dead zone to 5%
	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
	dipdw.diph.dwHow        = DIPH_BYOFFSET;
	dipdw.diph.dwObj		= DIJOFS_X;
	dipdw.dwData            = DIJ_DEADZONE;
	if(FAILED(lpJoystick->lpVtbl->SetProperty(lpJoystick, DIPROP_DEADZONE, &dipdw.diph))) 
	{ 
	   Error_Warn(TRUE,"IDirectInputDevice7:: SetProperty(DIPH_DEADZONE) FAILED\n"); 
	   lpJoystick->lpVtbl->Release(lpJoystick); 
	   return FALSE; 
	}
	dipdw.diph.dwObj = DIJOFS_Y;
	if(FAILED(lpJoystick->lpVtbl->SetProperty(lpJoystick, DIPROP_DEADZONE, &dipdw.diph))) 
	{ 
	   Error_Warn(TRUE,"IDirectInputDevice7:: SetProperty(DIPH_DEADZONE) FAILED\n"); 
	   lpJoystick->lpVtbl->Release(lpJoystick); 
	   return FALSE; 
	}

	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DIPROPAXISMODE_ABS;		 
	if(FAILED(lpJoystick->lpVtbl->SetProperty(lpJoystick, DIPROP_AXISMODE, &dipdw.diph))) 
	{ 
	   Error_Warn(TRUE,"IDirectInputDevice7:: SetProperty(AXISMODE) FAILED\n"); 
//	   lpJoystick->lpVtbl->Release(lpJoystick); 
//	   return FALSE; 
	}		
	
	// Save Details	
	directInputGlobs.JoystickDevices[directInputGlobs.numJoystickDevices].lpDIJoystickDevice = lpJoystick;
	strcpy(directInputGlobs.JoystickDevices[directInputGlobs.numJoystickDevices].ProductName,devInstance->tszProductName);
	strcpy(directInputGlobs.JoystickDevices[directInputGlobs.numJoystickDevices].ProductName,devInstance->tszInstanceName);
	directInputGlobs.JoystickDevices[directInputGlobs.numJoystickDevices].deviceType = devInstance->dwDevType;

	directInputGlobs.numJoystickDevices++;
	return DIENUM_CONTINUE;
}

BOOL DirectInput_Initialise(VOID) {

	HRESULT r;

	directInputGlobs.numJoystickDevices = 0;

	if (SUCCEEDED(r = DirectInputCreateEx(Main_hInstance(), DIRECTINPUT_VERSION, &IID_IDirectInput7, &directInputGlobs.lpDI, NULL))) {
		if (SUCCEEDED(r = directInputGlobs.lpDI->lpVtbl->CreateDeviceEx(directInputGlobs.lpDI, &GUID_SysKeyboard, &IID_IDirectInputDevice7, &directInputGlobs.lpDIKeyboardDevice, NULL))) {

			if (SUCCEEDED(r = directInputGlobs.lpDIKeyboardDevice->lpVtbl->SetDataFormat(directInputGlobs.lpDIKeyboardDevice, &c_dfDIKeyboard))) {
				if (SUCCEEDED(r = directInputGlobs.lpDIKeyboardDevice->lpVtbl->SetCooperativeLevel(directInputGlobs.lpDIKeyboardDevice, Main_hWnd(), DISCL_FOREGROUND|DISCL_NONEXCLUSIVE))) {

					directInputGlobs.lpDI->lpVtbl->EnumDevices(directInputGlobs.lpDI, DIDEVTYPE_JOYSTICK,DirectInput_JoystickEnumerateCallback,0,DIEDFL_ATTACHEDONLY);

					return TRUE;

				} else Error_DirectX(r, "SetCooperativeLevel");
		
			} else Error_DirectX(r, "SetCooperativeLevel");
			directInputGlobs.lpDIKeyboardDevice->lpVtbl->Release(directInputGlobs.lpDIKeyboardDevice);
			directInputGlobs.lpDIKeyboardDevice = NULL;

		} else Error_DirectX(r, "SetCooperativeLevel");
		directInputGlobs.lpDI->lpVtbl->Release(directInputGlobs.lpDI);
		directInputGlobs.lpDI = NULL;

	} else Error_DirectX(r, "DirectInputCreateEx");

	return FALSE;
}

BOOL DirectInput_KeyDown(UCHAR key) {

	return directInputGlobs.buffer[0][key] & 0x80;
}

BOOL DirectInput_KeyHit(UCHAR key) {

	return (directInputGlobs.buffer[0][key] & 0x80) && !(directInputGlobs.buffer[1][key] & 0x80);
}

static BOOL DirectInput_AcquireKeyboard(BOOL acquire) {

	HRESULT r;

	if (acquire) {
		if (SUCCEEDED(r = directInputGlobs.lpDIKeyboardDevice->lpVtbl->Acquire(directInputGlobs.lpDIKeyboardDevice))) {
			return TRUE;
		}
		else
		{
			OutputDebugString("Acquisition Failed\r\n");
		}
	} else if (!acquire) {
		if (SUCCEEDED(r = directInputGlobs.lpDIKeyboardDevice->lpVtbl->Unacquire(directInputGlobs.lpDIKeyboardDevice))) {
			return FALSE;
		}
	}

	return FALSE;
}

static BOOL DirectInput_AcquireJoystick(BOOL acquire) {
HRESULT	r;

	r = IDirectInputDevice_Acquire(directInputGlobs.controllerData.controller);

	if(r == DI_OK)	return TRUE;
	return FALSE;
	
}

float DirectInput_JoystickRead(DIJOYSTATE *js, UCHAR d)
{
	switch(directInputGlobs.controllerData.mapping[d])
	{
		case DIJ_AXIS_X:			return js->lX / 1000.0f;
		case DIJ_AXIS_Y:			return js->lY / 1000.0f;
		case DIJ_AXIS_Z:			return js->lZ / 1000.0f;
									
		case DIJ_AXIS_SLIDER:		return 0.0f;//js->rglSlider / 1000.0f;
		                   
		case DIJ_AXIS_ROTATION_X:	return js->lRx / 1000.0f;
		case DIJ_AXIS_ROTATION_Y:	return js->lRy / 1000.0f;
		case DIJ_AXIS_ROTATION_Z:	return js->lRz / 1000.0f;

		
		default:
			if(js->rgbButtons[directInputGlobs.controllerData.mapping[d] - DIJ_BUTTON_0] & 0x80)
			{
				return 1.0f;
			}
			return 0.0f;
			break;
	}

	return 0.0f;
}

BOOL DirectInput_Update(VOID) { 

	HRESULT		r;
	ULONG		loop;
	float		p;
	DIJOYSTATE	js;

	if (!Main_AppActive()) {

		DirectInput_AcquireKeyboard(FALSE);
		memset(directInputGlobs.buffer, 0, sizeof(directInputGlobs.buffer));

	} else {

		memcpy(directInputGlobs.buffer[1], directInputGlobs.buffer[0], sizeof(directInputGlobs.buffer[1]));

		for (loop=0 ; loop<2 ; loop++) {

			if (SUCCEEDED(r = directInputGlobs.lpDIKeyboardDevice->lpVtbl->GetDeviceState(directInputGlobs.lpDIKeyboardDevice, sizeof(directInputGlobs.buffer[0]), &directInputGlobs.buffer[0]))) {

				// Main Controller Stuff
				if(directInputGlobs.controllerData.controller == directInputGlobs.lpDIKeyboardDevice)	{
					// Left/Right
					p = 0.0f;
					if(DirectInput_KeyDown(directInputGlobs.controllerData.mapping[DINPUTACTION_LEFT]))		
					{
						directInputGlobs.controllerData.posData[DINPUTACTION_LEFT] = 1.0f;
						p -= 1.0f;
					}
					else	directInputGlobs.controllerData.posData[DINPUTACTION_LEFT] = 0.0f;
					if(DirectInput_KeyDown(directInputGlobs.controllerData.mapping[DINPUTACTION_RIGHT]))	
					{
						directInputGlobs.controllerData.posData[DINPUTACTION_RIGHT] = 1.0f;
						p += 1.0f;
					}
					else	directInputGlobs.controllerData.posData[DINPUTACTION_RIGHT] = 0.0f;

					directInputGlobs.controllerData.posData[DINPUTACTION_AXIS_X] = p;
		
					// Up/Down
					p = 0.0f;
					if(DirectInput_KeyDown(directInputGlobs.controllerData.mapping[DINPUTACTION_UP]))		
					{
						directInputGlobs.controllerData.posData[DINPUTACTION_UP] = 1.0f;
						p += 1.0f;
					}
					else	directInputGlobs.controllerData.posData[DINPUTACTION_UP] = 0.0f;
					if(DirectInput_KeyDown(directInputGlobs.controllerData.mapping[DINPUTACTION_DOWN]))		
					{
						directInputGlobs.controllerData.posData[DINPUTACTION_DOWN] = 1.0f;
						p -= 1.0f;
					}
					else	directInputGlobs.controllerData.posData[DINPUTACTION_DOWN] = 0.0f;
					directInputGlobs.controllerData.posData[DINPUTACTION_AXIS_Y] = p;
		
					// Actions 1&2&3
					if(DirectInput_KeyDown(directInputGlobs.controllerData.mapping[DINPUTACTION_ACTION1]))	directInputGlobs.controllerData.posData[DINPUTACTION_ACTION1] = 1.0f;
					else																					directInputGlobs.controllerData.posData[DINPUTACTION_ACTION1] = 0.0f;
					if(DirectInput_KeyDown(directInputGlobs.controllerData.mapping[DINPUTACTION_ACTION2]))	directInputGlobs.controllerData.posData[DINPUTACTION_ACTION2] = 1.0f;
					else																					directInputGlobs.controllerData.posData[DINPUTACTION_ACTION2] = 0.0f;
					if(DirectInput_KeyDown(directInputGlobs.controllerData.mapping[DINPUTACTION_ACTION3]))	directInputGlobs.controllerData.posData[DINPUTACTION_ACTION3] = 1.0f;
					else																					directInputGlobs.controllerData.posData[DINPUTACTION_ACTION3] = 0.0f;				
				}
				else if (directInputGlobs.controllerData.controller)	// Joystick Mappings
				{
					
					IDirectInputDevice7_Poll(directInputGlobs.controllerData.controller);
					r = IDirectInputDevice7_GetDeviceState(directInputGlobs.controllerData.controller, sizeof(DIJOYSTATE), &js); 
					if(r != DI_OK)
					{
						DirectInput_AcquireJoystick(TRUE);
						return FALSE;
					}	

					// Now Read.
					p = DirectInput_JoystickRead(&js,DINPUTACTION_AXIS_X);
					directInputGlobs.controllerData.posData[DINPUTACTION_AXIS_X] = p;
					if( p < 0.0f)	
					{	
						directInputGlobs.controllerData.posData[DINPUTACTION_LEFT] = 1.0f;
						directInputGlobs.controllerData.posData[DINPUTACTION_RIGHT] = 0.0f;
					}
					else if(p > 0.0f)
					{
						directInputGlobs.controllerData.posData[DINPUTACTION_LEFT] = 0.0f;
						directInputGlobs.controllerData.posData[DINPUTACTION_RIGHT] = 1.0f;
					}
					else
					{
						directInputGlobs.controllerData.posData[DINPUTACTION_LEFT] = 0.0f;
						directInputGlobs.controllerData.posData[DINPUTACTION_RIGHT] = 0.0f;
					}
			
					p = -DirectInput_JoystickRead(&js,DINPUTACTION_AXIS_Y);
					directInputGlobs.controllerData.posData[DINPUTACTION_AXIS_Y] = p;
					if( p < 0.0f)	
					{	
						directInputGlobs.controllerData.posData[DINPUTACTION_DOWN] = 1.0f;
						directInputGlobs.controllerData.posData[DINPUTACTION_UP] = 0.0f;
					}
					else if(p > 0.0f)
					{
						directInputGlobs.controllerData.posData[DINPUTACTION_DOWN] = 0.0f;
						directInputGlobs.controllerData.posData[DINPUTACTION_UP] = 1.0f;
					}
					else
					{
						directInputGlobs.controllerData.posData[DINPUTACTION_DOWN] = 0.0f;
						directInputGlobs.controllerData.posData[DINPUTACTION_UP] = 0.0f;
					}

					// Buttons
					p = DirectInput_JoystickRead(&js,DINPUTACTION_ACTION1);
					directInputGlobs.controllerData.posData[DINPUTACTION_ACTION1] = p;

					p = DirectInput_JoystickRead(&js,DINPUTACTION_ACTION2);
					directInputGlobs.controllerData.posData[DINPUTACTION_ACTION2] = p;

					p = DirectInput_JoystickRead(&js,DINPUTACTION_ACTION3);
					directInputGlobs.controllerData.posData[DINPUTACTION_ACTION3] = p;
					
				}
				return TRUE;

			} else if (DIERR_NOTACQUIRED == r || DIERR_INPUTLOST == r) {

				if (DirectInput_AcquireKeyboard(TRUE)) break;
				Error_DirectX(r, "GetDeviceStatus");

			} else {			
//				Error_DirectX(r, "GetDeviceStatus");
				break;
			}
		}

	}


	return FALSE;
}


// ***************************************************************************************************
// should get called every frame. Need to update the old mouse pos and deltas as we don't get a mouse
// move event if we aven't moved it. 
VOID	DirectInput_UpdateMouse(VOID) {

	directInputGlobs.mouse.oldX		= directInputGlobs.mouse.x;
	directInputGlobs.mouse.oldY		= directInputGlobs.mouse.y;


}

// ***************************************************************************************************
VOID	DirectInput_SetMousePos(ULONG xPos, ULONG yPos) {

	directInputGlobs.mouse.deltaX	= directInputGlobs.mouse.x - xPos;
	directInputGlobs.mouse.deltaY	= directInputGlobs.mouse.y - yPos;

	directInputGlobs.mouse.x		= xPos;
	directInputGlobs.mouse.y		= yPos;
}

// ***************************************************************************************************
VOID	DirectInput_SetLeftButtonDown(BOOL downFlag) {

	directInputGlobs.mouse.leftButtonDown = downFlag;

	if (downFlag == FALSE)
	{
		 directInputGlobs.mouse.leftButtonClicked = TRUE;
	}
}

// ***************************************************************************************************
VOID	DirectInput_SetRightButtonDown(BOOL downFlag) {

	directInputGlobs.mouse.rightButtonDown = downFlag;

	if (downFlag == FALSE)
	{
		 directInputGlobs.mouse.rightButtonClicked = TRUE;
	}

}

// ***************************************************************************************************
VOID	DirectInput_ClearClicked(VOID) {

	directInputGlobs.mouse.leftButtonClicked = FALSE;
	directInputGlobs.mouse.rightButtonClicked = FALSE;

}

// ***************************************************************************************************
ULONG	DirectInput_GetMouseX(VOID) {
	return directInputGlobs.mouse.x;
}

// ***************************************************************************************************
ULONG	DirectInput_GetMouseY(VOID) {
	return directInputGlobs.mouse.y;
}

// ***************************************************************************************************
VOID	DirectInput_GetMousePos(ULONG *x, ULONG *y) {
	if (x) *x = directInputGlobs.mouse.x;
	if (y) *y = directInputGlobs.mouse.y;
}

// ***************************************************************************************************
ULONG	DirectInput_GetMouseDeltaX(VOID) {
	return directInputGlobs.mouse.deltaX;
}

// ***************************************************************************************************
ULONG	DirectInput_GetMouseDeltaY(VOID) {
	return directInputGlobs.mouse.deltaY;
}

// ***************************************************************************************************
VOID	DirectInput_GetMouseDelta(ULONG *dx, ULONG *dy) {
	if (dx) *dx = directInputGlobs.mouse.deltaX;
	if (dy) *dy = directInputGlobs.mouse.deltaY;
}

// ***************************************************************************************************
BOOL	DirectInput_GetLeftButtonDown(VOID) {
	return directInputGlobs.mouse.leftButtonDown;
}

// ***************************************************************************************************
BOOL	DirectInput_GetRightButtonDown(VOID) {
	return directInputGlobs.mouse.rightButtonDown;
}

// ***************************************************************************************************
BOOL	DirectInput_IsLeftButtonClicked(VOID) {
	return directInputGlobs.mouse.leftButtonClicked;
}

// ***************************************************************************************************
BOOL	DirectInput_IsRightButtonClicked(VOID) {
	return directInputGlobs.mouse.rightButtonClicked;
}

// ***************************************************************************************************
void	DirectInput_SetLeftButtonClicked(BOOL newStatus) {
	directInputGlobs.mouse.leftButtonClicked = newStatus;
}

// ***************************************************************************************************
void	DirectInput_SetRightButtonClicked(BOOL newStatus) {
	directInputGlobs.mouse.rightButtonClicked = newStatus;
}




// ***************************************************************************************************
UCHAR __inline 	DirectInput_GetNumControllers(VOID) {
	return directInputGlobs.numJoystickDevices+1;
}

// ***************************************************************************************************
LPUCHAR	__inline DirectInput_GetControllerProductName(UCHAR controllerID) {

	if(controllerID >= (directInputGlobs.numJoystickDevices+1))
		return NULL;

	if(controllerID == 0)
		return("Keyboard");
	else
		return(directInputGlobs.JoystickDevices[controllerID-1].ProductName);
}

// ***************************************************************************************************
LPUCHAR	__inline DirectInput_GetControllerInstanceName(UCHAR controllerID) {

	if(controllerID >= (directInputGlobs.numJoystickDevices+1))
		return NULL;

	if(controllerID == 0)
		return("Keyboard");
	else
		return(directInputGlobs.JoystickDevices[controllerID-1].InstanceName);
}

// ***************************************************************************************************

// ***************************************************************************************************
BOOL	DirectInput_SetController(UCHAR deviceNum)
{
	if(deviceNum >= (directInputGlobs.numJoystickDevices+1))
		return FALSE;

	// Okay Set Device
	if(deviceNum == 0)	// Keyboard
	{
		directInputGlobs.controllerData.controller = directInputGlobs.lpDIKeyboardDevice;		
	}
	else
	{
		directInputGlobs.controllerData.controller = directInputGlobs.JoystickDevices[deviceNum-1].lpDIJoystickDevice;	
	}

	return TRUE;
}

// ***************************************************************************************************
BOOL	DirectInput_SetControllerMapping(UCHAR Action, UCHAR data)
{
	if(Action >= DINPUTACTION_END)
	{
		Error_Warn(TRUE,"Requested Controller Mapping Outside Of the standard UP/DOWN/LEFT/RIGHT/ACTION1/ACTION2 range");
		return FALSE;
	}

	directInputGlobs.controllerData.mapping[Action] = data;
	return TRUE;
}

UCHAR	DirectInput_GetControllerMapping(UCHAR Action)
{
	if(Action >= DINPUTACTION_END)
	{
		Error_Warn(TRUE,"Requested Controller Mapping Outside Of the standard UP/DOWN/LEFT/RIGHT/ACTION1/ACTION2 range");
		return 0;
	}

	return directInputGlobs.controllerData.mapping[Action];
}

// ***************************************************************************************************
// returns the location of the button/axis/key for the specified action. 
// 0=Unpressed/Center Anything Else is analogue or pressed.
// Note: UP&DOWN return the same value 
//       LEFT&RIGHT return the same Value range(-1.00 -> 1.00)
float __inline DirectInput_GetActionData(UCHAR Action) {
	
	if(Action >= DINPUTACTION_END)
	{
		Error_Fatal(TRUE,"Requested Controller Mapping Outside Of the standard UP/DOWN/LEFT/RIGHT/ACTION1/ACTION2 range");
		return 0.0f;
	}

	return directInputGlobs.controllerData.posData[Action];
}

// ***************************************************************************************************
ULONG __inline DirectInput_GetNumButtons(UCHAR deviceNum)
{
	if(deviceNum >= DINPUTACTION_END)
	{
		Error_Fatal(TRUE,"Requested Controller Mapping Outside Of the standard UP/DOWN/LEFT/RIGHT/ACTION1/ACTION2 range");
		return 0;
	}

	if(deviceNum == 0)
	{
		return 255;
	}

	return directInputGlobs.JoystickDevices[deviceNum-1].devCaps.dwButtons;
}


// ***************************************************************************************************
VOID	DirectInput_MapConfig2Control(UCHAR ctrl, LPUCHAR s)
{
long	i = 0;

	while(remapGlobs[i].defString[0] != 0)
	{
		if(stricmp(remapGlobs[i].defString,s) == 0)
		{
			DirectInput_SetControllerMapping(ctrl,remapGlobs[i].dinputMapping);
			return;
		}

		i++;
	}
}

// ***************************************************************************************************
LPUCHAR		DirectInput_Key2String(UCHAR diKey)
{
long	i = 0;

	while(remapGlobs[i].defString[0] != 0)
	{
		if(remapGlobs[i].dinputMapping == diKey)
		{
			return remapGlobs[i].dispString;
		}

		i++;
	}
	return NULL;
}


// ***************************************************************************************************
// This function returns a key if a key has been hit.
// -1 Otherwise.
signed int DirectInput_AnyKeyHit(VOID)
{
	signed int i;

	for(i=0;i<256;i++)
		if(DirectInput_KeyHit((UCHAR)i))
			return i;

	return -1;
}

// Temporary Function to return a pointer to the Key Mappings for use in a temp save
UCHAR* DirectInput_Temp_ReturnMappingPointer(VOID)
{
	return (LPUCHAR)&directInputGlobs.controllerData.mapping;
}

long DirectInput_Temp_ReturnMappingSize(VOID)
{
	return DINPUTACTION_END;
}

// ***************************************************************************************************
// ***************************************************************************************************
// ***************************************************************************************************
// ***************************************************************************************************
// ***************************************************************************************************

