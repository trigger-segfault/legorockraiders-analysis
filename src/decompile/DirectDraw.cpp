#include "DirectDraw.h"
#include "Main.h"

using namespace lego;
using namespace lego::ddraw;


#pragma region Globals

/// INTERNAL:
// <LegoRR.exe @0076bc80>
HWND lego::globals::g_DirectDraw_hWnd;

/// PUBLIC:
// <LegoRR.exe @0076bc84>
IDirectDraw4* lego::globals::g_IDirectDraw4;

/// INTERNAL:
// <LegoRR.exe @0076bc88>
IDirectDrawSurface4* lego::globals::g_IDirectDrawSurface4_RenderTarget;

/// PUBLIC:
// <LegoRR.exe @0076bc8c>
IDirectDrawSurface4* lego::globals::g_IDirectDrawSurface4_DrawTarget;

/// INTERNAL:
// <LegoRR.exe @0076bc90>
unsigned int lego::globals::g_DirectDraw_UNUSED_0076bc90;
// <LegoRR.exe @0076bc94>
IDirectDrawClipper* lego::globals::g_IDirectDrawClipper_RenderTarget;
// <LegoRR.exe @0076bc98>
IDirectDrawClipper* lego::globals::g_IDirectDrawClipper_DrawTarget;
// <LegoRR.exe @0076bc9c>
DriverMode* lego::globals::g_DirectDrawDriverEnumerate_TABLE;

// unused 4-byte gap

// <LegoRR.exe @0076bca4>
DeviceMode* lego::globals::g_DirectDrawDeviceEnumerate_TABLE;

// unused 4-byte gap

// <LegoRR.exe @0076bcac>
ScreenMode* lego::globals::g_DirectDrawScreenEnumerate_TABLE;
// <LegoRR.exe @0076bcb0>
int lego::globals::g_DirectDrawDriverEnumerate_COUNT;
// <LegoRR.exe @0076bcb4>
int lego::globals::g_DirectDrawDeviceEnumerate_COUNT;
// <LegoRR.exe @0076bcb8>
int lego::globals::g_DirectDrawScreenEnumerate_COUNT;
// <LegoRR.exe @0076bcbc>
BOOL lego::globals::g_ScreenIsFullScreen;
// <LegoRR.exe @0076bcc0>
Size2I lego::globals::g_ScreenSize;

#pragma endregion


#pragma region Functions

// <LegoRR.exe @0047c430>
void __cdecl lego::ddraw::InitDirectDraw(HWND hWnd)
{
	globals::g_DirectDraw_hWnd = hWnd;
	globals::g_IDirectDraw4 = nullptr;
	globals::g_IDirectDrawSurface4_RenderTarget = nullptr;
	globals::g_IDirectDrawSurface4_DrawTarget = nullptr;
	globals::g_DirectDraw_UNUSED_0076bc90 = 0;
	globals::g_IDirectDrawClipper_RenderTarget = nullptr;
	globals::g_IDirectDrawClipper_DrawTarget = nullptr;
	globals::g_DirectDrawDriverEnumerate_TABLE = nullptr;
	globals::g_DirectDrawDeviceEnumerate_TABLE = nullptr;
	globals::g_DirectDrawScreenEnumerate_TABLE = nullptr;
	globals::g_DirectDrawDriverEnumerate_COUNT = 0;
	globals::g_DirectDrawDeviceEnumerate_COUNT = 0;
	globals::g_DirectDrawScreenEnumerate_COUNT = 0;
}

// <LegoRR.exe @0047c480>
BOOL __cdecl lego::ddraw::DDraw_PopulateDriverModes(DriverMode * ref_driverModes, int * out_count)
{
	globals::g_DirectDrawDriverEnumerate_TABLE = ref_driverModes;
	::DirectDrawEnumerateA(DDraw_EnumerateDriverCallback, nullptr);
	*out_count = globals::g_DirectDrawDriverEnumerate_COUNT;
	return true;
}

