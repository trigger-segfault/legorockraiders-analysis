// DirectDraw.h : 
//

#pragma once

#include "../Common.h"


namespace lego {
namespace draw {

#pragma region Types

enum DriverModeFlags : unsigned int
{
	DRIVERMODE_NONE      = 0,

	DRIVERMODE_ISUSED    = 0x1, // this table item is valid
	DRIVERMODE_NOGUID_10 = 0x10,
	DRIVERMODE_NOGUID_20 = 0x20,
};
DEFINE_ENUM_FLAG_OPERATORS(DriverModeFlags)

enum DeviceModeFlags : unsigned int
{
	DEVICEMODE_NONE                = 0,

	DEVICEMODE_ISUSED              = 0x1, // this table item is valid
	DEVICEMODE_BPP_8               = 0x10, // supports 8-bit color mode
	DEVICEMODE_BPP_16              = 0x20, // supports 16-bit color mode
	DEVICEMODE_BPP_24              = 0x40, // supports 24-bit color mode
	DEVICEMODE_BPP_32              = 0x80, // supports 32-bit color mode
	DEVICEMODE_COLORMODEL_RGB      = 0x1000, // uses RGB color model
	DEVICEMODE_HARDWARE            = 0x2000, // hardware support
	DEVICEMODE_TEXTUREVIDEOMEMORY  = 0x4000,
	DEVICEMODE_TEXTURESYSTEMMEMORY = 0x8000,
};
DEFINE_ENUM_FLAG_OPERATORS(DeviceModeFlags)

enum ScreenModeFlags : unsigned int
{
	SCREENMODE_NONE      = 0,

	SCREENMODE_ISUSED    = 0x1, // this table item is valid
};
DEFINE_ENUM_FLAG_OPERATORS(ScreenModeFlags)

struct DriverMode
{
	/*000,10*/  GUID guid;
	/*010,100*/ char displayName[256];
	/*110,4*/   DriverModeFlags flags;
	/*114*/
};

struct DeviceMode
{
	/*000,10*/  GUID guid;
	/*010,100*/ char displayName[256];
	/*110,4*/   DeviceModeFlags flags;
	/*114*/
};

struct ScreenMode
{
	/*000,4*/   int screenWidth;
	/*004,4*/   int screenHeight;
	/*008,4*/   int bitDepth;
	/*00c,100*/ char displayName[256];
	/*10c,4*/   ScreenModeFlags flags;
	/*110*/
};

typedef void(__cdecl* SetPixelBPPFunction)(int x, int y, unsigned int color);

#pragma endregion


#pragma region Globals

namespace globals {
	// <LegoRR.exe @0076bc80>
	extern HWND g_DirectDraw_hWnd;
	// <LegoRR.exe @0076bc84>
	extern IDirectDraw4* g_IDirectDraw4;
	// <LegoRR.exe @0076bc88>
	extern IDirectDrawSurface4* g_IDirectDrawSurface4_RenderTarget;
	// <LegoRR.exe @0076bc8c>
	extern IDirectDrawSurface4* g_IDirectDrawSurface4_DrawTarget;
	// <LegoRR.exe @0076bc90>
	extern unsigned int g_DirectDraw_UNUSED_0076bc90;
	// <LegoRR.exe @0076bc94>
	extern IDirectDrawClipper* g_IDirectDrawClipper_RenderTarget;
	// <LegoRR.exe @0076bc98>
	extern IDirectDrawClipper* g_IDirectDrawClipper_DrawTarget;

} /* namespace globals */

#pragma endregion


#pragma region Functions

// <LegoRR.exe @00406500>
IDirectDraw4* __cdecl GetDirectDraw(void);

// <LegoRR.exe @00406510>
IDirectDrawSurface4* __cdecl GetDrawingSurface(void);

// <LegoRR.exe @0047c430>
void __cdecl InitDirectDraw(HWND hWnd);

// Unlike other populate methods, this must ONLY be called once.
// There's no extra cleanup like resetting the count.
// <LegoRR.exe @0047c480>
BOOL __cdecl PopulateDriverModes(DriverMode* ref_driverModes, int* out_count);

// <LegoRR.exe @0047c4b0>
BOOL CALLBACK DirectDrawDriverEnumerate_Callback(LPGUID lpGuid, LPSTR lpDriverName, LPSTR lpDriverDescription, LPVOID lpContext);

// <LegoRR.exe @0047c5a0>
BOOL __cdecl PopulateDeviceModes(DriverMode* driverMode, DeviceMode* ref_deviceModes, int* out_count);

// <LegoRR.exe @0047c640>
HRESULT CALLBACK DirectDrawDeviceEnumerate_Callback(LPGUID lpGuid, LPSTR lpDeviceDescription, LPSTR lpDeviceName, LPD3DDEVICEDESC lpD3DHWDeviceDesc, LPD3DDEVICEDESC lpD3DHELDeviceDesc, LPVOID lpContext);

// <LegoRR.exe @0047c770>
BOOL __cdecl PopulateScreenModes(DriverMode* driverMode, BOOL isFullScreen, ScreenMode* ref_ScreenModes, int* out_count);

// <LegoRR.exe @0047c810>
HRESULT CALLBACK DirectDrawScreenEnumerate_Callback(LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext);

// <LegoRR.exe @0047c8d0>
BOOL __cdecl StartScreenMode(BOOL isFullScreen, DriverMode* driver, DeviceMode* device, ScreenMode* screen, int x, int y, int screenWidth, int screenHeight);

// <LegoRR.exe @0047cb90>
void __cdecl Render(void);

// <LegoRR.exe @0047cee0>
void __cdecl CopyToDrawTarget(void);

// <LegoRR.exe @0047cf10>
void __cdecl RenderWindowed(void);

// <LegoRR.exe @0047cfb0>
void __cdecl CleanupDirectDraw(void);

// Input ref_textureUsage is in units of pixels, output is in units of bytes
// <LegoRR.exe @0047d010>
void __cdecl CalculateTextureUsage(unsigned int* ref_textureUsage);

// <LegoRR.exe @0047d090>
BOOL __cdecl GetAvailableVideoMemory(unsigned int* out_totalMem, unsigned int* out_freeMem);

// <LegoRR.exe @0047d0e0>
HRESULT __cdecl FillSurface(const Rect2F* rect, unsigned int rgbColor);

// <LegoRR.exe @0047d1a0>
BOOL __cdecl InitClipperRegion(BOOL isFullScreen, int screenWidth, int screenHeight);

#pragma endregion


} /* namespace draw */
} /* namespace lego */
