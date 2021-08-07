#pragma once

#include "../Common.h"

typedef unsigned char       undefined;
typedef unsigned char       undefined1;
typedef unsigned short      undefined2;
typedef unsigned int        undefined4;
typedef unsigned long long  undefined8;

//typedef unsigned char    bool;
//typedef unsigned short    ushort;
//typedef short    wchar_t;
//typedef unsigned short    word;
//typedef struct LiveObject LiveObject, *PLiveObject;

namespace lego {
namespace game {

typedef BOOL(__cdecl* GameInitFunction)(void);
typedef BOOL(__cdecl* GameUpdateFunction)(float elapsed); // float argument is elapsed game time units since last update
typedef void(__cdecl* GameCleanupFunction)(void);

#pragma pack(push, 4)
struct GameFunctions
{
	/*0,4*/ GameInitFunction Init;
	/*4,4*/ GameUpdateFunction Update;
	/*8,4*/ GameCleanupFunction Cleanup;
	/*c*/
};
#pragma pack(pop)

enum class ObjectType : int
{
	TVCamera          = -1, // not used in-game, may only be for loading in .ol files
	None              = 0,
	Vehicle           = 1, // [table]
	MiniFigure        = 2, // [table]
	RockMonster       = 3, // [table]
	Building          = 4, // [table]
	Boulder           = 5,
	PowerCrystal      = 6,
	Ore               = 7, // [normal, processed]
	Dynamite          = 8,
	Barrier           = 9,
    Upgrade           = 10, // [table] upgrade part attached to live vehicles, these are defined in a Vehicle's .ae file
	ElectricFence     = 11,
	SpiderWeb         = 12,
	SonicBlaster      = 13, // sonic blaster when carried and used like Dynamite (which may only be possible with debug keys)
	ElectricFenceStud = 14, // yellow beacon between electric fence connections, only present when distance is 2 blocks
	Path              = 15, // (never seen as a live object)
	PusherShot        = 16,
	FreezerShot       = 17,
	IceCube           = 18, // ice block created by frozen creatures
	LaserShot         = 19, // this does not include "instant" lasers, like from vehicles, and the mining laser
};

enum class ToolType : int
{
    Invalid      = -1,
    Drill        = 0,
    Shovel       = 1, // "Spade"
    Hammer       = 2,
    Spanner      = 3,
    LaserBeam    = 4,
    PusherBeam   = 5,
    SonicBlaster = 6,
    FreezerBeam  = 7,
};

// Other name parts: "<ResourceName>:NOTEXTURE"
enum class ResourceType : int
{
    Invalid = -1,

    Null = 0, // "NULL"  (ext: "")
    Mesh = 1, // "MESH"  (ext: "x")
    Frame = 2, // "FRAME" (ext: "x")
    Anim = 3, // "ANIM"  (ext: "x")
    Act = 4, // "ACT"   (ext: "ae") (loads "ae"-extension CFG file : g_FILEEXT_AE)
    empty = 5, // NULL    (ext: "")   (explicit)
    unassigned = 6, // NULL    (ext: NULL) (implicit)
    Lws = 7, // "LWS"   (ext: NULL)
    Lwo = 8, // "LWO"   (ext: NULL)
};

enum ObjectStatsFlags1 : unsigned int
{
	STATS1_NONE                   = 0,

	STATS1_SINGLEWIDTHDIG         = 0x1, // (leveled)
	STATS1_PROCESSORE             = 0x2,
	STATS1_PROCESSCRYSTAL         = 0x4,
	STATS1_STOREOBJECTS           = 0x8,

	STATS1_SMALLTELEPORTER        = 0x10,
	STATS1_BIGTELEPORTER          = 0x20,
	STATS1_WATERTELEPORTER        = 0x40,
	STATS1_COLLRADIUS             = 0x80,

	STATS1_COLLBOX                = 0x100, // (only with not CollRadius)
	STATS1_CAUSESLIP              = 0x200,
	STATS1_RANDOMMOVE             = 0x400,
	STATS1_CANSCARE               = 0x800,