// <LegoRR.exe @0047c4b0>
BOOL CALLBACK lego::ddraw::DDraw_EnumerateDriverCallback(LPGUID lpGuid, LPSTR lpDriverName, LPSTR lpDriverDescription, LPVOID lpContext)
{
	DriverMode* driver = &globals::g_DirectDrawDriverEnumerate_TABLE[globals::g_DirectDrawDriverEnumerate_COUNT];
	driver->flags = DRIVERMODE_ISUSED /*0x1*/;

	if (lpGuid == nullptr) {
		driver->flags |= DRIVERMODE_NOGUID_10 /*0x10*/;
		driver->flags |= DRIVERMODE_NOGUID_20 /*0x20*/;
	}
	else {
		driver->guid = *lpGuid; // can I just do this?
		// std::memcpy(&driver->guid, lpGuid, sizeof(GUID) /*0x10*/);
	}
	std::sprintf(driver->displayName, "%s (%s)", lpDriverName, lpDriverDescription);

	globals::g_DirectDrawDriverEnumerate_COUNT++;
	return true; // continue enumeration
}

// <LegoRR.exe @0047c5a0>
BOOL __cdecl lego::ddraw::DDraw_PopulateDeviceModes(const DriverMode * driver, DeviceMode * ref_deviceModes, int * out_count)
{
	BOOL success = false;
	globals::g_DirectDrawDeviceEnumerate_COUNT = 0;

	IDirectDraw* ddraw1;
	if (::DirectDrawCreate(const_cast<LPGUID>(&driver->guid), &ddraw1, nullptr) == 0) {

		IDirectDraw4* ddraw4; // uuid("9c59509a-39bd-11d1-8c4a-00c04fd930c5")
		if (ddraw1->QueryInterface(idl::IID_IDirectDraw4, (LPVOID*)&ddraw4) == 0) {

			IDirect3D3* d3d3; // uuid("bb223240-e72b-11d0-a9b4-00aa00c0993e")
			if (ddraw4->QueryInterface(idl::IID_IDirect3D3, (LPVOID*)&d3d3) == 0) {
				globals::g_DirectDrawDeviceEnumerate_TABLE = ref_deviceModes;
				d3d3->EnumDevices(DDraw_EnumerateDeviceCallback, nullptr);

				d3d3->Release();

				success = true;
			}
			/// FAILED: IDirectDraw4->QueryInterface => IDirect3D3
			ddraw4->Release();
		}
		/// FAILED: IDirectDraw->QueryInterface => IDirectDraw4
		ddraw1->Release();
	}
	/// FAILED: DirectDrawCreate

	*out_count = globals::g_DirectDrawDeviceEnumerate_COUNT;
	return success;
}

// <LegoRR.exe @0047c640>
HRESULT CALLBACK lego::ddraw::DDraw_EnumerateDeviceCallback(LPGUID lpGuid, LPSTR lpDeviceDescription, LPSTR lpDeviceName, D3DDEVICEDESC_V1 * lpD3DHWDeviceDesc, D3DDEVICEDESC_V1 * lpD3DHELDeviceDesc, LPVOID lpContext)
{
	DeviceMode* device = &globals::g_DirectDrawDeviceEnumerate_TABLE[globals::g_DirectDrawDeviceEnumerate_COUNT];
	device->flags = DEVICEMODE_ISUSED /*0x1*/;

	if (lpD3DHWDeviceDesc->dcmColorModel != 0) {
		device->flags |= DEVICEMODE_HARDWARE /*0x2000*/;
		lpD3DHELDeviceDesc = lpD3DHWDeviceDesc;
	}
	if ((lpD3DHELDeviceDesc->dwFlags & D3DDD_COLORMODEL /*0x1*/) && lpD3DHELDeviceDesc->dcmColorModel == D3DCOLOR_RGB /*0x2*/) {
		device->flags |= DEVICEMODE_COLORMODEL_RGB /*0x1000*/;
	}

	if (lpD3DHELDeviceDesc->dwFlags & D3DDD_DEVICERENDERBITDEPTH /*0x80*/) {
		// <https://github.com/github/VisualStudio/blob/263aac11f57d53c5f9fe64ba9916f77c058974d7/tools/Debugging%20Tools%20for%20Windows/winext/manifest/ddraw.h#L1421>

		if (lpD3DHELDeviceDesc->dwDeviceRenderBitDepth & DDBD_8 /*0x800*/) // 8 bpp (indexed)
			device->flags |= DEVICEMODE_BPP_8 /*0x10*/;

		if (lpD3DHELDeviceDesc->dwDeviceRenderBitDepth & DDBD_16 /*0x400*/) // 16 bpp
			device->flags |= DEVICEMODE_BPP_16 /*0x20*/;

		if (lpD3DHELDeviceDesc->dwDeviceRenderBitDepth & DDBD_24 /*0x200*/) // 24 bpp
			device->flags |= DEVICEMODE_BPP_24 /*0x40*/;

		if (lpD3DHELDeviceDesc->dwDeviceRenderBitDepth & DDBD_32 /*0x100*/) // 32 bpp
			device->flags |= DEVICEMODE_BPP_32 /*0x80*/;

	}

	if (lpD3DHELDeviceDesc->dwFlags & D3DDD_DEVCAPS /*0x2*/) {
		if (lpD3DHELDeviceDesc->dwDevCaps & D3DDEVCAPS_TEXTUREVIDEOMEMORY /*0x200*/) {
			device->flags |= DEVICEMODE_TEXTUREVIDEOMEMORY /*0x4000*/;
		}
		else if (lpD3DHELDeviceDesc->dwDevCaps & D3DDEVCAPS_TEXTURESYSTEMMEMORY /*0x100*/) {
			device->flags |= DEVICEMODE_TEXTURESYSTEMMEMORY /*0x8000*/;
		}
	}

	device->guid = *lpGuid; // can I just do this?
	// std::memcpy(&device->guid, lpGuid, sizeof(GUID) /*0x10*/);

	std::sprintf(device->displayName, "%s (%s)", lpDeviceName, lpDeviceDescription);

	globals::g_DirectDrawDeviceEnumerate_COUNT++;
	return DIENUM_CONTINUE /*0x1*/; // continue enumeration
}

