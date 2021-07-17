// DirectDraw.cpp : 
//

#include "DirectDraw.h"
#include "Images.h"
#include "../Main/Main.h"
#include "../Helpers/Utils.h"


#pragma region Globals
namespace lego {
namespace draw {
namespace globals {
	// define these because I'm too lazy to deal with linker errors
	static IID IID_IDirect3D3 = { 0xbb223240, 0xe72b, 0x11d0, 0xa9, 0xb4, 0x00, 0xaa, 0x00, 0xc0, 0x99, 0x3e };

	static IID IID_IDirectDraw4 = { 0x9c59509a, 0x39bd, 0x11d1, 0x8c, 0x4a, 0x00, 0xc0, 0x4f, 0xd9, 0x30, 0xc5 };


	// <LegoRR.exe @0076bc80>
	HWND g_DirectDraw_hWnd;
	// <LegoRR.exe @0076bc84>
	IDirectDraw4* g_IDirectDraw4;
	// <LegoRR.exe @0076bc88>
	IDirectDrawSurface4* g_IDirectDrawSurface4_RenderTarget;
	// <LegoRR.exe @0076bc8c>
	IDirectDrawSurface4* g_IDirectDrawSurface4_DrawTarget;
	// <LegoRR.exe @0076bc90>
	unsigned int g_DirectDraw_UNUSED_0076bc90;
	// <LegoRR.exe @0076bc94>
	IDirectDrawClipper* g_IDirectDrawClipper_RenderTarget;
	// <LegoRR.exe @0076bc98>
	IDirectDrawClipper* g_IDirectDrawClipper_DrawTarget;
	// <LegoRR.exe @0076bc9c>
	static DriverMode* g_DirectDrawDriverEnumerate_TABLE;

	// <LegoRR.exe @0076bca4>
	static DeviceMode* g_DirectDrawDeviceEnumerate_TABLE;

	// <LegoRR.exe @0076bcac>
	static ScreenMode* g_DirectDrawScreenEnumerate_TABLE;
	// <LegoRR.exe @0076bcb0>
	static int g_DirectDrawDriverEnumerate_COUNT;
	// <LegoRR.exe @0076bcb4>
	static int g_DirectDrawDeviceEnumerate_COUNT;
	// <LegoRR.exe @0076bcb8>
	static int g_DirectDrawScreenEnumerate_COUNT;
	// <LegoRR.exe @0076bcbc>
	static BOOL g_ScreenIsFullScreen;
	// <LegoRR.exe @0076bcc0>
	static Size2I g_ScreenSize;

} /* namespace globals */
} /* namespace directx */
} /* namespace lego */
#pragma endregion


using namespace lego;
using namespace lego::draw;


#pragma region Functions

// <LegoRR.exe @00406500>
IDirectDraw4* __cdecl lego::draw::GetDirectDraw(void)
{
	return globals::g_IDirectDraw4;
}

// <LegoRR.exe @00406510>
IDirectDrawSurface4* __cdecl lego::draw::GetDrawingSurface(void)
{
	return globals::g_IDirectDrawSurface4_DrawTarget;
}


#pragma region Enumerate Callbacks

// <LegoRR.exe @0047c4b0>
BOOL CALLBACK lego::draw::DirectDrawDriverEnumerate_Callback(LPGUID lpGuid, LPSTR lpDriverName, LPSTR lpDriverDescription, LPVOID lpContext)
{
	//debugf("Dlg_DirectDrawDriverEnumerate_Callback\n");
	DriverMode* driverMode = &globals::g_DirectDrawDriverEnumerate_TABLE[globals::g_DirectDrawDriverEnumerate_COUNT];

	driverMode->flags = DRIVERMODE_ISUSED /*0x1*/;
	if (lpGuid == NULL) {
		driverMode->flags |= DRIVERMODE_NOGUID_10 /*0x10*/;
		driverMode->flags |= DRIVERMODE_NOGUID_20 /*0x20*/;
	}
	else {
		driverMode->guid = *lpGuid; // can I just do this?
		// std::memcpy(&driverMode->guid, lpGuid, sizeof(GUID) /*16*/);
		// (driverMode->guid).Data1 = lpGuid->Data1;
		// *(undefined4 *)&(driverMode->guid).Data2 = *(undefined4 *)&lpGuid->Data2;
		// *(undefined4 *)(driverMode->guid).Data4 = *(undefined4 *)lpGuid->Data4;
		// *(undefined4 *)((driverMode->guid).Data4 + 4) = *(undefined4 *)(lpGuid->Data4 + 4);
	}
	std::sprintf(driverMode->displayName, "%s (%s)", lpDriverName, lpDriverDescription);
	globals::g_DirectDrawDriverEnumerate_COUNT++;
	return TRUE;
}


// <LegoRR.exe @0047c640>
HRESULT CALLBACK lego::draw::DirectDrawDeviceEnumerate_Callback(LPGUID lpGuid, LPSTR lpDeviceDescription, LPSTR lpDeviceName, LPD3DDEVICEDESC lpD3DHWDeviceDesc, LPD3DDEVICEDESC lpD3DHELDeviceDesc, LPVOID lpContext)
{
	//debugf("Dlg_DirectDrawDeviceEnumerate_Callback\n");
	DeviceMode* deviceMode = &globals::g_DirectDrawDeviceEnumerate_TABLE[globals::g_DirectDrawDeviceEnumerate_COUNT];

	deviceMode->flags = DEVICEMODE_ISUSED /*0x1*/;

	if (lpD3DHWDeviceDesc->dcmColorModel != 0) {
		deviceMode->flags |= DEVICEMODE_HARDWARE /*0x2000*/;
		lpD3DHELDeviceDesc = lpD3DHWDeviceDesc;
	}
	/* D3DDD_COLORMODEL (0x1) and D3DCOLOR_RGB (0x2) */
	if ((lpD3DHELDeviceDesc->dwFlags & D3DDD_COLORMODEL /*0x1*/) && lpD3DHELDeviceDesc->dcmColorModel == D3DCOLOR_RGB /*2*/) {
		deviceMode->flags |= DEVICEMODE_COLORMODEL_RGB /*0x1000*/;
	}

	/* D3DDD_DEVICERENDERBITDEPTH (0x80) */
	if (lpD3DHELDeviceDesc->dwFlags & D3DDD_DEVICERENDERBITDEPTH /*0x80*/) {
		/* <https://github.com/github/VisualStudio/blob/263aac11f57d53c5f9fe64ba9916f77c058974d7/tools/Debugging%20Tools%20for%20Windows/winext/manifest/ddraw.h#L1421>
		DDBD_8 (0x800) 8 bpp */
		if (lpD3DHELDeviceDesc->dwDeviceRenderBitDepth & DDBD_8 /*0x800*/)
			deviceMode->flags |= DEVICEMODE_BPP_8 /*0x10*/;

		/* DDBD_16 (0x400) 16 bpp */
		if (lpD3DHELDeviceDesc->dwDeviceRenderBitDepth & DDBD_16 /*0x400*/)
			deviceMode->flags |= DEVICEMODE_BPP_16 /*0x20*/;

		/* DDBD_24 (0x200) 24 bpp */
		if (lpD3DHELDeviceDesc->dwDeviceRenderBitDepth & DDBD_24 /*0x200*/)
			deviceMode->flags |= DEVICEMODE_BPP_24 /*0x40*/;

		/* DDBD_32 (0x100) 32 bpp */
		if (lpD3DHELDeviceDesc->dwDeviceRenderBitDepth & DDBD_32 /*0x100*/)
			deviceMode->flags |= DEVICEMODE_BPP_32 /*0x80*/;

	}
	/* D3DDD_DEVCAPS (0x2) */
	if (lpD3DHELDeviceDesc->dwFlags & D3DDD_DEVCAPS /*0x2*/) {
		if (lpD3DHELDeviceDesc->dwDevCaps & D3DDEVCAPS_TEXTUREVIDEOMEMORY /*0x200*/) {
			deviceMode->flags |= DEVICEMODE_TEXTUREVIDEOMEMORY /*0x4000*/;
		}
		else if (lpD3DHELDeviceDesc->dwDevCaps & D3DDEVCAPS_TEXTURESYSTEMMEMORY /*0x100*/) {
			deviceMode->flags |= DEVICEMODE_TEXTURESYSTEMMEMORY /*0x8000*/;
		}
		// /* D3DDEVCAPS_TEXTUREVIDEOMEMORY (0x200) */
		// if ((lpD3DHELDeviceDesc->dwDevCaps & 0x200) == 0) {
		// 	/* D3DDEVCAPS_TEXTURESYSTEMMEMORY (0x100) */
		// 	if ((lpD3DHELDeviceDesc->dwDevCaps & 0x100) == 0) goto LAB_0047c71d;
		// 	DVar2 = deviceMode->flags | DEVICEMODE_TEXTURESYSTEMMEMORY;
		// }
		// else {
		// DVar2 = deviceMode->flags | DEVICEMODE_TEXTUREVIDEOMEMORY;
		// }
		// deviceMode->flags = DVar2;
	}

	deviceMode->guid = *lpGuid; // can I just do this?
	// std::memcpy(&deviceMode->guid, lpGuid, sizeof(GUID) /*16*/);
	// (deviceMode->guid).Data1 = lpGuid->Data1;
	// *(undefined4 *)&(deviceMode->guid).Data2 = *(undefined4 *)&lpGuid->Data2;
	// *(undefined4 *)(deviceMode->guid).Data4 = *(undefined4 *)lpGuid->Data4;
	// *(undefined4 *)((deviceMode->guid).Data4 + 4) = *(undefined4 *)(lpGuid->Data4 + 4);

	std::sprintf(deviceMode->displayName, "%s (%s)", lpDeviceName, lpDeviceDescription);
	globals::g_DirectDrawDeviceEnumerate_COUNT++;
	return 1;
}


