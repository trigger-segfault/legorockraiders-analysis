#pragma once
#include "../Common.h"
#include "ModelGhidra.h"

namespace lego {


#pragma pack(push, 1)

typedef BOOL(__cdecl* GameInitFunction)(void);
typedef BOOL(__cdecl* GameUpdateFunction)(float elapsed); // float argument is elapsed game time units since last update
typedef void(__cdecl* GameCleanupFunction)(void);

struct GameFunctions
{
	/*0,4*/ GameInitFunction Init;
	/*4,4*/ GameUpdateFunction Update;
	/*8,4*/ GameCleanupFunction Cleanup;
	/*c*/
};

enum class ObjectType : int
{
	TVCamera = -1, // not used in-game, may only be for loading in .ol files
	None = 0,
	Vehicle = 1, // [table]
	MiniFigure = 2, // [table]
	RockMonster = 3, // [table]
	Building = 4, // [table]
	Boulder = 5,
	PowerCrystal = 6,
	Ore = 7, // [normal, processed]
	Dynamite = 8,
	Barrier = 9,
	Upgrade = 10, // [table] upgrade part attached to live vehicles, these are defined in a Vehicle's .ae file
	ElectricFence = 11,
	SpiderWeb = 12,
	SonicBlaster = 13, // sonic blaster when carried and used like Dynamite (which may only be possible with debug keys)
	ElectricFenceStud = 14, // yellow beacon between electric fence connections, only present when distance is 2 blocks
	Path = 15, // (never seen as a live object)
	PusherShot = 16,
	FreezerShot = 17,
	IceCube = 18, // ice block created by frozen creatures
	LaserShot = 19, // this does not include "instant" lasers, like from vehicles, and the mining laser
};

enum class ToolType : int
{
	Invalid = -1,
	Drill = 0,
	Shovel = 1, // "Spade"
	Hammer = 2,
	Spanner = 3,
	LaserBeam = 4,
	PusherBeam = 5,
	SonicBlaster = 6,
	FreezerBeam = 7,
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

enum PredugType : unsigned char
{
	PREDUG_WALL             = 0x0, // Undug wall (in exposed or hidden cavern)
	PREDUG_EXPOSED          = 0x1, // Exposed tile
	PREDUG_HIDDEN           = 0x2, // Undiscovered cavern tile
	PREDUG_EXPOSED_SLUGHOLE = 0x3, // Exposed Slimy Slug Hole
	PREDUG_HIDDEN_SLUGHOLE  = 0x4, // Undiscovered cavern Slimy Slug Hole
};

enum SurfaceTexture : unsigned char
{
	TEXTURE_GROUND              = 0x00, // Ground (floor)
	TEXTURE_WALL_F_SOIL         = 0x01, // Soil wall (forward)
	TEXTURE_WALL_F_LOOSE        = 0x02, // Loose "Dirt" wall (forward)
	TEXTURE_WALL_F_MEDIUM       = 0x03, // Medium "Loose" wall (forward)
	TEXTURE_WALL_F_HARD         = 0x04, // Hard wall (forward)
	TEXTURE_WALL_F_IMMOVABLE    = 0x05, // Immovable "Solid" wall (forward)
	TEXTURE_ERODE_LOW           = 0x06, // Erode level 1/4 (min)
	TEXTURE_07                  = 0x07, // [unused, Ice Biome] Hand-drawn lightning bolt over ground texture

	TEXTURE_RUBBLE_FULL         = 0x10, // Rubble level 4/4 (max)
	TEXTURE_RUBBLE_HIGH         = 0x11, // Rubble level 3/4
	TEXTURE_RUBBLE_MEDIUM       = 0x12, // Rubble level 2/4
	TEXTURE_RUBBLE_LOW          = 0x13, // Rubble level 1/4 (min)

	TEXTURE_ERODE_MEDIUM        = 0x16, // Erode level 2/4

	TEXTURE_WALL_F_CRYSTALSEAM  = 0x20, // "Energy" Crystal Seam wall (forward)
	TEXTURE_WALL_R_SOIL         = 0x21, // Soil wall (forward) [reinforced)
	TEXTURE_WALL_R_LOOSE        = 0x22, // Loose "Dirt" wall (forward) [reinforced)
	TEXTURE_WALL_R_MEDIUM       = 0x23, // Medium "Loose" wall (forward) [reinforced)
	TEXTURE_WALL_R_HARD         = 0x24, // Hard wall (forward) [reinforced)
	TEXTURE_WALL_R_IMMOVABLE    = 0x25, // Immovable "Solid" wall (forward) [reinforced)
	TEXTURE_ERODE_HIGH          = 0x26, // Erode level 3/4

	TEXTURE_SLUGHOLE            = 0x30, // Slimy slug hole
	TEXTURE_WALL_C_SOIL         = 0x31, // Soil wall (acute-corner)
	TEXTURE_WALL_C_LOOSE        = 0x32, // Loose "Dirt" wall (acute-corner)
	TEXTURE_WALL_C_MEDIUM       = 0x33, // Medium "Loose" wall (acute-corner)
	TEXTURE_WALL_C_HARD         = 0x34, // Hard wall (acute-corner)
	TEXTURE_WALL_C_IMMOVABLE    = 0x35, // Immovable "Solid" wall (acute-corner)
	TEXTURE_ERODE_FULL          = 0x36, // Erode level 4/4 (max)

	TEXTURE_WALL_F_ORESEAM      = 0x40, // Ore Seam wall (forward)

	TEXTURE_WATER               = 0x45, // Water lake
	TEXTURE_LAVA                = 0x46, // Lava lake
	TEXTURE_LAVA_NOTHOT         = 0x47, // [unused] Lava with text "NO HOT" drawn on it

	TEXTURE_WALL_O_SOIL         = 0x51, // Soil wall (obtuse-corner)
	TEXTURE_WALL_O_LOOSE        = 0x52, // Loose "Dirt" wall (obtuse-corner)
	TEXTURE_WALL_O_MEDIUM       = 0x53, // Medium "Loose" wall (obtuse-corner)
	TEXTURE_WALL_O_HARD         = 0x54, // Hard wall (obtuse-corner)
	TEXTURE_WALL_O_IMMOVABLE    = 0x55, // Immovable "Solid" wall (obtuse-corner)

	TEXTURE_PATH_4              = 0x60, // 4-sides Power Path
	TEXTURE_PATH_BUILD          = 0x61, // Power Path stud waiting to be built
	TEXTURE_PATH_2              = 0x62, // 2-sided Power Path (straight)
	TEXTURE_PATH_C              = 0x63, // 2-sided Power Path (corner)
	TEXTURE_PATH_3              = 0x64, // 3-sided Power Path
	TEXTURE_PATH_1              = 0x65, // 1-sided Power Path
	TEXTURE_PLATE_POWERED       = 0x66, // Square building Power Path plate [powered]
	TEXTURE_WALL_F_RECHARGESEAM = 0x67, // Recharge Seam wall (forward)

	TEXTURE_TUNNEL              = 0x70, // Tunnel as seen in top-down view (ceiling)
	TEXTURE_PATH_4_POWERED      = 0x71, // 4-sided Power Path [powered]
	TEXTURE_PATH_2_POWERED      = 0x72, // 2-sided Power Path (vertical) [powered]
	TEXTURE_PATH_C_POWERED      = 0x73, // 2-sided Power Path (corner) [powered]
	TEXTURE_PATH_3_POWERED      = 0x74, // 3-sided Power Path [powered]
	TEXTURE_PATH_1_POWERED      = 0x75, // 1-sided Power Path [powered]
	TEXTURE_PLATE               = 0x76, // Square building Power Path plate
	TEXTURE_WALL_GAP            = 0x77, // Gap for diagonally-connected wall
};

enum TerrainType : unsigned char
{
	TERRAIN_TUNNEL       = 0x0, // Tunnel (ceiling)
	TERRAIN_IMMOVABLE    = 0x1, // Immovable "Solid" wall
	TERRAIN_HARD         = 0x2, // Hard wall
	TERRAIN_MEDIUM       = 0x3, // Medium "Loose" wall
	TERRAIN_LOOSE        = 0x4, // Loose "Dirt" wall
	TERRAIN_SOIL         = 0x5, // [unused] Soil wall
	TERRAIN_LAVA         = 0x6, // Lava lake
	TERRAIN_WATER_unused = 0x7, // [unused] "flood water"
	TERRAIN_ORESEAM      = 0x8, // Ore Seam wall
	TERRAIN_LAKE         = 0x9, // Lake "Water"
	TERRAIN_CRYSTALSEAM  = 0xa, // "Energy" Crystal Seam wall
	TERRAIN_RECHARGESEAM = 0xb, // Recharge Seam wall
	TERRAIN_RUBBLE       = 0xc, // Rubble pile (at any level)
	TERRAIN_REINFORCED   = 0xd, // Reinforced wall type
	TERRAIN_PATH         = 0xe, // Power Path (TODO: does this include Building Power Path plates?)
	TERRAIN_SLUGHOLE     = 0xf, // Slimy Slug Hole
	TERRAIN_UNDISCOVERED = 0x10, // Undiscovered Cavern
	TERRAIN_CAVERN       = 0x11, // Exposed Cavern "Cavern floor"
};

enum CryOreType : unsigned char
{
	/*CRYORE_NONE           = 0x0,
	CRYORE_CRYSTAL_1      = 1,
	CRYORE_ORE_1          = 2,
	CRYORE_CRYSTAL_1_LV1  = 3,
	CRYORE_ORE_1_LV1      = 4,
	CRYORE_CRYSTAL_3      = 5,
	CRYORE_ORE_3          = 6,
	CRYORE_CRYSTAL_3_LV1  = 7,
	CRYORE_ORE_3_LV1      = 8,
	CRYORE_CRYSTAL_5      = 9,
	CRYORE_ORE_5          = 10,
	CRYORE_CRYSTAL_5_LV1  = 11,
	CRYORE_ORE_5_LV1      = 12,
	CRYORE_CRYSTAL_10     = 13,
	CRYORE_ORE_10         = 14,
	CRYORE_CRYSTAL_10_LV1 = 15,
	CRYORE_ORE_10_LV1     = 16,
	CRYORE_CRYSTAL_25     = 17,
	CRYORE_ORE_25         = 18,
	CRYORE_CRYSTAL_25_LV1 = 19,
	CRYORE_ORE_25_LV1     = 20,*/
	
	CRYORE_NONE           = 0x0,

	CRYORE_LV0_CRYSTAL_1  = 0x1,
	CRYORE_LV0_ORE_1      = 0x2,
	CRYORE_LV1_CRYSTAL_1  = 0x3,
	CRYORE_LV1_ORE_1      = 0x4,

	CRYORE_LV0_CRYSTAL_3  = 0x5,
	CRYORE_LV0_ORE_3      = 0x6,
	CRYORE_LV1_CRYSTAL_3  = 0x7,
	CRYORE_LV1_ORE_3      = 0x8,

	CRYORE_LV0_CRYSTAL_5  = 0x9,
	CRYORE_LV0_ORE_5      = 0xa,
	CRYORE_LV1_CRYSTAL_5  = 0xb,
	CRYORE_LV1_ORE_5      = 0xc,

	CRYORE_LV0_CRYSTAL_10 = 0xd,
	CRYORE_LV0_ORE_10     = 0xe,
	CRYORE_LV1_CRYSTAL_10 = 0xf,
	CRYORE_LV1_ORE_10     = 0x10,

	CRYORE_LV0_CRYSTAL_25 = 0x11,
	CRYORE_LV0_ORE_25     = 0x12,
	CRYORE_LV1_CRYSTAL_25 = 0x13,
	CRYORE_LV1_ORE_25     = 0x14,
};

enum ErodeType : unsigned char
{
	ERODE_NONE            = 0x0,

	ERODE_VERYSLOW_LAVA   = 0x1,
	ERODE_VERYSLOW_ALWAYS = 0x2,
	ERODE_SLOW_LAVA       = 0x3,
	ERODE_SLOW_ALWAYS     = 0x4,
	ERODE_MEDIUM_LAVA     = 0x5,
	ERODE_MEDIUM_ALWAYS   = 0x6,
	ERODE_FAST_LAVA       = 0x7,
	ERODE_FAST_ALWAYS     = 0x8,
	ERODE_VERYFAST_LAVA   = 0x9,
	ERODE_VERYFAST_ALWAYS = 0xa,
};

enum LevelBlockFlags1 : unsigned int
{
	BLOCK1_NONE          = 0,

	BLOCK1_RUBBLE_LOW    = 0x0,
	BLOCK1_RUBBLE_MEDIUM = 0x1,
	BLOCK1_RUBBLE_HIGH   = 0x2,
	BLOCK1_RUBBLE_FULL   = 0x3,

	BLOCK1_UNK_8         = 0x8,
	BLOCK1_UNK_10        = 0x10,
	BLOCK1_REINFORCED    = 0x20,
	BLOCK1_UNK_40        = 0x40,
	BLOCK1_UNK_80        = 0x80,

	BLOCK1_UNK_200       = 0x200,
	BLOCK1_UNK_400       = 0x400,
	BLOCK1_UNK_800       = 0x800,
	BLOCK1_UNK_1000      = 0x1000,

	BLOCK1_UNK_4000      = 0x4000,
	BLOCK1_UNK_8000      = 0x8000,