// <LegoRR.exe @0047c770>
BOOL __cdecl lego::ddraw::DDraw_PopulateScreenModes(const DriverMode * driver, BOOL isFullScreen, ScreenMode * ref_ScreenModes, int * out_count)
{
	BOOL success = false;
	globals::g_DirectDrawScreenEnumerate_COUNT = 0;

	if (driver != nullptr && (driver->flags & DRIVERMODE_ISUSED /*0x1*/)) {

		LPGUID lpGuid = nullptr;
		if (!(driver->flags & DRIVERMODE_NOGUID_10 /*0x10*/))
			lpGuid = const_cast<LPGUID>(&driver->guid); // not actually modified, but function requires non-const
		//LPGUID lpGuid = ((driver->flags & DRIVERMODE_NOGUID_10 /*0x10*/) ? nullptr : &driver->guid);

		IDirectDraw* ddraw1;
		if (::DirectDrawCreate(lpGuid, &ddraw1, nullptr) == 0) {

			IDirectDraw4* ddraw4; // uuid("9c59509a-39bd-11d1-8c4a-00c04fd930c5")
			if (ddraw1->QueryInterface(idl::IID_IDirectDraw4, (LPVOID*)&ddraw4) == 0) {
				globals::g_DirectDrawScreenEnumerate_TABLE = ref_ScreenModes;
				ddraw4->EnumDisplayModes(0, nullptr, (LPVOID)&isFullScreen, DDraw_EnumerateScreenCallback);

				ddraw4->Release();

				success = true;
			}
			/// FAILED: IDirectDraw->QueryInterface => IDirectDraw4
			ddraw1->Release();
		}
		/// FAILED: DirectDrawCreate
	}
	*out_count = globals::g_DirectDrawScreenEnumerate_COUNT;
	return success;
}

// <LegoRR.exe @0047c810>
HRESULT CALLBACK lego::ddraw::DDraw_EnumerateScreenCallback(DDSURFACEDESC2 * lpDDSurfaceDesc, LPVOID lpContext)
{
	ScreenMode* screen = &globals::g_DirectDrawScreenEnumerate_TABLE[globals::g_DirectDrawScreenEnumerate_COUNT];
	screen->flags = SCREENMODE_ISUSED /*0x1*/;
	screen->screenWidth  = (int)lpDDSurfaceDesc->dwWidth;
	screen->screenHeight = (int)lpDDSurfaceDesc->dwHeight;
	screen->bitDepth = (int)lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount;

	BOOL isFullScreen = *(BOOL*)lpContext;
	if (isFullScreen) {
		std::sprintf(screen->displayName, "%ix%i (%i bit)", (int)lpDDSurfaceDesc->dwWidth,
				(int)lpDDSurfaceDesc->dwHeight, (int)lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount);
	}
	else {
		/// QOL: Show bit-depth for Windowed mode too
		std::sprintf(screen->displayName, "%ix%i", (int)lpDDSurfaceDesc->dwWidth,
				(int)lpDDSurfaceDesc->dwHeight);

		if (globals::g_DirectDrawScreenEnumerate_COUNT != 0 && screen->bitDepth != main::GetDeviceBitsPerPixel()) {
			// Bit depth doesn't match system, we can't use this in windowed
			screen->flags &= ~SCREENMODE_ISUSED /*~0x1*/;
			
			// skip incrementing COUNT and return
			return DDENUMRET_OK /*0x1*/; // continue enumeration
		}
	}

	globals::g_DirectDrawScreenEnumerate_COUNT++;
	return DDENUMRET_OK /*0x1*/; // continue enumeration
}

