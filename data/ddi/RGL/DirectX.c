
#include <windows.h>
#include <ddraw.h>
#include <d3d.h>

#include "Standard.h"
#include "Quantizer.h"
#include "DirectX.h"
#include "Render.h"
#include "Errors.h"
#include "Main.h"
#include "Mem.h"
#include "Viewports.h"
#include "Files.h"

#pragma comment ( lib,"d3dim" )
#pragma comment ( lib,"ddraw" )
#pragma comment ( lib,"dxguid" )

struct DirectXGlobs {

	LPDIRECTDRAW7 directDraw;
	LPDIRECTDRAWSURFACE7 fSurf, bSurf, zSurf;
	LPDIRECT3D7 direct3D;
	LPDIRECT3DDEVICE7 device;

	RECT fRect;

	struct DirectXDriverEnum *driverList;
	struct DirectXModeEnum *currMode;
	struct DirectXDeviceEnum *currDevice;
	struct DirectXModeEnum windowedMode;

	ULONG driverCount;

	UCHAR alphaBits, redBits, greenBits, blueBits;
	UCHAR alphaSkip, redSkip, greenSkip, blueSkip;

	UWORD flags;

} directXGlobs = { NULL };

__inline LPDIRECTDRAW7			DirectX_DirectDraw(VOID)	{ return directXGlobs.directDraw; }
__inline LPDIRECTDRAWSURFACE7	DirectX_FrontSurf(VOID)		{ return directXGlobs.fSurf; }
__inline LPDIRECTDRAWSURFACE7	DirectX_BackSurf(VOID)		{ return directXGlobs.bSurf; }
__inline LPDIRECTDRAWSURFACE7	DirectX_ZSurf(VOID)			{ return directXGlobs.zSurf; }
__inline LPDIRECT3D7			DirectX_Direct3D(VOID)		{ return directXGlobs.direct3D; }
__inline LPDIRECT3DDEVICE7		DirectX_Device(VOID)		{ return directXGlobs.device; }
__inline BOOL					DirectX_FullScreen(VOID)	{ return DIRECTX_FLAG_FULLSCREEN == (directXGlobs.flags & DIRECTX_FLAG_FULLSCREEN); }
__inline BOOL					DirectX_Hardware(VOID)		{ return DIRECTX_FLAG_HARDWARE == (directXGlobs.flags & DIRECTX_FLAG_HARDWARE); }
__inline BOOL					DirectX_HardwareTnL(VOID)	{ return DIRECTX_FLAG_HARDWARETnL == (directXGlobs.flags & DIRECTX_FLAG_HARDWARETnL); }

VOID DirectX_Initialise(VOID) {

	DirectDrawEnumerateEx(DirectX_EnumerateDriverCallback, NULL, DDENUM_ATTACHEDSECONDARYDEVICES|DDENUM_DETACHEDSECONDARYDEVICES|DDENUM_NONDISPLAYDEVICES);
}

static BOOL WINAPI DirectX_EnumerateDriverCallback(GUID FAR *lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID lpContext, HMONITOR hm) {

	lpDirectXDriverEnum driver;
	HRESULT r;
	ULONG releaseCount;
	LPDIRECTDRAW7 ddraw7;

	directXGlobs.driverList = Mem_ReAllocClear(directXGlobs.driverList, sizeof(directXGlobs.driverList[0]) * (directXGlobs.driverCount + 1));
	driver = &directXGlobs.driverList[directXGlobs.driverCount++];

	sprintf(driver->name, "%s (%s)", lpDriverName, lpDriverDescription);

	if (lpGUID) driver->guid = *lpGUID;
	else driver->flags |= DIRECTXENUM_FLAG_NOGUID;

	r = DirectDrawCreateEx(lpGUID, &ddraw7, &IID_IDirectDraw7, NULL);
	Error_DirectX(r, "DirectDrawCreateEx");

	r = ddraw7->lpVtbl->EnumDisplayModes(ddraw7, 0, NULL, driver, DirectX_EnumerateModesCallback);
	Error_DirectX(r, "EnumDisplayModes");

	r = ddraw7->lpVtbl->QueryInterface(ddraw7, &IID_IDirect3D7, &driver->lpD3D7);
	Error_DirectX(r, "QueryInterface");

	r = driver->lpD3D7->lpVtbl->EnumDevices(driver->lpD3D7, DirectX_EnumerateDeviceCallback, driver);
	Error_DirectX(r, "EnumDevices");

	releaseCount = driver->lpD3D7->lpVtbl->Release(driver->lpD3D7);
	driver->lpD3D7 = NULL;
	releaseCount = ddraw7->lpVtbl->Release(ddraw7);

	return TRUE;
}

