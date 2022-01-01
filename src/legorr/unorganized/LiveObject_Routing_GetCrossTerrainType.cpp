
/* 0 = Can't Cross, 1 = Can Cross (floor), 2 = diagonal, 3 = wall */


//#define GetBlock(level,x,y) (level)->blocks[(level)->width * (y) + (x)]
#define GetBlock(x,y) Lego_GetLevel()->blocks[Lego_GetLevel()->width * (y) + (x)]


///NEWNAME: Lego_GetCrossTerrainType
int __cdecl LiveObject_Routing_GetCrossTerrainType(OPTIONAL LegoObject* liveObj, int bx1, int by1, int bx2, int by2, BOOL param_6)
{
	bool checkSingleWidthDig;
	bool checkEnterToolStore;
	bool checkWater;
	bool checkLand;
	bool checkLava;
	

	//const Lego_Level* level = Lego_GetLevel(); //legoGlobs.currLevel;
	const Lego_Block* block1 = &GetBlock(bx1, by1);

	bool checkEnterToolStore = false;
	bool checkWater = false;
	bool checkLand = true;
	bool checkLava = false;

	int result = 1;

	/*if (liveObj != NULL && (StatsObject_GetStatsFlags1(liveObj) & STATS1_CANBEDRIVEN) &&
		liveObj->driveObject == NULL)
	{
		return 0; // A driverless object can't do anything.
	}*/

	const Point2I DIRECTIONS[4] = {
		{  0, -1 },
		{  1,  0 },
		{  0,  1 },
		{ -1,  0 },
	};

	Direction dir = DIRECTION_UP;
	for (dir = DIRECTION_UP; dir < DIRECTION__COUNT; dir++) {
		
		if (bx1 == (bx2 + DIRECTIONS[dir].x) && by1 == (by2 + DIRECTIONS[dir].y))
			break;
	}

	if (liveObj != nullptr) {
		if ((StatsObject_GetStatsFlags1(liveObj) & STATS1_CANBEDRIVEN) &&
			liveObj->driveObject == nullptr)
		{
			return 0; // A driverless object can't do anything.
		}

		if (liveObj->type == LegoObject_ElectricFence) {
			return 0; // Electric Fences cannot move.
		}

		Point2I blockPos;
		if (!param_6 && LegoObject_GetBlockPos(liveObj, &blockPos.x, &blockPos.y) &&
			(bx1 == blockPos.x && by1 == blockPos.y))
		{
			return 1;
		}
		
		// Capabilities of object:
		checkSingleWidthDig = StatsObject_GetStatsFlags1(liveObj) & STATS1_SINGLEWIDTHDIG;
		checkEnterToolStore = StatsObject_GetStatsFlags3(liveObj) & STATS3_ENTERTOOLSTORE;
		checkWater = StatsObject_GetStatsFlags1(liveObj) & STATS1_CROSSWATER;
		checkLand = StatsObject_GetStatsFlags1(liveObj) & STATS1_CROSSLAND;
		checkLava = StatsObject_GetStatsFlags2(liveObj) & STATS2_CROSSLAVA;
	}
	else { // Capabilities when no object is specified:
		checkSingleWidthDig = false;
		checkEnterToolStore = false;
		checkWater = false;
		checkLand = true;
		checkLava = false;
	}


	if (block1->terrain == TERRAIN_LAKE && !checkWater) {
		return 0; // Don't want to drown.
	}

	if (block1->terrain != TERRAIN_LAKE && !checkLand) {
		return 0; // If we're not allowed on land, anything but Lake is... land...?
	}

	/*if (block1->terrain == TERRAIN_LAKE) {
		if (!checkWater) {
			return 0;
		}
		if (true) goto LAB_00431ea3;
	}
	if (!checkLand) {
		return 0;
	}
LAB_00431ea3:*/
	if (block1->terrain == TERRAIN_LAVA && !checkLava && !(block1->flags1 & BLOCK1_NOTHOT)) {
		// (NOTHOT flag is specific to an unused feature I think)
		return 0; // Hot lava, ouch! Can't cross.
	}

	if (block1->flags1 & BLOCK1_BUILDINGSOLID) {
		// (Normally units get instantly-shoved off solid buildings)
		return 0; // Buildings are never okay to route through.
	}

	if (param_6 && (block1->flags1 & BLOCK1_INCORNER)) {
		return 0;
	}

	if (!checkEnterToolStore && (block1->flags2 & BLOCK2_TOOLSTORE)) {
		return 0; // ToolStore is solid to this unit.
	}

	if (!checkSingleWidthDig) {
		if (!(block1->flags1 & BLOCK1_FLOOR)) {
			return 0;
		}
	}
	else {
		if (block1->predug == PREDUG_WALL) {
			return 0; // How this differs from the WALL flag condition, I'll never know...
		}

		if (block1->flags1 & BLOCK1_WALL) {
			// ****|WALL  -or-   ****
			// ****|WALL        |WALL|
			if ((GetBlock((bx1-1), by1).terrain == TERRAIN_LAVA) ||
				(GetBlock(bx1, (by1-1)).terrain == TERRAIN_LAVA))
			{
				return 0;
			}
			// ~~~~|WALL  -or-   ~~~~
			// ~~~~|WALL        |WALL|
			if ((GetBlock((bx1-1), by1).terrain == TERRAIN_WATER_unused) ||
				(GetBlock(bx1, (by1-1)).terrain == TERRAIN_WATER_unused))
			{
				return 0;
			}
			
			result = 3;
		}
		
		// Why is only DIRECTION_UP so special???
		if (dir == DIRECTION_UP) {
			if (block1->flags1 & BLOCK1_DIAGONAL) {
				result = 2;
			}
			if (GetBlock(bx2, by2).flags1 & BLOCK1_DIAGONAL) {
				result = 2;
			}
		}
	}

	if (bx2 != bx1 && by2 != by1) {
		// Yes, this is criss-crossing coordinates: bx1,by2 and bx2,by1.
		// Are the blocks adjacent of the start/end floors? If so.... what...?
		if ((GetBlock(bx1, by2).flags1 & BLOCK1_FLOOR) &&
			(GetBlock(bx2, by1).flags1 & BLOCK1_FLOOR))
		{
			result = 2;
		}
	}

	return result;
}