// <LegoRR.exe @0047c8d0>
BOOL __cdecl lego::ddraw::StartScreenMode(BOOL isFullScreen, const DriverMode * driver, const DeviceMode * device, const ScreenMode * screen, int x, int y, int screenWidth, int screenHeight)
{
	DDSURFACEDESC2 surf;

	DWORD dwBPP = 16; // 32;

	if (driver && !(driver->flags && DRIVERMODE_ISUSED)) {
		driver = nullptr;
	}
	if (screen) {
		if (!(screen->flags && SCREENMODE_ISUSED)) {
			screen = nullptr;
		}
		else if (screen) {
			screenWidth = screen->screenWidth;
			screenHeight = screen->screenHeight;
			dwBPP = (DWORD)screen->bitDepth;
		}
	}

	globals::g_ScreenIsFullScreen = isFullScreen;
	LPGUID lpGuid = nullptr;
	if (driver && !(driver->flags & DRIVERMODE_NOGUID_10 /*0x10*/))
		lpGuid = const_cast<LPGUID>(&driver->guid); // not actually modified, but function requires non-const

	globals::g_ScreenSize.width  = screenWidth;
	globals::g_ScreenSize.height = screenHeight;
	main::ShowGameWindow(isFullScreen, x, y, screenWidth, screenHeight);

	IDirectDraw* ddraw1;
	if (::DirectDrawCreate(lpGuid, &ddraw1, nullptr) == 0) {
		//IDirectDraw4* // uuid("9c59509a-39bd-11d1-8c4a-00c04fd930c5")
		if (ddraw1->QueryInterface(idl::IID_IDirectDraw4, (LPVOID*)&globals::g_IDirectDraw4) == 0) {

			DWORD dwFlags = (isFullScreen ? (DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN /*0x10 | 0x1*/)
										  : (DDSCL_NORMAL /*0x8*/));
			if (globals::g_IDirectDraw4->SetCooperativeLevel(globals::g_DirectDraw_hWnd, dwFlags) == 0) {
				//HRESULT result;
				if (!isFullScreen || globals::g_IDirectDraw4->SetDisplayMode((DWORD)screenWidth, (DWORD)screenHeight, dwBPP, 0, 0) == 0) {

					std::memset(&surf, 0, sizeof(surf) /*0x7c*/);
					surf.dwSize = sizeof(surf) /*0x7c*/;
					surf.dwFlags = DDSD_CAPS /*0x1*/;
					surf.ddsCaps.dwCaps = DDSCAPS_3DDEVICE | DDSCAPS_PRIMARYSURFACE /*0x2000 | 0x200*/;
					if (isFullScreen) {
						surf.dwFlags |= DDSD_BACKBUFFERCOUNT /*0x20*/;
						surf.dwBackBufferCount = 1;
						surf.ddsCaps.dwCaps |= DDSCAPS_FLIP | DDSCAPS_COMPLEX /*0x10 | 0x8*/;
					}

					if (globals::g_IDirectDraw4->CreateSurface(&surf, &globals::g_IDirectDrawSurface4_RenderTarget, nullptr) == 0) {
						HRESULT result;
						if (!isFullScreen) {
							surf.ddsCaps.dwCaps &= ~DDSCAPS_PRIMARYSURFACE /*~0x200*/;
							surf.ddsCaps.dwCaps |= DDSCAPS_OFFSCREENPLAIN /*0x40*/;
							surf.dwFlags |= DDSD_WIDTH | DDSD_HEIGHT /*0x4 | 0x2*/;
							surf.dwWidth  = screenWidth;
							surf.dwHeight = screenHeight;
							result = globals::g_IDirectDraw4->CreateSurface(&surf, &globals::g_IDirectDrawSurface4_DrawTarget, nullptr);
						}
						else {
							DDSCAPS2 ddsCaps;
							std::memset(&ddsCaps, 0, sizeof(ddsCaps) /*0x4*/);
							ddsCaps.dwCaps = DDSCAPS_BACKBUFFER /*0x4*/;
							result = globals::g_IDirectDrawSurface4_RenderTarget->GetAttachedSurface(&ddsCaps, &globals::g_IDirectDrawSurface4_DrawTarget);
						}
						if (result == 0) {

							if (DDraw_InitClipperRegion(isFullScreen, screenWidth, screenHeight) &&
								main::InitDirect3DRM(device, ddraw1, globals::g_IDirectDrawSurface4_DrawTarget, isFullScreen))
							{
								/// QOL: Change this behavior to allow showing the cursor on the title bar in windowed
								if (!isFullScreen) { // || SHOWCURSOR) {
									::ShowCursor(false /*SHOWCURSOR*/);
								}
								return true;
							}
							globals::g_IDirectDrawSurface4_DrawTarget->Release();
							globals::g_IDirectDrawSurface4_DrawTarget = nullptr;
						}
						/// FAILED: IDirectDraw4->CreateSurface (2) -or- IDirectDrawSurface4->GetAttachedSurface
						globals::g_IDirectDrawSurface4_RenderTarget->Release();
						globals::g_IDirectDrawSurface4_RenderTarget = nullptr;
					}
					/// FAILED: IDirectDraw4->CreateSurface (1)
				}
				/// FAILED: IDirectDraw4->SetDisplayMode
			}
			/// FAILED: IDirectDraw4->SetCooperativeLevel
			globals::g_IDirectDraw4->Release();
			globals::g_IDirectDraw4 = nullptr;
		}
		/// FAILED: IDirectDraw->QueryInterface => IDirectDraw4
		ddraw1->Release();
	}
	/// FAILED: DirectDrawCreate
	return false;
}