	BLOCK1_HIDDEN        = 0x20000,

	BLOCK1_UNK_80000     = 0x80000,
	BLOCK1_UNK_100000    = 0x100000,
	BLOCK1_UNK_200000    = 0x200000,
	BLOCK1_UNK_400000    = 0x400000,

	BLOCK1_EXPOSED       = 0x4000000,
	BLOCK1_UNK_8000000   = 0x8000000,

	BLOCK1_POWERPATH     = 0x20000000,
	BLOCK1_UNK_40000000  = 0x40000000,
	BLOCK1_UNK_80000000  = 0x80000000,
};
DEFINE_ENUM_FLAG_OPERATORS(LevelBlockFlags1)

enum LevelBlockFlags2 : unsigned int
{
	BLOCK2_NONE = 0,

	BLOCK2_SLUGHOLE_EXPOSED = 0x20,
	BLOCK2_EMERGE_POINT     = 0x40,
	BLOCK2_EMERGE_TRIGGER   = 0x80,

	BLOCK2_SLUGHOLE_HIDDEN  = 0x200,
};
DEFINE_ENUM_FLAG_OPERATORS(LevelBlockFlags2)


enum ResourceDataFlags : unsigned int
{
	RESDATA_NONE   = 0,

	RESDATA_UNK_2  = 0x2,

	RESDATA_UNK_8  = 0x8,
	RESDATA_UNK_10 = 0x10,
	RESDATA_UNK_20 = 0x20,

	RESDATA_UNK_80 = 0x80,
};
DEFINE_ENUM_FLAG_OPERATORS(ResourceDataFlags)



enum LiveFlags1 : unsigned int
{
	LIVEOBJ1_NONE          = 0,

	LIVEOBJ1_MOVING        = 0x1,
	LIVEOBJ1_UNK_2_LEFTING = 0x2,
	LIVEOBJ1_TURNING       = 0x4,

	LIVEOBJ1_REINFORCING   = 0x40,

	LIVEOBJ1_TURNRIGHT     = 0x80,

	LIVEOBJ1_CARRYING      = 0x400,

	LIVEOBJ1_CLEARING      = 0x40000,
	LIVEOBJ1_PLACING       = 0x80000,

	LIVEOBJ1_REST          = 0x20000000,
	LIVEOBJ1_EATING        = 0x40000000,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags1)

enum LiveFlags2 : unsigned int
{
	LIVEOBJ2_NONE        = 0,

	LIVEOBJ2_DRIVING     = 0x8,

	LIVEOBJ2_TRAINING    = 0x400,
	LIVEOBJ2_UNK_800     = 0x800,

	LIVEOBJ2_UPGRADING   = 0x8000,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags2)

enum LiveFlags3 : unsigned int
{
	LIVEOBJ3_NONE         = 0,

	LIVEOBJ3_SIMPLEOBJECT = 0x20000,

	LIVEOBJ3_UNK_80000    = 0x80000,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags3)

enum LiveFlags4 : unsigned int
{
	LIVEOBJ4_NONE = 0,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags4)

enum LiveFlags5 : unsigned int
{
	LIVEOBJ5_NONE = 0,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags5)


enum AITaskType : int
{
	AITASK__INVALID          = -1,

	AITASK_GOTO              = 0,
	AITASK_FOLLOW            = 1,
	AITASK_FOLLOWATTACK      = 2,
	AITASK_COLLECT           = 3,
	AITASK_GATHER            = 4,
	AITASK_DEPOSITE          = 5,
	AITASK_DUMP              = 6,
	AITASK_REQUEST           = 7,
	AITASK_DIG               = 8,
	AITASK_DYNAMITE          = 9,
	AITASK_REPAIR            = 10,
	AITASK_REINFORCE         = 11,
	AITASK_CLEAR             = 12,
	AITASK_WAIT              = 13,
	AITASK_ANIMATIONWAIT     = 14,
	AITASK_ELECFENCE         = 15,
	AITASK_EAT               = 16,
	AITASK_GOTOEAT           = 17,
	AITASK_FINDDRIVER        = 18,
	AITASK_GETTOOL           = 19,
	AITASK_SONICBLASTER      = 20,
	AITASK_UPGRADE           = 21,
	AITASK_BUILDPATH         = 22,
	AITASK_TRAIN             = 23,
	AITASK_DEPART            = 24,
	AITASK_ATTACKPATH        = 25,
	AITASK_ATTACKROCKMONSTER = 26,
	AITASK_RECHARGE          = 27,
	AITASK_DOCK              = 28,
	AITASK_ATTACKOBJECT      = 29,
	AITASK_FINDLOAD          = 30,
};

enum AIPriorityType : int
{
	AIPRIORITY__INVALID          = -1,

	AIPRIORITY_CRYSTAL           = 0,
	AIPRIORITY_ORE               = 1,
	AIPRIORITY_DEFAULTCOLLECT    = 2,
	AIPRIORITY_DESTRUCTION       = 3,
	AIPRIORITY_CONSTRUCTION      = 4,
	AIPRIORITY_REQUEST           = 5,
	AIPRIORITY_REINFORCE         = 6,
	AIPRIORITY_REPAIR            = 7,
	AIPRIORITY_CLEARING          = 8,
	AIPRIORITY_STORAGE           = 9,
	AIPRIORITY_REFINING          = 10,
	AIPRIORITY_HEALTHLOW         = 11,
	AIPRIORITY_GETIN             = 12,
	AIPRIORITY_UPGRADE           = 13,
	AIPRIORITY_BUILDPATH         = 14,
	AIPRIORITY_ATTACKROCKMONSTER = 15,
	AIPRIORITY_BARRIER           = 16,
	AIPRIORITY_FINDLOAD          = 17,
	AIPRIORITY_RECHARGE          = 18,
	AIPRIORITY_UPGRADEBUILDING   = 19,
	AIPRIORITY_GATHER            = 20,
	AIPRIORITY_STEAL             = 21,
	AIPRIORITY_PUNCH             = 22,
	AIPRIORITY_DEPART            = 23,
	AIPRIORITY_ATTACKPATH        = 24,
	AIPRIORITY_ATTACKOBJECT      = 25,
	AIPRIORITY_CONGREGATE        = 26,
};

enum ObjectStatsFlags1 : unsigned int
{
	STATS1_NONE                  = 0,

	STATS1_SINGLEWIDTHDIG        = 0x1,
	STATS1_PROCESSORE            = 0x2,
	STATS1_PROCESSCRYSTAL        = 0x4,
	STATS1_STOREOBJECTS          = 0x8,
	STATS1_SMALLTELEPORTER       = 0x10,
	STATS1_BIGTELEPORTER         = 0x20,
	STATS1_WATERTELEPORTER       = 0x40,
	STATS1_COLLRADIUS            = 0x80,
	STATS1_COLLBOX               = 0x100,
	STATS1_CAUSESLIP             = 0x200,
	STATS1_RANDOMMOVE            = 0x400,
	STATS1_CANSCARE              = 0x800,
	STATS1_RANDOMENTERWALL       = 0x1000,
	STATS1_SCAREDBYPLAYER        = 0x2000,
	STATS1_SNAXULIKE             = 0x4000,
	STATS1_GRABMINIFIGURE        = 0x8000,
	STATS1_CANCLEARRUBBLE        = 0x10000,
	STATS1_CANBEDRIVEN           = 0x20000,
	STATS1_CANSCARESCORPION      = 0x40000,
	STATS1_CANSTEAL              = 0x80000,
	STATS1_TOOLSTORE             = 0x100000,
	STATS1_FLOCKS                = 0x200000,
	STATS1_FLOCKS_DEBUG          = 0x400000,
	STATS1_FLOCKS_SMOOTH         = 0x800000,
	STATS1_CROSSWATER            = 0x1000000,
	STATS1_CROSSLAND             = 0x2000000,
	STATS1_FLOCKS_ONGROUND       = 0x4000000,
	STATS1_FLOCKS_QUICKDESTROY   = 0x8000000,
	STATS1_FLOCKS_ANIMATEBYPITCH = 0x10000000,
	STATS1_ROUTEAVOIDANCE        = 0x20000000,
	STATS1_BUMPDAMAGE            = 0x40000000,
	STATS1_MANTELEPORTER         = 0x80000000,
};
DEFINE_ENUM_FLAG_OPERATORS(ObjectStatsFlags1)

enum ObjectStatsFlags2 : unsigned int
{
	STATS2_NONE                   = 0,

	STATS2_SCAREDBYBIGBANGS       = 0x1,
	STATS2_UPGRADEBUILDING        = 0x2,
	STATS2_TRAINPILOT             = 0x4,
	STATS2_TRAINSAILOR            = 0x8,
	STATS2_TRAINDRIVER            = 0x10,
	STATS2_TRAINDYNAMITE          = 0x20,
	STATS2_TRAINREPAIR            = 0x40,
	STATS2_TRAINSCANNER           = 0x80,
	STATS2_TRACKER                = 0x100,
	STATS2_GENERATEPOWER          = 0x200, // Not used directly, half of "PowerBuilding" property
	STATS2_SELFPOWERED            = 0x400,
	STATS2_POWERBUILDING          = 0x200 | 0x400, // STATS2_GENERATEPOWER | STATS2_SELFPOWERED
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
	STATS2_DONTSHOWDAMAGE         = 0x8000000,
	STATS2_REMOVEREINFORCEMENT    = 0x10000000,
	STATS2_DONTSHOWONRADAR        = 0x20000000,
	STATS2_INVISIBLEDRIVER        = 0x40000000,
	STATS2_UNSELECTABLE           = 0x80000000,
};
DEFINE_ENUM_FLAG_OPERATORS(ObjectStatsFlags2)

enum ObjectStatsFlags3 : unsigned int
{
	STATS3_NONE                = 0,

	STATS3_CARRYVEHICLES       = 0x1,
	STATS3_VEHICLECANBECARRIED = 0x2,
	STATS3_CANSTRAFE           = 0x4,
	STATS3_CLASSASLARGE        = 0x8,
	STATS3_GETOUTATLAND        = 0x10,
	STATS3_GETINATLAND         = 0x20,
	STATS3_TAKECARRYINGDRIVERS = 0x40,
	STATS3_SHOWHEALTHBAR       = 0x80,
	STATS3_NEEDSPILOT          = 0x100,
	STATS3_ENTERTOOLSTORE      = 0x200,
};
DEFINE_ENUM_FLAG_OPERATORS(ObjectStatsFlags3)


enum GraphicsQuality : int
{
	QUALITY_WIREFRAME = 0,
	QUALITY_UNLITFLAT = 1,
	QUALITY_FLAT      = 2,
	QUALITY_GOURAUD   = 3,
	
	// There is no exact number assigned to this. But in certain contexts,
	//  passing anything not in the above list to a function,
	//  will allow directly defining the D3DRM render mode.
	QUALITY_CUSTOM    = 4, 
};


enum GameFlags1 : unsigned int
{
	GAME1_NONE                  = 0,
	
	//GAME1_UNK_1                 = 0x1,
	GAME1_RADARON               = 0x2,
	GAME1_UNK_4                 = 0x4,
	GAME1_MUSICON               = 0x8,

	GAME1_SOUNDON               = 0x10,
	GAME1_WALLPROMESHES         = 0x20,
	GAME1_FRAMERATEMONITOR      = 0x40,
	GAME1_MEMORYMONITOR         = 0x80,

	GAME1_UNK_100               = 0x100,
	GAME1_UNK_200               = 0x200,
	GAME1_CLEAR                 = 0x400,
	GAME1_PANELS                = 0x800,

	GAME1_RADAR_MAPVIEW         = 0x1000,
	GAME1_RADAR_TRACKOBJECTVIEW = 0x2000,
	GAME1_UNK_4000              = 0x4000,
	GAME1_FOGCOLOURRGB          = 0x8000,

	GAME1_HIGHFOGCOLOURRGB      = 0x10000,
	GAME1_UNK_20000             = 0x20000,
	GAME1_UNK_40000             = 0x40000,
	GAME1_DYNAMICPM             = 0x80000,

	GAME1_CAMERADISABLED        = 0x100000,
	GAME1_UNK_200000            = 0x200000,
	GAME1_ONLYBUILDONPATHS      = 0x400000,
	GAME1_ALWAYSROCKFALL        = 0x800000,

	GAME1_DEBUG_NONERPS         = 0x1000000,
	GAME1_PAUSED                = 0x2000000,
	GAME1_STREAMNERPSSPEACH     = 0x4000000,
	GAME1_UNK_8000000           = 0x8000000,

	GAME1_LASERTRACKER          = 0x10000000,
	GAME1_UNK_20000000          = 0x20000000,
	GAME1_DEBUG_NOCLIP_FPS      = 0x40000000,
	GAME1_UNK_80000000          = 0x80000000,
};
DEFINE_ENUM_FLAG_OPERATORS(GameFlags1)

enum GameFlags2 : unsigned int
{
	GAME2_NONE                 = 0,

