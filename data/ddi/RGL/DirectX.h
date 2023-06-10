
#ifndef _RGL_DIRECTX_H_
#define _RGL_DIRECTX_H_

/************************************************************************************************************************
 **** Constants and enumerations available outside the library...
 ************************************************************************************************************************/

#define DIRECTX_DUMPFILEMAGIC				'FDBR'

#define DIRECTX_NAMELENGTH					256

#define DIRECTX_FLAG_FULLSCREEN				0x0001
#define DIRECTX_FLAG_HARDWARE				0x0002
#define DIRECTX_FLAG_INSETUP				0x0004
#define DIRECTX_FLAG_16BIT					0x0008
#define DIRECTX_FLAG_HARDWARETnL			(0x0010|DIRECTX_FLAG_HARDWARE)

#define DIRECTXENUM_FLAG_NOGUID				0x0001

enum DirectXSurfaceType {

	DirectXSurfaceType_Z,
	DirectXSurfaceType_Back,
	DirectXSurfaceType_Front,

	DirectXSurfaceType_Count,
};

/************************************************************************************************************************
 **** Macros for use within the library...
 ************************************************************************************************************************/

#define DirectX_InitStruct(s)				{ memset((s),0,sizeof(*(s)));(s)->dwSize=sizeof(*(s)); }

#ifdef _RGL

/************************************************************************************************************************
 **** Internal structures for within the library...
 ************************************************************************************************************************/

#include <ddraw.h>
#include <d3d.h>

struct DirectXDriverEnum {

	GUID guid;
	UCHAR name[DIRECTX_NAMELENGTH];
	struct DirectXDeviceEnum *deviceList;
	struct DirectXModeEnum *modeList;
	LPDIRECT3D7 lpD3D7;
	ULONG deviceCount, modeCount;
	ULONG flags;
};

struct DirectXDeviceEnum {

	GUID guid;
	UCHAR name[DIRECTX_NAMELENGTH];
	LPDDPIXELFORMAT zBufferFormatList;
	LPDDPIXELFORMAT textureFormatList;
	ULONG zBufferFormatCount, textureFormatCount;
	ULONG flags;
};

struct DirectXModeEnum {

	UCHAR name[DIRECTX_NAMELENGTH];
	UWORD width, height, depth;
	UWORD flags;
};

struct DirectXFreqEntry {

	ULONG colour;
	ULONG count;
};

// Packing off around this structure...

struct DirectXBufferDump {

	enum DirectXBufferDump_Type type;
	AREA2Di shape;
	ULONG pitch;
	LPVOID buffer;
};


#endif // _RGL

/************************************************************************************************************************
 **** Typedefs available outside the library...
 ************************************************************************************************************************/

typedef struct DirectXFreqEntry				*lpDirectXFreqEntry;
typedef struct DirectXBufferDump			*lpDirectXBufferDump;
typedef struct DirectXDriverEnum			*lpDirectXDriverEnum;
typedef struct DirectXDeviceEnum			*lpDirectXDeviceEnum;
typedef struct DirectXModeEnum				*lpDirectXModeEnum;

