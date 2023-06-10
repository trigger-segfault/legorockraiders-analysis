
#ifndef _RGL_DIRECTINPUT_H
#define _RGL_DIRECTINPUT_H

enum {
	DINPUTACTION_UP = 0,
	DINPUTACTION_DOWN,
	DINPUTACTION_LEFT,		
	DINPUTACTION_RIGHT,	
	DINPUTACTION_ACTION1,	
	DINPUTACTION_ACTION2,
	DINPUTACTION_ACTION3,

	DINPUTACTION_AXIS_X,	// These Two Are Undefinable They work off the left and right or Up and Down Presses
	DINPUTACTION_AXIS_Y,

	DINPUTACTION_END
};

enum {
	DIJ_AXIS_X = 0,
	DIJ_AXIS_Y,
	DIJ_AXIS_Z,

	DIJ_AXIS_SLIDER,

	DIJ_AXIS_ROTATION_X,
	DIJ_AXIS_ROTATION_Y,
	DIJ_AXIS_ROTATION_Z,

	DIJ_BUTTON_0,
	DIJ_BUTTON_1,
	DIJ_BUTTON_2,
	DIJ_BUTTON_3,
	DIJ_BUTTON_4,
	DIJ_BUTTON_5,
	DIJ_BUTTON_6,
	DIJ_BUTTON_7,
	DIJ_BUTTON_8,
	DIJ_BUTTON_9,
	DIJ_BUTTON_10,
	DIJ_BUTTON_11,
	DIJ_BUTTON_12,
	DIJ_BUTTON_13,
	DIJ_BUTTON_14,
	DIJ_BUTTON_15,
	DIJ_BUTTON_16,
	DIJ_BUTTON_17,
	DIJ_BUTTON_18,
	DIJ_BUTTON_19,
	DIJ_BUTTON_20,
	DIJ_BUTTON_21,
	DIJ_BUTTON_22,
	DIJ_BUTTON_23,
	DIJ_BUTTON_24,
	DIJ_BUTTON_25,
	DIJ_BUTTON_26,
	DIJ_BUTTON_27,
	DIJ_BUTTON_28,
	DIJ_BUTTON_29,
	DIJ_BUTTON_30,
	DIJ_BUTTON_31
};

#include <dinput.h>

extern BOOL		__cdecl DirectInput_Initialise(VOID);
extern BOOL		__cdecl DirectInput_Update(VOID);
extern BOOL		__cdecl DirectInput_KeyDown(UCHAR key);
extern BOOL		__cdecl DirectInput_KeyHit(UCHAR key);
extern VOID		__cdecl DirectInput_UpdateMouse(VOID);
extern VOID		__cdecl DirectInput_ClearClicked(VOID);
extern VOID		__cdecl DirectInput_SetMousePos(ULONG xPos, ULONG yPos);
extern VOID		__cdecl DirectInput_SetLeftButtonDown(BOOL downFlag);
extern VOID		__cdecl DirectInput_SetRightButtonDown(BOOL downFlag);
extern VOID		__cdecl DirectInput_ClearClicked(VOID);
extern ULONG	__cdecl DirectInput_GetMouseX(VOID);
extern ULONG	__cdecl DirectInput_GetMouseY(VOID);
extern VOID		__cdecl DirectInput_GetMousePos(ULONG *x, ULONG *y);
extern ULONG	__cdecl DirectInput_GetMouseDeltaX(VOID);
extern ULONG	__cdecl DirectInput_GetMouseDeltaY(VOID);
extern VOID		__cdecl DirectInput_GetMouseDeltaPos(ULONG *x, ULONG *y);
extern VOID		__cdecl DirectInput_SetLeftButtonClicked(BOOL newStatus);
extern VOID		__cdecl DirectInput_SetRightButtonClicked(BOOL newStatus);
extern BOOL		__cdecl DirectInput_GetLeftButtonDown(VOID);
extern BOOL		__cdecl DirectInput_GetRightButtonDown(VOID);
extern BOOL		__cdecl DirectInput_IsLeftButtonClicked(VOID);
extern BOOL		__cdecl DirectInput_IsRightButtonClicked(VOID);

extern UCHAR	__cdecl DirectInput_GetNumControllers(VOID);
extern BOOL		__cdecl DirectInput_SetController(UCHAR deviceNum);
extern BOOL		__cdecl DirectInput_SetControllerMapping(UCHAR Action, UCHAR data);
extern float	__cdecl DirectInput_GetActionData(UCHAR Action);
extern UCHAR*	__cdecl DirectInput_GetControllerInstanceName(UCHAR controllerID);
extern UCHAR*	__cdecl DirectInput_GetControllerProductName(UCHAR controllerID);
extern ULONG	__cdecl DirectInput_GetNumButtons(UCHAR deviceNum);

extern VOID		__cdecl DirectInput_MapConfig2Control(UCHAR ctrl, UCHAR*string);
extern UCHAR*	__cdecl	DirectInput_Key2String(UCHAR diKey);
extern UCHAR	__cdecl	DirectInput_GetControllerMapping(UCHAR Action);
extern signed int __cdecl	DirectInput_AnyKeyHit(VOID);

typedef struct {
	UCHAR		defString[64];
	UCHAR		dinputMapping;
	UCHAR		dispString[64];
} Config2DInput, *lpConfig2DInput;

extern Config2DInput	remapGlobs[];

// Temp Functions
extern UCHAR*	__cdecl DirectInput_Temp_ReturnMappingPointer(VOID);
extern long		__cdecl DirectInput_Temp_ReturnMappingSize(VOID);


#endif // !_RGL_DIRECTINPUT_H