HRESULT CALLBACK DirectX_EnumerateZBufferFormatsCallback(LPDDPIXELFORMAT lpDDPixFmt, LPVOID lpContext) {
	
	lpDirectXDeviceEnum device = (lpDirectXDeviceEnum) lpContext;

	device->zBufferFormatList = Mem_ReAllocClear(device->zBufferFormatList, sizeof(device->zBufferFormatList[0]) * (device->zBufferFormatCount + 1));

	if (lpDDPixFmt->dwFlags & DDPF_ZBUFFER) Mem_Copy(&device->zBufferFormatList[device->zBufferFormatCount++], lpDDPixFmt, sizeof(*lpDDPixFmt));

	return D3DENUMRET_OK;
}

static HRESULT CALLBACK DirectX_EnumerateDeviceCallback(LPSTR lpDeviceDescription, LPSTR lpDeviceName, LPD3DDEVICEDESC7 lpD3DDeviceDesc, LPVOID lpContext) {

	lpDirectXDriverEnum driver = (lpDirectXDriverEnum) lpContext;
	lpDirectXDeviceEnum device;
	HRESULT r;

	driver->deviceList = Mem_ReAllocClear(driver->deviceList, sizeof(driver->deviceList[0]) * (driver->deviceCount + 1));
	device = &driver->deviceList[driver->deviceCount++];

	device->guid = lpD3DDeviceDesc->deviceGUID;
	sprintf(device->name, "%s (%s)", lpDeviceName, lpDeviceDescription);

	r = driver->lpD3D7->lpVtbl->EnumZBufferFormats(driver->lpD3D7, &device->guid, DirectX_EnumerateZBufferFormatsCallback, device);
	Error_DirectX(r, "EnumZBufferFormats");

	return TRUE;
}

static BOOL WINAPI DirectX_EnumerateModesCallback(LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext) {

	lpDirectXDriverEnum driver = (lpDirectXDriverEnum) lpContext;
	lpDirectXModeEnum mode;

	driver->modeList = Mem_ReAllocClear(driver->modeList, sizeof(driver->modeList[0]) * (driver->modeCount + 1));
	mode = &driver->modeList[driver->modeCount++];

	mode->width = (UWORD) lpDDSurfaceDesc->dwWidth;
	mode->height = (UWORD) lpDDSurfaceDesc->dwHeight;
	mode->depth = (UWORD) lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount;

	sprintf(mode->name, "%ix%ix%i", mode->width, mode->height, mode->depth);

	return TRUE;
}

BOOL DirectX_FindHardwareMode(LPULONG driver, LPULONG device) {

	SLONG driverIndex, deviceIndex;
	lpDirectXDriverEnum driverEnum;
	lpDirectXDeviceEnum deviceEnum;

	for (driverIndex=directXGlobs.driverCount-1 ; driverIndex>=0 ; driverIndex--) {
		driverEnum = &directXGlobs.driverList[driverIndex];
		for (deviceIndex=driverEnum->deviceCount-1 ; deviceIndex>=0 ; deviceIndex--) {
			deviceEnum = &driverEnum->deviceList[deviceIndex];

			if (IsEqualIID(&deviceEnum->guid, &IID_IDirect3DHALDevice) ||
				IsEqualIID(&deviceEnum->guid, &IID_IDirect3DTnLHalDevice)) {

				*driver = driverIndex;
				*device = deviceIndex;

				return TRUE;
			}
		}
	}

	return FALSE;
}

HRESULT CALLBACK DirectX_EnumerateTextureFormatsCallback(LPDDPIXELFORMAT lpDDPixFmt, LPVOID lpContext) {

	lpDirectXDeviceEnum device = (lpDirectXDeviceEnum) lpContext;

	device->textureFormatList = Mem_ReAllocClear(device->textureFormatList, sizeof(device->textureFormatList[0]) * (device->textureFormatCount + 1));

	Mem_Copy(&device->textureFormatList[device->textureFormatCount], lpDDPixFmt, sizeof(*lpDDPixFmt));

	device->textureFormatCount++;

	return D3DENUMRET_OK;
}

int DirectX_SortTextureListCallback(const void *a, const void *b) {
	
	LPDDPIXELFORMAT pfa = (LPDDPIXELFORMAT) a;
	LPDDPIXELFORMAT pfb = (LPDDPIXELFORMAT) b;
	DDPIXELFORMAT ddpf;
	HRESULT r;

	if (pfa->dwRGBBitCount == DirectX_GetDepth() && pfb->dwRGBBitCount != DirectX_GetDepth()) return -1;
	if (pfa->dwRGBBitCount != DirectX_GetDepth() && pfb->dwRGBBitCount == DirectX_GetDepth()) return 1;

	if (pfa->dwRGBBitCount == DirectX_GetDepth()) {		// Both or neither must be equal to the back buffer depth

		DirectX_InitStruct(&ddpf);
		r = directXGlobs.bSurf->lpVtbl->GetPixelFormat(directXGlobs.bSurf, &ddpf);
		Error_DirectX(r, "GetSurfaceDesc");

		if ((pfa->dwRBitMask == ddpf.dwRBitMask && pfa->dwGBitMask == ddpf.dwGBitMask && pfa->dwBBitMask == ddpf.dwBBitMask) &&
			!(pfb->dwRBitMask == ddpf.dwRBitMask && pfb->dwGBitMask == ddpf.dwGBitMask && pfb->dwBBitMask == ddpf.dwBBitMask)) return -1;

		if (!(pfa->dwRBitMask == ddpf.dwRBitMask && pfa->dwGBitMask == ddpf.dwGBitMask && pfa->dwBBitMask == ddpf.dwBBitMask) &&
			(pfb->dwRBitMask == ddpf.dwRBitMask && pfb->dwGBitMask == ddpf.dwGBitMask && pfb->dwBBitMask == ddpf.dwBBitMask)) return 1;

	}

	return 0;
}

