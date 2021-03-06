// DirectDraw.h :
//
/// STATUS: [Usable, but still being refactored]

#pragma once

#include "Common.h"


#pragma region Flags
namespace lego {

/// PUBLIC:
enum DriverModeFlags : unsigned int
{
	DRIVERMODE_NONE      = 0,

	DRIVERMODE_ISUSED    = 0x1, // this table item is valid
	DRIVERMODE_NOGUID_10 = 0x10,
	DRIVERMODE_NOGUID_20 = 0x20,
};
DEFINE_ENUM_FLAG_OPERATORS(DriverModeFlags)
static_assert(sizeof(DriverModeFlags) == 0x4, "");

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
static_assert(sizeof(DeviceModeFlags) == 0x4, "");

enum ScreenModeFlags : unsigned int
{
	SCREENMODE_NONE      = 0,

	SCREENMODE_ISUSED    = 0x1, // this table item is valid
};
DEFINE_ENUM_FLAG_OPERATORS(ScreenModeFlags)
static_assert(sizeof(ScreenModeFlags) == 0x4, "");

} /* namespace lego */
#pragma endregion


#pragma pack(push, 1)

#pragma region Types
namespace lego {

/// PUBLIC:
struct DriverMode
{
	/*000,10*/  GUID guid;
	/*010,100*/ char displayName[256];
	/*110,4*/   DriverModeFlags flags;
	/*114*/
};
static_assert(sizeof(DriverMode) == 0x114, "");

struct DeviceMode
{
	/*000,10*/  GUID guid;
	/*010,100*/ char displayName[256];
	/*110,4*/   DeviceModeFlags flags;
	/*114*/
};
static_assert(sizeof(DeviceMode) == 0x114, "");

struct ScreenMode
{
	/*000,4*/   int screenWidth;
	/*004,4*/   int screenHeight;
	/*008,4*/   int bitDepth;
	/*00c,100*/ char displayName[256];
	/*10c,4*/   ScreenModeFlags flags;
	/*110*/
};
static_assert(sizeof(ScreenMode) == 0x110, "");

} /* namespace lego */
#pragma endregion

#pragma pack(pop)


#pragma region Globals
namespace lego::ddraw {

/// PUBLIC:
// <LegoRR.exe @0076bc80 - 0076bcc8>
struct DDrawManager
{
	/// PRIVATE:
	// <LegoRR.exe @0076bc80>
	/*00,4*/ HWND hWnd;

	/// PUBLIC:
	// <LegoRR.exe @0076bc84>
	/*04,4*/ IDirectDraw4* DirectDraw4;

	/// PRIVATE:
	// <LegoRR.exe @0076bc88>
	/*08,4*/ IDirectDrawSurface4* RenderTarget;

	/// PUBLIC:
	// <LegoRR.exe @0076bc8c>
	/*0c,4*/ IDirectDrawSurface4* DrawTarget;

	/// PRIVATE:
	// <LegoRR.exe @0076bc90>
	/*10,4*/ unsigned int DDraw_unused_0076bc90;
	// <LegoRR.exe @0076bc94>
	/*14,4*/ IDirectDrawClipper* RenderTargetClipper;
	// <LegoRR.exe @0076bc98>
	/*18,4*/ IDirectDrawClipper* DrawTargetClipper;
	// <LegoRR.exe @0076bc9c>
	/*1c,4*/ DriverMode* DriverEnumerate_TABLE;
	// (unused 4-byte gap)
	// <LegoRR.exe @0076bca0>
	/*20,4*/ unsigned int reserved1;
	// <LegoRR.exe @0076bca4>
	/*24,4*/ DeviceMode* DeviceEnumerate_TABLE;
	// (unused 4-byte gap)
	// <LegoRR.exe @0076bca8>
	/*28,4*/ unsigned int reserved2;
	// <LegoRR.exe @0076bcac>
	/*2c,4*/ ScreenMode* ScreenEnumerate_TABLE;
	// <LegoRR.exe @0076bcb0>
	/*30,4*/ int DriverEnumerate_COUNT;
	// <LegoRR.exe @0076bcb4>
	/*34,4*/ int DeviceEnumerate_COUNT;
	// <LegoRR.exe @0076bcb8>
	/*38,4*/ int ScreenEnumerate_COUNT;
	// <LegoRR.exe @0076bcbc>
	/*3c,4*/ BOOL IsFullScreen;
	// <LegoRR.exe @0076bcc0>
	/*40,8*/ Size2I ScreenSize;
	/*48*/
};
static_assert(sizeof(DDrawManager) == 0x48, "");

} /* namespace lego::ddraw */
namespace lego::globals {

/// PUBLIC:
// <LegoRR.exe @0076bc80 - 0076bcc8>
extern lego::ddraw::DDrawManager g_DDraw;

/// PUBLIC:
// <LegoRR.exe @0076bc84>
#define g_IDirectDraw4 g_DDraw.DirectDraw4

/// PUBLIC:
// <LegoRR.exe @0076bc8c>
#define g_IDirectDrawSurface4_DrawTarget g_DDraw.DrawTarget

// // define these because I'm too lazy to deal with linker errors
// //static IID IID_IDirect3D3 = { 0xbb223240, 0xe72b, 0x11d0, 0xa9, 0xb4, 0x00, 0xaa, 0x00, 0xc0, 0x99, 0x3e };
// //static IID IID_IDirectDraw4 = { 0x9c59509a, 0x39bd, 0x11d1, 0x8c, 0x4a, 0x00, 0xc0, 0x4f, 0xd9, 0x30, 0xc5 };

// /// PRIVATE:
// // <LegoRR.exe @0076bc80>
// extern HWND g_DirectDraw_hWnd;

// /// PUBLIC:
// // <LegoRR.exe @0076bc84>
// extern IDirectDraw4* g_IDirectDraw4;

// /// PRIVATE:
// // <LegoRR.exe @0076bc88>
// extern IDirectDrawSurface4* g_IDirectDrawSurface4_RenderTarget;

// /// PUBLIC:
// // <LegoRR.exe @0076bc8c>
// extern IDirectDrawSurface4* g_IDirectDrawSurface4_DrawTarget;

// /// PRIVATE:
// // <LegoRR.exe @0076bc90>
// extern unsigned int g_DirectDraw_UNUSED_0076bc90;
// // <LegoRR.exe @0076bc94>
// extern IDirectDrawClipper* g_IDirectDrawClipper_RenderTarget;
// // <LegoRR.exe @0076bc98>
// extern IDirectDrawClipper* g_IDirectDrawClipper_DrawTarget;
// // <LegoRR.exe @0076bc9c>
// extern DriverMode* g_DirectDrawDriverEnumerate_TABLE;

// // (unused 4-byte gap)

// // <LegoRR.exe @0076bca4>
// extern DeviceMode* g_DirectDrawDeviceEnumerate_TABLE;

// // (unused 4-byte gap)

// // <LegoRR.exe @0076bcac>
// extern ScreenMode* g_DirectDrawScreenEnumerate_TABLE;
// // <LegoRR.exe @0076bcb0>
// extern int g_DirectDrawDriverEnumerate_COUNT;
// // <LegoRR.exe @0076bcb4>
// extern int g_DirectDrawDeviceEnumerate_COUNT;
// // <LegoRR.exe @0076bcb8>
// extern int g_DirectDrawScreenEnumerate_COUNT;
// // <LegoRR.exe @0076bcbc>
// extern BOOL g_ScreenIsFullScreen;
// // <LegoRR.exe @0076bcc0>
// extern Size2I g_ScreenSize;

} /* namespace lego::globals */
#pragma endregion


