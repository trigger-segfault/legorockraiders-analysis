
#include <ddraw.h>
#include <d3drm.h>

#include "..\inc\Standard.h"
#include "..\inc\Maths.h"
#include "..\inc\Errors.h"
#include "..\inc\Main.h"
#include "..\inc\Memory.h"
#include "..\inc\DirectDraw.h"
#include "..\inc\Bmp.h"

DirectDraw_Globs directDrawGlobs;

VOID DirectDraw_Initialise(HWND hWnd){

	directDrawGlobs.driverCount = 0;
	directDrawGlobs.driverList = NULL;
	directDrawGlobs.deviceCount = 0;
	directDrawGlobs.deviceList = NULL;
	directDrawGlobs.modeCount = 0;
	directDrawGlobs.modeList = NULL;
	directDrawGlobs.hWnd = hWnd;

	directDrawGlobs.lpDirectDraw = NULL;
	directDrawGlobs.fSurf = directDrawGlobs.bSurf = directDrawGlobs.zSurf = NULL;
	directDrawGlobs.lpFrontClipper = directDrawGlobs.lpFrontClipper = NULL;
}

BOOL WINAPI DirectDraw_EnumDriverCallback(GUID FAR *lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID lpContext) {

	directDrawGlobs.driverList[directDrawGlobs.driverCount].flags = DIRECTDRAW_FLAG_VALID;

	// Record the GUID
	if (NULL != lpGUID) directDrawGlobs.driverList[directDrawGlobs.driverCount].guid = *lpGUID;
	else directDrawGlobs.driverList[directDrawGlobs.driverCount].flags |= DIRECTDRAW_FLAG_DRIVER_PRIMARY;

#pragma message ( "TODO: Find out if driver can work in a window" )
	if (NULL == lpGUID) directDrawGlobs.driverList[directDrawGlobs.driverCount].flags |= DIRECTDRAW_FLAG_DRIVER_WINDOWOK;

	sprintf(directDrawGlobs.driverList[directDrawGlobs.driverCount].desc, "%s (%s)", lpDriverDescription, lpDriverName);

	directDrawGlobs.driverCount++;

	return TRUE;
}


BOOL DirectDraw_EnumDrivers(lpDirectDraw_Driver list, LPULONG count){

	directDrawGlobs.driverList = list;
	// Enumerate each driver and record its GUID and description
	DirectDrawEnumerate(DirectDraw_EnumDriverCallback, NULL);

	*count = directDrawGlobs.driverCount;
	return TRUE;
}


