


// Possible module names:
//  Water*, Wall*, Wait*
/// PUBLIC: Level_LoadLevelCFG
// <LegoRR.exe @0046de50>
void __cdecl Water_Initialise(Container_t *contRoot, LevelData *level)
{
  globs::waterGlobs.entryCount = 0;
  globs::waterGlobs.pairCount  = 0;
  // Assigned, but never used, level->DigDepth is always used instead
  globs::waterGlobs.digDepth = level->DigDepth;

  for (uint y = 0; y < level->dimensions.height; y++) {
    uint water_xMax = 0;
    uint water_xAlign = 0;

    for (uint x = 0; x < level->dimensions.width; x++) {
      if (level->blocks[level->dimensions.width * y + x].terrain == TERRAIN_WATER_unused /*7*/) {
        if (water_xAlign == water_xMax) {
          water_xAlign = x;
        }
        water_xMax = x + 1;
      }
      else {
        if (water_xAlign != water_xMax) {
          WaterEntry_t* entry = Water_InitSearchAddPairs(y, water_xAlign, water_xMax);
          if (entry == nullptr) {
            Water_InitAddPointFirst(y, water_xAlign, water_xMax);
          }
          else {
            Water_InitAddPoint(entry, y, water_xAlign, water_xMax);
          }
        }
        water_xMax = 0;
        water_xAlign = 0;
      }
    }
  }

  for (uint i = 0; i < globs::waterGlobs.pairCount; i++) {
    WaterEntry_t *second = globs::waterGlobs.pairTable[i].second;
    WaterEntry_t *first  = lobs::waterGlobs.pairTable[i].first;

    if (second->pointCount != 0) {
			// some form of overlapped copying...?
			std::memset(&first->points[first->pointCount], &second->points[0], sizeof(Point2F) * second->pointCount);
			first->pointCount  += second->pointCount;
			second->pointCount = 0;
    }
  }

  // Sort by pointCount, highest to lowest
  std::qsort(&globs::waterGlobs.entryTable, globs::waterGlobs.entryCount, 0x428, Water_QsortCompare);

	// Then cap entryCount to number of entries with non-zero pointCount's
  for (uint i = 0; i < globs::waterGlobs.entryCount; i++) {
    if (globs::waterGlobs.entryTable[i].pointCount == 0) {
      globs::waterGlobs.entryCount = i;
    }
  }

  Water_InitGroups(contRoot, level);
  Water_InitVertices(contRoot, level);
  return;
}

/// PRIVATE:
// <LegoRR.exe @0046ec60>
int __cdecl Water_QsortCompare(WaterEntry_t *a, WaterEntry_t *b)
{
  if (b->pointCount < a->pointCount)
    return -1;
  if (b->pointCount > a->pointCount)
    return  1;
  return 0;
}

