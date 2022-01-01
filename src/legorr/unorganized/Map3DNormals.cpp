
// <LegoRR.exe @004511f0>
void __cdecl lego::map::Map3D_Block_UpdateTextureAndVertices(Map3D *map,uint bx,uint by)
{
  Vector3F vertNormalsIn[4];
  Vector3F vertNormalsOut[4] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
  };
  Point2F blockOffsets[4] = {
    {  0.0f,  0.0f },
    { -1.0f,  0.0f },
    { -1.0f, -1.0f },
    {  0.0f, -1.0f },
  };

  for (uint32 i = 0; i < 4; i++) {
    blockOffsets[i].x += (real32)bx;
    blockOffsets[i].y += (real32)by;
  }
  
  for (uint32 i = 0; i < 4; i++) {
    Map3D_GetBlockDirectionNormal(map, (uint32)blockOffsets[i].x, (uint32)blockOffsets[i].y,
                                  i, &vertNormalsIn[i]);
  }
  

  for (uint32 i; i < 4; i++) { // out index
    uint32 bx1 = (uint32)blockOffsets[i].x;
    uint32 by1 = (uint32)blockOffsets[i].y;

    for (uint32 j; j < 4; j++) { // in index
      uint32 bx2 = (uint32)blockOffsets[j].x;
      uint32 by2 = (uint32)blockOffsets[j].y;

      if (!Map3D_BlockPairHasTextureMatch(map, bx1, by1, bx2, by2)) {
        Maths_Vector3DAdd(&vertNormalsOut[i], &vertNormalsOut[i], &vertNormalsIn[j]);
      }
    }
    Maths_Vector3DNormalize(&vertNormalsOut[i]);
  }

  for (uint32 i = 0; i < 4; i++) {
    Map3D_SetBlockDirectionNormal(map, (uint32)blockOffsets[i].x, (uint32)blockOffsets[i].y,
                                  i, &vertNormalsOut[i]);
  }
  return;
}

// <LegoRR.exe @0044ed90>
void __cdecl lego::map::Map3D_FlattenShapeVertices(Map3D *map,Point2I *shapePoints,uint shapeCount,float mult_4_0)
{
  Vector3F shapeVertPoses[10][4];

  real32 range = mult_4_0 * 0.5; // fVar4
  real32 minZ = 10000.0f;
  real32 maxZ = -10000.0f; // local_22c
  real32 totalZ = 0.0;
  Point2I DIRECTIONS[4] = {
    { 0, 0 },
    { 1, 0 },
    { 1, 1 },
    { 0, 1 },
  };
  Point2I local_200[4] = {
    { 0, 0 },
    { 1, 0 },
    { 1, 1 },
    { 0, 1 },
  };

  uint32 addCount = 0;
  for (uint32 i = 0; i < shapeCount; i++) {
    if ((i == shapeCount - 1) || (shapePoints[i].x != shapePoints[i+1].x) ||
                                  (shapePoints[i].y != shapePoints[i+1].y))
    {
      globs::s_SurfaceMap_Points10[addCount] = shapePoints[i];
      Map3D_GetBlockVertexPositions2(map, shapePoints[i].x, shapePoints[i].y, shapeVertPoses[addCount]);
      for (uint32 j = 0; j < 4; j++) {
        uint32 idx = (DIRECTIONS[j].x+shapePoints[i].x) + (DIRECTIONS[j].y+shapePoints[i].y) * map->gridWidth;
        if (!(map->blocks3D[idx].flags3D & MAP3DBLOCK_FLAG_VERTEXLEVELED)) {
          totalZ += shapeVertPoses[addCount][j].z;
          numVertTotal++;
        }
        else {
          real32 vertZ = shapeVertPoses[addCount][j].z;
          if (vertZ < minZ) minZ = vertZ;
          if (vertZ > maxZ) maxZ = vertZ;
          bCheckMinMax += 1;
        }
      }
      addCount++;
    }
    else {
      i++; // unknown increment i, to skip this block and start on next??? shape points are really bizarre
    }
  }
  
  // can we be sure this will be non-zero???
  real32 avgZ = totalZ / (real32)numVertTotal;

  if (bCheckMinMax) {
    if (avgZ + range > maxZ) avgZ = maxZ - range;
    if (avgZ - range < minZ) avgZ = minZ + range;
  }

  for (uint32 i = 0; i < addCount; i++) {
    for (uint32 j = 0; j < 4; j++) {
      uint32 bx = DIRECTIONS[j].x + globs::s_SurfaceMap_Points10[i].x;
      uint32 by = DIRECTIONS[j].y + globs::s_SurfaceMap_Points10[i].y;
      uint32 idx = bx + by * map->gridWidth;
      if (!(map->blocks3D[idx].flags3D & MAP3DBLOCK_FLAG_VERTEXLEVELED)) {
        real32 fVar5 = shapeVertPoses[i][j].z - avgZ;
        if (range < std::abs(fVar5)) {
          //                range + avgZ - shapeVertPoses[i][j].z
          real32 chDepth = ((fVar5 / fVar5) * range + avgZ) - shapeVertPoses[i][j].z;
          Map3D_Unk_ChangeWallDepth(map,bx,by, chDepth);
        }
        map->blocks3D[idx].flags3D |= MAP3DBLOCK_FLAG_VERTEXLEVELED;
      }
    }
  }
  return;
}