BOOL DirectDraw_EnumDevices(lpDirectDraw_Driver driver, lpDirectDraw_Device list, LPULONG count){

	LPDIRECTDRAW4 lpDD;
	LPDIRECTDRAW lpDD1;
#ifdef _USERAMP
	LPDIRECT3D2 lpD3D;
#else // _USERAMP
	LPDIRECT3D3 lpD3D;
#endif // _USERAMP
	LPGUID guid;
	BOOL res = FALSE;

	directDrawGlobs.deviceCount = 0;

	if (driver->flags & DIRECTDRAW_FLAG_DRIVER_PRIMARY) guid = NULL;
	else guid = &driver->guid;

	if (DirectDrawCreate(&driver->guid, &lpDD1, NULL) == DD_OK){
		if (lpDD1->lpVtbl->QueryInterface(lpDD1, &IID_IDirectDraw4, &lpDD) == DD_OK){
#ifdef _USERAMP
			if (lpDD->lpVtbl->QueryInterface(lpDD, &IID_IDirect3D2, &lpD3D) == DD_OK){
#else // _USERAMP
			if (lpDD->lpVtbl->QueryInterface(lpDD, &IID_IDirect3D3, &lpD3D) == DD_OK){
#endif // _USERAMP
				directDrawGlobs.deviceList = list;
				lpD3D->lpVtbl->EnumDevices(lpD3D, DirectDraw_EnumDeviceCallback, NULL);
				res = TRUE;

				lpD3D->lpVtbl->Release(lpD3D);
			} else Error_Warn(TRUE, "Unable to obtain Direct3D3");
			lpDD->lpVtbl->Release(lpDD);
		} else Error_Warn(TRUE, "Unable to obtain DirectDraw4");
		lpDD1->lpVtbl->Release(lpDD1);
	} else Error_Warn(TRUE, "Unable to create DirectDraw");

	*count = directDrawGlobs.deviceCount;

	return res;
}

static HRESULT WINAPI DirectDraw_EnumDeviceCallback(LPGUID lpGuid, LPSTR lpDeviceDescription, 
											   LPSTR lpDeviceName, LPD3DDEVICEDESC lpHWDesc, 
											   LPD3DDEVICEDESC lpHELDesc, LPVOID lpContext){

	lpDirectDraw_Device dev = &directDrawGlobs.deviceList[directDrawGlobs.deviceCount];
	LPD3DDEVICEDESC desc;

	dev->flags = DIRECTDRAW_FLAG_VALID;
	if (0 != lpHWDesc->dcmColorModel){
		dev->flags |= DIRECTDRAW_FLAG_DEVICE_HARDWARE;
		desc = lpHWDesc;
	} else desc = lpHELDesc;

	if (desc->dwFlags & D3DDD_COLORMODEL) if (D3DCOLOR_RGB == desc->dcmColorModel) dev->flags |= DIRECTDRAW_FLAG_DEVICE_COLOUR;
	if (desc->dwFlags & D3DDD_DEVICERENDERBITDEPTH){
		if (desc->dwDeviceRenderBitDepth & DDBD_8) dev->flags |= DIRECTDRAW_FLAG_DEVICE_DEPTH8;
		if (desc->dwDeviceRenderBitDepth & DDBD_16) dev->flags |= DIRECTDRAW_FLAG_DEVICE_DEPTH16;
		if (desc->dwDeviceRenderBitDepth & DDBD_24) dev->flags |= DIRECTDRAW_FLAG_DEVICE_DEPTH24;
		if (desc->dwDeviceRenderBitDepth & DDBD_32) dev->flags |= DIRECTDRAW_FLAG_DEVICE_DEPTH32;
	}

	if (desc->dwFlags & D3DDD_DEVCAPS){
		if (desc->dwDevCaps & D3DDEVCAPS_TEXTUREVIDEOMEMORY) dev->flags |= DIRECTDRAW_FLAG_DEVICE_VIDEOTEXTURE;
		else if (desc->dwDevCaps & D3DDEVCAPS_TEXTURESYSTEMMEMORY) dev->flags |= DIRECTDRAW_FLAG_DEVICE_SYSTEMTEXTURE;
	}

	dev->guid = *lpGuid;
	sprintf(dev->desc, "%s (%s)", lpDeviceName, lpDeviceDescription);

	directDrawGlobs.deviceCount++;

	return D3DENUMRET_OK;
}

/*
if (lpHELDesc->dwFlags & D3DDD_COLORMODEL) if (D3DCOLOR_RGB == lpHELDesc->dcmColorModel) dev->flags |= DIRECTDRAW_FLAG_DEVICE_COLOUR;
	if (lpHELDesc->dwFlags & D3DDD_DEVICERENDERBITDEPTH){
		if (DDBD_8 & lpHELDesc->dwDeviceRenderBitDepth) dev->flags |= DIRECTDRAW_FLAG_DEVICE_DEPTH8;
		if (DDBD_16 & lpHELDesc->dwDeviceRenderBitDepth) dev->flags |= DIRECTDRAW_FLAG_DEVICE_DEPTH16;
		if (DDBD_24 & lpHELDesc->dwDeviceRenderBitDepth) dev->flags |= DIRECTDRAW_FLAG_DEVICE_DEPTH24;
		if (DDBD_32 & lpHELDesc->dwDeviceRenderBitDepth) dev->flags |= DIRECTDRAW_FLAG_DEVICE_DEPTH32;
	}

	// Don't bother supporting zbuffers for now...
#pragma message ( "ZBuffer creation is ignored for now" )
	
//	if (lpHELDesc->dwFlags & D3DDD_DEVICEZBUFFERBITDEPTH){
//		if (DDBD_8 & lpHELDesc->dwDeviceZBufferBitDepth) dev->flags |= DIRECTDRAW_FLAG_DEVICE_ZBUFF8;
//		if (DDBD_16 & lpHELDesc->dwDeviceZBufferBitDepth) dev->flags |= DIRECTDRAW_FLAG_DEVICE_ZBUFF16;
//		if (DDBD_24 & lpHELDesc->dwDeviceZBufferBitDepth) dev->flags |= DIRECTDRAW_FLAG_DEVICE_ZBUFF24;
//		if (DDBD_32 & lpHELDesc->dwDeviceZBufferBitDepth) dev->flags |= DIRECTDRAW_FLAG_DEVICE_ZBUFF32;
//	}

	if (lpHWDesc->dwFlags & D3DDD_DEVICERENDERBITDEPTH){
		if (DDBD_8 & lpHWDesc->dwDeviceRenderBitDepth) dev->flags |= DIRECTDRAW_FLAG_DEVICE_DEPTH8;
		if (DDBD_16 & lpHWDesc->dwDeviceRenderBitDepth) dev->flags |= DIRECTDRAW_FLAG_DEVICE_DEPTH16;
		if (DDBD_24 & lpHWDesc->dwDeviceRenderBitDepth) dev->flags |= DIRECTDRAW_FLAG_DEVICE_DEPTH24;
		if (DDBD_32 & lpHWDesc->dwDeviceRenderBitDepth) dev->flags |= DIRECTDRAW_FLAG_DEVICE_DEPTH32;
	}
//	if (lpHWDesc->dwFlags & D3DDD_DEVICEZBUFFERBITDEPTH){
//		if (DDBD_8 & lpHWDesc->dwDeviceZBufferBitDepth) dev->flags |= DIRECTDRAW_FLAG_DEVICE_ZBUFF8;
//		if (DDBD_16 & lpHWDesc->dwDeviceZBufferBitDepth) dev->flags |= DIRECTDRAW_FLAG_DEVICE_ZBUFF16;
//		if (DDBD_24 & lpHWDesc->dwDeviceZBufferBitDepth) dev->flags |= DIRECTDRAW_FLAG_DEVICE_ZBUFF24;
//		if (DDBD_32 & lpHWDesc->dwDeviceZBufferBitDepth) dev->flags |= DIRECTDRAW_FLAG_DEVICE_ZBUFF32;
//	}
*/

BOOL DirectDraw_EnumModes(lpDirectDraw_Driver driver, BOOL fullScreen, lpDirectDraw_Mode list, LPULONG count){

	LPDIRECTDRAW4 lpDD;
	LPDIRECTDRAW lpDD1;
	LPGUID guid;
	BOOL res = FALSE;

	directDrawGlobs.modeCount = 0;

	if (driver) {
		if (driver->flags & DIRECTDRAW_FLAG_VALID){

			if (driver->flags & DIRECTDRAW_FLAG_DRIVER_PRIMARY) guid = NULL;
			else guid = &driver->guid;

			if (DirectDrawCreate(guid, &lpDD1, NULL) == DD_OK){
				if (lpDD1->lpVtbl->QueryInterface(lpDD1, &IID_IDirectDraw4, &lpDD) == DD_OK){
					
					directDrawGlobs.modeList = list;
					lpDD->lpVtbl->EnumDisplayModes(lpDD, 0, NULL, &fullScreen, DirectDraw_EnumModeCallback);
					res = TRUE;
					
					lpDD->lpVtbl->Release(lpDD);
				} else Error_Warn(TRUE, "Unable to obtain DirectDraw2");
				lpDD1->lpVtbl->Release(lpDD1);
			} else Error_Warn(TRUE, "Unable to create DirectDraw");
		} else Error_Fatal(TRUE, "Invalid driver passed to DirectDraw_EnumModes()");
	} else Error_Fatal(TRUE, "NULL passed as driver to DirectDraw_EnumModes()");
			
	*count = directDrawGlobs.modeCount;
	return res;
}

static HRESULT WINAPI DirectDraw_EnumModeCallback(LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext){

	lpDirectDraw_Mode mode = &directDrawGlobs.modeList[directDrawGlobs.modeCount];
	LPBOOL fullScreen = lpContext;

	mode->flags = DIRECTDRAW_FLAG_VALID;
	mode->width = lpDDSurfaceDesc->dwWidth;
	mode->height = lpDDSurfaceDesc->dwHeight;
	mode->bitDepth = lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount;

	if ((*fullScreen)) sprintf(mode->desc, "%ix%i (%i bit)", lpDDSurfaceDesc->dwWidth, lpDDSurfaceDesc->dwHeight, lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount);
	else sprintf(mode->desc, "%ix%i", lpDDSurfaceDesc->dwWidth, lpDDSurfaceDesc->dwHeight);

	if (!(*fullScreen) && directDrawGlobs.modeCount) {
		if (mode->bitDepth == Main_GetWindowsBitDepth()) directDrawGlobs.modeCount++;
		else mode->flags &= ~DIRECTDRAW_FLAG_VALID;
	} else directDrawGlobs.modeCount++;

	return D3DENUMRET_OK;
}


/*
BOOL DirectDraw_SetupFullScreen(lpDirectDraw_Driver driver, lpDirectDraw_Device device, lpDirectDraw_Mode mode){

	LPDIRECTDRAW ddraw1;
//	LPDIRECTDRAWSURFACE fSurf1;
	DDSURFACEDESC2 desc;
	DDSCAPS2 ddscaps;
	LPGUID guid;
	ULONG width = 320, height = 200, bpp = 16;
	ULONG zBuffDepth = 0;
	BOOL doubleBuffered = TRUE;

	if (driver) if (!(driver->flags & DIRECTDRAW_FLAG_VALID)) driver = NULL;
	if (device) if (!(device->flags & DIRECTDRAW_FLAG_VALID)) device = NULL;
	if (mode) if (!(mode->flags & DIRECTDRAW_FLAG_VALID)) mode = NULL;

	if (device) {
		if (device->flags & DIRECTDRAW_FLAG_DEVICE_ZBUFF8) zBuffDepth = 8;
		if (device->flags & DIRECTDRAW_FLAG_DEVICE_ZBUFF16) zBuffDepth = 16;
		if (device->flags & DIRECTDRAW_FLAG_DEVICE_ZBUFF24) zBuffDepth = 24;
		if (device->flags & DIRECTDRAW_FLAG_DEVICE_ZBUFF32) zBuffDepth = 32;
	}

	if (mode) {
		width = mode->width;
		height = mode->height;
		bpp = mode->bitDepth;
	}

	directDrawGlobs.width = width;
	directDrawGlobs.height = height;
	directDrawGlobs.fullScreen = TRUE;

	if (NULL == driver) guid = NULL;
	else if (driver->flags & DIRECTDRAW_FLAG_DRIVER_PRIMARY) guid = NULL;
	else guid = &driver->guid;

	Main_SetupDisplay(TRUE, 0, 0, width, height);

	if (DirectDrawCreate(guid, &ddraw1, 0) == DD_OK){
		if (ddraw1->lpVtbl->QueryInterface(ddraw1, &IID_IDirectDraw4, &directDrawGlobs.lpDirectDraw) == DD_OK){
			if (directDrawGlobs.lpDirectDraw->lpVtbl->SetCooperativeLevel(directDrawGlobs.lpDirectDraw, directDrawGlobs.hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN) == DD_OK){
				if (directDrawGlobs.lpDirectDraw->lpVtbl->SetDisplayMode(directDrawGlobs.lpDirectDraw, width, height, bpp, 0, 0) == DD_OK){

					memset(&desc, 0, sizeof(desc));
					desc.dwSize = sizeof(desc);
					desc.dwFlags = DDSD_BACKBUFFERCOUNT | DDSD_CAPS;
					desc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_3DDEVICE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
					desc.dwBackBufferCount = 1;
					
					if (directDrawGlobs.lpDirectDraw->lpVtbl->CreateSurface(directDrawGlobs.lpDirectDraw, &desc, &directDrawGlobs.fSurf, 0) == DD_OK){
//						if (fSurf1->lpVtbl->QueryInterface(fSurf1, &IID_IDirectDrawSurface3, &directDrawGlobs.fSurf) == S_OK){
							ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
							if (directDrawGlobs.fSurf->lpVtbl->GetAttachedSurface(directDrawGlobs.fSurf, &ddscaps, &directDrawGlobs.bSurf) == DD_OK){
								if (DirectDraw_CreateClipper(FALSE, width, height)){
									if (DirectDraw_SetupZBuffer(zBuffDepth, width, height)){
										if (Main_SetupDirect3D(device, ddraw1, directDrawGlobs.bSurf, doubleBuffered)){
										
											// Everything went OK, so tidy up and return
							//				fSurf1->lpVtbl->Release(fSurf1);
											ddraw1->lpVtbl->Release(ddraw1);
											return TRUE;
											
										}
									}
								}
								directDrawGlobs.bSurf->lpVtbl->Release(directDrawGlobs.bSurf);
							} else Error_Warn(TRUE, "Cannot Get Attached Back Surface");
							directDrawGlobs.fSurf->lpVtbl->Release(directDrawGlobs.fSurf);
						//} else Error_Warn(TRUE, "Cannot obtain Front Surface3");
					//	fSurf1->lpVtbl->Release(fSurf1);
					} else Error_Warn(TRUE, "Cannot create Front surface1");
				} else Error_Warn(TRUE, "Cannot set Display Mode");
			} else Error_Warn(TRUE, "Cannot set Cooperative Level");
			directDrawGlobs.lpDirectDraw->lpVtbl->Release(directDrawGlobs.lpDirectDraw);
		} else Error_Warn(TRUE, "Cannot obtain DirectDraw2");
		ddraw1->lpVtbl->Release(ddraw1);
	} else Error_Warn(TRUE, "Cannot create DirectDraw");

	return FALSE;
}

BOOL DirectDraw_SetupWindowed(lpDirectDraw_Device device, ULONG xPos, ULONG yPos, ULONG width, ULONG height){
	
	DDSURFACEDESC2		ddsd;
//	LPDIRECTDRAWSURFACE lpSurf;
	LPDIRECTDRAW		ddraw1;
	BOOL doubleBuffered = FALSE;
	BOOL palOK = FALSE;
	DDPIXELFORMAT pixelFormat;

	directDrawGlobs.width = width;
	directDrawGlobs.height = height;
	directDrawGlobs.fullScreen = FALSE;

	if (device) if (!(device->flags & DIRECTDRAW_FLAG_VALID)) device = NULL;

	Main_SetupDisplay(FALSE, xPos, yPos, width, height);

	if (DirectDrawCreate(NULL, &ddraw1, NULL) == DD_OK){
		if (ddraw1->lpVtbl->QueryInterface(ddraw1, &IID_IDirectDraw4, &directDrawGlobs.lpDirectDraw) == DD_OK){
			
			// Set normal cooperative level
			if (directDrawGlobs.lpDirectDraw->lpVtbl->SetCooperativeLevel(directDrawGlobs.lpDirectDraw, directDrawGlobs.hWnd, DDSCL_NORMAL) == DD_OK){
				
				// Create the front buffer
				memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
				ddsd.dwSize = sizeof(DDSURFACEDESC2);
				ddsd.dwFlags = DDSD_CAPS;
				ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_3DDEVICE;
				
				if (directDrawGlobs.lpDirectDraw->lpVtbl->CreateSurface(directDrawGlobs.lpDirectDraw, &ddsd, &directDrawGlobs.fSurf, NULL) == DD_OK){
//					if (lpSurf->lpVtbl->QueryInterface(lpSurf, &IID_IDirectDrawSurface3, &directDrawGlobs.fSurf) == DD_OK){
					//	lpSurf->lpVtbl->Release(lpSurf);
						
						// Create the back buffer
						memset(&ddsd, 0, sizeof(DDSURFACEDESC2));
						ddsd.dwSize = sizeof(DDSURFACEDESC2);
						ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
						ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
						ddsd.dwWidth  = width;
						ddsd.dwHeight = height;
						
						if (directDrawGlobs.lpDirectDraw->lpVtbl->CreateSurface(directDrawGlobs.lpDirectDraw, &ddsd, &directDrawGlobs.bSurf, NULL) == DD_OK){

//							if (lpSurf->lpVtbl->QueryInterface(lpSurf, &IID_IDirectDrawSurface3, &directDrawGlobs.bSurf) == DD_OK){
//								lpSurf->lpVtbl->Release(lpSurf);

								memset(&pixelFormat, 0, sizeof(DDPIXELFORMAT));
								pixelFormat.dwSize = sizeof(DDPIXELFORMAT);
								if (DD_OK == directDrawGlobs.bSurf->lpVtbl->GetPixelFormat(directDrawGlobs.bSurf, &pixelFormat)){
									if (pixelFormat.dwFlags & DDPF_PALETTEINDEXED8) {
										PALETTEENTRY pal[256];
										LPDIRECTDRAWPALETTE newpal;
										ULONG loop;

										GetPaletteEntries(GetStockObject(DEFAULT_PALETTE), 0, 255, pal);
										for (loop=0 ; loop<10 ; loop++) pal[loop].peFlags = pal[255-loop].peFlags = PC_EXPLICIT;
										for ( ; loop<246 ; loop++) {
											pal[loop].peFlags = PC_NOCOLLAPSE;
											pal[loop].peRed = pal[loop].peGreen = pal[loop].peBlue = (UCHAR) (((loop * 235) / 255) + 10);
										}

										palOK = FALSE;
										if (DD_OK == directDrawGlobs.lpDirectDraw->lpVtbl->CreatePalette(directDrawGlobs.lpDirectDraw, DDPCAPS_8BIT, pal, &newpal, NULL)){
											if (DD_OK == directDrawGlobs.bSurf->lpVtbl->SetPalette(directDrawGlobs.bSurf, newpal)){
												if (DD_OK == directDrawGlobs.fSurf->lpVtbl->SetPalette(directDrawGlobs.fSurf, newpal)){
													palOK = TRUE;
												} else Error_Warn(TRUE, "Unable to set palette on front surface");
											} else Error_Warn(TRUE, "Unable to set palette on back surface");
										} else Error_Warn(TRUE, "Unable to create palette");
									} else palOK = TRUE;
								} else palOK = FALSE;

								if (palOK){
									if (DirectDraw_CreateClipper(TRUE, width, height)){
										if (Main_SetupDirect3D(device, ddraw1, directDrawGlobs.bSurf, doubleBuffered)){
											
											return TRUE;
											
										}
									}
								} else Error_Warn(TRUE, "Error creating palette");
							//} else Error_Warn(TRUE, "Unable to obtain front Surface");
						} else Error_Warn(TRUE, "Unable to create back Surface1");
					//} else Error_Warn(TRUE, "Unable to obtain front Surface");
				} else Error_Warn(TRUE, "Unable to create front Surface1");
			} else Error_Warn(TRUE, "Unable to set Cooperative level");
		}
	}
	return FALSE;
}

*/

BOOL DirectDraw_Setup(BOOL fullscreen, lpDirectDraw_Driver driver, lpDirectDraw_Device device, lpDirectDraw_Mode mode, ULONG xPos, ULONG yPos, ULONG width, ULONG height){

	LPDIRECTDRAW ddraw1;
	DDSURFACEDESC2 desc;
	LPGUID guid;
	ULONG bpp = 16;
	HRESULT r;

	if (driver) if (!(driver->flags & DIRECTDRAW_FLAG_VALID)) driver = NULL;
	if (device) if (!(device->flags & DIRECTDRAW_FLAG_VALID)) device = NULL;
	if (mode) if (!(mode->flags & DIRECTDRAW_FLAG_VALID)) mode = NULL;

	if (mode) {
		width = mode->width;
		height = mode->height;
		bpp = mode->bitDepth;
	}

	directDrawGlobs.width = width;
	directDrawGlobs.height = height;
	directDrawGlobs.fullScreen = fullscreen;

	if (NULL == driver) guid = NULL;
	else if (driver->flags & DIRECTDRAW_FLAG_DRIVER_PRIMARY) guid = NULL;
	else guid = &driver->guid;

	Main_SetupDisplay(fullscreen, xPos, yPos, width, height);

	if (DD_OK == DirectDrawCreate(guid, &ddraw1, 0)){
		if (DD_OK == ddraw1->lpVtbl->QueryInterface(ddraw1, &IID_IDirectDraw4, &directDrawGlobs.lpDirectDraw)){
			if (DD_OK == directDrawGlobs.lpDirectDraw->lpVtbl->SetCooperativeLevel(directDrawGlobs.lpDirectDraw, directDrawGlobs.hWnd, fullscreen?(DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN):DDSCL_NORMAL)){
				if (fullscreen) r = directDrawGlobs.lpDirectDraw->lpVtbl->SetDisplayMode(directDrawGlobs.lpDirectDraw, width, height, bpp, 0, 0);
				else r = DD_OK;

				if (DD_OK == r) {
					memset(&desc, 0, sizeof(desc));
					desc.dwSize = sizeof(desc);
					desc.dwFlags = DDSD_CAPS;
					desc.ddsCaps.dwCaps = DDSCAPS_3DDEVICE | DDSCAPS_PRIMARYSURFACE;
					if (fullscreen) {
						desc.dwFlags |= DDSD_BACKBUFFERCOUNT;
						desc.dwBackBufferCount = 1;
						desc.ddsCaps.dwCaps |= DDSCAPS_FLIP | DDSCAPS_COMPLEX;
					}
					
					if (DD_OK == directDrawGlobs.lpDirectDraw->lpVtbl->CreateSurface(directDrawGlobs.lpDirectDraw, &desc, &directDrawGlobs.fSurf, 0)){
						
						if (!fullscreen) {
							// Create the back buffer
							desc.ddsCaps.dwCaps &= ~DDSCAPS_PRIMARYSURFACE;
							desc.ddsCaps.dwCaps |= DDSCAPS_OFFSCREENPLAIN;
							desc.dwFlags |= DDSD_HEIGHT | DDSD_WIDTH;
							desc.dwWidth  = width;
							desc.dwHeight = height;
							r = directDrawGlobs.lpDirectDraw->lpVtbl->CreateSurface(directDrawGlobs.lpDirectDraw, &desc, &directDrawGlobs.bSurf, NULL);
						} else {
							DDSCAPS2 ddscaps;
							memset(&ddscaps, 0, sizeof(ddscaps));
							ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
							r = directDrawGlobs.fSurf->lpVtbl->GetAttachedSurface(directDrawGlobs.fSurf, &ddscaps, &directDrawGlobs.bSurf);
						}
						
						if (DD_OK == r) {
							if (DirectDraw_CreateClipper(fullscreen, width, height)){
								if (Main_SetupDirect3D(device, ddraw1, directDrawGlobs.bSurf, fullscreen)){

									// Everything went OK, so tidy up and return
									ddraw1->lpVtbl->Release(ddraw1);

									if (fullscreen) ShowCursor(FALSE);

									return TRUE;
									
								}
							}
							directDrawGlobs.bSurf->lpVtbl->Release(directDrawGlobs.bSurf);
							directDrawGlobs.bSurf = NULL;
						} else Error_Warn(TRUE, "Error creating back surface");
						directDrawGlobs.fSurf->lpVtbl->Release(directDrawGlobs.fSurf);
						directDrawGlobs.fSurf = NULL;
					} else Error_Warn(TRUE, "Error creating front surface");
				} else Error_Warn(TRUE, "Cannot set Display Mode");
			} else Error_Warn(TRUE, "Cannot set Cooperative Level");
			directDrawGlobs.lpDirectDraw->lpVtbl->Release(directDrawGlobs.lpDirectDraw);
			directDrawGlobs.lpDirectDraw = NULL;
		} else Error_Warn(TRUE, "Cannot obtain DirectDraw2");
		ddraw1->lpVtbl->Release(ddraw1);
	} else Error_Warn(TRUE, "Cannot create DirectDraw");
	
	return FALSE;
}

/*
static BOOL DirectDraw_SetupZBuffer(ULONG depth, ULONG width, ULONG height){

//	LPDIRECTDRAWSURFACE zSurf1;
	DDSURFACEDESC2 desc;
//	HRESULT rval;

	if (depth){
		
		memset(&desc, 0, sizeof(desc));
		desc.dwSize = sizeof(desc);
		desc.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS | DDSD_ZBUFFERBITDEPTH;
		desc.dwWidth = width;
		desc.dwHeight = height;
//		desc.dwZBufferBitDepth = depth;


//		desc.ddsCaps.dwCaps = DDSCAPS2_ZBUFFER | DDSCAPS2_VIDEOMEMORY;
//
//		Error_Debug("DirectDraw Setup: Trying Video memory for ZBuffer\n");
//		rval = directDrawGlobs.lpDirectDraw->lpVtbl->CreateSurface(directDrawGlobs.lpDirectDraw, &desc, &zSurf1, NULL);
//		if (D3DERR_ZBUFF_NEEDS_SYSTEMMEMORY == rval){
//			Error_Debug("DirectDraw Setup: Using System memory for ZBuffer\n");
//			desc.ddsCaps.dwCaps = DDSCAPS2_ZBUFFER | DDSCAPS2_SYSTEMMEMORY;
//			rval = directDrawGlobs.lpDirectDraw->lpVtbl->CreateSurface(directDrawGlobs.lpDirectDraw, &desc, &zSurf1, 0);
//		}

//		desc.ddsCaps.dwCaps = DDSCAPS_ZBUFFER;
//		rval = directDrawGlobs.lpDirectDraw->lpVtbl->CreateSurface(directDrawGlobs.lpDirectDraw, &desc, &zSurf1, NULL);
//		
//		Error_Debug(Error_Format("rval == %d", rval));
//		
//		if (DD_OK == rval){
//			if (zSurf1->lpVtbl->QueryInterface(zSurf1, &IID_IDirectDrawSurface3, &directDrawGlobs.zSurf) == S_OK){
//				if (directDrawGlobs.bSurf->lpVtbl->AddAttachedSurface(directDrawGlobs.bSurf, directDrawGlobs.zSurf) == DD_OK){
//
//					return TRUE;
//
//				} else {
//					Error_Warn(TRUE, "Cannot Add ZBuffer as Attached Surface");
//					directDrawGlobs.zSurf->lpVtbl->Release(directDrawGlobs.zSurf);
//				}
//			} else Error_Warn(TRUE, "Cannot obtain ZBuffer Surface3");
//			zSurf1->lpVtbl->Release(zSurf1);
//		} else Error_Warn(TRUE, "Cannot create ZBuffer Surface1");

	} else {
		directDrawGlobs.zSurf = NULL;
		return TRUE;
	}

	return FALSE;
}
*/	

VOID DirectDraw_Flip(VOID){

	HRESULT r;

	if (directDrawGlobs.fullScreen) {
		r = directDrawGlobs.fSurf->lpVtbl->Flip(directDrawGlobs.fSurf, 0, DDFLIP_WAIT);
		Error_Fatal(r == DDERR_SURFACELOST, "Surface lost");
	}
	else DirectDraw_BlitBuffers();
}

VOID DirectDraw_SaveBackBuffer565(LPUCHAR fname) {

#include <stdio.h>

	if (mainGlobs.flags & MAIN_FLAG_DEBUGMODE) {
		FILE *dfp;
		DDSURFACEDESC2 desc;
		ULONG loop, x;
		LPULONG data;
		LPUCHAR buffer, line;

		memset(&desc, 0, sizeof(desc));
		desc.dwSize = sizeof(desc);
		if (DD_OK == (directDrawGlobs.bSurf->lpVtbl->Lock(directDrawGlobs.bSurf, NULL, &desc, DDLOCK_WAIT, NULL))) {
			if (16 == desc.ddpfPixelFormat.dwRGBBitCount) {
				if (buffer = Mem_Alloc(desc.dwWidth * desc.dwHeight * 3)) {
					for (loop=0 ; loop<desc.dwHeight ; loop++) {
						data = (LPULONG) &((LPUCHAR) desc.lpSurface)[desc.lPitch * loop];
						line = &buffer[desc.dwWidth * 3 * loop];
						for (x=0 ; x<desc.dwWidth / 2 ; x++) {
							line[(x * 6) + 3] = (UCHAR) ((data[x] >> (32 - 5)) & 0x1f) << (8 - 5);
							line[(x * 6) + 4] = (UCHAR) ((data[x] >> (32 - 5 - 6)) & 0x3f) << (8 - 6);
							line[(x * 6) + 5] = (UCHAR) ((data[x] >> (32 - 5 - 6 - 5)) & 0x1f) << (8 - 5);
							line[(x * 6) + 0] = (UCHAR) ((data[x] >> (32 - 5 - 6 - 5 - 5)) & 0x1f) << (8 - 5);
							line[(x * 6) + 1] = (UCHAR) ((data[x] >> (32 - 5 - 6 - 5 - 5 - 6)) & 0x3f) << (8 - 6);
							line[(x * 6) + 2] = (UCHAR) ((data[x] >> (32 - 5 - 6 - 5 - 5 - 6 - 5)) & 0x1f) << (8 - 5);
						}
					}
				}
			}
			directDrawGlobs.bSurf->lpVtbl->Unlock(directDrawGlobs.bSurf, NULL);
		}

		if (buffer) {
			if (dfp = fopen(fname, "wb")) {
				fwrite(buffer, 3, desc.dwWidth * desc.dwHeight, dfp);
				fclose(dfp);
			}
			Mem_Free(buffer);
		}
	}
}

BOOL DirectDraw_SaveBMP(LPDIRECTDRAWSURFACE4 surface, LPUCHAR fname) {

	lpFile ofp;
	DDSURFACEDESC2 desc;
	LPUCHAR buffer;
	ULONG loop, x, y;
	ULONG ul, bytesPerPixel, bitsPerPixel;
	ULONG rBits = 0, gBits = 0, bBits = 0;
	ULONG rShift, gShift, bShift;
	BOOL ok = FALSE;
	BMP_Header header = { 0 };
	ULONG bufferSize, lineWidth;

	if (ofp = File_Open(fname, "wb")) {
		memset(&desc, 0, sizeof(desc));
		desc.dwSize = sizeof(desc);
		if (DD_OK == surface->lpVtbl->Lock(surface, NULL, &desc, DDLOCK_WAIT, NULL)) {

			lineWidth = (desc.dwWidth * 3);
			lineWidth = ((lineWidth / 4) * 4) + ((lineWidth % 4)?4:0);
			bufferSize = lineWidth * desc.dwHeight;

			if (buffer = Mem_Alloc(bufferSize)) {
				memset(buffer, 0, bufferSize);

				bitsPerPixel = desc.ddpfPixelFormat.dwRGBBitCount;
				bytesPerPixel = bitsPerPixel / 8;
				for (loop=0 ; loop<32 ; loop++) if ((desc.ddpfPixelFormat.dwRBitMask >> loop) & 0x1) rBits++;
				for (loop=0 ; loop<32 ; loop++) if ((desc.ddpfPixelFormat.dwGBitMask >> loop) & 0x1) gBits++;
				for (loop=0 ; loop<32 ; loop++) if ((desc.ddpfPixelFormat.dwBBitMask >> loop) & 0x1) bBits++;
				rShift = gBits + bBits;
				gShift = bBits;
				bShift = 0;

				for (y=0 ; y<desc.dwHeight ; y++) {
					for (x=0 ; x<desc.dwWidth ; x++) {
						ul = ((LPULONG)(&((LPUCHAR)desc.lpSurface)[(y * desc.lPitch) + (x * bytesPerPixel)]))[0];
						ul >>= 32 - bitsPerPixel;
						buffer[(((desc.dwHeight - 1) - y) * lineWidth) + (x * 3) + 2] = (UCHAR) (((ul >> rShift) << (8 - rBits)));
						buffer[(((desc.dwHeight - 1) - y) * lineWidth) + (x * 3) + 1] = (UCHAR) (((ul >> gShift) << (8 - gBits)));
						buffer[(((desc.dwHeight - 1) - y) * lineWidth) + (x * 3) + 0] = (UCHAR) (((ul >> bShift) << (8 - bBits)));
					}
				}

				ok = TRUE;
			}

			surface->lpVtbl->Unlock(surface, NULL);

			header.bmp_str[0] = 'B';
			header.bmp_str[1] = 'M';
			header.file_size = bufferSize + sizeof(BMP_Header);
			header.img_offset = sizeof(BMP_Header);
			header.img_header_size = 40;
			header.wid = desc.dwWidth;
			header.hgt = desc.dwHeight;
			header.planes = 1;
			header.bits_per_pixel = 24;
			header.compression = 0;
			header.comp_img_size = 0;
			header.horz_res = 1;
			header.vert_res = 1;
			header.colours = 0;
			header.important_colours = 0;

			if (ok) {
				File_Write(&header, sizeof(BMP_Header), 1, ofp);
				File_Write(buffer, bufferSize, 1, ofp);
			}

			Mem_Free(buffer);
		}
		File_Close(ofp);
	}

	return ok;
}

VOID DirectDraw_ReturnFrontBuffer(VOID) {

	if (directDrawGlobs.fullScreen) {
		directDrawGlobs.bSurf->lpVtbl->Blt(directDrawGlobs.bSurf, NULL, directDrawGlobs.fSurf, NULL, DDBLT_WAIT, NULL);
	}
}

VOID DirectDraw_BlitBuffers(void){

	POINT pt;
	RECT src, dest;
	HRESULT r;

	// Calculate the destination blitting rectangle
//	GetClientRect(directDrawGlobs.hWnd, &dest);
	pt.x = pt.y = 0;
	dest.top = dest.left = 0;
	dest.right = directDrawGlobs.width;
	dest.bottom = directDrawGlobs.height;
	ClientToScreen(directDrawGlobs.hWnd, &pt);
	OffsetRect(&dest, pt.x, pt.y);

	// Fill out the source of the blit
	src.left = 0;
	src.top = 0;
	src.right = directDrawGlobs.width;
	src.bottom = directDrawGlobs.height;

	r = directDrawGlobs.fSurf->lpVtbl->Blt(directDrawGlobs.fSurf, &dest, directDrawGlobs.bSurf, &src, DDBLT_WAIT, NULL);
	Error_Fatal(r == DDERR_SURFACELOST, "Front surface lost");

/*		while (TRUE){

		if ((ddrval = directDrawGlobs.fSurf->lpVtbl->Blt(directDrawGlobs.fSurf, &dest, directDrawGlobs.bSurf, &src, DDBLT_WAIT, NULL)) == DD_OK){
			break;
		if(ddrval == DDERR_SURFACELOST) if(!Ddraw_RestoreSurfaces()) break;
		if(ddrval != DDERR_WASSTILLDRAWING) break;
	}

*/

//	return Succeeded;
}

VOID DirectDraw_Shutdown(VOID){

	if (directDrawGlobs.fSurf) directDrawGlobs.fSurf->lpVtbl->Release(directDrawGlobs.fSurf);
	if (directDrawGlobs.lpFrontClipper) directDrawGlobs.lpFrontClipper->lpVtbl->Release(directDrawGlobs.lpFrontClipper);
	if (directDrawGlobs.lpBackClipper) directDrawGlobs.lpBackClipper->lpVtbl->Release(directDrawGlobs.lpBackClipper);
	if (directDrawGlobs.lpDirectDraw){
		if (directDrawGlobs.fullScreen) directDrawGlobs.lpDirectDraw->lpVtbl->RestoreDisplayMode(directDrawGlobs.lpDirectDraw);
		if (directDrawGlobs.lpDirectDraw) directDrawGlobs.lpDirectDraw->lpVtbl->Release(directDrawGlobs.lpDirectDraw);
	}
}

VOID DirectDraw_AdjustTextureUsage(LPULONG textureUsage) {

	// Adjust the texture usage for cards that don't like 8 bit textures...

	DDPIXELFORMAT pixelFormat;

	memset(&pixelFormat, 0, sizeof(pixelFormat));
	pixelFormat.dwSize = sizeof(DDPIXELFORMAT);

	if (D3DRM_OK != lpDevice()->lpVtbl->FindPreferredTextureFormat(lpDevice(), DDBD_8, D3DRMFPTF_PALETTIZED, &pixelFormat)) {

		memset(&pixelFormat, 0, sizeof(pixelFormat));
		pixelFormat.dwSize = sizeof(DDPIXELFORMAT);
		
		if (D3DRM_OK == lpDevice()->lpVtbl->FindPreferredTextureFormat(lpDevice(), DDBD_16, 0, &pixelFormat)) {

			*textureUsage *= (pixelFormat.dwRGBBitCount / 8);

		}
	}
}

BOOL DirectDraw_GetAvailTextureMem(LPULONG total, LPULONG avail){

	DDSCAPS2 ddsc;

	memset(&ddsc, 0, sizeof(ddsc));
	ddsc.dwCaps = DDSCAPS_TEXTURE;
	*total = 0;
	*avail = 0;
	if (DD_OK == directDrawGlobs.lpDirectDraw->lpVtbl->GetAvailableVidMem(directDrawGlobs.lpDirectDraw, &ddsc, total, avail)) return TRUE;

	return FALSE;
}

BOOL DirectDraw_GetAvailVideoMem(LPULONG total, LPULONG avail){

	DDSCAPS2 ddsc;

	memset(&ddsc, 0, sizeof(ddsc));
	ddsc.dwCaps = DDSCAPS_VIDEOMEMORY;
	*total = 0;
	*avail = 0;
	if (DD_OK == directDrawGlobs.lpDirectDraw->lpVtbl->GetAvailableVidMem(directDrawGlobs.lpDirectDraw, &ddsc, total, avail)) return TRUE;

	return FALSE;
}

VOID DirectDraw_Clear(LPAREA2D window, ULONG colour){

	DDBLTFX bltFX;

	memset(&bltFX, 0, sizeof(DDBLTFX));
	bltFX.dwSize = sizeof(DDBLTFX);
	bltFX.dwFillColor = DirectDraw_GetColour(directDrawGlobs.bSurf, colour);

	if (window) {
	RECT rect = { (ULONG) window->x, (ULONG) window->y, (ULONG) (window->x + window->width), (ULONG) (window->y + window->height) };
		directDrawGlobs.bSurf->lpVtbl->Blt(directDrawGlobs.bSurf, &rect, NULL, NULL, DDBLT_COLORFILL|DDBLT_WAIT, &bltFX);
	} else directDrawGlobs.bSurf->lpVtbl->Blt(directDrawGlobs.bSurf, NULL, NULL, NULL, DDBLT_COLORFILL|DDBLT_WAIT, &bltFX);
}

static BOOL DirectDraw_CreateClipper(BOOL fullscreen, ULONG width, ULONG height){

	HRGN handle;
	ULONG size;
	RGNDATA *region;

	if (directDrawGlobs.lpDirectDraw->lpVtbl->CreateClipper(directDrawGlobs.lpDirectDraw, 0, &directDrawGlobs.lpBackClipper, NULL) == DD_OK){

		handle = CreateRectRgn(0, 0, width, height);
		size = GetRegionData(handle, 0, NULL);
		region = Mem_Alloc(size);
		GetRegionData(handle, size, region);

		if (DD_OK == directDrawGlobs.lpBackClipper->lpVtbl->SetClipList(directDrawGlobs.lpBackClipper, region, 0)){
			
			Mem_Free(region);

			if (directDrawGlobs.bSurf->lpVtbl->SetClipper(directDrawGlobs.bSurf, directDrawGlobs.lpBackClipper) == DD_OK){
				if (!fullscreen) {
					// Create the window clipper
					if (directDrawGlobs.lpDirectDraw->lpVtbl->CreateClipper(directDrawGlobs.lpDirectDraw, 0, &directDrawGlobs.lpFrontClipper, NULL) == DD_OK){
						// Associate the clipper with the window (obtain window sizes).
						if (directDrawGlobs.lpFrontClipper->lpVtbl->SetHWnd(directDrawGlobs.lpFrontClipper, 0, directDrawGlobs.hWnd) == DD_OK){
							if (directDrawGlobs.fSurf->lpVtbl->SetClipper(directDrawGlobs.fSurf, directDrawGlobs.lpFrontClipper) == DD_OK){
								
								return TRUE;
								
							} else Error_Warn(TRUE, "Cannot attach clipper to front buffer");
						} else Error_Warn(TRUE, "Cannot initialise clipper from hWnd");
					} else Error_Warn(TRUE, "Cannot create front clipper");
				} else return TRUE;
				
			} else Error_Warn(TRUE, "Cannot attach clipper to back buffer");
			directDrawGlobs.lpBackClipper->lpVtbl->Release(directDrawGlobs.lpBackClipper);
			directDrawGlobs.lpBackClipper = NULL;
		} else Error_Warn(TRUE, "Cannot set clip list");
		Mem_Free(region);

	}

	return FALSE;
}

VOID DirectDraw_Blt8To16(LPDIRECTDRAWSURFACE4 target, LPDIRECTDRAWSURFACE4 source, LPPALETTEENTRY palette) {
	
	DDSURFACEDESC2 tDesc, sDesc;
	ULONG rBits, gBits, bBits;
	UCHAR index, r, g, b;
	ULONG read, write;
	ULONG x, y;
	SLONG loop;

	memset(&tDesc, 0, sizeof(tDesc));
	memset(&sDesc, 0, sizeof(sDesc));
	tDesc.dwSize = sizeof(tDesc);
	sDesc.dwSize = sizeof(sDesc);

	if (DD_OK == source->lpVtbl->Lock(source, NULL, &sDesc, DDLOCK_WAIT, NULL)) {
		if (8 == sDesc.ddpfPixelFormat.dwRGBBitCount) {
			if (DD_OK == target->lpVtbl->Lock(target, NULL, &tDesc, DDLOCK_WAIT, NULL)) {
				if (16 == tDesc.ddpfPixelFormat.dwRGBBitCount && tDesc.dwWidth == sDesc.dwWidth && tDesc.dwHeight == sDesc.dwHeight) {

					for (rBits=loop=0 ; loop<32 ; loop++) if ((tDesc.ddpfPixelFormat.dwRBitMask >> loop) & 1) rBits++;
					for (gBits=loop=0 ; loop<32 ; loop++) if ((tDesc.ddpfPixelFormat.dwGBitMask >> loop) & 1) gBits++;
					for (bBits=loop=0 ; loop<32 ; loop++) if ((tDesc.ddpfPixelFormat.dwBBitMask >> loop) & 1) bBits++;

					for (y=0 ; y<sDesc.dwHeight ; y++) {
						for (x=0 ; x<sDesc.dwWidth ; x+=4) {

							read = ((LPULONG) (&((LPUCHAR) sDesc.lpSurface)[(y * sDesc.lPitch) + x]))[0];
							for (loop=3 ; loop>=0 ; loop--) {
								
								index = (UCHAR) (read >> (8 * loop));
								r = palette[index].peRed >> (8 - rBits);
								g = palette[index].peGreen >> (8 - gBits);
								b = palette[index].peBlue >> (8 - bBits);

								if (loop & 1) write = ((r << (gBits + bBits)) | (g << bBits) | b) << 16;
								else {
									ULONG offset = (loop & 2)?1:0;

									write |= ((r << (gBits + bBits)) | (g << bBits) | b);
									((LPULONG) (&((LPUCHAR) tDesc.lpSurface)[(y * tDesc.lPitch) + (x * 2)]))[offset] = write;
								}
							}
						}
					}

				}
				target->lpVtbl->Unlock(target, NULL);
			}
		}
		source->lpVtbl->Unlock(source, NULL);

		Error_Fatal(8 != sDesc.ddpfPixelFormat.dwRGBBitCount, "Source surface is not 8bits deep");
		Error_Fatal(16 != tDesc.ddpfPixelFormat.dwRGBBitCount, "Target surface is not 16bits deep");
		Error_Fatal(tDesc.dwWidth != sDesc.dwWidth || tDesc.dwHeight != sDesc.dwHeight, "Source and destination surfaces differ in dimension");
	}
}

ULONG DirectDraw_GetColour(LPDIRECTDRAWSURFACE4 surf, ULONG colour) {

	DDPIXELFORMAT pf;
	ULONG rbc, gbc, bbc, r, g, b;

	r = (colour & 0x00ff0000) >> 16; 
	g = (colour & 0x0000ff00) >> 8;
	b = (colour & 0x000000ff);

	memset(&pf, 0, sizeof(pf));
	pf.dwSize = sizeof(pf);
	surf->lpVtbl->GetPixelFormat(surf, &pf);
	if (pf.dwFlags & DDPF_RGB) {
		rbc = DirectDraw_GetNumberOfBits(pf.dwRBitMask);
		gbc = DirectDraw_GetNumberOfBits(pf.dwGBitMask);
		bbc = DirectDraw_GetNumberOfBits(pf.dwBBitMask);

		r = r >> (8 - rbc);
		g = g >> (8 - gbc);
		b = b >> (8 - bbc);

		r = r << (gbc + bbc);
		g = g << (bbc);

		return (r|g|b);
	} else {
		LPDIRECTDRAWPALETTE pal;
		PALETTEENTRY entries[256];
		ULONG loop;
		surf->lpVtbl->GetPalette(surf, &pal);
		pal->lpVtbl->GetEntries(pal, 0, 0, 256, entries);
		for (loop=0 ; loop<256 ; loop++) {
			if (entries[loop].peRed == r &&
				entries[loop].peGreen == g &&
				entries[loop].peBlue == b) {

				return loop;
			}
		}
	}
	return 0;
}

static ULONG DirectDraw_GetNumberOfBits(ULONG mask) {

	ULONG bc = 0;
	while(mask) {
		mask = mask & (mask - 1);
		bc++;
	}
	return bc;
}