static VOID DirectX_EnumerateTextureFormats(lpDirectXDeviceEnum deviceEnum, LPDIRECT3DDEVICE7 device) {

	HRESULT r;

	if (0 == deviceEnum->textureFormatCount) {
		r = device->lpVtbl->EnumTextureFormats(device, DirectX_EnumerateTextureFormatsCallback, deviceEnum);
		Error_DirectX(r, "EnumTextureFormats");
		qsort(deviceEnum->textureFormatList, deviceEnum->textureFormatCount, sizeof(deviceEnum->textureFormatList[0]), DirectX_SortTextureListCallback);
	}
}

BOOL DirectX_FindTextureFormat(ULONG depth, LPDDPIXELFORMAT texturePixelFormat) {

	ULONG loop;
	lpDirectXDeviceEnum device = directXGlobs.currDevice;
	LPDDPIXELFORMAT format;

	Error_Fatal(NULL == device, "No device created");
	Error_Fatal(0 == device->textureFormatCount, "No texture formats found/enumerated");

	if (0 == depth) {
		*texturePixelFormat = device->textureFormatList[0];
		return TRUE;
	}

	for (loop=0 ; loop<device->textureFormatCount ; loop++) {

		format = &device->textureFormatList[loop];
		
		if (format->dwRGBBitCount == depth) {
			*texturePixelFormat = *format;
			return TRUE;
		}
	}

	return FALSE;
}

VOID DirectX_CloseDown(BOOL exit) {

	ULONG r, loop, sub;

	if (directXGlobs.directDraw) {

		Render_ResetTextures();

		if (exit) directXGlobs.directDraw->lpVtbl->RestoreDisplayMode(directXGlobs.directDraw);

		r = directXGlobs.device->lpVtbl->Release(directXGlobs.device);
		directXGlobs.device = NULL;
		DirectX_RemoveZBuffer();
		r = directXGlobs.direct3D->lpVtbl->Release(directXGlobs.direct3D);
		directXGlobs.direct3D = NULL;
		r = directXGlobs.bSurf->lpVtbl->Release(directXGlobs.bSurf);
		directXGlobs.bSurf = NULL;
		r = directXGlobs.fSurf->lpVtbl->Release(directXGlobs.fSurf);
		directXGlobs.fSurf = NULL;
		if (exit) {

			r = directXGlobs.directDraw->lpVtbl->Release(directXGlobs.directDraw);
			directXGlobs.directDraw = NULL;

			for (loop=0 ; loop<directXGlobs.driverCount ; loop++) {
				for (sub=0 ; sub<directXGlobs.driverList[loop].deviceCount ; sub++) {
					Mem_Free(directXGlobs.driverList[loop].deviceList[sub].zBufferFormatList);
					if (directXGlobs.driverList[loop].deviceList[sub].textureFormatList) Mem_Free(directXGlobs.driverList[loop].deviceList[sub].textureFormatList);
				}
				Mem_Free(directXGlobs.driverList[loop].deviceList);
				Mem_Free(directXGlobs.driverList[loop].modeList);
			}

			Mem_Free(directXGlobs.driverList);
		}
	}
}

ULONG DirectX_GetDriverCount(VOID) {

	return directXGlobs.driverCount;
}

LPUCHAR DirectX_GetDriverName(ULONG driverIndex) {

	lpDirectXDriverEnum driver;

	Error_Fatal(driverIndex >= directXGlobs.driverCount, "Driver index is out of range");

	driver = &directXGlobs.driverList[driverIndex];

	return driver->name;
}

ULONG DirectX_GetDeviceCount(ULONG driverIndex) {

	lpDirectXDriverEnum driver;

	Error_Fatal(driverIndex >= directXGlobs.driverCount, "Driver index is out of range");

	driver = &directXGlobs.driverList[driverIndex];

	return driver->deviceCount;
}