/// PRIVATE:
// <LegoRR.exe @0046dfd0>
void __cdecl Water_InitGroups(Container_t *contRoot, LevelData *level)
{
  TerrainType TVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  float *pfVar6;
  longlong lVar7;
  Point2F_t *local_30;
  uint local_2c;
  uint *local_28;
  uint index;

  // see Direction enum: { DIRECTION_UP, DIRECTION_RIGHT, DIRECTION_DOWN, DIRECTION_LEFT }
	const Point2F_t DIRECTIONS[4] = {
		{  0.0f, -1.0f },
		{  1.0f,  0.0f },
		{  0.0f,  1.0f },
		{ -1.0f,  0.0f },
	};

  
	for (uint i = 0; i < globs::waterGlobs.entryCount; i++) {
		
		// Struct_428_ARRAY_0054a520[i].groupCount = 0;
		WaterEntry_t *entry = &globs::waterGlobs.entryTable[i];
		entry->groupCount = 0;

		for (unsigned int j = 0; j < entry->pointCount; j++) {

			for (int k = 0; k < 4; k++) {
				// lVar7 = __ftol((float10)dir->x + (float10)local_30->x);
				// x = (int)lVar7;
				// lVar7 = __ftol((float10)local_30->y + (float10)dir->y);
				// y = (int)lVar7;
				int x = (entry->points[j].x + DIRECTIONS[k].x);
				int y = (entry->points[j].y + DIRECTIONS[k].y);
				if ((x >= 0 && x < level->dimensions.width) && (y >= 0 && y < level->dimensions.height) &&
				  (level->blocks[y * level->dimensions.width + x].terrain != TERRAIN_WATER_unused /*0x7*/) &&
					(level->blocks[y * level->dimensions.width + x].terrain != TERRAIN_IMMOVABLE /*0x1*/))
				{
					entry->groups[entry->groupCount].index = j; // point index
					entry->groups[entry->groupCount].direction = (Direction)k; // direction index
					entry->groupCount++;
					break;
				}
			}
		}
	}
  return;
  
  DIRECTIONS[0].x = 0.0;
  DIRECTIONS[0].y = -1.0;
  DIRECTIONS[1].x = 1.0;
  DIRECTIONS[1].y = 0.0;
  DIRECTIONS[2].x = 0.0;
  DIRECTIONS[2].y = 1.0;
  DIRECTIONS[3].x = -1.0;
  DIRECTIONS[3].y = 0.0;
  index = 0;
  if (globs::waterGlobs.entryCount != 0) {
    local_28 = &globs::waterGlobs.entryTable[0].pointCount;
    do {
      local_30 = (Point2F_t *)(local_28 + -200);
      local_28[0x3d] = 0;
      local_2c = 0;
      if (*local_28 != 0) {
        do {
          uVar5 = 0;
          pfVar6 = &DIRECTIONS[0].y;
          do {
            lVar7 = __ftol((float10)pfVar6[-1] + (float10)local_30->x);
            iVar3 = (int)lVar7;
            lVar7 = __ftol((float10)local_30->y + (float10)*pfVar6);
            iVar4 = (int)lVar7;
            if ((((-1 < iVar3) && (iVar2 = (level->dimensions).width, iVar3 < iVar2)) &&
                (-1 < iVar4)) &&
               (((iVar4 < (level->dimensions).height &&
                 (TVar1 = level->blocks[iVar4 * iVar2 + iVar3].terrain,
                 TVar1 != TERRAIN_WATER_unused)) && (TVar1 != TERRAIN_IMMOVABLE)))) {
              local_28[local_28[0x3d] * 6 + 1] = local_2c;
              local_28[local_28[0x3d] * 6 + 2] = uVar5;
              local_28[0x3d] = local_28[0x3d] + 1;
              break;
            }
            uVar5 += 1;
            pfVar6 = pfVar6 + 2;
          } while (uVar5 < 4);
          local_30 = local_30 + 1;
          local_2c += 1;
        } while (local_2c < *local_28);
      }
      index += 1;
      local_28 = local_28 + 0x10a;
    } while (index < globs::waterGlobs.entryCount);
  }
  return;
}

