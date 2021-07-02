
#define s_MAP_SIGNATURE "MAP "


typedef short MAPTutorialBlock;

//struct MAPTutorialBlock
//{
//	/*0,2*/ short blockPointer; // (1-255) 0 if not a pointer
//	/*2*/
//};

enum MAPCryOreBlock : short
{
	CRYORE_NONE         = 0,

	CRYORE_CRYSTAL_1_A  = 1,
	CRYORE_ORE_1_A      = 2,
	CRYORE_CRYSTAL_1_B  = 3,
	CRYORE_ORE_1_B      = 4,

	CRYORE_CRYSTAL_3_A  = 5,
	CRYORE_ORE_3_A      = 6,
	CRYORE_CRYSTAL_3_B  = 7,
	CRYORE_ORE_3_B      = 8,

	CRYORE_CRYSTAL_5_A  = 9,
	CRYORE_ORE_5_A      = 10,
	CRYORE_CRYSTAL_5_B  = 11,
	CRYORE_ORE_5_B      = 12,

	CRYORE_CRYSTAL_10_A = 13,
	CRYORE_ORE_10_A     = 14,
	CRYORE_CRYSTAL_10_B = 15,
	CRYORE_ORE_10_B     = 16,

	CRYORE_CRYSTAL_25_A = 17,
	CRYORE_ORE_25_A     = 18,
	CRYORE_CRYSTAL_25_B = 19,
	CRYORE_ORE_25_B     = 20,
};

enum MAPEmergeBlock : short
{
	EMERGE_NONE         = 0,

	EMERGE_TRIGGER      = 1,
	EMERGE_EMERGE       = 2,
	EMERGE_UNUSED_3     = 3,
	EMERGE_UNUSED_4     = 4,
	EMERGE_UNUSED_5     = 5,
	EMERGE_UNUSED_6     = 6,

	EMERGE_INCREMENT    = 6,
};
enum MAPErosionBlock : short
{
	EROSION_NONE             = 0,

	EROSION_LAVA_VERYSLOW    = 1,
	EROSION_ALWAYS_VERYSLOW  = 2,

	EROSION_LAVA_SLOW        = 3,
	EROSION_ALWAYS_SLOW      = 4,

	EROSION_LAVA_MEDIUM      = 5,
	EROSION_ALWAYS_MEDIUM    = 6,

	EROSION_LAVA_FAST        = 7,
	EROSION_ALWAYS_FAST      = 8,

	EROSION_LAVA_VERYFAST    = 9,
	EROSION_ALWAYS_VERYFAST  = 10,

///TODO: What speed does reverse erosion take place in?
	EROSION_REVERSE_VERYFAST = 12,

	EROSION_REVERSE_FAST     = 14,

	EROSION_REVERSE_MEDIUM   = 16,

	EROSION_REVERSE_SLOW     = 18,

	EROSION_REVERSE_VERYSLOW = 20,

///TODO: What speed does reverse erosion take place in?
/*	EROSION_REVERSE_VERYSLOW = 12,

	EROSION_REVERSE_SLOW     = 14,

	EROSION_REVERSE_MEDIUM   = 16,

	EROSION_REVERSE_FAST     = 18,

	EROSION_REVERSE_VERYFAST = 20,*/
};

// <https://kb.rockraidersunited.com/Map_file#Terrain_map>
// Ore seam
// The Crystal seem
// Soil is unused