LPUCHAR DirectX_GetDeviceName(ULONG driverIndex, ULONG deviceIndex) {

	lpDirectXDriverEnum driver;
	lpDirectXDeviceEnum device;

	Error_Fatal(driverIndex >= directXGlobs.driverCount, "Driver index is out of range");

	driver = &directXGlobs.driverList[driverIndex];
	
	Error_Fatal(deviceIndex >= driver->deviceCount, "Device index is out of range");

	device = &driver->deviceList[deviceIndex];

	return device->name;
}

ULONG DirectX_GetWidth(VOID) {

	return directXGlobs.currMode->width;
}

ULONG DirectX_GetHeight(VOID) {

	return directXGlobs.currMode->height;
}

ULONG DirectX_GetDepth(VOID) {

	return directXGlobs.currMode->depth;
}

static HRESULT DirectX_SetupDisplay(LPDIRECTDRAW7 directDraw, BOOL fullScreen, ULONG width, ULONG height, ULONG depth) {

	DWORD flags;
	HRESULT r;

	if (fullScreen) flags = DDSCL_FULLSCREEN|DDSCL_EXCLUSIVE;
	else flags = DDSCL_NORMAL;

	if (DD_OK == (r = directDraw->lpVtbl->SetCooperativeLevel(directDraw, Main_hWnd(), flags))) {
		if (fullScreen) {
			r = directDraw->lpVtbl->SetDisplayMode(directDraw, width, height, depth, 0, 0);
			Error_DirectX(r, "SetDisplayMode");
		}
	}

	return r;
}

VOID DirectX_RestoreDisplayMode(VOID) {

	directXGlobs.directDraw->lpVtbl->SetCooperativeLevel(directXGlobs.directDraw, Main_hWnd(), DDSCL_NORMAL);
	directXGlobs.directDraw->lpVtbl->RestoreDisplayMode(directXGlobs.directDraw);
}

BOOL DirectX_Setup(BOOL fullScreen, ULONG driverIndex, ULONG deviceIndex, ULONG modeIndex, BOOL emulationMode) {

	if (!(directXGlobs.flags & DIRECTX_FLAG_INSETUP)) {		// Ensure no windows messages during setup call itself...

		HRESULT r;
		LPGUID lpGUID;
		lpDirectXDriverEnum driver;
		lpDirectXDeviceEnum device;
		lpDirectXModeEnum mode;

		DirectX_CloseDown(FALSE);

		directXGlobs.flags |= DIRECTX_FLAG_INSETUP;

		Error_FullScreenMode(fullScreen);

		driver = &directXGlobs.driverList[driverIndex];
		device = &driver->deviceList[deviceIndex];
		if (-1 == modeIndex) mode = &directXGlobs.windowedMode;
		else mode = &driver->modeList[modeIndex];

		if (driver->flags & DIRECTXENUM_FLAG_NOGUID) lpGUID = NULL;
		else lpGUID = &driver->guid;

		if (fullScreen) directXGlobs.flags |= DIRECTX_FLAG_FULLSCREEN;
		else directXGlobs.flags &= ~DIRECTX_FLAG_FULLSCREEN;
		
		if (IsEqualIID(&device->guid, &IID_IDirect3DHALDevice)) directXGlobs.flags |= DIRECTX_FLAG_HARDWARE;
		else if (IsEqualIID(&device->guid, &IID_IDirect3DTnLHalDevice)) directXGlobs.flags |= DIRECTX_FLAG_HARDWARETnL;

		if (DD_OK == (r = DirectX_CreateDirectDraw(lpGUID, emulationMode))) {
			if (DD_OK == (r = DirectX_SetupDisplay(directXGlobs.directDraw, fullScreen, mode->width, mode->height, mode->depth))) {
				if (DD_OK == (r = directXGlobs.directDraw->lpVtbl->QueryInterface(directXGlobs.directDraw, &IID_IDirect3D7, &directXGlobs.direct3D))) {
					Main_SetWindowSize(mode->width, mode->height, fullScreen);
					if (DD_OK == (r = DirectX_CreateFrontSurface(&directXGlobs.fSurf, directXGlobs.directDraw, fullScreen))) {
						if (DD_OK == (r = DirectX_CreateBackSurface(&directXGlobs.bSurf, directXGlobs.fSurf, directXGlobs.directDraw, fullScreen, mode->width, mode->height))) {
							if (DD_OK == (r = DirectX_CreateClippers(fullScreen, mode->width, mode->height))) {
								if (DD_OK == (r = DirectX_CreateZBuffer(&directXGlobs.zSurf, directXGlobs.directDraw, DirectX_FindZBufferFormat(device, mode->depth), mode->width, mode->height))) {
									if (DD_OK == (r = directXGlobs.direct3D->lpVtbl->CreateDevice(directXGlobs.direct3D, &device->guid, directXGlobs.bSurf, &directXGlobs.device))) {

										directXGlobs.flags &= ~DIRECTX_FLAG_INSETUP;
										directXGlobs.currMode = mode;
										directXGlobs.currDevice = device;
										DirectX_SetupBitCounts();
										Viewport_Reconfigure();
										DirectX_SetFrontRect();
										DirectX_EnumerateTextureFormats(device, directXGlobs.device);
										Render_ResetTextures();

										return TRUE;

									} else {
									
										if (DDERR_INVALIDPIXELFORMAT == r) Main_ReportError(MainErrorType_InvalidPixelFormat);
										Error_DirectX(r, "CreateDevice");
									}

									DirectX_RemoveZBuffer();

								} else Error_DirectX(r, "DirectX_CreateZBuffer");

								directXGlobs.bSurf->lpVtbl->Release(directXGlobs.bSurf);
								directXGlobs.bSurf = NULL;

							} else Error_DirectX(r, "DirectX_CreateClippers");

						} else Error_DirectX(r, "DirectX_CreateBackSurface");

						directXGlobs.fSurf->lpVtbl->Release(directXGlobs.fSurf);
						directXGlobs.fSurf = NULL;

					} else Error_DirectX(r, "DirectX_CreateFrontSurface");

					directXGlobs.direct3D->lpVtbl->Release(directXGlobs.direct3D);
					directXGlobs.direct3D = NULL;

				} else Error_DirectX(r, "QueryInterface");

			} else Error_DirectX(r, "DirectX_SetupDisplay");
		} else Error_DirectX(r, "DirectX_CreateDirectDraw");

		directXGlobs.flags &= ~DIRECTX_FLAG_INSETUP;
		return FALSE;

	}
	
	return TRUE;
}