/// PRIVATE:
// <LegoRR.exe @0046e140>
void __cdecl Water_InitVertices(Container_t *contRoot, LevelData *level)
{
  int iVar1;
  float fVar2;
  uint uVar3;
  Container_t *cont;
  D3DRMGroupIndex groupID;
  float *pfVar4;
  uint uVar5;
  float *pfVar6;
  Point2F_t *pPVar7;
  float *pfVar8;
  longlong lVar9;
  longlong lVar10;
  Vector3F_t *pVVar11;
  uint j;
  uint *local_134;
  float *local_130;
  int local_12c;
  uint i;
  float TU_COORDS [4];
  float TV_COORDS [4];
  uint FACEDATA [6];
  Point2F_t DIRECTIONS_F [4];
  Vector3F_t vertPoses [4];
  D3DRMVertex vertices [4];
  
  FACEDATA[1] = 1;
  FACEDATA[3] = 1;
  DIRECTIONS_F[0].x = 0.0;
  DIRECTIONS_F[0].y = 0.0;
  DIRECTIONS_F[1].x = 1.0;
  DIRECTIONS_F[1].y = 0.0;
  DIRECTIONS_F[2].x = 1.0;
  DIRECTIONS_F[2].y = 1.0;
  DIRECTIONS_F[3].x = 0.0;
  DIRECTIONS_F[3].y = 1.0;
  FACEDATA[0] = 0;
  FACEDATA[2] = 3;
  FACEDATA[4] = 2;
  FACEDATA[5] = 3;
  TU_COORDS[0] = 0.0;
  TU_COORDS[1] = 1.0;
  TU_COORDS[2] = 1.0;
  TU_COORDS[3] = 0.0;
  TV_COORDS[0] = 0.0;
  TV_COORDS[1] = 0.0;
  TV_COORDS[2] = 1.0;
  TV_COORDS[3] = 1.0;
  i = 0;
  if (globs::waterGlobs.entryCount != 0) {
    local_134 = &globs::waterGlobs.entryTable[0].pointCount;
    do {
      pfVar8 = (float *)(local_134 + -200);
                    /* entryTable[i].float_z_418 = -10000.0; */
      local_134[0x3e] = 0xc61c4000;
      j = 0;
      pfVar6 = pfVar8;
      if (*local_134 != 0) {
        do {
          pVVar11 = vertPoses;
          lVar9 = __ftol((float10)pfVar6[1]);
          uVar3 = (uint)lVar9;
          lVar9 = __ftol((float10)*pfVar6);
          Map3D_GetBlockVertexPositions(level->surfaceMap,(uint)lVar9,uVar3,pVVar11);
          local_130 = &vertPoses[0].z;
          pPVar7 = DIRECTIONS_F;
          local_12c = 4;
          do {
            lVar9 = __ftol((float10)pPVar7->y + (float10)pfVar6[1]);
            iVar1 = (level->dimensions).width;
            lVar10 = __ftol((float10)*pfVar6 + (float10)pPVar7->x);
            if (level->blocks[(int)lVar9 * iVar1 + (int)lVar10].predug == PREDUG_WALL) {
              if ((ushort)((ushort)(*local_130 < (float)local_134[0x3e]) << 8 |
                          (ushort)(*local_130 == (float)local_134[0x3e]) << 0xe) == 0) {
                    /* entryTable[i].dig_z_418 = vertPoses[k].z; */
                local_134[0x3e] = (uint)*local_130;
              }
            }
            else {
              local_134[0x41] |= WATER_HIDDEN /*0x1*/;
            }
            pPVar7 = pPVar7 + 1;
            local_130 = local_130 + 3;
            local_12c += -1;
          } while (local_12c != 0);
          j += 1;
          pfVar6 = pfVar6 + 2;
        } while (j < *local_134);
      }
                    /* entryTable[i].float_z2_41c = entryTable[i].float_z_418; */
      local_134[0x3f] = local_134[0x3e];
      cont = res::Container_MakeMesh2(contRoot,CONTAINER_MESHTYPE_TRANSPARENT);
      local_134[0x40] = (uint)cont;
      res::Container_Hide(cont,~local_134[0x41] & WATER_HIDDEN /*0x1*/);
      j = 0;
      if (*local_134 != 0) {
        do {
          groupID = res::Container_Mesh_AddGroup((Container_t *)local_134[0x40],4,2,3,FACEDATA);
          res::Container_Mesh_SetColourAlpha((Container_t *)local_134[0x40],groupID,0.0,0.3,0.8,0.6);
          pVVar11 = vertPoses;
          lVar9 = __ftol((float10)pfVar8[1]);
          uVar3 = (uint)lVar9;
          lVar9 = __ftol((float10)*pfVar8);
          Map3D_GetBlockVertexPositions(level->surfaceMap,(uint)lVar9,uVar3,pVVar11);
          pfVar6 = &vertPoses[0].y;
          pfVar4 = &vertices[0].position.y;
          uVar3 = 0;
          do {
                    /* vertices[k].position.x = vertPoses[k].x;
                       vertices[k].position.y = vertPoses[k].y;
                       vertices[k].position.z = entryTable[i].float_z_418;
                       vertices[k].normal.x = 0.0f;
                       vertices[k].normal.y = 0.0f;
                       vertices[k].normal.z = -1.0f;
                       vertices[k].tu = TU_COORDS[k];
                       vertices[k].tv = TV_COORDS[k];
                       vertices[k].colour = 0; */
            pfVar4[-1] = pfVar6[-1];
            *pfVar4 = *pfVar6;
            pfVar4[1] = (float)local_134[0x3e];
            uVar5 = uVar3 + 4;
            pfVar6 = pfVar6 + 3;
            pfVar4[2] = 0.0;
            pfVar4[3] = 0.0;
            pfVar4[4] = -1.0;
            fVar2 = *(float *)((int)TU_COORDS + uVar3);
            pfVar4[7] = 0.0;
            pfVar4[5] = fVar2;
            pfVar4[6] = *(float *)((int)TV_COORDS + uVar3);
            pfVar4 = pfVar4 + 9;
            uVar3 = uVar5;
          } while (uVar5 < 0x10);
          res::Container_Mesh_SetVertices((Container_t *)local_134[0x40],j,0,4,vertices);
          j += 1;
          pfVar8 = pfVar8 + 2;
        } while (j < *local_134);
      }
      i += 1;
      local_134 = local_134 + 0x10a;
    } while (i < globs::waterGlobs.entryCount);
  }
  return;
}

