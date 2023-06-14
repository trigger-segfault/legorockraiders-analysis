#pragma once



typedef unsigned char   undefined;

typedef unsigned long long    GUID;
typedef unsigned int    ImageBaseOffset32;
typedef unsigned char    bool;
typedef unsigned char    byte;
typedef unsigned int    dword;
float10
typedef long long    longlong;
typedef unsigned char    uchar;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned long long    ulonglong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined6;
typedef unsigned long long    undefined8;
typedef unsigned short    ushort;
typedef unsigned short    wchar16;
typedef short    wchar_t;
typedef unsigned short    word;
#define unkbyte9   unsigned long long
#define unkbyte10   unsigned long long
#define unkbyte11   unsigned long long
#define unkbyte12   unsigned long long
#define unkbyte13   unsigned long long
#define unkbyte14   unsigned long long
#define unkbyte15   unsigned long long
#define unkbyte16   unsigned long long

#define unkuint9   unsigned long long
#define unkuint10   unsigned long long
#define unkuint11   unsigned long long
#define unkuint12   unsigned long long
#define unkuint13   unsigned long long
#define unkuint14   unsigned long long
#define unkuint15   unsigned long long
#define unkuint16   unsigned long long

#define unkint9   long long
#define unkint10   long long
#define unkint11   long long
#define unkint12   long long
#define unkint13   long long
#define unkint14   long long
#define unkint15   long long
#define unkint16   long long

#define unkfloat1   float
#define unkfloat2   float
#define unkfloat3   float
#define unkfloat5   double
#define unkfloat6   double
#define unkfloat7   double
#define unkfloat9   long double
#define unkfloat11   long double
#define unkfloat12   long double
#define unkfloat13   long double
#define unkfloat14   long double
#define unkfloat15   long double
#define unkfloat16   long double

#define BADSPACEBASE   void
#define code   void

typedef union IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion, *PIMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion;

typedef struct IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct, *PIMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct;

struct IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct {
	dword OffsetToDirectory;
	dword DataIsDirectory;
};

union IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion {
	dword OffsetToData;
	struct IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct;
};

typedef struct TypeDescriptor TypeDescriptor, *PTypeDescriptor;

struct TypeDescriptor {
	dword hash;
	void * spare;
	char[0] name;
};

typedef struct _s_TryBlockMapEntry _s_TryBlockMapEntry, *P_s_TryBlockMapEntry;

typedef struct _s_TryBlockMapEntry TryBlockMapEntry;

typedef int __ehstate_t;

typedef struct _s_HandlerType _s_HandlerType, *P_s_HandlerType;

typedef struct _s_HandlerType HandlerType;

typedef int ptrdiff_t;

struct _s_HandlerType {
	uint adjectives;
	struct TypeDescriptor * pType;
	ptrdiff_t dispCatchObj;
	void * addressOfHandler;
};

struct _s_TryBlockMapEntry {
	__ehstate_t tryLow;
	__ehstate_t tryHigh;
	__ehstate_t catchHigh;
	int nCatches;
	HandlerType * pHandlerArray;
};

typedef struct _s_FuncInfo _s_FuncInfo, *P_s_FuncInfo;

typedef struct _s_UnwindMapEntry _s_UnwindMapEntry, *P_s_UnwindMapEntry;

typedef struct _s_UnwindMapEntry UnwindMapEntry;

struct _s_FuncInfo {
	uint magicNumber_and_bbtFlags;
	__ehstate_t maxState;
	UnwindMapEntry * pUnwindMap;
	uint nTryBlocks;
	TryBlockMapEntry * pTryBlockMap;
	uint nIPMapEntries;
	void * pIPToStateMap;
};

struct _s_UnwindMapEntry {
	__ehstate_t toState;
	void (* action)(void);
};

typedef struct _s_FuncInfo FuncInfo;

typedef struct _OVERLAPPED _OVERLAPPED, *P_OVERLAPPED;

typedef ulong ULONG_PTR;

typedef union _union_518 _union_518, *P_union_518;

typedef void * HANDLE;

typedef struct _struct_519 _struct_519, *P_struct_519;

typedef void * PVOID;

typedef ulong DWORD;

struct _struct_519 {
	DWORD Offset;
	DWORD OffsetHigh;
};

union _union_518 {
	struct _struct_519 s;
	PVOID Pointer;
};

struct _OVERLAPPED {
	ULONG_PTR Internal;
	ULONG_PTR InternalHigh;
	union _union_518 u;
	HANDLE hEvent;
};

typedef struct _SYSTEMTIME _SYSTEMTIME, *P_SYSTEMTIME;

typedef ushort WORD;

struct _SYSTEMTIME {
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
};

typedef struct _TIME_ZONE_INFORMATION _TIME_ZONE_INFORMATION, *P_TIME_ZONE_INFORMATION;

typedef long LONG;

typedef wchar_t WCHAR;

typedef struct _SYSTEMTIME SYSTEMTIME;

struct _TIME_ZONE_INFORMATION {
	LONG Bias;
	WCHAR StandardName[32];
	SYSTEMTIME StandardDate;
	LONG StandardBias;
	WCHAR DaylightName[32];
	SYSTEMTIME DaylightDate;
	LONG DaylightBias;
};

typedef struct _WIN32_FIND_DATAA _WIN32_FIND_DATAA, *P_WIN32_FIND_DATAA;

typedef struct _FILETIME _FILETIME, *P_FILETIME;

typedef struct _FILETIME FILETIME;

typedef char CHAR;

struct _FILETIME {
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;
};

struct _WIN32_FIND_DATAA {
	DWORD dwFileAttributes;
	FILETIME ftCreationTime;
	FILETIME ftLastAccessTime;
	FILETIME ftLastWriteTime;
	DWORD nFileSizeHigh;
	DWORD nFileSizeLow;
	DWORD dwReserved0;
	DWORD dwReserved1;
	CHAR cFileName[260];
	CHAR cAlternateFileName[14];
};

typedef struct _SECURITY_ATTRIBUTES _SECURITY_ATTRIBUTES, *P_SECURITY_ATTRIBUTES;

typedef struct _SECURITY_ATTRIBUTES * LPSECURITY_ATTRIBUTES;

typedef void * LPVOID;

typedef int BOOL;

struct _SECURITY_ATTRIBUTES {
	DWORD nLength;
	LPVOID lpSecurityDescriptor;
	BOOL bInheritHandle;
};

typedef struct _STARTUPINFOA _STARTUPINFOA, *P_STARTUPINFOA;

typedef CHAR * LPSTR;

typedef uchar BYTE;

typedef BYTE * LPBYTE;

struct _STARTUPINFOA {
	DWORD cb;
	LPSTR lpReserved;
	LPSTR lpDesktop;
	LPSTR lpTitle;
	DWORD dwX;
	DWORD dwY;
	DWORD dwXSize;
	DWORD dwYSize;
	DWORD dwXCountChars;
	DWORD dwYCountChars;
	DWORD dwFillAttribute;
	DWORD dwFlags;
	WORD wShowWindow;
	WORD cbReserved2;
	LPBYTE lpReserved2;
	HANDLE hStdInput;
	HANDLE hStdOutput;
	HANDLE hStdError;
};

typedef struct _STARTUPINFOA STARTUPINFOA;

typedef struct _EXCEPTION_POINTERS _EXCEPTION_POINTERS, *P_EXCEPTION_POINTERS;

typedef LONG (* PTOP_LEVEL_EXCEPTION_FILTER)(struct _EXCEPTION_POINTERS *);

typedef PTOP_LEVEL_EXCEPTION_FILTER LPTOP_LEVEL_EXCEPTION_FILTER;

typedef struct _EXCEPTION_RECORD _EXCEPTION_RECORD, *P_EXCEPTION_RECORD;

typedef struct _EXCEPTION_RECORD EXCEPTION_RECORD;

typedef EXCEPTION_RECORD * PEXCEPTION_RECORD;

typedef struct _CONTEXT _CONTEXT, *P_CONTEXT;

typedef struct _CONTEXT CONTEXT;

typedef CONTEXT * PCONTEXT;

typedef struct _FLOATING_SAVE_AREA _FLOATING_SAVE_AREA, *P_FLOATING_SAVE_AREA;

typedef struct _FLOATING_SAVE_AREA FLOATING_SAVE_AREA;

struct _FLOATING_SAVE_AREA {
	DWORD ControlWord;
	DWORD StatusWord;
	DWORD TagWord;
	DWORD ErrorOffset;
	DWORD ErrorSelector;
	DWORD DataOffset;
	DWORD DataSelector;
	BYTE RegisterArea[80];
	DWORD Cr0NpxState;
};

struct _CONTEXT {
	DWORD ContextFlags;
	DWORD Dr0;
	DWORD Dr1;
	DWORD Dr2;
	DWORD Dr3;
	DWORD Dr6;
	DWORD Dr7;
	FLOATING_SAVE_AREA FloatSave;
	DWORD SegGs;
	DWORD SegFs;
	DWORD SegEs;
	DWORD SegDs;
	DWORD Edi;
	DWORD Esi;
	DWORD Ebx;
	DWORD Edx;
	DWORD Ecx;
	DWORD Eax;
	DWORD Ebp;
	DWORD Eip;
	DWORD SegCs;
	DWORD EFlags;
	DWORD Esp;
	DWORD SegSs;
	BYTE ExtendedRegisters[512];
};

struct _EXCEPTION_RECORD {
	DWORD ExceptionCode;
	DWORD ExceptionFlags;
	struct _EXCEPTION_RECORD * ExceptionRecord;
	PVOID ExceptionAddress;
	DWORD NumberParameters;
	ULONG_PTR ExceptionInformation[15];
};

struct _EXCEPTION_POINTERS {
	PEXCEPTION_RECORD ExceptionRecord;
	PCONTEXT ContextRecord;
};

typedef struct _TIME_ZONE_INFORMATION TIME_ZONE_INFORMATION;

typedef struct _TIME_ZONE_INFORMATION * LPTIME_ZONE_INFORMATION;

typedef struct _OVERLAPPED * LPOVERLAPPED;

typedef struct _WIN32_FIND_DATAA * LPWIN32_FIND_DATAA;

typedef struct _STARTUPINFOA * LPSTARTUPINFOA;

typedef struct _SYSTEMTIME * LPSYSTEMTIME;

#define STD_OUTPUT_HANDLE -11

#define INVALID_FILE_ATTRIBUTES -1

#define DRIVE_CDROM 5

#define DRIVE_NO_ROOT_DIR 1

#define STD_ERROR_HANDLE -12

#define STD_INPUT_HANDLE -10

typedef DWORD ULONG;

typedef WCHAR OLECHAR;

typedef OLECHAR * LPOLESTR;

typedef ulong _fsize_t;

typedef struct _finddata32_t _finddata32_t, *P_finddata32_t;

typedef long __time32_t;

struct _finddata32_t {
	uint attrib;
	__time32_t time_create;
	__time32_t time_access;
	__time32_t time_write;
	_fsize_t size;
	char name[260];
};

typedef struct LoaderSection LoaderSection, *PLoaderSection;

struct LoaderSection { // [LegoRR/Loader.c|struct:0xc]
	char * name; // Name of the section files are being loaded from
	uint currentSize; // Current total size of files loaded for this section
	uint totalSize; // Predefined total "expected" size for files to load from this section
};

typedef struct ToolTip ToolTip, *PToolTip;

typedef struct Image Image, *PImage;

typedef enum SFX_ID { // [LegoRR/SFX.c|enum:0x4|type:int] SFXType is different from actual Sample indexes, these are hardcoded values that can easily be looked up by ID
	SFX_Ambient=6,
	SFX_AmbientLoop=7,
	SFX_AmbientMusicLoop=44,
	SFX_BoulderHit=34,
	SFX_Build=18,
	SFX_ButtonPressed=13,
	SFX_CaptainSlide=42,
	SFX_CrystalRecharge=26,
	SFX_Drill=2,
	SFX_DrillFade=3,
	SFX_Drip=5,
	SFX_Dynamite=43,
	SFX_FallIn=40,
	SFX_Floor=33,
	SFX_ID_Invalid=4294967295,
	SFX_ImmovableRock=31,
	SFX_InterfaceSlideOffScreen=22,
	SFX_InterfaceSlideOnScreen=21,
	SFX_Laser=27,
	SFX_LaserHit=28,
	SFX_Lava=38,
	SFX_LazerRecharge=29,
	SFX_MFDeposit=12,
	SFX_MFLift=14,
	SFX_MFThrow=15,
	SFX_MusicLoop=41,
	SFX_NULL=0,
	SFX_NotOkay=20,
	SFX_Okay=19,
	SFX_PanelSlideOffScreen=24,
	SFX_PanelSlideOnScreen=23,
	SFX_Place=35,
	SFX_PlaceCrystal=37,
	SFX_PlaceOre=36,
	SFX_Preload_Count=45,
	SFX_RockBreak=4,
	SFX_RockMonster=9,
	SFX_RockMonster2=10,
	SFX_RockMonsterStep=11,
	SFX_RockWipe=39,
	SFX_Siren=25,
	SFX_Stamp=1,
	SFX_Step=8,
	SFX_TopPriority=30,
	SFX_Walker=16,
	SFX_Wall=32,
	SFX_YesSir=17
} SFX_ID;

typedef enum ToolTipFlags { // [LegoRR/ToolTip.c|flags:0x4|type:uint] Note flags 0x1 and 0x2 are indistinguishable from one another.
	TOOLTIP_FLAG_ACTIVE=4,
	TOOLTIP_FLAG_ENABLED1=1,
	TOOLTIP_FLAG_ENABLED2=2,
	TOOLTIP_FLAG_IMAGECONTENT=8,
	TOOLTIP_FLAG_NONE=0,
	TOOLTIP_FLAG_RIGHTALIGN=16
} ToolTipFlags;

typedef struct IDirectDrawSurface4 IDirectDrawSurface4, *PIDirectDrawSurface4;

typedef enum ImageFlags { // [Gods98/Images.c|flags:0x4|type:uint]
	IMAGE_FLAG_INITIALISED=1,
	IMAGE_FLAG_NONE=0,
	IMAGE_FLAG_TEXTURE=4,
	IMAGE_FLAG_TRANS=2
} ImageFlags;

typedef struct IDirectDrawSurface4Vtbl IDirectDrawSurface4Vtbl, *PIDirectDrawSurface4Vtbl;

typedef long HRESULT;

typedef struct IUnknown IUnknown, *PIUnknown;


// WARNING! conflicting data type names: /guiddef.h/GUID - /GUID

typedef GUID IID;

typedef struct tagRECT tagRECT, *PtagRECT;

typedef struct tagRECT * LPRECT;

typedef struct DDSCAPS2 DDSCAPS2, *PDDSCAPS2;

typedef struct IDirectDrawPalette IDirectDrawPalette, *PIDirectDrawPalette;

typedef struct DDPIXELFORMAT DDPIXELFORMAT, *PDDPIXELFORMAT;

typedef struct DDSURFACEDESC2 DDSURFACEDESC2, *PDDSURFACEDESC2;

typedef struct DDCOLORKEY DDCOLORKEY, *PDDCOLORKEY;

typedef struct IUnknownVtbl IUnknownVtbl, *PIUnknownVtbl;

typedef struct IDirectDrawPaletteVtbl IDirectDrawPaletteVtbl, *PIDirectDrawPaletteVtbl;

typedef struct D3DRMPaletteEntry D3DRMPaletteEntry, *PD3DRMPaletteEntry;

typedef enum D3DRMPaletteFlags { // [DirectX/D3DRM.c|flags:0x1|type:byte|tags:DIRECTX]
	D3DRMPALETTE_FREE=0,
	D3DRMPALETTE_READONLY=1,
	D3DRMPALETTE_RESERVED=2
} D3DRMPaletteFlags;

struct ToolTip { // [LegoRR/ToolTip.c|struct:0x27c]
	float timer;
	char textBuffer[512];
	uint textWidth;
	uint textLineCount;
	struct Image * iconList[20];
	uint iconCount;
	int iconsY;
	int iconsHeight;
	int iconsX;
	int iconsWidth;
	struct Image * image; // Supplied with SetText prefixed with an at sign.
	enum SFX_ID sfxType;
	enum ToolTipFlags flags; // (flag 0x8 IMAGE is not for "iconList")
};

struct D3DRMPaletteEntry { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX]
	byte red; // 0 .. 255
	byte green; // 0 .. 255
	byte blue; // 0 .. 255
	enum D3DRMPaletteFlags flags; // one of D3DRMPaletteFlags
};

struct DDCOLORKEY { // [DirectX/DDraw.c|struct:0x8|tags:DIRECTX]
	DWORD dwColorSpaceLowValue;
	DWORD dwColorSpaceHighValue;
};

struct Image { // [Gods98/Images.c|struct:0x20|tags:LISTSET]
	struct IDirectDrawSurface4 * surface; // IDirectDrawSurface4
	uint width;
	uint height;
	uint penZero; // Palette entry 0
	uint pen255; // Palette entry 255
	uint penZeroRGB; // Palette entry 0 (as unpacked RGB)
	enum ImageFlags flags; // 2 is font?
	struct Image * nextFree;
};

struct IDirectDrawSurface4Vtbl { // [DirectX/DDraw.c|struct:0xb4|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer AddAttachedSurface;
	pointer AddOverlayDirtyRect;
	HRESULT (* Blt)(struct IDirectDrawSurface4 *, LPRECT, struct IDirectDrawSurface4 *, LPRECT, DWORD, void *);
	pointer BltBatch;
	pointer BltFast;
	pointer DeleteAttachedSurface;
	pointer EnumAttachedSurfaces;
	pointer EnumOverlayZOrders;
	HRESULT (* Flip)(struct IDirectDrawSurface4 *, struct IDirectDrawSurface4 *, DWORD);
	HRESULT (* GetAttachedSurface)(struct IDirectDrawSurface4 *, struct DDSCAPS2, struct IDirectDrawSurface4 * *);
	pointer GetBltStatus;
	pointer GetCaps;
	pointer GetClipper;
	pointer GetColorKey;
	pointer GetDC;
	pointer GetFlipStatus;
	pointer GetOverlayPosition;
	HRESULT (* GetPalette)(struct IDirectDrawSurface4 *, struct IDirectDrawPalette * *);
	HRESULT (* GetPixelFormat)(struct IDirectDrawSurface4 *, struct DDPIXELFORMAT *);
	pointer GetSurfaceDesc;
	pointer Initialize;
	pointer IsLost;
	HRESULT (* Lock)(struct IDirectDrawSurface4 *, LPRECT, struct DDSURFACEDESC2 *, DWORD, HANDLE);
	pointer ReleaseDC;
	pointer Restore;
	pointer SetClipper;
	HRESULT (* SetColorKey)(struct IDirectDrawSurface4 *, DWORD, struct DDCOLORKEY *);
	pointer SetOverlayPosition;
	HRESULT (* SetPalette)(struct IDirectDrawSurface4 *, struct IDirectDrawPalette *);
	HRESULT (* Unlock)(struct IDirectDrawSurface4 *, LPRECT);
	pointer UpdateOverlay;
	pointer UpdateOverlayDisplay;
	pointer UpdateOverlayZOrder;
	pointer GetDDInterface;
	pointer PageLock;
	pointer PageUnlock;
	pointer SetSurfaceDesc;
	pointer SetPrivateData;
	pointer GetPrivateData;
	pointer FreePrivateData;
	pointer GetUniquenessValue;
	pointer ChangeUniquenessValue;
};

struct IDirectDrawPalette { // [DirectX/DDraw.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirectDrawPaletteVtbl * lpVtbl;
};

struct DDPIXELFORMAT { // [DirectX/DDraw.c|struct:0x20|tags:DIRECTX] https://docs.microsoft.com/en-us/windows/win32/api/ddraw/ns-ddraw-ddpixelformat
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwFourCC;
	DWORD dwRGBBitCount;
	DWORD dwRBitMask;
	DWORD dwGBitMask;
	DWORD dwBBitMask;
	DWORD dwRGBAlphaBitMask;
};

struct DDSCAPS2 { // [DirectX/DDraw.c|struct:0x10|tags:DIRECTX]
	DWORD dwCaps; // capabilities of surface wanted
	DWORD dwCaps2;
	DWORD dwCaps3;
	DWORD dwCaps4_VolumeDepth;
};

struct DDSURFACEDESC2 { // [DirectX/DDraw.c|struct:0x7c|tags:DIRECTX]
	DWORD dwSize; // size of the DDSURFACEDESC2 structure
	DWORD dwFlags; // determines what fields are valid
	DWORD dwHeight; // height of surface to be created
	DWORD dwWidth; // width of input surface
	DWORD lPitch;
	DWORD dwBackBufferCount_Depth;
	DWORD dwMipMapCount_RefreshRate_SrcVBHandle;
	DWORD dwAlphaBitDepth; // depth of alpha buffer requested
	DWORD dwReserved; // reserved
	LPVOID lpSurface; // pointer to the associated surface memory
	struct DDCOLORKEY ddckCKDestOverlay_dwEmptyFaceColor;
	struct DDCOLORKEY ddckCKDestBlt; // color key for destination blt use
	struct DDCOLORKEY ddckCKSrcOverlay; // color key for source overlay use
	struct DDCOLORKEY ddckCKSrcBlt; // color key for source blt use
	struct DDPIXELFORMAT ddpfPixelFormat; // pixel format description of the surface
	struct DDSCAPS2 ddsCaps; // direct draw surface capabilities
	DWORD dwTextureStage; // stage in multitexture cascade
};

struct IDirectDrawPaletteVtbl { // [DirectX/DDraw.c|struct:0x1c|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer GetCaps;
	HRESULT (* GetEntries)(struct IDirectDrawPalette *, DWORD, DWORD, DWORD, struct D3DRMPaletteEntry *);
	pointer Initialize;
	pointer SetEntries;
};

struct tagRECT {
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;
};

struct IUnknownVtbl {
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, void * *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
};

struct IUnknown {
	struct IUnknownVtbl * lpVtbl;
};

struct IDirectDrawSurface4 { // [DirectX/DDraw.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirectDrawSurface4Vtbl * lpVtbl;
};

typedef struct DependencyRequirement DependencyRequirement, *PDependencyRequirement;

typedef enum LegoObject_Type { // [LegoRR/LegoObject.c|enum:0x4|type:int]
	LegoObject_Barrier=9,
	LegoObject_Boulder=5,
	LegoObject_Building=4,
	LegoObject_Dynamite=8,
	LegoObject_ElectricFence=11,
	LegoObject_ElectricFenceStud=14,
	LegoObject_Freezer=17,
	LegoObject_IceCube=18,
	LegoObject_LaserShot=19,
	LegoObject_MiniFigure=2,
	LegoObject_None=0,
	LegoObject_OohScary=13,
	LegoObject_Ore=7,
	LegoObject_Path=15,
	LegoObject_PowerCrystal=6,
	LegoObject_Pusher=16,
	LegoObject_RockMonster=3,
	LegoObject_SpiderWeb=12,
	LegoObject_TVCamera=4294967295,
	LegoObject_Type_Count=20,
	LegoObject_UpgradePart=10,
	LegoObject_Vehicle=1
} LegoObject_Type;

typedef uint LegoObject_ID;

struct DependencyRequirement { // [LegoRR/Dependencies.c|struct:0x10]
	enum LegoObject_Type objType;
	LegoObject_ID objID;
	uint objLevel;
	BOOL hasLevel;
};

typedef struct DependencyData DependencyData, *PDependencyData;

typedef enum DependencyFlags { // [LegoRR/Dependencies.c|flags:0x4|type:uint]
	DEPENDENCY_FLAG_HITONCESTAY=1,
	DEPENDENCY_FLAG_NONE=0,
	DEPENDENCY_FLAG_UNK_100=256,
	DEPENDENCY_FLAG_UNK_2=2,
	DEPENDENCY_FLAG_UNK_4=4,
	DEPENDENCY_FLAG_UNK_8=8
} DependencyFlags;

struct DependencyData { // [LegoRR/Dependencies.c|struct:0xc4]
	uint numRequirements[16]; // [levels:16]
	struct DependencyRequirement * requirements[16]; // [levels:16][*numRequired] Ptr to table of size numRequired
	BOOL manualLevel; // Force requirements for specific level if key format: "<HitOnceStay|*>:Object:<#>"
	enum DependencyFlags levelFlags[16]; // [levels:16] (1 = HitOnceStay)
};

typedef struct AdvisorPositionData AdvisorPositionData, *PAdvisorPositionData;

typedef enum Advisor_Anim { // [LegoRR/Advisor.c|enum:0x4|type:int]
	Advisor_Anim_Count=11,
	Advisor_Anim_PointToMap=0,
	Advisor_Anim_Point_E=3,
	Advisor_Anim_Point_N=1,
	Advisor_Anim_Point_NE=2,
	Advisor_Anim_Point_NW=8,
	Advisor_Anim_Point_S=5,
	Advisor_Anim_Point_SE=4,
	Advisor_Anim_Point_SW=6,
	Advisor_Anim_Point_Up=9,
	Advisor_Anim_Point_W=7,
	Advisor_Anim_Talk_Top=10
} Advisor_Anim;

typedef enum Text_Type { // [LegoRR/Text.c|enum:0x4|type:int]
	Text_AirSupplyLow=20,
	Text_AirSupplyRunningOut=21,
	Text_BuildHelp=10,
	Text_CannotPlaceBuilding=15,
	Text_CantDrill=3,
	Text_CantDrive=13,
	Text_CantReinforce=6,
	Text_CavernDiscovered=18,
	Text_CrystalFound=17,
	Text_CrystalOreDisabled=16,
	Text_Drill=1,
	Text_Drive=12,
	Text_Encyclopedia=8,
	Text_GameCompleted=23,
	Text_MakeTeleporter=14,
	Text_ManTrained=24,
	Text_NoDrill=2,
	Text_NoReinforce=5,
	Text_OreFound=19,
	Text_PickupCrystal=7,
	Text_RadarHelp=9,
	Text_Reinforce=4,
	Text_SelectionHelp=11,
	Text_SpaceToContinue=22,
	Text_Type_Count=26,
	Text_UnitUpgraded=25,
	Text_Walk=0
} Text_Type;

typedef enum Panel_Type { // [LegoRR/Panels.c|enum:0x4|type:int]
	Panel_CameraControl=9,
	Panel_CrystalSideBar=5,
	Panel_Encyclopedia=11,
	Panel_InfoDock=10,
	Panel_Information=7,
	Panel_Messages=3,
	Panel_MessagesSide=4,
	Panel_PriorityList=8,
	Panel_Radar=0,
	Panel_RadarFill=1,
	Panel_RadarOverlay=2,
	Panel_TopPanel=6,
	Panel_Type_Count=12
} Panel_Type;

typedef enum AdvisorFlags { // [LegoRR/Advisor.c|flags:0x4|type:uint]
	ADVISOR_FLAG_HASTEXT=262144,
	ADVISOR_FLAG_NONE=0,
	ADVISOR_FLAG_NOPANEL=65536,
	ADVISOR_FLAG_USED=131072
} AdvisorFlags;

struct AdvisorPositionData { // [LegoRR/Advisor.c|struct:0x24]
	enum Advisor_Anim animType;
	enum Text_Type textType;
	enum SFX_ID sfxID;
	enum Panel_Type panelType;
	float x; // Mutable x position
	float y; // Mutable y position
	float origX; // Immutable x position (set once)
	float origY; // Immutable y position (set once)
	enum AdvisorFlags flags; // (init: 0x20000), 0x10000 = NULL panel, 0x40000 = non-NULL text
};

typedef struct DependencyUnlocks DependencyUnlocks, *PDependencyUnlocks;

struct DependencyUnlocks { // [LegoRR/Dependencies.c|struct:0x204]
	enum LegoObject_Type objTypes[32];
	LegoObject_ID objIDs[32];
	uint objLevels[32];
	BOOL objHasLevels[32]; // (unlocks for a specific level)
	uint count;
};

typedef struct HelpWindowInfoLevels HelpWindowInfoLevels, *PHelpWindowInfoLevels;

struct HelpWindowInfoLevels { // [LegoRR/HelpWindow.c|struct:0x40]
	char * levels[16];
};

typedef struct PTL_Property PTL_Property, *PPTL_Property;

typedef enum Message_Type { // [LegoRR/Message.c|enum:0x4|type:int]
	Message_AttackBuilding=37,
	Message_AttackBuildingComplete=38,
	Message_BuildPath=48,
	Message_BuildPathComplete=49,
	Message_Clear=39,
	Message_ClearBuilding=58,
	Message_ClearBuildingComplete=59,
	Message_ClearComplete=40,
	Message_ClearFallIn=46,
	Message_ClearFallInComplete=47,
	Message_ClearInitial=60,
	Message_ClearInitialComplete=61,
	Message_ClearRemovePath=62,
	Message_ClearRemovePathComplete=63,
	Message_ClearSelection=3,
	Message_CollectCrystal=23,
	Message_CollectCrystalComplete=24,
	Message_CollectOre=29,
	Message_CollectOreComplete=30,
	Message_CollectTool=44,
	Message_CrystalToRefinery=25,
	Message_CrystalToRefineryComplete=26,
	Message_Debug_DestroyAll=64,
	Message_Deselect=4,
	Message_Dig=13,
	Message_DigComplete=14,
	Message_FirstPerson=9,
	Message_FollowAttack=43,
	Message_GatherRock=33,
	Message_GatherRockComplete=34,
	Message_GenerateCrystal=21,
	Message_GenerateCrystalAndOre=52,
	Message_GenerateCrystalAndOreComplete=53,
	Message_GenerateCrystalComplete=22,
	Message_GenerateFromCryOre=54,
	Message_GenerateFromCryOreComplete=55,
	Message_GenerateOre=27,
	Message_GenerateOreComplete=28,
	Message_GenerateRockMonster=31,
	Message_GenerateRockMonsterComplete=32,
	Message_GetIn=41,
	Message_Goto=5,
	Message_ManSelectedAndMonsterClicked=42,
	Message_Null=0,
	Message_PickRandomFloor=35,
	Message_PickRandomFloorComplete=36,
	Message_PlaySample=12,
	Message_ReduceSelection=45,
	Message_Reinforce=17,
	Message_ReinforceComplete=18,
	Message_Repair=15,
	Message_RepairComplete=16,
	Message_RockFall=19,
	Message_RockFallComplete=20,
	Message_RockMonsterGoto=6,
	Message_RockMonsterGotoComplete=7,
	Message_Select=1,
	Message_Selected=2,
	Message_TopView=11,
	Message_TrackObject=10,
	Message_Train=50,
	Message_TrainComplete=51,
	Message_Type_Count=65,
	Message_Upgrade=56,
	Message_UpgradeComplete=57,
	Message_UserGoto=8
} Message_Type;

struct PTL_Property { // [LegoRR/PTL.c|struct:0x8] Property loaded from a level's PTL config file (contains lookup index for actions)
	enum Message_Type fromType; // The original "posted" event message type.
	enum Message_Type toType; // The output "translated" event message type.
};

typedef struct Interface_Menu Interface_Menu, *PInterface_Menu;

typedef enum Interface_MenuItemType { // [LegoRR/Interface.c|enum:0x4|type:int] "Back" has no official name
	Interface_MenuItem_Attack=43,
	Interface_MenuItem_Back=0,
	Interface_MenuItem_Build=73,
	Interface_MenuItem_BuildBuilding=2,
	Interface_MenuItem_BuildLargeVehicle=4,
	Interface_MenuItem_BuildSmallVehicle=3,
	Interface_MenuItem_CancelConstruction=16,
	Interface_MenuItem_ClearRubble=9,
	Interface_MenuItem_ClearSelection=72,
	Interface_MenuItem_Dam=10,
	Interface_MenuItem_DeleteBuilding=40,
	Interface_MenuItem_DeleteElectricFence=42,
	Interface_MenuItem_DeleteMan=32,
	Interface_MenuItem_DeleteVehicle=41,
	Interface_MenuItem_DeselectDig=15,
	Interface_MenuItem_Dig=11,
	Interface_MenuItem_DropBirdScarer=33,
	Interface_MenuItem_Dynamite=13,
	Interface_MenuItem_EjectCrystal=38,
	Interface_MenuItem_EjectOre=39,
	Interface_MenuItem_Encyclopedia=71,
	Interface_MenuItem_GeologistTest=8,
	Interface_MenuItem_GetBirdScarer=56,
	Interface_MenuItem_GetDrill=49,
	Interface_MenuItem_GetFreezerGun=55,
	Interface_MenuItem_GetHammer=51,
	Interface_MenuItem_GetIn=24,
	Interface_MenuItem_GetLaser=53,
	Interface_MenuItem_GetOut=25,
	Interface_MenuItem_GetPusherGun=54,
	Interface_MenuItem_GetSpade=50,
	Interface_MenuItem_GetSpanner=52,
	Interface_MenuItem_GetTool=48,
	Interface_MenuItem_GoFeed=31,
	Interface_MenuItem_GotoDock=26,
	Interface_MenuItem_GotoFirstPerson=45,
	Interface_MenuItem_GotoSecondPerson=46,
	Interface_MenuItem_GotoTopView=44,
	Interface_MenuItem_LayPath=5,
	Interface_MenuItem_LegoManDig=30,
	Interface_MenuItem_LegoManGoto=27,
	Interface_MenuItem_MakeTeleporterPrimary=37,
	Interface_MenuItem_MinifigurePickUp=21,
	Interface_MenuItem_PlaceFence=14,
	Interface_MenuItem_PowerOff=35,
	Interface_MenuItem_PowerOn=34,
	Interface_MenuItem_Reinforce=12,
	Interface_MenuItem_RemovePath=6,
	Interface_MenuItem_Repair=36,
	Interface_MenuItem_RepairLava=7,
	Interface_MenuItem_SelectBuilding=19,
	Interface_MenuItem_SelectMan=17,
	Interface_MenuItem_SelectVehicle=18,
	Interface_MenuItem_TeleportMan=1,
	Interface_MenuItem_TrackObject=47,
	Interface_MenuItem_TrainDriver=58,
	Interface_MenuItem_TrainDynamite=63,
	Interface_MenuItem_TrainEngineer=59,
	Interface_MenuItem_TrainGeologist=60,
	Interface_MenuItem_TrainPilot=61,
	Interface_MenuItem_TrainSailor=62,
	Interface_MenuItem_TrainSkill=57,
	Interface_MenuItem_Type_Count=74,
	Interface_MenuItem_Type_Invalid=4294967295,
	Interface_MenuItem_UnLoadMinifigure=23,
	Interface_MenuItem_UnLoadVehicle=22,
	Interface_MenuItem_UpgardeCarry=70,
	Interface_MenuItem_UpgardeDrill=68,
	Interface_MenuItem_UpgardeScan=69,
	Interface_MenuItem_UpgradeBuilding=65,
	Interface_MenuItem_UpgradeEngine=67,
	Interface_MenuItem_UpgradeMan=64,
	Interface_MenuItem_UpgradeVehicle=66,
	Interface_MenuItem_VehicleDig=29,
	Interface_MenuItem_VehicleGoto=28,
	Interface_MenuItem_VehiclePickUp=20
} Interface_MenuItemType;

struct Interface_Menu { // [LegoRR/Interface.c|struct:0x8] Simple list of icons-by-enum for an interface menu.
	enum Interface_MenuItemType * iconList;
	uint iconCount;
};

typedef struct ObjectiveData ObjectiveData, *PObjectiveData;

typedef struct Point2F Point2F, *PPoint2F;

typedef struct Point2I Point2I, *PPoint2I;

struct Point2I { // [common.c|struct:0x8]
	int x;
	int y;
};

struct Point2F { // [common.c|struct:0x8] also Vector2F
	float x;
	float y;
};

struct ObjectiveData { // [LegoRR/???|struct:0x54]
	struct Image * panelImage; // (cfg: ObjectiveImage<W>x<H>[0])
	struct Point2F panelImagePosition; // (cfg: ObjectiveImage<W>x<H>[1,2])
	struct Image * achievedImage; // (cfg: ObjectiveAcheivedImage<W>x<H>[0]) unused
	struct Point2F achievedImagePosition; // (cfg: ObjectiveAcheivedImage<W>x<H>[1,2]) unused
	struct Image * failedImage; // (cfg: ObjectiveFailedImage<W>x<H>[0]) unused
	struct Point2F failedImagePosition; // (cfg: ObjectiveFailedImage<W>x<H>[1,2]) unused
	char * achievedVideoName; // (cfg: ObjectiveAcheivedAVI[0]) filename
	struct Point2F achievedVideoPosition; // (cfg: ObjectiveAcheivedAVI[1,2]) 
	BOOL noAchievedVideo; // True if cfg:ObjectiveAcheivedAVI was not parsed correctly (or does not eixst?)
	BOOL achievedVideoPlayed;
	uint crystals; // (cfg: CrystalObjective) number of crystals needed if non-zero
	uint ore; // (cfg: OreObjective) number of ore needed if non-zero
	struct Point2I blockPos; // (cfg: BlockObjective)
	float timer; // (cfg: TimerObjective, mult: 25.0, flags, format: "time:HitTimeFailObjective")
	enum LegoObject_Type constructionType; // (cfg: ConstructionObjective)
	int constructionID; // (cfg: ConstructionObjective)
};

typedef struct MsvcDOSErrnoInfo MsvcDOSErrnoInfo, *PMsvcDOSErrnoInfo;

typedef int errno_t;

struct MsvcDOSErrnoInfo { // [tags:HIDDEN,STD]
	uint doserrno;
	errno_t errno;
};

typedef struct BITMAP_FILE_INFO_STRUCT BITMAP_FILE_INFO_STRUCT, *PBITMAP_FILE_INFO_STRUCT;

typedef struct tagBITMAPFILEHEADER tagBITMAPFILEHEADER, *PtagBITMAPFILEHEADER;

typedef struct tagBITMAPFILEHEADER BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER tagBITMAPINFOHEADER, *PtagBITMAPINFOHEADER;

typedef struct tagBITMAPINFOHEADER BITMAPINFOHEADER;

typedef struct tagRGBQUAD tagRGBQUAD, *PtagRGBQUAD;

typedef struct tagRGBQUAD RGBQUAD;

struct tagRGBQUAD {
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
};

struct tagBITMAPFILEHEADER {
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
};

struct tagBITMAPINFOHEADER {
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
};

struct BITMAP_FILE_INFO_STRUCT { // [Gods98/dummy.c|struct:0x3a|pack:2] Helper struct to combine both BITMAPFILEHEADER, BITMAPINFOHEADER, and palette data into one field
	BITMAPFILEHEADER hdr;
	BITMAPINFOHEADER bmi;
	RGBQUAD bmiColors[1];
};

typedef enum _fpmath_enum { // [tags:HIDDEN,STD]
	_FPMATH__cabs=17,
	_FPMATH__hypot=24,
	_FPMATH__y0=34,
	_FPMATH__y1=35,
	_FPMATH__yn=36,
	_FPMATH_acos=13,
	_FPMATH_asin=14,
	_FPMATH_atan=15,
	_FPMATH_atan2=16,
	_FPMATH_ceil=12,
	_FPMATH_cos=18,
	_FPMATH_cosh=19,
	_FPMATH_exp=20,
	_FPMATH_fabs=21,
	_FPMATH_floor=11,
	_FPMATH_fmod=22,
	_FPMATH_frexp=23,
	_FPMATH_ldexp=25,
	_FPMATH_log=26,
	_FPMATH_log10=27,
	_FPMATH_modf=28,
	_FPMATH_pow=29,
	_FPMATH_sin=30,
	_FPMATH_sinh=31,
	_FPMATH_sqrt=5,
	_FPMATH_tan=32,
	_FPMATH_tanh=33
} _fpmath_enum;

typedef struct ElectricFence_Block ElectricFence_Block, *PElectricFence_Block;

typedef void (* ElectricFence_RunThroughListsCallback)(struct ElectricFence_Block *, void *);

typedef struct LegoObject LegoObject, *PLegoObject;

typedef struct VehicleModel VehicleModel, *PVehicleModel;

typedef struct CreatureModel CreatureModel, *PCreatureModel;

typedef struct BuildingModel BuildingModel, *PBuildingModel;

typedef struct Container Container, *PContainer;

typedef struct Upgrade_PartModel Upgrade_PartModel, *PUpgrade_PartModel;

typedef struct RoutingBlock RoutingBlock, *PRoutingBlock;

typedef struct BezierCurve BezierCurve, *PBezierCurve;

typedef struct Vector3F Vector3F, *PVector3F;

typedef struct AITask AITask, *PAITask;

typedef struct Flocks Flocks, *PFlocks;

typedef struct ObjectStats ObjectStats, *PObjectStats;

typedef enum LOD_PolyLevel { // [LegoRR/MeshLOD.c|enum:0x4|type:int]
	LOD_FPPoly=3,
	LOD_HighPoly=2,
	LOD_LowPoly=0,
	LOD_MediumPoly=1
} LOD_PolyLevel;

typedef enum LegoObject_ToolType { // [LegoRR/LegoObject.c|enum:0x4|type:int] One of the few enums with extra space before max. All items after FreezerGun are special tools.
	LegoObject_ToolType_Barrier=8,
	LegoObject_ToolType_BirdScarer=6,
	LegoObject_ToolType_Count=11,
	LegoObject_ToolType_CryOre=10,
	LegoObject_ToolType_Drill=0,
	LegoObject_ToolType_Dynamite=9,
	LegoObject_ToolType_FreezerGun=7,
	LegoObject_ToolType_Hammer=2,
	LegoObject_ToolType_Laser=4,
	LegoObject_ToolType_PusherGun=5,
	LegoObject_ToolType_Spade=1,
	LegoObject_ToolType_Spanner=3
} LegoObject_ToolType;

typedef struct TeleporterService TeleporterService, *PTeleporterService;

typedef enum LiveFlags1 { // [LegoRR/LegoObject.c|flags:0x4|type:uint]
	LIVEOBJ1_CANTDO=2147483648,
	LIVEOBJ1_CARRYING=1024,
	LIVEOBJ1_CAUGHTINWEB=33554432,
	LIVEOBJ1_CLEARING=262144,
	LIVEOBJ1_CRUMBLING=1048576,
	LIVEOBJ1_DRILLING=8,
	LIVEOBJ1_DRILLINGSTART=16,
	LIVEOBJ1_EATING=1073741824,
	LIVEOBJ1_ENTERING_WALLHOLE=131072,
	LIVEOBJ1_EXPANDING=256,
	LIVEOBJ1_GATHERINGROCK=512,
	LIVEOBJ1_GETTINGHIT=4096,
	LIVEOBJ1_LIFTING=2,
	LIVEOBJ1_MOVING=1,
	LIVEOBJ1_NONE=0,
	LIVEOBJ1_PLACING=524288,
	LIVEOBJ1_REINFORCING=64,
	LIVEOBJ1_REPAIRDRAINING=16777216,
	LIVEOBJ1_RESTING=536870912,
	LIVEOBJ1_RUNNINGAWAY=8388608,
	LIVEOBJ1_SCAREDBYPLAYER=134217728,
	LIVEOBJ1_SLIPPING=67108864,
	LIVEOBJ1_STORING=8192,
	LIVEOBJ1_TELEPORTINGDOWN=2097152,
	LIVEOBJ1_TELEPORTINGUP=4194304,
	LIVEOBJ1_TURNING=4,
	LIVEOBJ1_TURNRIGHT=128,
	LIVEOBJ1_UNK_10000=65536,
	LIVEOBJ1_UNK_4000=16384,
	LIVEOBJ1_UNK_800=2048,
	LIVEOBJ1_UNUSED_10000000=268435456,
	LIVEOBJ1_UNUSED_20=32,
	LIVEOBJ1_WAITING=32768
} LiveFlags1;

typedef enum LiveFlags2 { // [LegoRR/LegoObject.c|flags:0x4|type:uint]
	LIVEOBJ2_ACTIVEELECTRICFENCE=33554432,
	LIVEOBJ2_BUILDPATH=512,
	LIVEOBJ2_DAMAGESHAKING=1073741824,
	LIVEOBJ2_DAMAGE_UNK_1000=4096,
	LIVEOBJ2_DRIVING=8,
	LIVEOBJ2_FIRINGFREEZER=16777216,
	LIVEOBJ2_FIRINGLASER=4194304,
	LIVEOBJ2_FIRINGPUSHER=8388608,
	LIVEOBJ2_FROZEN=134217728,
	LIVEOBJ2_NONE=0,
	LIVEOBJ2_PUSHED=16384,
	LIVEOBJ2_RECHARGING=268435456,
	LIVEOBJ2_SHOWDAMAGENUMBERS=8192,
	LIVEOBJ2_THROWING=1,
	LIVEOBJ2_THROWN=2,
	LIVEOBJ2_TRAINING=1024,
	LIVEOBJ2_TRIGGERFRAMECALLBACK=65536,
	LIVEOBJ2_UNK_10=16,
	LIVEOBJ2_UNK_100=256,
	LIVEOBJ2_UNK_100000=1048576,
	LIVEOBJ2_UNK_20=32,
	LIVEOBJ2_UNK_20000=131072,
	LIVEOBJ2_UNK_200000=2097152,
	LIVEOBJ2_UNK_20000000=536870912,
	LIVEOBJ2_UNK_4=4,
	LIVEOBJ2_UNK_40=64,
	LIVEOBJ2_UNK_40000=262144,
	LIVEOBJ2_UNK_4000000=67108864,
	LIVEOBJ2_UNK_80=128,
	LIVEOBJ2_UNK_800=2048,
	LIVEOBJ2_UNK_80000=524288,
	LIVEOBJ2_UNK_80000000=2147483648,
	LIVEOBJ2_UPGRADING=32768
} LiveFlags2;

typedef enum LiveFlags3 { // [LegoRR/LegoObject.c|flags:0x4|type:uint]
	LIVEOBJ3_AITASK_UNK_400000=4194304,
	LIVEOBJ3_ALLOWCULLING_UNK=1048576,
	LIVEOBJ3_CANCARRY=32,
	LIVEOBJ3_CANDAMAGE=262144,
	LIVEOBJ3_CANDIG=2,
	LIVEOBJ3_CANDYNAMITE=32768,
	LIVEOBJ3_CANFIRSTPERSON=16,
	LIVEOBJ3_CANGATHER=67108864,
	LIVEOBJ3_CANPICKUP=64,
	LIVEOBJ3_CANREINFORCE=4,
	LIVEOBJ3_CANROUTERUBBLE=268435456,
	LIVEOBJ3_CANSELECT=256,
	LIVEOBJ3_CANTURN=8,
	LIVEOBJ3_CANYESSIR=128,
	LIVEOBJ3_CENTERBLOCKIDLE=4096,
	LIVEOBJ3_HASPOWER=536870912,
	LIVEOBJ3_MONSTER_UNK_8000000=134217728,
	LIVEOBJ3_NONE=0,
	LIVEOBJ3_POWEROFF=2147483648,
	LIVEOBJ3_REMOVING=8388608,
	LIVEOBJ3_SELECTED=2097152,
	LIVEOBJ3_SIMPLEOBJECT=131072,
	LIVEOBJ3_UNK_1=1,
	LIVEOBJ3_UNK_10000=65536,
	LIVEOBJ3_UNK_1000000=16777216,
	LIVEOBJ3_UNK_200=512,
	LIVEOBJ3_UNK_2000=8192,
	LIVEOBJ3_UNK_2000000=33554432,
	LIVEOBJ3_UNK_400=1024,
	LIVEOBJ3_UNK_4000=16384,
	LIVEOBJ3_UNK_40000000=1073741824,
	LIVEOBJ3_UNUSED_800=2048,
	LIVEOBJ3_UPGRADEPART=524288
} LiveFlags3;

typedef enum LiveFlags4 { // [LegoRR/LegoObject.c|flags:0x4|type:uint]
	LIVEOBJ4_CALLTOARMS=32,
	LIVEOBJ4_CRYORECOSTDROPPED=2048,
	LIVEOBJ4_DOCKOCCUPIED=64,
	LIVEOBJ4_DONTSHOWHELPWINDOW=512,
	LIVEOBJ4_DOUBLESELECTREADY=2,
	LIVEOBJ4_DRILLSOUNDPLAYING=1048576,
	LIVEOBJ4_ENGINESOUNDPLAYING=524288,
	LIVEOBJ4_ENTRANCEOCCUPIED=128,
	LIVEOBJ4_LASERTRACKERMODE=1,
	LIVEOBJ4_NONE=0,
	LIVEOBJ4_UNK_10=16,
	LIVEOBJ4_UNK_1000=4096,
	LIVEOBJ4_UNK_10000=65536,
	LIVEOBJ4_UNK_2000=8192,
	LIVEOBJ4_UNK_20000=131072,
	LIVEOBJ4_UNK_200000=2097152,
	LIVEOBJ4_UNK_4=4,
	LIVEOBJ4_UNK_4000=16384,
	LIVEOBJ4_UNK_40000=262144,
	LIVEOBJ4_UNK_400000=4194304,
	LIVEOBJ4_UNK_8=8,
	LIVEOBJ4_UNK_8000=32768,
	LIVEOBJ4_USEDBYCONSTRUCTION=256
} LiveFlags4;

typedef enum LegoObject_AbilityFlags { // [LegoRR/LegoObject.c|flags:0x4|type:uint] These can be substituted for LiveFlags5
	ABILITY_FLAG_DRIVER=4,
	ABILITY_FLAG_DYNAMITE=8,
	ABILITY_FLAG_NONE=0,
	ABILITY_FLAG_PILOT=1,
	ABILITY_FLAG_REPAIR=16,
	ABILITY_FLAG_SAILOR=2,
	ABILITY_FLAG_SCANNER=32
} LegoObject_AbilityFlags;

typedef enum LegoObject_UpgradeType { // [LegoRR/LegoObject.c|enum:0x4|type:uint]
	LegoObject_UpgradeType_Carry=3,
	LegoObject_UpgradeType_Drill=0,
	LegoObject_UpgradeType_Scan=2,
	LegoObject_UpgradeType_Speed=1
} LegoObject_UpgradeType;

typedef enum BoolTri { // [common.c|enum:0x4|type:uint] BoolTri, A 3-state boolean for True, False, or Error
	BOOL3_ERROR=2,
	BOOL3_FALSE=0,
	BOOL3_TRUE=1
} BoolTri;

typedef struct UpgradesModel UpgradesModel, *PUpgradesModel;

typedef struct WeaponsModel WeaponsModel, *PWeaponsModel;

typedef struct MeshLOD MeshLOD, *PMeshLOD;

typedef enum VehicleFlags { // [LegoRR/Vehicle.c|flags:0x4|type:uint]
	VEHICLE_FLAG_HIDDEN=2,
	VEHICLE_FLAG_HOLDMISSING=8,
	VEHICLE_FLAG_NOACTIVITY1=4,
	VEHICLE_FLAG_NONE=0,
	VEHICLE_FLAG_SOURCE=1
} VehicleFlags;

typedef enum CreatureFlags { // [LegoRR/Creature.c|flags:0x4|type:uint]
	CREATURE_FLAG_NONE=0,
	CREATURE_FLAG_SOURCE=1
} CreatureFlags;

typedef enum BuildingFlags { // [LegoRR/Building.c|flags:0x4|type:uint]
	BUILDING_FLAG_NONE=0,
	BUILDING_FLAG_SOURCE=1,
	BUILDING_FLAG_UPDATEPOWERLEVEL=2
} BuildingFlags;

typedef struct IDirect3DRMFrame3 IDirect3DRMFrame3, *PIDirect3DRMFrame3;

typedef struct Container_TypeData Container_TypeData, *PContainer_TypeData;

typedef enum Container_Type { // [Gods98/Containers.c|enum:0x4|type:int]
	Container_Type_Anim=3,
	Container_Type_Count=9,
	Container_Type_Frame=2,
	Container_Type_FromActivity=4,
	Container_Type_Invalid=4294967295,
	Container_Type_LWO=8,
	Container_Type_LWS=7,
	Container_Type_Light=5,
	Container_Type_Mesh=1,
	Container_Type_Null=0,
	Container_Type_Reference=6
} Container_Type;

typedef enum ContainerFlags { // [Gods98/Containers.c|flags:0x4|type:uint]
	CONTAINER_FLAG_ANIMATIONSKIPPED=32,
	CONTAINER_FLAG_DEADREFERENCE=16,
	CONTAINER_FLAG_HIDDEN=8,
	CONTAINER_FLAG_HIDDEN2=128,
	CONTAINER_FLAG_MESHSWAPPED=4,
	CONTAINER_FLAG_NONE=0,
	CONTAINER_FLAG_TRIGGERSAMPLE=2
} ContainerFlags;

typedef void (* ContainerActivityCallback)(struct Container *, void *);

typedef struct Container_CloneData Container_CloneData, *PContainer_CloneData;

typedef struct Upgrade_PartInfo Upgrade_PartInfo, *PUpgrade_PartInfo;

typedef enum RouteFlags { // [LegoRR/LegoObject.c|flags:0x1|type:byte]
	ROUTE_DIRECTION_MASK=3,
	ROUTE_FLAG_GOTOBUILDING=4,
	ROUTE_FLAG_NONE=0,
	ROUTE_FLAG_RUNAWAY=64,
	ROUTE_FLAG_UNK_10=16,
	ROUTE_FLAG_UNK_20=32,
	ROUTE_FLAG_UNK_8=8,
	ROUTE_UNK_MASK_c=12
} RouteFlags;

typedef enum RouteAction { // [LegoRR/Text.c|enum:0x1|type:byte]
	ROUTE_ACTION_21=21,
	ROUTE_ACTION_ATTACK=20,
	ROUTE_ACTION_CLEAR=4,
	ROUTE_ACTION_DOCK=19,
	ROUTE_ACTION_DROP=8,
	ROUTE_ACTION_EAT=11,
	ROUTE_ACTION_GATHERROCK=3,
	ROUTE_ACTION_PLACE=9,
	ROUTE_ACTION_RECHARGE=18,
	ROUTE_ACTION_REINFORCE=2,
	ROUTE_ACTION_REPAIRDRAIN=6,
	ROUTE_ACTION_STORE=7,
	ROUTE_ACTION_TRAIN=14,
	ROUTE_ACTION_UNK_1=1,
	ROUTE_ACTION_UNK_10=10,
	ROUTE_ACTION_UNK_12=12,
	ROUTE_ACTION_UNK_13=13,
	ROUTE_ACTION_UNK_16=16,
	ROUTE_ACTION_UNK_17=17,
	ROUTE_ACTION_UNK_5=5,
	ROUTE_ACTION_UPGRADE=15
} RouteAction;

typedef enum AITask_Type { // [LegoRR/AITask.c|enum:0x4|type:int]
	AITask_Type_AnimationWait=14,
	AITask_Type_AttackObject=29,
	AITask_Type_AttackPath=25,
	AITask_Type_AttackRockMonster=26,
	AITask_Type_BirdScarer=20,
	AITask_Type_BuildPath=22,
	AITask_Type_Clear=12,
	AITask_Type_Collect=3,
	AITask_Type_Count=31,
	AITask_Type_Depart=24,
	AITask_Type_Deposit=5,
	AITask_Type_Dig=8,
	AITask_Type_Dock=28,
	AITask_Type_Dump=6,
	AITask_Type_Dynamite=9,
	AITask_Type_Eat=16,
	AITask_Type_ElecFence=15,
	AITask_Type_FindDriver=18,
	AITask_Type_FindLoad=30,
	AITask_Type_Follow=1,
	AITask_Type_FollowAttack=2,
	AITask_Type_Gather=4,
	AITask_Type_GetTool=19,
	AITask_Type_Goto=0,
	AITask_Type_GotoEat=17,
	AITask_Type_Recharge=27,
	AITask_Type_Reinforce=11,
	AITask_Type_Repair=10,
	AITask_Type_Request=7,
	AITask_Type_Train=23,
	AITask_Type_Upgrade=21,
	AITask_Type_Wait=13
} AITask_Type;

typedef enum LegoObject_AbilityType { // [LegoRR/LegoObject.c|enum:0x4|type:int]
	LegoObject_AbilityType_Count=6,
	LegoObject_AbilityType_Driver=2,
	LegoObject_AbilityType_Dynamite=3,
	LegoObject_AbilityType_Invalid=4294967295,
	LegoObject_AbilityType_Pilot=0,
	LegoObject_AbilityType_Repair=4,
	LegoObject_AbilityType_Sailor=1,
	LegoObject_AbilityType_Scanner=5
} LegoObject_AbilityType;

typedef enum AI_Priority { // [LegoRR/AITask.c|enum:0x4|type:int]
	AI_Priority_AttackObject=25,
	AI_Priority_AttackPath=24,
	AI_Priority_AttackRockMonster=15,
	AI_Priority_Barrier=16,
	AI_Priority_BuildPath=14,
	AI_Priority_Clearing=8,
	AI_Priority_Congregate=26,
	AI_Priority_Construction=4,
	AI_Priority_Count=27,
	AI_Priority_Crystal=0,
	AI_Priority_DefaultCollect=2,
	AI_Priority_Depart=23,
	AI_Priority_Destruction=3,
	AI_Priority_FindLoad=17,
	AI_Priority_Gather=20,
	AI_Priority_GetIn=12,
	AI_Priority_HealthLow=11,
	AI_Priority_Ore=1,
	AI_Priority_Punch=22,
	AI_Priority_Recharge=18,
	AI_Priority_Refining=10,
	AI_Priority_Reinforce=6,
	AI_Priority_Repair=7,
	AI_Priority_Request=5,
	AI_Priority_Steal=21,
	AI_Priority_Storage=9,
	AI_Priority_Upgrade=13,
	AI_Priority_UpgradeBuilding=19
} AI_Priority;

typedef enum AITaskFlags { // [LegoRR/AITask.c|flags:0x4|type:uint]
	AITASK_FLAG_ACCEPTCARRYING=1048576,
	AITASK_FLAG_CARRYTASK=1024,
	AITASK_FLAG_CLONED=512,
	AITASK_FLAG_CREATUREREALLOCATE=8192,
	AITASK_FLAG_DIGCONNECTION=8,
	AITASK_FLAG_DISABLED=524288,
	AITASK_FLAG_DUPLICATE=64,
	AITASK_FLAG_FACEOUT=2048,
	AITASK_FLAG_FALLINCLEAR=16384,
	AITASK_FLAG_IMMEDIATESELECTION=256,
	AITASK_FLAG_MANUALYSELECTED=131072,
	AITASK_FLAG_MAXIMUMPRIORITY=65536,
	AITASK_FLAG_NONE=0,
	AITASK_FLAG_NOTIMELIMIT=128,
	AITASK_FLAG_PAUSEDDUPLICATION=262144,
	AITASK_FLAG_PERFORMING=1,
	AITASK_FLAG_REALLOCATE=16,
	AITASK_FLAG_REMOVING=32,
	AITASK_FLAG_UPDATED=2,
	AITASK_FLAG_UPGRADEBUILDING=2097152,
	AITASK_FLAG_VOLATILE=4,
	AITASK_FLAG_WAITINGFORTOOL=4096,
	AITASK_FLAG_WAITINGFORTRAIN=32768
} AITaskFlags;

typedef struct FlocksItem FlocksItem, *PFlocksItem;

typedef enum FlocksFlags { // [LegoRR/Flocks.c|flags:0x4|type:uint]
	FLOCKS_FLAG_NONE=0,
	FLOCKS_FLAG_UNK_1=1
} FlocksFlags;

typedef struct Size2F Size2F, *PSize2F;

typedef enum StatsFlags1 { // [LegoRR/Stats.c|flags:0x4|type:uint]
	STATS1_BIGTELEPORTER=32,
	STATS1_BUMPDAMAGE=1073741824,
	STATS1_CANBEDRIVEN=131072,
	STATS1_CANCLEARRUBBLE=65536,
	STATS1_CANSCARE=2048,
	STATS1_CANSCARESCORPION=262144,
	STATS1_CANSTEAL=524288,
	STATS1_CAUSESLIP=512,
	STATS1_COLLBOX=256,
	STATS1_COLLRADIUS=128,
	STATS1_CROSSLAND=33554432,
	STATS1_CROSSWATER=16777216,
	STATS1_FLOCKS=2097152,
	STATS1_FLOCKS_ANIMATEBYPITCH=268435456,
	STATS1_FLOCKS_DEBUG=4194304,
	STATS1_FLOCKS_ONGROUND=67108864,
	STATS1_FLOCKS_QUICKDESTROY=134217728,
	STATS1_FLOCKS_SMOOTH=8388608,
	STATS1_GRABMINIFIGURE=32768,
	STATS1_MANTELEPORTER=2147483648,
	STATS1_NONE=0,
	STATS1_PROCESSCRYSTAL=4,
	STATS1_PROCESSORE=2,
	STATS1_RANDOMENTERWALL=4096,
	STATS1_RANDOMMOVE=1024,
	STATS1_ROUTEAVOIDANCE=536870912,
	STATS1_SCAREDBYPLAYER=8192,
	STATS1_SINGLEWIDTHDIG=1,
	STATS1_SMALLTELEPORTER=16,
	STATS1_SNAXULIKE=16384,
	STATS1_STOREOBJECTS=8,
	STATS1_TOOLSTORE=1048576,
	STATS1_WATERTELEPORTER=64
} StatsFlags1;

typedef enum StatsFlags2 { // [LegoRR/Stats.c|flags:0x4|type:uint]
	STATS2_ATTACKPATHS=16384,
	STATS2_CANBEHITBYFENCE=65536,
	STATS2_CANBESHOTAT=262144,
	STATS2_CANDOUBLESELECT=131072,
	STATS2_CANFREEZE=16777216,
	STATS2_CANLASER=33554432,
	STATS2_CANPUSH=67108864,
	STATS2_CROSSLAVA=2097152,
	STATS2_DAMAGECAUSESCALLTOARMS=8388608,
	STATS2_DONTSHOWDAMAGE=134217728,
	STATS2_DONTSHOWONRADAR=536870912,
	STATS2_DRAINPOWER=524288,
	STATS2_GENERATEPOWER=512,
	STATS2_INVISIBLEDRIVER=1073741824,
	STATS2_NONE=0,
	STATS2_POWERBUILDING=1536,
	STATS2_REMOVEREINFORCEMENT=268435456,
	STATS2_SCAREDBYBIGBANGS=1,
	STATS2_SELFPOWERED=1024,
	STATS2_SPLITONZEROHEALTH=32768,
	STATS2_TRACKER=256,
	STATS2_TRAINDRIVER=16,
	STATS2_TRAINDYNAMITE=32,
	STATS2_TRAINPILOT=4,
	STATS2_TRAINREPAIR=64,
	STATS2_TRAINSAILOR=8,
	STATS2_TRAINSCANNER=128,
	STATS2_UNSELECTABLE=2147483648,
	STATS2_UPGRADEBUILDING=2,
	STATS2_USEBIGTELEPORTER=2048,
	STATS2_USEHOLES=1048576,
	STATS2_USELEGOMANTELEPORTER=4194304,
	STATS2_USESMALLTELEPORTER=4096,
	STATS2_USEWATERTELEPORTER=8192
} StatsFlags2;

typedef enum StatsFlags3 { // [LegoRR/Stats.c|flags:0x4|type:uint]
	STATS3_CANSTRAFE=4,
	STATS3_CARRYVEHICLES=1,
	STATS3_CLASSASLARGE=8,
	STATS3_ENTERTOOLSTORE=512,
	STATS3_GETINATLAND=32,
	STATS3_GETOUTATLAND=16,
	STATS3_NEEDSPILOT=256,
	STATS3_NONE=0,
	STATS3_SHOWHEALTHBAR=128,
	STATS3_TAKECARRYINGDRIVERS=64,
	STATS3_VEHICLECANBECARRIED=2
} StatsFlags3;

typedef enum LegoObject_UpgradeFlags { // [LegoRR/LegoObject.c|flags:0x4|type:uint]
	UPGRADE_FLAGS_ALL=15,
	UPGRADE_FLAG_CARRY=8,
	UPGRADE_FLAG_DRILL=1,
	UPGRADE_FLAG_NONE=0,
	UPGRADE_FLAG_SCAN=4,
	UPGRADE_FLAG_SPEED=2
} LegoObject_UpgradeFlags;

typedef enum MeshLODFlags { // [LegoRR/MeshLOD.c|flags:0x4|type:uint]
	MESHLOD_FLAG_CLONED=1,
	MESHLOD_FLAG_MEMBLOCK=2,
	MESHLOD_FLAG_NONE=0
} MeshLODFlags;

typedef struct IDirect3DRMFrame3Vtbl IDirect3DRMFrame3Vtbl, *PIDirect3DRMFrame3Vtbl;

typedef CHAR * LPCSTR;

typedef DWORD * LPDWORD;

typedef struct IDirect3DRMLight IDirect3DRMLight, *PIDirect3DRMLight;

typedef enum D3DRMCombineType { // [DirectX/D3DRM.c|enum:0x4|type:uint|tags:DIRECTX] TD3DRMCombineType
	D3DRMCOMBINE_AFTER=2,
	D3DRMCOMBINE_BEFORE=1,
	D3DRMCOMBINE_REPLACE=0
} D3DRMCombineType;

typedef struct Matrix4F Matrix4F, *PMatrix4F;

typedef struct IDirect3DRMVisual IDirect3DRMVisual, *PIDirect3DRMVisual;

typedef struct IDirect3DRMFrameArray IDirect3DRMFrameArray, *PIDirect3DRMFrameArray;

typedef struct IDirect3DRMLightArray IDirect3DRMLightArray, *PIDirect3DRMLightArray;

typedef enum D3DRMMaterialMode { // [DirectX/D3DRM.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DRMMATERIAL_FROMFRAME=2,
	D3DRMMATERIAL_FROMMESH=0,
	D3DRMMATERIAL_FROMPARENT=1
} D3DRMMaterialMode;

typedef enum D3DRMSortMode { // [DirectX/D3DRM.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DRMSORT_BACKTOFRONT=3,
	D3DRMSORT_FROMPARENT=0,
	D3DRMSORT_FRONTTOBACK=2,
	D3DRMSORT_NONE=1
} D3DRMSortMode;

typedef struct IDirect3DRMTexture3 IDirect3DRMTexture3, *PIDirect3DRMTexture3;

typedef enum D3DRMFrameConstraint { // [DirectX/D3DRM.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DRMCONSTRAIN_X=2,
	D3DRMCONSTRAIN_Y=1,
	D3DRMCONSTRAIN_Z=0
} D3DRMFrameConstraint;

typedef struct IDirectDrawSurface IDirectDrawSurface, *PIDirectDrawSurface;

typedef enum D3DRMFogMode { // [DirectX/D3DRM.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DRMFOG_EXPONENTIAL=1,
	D3DRMFOG_EXPONENTIALSQUARED=2,
	D3DRMFOG_LINEAR=0
} D3DRMFogMode;

typedef enum D3DRMZBufferMode { // [DirectX/D3DRM.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DRMZBUFFER_DISABLE=2,
	D3DRMZBUFFER_ENABLE=1,
	D3DRMZBUFFER_FROMPARENT=0
} D3DRMZBufferMode;

typedef enum D3DRMSceneFogMethod { // [DirectX/D3DRM.c|flags:0x4|type:uint|tags:DIRECTX] Values for flags in IDirect3DRMFrame3::SetSceneFogMethod
	D3DRMFOGMETHOD_ANY=4,
	D3DRMFOGMETHOD_TABLE=2,
	D3DRMFOGMETHOD_VERTEX=1,
	D3DRMFOGMETHOD__NONE=0
} D3DRMSceneFogMethod;

typedef struct IDirect3DRMMesh IDirect3DRMMesh, *PIDirect3DRMMesh;

typedef struct Mesh Mesh, *PMesh;

typedef struct IDirect3DRMLightVtbl IDirect3DRMLightVtbl, *PIDirect3DRMLightVtbl;

typedef enum D3DRMLightType { // [DirectX/D3DRM.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DRMLIGHT_AMBIENT=0,
	D3DRMLIGHT_DIRECTIONAL=3,
	D3DRMLIGHT_PARALLELPOINT=4,
	D3DRMLIGHT_POINT=1,
	D3DRMLIGHT_SPOT=2
} D3DRMLightType;

typedef struct IDirect3DRMFrame IDirect3DRMFrame, *PIDirect3DRMFrame;

typedef struct IDirect3DRMVisualVtbl IDirect3DRMVisualVtbl, *PIDirect3DRMVisualVtbl;

typedef struct IDirect3DRMFrameArrayVtbl IDirect3DRMFrameArrayVtbl, *PIDirect3DRMFrameArrayVtbl;

typedef struct IDirect3DRMLightArrayVtbl IDirect3DRMLightArrayVtbl, *PIDirect3DRMLightArrayVtbl;

typedef struct IDirect3DRMTexture3Vtbl IDirect3DRMTexture3Vtbl, *PIDirect3DRMTexture3Vtbl;

typedef struct D3DRMImage D3DRMImage, *PD3DRMImage;

typedef struct IDirectDrawSurfaceVtbl IDirectDrawSurfaceVtbl, *PIDirectDrawSurfaceVtbl;

typedef struct IDirect3DRMMeshVtbl IDirect3DRMMeshVtbl, *PIDirect3DRMMeshVtbl;

typedef struct Box3F Box3F, *PBox3F;

typedef enum D3DRMGroupIndex { // [DirectX/D3DRM.c|enum:0x4|type:uint|tags:DIRECTX,HIDDEN] group indexes begin a 0 (dummy for filling in the ALLGROUPS enum)
	D3DRMGROUP_0=0,
	D3DRMGROUP_ALLGROUPS=4294967295
} D3DRMGroupIndex;

typedef struct Vertex Vertex, *PVertex;

typedef enum D3DRMMapping { // [DirectX/D3DRM.c|flags:0x4|type:uint|tags:DIRECTX]
	D3DRMMAP_PERSPCORRECT=4,
	D3DRMMAP_WRAPU=1,
	D3DRMMAP_WRAPV=2
} D3DRMMapping;

typedef struct IDirect3DRMTexture IDirect3DRMTexture, *PIDirect3DRMTexture;

typedef enum D3DRMRenderQuality { // [DirectX/D3DRM.c|flags:0x4|type:uint|tags:DIRECTX,COMBOFLAGSENUM]
	D3DRMRENDER_FLAT=136,
	D3DRMRENDER_GOURAUD=137,
	D3DRMRENDER_PHONG=138,
	D3DRMRENDER_UNLITFLAT=128,
	D3DRMRENDER_WIREFRAME=64
} D3DRMRenderQuality;

typedef struct Mesh_Group Mesh_Group, *PMesh_Group;

typedef struct IDirect3DRMUserVisual IDirect3DRMUserVisual, *PIDirect3DRMUserVisual;

typedef struct Mesh_RenderDesc Mesh_RenderDesc, *PMesh_RenderDesc;

typedef struct Mesh_LightWave_Surface Mesh_LightWave_Surface, *PMesh_LightWave_Surface;

typedef struct IDirect3DRMFrameVtbl IDirect3DRMFrameVtbl, *PIDirect3DRMFrameVtbl;

typedef struct IDirect3DRMTextureVtbl IDirect3DRMTextureVtbl, *PIDirect3DRMTextureVtbl;

typedef struct Mesh_Vertex Mesh_Vertex, *PMesh_Vertex;

typedef struct D3DMaterial D3DMaterial, *PD3DMaterial;

typedef struct IDirect3DTexture2 IDirect3DTexture2, *PIDirect3DTexture2;

typedef struct IDirect3DRMUserVisualVtbl IDirect3DRMUserVisualVtbl, *PIDirect3DRMUserVisualVtbl;

typedef struct Viewport Viewport, *PViewport;

typedef void (* MeshRenderCallback)(struct Mesh *, void *, struct Viewport *);

typedef struct Container_Texture Container_Texture, *PContainer_Texture;

typedef struct ColourRGBAF ColourRGBAF, *PColourRGBAF;

typedef struct IDirect3DTexture2Vtbl IDirect3DTexture2Vtbl, *PIDirect3DTexture2Vtbl;

typedef struct IDirect3DRMViewport2 IDirect3DRMViewport2, *PIDirect3DRMViewport2;

typedef struct IDirect3DRMViewport2Vtbl IDirect3DRMViewport2Vtbl, *PIDirect3DRMViewport2Vtbl;

typedef struct IDirect3DRMDevice3 IDirect3DRMDevice3, *PIDirect3DRMDevice3;

typedef enum D3DRMViewportClearOptions { // [DirectX/D3DRM.c|flags:0x4|type:uint|tags:DIRECTX] Values for flags in IDirect3DRMViewport2::Clear2
	D3DRMCLEAR_ALL=7,
	D3DRMCLEAR_DIRTYRECTS=4,
	D3DRMCLEAR_TARGET=1,
	D3DRMCLEAR_ZBUFFER=2
} D3DRMViewportClearOptions;

typedef enum D3DRMProjectionType { // [DirectX/D3DRM.c|enum:0x4|type:uint|tags:DIRECTX] Do not use righthanded perspective in IDirect3DRMViewport2::SetProjection(). Set up righthanded mode by using IDirect3DRM3::SetOptions().
	D3DRMPROJECT_ORTHOGRAPHIC=1,
	D3DRMPROJECT_PERSPECTIVE=0,
	D3DRMPROJECT_RIGHTHANDORTHOGRAPHIC=3,
	D3DRMPROJECT_RIGHTHANDPERSPECTIVE=2
} D3DRMProjectionType;

typedef struct Vector4F Vector4F, *PVector4F;

typedef struct IDirect3DRMPickedArray IDirect3DRMPickedArray, *PIDirect3DRMPickedArray;

typedef struct IDirect3DViewport IDirect3DViewport, *PIDirect3DViewport;

typedef struct IDirect3DRMDevice3Vtbl IDirect3DRMDevice3Vtbl, *PIDirect3DRMDevice3Vtbl;

typedef struct IDirect3DRMPickedArrayVtbl IDirect3DRMPickedArrayVtbl, *PIDirect3DRMPickedArrayVtbl;

typedef struct D3DRMPickDesc D3DRMPickDesc, *PD3DRMPickDesc;

typedef struct IDirect3DViewportVtbl IDirect3DViewportVtbl, *PIDirect3DViewportVtbl;

struct Mesh_RenderDesc { // [Gods98/Mesh.c|struct:0xc]
	MeshRenderCallback renderCallback;
	void * renderCallbackData;
	uint renderFlags; // determines a lot of render states
};

struct RoutingBlock { // [LegoRR/Routing.c|struct:0x14]
	struct Point2I blockPos;
	struct Point2F blockOffset; // In range of [0.0,1.0], where 0.5 is the center of the block.
	enum RouteFlags flagsByte;
	enum RouteAction actionByte;
	undefined field_0x12;
	undefined field_0x13;
};

struct Vector3F { // [common.c|struct:0xc]
	float x;
	float y;
	float z;
};

struct Box3F { // [common.c|struct:0x18] Box3F
	struct Vector3F min;
	struct Vector3F max;
};

struct IDirect3DViewportVtbl { // [DirectX/D3D.c|struct:0x40|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer Initialize;
	pointer GetViewport;
	pointer SetViewport;
	pointer TransformVertices;
	pointer LightElements;
	pointer SetBackground;
	pointer GetBackground;
	pointer SetBackgroundDepth;
	pointer GetBackgroundDepth;
	pointer Clear;
	pointer AddLight;
	pointer DeleteLight;
	pointer NextLight;
};

struct IDirect3DRMFrame3 { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMFrame3Vtbl * lpVtbl;
};

struct IDirect3DRMPickedArray { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMPickedArrayVtbl * lpVtbl;
};

struct Container_CloneData { // [Gods98/Containers.c|struct:0x14] structure assigned to ResourceData->field_24 (allocated for ACT,ANIM resource types)
	struct Container * clonedFrom; // NULL if this is the original
	struct Container * * cloneTable; // List of clones (NULL for unused elements)
	uint cloneCount; // Total number of clones made and clone's number in the list.
	struct IDirect3DRMFrame3 * cloneNumber; // (init: ResourceData->frame2 IDirect3DRMFrame3 * ???)
	BOOL used; // (init: 1)
};

struct IDirect3DRMFrameArray { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMFrameArrayVtbl * lpVtbl;
};

struct Container { // [Gods98/Containers.c|struct:0x2c|tags:LISTSET]
	struct IDirect3DRMFrame3 * masterFrame; // (frame1)
	struct IDirect3DRMFrame3 * activityFrame; // (frame2)
	struct IDirect3DRMFrame3 * hiddenFrame; // (frame3)
	struct Container_TypeData * typeData;
	enum Container_Type type;
	enum ContainerFlags flags;
	ContainerActivityCallback activityCallback;
	void * activityCallbackData;
	void * userData; // (often LiveObject*)
	struct Container_CloneData * cloneData; // Only used by animsets.
	struct Container * nextFree;
};

struct IDirectDrawSurfaceVtbl { // [DirectX/DDraw.c|struct:0x90|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer AddAttachedSurface;
	pointer AddOverlayDirtyRect;
	pointer Blt;
	pointer BltBatch;
	pointer BltFast;
	pointer DeleteAttachedSurface;
	pointer EnumAttachedSurfaces;
	pointer EnumOverlayZOrders;
	pointer Flip;
	pointer GetAttachedSurface;
	pointer GetBltStatus;
	pointer GetCaps;
	pointer GetClipper;
	pointer GetColorKey;
	pointer GetDC;
	pointer GetFlipStatus;
	pointer GetOverlayPosition;
	pointer GetPalette;
	pointer GetPixelFormat;
	pointer GetSurfaceDesc;
	pointer Initialize;
	pointer IsLost;
	pointer Lock;
	pointer ReleaseDC;
	pointer Restore;
	pointer SetClipper;
	pointer SetColorKey;
	pointer SetOverlayPosition;
	pointer SetPalette;
	pointer Unlock;
	pointer UpdateOverlay;
	pointer UpdateOverlayDisplay;
	pointer UpdateOverlayZOrder;
};

struct Size2F { // [common.c|struct:0x8]
	float width;
	float height;
};

struct IDirect3DRMTexture3 { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMTexture3Vtbl * lpVtbl;
};

struct IDirect3DRMTextureVtbl { // [DirectX/D3DRM.c|struct:0x78|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Clone)(struct IUnknown *, struct IUnknown *, IID *, LPVOID *);
	HRESULT (* AddDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* DeleteDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* SetAppData)(struct IUnknown *, DWORD);
	DWORD (* GetAppData)(struct IUnknown *);
	HRESULT (* SetName)(struct IUnknown *, LPCSTR);
	HRESULT (* GetName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* GetClassName)(struct IUnknown *, LPDWORD, LPSTR);
	pointer InitFromFile;
	pointer InitFromSurface;
	pointer InitFromResource;
	pointer Changed;
	pointer SetColors;
	pointer SetShades;
	pointer SetDecalSize;
	pointer SetDecalOrigin;
	pointer SetDecalScale;
	pointer SetDecalTransparency;
	pointer SetDecalTransparentColor;
	pointer GetDecalSize;
	pointer GetDecalOrigin;
	D3DRMImage * (* GetImage)(struct IDirect3DRMTexture3 *);
	pointer GetShades;
	pointer GetColors;
	pointer GetDecalScale;
	pointer GetDecalTransparency;
	pointer GetDecalTransparentColor;
};

struct BezierCurve { // [LegoRR/Routing.c|struct:0x25c]
	uint count;
	struct Point2F points[50];
	float distances[50];
};

struct IDirect3DRMFrame3Vtbl { // [DirectX/D3DRM.c|struct:0x164|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Clone)(struct IUnknown *, struct IUnknown *, IID *, LPVOID *);
	HRESULT (* AddDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* DeleteDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* SetAppData)(struct IUnknown *, DWORD);
	DWORD (* GetAppData)(struct IUnknown *);
	HRESULT (* SetName)(struct IUnknown *, LPCSTR);
	HRESULT (* GetName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* GetClassName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* AddChild)(struct IDirect3DRMFrame3 *, struct IDirect3DRMFrame3 *);
	HRESULT (* AddLight)(struct IDirect3DRMFrame3 *, struct IDirect3DRMLight *);
	pointer AddMoveCallback;
	HRESULT (* AddTransform)(struct IDirect3DRMFrame3 *, enum D3DRMCombineType, struct Matrix4F *);
	HRESULT (* AddTranslation)(struct IDirect3DRMFrame3 *, enum D3DRMCombineType, float, float, float);
	HRESULT (* AddScale)(struct IDirect3DRMFrame3 *, enum D3DRMCombineType, float, float, float);
	HRESULT (* AddRotation)(struct IDirect3DRMFrame3 *, enum D3DRMCombineType, float, float, float, float);
	HRESULT (* AddVisual)(struct IDirect3DRMFrame3 *, struct IDirect3DRMVisual *);
	HRESULT (* GetChildren)(struct IDirect3DRMFrame3 *, struct IDirect3DRMFrameArray * *);
	DWORD (* GetColor)(struct IDirect3DRMFrame3 *);
	HRESULT (* GetLights)(struct IDirect3DRMFrame3 *, struct IDirect3DRMLightArray * *);
	D3DRMMaterialMode (* GetMaterialMode)(struct IDirect3DRMFrame3 *);
	HRESULT (* GetParent)(struct IDirect3DRMFrame3 *, struct IDirect3DRMFrame3 * *);
	HRESULT (* GetPosition)(struct IDirect3DRMFrame3 *, struct IDirect3DRMFrame3 *, struct Vector3F *);
	HRESULT (* GetRotation)(struct IDirect3DRMFrame3 *, struct IDirect3DRMFrame3 *, struct Vector3F *, float *);
	HRESULT (* GetScene)(struct IDirect3DRMFrame3 *, struct IDirect3DRMFrame3 * *);
	D3DRMSortMode (* GetSortMode)(struct IDirect3DRMFrame3 *);
	HRESULT (* GetTexture)(struct IDirect3DRMFrame3 *, struct IDirect3DRMTexture3 * *);
	HRESULT (* GetTransform)(struct IDirect3DRMFrame3 *, struct IDirect3DRMFrame3 *, struct Matrix4F *);
	HRESULT (* GetVelocity)(struct IDirect3DRMFrame3 *, struct IDirect3DRMFrame3 *, struct Vector3F *, BOOL);
	HRESULT (* GetOrientation)(struct IDirect3DRMFrame3 *, struct IDirect3DRMFrame3 *, struct Vector3F *, struct Vector3F *);
	HRESULT (* GetVisuals)(struct IDirect3DRMFrame3 *, DWORD *, struct IDirect3DRMVisual * *);
	HRESULT (* InverseTransform)(struct IDirect3DRMFrame3 *, struct Vector3F *, struct Vector3F *);
	pointer Load;
	HRESULT (* LookAt)(struct IDirect3DRMFrame3 *, struct IDirect3DRMFrame3 *, struct IDirect3DRMFrame3 *, enum D3DRMFrameConstraint);
	HRESULT (* Move)(struct IDirect3DRMFrame3 *, float);
	HRESULT (* DeleteChild)(struct IDirect3DRMFrame3 *, struct IDirect3DRMFrame3 *);
	HRESULT (* DeleteLight)(struct IDirect3DRMFrame3 *, struct IDirect3DRMLight *);
	pointer DeleteMoveCallback;
	HRESULT (* DeleteVisual)(struct IDirect3DRMFrame3 *, struct IDirect3DRMVisual *);
	DWORD (* GetSceneBackground)(struct IDirect3DRMFrame3 *);
	HRESULT (* GetSceneBackgroundDepth)(struct IDirect3DRMFrame3 *, struct IDirectDrawSurface * *);
	DWORD (* GetSceneFogColor)(struct IDirect3DRMFrame3 *);
	BOOL (* GetSceneFogEnable)(struct IDirect3DRMFrame3 *);
	D3DRMFogMode (* GetSceneFogMode)(struct IDirect3DRMFrame3 *);
	HRESULT (* GetSceneFogParams)(struct IDirect3DRMFrame3 *, float *, float *, float *);
	HRESULT (* SetSceneBackground)(struct IDirect3DRMFrame3 *, DWORD);
	HRESULT (* SetSceneBackgroundRGB)(struct IDirect3DRMFrame3 *, float, float, float);
	HRESULT (* SetSceneBackgroundDepth)(struct IDirect3DRMFrame3 *, struct IDirectDrawSurface *);
	HRESULT (* SetSceneBackgroundImage)(struct IDirect3DRMFrame3 *, struct IDirect3DRMTexture3 *);
	HRESULT (* SetSceneFogEnable)(struct IDirect3DRMFrame3 *, BOOL);
	HRESULT (* SetSceneFogColor)(struct IDirect3DRMFrame3 *, DWORD);
	HRESULT (* SetSceneFogMode)(struct IDirect3DRMFrame3 *, enum D3DRMFogMode);
	HRESULT (* SetSceneFogParams)(struct IDirect3DRMFrame3 *, float, float, float);
	HRESULT (* SetColor)(struct IDirect3DRMFrame3 *, DWORD);
	HRESULT (* SetColorRGB)(struct IDirect3DRMFrame3 *, float, float, float);
	D3DRMZBufferMode (* GetZbufferMode)(struct IDirect3DRMFrame3 *);
	HRESULT (* SetMaterialMode)(struct IDirect3DRMFrame3 *, enum D3DRMMaterialMode);
	HRESULT (* SetOrientation)(struct IDirect3DRMFrame3 *, struct IDirect3DRMFrame3 *, float, float, float, float, float, float);
	HRESULT (* SetPosition)(struct IDirect3DRMFrame3 *, struct IDirect3DRMFrame3 *, float, float, float);
	HRESULT (* SetRotation)(struct IDirect3DRMFrame3 *, struct IDirect3DRMFrame3 *, float, float, float, float);
	HRESULT (* SetSortMode)(struct IDirect3DRMFrame3 *, enum D3DRMSortMode);
	HRESULT (* SetTexture)(struct IDirect3DRMFrame3 *, struct IDirect3DRMTexture3 *);
	HRESULT (* SetVelocity)(struct IDirect3DRMFrame3 *, struct IDirect3DRMFrame3 *, float, float, float, BOOL);
	HRESULT (* SetZbufferMode)(struct IDirect3DRMFrame3 *, enum D3DRMZBufferMode);
	pointer Transform;
	pointer GetBox;
	pointer GetBoxEnable;
	pointer GetAxes;
	pointer GetMaterial;
	pointer GetInheritAxes;
	pointer GetHierarchyBox;
	pointer SetBox;
	pointer SetBoxEnable;
	pointer SetAxes;
	pointer SetInheritAxes;
	pointer SetMaterial;
	pointer SetQuaternion;
	pointer RayPick;
	pointer Save;
	pointer TransformVectors; // (unique to IDirect3DRMFrame3)
	pointer InverseTransformVectors; // (unique to IDirect3DRMFrame3)
	pointer SetTraversalOptions; // (unique to IDirect3DRMFrame3)
	pointer GetTraversalOptions; // (unique to IDirect3DRMFrame3)
	HRESULT (* SetSceneFogMethod)(struct IDirect3DRMFrame3 *, enum D3DRMSceneFogMethod); // (unique to IDirect3DRMFrame3)
	HRESULT (* GetSceneFogMethod)(struct IDirect3DRMFrame3 *, enum D3DRMSceneFogMethod *); // (unique to IDirect3DRMFrame3)
	pointer SetMaterialOverride; // (unique to IDirect3DRMFrame3)
	pointer GetMaterialOverride; // (unique to IDirect3DRMFrame3)
};

struct ObjectStats { // [LegoRR/Stats.c|struct:0x150]
	char unused_typeName[30];
	undefined2 padding;
	float RouteSpeed; // (leveled)
	float DrillTimes[18]; // (leveled, table of surface type times)
	float CollRadius; // (effect: flags1 | 0x80)
	float AlertRadius;
	float CollHeight;
	float PickSphere;
	float TrackDist;
	float HealthDecayRate;
	float EnergyDecayRate;
	float RepairValue; // (leveled)
	float RestPercent;
	float CarryMinHealth;
	float StampRadius;
	float AttackRadius;
	float WakeRadius; // (default: 20.0)
	struct Size2F CollBox; // (requires: invalid/no CollRadius, effect: flag 0x100, CollRadius = min(w,h) * 0.5)
	int BuildingBase; // (from: FUN_00408bb0, invalid: -1, either ptr or basenumber)
	int SurveyRadius; // (leveled)
	int CostOre;
	int CostCrystal;
	int CostRefinedOre;
	int CrystalDrain; // (leveled)
	enum SFX_ID DrillSound; // (from: FUN_00464f30, invalid: 2 "SFX_Drill")
	enum SFX_ID DrillFadeSound; // (from: FUN_00464f30, invalid: 3 "SFX_DrillFade")
	enum SFX_ID EngineSound; // (from: FUN_00464f30, invalid: 0 "SFX_Bodge")
	int NumOfToolsCanCarry; // (leveled)
	int WaterEntrances;
	float RubbleCoef; // (default: 1.0)
	float PathCoef; // (default: 1.0)
	float OxygenCoef; // (negative consumes oxygen)
	int Capacity;
	float AwarenessRange; // (default: 0.0)
	float PainThreshold; // (default: 0.0)
	int MaxCarry; // (leveled)
	int CarryStart; // (leveled)
	float UpgradeTime; // (leveled, mult: 25.0)
	float FunctionCoef; // (leveled)
	int UpgradeCostOre; // Carry:Scan:Speed:Drill (requires all 4)
	int UpgradeCostStuds; // Carry:Scan:Speed:Drill (requires all 4)
	float unused_viewAngle;
	float unused_viewDist;
	float FreezerTime; // (default: 0.0)
	float FreezerDamage; // (default: 0.0)
	float PusherDist; // (default: 0.0)
	float PusherDamage; // (default: 0.0)
	float LaserDamage; // (default: 0.0)
	float Flocks_Turn; // (default: 0.06)
	float Flocks_Speed; // (default: 2.0)
	float Flocks_Tightness; // (default: 2.0)
	float Flocks_GoalUpdate; // (default: 2.0)
	float Flocks_Height; // (default: 30.0)
	float Flocks_Randomness; // (default: 2.0)
	float Flocks_AttackTime; // (default: 300.0)
	int Flocks_Size; // (default: 5)
	float RandomMoveTime; // (default: 200.0)
	enum StatsFlags1 flags1;
	enum StatsFlags2 flags2;
	enum StatsFlags3 flags3;
};

struct Container_TypeData { // [Gods98/Containers.c|struct:0x10]
	char * name;
	struct IDirect3DRMLight * light;
	struct IDirect3DRMMesh * mesh;
	struct Mesh * transMesh;
};

struct IDirect3DRMPickedArrayVtbl { // [DirectX/D3DRM.c|struct:0x14|tags:DIRECTX,VFTABLE] Subclass of IDirect3DRMArrayVtbl
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	DWORD (* GetSize)(struct IDirect3DRMPickedArray *);
	HRESULT (* GetPick)(struct IDirect3DRMPickedArray *, DWORD, struct IDirect3DRMVisual * *, struct IDirect3DRMFrameArray * *, struct D3DRMPickDesc *);
};

struct IDirect3DRMViewport2Vtbl { // [DirectX/D3DRM.c|struct:0xa4|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Clone)(struct IUnknown *, struct IUnknown *, IID *, LPVOID *);
	HRESULT (* AddDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* DeleteDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* SetAppData)(struct IUnknown *, DWORD);
	DWORD (* GetAppData)(struct IUnknown *);
	HRESULT (* SetName)(struct IUnknown *, LPCSTR);
	HRESULT (* GetName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* GetClassName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* Init)(struct IDirect3DRMViewport2 *, struct IDirect3DRMDevice3 *, struct IDirect3DRMFrame3 *, int, int, DWORD, DWORD);
	HRESULT (* Clear)(struct IDirect3DRMViewport2 *, enum D3DRMViewportClearOptions);
	HRESULT (* Render)(struct IDirect3DRMViewport2 *, struct IDirect3DRMFrame3 *);
	HRESULT (* SetFront)(struct IDirect3DRMViewport2 *, float);
	HRESULT (* SetBack)(struct IDirect3DRMViewport2 *, float);
	HRESULT (* SetField)(struct IDirect3DRMViewport2 *, float);
	HRESULT (* SetUniformScaling)(struct IDirect3DRMViewport2 *, BOOL);
	HRESULT (* SetCamera)(struct IDirect3DRMViewport2 *, struct IDirect3DRMFrame3 *);
	HRESULT (* SetProjection)(struct IDirect3DRMViewport2 *, enum D3DRMProjectionType);
	HRESULT (* Transform)(struct IDirect3DRMViewport2 *, struct Vector4F *, struct Vector3F *);
	HRESULT (* InverseTransform)(struct IDirect3DRMViewport2 *, struct Vector3F *, struct Vector4F *);
	HRESULT (* Configure)(struct IDirect3DRMViewport2 *, int, int, DWORD, DWORD);
	HRESULT (* ForceUpdate)(struct IDirect3DRMViewport2 *, DWORD, DWORD, DWORD, DWORD);
	HRESULT (* SetPlane)(struct IDirect3DRMViewport2 *, float, float, float, float);
	HRESULT (* GetCamera)(struct IDirect3DRMViewport2 *, struct IDirect3DRMFrame3 * *);
	HRESULT (* GetDevice)(struct IDirect3DRMViewport2 *, struct IDirect3DRMDevice3 * *);
	HRESULT (* GetPlane)(struct IDirect3DRMViewport2 *, float *, float *, float *, float *);
	HRESULT (* Pick)(struct IDirect3DRMViewport2 *, int, int, struct IDirect3DRMPickedArray * *);
	BOOL (* GetUniformScaling)(struct IDirect3DRMViewport2 *);
	int (* GetX)(struct IDirect3DRMViewport2 *);
	int (* GetY)(struct IDirect3DRMViewport2 *);
	DWORD (* GetWidth)(struct IDirect3DRMViewport2 *);
	DWORD (* GetHeight)(struct IDirect3DRMViewport2 *);
	float10 (* GetField)(struct IDirect3DRMViewport2 *);
	float10 (* GetBack)(struct IDirect3DRMViewport2 *);
	float10 (* GetFront)(struct IDirect3DRMViewport2 *);
	D3DRMProjectionType (* GetProjection)(struct IDirect3DRMViewport2 *);
	HRESULT (* GetDirect3DViewport)(struct IDirect3DRMViewport2 *, struct IDirect3DViewport * *);
	HRESULT (* TransformVectors)(struct IDirect3DRMViewport2 *, DWORD, struct Vector4F *, struct Vector3F *);
	HRESULT (* InverseTransformVectors)(struct IDirect3DRMViewport2 *, DWORD, struct Vector3F *, struct Vector4F *);
};

struct ElectricFence_Block { // [LegoRR/ElectricFence.c|struct:0x14|tags:LISTSET]
	struct LegoObject * attachedObject;
	struct Point2I blockPos;
	float timer;
	struct ElectricFence_Block * nextFree; // (for listSet)
};

struct Mesh { // [Gods98/Mesh.c|struct:0x34|tags:LISTSET]
	uint groupCount; // seems to be a count
	uint listSize;
	struct Mesh_Group * groupList; // table ptr? -> 0x10 (struct: 0x70)
	struct IDirect3DRMUserVisual * uv;
	struct Mesh_RenderDesc renderDesc;
	struct Mesh_LightWave_Surface * lightWaveSurf;
	uint numOfRefs;
	struct Mesh * clonedFrom;
	struct IDirect3DRMFrame3 * frameCreatedOn;
	uint flags;
	struct Mesh * nextFree;
};

struct IDirect3DRMMeshVtbl { // [DirectX/D3DRM.c|struct:0x78|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Clone)(struct IUnknown *, struct IUnknown *, IID *, LPVOID *);
	HRESULT (* AddDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* DeleteDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* SetAppData)(struct IUnknown *, DWORD);
	DWORD (* GetAppData)(struct IUnknown *);
	HRESULT (* SetName)(struct IUnknown *, LPCSTR);
	HRESULT (* GetName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* GetClassName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* Scale)(struct IDirect3DRMMesh *, float, float, float);
	HRESULT (* Translate)(struct IDirect3DRMMesh *, float, float, float);
	HRESULT (* GetBox)(struct IDirect3DRMMesh *, struct Box3F *);
	HRESULT (* AddGroup)(struct IDirect3DRMMesh *, DWORD, DWORD, DWORD, void *, enum D3DRMGroupIndex *);
	HRESULT (* SetVertices)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex, DWORD, DWORD, struct Vertex *);
	HRESULT (* SetGroupColor)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex, DWORD);
	HRESULT (* SetGroupColorRGB)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex, float, float, float);
	HRESULT (* SetGroupMapping)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex);
	HRESULT (* SetGroupQuality)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex, enum D3DRMMapping);
	pointer SetGroupMaterial;
	HRESULT (* SetGroupTexture)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex, struct IDirect3DRMTexture *);
	DWORD (* GetGroupCount)(struct IDirect3DRMMesh *);
	HRESULT (* GetGroup)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex, DWORD *, DWORD *, DWORD *, DWORD *, void *);
	HRESULT (* GetVertices)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex, DWORD, DWORD, struct Vertex *);
	DWORD (* GetGroupColor)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex);
	D3DRMMapping (* GetGroupMapping)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex);
	D3DRMRenderQuality (* GetGroupQuality)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex);
	pointer GetGroupMaterial;
	HRESULT (* GetGroupTexture)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex, struct IDirect3DRMTexture * *);
};

struct IDirect3DRMFrame { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMFrameVtbl * lpVtbl;
};

struct UpgradesModel { // [LegoRR/Upgrade.c|struct:0x14]
	struct Upgrade_PartInfo * parts; // always ObjectUpgradePartData[200]
	uint partCount;
	uint currentLevel;
	enum LegoObject_UpgradeFlags levelFlags; // [carry][scan][speed][drill]
	struct LegoObject * firstObject;
};

struct IDirect3DRMTexture3Vtbl { // [DirectX/D3DRM.c|struct:0x98|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Clone)(struct IUnknown *, struct IUnknown *, IID *, LPVOID *);
	HRESULT (* AddDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* DeleteDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* SetAppData)(struct IUnknown *, DWORD);
	DWORD (* GetAppData)(struct IUnknown *);
	HRESULT (* SetName)(struct IUnknown *, LPCSTR);
	HRESULT (* GetName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* GetClassName)(struct IUnknown *, LPDWORD, LPSTR);
	pointer InitFromFile;
	pointer InitFromSurface;
	pointer InitFromResource;
	pointer Changed;
	pointer SetColors;
	pointer SetShades;
	pointer SetDecalSize;
	pointer SetDecalOrigin;
	pointer SetDecalScale;
	HRESULT (* SetDecalTransparency)(struct IDirect3DRMTexture3 *, BOOL);
	HRESULT (* SetDecalTransparentColor)(struct IDirect3DRMTexture3 *, DWORD);
	pointer GetDecalSize;
	pointer GetDecalOrigin;
	D3DRMImage * (* GetImage)(struct IDirect3DRMTexture3 *);
	pointer GetShades;
	pointer GetColors;
	pointer GetDecalScale;
	pointer GetDecalTransparency;
	pointer GetDecalTransparentColor;
	pointer InitFromImage;
	pointer InitFromResource2;
	pointer GenerateMIPMap;
	pointer GetSurface;
	pointer SetCacheOptions;
	pointer GetCacheOptions;
	pointer SetDownsampleCallback;
	pointer SetValidationCallback;
};

struct ColourRGBAF { // [common.c|struct:0x10]
	float red;
	float green;
	float blue;
	float alpha;
};

struct D3DMaterial { // [DirectX/D3D.c|struct:0x50|tags:DIRECTX]
	DWORD dwSize;
	struct ColourRGBAF diffuse;
	struct ColourRGBAF ambient;
	struct ColourRGBAF specular;
	struct ColourRGBAF emissive;
	float power;
	DWORD hTexture;
	DWORD dwRampSize;
};

struct Mesh_Group { // [Gods98/Mesh.c|struct:0x70]
	uint faceDataSize;
	uint vertexCount;
	ushort * faceData;
	struct Mesh_Vertex * vertices;
	struct D3DMaterial material;
	struct IDirect3DTexture2 * imText;
	uint renderFlags;
	struct Mesh_LightWave_Surface * lightWaveSurfaceInfo;
	uint flags;
};

struct WeaponsModel { // [LegoRR/Weapons.c|struct:0xa8]
	struct Container * fireNullPairs[3][2];
	struct Container * xPivotNulls[3];
	struct Container * yPivotNulls[3];
	float pivotMaxZ; // (ae: PivotMaxZ)
	float pivotMinZ; // (ae: PivotMinZ)
	BOOL fireNullPairFrames[3]; // (valid: [0,1])
	struct Vector3F fireDirections[3];
	struct Vector3F targetWorldPoses[3];
	struct Upgrade_PartInfo * parts[3];
	float timers[3];
	uint count;
};

struct VehicleModel { // [LegoRR/Vehicle.c|struct:0x1ec]
	LegoObject_ID objID;
	char * wheelNullName; // (ae: WheelNullName)
	struct Container * contAct1; // (ACT, true)
	struct Container * contAct2; // (ACT, true) Optional second ae file (seen for Grannit Grinder legs) This container has priority for finding null frames
	struct Container * contWheels[6]; // (ae:WheelMesh, LWO, false) Table for wheel nulls that are assigned a position calculated by wheelRefNulls
	struct Container * wheelNulls[6]; // Root wheel nulls that are used to calculate terrain-relative positioning
	uint wheelNullFrames;
	undefined reserved1[24];
	struct Vector3F wheelLastUp; // Last up orientation of vehicle with wheels.
	float wheelRadius; // (ae: WheelRadius)
	struct Vector3F wheelLastPositions[6]; // Last position of wheelNulls, used to calculate wheel turning.
	char * drillNullName; // (ae: DrillNullName)
	char * depositNullName; // (ae: DepositNullName)
	char * fireNullName; // (ae: FireNullName) "fire laser"
	char * driverNullName; // (ae: DriverNullName) 
	char * yPivot; // (ae: xPivot)
	char * xPivot; // (ae: yPivot)
	struct Container * drillNull;
	struct Container * depositNull;
	struct Container * driverNull;
	enum BoolTri cameraFlipDir; // (ae: CameraFlipDir)
	char * carryNullName; // (ae: CarryNullName)
	char * cameraNullName; // (ae: CameraNullName)
	struct Container * carryNulls[7];
	undefined reserved2[12];
	struct Container * cameraNulls[4];
	uint carryNullFrames; // (ae: CarryNullFrames)
	uint cameraNullFrames; // (ae: CameraNullFrames)
	struct UpgradesModel upgrades;
	struct WeaponsModel weapons;
	struct MeshLOD * polyMedium1; // (ae: MediumPoly from contAct1)
	struct MeshLOD * polyMedium2; // (ae: MediumPoly from contAct2)
	enum VehicleFlags flags; // (0x1: original that holds memory, 0x4: ?, 0x8: HoldMissing TRUE)
};

struct IDirect3DTexture2Vtbl { // [DirectX/D3D.c|struct:0x18|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer GetHandle;
	pointer PaletteChanged;
	pointer Load;
};

struct Upgrade_PartModel { // [LegoRR/Upgrade.c|struct:0x10]
	LegoObject_ID objID;
	struct Container * cont; // (LWO|ACT|MESH, true)
	struct LegoObject * nextObject;
	struct Upgrade_PartInfo * partInfo; // (not too sure about this type match)
};

struct Vector4F { // [common.c|struct:0x10] D3DRMVector4D
	float x;
	float y;
	float z;
	float w;
};

struct IDirect3DRMLightArray { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMLightArrayVtbl * lpVtbl;
};

struct IDirect3DRMVisual { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE] Identical to IDirect3DRMObject
	struct IDirect3DRMVisualVtbl * lpVtbl;
};

struct CreatureModel { // [LegoRR/Creature.c|struct:0x74] Possibly alphabetically correct names: Bipedal, BasicUnit, etc... (has to be before Bubble, and possible after BezierCurve or AI(Task?))
	LegoObject_ID objID;
	struct Container * contAct; // (ACT, true)
	undefined reserved1[24];
	char * cameraNullName; // (ae: CameraNullName)
	uint cameraNullFrames; // (ae: CameraNullFrames)
	enum BoolTri cameraFlipDir; // (ae: CameraFlipDir)
	char * drillNullName; // (ae: DrillNullName)
	char * footStepNullName; // (ae: FootStepNullName)
	char * carryNullName; // (ae: CarryNullName)
	char * throwNullName; // (ae: ThrowNullName)
	char * depositNullName; // (ae: DepositNullName)
	struct Container * drillNull;
	struct Container * footStepNull; // (unused)
	struct Container * carryNull;
	struct Container * throwNull;
	struct Container * depositNull;
	struct Container * cameraNulls[4];
	struct MeshLOD * polyMedium; // (ae: MediumPoly)
	struct MeshLOD * polyHigh; // (ae: HighPoly)
	struct MeshLOD * polyFP; // (ae: FPPoly::Camera#)
	enum CreatureFlags flags; // (0x1: original that holds memory)
};

struct Flocks { // [LegoRR/Flocks.c|struct:0x28] The singular flocks unit, which holds all items flying within it.
	struct FlocksItem * flocksSubdata1; // (is this a doubly-linked list?)
	struct FlocksItem * flocksSubdata2;
	uint numSubdata;
	BOOL hasVector1;
	BOOL hasVector2;
	undefined4 field_14;
	float floatx_18;
	undefined4 field_1c;
	float floaty_20;
	enum FlocksFlags flags; // (observed flags: 0x1, )
};

struct IDirect3DRMDevice3Vtbl { // [DirectX/D3DRM.c|struct:0xb0|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Clone)(struct IUnknown *, struct IUnknown *, IID *, LPVOID *);
	HRESULT (* AddDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* DeleteDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* SetAppData)(struct IUnknown *, DWORD);
	DWORD (* GetAppData)(struct IUnknown *);
	HRESULT (* SetName)(struct IUnknown *, LPCSTR);
	HRESULT (* GetName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* GetClassName)(struct IUnknown *, LPDWORD, LPSTR);
	pointer Init;
	pointer InitFromD3D;
	pointer InitFromClipper;
	pointer Update;
	pointer AddUpdateCallback;
	pointer DeleteUpdateCallback;
	pointer SetBufferCount;
	pointer GetBufferCount;
	HRESULT (* SetDither)(struct IDirect3DRMDevice3 *, BOOL);
	pointer SetShades;
	HRESULT (* SetQuality)(struct IDirect3DRMDevice3 *, DWORD);
	HRESULT (* SetTextureQuality)(struct IDirect3DRMDevice3 *, DWORD);
	pointer GetViewports;
	pointer GetDither;
	pointer GetShades;
	pointer GetHeight;
	pointer GetWidth;
	pointer GetTrianglesDrawn;
	pointer GetWireframeOptions;
	pointer GetQuality;
	pointer GetColorModel;
	pointer GetTextureQuality;
	pointer GetDirect3DDevice;
	pointer InitFromD3D2;
	pointer InitFromSurface;
	pointer SetRenderMode;
	pointer GetRenderMode;
	pointer GetDirect3DDevice2;
	HRESULT (* FindPreferredTextureFormat)(struct IDirect3DRMDevice3 *, DWORD, DWORD, struct DDPIXELFORMAT *);
	pointer RenderStateChange;
	pointer LightStateChange;
	pointer GetStateChangeOptions;
	pointer SetStateChangeOptions;
};

struct IDirect3DViewport { // [DirectX/D3D.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DViewportVtbl * lpVtbl;
};

struct IDirect3DRMVisualVtbl { // [DirectX/D3DRM.c|struct:0x2c|tags:DIRECTX,VFTABLE] Identical to IDirect3DRMObjectVtbl
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Clone)(struct IUnknown *, struct IUnknown *, IID *, LPVOID *);
	HRESULT (* AddDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* DeleteDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* SetAppData)(struct IUnknown *, DWORD);
	DWORD (* GetAppData)(struct IUnknown *);
	HRESULT (* SetName)(struct IUnknown *, LPCSTR);
	HRESULT (* GetName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* GetClassName)(struct IUnknown *, LPDWORD, LPSTR);
};

struct IDirect3DRMUserVisual { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMUserVisualVtbl * lpVtbl;
};

struct IDirect3DRMMesh { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMMeshVtbl * lpVtbl;
};

struct Vertex { // [common.c|struct:0x24] Vertex3F, Extension of D3DVertex with color field
	struct Vector3F position; // Homogeneous coordinates
	struct Vector3F normal; // Normal
	float tu; // Texture coordinates
	float tv; // Texture coordinates
	uint colour;
};

struct D3DRMImage { // [DirectX/D3DRM.c|struct:0x3c|tags:DIRECTX]
	int width; // width in pixels
	int height; // height in pixels
	int aspectx; // aspect ratio for non-square pixels
	int aspecty; // aspect ratio for non-square pixels
	int depth; // (bitDepth) bits per pixel
	BOOL rgb; // if false, pixels are indices into a palette
	int bytes_per_line; // (stride) number of bytes of memory for a scanline. This must be a multiple of 4.
	byte * buffer1; // memory to render into (first buffer)
	byte * buffer2; // for double-buffering
	DWORD red_mask; // 0xfc (8-bit only)
	DWORD green_mask; // 0xfc (8-bit only)
	DWORD blue_mask; // 0xfc (8-bit only)
	DWORD alpha_mask; // 0xfc (8-bit only)
	int palette_size; // number of entries in palette
	struct D3DRMPaletteEntry * palette; // always allocated to size[256]
};

struct Mesh_Vertex { // [Gods98/Mesh.c|struct:0x20] Untransformed/unlit vertices
	struct Vector3F position; // Homogeneous coordinates
	struct Vector3F normal; // Normal
	float tu; // Texture coordinates
	float tv; // Texture coordinates
};

struct IDirect3DTexture2 { // [DirectX/D3D.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DTexture2Vtbl * lpVtbl;
};

struct TeleporterService { // [LegoRR/Teleporter.c|struct:0x20]
	struct Point2F cameraPos; // (init: if flags 0x2)
	float float_8; // (init: 0 if flags 0x2)
	float float_c; // (init: 3.0 if flags 0x2)
	uint count; // (init: 0)
	int int_14; // (init: 40 if flags 0x1)
	uint flags; // (init: flags)
	struct TeleporterService * next;
};

struct IDirect3DRMLightArrayVtbl { // [DirectX/D3DRM.c|struct:0x14|tags:DIRECTX,VFTABLE] Subclass of IDirect3DRMArrayVtbl
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	DWORD (* GetSize)(struct IDirect3DRMLightArray *);
	HRESULT (* GetElement)(struct IDirect3DRMLightArray *, DWORD, struct IDirect3DRMLight * *);
};

struct BuildingModel { // [LegoRR/Building.c|struct:0x14c]
	LegoObject_ID objID;
	struct Container * contAct; // (ACT, true)
	char * carryNullName; // (ae: CarryNullName)
	char * cameraNullName; // (ae: CameraNullName)
	char * depositNullName; // (ae: DepositNullName)
	char * entranceNullName; // (ae: EntranceNullName)
	char * toolNullName; // (ae: ToolNullName)
	char * fireNullName; // (ae: FireNullName) "fire laser"
	char * yPivot; // (ae: yPivot)
	char * xPivot; // (ae: xPivot)
	struct Container * carryNulls[6];
	struct Container * cameraNulls[4];
	struct Container * toolNulls[6]; // (note: index five is never observed may be array size [5])
	struct Container * depositNull;
	struct Container * entranceNull;
	uint carryNullFrames; // (ae: CarryNullFrames)
	uint cameraNullFrames; // (ae: CameraNullFrames)
	uint toolNullFrames; // (ae: ToolNullFrames)
	struct Container * contPowerLevel; // (ae: PowerLevelScene, LWS, true) Scene used as some sort of power meter with diminishing returns during increment.
	float powerLevel;
	struct Point2I * shapePoints; // (ae: Shape) Point2I[10]
	uint shapeCount; // (ae: Shape)
	struct UpgradesModel upgrades;
	struct WeaponsModel weapons;
	enum BuildingFlags flags; // (0x1: original that holds memory [broken], 0x2: PowerLevel scene playing)
};

struct IDirect3DRMLight { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMLightVtbl * lpVtbl;
};

struct Matrix4F { // [common.c|struct:0x40]
	float values[4][4];
};

struct AITask { // [LegoRR/AITask.c|struct:0x68|tags:LISTSET]
	enum AITask_Type taskType;
	struct AITask * referrerTask; // Passed from certain Message_Events. Assigned but never used.
	struct Point2I blockPos;
	struct LegoObject * targetObject;
	float time; // Count-down timer.
	float timeIn; // Count-down timer.
	int priorityValue; // Field is known to be signed (range: 0,99).
	enum LegoObject_Type objType;
	LegoObject_ID objID;
	uint objLevel;
	uint constructHandle;
	struct Point2F blockOffset;
	enum LegoObject_ToolType toolType;
	enum LegoObject_AbilityType trainFlags;
	struct LegoObject * * unitList;
	uint unitListCount;
	struct LegoObject * assignedToObject; // Likely related to tasks with a two-object relation. Like training at a building.
	enum AI_Priority priorityType;
	uint creationTime; // Timestamp of task creation in `AITask_Create`, obtained from `Main_GetTime()`.
	enum Message_Type completeAction;
	struct AITask * getToolTask; // (bi-directional link between GetTool and GetTool_FromText)
	enum AITaskFlags flags;
	struct AITask * next; // Next in linked lists for `aiGlobs.AITaskUnkPtr`, `aiGlobs.AITaskDataNext`, and `LegoObject::aiTask`.
	struct AITask * nextFree; // (for listSet)
};

struct IDirect3DRMLightVtbl { // [DirectX/D3DRM.c|struct:0x78|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Clone)(struct IUnknown *, struct IUnknown *, IID *, LPVOID *);
	HRESULT (* AddDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* DeleteDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* SetAppData)(struct IUnknown *, DWORD);
	DWORD (* GetAppData)(struct IUnknown *);
	HRESULT (* SetName)(struct IUnknown *, LPCSTR);
	HRESULT (* GetName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* GetClassName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* SetType)(struct IDirect3DRMLight *, enum D3DRMLightType);
	HRESULT (* SetColor)(struct IDirect3DRMLight *, DWORD);
	HRESULT (* SetColorRGB)(struct IDirect3DRMLight *, float, float, float);
	HRESULT (* SetRange)(struct IDirect3DRMLight *, float);
	HRESULT (* SetUmbra)(struct IDirect3DRMLight *, float);
	HRESULT (* SetPenumbra)(struct IDirect3DRMLight *, float);
	HRESULT (* SetConstantAttenuation)(struct IDirect3DRMLight *, float);
	HRESULT (* SetLinearAttenuation)(struct IDirect3DRMLight *, float);
	HRESULT (* SetQuadraticAttenuation)(struct IDirect3DRMLight *, float);
	float10 (* GetRange)(struct IDirect3DRMLight *);
	float10 (* GetUmbra)(struct IDirect3DRMLight *);
	float10 (* GetPenumbra)(struct IDirect3DRMLight *);
	float10 (* GetConstantAttenuation)(struct IDirect3DRMLight *);
	float10 (* GetLinearAttenuation)(struct IDirect3DRMLight *);
	float10 (* GetQuadraticAttenuation)(struct IDirect3DRMLight *);
	DWORD (* GetColor)(struct IDirect3DRMLight *);
	D3DRMLightType (* GetType)(struct IDirect3DRMLight *);
	HRESULT (* SetEnableFrame)(struct IDirect3DRMLight *, struct IDirect3DRMFrame *);
	HRESULT (* GetEnableFrame)(struct IDirect3DRMLight *, struct IDirect3DRMFrame * *);
};

struct Container_Texture { // [Gods98/Containers.c|struct:0xc]
	struct IDirectDrawSurface4 * surface;
	struct IDirect3DRMTexture3 * texture;
	BOOL colourKey;
};

struct IDirect3DRMViewport2 { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMViewport2Vtbl * lpVtbl;
};

struct IDirect3DRMTexture { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMTextureVtbl * lpVtbl;
};

struct Viewport { // [Gods98/Viewports.c|struct:0x20|tags:LISTSET]
	float xoffset; // Position on viewport normalised to between 0.0 and 1.0
	float yoffset; // Position on viewport normalised to between 0.0 and 1.0
	float width; // Width and height of the viewport normalised as above
	float height; // Width and height of the viewport normalised as above
	struct IDirect3DRMViewport2 * lpVP; // Pointer to D3D(RM) viewport interface
	float smoothFOV; // (init: 0)
	BOOL rendering;
	struct Viewport * nextFree;
};

struct MeshLOD { // [LegoRR/MeshPoly.c|struct:0x18]
	struct Container * contMeshOrigin; // (LWO|MESH, true)
	struct Container * contMeshTarget;
	char * partName; // name of LoadObject file.lwo
	uint setID; // MeshLOD's may contain multiple sets of the same parts, this specifies which set its from.
	enum MeshLODFlags flags; // (1 = dont free partName/cont_0,  2 = unk dtor behavior)
	struct MeshLOD * next;
};

struct Upgrade_PartInfo { // [LegoRR/Upgrade.c|struct:0x14]
	uint level; // (ae: key Level%i%i%i%i)
	uint nullFrameNo; // (ae: value[1])
	char * nullObjectName; // (ae: value[0])
	char * weaponName; // (ae: value[2], optional)
	struct Upgrade_PartModel * upgradeData;
};

struct IDirectDrawSurface { // [DirectX/DDraw.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirectDrawSurfaceVtbl * lpVtbl;
};

struct IDirect3DRMDevice3 { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMDevice3Vtbl * lpVtbl;
};

struct IDirect3DRMFrameVtbl { // [DirectX/D3DRM.c|struct:0x114|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Clone)(struct IUnknown *, struct IUnknown *, IID *, LPVOID *);
	HRESULT (* AddDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* DeleteDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* SetAppData)(struct IUnknown *, DWORD);
	DWORD (* GetAppData)(struct IUnknown *);
	HRESULT (* SetName)(struct IUnknown *, LPCSTR);
	HRESULT (* GetName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* GetClassName)(struct IUnknown *, LPDWORD, LPSTR);
	pointer AddChild;
	pointer AddLight;
	pointer AddMoveCallback;
	pointer AddTransform;
	pointer AddTranslation;
	pointer AddScale;
	pointer AddRotation;
	pointer AddVisual;
	pointer GetChildren;
	pointer GetColor;
	pointer GetLights;
	pointer GetMaterialMode;
	pointer GetParent;
	pointer GetPosition;
	pointer GetRotation;
	pointer GetScene;
	pointer GetSortMode;
	pointer GetTexture;
	pointer GetTransform;
	pointer GetVelocity;
	pointer GetOrientation;
	pointer GetVisuals;
	pointer GetTextureTopology; // (unique to IDirect3DRMFrame)
	pointer InverseTransform;
	pointer Load;
	pointer LookAt;
	pointer Move;
	pointer DeleteChild;
	pointer DeleteLight;
	pointer DeleteMoveCallback;
	pointer DeleteVisual;
	pointer GetSceneBackground;
	pointer GetSceneBackgroundDepth;
	pointer GetSceneFogColor;
	pointer GetSceneFogEnable;
	pointer GetSceneFogMode;
	pointer GetSceneFogParams;
	pointer SetSceneBackground;
	pointer SetSceneBackgroundRGB;
	pointer SetSceneBackgroundDepth;
	pointer SetSceneBackgroundImage;
	pointer SetSceneFogEnable;
	pointer SetSceneFogColor;
	pointer SetSceneFogMode;
	pointer SetSceneFogParams;
	pointer SetColor;
	pointer SetColorRGB;
	pointer GetZbufferMode;
	pointer SetMaterialMode;
	pointer SetOrientation;
	pointer SetPosition;
	pointer SetRotation;
	pointer SetSortMode;
	pointer SetTexture;
	pointer SetTextureTopology; // (unique to IDirect3DRMFrame)
	pointer SetVelocity;
	pointer SetZbufferMode;
	pointer Transform; // (last of IDirect3DRMFrame)
};

struct D3DRMPickDesc { // [DirectX/D3DRM.c|struct:0x14|tags:DIRECTX]
	DWORD ulFaceIdx;
	enum D3DRMGroupIndex lGroupIdx;
	struct Vector3F vPosition;
};

struct FlocksItem { // [LegoRR/Flocks.c|struct:0xa0]  An individual item flying in a single Flocks unit.
	struct Vector3F vector_0;
	struct Vector3F vector_c;
	struct Vector3F vector_18;
	float rotationY_24;
	float rotationX_28;
	float rotationZ_2c;
	float float_30;
	float float_34;
	float GoalUpdate1;
	float Turn1;
	float Speed1;
	float Tightness1;
	float GoalUpdate2;
	float Turn2;
	float Speed2;
	float Tightness2;
	struct Matrix4F matrix;
	struct Container * cont;
	struct FlocksItem * subdataNext;
};

struct IDirect3DRMFrameArrayVtbl { // [DirectX/D3DRM.c|struct:0x14|tags:DIRECTX,VFTABLE] Subclass of IDirect3DRMArrayVtbl
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	DWORD (* GetSize)(struct IDirect3DRMFrameArray *);
	HRESULT (* GetElement)(struct IDirect3DRMFrameArray *, DWORD, struct IDirect3DRMFrame * *);
};

struct IDirect3DRMUserVisualVtbl { // [DirectX/D3DRM.c|struct:0x30|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Clone)(struct IUnknown *, struct IUnknown *, IID *, LPVOID *);
	HRESULT (* AddDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* DeleteDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* SetAppData)(struct IUnknown *, DWORD);
	DWORD (* GetAppData)(struct IUnknown *);
	HRESULT (* SetName)(struct IUnknown *, LPCSTR);
	HRESULT (* GetName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* GetClassName)(struct IUnknown *, LPDWORD, LPSTR);
	pointer Init;
};

struct Mesh_LightWave_Surface { // [Gods98/Mesh.c|struct:0x3c]
	struct Container_Texture * * textureSeq;
	struct Container_Texture * texture;
	uint numInTexSeq;
	struct ColourRGBAF colour;
	float diffuse;
	float emissive;
	float specular;
	float power;
	float transparency;
	uint flags;
	uint texFlags;
	int texSeqOffset;
};

struct LegoObject { // [LegoRR/LegoObject.c|struct:0x40c|tags:LISTSET]
	enum LegoObject_Type type;
	LegoObject_ID id;
	char * customName; // max size is 11 (NOT null-terminated)
	struct VehicleModel * vehicle; // Model for vehicle objects only.
	struct CreatureModel * miniFigure; // Model for mini-figure objects only.
	struct CreatureModel * rockMonster; // Model for monster objects only.
	struct BuildingModel * building; // Model for building objects only.
	struct Container * other; // Model for simple objects only.
	struct Upgrade_PartModel * upgradePart; // First upgrade part model in linked list of parts.
	struct RoutingBlock * routeBlocks; // Unknown pointer, likely in large allocated table
	uint routeBlocksTotal; // total blocks to travel for current route
	uint routeBlocksCurrent; // number of blocks traveled (up to routingBlocksTotal)
	struct BezierCurve routeCurve; // BezierCurve/Catmull-rom spline data
	float routeCurveTotalDist;
	float routeCurveCurrDist;
	float routeCurveInitialDist; // Used as spill-over when distance traveled is beyond routeCurveTotalDist.
	struct Point2F point_298;
	struct Vector3F tempPosition; // Last position used for finding new face direction when moving.
	struct Vector3F faceDirection; // 1.0 to -1.0 directions that determine rotation with atan2
	float faceDirectionLength; // faceDirection length (faceDirection may be Vector4F...)
	int strafeSignFP; // (direction sign only, does higher numbers do not affect speed)
	int forwardSignFP; // (direction sign only, does higher numbers do not affect speed)
	float rotateSpeedFP;
	struct Vector3F dirVector_2c8; // Always (0.0f, 0.0f, 0.0f)
	float animTime;
	uint animRepeat; // Number of times an activity animation is set to repeat (i.e. number of jumping jacks/reinforce hits). Zero is default.
	struct Container * cameraNull;
	uint cameraFrame;
	struct Container * contMiniTeleportUp;
	char * activityName1;
	char * activityName2; // Seems to be used with related objects like driven, swapped with activityName1.
	struct AITask * aiTask; // Linked list of tasks (or null). Linked using the `AITask::next` field.
	struct Point2F targetBlockPos; // (init: -1.0f, -1.0f)
	struct LegoObject * routeToObject;
	struct LegoObject * interactObject; // Used in combination with routeToObject for Upgrade station and RM boulders.
	struct LegoObject * carryingThisObject;
	struct LegoObject * carriedObjects[6]; // (includes carried vehicles)
	uint carryingIndex; // Index of carried object in holder's carriedObjects list.
	uint numCarriedObjects;
	uint carryNullFrames;
	struct Flocks * flocks;
	uint objLevel;
	struct ObjectStats * stats;
	float aiTimer_338;
	float carryRestTimer_33c;
	float health; // (init: -1.0f)
	float energy; // (init: -1.0f)
	int * stolenCrystalLevels; // (alloc: new int[6]) Each element is the count stolen for a level, index 0 only seems to be used for recovery
	enum LOD_PolyLevel polyLOD;
	int drillSoundHandle; // Handle returned by SFX_Play functions
	int engineSoundHandle; // Handle returned by SFX_Play functions
	float weaponSlowDeath;
	uint weaponID;
	float weaponRechargeTimer;
	struct LegoObject * freezeObject; // (bi-directional link between frozen RockMonster and IceCube)
	float freezeTimer;
	struct LegoObject * driveObject; // (bi-directional link between driver and driven)
	enum LegoObject_ToolType carriedTools[5];
	uint numCarriedTools;
	float bubbleTimer;
	struct Image * bubbleImage;
	uint teleporter_modeFlags;
	uint teleporter_teleportFlags;
	struct TeleporterService * teleporter;
	struct Vector3F beamVector_39c; // (used for unkWeaponTypes 1-3 "Lazer", "Pusher", "Freezer")
	struct Vector3F weaponVector_3a8; // (used for unkWeaponType 4 "Lazer")
	struct Point2F pushingVec2D;
	float pushingDist;
	struct LegoObject * throwObject; // (bi-directional link between thrower and thrown)
	struct LegoObject * projectileObject; // Projectile fired from weapon.
	undefined4 field_3c8; // (unused?)
	struct LegoObject * teleportDownObject;
	float damageNumbers; // Used to display damage text over objects.
	float elapsedTime1; // elapsed time counter 1
	float elapsedTime2; // elapsed time counter 2
	float eatWaitTimer; // Unit will try to find food once the timer reaches 125.
	enum LiveFlags1 flags1; // State flags for the object's current activity/behavior.
	enum LiveFlags2 flags2;
	enum LiveFlags3 flags3;
	enum LiveFlags4 flags4;
	enum LegoObject_AbilityFlags abilityFlags; // (orig: flags5) Trained ability flags, and saved in ObjectRecall.
	undefined4 field_3f4; // (set to zero with tool equipped and never read?)
	BOOL bool_3f8;
	float hurtSoundTimer; // Timer resets after reaching (hurtSoundDuration x 2)
	float hurtSoundDuration;
	enum LegoObject_UpgradeType upgradingType; // New upgrade type added as mask to vehicle level when upgrade is finished.
	struct LegoObject * nextFree; // (for listSet)
};

typedef struct InfoMessageInstance InfoMessageInstance, *PInfoMessageInstance;

typedef BOOL (* InfoEnumerateCallback)(struct InfoMessageInstance *, void *);

struct InfoMessageInstance { // [LegoRR/Info.c|struct:0x14]
	struct Point2I blockPos; // (-1, -1) for NULL blockPos
	struct LegoObject * object;
	char * text;
	struct InfoMessageInstance * next;
};

typedef int (* QsortCompare)(void *, void *);

typedef void (* FlocksCallback)(struct Flocks *, struct FlocksItem *, void *);

typedef BOOL (* AITask_RunThroughListsCallback)(struct AITask *, void *);

typedef struct Map3D Map3D, *PMap3D;

typedef float10 (* GetWorldZCallback)(float, float, struct Map3D *);

typedef struct Map3D_Block Map3D_Block, *PMap3D_Block;

typedef struct Detail_TextureSet Detail_TextureSet, *PDetail_TextureSet;

typedef struct IDirect3DRMMaterial2 IDirect3DRMMaterial2, *PIDirect3DRMMaterial2;

typedef struct Coord2U Coord2U, *PCoord2U;

typedef struct Map3D_TransitionBlock Map3D_TransitionBlock, *PMap3D_TransitionBlock;

typedef enum Map3DFlags { // [LegoRR/Map3D.c|flags:0x4|type:uint]
	MAP3D_FLAG_EMISSIVE_4=4,
	MAP3D_FLAG_NONE=0,
	MAP3D_FLAG_VERTEXMODIFIED=2
} Map3DFlags;

typedef enum SurfaceTexture { // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE,COORDNIBBLE]
	TEXTURE_DIAGONAL_STD=119,
	TEXTURE_FLOOR_07=7,
	TEXTURE_FLOOR_ERODE_HIGH=38,
	TEXTURE_FLOOR_ERODE_LOW=6,
	TEXTURE_FLOOR_ERODE_MAX=54,
	TEXTURE_FLOOR_ERODE_MED=22,
	TEXTURE_FLOOR_LAVA=70,
	TEXTURE_FLOOR_LAVA_NOTHOT=71,
	TEXTURE_FLOOR_PATH_1SIDES=101,
	TEXTURE_FLOOR_PATH_2SIDES=98,
	TEXTURE_FLOOR_PATH_3SIDES=100,
	TEXTURE_FLOOR_PATH_4SIDES=96,
	TEXTURE_FLOOR_PATH_CORNER=99,
	TEXTURE_FLOOR_PATH_FOUNDATION=118,
	TEXTURE_FLOOR_PATH_LAYED=97,
	TEXTURE_FLOOR_POWERED_1SIDES=117,
	TEXTURE_FLOOR_POWERED_2SIDES=114,
	TEXTURE_FLOOR_POWERED_3SIDES=116,
	TEXTURE_FLOOR_POWERED_4SIDES=113,
	TEXTURE_FLOOR_POWERED_CORNER=115,
	TEXTURE_FLOOR_POWERED_FOUNDATION=102,
	TEXTURE_FLOOR_RUBBLE_HIGH=17,
	TEXTURE_FLOOR_RUBBLE_LOW=19,
	TEXTURE_FLOOR_RUBBLE_MAX=16,
	TEXTURE_FLOOR_RUBBLE_MED=18,
	TEXTURE_FLOOR_SLUGHOLE=48,
	TEXTURE_FLOOR_STD=0,
	TEXTURE_FLOOR_WATER=69,
	TEXTURE_INCORNER_HARD=52,
	TEXTURE_INCORNER_IMM=53,
	TEXTURE_INCORNER_LOOSE=50,
	TEXTURE_INCORNER_MED=51,
	TEXTURE_INCORNER_SOIL=49,
	TEXTURE_OUTCORNER_HARD=84,
	TEXTURE_OUTCORNER_IMM=85,
	TEXTURE_OUTCORNER_LOOSE=82,
	TEXTURE_OUTCORNER_MED=83,
	TEXTURE_OUTCORNER_SOIL=81,
	TEXTURE_REINWALL_HARD=36,
	TEXTURE_REINWALL_IMM=37,
	TEXTURE_REINWALL_LOOSE=34,
	TEXTURE_REINWALL_MED=35,
	TEXTURE_REINWALL_SOIL=33,
	TEXTURE_ROOF_STD=112,
	TEXTURE_WALL_CRYSTALSEAM=32,
	TEXTURE_WALL_HARD=4,
	TEXTURE_WALL_IMM=5,
	TEXTURE_WALL_LOOSE=2,
	TEXTURE_WALL_MED=3,
	TEXTURE_WALL_ORESEAM=64,
	TEXTURE_WALL_RECHARGESEAM=103,
	TEXTURE_WALL_SOIL=1,
	TEXTURE__INVALID=255
} SurfaceTexture;

typedef enum Map3D_BlockFlags { // [LegoRR/Map3D.c|flags:0x1|type:byte] Flags for SurfaceMapStruct_28->byte_19
	MAP3DBLOCK_FLAG_NONE=0,
	MAP3DBLOCK_FLAG_ROTATED=1,
	MAP3DBLOCK_FLAG_UNK_20=32,
	MAP3DBLOCK_FLAG_UNK_40=64,
	MAP3DBLOCK_FLAG_UVWOBBLES=16,
	MAP3DBLOCK_FLAG_VERTEXLEVELED=8,
	MAP3DBLOCK_FLAG_VERTEXMODIFIED=4
} Map3D_BlockFlags;

typedef struct Size2I Size2I, *PSize2I;

typedef struct IDirect3DRMMaterial2Vtbl IDirect3DRMMaterial2Vtbl, *PIDirect3DRMMaterial2Vtbl;

typedef enum Map3D_TransitionFlags { // [LegoRR/Map3D.c|flags:0x1|type:byte]
	MAP3DTRANS_FLAG_NONE=0,
	MAP3DTRANS_FLAG_USED=1
} Map3D_TransitionFlags;

struct Coord2U { // [common.c|struct:0x4] Point2U structure using short-sized integers (name is based off the WINAPI console structure COORD, using the same layout)
	ushort x;
	ushort y;
};

struct Map3D_TransitionBlock { // [LegoRR/Map3D.c|struct:0x38]
	enum D3DRMGroupIndex groupID; // (init: -1, no group created yet)
	float timer; // count-up timer [0.05f-1.0f]
	struct Point2I blockPos;
	struct Point2F uvCoords[4];
	undefined4 reserved1;
	enum Map3D_TransitionFlags flags; // (0x1 = visible, only flag)
	undefined1 padding1[3];
};

struct Size2I { // [common.c|struct:0x8]
	int width;
	int height;
};

struct IDirect3DRMMaterial2Vtbl { // [DirectX/D3DRM.c|struct:0x4c|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Clone)(struct IUnknown *, struct IUnknown *, IID *, LPVOID *);
	HRESULT (* AddDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* DeleteDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* SetAppData)(struct IUnknown *, DWORD);
	DWORD (* GetAppData)(struct IUnknown *);
	HRESULT (* SetName)(struct IUnknown *, LPCSTR);
	HRESULT (* GetName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* GetClassName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* SetPower)(struct IDirect3DRMMaterial2 *, float);
	HRESULT (* SetSpecular)(struct IDirect3DRMMaterial2 *, float, float, float);
	HRESULT (* SetEmissive)(struct IDirect3DRMMaterial2 *, float, float, float);
	float (* GetPower)(struct IDirect3DRMMaterial2 *);
	HRESULT (* GetSpecular)(struct IDirect3DRMMaterial2 *, float *, float *, float *);
	HRESULT (* GetEmissive)(struct IDirect3DRMMaterial2 *, float *, float *, float *);
	HRESULT (* GetAmbient)(struct IDirect3DRMMaterial2 *, float *, float *, float *);
	HRESULT (* SetAmbient)(struct IDirect3DRMMaterial2 *, float, float, float);
};

struct Detail_TextureSet { // [LegoRR/Detail.c|struct:0xc]
	struct Size2I gridSize;
	struct Container_Texture * * gridSurfaces;
};

struct Map3D { // [LegoRR/Map3D.c|struct:0x73d4]
	uint blockWidth; // gridWidth - 1
	uint blockHeight; // gridHeight - 1
	uint gridWidth; // full map width
	uint gridHeight; // full map height
	float blockSize; // (cfg: BlockSize)
	float roughLevel; // (cfg: RoughLevel)
	struct Size2F worldDimensions_fnegx; // (-width, +height) * BlockSize / 2.0f  (smallDimensions)
	float float_20; // (some sort of maximum)
	struct Container * mesh; // Mesh for Map3D_Blocks
	struct Map3D_Block * blocks3D; // [*:dimensions]
	struct Detail_TextureSet * textureSet;
	struct IDirect3DRMMaterial2 * material; // (UNUSED: And never released!!!)
	byte texsGrid[128][128]; // [MAP3D_MAXTEXTURES][MAP3D_MAXTEXTURES]
	byte texsNum[128]; // [MAP3D_MAXTEXTURES]
	BOOL texsNoFade[128]; // [MAP3D_MAXTEXTURES] True for textures that cannot fade transition
	struct Coord2U visibleBlocksTable[500]; // (related to FP detail)
	uint visibleBlocksNum;
	struct Coord2U uvBlocksTable[2500]; // Blocks that require UV updates (EMISSIVE or UVWOBBLES)
	uint uvBlocksNum;
	struct Map3D_TransitionBlock transBlocks[10]; // [BASEMAPTEXTURES??]
	struct Container * transMesh; // Mesh for Map3D_TransitionBlocks
	enum Map3DFlags flagsMap;
};

struct Map3D_Block { // [LegoRR/Map3D.c|struct:0x28]
	struct Vector3F normalA; // Maths_PlaneNormal of vertex positions 0,1,3
	struct Vector3F normalB; // Maths_PlaneNormal of vertex positions 1,2,3
	enum SurfaceTexture texture;
	enum Map3D_BlockFlags flags3D;
	byte heightValue; // height block value taken from high.map file
	undefined1 padding1;
	struct Point2F uvCoord;
	byte highlight; // (WallHighlightType)
	undefined1 padding2[3];
};

struct IDirect3DRMMaterial2 { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMMaterial2Vtbl * lpVtbl;
};

typedef void (* XYCallback)(int, int);

typedef BOOL (* LegoObject_RunThroughListsCallback)(struct LegoObject *, void *);

typedef struct SFX_Property SFX_Property, *PSFX_Property;

struct SFX_Property { // [LegoRR/SFX.c|struct:0x8]
	int sound3DHandle;
	struct SFX_Property * next; // next group property
};

typedef struct SFX_Instance SFX_Instance, *PSFX_Instance;

typedef enum SFX_InstanceFlags { // [LegoRR/SFX.c|flags:0x4|type:uint]
	SFX_INSTANCE_FLAG_LOOPING=2,
	SFX_INSTANCE_FLAG_NONE=0,
	SFX_INSTANCE_FLAG_ONFRAME=4,
	SFX_INSTANCE_FLAG_SOUND3D=1
} SFX_InstanceFlags;

struct SFX_Instance { // [LegoRR/SFX.c|struct:0x18]
	int sampleIndex;
	struct IDirect3DRMFrame3 * frame; // what happened to hiding D3DRM behind Containers and 3DSound?
	struct Vector3F position;
	enum SFX_InstanceFlags flags;
};

typedef struct NERPMessageSound NERPMessageSound, *PNERPMessageSound;

struct NERPMessageSound { // [LegoRR/NERPs.c|struct:0x8]
	char * key;
	int sound3DHandle;
};

typedef struct Image_Globs Image_Globs, *PImage_Globs;

struct Image_Globs { // [Gods98/Images.c|struct:0x8c|tags:GLOBS]
	struct Image * listSet[32]; // Images list
	struct Image * freeList;
	uint listCount; // number of lists.
	uint flags;
};

typedef struct Font_Globs Font_Globs, *PFont_Globs;

typedef struct Font Font, *PFont;

typedef struct Area2F Area2F, *PArea2F;

typedef enum FontFlags { // [Gods98/Fonts.c|flags:0x4|type:uint]
	FONT_FLAG_INITIALISED=1,
	FONT_FLAG_NONE=0,
	FONT_FLAG_WINDOWSET=2,
	FONT_FLAG_WINDOWWRAPPED=4
} FontFlags;

struct Font_Globs { // [Gods98/Fonts.c|struct:0x8c|tags:GLOBS]
	struct Font * listSet[32]; // Fonts list
	struct Font * freeList;
	uint listCount; // number of lists.
	uint flags;
};

struct Area2F { // [common.c|struct:0x10] also Area2F
	float x;
	float y;
	float width;
	float height;
};

struct Font { // [Gods98/Fonts.c|struct:0xbf4|tags:LISTSET] (official: Font)
	struct Image * image;
	struct Area2F posSet[10][19];
	uint fontHeight;
	uint tabWidth;
	enum FontFlags flags;
	struct Font * nextFree;
};

typedef struct File_Globs File_Globs, *PFile_Globs;

typedef struct _iobuf _iobuf, *P_iobuf;

typedef struct _iobuf FILE;

typedef void (* FileLoadCallback)(char *, uint, void *);

struct _iobuf {
	char * _ptr;
	int _cnt;
	char * _base;
	int _flag;
	int _file;
	int _charbuf;
	int _bufsiz;
	char * _tmpfname;
};

struct File_Globs { // [Gods98/Files.c|struct:0xa20|tags:GLOBS]
	char wadBasePath[1024];
	char s_GetWadName_wadedName[1024];
	char s_VerifyFilename_full[260];
	FILE * s_ErrorFile_f; // (address not known)
	char dataDir[260];
	FileLoadCallback loadCallback;
	void * loadCallbackData;
	char cdLetter;
	undefined1 padding1[3];
	BOOL basePathSet;
	BOOL fileLogFileAccess; // (address not known)
};

typedef struct Draw_Globs Draw_Globs, *PDraw_Globs;

typedef void (* DrawPixelFunc)(int, int, uint);

typedef struct tagRECT RECT;

typedef enum Draw_GlobFlags { // [Gods98/Draw.c|flags:0x4|type:uint]
	DRAW_GLOB_FLAG_INITIALISED=1,
	DRAW_GLOB_FLAG_NONE=0
} Draw_GlobFlags;

struct Draw_Globs { // [Gods98/Draw.c|struct:0x4c|tags:GLOBS]
	DrawPixelFunc drawPixelFunc;
	struct Point2F clipStart;
	struct Point2F clipEnd;
	RECT lockRect;
	void * buffer;
	uint pitch;
	uint bpp;
	uint redMask;
	uint greenMask;
	uint blueMask;
	uint redBits;
	uint greenBits;
	uint blueBits;
	enum Draw_GlobFlags flags;
};

typedef struct Config_Globs Config_Globs, *PConfig_Globs;

typedef struct Config Config, *PConfig;

typedef enum Config_GlobFlags { // [Gods98/Memory.c|flags:0x4|type:uint]
	CONFIG_GLOB_FLAG_INITIALISED=1,
	CONFIG_GLOB_FLAG_LOADINGCONFIG=2,
	CONFIG_GLOB_FLAG_NONE=0
} Config_GlobFlags;

struct Config_Globs { // [Gods98/Config.c|struct:0x48c|tags:GLOBS]
	char s_JoinPath_string[1024]; // (not part of Manager, static array in JoinPath func)
	struct Config * listSet[32];
	struct Config * freeList;
	uint listCount;
	enum Config_GlobFlags flags;
};

struct Config { // [Gods98/Config.c|struct:0x20|tags:LISTSET] CFG file property node
	char * fileData; // Entire file text data for root CFGProperty only
	char * key; // Property or block key name
	char * value; // Property value or block open brace
	uint depth; // Block-depth of property
	uint itemHashCode; // Hash of item (unused)
	struct Config * linkNext; // Next property in linked list
	struct Config * linkPrev; // Previous property in linked list
	struct Config * nextFree; // (internal) used for allocation while reading(?)
};

typedef struct Mesh_Globs Mesh_Globs, *PMesh_Globs;

typedef struct Mesh_PostRenderInfo Mesh_PostRenderInfo, *PMesh_PostRenderInfo;

typedef struct Main_StateChangeData Main_StateChangeData, *PMain_StateChangeData;

typedef struct Mesh_TextureReference Mesh_TextureReference, *PMesh_TextureReference;

typedef struct IDirect3DMaterial3 IDirect3DMaterial3, *PIDirect3DMaterial3;

typedef struct IDirect3DMaterial3Vtbl IDirect3DMaterial3Vtbl, *PIDirect3DMaterial3Vtbl;

struct Main_StateChangeData { // [Gods98/Main.c|struct:0x8] The item's render state type is determined by the index in its table
	uint origValue; // not restricted to just uint value types, pointers, floats, signed ints, etc.
	BOOL changed;
};

struct IDirect3DMaterial3 { // [DirectX/D3D.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DMaterial3Vtbl * lpVtbl;
};

struct Mesh_TextureReference { // [Gods98/Mesh.c|struct:0xc]
	struct IDirectDrawSurface4 * surface;
	char * path;
	BOOL trans;
};

struct Mesh_Globs { // [Gods98/Mesh.c|struct:0xc21c|tags:GLOBS]
	struct Mesh * postRenderList;
	struct Mesh_PostRenderInfo * postRenderMeshList;
	struct Main_StateChangeData stateData[50];
	char * sharedTextureDir;
	struct Mesh_TextureReference textureList[2048];
	struct Mesh_TextureReference textureListShared[2048];
	uint textureCount;
	uint textureCountShared;
	DWORD oldTextureRM;
	DWORD oldMatIM;
	struct IDirect3DTexture2 * oldTextureIM;
	DWORD currTextureRM;
	DWORD currMatIM;
	struct IDirect3DTexture2 * currTextureIM;
	DWORD matHandle;
	struct IDirect3DMaterial3 * imMat;
	struct Mesh * listSet[20];
	struct Mesh * freeList;
	uint listCount; // (yeah, no uint flags)
};

struct Mesh_PostRenderInfo { // [Gods98/Mesh.c|struct:0x48]
	struct Mesh * mesh;
	struct Matrix4F matWorld;
	struct Mesh_PostRenderInfo * next;
};

struct IDirect3DMaterial3Vtbl { // [DirectX/D3D.c|struct:0x18|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer SetMaterial;
	pointer GetMaterial;
	pointer GetHandle;
};

typedef struct DirectDraw_Globs DirectDraw_Globs, *PDirectDraw_Globs;

typedef struct HWND__ HWND__, *PHWND__;

typedef struct HWND__ * HWND;

typedef struct IDirectDraw4 IDirectDraw4, *PIDirectDraw4;

typedef struct IDirectDrawClipper IDirectDrawClipper, *PIDirectDrawClipper;

typedef struct Graphics_Driver Graphics_Driver, *PGraphics_Driver;

typedef struct Graphics_Device Graphics_Device, *PGraphics_Device;

typedef struct Graphics_Mode Graphics_Mode, *PGraphics_Mode;

typedef struct IDirectDraw4Vtbl IDirectDraw4Vtbl, *PIDirectDraw4Vtbl;

typedef struct IDirectDrawClipperVtbl IDirectDrawClipperVtbl, *PIDirectDrawClipperVtbl;

typedef enum Graphics_DriverFlags { // [Gods98/DirectDraw.c|flags:0x4|type:uint] Valid flag is actually shared: DIRECTDRAW_FLAG_VALID
	GRAPHICS_DRIVER_FLAG_NONE=0,
	GRAPHICS_DRIVER_FLAG_PRIMARY=16,
	GRAPHICS_DRIVER_FLAG_VALID=1,
	GRAPHICS_DRIVER_FLAG_WINDOWOK=32
} Graphics_DriverFlags;

typedef enum Graphics_DeviceFlags { // [Gods98/DirectDraw.c|flags:0x4|type:uint] Valid flag is actually shared: DIRECTDRAW_FLAG_VALID
	GRAPHICS_DEVICE_FLAG_COLOUR=4096,
	GRAPHICS_DEVICE_FLAG_DEPTH16=32,
	GRAPHICS_DEVICE_FLAG_DEPTH24=64,
	GRAPHICS_DEVICE_FLAG_DEPTH32=128,
	GRAPHICS_DEVICE_FLAG_DEPTH8=16,
	GRAPHICS_DEVICE_FLAG_HARDWARE=8192,
	GRAPHICS_DEVICE_FLAG_NONE=0,
	GRAPHICS_DEVICE_FLAG_SYSTEMTEXTURE=32768,
	GRAPHICS_DEVICE_FLAG_VALID=1,
	GRAPHICS_DEVICE_FLAG_VIDEOTEXTURE=16384,
	GRAPHICS_DEVICE_FLAG_ZBUFF16=512,
	GRAPHICS_DEVICE_FLAG_ZBUFF24=1024,
	GRAPHICS_DEVICE_FLAG_ZBUFF32=2048,
	GRAPHICS_DEVICE_FLAG_ZBUFF8=256
} Graphics_DeviceFlags;

typedef enum Graphics_ModeFlags { // [Gods98/DirectDraw.c|flags:0x4|type:uint] Valid flag is actually shared: DIRECTDRAW_FLAG_VALID
	GRAPHICS_MODE_FLAG_NONE=0,
	GRAPHICS_MODE_FLAG_VALID=1
} Graphics_ModeFlags;

struct IDirectDrawClipperVtbl { // [DirectX/DDraw.c|struct:0x24|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer GetClipList;
	pointer GetHWnd;
	pointer Initialize;
	pointer IsClipListChanged;
	pointer SetClipList;
	pointer SetHWnd;
};

struct DirectDraw_Globs { // [Gods98/DirectDraw.c|struct:0x48|tags:GLOBS]
	HWND hWnd;
	struct IDirectDraw4 * lpDirectDraw;
	struct IDirectDrawSurface4 * fSurf; // "RenderTarget" surface
	struct IDirectDrawSurface4 * bSurf; // "DrawTarget" surface
	struct IDirectDrawSurface4 * zSurf; // (unused)
	struct IDirectDrawClipper * lpFrontClipper; // "RenderTarget" clipper
	struct IDirectDrawClipper * lpBackClipper; // "DrawTarget" clipper
	struct Graphics_Driver * driverList;
	struct Graphics_Driver * selectedDriver; // (unused)
	struct Graphics_Device * deviceList;
	struct Graphics_Device * selectedDevice; // (unused)
	struct Graphics_Mode * modeList; // "ScreenModes"
	uint driverCount;
	uint deviceCount;
	uint modeCount; // "ScreenModes"
	BOOL fullScreen;
	uint width;
	uint height;
};

struct IDirectDraw4 { // [DirectX/DDraw.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirectDraw4Vtbl * lpVtbl;
};

struct Graphics_Driver { // [Gods98/DirectDraw.c|struct:0x114]
	GUID guid;
	char desc[256]; // "name (description)"
	enum Graphics_DriverFlags flags;
};

struct Graphics_Mode { // [Gods98/DirectDraw.c|struct:0x110]
	uint width;
	uint height;
	uint bitDepth;
	char desc[256]; // "WxH (BPP bit)", "WxH" (windowed)
	enum Graphics_ModeFlags flags;
};

struct IDirectDraw4Vtbl { // [DirectX/DDraw.c|struct:0x70|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer Compact; // (start of IDirectDraw)
	pointer CreateClipper;
	HRESULT (* CreatePalette)(struct IDirectDraw4 *, DWORD, struct D3DRMPaletteEntry *, struct IDirectDrawPalette * *, struct IUnknown *);
	HRESULT (* CreateSurface)(struct IDirectDraw4 *, struct DDSURFACEDESC2 *, struct IDirectDrawSurface4 * *, struct IUnknown *);
	pointer DuplicateSurface;
	HRESULT (* EnumDisplayModes)(struct IDirectDraw4 *, DWORD, struct DDSURFACEDESC2 *, LPVOID, HRESULT (* )(struct DDSURFACEDESC2 *, LPVOID));
	HRESULT (* EnumSurfaces)(struct IDirectDraw4 *, DWORD, struct DDSURFACEDESC2 *, LPVOID, HRESULT (* )(struct IDirectDrawSurface4 *, struct DDSURFACEDESC2 *, LPVOID));
	pointer FlipToGDISurface;
	pointer GetCaps;
	pointer GetDisplayMode;
	pointer GetFourCCCodes;
	pointer GetGDISurface;
	pointer GetMonitorFrequency;
	pointer GetScanLine;
	pointer GetVerticalBlankStatus;
	pointer Initialize;
	pointer RestoreDisplayMode;
	HRESULT (* SetCooperativeLevel)(struct IDirectDraw4 *, HWND, DWORD);
	HRESULT (* SetDisplayMode)(struct IDirectDraw4 *, DWORD, DWORD, DWORD, DWORD, DWORD);
	pointer WaitForVerticalBlank;
	pointer GetAvailableVidMem; // (start of IDirectDraw2)
	pointer GetSurfaceFromDC; // (start of IDirectDraw4)
	pointer RestoreAllSurfaces;
	pointer TestCooperativeLevel;
	pointer GetDeviceIdentifier;
};

struct Graphics_Device { // [Gods98/DirectDraw.c|struct:0x114]
	GUID guid;
	char desc[256]; // "name (description)"
	enum Graphics_DeviceFlags flags;
};

struct HWND__ {
	int unused;
};

struct IDirectDrawClipper { // [DirectX/DDraw.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirectDrawClipperVtbl * lpVtbl;
};

typedef struct Container_Globs Container_Globs, *PContainer_Globs;

typedef struct Container_TextureRef Container_TextureRef, *PContainer_TextureRef;

typedef void (* ContainerSoundTriggerCallback)(char *, struct Container *, void *);

typedef void (* ContainerTriggerFrameCallback)(struct Container *, void *);

typedef enum Container_GlobFlags { // [Gods98/Containers.c|flags:0x4|type:uint] All flags used by the ResourceManager struct.
	CONTAINER_FLAG_INITIALISED=1,
	CONTAINER_FLAG_NONE=0,
	CONTAINER_FLAG_TRIGGERENABLED=64
} Container_GlobFlags;

struct Container_TextureRef { // [Gods98/Containers.c|struct:0x8]
	char * filename;
	struct IDirect3DRMTexture3 * texture;
};

struct Container_Globs { // [Gods98/Containers.c|struct:0x2018|tags:GLOBS]
	struct Container * listSet[20];
	struct Container * freeList;
	struct Container * rootContainer;
	char * typeName[9];
	char * extensionName[9];
	char * gameName;
	struct IDirect3DRMVisual * visualArray[4];
	struct Container_TextureRef textureSet[1000];
	uint textureCount;
	ContainerSoundTriggerCallback soundTriggerCallback;
	void * soundTriggerData;
	ContainerTriggerFrameCallback triggerFrameCallback;
	void * triggerFrameData;
	char * sharedDir;
	uint fogColour;
	uint listCount;
	enum Container_GlobFlags flags;
};

typedef struct Viewport_Globs Viewport_Globs, *PViewport_Globs;

struct Viewport_Globs { // [Gods98/Viewports.c|struct:0x8c|tags:GLOBS]
	struct Viewport * listSet[32];
	struct Viewport * freeList;
	uint listCount;
	uint flags;
};

typedef struct FileCheck_Globs FileCheck_Globs, *PFileCheck_Globs;

struct FileCheck_Globs { // [Gods98/Files.c|struct:0x1f4004|tags:GLOBS] Loose static variables for File_CheckRedundantFiles in Files.c
	char loadedList[2000][1024]; // MAYBE USE LINKED LIST
	uint numInList;
};

typedef struct RNC_Globs RNC_Globs, *PRNC_Globs;

typedef struct HuffmanLeaf HuffmanLeaf, *PHuffmanLeaf;

struct HuffmanLeaf { // [Gods98/Compress.c|struct:0x10]
	uint value_1;
	ushort count_1;
	undefined2 padding1;
	uint value_2;
	ushort count_2; // (bit_depth)
	undefined2 padding2;
};

struct RNC_Globs { // [Gods98/Compress.c|struct:0x32c|tags:GLOBS]
	byte BitCount; // Never greater than 16
	undefined1 padding1[3];
	undefined4 reserved1[5]; // Probably used for missing compression functions
	struct HuffmanLeaf HuffmanTable_Raw[16];
	struct HuffmanLeaf HuffmanTable_Dst[16];
	struct HuffmanLeaf HuffmanTable_Len[16];
	byte * Input; // Input ptr at current read position
	byte * Output;
	byte ByteBuffer; // buffer for method2 "fast"
	undefined1 padding2[3];
	uint BitBuffer; // buffer for method1 "best" (4-byte int, but should only ever be 2-bytes)
	byte * OutputEnd;
};

typedef struct Lws_Globs Lws_Globs, *PLws_Globs;

typedef struct Lws_MeshPath Lws_MeshPath, *PLws_MeshPath;

typedef BOOL (* LwsFindSFXIDFunc)(char *, uint *);

typedef BOOL (* LwsSoundEnabledFunc)(void);

typedef int (* LwsPlaySample3DFunc)(struct IDirect3DRMFrame3 *, uint, BOOL, BOOL, struct Vector3F *);

struct Lws_MeshPath { // [Gods98/Lws.c|struct:0x8]
	char * path;
	struct Mesh * mesh;
};

struct Lws_Globs { // [Gods98/Lws.c|struct:0x402c|tags:GLOBS]
	struct Lws_MeshPath meshPathList[1000]; // For full path to files...
	struct Lws_MeshPath meshPathListShared[1000]; // For shared files...
	char * sharedDir;
	uint meshPathCount;
	uint meshPathCountShared;
	float staticDissolveLevel[100];
	uint staticDissolveCount;
	LwsFindSFXIDFunc FindSFXIDFunc;
	LwsSoundEnabledFunc SoundEnabledFunc;
	LwsPlaySample3DFunc PlaySample3DFunc;
};

typedef struct Sound_Globs Sound_Globs, *PSound_Globs;

typedef void (* SoundCDStopCallback)(void);

typedef DWORD MCIERROR;

struct Sound_Globs { // [Gods98/Sound.c|struct:0x1b8|tags:GLOBS]
	uint useSound; // Number of sounds in soundList
	BOOL initialised;
	uint soundList[100];
	int currTrack;
	BOOL loopCDTrack;
	SoundCDStopCallback CDStopCallback;
	BOOL updateCDTrack;
	uint s_Update_lastUpdate;
	undefined4 reserved1[2];
	MCIERROR mciErr;
};

typedef struct Animation_Globs Animation_Globs, *PAnimation_Globs;

struct Animation_Globs { // [Gods98/Animation.c|struct:0x8|tags:GLOBS]
	bool g98NoAvis; // (global variable)
	byte padding1[3];
	struct IDirectDraw4 * ddraw; // (global variable)
};

typedef struct Wad_Globs Wad_Globs, *PWad_Globs;

typedef struct Wad Wad, *PWad;

typedef struct Wad_FileHandle Wad_FileHandle, *PWad_FileHandle;

typedef struct WadEntry WadEntry, *PWadEntry;

typedef enum Wad_EntryFlags { // [Gods98/Wad.c|flags:0x4|type:uint]
	WADENTRY_FLAG_IS_IN_WAD=4,
	WADENTRY_FLAG_NONE=0,
	WADENTRY_FLAG_RNCOMPRESSED=2,
	WADENTRY_FLAG_UNCOMPRESSED=1
} Wad_EntryFlags;

struct Wad_FileHandle { // [Gods98/Wad.c|struct:0x10]
	void * data; // Pointer to the file data
	BOOL active; // Is this handle active already
	int wadNo; // Wad file this handle uses
	int fileNo; // Index of the file in the wad structure
};

struct Wad { // [Gods98/Wad.c|struct:0x24] LegoRR WAD File information
	char * fName; // (unused)
	BOOL active; // 1 if WAD is in-use
	HANDLE hFile;
	HANDLE hFileMapping;
	FILE * fWad; // File handle of the wad
	char * * fileNames; // Names of actual files
	char * * wadNames; // Names within wad
	struct WadEntry * wadEntries;
	int numFiles; // number of file entries
};

struct Wad_Globs { // [Gods98/Wad.c|struct:0x7ec|tags:GLOBS]
	DWORD computerNameLength; // (address not known)
	BOOL wadLogFileAccess; // (address not known)
	FILE * s_ErrorFile_f; // (address not known)
	struct Wad wads[10]; // Wad structures
	int references[10]; // Current count of references to the wad file
	char computerName[16]; // (address not known)
	struct Wad_FileHandle fileHandles[100];
};

struct WadEntry { // [Gods98/Wad.c|struct:0x10] WAD file entry metadata contained within LegoWADFile structure
	enum Wad_EntryFlags compression; // usually 1, 2 for RNC compression
	int fileLength; // Compressed packed size
	int decompressedLength; // Original unpacked size (same as packedSize when uncompressed)
	int addr; // absolute file offset
};

typedef struct Input_Globs Input_Globs, *PInput_Globs;

typedef struct IDirectInputA IDirectInputA, *PIDirectInputA;

typedef struct IDirectInputDeviceA IDirectInputDeviceA, *PIDirectInputDeviceA;

typedef struct DIMOUSESTATE DIMOUSESTATE, *PDIMOUSESTATE;

typedef struct DIcallbackData DIcallbackData, *PDIcallbackData;

typedef struct IDirectInputAVtbl IDirectInputAVtbl, *PIDirectInputAVtbl;

typedef GUID * LPGUID;

typedef struct DIDEVICEINSTANCEA DIDEVICEINSTANCEA, *PDIDEVICEINSTANCEA;

typedef struct HINSTANCE__ HINSTANCE__, *PHINSTANCE__;

typedef struct HINSTANCE__ * HINSTANCE;

typedef struct IDirectInputDeviceAVtbl IDirectInputDeviceAVtbl, *PIDirectInputDeviceAVtbl;

typedef struct DIDEVCAPS DIDEVCAPS, *PDIDEVCAPS;

typedef struct DIDEVICEOBJECTINSTANCEA DIDEVICEOBJECTINSTANCEA, *PDIDEVICEOBJECTINSTANCEA;

typedef struct DIPROPHEADER DIPROPHEADER, *PDIPROPHEADER;

typedef struct DIDEVICEOBJECTDATA DIDEVICEOBJECTDATA, *PDIDEVICEOBJECTDATA;

typedef struct DIDATAFORMAT DIDATAFORMAT, *PDIDATAFORMAT;

typedef uint UINT_PTR;

typedef struct DIOBJECTDATAFORMAT DIOBJECTDATAFORMAT, *PDIOBJECTDATAFORMAT;

struct DIPROPHEADER { // [DirectX/DInput.c|struct:0x10|tags:DIRECTX]
	DWORD dwSize;
	DWORD dwHeaderSize;
	DWORD dwObj;
	DWORD dwHow;
};

struct IDirectInputDeviceA { // [DirectX/DInput.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirectInputDeviceAVtbl * lpVtbl;
};

struct DIDEVCAPS { // [DirectX/DInput.c|struct:0x2c|tags:DIRECTX]
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwDevType;
	DWORD dwAxes;
	DWORD dwButtons;
	DWORD dwPOVs;
	DWORD dwFFSamplePeriod;
	DWORD dwFFMinTimeResolution;
	DWORD dwFirmwareRevision;
	DWORD dwHardwareRevision;
	DWORD dwFFDriverVersion;
};

struct IDirectInputA { // [DirectX/DInput.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirectInputAVtbl * lpVtbl;
};

struct IDirectInputAVtbl { // [DirectX/DInput.c|struct:0x20|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* CreateDevice)(struct IDirectInputA *, LPGUID, struct IDirectInputDeviceA * *, struct IUnknown *);
	HRESULT (* EnumDevices)(struct IDirectInputA *, DWORD, BOOL (* )(struct DIDEVICEINSTANCEA *, LPVOID), LPVOID, DWORD);
	HRESULT (* GetDeviceStatus)(struct IDirectInputA *, LPGUID);
	HRESULT (* RunControlPanel)(struct IDirectInputA *, HWND, DWORD);
	HRESULT (* Initialize)(struct IDirectInputA *, HINSTANCE, DWORD);
};

struct DIcallbackData { // [DirectX/DInput.c|struct:0xc|tags:DIRECTX]
	struct IDirectInputA * di;
	HWND hWnd;
	void * joystick; // struct joystickType
};

struct DIMOUSESTATE { // [DirectX/DInput.c|struct:0x10|tags:DIRECTX]
	uint lX;
	uint lY;
	uint lZ;
	bool rgbButtons[4];
};

struct Input_Globs { // [Gods98/Input.c|struct:0x280|tags:GLOBS]
	bool prevKey_Map[256];
	struct IDirectInputA * lpdi;
	struct IDirectInputDeviceA * lpdiKeyboard;
	struct IDirectInputDeviceA * lpdiMouse;
	BOOL fKeybdAcquired;
	BOOL fMouseAcquired;
	RECT MouseBounds; // Bounding box in which mouse may move
	int msx; // Current position of the mouse
	int msy; // Current position of the mouse
	int prev_msx; // Previous position of the mouse
	int prev_msy; // Previous position of the mouse
	int diffx; // Relative movement of mouse cursor
	int diffy; // Relative movement of mouse cursor
	BOOL mslb; // Mouse buttons
	BOOL msrb; // Mouse buttons
	BOOL mslblast;
	BOOL mslbheld;
	BOOL lClicked;
	BOOL rClicked;
	BOOL lDoubleClicked;
	BOOL rDoubleClicked;
	BOOL caps;
	struct DIMOUSESTATE dims;
	struct DIcallbackData cbd;
	char Input_KeyTemp;
	byte padding1[3];
	bool Key_Map[256];
};

struct IDirectInputDeviceAVtbl { // [DirectX/DInput.c|struct:0x48|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* GetCapabilities)(struct IDirectInputDeviceA *, struct DIDEVCAPS *);
	HRESULT (* EnumObjects)(struct IDirectInputDeviceA *, BOOL (* )(struct DIDEVICEOBJECTINSTANCEA *, LPVOID), LPVOID, DWORD);
	HRESULT (* GetProperty)(struct IDirectInputDeviceA *, LPGUID, struct DIPROPHEADER *);
	HRESULT (* SetProperty)(struct IDirectInputDeviceA *, LPGUID, struct DIPROPHEADER *);
	HRESULT (* Acquire)(struct IDirectInputDeviceA *);
	HRESULT (* Unacquire)(struct IDirectInputDeviceA *);
	HRESULT (* GetDeviceState)(struct IDirectInputDeviceA *, DWORD, LPVOID);
	HRESULT (* GetDeviceData)(struct IDirectInputDeviceA *, DWORD, struct DIDEVICEOBJECTDATA *, DWORD *, DWORD);
	HRESULT (* SetDataFormat)(struct IDirectInputDeviceA *, struct DIDATAFORMAT *);
	HRESULT (* SetEventNotification)(struct IDirectInputDeviceA *, HANDLE);
	HRESULT (* SetCooperativeLevel)(struct IDirectInputDeviceA *, HWND, DWORD);
	HRESULT (* GetObjectInfo)(struct IDirectInputDeviceA *, struct DIDEVICEOBJECTINSTANCEA *, DWORD, DWORD);
	HRESULT (* GetDeviceInfo)(struct IDirectInputDeviceA *, struct DIDEVICEINSTANCEA *);
	HRESULT (* RunControlPanel)(struct IDirectInputDeviceA *, HWND, DWORD);
	HRESULT (* Initialize)(struct IDirectInputDeviceA *, HINSTANCE, DWORD, LPGUID);
};

struct DIOBJECTDATAFORMAT { // [DirectX/DInput.c|struct:0x10|tags:DIRECTX]
	GUID * pguid;
	DWORD dwOfs;
	DWORD dwType;
	DWORD dwFlags;
};

struct DIDEVICEOBJECTDATA { // [DirectX/DInput.c|struct:0x14|tags:DIRECTX]
	DWORD dwOfs;
	DWORD dwData;
	DWORD dwTimeStamp;
	DWORD dwSequence;
	UINT_PTR uAppData;
};

struct DIDEVICEOBJECTINSTANCEA { // [DirectX/DInput.c|struct:0x13c|tags:DIRECTX]
	DWORD dwSize;
	GUID guidType;
	DWORD dwOfs;
	DWORD dwType;
	DWORD dwFlags;
	char tszName[260];
	DWORD dwFFMaxForce;
	DWORD dwFFForceResolution;
	WORD wCollectionNumber;
	WORD wDesignatorIndex;
	WORD wUsagePage;
	WORD wUsage;
	DWORD dwDimension;
	WORD wExponent;
	WORD wReserved;
};

struct DIDATAFORMAT { // [DirectX/DInput.c|struct:0x18|tags:DIRECTX]
	DWORD dwSize;
	DWORD dwObjSize;
	DWORD dwFlags;
	DWORD dwDataSize;
	DWORD dwNumObjs;
	struct DIOBJECTDATAFORMAT * rgodf;
};

struct DIDEVICEINSTANCEA { // [DirectX/DInput.c|struct:0x244|tags:DIRECTX]
	DWORD dwSize;
	GUID guidInstance;
	GUID guidProduct;
	DWORD dwDevType;
	char tszInstanceName[260];
	char tszProductName[260];
	GUID guidFFDriver;
	WORD wUsagePage;
	WORD wUsage;
};

struct HINSTANCE__ {
	int unused;
};

typedef struct Sound3D_Globs Sound3D_Globs, *PSound3D_Globs;

typedef struct IDirectSound IDirectSound, *PIDirectSound;

typedef struct IDirectSoundBuffer IDirectSoundBuffer, *PIDirectSoundBuffer;

typedef struct IDirectSound3DListener IDirectSound3DListener, *PIDirectSound3DListener;

typedef struct Sound3D_StreamData Sound3D_StreamData, *PSound3D_StreamData;

typedef struct Sound3D_SoundRecord Sound3D_SoundRecord, *PSound3D_SoundRecord;

typedef struct Sound3D_SoundData Sound3D_SoundData, *PSound3D_SoundData;

typedef struct IDirectSoundVtbl IDirectSoundVtbl, *PIDirectSoundVtbl;

typedef struct IDirectSoundBufferVtbl IDirectSoundBufferVtbl, *PIDirectSoundBufferVtbl;

typedef struct IDirectSound3DListenerVtbl IDirectSound3DListenerVtbl, *PIDirectSound3DListenerVtbl;

typedef struct Sound3D_WaveData Sound3D_WaveData, *PSound3D_WaveData;

typedef struct IDirectSound3DBuffer IDirectSound3DBuffer, *PIDirectSound3DBuffer;

typedef struct tWAVEFORMATEX tWAVEFORMATEX, *PtWAVEFORMATEX;

typedef struct tWAVEFORMATEX WAVEFORMATEX;

typedef enum Sound3DFlags { // [LegoRR/SFX.c|flags:0x4|type:uint]
	SAMPLE_ISUSED=1,
	SAMPLE_MULTIPLE=4,
	SAMPLE_NONE=0,
	SAMPLE_STREAMED=8,
	SAMPLE_VOLUME=2
} Sound3DFlags;

typedef struct HMMIO__ HMMIO__, *PHMMIO__;

typedef struct HMMIO__ * HMMIO;

typedef struct _MMCKINFO _MMCKINFO, *P_MMCKINFO;

typedef struct _MMCKINFO MMCKINFO;

typedef struct IDirectSound3DBufferVtbl IDirectSound3DBufferVtbl, *PIDirectSound3DBufferVtbl;

typedef DWORD FOURCC;

struct Sound3D_SoundData { // [Gods98/3DSound.c|struct:0x134]
	char filename[260];
	uint size;
	uint avgBytesPerSec; // Only set for streaming buffers
	int frequency;
	int volume;
	int offset;
	byte * data;
	WAVEFORMATEX * waveFormat;
	struct IDirectSoundBuffer * dSoundBuffers[3]; // ([] = max simultaneous 3D sounds)
	uint bufferIndex; // (official: voice)
	enum Sound3DFlags flags;
};

struct tWAVEFORMATEX {
	WORD wFormatTag;
	WORD nChannels;
	DWORD nSamplesPerSec;
	DWORD nAvgBytesPerSec;
	WORD nBlockAlign;
	WORD wBitsPerSample;
	WORD cbSize;
};

struct IDirectSound { // [DirectX/DSound.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirectSoundVtbl * lpVtbl;
};

struct Sound3D_SoundRecord { // [Gods98/3DSound.c|struct:0x10]
	struct IDirect3DRMFrame3 * frame;
	struct IDirectSoundBuffer * soundBuff;
	struct IDirectSound3DBuffer * sound3DBuff;
	struct Sound3D_SoundRecord * next;
};

struct IDirectSound3DListenerVtbl { // [DirectX/DSound.c|struct:0x48|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer GetAllParameters;
	pointer GetDistanceFactor;
	pointer GetDopplerFactor;
	pointer GetOrientation;
	pointer GetPosition;
	pointer GetRolloffFactor;
	pointer GetVelocity;
	pointer SetAllParameters;
	pointer SetDistanceFactor;
	pointer SetDopplerFactor;
	pointer SetOrientation;
	pointer SetPosition;
	pointer SetRolloffFactor;
	pointer SetVelocity;
	pointer CommitDeferredSettings;
};

struct IDirectSoundBuffer { // [DirectX/DSound.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirectSoundBufferVtbl * lpVtbl;
};

struct _MMCKINFO {
	FOURCC ckid;
	DWORD cksize;
	FOURCC fccType;
	DWORD dwDataOffset;
	DWORD dwFlags;
};

struct Sound3D_WaveData { // [Gods98/3DSound.c|struct:0x54]
	WAVEFORMATEX * waveFormat; // Wave Format data structure (hGlobal)
	HMMIO hmmio; // MM I/O handle for the WAVE
	MMCKINFO mmck; // Multimedia RIFF chunk
	MMCKINFO mmckInRIFF; // Use in opening a WAVE file
	DWORD dwBufferSize; // Size of the entire buffer
	DWORD dwNotifySize; // size of each notification period.
	DWORD dwNextWriteOffset; // Offset to next buffer segment
	DWORD dwProgress; // Used with above to show prog.
	DWORD dwNextProgressCheck;
	DWORD dwLastPos; // the last play position returned by GetCurrentPos().
	BOOL bDonePlaying; // Signals early abort to timer
	BOOL bLoopFile; // Should we loop playback?
	BOOL bFoundEnd; // Timer found file end
};

struct Sound3D_StreamData { // [Gods98/3DSound.c|struct:0x5c]
	BOOL fileOpen; // paused/playing/used?
	struct Sound3D_WaveData wiWave;
	BOOL playing; // paused/playing/used?
};

struct IDirectSoundVtbl { // [DirectX/DSound.c|struct:0x2c|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer CreateSoundBuffer;
	pointer GetCaps;
	pointer DuplicateSoundBuffer;
	pointer SetCooperativeLevel;
	pointer Compact;
	pointer GetSpeakerConfig;
	pointer SetSpeakerConfig;
	pointer Initialize;
};

struct IDirectSound3DListener { // [DirectX/DSound.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirectSound3DListenerVtbl * lpVtbl;
};

struct IDirectSound3DBufferVtbl { // [DirectX/DSound.c|struct:0x54|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer GetAllParameters;
	pointer GetConeAngles;
	pointer GetConeOrientation;
	pointer GetConeOutsideVolume;
	pointer GetMaxDistance;
	pointer GetMinDistance;
	pointer GetMode;
	pointer GetPosition;
	pointer GetVelocity;
	pointer SetAllParameters;
	pointer SetConeAngles;
	pointer SetConeOrientation;
	pointer SetConeOutsideVolume;
	pointer SetMaxDistance;
	pointer SetMinDistance;
	pointer SetMode;
	pointer SetPosition;
	pointer SetVelocity;
};

struct IDirectSoundBufferVtbl { // [DirectX/DSound.c|struct:0x54|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer GetCaps;
	pointer GetCurrentPosition;
	pointer GetFormat;
	pointer GetVolume;
	pointer GetPan;
	pointer GetFrequency;
	pointer GetStatus;
	pointer Initialize;
	pointer Lock;
	pointer Play;
	pointer SetCurrentPosition;
	pointer SetFormat;
	pointer SetVolume;
	pointer SetPan;
	pointer SetFrequency;
	pointer Stop;
	pointer Unlock;
	pointer Restore;
};

struct HMMIO__ {
	int unused;
};

struct Sound3D_Globs { // [Gods98/3DSound.c|struct:0x2d34c|tags:GLOBS]
	struct IDirectSound * lpDSnd;
	struct IDirectSoundBuffer * lpDSBuff;
	struct IDirectSound3DListener * lp3DListenerInfo;
	struct IDirectSoundBuffer * lpDSStreamBuff;
	struct IDirectSoundBuffer * lpDSLoopStreamBuff;
	struct Sound3D_StreamData streamData;
	struct Sound3D_StreamData loopStreamData;
	struct Sound3D_SoundRecord * soundRecord;
	struct IDirect3DRMFrame3 * listenerFrame;
	float minDistanceForAttentuation;
	float maxDistance;
	int volume;
	struct Sound3D_SoundData soundTable[600];
	BOOL intialised;
	int windowsVolume;
	uint flags;
	struct IDirect3DRMFrame3 * updateFrameList[20];
	uint reserved1;
	struct Vector3F s_ListenerCallback_oldPos;
	uint reserved2;
	struct Vector3F s_ListenerCallback_oldOrien;
	uint reserved3;
	struct Vector3F s_ListenerCallback_oldOrienUp;
};

struct IDirectSound3DBuffer { // [DirectX/DSound.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirectSound3DBufferVtbl * lpVtbl;
};

typedef struct Main_Globs Main_Globs, *PMain_Globs;

typedef struct IDirect3DRM3 IDirect3DRM3, *PIDirect3DRM3;

typedef struct IDirect3DDevice3 IDirect3DDevice3, *PIDirect3DDevice3;

typedef struct Main_State Main_State, *PMain_State;

typedef enum MainFlags { // [Gods98/Main.c|flags:0x4|type:uint] Command line argument flags set when starting the game
	MAIN_FLAG_BEST=64,
	MAIN_FLAG_CLEANSAVES=1024,
	MAIN_FLAG_DEBUGCOMPLETE=32768,
	MAIN_FLAG_DEBUGMODE=8192,
	MAIN_FLAG_DONTMANAGETEXTURES=32,
	MAIN_FLAG_DUALMOUSE=16384,
	MAIN_FLAG_DUMPMODE=128,
	MAIN_FLAG_FORCETEXTUREMANAGEMENT=262144,
	MAIN_FLAG_FORCEVERTEXFOG=524288,
	MAIN_FLAG_FULLSCREEN=2,
	MAIN_FLAG_LANGDUMPUNKNOWN=4096,
	MAIN_FLAG_LEVELSOPEN=131072,
	MAIN_FLAG_MIPMAPENABLED=8,
	MAIN_FLAG_NONE=0,
	MAIN_FLAG_PAUSED=16,
	MAIN_FLAG_REDUCEANIMATION=4194304,
	MAIN_FLAG_REDUCEFLICS=16777216,
	MAIN_FLAG_REDUCEIMAGES=33554432,
	MAIN_FLAG_REDUCEPROMESHES=8388608,
	MAIN_FLAG_REDUCESAMPLES=1048576,
	MAIN_FLAG_SAVELANGFILE=2048,
	MAIN_FLAG_SHOWVERSION=2097152,
	MAIN_FLAG_STARTLEVEL=512,
	MAIN_FLAG_TESTERCALL=65536,
	MAIN_FLAG_UPDATED=1,
	MAIN_FLAG_VIDEOTEXTURE=4,
	MAIN_FLAG_WINDOW=256
} MainFlags;

typedef enum ProgrammerMode { // [LegoRR/Lego.c|enum:0x4|type:uint] Programmer mode enum
	PROGRAMMER_MODE_1=1,
	PROGRAMMER_MODE_10=10,
	PROGRAMMER_MODE_11=11,
	PROGRAMMER_MODE_2=2,
	PROGRAMMER_MODE_3=3,
	PROGRAMMER_OFF=0
} ProgrammerMode;

typedef enum MainCLFlags { // [LegoRR/Lego.c|flags:0x4|type:uint] Flags specified by the "-flags #" command line argument (which has to be in decimal...)
	CL_FLAG_BLOCKFADE=32768,
	CL_FLAG_NONE=0
} MainCLFlags;

typedef struct HACCEL__ HACCEL__, *PHACCEL__;

typedef struct HACCEL__ * HACCEL;

typedef uint UINT;

typedef UINT_PTR WPARAM;

typedef long LONG_PTR;

typedef LONG_PTR LPARAM;

typedef void (* MainWindowCallback)(HWND, UINT, WPARAM, LPARAM);

typedef struct IDirect3DRM3Vtbl IDirect3DRM3Vtbl, *PIDirect3DRM3Vtbl;

typedef struct IDirect3DRMMeshBuilder3 IDirect3DRMMeshBuilder3, *PIDirect3DRMMeshBuilder3;

typedef struct IDirect3DRMAnimationSet2 IDirect3DRMAnimationSet2, *PIDirect3DRMAnimationSet2;

typedef struct IDirect3DDevice3Vtbl IDirect3DDevice3Vtbl, *PIDirect3DDevice3Vtbl;

typedef BOOL (* MainStateInitialise)(void);

typedef BOOL (* MainStateMainLoop)(float);

typedef void (* MainStateShutdown)(void);

typedef struct IDirect3DRMMeshBuilder3Vtbl IDirect3DRMMeshBuilder3Vtbl, *PIDirect3DRMMeshBuilder3Vtbl;

typedef struct IDirect3DRMAnimationSet2Vtbl IDirect3DRMAnimationSet2Vtbl, *PIDirect3DRMAnimationSet2Vtbl;

struct HACCEL__ {
	int unused;
};

struct IDirect3DRM3Vtbl { // [DirectX/D3DRM.c|struct:0xa4|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* CreateObject)(struct IDirect3DRM3 *, struct IUnknown *, GUID *, void * *);
	HRESULT (* CreateFrame)(struct IDirect3DRM3 *, struct IDirect3DRMFrame3 *, struct IDirect3DRMFrame3 * *);
	HRESULT (* CreateMesh)(struct IDirect3DRM3 *, struct IDirect3DRMMesh * *);
	HRESULT (* CreateMeshBuilder)(struct IDirect3DRM3 *, struct IDirect3DRMMeshBuilder3 * *);
	pointer CreateFace;
	pointer CreateAnimation;
	HRESULT (* CreateAnimationSet)(struct IDirect3DRM3 *, struct IDirect3DRMAnimationSet2 * *);
	HRESULT (* CreateTexture)(struct IDirect3DRM3 *, struct D3DRMImage *, struct IDirect3DRMTexture3 * *);
	HRESULT (* CreateLight)(struct IDirect3DRM3 *, enum D3DRMLightType, DWORD, struct IDirect3DRMLight * *);
	HRESULT (* CreateLightRGB)(struct IDirect3DRM3 *, enum D3DRMLightType, float, float, float, struct IDirect3DRMLight * *);
	HRESULT (* CreateMaterial)(struct IDirect3DRM3 *, float, struct IDirect3DRMMaterial2 * *);
	HRESULT (* CreateDevice)(struct IDirect3DRM3 *, DWORD, DWORD, struct IDirect3DRMDevice3 * *);
	pointer CreateDeviceFromSurface;
	pointer CreateDeviceFromD3D;
	HRESULT (* CreateDeviceFromClipper)(struct IDirect3DRM3 *, struct IDirectDrawClipper *, GUID *, int, int, struct IDirect3DRMDevice3 * *);
	HRESULT (* CreateTextureFromSurface)(struct IDirect3DRM3 *, struct IDirectDrawSurface4 *, struct IDirect3DRMTexture3 * *);
	pointer CreateShadow;
	HRESULT (* CreateViewport)(struct IDirect3DRM3 *, struct IDirect3DRMDevice3 *, struct IDirect3DRMFrame3 *, DWORD, DWORD, DWORD, DWORD, struct IDirect3DRMViewport2 * *);
	pointer CreateWrap;
	pointer CreateUserVisual;
	HRESULT (* LoadTexture)(struct IDirect3DRM3 *, LPSTR, struct IDirect3DRMTexture3 * *);
	pointer LoadTextureFromResource;
	pointer SetSearchPath;
	pointer AddSearchPath;
	pointer GetSearchPath;
	pointer SetDefaultTextureColors;
	pointer SetDefaultTextureShades;
	pointer GetDevices;
	pointer GetNamedObject;
	pointer EnumerateObjects;
	pointer Load;
	pointer Tick;
	pointer CreateProgressiveMesh;
	pointer RegisterClient;
	pointer UnregisterClient;
	pointer CreateClippedVisual;
	pointer SetOptions;
	pointer GetOptions;
};

struct IDirect3DRM3 { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRM3Vtbl * lpVtbl;
};

struct IDirect3DDevice3 { // [DirectX/D3D.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DDevice3Vtbl * lpVtbl;
};

struct Main_State { // [Gods98/Main.c|struct:0xc] (unrelated to Main_StateChangeData)
	MainStateInitialise Initialise;
	MainStateMainLoop MainLoop;
	MainStateShutdown Shutdown;
};

struct IDirect3DRMMeshBuilder3 { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMMeshBuilder3Vtbl * lpVtbl;
};

struct IDirect3DRMAnimationSet2Vtbl { // [DirectX/D3DRM.c|struct:0x40|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Clone)(struct IUnknown *, struct IUnknown *, IID *, LPVOID *);
	HRESULT (* AddDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* DeleteDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* SetAppData)(struct IUnknown *, DWORD);
	DWORD (* GetAppData)(struct IUnknown *);
	HRESULT (* SetName)(struct IUnknown *, LPCSTR);
	HRESULT (* GetName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* GetClassName)(struct IUnknown *, LPDWORD, LPSTR);
	pointer AddAnimation;
	pointer Load;
	pointer DeleteAnimation;
	pointer SetTime;
	pointer GetAnimations;
};

struct IDirect3DDevice3Vtbl { // [DirectX/D3D.c|struct:0xa8|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer GetCaps;
	pointer GetStats;
	pointer AddViewport;
	pointer DeleteViewport;
	pointer NextViewport;
	pointer EnumTextureFormats;
	pointer BeginScene;
	pointer EndScene;
	pointer GetDirect3D;
	pointer SetCurrentViewport;
	pointer GetCurrentViewport;
	pointer SetRenderTarget;
	pointer GetRenderTarget;
	pointer Begin_;
	pointer BeginIndexed;
	pointer Vertex;
	pointer Index;
	pointer End_;
	pointer GetRenderState;
	pointer SetRenderState;
	pointer GetLightState;
	pointer SetLightState;
	pointer SetTransform;
	pointer GetTransform;
	pointer MultiplyTransform;
	pointer DrawPrimitive;
	pointer DrawIndexedPrimitive;
	pointer SetClipStatus;
	pointer GetClipStatus;
	pointer DrawPrimitiveStrided;
	pointer DrawIndexedPrimitiveStrided;
	pointer DrawPrimitiveVB;
	pointer DrawIndexedPrimitiveVB;
	pointer ComputeSphereVisibility;
	pointer GetTexture;
	pointer SetTexture;
	pointer GetTextureStageState;
	pointer SetTextureStageState;
	pointer ValidateDevice;
};

struct IDirect3DRMMeshBuilder3Vtbl { // [DirectX/D3DRM.c|struct:0x118|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Clone)(struct IUnknown *, struct IUnknown *, IID *, LPVOID *);
	HRESULT (* AddDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* DeleteDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* SetAppData)(struct IUnknown *, DWORD);
	DWORD (* GetAppData)(struct IUnknown *);
	HRESULT (* SetName)(struct IUnknown *, LPCSTR);
	HRESULT (* GetName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* GetClassName)(struct IUnknown *, LPDWORD, LPSTR);
	pointer Load;
	pointer Save;
	pointer Scale;
	pointer Translate;
	pointer SetColorSource;
	pointer GetBox;
	pointer GenerateNormals;
	pointer GetColorSource;
	pointer AddMesh;
	pointer AddMeshBuilder;
	pointer AddFrame; // (in LightAlloy, this isn't properly on a newline, it does exist)
	pointer AddFace;
	pointer AddFaces;
	pointer ReserveSpace;
	pointer SetColorRGB;
	pointer SetColor;
	pointer SetTexture;
	pointer SetMaterial;
	pointer SetTextureTopology;
	pointer SetQuality;
	pointer SetPerspective;
	pointer SetVertex;
	pointer SetNormal;
	pointer SetTextureCoordinates;
	pointer SetVertexColor;
	pointer SetVertexColorRGB;
	pointer GetFaces;
	pointer GetGeometry;
	pointer GetTextureCoordinates;
	pointer AddVertex;
	pointer AddNormal;
	pointer CreateFace;
	pointer GetQuality;
	pointer GetPerspective;
	pointer GetFaceCount;
	pointer GetVertexCount;
	pointer GetVertexColor;
	pointer CreateMesh;
	pointer GetFace;
	pointer GetVertex;
	pointer GetNormal;
	pointer DeleteVertices;
	pointer DeleteNormals;
	pointer DeleteFace;
	pointer Empty;
	pointer Optimize;
	pointer AddFacesIndexed;
	pointer CreateSubMesh;
	pointer GetParentMesh;
	pointer GetSubMeshes;
	pointer DeleteSubMesh;
	pointer Enable;
	pointer GetEnable;
	pointer AddTriangles;
	pointer SetVertices;
	pointer GetVertices;
	pointer SetNormals;
	pointer GetNormals;
	pointer GetNormalCount;
};

struct IDirect3DRMAnimationSet2 { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMAnimationSet2Vtbl * lpVtbl;
};

struct Main_Globs { // [Gods98/Main.c|struct:0x898|tags:GLOBS]
	HWND hWnd;
	HINSTANCE hInst;
	BOOL active;
	BOOL exit;
	char * className;
	char programName[256];
	struct IDirect3DRM3 * lpD3DRM;
	struct IDirect3DRMDevice3 * device;
	struct IDirect3DDevice3 * imDevice;
	enum D3DRMSceneFogMethod fogMethod;
	uint appWidth;
	uint appHeight;
	struct Main_State currState;
	BOOL stateSet;
	float fixedFrameTiming;
	struct Main_StateChangeData renderStateData[200];
	uint style;
	enum MainFlags flags;
	enum ProgrammerMode programmerLevel;
	char startLevel[128];
	char languageName[128];
	enum MainCLFlags clFlags;
	HACCEL accels;
	MainWindowCallback windowCallback;
};

typedef struct Init_Globs Init_Globs, *PInit_Globs;

struct Init_Globs { // [Gods98Init/Init.c|struct:0x1d444|tags:GLOBS]
	uint driverCount;
	uint deviceCount;
	uint modeCount;
	struct Graphics_Driver drivers[20];
	struct Graphics_Device devices[20];
	struct Graphics_Mode modes[200];
	struct Graphics_Driver * selDriver;
	struct Graphics_Device * selDevice;
	struct Graphics_Mode * selMode;
	BOOL selFullScreen;
	BOOL wasFullScreen; // Previous fullscreen state when Windowed button is disabled due to lack of support
	struct Graphics_Mode validModes[200];
	uint validModeCount;
};

typedef struct Error_Globs Error_Globs, *PError_Globs;

typedef struct File File, *PFile;

typedef enum FileSys { // [Gods98/Files.c|enum:0x4|type:int] Location of a lego File stream (WAD or REAL)
	FileSys_Error=2,
	FileSys_Standard=1,
	FileSys_Wad=0
} FileSys;

typedef union File_union File_union, *PFile_union;

typedef struct WADFILE WADFILE, *PWADFILE;

union File_union { // [Gods98/Files.c|union:0x4]
	FILE * std; // Standard file stream
	struct WADFILE * wad; // WAD file stream
};

struct File { // [Gods98/Files.c|struct:0x8]
	enum FileSys type;
	union File_union stream;
};

struct WADFILE { // [Gods98/Files.c|struct:0xc] Used as one of the stream types for the File struct (as opposed to the C API FILE* struct)
	int hFile; // Handle to file in the wad
	int streamPos; // Position in stream of the file.  Indexes are from 0-length-1 inclusive.
	BOOL eof; // Has the file hit EOF.
};

struct Error_Globs { // [Gods98/Errors.c|struct:0x818|tags:GLOBS]
	struct File * dumpFile;
	struct File * loadLogFile;
	struct File * loadErrorLogFile;
	struct File * redundantLogFile;
	char loadLogName[1024];
	char redundantLogName[1024];
	BOOL warnCalled;
	BOOL fullScreen;
};

typedef struct Key_Globs Key_Globs, *PKey_Globs;

struct Key_Globs { // [Gods98/Keys.c|struct:0x400|tags:GLOBS]
	char * keyName[256];
};

typedef struct Mem_Globs Mem_Globs, *PMem_Globs;

typedef struct Mem_Handle Mem_Handle, *PMem_Handle;

typedef enum Mem_HandleFlags { // [Gods98/Memory.c|flags:0x4|type:uint] Flags for SharedBuffer struct
	MEMORY_HANDLE_FLAG_NONE=0,
	MEMORY_HANDLE_FLAG_USED=1
} Mem_HandleFlags;

struct Mem_Handle { // [Gods98/Memory.c|struct:0x8]
	void * addr;
	enum Mem_HandleFlags flags; // 1 = isUsed
};

struct Mem_Globs { // [Gods98/Memory.c|struct:0x3e84|tags:GLOBS]
	struct Mem_Handle handleList[2000];
	uint flags; // (unused)
};

typedef struct Dxbug_Globs Dxbug_Globs, *PDxbug_Globs;

struct Dxbug_Globs { // [Gods98/Dxbug.c|struct:0x818|tags:GLOBS] DirectX (dxbug.c) debugging loose static variables
	HRESULT errnum;
	int line;
	int DXModuleNameNumber;
	int DXNumErrorsSet;
	char * file;
	uint reserved1;
	char DXErrorString[2048]; // Last error that was set (actually [1024], but the space is unused)
};

typedef struct _CRuntime2_Globs _CRuntime2_Globs, *P_CRuntime2_Globs;

struct _CRuntime2_Globs { // [tags:HIDDEN,STD,GLOBS]
	FILE * * _filesTable_0076dd98;
	undefined4 field_0x4;
	char CHAR_ARRAY_0076dda0[4096];
	int _filesCount_0076eda0;
	undefined4 field_0x100c[7];
	void * _handlesTable_0076edc0[64];
	uint _handlesSize_0076eec0;
	HANDLE _heap;
	LPSTR _acmdln;
	void * PTR_0076eecc;
	void * PTR_0076eed0;
};

typedef struct _CRuntime3_Globs _CRuntime3_Globs, *P_CRuntime3_Globs;

struct _CRuntime3_Globs { // [tags:HIDDEN,STD,GLOBS]
	undefined field_0x0;
	undefined field_0x1;
	undefined field_0x2;
	undefined field_0x3;
	undefined field_0x4;
	undefined field_0x5;
	undefined field_0x6;
	undefined field_0x7;
	undefined field_0x8;
	undefined field_0x9;
	undefined field_0xa;
	undefined field_0xb;
	undefined field_0xc;
	undefined field_0xd;
	undefined field_0xe;
	undefined field_0xf;
	undefined field_0x10;
	undefined field_0x11;
	undefined field_0x12;
	undefined field_0x13;
	pointer field_0x14;
	pointer field_0x18;
	pointer field_0x1c;
	pointer field_0x20;
	undefined4 field_0x24;
	undefined4 field_0x28;
	undefined4 field_0x2c;
	undefined4 field_0x30;
	undefined4 field_0x34;
	undefined4 field_0x38;
	undefined4 field_0x3c;
	undefined field_0x40;
	undefined field_0x41;
	undefined field_0x42;
	undefined field_0x43;
	undefined field_0x44;
	undefined field_0x45;
	undefined field_0x46;
	undefined field_0x47;
	undefined field_0x48;
	undefined field_0x49;
	undefined field_0x4a;
	undefined field_0x4b;
	undefined field_0x4c;
	undefined field_0x4d;
	undefined field_0x4e;
	undefined field_0x4f;
	undefined field_0x50;
	undefined field_0x51;
	undefined field_0x52;
	undefined field_0x53;
	undefined field_0x54;
	undefined field_0x55;
	undefined field_0x56;
	undefined field_0x57;
	undefined field_0x58;
	undefined field_0x59;
	undefined field_0x5a;
	undefined field_0x5b;
	undefined field_0x5c;
	undefined field_0x5d;
	undefined field_0x5e;
	undefined field_0x5f;
	undefined field_0x60;
	undefined field_0x61;
	undefined field_0x62;
	undefined field_0x63;
	undefined field_0x64;
	undefined field_0x65;
	undefined field_0x66;
	undefined field_0x67;
	undefined field_0x68;
	undefined field_0x69;
	undefined field_0x6a;
	undefined field_0x6b;
	undefined field_0x6c;
	undefined field_0x6d;
	undefined field_0x6e;
	undefined field_0x6f;
	undefined field_0x70;
	undefined field_0x71;
	undefined field_0x72;
	undefined field_0x73;
	undefined field_0x74;
	undefined field_0x75;
	undefined field_0x76;
	undefined field_0x77;
	undefined field_0x78;
	undefined field_0x79;
	undefined field_0x7a;
	undefined field_0x7b;
	undefined field_0x7c;
	undefined field_0x7d;
	undefined field_0x7e;
	undefined field_0x7f;
	undefined field_0x80;
	undefined field_0x81;
	undefined field_0x82;
	undefined field_0x83;
	undefined field_0x84;
	undefined field_0x85;
	undefined field_0x86;
	undefined field_0x87;
	undefined field_0x88;
	undefined field_0x89;
	undefined field_0x8a;
	undefined field_0x8b;
	undefined field_0x8c;
	undefined field_0x8d;
	undefined field_0x8e;
	undefined field_0x8f;
	undefined field_0x90;
	undefined field_0x91;
	undefined field_0x92;
	undefined field_0x93;
	undefined field_0x94;
	undefined field_0x95;
	undefined field_0x96;
	undefined field_0x97;
	undefined field_0x98;
	undefined field_0x99;
	undefined field_0x9a;
	undefined field_0x9b;
	undefined field_0x9c;
	undefined field_0x9d;
	undefined field_0x9e;
	undefined field_0x9f;
	undefined field_0xa0;
	undefined field_0xa1;
	undefined field_0xa2;
	undefined field_0xa3;
	undefined field_0xa4;
	undefined field_0xa5;
	undefined field_0xa6;
	undefined field_0xa7;
	undefined field_0xa8;
	undefined field_0xa9;
	undefined field_0xaa;
	undefined field_0xab;
	undefined field_0xac;
	undefined field_0xad;
	undefined field_0xae;
	undefined field_0xaf;
	undefined field_0xb0;
	undefined field_0xb1;
	undefined field_0xb2;
	undefined field_0xb3;
	undefined field_0xb4;
	undefined field_0xb5;
	undefined field_0xb6;
	undefined field_0xb7;
	undefined field_0xb8;
	undefined field_0xb9;
	undefined field_0xba;
	undefined field_0xbb;
	undefined field_0xbc;
	undefined field_0xbd;
	undefined field_0xbe;
	undefined field_0xbf;
	undefined field_0xc0;
	undefined field_0xc1;
	undefined field_0xc2;
	undefined field_0xc3;
	undefined field_0xc4;
	undefined field_0xc5;
	undefined field_0xc6;
	undefined field_0xc7;
	undefined field_0xc8;
	undefined field_0xc9;
	undefined field_0xca;
	undefined field_0xcb;
	undefined field_0xcc;
	undefined field_0xcd;
	undefined field_0xce;
	undefined field_0xcf;
	undefined field_0xd0;
	undefined field_0xd1;
	undefined field_0xd2;
	undefined field_0xd3;
	undefined field_0xd4;
	undefined field_0xd5;
	undefined field_0xd6;
	undefined field_0xd7;
	undefined field_0xd8;
	undefined field_0xd9;
	undefined field_0xda;
	undefined field_0xdb;
	undefined field_0xdc;
	undefined field_0xdd;
	undefined field_0xde;
	undefined field_0xdf;
	undefined field_0xe0;
	undefined field_0xe1;
	undefined field_0xe2;
	undefined field_0xe3;
	undefined field_0xe4;
	undefined field_0xe5;
	undefined field_0xe6;
	undefined field_0xe7;
	undefined field_0xe8;
	undefined field_0xe9;
	undefined field_0xea;
	undefined field_0xeb;
	undefined field_0xec;
	undefined field_0xed;
	undefined field_0xee;
	undefined field_0xef;
	undefined field_0xf0;
	undefined field_0xf1;
	undefined field_0xf2;
	undefined field_0xf3;
	undefined field_0xf4;
	undefined field_0xf5;
	undefined field_0xf6;
	undefined field_0xf7;
	undefined field_0xf8;
	undefined field_0xf9;
	undefined field_0xfa;
	undefined field_0xfb;
	undefined field_0xfc;
	undefined field_0xfd;
	undefined field_0xfe;
	undefined field_0xff;
	undefined field_0x100;
	undefined field_0x101;
	undefined field_0x102;
	undefined field_0x103;
	undefined field_0x104;
	undefined field_0x105;
	undefined field_0x106;
	undefined field_0x107;
	undefined field_0x108;
	undefined field_0x109;
	undefined field_0x10a;
	undefined field_0x10b;
	undefined field_0x10c;
	undefined field_0x10d;
	undefined field_0x10e;
	undefined field_0x10f;
	undefined field_0x110;
	undefined field_0x111;
	undefined field_0x112;
	undefined field_0x113;
	undefined field_0x114;
	undefined field_0x115;
	undefined field_0x116;
	undefined field_0x117;
	undefined field_0x118;
	undefined field_0x119;
	undefined field_0x11a;
	undefined field_0x11b;
	undefined field_0x11c;
	undefined field_0x11d;
	undefined field_0x11e;
	undefined field_0x11f;
	undefined field_0x120;
	undefined field_0x121;
	undefined field_0x122;
	undefined field_0x123;
	undefined field_0x124;
	undefined field_0x125;
	undefined field_0x126;
	undefined field_0x127;
	undefined field_0x128;
	undefined field_0x129;
	undefined field_0x12a;
	undefined field_0x12b;
	undefined field_0x12c;
	undefined field_0x12d;
	undefined field_0x12e;
	undefined field_0x12f;
	undefined field_0x130;
	undefined field_0x131;
	undefined field_0x132;
	undefined field_0x133;
	undefined field_0x134;
	undefined field_0x135;
	undefined field_0x136;
	undefined field_0x137;
	undefined field_0x138;
	undefined field_0x139;
	undefined field_0x13a;
	undefined field_0x13b;
	undefined field_0x13c;
	undefined field_0x13d;
	undefined field_0x13e;
	undefined field_0x13f;
	undefined field_0x140;
	undefined field_0x141;
	undefined field_0x142;
	undefined field_0x143;
	undefined field_0x144;
	undefined field_0x145;
	undefined field_0x146;
	undefined field_0x147;
	undefined field_0x148;
	undefined field_0x149;
	undefined field_0x14a;
	undefined field_0x14b;
	undefined field_0x14c;
	undefined field_0x14d;
	undefined field_0x14e;
	undefined field_0x14f;
	undefined field_0x150;
	undefined field_0x151;
	undefined field_0x152;
	undefined field_0x153;
	undefined field_0x154;
	undefined field_0x155;
	undefined field_0x156;
	undefined field_0x157;
	undefined field_0x158;
	undefined field_0x159;
	undefined field_0x15a;
	undefined field_0x15b;
	undefined field_0x15c;
	undefined field_0x15d;
	undefined field_0x15e;
	undefined field_0x15f;
	undefined field_0x160;
	undefined field_0x161;
	undefined field_0x162;
	undefined field_0x163;
	undefined field_0x164;
	undefined field_0x165;
	undefined field_0x166;
	undefined field_0x167;
	undefined field_0x168;
	undefined field_0x169;
	undefined field_0x16a;
	undefined field_0x16b;
	undefined field_0x16c;
	undefined field_0x16d;
	undefined field_0x16e;
	undefined field_0x16f;
	undefined field_0x170;
	undefined field_0x171;
	undefined field_0x172;
	undefined field_0x173;
	undefined field_0x174;
	undefined field_0x175;
	undefined field_0x176;
	undefined field_0x177;
	undefined field_0x178;
	undefined field_0x179;
	undefined field_0x17a;
	undefined field_0x17b;
	undefined field_0x17c;
	undefined field_0x17d;
	undefined field_0x17e;
	undefined field_0x17f;
	undefined field_0x180;
	undefined field_0x181;
	undefined field_0x182;
	undefined field_0x183;
	undefined field_0x184;
	undefined field_0x185;
	undefined field_0x186;
	undefined field_0x187;
	undefined field_0x188;
	undefined field_0x189;
	undefined field_0x18a;
	undefined field_0x18b;
	undefined field_0x18c;
	undefined field_0x18d;
	undefined field_0x18e;
	undefined field_0x18f;
	undefined field_0x190;
	undefined field_0x191;
	undefined field_0x192;
	undefined field_0x193;
	undefined field_0x194;
	undefined field_0x195;
	undefined field_0x196;
	undefined field_0x197;
	undefined field_0x198;
	undefined field_0x199;
	undefined field_0x19a;
	undefined field_0x19b;
	undefined field_0x19c;
	undefined field_0x19d;
	undefined field_0x19e;
	undefined field_0x19f;
	undefined field_0x1a0;
	undefined field_0x1a1;
	undefined field_0x1a2;
	undefined field_0x1a3;
	undefined field_0x1a4;
	undefined field_0x1a5;
	undefined field_0x1a6;
	undefined field_0x1a7;
	undefined field_0x1a8;
	undefined field_0x1a9;
	undefined field_0x1aa;
	undefined field_0x1ab;
	undefined field_0x1ac;
	undefined field_0x1ad;
	undefined field_0x1ae;
	undefined field_0x1af;
	undefined field_0x1b0;
	undefined field_0x1b1;
	undefined field_0x1b2;
	undefined field_0x1b3;
	undefined field_0x1b4;
	undefined field_0x1b5;
	undefined field_0x1b6;
	undefined field_0x1b7;
	undefined field_0x1b8;
	undefined field_0x1b9;
	undefined field_0x1ba;
	undefined field_0x1bb;
	undefined field_0x1bc;
	undefined field_0x1bd;
	undefined field_0x1be;
	undefined field_0x1bf;
	undefined field_0x1c0;
	undefined field_0x1c1;
	undefined field_0x1c2;
	undefined field_0x1c3;
	undefined field_0x1c4;
	undefined field_0x1c5;
	undefined field_0x1c6;
	undefined field_0x1c7;
	undefined field_0x1c8;
	undefined field_0x1c9;
	undefined field_0x1ca;
	undefined field_0x1cb;
	undefined field_0x1cc;
	undefined field_0x1cd;
	undefined field_0x1ce;
	undefined field_0x1cf;
	undefined field_0x1d0;
	undefined field_0x1d1;
	undefined field_0x1d2;
	undefined field_0x1d3;
	undefined field_0x1d4;
	undefined field_0x1d5;
	undefined field_0x1d6;
	undefined field_0x1d7;
	undefined field_0x1d8;
	undefined field_0x1d9;
	undefined field_0x1da;
	undefined field_0x1db;
	undefined field_0x1dc;
	undefined field_0x1dd;
	undefined field_0x1de;
	undefined field_0x1df;
	undefined field_0x1e0;
	undefined field_0x1e1;
	undefined field_0x1e2;
	undefined field_0x1e3;
	undefined field_0x1e4;
	undefined field_0x1e5;
	undefined field_0x1e6;
	undefined field_0x1e7;
	undefined field_0x1e8;
	undefined field_0x1e9;
	undefined field_0x1ea;
	undefined field_0x1eb;
	undefined field_0x1ec;
	undefined field_0x1ed;
	undefined field_0x1ee;
	undefined field_0x1ef;
	undefined field_0x1f0;
	undefined field_0x1f1;
	undefined field_0x1f2;
	undefined field_0x1f3;
	undefined field_0x1f4;
	undefined field_0x1f5;
	undefined field_0x1f6;
	undefined field_0x1f7;
	undefined field_0x1f8;
	undefined field_0x1f9;
	undefined field_0x1fa;
	undefined field_0x1fb;
	undefined field_0x1fc;
	undefined field_0x1fd;
	undefined field_0x1fe;
	undefined field_0x1ff;
	undefined field_0x200;
	undefined field_0x201;
	undefined field_0x202;
	undefined field_0x203;
	undefined field_0x204;
	undefined field_0x205;
	undefined field_0x206;
	undefined field_0x207;
	undefined field_0x208;
	undefined field_0x209;
	undefined field_0x20a;
	undefined field_0x20b;
	undefined field_0x20c;
	undefined field_0x20d;
	undefined field_0x20e;
	undefined field_0x20f;
	undefined field_0x210;
	undefined field_0x211;
	undefined field_0x212;
	undefined field_0x213;
	undefined field_0x214;
	undefined field_0x215;
	undefined field_0x216;
	undefined field_0x217;
	undefined field_0x218;
	undefined field_0x219;
	undefined field_0x21a;
	undefined field_0x21b;
	undefined field_0x21c;
	undefined field_0x21d;
	undefined field_0x21e;
	undefined field_0x21f;
	undefined field_0x220;
	undefined field_0x221;
	undefined field_0x222;
	undefined field_0x223;
	undefined field_0x224;
	undefined field_0x225;
	undefined field_0x226;
	undefined field_0x227;
	undefined field_0x228;
	undefined field_0x229;
	undefined field_0x22a;
	undefined field_0x22b;
	undefined field_0x22c;
	undefined field_0x22d;
	undefined field_0x22e;
	undefined field_0x22f;
	undefined field_0x230;
	undefined field_0x231;
	undefined field_0x232;
	undefined field_0x233;
	undefined field_0x234;
	undefined field_0x235;
	undefined field_0x236;
	undefined field_0x237;
	undefined field_0x238;
	undefined field_0x239;
	undefined field_0x23a;
	undefined field_0x23b;
	undefined field_0x23c;
	undefined field_0x23d;
	undefined field_0x23e;
	undefined field_0x23f;
	undefined field_0x240;
	undefined field_0x241;
	undefined field_0x242;
	undefined field_0x243;
	undefined field_0x244;
	undefined field_0x245;
	undefined field_0x246;
	undefined field_0x247;
	undefined field_0x248;
	undefined field_0x249;
	undefined field_0x24a;
	undefined field_0x24b;
	undefined field_0x24c;
	undefined field_0x24d;
	undefined field_0x24e;
	undefined field_0x24f;
	undefined field_0x250;
	undefined field_0x251;
	undefined field_0x252;
	undefined field_0x253;
	undefined field_0x254;
	undefined field_0x255;
	undefined field_0x256;
	undefined field_0x257;
	undefined field_0x258;
	undefined field_0x259;
	undefined field_0x25a;
	undefined field_0x25b;
	undefined field_0x25c;
	undefined field_0x25d;
	undefined field_0x25e;
	undefined field_0x25f;
	undefined field_0x260;
	undefined field_0x261;
	undefined field_0x262;
	undefined field_0x263;
	undefined field_0x264;
	undefined field_0x265;
	undefined field_0x266;
	undefined field_0x267;
	undefined field_0x268;
	undefined field_0x269;
	undefined field_0x26a;
	undefined field_0x26b;
	undefined field_0x26c;
	undefined field_0x26d;
	undefined field_0x26e;
	undefined field_0x26f;
	undefined field_0x270;
	undefined field_0x271;
	undefined field_0x272;
	undefined field_0x273;
	undefined field_0x274;
	undefined field_0x275;
	undefined field_0x276;
	undefined field_0x277;
	undefined field_0x278;
	undefined field_0x279;
	undefined field_0x27a;
	undefined field_0x27b;
	undefined field_0x27c;
	undefined field_0x27d;
	undefined field_0x27e;
	undefined field_0x27f;
	undefined field_0x280;
	undefined field_0x281;
	undefined field_0x282;
	undefined field_0x283;
	undefined field_0x284;
	undefined field_0x285;
	undefined field_0x286;
	undefined field_0x287;
	undefined field_0x288;
	undefined field_0x289;
	undefined field_0x28a;
	undefined field_0x28b;
	undefined field_0x28c;
	undefined field_0x28d;
	undefined field_0x28e;
	undefined field_0x28f;
	undefined field_0x290;
	undefined field_0x291;
	undefined field_0x292;
	undefined field_0x293;
	undefined field_0x294;
	undefined field_0x295;
	undefined field_0x296;
	undefined field_0x297;
	undefined field_0x298;
	undefined field_0x299;
	undefined field_0x29a;
	undefined field_0x29b;
	undefined field_0x29c;
	undefined field_0x29d;
	undefined field_0x29e;
	undefined field_0x29f;
	undefined field_0x2a0;
	undefined field_0x2a1;
	undefined field_0x2a2;
	undefined field_0x2a3;
	undefined field_0x2a4;
	undefined field_0x2a5;
	undefined field_0x2a6;
	undefined field_0x2a7;
	undefined field_0x2a8;
	undefined field_0x2a9;
	undefined field_0x2aa;
	undefined field_0x2ab;
	undefined field_0x2ac;
	undefined field_0x2ad;
	undefined field_0x2ae;
	undefined field_0x2af;
	undefined field_0x2b0;
	undefined field_0x2b1;
	undefined field_0x2b2;
	undefined field_0x2b3;
	undefined field_0x2b4;
	undefined field_0x2b5;
	undefined field_0x2b6;
	undefined field_0x2b7;
	undefined field_0x2b8;
	undefined field_0x2b9;
	undefined field_0x2ba;
	undefined field_0x2bb;
	undefined field_0x2bc;
	undefined field_0x2bd;
	undefined field_0x2be;
	undefined field_0x2bf;
	undefined field_0x2c0;
	undefined field_0x2c1;
	undefined field_0x2c2;
	undefined field_0x2c3;
	undefined field_0x2c4;
	undefined field_0x2c5;
	undefined field_0x2c6;
	undefined field_0x2c7;
	undefined field_0x2c8;
	undefined field_0x2c9;
	undefined field_0x2ca;
	undefined field_0x2cb;
	undefined field_0x2cc;
	undefined field_0x2cd;
	undefined field_0x2ce;
	undefined field_0x2cf;
	undefined field_0x2d0;
	undefined field_0x2d1;
	undefined field_0x2d2;
	undefined field_0x2d3;
	undefined field_0x2d4;
	undefined field_0x2d5;
	undefined field_0x2d6;
	undefined field_0x2d7;
	undefined field_0x2d8;
	undefined field_0x2d9;
	undefined field_0x2da;
	undefined field_0x2db;
	undefined field_0x2dc;
	undefined field_0x2dd;
	undefined field_0x2de;
	undefined field_0x2df;
	undefined field_0x2e0;
	undefined field_0x2e1;
	undefined field_0x2e2;
	undefined field_0x2e3;
	undefined field_0x2e4;
	undefined field_0x2e5;
	undefined field_0x2e6;
	undefined field_0x2e7;
	undefined field_0x2e8;
	undefined field_0x2e9;
	undefined field_0x2ea;
	undefined field_0x2eb;
	undefined field_0x2ec;
	undefined field_0x2ed;
	undefined field_0x2ee;
	undefined field_0x2ef;
	undefined field_0x2f0;
	undefined field_0x2f1;
	undefined field_0x2f2;
	undefined field_0x2f3;
	undefined field_0x2f4;
	undefined field_0x2f5;
	undefined field_0x2f6;
	undefined field_0x2f7;
	undefined field_0x2f8;
	undefined field_0x2f9;
	undefined field_0x2fa;
	undefined field_0x2fb;
	undefined field_0x2fc;
	undefined field_0x2fd;
	undefined field_0x2fe;
	undefined field_0x2ff;
	undefined field_0x300;
	undefined field_0x301;
	undefined field_0x302;
	undefined field_0x303;
	undefined field_0x304;
	undefined field_0x305;
	undefined field_0x306;
	undefined field_0x307;
	undefined field_0x308;
	undefined field_0x309;
	undefined field_0x30a;
	undefined field_0x30b;
	undefined field_0x30c;
	undefined field_0x30d;
	undefined field_0x30e;
	undefined field_0x30f;
	undefined field_0x310;
	undefined field_0x311;
	undefined field_0x312;
	undefined field_0x313;
	undefined field_0x314;
	undefined field_0x315;
	undefined field_0x316;
	undefined field_0x317;
	undefined field_0x318;
	undefined field_0x319;
	undefined field_0x31a;
	undefined field_0x31b;
	undefined field_0x31c;
	undefined field_0x31d;
	undefined field_0x31e;
	undefined field_0x31f;
	undefined field_0x320;
	undefined field_0x321;
	undefined field_0x322;
	undefined field_0x323;
	undefined field_0x324;
	undefined field_0x325;
	undefined field_0x326;
	undefined field_0x327;
	undefined field_0x328;
	undefined field_0x329;
	undefined field_0x32a;
	undefined field_0x32b;
	undefined field_0x32c;
	undefined field_0x32d;
	undefined field_0x32e;
	undefined field_0x32f;
	undefined field_0x330;
	undefined field_0x331;
	undefined field_0x332;
	undefined field_0x333;
	undefined field_0x334;
	undefined field_0x335;
	undefined field_0x336;
	undefined field_0x337;
	undefined field_0x338;
	undefined field_0x339;
	undefined field_0x33a;
	undefined field_0x33b;
	undefined field_0x33c;
	undefined field_0x33d;
	undefined field_0x33e;
	undefined field_0x33f;
	undefined field_0x340;
	undefined field_0x341;
	undefined field_0x342;
	undefined field_0x343;
	undefined field_0x344;
	undefined field_0x345;
	undefined field_0x346;
	undefined field_0x347;
	undefined field_0x348;
	undefined field_0x349;
	undefined field_0x34a;
	undefined field_0x34b;
	undefined field_0x34c;
	undefined field_0x34d;
	undefined field_0x34e;
	undefined field_0x34f;
	undefined field_0x350;
	undefined field_0x351;
	undefined field_0x352;
	undefined field_0x353;
	undefined field_0x354;
	undefined field_0x355;
	undefined field_0x356;
	undefined field_0x357;
	undefined field_0x358;
	undefined field_0x359;
	undefined field_0x35a;
	undefined field_0x35b;
	undefined field_0x35c;
	undefined field_0x35d;
	undefined field_0x35e;
	undefined field_0x35f;
	undefined field_0x360;
	undefined field_0x361;
	undefined field_0x362;
	undefined field_0x363;
	undefined field_0x364;
	undefined field_0x365;
	undefined field_0x366;
	undefined field_0x367;
	undefined field_0x368;
	undefined field_0x369;
	undefined field_0x36a;
	undefined field_0x36b;
	undefined field_0x36c;
	undefined field_0x36d;
	undefined field_0x36e;
	undefined field_0x36f;
	undefined field_0x370;
	undefined field_0x371;
	undefined field_0x372;
	undefined field_0x373;
	undefined field_0x374;
	undefined field_0x375;
	undefined field_0x376;
	undefined field_0x377;
	undefined field_0x378;
	undefined field_0x379;
	undefined field_0x37a;
	undefined field_0x37b;
	undefined field_0x37c;
	undefined field_0x37d;
	undefined field_0x37e;
	undefined field_0x37f;
	undefined field_0x380;
	undefined field_0x381;
	undefined field_0x382;
	undefined field_0x383;
	undefined field_0x384;
	undefined field_0x385;
	undefined field_0x386;
	undefined field_0x387;
	undefined field_0x388;
	undefined field_0x389;
	undefined field_0x38a;
	undefined field_0x38b;
	undefined field_0x38c;
	undefined field_0x38d;
	undefined field_0x38e;
	undefined field_0x38f;
	undefined field_0x390;
	undefined field_0x391;
	undefined field_0x392;
	undefined field_0x393;
	undefined field_0x394;
	undefined field_0x395;
	undefined field_0x396;
	undefined field_0x397;
	undefined field_0x398;
	undefined field_0x399;
	undefined field_0x39a;
	undefined field_0x39b;
	undefined field_0x39c;
	undefined field_0x39d;
	undefined field_0x39e;
	undefined field_0x39f;
	undefined field_0x3a0;
	undefined field_0x3a1;
	undefined field_0x3a2;
	undefined field_0x3a3;
	undefined field_0x3a4;
	undefined field_0x3a5;
	undefined field_0x3a6;
	undefined field_0x3a7;
	undefined field_0x3a8;
	undefined field_0x3a9;
	undefined field_0x3aa;
	undefined field_0x3ab;
	undefined field_0x3ac;
	undefined field_0x3ad;
	undefined field_0x3ae;
	undefined field_0x3af;
	undefined field_0x3b0;
	undefined field_0x3b1;
	undefined field_0x3b2;
	undefined field_0x3b3;
	undefined field_0x3b4;
	undefined field_0x3b5;
	undefined field_0x3b6;
	undefined field_0x3b7;
	undefined field_0x3b8;
	undefined field_0x3b9;
	undefined field_0x3ba;
	undefined field_0x3bb;
	undefined field_0x3bc;
	undefined field_0x3bd;
	undefined field_0x3be;
	undefined field_0x3bf;
	undefined field_0x3c0;
	undefined field_0x3c1;
	undefined field_0x3c2;
	undefined field_0x3c3;
	undefined field_0x3c4;
	undefined field_0x3c5;
	undefined field_0x3c6;
	undefined field_0x3c7;
	undefined field_0x3c8;
	undefined field_0x3c9;
	undefined field_0x3ca;
	undefined field_0x3cb;
	undefined field_0x3cc;
	undefined field_0x3cd;
	undefined field_0x3ce;
	undefined field_0x3cf;
	undefined field_0x3d0;
	undefined field_0x3d1;
	undefined field_0x3d2;
	undefined field_0x3d3;
	undefined field_0x3d4;
	undefined field_0x3d5;
	undefined field_0x3d6;
	undefined field_0x3d7;
	undefined field_0x3d8;
	undefined field_0x3d9;
	undefined field_0x3da;
	undefined field_0x3db;
	undefined field_0x3dc;
	undefined field_0x3dd;
	undefined field_0x3de;
	undefined field_0x3df;
	undefined field_0x3e0;
	undefined field_0x3e1;
	undefined field_0x3e2;
	undefined field_0x3e3;
	undefined field_0x3e4;
	undefined field_0x3e5;
	undefined field_0x3e6;
	undefined field_0x3e7;
	undefined field_0x3e8;
	undefined field_0x3e9;
	undefined field_0x3ea;
	undefined field_0x3eb;
	undefined field_0x3ec;
	undefined field_0x3ed;
	undefined field_0x3ee;
	undefined field_0x3ef;
	undefined field_0x3f0;
	undefined field_0x3f1;
	undefined field_0x3f2;
	undefined field_0x3f3;
	undefined field_0x3f4;
	undefined field_0x3f5;
	undefined field_0x3f6;
	undefined field_0x3f7;
	undefined field_0x3f8;
	undefined field_0x3f9;
	undefined field_0x3fa;
	undefined field_0x3fb;
	undefined field_0x3fc;
	undefined field_0x3fd;
	undefined field_0x3fe;
	undefined field_0x3ff;
	undefined field_0x400;
	undefined field_0x401;
	undefined field_0x402;
	undefined field_0x403;
	undefined field_0x404;
	undefined field_0x405;
	undefined field_0x406;
	undefined field_0x407;
	undefined field_0x408;
	undefined field_0x409;
	undefined field_0x40a;
	undefined field_0x40b;
	undefined field_0x40c;
	undefined field_0x40d;
	undefined field_0x40e;
	undefined field_0x40f;
	undefined field_0x410;
	undefined field_0x411;
	undefined field_0x412;
	undefined field_0x413;
	undefined field_0x414;
	undefined field_0x415;
	undefined field_0x416;
	undefined field_0x417;
	undefined field_0x418;
	undefined field_0x419;
	undefined field_0x41a;
	undefined field_0x41b;
	undefined field_0x41c;
	undefined field_0x41d;
	undefined field_0x41e;
	undefined field_0x41f;
	undefined field_0x420;
	undefined field_0x421;
	undefined field_0x422;
	undefined field_0x423;
	undefined field_0x424;
	undefined field_0x425;
	undefined field_0x426;
	undefined field_0x427;
	undefined field_0x428;
	undefined field_0x429;
	undefined field_0x42a;
	undefined field_0x42b;
	undefined field_0x42c;
	undefined field_0x42d;
	undefined field_0x42e;
	undefined field_0x42f;
	undefined field_0x430;
	undefined field_0x431;
	undefined field_0x432;
	undefined field_0x433;
	undefined field_0x434;
	undefined field_0x435;
	undefined field_0x436;
	undefined field_0x437;
	undefined field_0x438;
	undefined field_0x439;
	undefined field_0x43a;
	undefined field_0x43b;
	undefined field_0x43c;
	undefined field_0x43d;
	undefined field_0x43e;
	undefined field_0x43f;
	undefined field_0x440;
	undefined field_0x441;
	undefined field_0x442;
	undefined field_0x443;
	undefined field_0x444;
	undefined field_0x445;
	undefined field_0x446;
	undefined field_0x447;
	undefined field_0x448;
	undefined field_0x449;
	undefined field_0x44a;
	undefined field_0x44b;
	undefined field_0x44c;
	undefined field_0x44d;
	undefined field_0x44e;
	undefined field_0x44f;
	undefined field_0x450;
	undefined field_0x451;
	undefined field_0x452;
	undefined field_0x453;
	undefined field_0x454;
	undefined field_0x455;
	undefined field_0x456;
	undefined field_0x457;
	undefined field_0x458;
	undefined field_0x459;
	undefined field_0x45a;
	undefined field_0x45b;
	undefined field_0x45c;
	undefined field_0x45d;
	undefined field_0x45e;
	undefined field_0x45f;
	undefined field_0x460;
	undefined field_0x461;
	undefined field_0x462;
	undefined field_0x463;
	undefined field_0x464;
	undefined field_0x465;
	undefined field_0x466;
	undefined field_0x467;
	undefined field_0x468;
	undefined field_0x469;
	undefined field_0x46a;
	undefined field_0x46b;
	undefined field_0x46c;
	undefined field_0x46d;
	undefined field_0x46e;
	undefined field_0x46f;
	undefined field_0x470;
	undefined field_0x471;
	undefined field_0x472;
	undefined field_0x473;
	undefined field_0x474;
	undefined field_0x475;
	undefined field_0x476;
	undefined field_0x477;
	undefined field_0x478;
	undefined field_0x479;
	undefined field_0x47a;
	undefined field_0x47b;
	undefined field_0x47c;
	undefined field_0x47d;
	undefined field_0x47e;
	undefined field_0x47f;
	undefined field_0x480;
	undefined field_0x481;
	undefined field_0x482;
	undefined field_0x483;
	undefined field_0x484;
	undefined field_0x485;
	undefined field_0x486;
	undefined field_0x487;
	undefined field_0x488;
	undefined field_0x489;
	undefined field_0x48a;
	undefined field_0x48b;
	undefined field_0x48c;
	undefined field_0x48d;
	undefined field_0x48e;
	undefined field_0x48f;
	undefined field_0x490;
	undefined field_0x491;
	undefined field_0x492;
	undefined field_0x493;
	undefined field_0x494;
	undefined field_0x495;
	undefined field_0x496;
	undefined field_0x497;
	undefined field_0x498;
	undefined field_0x499;
	undefined field_0x49a;
	undefined field_0x49b;
	undefined field_0x49c;
	undefined field_0x49d;
	undefined field_0x49e;
	undefined field_0x49f;
	undefined field_0x4a0;
	undefined field_0x4a1;
	undefined field_0x4a2;
	undefined field_0x4a3;
	undefined field_0x4a4;
	undefined field_0x4a5;
	undefined field_0x4a6;
	undefined field_0x4a7;
	undefined field_0x4a8;
	undefined field_0x4a9;
	undefined field_0x4aa;
	undefined field_0x4ab;
	undefined field_0x4ac;
	undefined field_0x4ad;
	undefined field_0x4ae;
	undefined field_0x4af;
	undefined field_0x4b0;
	undefined field_0x4b1;
	undefined field_0x4b2;
	undefined field_0x4b3;
	undefined field_0x4b4;
	undefined field_0x4b5;
	undefined field_0x4b6;
	undefined field_0x4b7;
	undefined field_0x4b8;
	undefined field_0x4b9;
	undefined field_0x4ba;
	undefined field_0x4bb;
	undefined field_0x4bc;
	undefined field_0x4bd;
	undefined field_0x4be;
	undefined field_0x4bf;
	undefined field_0x4c0;
	undefined field_0x4c1;
	undefined field_0x4c2;
	undefined field_0x4c3;
	undefined field_0x4c4;
	undefined field_0x4c5;
	undefined field_0x4c6;
	undefined field_0x4c7;
	undefined field_0x4c8;
	undefined field_0x4c9;
	undefined field_0x4ca;
	undefined field_0x4cb;
	undefined field_0x4cc;
	undefined field_0x4cd;
	undefined field_0x4ce;
	undefined field_0x4cf;
	undefined field_0x4d0;
	undefined field_0x4d1;
	undefined field_0x4d2;
	undefined field_0x4d3;
	undefined field_0x4d4;
	undefined field_0x4d5;
	undefined field_0x4d6;
	undefined field_0x4d7;
	undefined field_0x4d8;
	undefined field_0x4d9;
	undefined field_0x4da;
	undefined field_0x4db;
	undefined field_0x4dc;
	undefined field_0x4dd;
	undefined field_0x4de;
	undefined field_0x4df;
	undefined field_0x4e0;
	undefined field_0x4e1;
	undefined field_0x4e2;
	undefined field_0x4e3;
	undefined field_0x4e4;
	undefined field_0x4e5;
	undefined field_0x4e6;
	undefined field_0x4e7;
	undefined field_0x4e8;
	undefined field_0x4e9;
	undefined field_0x4ea;
	undefined field_0x4eb;
	undefined field_0x4ec;
	undefined field_0x4ed;
	undefined field_0x4ee;
	undefined field_0x4ef;
	undefined field_0x4f0;
	undefined field_0x4f1;
	undefined field_0x4f2;
	undefined field_0x4f3;
	undefined field_0x4f4;
	undefined field_0x4f5;
	undefined field_0x4f6;
	undefined field_0x4f7;
	undefined field_0x4f8;
	undefined field_0x4f9;
	undefined field_0x4fa;
	undefined field_0x4fb;
	undefined field_0x4fc;
	undefined field_0x4fd;
	undefined field_0x4fe;
	undefined field_0x4ff;
	undefined field_0x500;
	undefined field_0x501;
	undefined field_0x502;
	undefined field_0x503;
	undefined field_0x504;
	undefined field_0x505;
	undefined field_0x506;
	undefined field_0x507;
	undefined field_0x508;
	undefined field_0x509;
	undefined field_0x50a;
	undefined field_0x50b;
	undefined field_0x50c;
	undefined field_0x50d;
	undefined field_0x50e;
	undefined field_0x50f;
	undefined field_0x510;
	undefined field_0x511;
	undefined field_0x512;
	undefined field_0x513;
	undefined field_0x514;
	undefined field_0x515;
	undefined field_0x516;
	undefined field_0x517;
	undefined field_0x518;
	undefined field_0x519;
	undefined field_0x51a;
	undefined field_0x51b;
	undefined field_0x51c;
	undefined field_0x51d;
	undefined field_0x51e;
	undefined field_0x51f;
	undefined field_0x520;
	undefined field_0x521;
	undefined field_0x522;
	undefined field_0x523;
	undefined field_0x524;
	undefined field_0x525;
	undefined field_0x526;
	undefined field_0x527;
	undefined field_0x528;
	undefined field_0x529;
	undefined field_0x52a;
	undefined field_0x52b;
	undefined field_0x52c;
	undefined field_0x52d;
	undefined field_0x52e;
	undefined field_0x52f;
	undefined field_0x530;
	undefined field_0x531;
	undefined field_0x532;
	undefined field_0x533;
	undefined field_0x534;
	undefined field_0x535;
	undefined field_0x536;
	undefined field_0x537;
	undefined field_0x538;
	undefined field_0x539;
	undefined field_0x53a;
	undefined field_0x53b;
	undefined field_0x53c;
	undefined field_0x53d;
	undefined field_0x53e;
	undefined field_0x53f;
	undefined field_0x540;
	undefined field_0x541;
	undefined field_0x542;
	undefined field_0x543;
	undefined field_0x544;
	undefined field_0x545;
	undefined field_0x546;
	undefined field_0x547;
	undefined field_0x548;
	undefined field_0x549;
	undefined field_0x54a;
	undefined field_0x54b;
	undefined field_0x54c;
	undefined field_0x54d;
	undefined field_0x54e;
	undefined field_0x54f;
	undefined field_0x550;
	undefined field_0x551;
	undefined field_0x552;
	undefined field_0x553;
	undefined field_0x554;
	undefined field_0x555;
	undefined field_0x556;
	undefined field_0x557;
	undefined field_0x558;
	undefined field_0x559;
	undefined field_0x55a;
	undefined field_0x55b;
	undefined field_0x55c;
	undefined field_0x55d;
	undefined field_0x55e;
	undefined field_0x55f;
	undefined field_0x560;
	undefined field_0x561;
	undefined field_0x562;
	undefined field_0x563;
	undefined field_0x564;
	undefined field_0x565;
	undefined field_0x566;
	undefined field_0x567;
	undefined field_0x568;
	undefined field_0x569;
	undefined field_0x56a;
	undefined field_0x56b;
	undefined field_0x56c;
	undefined field_0x56d;
	undefined field_0x56e;
	undefined field_0x56f;
	undefined field_0x570;
	undefined field_0x571;
	undefined field_0x572;
	undefined field_0x573;
	undefined field_0x574;
	undefined field_0x575;
	undefined field_0x576;
	undefined field_0x577;
	undefined field_0x578;
	undefined field_0x579;
	undefined field_0x57a;
	undefined field_0x57b;
	undefined field_0x57c;
	undefined field_0x57d;
	undefined field_0x57e;
	undefined field_0x57f;
	undefined field_0x580;
	undefined field_0x581;
	undefined field_0x582;
	undefined field_0x583;
	undefined field_0x584;
	undefined field_0x585;
	undefined field_0x586;
	undefined field_0x587;
	undefined field_0x588;
	undefined field_0x589;
	undefined field_0x58a;
	undefined field_0x58b;
	undefined field_0x58c;
	undefined field_0x58d;
	undefined field_0x58e;
	undefined field_0x58f;
	undefined field_0x590;
	undefined field_0x591;
	undefined field_0x592;
	undefined field_0x593;
	undefined field_0x594;
	undefined field_0x595;
	undefined field_0x596;
	undefined field_0x597;
	undefined field_0x598;
	undefined field_0x599;
	undefined field_0x59a;
	undefined field_0x59b;
	undefined field_0x59c;
	undefined field_0x59d;
	undefined field_0x59e;
	undefined field_0x59f;
	undefined field_0x5a0;
	undefined field_0x5a1;
	undefined field_0x5a2;
	undefined field_0x5a3;
	undefined field_0x5a4;
	undefined field_0x5a5;
	undefined field_0x5a6;
	undefined field_0x5a7;
	undefined field_0x5a8;
	undefined field_0x5a9;
	undefined field_0x5aa;
	undefined field_0x5ab;
	undefined field_0x5ac;
	undefined field_0x5ad;
	undefined field_0x5ae;
	undefined field_0x5af;
	undefined field_0x5b0;
	undefined field_0x5b1;
	undefined field_0x5b2;
	undefined field_0x5b3;
	undefined field_0x5b4;
	undefined field_0x5b5;
	undefined field_0x5b6;
	undefined field_0x5b7;
	undefined field_0x5b8;
	undefined field_0x5b9;
	undefined field_0x5ba;
	undefined field_0x5bb;
	undefined field_0x5bc;
	undefined field_0x5bd;
	undefined field_0x5be;
	undefined field_0x5bf;
	undefined field_0x5c0;
	undefined field_0x5c1;
	undefined field_0x5c2;
	undefined field_0x5c3;
	undefined field_0x5c4;
	undefined field_0x5c5;
	undefined field_0x5c6;
	undefined field_0x5c7;
	undefined field_0x5c8;
	undefined field_0x5c9;
	undefined field_0x5ca;
	undefined field_0x5cb;
	undefined field_0x5cc;
	undefined field_0x5cd;
	undefined field_0x5ce;
	undefined field_0x5cf;
	undefined field_0x5d0;
	undefined field_0x5d1;
	undefined field_0x5d2;
	undefined field_0x5d3;
	undefined field_0x5d4;
	undefined field_0x5d5;
	undefined field_0x5d6;
	undefined field_0x5d7;
	undefined field_0x5d8;
	undefined field_0x5d9;
	undefined field_0x5da;
	undefined field_0x5db;
	undefined field_0x5dc;
	undefined field_0x5dd;
	undefined field_0x5de;
	undefined field_0x5df;
	undefined field_0x5e0;
	undefined field_0x5e1;
	undefined field_0x5e2;
	undefined field_0x5e3;
	undefined field_0x5e4;
	undefined field_0x5e5;
	undefined field_0x5e6;
	undefined field_0x5e7;
	undefined field_0x5e8;
	undefined field_0x5e9;
	undefined field_0x5ea;
	undefined field_0x5eb;
	undefined field_0x5ec;
	undefined field_0x5ed;
	undefined field_0x5ee;
	undefined field_0x5ef;
	undefined field_0x5f0;
	undefined field_0x5f1;
	undefined field_0x5f2;
	undefined field_0x5f3;
	undefined field_0x5f4;
	undefined field_0x5f5;
	undefined field_0x5f6;
	undefined field_0x5f7;
	undefined field_0x5f8;
	undefined field_0x5f9;
	undefined field_0x5fa;
	undefined field_0x5fb;
	undefined field_0x5fc;
	undefined field_0x5fd;
	undefined field_0x5fe;
	undefined field_0x5ff;
	undefined field_0x600;
	undefined field_0x601;
	undefined field_0x602;
	undefined field_0x603;
	undefined field_0x604;
	undefined field_0x605;
	undefined field_0x606;
	undefined field_0x607;
	undefined field_0x608;
	undefined field_0x609;
	undefined field_0x60a;
	undefined field_0x60b;
	undefined field_0x60c;
	undefined field_0x60d;
	undefined field_0x60e;
	undefined field_0x60f;
	undefined field_0x610;
	undefined field_0x611;
	undefined field_0x612;
	undefined field_0x613;
	undefined field_0x614;
	undefined field_0x615;
	undefined field_0x616;
	undefined field_0x617;
	undefined field_0x618;
	undefined field_0x619;
	undefined field_0x61a;
	undefined field_0x61b;
	undefined field_0x61c;
	undefined field_0x61d;
	undefined field_0x61e;
	undefined field_0x61f;
	undefined field_0x620;
	undefined field_0x621;
	undefined field_0x622;
	undefined field_0x623;
	undefined field_0x624;
	undefined field_0x625;
	undefined field_0x626;
	undefined field_0x627;
	undefined field_0x628;
	undefined field_0x629;
	undefined field_0x62a;
	undefined field_0x62b;
	undefined field_0x62c;
	undefined field_0x62d;
	undefined field_0x62e;
	undefined field_0x62f;
	undefined field_0x630;
	undefined field_0x631;
	undefined field_0x632;
	undefined field_0x633;
	undefined field_0x634;
	undefined field_0x635;
	undefined field_0x636;
	undefined field_0x637;
	undefined field_0x638;
	undefined field_0x639;
	undefined field_0x63a;
	undefined field_0x63b;
	undefined field_0x63c;
	undefined field_0x63d;
	undefined field_0x63e;
	undefined field_0x63f;
	undefined field_0x640;
	undefined field_0x641;
	undefined field_0x642;
	undefined field_0x643;
	undefined field_0x644;
	undefined field_0x645;
	undefined field_0x646;
	undefined field_0x647;
	undefined field_0x648;
	undefined field_0x649;
	undefined field_0x64a;
	undefined field_0x64b;
	undefined field_0x64c;
	undefined field_0x64d;
	undefined field_0x64e;
	undefined field_0x64f;
	undefined field_0x650;
	undefined field_0x651;
	undefined field_0x652;
	undefined field_0x653;
	undefined field_0x654;
	undefined field_0x655;
	undefined field_0x656;
	undefined field_0x657;
	undefined field_0x658;
	undefined field_0x659;
	undefined field_0x65a;
	undefined field_0x65b;
	undefined field_0x65c;
	undefined field_0x65d;
	undefined field_0x65e;
	undefined field_0x65f;
	undefined field_0x660;
	undefined field_0x661;
	undefined field_0x662;
	undefined field_0x663;
	undefined field_0x664;
	undefined field_0x665;
	undefined field_0x666;
	undefined field_0x667;
	undefined field_0x668;
	undefined field_0x669;
	undefined field_0x66a;
	undefined field_0x66b;
	undefined field_0x66c;
	undefined field_0x66d;
	undefined field_0x66e;
	undefined field_0x66f;
	undefined field_0x670;
	undefined field_0x671;
	undefined field_0x672;
	undefined field_0x673;
	undefined field_0x674;
	undefined field_0x675;
	undefined field_0x676;
	undefined field_0x677;
	undefined field_0x678;
	undefined field_0x679;
	undefined field_0x67a;
	undefined field_0x67b;
	undefined field_0x67c;
	undefined field_0x67d;
	undefined field_0x67e;
	undefined field_0x67f;
	undefined field_0x680;
	undefined field_0x681;
	undefined field_0x682;
	undefined field_0x683;
	undefined field_0x684;
	undefined field_0x685;
	undefined field_0x686;
	undefined field_0x687;
	undefined field_0x688;
	undefined field_0x689;
	undefined field_0x68a;
	undefined field_0x68b;
	undefined field_0x68c;
	undefined field_0x68d;
	undefined field_0x68e;
	undefined field_0x68f;
	undefined field_0x690;
	undefined field_0x691;
	undefined field_0x692;
	undefined field_0x693;
	undefined field_0x694;
	undefined field_0x695;
	undefined field_0x696;
	undefined field_0x697;
	undefined field_0x698;
	undefined field_0x699;
	undefined field_0x69a;
	undefined field_0x69b;
	undefined field_0x69c;
	undefined field_0x69d;
	undefined field_0x69e;
	undefined field_0x69f;
	undefined field_0x6a0;
	undefined field_0x6a1;
	undefined field_0x6a2;
	undefined field_0x6a3;
	undefined field_0x6a4;
	undefined field_0x6a5;
	undefined field_0x6a6;
	undefined field_0x6a7;
	undefined field_0x6a8;
	undefined field_0x6a9;
	undefined field_0x6aa;
	undefined field_0x6ab;
	undefined field_0x6ac;
	undefined field_0x6ad;
	undefined field_0x6ae;
	undefined field_0x6af;
	undefined field_0x6b0;
	undefined field_0x6b1;
	undefined field_0x6b2;
	undefined field_0x6b3;
	undefined field_0x6b4;
	undefined field_0x6b5;
	undefined field_0x6b6;
	undefined field_0x6b7;
	undefined field_0x6b8;
	undefined field_0x6b9;
	undefined field_0x6ba;
	undefined field_0x6bb;
	undefined field_0x6bc;
	undefined field_0x6bd;
	undefined field_0x6be;
	undefined field_0x6bf;
	undefined field_0x6c0;
	undefined field_0x6c1;
	undefined field_0x6c2;
	undefined field_0x6c3;
	undefined field_0x6c4;
	undefined field_0x6c5;
	undefined field_0x6c6;
	undefined field_0x6c7;
	undefined field_0x6c8;
	undefined field_0x6c9;
	undefined field_0x6ca;
	undefined field_0x6cb;
	undefined field_0x6cc;
	undefined field_0x6cd;
	undefined field_0x6ce;
	undefined field_0x6cf;
	undefined field_0x6d0;
	undefined field_0x6d1;
	undefined field_0x6d2;
	undefined field_0x6d3;
	undefined field_0x6d4;
	undefined field_0x6d5;
	undefined field_0x6d6;
	undefined field_0x6d7;
	undefined field_0x6d8;
	undefined field_0x6d9;
	undefined field_0x6da;
	undefined field_0x6db;
	undefined field_0x6dc;
	undefined field_0x6dd;
	undefined field_0x6de;
	undefined field_0x6df;
	undefined field_0x6e0;
	undefined field_0x6e1;
	undefined field_0x6e2;
	undefined field_0x6e3;
	undefined field_0x6e4;
	undefined field_0x6e5;
	undefined field_0x6e6;
	undefined field_0x6e7;
	undefined field_0x6e8;
	undefined field_0x6e9;
	undefined field_0x6ea;
	undefined field_0x6eb;
	undefined field_0x6ec;
	undefined field_0x6ed;
	undefined field_0x6ee;
	undefined field_0x6ef;
	undefined field_0x6f0;
	undefined field_0x6f1;
	undefined field_0x6f2;
	undefined field_0x6f3;
	undefined field_0x6f4;
	undefined field_0x6f5;
	undefined field_0x6f6;
	undefined field_0x6f7;
	undefined field_0x6f8;
	undefined field_0x6f9;
	undefined field_0x6fa;
	undefined field_0x6fb;
	undefined field_0x6fc;
	undefined field_0x6fd;
	undefined field_0x6fe;
	undefined field_0x6ff;
	undefined field_0x700;
	undefined field_0x701;
	undefined field_0x702;
	undefined field_0x703;
	undefined field_0x704;
	undefined field_0x705;
	undefined field_0x706;
	undefined field_0x707;
	undefined field_0x708;
	undefined field_0x709;
	undefined field_0x70a;
	undefined field_0x70b;
	undefined field_0x70c;
	undefined field_0x70d;
	undefined field_0x70e;
	undefined field_0x70f;
	undefined field_0x710;
	undefined field_0x711;
	undefined field_0x712;
	undefined field_0x713;
	undefined field_0x714;
	undefined field_0x715;
	undefined field_0x716;
	undefined field_0x717;
	undefined field_0x718;
	undefined field_0x719;
	undefined field_0x71a;
	undefined field_0x71b;
	undefined field_0x71c;
	undefined field_0x71d;
	undefined field_0x71e;
	undefined field_0x71f;
	undefined field_0x720;
	undefined field_0x721;
	undefined field_0x722;
	undefined field_0x723;
	undefined field_0x724;
	undefined field_0x725;
	undefined field_0x726;
	undefined field_0x727;
	undefined field_0x728;
	undefined field_0x729;
	undefined field_0x72a;
	undefined field_0x72b;
	undefined field_0x72c;
	undefined field_0x72d;
	undefined field_0x72e;
	undefined field_0x72f;
	undefined field_0x730;
	undefined field_0x731;
	undefined field_0x732;
	undefined field_0x733;
	undefined field_0x734;
	undefined field_0x735;
	undefined field_0x736;
	undefined field_0x737;
	undefined field_0x738;
	undefined field_0x739;
	undefined field_0x73a;
	undefined field_0x73b;
	undefined field_0x73c;
	undefined field_0x73d;
	undefined field_0x73e;
	undefined field_0x73f;
	undefined field_0x740;
	undefined field_0x741;
	undefined field_0x742;
	undefined field_0x743;
	undefined field_0x744;
	undefined field_0x745;
	undefined field_0x746;
	undefined field_0x747;
	undefined field_0x748;
	undefined field_0x749;
	undefined field_0x74a;
	undefined field_0x74b;
	undefined field_0x74c;
	undefined field_0x74d;
	undefined field_0x74e;
	undefined field_0x74f;
	undefined field_0x750;
	undefined field_0x751;
	undefined field_0x752;
	undefined field_0x753;
	undefined field_0x754;
	undefined field_0x755;
	undefined field_0x756;
	undefined field_0x757;
	undefined field_0x758;
	undefined field_0x759;
	undefined field_0x75a;
	undefined field_0x75b;
	undefined field_0x75c;
	undefined field_0x75d;
	undefined field_0x75e;
	undefined field_0x75f;
	undefined field_0x760;
	undefined field_0x761;
	undefined field_0x762;
	undefined field_0x763;
	undefined field_0x764;
	undefined field_0x765;
	undefined field_0x766;
	undefined field_0x767;
	undefined field_0x768;
	undefined field_0x769;
	undefined field_0x76a;
	undefined field_0x76b;
	undefined field_0x76c;
	undefined field_0x76d;
	undefined field_0x76e;
	undefined field_0x76f;
	undefined field_0x770;
	undefined field_0x771;
	undefined field_0x772;
	undefined field_0x773;
	undefined field_0x774;
	undefined field_0x775;
	undefined field_0x776;
	undefined field_0x777;
	undefined field_0x778;
	undefined field_0x779;
	undefined field_0x77a;
	undefined field_0x77b;
	undefined field_0x77c;
	undefined field_0x77d;
	undefined field_0x77e;
	undefined field_0x77f;
	undefined field_0x780;
	undefined field_0x781;
	undefined field_0x782;
	undefined field_0x783;
	undefined field_0x784;
	undefined field_0x785;
	undefined field_0x786;
	undefined field_0x787;
	undefined field_0x788;
	undefined field_0x789;
	undefined field_0x78a;
	undefined field_0x78b;
	undefined field_0x78c;
	undefined field_0x78d;
	undefined field_0x78e;
	undefined field_0x78f;
	undefined field_0x790;
	undefined field_0x791;
	undefined field_0x792;
	undefined field_0x793;
	undefined field_0x794;
	undefined field_0x795;
	undefined field_0x796;
	undefined field_0x797;
	undefined field_0x798;
	undefined field_0x799;
	undefined field_0x79a;
	undefined field_0x79b;
	undefined field_0x79c;
	undefined field_0x79d;
	undefined field_0x79e;
	undefined field_0x79f;
	undefined field_0x7a0;
	undefined field_0x7a1;
	undefined field_0x7a2;
	undefined field_0x7a3;
	undefined field_0x7a4;
	undefined field_0x7a5;
	undefined field_0x7a6;
	undefined field_0x7a7;
	undefined field_0x7a8;
	undefined field_0x7a9;
	undefined field_0x7aa;
	undefined field_0x7ab;
	undefined field_0x7ac;
	undefined field_0x7ad;
	undefined field_0x7ae;
	undefined field_0x7af;
	undefined field_0x7b0;
	undefined field_0x7b1;
	undefined field_0x7b2;
	undefined field_0x7b3;
	undefined field_0x7b4;
	undefined field_0x7b5;
	undefined field_0x7b6;
	undefined field_0x7b7;
	undefined field_0x7b8;
	undefined field_0x7b9;
	undefined field_0x7ba;
	undefined field_0x7bb;
	undefined field_0x7bc;
	undefined field_0x7bd;
	undefined field_0x7be;
	undefined field_0x7bf;
	undefined field_0x7c0;
	undefined field_0x7c1;
	undefined field_0x7c2;
	undefined field_0x7c3;
	undefined field_0x7c4;
	undefined field_0x7c5;
	undefined field_0x7c6;
	undefined field_0x7c7;
	undefined field_0x7c8;
	undefined field_0x7c9;
	undefined field_0x7ca;
	undefined field_0x7cb;
	undefined field_0x7cc;
	undefined field_0x7cd;
	undefined field_0x7ce;
	undefined field_0x7cf;
	undefined field_0x7d0;
	undefined field_0x7d1;
	undefined field_0x7d2;
	undefined field_0x7d3;
	undefined field_0x7d4;
	undefined field_0x7d5;
	undefined field_0x7d6;
	undefined field_0x7d7;
	undefined field_0x7d8;
	undefined field_0x7d9;
	undefined field_0x7da;
	undefined field_0x7db;
	undefined field_0x7dc;
	undefined field_0x7dd;
	undefined field_0x7de;
	undefined field_0x7df;
	undefined field_0x7e0;
	undefined field_0x7e1;
	undefined field_0x7e2;
	undefined field_0x7e3;
	undefined field_0x7e4;
	undefined field_0x7e5;
	undefined field_0x7e6;
	undefined field_0x7e7;
	undefined field_0x7e8;
	undefined field_0x7e9;
	undefined field_0x7ea;
	undefined field_0x7eb;
	undefined field_0x7ec;
	undefined field_0x7ed;
	undefined field_0x7ee;
	undefined field_0x7ef;
	undefined field_0x7f0;
	undefined field_0x7f1;
	undefined field_0x7f2;
	undefined field_0x7f3;
	undefined field_0x7f4;
	undefined field_0x7f5;
	undefined field_0x7f6;
	undefined field_0x7f7;
	undefined field_0x7f8;
	undefined field_0x7f9;
	undefined field_0x7fa;
	undefined field_0x7fb;
	undefined field_0x7fc;
	undefined field_0x7fd;
	undefined field_0x7fe;
	undefined field_0x7ff;
	undefined field_0x800;
	undefined field_0x801;
	undefined field_0x802;
	undefined field_0x803;
	undefined field_0x804;
	undefined field_0x805;
	undefined field_0x806;
	undefined field_0x807;
	undefined field_0x808;
	undefined field_0x809;
	undefined field_0x80a;
	undefined field_0x80b;
	undefined field_0x80c;
	undefined field_0x80d;
	undefined field_0x80e;
	undefined field_0x80f;
	undefined field_0x810;
	undefined field_0x811;
	undefined field_0x812;
	undefined field_0x813;
	undefined field_0x814;
	undefined field_0x815;
	undefined field_0x816;
	undefined field_0x817;
	undefined field_0x818;
	undefined field_0x819;
	undefined field_0x81a;
	undefined field_0x81b;
	undefined field_0x81c;
	undefined field_0x81d;
	undefined field_0x81e;
	undefined field_0x81f;
	undefined field_0x820;
	undefined field_0x821;
	undefined field_0x822;
	undefined field_0x823;
	undefined field_0x824;
	undefined field_0x825;
	undefined field_0x826;
	undefined field_0x827;
	undefined field_0x828;
	undefined field_0x829;
	undefined field_0x82a;
	undefined field_0x82b;
	undefined field_0x82c;
	undefined field_0x82d;
	undefined field_0x82e;
	undefined field_0x82f;
	undefined field_0x830;
	undefined field_0x831;
	undefined field_0x832;
	undefined field_0x833;
	undefined field_0x834;
	undefined field_0x835;
	undefined field_0x836;
	undefined field_0x837;
	undefined field_0x838;
	undefined field_0x839;
	undefined field_0x83a;
	undefined field_0x83b;
	undefined field_0x83c;
	undefined field_0x83d;
	undefined field_0x83e;
	undefined field_0x83f;
	undefined field_0x840;
	undefined field_0x841;
	undefined field_0x842;
	undefined field_0x843;
	undefined field_0x844;
	undefined field_0x845;
	undefined field_0x846;
	undefined field_0x847;
	undefined field_0x848;
	undefined field_0x849;
	undefined field_0x84a;
	undefined field_0x84b;
	undefined field_0x84c;
	undefined field_0x84d;
	undefined field_0x84e;
	undefined field_0x84f;
	undefined field_0x850;
	undefined field_0x851;
	undefined field_0x852;
	undefined field_0x853;
	undefined field_0x854;
	undefined field_0x855;
	undefined field_0x856;
	undefined field_0x857;
	undefined field_0x858;
	undefined field_0x859;
	undefined field_0x85a;
	undefined field_0x85b;
	undefined field_0x85c;
	undefined field_0x85d;
	undefined field_0x85e;
	undefined field_0x85f;
	undefined field_0x860;
	undefined field_0x861;
	undefined field_0x862;
	undefined field_0x863;
	undefined field_0x864;
	undefined field_0x865;
	undefined field_0x866;
	undefined field_0x867;
	undefined field_0x868;
	undefined field_0x869;
	undefined field_0x86a;
	undefined field_0x86b;
	undefined field_0x86c;
	undefined field_0x86d;
	undefined field_0x86e;
	undefined field_0x86f;
	undefined field_0x870;
	undefined field_0x871;
	undefined field_0x872;
	undefined field_0x873;
	undefined field_0x874;
	undefined field_0x875;
	undefined field_0x876;
	undefined field_0x877;
	undefined field_0x878;
	undefined field_0x879;
	undefined field_0x87a;
	undefined field_0x87b;
	undefined field_0x87c;
	undefined field_0x87d;
	undefined field_0x87e;
	undefined field_0x87f;
	undefined field_0x880;
	undefined field_0x881;
	undefined field_0x882;
	undefined field_0x883;
	undefined field_0x884;
	undefined field_0x885;
	undefined field_0x886;
	undefined field_0x887;
	undefined field_0x888;
	undefined field_0x889;
	undefined field_0x88a;
	undefined field_0x88b;
	undefined field_0x88c;
	undefined field_0x88d;
	undefined field_0x88e;
	undefined field_0x88f;
	undefined field_0x890;
	undefined field_0x891;
	undefined field_0x892;
	undefined field_0x893;
	undefined field_0x894;
	undefined field_0x895;
	undefined field_0x896;
	undefined field_0x897;
	undefined field_0x898;
	undefined field_0x899;
	undefined field_0x89a;
	undefined field_0x89b;
	undefined field_0x89c;
	undefined field_0x89d;
	undefined field_0x89e;
	undefined field_0x89f;
	undefined field_0x8a0;
	undefined field_0x8a1;
	undefined field_0x8a2;
	undefined field_0x8a3;
	undefined field_0x8a4;
	undefined field_0x8a5;
	undefined field_0x8a6;
	undefined field_0x8a7;
	undefined field_0x8a8;
	undefined field_0x8a9;
	undefined field_0x8aa;
	undefined field_0x8ab;
	undefined field_0x8ac;
	undefined field_0x8ad;
	undefined field_0x8ae;
	undefined field_0x8af;
	undefined field_0x8b0;
	undefined field_0x8b1;
	undefined field_0x8b2;
	undefined field_0x8b3;
	undefined field_0x8b4;
	undefined field_0x8b5;
	undefined field_0x8b6;
	undefined field_0x8b7;
	undefined field_0x8b8;
	undefined field_0x8b9;
	undefined field_0x8ba;
	undefined field_0x8bb;
	undefined field_0x8bc;
	undefined field_0x8bd;
	undefined field_0x8be;
	undefined field_0x8bf;
	undefined field_0x8c0;
	undefined field_0x8c1;
	undefined field_0x8c2;
	undefined field_0x8c3;
	undefined field_0x8c4;
	undefined field_0x8c5;
	undefined field_0x8c6;
	undefined field_0x8c7;
	undefined field_0x8c8;
	undefined field_0x8c9;
	undefined field_0x8ca;
	undefined field_0x8cb;
	undefined field_0x8cc;
	undefined field_0x8cd;
	undefined field_0x8ce;
	undefined field_0x8cf;
	undefined field_0x8d0;
	undefined field_0x8d1;
	undefined field_0x8d2;
	undefined field_0x8d3;
	undefined field_0x8d4;
	undefined field_0x8d5;
	undefined field_0x8d6;
	undefined field_0x8d7;
	undefined field_0x8d8;
	undefined field_0x8d9;
	undefined field_0x8da;
	undefined field_0x8db;
	undefined field_0x8dc;
	undefined field_0x8dd;
	undefined field_0x8de;
	undefined field_0x8df;
	undefined field_0x8e0;
	undefined field_0x8e1;
	undefined field_0x8e2;
	undefined field_0x8e3;
	undefined field_0x8e4;
	undefined field_0x8e5;
	undefined field_0x8e6;
	undefined field_0x8e7;
	undefined field_0x8e8;
	undefined field_0x8e9;
	undefined field_0x8ea;
	undefined field_0x8eb;
	undefined field_0x8ec;
	undefined field_0x8ed;
	undefined field_0x8ee;
	undefined field_0x8ef;
	undefined field_0x8f0;
	undefined field_0x8f1;
	undefined field_0x8f2;
	undefined field_0x8f3;
	undefined field_0x8f4;
	undefined field_0x8f5;
	undefined field_0x8f6;
	undefined field_0x8f7;
	undefined field_0x8f8;
	undefined field_0x8f9;
	undefined field_0x8fa;
	undefined field_0x8fb;
	undefined field_0x8fc;
	undefined field_0x8fd;
	undefined field_0x8fe;
	undefined field_0x8ff;
	undefined field_0x900;
	undefined field_0x901;
	undefined field_0x902;
	undefined field_0x903;
	undefined field_0x904;
	undefined field_0x905;
	undefined field_0x906;
	undefined field_0x907;
	undefined field_0x908;
	undefined field_0x909;
	undefined field_0x90a;
	undefined field_0x90b;
	undefined field_0x90c;
	undefined field_0x90d;
	undefined field_0x90e;
	undefined field_0x90f;
	undefined field_0x910;
	undefined field_0x911;
	undefined field_0x912;
	undefined field_0x913;
	undefined field_0x914;
	undefined field_0x915;
	undefined field_0x916;
	undefined field_0x917;
	undefined field_0x918;
	undefined field_0x919;
	undefined field_0x91a;
	undefined field_0x91b;
	undefined field_0x91c;
	undefined field_0x91d;
	undefined field_0x91e;
	undefined field_0x91f;
	undefined field_0x920;
	undefined field_0x921;
	undefined field_0x922;
	undefined field_0x923;
	undefined field_0x924;
	undefined field_0x925;
	undefined field_0x926;
	undefined field_0x927;
	undefined field_0x928;
	undefined field_0x929;
	undefined field_0x92a;
	undefined field_0x92b;
	undefined field_0x92c;
	undefined field_0x92d;
	undefined field_0x92e;
	undefined field_0x92f;
	undefined field_0x930;
	undefined field_0x931;
	undefined field_0x932;
	undefined field_0x933;
	undefined field_0x934;
	undefined field_0x935;
	undefined field_0x936;
	undefined field_0x937;
	undefined field_0x938;
	undefined field_0x939;
	undefined field_0x93a;
	undefined field_0x93b;
	undefined field_0x93c;
	undefined field_0x93d;
	undefined field_0x93e;
	undefined field_0x93f;
	undefined field_0x940;
	undefined field_0x941;
	undefined field_0x942;
	undefined field_0x943;
	undefined field_0x944;
	undefined field_0x945;
	undefined field_0x946;
	undefined field_0x947;
	undefined field_0x948;
	undefined field_0x949;
	undefined field_0x94a;
	undefined field_0x94b;
	undefined field_0x94c;
	undefined field_0x94d;
	undefined field_0x94e;
	undefined field_0x94f;
	undefined field_0x950;
	undefined field_0x951;
	undefined field_0x952;
	undefined field_0x953;
	undefined field_0x954;
	undefined field_0x955;
	undefined field_0x956;
	undefined field_0x957;
	undefined field_0x958;
	undefined field_0x959;
	undefined field_0x95a;
	undefined field_0x95b;
	undefined field_0x95c;
	undefined field_0x95d;
	undefined field_0x95e;
	undefined field_0x95f;
	undefined field_0x960;
	undefined field_0x961;
	undefined field_0x962;
	undefined field_0x963;
	undefined field_0x964;
	undefined field_0x965;
	undefined field_0x966;
	undefined field_0x967;
	undefined field_0x968;
	undefined field_0x969;
	undefined field_0x96a;
	undefined field_0x96b;
	undefined field_0x96c;
	undefined field_0x96d;
	undefined field_0x96e;
	undefined field_0x96f;
	undefined field_0x970;
	undefined field_0x971;
	undefined field_0x972;
	undefined field_0x973;
	undefined field_0x974;
	undefined field_0x975;
	undefined field_0x976;
	undefined field_0x977;
	undefined field_0x978;
	undefined field_0x979;
	undefined field_0x97a;
	undefined field_0x97b;
	undefined field_0x97c;
	undefined field_0x97d;
	undefined field_0x97e;
	undefined field_0x97f;
	undefined field_0x980;
	undefined field_0x981;
	undefined field_0x982;
	undefined field_0x983;
	undefined field_0x984;
	undefined field_0x985;
	undefined field_0x986;
	undefined field_0x987;
	undefined field_0x988;
	undefined field_0x989;
	undefined field_0x98a;
	undefined field_0x98b;
	undefined field_0x98c;
	undefined field_0x98d;
	undefined field_0x98e;
	undefined field_0x98f;
	undefined field_0x990;
	undefined field_0x991;
	undefined field_0x992;
	undefined field_0x993;
	undefined field_0x994;
	undefined field_0x995;
	undefined field_0x996;
	undefined field_0x997;
	undefined field_0x998;
	undefined field_0x999;
	undefined field_0x99a;
	undefined field_0x99b;
	undefined field_0x99c;
	undefined field_0x99d;
	undefined field_0x99e;
	undefined field_0x99f;
	undefined field_0x9a0;
	undefined field_0x9a1;
	undefined field_0x9a2;
	undefined field_0x9a3;
	undefined field_0x9a4;
	undefined field_0x9a5;
	undefined field_0x9a6;
	undefined field_0x9a7;
	undefined field_0x9a8;
	undefined field_0x9a9;
	undefined field_0x9aa;
	undefined field_0x9ab;
	undefined field_0x9ac;
	undefined field_0x9ad;
	undefined field_0x9ae;
	undefined field_0x9af;
	undefined field_0x9b0;
	undefined field_0x9b1;
	undefined field_0x9b2;
	undefined field_0x9b3;
	undefined field_0x9b4;
	undefined field_0x9b5;
	undefined field_0x9b6;
	undefined field_0x9b7;
	undefined field_0x9b8;
	undefined field_0x9b9;
	undefined field_0x9ba;
	undefined field_0x9bb;
	undefined field_0x9bc;
	undefined field_0x9bd;
	undefined field_0x9be;
	undefined field_0x9bf;
	undefined field_0x9c0;
	undefined field_0x9c1;
	undefined field_0x9c2;
	undefined field_0x9c3;
	undefined field_0x9c4;
	undefined field_0x9c5;
	undefined field_0x9c6;
	undefined field_0x9c7;
	undefined field_0x9c8;
	undefined field_0x9c9;
	undefined field_0x9ca;
	undefined field_0x9cb;
	undefined field_0x9cc;
	undefined field_0x9cd;
	undefined field_0x9ce;
	undefined field_0x9cf;
	undefined field_0x9d0;
	undefined field_0x9d1;
	undefined field_0x9d2;
	undefined field_0x9d3;
	undefined field_0x9d4;
	undefined field_0x9d5;
	undefined field_0x9d6;
	undefined field_0x9d7;
	undefined field_0x9d8;
	undefined field_0x9d9;
	undefined field_0x9da;
	undefined field_0x9db;
	undefined field_0x9dc;
	undefined field_0x9dd;
	undefined field_0x9de;
	undefined field_0x9df;
	undefined field_0x9e0;
	undefined field_0x9e1;
	undefined field_0x9e2;
	undefined field_0x9e3;
	undefined field_0x9e4;
	undefined field_0x9e5;
	undefined field_0x9e6;
	undefined field_0x9e7;
	undefined field_0x9e8;
	undefined field_0x9e9;
	undefined field_0x9ea;
	undefined field_0x9eb;
	undefined field_0x9ec;
	undefined field_0x9ed;
	undefined field_0x9ee;
	undefined field_0x9ef;
	undefined field_0x9f0;
	undefined field_0x9f1;
	undefined field_0x9f2;
	undefined field_0x9f3;
	undefined field_0x9f4;
	undefined field_0x9f5;
	undefined field_0x9f6;
	undefined field_0x9f7;
	undefined field_0x9f8;
	undefined field_0x9f9;
	undefined field_0x9fa;
	undefined field_0x9fb;
	undefined field_0x9fc;
	undefined field_0x9fd;
	undefined field_0x9fe;
	undefined field_0x9ff;
	undefined field_0xa00;
	undefined field_0xa01;
	undefined field_0xa02;
	undefined field_0xa03;
	undefined field_0xa04;
	undefined field_0xa05;
	undefined field_0xa06;
	undefined field_0xa07;
	undefined field_0xa08;
	undefined field_0xa09;
	undefined field_0xa0a;
	undefined field_0xa0b;
	undefined field_0xa0c;
	undefined field_0xa0d;
	undefined field_0xa0e;
	undefined field_0xa0f;
	undefined field_0xa10;
	undefined field_0xa11;
	undefined field_0xa12;
	undefined field_0xa13;
	undefined field_0xa14;
	undefined field_0xa15;
	undefined field_0xa16;
	undefined field_0xa17;
	undefined field_0xa18;
	undefined field_0xa19;
	undefined field_0xa1a;
	undefined field_0xa1b;
	undefined field_0xa1c;
	undefined field_0xa1d;
	undefined field_0xa1e;
	undefined field_0xa1f;
	undefined field_0xa20;
	undefined field_0xa21;
	undefined field_0xa22;
	undefined field_0xa23;
	undefined field_0xa24;
	undefined field_0xa25;
	undefined field_0xa26;
	undefined field_0xa27;
	undefined field_0xa28;
	undefined field_0xa29;
	undefined field_0xa2a;
	undefined field_0xa2b;
	undefined field_0xa2c;
	undefined field_0xa2d;
	undefined field_0xa2e;
	undefined field_0xa2f;
	undefined field_0xa30;
	undefined field_0xa31;
	undefined field_0xa32;
	undefined field_0xa33;
	undefined field_0xa34;
	undefined field_0xa35;
	undefined field_0xa36;
	undefined field_0xa37;
	undefined field_0xa38;
	undefined field_0xa39;
	undefined field_0xa3a;
	undefined field_0xa3b;
	undefined field_0xa3c;
	undefined field_0xa3d;
	undefined field_0xa3e;
	undefined field_0xa3f;
	undefined field_0xa40;
	undefined field_0xa41;
	undefined field_0xa42;
	undefined field_0xa43;
	undefined field_0xa44;
	undefined field_0xa45;
	undefined field_0xa46;
	undefined field_0xa47;
	undefined field_0xa48;
	undefined field_0xa49;
	undefined field_0xa4a;
	undefined field_0xa4b;
	undefined field_0xa4c;
	undefined field_0xa4d;
	undefined field_0xa4e;
	undefined field_0xa4f;
	undefined field_0xa50;
	undefined field_0xa51;
	undefined field_0xa52;
	undefined field_0xa53;
	undefined field_0xa54;
	undefined field_0xa55;
	undefined field_0xa56;
	undefined field_0xa57;
	undefined field_0xa58;
	undefined field_0xa59;
	undefined field_0xa5a;
	undefined field_0xa5b;
	undefined field_0xa5c;
	undefined field_0xa5d;
	undefined field_0xa5e;
	undefined field_0xa5f;
	undefined field_0xa60;
	undefined field_0xa61;
	undefined field_0xa62;
	undefined field_0xa63;
	undefined field_0xa64;
	undefined field_0xa65;
	undefined field_0xa66;
	undefined field_0xa67;
	undefined field_0xa68;
	undefined field_0xa69;
	undefined field_0xa6a;
	undefined field_0xa6b;
	undefined field_0xa6c;
	undefined field_0xa6d;
	undefined field_0xa6e;
	undefined field_0xa6f;
	undefined field_0xa70;
	undefined field_0xa71;
	undefined field_0xa72;
	undefined field_0xa73;
	undefined field_0xa74;
	undefined field_0xa75;
	undefined field_0xa76;
	undefined field_0xa77;
	undefined field_0xa78;
	undefined field_0xa79;
	undefined field_0xa7a;
	undefined field_0xa7b;
	undefined field_0xa7c;
	undefined field_0xa7d;
	undefined field_0xa7e;
	undefined field_0xa7f;
	undefined field_0xa80;
	undefined field_0xa81;
	undefined field_0xa82;
	undefined field_0xa83;
	undefined field_0xa84;
	undefined field_0xa85;
	undefined field_0xa86;
	undefined field_0xa87;
	undefined field_0xa88;
	undefined field_0xa89;
	undefined field_0xa8a;
	undefined field_0xa8b;
	undefined field_0xa8c;
	undefined field_0xa8d;
	undefined field_0xa8e;
	undefined field_0xa8f;
	undefined field_0xa90;
	undefined field_0xa91;
	undefined field_0xa92;
	undefined field_0xa93;
	undefined field_0xa94;
	undefined field_0xa95;
	undefined field_0xa96;
	undefined field_0xa97;
	undefined field_0xa98;
	undefined field_0xa99;
	undefined field_0xa9a;
	undefined field_0xa9b;
	undefined field_0xa9c;
	undefined field_0xa9d;
	undefined field_0xa9e;
	undefined field_0xa9f;
	undefined field_0xaa0;
	undefined field_0xaa1;
	undefined field_0xaa2;
	undefined field_0xaa3;
	undefined field_0xaa4;
	undefined field_0xaa5;
	undefined field_0xaa6;
	undefined field_0xaa7;
	undefined field_0xaa8;
	undefined field_0xaa9;
	undefined field_0xaaa;
	undefined field_0xaab;
	undefined field_0xaac;
	undefined field_0xaad;
	undefined field_0xaae;
	undefined field_0xaaf;
	undefined field_0xab0;
	undefined field_0xab1;
	undefined field_0xab2;
	undefined field_0xab3;
	undefined field_0xab4;
	undefined field_0xab5;
	undefined field_0xab6;
	undefined field_0xab7;
	undefined field_0xab8;
	undefined field_0xab9;
	undefined field_0xaba;
	undefined field_0xabb;
	undefined field_0xabc;
	undefined field_0xabd;
	undefined field_0xabe;
	undefined field_0xabf;
	undefined field_0xac0;
	undefined field_0xac1;
	undefined field_0xac2;
	undefined field_0xac3;
	undefined field_0xac4;
	undefined field_0xac5;
	undefined field_0xac6;
	undefined field_0xac7;
	undefined field_0xac8;
	undefined field_0xac9;
	undefined field_0xaca;
	undefined field_0xacb;
	undefined field_0xacc;
	undefined field_0xacd;
	undefined field_0xace;
	undefined field_0xacf;
	undefined field_0xad0;
	undefined field_0xad1;
	undefined field_0xad2;
	undefined field_0xad3;
	undefined field_0xad4;
	undefined field_0xad5;
	undefined field_0xad6;
	undefined field_0xad7;
	undefined field_0xad8;
	undefined field_0xad9;
	undefined field_0xada;
	undefined field_0xadb;
	undefined field_0xadc;
	undefined field_0xadd;
	undefined field_0xade;
	undefined field_0xadf;
	undefined field_0xae0;
	undefined field_0xae1;
	undefined field_0xae2;
	undefined field_0xae3;
	undefined field_0xae4;
	undefined field_0xae5;
	undefined field_0xae6;
	undefined field_0xae7;
	undefined field_0xae8;
	undefined field_0xae9;
	undefined field_0xaea;
	undefined field_0xaeb;
	undefined field_0xaec;
	undefined field_0xaed;
	undefined field_0xaee;
	undefined field_0xaef;
	undefined field_0xaf0;
	undefined field_0xaf1;
	undefined field_0xaf2;
	undefined field_0xaf3;
	undefined field_0xaf4;
	undefined field_0xaf5;
	undefined field_0xaf6;
	undefined field_0xaf7;
	undefined field_0xaf8;
	undefined field_0xaf9;
	undefined field_0xafa;
	undefined field_0xafb;
	undefined field_0xafc;
	undefined field_0xafd;
	undefined field_0xafe;
	undefined field_0xaff;
	undefined field_0xb00;
	undefined field_0xb01;
	undefined field_0xb02;
	undefined field_0xb03;
	undefined field_0xb04;
	undefined field_0xb05;
	undefined field_0xb06;
	undefined field_0xb07;
	undefined field_0xb08;
	undefined field_0xb09;
	undefined field_0xb0a;
	undefined field_0xb0b;
	undefined field_0xb0c;
	undefined field_0xb0d;
	undefined field_0xb0e;
	undefined field_0xb0f;
	undefined field_0xb10;
	undefined field_0xb11;
	undefined field_0xb12;
	undefined field_0xb13;
	undefined field_0xb14;
	undefined field_0xb15;
	undefined field_0xb16;
	undefined field_0xb17;
	undefined field_0xb18;
	undefined field_0xb19;
	undefined field_0xb1a;
	undefined field_0xb1b;
	undefined field_0xb1c;
	undefined field_0xb1d;
	undefined field_0xb1e;
	undefined field_0xb1f;
	undefined field_0xb20;
	undefined field_0xb21;
	undefined field_0xb22;
	undefined field_0xb23;
	undefined field_0xb24;
	undefined field_0xb25;
	undefined field_0xb26;
	undefined field_0xb27;
	undefined field_0xb28;
	undefined field_0xb29;
	undefined field_0xb2a;
	undefined field_0xb2b;
	undefined field_0xb2c;
	undefined field_0xb2d;
	undefined field_0xb2e;
	undefined field_0xb2f;
	undefined field_0xb30;
	undefined field_0xb31;
	undefined field_0xb32;
	undefined field_0xb33;
	undefined field_0xb34;
	undefined field_0xb35;
	undefined field_0xb36;
	undefined field_0xb37;
	undefined field_0xb38;
	undefined field_0xb39;
	undefined field_0xb3a;
	undefined field_0xb3b;
	undefined field_0xb3c;
	undefined field_0xb3d;
	undefined field_0xb3e;
	undefined field_0xb3f;
	undefined field_0xb40;
	undefined field_0xb41;
	undefined field_0xb42;
	undefined field_0xb43;
	undefined field_0xb44;
	undefined field_0xb45;
	undefined field_0xb46;
	undefined field_0xb47;
	undefined field_0xb48;
	undefined field_0xb49;
	undefined field_0xb4a;
	undefined field_0xb4b;
	undefined field_0xb4c;
	undefined field_0xb4d;
	undefined field_0xb4e;
	undefined field_0xb4f;
	undefined field_0xb50;
	undefined field_0xb51;
	undefined field_0xb52;
	undefined field_0xb53;
	undefined field_0xb54;
	undefined field_0xb55;
	undefined field_0xb56;
	undefined field_0xb57;
	undefined field_0xb58;
	undefined field_0xb59;
	undefined field_0xb5a;
	undefined field_0xb5b;
	undefined field_0xb5c;
	undefined field_0xb5d;
	undefined field_0xb5e;
	undefined field_0xb5f;
	undefined field_0xb60;
	undefined field_0xb61;
	undefined field_0xb62;
	undefined field_0xb63;
	undefined field_0xb64;
	undefined field_0xb65;
	undefined field_0xb66;
	undefined field_0xb67;
	undefined field_0xb68;
	undefined field_0xb69;
	undefined field_0xb6a;
	undefined field_0xb6b;
	undefined field_0xb6c;
	undefined field_0xb6d;
	undefined field_0xb6e;
	undefined field_0xb6f;
	undefined field_0xb70;
	undefined field_0xb71;
	undefined field_0xb72;
	undefined field_0xb73;
	undefined field_0xb74;
	undefined field_0xb75;
	undefined field_0xb76;
	undefined field_0xb77;
	undefined field_0xb78;
	undefined field_0xb79;
	undefined field_0xb7a;
	undefined field_0xb7b;
	undefined field_0xb7c;
	undefined field_0xb7d;
	undefined field_0xb7e;
	undefined field_0xb7f;
	undefined field_0xb80;
	undefined field_0xb81;
	undefined field_0xb82;
	undefined field_0xb83;
	undefined field_0xb84;
	undefined field_0xb85;
	undefined field_0xb86;
	undefined field_0xb87;
	undefined field_0xb88;
	undefined field_0xb89;
	undefined field_0xb8a;
	undefined field_0xb8b;
	undefined field_0xb8c;
	undefined field_0xb8d;
	undefined field_0xb8e;
	undefined field_0xb8f;
	undefined field_0xb90;
	undefined field_0xb91;
	undefined field_0xb92;
	undefined field_0xb93;
	undefined field_0xb94;
	undefined field_0xb95;
	undefined field_0xb96;
	undefined field_0xb97;
	undefined field_0xb98;
	undefined field_0xb99;
	undefined field_0xb9a;
	undefined field_0xb9b;
	undefined field_0xb9c;
	undefined field_0xb9d;
	undefined field_0xb9e;
	undefined field_0xb9f;
	undefined field_0xba0;
	undefined field_0xba1;
	undefined field_0xba2;
	undefined field_0xba3;
	undefined field_0xba4;
	undefined field_0xba5;
	undefined field_0xba6;
	undefined field_0xba7;
	undefined field_0xba8;
	undefined field_0xba9;
	undefined field_0xbaa;
	undefined field_0xbab;
	undefined field_0xbac;
	undefined field_0xbad;
	undefined field_0xbae;
	undefined field_0xbaf;
	undefined field_0xbb0;
	undefined field_0xbb1;
	undefined field_0xbb2;
	undefined field_0xbb3;
	undefined field_0xbb4;
	undefined field_0xbb5;
	undefined field_0xbb6;
	undefined field_0xbb7;
	undefined field_0xbb8;
	undefined field_0xbb9;
	undefined field_0xbba;
	undefined field_0xbbb;
	undefined field_0xbbc;
	undefined field_0xbbd;
	undefined field_0xbbe;
	undefined field_0xbbf;
	undefined field_0xbc0;
	undefined field_0xbc1;
	undefined field_0xbc2;
	undefined field_0xbc3;
	undefined field_0xbc4;
	undefined field_0xbc5;
	undefined field_0xbc6;
	undefined field_0xbc7;
	undefined field_0xbc8;
	undefined field_0xbc9;
	undefined field_0xbca;
	undefined field_0xbcb;
	undefined field_0xbcc;
	undefined field_0xbcd;
	undefined field_0xbce;
	undefined field_0xbcf;
	undefined field_0xbd0;
	undefined field_0xbd1;
	undefined field_0xbd2;
	undefined field_0xbd3;
	undefined field_0xbd4;
	undefined field_0xbd5;
	undefined field_0xbd6;
	undefined field_0xbd7;
	undefined field_0xbd8;
	undefined field_0xbd9;
	undefined field_0xbda;
	undefined field_0xbdb;
	undefined field_0xbdc;
	undefined field_0xbdd;
	undefined field_0xbde;
	undefined field_0xbdf;
	undefined field_0xbe0;
	undefined field_0xbe1;
	undefined field_0xbe2;
	undefined field_0xbe3;
	undefined field_0xbe4;
	undefined field_0xbe5;
	undefined field_0xbe6;
	undefined field_0xbe7;
	undefined field_0xbe8;
	undefined field_0xbe9;
	undefined field_0xbea;
	undefined field_0xbeb;
	undefined field_0xbec;
	undefined field_0xbed;
	undefined field_0xbee;
	undefined field_0xbef;
	undefined field_0xbf0;
	undefined field_0xbf1;
	undefined field_0xbf2;
	undefined field_0xbf3;
	undefined field_0xbf4;
	undefined field_0xbf5;
	undefined field_0xbf6;
	undefined field_0xbf7;
	undefined field_0xbf8;
	undefined field_0xbf9;
	undefined field_0xbfa;
	undefined field_0xbfb;
	undefined field_0xbfc;
	undefined field_0xbfd;
	undefined field_0xbfe;
	undefined field_0xbff;
	undefined field_0xc00;
	undefined field_0xc01;
	undefined field_0xc02;
	undefined field_0xc03;
	undefined field_0xc04;
	undefined field_0xc05;
	undefined field_0xc06;
	undefined field_0xc07;
	undefined field_0xc08;
	undefined field_0xc09;
	undefined field_0xc0a;
	undefined field_0xc0b;
	undefined field_0xc0c;
	undefined field_0xc0d;
	undefined field_0xc0e;
	undefined field_0xc0f;
	undefined field_0xc10;
	undefined field_0xc11;
	undefined field_0xc12;
	undefined field_0xc13;
	undefined field_0xc14;
	undefined field_0xc15;
	undefined field_0xc16;
	undefined field_0xc17;
	undefined field_0xc18;
	undefined field_0xc19;
	undefined field_0xc1a;
	undefined field_0xc1b;
	undefined field_0xc1c;
	undefined field_0xc1d;
	undefined field_0xc1e;
	undefined field_0xc1f;
	undefined field_0xc20;
	undefined field_0xc21;
	undefined field_0xc22;
	undefined field_0xc23;
	undefined field_0xc24;
	undefined field_0xc25;
	undefined field_0xc26;
	undefined field_0xc27;
	undefined field_0xc28;
	undefined field_0xc29;
	undefined field_0xc2a;
	undefined field_0xc2b;
	undefined field_0xc2c;
	undefined field_0xc2d;
	undefined field_0xc2e;
	undefined field_0xc2f;
	undefined field_0xc30;
	undefined field_0xc31;
	undefined field_0xc32;
	undefined field_0xc33;
	undefined field_0xc34;
	undefined field_0xc35;
	undefined field_0xc36;
	undefined field_0xc37;
	undefined field_0xc38;
	undefined field_0xc39;
	undefined field_0xc3a;
	undefined field_0xc3b;
	undefined field_0xc3c;
	undefined field_0xc3d;
	undefined field_0xc3e;
	undefined field_0xc3f;
	undefined field_0xc40;
	undefined field_0xc41;
	undefined field_0xc42;
	undefined field_0xc43;
	undefined field_0xc44;
	undefined field_0xc45;
	undefined field_0xc46;
	undefined field_0xc47;
	undefined field_0xc48;
	undefined field_0xc49;
	undefined field_0xc4a;
	undefined field_0xc4b;
	undefined field_0xc4c;
	undefined field_0xc4d;
	undefined field_0xc4e;
	undefined field_0xc4f;
	undefined field_0xc50;
	undefined field_0xc51;
	undefined field_0xc52;
	undefined field_0xc53;
	undefined field_0xc54;
	undefined field_0xc55;
	undefined field_0xc56;
	undefined field_0xc57;
	undefined field_0xc58;
	undefined field_0xc59;
	undefined field_0xc5a;
	undefined field_0xc5b;
	undefined field_0xc5c;
	undefined field_0xc5d;
	undefined field_0xc5e;
	undefined field_0xc5f;
	undefined field_0xc60;
	undefined field_0xc61;
	undefined field_0xc62;
	undefined field_0xc63;
	undefined field_0xc64;
	undefined field_0xc65;
	undefined field_0xc66;
	undefined field_0xc67;
	undefined field_0xc68;
	undefined field_0xc69;
	undefined field_0xc6a;
	undefined field_0xc6b;
	undefined field_0xc6c;
	undefined field_0xc6d;
	undefined field_0xc6e;
	undefined field_0xc6f;
	undefined field_0xc70;
	undefined field_0xc71;
	undefined field_0xc72;
	undefined field_0xc73;
	undefined field_0xc74;
	undefined field_0xc75;
	undefined field_0xc76;
	undefined field_0xc77;
	undefined field_0xc78;
	undefined field_0xc79;
	undefined field_0xc7a;
	undefined field_0xc7b;
	undefined field_0xc7c;
	undefined field_0xc7d;
	undefined field_0xc7e;
	undefined field_0xc7f;
	undefined field_0xc80;
	undefined field_0xc81;
	undefined field_0xc82;
	undefined field_0xc83;
	undefined field_0xc84;
	undefined field_0xc85;
	undefined field_0xc86;
	undefined field_0xc87;
	undefined field_0xc88;
	undefined field_0xc89;
	undefined field_0xc8a;
	undefined field_0xc8b;
	undefined field_0xc8c;
	undefined field_0xc8d;
	undefined field_0xc8e;
	undefined field_0xc8f;
	undefined field_0xc90;
	undefined field_0xc91;
	undefined field_0xc92;
	undefined field_0xc93;
	undefined field_0xc94;
	undefined field_0xc95;
	undefined field_0xc96;
	undefined field_0xc97;
	undefined field_0xc98;
	undefined field_0xc99;
	undefined field_0xc9a;
	undefined field_0xc9b;
	undefined field_0xc9c;
	undefined field_0xc9d;
	undefined field_0xc9e;
	undefined field_0xc9f;
	undefined field_0xca0;
	undefined field_0xca1;
	undefined field_0xca2;
	undefined field_0xca3;
	undefined field_0xca4;
	undefined field_0xca5;
	undefined field_0xca6;
	undefined field_0xca7;
	undefined field_0xca8;
	undefined field_0xca9;
	undefined field_0xcaa;
	undefined field_0xcab;
	undefined field_0xcac;
	undefined field_0xcad;
	undefined field_0xcae;
	undefined field_0xcaf;
	undefined field_0xcb0;
	undefined field_0xcb1;
	undefined field_0xcb2;
	undefined field_0xcb3;
	undefined field_0xcb4;
	undefined field_0xcb5;
	undefined field_0xcb6;
	undefined field_0xcb7;
	undefined field_0xcb8;
	undefined field_0xcb9;
	undefined field_0xcba;
	undefined field_0xcbb;
	undefined field_0xcbc;
	undefined field_0xcbd;
	undefined field_0xcbe;
	undefined field_0xcbf;
	undefined field_0xcc0;
	undefined field_0xcc1;
	undefined field_0xcc2;
	undefined field_0xcc3;
	undefined field_0xcc4;
	undefined field_0xcc5;
	undefined field_0xcc6;
	undefined field_0xcc7;
	undefined field_0xcc8;
	undefined field_0xcc9;
	undefined field_0xcca;
	undefined field_0xccb;
	undefined field_0xccc;
	undefined field_0xccd;
	undefined field_0xcce;
	undefined field_0xccf;
	undefined field_0xcd0;
	undefined field_0xcd1;
	undefined field_0xcd2;
	undefined field_0xcd3;
	undefined field_0xcd4;
	undefined field_0xcd5;
	undefined field_0xcd6;
	undefined field_0xcd7;
	undefined field_0xcd8;
	undefined field_0xcd9;
	undefined field_0xcda;
	undefined field_0xcdb;
	undefined field_0xcdc;
	undefined field_0xcdd;
	undefined field_0xcde;
	undefined field_0xcdf;
	undefined field_0xce0;
	undefined field_0xce1;
	undefined field_0xce2;
	undefined field_0xce3;
	undefined field_0xce4;
	undefined field_0xce5;
	undefined field_0xce6;
	undefined field_0xce7;
	undefined field_0xce8;
	undefined field_0xce9;
	undefined field_0xcea;
	undefined field_0xceb;
	undefined field_0xcec;
	undefined field_0xced;
	undefined field_0xcee;
	undefined field_0xcef;
	undefined field_0xcf0;
	undefined field_0xcf1;
	undefined field_0xcf2;
	undefined field_0xcf3;
	undefined field_0xcf4;
	undefined field_0xcf5;
	undefined field_0xcf6;
	undefined field_0xcf7;
	undefined field_0xcf8;
	undefined field_0xcf9;
	undefined field_0xcfa;
	undefined field_0xcfb;
	undefined field_0xcfc;
	undefined field_0xcfd;
	undefined field_0xcfe;
	undefined field_0xcff;
	undefined field_0xd00;
	undefined field_0xd01;
	undefined field_0xd02;
	undefined field_0xd03;
	undefined field_0xd04;
	undefined field_0xd05;
	undefined field_0xd06;
	undefined field_0xd07;
	undefined field_0xd08;
	undefined field_0xd09;
	undefined field_0xd0a;
	undefined field_0xd0b;
	undefined field_0xd0c;
	undefined field_0xd0d;
	undefined field_0xd0e;
	undefined field_0xd0f;
	undefined field_0xd10;
	undefined field_0xd11;
	undefined field_0xd12;
	undefined field_0xd13;
	undefined field_0xd14;
	undefined field_0xd15;
	undefined field_0xd16;
	undefined field_0xd17;
	undefined field_0xd18;
	undefined field_0xd19;
	undefined field_0xd1a;
	undefined field_0xd1b;
	undefined field_0xd1c;
	undefined field_0xd1d;
	undefined field_0xd1e;
	undefined field_0xd1f;
	undefined field_0xd20;
	undefined field_0xd21;
	undefined field_0xd22;
	undefined field_0xd23;
	undefined field_0xd24;
	undefined field_0xd25;
	undefined field_0xd26;
	undefined field_0xd27;
	undefined field_0xd28;
	undefined field_0xd29;
	undefined field_0xd2a;
	undefined field_0xd2b;
	undefined field_0xd2c;
	undefined field_0xd2d;
	undefined field_0xd2e;
	undefined field_0xd2f;
	undefined field_0xd30;
	undefined field_0xd31;
	undefined field_0xd32;
	undefined field_0xd33;
	undefined field_0xd34;
	undefined field_0xd35;
	undefined field_0xd36;
	undefined field_0xd37;
	undefined field_0xd38;
	undefined field_0xd39;
	undefined field_0xd3a;
	undefined field_0xd3b;
	undefined field_0xd3c;
	undefined field_0xd3d;
	undefined field_0xd3e;
	undefined field_0xd3f;
	undefined field_0xd40;
	undefined field_0xd41;
	undefined field_0xd42;
	undefined field_0xd43;
	undefined field_0xd44;
	undefined field_0xd45;
	undefined field_0xd46;
	undefined field_0xd47;
	undefined field_0xd48;
	undefined field_0xd49;
	undefined field_0xd4a;
	undefined field_0xd4b;
	undefined field_0xd4c;
	undefined field_0xd4d;
	undefined field_0xd4e;
	undefined field_0xd4f;
	undefined field_0xd50;
	undefined field_0xd51;
	undefined field_0xd52;
	undefined field_0xd53;
	undefined field_0xd54;
	undefined field_0xd55;
	undefined field_0xd56;
	undefined field_0xd57;
	undefined field_0xd58;
	undefined field_0xd59;
	undefined field_0xd5a;
	undefined field_0xd5b;
	undefined field_0xd5c;
	undefined field_0xd5d;
	undefined field_0xd5e;
	undefined field_0xd5f;
	undefined field_0xd60;
	undefined field_0xd61;
	undefined field_0xd62;
	undefined field_0xd63;
	undefined field_0xd64;
	undefined field_0xd65;
	undefined field_0xd66;
	undefined field_0xd67;
	undefined field_0xd68;
	undefined field_0xd69;
	undefined field_0xd6a;
	undefined field_0xd6b;
	undefined field_0xd6c;
	undefined field_0xd6d;
	undefined field_0xd6e;
	undefined field_0xd6f;
	undefined field_0xd70;
	undefined field_0xd71;
	undefined field_0xd72;
	undefined field_0xd73;
	undefined field_0xd74;
	undefined field_0xd75;
	undefined field_0xd76;
	undefined field_0xd77;
	undefined field_0xd78;
	undefined field_0xd79;
	undefined field_0xd7a;
	undefined field_0xd7b;
	undefined field_0xd7c;
	undefined field_0xd7d;
	undefined field_0xd7e;
	undefined field_0xd7f;
	undefined field_0xd80;
	undefined field_0xd81;
	undefined field_0xd82;
	undefined field_0xd83;
	undefined field_0xd84;
	undefined field_0xd85;
	undefined field_0xd86;
	undefined field_0xd87;
	undefined field_0xd88;
	undefined field_0xd89;
	undefined field_0xd8a;
	undefined field_0xd8b;
	undefined field_0xd8c;
	undefined field_0xd8d;
	undefined field_0xd8e;
	undefined field_0xd8f;
	undefined field_0xd90;
	undefined field_0xd91;
	undefined field_0xd92;
	undefined field_0xd93;
	undefined field_0xd94;
	undefined field_0xd95;
	undefined field_0xd96;
	undefined field_0xd97;
	undefined field_0xd98;
	undefined field_0xd99;
	undefined field_0xd9a;
	undefined field_0xd9b;
	undefined field_0xd9c;
	undefined field_0xd9d;
	undefined field_0xd9e;
	undefined field_0xd9f;
	undefined field_0xda0;
	undefined field_0xda1;
	undefined field_0xda2;
	undefined field_0xda3;
	undefined field_0xda4;
	undefined field_0xda5;
	undefined field_0xda6;
	undefined field_0xda7;
	undefined field_0xda8;
	undefined field_0xda9;
	undefined field_0xdaa;
	undefined field_0xdab;
	undefined field_0xdac;
	undefined field_0xdad;
	undefined field_0xdae;
	undefined field_0xdaf;
	undefined field_0xdb0;
	undefined field_0xdb1;
	undefined field_0xdb2;
	undefined field_0xdb3;
	undefined field_0xdb4;
	undefined field_0xdb5;
	undefined field_0xdb6;
	undefined field_0xdb7;
	undefined field_0xdb8;
	undefined field_0xdb9;
	undefined field_0xdba;
	undefined field_0xdbb;
	undefined field_0xdbc;
	undefined field_0xdbd;
	undefined field_0xdbe;
	undefined field_0xdbf;
	undefined field_0xdc0;
	undefined field_0xdc1;
	undefined field_0xdc2;
	undefined field_0xdc3;
	undefined field_0xdc4;
	undefined field_0xdc5;
	undefined field_0xdc6;
	undefined field_0xdc7;
	undefined field_0xdc8;
	undefined field_0xdc9;
	undefined field_0xdca;
	undefined field_0xdcb;
	undefined field_0xdcc;
	undefined field_0xdcd;
	undefined field_0xdce;
	undefined field_0xdcf;
	undefined field_0xdd0;
	undefined field_0xdd1;
	undefined field_0xdd2;
	undefined field_0xdd3;
	undefined field_0xdd4;
	undefined field_0xdd5;
	undefined field_0xdd6;
	undefined field_0xdd7;
	undefined field_0xdd8;
	undefined field_0xdd9;
	undefined field_0xdda;
	undefined field_0xddb;
	undefined field_0xddc;
	undefined field_0xddd;
	undefined field_0xdde;
	undefined field_0xddf;
	undefined field_0xde0;
	undefined field_0xde1;
	undefined field_0xde2;
	undefined field_0xde3;
	undefined field_0xde4;
	undefined field_0xde5;
	undefined field_0xde6;
	undefined field_0xde7;
	undefined field_0xde8;
	undefined field_0xde9;
	undefined field_0xdea;
	undefined field_0xdeb;
	undefined field_0xdec;
	undefined field_0xded;
	undefined field_0xdee;
	undefined field_0xdef;
	undefined field_0xdf0;
	undefined field_0xdf1;
	undefined field_0xdf2;
	undefined field_0xdf3;
	undefined field_0xdf4;
	undefined field_0xdf5;
	undefined field_0xdf6;
	undefined field_0xdf7;
	undefined field_0xdf8;
	undefined field_0xdf9;
	undefined field_0xdfa;
	undefined field_0xdfb;
	undefined field_0xdfc;
	undefined field_0xdfd;
	undefined field_0xdfe;
	undefined field_0xdff;
	undefined field_0xe00;
	undefined field_0xe01;
	undefined field_0xe02;
	undefined field_0xe03;
	undefined field_0xe04;
	undefined field_0xe05;
	undefined field_0xe06;
	undefined field_0xe07;
	undefined field_0xe08;
	undefined field_0xe09;
	undefined field_0xe0a;
	undefined field_0xe0b;
	undefined field_0xe0c;
	undefined field_0xe0d;
	undefined field_0xe0e;
	undefined field_0xe0f;
	undefined field_0xe10;
	undefined field_0xe11;
	undefined field_0xe12;
	undefined field_0xe13;
	undefined field_0xe14;
	undefined field_0xe15;
	undefined field_0xe16;
	undefined field_0xe17;
	undefined field_0xe18;
	undefined field_0xe19;
	undefined field_0xe1a;
	undefined field_0xe1b;
	undefined field_0xe1c;
	undefined field_0xe1d;
	undefined field_0xe1e;
	undefined field_0xe1f;
	undefined field_0xe20;
	undefined field_0xe21;
	undefined field_0xe22;
	undefined field_0xe23;
	undefined field_0xe24;
	undefined field_0xe25;
	undefined field_0xe26;
	undefined field_0xe27;
	undefined field_0xe28;
	undefined field_0xe29;
	undefined field_0xe2a;
	undefined field_0xe2b;
	undefined field_0xe2c;
	undefined field_0xe2d;
	undefined field_0xe2e;
	undefined field_0xe2f;
	undefined field_0xe30;
	undefined field_0xe31;
	undefined field_0xe32;
	undefined field_0xe33;
	undefined field_0xe34;
	undefined field_0xe35;
	undefined field_0xe36;
	undefined field_0xe37;
	undefined field_0xe38;
	undefined field_0xe39;
	undefined field_0xe3a;
	undefined field_0xe3b;
	undefined field_0xe3c;
	undefined field_0xe3d;
	undefined field_0xe3e;
	undefined field_0xe3f;
	undefined field_0xe40;
	undefined field_0xe41;
	undefined field_0xe42;
	undefined field_0xe43;
	undefined field_0xe44;
	undefined field_0xe45;
	undefined field_0xe46;
	undefined field_0xe47;
	undefined field_0xe48;
	undefined field_0xe49;
	undefined field_0xe4a;
	undefined field_0xe4b;
	undefined field_0xe4c;
	undefined field_0xe4d;
	undefined field_0xe4e;
	undefined field_0xe4f;
	undefined field_0xe50;
	undefined field_0xe51;
	undefined field_0xe52;
	undefined field_0xe53;
	undefined field_0xe54;
	undefined field_0xe55;
	undefined field_0xe56;
	undefined field_0xe57;
	undefined field_0xe58;
	undefined field_0xe59;
	undefined field_0xe5a;
	undefined field_0xe5b;
	undefined field_0xe5c;
	undefined field_0xe5d;
	undefined field_0xe5e;
	undefined field_0xe5f;
	undefined field_0xe60;
	undefined field_0xe61;
	undefined field_0xe62;
	undefined field_0xe63;
	undefined field_0xe64;
	undefined field_0xe65;
	undefined field_0xe66;
	undefined field_0xe67;
	undefined field_0xe68;
	undefined field_0xe69;
	undefined field_0xe6a;
	undefined field_0xe6b;
	undefined field_0xe6c;
	undefined field_0xe6d;
	undefined field_0xe6e;
	undefined field_0xe6f;
	undefined field_0xe70;
	undefined field_0xe71;
	undefined field_0xe72;
	undefined field_0xe73;
	undefined field_0xe74;
	undefined field_0xe75;
	undefined field_0xe76;
	undefined field_0xe77;
	undefined field_0xe78;
	undefined field_0xe79;
	undefined field_0xe7a;
	undefined field_0xe7b;
	undefined field_0xe7c;
	undefined field_0xe7d;
	undefined field_0xe7e;
	undefined field_0xe7f;
	undefined field_0xe80;
	undefined field_0xe81;
	undefined field_0xe82;
	undefined field_0xe83;
	undefined field_0xe84;
	undefined field_0xe85;
	undefined field_0xe86;
	undefined field_0xe87;
	undefined field_0xe88;
	undefined field_0xe89;
	undefined field_0xe8a;
	undefined field_0xe8b;
	undefined field_0xe8c;
	undefined field_0xe8d;
	undefined field_0xe8e;
	undefined field_0xe8f;
	undefined field_0xe90;
	undefined field_0xe91;
	undefined field_0xe92;
	undefined field_0xe93;
	undefined field_0xe94;
	undefined field_0xe95;
	undefined field_0xe96;
	undefined field_0xe97;
	undefined field_0xe98;
	undefined field_0xe99;
	undefined field_0xe9a;
	undefined field_0xe9b;
	undefined field_0xe9c;
	undefined field_0xe9d;
	undefined field_0xe9e;
	undefined field_0xe9f;
	undefined field_0xea0;
	undefined field_0xea1;
	undefined field_0xea2;
	undefined field_0xea3;
	undefined field_0xea4;
	undefined field_0xea5;
	undefined field_0xea6;
	undefined field_0xea7;
	undefined field_0xea8;
	undefined field_0xea9;
	undefined field_0xeaa;
	undefined field_0xeab;
	undefined field_0xeac;
	undefined field_0xead;
	undefined field_0xeae;
	undefined field_0xeaf;
	undefined field_0xeb0;
	undefined field_0xeb1;
	undefined field_0xeb2;
	undefined field_0xeb3;
	undefined field_0xeb4;
	undefined field_0xeb5;
	undefined field_0xeb6;
	undefined field_0xeb7;
	undefined field_0xeb8;
	undefined field_0xeb9;
	undefined field_0xeba;
	undefined field_0xebb;
	undefined field_0xebc;
	undefined field_0xebd;
	undefined field_0xebe;
	undefined field_0xebf;
	undefined field_0xec0;
	undefined field_0xec1;
	undefined field_0xec2;
	undefined field_0xec3;
	undefined field_0xec4;
	undefined field_0xec5;
	undefined field_0xec6;
	undefined field_0xec7;
	undefined field_0xec8;
	undefined field_0xec9;
	undefined field_0xeca;
	undefined field_0xecb;
	undefined field_0xecc;
	undefined field_0xecd;
	undefined field_0xece;
	undefined field_0xecf;
	undefined field_0xed0;
	undefined field_0xed1;
	undefined field_0xed2;
	undefined field_0xed3;
	undefined field_0xed4;
	undefined field_0xed5;
	undefined field_0xed6;
	undefined field_0xed7;
	undefined field_0xed8;
	undefined field_0xed9;
	undefined field_0xeda;
	undefined field_0xedb;
	undefined field_0xedc;
	undefined field_0xedd;
	undefined field_0xede;
	undefined field_0xedf;
	undefined field_0xee0;
	undefined field_0xee1;
	undefined field_0xee2;
	undefined field_0xee3;
	undefined field_0xee4;
	undefined field_0xee5;
	undefined field_0xee6;
	undefined field_0xee7;
	undefined field_0xee8;
	undefined field_0xee9;
	undefined field_0xeea;
	undefined field_0xeeb;
	undefined field_0xeec;
	undefined field_0xeed;
	undefined field_0xeee;
	undefined field_0xeef;
	undefined field_0xef0;
	undefined field_0xef1;
	undefined field_0xef2;
	undefined field_0xef3;
	undefined field_0xef4;
	undefined field_0xef5;
	undefined field_0xef6;
	undefined field_0xef7;
	undefined field_0xef8;
	undefined field_0xef9;
	undefined field_0xefa;
	undefined field_0xefb;
	undefined field_0xefc;
	undefined field_0xefd;
	undefined field_0xefe;
	undefined field_0xeff;
	undefined field_0xf00;
	undefined field_0xf01;
	undefined field_0xf02;
	undefined field_0xf03;
	undefined field_0xf04;
	undefined field_0xf05;
	undefined field_0xf06;
	undefined field_0xf07;
	undefined field_0xf08;
	undefined field_0xf09;
	undefined field_0xf0a;
	undefined field_0xf0b;
	undefined field_0xf0c;
	undefined field_0xf0d;
	undefined field_0xf0e;
	undefined field_0xf0f;
	undefined field_0xf10;
	undefined field_0xf11;
	undefined field_0xf12;
	undefined field_0xf13;
	undefined field_0xf14;
	undefined field_0xf15;
	undefined field_0xf16;
	undefined field_0xf17;
	undefined field_0xf18;
	undefined field_0xf19;
	undefined field_0xf1a;
	undefined field_0xf1b;
	undefined field_0xf1c;
	undefined field_0xf1d;
	undefined field_0xf1e;
	undefined field_0xf1f;
	undefined field_0xf20;
	undefined field_0xf21;
	undefined field_0xf22;
	undefined field_0xf23;
	undefined field_0xf24;
	undefined field_0xf25;
	undefined field_0xf26;
	undefined field_0xf27;
	undefined field_0xf28;
	undefined field_0xf29;
	undefined field_0xf2a;
	undefined field_0xf2b;
	undefined field_0xf2c;
	undefined field_0xf2d;
	undefined field_0xf2e;
	undefined field_0xf2f;
	undefined field_0xf30;
	undefined field_0xf31;
	undefined field_0xf32;
	undefined field_0xf33;
	undefined field_0xf34;
	undefined field_0xf35;
	undefined field_0xf36;
	undefined field_0xf37;
	undefined field_0xf38;
	undefined field_0xf39;
	undefined field_0xf3a;
	undefined field_0xf3b;
	undefined field_0xf3c;
	undefined field_0xf3d;
	undefined field_0xf3e;
	undefined field_0xf3f;
	undefined field_0xf40;
	undefined field_0xf41;
	undefined field_0xf42;
	undefined field_0xf43;
	undefined field_0xf44;
	undefined field_0xf45;
	undefined field_0xf46;
	undefined field_0xf47;
	undefined field_0xf48;
	undefined field_0xf49;
	undefined field_0xf4a;
	undefined field_0xf4b;
	undefined field_0xf4c;
	undefined field_0xf4d;
	undefined field_0xf4e;
	undefined field_0xf4f;
	undefined field_0xf50;
	undefined field_0xf51;
	undefined field_0xf52;
	undefined field_0xf53;
	undefined field_0xf54;
	undefined field_0xf55;
	undefined field_0xf56;
	undefined field_0xf57;
	undefined field_0xf58;
	undefined field_0xf59;
	undefined field_0xf5a;
	undefined field_0xf5b;
	undefined field_0xf5c;
	undefined field_0xf5d;
	undefined field_0xf5e;
	undefined field_0xf5f;
	undefined field_0xf60;
	undefined field_0xf61;
	undefined field_0xf62;
	undefined field_0xf63;
	undefined field_0xf64;
	undefined field_0xf65;
	undefined field_0xf66;
	undefined field_0xf67;
	undefined field_0xf68;
	undefined field_0xf69;
	undefined field_0xf6a;
	undefined field_0xf6b;
	undefined field_0xf6c;
	undefined field_0xf6d;
	undefined field_0xf6e;
	undefined field_0xf6f;
	undefined field_0xf70;
	undefined field_0xf71;
	undefined field_0xf72;
	undefined field_0xf73;
	undefined field_0xf74;
	undefined field_0xf75;
	undefined field_0xf76;
	undefined field_0xf77;
	undefined field_0xf78;
	undefined field_0xf79;
	undefined field_0xf7a;
	undefined field_0xf7b;
	undefined field_0xf7c;
	undefined field_0xf7d;
	undefined field_0xf7e;
	undefined field_0xf7f;
	undefined field_0xf80;
	undefined field_0xf81;
	undefined field_0xf82;
	undefined field_0xf83;
	undefined field_0xf84;
	undefined field_0xf85;
	undefined field_0xf86;
	undefined field_0xf87;
	undefined field_0xf88;
	undefined field_0xf89;
	undefined field_0xf8a;
	undefined field_0xf8b;
	undefined field_0xf8c;
	undefined field_0xf8d;
	undefined field_0xf8e;
	undefined field_0xf8f;
	undefined field_0xf90;
	undefined field_0xf91;
	undefined field_0xf92;
	undefined field_0xf93;
	undefined field_0xf94;
	undefined field_0xf95;
	undefined field_0xf96;
	undefined field_0xf97;
	undefined field_0xf98;
	undefined field_0xf99;
	undefined field_0xf9a;
	undefined field_0xf9b;
	undefined field_0xf9c;
	undefined field_0xf9d;
	undefined field_0xf9e;
	undefined field_0xf9f;
	undefined field_0xfa0;
	undefined field_0xfa1;
	undefined field_0xfa2;
	undefined field_0xfa3;
	undefined field_0xfa4;
	undefined field_0xfa5;
	undefined field_0xfa6;
	undefined field_0xfa7;
	undefined field_0xfa8;
	undefined field_0xfa9;
	undefined field_0xfaa;
	undefined field_0xfab;
	undefined field_0xfac;
	undefined field_0xfad;
	undefined field_0xfae;
	undefined field_0xfaf;
	undefined field_0xfb0;
	undefined field_0xfb1;
	undefined field_0xfb2;
	undefined field_0xfb3;
	undefined field_0xfb4;
	undefined field_0xfb5;
	undefined field_0xfb6;
	undefined field_0xfb7;
	undefined field_0xfb8;
	undefined field_0xfb9;
	undefined field_0xfba;
	undefined field_0xfbb;
	undefined field_0xfbc;
	undefined field_0xfbd;
	undefined field_0xfbe;
	undefined field_0xfbf;
	undefined field_0xfc0;
	undefined field_0xfc1;
	undefined field_0xfc2;
	undefined field_0xfc3;
	undefined field_0xfc4;
	undefined field_0xfc5;
	undefined field_0xfc6;
	undefined field_0xfc7;
	undefined field_0xfc8;
	undefined field_0xfc9;
	undefined field_0xfca;
	undefined field_0xfcb;
	undefined field_0xfcc;
	undefined field_0xfcd;
	undefined field_0xfce;
	undefined field_0xfcf;
	undefined field_0xfd0;
	undefined field_0xfd1;
	undefined field_0xfd2;
	undefined field_0xfd3;
	undefined field_0xfd4;
	undefined field_0xfd5;
	undefined field_0xfd6;
	undefined field_0xfd7;
	undefined field_0xfd8;
	undefined field_0xfd9;
	undefined field_0xfda;
	undefined field_0xfdb;
	undefined field_0xfdc;
	undefined field_0xfdd;
	undefined field_0xfde;
	undefined field_0xfdf;
	undefined field_0xfe0;
	undefined field_0xfe1;
	undefined field_0xfe2;
	undefined field_0xfe3;
	undefined field_0xfe4;
	undefined field_0xfe5;
	undefined field_0xfe6;
	undefined field_0xfe7;
	undefined field_0xfe8;
	undefined field_0xfe9;
	undefined field_0xfea;
	undefined field_0xfeb;
	undefined field_0xfec;
	undefined field_0xfed;
	undefined field_0xfee;
	undefined field_0xfef;
	undefined field_0xff0;
	undefined field_0xff1;
	undefined field_0xff2;
	undefined field_0xff3;
	undefined field_0xff4;
	undefined field_0xff5;
	undefined field_0xff6;
	undefined field_0xff7;
	undefined field_0xff8;
	undefined field_0xff9;
	undefined field_0xffa;
	undefined field_0xffb;
	undefined field_0xffc;
	undefined field_0xffd;
	undefined field_0xffe;
	undefined field_0xfff;
	undefined field_0x1000;
	undefined field_0x1001;
	undefined field_0x1002;
	undefined field_0x1003;
	undefined field_0x1004;
	undefined field_0x1005;
	undefined field_0x1006;
	undefined field_0x1007;
	undefined field_0x1008;
	undefined field_0x1009;
	undefined field_0x100a;
	undefined field_0x100b;
	undefined field_0x100c;
	undefined field_0x100d;
	undefined field_0x100e;
	undefined field_0x100f;
	undefined field_0x1010;
	undefined field_0x1011;
	undefined field_0x1012;
	undefined field_0x1013;
	undefined field_0x1014;
	undefined field_0x1015;
	undefined field_0x1016;
	undefined field_0x1017;
	undefined field_0x1018;
	undefined field_0x1019;
	undefined field_0x101a;
	undefined field_0x101b;
	undefined field_0x101c;
	undefined field_0x101d;
	undefined field_0x101e;
	undefined field_0x101f;
	undefined field_0x1020;
	undefined field_0x1021;
	undefined field_0x1022;
	undefined field_0x1023;
	undefined field_0x1024;
	undefined field_0x1025;
	undefined field_0x1026;
	undefined field_0x1027;
	undefined field_0x1028;
	undefined field_0x1029;
	undefined field_0x102a;
	undefined field_0x102b;
	undefined field_0x102c;
	undefined field_0x102d;
	undefined field_0x102e;
	undefined field_0x102f;
	undefined field_0x1030;
	undefined field_0x1031;
	undefined field_0x1032;
	undefined field_0x1033;
	undefined field_0x1034;
	undefined field_0x1035;
	undefined field_0x1036;
	undefined field_0x1037;
	undefined field_0x1038;
	undefined field_0x1039;
	undefined field_0x103a;
	undefined field_0x103b;
	undefined field_0x103c;
	undefined field_0x103d;
	undefined field_0x103e;
	undefined field_0x103f;
	undefined field_0x1040;
	undefined field_0x1041;
	undefined field_0x1042;
	undefined field_0x1043;
	undefined field_0x1044;
	undefined field_0x1045;
	undefined field_0x1046;
	undefined field_0x1047;
	undefined field_0x1048;
	undefined field_0x1049;
	undefined field_0x104a;
	undefined field_0x104b;
	undefined field_0x104c;
	undefined field_0x104d;
	undefined field_0x104e;
	undefined field_0x104f;
	undefined field_0x1050;
	undefined field_0x1051;
	undefined field_0x1052;
	undefined field_0x1053;
	undefined field_0x1054;
	undefined field_0x1055;
	undefined field_0x1056;
	undefined field_0x1057;
	undefined field_0x1058;
	undefined field_0x1059;
	undefined field_0x105a;
	undefined field_0x105b;
	undefined field_0x105c;
	undefined field_0x105d;
	undefined field_0x105e;
	undefined field_0x105f;
	undefined field_0x1060;
	undefined field_0x1061;
	undefined field_0x1062;
	undefined field_0x1063;
	undefined field_0x1064;
	undefined field_0x1065;
	undefined field_0x1066;
	undefined field_0x1067;
	undefined field_0x1068;
	undefined field_0x1069;
	undefined field_0x106a;
	undefined field_0x106b;
	undefined field_0x106c;
	undefined field_0x106d;
	undefined field_0x106e;
	undefined field_0x106f;
	undefined field_0x1070;
	undefined field_0x1071;
	undefined field_0x1072;
	undefined field_0x1073;
	undefined field_0x1074;
	undefined field_0x1075;
	undefined field_0x1076;
	undefined field_0x1077;
	undefined field_0x1078;
	undefined field_0x1079;
	undefined field_0x107a;
	undefined field_0x107b;
	undefined field_0x107c;
	undefined field_0x107d;
	undefined field_0x107e;
	undefined field_0x107f;
	undefined field_0x1080;
	undefined field_0x1081;
	undefined field_0x1082;
	undefined field_0x1083;
	undefined field_0x1084;
	undefined field_0x1085;
	undefined field_0x1086;
	undefined field_0x1087;
	undefined field_0x1088;
	undefined field_0x1089;
	undefined field_0x108a;
	undefined field_0x108b;
	undefined field_0x108c;
	undefined field_0x108d;
	undefined field_0x108e;
	undefined field_0x108f;
	undefined field_0x1090;
	undefined field_0x1091;
	undefined field_0x1092;
	undefined field_0x1093;
	undefined field_0x1094;
	undefined field_0x1095;
	undefined field_0x1096;
	undefined field_0x1097;
	undefined field_0x1098;
	undefined field_0x1099;
	undefined field_0x109a;
	undefined field_0x109b;
	undefined field_0x109c;
	undefined field_0x109d;
	undefined field_0x109e;
	undefined field_0x109f;
	undefined field_0x10a0;
	undefined field_0x10a1;
	undefined field_0x10a2;
	undefined field_0x10a3;
	undefined field_0x10a4;
	undefined field_0x10a5;
	undefined field_0x10a6;
	undefined field_0x10a7;
	undefined field_0x10a8;
	undefined field_0x10a9;
	undefined field_0x10aa;
	undefined field_0x10ab;
	undefined field_0x10ac;
	undefined field_0x10ad;
	undefined field_0x10ae;
	undefined field_0x10af;
	undefined field_0x10b0;
	undefined field_0x10b1;
	undefined field_0x10b2;
	undefined field_0x10b3;
	undefined field_0x10b4;
	undefined field_0x10b5;
	undefined field_0x10b6;
	undefined field_0x10b7;
	undefined field_0x10b8;
	undefined field_0x10b9;
	undefined field_0x10ba;
	undefined field_0x10bb;
	undefined field_0x10bc;
	undefined field_0x10bd;
	undefined field_0x10be;
	undefined field_0x10bf;
	undefined field_0x10c0;
	undefined field_0x10c1;
	undefined field_0x10c2;
	undefined field_0x10c3;
	undefined field_0x10c4;
	undefined field_0x10c5;
	undefined field_0x10c6;
	undefined field_0x10c7;
	undefined field_0x10c8;
	undefined field_0x10c9;
	undefined field_0x10ca;
	undefined field_0x10cb;
	undefined field_0x10cc;
	undefined field_0x10cd;
	undefined field_0x10ce;
	undefined field_0x10cf;
	undefined field_0x10d0;
	undefined field_0x10d1;
	undefined field_0x10d2;
	undefined field_0x10d3;
	undefined field_0x10d4;
	undefined field_0x10d5;
	undefined field_0x10d6;
	undefined field_0x10d7;
	undefined field_0x10d8;
	undefined field_0x10d9;
	undefined field_0x10da;
	undefined field_0x10db;
	undefined field_0x10dc;
	undefined field_0x10dd;
	undefined field_0x10de;
	undefined field_0x10df;
	undefined field_0x10e0;
	undefined field_0x10e1;
	undefined field_0x10e2;
	undefined field_0x10e3;
	undefined field_0x10e4;
	undefined field_0x10e5;
	undefined field_0x10e6;
	undefined field_0x10e7;
	undefined field_0x10e8;
	undefined field_0x10e9;
	undefined field_0x10ea;
	undefined field_0x10eb;
	undefined field_0x10ec;
	undefined field_0x10ed;
	undefined field_0x10ee;
	undefined field_0x10ef;
	undefined field_0x10f0;
	undefined field_0x10f1;
	undefined field_0x10f2;
	undefined field_0x10f3;
	undefined field_0x10f4;
	undefined field_0x10f5;
	undefined field_0x10f6;
	undefined field_0x10f7;
	undefined field_0x10f8;
	undefined field_0x10f9;
	undefined field_0x10fa;
	undefined field_0x10fb;
	undefined field_0x10fc;
	undefined field_0x10fd;
	undefined field_0x10fe;
	undefined field_0x10ff;
	undefined field_0x1100;
	undefined field_0x1101;
	undefined field_0x1102;
	undefined field_0x1103;
	undefined field_0x1104;
	undefined field_0x1105;
	undefined field_0x1106;
	undefined field_0x1107;
	undefined field_0x1108;
	undefined field_0x1109;
	undefined field_0x110a;
	undefined field_0x110b;
	undefined field_0x110c;
	undefined field_0x110d;
	undefined field_0x110e;
	undefined field_0x110f;
	undefined field_0x1110;
	undefined field_0x1111;
	undefined field_0x1112;
	undefined field_0x1113;
	undefined field_0x1114;
	undefined field_0x1115;
	undefined field_0x1116;
	undefined field_0x1117;
	undefined field_0x1118;
	undefined field_0x1119;
	undefined field_0x111a;
	undefined field_0x111b;
	undefined field_0x111c;
	undefined field_0x111d;
	undefined field_0x111e;
	undefined field_0x111f;
	undefined field_0x1120;
	undefined field_0x1121;
	undefined field_0x1122;
	undefined field_0x1123;
	undefined field_0x1124;
	undefined field_0x1125;
	undefined field_0x1126;
	undefined field_0x1127;
	undefined field_0x1128;
	undefined field_0x1129;
	undefined field_0x112a;
	undefined field_0x112b;
	undefined field_0x112c;
	undefined field_0x112d;
	undefined field_0x112e;
	undefined field_0x112f;
	undefined field_0x1130;
	undefined field_0x1131;
	undefined field_0x1132;
	undefined field_0x1133;
	undefined field_0x1134;
	undefined field_0x1135;
	undefined field_0x1136;
	undefined field_0x1137;
	undefined field_0x1138;
	undefined field_0x1139;
	undefined field_0x113a;
	undefined field_0x113b;
	undefined field_0x113c;
	undefined field_0x113d;
	undefined field_0x113e;
	undefined field_0x113f;
	undefined field_0x1140;
	undefined field_0x1141;
	undefined field_0x1142;
	undefined field_0x1143;
	undefined field_0x1144;
	undefined field_0x1145;
	undefined field_0x1146;
	undefined field_0x1147;
	undefined field_0x1148;
	undefined field_0x1149;
	undefined field_0x114a;
	undefined field_0x114b;
	undefined field_0x114c;
	undefined field_0x114d;
	undefined field_0x114e;
	undefined field_0x114f;
	undefined field_0x1150;
	undefined field_0x1151;
	undefined field_0x1152;
	undefined field_0x1153;
	undefined field_0x1154;
	undefined field_0x1155;
	undefined field_0x1156;
	undefined field_0x1157;
	undefined field_0x1158;
	undefined field_0x1159;
	undefined field_0x115a;
	undefined field_0x115b;
	undefined field_0x115c;
	undefined field_0x115d;
	undefined field_0x115e;
	undefined field_0x115f;
	undefined field_0x1160;
	undefined field_0x1161;
	undefined field_0x1162;
	undefined field_0x1163;
	undefined field_0x1164;
	undefined field_0x1165;
	undefined field_0x1166;
	undefined field_0x1167;
	undefined field_0x1168;
	undefined field_0x1169;
	undefined field_0x116a;
	undefined field_0x116b;
	undefined field_0x116c;
	undefined field_0x116d;
	undefined field_0x116e;
	undefined field_0x116f;
	undefined field_0x1170;
	undefined field_0x1171;
	undefined field_0x1172;
	undefined field_0x1173;
	undefined field_0x1174;
	undefined field_0x1175;
	undefined field_0x1176;
	undefined field_0x1177;
	undefined field_0x1178;
	undefined field_0x1179;
	undefined field_0x117a;
	undefined field_0x117b;
	undefined field_0x117c;
	undefined field_0x117d;
	undefined field_0x117e;
	undefined field_0x117f;
	undefined field_0x1180;
	undefined field_0x1181;
	undefined field_0x1182;
	undefined field_0x1183;
	undefined field_0x1184;
	undefined field_0x1185;
	undefined field_0x1186;
	undefined field_0x1187;
	undefined field_0x1188;
	undefined field_0x1189;
	undefined field_0x118a;
	undefined field_0x118b;
	undefined field_0x118c;
	undefined field_0x118d;
	undefined field_0x118e;
	undefined field_0x118f;
	undefined field_0x1190;
	undefined field_0x1191;
	undefined field_0x1192;
	undefined field_0x1193;
	undefined field_0x1194;
	undefined field_0x1195;
	undefined field_0x1196;
	undefined field_0x1197;
	undefined field_0x1198;
	undefined field_0x1199;
	undefined field_0x119a;
	undefined field_0x119b;
	undefined field_0x119c;
	undefined field_0x119d;
	undefined field_0x119e;
	undefined field_0x119f;
	undefined field_0x11a0;
	undefined field_0x11a1;
	undefined field_0x11a2;
	undefined field_0x11a3;
	undefined field_0x11a4;
	undefined field_0x11a5;
	undefined field_0x11a6;
	undefined field_0x11a7;
	undefined field_0x11a8;
	undefined field_0x11a9;
	undefined field_0x11aa;
	undefined field_0x11ab;
	undefined field_0x11ac;
	undefined field_0x11ad;
	undefined field_0x11ae;
	undefined field_0x11af;
	undefined field_0x11b0;
	undefined field_0x11b1;
	undefined field_0x11b2;
	undefined field_0x11b3;
	undefined field_0x11b4;
	undefined field_0x11b5;
	undefined field_0x11b6;
	undefined field_0x11b7;
	undefined field_0x11b8;
	undefined field_0x11b9;
	undefined field_0x11ba;
	undefined field_0x11bb;
	undefined field_0x11bc;
	undefined field_0x11bd;
	undefined field_0x11be;
	undefined field_0x11bf;
	undefined field_0x11c0;
	undefined field_0x11c1;
	undefined field_0x11c2;
	undefined field_0x11c3;
	undefined field_0x11c4;
	undefined field_0x11c5;
	undefined field_0x11c6;
	undefined field_0x11c7;
	undefined field_0x11c8;
	undefined field_0x11c9;
	undefined field_0x11ca;
	undefined field_0x11cb;
	undefined field_0x11cc;
	undefined field_0x11cd;
	undefined field_0x11ce;
	undefined field_0x11cf;
	undefined field_0x11d0;
	undefined field_0x11d1;
	undefined field_0x11d2;
	undefined field_0x11d3;
	undefined field_0x11d4;
	undefined field_0x11d5;
	undefined field_0x11d6;
	undefined field_0x11d7;
	undefined field_0x11d8;
	undefined field_0x11d9;
	undefined field_0x11da;
	undefined field_0x11db;
	undefined field_0x11dc;
	undefined field_0x11dd;
	undefined field_0x11de;
	undefined field_0x11df;
	undefined field_0x11e0;
	undefined field_0x11e1;
	undefined field_0x11e2;
	undefined field_0x11e3;
	undefined field_0x11e4;
	undefined field_0x11e5;
	undefined field_0x11e6;
	undefined field_0x11e7;
	undefined field_0x11e8;
	undefined field_0x11e9;
	undefined field_0x11ea;
	undefined field_0x11eb;
	undefined field_0x11ec;
	undefined field_0x11ed;
	undefined field_0x11ee;
	undefined field_0x11ef;
	undefined field_0x11f0;
	undefined field_0x11f1;
	undefined field_0x11f2;
	undefined field_0x11f3;
	undefined field_0x11f4;
	undefined field_0x11f5;
	undefined field_0x11f6;
	undefined field_0x11f7;
	undefined field_0x11f8;
	undefined field_0x11f9;
	undefined field_0x11fa;
	undefined field_0x11fb;
	undefined field_0x11fc;
	undefined field_0x11fd;
	undefined field_0x11fe;
	undefined field_0x11ff;
	undefined field_0x1200;
	undefined field_0x1201;
	undefined field_0x1202;
	undefined field_0x1203;
	undefined field_0x1204;
	undefined field_0x1205;
	undefined field_0x1206;
	undefined field_0x1207;
	undefined field_0x1208;
	undefined field_0x1209;
	undefined field_0x120a;
	undefined field_0x120b;
	undefined field_0x120c;
	undefined field_0x120d;
	undefined field_0x120e;
	undefined field_0x120f;
	undefined field_0x1210;
	undefined field_0x1211;
	undefined field_0x1212;
	undefined field_0x1213;
	undefined field_0x1214;
	undefined field_0x1215;
	undefined field_0x1216;
	undefined field_0x1217;
	undefined field_0x1218;
	undefined field_0x1219;
	undefined field_0x121a;
	undefined field_0x121b;
	undefined field_0x121c;
	undefined field_0x121d;
	undefined field_0x121e;
	undefined field_0x121f;
	undefined field_0x1220;
	undefined field_0x1221;
	undefined field_0x1222;
	undefined field_0x1223;
	undefined field_0x1224;
	undefined field_0x1225;
	undefined field_0x1226;
	undefined field_0x1227;
	undefined field_0x1228;
	undefined field_0x1229;
	undefined field_0x122a;
	undefined field_0x122b;
	undefined field_0x122c;
	undefined field_0x122d;
	undefined field_0x122e;
	undefined field_0x122f;
	undefined field_0x1230;
	undefined field_0x1231;
	undefined field_0x1232;
	undefined field_0x1233;
	undefined field_0x1234;
	undefined field_0x1235;
	undefined field_0x1236;
	undefined field_0x1237;
	undefined field_0x1238;
	undefined field_0x1239;
	undefined field_0x123a;
	undefined field_0x123b;
	undefined field_0x123c;
	undefined field_0x123d;
	undefined field_0x123e;
	undefined field_0x123f;
	undefined field_0x1240;
	undefined field_0x1241;
	undefined field_0x1242;
	undefined field_0x1243;
	undefined field_0x1244;
	undefined field_0x1245;
	undefined field_0x1246;
	undefined field_0x1247;
	undefined field_0x1248;
	undefined field_0x1249;
	undefined field_0x124a;
	undefined field_0x124b;
	undefined field_0x124c;
	undefined field_0x124d;
	undefined field_0x124e;
	undefined field_0x124f;
	undefined field_0x1250;
	undefined field_0x1251;
	undefined field_0x1252;
	undefined field_0x1253;
	undefined field_0x1254;
	undefined field_0x1255;
	undefined field_0x1256;
	undefined field_0x1257;
	undefined field_0x1258;
	undefined field_0x1259;
	undefined field_0x125a;
	undefined field_0x125b;
	undefined field_0x125c;
	undefined field_0x125d;
	undefined field_0x125e;
	undefined field_0x125f;
	undefined field_0x1260;
	undefined field_0x1261;
	undefined field_0x1262;
	undefined field_0x1263;
	undefined field_0x1264;
	undefined field_0x1265;
	undefined field_0x1266;
	undefined field_0x1267;
	undefined field_0x1268;
	undefined field_0x1269;
	undefined field_0x126a;
	undefined field_0x126b;
	undefined field_0x126c;
	undefined field_0x126d;
	undefined field_0x126e;
	undefined field_0x126f;
	undefined field_0x1270;
	undefined field_0x1271;
	undefined field_0x1272;
	undefined field_0x1273;
	undefined field_0x1274;
	undefined field_0x1275;
	undefined field_0x1276;
	undefined field_0x1277;
	undefined field_0x1278;
	undefined field_0x1279;
	undefined field_0x127a;
	undefined field_0x127b;
	undefined field_0x127c;
	undefined field_0x127d;
	undefined field_0x127e;
	undefined field_0x127f;
	undefined field_0x1280;
	undefined field_0x1281;
	undefined field_0x1282;
	undefined field_0x1283;
	undefined field_0x1284;
	undefined field_0x1285;
	undefined field_0x1286;
	undefined field_0x1287;
	undefined field_0x1288;
	undefined field_0x1289;
	undefined field_0x128a;
	undefined field_0x128b;
	undefined field_0x128c;
	undefined field_0x128d;
	undefined field_0x128e;
	undefined field_0x128f;
	undefined field_0x1290;
	undefined field_0x1291;
	undefined field_0x1292;
	undefined field_0x1293;
	undefined field_0x1294;
	undefined field_0x1295;
	undefined field_0x1296;
	undefined field_0x1297;
	undefined field_0x1298;
	undefined field_0x1299;
	undefined field_0x129a;
	undefined field_0x129b;
	undefined field_0x129c;
	undefined field_0x129d;
	undefined field_0x129e;
	undefined field_0x129f;
	undefined field_0x12a0;
	undefined field_0x12a1;
	undefined field_0x12a2;
	undefined field_0x12a3;
	undefined field_0x12a4;
	undefined field_0x12a5;
	undefined field_0x12a6;
	undefined field_0x12a7;
	undefined field_0x12a8;
	undefined field_0x12a9;
	undefined field_0x12aa;
	undefined field_0x12ab;
	undefined field_0x12ac;
	undefined field_0x12ad;
	undefined field_0x12ae;
	undefined field_0x12af;
	undefined field_0x12b0;
	undefined field_0x12b1;
	undefined field_0x12b2;
	undefined field_0x12b3;
	undefined field_0x12b4;
	undefined field_0x12b5;
	undefined field_0x12b6;
	undefined field_0x12b7;
	undefined field_0x12b8;
	undefined field_0x12b9;
	undefined field_0x12ba;
	undefined field_0x12bb;
	undefined field_0x12bc;
	undefined field_0x12bd;
	undefined field_0x12be;
	undefined field_0x12bf;
	undefined field_0x12c0;
	undefined field_0x12c1;
	undefined field_0x12c2;
	undefined field_0x12c3;
	undefined field_0x12c4;
	undefined field_0x12c5;
	undefined field_0x12c6;
	undefined field_0x12c7;
	undefined field_0x12c8;
	undefined field_0x12c9;
	undefined field_0x12ca;
	undefined field_0x12cb;
	undefined field_0x12cc;
	undefined field_0x12cd;
	undefined field_0x12ce;
	undefined field_0x12cf;
	undefined field_0x12d0;
	undefined field_0x12d1;
	undefined field_0x12d2;
	undefined field_0x12d3;
	undefined field_0x12d4;
	undefined field_0x12d5;
	undefined field_0x12d6;
	undefined field_0x12d7;
	undefined field_0x12d8;
	undefined field_0x12d9;
	undefined field_0x12da;
	undefined field_0x12db;
	undefined field_0x12dc;
	undefined field_0x12dd;
	undefined field_0x12de;
	undefined field_0x12df;
	undefined field_0x12e0;
	undefined field_0x12e1;
	undefined field_0x12e2;
	undefined field_0x12e3;
	undefined field_0x12e4;
	undefined field_0x12e5;
	undefined field_0x12e6;
	undefined field_0x12e7;
	undefined field_0x12e8;
	undefined field_0x12e9;
	undefined field_0x12ea;
	undefined field_0x12eb;
	undefined field_0x12ec;
	undefined field_0x12ed;
	undefined field_0x12ee;
	undefined field_0x12ef;
	undefined field_0x12f0;
	undefined field_0x12f1;
	undefined field_0x12f2;
	undefined field_0x12f3;
	undefined field_0x12f4;
	undefined field_0x12f5;
	undefined field_0x12f6;
	undefined field_0x12f7;
	undefined field_0x12f8;
	undefined field_0x12f9;
	undefined field_0x12fa;
	undefined field_0x12fb;
	undefined field_0x12fc;
	undefined field_0x12fd;
	undefined field_0x12fe;
	undefined field_0x12ff;
	undefined field_0x1300;
	undefined field_0x1301;
	undefined field_0x1302;
	undefined field_0x1303;
	undefined field_0x1304;
	undefined field_0x1305;
	undefined field_0x1306;
	undefined field_0x1307;
	undefined field_0x1308;
	undefined field_0x1309;
	undefined field_0x130a;
	undefined field_0x130b;
	undefined field_0x130c;
	undefined field_0x130d;
	undefined field_0x130e;
	undefined field_0x130f;
	undefined field_0x1310;
	undefined field_0x1311;
	undefined field_0x1312;
	undefined field_0x1313;
	undefined field_0x1314;
	undefined field_0x1315;
	undefined field_0x1316;
	undefined field_0x1317;
	undefined field_0x1318;
	undefined field_0x1319;
	undefined field_0x131a;
	undefined field_0x131b;
	undefined field_0x131c;
	undefined field_0x131d;
	undefined field_0x131e;
	undefined field_0x131f;
	undefined field_0x1320;
	undefined field_0x1321;
	undefined field_0x1322;
	undefined field_0x1323;
	undefined field_0x1324;
	undefined field_0x1325;
	undefined field_0x1326;
	undefined field_0x1327;
	undefined field_0x1328;
	undefined field_0x1329;
	undefined field_0x132a;
	undefined field_0x132b;
	undefined field_0x132c;
	undefined field_0x132d;
	undefined field_0x132e;
	undefined field_0x132f;
	undefined field_0x1330;
	undefined field_0x1331;
	undefined field_0x1332;
	undefined field_0x1333;
	undefined field_0x1334;
	undefined field_0x1335;
	undefined field_0x1336;
	undefined field_0x1337;
	undefined field_0x1338;
	undefined field_0x1339;
	undefined field_0x133a;
	undefined field_0x133b;
	undefined field_0x133c;
	undefined field_0x133d;
	undefined field_0x133e;
	undefined field_0x133f;
	undefined field_0x1340;
	undefined field_0x1341;
	undefined field_0x1342;
	undefined field_0x1343;
	undefined field_0x1344;
	undefined field_0x1345;
	undefined field_0x1346;
	undefined field_0x1347;
	undefined field_0x1348;
	undefined field_0x1349;
	undefined field_0x134a;
	undefined field_0x134b;
	undefined field_0x134c;
	undefined field_0x134d;
	undefined field_0x134e;
	undefined field_0x134f;
	undefined field_0x1350;
	undefined field_0x1351;
	undefined field_0x1352;
	undefined field_0x1353;
	undefined field_0x1354;
	undefined field_0x1355;
	undefined field_0x1356;
	undefined field_0x1357;
	undefined field_0x1358;
	undefined field_0x1359;
	undefined field_0x135a;
	undefined field_0x135b;
	undefined field_0x135c;
	undefined field_0x135d;
	undefined field_0x135e;
	undefined field_0x135f;
	undefined field_0x1360;
	undefined field_0x1361;
	undefined field_0x1362;
	undefined field_0x1363;
	undefined field_0x1364;
	undefined field_0x1365;
	undefined field_0x1366;
	undefined field_0x1367;
	undefined field_0x1368;
	undefined field_0x1369;
	undefined field_0x136a;
	undefined field_0x136b;
	undefined field_0x136c;
	undefined field_0x136d;
	undefined field_0x136e;
	undefined field_0x136f;
	undefined field_0x1370;
	undefined field_0x1371;
	undefined field_0x1372;
	undefined field_0x1373;
	undefined field_0x1374;
	undefined field_0x1375;
	undefined field_0x1376;
	undefined field_0x1377;
	undefined field_0x1378;
	undefined field_0x1379;
	undefined field_0x137a;
	undefined field_0x137b;
	undefined field_0x137c;
	undefined field_0x137d;
	undefined field_0x137e;
	undefined field_0x137f;
	undefined field_0x1380;
	undefined field_0x1381;
	undefined field_0x1382;
	undefined field_0x1383;
	undefined field_0x1384;
	undefined field_0x1385;
	undefined field_0x1386;
	undefined field_0x1387;
	undefined field_0x1388;
	undefined field_0x1389;
	undefined field_0x138a;
	undefined field_0x138b;
	undefined field_0x138c;
	undefined field_0x138d;
	undefined field_0x138e;
	undefined field_0x138f;
	undefined field_0x1390;
	undefined field_0x1391;
	undefined field_0x1392;
	undefined field_0x1393;
	undefined field_0x1394;
	undefined field_0x1395;
	undefined field_0x1396;
	undefined field_0x1397;
	undefined field_0x1398;
	undefined field_0x1399;
	undefined field_0x139a;
	undefined field_0x139b;
	undefined field_0x139c;
	undefined field_0x139d;
	undefined field_0x139e;
	undefined field_0x139f;
	undefined field_0x13a0;
	undefined field_0x13a1;
	undefined field_0x13a2;
	undefined field_0x13a3;
	undefined field_0x13a4;
	undefined field_0x13a5;
	undefined field_0x13a6;
	undefined field_0x13a7;
	undefined field_0x13a8;
	undefined field_0x13a9;
	undefined field_0x13aa;
	undefined field_0x13ab;
	undefined field_0x13ac;
	undefined field_0x13ad;
	undefined field_0x13ae;
	undefined field_0x13af;
	undefined field_0x13b0;
	undefined field_0x13b1;
	undefined field_0x13b2;
	undefined field_0x13b3;
	undefined field_0x13b4;
	undefined field_0x13b5;
	undefined field_0x13b6;
	undefined field_0x13b7;
	undefined field_0x13b8;
	undefined field_0x13b9;
	undefined field_0x13ba;
	undefined field_0x13bb;
	undefined field_0x13bc;
	undefined field_0x13bd;
	undefined field_0x13be;
	undefined field_0x13bf;
	undefined field_0x13c0;
	undefined field_0x13c1;
	undefined field_0x13c2;
	undefined field_0x13c3;
	undefined field_0x13c4;
	undefined field_0x13c5;
	undefined field_0x13c6;
	undefined field_0x13c7;
	undefined field_0x13c8;
	undefined field_0x13c9;
	undefined field_0x13ca;
	undefined field_0x13cb;
	undefined field_0x13cc;
	undefined field_0x13cd;
	undefined field_0x13ce;
	undefined field_0x13cf;
	undefined field_0x13d0;
	undefined field_0x13d1;
	undefined field_0x13d2;
	undefined field_0x13d3;
	undefined field_0x13d4;
	undefined field_0x13d5;
	undefined field_0x13d6;
	undefined field_0x13d7;
	undefined field_0x13d8;
	undefined field_0x13d9;
	undefined field_0x13da;
	undefined field_0x13db;
	undefined field_0x13dc;
	undefined field_0x13dd;
	undefined field_0x13de;
	undefined field_0x13df;
	undefined field_0x13e0;
	undefined field_0x13e1;
	undefined field_0x13e2;
	undefined field_0x13e3;
	undefined field_0x13e4;
	undefined field_0x13e5;
	undefined field_0x13e6;
	undefined field_0x13e7;
	undefined field_0x13e8;
	undefined field_0x13e9;
	undefined field_0x13ea;
	undefined field_0x13eb;
	undefined field_0x13ec;
	undefined field_0x13ed;
	undefined field_0x13ee;
	undefined field_0x13ef;
	undefined field_0x13f0;
	undefined field_0x13f1;
	undefined field_0x13f2;
	undefined field_0x13f3;
	undefined field_0x13f4;
	undefined field_0x13f5;
	undefined field_0x13f6;
	undefined field_0x13f7;
	undefined field_0x13f8;
	undefined field_0x13f9;
	undefined field_0x13fa;
	undefined field_0x13fb;
	undefined field_0x13fc;
	undefined field_0x13fd;
	undefined field_0x13fe;
	undefined field_0x13ff;
	undefined field_0x1400;
	undefined field_0x1401;
	undefined field_0x1402;
	undefined field_0x1403;
	undefined field_0x1404;
	undefined field_0x1405;
	undefined field_0x1406;
	undefined field_0x1407;
	undefined field_0x1408;
	undefined field_0x1409;
	undefined field_0x140a;
	undefined field_0x140b;
	undefined field_0x140c;
	undefined field_0x140d;
	undefined field_0x140e;
	undefined field_0x140f;
	undefined field_0x1410;
	undefined field_0x1411;
	undefined field_0x1412;
	undefined field_0x1413;
	undefined field_0x1414;
	undefined field_0x1415;
	undefined field_0x1416;
	undefined field_0x1417;
	undefined field_0x1418;
	undefined field_0x1419;
	undefined field_0x141a;
	undefined field_0x141b;
	undefined field_0x141c;
	undefined field_0x141d;
	undefined field_0x141e;
	undefined field_0x141f;
	undefined field_0x1420;
	undefined field_0x1421;
	undefined field_0x1422;
	undefined field_0x1423;
	undefined field_0x1424;
	undefined field_0x1425;
	undefined field_0x1426;
	undefined field_0x1427;
	undefined field_0x1428;
	undefined field_0x1429;
	undefined field_0x142a;
	undefined field_0x142b;
	undefined field_0x142c;
	undefined field_0x142d;
	undefined field_0x142e;
	undefined field_0x142f;
	undefined field_0x1430;
	undefined field_0x1431;
	undefined field_0x1432;
	undefined field_0x1433;
	undefined field_0x1434;
	undefined field_0x1435;
	undefined field_0x1436;
	undefined field_0x1437;
	undefined field_0x1438;
	undefined field_0x1439;
	undefined field_0x143a;
	undefined field_0x143b;
	undefined field_0x143c;
	undefined field_0x143d;
	undefined field_0x143e;
	undefined field_0x143f;
	undefined field_0x1440;
	undefined field_0x1441;
	undefined field_0x1442;
	undefined field_0x1443;
	undefined field_0x1444;
	undefined field_0x1445;
	undefined field_0x1446;
	undefined field_0x1447;
	undefined field_0x1448;
	undefined field_0x1449;
	undefined field_0x144a;
	undefined field_0x144b;
	undefined field_0x144c;
	undefined field_0x144d;
	undefined field_0x144e;
	undefined field_0x144f;
	undefined field_0x1450;
	undefined field_0x1451;
	undefined field_0x1452;
	undefined field_0x1453;
	undefined field_0x1454;
	undefined field_0x1455;
	undefined field_0x1456;
	undefined field_0x1457;
	undefined field_0x1458;
	undefined field_0x1459;
	undefined field_0x145a;
	undefined field_0x145b;
	undefined field_0x145c;
	undefined field_0x145d;
	undefined field_0x145e;
	undefined field_0x145f;
	undefined field_0x1460;
	undefined field_0x1461;
	undefined field_0x1462;
	undefined field_0x1463;
	undefined field_0x1464;
	undefined field_0x1465;
	undefined field_0x1466;
	undefined field_0x1467;
	undefined field_0x1468;
	undefined field_0x1469;
	undefined field_0x146a;
	undefined field_0x146b;
	undefined field_0x146c;
	undefined field_0x146d;
	undefined field_0x146e;
	undefined field_0x146f;
	undefined field_0x1470;
	undefined field_0x1471;
	undefined field_0x1472;
	undefined field_0x1473;
	undefined field_0x1474;
	undefined field_0x1475;
	undefined field_0x1476;
	undefined field_0x1477;
	undefined field_0x1478;
	undefined field_0x1479;
	undefined field_0x147a;
	undefined field_0x147b;
	undefined field_0x147c;
	undefined field_0x147d;
	undefined field_0x147e;
	undefined field_0x147f;
	undefined field_0x1480;
	undefined field_0x1481;
	undefined field_0x1482;
	undefined field_0x1483;
	undefined field_0x1484;
	undefined field_0x1485;
	undefined field_0x1486;
	undefined field_0x1487;
	undefined field_0x1488;
	undefined field_0x1489;
	undefined field_0x148a;
	undefined field_0x148b;
	undefined field_0x148c;
	undefined field_0x148d;
	undefined field_0x148e;
	undefined field_0x148f;
	undefined field_0x1490;
	undefined field_0x1491;
	undefined field_0x1492;
	undefined field_0x1493;
	undefined field_0x1494;
	undefined field_0x1495;
	undefined field_0x1496;
	undefined field_0x1497;
	undefined field_0x1498;
	undefined field_0x1499;
	undefined field_0x149a;
	undefined field_0x149b;
	undefined field_0x149c;
	undefined field_0x149d;
	undefined field_0x149e;
	undefined field_0x149f;
	undefined field_0x14a0;
	undefined field_0x14a1;
	undefined field_0x14a2;
	undefined field_0x14a3;
	undefined field_0x14a4;
	undefined field_0x14a5;
	undefined field_0x14a6;
	undefined field_0x14a7;
	undefined field_0x14a8;
	undefined field_0x14a9;
	undefined field_0x14aa;
	undefined field_0x14ab;
	undefined field_0x14ac;
	undefined field_0x14ad;
	undefined field_0x14ae;
	undefined field_0x14af;
	undefined field_0x14b0;
	undefined field_0x14b1;
	undefined field_0x14b2;
	undefined field_0x14b3;
	undefined field_0x14b4;
	undefined field_0x14b5;
	undefined field_0x14b6;
	undefined field_0x14b7;
	undefined field_0x14b8;
	undefined field_0x14b9;
	undefined field_0x14ba;
	undefined field_0x14bb;
	undefined field_0x14bc;
	undefined field_0x14bd;
	undefined field_0x14be;
	undefined field_0x14bf;
	undefined field_0x14c0;
	undefined field_0x14c1;
	undefined field_0x14c2;
	undefined field_0x14c3;
	undefined field_0x14c4;
	undefined field_0x14c5;
	undefined field_0x14c6;
	undefined field_0x14c7;
	undefined field_0x14c8;
	undefined field_0x14c9;
	undefined field_0x14ca;
	undefined field_0x14cb;
	undefined field_0x14cc;
	undefined field_0x14cd;
	undefined field_0x14ce;
	undefined field_0x14cf;
	undefined field_0x14d0;
	undefined field_0x14d1;
	undefined field_0x14d2;
	undefined field_0x14d3;
	undefined field_0x14d4;
	undefined field_0x14d5;
	undefined field_0x14d6;
	undefined field_0x14d7;
	undefined field_0x14d8;
	undefined field_0x14d9;
	undefined field_0x14da;
	undefined field_0x14db;
	undefined field_0x14dc;
	undefined field_0x14dd;
	undefined field_0x14de;
	undefined field_0x14df;
	undefined field_0x14e0;
	undefined field_0x14e1;
	undefined field_0x14e2;
	undefined field_0x14e3;
	undefined field_0x14e4;
	undefined field_0x14e5;
	undefined field_0x14e6;
	undefined field_0x14e7;
	undefined field_0x14e8;
	undefined field_0x14e9;
	undefined field_0x14ea;
	undefined field_0x14eb;
	undefined field_0x14ec;
	undefined field_0x14ed;
	undefined field_0x14ee;
	undefined field_0x14ef;
	undefined field_0x14f0;
	undefined field_0x14f1;
	undefined field_0x14f2;
	undefined field_0x14f3;
	undefined field_0x14f4;
	undefined field_0x14f5;
	undefined field_0x14f6;
	undefined field_0x14f7;
	undefined field_0x14f8;
	undefined field_0x14f9;
	undefined field_0x14fa;
	undefined field_0x14fb;
	undefined field_0x14fc;
	undefined field_0x14fd;
	undefined field_0x14fe;
	undefined field_0x14ff;
	undefined field_0x1500;
	undefined field_0x1501;
	undefined field_0x1502;
	undefined field_0x1503;
	undefined field_0x1504;
	undefined field_0x1505;
	undefined field_0x1506;
	undefined field_0x1507;
	undefined field_0x1508;
	undefined field_0x1509;
	undefined field_0x150a;
	undefined field_0x150b;
	undefined field_0x150c;
	undefined field_0x150d;
	undefined field_0x150e;
	undefined field_0x150f;
	undefined field_0x1510;
	undefined field_0x1511;
	undefined field_0x1512;
	undefined field_0x1513;
	undefined field_0x1514;
	undefined field_0x1515;
	undefined field_0x1516;
	undefined field_0x1517;
	undefined field_0x1518;
	undefined field_0x1519;
	undefined field_0x151a;
	undefined field_0x151b;
	undefined field_0x151c;
	undefined field_0x151d;
	undefined field_0x151e;
	undefined field_0x151f;
	undefined field_0x1520;
	undefined field_0x1521;
	undefined field_0x1522;
	undefined field_0x1523;
	undefined field_0x1524;
	undefined field_0x1525;
	undefined field_0x1526;
	undefined field_0x1527;
	undefined field_0x1528;
	undefined field_0x1529;
	undefined field_0x152a;
	undefined field_0x152b;
	undefined field_0x152c;
	undefined field_0x152d;
	undefined field_0x152e;
	undefined field_0x152f;
	undefined field_0x1530;
	undefined field_0x1531;
	undefined field_0x1532;
	undefined field_0x1533;
	undefined field_0x1534;
	undefined field_0x1535;
	undefined field_0x1536;
	undefined field_0x1537;
	undefined field_0x1538;
	undefined field_0x1539;
	undefined field_0x153a;
	undefined field_0x153b;
	undefined field_0x153c;
	undefined field_0x153d;
	undefined field_0x153e;
	undefined field_0x153f;
	undefined field_0x1540;
	undefined field_0x1541;
	undefined field_0x1542;
	undefined field_0x1543;
	undefined field_0x1544;
	undefined field_0x1545;
	undefined field_0x1546;
	undefined field_0x1547;
	undefined field_0x1548;
	undefined field_0x1549;
	undefined field_0x154a;
	undefined field_0x154b;
	undefined field_0x154c;
	undefined field_0x154d;
	undefined field_0x154e;
	undefined field_0x154f;
	undefined field_0x1550;
	undefined field_0x1551;
	undefined field_0x1552;
	undefined field_0x1553;
	undefined field_0x1554;
	undefined field_0x1555;
	undefined field_0x1556;
	undefined field_0x1557;
	undefined field_0x1558;
	undefined field_0x1559;
	undefined field_0x155a;
	undefined field_0x155b;
	undefined field_0x155c;
	undefined field_0x155d;
	undefined field_0x155e;
	undefined field_0x155f;
	undefined field_0x1560;
	undefined field_0x1561;
	undefined field_0x1562;
	undefined field_0x1563;
	undefined field_0x1564;
	undefined field_0x1565;
	undefined field_0x1566;
	undefined field_0x1567;
	undefined field_0x1568;
	undefined field_0x1569;
	undefined field_0x156a;
	undefined field_0x156b;
	undefined field_0x156c;
	undefined field_0x156d;
	undefined field_0x156e;
	undefined field_0x156f;
	undefined field_0x1570;
	undefined field_0x1571;
	undefined field_0x1572;
	undefined field_0x1573;
	undefined field_0x1574;
	undefined field_0x1575;
	undefined field_0x1576;
	undefined field_0x1577;
	undefined field_0x1578;
	undefined field_0x1579;
	undefined field_0x157a;
	undefined field_0x157b;
	undefined field_0x157c;
	undefined field_0x157d;
	undefined field_0x157e;
	undefined field_0x157f;
	undefined field_0x1580;
	undefined field_0x1581;
	undefined field_0x1582;
	undefined field_0x1583;
	undefined field_0x1584;
	undefined field_0x1585;
	undefined field_0x1586;
	undefined field_0x1587;
	undefined field_0x1588;
	undefined field_0x1589;
	undefined field_0x158a;
	undefined field_0x158b;
	undefined field_0x158c;
	undefined field_0x158d;
	undefined field_0x158e;
	undefined field_0x158f;
	undefined field_0x1590;
	undefined field_0x1591;
	undefined field_0x1592;
	undefined field_0x1593;
	undefined field_0x1594;
	undefined field_0x1595;
	undefined field_0x1596;
	undefined field_0x1597;
	undefined field_0x1598;
	undefined field_0x1599;
	undefined field_0x159a;
	undefined field_0x159b;
	undefined field_0x159c;
	undefined field_0x159d;
	undefined field_0x159e;
	undefined field_0x159f;
	undefined field_0x15a0;
	undefined field_0x15a1;
	undefined field_0x15a2;
	undefined field_0x15a3;
	undefined field_0x15a4;
	undefined field_0x15a5;
	undefined field_0x15a6;
	undefined field_0x15a7;
	undefined field_0x15a8;
	undefined field_0x15a9;
	undefined field_0x15aa;
	undefined field_0x15ab;
	undefined field_0x15ac;
	undefined field_0x15ad;
	undefined field_0x15ae;
	undefined field_0x15af;
	undefined field_0x15b0;
	undefined field_0x15b1;
	undefined field_0x15b2;
	undefined field_0x15b3;
	undefined field_0x15b4;
	undefined field_0x15b5;
	undefined field_0x15b6;
	undefined field_0x15b7;
	undefined field_0x15b8;
	undefined field_0x15b9;
	undefined field_0x15ba;
	undefined field_0x15bb;
	undefined field_0x15bc;
	undefined field_0x15bd;
	undefined field_0x15be;
	undefined field_0x15bf;
	undefined field_0x15c0;
	undefined field_0x15c1;
	undefined field_0x15c2;
	undefined field_0x15c3;
	undefined field_0x15c4;
	undefined field_0x15c5;
	undefined field_0x15c6;
	undefined field_0x15c7;
	undefined field_0x15c8;
	undefined field_0x15c9;
	undefined field_0x15ca;
	undefined field_0x15cb;
	undefined field_0x15cc;
	undefined field_0x15cd;
	undefined field_0x15ce;
	undefined field_0x15cf;
	undefined field_0x15d0;
	undefined field_0x15d1;
	undefined field_0x15d2;
	undefined field_0x15d3;
	undefined field_0x15d4;
	undefined field_0x15d5;
	undefined field_0x15d6;
	undefined field_0x15d7;
	undefined field_0x15d8;
	undefined field_0x15d9;
	undefined field_0x15da;
	undefined field_0x15db;
	undefined field_0x15dc;
	undefined field_0x15dd;
	undefined field_0x15de;
	undefined field_0x15df;
	undefined field_0x15e0;
	undefined field_0x15e1;
	undefined field_0x15e2;
	undefined field_0x15e3;
	undefined field_0x15e4;
	undefined field_0x15e5;
	undefined field_0x15e6;
	undefined field_0x15e7;
	undefined field_0x15e8;
	undefined field_0x15e9;
	undefined field_0x15ea;
	undefined field_0x15eb;
	undefined field_0x15ec;
	undefined field_0x15ed;
	undefined field_0x15ee;
	undefined field_0x15ef;
	undefined field_0x15f0;
	undefined field_0x15f1;
	undefined field_0x15f2;
	undefined field_0x15f3;
	undefined field_0x15f4;
	undefined field_0x15f5;
	undefined field_0x15f6;
	undefined field_0x15f7;
	undefined field_0x15f8;
	undefined field_0x15f9;
	undefined field_0x15fa;
	undefined field_0x15fb;
	undefined field_0x15fc;
	undefined field_0x15fd;
	undefined field_0x15fe;
	undefined field_0x15ff;
	undefined field_0x1600;
	undefined field_0x1601;
	undefined field_0x1602;
	undefined field_0x1603;
	undefined field_0x1604;
	undefined field_0x1605;
	undefined field_0x1606;
	undefined field_0x1607;
	undefined field_0x1608;
	undefined field_0x1609;
	undefined field_0x160a;
	undefined field_0x160b;
	undefined field_0x160c;
	undefined field_0x160d;
	undefined field_0x160e;
	undefined field_0x160f;
	undefined field_0x1610;
	undefined field_0x1611;
	undefined field_0x1612;
	undefined field_0x1613;
	undefined field_0x1614;
	undefined field_0x1615;
	undefined field_0x1616;
	undefined field_0x1617;
	undefined field_0x1618;
	undefined field_0x1619;
	undefined field_0x161a;
	undefined field_0x161b;
	undefined field_0x161c;
	undefined field_0x161d;
	undefined field_0x161e;
	undefined field_0x161f;
	undefined field_0x1620;
	undefined field_0x1621;
	undefined field_0x1622;
	undefined field_0x1623;
	undefined field_0x1624;
	undefined field_0x1625;
	undefined field_0x1626;
	undefined field_0x1627;
	undefined field_0x1628;
	undefined field_0x1629;
	undefined field_0x162a;
	undefined field_0x162b;
	undefined field_0x162c;
	undefined field_0x162d;
	undefined field_0x162e;
	undefined field_0x162f;
	undefined field_0x1630;
	undefined field_0x1631;
	undefined field_0x1632;
	undefined field_0x1633;
	undefined field_0x1634;
	undefined field_0x1635;
	undefined field_0x1636;
	undefined field_0x1637;
	undefined field_0x1638;
	undefined field_0x1639;
	undefined field_0x163a;
	undefined field_0x163b;
	undefined field_0x163c;
	undefined field_0x163d;
	undefined field_0x163e;
	undefined field_0x163f;
	undefined field_0x1640;
	undefined field_0x1641;
	undefined field_0x1642;
	undefined field_0x1643;
	undefined field_0x1644;
	undefined field_0x1645;
	undefined field_0x1646;
	undefined field_0x1647;
	undefined field_0x1648;
	undefined field_0x1649;
	undefined field_0x164a;
	undefined field_0x164b;
	undefined field_0x164c;
	undefined field_0x164d;
	undefined field_0x164e;
	undefined field_0x164f;
	undefined field_0x1650;
	undefined field_0x1651;
	undefined field_0x1652;
	undefined field_0x1653;
	undefined field_0x1654;
	undefined field_0x1655;
	undefined field_0x1656;
	undefined field_0x1657;
	undefined field_0x1658;
	undefined field_0x1659;
	undefined field_0x165a;
	undefined field_0x165b;
	undefined field_0x165c;
	undefined field_0x165d;
	undefined field_0x165e;
	undefined field_0x165f;
	undefined field_0x1660;
	undefined field_0x1661;
	undefined field_0x1662;
	undefined field_0x1663;
	undefined field_0x1664;
	undefined field_0x1665;
	undefined field_0x1666;
	undefined field_0x1667;
	undefined field_0x1668;
	undefined field_0x1669;
	undefined field_0x166a;
	undefined field_0x166b;
	undefined field_0x166c;
	undefined field_0x166d;
	undefined field_0x166e;
	undefined field_0x166f;
	undefined field_0x1670;
	undefined field_0x1671;
	undefined field_0x1672;
	undefined field_0x1673;
	undefined field_0x1674;
	undefined field_0x1675;
	undefined field_0x1676;
	undefined field_0x1677;
	undefined field_0x1678;
	undefined field_0x1679;
	undefined field_0x167a;
	undefined field_0x167b;
	undefined field_0x167c;
	undefined field_0x167d;
	undefined field_0x167e;
	undefined field_0x167f;
	undefined field_0x1680;
	undefined field_0x1681;
	undefined field_0x1682;
	undefined field_0x1683;
	undefined field_0x1684;
	undefined field_0x1685;
	undefined field_0x1686;
	undefined field_0x1687;
	undefined field_0x1688;
	undefined field_0x1689;
	undefined field_0x168a;
	undefined field_0x168b;
	undefined field_0x168c;
	undefined field_0x168d;
	undefined field_0x168e;
	undefined field_0x168f;
	undefined field_0x1690;
	undefined field_0x1691;
	undefined field_0x1692;
	undefined field_0x1693;
	undefined field_0x1694;
	undefined field_0x1695;
	undefined field_0x1696;
	undefined field_0x1697;
	undefined field_0x1698;
	undefined field_0x1699;
	undefined field_0x169a;
	undefined field_0x169b;
	undefined field_0x169c;
	undefined field_0x169d;
	undefined field_0x169e;
	undefined field_0x169f;
	undefined field_0x16a0;
	undefined field_0x16a1;
	undefined field_0x16a2;
	undefined field_0x16a3;
	undefined field_0x16a4;
	undefined field_0x16a5;
	undefined field_0x16a6;
	undefined field_0x16a7;
	undefined field_0x16a8;
	undefined field_0x16a9;
	undefined field_0x16aa;
	undefined field_0x16ab;
	undefined field_0x16ac;
	undefined field_0x16ad;
	undefined field_0x16ae;
	undefined field_0x16af;
	undefined field_0x16b0;
	undefined field_0x16b1;
	undefined field_0x16b2;
	undefined field_0x16b3;
	undefined field_0x16b4;
	undefined field_0x16b5;
	undefined field_0x16b6;
	undefined field_0x16b7;
	undefined field_0x16b8;
	undefined field_0x16b9;
	undefined field_0x16ba;
	undefined field_0x16bb;
	undefined field_0x16bc;
	undefined field_0x16bd;
	undefined field_0x16be;
	undefined field_0x16bf;
	undefined field_0x16c0;
	undefined field_0x16c1;
	undefined field_0x16c2;
	undefined field_0x16c3;
	undefined field_0x16c4;
	undefined field_0x16c5;
	undefined field_0x16c6;
	undefined field_0x16c7;
	undefined field_0x16c8;
	undefined field_0x16c9;
	undefined field_0x16ca;
	undefined field_0x16cb;
	undefined field_0x16cc;
	undefined field_0x16cd;
	undefined field_0x16ce;
	undefined field_0x16cf;
	undefined field_0x16d0;
	undefined field_0x16d1;
	undefined field_0x16d2;
	undefined field_0x16d3;
	undefined field_0x16d4;
	undefined field_0x16d5;
	undefined field_0x16d6;
	undefined field_0x16d7;
	undefined field_0x16d8;
	undefined field_0x16d9;
	undefined field_0x16da;
	undefined field_0x16db;
	undefined field_0x16dc;
	undefined field_0x16dd;
	undefined field_0x16de;
	undefined field_0x16df;
	undefined field_0x16e0;
	undefined field_0x16e1;
	undefined field_0x16e2;
	undefined field_0x16e3;
	undefined field_0x16e4;
	undefined field_0x16e5;
	undefined field_0x16e6;
	undefined field_0x16e7;
	undefined field_0x16e8;
	undefined field_0x16e9;
	undefined field_0x16ea;
	undefined field_0x16eb;
	undefined field_0x16ec;
	undefined field_0x16ed;
	undefined field_0x16ee;
	undefined field_0x16ef;
	undefined field_0x16f0;
	undefined field_0x16f1;
	undefined field_0x16f2;
	undefined field_0x16f3;
	undefined field_0x16f4;
	undefined field_0x16f5;
	undefined field_0x16f6;
	undefined field_0x16f7;
	undefined field_0x16f8;
	undefined field_0x16f9;
	undefined field_0x16fa;
	undefined field_0x16fb;
	undefined field_0x16fc;
	undefined field_0x16fd;
	undefined field_0x16fe;
	undefined field_0x16ff;
	undefined field_0x1700;
	undefined field_0x1701;
	undefined field_0x1702;
	undefined field_0x1703;
	undefined field_0x1704;
	undefined field_0x1705;
	undefined field_0x1706;
	undefined field_0x1707;
	undefined field_0x1708;
	undefined field_0x1709;
	undefined field_0x170a;
	undefined field_0x170b;
	undefined field_0x170c;
	undefined field_0x170d;
	undefined field_0x170e;
	undefined field_0x170f;
	undefined field_0x1710;
	undefined field_0x1711;
	undefined field_0x1712;
	undefined field_0x1713;
	undefined field_0x1714;
	undefined field_0x1715;
	undefined field_0x1716;
	undefined field_0x1717;
	undefined field_0x1718;
	undefined field_0x1719;
	undefined field_0x171a;
	undefined field_0x171b;
	undefined field_0x171c;
	undefined field_0x171d;
	undefined field_0x171e;
	undefined field_0x171f;
	undefined field_0x1720;
	undefined field_0x1721;
	undefined field_0x1722;
	undefined field_0x1723;
	undefined field_0x1724;
	undefined field_0x1725;
	undefined field_0x1726;
	undefined field_0x1727;
	undefined field_0x1728;
	undefined field_0x1729;
	undefined field_0x172a;
	undefined field_0x172b;
	undefined field_0x172c;
	undefined field_0x172d;
	undefined field_0x172e;
	undefined field_0x172f;
	undefined field_0x1730;
	undefined field_0x1731;
	undefined field_0x1732;
	undefined field_0x1733;
	undefined field_0x1734;
	undefined field_0x1735;
	undefined field_0x1736;
	undefined field_0x1737;
	undefined field_0x1738;
	undefined field_0x1739;
	undefined field_0x173a;
	undefined field_0x173b;
	undefined field_0x173c;
	undefined field_0x173d;
	undefined field_0x173e;
	undefined field_0x173f;
	undefined field_0x1740;
	undefined field_0x1741;
	undefined field_0x1742;
	undefined field_0x1743;
	undefined field_0x1744;
	undefined field_0x1745;
	undefined field_0x1746;
	undefined field_0x1747;
	undefined field_0x1748;
	undefined field_0x1749;
	undefined field_0x174a;
	undefined field_0x174b;
	undefined field_0x174c;
	undefined field_0x174d;
	undefined field_0x174e;
	undefined field_0x174f;
	undefined field_0x1750;
	undefined field_0x1751;
	undefined field_0x1752;
	undefined field_0x1753;
	undefined field_0x1754;
	undefined field_0x1755;
	undefined field_0x1756;
	undefined field_0x1757;
	undefined field_0x1758;
	undefined field_0x1759;
	undefined field_0x175a;
	undefined field_0x175b;
	undefined field_0x175c;
	undefined field_0x175d;
	undefined field_0x175e;
	undefined field_0x175f;
	undefined field_0x1760;
	undefined field_0x1761;
	undefined field_0x1762;
	undefined field_0x1763;
	undefined field_0x1764;
	undefined field_0x1765;
	undefined field_0x1766;
	undefined field_0x1767;
	undefined field_0x1768;
	undefined field_0x1769;
	undefined field_0x176a;
	undefined field_0x176b;
	undefined field_0x176c;
	undefined field_0x176d;
	undefined field_0x176e;
	undefined field_0x176f;
	undefined field_0x1770;
	undefined field_0x1771;
	undefined field_0x1772;
	undefined field_0x1773;
	undefined field_0x1774;
	undefined field_0x1775;
	undefined field_0x1776;
	undefined field_0x1777;
	undefined field_0x1778;
	undefined field_0x1779;
	undefined field_0x177a;
	undefined field_0x177b;
	undefined field_0x177c;
	undefined field_0x177d;
	undefined field_0x177e;
	undefined field_0x177f;
	undefined field_0x1780;
	undefined field_0x1781;
	undefined field_0x1782;
	undefined field_0x1783;
	undefined field_0x1784;
	undefined field_0x1785;
	undefined field_0x1786;
	undefined field_0x1787;
	undefined field_0x1788;
	undefined field_0x1789;
	undefined field_0x178a;
	undefined field_0x178b;
	undefined field_0x178c;
	undefined field_0x178d;
	undefined field_0x178e;
	undefined field_0x178f;
	undefined field_0x1790;
	undefined field_0x1791;
	undefined field_0x1792;
	undefined field_0x1793;
	undefined field_0x1794;
	undefined field_0x1795;
	undefined field_0x1796;
	undefined field_0x1797;
	undefined field_0x1798;
	undefined field_0x1799;
	undefined field_0x179a;
	undefined field_0x179b;
	undefined field_0x179c;
	undefined field_0x179d;
	undefined field_0x179e;
	undefined field_0x179f;
	undefined field_0x17a0;
	undefined field_0x17a1;
	undefined field_0x17a2;
	undefined field_0x17a3;
	undefined field_0x17a4;
	undefined field_0x17a5;
	undefined field_0x17a6;
	undefined field_0x17a7;
	undefined field_0x17a8;
	undefined field_0x17a9;
	undefined field_0x17aa;
	undefined field_0x17ab;
	undefined field_0x17ac;
	undefined field_0x17ad;
	undefined field_0x17ae;
	undefined field_0x17af;
	undefined field_0x17b0;
	undefined field_0x17b1;
	undefined field_0x17b2;
	undefined field_0x17b3;
	undefined field_0x17b4;
	undefined field_0x17b5;
	undefined field_0x17b6;
	undefined field_0x17b7;
	undefined field_0x17b8;
	undefined field_0x17b9;
	undefined field_0x17ba;
	undefined field_0x17bb;
	undefined field_0x17bc;
	undefined field_0x17bd;
	undefined field_0x17be;
	undefined field_0x17bf;
	undefined field_0x17c0;
	undefined field_0x17c1;
	undefined field_0x17c2;
	undefined field_0x17c3;
	undefined field_0x17c4;
	undefined field_0x17c5;
	undefined field_0x17c6;
	undefined field_0x17c7;
	undefined field_0x17c8;
	undefined field_0x17c9;
	undefined field_0x17ca;
	undefined field_0x17cb;
	undefined field_0x17cc;
	undefined field_0x17cd;
	undefined field_0x17ce;
	undefined field_0x17cf;
	undefined field_0x17d0;
	undefined field_0x17d1;
	undefined field_0x17d2;
	undefined field_0x17d3;
	undefined field_0x17d4;
	undefined field_0x17d5;
	undefined field_0x17d6;
	undefined field_0x17d7;
	undefined field_0x17d8;
	undefined field_0x17d9;
	undefined field_0x17da;
	undefined field_0x17db;
	undefined field_0x17dc;
	undefined field_0x17dd;
	undefined field_0x17de;
	undefined field_0x17df;
	undefined field_0x17e0;
	undefined field_0x17e1;
	undefined field_0x17e2;
	undefined field_0x17e3;
	undefined field_0x17e4;
	undefined field_0x17e5;
	undefined field_0x17e6;
	undefined field_0x17e7;
	undefined field_0x17e8;
	undefined field_0x17e9;
	undefined field_0x17ea;
	undefined field_0x17eb;
	undefined field_0x17ec;
	undefined field_0x17ed;
	undefined field_0x17ee;
	undefined field_0x17ef;
	undefined field_0x17f0;
	undefined field_0x17f1;
	undefined field_0x17f2;
	undefined field_0x17f3;
	undefined field_0x17f4;
	undefined field_0x17f5;
	undefined field_0x17f6;
	undefined field_0x17f7;
	undefined field_0x17f8;
	undefined field_0x17f9;
	undefined field_0x17fa;
	undefined field_0x17fb;
	undefined field_0x17fc;
	undefined field_0x17fd;
	undefined field_0x17fe;
	undefined field_0x17ff;
	undefined field_0x1800;
	undefined field_0x1801;
	undefined field_0x1802;
	undefined field_0x1803;
	undefined field_0x1804;
	undefined field_0x1805;
	undefined field_0x1806;
	undefined field_0x1807;
	undefined field_0x1808;
	undefined field_0x1809;
	undefined field_0x180a;
	undefined field_0x180b;
	undefined field_0x180c;
	undefined field_0x180d;
	undefined field_0x180e;
	undefined field_0x180f;
	undefined field_0x1810;
	undefined field_0x1811;
	undefined field_0x1812;
	undefined field_0x1813;
	undefined field_0x1814;
	undefined field_0x1815;
	undefined field_0x1816;
	undefined field_0x1817;
	undefined field_0x1818;
	undefined field_0x1819;
	undefined field_0x181a;
	undefined field_0x181b;
	undefined field_0x181c;
	undefined field_0x181d;
	undefined field_0x181e;
	undefined field_0x181f;
	undefined field_0x1820;
	undefined field_0x1821;
	undefined field_0x1822;
	undefined field_0x1823;
	undefined field_0x1824;
	undefined field_0x1825;
	undefined field_0x1826;
	undefined field_0x1827;
	undefined field_0x1828;
	undefined field_0x1829;
	undefined field_0x182a;
	undefined field_0x182b;
	undefined field_0x182c;
	undefined field_0x182d;
	undefined field_0x182e;
	undefined field_0x182f;
	undefined field_0x1830;
	undefined field_0x1831;
	undefined field_0x1832;
	undefined field_0x1833;
	undefined field_0x1834;
	undefined field_0x1835;
	undefined field_0x1836;
	undefined field_0x1837;
	undefined field_0x1838;
	undefined field_0x1839;
	undefined field_0x183a;
	undefined field_0x183b;
	undefined field_0x183c;
	undefined field_0x183d;
	undefined field_0x183e;
	undefined field_0x183f;
	undefined field_0x1840;
	undefined field_0x1841;
	undefined field_0x1842;
	undefined field_0x1843;
	undefined field_0x1844;
	undefined field_0x1845;
	undefined field_0x1846;
	undefined field_0x1847;
	undefined field_0x1848;
	undefined field_0x1849;
	undefined field_0x184a;
	undefined field_0x184b;
	undefined field_0x184c;
	undefined field_0x184d;
	undefined field_0x184e;
	undefined field_0x184f;
	undefined field_0x1850;
	undefined field_0x1851;
	undefined field_0x1852;
	undefined field_0x1853;
	undefined field_0x1854;
	undefined field_0x1855;
	undefined field_0x1856;
	undefined field_0x1857;
	undefined field_0x1858;
	undefined field_0x1859;
	undefined field_0x185a;
	undefined field_0x185b;
	undefined field_0x185c;
	undefined field_0x185d;
	undefined field_0x185e;
	undefined field_0x185f;
	undefined field_0x1860;
	undefined field_0x1861;
	undefined field_0x1862;
	undefined field_0x1863;
	undefined field_0x1864;
	undefined field_0x1865;
	undefined field_0x1866;
	undefined field_0x1867;
	undefined field_0x1868;
	undefined field_0x1869;
	undefined field_0x186a;
	undefined field_0x186b;
	undefined field_0x186c;
	undefined field_0x186d;
	undefined field_0x186e;
	undefined field_0x186f;
	undefined field_0x1870;
	undefined field_0x1871;
	undefined field_0x1872;
	undefined field_0x1873;
	undefined field_0x1874;
	undefined field_0x1875;
	undefined field_0x1876;
	undefined field_0x1877;
	undefined field_0x1878;
	undefined field_0x1879;
	undefined field_0x187a;
	undefined field_0x187b;
	undefined field_0x187c;
	undefined field_0x187d;
	undefined field_0x187e;
	undefined field_0x187f;
	undefined field_0x1880;
	undefined field_0x1881;
	undefined field_0x1882;
	undefined field_0x1883;
	undefined field_0x1884;
	undefined field_0x1885;
	undefined field_0x1886;
	undefined field_0x1887;
	undefined field_0x1888;
	undefined field_0x1889;
	undefined field_0x188a;
	undefined field_0x188b;
	undefined field_0x188c;
	undefined field_0x188d;
	undefined field_0x188e;
	undefined field_0x188f;
	undefined field_0x1890;
	undefined field_0x1891;
	undefined field_0x1892;
	undefined field_0x1893;
	undefined field_0x1894;
	undefined field_0x1895;
	undefined field_0x1896;
	undefined field_0x1897;
	undefined field_0x1898;
	undefined field_0x1899;
	undefined field_0x189a;
	undefined field_0x189b;
	undefined field_0x189c;
	undefined field_0x189d;
	undefined field_0x189e;
	undefined field_0x189f;
	undefined field_0x18a0;
	undefined field_0x18a1;
	undefined field_0x18a2;
	undefined field_0x18a3;
	undefined field_0x18a4;
	undefined field_0x18a5;
	undefined field_0x18a6;
	undefined field_0x18a7;
	undefined field_0x18a8;
	undefined field_0x18a9;
	undefined field_0x18aa;
	undefined field_0x18ab;
	undefined field_0x18ac;
	undefined field_0x18ad;
	undefined field_0x18ae;
	undefined field_0x18af;
	undefined field_0x18b0;
	undefined field_0x18b1;
	undefined field_0x18b2;
	undefined field_0x18b3;
	undefined field_0x18b4;
	undefined field_0x18b5;
	undefined field_0x18b6;
	undefined field_0x18b7;
	undefined field_0x18b8;
	undefined field_0x18b9;
	undefined field_0x18ba;
	undefined field_0x18bb;
	undefined field_0x18bc;
	undefined field_0x18bd;
	undefined field_0x18be;
	undefined field_0x18bf;
	undefined field_0x18c0;
	undefined field_0x18c1;
	undefined field_0x18c2;
	undefined field_0x18c3;
	undefined field_0x18c4;
	undefined field_0x18c5;
	undefined field_0x18c6;
	undefined field_0x18c7;
	undefined field_0x18c8;
	undefined field_0x18c9;
	undefined field_0x18ca;
	undefined field_0x18cb;
	undefined field_0x18cc;
	undefined field_0x18cd;
	undefined field_0x18ce;
	undefined field_0x18cf;
	undefined field_0x18d0;
	undefined field_0x18d1;
	undefined field_0x18d2;
	undefined field_0x18d3;
	undefined field_0x18d4;
	undefined field_0x18d5;
	undefined field_0x18d6;
	undefined field_0x18d7;
	undefined field_0x18d8;
	undefined field_0x18d9;
	undefined field_0x18da;
	undefined field_0x18db;
	undefined field_0x18dc;
	undefined field_0x18dd;
	undefined field_0x18de;
	undefined field_0x18df;
	undefined field_0x18e0;
	undefined field_0x18e1;
	undefined field_0x18e2;
	undefined field_0x18e3;
	undefined field_0x18e4;
	undefined field_0x18e5;
	undefined field_0x18e6;
	undefined field_0x18e7;
	undefined field_0x18e8;
	undefined field_0x18e9;
	undefined field_0x18ea;
	undefined field_0x18eb;
	undefined field_0x18ec;
	undefined field_0x18ed;
	undefined field_0x18ee;
	undefined field_0x18ef;
	undefined field_0x18f0;
	undefined field_0x18f1;
	undefined field_0x18f2;
	undefined field_0x18f3;
	undefined field_0x18f4;
	undefined field_0x18f5;
	undefined field_0x18f6;
	undefined field_0x18f7;
	undefined field_0x18f8;
	undefined field_0x18f9;
	undefined field_0x18fa;
	undefined field_0x18fb;
	undefined field_0x18fc;
	undefined field_0x18fd;
	undefined field_0x18fe;
	undefined field_0x18ff;
	undefined field_0x1900;
	undefined field_0x1901;
	undefined field_0x1902;
	undefined field_0x1903;
	undefined field_0x1904;
	undefined field_0x1905;
	undefined field_0x1906;
	undefined field_0x1907;
	undefined field_0x1908;
	undefined field_0x1909;
	undefined field_0x190a;
	undefined field_0x190b;
	undefined field_0x190c;
	undefined field_0x190d;
	undefined field_0x190e;
	undefined field_0x190f;
	undefined field_0x1910;
	undefined field_0x1911;
	undefined field_0x1912;
	undefined field_0x1913;
	undefined field_0x1914;
	undefined field_0x1915;
	undefined field_0x1916;
	undefined field_0x1917;
	undefined field_0x1918;
	undefined field_0x1919;
	undefined field_0x191a;
	undefined field_0x191b;
	undefined field_0x191c;
	undefined field_0x191d;
	undefined field_0x191e;
	undefined field_0x191f;
	undefined field_0x1920;
	undefined field_0x1921;
	undefined field_0x1922;
	undefined field_0x1923;
	undefined field_0x1924;
	undefined field_0x1925;
	undefined field_0x1926;
	undefined field_0x1927;
	undefined field_0x1928;
	undefined field_0x1929;
	undefined field_0x192a;
	undefined field_0x192b;
	undefined field_0x192c;
	undefined field_0x192d;
	undefined field_0x192e;
	undefined field_0x192f;
	undefined field_0x1930;
	undefined field_0x1931;
	undefined field_0x1932;
	undefined field_0x1933;
	undefined field_0x1934;
	undefined field_0x1935;
	undefined field_0x1936;
	undefined field_0x1937;
	undefined field_0x1938;
	undefined field_0x1939;
	undefined field_0x193a;
	undefined field_0x193b;
	undefined field_0x193c;
	undefined field_0x193d;
	undefined field_0x193e;
	undefined field_0x193f;
	undefined field_0x1940;
	undefined field_0x1941;
	undefined field_0x1942;
	undefined field_0x1943;
	undefined field_0x1944;
	undefined field_0x1945;
	undefined field_0x1946;
	undefined field_0x1947;
	undefined field_0x1948;
	undefined field_0x1949;
	undefined field_0x194a;
	undefined field_0x194b;
	undefined field_0x194c;
	undefined field_0x194d;
	undefined field_0x194e;
	undefined field_0x194f;
	undefined field_0x1950;
	undefined field_0x1951;
	undefined field_0x1952;
	undefined field_0x1953;
	undefined field_0x1954;
	undefined field_0x1955;
	undefined field_0x1956;
	undefined field_0x1957;
	undefined field_0x1958;
	undefined field_0x1959;
	undefined field_0x195a;
	undefined field_0x195b;
	undefined field_0x195c;
	undefined field_0x195d;
	undefined field_0x195e;
	undefined field_0x195f;
	undefined field_0x1960;
	undefined field_0x1961;
	undefined field_0x1962;
	undefined field_0x1963;
	undefined field_0x1964;
	undefined field_0x1965;
	undefined field_0x1966;
	undefined field_0x1967;
	undefined field_0x1968;
	undefined field_0x1969;
	undefined field_0x196a;
	undefined field_0x196b;
	undefined field_0x196c;
	undefined field_0x196d;
	undefined field_0x196e;
	undefined field_0x196f;
	undefined field_0x1970;
	undefined field_0x1971;
	undefined field_0x1972;
	undefined field_0x1973;
	undefined field_0x1974;
	undefined field_0x1975;
	undefined field_0x1976;
	undefined field_0x1977;
	undefined field_0x1978;
	undefined field_0x1979;
	undefined field_0x197a;
	undefined field_0x197b;
	undefined field_0x197c;
	undefined field_0x197d;
	undefined field_0x197e;
	undefined field_0x197f;
	undefined field_0x1980;
	undefined field_0x1981;
	undefined field_0x1982;
	undefined field_0x1983;
	undefined field_0x1984;
	undefined field_0x1985;
	undefined field_0x1986;
	undefined field_0x1987;
	undefined field_0x1988;
	undefined field_0x1989;
	undefined field_0x198a;
	undefined field_0x198b;
	undefined field_0x198c;
	undefined field_0x198d;
	undefined field_0x198e;
	undefined field_0x198f;
	undefined field_0x1990;
	undefined field_0x1991;
	undefined field_0x1992;
	undefined field_0x1993;
	undefined field_0x1994;
	undefined field_0x1995;
	undefined field_0x1996;
	undefined field_0x1997;
	undefined field_0x1998;
	undefined field_0x1999;
	undefined field_0x199a;
	undefined field_0x199b;
	undefined field_0x199c;
	undefined field_0x199d;
	undefined field_0x199e;
	undefined field_0x199f;
	undefined field_0x19a0;
	undefined field_0x19a1;
	undefined field_0x19a2;
	undefined field_0x19a3;
	undefined field_0x19a4;
	undefined field_0x19a5;
	undefined field_0x19a6;
	undefined field_0x19a7;
	undefined field_0x19a8;
	undefined field_0x19a9;
	undefined field_0x19aa;
	undefined field_0x19ab;
	undefined field_0x19ac;
	undefined field_0x19ad;
	undefined field_0x19ae;
	undefined field_0x19af;
	undefined field_0x19b0;
	undefined field_0x19b1;
	undefined field_0x19b2;
	undefined field_0x19b3;
	undefined field_0x19b4;
	undefined field_0x19b5;
	undefined field_0x19b6;
	undefined field_0x19b7;
	undefined field_0x19b8;
	undefined field_0x19b9;
	undefined field_0x19ba;
	undefined field_0x19bb;
	undefined field_0x19bc;
	undefined field_0x19bd;
	undefined field_0x19be;
	undefined field_0x19bf;
	undefined field_0x19c0;
	undefined field_0x19c1;
	undefined field_0x19c2;
	undefined field_0x19c3;
	undefined field_0x19c4;
	undefined field_0x19c5;
	undefined field_0x19c6;
	undefined field_0x19c7;
	undefined field_0x19c8;
	undefined field_0x19c9;
	undefined field_0x19ca;
	undefined field_0x19cb;
	undefined field_0x19cc;
	undefined field_0x19cd;
	undefined field_0x19ce;
	undefined field_0x19cf;
	undefined field_0x19d0;
	undefined field_0x19d1;
	undefined field_0x19d2;
	undefined field_0x19d3;
	undefined field_0x19d4;
	undefined field_0x19d5;
	undefined field_0x19d6;
	undefined field_0x19d7;
	undefined field_0x19d8;
	undefined field_0x19d9;
	undefined field_0x19da;
	undefined field_0x19db;
	undefined field_0x19dc;
	undefined field_0x19dd;
	undefined field_0x19de;
	undefined field_0x19df;
	undefined field_0x19e0;
	undefined field_0x19e1;
	undefined field_0x19e2;
	undefined field_0x19e3;
	undefined field_0x19e4;
	undefined field_0x19e5;
	undefined field_0x19e6;
	undefined field_0x19e7;
	undefined field_0x19e8;
	undefined field_0x19e9;
	undefined field_0x19ea;
	undefined field_0x19eb;
	undefined field_0x19ec;
	undefined field_0x19ed;
	undefined field_0x19ee;
	undefined field_0x19ef;
	undefined field_0x19f0;
	undefined field_0x19f1;
	undefined field_0x19f2;
	undefined field_0x19f3;
	undefined field_0x19f4;
	undefined field_0x19f5;
	undefined field_0x19f6;
	undefined field_0x19f7;
	undefined field_0x19f8;
	undefined field_0x19f9;
	undefined field_0x19fa;
	undefined field_0x19fb;
	undefined field_0x19fc;
	undefined field_0x19fd;
	undefined field_0x19fe;
	undefined field_0x19ff;
	undefined field_0x1a00;
	undefined field_0x1a01;
	undefined field_0x1a02;
	undefined field_0x1a03;
	undefined field_0x1a04;
	undefined field_0x1a05;
	undefined field_0x1a06;
	undefined field_0x1a07;
	undefined field_0x1a08;
	undefined field_0x1a09;
	undefined field_0x1a0a;
	undefined field_0x1a0b;
	undefined field_0x1a0c;
	undefined field_0x1a0d;
	undefined field_0x1a0e;
	undefined field_0x1a0f;
	undefined field_0x1a10;
	undefined field_0x1a11;
	undefined field_0x1a12;
	undefined field_0x1a13;
	undefined field_0x1a14;
	undefined field_0x1a15;
	undefined field_0x1a16;
	undefined field_0x1a17;
	undefined field_0x1a18;
	undefined field_0x1a19;
	undefined field_0x1a1a;
	undefined field_0x1a1b;
	undefined field_0x1a1c;
	undefined field_0x1a1d;
	undefined field_0x1a1e;
	undefined field_0x1a1f;
	undefined field_0x1a20;
	undefined field_0x1a21;
	undefined field_0x1a22;
	undefined field_0x1a23;
	undefined field_0x1a24;
	undefined field_0x1a25;
	undefined field_0x1a26;
	undefined field_0x1a27;
	undefined field_0x1a28;
	undefined field_0x1a29;
	undefined field_0x1a2a;
	undefined field_0x1a2b;
	undefined field_0x1a2c;
	undefined field_0x1a2d;
	undefined field_0x1a2e;
	undefined field_0x1a2f;
	undefined field_0x1a30;
	undefined field_0x1a31;
	undefined field_0x1a32;
	undefined field_0x1a33;
	undefined field_0x1a34;
	undefined field_0x1a35;
	undefined field_0x1a36;
	undefined field_0x1a37;
	undefined field_0x1a38;
	undefined field_0x1a39;
	undefined field_0x1a3a;
	undefined field_0x1a3b;
	undefined field_0x1a3c;
	undefined field_0x1a3d;
	undefined field_0x1a3e;
	undefined field_0x1a3f;
	undefined field_0x1a40;
	undefined field_0x1a41;
	undefined field_0x1a42;
	undefined field_0x1a43;
	undefined field_0x1a44;
	undefined field_0x1a45;
	undefined field_0x1a46;
	undefined field_0x1a47;
	undefined field_0x1a48;
	undefined field_0x1a49;
	undefined field_0x1a4a;
	undefined field_0x1a4b;
	undefined field_0x1a4c;
	undefined field_0x1a4d;
	undefined field_0x1a4e;
	undefined field_0x1a4f;
	undefined field_0x1a50;
	undefined field_0x1a51;
	undefined field_0x1a52;
	undefined field_0x1a53;
	undefined field_0x1a54;
	undefined field_0x1a55;
	undefined field_0x1a56;
	undefined field_0x1a57;
	undefined field_0x1a58;
	undefined field_0x1a59;
	undefined field_0x1a5a;
	undefined field_0x1a5b;
	undefined field_0x1a5c;
	undefined field_0x1a5d;
	undefined field_0x1a5e;
	undefined field_0x1a5f;
	undefined field_0x1a60;
	undefined field_0x1a61;
	undefined field_0x1a62;
	undefined field_0x1a63;
	undefined field_0x1a64;
	undefined field_0x1a65;
	undefined field_0x1a66;
	undefined field_0x1a67;
	undefined field_0x1a68;
	undefined field_0x1a69;
	undefined field_0x1a6a;
	undefined field_0x1a6b;
	undefined field_0x1a6c;
	undefined field_0x1a6d;
	undefined field_0x1a6e;
	undefined field_0x1a6f;
	undefined field_0x1a70;
	undefined field_0x1a71;
	undefined field_0x1a72;
	undefined field_0x1a73;
	undefined field_0x1a74;
	undefined field_0x1a75;
	undefined field_0x1a76;
	undefined field_0x1a77;
	undefined field_0x1a78;
	undefined field_0x1a79;
	undefined field_0x1a7a;
	undefined field_0x1a7b;
	undefined field_0x1a7c;
	undefined field_0x1a7d;
	undefined field_0x1a7e;
	undefined field_0x1a7f;
	undefined field_0x1a80;
	undefined field_0x1a81;
	undefined field_0x1a82;
	undefined field_0x1a83;
	undefined field_0x1a84;
	undefined field_0x1a85;
	undefined field_0x1a86;
	undefined field_0x1a87;
	undefined field_0x1a88;
	undefined field_0x1a89;
	undefined field_0x1a8a;
	undefined field_0x1a8b;
	undefined field_0x1a8c;
	undefined field_0x1a8d;
	undefined field_0x1a8e;
	undefined field_0x1a8f;
	undefined field_0x1a90;
	undefined field_0x1a91;
	undefined field_0x1a92;
	undefined field_0x1a93;
	undefined field_0x1a94;
	undefined field_0x1a95;
	undefined field_0x1a96;
	undefined field_0x1a97;
	undefined field_0x1a98;
	undefined field_0x1a99;
	undefined field_0x1a9a;
	undefined field_0x1a9b;
	undefined field_0x1a9c;
	undefined field_0x1a9d;
	undefined field_0x1a9e;
	undefined field_0x1a9f;
	undefined field_0x1aa0;
	undefined field_0x1aa1;
	undefined field_0x1aa2;
	undefined field_0x1aa3;
	undefined field_0x1aa4;
	undefined field_0x1aa5;
	undefined field_0x1aa6;
	undefined field_0x1aa7;
	undefined field_0x1aa8;
	undefined field_0x1aa9;
	undefined field_0x1aaa;
	undefined field_0x1aab;
	undefined field_0x1aac;
	undefined field_0x1aad;
	undefined field_0x1aae;
	undefined field_0x1aaf;
	undefined field_0x1ab0;
	undefined field_0x1ab1;
	undefined field_0x1ab2;
	undefined field_0x1ab3;
	undefined field_0x1ab4;
	undefined field_0x1ab5;
	undefined field_0x1ab6;
	undefined field_0x1ab7;
	undefined field_0x1ab8;
	undefined field_0x1ab9;
	undefined field_0x1aba;
	undefined field_0x1abb;
	undefined field_0x1abc;
	undefined field_0x1abd;
	undefined field_0x1abe;
	undefined field_0x1abf;
	undefined field_0x1ac0;
	undefined field_0x1ac1;
	undefined field_0x1ac2;
	undefined field_0x1ac3;
	undefined field_0x1ac4;
	undefined field_0x1ac5;
	undefined field_0x1ac6;
	undefined field_0x1ac7;
	undefined field_0x1ac8;
	undefined field_0x1ac9;
	undefined field_0x1aca;
	undefined field_0x1acb;
	undefined field_0x1acc;
	undefined field_0x1acd;
	undefined field_0x1ace;
	undefined field_0x1acf;
	undefined field_0x1ad0;
	undefined field_0x1ad1;
	undefined field_0x1ad2;
	undefined field_0x1ad3;
	undefined field_0x1ad4;
	undefined field_0x1ad5;
	undefined field_0x1ad6;
	undefined field_0x1ad7;
	undefined field_0x1ad8;
	undefined field_0x1ad9;
	undefined field_0x1ada;
	undefined field_0x1adb;
	undefined field_0x1adc;
	undefined field_0x1add;
	undefined field_0x1ade;
	undefined field_0x1adf;
	undefined field_0x1ae0;
	undefined field_0x1ae1;
	undefined field_0x1ae2;
	undefined field_0x1ae3;
	undefined field_0x1ae4;
	undefined field_0x1ae5;
	undefined field_0x1ae6;
	undefined field_0x1ae7;
	undefined field_0x1ae8;
	undefined field_0x1ae9;
	undefined field_0x1aea;
	undefined field_0x1aeb;
	undefined field_0x1aec;
	undefined field_0x1aed;
	undefined field_0x1aee;
	undefined field_0x1aef;
	undefined field_0x1af0;
	undefined field_0x1af1;
	undefined field_0x1af2;
	undefined field_0x1af3;
	undefined field_0x1af4;
	undefined field_0x1af5;
	undefined field_0x1af6;
	undefined field_0x1af7;
	undefined field_0x1af8;
	undefined field_0x1af9;
	undefined field_0x1afa;
	undefined field_0x1afb;
	undefined field_0x1afc;
	undefined field_0x1afd;
	undefined field_0x1afe;
	undefined field_0x1aff;
	undefined field_0x1b00;
	undefined field_0x1b01;
	undefined field_0x1b02;
	undefined field_0x1b03;
	undefined field_0x1b04;
	undefined field_0x1b05;
	undefined field_0x1b06;
	undefined field_0x1b07;
	undefined field_0x1b08;
	undefined field_0x1b09;
	undefined field_0x1b0a;
	undefined field_0x1b0b;
	undefined field_0x1b0c;
	undefined field_0x1b0d;
	undefined field_0x1b0e;
	undefined field_0x1b0f;
	undefined field_0x1b10;
	undefined field_0x1b11;
	undefined field_0x1b12;
	undefined field_0x1b13;
	undefined field_0x1b14;
	undefined field_0x1b15;
	undefined field_0x1b16;
	undefined field_0x1b17;
	undefined field_0x1b18;
	undefined field_0x1b19;
	undefined field_0x1b1a;
	undefined field_0x1b1b;
	undefined field_0x1b1c;
	undefined field_0x1b1d;
	undefined field_0x1b1e;
	undefined field_0x1b1f;
	undefined field_0x1b20;
	undefined field_0x1b21;
	undefined field_0x1b22;
	undefined field_0x1b23;
	undefined field_0x1b24;
	undefined field_0x1b25;
	undefined field_0x1b26;
	undefined field_0x1b27;
	undefined field_0x1b28;
	undefined field_0x1b29;
	undefined field_0x1b2a;
	undefined field_0x1b2b;
	undefined field_0x1b2c;
	undefined field_0x1b2d;
	undefined field_0x1b2e;
	undefined field_0x1b2f;
	undefined field_0x1b30;
	undefined field_0x1b31;
	undefined field_0x1b32;
	undefined field_0x1b33;
	undefined field_0x1b34;
	undefined field_0x1b35;
	undefined field_0x1b36;
	undefined field_0x1b37;
	undefined field_0x1b38;
	undefined field_0x1b39;
	undefined field_0x1b3a;
	undefined field_0x1b3b;
	undefined field_0x1b3c;
	undefined field_0x1b3d;
	undefined field_0x1b3e;
	undefined field_0x1b3f;
	undefined field_0x1b40;
	undefined field_0x1b41;
	undefined field_0x1b42;
	undefined field_0x1b43;
	undefined field_0x1b44;
	undefined field_0x1b45;
	undefined field_0x1b46;
	undefined field_0x1b47;
	undefined field_0x1b48;
	undefined field_0x1b49;
	undefined field_0x1b4a;
	undefined field_0x1b4b;
	undefined field_0x1b4c;
	undefined field_0x1b4d;
	undefined field_0x1b4e;
	undefined field_0x1b4f;
	undefined field_0x1b50;
	undefined field_0x1b51;
	undefined field_0x1b52;
	undefined field_0x1b53;
	undefined field_0x1b54;
	undefined field_0x1b55;
	undefined field_0x1b56;
	undefined field_0x1b57;
	undefined field_0x1b58;
	undefined field_0x1b59;
	undefined field_0x1b5a;
	undefined field_0x1b5b;
	undefined field_0x1b5c;
	undefined field_0x1b5d;
	undefined field_0x1b5e;
	undefined field_0x1b5f;
	undefined field_0x1b60;
	undefined field_0x1b61;
	undefined field_0x1b62;
	undefined field_0x1b63;
	undefined field_0x1b64;
	undefined field_0x1b65;
	undefined field_0x1b66;
	undefined field_0x1b67;
	undefined field_0x1b68;
	undefined field_0x1b69;
	undefined field_0x1b6a;
	undefined field_0x1b6b;
	undefined field_0x1b6c;
	undefined field_0x1b6d;
	undefined field_0x1b6e;
	undefined field_0x1b6f;
	undefined field_0x1b70;
	undefined field_0x1b71;
	undefined field_0x1b72;
	undefined field_0x1b73;
	undefined field_0x1b74;
	undefined field_0x1b75;
	undefined field_0x1b76;
	undefined field_0x1b77;
	undefined field_0x1b78;
	undefined field_0x1b79;
	undefined field_0x1b7a;
	undefined field_0x1b7b;
	undefined field_0x1b7c;
	undefined field_0x1b7d;
	undefined field_0x1b7e;
	undefined field_0x1b7f;
	undefined field_0x1b80;
	undefined field_0x1b81;
	undefined field_0x1b82;
	undefined field_0x1b83;
	undefined field_0x1b84;
	undefined field_0x1b85;
	undefined field_0x1b86;
	undefined field_0x1b87;
	undefined field_0x1b88;
	undefined field_0x1b89;
	undefined field_0x1b8a;
	undefined field_0x1b8b;
	undefined field_0x1b8c;
	undefined field_0x1b8d;
	undefined field_0x1b8e;
	undefined field_0x1b8f;
	undefined field_0x1b90;
	undefined field_0x1b91;
	undefined field_0x1b92;
	undefined field_0x1b93;
	undefined field_0x1b94;
	undefined field_0x1b95;
	undefined field_0x1b96;
	undefined field_0x1b97;
	undefined field_0x1b98;
	undefined field_0x1b99;
	undefined field_0x1b9a;
	undefined field_0x1b9b;
	undefined field_0x1b9c;
	undefined field_0x1b9d;
	undefined field_0x1b9e;
	undefined field_0x1b9f;
	undefined field_0x1ba0;
	undefined field_0x1ba1;
	undefined field_0x1ba2;
	undefined field_0x1ba3;
	undefined field_0x1ba4;
	undefined field_0x1ba5;
	undefined field_0x1ba6;
	undefined field_0x1ba7;
	undefined field_0x1ba8;
	undefined field_0x1ba9;
	undefined field_0x1baa;
	undefined field_0x1bab;
	undefined field_0x1bac;
	undefined field_0x1bad;
	undefined field_0x1bae;
	undefined field_0x1baf;
	undefined field_0x1bb0;
	undefined field_0x1bb1;
	undefined field_0x1bb2;
	undefined field_0x1bb3;
	undefined field_0x1bb4;
	undefined field_0x1bb5;
	undefined field_0x1bb6;
	undefined field_0x1bb7;
	undefined field_0x1bb8;
	undefined field_0x1bb9;
	undefined field_0x1bba;
	undefined field_0x1bbb;
	undefined field_0x1bbc;
	undefined field_0x1bbd;
	undefined field_0x1bbe;
	undefined field_0x1bbf;
	undefined field_0x1bc0;
	undefined field_0x1bc1;
	undefined field_0x1bc2;
	undefined field_0x1bc3;
	undefined field_0x1bc4;
	undefined field_0x1bc5;
	undefined field_0x1bc6;
	undefined field_0x1bc7;
	undefined field_0x1bc8;
	undefined field_0x1bc9;
	undefined field_0x1bca;
	undefined field_0x1bcb;
	undefined field_0x1bcc;
	undefined field_0x1bcd;
	undefined field_0x1bce;
	undefined field_0x1bcf;
	undefined field_0x1bd0;
	undefined field_0x1bd1;
	undefined field_0x1bd2;
	undefined field_0x1bd3;
	undefined field_0x1bd4;
	undefined field_0x1bd5;
	undefined field_0x1bd6;
	undefined field_0x1bd7;
	undefined field_0x1bd8;
	undefined field_0x1bd9;
	undefined field_0x1bda;
	undefined field_0x1bdb;
	undefined field_0x1bdc;
	undefined field_0x1bdd;
	undefined field_0x1bde;
	undefined field_0x1bdf;
	undefined field_0x1be0;
	undefined field_0x1be1;
	undefined field_0x1be2;
	undefined field_0x1be3;
	undefined field_0x1be4;
	undefined field_0x1be5;
	undefined field_0x1be6;
	undefined field_0x1be7;
	undefined field_0x1be8;
	undefined field_0x1be9;
	undefined field_0x1bea;
	undefined field_0x1beb;
	undefined field_0x1bec;
	undefined field_0x1bed;
	undefined field_0x1bee;
	undefined field_0x1bef;
	undefined field_0x1bf0;
	undefined field_0x1bf1;
	undefined field_0x1bf2;
	undefined field_0x1bf3;
	undefined field_0x1bf4;
	undefined field_0x1bf5;
	undefined field_0x1bf6;
	undefined field_0x1bf7;
	undefined field_0x1bf8;
	undefined field_0x1bf9;
	undefined field_0x1bfa;
	undefined field_0x1bfb;
	undefined field_0x1bfc;
	undefined field_0x1bfd;
	undefined field_0x1bfe;
	undefined field_0x1bff;
	undefined field_0x1c00;
	undefined field_0x1c01;
	undefined field_0x1c02;
	undefined field_0x1c03;
	undefined field_0x1c04;
	undefined field_0x1c05;
	undefined field_0x1c06;
	undefined field_0x1c07;
	undefined field_0x1c08;
	undefined field_0x1c09;
	undefined field_0x1c0a;
	undefined field_0x1c0b;
	undefined field_0x1c0c;
	undefined field_0x1c0d;
	undefined field_0x1c0e;
	undefined field_0x1c0f;
	undefined field_0x1c10;
	undefined field_0x1c11;
	undefined field_0x1c12;
	undefined field_0x1c13;
	undefined field_0x1c14;
	undefined field_0x1c15;
	undefined field_0x1c16;
	undefined field_0x1c17;
	undefined field_0x1c18;
	undefined field_0x1c19;
	undefined field_0x1c1a;
	undefined field_0x1c1b;
	undefined field_0x1c1c;
	undefined field_0x1c1d;
	undefined field_0x1c1e;
	undefined field_0x1c1f;
	undefined field_0x1c20;
	undefined field_0x1c21;
	undefined field_0x1c22;
	undefined field_0x1c23;
	undefined field_0x1c24;
	undefined field_0x1c25;
	undefined field_0x1c26;
	undefined field_0x1c27;
	undefined field_0x1c28;
	undefined field_0x1c29;
	undefined field_0x1c2a;
	undefined field_0x1c2b;
	undefined field_0x1c2c;
	undefined field_0x1c2d;
	undefined field_0x1c2e;
	undefined field_0x1c2f;
	undefined field_0x1c30;
	undefined field_0x1c31;
	undefined field_0x1c32;
	undefined field_0x1c33;
	undefined field_0x1c34;
	undefined field_0x1c35;
	undefined field_0x1c36;
	undefined field_0x1c37;
	undefined field_0x1c38;
	undefined field_0x1c39;
	undefined field_0x1c3a;
	undefined field_0x1c3b;
	undefined field_0x1c3c;
	undefined field_0x1c3d;
	undefined field_0x1c3e;
	undefined field_0x1c3f;
	undefined field_0x1c40;
	undefined field_0x1c41;
	undefined field_0x1c42;
	undefined field_0x1c43;
	undefined field_0x1c44;
	undefined field_0x1c45;
	undefined field_0x1c46;
	undefined field_0x1c47;
	undefined field_0x1c48;
	undefined field_0x1c49;
	undefined field_0x1c4a;
	undefined field_0x1c4b;
	undefined field_0x1c4c;
	undefined field_0x1c4d;
	undefined field_0x1c4e;
	undefined field_0x1c4f;
	undefined field_0x1c50;
	undefined field_0x1c51;
	undefined field_0x1c52;
	undefined field_0x1c53;
	undefined field_0x1c54;
	undefined field_0x1c55;
	undefined field_0x1c56;
	undefined field_0x1c57;
	undefined field_0x1c58;
	undefined field_0x1c59;
	undefined field_0x1c5a;
	undefined field_0x1c5b;
	undefined field_0x1c5c;
	undefined field_0x1c5d;
	undefined field_0x1c5e;
	undefined field_0x1c5f;
	undefined field_0x1c60;
	undefined field_0x1c61;
	undefined field_0x1c62;
	undefined field_0x1c63;
	undefined field_0x1c64;
	undefined field_0x1c65;
	undefined field_0x1c66;
	undefined field_0x1c67;
	undefined field_0x1c68;
	undefined field_0x1c69;
	undefined field_0x1c6a;
	undefined field_0x1c6b;
	undefined field_0x1c6c;
	undefined field_0x1c6d;
	undefined field_0x1c6e;
	undefined field_0x1c6f;
	undefined field_0x1c70;
	undefined field_0x1c71;
	undefined field_0x1c72;
	undefined field_0x1c73;
	undefined field_0x1c74;
	undefined field_0x1c75;
	undefined field_0x1c76;
	undefined field_0x1c77;
	undefined field_0x1c78;
	undefined field_0x1c79;
	undefined field_0x1c7a;
	undefined field_0x1c7b;
	undefined field_0x1c7c;
	undefined field_0x1c7d;
	undefined field_0x1c7e;
	undefined field_0x1c7f;
	undefined field_0x1c80;
	undefined field_0x1c81;
	undefined field_0x1c82;
	undefined field_0x1c83;
	undefined field_0x1c84;
	undefined field_0x1c85;
	undefined field_0x1c86;
	undefined field_0x1c87;
	undefined field_0x1c88;
	undefined field_0x1c89;
	undefined field_0x1c8a;
	undefined field_0x1c8b;
	undefined field_0x1c8c;
	undefined field_0x1c8d;
	undefined field_0x1c8e;
	undefined field_0x1c8f;
	undefined field_0x1c90;
	undefined field_0x1c91;
	undefined field_0x1c92;
	undefined field_0x1c93;
	undefined field_0x1c94;
	undefined field_0x1c95;
	undefined field_0x1c96;
	undefined field_0x1c97;
	undefined field_0x1c98;
	undefined field_0x1c99;
	undefined field_0x1c9a;
	undefined field_0x1c9b;
	undefined field_0x1c9c;
	undefined field_0x1c9d;
	undefined field_0x1c9e;
	undefined field_0x1c9f;
	undefined field_0x1ca0;
	undefined field_0x1ca1;
	undefined field_0x1ca2;
	undefined field_0x1ca3;
	undefined field_0x1ca4;
	undefined field_0x1ca5;
	undefined field_0x1ca6;
	undefined field_0x1ca7;
	undefined field_0x1ca8;
	undefined field_0x1ca9;
	undefined field_0x1caa;
	undefined field_0x1cab;
	undefined field_0x1cac;
	undefined field_0x1cad;
	undefined field_0x1cae;
	undefined field_0x1caf;
	undefined field_0x1cb0;
	undefined field_0x1cb1;
	undefined field_0x1cb2;
	undefined field_0x1cb3;
	undefined field_0x1cb4;
	undefined field_0x1cb5;
	undefined field_0x1cb6;
	undefined field_0x1cb7;
	undefined field_0x1cb8;
	undefined field_0x1cb9;
	undefined field_0x1cba;
	undefined field_0x1cbb;
	undefined field_0x1cbc;
	undefined field_0x1cbd;
	undefined field_0x1cbe;
	undefined field_0x1cbf;
	undefined field_0x1cc0;
	undefined field_0x1cc1;
	undefined field_0x1cc2;
	undefined field_0x1cc3;
	undefined field_0x1cc4;
	undefined field_0x1cc5;
	undefined field_0x1cc6;
	undefined field_0x1cc7;
	undefined field_0x1cc8;
	undefined field_0x1cc9;
	undefined field_0x1cca;
	undefined field_0x1ccb;
	undefined field_0x1ccc;
	undefined field_0x1ccd;
	undefined field_0x1cce;
	undefined field_0x1ccf;
	undefined field_0x1cd0;
	undefined field_0x1cd1;
	undefined field_0x1cd2;
	undefined field_0x1cd3;
	undefined field_0x1cd4;
	undefined field_0x1cd5;
	undefined field_0x1cd6;
	undefined field_0x1cd7;
	undefined field_0x1cd8;
	undefined field_0x1cd9;
	undefined field_0x1cda;
	undefined field_0x1cdb;
	undefined field_0x1cdc;
	undefined field_0x1cdd;
	undefined field_0x1cde;
	undefined field_0x1cdf;
	undefined field_0x1ce0;
	undefined field_0x1ce1;
	undefined field_0x1ce2;
	undefined field_0x1ce3;
	undefined field_0x1ce4;
	undefined field_0x1ce5;
	undefined field_0x1ce6;
	undefined field_0x1ce7;
	undefined field_0x1ce8;
	undefined field_0x1ce9;
	undefined field_0x1cea;
	undefined field_0x1ceb;
	undefined field_0x1cec;
	undefined field_0x1ced;
	undefined field_0x1cee;
	undefined field_0x1cef;
	undefined field_0x1cf0;
	undefined field_0x1cf1;
	undefined field_0x1cf2;
	undefined field_0x1cf3;
	undefined field_0x1cf4;
	undefined field_0x1cf5;
	undefined field_0x1cf6;
	undefined field_0x1cf7;
	undefined field_0x1cf8;
	undefined field_0x1cf9;
	undefined field_0x1cfa;
	undefined field_0x1cfb;
	undefined field_0x1cfc;
	undefined field_0x1cfd;
	undefined field_0x1cfe;
	undefined field_0x1cff;
	undefined field_0x1d00;
	undefined field_0x1d01;
	undefined field_0x1d02;
	undefined field_0x1d03;
	undefined field_0x1d04;
	undefined field_0x1d05;
	undefined field_0x1d06;
	undefined field_0x1d07;
	undefined field_0x1d08;
	undefined field_0x1d09;
	undefined field_0x1d0a;
	undefined field_0x1d0b;
	undefined field_0x1d0c;
	undefined field_0x1d0d;
	undefined field_0x1d0e;
	undefined field_0x1d0f;
	undefined field_0x1d10;
	undefined field_0x1d11;
	undefined field_0x1d12;
	undefined field_0x1d13;
	undefined field_0x1d14;
	undefined field_0x1d15;
	undefined field_0x1d16;
	undefined field_0x1d17;
	undefined field_0x1d18;
	undefined field_0x1d19;
	undefined field_0x1d1a;
	undefined field_0x1d1b;
	undefined field_0x1d1c;
	undefined field_0x1d1d;
	undefined field_0x1d1e;
	undefined field_0x1d1f;
	undefined field_0x1d20;
	undefined field_0x1d21;
	undefined field_0x1d22;
	undefined field_0x1d23;
	undefined field_0x1d24;
	undefined field_0x1d25;
	undefined field_0x1d26;
	undefined field_0x1d27;
	undefined field_0x1d28;
	undefined field_0x1d29;
	undefined field_0x1d2a;
	undefined field_0x1d2b;
	undefined field_0x1d2c;
	undefined field_0x1d2d;
	undefined field_0x1d2e;
	undefined field_0x1d2f;
	undefined field_0x1d30;
	undefined field_0x1d31;
	undefined field_0x1d32;
	undefined field_0x1d33;
	undefined field_0x1d34;
	undefined field_0x1d35;
	undefined field_0x1d36;
	undefined field_0x1d37;
	undefined field_0x1d38;
	undefined field_0x1d39;
	undefined field_0x1d3a;
	undefined field_0x1d3b;
	undefined field_0x1d3c;
	undefined field_0x1d3d;
	undefined field_0x1d3e;
	undefined field_0x1d3f;
	undefined field_0x1d40;
	undefined field_0x1d41;
	undefined field_0x1d42;
	undefined field_0x1d43;
	undefined field_0x1d44;
	undefined field_0x1d45;
	undefined field_0x1d46;
	undefined field_0x1d47;
	undefined field_0x1d48;
	undefined field_0x1d49;
	undefined field_0x1d4a;
	undefined field_0x1d4b;
	undefined field_0x1d4c;
	undefined field_0x1d4d;
	undefined field_0x1d4e;
	undefined field_0x1d4f;
	undefined field_0x1d50;
	undefined field_0x1d51;
	undefined field_0x1d52;
	undefined field_0x1d53;
	undefined field_0x1d54;
	undefined field_0x1d55;
	undefined field_0x1d56;
	undefined field_0x1d57;
	undefined field_0x1d58;
	undefined field_0x1d59;
	undefined field_0x1d5a;
	undefined field_0x1d5b;
	undefined field_0x1d5c;
	undefined field_0x1d5d;
	undefined field_0x1d5e;
	undefined field_0x1d5f;
	undefined field_0x1d60;
	undefined field_0x1d61;
	undefined field_0x1d62;
	undefined field_0x1d63;
	undefined field_0x1d64;
	undefined field_0x1d65;
	undefined field_0x1d66;
	undefined field_0x1d67;
	undefined field_0x1d68;
	undefined field_0x1d69;
	undefined field_0x1d6a;
	undefined field_0x1d6b;
	undefined field_0x1d6c;
	undefined field_0x1d6d;
	undefined field_0x1d6e;
	undefined field_0x1d6f;
	undefined field_0x1d70;
	undefined field_0x1d71;
	undefined field_0x1d72;
	undefined field_0x1d73;
	undefined field_0x1d74;
	undefined field_0x1d75;
	undefined field_0x1d76;
	undefined field_0x1d77;
	undefined field_0x1d78;
	undefined field_0x1d79;
	undefined field_0x1d7a;
	undefined field_0x1d7b;
	undefined field_0x1d7c;
	undefined field_0x1d7d;
	undefined field_0x1d7e;
	undefined field_0x1d7f;
	undefined field_0x1d80;
	undefined field_0x1d81;
	undefined field_0x1d82;
	undefined field_0x1d83;
	undefined field_0x1d84;
	undefined field_0x1d85;
	undefined field_0x1d86;
	undefined field_0x1d87;
	undefined field_0x1d88;
	undefined field_0x1d89;
	undefined field_0x1d8a;
	undefined field_0x1d8b;
	undefined field_0x1d8c;
	undefined field_0x1d8d;
	undefined field_0x1d8e;
	undefined field_0x1d8f;
	undefined field_0x1d90;
	undefined field_0x1d91;
	undefined field_0x1d92;
	undefined field_0x1d93;
	undefined field_0x1d94;
	undefined field_0x1d95;
	undefined field_0x1d96;
	undefined field_0x1d97;
	undefined field_0x1d98;
	undefined field_0x1d99;
	undefined field_0x1d9a;
	undefined field_0x1d9b;
	undefined field_0x1d9c;
	undefined field_0x1d9d;
	undefined field_0x1d9e;
	undefined field_0x1d9f;
	undefined field_0x1da0;
	undefined field_0x1da1;
	undefined field_0x1da2;
	undefined field_0x1da3;
	undefined field_0x1da4;
	undefined field_0x1da5;
	undefined field_0x1da6;
	undefined field_0x1da7;
	undefined field_0x1da8;
	undefined field_0x1da9;
	undefined field_0x1daa;
	undefined field_0x1dab;
	undefined field_0x1dac;
	undefined field_0x1dad;
	undefined field_0x1dae;
	undefined field_0x1daf;
	undefined field_0x1db0;
	undefined field_0x1db1;
	undefined field_0x1db2;
	undefined field_0x1db3;
	undefined field_0x1db4;
	undefined field_0x1db5;
	undefined field_0x1db6;
	undefined field_0x1db7;
	undefined field_0x1db8;
	undefined field_0x1db9;
	undefined field_0x1dba;
	undefined field_0x1dbb;
	undefined field_0x1dbc;
	undefined field_0x1dbd;
	undefined field_0x1dbe;
	undefined field_0x1dbf;
	undefined field_0x1dc0;
	undefined field_0x1dc1;
	undefined field_0x1dc2;
	undefined field_0x1dc3;
	undefined field_0x1dc4;
	undefined field_0x1dc5;
	undefined field_0x1dc6;
	undefined field_0x1dc7;
	undefined field_0x1dc8;
	undefined field_0x1dc9;
	undefined field_0x1dca;
	undefined field_0x1dcb;
	undefined field_0x1dcc;
	undefined field_0x1dcd;
	undefined field_0x1dce;
	undefined field_0x1dcf;
	undefined field_0x1dd0;
	undefined field_0x1dd1;
	undefined field_0x1dd2;
	undefined field_0x1dd3;
	undefined field_0x1dd4;
	undefined field_0x1dd5;
	undefined field_0x1dd6;
	undefined field_0x1dd7;
	undefined field_0x1dd8;
	undefined field_0x1dd9;
	undefined field_0x1dda;
	undefined field_0x1ddb;
	undefined field_0x1ddc;
	undefined field_0x1ddd;
	undefined field_0x1dde;
	undefined field_0x1ddf;
	undefined field_0x1de0;
	undefined field_0x1de1;
	undefined field_0x1de2;
	undefined field_0x1de3;
	undefined field_0x1de4;
	undefined field_0x1de5;
	undefined field_0x1de6;
	undefined field_0x1de7;
	undefined field_0x1de8;
	undefined field_0x1de9;
	undefined field_0x1dea;
	undefined field_0x1deb;
	undefined field_0x1dec;
	undefined field_0x1ded;
	undefined field_0x1dee;
	undefined field_0x1def;
	undefined field_0x1df0;
	undefined field_0x1df1;
	undefined field_0x1df2;
	undefined field_0x1df3;
	undefined field_0x1df4;
	undefined field_0x1df5;
	undefined field_0x1df6;
	undefined field_0x1df7;
	undefined field_0x1df8;
	undefined field_0x1df9;
	undefined field_0x1dfa;
	undefined field_0x1dfb;
	undefined field_0x1dfc;
	undefined field_0x1dfd;
	undefined field_0x1dfe;
	undefined field_0x1dff;
	undefined field_0x1e00;
	undefined field_0x1e01;
	undefined field_0x1e02;
	undefined field_0x1e03;
	undefined field_0x1e04;
	undefined field_0x1e05;
	undefined field_0x1e06;
	undefined field_0x1e07;
	undefined field_0x1e08;
	undefined field_0x1e09;
	undefined field_0x1e0a;
	undefined field_0x1e0b;
	undefined field_0x1e0c;
	undefined field_0x1e0d;
	undefined field_0x1e0e;
	undefined field_0x1e0f;
	undefined field_0x1e10;
	undefined field_0x1e11;
	undefined field_0x1e12;
	undefined field_0x1e13;
	undefined field_0x1e14;
	undefined field_0x1e15;
	undefined field_0x1e16;
	undefined field_0x1e17;
	undefined field_0x1e18;
	undefined field_0x1e19;
	undefined field_0x1e1a;
	undefined field_0x1e1b;
	undefined field_0x1e1c;
	undefined field_0x1e1d;
	undefined field_0x1e1e;
	undefined field_0x1e1f;
	undefined field_0x1e20;
	undefined field_0x1e21;
	undefined field_0x1e22;
	undefined field_0x1e23;
	undefined field_0x1e24;
	undefined field_0x1e25;
	undefined field_0x1e26;
	undefined field_0x1e27;
	undefined field_0x1e28;
	undefined field_0x1e29;
	undefined field_0x1e2a;
	undefined field_0x1e2b;
	undefined field_0x1e2c;
	undefined field_0x1e2d;
	undefined field_0x1e2e;
	undefined field_0x1e2f;
	undefined field_0x1e30;
	undefined field_0x1e31;
	undefined field_0x1e32;
	undefined field_0x1e33;
	undefined field_0x1e34;
	undefined field_0x1e35;
	undefined field_0x1e36;
	undefined field_0x1e37;
	undefined field_0x1e38;
	undefined field_0x1e39;
	undefined field_0x1e3a;
	undefined field_0x1e3b;
	undefined field_0x1e3c;
	undefined field_0x1e3d;
	undefined field_0x1e3e;
	undefined field_0x1e3f;
	undefined field_0x1e40;
	undefined field_0x1e41;
	undefined field_0x1e42;
	undefined field_0x1e43;
	undefined field_0x1e44;
	undefined field_0x1e45;
	undefined field_0x1e46;
	undefined field_0x1e47;
	undefined field_0x1e48;
	undefined field_0x1e49;
	undefined field_0x1e4a;
	undefined field_0x1e4b;
	undefined field_0x1e4c;
	undefined field_0x1e4d;
	undefined field_0x1e4e;
	undefined field_0x1e4f;
	undefined field_0x1e50;
	undefined field_0x1e51;
	undefined field_0x1e52;
	undefined field_0x1e53;
	undefined field_0x1e54;
	undefined field_0x1e55;
	undefined field_0x1e56;
	undefined field_0x1e57;
	undefined field_0x1e58;
	undefined field_0x1e59;
	undefined field_0x1e5a;
	undefined field_0x1e5b;
	undefined field_0x1e5c;
	undefined field_0x1e5d;
	undefined field_0x1e5e;
	undefined field_0x1e5f;
	undefined field_0x1e60;
	undefined field_0x1e61;
	undefined field_0x1e62;
	undefined field_0x1e63;
	undefined field_0x1e64;
	undefined field_0x1e65;
	undefined field_0x1e66;
	undefined field_0x1e67;
	undefined field_0x1e68;
	undefined field_0x1e69;
	undefined field_0x1e6a;
	undefined field_0x1e6b;
	undefined field_0x1e6c;
	undefined field_0x1e6d;
	undefined field_0x1e6e;
	undefined field_0x1e6f;
	undefined field_0x1e70;
	undefined field_0x1e71;
	undefined field_0x1e72;
	undefined field_0x1e73;
	undefined field_0x1e74;
	undefined field_0x1e75;
	undefined field_0x1e76;
	undefined field_0x1e77;
	undefined field_0x1e78;
	undefined field_0x1e79;
	undefined field_0x1e7a;
	undefined field_0x1e7b;
	undefined field_0x1e7c;
	undefined field_0x1e7d;
	undefined field_0x1e7e;
	undefined field_0x1e7f;
	undefined field_0x1e80;
	undefined field_0x1e81;
	undefined field_0x1e82;
	undefined field_0x1e83;
	undefined field_0x1e84;
	undefined field_0x1e85;
	undefined field_0x1e86;
	undefined field_0x1e87;
	undefined field_0x1e88;
	undefined field_0x1e89;
	undefined field_0x1e8a;
	undefined field_0x1e8b;
	undefined field_0x1e8c;
	undefined field_0x1e8d;
	undefined field_0x1e8e;
	undefined field_0x1e8f;
	undefined field_0x1e90;
	undefined field_0x1e91;
	undefined field_0x1e92;
	undefined field_0x1e93;
	undefined field_0x1e94;
	undefined field_0x1e95;
	undefined field_0x1e96;
	undefined field_0x1e97;
	undefined field_0x1e98;
	undefined field_0x1e99;
	undefined field_0x1e9a;
	undefined field_0x1e9b;
	undefined field_0x1e9c;
	undefined field_0x1e9d;
	undefined field_0x1e9e;
	undefined field_0x1e9f;
	undefined field_0x1ea0;
	undefined field_0x1ea1;
	undefined field_0x1ea2;
	undefined field_0x1ea3;
	undefined field_0x1ea4;
	undefined field_0x1ea5;
	undefined field_0x1ea6;
	undefined field_0x1ea7;
	undefined field_0x1ea8;
	undefined field_0x1ea9;
	undefined field_0x1eaa;
	undefined field_0x1eab;
	undefined field_0x1eac;
	undefined field_0x1ead;
	undefined field_0x1eae;
	undefined field_0x1eaf;
	undefined field_0x1eb0;
	undefined field_0x1eb1;
	undefined field_0x1eb2;
	undefined field_0x1eb3;
	undefined field_0x1eb4;
	undefined field_0x1eb5;
	undefined field_0x1eb6;
	undefined field_0x1eb7;
	undefined field_0x1eb8;
	undefined field_0x1eb9;
	undefined field_0x1eba;
	undefined field_0x1ebb;
	undefined field_0x1ebc;
	undefined field_0x1ebd;
	undefined field_0x1ebe;
	undefined field_0x1ebf;
	undefined field_0x1ec0;
	undefined field_0x1ec1;
	undefined field_0x1ec2;
	undefined field_0x1ec3;
	undefined field_0x1ec4;
	undefined field_0x1ec5;
	undefined field_0x1ec6;
	undefined field_0x1ec7;
	undefined field_0x1ec8;
	undefined field_0x1ec9;
	undefined field_0x1eca;
	undefined field_0x1ecb;
	undefined field_0x1ecc;
	undefined field_0x1ecd;
	undefined field_0x1ece;
	undefined field_0x1ecf;
	undefined field_0x1ed0;
	undefined field_0x1ed1;
	undefined field_0x1ed2;
	undefined field_0x1ed3;
	undefined field_0x1ed4;
	undefined field_0x1ed5;
	undefined field_0x1ed6;
	undefined field_0x1ed7;
	undefined field_0x1ed8;
	undefined field_0x1ed9;
	undefined field_0x1eda;
	undefined field_0x1edb;
	undefined field_0x1edc;
	undefined field_0x1edd;
	undefined field_0x1ede;
	undefined field_0x1edf;
	undefined field_0x1ee0;
	undefined field_0x1ee1;
	undefined field_0x1ee2;
	undefined field_0x1ee3;
	undefined field_0x1ee4;
	undefined field_0x1ee5;
	undefined field_0x1ee6;
	undefined field_0x1ee7;
	undefined field_0x1ee8;
	undefined field_0x1ee9;
	undefined field_0x1eea;
	undefined field_0x1eeb;
	undefined field_0x1eec;
	undefined field_0x1eed;
	undefined field_0x1eee;
	undefined field_0x1eef;
	undefined field_0x1ef0;
	undefined field_0x1ef1;
	undefined field_0x1ef2;
	undefined field_0x1ef3;
	undefined field_0x1ef4;
	undefined field_0x1ef5;
	undefined field_0x1ef6;
	undefined field_0x1ef7;
	undefined field_0x1ef8;
	undefined field_0x1ef9;
	undefined field_0x1efa;
	undefined field_0x1efb;
	undefined field_0x1efc;
	undefined field_0x1efd;
	undefined field_0x1efe;
	undefined field_0x1eff;
	undefined field_0x1f00;
	undefined field_0x1f01;
	undefined field_0x1f02;
	undefined field_0x1f03;
	undefined field_0x1f04;
	undefined field_0x1f05;
	undefined field_0x1f06;
	undefined field_0x1f07;
	undefined field_0x1f08;
	undefined field_0x1f09;
	undefined field_0x1f0a;
	undefined field_0x1f0b;
	undefined field_0x1f0c;
	undefined field_0x1f0d;
	undefined field_0x1f0e;
	undefined field_0x1f0f;
	undefined field_0x1f10;
	undefined field_0x1f11;
	undefined field_0x1f12;
	undefined field_0x1f13;
	undefined field_0x1f14;
	undefined field_0x1f15;
	undefined field_0x1f16;
	undefined field_0x1f17;
	undefined field_0x1f18;
	undefined field_0x1f19;
	undefined field_0x1f1a;
	undefined field_0x1f1b;
	undefined field_0x1f1c;
	undefined field_0x1f1d;
	undefined field_0x1f1e;
	undefined field_0x1f1f;
	undefined field_0x1f20;
	undefined field_0x1f21;
	undefined field_0x1f22;
	undefined field_0x1f23;
	undefined field_0x1f24;
	undefined field_0x1f25;
	undefined field_0x1f26;
	undefined field_0x1f27;
	undefined field_0x1f28;
	undefined field_0x1f29;
	undefined field_0x1f2a;
	undefined field_0x1f2b;
	undefined field_0x1f2c;
	undefined field_0x1f2d;
	undefined field_0x1f2e;
	undefined field_0x1f2f;
	undefined field_0x1f30;
	undefined field_0x1f31;
	undefined field_0x1f32;
	undefined field_0x1f33;
	undefined field_0x1f34;
	undefined field_0x1f35;
	undefined field_0x1f36;
	undefined field_0x1f37;
	undefined field_0x1f38;
	undefined field_0x1f39;
	undefined field_0x1f3a;
	undefined field_0x1f3b;
	undefined field_0x1f3c;
	undefined field_0x1f3d;
	undefined field_0x1f3e;
	undefined field_0x1f3f;
	undefined field_0x1f40;
	undefined field_0x1f41;
	undefined field_0x1f42;
	undefined field_0x1f43;
	undefined field_0x1f44;
	undefined field_0x1f45;
	undefined field_0x1f46;
	undefined field_0x1f47;
	undefined field_0x1f48;
	undefined field_0x1f49;
	undefined field_0x1f4a;
	undefined field_0x1f4b;
	undefined field_0x1f4c;
	undefined field_0x1f4d;
	undefined field_0x1f4e;
	undefined field_0x1f4f;
	undefined field_0x1f50;
	undefined field_0x1f51;
	undefined field_0x1f52;
	undefined field_0x1f53;
	undefined field_0x1f54;
	undefined field_0x1f55;
	undefined field_0x1f56;
	undefined field_0x1f57;
	undefined field_0x1f58;
	undefined field_0x1f59;
	undefined field_0x1f5a;
	undefined field_0x1f5b;
	undefined field_0x1f5c;
	undefined field_0x1f5d;
	undefined field_0x1f5e;
	undefined field_0x1f5f;
	undefined field_0x1f60;
	undefined field_0x1f61;
	undefined field_0x1f62;
	undefined field_0x1f63;
	undefined field_0x1f64;
	undefined field_0x1f65;
	undefined field_0x1f66;
	undefined field_0x1f67;
	undefined field_0x1f68;
	undefined field_0x1f69;
	undefined field_0x1f6a;
	undefined field_0x1f6b;
	undefined field_0x1f6c;
	undefined field_0x1f6d;
	undefined field_0x1f6e;
	undefined field_0x1f6f;
	undefined field_0x1f70;
	undefined field_0x1f71;
	undefined field_0x1f72;
	undefined field_0x1f73;
	undefined field_0x1f74;
	undefined field_0x1f75;
	undefined field_0x1f76;
	undefined field_0x1f77;
	undefined field_0x1f78;
	undefined field_0x1f79;
	undefined field_0x1f7a;
	undefined field_0x1f7b;
	undefined field_0x1f7c;
	undefined field_0x1f7d;
	undefined field_0x1f7e;
	undefined field_0x1f7f;
	undefined field_0x1f80;
	undefined field_0x1f81;
	undefined field_0x1f82;
	undefined field_0x1f83;
	undefined field_0x1f84;
	undefined field_0x1f85;
	undefined field_0x1f86;
	undefined field_0x1f87;
	undefined field_0x1f88;
	undefined field_0x1f89;
	undefined field_0x1f8a;
	undefined field_0x1f8b;
	undefined field_0x1f8c;
	undefined field_0x1f8d;
	undefined field_0x1f8e;
	undefined field_0x1f8f;
	undefined field_0x1f90;
	undefined field_0x1f91;
	undefined field_0x1f92;
	undefined field_0x1f93;
	undefined field_0x1f94;
	undefined field_0x1f95;
	undefined field_0x1f96;
	undefined field_0x1f97;
	undefined field_0x1f98;
	undefined field_0x1f99;
	undefined field_0x1f9a;
	undefined field_0x1f9b;
	undefined field_0x1f9c;
	undefined field_0x1f9d;
	undefined field_0x1f9e;
	undefined field_0x1f9f;
	undefined field_0x1fa0;
	undefined field_0x1fa1;
	undefined field_0x1fa2;
	undefined field_0x1fa3;
	undefined field_0x1fa4;
	undefined field_0x1fa5;
	undefined field_0x1fa6;
	undefined field_0x1fa7;
	undefined field_0x1fa8;
	undefined field_0x1fa9;
	undefined field_0x1faa;
	undefined field_0x1fab;
	undefined field_0x1fac;
	undefined field_0x1fad;
	undefined field_0x1fae;
	undefined field_0x1faf;
	undefined field_0x1fb0;
	undefined field_0x1fb1;
	undefined field_0x1fb2;
	undefined field_0x1fb3;
	undefined field_0x1fb4;
	undefined field_0x1fb5;
	undefined field_0x1fb6;
	undefined field_0x1fb7;
	undefined field_0x1fb8;
	undefined field_0x1fb9;
	undefined field_0x1fba;
	undefined field_0x1fbb;
	undefined field_0x1fbc;
	undefined field_0x1fbd;
	undefined field_0x1fbe;
	undefined field_0x1fbf;
	undefined field_0x1fc0;
	undefined field_0x1fc1;
	undefined field_0x1fc2;
	undefined field_0x1fc3;
	undefined field_0x1fc4;
	undefined field_0x1fc5;
	undefined field_0x1fc6;
	undefined field_0x1fc7;
	undefined field_0x1fc8;
	undefined field_0x1fc9;
	undefined field_0x1fca;
	undefined field_0x1fcb;
	undefined field_0x1fcc;
	undefined field_0x1fcd;
	undefined field_0x1fce;
	undefined field_0x1fcf;
	undefined field_0x1fd0;
	undefined field_0x1fd1;
	undefined field_0x1fd2;
	undefined field_0x1fd3;
	undefined field_0x1fd4;
	undefined field_0x1fd5;
	undefined field_0x1fd6;
	undefined field_0x1fd7;
	undefined field_0x1fd8;
	undefined field_0x1fd9;
	undefined field_0x1fda;
	undefined field_0x1fdb;
	undefined field_0x1fdc;
	undefined field_0x1fdd;
	undefined field_0x1fde;
	undefined field_0x1fdf;
	undefined field_0x1fe0;
	undefined field_0x1fe1;
	undefined field_0x1fe2;
	undefined field_0x1fe3;
	undefined field_0x1fe4;
	undefined field_0x1fe5;
	undefined field_0x1fe6;
	undefined field_0x1fe7;
	undefined field_0x1fe8;
	undefined field_0x1fe9;
	undefined field_0x1fea;
	undefined field_0x1feb;
	undefined field_0x1fec;
	undefined field_0x1fed;
	undefined field_0x1fee;
	undefined field_0x1fef;
	undefined field_0x1ff0;
	undefined field_0x1ff1;
	undefined field_0x1ff2;
	undefined field_0x1ff3;
	undefined field_0x1ff4;
	undefined field_0x1ff5;
	undefined field_0x1ff6;
	undefined field_0x1ff7;
	undefined field_0x1ff8;
	undefined field_0x1ff9;
	undefined field_0x1ffa;
	undefined field_0x1ffb;
	undefined field_0x1ffc;
	undefined field_0x1ffd;
	undefined field_0x1ffe;
	undefined field_0x1fff;
	undefined field_0x2000;
	undefined field_0x2001;
	undefined field_0x2002;
	undefined field_0x2003;
	undefined field_0x2004;
	undefined field_0x2005;
	undefined field_0x2006;
	undefined field_0x2007;
	undefined field_0x2008;
	undefined field_0x2009;
	undefined field_0x200a;
	undefined field_0x200b;
	undefined field_0x200c;
	undefined field_0x200d;
	undefined field_0x200e;
	undefined field_0x200f;
	undefined field_0x2010;
	undefined field_0x2011;
	undefined field_0x2012;
	undefined field_0x2013;
	undefined field_0x2014;
	undefined field_0x2015;
	undefined field_0x2016;
	undefined field_0x2017;
	undefined field_0x2018;
	undefined field_0x2019;
	undefined field_0x201a;
	undefined field_0x201b;
	undefined4 field_0x201c;
	undefined field_0x2020;
	undefined field_0x2021;
	undefined field_0x2022;
	undefined field_0x2023;
	undefined4 field_0x2024;
	undefined field_0x2028;
	undefined field_0x2029;
	undefined field_0x202a;
	undefined field_0x202b;
	undefined field_0x202c;
	undefined field_0x202d;
	undefined field_0x202e;
	undefined field_0x202f;
	undefined field_0x2030;
	undefined field_0x2031;
	undefined field_0x2032;
	undefined field_0x2033;
	pointer field_0x2034;
	uint field_0x2038;
	float10 field_0x203c;
	undefined field_0x2046;
	undefined field_0x2047;
	undefined field_0x2048;
	undefined field_0x2049;
	undefined field_0x204a;
	undefined field_0x204b;
	float field_0x204c;
	undefined field_0x2050;
	undefined field_0x2051;
	undefined field_0x2052;
	undefined field_0x2053;
	float field_0x2054;
	undefined field_0x2058;
	undefined field_0x2059;
	undefined field_0x205a;
	undefined field_0x205b;
	undefined field_0x205c;
	undefined field_0x205d;
	undefined field_0x205e;
	undefined field_0x205f;
	undefined field_0x2060;
	undefined field_0x2061;
	undefined field_0x2062;
	undefined field_0x2063;
	undefined field_0x2064;
	undefined field_0x2065;
	undefined field_0x2066;
	undefined field_0x2067;
	undefined field_0x2068;
	undefined field_0x2069;
	undefined field_0x206a;
	undefined field_0x206b;
	undefined field_0x206c;
	undefined field_0x206d;
	undefined field_0x206e;
	undefined field_0x206f;
	undefined field_0x2070;
	undefined field_0x2071;
	undefined field_0x2072;
	undefined field_0x2073;
	undefined field_0x2074;
	undefined field_0x2075;
	undefined field_0x2076;
	undefined field_0x2077;
	undefined field_0x2078;
	undefined field_0x2079;
	undefined field_0x207a;
	undefined field_0x207b;
	float field_0x207c;
	float field_0x2080;
	undefined field_0x2084;
	undefined field_0x2085;
	undefined field_0x2086;
	undefined field_0x2087;
	undefined field_0x2088;
	undefined field_0x2089;
	undefined field_0x208a;
	undefined field_0x208b;
	undefined field_0x208c;
	undefined field_0x208d;
	undefined field_0x208e;
	undefined field_0x208f;
	undefined field_0x2090;
	undefined field_0x2091;
	undefined field_0x2092;
	undefined field_0x2093;
	undefined field_0x2094;
	undefined field_0x2095;
	undefined field_0x2096;
	undefined field_0x2097;
	double field_0x2098;
	double field_0x20a0;
	double field_0x20a8;
	double field_0x20b0;
	double field_0x20b8;
	undefined field_0x20c0;
	undefined field_0x20c1;
	undefined field_0x20c2;
	undefined field_0x20c3;
	undefined field_0x20c4;
	undefined field_0x20c5;
	int field_0x20c6;
	pointer field_0x20ca;
	pointer field_0x20ce;
	pointer field_0x20d2;
	pointer field_0x20d6;
	pointer field_0x20da;
	pointer field_0x20de;
	pointer field_0x20e2;
	pointer field_0x20e6;
	pointer field_0x20ea;
	pointer field_0x20ee;
	pointer field_0x20f2;
	pointer field_0x20f6;
	pointer field_0x20fa;
	pointer field_0x20fe;
	pointer field_0x2102;
	pointer field_0x2106;
	pointer field_0x210a;
	pointer field_0x210e;
	pointer field_0x2112;
	pointer field_0x2116;
	pointer field_0x211a;
	pointer field_0x211e;
	pointer field_0x2122;
	pointer field_0x2126;
	pointer field_0x212a;
	pointer field_0x212e;
	pointer field_0x2132;
	pointer field_0x2136;
	pointer field_0x213a;
	pointer field_0x213e;
	pointer field_0x2142;
	pointer field_0x2146;
	pointer field_0x214a;
	pointer field_0x214e;
	pointer field_0x2152;
	pointer field_0x2156;
	pointer field_0x215a;
	pointer field_0x215e;
	pointer field_0x2162;
	pointer field_0x2166;
	pointer field_0x216a;
	pointer field_0x216e;
	pointer field_0x2172;
	pointer field_0x2176;
	pointer field_0x217a;
	pointer field_0x217e;
	pointer field_0x2182;
	pointer field_0x2186;
	pointer field_0x218a;
	pointer field_0x218e;
	pointer field_0x2192;
	pointer field_0x2196;
	pointer field_0x219a;
	pointer field_0x219e;
	pointer field_0x21a2;
	pointer field_0x21a6;
	pointer field_0x21aa;
	pointer field_0x21ae;
	pointer field_0x21b2;
	pointer field_0x21b6;
	pointer field_0x21ba;
	pointer field_0x21be;
	pointer field_0x21c2;
	pointer field_0x21c6;
	undefined field_0x21ca;
	undefined field_0x21cb;
};

typedef struct _CRuntime4_Globs _CRuntime4_Globs, *P_CRuntime4_Globs;

struct _CRuntime4_Globs { // [tags:HIDDEN,STD,GLOBS]
	undefined4 field_0x0;
	undefined4 field_0x4;
	undefined8 field_0x8[2];
	float10 field_0x18;
	undefined1 field_0x22[6];
	float10 field_0x28;
	undefined1 field_0x32[2];
	char field_0x34[6];
	undefined1 field_0x3a[2];
	char field_0x3c[2];
	undefined1 field_0x3e[2];
	pointer field_0x40;
	undefined1 field_0x44[4];
	pointer field_0x48;
	pointer field_0x4c;
	undefined4 field_0x50;
	undefined4 field_0x54;
	undefined field_0x58;
	undefined field_0x59;
	undefined field_0x5a;
	undefined field_0x5b;
	undefined4 field_0x5c;
	undefined4 field_0x60;
	undefined field_0x64;
	undefined field_0x65;
	undefined field_0x66;
	undefined field_0x67;
	undefined field_0x68;
	undefined field_0x69;
	undefined field_0x6a;
	undefined field_0x6b;
	undefined field_0x6c;
	undefined field_0x6d;
	undefined field_0x6e;
	undefined field_0x6f;
	undefined field_0x70;
	undefined field_0x71;
	undefined field_0x72;
	undefined field_0x73;
	undefined field_0x74;
	undefined field_0x75;
	undefined field_0x76;
	undefined field_0x77;
	undefined field_0x78;
	undefined field_0x79;
	undefined field_0x7a;
	undefined field_0x7b;
	undefined4 field_0x7c;
	undefined field_0x80;
	undefined field_0x81;
	undefined field_0x82;
	undefined field_0x83;
	undefined field_0x84;
	undefined field_0x85;
	undefined field_0x86;
	undefined field_0x87;
	undefined4 field_0x88;
	undefined field_0x8c;
	undefined field_0x8d;
	undefined field_0x8e;
	undefined field_0x8f;
	undefined field_0x90;
	undefined field_0x91;
	undefined field_0x92;
	undefined field_0x93;
	undefined field_0x94;
	undefined field_0x95;
	undefined field_0x96;
	undefined field_0x97;
	undefined field_0x98;
	undefined field_0x99;
	undefined field_0x9a;
	undefined field_0x9b;
	undefined field_0x9c;
	undefined field_0x9d;
	undefined field_0x9e;
	undefined field_0x9f;
	undefined field_0xa0;
	undefined field_0xa1;
	undefined field_0xa2;
	undefined field_0xa3;
	undefined field_0xa4;
	undefined field_0xa5;
	undefined field_0xa6;
	undefined field_0xa7;
	undefined field_0xa8;
	undefined field_0xa9;
	undefined field_0xaa;
	undefined field_0xab;
	undefined field_0xac;
	undefined field_0xad;
	undefined field_0xae;
	undefined field_0xaf;
	undefined field_0xb0;
	undefined field_0xb1;
	undefined field_0xb2;
	undefined field_0xb3;
	undefined field_0xb4;
	undefined field_0xb5;
	undefined field_0xb6;
	undefined field_0xb7;
	undefined field_0xb8;
	undefined field_0xb9;
	undefined field_0xba;
	undefined field_0xbb;
	undefined field_0xbc;
	undefined field_0xbd;
	undefined field_0xbe;
	undefined field_0xbf;
	undefined field_0xc0;
	undefined field_0xc1;
	undefined field_0xc2;
	undefined field_0xc3;
	undefined field_0xc4;
	undefined field_0xc5;
	undefined field_0xc6;
	undefined field_0xc7;
	undefined4 field_0xc8;
	undefined4 field_0xcc;
	undefined4 field_0xd0;
	undefined4 field_0xd4;
	undefined1 field_0xd8;
	undefined field_0xd9;
	undefined field_0xda;
	undefined field_0xdb;
	undefined field_0xdc;
	undefined field_0xdd;
	undefined field_0xde;
	undefined field_0xdf;
	undefined4 field_0xe0;
	undefined4 field_0xe4;
	undefined4 field_0xe8;
	undefined4 field_0xec;
	undefined1 field_0xf0;
	undefined1 field_0xf1;
	undefined1 field_0xf2;
	undefined1 field_0xf3;
	undefined field_0xf4;
	undefined field_0xf5;
	undefined field_0xf6;
	undefined field_0xf7;
	undefined1 field_0xf8;
	undefined field_0xf9;
	undefined field_0xfa;
	undefined field_0xfb;
	undefined field_0xfc;
	undefined field_0xfd;
	undefined field_0xfe;
	undefined field_0xff;
	undefined field_0x100;
	undefined field_0x101;
	undefined field_0x102;
	undefined field_0x103;
	undefined field_0x104;
	undefined field_0x105;
	undefined field_0x106;
	undefined field_0x107;
	undefined field_0x108;
	undefined field_0x109;
	undefined field_0x10a;
	undefined field_0x10b;
	undefined field_0x10c;
	undefined field_0x10d;
	undefined field_0x10e;
	undefined field_0x10f;
	undefined4 field_0x110;
	undefined field_0x114;
	undefined field_0x115;
	undefined field_0x116;
	undefined field_0x117;
	undefined field_0x118;
	undefined field_0x119;
	undefined field_0x11a;
	undefined field_0x11b;
	undefined field_0x11c;
	undefined field_0x11d;
	undefined field_0x11e;
	undefined field_0x11f;
	undefined field_0x120;
	undefined field_0x121;
	undefined field_0x122;
	undefined field_0x123;
	undefined field_0x124;
	undefined field_0x125;
	undefined field_0x126;
	undefined field_0x127;
	undefined field_0x128;
	undefined field_0x129;
	undefined field_0x12a;
	undefined field_0x12b;
	undefined field_0x12c;
	undefined field_0x12d;
	undefined field_0x12e;
	undefined field_0x12f;
	undefined field_0x130;
	undefined field_0x131;
	undefined field_0x132;
	undefined field_0x133;
	undefined field_0x134;
	undefined field_0x135;
	undefined field_0x136;
	undefined field_0x137;
	undefined field_0x138;
	undefined field_0x139;
	undefined field_0x13a;
	undefined field_0x13b;
	undefined field_0x13c;
	undefined field_0x13d;
	undefined field_0x13e;
	undefined field_0x13f;
	undefined field_0x140;
	undefined field_0x141;
	undefined field_0x142;
	undefined field_0x143;
	undefined field_0x144;
	undefined field_0x145;
	undefined field_0x146;
	undefined field_0x147;
	undefined field_0x148;
	undefined field_0x149;
	undefined field_0x14a;
	undefined field_0x14b;
	undefined field_0x14c;
	undefined field_0x14d;
	undefined field_0x14e;
	undefined field_0x14f;
	undefined field_0x150;
	undefined field_0x151;
	undefined field_0x152;
	undefined field_0x153;
	undefined field_0x154;
	undefined field_0x155;
	undefined field_0x156;
	undefined field_0x157;
	undefined field_0x158;
	undefined field_0x159;
	undefined field_0x15a;
	undefined field_0x15b;
	undefined field_0x15c;
	undefined field_0x15d;
	undefined field_0x15e;
	undefined field_0x15f;
	undefined field_0x160;
	undefined field_0x161;
	undefined field_0x162;
	undefined field_0x163;
	undefined field_0x164;
	undefined field_0x165;
	undefined field_0x166;
	undefined field_0x167;
	undefined field_0x168;
	undefined field_0x169;
	undefined field_0x16a;
	undefined field_0x16b;
	undefined field_0x16c;
	undefined field_0x16d;
	undefined field_0x16e;
	undefined field_0x16f;
	undefined field_0x170;
	undefined field_0x171;
	undefined field_0x172;
	undefined field_0x173;
	undefined field_0x174;
	undefined field_0x175;
	undefined field_0x176;
	undefined field_0x177;
	undefined field_0x178;
	undefined field_0x179;
	undefined field_0x17a;
	undefined field_0x17b;
	undefined field_0x17c;
	undefined field_0x17d;
	undefined field_0x17e;
	undefined field_0x17f;
	undefined field_0x180;
	undefined field_0x181;
	undefined field_0x182;
	undefined field_0x183;
	undefined field_0x184;
	undefined field_0x185;
	undefined field_0x186;
	undefined field_0x187;
	undefined field_0x188;
	undefined field_0x189;
	undefined field_0x18a;
	undefined field_0x18b;
	undefined field_0x18c;
	undefined field_0x18d;
	undefined field_0x18e;
	undefined field_0x18f;
	undefined field_0x190;
	undefined field_0x191;
	undefined field_0x192;
	undefined field_0x193;
	undefined field_0x194;
	undefined field_0x195;
	undefined field_0x196;
	undefined field_0x197;
	undefined field_0x198;
	undefined field_0x199;
	undefined field_0x19a;
	undefined field_0x19b;
	undefined field_0x19c;
	undefined field_0x19d;
	undefined field_0x19e;
	undefined field_0x19f;
	undefined field_0x1a0;
	undefined field_0x1a1;
	undefined field_0x1a2;
	undefined field_0x1a3;
	undefined field_0x1a4;
	undefined field_0x1a5;
	undefined field_0x1a6;
	undefined field_0x1a7;
	undefined field_0x1a8;
	undefined field_0x1a9;
	undefined field_0x1aa;
	undefined field_0x1ab;
	undefined field_0x1ac;
	undefined field_0x1ad;
	undefined field_0x1ae;
	undefined field_0x1af;
	undefined field_0x1b0;
	undefined field_0x1b1;
	undefined field_0x1b2;
	undefined field_0x1b3;
	undefined field_0x1b4;
	undefined field_0x1b5;
	undefined field_0x1b6;
	undefined field_0x1b7;
	undefined field_0x1b8;
	undefined field_0x1b9;
	undefined field_0x1ba;
	undefined field_0x1bb;
	undefined field_0x1bc;
	undefined field_0x1bd;
	undefined field_0x1be;
	undefined field_0x1bf;
	undefined field_0x1c0;
	undefined field_0x1c1;
	undefined field_0x1c2;
	undefined field_0x1c3;
	undefined field_0x1c4;
	undefined field_0x1c5;
	undefined field_0x1c6;
	undefined field_0x1c7;
	undefined field_0x1c8;
	undefined field_0x1c9;
	undefined field_0x1ca;
	undefined field_0x1cb;
	undefined field_0x1cc;
	undefined field_0x1cd;
	undefined field_0x1ce;
	undefined field_0x1cf;
	undefined field_0x1d0;
	undefined field_0x1d1;
	undefined field_0x1d2;
	undefined field_0x1d3;
	undefined1 field_0x1d4;
	undefined field_0x1d5;
	undefined field_0x1d6;
	undefined field_0x1d7;
	int field_0x1d8;
	pointer field_0x1dc;
	int field_0x1e0;
	pointer field_0x1e4;
	int field_0x1e8;
	pointer field_0x1ec;
	int field_0x1f0;
	pointer field_0x1f4;
	int field_0x1f8;
	pointer field_0x1fc;
	int field_0x200;
	pointer field_0x204;
	int field_0x208;
	pointer field_0x20c;
	int field_0x210;
	pointer field_0x214;
	int field_0x218;
	pointer field_0x21c;
	int field_0x220;
	pointer field_0x224;
	int field_0x228;
	pointer field_0x22c;
	int field_0x230;
	pointer field_0x234;
	int field_0x238;
	pointer field_0x23c;
	int field_0x240;
	pointer field_0x244;
	int field_0x248;
	pointer field_0x24c;
	int field_0x250;
	pointer field_0x254;
	int field_0x258;
	pointer field_0x25c;
	int field_0x260;
	pointer field_0x264;
	uint __errorArray_004b34c0[45][2];
	pointer field_0x3d0;
	undefined field_0x3d4;
	undefined field_0x3d5;
	undefined field_0x3d6;
	undefined field_0x3d7;
	pointer field_0x3d8;
	undefined field_0x3dc;
	undefined field_0x3dd;
	undefined field_0x3de;
	undefined field_0x3df;
	undefined4 field_0x3e0;
	undefined field_0x3e4;
	undefined field_0x3e5;
	undefined field_0x3e6;
	undefined field_0x3e7;
	undefined field_0x3e8;
	undefined field_0x3e9;
	undefined field_0x3ea;
	undefined field_0x3eb;
	undefined field_0x3ec;
	undefined field_0x3ed;
	undefined field_0x3ee;
	undefined field_0x3ef;
	FILE __FILE_004b3648;
	FILE __FILE_004b3668;
	undefined field_0x430;
	undefined field_0x431;
	undefined field_0x432;
	undefined field_0x433;
	undefined field_0x434;
	undefined field_0x435;
	undefined field_0x436;
	undefined field_0x437;
	undefined field_0x438;
	undefined field_0x439;
	undefined field_0x43a;
	undefined field_0x43b;
	undefined field_0x43c;
	undefined field_0x43d;
	undefined field_0x43e;
	undefined field_0x43f;
	undefined field_0x440;
	undefined field_0x441;
	undefined field_0x442;
	undefined field_0x443;
	undefined field_0x444;
	undefined field_0x445;
	undefined field_0x446;
	undefined field_0x447;
	undefined field_0x448;
	undefined field_0x449;
	undefined field_0x44a;
	undefined field_0x44b;
	undefined field_0x44c;
	undefined field_0x44d;
	undefined field_0x44e;
	undefined field_0x44f;
	undefined field_0x450;
	undefined field_0x451;
	undefined field_0x452;
	undefined field_0x453;
	undefined field_0x454;
	undefined field_0x455;
	undefined field_0x456;
	undefined field_0x457;
	undefined field_0x458;
	undefined field_0x459;
	undefined field_0x45a;
	undefined field_0x45b;
	undefined field_0x45c;
	undefined field_0x45d;
	undefined field_0x45e;
	undefined field_0x45f;
	undefined field_0x460;
	undefined field_0x461;
	undefined field_0x462;
	undefined field_0x463;
	undefined field_0x464;
	undefined field_0x465;
	undefined field_0x466;
	undefined field_0x467;
	undefined field_0x468;
	undefined field_0x469;
	undefined field_0x46a;
	undefined field_0x46b;
	undefined field_0x46c;
	undefined field_0x46d;
	undefined field_0x46e;
	undefined field_0x46f;
	undefined field_0x470;
	undefined field_0x471;
	undefined field_0x472;
	undefined field_0x473;
	undefined field_0x474;
	undefined field_0x475;
	undefined field_0x476;
	undefined field_0x477;
	undefined field_0x478;
	undefined field_0x479;
	undefined field_0x47a;
	undefined field_0x47b;
	undefined field_0x47c;
	undefined field_0x47d;
	undefined field_0x47e;
	undefined field_0x47f;
	undefined field_0x480;
	undefined field_0x481;
	undefined field_0x482;
	undefined field_0x483;
	undefined field_0x484;
	undefined field_0x485;
	undefined field_0x486;
	undefined field_0x487;
	undefined field_0x488;
	undefined field_0x489;
	undefined field_0x48a;
	undefined field_0x48b;
	undefined field_0x48c;
	undefined field_0x48d;
	undefined field_0x48e;
	undefined field_0x48f;
	undefined field_0x490;
	undefined field_0x491;
	undefined field_0x492;
	undefined field_0x493;
	undefined field_0x494;
	undefined field_0x495;
	undefined field_0x496;
	undefined field_0x497;
	undefined field_0x498;
	undefined field_0x499;
	undefined field_0x49a;
	undefined field_0x49b;
	undefined field_0x49c;
	undefined field_0x49d;
	undefined field_0x49e;
	undefined field_0x49f;
	undefined field_0x4a0;
	undefined field_0x4a1;
	undefined field_0x4a2;
	undefined field_0x4a3;
	undefined field_0x4a4;
	undefined field_0x4a5;
	undefined field_0x4a6;
	undefined field_0x4a7;
	undefined field_0x4a8;
	undefined field_0x4a9;
	undefined field_0x4aa;
	undefined field_0x4ab;
	undefined field_0x4ac;
	undefined field_0x4ad;
	undefined field_0x4ae;
	undefined field_0x4af;
	undefined field_0x4b0;
	undefined field_0x4b1;
	undefined field_0x4b2;
	undefined field_0x4b3;
	undefined field_0x4b4;
	undefined field_0x4b5;
	undefined field_0x4b6;
	undefined field_0x4b7;
	undefined field_0x4b8;
	undefined field_0x4b9;
	undefined field_0x4ba;
	undefined field_0x4bb;
	undefined field_0x4bc;
	undefined field_0x4bd;
	undefined field_0x4be;
	undefined field_0x4bf;
	undefined field_0x4c0;
	undefined field_0x4c1;
	undefined field_0x4c2;
	undefined field_0x4c3;
	undefined field_0x4c4;
	undefined field_0x4c5;
	undefined field_0x4c6;
	undefined field_0x4c7;
	undefined field_0x4c8;
	undefined field_0x4c9;
	undefined field_0x4ca;
	undefined field_0x4cb;
	undefined field_0x4cc;
	undefined field_0x4cd;
	undefined field_0x4ce;
	undefined field_0x4cf;
	undefined field_0x4d0;
	undefined field_0x4d1;
	undefined field_0x4d2;
	undefined field_0x4d3;
	undefined field_0x4d4;
	undefined field_0x4d5;
	undefined field_0x4d6;
	undefined field_0x4d7;
	undefined field_0x4d8;
	undefined field_0x4d9;
	undefined field_0x4da;
	undefined field_0x4db;
	undefined field_0x4dc;
	undefined field_0x4dd;
	undefined field_0x4de;
	undefined field_0x4df;
	undefined field_0x4e0;
	undefined field_0x4e1;
	undefined field_0x4e2;
	undefined field_0x4e3;
	undefined field_0x4e4;
	undefined field_0x4e5;
	undefined field_0x4e6;
	undefined field_0x4e7;
	undefined field_0x4e8;
	undefined field_0x4e9;
	undefined field_0x4ea;
	undefined field_0x4eb;
	undefined field_0x4ec;
	undefined field_0x4ed;
	undefined field_0x4ee;
	undefined field_0x4ef;
	undefined field_0x4f0;
	undefined field_0x4f1;
	undefined field_0x4f2;
	undefined field_0x4f3;
	undefined field_0x4f4;
	undefined field_0x4f5;
	undefined field_0x4f6;
	undefined field_0x4f7;
	undefined field_0x4f8;
	undefined field_0x4f9;
	undefined field_0x4fa;
	undefined field_0x4fb;
	undefined field_0x4fc;
	undefined field_0x4fd;
	undefined field_0x4fe;
	undefined field_0x4ff;
	undefined field_0x500;
	undefined field_0x501;
	undefined field_0x502;
	undefined field_0x503;
	undefined field_0x504;
	undefined field_0x505;
	undefined field_0x506;
	undefined field_0x507;
	undefined field_0x508;
	undefined field_0x509;
	undefined field_0x50a;
	undefined field_0x50b;
	undefined field_0x50c;
	undefined field_0x50d;
	undefined field_0x50e;
	undefined field_0x50f;
	undefined field_0x510;
	undefined field_0x511;
	undefined field_0x512;
	undefined field_0x513;
	undefined field_0x514;
	undefined field_0x515;
	undefined field_0x516;
	undefined field_0x517;
	undefined field_0x518;
	undefined field_0x519;
	undefined field_0x51a;
	undefined field_0x51b;
	undefined field_0x51c;
	undefined field_0x51d;
	undefined field_0x51e;
	undefined field_0x51f;
	undefined field_0x520;
	undefined field_0x521;
	undefined field_0x522;
	undefined field_0x523;
	undefined field_0x524;
	undefined field_0x525;
	undefined field_0x526;
	undefined field_0x527;
	undefined field_0x528;
	undefined field_0x529;
	undefined field_0x52a;
	undefined field_0x52b;
	undefined field_0x52c;
	undefined field_0x52d;
	undefined field_0x52e;
	undefined field_0x52f;
	undefined field_0x530;
	undefined field_0x531;
	undefined field_0x532;
	undefined field_0x533;
	undefined field_0x534;
	undefined field_0x535;
	undefined field_0x536;
	undefined field_0x537;
	undefined field_0x538;
	undefined field_0x539;
	undefined field_0x53a;
	undefined field_0x53b;
	undefined field_0x53c;
	undefined field_0x53d;
	undefined field_0x53e;
	undefined field_0x53f;
	undefined field_0x540;
	undefined field_0x541;
	undefined field_0x542;
	undefined field_0x543;
	undefined field_0x544;
	undefined field_0x545;
	undefined field_0x546;
	undefined field_0x547;
	undefined field_0x548;
	undefined field_0x549;
	undefined field_0x54a;
	undefined field_0x54b;
	undefined field_0x54c;
	undefined field_0x54d;
	undefined field_0x54e;
	undefined field_0x54f;
	undefined field_0x550;
	undefined field_0x551;
	undefined field_0x552;
	undefined field_0x553;
	undefined field_0x554;
	undefined field_0x555;
	undefined field_0x556;
	undefined field_0x557;
	undefined field_0x558;
	undefined field_0x559;
	undefined field_0x55a;
	undefined field_0x55b;
	undefined field_0x55c;
	undefined field_0x55d;
	undefined field_0x55e;
	undefined field_0x55f;
	undefined field_0x560;
	undefined field_0x561;
	undefined field_0x562;
	undefined field_0x563;
	undefined field_0x564;
	undefined field_0x565;
	undefined field_0x566;
	undefined field_0x567;
	undefined field_0x568;
	undefined field_0x569;
	undefined field_0x56a;
	undefined field_0x56b;
	undefined field_0x56c;
	undefined field_0x56d;
	undefined field_0x56e;
	undefined field_0x56f;
	undefined field_0x570;
	undefined field_0x571;
	undefined field_0x572;
	undefined field_0x573;
	undefined field_0x574;
	undefined field_0x575;
	undefined field_0x576;
	undefined field_0x577;
	undefined field_0x578;
	undefined field_0x579;
	undefined field_0x57a;
	undefined field_0x57b;
	undefined field_0x57c;
	undefined field_0x57d;
	undefined field_0x57e;
	undefined field_0x57f;
	undefined field_0x580;
	undefined field_0x581;
	undefined field_0x582;
	undefined field_0x583;
	undefined field_0x584;
	undefined field_0x585;
	undefined field_0x586;
	undefined field_0x587;
	undefined field_0x588;
	undefined field_0x589;
	undefined field_0x58a;
	undefined field_0x58b;
	undefined field_0x58c;
	undefined field_0x58d;
	undefined field_0x58e;
	undefined field_0x58f;
	undefined field_0x590;
	undefined field_0x591;
	undefined field_0x592;
	undefined field_0x593;
	undefined field_0x594;
	undefined field_0x595;
	undefined field_0x596;
	undefined field_0x597;
	undefined field_0x598;
	undefined field_0x599;
	undefined field_0x59a;
	undefined field_0x59b;
	undefined field_0x59c;
	undefined field_0x59d;
	undefined field_0x59e;
	undefined field_0x59f;
	undefined field_0x5a0;
	undefined field_0x5a1;
	undefined field_0x5a2;
	undefined field_0x5a3;
	undefined field_0x5a4;
	undefined field_0x5a5;
	undefined field_0x5a6;
	undefined field_0x5a7;
	undefined field_0x5a8;
	undefined field_0x5a9;
	undefined field_0x5aa;
	undefined field_0x5ab;
	undefined field_0x5ac;
	undefined field_0x5ad;
	undefined field_0x5ae;
	undefined field_0x5af;
	undefined field_0x5b0;
	undefined field_0x5b1;
	undefined field_0x5b2;
	undefined field_0x5b3;
	undefined field_0x5b4;
	undefined field_0x5b5;
	undefined field_0x5b6;
	undefined field_0x5b7;
	undefined field_0x5b8;
	undefined field_0x5b9;
	undefined field_0x5ba;
	undefined field_0x5bb;
	undefined field_0x5bc;
	undefined field_0x5bd;
	undefined field_0x5be;
	undefined field_0x5bf;
	undefined field_0x5c0;
	undefined field_0x5c1;
	undefined field_0x5c2;
	undefined field_0x5c3;
	undefined field_0x5c4;
	undefined field_0x5c5;
	undefined field_0x5c6;
	undefined field_0x5c7;
	undefined field_0x5c8;
	undefined field_0x5c9;
	undefined field_0x5ca;
	undefined field_0x5cb;
	undefined field_0x5cc;
	undefined field_0x5cd;
	undefined field_0x5ce;
	undefined field_0x5cf;
	undefined field_0x5d0;
	undefined field_0x5d1;
	undefined field_0x5d2;
	undefined field_0x5d3;
	undefined field_0x5d4;
	undefined field_0x5d5;
	undefined field_0x5d6;
	undefined field_0x5d7;
	undefined field_0x5d8;
	undefined field_0x5d9;
	undefined field_0x5da;
	undefined field_0x5db;
	undefined field_0x5dc;
	undefined field_0x5dd;
	undefined field_0x5de;
	undefined field_0x5df;
	undefined field_0x5e0;
	undefined field_0x5e1;
	undefined field_0x5e2;
	undefined field_0x5e3;
	undefined field_0x5e4;
	undefined field_0x5e5;
	undefined field_0x5e6;
	undefined field_0x5e7;
	undefined field_0x5e8;
	undefined field_0x5e9;
	undefined field_0x5ea;
	undefined field_0x5eb;
	undefined field_0x5ec;
	undefined field_0x5ed;
	undefined field_0x5ee;
	undefined field_0x5ef;
	undefined field_0x5f0;
	undefined field_0x5f1;
	undefined field_0x5f2;
	undefined field_0x5f3;
	undefined field_0x5f4;
	undefined field_0x5f5;
	undefined field_0x5f6;
	undefined field_0x5f7;
	undefined field_0x5f8;
	undefined field_0x5f9;
	undefined field_0x5fa;
	undefined field_0x5fb;
	undefined field_0x5fc;
	undefined field_0x5fd;
	undefined field_0x5fe;
	undefined field_0x5ff;
	undefined field_0x600;
	undefined field_0x601;
	undefined field_0x602;
	undefined field_0x603;
	undefined field_0x604;
	undefined field_0x605;
	undefined field_0x606;
	undefined field_0x607;
	undefined field_0x608;
	undefined field_0x609;
	undefined field_0x60a;
	undefined field_0x60b;
	undefined field_0x60c;
	undefined field_0x60d;
	undefined field_0x60e;
	undefined field_0x60f;
	undefined field_0x610;
	undefined field_0x611;
	undefined field_0x612;
	undefined field_0x613;
	undefined field_0x614;
	undefined field_0x615;
	undefined field_0x616;
	undefined field_0x617;
	undefined field_0x618;
	undefined field_0x619;
	undefined field_0x61a;
	undefined field_0x61b;
	undefined field_0x61c;
	undefined field_0x61d;
	undefined field_0x61e;
	undefined field_0x61f;
	undefined field_0x620;
	undefined field_0x621;
	undefined field_0x622;
	undefined field_0x623;
	undefined field_0x624;
	undefined field_0x625;
	undefined field_0x626;
	undefined field_0x627;
	undefined field_0x628;
	undefined field_0x629;
	undefined field_0x62a;
	undefined field_0x62b;
	undefined field_0x62c;
	undefined field_0x62d;
	undefined field_0x62e;
	undefined field_0x62f;
	undefined field_0x630;
	undefined field_0x631;
	undefined field_0x632;
	undefined field_0x633;
	undefined field_0x634;
	undefined field_0x635;
	undefined field_0x636;
	undefined field_0x637;
	undefined field_0x638;
	undefined field_0x639;
	undefined field_0x63a;
	undefined field_0x63b;
	undefined field_0x63c;
	undefined field_0x63d;
	undefined field_0x63e;
	undefined field_0x63f;
	undefined field_0x640;
	undefined field_0x641;
	undefined field_0x642;
	undefined field_0x643;
	undefined field_0x644;
	undefined field_0x645;
	undefined field_0x646;
	undefined field_0x647;
	undefined field_0x648;
	undefined field_0x649;
	undefined field_0x64a;
	undefined field_0x64b;
	undefined field_0x64c;
	undefined field_0x64d;
	undefined field_0x64e;
	undefined field_0x64f;
	undefined field_0x650;
	undefined field_0x651;
	undefined field_0x652;
	undefined field_0x653;
	undefined field_0x654;
	undefined field_0x655;
	undefined field_0x656;
	undefined field_0x657;
	undefined field_0x658;
	undefined field_0x659;
	undefined field_0x65a;
	undefined field_0x65b;
	undefined field_0x65c;
	undefined field_0x65d;
	undefined field_0x65e;
	undefined field_0x65f;
	undefined field_0x660;
	undefined field_0x661;
	undefined field_0x662;
	undefined field_0x663;
	undefined field_0x664;
	undefined field_0x665;
	undefined field_0x666;
	undefined field_0x667;
	undefined field_0x668;
	undefined field_0x669;
	undefined field_0x66a;
	undefined field_0x66b;
	undefined field_0x66c;
	undefined field_0x66d;
	undefined field_0x66e;
	undefined field_0x66f;
	undefined field_0x670;
	undefined field_0x671;
	undefined field_0x672;
	undefined field_0x673;
	undefined field_0x674;
	undefined field_0x675;
	undefined field_0x676;
	undefined field_0x677;
	undefined field_0x678;
	undefined field_0x679;
	undefined field_0x67a;
	undefined field_0x67b;
	undefined field_0x67c;
	undefined field_0x67d;
	undefined field_0x67e;
	undefined field_0x67f;
	undefined field_0x680;
	undefined field_0x681;
	undefined field_0x682;
	undefined field_0x683;
	undefined field_0x684;
	undefined field_0x685;
	undefined field_0x686;
	undefined field_0x687;
	undefined4 field_0x688;
	undefined field_0x68c;
	undefined field_0x68d;
	undefined field_0x68e;
	undefined field_0x68f;
	undefined field_0x690;
	undefined field_0x691;
	undefined field_0x692;
	undefined field_0x693;
	undefined field_0x694;
	undefined field_0x695;
	undefined field_0x696;
	undefined field_0x697;
	undefined4 field_0x698;
	undefined4 field_0x69c;
	undefined4 field_0x6a0;
	undefined field_0x6a4;
	undefined field_0x6a5;
	undefined field_0x6a6;
	undefined field_0x6a7;
	char field_0x6a8[4];
	undefined field_0x6ac;
	undefined field_0x6ad;
	undefined field_0x6ae;
	undefined field_0x6af;
	undefined field_0x6b0;
	undefined field_0x6b1;
	undefined field_0x6b2;
	undefined field_0x6b3;
	undefined field_0x6b4;
	undefined field_0x6b5;
	undefined field_0x6b6;
	undefined field_0x6b7;
	undefined field_0x6b8;
	undefined field_0x6b9;
	undefined field_0x6ba;
	undefined field_0x6bb;
	undefined field_0x6bc;
	undefined field_0x6bd;
	undefined field_0x6be;
	undefined field_0x6bf;
	undefined field_0x6c0;
	undefined field_0x6c1;
	undefined field_0x6c2;
	undefined field_0x6c3;
	undefined field_0x6c4;
	undefined field_0x6c5;
	undefined field_0x6c6;
	undefined field_0x6c7;
	undefined field_0x6c8;
	undefined field_0x6c9;
	undefined field_0x6ca;
	undefined field_0x6cb;
	undefined field_0x6cc;
	undefined field_0x6cd;
	undefined field_0x6ce;
	undefined field_0x6cf;
	undefined field_0x6d0;
	undefined field_0x6d1;
	undefined field_0x6d2;
	undefined field_0x6d3;
	undefined field_0x6d4;
	undefined field_0x6d5;
	undefined field_0x6d6;
	undefined field_0x6d7;
	undefined field_0x6d8;
	undefined field_0x6d9;
	undefined field_0x6da;
	undefined field_0x6db;
	undefined field_0x6dc;
	undefined field_0x6dd;
	undefined field_0x6de;
	undefined field_0x6df;
	undefined field_0x6e0;
	undefined field_0x6e1;
	undefined field_0x6e2;
	undefined field_0x6e3;
	undefined field_0x6e4;
	undefined field_0x6e5;
	undefined field_0x6e6;
	undefined1 field_0x6e7;
	char field_0x6e8[4];
	undefined field_0x6ec;
	undefined field_0x6ed;
	undefined field_0x6ee;
	undefined field_0x6ef;
	undefined field_0x6f0;
	undefined field_0x6f1;
	undefined field_0x6f2;
	undefined field_0x6f3;
	undefined field_0x6f4;
	undefined field_0x6f5;
	undefined field_0x6f6;
	undefined field_0x6f7;
	undefined field_0x6f8;
	undefined field_0x6f9;
	undefined field_0x6fa;
	undefined field_0x6fb;
	undefined field_0x6fc;
	undefined field_0x6fd;
	undefined field_0x6fe;
	undefined field_0x6ff;
	undefined field_0x700;
	undefined field_0x701;
	undefined field_0x702;
	undefined field_0x703;
	undefined field_0x704;
	undefined field_0x705;
	undefined field_0x706;
	undefined field_0x707;
	undefined field_0x708;
	undefined field_0x709;
	undefined field_0x70a;
	undefined field_0x70b;
	undefined field_0x70c;
	undefined field_0x70d;
	undefined field_0x70e;
	undefined field_0x70f;
	undefined field_0x710;
	undefined field_0x711;
	undefined field_0x712;
	undefined field_0x713;
	undefined field_0x714;
	undefined field_0x715;
	undefined field_0x716;
	undefined field_0x717;
	undefined field_0x718;
	undefined field_0x719;
	undefined field_0x71a;
	undefined field_0x71b;
	undefined field_0x71c;
	undefined field_0x71d;
	undefined field_0x71e;
	undefined field_0x71f;
	undefined field_0x720;
	undefined field_0x721;
	undefined field_0x722;
	undefined field_0x723;
	undefined field_0x724;
	undefined field_0x725;
	undefined field_0x726;
	undefined1 field_0x727;
	pointer field_0x728;
	pointer field_0x72c;
	undefined4 field_0x730;
	undefined4 field_0x734;
	undefined4 field_0x738;
	undefined field_0x73c;
	undefined field_0x73d;
	undefined field_0x73e;
	undefined field_0x73f;
	undefined4 field_0x740;
	undefined4 field_0x744;
	undefined4 field_0x748;
	undefined field_0x74c;
	undefined field_0x74d;
	undefined field_0x74e;
	undefined field_0x74f;
	undefined field_0x750;
	undefined field_0x751;
	undefined field_0x752;
	undefined field_0x753;
	undefined field_0x754;
	undefined field_0x755;
	undefined field_0x756;
	undefined field_0x757;
	undefined field_0x758;
	undefined field_0x759;
	undefined field_0x75a;
	undefined field_0x75b;
	undefined field_0x75c;
	undefined field_0x75d;
	undefined field_0x75e;
	undefined field_0x75f;
	undefined field_0x760;
	undefined field_0x761;
	undefined field_0x762;
	undefined field_0x763;
	undefined field_0x764;
	undefined field_0x765;
	undefined field_0x766;
	undefined field_0x767;
	undefined field_0x768;
	undefined field_0x769;
	undefined field_0x76a;
	undefined field_0x76b;
	undefined field_0x76c;
	undefined field_0x76d;
	undefined field_0x76e;
	undefined field_0x76f;
	undefined field_0x770;
	undefined field_0x771;
	undefined field_0x772;
	undefined field_0x773;
	undefined field_0x774;
	undefined field_0x775;
	undefined field_0x776;
	undefined field_0x777;
	undefined field_0x778;
	undefined field_0x779;
	undefined field_0x77a;
	undefined field_0x77b;
	undefined field_0x77c;
	undefined field_0x77d;
	undefined field_0x77e;
	undefined field_0x77f;
	undefined field_0x780;
	undefined field_0x781;
	undefined field_0x782;
	undefined field_0x783;
	undefined field_0x784;
	undefined field_0x785;
	undefined field_0x786;
	undefined field_0x787;
	undefined field_0x788;
	undefined field_0x789;
	undefined field_0x78a;
	undefined field_0x78b;
	undefined field_0x78c;
	undefined field_0x78d;
	undefined field_0x78e;
	undefined field_0x78f;
	undefined field_0x790;
	undefined field_0x791;
	undefined field_0x792;
	undefined field_0x793;
	undefined field_0x794;
	undefined field_0x795;
	undefined field_0x796;
	undefined field_0x797;
	undefined field_0x798;
	undefined field_0x799;
	undefined field_0x79a;
	undefined field_0x79b;
	undefined field_0x79c;
	undefined field_0x79d;
	undefined field_0x79e;
	undefined field_0x79f;
	undefined field_0x7a0;
	undefined field_0x7a1;
	undefined field_0x7a2;
	undefined field_0x7a3;
	undefined field_0x7a4;
	undefined field_0x7a5;
	undefined field_0x7a6;
	undefined field_0x7a7;
	undefined field_0x7a8;
	undefined field_0x7a9;
	undefined field_0x7aa;
	undefined field_0x7ab;
	undefined field_0x7ac;
	undefined field_0x7ad;
	undefined field_0x7ae;
	undefined field_0x7af;
	undefined field_0x7b0;
	undefined field_0x7b1;
	undefined field_0x7b2;
	undefined field_0x7b3;
	undefined field_0x7b4;
	undefined field_0x7b5;
	undefined field_0x7b6;
	undefined field_0x7b7;
	undefined field_0x7b8;
	undefined field_0x7b9;
	undefined field_0x7ba;
	undefined field_0x7bb;
	undefined field_0x7bc;
	undefined field_0x7bd;
	undefined field_0x7be;
	undefined field_0x7bf;
	undefined field_0x7c0;
	undefined field_0x7c1;
	undefined field_0x7c2;
	undefined field_0x7c3;
	undefined field_0x7c4;
	undefined field_0x7c5;
	undefined field_0x7c6;
	undefined field_0x7c7;
	undefined field_0x7c8;
	undefined field_0x7c9;
	undefined field_0x7ca;
	undefined field_0x7cb;
	undefined field_0x7cc;
	undefined field_0x7cd;
	undefined field_0x7ce;
	undefined field_0x7cf;
	undefined field_0x7d0;
	undefined field_0x7d1;
	undefined field_0x7d2;
	undefined field_0x7d3;
	undefined field_0x7d4;
	undefined field_0x7d5;
	undefined field_0x7d6;
	undefined field_0x7d7;
	undefined field_0x7d8;
	undefined field_0x7d9;
	undefined field_0x7da;
	undefined field_0x7db;
	undefined field_0x7dc;
	undefined field_0x7dd;
	undefined field_0x7de;
	undefined field_0x7df;
	undefined field_0x7e0;
	undefined field_0x7e1;
	undefined field_0x7e2;
	undefined field_0x7e3;
	undefined field_0x7e4;
	undefined field_0x7e5;
	undefined field_0x7e6;
	undefined field_0x7e7;
	undefined field_0x7e8;
	undefined field_0x7e9;
	undefined field_0x7ea;
	undefined field_0x7eb;
	undefined field_0x7ec;
	undefined field_0x7ed;
	undefined field_0x7ee;
	undefined field_0x7ef;
	undefined field_0x7f0;
	undefined field_0x7f1;
	undefined field_0x7f2;
	undefined field_0x7f3;
	undefined field_0x7f4;
	undefined field_0x7f5;
	undefined field_0x7f6;
	undefined field_0x7f7;
	undefined field_0x7f8;
	undefined field_0x7f9;
	undefined field_0x7fa;
	undefined field_0x7fb;
	undefined field_0x7fc;
	undefined field_0x7fd;
	undefined field_0x7fe;
	undefined field_0x7ff;
	undefined field_0x800;
	undefined field_0x801;
	undefined field_0x802;
	undefined field_0x803;
	undefined field_0x804;
	undefined field_0x805;
	undefined field_0x806;
	undefined field_0x807;
	undefined field_0x808;
	undefined field_0x809;
	undefined field_0x80a;
	undefined field_0x80b;
	undefined field_0x80c;
	undefined field_0x80d;
	undefined field_0x80e;
	undefined field_0x80f;
	undefined field_0x810;
	undefined field_0x811;
	undefined field_0x812;
	undefined field_0x813;
	undefined field_0x814;
	undefined field_0x815;
	undefined field_0x816;
	undefined field_0x817;
	undefined field_0x818;
	undefined field_0x819;
	undefined field_0x81a;
	undefined field_0x81b;
	undefined field_0x81c;
	undefined field_0x81d;
	undefined field_0x81e;
	undefined field_0x81f;
	undefined field_0x820;
	undefined field_0x821;
	undefined field_0x822;
	undefined field_0x823;
	undefined field_0x824;
	undefined field_0x825;
	undefined field_0x826;
	undefined field_0x827;
	undefined field_0x828;
	undefined field_0x829;
	undefined field_0x82a;
	undefined field_0x82b;
	undefined field_0x82c;
	undefined field_0x82d;
	undefined field_0x82e;
	undefined field_0x82f;
	undefined field_0x830;
	undefined field_0x831;
	undefined field_0x832;
	undefined field_0x833;
	undefined field_0x834;
	undefined field_0x835;
	undefined field_0x836;
	undefined field_0x837;
	undefined field_0x838;
	undefined field_0x839;
	undefined field_0x83a;
	undefined field_0x83b;
	undefined field_0x83c;
	undefined field_0x83d;
	undefined field_0x83e;
	undefined field_0x83f;
	undefined field_0x840;
	undefined field_0x841;
	undefined field_0x842;
	undefined field_0x843;
	undefined field_0x844;
	undefined field_0x845;
	undefined field_0x846;
	undefined field_0x847;
	undefined field_0x848;
	undefined field_0x849;
	undefined field_0x84a;
	undefined field_0x84b;
	undefined field_0x84c;
	undefined field_0x84d;
	undefined field_0x84e;
	undefined field_0x84f;
	undefined field_0x850;
	undefined field_0x851;
	undefined field_0x852;
	undefined field_0x853;
	undefined field_0x854;
	undefined field_0x855;
	undefined field_0x856;
	undefined field_0x857;
	undefined field_0x858;
	undefined field_0x859;
	undefined field_0x85a;
	undefined field_0x85b;
	undefined field_0x85c;
	undefined field_0x85d;
	undefined field_0x85e;
	undefined field_0x85f;
	undefined field_0x860;
	undefined field_0x861;
	undefined field_0x862;
	undefined field_0x863;
	undefined field_0x864;
	undefined field_0x865;
	undefined field_0x866;
	undefined field_0x867;
	undefined field_0x868;
	undefined field_0x869;
	undefined field_0x86a;
	undefined field_0x86b;
	undefined field_0x86c;
	undefined field_0x86d;
	undefined field_0x86e;
	undefined field_0x86f;
	undefined field_0x870;
	undefined field_0x871;
	undefined field_0x872;
	undefined field_0x873;
	undefined field_0x874;
	undefined field_0x875;
	undefined field_0x876;
	undefined field_0x877;
	undefined field_0x878;
	undefined field_0x879;
	undefined field_0x87a;
	undefined field_0x87b;
	undefined field_0x87c;
	undefined field_0x87d;
	undefined field_0x87e;
	undefined field_0x87f;
	undefined field_0x880;
	undefined field_0x881;
	undefined field_0x882;
	undefined field_0x883;
	undefined field_0x884;
	undefined field_0x885;
	undefined field_0x886;
	undefined field_0x887;
	undefined field_0x888;
	undefined field_0x889;
	undefined field_0x88a;
	undefined field_0x88b;
	undefined field_0x88c;
	undefined field_0x88d;
	undefined field_0x88e;
	undefined field_0x88f;
	undefined field_0x890;
	undefined field_0x891;
	undefined field_0x892;
	undefined field_0x893;
	undefined field_0x894;
	undefined field_0x895;
	undefined field_0x896;
	undefined field_0x897;
	undefined field_0x898;
	undefined field_0x899;
	undefined field_0x89a;
	undefined field_0x89b;
	undefined field_0x89c;
	undefined field_0x89d;
	undefined field_0x89e;
	undefined field_0x89f;
	undefined field_0x8a0;
	undefined field_0x8a1;
	undefined field_0x8a2;
	undefined field_0x8a3;
	undefined field_0x8a4;
	undefined field_0x8a5;
	undefined field_0x8a6;
	undefined field_0x8a7;
	undefined field_0x8a8;
	undefined field_0x8a9;
	undefined field_0x8aa;
	undefined field_0x8ab;
	undefined field_0x8ac;
	undefined field_0x8ad;
	undefined field_0x8ae;
	undefined field_0x8af;
	undefined field_0x8b0;
	undefined field_0x8b1;
	undefined field_0x8b2;
	undefined field_0x8b3;
	undefined field_0x8b4;
	undefined field_0x8b5;
	undefined field_0x8b6;
	undefined field_0x8b7;
	undefined field_0x8b8;
	undefined field_0x8b9;
	undefined field_0x8ba;
	undefined field_0x8bb;
	undefined field_0x8bc;
	undefined field_0x8bd;
	undefined field_0x8be;
	undefined field_0x8bf;
	undefined field_0x8c0;
	undefined field_0x8c1;
	undefined field_0x8c2;
	undefined field_0x8c3;
	undefined field_0x8c4;
	undefined field_0x8c5;
	undefined field_0x8c6;
	undefined field_0x8c7;
	undefined field_0x8c8;
	undefined field_0x8c9;
	undefined field_0x8ca;
	undefined field_0x8cb;
	undefined field_0x8cc;
	undefined field_0x8cd;
	undefined field_0x8ce;
	undefined field_0x8cf;
	undefined field_0x8d0;
	undefined field_0x8d1;
	undefined field_0x8d2;
	undefined field_0x8d3;
	undefined field_0x8d4;
	undefined field_0x8d5;
	undefined field_0x8d6;
	undefined field_0x8d7;
	undefined field_0x8d8;
	undefined field_0x8d9;
	undefined field_0x8da;
	undefined field_0x8db;
	undefined field_0x8dc;
	undefined field_0x8dd;
	undefined field_0x8de;
	undefined field_0x8df;
	undefined field_0x8e0;
	undefined field_0x8e1;
	undefined field_0x8e2;
	undefined field_0x8e3;
	undefined field_0x8e4;
	undefined field_0x8e5;
	undefined field_0x8e6;
	undefined field_0x8e7;
	undefined field_0x8e8;
	undefined field_0x8e9;
	undefined field_0x8ea;
	undefined field_0x8eb;
	undefined field_0x8ec;
	undefined field_0x8ed;
	undefined field_0x8ee;
	undefined field_0x8ef;
	undefined field_0x8f0;
	undefined field_0x8f1;
	undefined field_0x8f2;
	undefined field_0x8f3;
	undefined field_0x8f4;
	undefined field_0x8f5;
	undefined field_0x8f6;
	undefined field_0x8f7;
	undefined field_0x8f8;
	undefined field_0x8f9;
	undefined field_0x8fa;
	undefined field_0x8fb;
	undefined field_0x8fc;
	undefined field_0x8fd;
	undefined field_0x8fe;
	undefined field_0x8ff;
	undefined field_0x900;
	undefined field_0x901;
	undefined field_0x902;
	undefined field_0x903;
	undefined field_0x904;
	undefined field_0x905;
	undefined field_0x906;
	undefined field_0x907;
	undefined field_0x908;
	undefined field_0x909;
	undefined field_0x90a;
	undefined field_0x90b;
	undefined field_0x90c;
	undefined field_0x90d;
	undefined field_0x90e;
	undefined field_0x90f;
	undefined field_0x910;
	undefined field_0x911;
	undefined field_0x912;
	undefined field_0x913;
	undefined field_0x914;
	undefined field_0x915;
	undefined field_0x916;
	undefined field_0x917;
	undefined field_0x918;
	undefined field_0x919;
	undefined field_0x91a;
	undefined field_0x91b;
	undefined field_0x91c;
	undefined field_0x91d;
	undefined field_0x91e;
	undefined field_0x91f;
	undefined field_0x920;
	undefined field_0x921;
	undefined field_0x922;
	undefined field_0x923;
	undefined field_0x924;
	undefined field_0x925;
	undefined field_0x926;
	undefined field_0x927;
	undefined field_0x928;
	undefined field_0x929;
	undefined field_0x92a;
	undefined field_0x92b;
	undefined field_0x92c;
	undefined field_0x92d;
	undefined field_0x92e;
	undefined field_0x92f;
	undefined field_0x930;
	undefined field_0x931;
	undefined field_0x932;
	undefined field_0x933;
	undefined field_0x934;
	undefined field_0x935;
	undefined field_0x936;
	undefined field_0x937;
	undefined field_0x938;
	undefined field_0x939;
	undefined field_0x93a;
	undefined field_0x93b;
	undefined field_0x93c;
	undefined field_0x93d;
	undefined field_0x93e;
	undefined field_0x93f;
	undefined field_0x940;
	undefined field_0x941;
	undefined field_0x942;
	undefined field_0x943;
	undefined field_0x944;
	undefined field_0x945;
	undefined field_0x946;
	undefined field_0x947;
	undefined field_0x948;
	undefined field_0x949;
	undefined field_0x94a;
	undefined field_0x94b;
	undefined field_0x94c;
	undefined field_0x94d;
	undefined field_0x94e;
	undefined field_0x94f;
	undefined field_0x950;
	undefined field_0x951;
	undefined field_0x952;
	undefined field_0x953;
	undefined field_0x954;
	undefined field_0x955;
	undefined field_0x956;
	undefined field_0x957;
	undefined field_0x958;
	undefined field_0x959;
	undefined field_0x95a;
	undefined field_0x95b;
	undefined field_0x95c;
	undefined field_0x95d;
	undefined field_0x95e;
	undefined field_0x95f;
	undefined field_0x960;
	undefined field_0x961;
	undefined field_0x962;
	undefined field_0x963;
	undefined field_0x964;
	undefined field_0x965;
	undefined field_0x966;
	undefined field_0x967;
	undefined field_0x968;
	undefined field_0x969;
	undefined field_0x96a;
	undefined field_0x96b;
	undefined field_0x96c;
	undefined field_0x96d;
	undefined field_0x96e;
	undefined field_0x96f;
	undefined field_0x970;
	undefined field_0x971;
	undefined field_0x972;
	undefined field_0x973;
	undefined field_0x974;
	undefined field_0x975;
	undefined field_0x976;
	undefined field_0x977;
	undefined field_0x978;
	undefined field_0x979;
	undefined field_0x97a;
	undefined field_0x97b;
	undefined field_0x97c;
	undefined field_0x97d;
	undefined field_0x97e;
	undefined field_0x97f;
	undefined field_0x980;
	undefined field_0x981;
	undefined field_0x982;
	undefined field_0x983;
	undefined field_0x984;
	undefined field_0x985;
	undefined field_0x986;
	undefined field_0x987;
	undefined field_0x988;
	undefined field_0x989;
	undefined field_0x98a;
	undefined field_0x98b;
	undefined field_0x98c;
	undefined field_0x98d;
	undefined field_0x98e;
	undefined field_0x98f;
	undefined field_0x990;
	undefined field_0x991;
	undefined field_0x992;
	undefined field_0x993;
	undefined field_0x994;
	undefined field_0x995;
	undefined field_0x996;
	undefined field_0x997;
	undefined field_0x998;
	undefined field_0x999;
	undefined field_0x99a;
	undefined field_0x99b;
	undefined field_0x99c;
	undefined field_0x99d;
	undefined field_0x99e;
	undefined field_0x99f;
	undefined field_0x9a0;
	undefined field_0x9a1;
	undefined field_0x9a2;
	undefined field_0x9a3;
	undefined field_0x9a4;
	undefined field_0x9a5;
	undefined field_0x9a6;
	undefined field_0x9a7;
	undefined field_0x9a8;
	undefined field_0x9a9;
	undefined field_0x9aa;
	undefined field_0x9ab;
	undefined field_0x9ac;
	undefined field_0x9ad;
	undefined field_0x9ae;
	undefined field_0x9af;
	undefined field_0x9b0;
	undefined field_0x9b1;
	undefined field_0x9b2;
	undefined field_0x9b3;
	undefined field_0x9b4;
	undefined field_0x9b5;
	undefined field_0x9b6;
	undefined field_0x9b7;
	undefined field_0x9b8;
	undefined field_0x9b9;
	undefined field_0x9ba;
	undefined field_0x9bb;
	undefined field_0x9bc;
	undefined field_0x9bd;
	undefined field_0x9be;
	undefined field_0x9bf;
	undefined field_0x9c0;
	undefined field_0x9c1;
	undefined field_0x9c2;
	undefined field_0x9c3;
	undefined field_0x9c4;
	undefined field_0x9c5;
	undefined field_0x9c6;
	undefined field_0x9c7;
	undefined field_0x9c8;
	undefined field_0x9c9;
	undefined field_0x9ca;
	undefined field_0x9cb;
	undefined field_0x9cc;
	undefined field_0x9cd;
	undefined field_0x9ce;
	undefined field_0x9cf;
	undefined field_0x9d0;
	undefined field_0x9d1;
	undefined field_0x9d2;
	undefined field_0x9d3;
	undefined field_0x9d4;
	undefined field_0x9d5;
	undefined field_0x9d6;
	undefined field_0x9d7;
	undefined field_0x9d8;
	undefined field_0x9d9;
	undefined field_0x9da;
	undefined field_0x9db;
	undefined field_0x9dc;
	undefined field_0x9dd;
	undefined field_0x9de;
	undefined field_0x9df;
	undefined field_0x9e0;
	undefined field_0x9e1;
	undefined field_0x9e2;
	undefined field_0x9e3;
	undefined field_0x9e4;
	undefined field_0x9e5;
	undefined field_0x9e6;
	undefined field_0x9e7;
	undefined field_0x9e8;
	undefined field_0x9e9;
	undefined field_0x9ea;
	undefined field_0x9eb;
	undefined field_0x9ec;
	undefined field_0x9ed;
	undefined field_0x9ee;
	undefined field_0x9ef;
	undefined field_0x9f0;
	undefined field_0x9f1;
	undefined field_0x9f2;
	undefined field_0x9f3;
	undefined field_0x9f4;
	undefined field_0x9f5;
	undefined field_0x9f6;
	undefined field_0x9f7;
	undefined field_0x9f8;
	undefined field_0x9f9;
	undefined field_0x9fa;
	undefined field_0x9fb;
	undefined field_0x9fc;
	undefined field_0x9fd;
	undefined field_0x9fe;
	undefined field_0x9ff;
	undefined field_0xa00;
	undefined field_0xa01;
	undefined field_0xa02;
	undefined field_0xa03;
	undefined field_0xa04;
	undefined field_0xa05;
	undefined field_0xa06;
	undefined field_0xa07;
	undefined field_0xa08;
	undefined field_0xa09;
	undefined field_0xa0a;
	undefined field_0xa0b;
	undefined field_0xa0c;
	undefined field_0xa0d;
	undefined field_0xa0e;
	undefined field_0xa0f;
	undefined field_0xa10;
	undefined field_0xa11;
	undefined field_0xa12;
	undefined field_0xa13;
	undefined field_0xa14;
	undefined field_0xa15;
	undefined field_0xa16;
	undefined field_0xa17;
	undefined field_0xa18;
	undefined field_0xa19;
	undefined field_0xa1a;
	undefined field_0xa1b;
	undefined field_0xa1c;
	undefined field_0xa1d;
	undefined field_0xa1e;
	undefined field_0xa1f;
	undefined field_0xa20;
	undefined field_0xa21;
	undefined field_0xa22;
	undefined field_0xa23;
	undefined field_0xa24;
	undefined field_0xa25;
	undefined field_0xa26;
	undefined field_0xa27;
	undefined field_0xa28;
	undefined field_0xa29;
	undefined field_0xa2a;
	undefined field_0xa2b;
	undefined field_0xa2c;
	undefined field_0xa2d;
	undefined field_0xa2e;
	undefined field_0xa2f;
	undefined field_0xa30;
	undefined field_0xa31;
	undefined field_0xa32;
	undefined field_0xa33;
	undefined field_0xa34;
	undefined field_0xa35;
	undefined field_0xa36;
	undefined field_0xa37;
	undefined field_0xa38;
	undefined field_0xa39;
	undefined field_0xa3a;
	undefined field_0xa3b;
	undefined field_0xa3c;
	undefined field_0xa3d;
	undefined field_0xa3e;
	undefined field_0xa3f;
	undefined field_0xa40;
	undefined field_0xa41;
	undefined field_0xa42;
	undefined field_0xa43;
	undefined field_0xa44;
	undefined field_0xa45;
	undefined field_0xa46;
	undefined field_0xa47;
	undefined field_0xa48;
	undefined field_0xa49;
	undefined field_0xa4a;
	undefined field_0xa4b;
	undefined field_0xa4c;
	undefined field_0xa4d;
	undefined field_0xa4e;
	undefined field_0xa4f;
	undefined field_0xa50;
	undefined field_0xa51;
	undefined field_0xa52;
	undefined field_0xa53;
	undefined field_0xa54;
	undefined field_0xa55;
	undefined field_0xa56;
	undefined field_0xa57;
	undefined field_0xa58;
	undefined field_0xa59;
	undefined field_0xa5a;
	undefined field_0xa5b;
	undefined field_0xa5c;
	undefined field_0xa5d;
	undefined field_0xa5e;
	undefined field_0xa5f;
	undefined field_0xa60;
	undefined field_0xa61;
	undefined field_0xa62;
	undefined field_0xa63;
	undefined field_0xa64;
	undefined field_0xa65;
	undefined field_0xa66;
	undefined field_0xa67;
	undefined field_0xa68;
	undefined field_0xa69;
	undefined field_0xa6a;
	undefined field_0xa6b;
	undefined field_0xa6c;
	undefined field_0xa6d;
	undefined field_0xa6e;
	undefined field_0xa6f;
	undefined field_0xa70;
	undefined field_0xa71;
	undefined field_0xa72;
	undefined field_0xa73;
	undefined field_0xa74;
	undefined field_0xa75;
	undefined field_0xa76;
	undefined field_0xa77;
	undefined field_0xa78;
	undefined field_0xa79;
	undefined field_0xa7a;
	undefined field_0xa7b;
	undefined field_0xa7c;
	undefined field_0xa7d;
	undefined field_0xa7e;
	undefined field_0xa7f;
	undefined field_0xa80;
	undefined field_0xa81;
	undefined field_0xa82;
	undefined field_0xa83;
	undefined field_0xa84;
	undefined field_0xa85;
	undefined field_0xa86;
	undefined field_0xa87;
	undefined field_0xa88;
	undefined field_0xa89;
	undefined field_0xa8a;
	undefined field_0xa8b;
	undefined field_0xa8c;
	undefined field_0xa8d;
	undefined field_0xa8e;
	undefined field_0xa8f;
	undefined field_0xa90;
	undefined field_0xa91;
	undefined field_0xa92;
	undefined field_0xa93;
	undefined field_0xa94;
	undefined field_0xa95;
	undefined field_0xa96;
	undefined field_0xa97;
	undefined field_0xa98;
	undefined field_0xa99;
	undefined field_0xa9a;
	undefined field_0xa9b;
	undefined field_0xa9c;
	undefined field_0xa9d;
	undefined field_0xa9e;
	undefined field_0xa9f;
	undefined field_0xaa0;
	undefined field_0xaa1;
	undefined field_0xaa2;
	undefined field_0xaa3;
	undefined field_0xaa4;
	undefined field_0xaa5;
	undefined field_0xaa6;
	undefined field_0xaa7;
	undefined field_0xaa8;
	undefined field_0xaa9;
	undefined field_0xaaa;
	undefined field_0xaab;
	undefined field_0xaac;
	undefined field_0xaad;
	undefined field_0xaae;
	undefined field_0xaaf;
};

typedef struct _CRuntime1_Globs _CRuntime1_Globs, *P_CRuntime1_Globs;

typedef uint size_t;

typedef int (* _PNH)(size_t);

struct _CRuntime1_Globs { // [tags:HIDDEN,STD,GLOBS] Contains internal C Runtime global variables (created just to collapse that annoying memory address from view in ghidra)
	undefined4 DAT_0054a0c8;
	undefined4 DAT_0054a0cc;
	errno_t errno;
	uint _doserrno;
	undefined4 DAT_0054a0d8;
	DWORD dwBuildNumbe;
	DWORD dwMajorMinorVersion;
	DWORD dwMinorVersion;
	DWORD dwMajorVersion;
	int __argc;
	char * * __argv;
	undefined4 field_0x2c;
	undefined4 DAT_0054a0f8;
	undefined4 DAT_0054a0fc;
	undefined4 DAT_0054a100;
	undefined4 field_0x3c;
	LPSTR _amodulefn;
	undefined4 field_0x44;
	undefined1 DAT_0054a110;
	undefined1 field_0x49[3];
	BOOL BOOL_0054a114;
	BOOL BOOL_0054a118;
	LPSTR __initenv;
	undefined4 field_0x58;
	undefined4 DAT_0054a124;
	undefined4 DAT_0054a128;
	undefined1 DAT_0054a12c;
	undefined1 field_0x65[3];
	undefined4 DAT_0054a130;
	undefined1 DAT_0054a134;
	undefined1 field_0x6d[3];
	undefined4 DAT_0054a138;
	undefined4 DAT_0054a13c;
	undefined8 field_0x78;
	undefined8 DAT_0054a148;
	undefined4 DAT_0054a150;
	BOOL _handlermode;
	_PNH _new_handler;
	undefined4 field_0x94;
	double DOUBLE_0054a160;
	undefined1 DAT_0054a168;
	undefined1 field_0xa1[7];
	undefined4 DAT_0054a170;
	undefined4 field_0xac;
	undefined4 DAT_0054a178;
	undefined4 field_0xb4;
	undefined4 DAT_0054a180;
	undefined4 field_0xbc[3];
	undefined4 DAT_0054a190;
	undefined4 DAT_0054a194;
	undefined4 DAT_0054a198;
	undefined4 DAT_0054a19c;
	undefined4 DAT_0054a1a0;
	undefined4 DAT_0054a1a4;
	char _amodulefn_buff[260];
	undefined4 field_0x1e4;
	int INT_0054a2b0;
	undefined4 field_0x1ec;
	char CHAR_ARRAY_0054a2b8[256];
	undefined4 field_0x2f0;
	undefined4 DAT_0054a3bc;
	undefined4 DAT_0054a3c0;
	undefined4 field_0x2fc;
	undefined4 DAT_0054a3c8;
	undefined4 DAT_0054a3cc;
	undefined4 DAT_0054a3d0;
	undefined4 DAT_0054a3d4;
	undefined4 DAT_0054a3d8;
	undefined4 field_0x314;
	undefined4 DAT_0054a3e0;
	int __unkCount_0054a3e4;
	char * __tmpFileBuffers_0054a3e8[2];
	undefined2 DAT_0054a3f0;
	undefined1 DAT_0054a3f2;
	undefined1 field_0x32b;
	undefined4 DAT_0054a3f4[7];
	undefined4 DAT_0054a410;
	undefined4 DAT_0054a414;
	undefined4 DAT_0054a418;
	undefined4 DAT_0054a41c;
	undefined4 DAT_0054a420;
	undefined4 DAT_0054a424;
	undefined4 DAT_0054a428;
	undefined4 DAT_0054a42c;
	undefined4 DAT_0054a430;
	undefined4 field_0x36c;
	undefined4 DAT_0054a438;
	undefined4 field_0x374;
	TIME_ZONE_INFORMATION lpTimeZoneInformation_0054a440;
	undefined4 DAT_0054a4ec;
	undefined4 DAT_0054a4f0;
	undefined4 DAT_0054a4f4;
	undefined4 DAT_0054a4f8;
	undefined4 DAT_0054a4fc;
	undefined4 DAT_0054a500;
	undefined4 DAT_0054a504;
	undefined8 field_0x440;
	undefined4 DAT_0054a510;
};

typedef struct SpiderWeb_Globs SpiderWeb_Globs, *PSpiderWeb_Globs;

typedef struct SpiderWeb_Block SpiderWeb_Block, *PSpiderWeb_Block;

typedef struct Lego_Level Lego_Level, *PLego_Level;

typedef enum SpiderWeb_BlockFlags { // [LegoRR/SpiderWeb.c|flags:0x4|type:uint]
	BLOCKWEB_FLAG_ACTIVE=256,
	BLOCKWEB_FLAG_NONE=0
} SpiderWeb_BlockFlags;

typedef struct EmergeTrigger EmergeTrigger, *PEmergeTrigger;

typedef struct Detail_Mesh Detail_Mesh, *PDetail_Mesh;

typedef struct RadarMap RadarMap, *PRadarMap;

typedef struct Lego_BlockActivity Lego_BlockActivity, *PLego_BlockActivity;

typedef struct Lego_Block Lego_Block, *PLego_Block;

typedef struct BlockPointer BlockPointer, *PBlockPointer;

typedef enum TextureType { // [LegoRR/dummy.c|enum:0x4|type:int|tags:HELPER,UNUSED]
	TEXTURES_ICE=2,
	TEXTURES_LAVA=1,
	TEXTURES_ROCK=0,
	TEXTURES__INVALID=4294967295
} TextureType;

typedef enum LevelStatus { // [LegoRR/Objective.c|enum:0x4|type:uint] Not sure if Objective...
	LEVELSTATUS_COMPLETE=1,
	LEVELSTATUS_FAILED=2,
	LEVELSTATUS_FAILED_CRYSTALS=3,
	LEVELSTATUS_FAILED_OTHER=4,
	LEVELSTATUS_INCOMPLETE=0
} LevelStatus;

typedef struct EmergeBlock EmergeBlock, *PEmergeBlock;

typedef struct Draw_Rect Draw_Rect, *PDraw_Rect;

typedef enum BlockActivityFlags { // [LegoRR/Lego.c|flags:0x1|type:byte] 0x1 does not directly affect other flags, 0x2 is used to remove the activity after destroying has finished.
	BLOCKACT_FLAG_DESTROYING=4,
	BLOCKACT_FLAG_NONE=0,
	BLOCKACT_FLAG_REMOVING=2,
	BLOCKACT_FLAG_STANDING=1
} BlockActivityFlags;

typedef enum Lego_PredugType { // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE]
	Lego_PredugType_Cavern_Exposed=1,
	Lego_PredugType_Cavern_Hidden=2,
	Lego_PredugType_SlugHole_Exposed=3,
	Lego_PredugType_SlugHole_Hidden=4,
	Lego_PredugType_Wall=0
} Lego_PredugType;

typedef enum Lego_SurfaceType8 { // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE] byte-sized alias for Lego_SurfaceType
	Lego_SurfaceType8_Cavern=17,
	Lego_SurfaceType8_CrystalSeam=10,
	Lego_SurfaceType8_Hard=2,
	Lego_SurfaceType8_Immovable=1,
	Lego_SurfaceType8_Lake=9,
	Lego_SurfaceType8_Lava=6,
	Lego_SurfaceType8_Loose=4,
	Lego_SurfaceType8_Medium=3,
	Lego_SurfaceType8_OreSeam=8,
	Lego_SurfaceType8_Path=14,
	Lego_SurfaceType8_RechargeSeam=11,
	Lego_SurfaceType8_Reinforcement=13,
	Lego_SurfaceType8_Rubble=12,
	Lego_SurfaceType8_SlugHole=15,
	Lego_SurfaceType8_Soil=5,
	Lego_SurfaceType8_Tunnel=0,
	Lego_SurfaceType8_Undiscovered=16,
	Lego_SurfaceType8_Water=7
} Lego_SurfaceType8;

typedef enum Lego_CryOreType { // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE]
	Lego_CryOreType_Crystal_Lv0_1=1,
	Lego_CryOreType_Crystal_Lv0_10=13,
	Lego_CryOreType_Crystal_Lv0_25=17,
	Lego_CryOreType_Crystal_Lv0_3=5,
	Lego_CryOreType_Crystal_Lv0_5=9,
	Lego_CryOreType_Crystal_Lv1_1=3,
	Lego_CryOreType_Crystal_Lv1_10=15,
	Lego_CryOreType_Crystal_Lv1_25=19,
	Lego_CryOreType_Crystal_Lv1_3=7,
	Lego_CryOreType_Crystal_Lv1_5=11,
	Lego_CryOreType_None=0,
	Lego_CryOreType_Ore_Lv01_10=16,
	Lego_CryOreType_Ore_Lv0_1=2,
	Lego_CryOreType_Ore_Lv0_10=14,
	Lego_CryOreType_Ore_Lv0_25=18,
	Lego_CryOreType_Ore_Lv0_3=6,
	Lego_CryOreType_Ore_Lv0_5=10,
	Lego_CryOreType_Ore_Lv1_1=4,
	Lego_CryOreType_Ore_Lv1_25=20,
	Lego_CryOreType_Ore_Lv1_3=8,
	Lego_CryOreType_Ore_Lv1_5=12
} Lego_CryOreType;

typedef enum Lego_ErodeType { // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE]
	Lego_ErodeType_Adjacent_Fast=7,
	Lego_ErodeType_Adjacent_Medium=5,
	Lego_ErodeType_Adjacent_Slow=3,
	Lego_ErodeType_Adjacent_VeryFast=9,
	Lego_ErodeType_Adjacent_VerySlow=1,
	Lego_ErodeType_None=0,
	Lego_ErodeType_Source_Fast=8,
	Lego_ErodeType_Source_Medium=6,
	Lego_ErodeType_Source_Slow=4,
	Lego_ErodeType_Source_VeryFast=10,
	Lego_ErodeType_Source_VerySlow=2
} Lego_ErodeType;

typedef enum BlockFlags1 { // [LegoRR/Lego.c|flags:0x4|type:uint]
	BLOCK1_BUILDINGPATH=32768,
	BLOCK1_BUILDINGSOLID=1024,
	BLOCK1_BUSY_FLOOR=524288,
	BLOCK1_BUSY_WALL=134217728,
	BLOCK1_CLEARED=2097152,
	BLOCK1_DESTROYEDCONNECTION=262144,
	BLOCK1_DIAGONAL=8192,
	BLOCK1_DIGREQUEST=8388608,
	BLOCK1_DOZERCLEARING=268435456,
	BLOCK1_ERODEACTIVE=2147483648,
	BLOCK1_EXPOSED=67108864,
	BLOCK1_EXPOSEDFLOORCHECKS=4194304,
	BLOCK1_FLOOR=8,
	BLOCK1_FOUNDATION=1048576,
	BLOCK1_HIDDEN=131072,
	BLOCK1_HIGHPOLY=256,
	BLOCK1_INCORNER=64,
	BLOCK1_LANDSLIDING=4096,
	BLOCK1_LAYEDPATH=1073741824,
	BLOCK1_NONE=0,
	BLOCK1_NOTHOT=512,
	BLOCK1_OUTCORNER=128,
	BLOCK1_PATH=536870912,
	BLOCK1_REINFORCED=32,
	BLOCK1_ROCKFALLFX=2048,
	BLOCK1_RUBBLE_FULL=3,
	BLOCK1_RUBBLE_LOW=1,
	BLOCK1_RUBBLE_MEDIUM=2,
	BLOCK1_SMOKE=16384,
	BLOCK1_SURVEYED=4,
	BLOCK1_UNUSED_PATHTYPE=16777216,
	BLOCK1_WALL=16
} BlockFlags1;

typedef enum BlockFlags2 { // [LegoRR/Lego.c|flags:0x4|type:uint]
	BLOCK2_DRAINPOWER_TEMP=2,
	BLOCK2_EMERGE_POINT=64,
	BLOCK2_EMERGE_TRIGGER=128,
	BLOCK2_ERODELOCKED=16,
	BLOCK2_FENCEREQUEST=8,
	BLOCK2_GENERATEPOWER=1,
	BLOCK2_NONE=0,
	BLOCK2_PATHSBUILTCOUNTED=1024,
	BLOCK2_POWERED=256,
	BLOCK2_SLUGHOLE_EXPOSED=32,
	BLOCK2_SLUGHOLE_HIDDEN=512,
	BLOCK2_TOOLSTORE=4
} BlockFlags2;

typedef struct Construction_Zone Construction_Zone, *PConstruction_Zone;

typedef struct Smoke Smoke, *PSmoke;

typedef enum Direction { // [common.c|enum:0x4|type:int]
	DIRECTION_DOWN=2,
	DIRECTION_LEFT=3,
	DIRECTION_RIGHT=1,
	DIRECTION_UP=0,
	DIRECTION__COUNT=4
} Direction;

typedef enum Construction_ZoneFlags { // [LegoRR/Construction.c|flags:0x4|type:uint]
	CONSTRUCTION_FLAG_LAYPATH=2,
	CONSTRUCTION_FLAG_NONE=0,
	CONSTRUCTION_FLAG_READY=1,
	CONSTRUCTION_FLAG_REQUESTED=4,
	CONSTRUCTION_FLAG_USESTUDS=8
} Construction_ZoneFlags;

typedef struct Smoke_Group Smoke_Group, *PSmoke_Group;

typedef struct ColourRGBF ColourRGBF, *PColourRGBF;

typedef enum SmokeFlags { // [LegoRR/Smoke.c|flags:0x4|type:uint] SMOKE_FLAG_UNK_4 is hopelessly broken, and impossible to reverse.
	SMOKE_FLAG_BROKEN_UNK_4=4,
	SMOKE_FLAG_HIDDEN=1,
	SMOKE_FLAG_NONE=0,
	SMOKE_FLAG_OWNCONTAINER=2,
	SMOKE_FLAG_REPEATCOUNT=8,
	SMOKE_FLAG_REPEATEND=16,
	SMOKE_FLAG_SFXFAILED=32
} SmokeFlags;

struct SpiderWeb_Globs { // [LegoRR/SpiderWeb.c|struct:0x8|tags:GLOBS]
	struct SpiderWeb_Block * webBlocks;
	struct Lego_Level * level;
};

struct Construction_Zone { // [LegoRR/Construction.c|struct:0xd4]
	LegoObject_ID objID; // Always used for Buildings, but for only for Paths in shared functions.
	enum Direction direction; // Direction of Building object when completed.
	uint handleValue; // Unique handle for this construction zone.
	struct Point2I originBlockPos; // Alternate handle to construction zone. Used as the primary tile for resource placement. Block position of Building object when completed.
	struct Point2I * shapeBlocks; // Only used by Buildings, transformed shape to match originBlockPos.
	uint shapeCount;
	uint requestCount; // Number of resources requested. Must be matched by placeCount to finish construction.
	uint placedCount;
	struct Construction_Zone * next; // Next in linked list.
	float float_28; // (ready: 125.0 , unused, possibly old timer for delay before construction)
	struct LegoObject * placedObjects[40];
	uint placedCount2; // Always identical to placedCount, no difference in usage.
	enum Construction_ZoneFlags flags;
};

struct ColourRGBF { // [common.c|struct:0xc]
	float red;
	float green;
	float blue;
};

struct Smoke_Group { // [LegoRR/Smoke.c|struct:0x3c]
	BOOL used;
	struct Vector3F randVec; // (init: Smoke_Group_Show, stored randomness applied to dirVec to get moveVec, unused)
	struct Vector3F moveVec; // (init: Smoke_Group_Show, readonly)
	struct Vector3F position; // (init: Container_GetPosition, updated)
	float float_28;
	float float_2c;
	float timer_30; // Count-up timer related to alpha (never used for anything).
	int int_34; // (random: [40,69]) Related to constant scalar 0.7f
	float timerUp_38; // Count-up timer (used for rendering).
};

struct Smoke { // [LegoRR/Smoke.c|struct:0x2a8]
	struct Smoke_Group groupList[10];
	float newSmokeTimer; // Countdown timer until another smoke group is added.
	struct Vector3F sfxOrigin; // Originating position of SFX when played in world.
	struct Vector3F dirVec; // Base move direction vector for smoke groups before randomness is applied.
	struct ColourRGBF colour;
	uint groupCount;
	int numRepeats; // (Dissipate) Number of repeats from 0-4 before vanishing.
	float animSpeed; // Speed of creating new groups and applied to movement speed.
	struct Container * cont; // Attached or created container for mesh.
	struct Mesh * mesh;
	enum SmokeFlags flags;
	struct Smoke * next; // Next Smoke in doubly-linked list.
	struct Smoke * previous; // Previous Smoke in doubly-linked list.
	enum SFX_ID sfxID;
	int sound3DPlayHandle;
};

struct RadarMap { // [LegoRR/RadarMap.c|struct:0x3c]
	struct Map3D * map;
	struct Area2F screenRect; // Passed value of (16.0f, 13.0f, 151.0f, 151.0f).
	float zoom; // Always assigned a value in the range [10,20], with 15 being the default. Higher values being more zoomed-in.
	float blockSize;
	struct Point2F centerPos;
	struct Area2F worldRect;
	struct Draw_Rect * drawRectList;
	uint drawRectCount;
};

struct BlockPointer { // [LegoRR/NERPs.c|struct:0xc]
	struct Point2I blockPos;
	struct BlockPointer * next; // Linked list of BlockPointers with same ID.
};

struct Detail_Mesh { // [LegoRR/Detail.c|struct:0x340]
	struct Container * promesh_ab[2];
	struct Container * clones_ab[2][100];
	float BlockSize;
	uint cloneCount;
	undefined field_0x330;
	undefined field_0x331;
	undefined field_0x332;
	undefined field_0x333;
	undefined field_0x334;
	undefined field_0x335;
	undefined field_0x336;
	undefined field_0x337;
	undefined field_0x338;
	undefined field_0x339;
	undefined field_0x33a;
	undefined field_0x33b;
	struct Detail_TextureSet * textureSet;
};

struct Lego_Block { // [LegoRR/Lego.c|struct:0x48|pack:1]
	enum Lego_PredugType predug;
	enum SurfaceTexture texture;
	enum Lego_SurfaceType8 terrain;
	byte direction; // clockwise (does not determine corner/wall type)
	byte blockpointer;
	enum Lego_CryOreType cryOre;
	enum Lego_ErodeType erodeSpeed;
	byte erodeLevel; // 0 = low, 1 = med, 2 = high, 3 = max, 4 = lava
	enum BlockFlags1 flags1;
	enum BlockFlags2 flags2;
	struct Construction_Zone * construct;
	float damage; // drill damage [0.0-1.0]
	struct Lego_BlockActivity * activity;
	struct Smoke * smoke;
	short randomness; // (sometimes sign-extended)
	ushort seamDigCount; // Number of times a seam has been dug (destroyed at 4).
	uint numLandSlides;
	uint clickCount;
	int generateCrystals;
	int generateOre;
	byte aiNode;
	undefined field_0x35;
	undefined field_0x36;
	undefined field_0x37;
	BOOL fallinUpper; // (fallin upper: 1 if fallin > 4)
	int fallinIntensity; // (fallin scale: 1-4)
	float fallinTimer; // (randomized with full fallin value)
	BOOL tutoHighlightState; // Tutorial block highlight color (false = tutorial color, true = normal).
};

struct EmergeBlock { // [LegoRR/Lego.c|struct:0xc]
	struct Point2I blockPos;
	BOOL used;
};

struct Lego_Level { // [LegoRR/Lego.c|struct:0x284]
	char * name; // (format: "Levels::level")
	struct Map3D * map;
	struct EmergeTrigger * emergeTriggers;
	uint emergeCount;
	undefined4 unused_rewardID; // Presumably used to lookup level rewards by some constant ID value.
	uint width;
	uint height;
	float BlockSize;
	float DigDepth;
	float RoofHeight;
	float RoughLevel;
	enum BoolTri UseRoof;
	enum BoolTri SafeCaverns;
	float SelBoxHeight;
	undefined4 field_0x38;
	undefined4 field_0x3c;
	undefined4 field_0x40;
	undefined4 field_0x44;
	undefined4 field_0x48;
	undefined4 field_0x4c;
	undefined4 field_0x50;
	undefined4 field_0x54;
	undefined4 field_0x58;
	undefined4 field_0x5c;
	undefined4 field_0x60;
	undefined4 field_0x64;
	undefined4 field_0x68;
	undefined4 field_0x6c;
	undefined4 field_0x70;
	struct Size2I textureSetSize; // surface texture width and height
	struct Detail_TextureSet * textureSet;
	struct Detail_Mesh * * promeshGrid;
	struct RadarMap * radarMap;
	struct Lego_BlockActivity * blockActLast; // Tail of doubly-linked list of block effects.
	int crystals; // (init: 0) Total number of Crystals stored.
	undefined4 unused_crystals_90; // (init: 0, unused) Presumably once for Crystals.
	int crystalsPickedUp; // (init: 0) Used by NERPs:GetCrystalsPickedUp.
	int crystalsDrained; // Crystals stored, but in-use powering buildings.
	int crystalsStolen; // For checking MaxStolen failure condition.
	int ore; // (init: 0) Total number of normal Ore stored. (EXCLUDES STUDS)
	undefined4 unused_ore_a4; // (init: 0, unused) Presumably once for Ore.
	int orePickedUp; // (init: 0) Used by NERPs:GetOrePickedUp.
	int studs; // (init: 0) Total number of Studs stored. (1 stud == 5 ore)
	int EmergeCreature; // (searches for Object ID by name, expects RockMonsterType)
	char * nextLevelID; // (cfg: NextLevel)
	struct Lego_Block * blocks; // grid of blocks [y][x]
	struct ObjectiveData objective;
	BOOL hasBlockPointers;
	struct BlockPointer * blockPointers[56];
	BOOL StartFP;
	BOOL NoDrain;
	float oxygenLevel; // (init: 100.0, Oxygen level?)
	float OxygenRate;
	float oxygenLevelMessage; // Tracks change in oxygen since the last message (new message after change of 5%).
	float BuildingTolerance; // (default: 4.0)
	float BuildingMaxVariation; // (default: 6.0)
	float UpgradeTimes[20]; // [objType] (mult: 25.0, 1:Vehicle, 2:MiniFigure, 3:Building)
	float TrainTime; // (mult: 25.0)
	float EmergeTimeOut; // (default: 1500.0)
	float SlugTime; // (default: 60.0, mult: 25.0 (applies to default))
	int Slug; // (default: 20 (invalid), searches for object index by name, expects RockMonsterType)
	char * FullName; // (replace '_' with ' ')
	enum TextureType BoulderAnimation; // (texture index, hardcoded: Rock, Lava, Ice)
	float MaxStolen;
	enum LevelStatus status; // (init: 0) 2 is used for Crystal failure as well
	BOOL IsStartTeleportEnabled; // (! DisableStartTeleport)
};

struct SpiderWeb_Block { // [LegoRR/SpiderWeb.c|struct:0xc]
	struct LegoObject * object; // "SpiderWeb" LiveObject
	float health; // Assumed as health, init: 100.0f
	enum SpiderWeb_BlockFlags flags;
};

struct Draw_Rect { // [Gods98/Draw.c|struct:0x1c]
	struct Area2F rect;
	float r;
	float g;
	float b;
};

struct Lego_BlockActivity { // [LegoRR/Lego.c|struct:0x1c] An effect or activity container attached to an individual block (only one per block max).
	struct Container * cont;
	struct Point2I blockPos;
	enum BlockActivityFlags flags; // (0x1=?, 0x2=?, 0x4=?)
	undefined field_0xd;
	undefined field_0xe;
	undefined field_0xf;
	struct Lego_BlockActivity * next;
	struct Lego_BlockActivity * previous;
	BOOL staticEffect; // (0 = reinforcement, 1 = recharge seam twinkle?)
};

struct EmergeTrigger { // [LegoRR/Lego.c|struct:0x4c]
	undefined4 field_0;
	struct Point2I blockPos;
	float timeout;
	struct EmergeBlock emergePoints[5];
};

typedef struct Front_Globs Front_Globs, *PFront_Globs;

typedef struct MenuSet MenuSet, *PMenuSet;

typedef struct LevelSet LevelSet, *PLevelSet;

typedef struct LevelLink LevelLink, *PLevelLink;

typedef struct Flic Flic, *PFlic;

typedef struct SaveData SaveData, *PSaveData;

typedef enum Front_RockWipeFlags { // [LegoRR/Front.c|flags:0x4|type:uint]
	ROCKWIPE_FLAG_ANIMATING=1,
	ROCKWIPE_FLAG_NOINPUT=2,
	ROCKWIPE_FLAG_NONE=0
} Front_RockWipeFlags;

typedef struct MenuTextWindow MenuTextWindow, *PMenuTextWindow;

typedef struct Menu Menu, *PMenu;

typedef enum FlicUserFlags { // [Gods98/Flic.c|flags:0x4|type:uint]
	FLICCATCHUPON=4,
	FLICDISK=0,
	FLICLOOPINGON=2,
	FLICMEMORY=1,
	FLICSOUNDOFF=8
} FlicUserFlags;

typedef struct ColourRGBPacked ColourRGBPacked, *PColourRGBPacked;

typedef struct FLICHEADERSTRUCT FLICHEADERSTRUCT, *PFLICHEADERSTRUCT;

typedef enum FlicDisplayMode { // [Gods98/Flic.c|enum:0x4|type:uint]
	FLICMODE_BYTEPERPIXEL=0,
	FLICMODE_HICOLOR=4,
	FLICMODE_MODEX=1,
	FLICMODE_PLANAR=2,
	FLICMODE_TRUECOLOR=3
} FlicDisplayMode;

typedef struct SaveStruct_18 SaveStruct_18, *PSaveStruct_18;

typedef struct SaveReward SaveReward, *PSaveReward;

typedef struct TextWindow TextWindow, *PTextWindow;

typedef struct MenuItem MenuItem, *PMenuItem;

typedef enum MenuFlags { // [LegoRR/FrontEnd.c|flags:0x4|type:uint]
	MENU_FLAG_CANSCROLL=2,
	MENU_FLAG_HASPOSITION=1,
	MENU_FLAG_NONE=0
} MenuFlags;

typedef struct MenuOverlay MenuOverlay, *PMenuOverlay;

typedef enum SaveRewardFlags { // [LegoRR/Rewards.c|flags:0x4|type:uint]
	SAVEREWARD_FLAG_COMPLETED=1,
	SAVEREWARD_FLAG_NONE=0,
	SAVEREWARD_FLAG_TUTORIAL=2
} SaveRewardFlags;

typedef struct RewardLevel RewardLevel, *PRewardLevel;

typedef union MenuItem_Data_union MenuItem_Data_union, *PMenuItem_Data_union;

typedef enum MenuItem_Type { // [LegoRR/FrontEnd.c|enum:0x4|type:int]
	MenuItem_Type_Count=7,
	MenuItem_Type_Cycle=0,
	MenuItem_Type_Invalid=4294967295,
	MenuItem_Type_Next=5,
	MenuItem_Type_RealSlider=4,
	MenuItem_Type_Select=6,
	MenuItem_Type_Slider=3,
	MenuItem_Type_TextInput=2,
	MenuItem_Type_Trigger=1
} MenuItem_Type;

typedef enum ToolTip_Type { // [LegoRR/ToolTip.c|enum:0x4|type:int]
	ToolTip_Back=34,
	ToolTip_CamControlCycle=26,
	ToolTip_CamControlCycleMinifigures=35,
	ToolTip_CamControlRotate=27,
	ToolTip_CamControlZoomIn=24,
	ToolTip_CamControlZoomOut=25,
	ToolTip_Close=30,
	ToolTip_Construction=3,
	ToolTip_FrontEnd_Back=38,
	ToolTip_InfoDockClose=16,
	ToolTip_InfoDockGoto=15,
	ToolTip_InfoMenuContinue=8,
	ToolTip_InfoMenuDisableFuture=9,
	ToolTip_InterfaceMenu=4,
	ToolTip_InterfaceMenuBackButton=5,
	ToolTip_MapBlock=6,
	ToolTip_More=33,
	ToolTip_NextMessage=32,
	ToolTip_Null=0,
	ToolTip_PreviousMessage=31,
	ToolTip_Priority=7,
	ToolTip_PriorityDisable=21,
	ToolTip_PriorityReset=23,
	ToolTip_PriorityUpOne=22,
	ToolTip_RadarBlock=1,
	ToolTip_RadarMapView=14,
	ToolTip_RadarObjectView=11,
	ToolTip_RadarToggle=10,
	ToolTip_RadarZoomIn=12,
	ToolTip_RadarZoomOut=13,
	ToolTip_Reward_Advance=37,
	ToolTip_Reward_Save=36,
	ToolTip_SideBar_Crystals=29,
	ToolTip_SideBar_Ore=28,
	ToolTip_TopPanelCallToArms=17,
	ToolTip_TopPanelInfo=18,
	ToolTip_TopPanelOptions=19,
	ToolTip_TopPanelPriorities=20,
	ToolTip_Type_Count=39,
	ToolTip_UnitSelect=2
} ToolTip_Type;

typedef enum MenuOverlay_Type { // [LegoRR/FrontEnd.c|enum:0x4|type:int] Based on extension: .flh (default), .avi, .bmp, .lws
	MenuOverlay_Type_Animation=1,
	MenuOverlay_Type_Count=4,
	MenuOverlay_Type_Flic=0,
	MenuOverlay_Type_Image=2,
	MenuOverlay_Type_Invalid=4294967295,
	MenuOverlay_Type_Lws=3
} MenuOverlay_Type;

typedef struct RewardBuildingCounts RewardBuildingCounts, *PRewardBuildingCounts;

typedef struct RewardLevelItem RewardLevelItem, *PRewardLevelItem;

typedef struct MenuItem_CycleData MenuItem_CycleData, *PMenuItem_CycleData;

typedef struct MenuItem_TriggerData MenuItem_TriggerData, *PMenuItem_TriggerData;

typedef struct MenuItem_TextInputData MenuItem_TextInputData, *PMenuItem_TextInputData;

typedef struct MenuItem_SliderData MenuItem_SliderData, *PMenuItem_SliderData;

typedef struct MenuItem_RealSliderData MenuItem_RealSliderData, *PMenuItem_RealSliderData;

typedef struct MenuItem_SelectData MenuItem_SelectData, *PMenuItem_SelectData;

typedef enum RewardItemFlags { // [LegoRR/Rewards.c|flags:0x4|type:uint]
	REWARDITEM_FLAG_BOXIMAGES=64,
	REWARDITEM_FLAG_FLIC=4,
	REWARDITEM_FLAG_IMAGES=2,
	REWARDITEM_FLAG_NAMETEXT=16,
	REWARDITEM_FLAG_NAMETEXT_HALFTRANS=32,
	REWARDITEM_FLAG_NONE=0,
	REWARDITEM_FLAG_VALUETEXT=1
} RewardItemFlags;

typedef void (* MenuItem_CycleCallback)(int);

typedef void (* MenuItem_TriggerCallback)(void);

typedef void (* MenuItem_SliderCallback)(int);

typedef void (* MenuItem_RealSliderCallback)(float);

typedef struct MenuItem_SelectItem MenuItem_SelectItem, *PMenuItem_SelectItem;

typedef void (* MenuItem_SelectCallback)(float, int);

typedef enum MenuItem_SelectItemFlags { // [LegoRR/FrontEnd.c|flags:0x4|type:uint]
	SELECTITEM_FLAG_ENABLED=4,
	SELECTITEM_FLAG_HASBANNER=1,
	SELECTITEM_FLAG_HASIMAGE=2,
	SELECTITEM_FLAG_NONE=0
} MenuItem_SelectItemFlags;

struct SaveStruct_18 { // [LegoRR/save.c|struct:0x18]
	undefined field_0x0;
	undefined field_0x1;
	undefined field_0x2;
	undefined field_0x3;
	undefined field_0x4;
	undefined field_0x5;
	undefined field_0x6;
	undefined field_0x7;
	undefined field_0x8;
	undefined field_0x9;
	undefined field_0xa;
	undefined field_0xb;
	undefined field_0xc;
	undefined field_0xd;
	undefined field_0xe;
	undefined field_0xf;
	undefined field_0x10;
	undefined field_0x11;
	undefined field_0x12;
	undefined field_0x13;
	undefined field_0x14;
	undefined field_0x15;
	undefined field_0x16;
	undefined field_0x17;
};

struct MenuItem_SliderData { // [LegoRR/FrontEnd.c|struct:0x38]
	int * valuePtr;
	int valueMin; // (cfg: Slider:[6])
	int valueMax; // (cfg: Slider:[7])
	int x2; // (cfg: Slider:[3])
	int y2; // (cfg: Slider:[4])
	MenuItem_SliderCallback callback;
	struct Image * imageBarOff; // (cfg: Slider:[8] "OffBar")
	struct Image * imageBarOn; // (cfg: Slider:[9] "OnBar")
	struct Image * imageCapLeft; // (cfg: Slider:[10] "Leftcap")
	struct Image * imageCapRight; // (cfg: Slider:[11] "Rightcap")
	struct Image * imagePlusLo; // (cfg: Slider:[12] "Plus")
	struct Image * imageMinusLo; // (cfg: Slider:[13] "Minus")
	struct Image * imagePlusHi; // (cfg: Slider:[14] "PlusHi")
	struct Image * imageMinusHi; // (cfg: Slider:[15] "MinusHi")
};

struct SaveData { // [LegoRR/save.c|struct:0xb8]
	undefined4 field_0x0;
	int SliderMusicVolume;
	int SliderSoundVolume;
	int SliderGameSpeed;
	int SliderBrightness;
	undefined4 field_0x14;
	uint missionsCount;
	struct SaveStruct_18 saveStruct18_1c;
	struct SaveReward * missionsTable; // std::malloc(count_18 * 0x3190)
	undefined4 field_0x38;
	undefined4 field_0x3c;
	undefined4 field_0x40;
	undefined4 field_0x44;
	undefined4 field_0x48;
	undefined4 field_0x4c;
	undefined4 field_0x50;
	undefined4 field_0x54;
	undefined4 field_0x58;
	undefined4 field_0x5c;
	undefined4 field_0x60;
	undefined4 field_0x64;
	undefined4 field_0x68;
	undefined4 field_0x6c;
	undefined4 field_0x70;
	undefined4 field_0x74;
	undefined4 field_0x78;
	undefined4 field_0x7c;
	undefined4 field_0x80;
	undefined4 field_0x84;
	undefined4 field_0x88;
	undefined4 field_0x8c;
	undefined4 field_0x90;
	undefined4 field_0x94;
	undefined4 field_0x98;
	undefined4 field_0x9c;
	undefined4 field_0xa0;
	undefined4 field_0xa4;
	undefined4 field_0xa8;
	undefined4 field_0xac;
	undefined4 field_0xb0;
	undefined4 field_0xb4;
};

struct LevelSet { // [LegoRR/FrontEnd.c|struct:0x14]
	int count;
	char * * idNames;
	char * * langNames;
	struct LevelLink * * levels;
	BOOL * visitedList; // True if this level has been loaded from level links (probably makes them require unlock)
};

struct Front_Globs { // [LegoRR/FrontEnd.c|struct:0x884|tags:GLOBS]
	struct MenuSet * pausedMenuSet; // (cfg: Menu::PausedMenu)
	struct MenuSet * mainMenuSet; // (cfg: Menu::MainMenuFull)
	struct MenuSet * optionsMenuSet; // (cfg: Menu::OptionsMenu)
	struct MenuSet * saveMenuSet; // (cfg: Menu::SaveMenu)
	struct LevelSet tutorialLevels; // (cfg: Main::TutorialStartLevel)
	struct LevelSet missionLevels; // (cfg: Main::StartLevel)
	struct LevelLink * startMissionLink; // (cfg: Main::StartLevel)
	struct LevelLink * startTutorialLink; // (cfg: Main::TutorialStartLevel)
	undefined8 reserved1a;
	undefined8 reserved1b; // (split up to prevent auto-field detection as array access)
	int triggerCredits; // [trigger: 1=play credits]
	undefined8 reserved2;
	int triggerQuitApp; // [trigger: 1=yes quit game]
	int selectMissionIndex; // [select: -1, or pressed mission item index]
	int selectTutorialIndex; // [select: -1, or pressed tutorial item index]
	int selectLoadSaveIndex; // [select: -1, or pressed save item index]
	int triggerContinueMission; // [trigger: 1=close pause menu]
	int sliderGameSpeed; // [slider: 0-5]
	int sliderSFXVolume; // [slider: 0-10]
	int sliderMusicVolume; // [slider: 0-10]
	int sliderBrightness; // [slider: 0-10]
	int cycleHelpWindow; // [cycle: Off,On]
	int triggerReplayObjective; // [trigger: 1=replay]
	int triggerQuitMission; // [trigger: 1=quit level]
	int triggerRestartMission; // [trigger: 1=restart level]
	int cycleWallDetail; // [cycle: High,Low]
	int cycleMusicOn; // [cycle: On,Off]
	int cycleSFXOn; // [cycle: On,Off]
	int cycleAutoGameSpeed; // [cycle: On,Off]
	int triggerBackSave; // [trigger: 1=leave save menu]
	struct Point2I overlayPosition;
	struct Flic * overlayImageOrFlic; // Image* or Flic* type
	uint overlayStartTime; // starting Main_GetTime (milliseconds)
	uint overlayCurrTime; // current Main_GetTime (milliseconds)
	struct Font * versionFont; // (file: bmpMbriefFONT2)
	char * versionString; // (cfg: Main::Version)
	struct SaveData saveData[6];
	int saveNumber;
	char * strDefaultLevelBMPS; // (cfg: Menu::DefaultLevelBMPS) memory storage
	undefined4 reserved3;
	struct Point2I scrollOffset; // Offset position in level select (or anywhere else with a larger menu image)
	undefined4 reserved4[2];
	struct Container * rockWipeAnim;
	enum Front_RockWipeFlags rockWipeFlags;
	float rockWipeTimer; // RockWipe animation timer in animation frames units.
	float rockWipeLastUpdateTime; // Main_GetTime should NEVER be stored as a float
	struct Container * rockWipeLight;
	BOOL saveMenuHasNoData;
	BOOL saveMenuHasSaved; // True when leaving the save menu without using the back button.
	BOOL saveMenuKeepOpen; // Used in a loop to continue showing the save menu.
	struct Size2I saveImageBigSize;
	char langLoadGame[64];
	char langSaveGame[64];
	struct MenuTextWindow * saveTextWnd;
	struct MenuTextWindow * saveLevelWnd;
	char langOverwriteTitle[128];
	char langOverwriteMessage[256];
	char langOverwriteOK[128];
	char langOverwriteCancel[128];
	BOOL shouldClearUnlockedLevels;
	undefined4 reserved5;
	undefined4 unused_zero_864; // (init: 0) Set to 0 and never touched?
	int maxLevelScreens;
	undefined4 reserved6[2];
	uint levelSelectHoverNumber;
	uint levelSelectLastNumber;
	BOOL levelSelectSFXStopped;
	float levelSelectSFXTimer;
};

struct MenuOverlay { // [LegoRR/FrontEnd.c|struct:0x20]
	char * filename;
	enum MenuOverlay_Type overlayType; // (.flh, .bmp, .avi, .lws)
	undefined4 field_8;
	struct Point2I position;
	enum SFX_ID sfxType;
	struct MenuOverlay * previous;
	undefined4 field_1c;
};

struct RewardBuildingCounts { // [LegoRR/Rewards.c|struct:0x198]
	char * nameTable[100];
	uint count;
	uint numPrevLevels_unk;
};

struct RewardLevelItem { // [LegoRR/Rewards.c|struct:0x210]
	enum RewardItemFlags flags; // (0x4 = flic)
	char name[32];
	float Importance;
	int Quota;
	undefined field_0x2c;
	undefined field_0x2d;
	undefined field_0x2e;
	undefined field_0x2f;
	float countdownRatio; // Elapsed / Countdown Timers
	float countdown; // Countdown timer
	float percentFloat;
	uint numGenerated;
	uint numDestroyed;
	uint numAttacked; // For every weapon attack
	float damageTaken;
	undefined field_0x4c;
	undefined field_0x4d;
	undefined field_0x4e;
	undefined field_0x4f;
	int percentInt;
	char Text[128]; // (TODO: size me)
	char valueText[128];
	struct Point2I TextPosition;
	struct Point2I ImagePosition;
	struct Point2I BoxImagePosition;
	char FlicName[128]; // (TODO: size me)
	struct Size2I FlicSize;
	struct Point2I FlicPosition;
	struct Flic * Flic;
	struct Image * Image;
	struct Font * Font;
	char * SoundName;
	struct Image * BoxImage;
};

struct RewardLevel { // [LegoRR/Rewards.c|struct:0x318c]
	BOOL Enabled;
	BOOL saveHasCapture;
	struct Image saveCaptureImage;
	struct RewardBuildingCounts buildingCounts;
	int Modifier;
	undefined field_0x1c4;
	undefined field_0x1c5;
	undefined field_0x1c6;
	undefined field_0x1c7;
	undefined4 field_1c8;
	uint uintConstructCount_1cc;
	uint uintConstruct_1d0;
	char buildingNameBuffers[100][64];
	undefined field_0x1ad4;
	undefined field_0x1ad5;
	undefined field_0x1ad6;
	undefined field_0x1ad7;
	undefined field_0x1ad8;
	undefined field_0x1ad9;
	undefined field_0x1ada;
	undefined field_0x1adb;
	undefined field_0x1adc;
	undefined field_0x1add;
	undefined field_0x1ade;
	undefined field_0x1adf;
	undefined field_0x1ae0;
	undefined field_0x1ae1;
	undefined field_0x1ae2;
	undefined field_0x1ae3;
	undefined field_0x1ae4;
	undefined field_0x1ae5;
	undefined field_0x1ae6;
	undefined field_0x1ae7;
	undefined field_0x1ae8;
	undefined field_0x1ae9;
	undefined field_0x1aea;
	undefined field_0x1aeb;
	undefined field_0x1aec;
	undefined field_0x1aed;
	undefined field_0x1aee;
	undefined field_0x1aef;
	undefined field_0x1af0;
	undefined field_0x1af1;
	undefined field_0x1af2;
	undefined field_0x1af3;
	undefined field_0x1af4;
	undefined field_0x1af5;
	undefined field_0x1af6;
	undefined field_0x1af7;
	undefined field_0x1af8;
	undefined field_0x1af9;
	undefined field_0x1afa;
	undefined field_0x1afb;
	undefined field_0x1afc;
	undefined field_0x1afd;
	undefined field_0x1afe;
	undefined field_0x1aff;
	undefined field_0x1b00;
	undefined field_0x1b01;
	undefined field_0x1b02;
	undefined field_0x1b03;
	float float_1b04;
	float float_1b08;
	float float_1b0c;
	undefined field_0x1b10;
	undefined field_0x1b11;
	undefined field_0x1b12;
	undefined field_0x1b13;
	undefined field_0x1b14;
	undefined field_0x1b15;
	undefined field_0x1b16;
	undefined field_0x1b17;
	undefined field_0x1b18;
	undefined field_0x1b19;
	undefined field_0x1b1a;
	undefined field_0x1b1b;
	undefined field_0x1b1c;
	undefined field_0x1b1d;
	undefined field_0x1b1e;
	undefined field_0x1b1f;
	undefined field_0x1b20;
	undefined field_0x1b21;
	undefined field_0x1b22;
	undefined field_0x1b23;
	undefined field_0x1b24;
	undefined field_0x1b25;
	undefined field_0x1b26;
	undefined field_0x1b27;
	undefined field_0x1b28;
	undefined field_0x1b29;
	undefined field_0x1b2a;
	undefined field_0x1b2b;
	undefined field_0x1b2c;
	undefined field_0x1b2d;
	undefined field_0x1b2e;
	undefined field_0x1b2f;
	undefined field_0x1b30;
	undefined field_0x1b31;
	undefined field_0x1b32;
	undefined field_0x1b33;
	undefined field_0x1b34;
	undefined field_0x1b35;
	undefined field_0x1b36;
	undefined field_0x1b37;
	undefined field_0x1b38;
	undefined field_0x1b39;
	undefined field_0x1b3a;
	undefined field_0x1b3b;
	undefined field_0x1b3c;
	undefined field_0x1b3d;
	undefined field_0x1b3e;
	undefined field_0x1b3f;
	undefined field_0x1b40;
	undefined field_0x1b41;
	undefined field_0x1b42;
	undefined field_0x1b43;
	undefined field_0x1b44;
	undefined field_0x1b45;
	undefined field_0x1b46;
	undefined field_0x1b47;
	undefined field_0x1b48;
	undefined field_0x1b49;
	undefined field_0x1b4a;
	undefined field_0x1b4b;
	undefined field_0x1b4c;
	undefined field_0x1b4d;
	undefined field_0x1b4e;
	undefined field_0x1b4f;
	undefined field_0x1b50;
	undefined field_0x1b51;
	undefined field_0x1b52;
	undefined field_0x1b53;
	undefined field_0x1b54;
	undefined field_0x1b55;
	undefined field_0x1b56;
	undefined field_0x1b57;
	undefined field_0x1b58;
	undefined field_0x1b59;
	undefined field_0x1b5a;
	undefined field_0x1b5b;
	undefined field_0x1b5c;
	undefined field_0x1b5d;
	undefined field_0x1b5e;
	undefined field_0x1b5f;
	undefined field_0x1b60;
	undefined field_0x1b61;
	undefined field_0x1b62;
	undefined field_0x1b63;
	undefined field_0x1b64;
	undefined field_0x1b65;
	undefined field_0x1b66;
	undefined field_0x1b67;
	undefined field_0x1b68;
	undefined field_0x1b69;
	undefined field_0x1b6a;
	undefined field_0x1b6b;
	undefined field_0x1b6c;
	undefined field_0x1b6d;
	undefined field_0x1b6e;
	undefined field_0x1b6f;
	undefined field_0x1b70;
	undefined field_0x1b71;
	undefined field_0x1b72;
	undefined field_0x1b73;
	undefined field_0x1b74;
	undefined field_0x1b75;
	undefined field_0x1b76;
	undefined field_0x1b77;
	undefined field_0x1b78;
	undefined field_0x1b79;
	undefined field_0x1b7a;
	undefined field_0x1b7b;
	undefined field_0x1b7c;
	undefined field_0x1b7d;
	undefined field_0x1b7e;
	undefined field_0x1b7f;
	undefined field_0x1b80;
	undefined field_0x1b81;
	undefined field_0x1b82;
	undefined field_0x1b83;
	undefined field_0x1b84;
	undefined field_0x1b85;
	undefined field_0x1b86;
	undefined field_0x1b87;
	undefined field_0x1b88;
	undefined field_0x1b89;
	undefined field_0x1b8a;
	undefined field_0x1b8b;
	undefined field_0x1b8c;
	undefined field_0x1b8d;
	undefined field_0x1b8e;
	undefined field_0x1b8f;
	undefined field_0x1b90;
	undefined field_0x1b91;
	undefined field_0x1b92;
	undefined field_0x1b93;
	undefined field_0x1b94;
	undefined field_0x1b95;
	undefined field_0x1b96;
	undefined field_0x1b97;
	undefined field_0x1b98;
	undefined field_0x1b99;
	undefined field_0x1b9a;
	undefined field_0x1b9b;
	undefined field_0x1b9c;
	undefined field_0x1b9d;
	undefined field_0x1b9e;
	undefined field_0x1b9f;
	undefined field_0x1ba0;
	undefined field_0x1ba1;
	undefined field_0x1ba2;
	undefined field_0x1ba3;
	undefined field_0x1ba4;
	undefined field_0x1ba5;
	undefined field_0x1ba6;
	undefined field_0x1ba7;
	undefined field_0x1ba8;
	undefined field_0x1ba9;
	undefined field_0x1baa;
	undefined field_0x1bab;
	undefined field_0x1bac;
	undefined field_0x1bad;
	undefined field_0x1bae;
	undefined field_0x1baf;
	undefined field_0x1bb0;
	undefined field_0x1bb1;
	undefined field_0x1bb2;
	undefined field_0x1bb3;
	undefined field_0x1bb4;
	undefined field_0x1bb5;
	undefined field_0x1bb6;
	undefined field_0x1bb7;
	undefined field_0x1bb8;
	undefined field_0x1bb9;
	undefined field_0x1bba;
	undefined field_0x1bbb;
	undefined field_0x1bbc;
	undefined field_0x1bbd;
	undefined field_0x1bbe;
	undefined field_0x1bbf;
	undefined field_0x1bc0;
	undefined field_0x1bc1;
	undefined field_0x1bc2;
	undefined field_0x1bc3;
	undefined field_0x1bc4;
	undefined field_0x1bc5;
	undefined field_0x1bc6;
	undefined field_0x1bc7;
	undefined field_0x1bc8;
	undefined field_0x1bc9;
	undefined field_0x1bca;
	undefined field_0x1bcb;
	undefined field_0x1bcc;
	undefined field_0x1bcd;
	undefined field_0x1bce;
	undefined field_0x1bcf;
	undefined field_0x1bd0;
	undefined field_0x1bd1;
	undefined field_0x1bd2;
	undefined field_0x1bd3;
	undefined field_0x1bd4;
	undefined field_0x1bd5;
	undefined field_0x1bd6;
	undefined field_0x1bd7;
	undefined field_0x1bd8;
	undefined field_0x1bd9;
	undefined field_0x1bda;
	undefined field_0x1bdb;
	undefined field_0x1bdc;
	undefined field_0x1bdd;
	undefined field_0x1bde;
	undefined field_0x1bdf;
	undefined field_0x1be0;
	undefined field_0x1be1;
	undefined field_0x1be2;
	undefined field_0x1be3;
	undefined field_0x1be4;
	undefined field_0x1be5;
	undefined field_0x1be6;
	undefined field_0x1be7;
	undefined field_0x1be8;
	undefined field_0x1be9;
	undefined field_0x1bea;
	undefined field_0x1beb;
	undefined field_0x1bec;
	undefined field_0x1bed;
	undefined field_0x1bee;
	undefined field_0x1bef;
	undefined field_0x1bf0;
	undefined field_0x1bf1;
	undefined field_0x1bf2;
	undefined field_0x1bf3;
	undefined field_0x1bf4;
	undefined field_0x1bf5;
	undefined field_0x1bf6;
	undefined field_0x1bf7;
	undefined field_0x1bf8;
	undefined field_0x1bf9;
	undefined field_0x1bfa;
	undefined field_0x1bfb;
	undefined field_0x1bfc;
	undefined field_0x1bfd;
	undefined field_0x1bfe;
	undefined field_0x1bff;
	undefined field_0x1c00;
	undefined field_0x1c01;
	undefined field_0x1c02;
	undefined field_0x1c03;
	undefined field_0x1c04;
	undefined field_0x1c05;
	undefined field_0x1c06;
	undefined field_0x1c07;
	undefined field_0x1c08;
	undefined field_0x1c09;
	undefined field_0x1c0a;
	undefined field_0x1c0b;
	undefined field_0x1c0c;
	undefined field_0x1c0d;
	undefined field_0x1c0e;
	undefined field_0x1c0f;
	undefined field_0x1c10;
	undefined field_0x1c11;
	undefined field_0x1c12;
	undefined field_0x1c13;
	undefined field_0x1c14;
	undefined field_0x1c15;
	undefined field_0x1c16;
	undefined field_0x1c17;
	undefined field_0x1c18;
	undefined field_0x1c19;
	undefined field_0x1c1a;
	undefined field_0x1c1b;
	undefined field_0x1c1c;
	undefined field_0x1c1d;
	undefined field_0x1c1e;
	undefined field_0x1c1f;
	undefined field_0x1c20;
	undefined field_0x1c21;
	undefined field_0x1c22;
	undefined field_0x1c23;
	undefined field_0x1c24;
	undefined field_0x1c25;
	undefined field_0x1c26;
	undefined field_0x1c27;
	undefined field_0x1c28;
	undefined field_0x1c29;
	undefined field_0x1c2a;
	undefined field_0x1c2b;
	undefined field_0x1c2c;
	undefined field_0x1c2d;
	undefined field_0x1c2e;
	undefined field_0x1c2f;
	undefined field_0x1c30;
	undefined field_0x1c31;
	undefined field_0x1c32;
	undefined field_0x1c33;
	undefined field_0x1c34;
	undefined field_0x1c35;
	undefined field_0x1c36;
	undefined field_0x1c37;
	undefined field_0x1c38;
	undefined field_0x1c39;
	undefined field_0x1c3a;
	undefined field_0x1c3b;
	undefined field_0x1c3c;
	undefined field_0x1c3d;
	undefined field_0x1c3e;
	undefined field_0x1c3f;
	undefined field_0x1c40;
	undefined field_0x1c41;
	undefined field_0x1c42;
	undefined field_0x1c43;
	undefined field_0x1c44;
	undefined field_0x1c45;
	undefined field_0x1c46;
	undefined field_0x1c47;
	undefined field_0x1c48;
	undefined field_0x1c49;
	undefined field_0x1c4a;
	undefined field_0x1c4b;
	undefined field_0x1c4c;
	undefined field_0x1c4d;
	undefined field_0x1c4e;
	undefined field_0x1c4f;
	undefined field_0x1c50;
	undefined field_0x1c51;
	undefined field_0x1c52;
	undefined field_0x1c53;
	undefined field_0x1c54;
	undefined field_0x1c55;
	undefined field_0x1c56;
	undefined field_0x1c57;
	undefined field_0x1c58;
	undefined field_0x1c59;
	undefined field_0x1c5a;
	undefined field_0x1c5b;
	undefined field_0x1c5c;
	undefined field_0x1c5d;
	undefined field_0x1c5e;
	undefined field_0x1c5f;
	undefined field_0x1c60;
	undefined field_0x1c61;
	undefined field_0x1c62;
	undefined field_0x1c63;
	undefined field_0x1c64;
	undefined field_0x1c65;
	undefined field_0x1c66;
	undefined field_0x1c67;
	undefined field_0x1c68;
	undefined field_0x1c69;
	undefined field_0x1c6a;
	undefined field_0x1c6b;
	undefined field_0x1c6c;
	undefined field_0x1c6d;
	undefined field_0x1c6e;
	undefined field_0x1c6f;
	undefined field_0x1c70;
	undefined field_0x1c71;
	undefined field_0x1c72;
	undefined field_0x1c73;
	undefined field_0x1c74;
	undefined field_0x1c75;
	undefined field_0x1c76;
	undefined field_0x1c77;
	undefined field_0x1c78;
	undefined field_0x1c79;
	undefined field_0x1c7a;
	undefined field_0x1c7b;
	undefined field_0x1c7c;
	undefined field_0x1c7d;
	undefined field_0x1c7e;
	undefined field_0x1c7f;
	undefined field_0x1c80;
	undefined field_0x1c81;
	undefined field_0x1c82;
	undefined field_0x1c83;
	undefined field_0x1c84;
	undefined field_0x1c85;
	undefined field_0x1c86;
	undefined field_0x1c87;
	undefined field_0x1c88;
	undefined field_0x1c89;
	undefined field_0x1c8a;
	undefined field_0x1c8b;
	undefined field_0x1c8c;
	undefined field_0x1c8d;
	undefined field_0x1c8e;
	undefined field_0x1c8f;
	undefined field_0x1c90;
	undefined field_0x1c91;
	undefined field_0x1c92;
	undefined field_0x1c93;
	undefined field_0x1c94;
	undefined field_0x1c95;
	undefined field_0x1c96;
	undefined field_0x1c97;
	undefined field_0x1c98;
	undefined field_0x1c99;
	undefined field_0x1c9a;
	undefined field_0x1c9b;
	undefined field_0x1c9c;
	undefined field_0x1c9d;
	undefined field_0x1c9e;
	undefined field_0x1c9f;
	undefined field_0x1ca0;
	undefined field_0x1ca1;
	undefined field_0x1ca2;
	undefined field_0x1ca3;
	undefined field_0x1ca4;
	undefined field_0x1ca5;
	undefined field_0x1ca6;
	undefined field_0x1ca7;
	undefined field_0x1ca8;
	undefined field_0x1ca9;
	undefined field_0x1caa;
	undefined field_0x1cab;
	undefined field_0x1cac;
	undefined field_0x1cad;
	undefined field_0x1cae;
	undefined field_0x1caf;
	undefined field_0x1cb0;
	undefined field_0x1cb1;
	undefined field_0x1cb2;
	undefined field_0x1cb3;
	undefined field_0x1cb4;
	undefined field_0x1cb5;
	undefined field_0x1cb6;
	undefined field_0x1cb7;
	undefined field_0x1cb8;
	undefined field_0x1cb9;
	undefined field_0x1cba;
	undefined field_0x1cbb;
	undefined field_0x1cbc;
	undefined field_0x1cbd;
	undefined field_0x1cbe;
	undefined field_0x1cbf;
	undefined field_0x1cc0;
	undefined field_0x1cc1;
	undefined field_0x1cc2;
	undefined field_0x1cc3;
	undefined field_0x1cc4;
	undefined field_0x1cc5;
	undefined field_0x1cc6;
	undefined field_0x1cc7;
	undefined field_0x1cc8;
	undefined field_0x1cc9;
	undefined field_0x1cca;
	undefined field_0x1ccb;
	undefined field_0x1ccc;
	undefined field_0x1ccd;
	undefined field_0x1cce;
	undefined field_0x1ccf;
	undefined field_0x1cd0;
	undefined field_0x1cd1;
	undefined field_0x1cd2;
	undefined field_0x1cd3;
	undefined field_0x1cd4;
	undefined field_0x1cd5;
	undefined field_0x1cd6;
	undefined field_0x1cd7;
	undefined field_0x1cd8;
	undefined field_0x1cd9;
	undefined field_0x1cda;
	undefined field_0x1cdb;
	undefined field_0x1cdc;
	undefined field_0x1cdd;
	undefined field_0x1cde;
	undefined field_0x1cdf;
	undefined field_0x1ce0;
	undefined field_0x1ce1;
	undefined field_0x1ce2;
	undefined field_0x1ce3;
	int itemCount; // (init: 10)
	struct RewardLevelItem * itemPtr; // (init: &items_TABLE)
	struct RewardLevelItem items[10];
};

struct ColourRGBPacked { // [common.c|struct:0x3|pack:1]
	byte red;
	byte green;
	byte blue;
};

struct FLICHEADERSTRUCT { // [Gods98/Flic.c|struct:0x88]
	int size; // Size of FLIC including this header
	ushort magic; // File type [0x1234, 0x9119, 0xaf11, 0xaf12, 0xaf43]
	ushort frames; // Number of frames in first segment
	ushort width; // FLIC width in pixels
	ushort height; // FLIC height in pixels
	ushort depth; // Bits per pixel (usually 8)
	ushort flags; // Set to zero or to three
	ushort speed; // Delay between frames
	ushort padding1;
	int next;
	int frit;
	char expand[82];
	ushort padding2;
	int NewPack;
	int SoundID;
	int SoundRate;
	char SoundChannels;
	char SoundBPS;
	ushort padding3;
	int SoundChunkSize;
	short SoundNumPreRead;
	ushort padding4;
};

struct Flic { // [Gods98/Flic.c|struct:0x6e8] (official: FLICSTRUCT)
	enum FlicUserFlags userflags;
	int fsXc; // (init: 0)
	int fsYc; // (init: 0)
	int fsXsize;
	int fsYsize;
	byte * rambufferhandle;
	byte * destportalhandle;
	char filename[256];
	struct ColourRGBPacked fsPalette256[256];
	ushort fsPalette64k[256];
	int framerate; // (init: 0x190000)
	int lastticks;
	int currentframe; // (init: 0)
	int overallframe; // (init: 0)
	int mode;
	int ringframe;
	int pointerposition; // (init: 0 if flags1, else 0x80)
	uint fsPitch;
	struct IDirectDrawSurface4 * fsSurface;
	struct FLICHEADERSTRUCT fsHeader;
	struct File * filehandle;
	void * fsSPtr;
	void * fsSource;
	enum FlicDisplayMode fsDisplayMode;
	int fsBitPlanes;
	int fsLoadBufferSize;
	void * fsLoadBuffer;
	BOOL is15bit; // true if green mask == 0x3e0
};

struct MenuItem_SelectItem { // [LegoRR/FrontEnd.c|struct:0x20]
	enum MenuItem_SelectItemFlags flags; // [0x1 = print name over image, 0x2, 0x4]
	char * banner;
	struct Image * images[3]; // (cfg: Level::MenuBMP[0,2,3]) see Menu_SelectImageType
	int frontEndX; // (cfg: Level::FrontEndX)
	int frontEndY; // (cfg: Level::FrontEndY)
	BOOL frontEndOpen; // (cfg: Level::FrontEndOpen)
};

struct MenuSet { // [LegoRR/FrontEnd.c|struct:0x8] A collection of menus that may interact with one another (i.e. MainMenuFull, PausedMenu)
	struct Menu * * menus; // (cfg: MenuSet::Menu1, Menu2...)
	uint menuCount; // (cfg: MenuSet::MenuCount)
};

struct SaveReward { // [LegoRR/save.c|struct:0x3190]
	enum SaveRewardFlags flags;
	struct RewardLevel reward;
};

struct LevelLink { // [LegoRR/FrontEnd.c|struct:0x14]
	int setIndex; // Index in LevelSet
	struct LevelLink * * linkLevels;
	uint linkCount;
	undefined4 field_c;
	BOOL visited; // True if reached in RunThroughRecurse callback.
};

struct MenuItem_CycleData { // [LegoRR/FrontEnd.c|struct:0x1c]
	char * * nameList; // (cfg: Cycle:[7...])
	uint cycleCount; // (cfg: Cycle:[6])
	int nameCount; // (cfg: Cycle:[7...])
	int * valuePtr;
	int x2; // (cfg: Cycle:[3])
	int y2; // (cfg: Cycle:[4])
	MenuItem_CycleCallback callback;
};

struct Menu { // [LegoRR/FrontEnd.c|struct:0xa0] A singular menu screen contained within a MenuSet structure.
	char * title; // (cfg: Menu::Title)
	char * fullName; // (cfg: Menu::FullName)
	uint titleLength; // (init: strlen(title))
	struct Font * menuFont; // (cfg: Menu::MenuFont)
	struct Image * menuImage; // (cfg: Menu::MenuImage)
	struct Image * menuImageDark; // (cfg: Menu::MenuImageDark)
	struct MenuItem * * items; // (cfg: Menu::Item1, Item2...)
	int itemCount; // (cfg: Menu::ItemCount) Number of used slots in items
	int itemCapacity; // Total number of slots allocated in items
	int itemFocus; // Index of item with keyboard focus
	BOOL closed; // Signals the menu(screen?) has been closed?
	struct Point2I position; // (cfg: Menu::Position)
	enum MenuFlags flags; // flags [0x1, 0x2, ...]
	struct Point2F currPosition;
	struct MenuOverlay * overlays; // (cfg: Menu::Overlay1, Overlay2...)
	BOOL autoCenter; // (cfg: Menu::AutoCenter)
	BOOL displayTitle; // (cfg: Menu::DisplayTitle)
	BOOL anchored; // (cfg: Menu::Anchored)
	struct Point2I anchoredPosition; // (cfg: Menu::Anchored)
	int centerX;
	char name[64]; // Name of menu in Lego.cfg
	enum BoolTri playRandom; // (cfg: Menu::PlayRandom)
};

struct MenuItem_SelectData { // [LegoRR/FrontEnd.c|struct:0x5c]
	struct MenuItem_SelectItem * selItemList;
	uint * widths[3]; // (image Hi,Lo,Locked widths, 3 identical for font string width) see Menu_SelectImageType
	uint * heights[3]; // (image Hi,Lo,Locked heights, 3 identical for font height) see Menu_SelectImageType
	uint selItemCount;
	char * string1;
	char * string2;
	int * valuePtr;
	int x2;
	int y2;
	int selItemHeight;
	int scrollCount; // Max number of select items visible in scroll area.
	int xString1;
	int yString1;
	int xString2;
	int yString2;
	int scrollStart; // Index offset of visible scroll area.
	undefined4 field_50;
	MenuItem_SelectCallback callback;
	struct Menu * nextMenu; // Optional menu to transition to after making a selection.
};

union MenuItem_Data_union { // [LegoRR/FrontEnd.c|union:0x4]
	struct MenuItem_CycleData * cycle;
	struct MenuItem_TriggerData * trigger;
	struct MenuItem_TextInputData * textInput;
	struct MenuItem_SliderData * slider;
	struct MenuItem_RealSliderData * realSlider;
	struct MenuItem_SelectData * select;
	struct Menu * next;
};

struct MenuItem { // [LegoRR/FrontEnd.c|struct:0x3c]
	char * banner; // (cfg: type:[3|5]) Label text
	uint length;
	struct Font * fontHi; // (cfg: Menu::HiFont)
	struct Font * fontLo; // (cfg: Menu::LoFont)
	union MenuItem_Data_union itemData; // (cfg: type:[0,*])
	enum MenuItem_Type itemType; // (cfg: type:[0])
	int x1; // (cfg: type:[1])
	int y1; // (cfg: type:[2])
	int centerOffLo;
	int centerOffHi;
	BOOL isImageItem; // Only true if imageHi is loaded (should be renamed)
	struct Image * imageLo;
	struct Image * imageHi;
	enum ToolTip_Type toolTipType;
	BOOL notInTuto; // (string value is unchecked, but "NotInTuto" is the only seen usage)
};

struct MenuItem_TriggerData { // [LegoRR/FrontEnd.c|struct:0xc]
	int * valuePtr;
	BOOL end; // (cfg: Trigger:[4]) End/close the current MenuSet
	MenuItem_TriggerCallback callback;
};

struct MenuItem_RealSliderData { // [LegoRR/FrontEnd.c|struct:0x1c]
	float * valuePtr;
	float valueMin; // (cfg: RealSlider:[6])
	float valueMax; // (cfg: RealSlider:[7])
	float valueStep; // (cfg: RealSlider:[8])
	int x2; // (cfg: RealSlider:[3])
	int y2; // (cfg: RealSlider:[4])
	MenuItem_RealSliderCallback callback;
};

struct MenuItem_TextInputData { // [LegoRR/FrontEnd.c|struct:0x18]
	char * valuePtr;
	int length;
	int caretPos; // Character index of cursor.
	int maxLength; // Maximum length of value buffer.
	int x2;
	int y2;
};

struct TextWindow { // [Gods98/TextWindow.c|struct:0x830] Probably a text rendering area (official: TextWindow)
	struct Font * font;
	struct Area2F windowSize;
	void * windowBuffer;
	char secondBuffer[1024];
	uint bufferSize;
	uint bufferEnd;
	uint lines[256]; // list of line numbers by char offset?
	uint linesCount;
	int linesCapacity;
	float displayDelay;
	uint flags;
};

struct MenuTextWindow { // [LegoRR/FrontEnd.c|struct:0x728] Menu/FrontEnd text structure, see CFG blocks: SaveText, LevelText
	struct TextWindow * textWindow;
	struct Image * PanelImage;
	struct Area2F WindowArea;
	struct Area2F PanelArea;
	char LoadText[256];
	char SaveText[256];
	char SlotText[256]; // format: %d (save number)
	char LoadSelText[256]; // format: %d (save number)
	char SaveSelText[256]; // format: %d (save number)
	char LevelText[256];
	char TutorialText[256];
};

typedef struct Dependencies_Globs Dependencies_Globs, *PDependencies_Globs;

struct Dependencies_Globs { // [LegoRR/Dependencies.c|struct:0xe5b4|tags:GLOBS]
	struct DependencyData table[20][15];
	BOOL disabled; // (Debug feature with F11 key)
};

typedef struct Roof_Globs Roof_Globs, *PRoof_Globs;

typedef struct RoofBlock RoofBlock, *PRoofBlock;

typedef enum RoofFlags { // [LegoRR/Roof.c|flags:0x4|type:uint]
	ROOF_FLAG_HIDDEN=1,
	ROOF_FLAG_NEEDUPDATE=2,
	ROOF_FLAG_NONE=0,
	ROOF_FLAG_SHIFTVERTICES=4
} RoofFlags;

struct Roof_Globs { // [LegoRR/Roof.c|struct:0x7f0|tags:GLOBS] A level's roof mesh displayed in the world (only when in FP)
	struct Container * contMesh; // MakeMesh2:IMMEDIATE
	struct Size2I dimensions;
	BOOL hidden;
	BOOL needsUpdate; // Similar to the ROOF_NEEDSUPDATE flag, but is true if any blocks have to be updated
	struct Container_Texture * texture;
	struct RoofBlock * grid; // Allocation size of 8, may be same as struct type below
	struct RoofBlock * visibleTable[500]; // items are either null, or point to a block in grid
	uint visibleCount; // (not sure if "visible" is correct)
};

struct RoofBlock { // [LegoRR/Roof.c|struct:0x8] Mesh group for a single block in the world's roof. (only used for FP)
	enum D3DRMGroupIndex groupID;
	enum RoofFlags flags; // (0x1 = hidde, 0x2 = needsUpdate, 0x4 = shiftVertices)
};

typedef struct AITask_Globs AITask_Globs, *PAITask_Globs;

typedef enum AITask_GlobFlags { // [LegoRR/AITask.c|flags:0x4|type:uint]
	AITASK_GLOB_FLAG_DISABLEUPDATES=2147483648,
	AITASK_GLOB_FLAG_INITIALISED=1,
	AITASK_GLOB_FLAG_NONE=0,
	AITASK_GLOB_FLAG_REMOVING=2,
	AITASK_GLOB_FLAG_UPDATINGOBJECT=4
} AITask_GlobFlags;

struct AITask_Globs { // [LegoRR/AITask.c|struct:0x4e9c|tags:GLOBS]
	struct AITask * listSet[12];
	struct AITask * freeList;
	uint listCount;
	char * aitaskName[31];
	char * priorityName[27];
	int priorityValues[27];
	struct AITask * pendingTaskList;
	struct AITask * creatureTaskList;
	struct LegoObject * freeUnitList[50];
	uint freeUnitCount;
	struct LegoObject * freeCreatureList[50];
	uint freeCreatureCount;
	uint requestObjCounts[20][15][16];
	BOOL disabledPriorities[27];
	enum AITask_GlobFlags flags;
};

typedef struct HelpWindow_Globs HelpWindow_Globs, *PHelpWindow_Globs;

typedef struct MenuButton MenuButton, *PMenuButton;

typedef enum HelpWindow_GlobFlags { // [LegoRR/HelpWindow.c|flags:0x4|type:uint]
	HELPWINDOW_GLOB_FLAG_ENABLED=64,
	HELPWINDOW_GLOB_FLAG_NONE=0,
	HELPWINDOW_GLOB_FLAG_UNK_1=1,
	HELPWINDOW_GLOB_FLAG_UNK_10=16,
	HELPWINDOW_GLOB_FLAG_UNK_2=2,
	HELPWINDOW_GLOB_FLAG_UNK_20=32,
	HELPWINDOW_GLOB_FLAG_UNK_4=4,
	HELPWINDOW_GLOB_FLAG_UNK_8=8
} HelpWindow_GlobFlags;

struct MenuButton { // [LegoRR/FrontEnd.c|struct:0x1c]
	struct Area2F window;
	struct Image * HiImage;
	struct Image * LoImage;
	char * Text;
};

struct HelpWindow_Globs { // [LegoRR/HelpWindow.c|struct:0xd6c|tags:GLOBS]
	struct Font * font;
	struct Point2F TextWindowPosition;
	float TextWindowBottom; // (Position.y + height)
	struct Image * BackgroundImage;
	struct Point2F BackgroundPosition;
	struct MenuButton Buttons[4]; // [Continue, CancelFutureButton, NULL, NULL]
	struct TextWindow * textWnd;
	char * VehicleInfos[15][16];
	char * MiniFigureInfos[15][16];
	char * BuildingInfos[15][16];
	char * CanBuildMessage;
	char * CanTransportMessage;
	char * CanBuildAndTransportMessage;
	char * activeObjName;
	enum LegoObject_Type activeObjType;
	LegoObject_ID activeObjID;
	uint activeObjLevel;
	enum LegoObject_Type unlockedObjTypes[30];
	LegoObject_ID unlockedObjIndexes[30];
	uint unlockedObjLevels[30];
	uint unlockedCount;
	float float_d58;
	float float_d5c;
	uint count_d60;
	undefined4 field_d64;
	enum HelpWindow_GlobFlags flags;
};

typedef struct Stats_Globs Stats_Globs, *PStats_Globs;

typedef struct ToolStats ToolStats, *PToolStats;

struct ToolStats { // [LegoRR/Stats.c|struct:0x10]
	enum AITask_Type taskTypes[3]; // Up to 3 AITaskTypes can be associated with a tool
	uint taskCount;
};

struct Stats_Globs { // [LegoRR/Stats.c|struct:0x5b0|tags:GLOBS]
	struct ObjectStats * * objectStats[20]; // [objType:20][*objIndex][*objLevel]
	uint objectLevels[20][15]; // [objType:20][objIndex:15]
	struct ToolStats toolStats[11]; // [toolType:11]
};

typedef struct SFX_Globs SFX_Globs, *PSFX_Globs;

typedef enum SFX_GlobFlags { // [LegoRR/SFX.c|flags:0x4|type:uint]
	SFX_GLOB_FLAG_NONE=0,
	SFX_GLOB_FLAG_POPULATEMODE=2,
	SFX_GLOB_FLAG_QUEUEMODE=8,
	SFX_GLOB_FLAG_SOUNDON=1
} SFX_GlobFlags;

typedef enum SoundMode { // [Gods98/Sound.c|enum:0x4|type:uint]
	SoundMode_Loop=1,
	SoundMode_Multi=2,
	SoundMode_Once=0
} SoundMode;

struct SFX_Globs { // [LegoRR/SFX.c|struct:0x1770|tags:GLOBS]
	struct SFX_Property samplePropTable[495];
	struct SFX_Property sampleGroupTable[200];
	uint * hashNameList;
	uint hashNameCount;
	uint sampleGroupCount;
	enum SFX_GlobFlags flags;
	struct SFX_Instance sfxInstanceTable[10];
	uint sfxInstanceCount;
	float globalSampleDuration; // Duration is multiplied by 25.0
	int globalSampleSoundHandle;
	enum SFX_ID globalSampleSFXType;
	enum SFX_ID soundQueueSFXTable_1[10];
	enum SoundMode soundQueueModesTable_1[10];
	enum SFX_ID soundQueueSFXTable_2[10];
	enum SoundMode soundQueueModesTable_2[10];
	uint soundQueueCount_1;
	uint soundQueueCount_2;
};

typedef struct Construction_Globs Construction_Globs, *PConstruction_Globs;

struct Construction_Globs { // [LegoRR/Construction.c|struct:0x38|tags:GLOBS]
	uint nextHandleValue; // Next handle value used when creating a construction zone.
	struct Construction_Zone * constructList; // Head of linked list.
	undefined4 unused_buildingBaseTable[5]; // (probably related to unused buildingBaseTable)
	char * buildingBaseName[5]; // empty table, no names
	uint buildingBaseCount;
	BOOL disableCryOreDrop;
};

typedef struct Objective_Globs Objective_Globs, *PObjective_Globs;

typedef enum Objective_GlobFlags { // [LegoRR/Objective.c|flags:0x4|type:uint] STATUSREADY means next status has been set, but has not been "updated" yet? HITTIMEFAIL is unused and replaced by SHOWACHIEVEDADVISOR.
	OBJECTIVE_GLOB_FLAG_BLOCK=1024,
	OBJECTIVE_GLOB_FLAG_BRIEFING=1,
	OBJECTIVE_GLOB_FLAG_COMPLETED=2,
	OBJECTIVE_GLOB_FLAG_CONSTRUCTION=4096,
	OBJECTIVE_GLOB_FLAG_CRYSTAL=256,
	OBJECTIVE_GLOB_FLAG_FAILED=4,
	OBJECTIVE_GLOB_FLAG_HITTIMEFAIL=64,
	OBJECTIVE_GLOB_FLAG_NONE=0,
	OBJECTIVE_GLOB_FLAG_ORE=512,
	OBJECTIVE_GLOB_FLAG_SHOWACHIEVEDADVISOR=32,
	OBJECTIVE_GLOB_FLAG_SHOWBRIEFINGADVISOR=16,
	OBJECTIVE_GLOB_FLAG_SHOWFAILEDADVISOR=128,
	OBJECTIVE_GLOB_FLAG_STATUSREADY=8,
	OBJECTIVE_GLOB_FLAG_TIMER=2048
} Objective_GlobFlags;

struct Objective_Globs { // [LegoRR/Objective.c|struct:0x28c|tags:GLOBS] Globals for objective messages (Chief briefing, etc).
	enum Objective_GlobFlags flags;
	struct File * file; // PTRFileStream_00500bc4
	char filename[128]; // CHAR_ARRAY_00500bc8
	char * messages[4]; // [Briefing,Completion,Failure,CrystalFailure] Strings containing text of entire status message (pages are separated with '\a').
	undefined reserved1[384]; // (possibly unused array of char[3][128])
	uint currentPages[4]; // (1-indexed) Current page number of the displayed status type. (g_Objective_StatusUnkCounts)
	uint currentPageStates[4]; // (1-indexed) State tracking for page to switch to (this is only used to check if the above field needs to trigger an update). (g_Objective_StatusUnkCounts2)
	uint pageCounts[4]; // Number of pages for the specific status. (g_Objective_StatusBellCounts)
	struct TextWindow * textWindows[4]; // Text windows for the specific status. (g_Objective_StatusTextWindows)
	struct TextWindow * pageTextWindows[3]; // PTRTextWindow_00500e18, PTRTextWindow_00500e1c, PTRTextWindow_00500e20
	struct TextWindow * beginTextWindow; // Unknown usage, only worked with when line "[BEGIN]" is found (PTRTextWindow_00500e24)
	undefined4 reserved2;
	BOOL hasBeginText; // True when text has been assigned to beginTextWindow (BOOL_00500e2c)
	BOOL achieved; // True if the level was has ended successfully. (g_LevelIsComplete)
	BOOL objectiveSwitch; // (see: NERPFunc__SetObjectiveSwitch)
	char * soundName;
	int soundHandle; // (init: -1 when unused) INT_00500e3c
	float soundTimer; // (init: (playTime - 1.5f) * 25.0f) FLOAT_00500e40
	BOOL showing; // True when an objective is currently being shown or changed to(?)
	BOOL endTeleportEnabled; // (cfg: ! DisableEndTeleport, default: false (enabled))
};

typedef struct Panel_Globs Panel_Globs, *PPanel_Globs;

typedef struct PanelData PanelData, *PPanelData;

typedef enum PanelButtonType { // [LegoRR/Panels.c|enum:0x4|type:int|tags:REALENUM] DEFINE ONLY
	PANELBUTTON_TYPE_COUNT=24
} PanelButtonType;

typedef struct PanelTextWindow PanelTextWindow, *PPanelTextWindow;

typedef enum Panel_GlobFlags { // [LegoRR/Panels.c|flags:0x4|type:uint] Todo...
	PANEL_GLOB_FLAG_NONE=0,
	PANEL_GLOB_FLAG_PRIORITIES_TOP=2,
	PANEL_GLOB_FLAG_PRIORITIES_UP=4,
	PANEL_GLOB_FLAG_ROTATECONTROL_ACTIVE=1,
	PANEL_GLOB_FLAG_ROTATECONTROL_DOWN=32,
	PANEL_GLOB_FLAG_ROTATECONTROL_LEFT=64,
	PANEL_GLOB_FLAG_ROTATECONTROL_RIGHT=128,
	PANEL_GLOB_FLAG_ROTATECONTROL_UP=16
} Panel_GlobFlags;

typedef struct PanelButtonData PanelButtonData, *PPanelButtonData;

typedef enum PanelDataFlags { // [LegoRR/Panels.c|flags:0x4|type:uint] Todo...
	PANEL_FLAG_CLOSED=4,
	PANEL_FLAG_HASIMAGE=1,
	PANEL_FLAG_NONE=0,
	PANEL_FLAG_OPEN=2,
	PANEL_FLAG_SLIDING=8
} PanelDataFlags;

typedef struct Rect2F Rect2F, *PRect2F;

typedef enum PanelButtonFlags { // [LegoRR/Panels.c|flags:0x4|type:uint]
	PANELBUTTON_FLAG_DOWN=4,
	PANELBUTTON_FLAG_HIDDEN=16,
	PANELBUTTON_FLAG_HOVER=2,
	PANELBUTTON_FLAG_NONE=0,
	PANELBUTTON_FLAG_TOGGLEABLE=32,
	PANELBUTTON_FLAG_TOGGLED=8,
	PANELBUTTON_FLAG_UNUSED_HOVERFLASH=64
} PanelButtonFlags;

struct PanelData { // [LegoRR/Panels.c|struct:0x30]
	struct Image * imageOrFlic;
	BOOL isFlic;
	struct Point2F openPos;
	struct Point2F closedPos;
	struct Point2F position;
	undefined4 reserved1; // Unused, but set to 0.
	struct PanelButtonData * buttonList;
	uint buttonCount;
	enum PanelDataFlags flags;
};

struct Panel_Globs { // [LegoRR/Panels.c|struct:0x7b8|tags:GLOBS]
	char * panelName[12];
	struct PanelData panelTable[12];
	char * panelButtonName[12][24];
	enum Panel_Type currentPanel;
	enum PanelButtonType currentButton;
	struct PanelTextWindow * infoTextWnd;
	struct PanelTextWindow * encyclopediaTextWnd;
	struct Image * crystalSmallImage; // Hard: "Interface\\RightPanel\\SmallCrystal.bmp"
	struct Image * crystalNoSmallImage; // Hard: "Interface\\RightPanel\\NoSmallCrystal.bmp"
	struct Image * crystalUsedImage; // Hard: "Interface\\RightPanel\\UsedCrystal.bmp"
	uint crystalQuota;
	struct Image * airMeterJuiceImage; // Hard: "Interface\\AirMeter\\msgpanel_air_juice.bmp"
	struct Image * airMeterNoAirImage; // Hard: "Interface\\AirMeter\\msgpanel_noair.bmp"
	struct Point2F airMeterJuiceOffset; // Hard: (85, 6) Offset relative to top-left corner of MsgPanel
	uint airMeterJuiceLength; // Hard: 236
	struct Point2F airMeterNoAirOffset; // Hard: (21, 0) Offset relative to top-left corner of MsgPanel
	BOOL airMeterOxygenLow; // Oxygen level is 10% or less.
	struct Image * cryOreSideBarImage; // Hard: "Interface\\RightPanel\\crystalsidebar_ore.bmp"
	struct Point2F cryOreSideBarOffset; // Hard: (615, 434)
	uint cryOreMeterOffset; // Hard: 423
	float cryOreMeterValue;
	struct Point2I rotateCenter;
	int rotateRadius;
	struct Point2F rotateUpOffset;
	struct Point2F rotateDownOffset;
	struct Point2F rotateLeftOffset;
	struct Point2F rotateRightOffset;
	struct Image * rotateUpImage;
	struct Image * rotateDownImage;
	struct Image * rotateLeftImage;
	struct Image * rotateRightImage;
	enum Panel_GlobFlags flags;
	undefined4 reserved;
	uint s_crystalShifts[2][6]; // static function variable for delayed change in crystal meter
};

struct Rect2F { // [common.c|struct:0x10]
	float left;
	float top;
	float right;
	float bottom;
};

struct PanelButtonData { // [LegoRR/Panels.c|struct:0x2c]
	struct Rect2F rect;
	struct Image * imageHover;
	struct Image * imagePressed;
	struct Image * image;
	undefined4 reserved1; // Unused and unset?
	enum ToolTip_Type toolTipType;
	int clickCount;
	enum PanelButtonFlags flags;
};

struct PanelTextWindow { // [LegoRR/Panels.c|struct:0x10] A Panel-based wrapper around the TextWindow class
	struct TextWindow * textWindow;
	struct Point2F position;
	struct PanelData * panel;
};

typedef struct Bubble_Globs Bubble_Globs, *PBubble_Globs;

typedef struct Bubble Bubble, *PBubble;

struct Bubble { // [LegoRR/Bubble.c|struct:0x8]
	struct LegoObject * object;
	float remainingTimer;
};

struct Bubble_Globs { // [LegoRR/Bubble.c|struct:0x4f4|tags:GLOBS]
	BOOL alwaysVisible; // Object Display HUD/UI over entities in-game
	struct Image * bubbleImage[39];
	char * bubbleName[39];
	undefined1 reserved1[72];
	struct Bubble healthBarList[20]; // Not a bubble image, but this tracks how long to show the bar after being damaged like normal bubbles.
	struct Bubble bubbleList[20]; // All other types of bubbles.
	struct Bubble powerOffList[20]; // Flashing no-power icons.
	struct Bubble callToArmsList[50]; // Action stations bubbles.
};

typedef struct GameControl_Globs GameControl_Globs, *PGameControl_Globs;

struct GameControl_Globs { // [LegoRR/???|struct:0x180|tags:GLOBS]
	int msy_Last_1;
	int msx_Last_1;
	struct Point2F pointf_8;
	undefined4 reserved1;
	BOOL mslb_Last_1;
	BOOL renameUseQuotes;
	undefined4 reserved2;
	bool typingState_Map[256];
	float dbgUpgradeChangeTimer;
	float dbgSpeedChangeTimer;
	float dbgRollOffChangeTimer;
	float sceneFogDelta; // Delta value used in Lego_UpdateSceneFog ((M_PI*2)/fogRate * elapsed).
	BOOL handleKeysLastLeftMouseButtonDown; // Tracks mouse released state in Lego_HandleKeys
	float dbgCursorLightLevel;
	BOOL isGameSpeedLocked; // When this is TRUE, game speed can only be lowered when calling `Game_SetGameSpeed`.
	BOOL mslb_Last_3;
	BOOL mslb_Last_4;
	struct Point2F pointf_144;
	BOOL mslb_Last_5;
	BOOL mslb_Last_6;
	BOOL mslb_Last_0;
	BOOL mslr_Last_0;
	float handleWorldNoMouseButtonsElapsed; // Duration that neither left or right mouse buttons have been down for (in game time).
	BOOL bool_160;
	struct LegoObject * toolTipObject;
	BOOL dbgF10InvertLighting;
	BOOL dbgF9DisableLightEffects;
	undefined4 reserved3;
	struct LegoObject * dbgGetInVehicle; // (K debug key, assigned to selected vehicle, pressing K with a rock raider will tell them to get in this registered vehicle)
	enum Direction direction_178;
	float timerTutorialBlockFlash;
};

typedef struct Smoke_Globs Smoke_Globs, *PSmoke_Globs;

struct Smoke_Globs { // [LegoRR/Smoke.c|struct:0x34|tags:GLOBS]
	struct Container_Texture * textureList[10];
	struct Smoke * firstSmoke; // A doublely-linked list, each node has next/previous as well
	struct Smoke * lastSmoke;
	uint textureCount;
};

typedef struct LightEffects_Globs LightEffects_Globs, *PLightEffects_Globs;

typedef struct Range2F Range2F, *PRange2F;

typedef enum LightEffects_GlobFlags { // [LegoRR/LightEffects.c|flags:0x4|type:uint] LightEffects_GlobFlags, Flags for LightEffectsManager global variable @004ebec8
	LIGHTFX_GLOB_FLAG_DIMIN_DONE=1024,
	LIGHTFX_GLOB_FLAG_DIMOUT=512,
	LIGHTFX_GLOB_FLAG_DIMOUT_DONE=4096,
	LIGHTFX_GLOB_FLAG_DISABLED=256,
	LIGHTFX_GLOB_FLAG_FADE_FORWARD=16,
	LIGHTFX_GLOB_FLAG_FADE_REVERSE=32,
	LIGHTFX_GLOB_FLAG_FADING=8,
	LIGHTFX_GLOB_FLAG_HASBLINK=1,
	LIGHTFX_GLOB_FLAG_HASFADE=4,
	LIGHTFX_GLOB_FLAG_HASMOVE=64,
	LIGHTFX_GLOB_FLAG_MOVING=128,
	LIGHTFX_GLOB_FLAG_NONE=0
} LightEffects_GlobFlags;

struct Range2F { // [common.c|struct:0x8]
	float min;
	float max;
};

struct LightEffects_Globs { // [LegoRR/LightEffects.c|struct:0xf4|tags:GLOBS] LightEffects module globals @004ebdd8
	struct Container * rootSpotlight; // [Cont+Move] init
	struct Container * rootLight; // [Move] init (Reference used when getting position of rootSpotlight)
	struct ColourRGBF initialRGB; // [Color] init
	struct ColourRGBF currentRGB; // [Color+Blink+Fade] init+update
	struct ColourRGBF blinkRGBMax; // [Blink] init (cfg: BlinkRGBMax)
	float blinkWait; // [Blink] update. Time between end of blink and next blink.
	struct Range2F blinkWaitRange; // [Blink] init (cfg: RandomRangeForTimeBetweenBlinks, mult: 25.0)
	float blinkChange; // [Blink] update
	float blinkChangeMax; // [Blink] init (cfg: MaxChangeAllowed, div: 255.0)
	struct ColourRGBF fadeDestRGB; // [Fade] update
	struct ColourRGBF fadeRGBMin; // [Fade] init (cfg: FadeRGBMin)
	struct ColourRGBF fadeRGBMax; // [Fade] init (cfg: FadeRGBMax)
	float fadeWait; // [Fade] update. Time between end of fade and next fade.
	struct Range2F fadeWaitRange; // [Fade] init (cfg: RandomRangeForTimeBetweenFades, mult: 25.0)
	struct ColourRGBF fadeSpeedRGB; // [Fade] update
	struct Range2F fadeSpeedRange; // [Fade] init (cfg: RandomRangeForFadeTimeFade, mult: 25.0)
	float fadeHold; // [Fade] update. Time between peak of fade before reversing.
	struct Range2F fadeHoldRange; // [Fade] init (cfg: RandomRangeForHoldTimeOfFade, mult: 25.0)
	struct ColourRGBF fadePosRGB; // [Fade] update
	struct Vector3F movePosition; // [Move] init+update (3D position of rootSpotlight)
	struct Vector3F moveLimit; // [Move] init (cfg: MoveLimit)
	float moveWait; // [Move] update. Time between end of move and next move.
	struct Range2F moveWaitRange; // [Move] init (cfg: RandomRangeForTimeBetweenMoves, mult: 25.0)
	float moveSpeed; // [Move] update
	struct Range2F moveSpeedRange; // [Move] init (cfg: RandomRangeForSpeedOfMove, mult: 25.0)
	struct Vector3F moveVector; // [Move] update
	float moveDist; // [Move] update
	struct Range2F moveDistRange; // [Move] init (cfg: RandomRangeForDistOfMove)
	undefined1 reserved1[12]; // possibly an unused Vector3F/ColourRGBF
	enum LightEffects_GlobFlags flags; // [all] init+update
};

typedef struct Lego_Globs Lego_Globs, *PLego_Globs;

typedef enum Graphics_Quality { // [Gods98/Main.c|enum:0x4|type:uint] Phong is unused.
	Flat=2,
	Gouraud=3,
	Phong=4,
	UnlitFlat=1,
	Wireframe=0
} Graphics_Quality;

typedef struct LegoCamera LegoCamera, *PLegoCamera;

typedef struct SelectPlace SelectPlace, *PSelectPlace;

typedef enum ViewMode { // [LegoRR/Lego.c|enum:0x4|type:int]
	ViewMode_FP=0,
	ViewMode_Top=1
} ViewMode;

typedef enum GameFlags1 { // [LegoRR/Lego.c|flags:0x4|type:uint]
	GAME1_ALWAYSROCKFALL=8388608,
	GAME1_CAMERAGOTO=2097152,
	GAME1_DDRAWCLEAR=1024,
	GAME1_DEBUG_NOCLIP_FPS=1073741824,
	GAME1_DEBUG_NONERPS=16777216,
	GAME1_DEBUG_SHOWVERTEXMODE=536870912,
	GAME1_DYNAMICPM=524288,
	GAME1_FOGCOLOURRGB=32768,
	GAME1_FREEZEINTERFACE=1048576,
	GAME1_HIGHFOGCOLOURRGB=65536,
	GAME1_LASERTRACKER=268435456,
	GAME1_LEVELENDING=134217728,
	GAME1_LEVELSTART=4,
	GAME1_MOUSEBUSY=512,
	GAME1_MULTISELECTING=256,
	GAME1_MUSICPLAYING=8,
	GAME1_NONE=0,
	GAME1_ONLYBUILDONPATHS=4194304,
	GAME1_PAUSED=33554432,
	GAME1_RADARON=2,
	GAME1_RADAR_MAPVIEW=4096,
	GAME1_RADAR_NOTRACKOBJECT=131072,
	GAME1_RADAR_TRACKOBJECTLOST=16384,
	GAME1_RADAR_TRACKOBJECTVIEW=8192,
	GAME1_RENDERPANELS=2048,
	GAME1_SHOWFPS=64,
	GAME1_SHOWMEMORY=128,
	GAME1_STREAMNERPSSPEACH=67108864,
	GAME1_USEDETAIL=32,
	GAME1_USESFX=16,
	GAME1_VERTEXLOCKONPOINTER=2147483648,
	GAME1_VERTEXMODE=262144
} GameFlags1;

typedef enum GameFlags2 { // [LegoRR/Lego.c|flags:0x4|type:uint]
	GAME2_ALLOWDEBUGKEYS=16,
	GAME2_ALLOWEDITMODE=32,
	GAME2_ALLOWRENAME=131072,
	GAME2_ATTACKDEFER=4,
	GAME2_CALLTOARMS=1,
	GAME2_CAMERAMOVING=512,
	GAME2_DISABLETOOLTIPSOUND=1048576,
	GAME2_GENERATESPIDERS=524288,
	GAME2_INMENU=4096,
	GAME2_INOPTIONSMENU=256,
	GAME2_LEVELEXITING=2,
	GAME2_MENU_HASNEXT=16384,
	GAME2_MENU_HASPREVIOUS=32768,
	GAME2_MESSAGE_HASNEXT=64,
	GAME2_MESSAGE_HASREPEAT=128,
	GAME2_MOUSE_INSIDEGAMEVIEW=1024,
	GAME2_MUSICREADY=2048,
	GAME2_NOAUTOEAT=2097152,
	GAME2_NOMULTISELECT=8192,
	GAME2_NONE=0,
	GAME2_RECALLOLOBJECTS=262144,
	GAME2_SHOWDEBUGTOOLTIPS=8
} GameFlags2;

typedef enum GameFlags3 { // [LegoRR/Lego.c|flags:0x4|type:uint] Flags for the current user action.
	GAME3_ENCYCLOPEDIA=1,
	GAME3_LEGOMANDIG=32,
	GAME3_LEGOMANGOTO=2,
	GAME3_LOADVEHICLE=16,
	GAME3_NONE=0,
	GAME3_PICKUPOBJECT=8,
	GAME3_PLACEBUILDING=128,
	GAME3_VEHICLEDIG=64,
	GAME3_VEHICLEGOTO=4
} GameFlags3;

typedef enum LegoCamera_Type { // [LegoRR/LegoCamera.c|enum:0x4|type:int]
	LegoCamera_FP=3,
	LegoCamera_None=0,
	LegoCamera_Radar=2,
	LegoCamera_Top=1,
	LegoCamera_Type_Count=4
} LegoCamera_Type;

typedef enum CameraFlags { // [LegoRR/LegoCamera.c|flags:0x4|type:uint]
	CAMERA_FLAG_FPSETUP=16,
	CAMERA_FLAG_FREEMOVEMENT=8,
	CAMERA_FLAG_NONE=0,
	CAMERA_FLAG_ROTATIONRANGE=2,
	CAMERA_FLAG_TILTRANGE=1,
	CAMERA_FLAG_ZOOMRANGE=4
} CameraFlags;

struct SelectPlace { // [LegoRR/SelectPlace.c|struct:0x8] Building selection highlight shown on map when placing
	struct Container * contMesh;
	float tileDepth; // (init: 5.0) Z height of each coloured square when drawing the building placement grid.
};

struct Lego_Globs { // [LegoRR/Lego.c|struct:0xf00|tags:GLOBS]
	struct Config * config;
	char * gameName;
	undefined4 field_8;
	undefined4 field_c;
	enum Graphics_Quality quality; // (cfg: Main::Quality)
	struct Lego_Level * currLevel;
	struct Container * rootCont; // containerGlobs.root
	struct Viewport * viewMain; // Viewport area: (0.0,0.0 - 1.0x1.0)
	struct Viewport * viewTrack; // Viewport area: (16,14 - 151x151)
	struct LegoCamera * cameraMain;
	struct LegoCamera * cameraTrack;
	struct LegoCamera * cameraFP;
	struct Container * spotlightTop;
	struct Container * spotlightTrack;
	struct Container * pointLightFP;
	struct Container * dirLightFP;
	struct Container * ambientLight;
	struct Container * rootSpotlight;
	struct Container * rootLight;
	struct Container * dirLightCallToArms;
	float FPClipBlocks; // (cfg: Main::FPClipBlocks)
	float TVClipDist; // (cfg: Main::TVClipDist)
	undefined4 field_58;
	undefined4 field_5c;
	undefined4 field_60;
	struct Font * fontStandard; // Loader, Debug text, Level Select window, Pull-out info icon window, (unused) Info, Encyclopedia(?).
	struct Font * fontToolTip; // ToolTip, CryOre count, Unit custom name, Teleporter queued, Interface UPG(???), Info icon count.
	struct Font * fontTallYellow; // (unused) Block / Vertex mode for unimplemented SingleWidthDig feature.
	struct Font * fontTextWindow; // TextMessage window (same as fontStandard).
	struct Font * fontBriefingLo; // Dark text color used by most menus that share the briefing menu background.
	struct Font * fontBriefingHi; // Bright text color used by most menus that share the briefing menu background.
	struct Font * fontCredits; // Credits roll only.
	struct TextWindow * textOnlyWindow;
	struct TextWindow * textImageWindow; // Same as textOnlyWindow, but used instead when there's an image.
	struct Point2F gotoNewPos; // Upcoming/current 2D world position used when programatically moving the camera.
	struct Point2F gotoTargetPos; // Desired 2D world position used when programatically moving the camera (using Smooth option)
	BOOL gotoSmooth; // When false, gotoNewPos is the target position (aka, camera smoothing).
	float gameSpeed;
	struct LegoObject * objectFP;
	struct Vector3F vectorDragStartUnk_a4;
	float float_b0;
	float float_b4;
	float float_b8;
	float float_bc;
	struct Point2I digVertexBlockPos; // Drilling pointer block position for unused Vertex Mode (SingleWidthDig).
	BOOL digVertexShowPointer; // Used with: digVertexBlockPos
	char * langPowerCrystal_name; // (cfg: ObjectNames)
	char * langOre_name; // (cfg: ObjectNames)
	char * langProcessedOre_name; // (cfg: ObjectNames)
	char * langDynamite_name; // (cfg: ObjectNames)
	char * langBarrier_name; // (cfg: ObjectNames)
	char * langElectricFence_name; // (cfg: ObjectNames)
	char * langSpiderWeb_name; // (cfg: ObjectNames)
	char * langOohScary_name; // (cfg: ObjectNames)
	char * langPath_name; // (cfg: ObjectNames)
	char * langPowerCrystal_theName; // (cfg: ObjectTheNames)
	char * langOre_theName; // (cfg: ObjectTheNames)
	char * langProcessedOre_theName; // (cfg: ObjectTheNames)
	char * langDynamite_theName; // (cfg: ObjectTheNames)
	char * langBarrier_theName; // (cfg: ObjectTheNames)
	char * langElectricFence_theName; // (cfg: ObjectTheNames)
	char * langSpiderWeb_theName; // (cfg: ObjectTheNames)
	char * langOohScary_theName; // (cfg: ObjectTheNames)
	char * langPath_theName; // (cfg: ObjectTheNames)
	struct VehicleModel * vehicleData; // (cfg: VehicleTypes)
	struct CreatureModel * miniFigureData; // (cfg: MiniFigureTypes)
	struct CreatureModel * rockMonsterData; // (cfg: RockMonsterTypes)
	struct BuildingModel * buildingData; // (cfg: BuildingTypes)
	struct Upgrade_PartModel * upgradeData; // (cfg: UpgradeTypes)
	char * * vehicleName; // (cfg: VehicleTypes)
	char * * miniFigureName; // (cfg: MiniFigureTypes)
	char * * rockMonsterName; // (cfg: RockMonsterTypes)
	char * * buildingName; // (cfg: BuildingTypes)
	char * * upgradeName; // (cfg: UpgradeTypes)
	char * toolName[11];
	char * langTool_name[11]; // (cfg: ToolNames)
	char * * langVehicle_name; // (cfg: ObjectNames)
	char * * langMiniFigure_name; // (cfg: ObjectNames)
	char * * langRockMonster_name; // (cfg: ObjectNames)
	char * * langBuilding_name; // (cfg: ObjectNames)
	char * * langUpgrade_name; // (cfg: ObjectNames) never specified in Lego.cfg
	char * * langVehicle_theName; // (cfg: ObjectTheNames)
	char * * langMiniFigure_theName; // (cfg: ObjectTheNames)
	char * * langRockMonster_theName; // (cfg: ObjectTheNames)
	char * * langBuilding_theName; // (cfg: ObjectTheNames)
	char * * langUpgrade_theName; // (cfg: ObjectTheNames) never specified in Lego.cfg
	uint vehicleCount; // (cfg: VehicleTypes)
	uint miniFigureCount; // (cfg: MiniFigureTypes)
	uint rockMonsterCount; // (cfg: RockMonsterTypes)
	uint buildingCount; // (cfg: BuildingTypes)
	uint upgradeCount; // (cfg: UpgradeTypes)
	char * surfaceName[18];
	char * langSurface_name[18]; // (cfg: SurfaceTypeDescriptions)
	enum SFX_ID langSurface_sound[18]; // (cfg: SurfaceTypeDescriptions)
	struct Container * contBoulder;
	struct Container * contBoulderExplode;
	struct Container * contBoulderExplodeIce;
	struct Container * contCrystal;
	struct Container * contDynamite;
	struct Container * contOresTable[2];
	struct Container * contOohScary;
	struct Container * contBarrier;
	struct Container * contElectricFence;
	struct Container * contSpiderWeb;
	struct Container * contRechargeSparkle;
	struct Container * contMiniTeleportUp;
	struct Container * contElectricFenceStud;
	struct Container * contPusher;
	struct Container * contFreezer;
	struct Container * contIceCube;
	struct Container * contSmashPath;
	struct Container * contLaserShot;
	struct SelectPlace * selectPlace;
	struct LegoObject * recordObjs[10];
	uint recordObjsCount;
	struct Area2F radarScreenRect;
	float radarZoom;
	struct Point2F radarCenter;
	float MedPolyRange; // (cfg: Main::MedPolyRange)
	float HighPolyRange; // (cfg: Main::HighPolyRange)
	int HPBlocks; // (cfg: Main::HPBlocks)
	struct ColourRGBF FogColourRGB; // (cfg: Level::FogColourRGB)
	struct ColourRGBF HighFogColourRGB; // (cfg: Level::HighFogColourRGB)
	float float_364; // level-related?
	struct ColourRGBF PowerCrystalRGB; // (cfg: Main::PowerCrystalRGB)
	struct ColourRGBF UnpoweredCrystalRGB; // (cfg: Main::UnpoweredCrystalRGB)
	enum LegoObject_Type placeObjType;
	LegoObject_ID placeObjID;
	enum Direction placeObjDirection;
	struct LegoObject * placeDestSmallTeleporter;
	struct LegoObject * placeDestBigTeleporter;
	struct LegoObject * placeDestWaterTeleporter;
	float MinEnergyForEat; // (cfg: Main::MinEnergyForEat)
	struct Image * TutorialIcon; // (cfg: Main::TutorialIcon)
	undefined4 field_3a0;
	float DynamiteDamageRadius; // (cfg: Main::DynamiteDamageRadius)
	float DynamiteMaxDamage; // (cfg: Main::DynamiteMaxDamage)
	float DynamiteWakeRadius; // (cfg: Main::DynamiteWakeRadius)
	float BirdScarerRadius; // (cfg: Main::BirdScarerRadius)
	enum LegoObject_Type objTeleportQueueTypes_TABLE[20];
	LegoObject_ID objTeleportQueueIDs_TABLE[20];
	uint objTeleportQueue_COUNT;
	float MiniFigureRunAway; // (cfg: Main::MiniFigureRunAway)
	struct Vector3F mouseWorldPos;
	struct Point2I powerDrainBlocks[100]; // Temporary list used during powergrid calculation.
	uint powerDrainCount;
	struct Point2I poweredBlocks[100]; // Related to power grid calculation.
	struct Point2I unpoweredBlocks[100];
	uint poweredBlockCount;
	uint unpoweredBlockCount;
	uint MaxReturnedCrystals; // (cfg: Main::MaxReturnedCrystals)
	int MouseScrollBorder; // (cfg: Main::MouseScrollBorder)
	char * langHealth_toolTip; // (cfg: ToolTipInfo::HealthText)
	char * langEnergy_toolTip; // (cfg: ToolTipInfo::EnergyText)
	char * langCrystals_toolTip; // (cfg: ToolTipInfo::CrystalsText)
	char * langOre_toolTip; // (cfg: ToolTipInfo::OreText)
	char * langStuds_toolTip; // (cfg: ToolTipInfo::StudsText)
	char * langTools_toolTip; // (cfg: ToolTipInfo::ToolsText)
	char * langCarryObject_toolTip; // (cfg: ToolTipInfo::CarryObjectText)
	char * langDrivenBy_toolTip; // (cfg: ToolTipInfo::DrivenByText)
	char * langOreRequired_toolTip; // (cfg: ToolTipInfo::OreRequiredText)
	BOOL IsFallinsEnabled; // (cfg not: Level::NoFallins)
	float MinDistFor3DSoundsOnTopView; // (cfg: Main::MinDistFor3DSoundsOnTopView)
	enum ViewMode viewMode; // FirstPerson or TopDown
	enum GameFlags1 flags1;
	enum GameFlags2 flags2;
	enum GameFlags3 flags3; // only first byte is used(?)
	float InitialSlugTime; // (cfg: Level::InitialSlugTime)
	struct Point2F NextButtonPos; // (cfg: Main::NextButtonPos<WxH>)
	struct Point2F RepeatButtonPos; // (cfg: Main::BackButtonPos<WxH>)
	struct Image * NextButtonImage; // (cfg: Main::NextButton<WxH>)
	struct Image * RepeatButtonImage; // (cfg: Main::BackButton<WxH>)
	struct Image * BackArrowImage; // (cfg: Main::BackArrow)
	float FogRate; // (cfg: Level::FogRate)
	float timerGame_e3c;
	float elapsedAbs;
	float DrainTime; // (cfg: Main::DrainTime)
	uint ReinforceHits; // (cfg: Main::ReinforceHits)
	uint CDStartTrack; // (cfg: Main::CDStartTrack)
	uint CDTracks; // (cfg: Main::CDTracks)
	uint FallinMultiplier; // (cfg: Level::FallinMultiplier)
	BOOL hasFallins;
	struct Point2F menuNextPoint;
	struct Point2F menuPrevPoint;
	struct ColourRGBF DragBoxRGB; // (cfg: Level::DragBoxRGB)
	struct Image * DialogImage; // (cfg: Dialog::Image)
	struct Image * DialogContrastOverlay; // (cfg: Dialog::ContrastOverlay)
	struct TextWindow * DialogTextWndTitle; // (cfg: Dialog::TitleWindow)
	struct TextWindow * DialogTextWndMessage; // (cfg: Dialog::TextWindow)
	struct TextWindow * DialogTextWndOK; // (cfg: Dialog::OKWindow)
	struct TextWindow * DialogTextWndCancel; // (cfg: Dialog::CancelWindow)
	char * CreditsTextFile; // (cfg: Main::CreditsTextFile)
	char * CreditsBackAVI; // (cfg: Main::CreditsBackAVI)
	char * langUpgradeLevel_name[16]; // (cfg: UpgradeNames)
	int BuildingUpgradeCostOre; // (cfg: Main::BuildingUpgradeCostOre)
	int BuildingUpgradeCostStuds; // (cfg: Main::BuildingUpgradeCostStuds)
	char * renameInput;
	struct Point2F renamePosition;
	char * RenameReplace; // (cfg: Main::RenameReplace)
	char * EndGameAVI1; // (cfg: Level::EndGameAVI1)
	char * EndGameAVI2; // (cfg: Level::EndGameAVI2)
	struct Point2I mouseBlockPos; // (static, Game_unkGameLoop_FUN_00426450)
};

struct LegoCamera { // [LegoRR/LegoCamera.c|struct:0xbc] May be camera data (which is related to- but not the same as viewports)
	enum LegoCamera_Type type;
	struct LegoObject * trackObj;
	float trackRadarZoomSpeed;
	float trackRadarZoom;
	float trackRadarRotationSpeed; // A constant yaw H rotation speed applied to tracked radar objects
	int trackFPCameraFrame; // CameraFrameIndex for FP object SwapPolyFP
	struct Vector3F moveVector; // current 3D (really 2D) movement and directional speed
	struct Container * contCam; // only cont parented for FP type (child of contRoot if FP)
	struct Container * cont2; // child of contRoot
	struct Container * cont3; // child of contRoot
	struct Container * cont4; // child of cont2
	struct Container * contListener; // child of cont4 (topdown type only)
	undefined reserved1[64];
	float tilt; // (init: 0.0f) current tilt (Pitch, V Rotation)
	struct Range2F tiltRange; // min/max tilt (Pitch, V Rotation)
	float rotation; // (init: 0.0f) current yaw (Angle, H Rotation)
	struct Range2F rotationRange; // min/max yaw (Angle, H Rotation)
	float zoom; // (init: 200.0f) current dist (Zoom)
	struct Range2F zoomRange; // min/max dist (Zoom)
	float moveSpeed; // current 3D (really 2D) movement speed
	float shakeIntensity;
	float shakeDuration;
	float shakeTimer; // count-up timer until shakeDuration
	struct Vector3F shakeVector;
	enum CameraFlags flags;
};

typedef struct NERPsRuntime_Globs NERPsRuntime_Globs, *PNERPsRuntime_Globs;

typedef enum TutorialFlags { // [LegoRR/NERPs.c|flags:0x4|type:uint]
	TUTORIAL_FLAG_NOBLOCKACTION=2,
	TUTORIAL_FLAG_NOCALLTOARMS=128,
	TUTORIAL_FLAG_NOCAMERA=4096,
	TUTORIAL_FLAG_NOCYCLEUNITS=1024,
	TUTORIAL_FLAG_NOHELPWINDOW=2048,
	TUTORIAL_FLAG_NOICONS=1,
	TUTORIAL_FLAG_NOINFO=256,
	TUTORIAL_FLAG_NOMAP=4,
	TUTORIAL_FLAG_NOMULTISELECT=512,
	TUTORIAL_FLAG_NOOBJECTS=8,
	TUTORIAL_FLAG_NOOPTIONS=32,
	TUTORIAL_FLAG_NOPRIORITIES=64,
	TUTORIAL_FLAG_NORADAR=16,
	TUTORIAL_NONE=0
} TutorialFlags;

struct NERPsRuntime_Globs { // [LegoRR/NERPs.c|struct:0x68|tags:GLOBS]
	int registers[8];
	BOOL messagePermit; // allows NERPs messages to display in the TextMessage panel. (see: NERPFunc__SetMessagePermit)
	undefined4 reserved1;
	enum TutorialFlags tutorialFlags; // (this is the last field in a structure starting at 0x00)
	BOOL timerbool_2c; // used by UpdateTimers
	BOOL nextArrowDisabled; // (see: NERPFunc__SetMessage)
	float messageTimer; // (see: NERPFunc__GetMessageTimer)
	int hiddenObjectsFound; // (see: NERPFunc__SetHiddenObjectsFound)
	BOOL messageWait; // (see: NERPFunc__SetMessageWait)
	BOOL logFuncCalls; // (always 0)
	undefined4 reserved2;
	float timers[4];
	BOOL supressArrow; // (see: NERPFunc__SupressArrow)
	BOOL allowCameraMovement; // (see: NERPFunc__AllowCameraMovement)
	float tutorialIconTimer;
	BOOL objectiveSwitch; // (see: NERPFunc__SetObjectiveSwitch)
};

typedef struct Advisor_Globs Advisor_Globs, *PAdvisor_Globs;

typedef struct AdvisorAnimData AdvisorAnimData, *PAdvisorAnimData;

typedef enum Advisor_Type { // [LegoRR/Advisor.c|enum:0x4|type:int] "Acheived" is a source-accurate, but misspelled name
	Advisor_IconPoint_BackButton=4,
	Advisor_IconPoint_Normal=3,
	Advisor_IconPoint_TopButtons=5,
	Advisor_Objective=0,
	Advisor_ObjectiveAcheived=1,
	Advisor_ObjectiveAchieved=1,
	Advisor_ObjectiveFailed=2,
	Advisor_PanelPoint_ControlZoomIn=18,
	Advisor_PanelPoint_ControlZoomOut=19,
	Advisor_PanelPoint_InfoDockClose=12,
	Advisor_PanelPoint_InfoDockGoto=11,
	Advisor_PanelPoint_RadarMapView=10,
	Advisor_PanelPoint_RadarTaggedObjectView=7,
	Advisor_PanelPoint_RadarToggle=6,
	Advisor_PanelPoint_RadarZoomIn=8,
	Advisor_PanelPoint_RadarZoomOut=9,
	Advisor_PanelPoint_TopPanelCallToArms=16,
	Advisor_PanelPoint_TopPanelGoBack=17,
	Advisor_PanelPoint_TopPanelInfo=13,
	Advisor_PanelPoint_TopPanelOptions=14,
	Advisor_PanelPoint_TopPanelPriorities=15,
	Advisor_TalkInGame=20,
	Advisor_Type_Count=21
} Advisor_Type;

typedef enum Advisor_GlobFlags { // [LegoRR/Advisor.c|flags:0x4|type:uint]
	ADVISOR_GLOB_FLAG_ANIMATING=1,
	ADVISOR_GLOB_FLAG_LOOPING=2,
	ADVISOR_GLOB_FLAG_NONE=0
} Advisor_GlobFlags;

struct AdvisorAnimData { // [LegoRR/Advisor.c|struct:0xc]
	struct Container * cont;
	float loopStartTime; // ignored when not looping
	float loopEndTime; // ignored when not looping
};

struct Advisor_Globs { // [LegoRR/Advisor.c|struct:0x410|tags:GLOBS]
	char * positionName[21];
	struct AdvisorPositionData positions[21];
	char * animName[11];
	struct AdvisorAnimData anims[11];
	enum Advisor_Type currType;
	struct Container * cameraCont;
	struct Viewport * viewMain;
	float viewZ; // Z position of every advisor type (init: 0.96f)
	struct Container * lightCont;
	enum Advisor_GlobFlags flags;
};

typedef struct Effect_Globs Effect_Globs, *PEffect_Globs;

typedef struct EffectRockFall EffectRockFall, *PEffectRockFall;

typedef struct EffectMisc EffectMisc, *PEffectMisc;

typedef struct EffectElectricFenceBeam EffectElectricFenceBeam, *PEffectElectricFenceBeam;

struct EffectRockFall { // [LegoRR/Effects.c|struct:0xa4]
	struct Container * cont; // LWS:true, or ANIM:true
	struct Container * contTable[4];
	uint xBlockPosTable[4];
	uint yBlockPosTable[4];
	BOOL finishedTable[4];
	char * itemName; // (temporary stack buffer, BROKEN AF)
	int itemFrameCount;
	undefined field_0x4c;
	undefined field_0x4d;
	undefined field_0x4e;
	undefined field_0x4f;
	undefined field_0x50;
	undefined field_0x51;
	undefined field_0x52;
	undefined field_0x53;
	undefined field_0x54;
	undefined field_0x55;
	undefined field_0x56;
	undefined field_0x57;
	undefined field_0x58;
	undefined field_0x59;
	undefined field_0x5a;
	undefined field_0x5b;
	undefined field_0x5c;
	undefined field_0x5d;
	undefined field_0x5e;
	undefined field_0x5f;
	undefined field_0x60;
	undefined field_0x61;
	undefined field_0x62;
	undefined field_0x63;
	undefined field_0x64;
	undefined field_0x65;
	undefined field_0x66;
	undefined field_0x67;
	undefined field_0x68;
	undefined field_0x69;
	undefined field_0x6a;
	undefined field_0x6b;
	undefined field_0x6c;
	undefined field_0x6d;
	undefined field_0x6e;
	undefined field_0x6f;
	undefined field_0x70;
	undefined field_0x71;
	undefined field_0x72;
	undefined field_0x73;
	undefined field_0x74;
	undefined field_0x75;
	undefined field_0x76;
	undefined field_0x77;
	undefined field_0x78;
	undefined field_0x79;
	undefined field_0x7a;
	undefined field_0x7b;
	undefined field_0x7c;
	undefined field_0x7d;
	undefined field_0x7e;
	undefined field_0x7f;
	undefined field_0x80;
	undefined field_0x81;
	undefined field_0x82;
	undefined field_0x83;
	undefined field_0x84;
	undefined field_0x85;
	undefined field_0x86;
	undefined field_0x87;
	undefined field_0x88;
	undefined field_0x89;
	undefined field_0x8a;
	undefined field_0x8b;
	undefined field_0x8c;
	undefined field_0x8d;
	undefined field_0x8e;
	undefined field_0x8f;
	undefined field_0x90;
	undefined field_0x91;
	undefined field_0x92;
	undefined field_0x93;
	undefined4 bitfieldTable_94[4];
};

struct EffectMisc { // [LegoRR/Effects.c|struct:0x38]
	struct Container * contTable[10];
	uint count; // (max of 10)
	undefined4 field_2c;
	struct Container * cont; // LWS,true | LWO,true
	undefined4 field_34;
};

struct EffectElectricFenceBeam { // [LegoRR/Effects.c|struct:0xf4]
	struct Container * cont; // LWS:true
	struct Container * contTable[30];
	BOOL finishedTable[30];
};

struct Effect_Globs { // [LegoRR/Effects.c|struct:0xc78|tags:GLOBS]
	uint rockFallCompletedTypes[12]; // (size not related to [style:3])
	uint rockFallCompletedIndexes[12]; // (size not related to [style:3])
	struct EffectRockFall rockFallEffects[12]; // [style:3][type:4] LWS:true, or ANIM:true
	char * rockFallStyleName[4];
	uint rockFallStyleCount;
	int rockFallStyleIndex;
	struct EffectMisc lazerHitEffect; // LWS:true, or LWO:true
	struct EffectMisc pusherHitEffect; // LWS:true, or LWO:true
	struct EffectMisc freezerHitEffect; // LWS:true, or LWO:true
	struct EffectMisc pathDustEffect; // LWS:true, or LWO:true
	struct EffectMisc lavaErosionSmokeEffects[4]; // [1-4] LWS:true, or LWO:true
	struct EffectMisc birdScarerEffect; // LWS:true, or LWO:true
	struct EffectMisc upgradeEffect; // LWS:true, or LWO:true
	struct Container * boulderExplodeContTable[4];
	struct Container * smashPathContTable[4];
	struct EffectElectricFenceBeam efenceEffects[2]; // [shortBeam,longBeam]
	struct Container * explosionCont; // LWS:true
	struct Container * explosionContTable[4];
	uint explosionCount;
};

typedef struct Water_Globs Water_Globs, *PWater_Globs;

typedef struct Water_Pool Water_Pool, *PWater_Pool;

typedef struct Water_PoolMergePair Water_PoolMergePair, *PWater_PoolMergePair;

typedef struct Water_PoolDrain Water_PoolDrain, *PWater_PoolDrain;

typedef enum WaterFlags { // [LegoRR/Water.c|flags:0x4|type:uint]
	WATER_FLAG_FULL=2,
	WATER_FLAG_NONE=0,
	WATER_FLAG_SETTLED=4,
	WATER_FLAG_VISIBLE=1
} WaterFlags;

struct Water_PoolDrain { // [LegoRR/Water.c|struct:0x18]
	uint blockIndex; // The index of the block in the Water_Pool that this drain is connected to.
	enum Direction direction; // The direction water drains in.
	float drainWaterLevel;
	float elapsedUp_c; // elapsed count-up timer
	float elapsedDown_10; // elapsed count-down timer
	BOOL active; // Actively draining pool down to drainWaterLevel.
};

struct Water_Pool { // [LegoRR/Water.c|struct:0x428]
	struct Point2F blocks[100]; // Blocks are coordinates on the map that are part of this pool.
	uint blockCount;
	struct Water_PoolDrain drainList[10]; // Drains are sources where water can flow away into.
	uint drainCount;
	float highWaterLevel; // (init: -10000.0, or vertPos if PREDUG)
	float currWaterLevel;
	struct Container * contMeshTrans;
	enum WaterFlags flags;
};

struct Water_PoolMergePair { // [LegoRR/Water.c|struct:0x8] This struct seems to be used solely for qsort ordering by pointsCount(?)
	struct Water_Pool * mainPool; // Pool to take on the extra blocks of otherPool.
	struct Water_Pool * removedPool; // Pool to be merged into mainPool and then erased.
};

struct Water_Globs { // [LegoRR/Water.c|struct:0x29ec|tags:GLOBS] Module globals for the unfinished "Water flooding" feature.
	struct Water_Pool poolList[10]; // Table of isolated pools (reservoirs) of water.
	uint poolCount;
	struct Water_PoolMergePair mergeList[10]; // Pools that need to be merged at the end of Initialise. (This can be retired by using a better flood-fill algorithm).
	uint mergeCount;
	float digDepth; // (assigned, but never used)
};

typedef struct ToolTip_Globs ToolTip_Globs, *PToolTip_Globs;

struct ToolTip_Globs { // [LegoRR/ToolTip.c|struct:0x61c4|tags:GLOBS]
	struct Font * font; // (init only)
	uint fontHeight; // (init only)
	uint borderThickness; // (init only)
	uint paddingThickness; // (init only)
	uint appWidth; // (init only) Likely the bounds where tooltips are allowed to display.
	uint appHeight; // (init only)
	int offsetY; // (init only) Y offset from cursor?
	float hoverTime; // Duration before showing tooltip  (init only)
	float rgbFloats[9]; // [r:g:b(3)][norm:hi:lo(3)]  (init only)
	char * toolTipName[39]; // (init only)
	struct ToolTip toolTips[39];
};

typedef struct Info_Globs Info_Globs, *PInfo_Globs;

typedef struct InfoData InfoData, *PInfoData;

typedef struct InfoMessage InfoMessage, *PInfoMessage;

typedef enum Info_GlobFlags { // [LegoRR/Info.c|flags:0x4|type:uint]
	INFO_GLOB_FLAG_AUTOGAMESPEED=16,
	INFO_GLOB_FLAG_NONE=0,
	INFO_GLOB_FLAG_UNK_1=1,
	INFO_GLOB_FLAG_UNK_2=2,
	INFO_GLOB_FLAG_UNK_4=4,
	INFO_GLOB_FLAG_UNK_8=8
} Info_GlobFlags;

typedef enum InfoDataFlags { // [LegoRR/Info.c|flags:0x4|type:uint]
	INFOTYPE_FLAG_CHANGEGAMESPEED=65536,
	INFOTYPE_FLAG_NONE=0,
	INFOTYPE_FLAG_UNK_20000=131072
} InfoDataFlags;

typedef enum Info_Type { // [LegoRR/Info.c|enum:0x4|type:int]
	Info_AirDepleting=16,
	Info_AirLow=17,
	Info_AirOut=18,
	Info_AirRestored=19,
	Info_BuildingDeath=12,
	Info_CanTrainMinifigure=35,
	Info_CanUpgradeMinifigure=34,
	Info_CaveIn=7,
	Info_CavernLocated=9,
	Info_Constructed=8,
	Info_CrystalFound=0,
	Info_CrystalPower=29,
	Info_CrystalSeamFound=36,
	Info_DynamitePlaced=13,
	Info_FoundMinifigure=33,
	Info_GenericDeath=38,
	Info_GenericMonster=39,
	Info_GenericSeamFound=37,
	Info_IceRockMonster=4,
	Info_Landslide=6,
	Info_LavaErode=30,
	Info_LavaRockMonster=3,
	Info_LegoManDeath=10,
	Info_NoPower=14,
	Info_OreCollected=26,
	Info_OreSeamFound=1,
	Info_PathCompleted=32,
	Info_PowerDrain=15,
	Info_RockMonster=2,
	Info_SlugEmerge=31,
	Info_TrainDriver=20,
	Info_TrainDynamite=21,
	Info_TrainPilot=23,
	Info_TrainRepair=22,
	Info_TrainSailor=24,
	Info_TrainScanner=25,
	Info_Type_Count=40,
	Info_UnderAttack=5,
	Info_VehicleDeath=11,
	Info_WallDug=27,
	Info_WallReinforced=28
} Info_Type;

struct InfoMessage { // [LegoRR/Info.c|struct:0x14]
	struct InfoMessageInstance * instance;
	uint instanceCount;
	enum Info_Type infoType;
	float float_c;
	struct InfoMessage * next;
};

struct InfoData { // [LegoRR/Info.c|struct:0x14]
	char * text;
	void * ptr_4; // struct size of >= 0xc (int field_4, inf field_8)
	enum SFX_ID sfxType;
	float float_c;
	enum InfoDataFlags flags;
};

struct Info_Globs { // [LegoRR/Info.c|struct:0x6f4|tags:GLOBS]
	char * infoName[40];
	struct InfoData infoDataTable[40];
	struct InfoMessage infoMessageTable[40];
	uint infoMessageCount;
	struct Font * font;
	struct Image * OverFlowImage;
	int int_6ec;
	enum Info_GlobFlags flags;
};

typedef struct RadarMap_Globs RadarMap_Globs, *PRadarMap_Globs;

struct RadarMap_Globs { // [LegoRR/RadarMap.c|struct:0x3f4|tags:GLOBS]
	struct ColourRGBF colourTable[30]; // (constant, RGBf [0,255] -> [0,1] on RadarMap_Initialise)
	struct Point2I highlightBlockPos; // (init: (-1, -1)) Unused, but can highlight a radar map block in rgb(255,  0,  0).
	struct Vector4F arrowPointsFrom[20];
	struct Vector4F arrowPointsTo[20];
	uint arrowPointCount;
};

typedef struct Weapon_Globs Weapon_Globs, *PWeapon_Globs;

typedef struct WeaponStats WeaponStats, *PWeaponStats;

typedef struct Weapon_Lazer Weapon_Lazer, *PWeapon_Lazer;

typedef struct Weapon_Projectile Weapon_Projectile, *PWeapon_Projectile;

typedef enum Weapon_KnownType { // [LegoRR/Weapons.c|enum:0x4|type:int|tags:UNKNOWN] This is not the same as WeponTypes defined in Lego.cfg, these are fixed ID's that are then looked up by value. Boulder is never used.
	Weapon_KnownType_Boulder=4,
	Weapon_KnownType_Freezer=3,
	Weapon_KnownType_Laser=1,
	Weapon_KnownType_None=0,
	Weapon_KnownType_Pusher=2
} Weapon_KnownType;

struct Weapon_Projectile { // [LegoRR/Weapons.c|struct:0x2b0] Seen in a table of [10]. This is likely an extension of the Weapons module.
	BOOL isCurvedPath;
	struct BezierCurve curve;
	float totalDistance; // Curved paths only.
	float currDistance; // Curved paths only.
	struct Vector3F initialPos;
	struct Vector3F currPos;
	struct Vector3F lastPos;
	float speed;
	struct Vector3F dir;
	undefined4 unused_29c; // assigned to 0 but unused
	struct LegoObject * shooterObject;
	struct LegoObject * projectileObject;
	int weaponID;
	enum Weapon_KnownType knownWeapon;
};

struct WeaponStats { // [LegoRR/Weapons.c|struct:0x4b68]
	float objectCoefs[20][15][16]; // (cfg: [object] l:e:v:e:l:s, inits: -1.0f)
	BOOL isSlowDeath; // (cfg: SlowDeath exists)
	float slowDeathInitialCoef; // (cfg: SlowDeath[0]) Initial damage multiplier.
	float slowDeathDuration; // (cfg: SlowDeath[1])
	float rechargeTime; // (cfg: RechargeTime, default: 0.0f)
	float damage; // (cfg: DefaultDamage, default: 0.0f)
	float dischargeRate; // (cfg: DischargeRate)
	int ammo; // (cfg: Ammo, unused?)
	float weaponRange; // (cfg: WeaponRange, default: 150.0f)
	float wallDestroyTimes[18]; // (cfg: WallDestroyTime_[surface], defaults: 5.0f)
};

struct Weapon_Lazer { // [LegoRR/???|struct:0x10]
	struct Mesh * innerMesh; // Inner bright beam.
	struct Mesh * outerMesh; // Outer blue-ish beam glow.
	struct Container * cont;
	float timer; // Countdown duration in frames.
};

struct Weapon_Globs { // [LegoRR/Weapons.c|struct:0x1b90|tags:GLOBS]
	uint weaponCount;
	char * * weaponNameList;
	struct WeaponStats * weaponStatsList;
	struct Weapon_Lazer lazerList[10];
	struct Weapon_Projectile projectileList[10];
	struct Config * config;
};

typedef struct ElectricFence_Globs ElectricFence_Globs, *PElectricFence_Globs;

typedef struct ElectricFence_GridBlock ElectricFence_GridBlock, *PElectricFence_GridBlock;

typedef enum ElectricFence_GridFlags { // [LegoRR/ElectricFence.c|flags:0x4|type:uint]
	FENCEGRID_DIRECTION_FLAG_DOWN=4,
	FENCEGRID_DIRECTION_FLAG_LEFT=8,
	FENCEGRID_DIRECTION_FLAG_RIGHT=2,
	FENCEGRID_DIRECTION_FLAG_UP=1,
	FENCEGRID_DIRECTION_MASK=15,
	FENCEGRID_FLAG_NONE=0,
	FENCEGRID_FLAG_UNK_100=256
} ElectricFence_GridFlags;

struct ElectricFence_GridBlock { // [LegoRR/ElectricFence.c|struct:0xc|tags:BLOCKGRID] Note that the size when allocating fenceGrid is mistakenly 0x14, but lookup is performed with size 0xc
	struct ElectricFence_Block * efence;
	struct LegoObject * studObj; // Glowing lime stud  object placed between 2-block-wide connections
	enum ElectricFence_GridFlags flags;
};

struct ElectricFence_Globs { // [LegoRR/ElectricFence.c|struct:0x90|tags:GLOBS]
	struct ElectricFence_GridBlock * fenceGrid; // BlockElectricFence[width * height]
	struct Lego_Level * level;
	struct ElectricFence_Block * listSet[32];
	struct ElectricFence_Block * freeList;
	uint listCount; // (no flags)
};

typedef struct Camera_Globs Camera_Globs, *PCamera_Globs;

struct Camera_Globs { // [LegoRR/LegoCamera.c|struct:0x10|tags:GLOBS]
	float maxSpeed; // (cfg: CameraSpeed) maximum move speed of camera
	float deceleration; // (cfg: CameraDropOff) movement deceleration
	float acceleration; // (cfg: CameraAcceleration) movement acceleration
	int mouseScrollIndent; // (cfg: MouseScrollIndent) area around window borders for mouse movement
};

typedef struct Loader_Globs Loader_Globs, *PLoader_Globs;

typedef enum Loader_GlobFlags { // [LegoRR/Loader.c|flags:0x4|type:uint]
	LOADER_GLOB_FLAG_ENABLED=1,
	LOADER_GLOB_FLAG_NONE=0
} Loader_GlobFlags;

struct Loader_Globs { // [LegoRR/Loader.c|struct:0x290|tags:GLOBS]
	struct Image * LoadScreen;
	struct Font * font;
	struct LoaderSection sectionList[50];
	struct LoaderSection * current; // current section being loaded
	struct Image * ShutdownScreen;
	struct Image * ProgressBar;
	struct Area2F ProgressWindow;
	enum Direction ProgressDirection; // expand direction of progress bar: U, R, D, L
	char * LoadingText;
	uint LoadingWidth; // measured width of font with LoadingText
	float progressLast; // percentage of filesize for section (stores percent of last render)
	enum Loader_GlobFlags flags; // (1 = show loading bar)
};

typedef struct Interface_Globs Interface_Globs, *PInterface_Globs;

typedef enum Keys8 { // [Gods98/Input.c|enum:0x1|type:byte] Byte-sized Keys enum
	KEYPAD_0=82,
	KEYPAD_1=79,
	KEYPAD_2=80,
	KEYPAD_3=81,
	KEYPAD_4=75,
	KEYPAD_5=76,
	KEYPAD_6=77,
	KEYPAD_7=71,
	KEYPAD_8=72,
	KEYPAD_9=73,
	KEYPAD_ASTERISK=55,
	KEYPAD_DELETE=83,
	KEYPAD_ENTER=156,
	KEYPAD_FORWARDFLASH=181,
	KEYPAD_MINUS=74,
	KEYPAD_NUMLOCK=69,
	KEYPAD_PLUS=78,
	KEY_A=30,
	KEY_ALT=56,
	KEY_ALTGR=184,
	KEY_AT=40,
	KEY_B=48,
	KEY_BACKSLASH=86,
	KEY_BACKSPACE=14,
	KEY_C=46,
	KEY_CAPLOCK=58,
	KEY_CURSORDOWN=208,
	KEY_CURSORLEFT=203,
	KEY_CURSORUP=200,
	KEY_D=32,
	KEY_DELETE=211,
	KEY_E=18,
	KEY_EIGHT=9,
	KEY_END=207,
	KEY_EQUALS=13,
	KEY_ESCAPE=1,
	KEY_F=33,
	KEY_F1=59,
	KEY_F10=68,
	KEY_F11=87,
	KEY_F12=88,
	KEY_F2=60,
	KEY_F3=61,
	KEY_F4=62,
	KEY_F5=63,
	KEY_F6=64,
	KEY_F7=65,
	KEY_F8=66,
	KEY_F9=67,
	KEY_FIVE=6,
	KEY_FOUR=5,
	KEY_G=34,
	KEY_H=35,
	KEY_HASH=43,
	KEY_HOME=199,
	KEY_I=23,
	KEY_INSERT=210,
	KEY_J=36,
	KEY_K=37,
	KEY_L=38,
	KEY_LEFTARROW=51,
	KEY_LEFTBRACE=26,
	KEY_LEFTCTRL=29,
	KEY_LEFTSHIFT=42,
	KEY_M=50,
	KEY_MINUS=12,
	KEY_N=49,
	KEY_NINE=10,
	KEY_O=24,
	KEY_ONE=2,
	KEY_P=25,
	KEY_PGDN=209,
	KEY_PGUP=201,
	KEY_PRINTSCREEN=183,
	KEY_Q=16,
	KEY_QUESTIONMARK=53,
	KEY_R=19,
	KEY_RETURN=28,
	KEY_RIGHTARROW=52,
	KEY_RIGHTBRACE=27,
	KEY_RIGHTCTRL=157,
	KEY_RIGHTSHIFT=54,
	KEY_RSINGLEQUOTE=41,
	KEY_S=31,
	KEY_SCROLLLOCK=70,
	KEY_SEMICOLON=39,
	KEY_SEVEN=8,
	KEY_SIX=7,
	KEY_SPACE=57,
	KEY_T=20,
	KEY_TAB=15,
	KEY_THREE=4,
	KEY_TWO=3,
	KEY_U=22,
	KEY_V=47,
	KEY_W=17,
	KEY_X=45,
	KEY_Y=21,
	KEY_Z=44,
	KEY_ZERO=11,
	KEY__NONE=0
} Keys8;

typedef enum Interface_MenuItemFlags { // [LegoRR/Interface.c|flags:0x4|type:uint]
	INTERFACE_MENUITEM_FLAG_FLASH=4,
	INTERFACE_MENUITEM_FLAG_NONE=0,
	INTERFACE_MENUITEM_FLAG_UNK_1=1,
	INTERFACE_MENUITEM_FLAG_UNK_2=2,
	INTERFACE_MENUITEM_FLAG_UNK_8=8
} Interface_MenuItemFlags;

typedef enum Interface_MenuType { // [LegoRR/Interface.c|enum:0x4|type:int]
	Interface_Menu_BuildBuilding=19,
	Interface_Menu_BuildLargeVehicle=21,
	Interface_Menu_BuildSmallVehicle=20,
	Interface_Menu_Building=13,
	Interface_Menu_Construction=4,
	Interface_Menu_ElectricFence=14,
	Interface_Menu_Encyclopedia=23,
	Interface_Menu_Erode=2,
	Interface_Menu_FP=15,
	Interface_Menu_GetTool=16,
	Interface_Menu_Ground=1,
	Interface_Menu_LandVehicle=10,
	Interface_Menu_LegoMan=9,
	Interface_Menu_Main=0,
	Interface_Menu_PlaceFence=3,
	Interface_Menu_Rubble=5,
	Interface_Menu_Tracker=8,
	Interface_Menu_TrainSkill=17,
	Interface_Menu_Type_Count=22,
	Interface_Menu_UNK_6=6,
	Interface_Menu_UnmannedVehicle=12,
	Interface_Menu_UpgradeVehicle=18,
	Interface_Menu_Wall=7,
	Interface_Menu_WaterVehicle=11
} Interface_MenuType;

typedef enum WallHighlightType { // [LegoRR/Lego.c|enum:0x4|type:int|tags:BIGENUMALIAS] (white, gray, red, green, blue, dark-yellow)
	WALLHIGHLIGHT_DIG=1,
	WALLHIGHLIGHT_DYNAMITE=2,
	WALLHIGHLIGHT_NONE=0,
	WALLHIGHLIGHT_REINFORCE=3,
	WALLHIGHLIGHT_SELECTED=4,
	WALLHIGHLIGHT_TUTORIAL=5
} WallHighlightType;

typedef enum Interface_GlobFlags { // [LegoRR/Interface.c|flags:0x4|type:uint]
	INTERFACE_GLOB_FLAG_NONE=0,
	INTERFACE_GLOB_FLAG_UNK_100=256,
	INTERFACE_GLOB_FLAG_UNK_1000=4096,
	INTERFACE_GLOB_FLAG_UNK_20=32,
	INTERFACE_GLOB_FLAG_UNK_200=512,
	INTERFACE_GLOB_FLAG_UNK_2000=8192,
	INTERFACE_GLOB_FLAG_UNK_4=4,
	INTERFACE_GLOB_FLAG_UNK_40=64,
	INTERFACE_GLOB_FLAG_UNK_400=1024,
	INTERFACE_GLOB_FLAG_UNK_4000=16384,
	INTERFACE_GLOB_FLAG_UNK_80=128,
	INTERFACE_GLOB_FLAG_UNK_800=2048
} Interface_GlobFlags;

struct Interface_Globs { // [LegoRR/Interface.c|struct:0x14ac|tags:GLOBS]
	struct Font * font;
	struct Image * iconPanelImages[11]; // (cfg: InterfaceSurroundImages[0]) g_InterfaceSurroundImages
	struct Point2F iconPanelIconOffsets[11]; // (cfg: InterfaceSurroundImages[1,2]) 
	struct Image * iconPanelNoBackImages[11]; // (cfg: InterfaceSurroundImages[5]) 
	struct Point2F iconPanelNoBackIconOffsets[11]; // (cfg: InterfaceSurroundImages[6,7]) 
	struct Image * backButtonImage_hl; // (cfg: InterfaceBackButton[2])
	struct Image * backButtonImage_pr; // (cfg: InterfaceBackButton[3])
	struct Point2F iconPanelBackButtonOffsets[11]; // (cfg: InterfaceSurroundImages[3,4]) Point2F_ARRAY_004dde6c
	struct Size2I backButtonSize; // (cfg: InterfaceBackButton[0,1])
	char * backButtonText; // (cfg: InterfaceBackButton[4])
	char * menuItemName[74];
	struct Image * menuItemIcons[74];
	struct Image * menuItemIcons_no[74];
	struct Image * menuItemIcons_pr[74];
	char * langMenuItemTexts[74];
	enum SFX_ID sfxMenuItemTexts[74];
	enum Keys8 menuItemF2keys[74];
	undefined2 padding1;
	enum Interface_MenuItemFlags menuItemFlags[74]; // (0x4: flashing)
	struct Image * * vehicleItemIcons;
	struct Image * * buildingItemIcons;
	struct Image * * vehicleItemIcons_no;
	struct Image * * buildingItemIcons_no;
	struct Image * * vehicleItemIcons_pr;
	struct Image * * buildingItemIcons_pr;
	char * langMenuItemTexts_no[74];
	enum SFX_ID sfxMenuItemTexts_no[74];
	enum Keys8 * vehicleItemF2Keys;
	enum Keys8 * buildingItemF2Keys;
	enum Interface_MenuItemFlags * vehicleItemFlags;
	enum Interface_MenuItemFlags * buildingItemFlags;
	uint menuItemClicks[74];
	uint * vehicleItemClicks;
	uint * buildingItemClicks;
	BOOL menuItemUnkBools[74]; // (default: false)
	struct Interface_Menu menuList[24];
	struct Point2I selBlockPos;
	enum Interface_MenuType currMenuType;
	struct Point2F currMenuPosition; // (init: 565,18) Current sliding position of menu. Point2F_004decd0
	enum LegoObject_Type objType_f80;
	LegoObject_ID objID_f84;
	struct Point2F slideStartPosition; // Point2F_004dece0
	struct Point2F slideEndPosition; // (init: pointf_f78) Point2F_004dece8
	float slideSpeed; // (init: 750.0f / 25.0f)
	struct Point2I highlightBlockPos;
	enum Interface_MenuType nextMenuType;
	enum Interface_MenuItemType menuItemType_fa8;
	undefined4 field_fac;
	undefined4 field_fb0;
	struct Area2F areaf_fb4;
	BOOL flashingState; // For block and icon flashing. false = off, true = on.
	float timer_fc8;
	enum Advisor_Type advisorType_fcc;
	enum Interface_MenuItemType menuItemType_fd0;
	enum LegoObject_Type objType_fd4;
	LegoObject_ID objID_fd8;
	BOOL objectBools[20][15];
	struct Image * dependenciesPlusImage;
	struct Image * dependenciesMinusImage;
	float float_1494;
	enum WallHighlightType origWallHighlight; // (backup for when a wall has a queued action, but we want it to show the selected colour)
	enum SFX_ID sfxType_149c;
	enum Interface_GlobFlags flags;
	enum SFX_ID sfxType_14a4;
	BOOL sfxPlaying;
};

typedef struct Teleporter_Globs Teleporter_Globs, *PTeleporter_Globs;

struct Teleporter_Globs { // [LegoRR/Teleporter.c|struct:0x10|tags:GLOBS]
	uint count;
	int intValue_40; // (const: 40)
	struct TeleporterService * current;
	float floatValue_3_0; // (const: 3.0)
};

typedef struct Fallin_Globs Fallin_Globs, *PFallin_Globs;

struct Fallin_Globs { // [LegoRR/Fallin.c|struct:0x4|tags:GLOBS] Just a single field for Fallins (most other settings are found in Lego_Globs)
	uint NumberOfLandSlidesTillCaveIn;
};

typedef struct Message_Globs Message_Globs, *PMessage_Globs;

typedef struct Message_Event Message_Event, *PMessage_Event;

struct Message_Event { // [LegoRR/Message.c|struct:0x14]
	enum Message_Type type;
	struct LegoObject * argumentObj; // (this argument is only used for objects)
	undefined4 argument2; // (this can be many types, and depends on the message)
	struct Point2I blockPos;
};

struct Message_Globs { // [LegoRR/Message.c|struct:0x14380|tags:GLOBS]
	struct Message_Event eventLists[2][2048];
	uint eventCounts[2];
	BOOL eventAB; // Whether to use index 0 or 1 of eventLists, eventCounts.
	struct LegoObject * selectedUnitList[100];
	enum Keys8 hotKeyKeyList[10];
	undefined2 padding1;
	struct Message_Event hotKeyEventList[10];
	char * messageName[65];
	undefined4 reserved1;
	uint selectedUnitCount;
	uint hotKeyCount;
};

typedef struct Encyclopedia_Globs Encyclopedia_Globs, *PEncyclopedia_Globs;

typedef enum Encyclopedia_GlobFlags { // [LegoRR/Encyclopedia.c|flags:0x4|type:uint]
	ENCYCLOPEDIA_GLOB_FLAG_ACTIVE=1,
	ENCYCLOPEDIA_GLOB_FLAG_NEEDSTEXT=2,
	ENCYCLOPEDIA_GLOB_FLAG_NONE=0
} Encyclopedia_GlobFlags;

struct Encyclopedia_Globs { // [LegoRR/Encyclopedia.c|struct:0x24|tags:GLOBS]
	struct File * * vehicleFiles;
	struct File * * minifigureFiles;
	struct File * * rockmonsterFiles;
	struct File * * buildingFiles;
	struct File * powercrystalFile;
	struct File * oreFile;
	struct File * currentObjFile;
	struct LegoObject * currentObj;
	enum Encyclopedia_GlobFlags flags;
};

typedef struct Pointer_Globs Pointer_Globs, *PPointer_Globs;

typedef enum Pointer_Type { // [LegoRR/Pointer.c|enum:0x4|type:int]
	Pointer_Blank=1,
	Pointer_CanBuild=22,
	Pointer_CannotBuild=23,
	Pointer_CantDrill=4,
	Pointer_CantDynamite=25,
	Pointer_CantGo=7,
	Pointer_CantHelp=15,
	Pointer_CantPickUp=27,
	Pointer_CantReinforce=11,
	Pointer_CantTeleport=9,
	Pointer_CantZoom=54,
	Pointer_Clear=5,
	Pointer_Drill=3,
	Pointer_Dynamite=24,
	Pointer_GetIn=17,
	Pointer_GetOut=18,
	Pointer_Go=6,
	Pointer_Help=14,
	Pointer_LegoManCantDig=29,
	Pointer_LegoManCantGo=37,
	Pointer_LegoManCantPickUp=33,
	Pointer_LegoManClear=41,
	Pointer_LegoManDig=31,
	Pointer_LegoManGo=39,
	Pointer_LegoManPickUp=35,
	Pointer_NotOkay=21,
	Pointer_Okay=20,
	Pointer_PickUp=26,
	Pointer_PickUpOre=28,
	Pointer_PutDown=16,
	Pointer_RadarPan=12,
	Pointer_Reinforce=10,
	Pointer_Selected=2,
	Pointer_Standard=0,
	Pointer_SurfaceType_CrystalSeam=52,
	Pointer_SurfaceType_Hard=44,
	Pointer_SurfaceType_Immovable=43,
	Pointer_SurfaceType_Lake=51,
	Pointer_SurfaceType_Lava=48,
	Pointer_SurfaceType_Loose=46,
	Pointer_SurfaceType_Medium=45,
	Pointer_SurfaceType_OreSeam=50,
	Pointer_SurfaceType_RechargeSeam=53,
	Pointer_SurfaceType_Soil=47,
	Pointer_SurfaceType_Water=49,
	Pointer_Teleport=8,
	Pointer_TrackObject=13,
	Pointer_TutorialBlockInfo=19,
	Pointer_Type_Count=56,
	Pointer_VehicleCantDig=30,
	Pointer_VehicleCantGo=38,
	Pointer_VehicleCantPickUp=34,
	Pointer_VehicleClear=42,
	Pointer_VehicleDig=32,
	Pointer_VehicleGo=40,
	Pointer_VehiclePickUp=36,
	Pointer_Zoom=55
} Pointer_Type;

struct Pointer_Globs { // [LegoRR/Pointer.c|struct:0x468|tags:GLOBS]
	enum Pointer_Type currType;
	struct Image * images[56]; // (each item is either an ImageBMP or ImageFlic)
	BOOL imageIsFlic[56];
	struct Point2I flicOffsets[56];
	char * pointerName[56];
	float timer; // Countdown timer to change pointer(?)
};

typedef struct Erode_Globs Erode_Globs, *PErode_Globs;

struct Erode_Globs { // [LegoRR/Erode.c|struct:0xfa14|tags:GLOBS]
	struct Point2I UnkBlocksList[2000];
	uint UnkBlocksCount;
	struct Point2I activeBlocks[2000];
	BOOL activeStates[2000];
	float activeTimers[2000]; // (countdown timers)
	struct Point2I lockedBlocks[1000];
	float lockedTimers[1000]; // (countdown timers)
	BOOL lockedStates[1000];
	float elapsedTimer; // (count-up elapsed timer)
	float ErodeTriggerTime; // (init: Lego.cfg)
	float ErodeErodeTime; // (init: Lego.cfg)
	float ErodeLockTime; // (init: Lego.cfg)
};

typedef struct ObjectRecall_Globs ObjectRecall_Globs, *PObjectRecall_Globs;

typedef struct ObjectRecallEntry ObjectRecallEntry, *PObjectRecallEntry;

struct ObjectRecallEntry { // [LegoRR/ObjectRecall.c|struct:0x14] Object recall structure (for .osf file)
	enum LegoObject_AbilityFlags abilityFlags; // LiveFlags5
	uint level;
	char customName[12];
};

struct ObjectRecall_Globs { // [LegoRR/ObjectRecall.c|struct:0x18|tags:GLOBS]
	struct ObjectRecallEntry * recallList;
	uint recallUsed;
	uint recallCapacity;
	struct ObjectRecallEntry * recallNewList;
	uint recallNewCount;
	BOOL loaded;
};

typedef struct Text_Globs Text_Globs, *PText_Globs;

typedef enum Text_GlobFlags { // [LegoRR/Text.c|flags:0x4|type:uint]
	TEXT_GLOB_FLAG_NONE=0,
	TEXT_GLOB_FLAG_UNK_1=1,
	TEXT_GLOB_FLAG_UNK_4=4
} Text_GlobFlags;

struct Text_Globs { // [LegoRR/Text.c|struct:0x4dc|tags:GLOBS]
	char * textName[26];
	char * textMessages[26];
	struct Image * textImages[26];
	char textImagesSFX[26][32];
	enum Text_Type currType;
	uint textCount;
	uint jankCounter; // See Text_Update for description. Jank is in the name for a reason...
	char * currText; // Pointer to NERPsMessage raw text
	float float_488;
	struct TextWindow * textOnlyWindow;
	struct TextWindow * textImageWindow; // Same as textOnlyWindow, but used instead when there's an image.
	undefined4 reserved1;
	uint uint_498;
	struct Area2F MsgPanel_Rect1;
	float float_4ac;
	float MsgPanel_Float20;
	float MsgPanel_Float42;
	float float_4b8;
	struct Area2F MsgPanel_Rect2;
	struct Point2I TextImagePosition;
	enum Text_GlobFlags TextPanelFlags; // (0x1: ?, 0x4: ?)
	float TextPauseTime;
};

typedef struct NERPsFile_Globs NERPsFile_Globs, *PNERPsFile_Globs;

typedef struct NERPsInstruction NERPsInstruction, *PNERPsInstruction;

typedef struct NERPMessageImage NERPMessageImage, *PNERPMessageImage;

typedef enum NERPsOpcode { // [LegoRR/NERPs.c|enum:0x2|type:ushort]
	OP_CALL=2,
	OP_CMP=1,
	OP_GOTO=8,
	OP_LABEL=4,
	OP_PUSH=0
} NERPsOpcode;

struct NERPsInstruction { // [LegoRR/NERPs.c|struct:0x4]
	short value;
	enum NERPsOpcode opcode;
};

struct NERPMessageImage { // [LegoRR/NERPs.c|struct:0x8]
	char * key;
	struct Image * image;
};

struct NERPsFile_Globs { // [LegoRR/NERPs.c|struct:0xb4|tags:GLOBS]
	BOOL camIsLockedOn;
	uint camLockOnRecord; // Record object pointer (0-indexed).
	struct Point2F camLockOnPos; // Assigned based on the lock-on object, but never used.
	struct LegoObject * camLockOnObject;
	BOOL camIsZooming;
	float camZoomTotal; // Total amount to zoom specified by NERPs function.
	float camZoomMoved; // Amount of the total that has been zoomed. (amount left == total - moved)
	BOOL camIsRotating;
	float camRotTotal; // Total amount to rotate specified by NERPs function.
	float camRotMoved; // Amount of the total that has been rotated. (amount left == total - moved)
	struct NERPsInstruction * instructions; // (script fileData)
	uint scriptSize; // (script fileSize)
	undefined4 reserved1[11];
	char * messageBuffer; // (message fileData)
	uint lineCount;
	char * * lineList;
	uint imageCount;
	struct NERPMessageImage * imageList; // :imageKey filePath
	uint soundCount;
	struct NERPMessageSound * soundList; // $soundKey filePath
	uint lineIndexArray_7c[9];
	uint uint_a0;
	int int_a4; // (signedness known due to constant comparison)
	uint uint_a8;
	int RecordObjectPointer;
	BOOL AdvisorTalkingMode;
};

typedef struct Flocks_Globs Flocks_Globs, *PFlocks_Globs;

struct Flocks_Globs { // [LegoRR/Flocks.c|struct:0x10|tags:GLOBS]
	float Turn;
	float Speed;
	float Tightness;
	float GoalUpdate;
};

typedef struct LegoObject_Globs LegoObject_Globs, *PLegoObject_Globs;

typedef enum LegoObject_GlobFlags { // [LegoRR/LegoObject.c|flags:0x4|type:uint] LegoObject_GlobFlags, ReservedPool LiveObject INITFLAGS
	OBJECT_GLOB_FLAG_CYCLEUNITS=64,
	OBJECT_GLOB_FLAG_INITIALISED=1,
	OBJECT_GLOB_FLAG_LEVELENDING=32,
	OBJECT_GLOB_FLAG_NONE=0,
	OBJECT_GLOB_FLAG_POWERNEEDSUPDATE=8,
	OBJECT_GLOB_FLAG_POWERUPDATING=4,
	OBJECT_GLOB_FLAG_REMOVING=2,
	OBJECT_GLOB_FLAG_UPDATING=16
} LegoObject_GlobFlags;

typedef struct HiddenObject HiddenObject, *PHiddenObject;

struct HiddenObject { // [LegoRR/LegoObject.c|struct:0x2c] Name is only guessed
	struct Point2I blockPos; // (ol: xPos, yPos -> blockPos)
	struct Point2F worldPos; // (ol: xPos, yPos)
	float heading; // (ol: heading -> radians)
	void * model; // (ol: type)
	enum LegoObject_Type type; // (ol: type)
	LegoObject_ID id; // (ol: type)
	float health; // (ol: health)
	char * olistID; // (ol: Object%i)
	char * olistDrivingID; // (ol: driving)
};

struct LegoObject_Globs { // [LegoRR/LegoObject.c|struct:0xc644|tags:GLOBS]
	struct LegoObject * listSet[32];
	struct LegoObject * freeList;
	enum SFX_ID objectTtSFX[20][15]; // [objType:20][objIndex:15] (cfg: ObjTtSFXs)
	char * activityName[79]; // [activityType:79]
	void * UnkSurfaceGrid_1_TABLE;
	void * UnkSurfaceGrid_2_TABLE;
	uint UnkSurfaceGrid_COUNT;
	float radarSurveyCycleTimer; // Timer for how often survey scans update.
	uint listCount;
	enum LegoObject_GlobFlags flags;
	uint toolNullIndex[11]; // [toolType:11]
	uint objectTotalLevels[20][15][16]; // [objType:20][objIndex:15][objLevel:16] 
	uint objectPrevLevels[20][15][16]; // [objType:20][objIndex:15][objLevel:16] 
	uint NERPs_TrainFlags;
	struct LegoObject * minifigureObj_9cb8;
	struct Point2I slugHoleBlocks[20];
	struct Point2I rechargeSeamBlocks[10];
	uint slugHoleCount;
	uint rechargeSeamCount;
	struct HiddenObject hiddenObjects[200];
	uint hiddenObjectCount;
	float dischargeBuildup; // When >= 1.0f, consume one crystal.
	struct SaveStruct_18 savestruct18_c01c;
	struct LegoObject * cycleUnits[256];
	uint cycleUnitCount;
	uint cycleBuildingCount;
	struct LegoObject * liveObjArray100_c43c[100]; // Used for water docking vehicles?
	uint uintCount_c5cc; // Count for liveObjArray100_c43c
	char * abilityName[6]; // [abilityType:6]
	struct Image * ToolTipIcons_Abilities[6]; // [abilityType:6] (cfg: ToolTipIcons)
	struct Image * ToolTipIcons_Tools[11]; // [toolType:11] (cfg: ToolTipIcons)
	struct Image * ToolTipIcon_Blank; // (cfg: ToolTipIcons::Blank)
	struct Image * ToolTipIcon_Ore; // (cfg: ToolTipIcons::Ore)
	uint BuildingsTeleported;
	float s_sound3DUpdateTimer;
	undefined4 s_stepCounter_c63c; // (static, counter %4 for step SFX)
	void * * s_FlocksDestroy_c640; // (static, Struct 0x10, used in Flocks activities (QUICK_DESTROY??))
};

typedef struct DamageFont_Globs DamageFont_Globs, *PDamageFont_Globs;

typedef struct DamageFontData DamageFontData, *PDamageFontData;

struct DamageFontData { // [LegoRR/DamageFont.c|struct:0x20]
	struct Container * ownerCont;
	struct Mesh * mesh;
	uint groupCount;
	float float_c;
	float float_10;
	float timerDown;
	float timerUp;
	uint flags;
};

struct DamageFont_Globs { // [LegoRR/DamageFont.c|struct:0x16c|tags:GLOBS]
	struct Container_Texture * fontTextDigitsTable[10];
	struct Container_Texture * fontTextMinus;
	struct DamageFontData instanceTable[10];
};

typedef struct LegoUpdate_Globs LegoUpdate_Globs, *PLegoUpdate_Globs;

struct LegoUpdate_Globs { // [LegoRR/Lego.c|struct:0x14|tags:GLOBS] (miscellaneous static function variables used during game update loop)
	float renameInputTimer; // (ram: 12.5)
	float dripSFXTimer; // (ram: 75.0)
	float ambientSFXTimer; // (ram: 250.0)
	float dbgRollOffFactorValue; // (ram: 1.0)
	float currentBaseLightLevel; // (ram: 0.7)
};

typedef struct Priorities_Globs Priorities_Globs, *PPriorities_Globs;

typedef enum Priorities_GlobFlags { // [LegoRR/Priorities.c|flags:0x4|type:uint]
	PRIORITIES_GLOB_FLAG_HOVER=1,
	PRIORITIES_GLOB_FLAG_NONE=0,
	PRIORITIES_GLOB_FLAG_PRESSED=2
} Priorities_GlobFlags;

struct Priorities_Globs { // [LegoRR/Priorities.c|struct:0x4c0|tags:GLOBS]
	char * langPriorityName[27]; // [AI_Priority_Count]
	struct Image * priorityImage[27]; // [AI_Priority_Count]
	struct Image * priorityPressImage[27]; // [AI_Priority_Count]
	struct Image * priorityOffImage[27]; // [AI_Priority_Count]
	enum SFX_ID sfxPriorityName[27]; // [AI_Priority_Count]
	enum AI_Priority buttonTypes[27]; // Priority types for each button at index.
	struct Point2F buttonPoints[27]; // Positions for each button at index.
	enum AI_Priority initialTypes[27]; // Initial button positions on level start, and when reset.
	uint initialValues[27]; // Initial values set by AITask_Game_SetPriorityValue for each button at index
	BOOL initialOff[27]; // Initial OFF state for each button at index
	uint count; // Number of priority buttons for level.
	struct Area2F hoverArea;
	uint pressIndex;
	enum Priorities_GlobFlags flags;
};

typedef struct PTL_Globs PTL_Globs, *PPTL_Globs;

struct PTL_Globs { // [LegoRR/PTL.c|struct:0x144|tags:GLOBS]
	struct PTL_Property table[40];
	uint count;
};

typedef struct Reward_Globs Reward_Globs, *PReward_Globs;

typedef struct RewardScroll RewardScroll, *PRewardScroll;

typedef struct RewardScrollLabel RewardScrollLabel, *PRewardScrollLabel;

typedef enum RewardScrollFlags { // [LegoRR/Rewards.c|flags:0x4|type:uint]
	REWARDSCROLL_NONE=0,
	REWARDSCROLL_UNK_1=1,
	REWARDSCROLL_UNK_2=2
} RewardScrollFlags;

typedef enum RewardScrollLabelMode { // [LegoRR/Rewards.c|enum:0x4|type:uint] Inclusive mode, None does nothing, WINDOW also performs IMAGE and TEXT, IMAGE also performs TEXT, TEXT does only that
	REWARDSCROLL_MODE_IMAGE=2,
	REWARDSCROLL_MODE_NONE=0,
	REWARDSCROLL_MODE_TEXT=3,
	REWARDSCROLL_MODE_WINDOW=1
} RewardScrollLabelMode;

typedef enum RewardScrollLabelFlags { // [LegoRR/Rewards.c|flags:0x4|type:uint]
	REWARDSCROLL_LABEL_CENTERED=1,
	REWARDSCROLL_LABEL_NONE=0,
	REWARDSCROLL_LABEL_NOSCROLL=2
} RewardScrollLabelFlags;

struct RewardScroll { // [LegoRR/Rewards.c|struct:0x28]
	float yInitial; // (init: appHeight() / 20.0f)
	float xPos; // (init: 0.0f)
	float yPos; // (init: appHeight() / 20.0f) scrollCountdown??
	float width; // (init: appWidth())
	float height; // (init: appHeight() - appHeight() / 3.5f)
	float scrollSpeed;
	float curScrollY; // (init: set to 400.0 after Create function)
	uint labelCount;
	struct RewardScrollLabel * * labels;
	enum RewardScrollFlags flags;
};

struct Reward_Globs { // [LegoRR/Rewards.c|struct:0x3250|tags:GLOBS]
	BOOL display; // (cfg: Display, default: false) Is the rewards screen shown on mission end?
	BOOL centerText; // (cfg: CentreText, default: false)
	undefined4 reserved1;
	float timer; // (cfg: Timer, default: 76.9375f)
	struct RewardLevel * base; // base reward state template
	struct RewardLevel * level; // level requirements reward state
	struct Image * wallpaper; // (cfg: Wallpaper)
	struct RewardLevel current; // current reward state, modified during gameplay
	float scrollSpeed; // (cfg: ScrollSpeed)
	float vertSpacing; // (cfg: VertSpacing)
	undefined4 reserved2[3];
	char * fontName; // (cfg: Font)
	struct Font * font; // (cfg: Font)
	char * titleFontName; // (cfg: TitleFont)
	struct Font * titleFont; // (cfg: TitleFont)
	char * backFontName; // (cfg: BackFont)
	struct Font * backFont; // (cfg: BackFont)
	struct Config * config;
	char * gameName;
	struct RewardScroll * scroll;
	struct Point2F saveButtonPosition; // (cfg: SaveButton[4,5])
	struct Image * saveButton; // (cfg: SaveButton[0])
	struct Image * saveButton_hi; // (cfg: SaveButton[1])
	struct Image * saveButton_in; // (cfg: SaveButton[2])
	struct Image * saveButton_dim; // (cfg: SaveButton[3])
	struct Point2F advanceButtonPosition; // (cfg: AdvanceButton[4,5])
	struct Image * advanceButton; // (cfg: AdvanceButton[0])
	struct Image * advanceButton_hi; // (cfg: AdvanceButton[1])
	struct Image * advanceButton_in; // (cfg: AdvanceButton[2])
	struct Image * advanceButton_dim; // (cfg: AdvanceButton[3])
	char * completeText; // (cfg: CompleteText)
	char * failedText; // (cfg: FailedText)
	char * quitText; // (cfg: QuitText)
	struct Point2I textPos; // (cfg: TextPos)
	char statusMessage[32];
	BOOL displayText; // (cfg: DisplayText, default: true)
	BOOL displayImages; // (cfg: DisplayImages, default: true)
	BOOL displayFlics; // (cfg: DisplayFlics, default: true)
};

struct RewardScrollLabel { // [LegoRR/Rewards.c|struct:0x20]
	enum RewardScrollLabelMode mode; // (0=none, 1=txtWnd+, 2=image+, 3=font+)
	float xPos;
	float yPos; // (vertSpacing?)
	struct TextWindow * textWnd;
	struct Image * image;
	char * text;
	struct Font * font;
	enum RewardScrollLabelFlags flags; // ( 1 = centered??, 2 = ? )
};

typedef struct ObjInfo_Globs ObjInfo_Globs, *PObjInfo_Globs;

typedef enum ObjInfo_GlobFlags { // [LegoRR/ObjInfo.c|flags:0x4|type:uint]
	OBJINFO_GLOB_FLAG_BUBBLEIMAGES=16,
	OBJINFO_GLOB_FLAG_HEALTHBAR=2,
	OBJINFO_GLOB_FLAG_HEALTHBAR_VERTICAL=8,
	OBJINFO_GLOB_FLAG_HUNGERIMAGES=1,
	OBJINFO_GLOB_FLAG_NONE=0
} ObjInfo_GlobFlags;

struct ObjInfo_Globs { // [LegoRR/ObjInfo.c|struct:0x78|tags:GLOBS]
	enum ObjInfo_GlobFlags flags;
	struct Point2F HealthBarPosition;
	struct Size2F HealthBarWidthHeight;
	uint HealthBarBorderSize;
	float HealthBarBorderRGB_r[3]; // [normal, hi, lo]
	float HealthBarBorderRGB_g[3]; // [normal, hi, lo]
	float HealthBarBorderRGB_b[3]; // [normal, hi, lo]
	struct ColourRGBF HealthBarRGB;
	struct ColourRGBF HealthBarBackgroundRGB;
	struct Point2F HungerPosition;
	struct Image * HungerImages[5];
	struct Point2F BubblePosition;
};

typedef enum TeleportObjectType { // [LegoRR/Teleporter.c|flags:0x4|type:uint|tags:FLAGASENUM]
	TELEPORT_SERVIVE_BARRIER=256,
	TELEPORT_SERVIVE_BOULDER=16,
	TELEPORT_SERVIVE_BUILDING=8,
	TELEPORT_SERVIVE_DYNAMITE=128,
	TELEPORT_SERVIVE_ELECTRICFENCE=1024,
	TELEPORT_SERVIVE_MINIFIGURE=2,
	TELEPORT_SERVIVE_NONE=0,
	TELEPORT_SERVIVE_OOHSCARY=4096,
	TELEPORT_SERVIVE_ORE=64,
	TELEPORT_SERVIVE_POWERCRYSTAL=32,
	TELEPORT_SERVIVE_ROCKMONSTER=4,
	TELEPORT_SERVIVE_SPIDERWEB=2048,
	TELEPORT_SERVIVE_UPGRADEPART=512,
	TELEPORT_SERVIVE_VEHICLE=1
} TeleportObjectType;

typedef enum CLGenResources { // [CLGen/resource.rc|enum:0x4|type:int|tags:RESOURCE]
	CLGEN_MAIN_ICON=1,
	CLGEN_MAIN_ICONGROUP=103,
	CLGEN_SELECTOR_DIALOG=101
} CLGenResources;

typedef enum LegoRRResources { // [Gods98init/resource.rc|enum:0x4|type:int|tags:RESOURCE]
	LEGORR_MAIN_ICON=1,
	LEGORR_MAIN_ICONGROUP=113,
	LEGORR_MODESELECTION_DIALOG=101
} LegoRRResources;

typedef enum CLGenDialogControls { // [CLGen/resource.rc|enum:0x4|type:int|tags:RESOURCE]
	CLGEN_ID_CANCEL=2,
	CLGEN_ID_OK=1,
	CLGEN_ID_SELECT_DROPDOWNLIST=1001,
	CLGEN_ID_SELECT_LABEL=1006
} CLGenDialogControls;

typedef enum LegoRRDialogControls { // [Gods98init/resource.rc|enum:0x4|type:int|tags:RESOURCE]
	LEGORR_ID_CANCEL=2,
	LEGORR_ID_DEVICE_LISTBOX=1002,
	LEGORR_ID_DRIVER_LISTBOX=1000,
	LEGORR_ID_FULLSCREEN_RADIOBUTTON=1004,
	LEGORR_ID_OK=1,
	LEGORR_ID_SCREENMODES_LABEL=1006,
	LEGORR_ID_SCREENMODES_LISTBOX=1003,
	LEGORR_ID_WINDOW_RADIOBUTTON=1005
} LegoRRDialogControls;

typedef enum RockFallType { // [LegoRR/Effects.c|enum:0x4|type:int]
	ROCKFALL_3SIDES=0,
	ROCKFALL_OUTSIDECORNER=1,
	ROCKFALL_VTUNNEL=2
} RockFallType;

typedef enum MiscEffectType { // [LegoRR/Effects.c|enum:0x4|type:int] Need a better name for this.
	MISCOBJECT_BIRDSCARER=8,
	MISCOBJECT_FREEZERHIT=2,
	MISCOBJECT_LAVAEROSIONSMOKE1=4,
	MISCOBJECT_LAVAEROSIONSMOKE2=5,
	MISCOBJECT_LAVAEROSIONSMOKE3=6,
	MISCOBJECT_LAVAEROSIONSMOKE4=7,
	MISCOBJECT_LAZERHIT=0,
	MISCOBJECT_PATHDUST=3,
	MISCOBJECT_PUSHERHIT=1,
	MISCOBJECT_UPGRADEEFFECT=9
} MiscEffectType;

typedef enum Menu_ScreenType { // [LegoRR/FrontEnd.c|enum:0x4|type:uint] Types of menus only shown out-of-game. (Load is purely speculataion)
	Menu_Screen_Count=5,
	Menu_Screen_Load_unused=3,
	Menu_Screen_Missions=1,
	Menu_Screen_Save=4,
	Menu_Screen_Title=0,
	Menu_Screen_Training=2
} Menu_ScreenType;

typedef enum WallHighlightType8 { // [LegoRR/Lego.c|enum:0x1|type:byte] Byte-sized WallHighlightType (white, gray, red, green, blue, dark-yellow)
	WALLHIGHLIGHT8_DIG=1,
	WALLHIGHLIGHT8_DYNAMITE=2,
	WALLHIGHLIGHT8_NONE=0,
	WALLHIGHLIGHT8_REINFORCE=3,
	WALLHIGHLIGHT8_SELECTED=4,
	WALLHIGHLIGHT8_TUTORIAL=5
} WallHighlightType8;

typedef enum PointerSFX_Type { // [LegoRR/Lego.c|enum:0x4|type:uint] Argument for Lego_SetPointerSFX (FUN_00428730)
	PointerSFX_NotOkay=1,
	PointerSFX_NotOkay_ImmovableRock=2,
	PointerSFX_Okay=0,
	PointerSFX_Okay_Floor=5,
	PointerSFX_Okay_TopPriority=3,
	PointerSFX_Okay_Wall=4
} PointerSFX_Type;

typedef enum BlockOrientation { // [LegoRR/dummy.c|enum:0x1|type:byte|tags:UNFINISHED]
	BLOCKORIENTATION_CORNER=2,
	BLOCKORIENTATION_OBTUSE=3
} BlockOrientation;

typedef enum PanelButtonRadar { // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
	PanelButton_Radar_Count=5,
	PanelButton_Radar_MapView=4,
	PanelButton_Radar_TaggedObjectView=1,
	PanelButton_Radar_Toggle=0,
	PanelButton_Radar_ZoomIn=2,
	PanelButton_Radar_ZoomOut=3
} PanelButtonRadar;

typedef enum PanelButtonInformation { // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
	PanelButton_Information_Count=2,
	PanelButton_Information_Function=1,
	PanelButton_Information_Toggle=0
} PanelButtonInformation;

typedef enum PanelButtonCameraControl { // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
	PanelButton_CameraControl_Count=4,
	PanelButton_CameraControl_CycleBuildings=2,
	PanelButton_CameraControl_Rotate=3,
	PanelButton_CameraControl_ZoomIn=0,
	PanelButton_CameraControl_ZoomOut=1
} PanelButtonCameraControl;

typedef enum PanelButton_Type { // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
	PanelButton_CameraControl_Count=4,
	PanelButton_CameraControl_CycleBuildings=2,
	PanelButton_CameraControl_Rotate=3,
	PanelButton_CameraControl_ZoomIn=0,
	PanelButton_CameraControl_ZoomOut=1,
	PanelButton_CrystalSideBar_Count=2,
	PanelButton_CrystalSideBar_Crystals=1,
	PanelButton_CrystalSideBar_Ore=0,
	PanelButton_Encyclopedia_Close=0,
	PanelButton_Encyclopedia_Count=1,
	PanelButton_InfoDock_Close=1,
	PanelButton_InfoDock_Count=2,
	PanelButton_InfoDock_Goto=0,
	PanelButton_Information_Count=2,
	PanelButton_Information_Function=1,
	PanelButton_Information_Toggle=0,
	PanelButton_PriorityList_Close=17,
	PanelButton_PriorityList_Count=19,
	PanelButton_PriorityList_Disable1=0,
	PanelButton_PriorityList_Disable2=1,
	PanelButton_PriorityList_Disable3=2,
	PanelButton_PriorityList_Disable4=3,
	PanelButton_PriorityList_Disable5=4,
	PanelButton_PriorityList_Disable6=5,
	PanelButton_PriorityList_Disable7=6,
	PanelButton_PriorityList_Disable8=7,
	PanelButton_PriorityList_Disable9=8,
	PanelButton_PriorityList_Reset=18,
	PanelButton_PriorityList_UpOne1=9,
	PanelButton_PriorityList_UpOne2=10,
	PanelButton_PriorityList_UpOne3=11,
	PanelButton_PriorityList_UpOne4=12,
	PanelButton_PriorityList_UpOne5=13,
	PanelButton_PriorityList_UpOne6=14,
	PanelButton_PriorityList_UpOne7=15,
	PanelButton_PriorityList_UpOne8=16,
	PanelButton_Radar_Count=5,
	PanelButton_Radar_MapView=4,
	PanelButton_Radar_TaggedObjectView=1,
	PanelButton_Radar_Toggle=0,
	PanelButton_Radar_ZoomIn=2,
	PanelButton_Radar_ZoomOut=3,
	PanelButton_TopPanel_CallToArms=2,
	PanelButton_TopPanel_Count=3,
	PanelButton_TopPanel_Options=0,
	PanelButton_TopPanel_Priorities=1,
	PanelButton_Type_Count=24
} PanelButton_Type;

typedef enum PanelButtonInfoDock { // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
	PanelButton_InfoDock_Close=1,
	PanelButton_InfoDock_Count=2,
	PanelButton_InfoDock_Goto=0
} PanelButtonInfoDock;

typedef enum PanelButtonPriorityList { // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
	PanelButton_PriorityList_Close=17,
	PanelButton_PriorityList_Count=19,
	PanelButton_PriorityList_Disable1=0,
	PanelButton_PriorityList_Disable2=1,
	PanelButton_PriorityList_Disable3=2,
	PanelButton_PriorityList_Disable4=3,
	PanelButton_PriorityList_Disable5=4,
	PanelButton_PriorityList_Disable6=5,
	PanelButton_PriorityList_Disable7=6,
	PanelButton_PriorityList_Disable8=7,
	PanelButton_PriorityList_Disable9=8,
	PanelButton_PriorityList_Reset=18,
	PanelButton_PriorityList_UpOne1=9,
	PanelButton_PriorityList_UpOne2=10,
	PanelButton_PriorityList_UpOne3=11,
	PanelButton_PriorityList_UpOne4=12,
	PanelButton_PriorityList_UpOne5=13,
	PanelButton_PriorityList_UpOne6=14,
	PanelButton_PriorityList_UpOne7=15,
	PanelButton_PriorityList_UpOne8=16
} PanelButtonPriorityList;

typedef enum PanelButtonEncyclopedia { // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
	PanelButton_Encyclopedia_Close=0,
	PanelButton_Encyclopedia_Count=1
} PanelButtonEncyclopedia;

typedef enum PanelButtonCrystalSideBar { // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
	PanelButton_CrystalSideBar_Count=2,
	PanelButton_CrystalSideBar_Crystals=1,
	PanelButton_CrystalSideBar_Ore=0
} PanelButtonCrystalSideBar;

typedef enum PanelButtonTopPanel { // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
	PanelButton_TopPanel_CallToArms=2,
	PanelButton_TopPanel_Count=3,
	PanelButton_TopPanel_Options=0,
	PanelButton_TopPanel_Priorities=1
} PanelButtonTopPanel;

typedef enum Lego_SurfaceType { // [LegoRR/Lego.c|enum:0x4|type:int|tags:BIGENUMALIAS] See TerrainType for byte-sized enum version.
	Lego_SurfaceType_Cavern=17,
	Lego_SurfaceType_Count=18,
	Lego_SurfaceType_CrystalSeam=10,
	Lego_SurfaceType_Hard=2,
	Lego_SurfaceType_Immovable=1,
	Lego_SurfaceType_Lake=9,
	Lego_SurfaceType_Lava=6,
	Lego_SurfaceType_Loose=4,
	Lego_SurfaceType_Medium=3,
	Lego_SurfaceType_OreSeam=8,
	Lego_SurfaceType_Path=14,
	Lego_SurfaceType_RechargeSeam=11,
	Lego_SurfaceType_Reinforcement=13,
	Lego_SurfaceType_Rubble=12,
	Lego_SurfaceType_SlugHole=15,
	Lego_SurfaceType_Soil=5,
	Lego_SurfaceType_Tunnel=0,
	Lego_SurfaceType_Undiscovered=16,
	Lego_SurfaceType_Water=7
} Lego_SurfaceType;

typedef enum Lego_FallInType { // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE]
	Lego_FallInType_Danger_High=7,
	Lego_FallInType_Danger_Low=5,
	Lego_FallInType_Danger_Medium=6,
	Lego_FallInType_Danger_VeryHigh=8,
	Lego_FallInType_None=0,
	Lego_FallInType_Normal_High=3,
	Lego_FallInType_Normal_Low=1,
	Lego_FallInType_Normal_Medium=2,
	Lego_FallInType_Normal_VeryHigh=4
} Lego_FallInType;

typedef enum Lego_PathType { // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE]
	Lego_PathType_None=0,
	Lego_PathType_Path=2,
	Lego_PathType_Rubble=1
} Lego_PathType;

typedef enum Bubble_Type { // [LegoRR/Bubble.c|enum:0x4|type:int]
	Bubble_BuildPath=35,
	Bubble_CallToArms=30,
	Bubble_CantDo=0,
	Bubble_CarryBarrier=20,
	Bubble_CarryCrystal=16,
	Bubble_CarryDynamite=19,
	Bubble_CarryElecFence=21,
	Bubble_CarryOre=17,
	Bubble_CarryStud=18,
	Bubble_CollectBarrier=6,
	Bubble_CollectBirdScarer=15,
	Bubble_CollectCrystal=2,
	Bubble_CollectDrill=8,
	Bubble_CollectDynamite=5,
	Bubble_CollectElecFence=7,
	Bubble_CollectFreezer=14,
	Bubble_CollectHammer=10,
	Bubble_CollectLaser=12,
	Bubble_CollectOre=3,
	Bubble_CollectPusher=13,
	Bubble_CollectSpade=9,
	Bubble_CollectSpanner=11,
	Bubble_CollectStud=4,
	Bubble_Dig=27,
	Bubble_Drill=25,
	Bubble_Drive=33,
	Bubble_Dynamite=23,
	Bubble_Eat=32,
	Bubble_ElecFence=31,
	Bubble_Flee=28,
	Bubble_Goto=22,
	Bubble_Idle=1,
	Bubble_PowerOff=29,
	Bubble_Recharge=37,
	Bubble_Reinforce=24,
	Bubble_Repair=26,
	Bubble_Request=38,
	Bubble_Train=36,
	Bubble_Type_Count=39,
	Bubble_Upgrade=34
} Bubble_Type;

typedef struct SearchAddCryOre_c SearchAddCryOre_c, *PSearchAddCryOre_c;

struct SearchAddCryOre_c { // [LegoRR/search.c|struct:0xc]
	undefined4 field_0;
	uint crystalCount;
	uint oreCount; // normal ore
};

typedef struct SearchLevelSelectInfo_14 SearchLevelSelectInfo_14, *PSearchLevelSelectInfo_14;

struct SearchLevelSelectInfo_14 { // [LegoRR/search.c|struct:0x14]
	struct SaveReward * saveReward; // (optional)
	struct LevelSet * levelSet;
	struct MenuItem_SelectData * selectData;
	uint index;
	BOOL keepLocked; // (check whether complete or unlocked???)
};

typedef struct SearchRadarObjectInArea SearchRadarObjectInArea, *PSearchRadarObjectInArea;

struct SearchRadarObjectInArea { // [LegoRR/search.c|struct:0x10]
	struct LegoObject * object;
	struct Point2F worldPos;
	float radius; // BlockSize -or- (BlockSize / 6.0)
};

typedef struct SearchNERPsTutorialAction SearchNERPsTutorialAction, *PSearchNERPsTutorialAction;

typedef enum NERPsTutorialAction { // [LegoRR/NERPs.c|enum:0x4|type:uint]
	NERPS_TUTORIAL_GETBLOCKISGROUND=1,
	NERPS_TUTORIAL_GETBLOCKISPATH=3,
	NERPS_TUTORIAL_GETCAMERAATTUTORIAL=6,
	NERPS_TUTORIAL_GETMONSTERATTUTORIAL=13,
	NERPS_TUTORIAL_GETUNITATBLOCK=10,
	NERPS_TUTORIAL_MAKESOMEONEPICKUP=12,
	NERPS_TUTORIAL_NONE=0,
	NERPS_TUTORIAL_SETBLOCKISGROUND=2,
	NERPS_TUTORIAL_SETBLOCKISPATH=4,
	NERPS_TUTORIAL_SETCAMERAGOTOTUTORIAL=5,
	NERPS_TUTORIAL_SETCONGREGATIONATTUTORIAL_START=8,
	NERPS_TUTORIAL_SETCONGREGATIONATTUTORIAL_STOP=9,
	NERPS_TUTORIAL_SETROCKMONSTERATTUTORIAL=7,
	NERPS_TUTORIAL_SETTUTORIALPOINTER_UNK=11
} NERPsTutorialAction;

struct SearchNERPsTutorialAction { // [LegoRR/search.c|struct:0x2c]
	enum NERPsTutorialAction action;
	int blockPointerIdx;
	int result;
	undefined field_0xc;
	undefined field_0xd;
	undefined field_0xe;
	undefined field_0xf;
	undefined field_0x10;
	undefined field_0x11;
	undefined field_0x12;
	undefined field_0x13;
	struct Point2I blockPos;
	undefined4 fieldBool_1c;
	undefined4 fieldBool_20;
	struct LegoObject * object_24;
	int int_28;
};

typedef struct SearchCollision_14 SearchCollision_14, *PSearchCollision_14;

struct SearchCollision_14 { // [LegoRR/search.c|struct:0x14] LiveObject_DoCollisionCallbacks_FUN_00446030
	struct LegoObject * targetObj;
	struct Point2F * pointf_4;
	float float_8;
	struct LegoObject * result;
	BOOL bool_10;
};

typedef struct SearchLevelLinkFindIndex_10 SearchLevelLinkFindIndex_10, *PSearchLevelLinkFindIndex_10;

struct SearchLevelLinkFindIndex_10 { // [LegoRR/search.c|struct:0x10]
	struct LevelLink * resultLink; // Output level link identifier (not modified on failure)
	int searchIndex; // Link index to search for
	int currentIndex; // Current index in linked list.
	int resultIndex; // Link index of found result, should end up equal to searchIndex, or 0 on failure.
};

typedef struct SearchLevelSelectAdd SearchLevelSelectAdd, *PSearchLevelSelectAdd;

struct SearchLevelSelectAdd { // [LegoRR/search.c|struct:0x10]
	struct LevelSet * levelSet;
	struct Menu * menu_4; // in_submenu (param_4)
	struct MenuItem_SelectData * itemData; // (init: 0)
	struct SaveData * currSave; // param_5
};

typedef struct SearchNERPsCountRecordObjects SearchNERPsCountRecordObjects, *PSearchNERPsCountRecordObjects;

struct SearchNERPsCountRecordObjects { // [LegoRR/search.c|struct:0x8]
	uint count;
	struct LegoObject * liveObj;
};

typedef struct SearchViewportWindow_14 SearchViewportWindow_14, *PSearchViewportWindow_14;

struct SearchViewportWindow_14 { // [LegoRR/search.c|struct:0x14]
	struct Viewport * view;
	struct Point2F dragStart;
	struct Point2F dragEnd;
};

typedef struct SearchSetObjectsLevel_8c SearchSetObjectsLevel_8c, *PSearchSetObjectsLevel_8c;

typedef enum LegoObject_IDs { // [LegoRR/dummy.c|enum:0x4|type:int|tags:HELPER]
	LegoObject_ID_Ore=0,
	LegoObject_ID_Ore_Count=2,
	LegoObject_ID_ProcessedOre=1
} LegoObject_IDs;

struct SearchSetObjectsLevel_8c { // [LegoRR/search.c|struct:0x8c]
	char objName[128];
	uint objLevel;
	enum LegoObject_Type objType;
	enum LegoObject_IDs objID;
};

typedef struct SearchObjectBlockXY_c SearchObjectBlockXY_c, *PSearchObjectBlockXY_c;

struct SearchObjectBlockXY_c { // [LegoRR/search.c|struct:0xc]
	struct LegoObject * resultObj;
	int bx;
	int by;
};

typedef struct SearchObjectMouseXY_c SearchObjectMouseXY_c, *PSearchObjectMouseXY_c;

struct SearchObjectMouseXY_c { // [LegoRR/search.c|struct:0xc]
	struct LegoObject * * refObj;
	float mouseX;
	float mouseY;
};

typedef struct SearchDynamiteRadius SearchDynamiteRadius, *PSearchDynamiteRadius;

struct SearchDynamiteRadius { // [LegoRR/search.c|struct:0x18] Used for both dynamite and birdScarer
	struct LegoObject * liveObj;
	struct Point2F worldPos;
	float radius;
	float maxDamage; // (dynamite only)
	float wakeRadius; // (dynamite only)
};

typedef struct SearchNERPsSetObjectHealthPain SearchNERPsSetObjectHealthPain, *PSearchNERPsSetObjectHealthPain;

struct SearchNERPsSetObjectHealthPain { // [LegoRR/search.c|struct:0xc]
	uint type; // (0 = runningAway, 1 = painThreshold, 2 = Health)
	uint runningAwayCount; // Only for healthType 0 (incremented)
	float painHealthValue; // Only for healthTypes 1,2 (assigns)
};

typedef struct SearchObjectTypeCount_c SearchObjectTypeCount_c, *PSearchObjectTypeCount_c;

struct SearchObjectTypeCount_c { // [LegoRR/search.c|struct:0xc]
	enum LegoObject_Type objType;
	int objIndex;
	uint count;
};

typedef struct SearchWeapons18_2 SearchWeapons18_2, *PSearchWeapons18_2;

struct SearchWeapons18_2 { // [LegoRR/search.c|struct:0x18]
	struct LegoObject * foundObject;
	float ref_float_4;
	struct Vector3F * fromPos;
	struct Vector3F * fromToDistance;
	BOOL success;
	struct LegoObject * ignoreObject;
};

typedef struct SearchNERPsSetMonsterAttack SearchNERPsSetMonsterAttack, *PSearchNERPsSetMonsterAttack;

struct SearchNERPsSetMonsterAttack { // [LegoRR/search.c|struct:0xc]
	uint sflags2Exclude; // (type: StatsFlags2) Fails the search if the target object has any of these flags (and is not 0xffffffff).
	uint sflags2Include; // (type: StatsFlags2) Fails the search if the target object has none of these flags (and is not 0xffffffff).
	BOOL stopAttacking; // EXACT BOOL (0 = start attacking, 1 = stop attacking)
};

typedef struct SearchInfoObject_8 SearchInfoObject_8, *PSearchInfoObject_8;

struct SearchInfoObject_8 { // [LegoRR/search.c|struct:0x8]
	struct LegoObject * object;
	uint index;
};

typedef struct SearchInfoObjectBlockPos_8 SearchInfoObjectBlockPos_8, *PSearchInfoObjectBlockPos_8;

struct SearchInfoObjectBlockPos_8 { // [LegoRR/search.c|struct:0x8]
	struct LegoObject * optObject;
	struct Point2I * optBlockPos;
};

typedef struct SearchTeleporter_10 SearchTeleporter_10, *PSearchTeleporter_10;

struct SearchTeleporter_10 { // [LegoRR/search.c|struct:0x10] Teleporter_Creat_FUN_0046a7d0
	enum LegoObject_Type objType;
	uint modeFlags;
	uint teleportFlags;
	struct TeleporterService * teleporter;
};

typedef struct LiveObjectInfo LiveObjectInfo, *PLiveObjectInfo;

struct LiveObjectInfo { // [LegoRR/search.c|struct:0x1c] This is some search info, that needs to be fixed up. Lot's of assumptions were made when creating this.
	struct LegoObject * liveObj;
	BOOL intbool_4;
	struct Point2F point_8;
	struct Vector3F vector_10;
};

typedef struct SearchAITaskDeselect_8 SearchAITaskDeselect_8, *PSearchAITaskDeselect_8;

struct SearchAITaskDeselect_8 { // [LegoRR/search.c|struct:0x8]
	struct Point2I * blockPos;
	BOOL digConnection; // If the task is AITask_Type_Dig, then this must match flag 0x8 (DIGCONNECTION).
};

typedef struct SearchInfoBlockPos_8 SearchInfoBlockPos_8, *PSearchInfoBlockPos_8;

struct SearchInfoBlockPos_8 { // [LegoRR/search.c|struct:0x8]
	struct Point2I * pBlockPos;
	uint index;
};

typedef struct SearchInterfaceFindObject SearchInterfaceFindObject, *PSearchInterfaceFindObject;

struct SearchInterfaceFindObject { // [LegoRR/search.c|struct:0x18]
	enum LegoObject_Type objType; // (condition: flags & 0x1)
	LegoObject_ID objID; // (condition: flags & 0x1)
	enum StatsFlags1 statsFlags1; // (condition: nonzero)
	enum StatsFlags2 statsFlags2; // (condition: nonzero)
	enum LegoObject_AbilityFlags abilityFlags; // (condition: flags & 0x2)
	uint flags; // (0x1: objType/objID, 0x2: abilityFlags)
};

typedef enum RewardUIState { // [LegoRR/Rewards.c|enum:0x4|type:uint]
	REWARDSTATE_0=0,
	REWARDSTATE_1=1,
	REWARDSTATE_2=2,
	REWARDSTATE_3=3,
	REWARDSTATE__COUNT=4
} RewardUIState;

typedef enum Reward_Type { // [LegoRR/Rewards.c|enum:0x4|type:int]
	Reward_Caverns=4,
	Reward_Constructions=3,
	Reward_Crystals=0,
	Reward_Diggable=2,
	Reward_Figures=5,
	Reward_Ore=1,
	Reward_Oxygen=7,
	Reward_RockMonsters=6,
	Reward_Score=9,
	Reward_Timer=8,
	Reward_Type_Count=10,
	Reward_Type_Invalid=4294967295
} Reward_Type;

typedef struct MapFileInfo MapFileInfo, *PMapFileInfo;

struct MapFileInfo { // [LegoRR/dummy.c|struct:0x12|pack:2]
	char Signature[4]; // "MAP "
	uint fileSize;
	struct Size2I dimensions;
	ushort blocks[1];
};

typedef struct RadarStructF_10 RadarStructF_10, *PRadarStructF_10;

struct RadarStructF_10 { // [LegoRR/RadarMap.c|struct:0x10]
	float width; // [0,1] as ratio of appWidth
	float height; // [0,1] as ratio of appHeight
	float field_8;
	float float_c; // (init: 1.0)
};

typedef enum Smoke_Type { // [LegoRR/Smoke.c|enum:0x4|type:uint]
	Smoke_Type_Attach=1,
	Smoke_Type_Dissipate=2,
	Smoke_Type_Looping=0
} Smoke_Type;

typedef enum Detail_TransformFlags { // [LegoRR/Detail.c|flags:0x1|type:byte]
	DETAIL_ROTATE_FLAG_X1_DEG90=1,
	DETAIL_ROTATE_FLAG_X1_DEGM90=2,
	DETAIL_ROTATE_FLAG_Y1_DEG90=4,
	DETAIL_ROTATE_FLAG_Y1_DEGM90=8,
	DETAIL_ROTATE_FLAG_Z1_DEG90=16,
	DETAIL_ROTATE_FLAG_Z1_DEGM90=32,
	DETAIL_TRANSFORM_FLAG_NONE=0,
	DETAIL_TRANSLATE_FLAG_Y10=64,
	DETAIL_TRANSLATE_FLAG_YM10=128
} Detail_TransformFlags;

typedef enum DirectionFlags { // [LegoRR/Lego.c|flags:0x4|type:uint]
	DIRECTION_FLAG_E=2,
	DIRECTION_FLAG_EW=10,
	DIRECTION_FLAG_N=1,
	DIRECTION_FLAG_NE=3,
	DIRECTION_FLAG_NEW=11,
	DIRECTION_FLAG_NONE=0,
	DIRECTION_FLAG_NS=5,
	DIRECTION_FLAG_NSE=7,
	DIRECTION_FLAG_NSEW=15,
	DIRECTION_FLAG_NSW=13,
	DIRECTION_FLAG_NW=9,
	DIRECTION_FLAG_S=4,
	DIRECTION_FLAG_SE=6,
	DIRECTION_FLAG_SEW=14,
	DIRECTION_FLAG_SW=12,
	DIRECTION_FLAG_W=8
} DirectionFlags;

typedef struct ScrollInfoStruct_20 ScrollInfoStruct_20, *PScrollInfoStruct_20;

typedef struct ScrollInfoSubStruct_1c ScrollInfoSubStruct_1c, *PScrollInfoSubStruct_1c;

typedef struct ScrollInfoSubStruct_28 ScrollInfoSubStruct_28, *PScrollInfoSubStruct_28;

struct ScrollInfoStruct_20 { // [LegoRR/ScrollInfo.c|struct:0x20]
	struct Image * image;
	struct Point2F pointOrSize;
	struct ScrollInfoSubStruct_1c * ptr1c_c;
	struct ScrollInfoSubStruct_1c * ptr1c_10;
	struct ScrollInfoSubStruct_28 * substruct28;
	enum Panel_Type panelType;
	uint flags; // (1 = used, 4 = hasImage)
};

struct ScrollInfoSubStruct_28 { // [LegoRR/ScrollInfo.c|struct:0x28]
	struct Point2F point1;
	struct Point2F point2;
	undefined4 field_10;
	undefined4 field_14;
	struct Image * image;
	int intM1_1c;
	int int_20;
	BOOL bool_24;
};

struct ScrollInfoSubStruct_1c { // [LegoRR/ScrollInfo.c|struct:0x1c]
	struct Point2F point1;
	struct Point2F point2;
	struct Image * image1;
	struct Image * image2;
	uint flags;
};

typedef struct Front_Cache Front_Cache, *PFront_Cache;

struct Front_Cache { // [LegoRR/FrontEnd.c|struct:0x10] Cache for image/fonts loaded from menus
	char * path;
	struct Image * image;
	struct Font * font;
	struct Front_Cache * next;
};

typedef struct CryTuple_8 CryTuple_8, *PCryTuple_8;

struct CryTuple_8 { // [LegoRR/FrontEnd.c|struct:0x8]
	uint cryCount;
	uint unkCount;
};

typedef enum Menu_ModalType { // [LegoRR/FrontEnd.c|enum:0x4|type:uint] Types of menus only shown over-top of gameplay. (Count treated as Invalid)
	Menu_Modal_Count=2,
	Menu_Modal_Options=1,
	Menu_Modal_Paused=0
} Menu_ModalType;

typedef enum MenuItem_SelectImageType { // [LegoRR/FrontEnd.c|enum:0x4|type:uint]
	MenuItem_SelectImage_Count=3,
	MenuItem_SelectImage_Dark=1,
	MenuItem_SelectImage_Light=0,
	MenuItem_SelectImage_Locked=2
} MenuItem_SelectImageType;

typedef struct MenuItemCallbackPair MenuItemCallbackPair, *PMenuItemCallbackPair;

struct MenuItemCallbackPair { // [LegoRR/dummy.c|struct:0x8]
	void * value;
	void * callback;
};

typedef BOOL (* LevelLink_RunThroughLinksCallback)(struct LevelLink *, void *);

typedef struct IDirectDrawMediaStream IDirectDrawMediaStream, *PIDirectDrawMediaStream;

typedef struct IDirectDrawMediaStreamVtbl IDirectDrawMediaStreamVtbl, *PIDirectDrawMediaStreamVtbl;

struct IDirectDrawMediaStreamVtbl { // [DirectX/MMStream.c|struct:0x3c|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer GetMultiMediaStream; // (start of IMediaStream)
	pointer GetInformation;
	pointer SetSameFormat;
	pointer AllocateSample;
	pointer CreateSharedSample;
	pointer SendEndOfStream;
	pointer GetFormat; // (start of IDirectDrawMediaStream)
	pointer SetFormat;
	pointer GetDirectDraw;
	pointer SetDirectDraw;
	pointer CreateSample;
	pointer GetTimePerFrame;
};

struct IDirectDrawMediaStream { // [DirectX/MMStream.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirectDrawMediaStreamVtbl * lpVtbl;
};

typedef struct IDirect3D3 IDirect3D3, *PIDirect3D3;

struct IDirect3D3 { // [DirectX/D3D.c|struct:0x4|tags:DIRECTX,INTERFACE,MISSINGVFTABLE]
	undefined field_0x0;
	undefined field_0x1;
	undefined field_0x2;
	undefined field_0x3;
};

typedef struct IAMMultiMediaStream IAMMultiMediaStream, *PIAMMultiMediaStream;

typedef struct IAMMultiMediaStreamVtbl IAMMultiMediaStreamVtbl, *PIAMMultiMediaStreamVtbl;

typedef enum MMStreamType {
	STREAMTYPE_READ=0,
	STREAMTYPE_TRANSFORM=2,
	STREAMTYPE_WRITE=1
} MMStreamType;

typedef struct IMediaStream IMediaStream, *PIMediaStream;

typedef enum MMStreamState {
	STREAMSTATE_RUN=1,
	STREAMSTATE_STOP=0
} MMStreamState;

typedef struct IGraphBuilder IGraphBuilder, *PIGraphBuilder;

typedef struct IMediaStreamFilter IMediaStreamFilter, *PIMediaStreamFilter;

typedef WCHAR * LPWSTR;

typedef struct IBindCtx IBindCtx, *PIBindCtx;

typedef struct IMoniker IMoniker, *PIMoniker;

typedef struct IMediaStreamVtbl IMediaStreamVtbl, *PIMediaStreamVtbl;

typedef struct IGraphBuilderVtbl IGraphBuilderVtbl, *PIGraphBuilderVtbl;

typedef struct IMediaStreamFilterVtbl IMediaStreamFilterVtbl, *PIMediaStreamFilterVtbl;

typedef struct IPersist IPersist, *PIPersist;

typedef struct IBindCtxVtbl IBindCtxVtbl, *PIBindCtxVtbl;

typedef struct tagBIND_OPTS tagBIND_OPTS, *PtagBIND_OPTS;

typedef struct tagBIND_OPTS BIND_OPTS;

typedef struct IRunningObjectTable IRunningObjectTable, *PIRunningObjectTable;

typedef struct IEnumString IEnumString, *PIEnumString;

typedef struct IMonikerVtbl IMonikerVtbl, *PIMonikerVtbl;

typedef GUID CLSID;

typedef struct IStream IStream, *PIStream;

typedef union _ULARGE_INTEGER _ULARGE_INTEGER, *P_ULARGE_INTEGER;

typedef union _ULARGE_INTEGER ULARGE_INTEGER;

typedef struct IEnumMoniker IEnumMoniker, *PIEnumMoniker;

typedef struct IPersistVtbl IPersistVtbl, *PIPersistVtbl;

typedef struct IRunningObjectTableVtbl IRunningObjectTableVtbl, *PIRunningObjectTableVtbl;

typedef struct IEnumStringVtbl IEnumStringVtbl, *PIEnumStringVtbl;

typedef struct IStreamVtbl IStreamVtbl, *PIStreamVtbl;

typedef union _LARGE_INTEGER _LARGE_INTEGER, *P_LARGE_INTEGER;

typedef union _LARGE_INTEGER LARGE_INTEGER;

typedef struct tagSTATSTG tagSTATSTG, *PtagSTATSTG;

typedef struct tagSTATSTG STATSTG;

typedef struct _struct_22 _struct_22, *P_struct_22;

typedef struct _struct_23 _struct_23, *P_struct_23;

typedef double ULONGLONG;

typedef struct IEnumMonikerVtbl IEnumMonikerVtbl, *PIEnumMonikerVtbl;

typedef struct _struct_19 _struct_19, *P_struct_19;

typedef struct _struct_20 _struct_20, *P_struct_20;

typedef double LONGLONG;

struct IMediaStream { // [DirectX/MMStream.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IMediaStreamVtbl * lpVtbl;
};

struct IPersistVtbl {
	HRESULT (* QueryInterface)(struct IPersist *, IID *, void * *);
	ULONG (* AddRef)(struct IPersist *);
	ULONG (* Release)(struct IPersist *);
	HRESULT (* GetClassID)(struct IPersist *, CLSID *);
};

struct IStreamVtbl {
	HRESULT (* QueryInterface)(struct IStream *, IID *, void * *);
	ULONG (* AddRef)(struct IStream *);
	ULONG (* Release)(struct IStream *);
	HRESULT (* Read)(struct IStream *, void *, ULONG, ULONG *);
	HRESULT (* Write)(struct IStream *, void *, ULONG, ULONG *);
	HRESULT (* Seek)(struct IStream *, LARGE_INTEGER, DWORD, ULARGE_INTEGER *);
	HRESULT (* SetSize)(struct IStream *, ULARGE_INTEGER);
	HRESULT (* CopyTo)(struct IStream *, struct IStream *, ULARGE_INTEGER, ULARGE_INTEGER *, ULARGE_INTEGER *);
	HRESULT (* Commit)(struct IStream *, DWORD);
	HRESULT (* Revert)(struct IStream *);
	HRESULT (* LockRegion)(struct IStream *, ULARGE_INTEGER, ULARGE_INTEGER, DWORD);
	HRESULT (* UnlockRegion)(struct IStream *, ULARGE_INTEGER, ULARGE_INTEGER, DWORD);
	HRESULT (* Stat)(struct IStream *, STATSTG *, DWORD);
	HRESULT (* Clone)(struct IStream *, struct IStream * *);
};

struct IEnumStringVtbl {
	HRESULT (* QueryInterface)(struct IEnumString *, IID *, void * *);
	ULONG (* AddRef)(struct IEnumString *);
	ULONG (* Release)(struct IEnumString *);
	HRESULT (* Next)(struct IEnumString *, ULONG, LPOLESTR *, ULONG *);
	HRESULT (* Skip)(struct IEnumString *, ULONG);
	HRESULT (* Reset)(struct IEnumString *);
	HRESULT (* Clone)(struct IEnumString *, struct IEnumString * *);
};

struct _struct_20 {
	DWORD LowPart;
	LONG HighPart;
};

struct _struct_19 {
	DWORD LowPart;
	LONG HighPart;
};

union _LARGE_INTEGER {
	struct _struct_19 s;
	struct _struct_20 u;
	LONGLONG QuadPart;
};

struct IGraphBuilderVtbl { // [DirectX/MMStream.c|struct:0x48|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer AddFilter;
	pointer RemoveFilter;
	pointer EnumFilters;
	pointer FindFilterByName;
	pointer ConnectDirect;
	pointer Reconnect;
	pointer Disconnect;
	pointer SetDefaultSyncSource;
	pointer Connect;
	pointer Render;
	pointer RenderFile;
	pointer AddSourceFilter;
	pointer SetLogFile;
	pointer Abort;
	pointer ShouldOperationContinue;
};

struct IEnumString {
	struct IEnumStringVtbl * lpVtbl;
};

struct tagBIND_OPTS {
	DWORD cbStruct;
	DWORD grfFlags;
	DWORD grfMode;
	DWORD dwTickCountDeadline;
};

struct IMediaStreamFilter { // [DirectX/MMStream.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IMediaStreamFilterVtbl * lpVtbl;
};

struct IAMMultiMediaStream { // [DirectX/MMStream.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IAMMultiMediaStreamVtbl * lpVtbl;
};

struct IMediaStreamFilterVtbl { // [DirectX/MMStream.c|struct:0x60|tags:DIRECTX,VFTABLE] Subclass of IDirect3DRMArrayVtbl
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* GetClassID)(struct IPersist *, GUID *); // (start of IPersist)
	pointer Stop; // (start of IMediaFilter)
	pointer Pause;
	pointer Run;
	pointer GetState;
	pointer SetSyncSource;
	pointer GetSyncSource;
	pointer EnumPins; // (start of IBaseFilter)
	pointer FindPin;
	pointer QueryFilterInfo;
	pointer JoinFilterGraph;
	pointer QueryVendorInfo;
	pointer AddMediaStream; // (start of IMediaStreamFilter)
	pointer GetMediaStream;
	pointer EnumMediaStreams;
	pointer SupportSeeking;
	pointer ReferenceTimeToStreamTime;
	pointer GetCurrentStreamTime;
	pointer WaitUntil;
	pointer Flush;
	pointer EndOfStream;
};

struct _struct_23 {
	DWORD LowPart;
	DWORD HighPart;
};

struct IPersist {
	struct IPersistVtbl * lpVtbl;
};

struct _struct_22 {
	DWORD LowPart;
	DWORD HighPart;
};

struct IMediaStreamVtbl { // [DirectX/MMStream.c|struct:0x24|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer GetMultiMediaStream;
	pointer GetInformation;
	pointer SetSameFormat;
	pointer AllocateSample;
	pointer CreateSharedSample;
	pointer SendEndOfStream;
};

struct IAMMultiMediaStreamVtbl { // [DirectX/MMStream.c|struct:0x4c|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* GetInformation)(struct IAMMultiMediaStream *, DWORD *, enum MMStreamType *);
	HRESULT (* GetMediaStream)(struct IAMMultiMediaStream *, GUID *, struct IMediaStream * *);
	HRESULT (* EnumMediaStreams)(struct IAMMultiMediaStream *, int, struct IMediaStream * *);
	HRESULT (* GetState)(struct IAMMultiMediaStream *, enum MMStreamState *);
	HRESULT (* SetState)(struct IAMMultiMediaStream *, enum MMStreamState);
	HRESULT (* GetTime)(struct IAMMultiMediaStream *, longlong *);
	HRESULT (* GetDuration)(struct IAMMultiMediaStream *, longlong *);
	HRESULT (* Seek)(struct IAMMultiMediaStream *, longlong);
	HRESULT (* GetEndOfStreamEventHandle)(struct IAMMultiMediaStream *, HANDLE *);
	HRESULT (* Initialize)(struct IAMMultiMediaStream *, enum MMStreamType, DWORD, struct IGraphBuilder *);
	HRESULT (* GetFilterGraph)(struct IAMMultiMediaStream *, struct IGraphBuilder * *);
	HRESULT (* GetFilter)(struct IAMMultiMediaStream *, struct IMediaStreamFilter * *);
	HRESULT (* AddMediaStream)(struct IAMMultiMediaStream *, struct IUnknown *, GUID *, DWORD, struct IMediaStream * *);
	HRESULT (* OpenFile)(struct IAMMultiMediaStream *, LPWSTR, DWORD);
	HRESULT (* OpenMoniker)(struct IAMMultiMediaStream *, struct IBindCtx *, struct IMoniker *, DWORD);
	HRESULT (* Render)(struct IAMMultiMediaStream *, DWORD);
};

struct IStream {
	struct IStreamVtbl * lpVtbl;
};

struct IMoniker {
	struct IMonikerVtbl * lpVtbl;
};

struct IEnumMonikerVtbl {
	HRESULT (* QueryInterface)(struct IEnumMoniker *, IID *, void * *);
	ULONG (* AddRef)(struct IEnumMoniker *);
	ULONG (* Release)(struct IEnumMoniker *);
	HRESULT (* Next)(struct IEnumMoniker *, ULONG, struct IMoniker * *, ULONG *);
	HRESULT (* Skip)(struct IEnumMoniker *, ULONG);
	HRESULT (* Reset)(struct IEnumMoniker *);
	HRESULT (* Clone)(struct IEnumMoniker *, struct IEnumMoniker * *);
};

union _ULARGE_INTEGER {
	struct _struct_22 s;
	struct _struct_23 u;
	ULONGLONG QuadPart;
};

struct IBindCtx {
	struct IBindCtxVtbl * lpVtbl;
};

struct IBindCtxVtbl {
	HRESULT (* QueryInterface)(struct IBindCtx *, IID *, void * *);
	ULONG (* AddRef)(struct IBindCtx *);
	ULONG (* Release)(struct IBindCtx *);
	HRESULT (* RegisterObjectBound)(struct IBindCtx *, struct IUnknown *);
	HRESULT (* RevokeObjectBound)(struct IBindCtx *, struct IUnknown *);
	HRESULT (* ReleaseBoundObjects)(struct IBindCtx *);
	HRESULT (* SetBindOptions)(struct IBindCtx *, BIND_OPTS *);
	HRESULT (* GetBindOptions)(struct IBindCtx *, BIND_OPTS *);
	HRESULT (* GetRunningObjectTable)(struct IBindCtx *, struct IRunningObjectTable * *);
	HRESULT (* RegisterObjectParam)(struct IBindCtx *, LPOLESTR, struct IUnknown *);
	HRESULT (* GetObjectParam)(struct IBindCtx *, LPOLESTR, struct IUnknown * *);
	HRESULT (* EnumObjectParam)(struct IBindCtx *, struct IEnumString * *);
	HRESULT (* RevokeObjectParam)(struct IBindCtx *, LPOLESTR);
};

struct IRunningObjectTableVtbl {
	HRESULT (* QueryInterface)(struct IRunningObjectTable *, IID *, void * *);
	ULONG (* AddRef)(struct IRunningObjectTable *);
	ULONG (* Release)(struct IRunningObjectTable *);
	HRESULT (* Register)(struct IRunningObjectTable *, DWORD, struct IUnknown *, struct IMoniker *, DWORD *);
	HRESULT (* Revoke)(struct IRunningObjectTable *, DWORD);
	HRESULT (* IsRunning)(struct IRunningObjectTable *, struct IMoniker *);
	HRESULT (* GetObjectA)(struct IRunningObjectTable *, struct IMoniker *, struct IUnknown * *);
	HRESULT (* NoteChangeTime)(struct IRunningObjectTable *, DWORD, FILETIME *);
	HRESULT (* GetTimeOfLastChange)(struct IRunningObjectTable *, struct IMoniker *, FILETIME *);
	HRESULT (* EnumRunning)(struct IRunningObjectTable *, struct IEnumMoniker * *);
};

struct tagSTATSTG {
	LPOLESTR pwcsName;
	DWORD type;
	ULARGE_INTEGER cbSize;
	FILETIME mtime;
	FILETIME ctime;
	FILETIME atime;
	DWORD grfMode;
	DWORD grfLocksSupported;
	CLSID clsid;
	DWORD grfStateBits;
	DWORD reserved;
};

struct IGraphBuilder { // [DirectX/MMStream.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IGraphBuilderVtbl * lpVtbl;
};

struct IMonikerVtbl {
	HRESULT (* QueryInterface)(struct IMoniker *, IID *, void * *);
	ULONG (* AddRef)(struct IMoniker *);
	ULONG (* Release)(struct IMoniker *);
	HRESULT (* GetClassID)(struct IMoniker *, CLSID *);
	HRESULT (* IsDirty)(struct IMoniker *);
	HRESULT (* Load)(struct IMoniker *, struct IStream *);
	HRESULT (* Save)(struct IMoniker *, struct IStream *, BOOL);
	HRESULT (* GetSizeMax)(struct IMoniker *, ULARGE_INTEGER *);
	HRESULT (* BindToObject)(struct IMoniker *, struct IBindCtx *, struct IMoniker *, IID *, void * *);
	HRESULT (* BindToStorage)(struct IMoniker *, struct IBindCtx *, struct IMoniker *, IID *, void * *);
	HRESULT (* Reduce)(struct IMoniker *, struct IBindCtx *, DWORD, struct IMoniker * *, struct IMoniker * *);
	HRESULT (* ComposeWith)(struct IMoniker *, struct IMoniker *, BOOL, struct IMoniker * *);
	HRESULT (* Enum)(struct IMoniker *, BOOL, struct IEnumMoniker * *);
	HRESULT (* IsEqual)(struct IMoniker *, struct IMoniker *);
	HRESULT (* Hash)(struct IMoniker *, DWORD *);
	HRESULT (* IsRunning)(struct IMoniker *, struct IBindCtx *, struct IMoniker *, struct IMoniker *);
	HRESULT (* GetTimeOfLastChange)(struct IMoniker *, struct IBindCtx *, struct IMoniker *, FILETIME *);
	HRESULT (* Inverse)(struct IMoniker *, struct IMoniker * *);
	HRESULT (* CommonPrefixWith)(struct IMoniker *, struct IMoniker *, struct IMoniker * *);
	HRESULT (* RelativePathTo)(struct IMoniker *, struct IMoniker *, struct IMoniker * *);
	HRESULT (* GetDisplayName)(struct IMoniker *, struct IBindCtx *, struct IMoniker *, LPOLESTR *);
	HRESULT (* ParseDisplayName)(struct IMoniker *, struct IBindCtx *, struct IMoniker *, LPOLESTR, ULONG *, struct IMoniker * *);
	HRESULT (* IsSystemMoniker)(struct IMoniker *, DWORD *);
};

struct IRunningObjectTable {
	struct IRunningObjectTableVtbl * lpVtbl;
};

struct IEnumMoniker {
	struct IEnumMonikerVtbl * lpVtbl;
};

typedef struct IFilterGraph IFilterGraph, *PIFilterGraph;

typedef struct IFilterGraphVtbl IFilterGraphVtbl, *PIFilterGraphVtbl;

struct IFilterGraphVtbl { // [DirectX/MMStream.c|struct:0x2c|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer AddFilter;
	pointer RemoveFilter;
	pointer EnumFilters;
	pointer FindFilterByName;
	pointer ConnectDirect;
	pointer Reconnect;
	pointer Disconnect;
	pointer SetDefaultSyncSource;
};

struct IFilterGraph { // [DirectX/MMStream.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IFilterGraphVtbl * lpVtbl;
};

typedef struct IDirectDrawSurface3 IDirectDrawSurface3, *PIDirectDrawSurface3;

typedef struct IDirectDrawSurface3Vtbl IDirectDrawSurface3Vtbl, *PIDirectDrawSurface3Vtbl;

struct IDirectDrawSurface3 { // [DirectX/DDraw.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirectDrawSurface3Vtbl * lpVtbl;
};

struct IDirectDrawSurface3Vtbl { // [DirectX/DDraw.c|struct:0xa0|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer AddAttachedSurface; // (start of IDirectDrawSurface)
	pointer AddOverlayDirtyRect;
	pointer Blt;
	pointer BltBatch;
	pointer BltFast;
	pointer DeleteAttachedSurface;
	pointer EnumAttachedSurfaces;
	pointer EnumOverlayZOrders;
	pointer Flip;
	pointer GetAttachedSurface;
	pointer GetBltStatus;
	pointer GetCaps;
	pointer GetClipper;
	pointer GetColorKey;
	pointer GetDC;
	pointer GetFlipStatus;
	pointer GetOverlayPosition;
	pointer GetPalette;
	pointer GetPixelFormat;
	pointer GetSurfaceDesc;
	pointer Initialize;
	pointer IsLost;
	pointer Lock;
	pointer ReleaseDC;
	pointer Restore;
	pointer SetClipper;
	pointer SetColorKey;
	pointer SetOverlayPosition;
	pointer SetPalette;
	pointer Unlock;
	pointer UpdateOverlay;
	pointer UpdateOverlayDisplay;
	pointer UpdateOverlayZOrder;
	pointer GetDDInterface; // (start of IDirectDrawSurface2)
	pointer PageLock;
	pointer PageUnlock;
	pointer SetSurfaceDesc; // (start of IDirectDrawSurface3)
};

typedef struct IDirect3DTexture IDirect3DTexture, *PIDirect3DTexture;

typedef struct IDirect3DTextureVtbl IDirect3DTextureVtbl, *PIDirect3DTextureVtbl;

struct IDirect3DTexture { // [DirectX/D3D.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DTextureVtbl * lpVtbl;
};

struct IDirect3DTextureVtbl { // [DirectX/D3D.c|struct:0x20|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer Initialize;
	pointer GetHandle;
	pointer PaletteChanged;
	pointer Load;
	pointer Unload;
};

typedef struct IDirect3DRMPicked2Array IDirect3DRMPicked2Array, *PIDirect3DRMPicked2Array;

typedef struct IDirect3DRMPicked2ArrayVtbl IDirect3DRMPicked2ArrayVtbl, *PIDirect3DRMPicked2ArrayVtbl;

typedef struct D3DRMPickDesc2 D3DRMPickDesc2, *PD3DRMPickDesc2;

struct D3DRMPickDesc2 { // [DirectX/D3DRM.c|struct:0x2c|tags:DIRECTX]
	DWORD ulFaceIdx;
	enum D3DRMGroupIndex lGroupIdx;
	struct Vector3F vPosition;
	struct Point2F tuv; // Texture coordinates
	struct Vector3F dvNormal;
	DWORD dcColor;
};

struct IDirect3DRMPicked2ArrayVtbl { // [DirectX/D3DRM.c|struct:0x14|tags:DIRECTX,VFTABLE] Subclass of IDirect3DRMArrayVtbl
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	DWORD (* GetSize)(struct IDirect3DRMPicked2Array *);
	HRESULT (* GetPick)(struct IDirect3DRMPicked2Array *, DWORD, struct IDirect3DRMVisual * *, struct IDirect3DRMFrameArray * *, struct D3DRMPickDesc2 *);
};

struct IDirect3DRMPicked2Array { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMPicked2ArrayVtbl * lpVtbl;
};

typedef struct IDirect3DRMMaterial IDirect3DRMMaterial, *PIDirect3DRMMaterial;

typedef struct IDirect3DRMMaterialVtbl IDirect3DRMMaterialVtbl, *PIDirect3DRMMaterialVtbl;

struct IDirect3DRMMaterial { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMMaterialVtbl * lpVtbl;
};

struct IDirect3DRMMaterialVtbl { // [DirectX/D3DRM.c|struct:0x44|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Clone)(struct IUnknown *, struct IUnknown *, IID *, LPVOID *);
	HRESULT (* AddDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* DeleteDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* SetAppData)(struct IUnknown *, DWORD);
	DWORD (* GetAppData)(struct IUnknown *);
	HRESULT (* SetName)(struct IUnknown *, LPCSTR);
	HRESULT (* GetName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* GetClassName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* SetPower)(struct IDirect3DRMMaterial *, float);
	HRESULT (* SetSpecular)(struct IDirect3DRMMaterial *, float, float, float);
	HRESULT (* SetEmissive)(struct IDirect3DRMMaterial *, float, float, float);
	float (* GetPower)(struct IDirect3DRMMaterial *);
	HRESULT (* GetSpecular)(struct IDirect3DRMMaterial *, float *, float *, float *);
	HRESULT (* GetEmissive)(struct IDirect3DRMMaterial *, float *, float *, float *);
};

typedef struct IDirectDraw IDirectDraw, *PIDirectDraw;

typedef struct IDirectDrawVtbl IDirectDrawVtbl, *PIDirectDrawVtbl;

struct IDirectDrawVtbl { // [DirectX/DDraw.c|struct:0x5c|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer Compact; // (start of IDirectDraw)
	pointer CreateClipper;
	HRESULT (* CreatePalette)(struct IDirectDraw4 *, DWORD, struct D3DRMPaletteEntry *, struct IDirectDrawPalette * *, struct IUnknown *);
	HRESULT (* CreateSurface)(struct IDirectDraw4 *, struct DDSURFACEDESC2 *, struct IDirectDrawSurface4 * *, struct IUnknown *);
	pointer DuplicateSurface;
	HRESULT (* EnumDisplayModes)(struct IDirectDraw4 *, DWORD, struct DDSURFACEDESC2 *, LPVOID, HRESULT (* )(struct DDSURFACEDESC2 *, LPVOID));
	HRESULT (* EnumSurfaces)(struct IDirectDraw4 *, DWORD, struct DDSURFACEDESC2 *, LPVOID, HRESULT (* )(struct IDirectDrawSurface4 *, struct DDSURFACEDESC2 *, LPVOID));
	pointer FlipToGDISurface;
	pointer GetCaps;
	pointer GetDisplayMode;
	pointer GetFourCCCodes;
	pointer GetGDISurface;
	pointer GetMonitorFrequency;
	pointer GetScanLine;
	pointer GetVerticalBlankStatus;
	pointer Initialize;
	pointer RestoreDisplayMode;
	HRESULT (* SetCooperativeLevel)(struct IDirectDraw4 *, HWND, DWORD);
	HRESULT (* SetDisplayMode)(struct IDirectDraw4 *, DWORD, DWORD, DWORD, DWORD, DWORD);
	pointer WaitForVerticalBlank;
};

struct IDirectDraw { // [DirectX/DDraw.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirectDrawVtbl * lpVtbl;
};

typedef struct IGetFrame IGetFrame, *PIGetFrame;

typedef struct IGetFrameVtbl IGetFrameVtbl, *PIGetFrameVtbl;

typedef struct HDC__ HDC__, *PHDC__;

typedef struct HDC__ * HDC;

struct IGetFrameVtbl { // [DirectX/AVIFile.c|struct:0x28|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	void * (* GetFrame)(struct IGetFrame *, int); // (after this is commented out: GetFrameData)
	HRESULT (* Begin)(struct IGetFrame *, int, int, int);
	HRESULT (* End)(struct IGetFrame *);
	HRESULT (* SetFormat)(struct IGetFrame *, BITMAPINFOHEADER *, void *, int, int, int, int);
	HRESULT (* DrawFrameStart)(struct IGetFrame *); // (commented out)
	HRESULT (* DrawFrame)(struct IGetFrame *, int, HDC, int, int, int, int); // (commented out)
	HRESULT (* DrawFrameEnd)(struct IGetFrame *); // (commented out)
};

struct IGetFrame { // [DirectX/AVIFile.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IGetFrameVtbl * lpVtbl;
};

struct HDC__ {
	int unused;
};

typedef struct IDirect3DViewport3 IDirect3DViewport3, *PIDirect3DViewport3;

typedef struct IDirect3DViewport3Vtbl IDirect3DViewport3Vtbl, *PIDirect3DViewport3Vtbl;

struct IDirect3DViewport3Vtbl { // [DirectX/D3D.c|struct:0x54|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer Initialize;
	pointer GetViewport;
	pointer SetViewport;
	pointer TransformVertices;
	pointer LightElements;
	pointer SetBackground;
	pointer GetBackground;
	pointer SetBackgroundDepth;
	pointer GetBackgroundDepth;
	pointer Clear;
	pointer AddLight;
	pointer DeleteLight;
	pointer NextLight;
	pointer GetViewport2;
	pointer SetViewport2;
	pointer SetBackgroundDepth2;
	pointer GetBackgroundDepth2;
	pointer Clear2;
};

struct IDirect3DViewport3 { // [DirectX/D3D.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DViewport3Vtbl * lpVtbl;
};

typedef struct IAVIStreaming IAVIStreaming, *PIAVIStreaming;

typedef struct IAVIStreamingVtbl IAVIStreamingVtbl, *PIAVIStreamingVtbl;

struct IAVIStreamingVtbl { // [DirectX/AVIFile.c|struct:0x14|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Begin)(struct IAVIStreaming *, int, int, int);
	HRESULT (* End)(struct IAVIStreaming *);
};

struct IAVIStreaming { // [DirectX/AVIFile.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IAVIStreamingVtbl * lpVtbl;
};

typedef struct IDirect3DRMVisualArray IDirect3DRMVisualArray, *PIDirect3DRMVisualArray;

typedef struct IDirect3DRMVisualArrayVtbl IDirect3DRMVisualArrayVtbl, *PIDirect3DRMVisualArrayVtbl;

struct IDirect3DRMVisualArray { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMVisualArrayVtbl * lpVtbl;
};

struct IDirect3DRMVisualArrayVtbl { // [DirectX/D3DRM.c|struct:0x14|tags:DIRECTX,VFTABLE] Subclass of IDirect3DRMArrayVtbl
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	DWORD (* GetSize)(struct IDirect3DRMVisualArray *);
	HRESULT (* GetElement)(struct IDirect3DRMVisualArray *, DWORD, struct IDirect3DRMVisual * *);
};

typedef struct IAVIStream IAVIStream, *PIAVIStream;

typedef struct IAVIStreamVtbl IAVIStreamVtbl, *PIAVIStreamVtbl;

typedef struct AVISTREAMINFOA AVISTREAMINFOA, *PAVISTREAMINFOA;

typedef enum AVIStreamInfoFlags { // [DirectX/AVIFile.c|flags:0x4|type:uint|tags:DIRECTX] Flags for dwFlags in AVISTREAMINFO_ struct
	AVIIF_COMPUSE=268369920,
	AVIIF_FIRSTPART=32,
	AVIIF_KEYFRAME=16,
	AVIIF_LASTPART=64,
	AVIIF_LIST=1,
	AVIIF_MIDPART=96,
	AVIIF_NOTIME=256
} AVIStreamInfoFlags;

typedef enum AVIStreamInfoCaps { // [DirectX/AVIFile.c|flags:0x4|type:uint|tags:DIRECTX] Flags for unknown field in AVISTREAMINFO_ struct
	AVISTREAMINFO_DISABLED=1,
	AVISTREAMINFO_FORMATCHANGES=65536
} AVIStreamInfoCaps;

struct AVISTREAMINFOA { // [DirectX/AVIFile.c|struct:0x8c|tags:DIRECTX]
	DWORD fccType;
	DWORD fccHandler;
	enum AVIStreamInfoFlags dwFlags; // Contains AVITF_* flags
	enum AVIStreamInfoCaps dwCaps;
	WORD wPriority;
	WORD wLanguage;
	DWORD dwScale;
	DWORD dwRate; // dwRate / dwScale == samples/second
	DWORD dwStart;
	DWORD dwLength; // In units above...
	DWORD dwInitialFrames;
	DWORD dwSuggestedBufferSize;
	DWORD dwQuality;
	DWORD dwSampleSize;
	RECT rcFrame;
	DWORD dwEditCount;
	DWORD dwFormatChangeCount;
	char szName[64];
};

struct IAVIStreamVtbl { // [DirectX/AVIFile.c|struct:0x38|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Create)(struct IAVIStream *, LPARAM, LPARAM);
	HRESULT (* Info)(struct IAVIStream *, struct AVISTREAMINFOA *, int);
	int (* FindSample)(struct IAVIStream *, int, int);
	HRESULT (* ReadFormat)(struct IAVIStream *, int, void *, int *);
	HRESULT (* SetFormat)(struct IAVIStream *, int, void *, int);
	HRESULT (* Read)(struct IAVIStream *, int, int, void *, int, int *, int *);
	HRESULT (* Write)(struct IAVIStream *, int, int, void *, int, DWORD, int *, int *);
	HRESULT (* Delete)(struct IAVIStream *, int, int);
	HRESULT (* ReadData)(struct IAVIStream *, DWORD, void *, int *);
	HRESULT (* WriteData)(struct IAVIStream *, DWORD, void *, int);
	HRESULT (* SetInfo)(struct IAVIStream *, struct AVISTREAMINFOA *, int);
};

struct IAVIStream { // [DirectX/AVIFile.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IAVIStreamVtbl * lpVtbl;
};

typedef struct IDirectDrawStreamSample IDirectDrawStreamSample, *PIDirectDrawStreamSample;

typedef struct IDirectDrawStreamSampleVtbl IDirectDrawStreamSampleVtbl, *PIDirectDrawStreamSampleVtbl;

struct IDirectDrawStreamSample { // [DirectX/MMStream.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirectDrawStreamSampleVtbl * lpVtbl;
};

struct IDirectDrawStreamSampleVtbl { // [DirectX/MMStream.c|struct:0x28|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer GetMediaStream; // (start of IStreamSample)
	pointer GetSampleTimes;
	pointer SetSampleTimes;
	pointer Update;
	pointer CompletionStatus;
	pointer GetSurface; // (start of IDirectDrawStreamSample)
	pointer SetRect;
};

typedef struct IDirect3DRMViewport IDirect3DRMViewport, *PIDirect3DRMViewport;

typedef struct IDirect3DRMViewportVtbl IDirect3DRMViewportVtbl, *PIDirect3DRMViewportVtbl;

struct IDirect3DRMViewport { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMViewportVtbl * lpVtbl;
};

struct IDirect3DRMViewportVtbl { // [DirectX/D3DRM.c|struct:0x9c|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Clone)(struct IUnknown *, struct IUnknown *, IID *, LPVOID *);
	HRESULT (* AddDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* DeleteDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* SetAppData)(struct IUnknown *, DWORD);
	DWORD (* GetAppData)(struct IUnknown *);
	HRESULT (* SetName)(struct IUnknown *, LPCSTR);
	HRESULT (* GetName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* GetClassName)(struct IUnknown *, LPDWORD, LPSTR);
	pointer Init;
	pointer Clear;
	pointer Render;
	pointer SetFront;
	pointer SetBack;
	pointer SetField;
	pointer SetUniformScaling;
	pointer SetCamera;
	pointer SetProjection;
	pointer Transform;
	pointer InverseTransform;
	pointer Configure;
	pointer ForceUpdate;
	pointer SetPlane;
	pointer GetCamera;
	pointer GetDevice;
	pointer GetPlane;
	pointer Pick;
	pointer GetUniformScaling;
	pointer GetX;
	pointer GetY;
	pointer GetWidth;
	pointer GetHeight;
	pointer GetField;
	pointer GetBack;
	pointer GetFront;
	pointer GetProjection;
	pointer GetDirect3DViewport;
};

typedef struct IStreamSample IStreamSample, *PIStreamSample;

typedef struct IStreamSampleVtbl IStreamSampleVtbl, *PIStreamSampleVtbl;

struct IStreamSample { // [DirectX/MMStream.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IStreamSampleVtbl * lpVtbl;
};

struct IStreamSampleVtbl { // [DirectX/MMStream.c|struct:0x20|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer GetMediaStream;
	pointer GetSampleTimes;
	pointer SetSampleTimes;
	pointer Update;
	pointer CompletionStatus;
};

typedef struct IDirect3DRMFrame2 IDirect3DRMFrame2, *PIDirect3DRMFrame2;

typedef struct IDirect3DRMFrame2Vtbl IDirect3DRMFrame2Vtbl, *PIDirect3DRMFrame2Vtbl;

struct IDirect3DRMFrame2 { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE] Extension of IDirect3DRMFrame
	struct IDirect3DRMFrame2Vtbl * lpVtbl;
};

struct IDirect3DRMFrame2Vtbl { // [DirectX/D3DRM.c|struct:0x150|tags:DIRECTX,VFTABLE] Extension of IDirect3DRMFrameVtbl
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Clone)(struct IUnknown *, struct IUnknown *, IID *, LPVOID *);
	HRESULT (* AddDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* DeleteDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* SetAppData)(struct IUnknown *, DWORD);
	DWORD (* GetAppData)(struct IUnknown *);
	HRESULT (* SetName)(struct IUnknown *, LPCSTR);
	HRESULT (* GetName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* GetClassName)(struct IUnknown *, LPDWORD, LPSTR);
	pointer AddChild;
	pointer AddLight;
	pointer AddMoveCallback;
	pointer AddTransform;
	pointer AddTranslation;
	pointer AddScale;
	pointer AddRotation;
	pointer AddVisual;
	pointer GetChildren;
	pointer GetColor;
	pointer GetLights;
	pointer GetMaterialMode;
	pointer GetParent;
	pointer GetPosition;
	pointer GetRotation;
	pointer GetScene;
	pointer GetSortMode;
	pointer GetTexture;
	pointer GetTransform;
	pointer GetVelocity;
	pointer GetOrientation;
	pointer GetVisuals;
	pointer GetTextureTopology; // (unique to IDirect3DRMFrame)
	pointer InverseTransform;
	pointer Load;
	pointer LookAt;
	pointer Move;
	pointer DeleteChild;
	pointer DeleteLight;
	pointer DeleteMoveCallback;
	pointer DeleteVisual;
	pointer GetSceneBackground;
	pointer GetSceneBackgroundDepth;
	pointer GetSceneFogColor;
	pointer GetSceneFogEnable;
	pointer GetSceneFogMode;
	pointer GetSceneFogParams;
	pointer SetSceneBackground;
	pointer SetSceneBackgroundRGB;
	pointer SetSceneBackgroundDepth;
	pointer SetSceneBackgroundImage;
	pointer SetSceneFogEnable;
	pointer SetSceneFogColor;
	pointer SetSceneFogMode;
	pointer SetSceneFogParams;
	pointer SetColor;
	pointer SetColorRGB;
	pointer GetZbufferMode;
	pointer SetMaterialMode;
	pointer SetOrientation;
	pointer SetPosition;
	pointer SetRotation;
	pointer SetSortMode;
	pointer SetTexture;
	pointer SetTextureTopology; // (unique to IDirect3DRMFrame)
	pointer SetVelocity;
	pointer SetZbufferMode;
	pointer Transform; // (last of IDirect3DRMFrame)
	pointer AddMoveCallback2; // (unique to IDirect3DRMFrame2)
	pointer GetBox;
	pointer GetBoxEnable;
	pointer GetAxes;
	pointer GetMaterial;
	pointer GetInheritAxes;
	pointer GetHierarchyBox;
	pointer SetBox;
	pointer SetBoxEnable;
	pointer SetAxes;
	pointer SetInheritAxes;
	pointer SetMaterial;
	pointer SetQuaternion;
	pointer RayPick;
	pointer Save; // (last of IDirect3DRMFrame2)
};

typedef struct IDirectDraw2 IDirectDraw2, *PIDirectDraw2;

typedef struct IDirectDraw2Vtbl IDirectDraw2Vtbl, *PIDirectDraw2Vtbl;

struct IDirectDraw2Vtbl { // [DirectX/DDraw.c|struct:0x60|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer Compact; // (start of IDirectDraw)
	pointer CreateClipper;
	HRESULT (* CreatePalette)(struct IDirectDraw4 *, DWORD, struct D3DRMPaletteEntry *, struct IDirectDrawPalette * *, struct IUnknown *);
	HRESULT (* CreateSurface)(struct IDirectDraw4 *, struct DDSURFACEDESC2 *, struct IDirectDrawSurface4 * *, struct IUnknown *);
	pointer DuplicateSurface;
	HRESULT (* EnumDisplayModes)(struct IDirectDraw4 *, DWORD, struct DDSURFACEDESC2 *, LPVOID, HRESULT (* )(struct DDSURFACEDESC2 *, LPVOID));
	HRESULT (* EnumSurfaces)(struct IDirectDraw4 *, DWORD, struct DDSURFACEDESC2 *, LPVOID, HRESULT (* )(struct IDirectDrawSurface4 *, struct DDSURFACEDESC2 *, LPVOID));
	pointer FlipToGDISurface;
	pointer GetCaps;
	pointer GetDisplayMode;
	pointer GetFourCCCodes;
	pointer GetGDISurface;
	pointer GetMonitorFrequency;
	pointer GetScanLine;
	pointer GetVerticalBlankStatus;
	pointer Initialize;
	pointer RestoreDisplayMode;
	HRESULT (* SetCooperativeLevel)(struct IDirectDraw4 *, HWND, DWORD);
	HRESULT (* SetDisplayMode)(struct IDirectDraw4 *, DWORD, DWORD, DWORD, DWORD, DWORD);
	pointer WaitForVerticalBlank;
	pointer GetAvailableVidMem; // (start of IDirectDraw2)
};

struct IDirectDraw2 { // [DirectX/DDraw.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirectDraw2Vtbl * lpVtbl;
};

typedef struct IAVIFile IAVIFile, *PIAVIFile;

typedef struct IAVIFileVtbl IAVIFileVtbl, *PIAVIFileVtbl;

typedef struct AVIFILEINFOA AVIFILEINFOA, *PAVIFILEINFOA;

typedef enum AVIFileInfoFlags { // [DirectX/AVIFile.c|flags:0x4|type:uint|tags:DIRECTX] Flags for dwFlags in AVIFILEINFO_ struct
	AVIFILEINFO_COPYRIGHTED=131072,
	AVIFILEINFO_HASINDEX=16,
	AVIFILEINFO_ISINTERLEAVED=256,
	AVIFILEINFO_MUSTUSEINDEX=32,
	AVIFILEINFO_WASCAPTUREFILE=65536
} AVIFileInfoFlags;

typedef enum AVIFileInfoCaps { // [DirectX/AVIFile.c|flags:0x4|type:uint|tags:DIRECTX] Flags for dwCaps in AVIFILEINFO_ struct
	AVIFILECAPS_ALLKEYFRAMES=16,
	AVIFILECAPS_CANREAD=1,
	AVIFILECAPS_CANWRITE=2,
	AVIFILECAPS_NOCOMPRESSION=32
} AVIFileInfoCaps;

struct AVIFILEINFOA { // [DirectX/AVIFile.c|struct:0x6c|tags:DIRECTX]
	DWORD dwMaxBytesPerSec; // max. transfer rate
	enum AVIFileInfoFlags dwFlags; // the ever-present flags
	enum AVIFileInfoCaps dwCaps;
	DWORD dwStreams;
	DWORD dwSuggestedBufferSize;
	DWORD dwWidth;
	DWORD dwHeight;
	DWORD dwScale;
	DWORD dwRate; // dwRate / dwScale == samples/second
	DWORD dwLength;
	DWORD dwEditCount;
	char szFileType[64]; // descriptive string for file type?
};

struct IAVIFileVtbl { // [DirectX/AVIFile.c|struct:0x28|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Info)(struct IAVIFile *, struct AVIFILEINFOA *, int);
	HRESULT (* GetStream)(struct IAVIFile *, struct IAVIStream * *, DWORD, int);
	HRESULT (* CreateStream)(struct IAVIFile *, struct IAVIStream * *, struct AVIFILEINFOA *);
	HRESULT (* WriteData)(struct IAVIFile *, DWORD, void *, int);
	HRESULT (* ReadData)(struct IAVIFile *, DWORD, void *, int *);
	HRESULT (* EndRecord)(struct IAVIFile *);
	HRESULT (* DeleteStream)(struct IAVIFile *, DWORD, int);
};

struct IAVIFile { // [DirectX/AVIFile.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IAVIFileVtbl * lpVtbl;
};

typedef struct IMultiMediaStream IMultiMediaStream, *PIMultiMediaStream;

typedef struct IMultiMediaStreamVtbl IMultiMediaStreamVtbl, *PIMultiMediaStreamVtbl;

struct IMultiMediaStream { // [DirectX/MMStream.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IMultiMediaStreamVtbl * lpVtbl;
};

struct IMultiMediaStreamVtbl { // [DirectX/MMStream.c|struct:0x30|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer GetInformation;
	pointer GetMediaStream;
	pointer EnumMediaStreams;
	pointer GetState;
	pointer SetState;
	pointer GetTime;
	pointer GetDuration;
	pointer Seek;
	pointer GetEndOfStreamEventHandle;
};

typedef struct IDirect3DRMArray IDirect3DRMArray, *PIDirect3DRMArray;

typedef struct IDirect3DRMArrayVtbl IDirect3DRMArrayVtbl, *PIDirect3DRMArrayVtbl;

struct IDirect3DRMArray { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMArrayVtbl * lpVtbl;
};

struct IDirect3DRMArrayVtbl { // [DirectX/D3DRM.c|struct:0x10|tags:DIRECTX,VFTABLE] Subclass of IDirect3DRMArrayVtbl
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer GetSize;
};

typedef struct IDirect3DRMObject IDirect3DRMObject, *PIDirect3DRMObject;

typedef struct IDirect3DRMObjectVtbl IDirect3DRMObjectVtbl, *PIDirect3DRMObjectVtbl;

struct IDirect3DRMObject { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMObjectVtbl * lpVtbl;
};

struct IDirect3DRMObjectVtbl { // [DirectX/D3DRM.c|struct:0x2c|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Clone)(struct IUnknown *, struct IUnknown *, IID *, LPVOID *);
	HRESULT (* AddDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* DeleteDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* SetAppData)(struct IUnknown *, DWORD);
	DWORD (* GetAppData)(struct IUnknown *);
	HRESULT (* SetName)(struct IUnknown *, LPCSTR);
	HRESULT (* GetName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* GetClassName)(struct IUnknown *, LPDWORD, LPSTR);
};

typedef struct IDirect3DRMTexture2 IDirect3DRMTexture2, *PIDirect3DRMTexture2;

typedef struct IDirect3DRMTexture2Vtbl IDirect3DRMTexture2Vtbl, *PIDirect3DRMTexture2Vtbl;

struct IDirect3DRMTexture2 { // [DirectX/D3DRM.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DRMTexture2Vtbl * lpVtbl;
};

struct IDirect3DRMTexture2Vtbl { // [DirectX/D3DRM.c|struct:0x84|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Clone)(struct IUnknown *, struct IUnknown *, IID *, LPVOID *);
	HRESULT (* AddDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* DeleteDestroyCallback)(struct IUnknown *, void *, LPVOID);
	HRESULT (* SetAppData)(struct IUnknown *, DWORD);
	DWORD (* GetAppData)(struct IUnknown *);
	HRESULT (* SetName)(struct IUnknown *, LPCSTR);
	HRESULT (* GetName)(struct IUnknown *, LPDWORD, LPSTR);
	HRESULT (* GetClassName)(struct IUnknown *, LPDWORD, LPSTR);
	pointer InitFromFile;
	pointer InitFromSurface;
	pointer InitFromResource;
	pointer Changed;
	pointer SetColors;
	pointer SetShades;
	pointer SetDecalSize;
	pointer SetDecalOrigin;
	pointer SetDecalScale;
	pointer SetDecalTransparency;
	pointer SetDecalTransparentColor;
	pointer GetDecalSize;
	pointer GetDecalOrigin;
	D3DRMImage * (* GetImage)(struct IDirect3DRMTexture3 *);
	pointer GetShades;
	pointer GetColors;
	pointer GetDecalScale;
	pointer GetDecalTransparency;
	pointer GetDecalTransparentColor;
	pointer InitFromImage;
	pointer InitFromResource2;
	pointer GenerateMIPMap;
};

typedef struct IDirect3DMaterial2 IDirect3DMaterial2, *PIDirect3DMaterial2;

typedef struct IDirect3DMaterial2Vtbl IDirect3DMaterial2Vtbl, *PIDirect3DMaterial2Vtbl;

struct IDirect3DMaterial2 { // [DirectX/D3D.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DMaterial2Vtbl * lpVtbl;
};

struct IDirect3DMaterial2Vtbl { // [DirectX/D3D.c|struct:0x18|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer SetMaterial;
	pointer GetMaterial;
	pointer GetHandle;
};

typedef struct IDirect3DMaterial IDirect3DMaterial, *PIDirect3DMaterial;

typedef struct IDirect3DMaterialVtbl IDirect3DMaterialVtbl, *PIDirect3DMaterialVtbl;

struct IDirect3DMaterialVtbl { // [DirectX/D3D.c|struct:0x24|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer Initialize;
	pointer SetMaterial;
	pointer GetMaterial;
	pointer GetHandle;
	pointer Reserve;
	pointer Unreserve;
};

struct IDirect3DMaterial { // [DirectX/D3D.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DMaterialVtbl * lpVtbl;
};

typedef struct IDirect3DLight IDirect3DLight, *PIDirect3DLight;

typedef struct IDirect3DLightVtbl IDirect3DLightVtbl, *PIDirect3DLightVtbl;

struct IDirect3DLightVtbl { // [DirectX/D3D.c|struct:0x18|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer Initialize;
	pointer SetLight;
	pointer GetLight;
};

struct IDirect3DLight { // [DirectX/D3D.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirect3DLightVtbl * lpVtbl;
};

typedef struct IDirectDrawSurface2 IDirectDrawSurface2, *PIDirectDrawSurface2;

typedef struct IDirectDrawSurface2Vtbl IDirectDrawSurface2Vtbl, *PIDirectDrawSurface2Vtbl;

struct IDirectDrawSurface2Vtbl { // [DirectX/DDraw.c|struct:0x9c|tags:DIRECTX,VFTABLE]
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer AddAttachedSurface; // (start of IDirectDrawSurface)
	pointer AddOverlayDirtyRect;
	pointer Blt;
	pointer BltBatch;
	pointer BltFast;
	pointer DeleteAttachedSurface;
	pointer EnumAttachedSurfaces;
	pointer EnumOverlayZOrders;
	pointer Flip;
	pointer GetAttachedSurface;
	pointer GetBltStatus;
	pointer GetCaps;
	pointer GetClipper;
	pointer GetColorKey;
	pointer GetDC;
	pointer GetFlipStatus;
	pointer GetOverlayPosition;
	pointer GetPalette;
	pointer GetPixelFormat;
	pointer GetSurfaceDesc;
	pointer Initialize;
	pointer IsLost;
	pointer Lock;
	pointer ReleaseDC;
	pointer Restore;
	pointer SetClipper;
	pointer SetColorKey;
	pointer SetOverlayPosition;
	pointer SetPalette;
	pointer Unlock;
	pointer UpdateOverlay;
	pointer UpdateOverlayDisplay;
	pointer UpdateOverlayZOrder;
	pointer GetDDInterface; // (start of IDirectDrawSurface2)
	pointer PageLock;
	pointer PageUnlock;
};

struct IDirectDrawSurface2 { // [DirectX/DDraw.c|struct:0x4|tags:DIRECTX,INTERFACE]
	struct IDirectDrawSurface2Vtbl * lpVtbl;
};

typedef struct D3DRMLoadResource D3DRMLoadResource, *PD3DRMLoadResource;

typedef HINSTANCE HMODULE;

struct D3DRMLoadResource { // [DirectX/D3DRM.c|struct:0xc|tags:DIRECTX]
	HMODULE hModule;
	LPSTR lpName;
	LPSTR lpType;
};

typedef struct D3DRMRay D3DRMRay, *PD3DRMRay;

struct D3DRMRay { // [DirectX/D3DRM.c|struct:0x18|tags:DIRECTX]
	struct Vector3F dvDir;
	struct Vector3F dvPos;
};

typedef struct D3DRMAnimationScaleKey D3DRMAnimationScaleKey, *PD3DRMAnimationScaleKey;

typedef enum D3DRMAnimationKeyType { // [DirectX/D3DRM.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DRMANIMATION_POSITIONKEY=3,
	D3DRMANIMATION_ROTATEKEY=1,
	D3DRMANIMATION_SCALEKEY=2
} D3DRMAnimationKeyType;

struct D3DRMAnimationScaleKey { // [DirectX/D3DRM.c|struct:0x20|tags:DIRECTX,SUBTYPEALIAS]
	DWORD dwSize;
	enum D3DRMAnimationKeyType dwKeyType;
	float dvTime;
	DWORD dwID;
	struct Vector3F dvScaleKey;
	undefined field_0x1c;
	undefined field_0x1d;
	undefined field_0x1e;
	undefined field_0x1f;
};

typedef struct D3DDEVICEDESC_V1 D3DDEVICEDESC_V1, *PD3DDEVICEDESC_V1;

typedef struct D3DTRANSFORMCAPS D3DTRANSFORMCAPS, *PD3DTRANSFORMCAPS;

typedef struct D3DLIGHTINGCAPS D3DLIGHTINGCAPS, *PD3DLIGHTINGCAPS;

typedef struct D3DPRIMCAPS D3DPRIMCAPS, *PD3DPRIMCAPS;

struct D3DLIGHTINGCAPS { // [DirectX/D3D.c|struct:0x10|tags:DIRECTX]
	DWORD dwSize;
	DWORD dwCaps; // Lighting caps
	DWORD dwLightingModel; // Lighting model - RGB or mono
	DWORD dwNumLights; // Number of lights that can be handled
};

struct D3DPRIMCAPS { // [DirectX/D3D.c|struct:0x38|tags:DIRECTX]
	DWORD dwSize;
	DWORD dwMiscCaps; // Capability flags
	DWORD dwRasterCaps;
	DWORD dwZCmpCaps;
	DWORD dwSrcBlendCaps;
	DWORD dwDestBlendCaps;
	DWORD dwAlphaCmpCaps;
	DWORD dwShadeCaps;
	DWORD dwTextureCaps;
	DWORD dwTextureFilterCaps;
	DWORD dwTextureBlendCaps;
	DWORD dwTextureAddressCaps;
	DWORD dwStippleWidth; // maximum width and height of
	DWORD dwStippleHeight; // of supported stipple (up to 32x32)
};

struct D3DTRANSFORMCAPS { // [DirectX/D3D.c|struct:0x8|tags:DIRECTX]
	DWORD dwSize;
	DWORD dwCaps;
};

struct D3DDEVICEDESC_V1 { // [DirectX/D3D.c|struct:0xac|tags:DIRECTX]
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dcmColorModel;
	DWORD dwDevCaps;
	struct D3DTRANSFORMCAPS dtcTransformCaps;
	BOOL bClipping;
	struct D3DLIGHTINGCAPS dlcLightingCaps;
	struct D3DPRIMCAPS dpcLineCaps;
	struct D3DPRIMCAPS dpcTriCaps;
	DWORD dwDeviceRenderBitDepth;
	DWORD dwDeviceZBufferBitDepth;
	DWORD dwMaxBufferSize;
	DWORD dwMaxVertexCount;
};

typedef struct D3DRMQuaternion D3DRMQuaternion, *PD3DRMQuaternion;

struct D3DRMQuaternion { // [DirectX/D3DRM.c|struct:0x10|tags:DIRECTX]
	float s;
	struct Vector3F v;
};

typedef struct AVIFILEINFOW AVIFILEINFOW, *PAVIFILEINFOW;

struct AVIFILEINFOW { // [DirectX/AVIFile.c|struct:0xac|tags:DIRECTX]
	DWORD dwMaxBytesPerSec; // max. transfer rate
	enum AVIFileInfoFlags dwFlags; // the ever-present flags
	enum AVIFileInfoCaps dwCaps;
	DWORD dwStreams;
	DWORD dwSuggestedBufferSize;
	DWORD dwWidth;
	DWORD dwHeight;
	DWORD dwScale;
	DWORD dwRate; // dwRate / dwScale == samples/second
	DWORD dwLength;
	DWORD dwEditCount;
	wchar16 szFileType[64]; // descriptive string for file type?
};

typedef struct DSBUFFERDESC DSBUFFERDESC, *PDSBUFFERDESC;

struct DSBUFFERDESC { // [DirectX/DSound.c|struct:0x14|tags:DIRECTX]
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwBufferBytes;
	DWORD dwReserved;
	WAVEFORMATEX * lpwfxFormat;
};

typedef struct AVISTREAMINFOW AVISTREAMINFOW, *PAVISTREAMINFOW;

struct AVISTREAMINFOW { // [DirectX/AVIFile.c|struct:0xcc|tags:DIRECTX]
	DWORD fccType;
	DWORD fccHandler;
	enum AVIStreamInfoFlags dwFlags; // Contains AVITF_* flags
	enum AVIStreamInfoCaps dwCaps;
	WORD wPriority;
	WORD wLanguage;
	DWORD dwScale;
	DWORD dwRate; // dwRate / dwScale == samples/second
	DWORD dwStart;
	DWORD dwLength; // In units above...
	DWORD dwInitialFrames;
	DWORD dwSuggestedBufferSize;
	DWORD dwQuality;
	DWORD dwSampleSize;
	RECT rcFrame;
	DWORD dwEditCount;
	DWORD dwFormatChangeCount;
	wchar16 szName[64];
};

typedef struct D3DRMAnimationRotateKey D3DRMAnimationRotateKey, *PD3DRMAnimationRotateKey;

struct D3DRMAnimationRotateKey { // [DirectX/D3DRM.c|struct:0x20|tags:DIRECTX,SUBTYPEALIAS]
	DWORD dwSize;
	enum D3DRMAnimationKeyType dwKeyType;
	float dvTime;
	DWORD dwID;
	struct D3DRMQuaternion dqRotateKey;
};

typedef struct D3DRMAnimationPositionKey D3DRMAnimationPositionKey, *PD3DRMAnimationPositionKey;

struct D3DRMAnimationPositionKey { // [DirectX/D3DRM.c|struct:0x20|tags:DIRECTX,SUBTYPEALIAS]
	DWORD dwSize;
	enum D3DRMAnimationKeyType dwKeyType;
	float dvTime;
	DWORD dwID;
	struct Vector3F dvPositionKey;
	undefined field_0x1c;
	undefined field_0x1d;
	undefined field_0x1e;
	undefined field_0x1f;
};

typedef struct D3DRMLoadMemory D3DRMLoadMemory, *PD3DRMLoadMemory;

struct D3DRMLoadMemory { // [DirectX/D3DRM.c|struct:0x8|tags:DIRECTX]
	void * lpMemory;
	DWORD dwSize;
};

typedef struct D3DRMPMeshLoadStatus D3DRMPMeshLoadStatus, *PD3DRMPMeshLoadStatus;

typedef enum D3DRMMeshStatusFlags { // [DirectX/D3DRM.c|flags:0x4|type:uint|tags:DIRECTX]
	D3DRMPMESHSTATUS_BASEMESHCOMPLETE=4,
	D3DRMPMESHSTATUS_COMPLETE=8,
	D3DRMPMESHSTATUS_INTERRUPTED=2,
	D3DRMPMESHSTATUS_RENDERABLE=16,
	D3DRMPMESHSTATUS_VALID=1
} D3DRMMeshStatusFlags;

struct D3DRMPMeshLoadStatus { // [DirectX/D3DRM.c|struct:0x20|tags:DIRECTX]
	DWORD dwSize; // Size of this structure
	DWORD dwPMeshSize; // Total Size (bytes)
	DWORD dwBaseMeshSize; // Total Size of the Base Mesh
	DWORD dwBytesLoaded; // Total bytes loaded
	DWORD dwVerticesLoaded; // Number of vertices loaded
	DWORD dwFacesLoaded; // Number of faces loaded
	HRESULT dwLoadResult; // Result of the load operation
	enum D3DRMMeshStatusFlags dwFlags;
};

typedef struct DDSURFACEDESC DDSURFACEDESC, *PDDSURFACEDESC;

typedef struct DDSCAPS DDSCAPS, *PDDSCAPS;

struct DDSCAPS { // [DirectX/DDraw.c|struct:0x4|tags:DIRECTX]
	DWORD dwCaps; // capabilities of surface wanted
};

struct DDSURFACEDESC { // [DirectX/DDraw.c|struct:0x6c|tags:DIRECTX]
	DWORD dwSize; // size of the DDSURFACEDESC structure
	DWORD dwFlags; // determines what fields are valid
	DWORD dwHeight; // height of surface to be created
	DWORD dwWidth; // width of input surface
	DWORD lPitch;
	DWORD dwBackBufferCount; // number of back buffers requested
	DWORD dwMipMapCount_RefreshRate_SrcVBHandle;
	DWORD dwAlphaBitDepth; // depth of alpha buffer requested
	DWORD dwReserved; // reserved
	LPVOID lpSurface; // pointer to the associated surface memory
	struct DDCOLORKEY ddckCKDestOverlay; // color key for destination overlay use
	struct DDCOLORKEY ddckCKDestBlt; // color key for destination blt use
	struct DDCOLORKEY ddckCKSrcOverlay; // color key for source overlay use
	struct DDCOLORKEY ddckCKSrcBlt; // color key for source blt use
	struct DDPIXELFORMAT ddpfPixelFormat; // pixel format description of the surface
	struct DDSCAPS ddsCaps; // direct draw surface capabilities
};

typedef struct D3DRMAnimationKey D3DRMAnimationKey, *PD3DRMAnimationKey;

struct D3DRMAnimationKey { // [DirectX/D3DRM.c|struct:0x20|tags:DIRECTX]
	DWORD dwSize;
	enum D3DRMAnimationKeyType dwKeyType;
	float dvTime;
	DWORD dwID;
	float dvK[4];
};

typedef struct AVICOMPRESSOPTIONS AVICOMPRESSOPTIONS, *PAVICOMPRESSOPTIONS;

typedef enum AVICompressFlags { // [DirectX/AVIFile.c|flags:0x4|type:uint|tags:DIRECTX] Defines for the dwFlags field of the AVICOMPRESSOPTIONS struct
	AVICOMPRESSF_DATARATE=2,
	AVICOMPRESSF_INTERLEAVE=1,
	AVICOMPRESSF_KEYFRAMES=4,
	AVICOMPRESSF_VALID=8
} AVICompressFlags;

struct AVICOMPRESSOPTIONS { // [DirectX/AVIFile.c|struct:0x2c|tags:DIRECTX]
	DWORD fccType; // stream type, for consistency
	DWORD fccHandler; // compressor
	DWORD dwKeyFrameEvery; // keyframe rate
	DWORD dwQuality; // compress quality 0-10,000
	DWORD dwBytesPerSecond; // bytes per second
	enum AVICompressFlags dwFlags; // flags... see below
	LPVOID lpFormat; // save format
	DWORD cbFormat;
	LPVOID lpParms; // compressor options
	DWORD cbParms;
	DWORD dwInterleaveEvery; // for non-video streams only
};

typedef enum D3DRMMeshEventType { // [DirectX/D3DRM.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DRMPMESHEVENT_BASEMESH=1,
	D3DRMPMESHEVENT_COMPLETE=2
} D3DRMMeshEventType;

typedef enum D3DTextureFilter { // [DirectX/D3D.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DFILTER_INVALID_0=0,
	D3DFILTER_LINEAR=2,
	D3DFILTER_LINEARMIPLINEAR=6,
	D3DFILTER_LINEARMIPNEAREST=5,
	D3DFILTER_MIPLINEAR=4,
	D3DFILTER_MIPNEAREST=3,
	D3DFILTER_NEAREST=1
} D3DTextureFilter;

typedef enum D3DRMAnimationOptions { // [DirectX/D3DRM.c|flags:0x4|type:uint|tags:DIRECTX]
	D3DRMANIMATION_CLOSED=2,
	D3DRMANIMATION_LINEARPOSITION=4,
	D3DRMANIMATION_OPEN=1,
	D3DRMANIMATION_POSITION=32,
	D3DRMANIMATION_SCALEANDROTATION=16,
	D3DRMANIMATION_SPLINEPOSITION=8
} D3DRMAnimationOptions;

typedef enum D3DPrimitiveType { // [DirectX/D3D.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DPT_INVALID_0=0,
	D3DPT_LINELIST=2,
	D3DPT_LINESTRIP=3,
	D3DPT_POINTLIST=1,
	D3DPT_TRIANGLEFAN=6,
	D3DPT_TRIANGLELIST=4,
	D3DPT_TRIANGLESTRIP=5
} D3DPrimitiveType;

typedef enum D3DBlend { // [DirectX/D3D.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DBLEND_BOTHINVSRCALPHA=13,
	D3DBLEND_BOTHSRCALPHA=12,
	D3DBLEND_DESTALPHA=7,
	D3DBLEND_DESTCOLOR=9,
	D3DBLEND_INVALID_0=0,
	D3DBLEND_INVDESTALPHA=8,
	D3DBLEND_INVDESTCOLOR=10,
	D3DBLEND_INVSRCALPHA=6,
	D3DBLEND_INVSRCCOLOR=4,
	D3DBLEND_ONE=2,
	D3DBLEND_SRCALPHA=5,
	D3DBLEND_SRCALPHASAT=11,
	D3DBLEND_SRCCOLOR=3,
	D3DBLEND_ZERO=1
} D3DBlend;

typedef enum D3DRMXOFFormat { // [DirectX/D3DRM.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DRMXOF_BINARY=0,
	D3DRMXOF_COMPRESSED=1,
	D3DRMXOF_TEXT=2
} D3DRMXOFFormat;

typedef enum D3DRMLoadOptions { // [DirectX/D3DRM.c|flags:0x4|type:uint|tags:DIRECTX]
	D3DRMLOAD_ASYNCHRONOUS=1024,
	D3DRMLOAD_BYGUID=64,
	D3DRMLOAD_BYNAME=16,
	D3DRMLOAD_BYPOSITION=32,
	D3DRMLOAD_FIRST=128,
	D3DRMLOAD_FROMFILE=0,
	D3DRMLOAD_FROMMEMORY=2,
	D3DRMLOAD_FROMRESOURCE=1,
	D3DRMLOAD_FROMSTREAM=4,
	D3DRMLOAD_FROMURL=8,
	D3DRMLOAD_INSTANCEBYCOPYING=512,
	D3DRMLOAD_INSTANCEBYREFERENCE=256
} D3DRMLoadOptions;

typedef enum D3DTextureOp { // [DirectX/D3D.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DTOP_ADD=7,
	D3DTOP_ADDSIGNED=8,
	D3DTOP_ADDSIGNED2X=9,
	D3DTOP_ADDSMOOTH=11,
	D3DTOP_BLENDCURRENTALPHA=16,
	D3DTOP_BLENDDIFFUSEALPHA=12,
	D3DTOP_BLENDFACTORALPHA=14,
	D3DTOP_BLENDTEXTUREALPHA=13,
	D3DTOP_BLENDTEXTUREALPHAPM=15,
	D3DTOP_BUMPENVMAP=22,
	D3DTOP_BUMPENVMAPLUMINANCE=23,
	D3DTOP_DISABLE=1,
	D3DTOP_DOTPRODUCT3=24,
	D3DTOP_INVALID_0=0,
	D3DTOP_MODULATE=4,
	D3DTOP_MODULATE2X=5,
	D3DTOP_MODULATE4x=6,
	D3DTOP_MODULATEALPHA_ADDCOLOR=18,
	D3DTOP_MODULATECOLOR_ADDALPHA=19,
	D3DTOP_MODULATEINVALPHA_ADDCOLOR=20,
	D3DTOP_MODULATEINVCOLOR_ADDALPHA=21,
	D3DTOP_PREMODULATE=17,
	D3DTOP_SELECTARG1=2,
	D3DTOP_SELECTARG2=3,
	D3DTOP_SUBTRACT=10
} D3DTextureOp;

typedef enum D3DRMTextureQuality { // [DirectX/D3DRM.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DRMTEXTURE_LINEAR=1,
	D3DRMTEXTURE_LINEARMIPLINEAR=5,
	D3DRMTEXTURE_LINEARMIPNEAREST=4,
	D3DRMTEXTURE_MIPLINEAR=3,
	D3DRMTEXTURE_MIPNEAREST=2,
	D3DRMTEXTURE_NEAREST=0
} D3DRMTextureQuality;

typedef enum D3DRMTextureFlags { // [DirectX/D3DRM.c|flags:0x4|type:uint|tags:DIRECTX] Texture flags
	D3DRMTEXTURE_CHANGEDPALETTE=128,
	D3DRMTEXTURE_CHANGEDPIXELS=64,
	D3DRMTEXTURE_DOWNSAMPLEBILINEAR=8,
	D3DRMTEXTURE_DOWNSAMPLENONE=32,
	D3DRMTEXTURE_DOWNSAMPLEPOINT=4,
	D3DRMTEXTURE_DOWNSAMPLEREDUCEDEPTH=16,
	D3DRMTEXTURE_FORCERESIDENT=1,
	D3DRMTEXTURE_INVALIDATEONLY=256,
	D3DRMTEXTURE_STATIC=2
} D3DRMTextureFlags;

typedef enum D3DRMWireframeOptions { // [DirectX/D3DRM.c|flags:0x4|type:uint|tags:DIRECTX]
	D3DRMWIREFRAME_CULL=1,
	D3DRMWIREFRAME_HIDDENLINE=2
} D3DRMWireframeOptions;

typedef enum D3DRMInterpolationOptions { // [DirectX/D3DRM.c|Flags:0x4|type:uint|tags:DIRECTX]
	D3DRMINTERPOLATION_CLOSED=2,
	D3DRMINTERPOLATION_LINEAR=4,
	D3DRMINTERPOLATION_NEAREST=256,
	D3DRMINTERPOLATION_OPEN=1,
	D3DRMINTERPOLATION_SLERPNORMALS=128,
	D3DRMINTERPOLATION_SPLINE=8,
	D3DRMINTERPOLATION_VERTEXCOLOR=64
} D3DRMInterpolationOptions;

typedef enum D3DRMSaveOptions { // [DirectX/D3DRM.c|flags:0x4|type:uint|tags:DIRECTX]
	D3DRMXOFSAVE_ALL=15,
	D3DRMXOFSAVE_MATERIALS=4,
	D3DRMXOFSAVE_NORMALS=1,
	D3DRMXOFSAVE_TEMPLATES=16,
	D3DRMXOFSAVE_TEXTURECOORDINATES=2,
	D3DRMXOFSAVE_TEXTURENAMES=8,
	D3DRMXOFSAVE_TEXTURETOPOLOGY=32
} D3DRMSaveOptions;

typedef enum D3DRMUserVisualReason { // [DirectX/D3DRM.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DRMUSERVISUAL_CANSEE=0,
	D3DRMUSERVISUAL_RENDER=1
} D3DRMUserVisualReason;

typedef enum D3DRMWrapType { // [DirectX/D3DRM.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DRMWRAP_BOX=5,
	D3DRMWRAP_CHROME=3,
	D3DRMWRAP_CYLINDER=1,
	D3DRMWRAP_FLAT=0,
	D3DRMWRAP_SHEET=4,
	D3DRMWRAP_SPHERE=2
} D3DRMWrapType;

typedef enum D3DRMStateChangeFlags { // [DirectX/D3DRM.c|flags:0x4|type:uint|tags:DIRECTX]
	D3DRMSTATECHANGE_LIGHT=64,
	D3DRMSTATECHANGE_NONVOLATILE=4,
	D3DRMSTATECHANGE_RENDER=32,
	D3DRMSTATECHANGE_UPDATEONLY=1,
	D3DRMSTATECHANGE_VOLATILE=2
} D3DRMStateChangeFlags;

typedef enum D3DRMFrameTraversalOptions { // [DirectX/D3DRM.c|flags:0x4|type:uint|tags:DIRECTX] Values for flags in IDirect3DRMFrame3::SetTraversalOptions
	D3DRMFRAME_PICKENABLE=2,
	D3DRMFRAME_RENDERENABLE=1
} D3DRMFrameTraversalOptions;

typedef enum D3DShadeMode { // [DirectX/D3D.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DSHADE_FLAT=1,
	D3DSHADE_GOURAUD=2,
	D3DSHADE_INVALID_0=0,
	D3DSHADE_PHONG=3
} D3DShadeMode;

typedef enum D3DTransformStateType { // [DirectX/D3D.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DTRANSFORMSTATE_PROJECTION=3,
	D3DTRANSFORMSTATE_TEXTURE0=16,
	D3DTRANSFORMSTATE_TEXTURE1=17,
	D3DTRANSFORMSTATE_TEXTURE2=18,
	D3DTRANSFORMSTATE_TEXTURE3=19,
	D3DTRANSFORMSTATE_TEXTURE4=20,
	D3DTRANSFORMSTATE_TEXTURE5=21,
	D3DTRANSFORMSTATE_TEXTURE6=22,
	D3DTRANSFORMSTATE_TEXTURE7=23,
	D3DTRANSFORMSTATE_VIEW=2,
	D3DTRANSFORMSTATE_WORLD=1,
	D3DTRANSFORMSTATE_WORLD1=4,
	D3DTRANSFORMSTATE_WORLD2=5,
	D3DTRANSFORMSTATE_WORLD3=6
} D3DTransformStateType;

typedef enum D3DCull { // [DirectX/D3D.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DCULL_CCW=3,
	D3DCULL_CW=2,
	D3DCULL_INVALID_0=0,
	D3DCULL_NONE=1
} D3DCull;

typedef enum D3DTextureArg { // [DirectX/D3D.c|flags:0x4|type:uint|tags:DIRECTX] (unnamed)
	D3DTA_ALPHAREPLICATE=32,
	D3DTA_COMPLEMENT=16,
	D3DTA_CURRENT=1,
	D3DTA_DIFFUSE=0,
	D3DTA_SELECTMASK=15,
	D3DTA_SPECULAR=4,
	D3DTA_TEXTURE=2,
	D3DTA_TFACTOR=3
} D3DTextureArg;

typedef enum D3DRMMaterialOverride { // [DirectX/D3DRM.c|flags:0x4|type:uint|tags:DIRECTX]
	D3DRMMATERIALOVERRIDE_ALL=255,
	D3DRMMATERIALOVERRIDE_AMBIENT=4,
	D3DRMMATERIALOVERRIDE_DIFFUSE=3,
	D3DRMMATERIALOVERRIDE_DIFFUSE_ALPHAMULTIPLY=128,
	D3DRMMATERIALOVERRIDE_DIFFUSE_ALPHAONLY=1,
	D3DRMMATERIALOVERRIDE_DIFFUSE_RGBONLY=2,
	D3DRMMATERIALOVERRIDE_EMISSIVE=8,
	D3DRMMATERIALOVERRIDE_POWER=32,
	D3DRMMATERIALOVERRIDE_SPECULAR=16,
	D3DRMMATERIALOVERRIDE_TEXTURE=64
} D3DRMMaterialOverride;

typedef enum D3DRMFPTFFlags { // [DirectX/D3DRM.c|flags:0x4|type:uint|tags:DIRECTX]
	D3DRMFPTF_ALPHA=1,
	D3DRMFPTF_NOALPHA=2,
	D3DRMFPTF_NOTPALETTIZED=8,
	D3DRMFPTF_PALETTIZED=4
} D3DRMFPTFFlags;

typedef enum D3DLightStateType { // [DirectX/D3D.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DLIGHTSTATE_AMBIENT=2,
	D3DLIGHTSTATE_COLORMODEL=3,
	D3DLIGHTSTATE_FOGDENSITY=7,
	D3DLIGHTSTATE_FOGEND=6,
	D3DLIGHTSTATE_FOGMODE=4,
	D3DLIGHTSTATE_FOGSTART=5,
	D3DLIGHTSTATE_INVALID_0=0,
	D3DLIGHTSTATE_MATERIAL=1
} D3DLightStateType;

typedef enum D3DRenderStateType { // [DirectX/D3D.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DRENDERSTATE_ALPHABLENDENABLE=27,
	D3DRENDERSTATE_ALPHAFUNC=25,
	D3DRENDERSTATE_ALPHAREF=24,
	D3DRENDERSTATE_ALPHATESTENABLE=15,
	D3DRENDERSTATE_AMBIENT=139,
	D3DRENDERSTATE_AMBIENTMATERIALSOURCE=147,
	D3DRENDERSTATE_ANISOTROPY=49,
	D3DRENDERSTATE_ANTIALIAS=2,
	D3DRENDERSTATE_BORDERCOLOR=43,
	D3DRENDERSTATE_CLIPPING=136,
	D3DRENDERSTATE_CLIPPLANEENABLE=152,
	D3DRENDERSTATE_COLORKEYBLENDENABLE=144,
	D3DRENDERSTATE_COLORKEYENABLE=41,
	D3DRENDERSTATE_COLORVERTEX=141,
	D3DRENDERSTATE_CULLMODE=22,
	D3DRENDERSTATE_DESTBLEND=20,
	D3DRENDERSTATE_DIFFUSEMATERIALSOURCE=145,
	D3DRENDERSTATE_DITHERENABLE=26,
	D3DRENDERSTATE_EDGEANTIALIAS=40,
	D3DRENDERSTATE_EMISSIVEMATERIALSOURCE=148,
	D3DRENDERSTATE_EXTENTS=138,
	D3DRENDERSTATE_FILLMODE=8,
	D3DRENDERSTATE_FLUSHBATCH=50,
	D3DRENDERSTATE_FOGCOLOR=34,
	D3DRENDERSTATE_FOGDENSITY=38,
	D3DRENDERSTATE_FOGENABLE=28,
	D3DRENDERSTATE_FOGEND=37,
	D3DRENDERSTATE_FOGSTART=36,
	D3DRENDERSTATE_FOGTABLEMODE=35,
	D3DRENDERSTATE_FOGVERTEXMODE=140,
	D3DRENDERSTATE_LASTPIXEL=16,
	D3DRENDERSTATE_LIGHTING=137,
	D3DRENDERSTATE_LINEPATTERN=10,
	D3DRENDERSTATE_LOCALVIEWER=142,
	D3DRENDERSTATE_MIPMAPLODBIAS=46,
	D3DRENDERSTATE_MONOENABLE=11,
	D3DRENDERSTATE_NORMALIZENORMALS=143,
	D3DRENDERSTATE_PLANEMASK=13,
	D3DRENDERSTATE_RANGEFOGENABLE=48,
	D3DRENDERSTATE_ROP2=12,
	D3DRENDERSTATE_SHADEMODE=9,
	D3DRENDERSTATE_SPECULARENABLE=29,
	D3DRENDERSTATE_SPECULARMATERIALSOURCE=146,
	D3DRENDERSTATE_SRCBLEND=19,
	D3DRENDERSTATE_STENCILENABLE=52,
	D3DRENDERSTATE_STENCILFAIL=53,
	D3DRENDERSTATE_STENCILFUNC=56,
	D3DRENDERSTATE_STENCILMASK=58,
	D3DRENDERSTATE_STENCILPASS=55,
	D3DRENDERSTATE_STENCILREF=57,
	D3DRENDERSTATE_STENCILWRITEMASK=59,
	D3DRENDERSTATE_STENCILZFAIL=54,
	D3DRENDERSTATE_STIPPLEDALPHA=33,
	D3DRENDERSTATE_STIPPLEENABLE=39,
	D3DRENDERSTATE_STIPPLEPATTERN00=64,
	D3DRENDERSTATE_STIPPLEPATTERN01=65,
	D3DRENDERSTATE_STIPPLEPATTERN02=66,
	D3DRENDERSTATE_STIPPLEPATTERN03=67,
	D3DRENDERSTATE_STIPPLEPATTERN04=68,
	D3DRENDERSTATE_STIPPLEPATTERN05=69,
	D3DRENDERSTATE_STIPPLEPATTERN06=70,
	D3DRENDERSTATE_STIPPLEPATTERN07=71,
	D3DRENDERSTATE_STIPPLEPATTERN08=72,
	D3DRENDERSTATE_STIPPLEPATTERN09=73,
	D3DRENDERSTATE_STIPPLEPATTERN10=74,
	D3DRENDERSTATE_STIPPLEPATTERN11=75,
	D3DRENDERSTATE_STIPPLEPATTERN12=76,
	D3DRENDERSTATE_STIPPLEPATTERN13=77,
	D3DRENDERSTATE_STIPPLEPATTERN14=78,
	D3DRENDERSTATE_STIPPLEPATTERN15=79,
	D3DRENDERSTATE_STIPPLEPATTERN16=80,
	D3DRENDERSTATE_STIPPLEPATTERN17=81,
	D3DRENDERSTATE_STIPPLEPATTERN18=82,
	D3DRENDERSTATE_STIPPLEPATTERN19=83,
	D3DRENDERSTATE_STIPPLEPATTERN20=84,
	D3DRENDERSTATE_STIPPLEPATTERN21=85,
	D3DRENDERSTATE_STIPPLEPATTERN22=86,
	D3DRENDERSTATE_STIPPLEPATTERN23=87,
	D3DRENDERSTATE_STIPPLEPATTERN24=88,
	D3DRENDERSTATE_STIPPLEPATTERN25=89,
	D3DRENDERSTATE_STIPPLEPATTERN26=90,
	D3DRENDERSTATE_STIPPLEPATTERN27=91,
	D3DRENDERSTATE_STIPPLEPATTERN28=92,
	D3DRENDERSTATE_STIPPLEPATTERN29=93,
	D3DRENDERSTATE_STIPPLEPATTERN30=94,
	D3DRENDERSTATE_STIPPLEPATTERN31=95,
	D3DRENDERSTATE_SUBPIXEL=31,
	D3DRENDERSTATE_SUBPIXELX=32,
	D3DRENDERSTATE_TEXTUREADDRESS=3,
	D3DRENDERSTATE_TEXTUREADDRESSU=44,
	D3DRENDERSTATE_TEXTUREADDRESSV=45,
	D3DRENDERSTATE_TEXTUREFACTOR=60,
	D3DRENDERSTATE_TEXTUREHANDLE=1,
	D3DRENDERSTATE_TEXTUREMAG=17,
	D3DRENDERSTATE_TEXTUREMAPBLEND=21,
	D3DRENDERSTATE_TEXTUREMIN=18,
	D3DRENDERSTATE_TEXTUREPERSPECTIVE=4,
	D3DRENDERSTATE_TRANSLUCENTSORTINDEPENDENT=51,
	D3DRENDERSTATE_VERTEXBLEND=151,
	D3DRENDERSTATE_WRAP0=128,
	D3DRENDERSTATE_WRAP1=129,
	D3DRENDERSTATE_WRAP2=130,
	D3DRENDERSTATE_WRAP3=131,
	D3DRENDERSTATE_WRAP4=132,
	D3DRENDERSTATE_WRAP5=133,
	D3DRENDERSTATE_WRAP6=134,
	D3DRENDERSTATE_WRAP7=135,
	D3DRENDERSTATE_WRAPU=5,
	D3DRENDERSTATE_WRAPV=6,
	D3DRENDERSTATE_ZBIAS=47,
	D3DRENDERSTATE_ZENABLE=7,
	D3DRENDERSTATE_ZFUNC=23,
	D3DRENDERSTATE_ZVISIBLE=30,
	D3DRENDERSTATE_ZWRITEENABLE=14
} D3DRenderStateType;

typedef enum D3DRMShadowFlags { // [DirectX/D3DRM.c|flags:0x4|type:uint|tags:DIRECTX] Shadow flags
	D3DRMSHADOW_TRUEALPHA=1
} D3DRMShadowFlags;

typedef enum D3DRMColorSource { // [DirectX/D3DRM.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DRMCOLOR_FROMFACE=0,
	D3DRMCOLOR_FROMVERTEX=1
} D3DRMColorSource;

typedef enum D3DTextureStageStateType { // [DirectX/D3D.c|enum:0x4|type:uint|tags:DIRECTX]
	D3DTSS_ADDRESS=12,
	D3DTSS_ADDRESSU=13,
	D3DTSS_ADDRESSV=14,
	D3DTSS_ALPHAARG1=5,
	D3DTSS_ALPHAARG2=6,
	D3DTSS_ALPHAOP=4,
	D3DTSS_BORDERCOLOR=15,
	D3DTSS_BUMPENVLOFFSET=23,
	D3DTSS_BUMPENVLSCALE=22,
	D3DTSS_BUMPENVMAT00=7,
	D3DTSS_BUMPENVMAT01=8,
	D3DTSS_BUMPENVMAT10=9,
	D3DTSS_BUMPENVMAT11=10,
	D3DTSS_COLORARG1=2,
	D3DTSS_COLORARG2=3,
	D3DTSS_COLOROP=1,
	D3DTSS_MAGFILTER=16,
	D3DTSS_MAXANISOTROPY=21,
	D3DTSS_MAXMIPLEVEL=20,
	D3DTSS_MINFILTER=17,
	D3DTSS_MIPFILTER=18,
	D3DTSS_MIPMAPLODBIAS=19,
	D3DTSS_TCI_CAMERASPACENORMAL=65536,
	D3DTSS_TCI_CAMERASPACEPOSITION=131072,
	D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR=196608,
	D3DTSS_TCI_PASSTHRU=0,
	D3DTSS_TEXCOORDINDEX=11,
	D3DTSS_TEXTURETRANSFORMFLAGS=24
} D3DTextureStageStateType;

typedef BOOL (* NERPsBlockPointerCallback)(struct BlockPointer *, uint, uint, void *);

typedef struct NERPsFunctionSignature NERPsFunctionSignature, *PNERPsFunctionSignature;

typedef int (* NERPsFunction)(int *);

typedef enum NERPsFunctionArgs { // [LegoRR/NERPs.c|enum:0x4|type:uint]
	NERPS_ARGS_0=0,
	NERPS_ARGS_0_NORETURN=3,
	NERPS_ARGS_1=1,
	NERPS_ARGS_1_NORETURN=4,
	NERPS_ARGS_2=2,
	NERPS_ARGS_2_NORETURN=5,
	NERPS_ARGS_3_NORETURN=6,
	NERPS_END_OF_LIST=7
} NERPsFunctionArgs;

struct NERPsFunctionSignature { // [LegoRR/NERPs.c|struct:0xc]
	char * name;
	NERPsFunction function;
	enum NERPsFunctionArgs arguments;
};

typedef enum RegistryType { // [Gods98/Registry.c|enum:0x4|type:uint] Supported registry information types
	REGISTRY_DWORD_VALUE=1,
	REGISTRY_STRING_VALUE=0
} RegistryType;

typedef struct ColourRGBAI ColourRGBAI, *PColourRGBAI;

struct ColourRGBAI { // [common.c|struct:0x10]
	uint red;
	uint green;
	uint blue;
	uint alpha;
};

typedef struct ColourRGBI ColourRGBI, *PColourRGBI;

struct ColourRGBI { // [common.c|struct:0xc]
	uint red;
	uint green;
	uint blue;
};

typedef struct ColourRGBAPacked ColourRGBAPacked, *PColourRGBAPacked;

struct ColourRGBAPacked { // [common.c|struct:0x4|pack:1]
	byte red;
	byte green;
	byte blue;
	byte alpha;
};

typedef enum DrawEffect { // [Gods98/Draw.c|enum:0x4|type:uint]
	DrawEffect_HalfTrans=2,
	DrawEffect_None=0,
	DrawEffect_XOR=1
} DrawEffect;

typedef struct RNC_HeaderInfo RNC_HeaderInfo, *PRNC_HeaderInfo;

typedef enum RNCCompression { // [Gods98/Compress.c|enum:0x1|type:byte]
	RNC_COMPRESS_BEST=1,
	RNC_COMPRESS_FAST=2,
	RNC_COMPRESS_STORE=0
} RNCCompression;

struct RNC_HeaderInfo { // [Gods98/Compress.c|struct:0x13|pack:1] After this structure is the RNC data payload
	char signature[3]; // "RNC"
	enum RNCCompression compression; // (0=store, 1=best, 2=fast)
	uint beOrigSize;
	uint bePackedSize;
	ushort beOrigCRC;
	ushort bePackedCRC; // Checksum of the RNC data
	byte leeway; // Difference between compressed and uncompressed data in largest pack chunk (if larger than decompressed data)
	byte packChunks; // Amount of pack chunks
	byte data[1];
};

typedef struct RNC_Header RNC_Header, *PRNC_Header;

struct RNC_Header { // [Gods98/Compress.c|struct:0x12|pack:1] After this structure is the RNC data payload
	char signature[3]; // "RNC"
	enum RNCCompression compression; // (0=store, 1=best, 2=fast)
	uint beOrigSize;
	uint bePackedSize;
	ushort beOrigCRC;
	ushort bePackedCRC; // Checksum of the RNC data
	byte leeway; // Difference between compressed and uncompressed data in largest pack chunk (if larger than decompressed data)
	byte packChunks; // Amount of pack chunks
};

typedef enum RNCError { // [Gods98/Compress.c|enum:0x2|type:short]
	RNC_INVALIDCOMPRESSION=65534,
	RNC_INVALIDFILE=65535,
	RNC_OK=0
} RNCError;

typedef enum Image_TextureMode { // [Gods98/Images.c|enum:0x4|type:uint]
	Image_TextureMode_Additive=2,
	Image_TextureMode_Count=7,
	Image_TextureMode_Fixed_Additive=5,
	Image_TextureMode_Fixed_Subtractive=4,
	Image_TextureMode_Fixed_Transparent=6,
	Image_TextureMode_Normal=0,
	Image_TextureMode_Subtractive=1,
	Image_TextureMode_Transparent=3
} Image_TextureMode;

typedef enum FlicError { // [Gods98/Flic.c|enum:0x4|type:int]
	FLICERROR=4294967295,
	FLICFILEERROR=3005,
	FLICFILENOTFOUND=3004,
	FLICFINISHED=1,
	FLICFRAMEDOESNOTEXIST=3007,
	FLICINVALIDFILE=3003,
	FLICINVALIDHANDLE=3000,
	FLICNOERROR=0,
	FLICNOMOREFRAMES=3009,
	FLICNOMOREHANDLES=3001,
	FLICNOTENOUGHMEMORY=3002,
	FLICOFFPORTAL=3006,
	FLICREPLAYNOTSUPPORTED=3008,
	FLICSOUNDHEADERERROR=3010
} FlicError;

typedef struct Container_AppData Container_AppData, *PContainer_AppData;

typedef struct AnimClone AnimClone, *PAnimClone;

typedef struct Sound3D_SoundFrameRecord Sound3D_SoundFrameRecord, *PSound3D_SoundFrameRecord;

typedef struct Lws_Info Lws_Info, *PLws_Info;

typedef struct Lws_SoundTrigger Lws_SoundTrigger, *PLws_SoundTrigger;

typedef struct Lws_Node Lws_Node, *PLws_Node;

typedef struct Lws_KeyInfo Lws_KeyInfo, *PLws_KeyInfo;

struct Lws_KeyInfo { // [Gods98/Lws.c|struct:0x28]
	struct Vector3F position;
	struct Vector3F hpb;
	struct Vector3F scale;
	ushort frame;
	ushort padding1;
};

struct Lws_Node { // [Gods98/Lws.c|struct:0x34]
	char * name;
	ushort reference;
	ushort frameIndex;
	byte triggerIndex;
	byte padding1[3];
	struct Vector3F pivotVector;
	struct Lws_KeyInfo * keyList;
	float * dissolveLevel;
	ushort * dissolveFrame;
	ushort keyCount;
	ushort dissolveCount;
	byte flags;
	byte padding2[3];
	struct Lws_Node * childList;
	struct Lws_Node * next;
};

struct Sound3D_SoundFrameRecord { // [Gods98/3DSound.c|struct:0x14]
	struct IDirectSound3DBuffer * sound3DBuff;
	struct Vector3F pos;
	struct Sound3D_SoundFrameRecord * next;
};

struct Lws_SoundTrigger { // [Gods98/Lws.c|struct:0xd0]
	uint sfxID;
	ushort frameStartList[25];
	ushort frameEndList[25];
	uint loopUID[25];
	ushort count;
	ushort padding1;
};

struct Container_AppData { // [Gods98/Containers.c|struct:0x28]
	struct Container * ownerContainer;
	char * animSetFileName; // For the dodgy Animation Set clone stuff...
	char * frameName; // For freeing the allocation for SetName...
	uint frameCount;
	float currTime;
	float transCo; // Standard translation during amimset loop.
	char * activitySample; // Sample to play when activity is called...
	struct AnimClone * animClone;
	uint trigger;
	struct Sound3D_SoundFrameRecord * soundList; // For 'Sound3D'
};

struct AnimClone { // [Gods98/AnimClone.c|struct:0x20]
	struct AnimClone * clonedFrom;
	struct Lws_Info * scene; // LWS struct
	struct IDirect3DRMAnimationSet2 * animSet; // (not LWS)
	BOOL lws;
	struct IDirect3DRMFrame3 * root; // (not LWS)
	struct IDirect3DRMFrame3 * * partArray; // (not LWS) table of COM objects, length is count_18
	uint partCount; // (not LWS)
	uint frameCount;
};

struct Lws_Info { // [Gods98/Lws.c|struct:0x38]
	ushort firstFrame;
	ushort lastFrame;
	float fps;
	char * filePath;
	float lastTime;
	float time;
	struct IDirect3DRMFrame3 * frameList;
	struct Lws_SoundTrigger * triggerList;
	struct Lws_Node * masterNode;
	struct Lws_Node * nodeList;
	ushort nodeCount;
	ushort nodeListSize;
	ushort triggerCount;
	ushort padding1;
	struct Lws_Info * clonedFrom;
	uint referenceCount;
	byte flags;
	byte padding2[3];
};

typedef struct Container_SearchData Container_SearchData, *PContainer_SearchData;

typedef enum Container_SearchMode { // [Gods98/Containers.c|enum:0x4|type:uint]
	Container_SearchMode_FirstMatch=0,
	Container_SearchMode_MatchCount=1,
	Container_SearchMode_NthMatch=2
} Container_SearchMode;

struct Container_SearchData { // [Gods98/Containers.c|struct:0x1c|tags:SEARCH]
	char * string;
	uint stringLen;
	BOOL caseSensitive;
	struct IDirect3DRMFrame3 * resultFrame;
	uint count;
	enum Container_SearchMode mode;
	uint matchNumber;
};

typedef struct Container_TextureData Container_TextureData, *PContainer_TextureData;

struct Container_TextureData { // [Gods98/Containers.c|struct:0x8]
	char * xFileName;
	uint flags;
};

typedef enum Container_TextureFlags { // [Gods98/Containers.c|flags:0x4|type:uint]
	CONTAINER_TEXTURE_NOLOAD=1,
	CONTAINER_TEXTURE_NONE=0
} Container_TextureFlags;

typedef enum Container_MeshType { // [Gods98/Containers.c|enum:0x4|type:uint]
	Container_MeshType_Additive=4,
	Container_MeshType_Immediate=2,
	Container_MeshType_Normal=0,
	Container_MeshType_SeperateMeshes=1,
	Container_MeshType_Subtractive=5,
	Container_MeshType_Transparent=3
} Container_MeshType;

typedef enum Container_Quality { // [Gods98/Containers.c|enum:0x4|type:uint]
	Container_Quality_Flat=2,
	Container_Quality_Gouraud=3,
	Container_Quality_Phong=4,
	Container_Quality_UnlitFlat=1,
	Container_Quality_Wireframe=0
} Container_Quality;

typedef enum Container_FogMode { // [Gods98/Containers.c|enum:0x4|type:uint]
	Container_FogMode_Exponential=1,
	Container_FogMode_ExponentialSquared=2,
	Container_FogMode_Linear=3,
	Container_FogMode_None=0
} Container_FogMode;

typedef enum Container_Light { // [Gods98/Containers.c|enum:0x4|type:uint]
	Container_Light_Ambient=0,
	Container_Light_Directional=3,
	Container_Light_ParallelPoint=4,
	Container_Light_Point=1,
	Container_Light_Spot=2
} Container_Light;

typedef enum Container_Combine { // [Gods98/Containers.c|enum:0x4|type:uint]
	Container_Combine_After=2,
	Container_Combine_Before=1,
	Container_Combine_Replace=0
} Container_Combine;

typedef BOOL (* ContainerWalkTreeCallback)(struct IDirect3DRMFrame3 *, void *);

typedef struct LWSURFACE LWSURFACE, *PLWSURFACE;

typedef struct LWRGB LWRGB, *PLWRGB;

typedef enum LWTEXFLAGS { // [Gods98/Lwt.c|flags:0x4|type:uint]
	TFM_ANTIALIASING=64,
	TFM_AXIS_X=1,
	TFM_AXIS_Y=2,
	TFM_AXIS_Z=4,
	TFM_NEGATIVE_IMAGE=16,
	TFM_PIXEL_BLENDING=32,
	TFM_SEQUENCE=128,
	TFM_WORLD_COORD=8
} LWTEXFLAGS;

typedef enum LWSRFFLAGS { // [Gods98/Lwt.c|flags:0x4|type:uint]
	SFM_ADDITIVE=512,
	SFM_COLORFILTER=16,
	SFM_COLORHIGHLIGHTS=8,
	SFM_DOUBLESIDED=256,
	SFM_LUMINOUS=1,
	SFM_OPAQUEEDGE=32,
	SFM_OUTLINE=2,
	SFM_SHARPTERMINATOR=128,
	SFM_SMOOTHING=4,
	SFM_TRANSPARENTEDGE=64
} LWSRFFLAGS;

typedef enum LWTEXMAPTYPE { // [Gods98/Lwt.c|flags:0x4|type:uint]
	MT_CYLINDRICAL=1,
	MT_MAX=3,
	MT_PLANAR=0,
	MT_SPHERICAL=2
} LWTEXMAPTYPE;

typedef struct TEXDATA TEXDATA, *PTEXDATA;

struct TEXDATA { // [Gods98/Lwt.c|struct:0xc] (an alias for Vector3F)
	float tdX;
	float tdY;
	float tdZ;
};

struct LWRGB { // [Gods98/Lwt.c|struct:0x4|pack:1] (an alias for ColourRGBAPacked)
	byte colRed;
	byte colGreen;
	byte colBlue;
	byte colAlpha;
};

struct LWSURFACE { // [Gods98/Lwt.c|struct:0x54]
	char * srfName;
	struct LWSURFACE * srfNextSurf;
	char * srfPath;
	struct LWRGB srfCol;
	char srfTCLR[4];
	enum LWTEXFLAGS srfTexFlags;
	enum LWSRFFLAGS srfFlags;
	enum LWTEXMAPTYPE srfTexType;
	uint srfTexWrap;
	struct TEXDATA srfTexSize;
	struct TEXDATA srfTexCentre;
	float srfLuminous;
	float srfTransparent;
	float srfDiffuse;
	float srfReflect;
	float srfSpecular;
	float srfSpecPower;
};

typedef struct LWSURFLIST LWSURFLIST, *PLWSURFLIST;

struct LWSURFLIST { // [Gods98/Lwt.c|struct:0x8]
	uint srflCount;
	char * * srflName;
};

typedef struct LWSIZE LWSIZE, *PLWSIZE;

struct LWSIZE { // [Gods98/Lwt.c|struct:0xc]
	uint lwVertCount;
	uint lwPolyCount;
	uint lwSurfaceCount;
};

typedef struct LWPOLY LWPOLY, *PLWPOLY;

struct LWPOLY { // [Gods98/Lwt.c|struct:0xc]
	uint plyCount;
	uint plySurface;
	ushort * plyData;
};

typedef struct APPOBJ APPOBJ, *PAPPOBJ;

struct APPOBJ { // [Gods98/Lwt.c|struct:0x20] LightWave lwt APPOBJ
	char * aoPath;
	struct LWSIZE aoSize;
	float * aoVerts;
	struct LWPOLY * aoPoly;
	struct LWSURFACE * aoSurface;
	struct File * aoFileUV;
};

typedef BOOL (* AnimCloneWalkTreeCallback)(struct IDirect3DRMFrame3 *, void *);

typedef struct Box2I Box2I, *PBox2I;

struct Box2I { // [common.c|struct:0x10]
	int x1;
	int y1;
	int x2;
	int y2;
};

typedef struct Area2I Area2I, *PArea2I;

struct Area2I { // [common.c|struct:0x10] also Area2I
	int x;
	int y;
	int width;
	int height;
};

typedef struct Box2F Box2F, *PBox2F;

struct Box2F { // [common.c|struct:0x10]
	float x1;
	float y1;
	float x2;
	float y2;
};

typedef struct Rect2I Rect2I, *PRect2I;

struct Rect2I { // [common.c|struct:0x10]
	int left;
	int top;
	int right;
	int bottom;
};

typedef enum Keys32 { // [Gods98/Input.c|enum:0x4|type:int|tags:HELPER] 32-bit sized Keys enum
	KEYPAD_0=82,
	KEYPAD_1=79,
	KEYPAD_2=80,
	KEYPAD_3=81,
	KEYPAD_4=75,
	KEYPAD_5=76,
	KEYPAD_6=77,
	KEYPAD_7=71,
	KEYPAD_8=72,
	KEYPAD_9=73,
	KEYPAD_ASTERISK=55,
	KEYPAD_DELETE=83,
	KEYPAD_ENTER=156,
	KEYPAD_FORWARDFLASH=181,
	KEYPAD_MINUS=74,
	KEYPAD_NUMLOCK=69,
	KEYPAD_PLUS=78,
	KEY_A=30,
	KEY_ALT=56,
	KEY_ALTGR=184,
	KEY_AT=40,
	KEY_B=48,
	KEY_BACKSLASH=86,
	KEY_BACKSPACE=14,
	KEY_C=46,
	KEY_CAPLOCK=58,
	KEY_CURSORDOWN=208,
	KEY_CURSORLEFT=203,
	KEY_CURSORUP=200,
	KEY_D=32,
	KEY_DELETE=211,
	KEY_E=18,
	KEY_EIGHT=9,
	KEY_END=207,
	KEY_EQUALS=13,
	KEY_ESCAPE=1,
	KEY_F=33,
	KEY_F1=59,
	KEY_F10=68,
	KEY_F11=87,
	KEY_F12=88,
	KEY_F2=60,
	KEY_F3=61,
	KEY_F4=62,
	KEY_F5=63,
	KEY_F6=64,
	KEY_F7=65,
	KEY_F8=66,
	KEY_F9=67,
	KEY_FIVE=6,
	KEY_FOUR=5,
	KEY_G=34,
	KEY_H=35,
	KEY_HASH=43,
	KEY_HOME=199,
	KEY_I=23,
	KEY_INSERT=210,
	KEY_J=36,
	KEY_K=37,
	KEY_L=38,
	KEY_LEFTARROW=51,
	KEY_LEFTBRACE=26,
	KEY_LEFTCTRL=29,
	KEY_LEFTSHIFT=42,
	KEY_M=50,
	KEY_MINUS=12,
	KEY_N=49,
	KEY_NINE=10,
	KEY_O=24,
	KEY_ONE=2,
	KEY_P=25,
	KEY_PGDN=209,
	KEY_PGUP=201,
	KEY_PRINTSCREEN=183,
	KEY_Q=16,
	KEY_QUESTIONMARK=53,
	KEY_R=19,
	KEY_RETURN=28,
	KEY_RIGHTARROW=52,
	KEY_RIGHTBRACE=27,
	KEY_RIGHTCTRL=157,
	KEY_RIGHTSHIFT=54,
	KEY_RSINGLEQUOTE=41,
	KEY_S=31,
	KEY_SCROLLLOCK=70,
	KEY_SEMICOLON=39,
	KEY_SEVEN=8,
	KEY_SIX=7,
	KEY_SPACE=57,
	KEY_T=20,
	KEY_TAB=15,
	KEY_THREE=4,
	KEY_TWO=3,
	KEY_U=22,
	KEY_V=47,
	KEY_W=17,
	KEY_X=45,
	KEY_Y=21,
	KEY_Z=44,
	KEY_ZERO=11,
	KEY__NONE=0
} Keys32;

typedef struct Main_StateChangeData Mesh_TextureStateChangeData;

typedef enum Mesh_Colour { // [Gods98/Mesh.c|enum:0x4|type:uint]
	Mesh_Colour_Alpha=4,
	Mesh_Colour_Ambient=1,
	Mesh_Colour_Diffuse=0,
	Mesh_Colour_Emissive=3,
	Mesh_Colour_Power=5,
	Mesh_Colour_Specular=2
} Mesh_Colour;

typedef enum Mesh_Type { // [Gods98/Mesh.c|enum:0x4|type:uint]
	Mesh_Type_LightWaveObject=2,
	Mesh_Type_Norm=0,
	Mesh_Type_PostEffect=1
} Mesh_Type;

typedef enum Sound3DPlay { // [Gods98/3DSound.c|enum:0x4|type:uint]
	Sound3DPlay_Normal=2,
	Sound3DPlay_OnFrame=0,
	Sound3DPlay_OnPos=1
} Sound3DPlay;

typedef struct G98CSurface G98CSurface, *PG98CSurface;

typedef struct G98CSurfaceVtbl G98CSurfaceVtbl, *PG98CSurfaceVtbl;

struct G98CSurfaceVtbl { // [Gods98/Animation.c|struct:0xc|tags:VFTABLE]
	G98CSurface * (* deletor)(struct G98CSurface *, byte);
	int (* Width)(struct G98CSurface *);
	int (* Height)(struct G98CSurface *);
};

struct G98CSurface { // [Gods98/Animation.c|struct:0x98|tags:CLASS,VIRTUAL]
	struct G98CSurfaceVtbl * vftable;
	struct IDirectDrawClipper * m_clipper; // Clipper (init: 0, unused)
	bool m_surfaceLocked; // Is the surface currently locked
	byte padding1[3];
	int m_bpp; // Bits per pixel of the surface.
	struct IDirectDrawPalette * m_palette; // The Direct Draw palette
	bool m_colourKeyed; // Set to true if the surface has a transparent colour key.
	bool m_squashToEdge; // Squah the image up at the edge of the screen
	bool m_15bit; // The 16 bit mode is really fifteen bit
	bool m_surfaceInited; // Is the surface initialised
	struct IDirectDrawSurface4 * m_surf; // Direct Draw surface.
	struct DDSURFACEDESC2 m_desc; // Description of the surface
};

typedef struct G98CAnimation G98CAnimation, *PG98CAnimation;

typedef struct G98CAnimation Animation_t;

typedef struct G98CAnimationVtbl G98CAnimationVtbl, *PG98CAnimationVtbl;

struct G98CAnimationVtbl { // [Gods98/Animation.c|struct:0x4|tags:VFTABLE]
	G98CAnimation * (* deletor)(struct G98CAnimation *, byte);
};

struct G98CAnimation { // [Gods98/Animation.c|struct:0xc4|tags:CLASS,VIRTUAL]
	struct G98CAnimationVtbl * vftable;
	struct IAVIStream * m_aviStream;
	struct IGetFrame * m_decompressFn;
	struct AVISTREAMINFOA m_aviStreamInfo;
	bool m_colourKeySet; // (init: 0)
	bool m_init; // (init: 0, 1 on open / has renderer)
	ushort padding1;
	RECT m_movieRect; // (copied from streamInfo.rcFrame)
	float m_startTime; // (init: timeGetTime() * 0.001)
	float m_currTime; // (milliseconds, just like startTime)
	float m_aviTimeScale;
	uint m_currFrame; // (init: 0)
	uint m_length; // (unused)
	struct G98CSurface * m_movieSurf;
};

typedef struct G98CMovie G98CMovie, *PG98CMovie;

typedef struct G98CMovie Movie_t;

struct G98CMovie { // [Gods98Other/Movie.c|struct:0x38|tags:CLASS]
	struct IAMMultiMediaStream * m_amStream;
	HRESULT m_err;
	struct IMediaStream * m_sampleBaseStream;
	struct IDirectDrawMediaStream * m_sampleStream;
	struct IDirectDrawSurface * m_baseSurf; // base surface for IDirectDrawStreamSample* m_sample
	struct IDirectDrawSurface3 * m_surf; // DDS3 surface for IDirectDrawStreamSample* m_sample
	struct IDirectDrawStreamSample * m_sample;
	struct IDirectDrawSurface3 * m_bSurf; // render target passed in by constructor
	RECT m_movieRect; // rect for IDirectDrawStreamSample* m_sample
	char * m_filename;
	struct IDirectDraw2 * m_ddraw2;
};

typedef struct RROSFileHeader RROSFileHeader, *PRROSFileHeader;

struct RROSFileHeader { // [LegoRR/ObjectRecall.c|struct:0x8] For .osf Object Recall save files
	char signature[4];
	uint count;
};

typedef struct BasicObjectModel BasicObjectModel, *PBasicObjectModel;

struct BasicObjectModel { // [LegoRR/dummy.c|struct:0x8] This is a dummy structure that is used for CreatureData, BuildingData, and UpgradeData (for functions using these structures that have been merged together). It's highly likely this similarity is only due to linked functions performing the same behavior and being grouped together.
	LegoObject_ID objID;
	struct Container * contAct; // ACT, true
};

typedef enum Activity_Type { // [LegoRR/LegoObject.c|enum:0x4|type:int]
	Activity_BuildPath=40,
	Activity_CantDo=11,
	Activity_Carry=17,
	Activity_CarryRubble=18,
	Activity_CarryStand=22,
	Activity_CarryTurnLeft=20,
	Activity_CarryTurnRight=21,
	Activity_Clear=30,
	Activity_Closing=54,
	Activity_Collect=15,
	Activity_Crumble=77,
	Activity_Deposit=29,
	Activity_Drill=4,
	Activity_Dynamite=28,
	Activity_Eat=35,
	Activity_Emerge=12,
	Activity_Enter=13,
	Activity_EnterRein=14,
	Activity_Explode=42,
	Activity_FireLaser=44,
	Activity_FloatOff=52,
	Activity_FloatOn=51,
	Activity_FreezeMelt=47,
	Activity_FreezeStart=46,
	Activity_Freezed=45,
	Activity_Gather=16,
	Activity_GetUp=39,
	Activity_HitBack=26,
	Activity_HitFront=25,
	Activity_HitHard=27,
	Activity_HitLeft=23,
	Activity_HitRight=24,
	Activity_Open=55,
	Activity_Opening=53,
	Activity_Place=31,
	Activity_Recharge=48,
	Activity_Reinforce=7,
	Activity_Repair=32,
	Activity_Rest=34,
	Activity_Reverse=8,
	Activity_Route=1,
	Activity_RouteRubble=2,
	Activity_RunPanic=3,
	Activity_Slip=33,
	Activity_Stamp=36,
	Activity_Stand=0,
	Activity_Teleport=5,
	Activity_TeleportIn=78,
	Activity_Throw=19,
	Activity_ThrowMan=37,
	Activity_ThrownByRockMonster=38,
	Activity_Train=50,
	Activity_TurnLeft=9,
	Activity_TurnRight=10,
	Activity_Type_Count=79,
	Activity_Unpowered=43,
	Activity_Upgrade=41,
	Activity_Waiting1=56,
	Activity_Waiting10=65,
	Activity_Waiting11=66,
	Activity_Waiting12=67,
	Activity_Waiting13=68,
	Activity_Waiting14=69,
	Activity_Waiting15=70,
	Activity_Waiting16=71,
	Activity_Waiting17=72,
	Activity_Waiting18=73,
	Activity_Waiting19=74,
	Activity_Waiting2=57,
	Activity_Waiting20=75,
	Activity_Waiting21=76,
	Activity_Waiting3=58,
	Activity_Waiting4=59,
	Activity_Waiting5=60,
	Activity_Waiting6=61,
	Activity_Waiting7=62,
	Activity_Waiting8=63,
	Activity_Waiting9=64,
	Activity_WakeUp=49,
	Activity_Walk=6
} Activity_Type;

typedef enum LiveFlags5 { // [LegoRR/LegoObject.c|flags:0x4|type:uint] These flags contain LiveObject abilities, and are the one of the fields stored/restored with ObjectRecall.
	LIVEOBJ5_ABILITY_DRIVER=4,
	LIVEOBJ5_ABILITY_DYNAMITE=8,
	LIVEOBJ5_ABILITY_PILOT=1,
	LIVEOBJ5_ABILITY_REPAIR=16,
	LIVEOBJ5_ABILITY_SAILOR=2,
	LIVEOBJ5_ABILITY_SCANNER=32,
	LIVEOBJ5_NONE=0
} LiveFlags5;

typedef char * va_list;

typedef struct astruct astruct, *Pastruct;

struct astruct {
	byte field_0x0;
	byte field_0x1;
	undefined field_0x2;
	undefined field_0x3;
};

typedef struct astruct_1 astruct_1, *Pastruct_1;

struct astruct_1 {
	int field_0x0;
};

typedef struct tagMSG tagMSG, *PtagMSG;

typedef struct tagMSG MSG;

typedef struct tagPOINT tagPOINT, *PtagPOINT;

typedef struct tagPOINT POINT;

struct tagPOINT {
	LONG x;
	LONG y;
};

struct tagMSG {
	HWND hwnd;
	UINT message;
	WPARAM wParam;
	LPARAM lParam;
	DWORD time;
	POINT pt;
};

typedef struct tagWNDCLASSA tagWNDCLASSA, *PtagWNDCLASSA;

typedef LONG_PTR LRESULT;

typedef LRESULT (* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

typedef struct HICON__ HICON__, *PHICON__;

typedef struct HICON__ * HICON;

typedef HICON HCURSOR;

typedef struct HBRUSH__ HBRUSH__, *PHBRUSH__;

typedef struct HBRUSH__ * HBRUSH;

struct HBRUSH__ {
	int unused;
};

struct tagWNDCLASSA {
	UINT style;
	WNDPROC lpfnWndProc;
	int cbClsExtra;
	int cbWndExtra;
	HINSTANCE hInstance;
	HICON hIcon;
	HCURSOR hCursor;
	HBRUSH hbrBackground;
	LPCSTR lpszMenuName;
	LPCSTR lpszClassName;
};

struct HICON__ {
	int unused;
};

typedef struct tagMSG * LPMSG;

typedef struct tagWNDCLASSA WNDCLASSA;

typedef int INT_PTR;

typedef INT_PTR (* DLGPROC)(HWND, UINT, WPARAM, LPARAM);

#define LB_DELETESTRING 386

#define WM_INITDIALOG 272

#define IDCANCEL 2

#define LB_GETCURSEL 392

#define WM_CLOSE 16

#define WM_ACTIVATE 6

#define WM_QUIT 18

#define IDOK 1

#define WM_DESTROY 2

#define WM_WINDOWPOSCHANGING 70

#define BST_CHECKED 1

#define WM_ACTIVATEAPP 28

#define LB_SETCURSEL 390

#define CS_DBLCLKS 8

#define WS_EX_APPWINDOW 262144

#define WM_SETTEXT 12

#define WM_COMMAND 273

#define SWP_NOZORDER 4

#define BM_SETCHECK 241

#define WM_SYSKEYDOWN 260

#define LB_GETTEXT 393

#define WM_NCACTIVATE 134

#define SW_SHOW 5

#define LB_ADDSTRING 384

#define HWND_TOP 0

#define WM_SYSKEYUP 261

typedef struct IMAGE_DOS_HEADER IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;

struct IMAGE_DOS_HEADER {
	char e_magic[2]; // Magic number
	word e_cblp; // Bytes of last page
	word e_cp; // Pages in file
	word e_crlc; // Relocations
	word e_cparhdr; // Size of header in paragraphs
	word e_minalloc; // Minimum extra paragraphs needed
	word e_maxalloc; // Maximum extra paragraphs needed
	word e_ss; // Initial (relative) SS value
	word e_sp; // Initial SP value
	word e_csum; // Checksum
	word e_ip; // Initial IP value
	word e_cs; // Initial (relative) CS value
	word e_lfarlc; // File address of relocation table
	word e_ovno; // Overlay number
	word e_res[4][4]; // Reserved words
	word e_oemid; // OEM identifier (for e_oeminfo)
	word e_oeminfo; // OEM information; e_oemid specific
	word e_res2[10][10]; // Reserved words
	dword e_lfanew; // File address of new exe header
	byte e_program[64]; // Actual DOS program
};

typedef ULONG_PTR DWORD_PTR;

typedef ULONG_PTR SIZE_T;

#define EINVAL 22

#define ENOENT 2

#define EACCES 13

#define ERANGE 34

#define EDOM 33

#define ENOMEM 12

#define ENOEXEC 8

typedef struct tagMIXERCONTROLA tagMIXERCONTROLA, *PtagMIXERCONTROLA;

typedef union _union_1085 _union_1085, *P_union_1085;

typedef union _union_1088 _union_1088, *P_union_1088;

typedef struct _struct_1086 _struct_1086, *P_struct_1086;

typedef struct _struct_1087 _struct_1087, *P_struct_1087;

struct _struct_1086 {
	LONG lMinimum;
	LONG lMaximum;
};

struct _struct_1087 {
	DWORD dwMinimum;
	DWORD dwMaximum;
};

union _union_1085 {
	struct _struct_1086 s;
	struct _struct_1087 s2;
	DWORD dwReserved[6];
};

union _union_1088 {
	DWORD cSteps;
	DWORD cbCustomData;
	DWORD dwReserved[6];
};

struct tagMIXERCONTROLA {
	DWORD cbStruct;
	DWORD dwControlID;
	DWORD dwControlType;
	DWORD fdwControl;
	DWORD cMultipleItems;
	CHAR szShortName[16];
	CHAR szName[64];
	union _union_1085 Bounds;
	union _union_1088 Metrics;
};

typedef UINT MMVERSION;

typedef struct HMIXER__ HMIXER__, *PHMIXER__;

struct HMIXER__ {
	int unused;
};

typedef char * HPSTR;

typedef LRESULT (MMIOPROC)(LPSTR, UINT, LPARAM, LPARAM);

typedef struct waveformat_tag waveformat_tag, *Pwaveformat_tag;

struct waveformat_tag {
	WORD wFormatTag;
	WORD nChannels;
	DWORD nSamplesPerSec;
	DWORD nAvgBytesPerSec;
	WORD nBlockAlign;
};

typedef struct HMIXEROBJ__ HMIXEROBJ__, *PHMIXEROBJ__;

typedef struct HMIXEROBJ__ * HMIXEROBJ;

struct HMIXEROBJ__ {
	int unused;
};

typedef struct HMIXER__ * HMIXER;

typedef HMIXER * LPHMIXER;

typedef struct tagMIXERCAPSA tagMIXERCAPSA, *PtagMIXERCAPSA;

struct tagMIXERCAPSA {
	WORD wMid;
	WORD wPid;
	MMVERSION vDriverVersion;
	CHAR szPname[32];
	DWORD fdwSupport;
	DWORD cDestinations;
};

typedef struct pcmwaveformat_tag pcmwaveformat_tag, *Ppcmwaveformat_tag;

typedef struct waveformat_tag WAVEFORMAT;

struct pcmwaveformat_tag {
	WAVEFORMAT wf;
	WORD wBitsPerSample;
};

typedef struct tagMIXERCONTROLA * LPMIXERCONTROLA;

typedef struct tMIXERCONTROLDETAILS tMIXERCONTROLDETAILS, *PtMIXERCONTROLDETAILS;

typedef union _union_1099 _union_1099, *P_union_1099;

union _union_1099 {
	HWND hwndOwner;
	DWORD cMultipleItems;
};

struct tMIXERCONTROLDETAILS {
	DWORD cbStruct;
	DWORD dwControlID;
	DWORD cChannels;
	union _union_1099 u;
	DWORD cbDetails;
	LPVOID paDetails;
};

typedef struct _struct_1081 _struct_1081, *P_struct_1081;

struct _struct_1081 {
	DWORD dwType;
	DWORD dwDeviceID;
	WORD wMid;
	WORD wPid;
	MMVERSION vDriverVersion;
	CHAR szPname[32];
};

typedef struct tagMIXERLINECONTROLSA tagMIXERLINECONTROLSA, *PtagMIXERLINECONTROLSA;

typedef union _union_1095 _union_1095, *P_union_1095;

union _union_1095 {
	DWORD dwControlID;
	DWORD dwControlType;
};

struct tagMIXERLINECONTROLSA {
	DWORD cbStruct;
	DWORD dwLineID;
	union _union_1095 u;
	DWORD cControls;
	DWORD cbmxctrl;
	LPMIXERCONTROLA pamxctrl;
};

typedef struct pcmwaveformat_tag PCMWAVEFORMAT;

typedef UINT MMRESULT;

typedef struct _MMIOINFO _MMIOINFO, *P_MMIOINFO;

typedef struct _MMIOINFO MMIOINFO;

typedef MMIOPROC * LPMMIOPROC;

typedef struct HTASK__ HTASK__, *PHTASK__;

typedef struct HTASK__ * HTASK;

struct _MMIOINFO {
	DWORD dwFlags;
	FOURCC fccIOProc;
	LPMMIOPROC pIOProc;
	UINT wErrorRet;
	HTASK htask;
	LONG cchBuffer;
	HPSTR pchBuffer;
	HPSTR pchNext;
	HPSTR pchEndRead;
	HPSTR pchEndWrite;
	LONG lBufOffset;
	LONG lDiskOffset;
	DWORD adwInfo[3];
	DWORD dwReserved1;
	DWORD dwReserved2;
	HMMIO hmmio;
};

struct HTASK__ {
	int unused;
};

typedef MMIOINFO * LPCMMIOINFO;

typedef struct tagMIXERLINEA tagMIXERLINEA, *PtagMIXERLINEA;

typedef struct tagMIXERLINEA * LPMIXERLINEA;

struct tagMIXERLINEA {
	DWORD cbStruct;
	DWORD dwDestination;
	DWORD dwSource;
	DWORD dwLineID;
	DWORD fdwLine;
	DWORD_PTR dwUser;
	DWORD dwComponentType;
	DWORD cChannels;
	DWORD cConnections;
	DWORD cControls;
	CHAR szShortName[16];
	CHAR szName[64];
	struct _struct_1081 Target;
};

typedef struct tagMIXERLINECONTROLSA * LPMIXERLINECONTROLSA;

typedef struct tagMIXERCAPSA * LPMIXERCAPSA;

typedef struct _MMIOINFO * LPMMIOINFO;

typedef struct tMIXERCONTROLDETAILS * LPMIXERCONTROLDETAILS;

typedef struct _MMCKINFO * LPMMCKINFO;

#define SEEK_SET 0

#define SEEK_CUR 1

#define WAVE_FORMAT_PCM 1

#define SEEK_END 2

typedef struct _cpinfo _cpinfo, *P_cpinfo;

struct _cpinfo {
	UINT MaxCharSize;
	BYTE DefaultChar[2];
	BYTE LeadByte[12];
};

typedef struct _cpinfo * LPCPINFO;

#define C1_SPACE 8

#define C1_DIGIT 4

#define C1_LOWER 2

#define C1_UPPER 1

#define C1_XDIGIT 128

#define CP_ACP 0

typedef struct _GUID _GUID, *P_GUID;

struct _GUID {
	ulong Data1;
	ushort Data2;
	ushort Data3;
	uchar Data4[8];
};

typedef struct _RGNDATA _RGNDATA, *P_RGNDATA;

typedef struct _RGNDATAHEADER _RGNDATAHEADER, *P_RGNDATAHEADER;

typedef struct _RGNDATAHEADER RGNDATAHEADER;

struct _RGNDATAHEADER {
	DWORD dwSize;
	DWORD iType;
	DWORD nCount;
	DWORD nRgnSize;
	RECT rcBound;
};

struct _RGNDATA {
	RGNDATAHEADER rdh;
	char Buffer[1];
};

typedef struct tagBITMAPINFO tagBITMAPINFO, *PtagBITMAPINFO;

struct tagBITMAPINFO {
	BITMAPINFOHEADER bmiHeader;
	RGBQUAD bmiColors[1];
};

typedef struct tagBITMAPINFO BITMAPINFO;

typedef struct _RGNDATA * LPRGNDATA;

#define BITSPIXEL 12

typedef WCHAR * PCNZWCH;

typedef WCHAR * LPWCH;

typedef WCHAR * LPCWSTR;

typedef LONG * PLONG;

typedef CHAR * LPCH;

typedef DWORD LCID;

typedef CHAR * PCNZCH;

#define HEAP_NO_SERIALIZE 1

#define FILE_ATTRIBUTE_READONLY 1

#define FILE_ATTRIBUTE_NORMAL 128

#define ERROR_ALREADY_EXISTS 183

#define SH_DENYNO 64

typedef struct D3DVECTOR D3DVECTOR, *PD3DVECTOR;

typedef float D3DVALUE;

struct D3DVECTOR {
	D3DVALUE dvX;
	D3DVALUE dvY;
	D3DVALUE dvZ;
};

typedef struct tagPOINT * LPPOINT;

typedef struct HKEY__ HKEY__, *PHKEY__;

struct HKEY__ {
	int unused;
};

typedef int (* FARPROC)(void);

typedef WORD ATOM;

typedef struct HRGN__ HRGN__, *PHRGN__;

typedef struct HRGN__ * HRGN;

struct HRGN__ {
	int unused;
};

typedef BOOL * LPBOOL;

typedef struct HKEY__ * HKEY;

typedef DWORD COLORREF;

typedef HANDLE HGLOBAL;

typedef struct HMENU__ HMENU__, *PHMENU__;

typedef struct HMENU__ * HMENU;

struct HMENU__ {
	int unused;
};

typedef struct _FILETIME * LPFILETIME;

typedef HKEY * PHKEY;

typedef WORD * LPWORD;

typedef void * LPCVOID;

#define FALSE 0

#define MAX_PATH 260

#define TRUE 1

typedef struct IMAGE_OPTIONAL_HEADER32 IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;

typedef struct IMAGE_DATA_DIRECTORY IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

struct IMAGE_DATA_DIRECTORY {
	ImageBaseOffset32 VirtualAddress;
	dword Size;
};

struct IMAGE_OPTIONAL_HEADER32 {
	word Magic;
	byte MajorLinkerVersion;
	byte MinorLinkerVersion;
	dword SizeOfCode;
	dword SizeOfInitializedData;
	dword SizeOfUninitializedData;
	ImageBaseOffset32 AddressOfEntryPoint;
	ImageBaseOffset32 BaseOfCode;
	ImageBaseOffset32 BaseOfData;
	pointer32 ImageBase;
	dword SectionAlignment;
	dword FileAlignment;
	word MajorOperatingSystemVersion;
	word MinorOperatingSystemVersion;
	word MajorImageVersion;
	word MinorImageVersion;
	word MajorSubsystemVersion;
	word MinorSubsystemVersion;
	dword Win32VersionValue;
	dword SizeOfImage;
	dword SizeOfHeaders;
	dword CheckSum;
	word Subsystem;
	word DllCharacteristics;
	dword SizeOfStackReserve;
	dword SizeOfStackCommit;
	dword SizeOfHeapReserve;
	dword SizeOfHeapCommit;
	dword LoaderFlags;
	dword NumberOfRvaAndSizes;
	struct IMAGE_DATA_DIRECTORY DataDirectory[16];
};

typedef struct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct, *PIMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct;

struct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct {
	dword NameOffset;
	dword NameIsString;
};

typedef struct IMAGE_FILE_HEADER IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

struct IMAGE_FILE_HEADER {
	word Machine; // 332
	word NumberOfSections;
	dword TimeDateStamp;
	dword PointerToSymbolTable;
	dword NumberOfSymbols;
	word SizeOfOptionalHeader;
	word Characteristics;
};

typedef struct IMAGE_NT_HEADERS32 IMAGE_NT_HEADERS32, *PIMAGE_NT_HEADERS32;

struct IMAGE_NT_HEADERS32 {
	char Signature[4];
	struct IMAGE_FILE_HEADER FileHeader;
	struct IMAGE_OPTIONAL_HEADER32 OptionalHeader;
};

typedef union IMAGE_RESOURCE_DIRECTORY_ENTRY IMAGE_RESOURCE_DIRECTORY_ENTRY, *PIMAGE_RESOURCE_DIRECTORY_ENTRY;

typedef union IMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion IMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion, *PIMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion;

union IMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion {
	struct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct;
	dword Name;
	word Id;
};

union IMAGE_RESOURCE_DIRECTORY_ENTRY {
	union IMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion NameUnion;
	union IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion DirectoryUnion;
};

typedef struct IMAGE_SECTION_HEADER IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;

typedef union Misc Misc, *PMisc;

typedef enum SectionFlags {
	IMAGE_SCN_ALIGN_1024BYTES=11534336,
	IMAGE_SCN_ALIGN_128BYTES=8388608,
	IMAGE_SCN_ALIGN_16BYTES=5242880,
	IMAGE_SCN_ALIGN_1BYTES=1048576,
	IMAGE_SCN_ALIGN_2048BYTES=12582912,
	IMAGE_SCN_ALIGN_256BYTES=9437184,
	IMAGE_SCN_ALIGN_2BYTES=2097152,
	IMAGE_SCN_ALIGN_32BYTES=6291456,
	IMAGE_SCN_ALIGN_4096BYTES=13631488,
	IMAGE_SCN_ALIGN_4BYTES=3145728,
	IMAGE_SCN_ALIGN_512BYTES=10485760,
	IMAGE_SCN_ALIGN_64BYTES=7340032,
	IMAGE_SCN_ALIGN_8192BYTES=14680064,
	IMAGE_SCN_ALIGN_8BYTES=4194304,
	IMAGE_SCN_CNT_CODE=32,
	IMAGE_SCN_CNT_INITIALIZED_DATA=64,
	IMAGE_SCN_CNT_UNINITIALIZED_DATA=128,
	IMAGE_SCN_GPREL=32768,
	IMAGE_SCN_LNK_COMDAT=4096,
	IMAGE_SCN_LNK_INFO=512,
	IMAGE_SCN_LNK_NRELOC_OVFL=16777216,
	IMAGE_SCN_LNK_OTHER=256,
	IMAGE_SCN_LNK_REMOVE=2048,
	IMAGE_SCN_MEM_16BIT=131072,
	IMAGE_SCN_MEM_DISCARDABLE=33554432,
	IMAGE_SCN_MEM_EXECUTE=536870912,
	IMAGE_SCN_MEM_LOCKED=262144,
	IMAGE_SCN_MEM_NOT_CACHED=67108864,
	IMAGE_SCN_MEM_NOT_PAGED=134217728,
	IMAGE_SCN_MEM_PRELOAD=524288,
	IMAGE_SCN_MEM_PURGEABLE=131072,
	IMAGE_SCN_MEM_READ=1073741824,
	IMAGE_SCN_MEM_SHARED=268435456,
	IMAGE_SCN_MEM_WRITE=2147483648,
	IMAGE_SCN_RESERVED_0001=16,
	IMAGE_SCN_RESERVED_0040=1024,
	IMAGE_SCN_TYPE_NO_PAD=8
} SectionFlags;

union Misc {
	dword PhysicalAddress;
	dword VirtualSize;
};

struct IMAGE_SECTION_HEADER {
	char Name[8];
	union Misc Misc;
	ImageBaseOffset32 VirtualAddress;
	dword SizeOfRawData;
	dword PointerToRawData;
	dword PointerToRelocations;
	dword PointerToLinenumbers;
	word NumberOfRelocations;
	word NumberOfLinenumbers;
	enum SectionFlags Characteristics;
};

typedef struct IMAGE_RESOURCE_DATA_ENTRY IMAGE_RESOURCE_DATA_ENTRY, *PIMAGE_RESOURCE_DATA_ENTRY;

struct IMAGE_RESOURCE_DATA_ENTRY {
	dword OffsetToData;
	dword Size;
	dword CodePage;
	dword Reserved;
};

typedef struct IMAGE_RESOURCE_DIRECTORY IMAGE_RESOURCE_DIRECTORY, *PIMAGE_RESOURCE_DIRECTORY;

struct IMAGE_RESOURCE_DIRECTORY {
	dword Characteristics;
	dword TimeDateStamp;
	word MajorVersion;
	word MinorVersion;
	word NumberOfNamedEntries;
	word NumberOfIdEntries;
};

typedef LONG LSTATUS;

#define HKEY_LOCAL_MACHINE 2147483650

typedef struct IUnknown * LPUNKNOWN;