// <LegoRR.exe @0047c810>
HRESULT CALLBACK lego::draw::DirectDrawScreenEnumerate_Callback(LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext)
{
	//debugf("Dlg_DirectDrawScreenEnumerate_Callback\n");
	ScreenMode* screenMode = &globals::g_DirectDrawScreenEnumerate_TABLE[globals::g_DirectDrawScreenEnumerate_COUNT];
	screenMode->flags = SCREENMODE_ISUSED /*0x1*/;
	screenMode->screenWidth = lpDDSurfaceDesc->dwWidth;
	screenMode->screenHeight = lpDDSurfaceDesc->dwHeight;
	screenMode->bitDepth = lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount;

	BOOL isFullScreen = *(BOOL*)lpContext;
	if (isFullScreen) {
		std::sprintf(screenMode->displayName, "%ix%i (%i bit)", (int)lpDDSurfaceDesc->dwWidth, (int)lpDDSurfaceDesc->dwHeight, (int)lpDDSurfaceDesc->ddpfPixelFormat.dwRGBBitCount);
	}
	else {
		std::sprintf(screenMode->displayName, "%ix%i", (int)lpDDSurfaceDesc->dwWidth, (int)lpDDSurfaceDesc->dwHeight);
		if (screenMode->bitDepth != main::GetDeviceBitsPerPixel()) {
			// Bit depth doesn't match system, we can't use this in windowed
			screenMode->flags &= ~SCREENMODE_ISUSED /*~0x1*/;
		}
	}

	globals::g_DirectDrawScreenEnumerate_COUNT++;
	return 1;
}

#pragma endregion


// <LegoRR.exe @0047c430>
void __cdecl lego::draw::InitDirectDraw(HWND hWnd)
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

// Unlike other populate methods, this must ONLY be called once.
// There's no extra cleanup like resetting the count.
// <LegoRR.exe @0047c480>
BOOL __cdecl lego::draw::PopulateDriverModes(DriverMode* ref_driverModes, int* out_count)
{
	debugf("Dlg_PopulateDriverModes\n");
	globals::g_DirectDrawDriverEnumerate_TABLE = ref_driverModes;
	if (DirectDrawEnumerateA(DirectDrawDriverEnumerate_Callback, nullptr) != 0)
		debugf("FAILED: Dlg_PopulateDriverModes -> DirectDrawEnumerateA\n");
	*out_count = globals::g_DirectDrawDriverEnumerate_COUNT;
	return TRUE;
}

// <LegoRR.exe @0047c5a0>
BOOL __cdecl lego::draw::PopulateDeviceModes(DriverMode* driverMode, DeviceMode* ref_deviceModes, int* out_count)
{
	debugf("Dlg_PopulateDeviceModes\n");
	BOOL success = FALSE;
	globals::g_DirectDrawDeviceEnumerate_COUNT = 0;

	IDirectDraw* baseDirectDraw;
	if (DirectDrawCreate(&driverMode->guid, &baseDirectDraw, NULL) == 0) {

		IDirectDraw4* directDraw = nullptr; // dummy init // uuid("9c59509a-39bd-11d1-8c4a-00c04fd930c5")
		if (baseDirectDraw->QueryInterface(/*globals::*/IID_IDirectDraw4, (LPVOID*)&directDraw) == 0) {

			IDirect3D3* direct3D = nullptr; // dummy init // uuid("bb223240-e72b-11d0-a9b4-00aa00c0993e")
			if (directDraw->QueryInterface(/*globals::*/IID_IDirect3D3, (LPVOID*)&direct3D) == 0) {
				globals::g_DirectDrawDeviceEnumerate_TABLE = ref_deviceModes;
				if (direct3D->EnumDevices(DirectDrawDeviceEnumerate_Callback, NULL) != 0)
					debugf("FAILED: Dlg_PopulateDeviceModes -> EnumDevices\n");

				success = TRUE;

				direct3D->Release();
			}
			else debugf("FAILED: Dlg_PopulateDeviceModes -> QueryInterface IID_IDirect3D3\n");
			directDraw->Release();
		}
		else debugf("FAILED: Dlg_PopulateDeviceModes -> QueryInterface IID_IDirectDraw4\n");
		baseDirectDraw->Release();
	}
	else debugf("FAILED: Dlg_PopulateDeviceModes -> DirectDrawCreate\n");
	*out_count = globals::g_DirectDrawDeviceEnumerate_COUNT;
	return success;
}

// <LegoRR.exe @0047c770>
BOOL __cdecl lego::draw::PopulateScreenModes(DriverMode* driverMode, BOOL isFullScreen, ScreenMode* ref_ScreenModes, int* out_count)
{
	debugf("Dlg_PopulateScreenModes\n");
	BOOL success = FALSE;
	globals::g_DirectDrawScreenEnumerate_COUNT = 0;

	if (driverMode != NULL && (driverMode->flags & DRIVERMODE_ISUSED /*0x1*/)) {

		IDirectDraw* baseDirectDraw = nullptr; // dummy init
		LPGUID lpGuid = ((driverMode->flags & DRIVERMODE_NOGUID_10 /*0x10*/) ? NULL : &driverMode->guid);
		if (DirectDrawCreate(lpGuid, &baseDirectDraw, NULL) == 0) {

			IDirectDraw4* directDraw = nullptr; // dummy init // uuid("9c59509a-39bd-11d1-8c4a-00c04fd930c5")
			if (baseDirectDraw->QueryInterface(/*globals::*/IID_IDirectDraw4, (LPVOID*)&directDraw) == 0) {
				globals::g_DirectDrawScreenEnumerate_TABLE = ref_ScreenModes;
				if (directDraw->EnumDisplayModes(0, NULL, (LPVOID)&isFullScreen, DirectDrawScreenEnumerate_Callback) != 0)
					debugf("FAILED: Dlg_PopulateScreenModes -> EnumDisplayModes\n");

				success = TRUE;

				directDraw->Release();
			}
			else debugf("FAILED: Dlg_PopulateScreenModes -> QueryInterface IID_IDirectDraw4\n");
			baseDirectDraw->Release();
		}
		else debugf("FAILED: Dlg_PopulateScreenModes -> DirectDrawCreate\n");
	}
	*out_count = globals::g_DirectDrawScreenEnumerate_COUNT;
	return success;
}

#if 0
// <LegoRR.exe @00483c00>
void __cdecl FUN_00483c00(void)
{
	//D3DLIGHTSTATETYPE
	if (lego::globals::DAT_00541574 != lego::globals::DAT_00541568) {
		lego::globals::g_IDirect3DDevice3->SetLightState(D3DLIGHTSTATE_MATERIAL /*1*/, DAT_00541568);
	}
	if (!(lego::globals::g_CMDLINE_FLAGS & CMD_NM /*0x20, no texture management*/)) {
		if (DAT_00541578 != DAT_0054156c) {
			lego::globals::g_IDirect3DDevice3->SetTexture(NULL, DAT_0054156c);
		}
		if (DAT_00541564 != 0) {
			lego::globals::g_IDirect3DDevice3->SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE /*1*/, DAT_00541564);
		}
	}
	else {
		lego::globals::g_IDirect3DDevice3->SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE /*1*/, DAT_00541564);
	}
	return;
}