static HRESULT DirectX_CreateDirectDraw(LPGUID lpGUID, BOOL emulationMode) {

	HRESULT r;

	if (emulationMode) lpGUID = (LPGUID) DDCREATE_EMULATIONONLY;
	
	if (directXGlobs.directDraw) r = DD_OK;
	else {
		if (DD_OK != (r = DirectDrawCreateEx(lpGUID, &directXGlobs.directDraw, &IID_IDirectDraw7, NULL))) {
			directXGlobs.directDraw = NULL;
		}
	}

	return r;
}

static HRESULT DirectX_CreateFrontSurface(LPDIRECTDRAWSURFACE7 *surface, LPDIRECTDRAW7 ddraw, BOOL fullScreen) {

	DDSURFACEDESC2 desc;

	memset(&desc, 0, sizeof(desc));
	desc.dwSize = sizeof(desc);

	desc.dwFlags = DDSD_CAPS;
	desc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	if (fullScreen) {
		desc.dwFlags |= DDSD_BACKBUFFERCOUNT;
		desc.dwBackBufferCount = 1;
		desc.ddsCaps.dwCaps |= DDSCAPS_3DDEVICE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
	}

	return ddraw->lpVtbl->CreateSurface(ddraw, &desc, &directXGlobs.fSurf, NULL);
}

static HRESULT DirectX_CreateBackSurface(LPDIRECTDRAWSURFACE7 *surface, LPDIRECTDRAWSURFACE7 frontSurface, LPDIRECTDRAW7 ddraw, BOOL fullScreen, ULONG width, ULONG height) {

	HRESULT r;

	if (fullScreen) {

		DDSCAPS2 ddscaps;
		memset(&ddscaps, 0, sizeof(ddscaps));
		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
		r = directXGlobs.fSurf->lpVtbl->GetAttachedSurface(frontSurface, &ddscaps, surface);

	} else {

		DDSURFACEDESC2 desc;

		memset(&desc, 0, sizeof(desc));
		desc.dwSize = sizeof(desc);
		desc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		desc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
		desc.dwWidth = width;
		desc.dwHeight = height;
		r = ddraw->lpVtbl->CreateSurface(ddraw, &desc, surface, NULL);

	}

	return r;
}

static VOID DirectX_SetupBitCounts(VOID) {

	DDSURFACEDESC2 desc;
	memset(&desc, 0, sizeof(desc));
	desc.dwSize = sizeof(desc);

	directXGlobs.bSurf->lpVtbl->GetSurfaceDesc(directXGlobs.bSurf, &desc);

	if (16 == desc.ddpfPixelFormat.dwRGBBitCount) directXGlobs.flags |= DIRECTX_FLAG_16BIT;

	directXGlobs.alphaBits = directXGlobs.redBits = directXGlobs.greenBits = directXGlobs.blueBits = 0;
	DirectX_GetBitCounts(&desc.ddpfPixelFormat, &directXGlobs.alphaBits, &directXGlobs.redBits, &directXGlobs.greenBits, &directXGlobs.blueBits);
	directXGlobs.blueSkip = 0;
	directXGlobs.greenSkip = directXGlobs.blueSkip + directXGlobs.blueBits;
	directXGlobs.redSkip = directXGlobs.greenSkip + directXGlobs.greenBits;
	directXGlobs.alphaSkip = directXGlobs.redSkip + directXGlobs.redBits;

}

