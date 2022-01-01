
// <LegoRR.exe @0042b780>
//void __cdecl lego::game::SurfaceMap_LoadTextureCoords(SurfaceMap* map)
void __cdecl lego::game::Lego_InitTextureMappings(SurfaceMap* map)
{
	// Floor types
	const SurfaceTexture floorTypes[31] = {
		TEXTURE_FLOOR_STD,
		TEXTURE_FLOOR_STD, // TEXTURE_FLOOR_STD2,
		TEXTURE_FLOOR_STD, // TEXTURE_FLOOR_STD3,
		TEXTURE_FLOOR_STD, // TEXTURE_FLOOR_REIN,
		TEXTURE_FLOOR_LAVA,
		TEXTURE_FLOOR_LAVA_NOTHOT,
		TEXTURE_FLOOR_WATER,
		TEXTURE_FLOOR_STD, // TEXTURE_FLOOR_DOZED,
		TEXTURE_FLOOR_PATH_FOUNDATION,
		TEXTURE_FLOOR_POWERED_FOUNDATION,
		TEXTURE_FLOOR_RUBBLE_MAX,
		TEXTURE_FLOOR_RUBBLE_HIGH,
		TEXTURE_FLOOR_RUBBLE_MED,
		TEXTURE_FLOOR_RUBBLE_LOW,
		TEXTURE_FLOOR_ERODE_LOW,
		TEXTURE_FLOOR_ERODE_MED,
		TEXTURE_FLOOR_ERODE_HIGH,
		TEXTURE_FLOOR_ERODE_MAX,
		TEXTURE_FLOOR_07,
		TEXTURE_FLOOR_PATH_BUILD,
		TEXTURE_FLOOR_PATH_4SIDES,
		TEXTURE_FLOOR_PATH_2SIDES,
		TEXTURE_FLOOR_PATH_CORNER,
		TEXTURE_FLOOR_PATH_3SIDES,
		TEXTURE_FLOOR_PATH_1SIDES,
		TEXTURE_FLOOR_POWERED_4SIDES,
		TEXTURE_FLOOR_POWERED_2SIDES,
		TEXTURE_FLOOR_POWERED_CORNER,
		TEXTURE_FLOOR_POWERED_3SIDES,
		TEXTURE_FLOOR_POWERED_1SIDES,
		TEXTURE_FLOOR_SLUGHOLE,
	};
	// Roof "surface" types
	const SurfaceTexture roofTypes[6] = { // Labeled as "TEXTURE_SURFACE_*" in RRPSX.
		TEXTURE_ROOF_STD, // TEXTURE_ROOF_STD,
		TEXTURE_ROOF_STD, // TEXTURE_ROOF_IMM,
		TEXTURE_ROOF_STD, // TEXTURE_ROOF_HARD,
		TEXTURE_ROOF_STD, // TEXTURE_ROOF_MED,
		TEXTURE_ROOF_STD, // TEXTURE_ROOF_LOOSE,
		TEXTURE_ROOF_STD, // TEXTURE_ROOF_SOIL,
	};
	// Forward-facing walls
	const SurfaceTexture forwardWalls[16] = {
		TEXTURE_WALL_IMM,
		TEXTURE_WALL_HARD,
		TEXTURE_WALL_MED,
		TEXTURE_WALL_LOOSE,
		TEXTURE_WALL_SOIL,
		TEXTURE_WALL_ORESEAM,
		TEXTURE_WALL_CRYSTALSEAM,
		TEXTURE_WALL_RECHARGESEAM,
		// Alternate styles "2": (unused)
		TEXTURE_WALL_IMM,   // TEXTURE_WALL_IMM2,
		TEXTURE_WALL_HARD,  // TEXTURE_WALL_HARD2,
		TEXTURE_WALL_MED,   // TEXTURE_WALL_MED2,
		TEXTURE_WALL_LOOSE, // TEXTURE_WALL_LOOSE2,
		TEXTURE_WALL_SOIL,  // TEXTURE_WALL_SOIL2,
		TEXTURE_WALL_ORESEAM,      // TEXTURE_WALL_ORESEAM2,
		TEXTURE_WALL_CRYSTALSEAM,  // TEXTURE_WALL_CRYSTALSEAM2,
		TEXTURE_WALL_RECHARGESEAM, // TEXTURE_WALL_RECHARGESEAM2,
	};
	// Forward-Reinforced walls
	const SurfaceTexture reinWalls[5] = {
		TEXTURE_REINWALL_IMM,
		TEXTURE_REINWALL_HARD,
		TEXTURE_REINWALL_MED,
		TEXTURE_REINWALL_LOOSE,
		TEXTURE_REINWALL_SOIL,
	};
	// Acute-corner walls
	const SurfaceTexture inCorners[5] = {
		TEXTURE_INCORNER_IMM,
		TEXTURE_INCORNER_HARD,
		TEXTURE_INCORNER_MED,
		TEXTURE_INCORNER_LOOSE,
		TEXTURE_INCORNER_SOIL,
	};
	const SurfaceTexture reinInCorners[5] = {
		TEXTURE_INCORNER_IMM,   // TEXTURE_REININCORNER_IMM,
		TEXTURE_INCORNER_HARD,  // TEXTURE_REININCORNER_HARD,
		TEXTURE_INCORNER_MED,   // TEXTURE_REININCORNER_MED,
		TEXTURE_INCORNER_LOOSE, // TEXTURE_REININCORNER_LOOSE,
		TEXTURE_INCORNER_SOIL,  // TEXTURE_REININCORNER_SOIL,
	};
	// Obtuse-corner walls
	const SurfaceTexture outCorners[5] = {
		TEXTURE_OUTCORNER_IMM,
		TEXTURE_OUTCORNER_HARD,
		TEXTURE_OUTCORNER_MED,
		TEXTURE_OUTCORNER_LOOSE,
		TEXTURE_OUTCORNER_SOIL,
	};
	const SurfaceTexture reinOutCorner[5] = {
		TEXTURE_OUTCORNER_IMM,   // TEXTURE_REINOUTCORNER_IMM,
		TEXTURE_OUTCORNER_HARD,  // TEXTURE_REINOUTCORNER_HARD,
		TEXTURE_OUTCORNER_MED,   // TEXTURE_REINOUTCORNER_MED,
		TEXTURE_OUTCORNER_LOOSE, // TEXTURE_REINOUTCORNER_LOOSE,
		TEXTURE_OUTCORNER_SOIL,  // TEXTURE_REINOUTCORNER_SOIL,
	};
	// Diagonal "gap" walls
	const SurfaceTexture diagonalWalls[5] = {
		TEXTURE_DIAGONAL_STD, // TEXTURE_DIAGONAL_IMM,
		TEXTURE_DIAGONAL_STD, // TEXTURE_DIAGONAL_HARD,
		TEXTURE_DIAGONAL_STD, // TEXTURE_DIAGONAL_MED,
		TEXTURE_DIAGONAL_STD, // TEXTURE_DIAGONAL_LOOSE,
		TEXTURE_DIAGONAL_STD, // TEXTURE_DIAGONAL_SOIL,
	};

	// Defines mappings for Floor<->Wall types:
	for (uint32 i = 0; i < _countof(floorTypes); i++) {

		for (uint32 j = 0; j < _countof(forwardWalls); j++) {
			Map3D_AddTextureMapping(map, floorTypes[i], forwardWalls[j]);
		}
		for (uint32 j = 0; j < _countof(reinWalls); j++) {
			Map3D_AddTextureMapping(map, floorTypes[i], reinWalls[j]);
		}

		for (uint32 j = 0; j < _countof(inCorners); j++) {
			Map3D_AddTextureMapping(map, floorTypes[i], inCorners[j]);
		}
		for (uint32 j = 0; j < _countof(reinInCorners); j++) {
			Map3D_AddTextureMapping(map, floorTypes[i], reinInCorners[j]); 
		}

		for (uint32 j = 0; j < _countof(outCorners); j++) {
			Map3D_AddTextureMapping(map, floorTypes[i], outCorners[j]);
		}
		for (uint32 j = 0; j < _countof(reinOutCorner); j++) {
			Map3D_AddTextureMapping(map, floorTypes[i], reinOutCorner[j]);
		}

		for (uint32 j = 0; j < _countof(diagonalWalls); j++) {
			Map3D_AddTextureMapping(map, floorTypes[i], diagonalWalls[j]);
		}
	}

	// Defines mappings for Roof<->Wall types:
	for (uint32 i = 0; i < _countof(roofTypes); i++) {
		// Anything past the first loop iteration is redundant, due to all entries being the same.
		// HOWEVER, this means assembly modifications are possible.

		for (uint32 j = 0; j < _countof(forwardWalls); j++) {
			Map3D_AddTextureMapping(map, roofTypes[i], forwardWalls[j]);
		}
		for (uint32 j = 0; j < _countof(reinWalls); j++) {
			Map3D_AddTextureMapping(map, roofTypes[i], reinWalls[j]);
		}

		for (uint32 j = 0; j < _countof(inCorners); j++) {
			Map3D_AddTextureMapping(map, roofTypes[i], inCorners[j]);
		}
		for (uint32 j = 0; j < _countof(reinInCorners); j++) {
			Map3D_AddTextureMapping(map, roofTypes[i], reinInCorners[j]);
		}

		for (uint32 j = 0; j < _countof(outCorners); j++) {
			Map3D_AddTextureMapping(map, roofTypes[i], outCorners[j]);
		}
		for (uint32 j = 0; j < _countof(reinOutCorner); j++) {
			Map3D_AddTextureMapping(map, roofTypes[i], reinOutCorner[j]);
		}

		for (uint32 j = 0; j < _countof(diagonalWalls); j++) {
			Map3D_AddTextureMapping(map, roofTypes[i], diagonalWalls[j]);
		}
	}
}

// <LegoRR.exe @0044f460>
//void __cdecl lego::game::SurfaceMap_AddTextureCoordMapping(SurfaceMap* map, SurfaceTexture texA, SurfaceTexture texB)
void __cdecl lego::map::Map3D_AddTextureMapping(Map3D* map, SurfaceTexture texA, SurfaceTexture texB)
{
	// Check if mapping is already added. If so, stop now to prevent duplicates.
	// Note: Since mappings are symmetrical, we don't need to search through `texsGrid[textB]` mappings.
	const uint32 texANum = map->texsNum[texA];
	for (uint32 i = 0; i < texANum; i++) {
		if (map->texsGrid[texA][i] == texB)
			return; // Mapping already exists, stop now.
	}

	// mapping not found, add texB to end of texA[] list
	map->texsGrid[texA][map->texsNum[texA]] = texB;
	map->texsNum[texA]++;

	// now create the reverse mapping, add texA to end of texB[] list
	map->texsGrid[texB][map->texsNum[texB]] = texA;
	map->texsNum[texB]++;
}