	GAME2_CALLTOARMS           = 0x1,
	//GAME2_UNK_2                = 0x2,
	GAME2_UNK_4                = 0x4,
	GAME2_SHOWDEBUGTOOLTIPS    = 0x8,
	GAME2_ALLOWDEBUGKEYS       = 0x10,
	GAME2_ALLOWEDITMODE        = 0x20,
	GAME2_UNK_40               = 0x40,
	GAME2_UNK_80               = 0x80,
	GAME2_INOPTIONSMENU        = 0x100,
	GAME2_CAMERAMOVING         = 0x200,
	GAME2_MOUSE_INSIDEGAMEVIEW = 0x400,
	GAME2_MUSICON              = 0x800,
	GAME2_INMENU               = 0x1000,
	GAME2_NOMULTISELECT        = 0x2000,
	GAME2_MENU_HASNEXT         = 0x4000,
	GAME2_MENU_HASPREVIOUS     = 0x8000,
	//GAME2_UNK_10000            = 0x10000,
	GAME2_ALLOWRENAME          = 0x20000,
	GAME2_RECALLOLOBJECTS      = 0x40000,
	GAME2_GENERATESPIDERS      = 0x80000,
	GAME2_DISABLETOOLTIPSOUND  = 0x100000,
	GAME2_NOAUTOEAT            = 0x200000,
};
DEFINE_ENUM_FLAG_OPERATORS(GameFlags2)

enum GameFlags3 : unsigned int
{
	GAME3_NONE          = 0,

	GAME3_UNK_1         = 0x1,
	GAME3_UNK_2         = 0x2,
	GAME3_UNK_4         = 0x4,
	GAME3_PICKUPOBJECT  = 0x8,
	GAME3_LOADVEHICLE   = 0x10,
	GAME3_UNK_20        = 0x20,
	GAME3_UNK_40        = 0x40,
	GAME3_PLACEBUILDING = 0x80,
};
DEFINE_ENUM_FLAG_OPERATORS(GameFlags3)

enum TextureType : int
{
	TEXTURES__INVALID = -1,

	TEXTURES_ROCK = 0,
	TEXTURES_LAVA = 1,
	TEXTURES_ICE  = 2,
};

enum LevelCompleteStatus : int
{
	LEVELSTATUS_NONE            = 0,
	LEVELSTATUS_COMPLETE        = 1,
	LEVELSTATUS_FAILED          = 2,
	LEVELSTATUS_FAILED_CRYSTALS = 3,
	LEVELSTATUS_FAILED_OTHER    = 4,
};

// Location of a lego File stream (WAD or REAL)
// Same as BOOL3
enum FileLocation : int
{
	FILELOC_WAD   = 0,
	FILELOC_STD   = 1,
	FILELOC_ERROR = 2,
};

enum DriverModeFlags : unsigned int
{
	DRIVERMODE_NONE      = 0,

	DRIVERMODE_ISUSED    = 0x1,

	DRIVERMODE_NOGUID_10 = 0x10,
	DRIVERMODE_NOGUID_20 = 0x20,
};
DEFINE_ENUM_FLAG_OPERATORS(DriverModeFlags)

enum DeviceModeFlags : unsigned int
{
	DEVICEMODE_NONE                = 0,

	DEVICEMODE_ISUSED              = 0x1,

	DEVICEMODE_BPP_8               = 0x10,
	DEVICEMODE_BPP_16              = 0x20,
	DEVICEMODE_BPP_24              = 0x40,
	DEVICEMODE_BPP_32              = 0x80,

	DEVICEMODE_COLORMODEL_RGB      = 0x1000,
	DEVICEMODE_HARDWARE            = 0x2000,
	DEVICEMODE_TEXTUREVIDEOMEMORY  = 0x4000,
	DEVICEMODE_TEXTURESYSTEMMEMORY = 0x8000,
};
DEFINE_ENUM_FLAG_OPERATORS(DeviceModeFlags)

enum ScreenModeFlags : unsigned int
{
	SCREENMODE_NONE   = 0,

	SCREENMODE_ISUSED = 0x1,
};
DEFINE_ENUM_FLAG_OPERATORS(ScreenModeFlags)

enum MessageType : int
{
	MESSAGE__INVALID                       = -1,
	
	MESSAGE_NULL                           = 0,
	MESSAGE_SELECT                         = 1,
	MESSAGE_SELECTED                       = 2,
	MESSAGE_CLEARSELECT                    = 3,
	MESSAGE_DESELECT                       = 4,
	MESSAGE_GOTO                           = 5,
	MESSAGE_ROCKMONSTERGOTO                = 6,
	MESSAGE_ROCKMONSTERGOTO_COMPLETE       = 7,
	MESSAGE_USERGOTO                       = 8,
	MESSAGE_FIRSTPERSON                    = 9,
	MESSAGE_TRACKOBJECT                    = 10,
	MESSAGE_TOPVIEW                        = 11,
	MESSAGE_PLAYSAMPLE                     = 12,
	MESSAGE_DIG                            = 13,
	MESSAGE_DIG_COMPLETE                   = 14,
	MESSAGE_REPAIR                         = 15,
	MESSAGE_REPAIR_COMPLETE                = 16,
	MESSAGE_REINFORCE                      = 17,
	MESSAGE_REINFORCE_COMPLETE             = 18,
	MESSAGE_ROCKFALL                       = 19,
	MESSAGE_ROCKFALL_COMPLETE              = 20,
	MESSAGE_GENERATECRYSTAL                = 21,
	MESSAGE_GENERATECRYSTAL_COMPLETE       = 22,
	MESSAGE_COLLECTCRYSTAL                 = 23,
	MESSAGE_COLLECTCRYSTAL_COMPLETE        = 24,
	MESSAGE_CRYSTALTOREFINERY              = 25,
	MESSAGE_CRYSTALTOREFINERY_COMPLETE     = 26,
	MESSAGE_GENERATEORE                    = 27,
	MESSAGE_GENERATEORE_COMPLETE           = 28,
	MESSAGE_COLLECTORE                     = 29,
	MESSAGE_COLLECTORE_COMPLETE            = 30,
	MESSAGE_GENERATEROCKMONSTER            = 31,
	MESSAGE_GENERATEROCKMONSTER_COMPLETE   = 32,
	MESSAGE_GATHERROCK                     = 33,
	MESSAGE_GATHERROCK_COMPLETE            = 34,
	MESSAGE_PICKRANDOMFLOOR                = 35,
	MESSAGE_PICKRANDOMFLOOR_COMPLETE       = 36,
	MESSAGE_ATTACKBUILDING                 = 37,
	MESSAGE_ATTACKBUILDING_COMPLETE        = 38,
	MESSAGE_CLEAR                          = 39,
	MESSAGE_CLEAR_COMPLETE                 = 40,
	MESSAGE_GETIN                          = 41,
	MESSAGE_MANSELECTEDANDMONSTERCLICKED   = 42,
	MESSAGE_FOLLOWATTACK                   = 43,
	MESSAGE_COLLECTTOOL                    = 44,
	MESSAGE_REDUCESELECTION                = 45,
	MESSAGE_CLEARFALLIN                    = 46,
	MESSAGE_CLEARFALLIN_COMPLETE           = 47,
	MESSAGE_BUILDPATH                      = 48,
	MESSAGE_BUILDPATH_COMPLETE             = 49,
	MESSAGE_TRAIN                          = 50,
	MESSAGE_TRAIN_COMPLETE                 = 51,
	MESSAGE_GENERATECRYSTALANDORE          = 52,
	MESSAGE_GENERATECRYSTALANDORE_COMPLETE = 53,
	MESSAGE_GENERATEFROMCRYORE             = 54,
	MESSAGE_GENERATEFROMCRYORE_COMPLETE    = 55,
	MESSAGE_UPGRADE                        = 56,
	MESSAGE_UPGRADE_COMPLETE               = 57,
	MESSAGE_CLEARBUILDING                  = 58,
	MESSAGE_CLEARBUILDING_COMPLETE         = 59,
	MESSAGE_CLEARINITIAL                   = 60,
	MESSAGE_CLEARINITIAL_COMPLETE          = 61,
	MESSAGE_CLEARREMOVEPATH                = 62,
	MESSAGE_CLEARREMOVEPATH_COMPLETE       = 63,
	MESSAGE_DEBUG_DESTROYALL               = 64,
};


enum WADEntryFlags : unsigned int
{
	WADENTRY_NONE            = 0,

	WADENTRY_UNK_STORE       = 0x1,
	WADENTRY_RNC_COMPRESSION = 0x2,
};
DEFINE_ENUM_FLAG_OPERATORS(WADEntryFlags)

enum FileBufferFlags : unsigned int
{
	FILEBUFFER_NONE   = 0,

	FILEBUFFER_ISUSED = 0x1,
};
DEFINE_ENUM_FLAG_OPERATORS(FileBufferFlags)

enum NERPSFunctionArgs : int
{
	NERPS_ARGS_0          = 0, // int func(void);
	NERPS_ARGS_1          = 1, // int func(int);
	NERPS_ARGS_2          = 2, // int func(int, int);
	NERPS_ARGS_0_NORETURN = 3, // void func(void);
	NERPS_ARGS_1_NORETURN = 4, // void func(int);
	NERPS_ARGS_2_NORETURN = 5, // void func(int, int);
	NERPS_ARGS_3_NORETURN = 6, // void func(int, int, int);
	NERPS_END_OF_LIST     = 7, // End of NERPs functions list "**End Of List**"
};

enum SampleFlags : unsigned int
{
	SAMPLE_NONE     = 0,

	SAMPLE_ISUSED   = 0x1,
	SAMPLE_VOLUME   = 0x2,
	SAMPLE_MULTIPLE = 0x4,
	SAMPLE_STREAMED = 0x8,
};
DEFINE_ENUM_FLAG_OPERATORS(SampleFlags)

enum ResourceManagerFlags : unsigned int
{
	RESMANAGER_NONE          = 0,

	RESMANAGER_ISINIT        = 0x1,

	RESMANAGER_SOUNDCALLBACK = 0x40,
};
DEFINE_ENUM_FLAG_OPERATORS(ResourceManagerFlags)

enum TrainedFlags : unsigned int
{
	TRAINED_NONE     = 0,

	TRAINED_PILOT    = 0x1,
	TRAINED_SAILOR   = 0x2,
	TRAINED_DRIVER   = 0x4,
	TRAINED_DYNAMITE = 0x8,
	TRAINED_REPAIR   = 0x10,
	TRAINED_SCANNER  = 0x20,
};
DEFINE_ENUM_FLAG_OPERATORS(TrainedFlags)

enum AudioFlags : unsigned int
{
	AUDIO_NONE    = 0,

	AUDIO_SOUNDON = 0x1,
	AUDIO_UNK_2   = 0x2,

	AUDIO_UNK_8   = 0x8,
};
DEFINE_ENUM_FLAG_OPERATORS(AudioFlags)

enum ObjectiveFlags : unsigned int
{
	OBJECTIVE_NONE               = 0,