VOID DirectX_GetBitCounts(LPDDPIXELFORMAT ddpf, LPUCHAR aBits, LPUCHAR rBits, LPUCHAR gBits, LPUCHAR bBits) {

	ULONG loop;

	Error_Fatal(NULL==rBits||NULL==gBits||NULL==bBits, "Must specify red green and blue");

	if (aBits) *aBits = 0;
	*rBits = *gBits = *bBits = 0;

	for (loop=0 ; loop<32 ; loop++) {
		if (aBits) if ((ddpf->dwRGBAlphaBitMask>>loop)&0x1) (*aBits)++;
		if ((ddpf->dwRBitMask>>loop)&0x1) (*rBits)++;
		if ((ddpf->dwGBitMask>>loop)&0x1) (*gBits)++;
		if ((ddpf->dwBBitMask>>loop)&0x1) (*bBits)++;
	}
}

LPDDPIXELFORMAT DirectX_FindZBufferFormat(lpDirectXDeviceEnum device, ULONG preferedDepth) {

	ULONG loop;
	LPDDPIXELFORMAT zBufferPF = NULL;

	for (loop=0 ; loop<device->zBufferFormatCount ; loop++) {
		zBufferPF = &device->zBufferFormatList[loop];
		if (zBufferPF->dwZBufferBitDepth == preferedDepth) break;
	}

	return zBufferPF;
}

HRESULT DirectX_CreateZBuffer(LPDIRECTDRAWSURFACE7 *surface, LPDIRECTDRAW7 ddraw, LPDDPIXELFORMAT zBufferPF, ULONG width, ULONG height) {

	if (zBufferPF) {

		DDSURFACEDESC2 desc;
		HRESULT r;

		memset(&desc, 0, sizeof(desc));
		desc.dwSize = sizeof(desc);
		desc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
		desc.ddsCaps.dwCaps = DDSCAPS_ZBUFFER;
		desc.dwWidth = width;
		desc.dwHeight = height;

		if (DirectX_Hardware()) desc.ddsCaps.dwCaps |= DDSCAPS_VIDEOMEMORY;
		else desc.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;

		Mem_Copy(&desc.ddpfPixelFormat, zBufferPF, sizeof(*zBufferPF));

		if (DD_OK == (r = directXGlobs.directDraw->lpVtbl->CreateSurface(ddraw, &desc, surface, NULL))) {
			if (DD_OK != (r = directXGlobs.bSurf->lpVtbl->AddAttachedSurface(directXGlobs.bSurf, directXGlobs.zSurf))) {

				directXGlobs.zSurf->lpVtbl->Release(directXGlobs.zSurf);

			}
		}

		return r;

	} else return DD_OK;
}

static HRESULT WINAPI DirectX_EnumZBufferCallback(LPDDPIXELFORMAT lpDDPF, LPVOID data) {

	if (lpDDPF->dwFlags == DDPF_ZBUFFER) {
		Mem_Copy(data, lpDDPF, sizeof(*lpDDPF));
		return D3DENUMRET_CANCEL;
	}

	return D3DENUMRET_OK;
}

static VOID DirectX_RemoveZBuffer(VOID) {

	directXGlobs.bSurf->lpVtbl->DeleteAttachedSurface(directXGlobs.bSurf, 0, directXGlobs.zSurf);
	directXGlobs.zSurf->lpVtbl->Release(directXGlobs.zSurf);
	directXGlobs.zSurf = NULL;
}

static HRESULT DirectX_CreateClippers(BOOL fullScreen, ULONG width, ULONG height) {

	LPDIRECTDRAWCLIPPER clipper;
	HRESULT r;

	if (SUCCEEDED(r = directXGlobs.directDraw->lpVtbl->CreateClipper(directXGlobs.directDraw, 0, &clipper, NULL))) {

		HRGN handle;
		ULONG size;
		RGNDATA *region;

		handle = CreateRectRgn(0, 0, width, height);
		size = GetRegionData(handle, 0, NULL);
		region = Mem_Alloc(size);
		GetRegionData(handle, size, region);

		if (SUCCEEDED(r = clipper->lpVtbl->SetClipList(clipper, region, 0))) {
			if (SUCCEEDED(r = directXGlobs.bSurf->lpVtbl->SetClipper(directXGlobs.bSurf, clipper))) {
			
				clipper->lpVtbl->Release(clipper);
				clipper = NULL;

				if (fullScreen) r = DD_OK;
				else {
					if (DD_OK == (r = directXGlobs.directDraw->lpVtbl->CreateClipper(directXGlobs.directDraw, 0, &clipper, NULL))) {

						clipper->lpVtbl->SetHWnd(clipper, 0, Main_hWnd());
						directXGlobs.fSurf->lpVtbl->SetClipper(directXGlobs.fSurf, clipper);
						clipper->lpVtbl->Release(clipper);
						clipper = NULL;

					}
				}

			} else Error_DirectX(r, "SetClipper");
		} else Error_DirectX(r, "SetClipList");

		Mem_Free(region);
	}

	return r;
}

