void __cdecl lego::game::Level_GenerateFallin_InRadius(Point2I *blockPos,int radius,BOOL param_3)
{
  uint diameter;
  short rng1;
  short rng2;
  uint uVar2;
  BOOL BVar3;
  int iVar4;
  unsigned int i;
  Point2I blockOffPos;
  BOOL fallins [100];
  
  std::memset(fallins, 0, sizeof(fallins));

  unsigned int diameter = radius * 2;
  unsigned int i = 0;
  while( true ) {
    unsigned int uVar2 = diameter * diameter
    if (!param_3)
      uVar2 /= 4;

    // if (!param_3)
    //   uVar2 = diameter * diameter >> 2;
    // else
    //   uVar2 = diameter * diameter;

    if (i >= uVar2) // fall-off, reduce intensity farther out(?)
      break;
  
    unsigned int rng1 = math::Maths_Rand();
    unsigned int rng2 = math::Maths_Rand();
    blockOffPos.x = (blockPos->x + (rng1 % diameter)) - radius;
    blockOffPos.y = (blockPos->y + (rng2 % diameter)) - radius;
    iVar4 = (rng2 % diameter) + (rng1 % diameter) * 10;
    if (fallins[iVar4] == 0) {

      if (Fallin_Block_FUN_0040f0c0(&blockOffPos, TRUE) && param_3) {
        return;
      }
      fallins[iVar4] = TRUE;
    }
    i += 1;
  }
  return;
}


BOOL __cdecl lego::game::Fallin_Block_FUN_0040f0c0(Point2I *blockPos,BOOL param_2)
{
  bool bVar1;
  BOOL BVar2;
  uint unkIntensity;
  int *pDirY;
  uint i;
  int count;
  Point2I blockOffPos;
  Point2I DIRECTIONS [4];
  
  i = 0;
  bVar1 = true;
  unkIntensity = 0;
  count = 0;
  GetSurfaceMap();
  DIRECTIONS[0].x = 0;
  DIRECTIONS[0].y = -1;
  DIRECTIONS[1].x = 1;
  DIRECTIONS[1].y = 0;
  DIRECTIONS[2].x = 0;
  DIRECTIONS[2].y = 1;
  DIRECTIONS[3].x = -1;
  DIRECTIONS[3].y = 0;
  BVar2 = Fallin_Block_UpdateFallinsUnk1(blockPos);
  if (BVar2 != 0) {
    pDirY = &DIRECTIONS[0].y;
    do {
      blockOffPos.x = pDirY[-1] + blockPos->x;
      blockOffPos.y = *pDirY + blockPos->y;
      BVar2 = Level_Block_IsFlags1_10Not8(blockOffPos.x,blockOffPos.y);
      if (BVar2 != 0) {
        BVar2 = Level_Block_IsImmovable(&blockOffPos);
        if (BVar2 == 0) {
          BVar2 = Level_Block_IsReinforced(blockOffPos.x,blockOffPos.y);
          if (BVar2 != 0) goto LAB_0040f164;
        }
        else {
LAB_0040f164:
          bVar1 = false;
        }
        unkIntensity |= 1 << ((byte)i & 0x1f);
        BVar2 = Level_Block_IsFlags1_c0(blockOffPos.x,blockOffPos.y);
        if (BVar2 == 0) {
          count += 1;
        }
      }
      i += 1;
      pDirY = pDirY + 2;
    } while (i < 4);
    if (((bVar1) && (unkIntensity != 0)) && (count != 0)) {
      Fallin_Block_FUN_0040f260(blockPos,unkIntensity,param_2);
      return TRUE;
    }
  }
  return 0;
}


def m(flags1):
  from struct import pack, unpack
  def s32(num): return unpack('<i', pack('<I', num & 0xffffffff))[0]
  def u32(num): return num & 0xffffffff
  flags1 = u32(flags1)
  rubble = flags1 & 0x3
  r1 = (rubble + u32(~0) ^ flags1) & 3 ^ flags1
  r2 = (rubble - 1 ^ flags1) & 3 ^ flags1
  r3 = (u32(rubble - 1) ^ flags1) & 3 ^ flags1
  return ', '.join(hex(r) for r in (r1, r2, r3))