#pragma region D3D ENUMS
enum D3DLIGHTSTATETYPE {
	D3DLIGHTSTATE_MATERIAL    = 1,
	D3DLIGHTSTATE_AMBIENT     = 2,
	D3DLIGHTSTATE_COLORMODEL  = 3,
	D3DLIGHTSTATE_FOGMODE     = 4,
	D3DLIGHTSTATE_FOGSTART    = 5,
	D3DLIGHTSTATE_FOGEND      = 6,
	D3DLIGHTSTATE_FOGDENSITY  = 7,
	D3DLIGHTSTATE_COLORVERTEX = 8,
	D3DLIGHTSTATE_FORCE_DWORD = 0x7fffffff, /* force 32-bit size enum */
} ;

enum D3DANTIALIASMODE : unsigned int
{
	D3DANTIALIAS_NONE            = 0,
	D3DANTIALIAS_SORTDEPENDENT   = 1,
	D3DANTIALIAS_SORTINDEPENDENT = 2,
};
enum D3DBLEND : unsigned int
{
	D3DBLEND_INVALID_0       = 0,
	D3DBLEND_ZERO            = 1,
	D3DBLEND_ONE             = 2,
	D3DBLEND_SRCCOLOR        = 3,
	D3DBLEND_INVSRCCOLOR     = 4,
	D3DBLEND_SRCALPHA        = 5,
	D3DBLEND_INVSRCALPHA     = 6,
	D3DBLEND_DESTALPHA       = 7,
	D3DBLEND_INVDESTALPHA    = 8,
	D3DBLEND_DESTCOLOR       = 9,
	D3DBLEND_INVDESTCOLOR    = 10,
	D3DBLEND_SRCALPHASAT     = 11,
	D3DBLEND_BOTHSRCALPHA    = 12,
	D3DBLEND_BOTHINVSRCALPHA = 13,
};
enum D3DCMPFUNC : unsigned int
{
	D3DCMP_INVALID_0    = 0,
	D3DCMP_NEVER        = 1,
	D3DCMP_LESS         = 2,
	D3DCMP_EQUAL        = 3,
	D3DCMP_LESSEQUAL    = 4,
	D3DCMP_GREATER      = 5,
	D3DCMP_NOTEQUAL     = 6,
	D3DCMP_GREATEREQUAL = 7,
	D3DCMP_ALWAYS       = 8,
};
enum D3DCULL : unsigned int
{
	D3DCULL_INVALID_0 = 0,
	D3DCULL_NONE      = 1,
	D3DCULL_CW        = 2,
	D3DCULL_CCW       = 3,
};
enum D3DFILLMODE : unsigned int // D3DFILL_MODE
{
	D3DFILL_INVALID_0 = 0,
	D3DFILL_POINT     = 1,
	D3DFILL_WIREFRAME = 2,
	D3DFILL_SOLID     = 3,
};
enum D3DFOGMODE : unsigned int
{
	D3DFOG_NONE = 0,
	D3DFOG_EXP  = 1,
	D3DFOG_EXP2 = 2,
};
enum D3DLIGHTTYPE : unsigned int
{

};
enum D3DMATERIALCOLORSOURCE : unsigned int
{
	D3DMCS_MATERIAL = 0,
	D3DMCS_COLOR1   = 1,
	D3DMCS_COLOR2   = 2,
};
enum D3DPRIMITIVETYPE : unsigned int
{
	D3DPT_INVALID_0     = 0,
	D3DPT_POINTLIST     = 1,
	D3DPT_LINELIST      = 2,
	D3DPT_LINESTRIP     = 3,
	D3DPT_TRIANGLELIST  = 4,
	D3DPT_TRIANGLESTRIP = 5,
	D3DPT_TRIANGLEFAN   = 6,
};
enum D3DRENDERSTATETYPE : unsigned int
{
	D3DRENDERSTATE_ANTIALIAS          = 2, // D3DANTIALIASMODE

	D3DRENDERSTATE_TEXTUREPERSPECTIVE = 4, // BOOL, TRUE for perspective correction

	D3DRENDERSTATE_ZENABLE            = 7, // D3DZBUFFERTYPE (or TRUE/FALSE for legacy)
	D3DRENDERSTATE_FILLMODE           = 8, // D3DFILLMODE
	D3DRENDERSTATE_SHADEMODE          = 9, // D3DSHADEMODE
	D3DRENDERSTATE_LINEPATTERN        = 10, // D3DLINEPATTERN

	D3DRENDERSTATE_ZWRITEENABLE       = 14, // BOOL, TRUE to enable z writes
	D3DRENDERSTATE_ALPHATESTENABLE    = 15, // BOOL, TRUE to enable alpha tests
	D3DRENDERSTATE_LASTPIXEL          = 16, // BOOL, TRUE for last-pixel on lines

	D3DRENDERSTATE_SRCBLEND           = 19, // D3DBLEND
	D3DRENDERSTATE_DESTBLEND          = 20, // D3DBLEND

	D3DRENDERSTATE_CULLMODE           = 22, // D3DCULL
	D3DRENDERSTATE_ZFUNC              = 23, // D3DCMPFUNC
	D3DRENDERSTATE_ALPHAREF           = 24,
	D3DRENDERSTATE_ALPHAFUNC          = 25, // D3DCMPFUNC
	D3DRENDERSTATE_DITHERENABLE       = 26, // BOOL, TRUE to enable dithering
	D3DRENDERSTATE_ALPHABLENDENABLE   = 27, // BOOL, TRUE to enable alpha blending
	D3DRENDERSTATE_FOGENABLE          = 28, // BOOL, TRUE to enable fog blending
	D3DRENDERSTATE_SPECULARENABLE     = 29, // BOOL, TRUE to enable specular
	D3DRENDERSTATE_ZVISIBLE           = 30, // BOOL, TRUE to enable z checking

	D3DRENDERSTATE_STIPPLEDALPHA      = 33, // BOOL, TRUE to enable stippled alpha (RGB device only)
	D3DRENDERSTATE_FOGCOLOR           = 34, // D3DCOLOR (DWORD)
	D3DRENDERSTATE_FOGTABLEMODE       = 35, // D3DFOGMODE
	D3DRENDERSTATE_FOGSTART           = 36, // DWORD, Fog start (for both vertex and pixel fog)
	D3DRENDERSTATE_FOGEND             = 37, // DWORD, Fog end
	D3DRENDERSTATE_FOGDENSITY         = 38, // DWORD, Fog density

	// Direct3D version 7
	D3DRENDERSTATE_EDGEANTIALIAS      = 40, // BOOL, TRUE to enable edge antialiasing
	D3DRENDERSTATE_COLORKEYENABLE     = 41, // BOOL, TRUE to enable source colorkeyed textures

	D3DRENDERSTATE_ZBIAS              = 47, // LONG, Z bias
	D3DRENDERSTATE_RANGEFOGENABLE     = 48, // BOOL?, Enables range-based fog

	// Direct3D version 5
	D3DRENDERSTATE_STENCILENABLE      = 52, // BOOL, enable/disable stenciling
	D3DRENDERSTATE_STENCILFAIL        = 53,
	D3DRENDERSTATE_STENCILZFAIL       = 54,
	D3DRENDERSTATE_STENCILPASS        = 55,
	D3DRENDERSTATE_STENCILFUNC        = 56, // D3DCMPFUNC, Stencil Test passes if ((ref & mask) stencilfn (stencil & mask)) is true
	D3DRENDERSTATE_STENCILREF         = 57,
	D3DRENDERSTATE_STENCILMASK        = 58,
	D3DRENDERSTATE_STENCILWRITEMASK   = 59,
	D3DRENDERSTATE_TEXTUREFACTOR      = 60, // DWORD (D3DCOLOR), used for multi-texture blend

	// Direct3D version 6
	D3DRENDERSTATE_WRAP0              = 128,
	D3DRENDERSTATE_WRAP1              = 129,
	D3DRENDERSTATE_WRAP2              = 130,
	D3DRENDERSTATE_WRAP3              = 131,
	D3DRENDERSTATE_WRAP4              = 132,
	D3DRENDERSTATE_WRAP5              = 133,
	D3DRENDERSTATE_WRAP6              = 134,
	D3DRENDERSTATE_WRAP7              = 135,