	STATS1_RANDOMENTERWALL        = 0x1000,
	STATS1_SCAREDBYPLAYER         = 0x2000,
	STATS1_SNAXULIKE              = 0x4000,
	STATS1_GRABMINIFIGURE         = 0x8000,

	STATS1_CANCLEARRUBBLE         = 0x10000,
	STATS1_CANBEDRIVEN            = 0x20000,
	STATS1_CANSCARESCORPION       = 0x40000,
	STATS1_CANSTEAL               = 0x80000,

	STATS1_TOOLSTORE              = 0x100000,
	STATS1_FLOCKS                 = 0x200000,
	STATS1_FLOCKS_DEBUG           = 0x400000,
	STATS1_FLOCKS_SMOOTH          = 0x800000,

	STATS1_CROSSWATER             = 0x1000000,
	STATS1_CROSSLAND              = 0x2000000,
	STATS1_FLOCKS_ONGROUND        = 0x4000000,
	STATS1_FLOCKS_QUICKDESTROY    = 0x8000000,

	STATS1_FLOCKS_ANIMATEBYPITCH  = 0x10000000,
	STATS1_ROUTEAVOIDANCE         = 0x20000000,
	STATS1_BUMPDAMAGE             = 0x40000000,
	STATS1_MANTELEPORTER          = 0x80000000,
};
DEFINE_ENUM_FLAG_OPERATORS(ObjectStatsFlags1)

enum ObjectStatsFlags2 : unsigned int
{
	STATS2_NONE                   = 0,

	STATS2_SCAREDBYBIGBANGS       = 0x1,
	STATS2_UPGRADEBUILDING        = 0x2,
	STATS2_TRAINPILOT             = 0x4, // (leveled)
	STATS2_TRAINSAILOR            = 0x8, // (leveled)

	STATS2_TRAINDRIVER            = 0x10, // (leveled)
	STATS2_TRAINDYNAMITE          = 0x20, // (leveled)
	STATS2_TRAINREPAIR            = 0x40, // (leveled)
	STATS2_TRAINSCANNER           = 0x80, // (leveled)

	STATS2_TRACKER                = 0x100, // (has mounted laser?)
	STATS2_GENERATEPOWER          = 0x200, // (not a stand-alone flag, always combined with SelfPowered)
	STATS2_SELFPOWERED            = 0x400,
	STATS2_POWERBUILDING          = 0x600,
	STATS2_USEBIGTELEPORTER       = 0x800,

	STATS2_USESMALLTELEPORTER     = 0x1000,
	STATS2_USEWATERTELEPORTER     = 0x2000,
	STATS2_ATTACKPATHS            = 0x4000,
	STATS2_SPLITONZEROHEALTH      = 0x8000,

	STATS2_CANBEHITBYFENCE        = 0x10000,
	STATS2_CANDOUBLESELECT        = 0x20000,
	STATS2_CANBESHOTAT            = 0x40000,
	STATS2_DRAINPOWER             = 0x80000,

	STATS2_USEHOLES               = 0x100000,
	STATS2_CROSSLAVA              = 0x200000,
	STATS2_USELEGOMANTELEPORTER   = 0x400000,
	STATS2_DAMAGECAUSESCALLTOARMS = 0x800000,

	STATS2_CANFREEZE              = 0x1000000,
	STATS2_CANLASER               = 0x2000000,
	STATS2_CANPUSH                = 0x4000000,
	STATS2_DONTSHOWDAMAGE         = 0x8000000, // (don't show RPG damage number effect)

	STATS2_REMOVEREINFORCEMENT    = 0x10000000,
	STATS2_DONTSHOWONRADAR        = 0x20000000,
	STATS2_INVISIBLEDRIVER        = 0x40000000,
	STATS2_UNSELECTABLE           = 0x80000000,
};
DEFINE_ENUM_FLAG_OPERATORS(ObjectStatsFlags2)

enum ObjectStatsFlags3 : unsigned int
{
	STATS3_NONE                   = 0,