// <LegoRR.exe @0047cb90>
void __cdecl lego::ddraw::DDraw_Render(void)
{
	if (globals::g_ScreenIsFullScreen) {
		globals::g_IDirectDrawSurface4_RenderTarget->Flip(nullptr, DDFLIP_WAIT /*0x1*/);
	}
	else {
		// in assembly, this is a direct JMP, and not a CALL... no idea why
		DDraw_RenderWindowed();
	}
}

// Called by FUN_0047e700 <= MenuLoop_FUN_00413ab0
// <LegoRR.exe @0047cbb0>
int __cdecl lego::ddraw::Image_FUN_0047cbb0(int * param_1, char * param_2)
{
	
}

// <LegoRR.exe @0047cee0>
void __cdecl lego::ddraw::DDraw_CopyToDrawTarget(void)
{
	if (globals::g_ScreenIsFullScreen) {
		globals::g_IDirectDrawSurface4_DrawTarget->Blt(nullptr, globals::g_IDirectDrawSurface4_RenderTarget,
													   nullptr, DDBLT_WAIT /*0x1000000*/, nullptr);
	}
}

// <LegoRR.exe @0047cf10>
void __cdecl lego::ddraw::DDraw_RenderWindowed(void)
{
	POINT ptClient = { 0, 0 };
	RECT dstRect = { 0, 0, globals::g_ScreenSize.width, globals::g_ScreenSize.height };

	::ClientToScreen(globals::g_DirectDraw_hWnd, &ptClient);
	::OffsetRect(&dstRect, ptClient.x, ptClient.y);

	RECT srcRect = { 0, 0, globals::g_ScreenSize.width, globals::g_ScreenSize.height };

	globals::g_IDirectDrawSurface4_RenderTarget->Blt(&dstRect, globals::g_IDirectDrawSurface4_DrawTarget,
													 &srcRect, DDBLT_WAIT /*0x1000000*/, nullptr);
}