	D3DRENDERSTATE_CLIPPING            = 136,
	D3DRENDERSTATE_LIGHTING            = 137,
    D3DRENDERSTATE_EXTENTS             = 138,
    D3DRENDERSTATE_AMBIENT             = 139,
    D3DRENDERSTATE_FOGVERTEXMODE       = 140,
    D3DRENDERSTATE_COLORVERTEX         = 141,
    D3DRENDERSTATE_LOCALVIEWER         = 142,
    D3DRENDERSTATE_NORMALIZENORMALS    = 143,
    D3DRENDERSTATE_COLORKEYBLENDENABLE = 144,
    D3DRENDERSTATE_DIFFUSEMATERIALSOURCE    = 145,
    D3DRENDERSTATE_SPECULARMATERIALSOURCE   = 146,
    D3DRENDERSTATE_AMBIENTMATERIALSOURCE    = 147,
    D3DRENDERSTATE_EMISSIVEMATERIALSOURCE   = 148,
    D3DRENDERSTATE_VERTEXBLEND              = 151,
    D3DRENDERSTATE_CLIPPLANEENABLE          = 152,

	//
	// retired renderstates - not supported for DX7 interfaces
	//
    D3DRENDERSTATE_TEXTUREHANDLE      = 1, // Texture handle for legacy interfaces (Texture;Texture2)
    D3DRENDERSTATE_TEXTUREADDRESS     = 3, // D3DTEXTUREADDRESS
	D3DRENDERSTATE_WRAPU              = 5, // TRUE for wrapping in u
	D3DRENDERSTATE_WRAPV              = 6, // TRUE for wrapping in v
	D3DRENDERSTATE_MONOENABLE         = 11, // TRUE to enable mono rasterization
	D3DRENDERSTATE_ROP2               = 12, // ROP2
	D3DRENDERSTATE_PLANEMASK          = 13, // DWORD physical plane mask
	D3DRENDERSTATE_TEXTUREMAG         = 17, // D3DTEXTUREFILTER
	D3DRENDERSTATE_TEXTUREMIN         = 18, // D3DTEXTUREFILTER
	D3DRENDERSTATE_TEXTUREMAPBLEND    = 21, // D3DTEXTUREBLEND
	D3DRENDERSTATE_SUBPIXEL           = 31, // TRUE to enable subpixel correction
	D3DRENDERSTATE_SUBPIXELX          = 32, // TRUE to enable correction in X only
	D3DRENDERSTATE_STIPPLEENABLE      = 39, // TRUE to enable stippling
	D3DRENDERSTATE_BORDERCOLOR        = 43, // Border color for texturing w/border
	D3DRENDERSTATE_TEXTUREADDRESSU    = 44, // Texture addressing mode for U coordinate
	D3DRENDERSTATE_TEXTUREADDRESSV    = 45, // Texture addressing mode for V coordinate
	D3DRENDERSTATE_MIPMAPLODBIAS      = 46, // D3DVALUE Mipmap LOD bias
	D3DRENDERSTATE_ANISOTROPY         = 49, // Max. anisotropy. 1 = no anisotropy
	// DIRECT3D_VERSION_5
    D3DRENDERSTATE_FLUSHBATCH         = 50, // Explicit flush for DP batching (DX5 Only)
    D3DRENDERSTATE_TRANSLUCENTSORTINDEPENDENT = 51, // BOOL, enable sort-independent transparency

    // DIRECT3D_VERSION_6
    D3DRENDERSTATE_STIPPLEPATTERN00   = 64, // Stipple pattern 01...
    D3DRENDERSTATE_STIPPLEPATTERN01   = 65,
    D3DRENDERSTATE_STIPPLEPATTERN02   = 66,
    D3DRENDERSTATE_STIPPLEPATTERN03   = 67,
    D3DRENDERSTATE_STIPPLEPATTERN04   = 68,
    D3DRENDERSTATE_STIPPLEPATTERN05   = 69,
    D3DRENDERSTATE_STIPPLEPATTERN06   = 70,
    D3DRENDERSTATE_STIPPLEPATTERN07   = 71,
    D3DRENDERSTATE_STIPPLEPATTERN08   = 72,
    D3DRENDERSTATE_STIPPLEPATTERN09   = 73,
    D3DRENDERSTATE_STIPPLEPATTERN10   = 74,
    D3DRENDERSTATE_STIPPLEPATTERN11   = 75,
    D3DRENDERSTATE_STIPPLEPATTERN12   = 76,
    D3DRENDERSTATE_STIPPLEPATTERN13   = 77,
    D3DRENDERSTATE_STIPPLEPATTERN14   = 78,
    D3DRENDERSTATE_STIPPLEPATTERN15   = 79,
    D3DRENDERSTATE_STIPPLEPATTERN16   = 80,
    D3DRENDERSTATE_STIPPLEPATTERN17   = 81,
    D3DRENDERSTATE_STIPPLEPATTERN18   = 82,
    D3DRENDERSTATE_STIPPLEPATTERN19   = 83,
    D3DRENDERSTATE_STIPPLEPATTERN20   = 84,
    D3DRENDERSTATE_STIPPLEPATTERN21   = 85,
    D3DRENDERSTATE_STIPPLEPATTERN22   = 86,
    D3DRENDERSTATE_STIPPLEPATTERN23   = 87,
    D3DRENDERSTATE_STIPPLEPATTERN24   = 88,
    D3DRENDERSTATE_STIPPLEPATTERN25   = 89,
    D3DRENDERSTATE_STIPPLEPATTERN26   = 90,
    D3DRENDERSTATE_STIPPLEPATTERN27   = 91,
    D3DRENDERSTATE_STIPPLEPATTERN28   = 92,
    D3DRENDERSTATE_STIPPLEPATTERN29   = 93,
    D3DRENDERSTATE_STIPPLEPATTERN30   = 94,
    D3DRENDERSTATE_STIPPLEPATTERN31   = 95,
};
enum D3DSHADEMODE : unsigned int
{

};
enum D3DSTATEBLOCKTYPE : unsigned int
{

};
enum D3DSTENCILOP : unsigned int
{

};
enum D3DTEXTUREADDRESS : unsigned int
{
	D3DTADDRESS_INVALID_0 = 0,
	D3DTADDRESS_WRAP      = 1,
	D3DTADDRESS_MIRROR    = 2,
	D3DTADDRESS_CLAMP     = 4,
	D3DTADDRESS_BORDER    = 5,
};
enum D3DTEXTUREMAGFILTER : unsigned int
{

};
enum D3DTEXTUREMINFILTER : unsigned int
{

};
enum D3DTEXTUREMIPFILTER : unsigned int
{

};
enum D3DTEXTUREOP : unsigned int
{

};
enum D3DTEXTURESTAGESTATETYPE : unsigned int
{

};
enum D3DTEXTURETRANSFORMFLAGS : unsigned int
{

};
enum D3DTRANSFORMSTATETYPE : unsigned int
{
	D3DTRANSFORMSTATE_WORLD      = 1,
	D3DTRANSFORMSTATE_VIEW       = 2,
	D3DTRANSFORMSTATE_PROJECTION = 3,
	D3DTRANSFORMSTATE_WORLD1     = 4,
	D3DTRANSFORMSTATE_WORLD2     = 5,
	D3DTRANSFORMSTATE_WORLD3     = 6,
	D3DTRANSFORMSTATE_TEXTURE0   = 16,
	D3DTRANSFORMSTATE_TEXTURE1   = 17,
	D3DTRANSFORMSTATE_TEXTURE2   = 18,
	D3DTRANSFORMSTATE_TEXTURE3   = 19,
	D3DTRANSFORMSTATE_TEXTURE4   = 20,
	D3DTRANSFORMSTATE_TEXTURE5   = 21,
	D3DTRANSFORMSTATE_TEXTURE6   = 22,
	D3DTRANSFORMSTATE_TEXTURE7   = 23,

	// [...]
};
enum D3DVERTEXBLENDFLAGS : unsigned int
{

};
enum D3DVERTEXTYPE : unsigned int
{
	D3DVT_INVALID_0 = 0,
	D3DVT_VERTEX    = 1,
	D3DVT_LVERTEX   = 2,
	D3DVT_TLVERTEX  = 3,
};
enum D3DZBUFFERTYPE : unsigned int
{
	D3DZB_FALSE = 0,
	D3DZB_TRUE  = 1, // Z buffering
	D3DZB_USEW  = 2, // W buffering
};