	OBJECTIVE_UNK_1              = 0x1,
	OBJECTIVE_COMPLETE           = 0x2,
	OBJECTIVE_FAILED             = 0x4,
	OBJECTIVE_UNK_8              = 0x8,
	OBJECTIVE_SHOWADVISOR        = 0x10,
	OBJECTIVE_SHOWACHEIVEADVISOR = 0x20,
	OBJECTIVE_HITTIMEFAIL        = 0x40,
	OBJECTIVE_SHOWFAILEDADVISOR  = 0x80,
	OBJECTIVE_CRYSTAL            = 0x100,
	OBJECTIVE_ORE                = 0x200,
	OBJECTIVE_BLOCK              = 0x400,
	OBJECTIVE_TIMER              = 0x800,
	OBJECTIVE_CONSTRUCTION       = 0x1000,
};
DEFINE_ENUM_FLAG_OPERATORS(ObjectiveFlags)

enum ObjInfoFlags : unsigned int
{
	OBJINFO_BUBBLEIMAGES = 16,
	OBJINFO_HEALTHBAR = 2,
	OBJINFO_HEALTHBAR_VERTICAL = 8,
	OBJINFO_HUNGERIMAGES = 1,
	OBJINFO_NONE = 0
};
DEFINE_ENUM_FLAG_OPERATORS(ObjInfoFlags)

/*enum KeysByte : unsigned char
{
	KEYPAD_0 = 82,
	KEYPAD_1 = 79,
	KEYPAD_2 = 80,
	KEYPAD_3 = 81,
	KEYPAD_4 = 75,
	KEYPAD_5 = 76,
	KEYPAD_6 = 77,
	KEYPAD_7 = 71,
	KEYPAD_8 = 72,
	KEYPAD_9 = 73,
	KEYPAD_ASTERISK = 55,
	KEYPAD_DELETE = 83,
	KEYPAD_ENTER = 156,
	KEYPAD_FORWARDFLASH = 181,
	KEYPAD_MINUS = 74,
	KEYPAD_NUMLOCK = 69,
	KEYPAD_PLUS = 78,
	KEY_A = 30,
	KEY_ALT = 56,
	KEY_ALTGR = 184,
	KEY_AT = 40,
	KEY_B = 48,
	KEY_BACKSLASH = 86,
	KEY_BACKSPACE = 14,
	KEY_C = 46,
	KEY_CAPLOCK = 58,
	KEY_CURSORDOWN = 208,
	KEY_CURSORLEFT = 203,
	KEY_CURSORUP = 200,
	KEY_D = 32,
	KEY_DELETE = 211,
	KEY_E = 18,
	KEY_EIGHT = 9,
	KEY_END = 207,
	KEY_EQUALS = 13,
	KEY_ESCAPE = 1,
	KEY_F = 33,
	KEY_F1 = 59,
	KEY_F10 = 68,
	KEY_F11 = 87,
	KEY_F12 = 88,
	KEY_F2 = 60,
	KEY_F3 = 61,
	KEY_F4 = 62,
	KEY_F5 = 63,
	KEY_F6 = 64,
	KEY_F7 = 65,
	KEY_F8 = 66,
	KEY_F9 = 67,
	KEY_FIVE = 6,
	KEY_FOUR = 5,
	KEY_G = 34,
	KEY_H = 35,
	KEY_HASH = 43,
	KEY_HOME = 199,
	KEY_I = 23,
	KEY_INSERT = 210,
	KEY_J = 36,
	KEY_K = 37,
	KEY_L = 38,
	KEY_LEFTARROW = 51,
	KEY_LEFTBRACE = 26,
	KEY_LEFTCTRL = 29,
	KEY_LEFTSHIFT = 42,
	KEY_M = 50,
	KEY_MINUS = 12,
	KEY_N = 49,
	KEY_NINE = 10,
	KEY_O = 24,
	KEY_ONE = 2,
	KEY_P = 25,
	KEY_PGDN = 209,
	KEY_PGUP = 201,
	KEY_PRINTSCREEN = 183,
	KEY_Q = 16,
	KEY_QUESTIONMARK = 53,
	KEY_R = 19,
	KEY_RETURN = 28,
	KEY_RIGHTARROW = 52,
	KEY_RIGHTBRACE = 27,
	KEY_RIGHTCTRL = 157,
	KEY_RIGHTSHIFT = 54,
	KEY_RSINGLEQUOTE = 41,
	KEY_S = 31,
	KEY_SCROLLLOCK = 70,
	KEY_SEMICOLON = 39,
	KEY_SEVEN = 8,
	KEY_SIX = 7,
	KEY_SPACE = 57,
	KEY_T = 20,
	KEY_TAB = 15,
	KEY_THREE = 4,
	KEY_TWO = 3,
	KEY_U = 22,
	KEY_V = 47,
	KEY_W = 17,
	KEY_X = 45,
	KEY_Y = 21,
	KEY_Z = 44,
	KEY_ZERO = 11,
	KEY__NONE = 0
};*/


enum MenuItemType : int
{
	MENUITEM_CYCLE = 0,
	MENUITEM_NEXT = 5,
	MENUITEM_REALSLIDER = 4,
	MENUITEM_SLIDER = 3,
	MENUITEM_TEXTINPUT = 2,
	MENUITEM_TRIGGER = 1,
	MENUITEM__INVALID = -1,
};


enum AdvisorType : int
{
	ADVISOR_ICONPOINT_BACKBUTTON = 4,
	ADVISOR_ICONPOINT_NORMAL = 3,
	ADVISOR_ICONPOINT_TOPBUTTONS = 5,
	ADVISOR_OBJECTIVE = 0,
	ADVISOR_OBJECTIVEACHIEVED = 1,
	ADVISOR_OBJECTIVEFAILED = 2,
	ADVISOR_PANELPOINT_CONTROLZOOMIN = 18,
	ADVISOR_PANELPOINT_CONTROLZOOMOUT = 19,
	ADVISOR_PANELPOINT_INFODOCKCLOSE = 12,
	ADVISOR_PANELPOINT_INFODOCKGOTO = 11,
	ADVISOR_PANELPOINT_RADARMAPVIEW = 10,
	ADVISOR_PANELPOINT_RADARTOGGLE = 6,
	ADVISOR_PANELPOINT_RADARTOGGLEOBJECTVIEW = 7,
	ADVISOR_PANELPOINT_RADARZOOMIN = 8,
	ADVISOR_PANELPOINT_RADARZOOMOUT = 9,
	ADVISOR_PANELPOINT_TOPPANELCALLTOARMS = 16,
	ADVISOR_PANELPOINT_TOPPANELGOBACK = 17,
	ADVISOR_PANELPOINT_TOPPANELINFO = 13,
	ADVISOR_PANELPOINT_TOPPANELOPTIONS = 14,
	ADVISOR_PANELPOINT_TOPPANELPRIORITIES = 15,
	ADVISOR_TALKINGAME = 20,
	ADVISOR__INVALID = -1,
};


enum RegistryType : unsigned int
{
	REGISTRY_STRING = 0,
	REGISTRY_NUMBER = 1,
};

enum PolyMode : int
{
	POLY_LOW    = 0,
	POLY_MEDIUM = 1,
	POLY_HIGH   = 2,
	POLY_FP     = 3,
};

enum SurfaceType : int
{
	SURFACE_CAVERN = 17,
	SURFACE_CRYSTALSEAM = 10,
	SURFACE_HARD = 2,
	SURFACE_IMMOVABLE = 1,
	SURFACE_LAKE = 9,
	SURFACE_LAVA = 6,
	SURFACE_LOOSE = 4,
	SURFACE_MEDIUM = 3,
	SURFACE_ORESEAM = 8,
	SURFACE_PATH = 14,
	SURFACE_RECHARGESEAM = 11,
	SURFACE_REINFORCEMENT = 13,
	SURFACE_RUBBLE = 12,
	SURFACE_SLUGHOLE = 15,
	SURFACE_SOIL = 5,
	SURFACE_TUNNEL = 0,
	SURFACE_UNDISCOVERED = 16,
	SURFACE_WATER_unused = 7,
	SURFACE__INVALID = -1,
};

enum AdvisorAnim : int
{
	ADVISORANIM__INVALID   = -1,

	ADVISORANIM_POINTTOMAP = 0,
	ADVISORANIM_POINT_N    = 1,
	ADVISORANIM_POINT_NE   = 2,
	ADVISORANIM_POINT_E    = 3,
	ADVISORANIM_POINT_SE   = 4,
	ADVISORANIM_POINT_S    = 5,
	ADVISORANIM_POINT_SW   = 6,
	ADVISORANIM_POINT_W    = 7,
	ADVISORANIM_POINT_NW   = 8,
	ADVISORANIM_POINT_UP   = 9,
	ADVISORANIM_TALK_TOP   = 10,
};

//enum Keys : int
enum Keys : unsigned char
{
	KEYPAD_0 = 82,
	KEYPAD_1 = 79,
	KEYPAD_2 = 80,
	KEYPAD_3 = 81,
	KEYPAD_4 = 75,
	KEYPAD_5 = 76,
	KEYPAD_6 = 77,
	KEYPAD_7 = 71,
	KEYPAD_8 = 72,
	KEYPAD_9 = 73,
	KEYPAD_ASTERISK = 55,
	KEYPAD_DELETE = 83,
	KEYPAD_ENTER = 156,
	KEYPAD_FORWARDFLASH = 181,
	KEYPAD_MINUS = 74,
	KEYPAD_NUMLOCK = 69,
	KEYPAD_PLUS = 78,
	KEY_A = 30,
	KEY_ALT = 56,
	KEY_ALTGR = 184,
	KEY_AT = 40,
	KEY_B = 48,
	KEY_BACKSLASH = 86,
	KEY_BACKSPACE = 14,
	KEY_C = 46,
	KEY_CAPLOCK = 58,
	KEY_CURSORDOWN = 208,
	KEY_CURSORLEFT = 203,
	KEY_CURSORUP = 200,
	KEY_D = 32,
	KEY_DELETE = 211,
	KEY_E = 18,
	KEY_EIGHT = 9,
	KEY_END = 207,
	KEY_EQUALS = 13,
	KEY_ESCAPE = 1,
	KEY_F = 33,
	KEY_F1 = 59,
	KEY_F10 = 68,
	KEY_F11 = 87,
	KEY_F12 = 88,
	KEY_F2 = 60,
	KEY_F3 = 61,
	KEY_F4 = 62,
	KEY_F5 = 63,
	KEY_F6 = 64,
	KEY_F7 = 65,
	KEY_F8 = 66,
	KEY_F9 = 67,
	KEY_FIVE = 6,
	KEY_FOUR = 5,
	KEY_G = 34,
	KEY_H = 35,
	KEY_HASH = 43,
	KEY_HOME = 199,
	KEY_I = 23,
	KEY_INSERT = 210,
	KEY_J = 36,
	KEY_K = 37,
	KEY_L = 38,
	KEY_LEFTARROW = 51,
	KEY_LEFTBRACE = 26,
	KEY_LEFTCTRL = 29,
	KEY_LEFTSHIFT = 42,
	KEY_M = 50,
	KEY_MINUS = 12,
	KEY_N = 49,
	KEY_NINE = 10,
	KEY_O = 24,
	KEY_ONE = 2,
	KEY_P = 25,
	KEY_PGDN = 209,
	KEY_PGUP = 201,
	KEY_PRINTSCREEN = 183,
	KEY_Q = 16,
	KEY_QUESTIONMARK = 53,
	KEY_R = 19,
	KEY_RETURN = 28,
	KEY_RIGHTARROW = 52,
	KEY_RIGHTBRACE = 27,
	KEY_RIGHTCTRL = 157,
	KEY_RIGHTSHIFT = 54,
	KEY_RSINGLEQUOTE = 41,
	KEY_S = 31,
	KEY_SCROLLLOCK = 70,
	KEY_SEMICOLON = 39,
	KEY_SEVEN = 8,
	KEY_SIX = 7,
	KEY_SPACE = 57,
	KEY_T = 20,
	KEY_TAB = 15,
	KEY_THREE = 4,
	KEY_TWO = 3,
	KEY_U = 22,
	KEY_V = 47,
	KEY_W = 17,
	KEY_X = 45,
	KEY_Y = 21,
	KEY_Z = 44,
	KEY_ZERO = 11,
	KEY__NONE = 0,
};


enum PathType : unsigned char
{
	PATH_NONE      = 0x00,
	PATH_RUBBLE    = 0x01,
	PATH_POWERPATH = 0x02,
};

enum FallinType : unsigned char
{
	FALLIN_NONE            = 0x00,

	FALLIN_LOW             = 0x01,
	FALLIN_MEDIUM          = 0x02,
	FALLIN_HIGH            = 0x03,
	FALLIN_VERYHIGH        = 0x04,
	FALLIN_CAVEIN_LOW      = 0x05,
	FALLIN_CAVEIN_MEDIUM   = 0x06,
	FALLIN_CAVEIN_HIGH     = 0x07,
	FALLIN_CAVEIN_VERYHIGH = 0x08,
};

enum BubbleType : int
{
	BUBBLE__INVALID          = -1,

	BUBBLE_CANTDO            = 0,
	BUBBLE_IDLE              = 1,
	BUBBLE_COLLECTCRYSTAL    = 2,
	BUBBLE_COLLECTORE        = 3,
	BUBBLE_COLLECTSTUD       = 4,
	BUBBLE_COLLECTDYNAMITE   = 5,
	BUBBLE_COLLECTBARRIER    = 6,
	BUBBLE_COLLECTELECFENCE  = 7,
	BUBBLE_COLLECTDRILL      = 8,
	BUBBLE_COLLECTSPADE      = 9,
	BUBBLE_COLLECTHAMMER     = 10,
	BUBBLE_COLLECTSPANNER    = 11,
	BUBBLE_COLLECTLASER      = 12,
	BUBBLE_COLLECTPUSHER     = 13,
	BUBBLE_COLLECTFREEZER    = 14,
	BUBBLE_COLLECTBIRDSCARER = 15,
	BUBBLE_CARRYCRYSTAL      = 16,
	BUBBLE_CARRYORE          = 17,
	BUBBLE_CARRYSTUD         = 18,
	BUBBLE_CARRYDYNAMITE     = 19,
	BUBBLE_CARRYBARRIER      = 20,
	BUBBLE_CARRYELECFENCE    = 21,
	BUBBLE_GOTO              = 22,
	BUBBLE_DYNAMITE          = 23,
	BUBBLE_REINFORCE         = 24,
	BUBBLE_DRILL             = 25,
	BUBBLE_REPAIR            = 26,
	BUBBLE_DIG               = 27,
	BUBBLE_FLEE              = 28,
	BUBBLE_POWEROFF          = 29,
	BUBBLE_CALLTOARMS        = 30,
	BUBBLE_ELECFENCE         = 31,
	BUBBLE_EAT               = 32,
	BUBBLE_DRIVE             = 33,
	BUBBLE_UPGRADE           = 34,
	BUBBLE_BUILDPATH         = 35,
	BUBBLE_TRAIN             = 36,
	BUBBLE_RECHARGE          = 37,
	BUBBLE_REQUEST           = 38,
};

enum OreType : int
{
	ORE_NORMAL    = 0,
	ORE_PROCESSED = 1,
};

enum AbilityType : int
{
	ABILITY__INVALID = -1,

	ABILITY_PILOT    = 0,
	ABILITY_SAILOR   = 1,
	ABILITY_DRIVER   = 2,
	ABILITY_DYNAMITE = 3,
	ABILITY_REPAIR   = 4,
	ABILITY_SCANNER  = 5,
};

enum InfoType : int
{
	INFO__INVALID             = -1,

