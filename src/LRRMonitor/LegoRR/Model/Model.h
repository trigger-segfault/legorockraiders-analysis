#pragma once
#include "../Common.h"
#include "GhidraTypes.h"

#include "BasicEnums.h"
#include "BasicTypes.h"

namespace lego {


#pragma pack(push, 1)

typedef BOOL (__cdecl* GameInitFunction)(void);
typedef BOOL (__cdecl* GameUpdateFunction)(float elapsed); // float argument is elapsed game time units since last update
typedef void (__cdecl* GameCleanupFunction)(void);

struct GameFunctions
{
	/*0,4*/ GameInitFunction Init;
	/*4,4*/ GameUpdateFunction Update;
	/*8,4*/ GameCleanupFunction Cleanup;
	/*c*/
};
static_assert(sizeof(GameFunctions) == 0xc, "");

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
static_assert(sizeof(ObjectType) == 0x4, "");

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
static_assert(sizeof(ToolType) == 0x4, "");

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
static_assert(sizeof(ResourceType) == 0x4, "");

enum PredugType : unsigned char
{
	PREDUG_WALL             = 0x00, // Undug wall (in exposed or hidden cavern)
	PREDUG_EXPOSED          = 0x01, // Exposed tile
	PREDUG_HIDDEN           = 0x02, // Undiscovered cavern tile
	PREDUG_EXPOSED_SLUGHOLE = 0x03, // Exposed Slimy Slug Hole
	PREDUG_HIDDEN_SLUGHOLE  = 0x04, // Undiscovered cavern Slimy Slug Hole
};
static_assert(sizeof(PredugType) == 0x1, "");

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
static_assert(sizeof(SurfaceTexture) == 0x1, "");

enum TerrainType : unsigned char
{
	TERRAIN_TUNNEL       = 0x00, // Tunnel (ceiling)
	TERRAIN_IMMOVABLE    = 0x01, // Immovable "Solid" wall
	TERRAIN_HARD         = 0x02, // Hard wall
	TERRAIN_MEDIUM       = 0x03, // Medium "Loose" wall
	TERRAIN_LOOSE        = 0x04, // Loose "Dirt" wall
	TERRAIN_SOIL         = 0x05, // [unused] Soil wall
	TERRAIN_LAVA         = 0x06, // Lava lake
	TERRAIN_WATER_unused = 0x07, // [unused] "flood water"
	TERRAIN_ORESEAM      = 0x08, // Ore Seam wall
	TERRAIN_LAKE         = 0x09, // Lake "Water"
	TERRAIN_CRYSTALSEAM  = 0x0a, // "Energy" Crystal Seam wall
	TERRAIN_RECHARGESEAM = 0x0b, // Recharge Seam wall
	TERRAIN_RUBBLE       = 0x0c, // Rubble pile (at any level)
	TERRAIN_REINFORCED   = 0x0d, // Reinforced wall type
	TERRAIN_PATH         = 0x0e, // Power Path (TODO: does this include Building Power Path plates?)
	TERRAIN_SLUGHOLE     = 0x0f, // Slimy Slug Hole
	TERRAIN_UNDISCOVERED = 0x10, // Undiscovered Cavern
	TERRAIN_CAVERN       = 0x11, // Exposed Cavern "Cavern floor"
};
static_assert(sizeof(TerrainType) == 0x1, "");

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
	
	CRYORE_NONE           = 0x00,

	CRYORE_LV0_CRYSTAL_1  = 0x01,
	CRYORE_LV0_ORE_1      = 0x02,
	CRYORE_LV1_CRYSTAL_1  = 0x03,
	CRYORE_LV1_ORE_1      = 0x04,

	CRYORE_LV0_CRYSTAL_3  = 0x05,
	CRYORE_LV0_ORE_3      = 0x06,
	CRYORE_LV1_CRYSTAL_3  = 0x07,
	CRYORE_LV1_ORE_3      = 0x08,

	CRYORE_LV0_CRYSTAL_5  = 0x09,
	CRYORE_LV0_ORE_5      = 0x0a,
	CRYORE_LV1_CRYSTAL_5  = 0x0b,
	CRYORE_LV1_ORE_5      = 0x0c,

	CRYORE_LV0_CRYSTAL_10 = 0x0d,
	CRYORE_LV0_ORE_10     = 0x0e,
	CRYORE_LV1_CRYSTAL_10 = 0x0f,
	CRYORE_LV1_ORE_10     = 0x10,

	CRYORE_LV0_CRYSTAL_25 = 0x11,
	CRYORE_LV0_ORE_25     = 0x12,
	CRYORE_LV1_CRYSTAL_25 = 0x13,
	CRYORE_LV1_ORE_25     = 0x14,
};
static_assert(sizeof(CryOreType) == 0x1, "");

enum ErodeType : unsigned char
{
	ERODE_NONE            = 0x00,

	ERODE_VERYSLOW_LAVA   = 0x01,
	ERODE_VERYSLOW_ALWAYS = 0x02,
	ERODE_SLOW_LAVA       = 0x03,
	ERODE_SLOW_ALWAYS     = 0x04,
	ERODE_MEDIUM_LAVA     = 0x05,
	ERODE_MEDIUM_ALWAYS   = 0x06,
	ERODE_FAST_LAVA       = 0x07,
	ERODE_FAST_ALWAYS     = 0x08,
	ERODE_VERYFAST_LAVA   = 0x09,
	ERODE_VERYFAST_ALWAYS = 0x0a,
};
static_assert(sizeof(ErodeType) == 0x1, "");

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
static_assert(sizeof(LevelBlockFlags1) == 0x4, "");

enum LevelBlockFlags2 : unsigned int
{
	BLOCK2_NONE = 0,

	BLOCK2_SLUGHOLE_EXPOSED = 0x20,
	BLOCK2_EMERGE_POINT     = 0x40,
	BLOCK2_EMERGE_TRIGGER   = 0x80,

	BLOCK2_SLUGHOLE_HIDDEN  = 0x200,
};
DEFINE_ENUM_FLAG_OPERATORS(LevelBlockFlags2)
static_assert(sizeof(LevelBlockFlags2) == 0x4, "");


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
static_assert(sizeof(ResourceDataFlags) == 0x4, "");



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
static_assert(sizeof(LiveFlags1) == 0x4, "");

enum LiveFlags2 : unsigned int
{
	LIVEOBJ2_NONE        = 0,

	LIVEOBJ2_DRIVING     = 0x8,

	LIVEOBJ2_TRAINING    = 0x400,
	LIVEOBJ2_UNK_800     = 0x800,

	LIVEOBJ2_UPGRADING   = 0x8000,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags2)
static_assert(sizeof(LiveFlags2) == 0x4, "");

enum LiveFlags3 : unsigned int
{
	LIVEOBJ3_NONE         = 0,

	LIVEOBJ3_SIMPLEOBJECT = 0x20000,

	LIVEOBJ3_UNK_80000    = 0x80000,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags3)
static_assert(sizeof(LiveFlags3) == 0x4, "");

enum LiveFlags4 : unsigned int
{
	LIVEOBJ4_NONE = 0,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags4)
static_assert(sizeof(LiveFlags4) == 0x4, "");

enum LiveFlags5 : unsigned int
{
	LIVEOBJ5_NONE = 0,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags5)
static_assert(sizeof(LiveFlags5) == 0x4, "");


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
static_assert(sizeof(AITaskType) == 0x4, "");

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
static_assert(sizeof(AIPriorityType) == 0x4, "");

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
static_assert(sizeof(ObjectStatsFlags1) == 0x4, "");

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
static_assert(sizeof(ObjectStatsFlags2) == 0x4, "");

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
static_assert(sizeof(ObjectStatsFlags3) == 0x4, "");


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
static_assert(sizeof(GraphicsQuality) == 0x4, "");


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
static_assert(sizeof(GameFlags1) == 0x4, "");

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
static_assert(sizeof(GameFlags2) == 0x4, "");

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
static_assert(sizeof(GameFlags3) == 0x4, "");

enum TextureType : int
{
	TEXTURES__INVALID = -1,

	TEXTURES_ROCK = 0,
	TEXTURES_LAVA = 1,
	TEXTURES_ICE  = 2,
};
static_assert(sizeof(TextureType) == 0x4, "");

enum LevelCompleteStatus : int
{
	LEVELSTATUS_NONE            = 0,
	LEVELSTATUS_COMPLETE        = 1,
	LEVELSTATUS_FAILED          = 2,
	LEVELSTATUS_FAILED_CRYSTALS = 3,
	LEVELSTATUS_FAILED_OTHER    = 4,
};
static_assert(sizeof(LevelCompleteStatus) == 0x4, "");

// Location of a lego File stream (WAD or REAL)
// Same as BOOL3
enum FileLocation : int
{
	FILELOC_WAD   = 0,
	FILELOC_STD   = 1,
	FILELOC_ERROR = 2,
};
static_assert(sizeof(FileLocation) == 0x4, "");

enum DriverModeFlags : unsigned int
{
	DRIVERMODE_NONE      = 0,

	DRIVERMODE_ISUSED    = 0x1,

	DRIVERMODE_NOGUID_10 = 0x10,
	DRIVERMODE_NOGUID_20 = 0x20,
};
DEFINE_ENUM_FLAG_OPERATORS(DriverModeFlags)
static_assert(sizeof(DriverModeFlags) == 0x4, "");

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
static_assert(sizeof(DeviceModeFlags) == 0x4, "");

enum ScreenModeFlags : unsigned int
{
	SCREENMODE_NONE   = 0,

	SCREENMODE_ISUSED = 0x1,
};
DEFINE_ENUM_FLAG_OPERATORS(ScreenModeFlags)
static_assert(sizeof(ScreenModeFlags) == 0x4, "");

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
static_assert(sizeof(MessageType) == 0x4, "");


enum WADEntryFlags : unsigned int
{
	WADENTRY_NONE            = 0,

	WADENTRY_UNK_STORE       = 0x1,
	WADENTRY_RNC_COMPRESSION = 0x2,
};
DEFINE_ENUM_FLAG_OPERATORS(WADEntryFlags)
static_assert(sizeof(WADEntryFlags) == 0x4, "");

enum FileBufferFlags : unsigned int
{
	FILEBUFFER_NONE   = 0,

	FILEBUFFER_ISUSED = 0x1,
};
DEFINE_ENUM_FLAG_OPERATORS(FileBufferFlags)
static_assert(sizeof(FileBufferFlags) == 0x4, "");

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
static_assert(sizeof(NERPSFunctionArgs) == 0x4, "");

enum SampleFlags : unsigned int
{
	SAMPLE_NONE     = 0,

	SAMPLE_ISUSED   = 0x1,
	SAMPLE_VOLUME   = 0x2,
	SAMPLE_MULTIPLE = 0x4,
	SAMPLE_STREAMED = 0x8,
};
DEFINE_ENUM_FLAG_OPERATORS(SampleFlags)
static_assert(sizeof(SampleFlags) == 0x4, "");

enum ResourceManagerFlags : unsigned int
{
	RESMANAGER_NONE          = 0,

	RESMANAGER_ISINIT        = 0x1,

	RESMANAGER_SOUNDCALLBACK = 0x40,
};
DEFINE_ENUM_FLAG_OPERATORS(ResourceManagerFlags)
static_assert(sizeof(ResourceManagerFlags) == 0x4, "");

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
static_assert(sizeof(TrainedFlags) == 0x4, "");

enum AudioFlags : unsigned int
{
	AUDIO_NONE    = 0,

	AUDIO_SOUNDON = 0x1,
	AUDIO_UNK_2   = 0x2,

	AUDIO_UNK_8   = 0x8,
};
DEFINE_ENUM_FLAG_OPERATORS(AudioFlags)
static_assert(sizeof(AudioFlags) == 0x4, "");

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
static_assert(sizeof(ObjectiveFlags) == 0x4, "");

enum ObjInfoFlags : unsigned int
{
	OBJINFO_BUBBLEIMAGES = 16,
	OBJINFO_HEALTHBAR = 2,
	OBJINFO_HEALTHBAR_VERTICAL = 8,
	OBJINFO_HUNGERIMAGES = 1,
	OBJINFO_NONE = 0
};
DEFINE_ENUM_FLAG_OPERATORS(ObjInfoFlags)
static_assert(sizeof(ObjInfoFlags) == 0x4, "");

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
	MENUITEM__INVALID   = -1,

	MENUITEM_CYCLE      = 0,
	MENUITEM_TRIGGER    = 1,
	MENUITEM_TEXTINPUT  = 2,
	MENUITEM_SLIDER     = 3,
	MENUITEM_REALSLIDER = 4,
	MENUITEM_NEXT       = 5,
};
static_assert(sizeof(MenuItemType) == 0x4, "");