BOOL __cdecl lego::game::Level_BlockProc_Dust_FUN_00432bc0(Point2I *blockPos)
{
  LevelBlockFlags1 LVar1;
  LevelData *level;
  int iVar2;
  LevelBlockFlags1 LVar3;
  BOOL result;
  float10 fVar4;
  Vector3F local_18;
  Vector3F local_c;
  LevelBlock *pBlock;
  
  level = globs::legoGlobs.level;
  result = 1;
  iVar2 = ((globs::legoGlobs.level)->dimensions).width * blockPos->y + blockPos->x;
  pBlock = (globs::legoGlobs.level)->blocks + iVar2;
  LVar1 = (globs::legoGlobs.level)->blocks[iVar2].flags1;                                                         
                    /* BLOCK1_RUBBLE_FULL is also a mask for rubble level */
  LVar3 = LVar1 & BLOCK1_RUBBLE_FULL;
  if ((LVar1 & BLOCK1_UNK_200000) == BLOCK1_NONE) {
    if (LVar3 != BLOCK1_NONE) {
                    /* Positive modulus % 4 (??) */
      pBlock->flags1 = (LVar3 + ~BLOCK1_NONE ^ LVar1) & BLOCK1_RUBBLE_FULL ^ LVar1;
    }
    else {
      pBlock->flags1 = LVar1 | BLOCK1_UNK_200000;
      front::Info_DoAll_FUN_00419820(blockPos);
      front::Interface_IfSelectedRubble_IsBlockPos(blockPos);
      ai::AITask_DoCallbacks_Block_FUN_00402a90(blockPos,FALSE);
      Map3D_BlockToWorldPos
                (level->surfaceMap,blockPos->x,blockPos->y,(float *)&local_18,&local_18.y);
      fVar4 = Map3D_GetWorldZ(level->surfaceMap,local_18.x,local_18.y);
      local_18.z = (float)fVar4;
      math::Maths_Vector3DRandom(&local_c);
      local_c.z = 0.0;
      effect::Effect_Spawn_Particle(MISCOBJECT_PATHDUST,&local_18,&local_c);
    }
    result = ZEXT14(LVar3 == BLOCK1_NONE);
    Level_UpdateBlockSurfaceUnk(level,blockPos->x,blockPos->y,0);
  }
  return result;
}



BOOL __cdecl lego::game::Map3D_WorldToBlockPos(SurfaceMap *surfMap,float in_x,float in_y,int *out_bx,int *out_by,float *out_unk_z)
{
  int bx = ((in_x - surfMap->worldDimensions_fnegx.width)  / surfMap->BlockSize);
  int by = ((surfMap->worldDimensions_fnegx.height - in_y) / surfMap->BlockSize);

  if (out_bx != nullptr)
    *out_bx = bx;
  if (out_by != nullptr)
    *out_by = by;

  if ((bx >= 0 && bx < surfMap->smallDimensions.width) &&
      (by >= 0 && by < surfMap->smallDimensions.height))
  {
    if (out_unk_z != nullptr) {
      float blockSize = surfMap->BlockSize;
      float halfSize  = surfMap->BlockSize / 2.0f;
      float fx =  ((in_x - ((bx * blockSize) + surfMap->worldDimensions_fnegx.width))  / halfSize);
      float fy = -((in_y - (surfMap->worldDimensions_fnegx.height - (by * blockSize))) / halfSize);
      
      if (fx > 1.0f)
        fx = 2.0 - fx;

      if (fy > 1.0f)
        fy = 2.0 - fy;

      *out_unk_z = ((fx < fy) ? fx : fy); // min(fx, fy);
    }
    return true;
  }

  // out of bounds
  return false;
}


void __cdecl lego::game::Map3D_FUN_0044f0b0(SurfaceMap *surfMap,uint bx,uint by,BOOL isNotStruct28_Flag1)
{
  D3DRMVertex vertices[4];
  D3DRMVertex vertexSwap;
  
  int idx = surfMap->dimensions.width * by + bx;
  D3DRMGroupIndex groupID = surfMap->smallDimensions.width * by + bx;

  if ((isNotStruct28_Flag1 && !(surfMap->grid28_28[idx].byteflags_19 & SURFMAP_STRUCT28_UNK_1)) ||
      (!isNotStruct28_Flag1 && (surfMap->grid28_28[idx].byteflags_19 & SURFMAP_STRUCT28_UNK_1)))
  {
    res::Container_Mesh_GetVertices(surfMap->resMesh_24, groupID, 0, 4, vertices);

    if (!(surfMap->grid28_28[idx].byteflags_19 & SURFMAP_STRUCT28_UNK_1)) {
      surfMap->grid28_28[idx].byteflags_19 |= SURFMAP_STRUCT28_UNK_1;
      
      // Shift vertices up one
      std::memcpy(&vertexSwap,  &vertices[3], sizeof(D3DRMVertex));
      std::memcpy(&vertices[3], &vertices[2], sizeof(D3DRMVertex));
      std::memcpy(&vertices[2], &vertices[1], sizeof(D3DRMVertex));
      std::memcpy(&vertices[1], &vertices[0], sizeof(D3DRMVertex));
      std::memcpy(&vertices[0], &vertexSwap,  sizeof(D3DRMVertex));
    }
    else {
      surfMap->grid28_28[idx].byteflags_19 &= ~SURFMAP_STRUCT28_UNK_1;
      
      // Shift vertices down one
      std::memcpy(&vertexSwap,  &vertices[0], sizeof(D3DRMVertex));
      std::memcpy(&vertices[0], &vertices[1], sizeof(D3DRMVertex));
      std::memcpy(&vertices[1], &vertices[2], sizeof(D3DRMVertex));
      std::memcpy(&vertices[2], &vertices[3], sizeof(D3DRMVertex));
      std::memcpy(&vertices[3], &vertexSwap,  sizeof(D3DRMVertex));
    }

    res::Container_Mesh_SetVertices(surfMap->resMesh_24, groupID, 0, 4, vertices);
    Map3D_Block_InitPlaneNormals(surfMap, bx, by);
                    /* Perform action in a square: { { 0, 0 }, { 1, 0 },
                                                     { 0, 1 }, { 1, 1 } } */
    Map3D_SetFlags2_AndStruct28_SetFlag19_4(surfMap, bx,     by);
    Map3D_SetFlags2_AndStruct28_SetFlag19_4(surfMap, bx + 1, by);
    Map3D_SetFlags2_AndStruct28_SetFlag19_4(surfMap, bx + 1, by + 1);
    Map3D_SetFlags2_AndStruct28_SetFlag19_4(surfMap, bx,     by + 1);
  }
  return;
}