VOID DirectX_EvictTextures(VOID) {

	DirectX_Direct3D()->lpVtbl->EvictManagedTextures(DirectX_Direct3D());
}

VOID DirectX_GetAvailableTextureMemory(LPULONG total, LPULONG used, LPULONG free) {

	DDSCAPS2 ddsCaps;
	ULONG totalMem, freeMem;

	memset(&ddsCaps, 0, sizeof(ddsCaps));
	ddsCaps.dwCaps |= DDSCAPS_TEXTURE;

	DirectX_DirectDraw()->lpVtbl->GetAvailableVidMem(DirectX_DirectDraw(), &ddsCaps, &totalMem, &freeMem);

	if (total) *total = totalMem;
	if (used) *used = totalMem - freeMem;
	if (free) *free = freeMem;
}

VOID DirectX_SetFrontRect(VOID) {

	GetClientRect(Main_hWnd(), &directXGlobs.fRect);
	ClientToScreen(Main_hWnd(), (POINT*)&directXGlobs.fRect.left);
	ClientToScreen(Main_hWnd(), (POINT*)&directXGlobs.fRect.right);
}

ULONG DirectX_GetRefreshRate(VOID) {

	HRESULT r;
	ULONG rate;

	r = DirectX_DirectDraw()->lpVtbl->GetMonitorFrequency(DirectX_DirectDraw(), &rate);
	Error_DirectX(r, "GetMonitorFrequency");

	return rate;
}

VOID DirectX_WaitForVerticalBlank(ULONG count) {

	ULONG loop;
	HRESULT r;

	for (loop=0 ; loop<count ; loop++) {
		r = DirectX_DirectDraw()->lpVtbl->WaitForVerticalBlank(DirectX_DirectDraw(), DDWAITVB_BLOCKBEGIN, NULL);
		Error_DirectX(r, "WaitForVerticalBlank");
	}
}

VOID DirectX_Flip(VOID) {

	HRESULT r;

	if (directXGlobs.flags & DIRECTX_FLAG_FULLSCREEN) {
		
		r = directXGlobs.fSurf->lpVtbl->Flip(directXGlobs.fSurf, 0, DDFLIP_WAIT);
		Error_DirectX(r, "Flip");

	} else {

		r = DirectX_DirectDraw()->lpVtbl->WaitForVerticalBlank(DirectX_DirectDraw(), DDWAITVB_BLOCKBEGIN, NULL);
		Error_DirectX(r, "WaitForVerticalBlank");
		r = directXGlobs.fSurf->lpVtbl->Blt(directXGlobs.fSurf, &directXGlobs.fRect, directXGlobs.bSurf, NULL, DDBLT_WAIT, NULL);
		Error_DirectX(r, "Blt");
	
	}
}

ULONG DirectX_FindWindowedMode(HWND hWnd) {

	RECT screenRect;
	lpDirectXModeEnum mode = &directXGlobs.windowedMode;

	GetClientRect(hWnd, &screenRect);
	ClientToScreen(hWnd, (POINT*) &screenRect.left);
	ClientToScreen(hWnd, (POINT*) &screenRect.right);
	mode->width = (UWORD) (screenRect.right - screenRect.left);
	mode->height = (UWORD) (screenRect.bottom - screenRect.top);

	mode->depth = 0;		// Not required...

	return -1;
}

BOOL DirectX_FindMode(ULONG driverIndex, ULONG width, ULONG height, ULONG depth, LPULONG mode) {

	ULONG loop;
	lpDirectXDriverEnum driver;

	Error_Fatal(driverIndex>directXGlobs.driverCount, "Invalid driver specified");

	driver = &directXGlobs.driverList[driverIndex];

	for (loop=0 ; loop<driver->modeCount ; loop++) {
		if ((0 == depth || driver->modeList[loop].depth == depth) &&
			(0 == width || driver->modeList[loop].width == width) &&
			(0 == height || driver->modeList[loop].height == height)) {

			if (mode) *mode = loop;
			return TRUE;
		}
	}

	return FALSE;
}

__inline static ULONG DirectX_ColourMatchARGB(UCHAR a, UCHAR r, UCHAR g, UCHAR b) {

	ULONG colour;

	if (directXGlobs.flags & DIRECTX_FLAG_16BIT) {
		a = a >> (8 - directXGlobs.alphaBits);
		r = r >> (8 - directXGlobs.redBits);
		g = g >> (8 - directXGlobs.greenBits);
		b = b >> (8 - directXGlobs.blueBits);
		colour = (a<<directXGlobs.alphaSkip)|(r<<directXGlobs.redSkip)|(g<<directXGlobs.greenSkip)|(b<<directXGlobs.blueSkip);
	} else colour = (a<<24)|(r<<16)|(g<<8)|b;

	return colour;	
}

