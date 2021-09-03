#pragma once

#include "../framework.h"
#include "Maths.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define DIRECTDRAW_MAXDRIVERS				20
#define DIRECTDRAW_MAXDEVICES				20
#define DIRECTDRAW_MAXMODES					200
#define DIRECTDRAW_DRIVERSTRINGLEN			256
#define DIRECTDRAW_DEVICESTRINGLEN			256

#pragma endregion

/**********************************************************************************
 ******** Enumerations
 **********************************************************************************/

#pragma region Enums

#define DIRECTDRAW_FLAG_VALID					0x00000001

#define DIRECTDRAW_FLAG_DRIVER_PRIMARY			0x00000010
#define DIRECTDRAW_FLAG_DRIVER_WINDOWOK			0x00000020

#define DIRECTDRAW_FLAG_DEVICE_DEPTH8			0x00000010
#define DIRECTDRAW_FLAG_DEVICE_DEPTH16			0x00000020
#define DIRECTDRAW_FLAG_DEVICE_DEPTH24			0x00000040
#define DIRECTDRAW_FLAG_DEVICE_DEPTH32			0x00000080
#define DIRECTDRAW_FLAG_DEVICE_ZBUFF8			0x00000100
#define DIRECTDRAW_FLAG_DEVICE_ZBUFF16			0x00000200
#define DIRECTDRAW_FLAG_DEVICE_ZBUFF24			0x00000400
#define DIRECTDRAW_FLAG_DEVICE_ZBUFF32			0x00000800
#define DIRECTDRAW_FLAG_DEVICE_COLOUR			0x00001000
#define DIRECTDRAW_FLAG_DEVICE_HARDWARE			0x00002000
#define DIRECTDRAW_FLAG_DEVICE_VIDEOTEXTURE		0x00004000
#define DIRECTDRAW_FLAG_DEVICE_SYSTEMTEXTURE	0x00008000

/// CUSTOM:
#define DIRECTDRAW_FLAG_DRIVER_VALID			0x00000001
#define DIRECTDRAW_FLAG_DEVICE_VALID			0x00000001
#define DIRECTDRAW_FLAG_MODE_VALID				0x00000001

#pragma endregion

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

typedef struct DirectDraw_Driver
{
	/*000,10*/ GUID guid;
	/*010,100*/ char desc[DIRECTDRAW_DRIVERSTRINGLEN];
	/*110,4*/ unsigned long flags;
} DirectDraw_Driver, *lpDirectDraw_Driver;
static_assert(sizeof(DirectDraw_Driver) == 0x114, "");


typedef struct DirectDraw_Device
{
	/*000,10*/ GUID guid;
	/*010,100*/ char desc[DIRECTDRAW_DEVICESTRINGLEN];
	/*110,4*/ unsigned long flags;
} DirectDraw_Device, *lpDirectDraw_Device;
static_assert(sizeof(DirectDraw_Device) == 0x114, "");


typedef struct DirectDraw_Mode
{
	/*000,4*/ unsigned long width;
	/*004,4*/ unsigned long height;
	/*008,4*/ unsigned long bitDepth;
	/*00c,100*/ char desc[DIRECTDRAW_DEVICESTRINGLEN];
	/*10c,4*/ unsigned long flags;
	/*110*/
} DirectDraw_Mode, *lpDirectDraw_Mode;
static_assert(sizeof(DirectDraw_Mode) == 0x110, "");


typedef struct DirectDraw_Globs
{
	/*00,4*/ HWND hWnd;
	/*04,4*/ IDirectDraw4* lpDirectDraw;
	/*08,4*/ IDirectDrawSurface4* fSurf;
	/*0c,4*/ IDirectDrawSurface4* bSurf;
	/*10,4*/ IDirectDrawSurface4* zSurf;			// (unused)
	/*14,4*/ IDirectDrawClipper* lpFrontClipper;
	/*18,4*/ IDirectDrawClipper* lpBackClipper;
	/*1c,4*/ DirectDraw_Driver* driverList;
	/*20,4*/ DirectDraw_Driver* selectedDriver;		// (unused)
	/*24,4*/ DirectDraw_Device* deviceList;
	/*28,4*/ DirectDraw_Device* selectedDevice;		// (unused)
	/*2c,4*/ DirectDraw_Mode* modeList;
	/*30,4*/ unsigned long driverCount;
	/*34,4*/ unsigned long deviceCount;
	/*38,4*/ unsigned long modeCount;
	/*3c,4*/ BOOL fullScreen;
	/*40,4*/ unsigned long width;
	/*44,4*/ unsigned long height;
	/*48*/
} DirectDraw_Globs;
static_assert(sizeof(DirectDraw_Globs) == 0x48, "");

#pragma endregion