	STATS3_CARRYVEHICLES          = 0x1,
	STATS3_VEHICLECANBECARRIED    = 0x2,
	STATS3_CANSTRAFE              = 0x4,
	STATS3_CLASSASLARGE           = 0x8,

	STATS3_GETOUTATLAND           = 0x10,
	STATS3_GETINATLAND            = 0x20,
	STATS3_TAKECARRYINGDRIVERS    = 0x40,
	STATS3_SHOWHEALTHBAR          = 0x80,

	STATS3_NEEDSPILOT             = 0x100, // NEVER SEEN
	STATS3_ENTERTOOLSTORE         = 0x200,
	//STATS3_UNK_400                = 0x400,
	//STATS3_UNK_800                = 0x800,

	//STATS3_UNK_1000               = 0x1000,
	//STATS3_UNK_2000               = 0x2000,
	//STATS3_UNK_4000               = 0x4000,
	//STATS3_UNK_8000               = 0x8000,

	//STATS3_UNK_10000              = 0x10000,
	//STATS3_UNK_20000              = 0x20000,
	//STATS3_UNK_40000              = 0x40000,
	//STATS3_UNK_80000              = 0x80000,

	//STATS3_UNK_100000             = 0x100000,
	//STATS3_UNK_200000             = 0x200000,
	//STATS3_UNK_400000             = 0x400000,
	//STATS3_UNK_800000             = 0x800000,

	//STATS3_UNK_1000000            = 0x1000000,
	//STATS3_UNK_2000000            = 0x2000000,
	//STATS3_UNK_4000000            = 0x4000000,
	//STATS3_UNK_8000000            = 0x8000000,