// This function can be completely ignored, since there's not actual information on what
// logf_removed is doing.
/// PUBLIC: Game_SetViewMode
// <LegoRR.exe @0046e480>
void __cdecl lego::debug::Water_Debug_LogContainerMesh(BOOL logWithValues)
{
  Container_t **ppCVar1;
  uint i;
  Container_t *message;
  undefined4 uVar2;
  undefined4 uVar3;
  
  i = 0;
  if (globs::waterGlobs.entryCount != 0) {
    ppCVar1 = &globs::waterGlobs.entryTable[0].contMeshTrans;
    do {
      if (logWithValues == 0) {
                    /* contMeshTrans (Container_t*), 0.0, 0.0 */
        message = *ppCVar1;
        uVar3 = 0;
        uVar2 = 0;
      }
      else {
        message = *ppCVar1;
                    /* contMeshTrans (Container_t*), 0.12, 0.32 */
        uVar3 = 1050924810;
        uVar2 = 1039516304;
      }
      util::logf_removed((char *)message,0,uVar2,uVar3);
      i += 1;
      ppCVar1 = ppCVar1 + 0x10a;
    } while (i < globs::waterGlobs.entryCount);
  }
  return;
}


/// PUBLIC: Level_DestroyWall
// <LegoRR.exe @0046e4e0>
void __cdecl Water_Block_DestroyWallComplete(LevelData *level, int param_2, uint param_3)
{
  const Point2I_t VERT_OFFSETS[4] = {
    { 0, 1 },
    { 1, 2 },
    { 2, 3 },
    { 3, 0 },
  };

  uint index;
  WaterEntry_t *entry = Water_Block_SubDestroyWall_AndDebug_WKey(param_2, param_3, &index);
  if (entry != nullptr) {
    entry->flags &= ~WATER_STATE_B /*~0x4*/;
    entry->flags |= WATER_HIDDEN /*0x1*/;

    res::Container_Hide(entry->contMeshTrans, false);

    WaterEntryGroup_t *group = &entry->groups[index];
    group->bool_14  = true;
    group->float_c  = 0.0f;
    group->float_10 = 0.0f;

    uint by = __ftol(entry->points[group->index].y);
    uint bx = __ftol(entry->points[group->index].x);
    Map3D_GetBlockVertexPositions(level->surfaceMap, bx, by, vertPoses);

    // min (-x, -y) for vertPoses[VERT_OFFSETS[group->direction].<x|y>].z
    Point2F_t vertDirZ = {
      vertPoses[ VERT_OFFSETS[group->direction].x ].z,
      vertPoses[ VERT_OFFSETS[group->direction].y ].z
    };
    group->float_maxDirZ_8 = std::max(vertDirZ.x, vertDirZ.y);

    // if (vertDirZ.x > vertDirZ.y)
    //   group->float_maxDirZ_8 = vertDirZ.x;
    // else
    //   group->float_maxDirZ_8 = vertDirZ.y;

    // group->float_maxDirZ_8 = 
    // float fVar2 = -vertPoses[VERT_OFFSETS[group->direction].x].z;
    // if (-vertPoses[VERT_OFFSETS[group->direction].y].z <= -vertPoses[VERT_OFFSETS[group->direction].x].z) {
    //   fVar2 = -vertPoses[VERT_OFFSETS[group->direction].y].z;
    // }
    // group->float_maxDirZ_8 = -fVar2;
    // // group->float_maxDirZ_8 = -fVar3;
  }
  return;
}