/**********************************************************************************
 ******** Globals
 **********************************************************************************/

#pragma region Globals

// <LegoRR.exe @0076bc80>
extern DirectDraw_Globs directDrawGlobs;

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @00406500>
__inline IDirectDraw4* __cdecl DirectDraw() { return directDrawGlobs.lpDirectDraw; }

//__inline IDirectDrawSurface4* __cdecl DirectDraw_fSurf()	{ return directDrawGlobs.fSurf; }

// <LegoRR.exe @00406510>
__inline IDirectDrawSurface4* __cdecl DirectDraw_bSurf() { return directDrawGlobs.bSurf; }

//__inline BOOL __cdecl DirectDraw_FullScreen()				{ return directDrawGlobs.fullScreen; }

//__inline BOOL __cdecl DirectDraw_SetupFullScreen(lpDirectDraw_Driver driver, lpDirectDraw_Device device, lpDirectDraw_Mode mode)	{ return DirectDraw_Setup(TRUE, driver, device, mode, 0, 0, 320, 200); }
//__inline BOOL __cdecl DirectDraw_SetupWindowed(lpDirectDraw_Device device, ULONG xPos, ULONG yPos, ULONG width, ULONG height)		{ return DirectDraw_Setup(FALSE, NULL, device, NULL, xPos, yPos, width, height); }


// <LegoRR.exe @0047c430>
void __cdecl DirectDraw_Initialise(HWND hWnd);

// <LegoRR.exe @0047c480>
BOOL __cdecl DirectDraw_EnumDrivers(OUT DirectDraw_Driver* list, OUT unsigned long* count);

// <LegoRR.exe @0047c4b0>
BOOL WINAPI DirectDraw_EnumDriverCallback(GUID FAR* lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID lpContext);

// <LegoRR.exe @0047c5a0>
BOOL __cdecl DirectDraw_EnumDevices(const DirectDraw_Driver* driver, OUT DirectDraw_Device* list, OUT unsigned long* count);

// <LegoRR.exe @0047c640>
HRESULT WINAPI DirectDraw_EnumDeviceCallback(LPGUID lpGuid, LPSTR lpDeviceDescription,
											LPSTR lpDeviceName, LPD3DDEVICEDESC lpHWDesc,
											LPD3DDEVICEDESC lpHELDesc, LPVOID lpContext);

// <LegoRR.exe @0047c770>
BOOL __cdecl DirectDraw_EnumModes(const DirectDraw_Driver* driver, BOOL fullScreen, OUT DirectDraw_Mode* list, OUT unsigned long* count);

// <LegoRR.exe @0047c810>
HRESULT WINAPI DirectDraw_EnumModeCallback(LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext);

// <LegoRR.exe @0047c8d0>
BOOL __cdecl DirectDraw_Setup(BOOL fullscreen, const DirectDraw_Driver* driver, const DirectDraw_Device* device, const DirectDraw_Mode* mode,
	unsigned long xPos, unsigned long yPos, unsigned long width, unsigned long height);

// <LegoRR.exe @0047cb90>
void __cdecl DirectDraw_Flip(void);

// <LegoRR.exe @0047cbb0>
BOOL __cdecl DirectDraw_SaveBMP(IDirectDrawSurface4* surface, const char* fname);

// <LegoRR.exe @0047cee0>
void __cdecl DirectDraw_ReturnFrontBuffer(void);

// <LegoRR.exe @0047cf10>
void __cdecl DirectDraw_BlitBuffers(void);

// <LegoRR.exe @0047cfb0>
void __cdecl DirectDraw_Shutdown(void);

// Adjust the texture usage for cards that don't like 8 bit textures...
// <LegoRR.exe @0047d010>
void __cdecl DirectDraw_AdjustTextureUsage(IN OUT unsigned long* textureUsage);

// <LegoRR.exe @0047d090>
BOOL __cdecl DirectDraw_GetAvailTextureMem(OUT unsigned long* total, OUT unsigned long* avail);

// <LegoRR.exe @0047d0e0>
void __cdecl DirectDraw_Clear(const AREA2D* window, unsigned long colour);

// <LegoRR.exe @0047d1a0>
BOOL __cdecl DirectDraw_CreateClipper(BOOL fullscreen, unsigned long width, unsigned long height);

// <LegoRR.exe @0047d2c0>
void __cdecl DirectDraw_Blt8To16(IDirectDrawSurface4* target, IDirectDrawSurface4* source, PALETTEENTRY* palette);

// <LegoRR.exe @0047d590>
unsigned long __cdecl DirectDraw_GetColour(IDirectDrawSurface4* surf, unsigned long colour);

// <LegoRR.exe @0047d6b0>
unsigned long __cdecl DirectDraw_GetNumberOfBits(unsigned long mask);

#pragma endregion

}