	INFO_CRYSTALFOUND         = 0,
	INFO_ORESEAMFOUND         = 1,
	INFO_ROCKMONSTER          = 2,
	INFO_LAVAROCKMONSTER      = 3,
	INFO_ICEROCKMONSTER       = 4,
	INFO_UNDERATTACK          = 5,
	INFO_LANDSLIDE            = 6,
	INFO_CAVEIN               = 7,
	INFO_CONSTRUCTED          = 8,
	INFO_CAVERNLOCATED        = 9,
	INFO_LEGOMANDEATH         = 10,
	INFO_VEHICLEDEATH         = 11,
	INFO_BUILDINGDEATH        = 12,
	INFO_DYNAMITEPLACED       = 13,
	INFO_NOPOWER              = 14,
	INFO_POWERDRAIN           = 15,
	INFO_AIRDEPLETING         = 16,
	INFO_AIRLOW               = 17,
	INFO_AIROUT               = 18,
	INFO_AIRRESTORED          = 19,
	INFO_TRAINDRIVER          = 20,
	INFO_TRAINDYNAMITE        = 21,
	INFO_TRAINREPAIR          = 22,
	INFO_TRAINPILOT           = 23,
	INFO_TRAINSAILOR          = 24,
	INFO_TRAINSCANNER         = 25,
	INFO_ORECOLLECTED         = 26,
	INFO_WALLDUG              = 27,
	INFO_WALLREINFORCED       = 28,
	INFO_CRYSTALPOWER         = 29,
	INFO_LAVAERODE            = 30,
	INFO_SLUGEMERGE           = 31,
	INFO_PATHCOMPLETED        = 32,
	INFO_FOUNDMINIFIGURE      = 33,
	INFO_CANUPGRADEMINIFIGURE = 34,
	INFO_CANTRAINMINIFIGURE   = 35,
	INFO_CRYSTALSEAMFOUND     = 36,
	INFO_GENERICSEAMFOUND     = 37,
	INFO_GENERICDEATH         = 38,
	INFO_GENERICMONSTER       = 39,
};

enum ActivityType : int
{
	ACTIVITY__INVALID            = -1,

	ACTIVITY_STAND               = 0,
	ACTIVITY_ROUTE               = 1,
	ACTIVITY_ROUTERUBBLE         = 2,
	ACTIVITY_RUNPANIC            = 3,
	ACTIVITY_DRILL               = 4,
	ACTIVITY_TELEPORT            = 5,
	ACTIVITY_WALK                = 6,
	ACTIVITY_REINFORCE           = 7,
	ACTIVITY_REVERSE             = 8,
	ACTIVITY_TURNLEFT            = 9,
	ACTIVITY_TURNRIGHT           = 10,
	ACTIVITY_CANTDO              = 11,
	ACTIVITY_EMERGE              = 12,
	ACTIVITY_ENTER               = 13,
	ACTIVITY_ENTERREIN           = 14,
	ACTIVITY_COLLECT             = 15,
	ACTIVITY_GATHER              = 16,
	ACTIVITY_CARRY               = 17,
	ACTIVITY_CARRYRUBBLE         = 18,
	ACTIVITY_THROW               = 19,
	ACTIVITY_CARRYTURNLEFT       = 20,
	ACTIVITY_CARRYTURNRIGHT      = 21,
	ACTIVITY_CARRYSTAND          = 22,
	ACTIVITY_HITLEFT             = 23,
	ACTIVITY_HITRIGHT            = 24,
	ACTIVITY_HITFRONT            = 25,
	ACTIVITY_HITBACK             = 26,
	ACTIVITY_HITHARD             = 27,
	ACTIVITY_DYNAMITE            = 28,
	ACTIVITY_DESPOSITE           = 29,
	ACTIVITY_CLEAR               = 30,
	ACTIVITY_PLACE               = 31,
	ACTIVITY_REPAIR              = 32,
	ACTIVITY_SLIP                = 33,
	ACTIVITY_REST                = 34,
	ACTIVITY_EAT                 = 35,
	ACTIVITY_STAMP               = 36,
	ACTIVITY_THROWMAN            = 37,
	ACTIVITY_THROWNBYROCKMONSTER = 38,
	ACTIVITY_GETUP               = 39,
	ACTIVITY_BUILDPATH           = 40,
	ACTIVITY_UPGRADE             = 41,
	ACTIVITY_EXPLODE             = 42,
	ACTIVITY_UNPOWERED           = 43,
	ACTIVITY_FIRELASER           = 44,
	ACTIVITY_FREEZED             = 45,
	ACTIVITY_FREEZESTART         = 46,
	ACTIVITY_FREEZEMELT          = 47,
	ACTIVITY_RECHARGE            = 48,
	ACTIVITY_WAKEUP              = 49,
	ACTIVITY_TRAIN               = 50,
	ACTIVITY_FLOATON             = 51,
	ACTIVITY_FLOATOFF            = 52,
	ACTIVITY_OPENING             = 53,
	ACTIVITY_CLOSING             = 54,
	ACTIVITY_OPEN                = 55,
	ACTIVITY_WAITING1            = 56,
	ACTIVITY_WAITING2            = 57,
	ACTIVITY_WAITING3            = 58,
	ACTIVITY_WAITING4            = 59,
	ACTIVITY_WAITING5            = 60,
	ACTIVITY_WAITING6            = 61,
	ACTIVITY_WAITING7            = 62,
	ACTIVITY_WAITING8            = 63,
	ACTIVITY_WAITING9            = 64,
	ACTIVITY_WAITING10           = 65,
	ACTIVITY_WAITING11           = 66,
	ACTIVITY_WAITING12           = 67,
	ACTIVITY_WAITING13           = 68,
	ACTIVITY_WAITING14           = 69,
	ACTIVITY_WAITING15           = 70,
	ACTIVITY_WAITING16           = 71,
	ACTIVITY_WAITING17           = 72,
	ACTIVITY_WAITING18           = 73,
	ACTIVITY_WAITING19           = 74,
	ACTIVITY_WAITING20           = 75,
	ACTIVITY_WAITING21           = 76,
	ACTIVITY_CRUMBLE             = 77,
	ACTIVITY_TELEPORTIN          = 78,
};

enum TextType : int
{
	TEXT__INVALID            = -1,