// <LegoRR.exe @0047cfb0>
void __cdecl lego::ddraw::CleanupDirectDraw(void)
{
	if (globals::g_IDirectDrawSurface4_RenderTarget)
		globals::g_IDirectDrawSurface4_RenderTarget->Release();
	if (globals::g_IDirectDrawClipper_RenderTarget)
		globals::g_IDirectDrawClipper_RenderTarget->Release();

	// This is cleaned up elsewhere, during DDraw_InitClipperRegion
	//if (globals::g_IDirectDrawSurface4_DrawTarget)
	//	globals::g_IDirectDrawSurface4_DrawTarget->Release();

	if (globals::g_IDirectDrawClipper_DrawTarget)
		globals::g_IDirectDrawClipper_DrawTarget->Release();

	if (globals::g_IDirectDraw4) {
		if (globals::g_ScreenIsFullScreen)
			globals::g_IDirectDraw4->RestoreDisplayMode();

		if (globals::g_IDirectDraw4)
			globals::g_IDirectDraw4->Release();
	}
}

// Convert texture usage (in units of pixels) into units of bytes.
//  This should *always* result in: ref_textureUsage * 2  (aka 2 bytes per 16-bit pixel)
// <LegoRR.exe @0047d010>
void __cdecl lego::ddraw::CalculateTextureUsage(uint * ref_textureUsage)
{
	/*typedef enum CONST_D3DRMFPTFFLAGS {
		D3DRMFPTF_ALPHA = 0x00000001,
		D3DRMFPTF_NOALPHA = 0x00000002,
		D3DRMFPTF_PALETTIZED = 0x00000004,
		D3DRMFPTF_NOTPALETTIZED = 0x00000008
	} D3DRMFPTFFLAGS;*/
	DDPIXELFORMAT pixFmt;

	// first make sure we're not in 8-bit paletted mode?
	std::memset(&pixFmt, 0, sizeof(DDPIXELFORMAT) /*0x20*/);
	pixFmt.dwSize = sizeof(DDPIXELFORMAT) /*0x20*/;
	if (main::globals::g_IDirect3DRMDevice3->FindPreferredTextureFormat(DDBD_8 /*0x800*/, D3DRMFPTF_PALETTIZED /*0x4*/, &pixFmt) != 0) {

		// confirm we are in 16 bit mode than multiply by number of bytes per pixel (rounded down)
		std::memset(&pixFmt, 0, sizeof(DDPIXELFORMAT) /*0x20*/);
		pixFmt.dwSize = sizeof(DDPIXELFORMAT) /*0x20*/;
		if (main::globals::g_IDirect3DRMDevice3->FindPreferredTextureFormat(DDBD_16 /*0x400*/, 0, &pixFmt) == 0) {
			*ref_textureUsage *= (pixFmt.dwRGBBitCount / 8);
			//*(unsigned int*)pixFmt.dwGBitMask = (unaff_EDI >> 3) * *(int*)pixFmt.dwGBitMask;
		}
	}
}

// <LegoRR.exe @0047d090>
BOOL __cdecl lego::ddraw::GetAvailableVideoMemory(uint * out_totalMem, uint * out_freeMem)
{
	DDSCAPS2 ddsCaps;
	ddsCaps.dwCaps = DDSCAPS_TEXTURE /*0x1000*/;
	ddsCaps.dwCaps2 = 0;
	ddsCaps.dwCaps3 = 0;
	ddsCaps.dwCaps4 = 0;

	*out_totalMem = 0;
	*out_freeMem = 0;
	return (globals::g_IDirectDraw4->GetAvailableVidMem(&ddsCaps, (LPDWORD)out_totalMem, (LPDWORD)out_freeMem) == 0);
}

// <LegoRR.exe @0047d0e0>
HRESULT __cdecl lego::ddraw::Draw_FillSurface(const Rect2F * rect, uint rgbColor)
{
	DDBLTFX ddBlt;
	std::memset(&ddBlt, 0, sizeof(ddBlt) /*0x64*/);
	ddBlt.dwSize = sizeof(ddBlt) /*0x64*/;
	ddBlt.dwFillColor = packNativeRGB(globals::g_IDirectDrawSurface4_DrawTarget, rgbColor);

	if (rect != nullptr) {
		RECT dstRect = {
			(int)(long long)rect->x,
			(int)(long long)rect->y,
			(int)(long long)(rect->width  + rect->x),
			(int)(long long)(rect->height + rect->y)
		};

		return globals::g_IDirectDrawSurface4_DrawTarget->Blt(&dstRect, nullptr, nullptr,
			DDBLT_WAIT | DDBLT_COLORFILL /*0x1000000 | 0x400*/, &ddBlt);
	}
	else {
		return globals::g_IDirectDrawSurface4_DrawTarget->Blt(nullptr, nullptr, nullptr,
			DDBLT_WAIT | DDBLT_COLORFILL /*0x1000000 | 0x400*/, &ddBlt);
	}
}