/*

D3DANTIALIASMODE
D3DBLEND
D3DCMPFUNC
D3DCULL
D3DFILLMODE
D3DFOGMODE
D3DLIGHTTYPE
D3DMATERIALCOLORSOURCE
D3DPRIMITIVETYPE
D3DRENDERSTATETYPE
D3DSHADEMODE
D3DSTATEBLOCKTYPE
D3DSTENCILOP
D3DTEXTUREADDRESS
D3DTEXTUREMAGFILTER
D3DTEXTUREMINFILTER
D3DTEXTUREMIPFILTER
D3DTEXTUREOP
D3DTEXTURESTAGESTATETYPE
D3DTEXTURETRANSFORMFLAGS
D3DTRANSFORMSTATETYPE
D3DVERTEXBLENDFLAGS
D3DVERTEXTYPE
D3DZBUFFERTYPE

type  
  PD3DRenderStateType = ^TD3DRenderStateType;
  TD3DRenderStateType = DWORD;

const
  D3DRENDERSTATE_ANTIALIAS          = 2;    (* D3DANTIALIASMODE *)
  {$EXTERNALSYM D3DRENDERSTATE_ANTIALIAS}
  D3DRENDERSTATE_TEXTUREPERSPECTIVE = 4;    (* TRUE for perspective correction *)
  {$EXTERNALSYM D3DRENDERSTATE_TEXTUREPERSPECTIVE}
  D3DRENDERSTATE_ZENABLE            = 7;    (* D3DZBUFFERTYPE (or TRUE/FALSE for legacy) *)
  {$EXTERNALSYM D3DRENDERSTATE_ZENABLE}
  D3DRENDERSTATE_FILLMODE           = 8;    (* D3DFILL_MODE        *)
  {$EXTERNALSYM D3DRENDERSTATE_FILLMODE}
  D3DRENDERSTATE_SHADEMODE          = 9;    (* D3DSHADEMODE *)
  {$EXTERNALSYM D3DRENDERSTATE_SHADEMODE}
  D3DRENDERSTATE_LINEPATTERN        = 10;   (* D3DLINEPATTERN *)
  {$EXTERNALSYM D3DRENDERSTATE_LINEPATTERN}
  D3DRENDERSTATE_ZWRITEENABLE       = 14;   (* TRUE to enable z writes *)
  {$EXTERNALSYM D3DRENDERSTATE_ZWRITEENABLE}
  D3DRENDERSTATE_ALPHATESTENABLE    = 15;   (* TRUE to enable alpha tests *)
  {$EXTERNALSYM D3DRENDERSTATE_ALPHATESTENABLE}
  D3DRENDERSTATE_LASTPIXEL          = 16;   (* TRUE for last-pixel on lines *)
  {$EXTERNALSYM D3DRENDERSTATE_LASTPIXEL}
  D3DRENDERSTATE_SRCBLEND           = 19;   (* D3DBLEND *)
  {$EXTERNALSYM D3DRENDERSTATE_SRCBLEND}
  D3DRENDERSTATE_DESTBLEND          = 20;   (* D3DBLEND *)
  {$EXTERNALSYM D3DRENDERSTATE_DESTBLEND}
  D3DRENDERSTATE_CULLMODE           = 22;   (* D3DCULL *)
  {$EXTERNALSYM D3DRENDERSTATE_CULLMODE}
  D3DRENDERSTATE_ZFUNC              = 23;   (* D3DCMPFUNC *)
  {$EXTERNALSYM D3DRENDERSTATE_ZFUNC}
  D3DRENDERSTATE_ALPHAREF           = 24;   (* D3DFIXED *)
  {$EXTERNALSYM D3DRENDERSTATE_ALPHAREF}
  D3DRENDERSTATE_ALPHAFUNC          = 25;   (* D3DCMPFUNC *)
  {$EXTERNALSYM D3DRENDERSTATE_ALPHAFUNC}
  D3DRENDERSTATE_DITHERENABLE       = 26;   (* TRUE to enable dithering *)
  {$EXTERNALSYM D3DRENDERSTATE_DITHERENABLE}
  D3DRENDERSTATE_ALPHABLENDENABLE   = 27;   (* TRUE to enable alpha blending *)
  {$EXTERNALSYM D3DRENDERSTATE_ALPHABLENDENABLE}
 // DIRECT3D_VERSION_5
  D3DRENDERSTATE_FOGENABLE          = 28;   (* TRUE to enable fog blending *)
  {$EXTERNALSYM D3DRENDERSTATE_FOGENABLE}
  D3DRENDERSTATE_SPECULARENABLE     = 29;   (* TRUE to enable specular *)
  {$EXTERNALSYM D3DRENDERSTATE_SPECULARENABLE}
  D3DRENDERSTATE_ZVISIBLE           = 30;   (* TRUE to enable z checking *)
  {$EXTERNALSYM D3DRENDERSTATE_ZVISIBLE}
  D3DRENDERSTATE_STIPPLEDALPHA      = 33;   (* TRUE to enable stippled alpha (RGB device only) *)
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEDALPHA}
  D3DRENDERSTATE_FOGCOLOR           = 34;   (* D3DCOLOR *)
  {$EXTERNALSYM D3DRENDERSTATE_FOGCOLOR}
  D3DRENDERSTATE_FOGTABLEMODE       = 35;   (* D3DFOGMODE *)
  {$EXTERNALSYM D3DRENDERSTATE_FOGTABLEMODE}
  D3DRENDERSTATE_FOGSTART           = 36;   (* Fog start (for both vertex and pixel fog) *)
  {$EXTERNALSYM D3DRENDERSTATE_FOGSTART}
  D3DRENDERSTATE_FOGEND             = 37;   (* Fog end      *)
  {$EXTERNALSYM D3DRENDERSTATE_FOGEND}
  D3DRENDERSTATE_FOGDENSITY         = 38;   (* Fog density  *)
  {$EXTERNALSYM D3DRENDERSTATE_FOGDENSITY}
 // DIRECT3D_VERSION_7
  D3DRENDERSTATE_EDGEANTIALIAS      = 40;   (* TRUE to enable edge antialiasing *)
  {$EXTERNALSYM D3DRENDERSTATE_EDGEANTIALIAS}
  D3DRENDERSTATE_COLORKEYENABLE     = 41;   (* TRUE to enable source colorkeyed textures *)
  {$EXTERNALSYM D3DRENDERSTATE_COLORKEYENABLE}
  D3DRENDERSTATE_ZBIAS              = 47;   (* LONG Z bias *)
  {$EXTERNALSYM D3DRENDERSTATE_ZBIAS}
  D3DRENDERSTATE_RANGEFOGENABLE     = 48;   (* Enables range-based fog *)
  {$EXTERNALSYM D3DRENDERSTATE_RANGEFOGENABLE}
 // DIRECT3D_VERSION_5

  D3DRENDERSTATE_STENCILENABLE      = 52;   (* BOOL enable/disable stenciling *)
  {$EXTERNALSYM D3DRENDERSTATE_STENCILENABLE}
  D3DRENDERSTATE_STENCILFAIL        = 53;   (* D3DSTENCILOP to do if stencil test fails *)
  {$EXTERNALSYM D3DRENDERSTATE_STENCILFAIL}
  D3DRENDERSTATE_STENCILZFAIL       = 54;   (* D3DSTENCILOP to do if stencil test passes and Z test fails *)
  {$EXTERNALSYM D3DRENDERSTATE_STENCILZFAIL}
  D3DRENDERSTATE_STENCILPASS        = 55;   (* D3DSTENCILOP to do if both stencil and Z tests pass *)
  {$EXTERNALSYM D3DRENDERSTATE_STENCILPASS}
  D3DRENDERSTATE_STENCILFUNC        = 56;   (* D3DCMPFUNC fn.  Stencil Test passes if ((ref & mask) stencilfn (stencil & mask)) is true *)
  {$EXTERNALSYM D3DRENDERSTATE_STENCILFUNC}
  D3DRENDERSTATE_STENCILREF         = 57;   (* Reference value used in stencil test *)
  {$EXTERNALSYM D3DRENDERSTATE_STENCILREF}
  D3DRENDERSTATE_STENCILMASK        = 58;   (* Mask value used in stencil test *)
  {$EXTERNALSYM D3DRENDERSTATE_STENCILMASK}
  D3DRENDERSTATE_STENCILWRITEMASK   = 59;   (* Write mask applied to values written to stencil buffer *)
  {$EXTERNALSYM D3DRENDERSTATE_STENCILWRITEMASK}
  D3DRENDERSTATE_TEXTUREFACTOR      = 60;   (* D3DCOLOR used for multi-texture blend *)
  {$EXTERNALSYM D3DRENDERSTATE_TEXTUREFACTOR}
 // DIRECT3D_VERSION_6


  (*
   * 128 values [128; 255] are reserved for texture coordinate wrap flags.
   * These are constructed with the D3DWRAP_U and D3DWRAP_V macros. Using
   * a flags word preserves forward compatibility with texture coordinates
   * that are >2D.
   *)
  D3DRENDERSTATE_WRAP0              = 128;  (* wrap for 1st texture coord. set *)
  {$EXTERNALSYM D3DRENDERSTATE_WRAP0}
  D3DRENDERSTATE_WRAP1              = 129;  (* wrap for 2nd texture coord. set *)
  {$EXTERNALSYM D3DRENDERSTATE_WRAP1}
  D3DRENDERSTATE_WRAP2              = 130;  (* wrap for 3rd texture coord. set *)
  {$EXTERNALSYM D3DRENDERSTATE_WRAP2}
  D3DRENDERSTATE_WRAP3              = 131;  (* wrap for 4th texture coord. set *)
  {$EXTERNALSYM D3DRENDERSTATE_WRAP3}
  D3DRENDERSTATE_WRAP4              = 132;  (* wrap for 5th texture coord. set *)
  {$EXTERNALSYM D3DRENDERSTATE_WRAP4}
  D3DRENDERSTATE_WRAP5              = 133;  (* wrap for 6th texture coord. set *)
  {$EXTERNALSYM D3DRENDERSTATE_WRAP5}
  D3DRENDERSTATE_WRAP6              = 134;  (* wrap for 7th texture coord. set *)
  {$EXTERNALSYM D3DRENDERSTATE_WRAP6}
  D3DRENDERSTATE_WRAP7              = 135;  (* wrap for 8th texture coord. set *)
  {$EXTERNALSYM D3DRENDERSTATE_WRAP7}
 // DIRECT3D_VERSION_6
  D3DRENDERSTATE_CLIPPING            = 136;
  {$EXTERNALSYM D3DRENDERSTATE_CLIPPING}
  D3DRENDERSTATE_LIGHTING            = 137;
  {$EXTERNALSYM D3DRENDERSTATE_LIGHTING}
  D3DRENDERSTATE_EXTENTS             = 138;
  {$EXTERNALSYM D3DRENDERSTATE_EXTENTS}
  D3DRENDERSTATE_AMBIENT             = 139;
  {$EXTERNALSYM D3DRENDERSTATE_AMBIENT}
  D3DRENDERSTATE_FOGVERTEXMODE       = 140;
  {$EXTERNALSYM D3DRENDERSTATE_FOGVERTEXMODE}
  D3DRENDERSTATE_COLORVERTEX         = 141;
  {$EXTERNALSYM D3DRENDERSTATE_COLORVERTEX}
  D3DRENDERSTATE_LOCALVIEWER         = 142;
  {$EXTERNALSYM D3DRENDERSTATE_LOCALVIEWER}
  D3DRENDERSTATE_NORMALIZENORMALS    = 143;
  {$EXTERNALSYM D3DRENDERSTATE_NORMALIZENORMALS}
  D3DRENDERSTATE_COLORKEYBLENDENABLE = 144;
  {$EXTERNALSYM D3DRENDERSTATE_COLORKEYBLENDENABLE}
  D3DRENDERSTATE_DIFFUSEMATERIALSOURCE    = 145;
  {$EXTERNALSYM D3DRENDERSTATE_DIFFUSEMATERIALSOURCE}
  D3DRENDERSTATE_SPECULARMATERIALSOURCE   = 146;
  {$EXTERNALSYM D3DRENDERSTATE_SPECULARMATERIALSOURCE}
  D3DRENDERSTATE_AMBIENTMATERIALSOURCE    = 147;
  {$EXTERNALSYM D3DRENDERSTATE_AMBIENTMATERIALSOURCE}
  D3DRENDERSTATE_EMISSIVEMATERIALSOURCE   = 148;
  {$EXTERNALSYM D3DRENDERSTATE_EMISSIVEMATERIALSOURCE}
  D3DRENDERSTATE_VERTEXBLEND              = 151;
  {$EXTERNALSYM D3DRENDERSTATE_VERTEXBLEND}
  D3DRENDERSTATE_CLIPPLANEENABLE          = 152;
  {$EXTERNALSYM D3DRENDERSTATE_CLIPPLANEENABLE}

 // DIRECT3D_VERSION_7

//
// retired renderstates - not supported for DX7 interfaces
//
  D3DRENDERSTATE_TEXTUREHANDLE      = 1;    (* Texture handle for legacy interfaces (Texture;Texture2) *)
  {$EXTERNALSYM D3DRENDERSTATE_TEXTUREHANDLE}
  D3DRENDERSTATE_TEXTUREADDRESS     = 3;    (* D3DTEXTUREADDRESS  *)
  {$EXTERNALSYM D3DRENDERSTATE_TEXTUREADDRESS}
  D3DRENDERSTATE_WRAPU              = 5;    (* TRUE for wrapping in u *)
  {$EXTERNALSYM D3DRENDERSTATE_WRAPU}
  D3DRENDERSTATE_WRAPV              = 6;    (* TRUE for wrapping in v *)
  {$EXTERNALSYM D3DRENDERSTATE_WRAPV}
  D3DRENDERSTATE_MONOENABLE         = 11;   (* TRUE to enable mono rasterization *)
  {$EXTERNALSYM D3DRENDERSTATE_MONOENABLE}
  D3DRENDERSTATE_ROP2               = 12;   (* ROP2 *)
  {$EXTERNALSYM D3DRENDERSTATE_ROP2}
  D3DRENDERSTATE_PLANEMASK          = 13;   (* DWORD physical plane mask *)
  {$EXTERNALSYM D3DRENDERSTATE_PLANEMASK}
  D3DRENDERSTATE_TEXTUREMAG         = 17;   (* D3DTEXTUREFILTER *)
  {$EXTERNALSYM D3DRENDERSTATE_TEXTUREMAG}
  D3DRENDERSTATE_TEXTUREMIN         = 18;   (* D3DTEXTUREFILTER *)
  {$EXTERNALSYM D3DRENDERSTATE_TEXTUREMIN}
  D3DRENDERSTATE_TEXTUREMAPBLEND    = 21;   (* D3DTEXTUREBLEND *)
  {$EXTERNALSYM D3DRENDERSTATE_TEXTUREMAPBLEND}
  D3DRENDERSTATE_SUBPIXEL           = 31;   (* TRUE to enable subpixel correction *)
  {$EXTERNALSYM D3DRENDERSTATE_SUBPIXEL}
  D3DRENDERSTATE_SUBPIXELX          = 32;   (* TRUE to enable correction in X only *)
  {$EXTERNALSYM D3DRENDERSTATE_SUBPIXELX}
  D3DRENDERSTATE_STIPPLEENABLE      = 39;   (* TRUE to enable stippling *)
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEENABLE}
  D3DRENDERSTATE_BORDERCOLOR        = 43;   (* Border color for texturing w/border *)
  {$EXTERNALSYM D3DRENDERSTATE_BORDERCOLOR}
  D3DRENDERSTATE_TEXTUREADDRESSU    = 44;   (* Texture addressing mode for U coordinate *)
  {$EXTERNALSYM D3DRENDERSTATE_TEXTUREADDRESSU}
  D3DRENDERSTATE_TEXTUREADDRESSV    = 45;   (* Texture addressing mode for V coordinate *)
  {$EXTERNALSYM D3DRENDERSTATE_TEXTUREADDRESSV}
  D3DRENDERSTATE_MIPMAPLODBIAS      = 46;   (* D3DVALUE Mipmap LOD bias *)
  {$EXTERNALSYM D3DRENDERSTATE_MIPMAPLODBIAS}
  D3DRENDERSTATE_ANISOTROPY         = 49;   (* Max. anisotropy. 1 = no anisotropy *)
  {$EXTERNALSYM D3DRENDERSTATE_ANISOTROPY}
 // DIRECT3D_VERSION_5
  D3DRENDERSTATE_FLUSHBATCH         = 50;   (* Explicit flush for DP batching (DX5 Only) *)
  {$EXTERNALSYM D3DRENDERSTATE_FLUSHBATCH}
  D3DRENDERSTATE_TRANSLUCENTSORTINDEPENDENT=51; (* BOOL enable sort-independent transparency *)
  {$EXTERNALSYM D3DRENDERSTATE_TRANSLUCENTSORTINDEPENDENT}
 // DIRECT3D_VERSION_6
  D3DRENDERSTATE_STIPPLEPATTERN00   = 64;   (* Stipple pattern 01...  *)
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN00}
  D3DRENDERSTATE_STIPPLEPATTERN01   = 65;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN01}
  D3DRENDERSTATE_STIPPLEPATTERN02   = 66;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN02}
  D3DRENDERSTATE_STIPPLEPATTERN03   = 67;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN03}
  D3DRENDERSTATE_STIPPLEPATTERN04   = 68;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN04}
  D3DRENDERSTATE_STIPPLEPATTERN05   = 69;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN05}
  D3DRENDERSTATE_STIPPLEPATTERN06   = 70;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN06}
  D3DRENDERSTATE_STIPPLEPATTERN07   = 71;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN07}
  D3DRENDERSTATE_STIPPLEPATTERN08   = 72;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN08}
  D3DRENDERSTATE_STIPPLEPATTERN09   = 73;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN09}
  D3DRENDERSTATE_STIPPLEPATTERN10   = 74;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN10}
  D3DRENDERSTATE_STIPPLEPATTERN11   = 75;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN11}
  D3DRENDERSTATE_STIPPLEPATTERN12   = 76;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN12}
  D3DRENDERSTATE_STIPPLEPATTERN13   = 77;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN13}
  D3DRENDERSTATE_STIPPLEPATTERN14   = 78;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN14}
  D3DRENDERSTATE_STIPPLEPATTERN15   = 79;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN15}
  D3DRENDERSTATE_STIPPLEPATTERN16   = 80;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN16}
  D3DRENDERSTATE_STIPPLEPATTERN17   = 81;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN17}
  D3DRENDERSTATE_STIPPLEPATTERN18   = 82;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN18}
  D3DRENDERSTATE_STIPPLEPATTERN19   = 83;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN19}
  D3DRENDERSTATE_STIPPLEPATTERN20   = 84;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN20}
  D3DRENDERSTATE_STIPPLEPATTERN21   = 85;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN21}
  D3DRENDERSTATE_STIPPLEPATTERN22   = 86;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN22}
  D3DRENDERSTATE_STIPPLEPATTERN23   = 87;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN23}
  D3DRENDERSTATE_STIPPLEPATTERN24   = 88;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN24}
  D3DRENDERSTATE_STIPPLEPATTERN25   = 89;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN25}
  D3DRENDERSTATE_STIPPLEPATTERN26   = 90;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN26}
  D3DRENDERSTATE_STIPPLEPATTERN27   = 91;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN27}
  D3DRENDERSTATE_STIPPLEPATTERN28   = 92;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN28}
  D3DRENDERSTATE_STIPPLEPATTERN29   = 93;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN29}
  D3DRENDERSTATE_STIPPLEPATTERN30   = 94;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN30}
  D3DRENDERSTATE_STIPPLEPATTERN31   = 95;
  {$EXTERNALSYM D3DRENDERSTATE_STIPPLEPATTERN31}

//
// retired renderstate names - the values are still used under new naming conventions
//
  D3DRENDERSTATE_FOGTABLESTART      = 36;   (* Fog table start    *)
  {$EXTERNALSYM D3DRENDERSTATE_FOGTABLESTART}
  D3DRENDERSTATE_FOGTABLEEND        = 37;   (* Fog table end      *)
  {$EXTERNALSYM D3DRENDERSTATE_FOGTABLEEND}
  D3DRENDERSTATE_FOGTABLEDENSITY    = 38;   (* Fog table density  *)
  {$EXTERNALSYM D3DRENDERSTATE_FOGTABLEDENSITY}
*/
#pragma endregion