enum AdvisorType : int
{
	ADVISOR__INVALID                         = -1,

	ADVISOR_OBJECTIVE                        = 0,
	ADVISOR_OBJECTIVEACHIEVED                = 1,
	ADVISOR_OBJECTIVEFAILED                  = 2,
	ADVISOR_ICONPOINT_NORMAL                 = 3,
	ADVISOR_ICONPOINT_BACKBUTTON             = 4,
	ADVISOR_ICONPOINT_TOPBUTTONS             = 5,
	ADVISOR_PANELPOINT_RADARTOGGLE           = 6,
	ADVISOR_PANELPOINT_RADARTOGGLEOBJECTVIEW = 7,
	ADVISOR_PANELPOINT_RADARZOOMIN           = 8,
	ADVISOR_PANELPOINT_RADARZOOMOUT          = 9,
	ADVISOR_PANELPOINT_RADARMAPVIEW          = 10,
	ADVISOR_PANELPOINT_INFODOCKGOTO          = 11,
	ADVISOR_PANELPOINT_INFODOCKCLOSE         = 12,
	ADVISOR_PANELPOINT_TOPPANELINFO          = 13,
	ADVISOR_PANELPOINT_TOPPANELOPTIONS       = 14,
	ADVISOR_PANELPOINT_TOPPANELPRIORITIES    = 15,
	ADVISOR_PANELPOINT_TOPPANELCALLTOARMS    = 16,
	ADVISOR_PANELPOINT_TOPPANELGOBACK        = 17,
	ADVISOR_PANELPOINT_CONTROLZOOMIN         = 18,
	ADVISOR_PANELPOINT_CONTROLZOOMOUT        = 19,
	ADVISOR_TALKINGAME                       = 20,
};
static_assert(sizeof(AdvisorType) == 0x4, "");


enum RegistryType : unsigned int
{
	REGISTRY_STRING = 0,
	REGISTRY_NUMBER = 1,
};
static_assert(sizeof(RegistryType) == 0x4, "");

enum PolyMode : int
{
	POLY_LOW    = 0,
	POLY_MEDIUM = 1,
	POLY_HIGH   = 2,
	POLY_FP     = 3,
};
static_assert(sizeof(PolyMode) == 0x4, "");

enum SurfaceType : int
{
	SURFACE__INVALID      = -1,

	SURFACE_TUNNEL        = 0,
	SURFACE_IMMOVABLE     = 1,
	SURFACE_HARD          = 2,
	SURFACE_MEDIUM        = 3,
	SURFACE_LOOSE         = 4,
	SURFACE_SOIL          = 5,
	SURFACE_LAVA          = 6,
	SURFACE_WATER_unused  = 7,
	SURFACE_ORESEAM       = 8,
	SURFACE_LAKE          = 9,
	SURFACE_CRYSTALSEAM   = 10,
	SURFACE_RECHARGESEAM  = 11,
	SURFACE_RUBBLE        = 12,
	SURFACE_REINFORCEMENT = 13,
	SURFACE_PATH          = 14,
	SURFACE_SLUGHOLE      = 15,
	SURFACE_UNDISCOVERED  = 16,
	SURFACE_CAVERN        = 17,
};
static_assert(sizeof(SurfaceType) == 0x4, "");

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
static_assert(sizeof(AdvisorAnim) == 0x4, "");

// Keys use the same numbering as used by DirectInput's "DIK_*" enums.
enum Keys : unsigned char
{
    KEY_NONE            = 0,   // Not a real KEY enum name

    KEY_ESCAPE          = 1,   // ESC
    KEY_ONE             = 2,   // '1'
    KEY_TWO             = 3,   // '2'
    KEY_THREE           = 4,   // '3'
    KEY_FOUR            = 5,   // '4'
    KEY_FIVE            = 6,   // '5'
    KEY_SIX             = 7,   // '6'
    KEY_SEVEN           = 8,   // '7'
    KEY_EIGHT           = 9,   // '8'
    KEY_NINE            = 10,  // '9'
    KEY_ZERO            = 11,  // '0'
    KEY_MINUS           = 12,  // '-'
    KEY_EQUALS          = 13,  // '='
    KEY_BACKSPACE       = 14,  // BACK
    KEY_TAB             = 15,  // '\t'
    KEY_Q               = 16,  // 'Q'
    KEY_W               = 17,  // 'W'
    KEY_E               = 18,  // 'E'
    KEY_R               = 19,  // 'R'
    KEY_T               = 20,  // 'T'
    KEY_Y               = 21,  // 'Y'
    KEY_U               = 22,  // 'U'
    KEY_I               = 23,  // 'I'
    KEY_O               = 24,  // 'O'
    KEY_P               = 25,  // 'P'
    KEY_LEFTBRACE       = 26,  // '{'
    KEY_RIGHTBRACE      = 27,  // '}'
    KEY_RETURN          = 28,  // Enter
    KEY_LEFTCTRL        = 29,  // LCtrl
    KEY_A               = 30,  // 'A'
    KEY_S               = 31,  // 'S'
    KEY_D               = 32,  // 'D'
    KEY_F               = 33,  // 'F'
    KEY_G               = 34,  // 'G'
    KEY_H               = 35,  // 'H'
    KEY_J               = 36,  // 'J'
    KEY_K               = 37,  // 'K'
    KEY_L               = 38,  // 'L'
    KEY_SEMICOLON       = 39,  // ';'
    KEY_AT              = 40,  // '"' [English U.S.], '@' [English U.K. ...I think]
    KEY_RSINGLEQUOTE    = 41,  // '~' [English U.S.], ??? [English U.K. ...could be '`' or '\'']
    KEY_LEFTSHIFT       = 42,  // LShift key
    KEY_HASH            = 43,  // '|' [English U.S.], '#' [English U.K. ...I think]
    KEY_Z               = 44,  // 'Z'
    KEY_X               = 45,  // 'X'
    KEY_C               = 46,  // 'C'
    KEY_V               = 47,  // 'V'
    KEY_B               = 48,  // 'B'
    KEY_N               = 49,  // 'N'
    KEY_M               = 50,  // 'M'
    KEY_LEFTARROW       = 51,  // '<'
    KEY_RIGHTARROW      = 52,  // '>'
    KEY_QUESTIONMARK    = 53,  // '?'
    KEY_RIGHTSHIFT      = 54,  // RShift
    KEYPAD_ASTERISK     = 55,  // Numpad '*' (Multiply)
    KEY_ALT             = 56,  // LAlt (LMenu)
    KEY_SPACE           = 57,  // ' ' Space bar
    KEY_CAPLOCK         = 58,  // CAPS lock
    KEY_F1              = 59,  // F1
    KEY_F2              = 60,  // F2
    KEY_F3              = 61,  // F3
    KEY_F4              = 62,  // F4
    KEY_F5              = 63,  // F5
    KEY_F6              = 64,  // F6
    KEY_F7              = 65,  // F7
    KEY_F8              = 66,  // F8
    KEY_F9              = 67,  // F9
    KEY_F10             = 68,  // F10
    KEYPAD_NUMLOCK      = 69,  // NUM lock key
    KEY_SCROLLLOCK      = 70,  // SCR lock key
    KEYPAD_7            = 71,  // Numpad '7'
    KEYPAD_8            = 72,  // Numpad '8'
    KEYPAD_9            = 73,  // Numpad '9'
    KEYPAD_MINUS        = 74,  // Numpad '-' (Subtract)
    KEYPAD_4            = 75,  // Numpad '4'
    KEYPAD_5            = 76,  // Numpad '5'
    KEYPAD_6            = 77,  // Numpad '6'
    KEYPAD_PLUS         = 78,  // Numpad '+' (Add)
    KEYPAD_1            = 79,  // Numpad '1'
    KEYPAD_2            = 80,  // Numpad '2'
    KEYPAD_3            = 81,  // Numpad '3'
    KEYPAD_0            = 82,  // Numpad '0'
    KEYPAD_DELETE       = 83,  // Numpad '.' (Decimal, DEL)
    KEY_BACKSLASH       = 86,  // OEM_102: <> or \| on RT 102-key keyboard (Non-U.S.)
    KEY_F11             = 87,  // F11
    KEY_F12             = 88,  // F12
    KEYPAD_ENTER        = 156, // Numpad Enter (Return)
    KEY_RIGHTCTRL       = 157, // RCtrl
    KEYPAD_FORWARDSLASH = 181, // Numpad '/' (Divide)
    KEY_PRINTSCREEN     = 183, // PRNT SCR
    KEY_ALTGR           = 184, // RAlt (RMenu): Non-English modifier key for foreign characters 
    KEY_HOME            = 199, // Home
    KEY_CURSORUP        = 200, // Up arrow key
    KEY_PGUP            = 201, // Page up (Prior)
    KEY_CURSORLEFT      = 203, // Left arrow key
    KEY_CURSORRIGHT     = 205, // Right arrow key
    KEY_END             = 207, // End
    KEY_CURSORDOWN      = 208, // Down arrow key
    KEY_PGDN            = 209, // Page down (Next)
    KEY_INSERT          = 210, // INS
    KEY_DELETE          = 211, // DEL
};
static_assert(sizeof(Keys) == 0x1, "");


enum PathType : unsigned char
{
	PATH_NONE      = 0x00,
	PATH_RUBBLE    = 0x01,
	PATH_POWERPATH = 0x02,
};
static_assert(sizeof(PathType) == 0x1, "");

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
static_assert(sizeof(FallinType) == 0x1, "");

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
static_assert(sizeof(BubbleType) == 0x4, "");

enum OreType : int
{
	ORE_NORMAL    = 0,
	ORE_PROCESSED = 1,
};
static_assert(sizeof(OreType) == 0x4, "");

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
static_assert(sizeof(AbilityType) == 0x4, "");

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
static_assert(sizeof(InfoType) == 0x4, "");

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
static_assert(sizeof(ActivityType) == 0x4, "");

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
static_assert(sizeof(TextType) == 0x4, "");


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


typedef void (__cdecl* FileOpenCallback)(const char* fileName, unsigned int fileSize, void* lpValue);

typedef void (__cdecl* MusicCallback)(void);

typedef void (__cdecl* ResourceDrawCallback)(ResourceData* resData, void* lpValue);

typedef void (__cdecl* ResourceSoundCallback)(const char* sampleName, ResourceData* resData, void* lpValue);

typedef BOOL (__cdecl* LiveObjectPredicate)(LiveObject* liveObj, void* lpValue);

typedef float10 (__cdecl* GetSurfaceZCallback)(float x, float y, LevelSurfaceMap* surfMap);

typedef BOOL (__cdecl* GameInitFunction)(void);
typedef BOOL (__cdecl* GameUpdateFunction)(float elapsed);
typedef void (__cdecl* GameCleanupFunction)(void);

typedef void (__cdecl* FlocksCallback)(FlockData* flockData, FlockSubdata* subdata, void* lpValue);

typedef void (__cdecl* FileOpenCallback)(const char* filename, unsigned int fileSize, void* lpValue);

// used by std::qsort
typedef int (__cdecl* CompareCallback)(void* item1, void* item2);

typedef int (__cdecl* NERPSFunction)(int* stack);





struct StructF_10
{
	/*00,4*/ float float_0;
	/*04,4*/ float float_4;
	/*08,4*/ undefined4 field_8;
	/*0c,4*/ float float_c;
	/*10*/
};
static_assert(sizeof(StructF_10) == 0x10, "");

struct LevelIdentifier
{
	/*00,4*/ undefined4 field_0;
	/*04,4*/ undefined4 field_4;
	/*08,4*/ undefined4 field_8;
	/*0c,4*/ undefined4 field_c;
	/*10,4*/ undefined4 field_10;
	/*14*/
};
static_assert(sizeof(LevelIdentifier) == 0x14, "");