#ifndef _AUTOPROTOTYPES
// Auto Prototypes
extern unsigned __int64 __stdcall Int64ShllMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern __int64 __stdcall Int64ShraMod32(__int64 Value,unsigned long ShiftCount);
extern unsigned __int64 __stdcall Int64ShrlMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern void *__cdecl GetFiberData(void );
extern void *__cdecl GetCurrentFiber(void );
extern struct IDirectDraw7 *__cdecl DirectX_DirectDraw(void );
extern struct IDirectDrawSurface7 *__cdecl DirectX_FrontSurf(void );
extern struct IDirectDrawSurface7 *__cdecl DirectX_BackSurf(void );
extern struct IDirectDrawSurface7 *__cdecl DirectX_ZSurf(void );
extern struct IDirect3D7 *__cdecl DirectX_Direct3D(void );
extern struct IDirect3DDevice7 *__cdecl DirectX_Device(void );
extern int __cdecl DirectX_FullScreen(void );
extern int __cdecl DirectX_Hardware(void );
extern int __cdecl DirectX_HardwareTnL(void );
extern void __cdecl DirectX_Initialise(void );
static int __stdcall DirectX_EnumerateDriverCallback(struct _GUID *lpGUID,char *lpDriverDescription,char *lpDriverName,void *lpContext,struct HMONITOR__ *hm);
extern long __stdcall DirectX_EnumerateZBufferFormatsCallback(struct _DDPIXELFORMAT *lpDDPixFmt,void *lpContext);
static long __stdcall DirectX_EnumerateDeviceCallback(char *lpDeviceDescription,char *lpDeviceName,struct _D3DDeviceDesc7 *lpD3DDeviceDesc,void *lpContext);
static int __stdcall DirectX_EnumerateModesCallback(struct _DDSURFACEDESC2 *lpDDSurfaceDesc,void *lpContext);
extern long __stdcall DirectX_EnumerateTextureFormatsCallback(struct _DDPIXELFORMAT *lpDDPixFmt,void *lpContext);
extern int __cdecl DirectX_SortTextureListCallback(const void *a,const void *b);
static void __cdecl DirectX_EnumerateTextureFormats(struct DirectXDeviceEnum *deviceEnum,struct IDirect3DDevice7 *device);
extern int __cdecl DirectX_FindTextureFormat(unsigned long depth,struct _DDPIXELFORMAT *texturePixelFormat);
extern void __cdecl DirectX_CloseDown(int exit);
extern unsigned long __cdecl DirectX_GetDriverCount(void );
extern unsigned char *__cdecl DirectX_GetDriverName(unsigned long driverIndex);
extern unsigned long __cdecl DirectX_GetDeviceCount(unsigned long driverIndex);
extern unsigned char *__cdecl DirectX_GetDeviceName(unsigned long driverIndex,unsigned long deviceIndex);
extern unsigned long __cdecl DirectX_GetWidth(void );
extern unsigned long __cdecl DirectX_GetHeight(void );
extern unsigned long __cdecl DirectX_GetDepth(void );
static long __cdecl DirectX_SetupDisplay(struct IDirectDraw7 *directDraw,int fullScreen,unsigned long width,unsigned long height,unsigned long depth);
extern void __cdecl DirectX_RestoreDisplayMode(void );
extern int __cdecl DirectX_Setup(int fullScreen,unsigned long driverIndex,unsigned long deviceIndex,unsigned long modeIndex,int emulationMode);
static long __cdecl DirectX_CreateDirectDraw(struct _GUID *lpGUID,int emulationMode);
static long __cdecl DirectX_CreateFrontSurface(struct IDirectDrawSurface7 **surface ,struct IDirectDraw7 *ddraw,int fullScreen);
static long __cdecl DirectX_CreateBackSurface(struct IDirectDrawSurface7 **surface ,struct IDirectDrawSurface7 *frontSurface,struct IDirectDraw7 *ddraw,int fullScreen,unsigned long width,unsigned long height);
static void __cdecl DirectX_SetupBitCounts(void );
extern void __cdecl DirectX_GetBitCounts(struct _DDPIXELFORMAT *ddpf,unsigned char *aBits,unsigned char *rBits,unsigned char *gBits,unsigned char *bBits);
extern struct _DDPIXELFORMAT *__cdecl DirectX_FindZBufferFormat(struct DirectXDeviceEnum *device,unsigned long preferedDepth);
extern long __cdecl DirectX_CreateZBuffer(struct IDirectDrawSurface7 **surface ,struct IDirectDraw7 *ddraw,struct _DDPIXELFORMAT *zBufferPF,unsigned long width,unsigned long height);
static long __stdcall DirectX_EnumZBufferCallback(struct _DDPIXELFORMAT *lpDDPF,void *data);
static void __cdecl DirectX_RemoveZBuffer(void );
static long __cdecl DirectX_CreateClippers(int fullScreen, unsigned long width, unsigned long height);
extern VOID __cdecl DirectX_EvictTextures(VOID);
extern void __cdecl DirectX_GetAvailableTextureMemory(LPULONG total, LPULONG used, LPULONG free);
extern void __cdecl DirectX_SetFrontRect(void );
extern void __cdecl DirectX_WaitForVerticalBlank(unsigned long count);
extern void __cdecl DirectX_Flip(void );
extern unsigned long __cdecl DirectX_FindWindowedMode(struct HWND__ *hWnd);
extern int __cdecl DirectX_FindMode(unsigned long driverIndex,unsigned long width,unsigned long height,unsigned long depth,unsigned long *mode);
extern unsigned long __cdecl DirectX_ConvertToBufferColour(unsigned long colour);
extern ULONG __cdecl DirectX_ColourMatchPacked(ULONG colour);
extern unsigned long __cdecl DirectX_ColourMatch(REAL r, REAL g, REAL b, REAL a);
extern int __cdecl DirectX_GetRenderSurfaceBitDepth(void );
extern void __cdecl DirectX_ConvertSurface(struct IDirectDrawSurface7 *src,struct IDirectDrawSurface7 *dest);
static void __cdecl DirectX_CopySurfaceData8Bit(struct _DDSURFACEDESC2 *sDesc,struct _DDSURFACEDESC2 *dDesc);
static void __cdecl DirectX_CopySurfaceDataMasked(struct _DDSURFACEDESC2 *sDesc,struct _DDSURFACEDESC2 *dDesc);
static void __cdecl DirectX_GenerateSurfaceFromPalette(struct _DDSURFACEDESC2 *sDesc,struct _DDSURFACEDESC2 *dDesc,struct tagPALETTEENTRY *palette);
static struct IDirectDrawPalette *__cdecl DirectX_GeneratePalettizedSurface(struct _DDSURFACEDESC2 *sDesc,struct _DDSURFACEDESC2 *dDesc,unsigned long colourCount);
extern struct DirectXBufferDump *__cdecl DirectX_DumpBuffer(int type,struct AREA2Di *shape);
extern int __cdecl DirectX_WriteBufferDump(struct DirectXBufferDump *dump,unsigned char *fname);
extern void __cdecl DirectX_FreeBufferDump(struct DirectXBufferDump *dump);
extern int __cdecl DirectX_FindHardwareMode(LPULONG driver, LPULONG device);
extern void __cdecl DirectX_ClearBackBuffer(COLOUR colour);
extern ULONG __cdecl DirectX_GetRefreshRate(VOID);
// Auto Prototypes
#endif // !_AUTOPROTOTYPES

#endif // !_RGL_DIRECTX_H_
