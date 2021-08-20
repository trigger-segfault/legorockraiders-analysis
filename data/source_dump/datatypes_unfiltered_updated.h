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

typedef struct Point2I Point2I, *PPoint2I;

struct Point2I {
	int x;
	int y;
};

typedef struct LevelBlock LevelBlock, *PLevelBlock;

typedef enum PredugType {
	PREDUG_EXPOSED=1,
	PREDUG_EXPOSED_SLUGHOLE=3,
	PREDUG_HIDDEN=2,
	PREDUG_HIDDEN_SLUGHOLE=4,
	PREDUG_WALL=0
} PredugType;

typedef enum SurfaceTexture {
	TEXTURE_07=7,
	TEXTURE_ERODE_FULL=54,
	TEXTURE_ERODE_HIGH=38,
	TEXTURE_ERODE_LOW=6,
	TEXTURE_ERODE_MEDIUM=22,
	TEXTURE_GROUND=0,
	TEXTURE_LAVA=70,
	TEXTURE_LAVA_NOTHOT=71,
	TEXTURE_PATH_1=101,
	TEXTURE_PATH_1_POWERED=117,
	TEXTURE_PATH_2=98,
	TEXTURE_PATH_2_POWERED=114,
	TEXTURE_PATH_3=100,
	TEXTURE_PATH_3_POWERED=116,
	TEXTURE_PATH_4=96,
	TEXTURE_PATH_4_POWERED=113,
	TEXTURE_PATH_BUILD=97,
	TEXTURE_PATH_C=99,
	TEXTURE_PATH_C_POWERED=115,
	TEXTURE_PLATE=118,
	TEXTURE_PLATE_POWERED=102,
	TEXTURE_RUBBLE_FULL=16,
	TEXTURE_RUBBLE_HIGH=17,
	TEXTURE_RUBBLE_LOW=19,
	TEXTURE_RUBBLE_MEDIUM=18,
	TEXTURE_SLUGHOLE=48,
	TEXTURE_TUNNEL=112,
	TEXTURE_WALL_C_HARD=52,
	TEXTURE_WALL_C_IMMOVABLE=53,
	TEXTURE_WALL_C_LOOSE=50,
	TEXTURE_WALL_C_MEDIUM=51,
	TEXTURE_WALL_C_SOIL=49,
	TEXTURE_WALL_F_CRYSTALSEAM=32,
	TEXTURE_WALL_F_HARD=4,
	TEXTURE_WALL_F_IMMOVABLE=5,
	TEXTURE_WALL_F_LOOSE=2,
	TEXTURE_WALL_F_MEDIUM=3,
	TEXTURE_WALL_F_ORESEAM=64,
	TEXTURE_WALL_F_RECHARGESEAM=103,
	TEXTURE_WALL_F_SOIL=1,
	TEXTURE_WALL_GAP=119,
	TEXTURE_WALL_O_HARD=84,
	TEXTURE_WALL_O_IMMOVABLE=85,
	TEXTURE_WALL_O_LOOSE=82,
	TEXTURE_WALL_O_MEDIUM=83,
	TEXTURE_WALL_O_SOIL=81,
	TEXTURE_WALL_R_HARD=36,
	TEXTURE_WALL_R_IMMOVABLE=37,
	TEXTURE_WALL_R_LOOSE=34,
	TEXTURE_WALL_R_MEDIUM=35,
	TEXTURE_WALL_R_SOIL=33,
	TEXTURE_WATER=69
} SurfaceTexture;

typedef enum TerrainType {
	TERRAIN_CAVERN=17,
	TERRAIN_CRYSTALSEAM=10,
	TERRAIN_HARD=2,
	TERRAIN_IMMOVABLE=1,
	TERRAIN_LAKE=9,
	TERRAIN_LAVA=6,
	TERRAIN_LOOSE=4,
	TERRAIN_MEDIUM=3,
	TERRAIN_ORESEAM=8,
	TERRAIN_PATH=14,
	TERRAIN_RECHARGESEAM=11,
	TERRAIN_REINFORCED=13,
	TERRAIN_RUBBLE=12,
	TERRAIN_SLUGHOLE=15,
	TERRAIN_SOIL=5,
	TERRAIN_TUNNEL=0,
	TERRAIN_UNDISCOVERED=16,
	TERRAIN_WATER_unused=7
} TerrainType;

typedef enum CryOreType {
	CRYORE_CRYSTAL_1=1,
	CRYORE_CRYSTAL_10=13,
	CRYORE_CRYSTAL_10_alt=15,
	CRYORE_CRYSTAL_1_alt=3,
	CRYORE_CRYSTAL_25=17,
	CRYORE_CRYSTAL_25_alt=19,
	CRYORE_CRYSTAL_3=5,
	CRYORE_CRYSTAL_3_alt=7,
	CRYORE_CRYSTAL_5=9,
	CRYORE_CRYSTAL_5_alt=11,
	CRYORE_NONE=0,
	CRYORE_ORE_1=2,
	CRYORE_ORE_10=14,
	CRYORE_ORE_10_alt=16,
	CRYORE_ORE_1_alt=4,
	CRYORE_ORE_25=18,
	CRYORE_ORE_25_alt=20,
	CRYORE_ORE_3=6,
	CRYORE_ORE_3_alt=8,
	CRYORE_ORE_5=10,
	CRYORE_ORE_5_alt=12
} CryOreType;

typedef enum ErodeType {
	ERODE_FAST_ALWAYS=8,
	ERODE_FAST_LAVA=7,
	ERODE_MEDIUM_ALWAYS=6,
	ERODE_MEDIUM_LAVA=5,
	ERODE_NONE=0,
	ERODE_SLOW_ALWAYS=4,
	ERODE_SLOW_LAVA=3,
	ERODE_VERYFAST_ALWAYS=10,
	ERODE_VERYFAST_LAVA=9,
	ERODE_VERYSLOW_ALWAYS=2,
	ERODE_VERYSLOW_LAVA=1
} ErodeType;

typedef enum LevelBlockFlags1 {
	BLOCK1_EXPOSED=67108864,
	BLOCK1_HIDDEN=131072,
	BLOCK1_NONE=0,
	BLOCK1_POWERPATH=536870912,
	BLOCK1_REINFORCED=32,
	BLOCK1_RUBBLE_FULL=3,
	BLOCK1_RUBBLE_LOW=1,
	BLOCK1_RUBBLE_MEDIUM=2,
	BLOCK1_UNK_10=16,
	BLOCK1_UNK_1000=4096,
	BLOCK1_UNK_100000=1048576,
	BLOCK1_UNK_200=512,
	BLOCK1_UNK_200000=2097152,
	BLOCK1_UNK_40=64,
	BLOCK1_UNK_400=1024,
	BLOCK1_UNK_4000=16384,
	BLOCK1_UNK_400000=4194304,
	BLOCK1_UNK_40000000=1073741824,
	BLOCK1_UNK_8=8,
	BLOCK1_UNK_80=128,
	BLOCK1_UNK_800=2048,
	BLOCK1_UNK_8000=32768,
	BLOCK1_UNK_80000=524288,
	BLOCK1_UNK_8000000=134217728,
	BLOCK1_UNK_80000000=2147483648
} LevelBlockFlags1;

typedef enum LevelBlockFlags2 {
	BLOCK2_EMERGE_POINT=64,
	BLOCK2_EMERGE_TRIGGER=128,
	BLOCK2_NONE=0,
	BLOCK2_SLUGHOLE_EXPOSED=32,
	BLOCK2_SLUGHOLE_HIDDEN=512
} LevelBlockFlags2;

typedef struct LevelStruct_1c LevelStruct_1c, *PLevelStruct_1c;

typedef struct Container Container, *PContainer;

typedef struct IDirect3DRMFrame3 IDirect3DRMFrame3, *PIDirect3DRMFrame3;

typedef struct Container_TypeData Container_TypeData, *PContainer_TypeData;

typedef enum ResourceType {
	RESOURCETYPE_COUNT=9,
	RESOURCE_ACT=4,
	RESOURCE_ANIM=3,
	RESOURCE_FRAME=2,
	RESOURCE_LIGHT=5,
	RESOURCE_LWO=8,
	RESOURCE_LWS=7,
	RESOURCE_MESH=1,
	RESOURCE_NULL=0,
	RESOURCE_REFERENCE=6,
	RESOURCE__INVALID=4294967295
} ResourceType;

typedef enum ResourceDataFlags {
	RESDATA_NONE=0,
	RESDATA_UNK_10=16,
	RESDATA_UNK_2=2,
	RESDATA_UNK_20=32,
	RESDATA_UNK_8=8,
	RESDATA_UNK_80=128
} ResourceDataFlags;

typedef struct Container_CloneData Container_CloneData, *PContainer_CloneData;

typedef struct IDirect3DRMFrame3Vtbl IDirect3DRMFrame3Vtbl, *PIDirect3DRMFrame3Vtbl;

typedef long HRESULT;

typedef struct IUnknown IUnknown, *PIUnknown;


// WARNING! conflicting data type names: /guiddef.h/GUID - /GUID

typedef GUID IID;

typedef CHAR * LPCSTR;

typedef DWORD * LPDWORD;

typedef struct IDirect3DRMLight IDirect3DRMLight, *PIDirect3DRMLight;

typedef enum D3DRMCombineType { // TD3DRMCombineType
	D3DRMCOMBINE_AFTER=2,
	D3DRMCOMBINE_BEFORE=1,
	D3DRMCOMBINE_REPLACE=0
} D3DRMCombineType;

typedef struct Matrix4F Matrix4F, *PMatrix4F;

typedef struct IDirect3DRMVisual IDirect3DRMVisual, *PIDirect3DRMVisual;

typedef struct IDirect3DRMFrameArray IDirect3DRMFrameArray, *PIDirect3DRMFrameArray;

typedef struct IDirect3DRMLightArray IDirect3DRMLightArray, *PIDirect3DRMLightArray;

typedef enum D3DRMMaterialMode {
	D3DRMMATERIAL_FROMFRAME=2,
	D3DRMMATERIAL_FROMMESH=0,
	D3DRMMATERIAL_FROMPARENT=1
} D3DRMMaterialMode;

typedef struct Vector3F Vector3F, *PVector3F;

typedef enum D3DRMSortMode {
	D3DRMSORT_BACKTOFRONT=3,
	D3DRMSORT_FROMPARENT=0,
	D3DRMSORT_FRONTTOBACK=2,
	D3DRMSORT_NONE=1
} D3DRMSortMode;

typedef struct IDirect3DRMTexture3 IDirect3DRMTexture3, *PIDirect3DRMTexture3;

typedef enum D3DRMFrameConstraint {
	D3DRMCONSTRAIN_X=2,
	D3DRMCONSTRAIN_Y=1,
	D3DRMCONSTRAIN_Z=0
} D3DRMFrameConstraint;

typedef struct IDirectDrawSurface IDirectDrawSurface, *PIDirectDrawSurface;

typedef enum D3DRMFogMode {
	D3DRMFOG_EXPONENTIAL=1,
	D3DRMFOG_EXPONENTIALSQUARED=2,
	D3DRMFOG_LINEAR=0
} D3DRMFogMode;

typedef enum D3DRMZBufferMode {
	D3DRMZBUFFER_DISABLE=2,
	D3DRMZBUFFER_ENABLE=1,
	D3DRMZBUFFER_FROMPARENT=0
} D3DRMZBufferMode;

typedef enum D3DRMSceneFogMethod { // Values for flags in IDirect3DRMFrame3::SetSceneFogMethod
	D3DRMFOGMETHOD_ANY=4,
	D3DRMFOGMETHOD_TABLE=2,
	D3DRMFOGMETHOD_VERTEX=1,
	D3DRMFOGMETHOD__NONE=0
} D3DRMSceneFogMethod;

typedef struct IDirect3DRMMesh IDirect3DRMMesh, *PIDirect3DRMMesh;

typedef struct Mesh Mesh, *PMesh;

typedef struct IUnknownVtbl IUnknownVtbl, *PIUnknownVtbl;

typedef struct IDirect3DRMLightVtbl IDirect3DRMLightVtbl, *PIDirect3DRMLightVtbl;

typedef enum D3DRMLightType {
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

typedef struct D3DRMBox D3DRMBox, *PD3DRMBox;

typedef enum D3DRMGroupIndex { // group indexes begin a 0
	D3DRMGROUP_0=0,
	D3DRMGROUP_ALLGROUPS=4294967295
} D3DRMGroupIndex;

typedef struct D3DRMVertex D3DRMVertex, *PD3DRMVertex;

typedef enum D3DRMMapping {
	D3DRMMAP_PERSPCORRECT=4,
	D3DRMMAP_WRAPU=1,
	D3DRMMAP_WRAPV=2
} D3DRMMapping;

typedef struct IDirect3DRMTexture IDirect3DRMTexture, *PIDirect3DRMTexture;

typedef enum D3DRMRenderQuality {
	D3DRMRENDER_FLAT=136,
	D3DRMRENDER_GOURAUD=137,
	D3DRMRENDER_PHONG=138,
	D3DRMRENDER_UNLITFLAT=128,
	D3DRMRENDER_WIREFRAME=64
} D3DRMRenderQuality;

typedef struct Mesh_Group Mesh_Group, *PMesh_Group;

typedef struct IDirect3DRMUserVisual IDirect3DRMUserVisual, *PIDirect3DRMUserVisual;

typedef struct Mesh_RenderDesc Mesh_RenderDesc, *PMesh_RenderDesc;

typedef struct Viewport Viewport, *PViewport;

typedef struct Mesh_LightWave_Surface Mesh_LightWave_Surface, *PMesh_LightWave_Surface;

typedef struct IDirect3DRMFrameVtbl IDirect3DRMFrameVtbl, *PIDirect3DRMFrameVtbl;

typedef struct D3DRMPaletteEntry D3DRMPaletteEntry, *PD3DRMPaletteEntry;

typedef struct IDirect3DRMTextureVtbl IDirect3DRMTextureVtbl, *PIDirect3DRMTextureVtbl;

typedef struct Mesh_Vertex Mesh_Vertex, *PMesh_Vertex;

typedef struct D3DMaterial D3DMaterial, *PD3DMaterial;

typedef struct IDirect3DTexture2 IDirect3DTexture2, *PIDirect3DTexture2;

typedef struct IDirect3DRMUserVisualVtbl IDirect3DRMUserVisualVtbl, *PIDirect3DRMUserVisualVtbl;

typedef struct IDirect3DRMViewport2 IDirect3DRMViewport2, *PIDirect3DRMViewport2;

typedef struct Container_Texture Container_Texture, *PContainer_Texture;

typedef struct ColourRGBAF ColourRGBAF, *PColourRGBAF;

typedef enum D3DRMPaletteFlags {
	D3DRMPALETTE_FREE=0,
	D3DRMPALETTE_READONLY=1,
	D3DRMPALETTE_RESERVED=2
} D3DRMPaletteFlags;

typedef struct IDirect3DTexture2Vtbl IDirect3DTexture2Vtbl, *PIDirect3DTexture2Vtbl;

typedef struct IDirect3DRMViewport2Vtbl IDirect3DRMViewport2Vtbl, *PIDirect3DRMViewport2Vtbl;

typedef struct IDirect3DRMDevice3 IDirect3DRMDevice3, *PIDirect3DRMDevice3;

typedef enum D3DRMViewportClearOptions { // Values for flags in IDirect3DRMViewport2::Clear2
	D3DRMCLEAR_ALL=7,
	D3DRMCLEAR_DIRTYRECTS=4,
	D3DRMCLEAR_TARGET=1,
	D3DRMCLEAR_ZBUFFER=2
} D3DRMViewportClearOptions;

typedef enum D3DRMProjectionType { // Do not use righthanded perspective in IDirect3DRMViewport2::SetProjection(). Set up righthanded mode by using IDirect3DRM3::SetOptions().
	D3DRMPROJECT_ORTHOGRAPHIC=1,
	D3DRMPROJECT_PERSPECTIVE=0,
	D3DRMPROJECT_RIGHTHANDORTHOGRAPHIC=3,
	D3DRMPROJECT_RIGHTHANDPERSPECTIVE=2
} D3DRMProjectionType;

typedef struct Vector4F Vector4F, *PVector4F;

typedef struct IDirect3DRMPickedArray IDirect3DRMPickedArray, *PIDirect3DRMPickedArray;

typedef struct IDirect3DViewport IDirect3DViewport, *PIDirect3DViewport;

typedef struct IDirectDrawSurface4 IDirectDrawSurface4, *PIDirectDrawSurface4;

typedef struct IDirect3DRMDevice3Vtbl IDirect3DRMDevice3Vtbl, *PIDirect3DRMDevice3Vtbl;

typedef struct DDPIXELFORMAT DDPIXELFORMAT, *PDDPIXELFORMAT;

typedef struct IDirect3DRMPickedArrayVtbl IDirect3DRMPickedArrayVtbl, *PIDirect3DRMPickedArrayVtbl;

typedef struct D3DRMPickDesc D3DRMPickDesc, *PD3DRMPickDesc;

typedef struct IDirect3DViewportVtbl IDirect3DViewportVtbl, *PIDirect3DViewportVtbl;

typedef struct IDirectDrawSurface4Vtbl IDirectDrawSurface4Vtbl, *PIDirectDrawSurface4Vtbl;

typedef struct tagRECT tagRECT, *PtagRECT;

typedef struct tagRECT * LPRECT;

typedef struct DDSCAPS2 DDSCAPS2, *PDDSCAPS2;

typedef struct IDirectDrawPalette IDirectDrawPalette, *PIDirectDrawPalette;

typedef struct DDSURFACEDESC2 DDSURFACEDESC2, *PDDSURFACEDESC2;

typedef struct DDCOLORKEY DDCOLORKEY, *PDDCOLORKEY;

typedef struct IDirectDrawPaletteVtbl IDirectDrawPaletteVtbl, *PIDirectDrawPaletteVtbl;

struct Vector3F {
	float x;
	float y;
	float z;
};

struct D3DRMVertex { // Extension of D3DVertex with color field
	struct Vector3F position; // Homogeneous coordinates
	struct Vector3F normal; // Normal
	float tu; // Texture coordinates
	float tv; // Texture coordinates
	DWORD colour;
};

struct Mesh_RenderDesc {
	void (* renderCallback)(struct Mesh *, void *, struct Viewport *);
	void * renderCallbackData;
	uint renderFlags; // determines a lot of render states
};

struct LevelBlock {
	enum PredugType predug;
	enum SurfaceTexture texture;
	enum TerrainType terrain;
	byte field_3;
	byte blockpointer;
	enum CryOreType cryOre;
	enum ErodeType erodeSpeed;
	byte field_7;
	enum LevelBlockFlags1 flags1;
	enum LevelBlockFlags2 flags2;
	undefined4 field_10;
	float float_14;
	struct LevelStruct_1c * struct1c_18;
	undefined4 field_1c;
	short randomness;
	undefined field_0x22;
	undefined field_0x23;
	uint numLandSlides;
	uint clickCount;
	int generateCrystals;
	int generateOre;
	byte aiNode;
	undefined field_0x35;
	undefined field_0x36;
	undefined field_0x37;
	BOOL fallinUpper;
	float fallinIntensity;
	float fallinTimer;
	undefined4 field_44;
};

struct IDirect3DViewportVtbl {
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

struct IDirect3DRMFrame3 {
	struct IDirect3DRMFrame3Vtbl * lpVtbl;
};

struct IDirect3DRMPickedArray {
	struct IDirect3DRMPickedArrayVtbl * lpVtbl;
};

struct Container_CloneData { // structure assigned to ResourceData->field_24 (allocated for ACT,ANIM resource types)
	struct Container * clonedFrom; // NULL if this is the original
	struct Container * * cloneTable; // List of clones (NULL for unused elements)
	uint cloneCount; // Total number of clones made and clone's number in the list.
	struct IDirect3DRMFrame3 * cloneNumber; // (init: ResourceData->frame2 IDirect3DRMFrame3 * ???)
	BOOL used; // (init: 1)
};

struct IDirect3DRMFrameArray {
	struct IDirect3DRMFrameArrayVtbl * lpVtbl;
};

struct Container {
	struct IDirect3DRMFrame3 * masterFrame; // (frame1)
	struct IDirect3DRMFrame3 * activityFrame; // (frame2)
	struct IDirect3DRMFrame3 * hiddenFrame; // (frame3)
	struct Container_TypeData * typeData;
	enum ResourceType type;
	enum ResourceDataFlags flags;
	pointer activityCallback;
	void * activityCallbackData;
	void * userData; // (often LiveObject*)
	struct Container_CloneData * cloneData; // Only used by animsets.
	struct Container * nextFree;
};

struct IDirectDrawSurfaceVtbl {
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

struct DDSCAPS2 {
	DWORD dwCaps; // capabilities of surface wanted
	DWORD dwCaps2;
	DWORD dwCaps3;
	DWORD dwCaps4_VolumeDepth;
};

struct IDirect3DRMTexture3 {
	struct IDirect3DRMTexture3Vtbl * lpVtbl;
};

struct IDirect3DRMTextureVtbl {
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

struct IDirect3DRMFrame3Vtbl {
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

struct Container_TypeData {
	char * name;
	struct IDirect3DRMLight * light;
	struct IDirect3DRMMesh * mesh;
	struct Mesh * transMesh;
};

struct IDirect3DRMPickedArrayVtbl { // Subclass of IDirect3DRMArrayVtbl
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	DWORD (* GetSize)(struct IDirect3DRMPickedArray *);
	HRESULT (* GetPick)(struct IDirect3DRMPickedArray *, DWORD, struct IDirect3DRMVisual * *, struct IDirect3DRMFrameArray * *, struct D3DRMPickDesc *);
};

struct IDirect3DRMViewport2Vtbl {
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

struct D3DRMBox {
	struct Vector3F min;
	struct Vector3F max;
};

struct Mesh {
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

struct IDirect3DRMMeshVtbl {
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
	HRESULT (* GetBox)(struct IDirect3DRMMesh *, struct D3DRMBox *);
	HRESULT (* AddGroup)(struct IDirect3DRMMesh *, DWORD, DWORD, DWORD, void *, enum D3DRMGroupIndex *);
	HRESULT (* SetVertices)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex, DWORD, DWORD, struct D3DRMVertex *);
	HRESULT (* SetGroupColor)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex, DWORD);
	HRESULT (* SetGroupColorRGB)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex, float, float, float);
	HRESULT (* SetGroupMapping)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex);
	HRESULT (* SetGroupQuality)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex, enum D3DRMMapping);
	pointer SetGroupMaterial;
	HRESULT (* SetGroupTexture)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex, struct IDirect3DRMTexture *);
	DWORD (* GetGroupCount)(struct IDirect3DRMMesh *);
	HRESULT (* GetGroup)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex, DWORD *, DWORD *, DWORD *, DWORD *, void *);
	HRESULT (* GetVertices)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex, DWORD, DWORD, struct D3DRMVertex *);
	DWORD (* GetGroupColor)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex);
	D3DRMMapping (* GetGroupMapping)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex);
	D3DRMRenderQuality (* GetGroupQuality)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex);
	pointer GetGroupMaterial;
	HRESULT (* GetGroupTexture)(struct IDirect3DRMMesh *, enum D3DRMGroupIndex, struct IDirect3DRMTexture * *);
};

struct IDirect3DRMFrame {
	struct IDirect3DRMFrameVtbl * lpVtbl;
};

struct IDirect3DRMTexture3Vtbl {
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

struct ColourRGBAF {
	float red;
	float green;
	float blue;
	float alpha;
};

struct D3DMaterial {
	DWORD dwSize;
	struct ColourRGBAF diffuse;
	struct ColourRGBAF ambient;
	struct ColourRGBAF specular;
	struct ColourRGBAF emissive;
	float power;
	DWORD hTexture;
	DWORD dwRampSize;
};

struct Mesh_Group {
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

struct IDirectDrawSurface4Vtbl {
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

struct IDirectDrawPalette {
	struct IDirectDrawPaletteVtbl * lpVtbl;
};

struct IDirect3DTexture2Vtbl {
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer GetHandle;
	pointer PaletteChanged;
	pointer Load;
};

struct Vector4F { // D3DRMVector4D
	float x;
	float y;
	float z;
	float w;
};

struct IUnknown {
	struct IUnknownVtbl * lpVtbl;
};

struct IDirect3DRMLightArray {
	struct IDirect3DRMLightArrayVtbl * lpVtbl;
};

struct DDPIXELFORMAT { // https://docs.microsoft.com/en-us/windows/win32/api/ddraw/ns-ddraw-ddpixelformat
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwFourCC;
	DWORD dwRGBBitCount;
	DWORD dwRBitMask;
	DWORD dwGBitMask;
	DWORD dwBBitMask;
	DWORD dwRGBAlphaBitMask;
};

struct IDirect3DRMVisual { // Identical to IDirect3DRMObject
	struct IDirect3DRMVisualVtbl * lpVtbl;
};

struct IDirect3DRMDevice3Vtbl {
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

struct IDirect3DViewport {
	struct IDirect3DViewportVtbl * lpVtbl;
};

struct IDirect3DRMVisualVtbl { // Identical to IDirect3DRMObjectVtbl
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

struct IDirect3DRMUserVisual {
	struct IDirect3DRMUserVisualVtbl * lpVtbl;
};

struct IDirect3DRMMesh {
	struct IDirect3DRMMeshVtbl * lpVtbl;
};

struct D3DRMPaletteEntry {
	byte red; // 0 .. 255
	byte green; // 0 .. 255
	byte blue; // 0 .. 255
	enum D3DRMPaletteFlags flags; // one of D3DRMPaletteFlags
};

struct D3DRMImage {
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

struct DDCOLORKEY {
	DWORD dwColorSpaceLowValue;
	DWORD dwColorSpaceHighValue;
};

struct Mesh_Vertex { // Untransformed/unlit vertices
	struct Vector3F position; // Homogeneous coordinates
	struct Vector3F normal; // Normal
	float tu; // Texture coordinates
	float tv; // Texture coordinates
};

struct IDirect3DTexture2 {
	struct IDirect3DTexture2Vtbl * lpVtbl;
};

struct LevelStruct_1c { // related to Terrain map?
	struct Container * resData;
	struct Point2I position;
	undefined4 field_c;
	struct LevelStruct_1c * next;
	struct LevelStruct_1c * previous;
	BOOL bool_18;
};

struct IDirect3DRMLightArrayVtbl { // Subclass of IDirect3DRMArrayVtbl
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	DWORD (* GetSize)(struct IDirect3DRMLightArray *);
	HRESULT (* GetElement)(struct IDirect3DRMLightArray *, DWORD, struct IDirect3DRMLight * *);
};

struct IDirect3DRMLight {
	struct IDirect3DRMLightVtbl * lpVtbl;
};

struct Matrix4F {
	float values[4][4];
};

struct DDSURFACEDESC2 {
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

struct IDirectDrawPaletteVtbl {
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

struct IDirectDrawSurface4 {
	struct IDirectDrawSurface4Vtbl * lpVtbl;
};

struct IDirect3DRMLightVtbl {
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

struct IDirect3DRMViewport2 {
	struct IDirect3DRMViewport2Vtbl * lpVtbl;
};

struct Container_Texture {
	struct IDirectDrawSurface4 * surface;
	struct IDirect3DRMTexture3 * texture;
	BOOL colourKey;
};

struct IDirect3DRMTexture {
	struct IDirect3DRMTextureVtbl * lpVtbl;
};

struct Viewport {
	float xoffset; // Position on viewport normalised to between 0.0 and 1.0
	float yoffset; // Position on viewport normalised to between 0.0 and 1.0
	float width; // Width and height of the viewport normalised as above
	float height; // Width and height of the viewport normalised as above
	struct IDirect3DRMViewport2 * lpVP; // Pointer to D3D(RM) viewport interface
	float smoothFOV; // (init: 0)
	BOOL rendering;
	struct Viewport * nextFree;
};

struct IDirectDrawSurface {
	struct IDirectDrawSurfaceVtbl * lpVtbl;
};

struct IDirect3DRMDevice3 {
	struct IDirect3DRMDevice3Vtbl * lpVtbl;
};

struct IDirect3DRMFrameVtbl {
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

struct D3DRMPickDesc {
	DWORD ulFaceIdx;
	enum D3DRMGroupIndex lGroupIdx;
	struct Vector3F vPosition;
};

struct IUnknownVtbl {
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, void * *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
};

struct IDirect3DRMFrameArrayVtbl { // Subclass of IDirect3DRMArrayVtbl
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	DWORD (* GetSize)(struct IDirect3DRMFrameArray *);
	HRESULT (* GetElement)(struct IDirect3DRMFrameArray *, DWORD, struct IDirect3DRMFrame * *);
};

struct IDirect3DRMUserVisualVtbl {
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

struct Mesh_LightWave_Surface {
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

typedef struct GameManager GameManager, *PGameManager;

typedef struct CFGProperty CFGProperty, *PCFGProperty;

typedef enum GraphicsQuality {
	QUALITY_FLAT=2,
	QUALITY_GOURAUD=3,
	QUALITY_UNLITFLAT=1,
	QUALITY_WIREFRAME=0
} GraphicsQuality;

typedef struct LevelData LevelData, *PLevelData;

typedef struct CameraData CameraData, *PCameraData;

typedef struct ImageFont ImageFont, *PImageFont;

typedef struct TextWindow TextWindow, *PTextWindow;

typedef struct Point2F Point2F, *PPoint2F;

typedef struct LiveObject LiveObject, *PLiveObject;

typedef struct VehicleData VehicleData, *PVehicleData;

typedef struct CreatureData CreatureData, *PCreatureData;

typedef struct BuildingData BuildingData, *PBuildingData;

typedef struct UpgradeData UpgradeData, *PUpgradeData;

typedef struct ColourRGBF ColourRGBF, *PColourRGBF;

typedef enum ObjectType {
	OBJECT_BARRIER=9,
	OBJECT_BOULDER=5,
	OBJECT_BUILDING=4,
	OBJECT_DYNAMITE=8,
	OBJECT_ELECTRICFENCE=11,
	OBJECT_ELECTRICFENCESTUD=14,
	OBJECT_FREEZER=17,
	OBJECT_ICECUBE=18,
	OBJECT_LASERSHOT=19,
	OBJECT_MINIFIGURE=2,
	OBJECT_NONE=0,
	OBJECT_OOHSCARY=13,
	OBJECT_ORE=7,
	OBJECT_PATH=15,
	OBJECT_POWERCRYSTAL=6,
	OBJECT_PUSHER=16,
	OBJECT_ROCKMONSTER=3,
	OBJECT_SPIDERWEB=12,
	OBJECT_TVCAMERA=4294967295,
	OBJECT_UPGRADEPART=10,
	OBJECT_VEHICLE=1
} ObjectType;

typedef enum Direction {
	DIRECTION_DOWN=2,
	DIRECTION_LEFT=3,
	DIRECTION_RIGHT=1,
	DIRECTION_UP=0,
	DIRECTION__COUNT=4
} Direction;

typedef struct ImageBMP ImageBMP, *PImageBMP;

typedef enum ViewMode {
	VIEW_FIRSTPERSON=0,
	VIEW_TOPDOWN=1
} ViewMode;

typedef enum GameFlags1 {
	GAME1_ALWAYSROCKFALL=8388608,
	GAME1_CAMERADISABLED=1048576,
	GAME1_CLEAR=1024,
	GAME1_DEBUG_NOCLIP_FPS=1073741824,
	GAME1_DEBUG_NONERPS=16777216,
	GAME1_DYNAMICPM=524288,
	GAME1_FOGCOLOURRGB=32768,
	GAME1_FRAMERATEMONITOR=64,
	GAME1_HIGHFOGCOLOURRGB=65536,
	GAME1_LASERTRACKER=268435456,
	GAME1_LEVELSTART=4,
	GAME1_MEMORYMONITOR=128,
	GAME1_MUSICON=8,
	GAME1_NONE=0,
	GAME1_ONLYBUILDONPATHS=4194304,
	GAME1_PANELS=2048,
	GAME1_PAUSED=33554432,
	GAME1_RADARON=2,
	GAME1_RADAR_MAPVIEW=4096,
	GAME1_RADAR_TRACKOBJECTVIEW=8192,
	GAME1_SOUNDON=16,
	GAME1_STREAMNERPSSPEACH=67108864,
	GAME1_UNK_100=256,
	GAME1_UNK_200=512,
	GAME1_UNK_20000=131072,
	GAME1_UNK_200000=2097152,
	GAME1_UNK_20000000=536870912,
	GAME1_UNK_4000=16384,
	GAME1_UNK_40000=262144,
	GAME1_UNK_8000000=134217728,
	GAME1_UNK_80000000=2147483648,
	GAME1_WALLPROMESHES=32
} GameFlags1;

typedef enum GameFlags2 {
	GAME2_ALLOWDEBUGKEYS=16,
	GAME2_ALLOWEDITMODE=32,
	GAME2_ALLOWRENAME=131072,
	GAME2_CALLTOARMS=1,
	GAME2_CAMERAMOVING=512,
	GAME2_DISABLETOOLTIPSOUND=1048576,
	GAME2_GENERATESPIDERS=524288,
	GAME2_INMENU=4096,
	GAME2_INOPTIONSMENU=256,
	GAME2_MENU_HASNEXT=16384,
	GAME2_MENU_HASPREVIOUS=32768,
	GAME2_MOUSE_INSIDEGAMEVIEW=1024,
	GAME2_MUSICON=2048,
	GAME2_NOAUTOEAT=2097152,
	GAME2_NOMULTISELECT=8192,
	GAME2_NONE=0,
	GAME2_RECALLOLOBJECTS=262144,
	GAME2_SHOWDEBUGTOOLTIPS=8,
	GAME2_UNK_2=2,
	GAME2_UNK_4=4,
	GAME2_UNK_40=64,
	GAME2_UNK_80=128
} GameFlags2;

typedef enum GameFlags3 {
	GAME3_LOADVEHICLE=16,
	GAME3_NONE=0,
	GAME3_PICKUPOBJECT=8,
	GAME3_PLACEBUILDING=128,
	GAME3_UNK_1=1,
	GAME3_UNK_2=2,
	GAME3_UNK_20=32,
	GAME3_UNK_4=4,
	GAME3_UNK_40=64
} GameFlags3;

typedef struct SurfaceMap SurfaceMap, *PSurfaceMap;

typedef struct Size2I Size2I, *PSize2I;

typedef enum BOOL3 { // A 3-state boolean for True, False, or Error
	BOOL3_ERROR=2,
	BOOL3_FALSE=0,
	BOOL3_TRUE=1
} BOOL3;

typedef struct SurfaceTextureGrid SurfaceTextureGrid, *PSurfaceTextureGrid;

typedef struct LevelStruct_3c LevelStruct_3c, *PLevelStruct_3c;

typedef struct ObjectiveData ObjectiveData, *PObjectiveData;

typedef struct BlockPointer BlockPointer, *PBlockPointer;

typedef enum TextureType {
	TEXTURES_ICE=2,
	TEXTURES_LAVA=1,
	TEXTURES_ROCK=0,
	TEXTURES__INVALID=4294967295
} TextureType;

typedef enum LevelCompleteStatus {
	LEVELSTATUS_COMPLETE=1,
	LEVELSTATUS_FAILED=2,
	LEVELSTATUS_FAILED_CRYSTALS=3,
	LEVELSTATUS_FAILED_OTHER=4,
	LEVELSTATUS_NONE=0
} LevelCompleteStatus;

typedef enum CameraType {
	CAMERATYPE_FIRSTPERSON=3,
	CAMERATYPE_NONE=0,
	CAMERATYPE_RADAR=2,
	CAMERATYPE_TOPDOWN=1
} CameraType;

typedef struct Range2F Range2F, *PRange2F;

typedef enum CameraFlags {
	CAMERA_DISTRANGE=4,
	CAMERA_NONE=0,
	CAMERA_TILTRANGE=1,
	CAMERA_UNK_8=8,
	CAMERA_YAWRANGE=2
} CameraFlags;

typedef struct Rect2F Rect2F, *PRect2F;

typedef struct AITaskData AITaskData, *PAITaskData;

typedef struct FlockData FlockData, *PFlockData;

typedef struct ObjectStats ObjectStats, *PObjectStats;

typedef enum ToolType {
	TOOL_BIRDSCARER=6,
	TOOL_DRILL=0,
	TOOL_FREEZERGUN=7,
	TOOL_HAMMER=2,
	TOOL_LASER=4,
	TOOL_PUSHERGUN=5,
	TOOL_SPADE=1,
	TOOL_SPANNER=3,
	TOOL__INVALID=4294967295
} ToolType;

typedef enum LiveFlags1 {
	LIVEOBJ1_CARRYING=1024,
	LIVEOBJ1_CLEARING=262144,
	LIVEOBJ1_EATING=1073741824,
	LIVEOBJ1_LIFTING=2,
	LIVEOBJ1_MOVING=1,
	LIVEOBJ1_NONE=0,
	LIVEOBJ1_PLACING=524288,
	LIVEOBJ1_REINFORCING=64,
	LIVEOBJ1_REST=536870912,
	LIVEOBJ1_TURNING=4,
	LIVEOBJ1_TURNRIGHT=128,
	LIVEOBJ1_UNK_10=16,
	LIVEOBJ1_UNK_100=256,
	LIVEOBJ1_UNK_1000=4096,
	LIVEOBJ1_UNK_10000=65536,
	LIVEOBJ1_UNK_100000=1048576,
	LIVEOBJ1_UNK_1000000=16777216,
	LIVEOBJ1_UNK_10000000=268435456,
	LIVEOBJ1_UNK_200=512,
	LIVEOBJ1_UNK_2000=8192,
	LIVEOBJ1_UNK_20000=131072,
	LIVEOBJ1_UNK_200000=2097152,
	LIVEOBJ1_UNK_4000=16384,
	LIVEOBJ1_UNK_400000=4194304,
	LIVEOBJ1_UNK_4000000=67108864,
	LIVEOBJ1_UNK_8=8,
	LIVEOBJ1_UNK_800=2048,
	LIVEOBJ1_UNK_8000=32768,
	LIVEOBJ1_UNK_800000=8388608,
	LIVEOBJ1_UNK_80000000=2147483648
} LiveFlags1;

typedef enum LiveFlags2 {
	LIVEOBJ2_DRIVING=8,
	LIVEOBJ2_NONE=0,
	LIVEOBJ2_TRAINING=1024,
	LIVEOBJ2_UNK_1=1,
	LIVEOBJ2_UNK_10=16,
	LIVEOBJ2_UNK_100=256,
	LIVEOBJ2_UNK_10000=65536,
	LIVEOBJ2_UNK_100000=1048576,
	LIVEOBJ2_UNK_1000000=16777216,
	LIVEOBJ2_UNK_10000000=268435456,
	LIVEOBJ2_UNK_2=2,
	LIVEOBJ2_UNK_20=32,
	LIVEOBJ2_UNK_200=512,
	LIVEOBJ2_UNK_20000=131072,
	LIVEOBJ2_UNK_200000=2097152,
	LIVEOBJ2_UNK_2000000=33554432,
	LIVEOBJ2_UNK_20000000=536870912,
	LIVEOBJ2_UNK_4=4,
	LIVEOBJ2_UNK_40=64,
	LIVEOBJ2_UNK_4000=16384,
	LIVEOBJ2_UNK_40000=262144,
	LIVEOBJ2_UNK_400000=4194304,
	LIVEOBJ2_UNK_4000000=67108864,
	LIVEOBJ2_UNK_40000000=1073741824,
	LIVEOBJ2_UNK_800=2048,
	LIVEOBJ2_UNK_80000=524288,
	LIVEOBJ2_UNK_800000=8388608,
	LIVEOBJ2_UNK_8000000=134217728,
	LIVEOBJ2_UNK_80000000=2147483648,
	LIVEOBJ2_UPGRADING=32768
} LiveFlags2;

typedef enum LiveFlags3 {
	LIVEOBJ3_NONE=0,
	LIVEOBJ3_SIMPLEOBJECT=131072,
	LIVEOBJ3_UNK_100000=1048576,
	LIVEOBJ3_UNK_1000000=16777216,
	LIVEOBJ3_UNK_10000000=268435456,
	LIVEOBJ3_UNK_2000000=33554432,
	LIVEOBJ3_UNK_20000000=536870912,
	LIVEOBJ3_UNK_4000=16384,
	LIVEOBJ3_UNK_4000000=67108864,
	LIVEOBJ3_UNK_40000000=1073741824,
	LIVEOBJ3_UNK_80=128,
	LIVEOBJ3_UNK_80000=524288,
	LIVEOBJ3_UNK_800000=8388608,
	LIVEOBJ3_UNK_80000000=2147483648
} LiveFlags3;

typedef enum LiveFlags4 {
	LIVEOBJ4_CALLTOARMS_20=32,
	LIVEOBJ4_NONE=0,
	LIVEOBJ4_UNK_10=16,
	LIVEOBJ4_UNK_1000=4096,
	LIVEOBJ4_UNK_10000=65536,
	LIVEOBJ4_UNK_100000=1048576,
	LIVEOBJ4_UNK_2=2,
	LIVEOBJ4_UNK_2000=8192,
	LIVEOBJ4_UNK_20000=131072,
	LIVEOBJ4_UNK_200000=2097152,
	LIVEOBJ4_UNK_40=64,
	LIVEOBJ4_UNK_4000=16384,
	LIVEOBJ4_UNK_40000=262144,
	LIVEOBJ4_UNK_80=128,
	LIVEOBJ4_UNK_800=2048,
	LIVEOBJ4_UNK_8000=32768,
	LIVEOBJ4_UNK_80000=524288
} LiveFlags4;

typedef enum LiveFlags5 {
	LIVEOBJ5_NONE=0,
	LIVEOBJ5_UNK_8=8
} LiveFlags5;

typedef struct ObjectUpgradesData ObjectUpgradesData, *PObjectUpgradesData;

typedef struct PolyMeshData PolyMeshData, *PPolyMeshData;

typedef struct Size2F Size2F, *PSize2F;

typedef struct Coord2I Coord2I, *PCoord2I;

typedef struct SurfaceMapStruct38 SurfaceMapStruct38, *PSurfaceMapStruct38;

typedef enum AITaskType {
	AITASK_ANIMATIONWAIT=14,
	AITASK_ATTACKOBJECT=29,
	AITASK_ATTACKPATH=25,
	AITASK_ATTACKROCKMONSTER=26,
	AITASK_BIRDSCARER=20,
	AITASK_BUILDPATH=22,
	AITASK_CLEAR=12,
	AITASK_COLLECT=3,
	AITASK_DEPART=24,
	AITASK_DEPOSITE=5,
	AITASK_DIG=8,
	AITASK_DOCK=28,
	AITASK_DUMP=6,
	AITASK_DYNAMITE=9,
	AITASK_EAT=16,
	AITASK_ELECFENCE=15,
	AITASK_FINDDRIVER=18,
	AITASK_FINDLOAD=30,
	AITASK_FOLLOW=1,
	AITASK_FOLLOWATTACK=2,
	AITASK_GATHER=4,
	AITASK_GETTOOL=19,
	AITASK_GOTO=0,
	AITASK_GOTOEAT=17,
	AITASK_RECHARGE=27,
	AITASK_REINFORCE=11,
	AITASK_REPAIR=10,
	AITASK_REQUEST=7,
	AITASK_TRAIN=23,
	AITASK_UPGRADE=21,
	AITASK_WAIT=13,
	AITASK__INVALID=4294967295
} AITaskType;

typedef enum AIPriorityType {
	AIPRIORITY_ATTACKOBJECT=25,
	AIPRIORITY_ATTACKPATH=24,
	AIPRIORITY_ATTACKROCKMONSTER=15,
	AIPRIORITY_BARRIER=16,
	AIPRIORITY_BUILDPATH=14,
	AIPRIORITY_CLEARING=8,
	AIPRIORITY_CONGREGATE=26,
	AIPRIORITY_CONSTRUCTION=4,
	AIPRIORITY_CRYSTAL=0,
	AIPRIORITY_DEFAULTCOLLECT=2,
	AIPRIORITY_DEPART=23,
	AIPRIORITY_DESTRUCTION=3,
	AIPRIORITY_FINDLOAD=17,
	AIPRIORITY_GATHER=20,
	AIPRIORITY_GETIN=12,
	AIPRIORITY_HEALTHLOW=11,
	AIPRIORITY_ORE=1,
	AIPRIORITY_PUNCH=22,
	AIPRIORITY_RECHARGE=18,
	AIPRIORITY_REFINING=10,
	AIPRIORITY_REINFORCE=6,
	AIPRIORITY_REPAIR=7,
	AIPRIORITY_REQUEST=5,
	AIPRIORITY_STEAL=21,
	AIPRIORITY_STORAGE=9,
	AIPRIORITY_UPGRADE=13,
	AIPRIORITY_UPGRADEBUILDING=19,
	AIPRIORITY__INVALID=4294967295
} AIPriorityType;

typedef enum MessageType {
	MESSAGE_ATTACKBUILDING=37,
	MESSAGE_ATTACKBUILDING_COMPLETE=38,
	MESSAGE_BUILDPATH=48,
	MESSAGE_BUILDPATH_COMPLETE=49,
	MESSAGE_CLEAR=39,
	MESSAGE_CLEARBUILDING=58,
	MESSAGE_CLEARBUILDING_COMPLETE=59,
	MESSAGE_CLEARFALLIN=46,
	MESSAGE_CLEARFALLIN_COMPLETE=47,
	MESSAGE_CLEARINITIAL=60,
	MESSAGE_CLEARINITIAL_COMPLETE=61,
	MESSAGE_CLEARREMOVEPATH=62,
	MESSAGE_CLEARREMOVEPATH_COMPLETE=63,
	MESSAGE_CLEARSELECT=3,
	MESSAGE_CLEAR_COMPLETE=40,
	MESSAGE_COLLECTCRYSTAL=23,
	MESSAGE_COLLECTCRYSTAL_COMPLETE=24,
	MESSAGE_COLLECTORE=29,
	MESSAGE_COLLECTORE_COMPLETE=30,
	MESSAGE_COLLECTTOOL=44,
	MESSAGE_CRYSTALTOREFINERY=25,
	MESSAGE_CRYSTALTOREFINERY_COMPLETE=26,
	MESSAGE_DEBUG_DESTROYALL=64,
	MESSAGE_DESELECT=4,
	MESSAGE_DIG=13,
	MESSAGE_DIG_COMPLETE=14,
	MESSAGE_FIRSTPERSON=9,
	MESSAGE_FOLLOWATTACK=43,
	MESSAGE_GATHERROCK=33,
	MESSAGE_GATHERROCK_COMPLETE=34,
	MESSAGE_GENERATECRYSTAL=21,
	MESSAGE_GENERATECRYSTALANDORE=52,
	MESSAGE_GENERATECRYSTALANDORE_COMPLETE=53,
	MESSAGE_GENERATECRYSTAL_COMPLETE=22,
	MESSAGE_GENERATEFROMCRYORE=54,
	MESSAGE_GENERATEFROMCRYORE_COMPLETE=55,
	MESSAGE_GENERATEORE=27,
	MESSAGE_GENERATEORE_COMPLETE=28,
	MESSAGE_GENERATEROCKMONSTER=31,
	MESSAGE_GENERATEROCKMONSTER_COMPLETE=32,
	MESSAGE_GETIN=41,
	MESSAGE_GOTO=5,
	MESSAGE_MANSELECTEDANDMONSTERCLICKED=42,
	MESSAGE_NULL=0,
	MESSAGE_PICKRANDOMFLOOR=35,
	MESSAGE_PICKRANDOMFLOOR_COMPLETE=36,
	MESSAGE_PLAYSAMPLE=12,
	MESSAGE_REDUCESELECTION=45,
	MESSAGE_REINFORCE=17,
	MESSAGE_REINFORCE_COMPLETE=18,
	MESSAGE_REPAIR=15,
	MESSAGE_REPAIR_COMPLETE=16,
	MESSAGE_ROCKFALL=19,
	MESSAGE_ROCKFALL_COMPLETE=20,
	MESSAGE_ROCKMONSTERGOTO=6,
	MESSAGE_ROCKMONSTERGOTO_COMPLETE=7,
	MESSAGE_SELECT=1,
	MESSAGE_SELECTED=2,
	MESSAGE_TOPVIEW=11,
	MESSAGE_TRACKOBJECT=10,
	MESSAGE_TRAIN=50,
	MESSAGE_TRAIN_COMPLETE=51,
	MESSAGE_UPGRADE=56,
	MESSAGE_UPGRADE_COMPLETE=57,
	MESSAGE_USERGOTO=8,
	MESSAGE__INVALID=4294967295
} MessageType;

typedef struct FlockSubdata FlockSubdata, *PFlockSubdata;

typedef enum ObjectStatsFlags1 {
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
} ObjectStatsFlags1;

typedef enum ObjectStatsFlags2 {
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
} ObjectStatsFlags2;

typedef enum ObjectStatsFlags3 {
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
} ObjectStatsFlags3;

typedef struct ObjectUpgradePartData ObjectUpgradePartData, *PObjectUpgradePartData;

struct Point2F {
	float x;
	float y;
};

struct ColourRGBF {
	float red;
	float green;
	float blue;
};

struct GameManager {
	struct CFGProperty * LegoCfgRoot; // g_LegoCfgRoot
	char * CfgRootName; // g_CFG_ROOTPATH
	undefined4 field_8;
	undefined4 field_c;
	enum GraphicsQuality Quality; // g_GraphicsQuality
	struct LevelData * level; // g_LEVEL_STRUCTPTR_SIZE_284__005570d4
	struct Container * resRoot; // DAT_005570d8
	struct Viewport * viewMain; // Viewport area: (0.0,0.0 - 1.0x1.0)
	struct Viewport * viewRadar; // Viewport area: (16,14 - 151x151)
	struct CameraData * cameraMain; // PTR_005570e4
	struct CameraData * cameraRadar; // DAT_005570e8
	struct CameraData * cameraFP; // DAT_005570ec
	struct Container * resTopSpotlight; // PTR_005570f0
	struct Container * resTrackSpotlight; // DAT_005570f4
	struct Container * resFPLight; // PTR_005570f8
	struct Container * resFPRotLight; // PTR_005570fc
	struct Container * resAmbientLight; // PTR_00557100
	struct Container * resRootSpotlight; // PTR_00557104
	struct Container * resRootLight; // PTR_00557108
	struct Container * resFPRotLightDefault; // PTR_0055710c
	float FPClipBlocks; // FLOAT_00557110
	float TVClipDist; // g_tvclipdist
	undefined4 field_58;
	undefined4 field_5c;
	undefined4 field_60;
	struct ImageFont * bmpFONT5_HI; // g_FONT_FONT5_HI
	struct ImageFont * bmpToolTipFont; // g_FONT_ToolTipFont
	struct ImageFont * bmpDeskTopFont; // g_FONT_DeskTopFont
	struct ImageFont * bmpfont5_HI; // g_FONT_font5_HI
	struct ImageFont * bmpMbriefFONT; // g_FONT_MbriefFONT
	struct ImageFont * bmpMbriefFONT2; // g_FONT_MbriefFONT2
	struct ImageFont * bmpRSFont; // g_FONT_RSFont
	struct TextWindow * textWnd_80; // PTR_00557140
	struct TextWindow * textWnd_84; // PTR_00557144
	struct Point2F pointf_88; // FLOAT_00557148
	struct Point2F pointf_90; // FLOAT_00557150
	BOOL bool_98; // BOOL_00557158
	float gameSpeed; // FLOAT_0055715c
	struct LiveObject * objectFP; // DAT_00557160
	float float_a4; // FLOAT_00557164
	float float_a8; // FLOAT_00557168
	float float_ac; // FLOAT_0055716c
	float float_b0; // FLOAT_00557170
	float float_b4; // FLOAT_00557174
	float float_b8; // FLOAT_00557178
	float float_bc; // FLOAT_0055717c
	struct Point2I pointi_c0; // DAT_00557180
	BOOL bool_c8; // DAT_00557188
	char * ObjectNames_PowerCrystal; // g_ObjectNames_PowerCrystal
	char * ObjectNames_Ore; // g_ObjectNames_Ore
	char * ObjectNames_ProcessedOre; // g_ObjectNames_ProcessedOre
	char * ObjectNames_Dynamite; // g_ObjectNames_Dynamite
	char * ObjectNames_Barrier; // g_ObjectNames_Barrier
	char * ObjectNames_ElectricFence; // g_ObjectNames_ElectricFence
	char * ObjectNames_SpiderWeb; // g_ObjectNames_SpiderWeb
	char * ObjectNames_OohScary; // g_ObjectNames_OohScary
	char * ObjectNames_Path; // g_ObjectNames_Path
	char * ObjectTheNames_PowerCrystal; // g_ObjectTheNames_PowerCrystal
	char * ObjectTheNames_Ore; // g_ObjectTheNames_Ore
	char * ObjectTheNames_ProcessedOre; // g_ObjectTheNames_ProcessedOre
	char * ObjectTheNames_Dynamite; // g_ObjectTheNames_Dynamite
	char * ObjectTheNames_Barrier; // g_ObjectTheNames_Barrier
	char * ObjectTheNames_ElectricFence; // g_ObjectTheNames_ElectricFence
	char * ObjectTheNames_SpiderWeb; // g_ObjectTheNames_SpiderWeb
	char * ObjectTheNames_OohScary; // g_ObjectTheNames_OohScary
	char * ObjectTheNames_Path; // g_ObjectTheNames_Path
	struct VehicleData * VehicleData_TABLE; // g_VehicleData_TABLE
	struct CreatureData * MiniFigureData_TABLE; // g_MiniFigureData_TABLE
	struct CreatureData * RockMonsterData_TABLE; // g_RockMonsterData_TABLE
	struct BuildingData * BuildingData_TABLE; // g_BuildingData_TABLE
	struct UpgradeData * UpgradeData_TABLE; // g_UpgradeData_TABLE
	char * * VehicleTypes_TABLE; // g_VehicleTypes_TABLE
	char * * MiniFigureTypes_TABLE; // g_MiniFigureTypes_TABLE
	char * * RockMonsterTypes_TABLE; // g_RockMonsterTypes_TABLE
	char * * BuildingTypes_TABLE; // g_BuildingTypes_TABLE
	char * * UpgradeTypes_TABLE; // g_UpgradeTypes_TABLE
	char * ToolTypes_TABLE[11]; // g_ToolTypes_TABLE
	char * ToolNames_TABLE[11]; // g_ToolNames_TABLE
	char * * ObjectNames_VehicleTypes_TABLE; // g_ObjectNames_VehicleTypes_TABLE
	char * * ObjectNames_MiniFigureTypes_TABLE; // g_ObjectNames_MiniFigureTypes_TABLE
	char * * ObjectNames_RockMonsterTypes_TABLE; // g_ObjectNames_RockMonsterTypes_TABLE
	char * * ObjectNames_BuildingTypes_TABLE; // g_ObjectNames_BuildingTypes_TABLE
	char * * ObjectNames_UpgradeTypes_TABLE; // g_ObjectNames_UpgradeTypes_TABLE
	char * * ObjectTheNames_VehicleTypes_TABLE; // g_ObjectTheNames_VehicleTypes_TABLE
	char * * ObjectTheNames_MiniFigureTypes_TABLE; // g_ObjectTheNames_MiniFigureTypes_TABLE
	char * * ObjectTheNames_RockMonsterTypes_TABLE; // g_ObjectTheNames_RockMonsterTypes_TABLE
	char * * ObjectTheNames_BuildingTypes_TABLE; // g_ObjectTheNames_BuildingTypes_TABLE
	char * * ObjectTheNames_UpgradeTypes_TABLE; // g_ObjectTheNames_UpgradeTypes_TABLE
	uint VehicleTypes_COUNT; // g_VehicleTypes_COUNT
	uint MiniFigureTypes_COUNT; // g_MiniFigureTypes_COUNT
	uint RockMonsterTypes_COUNT; // g_RockMonsterTypes_COUNT
	uint BuildingTypes_COUNT; // g_BuildingTypes_COUNT
	uint UpgradeTypes_COUNT; // g_UpgradeTypes_COUNT
	char * SurfaceTypes_TABLE[18]; // g_SurfaceTypes_TABLE
	char * SurfaceTypeDescriptions_name_TABLE[18]; // g_SurfaceTypeDescriptions_name_TABLE
	void * SurfaceTypeDescriptions_sound_TABLE[18]; // g_SurfaceTypeDescriptions_sound_TABLE
	struct Container * RES_Boulder; // g_RES_BOULDER
	struct Container * RES_BoulderExplode; // DAT_0055736c
	struct Container * RES_BoulderExplodeIce; // DAT_00557370
	struct Container * RES_Crystal; // g_RES_POWERCRYSTAL
	struct Container * RES_Dynamite; // g_RES_DYNAMITE
	struct Container * RES_Ores_TABLE[2]; // g_RES_ORES_TABLE
	struct Container * RES_OohScary; // g_RES_OOHSCARY
	struct Container * RES_Barrier; // g_RES_BARRIER
	struct Container * RES_ElectricFence; // g_RES_ELECTRICFENCE
	struct Container * RES_SpiderWeb; // g_RES_SPIDERWEB
	struct Container * RES_RechargeSparkle; // DAT_00557394
	struct Container * RES_MiniTeleportUp; // DAT_00557398
	struct Container * RES_ElectricFenceStud; // DAT_0055739c
	struct Container * RES_Pusher; // g_RES_PUSHER
	struct Container * RES_Freezer; // g_RES_FREEZER
	struct Container * RES_IceCube; // DAT_005573a8
	struct Container * RES_SmashPath; // DAT_005573ac
	struct Container * RES_LaserShot; // g_RES_LASERSHOT
	struct Container * * RES_2f4_TABLEUNK; // DAT_005573b4
	undefined4 table10_2f8[10]; // g_UNK_TABLE__005573b8
	uint count10_320; // UINT_005573e0
	float float_324; // FLOAT_005573e4
	float float_328; // FLOAT_005573e8
	float float_32c; // FLOAT_005573ec
	float float_330; // FLOAT_005573f0
	float tvTiltOrZoom_334;
	struct Point2F tvFaceDirection_338;
	float MedPolyRange; // g_MedPolyRange
	float HighPolyRange; // g_HighPolyRange
	int HPBlocks; // g_HPBlocks
	struct ColourRGBF FogColourRGB; // g_FogColourRGB
	struct ColourRGBF HighFogColourRGB; // g_HighFogColourRGB
	float float_364; // g_LEVEL_UNK_FLOAT_00557424
	struct ColourRGBF PowerCrystalRGB; // g_PowerCrystalRGB
	struct ColourRGBF UnpoweredCrystalRGB; // g_UnpoweredCrystalRGB
	enum ObjectType placeObjType; // INT_00557440
	int placeObjIndex; // INT_00557444
	enum Direction placeObjDirection; // INT_00557448
	struct LiveObject * placeDestSmallTeleporter; // PTR_0055744c
	struct LiveObject * placeDestBigTeleporter; // PTR_00557450
	struct LiveObject * placeDestWaterTeleporter; // PTR_00557454
	float MinEnergyForEat; // g_MinEnergyForEat
	struct ImageBMP * TutorialIcon; // bmp? PTR_0055745c
	undefined4 field_3a0;
	float DynamiteDamageRadius; // g_DynamiteDamageRadius
	float DynamiteMaxDamage; // g_DynamiteMaxDamage
	float DynamiteWakeRadius; // g_DynamiteWakeRadius
	float BirdScarerRadius; // g_BirdScarerRadius
	enum ObjectType objTeleportQueueTypes_TABLE[20]; // UNK_ARRAY_00557474
	int objTeleportQueueIndexes_TABLE[20]; // UNK_ARRAY_005574c4
	uint objTeleportQueue_COUNT; // count for above 2 arrays, UINT_00557514
	float MiniFigureRunAway; // g_MiniFigureRunAway
	struct Vector3F vector_45c; // FLOAT_0055751c
	undefined4 table200_468[200]; // UNK_ARRAY_00557528
	uint count_788; // UINT_00557848
	struct Point2I points2x100_78c[2][100]; // UNK_ARRAY_0055784c
	uint pointsCount2_dcc[2]; // UINT_00557e8c
	uint MaxReturnedCrystals; // g_MaxReturnedCrystals
	uint MouseScrollBorder; // g_MouseScrollBorder
	char * HealthText; // g_HealthText
	char * EnergyText; // g_EnergyText
	char * CrystalsText; // g_CrystalsText
	char * OreText; // g_OreText
	char * StudsText; // g_StudsText
	char * ToolsText; // g_ToolsText
	char * CarryObjectText; // g_CarryObjectText
	char * DrivenByText; // g_DrivenByText
	char * OreRequiredText; // g_OreRequiredText
	BOOL IsFallinsEnabled; // (! "NoFallins"), g_YesFallins
	float MinDistFor3DSoundsOnTopView; // g_MinDistFor3DSoundsOnTopView
	enum ViewMode viewMode; // (may not be bool, compared with 0, and 1) g_GAME_UNK_BOOL_00557ec8
	enum GameFlags1 flags1; // g_GAME_GameFlags1
	enum GameFlags2 flags2; // g_GAME_GameFlags2
	enum GameFlags3 flags3; // only first byte is used(?), g_GAME_GameFlags3
	float InitialSlugTime; // g_InitialSlugTime
	struct Point2F NextButtonPos; // g_NextButton
	struct Point2F BackButtonPos; // g_BackButtonPos
	struct ImageBMP * NextButton; // bmp? PTR_00557eec
	struct ImageBMP * BackButton; // bmp? PTR_00557ef0
	struct ImageBMP * BackArrow; // bmp? PTR_00557ef4
	float FogRate; // g_LEVEL_FogRate
	float timerGame_e3c; // FLOAT_00557efc
	float elapsedAbs; // assigned to Game_Update param_1 float fpsSync, FLOAT_00557f00
	float DrainTime; // g_DrainTime
	uint ReinforceHits; // g_ReinforceHits
	uint CDStartTrack; // g_CDStartTrack
	uint CDTracks; // g_CDTracks
	uint FallinMultiplier; // g_LEVEL_FallinMultiplier
	BOOL hasFallins; // BOOL_00557f18
	struct Point2F menuNextPoint; // DAT_00557f1c
	struct Point2F menuPrevPoint; // DAT_00557f24
	struct ColourRGBF DragBoxRGB; // g_DragBoxRGB
	struct ImageBMP * DialogImage; // PTR_00557f38
	struct ImageBMP * DialogContrastOverlay; // PTR_00557f3c
	void * drawregion_e80; // PTR_00557f40
	void * drawregion_e84; // PTR_00557f44
	void * drawregion_e88; // PTR_00557f48
	void * drawregion_e8c; // PTR_00557f4c
	char * CreditsTextFile; // g_CreditsTextFile
	char * CreditsBackAVI; // g_CreditsBackAVI
	char * UpgradeNames_TABLE[16]; // g_UpgradeNames_TABLE
	int BuildingUpgradeCostOre; // g_BuildingUpgradeCostOre
	int BuildingUpgradeCostStuds; // g_BuildingUpgradeCostStuds
	char * renameInput;
	struct Point2F renamePosition;
	char * RenameReplace; // g_RenameReplace
	char * EndGameAVI1; // g_EndGameAVI1
	char * EndGameAVI2; // g_EndGameAVI2
};

struct Rect2F {
	float x;
	float y;
	float width;
	float height;
};

struct LevelStruct_3c {
	struct SurfaceMap * surfMap;
	struct Rect2F rectf_4;
	float float_14;
	float float_18;
	float float_1c;
	float float_20;
	undefined4 field_24;
	undefined4 field_28;
	undefined4 field_2c;
	undefined4 field_30;
	undefined4 field_34;
	undefined4 field_38;
};

struct SurfaceMapStruct38 {
	undefined4 field_0;
	float float_4;
	undefined4 field_8;
	undefined4 field_c;
	undefined4 table_10[8];
	undefined field_0x30;
	undefined field_0x31;
	undefined field_0x32;
	undefined field_0x33;
	uint flags;
};

struct LiveObject {
	enum ObjectType objType;
	int objIndex;
	char * customName; // max size is 11 (NOT null-terminated)
	struct VehicleData * vehicle;
	struct CreatureData * miniFigure;
	struct CreatureData * rockMonster;
	struct BuildingData * building;
	struct Container * other;
	struct UpgradeData * upgrade;
	void * routeptr_24; // Unknown pointer, likely in large allocated table
	uint routingBlocksTotal; // total blocks to travel for current route
	uint routingBlocksCurrent; // number of blocks traveled (up to routingBlocksTotal)
	int value_30; // Usually 50 (0x32)
	float floats_34[100];
	float floats_1c4[50];
	struct Vector3F vector_28c;
	struct Point2F point_298;
	struct Vector3F vector_2a0;
	struct Vector3F faceDirection; // 1.0 to -1.0 directions that determine rotation with atan2
	float float_2b8;
	int strafeSpeed_2bc;
	int forwardSpeed_2c0;
	float rotateSpeed_2c4;
	undefined4 field_2c8;
	undefined4 field_2cc;
	undefined4 field_2d0;
	float float_2d4;
	BOOL unkbool_2d8;
	struct Container * resData_2dc;
	int index_2e0;
	struct Container * resData_2e4;
	char * aitaskName1;
	char * aitaskName2;
	struct AITaskData * aitask_2f0;
	struct Point2F point_2f4; // (assigned -1.0f)
	struct LiveObject * object_2fc; // other half of object_300
	struct LiveObject * object_300; // other half of object_2fc
	struct LiveObject * carryingThisObject;
	struct LiveObject * carriedObjects[7];
	uint numCarriedObjects;
	uint field_328;
	struct FlockData * flocksData_32c;
	uint objLevel;
	struct ObjectStats * stats;
	float float_338;
	float float_33c;
	float health; // (assigned -1.0f)
	float energy; // (assigned -1.0f)
	int * tableptr_348; // element size is 0x4
	BOOL mode_34c;
	undefined4 field_350;
	undefined4 field_354;
	undefined4 field_358;
	undefined4 field_35c;
	undefined4 field_360;
	struct LiveObject * object_364;
	float float_368;
	struct LiveObject * drivenObject; // same as drivingThisObject
	enum ToolType carriedTools[5];
	uint numCarriedTools;
	undefined4 field_388;
	struct ImageBMP * bubbleImage_38c;
	undefined4 field_390;
	undefined4 field_394;
	undefined4 field_398;
	undefined4 field_39c;
	undefined4 field_3a0;
	undefined4 field_3a4;
	undefined4 field_3a8;
	undefined4 field_3ac;
	undefined4 field_3b0;
	struct Vector3F vector_3b4;
	struct LiveObject * object_3c0;
	undefined4 field_3c4;
	undefined4 field_3c8;
	struct LiveObject * object_3cc;
	undefined4 field_3d0;
	float elapsedTime1; // elapsed time counter 1
	float elapsedTime2; // elapsed time counter 2
	float activityElapsedTime; // elapsed time since last order?
	enum LiveFlags1 flags1;
	enum LiveFlags2 flags2;
	enum LiveFlags3 flags3; // (assigned 0, flags?)
	enum LiveFlags4 flags4;
	enum LiveFlags5 flags5_3f0; // (assigned 0, flags?)
	undefined4 field_3f4;
	undefined4 field_3f8;
	float floatSnd_3fc;
	float floatSnd_400;
	undefined4 field_404;
	struct LiveObject * pool_m_next;
};

struct Coord2I { // Point2I structure using short-sized integers (name is based off the WINAPI console structure COORD, using the same ,layout)
	short sx;
	short sy;
};

struct Size2F {
	float width;
	float height;
};

struct Size2I {
	int width;
	int height;
};

struct SurfaceTextureGrid {
	struct Size2I gridSize;
	struct Container_Texture * * gridSurfaces;
};

struct ObjectiveData {
	struct ImageBMP * ObjectiveImage; // bmp
	struct Point2F ObjectiveImagePosition;
	struct ImageBMP * ObjectiveAcheivedImage; // bmp
	struct Point2F ObjectiveAcheivedImagePosition;
	struct ImageBMP * ObjectiveFailedImage; // bmp
	struct Point2F ObjectiveFailedImagePosition;
	char * ObjectiveAcheivedAVIFilename; // filename
	struct Point2F ObjectiveAcheivedAVIPosition;
	undefined4 field_30;
	undefined4 field_34;
	int CrystalObjective; // number of crystals needed if non-zero
	int OreObjective; // number of ore needed if non-zero
	struct Point2I BlockObjective;
	float TimerObjective; // (mult: 25.0, flags, format: "time:HitTimeFailObjective")
	enum ObjectType ConstructionObjectiveObjType;
	int ConstructionObjectiveObjIndex;
};

struct LevelData {
	char * levelName; // (format: "Levels::level")
	struct SurfaceMap * surfaceMap;
	void * ptrtable_8;
	uint count_c;
	undefined4 field_10;
	struct Size2I dimensions;
	float BlockSize;
	float DigDepth;
	float RoofHeight;
	float RoughLevel;
	enum BOOL3 UseRoof;
	enum BOOL3 SafeCaverns;
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
	struct Size2I surfTextSize; // surface texture width and height
	struct SurfaceTextureGrid * surfTextGrid;
	undefined4 field_0x80;
	struct LevelStruct_3c * struct3c_84;
	struct LevelStruct_1c * terrain1c_88;
	int numCrystals; // (init: 0)
	undefined4 field_90; // (init: 0)
	undefined4 field_94; // (init: 0)
	int numDrainedCrystals; // assumption
	undefined4 field_9c;
	int numOre; // (init: 0)
	undefined4 field_a4; // (init: 0)
	undefined4 field_a8; // (init: 0)
	int numProcessedOre;
	int EmergeCreature; // (searches for object index by name, expects RockMonsterType)
	char * NextLevel;
	struct LevelBlock * blocks; // grid of blocks [y][x]
	struct ObjectiveData objective;
	BOOL hasBlockPointers;
	struct BlockPointer * blockPointers[56];
	BOOL StartFP;
	BOOL NoDrain;
	float oxygenLevel; // (init: 100.0, Oxygen level?)
	float OxygenRate;
	float float_204; // (init: 100.0, Oxygen level?)
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
	enum LevelCompleteStatus status; // (init: 0) 2 is used for Crystal failure as well
	BOOL IsStartTeleportEnabled; // (! DisableStartTeleport)
};

struct BlockPointer {
	struct Point2I position;
	uint id;
};

struct AITaskData {
	enum AITaskType taskType;
	undefined4 field_4;
	struct Point2I position;
	struct LiveObject * object_10;
	float unkExpiryTime;
	float float_18;
	uint priorityValue;
	enum ObjectType objType;
	int objIndex;
	int objLevel;
	undefined4 field_2c;
	struct Point2F pointf_30; // probably a table
	enum ToolType toolType;
	undefined4 mode_3c;
	void * ptr_40;
	undefined4 field_44;
	struct LiveObject * object_48;
	enum AIPriorityType priorityType;
	uint taskStartTime;
	enum MessageType completeAction;
	struct AITaskData * aiTask_58;
	uint flags_5c; // not set means ptr_40 is assigned
	struct AITaskData * next; // assigned to DAT_004b4358
	struct AITaskData * pool_m_next;
};

struct CreatureData {
	int objIndex;
	struct Container * aeResData; // ACT, true
	undefined4 field_8;
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
	undefined field_0x18;
	undefined field_0x19;
	undefined field_0x1a;
	undefined field_0x1b;
	undefined field_0x1c;
	undefined field_0x1d;
	undefined field_0x1e;
	undefined field_0x1f;
	char * CameraNullName;
	uint CameraNullFrames;
	enum BOOL3 CameraFlipDir;
	char * DrillNullName;
	char * FootStepNullName;
	char * CarryNullName;
	char * ThrowNullName;
	char * DepositNullName;
	undefined4 field_40;
	undefined4 field_44;
	struct Container * resData_48;
	undefined4 field_4c;
	undefined4 field_50;
	undefined4 cameraFramesTable_54[4];
	struct PolyMeshData * subdata_64;
	struct PolyMeshData * subdata_68;
	struct PolyMeshData * subdata_6c;
	uint flags;
};

struct ObjectStats {
	undefined4 field_0;
	undefined4 field_4;
	undefined4 field_8;
	undefined4 field_c;
	undefined4 field_10;
	undefined4 field_14;
	undefined4 field_18;
	undefined4 field_1c;
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
	int DrillSound; // (from: FUN_00464f30, invalid: 2 "SFX_Drill")
	int DrillFadeSound; // (from: FUN_00464f30, invalid: 3 "SFX_DrillFade")
	int EngineSound; // (from: FUN_00464f30, invalid: 0 "SFX_Bodge")
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
	undefined4 field_104;
	undefined4 field_108;
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
	enum ObjectStatsFlags1 flags1;
	enum ObjectStatsFlags2 flags2;
	enum ObjectStatsFlags3 flags3;
};

struct ObjectUpgradePartData {
	uint level;
	int NullInstance;
	char * NullObjectName;
	char * WeaponName;
	struct UpgradeData * upgradeData;
};

struct CFGProperty { // CFG file property node
	char * fileData; // Entire file text data for root CFGProperty only
	char * key; // Property or block key name
	char * value; // Property value or block open brace
	uint depth; // Block-depth of property
	uint itemHashCode; // Hash of item (unused)
	struct CFGProperty * linkNext; // Next property in linked list
	struct CFGProperty * linkPrev; // Previous property in linked list
	struct CFGProperty * nextFree; // (internal) used for allocation while reading(?)
};

struct ObjectUpgradesData {
	struct ObjectUpgradePartData * parts; // always ObjectUpgradePartData[200]
	uint count;
	int currentLevel;
	uint levelsMask; // [carry][scan][speed][drill]
	struct LiveObject * * upgradeObjs;
};

struct BuildingData {
	int objIndex;
	struct Container * aeResData; // ACT, true
	char * CarryNullName;
	char * CameraNullName;
	char * DepositNullName;
	char * EntranceNullName;
	char * ToolNullName;
	char * FireNullName; // "fire laser"
	char * yPivot;
	char * xPivot;
	undefined4 carryFramesTable_28[6];
	undefined4 cameraFramesTable_40[4];
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
	undefined4 field_68;
	undefined4 field_6c;
	uint CarryNullFrames;
	uint CameraNullFrames;
	uint ToolNullFrames;
	struct Container * PowerLevelScene; // LWS, true
	undefined4 field_80;
	struct Point2I * shapePoints; // Point2I[10]
	uint shapeCount;
	struct ObjectUpgradesData upgrades;
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
	float PivotMaxZ;
	float PivotMinZ;
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
	uint count_144;
	uint flags;
};

struct VehicleData {
	int objIndex;
	char * WheelNullName;
	struct Container * aeResData1;
	struct Container * aeResData2; // Optional second ae file (seen for Grannit Grinder legs)
	struct Container * WheelMeshes[6]; // LWO, false
	undefined4 wheel_fields_28[6];
	uint numWheelNulls;
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
	undefined4 field_5c;
	undefined4 field_60;
	float float_64;
	float WheelRadius;
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
	char * DrillNullName;
	char * DepositNullName;
	char * FireNullName; // "fire laser"
	char * DriverNullName;
	char * yPivot;
	char * xPivot;
	undefined4 field_cc;
	undefined4 field_d0;
	struct Container * resData_d4;
	enum BOOL3 CameraFlipDir;
	char * CarryNullName;
	char * CameraNullName;
	undefined4 carryFramesTable_e4[7];
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
	undefined4 cameraFramesTable_10c[4];
	uint CarryNullFrames;
	uint CameraNullFrames;
	struct ObjectUpgradesData upgrades;
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
	float PivotMaxZ;
	float PivotMinZ;
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
	undefined4 table6_1c4[6];
	undefined4 field_1dc;
	struct PolyMeshData * subdata_1e0;
	struct PolyMeshData * subdata_1e4;
	uint flags; // HoldMissing TRUE -> 0x8
};

struct Range2F {
	float min;
	float max;
};

struct UpgradeData {
	int objectIndex;
	struct Container * aeResData; // ACT, true
	struct LiveObject * object_8;
	undefined4 field_c;
};

struct ImageFont {
	struct ImageBMP * bitmap;
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
	undefined field_0x18;
	undefined field_0x19;
	undefined field_0x1a;
	undefined field_0x1b;
	undefined field_0x1c;
	undefined field_0x1d;
	undefined field_0x1e;
	undefined field_0x1f;
	undefined field_0x20;
	undefined field_0x21;
	undefined field_0x22;
	undefined field_0x23;
	undefined field_0x24;
	undefined field_0x25;
	undefined field_0x26;
	undefined field_0x27;
	undefined field_0x28;
	undefined field_0x29;
	undefined field_0x2a;
	undefined field_0x2b;
	undefined field_0x2c;
	undefined field_0x2d;
	undefined field_0x2e;
	undefined field_0x2f;
	undefined field_0x30;
	undefined field_0x31;
	undefined field_0x32;
	undefined field_0x33;
	undefined field_0x34;
	undefined field_0x35;
	undefined field_0x36;
	undefined field_0x37;
	undefined field_0x38;
	undefined field_0x39;
	undefined field_0x3a;
	undefined field_0x3b;
	undefined field_0x3c;
	undefined field_0x3d;
	undefined field_0x3e;
	undefined field_0x3f;
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
	undefined4 field_be4;
	undefined field_0xbe8;
	undefined field_0xbe9;
	undefined field_0xbea;
	undefined field_0xbeb;
	undefined field_0xbec;
	undefined field_0xbed;
	undefined field_0xbee;
	undefined field_0xbef;
	struct ImageFont * pool_m_next;
};

struct FlockData {
	struct FlockSubdata * flocksSubdata1;
	struct FlockSubdata * flocksSubdata2;
	uint numSubdata;
	uint hasVector1;
	uint hasVector2;
	undefined4 field_14;
	undefined4 field_18;
	undefined4 field_1c;
	undefined4 field_20;
	undefined4 field_24;
};

struct SurfaceMap { // size 0x73d4... dear god.... no...
	struct Size2I smallDimensions; // full map dimensions - 1
	struct Size2I dimensions; // full map dimensions
	float BlockSize;
	float RoughLevel;
	struct Size2F blockDimensions_neg; // smallDimensions * BlockSize * 0.5 (width is negative??)
	float float_20;
	struct Container * resData_24;
	undefined4 field_28;
	undefined4 field_2c;
	undefined4 unkMaterialData_30; // Material related
	byte texsGrid[128][128];
	byte texsNum[128];
	undefined4 flat_40b4[128];
	struct Coord2I coordsTable[500];
	uint coordsNum;
	undefined field_0x4a88;
	undefined field_0x4a89;
	undefined field_0x4a8a;
	undefined field_0x4a8b;
	undefined field_0x4a8c;
	undefined field_0x4a8d;
	undefined field_0x4a8e;
	undefined field_0x4a8f;
	undefined field_0x4a90;
	undefined field_0x4a91;
	undefined field_0x4a92;
	undefined field_0x4a93;
	undefined field_0x4a94;
	undefined field_0x4a95;
	undefined field_0x4a96;
	undefined field_0x4a97;
	undefined field_0x4a98;
	undefined field_0x4a99;
	undefined field_0x4a9a;
	undefined field_0x4a9b;
	undefined field_0x4a9c;
	undefined field_0x4a9d;
	undefined field_0x4a9e;
	undefined field_0x4a9f;
	undefined field_0x4aa0;
	undefined field_0x4aa1;
	undefined field_0x4aa2;
	undefined field_0x4aa3;
	undefined field_0x4aa4;
	undefined field_0x4aa5;
	undefined field_0x4aa6;
	undefined field_0x4aa7;
	undefined field_0x4aa8;
	undefined field_0x4aa9;
	undefined field_0x4aaa;
	undefined field_0x4aab;
	undefined field_0x4aac;
	undefined field_0x4aad;
	undefined field_0x4aae;
	undefined field_0x4aaf;
	undefined field_0x4ab0;
	undefined field_0x4ab1;
	undefined field_0x4ab2;
	undefined field_0x4ab3;
	undefined field_0x4ab4;
	undefined field_0x4ab5;
	undefined field_0x4ab6;
	undefined field_0x4ab7;
	undefined field_0x4ab8;
	undefined field_0x4ab9;
	undefined field_0x4aba;
	undefined field_0x4abb;
	undefined field_0x4abc;
	undefined field_0x4abd;
	undefined field_0x4abe;
	undefined field_0x4abf;
	undefined field_0x4ac0;
	undefined field_0x4ac1;
	undefined field_0x4ac2;
	undefined field_0x4ac3;
	undefined field_0x4ac4;
	undefined field_0x4ac5;
	undefined field_0x4ac6;
	undefined field_0x4ac7;
	undefined field_0x4ac8;
	undefined field_0x4ac9;
	undefined field_0x4aca;
	undefined field_0x4acb;
	undefined field_0x4acc;
	undefined field_0x4acd;
	undefined field_0x4ace;
	undefined field_0x4acf;
	undefined field_0x4ad0;
	undefined field_0x4ad1;
	undefined field_0x4ad2;
	undefined field_0x4ad3;
	undefined field_0x4ad4;
	undefined field_0x4ad5;
	undefined field_0x4ad6;
	undefined field_0x4ad7;
	undefined field_0x4ad8;
	undefined field_0x4ad9;
	undefined field_0x4ada;
	undefined field_0x4adb;
	undefined field_0x4adc;
	undefined field_0x4add;
	undefined field_0x4ade;
	undefined field_0x4adf;
	undefined field_0x4ae0;
	undefined field_0x4ae1;
	undefined field_0x4ae2;
	undefined field_0x4ae3;
	undefined field_0x4ae4;
	undefined field_0x4ae5;
	undefined field_0x4ae6;
	undefined field_0x4ae7;
	undefined field_0x4ae8;
	undefined field_0x4ae9;
	undefined field_0x4aea;
	undefined field_0x4aeb;
	undefined field_0x4aec;
	undefined field_0x4aed;
	undefined field_0x4aee;
	undefined field_0x4aef;
	undefined field_0x4af0;
	undefined field_0x4af1;
	undefined field_0x4af2;
	undefined field_0x4af3;
	undefined field_0x4af4;
	undefined field_0x4af5;
	undefined field_0x4af6;
	undefined field_0x4af7;
	undefined field_0x4af8;
	undefined field_0x4af9;
	undefined field_0x4afa;
	undefined field_0x4afb;
	undefined field_0x4afc;
	undefined field_0x4afd;
	undefined field_0x4afe;
	undefined field_0x4aff;
	undefined field_0x4b00;
	undefined field_0x4b01;
	undefined field_0x4b02;
	undefined field_0x4b03;
	undefined field_0x4b04;
	undefined field_0x4b05;
	undefined field_0x4b06;
	undefined field_0x4b07;
	undefined field_0x4b08;
	undefined field_0x4b09;
	undefined field_0x4b0a;
	undefined field_0x4b0b;
	undefined field_0x4b0c;
	undefined field_0x4b0d;
	undefined field_0x4b0e;
	undefined field_0x4b0f;
	undefined field_0x4b10;
	undefined field_0x4b11;
	undefined field_0x4b12;
	undefined field_0x4b13;
	undefined field_0x4b14;
	undefined field_0x4b15;
	undefined field_0x4b16;
	undefined field_0x4b17;
	undefined field_0x4b18;
	undefined field_0x4b19;
	undefined field_0x4b1a;
	undefined field_0x4b1b;
	undefined field_0x4b1c;
	undefined field_0x4b1d;
	undefined field_0x4b1e;
	undefined field_0x4b1f;
	undefined field_0x4b20;
	undefined field_0x4b21;
	undefined field_0x4b22;
	undefined field_0x4b23;
	undefined field_0x4b24;
	undefined field_0x4b25;
	undefined field_0x4b26;
	undefined field_0x4b27;
	undefined field_0x4b28;
	undefined field_0x4b29;
	undefined field_0x4b2a;
	undefined field_0x4b2b;
	undefined field_0x4b2c;
	undefined field_0x4b2d;
	undefined field_0x4b2e;
	undefined field_0x4b2f;
	undefined field_0x4b30;
	undefined field_0x4b31;
	undefined field_0x4b32;
	undefined field_0x4b33;
	undefined field_0x4b34;
	undefined field_0x4b35;
	undefined field_0x4b36;
	undefined field_0x4b37;
	undefined field_0x4b38;
	undefined field_0x4b39;
	undefined field_0x4b3a;
	undefined field_0x4b3b;
	undefined field_0x4b3c;
	undefined field_0x4b3d;
	undefined field_0x4b3e;
	undefined field_0x4b3f;
	undefined field_0x4b40;
	undefined field_0x4b41;
	undefined field_0x4b42;
	undefined field_0x4b43;
	undefined field_0x4b44;
	undefined field_0x4b45;
	undefined field_0x4b46;
	undefined field_0x4b47;
	undefined field_0x4b48;
	undefined field_0x4b49;
	undefined field_0x4b4a;
	undefined field_0x4b4b;
	undefined field_0x4b4c;
	undefined field_0x4b4d;
	undefined field_0x4b4e;
	undefined field_0x4b4f;
	undefined field_0x4b50;
	undefined field_0x4b51;
	undefined field_0x4b52;
	undefined field_0x4b53;
	undefined field_0x4b54;
	undefined field_0x4b55;
	undefined field_0x4b56;
	undefined field_0x4b57;
	undefined field_0x4b58;
	undefined field_0x4b59;
	undefined field_0x4b5a;
	undefined field_0x4b5b;
	undefined field_0x4b5c;
	undefined field_0x4b5d;
	undefined field_0x4b5e;
	undefined field_0x4b5f;
	undefined field_0x4b60;
	undefined field_0x4b61;
	undefined field_0x4b62;
	undefined field_0x4b63;
	undefined field_0x4b64;
	undefined field_0x4b65;
	undefined field_0x4b66;
	undefined field_0x4b67;
	undefined field_0x4b68;
	undefined field_0x4b69;
	undefined field_0x4b6a;
	undefined field_0x4b6b;
	undefined field_0x4b6c;
	undefined field_0x4b6d;
	undefined field_0x4b6e;
	undefined field_0x4b6f;
	undefined field_0x4b70;
	undefined field_0x4b71;
	undefined field_0x4b72;
	undefined field_0x4b73;
	undefined field_0x4b74;
	undefined field_0x4b75;
	undefined field_0x4b76;
	undefined field_0x4b77;
	undefined field_0x4b78;
	undefined field_0x4b79;
	undefined field_0x4b7a;
	undefined field_0x4b7b;
	undefined field_0x4b7c;
	undefined field_0x4b7d;
	undefined field_0x4b7e;
	undefined field_0x4b7f;
	undefined field_0x4b80;
	undefined field_0x4b81;
	undefined field_0x4b82;
	undefined field_0x4b83;
	undefined field_0x4b84;
	undefined field_0x4b85;
	undefined field_0x4b86;
	undefined field_0x4b87;
	undefined field_0x4b88;
	undefined field_0x4b89;
	undefined field_0x4b8a;
	undefined field_0x4b8b;
	undefined field_0x4b8c;
	undefined field_0x4b8d;
	undefined field_0x4b8e;
	undefined field_0x4b8f;
	undefined field_0x4b90;
	undefined field_0x4b91;
	undefined field_0x4b92;
	undefined field_0x4b93;
	undefined field_0x4b94;
	undefined field_0x4b95;
	undefined field_0x4b96;
	undefined field_0x4b97;
	undefined field_0x4b98;
	undefined field_0x4b99;
	undefined field_0x4b9a;
	undefined field_0x4b9b;
	undefined field_0x4b9c;
	undefined field_0x4b9d;
	undefined field_0x4b9e;
	undefined field_0x4b9f;
	undefined field_0x4ba0;
	undefined field_0x4ba1;
	undefined field_0x4ba2;
	undefined field_0x4ba3;
	undefined field_0x4ba4;
	undefined field_0x4ba5;
	undefined field_0x4ba6;
	undefined field_0x4ba7;
	undefined field_0x4ba8;
	undefined field_0x4ba9;
	undefined field_0x4baa;
	undefined field_0x4bab;
	undefined field_0x4bac;
	undefined field_0x4bad;
	undefined field_0x4bae;
	undefined field_0x4baf;
	undefined field_0x4bb0;
	undefined field_0x4bb1;
	undefined field_0x4bb2;
	undefined field_0x4bb3;
	undefined field_0x4bb4;
	undefined field_0x4bb5;
	undefined field_0x4bb6;
	undefined field_0x4bb7;
	undefined field_0x4bb8;
	undefined field_0x4bb9;
	undefined field_0x4bba;
	undefined field_0x4bbb;
	undefined field_0x4bbc;
	undefined field_0x4bbd;
	undefined field_0x4bbe;
	undefined field_0x4bbf;
	undefined field_0x4bc0;
	undefined field_0x4bc1;
	undefined field_0x4bc2;
	undefined field_0x4bc3;
	undefined field_0x4bc4;
	undefined field_0x4bc5;
	undefined field_0x4bc6;
	undefined field_0x4bc7;
	undefined field_0x4bc8;
	undefined field_0x4bc9;
	undefined field_0x4bca;
	undefined field_0x4bcb;
	undefined field_0x4bcc;
	undefined field_0x4bcd;
	undefined field_0x4bce;
	undefined field_0x4bcf;
	undefined field_0x4bd0;
	undefined field_0x4bd1;
	undefined field_0x4bd2;
	undefined field_0x4bd3;
	undefined field_0x4bd4;
	undefined field_0x4bd5;
	undefined field_0x4bd6;
	undefined field_0x4bd7;
	undefined field_0x4bd8;
	undefined field_0x4bd9;
	undefined field_0x4bda;
	undefined field_0x4bdb;
	undefined field_0x4bdc;
	undefined field_0x4bdd;
	undefined field_0x4bde;
	undefined field_0x4bdf;
	undefined field_0x4be0;
	undefined field_0x4be1;
	undefined field_0x4be2;
	undefined field_0x4be3;
	undefined field_0x4be4;
	undefined field_0x4be5;
	undefined field_0x4be6;
	undefined field_0x4be7;
	undefined field_0x4be8;
	undefined field_0x4be9;
	undefined field_0x4bea;
	undefined field_0x4beb;
	undefined field_0x4bec;
	undefined field_0x4bed;
	undefined field_0x4bee;
	undefined field_0x4bef;
	undefined field_0x4bf0;
	undefined field_0x4bf1;
	undefined field_0x4bf2;
	undefined field_0x4bf3;
	undefined field_0x4bf4;
	undefined field_0x4bf5;
	undefined field_0x4bf6;
	undefined field_0x4bf7;
	undefined field_0x4bf8;
	undefined field_0x4bf9;
	undefined field_0x4bfa;
	undefined field_0x4bfb;
	undefined field_0x4bfc;
	undefined field_0x4bfd;
	undefined field_0x4bfe;
	undefined field_0x4bff;
	undefined field_0x4c00;
	undefined field_0x4c01;
	undefined field_0x4c02;
	undefined field_0x4c03;
	undefined field_0x4c04;
	undefined field_0x4c05;
	undefined field_0x4c06;
	undefined field_0x4c07;
	undefined field_0x4c08;
	undefined field_0x4c09;
	undefined field_0x4c0a;
	undefined field_0x4c0b;
	undefined field_0x4c0c;
	undefined field_0x4c0d;
	undefined field_0x4c0e;
	undefined field_0x4c0f;
	undefined field_0x4c10;
	undefined field_0x4c11;
	undefined field_0x4c12;
	undefined field_0x4c13;
	undefined field_0x4c14;
	undefined field_0x4c15;
	undefined field_0x4c16;
	undefined field_0x4c17;
	undefined field_0x4c18;
	undefined field_0x4c19;
	undefined field_0x4c1a;
	undefined field_0x4c1b;
	undefined field_0x4c1c;
	undefined field_0x4c1d;
	undefined field_0x4c1e;
	undefined field_0x4c1f;
	undefined field_0x4c20;
	undefined field_0x4c21;
	undefined field_0x4c22;
	undefined field_0x4c23;
	undefined field_0x4c24;
	undefined field_0x4c25;
	undefined field_0x4c26;
	undefined field_0x4c27;
	undefined field_0x4c28;
	undefined field_0x4c29;
	undefined field_0x4c2a;
	undefined field_0x4c2b;
	undefined field_0x4c2c;
	undefined field_0x4c2d;
	undefined field_0x4c2e;
	undefined field_0x4c2f;
	undefined field_0x4c30;
	undefined field_0x4c31;
	undefined field_0x4c32;
	undefined field_0x4c33;
	undefined field_0x4c34;
	undefined field_0x4c35;
	undefined field_0x4c36;
	undefined field_0x4c37;
	undefined field_0x4c38;
	undefined field_0x4c39;
	undefined field_0x4c3a;
	undefined field_0x4c3b;
	undefined field_0x4c3c;
	undefined field_0x4c3d;
	undefined field_0x4c3e;
	undefined field_0x4c3f;
	undefined field_0x4c40;
	undefined field_0x4c41;
	undefined field_0x4c42;
	undefined field_0x4c43;
	undefined field_0x4c44;
	undefined field_0x4c45;
	undefined field_0x4c46;
	undefined field_0x4c47;
	undefined field_0x4c48;
	undefined field_0x4c49;
	undefined field_0x4c4a;
	undefined field_0x4c4b;
	undefined field_0x4c4c;
	undefined field_0x4c4d;
	undefined field_0x4c4e;
	undefined field_0x4c4f;
	undefined field_0x4c50;
	undefined field_0x4c51;
	undefined field_0x4c52;
	undefined field_0x4c53;
	undefined field_0x4c54;
	undefined field_0x4c55;
	undefined field_0x4c56;
	undefined field_0x4c57;
	undefined field_0x4c58;
	undefined field_0x4c59;
	undefined field_0x4c5a;
	undefined field_0x4c5b;
	undefined field_0x4c5c;
	undefined field_0x4c5d;
	undefined field_0x4c5e;
	undefined field_0x4c5f;
	undefined field_0x4c60;
	undefined field_0x4c61;
	undefined field_0x4c62;
	undefined field_0x4c63;
	undefined field_0x4c64;
	undefined field_0x4c65;
	undefined field_0x4c66;
	undefined field_0x4c67;
	undefined field_0x4c68;
	undefined field_0x4c69;
	undefined field_0x4c6a;
	undefined field_0x4c6b;
	undefined field_0x4c6c;
	undefined field_0x4c6d;
	undefined field_0x4c6e;
	undefined field_0x4c6f;
	undefined field_0x4c70;
	undefined field_0x4c71;
	undefined field_0x4c72;
	undefined field_0x4c73;
	undefined field_0x4c74;
	undefined field_0x4c75;
	undefined field_0x4c76;
	undefined field_0x4c77;
	undefined field_0x4c78;
	undefined field_0x4c79;
	undefined field_0x4c7a;
	undefined field_0x4c7b;
	undefined field_0x4c7c;
	undefined field_0x4c7d;
	undefined field_0x4c7e;
	undefined field_0x4c7f;
	undefined field_0x4c80;
	undefined field_0x4c81;
	undefined field_0x4c82;
	undefined field_0x4c83;
	undefined field_0x4c84;
	undefined field_0x4c85;
	undefined field_0x4c86;
	undefined field_0x4c87;
	undefined field_0x4c88;
	undefined field_0x4c89;
	undefined field_0x4c8a;
	undefined field_0x4c8b;
	undefined field_0x4c8c;
	undefined field_0x4c8d;
	undefined field_0x4c8e;
	undefined field_0x4c8f;
	undefined field_0x4c90;
	undefined field_0x4c91;
	undefined field_0x4c92;
	undefined field_0x4c93;
	undefined field_0x4c94;
	undefined field_0x4c95;
	undefined field_0x4c96;
	undefined field_0x4c97;
	undefined field_0x4c98;
	undefined field_0x4c99;
	undefined field_0x4c9a;
	undefined field_0x4c9b;
	undefined field_0x4c9c;
	undefined field_0x4c9d;
	undefined field_0x4c9e;
	undefined field_0x4c9f;
	undefined field_0x4ca0;
	undefined field_0x4ca1;
	undefined field_0x4ca2;
	undefined field_0x4ca3;
	undefined field_0x4ca4;
	undefined field_0x4ca5;
	undefined field_0x4ca6;
	undefined field_0x4ca7;
	undefined field_0x4ca8;
	undefined field_0x4ca9;
	undefined field_0x4caa;
	undefined field_0x4cab;
	undefined field_0x4cac;
	undefined field_0x4cad;
	undefined field_0x4cae;
	undefined field_0x4caf;
	undefined field_0x4cb0;
	undefined field_0x4cb1;
	undefined field_0x4cb2;
	undefined field_0x4cb3;
	undefined field_0x4cb4;
	undefined field_0x4cb5;
	undefined field_0x4cb6;
	undefined field_0x4cb7;
	undefined field_0x4cb8;
	undefined field_0x4cb9;
	undefined field_0x4cba;
	undefined field_0x4cbb;
	undefined field_0x4cbc;
	undefined field_0x4cbd;
	undefined field_0x4cbe;
	undefined field_0x4cbf;
	undefined field_0x4cc0;
	undefined field_0x4cc1;
	undefined field_0x4cc2;
	undefined field_0x4cc3;
	undefined field_0x4cc4;
	undefined field_0x4cc5;
	undefined field_0x4cc6;
	undefined field_0x4cc7;
	undefined field_0x4cc8;
	undefined field_0x4cc9;
	undefined field_0x4cca;
	undefined field_0x4ccb;
	undefined field_0x4ccc;
	undefined field_0x4ccd;
	undefined field_0x4cce;
	undefined field_0x4ccf;
	undefined field_0x4cd0;
	undefined field_0x4cd1;
	undefined field_0x4cd2;
	undefined field_0x4cd3;
	undefined field_0x4cd4;
	undefined field_0x4cd5;
	undefined field_0x4cd6;
	undefined field_0x4cd7;
	undefined field_0x4cd8;
	undefined field_0x4cd9;
	undefined field_0x4cda;
	undefined field_0x4cdb;
	undefined field_0x4cdc;
	undefined field_0x4cdd;
	undefined field_0x4cde;
	undefined field_0x4cdf;
	undefined field_0x4ce0;
	undefined field_0x4ce1;
	undefined field_0x4ce2;
	undefined field_0x4ce3;
	undefined field_0x4ce4;
	undefined field_0x4ce5;
	undefined field_0x4ce6;
	undefined field_0x4ce7;
	undefined field_0x4ce8;
	undefined field_0x4ce9;
	undefined field_0x4cea;
	undefined field_0x4ceb;
	undefined field_0x4cec;
	undefined field_0x4ced;
	undefined field_0x4cee;
	undefined field_0x4cef;
	undefined field_0x4cf0;
	undefined field_0x4cf1;
	undefined field_0x4cf2;
	undefined field_0x4cf3;
	undefined field_0x4cf4;
	undefined field_0x4cf5;
	undefined field_0x4cf6;
	undefined field_0x4cf7;
	undefined field_0x4cf8;
	undefined field_0x4cf9;
	undefined field_0x4cfa;
	undefined field_0x4cfb;
	undefined field_0x4cfc;
	undefined field_0x4cfd;
	undefined field_0x4cfe;
	undefined field_0x4cff;
	undefined field_0x4d00;
	undefined field_0x4d01;
	undefined field_0x4d02;
	undefined field_0x4d03;
	undefined field_0x4d04;
	undefined field_0x4d05;
	undefined field_0x4d06;
	undefined field_0x4d07;
	undefined field_0x4d08;
	undefined field_0x4d09;
	undefined field_0x4d0a;
	undefined field_0x4d0b;
	undefined field_0x4d0c;
	undefined field_0x4d0d;
	undefined field_0x4d0e;
	undefined field_0x4d0f;
	undefined field_0x4d10;
	undefined field_0x4d11;
	undefined field_0x4d12;
	undefined field_0x4d13;
	undefined field_0x4d14;
	undefined field_0x4d15;
	undefined field_0x4d16;
	undefined field_0x4d17;
	undefined field_0x4d18;
	undefined field_0x4d19;
	undefined field_0x4d1a;
	undefined field_0x4d1b;
	undefined field_0x4d1c;
	undefined field_0x4d1d;
	undefined field_0x4d1e;
	undefined field_0x4d1f;
	undefined field_0x4d20;
	undefined field_0x4d21;
	undefined field_0x4d22;
	undefined field_0x4d23;
	undefined field_0x4d24;
	undefined field_0x4d25;
	undefined field_0x4d26;
	undefined field_0x4d27;
	undefined field_0x4d28;
	undefined field_0x4d29;
	undefined field_0x4d2a;
	undefined field_0x4d2b;
	undefined field_0x4d2c;
	undefined field_0x4d2d;
	undefined field_0x4d2e;
	undefined field_0x4d2f;
	undefined field_0x4d30;
	undefined field_0x4d31;
	undefined field_0x4d32;
	undefined field_0x4d33;
	undefined field_0x4d34;
	undefined field_0x4d35;
	undefined field_0x4d36;
	undefined field_0x4d37;
	undefined field_0x4d38;
	undefined field_0x4d39;
	undefined field_0x4d3a;
	undefined field_0x4d3b;
	undefined field_0x4d3c;
	undefined field_0x4d3d;
	undefined field_0x4d3e;
	undefined field_0x4d3f;
	undefined field_0x4d40;
	undefined field_0x4d41;
	undefined field_0x4d42;
	undefined field_0x4d43;
	undefined field_0x4d44;
	undefined field_0x4d45;
	undefined field_0x4d46;
	undefined field_0x4d47;
	undefined field_0x4d48;
	undefined field_0x4d49;
	undefined field_0x4d4a;
	undefined field_0x4d4b;
	undefined field_0x4d4c;
	undefined field_0x4d4d;
	undefined field_0x4d4e;
	undefined field_0x4d4f;
	undefined field_0x4d50;
	undefined field_0x4d51;
	undefined field_0x4d52;
	undefined field_0x4d53;
	undefined field_0x4d54;
	undefined field_0x4d55;
	undefined field_0x4d56;
	undefined field_0x4d57;
	undefined field_0x4d58;
	undefined field_0x4d59;
	undefined field_0x4d5a;
	undefined field_0x4d5b;
	undefined field_0x4d5c;
	undefined field_0x4d5d;
	undefined field_0x4d5e;
	undefined field_0x4d5f;
	undefined field_0x4d60;
	undefined field_0x4d61;
	undefined field_0x4d62;
	undefined field_0x4d63;
	undefined field_0x4d64;
	undefined field_0x4d65;
	undefined field_0x4d66;
	undefined field_0x4d67;
	undefined field_0x4d68;
	undefined field_0x4d69;
	undefined field_0x4d6a;
	undefined field_0x4d6b;
	undefined field_0x4d6c;
	undefined field_0x4d6d;
	undefined field_0x4d6e;
	undefined field_0x4d6f;
	undefined field_0x4d70;
	undefined field_0x4d71;
	undefined field_0x4d72;
	undefined field_0x4d73;
	undefined field_0x4d74;
	undefined field_0x4d75;
	undefined field_0x4d76;
	undefined field_0x4d77;
	undefined field_0x4d78;
	undefined field_0x4d79;
	undefined field_0x4d7a;
	undefined field_0x4d7b;
	undefined field_0x4d7c;
	undefined field_0x4d7d;
	undefined field_0x4d7e;
	undefined field_0x4d7f;
	undefined field_0x4d80;
	undefined field_0x4d81;
	undefined field_0x4d82;
	undefined field_0x4d83;
	undefined field_0x4d84;
	undefined field_0x4d85;
	undefined field_0x4d86;
	undefined field_0x4d87;
	undefined field_0x4d88;
	undefined field_0x4d89;
	undefined field_0x4d8a;
	undefined field_0x4d8b;
	undefined field_0x4d8c;
	undefined field_0x4d8d;
	undefined field_0x4d8e;
	undefined field_0x4d8f;
	undefined field_0x4d90;
	undefined field_0x4d91;
	undefined field_0x4d92;
	undefined field_0x4d93;
	undefined field_0x4d94;
	undefined field_0x4d95;
	undefined field_0x4d96;
	undefined field_0x4d97;
	undefined field_0x4d98;
	undefined field_0x4d99;
	undefined field_0x4d9a;
	undefined field_0x4d9b;
	undefined field_0x4d9c;
	undefined field_0x4d9d;
	undefined field_0x4d9e;
	undefined field_0x4d9f;
	undefined field_0x4da0;
	undefined field_0x4da1;
	undefined field_0x4da2;
	undefined field_0x4da3;
	undefined field_0x4da4;
	undefined field_0x4da5;
	undefined field_0x4da6;
	undefined field_0x4da7;
	undefined field_0x4da8;
	undefined field_0x4da9;
	undefined field_0x4daa;
	undefined field_0x4dab;
	undefined field_0x4dac;
	undefined field_0x4dad;
	undefined field_0x4dae;
	undefined field_0x4daf;
	undefined field_0x4db0;
	undefined field_0x4db1;
	undefined field_0x4db2;
	undefined field_0x4db3;
	undefined field_0x4db4;
	undefined field_0x4db5;
	undefined field_0x4db6;
	undefined field_0x4db7;
	undefined field_0x4db8;
	undefined field_0x4db9;
	undefined field_0x4dba;
	undefined field_0x4dbb;
	undefined field_0x4dbc;
	undefined field_0x4dbd;
	undefined field_0x4dbe;
	undefined field_0x4dbf;
	undefined field_0x4dc0;
	undefined field_0x4dc1;
	undefined field_0x4dc2;
	undefined field_0x4dc3;
	undefined field_0x4dc4;
	undefined field_0x4dc5;
	undefined field_0x4dc6;
	undefined field_0x4dc7;
	undefined field_0x4dc8;
	undefined field_0x4dc9;
	undefined field_0x4dca;
	undefined field_0x4dcb;
	undefined field_0x4dcc;
	undefined field_0x4dcd;
	undefined field_0x4dce;
	undefined field_0x4dcf;
	undefined field_0x4dd0;
	undefined field_0x4dd1;
	undefined field_0x4dd2;
	undefined field_0x4dd3;
	undefined field_0x4dd4;
	undefined field_0x4dd5;
	undefined field_0x4dd6;
	undefined field_0x4dd7;
	undefined field_0x4dd8;
	undefined field_0x4dd9;
	undefined field_0x4dda;
	undefined field_0x4ddb;
	undefined field_0x4ddc;
	undefined field_0x4ddd;
	undefined field_0x4dde;
	undefined field_0x4ddf;
	undefined field_0x4de0;
	undefined field_0x4de1;
	undefined field_0x4de2;
	undefined field_0x4de3;
	undefined field_0x4de4;
	undefined field_0x4de5;
	undefined field_0x4de6;
	undefined field_0x4de7;
	undefined field_0x4de8;
	undefined field_0x4de9;
	undefined field_0x4dea;
	undefined field_0x4deb;
	undefined field_0x4dec;
	undefined field_0x4ded;
	undefined field_0x4dee;
	undefined field_0x4def;
	undefined field_0x4df0;
	undefined field_0x4df1;
	undefined field_0x4df2;
	undefined field_0x4df3;
	undefined field_0x4df4;
	undefined field_0x4df5;
	undefined field_0x4df6;
	undefined field_0x4df7;
	undefined field_0x4df8;
	undefined field_0x4df9;
	undefined field_0x4dfa;
	undefined field_0x4dfb;
	undefined field_0x4dfc;
	undefined field_0x4dfd;
	undefined field_0x4dfe;
	undefined field_0x4dff;
	undefined field_0x4e00;
	undefined field_0x4e01;
	undefined field_0x4e02;
	undefined field_0x4e03;
	undefined field_0x4e04;
	undefined field_0x4e05;
	undefined field_0x4e06;
	undefined field_0x4e07;
	undefined field_0x4e08;
	undefined field_0x4e09;
	undefined field_0x4e0a;
	undefined field_0x4e0b;
	undefined field_0x4e0c;
	undefined field_0x4e0d;
	undefined field_0x4e0e;
	undefined field_0x4e0f;
	undefined field_0x4e10;
	undefined field_0x4e11;
	undefined field_0x4e12;
	undefined field_0x4e13;
	undefined field_0x4e14;
	undefined field_0x4e15;
	undefined field_0x4e16;
	undefined field_0x4e17;
	undefined field_0x4e18;
	undefined field_0x4e19;
	undefined field_0x4e1a;
	undefined field_0x4e1b;
	undefined field_0x4e1c;
	undefined field_0x4e1d;
	undefined field_0x4e1e;
	undefined field_0x4e1f;
	undefined field_0x4e20;
	undefined field_0x4e21;
	undefined field_0x4e22;
	undefined field_0x4e23;
	undefined field_0x4e24;
	undefined field_0x4e25;
	undefined field_0x4e26;
	undefined field_0x4e27;
	undefined field_0x4e28;
	undefined field_0x4e29;
	undefined field_0x4e2a;
	undefined field_0x4e2b;
	undefined field_0x4e2c;
	undefined field_0x4e2d;
	undefined field_0x4e2e;
	undefined field_0x4e2f;
	undefined field_0x4e30;
	undefined field_0x4e31;
	undefined field_0x4e32;
	undefined field_0x4e33;
	undefined field_0x4e34;
	undefined field_0x4e35;
	undefined field_0x4e36;
	undefined field_0x4e37;
	undefined field_0x4e38;
	undefined field_0x4e39;
	undefined field_0x4e3a;
	undefined field_0x4e3b;
	undefined field_0x4e3c;
	undefined field_0x4e3d;
	undefined field_0x4e3e;
	undefined field_0x4e3f;
	undefined field_0x4e40;
	undefined field_0x4e41;
	undefined field_0x4e42;
	undefined field_0x4e43;
	undefined field_0x4e44;
	undefined field_0x4e45;
	undefined field_0x4e46;
	undefined field_0x4e47;
	undefined field_0x4e48;
	undefined field_0x4e49;
	undefined field_0x4e4a;
	undefined field_0x4e4b;
	undefined field_0x4e4c;
	undefined field_0x4e4d;
	undefined field_0x4e4e;
	undefined field_0x4e4f;
	undefined field_0x4e50;
	undefined field_0x4e51;
	undefined field_0x4e52;
	undefined field_0x4e53;
	undefined field_0x4e54;
	undefined field_0x4e55;
	undefined field_0x4e56;
	undefined field_0x4e57;
	undefined field_0x4e58;
	undefined field_0x4e59;
	undefined field_0x4e5a;
	undefined field_0x4e5b;
	undefined field_0x4e5c;
	undefined field_0x4e5d;
	undefined field_0x4e5e;
	undefined field_0x4e5f;
	undefined field_0x4e60;
	undefined field_0x4e61;
	undefined field_0x4e62;
	undefined field_0x4e63;
	undefined field_0x4e64;
	undefined field_0x4e65;
	undefined field_0x4e66;
	undefined field_0x4e67;
	undefined field_0x4e68;
	undefined field_0x4e69;
	undefined field_0x4e6a;
	undefined field_0x4e6b;
	undefined field_0x4e6c;
	undefined field_0x4e6d;
	undefined field_0x4e6e;
	undefined field_0x4e6f;
	undefined field_0x4e70;
	undefined field_0x4e71;
	undefined field_0x4e72;
	undefined field_0x4e73;
	undefined field_0x4e74;
	undefined field_0x4e75;
	undefined field_0x4e76;
	undefined field_0x4e77;
	undefined field_0x4e78;
	undefined field_0x4e79;
	undefined field_0x4e7a;
	undefined field_0x4e7b;
	undefined field_0x4e7c;
	undefined field_0x4e7d;
	undefined field_0x4e7e;
	undefined field_0x4e7f;
	undefined field_0x4e80;
	undefined field_0x4e81;
	undefined field_0x4e82;
	undefined field_0x4e83;
	undefined field_0x4e84;
	undefined field_0x4e85;
	undefined field_0x4e86;
	undefined field_0x4e87;
	undefined field_0x4e88;
	undefined field_0x4e89;
	undefined field_0x4e8a;
	undefined field_0x4e8b;
	undefined field_0x4e8c;
	undefined field_0x4e8d;
	undefined field_0x4e8e;
	undefined field_0x4e8f;
	undefined field_0x4e90;
	undefined field_0x4e91;
	undefined field_0x4e92;
	undefined field_0x4e93;
	undefined field_0x4e94;
	undefined field_0x4e95;
	undefined field_0x4e96;
	undefined field_0x4e97;
	undefined field_0x4e98;
	undefined field_0x4e99;
	undefined field_0x4e9a;
	undefined field_0x4e9b;
	undefined field_0x4e9c;
	undefined field_0x4e9d;
	undefined field_0x4e9e;
	undefined field_0x4e9f;
	undefined field_0x4ea0;
	undefined field_0x4ea1;
	undefined field_0x4ea2;
	undefined field_0x4ea3;
	undefined field_0x4ea4;
	undefined field_0x4ea5;
	undefined field_0x4ea6;
	undefined field_0x4ea7;
	undefined field_0x4ea8;
	undefined field_0x4ea9;
	undefined field_0x4eaa;
	undefined field_0x4eab;
	undefined field_0x4eac;
	undefined field_0x4ead;
	undefined field_0x4eae;
	undefined field_0x4eaf;
	undefined field_0x4eb0;
	undefined field_0x4eb1;
	undefined field_0x4eb2;
	undefined field_0x4eb3;
	undefined field_0x4eb4;
	undefined field_0x4eb5;
	undefined field_0x4eb6;
	undefined field_0x4eb7;
	undefined field_0x4eb8;
	undefined field_0x4eb9;
	undefined field_0x4eba;
	undefined field_0x4ebb;
	undefined field_0x4ebc;
	undefined field_0x4ebd;
	undefined field_0x4ebe;
	undefined field_0x4ebf;
	undefined field_0x4ec0;
	undefined field_0x4ec1;
	undefined field_0x4ec2;
	undefined field_0x4ec3;
	undefined field_0x4ec4;
	undefined field_0x4ec5;
	undefined field_0x4ec6;
	undefined field_0x4ec7;
	undefined field_0x4ec8;
	undefined field_0x4ec9;
	undefined field_0x4eca;
	undefined field_0x4ecb;
	undefined field_0x4ecc;
	undefined field_0x4ecd;
	undefined field_0x4ece;
	undefined field_0x4ecf;
	undefined field_0x4ed0;
	undefined field_0x4ed1;
	undefined field_0x4ed2;
	undefined field_0x4ed3;
	undefined field_0x4ed4;
	undefined field_0x4ed5;
	undefined field_0x4ed6;
	undefined field_0x4ed7;
	undefined field_0x4ed8;
	undefined field_0x4ed9;
	undefined field_0x4eda;
	undefined field_0x4edb;
	undefined field_0x4edc;
	undefined field_0x4edd;
	undefined field_0x4ede;
	undefined field_0x4edf;
	undefined field_0x4ee0;
	undefined field_0x4ee1;
	undefined field_0x4ee2;
	undefined field_0x4ee3;
	undefined field_0x4ee4;
	undefined field_0x4ee5;
	undefined field_0x4ee6;
	undefined field_0x4ee7;
	undefined field_0x4ee8;
	undefined field_0x4ee9;
	undefined field_0x4eea;
	undefined field_0x4eeb;
	undefined field_0x4eec;
	undefined field_0x4eed;
	undefined field_0x4eee;
	undefined field_0x4eef;
	undefined field_0x4ef0;
	undefined field_0x4ef1;
	undefined field_0x4ef2;
	undefined field_0x4ef3;
	undefined field_0x4ef4;
	undefined field_0x4ef5;
	undefined field_0x4ef6;
	undefined field_0x4ef7;
	undefined field_0x4ef8;
	undefined field_0x4ef9;
	undefined field_0x4efa;
	undefined field_0x4efb;
	undefined field_0x4efc;
	undefined field_0x4efd;
	undefined field_0x4efe;
	undefined field_0x4eff;
	undefined field_0x4f00;
	undefined field_0x4f01;
	undefined field_0x4f02;
	undefined field_0x4f03;
	undefined field_0x4f04;
	undefined field_0x4f05;
	undefined field_0x4f06;
	undefined field_0x4f07;
	undefined field_0x4f08;
	undefined field_0x4f09;
	undefined field_0x4f0a;
	undefined field_0x4f0b;
	undefined field_0x4f0c;
	undefined field_0x4f0d;
	undefined field_0x4f0e;
	undefined field_0x4f0f;
	undefined field_0x4f10;
	undefined field_0x4f11;
	undefined field_0x4f12;
	undefined field_0x4f13;
	undefined field_0x4f14;
	undefined field_0x4f15;
	undefined field_0x4f16;
	undefined field_0x4f17;
	undefined field_0x4f18;
	undefined field_0x4f19;
	undefined field_0x4f1a;
	undefined field_0x4f1b;
	undefined field_0x4f1c;
	undefined field_0x4f1d;
	undefined field_0x4f1e;
	undefined field_0x4f1f;
	undefined field_0x4f20;
	undefined field_0x4f21;
	undefined field_0x4f22;
	undefined field_0x4f23;
	undefined field_0x4f24;
	undefined field_0x4f25;
	undefined field_0x4f26;
	undefined field_0x4f27;
	undefined field_0x4f28;
	undefined field_0x4f29;
	undefined field_0x4f2a;
	undefined field_0x4f2b;
	undefined field_0x4f2c;
	undefined field_0x4f2d;
	undefined field_0x4f2e;
	undefined field_0x4f2f;
	undefined field_0x4f30;
	undefined field_0x4f31;
	undefined field_0x4f32;
	undefined field_0x4f33;
	undefined field_0x4f34;
	undefined field_0x4f35;
	undefined field_0x4f36;
	undefined field_0x4f37;
	undefined field_0x4f38;
	undefined field_0x4f39;
	undefined field_0x4f3a;
	undefined field_0x4f3b;
	undefined field_0x4f3c;
	undefined field_0x4f3d;
	undefined field_0x4f3e;
	undefined field_0x4f3f;
	undefined field_0x4f40;
	undefined field_0x4f41;
	undefined field_0x4f42;
	undefined field_0x4f43;
	undefined field_0x4f44;
	undefined field_0x4f45;
	undefined field_0x4f46;
	undefined field_0x4f47;
	undefined field_0x4f48;
	undefined field_0x4f49;
	undefined field_0x4f4a;
	undefined field_0x4f4b;
	undefined field_0x4f4c;
	undefined field_0x4f4d;
	undefined field_0x4f4e;
	undefined field_0x4f4f;
	undefined field_0x4f50;
	undefined field_0x4f51;
	undefined field_0x4f52;
	undefined field_0x4f53;
	undefined field_0x4f54;
	undefined field_0x4f55;
	undefined field_0x4f56;
	undefined field_0x4f57;
	undefined field_0x4f58;
	undefined field_0x4f59;
	undefined field_0x4f5a;
	undefined field_0x4f5b;
	undefined field_0x4f5c;
	undefined field_0x4f5d;
	undefined field_0x4f5e;
	undefined field_0x4f5f;
	undefined field_0x4f60;
	undefined field_0x4f61;
	undefined field_0x4f62;
	undefined field_0x4f63;
	undefined field_0x4f64;
	undefined field_0x4f65;
	undefined field_0x4f66;
	undefined field_0x4f67;
	undefined field_0x4f68;
	undefined field_0x4f69;
	undefined field_0x4f6a;
	undefined field_0x4f6b;
	undefined field_0x4f6c;
	undefined field_0x4f6d;
	undefined field_0x4f6e;
	undefined field_0x4f6f;
	undefined field_0x4f70;
	undefined field_0x4f71;
	undefined field_0x4f72;
	undefined field_0x4f73;
	undefined field_0x4f74;
	undefined field_0x4f75;
	undefined field_0x4f76;
	undefined field_0x4f77;
	undefined field_0x4f78;
	undefined field_0x4f79;
	undefined field_0x4f7a;
	undefined field_0x4f7b;
	undefined field_0x4f7c;
	undefined field_0x4f7d;
	undefined field_0x4f7e;
	undefined field_0x4f7f;
	undefined field_0x4f80;
	undefined field_0x4f81;
	undefined field_0x4f82;
	undefined field_0x4f83;
	undefined field_0x4f84;
	undefined field_0x4f85;
	undefined field_0x4f86;
	undefined field_0x4f87;
	undefined field_0x4f88;
	undefined field_0x4f89;
	undefined field_0x4f8a;
	undefined field_0x4f8b;
	undefined field_0x4f8c;
	undefined field_0x4f8d;
	undefined field_0x4f8e;
	undefined field_0x4f8f;
	undefined field_0x4f90;
	undefined field_0x4f91;
	undefined field_0x4f92;
	undefined field_0x4f93;
	undefined field_0x4f94;
	undefined field_0x4f95;
	undefined field_0x4f96;
	undefined field_0x4f97;
	undefined field_0x4f98;
	undefined field_0x4f99;
	undefined field_0x4f9a;
	undefined field_0x4f9b;
	undefined field_0x4f9c;
	undefined field_0x4f9d;
	undefined field_0x4f9e;
	undefined field_0x4f9f;
	undefined field_0x4fa0;
	undefined field_0x4fa1;
	undefined field_0x4fa2;
	undefined field_0x4fa3;
	undefined field_0x4fa4;
	undefined field_0x4fa5;
	undefined field_0x4fa6;
	undefined field_0x4fa7;
	undefined field_0x4fa8;
	undefined field_0x4fa9;
	undefined field_0x4faa;
	undefined field_0x4fab;
	undefined field_0x4fac;
	undefined field_0x4fad;
	undefined field_0x4fae;
	undefined field_0x4faf;
	undefined field_0x4fb0;
	undefined field_0x4fb1;
	undefined field_0x4fb2;
	undefined field_0x4fb3;
	undefined field_0x4fb4;
	undefined field_0x4fb5;
	undefined field_0x4fb6;
	undefined field_0x4fb7;
	undefined field_0x4fb8;
	undefined field_0x4fb9;
	undefined field_0x4fba;
	undefined field_0x4fbb;
	undefined field_0x4fbc;
	undefined field_0x4fbd;
	undefined field_0x4fbe;
	undefined field_0x4fbf;
	undefined field_0x4fc0;
	undefined field_0x4fc1;
	undefined field_0x4fc2;
	undefined field_0x4fc3;
	undefined field_0x4fc4;
	undefined field_0x4fc5;
	undefined field_0x4fc6;
	undefined field_0x4fc7;
	undefined field_0x4fc8;
	undefined field_0x4fc9;
	undefined field_0x4fca;
	undefined field_0x4fcb;
	undefined field_0x4fcc;
	undefined field_0x4fcd;
	undefined field_0x4fce;
	undefined field_0x4fcf;
	undefined field_0x4fd0;
	undefined field_0x4fd1;
	undefined field_0x4fd2;
	undefined field_0x4fd3;
	undefined field_0x4fd4;
	undefined field_0x4fd5;
	undefined field_0x4fd6;
	undefined field_0x4fd7;
	undefined field_0x4fd8;
	undefined field_0x4fd9;
	undefined field_0x4fda;
	undefined field_0x4fdb;
	undefined field_0x4fdc;
	undefined field_0x4fdd;
	undefined field_0x4fde;
	undefined field_0x4fdf;
	undefined field_0x4fe0;
	undefined field_0x4fe1;
	undefined field_0x4fe2;
	undefined field_0x4fe3;
	undefined field_0x4fe4;
	undefined field_0x4fe5;
	undefined field_0x4fe6;
	undefined field_0x4fe7;
	undefined field_0x4fe8;
	undefined field_0x4fe9;
	undefined field_0x4fea;
	undefined field_0x4feb;
	undefined field_0x4fec;
	undefined field_0x4fed;
	undefined field_0x4fee;
	undefined field_0x4fef;
	undefined field_0x4ff0;
	undefined field_0x4ff1;
	undefined field_0x4ff2;
	undefined field_0x4ff3;
	undefined field_0x4ff4;
	undefined field_0x4ff5;
	undefined field_0x4ff6;
	undefined field_0x4ff7;
	undefined field_0x4ff8;
	undefined field_0x4ff9;
	undefined field_0x4ffa;
	undefined field_0x4ffb;
	undefined field_0x4ffc;
	undefined field_0x4ffd;
	undefined field_0x4ffe;
	undefined field_0x4fff;
	undefined field_0x5000;
	undefined field_0x5001;
	undefined field_0x5002;
	undefined field_0x5003;
	undefined field_0x5004;
	undefined field_0x5005;
	undefined field_0x5006;
	undefined field_0x5007;
	undefined field_0x5008;
	undefined field_0x5009;
	undefined field_0x500a;
	undefined field_0x500b;
	undefined field_0x500c;
	undefined field_0x500d;
	undefined field_0x500e;
	undefined field_0x500f;
	undefined field_0x5010;
	undefined field_0x5011;
	undefined field_0x5012;
	undefined field_0x5013;
	undefined field_0x5014;
	undefined field_0x5015;
	undefined field_0x5016;
	undefined field_0x5017;
	undefined field_0x5018;
	undefined field_0x5019;
	undefined field_0x501a;
	undefined field_0x501b;
	undefined field_0x501c;
	undefined field_0x501d;
	undefined field_0x501e;
	undefined field_0x501f;
	undefined field_0x5020;
	undefined field_0x5021;
	undefined field_0x5022;
	undefined field_0x5023;
	undefined field_0x5024;
	undefined field_0x5025;
	undefined field_0x5026;
	undefined field_0x5027;
	undefined field_0x5028;
	undefined field_0x5029;
	undefined field_0x502a;
	undefined field_0x502b;
	undefined field_0x502c;
	undefined field_0x502d;
	undefined field_0x502e;
	undefined field_0x502f;
	undefined field_0x5030;
	undefined field_0x5031;
	undefined field_0x5032;
	undefined field_0x5033;
	undefined field_0x5034;
	undefined field_0x5035;
	undefined field_0x5036;
	undefined field_0x5037;
	undefined field_0x5038;
	undefined field_0x5039;
	undefined field_0x503a;
	undefined field_0x503b;
	undefined field_0x503c;
	undefined field_0x503d;
	undefined field_0x503e;
	undefined field_0x503f;
	undefined field_0x5040;
	undefined field_0x5041;
	undefined field_0x5042;
	undefined field_0x5043;
	undefined field_0x5044;
	undefined field_0x5045;
	undefined field_0x5046;
	undefined field_0x5047;
	undefined field_0x5048;
	undefined field_0x5049;
	undefined field_0x504a;
	undefined field_0x504b;
	undefined field_0x504c;
	undefined field_0x504d;
	undefined field_0x504e;
	undefined field_0x504f;
	undefined field_0x5050;
	undefined field_0x5051;
	undefined field_0x5052;
	undefined field_0x5053;
	undefined field_0x5054;
	undefined field_0x5055;
	undefined field_0x5056;
	undefined field_0x5057;
	undefined field_0x5058;
	undefined field_0x5059;
	undefined field_0x505a;
	undefined field_0x505b;
	undefined field_0x505c;
	undefined field_0x505d;
	undefined field_0x505e;
	undefined field_0x505f;
	undefined field_0x5060;
	undefined field_0x5061;
	undefined field_0x5062;
	undefined field_0x5063;
	undefined field_0x5064;
	undefined field_0x5065;
	undefined field_0x5066;
	undefined field_0x5067;
	undefined field_0x5068;
	undefined field_0x5069;
	undefined field_0x506a;
	undefined field_0x506b;
	undefined field_0x506c;
	undefined field_0x506d;
	undefined field_0x506e;
	undefined field_0x506f;
	undefined field_0x5070;
	undefined field_0x5071;
	undefined field_0x5072;
	undefined field_0x5073;
	undefined field_0x5074;
	undefined field_0x5075;
	undefined field_0x5076;
	undefined field_0x5077;
	undefined field_0x5078;
	undefined field_0x5079;
	undefined field_0x507a;
	undefined field_0x507b;
	undefined field_0x507c;
	undefined field_0x507d;
	undefined field_0x507e;
	undefined field_0x507f;
	undefined field_0x5080;
	undefined field_0x5081;
	undefined field_0x5082;
	undefined field_0x5083;
	undefined field_0x5084;
	undefined field_0x5085;
	undefined field_0x5086;
	undefined field_0x5087;
	undefined field_0x5088;
	undefined field_0x5089;
	undefined field_0x508a;
	undefined field_0x508b;
	undefined field_0x508c;
	undefined field_0x508d;
	undefined field_0x508e;
	undefined field_0x508f;
	undefined field_0x5090;
	undefined field_0x5091;
	undefined field_0x5092;
	undefined field_0x5093;
	undefined field_0x5094;
	undefined field_0x5095;
	undefined field_0x5096;
	undefined field_0x5097;
	undefined field_0x5098;
	undefined field_0x5099;
	undefined field_0x509a;
	undefined field_0x509b;
	undefined field_0x509c;
	undefined field_0x509d;
	undefined field_0x509e;
	undefined field_0x509f;
	undefined field_0x50a0;
	undefined field_0x50a1;
	undefined field_0x50a2;
	undefined field_0x50a3;
	undefined field_0x50a4;
	undefined field_0x50a5;
	undefined field_0x50a6;
	undefined field_0x50a7;
	undefined field_0x50a8;
	undefined field_0x50a9;
	undefined field_0x50aa;
	undefined field_0x50ab;
	undefined field_0x50ac;
	undefined field_0x50ad;
	undefined field_0x50ae;
	undefined field_0x50af;
	undefined field_0x50b0;
	undefined field_0x50b1;
	undefined field_0x50b2;
	undefined field_0x50b3;
	undefined field_0x50b4;
	undefined field_0x50b5;
	undefined field_0x50b6;
	undefined field_0x50b7;
	undefined field_0x50b8;
	undefined field_0x50b9;
	undefined field_0x50ba;
	undefined field_0x50bb;
	undefined field_0x50bc;
	undefined field_0x50bd;
	undefined field_0x50be;
	undefined field_0x50bf;
	undefined field_0x50c0;
	undefined field_0x50c1;
	undefined field_0x50c2;
	undefined field_0x50c3;
	undefined field_0x50c4;
	undefined field_0x50c5;
	undefined field_0x50c6;
	undefined field_0x50c7;
	undefined field_0x50c8;
	undefined field_0x50c9;
	undefined field_0x50ca;
	undefined field_0x50cb;
	undefined field_0x50cc;
	undefined field_0x50cd;
	undefined field_0x50ce;
	undefined field_0x50cf;
	undefined field_0x50d0;
	undefined field_0x50d1;
	undefined field_0x50d2;
	undefined field_0x50d3;
	undefined field_0x50d4;
	undefined field_0x50d5;
	undefined field_0x50d6;
	undefined field_0x50d7;
	undefined field_0x50d8;
	undefined field_0x50d9;
	undefined field_0x50da;
	undefined field_0x50db;
	undefined field_0x50dc;
	undefined field_0x50dd;
	undefined field_0x50de;
	undefined field_0x50df;
	undefined field_0x50e0;
	undefined field_0x50e1;
	undefined field_0x50e2;
	undefined field_0x50e3;
	undefined field_0x50e4;
	undefined field_0x50e5;
	undefined field_0x50e6;
	undefined field_0x50e7;
	undefined field_0x50e8;
	undefined field_0x50e9;
	undefined field_0x50ea;
	undefined field_0x50eb;
	undefined field_0x50ec;
	undefined field_0x50ed;
	undefined field_0x50ee;
	undefined field_0x50ef;
	undefined field_0x50f0;
	undefined field_0x50f1;
	undefined field_0x50f2;
	undefined field_0x50f3;
	undefined field_0x50f4;
	undefined field_0x50f5;
	undefined field_0x50f6;
	undefined field_0x50f7;
	undefined field_0x50f8;
	undefined field_0x50f9;
	undefined field_0x50fa;
	undefined field_0x50fb;
	undefined field_0x50fc;
	undefined field_0x50fd;
	undefined field_0x50fe;
	undefined field_0x50ff;
	undefined field_0x5100;
	undefined field_0x5101;
	undefined field_0x5102;
	undefined field_0x5103;
	undefined field_0x5104;
	undefined field_0x5105;
	undefined field_0x5106;
	undefined field_0x5107;
	undefined field_0x5108;
	undefined field_0x5109;
	undefined field_0x510a;
	undefined field_0x510b;
	undefined field_0x510c;
	undefined field_0x510d;
	undefined field_0x510e;
	undefined field_0x510f;
	undefined field_0x5110;
	undefined field_0x5111;
	undefined field_0x5112;
	undefined field_0x5113;
	undefined field_0x5114;
	undefined field_0x5115;
	undefined field_0x5116;
	undefined field_0x5117;
	undefined field_0x5118;
	undefined field_0x5119;
	undefined field_0x511a;
	undefined field_0x511b;
	undefined field_0x511c;
	undefined field_0x511d;
	undefined field_0x511e;
	undefined field_0x511f;
	undefined field_0x5120;
	undefined field_0x5121;
	undefined field_0x5122;
	undefined field_0x5123;
	undefined field_0x5124;
	undefined field_0x5125;
	undefined field_0x5126;
	undefined field_0x5127;
	undefined field_0x5128;
	undefined field_0x5129;
	undefined field_0x512a;
	undefined field_0x512b;
	undefined field_0x512c;
	undefined field_0x512d;
	undefined field_0x512e;
	undefined field_0x512f;
	undefined field_0x5130;
	undefined field_0x5131;
	undefined field_0x5132;
	undefined field_0x5133;
	undefined field_0x5134;
	undefined field_0x5135;
	undefined field_0x5136;
	undefined field_0x5137;
	undefined field_0x5138;
	undefined field_0x5139;
	undefined field_0x513a;
	undefined field_0x513b;
	undefined field_0x513c;
	undefined field_0x513d;
	undefined field_0x513e;
	undefined field_0x513f;
	undefined field_0x5140;
	undefined field_0x5141;
	undefined field_0x5142;
	undefined field_0x5143;
	undefined field_0x5144;
	undefined field_0x5145;
	undefined field_0x5146;
	undefined field_0x5147;
	undefined field_0x5148;
	undefined field_0x5149;
	undefined field_0x514a;
	undefined field_0x514b;
	undefined field_0x514c;
	undefined field_0x514d;
	undefined field_0x514e;
	undefined field_0x514f;
	undefined field_0x5150;
	undefined field_0x5151;
	undefined field_0x5152;
	undefined field_0x5153;
	undefined field_0x5154;
	undefined field_0x5155;
	undefined field_0x5156;
	undefined field_0x5157;
	undefined field_0x5158;
	undefined field_0x5159;
	undefined field_0x515a;
	undefined field_0x515b;
	undefined field_0x515c;
	undefined field_0x515d;
	undefined field_0x515e;
	undefined field_0x515f;
	undefined field_0x5160;
	undefined field_0x5161;
	undefined field_0x5162;
	undefined field_0x5163;
	undefined field_0x5164;
	undefined field_0x5165;
	undefined field_0x5166;
	undefined field_0x5167;
	undefined field_0x5168;
	undefined field_0x5169;
	undefined field_0x516a;
	undefined field_0x516b;
	undefined field_0x516c;
	undefined field_0x516d;
	undefined field_0x516e;
	undefined field_0x516f;
	undefined field_0x5170;
	undefined field_0x5171;
	undefined field_0x5172;
	undefined field_0x5173;
	undefined field_0x5174;
	undefined field_0x5175;
	undefined field_0x5176;
	undefined field_0x5177;
	undefined field_0x5178;
	undefined field_0x5179;
	undefined field_0x517a;
	undefined field_0x517b;
	undefined field_0x517c;
	undefined field_0x517d;
	undefined field_0x517e;
	undefined field_0x517f;
	undefined field_0x5180;
	undefined field_0x5181;
	undefined field_0x5182;
	undefined field_0x5183;
	undefined field_0x5184;
	undefined field_0x5185;
	undefined field_0x5186;
	undefined field_0x5187;
	undefined field_0x5188;
	undefined field_0x5189;
	undefined field_0x518a;
	undefined field_0x518b;
	undefined field_0x518c;
	undefined field_0x518d;
	undefined field_0x518e;
	undefined field_0x518f;
	undefined field_0x5190;
	undefined field_0x5191;
	undefined field_0x5192;
	undefined field_0x5193;
	undefined field_0x5194;
	undefined field_0x5195;
	undefined field_0x5196;
	undefined field_0x5197;
	undefined field_0x5198;
	undefined field_0x5199;
	undefined field_0x519a;
	undefined field_0x519b;
	undefined field_0x519c;
	undefined field_0x519d;
	undefined field_0x519e;
	undefined field_0x519f;
	undefined field_0x51a0;
	undefined field_0x51a1;
	undefined field_0x51a2;
	undefined field_0x51a3;
	undefined field_0x51a4;
	undefined field_0x51a5;
	undefined field_0x51a6;
	undefined field_0x51a7;
	undefined field_0x51a8;
	undefined field_0x51a9;
	undefined field_0x51aa;
	undefined field_0x51ab;
	undefined field_0x51ac;
	undefined field_0x51ad;
	undefined field_0x51ae;
	undefined field_0x51af;
	undefined field_0x51b0;
	undefined field_0x51b1;
	undefined field_0x51b2;
	undefined field_0x51b3;
	undefined field_0x51b4;
	undefined field_0x51b5;
	undefined field_0x51b6;
	undefined field_0x51b7;
	undefined field_0x51b8;
	undefined field_0x51b9;
	undefined field_0x51ba;
	undefined field_0x51bb;
	undefined field_0x51bc;
	undefined field_0x51bd;
	undefined field_0x51be;
	undefined field_0x51bf;
	undefined field_0x51c0;
	undefined field_0x51c1;
	undefined field_0x51c2;
	undefined field_0x51c3;
	undefined field_0x51c4;
	undefined field_0x51c5;
	undefined field_0x51c6;
	undefined field_0x51c7;
	undefined field_0x51c8;
	undefined field_0x51c9;
	undefined field_0x51ca;
	undefined field_0x51cb;
	undefined field_0x51cc;
	undefined field_0x51cd;
	undefined field_0x51ce;
	undefined field_0x51cf;
	undefined field_0x51d0;
	undefined field_0x51d1;
	undefined field_0x51d2;
	undefined field_0x51d3;
	undefined field_0x51d4;
	undefined field_0x51d5;
	undefined field_0x51d6;
	undefined field_0x51d7;
	undefined field_0x51d8;
	undefined field_0x51d9;
	undefined field_0x51da;
	undefined field_0x51db;
	undefined field_0x51dc;
	undefined field_0x51dd;
	undefined field_0x51de;
	undefined field_0x51df;
	undefined field_0x51e0;
	undefined field_0x51e1;
	undefined field_0x51e2;
	undefined field_0x51e3;
	undefined field_0x51e4;
	undefined field_0x51e5;
	undefined field_0x51e6;
	undefined field_0x51e7;
	undefined field_0x51e8;
	undefined field_0x51e9;
	undefined field_0x51ea;
	undefined field_0x51eb;
	undefined field_0x51ec;
	undefined field_0x51ed;
	undefined field_0x51ee;
	undefined field_0x51ef;
	undefined field_0x51f0;
	undefined field_0x51f1;
	undefined field_0x51f2;
	undefined field_0x51f3;
	undefined field_0x51f4;
	undefined field_0x51f5;
	undefined field_0x51f6;
	undefined field_0x51f7;
	undefined field_0x51f8;
	undefined field_0x51f9;
	undefined field_0x51fa;
	undefined field_0x51fb;
	undefined field_0x51fc;
	undefined field_0x51fd;
	undefined field_0x51fe;
	undefined field_0x51ff;
	undefined field_0x5200;
	undefined field_0x5201;
	undefined field_0x5202;
	undefined field_0x5203;
	undefined field_0x5204;
	undefined field_0x5205;
	undefined field_0x5206;
	undefined field_0x5207;
	undefined field_0x5208;
	undefined field_0x5209;
	undefined field_0x520a;
	undefined field_0x520b;
	undefined field_0x520c;
	undefined field_0x520d;
	undefined field_0x520e;
	undefined field_0x520f;
	undefined field_0x5210;
	undefined field_0x5211;
	undefined field_0x5212;
	undefined field_0x5213;
	undefined field_0x5214;
	undefined field_0x5215;
	undefined field_0x5216;
	undefined field_0x5217;
	undefined field_0x5218;
	undefined field_0x5219;
	undefined field_0x521a;
	undefined field_0x521b;
	undefined field_0x521c;
	undefined field_0x521d;
	undefined field_0x521e;
	undefined field_0x521f;
	undefined field_0x5220;
	undefined field_0x5221;
	undefined field_0x5222;
	undefined field_0x5223;
	undefined field_0x5224;
	undefined field_0x5225;
	undefined field_0x5226;
	undefined field_0x5227;
	undefined field_0x5228;
	undefined field_0x5229;
	undefined field_0x522a;
	undefined field_0x522b;
	undefined field_0x522c;
	undefined field_0x522d;
	undefined field_0x522e;
	undefined field_0x522f;
	undefined field_0x5230;
	undefined field_0x5231;
	undefined field_0x5232;
	undefined field_0x5233;
	undefined field_0x5234;
	undefined field_0x5235;
	undefined field_0x5236;
	undefined field_0x5237;
	undefined field_0x5238;
	undefined field_0x5239;
	undefined field_0x523a;
	undefined field_0x523b;
	undefined field_0x523c;
	undefined field_0x523d;
	undefined field_0x523e;
	undefined field_0x523f;
	undefined field_0x5240;
	undefined field_0x5241;
	undefined field_0x5242;
	undefined field_0x5243;
	undefined field_0x5244;
	undefined field_0x5245;
	undefined field_0x5246;
	undefined field_0x5247;
	undefined field_0x5248;
	undefined field_0x5249;
	undefined field_0x524a;
	undefined field_0x524b;
	undefined field_0x524c;
	undefined field_0x524d;
	undefined field_0x524e;
	undefined field_0x524f;
	undefined field_0x5250;
	undefined field_0x5251;
	undefined field_0x5252;
	undefined field_0x5253;
	undefined field_0x5254;
	undefined field_0x5255;
	undefined field_0x5256;
	undefined field_0x5257;
	undefined field_0x5258;
	undefined field_0x5259;
	undefined field_0x525a;
	undefined field_0x525b;
	undefined field_0x525c;
	undefined field_0x525d;
	undefined field_0x525e;
	undefined field_0x525f;
	undefined field_0x5260;
	undefined field_0x5261;
	undefined field_0x5262;
	undefined field_0x5263;
	undefined field_0x5264;
	undefined field_0x5265;
	undefined field_0x5266;
	undefined field_0x5267;
	undefined field_0x5268;
	undefined field_0x5269;
	undefined field_0x526a;
	undefined field_0x526b;
	undefined field_0x526c;
	undefined field_0x526d;
	undefined field_0x526e;
	undefined field_0x526f;
	undefined field_0x5270;
	undefined field_0x5271;
	undefined field_0x5272;
	undefined field_0x5273;
	undefined field_0x5274;
	undefined field_0x5275;
	undefined field_0x5276;
	undefined field_0x5277;
	undefined field_0x5278;
	undefined field_0x5279;
	undefined field_0x527a;
	undefined field_0x527b;
	undefined field_0x527c;
	undefined field_0x527d;
	undefined field_0x527e;
	undefined field_0x527f;
	undefined field_0x5280;
	undefined field_0x5281;
	undefined field_0x5282;
	undefined field_0x5283;
	undefined field_0x5284;
	undefined field_0x5285;
	undefined field_0x5286;
	undefined field_0x5287;
	undefined field_0x5288;
	undefined field_0x5289;
	undefined field_0x528a;
	undefined field_0x528b;
	undefined field_0x528c;
	undefined field_0x528d;
	undefined field_0x528e;
	undefined field_0x528f;
	undefined field_0x5290;
	undefined field_0x5291;
	undefined field_0x5292;
	undefined field_0x5293;
	undefined field_0x5294;
	undefined field_0x5295;
	undefined field_0x5296;
	undefined field_0x5297;
	undefined field_0x5298;
	undefined field_0x5299;
	undefined field_0x529a;
	undefined field_0x529b;
	undefined field_0x529c;
	undefined field_0x529d;
	undefined field_0x529e;
	undefined field_0x529f;
	undefined field_0x52a0;
	undefined field_0x52a1;
	undefined field_0x52a2;
	undefined field_0x52a3;
	undefined field_0x52a4;
	undefined field_0x52a5;
	undefined field_0x52a6;
	undefined field_0x52a7;
	undefined field_0x52a8;
	undefined field_0x52a9;
	undefined field_0x52aa;
	undefined field_0x52ab;
	undefined field_0x52ac;
	undefined field_0x52ad;
	undefined field_0x52ae;
	undefined field_0x52af;
	undefined field_0x52b0;
	undefined field_0x52b1;
	undefined field_0x52b2;
	undefined field_0x52b3;
	undefined field_0x52b4;
	undefined field_0x52b5;
	undefined field_0x52b6;
	undefined field_0x52b7;
	undefined field_0x52b8;
	undefined field_0x52b9;
	undefined field_0x52ba;
	undefined field_0x52bb;
	undefined field_0x52bc;
	undefined field_0x52bd;
	undefined field_0x52be;
	undefined field_0x52bf;
	undefined field_0x52c0;
	undefined field_0x52c1;
	undefined field_0x52c2;
	undefined field_0x52c3;
	undefined field_0x52c4;
	undefined field_0x52c5;
	undefined field_0x52c6;
	undefined field_0x52c7;
	undefined field_0x52c8;
	undefined field_0x52c9;
	undefined field_0x52ca;
	undefined field_0x52cb;
	undefined field_0x52cc;
	undefined field_0x52cd;
	undefined field_0x52ce;
	undefined field_0x52cf;
	undefined field_0x52d0;
	undefined field_0x52d1;
	undefined field_0x52d2;
	undefined field_0x52d3;
	undefined field_0x52d4;
	undefined field_0x52d5;
	undefined field_0x52d6;
	undefined field_0x52d7;
	undefined field_0x52d8;
	undefined field_0x52d9;
	undefined field_0x52da;
	undefined field_0x52db;
	undefined field_0x52dc;
	undefined field_0x52dd;
	undefined field_0x52de;
	undefined field_0x52df;
	undefined field_0x52e0;
	undefined field_0x52e1;
	undefined field_0x52e2;
	undefined field_0x52e3;
	undefined field_0x52e4;
	undefined field_0x52e5;
	undefined field_0x52e6;
	undefined field_0x52e7;
	undefined field_0x52e8;
	undefined field_0x52e9;
	undefined field_0x52ea;
	undefined field_0x52eb;
	undefined field_0x52ec;
	undefined field_0x52ed;
	undefined field_0x52ee;
	undefined field_0x52ef;
	undefined field_0x52f0;
	undefined field_0x52f1;
	undefined field_0x52f2;
	undefined field_0x52f3;
	undefined field_0x52f4;
	undefined field_0x52f5;
	undefined field_0x52f6;
	undefined field_0x52f7;
	undefined field_0x52f8;
	undefined field_0x52f9;
	undefined field_0x52fa;
	undefined field_0x52fb;
	undefined field_0x52fc;
	undefined field_0x52fd;
	undefined field_0x52fe;
	undefined field_0x52ff;
	undefined field_0x5300;
	undefined field_0x5301;
	undefined field_0x5302;
	undefined field_0x5303;
	undefined field_0x5304;
	undefined field_0x5305;
	undefined field_0x5306;
	undefined field_0x5307;
	undefined field_0x5308;
	undefined field_0x5309;
	undefined field_0x530a;
	undefined field_0x530b;
	undefined field_0x530c;
	undefined field_0x530d;
	undefined field_0x530e;
	undefined field_0x530f;
	undefined field_0x5310;
	undefined field_0x5311;
	undefined field_0x5312;
	undefined field_0x5313;
	undefined field_0x5314;
	undefined field_0x5315;
	undefined field_0x5316;
	undefined field_0x5317;
	undefined field_0x5318;
	undefined field_0x5319;
	undefined field_0x531a;
	undefined field_0x531b;
	undefined field_0x531c;
	undefined field_0x531d;
	undefined field_0x531e;
	undefined field_0x531f;
	undefined field_0x5320;
	undefined field_0x5321;
	undefined field_0x5322;
	undefined field_0x5323;
	undefined field_0x5324;
	undefined field_0x5325;
	undefined field_0x5326;
	undefined field_0x5327;
	undefined field_0x5328;
	undefined field_0x5329;
	undefined field_0x532a;
	undefined field_0x532b;
	undefined field_0x532c;
	undefined field_0x532d;
	undefined field_0x532e;
	undefined field_0x532f;
	undefined field_0x5330;
	undefined field_0x5331;
	undefined field_0x5332;
	undefined field_0x5333;
	undefined field_0x5334;
	undefined field_0x5335;
	undefined field_0x5336;
	undefined field_0x5337;
	undefined field_0x5338;
	undefined field_0x5339;
	undefined field_0x533a;
	undefined field_0x533b;
	undefined field_0x533c;
	undefined field_0x533d;
	undefined field_0x533e;
	undefined field_0x533f;
	undefined field_0x5340;
	undefined field_0x5341;
	undefined field_0x5342;
	undefined field_0x5343;
	undefined field_0x5344;
	undefined field_0x5345;
	undefined field_0x5346;
	undefined field_0x5347;
	undefined field_0x5348;
	undefined field_0x5349;
	undefined field_0x534a;
	undefined field_0x534b;
	undefined field_0x534c;
	undefined field_0x534d;
	undefined field_0x534e;
	undefined field_0x534f;
	undefined field_0x5350;
	undefined field_0x5351;
	undefined field_0x5352;
	undefined field_0x5353;
	undefined field_0x5354;
	undefined field_0x5355;
	undefined field_0x5356;
	undefined field_0x5357;
	undefined field_0x5358;
	undefined field_0x5359;
	undefined field_0x535a;
	undefined field_0x535b;
	undefined field_0x535c;
	undefined field_0x535d;
	undefined field_0x535e;
	undefined field_0x535f;
	undefined field_0x5360;
	undefined field_0x5361;
	undefined field_0x5362;
	undefined field_0x5363;
	undefined field_0x5364;
	undefined field_0x5365;
	undefined field_0x5366;
	undefined field_0x5367;
	undefined field_0x5368;
	undefined field_0x5369;
	undefined field_0x536a;
	undefined field_0x536b;
	undefined field_0x536c;
	undefined field_0x536d;
	undefined field_0x536e;
	undefined field_0x536f;
	undefined field_0x5370;
	undefined field_0x5371;
	undefined field_0x5372;
	undefined field_0x5373;
	undefined field_0x5374;
	undefined field_0x5375;
	undefined field_0x5376;
	undefined field_0x5377;
	undefined field_0x5378;
	undefined field_0x5379;
	undefined field_0x537a;
	undefined field_0x537b;
	undefined field_0x537c;
	undefined field_0x537d;
	undefined field_0x537e;
	undefined field_0x537f;
	undefined field_0x5380;
	undefined field_0x5381;
	undefined field_0x5382;
	undefined field_0x5383;
	undefined field_0x5384;
	undefined field_0x5385;
	undefined field_0x5386;
	undefined field_0x5387;
	undefined field_0x5388;
	undefined field_0x5389;
	undefined field_0x538a;
	undefined field_0x538b;
	undefined field_0x538c;
	undefined field_0x538d;
	undefined field_0x538e;
	undefined field_0x538f;
	undefined field_0x5390;
	undefined field_0x5391;
	undefined field_0x5392;
	undefined field_0x5393;
	undefined field_0x5394;
	undefined field_0x5395;
	undefined field_0x5396;
	undefined field_0x5397;
	undefined field_0x5398;
	undefined field_0x5399;
	undefined field_0x539a;
	undefined field_0x539b;
	undefined field_0x539c;
	undefined field_0x539d;
	undefined field_0x539e;
	undefined field_0x539f;
	undefined field_0x53a0;
	undefined field_0x53a1;
	undefined field_0x53a2;
	undefined field_0x53a3;
	undefined field_0x53a4;
	undefined field_0x53a5;
	undefined field_0x53a6;
	undefined field_0x53a7;
	undefined field_0x53a8;
	undefined field_0x53a9;
	undefined field_0x53aa;
	undefined field_0x53ab;
	undefined field_0x53ac;
	undefined field_0x53ad;
	undefined field_0x53ae;
	undefined field_0x53af;
	undefined field_0x53b0;
	undefined field_0x53b1;
	undefined field_0x53b2;
	undefined field_0x53b3;
	undefined field_0x53b4;
	undefined field_0x53b5;
	undefined field_0x53b6;
	undefined field_0x53b7;
	undefined field_0x53b8;
	undefined field_0x53b9;
	undefined field_0x53ba;
	undefined field_0x53bb;
	undefined field_0x53bc;
	undefined field_0x53bd;
	undefined field_0x53be;
	undefined field_0x53bf;
	undefined field_0x53c0;
	undefined field_0x53c1;
	undefined field_0x53c2;
	undefined field_0x53c3;
	undefined field_0x53c4;
	undefined field_0x53c5;
	undefined field_0x53c6;
	undefined field_0x53c7;
	undefined field_0x53c8;
	undefined field_0x53c9;
	undefined field_0x53ca;
	undefined field_0x53cb;
	undefined field_0x53cc;
	undefined field_0x53cd;
	undefined field_0x53ce;
	undefined field_0x53cf;
	undefined field_0x53d0;
	undefined field_0x53d1;
	undefined field_0x53d2;
	undefined field_0x53d3;
	undefined field_0x53d4;
	undefined field_0x53d5;
	undefined field_0x53d6;
	undefined field_0x53d7;
	undefined field_0x53d8;
	undefined field_0x53d9;
	undefined field_0x53da;
	undefined field_0x53db;
	undefined field_0x53dc;
	undefined field_0x53dd;
	undefined field_0x53de;
	undefined field_0x53df;
	undefined field_0x53e0;
	undefined field_0x53e1;
	undefined field_0x53e2;
	undefined field_0x53e3;
	undefined field_0x53e4;
	undefined field_0x53e5;
	undefined field_0x53e6;
	undefined field_0x53e7;
	undefined field_0x53e8;
	undefined field_0x53e9;
	undefined field_0x53ea;
	undefined field_0x53eb;
	undefined field_0x53ec;
	undefined field_0x53ed;
	undefined field_0x53ee;
	undefined field_0x53ef;
	undefined field_0x53f0;
	undefined field_0x53f1;
	undefined field_0x53f2;
	undefined field_0x53f3;
	undefined field_0x53f4;
	undefined field_0x53f5;
	undefined field_0x53f6;
	undefined field_0x53f7;
	undefined field_0x53f8;
	undefined field_0x53f9;
	undefined field_0x53fa;
	undefined field_0x53fb;
	undefined field_0x53fc;
	undefined field_0x53fd;
	undefined field_0x53fe;
	undefined field_0x53ff;
	undefined field_0x5400;
	undefined field_0x5401;
	undefined field_0x5402;
	undefined field_0x5403;
	undefined field_0x5404;
	undefined field_0x5405;
	undefined field_0x5406;
	undefined field_0x5407;
	undefined field_0x5408;
	undefined field_0x5409;
	undefined field_0x540a;
	undefined field_0x540b;
	undefined field_0x540c;
	undefined field_0x540d;
	undefined field_0x540e;
	undefined field_0x540f;
	undefined field_0x5410;
	undefined field_0x5411;
	undefined field_0x5412;
	undefined field_0x5413;
	undefined field_0x5414;
	undefined field_0x5415;
	undefined field_0x5416;
	undefined field_0x5417;
	undefined field_0x5418;
	undefined field_0x5419;
	undefined field_0x541a;
	undefined field_0x541b;
	undefined field_0x541c;
	undefined field_0x541d;
	undefined field_0x541e;
	undefined field_0x541f;
	undefined field_0x5420;
	undefined field_0x5421;
	undefined field_0x5422;
	undefined field_0x5423;
	undefined field_0x5424;
	undefined field_0x5425;
	undefined field_0x5426;
	undefined field_0x5427;
	undefined field_0x5428;
	undefined field_0x5429;
	undefined field_0x542a;
	undefined field_0x542b;
	undefined field_0x542c;
	undefined field_0x542d;
	undefined field_0x542e;
	undefined field_0x542f;
	undefined field_0x5430;
	undefined field_0x5431;
	undefined field_0x5432;
	undefined field_0x5433;
	undefined field_0x5434;
	undefined field_0x5435;
	undefined field_0x5436;
	undefined field_0x5437;
	undefined field_0x5438;
	undefined field_0x5439;
	undefined field_0x543a;
	undefined field_0x543b;
	undefined field_0x543c;
	undefined field_0x543d;
	undefined field_0x543e;
	undefined field_0x543f;
	undefined field_0x5440;
	undefined field_0x5441;
	undefined field_0x5442;
	undefined field_0x5443;
	undefined field_0x5444;
	undefined field_0x5445;
	undefined field_0x5446;
	undefined field_0x5447;
	undefined field_0x5448;
	undefined field_0x5449;
	undefined field_0x544a;
	undefined field_0x544b;
	undefined field_0x544c;
	undefined field_0x544d;
	undefined field_0x544e;
	undefined field_0x544f;
	undefined field_0x5450;
	undefined field_0x5451;
	undefined field_0x5452;
	undefined field_0x5453;
	undefined field_0x5454;
	undefined field_0x5455;
	undefined field_0x5456;
	undefined field_0x5457;
	undefined field_0x5458;
	undefined field_0x5459;
	undefined field_0x545a;
	undefined field_0x545b;
	undefined field_0x545c;
	undefined field_0x545d;
	undefined field_0x545e;
	undefined field_0x545f;
	undefined field_0x5460;
	undefined field_0x5461;
	undefined field_0x5462;
	undefined field_0x5463;
	undefined field_0x5464;
	undefined field_0x5465;
	undefined field_0x5466;
	undefined field_0x5467;
	undefined field_0x5468;
	undefined field_0x5469;
	undefined field_0x546a;
	undefined field_0x546b;
	undefined field_0x546c;
	undefined field_0x546d;
	undefined field_0x546e;
	undefined field_0x546f;
	undefined field_0x5470;
	undefined field_0x5471;
	undefined field_0x5472;
	undefined field_0x5473;
	undefined field_0x5474;
	undefined field_0x5475;
	undefined field_0x5476;
	undefined field_0x5477;
	undefined field_0x5478;
	undefined field_0x5479;
	undefined field_0x547a;
	undefined field_0x547b;
	undefined field_0x547c;
	undefined field_0x547d;
	undefined field_0x547e;
	undefined field_0x547f;
	undefined field_0x5480;
	undefined field_0x5481;
	undefined field_0x5482;
	undefined field_0x5483;
	undefined field_0x5484;
	undefined field_0x5485;
	undefined field_0x5486;
	undefined field_0x5487;
	undefined field_0x5488;
	undefined field_0x5489;
	undefined field_0x548a;
	undefined field_0x548b;
	undefined field_0x548c;
	undefined field_0x548d;
	undefined field_0x548e;
	undefined field_0x548f;
	undefined field_0x5490;
	undefined field_0x5491;
	undefined field_0x5492;
	undefined field_0x5493;
	undefined field_0x5494;
	undefined field_0x5495;
	undefined field_0x5496;
	undefined field_0x5497;
	undefined field_0x5498;
	undefined field_0x5499;
	undefined field_0x549a;
	undefined field_0x549b;
	undefined field_0x549c;
	undefined field_0x549d;
	undefined field_0x549e;
	undefined field_0x549f;
	undefined field_0x54a0;
	undefined field_0x54a1;
	undefined field_0x54a2;
	undefined field_0x54a3;
	undefined field_0x54a4;
	undefined field_0x54a5;
	undefined field_0x54a6;
	undefined field_0x54a7;
	undefined field_0x54a8;
	undefined field_0x54a9;
	undefined field_0x54aa;
	undefined field_0x54ab;
	undefined field_0x54ac;
	undefined field_0x54ad;
	undefined field_0x54ae;
	undefined field_0x54af;
	undefined field_0x54b0;
	undefined field_0x54b1;
	undefined field_0x54b2;
	undefined field_0x54b3;
	undefined field_0x54b4;
	undefined field_0x54b5;
	undefined field_0x54b6;
	undefined field_0x54b7;
	undefined field_0x54b8;
	undefined field_0x54b9;
	undefined field_0x54ba;
	undefined field_0x54bb;
	undefined field_0x54bc;
	undefined field_0x54bd;
	undefined field_0x54be;
	undefined field_0x54bf;
	undefined field_0x54c0;
	undefined field_0x54c1;
	undefined field_0x54c2;
	undefined field_0x54c3;
	undefined field_0x54c4;
	undefined field_0x54c5;
	undefined field_0x54c6;
	undefined field_0x54c7;
	undefined field_0x54c8;
	undefined field_0x54c9;
	undefined field_0x54ca;
	undefined field_0x54cb;
	undefined field_0x54cc;
	undefined field_0x54cd;
	undefined field_0x54ce;
	undefined field_0x54cf;
	undefined field_0x54d0;
	undefined field_0x54d1;
	undefined field_0x54d2;
	undefined field_0x54d3;
	undefined field_0x54d4;
	undefined field_0x54d5;
	undefined field_0x54d6;
	undefined field_0x54d7;
	undefined field_0x54d8;
	undefined field_0x54d9;
	undefined field_0x54da;
	undefined field_0x54db;
	undefined field_0x54dc;
	undefined field_0x54dd;
	undefined field_0x54de;
	undefined field_0x54df;
	undefined field_0x54e0;
	undefined field_0x54e1;
	undefined field_0x54e2;
	undefined field_0x54e3;
	undefined field_0x54e4;
	undefined field_0x54e5;
	undefined field_0x54e6;
	undefined field_0x54e7;
	undefined field_0x54e8;
	undefined field_0x54e9;
	undefined field_0x54ea;
	undefined field_0x54eb;
	undefined field_0x54ec;
	undefined field_0x54ed;
	undefined field_0x54ee;
	undefined field_0x54ef;
	undefined field_0x54f0;
	undefined field_0x54f1;
	undefined field_0x54f2;
	undefined field_0x54f3;
	undefined field_0x54f4;
	undefined field_0x54f5;
	undefined field_0x54f6;
	undefined field_0x54f7;
	undefined field_0x54f8;
	undefined field_0x54f9;
	undefined field_0x54fa;
	undefined field_0x54fb;
	undefined field_0x54fc;
	undefined field_0x54fd;
	undefined field_0x54fe;
	undefined field_0x54ff;
	undefined field_0x5500;
	undefined field_0x5501;
	undefined field_0x5502;
	undefined field_0x5503;
	undefined field_0x5504;
	undefined field_0x5505;
	undefined field_0x5506;
	undefined field_0x5507;
	undefined field_0x5508;
	undefined field_0x5509;
	undefined field_0x550a;
	undefined field_0x550b;
	undefined field_0x550c;
	undefined field_0x550d;
	undefined field_0x550e;
	undefined field_0x550f;
	undefined field_0x5510;
	undefined field_0x5511;
	undefined field_0x5512;
	undefined field_0x5513;
	undefined field_0x5514;
	undefined field_0x5515;
	undefined field_0x5516;
	undefined field_0x5517;
	undefined field_0x5518;
	undefined field_0x5519;
	undefined field_0x551a;
	undefined field_0x551b;
	undefined field_0x551c;
	undefined field_0x551d;
	undefined field_0x551e;
	undefined field_0x551f;
	undefined field_0x5520;
	undefined field_0x5521;
	undefined field_0x5522;
	undefined field_0x5523;
	undefined field_0x5524;
	undefined field_0x5525;
	undefined field_0x5526;
	undefined field_0x5527;
	undefined field_0x5528;
	undefined field_0x5529;
	undefined field_0x552a;
	undefined field_0x552b;
	undefined field_0x552c;
	undefined field_0x552d;
	undefined field_0x552e;
	undefined field_0x552f;
	undefined field_0x5530;
	undefined field_0x5531;
	undefined field_0x5532;
	undefined field_0x5533;
	undefined field_0x5534;
	undefined field_0x5535;
	undefined field_0x5536;
	undefined field_0x5537;
	undefined field_0x5538;
	undefined field_0x5539;
	undefined field_0x553a;
	undefined field_0x553b;
	undefined field_0x553c;
	undefined field_0x553d;
	undefined field_0x553e;
	undefined field_0x553f;
	undefined field_0x5540;
	undefined field_0x5541;
	undefined field_0x5542;
	undefined field_0x5543;
	undefined field_0x5544;
	undefined field_0x5545;
	undefined field_0x5546;
	undefined field_0x5547;
	undefined field_0x5548;
	undefined field_0x5549;
	undefined field_0x554a;
	undefined field_0x554b;
	undefined field_0x554c;
	undefined field_0x554d;
	undefined field_0x554e;
	undefined field_0x554f;
	undefined field_0x5550;
	undefined field_0x5551;
	undefined field_0x5552;
	undefined field_0x5553;
	undefined field_0x5554;
	undefined field_0x5555;
	undefined field_0x5556;
	undefined field_0x5557;
	undefined field_0x5558;
	undefined field_0x5559;
	undefined field_0x555a;
	undefined field_0x555b;
	undefined field_0x555c;
	undefined field_0x555d;
	undefined field_0x555e;
	undefined field_0x555f;
	undefined field_0x5560;
	undefined field_0x5561;
	undefined field_0x5562;
	undefined field_0x5563;
	undefined field_0x5564;
	undefined field_0x5565;
	undefined field_0x5566;
	undefined field_0x5567;
	undefined field_0x5568;
	undefined field_0x5569;
	undefined field_0x556a;
	undefined field_0x556b;
	undefined field_0x556c;
	undefined field_0x556d;
	undefined field_0x556e;
	undefined field_0x556f;
	undefined field_0x5570;
	undefined field_0x5571;
	undefined field_0x5572;
	undefined field_0x5573;
	undefined field_0x5574;
	undefined field_0x5575;
	undefined field_0x5576;
	undefined field_0x5577;
	undefined field_0x5578;
	undefined field_0x5579;
	undefined field_0x557a;
	undefined field_0x557b;
	undefined field_0x557c;
	undefined field_0x557d;
	undefined field_0x557e;
	undefined field_0x557f;
	undefined field_0x5580;
	undefined field_0x5581;
	undefined field_0x5582;
	undefined field_0x5583;
	undefined field_0x5584;
	undefined field_0x5585;
	undefined field_0x5586;
	undefined field_0x5587;
	undefined field_0x5588;
	undefined field_0x5589;
	undefined field_0x558a;
	undefined field_0x558b;
	undefined field_0x558c;
	undefined field_0x558d;
	undefined field_0x558e;
	undefined field_0x558f;
	undefined field_0x5590;
	undefined field_0x5591;
	undefined field_0x5592;
	undefined field_0x5593;
	undefined field_0x5594;
	undefined field_0x5595;
	undefined field_0x5596;
	undefined field_0x5597;
	undefined field_0x5598;
	undefined field_0x5599;
	undefined field_0x559a;
	undefined field_0x559b;
	undefined field_0x559c;
	undefined field_0x559d;
	undefined field_0x559e;
	undefined field_0x559f;
	undefined field_0x55a0;
	undefined field_0x55a1;
	undefined field_0x55a2;
	undefined field_0x55a3;
	undefined field_0x55a4;
	undefined field_0x55a5;
	undefined field_0x55a6;
	undefined field_0x55a7;
	undefined field_0x55a8;
	undefined field_0x55a9;
	undefined field_0x55aa;
	undefined field_0x55ab;
	undefined field_0x55ac;
	undefined field_0x55ad;
	undefined field_0x55ae;
	undefined field_0x55af;
	undefined field_0x55b0;
	undefined field_0x55b1;
	undefined field_0x55b2;
	undefined field_0x55b3;
	undefined field_0x55b4;
	undefined field_0x55b5;
	undefined field_0x55b6;
	undefined field_0x55b7;
	undefined field_0x55b8;
	undefined field_0x55b9;
	undefined field_0x55ba;
	undefined field_0x55bb;
	undefined field_0x55bc;
	undefined field_0x55bd;
	undefined field_0x55be;
	undefined field_0x55bf;
	undefined field_0x55c0;
	undefined field_0x55c1;
	undefined field_0x55c2;
	undefined field_0x55c3;
	undefined field_0x55c4;
	undefined field_0x55c5;
	undefined field_0x55c6;
	undefined field_0x55c7;
	undefined field_0x55c8;
	undefined field_0x55c9;
	undefined field_0x55ca;
	undefined field_0x55cb;
	undefined field_0x55cc;
	undefined field_0x55cd;
	undefined field_0x55ce;
	undefined field_0x55cf;
	undefined field_0x55d0;
	undefined field_0x55d1;
	undefined field_0x55d2;
	undefined field_0x55d3;
	undefined field_0x55d4;
	undefined field_0x55d5;
	undefined field_0x55d6;
	undefined field_0x55d7;
	undefined field_0x55d8;
	undefined field_0x55d9;
	undefined field_0x55da;
	undefined field_0x55db;
	undefined field_0x55dc;
	undefined field_0x55dd;
	undefined field_0x55de;
	undefined field_0x55df;
	undefined field_0x55e0;
	undefined field_0x55e1;
	undefined field_0x55e2;
	undefined field_0x55e3;
	undefined field_0x55e4;
	undefined field_0x55e5;
	undefined field_0x55e6;
	undefined field_0x55e7;
	undefined field_0x55e8;
	undefined field_0x55e9;
	undefined field_0x55ea;
	undefined field_0x55eb;
	undefined field_0x55ec;
	undefined field_0x55ed;
	undefined field_0x55ee;
	undefined field_0x55ef;
	undefined field_0x55f0;
	undefined field_0x55f1;
	undefined field_0x55f2;
	undefined field_0x55f3;
	undefined field_0x55f4;
	undefined field_0x55f5;
	undefined field_0x55f6;
	undefined field_0x55f7;
	undefined field_0x55f8;
	undefined field_0x55f9;
	undefined field_0x55fa;
	undefined field_0x55fb;
	undefined field_0x55fc;
	undefined field_0x55fd;
	undefined field_0x55fe;
	undefined field_0x55ff;
	undefined field_0x5600;
	undefined field_0x5601;
	undefined field_0x5602;
	undefined field_0x5603;
	undefined field_0x5604;
	undefined field_0x5605;
	undefined field_0x5606;
	undefined field_0x5607;
	undefined field_0x5608;
	undefined field_0x5609;
	undefined field_0x560a;
	undefined field_0x560b;
	undefined field_0x560c;
	undefined field_0x560d;
	undefined field_0x560e;
	undefined field_0x560f;
	undefined field_0x5610;
	undefined field_0x5611;
	undefined field_0x5612;
	undefined field_0x5613;
	undefined field_0x5614;
	undefined field_0x5615;
	undefined field_0x5616;
	undefined field_0x5617;
	undefined field_0x5618;
	undefined field_0x5619;
	undefined field_0x561a;
	undefined field_0x561b;
	undefined field_0x561c;
	undefined field_0x561d;
	undefined field_0x561e;
	undefined field_0x561f;
	undefined field_0x5620;
	undefined field_0x5621;
	undefined field_0x5622;
	undefined field_0x5623;
	undefined field_0x5624;
	undefined field_0x5625;
	undefined field_0x5626;
	undefined field_0x5627;
	undefined field_0x5628;
	undefined field_0x5629;
	undefined field_0x562a;
	undefined field_0x562b;
	undefined field_0x562c;
	undefined field_0x562d;
	undefined field_0x562e;
	undefined field_0x562f;
	undefined field_0x5630;
	undefined field_0x5631;
	undefined field_0x5632;
	undefined field_0x5633;
	undefined field_0x5634;
	undefined field_0x5635;
	undefined field_0x5636;
	undefined field_0x5637;
	undefined field_0x5638;
	undefined field_0x5639;
	undefined field_0x563a;
	undefined field_0x563b;
	undefined field_0x563c;
	undefined field_0x563d;
	undefined field_0x563e;
	undefined field_0x563f;
	undefined field_0x5640;
	undefined field_0x5641;
	undefined field_0x5642;
	undefined field_0x5643;
	undefined field_0x5644;
	undefined field_0x5645;
	undefined field_0x5646;
	undefined field_0x5647;
	undefined field_0x5648;
	undefined field_0x5649;
	undefined field_0x564a;
	undefined field_0x564b;
	undefined field_0x564c;
	undefined field_0x564d;
	undefined field_0x564e;
	undefined field_0x564f;
	undefined field_0x5650;
	undefined field_0x5651;
	undefined field_0x5652;
	undefined field_0x5653;
	undefined field_0x5654;
	undefined field_0x5655;
	undefined field_0x5656;
	undefined field_0x5657;
	undefined field_0x5658;
	undefined field_0x5659;
	undefined field_0x565a;
	undefined field_0x565b;
	undefined field_0x565c;
	undefined field_0x565d;
	undefined field_0x565e;
	undefined field_0x565f;
	undefined field_0x5660;
	undefined field_0x5661;
	undefined field_0x5662;
	undefined field_0x5663;
	undefined field_0x5664;
	undefined field_0x5665;
	undefined field_0x5666;
	undefined field_0x5667;
	undefined field_0x5668;
	undefined field_0x5669;
	undefined field_0x566a;
	undefined field_0x566b;
	undefined field_0x566c;
	undefined field_0x566d;
	undefined field_0x566e;
	undefined field_0x566f;
	undefined field_0x5670;
	undefined field_0x5671;
	undefined field_0x5672;
	undefined field_0x5673;
	undefined field_0x5674;
	undefined field_0x5675;
	undefined field_0x5676;
	undefined field_0x5677;
	undefined field_0x5678;
	undefined field_0x5679;
	undefined field_0x567a;
	undefined field_0x567b;
	undefined field_0x567c;
	undefined field_0x567d;
	undefined field_0x567e;
	undefined field_0x567f;
	undefined field_0x5680;
	undefined field_0x5681;
	undefined field_0x5682;
	undefined field_0x5683;
	undefined field_0x5684;
	undefined field_0x5685;
	undefined field_0x5686;
	undefined field_0x5687;
	undefined field_0x5688;
	undefined field_0x5689;
	undefined field_0x568a;
	undefined field_0x568b;
	undefined field_0x568c;
	undefined field_0x568d;
	undefined field_0x568e;
	undefined field_0x568f;
	undefined field_0x5690;
	undefined field_0x5691;
	undefined field_0x5692;
	undefined field_0x5693;
	undefined field_0x5694;
	undefined field_0x5695;
	undefined field_0x5696;
	undefined field_0x5697;
	undefined field_0x5698;
	undefined field_0x5699;
	undefined field_0x569a;
	undefined field_0x569b;
	undefined field_0x569c;
	undefined field_0x569d;
	undefined field_0x569e;
	undefined field_0x569f;
	undefined field_0x56a0;
	undefined field_0x56a1;
	undefined field_0x56a2;
	undefined field_0x56a3;
	undefined field_0x56a4;
	undefined field_0x56a5;
	undefined field_0x56a6;
	undefined field_0x56a7;
	undefined field_0x56a8;
	undefined field_0x56a9;
	undefined field_0x56aa;
	undefined field_0x56ab;
	undefined field_0x56ac;
	undefined field_0x56ad;
	undefined field_0x56ae;
	undefined field_0x56af;
	undefined field_0x56b0;
	undefined field_0x56b1;
	undefined field_0x56b2;
	undefined field_0x56b3;
	undefined field_0x56b4;
	undefined field_0x56b5;
	undefined field_0x56b6;
	undefined field_0x56b7;
	undefined field_0x56b8;
	undefined field_0x56b9;
	undefined field_0x56ba;
	undefined field_0x56bb;
	undefined field_0x56bc;
	undefined field_0x56bd;
	undefined field_0x56be;
	undefined field_0x56bf;
	undefined field_0x56c0;
	undefined field_0x56c1;
	undefined field_0x56c2;
	undefined field_0x56c3;
	undefined field_0x56c4;
	undefined field_0x56c5;
	undefined field_0x56c6;
	undefined field_0x56c7;
	undefined field_0x56c8;
	undefined field_0x56c9;
	undefined field_0x56ca;
	undefined field_0x56cb;
	undefined field_0x56cc;
	undefined field_0x56cd;
	undefined field_0x56ce;
	undefined field_0x56cf;
	undefined field_0x56d0;
	undefined field_0x56d1;
	undefined field_0x56d2;
	undefined field_0x56d3;
	undefined field_0x56d4;
	undefined field_0x56d5;
	undefined field_0x56d6;
	undefined field_0x56d7;
	undefined field_0x56d8;
	undefined field_0x56d9;
	undefined field_0x56da;
	undefined field_0x56db;
	undefined field_0x56dc;
	undefined field_0x56dd;
	undefined field_0x56de;
	undefined field_0x56df;
	undefined field_0x56e0;
	undefined field_0x56e1;
	undefined field_0x56e2;
	undefined field_0x56e3;
	undefined field_0x56e4;
	undefined field_0x56e5;
	undefined field_0x56e6;
	undefined field_0x56e7;
	undefined field_0x56e8;
	undefined field_0x56e9;
	undefined field_0x56ea;
	undefined field_0x56eb;
	undefined field_0x56ec;
	undefined field_0x56ed;
	undefined field_0x56ee;
	undefined field_0x56ef;
	undefined field_0x56f0;
	undefined field_0x56f1;
	undefined field_0x56f2;
	undefined field_0x56f3;
	undefined field_0x56f4;
	undefined field_0x56f5;
	undefined field_0x56f6;
	undefined field_0x56f7;
	undefined field_0x56f8;
	undefined field_0x56f9;
	undefined field_0x56fa;
	undefined field_0x56fb;
	undefined field_0x56fc;
	undefined field_0x56fd;
	undefined field_0x56fe;
	undefined field_0x56ff;
	undefined field_0x5700;
	undefined field_0x5701;
	undefined field_0x5702;
	undefined field_0x5703;
	undefined field_0x5704;
	undefined field_0x5705;
	undefined field_0x5706;
	undefined field_0x5707;
	undefined field_0x5708;
	undefined field_0x5709;
	undefined field_0x570a;
	undefined field_0x570b;
	undefined field_0x570c;
	undefined field_0x570d;
	undefined field_0x570e;
	undefined field_0x570f;
	undefined field_0x5710;
	undefined field_0x5711;
	undefined field_0x5712;
	undefined field_0x5713;
	undefined field_0x5714;
	undefined field_0x5715;
	undefined field_0x5716;
	undefined field_0x5717;
	undefined field_0x5718;
	undefined field_0x5719;
	undefined field_0x571a;
	undefined field_0x571b;
	undefined field_0x571c;
	undefined field_0x571d;
	undefined field_0x571e;
	undefined field_0x571f;
	undefined field_0x5720;
	undefined field_0x5721;
	undefined field_0x5722;
	undefined field_0x5723;
	undefined field_0x5724;
	undefined field_0x5725;
	undefined field_0x5726;
	undefined field_0x5727;
	undefined field_0x5728;
	undefined field_0x5729;
	undefined field_0x572a;
	undefined field_0x572b;
	undefined field_0x572c;
	undefined field_0x572d;
	undefined field_0x572e;
	undefined field_0x572f;
	undefined field_0x5730;
	undefined field_0x5731;
	undefined field_0x5732;
	undefined field_0x5733;
	undefined field_0x5734;
	undefined field_0x5735;
	undefined field_0x5736;
	undefined field_0x5737;
	undefined field_0x5738;
	undefined field_0x5739;
	undefined field_0x573a;
	undefined field_0x573b;
	undefined field_0x573c;
	undefined field_0x573d;
	undefined field_0x573e;
	undefined field_0x573f;
	undefined field_0x5740;
	undefined field_0x5741;
	undefined field_0x5742;
	undefined field_0x5743;
	undefined field_0x5744;
	undefined field_0x5745;
	undefined field_0x5746;
	undefined field_0x5747;
	undefined field_0x5748;
	undefined field_0x5749;
	undefined field_0x574a;
	undefined field_0x574b;
	undefined field_0x574c;
	undefined field_0x574d;
	undefined field_0x574e;
	undefined field_0x574f;
	undefined field_0x5750;
	undefined field_0x5751;
	undefined field_0x5752;
	undefined field_0x5753;
	undefined field_0x5754;
	undefined field_0x5755;
	undefined field_0x5756;
	undefined field_0x5757;
	undefined field_0x5758;
	undefined field_0x5759;
	undefined field_0x575a;
	undefined field_0x575b;
	undefined field_0x575c;
	undefined field_0x575d;
	undefined field_0x575e;
	undefined field_0x575f;
	undefined field_0x5760;
	undefined field_0x5761;
	undefined field_0x5762;
	undefined field_0x5763;
	undefined field_0x5764;
	undefined field_0x5765;
	undefined field_0x5766;
	undefined field_0x5767;
	undefined field_0x5768;
	undefined field_0x5769;
	undefined field_0x576a;
	undefined field_0x576b;
	undefined field_0x576c;
	undefined field_0x576d;
	undefined field_0x576e;
	undefined field_0x576f;
	undefined field_0x5770;
	undefined field_0x5771;
	undefined field_0x5772;
	undefined field_0x5773;
	undefined field_0x5774;
	undefined field_0x5775;
	undefined field_0x5776;
	undefined field_0x5777;
	undefined field_0x5778;
	undefined field_0x5779;
	undefined field_0x577a;
	undefined field_0x577b;
	undefined field_0x577c;
	undefined field_0x577d;
	undefined field_0x577e;
	undefined field_0x577f;
	undefined field_0x5780;
	undefined field_0x5781;
	undefined field_0x5782;
	undefined field_0x5783;
	undefined field_0x5784;
	undefined field_0x5785;
	undefined field_0x5786;
	undefined field_0x5787;
	undefined field_0x5788;
	undefined field_0x5789;
	undefined field_0x578a;
	undefined field_0x578b;
	undefined field_0x578c;
	undefined field_0x578d;
	undefined field_0x578e;
	undefined field_0x578f;
	undefined field_0x5790;
	undefined field_0x5791;
	undefined field_0x5792;
	undefined field_0x5793;
	undefined field_0x5794;
	undefined field_0x5795;
	undefined field_0x5796;
	undefined field_0x5797;
	undefined field_0x5798;
	undefined field_0x5799;
	undefined field_0x579a;
	undefined field_0x579b;
	undefined field_0x579c;
	undefined field_0x579d;
	undefined field_0x579e;
	undefined field_0x579f;
	undefined field_0x57a0;
	undefined field_0x57a1;
	undefined field_0x57a2;
	undefined field_0x57a3;
	undefined field_0x57a4;
	undefined field_0x57a5;
	undefined field_0x57a6;
	undefined field_0x57a7;
	undefined field_0x57a8;
	undefined field_0x57a9;
	undefined field_0x57aa;
	undefined field_0x57ab;
	undefined field_0x57ac;
	undefined field_0x57ad;
	undefined field_0x57ae;
	undefined field_0x57af;
	undefined field_0x57b0;
	undefined field_0x57b1;
	undefined field_0x57b2;
	undefined field_0x57b3;
	undefined field_0x57b4;
	undefined field_0x57b5;
	undefined field_0x57b6;
	undefined field_0x57b7;
	undefined field_0x57b8;
	undefined field_0x57b9;
	undefined field_0x57ba;
	undefined field_0x57bb;
	undefined field_0x57bc;
	undefined field_0x57bd;
	undefined field_0x57be;
	undefined field_0x57bf;
	undefined field_0x57c0;
	undefined field_0x57c1;
	undefined field_0x57c2;
	undefined field_0x57c3;
	undefined field_0x57c4;
	undefined field_0x57c5;
	undefined field_0x57c6;
	undefined field_0x57c7;
	undefined field_0x57c8;
	undefined field_0x57c9;
	undefined field_0x57ca;
	undefined field_0x57cb;
	undefined field_0x57cc;
	undefined field_0x57cd;
	undefined field_0x57ce;
	undefined field_0x57cf;
	undefined field_0x57d0;
	undefined field_0x57d1;
	undefined field_0x57d2;
	undefined field_0x57d3;
	undefined field_0x57d4;
	undefined field_0x57d5;
	undefined field_0x57d6;
	undefined field_0x57d7;
	undefined field_0x57d8;
	undefined field_0x57d9;
	undefined field_0x57da;
	undefined field_0x57db;
	undefined field_0x57dc;
	undefined field_0x57dd;
	undefined field_0x57de;
	undefined field_0x57df;
	undefined field_0x57e0;
	undefined field_0x57e1;
	undefined field_0x57e2;
	undefined field_0x57e3;
	undefined field_0x57e4;
	undefined field_0x57e5;
	undefined field_0x57e6;
	undefined field_0x57e7;
	undefined field_0x57e8;
	undefined field_0x57e9;
	undefined field_0x57ea;
	undefined field_0x57eb;
	undefined field_0x57ec;
	undefined field_0x57ed;
	undefined field_0x57ee;
	undefined field_0x57ef;
	undefined field_0x57f0;
	undefined field_0x57f1;
	undefined field_0x57f2;
	undefined field_0x57f3;
	undefined field_0x57f4;
	undefined field_0x57f5;
	undefined field_0x57f6;
	undefined field_0x57f7;
	undefined field_0x57f8;
	undefined field_0x57f9;
	undefined field_0x57fa;
	undefined field_0x57fb;
	undefined field_0x57fc;
	undefined field_0x57fd;
	undefined field_0x57fe;
	undefined field_0x57ff;
	undefined field_0x5800;
	undefined field_0x5801;
	undefined field_0x5802;
	undefined field_0x5803;
	undefined field_0x5804;
	undefined field_0x5805;
	undefined field_0x5806;
	undefined field_0x5807;
	undefined field_0x5808;
	undefined field_0x5809;
	undefined field_0x580a;
	undefined field_0x580b;
	undefined field_0x580c;
	undefined field_0x580d;
	undefined field_0x580e;
	undefined field_0x580f;
	undefined field_0x5810;
	undefined field_0x5811;
	undefined field_0x5812;
	undefined field_0x5813;
	undefined field_0x5814;
	undefined field_0x5815;
	undefined field_0x5816;
	undefined field_0x5817;
	undefined field_0x5818;
	undefined field_0x5819;
	undefined field_0x581a;
	undefined field_0x581b;
	undefined field_0x581c;
	undefined field_0x581d;
	undefined field_0x581e;
	undefined field_0x581f;
	undefined field_0x5820;
	undefined field_0x5821;
	undefined field_0x5822;
	undefined field_0x5823;
	undefined field_0x5824;
	undefined field_0x5825;
	undefined field_0x5826;
	undefined field_0x5827;
	undefined field_0x5828;
	undefined field_0x5829;
	undefined field_0x582a;
	undefined field_0x582b;
	undefined field_0x582c;
	undefined field_0x582d;
	undefined field_0x582e;
	undefined field_0x582f;
	undefined field_0x5830;
	undefined field_0x5831;
	undefined field_0x5832;
	undefined field_0x5833;
	undefined field_0x5834;
	undefined field_0x5835;
	undefined field_0x5836;
	undefined field_0x5837;
	undefined field_0x5838;
	undefined field_0x5839;
	undefined field_0x583a;
	undefined field_0x583b;
	undefined field_0x583c;
	undefined field_0x583d;
	undefined field_0x583e;
	undefined field_0x583f;
	undefined field_0x5840;
	undefined field_0x5841;
	undefined field_0x5842;
	undefined field_0x5843;
	undefined field_0x5844;
	undefined field_0x5845;
	undefined field_0x5846;
	undefined field_0x5847;
	undefined field_0x5848;
	undefined field_0x5849;
	undefined field_0x584a;
	undefined field_0x584b;
	undefined field_0x584c;
	undefined field_0x584d;
	undefined field_0x584e;
	undefined field_0x584f;
	undefined field_0x5850;
	undefined field_0x5851;
	undefined field_0x5852;
	undefined field_0x5853;
	undefined field_0x5854;
	undefined field_0x5855;
	undefined field_0x5856;
	undefined field_0x5857;
	undefined field_0x5858;
	undefined field_0x5859;
	undefined field_0x585a;
	undefined field_0x585b;
	undefined field_0x585c;
	undefined field_0x585d;
	undefined field_0x585e;
	undefined field_0x585f;
	undefined field_0x5860;
	undefined field_0x5861;
	undefined field_0x5862;
	undefined field_0x5863;
	undefined field_0x5864;
	undefined field_0x5865;
	undefined field_0x5866;
	undefined field_0x5867;
	undefined field_0x5868;
	undefined field_0x5869;
	undefined field_0x586a;
	undefined field_0x586b;
	undefined field_0x586c;
	undefined field_0x586d;
	undefined field_0x586e;
	undefined field_0x586f;
	undefined field_0x5870;
	undefined field_0x5871;
	undefined field_0x5872;
	undefined field_0x5873;
	undefined field_0x5874;
	undefined field_0x5875;
	undefined field_0x5876;
	undefined field_0x5877;
	undefined field_0x5878;
	undefined field_0x5879;
	undefined field_0x587a;
	undefined field_0x587b;
	undefined field_0x587c;
	undefined field_0x587d;
	undefined field_0x587e;
	undefined field_0x587f;
	undefined field_0x5880;
	undefined field_0x5881;
	undefined field_0x5882;
	undefined field_0x5883;
	undefined field_0x5884;
	undefined field_0x5885;
	undefined field_0x5886;
	undefined field_0x5887;
	undefined field_0x5888;
	undefined field_0x5889;
	undefined field_0x588a;
	undefined field_0x588b;
	undefined field_0x588c;
	undefined field_0x588d;
	undefined field_0x588e;
	undefined field_0x588f;
	undefined field_0x5890;
	undefined field_0x5891;
	undefined field_0x5892;
	undefined field_0x5893;
	undefined field_0x5894;
	undefined field_0x5895;
	undefined field_0x5896;
	undefined field_0x5897;
	undefined field_0x5898;
	undefined field_0x5899;
	undefined field_0x589a;
	undefined field_0x589b;
	undefined field_0x589c;
	undefined field_0x589d;
	undefined field_0x589e;
	undefined field_0x589f;
	undefined field_0x58a0;
	undefined field_0x58a1;
	undefined field_0x58a2;
	undefined field_0x58a3;
	undefined field_0x58a4;
	undefined field_0x58a5;
	undefined field_0x58a6;
	undefined field_0x58a7;
	undefined field_0x58a8;
	undefined field_0x58a9;
	undefined field_0x58aa;
	undefined field_0x58ab;
	undefined field_0x58ac;
	undefined field_0x58ad;
	undefined field_0x58ae;
	undefined field_0x58af;
	undefined field_0x58b0;
	undefined field_0x58b1;
	undefined field_0x58b2;
	undefined field_0x58b3;
	undefined field_0x58b4;
	undefined field_0x58b5;
	undefined field_0x58b6;
	undefined field_0x58b7;
	undefined field_0x58b8;
	undefined field_0x58b9;
	undefined field_0x58ba;
	undefined field_0x58bb;
	undefined field_0x58bc;
	undefined field_0x58bd;
	undefined field_0x58be;
	undefined field_0x58bf;
	undefined field_0x58c0;
	undefined field_0x58c1;
	undefined field_0x58c2;
	undefined field_0x58c3;
	undefined field_0x58c4;
	undefined field_0x58c5;
	undefined field_0x58c6;
	undefined field_0x58c7;
	undefined field_0x58c8;
	undefined field_0x58c9;
	undefined field_0x58ca;
	undefined field_0x58cb;
	undefined field_0x58cc;
	undefined field_0x58cd;
	undefined field_0x58ce;
	undefined field_0x58cf;
	undefined field_0x58d0;
	undefined field_0x58d1;
	undefined field_0x58d2;
	undefined field_0x58d3;
	undefined field_0x58d4;
	undefined field_0x58d5;
	undefined field_0x58d6;
	undefined field_0x58d7;
	undefined field_0x58d8;
	undefined field_0x58d9;
	undefined field_0x58da;
	undefined field_0x58db;
	undefined field_0x58dc;
	undefined field_0x58dd;
	undefined field_0x58de;
	undefined field_0x58df;
	undefined field_0x58e0;
	undefined field_0x58e1;
	undefined field_0x58e2;
	undefined field_0x58e3;
	undefined field_0x58e4;
	undefined field_0x58e5;
	undefined field_0x58e6;
	undefined field_0x58e7;
	undefined field_0x58e8;
	undefined field_0x58e9;
	undefined field_0x58ea;
	undefined field_0x58eb;
	undefined field_0x58ec;
	undefined field_0x58ed;
	undefined field_0x58ee;
	undefined field_0x58ef;
	undefined field_0x58f0;
	undefined field_0x58f1;
	undefined field_0x58f2;
	undefined field_0x58f3;
	undefined field_0x58f4;
	undefined field_0x58f5;
	undefined field_0x58f6;
	undefined field_0x58f7;
	undefined field_0x58f8;
	undefined field_0x58f9;
	undefined field_0x58fa;
	undefined field_0x58fb;
	undefined field_0x58fc;
	undefined field_0x58fd;
	undefined field_0x58fe;
	undefined field_0x58ff;
	undefined field_0x5900;
	undefined field_0x5901;
	undefined field_0x5902;
	undefined field_0x5903;
	undefined field_0x5904;
	undefined field_0x5905;
	undefined field_0x5906;
	undefined field_0x5907;
	undefined field_0x5908;
	undefined field_0x5909;
	undefined field_0x590a;
	undefined field_0x590b;
	undefined field_0x590c;
	undefined field_0x590d;
	undefined field_0x590e;
	undefined field_0x590f;
	undefined field_0x5910;
	undefined field_0x5911;
	undefined field_0x5912;
	undefined field_0x5913;
	undefined field_0x5914;
	undefined field_0x5915;
	undefined field_0x5916;
	undefined field_0x5917;
	undefined field_0x5918;
	undefined field_0x5919;
	undefined field_0x591a;
	undefined field_0x591b;
	undefined field_0x591c;
	undefined field_0x591d;
	undefined field_0x591e;
	undefined field_0x591f;
	undefined field_0x5920;
	undefined field_0x5921;
	undefined field_0x5922;
	undefined field_0x5923;
	undefined field_0x5924;
	undefined field_0x5925;
	undefined field_0x5926;
	undefined field_0x5927;
	undefined field_0x5928;
	undefined field_0x5929;
	undefined field_0x592a;
	undefined field_0x592b;
	undefined field_0x592c;
	undefined field_0x592d;
	undefined field_0x592e;
	undefined field_0x592f;
	undefined field_0x5930;
	undefined field_0x5931;
	undefined field_0x5932;
	undefined field_0x5933;
	undefined field_0x5934;
	undefined field_0x5935;
	undefined field_0x5936;
	undefined field_0x5937;
	undefined field_0x5938;
	undefined field_0x5939;
	undefined field_0x593a;
	undefined field_0x593b;
	undefined field_0x593c;
	undefined field_0x593d;
	undefined field_0x593e;
	undefined field_0x593f;
	undefined field_0x5940;
	undefined field_0x5941;
	undefined field_0x5942;
	undefined field_0x5943;
	undefined field_0x5944;
	undefined field_0x5945;
	undefined field_0x5946;
	undefined field_0x5947;
	undefined field_0x5948;
	undefined field_0x5949;
	undefined field_0x594a;
	undefined field_0x594b;
	undefined field_0x594c;
	undefined field_0x594d;
	undefined field_0x594e;
	undefined field_0x594f;
	undefined field_0x5950;
	undefined field_0x5951;
	undefined field_0x5952;
	undefined field_0x5953;
	undefined field_0x5954;
	undefined field_0x5955;
	undefined field_0x5956;
	undefined field_0x5957;
	undefined field_0x5958;
	undefined field_0x5959;
	undefined field_0x595a;
	undefined field_0x595b;
	undefined field_0x595c;
	undefined field_0x595d;
	undefined field_0x595e;
	undefined field_0x595f;
	undefined field_0x5960;
	undefined field_0x5961;
	undefined field_0x5962;
	undefined field_0x5963;
	undefined field_0x5964;
	undefined field_0x5965;
	undefined field_0x5966;
	undefined field_0x5967;
	undefined field_0x5968;
	undefined field_0x5969;
	undefined field_0x596a;
	undefined field_0x596b;
	undefined field_0x596c;
	undefined field_0x596d;
	undefined field_0x596e;
	undefined field_0x596f;
	undefined field_0x5970;
	undefined field_0x5971;
	undefined field_0x5972;
	undefined field_0x5973;
	undefined field_0x5974;
	undefined field_0x5975;
	undefined field_0x5976;
	undefined field_0x5977;
	undefined field_0x5978;
	undefined field_0x5979;
	undefined field_0x597a;
	undefined field_0x597b;
	undefined field_0x597c;
	undefined field_0x597d;
	undefined field_0x597e;
	undefined field_0x597f;
	undefined field_0x5980;
	undefined field_0x5981;
	undefined field_0x5982;
	undefined field_0x5983;
	undefined field_0x5984;
	undefined field_0x5985;
	undefined field_0x5986;
	undefined field_0x5987;
	undefined field_0x5988;
	undefined field_0x5989;
	undefined field_0x598a;
	undefined field_0x598b;
	undefined field_0x598c;
	undefined field_0x598d;
	undefined field_0x598e;
	undefined field_0x598f;
	undefined field_0x5990;
	undefined field_0x5991;
	undefined field_0x5992;
	undefined field_0x5993;
	undefined field_0x5994;
	undefined field_0x5995;
	undefined field_0x5996;
	undefined field_0x5997;
	undefined field_0x5998;
	undefined field_0x5999;
	undefined field_0x599a;
	undefined field_0x599b;
	undefined field_0x599c;
	undefined field_0x599d;
	undefined field_0x599e;
	undefined field_0x599f;
	undefined field_0x59a0;
	undefined field_0x59a1;
	undefined field_0x59a2;
	undefined field_0x59a3;
	undefined field_0x59a4;
	undefined field_0x59a5;
	undefined field_0x59a6;
	undefined field_0x59a7;
	undefined field_0x59a8;
	undefined field_0x59a9;
	undefined field_0x59aa;
	undefined field_0x59ab;
	undefined field_0x59ac;
	undefined field_0x59ad;
	undefined field_0x59ae;
	undefined field_0x59af;
	undefined field_0x59b0;
	undefined field_0x59b1;
	undefined field_0x59b2;
	undefined field_0x59b3;
	undefined field_0x59b4;
	undefined field_0x59b5;
	undefined field_0x59b6;
	undefined field_0x59b7;
	undefined field_0x59b8;
	undefined field_0x59b9;
	undefined field_0x59ba;
	undefined field_0x59bb;
	undefined field_0x59bc;
	undefined field_0x59bd;
	undefined field_0x59be;
	undefined field_0x59bf;
	undefined field_0x59c0;
	undefined field_0x59c1;
	undefined field_0x59c2;
	undefined field_0x59c3;
	undefined field_0x59c4;
	undefined field_0x59c5;
	undefined field_0x59c6;
	undefined field_0x59c7;
	undefined field_0x59c8;
	undefined field_0x59c9;
	undefined field_0x59ca;
	undefined field_0x59cb;
	undefined field_0x59cc;
	undefined field_0x59cd;
	undefined field_0x59ce;
	undefined field_0x59cf;
	undefined field_0x59d0;
	undefined field_0x59d1;
	undefined field_0x59d2;
	undefined field_0x59d3;
	undefined field_0x59d4;
	undefined field_0x59d5;
	undefined field_0x59d6;
	undefined field_0x59d7;
	undefined field_0x59d8;
	undefined field_0x59d9;
	undefined field_0x59da;
	undefined field_0x59db;
	undefined field_0x59dc;
	undefined field_0x59dd;
	undefined field_0x59de;
	undefined field_0x59df;
	undefined field_0x59e0;
	undefined field_0x59e1;
	undefined field_0x59e2;
	undefined field_0x59e3;
	undefined field_0x59e4;
	undefined field_0x59e5;
	undefined field_0x59e6;
	undefined field_0x59e7;
	undefined field_0x59e8;
	undefined field_0x59e9;
	undefined field_0x59ea;
	undefined field_0x59eb;
	undefined field_0x59ec;
	undefined field_0x59ed;
	undefined field_0x59ee;
	undefined field_0x59ef;
	undefined field_0x59f0;
	undefined field_0x59f1;
	undefined field_0x59f2;
	undefined field_0x59f3;
	undefined field_0x59f4;
	undefined field_0x59f5;
	undefined field_0x59f6;
	undefined field_0x59f7;
	undefined field_0x59f8;
	undefined field_0x59f9;
	undefined field_0x59fa;
	undefined field_0x59fb;
	undefined field_0x59fc;
	undefined field_0x59fd;
	undefined field_0x59fe;
	undefined field_0x59ff;
	undefined field_0x5a00;
	undefined field_0x5a01;
	undefined field_0x5a02;
	undefined field_0x5a03;
	undefined field_0x5a04;
	undefined field_0x5a05;
	undefined field_0x5a06;
	undefined field_0x5a07;
	undefined field_0x5a08;
	undefined field_0x5a09;
	undefined field_0x5a0a;
	undefined field_0x5a0b;
	undefined field_0x5a0c;
	undefined field_0x5a0d;
	undefined field_0x5a0e;
	undefined field_0x5a0f;
	undefined field_0x5a10;
	undefined field_0x5a11;
	undefined field_0x5a12;
	undefined field_0x5a13;
	undefined field_0x5a14;
	undefined field_0x5a15;
	undefined field_0x5a16;
	undefined field_0x5a17;
	undefined field_0x5a18;
	undefined field_0x5a19;
	undefined field_0x5a1a;
	undefined field_0x5a1b;
	undefined field_0x5a1c;
	undefined field_0x5a1d;
	undefined field_0x5a1e;
	undefined field_0x5a1f;
	undefined field_0x5a20;
	undefined field_0x5a21;
	undefined field_0x5a22;
	undefined field_0x5a23;
	undefined field_0x5a24;
	undefined field_0x5a25;
	undefined field_0x5a26;
	undefined field_0x5a27;
	undefined field_0x5a28;
	undefined field_0x5a29;
	undefined field_0x5a2a;
	undefined field_0x5a2b;
	undefined field_0x5a2c;
	undefined field_0x5a2d;
	undefined field_0x5a2e;
	undefined field_0x5a2f;
	undefined field_0x5a30;
	undefined field_0x5a31;
	undefined field_0x5a32;
	undefined field_0x5a33;
	undefined field_0x5a34;
	undefined field_0x5a35;
	undefined field_0x5a36;
	undefined field_0x5a37;
	undefined field_0x5a38;
	undefined field_0x5a39;
	undefined field_0x5a3a;
	undefined field_0x5a3b;
	undefined field_0x5a3c;
	undefined field_0x5a3d;
	undefined field_0x5a3e;
	undefined field_0x5a3f;
	undefined field_0x5a40;
	undefined field_0x5a41;
	undefined field_0x5a42;
	undefined field_0x5a43;
	undefined field_0x5a44;
	undefined field_0x5a45;
	undefined field_0x5a46;
	undefined field_0x5a47;
	undefined field_0x5a48;
	undefined field_0x5a49;
	undefined field_0x5a4a;
	undefined field_0x5a4b;
	undefined field_0x5a4c;
	undefined field_0x5a4d;
	undefined field_0x5a4e;
	undefined field_0x5a4f;
	undefined field_0x5a50;
	undefined field_0x5a51;
	undefined field_0x5a52;
	undefined field_0x5a53;
	undefined field_0x5a54;
	undefined field_0x5a55;
	undefined field_0x5a56;
	undefined field_0x5a57;
	undefined field_0x5a58;
	undefined field_0x5a59;
	undefined field_0x5a5a;
	undefined field_0x5a5b;
	undefined field_0x5a5c;
	undefined field_0x5a5d;
	undefined field_0x5a5e;
	undefined field_0x5a5f;
	undefined field_0x5a60;
	undefined field_0x5a61;
	undefined field_0x5a62;
	undefined field_0x5a63;
	undefined field_0x5a64;
	undefined field_0x5a65;
	undefined field_0x5a66;
	undefined field_0x5a67;
	undefined field_0x5a68;
	undefined field_0x5a69;
	undefined field_0x5a6a;
	undefined field_0x5a6b;
	undefined field_0x5a6c;
	undefined field_0x5a6d;
	undefined field_0x5a6e;
	undefined field_0x5a6f;
	undefined field_0x5a70;
	undefined field_0x5a71;
	undefined field_0x5a72;
	undefined field_0x5a73;
	undefined field_0x5a74;
	undefined field_0x5a75;
	undefined field_0x5a76;
	undefined field_0x5a77;
	undefined field_0x5a78;
	undefined field_0x5a79;
	undefined field_0x5a7a;
	undefined field_0x5a7b;
	undefined field_0x5a7c;
	undefined field_0x5a7d;
	undefined field_0x5a7e;
	undefined field_0x5a7f;
	undefined field_0x5a80;
	undefined field_0x5a81;
	undefined field_0x5a82;
	undefined field_0x5a83;
	undefined field_0x5a84;
	undefined field_0x5a85;
	undefined field_0x5a86;
	undefined field_0x5a87;
	undefined field_0x5a88;
	undefined field_0x5a89;
	undefined field_0x5a8a;
	undefined field_0x5a8b;
	undefined field_0x5a8c;
	undefined field_0x5a8d;
	undefined field_0x5a8e;
	undefined field_0x5a8f;
	undefined field_0x5a90;
	undefined field_0x5a91;
	undefined field_0x5a92;
	undefined field_0x5a93;
	undefined field_0x5a94;
	undefined field_0x5a95;
	undefined field_0x5a96;
	undefined field_0x5a97;
	undefined field_0x5a98;
	undefined field_0x5a99;
	undefined field_0x5a9a;
	undefined field_0x5a9b;
	undefined field_0x5a9c;
	undefined field_0x5a9d;
	undefined field_0x5a9e;
	undefined field_0x5a9f;
	undefined field_0x5aa0;
	undefined field_0x5aa1;
	undefined field_0x5aa2;
	undefined field_0x5aa3;
	undefined field_0x5aa4;
	undefined field_0x5aa5;
	undefined field_0x5aa6;
	undefined field_0x5aa7;
	undefined field_0x5aa8;
	undefined field_0x5aa9;
	undefined field_0x5aaa;
	undefined field_0x5aab;
	undefined field_0x5aac;
	undefined field_0x5aad;
	undefined field_0x5aae;
	undefined field_0x5aaf;
	undefined field_0x5ab0;
	undefined field_0x5ab1;
	undefined field_0x5ab2;
	undefined field_0x5ab3;
	undefined field_0x5ab4;
	undefined field_0x5ab5;
	undefined field_0x5ab6;
	undefined field_0x5ab7;
	undefined field_0x5ab8;
	undefined field_0x5ab9;
	undefined field_0x5aba;
	undefined field_0x5abb;
	undefined field_0x5abc;
	undefined field_0x5abd;
	undefined field_0x5abe;
	undefined field_0x5abf;
	undefined field_0x5ac0;
	undefined field_0x5ac1;
	undefined field_0x5ac2;
	undefined field_0x5ac3;
	undefined field_0x5ac4;
	undefined field_0x5ac5;
	undefined field_0x5ac6;
	undefined field_0x5ac7;
	undefined field_0x5ac8;
	undefined field_0x5ac9;
	undefined field_0x5aca;
	undefined field_0x5acb;
	undefined field_0x5acc;
	undefined field_0x5acd;
	undefined field_0x5ace;
	undefined field_0x5acf;
	undefined field_0x5ad0;
	undefined field_0x5ad1;
	undefined field_0x5ad2;
	undefined field_0x5ad3;
	undefined field_0x5ad4;
	undefined field_0x5ad5;
	undefined field_0x5ad6;
	undefined field_0x5ad7;
	undefined field_0x5ad8;
	undefined field_0x5ad9;
	undefined field_0x5ada;
	undefined field_0x5adb;
	undefined field_0x5adc;
	undefined field_0x5add;
	undefined field_0x5ade;
	undefined field_0x5adf;
	undefined field_0x5ae0;
	undefined field_0x5ae1;
	undefined field_0x5ae2;
	undefined field_0x5ae3;
	undefined field_0x5ae4;
	undefined field_0x5ae5;
	undefined field_0x5ae6;
	undefined field_0x5ae7;
	undefined field_0x5ae8;
	undefined field_0x5ae9;
	undefined field_0x5aea;
	undefined field_0x5aeb;
	undefined field_0x5aec;
	undefined field_0x5aed;
	undefined field_0x5aee;
	undefined field_0x5aef;
	undefined field_0x5af0;
	undefined field_0x5af1;
	undefined field_0x5af2;
	undefined field_0x5af3;
	undefined field_0x5af4;
	undefined field_0x5af5;
	undefined field_0x5af6;
	undefined field_0x5af7;
	undefined field_0x5af8;
	undefined field_0x5af9;
	undefined field_0x5afa;
	undefined field_0x5afb;
	undefined field_0x5afc;
	undefined field_0x5afd;
	undefined field_0x5afe;
	undefined field_0x5aff;
	undefined field_0x5b00;
	undefined field_0x5b01;
	undefined field_0x5b02;
	undefined field_0x5b03;
	undefined field_0x5b04;
	undefined field_0x5b05;
	undefined field_0x5b06;
	undefined field_0x5b07;
	undefined field_0x5b08;
	undefined field_0x5b09;
	undefined field_0x5b0a;
	undefined field_0x5b0b;
	undefined field_0x5b0c;
	undefined field_0x5b0d;
	undefined field_0x5b0e;
	undefined field_0x5b0f;
	undefined field_0x5b10;
	undefined field_0x5b11;
	undefined field_0x5b12;
	undefined field_0x5b13;
	undefined field_0x5b14;
	undefined field_0x5b15;
	undefined field_0x5b16;
	undefined field_0x5b17;
	undefined field_0x5b18;
	undefined field_0x5b19;
	undefined field_0x5b1a;
	undefined field_0x5b1b;
	undefined field_0x5b1c;
	undefined field_0x5b1d;
	undefined field_0x5b1e;
	undefined field_0x5b1f;
	undefined field_0x5b20;
	undefined field_0x5b21;
	undefined field_0x5b22;
	undefined field_0x5b23;
	undefined field_0x5b24;
	undefined field_0x5b25;
	undefined field_0x5b26;
	undefined field_0x5b27;
	undefined field_0x5b28;
	undefined field_0x5b29;
	undefined field_0x5b2a;
	undefined field_0x5b2b;
	undefined field_0x5b2c;
	undefined field_0x5b2d;
	undefined field_0x5b2e;
	undefined field_0x5b2f;
	undefined field_0x5b30;
	undefined field_0x5b31;
	undefined field_0x5b32;
	undefined field_0x5b33;
	undefined field_0x5b34;
	undefined field_0x5b35;
	undefined field_0x5b36;
	undefined field_0x5b37;
	undefined field_0x5b38;
	undefined field_0x5b39;
	undefined field_0x5b3a;
	undefined field_0x5b3b;
	undefined field_0x5b3c;
	undefined field_0x5b3d;
	undefined field_0x5b3e;
	undefined field_0x5b3f;
	undefined field_0x5b40;
	undefined field_0x5b41;
	undefined field_0x5b42;
	undefined field_0x5b43;
	undefined field_0x5b44;
	undefined field_0x5b45;
	undefined field_0x5b46;
	undefined field_0x5b47;
	undefined field_0x5b48;
	undefined field_0x5b49;
	undefined field_0x5b4a;
	undefined field_0x5b4b;
	undefined field_0x5b4c;
	undefined field_0x5b4d;
	undefined field_0x5b4e;
	undefined field_0x5b4f;
	undefined field_0x5b50;
	undefined field_0x5b51;
	undefined field_0x5b52;
	undefined field_0x5b53;
	undefined field_0x5b54;
	undefined field_0x5b55;
	undefined field_0x5b56;
	undefined field_0x5b57;
	undefined field_0x5b58;
	undefined field_0x5b59;
	undefined field_0x5b5a;
	undefined field_0x5b5b;
	undefined field_0x5b5c;
	undefined field_0x5b5d;
	undefined field_0x5b5e;
	undefined field_0x5b5f;
	undefined field_0x5b60;
	undefined field_0x5b61;
	undefined field_0x5b62;
	undefined field_0x5b63;
	undefined field_0x5b64;
	undefined field_0x5b65;
	undefined field_0x5b66;
	undefined field_0x5b67;
	undefined field_0x5b68;
	undefined field_0x5b69;
	undefined field_0x5b6a;
	undefined field_0x5b6b;
	undefined field_0x5b6c;
	undefined field_0x5b6d;
	undefined field_0x5b6e;
	undefined field_0x5b6f;
	undefined field_0x5b70;
	undefined field_0x5b71;
	undefined field_0x5b72;
	undefined field_0x5b73;
	undefined field_0x5b74;
	undefined field_0x5b75;
	undefined field_0x5b76;
	undefined field_0x5b77;
	undefined field_0x5b78;
	undefined field_0x5b79;
	undefined field_0x5b7a;
	undefined field_0x5b7b;
	undefined field_0x5b7c;
	undefined field_0x5b7d;
	undefined field_0x5b7e;
	undefined field_0x5b7f;
	undefined field_0x5b80;
	undefined field_0x5b81;
	undefined field_0x5b82;
	undefined field_0x5b83;
	undefined field_0x5b84;
	undefined field_0x5b85;
	undefined field_0x5b86;
	undefined field_0x5b87;
	undefined field_0x5b88;
	undefined field_0x5b89;
	undefined field_0x5b8a;
	undefined field_0x5b8b;
	undefined field_0x5b8c;
	undefined field_0x5b8d;
	undefined field_0x5b8e;
	undefined field_0x5b8f;
	undefined field_0x5b90;
	undefined field_0x5b91;
	undefined field_0x5b92;
	undefined field_0x5b93;
	undefined field_0x5b94;
	undefined field_0x5b95;
	undefined field_0x5b96;
	undefined field_0x5b97;
	undefined field_0x5b98;
	undefined field_0x5b99;
	undefined field_0x5b9a;
	undefined field_0x5b9b;
	undefined field_0x5b9c;
	undefined field_0x5b9d;
	undefined field_0x5b9e;
	undefined field_0x5b9f;
	undefined field_0x5ba0;
	undefined field_0x5ba1;
	undefined field_0x5ba2;
	undefined field_0x5ba3;
	undefined field_0x5ba4;
	undefined field_0x5ba5;
	undefined field_0x5ba6;
	undefined field_0x5ba7;
	undefined field_0x5ba8;
	undefined field_0x5ba9;
	undefined field_0x5baa;
	undefined field_0x5bab;
	undefined field_0x5bac;
	undefined field_0x5bad;
	undefined field_0x5bae;
	undefined field_0x5baf;
	undefined field_0x5bb0;
	undefined field_0x5bb1;
	undefined field_0x5bb2;
	undefined field_0x5bb3;
	undefined field_0x5bb4;
	undefined field_0x5bb5;
	undefined field_0x5bb6;
	undefined field_0x5bb7;
	undefined field_0x5bb8;
	undefined field_0x5bb9;
	undefined field_0x5bba;
	undefined field_0x5bbb;
	undefined field_0x5bbc;
	undefined field_0x5bbd;
	undefined field_0x5bbe;
	undefined field_0x5bbf;
	undefined field_0x5bc0;
	undefined field_0x5bc1;
	undefined field_0x5bc2;
	undefined field_0x5bc3;
	undefined field_0x5bc4;
	undefined field_0x5bc5;
	undefined field_0x5bc6;
	undefined field_0x5bc7;
	undefined field_0x5bc8;
	undefined field_0x5bc9;
	undefined field_0x5bca;
	undefined field_0x5bcb;
	undefined field_0x5bcc;
	undefined field_0x5bcd;
	undefined field_0x5bce;
	undefined field_0x5bcf;
	undefined field_0x5bd0;
	undefined field_0x5bd1;
	undefined field_0x5bd2;
	undefined field_0x5bd3;
	undefined field_0x5bd4;
	undefined field_0x5bd5;
	undefined field_0x5bd6;
	undefined field_0x5bd7;
	undefined field_0x5bd8;
	undefined field_0x5bd9;
	undefined field_0x5bda;
	undefined field_0x5bdb;
	undefined field_0x5bdc;
	undefined field_0x5bdd;
	undefined field_0x5bde;
	undefined field_0x5bdf;
	undefined field_0x5be0;
	undefined field_0x5be1;
	undefined field_0x5be2;
	undefined field_0x5be3;
	undefined field_0x5be4;
	undefined field_0x5be5;
	undefined field_0x5be6;
	undefined field_0x5be7;
	undefined field_0x5be8;
	undefined field_0x5be9;
	undefined field_0x5bea;
	undefined field_0x5beb;
	undefined field_0x5bec;
	undefined field_0x5bed;
	undefined field_0x5bee;
	undefined field_0x5bef;
	undefined field_0x5bf0;
	undefined field_0x5bf1;
	undefined field_0x5bf2;
	undefined field_0x5bf3;
	undefined field_0x5bf4;
	undefined field_0x5bf5;
	undefined field_0x5bf6;
	undefined field_0x5bf7;
	undefined field_0x5bf8;
	undefined field_0x5bf9;
	undefined field_0x5bfa;
	undefined field_0x5bfb;
	undefined field_0x5bfc;
	undefined field_0x5bfd;
	undefined field_0x5bfe;
	undefined field_0x5bff;
	undefined field_0x5c00;
	undefined field_0x5c01;
	undefined field_0x5c02;
	undefined field_0x5c03;
	undefined field_0x5c04;
	undefined field_0x5c05;
	undefined field_0x5c06;
	undefined field_0x5c07;
	undefined field_0x5c08;
	undefined field_0x5c09;
	undefined field_0x5c0a;
	undefined field_0x5c0b;
	undefined field_0x5c0c;
	undefined field_0x5c0d;
	undefined field_0x5c0e;
	undefined field_0x5c0f;
	undefined field_0x5c10;
	undefined field_0x5c11;
	undefined field_0x5c12;
	undefined field_0x5c13;
	undefined field_0x5c14;
	undefined field_0x5c15;
	undefined field_0x5c16;
	undefined field_0x5c17;
	undefined field_0x5c18;
	undefined field_0x5c19;
	undefined field_0x5c1a;
	undefined field_0x5c1b;
	undefined field_0x5c1c;
	undefined field_0x5c1d;
	undefined field_0x5c1e;
	undefined field_0x5c1f;
	undefined field_0x5c20;
	undefined field_0x5c21;
	undefined field_0x5c22;
	undefined field_0x5c23;
	undefined field_0x5c24;
	undefined field_0x5c25;
	undefined field_0x5c26;
	undefined field_0x5c27;
	undefined field_0x5c28;
	undefined field_0x5c29;
	undefined field_0x5c2a;
	undefined field_0x5c2b;
	undefined field_0x5c2c;
	undefined field_0x5c2d;
	undefined field_0x5c2e;
	undefined field_0x5c2f;
	undefined field_0x5c30;
	undefined field_0x5c31;
	undefined field_0x5c32;
	undefined field_0x5c33;
	undefined field_0x5c34;
	undefined field_0x5c35;
	undefined field_0x5c36;
	undefined field_0x5c37;
	undefined field_0x5c38;
	undefined field_0x5c39;
	undefined field_0x5c3a;
	undefined field_0x5c3b;
	undefined field_0x5c3c;
	undefined field_0x5c3d;
	undefined field_0x5c3e;
	undefined field_0x5c3f;
	undefined field_0x5c40;
	undefined field_0x5c41;
	undefined field_0x5c42;
	undefined field_0x5c43;
	undefined field_0x5c44;
	undefined field_0x5c45;
	undefined field_0x5c46;
	undefined field_0x5c47;
	undefined field_0x5c48;
	undefined field_0x5c49;
	undefined field_0x5c4a;
	undefined field_0x5c4b;
	undefined field_0x5c4c;
	undefined field_0x5c4d;
	undefined field_0x5c4e;
	undefined field_0x5c4f;
	undefined field_0x5c50;
	undefined field_0x5c51;
	undefined field_0x5c52;
	undefined field_0x5c53;
	undefined field_0x5c54;
	undefined field_0x5c55;
	undefined field_0x5c56;
	undefined field_0x5c57;
	undefined field_0x5c58;
	undefined field_0x5c59;
	undefined field_0x5c5a;
	undefined field_0x5c5b;
	undefined field_0x5c5c;
	undefined field_0x5c5d;
	undefined field_0x5c5e;
	undefined field_0x5c5f;
	undefined field_0x5c60;
	undefined field_0x5c61;
	undefined field_0x5c62;
	undefined field_0x5c63;
	undefined field_0x5c64;
	undefined field_0x5c65;
	undefined field_0x5c66;
	undefined field_0x5c67;
	undefined field_0x5c68;
	undefined field_0x5c69;
	undefined field_0x5c6a;
	undefined field_0x5c6b;
	undefined field_0x5c6c;
	undefined field_0x5c6d;
	undefined field_0x5c6e;
	undefined field_0x5c6f;
	undefined field_0x5c70;
	undefined field_0x5c71;
	undefined field_0x5c72;
	undefined field_0x5c73;
	undefined field_0x5c74;
	undefined field_0x5c75;
	undefined field_0x5c76;
	undefined field_0x5c77;
	undefined field_0x5c78;
	undefined field_0x5c79;
	undefined field_0x5c7a;
	undefined field_0x5c7b;
	undefined field_0x5c7c;
	undefined field_0x5c7d;
	undefined field_0x5c7e;
	undefined field_0x5c7f;
	undefined field_0x5c80;
	undefined field_0x5c81;
	undefined field_0x5c82;
	undefined field_0x5c83;
	undefined field_0x5c84;
	undefined field_0x5c85;
	undefined field_0x5c86;
	undefined field_0x5c87;
	undefined field_0x5c88;
	undefined field_0x5c89;
	undefined field_0x5c8a;
	undefined field_0x5c8b;
	undefined field_0x5c8c;
	undefined field_0x5c8d;
	undefined field_0x5c8e;
	undefined field_0x5c8f;
	undefined field_0x5c90;
	undefined field_0x5c91;
	undefined field_0x5c92;
	undefined field_0x5c93;
	undefined field_0x5c94;
	undefined field_0x5c95;
	undefined field_0x5c96;
	undefined field_0x5c97;
	undefined field_0x5c98;
	undefined field_0x5c99;
	undefined field_0x5c9a;
	undefined field_0x5c9b;
	undefined field_0x5c9c;
	undefined field_0x5c9d;
	undefined field_0x5c9e;
	undefined field_0x5c9f;
	undefined field_0x5ca0;
	undefined field_0x5ca1;
	undefined field_0x5ca2;
	undefined field_0x5ca3;
	undefined field_0x5ca4;
	undefined field_0x5ca5;
	undefined field_0x5ca6;
	undefined field_0x5ca7;
	undefined field_0x5ca8;
	undefined field_0x5ca9;
	undefined field_0x5caa;
	undefined field_0x5cab;
	undefined field_0x5cac;
	undefined field_0x5cad;
	undefined field_0x5cae;
	undefined field_0x5caf;
	undefined field_0x5cb0;
	undefined field_0x5cb1;
	undefined field_0x5cb2;
	undefined field_0x5cb3;
	undefined field_0x5cb4;
	undefined field_0x5cb5;
	undefined field_0x5cb6;
	undefined field_0x5cb7;
	undefined field_0x5cb8;
	undefined field_0x5cb9;
	undefined field_0x5cba;
	undefined field_0x5cbb;
	undefined field_0x5cbc;
	undefined field_0x5cbd;
	undefined field_0x5cbe;
	undefined field_0x5cbf;
	undefined field_0x5cc0;
	undefined field_0x5cc1;
	undefined field_0x5cc2;
	undefined field_0x5cc3;
	undefined field_0x5cc4;
	undefined field_0x5cc5;
	undefined field_0x5cc6;
	undefined field_0x5cc7;
	undefined field_0x5cc8;
	undefined field_0x5cc9;
	undefined field_0x5cca;
	undefined field_0x5ccb;
	undefined field_0x5ccc;
	undefined field_0x5ccd;
	undefined field_0x5cce;
	undefined field_0x5ccf;
	undefined field_0x5cd0;
	undefined field_0x5cd1;
	undefined field_0x5cd2;
	undefined field_0x5cd3;
	undefined field_0x5cd4;
	undefined field_0x5cd5;
	undefined field_0x5cd6;
	undefined field_0x5cd7;
	undefined field_0x5cd8;
	undefined field_0x5cd9;
	undefined field_0x5cda;
	undefined field_0x5cdb;
	undefined field_0x5cdc;
	undefined field_0x5cdd;
	undefined field_0x5cde;
	undefined field_0x5cdf;
	undefined field_0x5ce0;
	undefined field_0x5ce1;
	undefined field_0x5ce2;
	undefined field_0x5ce3;
	undefined field_0x5ce4;
	undefined field_0x5ce5;
	undefined field_0x5ce6;
	undefined field_0x5ce7;
	undefined field_0x5ce8;
	undefined field_0x5ce9;
	undefined field_0x5cea;
	undefined field_0x5ceb;
	undefined field_0x5cec;
	undefined field_0x5ced;
	undefined field_0x5cee;
	undefined field_0x5cef;
	undefined field_0x5cf0;
	undefined field_0x5cf1;
	undefined field_0x5cf2;
	undefined field_0x5cf3;
	undefined field_0x5cf4;
	undefined field_0x5cf5;
	undefined field_0x5cf6;
	undefined field_0x5cf7;
	undefined field_0x5cf8;
	undefined field_0x5cf9;
	undefined field_0x5cfa;
	undefined field_0x5cfb;
	undefined field_0x5cfc;
	undefined field_0x5cfd;
	undefined field_0x5cfe;
	undefined field_0x5cff;
	undefined field_0x5d00;
	undefined field_0x5d01;
	undefined field_0x5d02;
	undefined field_0x5d03;
	undefined field_0x5d04;
	undefined field_0x5d05;
	undefined field_0x5d06;
	undefined field_0x5d07;
	undefined field_0x5d08;
	undefined field_0x5d09;
	undefined field_0x5d0a;
	undefined field_0x5d0b;
	undefined field_0x5d0c;
	undefined field_0x5d0d;
	undefined field_0x5d0e;
	undefined field_0x5d0f;
	undefined field_0x5d10;
	undefined field_0x5d11;
	undefined field_0x5d12;
	undefined field_0x5d13;
	undefined field_0x5d14;
	undefined field_0x5d15;
	undefined field_0x5d16;
	undefined field_0x5d17;
	undefined field_0x5d18;
	undefined field_0x5d19;
	undefined field_0x5d1a;
	undefined field_0x5d1b;
	undefined field_0x5d1c;
	undefined field_0x5d1d;
	undefined field_0x5d1e;
	undefined field_0x5d1f;
	undefined field_0x5d20;
	undefined field_0x5d21;
	undefined field_0x5d22;
	undefined field_0x5d23;
	undefined field_0x5d24;
	undefined field_0x5d25;
	undefined field_0x5d26;
	undefined field_0x5d27;
	undefined field_0x5d28;
	undefined field_0x5d29;
	undefined field_0x5d2a;
	undefined field_0x5d2b;
	undefined field_0x5d2c;
	undefined field_0x5d2d;
	undefined field_0x5d2e;
	undefined field_0x5d2f;
	undefined field_0x5d30;
	undefined field_0x5d31;
	undefined field_0x5d32;
	undefined field_0x5d33;
	undefined field_0x5d34;
	undefined field_0x5d35;
	undefined field_0x5d36;
	undefined field_0x5d37;
	undefined field_0x5d38;
	undefined field_0x5d39;
	undefined field_0x5d3a;
	undefined field_0x5d3b;
	undefined field_0x5d3c;
	undefined field_0x5d3d;
	undefined field_0x5d3e;
	undefined field_0x5d3f;
	undefined field_0x5d40;
	undefined field_0x5d41;
	undefined field_0x5d42;
	undefined field_0x5d43;
	undefined field_0x5d44;
	undefined field_0x5d45;
	undefined field_0x5d46;
	undefined field_0x5d47;
	undefined field_0x5d48;
	undefined field_0x5d49;
	undefined field_0x5d4a;
	undefined field_0x5d4b;
	undefined field_0x5d4c;
	undefined field_0x5d4d;
	undefined field_0x5d4e;
	undefined field_0x5d4f;
	undefined field_0x5d50;
	undefined field_0x5d51;
	undefined field_0x5d52;
	undefined field_0x5d53;
	undefined field_0x5d54;
	undefined field_0x5d55;
	undefined field_0x5d56;
	undefined field_0x5d57;
	undefined field_0x5d58;
	undefined field_0x5d59;
	undefined field_0x5d5a;
	undefined field_0x5d5b;
	undefined field_0x5d5c;
	undefined field_0x5d5d;
	undefined field_0x5d5e;
	undefined field_0x5d5f;
	undefined field_0x5d60;
	undefined field_0x5d61;
	undefined field_0x5d62;
	undefined field_0x5d63;
	undefined field_0x5d64;
	undefined field_0x5d65;
	undefined field_0x5d66;
	undefined field_0x5d67;
	undefined field_0x5d68;
	undefined field_0x5d69;
	undefined field_0x5d6a;
	undefined field_0x5d6b;
	undefined field_0x5d6c;
	undefined field_0x5d6d;
	undefined field_0x5d6e;
	undefined field_0x5d6f;
	undefined field_0x5d70;
	undefined field_0x5d71;
	undefined field_0x5d72;
	undefined field_0x5d73;
	undefined field_0x5d74;
	undefined field_0x5d75;
	undefined field_0x5d76;
	undefined field_0x5d77;
	undefined field_0x5d78;
	undefined field_0x5d79;
	undefined field_0x5d7a;
	undefined field_0x5d7b;
	undefined field_0x5d7c;
	undefined field_0x5d7d;
	undefined field_0x5d7e;
	undefined field_0x5d7f;
	undefined field_0x5d80;
	undefined field_0x5d81;
	undefined field_0x5d82;
	undefined field_0x5d83;
	undefined field_0x5d84;
	undefined field_0x5d85;
	undefined field_0x5d86;
	undefined field_0x5d87;
	undefined field_0x5d88;
	undefined field_0x5d89;
	undefined field_0x5d8a;
	undefined field_0x5d8b;
	undefined field_0x5d8c;
	undefined field_0x5d8d;
	undefined field_0x5d8e;
	undefined field_0x5d8f;
	undefined field_0x5d90;
	undefined field_0x5d91;
	undefined field_0x5d92;
	undefined field_0x5d93;
	undefined field_0x5d94;
	undefined field_0x5d95;
	undefined field_0x5d96;
	undefined field_0x5d97;
	undefined field_0x5d98;
	undefined field_0x5d99;
	undefined field_0x5d9a;
	undefined field_0x5d9b;
	undefined field_0x5d9c;
	undefined field_0x5d9d;
	undefined field_0x5d9e;
	undefined field_0x5d9f;
	undefined field_0x5da0;
	undefined field_0x5da1;
	undefined field_0x5da2;
	undefined field_0x5da3;
	undefined field_0x5da4;
	undefined field_0x5da5;
	undefined field_0x5da6;
	undefined field_0x5da7;
	undefined field_0x5da8;
	undefined field_0x5da9;
	undefined field_0x5daa;
	undefined field_0x5dab;
	undefined field_0x5dac;
	undefined field_0x5dad;
	undefined field_0x5dae;
	undefined field_0x5daf;
	undefined field_0x5db0;
	undefined field_0x5db1;
	undefined field_0x5db2;
	undefined field_0x5db3;
	undefined field_0x5db4;
	undefined field_0x5db5;
	undefined field_0x5db6;
	undefined field_0x5db7;
	undefined field_0x5db8;
	undefined field_0x5db9;
	undefined field_0x5dba;
	undefined field_0x5dbb;
	undefined field_0x5dbc;
	undefined field_0x5dbd;
	undefined field_0x5dbe;
	undefined field_0x5dbf;
	undefined field_0x5dc0;
	undefined field_0x5dc1;
	undefined field_0x5dc2;
	undefined field_0x5dc3;
	undefined field_0x5dc4;
	undefined field_0x5dc5;
	undefined field_0x5dc6;
	undefined field_0x5dc7;
	undefined field_0x5dc8;
	undefined field_0x5dc9;
	undefined field_0x5dca;
	undefined field_0x5dcb;
	undefined field_0x5dcc;
	undefined field_0x5dcd;
	undefined field_0x5dce;
	undefined field_0x5dcf;
	undefined field_0x5dd0;
	undefined field_0x5dd1;
	undefined field_0x5dd2;
	undefined field_0x5dd3;
	undefined field_0x5dd4;
	undefined field_0x5dd5;
	undefined field_0x5dd6;
	undefined field_0x5dd7;
	undefined field_0x5dd8;
	undefined field_0x5dd9;
	undefined field_0x5dda;
	undefined field_0x5ddb;
	undefined field_0x5ddc;
	undefined field_0x5ddd;
	undefined field_0x5dde;
	undefined field_0x5ddf;
	undefined field_0x5de0;
	undefined field_0x5de1;
	undefined field_0x5de2;
	undefined field_0x5de3;
	undefined field_0x5de4;
	undefined field_0x5de5;
	undefined field_0x5de6;
	undefined field_0x5de7;
	undefined field_0x5de8;
	undefined field_0x5de9;
	undefined field_0x5dea;
	undefined field_0x5deb;
	undefined field_0x5dec;
	undefined field_0x5ded;
	undefined field_0x5dee;
	undefined field_0x5def;
	undefined field_0x5df0;
	undefined field_0x5df1;
	undefined field_0x5df2;
	undefined field_0x5df3;
	undefined field_0x5df4;
	undefined field_0x5df5;
	undefined field_0x5df6;
	undefined field_0x5df7;
	undefined field_0x5df8;
	undefined field_0x5df9;
	undefined field_0x5dfa;
	undefined field_0x5dfb;
	undefined field_0x5dfc;
	undefined field_0x5dfd;
	undefined field_0x5dfe;
	undefined field_0x5dff;
	undefined field_0x5e00;
	undefined field_0x5e01;
	undefined field_0x5e02;
	undefined field_0x5e03;
	undefined field_0x5e04;
	undefined field_0x5e05;
	undefined field_0x5e06;
	undefined field_0x5e07;
	undefined field_0x5e08;
	undefined field_0x5e09;
	undefined field_0x5e0a;
	undefined field_0x5e0b;
	undefined field_0x5e0c;
	undefined field_0x5e0d;
	undefined field_0x5e0e;
	undefined field_0x5e0f;
	undefined field_0x5e10;
	undefined field_0x5e11;
	undefined field_0x5e12;
	undefined field_0x5e13;
	undefined field_0x5e14;
	undefined field_0x5e15;
	undefined field_0x5e16;
	undefined field_0x5e17;
	undefined field_0x5e18;
	undefined field_0x5e19;
	undefined field_0x5e1a;
	undefined field_0x5e1b;
	undefined field_0x5e1c;
	undefined field_0x5e1d;
	undefined field_0x5e1e;
	undefined field_0x5e1f;
	undefined field_0x5e20;
	undefined field_0x5e21;
	undefined field_0x5e22;
	undefined field_0x5e23;
	undefined field_0x5e24;
	undefined field_0x5e25;
	undefined field_0x5e26;
	undefined field_0x5e27;
	undefined field_0x5e28;
	undefined field_0x5e29;
	undefined field_0x5e2a;
	undefined field_0x5e2b;
	undefined field_0x5e2c;
	undefined field_0x5e2d;
	undefined field_0x5e2e;
	undefined field_0x5e2f;
	undefined field_0x5e30;
	undefined field_0x5e31;
	undefined field_0x5e32;
	undefined field_0x5e33;
	undefined field_0x5e34;
	undefined field_0x5e35;
	undefined field_0x5e36;
	undefined field_0x5e37;
	undefined field_0x5e38;
	undefined field_0x5e39;
	undefined field_0x5e3a;
	undefined field_0x5e3b;
	undefined field_0x5e3c;
	undefined field_0x5e3d;
	undefined field_0x5e3e;
	undefined field_0x5e3f;
	undefined field_0x5e40;
	undefined field_0x5e41;
	undefined field_0x5e42;
	undefined field_0x5e43;
	undefined field_0x5e44;
	undefined field_0x5e45;
	undefined field_0x5e46;
	undefined field_0x5e47;
	undefined field_0x5e48;
	undefined field_0x5e49;
	undefined field_0x5e4a;
	undefined field_0x5e4b;
	undefined field_0x5e4c;
	undefined field_0x5e4d;
	undefined field_0x5e4e;
	undefined field_0x5e4f;
	undefined field_0x5e50;
	undefined field_0x5e51;
	undefined field_0x5e52;
	undefined field_0x5e53;
	undefined field_0x5e54;
	undefined field_0x5e55;
	undefined field_0x5e56;
	undefined field_0x5e57;
	undefined field_0x5e58;
	undefined field_0x5e59;
	undefined field_0x5e5a;
	undefined field_0x5e5b;
	undefined field_0x5e5c;
	undefined field_0x5e5d;
	undefined field_0x5e5e;
	undefined field_0x5e5f;
	undefined field_0x5e60;
	undefined field_0x5e61;
	undefined field_0x5e62;
	undefined field_0x5e63;
	undefined field_0x5e64;
	undefined field_0x5e65;
	undefined field_0x5e66;
	undefined field_0x5e67;
	undefined field_0x5e68;
	undefined field_0x5e69;
	undefined field_0x5e6a;
	undefined field_0x5e6b;
	undefined field_0x5e6c;
	undefined field_0x5e6d;
	undefined field_0x5e6e;
	undefined field_0x5e6f;
	undefined field_0x5e70;
	undefined field_0x5e71;
	undefined field_0x5e72;
	undefined field_0x5e73;
	undefined field_0x5e74;
	undefined field_0x5e75;
	undefined field_0x5e76;
	undefined field_0x5e77;
	undefined field_0x5e78;
	undefined field_0x5e79;
	undefined field_0x5e7a;
	undefined field_0x5e7b;
	undefined field_0x5e7c;
	undefined field_0x5e7d;
	undefined field_0x5e7e;
	undefined field_0x5e7f;
	undefined field_0x5e80;
	undefined field_0x5e81;
	undefined field_0x5e82;
	undefined field_0x5e83;
	undefined field_0x5e84;
	undefined field_0x5e85;
	undefined field_0x5e86;
	undefined field_0x5e87;
	undefined field_0x5e88;
	undefined field_0x5e89;
	undefined field_0x5e8a;
	undefined field_0x5e8b;
	undefined field_0x5e8c;
	undefined field_0x5e8d;
	undefined field_0x5e8e;
	undefined field_0x5e8f;
	undefined field_0x5e90;
	undefined field_0x5e91;
	undefined field_0x5e92;
	undefined field_0x5e93;
	undefined field_0x5e94;
	undefined field_0x5e95;
	undefined field_0x5e96;
	undefined field_0x5e97;
	undefined field_0x5e98;
	undefined field_0x5e99;
	undefined field_0x5e9a;
	undefined field_0x5e9b;
	undefined field_0x5e9c;
	undefined field_0x5e9d;
	undefined field_0x5e9e;
	undefined field_0x5e9f;
	undefined field_0x5ea0;
	undefined field_0x5ea1;
	undefined field_0x5ea2;
	undefined field_0x5ea3;
	undefined field_0x5ea4;
	undefined field_0x5ea5;
	undefined field_0x5ea6;
	undefined field_0x5ea7;
	undefined field_0x5ea8;
	undefined field_0x5ea9;
	undefined field_0x5eaa;
	undefined field_0x5eab;
	undefined field_0x5eac;
	undefined field_0x5ead;
	undefined field_0x5eae;
	undefined field_0x5eaf;
	undefined field_0x5eb0;
	undefined field_0x5eb1;
	undefined field_0x5eb2;
	undefined field_0x5eb3;
	undefined field_0x5eb4;
	undefined field_0x5eb5;
	undefined field_0x5eb6;
	undefined field_0x5eb7;
	undefined field_0x5eb8;
	undefined field_0x5eb9;
	undefined field_0x5eba;
	undefined field_0x5ebb;
	undefined field_0x5ebc;
	undefined field_0x5ebd;
	undefined field_0x5ebe;
	undefined field_0x5ebf;
	undefined field_0x5ec0;
	undefined field_0x5ec1;
	undefined field_0x5ec2;
	undefined field_0x5ec3;
	undefined field_0x5ec4;
	undefined field_0x5ec5;
	undefined field_0x5ec6;
	undefined field_0x5ec7;
	undefined field_0x5ec8;
	undefined field_0x5ec9;
	undefined field_0x5eca;
	undefined field_0x5ecb;
	undefined field_0x5ecc;
	undefined field_0x5ecd;
	undefined field_0x5ece;
	undefined field_0x5ecf;
	undefined field_0x5ed0;
	undefined field_0x5ed1;
	undefined field_0x5ed2;
	undefined field_0x5ed3;
	undefined field_0x5ed4;
	undefined field_0x5ed5;
	undefined field_0x5ed6;
	undefined field_0x5ed7;
	undefined field_0x5ed8;
	undefined field_0x5ed9;
	undefined field_0x5eda;
	undefined field_0x5edb;
	undefined field_0x5edc;
	undefined field_0x5edd;
	undefined field_0x5ede;
	undefined field_0x5edf;
	undefined field_0x5ee0;
	undefined field_0x5ee1;
	undefined field_0x5ee2;
	undefined field_0x5ee3;
	undefined field_0x5ee4;
	undefined field_0x5ee5;
	undefined field_0x5ee6;
	undefined field_0x5ee7;
	undefined field_0x5ee8;
	undefined field_0x5ee9;
	undefined field_0x5eea;
	undefined field_0x5eeb;
	undefined field_0x5eec;
	undefined field_0x5eed;
	undefined field_0x5eee;
	undefined field_0x5eef;
	undefined field_0x5ef0;
	undefined field_0x5ef1;
	undefined field_0x5ef2;
	undefined field_0x5ef3;
	undefined field_0x5ef4;
	undefined field_0x5ef5;
	undefined field_0x5ef6;
	undefined field_0x5ef7;
	undefined field_0x5ef8;
	undefined field_0x5ef9;
	undefined field_0x5efa;
	undefined field_0x5efb;
	undefined field_0x5efc;
	undefined field_0x5efd;
	undefined field_0x5efe;
	undefined field_0x5eff;
	undefined field_0x5f00;
	undefined field_0x5f01;
	undefined field_0x5f02;
	undefined field_0x5f03;
	undefined field_0x5f04;
	undefined field_0x5f05;
	undefined field_0x5f06;
	undefined field_0x5f07;
	undefined field_0x5f08;
	undefined field_0x5f09;
	undefined field_0x5f0a;
	undefined field_0x5f0b;
	undefined field_0x5f0c;
	undefined field_0x5f0d;
	undefined field_0x5f0e;
	undefined field_0x5f0f;
	undefined field_0x5f10;
	undefined field_0x5f11;
	undefined field_0x5f12;
	undefined field_0x5f13;
	undefined field_0x5f14;
	undefined field_0x5f15;
	undefined field_0x5f16;
	undefined field_0x5f17;
	undefined field_0x5f18;
	undefined field_0x5f19;
	undefined field_0x5f1a;
	undefined field_0x5f1b;
	undefined field_0x5f1c;
	undefined field_0x5f1d;
	undefined field_0x5f1e;
	undefined field_0x5f1f;
	undefined field_0x5f20;
	undefined field_0x5f21;
	undefined field_0x5f22;
	undefined field_0x5f23;
	undefined field_0x5f24;
	undefined field_0x5f25;
	undefined field_0x5f26;
	undefined field_0x5f27;
	undefined field_0x5f28;
	undefined field_0x5f29;
	undefined field_0x5f2a;
	undefined field_0x5f2b;
	undefined field_0x5f2c;
	undefined field_0x5f2d;
	undefined field_0x5f2e;
	undefined field_0x5f2f;
	undefined field_0x5f30;
	undefined field_0x5f31;
	undefined field_0x5f32;
	undefined field_0x5f33;
	undefined field_0x5f34;
	undefined field_0x5f35;
	undefined field_0x5f36;
	undefined field_0x5f37;
	undefined field_0x5f38;
	undefined field_0x5f39;
	undefined field_0x5f3a;
	undefined field_0x5f3b;
	undefined field_0x5f3c;
	undefined field_0x5f3d;
	undefined field_0x5f3e;
	undefined field_0x5f3f;
	undefined field_0x5f40;
	undefined field_0x5f41;
	undefined field_0x5f42;
	undefined field_0x5f43;
	undefined field_0x5f44;
	undefined field_0x5f45;
	undefined field_0x5f46;
	undefined field_0x5f47;
	undefined field_0x5f48;
	undefined field_0x5f49;
	undefined field_0x5f4a;
	undefined field_0x5f4b;
	undefined field_0x5f4c;
	undefined field_0x5f4d;
	undefined field_0x5f4e;
	undefined field_0x5f4f;
	undefined field_0x5f50;
	undefined field_0x5f51;
	undefined field_0x5f52;
	undefined field_0x5f53;
	undefined field_0x5f54;
	undefined field_0x5f55;
	undefined field_0x5f56;
	undefined field_0x5f57;
	undefined field_0x5f58;
	undefined field_0x5f59;
	undefined field_0x5f5a;
	undefined field_0x5f5b;
	undefined field_0x5f5c;
	undefined field_0x5f5d;
	undefined field_0x5f5e;
	undefined field_0x5f5f;
	undefined field_0x5f60;
	undefined field_0x5f61;
	undefined field_0x5f62;
	undefined field_0x5f63;
	undefined field_0x5f64;
	undefined field_0x5f65;
	undefined field_0x5f66;
	undefined field_0x5f67;
	undefined field_0x5f68;
	undefined field_0x5f69;
	undefined field_0x5f6a;
	undefined field_0x5f6b;
	undefined field_0x5f6c;
	undefined field_0x5f6d;
	undefined field_0x5f6e;
	undefined field_0x5f6f;
	undefined field_0x5f70;
	undefined field_0x5f71;
	undefined field_0x5f72;
	undefined field_0x5f73;
	undefined field_0x5f74;
	undefined field_0x5f75;
	undefined field_0x5f76;
	undefined field_0x5f77;
	undefined field_0x5f78;
	undefined field_0x5f79;
	undefined field_0x5f7a;
	undefined field_0x5f7b;
	undefined field_0x5f7c;
	undefined field_0x5f7d;
	undefined field_0x5f7e;
	undefined field_0x5f7f;
	undefined field_0x5f80;
	undefined field_0x5f81;
	undefined field_0x5f82;
	undefined field_0x5f83;
	undefined field_0x5f84;
	undefined field_0x5f85;
	undefined field_0x5f86;
	undefined field_0x5f87;
	undefined field_0x5f88;
	undefined field_0x5f89;
	undefined field_0x5f8a;
	undefined field_0x5f8b;
	undefined field_0x5f8c;
	undefined field_0x5f8d;
	undefined field_0x5f8e;
	undefined field_0x5f8f;
	undefined field_0x5f90;
	undefined field_0x5f91;
	undefined field_0x5f92;
	undefined field_0x5f93;
	undefined field_0x5f94;
	undefined field_0x5f95;
	undefined field_0x5f96;
	undefined field_0x5f97;
	undefined field_0x5f98;
	undefined field_0x5f99;
	undefined field_0x5f9a;
	undefined field_0x5f9b;
	undefined field_0x5f9c;
	undefined field_0x5f9d;
	undefined field_0x5f9e;
	undefined field_0x5f9f;
	undefined field_0x5fa0;
	undefined field_0x5fa1;
	undefined field_0x5fa2;
	undefined field_0x5fa3;
	undefined field_0x5fa4;
	undefined field_0x5fa5;
	undefined field_0x5fa6;
	undefined field_0x5fa7;
	undefined field_0x5fa8;
	undefined field_0x5fa9;
	undefined field_0x5faa;
	undefined field_0x5fab;
	undefined field_0x5fac;
	undefined field_0x5fad;
	undefined field_0x5fae;
	undefined field_0x5faf;
	undefined field_0x5fb0;
	undefined field_0x5fb1;
	undefined field_0x5fb2;
	undefined field_0x5fb3;
	undefined field_0x5fb4;
	undefined field_0x5fb5;
	undefined field_0x5fb6;
	undefined field_0x5fb7;
	undefined field_0x5fb8;
	undefined field_0x5fb9;
	undefined field_0x5fba;
	undefined field_0x5fbb;
	undefined field_0x5fbc;
	undefined field_0x5fbd;
	undefined field_0x5fbe;
	undefined field_0x5fbf;
	undefined field_0x5fc0;
	undefined field_0x5fc1;
	undefined field_0x5fc2;
	undefined field_0x5fc3;
	undefined field_0x5fc4;
	undefined field_0x5fc5;
	undefined field_0x5fc6;
	undefined field_0x5fc7;
	undefined field_0x5fc8;
	undefined field_0x5fc9;
	undefined field_0x5fca;
	undefined field_0x5fcb;
	undefined field_0x5fcc;
	undefined field_0x5fcd;
	undefined field_0x5fce;
	undefined field_0x5fcf;
	undefined field_0x5fd0;
	undefined field_0x5fd1;
	undefined field_0x5fd2;
	undefined field_0x5fd3;
	undefined field_0x5fd4;
	undefined field_0x5fd5;
	undefined field_0x5fd6;
	undefined field_0x5fd7;
	undefined field_0x5fd8;
	undefined field_0x5fd9;
	undefined field_0x5fda;
	undefined field_0x5fdb;
	undefined field_0x5fdc;
	undefined field_0x5fdd;
	undefined field_0x5fde;
	undefined field_0x5fdf;
	undefined field_0x5fe0;
	undefined field_0x5fe1;
	undefined field_0x5fe2;
	undefined field_0x5fe3;
	undefined field_0x5fe4;
	undefined field_0x5fe5;
	undefined field_0x5fe6;
	undefined field_0x5fe7;
	undefined field_0x5fe8;
	undefined field_0x5fe9;
	undefined field_0x5fea;
	undefined field_0x5feb;
	undefined field_0x5fec;
	undefined field_0x5fed;
	undefined field_0x5fee;
	undefined field_0x5fef;
	undefined field_0x5ff0;
	undefined field_0x5ff1;
	undefined field_0x5ff2;
	undefined field_0x5ff3;
	undefined field_0x5ff4;
	undefined field_0x5ff5;
	undefined field_0x5ff6;
	undefined field_0x5ff7;
	undefined field_0x5ff8;
	undefined field_0x5ff9;
	undefined field_0x5ffa;
	undefined field_0x5ffb;
	undefined field_0x5ffc;
	undefined field_0x5ffd;
	undefined field_0x5ffe;
	undefined field_0x5fff;
	undefined field_0x6000;
	undefined field_0x6001;
	undefined field_0x6002;
	undefined field_0x6003;
	undefined field_0x6004;
	undefined field_0x6005;
	undefined field_0x6006;
	undefined field_0x6007;
	undefined field_0x6008;
	undefined field_0x6009;
	undefined field_0x600a;
	undefined field_0x600b;
	undefined field_0x600c;
	undefined field_0x600d;
	undefined field_0x600e;
	undefined field_0x600f;
	undefined field_0x6010;
	undefined field_0x6011;
	undefined field_0x6012;
	undefined field_0x6013;
	undefined field_0x6014;
	undefined field_0x6015;
	undefined field_0x6016;
	undefined field_0x6017;
	undefined field_0x6018;
	undefined field_0x6019;
	undefined field_0x601a;
	undefined field_0x601b;
	undefined field_0x601c;
	undefined field_0x601d;
	undefined field_0x601e;
	undefined field_0x601f;
	undefined field_0x6020;
	undefined field_0x6021;
	undefined field_0x6022;
	undefined field_0x6023;
	undefined field_0x6024;
	undefined field_0x6025;
	undefined field_0x6026;
	undefined field_0x6027;
	undefined field_0x6028;
	undefined field_0x6029;
	undefined field_0x602a;
	undefined field_0x602b;
	undefined field_0x602c;
	undefined field_0x602d;
	undefined field_0x602e;
	undefined field_0x602f;
	undefined field_0x6030;
	undefined field_0x6031;
	undefined field_0x6032;
	undefined field_0x6033;
	undefined field_0x6034;
	undefined field_0x6035;
	undefined field_0x6036;
	undefined field_0x6037;
	undefined field_0x6038;
	undefined field_0x6039;
	undefined field_0x603a;
	undefined field_0x603b;
	undefined field_0x603c;
	undefined field_0x603d;
	undefined field_0x603e;
	undefined field_0x603f;
	undefined field_0x6040;
	undefined field_0x6041;
	undefined field_0x6042;
	undefined field_0x6043;
	undefined field_0x6044;
	undefined field_0x6045;
	undefined field_0x6046;
	undefined field_0x6047;
	undefined field_0x6048;
	undefined field_0x6049;
	undefined field_0x604a;
	undefined field_0x604b;
	undefined field_0x604c;
	undefined field_0x604d;
	undefined field_0x604e;
	undefined field_0x604f;
	undefined field_0x6050;
	undefined field_0x6051;
	undefined field_0x6052;
	undefined field_0x6053;
	undefined field_0x6054;
	undefined field_0x6055;
	undefined field_0x6056;
	undefined field_0x6057;
	undefined field_0x6058;
	undefined field_0x6059;
	undefined field_0x605a;
	undefined field_0x605b;
	undefined field_0x605c;
	undefined field_0x605d;
	undefined field_0x605e;
	undefined field_0x605f;
	undefined field_0x6060;
	undefined field_0x6061;
	undefined field_0x6062;
	undefined field_0x6063;
	undefined field_0x6064;
	undefined field_0x6065;
	undefined field_0x6066;
	undefined field_0x6067;
	undefined field_0x6068;
	undefined field_0x6069;
	undefined field_0x606a;
	undefined field_0x606b;
	undefined field_0x606c;
	undefined field_0x606d;
	undefined field_0x606e;
	undefined field_0x606f;
	undefined field_0x6070;
	undefined field_0x6071;
	undefined field_0x6072;
	undefined field_0x6073;
	undefined field_0x6074;
	undefined field_0x6075;
	undefined field_0x6076;
	undefined field_0x6077;
	undefined field_0x6078;
	undefined field_0x6079;
	undefined field_0x607a;
	undefined field_0x607b;
	undefined field_0x607c;
	undefined field_0x607d;
	undefined field_0x607e;
	undefined field_0x607f;
	undefined field_0x6080;
	undefined field_0x6081;
	undefined field_0x6082;
	undefined field_0x6083;
	undefined field_0x6084;
	undefined field_0x6085;
	undefined field_0x6086;
	undefined field_0x6087;
	undefined field_0x6088;
	undefined field_0x6089;
	undefined field_0x608a;
	undefined field_0x608b;
	undefined field_0x608c;
	undefined field_0x608d;
	undefined field_0x608e;
	undefined field_0x608f;
	undefined field_0x6090;
	undefined field_0x6091;
	undefined field_0x6092;
	undefined field_0x6093;
	undefined field_0x6094;
	undefined field_0x6095;
	undefined field_0x6096;
	undefined field_0x6097;
	undefined field_0x6098;
	undefined field_0x6099;
	undefined field_0x609a;
	undefined field_0x609b;
	undefined field_0x609c;
	undefined field_0x609d;
	undefined field_0x609e;
	undefined field_0x609f;
	undefined field_0x60a0;
	undefined field_0x60a1;
	undefined field_0x60a2;
	undefined field_0x60a3;
	undefined field_0x60a4;
	undefined field_0x60a5;
	undefined field_0x60a6;
	undefined field_0x60a7;
	undefined field_0x60a8;
	undefined field_0x60a9;
	undefined field_0x60aa;
	undefined field_0x60ab;
	undefined field_0x60ac;
	undefined field_0x60ad;
	undefined field_0x60ae;
	undefined field_0x60af;
	undefined field_0x60b0;
	undefined field_0x60b1;
	undefined field_0x60b2;
	undefined field_0x60b3;
	undefined field_0x60b4;
	undefined field_0x60b5;
	undefined field_0x60b6;
	undefined field_0x60b7;
	undefined field_0x60b8;
	undefined field_0x60b9;
	undefined field_0x60ba;
	undefined field_0x60bb;
	undefined field_0x60bc;
	undefined field_0x60bd;
	undefined field_0x60be;
	undefined field_0x60bf;
	undefined field_0x60c0;
	undefined field_0x60c1;
	undefined field_0x60c2;
	undefined field_0x60c3;
	undefined field_0x60c4;
	undefined field_0x60c5;
	undefined field_0x60c6;
	undefined field_0x60c7;
	undefined field_0x60c8;
	undefined field_0x60c9;
	undefined field_0x60ca;
	undefined field_0x60cb;
	undefined field_0x60cc;
	undefined field_0x60cd;
	undefined field_0x60ce;
	undefined field_0x60cf;
	undefined field_0x60d0;
	undefined field_0x60d1;
	undefined field_0x60d2;
	undefined field_0x60d3;
	undefined field_0x60d4;
	undefined field_0x60d5;
	undefined field_0x60d6;
	undefined field_0x60d7;
	undefined field_0x60d8;
	undefined field_0x60d9;
	undefined field_0x60da;
	undefined field_0x60db;
	undefined field_0x60dc;
	undefined field_0x60dd;
	undefined field_0x60de;
	undefined field_0x60df;
	undefined field_0x60e0;
	undefined field_0x60e1;
	undefined field_0x60e2;
	undefined field_0x60e3;
	undefined field_0x60e4;
	undefined field_0x60e5;
	undefined field_0x60e6;
	undefined field_0x60e7;
	undefined field_0x60e8;
	undefined field_0x60e9;
	undefined field_0x60ea;
	undefined field_0x60eb;
	undefined field_0x60ec;
	undefined field_0x60ed;
	undefined field_0x60ee;
	undefined field_0x60ef;
	undefined field_0x60f0;
	undefined field_0x60f1;
	undefined field_0x60f2;
	undefined field_0x60f3;
	undefined field_0x60f4;
	undefined field_0x60f5;
	undefined field_0x60f6;
	undefined field_0x60f7;
	undefined field_0x60f8;
	undefined field_0x60f9;
	undefined field_0x60fa;
	undefined field_0x60fb;
	undefined field_0x60fc;
	undefined field_0x60fd;
	undefined field_0x60fe;
	undefined field_0x60ff;
	undefined field_0x6100;
	undefined field_0x6101;
	undefined field_0x6102;
	undefined field_0x6103;
	undefined field_0x6104;
	undefined field_0x6105;
	undefined field_0x6106;
	undefined field_0x6107;
	undefined field_0x6108;
	undefined field_0x6109;
	undefined field_0x610a;
	undefined field_0x610b;
	undefined field_0x610c;
	undefined field_0x610d;
	undefined field_0x610e;
	undefined field_0x610f;
	undefined field_0x6110;
	undefined field_0x6111;
	undefined field_0x6112;
	undefined field_0x6113;
	undefined field_0x6114;
	undefined field_0x6115;
	undefined field_0x6116;
	undefined field_0x6117;
	undefined field_0x6118;
	undefined field_0x6119;
	undefined field_0x611a;
	undefined field_0x611b;
	undefined field_0x611c;
	undefined field_0x611d;
	undefined field_0x611e;
	undefined field_0x611f;
	undefined field_0x6120;
	undefined field_0x6121;
	undefined field_0x6122;
	undefined field_0x6123;
	undefined field_0x6124;
	undefined field_0x6125;
	undefined field_0x6126;
	undefined field_0x6127;
	undefined field_0x6128;
	undefined field_0x6129;
	undefined field_0x612a;
	undefined field_0x612b;
	undefined field_0x612c;
	undefined field_0x612d;
	undefined field_0x612e;
	undefined field_0x612f;
	undefined field_0x6130;
	undefined field_0x6131;
	undefined field_0x6132;
	undefined field_0x6133;
	undefined field_0x6134;
	undefined field_0x6135;
	undefined field_0x6136;
	undefined field_0x6137;
	undefined field_0x6138;
	undefined field_0x6139;
	undefined field_0x613a;
	undefined field_0x613b;
	undefined field_0x613c;
	undefined field_0x613d;
	undefined field_0x613e;
	undefined field_0x613f;
	undefined field_0x6140;
	undefined field_0x6141;
	undefined field_0x6142;
	undefined field_0x6143;
	undefined field_0x6144;
	undefined field_0x6145;
	undefined field_0x6146;
	undefined field_0x6147;
	undefined field_0x6148;
	undefined field_0x6149;
	undefined field_0x614a;
	undefined field_0x614b;
	undefined field_0x614c;
	undefined field_0x614d;
	undefined field_0x614e;
	undefined field_0x614f;
	undefined field_0x6150;
	undefined field_0x6151;
	undefined field_0x6152;
	undefined field_0x6153;
	undefined field_0x6154;
	undefined field_0x6155;
	undefined field_0x6156;
	undefined field_0x6157;
	undefined field_0x6158;
	undefined field_0x6159;
	undefined field_0x615a;
	undefined field_0x615b;
	undefined field_0x615c;
	undefined field_0x615d;
	undefined field_0x615e;
	undefined field_0x615f;
	undefined field_0x6160;
	undefined field_0x6161;
	undefined field_0x6162;
	undefined field_0x6163;
	undefined field_0x6164;
	undefined field_0x6165;
	undefined field_0x6166;
	undefined field_0x6167;
	undefined field_0x6168;
	undefined field_0x6169;
	undefined field_0x616a;
	undefined field_0x616b;
	undefined field_0x616c;
	undefined field_0x616d;
	undefined field_0x616e;
	undefined field_0x616f;
	undefined field_0x6170;
	undefined field_0x6171;
	undefined field_0x6172;
	undefined field_0x6173;
	undefined field_0x6174;
	undefined field_0x6175;
	undefined field_0x6176;
	undefined field_0x6177;
	undefined field_0x6178;
	undefined field_0x6179;
	undefined field_0x617a;
	undefined field_0x617b;
	undefined field_0x617c;
	undefined field_0x617d;
	undefined field_0x617e;
	undefined field_0x617f;
	undefined field_0x6180;
	undefined field_0x6181;
	undefined field_0x6182;
	undefined field_0x6183;
	undefined field_0x6184;
	undefined field_0x6185;
	undefined field_0x6186;
	undefined field_0x6187;
	undefined field_0x6188;
	undefined field_0x6189;
	undefined field_0x618a;
	undefined field_0x618b;
	undefined field_0x618c;
	undefined field_0x618d;
	undefined field_0x618e;
	undefined field_0x618f;
	undefined field_0x6190;
	undefined field_0x6191;
	undefined field_0x6192;
	undefined field_0x6193;
	undefined field_0x6194;
	undefined field_0x6195;
	undefined field_0x6196;
	undefined field_0x6197;
	undefined field_0x6198;
	undefined field_0x6199;
	undefined field_0x619a;
	undefined field_0x619b;
	undefined field_0x619c;
	undefined field_0x619d;
	undefined field_0x619e;
	undefined field_0x619f;
	undefined field_0x61a0;
	undefined field_0x61a1;
	undefined field_0x61a2;
	undefined field_0x61a3;
	undefined field_0x61a4;
	undefined field_0x61a5;
	undefined field_0x61a6;
	undefined field_0x61a7;
	undefined field_0x61a8;
	undefined field_0x61a9;
	undefined field_0x61aa;
	undefined field_0x61ab;
	undefined field_0x61ac;
	undefined field_0x61ad;
	undefined field_0x61ae;
	undefined field_0x61af;
	undefined field_0x61b0;
	undefined field_0x61b1;
	undefined field_0x61b2;
	undefined field_0x61b3;
	undefined field_0x61b4;
	undefined field_0x61b5;
	undefined field_0x61b6;
	undefined field_0x61b7;
	undefined field_0x61b8;
	undefined field_0x61b9;
	undefined field_0x61ba;
	undefined field_0x61bb;
	undefined field_0x61bc;
	undefined field_0x61bd;
	undefined field_0x61be;
	undefined field_0x61bf;
	undefined field_0x61c0;
	undefined field_0x61c1;
	undefined field_0x61c2;
	undefined field_0x61c3;
	undefined field_0x61c4;
	undefined field_0x61c5;
	undefined field_0x61c6;
	undefined field_0x61c7;
	undefined field_0x61c8;
	undefined field_0x61c9;
	undefined field_0x61ca;
	undefined field_0x61cb;
	undefined field_0x61cc;
	undefined field_0x61cd;
	undefined field_0x61ce;
	undefined field_0x61cf;
	undefined field_0x61d0;
	undefined field_0x61d1;
	undefined field_0x61d2;
	undefined field_0x61d3;
	undefined field_0x61d4;
	undefined field_0x61d5;
	undefined field_0x61d6;
	undefined field_0x61d7;
	undefined field_0x61d8;
	undefined field_0x61d9;
	undefined field_0x61da;
	undefined field_0x61db;
	undefined field_0x61dc;
	undefined field_0x61dd;
	undefined field_0x61de;
	undefined field_0x61df;
	undefined field_0x61e0;
	undefined field_0x61e1;
	undefined field_0x61e2;
	undefined field_0x61e3;
	undefined field_0x61e4;
	undefined field_0x61e5;
	undefined field_0x61e6;
	undefined field_0x61e7;
	undefined field_0x61e8;
	undefined field_0x61e9;
	undefined field_0x61ea;
	undefined field_0x61eb;
	undefined field_0x61ec;
	undefined field_0x61ed;
	undefined field_0x61ee;
	undefined field_0x61ef;
	undefined field_0x61f0;
	undefined field_0x61f1;
	undefined field_0x61f2;
	undefined field_0x61f3;
	undefined field_0x61f4;
	undefined field_0x61f5;
	undefined field_0x61f6;
	undefined field_0x61f7;
	undefined field_0x61f8;
	undefined field_0x61f9;
	undefined field_0x61fa;
	undefined field_0x61fb;
	undefined field_0x61fc;
	undefined field_0x61fd;
	undefined field_0x61fe;
	undefined field_0x61ff;
	undefined field_0x6200;
	undefined field_0x6201;
	undefined field_0x6202;
	undefined field_0x6203;
	undefined field_0x6204;
	undefined field_0x6205;
	undefined field_0x6206;
	undefined field_0x6207;
	undefined field_0x6208;
	undefined field_0x6209;
	undefined field_0x620a;
	undefined field_0x620b;
	undefined field_0x620c;
	undefined field_0x620d;
	undefined field_0x620e;
	undefined field_0x620f;
	undefined field_0x6210;
	undefined field_0x6211;
	undefined field_0x6212;
	undefined field_0x6213;
	undefined field_0x6214;
	undefined field_0x6215;
	undefined field_0x6216;
	undefined field_0x6217;
	undefined field_0x6218;
	undefined field_0x6219;
	undefined field_0x621a;
	undefined field_0x621b;
	undefined field_0x621c;
	undefined field_0x621d;
	undefined field_0x621e;
	undefined field_0x621f;
	undefined field_0x6220;
	undefined field_0x6221;
	undefined field_0x6222;
	undefined field_0x6223;
	undefined field_0x6224;
	undefined field_0x6225;
	undefined field_0x6226;
	undefined field_0x6227;
	undefined field_0x6228;
	undefined field_0x6229;
	undefined field_0x622a;
	undefined field_0x622b;
	undefined field_0x622c;
	undefined field_0x622d;
	undefined field_0x622e;
	undefined field_0x622f;
	undefined field_0x6230;
	undefined field_0x6231;
	undefined field_0x6232;
	undefined field_0x6233;
	undefined field_0x6234;
	undefined field_0x6235;
	undefined field_0x6236;
	undefined field_0x6237;
	undefined field_0x6238;
	undefined field_0x6239;
	undefined field_0x623a;
	undefined field_0x623b;
	undefined field_0x623c;
	undefined field_0x623d;
	undefined field_0x623e;
	undefined field_0x623f;
	undefined field_0x6240;
	undefined field_0x6241;
	undefined field_0x6242;
	undefined field_0x6243;
	undefined field_0x6244;
	undefined field_0x6245;
	undefined field_0x6246;
	undefined field_0x6247;
	undefined field_0x6248;
	undefined field_0x6249;
	undefined field_0x624a;
	undefined field_0x624b;
	undefined field_0x624c;
	undefined field_0x624d;
	undefined field_0x624e;
	undefined field_0x624f;
	undefined field_0x6250;
	undefined field_0x6251;
	undefined field_0x6252;
	undefined field_0x6253;
	undefined field_0x6254;
	undefined field_0x6255;
	undefined field_0x6256;
	undefined field_0x6257;
	undefined field_0x6258;
	undefined field_0x6259;
	undefined field_0x625a;
	undefined field_0x625b;
	undefined field_0x625c;
	undefined field_0x625d;
	undefined field_0x625e;
	undefined field_0x625f;
	undefined field_0x6260;
	undefined field_0x6261;
	undefined field_0x6262;
	undefined field_0x6263;
	undefined field_0x6264;
	undefined field_0x6265;
	undefined field_0x6266;
	undefined field_0x6267;
	undefined field_0x6268;
	undefined field_0x6269;
	undefined field_0x626a;
	undefined field_0x626b;
	undefined field_0x626c;
	undefined field_0x626d;
	undefined field_0x626e;
	undefined field_0x626f;
	undefined field_0x6270;
	undefined field_0x6271;
	undefined field_0x6272;
	undefined field_0x6273;
	undefined field_0x6274;
	undefined field_0x6275;
	undefined field_0x6276;
	undefined field_0x6277;
	undefined field_0x6278;
	undefined field_0x6279;
	undefined field_0x627a;
	undefined field_0x627b;
	undefined field_0x627c;
	undefined field_0x627d;
	undefined field_0x627e;
	undefined field_0x627f;
	undefined field_0x6280;
	undefined field_0x6281;
	undefined field_0x6282;
	undefined field_0x6283;
	undefined field_0x6284;
	undefined field_0x6285;
	undefined field_0x6286;
	undefined field_0x6287;
	undefined field_0x6288;
	undefined field_0x6289;
	undefined field_0x628a;
	undefined field_0x628b;
	undefined field_0x628c;
	undefined field_0x628d;
	undefined field_0x628e;
	undefined field_0x628f;
	undefined field_0x6290;
	undefined field_0x6291;
	undefined field_0x6292;
	undefined field_0x6293;
	undefined field_0x6294;
	undefined field_0x6295;
	undefined field_0x6296;
	undefined field_0x6297;
	undefined field_0x6298;
	undefined field_0x6299;
	undefined field_0x629a;
	undefined field_0x629b;
	undefined field_0x629c;
	undefined field_0x629d;
	undefined field_0x629e;
	undefined field_0x629f;
	undefined field_0x62a0;
	undefined field_0x62a1;
	undefined field_0x62a2;
	undefined field_0x62a3;
	undefined field_0x62a4;
	undefined field_0x62a5;
	undefined field_0x62a6;
	undefined field_0x62a7;
	undefined field_0x62a8;
	undefined field_0x62a9;
	undefined field_0x62aa;
	undefined field_0x62ab;
	undefined field_0x62ac;
	undefined field_0x62ad;
	undefined field_0x62ae;
	undefined field_0x62af;
	undefined field_0x62b0;
	undefined field_0x62b1;
	undefined field_0x62b2;
	undefined field_0x62b3;
	undefined field_0x62b4;
	undefined field_0x62b5;
	undefined field_0x62b6;
	undefined field_0x62b7;
	undefined field_0x62b8;
	undefined field_0x62b9;
	undefined field_0x62ba;
	undefined field_0x62bb;
	undefined field_0x62bc;
	undefined field_0x62bd;
	undefined field_0x62be;
	undefined field_0x62bf;
	undefined field_0x62c0;
	undefined field_0x62c1;
	undefined field_0x62c2;
	undefined field_0x62c3;
	undefined field_0x62c4;
	undefined field_0x62c5;
	undefined field_0x62c6;
	undefined field_0x62c7;
	undefined field_0x62c8;
	undefined field_0x62c9;
	undefined field_0x62ca;
	undefined field_0x62cb;
	undefined field_0x62cc;
	undefined field_0x62cd;
	undefined field_0x62ce;
	undefined field_0x62cf;
	undefined field_0x62d0;
	undefined field_0x62d1;
	undefined field_0x62d2;
	undefined field_0x62d3;
	undefined field_0x62d4;
	undefined field_0x62d5;
	undefined field_0x62d6;
	undefined field_0x62d7;
	undefined field_0x62d8;
	undefined field_0x62d9;
	undefined field_0x62da;
	undefined field_0x62db;
	undefined field_0x62dc;
	undefined field_0x62dd;
	undefined field_0x62de;
	undefined field_0x62df;
	undefined field_0x62e0;
	undefined field_0x62e1;
	undefined field_0x62e2;
	undefined field_0x62e3;
	undefined field_0x62e4;
	undefined field_0x62e5;
	undefined field_0x62e6;
	undefined field_0x62e7;
	undefined field_0x62e8;
	undefined field_0x62e9;
	undefined field_0x62ea;
	undefined field_0x62eb;
	undefined field_0x62ec;
	undefined field_0x62ed;
	undefined field_0x62ee;
	undefined field_0x62ef;
	undefined field_0x62f0;
	undefined field_0x62f1;
	undefined field_0x62f2;
	undefined field_0x62f3;
	undefined field_0x62f4;
	undefined field_0x62f5;
	undefined field_0x62f6;
	undefined field_0x62f7;
	undefined field_0x62f8;
	undefined field_0x62f9;
	undefined field_0x62fa;
	undefined field_0x62fb;
	undefined field_0x62fc;
	undefined field_0x62fd;
	undefined field_0x62fe;
	undefined field_0x62ff;
	undefined field_0x6300;
	undefined field_0x6301;
	undefined field_0x6302;
	undefined field_0x6303;
	undefined field_0x6304;
	undefined field_0x6305;
	undefined field_0x6306;
	undefined field_0x6307;
	undefined field_0x6308;
	undefined field_0x6309;
	undefined field_0x630a;
	undefined field_0x630b;
	undefined field_0x630c;
	undefined field_0x630d;
	undefined field_0x630e;
	undefined field_0x630f;
	undefined field_0x6310;
	undefined field_0x6311;
	undefined field_0x6312;
	undefined field_0x6313;
	undefined field_0x6314;
	undefined field_0x6315;
	undefined field_0x6316;
	undefined field_0x6317;
	undefined field_0x6318;
	undefined field_0x6319;
	undefined field_0x631a;
	undefined field_0x631b;
	undefined field_0x631c;
	undefined field_0x631d;
	undefined field_0x631e;
	undefined field_0x631f;
	undefined field_0x6320;
	undefined field_0x6321;
	undefined field_0x6322;
	undefined field_0x6323;
	undefined field_0x6324;
	undefined field_0x6325;
	undefined field_0x6326;
	undefined field_0x6327;
	undefined field_0x6328;
	undefined field_0x6329;
	undefined field_0x632a;
	undefined field_0x632b;
	undefined field_0x632c;
	undefined field_0x632d;
	undefined field_0x632e;
	undefined field_0x632f;
	undefined field_0x6330;
	undefined field_0x6331;
	undefined field_0x6332;
	undefined field_0x6333;
	undefined field_0x6334;
	undefined field_0x6335;
	undefined field_0x6336;
	undefined field_0x6337;
	undefined field_0x6338;
	undefined field_0x6339;
	undefined field_0x633a;
	undefined field_0x633b;
	undefined field_0x633c;
	undefined field_0x633d;
	undefined field_0x633e;
	undefined field_0x633f;
	undefined field_0x6340;
	undefined field_0x6341;
	undefined field_0x6342;
	undefined field_0x6343;
	undefined field_0x6344;
	undefined field_0x6345;
	undefined field_0x6346;
	undefined field_0x6347;
	undefined field_0x6348;
	undefined field_0x6349;
	undefined field_0x634a;
	undefined field_0x634b;
	undefined field_0x634c;
	undefined field_0x634d;
	undefined field_0x634e;
	undefined field_0x634f;
	undefined field_0x6350;
	undefined field_0x6351;
	undefined field_0x6352;
	undefined field_0x6353;
	undefined field_0x6354;
	undefined field_0x6355;
	undefined field_0x6356;
	undefined field_0x6357;
	undefined field_0x6358;
	undefined field_0x6359;
	undefined field_0x635a;
	undefined field_0x635b;
	undefined field_0x635c;
	undefined field_0x635d;
	undefined field_0x635e;
	undefined field_0x635f;
	undefined field_0x6360;
	undefined field_0x6361;
	undefined field_0x6362;
	undefined field_0x6363;
	undefined field_0x6364;
	undefined field_0x6365;
	undefined field_0x6366;
	undefined field_0x6367;
	undefined field_0x6368;
	undefined field_0x6369;
	undefined field_0x636a;
	undefined field_0x636b;
	undefined field_0x636c;
	undefined field_0x636d;
	undefined field_0x636e;
	undefined field_0x636f;
	undefined field_0x6370;
	undefined field_0x6371;
	undefined field_0x6372;
	undefined field_0x6373;
	undefined field_0x6374;
	undefined field_0x6375;
	undefined field_0x6376;
	undefined field_0x6377;
	undefined field_0x6378;
	undefined field_0x6379;
	undefined field_0x637a;
	undefined field_0x637b;
	undefined field_0x637c;
	undefined field_0x637d;
	undefined field_0x637e;
	undefined field_0x637f;
	undefined field_0x6380;
	undefined field_0x6381;
	undefined field_0x6382;
	undefined field_0x6383;
	undefined field_0x6384;
	undefined field_0x6385;
	undefined field_0x6386;
	undefined field_0x6387;
	undefined field_0x6388;
	undefined field_0x6389;
	undefined field_0x638a;
	undefined field_0x638b;
	undefined field_0x638c;
	undefined field_0x638d;
	undefined field_0x638e;
	undefined field_0x638f;
	undefined field_0x6390;
	undefined field_0x6391;
	undefined field_0x6392;
	undefined field_0x6393;
	undefined field_0x6394;
	undefined field_0x6395;
	undefined field_0x6396;
	undefined field_0x6397;
	undefined field_0x6398;
	undefined field_0x6399;
	undefined field_0x639a;
	undefined field_0x639b;
	undefined field_0x639c;
	undefined field_0x639d;
	undefined field_0x639e;
	undefined field_0x639f;
	undefined field_0x63a0;
	undefined field_0x63a1;
	undefined field_0x63a2;
	undefined field_0x63a3;
	undefined field_0x63a4;
	undefined field_0x63a5;
	undefined field_0x63a6;
	undefined field_0x63a7;
	undefined field_0x63a8;
	undefined field_0x63a9;
	undefined field_0x63aa;
	undefined field_0x63ab;
	undefined field_0x63ac;
	undefined field_0x63ad;
	undefined field_0x63ae;
	undefined field_0x63af;
	undefined field_0x63b0;
	undefined field_0x63b1;
	undefined field_0x63b2;
	undefined field_0x63b3;
	undefined field_0x63b4;
	undefined field_0x63b5;
	undefined field_0x63b6;
	undefined field_0x63b7;
	undefined field_0x63b8;
	undefined field_0x63b9;
	undefined field_0x63ba;
	undefined field_0x63bb;
	undefined field_0x63bc;
	undefined field_0x63bd;
	undefined field_0x63be;
	undefined field_0x63bf;
	undefined field_0x63c0;
	undefined field_0x63c1;
	undefined field_0x63c2;
	undefined field_0x63c3;
	undefined field_0x63c4;
	undefined field_0x63c5;
	undefined field_0x63c6;
	undefined field_0x63c7;
	undefined field_0x63c8;
	undefined field_0x63c9;
	undefined field_0x63ca;
	undefined field_0x63cb;
	undefined field_0x63cc;
	undefined field_0x63cd;
	undefined field_0x63ce;
	undefined field_0x63cf;
	undefined field_0x63d0;
	undefined field_0x63d1;
	undefined field_0x63d2;
	undefined field_0x63d3;
	undefined field_0x63d4;
	undefined field_0x63d5;
	undefined field_0x63d6;
	undefined field_0x63d7;
	undefined field_0x63d8;
	undefined field_0x63d9;
	undefined field_0x63da;
	undefined field_0x63db;
	undefined field_0x63dc;
	undefined field_0x63dd;
	undefined field_0x63de;
	undefined field_0x63df;
	undefined field_0x63e0;
	undefined field_0x63e1;
	undefined field_0x63e2;
	undefined field_0x63e3;
	undefined field_0x63e4;
	undefined field_0x63e5;
	undefined field_0x63e6;
	undefined field_0x63e7;
	undefined field_0x63e8;
	undefined field_0x63e9;
	undefined field_0x63ea;
	undefined field_0x63eb;
	undefined field_0x63ec;
	undefined field_0x63ed;
	undefined field_0x63ee;
	undefined field_0x63ef;
	undefined field_0x63f0;
	undefined field_0x63f1;
	undefined field_0x63f2;
	undefined field_0x63f3;
	undefined field_0x63f4;
	undefined field_0x63f5;
	undefined field_0x63f6;
	undefined field_0x63f7;
	undefined field_0x63f8;
	undefined field_0x63f9;
	undefined field_0x63fa;
	undefined field_0x63fb;
	undefined field_0x63fc;
	undefined field_0x63fd;
	undefined field_0x63fe;
	undefined field_0x63ff;
	undefined field_0x6400;
	undefined field_0x6401;
	undefined field_0x6402;
	undefined field_0x6403;
	undefined field_0x6404;
	undefined field_0x6405;
	undefined field_0x6406;
	undefined field_0x6407;
	undefined field_0x6408;
	undefined field_0x6409;
	undefined field_0x640a;
	undefined field_0x640b;
	undefined field_0x640c;
	undefined field_0x640d;
	undefined field_0x640e;
	undefined field_0x640f;
	undefined field_0x6410;
	undefined field_0x6411;
	undefined field_0x6412;
	undefined field_0x6413;
	undefined field_0x6414;
	undefined field_0x6415;
	undefined field_0x6416;
	undefined field_0x6417;
	undefined field_0x6418;
	undefined field_0x6419;
	undefined field_0x641a;
	undefined field_0x641b;
	undefined field_0x641c;
	undefined field_0x641d;
	undefined field_0x641e;
	undefined field_0x641f;
	undefined field_0x6420;
	undefined field_0x6421;
	undefined field_0x6422;
	undefined field_0x6423;
	undefined field_0x6424;
	undefined field_0x6425;
	undefined field_0x6426;
	undefined field_0x6427;
	undefined field_0x6428;
	undefined field_0x6429;
	undefined field_0x642a;
	undefined field_0x642b;
	undefined field_0x642c;
	undefined field_0x642d;
	undefined field_0x642e;
	undefined field_0x642f;
	undefined field_0x6430;
	undefined field_0x6431;
	undefined field_0x6432;
	undefined field_0x6433;
	undefined field_0x6434;
	undefined field_0x6435;
	undefined field_0x6436;
	undefined field_0x6437;
	undefined field_0x6438;
	undefined field_0x6439;
	undefined field_0x643a;
	undefined field_0x643b;
	undefined field_0x643c;
	undefined field_0x643d;
	undefined field_0x643e;
	undefined field_0x643f;
	undefined field_0x6440;
	undefined field_0x6441;
	undefined field_0x6442;
	undefined field_0x6443;
	undefined field_0x6444;
	undefined field_0x6445;
	undefined field_0x6446;
	undefined field_0x6447;
	undefined field_0x6448;
	undefined field_0x6449;
	undefined field_0x644a;
	undefined field_0x644b;
	undefined field_0x644c;
	undefined field_0x644d;
	undefined field_0x644e;
	undefined field_0x644f;
	undefined field_0x6450;
	undefined field_0x6451;
	undefined field_0x6452;
	undefined field_0x6453;
	undefined field_0x6454;
	undefined field_0x6455;
	undefined field_0x6456;
	undefined field_0x6457;
	undefined field_0x6458;
	undefined field_0x6459;
	undefined field_0x645a;
	undefined field_0x645b;
	undefined field_0x645c;
	undefined field_0x645d;
	undefined field_0x645e;
	undefined field_0x645f;
	undefined field_0x6460;
	undefined field_0x6461;
	undefined field_0x6462;
	undefined field_0x6463;
	undefined field_0x6464;
	undefined field_0x6465;
	undefined field_0x6466;
	undefined field_0x6467;
	undefined field_0x6468;
	undefined field_0x6469;
	undefined field_0x646a;
	undefined field_0x646b;
	undefined field_0x646c;
	undefined field_0x646d;
	undefined field_0x646e;
	undefined field_0x646f;
	undefined field_0x6470;
	undefined field_0x6471;
	undefined field_0x6472;
	undefined field_0x6473;
	undefined field_0x6474;
	undefined field_0x6475;
	undefined field_0x6476;
	undefined field_0x6477;
	undefined field_0x6478;
	undefined field_0x6479;
	undefined field_0x647a;
	undefined field_0x647b;
	undefined field_0x647c;
	undefined field_0x647d;
	undefined field_0x647e;
	undefined field_0x647f;
	undefined field_0x6480;
	undefined field_0x6481;
	undefined field_0x6482;
	undefined field_0x6483;
	undefined field_0x6484;
	undefined field_0x6485;
	undefined field_0x6486;
	undefined field_0x6487;
	undefined field_0x6488;
	undefined field_0x6489;
	undefined field_0x648a;
	undefined field_0x648b;
	undefined field_0x648c;
	undefined field_0x648d;
	undefined field_0x648e;
	undefined field_0x648f;
	undefined field_0x6490;
	undefined field_0x6491;
	undefined field_0x6492;
	undefined field_0x6493;
	undefined field_0x6494;
	undefined field_0x6495;
	undefined field_0x6496;
	undefined field_0x6497;
	undefined field_0x6498;
	undefined field_0x6499;
	undefined field_0x649a;
	undefined field_0x649b;
	undefined field_0x649c;
	undefined field_0x649d;
	undefined field_0x649e;
	undefined field_0x649f;
	undefined field_0x64a0;
	undefined field_0x64a1;
	undefined field_0x64a2;
	undefined field_0x64a3;
	undefined field_0x64a4;
	undefined field_0x64a5;
	undefined field_0x64a6;
	undefined field_0x64a7;
	undefined field_0x64a8;
	undefined field_0x64a9;
	undefined field_0x64aa;
	undefined field_0x64ab;
	undefined field_0x64ac;
	undefined field_0x64ad;
	undefined field_0x64ae;
	undefined field_0x64af;
	undefined field_0x64b0;
	undefined field_0x64b1;
	undefined field_0x64b2;
	undefined field_0x64b3;
	undefined field_0x64b4;
	undefined field_0x64b5;
	undefined field_0x64b6;
	undefined field_0x64b7;
	undefined field_0x64b8;
	undefined field_0x64b9;
	undefined field_0x64ba;
	undefined field_0x64bb;
	undefined field_0x64bc;
	undefined field_0x64bd;
	undefined field_0x64be;
	undefined field_0x64bf;
	undefined field_0x64c0;
	undefined field_0x64c1;
	undefined field_0x64c2;
	undefined field_0x64c3;
	undefined field_0x64c4;
	undefined field_0x64c5;
	undefined field_0x64c6;
	undefined field_0x64c7;
	undefined field_0x64c8;
	undefined field_0x64c9;
	undefined field_0x64ca;
	undefined field_0x64cb;
	undefined field_0x64cc;
	undefined field_0x64cd;
	undefined field_0x64ce;
	undefined field_0x64cf;
	undefined field_0x64d0;
	undefined field_0x64d1;
	undefined field_0x64d2;
	undefined field_0x64d3;
	undefined field_0x64d4;
	undefined field_0x64d5;
	undefined field_0x64d6;
	undefined field_0x64d7;
	undefined field_0x64d8;
	undefined field_0x64d9;
	undefined field_0x64da;
	undefined field_0x64db;
	undefined field_0x64dc;
	undefined field_0x64dd;
	undefined field_0x64de;
	undefined field_0x64df;
	undefined field_0x64e0;
	undefined field_0x64e1;
	undefined field_0x64e2;
	undefined field_0x64e3;
	undefined field_0x64e4;
	undefined field_0x64e5;
	undefined field_0x64e6;
	undefined field_0x64e7;
	undefined field_0x64e8;
	undefined field_0x64e9;
	undefined field_0x64ea;
	undefined field_0x64eb;
	undefined field_0x64ec;
	undefined field_0x64ed;
	undefined field_0x64ee;
	undefined field_0x64ef;
	undefined field_0x64f0;
	undefined field_0x64f1;
	undefined field_0x64f2;
	undefined field_0x64f3;
	undefined field_0x64f4;
	undefined field_0x64f5;
	undefined field_0x64f6;
	undefined field_0x64f7;
	undefined field_0x64f8;
	undefined field_0x64f9;
	undefined field_0x64fa;
	undefined field_0x64fb;
	undefined field_0x64fc;
	undefined field_0x64fd;
	undefined field_0x64fe;
	undefined field_0x64ff;
	undefined field_0x6500;
	undefined field_0x6501;
	undefined field_0x6502;
	undefined field_0x6503;
	undefined field_0x6504;
	undefined field_0x6505;
	undefined field_0x6506;
	undefined field_0x6507;
	undefined field_0x6508;
	undefined field_0x6509;
	undefined field_0x650a;
	undefined field_0x650b;
	undefined field_0x650c;
	undefined field_0x650d;
	undefined field_0x650e;
	undefined field_0x650f;
	undefined field_0x6510;
	undefined field_0x6511;
	undefined field_0x6512;
	undefined field_0x6513;
	undefined field_0x6514;
	undefined field_0x6515;
	undefined field_0x6516;
	undefined field_0x6517;
	undefined field_0x6518;
	undefined field_0x6519;
	undefined field_0x651a;
	undefined field_0x651b;
	undefined field_0x651c;
	undefined field_0x651d;
	undefined field_0x651e;
	undefined field_0x651f;
	undefined field_0x6520;
	undefined field_0x6521;
	undefined field_0x6522;
	undefined field_0x6523;
	undefined field_0x6524;
	undefined field_0x6525;
	undefined field_0x6526;
	undefined field_0x6527;
	undefined field_0x6528;
	undefined field_0x6529;
	undefined field_0x652a;
	undefined field_0x652b;
	undefined field_0x652c;
	undefined field_0x652d;
	undefined field_0x652e;
	undefined field_0x652f;
	undefined field_0x6530;
	undefined field_0x6531;
	undefined field_0x6532;
	undefined field_0x6533;
	undefined field_0x6534;
	undefined field_0x6535;
	undefined field_0x6536;
	undefined field_0x6537;
	undefined field_0x6538;
	undefined field_0x6539;
	undefined field_0x653a;
	undefined field_0x653b;
	undefined field_0x653c;
	undefined field_0x653d;
	undefined field_0x653e;
	undefined field_0x653f;
	undefined field_0x6540;
	undefined field_0x6541;
	undefined field_0x6542;
	undefined field_0x6543;
	undefined field_0x6544;
	undefined field_0x6545;
	undefined field_0x6546;
	undefined field_0x6547;
	undefined field_0x6548;
	undefined field_0x6549;
	undefined field_0x654a;
	undefined field_0x654b;
	undefined field_0x654c;
	undefined field_0x654d;
	undefined field_0x654e;
	undefined field_0x654f;
	undefined field_0x6550;
	undefined field_0x6551;
	undefined field_0x6552;
	undefined field_0x6553;
	undefined field_0x6554;
	undefined field_0x6555;
	undefined field_0x6556;
	undefined field_0x6557;
	undefined field_0x6558;
	undefined field_0x6559;
	undefined field_0x655a;
	undefined field_0x655b;
	undefined field_0x655c;
	undefined field_0x655d;
	undefined field_0x655e;
	undefined field_0x655f;
	undefined field_0x6560;
	undefined field_0x6561;
	undefined field_0x6562;
	undefined field_0x6563;
	undefined field_0x6564;
	undefined field_0x6565;
	undefined field_0x6566;
	undefined field_0x6567;
	undefined field_0x6568;
	undefined field_0x6569;
	undefined field_0x656a;
	undefined field_0x656b;
	undefined field_0x656c;
	undefined field_0x656d;
	undefined field_0x656e;
	undefined field_0x656f;
	undefined field_0x6570;
	undefined field_0x6571;
	undefined field_0x6572;
	undefined field_0x6573;
	undefined field_0x6574;
	undefined field_0x6575;
	undefined field_0x6576;
	undefined field_0x6577;
	undefined field_0x6578;
	undefined field_0x6579;
	undefined field_0x657a;
	undefined field_0x657b;
	undefined field_0x657c;
	undefined field_0x657d;
	undefined field_0x657e;
	undefined field_0x657f;
	undefined field_0x6580;
	undefined field_0x6581;
	undefined field_0x6582;
	undefined field_0x6583;
	undefined field_0x6584;
	undefined field_0x6585;
	undefined field_0x6586;
	undefined field_0x6587;
	undefined field_0x6588;
	undefined field_0x6589;
	undefined field_0x658a;
	undefined field_0x658b;
	undefined field_0x658c;
	undefined field_0x658d;
	undefined field_0x658e;
	undefined field_0x658f;
	undefined field_0x6590;
	undefined field_0x6591;
	undefined field_0x6592;
	undefined field_0x6593;
	undefined field_0x6594;
	undefined field_0x6595;
	undefined field_0x6596;
	undefined field_0x6597;
	undefined field_0x6598;
	undefined field_0x6599;
	undefined field_0x659a;
	undefined field_0x659b;
	undefined field_0x659c;
	undefined field_0x659d;
	undefined field_0x659e;
	undefined field_0x659f;
	undefined field_0x65a0;
	undefined field_0x65a1;
	undefined field_0x65a2;
	undefined field_0x65a3;
	undefined field_0x65a4;
	undefined field_0x65a5;
	undefined field_0x65a6;
	undefined field_0x65a7;
	undefined field_0x65a8;
	undefined field_0x65a9;
	undefined field_0x65aa;
	undefined field_0x65ab;
	undefined field_0x65ac;
	undefined field_0x65ad;
	undefined field_0x65ae;
	undefined field_0x65af;
	undefined field_0x65b0;
	undefined field_0x65b1;
	undefined field_0x65b2;
	undefined field_0x65b3;
	undefined field_0x65b4;
	undefined field_0x65b5;
	undefined field_0x65b6;
	undefined field_0x65b7;
	undefined field_0x65b8;
	undefined field_0x65b9;
	undefined field_0x65ba;
	undefined field_0x65bb;
	undefined field_0x65bc;
	undefined field_0x65bd;
	undefined field_0x65be;
	undefined field_0x65bf;
	undefined field_0x65c0;
	undefined field_0x65c1;
	undefined field_0x65c2;
	undefined field_0x65c3;
	undefined field_0x65c4;
	undefined field_0x65c5;
	undefined field_0x65c6;
	undefined field_0x65c7;
	undefined field_0x65c8;
	undefined field_0x65c9;
	undefined field_0x65ca;
	undefined field_0x65cb;
	undefined field_0x65cc;
	undefined field_0x65cd;
	undefined field_0x65ce;
	undefined field_0x65cf;
	undefined field_0x65d0;
	undefined field_0x65d1;
	undefined field_0x65d2;
	undefined field_0x65d3;
	undefined field_0x65d4;
	undefined field_0x65d5;
	undefined field_0x65d6;
	undefined field_0x65d7;
	undefined field_0x65d8;
	undefined field_0x65d9;
	undefined field_0x65da;
	undefined field_0x65db;
	undefined field_0x65dc;
	undefined field_0x65dd;
	undefined field_0x65de;
	undefined field_0x65df;
	undefined field_0x65e0;
	undefined field_0x65e1;
	undefined field_0x65e2;
	undefined field_0x65e3;
	undefined field_0x65e4;
	undefined field_0x65e5;
	undefined field_0x65e6;
	undefined field_0x65e7;
	undefined field_0x65e8;
	undefined field_0x65e9;
	undefined field_0x65ea;
	undefined field_0x65eb;
	undefined field_0x65ec;
	undefined field_0x65ed;
	undefined field_0x65ee;
	undefined field_0x65ef;
	undefined field_0x65f0;
	undefined field_0x65f1;
	undefined field_0x65f2;
	undefined field_0x65f3;
	undefined field_0x65f4;
	undefined field_0x65f5;
	undefined field_0x65f6;
	undefined field_0x65f7;
	undefined field_0x65f8;
	undefined field_0x65f9;
	undefined field_0x65fa;
	undefined field_0x65fb;
	undefined field_0x65fc;
	undefined field_0x65fd;
	undefined field_0x65fe;
	undefined field_0x65ff;
	undefined field_0x6600;
	undefined field_0x6601;
	undefined field_0x6602;
	undefined field_0x6603;
	undefined field_0x6604;
	undefined field_0x6605;
	undefined field_0x6606;
	undefined field_0x6607;
	undefined field_0x6608;
	undefined field_0x6609;
	undefined field_0x660a;
	undefined field_0x660b;
	undefined field_0x660c;
	undefined field_0x660d;
	undefined field_0x660e;
	undefined field_0x660f;
	undefined field_0x6610;
	undefined field_0x6611;
	undefined field_0x6612;
	undefined field_0x6613;
	undefined field_0x6614;
	undefined field_0x6615;
	undefined field_0x6616;
	undefined field_0x6617;
	undefined field_0x6618;
	undefined field_0x6619;
	undefined field_0x661a;
	undefined field_0x661b;
	undefined field_0x661c;
	undefined field_0x661d;
	undefined field_0x661e;
	undefined field_0x661f;
	undefined field_0x6620;
	undefined field_0x6621;
	undefined field_0x6622;
	undefined field_0x6623;
	undefined field_0x6624;
	undefined field_0x6625;
	undefined field_0x6626;
	undefined field_0x6627;
	undefined field_0x6628;
	undefined field_0x6629;
	undefined field_0x662a;
	undefined field_0x662b;
	undefined field_0x662c;
	undefined field_0x662d;
	undefined field_0x662e;
	undefined field_0x662f;
	undefined field_0x6630;
	undefined field_0x6631;
	undefined field_0x6632;
	undefined field_0x6633;
	undefined field_0x6634;
	undefined field_0x6635;
	undefined field_0x6636;
	undefined field_0x6637;
	undefined field_0x6638;
	undefined field_0x6639;
	undefined field_0x663a;
	undefined field_0x663b;
	undefined field_0x663c;
	undefined field_0x663d;
	undefined field_0x663e;
	undefined field_0x663f;
	undefined field_0x6640;
	undefined field_0x6641;
	undefined field_0x6642;
	undefined field_0x6643;
	undefined field_0x6644;
	undefined field_0x6645;
	undefined field_0x6646;
	undefined field_0x6647;
	undefined field_0x6648;
	undefined field_0x6649;
	undefined field_0x664a;
	undefined field_0x664b;
	undefined field_0x664c;
	undefined field_0x664d;
	undefined field_0x664e;
	undefined field_0x664f;
	undefined field_0x6650;
	undefined field_0x6651;
	undefined field_0x6652;
	undefined field_0x6653;
	undefined field_0x6654;
	undefined field_0x6655;
	undefined field_0x6656;
	undefined field_0x6657;
	undefined field_0x6658;
	undefined field_0x6659;
	undefined field_0x665a;
	undefined field_0x665b;
	undefined field_0x665c;
	undefined field_0x665d;
	undefined field_0x665e;
	undefined field_0x665f;
	undefined field_0x6660;
	undefined field_0x6661;
	undefined field_0x6662;
	undefined field_0x6663;
	undefined field_0x6664;
	undefined field_0x6665;
	undefined field_0x6666;
	undefined field_0x6667;
	undefined field_0x6668;
	undefined field_0x6669;
	undefined field_0x666a;
	undefined field_0x666b;
	undefined field_0x666c;
	undefined field_0x666d;
	undefined field_0x666e;
	undefined field_0x666f;
	undefined field_0x6670;
	undefined field_0x6671;
	undefined field_0x6672;
	undefined field_0x6673;
	undefined field_0x6674;
	undefined field_0x6675;
	undefined field_0x6676;
	undefined field_0x6677;
	undefined field_0x6678;
	undefined field_0x6679;
	undefined field_0x667a;
	undefined field_0x667b;
	undefined field_0x667c;
	undefined field_0x667d;
	undefined field_0x667e;
	undefined field_0x667f;
	undefined field_0x6680;
	undefined field_0x6681;
	undefined field_0x6682;
	undefined field_0x6683;
	undefined field_0x6684;
	undefined field_0x6685;
	undefined field_0x6686;
	undefined field_0x6687;
	undefined field_0x6688;
	undefined field_0x6689;
	undefined field_0x668a;
	undefined field_0x668b;
	undefined field_0x668c;
	undefined field_0x668d;
	undefined field_0x668e;
	undefined field_0x668f;
	undefined field_0x6690;
	undefined field_0x6691;
	undefined field_0x6692;
	undefined field_0x6693;
	undefined field_0x6694;
	undefined field_0x6695;
	undefined field_0x6696;
	undefined field_0x6697;
	undefined field_0x6698;
	undefined field_0x6699;
	undefined field_0x669a;
	undefined field_0x669b;
	undefined field_0x669c;
	undefined field_0x669d;
	undefined field_0x669e;
	undefined field_0x669f;
	undefined field_0x66a0;
	undefined field_0x66a1;
	undefined field_0x66a2;
	undefined field_0x66a3;
	undefined field_0x66a4;
	undefined field_0x66a5;
	undefined field_0x66a6;
	undefined field_0x66a7;
	undefined field_0x66a8;
	undefined field_0x66a9;
	undefined field_0x66aa;
	undefined field_0x66ab;
	undefined field_0x66ac;
	undefined field_0x66ad;
	undefined field_0x66ae;
	undefined field_0x66af;
	undefined field_0x66b0;
	undefined field_0x66b1;
	undefined field_0x66b2;
	undefined field_0x66b3;
	undefined field_0x66b4;
	undefined field_0x66b5;
	undefined field_0x66b6;
	undefined field_0x66b7;
	undefined field_0x66b8;
	undefined field_0x66b9;
	undefined field_0x66ba;
	undefined field_0x66bb;
	undefined field_0x66bc;
	undefined field_0x66bd;
	undefined field_0x66be;
	undefined field_0x66bf;
	undefined field_0x66c0;
	undefined field_0x66c1;
	undefined field_0x66c2;
	undefined field_0x66c3;
	undefined field_0x66c4;
	undefined field_0x66c5;
	undefined field_0x66c6;
	undefined field_0x66c7;
	undefined field_0x66c8;
	undefined field_0x66c9;
	undefined field_0x66ca;
	undefined field_0x66cb;
	undefined field_0x66cc;
	undefined field_0x66cd;
	undefined field_0x66ce;
	undefined field_0x66cf;
	undefined field_0x66d0;
	undefined field_0x66d1;
	undefined field_0x66d2;
	undefined field_0x66d3;
	undefined field_0x66d4;
	undefined field_0x66d5;
	undefined field_0x66d6;
	undefined field_0x66d7;
	undefined field_0x66d8;
	undefined field_0x66d9;
	undefined field_0x66da;
	undefined field_0x66db;
	undefined field_0x66dc;
	undefined field_0x66dd;
	undefined field_0x66de;
	undefined field_0x66df;
	undefined field_0x66e0;
	undefined field_0x66e1;
	undefined field_0x66e2;
	undefined field_0x66e3;
	undefined field_0x66e4;
	undefined field_0x66e5;
	undefined field_0x66e6;
	undefined field_0x66e7;
	undefined field_0x66e8;
	undefined field_0x66e9;
	undefined field_0x66ea;
	undefined field_0x66eb;
	undefined field_0x66ec;
	undefined field_0x66ed;
	undefined field_0x66ee;
	undefined field_0x66ef;
	undefined field_0x66f0;
	undefined field_0x66f1;
	undefined field_0x66f2;
	undefined field_0x66f3;
	undefined field_0x66f4;
	undefined field_0x66f5;
	undefined field_0x66f6;
	undefined field_0x66f7;
	undefined field_0x66f8;
	undefined field_0x66f9;
	undefined field_0x66fa;
	undefined field_0x66fb;
	undefined field_0x66fc;
	undefined field_0x66fd;
	undefined field_0x66fe;
	undefined field_0x66ff;
	undefined field_0x6700;
	undefined field_0x6701;
	undefined field_0x6702;
	undefined field_0x6703;
	undefined field_0x6704;
	undefined field_0x6705;
	undefined field_0x6706;
	undefined field_0x6707;
	undefined field_0x6708;
	undefined field_0x6709;
	undefined field_0x670a;
	undefined field_0x670b;
	undefined field_0x670c;
	undefined field_0x670d;
	undefined field_0x670e;
	undefined field_0x670f;
	undefined field_0x6710;
	undefined field_0x6711;
	undefined field_0x6712;
	undefined field_0x6713;
	undefined field_0x6714;
	undefined field_0x6715;
	undefined field_0x6716;
	undefined field_0x6717;
	undefined field_0x6718;
	undefined field_0x6719;
	undefined field_0x671a;
	undefined field_0x671b;
	undefined field_0x671c;
	undefined field_0x671d;
	undefined field_0x671e;
	undefined field_0x671f;
	undefined field_0x6720;
	undefined field_0x6721;
	undefined field_0x6722;
	undefined field_0x6723;
	undefined field_0x6724;
	undefined field_0x6725;
	undefined field_0x6726;
	undefined field_0x6727;
	undefined field_0x6728;
	undefined field_0x6729;
	undefined field_0x672a;
	undefined field_0x672b;
	undefined field_0x672c;
	undefined field_0x672d;
	undefined field_0x672e;
	undefined field_0x672f;
	undefined field_0x6730;
	undefined field_0x6731;
	undefined field_0x6732;
	undefined field_0x6733;
	undefined field_0x6734;
	undefined field_0x6735;
	undefined field_0x6736;
	undefined field_0x6737;
	undefined field_0x6738;
	undefined field_0x6739;
	undefined field_0x673a;
	undefined field_0x673b;
	undefined field_0x673c;
	undefined field_0x673d;
	undefined field_0x673e;
	undefined field_0x673f;
	undefined field_0x6740;
	undefined field_0x6741;
	undefined field_0x6742;
	undefined field_0x6743;
	undefined field_0x6744;
	undefined field_0x6745;
	undefined field_0x6746;
	undefined field_0x6747;
	undefined field_0x6748;
	undefined field_0x6749;
	undefined field_0x674a;
	undefined field_0x674b;
	undefined field_0x674c;
	undefined field_0x674d;
	undefined field_0x674e;
	undefined field_0x674f;
	undefined field_0x6750;
	undefined field_0x6751;
	undefined field_0x6752;
	undefined field_0x6753;
	undefined field_0x6754;
	undefined field_0x6755;
	undefined field_0x6756;
	undefined field_0x6757;
	undefined field_0x6758;
	undefined field_0x6759;
	undefined field_0x675a;
	undefined field_0x675b;
	undefined field_0x675c;
	undefined field_0x675d;
	undefined field_0x675e;
	undefined field_0x675f;
	undefined field_0x6760;
	undefined field_0x6761;
	undefined field_0x6762;
	undefined field_0x6763;
	undefined field_0x6764;
	undefined field_0x6765;
	undefined field_0x6766;
	undefined field_0x6767;
	undefined field_0x6768;
	undefined field_0x6769;
	undefined field_0x676a;
	undefined field_0x676b;
	undefined field_0x676c;
	undefined field_0x676d;
	undefined field_0x676e;
	undefined field_0x676f;
	undefined field_0x6770;
	undefined field_0x6771;
	undefined field_0x6772;
	undefined field_0x6773;
	undefined field_0x6774;
	undefined field_0x6775;
	undefined field_0x6776;
	undefined field_0x6777;
	undefined field_0x6778;
	undefined field_0x6779;
	undefined field_0x677a;
	undefined field_0x677b;
	undefined field_0x677c;
	undefined field_0x677d;
	undefined field_0x677e;
	undefined field_0x677f;
	undefined field_0x6780;
	undefined field_0x6781;
	undefined field_0x6782;
	undefined field_0x6783;
	undefined field_0x6784;
	undefined field_0x6785;
	undefined field_0x6786;
	undefined field_0x6787;
	undefined field_0x6788;
	undefined field_0x6789;
	undefined field_0x678a;
	undefined field_0x678b;
	undefined field_0x678c;
	undefined field_0x678d;
	undefined field_0x678e;
	undefined field_0x678f;
	undefined field_0x6790;
	undefined field_0x6791;
	undefined field_0x6792;
	undefined field_0x6793;
	undefined field_0x6794;
	undefined field_0x6795;
	undefined field_0x6796;
	undefined field_0x6797;
	undefined field_0x6798;
	undefined field_0x6799;
	undefined field_0x679a;
	undefined field_0x679b;
	undefined field_0x679c;
	undefined field_0x679d;
	undefined field_0x679e;
	undefined field_0x679f;
	undefined field_0x67a0;
	undefined field_0x67a1;
	undefined field_0x67a2;
	undefined field_0x67a3;
	undefined field_0x67a4;
	undefined field_0x67a5;
	undefined field_0x67a6;
	undefined field_0x67a7;
	undefined field_0x67a8;
	undefined field_0x67a9;
	undefined field_0x67aa;
	undefined field_0x67ab;
	undefined field_0x67ac;
	undefined field_0x67ad;
	undefined field_0x67ae;
	undefined field_0x67af;
	undefined field_0x67b0;
	undefined field_0x67b1;
	undefined field_0x67b2;
	undefined field_0x67b3;
	undefined field_0x67b4;
	undefined field_0x67b5;
	undefined field_0x67b6;
	undefined field_0x67b7;
	undefined field_0x67b8;
	undefined field_0x67b9;
	undefined field_0x67ba;
	undefined field_0x67bb;
	undefined field_0x67bc;
	undefined field_0x67bd;
	undefined field_0x67be;
	undefined field_0x67bf;
	undefined field_0x67c0;
	undefined field_0x67c1;
	undefined field_0x67c2;
	undefined field_0x67c3;
	undefined field_0x67c4;
	undefined field_0x67c5;
	undefined field_0x67c6;
	undefined field_0x67c7;
	undefined field_0x67c8;
	undefined field_0x67c9;
	undefined field_0x67ca;
	undefined field_0x67cb;
	undefined field_0x67cc;
	undefined field_0x67cd;
	undefined field_0x67ce;
	undefined field_0x67cf;
	undefined field_0x67d0;
	undefined field_0x67d1;
	undefined field_0x67d2;
	undefined field_0x67d3;
	undefined field_0x67d4;
	undefined field_0x67d5;
	undefined field_0x67d6;
	undefined field_0x67d7;
	undefined field_0x67d8;
	undefined field_0x67d9;
	undefined field_0x67da;
	undefined field_0x67db;
	undefined field_0x67dc;
	undefined field_0x67dd;
	undefined field_0x67de;
	undefined field_0x67df;
	undefined field_0x67e0;
	undefined field_0x67e1;
	undefined field_0x67e2;
	undefined field_0x67e3;
	undefined field_0x67e4;
	undefined field_0x67e5;
	undefined field_0x67e6;
	undefined field_0x67e7;
	undefined field_0x67e8;
	undefined field_0x67e9;
	undefined field_0x67ea;
	undefined field_0x67eb;
	undefined field_0x67ec;
	undefined field_0x67ed;
	undefined field_0x67ee;
	undefined field_0x67ef;
	undefined field_0x67f0;
	undefined field_0x67f1;
	undefined field_0x67f2;
	undefined field_0x67f3;
	undefined field_0x67f4;
	undefined field_0x67f5;
	undefined field_0x67f6;
	undefined field_0x67f7;
	undefined field_0x67f8;
	undefined field_0x67f9;
	undefined field_0x67fa;
	undefined field_0x67fb;
	undefined field_0x67fc;
	undefined field_0x67fd;
	undefined field_0x67fe;
	undefined field_0x67ff;
	undefined field_0x6800;
	undefined field_0x6801;
	undefined field_0x6802;
	undefined field_0x6803;
	undefined field_0x6804;
	undefined field_0x6805;
	undefined field_0x6806;
	undefined field_0x6807;
	undefined field_0x6808;
	undefined field_0x6809;
	undefined field_0x680a;
	undefined field_0x680b;
	undefined field_0x680c;
	undefined field_0x680d;
	undefined field_0x680e;
	undefined field_0x680f;
	undefined field_0x6810;
	undefined field_0x6811;
	undefined field_0x6812;
	undefined field_0x6813;
	undefined field_0x6814;
	undefined field_0x6815;
	undefined field_0x6816;
	undefined field_0x6817;
	undefined field_0x6818;
	undefined field_0x6819;
	undefined field_0x681a;
	undefined field_0x681b;
	undefined field_0x681c;
	undefined field_0x681d;
	undefined field_0x681e;
	undefined field_0x681f;
	undefined field_0x6820;
	undefined field_0x6821;
	undefined field_0x6822;
	undefined field_0x6823;
	undefined field_0x6824;
	undefined field_0x6825;
	undefined field_0x6826;
	undefined field_0x6827;
	undefined field_0x6828;
	undefined field_0x6829;
	undefined field_0x682a;
	undefined field_0x682b;
	undefined field_0x682c;
	undefined field_0x682d;
	undefined field_0x682e;
	undefined field_0x682f;
	undefined field_0x6830;
	undefined field_0x6831;
	undefined field_0x6832;
	undefined field_0x6833;
	undefined field_0x6834;
	undefined field_0x6835;
	undefined field_0x6836;
	undefined field_0x6837;
	undefined field_0x6838;
	undefined field_0x6839;
	undefined field_0x683a;
	undefined field_0x683b;
	undefined field_0x683c;
	undefined field_0x683d;
	undefined field_0x683e;
	undefined field_0x683f;
	undefined field_0x6840;
	undefined field_0x6841;
	undefined field_0x6842;
	undefined field_0x6843;
	undefined field_0x6844;
	undefined field_0x6845;
	undefined field_0x6846;
	undefined field_0x6847;
	undefined field_0x6848;
	undefined field_0x6849;
	undefined field_0x684a;
	undefined field_0x684b;
	undefined field_0x684c;
	undefined field_0x684d;
	undefined field_0x684e;
	undefined field_0x684f;
	undefined field_0x6850;
	undefined field_0x6851;
	undefined field_0x6852;
	undefined field_0x6853;
	undefined field_0x6854;
	undefined field_0x6855;
	undefined field_0x6856;
	undefined field_0x6857;
	undefined field_0x6858;
	undefined field_0x6859;
	undefined field_0x685a;
	undefined field_0x685b;
	undefined field_0x685c;
	undefined field_0x685d;
	undefined field_0x685e;
	undefined field_0x685f;
	undefined field_0x6860;
	undefined field_0x6861;
	undefined field_0x6862;
	undefined field_0x6863;
	undefined field_0x6864;
	undefined field_0x6865;
	undefined field_0x6866;
	undefined field_0x6867;
	undefined field_0x6868;
	undefined field_0x6869;
	undefined field_0x686a;
	undefined field_0x686b;
	undefined field_0x686c;
	undefined field_0x686d;
	undefined field_0x686e;
	undefined field_0x686f;
	undefined field_0x6870;
	undefined field_0x6871;
	undefined field_0x6872;
	undefined field_0x6873;
	undefined field_0x6874;
	undefined field_0x6875;
	undefined field_0x6876;
	undefined field_0x6877;
	undefined field_0x6878;
	undefined field_0x6879;
	undefined field_0x687a;
	undefined field_0x687b;
	undefined field_0x687c;
	undefined field_0x687d;
	undefined field_0x687e;
	undefined field_0x687f;
	undefined field_0x6880;
	undefined field_0x6881;
	undefined field_0x6882;
	undefined field_0x6883;
	undefined field_0x6884;
	undefined field_0x6885;
	undefined field_0x6886;
	undefined field_0x6887;
	undefined field_0x6888;
	undefined field_0x6889;
	undefined field_0x688a;
	undefined field_0x688b;
	undefined field_0x688c;
	undefined field_0x688d;
	undefined field_0x688e;
	undefined field_0x688f;
	undefined field_0x6890;
	undefined field_0x6891;
	undefined field_0x6892;
	undefined field_0x6893;
	undefined field_0x6894;
	undefined field_0x6895;
	undefined field_0x6896;
	undefined field_0x6897;
	undefined field_0x6898;
	undefined field_0x6899;
	undefined field_0x689a;
	undefined field_0x689b;
	undefined field_0x689c;
	undefined field_0x689d;
	undefined field_0x689e;
	undefined field_0x689f;
	undefined field_0x68a0;
	undefined field_0x68a1;
	undefined field_0x68a2;
	undefined field_0x68a3;
	undefined field_0x68a4;
	undefined field_0x68a5;
	undefined field_0x68a6;
	undefined field_0x68a7;
	undefined field_0x68a8;
	undefined field_0x68a9;
	undefined field_0x68aa;
	undefined field_0x68ab;
	undefined field_0x68ac;
	undefined field_0x68ad;
	undefined field_0x68ae;
	undefined field_0x68af;
	undefined field_0x68b0;
	undefined field_0x68b1;
	undefined field_0x68b2;
	undefined field_0x68b3;
	undefined field_0x68b4;
	undefined field_0x68b5;
	undefined field_0x68b6;
	undefined field_0x68b7;
	undefined field_0x68b8;
	undefined field_0x68b9;
	undefined field_0x68ba;
	undefined field_0x68bb;
	undefined field_0x68bc;
	undefined field_0x68bd;
	undefined field_0x68be;
	undefined field_0x68bf;
	undefined field_0x68c0;
	undefined field_0x68c1;
	undefined field_0x68c2;
	undefined field_0x68c3;
	undefined field_0x68c4;
	undefined field_0x68c5;
	undefined field_0x68c6;
	undefined field_0x68c7;
	undefined field_0x68c8;
	undefined field_0x68c9;
	undefined field_0x68ca;
	undefined field_0x68cb;
	undefined field_0x68cc;
	undefined field_0x68cd;
	undefined field_0x68ce;
	undefined field_0x68cf;
	undefined field_0x68d0;
	undefined field_0x68d1;
	undefined field_0x68d2;
	undefined field_0x68d3;
	undefined field_0x68d4;
	undefined field_0x68d5;
	undefined field_0x68d6;
	undefined field_0x68d7;
	undefined field_0x68d8;
	undefined field_0x68d9;
	undefined field_0x68da;
	undefined field_0x68db;
	undefined field_0x68dc;
	undefined field_0x68dd;
	undefined field_0x68de;
	undefined field_0x68df;
	undefined field_0x68e0;
	undefined field_0x68e1;
	undefined field_0x68e2;
	undefined field_0x68e3;
	undefined field_0x68e4;
	undefined field_0x68e5;
	undefined field_0x68e6;
	undefined field_0x68e7;
	undefined field_0x68e8;
	undefined field_0x68e9;
	undefined field_0x68ea;
	undefined field_0x68eb;
	undefined field_0x68ec;
	undefined field_0x68ed;
	undefined field_0x68ee;
	undefined field_0x68ef;
	undefined field_0x68f0;
	undefined field_0x68f1;
	undefined field_0x68f2;
	undefined field_0x68f3;
	undefined field_0x68f4;
	undefined field_0x68f5;
	undefined field_0x68f6;
	undefined field_0x68f7;
	undefined field_0x68f8;
	undefined field_0x68f9;
	undefined field_0x68fa;
	undefined field_0x68fb;
	undefined field_0x68fc;
	undefined field_0x68fd;
	undefined field_0x68fe;
	undefined field_0x68ff;
	undefined field_0x6900;
	undefined field_0x6901;
	undefined field_0x6902;
	undefined field_0x6903;
	undefined field_0x6904;
	undefined field_0x6905;
	undefined field_0x6906;
	undefined field_0x6907;
	undefined field_0x6908;
	undefined field_0x6909;
	undefined field_0x690a;
	undefined field_0x690b;
	undefined field_0x690c;
	undefined field_0x690d;
	undefined field_0x690e;
	undefined field_0x690f;
	undefined field_0x6910;
	undefined field_0x6911;
	undefined field_0x6912;
	undefined field_0x6913;
	undefined field_0x6914;
	undefined field_0x6915;
	undefined field_0x6916;
	undefined field_0x6917;
	undefined field_0x6918;
	undefined field_0x6919;
	undefined field_0x691a;
	undefined field_0x691b;
	undefined field_0x691c;
	undefined field_0x691d;
	undefined field_0x691e;
	undefined field_0x691f;
	undefined field_0x6920;
	undefined field_0x6921;
	undefined field_0x6922;
	undefined field_0x6923;
	undefined field_0x6924;
	undefined field_0x6925;
	undefined field_0x6926;
	undefined field_0x6927;
	undefined field_0x6928;
	undefined field_0x6929;
	undefined field_0x692a;
	undefined field_0x692b;
	undefined field_0x692c;
	undefined field_0x692d;
	undefined field_0x692e;
	undefined field_0x692f;
	undefined field_0x6930;
	undefined field_0x6931;
	undefined field_0x6932;
	undefined field_0x6933;
	undefined field_0x6934;
	undefined field_0x6935;
	undefined field_0x6936;
	undefined field_0x6937;
	undefined field_0x6938;
	undefined field_0x6939;
	undefined field_0x693a;
	undefined field_0x693b;
	undefined field_0x693c;
	undefined field_0x693d;
	undefined field_0x693e;
	undefined field_0x693f;
	undefined field_0x6940;
	undefined field_0x6941;
	undefined field_0x6942;
	undefined field_0x6943;
	undefined field_0x6944;
	undefined field_0x6945;
	undefined field_0x6946;
	undefined field_0x6947;
	undefined field_0x6948;
	undefined field_0x6949;
	undefined field_0x694a;
	undefined field_0x694b;
	undefined field_0x694c;
	undefined field_0x694d;
	undefined field_0x694e;
	undefined field_0x694f;
	undefined field_0x6950;
	undefined field_0x6951;
	undefined field_0x6952;
	undefined field_0x6953;
	undefined field_0x6954;
	undefined field_0x6955;
	undefined field_0x6956;
	undefined field_0x6957;
	undefined field_0x6958;
	undefined field_0x6959;
	undefined field_0x695a;
	undefined field_0x695b;
	undefined field_0x695c;
	undefined field_0x695d;
	undefined field_0x695e;
	undefined field_0x695f;
	undefined field_0x6960;
	undefined field_0x6961;
	undefined field_0x6962;
	undefined field_0x6963;
	undefined field_0x6964;
	undefined field_0x6965;
	undefined field_0x6966;
	undefined field_0x6967;
	undefined field_0x6968;
	undefined field_0x6969;
	undefined field_0x696a;
	undefined field_0x696b;
	undefined field_0x696c;
	undefined field_0x696d;
	undefined field_0x696e;
	undefined field_0x696f;
	undefined field_0x6970;
	undefined field_0x6971;
	undefined field_0x6972;
	undefined field_0x6973;
	undefined field_0x6974;
	undefined field_0x6975;
	undefined field_0x6976;
	undefined field_0x6977;
	undefined field_0x6978;
	undefined field_0x6979;
	undefined field_0x697a;
	undefined field_0x697b;
	undefined field_0x697c;
	undefined field_0x697d;
	undefined field_0x697e;
	undefined field_0x697f;
	undefined field_0x6980;
	undefined field_0x6981;
	undefined field_0x6982;
	undefined field_0x6983;
	undefined field_0x6984;
	undefined field_0x6985;
	undefined field_0x6986;
	undefined field_0x6987;
	undefined field_0x6988;
	undefined field_0x6989;
	undefined field_0x698a;
	undefined field_0x698b;
	undefined field_0x698c;
	undefined field_0x698d;
	undefined field_0x698e;
	undefined field_0x698f;
	undefined field_0x6990;
	undefined field_0x6991;
	undefined field_0x6992;
	undefined field_0x6993;
	undefined field_0x6994;
	undefined field_0x6995;
	undefined field_0x6996;
	undefined field_0x6997;
	undefined field_0x6998;
	undefined field_0x6999;
	undefined field_0x699a;
	undefined field_0x699b;
	undefined field_0x699c;
	undefined field_0x699d;
	undefined field_0x699e;
	undefined field_0x699f;
	undefined field_0x69a0;
	undefined field_0x69a1;
	undefined field_0x69a2;
	undefined field_0x69a3;
	undefined field_0x69a4;
	undefined field_0x69a5;
	undefined field_0x69a6;
	undefined field_0x69a7;
	undefined field_0x69a8;
	undefined field_0x69a9;
	undefined field_0x69aa;
	undefined field_0x69ab;
	undefined field_0x69ac;
	undefined field_0x69ad;
	undefined field_0x69ae;
	undefined field_0x69af;
	undefined field_0x69b0;
	undefined field_0x69b1;
	undefined field_0x69b2;
	undefined field_0x69b3;
	undefined field_0x69b4;
	undefined field_0x69b5;
	undefined field_0x69b6;
	undefined field_0x69b7;
	undefined field_0x69b8;
	undefined field_0x69b9;
	undefined field_0x69ba;
	undefined field_0x69bb;
	undefined field_0x69bc;
	undefined field_0x69bd;
	undefined field_0x69be;
	undefined field_0x69bf;
	undefined field_0x69c0;
	undefined field_0x69c1;
	undefined field_0x69c2;
	undefined field_0x69c3;
	undefined field_0x69c4;
	undefined field_0x69c5;
	undefined field_0x69c6;
	undefined field_0x69c7;
	undefined field_0x69c8;
	undefined field_0x69c9;
	undefined field_0x69ca;
	undefined field_0x69cb;
	undefined field_0x69cc;
	undefined field_0x69cd;
	undefined field_0x69ce;
	undefined field_0x69cf;
	undefined field_0x69d0;
	undefined field_0x69d1;
	undefined field_0x69d2;
	undefined field_0x69d3;
	undefined field_0x69d4;
	undefined field_0x69d5;
	undefined field_0x69d6;
	undefined field_0x69d7;
	undefined field_0x69d8;
	undefined field_0x69d9;
	undefined field_0x69da;
	undefined field_0x69db;
	undefined field_0x69dc;
	undefined field_0x69dd;
	undefined field_0x69de;
	undefined field_0x69df;
	undefined field_0x69e0;
	undefined field_0x69e1;
	undefined field_0x69e2;
	undefined field_0x69e3;
	undefined field_0x69e4;
	undefined field_0x69e5;
	undefined field_0x69e6;
	undefined field_0x69e7;
	undefined field_0x69e8;
	undefined field_0x69e9;
	undefined field_0x69ea;
	undefined field_0x69eb;
	undefined field_0x69ec;
	undefined field_0x69ed;
	undefined field_0x69ee;
	undefined field_0x69ef;
	undefined field_0x69f0;
	undefined field_0x69f1;
	undefined field_0x69f2;
	undefined field_0x69f3;
	undefined field_0x69f4;
	undefined field_0x69f5;
	undefined field_0x69f6;
	undefined field_0x69f7;
	undefined field_0x69f8;
	undefined field_0x69f9;
	undefined field_0x69fa;
	undefined field_0x69fb;
	undefined field_0x69fc;
	undefined field_0x69fd;
	undefined field_0x69fe;
	undefined field_0x69ff;
	undefined field_0x6a00;
	undefined field_0x6a01;
	undefined field_0x6a02;
	undefined field_0x6a03;
	undefined field_0x6a04;
	undefined field_0x6a05;
	undefined field_0x6a06;
	undefined field_0x6a07;
	undefined field_0x6a08;
	undefined field_0x6a09;
	undefined field_0x6a0a;
	undefined field_0x6a0b;
	undefined field_0x6a0c;
	undefined field_0x6a0d;
	undefined field_0x6a0e;
	undefined field_0x6a0f;
	undefined field_0x6a10;
	undefined field_0x6a11;
	undefined field_0x6a12;
	undefined field_0x6a13;
	undefined field_0x6a14;
	undefined field_0x6a15;
	undefined field_0x6a16;
	undefined field_0x6a17;
	undefined field_0x6a18;
	undefined field_0x6a19;
	undefined field_0x6a1a;
	undefined field_0x6a1b;
	undefined field_0x6a1c;
	undefined field_0x6a1d;
	undefined field_0x6a1e;
	undefined field_0x6a1f;
	undefined field_0x6a20;
	undefined field_0x6a21;
	undefined field_0x6a22;
	undefined field_0x6a23;
	undefined field_0x6a24;
	undefined field_0x6a25;
	undefined field_0x6a26;
	undefined field_0x6a27;
	undefined field_0x6a28;
	undefined field_0x6a29;
	undefined field_0x6a2a;
	undefined field_0x6a2b;
	undefined field_0x6a2c;
	undefined field_0x6a2d;
	undefined field_0x6a2e;
	undefined field_0x6a2f;
	undefined field_0x6a30;
	undefined field_0x6a31;
	undefined field_0x6a32;
	undefined field_0x6a33;
	undefined field_0x6a34;
	undefined field_0x6a35;
	undefined field_0x6a36;
	undefined field_0x6a37;
	undefined field_0x6a38;
	undefined field_0x6a39;
	undefined field_0x6a3a;
	undefined field_0x6a3b;
	undefined field_0x6a3c;
	undefined field_0x6a3d;
	undefined field_0x6a3e;
	undefined field_0x6a3f;
	undefined field_0x6a40;
	undefined field_0x6a41;
	undefined field_0x6a42;
	undefined field_0x6a43;
	undefined field_0x6a44;
	undefined field_0x6a45;
	undefined field_0x6a46;
	undefined field_0x6a47;
	undefined field_0x6a48;
	undefined field_0x6a49;
	undefined field_0x6a4a;
	undefined field_0x6a4b;
	undefined field_0x6a4c;
	undefined field_0x6a4d;
	undefined field_0x6a4e;
	undefined field_0x6a4f;
	undefined field_0x6a50;
	undefined field_0x6a51;
	undefined field_0x6a52;
	undefined field_0x6a53;
	undefined field_0x6a54;
	undefined field_0x6a55;
	undefined field_0x6a56;
	undefined field_0x6a57;
	undefined field_0x6a58;
	undefined field_0x6a59;
	undefined field_0x6a5a;
	undefined field_0x6a5b;
	undefined field_0x6a5c;
	undefined field_0x6a5d;
	undefined field_0x6a5e;
	undefined field_0x6a5f;
	undefined field_0x6a60;
	undefined field_0x6a61;
	undefined field_0x6a62;
	undefined field_0x6a63;
	undefined field_0x6a64;
	undefined field_0x6a65;
	undefined field_0x6a66;
	undefined field_0x6a67;
	undefined field_0x6a68;
	undefined field_0x6a69;
	undefined field_0x6a6a;
	undefined field_0x6a6b;
	undefined field_0x6a6c;
	undefined field_0x6a6d;
	undefined field_0x6a6e;
	undefined field_0x6a6f;
	undefined field_0x6a70;
	undefined field_0x6a71;
	undefined field_0x6a72;
	undefined field_0x6a73;
	undefined field_0x6a74;
	undefined field_0x6a75;
	undefined field_0x6a76;
	undefined field_0x6a77;
	undefined field_0x6a78;
	undefined field_0x6a79;
	undefined field_0x6a7a;
	undefined field_0x6a7b;
	undefined field_0x6a7c;
	undefined field_0x6a7d;
	undefined field_0x6a7e;
	undefined field_0x6a7f;
	undefined field_0x6a80;
	undefined field_0x6a81;
	undefined field_0x6a82;
	undefined field_0x6a83;
	undefined field_0x6a84;
	undefined field_0x6a85;
	undefined field_0x6a86;
	undefined field_0x6a87;
	undefined field_0x6a88;
	undefined field_0x6a89;
	undefined field_0x6a8a;
	undefined field_0x6a8b;
	undefined field_0x6a8c;
	undefined field_0x6a8d;
	undefined field_0x6a8e;
	undefined field_0x6a8f;
	undefined field_0x6a90;
	undefined field_0x6a91;
	undefined field_0x6a92;
	undefined field_0x6a93;
	undefined field_0x6a94;
	undefined field_0x6a95;
	undefined field_0x6a96;
	undefined field_0x6a97;
	undefined field_0x6a98;
	undefined field_0x6a99;
	undefined field_0x6a9a;
	undefined field_0x6a9b;
	undefined field_0x6a9c;
	undefined field_0x6a9d;
	undefined field_0x6a9e;
	undefined field_0x6a9f;
	undefined field_0x6aa0;
	undefined field_0x6aa1;
	undefined field_0x6aa2;
	undefined field_0x6aa3;
	undefined field_0x6aa4;
	undefined field_0x6aa5;
	undefined field_0x6aa6;
	undefined field_0x6aa7;
	undefined field_0x6aa8;
	undefined field_0x6aa9;
	undefined field_0x6aaa;
	undefined field_0x6aab;
	undefined field_0x6aac;
	undefined field_0x6aad;
	undefined field_0x6aae;
	undefined field_0x6aaf;
	undefined field_0x6ab0;
	undefined field_0x6ab1;
	undefined field_0x6ab2;
	undefined field_0x6ab3;
	undefined field_0x6ab4;
	undefined field_0x6ab5;
	undefined field_0x6ab6;
	undefined field_0x6ab7;
	undefined field_0x6ab8;
	undefined field_0x6ab9;
	undefined field_0x6aba;
	undefined field_0x6abb;
	undefined field_0x6abc;
	undefined field_0x6abd;
	undefined field_0x6abe;
	undefined field_0x6abf;
	undefined field_0x6ac0;
	undefined field_0x6ac1;
	undefined field_0x6ac2;
	undefined field_0x6ac3;
	undefined field_0x6ac4;
	undefined field_0x6ac5;
	undefined field_0x6ac6;
	undefined field_0x6ac7;
	undefined field_0x6ac8;
	undefined field_0x6ac9;
	undefined field_0x6aca;
	undefined field_0x6acb;
	undefined field_0x6acc;
	undefined field_0x6acd;
	undefined field_0x6ace;
	undefined field_0x6acf;
	undefined field_0x6ad0;
	undefined field_0x6ad1;
	undefined field_0x6ad2;
	undefined field_0x6ad3;
	undefined field_0x6ad4;
	undefined field_0x6ad5;
	undefined field_0x6ad6;
	undefined field_0x6ad7;
	undefined field_0x6ad8;
	undefined field_0x6ad9;
	undefined field_0x6ada;
	undefined field_0x6adb;
	undefined field_0x6adc;
	undefined field_0x6add;
	undefined field_0x6ade;
	undefined field_0x6adf;
	undefined field_0x6ae0;
	undefined field_0x6ae1;
	undefined field_0x6ae2;
	undefined field_0x6ae3;
	undefined field_0x6ae4;
	undefined field_0x6ae5;
	undefined field_0x6ae6;
	undefined field_0x6ae7;
	undefined field_0x6ae8;
	undefined field_0x6ae9;
	undefined field_0x6aea;
	undefined field_0x6aeb;
	undefined field_0x6aec;
	undefined field_0x6aed;
	undefined field_0x6aee;
	undefined field_0x6aef;
	undefined field_0x6af0;
	undefined field_0x6af1;
	undefined field_0x6af2;
	undefined field_0x6af3;
	undefined field_0x6af4;
	undefined field_0x6af5;
	undefined field_0x6af6;
	undefined field_0x6af7;
	undefined field_0x6af8;
	undefined field_0x6af9;
	undefined field_0x6afa;
	undefined field_0x6afb;
	undefined field_0x6afc;
	undefined field_0x6afd;
	undefined field_0x6afe;
	undefined field_0x6aff;
	undefined field_0x6b00;
	undefined field_0x6b01;
	undefined field_0x6b02;
	undefined field_0x6b03;
	undefined field_0x6b04;
	undefined field_0x6b05;
	undefined field_0x6b06;
	undefined field_0x6b07;
	undefined field_0x6b08;
	undefined field_0x6b09;
	undefined field_0x6b0a;
	undefined field_0x6b0b;
	undefined field_0x6b0c;
	undefined field_0x6b0d;
	undefined field_0x6b0e;
	undefined field_0x6b0f;
	undefined field_0x6b10;
	undefined field_0x6b11;
	undefined field_0x6b12;
	undefined field_0x6b13;
	undefined field_0x6b14;
	undefined field_0x6b15;
	undefined field_0x6b16;
	undefined field_0x6b17;
	undefined field_0x6b18;
	undefined field_0x6b19;
	undefined field_0x6b1a;
	undefined field_0x6b1b;
	undefined field_0x6b1c;
	undefined field_0x6b1d;
	undefined field_0x6b1e;
	undefined field_0x6b1f;
	undefined field_0x6b20;
	undefined field_0x6b21;
	undefined field_0x6b22;
	undefined field_0x6b23;
	undefined field_0x6b24;
	undefined field_0x6b25;
	undefined field_0x6b26;
	undefined field_0x6b27;
	undefined field_0x6b28;
	undefined field_0x6b29;
	undefined field_0x6b2a;
	undefined field_0x6b2b;
	undefined field_0x6b2c;
	undefined field_0x6b2d;
	undefined field_0x6b2e;
	undefined field_0x6b2f;
	undefined field_0x6b30;
	undefined field_0x6b31;
	undefined field_0x6b32;
	undefined field_0x6b33;
	undefined field_0x6b34;
	undefined field_0x6b35;
	undefined field_0x6b36;
	undefined field_0x6b37;
	undefined field_0x6b38;
	undefined field_0x6b39;
	undefined field_0x6b3a;
	undefined field_0x6b3b;
	undefined field_0x6b3c;
	undefined field_0x6b3d;
	undefined field_0x6b3e;
	undefined field_0x6b3f;
	undefined field_0x6b40;
	undefined field_0x6b41;
	undefined field_0x6b42;
	undefined field_0x6b43;
	undefined field_0x6b44;
	undefined field_0x6b45;
	undefined field_0x6b46;
	undefined field_0x6b47;
	undefined field_0x6b48;
	undefined field_0x6b49;
	undefined field_0x6b4a;
	undefined field_0x6b4b;
	undefined field_0x6b4c;
	undefined field_0x6b4d;
	undefined field_0x6b4e;
	undefined field_0x6b4f;
	undefined field_0x6b50;
	undefined field_0x6b51;
	undefined field_0x6b52;
	undefined field_0x6b53;
	undefined field_0x6b54;
	undefined field_0x6b55;
	undefined field_0x6b56;
	undefined field_0x6b57;
	undefined field_0x6b58;
	undefined field_0x6b59;
	undefined field_0x6b5a;
	undefined field_0x6b5b;
	undefined field_0x6b5c;
	undefined field_0x6b5d;
	undefined field_0x6b5e;
	undefined field_0x6b5f;
	undefined field_0x6b60;
	undefined field_0x6b61;
	undefined field_0x6b62;
	undefined field_0x6b63;
	undefined field_0x6b64;
	undefined field_0x6b65;
	undefined field_0x6b66;
	undefined field_0x6b67;
	undefined field_0x6b68;
	undefined field_0x6b69;
	undefined field_0x6b6a;
	undefined field_0x6b6b;
	undefined field_0x6b6c;
	undefined field_0x6b6d;
	undefined field_0x6b6e;
	undefined field_0x6b6f;
	undefined field_0x6b70;
	undefined field_0x6b71;
	undefined field_0x6b72;
	undefined field_0x6b73;
	undefined field_0x6b74;
	undefined field_0x6b75;
	undefined field_0x6b76;
	undefined field_0x6b77;
	undefined field_0x6b78;
	undefined field_0x6b79;
	undefined field_0x6b7a;
	undefined field_0x6b7b;
	undefined field_0x6b7c;
	undefined field_0x6b7d;
	undefined field_0x6b7e;
	undefined field_0x6b7f;
	undefined field_0x6b80;
	undefined field_0x6b81;
	undefined field_0x6b82;
	undefined field_0x6b83;
	undefined field_0x6b84;
	undefined field_0x6b85;
	undefined field_0x6b86;
	undefined field_0x6b87;
	undefined field_0x6b88;
	undefined field_0x6b89;
	undefined field_0x6b8a;
	undefined field_0x6b8b;
	undefined field_0x6b8c;
	undefined field_0x6b8d;
	undefined field_0x6b8e;
	undefined field_0x6b8f;
	undefined field_0x6b90;
	undefined field_0x6b91;
	undefined field_0x6b92;
	undefined field_0x6b93;
	undefined field_0x6b94;
	undefined field_0x6b95;
	undefined field_0x6b96;
	undefined field_0x6b97;
	undefined field_0x6b98;
	undefined field_0x6b99;
	undefined field_0x6b9a;
	undefined field_0x6b9b;
	undefined field_0x6b9c;
	undefined field_0x6b9d;
	undefined field_0x6b9e;
	undefined field_0x6b9f;
	undefined field_0x6ba0;
	undefined field_0x6ba1;
	undefined field_0x6ba2;
	undefined field_0x6ba3;
	undefined field_0x6ba4;
	undefined field_0x6ba5;
	undefined field_0x6ba6;
	undefined field_0x6ba7;
	undefined field_0x6ba8;
	undefined field_0x6ba9;
	undefined field_0x6baa;
	undefined field_0x6bab;
	undefined field_0x6bac;
	undefined field_0x6bad;
	undefined field_0x6bae;
	undefined field_0x6baf;
	undefined field_0x6bb0;
	undefined field_0x6bb1;
	undefined field_0x6bb2;
	undefined field_0x6bb3;
	undefined field_0x6bb4;
	undefined field_0x6bb5;
	undefined field_0x6bb6;
	undefined field_0x6bb7;
	undefined field_0x6bb8;
	undefined field_0x6bb9;
	undefined field_0x6bba;
	undefined field_0x6bbb;
	undefined field_0x6bbc;
	undefined field_0x6bbd;
	undefined field_0x6bbe;
	undefined field_0x6bbf;
	undefined field_0x6bc0;
	undefined field_0x6bc1;
	undefined field_0x6bc2;
	undefined field_0x6bc3;
	undefined field_0x6bc4;
	undefined field_0x6bc5;
	undefined field_0x6bc6;
	undefined field_0x6bc7;
	undefined field_0x6bc8;
	undefined field_0x6bc9;
	undefined field_0x6bca;
	undefined field_0x6bcb;
	undefined field_0x6bcc;
	undefined field_0x6bcd;
	undefined field_0x6bce;
	undefined field_0x6bcf;
	undefined field_0x6bd0;
	undefined field_0x6bd1;
	undefined field_0x6bd2;
	undefined field_0x6bd3;
	undefined field_0x6bd4;
	undefined field_0x6bd5;
	undefined field_0x6bd6;
	undefined field_0x6bd7;
	undefined field_0x6bd8;
	undefined field_0x6bd9;
	undefined field_0x6bda;
	undefined field_0x6bdb;
	undefined field_0x6bdc;
	undefined field_0x6bdd;
	undefined field_0x6bde;
	undefined field_0x6bdf;
	undefined field_0x6be0;
	undefined field_0x6be1;
	undefined field_0x6be2;
	undefined field_0x6be3;
	undefined field_0x6be4;
	undefined field_0x6be5;
	undefined field_0x6be6;
	undefined field_0x6be7;
	undefined field_0x6be8;
	undefined field_0x6be9;
	undefined field_0x6bea;
	undefined field_0x6beb;
	undefined field_0x6bec;
	undefined field_0x6bed;
	undefined field_0x6bee;
	undefined field_0x6bef;
	undefined field_0x6bf0;
	undefined field_0x6bf1;
	undefined field_0x6bf2;
	undefined field_0x6bf3;
	undefined field_0x6bf4;
	undefined field_0x6bf5;
	undefined field_0x6bf6;
	undefined field_0x6bf7;
	undefined field_0x6bf8;
	undefined field_0x6bf9;
	undefined field_0x6bfa;
	undefined field_0x6bfb;
	undefined field_0x6bfc;
	undefined field_0x6bfd;
	undefined field_0x6bfe;
	undefined field_0x6bff;
	undefined field_0x6c00;
	undefined field_0x6c01;
	undefined field_0x6c02;
	undefined field_0x6c03;
	undefined field_0x6c04;
	undefined field_0x6c05;
	undefined field_0x6c06;
	undefined field_0x6c07;
	undefined field_0x6c08;
	undefined field_0x6c09;
	undefined field_0x6c0a;
	undefined field_0x6c0b;
	undefined field_0x6c0c;
	undefined field_0x6c0d;
	undefined field_0x6c0e;
	undefined field_0x6c0f;
	undefined field_0x6c10;
	undefined field_0x6c11;
	undefined field_0x6c12;
	undefined field_0x6c13;
	undefined field_0x6c14;
	undefined field_0x6c15;
	undefined field_0x6c16;
	undefined field_0x6c17;
	undefined field_0x6c18;
	undefined field_0x6c19;
	undefined field_0x6c1a;
	undefined field_0x6c1b;
	undefined field_0x6c1c;
	undefined field_0x6c1d;
	undefined field_0x6c1e;
	undefined field_0x6c1f;
	undefined field_0x6c20;
	undefined field_0x6c21;
	undefined field_0x6c22;
	undefined field_0x6c23;
	undefined field_0x6c24;
	undefined field_0x6c25;
	undefined field_0x6c26;
	undefined field_0x6c27;
	undefined field_0x6c28;
	undefined field_0x6c29;
	undefined field_0x6c2a;
	undefined field_0x6c2b;
	undefined field_0x6c2c;
	undefined field_0x6c2d;
	undefined field_0x6c2e;
	undefined field_0x6c2f;
	undefined field_0x6c30;
	undefined field_0x6c31;
	undefined field_0x6c32;
	undefined field_0x6c33;
	undefined field_0x6c34;
	undefined field_0x6c35;
	undefined field_0x6c36;
	undefined field_0x6c37;
	undefined field_0x6c38;
	undefined field_0x6c39;
	undefined field_0x6c3a;
	undefined field_0x6c3b;
	undefined field_0x6c3c;
	undefined field_0x6c3d;
	undefined field_0x6c3e;
	undefined field_0x6c3f;
	undefined field_0x6c40;
	undefined field_0x6c41;
	undefined field_0x6c42;
	undefined field_0x6c43;
	undefined field_0x6c44;
	undefined field_0x6c45;
	undefined field_0x6c46;
	undefined field_0x6c47;
	undefined field_0x6c48;
	undefined field_0x6c49;
	undefined field_0x6c4a;
	undefined field_0x6c4b;
	undefined field_0x6c4c;
	undefined field_0x6c4d;
	undefined field_0x6c4e;
	undefined field_0x6c4f;
	undefined field_0x6c50;
	undefined field_0x6c51;
	undefined field_0x6c52;
	undefined field_0x6c53;
	undefined field_0x6c54;
	undefined field_0x6c55;
	undefined field_0x6c56;
	undefined field_0x6c57;
	undefined field_0x6c58;
	undefined field_0x6c59;
	undefined field_0x6c5a;
	undefined field_0x6c5b;
	undefined field_0x6c5c;
	undefined field_0x6c5d;
	undefined field_0x6c5e;
	undefined field_0x6c5f;
	undefined field_0x6c60;
	undefined field_0x6c61;
	undefined field_0x6c62;
	undefined field_0x6c63;
	undefined field_0x6c64;
	undefined field_0x6c65;
	undefined field_0x6c66;
	undefined field_0x6c67;
	undefined field_0x6c68;
	undefined field_0x6c69;
	undefined field_0x6c6a;
	undefined field_0x6c6b;
	undefined field_0x6c6c;
	undefined field_0x6c6d;
	undefined field_0x6c6e;
	undefined field_0x6c6f;
	undefined field_0x6c70;
	undefined field_0x6c71;
	undefined field_0x6c72;
	undefined field_0x6c73;
	undefined field_0x6c74;
	undefined field_0x6c75;
	undefined field_0x6c76;
	undefined field_0x6c77;
	undefined field_0x6c78;
	undefined field_0x6c79;
	undefined field_0x6c7a;
	undefined field_0x6c7b;
	undefined field_0x6c7c;
	undefined field_0x6c7d;
	undefined field_0x6c7e;
	undefined field_0x6c7f;
	undefined field_0x6c80;
	undefined field_0x6c81;
	undefined field_0x6c82;
	undefined field_0x6c83;
	undefined field_0x6c84;
	undefined field_0x6c85;
	undefined field_0x6c86;
	undefined field_0x6c87;
	undefined field_0x6c88;
	undefined field_0x6c89;
	undefined field_0x6c8a;
	undefined field_0x6c8b;
	undefined field_0x6c8c;
	undefined field_0x6c8d;
	undefined field_0x6c8e;
	undefined field_0x6c8f;
	undefined field_0x6c90;
	undefined field_0x6c91;
	undefined field_0x6c92;
	undefined field_0x6c93;
	undefined field_0x6c94;
	undefined field_0x6c95;
	undefined field_0x6c96;
	undefined field_0x6c97;
	undefined field_0x6c98;
	undefined field_0x6c99;
	undefined field_0x6c9a;
	undefined field_0x6c9b;
	undefined field_0x6c9c;
	undefined field_0x6c9d;
	undefined field_0x6c9e;
	undefined field_0x6c9f;
	undefined field_0x6ca0;
	undefined field_0x6ca1;
	undefined field_0x6ca2;
	undefined field_0x6ca3;
	undefined field_0x6ca4;
	undefined field_0x6ca5;
	undefined field_0x6ca6;
	undefined field_0x6ca7;
	undefined field_0x6ca8;
	undefined field_0x6ca9;
	undefined field_0x6caa;
	undefined field_0x6cab;
	undefined field_0x6cac;
	undefined field_0x6cad;
	undefined field_0x6cae;
	undefined field_0x6caf;
	undefined field_0x6cb0;
	undefined field_0x6cb1;
	undefined field_0x6cb2;
	undefined field_0x6cb3;
	undefined field_0x6cb4;
	undefined field_0x6cb5;
	undefined field_0x6cb6;
	undefined field_0x6cb7;
	undefined field_0x6cb8;
	undefined field_0x6cb9;
	undefined field_0x6cba;
	undefined field_0x6cbb;
	undefined field_0x6cbc;
	undefined field_0x6cbd;
	undefined field_0x6cbe;
	undefined field_0x6cbf;
	undefined field_0x6cc0;
	undefined field_0x6cc1;
	undefined field_0x6cc2;
	undefined field_0x6cc3;
	undefined field_0x6cc4;
	undefined field_0x6cc5;
	undefined field_0x6cc6;
	undefined field_0x6cc7;
	undefined field_0x6cc8;
	undefined field_0x6cc9;
	undefined field_0x6cca;
	undefined field_0x6ccb;
	undefined field_0x6ccc;
	undefined field_0x6ccd;
	undefined field_0x6cce;
	undefined field_0x6ccf;
	undefined field_0x6cd0;
	undefined field_0x6cd1;
	undefined field_0x6cd2;
	undefined field_0x6cd3;
	undefined field_0x6cd4;
	undefined field_0x6cd5;
	undefined field_0x6cd6;
	undefined field_0x6cd7;
	undefined field_0x6cd8;
	undefined field_0x6cd9;
	undefined field_0x6cda;
	undefined field_0x6cdb;
	undefined field_0x6cdc;
	undefined field_0x6cdd;
	undefined field_0x6cde;
	undefined field_0x6cdf;
	undefined field_0x6ce0;
	undefined field_0x6ce1;
	undefined field_0x6ce2;
	undefined field_0x6ce3;
	undefined field_0x6ce4;
	undefined field_0x6ce5;
	undefined field_0x6ce6;
	undefined field_0x6ce7;
	undefined field_0x6ce8;
	undefined field_0x6ce9;
	undefined field_0x6cea;
	undefined field_0x6ceb;
	undefined field_0x6cec;
	undefined field_0x6ced;
	undefined field_0x6cee;
	undefined field_0x6cef;
	undefined field_0x6cf0;
	undefined field_0x6cf1;
	undefined field_0x6cf2;
	undefined field_0x6cf3;
	undefined field_0x6cf4;
	undefined field_0x6cf5;
	undefined field_0x6cf6;
	undefined field_0x6cf7;
	undefined field_0x6cf8;
	undefined field_0x6cf9;
	undefined field_0x6cfa;
	undefined field_0x6cfb;
	undefined field_0x6cfc;
	undefined field_0x6cfd;
	undefined field_0x6cfe;
	undefined field_0x6cff;
	undefined field_0x6d00;
	undefined field_0x6d01;
	undefined field_0x6d02;
	undefined field_0x6d03;
	undefined field_0x6d04;
	undefined field_0x6d05;
	undefined field_0x6d06;
	undefined field_0x6d07;
	undefined field_0x6d08;
	undefined field_0x6d09;
	undefined field_0x6d0a;
	undefined field_0x6d0b;
	undefined field_0x6d0c;
	undefined field_0x6d0d;
	undefined field_0x6d0e;
	undefined field_0x6d0f;
	undefined field_0x6d10;
	undefined field_0x6d11;
	undefined field_0x6d12;
	undefined field_0x6d13;
	undefined field_0x6d14;
	undefined field_0x6d15;
	undefined field_0x6d16;
	undefined field_0x6d17;
	undefined field_0x6d18;
	undefined field_0x6d19;
	undefined field_0x6d1a;
	undefined field_0x6d1b;
	undefined field_0x6d1c;
	undefined field_0x6d1d;
	undefined field_0x6d1e;
	undefined field_0x6d1f;
	undefined field_0x6d20;
	undefined field_0x6d21;
	undefined field_0x6d22;
	undefined field_0x6d23;
	undefined field_0x6d24;
	undefined field_0x6d25;
	undefined field_0x6d26;
	undefined field_0x6d27;
	undefined field_0x6d28;
	undefined field_0x6d29;
	undefined field_0x6d2a;
	undefined field_0x6d2b;
	undefined field_0x6d2c;
	undefined field_0x6d2d;
	undefined field_0x6d2e;
	undefined field_0x6d2f;
	undefined field_0x6d30;
	undefined field_0x6d31;
	undefined field_0x6d32;
	undefined field_0x6d33;
	undefined field_0x6d34;
	undefined field_0x6d35;
	undefined field_0x6d36;
	undefined field_0x6d37;
	undefined field_0x6d38;
	undefined field_0x6d39;
	undefined field_0x6d3a;
	undefined field_0x6d3b;
	undefined field_0x6d3c;
	undefined field_0x6d3d;
	undefined field_0x6d3e;
	undefined field_0x6d3f;
	undefined field_0x6d40;
	undefined field_0x6d41;
	undefined field_0x6d42;
	undefined field_0x6d43;
	undefined field_0x6d44;
	undefined field_0x6d45;
	undefined field_0x6d46;
	undefined field_0x6d47;
	undefined field_0x6d48;
	undefined field_0x6d49;
	undefined field_0x6d4a;
	undefined field_0x6d4b;
	undefined field_0x6d4c;
	undefined field_0x6d4d;
	undefined field_0x6d4e;
	undefined field_0x6d4f;
	undefined field_0x6d50;
	undefined field_0x6d51;
	undefined field_0x6d52;
	undefined field_0x6d53;
	undefined field_0x6d54;
	undefined field_0x6d55;
	undefined field_0x6d56;
	undefined field_0x6d57;
	undefined field_0x6d58;
	undefined field_0x6d59;
	undefined field_0x6d5a;
	undefined field_0x6d5b;
	undefined field_0x6d5c;
	undefined field_0x6d5d;
	undefined field_0x6d5e;
	undefined field_0x6d5f;
	undefined field_0x6d60;
	undefined field_0x6d61;
	undefined field_0x6d62;
	undefined field_0x6d63;
	undefined field_0x6d64;
	undefined field_0x6d65;
	undefined field_0x6d66;
	undefined field_0x6d67;
	undefined field_0x6d68;
	undefined field_0x6d69;
	undefined field_0x6d6a;
	undefined field_0x6d6b;
	undefined field_0x6d6c;
	undefined field_0x6d6d;
	undefined field_0x6d6e;
	undefined field_0x6d6f;
	undefined field_0x6d70;
	undefined field_0x6d71;
	undefined field_0x6d72;
	undefined field_0x6d73;
	undefined field_0x6d74;
	undefined field_0x6d75;
	undefined field_0x6d76;
	undefined field_0x6d77;
	undefined field_0x6d78;
	undefined field_0x6d79;
	undefined field_0x6d7a;
	undefined field_0x6d7b;
	undefined field_0x6d7c;
	undefined field_0x6d7d;
	undefined field_0x6d7e;
	undefined field_0x6d7f;
	undefined field_0x6d80;
	undefined field_0x6d81;
	undefined field_0x6d82;
	undefined field_0x6d83;
	undefined field_0x6d84;
	undefined field_0x6d85;
	undefined field_0x6d86;
	undefined field_0x6d87;
	undefined field_0x6d88;
	undefined field_0x6d89;
	undefined field_0x6d8a;
	undefined field_0x6d8b;
	undefined field_0x6d8c;
	undefined field_0x6d8d;
	undefined field_0x6d8e;
	undefined field_0x6d8f;
	undefined field_0x6d90;
	undefined field_0x6d91;
	undefined field_0x6d92;
	undefined field_0x6d93;
	undefined field_0x6d94;
	undefined field_0x6d95;
	undefined field_0x6d96;
	undefined field_0x6d97;
	undefined field_0x6d98;
	undefined field_0x6d99;
	undefined field_0x6d9a;
	undefined field_0x6d9b;
	undefined field_0x6d9c;
	undefined field_0x6d9d;
	undefined field_0x6d9e;
	undefined field_0x6d9f;
	undefined field_0x6da0;
	undefined field_0x6da1;
	undefined field_0x6da2;
	undefined field_0x6da3;
	undefined field_0x6da4;
	undefined field_0x6da5;
	undefined field_0x6da6;
	undefined field_0x6da7;
	undefined field_0x6da8;
	undefined field_0x6da9;
	undefined field_0x6daa;
	undefined field_0x6dab;
	undefined field_0x6dac;
	undefined field_0x6dad;
	undefined field_0x6dae;
	undefined field_0x6daf;
	undefined field_0x6db0;
	undefined field_0x6db1;
	undefined field_0x6db2;
	undefined field_0x6db3;
	undefined field_0x6db4;
	undefined field_0x6db5;
	undefined field_0x6db6;
	undefined field_0x6db7;
	undefined field_0x6db8;
	undefined field_0x6db9;
	undefined field_0x6dba;
	undefined field_0x6dbb;
	undefined field_0x6dbc;
	undefined field_0x6dbd;
	undefined field_0x6dbe;
	undefined field_0x6dbf;
	undefined field_0x6dc0;
	undefined field_0x6dc1;
	undefined field_0x6dc2;
	undefined field_0x6dc3;
	undefined field_0x6dc4;
	undefined field_0x6dc5;
	undefined field_0x6dc6;
	undefined field_0x6dc7;
	undefined field_0x6dc8;
	undefined field_0x6dc9;
	undefined field_0x6dca;
	undefined field_0x6dcb;
	undefined field_0x6dcc;
	undefined field_0x6dcd;
	undefined field_0x6dce;
	undefined field_0x6dcf;
	undefined field_0x6dd0;
	undefined field_0x6dd1;
	undefined field_0x6dd2;
	undefined field_0x6dd3;
	undefined field_0x6dd4;
	undefined field_0x6dd5;
	undefined field_0x6dd6;
	undefined field_0x6dd7;
	undefined field_0x6dd8;
	undefined field_0x6dd9;
	undefined field_0x6dda;
	undefined field_0x6ddb;
	undefined field_0x6ddc;
	undefined field_0x6ddd;
	undefined field_0x6dde;
	undefined field_0x6ddf;
	undefined field_0x6de0;
	undefined field_0x6de1;
	undefined field_0x6de2;
	undefined field_0x6de3;
	undefined field_0x6de4;
	undefined field_0x6de5;
	undefined field_0x6de6;
	undefined field_0x6de7;
	undefined field_0x6de8;
	undefined field_0x6de9;
	undefined field_0x6dea;
	undefined field_0x6deb;
	undefined field_0x6dec;
	undefined field_0x6ded;
	undefined field_0x6dee;
	undefined field_0x6def;
	undefined field_0x6df0;
	undefined field_0x6df1;
	undefined field_0x6df2;
	undefined field_0x6df3;
	undefined field_0x6df4;
	undefined field_0x6df5;
	undefined field_0x6df6;
	undefined field_0x6df7;
	undefined field_0x6df8;
	undefined field_0x6df9;
	undefined field_0x6dfa;
	undefined field_0x6dfb;
	undefined field_0x6dfc;
	undefined field_0x6dfd;
	undefined field_0x6dfe;
	undefined field_0x6dff;
	undefined field_0x6e00;
	undefined field_0x6e01;
	undefined field_0x6e02;
	undefined field_0x6e03;
	undefined field_0x6e04;
	undefined field_0x6e05;
	undefined field_0x6e06;
	undefined field_0x6e07;
	undefined field_0x6e08;
	undefined field_0x6e09;
	undefined field_0x6e0a;
	undefined field_0x6e0b;
	undefined field_0x6e0c;
	undefined field_0x6e0d;
	undefined field_0x6e0e;
	undefined field_0x6e0f;
	undefined field_0x6e10;
	undefined field_0x6e11;
	undefined field_0x6e12;
	undefined field_0x6e13;
	undefined field_0x6e14;
	undefined field_0x6e15;
	undefined field_0x6e16;
	undefined field_0x6e17;
	undefined field_0x6e18;
	undefined field_0x6e19;
	undefined field_0x6e1a;
	undefined field_0x6e1b;
	undefined field_0x6e1c;
	undefined field_0x6e1d;
	undefined field_0x6e1e;
	undefined field_0x6e1f;
	undefined field_0x6e20;
	undefined field_0x6e21;
	undefined field_0x6e22;
	undefined field_0x6e23;
	undefined field_0x6e24;
	undefined field_0x6e25;
	undefined field_0x6e26;
	undefined field_0x6e27;
	undefined field_0x6e28;
	undefined field_0x6e29;
	undefined field_0x6e2a;
	undefined field_0x6e2b;
	undefined field_0x6e2c;
	undefined field_0x6e2d;
	undefined field_0x6e2e;
	undefined field_0x6e2f;
	undefined field_0x6e30;
	undefined field_0x6e31;
	undefined field_0x6e32;
	undefined field_0x6e33;
	undefined field_0x6e34;
	undefined field_0x6e35;
	undefined field_0x6e36;
	undefined field_0x6e37;
	undefined field_0x6e38;
	undefined field_0x6e39;
	undefined field_0x6e3a;
	undefined field_0x6e3b;
	undefined field_0x6e3c;
	undefined field_0x6e3d;
	undefined field_0x6e3e;
	undefined field_0x6e3f;
	undefined field_0x6e40;
	undefined field_0x6e41;
	undefined field_0x6e42;
	undefined field_0x6e43;
	undefined field_0x6e44;
	undefined field_0x6e45;
	undefined field_0x6e46;
	undefined field_0x6e47;
	undefined field_0x6e48;
	undefined field_0x6e49;
	undefined field_0x6e4a;
	undefined field_0x6e4b;
	undefined field_0x6e4c;
	undefined field_0x6e4d;
	undefined field_0x6e4e;
	undefined field_0x6e4f;
	undefined field_0x6e50;
	undefined field_0x6e51;
	undefined field_0x6e52;
	undefined field_0x6e53;
	undefined field_0x6e54;
	undefined field_0x6e55;
	undefined field_0x6e56;
	undefined field_0x6e57;
	undefined field_0x6e58;
	undefined field_0x6e59;
	undefined field_0x6e5a;
	undefined field_0x6e5b;
	undefined field_0x6e5c;
	undefined field_0x6e5d;
	undefined field_0x6e5e;
	undefined field_0x6e5f;
	undefined field_0x6e60;
	undefined field_0x6e61;
	undefined field_0x6e62;
	undefined field_0x6e63;
	undefined field_0x6e64;
	undefined field_0x6e65;
	undefined field_0x6e66;
	undefined field_0x6e67;
	undefined field_0x6e68;
	undefined field_0x6e69;
	undefined field_0x6e6a;
	undefined field_0x6e6b;
	undefined field_0x6e6c;
	undefined field_0x6e6d;
	undefined field_0x6e6e;
	undefined field_0x6e6f;
	undefined field_0x6e70;
	undefined field_0x6e71;
	undefined field_0x6e72;
	undefined field_0x6e73;
	undefined field_0x6e74;
	undefined field_0x6e75;
	undefined field_0x6e76;
	undefined field_0x6e77;
	undefined field_0x6e78;
	undefined field_0x6e79;
	undefined field_0x6e7a;
	undefined field_0x6e7b;
	undefined field_0x6e7c;
	undefined field_0x6e7d;
	undefined field_0x6e7e;
	undefined field_0x6e7f;
	undefined field_0x6e80;
	undefined field_0x6e81;
	undefined field_0x6e82;
	undefined field_0x6e83;
	undefined field_0x6e84;
	undefined field_0x6e85;
	undefined field_0x6e86;
	undefined field_0x6e87;
	undefined field_0x6e88;
	undefined field_0x6e89;
	undefined field_0x6e8a;
	undefined field_0x6e8b;
	undefined field_0x6e8c;
	undefined field_0x6e8d;
	undefined field_0x6e8e;
	undefined field_0x6e8f;
	undefined field_0x6e90;
	undefined field_0x6e91;
	undefined field_0x6e92;
	undefined field_0x6e93;
	undefined field_0x6e94;
	undefined field_0x6e95;
	undefined field_0x6e96;
	undefined field_0x6e97;
	undefined field_0x6e98;
	undefined field_0x6e99;
	undefined field_0x6e9a;
	undefined field_0x6e9b;
	undefined field_0x6e9c;
	undefined field_0x6e9d;
	undefined field_0x6e9e;
	undefined field_0x6e9f;
	undefined field_0x6ea0;
	undefined field_0x6ea1;
	undefined field_0x6ea2;
	undefined field_0x6ea3;
	undefined field_0x6ea4;
	undefined field_0x6ea5;
	undefined field_0x6ea6;
	undefined field_0x6ea7;
	undefined field_0x6ea8;
	undefined field_0x6ea9;
	undefined field_0x6eaa;
	undefined field_0x6eab;
	undefined field_0x6eac;
	undefined field_0x6ead;
	undefined field_0x6eae;
	undefined field_0x6eaf;
	undefined field_0x6eb0;
	undefined field_0x6eb1;
	undefined field_0x6eb2;
	undefined field_0x6eb3;
	undefined field_0x6eb4;
	undefined field_0x6eb5;
	undefined field_0x6eb6;
	undefined field_0x6eb7;
	undefined field_0x6eb8;
	undefined field_0x6eb9;
	undefined field_0x6eba;
	undefined field_0x6ebb;
	undefined field_0x6ebc;
	undefined field_0x6ebd;
	undefined field_0x6ebe;
	undefined field_0x6ebf;
	undefined field_0x6ec0;
	undefined field_0x6ec1;
	undefined field_0x6ec2;
	undefined field_0x6ec3;
	undefined field_0x6ec4;
	undefined field_0x6ec5;
	undefined field_0x6ec6;
	undefined field_0x6ec7;
	undefined field_0x6ec8;
	undefined field_0x6ec9;
	undefined field_0x6eca;
	undefined field_0x6ecb;
	undefined field_0x6ecc;
	undefined field_0x6ecd;
	undefined field_0x6ece;
	undefined field_0x6ecf;
	undefined field_0x6ed0;
	undefined field_0x6ed1;
	undefined field_0x6ed2;
	undefined field_0x6ed3;
	undefined field_0x6ed4;
	undefined field_0x6ed5;
	undefined field_0x6ed6;
	undefined field_0x6ed7;
	undefined field_0x6ed8;
	undefined field_0x6ed9;
	undefined field_0x6eda;
	undefined field_0x6edb;
	undefined field_0x6edc;
	undefined field_0x6edd;
	undefined field_0x6ede;
	undefined field_0x6edf;
	undefined field_0x6ee0;
	undefined field_0x6ee1;
	undefined field_0x6ee2;
	undefined field_0x6ee3;
	undefined field_0x6ee4;
	undefined field_0x6ee5;
	undefined field_0x6ee6;
	undefined field_0x6ee7;
	undefined field_0x6ee8;
	undefined field_0x6ee9;
	undefined field_0x6eea;
	undefined field_0x6eeb;
	undefined field_0x6eec;
	undefined field_0x6eed;
	undefined field_0x6eee;
	undefined field_0x6eef;
	undefined field_0x6ef0;
	undefined field_0x6ef1;
	undefined field_0x6ef2;
	undefined field_0x6ef3;
	undefined field_0x6ef4;
	undefined field_0x6ef5;
	undefined field_0x6ef6;
	undefined field_0x6ef7;
	undefined field_0x6ef8;
	undefined field_0x6ef9;
	undefined field_0x6efa;
	undefined field_0x6efb;
	undefined field_0x6efc;
	undefined field_0x6efd;
	undefined field_0x6efe;
	undefined field_0x6eff;
	undefined field_0x6f00;
	undefined field_0x6f01;
	undefined field_0x6f02;
	undefined field_0x6f03;
	undefined field_0x6f04;
	undefined field_0x6f05;
	undefined field_0x6f06;
	undefined field_0x6f07;
	undefined field_0x6f08;
	undefined field_0x6f09;
	undefined field_0x6f0a;
	undefined field_0x6f0b;
	undefined field_0x6f0c;
	undefined field_0x6f0d;
	undefined field_0x6f0e;
	undefined field_0x6f0f;
	undefined field_0x6f10;
	undefined field_0x6f11;
	undefined field_0x6f12;
	undefined field_0x6f13;
	undefined field_0x6f14;
	undefined field_0x6f15;
	undefined field_0x6f16;
	undefined field_0x6f17;
	undefined field_0x6f18;
	undefined field_0x6f19;
	undefined field_0x6f1a;
	undefined field_0x6f1b;
	undefined field_0x6f1c;
	undefined field_0x6f1d;
	undefined field_0x6f1e;
	undefined field_0x6f1f;
	undefined field_0x6f20;
	undefined field_0x6f21;
	undefined field_0x6f22;
	undefined field_0x6f23;
	undefined field_0x6f24;
	undefined field_0x6f25;
	undefined field_0x6f26;
	undefined field_0x6f27;
	undefined field_0x6f28;
	undefined field_0x6f29;
	undefined field_0x6f2a;
	undefined field_0x6f2b;
	undefined field_0x6f2c;
	undefined field_0x6f2d;
	undefined field_0x6f2e;
	undefined field_0x6f2f;
	undefined field_0x6f30;
	undefined field_0x6f31;
	undefined field_0x6f32;
	undefined field_0x6f33;
	undefined field_0x6f34;
	undefined field_0x6f35;
	undefined field_0x6f36;
	undefined field_0x6f37;
	undefined field_0x6f38;
	undefined field_0x6f39;
	undefined field_0x6f3a;
	undefined field_0x6f3b;
	undefined field_0x6f3c;
	undefined field_0x6f3d;
	undefined field_0x6f3e;
	undefined field_0x6f3f;
	undefined field_0x6f40;
	undefined field_0x6f41;
	undefined field_0x6f42;
	undefined field_0x6f43;
	undefined field_0x6f44;
	undefined field_0x6f45;
	undefined field_0x6f46;
	undefined field_0x6f47;
	undefined field_0x6f48;
	undefined field_0x6f49;
	undefined field_0x6f4a;
	undefined field_0x6f4b;
	undefined field_0x6f4c;
	undefined field_0x6f4d;
	undefined field_0x6f4e;
	undefined field_0x6f4f;
	undefined field_0x6f50;
	undefined field_0x6f51;
	undefined field_0x6f52;
	undefined field_0x6f53;
	undefined field_0x6f54;
	undefined field_0x6f55;
	undefined field_0x6f56;
	undefined field_0x6f57;
	undefined field_0x6f58;
	undefined field_0x6f59;
	undefined field_0x6f5a;
	undefined field_0x6f5b;
	undefined field_0x6f5c;
	undefined field_0x6f5d;
	undefined field_0x6f5e;
	undefined field_0x6f5f;
	undefined field_0x6f60;
	undefined field_0x6f61;
	undefined field_0x6f62;
	undefined field_0x6f63;
	undefined field_0x6f64;
	undefined field_0x6f65;
	undefined field_0x6f66;
	undefined field_0x6f67;
	undefined field_0x6f68;
	undefined field_0x6f69;
	undefined field_0x6f6a;
	undefined field_0x6f6b;
	undefined field_0x6f6c;
	undefined field_0x6f6d;
	undefined field_0x6f6e;
	undefined field_0x6f6f;
	undefined field_0x6f70;
	undefined field_0x6f71;
	undefined field_0x6f72;
	undefined field_0x6f73;
	undefined field_0x6f74;
	undefined field_0x6f75;
	undefined field_0x6f76;
	undefined field_0x6f77;
	undefined field_0x6f78;
	undefined field_0x6f79;
	undefined field_0x6f7a;
	undefined field_0x6f7b;
	undefined field_0x6f7c;
	undefined field_0x6f7d;
	undefined field_0x6f7e;
	undefined field_0x6f7f;
	undefined field_0x6f80;
	undefined field_0x6f81;
	undefined field_0x6f82;
	undefined field_0x6f83;
	undefined field_0x6f84;
	undefined field_0x6f85;
	undefined field_0x6f86;
	undefined field_0x6f87;
	undefined field_0x6f88;
	undefined field_0x6f89;
	undefined field_0x6f8a;
	undefined field_0x6f8b;
	undefined field_0x6f8c;
	undefined field_0x6f8d;
	undefined field_0x6f8e;
	undefined field_0x6f8f;
	undefined field_0x6f90;
	undefined field_0x6f91;
	undefined field_0x6f92;
	undefined field_0x6f93;
	undefined field_0x6f94;
	undefined field_0x6f95;
	undefined field_0x6f96;
	undefined field_0x6f97;
	undefined field_0x6f98;
	undefined field_0x6f99;
	undefined field_0x6f9a;
	undefined field_0x6f9b;
	undefined field_0x6f9c;
	undefined field_0x6f9d;
	undefined field_0x6f9e;
	undefined field_0x6f9f;
	undefined field_0x6fa0;
	undefined field_0x6fa1;
	undefined field_0x6fa2;
	undefined field_0x6fa3;
	undefined field_0x6fa4;
	undefined field_0x6fa5;
	undefined field_0x6fa6;
	undefined field_0x6fa7;
	undefined field_0x6fa8;
	undefined field_0x6fa9;
	undefined field_0x6faa;
	undefined field_0x6fab;
	undefined field_0x6fac;
	undefined field_0x6fad;
	undefined field_0x6fae;
	undefined field_0x6faf;
	undefined field_0x6fb0;
	undefined field_0x6fb1;
	undefined field_0x6fb2;
	undefined field_0x6fb3;
	undefined field_0x6fb4;
	undefined field_0x6fb5;
	undefined field_0x6fb6;
	undefined field_0x6fb7;
	undefined field_0x6fb8;
	undefined field_0x6fb9;
	undefined field_0x6fba;
	undefined field_0x6fbb;
	undefined field_0x6fbc;
	undefined field_0x6fbd;
	undefined field_0x6fbe;
	undefined field_0x6fbf;
	undefined field_0x6fc0;
	undefined field_0x6fc1;
	undefined field_0x6fc2;
	undefined field_0x6fc3;
	undefined field_0x6fc4;
	undefined field_0x6fc5;
	undefined field_0x6fc6;
	undefined field_0x6fc7;
	undefined field_0x6fc8;
	undefined field_0x6fc9;
	undefined field_0x6fca;
	undefined field_0x6fcb;
	undefined field_0x6fcc;
	undefined field_0x6fcd;
	undefined field_0x6fce;
	undefined field_0x6fcf;
	undefined field_0x6fd0;
	undefined field_0x6fd1;
	undefined field_0x6fd2;
	undefined field_0x6fd3;
	undefined field_0x6fd4;
	undefined field_0x6fd5;
	undefined field_0x6fd6;
	undefined field_0x6fd7;
	undefined field_0x6fd8;
	undefined field_0x6fd9;
	undefined field_0x6fda;
	undefined field_0x6fdb;
	undefined field_0x6fdc;
	undefined field_0x6fdd;
	undefined field_0x6fde;
	undefined field_0x6fdf;
	undefined field_0x6fe0;
	undefined field_0x6fe1;
	undefined field_0x6fe2;
	undefined field_0x6fe3;
	undefined field_0x6fe4;
	undefined field_0x6fe5;
	undefined field_0x6fe6;
	undefined field_0x6fe7;
	undefined field_0x6fe8;
	undefined field_0x6fe9;
	undefined field_0x6fea;
	undefined field_0x6feb;
	undefined field_0x6fec;
	undefined field_0x6fed;
	undefined field_0x6fee;
	undefined field_0x6fef;
	undefined field_0x6ff0;
	undefined field_0x6ff1;
	undefined field_0x6ff2;
	undefined field_0x6ff3;
	undefined field_0x6ff4;
	undefined field_0x6ff5;
	undefined field_0x6ff6;
	undefined field_0x6ff7;
	undefined field_0x6ff8;
	undefined field_0x6ff9;
	undefined field_0x6ffa;
	undefined field_0x6ffb;
	undefined field_0x6ffc;
	undefined field_0x6ffd;
	undefined field_0x6ffe;
	undefined field_0x6fff;
	undefined field_0x7000;
	undefined field_0x7001;
	undefined field_0x7002;
	undefined field_0x7003;
	undefined field_0x7004;
	undefined field_0x7005;
	undefined field_0x7006;
	undefined field_0x7007;
	undefined field_0x7008;
	undefined field_0x7009;
	undefined field_0x700a;
	undefined field_0x700b;
	undefined field_0x700c;
	undefined field_0x700d;
	undefined field_0x700e;
	undefined field_0x700f;
	undefined field_0x7010;
	undefined field_0x7011;
	undefined field_0x7012;
	undefined field_0x7013;
	undefined field_0x7014;
	undefined field_0x7015;
	undefined field_0x7016;
	undefined field_0x7017;
	undefined field_0x7018;
	undefined field_0x7019;
	undefined field_0x701a;
	undefined field_0x701b;
	undefined field_0x701c;
	undefined field_0x701d;
	undefined field_0x701e;
	undefined field_0x701f;
	undefined field_0x7020;
	undefined field_0x7021;
	undefined field_0x7022;
	undefined field_0x7023;
	undefined field_0x7024;
	undefined field_0x7025;
	undefined field_0x7026;
	undefined field_0x7027;
	undefined field_0x7028;
	undefined field_0x7029;
	undefined field_0x702a;
	undefined field_0x702b;
	undefined field_0x702c;
	undefined field_0x702d;
	undefined field_0x702e;
	undefined field_0x702f;
	undefined field_0x7030;
	undefined field_0x7031;
	undefined field_0x7032;
	undefined field_0x7033;
	undefined field_0x7034;
	undefined field_0x7035;
	undefined field_0x7036;
	undefined field_0x7037;
	undefined field_0x7038;
	undefined field_0x7039;
	undefined field_0x703a;
	undefined field_0x703b;
	undefined field_0x703c;
	undefined field_0x703d;
	undefined field_0x703e;
	undefined field_0x703f;
	undefined field_0x7040;
	undefined field_0x7041;
	undefined field_0x7042;
	undefined field_0x7043;
	undefined field_0x7044;
	undefined field_0x7045;
	undefined field_0x7046;
	undefined field_0x7047;
	undefined field_0x7048;
	undefined field_0x7049;
	undefined field_0x704a;
	undefined field_0x704b;
	undefined field_0x704c;
	undefined field_0x704d;
	undefined field_0x704e;
	undefined field_0x704f;
	undefined field_0x7050;
	undefined field_0x7051;
	undefined field_0x7052;
	undefined field_0x7053;
	undefined field_0x7054;
	undefined field_0x7055;
	undefined field_0x7056;
	undefined field_0x7057;
	undefined field_0x7058;
	undefined field_0x7059;
	undefined field_0x705a;
	undefined field_0x705b;
	undefined field_0x705c;
	undefined field_0x705d;
	undefined field_0x705e;
	undefined field_0x705f;
	undefined field_0x7060;
	undefined field_0x7061;
	undefined field_0x7062;
	undefined field_0x7063;
	undefined field_0x7064;
	undefined field_0x7065;
	undefined field_0x7066;
	undefined field_0x7067;
	undefined field_0x7068;
	undefined field_0x7069;
	undefined field_0x706a;
	undefined field_0x706b;
	undefined field_0x706c;
	undefined field_0x706d;
	undefined field_0x706e;
	undefined field_0x706f;
	undefined field_0x7070;
	undefined field_0x7071;
	undefined field_0x7072;
	undefined field_0x7073;
	undefined field_0x7074;
	undefined field_0x7075;
	undefined field_0x7076;
	undefined field_0x7077;
	undefined field_0x7078;
	undefined field_0x7079;
	undefined field_0x707a;
	undefined field_0x707b;
	undefined field_0x707c;
	undefined field_0x707d;
	undefined field_0x707e;
	undefined field_0x707f;
	undefined field_0x7080;
	undefined field_0x7081;
	undefined field_0x7082;
	undefined field_0x7083;
	undefined field_0x7084;
	undefined field_0x7085;
	undefined field_0x7086;
	undefined field_0x7087;
	undefined field_0x7088;
	undefined field_0x7089;
	undefined field_0x708a;
	undefined field_0x708b;
	undefined field_0x708c;
	undefined field_0x708d;
	undefined field_0x708e;
	undefined field_0x708f;
	undefined field_0x7090;
	undefined field_0x7091;
	undefined field_0x7092;
	undefined field_0x7093;
	undefined field_0x7094;
	undefined field_0x7095;
	undefined field_0x7096;
	undefined field_0x7097;
	undefined field_0x7098;
	undefined field_0x7099;
	undefined field_0x709a;
	undefined field_0x709b;
	undefined field_0x709c;
	undefined field_0x709d;
	undefined field_0x709e;
	undefined field_0x709f;
	undefined field_0x70a0;
	undefined field_0x70a1;
	undefined field_0x70a2;
	undefined field_0x70a3;
	undefined field_0x70a4;
	undefined field_0x70a5;
	undefined field_0x70a6;
	undefined field_0x70a7;
	undefined field_0x70a8;
	undefined field_0x70a9;
	undefined field_0x70aa;
	undefined field_0x70ab;
	undefined field_0x70ac;
	undefined field_0x70ad;
	undefined field_0x70ae;
	undefined field_0x70af;
	undefined field_0x70b0;
	undefined field_0x70b1;
	undefined field_0x70b2;
	undefined field_0x70b3;
	undefined field_0x70b4;
	undefined field_0x70b5;
	undefined field_0x70b6;
	undefined field_0x70b7;
	undefined field_0x70b8;
	undefined field_0x70b9;
	undefined field_0x70ba;
	undefined field_0x70bb;
	undefined field_0x70bc;
	undefined field_0x70bd;
	undefined field_0x70be;
	undefined field_0x70bf;
	undefined field_0x70c0;
	undefined field_0x70c1;
	undefined field_0x70c2;
	undefined field_0x70c3;
	undefined field_0x70c4;
	undefined field_0x70c5;
	undefined field_0x70c6;
	undefined field_0x70c7;
	undefined field_0x70c8;
	undefined field_0x70c9;
	undefined field_0x70ca;
	undefined field_0x70cb;
	undefined field_0x70cc;
	undefined field_0x70cd;
	undefined field_0x70ce;
	undefined field_0x70cf;
	undefined field_0x70d0;
	undefined field_0x70d1;
	undefined field_0x70d2;
	undefined field_0x70d3;
	undefined field_0x70d4;
	undefined field_0x70d5;
	undefined field_0x70d6;
	undefined field_0x70d7;
	undefined field_0x70d8;
	undefined field_0x70d9;
	undefined field_0x70da;
	undefined field_0x70db;
	undefined field_0x70dc;
	undefined field_0x70dd;
	undefined field_0x70de;
	undefined field_0x70df;
	undefined field_0x70e0;
	undefined field_0x70e1;
	undefined field_0x70e2;
	undefined field_0x70e3;
	undefined field_0x70e4;
	undefined field_0x70e5;
	undefined field_0x70e6;
	undefined field_0x70e7;
	undefined field_0x70e8;
	undefined field_0x70e9;
	undefined field_0x70ea;
	undefined field_0x70eb;
	undefined field_0x70ec;
	undefined field_0x70ed;
	undefined field_0x70ee;
	undefined field_0x70ef;
	undefined field_0x70f0;
	undefined field_0x70f1;
	undefined field_0x70f2;
	undefined field_0x70f3;
	undefined field_0x70f4;
	undefined field_0x70f5;
	undefined field_0x70f6;
	undefined field_0x70f7;
	undefined field_0x70f8;
	undefined field_0x70f9;
	undefined field_0x70fa;
	undefined field_0x70fb;
	undefined field_0x70fc;
	undefined field_0x70fd;
	undefined field_0x70fe;
	undefined field_0x70ff;
	undefined field_0x7100;
	undefined field_0x7101;
	undefined field_0x7102;
	undefined field_0x7103;
	undefined field_0x7104;
	undefined field_0x7105;
	undefined field_0x7106;
	undefined field_0x7107;
	undefined field_0x7108;
	undefined field_0x7109;
	undefined field_0x710a;
	undefined field_0x710b;
	undefined field_0x710c;
	undefined field_0x710d;
	undefined field_0x710e;
	undefined field_0x710f;
	undefined field_0x7110;
	undefined field_0x7111;
	undefined field_0x7112;
	undefined field_0x7113;
	undefined field_0x7114;
	undefined field_0x7115;
	undefined field_0x7116;
	undefined field_0x7117;
	undefined field_0x7118;
	undefined field_0x7119;
	undefined field_0x711a;
	undefined field_0x711b;
	undefined field_0x711c;
	undefined field_0x711d;
	undefined field_0x711e;
	undefined field_0x711f;
	undefined field_0x7120;
	undefined field_0x7121;
	undefined field_0x7122;
	undefined field_0x7123;
	undefined field_0x7124;
	undefined field_0x7125;
	undefined field_0x7126;
	undefined field_0x7127;
	undefined field_0x7128;
	undefined field_0x7129;
	undefined field_0x712a;
	undefined field_0x712b;
	undefined field_0x712c;
	undefined field_0x712d;
	undefined field_0x712e;
	undefined field_0x712f;
	undefined field_0x7130;
	undefined field_0x7131;
	undefined field_0x7132;
	undefined field_0x7133;
	undefined field_0x7134;
	undefined field_0x7135;
	undefined field_0x7136;
	undefined field_0x7137;
	undefined field_0x7138;
	undefined field_0x7139;
	undefined field_0x713a;
	undefined field_0x713b;
	undefined field_0x713c;
	undefined field_0x713d;
	undefined field_0x713e;
	undefined field_0x713f;
	undefined field_0x7140;
	undefined field_0x7141;
	undefined field_0x7142;
	undefined field_0x7143;
	undefined field_0x7144;
	undefined field_0x7145;
	undefined field_0x7146;
	undefined field_0x7147;
	undefined field_0x7148;
	undefined field_0x7149;
	undefined field_0x714a;
	undefined field_0x714b;
	undefined field_0x714c;
	undefined field_0x714d;
	undefined field_0x714e;
	undefined field_0x714f;
	undefined field_0x7150;
	undefined field_0x7151;
	undefined field_0x7152;
	undefined field_0x7153;
	undefined field_0x7154;
	undefined field_0x7155;
	undefined field_0x7156;
	undefined field_0x7157;
	undefined field_0x7158;
	undefined field_0x7159;
	undefined field_0x715a;
	undefined field_0x715b;
	undefined field_0x715c;
	undefined field_0x715d;
	undefined field_0x715e;
	undefined field_0x715f;
	undefined field_0x7160;
	undefined field_0x7161;
	undefined field_0x7162;
	undefined field_0x7163;
	undefined field_0x7164;
	undefined field_0x7165;
	undefined field_0x7166;
	undefined field_0x7167;
	undefined field_0x7168;
	undefined field_0x7169;
	undefined field_0x716a;
	undefined field_0x716b;
	undefined field_0x716c;
	undefined field_0x716d;
	undefined field_0x716e;
	undefined field_0x716f;
	undefined field_0x7170;
	undefined field_0x7171;
	undefined field_0x7172;
	undefined field_0x7173;
	undefined field_0x7174;
	undefined field_0x7175;
	undefined field_0x7176;
	undefined field_0x7177;
	undefined field_0x7178;
	undefined field_0x7179;
	undefined field_0x717a;
	undefined field_0x717b;
	undefined field_0x717c;
	undefined field_0x717d;
	undefined field_0x717e;
	undefined field_0x717f;
	undefined field_0x7180;
	undefined field_0x7181;
	undefined field_0x7182;
	undefined field_0x7183;
	undefined field_0x7184;
	undefined field_0x7185;
	undefined field_0x7186;
	undefined field_0x7187;
	undefined field_0x7188;
	undefined field_0x7189;
	undefined field_0x718a;
	undefined field_0x718b;
	undefined field_0x718c;
	undefined field_0x718d;
	undefined field_0x718e;
	undefined field_0x718f;
	undefined field_0x7190;
	undefined field_0x7191;
	undefined field_0x7192;
	undefined field_0x7193;
	undefined field_0x7194;
	undefined field_0x7195;
	undefined field_0x7196;
	undefined field_0x7197;
	undefined4 field_7198;
	struct SurfaceMapStruct38 table38_719c[10];
	struct Container * resData_73cc;
	undefined4 field_73d0;
};

struct CameraData { // May be camera data (which is related to- but not the same as viewports)
	enum CameraType camType;
	struct LiveObject * object_4;
	float float_8;
	float float_c;
	float float_10;
	undefined4 field_14;
	struct Vector3F vector_18;
	struct Container * resData1; // only resData created for FP type (null attachment)
	struct Container * resData2; // attached to resRoot
	struct Container * resData3; // attached to resRoot
	struct Container * resData4; // attached to resData2
	struct Container * resTableunk_34; // attached to resData4 (topdown type only)
	undefined field_0x38;
	undefined field_0x39;
	undefined field_0x3a;
	undefined field_0x3b;
	undefined field_0x3c;
	undefined field_0x3d;
	undefined field_0x3e;
	undefined field_0x3f;
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
	float tilt;
	struct Range2F TiltRange;
	float yaw;
	struct Range2F YawRange;
	float dist;
	struct Range2F DistRange;
	float speedAccel_9c;
	struct Vector3F vector_a0;
	struct Vector3F vector_ac;
	enum CameraFlags flags;
};

struct ImageBMP {
	struct IDirectDrawSurface4 * surface; // IDirectDrawSurface4
	uint width;
	uint height;
	uint penZero; // Palette entry 0
	uint pen255; // Palette entry 255
	uint penZeroRGB; // Palette entry 0 (as unpacked RGB)
	uint flags; // 2 is font?
	struct ImageBMP * nextFree;
};

struct FlockSubdata {
	struct Vector3F vector_0;
	struct Vector3F vector_c;
	struct Vector3F vector_18;
	float float_24;
	float float_28;
	float float_2c;
	float float_30;
	undefined4 field_34;
	float GoalUpdate1;
	float Turn1;
	float Speed1;
	float Tightness1;
	float GoalUpdate2;
	float Turn2;
	float Speed2;
	float Tightness2;
	float matrix[16];
	struct Container * resData_98;
	struct FlockSubdata * subdataNext_9c;
};

struct PolyMeshData {
	undefined4 field_0;
	struct Container * resDataUnassigned_4;
	char * partName; // name of LoadObject file.lwo
	uint index;
	int int_10;
	struct PolyMeshData * previous;
};

struct TextWindow { // Probably a text rendering area (official: TextWindow)
	struct ImageFont * font;
	struct Rect2F windowSize;
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

typedef struct FileStream FileStream, *PFileStream;

typedef enum FileSystemType { // Location of a lego File stream (WAD or REAL)
	FILESYSTEM_ERR=2,
	FILESYSTEM_STD=1,
	FILESYSTEM_WAD=0
} FileSystemType;

typedef union FileStreamData FileStreamData, *PFileStreamData;

typedef struct _iobuf _iobuf, *P_iobuf;

typedef struct _iobuf FILE;

typedef struct FileWADStream FileWADStream, *PFileWADStream;

union FileStreamData {
	FILE * std; // Standard file stream
	struct FileWADStream * wad; // WAD file stream
};

struct FileStream {
	enum FileSystemType location;
	union FileStreamData stream;
};

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

struct FileWADStream {
	int hFile; // Handle to file in the wad
	int streamPos; // Position in stream of the file.  Indexes are from 0-length-1 inclusive.
	BOOL eof; // Has the file hit EOF.
};

typedef struct WADStream WADStream, *PWADStream;

struct WADStream {
	void * data; // Pointer to the file data
	BOOL active; // Is this handle active already
	int wadFile; // Wad file this handle uses
	int indexOfFileInWad; // Index of the file in the wad structure
};

typedef struct LoaderProfileItem LoaderProfileItem, *PLoaderProfileItem;

struct LoaderProfileItem {
	char * name;
	undefined4 field_4;
	undefined4 field_8;
};

typedef struct HelpWindowInfoLevels HelpWindowInfoLevels, *PHelpWindowInfoLevels;

struct HelpWindowInfoLevels {
	char * levels[16];
};

typedef struct SubMenu SubMenu, *PSubMenu;

typedef struct SubMenuItem SubMenuItem, *PSubMenuItem;

typedef struct SubMenuOverlay SubMenuOverlay, *PSubMenuOverlay;

typedef enum MenuItemType {
	MENUITEM_CYCLE=0,
	MENUITEM_NEXT=5,
	MENUITEM_REALSLIDER=4,
	MENUITEM_SLIDER=3,
	MENUITEM_TEXTINPUT=2,
	MENUITEM_TRIGGER=1,
	MENUITEM__COUNT=6,
	MENUITEM__INVALID=4294967295
} MenuItemType;

typedef enum SFXType { // SFXType is different from actual Sample indexes, these are hardcoded values that can easily be looked up by ID
	SFX_AMBIENT=6,
	SFX_AMBIENTLOOP=7,
	SFX_AMBIENTMUSICLOOP=44,
	SFX_BOULDERHIT=34,
	SFX_BUILD=18,
	SFX_BUTTONPRESSED=13,
	SFX_CAPTAINSLIDE=42,
	SFX_CRYSTALRECHARGE=26,
	SFX_DRILL=2,
	SFX_DRILLFADE=3,
	SFX_DRIP=5,
	SFX_DYNAMITE=43,
	SFX_FALLIN=40,
	SFX_FLOOR=33,
	SFX_IMMOVABLEROCK=31,
	SFX_INTERFACESLIDEOFFSCREEN=22,
	SFX_INTERFACESLIDEONSCREEN=21,
	SFX_LASER=27,
	SFX_LASERHIT=28,
	SFX_LAVA=38,
	SFX_LAZERRECHARGE=29,
	SFX_MFDEPOSIT=12,
	SFX_MFLIFT=14,
	SFX_MFTHROW=15,
	SFX_MUSICLOOP=41,
	SFX_NOTOKAY=20,
	SFX_NULL=0,
	SFX_OKAY=19,
	SFX_PANELSLIDEOFFSCREEN=24,
	SFX_PANELSLIDEONSCREEN=23,
	SFX_PLACE=35,
	SFX_PLACECRYSTAL=37,
	SFX_PLACEORE=36,
	SFX_ROCKBREAK=4,
	SFX_ROCKMONSTER=9,
	SFX_ROCKMONSTER2=10,
	SFX_ROCKMONSTERSTEP=11,
	SFX_ROCKWIPE=39,
	SFX_SIREN=25,
	SFX_STAMP=1,
	SFX_STEP=8,
	SFX_TOPPRIORITY=30,
	SFX_WALKER=16,
	SFX_WALL=32,
	SFX_YESSIR=17,
	SFX__INVALID=4294967295
} SFXType;

struct SubMenuItem {
	char * banner;
	uint length;
	struct ImageFont * HiFont;
	struct ImageFont * LoFont;
	void * itemData;
	enum MenuItemType itemType;
	struct Point2I point1;
	undefined4 field_20;
	undefined4 field_24;
	undefined field_0x28;
	undefined field_0x29;
	undefined field_0x2a;
	undefined field_0x2b;
	undefined field_0x2c;
	undefined field_0x2d;
	undefined field_0x2e;
	undefined field_0x2f;
	undefined field_0x30;
	undefined field_0x31;
	undefined field_0x32;
	undefined field_0x33;
	undefined field_0x34;
	undefined field_0x35;
	undefined field_0x36;
	undefined field_0x37;
	undefined4 field_38;
};

struct SubMenuOverlay {
	char * filename;
	int overlayType; // (bmp, avi, lws, flh?)
	undefined4 field_8;
	struct Point2I position;
	enum SFXType sfxType;
	struct SubMenuOverlay * previous;
	undefined4 field_1c;
};

struct SubMenu {
	void * ptr_0;
	void * ptr_4;
	uint length_8; // (init: strlen(param_1))
	struct ImageFont * MenuFont; // (init: param_3)
	struct ImageBMP * MenuImage;
	struct ImageBMP * MenuImageDark;
	struct SubMenuItem * Items;
	int ItemCount;
	int int_20; // (init: 15)
	undefined4 field_24;
	undefined4 field_28;
	struct Point2I Position;
	uint uint_34;
	undefined field_0x38;
	undefined field_0x39;
	undefined field_0x3a;
	undefined field_0x3b;
	undefined field_0x3c;
	undefined field_0x3d;
	undefined field_0x3e;
	undefined field_0x3f;
	struct SubMenuOverlay * Overlays;
	BOOL AutoCenter;
	BOOL DisplayTitle;
	BOOL isAnchored;
	struct Point2I AnchoredPosition;
	int flags_58; // (0x2 = CanScroll)
	char CfgName[64];
	enum BOOL3 PlayRandom;
};

typedef struct D3DStateItem D3DStateItem, *PD3DStateItem;

struct D3DStateItem { // The item's render state type is determined by the index in its table
	DWORD value;
	BOOL isUsed;
};

typedef struct DriverMode DriverMode, *PDriverMode;

typedef enum DriverModeFlags {
	DRIVERMODE_NONE=0,
	DRIVERMODE_PRIMARY=16,
	DRIVERMODE_VALID=1,
	DRIVERMODE_WINDOWOK=32
} DriverModeFlags;

struct DriverMode {
	GUID guid;
	char desc[256]; // "name (description)"
	enum DriverModeFlags flags;
};

typedef struct MenuCollection MenuCollection, *PMenuCollection;

struct MenuCollection {
	struct SubMenu * * menus;
	uint count;
};

typedef struct PTLProperty PTLProperty, *PPTLProperty;

struct PTLProperty { // Property loaded from a level's PTL config file (contains lookup index for actions)
	enum MessageType eventIndex;
	enum MessageType actionIndex;
};

typedef struct InterfaceMenuItem InterfaceMenuItem, *PInterfaceMenuItem;

struct InterfaceMenuItem {
	int * parameters;
	uint numParams;
};

typedef struct MiscObjectDependencies MiscObjectDependencies, *PMiscObjectDependencies;

struct MiscObjectDependencies {
	undefined4 field_0;
	uint levels_flags[16];
	undefined4 levels_field_44[16];
	undefined4 levels_field_84[16];
};

typedef struct GameFunctions GameFunctions, *PGameFunctions;

struct GameFunctions {
	BOOL (* Initialise)(void);
	BOOL (* MainLoop)(float);
	void (* Shutdown)(void);
};

typedef struct WADFile WADFile, *PWADFile;

typedef struct WADEntry WADEntry, *PWADEntry;

typedef enum WADEntryFlags {
	WAD_FILE_IS_IN_WAD=4,
	WAD_FILE_NONE=0,
	WAD_FILE_RNCOMPRESSED=2,
	WAD_FILE_UNCOMPRESSED=1
} WADEntryFlags;

struct WADEntry { // WAD file entry metadata contained within LegoWADFile structure
	enum WADEntryFlags compression; // usually 1, 2 for RNC compression
	int fileLength; // Compressed packed size
	int decompressedLength; // Original unpacked size (same as packedSize when uncompressed)
	int addr; // absolute file offset
};

struct WADFile { // LegoRR WAD File information
	char * fName; // (unused)
	BOOL active; // 1 if WAD is in-use
	HANDLE hFile;
	HANDLE hFileMapping;
	FILE * fWad; // File handle of the wad
	char * * fileNames; // Names of actual files
	char * * wadNames; // Names within wad
	struct WADEntry * wadEntries;
	int numFiles; // number of file entries
};

typedef struct Draw_Rect Draw_Rect, *PDraw_Rect;

struct Draw_Rect {
	struct Rect2F rect;
	float r;
	float g;
	float b;
};

typedef struct DeviceMode DeviceMode, *PDeviceMode;

typedef enum DeviceModeFlags {
	DEVICEMODE_COLOUR=4096,
	DEVICEMODE_DEPTH16=32,
	DEVICEMODE_DEPTH24=64,
	DEVICEMODE_DEPTH32=128,
	DEVICEMODE_DEPTH8=16,
	DEVICEMODE_HARDWARE=8192,
	DEVICEMODE_ISUSED=1,
	DEVICEMODE_NONE=0,
	DEVICEMODE_SYSTEMTEXTURE=32768,
	DEVICEMODE_VIDEOTEXTURE=16384,
	DEVICEMODE_ZBUFF16=512,
	DEVICEMODE_ZBUFF24=1024,
	DEVICEMODE_ZBUFF32=2048,
	DEVICEMODE_ZBUFF8=256
} DeviceModeFlags;

struct DeviceMode {
	GUID guid;
	char desc[256]; // "name (description)"
	enum DeviceModeFlags flags;
};

typedef struct ScreenMode ScreenMode, *PScreenMode;

typedef enum ScreenModeFlags {
	SCREENMODE_ISUSED=1,
	SCREENMODE_NONE=0
} ScreenModeFlags;

struct ScreenMode {
	uint width;
	uint height;
	uint bitDepth;
	char desc[256]; // "WxH (BPP bit)", "WxH" (windowed)
	enum ScreenModeFlags flags;
};

typedef struct Container_TextureRef Container_TextureRef, *PContainer_TextureRef;

struct Container_TextureRef {
	char * filename;
	struct IDirect3DRMTexture3 * texture;
};

typedef struct LTRBRect2F LTRBRect2F, *PLTRBRect2F;

struct LTRBRect2F {
	float left;
	float top;
	float right;
	float bottom;
};

typedef struct LTRBRect2I LTRBRect2I, *PLTRBRect2I;

struct LTRBRect2I {
	int left;
	int top;
	int right;
	int bottom;
};

typedef struct ToolTipData ToolTipData, *PToolTipData;

struct ToolTipData {
	float float_0;
	char tooltipText[512];
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
	undefined4 field_25c;
	undefined4 field_260;
	undefined4 field_264;
	undefined4 field_268;
	undefined4 field_26c;
	struct ImageBMP * tooltipImage;
	undefined4 field_274;
	uint flags;
};

typedef struct ColourRGBAI ColourRGBAI, *PColourRGBAI;

struct ColourRGBAI {
	uint red;
	uint green;
	uint blue;
	uint alpha;
};

typedef struct ColourRGBPacked ColourRGBPacked, *PColourRGBPacked;

struct ColourRGBPacked {
	byte red;
	byte green;
	byte blue;
};

typedef struct ImageFlic ImageFlic, *PImageFlic;

typedef enum FlicUserFlags {
	FLICCATCHUPON=4,
	FLICDISK=0,
	FLICLOOPINGON=2,
	FLICMEMORY=1,
	FLICSOUNDOFF=8
} FlicUserFlags;

typedef struct FLICHEADERSTRUCT FLICHEADERSTRUCT, *PFLICHEADERSTRUCT;

typedef enum FlicDisplayMode {
	FLICMODE_BYTEPERPIXEL=0,
	FLICMODE_HICOLOR=4,
	FLICMODE_MODEX=1,
	FLICMODE_PLANAR=2,
	FLICMODE_TRUECOLOR=3
} FlicDisplayMode;

struct FLICHEADERSTRUCT {
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

struct ImageFlic { // (official: FLICSTRUCT)
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
	struct FileStream * filehandle;
	void * fsSPtr;
	void * fsSource;
	enum FlicDisplayMode fsDisplayMode;
	int fsBitPlanes;
	int fsLoadBufferSize;
	void * fsLoadBuffer;
	BOOL is15bit; // true if green mask == 0x3e0
};

typedef struct ErodeState ErodeState, *PErodeState;

struct ErodeState {
	undefined4 field_0;
	undefined4 field_4;
};

typedef struct LightEffectsManager LightEffectsManager, *PLightEffectsManager;

typedef enum LightEffectsFlags { // Flags for LightEffectsManager global variable @004ebec8
	LIGHTEFFECTS_DIMIN_DONE=1024,
	LIGHTEFFECTS_DIMOUT=512,
	LIGHTEFFECTS_DIMOUT_DONE=4096,
	LIGHTEFFECTS_DISABLED=256,
	LIGHTEFFECTS_FADE_FORWARD=16,
	LIGHTEFFECTS_FADE_REVERSE=32,
	LIGHTEFFECTS_FADING=8,
	LIGHTEFFECTS_HASBLINK=1,
	LIGHTEFFECTS_HASFADE=4,
	LIGHTEFFECTS_HASMOVE=64,
	LIGHTEFFECTS_MOVING=128,
	LIGHTEFFECTS_NONE=0
} LightEffectsFlags;

struct LightEffectsManager { // LightEffects module globals @004ebdd8
	struct Container * resSpotlight; // [Res+Move] init
	struct Container * resRootLight; // [Move] init
	struct ColourRGBF initialRGB; // [Color] init
	struct ColourRGBF currentRGB; // [Color+Blink+Fade] init+update
	struct ColourRGBF BlinkRGBMax; // [Blink] init
	float blinkTime; // [Blink] update
	struct Range2F RandomRangeForTimeBetweenBlinks; // [Blink] init
	float blinkChange; // [Blink] update
	float MaxChangeAllowed; // [Blink] init
	struct ColourRGBF fadeDestRGB; // [Fade] update
	struct ColourRGBF FadeRGBMin; // [Fade] init
	struct ColourRGBF FadeRGBMax; // [Fade] init
	float fadeTime; // [Fade] update
	struct Range2F RandomRangeForTimeBetweenFades; // [Fade] init
	struct ColourRGBF fadeSpeedRGB; // [Fade] update
	struct Range2F RandomRangeForFadeTimeFade; // [Fade] init
	float fadeHoldTime; // [Fade] update
	struct Range2F RandomRangeForHoldTimeOfFade; // [Fade] init
	struct ColourRGBF fadePosRGB; // [Fade] update
	struct Vector3F resPosition; // [Move] init+update
	struct Vector3F MoveLimit; // [Move] init
	float moveTime; // [Move] update
	struct Range2F RandomRangeForTimeBetweenMoves; // [Move] init
	float moveSpeed; // [Move] update
	struct Range2F RandomRangeForSpeedOfMove; // [Move] init
	struct Vector3F vectorMove; // [Move] update
	float moveDist; // [Move] update
	struct Range2F RandomRangeForDistOfMove; // [Move] init
	undefined1 reserved1[12]; // possibly an unused Vector3F/ColourRGBF
	enum LightEffectsFlags flags; // [all] init+update
};

typedef struct ColourRGBI ColourRGBI, *PColourRGBI;

struct ColourRGBI {
	uint red;
	uint green;
	uint blue;
};

typedef struct Rect2I Rect2I, *PRect2I;

struct Rect2I {
	int x;
	int y;
	int width;
	int height;
};

typedef struct AdvisorPositionData AdvisorPositionData, *PAdvisorPositionData;

typedef enum AdvisorAnimType {
	ADVISORANIM_POINTTOMAP=0,
	ADVISORANIM_POINT_E=3,
	ADVISORANIM_POINT_N=1,
	ADVISORANIM_POINT_NE=2,
	ADVISORANIM_POINT_NW=8,
	ADVISORANIM_POINT_S=5,
	ADVISORANIM_POINT_SE=4,
	ADVISORANIM_POINT_SW=6,
	ADVISORANIM_POINT_UP=9,
	ADVISORANIM_POINT_W=7,
	ADVISORANIM_TALK_TOP=10,
	ADVISORANIM__COUNT=11,
	ADVISORANIM__INVALID=4294967295
} AdvisorAnimType;

typedef enum TextType {
	TEXT_AIRSUPPLYLOW=20,
	TEXT_AIRSUPPLYRUNNINGOUT=21,
	TEXT_BUILDHELP=10,
	TEXT_CANNOTPLACEBUILDING=15,
	TEXT_CANTDRILL=3,
	TEXT_CANTDRIVE=13,
	TEXT_CANTREINFORCE=6,
	TEXT_CAVERNDISCOVERED=18,
	TEXT_CRYSTALFOUND=17,
	TEXT_CRYSTALOREDISABLED=16,
	TEXT_DRILL=1,
	TEXT_DRIVE=12,
	TEXT_ENCYCLOPEDIA=8,
	TEXT_GAMECOMPLETE=23,
	TEXT_MAKETELEPORTER=14,
	TEXT_MANTRAINED=24,
	TEXT_NODRILL=2,
	TEXT_NOREINFORCE=5,
	TEXT_OREFOUND=19,
	TEXT_PICKUPCRYSTAL=7,
	TEXT_RADARHELP=9,
	TEXT_REINFORCE=4,
	TEXT_SELECTIONHELP=11,
	TEXT_SPACETOCONTINUE=22,
	TEXT_UNITUPGRADED=25,
	TEXT_WALK=0,
	TEXT__COUNT=26,
	TEXT__INVALID=4294967295
} TextType;

typedef enum PanelType {
	PANEL_CAMERACONTROL=9,
	PANEL_CRYSTALSIDEBAR=5,
	PANEL_ENCYCLOPEDIA=11,
	PANEL_INFODOCK=10,
	PANEL_INFORMATION=7,
	PANEL_MESSAGES=3,
	PANEL_MESSAGESIDE=4,
	PANEL_PRIORITYLIST=8,
	PANEL_RADAR=0,
	PANEL_RADARFILL=1,
	PANEL_RADAROVERLAY=2,
	PANEL_TOPPANEL=6,
	PANEL__COUNT=12,
	PANEL__INVALID=4294967295
} PanelType;

typedef enum AdvisorPositionFlags {
	ADVISORPOS_DEFAULT=131072,
	ADVISORPOS_HASTEXT=262144,
	ADVISORPOS_NONE=0,
	ADVISORPOS_NOPANEL=65536
} AdvisorPositionFlags;

struct AdvisorPositionData {
	enum AdvisorAnimType animType;
	enum TextType textType;
	int sfxIndex;
	enum PanelType panelType;
	struct Point2F point1;
	struct Point2F point2; // Identical to point1
	enum AdvisorPositionFlags flags; // (init: 0x20000), 0x10000 = NULL panel, 0x40000 = non-NULL text
};

typedef struct Mem_Handle Mem_Handle, *PMem_Handle;

typedef enum MemHandleFlags { // Flags for SharedBuffer struct
	MEMORY_HANDLE_FLAG_NONE=0,
	MEMORY_HANDLE_FLAG_USED=1
} MemHandleFlags;

struct Mem_Handle {
	void * addr;
	enum MemHandleFlags flags; // 1 = isUsed
};

typedef struct ColourRGBAPacked ColourRGBAPacked, *PColourRGBAPacked;

struct ColourRGBAPacked {
	byte red;
	byte green;
	byte blue;
	byte alpha;
};

typedef struct P1P2Rect2I P1P2Rect2I, *PP1P2Rect2I;

struct P1P2Rect2I {
	int x1;
	int y1;
	int x2;
	int y2;
};

typedef struct P1P2Rect2F P1P2Rect2F, *PP1P2Rect2F;

struct P1P2Rect2F {
	float x1;
	float y1;
	float x2;
	float y2;
};

typedef int WADStreamHandle;

typedef struct MsvcDOSErrnoInfo MsvcDOSErrnoInfo, *PMsvcDOSErrnoInfo;

typedef int errno_t;

struct MsvcDOSErrnoInfo {
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

struct BITMAP_FILE_INFO_STRUCT { // Helper struct to combine both BITMAPFILEHEADER, BITMAPINFOHEADER, and palette data into one field
	BITMAPFILEHEADER hdr;
	BITMAPINFOHEADER bmi;
	RGBQUAD bmiColors[1];
};

typedef struct FLIC_HEADER FLIC_HEADER, *PFLIC_HEADER;

struct FLIC_HEADER {
	DWORD size; // Size of FLIC including this header
	WORD type; // File type [0x1234, 0x9119, 0xaf11, 0xaf12, 0xaf43]
	WORD frames; // Number of frames in first segment
	WORD width; // FLIC width in pixels
	WORD height; // FLIC height in pixels
	WORD depth; // Bits per pixel (usually 8)
	WORD flags; // Set to zero or to three
	DWORD speed; // Delay between frames
	WORD reserved1; // Set to zero
	DWORD created; // Date of FLIC creation (FLC only)
	DWORD creator; // Serial number or compiler id (FLC only)
	DWORD updated; // Date of FLIC update (FLC only)
	DWORD updater; // Serial number (FLC only), see creator
	WORD aspect_dx; // Width of square rectangle (FLC only)
	WORD aspect_dy; // Height of square rectangle (FLC only)
	WORD ext_flags; // EGI: flags for specific EGI extensions
	WORD keyframes; // EGI: key-image frequency
	WORD totalframes; // EGI: total number of frames (segments)
	DWORD req_memory; // EGI: maximum chunk size (uncompressed)
	WORD max_regions; // EGI: max. number of regions in a CHK_REGION chunk
	WORD transp_num; // EGI: number of transparent levels
	BYTE reserved2[24]; // Set to zero
	DWORD oframe1; // Offset to frame 1 (FLC only)
	DWORD oframe2; // Offset to frame 2 (FLC only)
	BYTE reserved3[40]; // Set to zero
};

typedef struct Sound3D_SoundData Sound3D_SoundData, *PSound3D_SoundData;

typedef struct tWAVEFORMATEX tWAVEFORMATEX, *PtWAVEFORMATEX;

typedef struct tWAVEFORMATEX WAVEFORMATEX;

typedef struct IDirectSoundBuffer IDirectSoundBuffer, *PIDirectSoundBuffer;

typedef enum SampleFlags {
	SAMPLE_ISUSED=1,
	SAMPLE_MULTIPLE=4,
	SAMPLE_NONE=0,
	SAMPLE_STREAMED=8,
	SAMPLE_VOLUME=2
} SampleFlags;

typedef struct IDirectSoundBufferVtbl IDirectSoundBufferVtbl, *PIDirectSoundBufferVtbl;

struct Sound3D_SoundData { // (official: Sound3D_SoundData)
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
	enum SampleFlags flags;
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

struct IDirectSoundBuffer {
	struct IDirectSoundBufferVtbl * lpVtbl;
};

struct IDirectSoundBufferVtbl {
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

typedef struct SampleProperty SampleProperty, *PSampleProperty;

struct SampleProperty {
	int sampleIndex;
	struct SampleProperty * next;
};

typedef struct NERPMessageSound NERPMessageSound, *PNERPMessageSound;

struct NERPMessageSound {
	char * key;
	int sampleIndex;
};

typedef struct Sound3D_WaveData Sound3D_WaveData, *PSound3D_WaveData;

typedef struct HMMIO__ HMMIO__, *PHMMIO__;

typedef struct HMMIO__ * HMMIO;

typedef struct _MMCKINFO _MMCKINFO, *P_MMCKINFO;

typedef struct _MMCKINFO MMCKINFO;

typedef DWORD FOURCC;

struct _MMCKINFO {
	FOURCC ckid;
	DWORD cksize;
	FOURCC fccType;
	DWORD dwDataOffset;
	DWORD dwFlags;
};

struct Sound3D_WaveData {
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

struct HMMIO__ {
	int unused;
};

typedef struct Sound3D_StreamData Sound3D_StreamData, *PSound3D_StreamData;

struct Sound3D_StreamData {
	BOOL fileOpen; // paused/playing/used?
	struct Sound3D_WaveData wiWave;
	BOOL playing; // paused/playing/used?
};

typedef struct Image_Globs Image_Globs, *PImage_Globs;

struct Image_Globs {
	struct ImageBMP * listSet[32]; // Images list
	struct ImageBMP * freeList;
	uint listCount; // number of lists.
	uint flags;
};

typedef struct Font_Globs Font_Globs, *PFont_Globs;

struct Font_Globs {
	struct ImageFont * listSet[32]; // Fonts list
	struct ImageFont * freeList;
	uint listCount; // number of lists.
	uint flags;
};

typedef struct File_Globs File_Globs, *PFile_Globs;

struct File_Globs {
	char wadBasePath[1024];
	char s_GetWadName_wadedName[1024];
	char s_VerifyFilename_full[260];
	FILE * s_ErrorFile_f; // (address not known)
	char dataDir[260];
	void (* loadCallback)(char *, uint, void *);
	void * loadCallbackData;
	char cdLetter;
	undefined1 padding1[3];
	BOOL basePathSet;
	BOOL fileLogFileAccess; // (address not known)
};

typedef struct Draw_Globs Draw_Globs, *PDraw_Globs;

typedef struct tagRECT RECT;

struct Draw_Globs {
	void (* drawPixelFunc)(int, int, uint);
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
	uint flags;
};

typedef struct Config_Globs Config_Globs, *PConfig_Globs;

struct Config_Globs {
	char s_JoinPath_string[1024]; // (not part of Manager, static array in JoinPath func)
	struct CFGProperty * listSet[32];
	struct CFGProperty * freeList;
	uint listCount;
	uint flags;
};

typedef struct Mesh_Globs Mesh_Globs, *PMesh_Globs;

typedef struct Mesh_PostRenderInfo Mesh_PostRenderInfo, *PMesh_PostRenderInfo;

typedef struct Mesh_TextureReference Mesh_TextureReference, *PMesh_TextureReference;

typedef struct IDirect3DMaterial3 IDirect3DMaterial3, *PIDirect3DMaterial3;

typedef struct IDirect3DMaterial3Vtbl IDirect3DMaterial3Vtbl, *PIDirect3DMaterial3Vtbl;

struct IDirect3DMaterial3 {
	struct IDirect3DMaterial3Vtbl * lpVtbl;
};

struct Mesh_TextureReference {
	struct IDirectDrawSurface4 * surface;
	char * path;
	BOOL trans;
};

struct Mesh_Globs {
	struct Mesh * postRenderList;
	struct Mesh_PostRenderInfo * postRenderMeshList;
	struct D3DStateItem stateData[50];
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

struct Mesh_PostRenderInfo {
	struct Mesh * mesh;
	struct Matrix4F matWorld;
	struct Mesh_PostRenderInfo * next;
};

struct IDirect3DMaterial3Vtbl {
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

typedef struct IDirectDraw4Vtbl IDirectDraw4Vtbl, *PIDirectDraw4Vtbl;

typedef struct IDirectDrawClipperVtbl IDirectDrawClipperVtbl, *PIDirectDrawClipperVtbl;

struct IDirectDrawClipperVtbl {
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

struct DirectDraw_Globs {
	HWND hWnd;
	struct IDirectDraw4 * lpDirectDraw;
	struct IDirectDrawSurface4 * fSurf; // "RenderTarget" surface
	struct IDirectDrawSurface4 * bSurf; // "DrawTarget" surface
	struct IDirectDrawSurface4 * zSurf; // (unused)
	struct IDirectDrawClipper * lpFrontClipper; // "RenderTarget" clipper
	struct IDirectDrawClipper * lpBackClipper; // "DrawTarget" clipper
	struct DriverMode * driverList;
	struct DriverMode * selectedDriver; // (unused)
	struct DeviceMode * deviceList;
	struct DeviceMode * selectedDevice; // (unused)
	struct ScreenMode * modeList; // "ScreenModes"
	uint driverCount;
	uint deviceCount;
	uint modeCount; // "ScreenModes"
	BOOL fullScreen;
	uint width;
	uint height;
};

struct IDirectDraw4 {
	struct IDirectDraw4Vtbl * lpVtbl;
};

struct IDirectDraw4Vtbl {
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

struct HWND__ {
	int unused;
};

struct IDirectDrawClipper {
	struct IDirectDrawClipperVtbl * lpVtbl;
};

typedef struct Container_Globs Container_Globs, *PContainer_Globs;

typedef enum ResourceManagerFlags { // All flags used by the ResourceManager struct.
	RESMANAGER_ISINIT=1,
	RESMANAGER_NONE=0,
	RESMANAGER_SOUNDCALLBACK=64
} ResourceManagerFlags;

struct Container_Globs {
	struct Container * listSet[20];
	struct Container * freeList;
	struct Container * rootContainer;
	char * typeName[9];
	char * extensionName[9];
	char * gameName;
	struct IDirect3DRMVisual * visualArray[4];
	struct Container_TextureRef textureSet[1000];
	uint textureCount;
	void (* soundTriggerCallback)(char *, struct Container *, void *);
	void * soundTriggerData;
	void (* triggerFrameCallback)(struct Container *, void *);
	void * triggerFrameData;
	char * sharedDir;
	uint fogColour;
	uint listCount;
	enum ResourceManagerFlags flags;
};

typedef struct Viewport_Globs Viewport_Globs, *PViewport_Globs;

struct Viewport_Globs {
	struct Viewport * listSet[32];
	struct Viewport * freeList;
	uint listCount;
	uint flags;
};

typedef struct FileCheck_Globs FileCheck_Globs, *PFileCheck_Globs;

struct FileCheck_Globs { // Loose static variables for File_CheckRedundantFiles in Files.c
	char loadedList[2000][1024]; // MAYBE USE LINKED LIST
	uint numInList;
};

typedef struct Lws_Globs Lws_Globs, *PLws_Globs;

typedef struct Lws_MeshPath Lws_MeshPath, *PLws_MeshPath;

struct Lws_MeshPath {
	char * path;
	struct Mesh * mesh;
};

struct Lws_Globs {
	struct Lws_MeshPath meshPathList[1000]; // For full path to files...
	struct Lws_MeshPath meshPathListShared[1000]; // For shared files...
	char * sharedDir;
	uint meshPathCount;
	uint meshPathCountShared;
	float staticDissolveLevel[100];
	uint staticDissolveCount;
	BOOL (* FindSFXIDFunc)(char *, uint *);
	BOOL (* SoundEnabledFunc)(void);
	int (* PlaySample3DFunc)(struct IDirect3DRMFrame3 *, uint, BOOL, BOOL, struct Vector3F *);
};

typedef struct Sound_Globs Sound_Globs, *PSound_Globs;

typedef DWORD MCIERROR;

struct Sound_Globs {
	uint useSound; // Number of sounds in soundList
	BOOL initialised;
	uint soundList[100];
	int currTrack;
	BOOL loopCDTrack;
	void (* CDStopCallback)(void);
	BOOL updateCDTrack;
	uint s_Update_lastUpdate;
	ulonglong reserved1;
	MCIERROR mciErr;
};

typedef struct Animation_Globs Animation_Globs, *PAnimation_Globs;

struct Animation_Globs {
	bool g98NoAvis;
	byte padding1[3];
	struct IDirectDraw4 * ddraw;
};

typedef struct Wad_Globs Wad_Globs, *PWad_Globs;

struct Wad_Globs {
	DWORD computerNameLength; // (address not known)
	BOOL wadLogFileAccess; // (address not known)
	FILE * s_ErrorFile_f; // (address not known)
	struct WADFile wads[10]; // Wad structures
	int references[10]; // Current count of references to the wad file
	char computerName[16]; // (address not known)
	struct WADStream fileHandles[100];
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

struct DIPROPHEADER {
	DWORD dwSize;
	DWORD dwHeaderSize;
	DWORD dwObj;
	DWORD dwHow;
};

struct IDirectInputDeviceA {
	struct IDirectInputDeviceAVtbl * lpVtbl;
};

struct DIDEVCAPS {
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

struct IDirectInputA {
	struct IDirectInputAVtbl * lpVtbl;
};

struct IDirectInputAVtbl {
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* CreateDevice)(struct IDirectInputA *, LPGUID, struct IDirectInputDeviceA * *, struct IUnknown *);
	HRESULT (* EnumDevices)(struct IDirectInputA *, DWORD, BOOL (* )(struct DIDEVICEINSTANCEA *, LPVOID), LPVOID, DWORD);
	HRESULT (* GetDeviceStatus)(struct IDirectInputA *, LPGUID);
	HRESULT (* RunControlPanel)(struct IDirectInputA *, HWND, DWORD);
	HRESULT (* Initialize)(struct IDirectInputA *, HINSTANCE, DWORD);
};

struct DIcallbackData {
	struct IDirectInputA * di;
	HWND hWnd;
	void * joystick; // struct joystickType
};

struct DIMOUSESTATE {
	uint lX;
	uint lY;
	uint lZ;
	bool rgbButtons[4];
};

struct Input_Globs {
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

struct IDirectInputDeviceAVtbl {
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

struct DIOBJECTDATAFORMAT {
	LPGUID pguid;
	DWORD dwOfs;
	DWORD dwType;
	DWORD dwFlags;
};

struct DIDEVICEOBJECTDATA {
	DWORD dwOfs;
	DWORD dwData;
	DWORD dwTimeStamp;
	DWORD dwSequence;
	UINT_PTR uAppData;
};

struct DIDEVICEOBJECTINSTANCEA {
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

struct DIDATAFORMAT {
	DWORD dwSize;
	DWORD dwObjSize;
	DWORD dwFlags;
	DWORD dwDataSize;
	DWORD dwNumObjs;
	struct DIOBJECTDATAFORMAT * rgodf;
};

struct DIDEVICEINSTANCEA {
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

typedef struct IDirectSound3DListener IDirectSound3DListener, *PIDirectSound3DListener;

typedef struct Sound3D_SoundRecord Sound3D_SoundRecord, *PSound3D_SoundRecord;

typedef struct IDirectSoundVtbl IDirectSoundVtbl, *PIDirectSoundVtbl;

typedef struct IDirectSound3DListenerVtbl IDirectSound3DListenerVtbl, *PIDirectSound3DListenerVtbl;

typedef struct IDirectSound3DBuffer IDirectSound3DBuffer, *PIDirectSound3DBuffer;

typedef struct IDirectSound3DBufferVtbl IDirectSound3DBufferVtbl, *PIDirectSound3DBufferVtbl;

struct IDirectSound {
	struct IDirectSoundVtbl * lpVtbl;
};

struct Sound3D_SoundRecord {
	struct IDirect3DRMFrame3 * frame;
	struct IDirectSoundBuffer * soundBuff;
	struct IDirectSound3DBuffer * sound3DBuff;
	struct Sound3D_SoundRecord * next;
};

struct IDirectSound3DListenerVtbl {
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

struct IDirectSoundVtbl {
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

struct IDirectSound3DListener {
	struct IDirectSound3DListenerVtbl * lpVtbl;
};

struct IDirectSound3DBufferVtbl {
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

struct Sound3D_Globs {
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

struct IDirectSound3DBuffer {
	struct IDirectSound3DBufferVtbl * lpVtbl;
};

typedef struct Main_Globs Main_Globs, *PMain_Globs;

typedef uint UINT;

typedef UINT_PTR WPARAM;

typedef long LONG_PTR;

typedef LONG_PTR LPARAM;

typedef struct IDirect3DRM3 IDirect3DRM3, *PIDirect3DRM3;

typedef struct IDirect3DDevice3 IDirect3DDevice3, *PIDirect3DDevice3;

typedef enum CmdlineFlags { // Command line argument flags set when starting the game
	CMD_BEST=64,
	CMD_CLEANSAVES=1024,
	CMD_D3DRMUPDATED=1,
	CMD_DEBUG=8192,
	CMD_DEBUGCOMPLETE=32768,
	CMD_DUALMOUSE=16384,
	CMD_FPSLOCK30=128,
	CMD_FTM=262144,
	CMD_FULLSCREEN=2,
	CMD_FVF=524288,
	CMD_MIPMAP=8,
	CMD_NM=32,
	CMD_NOFPSLOCK=16,
	CMD_NONE=0,
	CMD_REDUCEANIMATION=4194304,
	CMD_REDUCEFLICS=16777216,
	CMD_REDUCEIMAGES=33554432,
	CMD_REDUCEPROMESHES=8388608,
	CMD_REDUCESAMPLES=1048576,
	CMD_SHOWVERSION=2097152,
	CMD_STARTLEVEL=512,
	CMD_TESTERCALL=65536,
	CMD_TESTLEVELS=131072,
	CMD_TEXTUREVIDEOMEMORY=4,
	CMD_WINDOW=256
} CmdlineFlags;

typedef enum ProgrammerMode { // Programmer mode enum
	PROGRAMMER_MODE_1=1,
	PROGRAMMER_MODE_10=10,
	PROGRAMMER_MODE_11=11,
	PROGRAMMER_MODE_2=2,
	PROGRAMMER_MODE_3=3,
	PROGRAMMER_OFF=0
} ProgrammerMode;

typedef enum FeatureFlags { // Flags specified by the "-flags #" command line argument (which has to be in decimal...)
	FEATURE_BLOCKFADEIN=32768,
	FEATURE_NONE=0
} FeatureFlags;

typedef struct HACCEL__ HACCEL__, *PHACCEL__;

typedef struct HACCEL__ * HACCEL;

typedef struct IDirect3DRM3Vtbl IDirect3DRM3Vtbl, *PIDirect3DRM3Vtbl;

typedef struct IDirect3DRMMeshBuilder3 IDirect3DRMMeshBuilder3, *PIDirect3DRMMeshBuilder3;

typedef struct IDirect3DRMAnimationSet2 IDirect3DRMAnimationSet2, *PIDirect3DRMAnimationSet2;

typedef struct IDirect3DDevice3Vtbl IDirect3DDevice3Vtbl, *PIDirect3DDevice3Vtbl;

typedef struct IDirect3DRMMeshBuilder3Vtbl IDirect3DRMMeshBuilder3Vtbl, *PIDirect3DRMMeshBuilder3Vtbl;

typedef struct IDirect3DRMAnimationSet2Vtbl IDirect3DRMAnimationSet2Vtbl, *PIDirect3DRMAnimationSet2Vtbl;

struct HACCEL__ {
	int unused;
};

struct IDirect3DRM3Vtbl {
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
	pointer CreateMaterial;
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

struct IDirect3DRM3 {
	struct IDirect3DRM3Vtbl * lpVtbl;
};

struct IDirect3DDevice3 {
	struct IDirect3DDevice3Vtbl * lpVtbl;
};

struct IDirect3DRMMeshBuilder3 {
	struct IDirect3DRMMeshBuilder3Vtbl * lpVtbl;
};

struct IDirect3DRMAnimationSet2Vtbl {
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

struct IDirect3DDevice3Vtbl {
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

struct IDirect3DRMMeshBuilder3Vtbl {
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

struct IDirect3DRMAnimationSet2 {
	struct IDirect3DRMAnimationSet2Vtbl * lpVtbl;
};

struct Main_Globs {
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
	struct GameFunctions currState;
	BOOL stateSet;
	float fixedFrameTiming;
	struct D3DStateItem renderStateData[200];
	uint style;
	enum CmdlineFlags flags;
	enum ProgrammerMode programmerLevel;
	char startLevel[128];
	char languageName[128];
	enum FeatureFlags clFlags;
	HACCEL accels;
	void (* windowCallback)(HWND, UINT, WPARAM, LPARAM);
};

typedef struct Init_Globs Init_Globs, *PInit_Globs;

struct Init_Globs {
	uint driverCount;
	uint deviceCount;
	uint modeCount;
	struct DriverMode drivers[20];
	struct DeviceMode devices[20];
	struct ScreenMode modes[200];
	struct DriverMode * selDriver;
	struct DeviceMode * selDevice;
	struct ScreenMode * selMode;
	BOOL selFullScreen;
	BOOL wasFullScreen; // Previous fullscreen state when Windowed button is disabled due to lack of support
	struct ScreenMode validModes[200];
	uint validModeCount;
};

typedef struct Error_Globs Error_Globs, *PError_Globs;

struct Error_Globs {
	struct FileStream * dumpFile;
	struct FileStream * loadLogFile;
	struct FileStream * loadErrorLogFile;
	struct FileStream * redundantLogFile;
	char loadLogName[1024];
	char redundantLogName[1024];
	BOOL warnCalled;
	BOOL fullScreen;
};

typedef struct Key_Globs Key_Globs, *PKey_Globs;

struct Key_Globs {
	char * keyName[256];
};

typedef struct Mem_Globs Mem_Globs, *PMem_Globs;

struct Mem_Globs {
	struct Mem_Handle handleList[2000];
	uint flags; // (unused)
};

typedef struct Dxbug_Globs Dxbug_Globs, *PDxbug_Globs;

struct Dxbug_Globs { // DirectX (dxbug.c) debugging loose static variables
	HRESULT errnum;
	int line;
	int DXModuleNameNumber;
	int DXNumErrorsSet;
	char * file;
	uint reserved1;
	char DXErrorString[2048]; // Last error that was set (actually [1024], but the space is unused)
};

typedef enum TrainedFlags {
	TRAINED_DRIVER=4,
	TRAINED_DYNAMITE=8,
	TRAINED_NONE=0,
	TRAINED_PILOT=1,
	TRAINED_REPAIR=16,
	TRAINED_SAILOR=2,
	TRAINED_SCANNER=32
} TrainedFlags;

typedef enum AudioFlags {
	AUDIO_SOUNDON=1,
	AUDIO_UNK_2=2,
	AUDIO_UNK_8=8
} AudioFlags;

typedef enum TutorialFlags {
	TUTORIAL_NONE=0,
	TUTORIAL_UNK_10=16,
	TUTORIAL_UNK_100=256,
	TUTORIAL_UNK_1000=4096,
	TUTORIAL_UNK_2=2,
	TUTORIAL_UNK_20=32,
	TUTORIAL_UNK_200=512,
	TUTORIAL_UNK_4=4,
	TUTORIAL_UNK_40=64,
	TUTORIAL_UNK_400=1024,
	TUTORIAL_UNK_8=8,
	TUTORIAL_UNK_80=128
} TutorialFlags;

typedef enum ObjectiveFlags {
	OBJECTIVE_BLOCK=1024,
	OBJECTIVE_COMPLETE=2,
	OBJECTIVE_CONSTRUCTION=4096,
	OBJECTIVE_CRYSTAL=256,
	OBJECTIVE_FAILED=4,
	OBJECTIVE_HITTIMEFAIL=64,
	OBJECTIVE_NONE=0,
	OBJECTIVE_ORE=512,
	OBJECTIVE_SHOWACHEIVEADVISOR=32,
	OBJECTIVE_SHOWADVISOR=16,
	OBJECTIVE_SHOWFAILEDADVISOR=128,
	OBJECTIVE_TIMER=2048,
	OBJECTIVE_UNK_1=1,
	OBJECTIVE_UNK_8=8
} ObjectiveFlags;

typedef enum LiveManagerFlags { // ReservedPool LiveObject INITFLAGS
	LIVEMANAGER_ISUSED=1,
	LIVEMANAGER_NONE=0,
	LIVEMANAGER_UNK_20=32
} LiveManagerFlags;

typedef enum RewardItemFlags {
	REWARDITEM_BOXIMAGES=64,
	REWARDITEM_IMAGES=2,
	REWARDITEM_NONE=0,
	REWARDITEM_TEXT_1=1,
	REWARDITEM_TEXT_10=16,
	REWARDITEM_TEXT_20=32,
	REWARDITEM_UNK_4=4
} RewardItemFlags;

typedef enum ObjInfoFlags {
	OBJINFO_BUBBLEIMAGES=16,
	OBJINFO_HEALTHBAR=2,
	OBJINFO_HEALTHBAR_VERTICAL=8,
	OBJINFO_HUNGERIMAGES=1,
	OBJINFO_NONE=0
} ObjInfoFlags;

typedef enum InfoMessageFlags {
	INFOMSG_AUTOGAMESPEED=16,
	INFOMSG_NONE=0,
	INFOMSG_UNK_1=1,
	INFOMSG_UNK_2=2,
	INFOMSG_UNK_4=4,
	INFOMSG_UNK_8=8
} InfoMessageFlags;

typedef enum AdvisorStateFlags {
	ADVISORSTATE_NONE=0,
	ADVISORSTATE_UNK_1=1,
	ADVISORSTATE_UNK_2=2
} AdvisorStateFlags;

typedef struct LWSURFACE LWSURFACE, *PLWSURFACE;

typedef struct LWRGB LWRGB, *PLWRGB;

typedef enum LWTEXFLAGS {
	TFM_ANTIALIASING=64,
	TFM_AXIS_X=1,
	TFM_AXIS_Y=2,
	TFM_AXIS_Z=4,
	TFM_NEGATIVE_IMAGE=16,
	TFM_PIXEL_BLENDING=32,
	TFM_SEQUENCE=128,
	TFM_WORLD_COORD=8
} LWTEXFLAGS;

typedef enum LWSRFFLAGS {
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

typedef enum LWTEXMAPTYPE {
	MT_CYLINDRICAL=1,
	MT_MAX=3,
	MT_PLANAR=0,
	MT_SPHERICAL=2
} LWTEXMAPTYPE;

typedef struct TEXDATA TEXDATA, *PTEXDATA;

struct TEXDATA { // (an alias for Vector3F)
	float tdX;
	float tdY;
	float tdZ;
};

struct LWRGB { // (an alias for ColourRGBAPacked)
	byte colRed;
	byte colGreen;
	byte colBlue;
	byte colAlpha;
};

struct LWSURFACE {
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

typedef struct Lws_KeyInfo Lws_KeyInfo, *PLws_KeyInfo;

struct Lws_KeyInfo {
	struct Vector3F position;
	struct Vector3F hpb;
	struct Vector3F scale;
	ushort frame;
	ushort padding1;
};

typedef struct Lws_Node Lws_Node, *PLws_Node;

struct Lws_Node {
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

typedef struct LWSURFLIST LWSURFLIST, *PLWSURFLIST;

struct LWSURFLIST {
	uint srflCount;
	char * * srflName;
};

typedef struct LWSIZE LWSIZE, *PLWSIZE;

struct LWSIZE {
	uint lwVertCount;
	uint lwPolyCount;
	uint lwSurfaceCount;
};

typedef struct LWPOLY LWPOLY, *PLWPOLY;

struct LWPOLY {
	uint plyCount;
	uint plySurface;
	ushort * plyData;
};

typedef struct APPOBJ APPOBJ, *PAPPOBJ;

struct APPOBJ { // LightWave lwt APPOBJ
	char * aoPath;
	struct LWSIZE aoSize;
	float * aoVerts;
	struct LWPOLY * aoPoly;
	struct LWSURFACE * aoSurface;
	struct FileStream * aoFileUV;
};

typedef struct Lws_SoundTrigger Lws_SoundTrigger, *PLws_SoundTrigger;

struct Lws_SoundTrigger {
	uint sfxID;
	ushort frameStartList[25];
	ushort frameEndList[25];
	uint loopUID[25];
	ushort count;
	ushort padding1;
};

typedef struct Lws_Info Lws_Info, *PLws_Info;

struct Lws_Info {
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

typedef struct VideoPlayer VideoPlayer, *PVideoPlayer;

typedef struct VideoPlayer VideoPlayer_t;

typedef struct IAMMultiMediaStream IAMMultiMediaStream, *PIAMMultiMediaStream;

typedef struct IMediaStream IMediaStream, *PIMediaStream;

typedef struct IDirectDrawMediaStream IDirectDrawMediaStream, *PIDirectDrawMediaStream;

typedef struct IDirectDrawSurface3 IDirectDrawSurface3, *PIDirectDrawSurface3;

typedef struct IDirectDrawStreamSample IDirectDrawStreamSample, *PIDirectDrawStreamSample;

typedef struct IDirectDraw2 IDirectDraw2, *PIDirectDraw2;

typedef struct IAMMultiMediaStreamVtbl IAMMultiMediaStreamVtbl, *PIAMMultiMediaStreamVtbl;

typedef enum MMStreamType {
	STREAMTYPE_READ=0,
	STREAMTYPE_TRANSFORM=2,
	STREAMTYPE_WRITE=1
} MMStreamType;

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

typedef struct IDirectDrawMediaStreamVtbl IDirectDrawMediaStreamVtbl, *PIDirectDrawMediaStreamVtbl;

typedef struct IDirectDrawSurface3Vtbl IDirectDrawSurface3Vtbl, *PIDirectDrawSurface3Vtbl;

typedef struct IDirectDrawStreamSampleVtbl IDirectDrawStreamSampleVtbl, *PIDirectDrawStreamSampleVtbl;

typedef struct IDirectDraw2Vtbl IDirectDraw2Vtbl, *PIDirectDraw2Vtbl;

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

struct IMediaStream {
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

struct IDirectDrawStreamSample {
	struct IDirectDrawStreamSampleVtbl * lpVtbl;
};

struct IDirectDraw2Vtbl {
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

struct IGraphBuilderVtbl {
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

struct IMediaStreamFilter {
	struct IMediaStreamFilterVtbl * lpVtbl;
};

struct IAMMultiMediaStream {
	struct IAMMultiMediaStreamVtbl * lpVtbl;
};

struct IMediaStreamFilterVtbl { // Subclass of IDirect3DRMArrayVtbl
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

struct IDirectDrawMediaStreamVtbl {
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

struct IDirectDraw2 {
	struct IDirectDraw2Vtbl * lpVtbl;
};

struct IMediaStreamVtbl {
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

struct IAMMultiMediaStreamVtbl {
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

struct IDirectDrawStreamSampleVtbl {
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

struct IDirectDrawSurface3 {
	struct IDirectDrawSurface3Vtbl * lpVtbl;
};

struct IDirectDrawSurface3Vtbl {
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

struct IDirectDrawMediaStream {
	struct IDirectDrawMediaStreamVtbl * lpVtbl;
};

struct VideoPlayer {
	struct IAMMultiMediaStream * amMediaStream;
	HRESULT errorCode;
	struct IMediaStream * mediaStream;
	struct IDirectDrawMediaStream * ddMediaStream;
	struct IDirectDrawSurface * ddSampleSurface;
	struct IDirectDrawSurface3 * ddDrawSurface;
	struct IDirectDrawStreamSample * ddStreamSample;
	struct IDirectDrawSurface3 * ddRenderSurface;
	RECT rect;
	char * filename;
	struct IDirectDraw2 * ddraw2;
};

struct IGraphBuilder {
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

typedef struct AVIPlayerVtbl AVIPlayerVtbl, *PAVIPlayerVtbl;

typedef struct AVIPlayer AVIPlayer, *PAVIPlayer;

typedef struct IAVIStream IAVIStream, *PIAVIStream;

typedef struct IGetFrame IGetFrame, *PIGetFrame;

typedef struct AVISTREAMINFOA AVISTREAMINFOA, *PAVISTREAMINFOA;

typedef struct AVIRenderer AVIRenderer, *PAVIRenderer;

typedef struct IAVIStreamVtbl IAVIStreamVtbl, *PIAVIStreamVtbl;

typedef struct IGetFrameVtbl IGetFrameVtbl, *PIGetFrameVtbl;

typedef struct HDC__ HDC__, *PHDC__;

typedef struct HDC__ * HDC;

typedef enum AVIStreamInfoFlags { // Flags for dwFlags in AVISTREAMINFO_ struct
	AVIIF_COMPUSE=268369920,
	AVIIF_FIRSTPART=32,
	AVIIF_KEYFRAME=16,
	AVIIF_LASTPART=64,
	AVIIF_LIST=1,
	AVIIF_MIDPART=96,
	AVIIF_NOTIME=256
} AVIStreamInfoFlags;

typedef enum AVIStreamInfoCaps { // Flags for unknown field in AVISTREAMINFO_ struct
	AVISTREAMINFO_DISABLED=1,
	AVISTREAMINFO_FORMATCHANGES=65536
} AVIStreamInfoCaps;

typedef struct AVIRendererVtbl AVIRendererVtbl, *PAVIRendererVtbl;

struct AVIRenderer {
	struct AVIRendererVtbl * vftable;
	uint field_unused_4; // (init: 0)
	bool isLocked; // true if ddSurface4 is locked
	byte reserved1[3];
	int depth; // bit depth
	struct IDirectDrawPalette * ddPalette;
	bool bool_unused_14; // (init: 0 on InitSurfaceDesc)
	bool bool_unused_15; // (init: 0)
	bool isBPP15; // true if 16-bpp with actual bit-count at 15
	bool isOpen; // (init: 0, 1 on InitSurface success)
	struct IDirectDrawSurface4 * ddSurface4; // (init: 0)
	struct DDSURFACEDESC2 surfDesc;
};

struct AVIRendererVtbl {
	AVIRenderer * (* deletor)(struct AVIRenderer *, byte);
	uint (* GetWidth)(struct AVIRenderer *);
	uint (* GetHeight)(struct AVIRenderer *);
};

struct AVIPlayerVtbl {
	AVIPlayer * (* deletor)(struct AVIPlayer *, byte);
};

struct AVISTREAMINFOA {
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

struct IAVIStreamVtbl {
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

struct IGetFrameVtbl {
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

struct IGetFrame {
	struct IGetFrameVtbl * lpVtbl;
};

struct HDC__ {
	int unused;
};

struct AVIPlayer {
	struct AVIPlayerVtbl * vftable;
	struct IAVIStream * aviStream;
	struct IGetFrame * aviFrame;
	struct AVISTREAMINFOA streamInfo;
	bool bool_unused_98; // (init: 0)
	bool isOpen; // (init: 0, 1 on open / has renderer)
	ushort reserved1;
	RECT rect; // (copied from streamInfo.rcFrame)
	float startTime; // (init: timeGetTime() * 0.001)
	float currentTime; // (milliseconds, just like startTime)
	float rate;
	uint position; // (init: 0)
	uint reserved2;
	struct AVIRenderer * renderer;
};

struct IAVIStream {
	struct IAVIStreamVtbl * lpVtbl;
};

typedef struct AVIPlayer AVIPlayer_t;

typedef struct AdvisorAnimData AdvisorAnimData, *PAdvisorAnimData;

struct AdvisorAnimData {
	struct Container * resData;
	float loopStartTime; // ignored when not looping
	float loopEndTime; // ignored when not looping
};

typedef struct InfoMessageData InfoMessageData, *PInfoMessageData;

struct InfoMessageData {
	char * text;
	undefined4 field_4;
	enum SFXType sfxType;
	float float_c;
	uint flags;
};

typedef struct SelectedUnitHotkey SelectedUnitHotkey, *PSelectedUnitHotkey;

struct SelectedUnitHotkey {
	int field_0;
	int field_4;
	BOOL bool_8;
	int field_c;
	int field_10;
};

typedef struct ToolData ToolData, *PToolData;

struct ToolData {
	enum AITaskType taskType;
	undefined4 field_4;
	undefined4 field_c;
	int count;
};

typedef struct LevelIdentifier LevelIdentifier, *PLevelIdentifier;

struct LevelIdentifier {
	int field_0;
	char * * field_4;
	undefined4 field_8;
	void * * field_c;
	undefined4 field_10;
};

typedef struct PairStruct_428 PairStruct_428, *PPairStruct_428;

typedef struct Struct_428 Struct_428, *PStruct_428;

typedef struct ItemStruct_428 ItemStruct_428, *PItemStruct_428;

struct ItemStruct_428 {
	uint index;
	enum Direction direction;
	undefined4 field_8;
	undefined4 field_c;
	undefined4 field_10;
	undefined4 field_14;
};

struct PairStruct_428 {
	struct Struct_428 * first;
	struct Struct_428 * second;
};

struct Struct_428 {
	struct Point2F points[100];
	uint pointsCount;
	struct ItemStruct_428 items[10];
	uint itemsCount;
	undefined4 field_418;
	undefined4 field_41c;
	undefined4 field_420;
	undefined4 field_424;
};

typedef struct Struct_8__00558bc4 Struct_8__00558bc4, *PStruct_8__00558bc4;

struct Struct_8__00558bc4 {
	struct LiveObject * object_0;
	float float_4;
};

typedef struct RewardFrontEnd RewardFrontEnd, *PRewardFrontEnd;

typedef struct RewardFrontEndItem RewardFrontEndItem, *PRewardFrontEndItem;

struct RewardFrontEndItem {
	enum RewardItemFlags flags;
	char name[32];
	float Importance;
	int Quota;
	undefined field_0x2c;
	undefined field_0x2d;
	undefined field_0x2e;
	undefined field_0x2f;
	undefined field_0x30;
	undefined field_0x31;
	undefined field_0x32;
	undefined field_0x33;
	undefined field_0x34;
	undefined field_0x35;
	undefined field_0x36;
	undefined field_0x37;
	undefined field_0x38;
	undefined field_0x39;
	undefined field_0x3a;
	undefined field_0x3b;
	undefined field_0x3c;
	undefined field_0x3d;
	undefined field_0x3e;
	undefined field_0x3f;
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
	char Text[256]; // (TODO: size me)
	struct Point2I TextPosition;
	struct Point2I ImagePosition;
	struct Point2I BoxImagePosition;
	char FlicName[128]; // (TODO: size me)
	struct Size2I FlicSize;
	struct Point2I FlicPosition;
	undefined field_0x1fc;
	undefined field_0x1fd;
	undefined field_0x1fe;
	undefined field_0x1ff;
	struct ImageBMP * Image;
	struct ImageFont * Font;
	char * SoundName;
	struct ImageBMP * BoxImage;
};

struct RewardFrontEnd {
	BOOL Enabled;
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
	undefined field_0x18;
	undefined field_0x19;
	undefined field_0x1a;
	undefined field_0x1b;
	undefined field_0x1c;
	undefined field_0x1d;
	undefined field_0x1e;
	undefined field_0x1f;
	undefined field_0x20;
	undefined field_0x21;
	undefined field_0x22;
	undefined field_0x23;
	undefined field_0x24;
	undefined field_0x25;
	undefined field_0x26;
	undefined field_0x27;
	undefined field_0x28;
	undefined field_0x29;
	undefined field_0x2a;
	undefined field_0x2b;
	undefined field_0x2c;
	undefined field_0x2d;
	undefined field_0x2e;
	undefined field_0x2f;
	undefined field_0x30;
	undefined field_0x31;
	undefined field_0x32;
	undefined field_0x33;
	undefined field_0x34;
	undefined field_0x35;
	undefined field_0x36;
	undefined field_0x37;
	undefined field_0x38;
	undefined field_0x39;
	undefined field_0x3a;
	undefined field_0x3b;
	undefined field_0x3c;
	undefined field_0x3d;
	undefined field_0x3e;
	undefined field_0x3f;
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
	int Modifier;
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
	int items_COUNT; // (init: 10)
	struct RewardFrontEndItem * items_PTR; // (init: &items_TABLE)
	struct RewardFrontEndItem items_TABLE[10];
};

typedef struct Container_AppData Container_AppData, *PContainer_AppData;

typedef struct AnimClone AnimClone, *PAnimClone;

typedef struct Sound3D_SoundFrameRecord Sound3D_SoundFrameRecord, *PSound3D_SoundFrameRecord;

struct Sound3D_SoundFrameRecord {
	struct IDirectSound3DBuffer * sound3DBuff;
	struct Vector3F pos;
	struct Sound3D_SoundFrameRecord * next;
};

struct Container_AppData {
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

struct AnimClone {
	struct AnimClone * clonedFrom;
	struct Lws_Info * scene; // LWS struct
	struct IDirect3DRMAnimationSet2 * animSet; // (not LWS)
	BOOL lws;
	struct IDirect3DRMFrame3 * root; // (not LWS)
	struct IDirect3DRMFrame3 * * partArray; // (not LWS) table of COM objects, length is count_18
	uint partCount; // (not LWS)
	uint frameCount;
};

typedef struct BlockObject BlockObject, *PBlockObject;

struct BlockObject {
	struct LiveObject * attachedObject;
	struct Point2I position;
	undefined4 field_c;
	struct BlockObject * pool_m_next;
};

typedef struct ItemStruct_34 ItemStruct_34, *PItemStruct_34;

struct ItemStruct_34 {
	struct Mesh * struct34_1;
	struct Mesh * struct34_2;
	struct Container * resData;
	float time;
};

typedef struct MessageAction MessageAction, *PMessageAction;

struct MessageAction {
	enum MessageType event;
	struct LiveObject * object_4;
	BOOL field_8;
	struct Point2I position;
};

typedef struct ProMeshData ProMeshData, *PProMeshData;

struct ProMeshData {
	struct Container * promesh_a;
	struct Container * promesh_b;
	undefined4 table_a[100];
	undefined4 table_b[100];
	float BlockSize;
	undefined4 field_32c;
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
	struct SurfaceTextureGrid * surfTextGrid;
};

typedef struct InfoMessageInstance InfoMessageInstance, *PInfoMessageInstance;

typedef enum InfoType {
	INFO_AIRDEPLETING=16,
	INFO_AIRLOW=17,
	INFO_AIROUT=18,
	INFO_AIRRESTORED=19,
	INFO_BUILDINGDEATH=12,
	INFO_CANTRAINMINIFIGURE=35,
	INFO_CANUPGRADEMINIFIGURE=34,
	INFO_CAVEIN=7,
	INFO_CAVERNLOCATED=9,
	INFO_CONSTRUCTED=8,
	INFO_CRYSTALFOUND=0,
	INFO_CRYSTALPOWER=29,
	INFO_CRYSTALSEAMFOUND=36,
	INFO_DYNAMITEPLACED=13,
	INFO_FOUNDMINIFIGURE=33,
	INFO_GENERICDEATH=38,
	INFO_GENERICMONSTER=39,
	INFO_GENERICSEAMFOUND=37,
	INFO_ICEROCKMONSTER=4,
	INFO_LANDSLIDE=6,
	INFO_LAVAERODE=30,
	INFO_LAVAROCKMONSTER=3,
	INFO_LEGOMANDEATH=10,
	INFO_NOPOWER=14,
	INFO_ORECOLLECTED=26,
	INFO_ORESEAMFOUND=1,
	INFO_PATHCOMPLETED=32,
	INFO_POWERDRAIN=15,
	INFO_ROCKMONSTER=2,
	INFO_SLUGEMERGE=31,
	INFO_TRAINDRIVER=20,
	INFO_TRAINDYNAMITE=21,
	INFO_TRAINPILOT=23,
	INFO_TRAINREPAIR=22,
	INFO_TRAINSAILOR=24,
	INFO_TRAINSCANNER=25,
	INFO_UNDERATTACK=5,
	INFO_VEHICLEDEATH=11,
	INFO_WALLDUG=27,
	INFO_WALLREINFORCED=28,
	INFO__INVALID=4294967295
} InfoType;

struct InfoMessageInstance {
	enum InfoType infoType;
	undefined field_0x4;
	undefined field_0x5;
	undefined field_0x6;
	undefined field_0x7;
	undefined field_0x8;
	undefined field_0x9;
	undefined field_0xa;
	undefined field_0xb;
	float float_c;
	undefined field_0x10;
	undefined field_0x11;
	undefined field_0x12;
	undefined field_0x13;
};

typedef struct Container_SearchData Container_SearchData, *PContainer_SearchData;

typedef enum ContainerSearchMode {
	CONTAINER_SEARCHMODE_FIRSTMATCH=0,
	CONTAINER_SEARCHMODE_MATCHCOUNT=1,
	CONTAINER_SEARCHMODE_NTHMATCH=2
} ContainerSearchMode;

struct Container_SearchData {
	char * string;
	uint stringLen;
	BOOL caseSensitive;
	struct IDirect3DRMFrame3 * resultFrame;
	uint count;
	enum ContainerSearchMode mode;
	uint matchNumber;
};

typedef struct MapFileInfo MapFileInfo, *PMapFileInfo;

struct MapFileInfo {
	char Signature[4]; // "MAP "
	uint fileSize;
	struct Size2I dimensions;
	ushort blocks[1];
};

typedef struct PanelData PanelData, *PPanelData;

struct PanelData {
	struct ImageBMP * imageOrFlic;
	BOOL isFlic;
	struct Point2F xyOut;
	struct Point2F xyIn;
	struct Point2F xyOutIn;
	undefined4 field_20;
	undefined4 field_24;
	undefined4 field_28;
	uint flags;
};

typedef struct Struct_2b0 Struct_2b0, *PStruct_2b0;

struct Struct_2b0 { // Seen in a table of [10]
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
	undefined field_0x18;
	undefined field_0x19;
	undefined field_0x1a;
	undefined field_0x1b;
	undefined field_0x1c;
	undefined field_0x1d;
	undefined field_0x1e;
	undefined field_0x1f;
	undefined field_0x20;
	undefined field_0x21;
	undefined field_0x22;
	undefined field_0x23;
	undefined field_0x24;
	undefined field_0x25;
	undefined field_0x26;
	undefined field_0x27;
	undefined field_0x28;
	undefined field_0x29;
	undefined field_0x2a;
	undefined field_0x2b;
	undefined field_0x2c;
	undefined field_0x2d;
	undefined field_0x2e;
	undefined field_0x2f;
	undefined field_0x30;
	undefined field_0x31;
	undefined field_0x32;
	undefined field_0x33;
	undefined field_0x34;
	undefined field_0x35;
	undefined field_0x36;
	undefined field_0x37;
	undefined field_0x38;
	undefined field_0x39;
	undefined field_0x3a;
	undefined field_0x3b;
	undefined field_0x3c;
	undefined field_0x3d;
	undefined field_0x3e;
	undefined field_0x3f;
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
	float float_264;
	struct Vector3F vector_268;
	struct Vector3F vector_274;
	struct Vector3F position_280;
	float float_28c;
	struct Vector3F vector_290;
	undefined field_0x29c;
	undefined field_0x29d;
	undefined field_0x29e;
	undefined field_0x29f;
	undefined field_0x2a0;
	undefined field_0x2a1;
	undefined field_0x2a2;
	undefined field_0x2a3;
	struct LiveObject * object_2a4;
	int weaponType;
	undefined4 field_2ac;
};

typedef struct MiscObjectData MiscObjectData, *PMiscObjectData;

struct MiscObjectData {
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
	undefined field_0x18;
	undefined field_0x19;
	undefined field_0x1a;
	undefined field_0x1b;
	undefined field_0x1c;
	undefined field_0x1d;
	undefined field_0x1e;
	undefined field_0x1f;
	undefined field_0x20;
	undefined field_0x21;
	undefined field_0x22;
	undefined field_0x23;
	undefined field_0x24;
	undefined field_0x25;
	undefined field_0x26;
	undefined field_0x27;
	undefined field_0x28;
	undefined field_0x29;
	undefined field_0x2a;
	undefined field_0x2b;
	undefined field_0x2c;
	undefined field_0x2d;
	undefined field_0x2e;
	undefined field_0x2f;
	struct Container * resData; // LWS,true | LWO,true
	undefined field_0x34;
	undefined field_0x35;
	undefined field_0x36;
	undefined field_0x37;
};

typedef struct ImageStruct_10 ImageStruct_10, *PImageStruct_10;

struct ImageStruct_10 {
	char * name;
	struct ImageBMP * image;
	struct ImageFont * font;
	struct ImageStruct_10 * next;
};

typedef struct LiveObjectInfo LiveObjectInfo, *PLiveObjectInfo;

struct LiveObjectInfo {
	struct LiveObject * liveObj;
	BOOL intbool_4;
	struct Point2F point_8;
	struct Vector3F vector_10;
};

typedef struct WeaponStats WeaponStats, *PWeaponStats;

struct WeaponStats {
	float ObjectRatios[20][15][16]; // (inits: -1.0f)
	BOOL isSlowDeath; // (init: false)
	float SlowDeath_initial; // Initial damage percent
	float SlowDeath_duration;
	float RechargeTime; // (init: 0.0f)
	float DefaultDamage; // (init: 0.0f)
	float DischargeRate;
	int Ammo;
	float WeaponRange; // (init: 150.0f)
	float WallDestroyTimes[18]; // (defaults: 5.0f)
};

typedef struct Container_TextureData Container_TextureData, *PContainer_TextureData;

struct Container_TextureData {
	char * xFileName;
	uint flags;
};

typedef struct Sound3DInstance Sound3DInstance, *PSound3DInstance;

struct Sound3DInstance {
	int sampleIndex;
	struct IDirect3DRMFrame3 * frame;
	struct Vector3F position;
	uint flags;
};

typedef struct RewardSubstruct_20 RewardSubstruct_20, *PRewardSubstruct_20;

struct RewardSubstruct_20 {
	int int_0;
	undefined4 field_4;
	float vertSpacing;
	undefined4 field_c;
	undefined4 field_10;
	char * text;
	struct ImageFont * font;
	uint flags;
};

typedef struct RewardStruct_28 RewardStruct_28, *PRewardStruct_28;

struct RewardStruct_28 {
	undefined4 field_0;
	undefined4 field_4;
	float float_8;
	float float_c;
	float float_10;
	float scrollSpeed;
	float float_18;
	int substruct_COUNT;
	struct RewardSubstruct_20 * * substruct_TABLE;
	uint flags;
};

typedef struct BasicObjectData BasicObjectData, *PBasicObjectData;

struct BasicObjectData {
	int objIndex;
	struct Container * aeResData; // ACT, true
};

typedef struct Struct_b8__00558080 Struct_b8__00558080, *PStruct_b8__00558080;

struct Struct_b8__00558080 {
	undefined4 field_0x0;
	undefined4 field_0x4;
	undefined4 field_0x8;
	undefined4 field_0xc;
	undefined4 field_0x10;
	undefined4 field_0x14;
	undefined4 field_0x18;
	undefined4 field_0x1c;
	undefined4 field_0x20;
	undefined4 field_0x24;
	undefined4 field_0x28;
	undefined4 field_0x2c;
	undefined4 field_0x30;
	undefined4 field_0x34;
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

typedef struct StructF_10 StructF_10, *PStructF_10;

struct StructF_10 {
	float float_0;
	float float_4;
	undefined4 field_8;
	float float_c;
};

typedef enum CLGenResources {
	CLGEN_MAIN_ICON=1,
	CLGEN_MAIN_ICONGROUP=103,
	CLGEN_SELECTOR_DIALOG=101
} CLGenResources;

typedef enum KeysByte {
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
} KeysByte;

typedef enum LegoRRResources {
	LEGORR_MAIN_ICON=1,
	LEGORR_MAIN_ICONGROUP=113,
	LEGORR_MODESELECTION_DIALOG=101
} LegoRRResources;

typedef enum MaterialType {
	MATERIAL_ALPHA=4,
	MATERIAL_AMBIENT=1,
	MATERIAL_DIFFUSE=0,
	MATERIAL_EMISSIVE=3,
	MATERIAL_POWER=5,
	MATERIAL_SPECULAR=2
} MaterialType;

typedef enum AdvisorType {
	ADVISOR_ICONPOINT_BACKBUTTON=4,
	ADVISOR_ICONPOINT_NORMAL=3,
	ADVISOR_ICONPOINT_TOPBUTTONS=5,
	ADVISOR_OBJECTIVE=0,
	ADVISOR_OBJECTIVEACHIEVED=1,
	ADVISOR_OBJECTIVEFAILED=2,
	ADVISOR_PANELPOINT_CONTROLZOOMIN=18,
	ADVISOR_PANELPOINT_CONTROLZOOMOUT=19,
	ADVISOR_PANELPOINT_INFODOCKCLOSE=12,
	ADVISOR_PANELPOINT_INFODOCKGOTO=11,
	ADVISOR_PANELPOINT_RADARMAPVIEW=10,
	ADVISOR_PANELPOINT_RADARTOGGLE=6,
	ADVISOR_PANELPOINT_RADARTOGGLEOBJECTVIEW=7,
	ADVISOR_PANELPOINT_RADARZOOMIN=8,
	ADVISOR_PANELPOINT_RADARZOOMOUT=9,
	ADVISOR_PANELPOINT_TOPPANELCALLTOARMS=16,
	ADVISOR_PANELPOINT_TOPPANELGOBACK=17,
	ADVISOR_PANELPOINT_TOPPANELINFO=13,
	ADVISOR_PANELPOINT_TOPPANELOPTIONS=14,
	ADVISOR_PANELPOINT_TOPPANELPRIORITIES=15,
	ADVISOR_TALKINGAME=20,
	ADVISOR__COUNT=21,
	ADVISOR__INVALID=4294967295
} AdvisorType;

typedef enum CLGenDialogControls {
	CLGEN_ID_CANCEL=2,
	CLGEN_ID_OK=1,
	CLGEN_ID_SELECT_DROPDOWNLIST=1001,
	CLGEN_ID_SELECT_LABEL=1006
} CLGenDialogControls;

typedef enum RegistryType { // Supported registry information types
	REGISTRY_DWORD_VALUE=1,
	REGISTRY_STRING_VALUE=0
} RegistryType;

typedef enum PanelButtonRadarType {
	PANELBUTTON_RADAR_MAPVIEW=4,
	PANELBUTTON_RADAR_TAGGEDOBJECTVIEW=1,
	PANELBUTTON_RADAR_TOGGLE=0,
	PANELBUTTON_RADAR_ZOOMIN=2,
	PANELBUTTON_RADAR_ZOOMOUT=3,
	PANELBUTTON_RADAR__COUNT=5,
	PANELBUTTON_RADAR__INVALID=4294967295
} PanelButtonRadarType;

typedef enum PointerType {
	POINTER_BLANK=1,
	POINTER_CANBUILD=22,
	POINTER_CANNOTBUILD=23,
	POINTER_CANTDRILL=4,
	POINTER_CANTDYNAMITE=25,
	POINTER_CANTGO=7,
	POINTER_CANTHELP=15,
	POINTER_CANTPICKUP=27,
	POINTER_CANTREINFORCE=11,
	POINTER_CANTTELEPORT=9,
	POINTER_CANTZOOM=54,
	POINTER_CLEAR=5,
	POINTER_DRILL=3,
	POINTER_DYNAMITE=24,
	POINTER_GETIN=17,
	POINTER_GETOUT=18,
	POINTER_GO=6,
	POINTER_HELP=14,
	POINTER_LEGOMANCANTDIG=29,
	POINTER_LEGOMANCANTGO=37,
	POINTER_LEGOMANCANTPICKUP=33,
	POINTER_LEGOMANCLEAR=41,
	POINTER_LEGOMANDIG=31,
	POINTER_LEGOMANGO=39,
	POINTER_LEGOMANPICKUP=35,
	POINTER_NOTOKAY=21,
	POINTER_OKAY=20,
	POINTER_PICKUP=26,
	POINTER_PICKUPORE=28,
	POINTER_PUTDOWN=16,
	POINTER_RADARPAN=12,
	POINTER_REINFORCE=10,
	POINTER_SELECTED=2,
	POINTER_STANDARD=0,
	POINTER_SURFACETYPE_CRYSTALSEAM=52,
	POINTER_SURFACETYPE_HARD=44,
	POINTER_SURFACETYPE_IMMOVABLE=43,
	POINTER_SURFACETYPE_LAKE=51,
	POINTER_SURFACETYPE_LAVA=48,
	POINTER_SURFACETYPE_LOOSE=46,
	POINTER_SURFACETYPE_MEDIUM=45,
	POINTER_SURFACETYPE_ORESEAM=50,
	POINTER_SURFACETYPE_RECHARGESEAM=53,
	POINTER_SURFACETYPE_SOIL=47,
	POINTER_SURFACETYPE_WATER_unused=49,
	POINTER_TELEPORT=8,
	POINTER_TRACKOBJECT=13,
	POINTER_TUTORIALBLOCKINFO=19,
	POINTER_VEHICLECANTDIG=30,
	POINTER_VEHICLECANTGO=38,
	POINTER_VEHICLECANTPICKUP=34,
	POINTER_VEHICLECLEAR=42,
	POINTER_VEHICLEDIG=32,
	POINTER_VEHICLEGO=40,
	POINTER_VEHICLEPICKUP=36,
	POINTER_ZOOM=55
} PointerType;

typedef enum SurfaceType {
	SURFACE_CAVERN=17,
	SURFACE_CRYSTALSEAM=10,
	SURFACE_HARD=2,
	SURFACE_IMMOVABLE=1,
	SURFACE_LAKE=9,
	SURFACE_LAVA=6,
	SURFACE_LOOSE=4,
	SURFACE_MEDIUM=3,
	SURFACE_ORESEAM=8,
	SURFACE_PATH=14,
	SURFACE_RECHARGESEAM=11,
	SURFACE_REINFORCEMENT=13,
	SURFACE_RUBBLE=12,
	SURFACE_SLUGHOLE=15,
	SURFACE_SOIL=5,
	SURFACE_TUNNEL=0,
	SURFACE_UNDISCOVERED=16,
	SURFACE_WATER_unused=7,
	SURFACE__INVALID=4294967295
} SurfaceType;

typedef enum RewardItemType {
	REWARDTYPE_CAVERNS=4,
	REWARDTYPE_CONSTRUCTIONS=3,
	REWARDTYPE_CRYSTALS=0,
	REWARDTYPE_DIGGABLE=2,
	REWARDTYPE_FIGURES=5,
	REWARDTYPE_ORE=1,
	REWARDTYPE_OXYGEN=7,
	REWARDTYPE_ROCKMONSTERS=6,
	REWARDTYPE_SCORE=9,
	REWARDTYPE_TIMER=8,
	REWARDTYPE__COUNT=10,
	REWARDTYPE__INVALID=4294967295
} RewardItemType;

typedef enum Keys {
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
} Keys;

typedef enum LegoRRDialogControls {
	LEGORR_ID_CANCEL=2,
	LEGORR_ID_DEVICE_LISTBOX=1002,
	LEGORR_ID_DRIVER_LISTBOX=1000,
	LEGORR_ID_FULLSCREEN_RADIOBUTTON=1004,
	LEGORR_ID_OK=1,
	LEGORR_ID_SCREENMODES_LABEL=1006,
	LEGORR_ID_SCREENMODES_LISTBOX=1003,
	LEGORR_ID_WINDOW_RADIOBUTTON=1005
} LegoRRDialogControls;

typedef enum DrawEffect {
	DrawEffect_HalfTrans=2,
	DrawEffect_None=0,
	DrawEffect_XOR=1
} DrawEffect;

typedef enum Sound3DPlayMode {
	SOUND3D_PLAY_NORMAL=2,
	SOUND3D_PLAY_ONFRAME=0,
	SOUND3D_PLAY_ONPOS=1
} Sound3DPlayMode;

typedef enum PanelButtonInformationType {
	PANELBUTTON_INFORMATION_FUNCTION=1,
	PANELBUTTON_INFORMATION_TOGGLE=0,
	PANELBUTTON_INFORMATION__COUNT=2,
	PANELBUTTON_INFORMATION__INVALID=4294967295
} PanelButtonInformationType;

typedef enum PanelButtonTopPanelType {
	PANELBUTTON_TOPPANEL_CALLTOARMS=2,
	PANELBUTTON_TOPPANEL_OPTIONS=0,
	PANELBUTTON_TOPPANEL_PRIORITIES=1,
	PANELBUTTON_TOPPANEL__COUNT=3,
	PANELBUTTON_TOPPANEL__INVALID=4294967295
} PanelButtonTopPanelType;

typedef enum PanelButtonCrystalSideBarType {
	PANELBUTTON_CRYSTALSIDEBAR_CRYSTALS=1,
	PANELBUTTON_CRYSTALSIDEBAR_ORE=0,
	PANELBUTTON_CRYSTALSIDEBAR__COUNT=2,
	PANELBUTTON_CRYSTALSIDEBAR__INVALID=4294967295
} PanelButtonCrystalSideBarType;

typedef enum PolyMode {
	POLY_FP=3,
	POLY_HIGH=2,
	POLY_LOW=0,
	POLY_MEDIUM=1
} PolyMode;

typedef enum FlicError {
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

typedef enum PathType {
	PATH_NONE=0,
	PATH_POWERPATH=2,
	PATH_RUBBLE=1
} PathType;

typedef enum FallinType {
	FALLIN_CAVEIN_HIGH=7,
	FALLIN_CAVEIN_LOW=5,
	FALLIN_CAVEIN_MEDIUM=6,
	FALLIN_CAVEIN_VERYHIGH=8,
	FALLIN_HIGH=3,
	FALLIN_LOW=1,
	FALLIN_MEDIUM=2,
	FALLIN_NONE=0,
	FALLIN_VERYHIGH=4
} FallinType;

typedef enum BubbleType {
	BUBBLE_BUILDPATH=35,
	BUBBLE_CALLTOARMS=30,
	BUBBLE_CANTDO=0,
	BUBBLE_CARRYBARRIER=20,
	BUBBLE_CARRYCRYSTAL=16,
	BUBBLE_CARRYDYNAMITE=19,
	BUBBLE_CARRYELECFENCE=21,
	BUBBLE_CARRYORE=17,
	BUBBLE_CARRYSTUD=18,
	BUBBLE_COLLECTBARRIER=6,
	BUBBLE_COLLECTCRYSTAL=2,
	BUBBLE_COLLECTDRILL=8,
	BUBBLE_COLLECTDYNAMITE=5,
	BUBBLE_COLLECTELECFENCE=7,
	BUBBLE_COLLECTFREEZERBEAM=14,
	BUBBLE_COLLECTHAMMER=10,
	BUBBLE_COLLECTLASERBEAM=12,
	BUBBLE_COLLECTORE=3,
	BUBBLE_COLLECTPUSHERBEAM=13,
	BUBBLE_COLLECTSHOVEL=9,
	BUBBLE_COLLECTSONICBLASTER=15,
	BUBBLE_COLLECTSPANNER=11,
	BUBBLE_COLLECTSTUD=4,
	BUBBLE_DIG=27,
	BUBBLE_DRILL=25,
	BUBBLE_DRIVE=33,
	BUBBLE_DYNAMITE=23,
	BUBBLE_EAT=32,
	BUBBLE_ELECFENCE=31,
	BUBBLE_FLEE=28,
	BUBBLE_GOTO=22,
	BUBBLE_IDLE=1,
	BUBBLE_POWEROFF=29,
	BUBBLE_RECHARGE=37,
	BUBBLE_REINFORCE=24,
	BUBBLE_REPAIR=26,
	BUBBLE_REQUEST=38,
	BUBBLE_TRAIN=36,
	BUBBLE_UPGRADE=34,
	BUBBLE__INVALID=4294967295
} BubbleType;

typedef enum OreType {
	ORE_NORMAL=0,
	ORE_PROCESSED=1
} OreType;

typedef enum AbilityType {
	ABILITY_DRIVER=2,
	ABILITY_DYNAMITE=3,
	ABILITY_PILOT=0,
	ABILITY_REPAIR=4,
	ABILITY_SAILOR=1,
	ABILITY_SCANNER=5,
	ABILITY__INVALID=4294967295
} AbilityType;

typedef enum ActivityType {
	ACTIVITY_BUILDPATH=40,
	ACTIVITY_CANTDO=11,
	ACTIVITY_CARRY=17,
	ACTIVITY_CARRYRUBBLE=18,
	ACTIVITY_CARRYSTAND=22,
	ACTIVITY_CARRYTURNLEFT=20,
	ACTIVITY_CARRYTURNRIGHT=21,
	ACTIVITY_CLEAR=30,
	ACTIVITY_CLOSING=54,
	ACTIVITY_COLLECT=15,
	ACTIVITY_CRUMBLE=77,
	ACTIVITY_DESPOSIT=29,
	ACTIVITY_DRILL=4,
	ACTIVITY_DYNAMITE=28,
	ACTIVITY_EAT=35,
	ACTIVITY_EMERGE=12,
	ACTIVITY_ENTER=13,
	ACTIVITY_ENTERREIN=14,
	ACTIVITY_EXPLODE=42,
	ACTIVITY_FIRELASER=44,
	ACTIVITY_FLOATOFF=52,
	ACTIVITY_FLOATON=51,
	ACTIVITY_FREEZED=45,
	ACTIVITY_FREEZEMELT=47,
	ACTIVITY_FREEZESTART=46,
	ACTIVITY_GATHER=16,
	ACTIVITY_GETUP=39,
	ACTIVITY_HITBACK=26,
	ACTIVITY_HITFRONT=25,
	ACTIVITY_HITHARD=27,
	ACTIVITY_HITLEFT=23,
	ACTIVITY_HITRIGHT=24,
	ACTIVITY_OPEN=55,
	ACTIVITY_OPENING=53,
	ACTIVITY_PLACE=31,
	ACTIVITY_RECHARGE=48,
	ACTIVITY_REINFORCE=7,
	ACTIVITY_REPAIR=32,
	ACTIVITY_REST=34,
	ACTIVITY_REVERSE=8,
	ACTIVITY_ROUTE=1,
	ACTIVITY_ROUTERUBBLE=2,
	ACTIVITY_RUNPANIC=3,
	ACTIVITY_SLIP=33,
	ACTIVITY_STAMP=36,
	ACTIVITY_STAND=0,
	ACTIVITY_TELEPORT=5,
	ACTIVITY_TELEPORTIN=78,
	ACTIVITY_THROW=19,
	ACTIVITY_THROWMAN=37,
	ACTIVITY_THROWNBYROCKMONSTER=38,
	ACTIVITY_TRAIN=50,
	ACTIVITY_TURNLEFT=9,
	ACTIVITY_TURNRIGHT=10,
	ACTIVITY_UNPOWERED=43,
	ACTIVITY_UPGRADE=41,
	ACTIVITY_WAITING1=56,
	ACTIVITY_WAITING10=65,
	ACTIVITY_WAITING11=66,
	ACTIVITY_WAITING12=67,
	ACTIVITY_WAITING13=68,
	ACTIVITY_WAITING14=69,
	ACTIVITY_WAITING15=70,
	ACTIVITY_WAITING16=71,
	ACTIVITY_WAITING17=72,
	ACTIVITY_WAITING18=73,
	ACTIVITY_WAITING19=74,
	ACTIVITY_WAITING2=57,
	ACTIVITY_WAITING20=75,
	ACTIVITY_WAITING21=76,
	ACTIVITY_WAITING3=58,
	ACTIVITY_WAITING4=59,
	ACTIVITY_WAITING5=60,
	ACTIVITY_WAITING6=61,
	ACTIVITY_WAITING7=62,
	ACTIVITY_WAITING8=63,
	ACTIVITY_WAITING9=64,
	ACTIVITY_WAKEUP=49,
	ACTIVITY_WALK=6,
	ACTIVITY__INVALID=4294967295
} ActivityType;

typedef enum NERPSFunctionArgs {
	NERPS_ARGS_0=0,
	NERPS_ARGS_0_NORETURN=3,
	NERPS_ARGS_1=1,
	NERPS_ARGS_1_NORETURN=4,
	NERPS_ARGS_2=2,
	NERPS_ARGS_2_NORETURN=5,
	NERPS_ARGS_3_NORETURN=6,
	NERPS_END_OF_LIST=7
} NERPSFunctionArgs;

typedef struct NERPSFunctionSignature NERPSFunctionSignature, *PNERPSFunctionSignature;

struct NERPSFunctionSignature {
	char * name;
	int (* function)(int *);
	enum NERPSFunctionArgs arguments;
};

typedef struct HuffmanLeaf HuffmanLeaf, *PHuffmanLeaf;

struct HuffmanLeaf {
	uint value_1;
	ushort count_1;
	undefined field_0x6;
	undefined field_0x7;
	uint value_2;
	ushort count_2;
	undefined field_0xe;
	undefined field_0xf;
};

typedef struct IDirect3D3 IDirect3D3, *PIDirect3D3;

struct IDirect3D3 {
	undefined field_0x0;
	undefined field_0x1;
	undefined field_0x2;
	undefined field_0x3;
};

typedef struct IFilterGraph IFilterGraph, *PIFilterGraph;

typedef struct IFilterGraphVtbl IFilterGraphVtbl, *PIFilterGraphVtbl;

struct IFilterGraphVtbl {
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

struct IFilterGraph {
	struct IFilterGraphVtbl * lpVtbl;
};

typedef struct IDirect3DTexture IDirect3DTexture, *PIDirect3DTexture;

typedef struct IDirect3DTextureVtbl IDirect3DTextureVtbl, *PIDirect3DTextureVtbl;

struct IDirect3DTexture {
	struct IDirect3DTextureVtbl * lpVtbl;
};

struct IDirect3DTextureVtbl {
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

struct D3DRMPickDesc2 {
	DWORD ulFaceIdx;
	enum D3DRMGroupIndex lGroupIdx;
	struct Vector3F vPosition;
	struct Point2F tuv; // Texture coordinates
	struct Vector3F dvNormal;
	DWORD dcColor;
};

struct IDirect3DRMPicked2ArrayVtbl { // Subclass of IDirect3DRMArrayVtbl
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	DWORD (* GetSize)(struct IDirect3DRMPicked2Array *);
	HRESULT (* GetPick)(struct IDirect3DRMPicked2Array *, DWORD, struct IDirect3DRMVisual * *, struct IDirect3DRMFrameArray * *, struct D3DRMPickDesc2 *);
};

struct IDirect3DRMPicked2Array {
	struct IDirect3DRMPicked2ArrayVtbl * lpVtbl;
};

typedef struct IDirectDraw IDirectDraw, *PIDirectDraw;

typedef struct IDirectDrawVtbl IDirectDrawVtbl, *PIDirectDrawVtbl;

struct IDirectDrawVtbl {
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

struct IDirectDraw {
	struct IDirectDrawVtbl * lpVtbl;
};

typedef struct IDirect3DViewport3 IDirect3DViewport3, *PIDirect3DViewport3;

typedef struct IDirect3DViewport3Vtbl IDirect3DViewport3Vtbl, *PIDirect3DViewport3Vtbl;

struct IDirect3DViewport3Vtbl {
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

struct IDirect3DViewport3 {
	struct IDirect3DViewport3Vtbl * lpVtbl;
};

typedef struct IAVIStreaming IAVIStreaming, *PIAVIStreaming;

typedef struct IAVIStreamingVtbl IAVIStreamingVtbl, *PIAVIStreamingVtbl;

struct IAVIStreamingVtbl {
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* Begin)(struct IAVIStreaming *, int, int, int);
	HRESULT (* End)(struct IAVIStreaming *);
};

struct IAVIStreaming {
	struct IAVIStreamingVtbl * lpVtbl;
};

typedef struct IDirect3DRMVisualArray IDirect3DRMVisualArray, *PIDirect3DRMVisualArray;

typedef struct IDirect3DRMVisualArrayVtbl IDirect3DRMVisualArrayVtbl, *PIDirect3DRMVisualArrayVtbl;

struct IDirect3DRMVisualArray {
	struct IDirect3DRMVisualArrayVtbl * lpVtbl;
};

struct IDirect3DRMVisualArrayVtbl { // Subclass of IDirect3DRMArrayVtbl
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	DWORD (* GetSize)(struct IDirect3DRMVisualArray *);
	HRESULT (* GetElement)(struct IDirect3DRMVisualArray *, DWORD, struct IDirect3DRMVisual * *);
};

typedef struct IDirect3DRMViewport IDirect3DRMViewport, *PIDirect3DRMViewport;

typedef struct IDirect3DRMViewportVtbl IDirect3DRMViewportVtbl, *PIDirect3DRMViewportVtbl;

struct IDirect3DRMViewport {
	struct IDirect3DRMViewportVtbl * lpVtbl;
};

struct IDirect3DRMViewportVtbl {
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

struct IStreamSample {
	struct IStreamSampleVtbl * lpVtbl;
};

struct IStreamSampleVtbl {
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

struct IDirect3DRMFrame2 { // Extension of IDirect3DRMFrame
	struct IDirect3DRMFrame2Vtbl * lpVtbl;
};

struct IDirect3DRMFrame2Vtbl { // Extension of IDirect3DRMFrameVtbl
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

typedef struct IAVIFile IAVIFile, *PIAVIFile;

typedef struct IAVIFileVtbl IAVIFileVtbl, *PIAVIFileVtbl;

typedef struct AVIFILEINFOA AVIFILEINFOA, *PAVIFILEINFOA;

typedef enum AVIFileInfoFlags { // Flags for dwFlags in AVIFILEINFO_ struct
	AVIFILEINFO_COPYRIGHTED=131072,
	AVIFILEINFO_HASINDEX=16,
	AVIFILEINFO_ISINTERLEAVED=256,
	AVIFILEINFO_MUSTUSEINDEX=32,
	AVIFILEINFO_WASCAPTUREFILE=65536
} AVIFileInfoFlags;

typedef enum AVIFileInfoCaps { // Flags for dwCaps in AVIFILEINFO_ struct
	AVIFILECAPS_ALLKEYFRAMES=16,
	AVIFILECAPS_CANREAD=1,
	AVIFILECAPS_CANWRITE=2,
	AVIFILECAPS_NOCOMPRESSION=32
} AVIFileInfoCaps;

struct AVIFILEINFOA {
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

struct IAVIFileVtbl {
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

struct IAVIFile {
	struct IAVIFileVtbl * lpVtbl;
};

typedef struct IMultiMediaStream IMultiMediaStream, *PIMultiMediaStream;

typedef struct IMultiMediaStreamVtbl IMultiMediaStreamVtbl, *PIMultiMediaStreamVtbl;

struct IMultiMediaStream {
	struct IMultiMediaStreamVtbl * lpVtbl;
};

struct IMultiMediaStreamVtbl {
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

struct IDirect3DRMArray {
	struct IDirect3DRMArrayVtbl * lpVtbl;
};

struct IDirect3DRMArrayVtbl { // Subclass of IDirect3DRMArrayVtbl
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer GetSize;
};

typedef struct IDirect3DRMObject IDirect3DRMObject, *PIDirect3DRMObject;

typedef struct IDirect3DRMObjectVtbl IDirect3DRMObjectVtbl, *PIDirect3DRMObjectVtbl;

struct IDirect3DRMObject {
	struct IDirect3DRMObjectVtbl * lpVtbl;
};

struct IDirect3DRMObjectVtbl {
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

struct IDirect3DRMTexture2 {
	struct IDirect3DRMTexture2Vtbl * lpVtbl;
};

struct IDirect3DRMTexture2Vtbl {
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

struct IDirect3DMaterial2 {
	struct IDirect3DMaterial2Vtbl * lpVtbl;
};

struct IDirect3DMaterial2Vtbl {
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer SetMaterial;
	pointer GetMaterial;
	pointer GetHandle;
};

typedef struct IDirect3DMaterial IDirect3DMaterial, *PIDirect3DMaterial;

typedef struct IDirect3DMaterialVtbl IDirect3DMaterialVtbl, *PIDirect3DMaterialVtbl;

struct IDirect3DMaterialVtbl {
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

struct IDirect3DMaterial {
	struct IDirect3DMaterialVtbl * lpVtbl;
};

typedef struct IDirect3DLight IDirect3DLight, *PIDirect3DLight;

typedef struct IDirect3DLightVtbl IDirect3DLightVtbl, *PIDirect3DLightVtbl;

struct IDirect3DLightVtbl {
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer Initialize;
	pointer SetLight;
	pointer GetLight;
};

struct IDirect3DLight {
	struct IDirect3DLightVtbl * lpVtbl;
};

typedef struct IDirectDrawSurface2 IDirectDrawSurface2, *PIDirectDrawSurface2;

typedef struct IDirectDrawSurface2Vtbl IDirectDrawSurface2Vtbl, *PIDirectDrawSurface2Vtbl;

struct IDirectDrawSurface2Vtbl {
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

struct IDirectDrawSurface2 {
	struct IDirectDrawSurface2Vtbl * lpVtbl;
};

typedef struct D3DRMLoadResource D3DRMLoadResource, *PD3DRMLoadResource;

typedef HINSTANCE HMODULE;

struct D3DRMLoadResource {
	HMODULE hModule;
	LPSTR lpName;
	LPSTR lpType;
};

typedef struct D3DRMRay D3DRMRay, *PD3DRMRay;

struct D3DRMRay {
	struct Vector3F dvDir;
	struct Vector3F dvPos;
};

typedef struct D3DRMAnimationScaleKey D3DRMAnimationScaleKey, *PD3DRMAnimationScaleKey;

typedef enum D3DRMAnimationKeyType {
	D3DRMANIMATION_POSITIONKEY=3,
	D3DRMANIMATION_ROTATEKEY=1,
	D3DRMANIMATION_SCALEKEY=2
} D3DRMAnimationKeyType;

struct D3DRMAnimationScaleKey {
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

struct D3DLIGHTINGCAPS {
	DWORD dwSize;
	DWORD dwCaps; // Lighting caps
	DWORD dwLightingModel; // Lighting model - RGB or mono
	DWORD dwNumLights; // Number of lights that can be handled
};

struct D3DPRIMCAPS {
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

struct D3DTRANSFORMCAPS {
	DWORD dwSize;
	DWORD dwCaps;
};

struct D3DDEVICEDESC_V1 {
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

struct D3DRMQuaternion {
	float s;
	struct Vector3F v;
};

typedef struct AVIFILEINFOW AVIFILEINFOW, *PAVIFILEINFOW;

struct AVIFILEINFOW {
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

struct DSBUFFERDESC {
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwBufferBytes;
	DWORD dwReserved;
	WAVEFORMATEX * lpwfxFormat;
};

typedef struct AVISTREAMINFOW AVISTREAMINFOW, *PAVISTREAMINFOW;

struct AVISTREAMINFOW {
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

struct D3DRMAnimationRotateKey {
	DWORD dwSize;
	enum D3DRMAnimationKeyType dwKeyType;
	float dvTime;
	DWORD dwID;
	struct D3DRMQuaternion dqRotateKey;
};

typedef struct D3DRMAnimationPositionKey D3DRMAnimationPositionKey, *PD3DRMAnimationPositionKey;

struct D3DRMAnimationPositionKey {
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

struct D3DRMLoadMemory {
	void * lpMemory;
	DWORD dwSize;
};

typedef struct D3DRMPMeshLoadStatus D3DRMPMeshLoadStatus, *PD3DRMPMeshLoadStatus;

typedef enum D3DRMMeshStatusFlags {
	D3DRMPMESHSTATUS_BASEMESHCOMPLETE=4,
	D3DRMPMESHSTATUS_COMPLETE=8,
	D3DRMPMESHSTATUS_INTERRUPTED=2,
	D3DRMPMESHSTATUS_RENDERABLE=16,
	D3DRMPMESHSTATUS_VALID=1
} D3DRMMeshStatusFlags;

struct D3DRMPMeshLoadStatus {
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

struct DDSCAPS {
	DWORD dwCaps; // capabilities of surface wanted
};

struct DDSURFACEDESC {
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

struct D3DRMAnimationKey {
	DWORD dwSize;
	enum D3DRMAnimationKeyType dwKeyType;
	float dvTime;
	DWORD dwID;
	float dvK[4];
};

typedef struct AVICOMPRESSOPTIONS AVICOMPRESSOPTIONS, *PAVICOMPRESSOPTIONS;

typedef enum AVICompressFlags { // Defines for the dwFlags field of the AVICOMPRESSOPTIONS struct
	AVICOMPRESSF_DATARATE=2,
	AVICOMPRESSF_INTERLEAVE=1,
	AVICOMPRESSF_KEYFRAMES=4,
	AVICOMPRESSF_VALID=8
} AVICompressFlags;

struct AVICOMPRESSOPTIONS {
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

typedef enum D3DRMMeshEventType {
	D3DRMPMESHEVENT_BASEMESH=1,
	D3DRMPMESHEVENT_COMPLETE=2
} D3DRMMeshEventType;

typedef enum D3DTextureFilter {
	D3DFILTER_INVALID_0=0,
	D3DFILTER_LINEAR=2,
	D3DFILTER_LINEARMIPLINEAR=6,
	D3DFILTER_LINEARMIPNEAREST=5,
	D3DFILTER_MIPLINEAR=4,
	D3DFILTER_MIPNEAREST=3,
	D3DFILTER_NEAREST=1
} D3DTextureFilter;

typedef enum D3DRMAnimationOptions {
	D3DRMANIMATION_CLOSED=2,
	D3DRMANIMATION_LINEARPOSITION=4,
	D3DRMANIMATION_OPEN=1,
	D3DRMANIMATION_POSITION=32,
	D3DRMANIMATION_SCALEANDROTATION=16,
	D3DRMANIMATION_SPLINEPOSITION=8
} D3DRMAnimationOptions;

typedef enum D3DPrimitiveType {
	D3DPT_INVALID_0=0,
	D3DPT_LINELIST=2,
	D3DPT_LINESTRIP=3,
	D3DPT_POINTLIST=1,
	D3DPT_TRIANGLEFAN=6,
	D3DPT_TRIANGLELIST=4,
	D3DPT_TRIANGLESTRIP=5
} D3DPrimitiveType;

typedef enum D3DBlend {
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

typedef enum D3DRMXOFFormat {
	D3DRMXOF_BINARY=0,
	D3DRMXOF_COMPRESSED=1,
	D3DRMXOF_TEXT=2
} D3DRMXOFFormat;

typedef enum D3DRMLoadOptions {
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

typedef enum D3DTextureOp {
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

typedef enum D3DRMTextureQuality {
	D3DRMTEXTURE_LINEAR=1,
	D3DRMTEXTURE_LINEARMIPLINEAR=5,
	D3DRMTEXTURE_LINEARMIPNEAREST=4,
	D3DRMTEXTURE_MIPLINEAR=3,
	D3DRMTEXTURE_MIPNEAREST=2,
	D3DRMTEXTURE_NEAREST=0
} D3DRMTextureQuality;

typedef enum D3DRMTextureFlags { // Texture flags
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

typedef enum D3DRMWireframeOptions {
	D3DRMWIREFRAME_CULL=1,
	D3DRMWIREFRAME_HIDDENLINE=2
} D3DRMWireframeOptions;

typedef enum D3DRMInterpolationOptions {
	D3DRMINTERPOLATION_CLOSED=2,
	D3DRMINTERPOLATION_LINEAR=4,
	D3DRMINTERPOLATION_NEAREST=256,
	D3DRMINTERPOLATION_OPEN=1,
	D3DRMINTERPOLATION_SLERPNORMALS=128,
	D3DRMINTERPOLATION_SPLINE=8,
	D3DRMINTERPOLATION_VERTEXCOLOR=64
} D3DRMInterpolationOptions;

typedef enum D3DRMSaveOptions {
	D3DRMXOFSAVE_ALL=15,
	D3DRMXOFSAVE_MATERIALS=4,
	D3DRMXOFSAVE_NORMALS=1,
	D3DRMXOFSAVE_TEMPLATES=16,
	D3DRMXOFSAVE_TEXTURECOORDINATES=2,
	D3DRMXOFSAVE_TEXTURENAMES=8,
	D3DRMXOFSAVE_TEXTURETOPOLOGY=32
} D3DRMSaveOptions;

typedef enum D3DRMUserVisualReason {
	D3DRMUSERVISUAL_CANSEE=0,
	D3DRMUSERVISUAL_RENDER=1
} D3DRMUserVisualReason;

typedef enum D3DRMWrapType {
	D3DRMWRAP_BOX=5,
	D3DRMWRAP_CHROME=3,
	D3DRMWRAP_CYLINDER=1,
	D3DRMWRAP_FLAT=0,
	D3DRMWRAP_SHEET=4,
	D3DRMWRAP_SPHERE=2
} D3DRMWrapType;

typedef enum D3DRMStateChangeFlags {
	D3DRMSTATECHANGE_LIGHT=64,
	D3DRMSTATECHANGE_NONVOLATILE=4,
	D3DRMSTATECHANGE_RENDER=32,
	D3DRMSTATECHANGE_UPDATEONLY=1,
	D3DRMSTATECHANGE_VOLATILE=2
} D3DRMStateChangeFlags;

typedef enum D3DRMFrameTraversalOptions { // Values for flags in IDirect3DRMFrame3::SetTraversalOptions
	D3DRMFRAME_PICKENABLE=2,
	D3DRMFRAME_RENDERENABLE=1
} D3DRMFrameTraversalOptions;

typedef enum D3DShadeMode {
	D3DSHADE_FLAT=1,
	D3DSHADE_GOURAUD=2,
	D3DSHADE_INVALID_0=0,
	D3DSHADE_PHONG=3
} D3DShadeMode;

typedef enum D3DTransformStateType {
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

typedef enum D3DCull {
	D3DCULL_CCW=3,
	D3DCULL_CW=2,
	D3DCULL_INVALID_0=0,
	D3DCULL_NONE=1
} D3DCull;

typedef enum D3DTextureArg { // (unnamed)
	D3DTA_ALPHAREPLICATE=32,
	D3DTA_COMPLEMENT=16,
	D3DTA_CURRENT=1,
	D3DTA_DIFFUSE=0,
	D3DTA_SELECTMASK=15,
	D3DTA_SPECULAR=4,
	D3DTA_TEXTURE=2,
	D3DTA_TFACTOR=3
} D3DTextureArg;

typedef enum D3DRMMaterialOverride {
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

typedef enum D3DRMFPTFFlags {
	D3DRMFPTF_ALPHA=1,
	D3DRMFPTF_NOALPHA=2,
	D3DRMFPTF_NOTPALETTIZED=8,
	D3DRMFPTF_PALETTIZED=4
} D3DRMFPTFFlags;

typedef enum D3DLightStateType {
	D3DLIGHTSTATE_AMBIENT=2,
	D3DLIGHTSTATE_COLORMODEL=3,
	D3DLIGHTSTATE_FOGDENSITY=7,
	D3DLIGHTSTATE_FOGEND=6,
	D3DLIGHTSTATE_FOGMODE=4,
	D3DLIGHTSTATE_FOGSTART=5,
	D3DLIGHTSTATE_INVALID_0=0,
	D3DLIGHTSTATE_MATERIAL=1
} D3DLightStateType;

typedef enum D3DRenderStateType {
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

typedef enum D3DRMShadowFlags { // Shadow flags
	D3DRMSHADOW_TRUEALPHA=1
} D3DRMShadowFlags;

typedef enum D3DRMColorSource {
	D3DRMCOLOR_FROMFACE=0,
	D3DRMCOLOR_FROMVERTEX=1
} D3DRMColorSource;

typedef enum D3DTextureStageStateType {
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

typedef char * va_list;

typedef struct astruct astruct, *Pastruct;

struct astruct {
	byte field_0x0;
	byte field_0x1;
	undefined field_0x2;
	undefined field_0x3;
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

typedef uint size_t;

typedef int (* _PNH)(size_t);

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

typedef struct _RGNDATA * LPRGNDATA;

#define BITSPIXEL 12

typedef WCHAR * PCNZWCH;

typedef WCHAR * LPWCH;

typedef WCHAR * LPCWSTR;

typedef LONG * PLONG;

typedef CHAR * LPCH;

typedef DWORD LCID;

typedef CHAR * PCNZCH;

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