struct Sound3DInstance
{
	/*00,4*/ int sampleIndex;
	/*04,4*/ IDirect3DRMFrame3* frame;
	/*08,c*/ Vector3F position;
	/*14,4*/ unsigned int flags;
	/*18*/
};
static_assert(sizeof(Sound3DInstance) == 0x18, "");

struct LiveObjectInfo
{
	/*00,4*/ LiveObject* liveObj;
	/*04,4*/ BOOL intbool_4;
	/*08,8*/ Point2F point_8;
	/*10,c*/ Vector3F vector_10;
	/*1c*/
};
static_assert(sizeof(LiveObjectInfo) == 0x1c, "");

struct MiscObjectData
{
	/*00,30*/ undefined field_0x0_0x30[0x30];
	/*30,4*/ ResourceData* resData; // LWS,true | LWO,true
	/*34,4*/ undefined field_0x34_0x38[0x4];
	/*38*/
};
static_assert(sizeof(MiscObjectData) == 0x38, "");

struct ProMeshData
{
	/*000,4*/ ResourceData* promesh_a;
	/*004,4*/ ResourceData* promesh_b;
	/*008,190*/ undefined4 table_a[100];
	/*198,190*/ undefined4 table_b[100];
	/*328,4*/ float BlockSize;
	/*32c,4*/ undefined4 field_32c;
	/*330,c*/ undefined field_0x330_0x33c[0xc];
	/*33c,4*/ SurfaceTextureGrid* surfTextGrid;
	/*340*/
};
static_assert(sizeof(ProMeshData) == 0x340, "");

struct MessageAction
{
	/*00,4*/ MessageType event;
	/*04,4*/ LiveObject* object_4;
	/*08,4*/ undefined4 field_8;
	/*0c,4*/ undefined4 field_c;
	/*10,4*/ undefined4 field_10;
	/*14*/
};
static_assert(sizeof(MessageAction) == 0x14, "");

struct ActFrameResource
{
	/*00,4*/ ActFrameResource* previous;
	/*04,4*/ void* lwsStruct38; // LWS struct
	/*08,4*/ IDirect3DRMAnimationSet2* animSet; // (not LWS)
	/*0c,4*/ BOOL isLWSFile;
	/*10,4*/ IDirect3DRMFrame3* rootFrame; // (not LWS)
	/*14,4*/ IDirect3DRMFrame3** framesTable; // (not LWS) table of COM objects, length is count_18
	/*18,4*/ unsigned int framesCount; // (not LWS)
	/*1c,4*/ undefined4 field_1c;
	/*20*/
};
static_assert(sizeof(ActFrameResource) == 0x20, "");

struct ResourceAppData
{
	/*00,4*/ ResourceData* resData;
	/*04,4*/ char* filename;
	/*08,4*/ char* frameName;
	/*0c,4*/ undefined4 field_c;
	/*10,4*/ float float_10;
	/*14,4*/ float float_14;
	/*18,4*/ char* sampleName;
	/*1c,4*/ ActFrameResource* actFrameRes;
	/*20,4*/ undefined4 field_20;
	/*24,4*/ SoundResource* soundRes;
	/*28*/
};
static_assert(sizeof(ResourceAppData) == 0x28, "");


struct SoundResource
{
	/*00,4*/ IDirectSound3DBuffer* sound3dBuffer;
	/*04,4*/ undefined4 field_4;
	/*08,4*/ undefined4 field_8;
	/*0c,4*/ undefined4 field_c;
	/*10,4*/ SoundResource* previous;
	/*14*/
};
static_assert(sizeof(SoundResource) == 0x14, "");

struct Struct_8__00558bc4
{
	/*0,4*/ LiveObject* object_0;
	/*4,4*/ float float_4;
	/*8*/
};
static_assert(sizeof(Struct_8__00558bc4) == 0x8, "");

struct PairStruct_428
{
	/*0,4*/ Struct_428* first;
	/*4,4*/ Struct_428* second;
	/*8*/
};
static_assert(sizeof(PairStruct_428) == 0x8, "");

struct Struct_b8__00558080
{
	/*00,b8*/ undefined field_0x0_0xb8[0xb8];
	/*b8*/
};
static_assert(sizeof(Struct_b8__00558080) == 0xb8, "");

struct MapFileInfo
{
	/*00,4*/ char Signature[4]; // "MAP "
	/*04,4*/ unsigned int fileSize;
	/*08,8*/ Size2I dimensions;
	/*10,2*/ unsigned short blocks[1];
	/*12*/
};
static_assert(sizeof(MapFileInfo) == 0x12, "");

struct BlockObject
{
	/*00,4*/ LiveObject* attachedObject;
	/*04,8*/ Point2I position;
	/*0c,4*/ undefined4 field_c;
	/*10,4*/ BlockObject* pool_m_next;
	/*14*/
};
static_assert(sizeof(BlockObject) == 0x14, "");

struct ItemStruct_428
{
	/*00,4*/ unsigned int index;
	/*04,4*/ Direction direction;
	/*08,4*/ undefined4 field_8;
	/*0c,4*/ undefined4 field_c;
	/*10,4*/ undefined4 field_10;
	/*14,4*/ undefined4 field_14;
	/*18*/
};
static_assert(sizeof(ItemStruct_428) == 0x18, "");

struct Struct_428
{
	/*000,320*/ Point2F points[100];
	/*320,4*/ unsigned int pointsCount;
	/*324,f0*/ ItemStruct_428 items[10];
	/*414,4*/ unsigned int itemsCount;
	/*418,4*/ undefined4 field_418;
	/*41c,4*/ undefined4 field_41c;
	/*420,4*/ undefined4 field_420;
	/*424,4*/ undefined4 field_424;
	/*428*/
};
static_assert(sizeof(Struct_428) == 0x428, "");

struct BasicObjectData
{
	/*0,4*/ int objIndex;
	/*4,4*/ ResourceData* aeResData; // ACT, true
	/*8*/
};
static_assert(sizeof(BasicObjectData) == 0x8, "");



struct SelectedUnitHotkey
{
	/*00,4*/ int field_0;
	/*04,4*/ int field_4;
	/*08,4*/ BOOL bool_8;
	/*0c,4*/ int field_c;
	/*10,4*/ int field_10;
	/*14*/
};
static_assert(sizeof(SelectedUnitHotkey) == 0x14, "");

struct AdvisorAnimData
{
	/*0,4*/ ResourceData* resData;
	/*4,4*/ float loopStartTime; // ignored when not looping
	/*8,4*/ float loopEndTime; // ignored when not looping
	/*c*/
};
static_assert(sizeof(AdvisorAnimData) == 0xc, "");

struct AudioPlaybackData
{
	/*00,4*/ BOOL isUsed1; // paused/playing/used?
	/*04,4*/ WAVEFORMATEX* waveFormat; // hGlobal
	/*08,4*/ HMMIO hMmio;
	/*0c,14*/ MMCKINFO mmckInfo;
	/*20,14*/ MMCKINFO mmckInfoData;
	/*34,4*/ unsigned int bufferBytesSize;
	/*38,4*/ unsigned int totalFrames; // probably
	/*3c,4*/ unsigned int playback_3c;
	/*40,4*/ unsigned int playback_40;
	/*44,4*/ unsigned int playback_44; // thought to be totalSamples
	/*48,4*/ unsigned int playback_48;
	/*4c,4*/ undefined4 field_4c;
	/*50,4*/ BOOL modeChoice;
	/*54,4*/ undefined4 field_54;
	/*58,4*/ BOOL isUsed2; // paused/playing/used?
	/*5c*/
};
static_assert(sizeof(AudioPlaybackData) == 0x5c, "");

struct NERPMessageSound
{
	/*0,4*/ char* key;
	/*4,4*/ int sampleIndex;
	/*8*/
};
static_assert(sizeof(NERPMessageSound) == 0x8, "");

struct SampleProperty
{
	/*0,4*/ int sampleIndex;
	/*4,4*/ SampleProperty* next;
	/*8*/
};
static_assert(sizeof(SampleProperty) == 0x8, "");

struct SampleData
{
	/*000,104*/ char filename[260];
	/*104,4*/ unsigned int length;
	/*108,4*/ unsigned int avgBytesPerSec;
	/*10c,4*/ unsigned int frequency;
	/*110,4*/ int volume;
	/*114,4*/ undefined4 offset;
	/*118,4*/ HGLOBAL hGlobal_118;
	/*11c,4*/ HGLOBAL hGlobal_11c;
	/*120,4*/ IDirectSoundBuffer* dSoundBuffer1;
	/*124,4*/ IDirectSoundBuffer* dSoundBuffer2;
	/*128,4*/ IDirectSoundBuffer* dSoundBuffer3;
	/*12c,4*/ undefined4 bufferIndex;
	/*130,4*/ SampleFlags flags;
	/*134*/
};
static_assert(sizeof(SampleData) == 0x134, "");


struct SharedWADEntry
{
	/*00,4*/ void* fileData;
	/*04,4*/ BOOL isUsed;
	/*08,4*/ int wadIndex;
	/*0c,4*/ int entryIndex;
	/*10*/
};
static_assert(sizeof(SharedWADEntry) == 0x10, "");

struct SharedTextureResource
{
	/*0,4*/ char* name;
	/*4,4*/ IDirect3DRMTexture3* texture;
	/*8*/
};
static_assert(sizeof(SharedTextureResource) == 0x8, "");

struct ResourceManager
{
	/*0000,50*/ ResourceData* pool_g_TABLE[20]; // PTR_0076bd80
	/*0050,4*/ ResourceData* pool_g_NEXT; // PTR_0076bd84
	/*0054,4*/ ResourceData* pool_g_ROOT; // PTR_0076bd88
	/*0058,24*/ const char* Types_TABLE[9]; // PTR_0076bdd8
	/*007c,24*/ const char* Extensions_TABLE[9]; // PTR_0076bdfc
	/*00a0,4*/ char* CfgRootName; // PTR_0076be20
	/*00a4,4*/ undefined4 DAT_0076be24; // DAT_0076be24
	/*00a8,4*/ undefined4 field_a8; // DAT_0076be28
	/*00ac,4*/ undefined4 field_ac; // referenced by addr to get last item of g_Textures_TABLE
	/*00b0,4*/ undefined4 field_b0; // DAT_0076be30
	/*00b4,1f40*/ SharedTextureResource Textures_TABLE[1000]; // PTR_0076be34
	/*1ff4,4*/ unsigned int Textures_COUNT; // DAT_0076dd74
	/*1ff8,4*/ pointer soundCallback; // PTR_0076dd78
	/*1ffc,4*/ void* soundCallback_VALUE; // PTR_0076dd7c
	/*2000,4*/ pointer drawCallback; // PTR_0076dd80
	/*2004,4*/ void* drawCallback_VALUE; // PTR_0076dd84
	/*2008,4*/ char* SharedTextures; // PTR_0076dd88
	/*200c,4*/ unsigned int SceneFogColor; // DAT_0076dd8c
	/*2010,4*/ unsigned int pool_g_COUNT; // DAT_0076dd90
	/*2014,4*/ unsigned int pool_g_INITFLAGS; // DAT_0076dd94
	/*2018*/
};
static_assert(sizeof(ResourceManager) == 0x2018, "");


struct NERPSFunctionSignature
{
	/*0,4*/ const char* name;
	/*4,4*/ int (*function)(int*);
	/*8,4*/ NERPSFunctionArgs arguments;
	/*c*/
};
static_assert(sizeof(NERPSFunctionSignature) == 0xc, "");


struct MiscObjectDependencies
{
	/*00,4*/ undefined4 field_0;
	/*04,40*/ unsigned int levels_flags[16];
	/*44,40*/ undefined4 levels_field_44[16];
	/*84,40*/ undefined4 levels_field_84[16];
	/*c4*/
};
static_assert(sizeof(MiscObjectDependencies) == 0xc4, "");


struct SharedFileBuffer
{
	/*0,4*/ void* fileData;
	/*4,4*/ FileBufferFlags flags; // 1 = isUsed
	/*8*/
};
static_assert(sizeof(SharedFileBuffer) == 0x8, "");

struct ErodeState
{
	/*0,4*/ undefined4 field_0;
	/*4,4*/ undefined4 field_4;
	/*8*/
};
static_assert(sizeof(ErodeState) == 0x8, "");