/// PUBLIC: Level_Debug_WKey_NeedsBlockFlags1_8_FUN_004303a0
// <LegoRR.exe @0046e5f0>
void __cdecl Water_Block_Debug_WKey(uint bx, uint by)
{
  uint index;
  WaterEntry_t *entry = Water_Block_SubDestroyWall_AndDebug_WKey(bx, by, &index);
  if (entry != nullptr) {
    entry->flags &= ~WATER_STATE_A /*~0x2*/;
    entry->flags |= WATER_HIDDEN /*0x1*/;
    res::Container_Hide(entry->contMeshTrans, false);
    entry->groups[index].bool_14 = false;
  }
  return;
}

/// PUBLIC: LRR_MainLoop
// <LegoRR.exe @0046e650>
void __cdecl Water_Update(LevelData *level, float elapsedGame)
{
  float fVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  bool bVar5;
  float *pfVar6;
  int iVar7;
  uint uVar8;
  uint *puVar9;
  D3DRMGroupIndex groupID;
  bool bVar10;
  uint unkCount;
  uint i;
  D3DRMVertex vertices[4];

  for (uint i = 0; i < globs::waterGlobs.entryCount; i++) {
    WaterEntry_t *entry = &globs::waterGlobs.entryTable[i];

    bool bState_A = false;
    // this isn't a mistake, flags alternate, so 0x4 only works if 0x2 is false
    bool bState_B = !(entry->flags & WATER_STATE_A /*0x2*/);
    float dig_z2 = entry->dig_z_418;

    for (uint j = 0; j < globs::waterGlobs.entryTable[i].groupCount; j++) {
      WaterEntryGroup_t *group = &globs::waterGlobs.entryTable[i].groups[j];

      bool bElapseFloat10 = false; // if true, update float_10 elapsed time
      if (!group->bool_14 || group->float_maxDirZ_8 < entry->dig_z2_41c) {
          // ((ushort)((ushort)((float)puVar9[2] < *pfVar6) << 8 |
          //         (ushort)((float)puVar9[2] == *pfVar6) << 0xe) == 0)) {
LAB_0046e6eb:
        bElapseFloat10 = true;
      }
      else {
        if (dig_z2 < group->float_maxDirZ_8)
          dig_z2 = group->float_maxDirZ_8;

        unkCount += 1;
        bState_B = false;
        bState_A = true;
        if (group->float_maxDirZ_8 == entry->dig_z2_41c)
          bElapseFloat10 = true;
      }

      group->float_c += elapsedGame * 1.5f;
      if (bElapseFloat10)
        group->float_10 += elapsedGame * 0.5f;

      if (group->float_c  > 240.0f)
        group->float_c  = 240.0f;

      if (group->float_10 > 240.0f)
        group->float_10 = 240.0f;

    }

    if (globs::waterGlobs.entryTable[i].flags & WATER_STATE_B /*0x4*/)
      bState_A = false;


    if (bState_A || bState_B) {

      float dig_diff = (entry->dig_z2_41c - entry->dig_z_418) / level->DigDepth;

      if (bState_A) {
        entry->flags &= ~WATER_STATE_A /*~0x2*/;
        entry->dig_z2_41c += ((float)unkCount * elapsedGame * 0.3f) / (dig_diff + 1.0f);
        if (dig_z2 <= entry->dig_z2_41c) {
          entry->dig_z2_41c = dig_z2;
          entry->flags |= WATER_STATE_B /*0x4*/;
        }
      }
      else {
        entry->flags &= ~WATER_STATE_B /*~0x4*/;
        entry->dig_z2_41c -= elapsedGame * 0.05;
        if (dig_z2 >= entry->dig_z2_41c) {
          entry->dig_z2_41c = dig_z2;
          entry->flags |= WATER_STATE_A /*0x2*/;
        }
      }
      // rgb(  0, 76,204) + alpha change
      res::Container_SetColourAlpha(entry->contMeshTrans, 0.0f, 0.3f, 0.8f, 0.6f - dig_diff * 0.4f);

      for (uint j = 0; j < globs::waterGlobs.entryTable[i].pointCount; j++) {
        //Point2F_t *pPoint = &globs::waterGlobs.entryTable[i].points[j]; (not used, just the count)
        
        res::Container_Mesh_GetVertices(entry->contMeshTrans, j /*groupID*/, 0, 4, vertices);

        // copy to vertices Z positions
        for (int k = 0; k < 4; k++) {
          vertices[k].z = entry->dig_z2_41c;
        }
        res::Container_Mesh_SetVertices(entry->contMeshTrans, j /*groupID*/, 0, 4, vertices);
      }
    }

  }
  Water_UpdateMap3DBlocks(level);
  return;
}