// <LegoRR.exe @0046e140>
void __cdecl lego::game::LevelStruct428_Initialise_Sub_Pass2(Container *contRoot,LevelData *level)
{
  Vector3F vertPoses[4];
  D3DRMVertex vertices[4];

  Point2F DIRECTIONS_F[4];
  DIRECTIONS_F[0].x = 0.0;
  DIRECTIONS_F[0].y = 0.0;
  DIRECTIONS_F[1].x = 1.0;
  DIRECTIONS_F[1].y = 0.0;
  DIRECTIONS_F[2].x = 1.0;
  DIRECTIONS_F[2].y = 1.0;
  DIRECTIONS_F[3].x = 0.0;
  DIRECTIONS_F[3].y = 1.0;

  uint FACEDATA[6];
  FACEDATA[0] = 0;
  FACEDATA[1] = 1;
  FACEDATA[2] = 3;
  FACEDATA[3] = 1;
  FACEDATA[4] = 2;
  FACEDATA[5] = 3;

  float TU_COORDS[4];
  TU_COORDS[0] = 0.0;
  TU_COORDS[1] = 1.0;
  TU_COORDS[2] = 1.0;
  TU_COORDS[3] = 0.0;

  float TV_COORDS[4];
  TV_COORDS[0] = 0.0;
  TV_COORDS[1] = 0.0;
  TV_COORDS[2] = 1.0;
  TV_COORDS[3] = 1.0;

  //globs::levelstruct428Globs.structTable
  //globs::levelstruct428Globs.structCount

  Struct_428* structTable = globs::levelstruct428Globs.structTable; // Struct_428[10];
  uint structCount        = globs::levelstruct428Globs.structCount;

  for (int i = 0; i < structCount; i++) {

    structTable[i].float_z_418 = -10000.0f;

    for (int j = 0; j < structTable[i].pointsCount; j++) {
      uint bx = __ftol(structTable[i].points[j].x);
      uint by = __ftol(structTable[i].points[j].y);
      
      Map3D_GetBlockVertexPositions(level->surfaceMap, bx, by, vertPoses);

      for (int k = 0; k < 4; k++) { // 4 == _countof(vertPoses)
        bx = __ftol(structTable[i].points[j].x + DIRECTIONS_F[k].x);
        by = __ftol(structTable[i].points[j].y + DIRECTIONS_F[k].y);
        int idx = level->dimensions.width * by + bx;
        
        if (level->blocks[idx].predug == PREDUG_WALL) {
          if (vertPoses[k].z > structTable[i].float_z_418) {
            structTable[i].float_z_418 = vertPoses[k].z;
          }
        }
        else {
          structTable[i].flags |= 0x1;
        }
      }
    }

    // initial height or something?
    structTable[i].float_z2_41c = structTable[i].float_z_418;
  
    structTable[i].contMeshTrans = res::Container_MakeMesh2(contRoot, CONTAINER_MESHTYPE_TRANSPARENT /*0x3*/);
    
    // 0x1 == visible flag?
    res::Container_Hide(structTable[i].contMeshTrans, !(structTable[i].flags & 0x1)); 
    
    for (int j = 0; j < structTable[i].pointsCount; j++) {
      
      uint groupID = res::Container_Mesh_AddGroup(structTable[i].contMeshTrans, 4, 2, 3, FACEDATA);
      res::Container_Mesh_SetColourAlpha(structTable[i].contMeshTrans, groupID, 0.0f, 0.3f, 0.8f, 0.6f);

      uint bx = __ftol(structTable[i].points[j].x);
      uint by = __ftol(structTable[i].points[j].y);
      
      Map3D_GetBlockVertexPositions(level->surfaceMap, bx, by, vertPoses);

      for (int k = 0; k < 4; k++) { // 4 == _countof(vertPoses)
        vertices[k].position.x = vertPoses[k].x;
        vertices[k].position.y = vertPoses[k].y;
        vertices[k].position.z = structTable[i].float_z_418;
        vertices[k].normal.x = 0.0f;
        vertices[k].normal.y = 0.0f;
        vertices[k].normal.z = -1.0f;
        vertices[k].tu = TU_COORDS[k];
        vertices[k].tv = TV_COORDS[k];
        vertices[k].colour = 0;
      }

      res::Container_Mesh_SetVertices(structTable[i].contMeshTrans, j, 0, 4, vertices);
    }
  }
}
