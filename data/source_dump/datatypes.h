typedef unsigned char   undefined;

typedef unsigned long long    GUID;
typedef unsigned int    ImageBaseOffset32;
typedef unsigned char    bool;
typedef unsigned char    byte;
typedef unsigned int    dword;
typedef long double     float10;  // No... Visual Studio doesn't support this. Just give up :c
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

typedef unsigned short    wchar16;
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

#define DRIVE_NO_ROOT_DIR 1

#define INVALID_FILE_ATTRIBUTES -1

#define DRIVE_CDROM 5

typedef DWORD ULONG;

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
	TEXTURE_PATH_BASE=118,
	TEXTURE_PATH_BASE_POWERED=102,
	TEXTURE_PATH_BUILD=97,
	TEXTURE_PATH_C=99,
	TEXTURE_PATH_C_POWERED=115,
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

typedef struct ResourceData ResourceData, *PResourceData;

typedef struct IDirect3DRMFrame3 IDirect3DRMFrame3, *PIDirect3DRMFrame3;

typedef struct ResourceSubdata ResourceSubdata, *PResourceSubdata;

typedef enum ResourceType {
	RESOURCE_ACT=4,
	RESOURCE_ANIM=3,
	RESOURCE_FRAME=2,
	RESOURCE_LIGHT=5,
	RESOURCE_LWO=8,
	RESOURCE_LWS=7,
	RESOURCE_MESH=1,
	RESOURCE_NULL=0,
	RESOURCE__INVALID=4294967295,
	RESOURCE_unassigned=6
} ResourceType;

typedef enum ResourceDataFlags {
	RESDATA_NONE=0,
	RESDATA_UNK_10=16,
	RESDATA_UNK_2=2,
	RESDATA_UNK_20=32,
	RESDATA_UNK_8=8,
	RESDATA_UNK_80=128
} ResourceDataFlags;

typedef struct LiveObject LiveObject, *PLiveObject;

typedef struct ActStruct_14 ActStruct_14, *PActStruct_14;

typedef struct IDirect3DRMFrame3Vtbl IDirect3DRMFrame3Vtbl, *PIDirect3DRMFrame3Vtbl;

typedef long HRESULT;

typedef struct IUnknown IUnknown, *PIUnknown;


// WARNING! conflicting data type names: /guiddef.h/GUID - /GUID

typedef GUID IID;

typedef CHAR * LPCSTR;

typedef DWORD * LPDWORD;

typedef struct IDirect3DRMLight IDirect3DRMLight, *PIDirect3DRMLight;

typedef struct IDirect3DRMMesh IDirect3DRMMesh, *PIDirect3DRMMesh;

typedef struct Struct_34 Struct_34, *PStruct_34;

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
	OBJECT_ORE=7,
	OBJECT_PATH=15,
	OBJECT_POWERCRYSTAL=6,
	OBJECT_PUSHER=16,
	OBJECT_ROCKMONSTER=3,
	OBJECT_SONICBLASTER=13,
	OBJECT_SPIDERWEB=12,
	OBJECT_TVCAMERA=4294967295,
	OBJECT_UPGRADEPART=10,
	OBJECT_VEHICLE=1
} ObjectType;

typedef struct VehicleData VehicleData, *PVehicleData;

typedef struct CreatureData CreatureData, *PCreatureData;

typedef struct BuildingData BuildingData, *PBuildingData;

typedef struct UpgradeData UpgradeData, *PUpgradeData;

typedef struct Vector3F Vector3F, *PVector3F;

typedef struct Point2F Point2F, *PPoint2F;

typedef struct AITaskData AITaskData, *PAITaskData;

typedef struct FlockData FlockData, *PFlockData;

typedef struct ObjectStats ObjectStats, *PObjectStats;

typedef enum ToolType {
	TOOL_DRILL=0,
	TOOL_FREEZERBEAM=7,
	TOOL_HAMMER=2,
	TOOL_LASERBEAM=4,
	TOOL_PUSHERBEAM=5,
	TOOL_SHOVEL=1,
	TOOL_SONICBLASTER=6,
	TOOL_SPANNER=3,
	TOOL__INVALID=4294967295
} ToolType;

typedef enum LiveFlags1 {
	LIVEOBJ1_CARRYING=1024,
	LIVEOBJ1_CLEARING=262144,
	LIVEOBJ1_EATING=1073741824,
	LIVEOBJ1_MOVING=1,
	LIVEOBJ1_NONE=0,
	LIVEOBJ1_PLACING=524288,
	LIVEOBJ1_REINFORCING=64,
	LIVEOBJ1_REST=536870912,
	LIVEOBJ1_TURNING=4,
	LIVEOBJ1_TURNRIGHT=128,
	LIVEOBJ1_UNK_2_LEFTING=2
} LiveFlags1;

typedef enum LiveFlags2 {
	LIVEOBJ2_DRIVING=8,
	LIVEOBJ2_NONE=0,
	LIVEOBJ2_TRAINING=1024,
	LIVEOBJ2_UNK_800=2048,
	LIVEOBJ2_UPGRADING=32768
} LiveFlags2;

typedef enum LiveFlags3 {
	LIVEOBJ3_NONE=0,
	LIVEOBJ3_SIMPLEOBJECT=131072,
	LIVEOBJ3_UNK_80000=524288
} LiveFlags3;

typedef enum LiveFlags4 {
	LIVEOBJ4_NONE=0
} LiveFlags4;

typedef enum LiveFlags5 {
	LIVEOBJ5_NONE=0
} LiveFlags5;

typedef struct IUnknownVtbl IUnknownVtbl, *PIUnknownVtbl;

typedef struct IDirect3DRMLightVtbl IDirect3DRMLightVtbl, *PIDirect3DRMLightVtbl;

typedef struct IDirect3DRMMeshVtbl IDirect3DRMMeshVtbl, *PIDirect3DRMMeshVtbl;

typedef struct LwoFrame LwoFrame, *PLwoFrame;

typedef struct IDirect3DRMUserVisual IDirect3DRMUserVisual, *PIDirect3DRMUserVisual;

typedef struct IDirect3DRMViewport2 IDirect3DRMViewport2, *PIDirect3DRMViewport2;

typedef enum BOOL3 { // A 3-state boolean for True, False, or Error
	BOOL3_ERROR=2,
	BOOL3_FALSE=0,
	BOOL3_TRUE=1
} BOOL3;

typedef struct ObjectUpgradesData ObjectUpgradesData, *PObjectUpgradesData;

typedef struct PolyMeshData PolyMeshData, *PPolyMeshData;