/// PRIVATE:
// <LegoRR.exe @0046e8d0>
void __cdecl Water_UpdateMap3DBlocks(LevelData *level)
{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  uint *puVar4;
  longlong lVar5;
  Vector3F_t *pVVar6;
  uint by;
  uint bx;
  uint i;
  uint j;

  Point2F_t worldPos;
  Vector3F_t vertPoses[4];

	const Vector3F_t DIRECTIONS3[4] = {
		{  0.0f,  1.0f,  0.0f },
		{  1.0f,  0.0f,  0.0f },
		{  0.0f, -1.0f,  0.0f },
		{ -1.0f,  0.0f,  0.0f },
	};

  const Point2I_t VERT_OFFSETS[4] = {
    { 0, 1 },
    { 1, 2 },
    { 2, 3 },
    { 3, 0 },
  };
  
  // VERT_OFFSETS[0].x = 0;
  // VERT_OFFSETS[0].y = 1;
  // VERT_OFFSETS[1].x = 1;
  // VERT_OFFSETS[1].y = 2;
  // VERT_OFFSETS[2].x = 2;
  // VERT_OFFSETS[2].y = 3;
  // VERT_OFFSETS[3].x = 3;
  // VERT_OFFSETS[3].y = 0;
  // DIRECTIONS3[0].x = 0.0;
  // DIRECTIONS3[0].y = 1.0;
  // DIRECTIONS3[0].z = 0.0;
  // DIRECTIONS3[1].x = 1.0;
  // DIRECTIONS3[1].y = 0.0;
  // DIRECTIONS3[1].z = 0.0;
  // DIRECTIONS3[2].x = 0.0;
  // DIRECTIONS3[2].y = -1.0;
  // DIRECTIONS3[2].z = 0.0;
  // DIRECTIONS3[3].x = -1.0;
  // DIRECTIONS3[3].y = 0.0;
  // DIRECTIONS3[3].z = 0.0;

  for (uint i = 0; i < globs::waterGlobs.entryCount; i++) {
    for (uint j = 0; j < globs::waterGlobs.entryTable[i].groupCount; j++) {

      uint idx = globs::waterGlobs.entryTable[i].groups[j].index;
      uint by = __ftol(globs::waterGlobs.entryTable[i].points[idx].y);
      uint bx = __ftol(globs::waterGlobs.entryTable[i].points[idx].x);
      Map3D_GetBlockVertexPositions(level->surfaceMap, bx, by, vertPoses);

      Direction dir = globs::waterGlobs.entryTable[i].groups[j].direction;
      float dirMult = globs::waterGlobs.entryTable[i].groups[j].float_c;
      worldPos.x = DIRECTIONS3[dir].x * dirMult + (vertPoses[VERT_OFFSETS[dir].x].x + vertPoses[VERT_OFFSETS[dir].y].x) / 2.0f;
      worldPos.y = DIRECTIONS3[dir].y * dirMult + (vertPoses[VERT_OFFSETS[dir].x].y + vertPoses[VERT_OFFSETS[dir].y].y) / 2.0f;
      Map3D_WorldToBlockPos_NoZ(level->surfaceMap, worldPos.x, worldPos.y, &bx, &by);
      Level_Block_SetFlags1_200_AndUpdateSurface_LevelStruct428(level, bx, by, true);

      idx = globs::waterGlobs.entryTable[i].groups[j].index;
      by = __ftol(globs::waterGlobs.entryTable[i].points[idx].y);
      bx = __ftol(globs::waterGlobs.entryTable[i].points[idx].x);
      Map3D_GetBlockVertexPositions(level->surfaceMap, bx, by, vertPoses);

      dir = globs::waterGlobs.entryTable[i].groups[j].direction;
      dirMult = globs::waterGlobs.entryTable[i].groups[j].float_10;
      worldPos.x = DIRECTIONS3[dir].x * dirMult + (vertPoses[VERT_OFFSETS[dir].x].x + vertPoses[VERT_OFFSETS[dir].y].x) / 2.0f;
      worldPos.y = DIRECTIONS3[dir].y * dirMult + (vertPoses[VERT_OFFSETS[dir].x].y + vertPoses[VERT_OFFSETS[dir].y].y) / 2.0f;
      Map3D_WorldToBlockPos_NoZ(level->surfaceMap, worldPos.x, worldPos.y, &bx, &by);
      Level_Block_SetFlags1_200_AndUpdateSurface_LevelStruct428(level, bx, by, false);
    }
  }

  return;
}