struct ToolTipData
{
	/*000,4*/ float float_0;
	/*004,200*/ char tooltipText[512];
	/*204,58*/ undefined field_0x204_0x25c[0x58];
	/*25c,4*/ undefined4 field_25c;
	/*260,4*/ undefined4 field_260;
	/*264,4*/ undefined4 field_264;
	/*268,4*/ undefined4 field_268;
	/*26c,4*/ undefined4 field_26c;
	/*270,4*/ ImageBMP* tooltipImage;
	/*274,4*/ undefined4 field_274;
	/*278,4*/ unsigned int flags;
	/*27c*/
};
static_assert(sizeof(ToolTipData) == 0x27c, "");

struct SharedObjectResource
{
	/*0,4*/ char* resName;
	/*4,4*/ Struct_34* lwoStruct34;
	/*8*/
};
static_assert(sizeof(SharedObjectResource) == 0x8, "");

// The item's render state type is determined by the index in its table
struct RenderStateItem
{
	/*0,4*/ DWORD value;
	/*4,4*/ BOOL isUsed;
	/*8*/
};
static_assert(sizeof(RenderStateItem) == 0x8, "");

struct ImageFont
{
	/*000,4*/ ImageBMP* bitmap;
	/*004,be0*/ undefined field_0x4_0xbe4[0xbe0];
	/*be4,4*/ undefined4 field_be4;
	/*be8,8*/ undefined field_0xbe8_0xbf0[0x8];
	/*bf0,4*/ ImageFont* pool_m_next;
	/*bf4*/
};
static_assert(sizeof(ImageFont) == 0xbf4, "");

struct FileStream {
	/*0,4*/ FileLocation location;
	/*4,4*/ union {
		FILE* std; // Standard file stream
		WADEntryStream* wad; // WAD file stream
	};
	/*8*/
};
static_assert(sizeof(FileStream) == 0x8, "");

struct WADEntryStream
{
	/*0,4*/ int sharedIndex;
	/*4,4*/ int position;
	/*8,4*/ undefined4 field_8;
	/*c*/
};
static_assert(sizeof(WADEntryStream) == 0xc, "");

// WAD file entry metadata contained within LegoWADFile structure
struct WADEntry
{
	/*00,4*/ WADEntryFlags flags; // usually 1, 2 for RNC compression
	//undefined field_0x1;
	//undefined field_0x2;
	//undefined field_0x3;
	/*04,4*/ unsigned int packedSize; // Compressed packed size
	/*08,4*/ unsigned int origSize; // Original unpacked size (same as packedSize when uncompressed)
	/*0c,4*/ unsigned int offset; // absolute file offset
	/*10*/
};
static_assert(sizeof(WADEntry) == 0x10, "");

// LegoRR WAD File information
struct WADFile
{
	/*00,4*/ undefined4 field_0;
	/*04,4*/ BOOL isUsed; // 1 if WAD is in-use
	/*08,4*/ undefined4 field_8;
	/*0c,4*/ undefined4 field_c;
	/*10,4*/ FILE* file; // file I/O
	/*14,4*/ char** absdirs; // source file paths when WAD was built
	/*18,4*/ char** reldirs; // relative file paths inside WAD
	/*1c,4*/ WADEntry* entries; // file entry metadata
	/*20,4*/ unsigned int count; // number of file entries
	/*24*/
};
static_assert(sizeof(WADFile) == 0x24, "");

struct LoaderProfileItem
{
	/*0,4*/ char* name;
	/*4,4*/ undefined4 field_4;
	/*8,4*/ undefined4 field_8;
	/*c*/
};
static_assert(sizeof(LoaderProfileItem) == 0xc, "");

struct SurfaceTextureGrid
{
	/*0,8*/ Size2I gridSize;
	/*8,4*/ DirectXSurfaceTuple** gridSurfaces;
	/*c*/
};
static_assert(sizeof(SurfaceTextureGrid) == 0xc, "");

struct HelpWindowInfoLevels
{
	/*00,40*/ char* levels[16];
	/*40*/
};
static_assert(sizeof(HelpWindowInfoLevels) == 0x40, "");

struct InterfaceMenuItem
{
	/*0,4*/ int* parameters;
	/*4,4*/ unsigned int numParams;
	/*8*/
};
static_assert(sizeof(InterfaceMenuItem) == 0x8, "");

// Property loaded from a level's PTL config file (contains lookup index for actions)
struct PTLProperty
{
	/*0,4*/ MessageType eventIndex;
	/*4,4*/ MessageType actionIndex;
	/*8*/
};
static_assert(sizeof(PTLProperty) == 0x8, "");

struct DriverMode
{
	/*000,10*/ GUID guid;
	/*010,100*/ char displayName[256]; // "name (description)"
	/*110,4*/ DriverModeFlags flags;
	/*114*/
};
static_assert(sizeof(DriverMode) == 0x114, "");

struct DeviceMode
{
	/*000,10*/ GUID guid;
	/*010,100*/ char displayName[256]; // "name (description)"
	/*110,4*/ DeviceModeFlags flags;
	/*114*/
};
static_assert(sizeof(DeviceMode) == 0x114, "");

struct ScreenMode
{
	/*000,4*/ int screenWidth;
	/*004,4*/ int screenHeight;
	/*008,4*/ int bitDepth;
	/*00c,100*/ char displayName[256]; // "WxH (BPP bit)", "WxH" (windowed)
	/*10c,4*/ ScreenModeFlags flags;
	/*110*/
};
static_assert(sizeof(ScreenMode) == 0x110, "");

struct ImageBMP
{
	/*00,4*/ IDirectDrawSurface4* ddSurface; // IDirectDrawSurface4
	/*04,4*/ int width;
	/*08,4*/ int height;
	/*0c,4*/ unsigned int firstColor24;
	/*10,4*/ unsigned int lastColor24;
	/*14,4*/ unsigned int firstColorNative;
	/*18,4*/ unsigned int flags; // 2 is font?
	/*1c,4*/ ImageBMP* pool_m_next;
	/*20*/
};
static_assert(sizeof(ImageBMP) == 0x20, "");

struct SurfaceMapStruct38
{
	/*00,4*/ undefined4 field_0;
	/*04,4*/ float float_4;
	/*08,4*/ undefined4 field_8;
	/*0c,4*/ undefined4 field_c;
	/*10,20*/ undefined4 table_10[8];
	/*30,4*/ undefined field_0x30_0x34[0x4];
	/*34,4*/ unsigned int flags;
	/*38*/
};
static_assert(sizeof(SurfaceMapStruct38) == 0x38, "");

struct ObjectiveData
{
	/*00,4*/ void* ObjectiveImage; // bmp
	/*04,4*/ int ObjectiveImage_width_x; // ???
	/*08,4*/ int ObjectiveImage_height_y; // ???
	/*0c,4*/ void* ObjectiveAcheivedImage; // bmp
	/*10,4*/ int ObjectiveAcheivedImage_width_x; // ???
	/*14,4*/ int ObjectiveAcheivedImage_height_y; // ???
	/*18,4*/ void* ObjectiveFailedImage; // bmp
	/*1c,4*/ int ObjectiveFailedImage_width_x; // ???
	/*20,4*/ int ObjectiveFailedImage_height_y; // ???
	/*24,4*/ void* ObjectiveAcheivedAVI; // ???
	/*28,4*/ int ObjectiveAcheivedAVI_width_x; // ???
	/*2c,4*/ int ObjectiveAcheivedAVI_height_y; // ???
	/*30,4*/ undefined4 field_30;
	/*34,4*/ undefined4 field_34;
	/*38,4*/ int CrystalObjective; // number of crystals needed if non-zero
	/*3c,4*/ int OreObjective; // number of ore needed if non-zero
	/*40,8*/ Point2I BlockObjective;
	/*48,4*/ float TimerObjective; // (mult: 25.0, flags, format: "time:HitTimeFailObjective")
	/*4c,4*/ int ConstructionObjective_type;
	/*50,4*/ int ConstructionObjective_index;
	/*54*/
};
static_assert(sizeof(ObjectiveData) == 0x54, "");

struct LevelData
{
	/*000,4*/ char* levelName; // (format: "Levels::level")
	/*004,4*/ LevelSurfaceMap* surfaceMap;
	/*008,4*/ undefined4 field_8;
	/*00c,4*/ undefined4 field_c;
	/*010,4*/ undefined4 field_10;
	/*014,8*/ Size2I dimensions;
	/*01c,4*/ float BlockSize;
	/*020,4*/ float DigDepth;
	/*024,4*/ float RoofHeight;
	/*028,4*/ float RoughLevel;
	/*02c,4*/ BOOL3 UseRoof;
	/*030,4*/ BOOL3 SafeCaverns;
	/*034,4*/ float SelBoxHeight;
	/*038,4*/ undefined4 field_0x38;
	/*03c,4*/ undefined4 field_0x3c;
	/*040,4*/ undefined4 field_0x40;
	/*044,4*/ undefined4 field_0x44;
	/*048,4*/ undefined4 field_0x48;
	/*04c,4*/ undefined4 field_0x4c;
	/*050,4*/ undefined4 field_0x50;
	/*054,4*/ undefined4 field_0x54;
	/*058,4*/ undefined4 field_0x58;
	/*05c,4*/ undefined4 field_0x5c;
	/*060,4*/ undefined4 field_0x60;
	/*064,4*/ undefined4 field_0x64;
	/*068,4*/ undefined4 field_0x68;
	/*06c,4*/ undefined4 field_0x6c;
	/*070,4*/ undefined4 field_0x70;
	/*074,8*/ Size2I surfTextSize; // surface texture width and height
	/*07c,4*/ SurfaceTextureGrid* surfTextGrid;
	/*080,4*/ undefined4 field_0x80;
	/*084,4*/ LevelStruct_3c* struct3c_84;
	/*088,4*/ LevelStruct_1c* terrain1c_88;
	/*08c,4*/ int numCrystals; // (init: 0)
	/*090,4*/ undefined4 field_90; // (init: 0)
	/*094,4*/ undefined4 field_94; // (init: 0)
	/*098,4*/ int numDrainedCrystals; // assumption
	/*09c,4*/ undefined4 field_9c;
	/*0a0,4*/ int numOre; // (init: 0)
	/*0a4,4*/ undefined4 field_a4; // (init: 0)
	/*0a8,4*/ undefined4 field_a8; // (init: 0)
	/*0ac,4*/ int numProcessedOre;
	/*0b0,4*/ int EmergeCreature; // (searches for object index by name, expects RockMonsterType)
	/*0b4,4*/ char* NextLevel;
	/*0b8,4*/ LevelBlock* blocks; // grid of blocks [y][x]
	/*0bc,54*/ ObjectiveData objective;
	/*110,4*/ BOOL hasBlockPointers;
	/*114,e0*/ BlockPointer* blockPointers[56];
	/*1f4,4*/ BOOL StartFP;
	/*1f8,4*/ BOOL NoDrain;
	/*1fc,4*/ float oxygenLevel; // (init: 100.0, Oxygen level?)
	/*200,4*/ float OxygenRate;
	/*204,4*/ float float_204; // (init: 100.0, Oxygen level?)
	/*208,4*/ float BuildingTolerance; // (default: 4.0)
	/*20c,4*/ float BuildingMaxVariation; // (default: 6.0)
	/*210,50*/ float UpgradeTimes[20]; // [objType] (mult: 25.0, 1:Vehicle, 2:MiniFigure, 3:Building)
	/*260,4*/ float TrainTime; // (mult: 25.0)
	/*264,4*/ float EmergeTimeOut; // (default: 1500.0)
	/*268,4*/ float SlugTime; // (default: 60.0, mult: 25.0 (applies to default))
	/*26c,4*/ int Slug; // (default: 20 (invalid), searches for object index by name, expects RockMonsterType)
	/*270,4*/ char* FullName; // (replace '_' with ' ')
	/*274,4*/ TextureType BoulderAnimation; // (texture index, hardcoded: Rock, Lava, Ice)
	/*278,4*/ float MaxStolen;
	/*27c,4*/ LevelCompleteStatus status; // (init: 0) 2 is used for Crystal failure as well
	/*280,4*/ BOOL IsStartTeleportEnabled; // (! DisableStartTeleport)
	/*284*/
};
static_assert(sizeof(LevelData) == 0x284, "");

struct BlockPointer
{
	/*0,8*/ Point2I position;
	/*8,4*/ unsigned int id;
	/*c*/
};
static_assert(sizeof(BlockPointer) == 0xc, "");