#endif


#undef DEFINE_GUID
#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        EXTERN_C const GUID DECLSPEC_SELECTANY name \
                = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

//#define INITGUID
DEFINE_GUID(IID_IDirect3DRM, 0x2bc49361, 0x8327, 0x11cf, 0xac, 0x4a, 0x0, 0x0, 0xc0, 0x38, 0x25, 0xa1);
DEFINE_GUID(IID_IDirect3DRM2, 0x4516ecc8, 0x8f20, 0x11d0, 0x9b, 0x6d, 0x00, 0x00, 0xc0, 0x78, 0x1b, 0xc3);
DEFINE_GUID(IID_IDirect3DRM3, 0x4516ec83, 0x8f20, 0x11d0, 0x9b, 0x6d, 0x00, 0x00, 0xc0, 0x78, 0x1b, 0xc3);

// <LegoRR.exe @0047c8d0>
BOOL __cdecl lego::draw::StartScreenMode(BOOL isFullScreen, DriverMode* driver, DeviceMode* device, ScreenMode* screen, int x, int y, int screenWidth, int screenHeight)
{
	DDSURFACEDESC2 surf = { 0 }; // dummy init

	DWORD dwBPP = 16; // 32;
	debugf("DRIVER: %p\nDEVICE: %p\nSCREEN: %p\n", driver, device, screen);
	if (driver && !(driver->flags && DRIVERMODE_ISUSED))
		driver = nullptr;

	if (screen) {
		if (!(screen->flags && SCREENMODE_ISUSED))
			screen = nullptr;
		if (screen) {
			screenWidth = screen->screenWidth;
			screenHeight = screen->screenHeight;
			dwBPP = screen->bitDepth;
		}
	}
	//const char* name1 = (driver ? &driver->displayName[0] : "");
	//if (driver) { OutputDebugStringA(driver->displayName); OutputDebugStringA("\n"); }
	//debugf("DRIVER: %s\n", name1);
	debugf("DRIVER: %s\nDEVICE: %s\nSCREEN: %s\nBPP: %i\n",
		(driver ? driver->displayName : ""), (device ? device->displayName : ""),
		(screen ? screen->displayName : ""), (int)(screen ? (int)screen->bitDepth : (int)dwBPP));


	globals::g_ScreenIsFullScreen = isFullScreen;
	LPGUID lpGuid = ((!driver || (driver->flags & DRIVERMODE_NOGUID_10) /*0x10*/) ? nullptr : &driver->guid);
	//debugf("GUID: %p\n", lpGuid);

	globals::g_ScreenSize.width  = screenWidth;
	globals::g_ScreenSize.height = screenHeight;
	main::ShowGameWindow(isFullScreen, x, y, screenWidth, screenHeight);

	IDirectDraw* ddraw1 = nullptr; // dummy init
	if (DirectDrawCreate(lpGuid, &ddraw1, nullptr) == 0) {
		//IDirectDraw4* directDraw; // uuid("9c59509a-39bd-11d1-8c4a-00c04fd930c5")
		if (ddraw1->QueryInterface(/*globals::*/IID_IDirectDraw4, (LPVOID*)&globals::g_IDirectDraw4) == 0) {

			DWORD dwFlags = (isFullScreen ? (DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN /*0x11*/) : (DDSCL_NORMAL /*0x8*/));
			if (globals::g_IDirectDraw4->SetCooperativeLevel(globals::g_DirectDraw_hWnd, dwFlags) == 0) {
				//HRESULT result;
				if (!isFullScreen || globals::g_IDirectDraw4->SetDisplayMode(screenWidth, screenHeight, dwBPP, 0, 0) == 0) {
					std::memset(&surf, 0, sizeof(surf));
					surf.dwSize = sizeof(surf);
					surf.dwFlags = DDSD_CAPS /*0x1*/;
					surf.ddsCaps.dwCaps = DDSCAPS_3DDEVICE | DDSCAPS_PRIMARYSURFACE /*0x2200*/;
					if (isFullScreen) {
						surf.dwFlags |= DDSD_BACKBUFFERCOUNT /*0x20*/;
						surf.dwBackBufferCount = 1;
						surf.ddsCaps.dwCaps |= DDSCAPS_FLIP | DDSCAPS_COMPLEX /*0x18*/;
					}
					if (globals::g_IDirectDraw4->CreateSurface(&surf, &globals::g_IDirectDrawSurface4_RenderTarget, nullptr) == 0) {
						HRESULT result;
						if (!isFullScreen) {
							surf.ddsCaps.dwCaps &= ~DDSCAPS_PRIMARYSURFACE /*~0x200 0xfffffdff*/;
							surf.ddsCaps.dwCaps |= DDSCAPS_OFFSCREENPLAIN /*0x40*/;
							surf.dwFlags |= DDSD_WIDTH | DDSD_HEIGHT /*0x6*/;
							surf.dwWidth  = screenWidth;
							surf.dwHeight = screenHeight;
							result = globals::g_IDirectDraw4->CreateSurface(&surf, &globals::g_IDirectDrawSurface4_DrawTarget, nullptr);
						}
						else {
							DDSCAPS2 ddsCaps = { 0 }; // dummy init
							std::memset(&ddsCaps, 0, sizeof(ddsCaps));
							ddsCaps.dwCaps = DDSCAPS_BACKBUFFER /*0x4*/;
							result = globals::g_IDirectDrawSurface4_RenderTarget->GetAttachedSurface(&ddsCaps, &globals::g_IDirectDrawSurface4_DrawTarget);
						}
						if (result == 0) {

							if (InitClipperRegion(isFullScreen, screenWidth, screenHeight) &&
								main::InitDirect3DRM(device, ddraw1, globals::g_IDirectDrawSurface4_DrawTarget, isFullScreen))
							{
								if (!isFullScreen || SHOWCURSOR)
									ShowCursor(SHOWCURSOR /*FALSE*/);
								return TRUE;
							}
							debugf("FAILED: Main_CreateRectRgn\n");
							globals::g_IDirectDrawSurface4_DrawTarget->Release();
							globals::g_IDirectDrawSurface4_DrawTarget = nullptr;
						}
						debugf("FAILED: g_IDirectDrawSurface4_DrawTarget\n");
						globals::g_IDirectDrawSurface4_RenderTarget->Release();
						globals::g_IDirectDrawSurface4_RenderTarget = nullptr;

					}
					debugf("FAILED: g_IDirectDrawSurface4_RenderTarget\n");
				}
				debugf("FAILED: SetCooperativeLevel\n");
			}
			debugf("FAILED: SetDisplayMode\n");
			globals::g_IDirectDraw4->Release();
			globals::g_IDirectDraw4 = nullptr;
		}
		debugf("FAILED: QueryInterface\n");
		ddraw1->Release();
	}
	debugf("FAILED: DirectDrawCreate\n");
	return FALSE;
}