	TEXT_WALK                = 0,
	TEXT_DRILL               = 1,
	TEXT_NODRILL             = 2,
	TEXT_CANTDRILL           = 3,
	TEXT_REINFORCE           = 4,
	TEXT_NOREINFORCE         = 5,
	TEXT_CANTREINFORCE       = 6,
	TEXT_PICKUPCRYSTAL       = 7,
	TEXT_ENCYCLOPEDIA        = 8,
	TEXT_RADARHELP           = 9,
	TEXT_BUILDHELP           = 10,
	TEXT_SELECTIONHELP       = 11,
	TEXT_DRIVE               = 12,
	TEXT_CANTDRIVE           = 13,
	TEXT_MAKETELEPORTER      = 14,
	TEXT_CANNOTPLACEBUILDING = 15,
	TEXT_CRYSTALOREDISABLED  = 16,
	TEXT_CRYSTALFOUND        = 17,
	TEXT_CAVERNDISCOVERED    = 18,
	TEXT_OREFOUND            = 19,
	TEXT_AIRSUPPLYLOW        = 20,
	TEXT_AIRSUPPLYRUNNINGOUT = 21,
	TEXT_SPACETOCONTINUE     = 22,
	TEXT_GAMECOMPLETE        = 23,
	TEXT_MANTRAINED          = 24,
	TEXT_UNITUPGRADED        = 25,
};


struct ResourceData;
struct LiveObject;
struct LevelBlock;
struct Level;
struct FlockData;
struct LwoFrame;
struct FlockSubdata;
struct ResourceSubdata;
struct ActStruct_14;
struct CreatureData;
struct Struct_34;
struct ObjectStats;
struct UpgradeData;
struct ObjectUpgradePartData;
struct ObjectUpgradesData;
struct BuildingData;
struct PolyMeshData;
struct VehicleData;
struct Struct_830;
struct Struct_bc;
struct GameManager;
struct LevelStruct_3c;
struct LevelStruct_1c;
struct SurfaceMapStruct38;
struct ImageBMP;
struct SurfaceTextureGrid;
struct LevelSurfaceMap;
struct DirectXSurfaceTuple;
struct BlockPointer;
struct LevelData;
struct ObjectiveData;
struct ImageFont;
struct FileStream;
struct WADEntryStream;
struct LoaderProfileItem;
struct HelpWindowInfoLevels;
struct WADEntry;
struct WADFile;
struct RenderStateItem;
struct DeviceMode;
struct DriverMode;
struct ScreenMode;
struct SharedObjectResource;
struct ToolTipData;
struct ErodeState;
struct SharedTextureResource;
struct SharedFileBuffer;
struct MiscObjectDependencies;
struct SharedWADEntry;
struct ResourceManager;
struct NERPSFunctionSignature;
struct SampleProperty;
struct SampleData;
struct AudioPlaybackData;
struct NERPMessageSound;
struct AdvisorAnimData;
struct SelectedUnitHotkey;
struct BasicObjectData;
struct ItemStruct_428;
struct Struct_428;
struct MapFileInfo;
struct BlockObject;
struct Struct_b8__00558080;
struct Struct_8__00558bc4;
struct PairStruct_428;
struct SoundResource;
struct ResourceAppData;
struct ActFrameResource;
struct MessageAction;
struct ProMeshData;
struct LevelIdentifier;
struct Sound3DInstance;
struct LiveObjectInfo;
struct MiscObjectData;
struct StructF_10;
struct CFGProperty;


struct StructF_10 {
	float float_0;
	float float_4;
	undefined4 field_8;
	float float_c;
};
static_assert(sizeof(StructF_10) == 0x10, "");

struct LevelIdentifier {
	undefined4 field_0;
	undefined4 field_4;
	undefined4 field_8;
	undefined4 field_c;
	undefined4 field_10;
};
static_assert(sizeof(LevelIdentifier) == 0x14, "");

struct Sound3DInstance {
	int sampleIndex;
	IDirect3DRMFrame3* frame;
	Vector3F position;
	uint flags;
};
static_assert(sizeof(Sound3DInstance) == 0x18, "");

struct LiveObjectInfo {
	LiveObject* liveObj;
	BOOL intbool_4;
	Point2F point_8;
	Vector3F vector_10;
};
static_assert(sizeof(LiveObjectInfo) == 0x1c, "");

struct MiscObjectData {
	undefined field_0x0_0x30[0x30];
	ResourceData* resData; // LWS,true | LWO,true
	undefined field_0x34_0x38[0x4];
};
static_assert(sizeof(MiscObjectData) == 0x38, "");

struct ProMeshData {
	ResourceData* promesh_a;
	ResourceData* promesh_b;
	undefined4 table_a[100];
	undefined4 table_b[100];
	float BlockSize;
	undefined4 field_32c;
	undefined field_0x330_0x33c[0xc];
	SurfaceTextureGrid* surfTextGrid;
};
static_assert(sizeof(ProMeshData) == 0x340, "");

struct MessageAction {
	MessageType event;
	LiveObject* object_4;
	undefined4 field_8;
	undefined4 field_c;
	undefined4 field_10;
};
static_assert(sizeof(MessageAction) == 0x14, "");

struct ActFrameResource {
	ActFrameResource* previous;
	void* lwsStruct38; // LWS struct
	IDirect3DRMAnimationSet2* animSet; // (not LWS)
	BOOL isLWSFile;
	IDirect3DRMFrame3* rootFrame; // (not LWS)
	IDirect3DRMFrame3** framesTable; // (not LWS) table of COM objects, length is count_18
	uint framesCount; // (not LWS)
	undefined4 field_1c;
};
static_assert(sizeof(ActFrameResource) == 0x20, "");

struct ResourceAppData {
	ResourceData* resData;
	char* filename;
	char* frameName;
	undefined4 field_c;
	float float_10;
	float float_14;
	char* sampleName;
	ActFrameResource* actFrameRes;
	undefined4 field_20;
	SoundResource* soundRes;
};
static_assert(sizeof(ResourceAppData) == 0x28, "");


struct SoundResource {
	IDirectSound3DBuffer* sound3dBuffer;
	undefined4 field_4;
	undefined4 field_8;
	undefined4 field_c;
	SoundResource* previous;
};
static_assert(sizeof(SoundResource) == 0x14, "");

struct Struct_8__00558bc4 {
	LiveObject* object_0;
	float float_4;
};
static_assert(sizeof(Struct_8__00558bc4) == 0x8, "");

struct PairStruct_428 {
	Struct_428* first;
	Struct_428* second;
};
static_assert(sizeof(PairStruct_428) == 0x8, "");

struct Struct_b8__00558080 {
	undefined field_0x0_0xb8[0xb8];
};
static_assert(sizeof(Struct_b8__00558080) == 0xb8, "");

struct MapFileInfo {
	char Signature[4]; // "MAP "
	uint fileSize;
	Size2I dimensions;
	ushort blocks[1];
};
static_assert(sizeof(MapFileInfo) == 0x12, "");

struct BlockObject {
	LiveObject* attachedObject;
	Point2I position;
	undefined4 field_c;
	BlockObject* pool_m_next;
};
static_assert(sizeof(BlockObject) == 0x14, "");

struct ItemStruct_428 {
	uint index;
	Direction direction;
	undefined4 field_8;
	undefined4 field_c;
	undefined4 field_10;
	undefined4 field_14;
};
static_assert(sizeof(ItemStruct_428) == 0x18, "");

struct Struct_428 {
	Point2F points[100];
	uint pointsCount;
	ItemStruct_428 items[10];
	uint itemsCount;
	undefined4 field_418;
	undefined4 field_41c;
	undefined4 field_420;
	undefined4 field_424;
};
static_assert(sizeof(Struct_428) == 0x428, "");

struct BasicObjectData {
	int objIndex;
	ResourceData* aeResData; // ACT, true
};
static_assert(sizeof(BasicObjectData) == 0x8, "");



struct SelectedUnitHotkey {
	int field_0;
	int field_4;
	BOOL bool_8;
	int field_c;
	int field_10;
};
static_assert(sizeof(SelectedUnitHotkey) == 0x14, "");

struct AdvisorAnimData {
	ResourceData* resData;
	float loopStartTime; // ignored when not looping
	float loopEndTime; // ignored when not looping
};
static_assert(sizeof(AdvisorAnimData) == 0xc, "");

struct AudioPlaybackData {
	BOOL isUsed1; // paused/playing/used?
	WAVEFORMATEX* waveFormat; // hGlobal
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
static_assert(sizeof(AudioPlaybackData) == 0x5c, "");

struct NERPMessageSound {
	char* key;
	int sampleIndex;
};
static_assert(sizeof(NERPMessageSound) == 0x8, "");

struct SampleProperty {
	int sampleIndex;
	SampleProperty* next;
};
static_assert(sizeof(SampleProperty) == 0x8, "");

struct SampleData {
	char filename[260];
	uint length;
	uint avgBytesPerSec;
	uint frequency;
	int volume;
	undefined4 offset;
	HGLOBAL hGlobal_118;
	HGLOBAL hGlobal_11c;
	IDirectSoundBuffer* dSoundBuffer1;
	IDirectSoundBuffer* dSoundBuffer2;
	IDirectSoundBuffer* dSoundBuffer3;
	undefined4 bufferIndex;
	SampleFlags flags;
};
static_assert(sizeof(SampleData) == 0x134, "");


struct SharedWADEntry {
	void* fileData;
	BOOL isUsed;
	int wadIndex;
	int entryIndex;
};
static_assert(sizeof(SharedWADEntry) == 0x10, "");

struct SharedTextureResource {
	char* name;
	IDirect3DRMTexture3* texture;
};
static_assert(sizeof(SharedTextureResource) == 0x8, "");

struct ResourceManager {
	ResourceData* pool_g_TABLE[20]; // PTR_0076bd80
	ResourceData* pool_g_NEXT; // PTR_0076bd84
	ResourceData* pool_g_ROOT; // PTR_0076bd88
	char* Types_TABLE[9]; // PTR_0076bdd8
	char* Extensions_TABLE[9]; // PTR_0076bdfc
	char* CfgRootName; // PTR_0076be20
	undefined4 DAT_0076be24; // DAT_0076be24
	undefined4 field_a8; // DAT_0076be28
	undefined4 field_ac; // referenced by addr to get last item of g_Textures_TABLE
	undefined4 field_b0; // DAT_0076be30
	SharedTextureResource Textures_TABLE[1000]; // PTR_0076be34
	uint Textures_COUNT; // DAT_0076dd74
	pointer soundCallback; // PTR_0076dd78
	void* soundCallback_VALUE; // PTR_0076dd7c
	pointer drawCallback; // PTR_0076dd80
	void* drawCallback_VALUE; // PTR_0076dd84
	char* SharedTextures; // PTR_0076dd88
	uint SceneFogColor; // DAT_0076dd8c
	uint pool_g_COUNT; // DAT_0076dd90
	uint pool_g_INITFLAGS; // DAT_0076dd94
};
static_assert(sizeof(ResourceManager) == 0x2018, "");


struct NERPSFunctionSignature {
	char* name;
	int (*function)(int*);
	NERPSFunctionArgs arguments;
};
static_assert(sizeof(NERPSFunctionSignature) == 0xc, "");


struct MiscObjectDependencies {
	undefined4 field_0;
	uint levels_flags[16];
	undefined4 levels_field_44[16];
	undefined4 levels_field_84[16];
};
static_assert(sizeof(MiscObjectDependencies) == 0xc4, "");


struct SharedFileBuffer {
	void* fileData;
	FileBufferFlags flags; // 1 = isUsed
};
static_assert(sizeof(SharedFileBuffer) == 0x8, "");

struct ErodeState {
	undefined4 field_0;
	undefined4 field_4;
};
static_assert(sizeof(ErodeState) == 0x8, "");


struct ToolTipData {
	float float_0;
	char tooltipText[512];
	undefined field_0x204_0x25c[0x58];
	undefined4 field_25c;
	undefined4 field_260;
	undefined4 field_264;
	undefined4 field_268;
	undefined4 field_26c;
	ImageBMP* tooltipImage;
	undefined4 field_274;
	uint flags;
};
static_assert(sizeof(ToolTipData) == 0x27c, "");

struct SharedObjectResource {
	char* resName;
	Struct_34* lwoStruct34;
};
static_assert(sizeof(SharedObjectResource) == 0x8, "");

struct RenderStateItem { // The item's render state type is determined by the index in its table
	DWORD value;
	BOOL isUsed;
};
static_assert(sizeof(RenderStateItem) == 0x8, "");

struct ImageFont {
	ImageBMP* bitmap;
	undefined field_0x4_0xbe4[0xbe0];
	undefined4 field_be4;
	undefined field_0xbe8_0xbf0[0x8];
	ImageFont* pool_m_next;
};
static_assert(sizeof(ImageFont) == 0xbf4, "");

struct FileStream {
	FileLocation location;
	union {
		FILE* std; // Standard file stream
		WADEntryStream* wad; // WAD file stream
		//struct FILE* std; // Standard file stream
		//struct WADEntryStream* wad; // WAD file stream
	};
};
static_assert(sizeof(FileStream) == 0x8, "");

struct WADEntryStream {
	int sharedIndex;
	int position;
	undefined4 field_8;
};
static_assert(sizeof(WADEntryStream) == 0xc, "");


struct WADEntry { // WAD file entry metadata contained within LegoWADFile structure
	WADEntryFlags flags; // usually 1, 2 for RNC compression
	//undefined field_0x1;
	//undefined field_0x2;
	//undefined field_0x3;
	uint packedSize; // Compressed packed size
	uint origSize; // Original unpacked size (same as packedSize when uncompressed)
	uint offset; // absolute file offset
};
static_assert(sizeof(WADEntry) == 0x10, "");

struct WADFile { // LegoRR WAD File information
	undefined4 field_0;
	BOOL isUsed; // 1 if WAD is in-use
	undefined4 field_8;
	undefined4 field_c;
	FILE* file; // file I/O
	char** absdirs; // source file paths when WAD was built
	char** reldirs; // relative file paths inside WAD
	WADEntry* entries; // file entry metadata
	uint count; // number of file entries
};
static_assert(sizeof(WADFile) == 0x24, "");

struct LoaderProfileItem {
	char* name;
	undefined4 field_4;
	undefined4 field_8;
};
static_assert(sizeof(LoaderProfileItem) == 0xc, "");

struct SurfaceTextureGrid {
	Size2I gridSize;
	DirectXSurfaceTuple** gridSurfaces;
};
static_assert(sizeof(SurfaceTextureGrid) == 0xc, "");

struct HelpWindowInfoLevels {
	char* levels[16];
};
static_assert(sizeof(HelpWindowInfoLevels) == 0x40, "");

struct InterfaceMenuItem {
	int* parameters;
	uint numParams;
};
static_assert(sizeof(InterfaceMenuItem) == 0x8, "");

struct PTLProperty { // Property loaded from a level's PTL config file (contains lookup index for actions)
	MessageType eventIndex;
	MessageType actionIndex;
};
static_assert(sizeof(PTLProperty) == 0x8, "");

struct DriverMode {
	GUID guid;
	char displayName[256]; // "name (description)"
	DriverModeFlags flags;
};
static_assert(sizeof(DriverMode) == 0x114, "");

struct DeviceMode {
	GUID guid;
	char displayName[256]; // "name (description)"
	DeviceModeFlags flags;
};
static_assert(sizeof(DeviceMode) == 0x114, "");

struct ScreenMode {
	int screenWidth;
	int screenHeight;
	int bitDepth;
	char displayName[256]; // "WxH (BPP bit)", "WxH" (windowed)
	ScreenModeFlags flags;
};
static_assert(sizeof(ScreenMode) == 0x110, "");

struct ImageBMP {
	IDirectDrawSurface4* ddSurface; // IDirectDrawSurface4
	int width;
	int height;
	uint firstColor24;
	uint lastColor24;
	uint firstColorNative;
	uint flags; // 2 is font?
	ImageBMP* pool_m_next;
};
static_assert(sizeof(ImageBMP) == 0x20, "");

struct SurfaceMapStruct38 {
	undefined4 field_0;
	float float_4;
	undefined4 field_8;
	undefined4 field_c;
	undefined4 table_10[8];
	undefined field_0x30_0x34[0x4];
	uint flags;
};
static_assert(sizeof(SurfaceMapStruct38) == 0x38, "");

struct ObjectiveData {
	void* ObjectiveImage; // bmp
	int ObjectiveImage_width_x; // ???
	int ObjectiveImage_height_y; // ???
	void* ObjectiveAcheivedImage; // bmp
	int ObjectiveAcheivedImage_width_x; // ???
	int ObjectiveAcheivedImage_height_y; // ???
	void* ObjectiveFailedImage; // bmp
	int ObjectiveFailedImage_width_x; // ???
	int ObjectiveFailedImage_height_y; // ???
	void* ObjectiveAcheivedAVI; // ???
	int ObjectiveAcheivedAVI_width_x; // ???
	int ObjectiveAcheivedAVI_height_y; // ???
	undefined4 field_30;
	undefined4 field_34;
	int CrystalObjective; // number of crystals needed if non-zero
	int OreObjective; // number of ore needed if non-zero
	Point2I BlockObjective;
	float TimerObjective; // (mult: 25.0, flags, format: "time:HitTimeFailObjective")
	int ConstructionObjective_type;
	int ConstructionObjective_index;
};
static_assert(sizeof(ObjectiveData) == 0x54, "");

struct LevelData {
	char* levelName; // (format: "Levels::level")
	LevelSurfaceMap* surfaceMap;
	undefined4 field_8;
	undefined4 field_c;
	undefined4 field_10;
	Size2I dimensions;
	float BlockSize;
	float DigDepth;
	float RoofHeight;
	float RoughLevel;
	BOOL3 UseRoof;
	BOOL3 SafeCaverns;
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
	Size2I surfTextSize; // surface texture width and height
	SurfaceTextureGrid* surfTextGrid;
	undefined4 field_0x80;
	LevelStruct_3c* struct3c_84;
	LevelStruct_1c* terrain1c_88;
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
	char* NextLevel;
	LevelBlock* blocks; // grid of blocks [y][x]
	ObjectiveData objective;
	BOOL hasBlockPointers;
	BlockPointer* blockPointers[56];
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
	char* FullName; // (replace '_' with ' ')
	TextureType BoulderAnimation; // (texture index, hardcoded: Rock, Lava, Ice)
	float MaxStolen;
	LevelCompleteStatus status; // (init: 0) 2 is used for Crystal failure as well
	BOOL IsStartTeleportEnabled; // (! DisableStartTeleport)
};
static_assert(sizeof(LevelData) == 0x284, "");

struct BlockPointer {
	Point2I position;
	uint id;
};
static_assert(sizeof(BlockPointer) == 0xc, "");

struct DirectXSurfaceTuple {
	IDirectDrawSurface4* surface;
	IDirect3DRMTexture3* texture;
	undefined4 field_8;
};
static_assert(sizeof(DirectXSurfaceTuple) == 0xc, "");

struct LevelSurfaceMap { // size 0x73d4... dear god.... no...
	Size2I smallDimensions; // full map dimensions - 1
	Size2I dimensions; // full map dimensions
	float BlockSize;
	float RoughLevel;
	Size2F blockDimensions_neg; // smallDimensions * BlockSize * 0.5 (width is negative??)
	float float_20;
	ResourceData* resData_24;
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
	SurfaceMapStruct38 table38_719c[10];
	ResourceData* resData_73cc;
	undefined4 field_73d0;
};
static_assert(sizeof(LevelSurfaceMap) == 0x73d4, "");

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
static_assert(sizeof(LevelStruct_3c) == 0x3c, "");

struct GameManager {
	CFGProperty* LegoCfgRoot; // g_LegoCfgRoot
	char* CfgRootName; // g_CFG_ROOTPATH
	undefined4 field_8;
	undefined4 field_c;
	GraphicsQuality Quality; // g_GraphicsQuality
	LevelData* level; // g_LEVEL_STRUCTPTR_SIZE_284__005570d4
	ResourceData* resRoot; // DAT_005570d8
	void* ptr_1c; // PTR_005570dc
	undefined4 field_20; // DAT_005570e0
	Struct_bc* structbc_24; // PTR_005570e4
	Struct_bc* structbc_28; // DAT_005570e8
	Struct_bc* structbc_2c; // DAT_005570ec
	ResourceData* struct2c_30; // PTR_005570f0
	ResourceData* struct2c_34; // DAT_005570f4
	ResourceData* struct2c_38; // PTR_005570f8
	ResourceData* struct2c_3c; // PTR_005570fc
	ResourceData* struct2c_40; // PTR_00557100
	ResourceData* struct2c_44; // PTR_00557104
	ResourceData* struct2c_48; // PTR_00557108
	ResourceData* struct2c_4c; // PTR_0055710c
	float FPClipBlocks; // FLOAT_00557110
	float TVClipDist; // g_tvclipdist
	undefined4 field_58;
	undefined4 field_5c;
	undefined4 field_60;
	ImageFont* bmpFONT5_HI; // g_FONT_FONT5_HI
	ImageFont* bmpToolTipFont; // g_FONT_ToolTipFont
	ImageFont* bmpDeskTopFont; // g_FONT_DeskTopFont
	ImageFont* bmpfont5_HI; // g_FONT_font5_HI
	ImageFont* bmpMbriefFONT; // g_FONT_MbriefFONT
	ImageFont* bmpMbriefFONT2; // g_FONT_MbriefFONT2
	ImageFont* bmpRSFont; // g_FONT_RSFont
	Struct_830* struct830_80; // PTR_00557140
	Struct_830* struct830_84; // PTR_00557144
	float float_88; // FLOAT_00557148
	float float_8c; // FLOAT_0055714c
	float float_90; // FLOAT_00557150
	float float_94; // FLOAT_00557154
	BOOL bool_98; // BOOL_00557158
	float gameSpeed; // FLOAT_0055715c
	LiveObject* object_a0; // DAT_00557160
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
	char* ObjectNames_PowerCrystal; // g_ObjectNames_PowerCrystal
	char* ObjectNames_Ore; // g_ObjectNames_Ore
	char* ObjectNames_ProcessedOre; // g_ObjectNames_ProcessedOre
	char* ObjectNames_Dynamite; // g_ObjectNames_Dynamite
	char* ObjectNames_Barrier; // g_ObjectNames_Barrier
	char* ObjectNames_ElectricFence; // g_ObjectNames_ElectricFence
	char* ObjectNames_SpiderWeb; // g_ObjectNames_SpiderWeb
	char* ObjectNames_OohScary; // g_ObjectNames_OohScary
	char* ObjectNames_Path; // g_ObjectNames_Path
	char* ObjectTheNames_PowerCrystal; // g_ObjectTheNames_PowerCrystal
	char* ObjectTheNames_Ore; // g_ObjectTheNames_Ore
	char* ObjectTheNames_ProcessedOre; // g_ObjectTheNames_ProcessedOre
	char* ObjectTheNames_Dynamite; // g_ObjectTheNames_Dynamite
	char* ObjectTheNames_Barrier; // g_ObjectTheNames_Barrier
	char* ObjectTheNames_ElectricFence; // g_ObjectTheNames_ElectricFence
	char* ObjectTheNames_SpiderWeb; // g_ObjectTheNames_SpiderWeb
	char* ObjectTheNames_OohScary; // g_ObjectTheNames_OohScary
	char* ObjectTheNames_Path; // g_ObjectTheNames_Path
	VehicleData* VehicleData_TABLE; // g_VehicleData_TABLE
	CreatureData* MiniFigureData_TABLE; // g_MiniFigureData_TABLE
	CreatureData* RockMonsterData_TABLE; // g_RockMonsterData_TABLE
	BuildingData* BuildingData_TABLE; // g_BuildingData_TABLE
	UpgradeData* UpgradeData_TABLE; // g_UpgradeData_TABLE
	char** VehicleTypes_TABLE; // g_VehicleTypes_TABLE
	char** MiniFigureTypes_TABLE; // g_MiniFigureTypes_TABLE
	char** RockMonsterTypes_TABLE; // g_RockMonsterTypes_TABLE
	char** BuildingTypes_TABLE; // g_BuildingTypes_TABLE
	char** UpgradeTypes_TABLE; // g_UpgradeTypes_TABLE
	char* ToolTypes_TABLE[11]; // g_ToolTypes_TABLE
	char* ToolNames_TABLE[11]; // g_ToolNames_TABLE
	char** ObjectNames_VehicleTypes_TABLE; // g_ObjectNames_VehicleTypes_TABLE
	char** ObjectNames_MiniFigureTypes_TABLE; // g_ObjectNames_MiniFigureTypes_TABLE
	char** ObjectNames_RockMonsterTypes_TABLE; // g_ObjectNames_RockMonsterTypes_TABLE
	char** ObjectNames_BuildingTypes_TABLE; // g_ObjectNames_BuildingTypes_TABLE
	char** ObjectNames_UpgradeTypes_TABLE; // g_ObjectNames_UpgradeTypes_TABLE
	char** ObjectTheNames_VehicleTypes_TABLE; // g_ObjectTheNames_VehicleTypes_TABLE
	char** ObjectTheNames_MiniFigureTypes_TABLE; // g_ObjectTheNames_MiniFigureTypes_TABLE
	char** ObjectTheNames_RockMonsterTypes_TABLE; // g_ObjectTheNames_RockMonsterTypes_TABLE
	char** ObjectTheNames_BuildingTypes_TABLE; // g_ObjectTheNames_BuildingTypes_TABLE
	char** ObjectTheNames_UpgradeTypes_TABLE; // g_ObjectTheNames_UpgradeTypes_TABLE
	uint VehicleTypes_COUNT; // g_VehicleTypes_COUNT
	uint MiniFigureTypes_COUNT; // g_MiniFigureTypes_COUNT
	uint RockMonsterTypes_COUNT; // g_RockMonsterTypes_COUNT
	uint BuildingTypes_COUNT; // g_BuildingTypes_COUNT
	uint UpgradeTypes_COUNT; // g_UpgradeTypes_COUNT
	char* SurfaceTypes_TABLE[18]; // g_SurfaceTypes_TABLE
	char* SurfaceTypeDescriptions_name_TABLE[18]; // g_SurfaceTypeDescriptions_name_TABLE
	void* SurfaceTypeDescriptions_sound_TABLE[18]; // g_SurfaceTypeDescriptions_sound_TABLE
	ResourceData* RES_Boulder; // g_RES_BOULDER
	ResourceData* RES_BoulderExplode; // DAT_0055736c
	ResourceData* RES_BoulderExplodeIce; // DAT_00557370
	ResourceData* RES_Crystal; // g_RES_POWERCRYSTAL
	ResourceData* RES_Dynamite; // g_RES_DYNAMITE
	ResourceData* RES_Ores_TABLE[2]; // g_RES_ORES_TABLE
	ResourceData* RES_OohScary; // g_RES_OOHSCARY
	ResourceData* RES_Barrier; // g_RES_BARRIER
	ResourceData* RES_ElectricFence; // g_RES_ELECTRICFENCE
	ResourceData* RES_SpiderWeb; // g_RES_SPIDERWEB
	ResourceData* RES_RechargeSparkle; // DAT_00557394
	ResourceData* RES_MiniTeleportUp; // DAT_00557398
	ResourceData* RES_ElectricFenceStud; // DAT_0055739c
	ResourceData* RES_Pusher; // g_RES_PUSHER
	ResourceData* RES_Freezer; // g_RES_FREEZER
	ResourceData* RES_IceCube; // DAT_005573a8
	ResourceData* RES_SmashPath; // DAT_005573ac
	ResourceData* RES_LaserShot; // g_RES_LASERSHOT
	ResourceData** RES_2f4_TABLEUNK; // DAT_005573b4
	undefined4 table10_2f8[10]; // g_UNK_TABLE__005573b8
	uint count10_2fc; // UINT_005573e0
	float float_324; // FLOAT_005573e4
	float float_328; // FLOAT_005573e8
	float float_32c; // FLOAT_005573ec
	float float_330; // FLOAT_005573f0
	float tvTiltOrZoom_334;
	Point2F tvFaceDirection_338;
	float MedPolyRange; // g_MedPolyRange
	float HighPolyRange; // g_HighPolyRange
	int HPBlocks; // g_HPBlocks
	ColourRGBF FogColourRGB; // g_FogColourRGB
	ColourRGBF HighFogColourRGB; // g_HighFogColourRGB
	float float_364; // g_LEVEL_UNK_FLOAT_00557424
	ColourRGBF PowerCrystalRGB; // g_PowerCrystalRGB
	ColourRGBF UnpoweredCrystalRGB; // g_UnpoweredCrystalRGB
	ObjectType placeObjType; // INT_00557440
	int placeObjIndex; // INT_00557444
	Direction placeObjDirection; // INT_00557448
	LiveObject* placeDestSmallTeleporter; // PTR_0055744c
	LiveObject* placeDestBigTeleporter; // PTR_00557450
	LiveObject* placeDestWaterTeleporter; // PTR_00557454
	float MinEnergyForEat; // g_MinEnergyForEat
	ImageBMP* TutorialIcon; // bmp? PTR_0055745c
	undefined4 field_3a0;
	float DynamiteDamageRadius; // g_DynamiteDamageRadius
	float DynamiteMaxDamage; // g_DynamiteMaxDamage
	float DynamiteWakeRadius; // g_DynamiteWakeRadius
	float BirdScarerRadius; // g_BirdScarerRadius
	ObjectType objTeleportQueueTypes_TABLE[20]; // UNK_ARRAY_00557474
	int objTeleportQueueIndexes_TABLE[20]; // UNK_ARRAY_005574c4
	uint objTeleportQueue_COUNT; // count for above 2 arrays, UINT_00557514
	float MiniFigureRunAway; // g_MiniFigureRunAway
	Vector3F vector_45c; // FLOAT_0055751c
	undefined4 table200_468[200]; // UNK_ARRAY_00557528
	uint count_788; // UINT_00557848
	undefined4 table200_78c[200]; // UNK_ARRAY_0055784c
	undefined4 table200_aac[200]; // UNK_ARRAY_00557b6c
	uint count_dcc; // UINT_00557e8c
	uint count_dd0; // UINT_00557e90
	uint MaxReturnedCrystals; // g_MaxReturnedCrystals
	uint MouseScrollBorder; // g_MouseScrollBorder
	char* HealthText; // g_HealthText
	char* EnergyText; // g_EnergyText
	char* CrystalsText; // g_CrystalsText
	char* OreText; // g_OreText
	char* StudsText; // g_StudsText
	char* ToolsText; // g_ToolsText
	char* CarryObjectText; // g_CarryObjectText
	char* DrivenByText; // g_DrivenByText
	char* OreRequiredText; // g_OreRequiredText
	BOOL IsFallinsEnabled; // (! "NoFallins"), g_YesFallins
	float MinDistFor3DSoundsOnTopView; // g_MinDistFor3DSoundsOnTopView
	uint unkbool_308; // (may not be bool, compared with 0, and 1) g_GAME_UNK_BOOL_00557ec8
	GameFlags1 flags1; // g_GAME_GameFlags1
	GameFlags2 flags2; // g_GAME_GameFlags2
	GameFlags3 flags3; // only first byte is used(?), g_GAME_GameFlags3
	float InitialSlugTime; // g_InitialSlugTime
	Point2F NextButtonPos; // g_NextButton
	Point2F BackButtonPos; // g_BackButtonPos
	ImageBMP* NextButton; // bmp? PTR_00557eec
	ImageBMP* BackButton; // bmp? PTR_00557ef0
	ImageBMP* BackArrow; // bmp? PTR_00557ef4
	float FogRate; // g_LEVEL_FogRate
	float float_e3c; // FLOAT_00557efc
	float floatfps_e40; // assigned to Game_Update param_1 float fpsSync, FLOAT_00557f00
	float DrainTime; // g_DrainTime
	uint ReinforceHits; // g_ReinforceHits
	uint CDStartTrack; // g_CDStartTrack
	uint CDTracks; // g_CDTracks
	uint FallinMultiplier; // g_LEVEL_FallinMultiplier
	BOOL hasFallins; // BOOL_00557f18
	Point2F menuNextPoint; // DAT_00557f1c
	Point2F menuPrevPoint; // DAT_00557f24
	ColourRGBF DragBoxRGB; // g_DragBoxRGB
	ImageBMP* DialogImage; // PTR_00557f38
	ImageBMP* DialogContrastOverlay; // PTR_00557f3c
	void* drawregion_e80; // PTR_00557f40
	void* drawregion_e84; // PTR_00557f44
	void* drawregion_e88; // PTR_00557f48
	void* drawregion_e8c; // PTR_00557f4c
	char* CreditsTextFile; // g_CreditsTextFile
	char* CreditsBackAVI; // g_CreditsBackAVI
	char* UpgradeNames_TABLE[16]; // g_UpgradeNames_TABLE
	int BuildingUpgradeCostOre; // g_BuildingUpgradeCostOre
	int BuildingUpgradeCostStuds; // g_BuildingUpgradeCostStuds
	char* renameInput; // DAT_00557fa0
	float float_ee4; // FLOAT_00557fa4
	float float_ee8; // FLOAT_00557fa8
	char* RenameReplace; // g_RenameReplace
	char* EndGameAVI1; // g_EndGameAVI1
	char* EndGameAVI2; // g_EndGameAVI2
};
static_assert(sizeof(GameManager) == 0xef8, "");

struct CFGProperty
{
	/// INTERNAL:
	/*00,4*/ char* fileText; // the entire CFG file text (only stored for root property)
	/// PUBLIC:
	/*04,4*/ const char* key;   // init: NULL
	/*08,4*/ const char* value; // init: NULL
	/// INTERNAL:
	/*0c,4*/ unsigned int depth;    // init: 0 (if root)
	/*10,4*/ unsigned int field_10; // init: 0 (unknown usage)
	/*14,4*/ CFGProperty* next; // init: NULL
	/*18,4*/ CFGProperty* previous;  // init: NULL (if root)
	/*1c,4*/ CFGProperty* pool_m_next;
	/*20*/
};
static_assert(sizeof(CFGProperty) == 0x20, "");

struct Struct_bc {
	undefined4 mode_0;
	LiveObject* object_4;
	float float_8;
	float float_c;
	float float_10;
	undefined4 field_14;
	Vector3F vector_18;
	ResourceData* resData_24;
	ResourceData* resData_28;
	ResourceData* resData_2c;
	ResourceData* resData_30;
	undefined4 tableunk_34;
	undefined field_0x38_0x90[0x58];
	float float_90;
	undefined field_0x94_0xa0[0xc];
	Vector3F vector_a0;
	Vector3F vector_ac;
	uint flags;
};
static_assert(sizeof(Struct_bc) == 0xbc, "");

struct Struct_830 { // Probably a text rendering area
	ImageFont* font;
	Rect2F area;
	void* allocData;
	undefined field_0x18_0x418[0x400];
	uint allocSize;
	undefined field_0x41c_0x82c[0x410];
	uint flags;
};
static_assert(sizeof(Struct_830) == 0x830, "");

struct LwoFrame {
	uint dwSize;
	undefined field_0x4_0x64[0x60];
	undefined4 field_64;
	undefined field_0x68_0x6c[0x4];
	uint flags;
};
static_assert(sizeof(LwoFrame) == 0x70, "");

struct ObjectUpgradePartData {
	uint level;
	int NullInstance;
	char* NullObjectName;
	char* WeaponName;
	UpgradeData* upgradeData;
};
static_assert(sizeof(ObjectUpgradePartData) == 0x14, "");

struct FlockSubdata {
	Vector3F vector_0;
	Vector3F vector_c;
	Vector3F vector_18;
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
	ResourceData* resData_98;
	FlockSubdata* subdataNext_9c;
};
static_assert(sizeof(FlockSubdata) == 0xa0, "");

struct ObjectUpgradesData {
	ObjectUpgradePartData* parts; // always ObjectUpgradePartData[200]
	uint count;
	int currentLevel;
	uint levelsMask; // [carry][scan][speed][drill]
	LiveObject** upgradeObjs;
};
static_assert(sizeof(ObjectUpgradesData) == 0x14, "");

struct BuildingData {
	int objIndex;
	ResourceData* aeResData; // ACT, true
	char* CarryNullName;
	char* CameraNullName;
	char* DepositNullName;
	char* EntranceNullName;
	char* ToolNullName;
	char* FireNullName; // "fire laser"
	char* yPivot;
	char* xPivot;
	undefined4 carryFramesTable_28[6];
	undefined4 cameraFramesTable_40[4];
	undefined field_0x50_0x68[0x18];
	undefined4 field_68;
	undefined4 field_6c;
	uint CarryNullFrames;
	uint CameraNullFrames;
	uint ToolNullFrames;
	ResourceData* PowerLevelScene; // LWS, true
	undefined4 field_80;
	Point2I* shapePoints; // Point2I[10]
	uint shapeCount;
	ObjectUpgradesData upgrades;
	undefined field_0xa0_0xd0[0x30];
	float PivotMaxZ;
	float PivotMinZ;
	undefined field_0xd8_0x144[0x6c];
	uint count_144;
	uint flags;
};
static_assert(sizeof(BuildingData) == 0x14c, "");


struct PolyMeshData {
	undefined4 field_0;
	undefined4 field_4;
	char* partName; // name of LoadObject file.lwo
	uint index;
	int int_10;
	PolyMeshData* previous;
};
static_assert(sizeof(PolyMeshData) == 0x18, "");

struct VehicleData {
	int objIndex;
	char* WheelNullName;
	ResourceData* aeResData1;
	ResourceData* aeResData2; // Optional second ae file (seen for Grannit Grinder legs)
	ResourceData* WheelMeshes[6]; // LWO, false
	undefined4 wheel_fields_28[6];
	uint numWheelNulls;
	undefined field_0x44_0x5c[0x18];
	undefined4 field_5c;
	undefined4 field_60;
	float float_64;
	float WheelRadius;
	undefined field_0x6c_0xb4[0x48];
	char* DrillNullName;
	char* DepositNullName;
	char* FireNullName; // "fire laser"
	char* DriverNullName;
	char* yPivot;
	char* xPivot;
	undefined4 field_cc;
	undefined4 field_d0;
	ResourceData* resData_d4;
	BOOL3 CameraFlipDir;
	char* CarryNullName;
	char* CameraNullName;
	undefined4 carryFramesTable_e4[7];
	undefined field_0x100_0x10c[0xc];
	undefined4 cameraFramesTable_10c[4];
	uint CarryNullFrames;
	uint CameraNullFrames;
	ObjectUpgradesData upgrades;
	undefined field_0x138_0x168[0x30];
	float PivotMaxZ;
	float PivotMinZ;
	undefined field_0x170_0x1c4[0x54];
	undefined4 table6_1c4[6];
	undefined4 field_1dc;
	PolyMeshData* subdata_1e0;
	PolyMeshData* subdata_1e4;
	uint flags; // HoldMissing TRUE -> 0x8
};
static_assert(sizeof(VehicleData) == 0x1ec, "");


struct FlockData {
	FlockSubdata* flocksSubdata1;
	FlockSubdata* flocksSubdata2;
	uint numSubdata;
	uint hasVector1;
	uint hasVector2;
	undefined4 field_14;
	undefined4 field_18;
	undefined4 field_1c;
	undefined4 field_20;
	undefined4 field_24;
};
static_assert(sizeof(FlockData) == 0x28, "");

struct Struct_34 {
	uint count_0; // seems to be a count
	undefined4 field_4;
	LwoFrame* lwoTable_8; // table ptr? -> 0x10 (struct: 0x70)
	IDirect3DRMUserVisual* userVisual_c;
	IDirect3DRMViewport2* viewport_10; // IDirect3DRMViewport2 ?
	undefined4 param4_14;
	undefined4 unkFlags3_18;
	void* ptr_1c;
	uint refCount_20;
	Struct_34* struct34_24;
	IDirect3DRMFrame3* frame_28;
	uint flags;
	Struct_34* pool_m_next;
};
static_assert(sizeof(Struct_34) == 0x34, "");

struct ResourceSubdata {
	char* name;
	IDirect3DRMLight* light;
	IDirect3DRMMesh* mesh;
	Struct_34* struct34_c;
};
static_assert(sizeof(ResourceSubdata) == 0x10, "");

struct ActStruct_14 { // structure assigned to ResourceData->field_24 (allocated for ACT,ANIM resource types)
	ResourceData* resData; // (init: source of DuplicateResource)
	undefined4 field_4; // (init: 0)
	undefined4 field_8; // (init: 0)
	IDirect3DRMFrame3* frame; // (init: ResourceData->frame2)
	BOOL isUsed; // (init: 1)
};
static_assert(sizeof(ActStruct_14) == 0x14, "");

struct ResourceData {
	IDirect3DRMFrame3* frame1;
	IDirect3DRMFrame3* frame2;
	IDirect3DRMFrame3* frame3;
	ResourceSubdata* subdata_c;
	ResourceType resType;
	ResourceDataFlags flags;
	undefined4 field_18;
	undefined4 field_1c;
	LiveObject* ownerObj;
	ActStruct_14* actstruct_24;
	ResourceData* pool_m_next;
};
static_assert(sizeof(ResourceData) == 0x2c, "");

// related to Terrain map?
struct LevelStruct_1c
{
	ResourceData* resData;
	Point2I position;
	undefined4 field_c;
	LevelStruct_1c* next;
	LevelStruct_1c* previous;
	BOOL bool_18;
};
static_assert(sizeof(LevelStruct_1c) == 0x1c, "");

struct LevelBlock {
	PredugType predug;
	SurfaceTexture texture;
	TerrainType terrain;
	byte field_3;
	byte blockpointer;
	CryOreType cryOre;
	ErodeType erodeSpeed;
	byte field_7;
	LevelBlockFlags1 flags1;
	LevelBlockFlags2 flags2;
	undefined4 field_10;
	float float_14;
	LevelStruct_1c* struct1c_18;
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
static_assert(sizeof(LevelBlock) == 0x48, "");


struct CreatureData {
	int objIndex;
	ResourceData* aeResData; // ACT, true
	undefined4 field_8;
	undefined field_0xc_0x20[0x14];
	char* CameraNullName;
	uint CameraNullFrames;
	BOOL3 CameraFlipDir;
	char* DrillNullName;
	char* FootStepNullName;
	char* CarryNullName;
	char* ThrowNullName;
	char* DepositNullName;
	undefined4 field_40;
	undefined4 field_44;
	ResourceData* resData_48;
	undefined4 field_4c;
	undefined4 field_50;
	undefined4 cameraFramesTable_54[4];
	PolyMeshData* subdata_64;
	PolyMeshData* subdata_68;
	PolyMeshData* subdata_6c;
	uint flags;
};
static_assert(sizeof(CreatureData) == 0x74, "");


struct AITaskData {
	AITaskType taskType;
	undefined4 field_4;
	Point2I position;
	LiveObject* object_10;
	float unkExpiryTime;
	float float_18;
	uint priorityValue;
	ObjectType objType;
	int objIndex;
	int objLevel;
	undefined4 field_2c;
	Point2F pointf_30; // probably a table
	undefined field_0x38_0x3c[0x4];
	undefined4 mode_3c;
	void* ptr_40;
	undefined field_0x44_0x48[0x4];
	LiveObject* object_48;
	AIPriorityType priorityType;
	uint taskStartTime;
	undefined field_0x54_0x5c[0x8];
	uint flags_5c; // not set means ptr_40 is assigned
	AITaskData* next; // assigned to DAT_004b4358
	AITaskData* pool_m_next;
};
static_assert(sizeof(AITaskData) == 0x68, "");

struct LiveObject {
	ObjectType objType;
	int objIndex;
	char* customName; // max size is 11 (NOT null-terminated)
	VehicleData* vehicle;
	CreatureData* miniFigure;
	CreatureData* rockMonster;
	BuildingData* building;
	ResourceData* other;
	UpgradeData* upgrade;
	void* routeptr_24; // Unknown pointer, likely in large allocated table
	uint routingBlocksTotal; // total blocks to travel for current route
	uint routingBlocksCurrent; // number of blocks traveled (up to routingBlocksTotal)
	int value_30; // Usually 50 (0x32)
	float floats_34[100];
	float floats_1c4[50];
	Vector3F vector_28c;
	Point2F point_298;
	Vector3F vector_2a0;
	Vector3F faceDirection; // 1.0 to -1.0 directions that determine rotation with atan2
	float float_2b8;
	undefined4 field_2bc;
	undefined4 field_2c0;
	undefined4 field_2c4;
	undefined4 field_2c8;
	undefined4 field_2cc;
	undefined4 field_2d0;
	float float_2d4;
	BOOL unkbool_2d8;
	ResourceData* resData_2dc;
	int index_2e0;
	ResourceData* resData_2e4;
	char* aitaskName1;
	char* aitaskName2;
	AITaskData* aitask_2f0;
	Point2F point_2f4; // (assigned -1.0f)
	LiveObject* object_2fc; // other half of object_300
	LiveObject* object_300; // other half of object_2fc
	LiveObject* carryingThisObject;
	LiveObject* carriedObjects[7];
	uint numCarriedObjects;
	uint field_328;
	FlockData* flocksData_32c;
	uint objLevel;
	ObjectStats* stats;
	float float_338;
	float float_33c;
	float health; // (assigned -1.0f)
	float energy; // (assigned -1.0f)
	int* tableptr_348; // element size is 0x4
	BOOL mode_34c;
	undefined4 field_350;
	undefined4 field_354;
	undefined4 field_358;
	undefined4 field_35c;
	undefined4 field_360;
	undefined4 field_364;
	undefined4 field_368;
	LiveObject* drivenObject; // same as drivingThisObject
	ToolType carriedTools[5];
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
	LiveObject* object_3c0;
	undefined4 field_3c4;
	undefined4 field_3c8;
	LiveObject* object_3cc;
	undefined4 field_3d0;
	float elapsedTime1; // elapsed time counter 1
	float elapsedTime2; // elapsed time counter 2
	float activityElapsedTime; // elapsed time since last order?
	LiveFlags1 flags1_3e0;
	LiveFlags2 flags2_3e4;
	LiveFlags3 flags3_3e8; // (assigned 0, flags?)
	LiveFlags4 flags4_3ec;
	LiveFlags5 flags5_3f0; // (assigned 0, flags?)
	undefined4 field_3f4;
	undefined4 field_3f8;
	undefined4 field_3fc;
	undefined4 field_400;
	undefined4 field_404;
	LiveObject* pool_m_next;
};
static_assert(sizeof(LiveObject) == 0x40c, "");

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
	Size2F CollBox; // (requires: invalid/no CollRadius, effect: flag 0x100, CollRadius = min(w,h) * 0.5)
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
	ObjectStatsFlags1 flags1;
	ObjectStatsFlags2 flags2;
	ObjectStatsFlags3 flags3;
};
static_assert(sizeof(ObjectStats) == 0x150, "");




#pragma pack(pop)



}