__inline ULONG DirectX_ColourMatchPacked(ULONG colour) {

	UCHAR a, r, g, b;

	a = (UCHAR) ((colour >> 24) & 0xff);
	r = (UCHAR) ((colour >> 16) & 0xff);
	g = (UCHAR) ((colour >> 8) & 0xff);
	b = (UCHAR) (colour & 0xff);

	return DirectX_ColourMatchARGB(a, r, g, b);
}

__inline ULONG DirectX_ColourMatch(REAL r, REAL g, REAL b, REAL a) {

	UCHAR alpha, red, green, blue;
	Error_Fatal(a>1.0f||r>1.0f||g>1.0f||b>1.0f, "Invalid rgb values");

	alpha = (UCHAR)(a*255.0f);
	red = (UCHAR)(r*255.0f);
	green = (UCHAR)(g*255.0f);
	blue = (UCHAR)(b*255.0f);

	return DirectX_ColourMatchARGB(alpha, red, green, blue);
}

__inline DirectX_GetRenderSurfaceBitDepth(VOID) {

	DDPIXELFORMAT ddpf;
//	memset(&ddpf, 0, sizeof(ddpf));
//	ddpf.dwSize = sizeof(ddpf);
	DirectX_InitStruct(&ddpf);

	DirectX_BackSurf()->lpVtbl->GetPixelFormat(DirectX_BackSurf(), &ddpf);
	return ddpf.dwRGBBitCount;
}

VOID DirectX_ClearBackBuffer(COLOUR colour) {

	DDBLTFX bltFX;

	DirectX_InitStruct(&bltFX);

	bltFX.dwFillColor = DirectX_ColourMatchPacked(colour);

	DirectX_BackSurf()->lpVtbl->Blt(DirectX_BackSurf(), NULL, NULL, NULL, DDBLT_COLORFILL, &bltFX);
}

lpDirectXBufferDump DirectX_DumpBuffer(enum DirectXSurfaceType type, LPAREA2Di shape) {

	lpDirectXBufferDump dump, result = NULL;
	LPDIRECTDRAWSURFACE7 surface;
	DDSURFACEDESC2 desc;
	ULONG y, bytesPerPixel, loop;
	LPULONG srcLine, destLine;

//	memset(&desc, 0, sizeof(desc));
//	desc.dwSize = sizeof(desc);
	DirectX_InitStruct(&desc);

	switch (type) {
	case DirectXSurfaceType_Z:			surface = DirectX_ZSurf();			break;
	case DirectXSurfaceType_Back:		surface = DirectX_BackSurf();		break;
	default: Error_Fatal(TRUE, "Unknown surface type");
	}

	if (DD_OK == surface->lpVtbl->Lock(surface, NULL, &desc, DDLOCK_WAIT, NULL)) {
		if (dump = Mem_AllocClear(sizeof(*dump))) {

			bytesPerPixel = (desc.ddpfPixelFormat.dwRGBBitCount / 8);
			if (shape) dump->shape = *shape;
			else {
				dump->shape.x = dump->shape.y = 0;
				dump->shape.width = desc.dwWidth;
				dump->shape.height = desc.dwHeight;
			}
			dump->pitch = (dump->shape.width * bytesPerPixel);
			dump->pitch = ((dump->pitch / 4) * 4) + ((dump->pitch % 4)?4:0);

			if (dump->buffer = Mem_Alloc(dump->shape.height * dump->pitch)) {
				for (y=0 ; y<dump->shape.height ; y++) {

					srcLine = &((LPULONG)desc.lpSurface)[((desc.lPitch * (y + dump->shape.y)) + (dump->shape.x * bytesPerPixel)) / 4];
					destLine = &((LPULONG)dump->buffer)[(y * dump->pitch) / 4];

					for (loop=0 ; loop<(dump->pitch/4) ; loop++) destLine[loop] = srcLine[loop];
				}
				result = dump;
			}
			if (NULL == result) Mem_Free(dump);
		}
		surface->lpVtbl->Unlock(surface, NULL);
	}

	return result;
}

BOOL DirectX_WriteBufferDump(lpDirectXBufferDump dump, LPUCHAR fname) {
	
	lpFile dfp;
	struct DirectXBufferDump write = *dump;
	ULONG magic = DIRECTX_DUMPFILEMAGIC;

	if (dfp = File_Open(fname, "w")) {
		write.buffer = NULL;
		File_Write(&magic, sizeof(ULONG), 1, dfp);
		File_Write(&write, sizeof(struct DirectXBufferDump), 1, dfp);
		File_Write(dump->buffer, dump->pitch, dump->shape.height, dfp);
		File_Close(dfp);

		return TRUE;
	}
	return FALSE;
}

VOID DirectX_FreeBufferDump(lpDirectXBufferDump dump) {

	if (dump) {
		Mem_Free(dump->buffer);
		Mem_Free(dump);
	}
}