// <LegoRR.exe @0047cb90>
void __cdecl lego::draw::Render(void)
{
	if (globals::g_ScreenIsFullScreen) {
		globals::g_IDirectDrawSurface4_RenderTarget->Flip(nullptr, DDFLIP_WAIT /*0x1*/);
	}
	else {
		RenderWindowed();
	}
}

// <LegoRR.exe @0047cee0>
void __cdecl lego::draw::CopyToDrawTarget(void)
{
	if (globals::g_ScreenIsFullScreen) {
		globals::g_IDirectDrawSurface4_DrawTarget->Blt(nullptr, globals::g_IDirectDrawSurface4_RenderTarget,
													   nullptr, DDBLT_WAIT /*0x1000000*/, nullptr);
	}
}

// <LegoRR.exe @0047cf10>
void __cdecl lego::draw::RenderWindowed(void)
{
	POINT ptClient = { 0, 0 };
	RECT dstRect = { 0, 0, globals::g_ScreenSize.width, globals::g_ScreenSize.height };
	RECT srcRect = { 0, 0, globals::g_ScreenSize.width, globals::g_ScreenSize.height };

	ClientToScreen(globals::g_DirectDraw_hWnd, &ptClient);
	OffsetRect(&dstRect, ptClient.x, ptClient.y);

	globals::g_IDirectDrawSurface4_RenderTarget->Blt(&dstRect, globals::g_IDirectDrawSurface4_DrawTarget,
													 &srcRect, DDBLT_WAIT /*0x1000000*/, nullptr);
}