// <LegoRR.exe @0047d1a0>
BOOL __cdecl lego::ddraw::DDraw_InitClipperRegion(BOOL isFullScreen, int screenWidth, int screenHeight)
{
	if (globals::g_IDirectDraw4->CreateClipper(0, &globals::g_IDirectDrawClipper_DrawTarget, nullptr) == 0) {
		HRGN hRgn = ::CreateRectRgn(0, 0, screenWidth, screenHeight);
		DWORD length = ::GetRegionData(hRgn, 0, nullptr);
		LPRGNDATA lpRgnData = (LPRGNDATA)std::malloc(length);
		::GetRegionData(hRgn, length, lpRgnData);

		if (globals::g_IDirectDrawClipper_DrawTarget->SetClipList(lpRgnData, 0) == 0) {
			std::free(lpRgnData);
			if (globals::g_IDirectDrawSurface4_DrawTarget->SetClipper(globals::g_IDirectDrawClipper_DrawTarget) == 0) {
				
				if (isFullScreen) {
					return true;
				}

				if (globals::g_IDirectDraw4->CreateClipper(0, &globals::g_IDirectDrawClipper_RenderTarget, nullptr) == 0) {
					if (globals::g_IDirectDrawClipper_RenderTarget->SetHWnd(0, globals::g_DirectDraw_hWnd) == 0) {
						if (globals::g_IDirectDrawSurface4_RenderTarget->SetClipper(globals::g_IDirectDrawClipper_RenderTarget) == 0) {
							return true;
						}
					}
					/// FAILED: IDirectDrawClipper->SetHWnd
				}
				/// FAILED: IDirectDraw4->CreateClipper (2)
			}
			/// FAILED: IDirectDrawSurface4->SetClipper (1)
			globals::g_IDirectDrawSurface4_DrawTarget->Release();
			globals::g_IDirectDrawSurface4_DrawTarget = nullptr;
		}
		/// FAILED: IDirectDrawClipper->SetClipList
		std::free(lpRgnData); // this will get free'd twice...
	}
	/// FAILED: IDirectDraw4->CreateClipper (1)
	return false;
}

// Called by FUN_00474310
// <LegoRR.exe @0047d2c0>
undefined __cdecl lego::ddraw::DDraw_FUN_0047d2c0(undefined4 param_1, int * param_2)
{
	
}

// Called by FUN_00474310, Draw_FillSurface
// <LegoRR.exe @0047d590>
uint __cdecl lego::ddraw::packNativeRGB(IDirectDrawSurface4 * ddSurface4, uint rgbColor)
{
	PALETTEENTRY palEntries[256];

	unsigned int r = rgbColor & 0xff;
	unsigned int g = (rgbColor >> 8) & 0xff;
	unsigned int b = (rgbColor >> 16) & 0xff;

	DDPIXELFORMAT pixFmt;
	std::memset(&pixFmt, 0, sizeof(pixFmt) /*0x20*/);
	pixFmt.dwSize = sizeof(pixFmt) /*0x20*/;

	ddSurface4->GetPixelFormat(&pixFmt);

	if (pixFmt.dwFlags & DDPF_RGB /*0x40*/) {
		int rbits = countBits2(pixFmt.dwRBitMask);
		int gbits = countBits2(pixFmt.dwGBitMask);
		int bbits = countBits2(pixFmt.dwBBitMask);
		return	((r >> (8U - (rbits & 0x1f))) << ((bbits & 0x1f) + (gbits & 0x1f))) |
				((g >> (8U - (gbits & 0x1f))) <<  (bbits & 0x1f)) |
				 (b >> (8U - (bbits & 0x1f)));
	}
	else {
		IDirectDrawPalette* ddPal;
		ddSurface4->GetPalette(&ddPal);
		ddPal->GetEntries(0, 0, 256, palEntries);
		for (int i = 0; i < 256; i++) {
			if (palEntries[i].peRed == r && palEntries[i].peGreen == g && palEntries[i].peBlue == b)
				return i;
		}
		return 256;
	}
}

// Called by packNativeRGB
// <LegoRR.exe @0047d6b0>
int __cdecl lego::ddraw::countBits2(uint value)
{
	int count = 0;	
	while (value != 0) {
		value &= value - 1;
		count++;
	}
	return count;
}

#pragma endregion
