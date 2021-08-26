
#ifndef _GODS98_DIRECTDRAW_H_
#define _GODS98_DIRECTDRAW_H_

#include "Standard.h"

#define DIRECTDRAW_MAXDRIVERS				20
#define DIRECTDRAW_MAXDEVICES				20
#define DIRECTDRAW_MAXMODES					200
#define DIRECTDRAW_DRIVERSTRINGLEN			256
#define DIRECTDRAW_DEVICESTRINGLEN			256

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

#ifndef _GODS98COMPILE
#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct _GUID {          // size is 16
    ULONG	Data1;
    UWORD	Data2;
    UWORD	Data3;
    UCHAR	Data4[8];
} GUID;
#endif // !GUID_DEFINED
#endif // !_GODS98COMPILE

typedef struct DirectDraw_Driver {

	GUID guid;
	UCHAR desc[DIRECTDRAW_DRIVERSTRINGLEN];
	ULONG flags;

} DirectDraw_Driver, *lpDirectDraw_Driver;

typedef struct DirectDraw_Device {

	GUID guid;
	UCHAR desc[DIRECTDRAW_DEVICESTRINGLEN];
	ULONG flags;

} DirectDraw_Device, *lpDirectDraw_Device;

typedef struct DirectDraw_Mode {

	ULONG width, height, bitDepth;
	UCHAR desc[DIRECTDRAW_DEVICESTRINGLEN];
	ULONG flags;

} DirectDraw_Mode, *lpDirectDraw_Mode;

#ifdef _GODS98COMPILE

typedef struct DirectDraw_Globs {

	HWND hWnd;

	LPDIRECTDRAW4 lpDirectDraw;
	LPDIRECTDRAWSURFACE4 fSurf, bSurf, zSurf;
	LPDIRECTDRAWCLIPPER lpFrontClipper, lpBackClipper;

	lpDirectDraw_Driver driverList, selectedDriver;
	lpDirectDraw_Device deviceList, selectedDevice;
	lpDirectDraw_Mode modeList;

	ULONG driverCount;
	ULONG deviceCount;
	ULONG modeCount;

	BOOL fullScreen;
	ULONG width;
	ULONG height;

} DirectDraw_Globs, *lpDirectDraw_Globs;

extern DirectDraw_Globs directDrawGlobs;

__inline LPDIRECTDRAW4 DirectDraw()					{ return directDrawGlobs.lpDirectDraw; }
__inline LPDIRECTDRAWSURFACE4 DirectDraw_fSurf()	{ return directDrawGlobs.fSurf; }
__inline LPDIRECTDRAWSURFACE4 DirectDraw_bSurf()	{ return directDrawGlobs.bSurf; }
__inline BOOL DirectDraw_FullScreen()				{ return directDrawGlobs.fullScreen; }

#endif // _GODS98COMPILE

#ifndef _GENPROTFILE
#include "..\Src\DirectDraw.prot"
#endif // _GENPROTFILE

__inline BOOL DirectDraw_SetupFullScreen(lpDirectDraw_Driver driver, lpDirectDraw_Device device, lpDirectDraw_Mode mode)	{ return DirectDraw_Setup(TRUE, driver, device, mode, 0, 0, 320, 200); }
__inline BOOL DirectDraw_SetupWindowed(lpDirectDraw_Device device, ULONG xPos, ULONG yPos, ULONG width, ULONG height)		{ return DirectDraw_Setup(FALSE, NULL, device, NULL, xPos, yPos, width, height); }

#endif // _GODS98_DIRECTDRAW_H_