// <LegoRR.exe @0047cfb0>
void __cdecl lego::draw::CleanupDirectDraw(void)
{
	if (globals::g_IDirectDrawSurface4_RenderTarget)
		globals::g_IDirectDrawSurface4_RenderTarget->Release();
	if (globals::g_IDirectDrawClipper_RenderTarget)
		globals::g_IDirectDrawClipper_RenderTarget->Release();

	// (this actually is not present)
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

// Input ref_textureUsage is in units of pixels, output is in units of bytes
// <LegoRR.exe @0047d010>
void __cdecl lego::draw::CalculateTextureUsage(unsigned int* ref_textureUsage)
{
	/*typedef enum CONST_D3DRMFPTFFLAGS {
		D3DRMFPTF_ALPHA = 0x00000001,
		D3DRMFPTF_NOALPHA = 0x00000002,
		D3DRMFPTF_PALETTIZED = 0x00000004,
		D3DRMFPTF_NOTPALETTIZED = 0x00000008
	} D3DRMFPTFFLAGS;*/
	DDPIXELFORMAT pixFmt = { 0 }; // dummy init

	// first make sure we're not in 8-bit paletted mode?
	std::memset(&pixFmt, 0, sizeof(DDPIXELFORMAT));
	pixFmt.dwSize = sizeof(DDPIXELFORMAT) /*0x20*/;
	if (main::globals::g_IDirect3DRMDevice3->FindPreferredTextureFormat(DDBD_8 /*0x800*/, D3DRMFPTF_PALETTIZED /*0x4*/, &pixFmt) != 0) {

		// confirm we are in 16 bit mode than multiply by number of bytes per pixel (rounded down)
		std::memset(&pixFmt, 0, sizeof(DDPIXELFORMAT));
		pixFmt.dwSize = sizeof(DDPIXELFORMAT) /*0x20*/;
		if (main::globals::g_IDirect3DRMDevice3->FindPreferredTextureFormat(DDBD_16 /*0x400*/, 0, &pixFmt) == 0) {
			*ref_textureUsage *= (pixFmt.dwRGBBitCount / 8);
			//*(unsigned int*)pixFmt.dwGBitMask = (unaff_EDI >> 3) * *(int*)pixFmt.dwGBitMask;
		}
	}
}

// <LegoRR.exe @0047d090>
BOOL __cdecl lego::draw::GetAvailableVideoMemory(unsigned int* out_totalMem, unsigned int* out_freeMem)
{
	DDSCAPS2 ddsCaps = { 0 }; // dummy init
	ddsCaps.dwCaps = DDSCAPS_TEXTURE /*0x1000*/;
	ddsCaps.dwCaps2 = 0;
	ddsCaps.dwCaps3 = 0;
	ddsCaps.dwCaps4 = 0;

	*out_totalMem = 0;
	*out_freeMem = 0;
	return (globals::g_IDirectDraw4->GetAvailableVidMem(&ddsCaps, (LPDWORD)out_totalMem, (LPDWORD)out_freeMem) == 0);
}

// <LegoRR.exe @0047d0e0>
HRESULT __cdecl lego::draw::FillSurface(const Rect2F* rect, unsigned int rgbColor)
{
	DDBLTFX ddBlt = { 0 }; // dummy init
	std::memset(&ddBlt, 0, sizeof(ddBlt));
	ddBlt.dwSize = sizeof(ddBlt);
	ddBlt.dwFillColor = lego::image::packNativeRGB(globals::g_IDirectDrawSurface4_DrawTarget, rgbColor);

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
static BOOL __cdecl lego::draw::InitClipperRegion(BOOL isFullScreen, int screenWidth, int screenHeight)
{
	if (globals::g_IDirectDraw4->CreateClipper(0, &globals::g_IDirectDrawClipper_DrawTarget, nullptr) == 0) {
		HRGN hrgn = CreateRectRgn(0, 0, screenWidth, screenHeight);
		DWORD length = GetRegionData(hrgn, 0, nullptr);
		LPRGNDATA lpRgnData = (LPRGNDATA)std::malloc(length);
		GetRegionData(hrgn, length, lpRgnData);
		if (globals::g_IDirectDrawClipper_DrawTarget->SetClipList(lpRgnData, 0) == 0) {
			std::free(lpRgnData);
			if (globals::g_IDirectDrawSurface4_DrawTarget->SetClipper(globals::g_IDirectDrawClipper_DrawTarget) == 0) {
				if (isFullScreen) {
					return TRUE;
				}
				if (globals::g_IDirectDraw4->CreateClipper(0, &globals::g_IDirectDrawClipper_RenderTarget, nullptr) == 0) {
					if (globals::g_IDirectDrawClipper_RenderTarget->SetHWnd(0, globals::g_DirectDraw_hWnd) == 0) {
						if (globals::g_IDirectDrawSurface4_RenderTarget->SetClipper(globals::g_IDirectDrawClipper_RenderTarget) == 0) {
							return TRUE;
						}
						debugf("FAILED: SetClipper RenderTarget\n");
					}
					debugf("FAILED: SetHWnd\n");
				}
				debugf("FAILED: CreateClipper RenderTarget\n");
			}
			debugf("FAILED: SetClipper DrawTarget\n");
			globals::g_IDirectDrawSurface4_DrawTarget->Release();
			globals::g_IDirectDrawSurface4_DrawTarget = nullptr;
		}
		debugf("FAILED: SetClipList DrawTarget\n");
		std::free(lpRgnData);
	}
	debugf("FAILED: CreateClipper DrawTarget\n");
	return FALSE;
}

#pragma endregion