struct DirectXSurfaceTuple
{
	/*0,4*/ IDirectDrawSurface4* surface;
	/*4,4*/ IDirect3DRMTexture3* texture;
	/*8,4*/ undefined4 field_8;
	/*c*/
};
static_assert(sizeof(DirectXSurfaceTuple) == 0xc, "");

// size 0x73d4... dear god.... no...
struct LevelSurfaceMap
{
	/*0000,8*/ Size2I smallDimensions; // full map dimensions - 1
	/*0008,8*/ Size2I dimensions; // full map dimensions
	/*0010,4*/ float BlockSize;
	/*0014,4*/ float RoughLevel;
	/*0018,8*/ Size2F blockDimensions_neg; // smallDimensions * BlockSize * 0.5 (width is negative??)
	/*0020,4*/ float float_20;
	/*0024,4*/ ResourceData* resData_24;
	/*0028,4*/ undefined4 field_28;
	/*002c,4*/ undefined4 field_2c;
	/*0030,4*/ undefined4 field_30;
	/*0034,4000*/ undefined field_0x34_0x4034[0x4000];
	/*4034,80*/ undefined4 flat_4034[32];
	/*40b4,200*/ undefined4 flat_40b4[128];
	/*42b4,7d0*/ unsigned short table_42b4[1000];
	/*4a84,4*/ unsigned int count_4a84;
	/*4a88,2710*/ undefined field_0x4a88_0x7198[0x2710];
	/*7198,4*/ undefined4 field_7198;
	/*719c,230*/ SurfaceMapStruct38 table38_719c[10];
	/*73cc,4*/ ResourceData* resData_73cc;
	/*73d0,4*/ undefined4 field_73d0;
	/*73d4*/
};
static_assert(sizeof(LevelSurfaceMap) == 0x73d4, "");

struct LevelStruct_3c
{
	/*00,4*/ undefined4 field_0;
	/*04,4*/ undefined4 field_4;
	/*08,4*/ undefined4 field_8;
	/*0c,4*/ undefined4 field_c;
	/*10,4*/ undefined4 field_10;
	/*14,4*/ undefined4 field_14;
	/*18,4*/ undefined4 field_18;
	/*1c,4*/ undefined4 field_1c;
	/*20,4*/ undefined4 field_20;
	/*24,4*/ undefined4 field_24;
	/*28,4*/ undefined4 field_28;
	/*2c,4*/ undefined4 field_2c;
	/*30,4*/ undefined4 field_30;
	/*34,4*/ undefined4 field_34;
	/*38,4*/ undefined4 field_38;
	/*3c*/
};
static_assert(sizeof(LevelStruct_3c) == 0x3c, "");