#pragma region Functions
namespace lego::ddraw {

/// PUBLIC:
// <LegoRR.exe @0047c430>
void __cdecl InitDirectDraw(HWND hWnd);
// <LegoRR.exe @0047c480>
BOOL __cdecl DDraw_PopulateDriverModes(DriverMode* ref_driverModes, int* out_count);

/// PRIVATE:
// <LegoRR.exe @0047c4b0>
BOOL CALLBACK DDraw_EnumerateDriverCallback(LPGUID lpGuid, LPSTR lpDriverName, LPSTR lpDriverDescription, LPVOID lpContext);

/// PUBLIC:
// <LegoRR.exe @0047c5a0>
BOOL __cdecl DDraw_PopulateDeviceModes(const DriverMode* driver, DeviceMode* ref_deviceModes, int* out_count);

/// PRIVATE:
// <LegoRR.exe @0047c640>
HRESULT CALLBACK DDraw_EnumerateDeviceCallback(LPGUID lpGuid, LPSTR lpDeviceDescription, LPSTR lpDeviceName, D3DDEVICEDESC_V1* lpD3DHWDeviceDesc, D3DDEVICEDESC_V1* lpD3DHELDeviceDesc, LPVOID lpContext);

/// PUBLIC:
// <LegoRR.exe @0047c770>
BOOL __cdecl DDraw_PopulateScreenModes(const DriverMode* driver, BOOL isFullScreen, ScreenMode* ref_ScreenModes, int* out_count);

/// PRIVATE:
// <LegoRR.exe @0047c810>
HRESULT CALLBACK DDraw_EnumerateScreenCallback(DDSURFACEDESC2* lpDDSurfaceDesc, LPVOID lpContext);

/// PUBLIC:
// <LegoRR.exe @0047c8d0>
BOOL __cdecl StartScreenMode(BOOL isFullScreen, const DriverMode* driver, const DeviceMode* device, const ScreenMode* screen, int x, int y, int screenWidth, int screenHeight);
// <LegoRR.exe @0047cb90>
void __cdecl DDraw_Render(void);
// <LegoRR.exe @0047cbb0>
BOOL __cdecl DDraw_SaveToFile(IDirectDrawSurface4* ddSurface4, const char* filename);
// <LegoRR.exe @0047cee0>
void __cdecl DDraw_CopyToDrawTarget(void);

/// PRIVATE:
// <LegoRR.exe @0047cf10>
void __cdecl DDraw_RenderWindowed(void);

/// PUBLIC:
// <LegoRR.exe @0047cfb0>
void __cdecl CleanupDirectDraw(void);
// <LegoRR.exe @0047d010>
void __cdecl CalculateTextureUsage(unsigned int* ref_textureUsage);
// <LegoRR.exe @0047d090>
BOOL __cdecl GetAvailableVideoMemory(unsigned int* out_totalMem, unsigned int* out_freeMem);
// <LegoRR.exe @0047d0e0>
HRESULT __cdecl DDraw_FillDrawTarget(const Rect2F* rect, unsigned int rgbColor);

/// PRIVATE:
// <LegoRR.exe @0047d1a0>
BOOL __cdecl DDraw_InitClipperRegion(BOOL isFullScreen, int screenWidth, int screenHeight);

/// PUBLIC:
// <LegoRR.exe @0047d2c0>
void __cdecl DDraw_UnkChangePalette(IDirectDrawSurface4* ddSurface4_a, IDirectDrawSurface4* ddSurface4_b, D3DRMPaletteEntry* palette);
// <LegoRR.exe @0047d590>
unsigned int __cdecl packNativeRGB(IDirectDrawSurface4* ddSurface4, unsigned int rgbColor);

/// PRIVATE:
// <LegoRR.exe @0047d6b0>
int __cdecl countBits2(unsigned int value);

} /* namespace lego::ddraw */
#pragma endregion