/// PUBLIC: Level_Debug_WKey_NeedsBlockFlags1_8_FUN_004303a0
// <LegoRR.exe @0046eb60>
WaterEntry_t * __cdecl Water_Block_SubDestroyWall_AndDebug_WKey(uint bx, uint by, uint *out_index)
{
  uint j;
  WaterEntryGroup_t *pIVar1;
  WaterEntryGroup_t *pGroup;
  // float10 extraout_ST0;
  longlong lVar2;
  uint i;

  // see Direction enum: { DIRECTION_UP, DIRECTION_RIGHT, DIRECTION_DOWN, DIRECTION_LEFT }
	const Point2F_t DIRECTIONS[4] = {
		{  0.0f, -1.0f },
		{  1.0f,  0.0f },
		{  0.0f,  1.0f },
		{ -1.0f,  0.0f },
	};

  if (globs::waterGlobs.entryCount == 0) {
    return nullptr;
  }

  i = 0;
                    /* pVar1 ~= &globs::waterGlobs.entryTable[i]; */
  pIVar1 = globs::waterGlobs.entryTable[0].groups;
  do {
                    /* pGroup = &globs::waterGlobs.entryTable[i].groups[0]; */
    j = 0;
    pGroup = pIVar1;
                    /* if (globs::waterGlobs.entryTable[i].groupCount != 0) */
    if (pIVar1[10].index != 0) {
      do {
                    /* if ((bx == (uint)__ftol(entryTable[i].points[j].x +
                       DIRECTIONS_F[entryTable[i].groups[j]->direction].x) && 
                           (by == (uint)__ftol(entryTable[i].points[j].y +
                       DIRECTIONS_F[entryTable[i].groups[j]->direction].y)) */
        lVar2 = __ftol((float10)((WaterEntry_t *)&pIVar1[-0x22].float_c)->points[pGroup->index].x +
                       (float10)DIRECTIONS_F[pGroup->direction].x);
        if ((bx == (uint)lVar2) && (lVar2 = __ftol(extraout_ST0), by == (uint)lVar2)) {
          if (out_index != nullptr) {
                    /* This may also be a count up to the matching point */
            *out_index = j;
          }
                    /* return &globs::waterGlobs.entryTable[i]; */
          return (WaterEntry_t *)&pIVar1[-0x22].float_c;
        }
        j += 1;
        pGroup = pGroup + 1;
                    /* while (j < globs::waterGlobs.entryTable[i].groupCount); */
      } while (j < pIVar1[10].index);
    }
    i += 1;
                    /* pVar1 ~= &globs::waterGlobs.entryTable[++i]; */
    pIVar1 = (WaterEntryGroup_t *)&pIVar1[0x2c].float_maxDirZ_8;
    if (globs::waterGlobs.entryCount <= i) {
      return nullptr;
    }
  } while( true );
}