struct GameManager
{
	/*000,4*/ CFGProperty* LegoCfgRoot; // g_LegoCfgRoot
	/*004,4*/ char* CfgRootName; // g_CFG_ROOTPATH
	/*008,4*/ undefined4 field_8;
	/*00c,4*/ undefined4 field_c;
	/*010,4*/ GraphicsQuality Quality; // g_GraphicsQuality
	/*014,4*/ LevelData* level; // g_LEVEL_STRUCTPTR_SIZE_284__005570d4
	/*018,4*/ ResourceData* resRoot; // DAT_005570d8
	/*01c,4*/ void* ptr_1c; // PTR_005570dc
	/*020,4*/ undefined4 field_20; // DAT_005570e0
	/*024,4*/ Struct_bc* structbc_24; // PTR_005570e4
	/*028,4*/ Struct_bc* structbc_28; // DAT_005570e8
	/*02c,4*/ Struct_bc* structbc_2c; // DAT_005570ec
	/*030,4*/ ResourceData* struct2c_30; // PTR_005570f0
	/*034,4*/ ResourceData* struct2c_34; // DAT_005570f4
	/*038,4*/ ResourceData* struct2c_38; // PTR_005570f8
	/*03c,4*/ ResourceData* struct2c_3c; // PTR_005570fc
	/*040,4*/ ResourceData* struct2c_40; // PTR_00557100
	/*044,4*/ ResourceData* struct2c_44; // PTR_00557104
	/*048,4*/ ResourceData* struct2c_48; // PTR_00557108
	/*04c,4*/ ResourceData* struct2c_4c; // PTR_0055710c
	/*050,4*/ float FPClipBlocks; // FLOAT_00557110
	/*054,4*/ float TVClipDist; // g_tvclipdist
	/*058,4*/ undefined4 field_58;
	/*05c,4*/ undefined4 field_5c;
	/*060,4*/ undefined4 field_60;
	/*064,4*/ ImageFont* bmpFONT5_HI; // g_FONT_FONT5_HI
	/*068,4*/ ImageFont* bmpToolTipFont; // g_FONT_ToolTipFont
	/*06c,4*/ ImageFont* bmpDeskTopFont; // g_FONT_DeskTopFont
	/*070,4*/ ImageFont* bmpfont5_HI; // g_FONT_font5_HI
	/*074,4*/ ImageFont* bmpMbriefFONT; // g_FONT_MbriefFONT
	/*078,4*/ ImageFont* bmpMbriefFONT2; // g_FONT_MbriefFONT2
	/*07c,4*/ ImageFont* bmpRSFont; // g_FONT_RSFont
	/*080,4*/ Struct_830* struct830_80; // PTR_00557140
	/*084,4*/ Struct_830* struct830_84; // PTR_00557144
	/*088,4*/ float float_88; // FLOAT_00557148
	/*08c,4*/ float float_8c; // FLOAT_0055714c
	/*090,4*/ float float_90; // FLOAT_00557150
	/*094,4*/ float float_94; // FLOAT_00557154
	/*098,4*/ BOOL bool_98; // BOOL_00557158
	/*09c,4*/ float gameSpeed; // FLOAT_0055715c
	/*0a0,4*/ LiveObject* object_a0; // DAT_00557160
	/*0a4,4*/ float float_a4; // FLOAT_00557164
	/*0a8,4*/ float float_a8; // FLOAT_00557168
	/*0ac,4*/ float float_ac; // FLOAT_0055716c
	/*0b0,4*/ float float_b0; // FLOAT_00557170
	/*0b4,4*/ float float_b4; // FLOAT_00557174
	/*0b8,4*/ float float_b8; // FLOAT_00557178
	/*0bc,4*/ float float_bc; // FLOAT_0055717c
	/*0c0,4*/ undefined4 field_c0; // DAT_00557180
	/*0c4,4*/ undefined4 field_c4; // DAT_0055718c
	/*0c8,4*/ BOOL bool_c8; // DAT_00557188
	/*0cc,4*/ char* ObjectNames_PowerCrystal; // g_ObjectNames_PowerCrystal
	/*0d0,4*/ char* ObjectNames_Ore; // g_ObjectNames_Ore
	/*0d4,4*/ char* ObjectNames_ProcessedOre; // g_ObjectNames_ProcessedOre
	/*0d8,4*/ char* ObjectNames_Dynamite; // g_ObjectNames_Dynamite
	/*0dc,4*/ char* ObjectNames_Barrier; // g_ObjectNames_Barrier
	/*0e0,4*/ char* ObjectNames_ElectricFence; // g_ObjectNames_ElectricFence
	/*0e4,4*/ char* ObjectNames_SpiderWeb; // g_ObjectNames_SpiderWeb
	/*0e8,4*/ char* ObjectNames_OohScary; // g_ObjectNames_OohScary
	/*0ec,4*/ char* ObjectNames_Path; // g_ObjectNames_Path
	/*0f0,4*/ char* ObjectTheNames_PowerCrystal; // g_ObjectTheNames_PowerCrystal
	/*0f4,4*/ char* ObjectTheNames_Ore; // g_ObjectTheNames_Ore
	/*0f8,4*/ char* ObjectTheNames_ProcessedOre; // g_ObjectTheNames_ProcessedOre
	/*0fc,4*/ char* ObjectTheNames_Dynamite; // g_ObjectTheNames_Dynamite
	/*100,4*/ char* ObjectTheNames_Barrier; // g_ObjectTheNames_Barrier
	/*104,4*/ char* ObjectTheNames_ElectricFence; // g_ObjectTheNames_ElectricFence
	/*108,4*/ char* ObjectTheNames_SpiderWeb; // g_ObjectTheNames_SpiderWeb
	/*10c,4*/ char* ObjectTheNames_OohScary; // g_ObjectTheNames_OohScary
	/*110,4*/ char* ObjectTheNames_Path; // g_ObjectTheNames_Path
	/*114,4*/ VehicleData* VehicleData_TABLE; // g_VehicleData_TABLE
	/*118,4*/ CreatureData* MiniFigureData_TABLE; // g_MiniFigureData_TABLE
	/*11c,4*/ CreatureData* RockMonsterData_TABLE; // g_RockMonsterData_TABLE
	/*120,4*/ BuildingData* BuildingData_TABLE; // g_BuildingData_TABLE
	/*124,4*/ UpgradeData* UpgradeData_TABLE; // g_UpgradeData_TABLE
	/*128,4*/ char** VehicleTypes_TABLE; // g_VehicleTypes_TABLE
	/*12c,4*/ char** MiniFigureTypes_TABLE; // g_MiniFigureTypes_TABLE
	/*130,4*/ char** RockMonsterTypes_TABLE; // g_RockMonsterTypes_TABLE
	/*134,4*/ char** BuildingTypes_TABLE; // g_BuildingTypes_TABLE
	/*138,4*/ char** UpgradeTypes_TABLE; // g_UpgradeTypes_TABLE
	/*13c,2c*/ const char* ToolTypes_TABLE[11]; // g_ToolTypes_TABLE
	/*168,2c*/ char* ToolNames_TABLE[11]; // g_ToolNames_TABLE
	/*194,4*/ char** ObjectNames_VehicleTypes_TABLE; // g_ObjectNames_VehicleTypes_TABLE
	/*198,4*/ char** ObjectNames_MiniFigureTypes_TABLE; // g_ObjectNames_MiniFigureTypes_TABLE
	/*19c,4*/ char** ObjectNames_RockMonsterTypes_TABLE; // g_ObjectNames_RockMonsterTypes_TABLE
	/*1a0,4*/ char** ObjectNames_BuildingTypes_TABLE; // g_ObjectNames_BuildingTypes_TABLE
	/*1a4,4*/ char** ObjectNames_UpgradeTypes_TABLE; // g_ObjectNames_UpgradeTypes_TABLE
	/*1a8,4*/ char** ObjectTheNames_VehicleTypes_TABLE; // g_ObjectTheNames_VehicleTypes_TABLE
	/*1ac,4*/ char** ObjectTheNames_MiniFigureTypes_TABLE; // g_ObjectTheNames_MiniFigureTypes_TABLE
	/*1b0,4*/ char** ObjectTheNames_RockMonsterTypes_TABLE; // g_ObjectTheNames_RockMonsterTypes_TABLE
	/*1b4,4*/ char** ObjectTheNames_BuildingTypes_TABLE; // g_ObjectTheNames_BuildingTypes_TABLE
	/*1b8,4*/ char** ObjectTheNames_UpgradeTypes_TABLE; // g_ObjectTheNames_UpgradeTypes_TABLE
	/*1bc,4*/ unsigned int VehicleTypes_COUNT; // g_VehicleTypes_COUNT
	/*1c0,4*/ unsigned int MiniFigureTypes_COUNT; // g_MiniFigureTypes_COUNT
	/*1c4,4*/ unsigned int RockMonsterTypes_COUNT; // g_RockMonsterTypes_COUNT
	/*1c8,4*/ unsigned int BuildingTypes_COUNT; // g_BuildingTypes_COUNT
	/*1cc,4*/ unsigned int UpgradeTypes_COUNT; // g_UpgradeTypes_COUNT
	/*1d0,48*/ const char* SurfaceTypes_TABLE[18]; // g_SurfaceTypes_TABLE
	/*218,48*/ char* SurfaceTypeDescriptions_name_TABLE[18]; // g_SurfaceTypeDescriptions_name_TABLE
	/*260,48*/ void* SurfaceTypeDescriptions_sound_TABLE[18]; // g_SurfaceTypeDescriptions_sound_TABLE
	/*2a8,4*/ ResourceData* RES_Boulder; // g_RES_BOULDER
	/*2ac,4*/ ResourceData* RES_BoulderExplode; // DAT_0055736c
	/*2b0,4*/ ResourceData* RES_BoulderExplodeIce; // DAT_00557370
	/*2b4,4*/ ResourceData* RES_Crystal; // g_RES_POWERCRYSTAL
	/*2b8,4*/ ResourceData* RES_Dynamite; // g_RES_DYNAMITE
	/*2bc,8*/ ResourceData* RES_Ores_TABLE[2]; // g_RES_ORES_TABLE
	/*2c4,4*/ ResourceData* RES_OohScary; // g_RES_OOHSCARY
	/*2c8,4*/ ResourceData* RES_Barrier; // g_RES_BARRIER
	/*2cc,4*/ ResourceData* RES_ElectricFence; // g_RES_ELECTRICFENCE
	/*2d0,4*/ ResourceData* RES_SpiderWeb; // g_RES_SPIDERWEB
	/*2d4,4*/ ResourceData* RES_RechargeSparkle; // DAT_00557394
	/*2d8,4*/ ResourceData* RES_MiniTeleportUp; // DAT_00557398
	/*2dc,4*/ ResourceData* RES_ElectricFenceStud; // DAT_0055739c
	/*2e0,4*/ ResourceData* RES_Pusher; // g_RES_PUSHER
	/*2e4,4*/ ResourceData* RES_Freezer; // g_RES_FREEZER
	/*2e8,4*/ ResourceData* RES_IceCube; // DAT_005573a8
	/*2ec,4*/ ResourceData* RES_SmashPath; // DAT_005573ac
	/*2f0,4*/ ResourceData* RES_LaserShot; // g_RES_LASERSHOT
	/*2f4,4*/ ResourceData** RES_2f4_TABLEUNK; // DAT_005573b4
	/*2f8,28*/ undefined4 table10_2f8[10]; // g_UNK_TABLE__005573b8
	/*330,4*/ unsigned int count10_320; // UINT_005573e0
	/*324,4*/ float float_324; // FLOAT_005573e4
	/*328,4*/ float float_328; // FLOAT_005573e8
	/*32c,4*/ float float_32c; // FLOAT_005573ec
	/*330,4*/ float float_330; // FLOAT_005573f0
	/*334,4*/ float tvTiltOrZoom_334;
	/*338,8*/ Point2F tvFaceDirection_338;
	/*340,4*/ float MedPolyRange; // g_MedPolyRange
	/*344,4*/ float HighPolyRange; // g_HighPolyRange
	/*348,4*/ int HPBlocks; // g_HPBlocks
	/*34c,c*/ ColourRGBF FogColourRGB; // g_FogColourRGB
	/*358,c*/ ColourRGBF HighFogColourRGB; // g_HighFogColourRGB
	/*364,4*/ float float_364; // g_LEVEL_UNK_FLOAT_00557424
	/*368,c*/ ColourRGBF PowerCrystalRGB; // g_PowerCrystalRGB
	/*374,c*/ ColourRGBF UnpoweredCrystalRGB; // g_UnpoweredCrystalRGB
	/*380,4*/ ObjectType placeObjType; // INT_00557440
	/*384,4*/ int placeObjIndex; // INT_00557444
	/*388,4*/ Direction placeObjDirection; // INT_00557448
	/*38c,4*/ LiveObject* placeDestSmallTeleporter; // PTR_0055744c
	/*390,4*/ LiveObject* placeDestBigTeleporter; // PTR_00557450
	/*394,4*/ LiveObject* placeDestWaterTeleporter; // PTR_00557454
	/*398,4*/ float MinEnergyForEat; // g_MinEnergyForEat
	/*39c,4*/ ImageBMP* TutorialIcon; // bmp? PTR_0055745c
	/*3a0,4*/ undefined4 field_3a0;
	/*3a4,4*/ float DynamiteDamageRadius; // g_DynamiteDamageRadius
	/*3a8,4*/ float DynamiteMaxDamage; // g_DynamiteMaxDamage
	/*3ac,4*/ float DynamiteWakeRadius; // g_DynamiteWakeRadius
	/*3b0,4*/ float BirdScarerRadius; // g_BirdScarerRadius
	/*3b4,50*/ ObjectType objTeleportQueueTypes_TABLE[20]; // UNK_ARRAY_00557474
	/*404,50*/ int objTeleportQueueIndexes_TABLE[20]; // UNK_ARRAY_005574c4
	/*454,4*/ unsigned int objTeleportQueue_COUNT; // count for above 2 arrays, UINT_00557514
	/*458,4*/ float MiniFigureRunAway; // g_MiniFigureRunAway
	/*45c,c*/ Vector3F vector_45c; // FLOAT_0055751c
	/*468,320*/ undefined4 table200_468[200]; // UNK_ARRAY_00557528
	/*788,4*/ unsigned int count_788; // UINT_00557848
	/*78c,320*/ undefined4 table200_78c[200]; // UNK_ARRAY_0055784c
	/*aac,320*/ undefined4 table200_aac[200]; // UNK_ARRAY_00557b6c
	/*dcc,4*/ unsigned int count_dcc; // UINT_00557e8c
	/*dd0,4*/ unsigned int count_dd0; // UINT_00557e90
	/*dd4,4*/ unsigned int MaxReturnedCrystals; // g_MaxReturnedCrystals
	/*dd8,4*/ unsigned int MouseScrollBorder; // g_MouseScrollBorder
	/*ddc,4*/ char* HealthText; // g_HealthText
	/*de0,4*/ char* EnergyText; // g_EnergyText
	/*de4,4*/ char* CrystalsText; // g_CrystalsText
	/*de8,4*/ char* OreText; // g_OreText
	/*dec,4*/ char* StudsText; // g_StudsText
	/*df0,4*/ char* ToolsText; // g_ToolsText
	/*df4,4*/ char* CarryObjectText; // g_CarryObjectText
	/*df8,4*/ char* DrivenByText; // g_DrivenByText
	/*dfc,4*/ char* OreRequiredText; // g_OreRequiredText
	/*e00,4*/ BOOL IsFallinsEnabled; // (! "NoFallins"), g_YesFallins
	/*e04,4*/ float MinDistFor3DSoundsOnTopView; // g_MinDistFor3DSoundsOnTopView
	/*e08,4*/ unsigned int unkbool_308; // (may not be bool, compared with 0, and 1) g_GAME_UNK_BOOL_00557ec8
	/*e0c,4*/ GameFlags1 flags1; // g_GAME_GameFlags1
	/*e10,4*/ GameFlags2 flags2; // g_GAME_GameFlags2
	/*e14,4*/ GameFlags3 flags3; // only first byte is used(?), g_GAME_GameFlags3
	/*e18,4*/ float InitialSlugTime; // g_InitialSlugTime
	/*e1c,8*/ Point2F NextButtonPos; // g_NextButton
	/*e24,8*/ Point2F BackButtonPos; // g_BackButtonPos
	/*e2c,4*/ ImageBMP* NextButton; // bmp? PTR_00557eec
	/*e30,4*/ ImageBMP* BackButton; // bmp? PTR_00557ef0
	/*e34,4*/ ImageBMP* BackArrow; // bmp? PTR_00557ef4
	/*e38,4*/ float FogRate; // g_LEVEL_FogRate
	/*e3c,4*/ float float_e3c; // FLOAT_00557efc
	/*e40,4*/ float floatfps_e40; // assigned to Game_Update param_1 float fpsSync, FLOAT_00557f00
	/*e44,4*/ float DrainTime; // g_DrainTime
	/*e48,4*/ unsigned int ReinforceHits; // g_ReinforceHits
	/*e4c,4*/ unsigned int CDStartTrack; // g_CDStartTrack
	/*e50,4*/ unsigned int CDTracks; // g_CDTracks
	/*e54,4*/ unsigned int FallinMultiplier; // g_LEVEL_FallinMultiplier
	/*e58,4*/ BOOL hasFallins; // BOOL_00557f18
	/*e5c,8*/ Point2F menuNextPoint; // DAT_00557f1c
	/*e64,8*/ Point2F menuPrevPoint; // DAT_00557f24
	/*e6c,c*/ ColourRGBF DragBoxRGB; // g_DragBoxRGB
	/*e78,4*/ ImageBMP* DialogImage; // PTR_00557f38
	/*e7c,4*/ ImageBMP* DialogContrastOverlay; // PTR_00557f3c
	/*e80,4*/ void* drawregion_e80; // PTR_00557f40
	/*e84,4*/ void* drawregion_e84; // PTR_00557f44
	/*e88,4*/ void* drawregion_e88; // PTR_00557f48
	/*e8c,4*/ void* drawregion_e8c; // PTR_00557f4c
	/*e90,4*/ char* CreditsTextFile; // g_CreditsTextFile
	/*e94,4*/ char* CreditsBackAVI; // g_CreditsBackAVI
	/*e98,40*/ char* UpgradeNames_TABLE[16]; // g_UpgradeNames_TABLE
	/*ed8,4*/ int BuildingUpgradeCostOre; // g_BuildingUpgradeCostOre
	/*edc,4*/ int BuildingUpgradeCostStuds; // g_BuildingUpgradeCostStuds
	/*ee0,4*/ char* renameInput; // DAT_00557fa0
	/*ee4,4*/ float float_ee4; // FLOAT_00557fa4
	/*ee8,4*/ float float_ee8; // FLOAT_00557fa8
	/*eec,4*/ char* RenameReplace; // g_RenameReplace
	/*ef0,4*/ char* EndGameAVI1; // g_EndGameAVI1
	/*ef4,4*/ char* EndGameAVI2; // g_EndGameAVI2
	/*ef8*/
};
static_assert(sizeof(GameManager) == 0xef8, "");

struct CFGProperty
{
	/*00,4*/ char* fileText; // the entire CFG file text (only stored for root property)
	/*04,4*/ const char* key;   // init: NULL
	/*08,4*/ const char* value; // init: NULL
	/*0c,4*/ unsigned int depth;    // init: 0 (if root)
	/*10,4*/ unsigned int field_10; // init: 0 (unknown usage)
	/*14,4*/ CFGProperty* next; // init: NULL
	/*18,4*/ CFGProperty* previous;  // init: NULL (if root)
	/*1c,4*/ CFGProperty* pool_m_next;
	/*20*/
};
static_assert(sizeof(CFGProperty) == 0x20, "");

struct Struct_bc
{
	/*00,4*/ undefined4 mode_0;
	/*04,4*/ LiveObject* object_4;
	/*08,4*/ float float_8;
	/*0c,4*/ float float_c;
	/*10,4*/ float float_10;
	/*14,4*/ undefined4 field_14;
	/*18,c*/ Vector3F vector_18;
	/*24,4*/ ResourceData* resData_24;
	/*28,4*/ ResourceData* resData_28;
	/*2c,4*/ ResourceData* resData_2c;
	/*30,4*/ ResourceData* resData_30;
	/*34,4*/ undefined4 tableunk_34;
	/*38,58*/ undefined field_0x38_0x90[0x58];
	/*90,4*/ float float_90;
	/*94,c*/ undefined field_0x94_0xa0[0xc];
	/*a0,c*/ Vector3F vector_a0;
	/*ac,c*/ Vector3F vector_ac;
	/*b8,4*/ unsigned int flags;
	/*bc*/
};
static_assert(sizeof(Struct_bc) == 0xbc, "");

// Probably a text rendering area
struct Struct_830
{
	/*000,4*/ ImageFont* font;
	/*004,10*/ Rect2F area;
	/*014,4*/ void* allocData;
	/*018,400*/ undefined field_0x18_0x418[0x400];
	/*418,4*/ unsigned int allocSize;
	/*41c,410*/ undefined field_0x41c_0x82c[0x410];
	/*82c,4*/ unsigned int flags;
	/*830*/
};
static_assert(sizeof(Struct_830) == 0x830, "");

struct LwoFrame
{
	/*00,4*/ unsigned int dwSize;
	/*04,60*/ undefined field_0x4_0x64[0x60];
	/*64,4*/ undefined4 field_64;
	/*68,4*/ undefined field_0x68_0x6c[0x4];
	/*6c,4*/ unsigned int flags;
	/*70*/
};
static_assert(sizeof(LwoFrame) == 0x70, "");