	//STATS3_UNK_10000000           = 0x10000000,
	//STATS3_UNK_20000000           = 0x20000000,
	//STATS3_UNK_40000000           = 0x40000000,
	//STATS3_UNK_80000000           = 0x80000000,
};
DEFINE_ENUM_FLAG_OPERATORS(ObjectStatsFlags3)


struct ObjectStats
{
    undefined4 field_0;
    undefined4 field_4;
    undefined4 field_8;
    undefined4 field_c;
    undefined4 field_10;
    undefined4 field_14;
    undefined4 field_18;
    undefined4 field_1c;
    float RouteSpeed; /* (leveled) */
    float DrillTimes[18]; /* (leveled, table of surface type times) */
    float CollRadius; /* (effect: flags1 | 0x80) */
    float AlertRadius;
    float CollHeight;
    float PickSphere;
    float TrackDist;
    float HealthDecayRate;
    float EnergyDecayRate;
    float RepairValue; /* (leveled) */
    float RestPercent;
    float CarryMinHealth;
    float StampRadius;
    float AttackRadius;
    float WakeRadius; /* (default: 20.0) */
    struct Size2F CollBox; /* (requires: invalid/no CollRadius, effect: flag 0x100, CollRadius = min(w,h) * 0.5) */
    int BuildingBase; /* (from: FUN_00408bb0, invalid: -1, either ptr or basenumber) */
    int SurveyRadius; /* (leveled) */
    int CostOre;
    int CostCrystal;
    int CostRefinedOre;
    int CrystalDrain; /* (leveled) */
    int DrillSound; /* (from: FUN_00464f30, invalid: 2 "SFX_Drill") */
    int DrillFadeSound; /* (from: FUN_00464f30, invalid: 3 "SFX_DrillFade") */
    int EngineSound; /* (from: FUN_00464f30, invalid: 0 "SFX_Bodge") */
    int NumOfToolsCanCarry; /* (leveled) */
    int WaterEntrances;
    float RubbleCoef; /* (default: 1.0) */
    float PathCoef; /* (default: 1.0) */
    float OxygenCoef; /* (negative consumes oxygen) */
    int Capacity;
    float AwarenessRange; /* (default: 0.0) */
    float PainThreshold; /* (default: 0.0) */
    int MaxCarry; /* (leveled) */
    int CarryStart; /* (leveled) */
    float UpgradeTime; /* (leveled, mult: 25.0) */
    float FunctionCoef; /* (leveled) */
    int UpgradeCostOre; /* Carry:Scan:Speed:Drill (requires all 4) */
    int UpgradeCostStuds; /* Carry:Scan:Speed:Drill (requires all 4) */
    undefined4 field_104;
    undefined4 field_108;
    float FreezerTime; /* (default: 0.0) */
    float FreezerDamage; /* (default: 0.0) */
    float PusherDist; /* (default: 0.0) */
    float PusherDamage; /* (default: 0.0) */
    float LaserDamage; /* (default: 0.0) */
    float Flocks_Turn; /* (default: 0.06) */
    float Flocks_Speed; /* (default: 2.0) */
    float Flocks_Tightness; /* (default: 2.0) */
    float Flocks_GoalUpdate; /* (default: 2.0) */
    float Flocks_Height; /* (default: 30.0) */
    float Flocks_Randomness; /* (default: 2.0) */
    float Flocks_AttackTime; /* (default: 300.0) */
    int Flocks_Size; /* (default: 5) */
    float RandomMoveTime; /* (default: 200.0) */
    ObjectStatsFlags1 flags1;
    ObjectStatsFlags2 flags2;
    ObjectStatsFlags3 flags3;
};

struct LiveObject;

struct ResourceData
{
    void* frame1; //IDirect3DRMFrame3* frame1;
    void* frame2; //IDirect3DRMFrame3* frame2;
    void* frame3; //IDirect3DRMFrame3* frame3;
    void* struct10_c;
    ResourceType resType;
    unsigned int flags_14;
    undefined4 field_18;
    undefined4 field_1c;
    LiveObject* object_20;
    undefined4 field_24;
    ResourceData* pool_m_next;
};

struct UpgradeData;

struct ObjectUpgradePartData
{
    unsigned int level;
    int NullInstance;
    char* NullObjectName;
    char* WeaponName;
    UpgradeData* upgradeData;
};

struct ObjectUpgradesData
{
    ObjectUpgradePartData* parts; /* always ObjectUpgradePartData[200] */
    unsigned int count;
    undefined4 field_8;
    unsigned int levelsMask; /* [carry][scan][speed][drill] */
};


struct BuildingData
{
    int objIndex;
    ResourceData* aeResData; /* ACT, true */
    char* CarryNullName;
    char* CameraNullName;
    char* DepositNullName;
    char* EntranceNullName;
    char* ToolNullName;
    char* FireNullName; /* "fire laser" */
    char* yPivot;
    char* xPivot;
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
    int CarryNullFrames;
    int CameraNullFrames;
    int ToolNullFrames;
    ResourceData* PowerLevelScene; /* LWS, true */
    undefined field_0x80;
    undefined field_0x81;
    undefined field_0x82;
    undefined field_0x83;
    Point2I* shapePoints; /* Point2I[10] */
    unsigned int shapeCount;
    ObjectUpgradesData upgrades;
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
    unsigned int count_144;
    unsigned int flags;
};

struct VehicleData
{
    int objIndex;
    char* WheelNullName;
    ResourceData* aeResData1;
    ResourceData* aeResData2; /* Optional second ae file (seen for Grannit Grinder legs) */
    ResourceData* WheelMeshes[6]; /* LWO, false */
    undefined4 field_0x28[6];
    BOOL hasWheelNull;
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
    char* DrillNullName;
    char* DepositNullName;
    char* FireNullName; /* "fire laser" */
    char* DriverNullName;
    char* yPivot;
    char* xPivot;
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
    BOOL3 CameraFlipDir;
    char* CarryNullName;
    char* CameraNullName;
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
    int CarryNullFrames;
    int CameraNullFrames;
    ObjectUpgradesData upgrades;
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
    void* subdata_1e0;
    void* subdata_1e4;
    unsigned int flags; /* HoldMissing TRUE -> 0x8 */
};

struct CreatureData;
struct AITaskData;

struct LiveObject
{
    ObjectType objType;
    int objIndex;
    char* customName; /* max size is 11 (NOT null-terminated) */
    VehicleData* vehicle;
    CreatureData* miniFigure;
    CreatureData* rockMonster;
    BuildingData* building;
    ResourceData* other;
    UpgradeData* upgrade;
    void* routeptr_24; /* Unknown pointer, likely in large allocated table */
    int routingBlocksTotal; /* total blocks to travel for current route */
    int routingBlocksCurrent; /* number of blocks traveled (up to routingBlocksTotal) */
    int value_30; /* Usually 50 (0x32) */
    float floats_34[100];
    float floats_1c4[50];
    Vector3F vector_28c;
    Point2F point_298;
    Vector3F vector_2a0;
    Vector3F faceDirection; /* 1.0 to -1.0 directions that determine rotation with atan2 */
    float float_2b8;
    undefined4 field_2bc;
    undefined4 field_2c0;
    undefined4 field_2c4;
    undefined4 field_2c8;
    undefined4 field_2cc;
    undefined4 field_2d0;
    float float_2d4;
    BOOL unkbool_2d8;
    void* ptr_2dc;
    int index_2e0;
    undefined4 field_2e4;
    const char* aitaskName1;
    const char* aitaskName2;
    AITaskData* aitask_2f0;
    Point2F point_2f4; /* (assigned -1.0f) */
    LiveObject* object_2fc;
    undefined4 field_300;
    LiveObject* carryingThisObject;
    LiveObject* carriedObjects[7];
    unsigned int numCarriedObjects;
    unsigned int field_328;
    undefined4 field_32c;
    unsigned int objLevel;
    const ObjectStats* stats;
    float float_338;
    float float_33c;
    float health; /* (assigned -1.0f) */
    float energy; /* (assigned -1.0f) */
    undefined4 field_348;
    undefined4 field_34c;
    undefined4 field_350;
    undefined4 field_354;
    undefined4 field_358;
    undefined4 field_35c;
    undefined4 field_360;
    undefined4 field_364;
    undefined4 field_368;
    LiveObject* drivenObject; /* same as drivingThisObject */
    ToolType carriedTools[5];
    unsigned int numCarriedTools;
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
    LiveObject* object_3c0;
    undefined4 field_3c4;
    undefined4 field_3c8;
    LiveObject* object_3cc;
    undefined4 field_3d0;
    float elapsedTime1; /* elapsed time counter 1 */
    float elapsedTime2; /* elapsed time counter 2 */
    float activityElapsedTime; /* elapsed time since last order? */
    unsigned int flags_3e0;
    unsigned int flags_3e4;
    unsigned int flags_3e8; /* (assigned 0, flags?) */
    unsigned int flags_3ec;
    unsigned int flags_3f0; /* (assigned 0, flags?) */
    undefined4 field_3f4;
    undefined4 field_3f8;
    undefined4 field_3fc;
    undefined4 field_400;
    undefined4 field_404;
    LiveObject* pool_m_next;
};

struct UpgradeData
{
    int objIndex;
    undefined4 field_4;
    undefined4 field_8;
    undefined4 field_c;
};

struct AITaskData
{
    int taskType;
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
    LiveObject* object_10;
    float unkExpiryTime;
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
    void* ptr_40;
    undefined field_0x44;
    undefined field_0x45;
    undefined field_0x46;
    undefined field_0x47;
    LiveObject* object_48;
    undefined field_0x4c;
    undefined field_0x4d;
    undefined field_0x4e;
    undefined field_0x4f;
    unsigned int taskStartTime;
    undefined field_0x54;
    undefined field_0x55;
    undefined field_0x56;
    undefined field_0x57;
    undefined field_0x58;
    undefined field_0x59;
    undefined field_0x5a;
    undefined field_0x5b;
    unsigned int flags_5c; /* not set means ptr_40 is assigned */
    AITaskData* next; /* assigned to DAT_004b4358 */
    AITaskData* pool_m_next;
};

struct CreatureData
{
    int objIndex;
    void* ptr_4;
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
    void* subdata_64;
    void* subdata_68;
    void* subdata_6c;
    unsigned int flags;
};

}
}
