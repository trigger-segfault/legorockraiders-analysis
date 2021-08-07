#pragma once
#include "BasicTypes.h"


// <https://kb.rockraidersunited.com/Map_file>

#pragma pack(push, 1)


#define MAPFILE_SIGNATURE "MAP "

struct MapFileInfo;


struct MapFileInfo
{
	/*00,4*/ char Signature[4]; // "MAP "
	/*04,4*/ unsigned int fileSize;
	/*08,8*/ Size2I dimensions;
	/*10,*/  unsigned short blocks[1];
};
static_assert(sizeof(MapFileInfo) == 0x12, "");


// Block Pointers map [tuto.map]
typedef unsigned char BlockPointerValue;

// CryOre map [cror.map]
enum CryOreType : unsigned char
{
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

// Emerge map [emrg.map]
enum EmergeType : unsigned char
{
	EMERGE_NONE     = 0x00,

	EMERGE_TRIGGER  = 0x01,
	EMERGE_POINT    = 0x02,
	EMERGE_UNUSED_3 = 0x03,
	EMERGE_UNUSED_4 = 0x04,
	EMERGE_UNUSED_5 = 0x05,
	EMERGE_UNUSED_6 = 0x06,

	EMERGE_INCREMENT = 0x6,
};
static_assert(sizeof(EmergeType) == 0x1, "");

// Erode map [erod.map]
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

// Fallin map [fall.map]
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

// Path map [path.map]
enum PathType : unsigned char
{
	PATH_NONE      = 0x00,
	PATH_RUBBLE    = 0x01,
	PATH_POWERPATH = 0x02,
};
static_assert(sizeof(PathType) == 0x1, "");

// Predug map [dugg.map]
enum PredugType : unsigned char
{
	PREDUG_WALL             = 0x00, // Undug wall (in exposed or hidden cavern)
	PREDUG_EXPOSED          = 0x01, // Exposed tile
	PREDUG_HIDDEN           = 0x02, // Undiscovered cavern tile
	PREDUG_EXPOSED_SLUGHOLE = 0x03, // Exposed Slimy Slug Hole
	PREDUG_HIDDEN_SLUGHOLE  = 0x04, // Undiscovered cavern Slimy Slug Hole
};
static_assert(sizeof(PredugType) == 0x1, "");

// Surface map [high.map]
typedef unsigned short SurfaceValue;

// Terrain map [surf.map]
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


// AI map [???.map]


// [World\WorldTextures\BIOMESplit\BIOME*.bmp]
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


#pragma pack(pop)