struct ObjectUpgradePartData
{
	/*00,4*/ unsigned int level;
	/*04,4*/ int NullInstance;
	/*08,4*/ char* NullObjectName;
	/*0c,4*/ char* WeaponName;
	/*10,4*/ UpgradeData* upgradeData;
	/*14*/
};
static_assert(sizeof(ObjectUpgradePartData) == 0x14, "");

struct FlockSubdata
{
	/*00,c*/ Vector3F vector_0;
	/*0c,c*/ Vector3F vector_c;
	/*18,c*/ Vector3F vector_18;
	/*24,4*/ float float_24;
	/*28,4*/ float float_28;
	/*2c,4*/ float float_2c;
	/*30,4*/ float float_30;
	/*34,4*/ undefined4 field_34;
	/*38,4*/ float GoalUpdate1;
	/*3c,4*/ float Turn1;
	/*40,4*/ float Speed1;
	/*44,4*/ float Tightness1;
	/*48,4*/ float GoalUpdate2;
	/*4c,4*/ float Turn2;
	/*50,4*/ float Speed2;
	/*54,4*/ float Tightness2;
	///*58,40*/ float matrix[16];
	/*58,40*/ Matrix4F matrix;
	/*98,4*/ ResourceData* resData_98;
	/*9c,4*/ FlockSubdata* subdataNext_9c;
	/*a0*/
};
static_assert(sizeof(FlockSubdata) == 0xa0, "");

struct ObjectUpgradesData
{
	/*00,4*/ ObjectUpgradePartData* parts; // always ObjectUpgradePartData[200]
	/*04,4*/ unsigned int count;
	/*08,4*/ int currentLevel;
	/*0c,4*/ unsigned int levelsMask; // [carry][scan][speed][drill]
	/*10,4*/ LiveObject** upgradeObjs;
	/*14*/
};
static_assert(sizeof(ObjectUpgradesData) == 0x14, "");

struct BuildingData
{
	/*000,4*/ int objIndex;
	/*004,4*/ ResourceData* aeResData; // ACT, true
	/*008,4*/ char* CarryNullName;
	/*00c,4*/ char* CameraNullName;
	/*010,4*/ char* DepositNullName;
	/*014,4*/ char* EntranceNullName;
	/*018,4*/ char* ToolNullName;
	/*01c,4*/ char* FireNullName; // "fire laser"
	/*020,4*/ char* yPivot;
	/*024,4*/ char* xPivot;
	/*028,18*/ undefined4 carryFramesTable_28[6];
	/*040,10*/ undefined4 cameraFramesTable_40[4];
	/*050,18*/ undefined field_0x50_0x68[0x18];
	/*068,4*/ undefined4 field_68;
	/*06c,4*/ undefined4 field_6c;
	/*070,4*/ unsigned int CarryNullFrames;
	/*074,4*/ unsigned int CameraNullFrames;
	/*078,4*/ unsigned int ToolNullFrames;
	/*07c,4*/ ResourceData* PowerLevelScene; // LWS, true
	/*080,4*/ undefined4 field_80;
	/*084,4*/ Point2I* shapePoints; // Point2I[10]
	/*088,4*/ unsigned int shapeCount;
	/*08c,14*/ ObjectUpgradesData upgrades;
	/*0a0,30*/ undefined field_0xa0_0xd0[0x30];
	/*0d0,4*/ float PivotMaxZ;
	/*0d4,4*/ float PivotMinZ;
	/*0d8,6c*/ undefined field_0xd8_0x144[0x6c];
	/*144,4*/ unsigned int count_144;
	/*148,4*/ unsigned int flags;
	/*14c*/
};
static_assert(sizeof(BuildingData) == 0x14c, "");


struct PolyMeshData
{
	/*00,4*/ undefined4 field_0;
	/*04,4*/ undefined4 field_4;
	/*08,4*/ char* partName; // name of LoadObject file.lwo
	/*0c,4*/ unsigned int index;
	/*10,4*/ int int_10;
	/*14,4*/ PolyMeshData* previous;
	/*18*/
};
static_assert(sizeof(PolyMeshData) == 0x18, "");

struct VehicleData
{
	/*000,4*/ int objIndex;
	/*004,4*/ char* WheelNullName;
	/*008,4*/ ResourceData* aeResData1;
	/*00c,4*/ ResourceData* aeResData2; // Optional second ae file (seen for Grannit Grinder legs)
	/*010,18*/ ResourceData* WheelMeshes[6]; // LWO, false
	/*028,18*/ undefined4 wheel_fields_28[6];
	/*040,4*/ unsigned int numWheelNulls;
	/*044,18*/ undefined field_0x44_0x5c[0x18];
	/*05c,4*/ undefined4 field_5c;
	/*060,4*/ undefined4 field_60;
	/*064,4*/ float float_64;
	/*068,4*/ float WheelRadius;
	/*06c,48*/ undefined field_0x6c_0xb4[0x48];
	/*0b4,4*/ char* DrillNullName;
	/*0b8,4*/ char* DepositNullName;
	/*0bc,4*/ char* FireNullName; // "fire laser"
	/*0c0,4*/ char* DriverNullName;
	/*0c4,4*/ char* yPivot;
	/*0c8,4*/ char* xPivot;
	/*0cc,4*/ undefined4 field_cc;
	/*0d0,4*/ undefined4 field_d0;
	/*0d4,4*/ ResourceData* resData_d4;
	/*0d8,4*/ BOOL3 CameraFlipDir;
	/*0dc,4*/ char* CarryNullName;
	/*0e0,4*/ char* CameraNullName;
	/*0e4,1c*/ undefined4 carryFramesTable_e4[7];
	/*100,c*/ undefined field_0x100_0x10c[0xc];
	/*10c,10*/ undefined4 cameraFramesTable_10c[4];
	/*11c,4*/ unsigned int CarryNullFrames;
	/*120,4*/ unsigned int CameraNullFrames;
	/*124,14*/ ObjectUpgradesData upgrades;
	/*138,30*/ undefined field_0x138_0x168[0x30];
	/*168,4*/ float PivotMaxZ;
	/*16c,4*/ float PivotMinZ;
	/*170,54*/ undefined field_0x170_0x1c4[0x54];
	/*1c4,18*/ undefined4 table6_1c4[6];
	/*1dc,4*/ undefined4 field_1dc;
	/*1e0,4*/ PolyMeshData* subdata_1e0;
	/*1e4,4*/ PolyMeshData* subdata_1e4;
	/*1e8,4*/ unsigned int flags; // HoldMissing TRUE -> 0x8
	/*1ec*/
};
static_assert(sizeof(VehicleData) == 0x1ec, "");


struct FlockData
{
	/*00,4*/ FlockSubdata* flocksSubdata1;
	/*04,4*/ FlockSubdata* flocksSubdata2;
	/*08,4*/ unsigned int numSubdata;
	/*0c,4*/ unsigned int hasVector1;
	/*10,4*/ unsigned int hasVector2;
	/*14,4*/ undefined4 field_14;
	/*18,4*/ undefined4 field_18;
	/*1c,4*/ undefined4 field_1c;
	/*20,4*/ undefined4 field_20;
	/*24,4*/ undefined4 field_24;
	/*28*/
};
static_assert(sizeof(FlockData) == 0x28, "");

struct Struct_34
{
	/*00,4*/ unsigned int count_0; // seems to be a count
	/*04,4*/ undefined4 field_4;
	/*08,4*/ LwoFrame* lwoTable_8; // table ptr? -> 0x10 (struct: 0x70)
	/*0c,4*/ IDirect3DRMUserVisual* userVisual_c;
	/*10,4*/ IDirect3DRMViewport2* viewport_10; // IDirect3DRMViewport2 ?
	/*14,4*/ undefined4 param4_14;
	/*18,4*/ undefined4 unkFlags3_18;
	/*1c,4*/ void* ptr_1c;
	/*20,4*/ unsigned int refCount_20;
	/*24,4*/ Struct_34* struct34_24;
	/*28,4*/ IDirect3DRMFrame3* frame_28;
	/*2c,4*/ unsigned int flags;
	/*30,4*/ Struct_34* pool_m_next;
	/*34*/
};
static_assert(sizeof(Struct_34) == 0x34, "");

struct ResourceSubdata
{
	/*00,4*/ char* name;
	/*04,4*/ IDirect3DRMLight* light;
	/*08,4*/ IDirect3DRMMesh* mesh;
	/*0c,4*/ Struct_34* struct34_c;
	/*10*/
};
static_assert(sizeof(ResourceSubdata) == 0x10, "");

struct ActStruct_14 { // structure assigned to ResourceData->field_24 (allocated for ACT,ANIM resource types)
	/*00,4*/ ResourceData* resData; // (init: source of DuplicateResource)
	/*04,4*/ undefined4 field_4; // (init: 0)
	/*08,4*/ undefined4 field_8; // (init: 0)
	/*0c,4*/ IDirect3DRMFrame3* frame; // (init: ResourceData->frame2)
	/*10,4*/ BOOL isUsed; // (init: 1)
	/*14*/
};
static_assert(sizeof(ActStruct_14) == 0x14, "");

struct ResourceData
{
	/*00,4*/ IDirect3DRMFrame3* frame1;
	/*04,4*/ IDirect3DRMFrame3* frame2;
	/*08,4*/ IDirect3DRMFrame3* frame3;
	/*0c,4*/ ResourceSubdata* subdata_c;
	/*10,4*/ ResourceType resType;
	/*14,4*/ ResourceDataFlags flags;
	/*18,4*/ undefined4 field_18;
	/*1c,4*/ undefined4 field_1c;
	/*20,4*/ LiveObject* ownerObj;
	/*24,4*/ ActStruct_14* actstruct_24;
	/*28,4*/ ResourceData* pool_m_next;
	/*2c*/
};
static_assert(sizeof(ResourceData) == 0x2c, "");

// related to Terrain map?
struct LevelStruct_1c
{
	/*00,4*/ ResourceData* resData;
	/*04,8*/ Point2I position;
	/*0c,4*/ undefined4 field_c;
	/*10,4*/ LevelStruct_1c* next;
	/*14,4*/ LevelStruct_1c* previous;
	/*18,4*/ BOOL bool_18;
	/*1c*/
};
static_assert(sizeof(LevelStruct_1c) == 0x1c, "");

struct LevelBlock
{
	/*00,1*/ PredugType predug;
	/*01,1*/ SurfaceTexture texture;
	/*02,1*/ TerrainType terrain;
	/*03,1*/ unsigned char field_3;
	/*04,1*/ unsigned char blockpointer;
	/*05,1*/ CryOreType cryOre;
	/*06,1*/ ErodeType erodeSpeed;
	/*07,1*/ unsigned char field_7;
	/*08,4*/ LevelBlockFlags1 flags1;
	/*0c,4*/ LevelBlockFlags2 flags2;
	/*10,4*/ undefined4 field_10;
	/*14,4*/ float float_14;
	/*18,4*/ LevelStruct_1c* struct1c_18;
	/*1c,4*/ undefined4 field_1c;
	/*20,2*/ short randomness;
	/*22,1*/ undefined field_0x22;
	/*23,1*/ undefined field_0x23;
	/*24,4*/ unsigned int numLandSlides;
	/*28,4*/ unsigned int clickCount;
	/*2c,4*/ undefined4 field_2c;
	/*30,4*/ undefined4 field_30;
	/*34,1*/ unsigned char aiNode;
	/*35,1*/ undefined field_0x35;
	/*36,1*/ undefined field_0x36;
	/*37,1*/ undefined field_0x37;
	/*38,4*/ BOOL fallinUpper;
	/*3c,4*/ float fallinIntensity;
	/*40,4*/ float fallinTimer;
	/*44,4*/ undefined4 field_44;
	/*48*/
};
static_assert(sizeof(LevelBlock) == 0x48, "");