/// PRIVATE:
// <LegoRR.exe @0046ec90>
WaterEntry_t * __cdecl Water_InitSearchAddPairs(int y, uint xAlign, uint xMax)
{
  Water_Globs *pLVar1;
  Water_Globs *pLVar2;
  uint uVar3;
  Water_Globs *pLVar4;
  Water_Globs *pLVar5;
  uint uVar6;
  
  pLVar4 = nullptr;
  if ((y != 0) && (xAlign < xMax)) {
    do {
      uVar3 = 0;
      if (globs::waterGlobs.entryCount != 0) {
        pLVar1 = &globs::waterGlobs;
        do {
          uVar6 = 0;
          if (*(uint *)pLVar1->entryTable != 0) {
            pLVar2 = pLVar1;
            pLVar5 = pLVar4;
            do {
              pLVar4 = pLVar5;
              if (((((float)(ulonglong)xAlign == pLVar2->entryTable[0].points[0].x) &&
                   ((float)(ulonglong)(y - 1) == pLVar2->entryTable[0].points[0].y)) &&
                  (pLVar4 = pLVar1, pLVar5 != nullptr)) && (pLVar4 = pLVar5, pLVar5 != pLVar1)) {
                globs::waterGlobs.pairTable[globs::waterGlobs.pairCount].first =  (WaterEntry_t *)pLVar5;
                globs::waterGlobs.pairTable[globs::waterGlobs.pairCount].second = (WaterEntry_t *)pLVar1;
                globs::waterGlobs.pairCount++;
              }
              uVar6++;
              pLVar2 = (Water_Globs *)(pLVar2->entryTable[0].points + 1);
              pLVar5 = pLVar4;
            } while (uVar6 < *(uint *)pLVar1->entryTable);
          }
          uVar3++;
          pLVar1 = (Water_Globs *)(pLVar1->entryTable + 1);
        } while (uVar3 < globs::waterGlobs.entryCount);
      }
      xAlign++;
    } while (xAlign < xMax);
  }
  return (WaterEntry_t *)pLVar4;
}

/// PRIVATE:
// <LegoRR.exe @0046ed90>
void __cdecl Water_InitAddPoint(WaterEntry_t *last, uint y, uint xAlign, uint xMax)
{
  for (uint x = xAlign; x < xMax; x++) {
    last->points[last->pointCount].x = (float)(ulonglong)x;
    last->points[last->pointCount].y = (float)(ulonglong)y;
    last->pointCount++;
  }
  return;
}

/// PRIVATE:
// <LegoRR.exe @0046edf0>
void __cdecl Water_InitAddPointFirst(uint y, uint xAlign, uint xMax)
{
  WaterEntry_t *entry = &globs::waterGlobs.entryTable[globs::waterGlobs.entryCount];
  entry->pointCount = 0;
  Water_InitAddPoint(entry, y, xAlign, xMax);
  globs::waterGlobs.entryCount++;
  return;
}