typedef enum AITaskType {
	AITASK_ANIMATIONWAIT=14,
	AITASK_ATTACKOBJECT=29,
	AITASK_ATTACKPATH=25,
	AITASK_ATTACKROCKMONSTER=26,
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
	AITASK_SONICBLASTER=20,
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

typedef struct FlockSubdata FlockSubdata, *PFlockSubdata;

typedef struct Size2F Size2F, *PSize2F;

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

typedef struct IDirect3DRMUserVisualVtbl IDirect3DRMUserVisualVtbl, *PIDirect3DRMUserVisualVtbl;

typedef struct IDirect3DRMViewport2Vtbl IDirect3DRMViewport2Vtbl, *PIDirect3DRMViewport2Vtbl;

typedef struct ObjectUpgradePartData ObjectUpgradePartData, *PObjectUpgradePartData;

struct IDirect3DRMMesh {
	struct IDirect3DRMMeshVtbl * lpVtbl;
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
	undefined4 field_2c;
	undefined4 field_30;
	byte aiNode;
	undefined field_0x35;
	undefined field_0x36;
	undefined field_0x37;
	BOOL fallinUpper;
	float fallinIntensity;
	float fallinTimer;
	undefined4 field_44;
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

struct LevelStruct_1c { // related to Terrain map?
	struct ResourceData * resData;
	struct Point2I position;
	undefined4 field_c;
	struct LevelStruct_1c * next;
	struct LevelStruct_1c * previous;
	BOOL bool_18;
};

struct IDirect3DRMFrame3 {
	struct IDirect3DRMFrame3Vtbl * lpVtbl;
};

struct IDirect3DRMLight {
	struct IDirect3DRMLightVtbl * lpVtbl;
};

struct ResourceSubdata {
	char * name;
	struct IDirect3DRMLight * light;
	struct IDirect3DRMMesh * mesh;
	struct Struct_34 * struct34_c;
};

struct Vector3F {
	float x;
	float y;
	float z;
};

struct Point2F {
	float x;
	float y;
};

struct LiveObject {
	enum ObjectType objType;
	int objIndex;
	char * customName; // max size is 11 (NOT null-terminated)
	struct VehicleData * vehicle;
	struct CreatureData * miniFigure;
	struct CreatureData * rockMonster;
	struct BuildingData * building;
	struct ResourceData * other;
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
	undefined4 field_2bc;
	undefined4 field_2c0;
	undefined4 field_2c4;
	undefined4 field_2c8;
	undefined4 field_2cc;
	undefined4 field_2d0;
	float float_2d4;
	BOOL unkbool_2d8;
	struct ResourceData * resData_2dc;
	int index_2e0;
	struct ResourceData * resData_2e4;
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
	undefined4 field_364;
	undefined4 field_368;
	struct LiveObject * drivenObject; // same as drivingThisObject
	enum ToolType carriedTools[5];
	uint numCarriedTools;
	undefined4 field_388;
	undefined4 field_38c;
	undefined4 field_390;
	undefined4 field_394;
	undefined4 field_398;
	undefined4 field_39c;
	undefined4 field_3a0;
	undefined4 field_3a4;
	undefined4 field_3a8;
	undefined4 field_3ac;
	undefined4 field_3b0;
	undefined4 field_3b4;
	undefined4 field_3b8;
	undefined4 field_3bc;
	struct LiveObject * object_3c0;
	undefined4 field_3c4;
	undefined4 field_3c8;
	struct LiveObject * object_3cc;
	undefined4 field_3d0;
	float elapsedTime1; // elapsed time counter 1
	float elapsedTime2; // elapsed time counter 2
	float activityElapsedTime; // elapsed time since last order?
	enum LiveFlags1 flags1_3e0;
	enum LiveFlags2 flags2_3e4;
	enum LiveFlags3 flags3_3e8; // (assigned 0, flags?)
	enum LiveFlags4 flags4_3ec;
	enum LiveFlags5 flags5_3f0; // (assigned 0, flags?)
	undefined4 field_3f4;
	undefined4 field_3f8;
	undefined4 field_3fc;
	undefined4 field_400;
	undefined4 field_404;
	struct LiveObject * pool_m_next;
};

struct Size2F {
	float width;
	float height;
};

struct ActStruct_14 { // structure assigned to ResourceData->field_24 (allocated for ACT,ANIM resource types)
	struct ResourceData * resData; // (init: source of DuplicateResource)
	undefined4 field_4; // (init: 0)
	undefined4 field_8; // (init: 0)
	struct IDirect3DRMFrame3 * frame; // (init: ResourceData->frame2)
	BOOL isUsed; // (init: 1)
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
	pointer SetType;
	pointer SetColor;
	pointer SetColorRGB;
	pointer SetRange;
	pointer SetUmbra;
	pointer SetPenumbra;
	pointer SetConstantAttenuation;
	pointer SetLinearAttenuation;
	pointer SetQuadraticAttenuation;
	pointer GetRange;
	pointer GetUmbra;
	pointer GetPenumbra;
	pointer GetConstantAttenuation;
	pointer GetLinearAttenuation;
	pointer GetQuadraticAttenuation;
	pointer GetColor;
	pointer GetType;
	pointer SetEnableFrame;
	pointer GetEnableFrame;
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
	undefined field_0x38_0x3c[0x4];
	undefined4 mode_3c;
	void * ptr_40;
	undefined field_0x44_0x48[0x4];
	struct LiveObject * object_48;
	enum AIPriorityType priorityType;
	uint taskStartTime;
	undefined field_0x54_0x5c[0x8];
	uint flags_5c; // not set means ptr_40 is assigned
	struct AITaskData * next; // assigned to DAT_004b4358
	struct AITaskData * pool_m_next;
};

struct CreatureData {
	int objIndex;
	struct ResourceData * aeResData; // ACT, true
	undefined4 field_8;
	undefined field_0xc_0x20[0x14];
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
	struct ResourceData * resData_48;
	undefined4 field_4c;
	undefined4 field_50;
	undefined4 cameraFramesTable_54[4];
	struct PolyMeshData * subdata_64;
	struct PolyMeshData * subdata_68;
	struct PolyMeshData * subdata_6c;
	uint flags;
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
	pointer SetVelocity;
	pointer SetZbufferMode;
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
	pointer TransformVectors;
	pointer InverseTransformVectors;
	pointer SetTraversalOptions;
	pointer GetTraversalOptions;
	pointer SetSceneFogMethod;
	pointer GetSceneFogMethod;
	pointer SetMaterialOverride;
	pointer GetMaterialOverride;
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
	undefined4 BuildingBase; // (from: FUN_00408bb0, invalid: -1, either ptr or basenumber)
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

struct ResourceData {
	struct IDirect3DRMFrame3 * frame1;
	struct IDirect3DRMFrame3 * frame2;
	struct IDirect3DRMFrame3 * frame3;
	struct ResourceSubdata * subdata_c;
	enum ResourceType resType;
	enum ResourceDataFlags flags;
	undefined4 field_18;
	undefined4 field_1c;
	struct LiveObject * ownerObj;
	struct ActStruct_14 * actstruct_24;
	struct ResourceData * pool_m_next;
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
	struct ResourceData * resData_98;
	struct FlockSubdata * subdataNext_9c;
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
	pointer TransformVectors;
	pointer InverseTransformVectors;
};

struct Struct_34 {
	uint count_0; // seems to be a count
	undefined4 field_4;
	struct LwoFrame * lwoTable_8; // table ptr? -> 0x10 (struct: 0x70)
	struct IDirect3DRMUserVisual * userVisual_c;
	struct IDirect3DRMViewport2 * viewport_10; // IDirect3DRMViewport2 ?
	undefined4 param4_14;
	undefined4 unkFlags3_18;
	void * ptr_1c;
	uint refCount_20;
	struct Struct_34 * struct34_24;
	struct IDirect3DRMFrame3 * frame_28;
	uint flags;
	struct Struct_34 * pool_m_next;
};

struct ObjectUpgradePartData {
	uint level;
	int NullInstance;
	char * NullObjectName;
	char * WeaponName;
	struct UpgradeData * upgradeData;
};

struct IDirect3DRMViewport2 {
	struct IDirect3DRMViewport2Vtbl * lpVtbl;
};

struct ObjectUpgradesData {
	struct ObjectUpgradePartData * parts; // always ObjectUpgradePartData[200]
	uint count;
	int currentLevel;
	uint levelsMask; // [carry][scan][speed][drill]
	struct LiveObject * * upgradeObjs;
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
	pointer Scale;
	pointer Translate;
	pointer GetBox;
	pointer AddGroup;
	pointer SetVertices;
	pointer SetGroupColor;
	pointer SetGroupColorRGB;
	pointer SetGroupMapping;
	pointer SetGroupQuality;
	pointer SetGroupMaterial;
	pointer SetGroupTexture;
	pointer GetGroupCount;
	pointer GetGroup;
	pointer GetVertices;
	pointer GetGroupColor;
	pointer GetGroupMapping;
	pointer GetGroupQuality;
	pointer GetGroupMaterial;
	pointer GetGroupTexture;
};

struct BuildingData {
	int objIndex;
	struct ResourceData * aeResData; // ACT, true
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
	undefined field_0x50_0x68[0x18];
	undefined4 field_68;
	undefined4 field_6c;
	uint CarryNullFrames;
	uint CameraNullFrames;
	uint ToolNullFrames;
	struct ResourceData * PowerLevelScene; // LWS, true
	undefined4 field_80;
	struct Point2I * shapePoints; // Point2I[10]
	uint shapeCount;
	struct ObjectUpgradesData upgrades;
	undefined field_0xa0_0xd0[0x30];
	float PivotMaxZ;
	float PivotMinZ;
	undefined field_0xd8_0x144[0x6c];
	uint count_144;
	uint flags;
};

struct PolyMeshData {
	undefined4 field_0;
	undefined4 field_4;
	char * partName; // name of LoadObject file.lwo
	uint index;
	int int_10;
	struct PolyMeshData * previous;
};

struct VehicleData {
	int objIndex;
	char * WheelNullName;
	struct ResourceData * aeResData1;
	struct ResourceData * aeResData2; // Optional second ae file (seen for Grannit Grinder legs)
	struct ResourceData * WheelMeshes[6]; // LWO, false
	undefined4 wheel_fields_28[6];
	uint numWheelNulls;
	undefined field_0x44_0x5c[0x18];
	undefined4 field_5c;
	undefined4 field_60;
	float float_64;
	float WheelRadius;
	undefined field_0x6c_0xb4[0x48];
	char * DrillNullName;
	char * DepositNullName;
	char * FireNullName; // "fire laser"
	char * DriverNullName;
	char * yPivot;
	char * xPivot;
	undefined4 field_cc;
	undefined4 field_d0;
	struct ResourceData * resData_d4;
	enum BOOL3 CameraFlipDir;
	char * CarryNullName;
	char * CameraNullName;
	undefined4 carryFramesTable_e4[7];
	undefined field_0x100_0x10c[0xc];
	undefined4 cameraFramesTable_10c[4];
	uint CarryNullFrames;
	uint CameraNullFrames;
	struct ObjectUpgradesData upgrades;
	undefined field_0x138_0x168[0x30];
	float PivotMaxZ;
	float PivotMinZ;
	undefined field_0x170_0x1c4[0x54];
	undefined4 table6_1c4[6];
	undefined4 field_1dc;
	struct PolyMeshData * subdata_1e0;
	struct PolyMeshData * subdata_1e4;
	uint flags; // HoldMissing TRUE -> 0x8
};

struct LwoFrame {
	uint dwSize;
	undefined field_0x4_0x64[0x60];
	undefined4 field_64;
	undefined field_0x68_0x6c[0x4];
	uint flags;
};

struct IUnknownVtbl {
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, void * *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
};

struct IUnknown {
	struct IUnknownVtbl * lpVtbl;
};

struct UpgradeData {
	int objectIndex;
	struct ResourceData * aeResData; // ACT, true
	struct LiveObject * object_8;
	undefined4 field_c;
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

struct IDirect3DRMUserVisual {
	struct IDirect3DRMUserVisualVtbl * lpVtbl;
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

typedef struct Struct_bc Struct_bc, *PStruct_bc;

typedef struct ImageFont ImageFont, *PImageFont;

typedef struct Struct_830 Struct_830, *PStruct_830;

typedef struct ColourRGBF ColourRGBF, *PColourRGBF;

typedef enum Direction {
	DIRECTION_DOWN=2,
	DIRECTION_LEFT=3,
	DIRECTION_RIGHT=1,
	DIRECTION_UP=0
} Direction;

typedef struct ImageBMP ImageBMP, *PImageBMP;

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
	GAME1_UNK_4=4,
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

typedef struct LevelSurfaceMap LevelSurfaceMap, *PLevelSurfaceMap;

typedef struct Size2I Size2I, *PSize2I;

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

typedef struct Rect2F Rect2F, *PRect2F;

typedef struct IDirectDrawSurface4 IDirectDrawSurface4, *PIDirectDrawSurface4;

typedef struct SurfaceMapStruct38 SurfaceMapStruct38, *PSurfaceMapStruct38;

typedef struct DirectXSurfaceTuple DirectXSurfaceTuple, *PDirectXSurfaceTuple;

typedef struct IDirectDrawSurface4Vtbl IDirectDrawSurface4Vtbl, *PIDirectDrawSurface4Vtbl;

typedef struct tagRECT tagRECT, *PtagRECT;

typedef struct tagRECT * LPRECT;

typedef struct DDSCAPS2 DDSCAPS2, *PDDSCAPS2;

typedef struct IDirectDrawPalette IDirectDrawPalette, *PIDirectDrawPalette;

typedef struct DDPIXELFORMAT DDPIXELFORMAT, *PDDPIXELFORMAT;

typedef struct DDSURFACEDESC2 DDSURFACEDESC2, *PDDSURFACEDESC2;

typedef struct DDCOLORKEY DDCOLORKEY, *PDDCOLORKEY;

typedef struct IDirect3DRMTexture3 IDirect3DRMTexture3, *PIDirect3DRMTexture3;

typedef struct IDirectDrawPaletteVtbl IDirectDrawPaletteVtbl, *PIDirectDrawPaletteVtbl;

typedef struct D3DRMPALETTEENTRY D3DRMPALETTEENTRY, *PD3DRMPALETTEENTRY;

typedef struct IDirect3DRMTexture3Vtbl IDirect3DRMTexture3Vtbl, *PIDirect3DRMTexture3Vtbl;

typedef struct D3DRMIMAGE D3DRMIMAGE, *PD3DRMIMAGE;

typedef enum D3DRMPALETTEFLAGS {
	D3DRMPALETTE_FREE=0,
	D3DRMPALETTE_READONLY=1,
	D3DRMPALETTE_RESERVED=2
} D3DRMPALETTEFLAGS;

struct Rect2F {
	float x;
	float y;
	float width;
	float height;
};

struct Struct_830 { // Probably a text rendering area
	struct ImageFont * font;
	struct Rect2F area;
	void * allocData;
	undefined field_0x18_0x418[0x400];
	uint allocSize;
	undefined field_0x41c_0x82c[0x410];
	uint flags;
};

struct Struct_bc {
	undefined4 mode_0;
	struct LiveObject * object_4;
	float float_8;
	float float_c;
	float float_10;
	undefined4 field_14;
	struct Vector3F vector_18;
	struct ResourceData * resData_24;
	struct ResourceData * resData_28;
	struct ResourceData * resData_2c;
	struct ResourceData * resData_30;
	undefined4 tableunk_34;
	undefined field_0x38_0x90[0x58];
	float float_90;
	undefined field_0x94_0xa0[0xc];
	struct Vector3F vector_a0;
	struct Vector3F vector_ac;
	uint flags;
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
	struct ResourceData * resRoot; // DAT_005570d8
	void * ptr_1c; // PTR_005570dc
	undefined4 field_20; // DAT_005570e0
	struct Struct_bc * structbc_24; // PTR_005570e4
	struct Struct_bc * structbc_28; // DAT_005570e8
	struct Struct_bc * structbc_2c; // DAT_005570ec
	struct ResourceData * struct2c_30; // PTR_005570f0
	struct ResourceData * struct2c_34; // DAT_005570f4
	struct ResourceData * struct2c_38; // PTR_005570f8
	struct ResourceData * struct2c_3c; // PTR_005570fc
	struct ResourceData * struct2c_40; // PTR_00557100
	struct ResourceData * struct2c_44; // PTR_00557104
	struct ResourceData * struct2c_48; // PTR_00557108
	struct ResourceData * struct2c_4c; // PTR_0055710c
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
	struct Struct_830 * struct830_80; // PTR_00557140
	struct Struct_830 * struct830_84; // PTR_00557144
	float float_88; // FLOAT_00557148
	float float_8c; // FLOAT_0055714c
	float float_90; // FLOAT_00557150
	float float_94; // FLOAT_00557154
	BOOL bool_98; // BOOL_00557158
	float gameSpeed; // FLOAT_0055715c
	struct LiveObject * object_a0; // DAT_00557160
	float float_a4; // FLOAT_00557164
	float float_a8; // FLOAT_00557168
	float float_ac; // FLOAT_0055716c
	float float_b0; // FLOAT_00557170
	float float_b4; // FLOAT_00557174
	float float_b8; // FLOAT_00557178
	float float_bc; // FLOAT_0055717c
	undefined4 field_c0; // DAT_00557180
	undefined4 field_c4; // DAT_0055718c
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
	struct ResourceData * RES_Boulder; // g_RES_BOULDER
	struct ResourceData * RES_BoulderExplode; // DAT_0055736c
	struct ResourceData * RES_BoulderExplodeIce; // DAT_00557370
	struct ResourceData * RES_Crystal; // g_RES_POWERCRYSTAL
	struct ResourceData * RES_Dynamite; // g_RES_DYNAMITE
	struct ResourceData * RES_Ores_TABLE[2]; // g_RES_ORES_TABLE
	struct ResourceData * RES_OohScary; // g_RES_OOHSCARY
	struct ResourceData * RES_Barrier; // g_RES_BARRIER
	struct ResourceData * RES_ElectricFence; // g_RES_ELECTRICFENCE
	struct ResourceData * RES_SpiderWeb; // g_RES_SPIDERWEB
	struct ResourceData * RES_RechargeSparkle; // DAT_00557394
	struct ResourceData * RES_MiniTeleportUp; // DAT_00557398
	struct ResourceData * RES_ElectricFenceStud; // DAT_0055739c
	struct ResourceData * RES_Pusher; // g_RES_PUSHER
	struct ResourceData * RES_Freezer; // g_RES_FREEZER
	struct ResourceData * RES_IceCube; // DAT_005573a8
	struct ResourceData * RES_SmashPath; // DAT_005573ac
	struct ResourceData * RES_LaserShot; // g_RES_LASERSHOT
	struct ResourceData * * RES_2f4_TABLEUNK; // DAT_005573b4
	undefined4 table10_2f8[10]; // g_UNK_TABLE__005573b8
	uint count10_2fc; // UINT_005573e0
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
	undefined4 table200_78c[200]; // UNK_ARRAY_0055784c
	undefined4 table200_aac[200]; // UNK_ARRAY_00557b6c
	uint count_dcc; // UINT_00557e8c
	uint count_dd0; // UINT_00557e90
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
	uint unkbool_308; // (may not be bool, compared with 0, and 1) g_GAME_UNK_BOOL_00557ec8
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
	float float_e3c; // FLOAT_00557efc
	float floatfps_e40; // assigned to Game_Update param_1 float fpsSync, FLOAT_00557f00
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
	char * renameInput; // DAT_00557fa0
	float float_ee4; // FLOAT_00557fa4
	float float_ee8; // FLOAT_00557fa8
	char * RenameReplace; // g_RenameReplace
	char * EndGameAVI1; // g_EndGameAVI1
	char * EndGameAVI2; // g_EndGameAVI2
};

struct LevelStruct_3c {
	undefined4 field_0;
	undefined4 field_4;
	undefined4 field_8;
	undefined4 field_c;
	undefined4 field_10;
	undefined4 field_14;
	undefined4 field_18;
	undefined4 field_1c;
	undefined4 field_20;
	undefined4 field_24;
	undefined4 field_28;
	undefined4 field_2c;
	undefined4 field_30;
	undefined4 field_34;
	undefined4 field_38;
};

struct DDCOLORKEY {
	DWORD dwColorSpaceLowValue;
	DWORD dwColorSpaceHighValue;
};

struct D3DRMIMAGE {
	int width; // width in pixels
	int height; // height in pixels
	int aspectx; // aspect ratio for non-square pixels
	int aspecty; // aspect ratio for non-square pixels
	int bitsPerPixel;
	BOOL isRGB; // if false, pixels are indices into a palette
	uint stride;
	byte * buffer1; // memory to render into (first buffer)
	byte * buffer2; // for double-buffering
	uint red_mask; // 0xfc (8-bit only)
	uint green_mask; // 0xfc (8-bit only)
	uint blue_mask; // 0xfc (8-bit only)
	uint alpha_mask; // 0xfc (8-bit only)
	int palette_size;
	struct D3DRMPALETTEENTRY * palette; // always allocated to size[256]
};

struct SurfaceMapStruct38 {
	undefined4 field_0;
	float float_4;
	undefined4 field_8;
	undefined4 field_c;
	undefined4 table_10[8];
	undefined field_0x30_0x34[0x4];
	uint flags;
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

struct DDSCAPS2 {
	DWORD dwCaps;
	DWORD dwCaps2;
	DWORD dwCaps3;
	DWORD dwCaps4_VolumeDepth;
};

struct DDSURFACEDESC2 {
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwHeight;
	DWORD dwWidth;
	DWORD lPitch_dwLinearSize;
	DWORD dwBackBufferCount_Depth;
	DWORD dwMipMapCount_RefreshRate_SrcVBHandle;
	DWORD dwAlphaBitDepth;
	DWORD dwReserved;
	LPVOID lpSurface;
	struct DDCOLORKEY ddckCKDestOverlay_dwEmptyFaceColor;
	struct DDCOLORKEY ddckCKDestBlt;
	struct DDCOLORKEY ddckCKSrcOverlay;
	struct DDCOLORKEY ddckCKSrcBlt;
	struct DDPIXELFORMAT ddpfPixelFormat;
	struct DDSCAPS2 ddsCaps;
	DWORD dwTextureStage;
};

struct IDirectDrawPaletteVtbl {
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer GetCaps;
	HRESULT (* GetEntries)(struct IDirectDrawPalette *, DWORD, DWORD, DWORD, struct D3DRMPALETTEENTRY *);
	pointer Initialize;
	pointer SetEntries;
};

struct tagRECT {
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;
};

struct ImageBMP {
	struct IDirectDrawSurface4 * ddSurface; // IDirectDrawSurface4
	int width;
	int height;
	uint firstColor24;
	uint lastColor24;
	uint firstColorNative;
	uint flags; // 2 is font?
	struct ImageBMP * pool_m_next;
};

struct IDirect3DRMTexture3 {
	struct IDirect3DRMTexture3Vtbl * lpVtbl;
};

struct IDirectDrawSurface4 {
	struct IDirectDrawSurface4Vtbl * lpVtbl;
};

struct Size2I {
	int width;
	int height;
};

struct SurfaceTextureGrid {
	struct Size2I gridSize;
	struct DirectXSurfaceTuple * * gridSurfaces;
};

struct D3DRMPALETTEENTRY {
	byte red; // 0 .. 255
	byte green; // 0 .. 255
	byte blue; // 0 .. 255
	enum D3DRMPALETTEFLAGS flags; // one of D3DRMPALETTEFLAGS
};

struct ObjectiveData {
	void * ObjectiveImage; // bmp
	int ObjectiveImage_width_x; // ???
	int ObjectiveImage_height_y; // ???
	void * ObjectiveAcheivedImage; // bmp
	int ObjectiveAcheivedImage_width_x; // ???
	int ObjectiveAcheivedImage_height_y; // ???
	void * ObjectiveFailedImage; // bmp
	int ObjectiveFailedImage_width_x; // ???
	int ObjectiveFailedImage_height_y; // ???
	void * ObjectiveAcheivedAVI; // ???
	int ObjectiveAcheivedAVI_width_x; // ???
	int ObjectiveAcheivedAVI_height_y; // ???
	undefined4 field_30;
	undefined4 field_34;
	int CrystalObjective; // number of crystals needed if non-zero
	int OreObjective; // number of ore needed if non-zero
	struct Point2I BlockObjective;
	float TimerObjective; // (mult: 25.0, flags, format: "time:HitTimeFailObjective")
	int ConstructionObjective_type;
	int ConstructionObjective_index;
};

struct LevelData {
	char * levelName; // (format: "Levels::level")
	struct LevelSurfaceMap * surfaceMap;
	undefined4 field_8;
	undefined4 field_c;
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

struct DirectXSurfaceTuple {
	struct IDirectDrawSurface4 * surface;
	struct IDirect3DRMTexture3 * texture;
	undefined4 field_8;
};

struct LevelSurfaceMap { // size 0x73d4... dear god.... no...
	struct Size2I smallDimensions; // full map dimensions - 1
	struct Size2I dimensions; // full map dimensions
	float BlockSize;
	float RoughLevel;
	struct Size2F blockDimensions_neg; // smallDimensions * BlockSize * 0.5 (width is negative??)
	float float_20;
	struct ResourceData * resData_24;
	undefined4 field_28;
	undefined4 field_2c;
	undefined4 field_30;
	undefined field_0x34_0x4034[0x4000];
	undefined4 flat_4034[32];
	undefined4 flat_40b4[128];
	ushort table_42b4[1000];
	uint count_4a84;
	undefined field_0x4a88_0x7198[0x2710];
	undefined4 field_7198;
	struct SurfaceMapStruct38 table38_719c[10];
	struct ResourceData * resData_73cc;
	undefined4 field_73d0;
};

struct CFGProperty { // CFG file property node
	char * fileText; // Entire file text data for root CFGProperty only
	char * key; // Property or block key name
	char * value; // Property value or block open brace
	uint depth; // Block-depth of property
	undefined4 field_10;
	struct CFGProperty * next; // Next property in linked list
	struct CFGProperty * previous; // Previous property in linked list
	struct CFGProperty * pool_m_next; // (internal) used for allocation while reading(?)
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
	D3DRMIMAGE * (* GetImage)(struct IDirect3DRMTexture3 *);
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

struct ImageFont {
	struct ImageBMP * bitmap;
	undefined field_0x4_0xbe4[0xbe0];
	undefined4 field_be4;
	undefined field_0xbe8_0xbf0[0x8];
	struct ImageFont * pool_m_next;
};

typedef struct FileStream FileStream, *PFileStream;

typedef enum FileLocation { // Location of a lego File stream (WAD or REAL)
	FILELOC_ERROR=2,
	FILELOC_STD=1,
	FILELOC_WAD=0
} FileLocation;

typedef union FileStreamData FileStreamData, *PFileStreamData;

typedef struct _iobuf _iobuf, *P_iobuf;

typedef struct _iobuf FILE;

typedef struct WADEntryStream WADEntryStream, *PWADEntryStream;

union FileStreamData {
	FILE * std; // Standard file stream
	struct WADEntryStream * wad; // WAD file stream
};

struct FileStream {
	enum FileLocation location;
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

struct WADEntryStream {
	int sharedIndex;
	int position;
	undefined4 field_8;
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

typedef struct DriverMode DriverMode, *PDriverMode;

typedef enum DriverModeFlags {
	DRIVERMODE_ISUSED=1,
	DRIVERMODE_NOGUID_10=16,
	DRIVERMODE_NOGUID_20=32,
	DRIVERMODE_NONE=0
} DriverModeFlags;

struct DriverMode {
	GUID guid;
	char displayName[256]; // "name (description)"
	enum DriverModeFlags flags;
};

typedef struct PTLProperty PTLProperty, *PPTLProperty;

typedef enum MessageType {
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
	MESSAGE__INVALID=4294967295,
	MESSAG_ATTACKBUILDING=37,
	MESSAG_ATTACKBUILDING_COMPLETE=38
} MessageType;

struct PTLProperty { // Property loaded from a level's PTL config file (contains lookup index for actions)
	enum MessageType eventIndex;
	enum MessageType actionIndex;
};

typedef struct InterfaceMenuItem InterfaceMenuItem, *PInterfaceMenuItem;

struct InterfaceMenuItem {
	int * parameters;
	uint numParams;
};

typedef struct Matrix4F Matrix4F, *PMatrix4F;

struct Matrix4F {
	float values[4][4];
};

typedef struct GameFunctions GameFunctions, *PGameFunctions;

struct GameFunctions {
	BOOL (* Init)(void);
	BOOL (* Update)(float);
	void (* Cleanup)(void);
};

typedef struct WADFile WADFile, *PWADFile;

typedef struct WADEntry WADEntry, *PWADEntry;

typedef enum WADEntryFlags {
	WADENTRY_NONE=0,
	WADENTRY_RNC_COMPRESSION=2,
	WADENTRY_UNK_STORE=1
} WADEntryFlags;

struct WADEntry { // WAD file entry metadata contained within LegoWADFile structure
	enum WADEntryFlags flags; // usually 1, 2 for RNC compression
	undefined field_0x1;
	undefined field_0x2;
	undefined field_0x3;
	uint packedSize; // Compressed packed size
	uint origSize; // Original unpacked size (same as packedSize when uncompressed)
	uint offset; // absolute file offset
};

struct WADFile { // LegoRR WAD File information
	undefined4 field_0;
	BOOL isUsed; // 1 if WAD is in-use
	undefined4 field_8;
	undefined4 field_c;
	FILE * file; // file I/O
	char * * absdirs; // source file paths when WAD was built
	char * * reldirs; // relative file paths inside WAD
	struct WADEntry * entries; // file entry metadata
	uint count; // number of file entries
};

typedef struct RenderStateItem RenderStateItem, *PRenderStateItem;

struct RenderStateItem { // The item's render state type is determined by the index in its table
	DWORD value;
	BOOL isUsed;
};

typedef struct DeviceMode DeviceMode, *PDeviceMode;

typedef enum DeviceModeFlags {
	DEVICEMODE_BPP_16=32,
	DEVICEMODE_BPP_24=64,
	DEVICEMODE_BPP_32=128,
	DEVICEMODE_BPP_8=16,
	DEVICEMODE_COLORMODEL_RGB=4096,
	DEVICEMODE_HARDWARE=8192,
	DEVICEMODE_ISUSED=1,
	DEVICEMODE_NONE=0,
	DEVICEMODE_TEXTURESYSTEMMEMORY=32768,
	DEVICEMODE_TEXTUREVIDEOMEMORY=16384
} DeviceModeFlags;

struct DeviceMode {
	GUID guid;
	char displayName[256]; // "name (description)"
	enum DeviceModeFlags flags;
};

typedef struct ScreenMode ScreenMode, *PScreenMode;

typedef enum ScreenModeFlags {
	SCREENMODE_ISUSED=1,
	SCREENMODE_NONE=0
} ScreenModeFlags;

struct ScreenMode {
	int screenWidth;
	int screenHeight;
	int bitDepth;
	char displayName[256]; // "WxH (BPP bit)", "WxH" (windowed)
	enum ScreenModeFlags flags;
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

typedef struct SharedObjectResource SharedObjectResource, *PSharedObjectResource;

struct SharedObjectResource {
	char * resName;
	struct Struct_34 * lwoStruct34;
};

typedef struct ToolTipData ToolTipData, *PToolTipData;

struct ToolTipData {
	float float_0;
	char tooltipText[512];
	undefined field_0x204_0x25c[0x58];
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

typedef struct ColourRGBAF ColourRGBAF, *PColourRGBAF;

struct ColourRGBAF {
	float red;
	float green;
	float blue;
	float alpha;
};

typedef struct ErodeState ErodeState, *PErodeState;

struct ErodeState {
	undefined4 field_0;
	undefined4 field_4;
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

typedef struct SharedTextureResource SharedTextureResource, *PSharedTextureResource;

struct SharedTextureResource {
	char * name;
	struct IDirect3DRMTexture3 * texture;
};

typedef struct SharedFileBuffer SharedFileBuffer, *PSharedFileBuffer;

typedef enum FileBufferFlags {
	FILEBUFFER_ISUSED=1,
	FILEBUFFER_NONE=0
} FileBufferFlags;

struct SharedFileBuffer {
	void * fileData;
	enum FileBufferFlags flags; // 1 = isUsed
};

typedef struct MiscObjectDependencies MiscObjectDependencies, *PMiscObjectDependencies;

struct MiscObjectDependencies {
	undefined4 field_0;
	uint levels_flags[16];
	undefined4 levels_field_44[16];
	undefined4 levels_field_84[16];
};

typedef struct SharedWADEntry SharedWADEntry, *PSharedWADEntry;

struct SharedWADEntry {
	void * fileData;
	BOOL isUsed;
	int wadIndex;
	int entryIndex;
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

typedef struct ResourceManager ResourceManager, *PResourceManager;

struct ResourceManager {
	struct ResourceData * pool_g_TABLE[20]; // PTR_0076bd80
	struct ResourceData * pool_g_NEXT; // PTR_0076bd84
	struct ResourceData * pool_g_ROOT; // PTR_0076bd88
	char * Types_TABLE[9]; // PTR_0076bdd8
	char * Extensions_TABLE[9]; // PTR_0076bdfc
	char * CfgRootName; // PTR_0076be20
	undefined4 DAT_0076be24; // DAT_0076be24
	undefined4 field_a8; // DAT_0076be28
	undefined4 field_ac; // referenced by addr to get last item of g_Textures_TABLE
	undefined4 field_b0; // DAT_0076be30
	struct SharedTextureResource Textures_TABLE[1000]; // PTR_0076be34
	uint Textures_COUNT; // DAT_0076dd74
	pointer soundCallback; // PTR_0076dd78
	void * soundCallback_VALUE; // PTR_0076dd7c
	pointer drawCallback; // PTR_0076dd80
	void * drawCallback_VALUE; // PTR_0076dd84
	char * SharedTextures; // PTR_0076dd88
	uint SceneFogColor; // DAT_0076dd8c
	uint pool_g_COUNT; // DAT_0076dd90
	uint pool_g_INITFLAGS; // DAT_0076dd94
};

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

struct tagBITMAPFILEHEADER {
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
};

struct tagRGBQUAD {
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
};

struct BITMAP_FILE_INFO_STRUCT { // Helper struct to combine both BITMAPFILEHEADER, BITMAPINFOHEADER, and palette data into one field
	BITMAPFILEHEADER hdr;
	BITMAPINFOHEADER bmi;
	RGBQUAD bmiColors[1];
};

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

typedef struct SampleData SampleData, *PSampleData;

typedef HANDLE HGLOBAL;

typedef struct IDirectSoundBuffer IDirectSoundBuffer, *PIDirectSoundBuffer;

typedef enum SampleFlags {
	SAMPLE_ISUSED=1,
	SAMPLE_MULTIPLE=4,
	SAMPLE_NONE=0,
	SAMPLE_STREAMED=8,
	SAMPLE_VOLUME=2
} SampleFlags;

typedef struct IDirectSoundBufferVtbl IDirectSoundBufferVtbl, *PIDirectSoundBufferVtbl;

struct SampleData {
	char filename[260];
	uint length;
	uint avgBytesPerSec;
	uint frequency;
	int volume;
	undefined4 offset;
	HGLOBAL hGlobal_118;
	HGLOBAL hGlobal_11c;
	struct IDirectSoundBuffer * dSoundBuffer1;
	struct IDirectSoundBuffer * dSoundBuffer2;
	struct IDirectSoundBuffer * dSoundBuffer3;
	undefined4 bufferIndex;
	enum SampleFlags flags;
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

struct IDirectSoundBuffer {
	struct IDirectSoundBufferVtbl * lpVtbl;
};

typedef struct SampleProperty SampleProperty, *PSampleProperty;

struct SampleProperty {
	int sampleIndex;
	struct SampleProperty * next;
};

typedef struct AudioPlaybackData AudioPlaybackData, *PAudioPlaybackData;

typedef struct tWAVEFORMATEX tWAVEFORMATEX, *PtWAVEFORMATEX;

typedef struct tWAVEFORMATEX WAVEFORMATEX;

typedef struct HMMIO__ HMMIO__, *PHMMIO__;

typedef struct HMMIO__ * HMMIO;

typedef struct _MMCKINFO _MMCKINFO, *P_MMCKINFO;

typedef struct _MMCKINFO MMCKINFO;

typedef DWORD FOURCC;

struct tWAVEFORMATEX {
	WORD wFormatTag;
	WORD nChannels;
	DWORD nSamplesPerSec;
	DWORD nAvgBytesPerSec;
	WORD nBlockAlign;
	WORD wBitsPerSample;
	WORD cbSize;
};

struct _MMCKINFO {
	FOURCC ckid;
	DWORD cksize;
	FOURCC fccType;
	DWORD dwDataOffset;
	DWORD dwFlags;
};

struct HMMIO__ {
	int unused;
};

struct AudioPlaybackData {
	BOOL isUsed1; // paused/playing/used?
	WAVEFORMATEX * waveFormat; // hGlobal
	HMMIO hMmio;
	MMCKINFO mmckInfo;
	MMCKINFO mmckInfoData;
	uint bufferBytesSize;
	uint totalFrames; // probably
	uint playback_3c;
	uint playback_40;
	uint playback_44; // thought to be totalSamples
	uint playback_48;
	undefined4 field_4c;
	BOOL modeChoice;
	undefined4 field_54;
	BOOL isUsed2; // paused/playing/used?
};

typedef struct NERPMessageSound NERPMessageSound, *PNERPMessageSound;

struct NERPMessageSound {
	char * key;
	int sampleIndex;
};

typedef enum ResourceManagerFlags {
	RESMANAGER_ISINIT=1,
	RESMANAGER_NONE=0,
	RESMANAGER_SOUNDCALLBACK=64
} ResourceManagerFlags;

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

typedef enum TrainedFlags {
	TRAINED_DRIVER=4,
	TRAINED_DYNAMITE=8,
	TRAINED_NONE=0,
	TRAINED_PILOT=1,
	TRAINED_REPAIR=16,
	TRAINED_SAILOR=2,
	TRAINED_SCANNER=32
} TrainedFlags;

typedef enum DebugFlags { // Flags specified by the "-flags #" command line argument (which has to be in decimal...)
	DEBUGFLAG_BLOCKFADEIN=32768,
	DEBUGFLAG_NONE=0
} DebugFlags;

typedef enum AudioFlags {
	AUDIO_SOUNDON=1,
	AUDIO_UNK_2=2,
	AUDIO_UNK_8=8
} AudioFlags;

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

typedef enum ObjInfoFlags {
	OBJINFO_BUBBLEIMAGES=16,
	OBJINFO_HEALTHBAR=2,
	OBJINFO_HEALTHBAR_VERTICAL=8,
	OBJINFO_HUNGERIMAGES=1,
	OBJINFO_NONE=0
} ObjInfoFlags;

typedef struct AdvisorAnimData AdvisorAnimData, *PAdvisorAnimData;

struct AdvisorAnimData {
	struct ResourceData * resData;
	float loopStartTime; // ignored when not looping
	float loopEndTime; // ignored when not looping
};

typedef struct SelectedUnitHotkey SelectedUnitHotkey, *PSelectedUnitHotkey;

struct SelectedUnitHotkey {
	int field_0;
	int field_4;
	BOOL bool_8;
	int field_c;
	int field_10;
};

typedef struct BasicObjectData BasicObjectData, *PBasicObjectData;

struct BasicObjectData {
	int objIndex;
	struct ResourceData * aeResData; // ACT, true
};

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

typedef struct MapFileInfo MapFileInfo, *PMapFileInfo;

struct MapFileInfo {
	char Signature[4]; // "MAP "
	uint fileSize;
	struct Size2I dimensions;
	ushort blocks[1];
};

typedef struct BlockObject BlockObject, *PBlockObject;

struct BlockObject {
	struct LiveObject * attachedObject;
	struct Point2I position;
	undefined4 field_c;
	struct BlockObject * pool_m_next;
};

typedef struct Struct_b8__00558080 Struct_b8__00558080, *PStruct_b8__00558080;

struct Struct_b8__00558080 {
	undefined field_0x0_0xb8[0xb8];
};

typedef struct PairStruct_428 PairStruct_428, *PPairStruct_428;

struct PairStruct_428 {
	struct Struct_428 * first;
	struct Struct_428 * second;
};

typedef struct Struct_8__00558bc4 Struct_8__00558bc4, *PStruct_8__00558bc4;

struct Struct_8__00558bc4 {
	struct LiveObject * object_0;
	float float_4;
};

typedef struct ResourceAppData ResourceAppData, *PResourceAppData;

typedef struct ActFrameResource ActFrameResource, *PActFrameResource;

typedef struct SoundResource SoundResource, *PSoundResource;

typedef struct IDirect3DRMAnimationSet2 IDirect3DRMAnimationSet2, *PIDirect3DRMAnimationSet2;

typedef struct IDirectSound3DBuffer IDirectSound3DBuffer, *PIDirectSound3DBuffer;

typedef struct IDirect3DRMAnimationSet2Vtbl IDirect3DRMAnimationSet2Vtbl, *PIDirect3DRMAnimationSet2Vtbl;

typedef struct IDirectSound3DBufferVtbl IDirectSound3DBufferVtbl, *PIDirectSound3DBufferVtbl;

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

struct SoundResource {
	struct IDirectSound3DBuffer * sound3dBuffer;
	undefined4 field_4;
	undefined4 field_8;
	undefined4 field_c;
	struct SoundResource * previous;
};

struct ResourceAppData {
	struct ResourceData * resData;
	char * filename;
	char * frameName;
	undefined4 field_c;
	float float_10;
	float float_14;
	char * sampleName;
	struct ActFrameResource * actFrameRes;
	undefined4 field_20;
	struct SoundResource * soundRes;
};

struct ActFrameResource {
	struct ActFrameResource * previous;
	void * lwsStruct38; // LWS struct
	struct IDirect3DRMAnimationSet2 * animSet; // (not LWS)
	BOOL isLWSFile;
	struct IDirect3DRMFrame3 * rootFrame; // (not LWS)
	struct IDirect3DRMFrame3 * * framesTable; // (not LWS) table of COM objects, length is count_18
	uint framesCount; // (not LWS)
	undefined4 field_1c;
};

struct IDirect3DRMAnimationSet2 {
	struct IDirect3DRMAnimationSet2Vtbl * lpVtbl;
};

struct IDirectSound3DBuffer {
	struct IDirectSound3DBufferVtbl * lpVtbl;
};

typedef struct MessageAction MessageAction, *PMessageAction;

struct MessageAction {
	enum MessageType event;
	struct LiveObject * object_4;
	undefined4 field_8;
	undefined4 field_c;
	undefined4 field_10;
};

typedef struct ProMeshData ProMeshData, *PProMeshData;

struct ProMeshData {
	struct ResourceData * promesh_a;
	struct ResourceData * promesh_b;
	undefined4 table_a[100];
	undefined4 table_b[100];
	float BlockSize;
	undefined4 field_32c;
	undefined field_0x330_0x33c[0xc];
	struct SurfaceTextureGrid * surfTextGrid;
};

typedef struct MiscObjectData MiscObjectData, *PMiscObjectData;

struct MiscObjectData {
	undefined field_0x0_0x30[0x30];
	struct ResourceData * resData; // LWS,true | LWO,true
	undefined field_0x34_0x38[0x4];
};

typedef struct LiveObjectInfo LiveObjectInfo, *PLiveObjectInfo;

struct LiveObjectInfo {
	struct LiveObject * liveObj;
	BOOL intbool_4;
	struct Point2F point_8;
	struct Vector3F vector_10;
};

typedef struct Sound3DInstance Sound3DInstance, *PSound3DInstance;

struct Sound3DInstance {
	int sampleIndex;
	struct IDirect3DRMFrame3 * frame;
	struct Vector3F position;
	uint flags;
};

typedef struct LevelIdentifier LevelIdentifier, *PLevelIdentifier;

struct LevelIdentifier {
	undefined4 field_0;
	undefined4 field_4;
	undefined4 field_8;
	undefined4 field_c;
	undefined4 field_10;
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

typedef enum MenuItemType {
	MENUITEM_CYCLE=0,
	MENUITEM_NEXT=5,
	MENUITEM_REALSLIDER=4,
	MENUITEM_SLIDER=3,
	MENUITEM_TEXTINPUT=2,
	MENUITEM_TRIGGER=1,
	MENUITEM__INVALID=4294967295
} MenuItemType;

typedef enum LegoRRResources {
	LEGORR_MAIN_ICON=1,
	LEGORR_MAIN_ICONGROUP=113,
	LEGORR_MODESELECTION_DIALOG=101
} LegoRRResources;

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
	ADVISOR__INVALID=4294967295
} AdvisorType;

typedef enum CLGenDialogControls {
	CLGEN_ID_CANCEL=2,
	CLGEN_ID_OK=1,
	CLGEN_ID_SELECT_DROPDOWNLIST=1001,
	CLGEN_ID_SELECT_LABEL=1006
} CLGenDialogControls;

typedef enum RegistryType {
	REGISTRY_NUMBER=1,
	REGISTRY_STRING=0
} RegistryType;

typedef enum PolyMode {
	POLY_FP=3,
	POLY_HIGH=2,
	POLY_LOW=0,
	POLY_MEDIUM=1
} PolyMode;

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

typedef enum AdvisorAnim {
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
	ADVISORANIM__INVALID=4294967295
} AdvisorAnim;

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

typedef enum ProgrammerMode { // Programmer mode enum
	PROGRAMMER_MODE_1=1,
	PROGRAMMER_MODE_10=10,
	PROGRAMMER_MODE_11=11,
	PROGRAMMER_MODE_2=2,
	PROGRAMMER_MODE_3=3,
	PROGRAMMER_OFF=0
} ProgrammerMode;

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
	ACTIVITY_DESPOSITE=29,
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
	TEXT__INVALID=4294967295
} TextType;

typedef struct IDirectSound IDirectSound, *PIDirectSound;

typedef struct IDirectSoundVtbl IDirectSoundVtbl, *PIDirectSoundVtbl;

struct IDirectSound {
	struct IDirectSoundVtbl * lpVtbl;
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

typedef struct IDirectInputDeviceA IDirectInputDeviceA, *PIDirectInputDeviceA;

typedef struct IDirectInputDeviceAVtbl IDirectInputDeviceAVtbl, *PIDirectInputDeviceAVtbl;

typedef struct DIDEVCAPS DIDEVCAPS, *PDIDEVCAPS;

typedef struct DIDEVICEOBJECTINSTANCEA DIDEVICEOBJECTINSTANCEA, *PDIDEVICEOBJECTINSTANCEA;

typedef GUID * LPGUID;

typedef struct DIPROPHEADER DIPROPHEADER, *PDIPROPHEADER;

typedef struct DIDEVICEOBJECTDATA DIDEVICEOBJECTDATA, *PDIDEVICEOBJECTDATA;

typedef struct DIDATAFORMAT DIDATAFORMAT, *PDIDATAFORMAT;

typedef struct HWND__ HWND__, *PHWND__;

typedef struct HWND__ * HWND;

typedef struct DIDEVICEINSTANCEA DIDEVICEINSTANCEA, *PDIDEVICEINSTANCEA;

typedef struct HINSTANCE__ HINSTANCE__, *PHINSTANCE__;

typedef struct HINSTANCE__ * HINSTANCE;

typedef uint UINT_PTR;

typedef struct DIOBJECTDATAFORMAT DIOBJECTDATAFORMAT, *PDIOBJECTDATAFORMAT;

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

struct DIPROPHEADER {
	DWORD dwSize;
	DWORD dwHeaderSize;
	DWORD dwObj;
	DWORD dwHow;
};

struct IDirectInputDeviceA {
	struct IDirectInputDeviceAVtbl * lpVtbl;
};

struct DIOBJECTDATAFORMAT {
	LPGUID pguid;
	DWORD dwOfs;
	DWORD dwType;
	DWORD dwFlags;
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

struct HWND__ {
	int unused;
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

typedef struct IDirectDrawClipper IDirectDrawClipper, *PIDirectDrawClipper;

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

struct IDirectDrawClipper {
	struct IDirectDrawClipperVtbl * lpVtbl;
};

typedef struct IDirect3D3 IDirect3D3, *PIDirect3D3;

struct IDirect3D3 {
	undefined4 field_0x0;
};

typedef struct IDirect3DRMFrameArray IDirect3DRMFrameArray, *PIDirect3DRMFrameArray;

typedef struct IDirect3DRMFrameArrayVtbl IDirect3DRMFrameArrayVtbl, *PIDirect3DRMFrameArrayVtbl;

struct IDirect3DRMFrameArray {
	struct IDirect3DRMFrameArrayVtbl * lpVtbl;
};

struct IDirect3DRMFrameArrayVtbl { // Subclass of IDirect3DRMArrayVtbl
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	DWORD (* GetSize)(struct IDirect3DRMFrameArray *);
	HRESULT (* GetElement)(struct IDirect3DRMFrameArray *, struct IUnknown * *);
};

typedef struct IDirect3DTexture IDirect3DTexture, *PIDirect3DTexture;

typedef struct IDirect3DTextureVtbl IDirect3DTextureVtbl, *PIDirect3DTextureVtbl;

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

struct IDirect3DTexture {
	struct IDirect3DTextureVtbl * lpVtbl;
};

typedef struct IDirect3DRM3 IDirect3DRM3, *PIDirect3DRM3;

typedef struct IDirect3DRM3Vtbl IDirect3DRM3Vtbl, *PIDirect3DRM3Vtbl;

typedef GUID CLSID;

struct IDirect3DRM3Vtbl {
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	HRESULT (* CreateObject)(struct IUnknown *, CLSID *, struct IUnknown *);
	HRESULT (* CreateFrame)(struct IDirect3DRM3 *, struct IDirect3DRMFrame3 *, struct IDirect3DRMFrame3 * *);
	pointer CreateMesh;
	pointer CreateMeshBuilder;
	pointer CreateFace;
	pointer CreateAnimation;
	pointer CreateAnimationSet;
	pointer CreateTexture;
	pointer CreateLight;
	pointer CreateLightRGB;
	pointer CreateMaterial;
	pointer CreateDevice;
	pointer CreateDeviceFromSurface;
	pointer CreateDeviceFromD3D;
	pointer CreateDeviceFromClipper;
	HRESULT (* CreateTextureFromSurface)(struct IDirect3DRM3 *, struct IDirectDrawSurface4 *, struct IDirect3DRMTexture3 * *);
	pointer CreateShadow;
	pointer CreateViewport;
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

typedef struct IDirect3DDevice3 IDirect3DDevice3, *PIDirect3DDevice3;

typedef struct IDirect3DDevice3Vtbl IDirect3DDevice3Vtbl, *PIDirect3DDevice3Vtbl;

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

struct IDirect3DDevice3 {
	struct IDirect3DDevice3Vtbl * lpVtbl;
};

typedef struct IDirectDraw4 IDirectDraw4, *PIDirectDraw4;

typedef struct IDirectDraw4Vtbl IDirectDraw4Vtbl, *PIDirectDraw4Vtbl;

struct IDirectDraw4Vtbl {
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer Compact;
	pointer CreateClipper;
	HRESULT (* CreatePalette)(struct IDirectDraw4 *, DWORD, struct D3DRMPALETTEENTRY *, struct IDirectDrawPalette * *, struct IUnknown *);
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
	pointer GetAvailableVidMem;
	pointer GetSurfaceFromDC;
	pointer RestoreAllSurfaces;
	pointer TestCooperativeLevel;
	pointer GetDeviceIdentifier;
};

struct IDirectDraw4 {
	struct IDirectDraw4Vtbl * lpVtbl;
};

typedef struct IDirect3DRMTexture IDirect3DRMTexture, *PIDirect3DRMTexture;

typedef struct IDirect3DRMTextureVtbl IDirect3DRMTextureVtbl, *PIDirect3DRMTextureVtbl;

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
	D3DRMIMAGE * (* GetImage)(struct IDirect3DRMTexture3 *);
	pointer GetShades;
	pointer GetColors;
	pointer GetDecalScale;
	pointer GetDecalTransparency;
	pointer GetDecalTransparentColor;
};

struct IDirect3DRMTexture {
	struct IDirect3DRMTextureVtbl * lpVtbl;
};

typedef struct IDirect3DTexture2 IDirect3DTexture2, *PIDirect3DTexture2;

typedef struct IDirect3DTexture2Vtbl IDirect3DTexture2Vtbl, *PIDirect3DTexture2Vtbl;

struct IDirect3DTexture2 {
	struct IDirect3DTexture2Vtbl * lpVtbl;
};

struct IDirect3DTexture2Vtbl {
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer GetHandle;
	pointer PaletteChanged;
	pointer Load;
};

typedef struct IDirectInputA IDirectInputA, *PIDirectInputA;

typedef struct IDirectInputAVtbl IDirectInputAVtbl, *PIDirectInputAVtbl;

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

typedef struct IDirect3DRMArray IDirect3DRMArray, *PIDirect3DRMArray;

typedef struct IDirect3DRMArrayVtbl IDirect3DRMArrayVtbl, *PIDirect3DRMArrayVtbl;

struct IDirect3DRMArrayVtbl { // Subclass of IDirect3DRMArrayVtbl
	HRESULT (* QueryInterface)(struct IUnknown *, IID *, LPVOID *);
	ULONG (* AddRef)(struct IUnknown *);
	ULONG (* Release)(struct IUnknown *);
	pointer GetSize;
};

struct IDirect3DRMArray {
	struct IDirect3DRMArrayVtbl * lpVtbl;
};

typedef struct IDirect3DRMDevice3 IDirect3DRMDevice3, *PIDirect3DRMDevice3;

typedef struct IDirect3DRMDevice3Vtbl IDirect3DRMDevice3Vtbl, *PIDirect3DRMDevice3Vtbl;

struct IDirect3DRMDevice3 {
	struct IDirect3DRMDevice3Vtbl * lpVtbl;
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

typedef struct IDirectDrawSurface IDirectDrawSurface, *PIDirectDrawSurface;

typedef struct IDirectDrawSurfaceVtbl IDirectDrawSurfaceVtbl, *PIDirectDrawSurfaceVtbl;

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

struct IDirectDrawSurface {
	struct IDirectDrawSurfaceVtbl * lpVtbl;
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
	D3DRMIMAGE * (* GetImage)(struct IDirect3DRMTexture3 *);
	pointer GetShades;
	pointer GetColors;
	pointer GetDecalScale;
	pointer GetDecalTransparency;
	pointer GetDecalTransparentColor;
	pointer InitFromImage;
	pointer InitFromResource2;
	pointer GenerateMIPMap;
};

typedef struct IDirectSound3DListener IDirectSound3DListener, *PIDirectSound3DListener;

typedef struct IDirectSound3DListenerVtbl IDirectSound3DListenerVtbl, *PIDirectSound3DListenerVtbl;

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

struct IDirectSound3DListener {
	struct IDirectSound3DListenerVtbl * lpVtbl;
};

typedef struct IDirect3DRMMeshBuilder3 IDirect3DRMMeshBuilder3, *PIDirect3DRMMeshBuilder3;

typedef struct IDirect3DRMMeshBuilder3Vtbl IDirect3DRMMeshBuilder3Vtbl, *PIDirect3DRMMeshBuilder3Vtbl;

struct IDirect3DRMMeshBuilder3 {
	struct IDirect3DRMMeshBuilder3Vtbl * lpVtbl;
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

typedef struct D3DDEVICEDESC_V1 D3DDEVICEDESC_V1, *PD3DDEVICEDESC_V1;

typedef struct D3DTRANSFORMCAPS D3DTRANSFORMCAPS, *PD3DTRANSFORMCAPS;

typedef struct D3DLIGHTINGCAPS D3DLIGHTINGCAPS, *PD3DLIGHTINGCAPS;

typedef struct D3DPRIMCAPS D3DPRIMCAPS, *PD3DPRIMCAPS;

struct D3DTRANSFORMCAPS {
	DWORD dwSize;
	DWORD dwCaps;
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

struct D3DLIGHTINGCAPS {
	DWORD dwSize;
	DWORD dwCaps; // Lighting caps
	DWORD dwLightingModel; // Lighting model - RGB or mono
	DWORD dwNumLights; // Number of lights that can be handled
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

typedef struct DSBUFFERDESC DSBUFFERDESC, *PDSBUFFERDESC;

struct DSBUFFERDESC {
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwBufferBytes;
	DWORD dwReserved;
	WAVEFORMATEX * lpwfxFormat;
};

typedef enum D3DRMCombineType { // TD3DRMCombineType
	D3DRMCOMBINE_AFTER=2,
	D3DRMCOMBINE_BEFORE=1,
	D3DRMCOMBINE_REPLACE=0
} D3DRMCombineType;

typedef enum D3DRMSortMode {
	D3DRMSORT_BACKTOFRONT=3,
	D3DRMSORT_FROMPARENT=0,
	D3DRMSORT_FRONTTOBACK=2,
	D3DRMSORT_NONE=1
} D3DRMSortMode;

typedef enum D3DRMFrameConstraint {
	D3DRMCONSTRAIN_X=2,
	D3DRMCONSTRAIN_Y=1,
	D3DRMCONSTRAIN_Z=0
} D3DRMFrameConstraint;

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

typedef enum D3DRMSceneFogMethod {
	D3DRMFOGMETHOD_ANY=4,
	D3DRMFOGMETHOD_TABLE=2,
	D3DRMFOGMETHOD_VERTEX=1,
	D3DRMFOGMETHOD__NONE=0
} D3DRMSceneFogMethod;

typedef enum D3DRMUserVisualReason {
	D3DRMUSERVISUAL_CANSEE=0,
	D3DRMUSERVISUAL_RENDER=1
} D3DRMUserVisualReason;

typedef enum D3DRMLightType {
	D3DRMLIGHT_AMBIENT=0,
	D3DRMLIGHT_DIRECTIONAL=3,
	D3DRMLIGHT_PARALLELPOINT=4,
	D3DRMLIGHT_POINT=1,
	D3DRMLIGHT_SPOT=2
} D3DRMLightType;

typedef enum D3DRMRenderQuality {
	D3DRMRENDER_FLAT=136,
	D3DRMRENDER_GOURAUD=137,
	D3DRMRENDER_PHONG=138,
	D3DRMRENDER_UNLITFLAT=128,
	D3DRMRENDER_WIREFRAME=64
} D3DRMRenderQuality;

typedef struct tagMSG tagMSG, *PtagMSG;

typedef struct tagMSG MSG;

typedef uint UINT;

typedef UINT_PTR WPARAM;

typedef long LONG_PTR;

typedef LONG_PTR LPARAM;

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

typedef DWORD MCIERROR;

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

typedef uint size_t;

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

typedef struct tagRECT RECT;

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

typedef WCHAR * LPWSTR;

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

typedef HINSTANCE HMODULE;

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

typedef struct HDC__ HDC__, *PHDC__;

struct HDC__ {
	int unused;
};

typedef struct HMENU__ HMENU__, *PHMENU__;

typedef struct HMENU__ * HMENU;

struct HMENU__ {
	int unused;
};

typedef struct _FILETIME * LPFILETIME;

typedef struct HDC__ * HDC;

typedef HKEY * PHKEY;

typedef WORD * LPWORD;

typedef void * LPCVOID;

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