struct CreatureData
{
	/*00,4*/ int objIndex;
	/*04,4*/ ResourceData* aeResData; // ACT, true
	/*08,4*/ undefined4 field_8;
	/*0c,14*/ undefined field_0xc_0x20[0x14];
	/*20,4*/ char* CameraNullName;
	/*24,4*/ unsigned int CameraNullFrames;
	/*28,4*/ BOOL3 CameraFlipDir;
	/*2c,4*/ char* DrillNullName;
	/*30,4*/ char* FootStepNullName;
	/*34,4*/ char* CarryNullName;
	/*38,4*/ char* ThrowNullName;
	/*3c,4*/ char* DepositNullName;
	/*40,4*/ undefined4 field_40;
	/*44,4*/ undefined4 field_44;
	/*48,4*/ ResourceData* resData_48;
	/*4c,4*/ undefined4 field_4c;
	/*50,4*/ undefined4 field_50;
	/*54,10*/ undefined4 cameraFramesTable_54[4];
	/*64,4*/ PolyMeshData* subdata_64;
	/*68,4*/ PolyMeshData* subdata_68;
	/*6c,4*/ PolyMeshData* subdata_6c;
	/*70,4*/ unsigned int flags;
	/*74*/
};
static_assert(sizeof(CreatureData) == 0x74, "");


struct AITaskData
{
	/*00,4*/ AITaskType taskType;
	/*04,4*/ undefined4 field_4;
	/*08,8*/ Point2I position;
	/*10,4*/ LiveObject* object_10;
	/*14,4*/ float unkExpiryTime;
	/*18,4*/ float float_18;
	/*1c,4*/ unsigned int priorityValue;
	/*20,4*/ ObjectType objType;
	/*24,4*/ int objIndex;
	/*28,4*/ int objLevel;
	/*2c,4*/ undefined4 field_2c;
	/*30,8*/ Point2F pointf_30; // probably a table
	/*38,4*/ undefined field_0x38_0x3c[0x4];
	/*3c,4*/ undefined4 mode_3c;
	/*40,4*/ void* ptr_40;
	/*44,4*/ undefined field_0x44_0x48[0x4];
	/*48,4*/ LiveObject* object_48;
	/*4c,4*/ AIPriorityType priorityType;
	/*50,4*/ unsigned int taskStartTime;
	/*54,8*/ undefined field_0x54_0x5c[0x8];
	/*5c,4*/ unsigned int flags_5c; // not set means ptr_40 is assigned
	/*60,4*/ AITaskData* next; // assigned to DAT_004b4358
	/*64,4*/ AITaskData* pool_m_next;
	/*68*/
};
static_assert(sizeof(AITaskData) == 0x68, "");

struct LiveObject
{
	/*000,4*/ ObjectType objType;
	/*004,4*/ int objIndex;
	/*008,4*/ char* customName; // max size is 11 (NOT null-terminated)
	/*00c,4*/ VehicleData* vehicle;
	/*010,4*/ CreatureData* miniFigure;
	/*014,4*/ CreatureData* rockMonster;
	/*018,4*/ BuildingData* building;
	/*01c,4*/ ResourceData* other;
	/*020,4*/ UpgradeData* upgrade;
	/*024,4*/ void* routeptr_24; // Unknown pointer, likely in large allocated table
	/*028,4*/ unsigned int routingBlocksTotal; // total blocks to travel for current route
	/*02c,4*/ unsigned int routingBlocksCurrent; // number of blocks traveled (up to routingBlocksTotal)
	/*030,4*/ int value_30; // Usually 50 (0x32)
	/*034,190*/ float floats_34[100];
	/*1c4,c8*/ float floats_1c4[50];
	/*28c,c*/ Vector3F vector_28c;
	/*298,8*/ Point2F point_298;
	/*2a0,c*/ Vector3F vector_2a0;
	/*2ac,c*/ Vector3F faceDirection; // 1.0 to -1.0 directions that determine rotation with atan2
	/*2b8,4*/ float float_2b8;
	/*2bc,4*/ undefined4 field_2bc;
	/*2c0,4*/ undefined4 field_2c0;
	/*2c4,4*/ undefined4 field_2c4;
	/*2c8,4*/ undefined4 field_2c8;
	/*2cc,4*/ undefined4 field_2cc;
	/*2d0,4*/ undefined4 field_2d0;
	/*2d4,4*/ float float_2d4;
	/*2d8,4*/ BOOL unkbool_2d8;
	/*2dc,4*/ ResourceData* resData_2dc;
	/*2e0,4*/ int index_2e0;
	/*2e4,4*/ ResourceData* resData_2e4;
	/*2e8,4*/ const char* aitaskName1;
	/*2ec,4*/ const char* aitaskName2;
	/*2f0,4*/ AITaskData* aitask_2f0;
	/*2f4,8*/ Point2F point_2f4; // (assigned -1.0f)
	/*2fc,4*/ LiveObject* object_2fc; // other half of object_300
	/*300,4*/ LiveObject* object_300; // other half of object_2fc
	/*304,4*/ LiveObject* carryingThisObject;
	/*308,1c*/ LiveObject* carriedObjects[7];
	/*324,4*/ unsigned int numCarriedObjects;
	/*328,4*/ unsigned int field_328;
	/*32c,4*/ FlockData* flocksData_32c;
	/*330,4*/ unsigned int objLevel;
	/*334,4*/ ObjectStats* stats;
	/*338,4*/ float float_338;
	/*33c,4*/ float float_33c;
	/*340,4*/ float health; // (assigned -1.0f)
	/*344,4*/ float energy; // (assigned -1.0f)
	/*348,4*/ int* tableptr_348; // element size is 0x4
	/*34c,4*/ BOOL mode_34c;
	/*350,4*/ undefined4 field_350;
	/*354,4*/ undefined4 field_354;
	/*358,4*/ undefined4 field_358;
	/*35c,4*/ undefined4 field_35c;
	/*360,4*/ undefined4 field_360;
	/*364,4*/ undefined4 field_364;
	/*368,4*/ undefined4 field_368;
	/*36c,4*/ LiveObject* drivenObject; // same as drivingThisObject
	/*370,14*/ ToolType carriedTools[5];
	/*384,4*/ unsigned int numCarriedTools;
	/*388,4*/ undefined4 field_388;
	/*38c,4*/ undefined4 field_38c;
	/*390,4*/ undefined4 field_390;
	/*394,4*/ undefined4 field_394;
	/*398,4*/ undefined4 field_398;
	/*39c,4*/ undefined4 field_39c;
	/*3a0,4*/ undefined4 field_3a0;
	/*3a4,4*/ undefined4 field_3a4;
	/*3a8,4*/ undefined4 field_3a8;
	/*3ac,4*/ undefined4 field_3ac;
	/*3b0,4*/ undefined4 field_3b0;
	/*3b4,4*/ undefined4 field_3b4;
	/*3b8,4*/ undefined4 field_3b8;
	/*3bc,4*/ undefined4 field_3bc;
	/*3c0,4*/ LiveObject* object_3c0;
	/*3c4,4*/ undefined4 field_3c4;
	/*3c8,4*/ undefined4 field_3c8;
	/*3cc,4*/ LiveObject* object_3cc;
	/*3d0,4*/ undefined4 field_3d0;
	/*3d4,4*/ float elapsedTime1; // elapsed time counter 1
	/*3d8,4*/ float elapsedTime2; // elapsed time counter 2
	/*3dc,4*/ float activityElapsedTime; // elapsed time since last order?
	/*3e0,4*/ LiveFlags1 flags1_3e0;
	/*3e4,4*/ LiveFlags2 flags2_3e4;
	/*3e8,4*/ LiveFlags3 flags3_3e8; // (assigned 0, flags?)
	/*3ec,4*/ LiveFlags4 flags4_3ec;
	/*3f0,4*/ LiveFlags5 flags5_3f0; // (assigned 0, flags?)
	/*3f4,4*/ undefined4 field_3f4;
	/*3f8,4*/ undefined4 field_3f8;
	/*3fc,4*/ undefined4 field_3fc;
	/*400,4*/ undefined4 field_400;
	/*404,4*/ undefined4 field_404;
	/*408,4*/ LiveObject* pool_m_next;
	/*40c*/
};
static_assert(sizeof(LiveObject) == 0x40c, "");

struct ObjectStats
{
	/*000,4*/ undefined4 field_0; // == 0x30 for built-in object stats
	/*004,4*/ undefined4 field_4;
	/*008,4*/ undefined4 field_8;
	/*00c,4*/ undefined4 field_c;
	/*010,4*/ undefined4 field_10;
	/*014,4*/ undefined4 field_14;
	/*018,4*/ undefined4 field_18;
	/*01c,4*/ undefined4 field_1c;
	/*020,4*/ float RouteSpeed; // (leveled)
	/*024,48*/ float DrillTimes[18]; // (leveled, table of surface type times)
	/*06c,4*/ float CollRadius; // (effect: flags1 | 0x80)
	/*070,4*/ float AlertRadius;
	/*074,4*/ float CollHeight;
	/*078,4*/ float PickSphere;
	/*07c,4*/ float TrackDist;
	/*080,4*/ float HealthDecayRate;
	/*084,4*/ float EnergyDecayRate;
	/*088,4*/ float RepairValue; // (leveled)
	/*08c,4*/ float RestPercent;
	/*090,4*/ float CarryMinHealth;
	/*094,4*/ float StampRadius;
	/*098,4*/ float AttackRadius;
	/*09c,4*/ float WakeRadius; // (default: 20.0)
	/*0a0,8*/ Size2F CollBox; // (requires: invalid/no CollRadius, effect: flag 0x100, CollRadius = min(w,h) * 0.5)
	/*0a8,4*/ int BuildingBase; // (from: FUN_00408bb0, invalid: -1, either ptr or basenumber)
	/*0ac,4*/ int SurveyRadius; // (leveled)
	/*0b0,4*/ int CostOre;
	/*0b4,4*/ int CostCrystal;
	/*0b8,4*/ int CostRefinedOre;
	/*0bc,4*/ int CrystalDrain; // (leveled)
	/*0c0,4*/ int DrillSound; // (from: FUN_00464f30, invalid: 2 "SFX_Drill")
	/*0c4,4*/ int DrillFadeSound; // (from: FUN_00464f30, invalid: 3 "SFX_DrillFade")
	/*0c8,4*/ int EngineSound; // (from: FUN_00464f30, invalid: 0 "SFX_Bodge")
	/*0cc,4*/ int NumOfToolsCanCarry; // (leveled)
	/*0d0,4*/ int WaterEntrances;
	/*0d4,4*/ float RubbleCoef; // (default: 1.0)
	/*0d8,4*/ float PathCoef; // (default: 1.0)
	/*0dc,4*/ float OxygenCoef; // (negative consumes oxygen)
	/*0e0,4*/ int Capacity;
	/*0e4,4*/ float AwarenessRange; // (default: 0.0)
	/*0e8,4*/ float PainThreshold; // (default: 0.0)
	/*0ec,4*/ int MaxCarry; // (leveled)
	/*0f0,4*/ int CarryStart; // (leveled)
	/*0f4,4*/ float UpgradeTime; // (leveled, mult: 25.0)
	/*0f8,4*/ float FunctionCoef; // (leveled)
	/*0fc,4*/ int UpgradeCostOre; // Carry:Scan:Speed:Drill (requires all 4)
	/*100,4*/ int UpgradeCostStuds; // Carry:Scan:Speed:Drill (requires all 4)
	/*104,4*/ undefined4 field_104;
	/*108,4*/ undefined4 field_108;
	/*10c,4*/ float FreezerTime; // (default: 0.0)
	/*110,4*/ float FreezerDamage; // (default: 0.0)
	/*114,4*/ float PusherDist; // (default: 0.0)
	/*118,4*/ float PusherDamage; // (default: 0.0)
	/*11c,4*/ float LaserDamage; // (default: 0.0)
	/*120,4*/ float Flocks_Turn; // (default: 0.06)
	/*124,4*/ float Flocks_Speed; // (default: 2.0)
	/*128,4*/ float Flocks_Tightness; // (default: 2.0)
	/*12c,4*/ float Flocks_GoalUpdate; // (default: 2.0)
	/*130,4*/ float Flocks_Height; // (default: 30.0)
	/*134,4*/ float Flocks_Randomness; // (default: 2.0)
	/*138,4*/ float Flocks_AttackTime; // (default: 300.0)
	/*13c,4*/ int Flocks_Size; // (default: 5)
	/*140,4*/ float RandomMoveTime; // (default: 200.0)
	/*144,4*/ ObjectStatsFlags1 flags1;
	/*148,4*/ ObjectStatsFlags2 flags2;
	/*14c,4*/ ObjectStatsFlags3 flags3;
	/*150*/
};
static_assert(sizeof(ObjectStats) == 0x150, "");




#pragma pack(pop)



}