
typedef struct Init_Globs {

	ULONG driverCount, deviceCount, modeCount;
	DirectDraw_Driver drivers[DIRECTDRAW_MAXDRIVERS];
	DirectDraw_Device devices[DIRECTDRAW_MAXDEVICES];
	DirectDraw_Mode modes[DIRECTDRAW_MAXMODES];

	lpDirectDraw_Driver selDriver;
	lpDirectDraw_Device selDevice;
	lpDirectDraw_Mode selMode;
	BOOL selFullScreen, wasFullScreen;

	DirectDraw_Mode validModes[DIRECTDRAW_MAXMODES];
	ULONG validModeCount;

} Init_Globs;

#ifndef _GENPROTFILE
#include "..\Src\Init.prot"
#endif // _GENPROTFILE
