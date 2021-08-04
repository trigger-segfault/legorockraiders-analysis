
/* WARNING: Function: _alloca4k replaced with injection: alloca_probe */

BOOL __cdecl lego::res::Res_LoadAEFileVehicle(VehicleData* vehicle, int index, ResourceData* resRoot, const char* aeFilename, const char* rootName)
{
  char cVar1;
  int iVar2;
  ResourceData *pRVar3;
  CFGProperty *prop;
  char *pcVar4;
  BOOL3 BVar5;
  int **ppiVar6;
  CFGProperty *root;
  int iVar7;
  uint uVar8;
  uint uVar9;
  int *piVar10;
  undefined4 *puVar11;
  VehicleData *pVVar12;
  ResourceData **ppRVar13;
  char *pcVar14;
  undefined4 *puVar15;
  float10 fVar16;
  // char *pcStack4560;
  // char *pcStack4556;
  float fStack4520;
  float fStack4516;
  float fStack4504;
  char *apcStack4500 [2];
  int aiStack4492 [99];
  char dirnameBuffer[1024];
  char aeFilenameBuffer[1024];
  char inputFilenameBuffer[1024];
  char lwoFilenameBuffer[1024];
  undefined4 uStack4;
  
  uStack4 = 0x46c9ba;


  char* aeNameParts[2];
  char* pathParts[100];

  // pVVar12 = vehicle;
  // for (iVar7 = 0x7b; iVar7 != 0; iVar7 += -1) {
  //   pVVar12->objIndex = 0;
  //   pVVar12 = (VehicleData *)&pVVar12->WheelNullName;
  // }
  // uVar8 = 0xffffffff;
  // do {
  //   pcVar4 = aeFilename;
  //   if (uVar8 == 0) break;
  //   uVar8 -= 1;
  //   pcVar4 = aeFilename + 1;
  //   cVar1 = *aeFilename;
  //   aeFilename = pcVar4;
  // } while (cVar1 != '\0');
  // uVar8 = ~uVar8;
  // puVar11 = (undefined4 *)(pcVar4 + -uVar8);
  // puVar15 = inputFilenameBuffer;
  // for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 -= 1) {
  //   *puVar15 = *puVar11;
  //   puVar11 = puVar11 + 1;
  //   puVar15 = puVar15 + 1;
  // }
  // for (uVar8 &= 3; uVar8 != 0; uVar8 -= 1) {
  //   *(undefined *)puVar15 = *(undefined *)puVar11;
  //   puVar11 = (undefined4 *)((int)puVar11 + 1);
  //   puVar15 = (undefined4 *)((int)puVar15 + 1);
  // }
  std::memset(vehicle, 0, 0x1ec /*sizeof(VehicleData)*/);
  std::strcpy(inputFilenameBuffer, aeFilename);
  int numParts = util::stringSplit(inputFilenameBuffer, aeNameParts, ",");

  vehicle->aeResData1 = Res_LoadResource(resRoot, aeNameParts[0], "ACT", true);
  if (vehicle->aeResData1 != NULL) {
    if (numParts == 2) {
      vehicle->aeResData2 = Res_LoadResource(pRVar3, aeNameParts[1], "ACT", true);
    }
    else {
      vehicle->aeResData2 = NULL;
    }

    // this simply gets the filename of the path, this is then used to lookup "dirname\\filename\\filename.ae"
    // dirname+filename (dirnameBuffer) and filename (pathParts[numParts - 1])
    std::strcpy(dirnameBuffer, aeNameParts[0]);
    numParts = util::stringSplit(dirnameBuffer, pathParts, "\\");
    for (int j = 1; j < numParts; j++) {
      pathParts[j][-1] = '\\'; // restore separators for dirname to their original character (except that connecting file final?)
    }
    std::sprintf(aeFilenameBuffer, "%s\\%s.%s", dirnameBuffer, pathParts[numParts - 1], "ae");
    // if (numParts > 1) {
    //   // piVar10 = aiStack4492;
    //   piVar10 = &pathParts[1];
    //   iVar7 = numParts - 1;
    //   do {
    //     iVar2 = *piVar10;
    //     piVar10 = piVar10 + 1;
    //     iVar7 += -1;
    //     *(undefined *)(iVar2 + -1) = '\\';
    //   } while (iVar7 != 0);
    // }
    // std::sprintf(aeFilenameBuffer, "%s\\%s.%s", dirnameBuffer, apcStack4500[numParts], "ae");
    prop = cfg::CFG_Open(aeFilenameBuffer);
    if (prop != NULL) {
      const char* keyPath = cfg::CFG_JoinPath(rootName, "CameraNullName", NULL);
      vehicle->CameraNullName = cfg::CFG_CopyPropertyValue(prop, keyPath);
      if (vehicle->CameraNullName == NULL) {
        vehicle->CameraNullFrames = 0;
      }
      else {
        keyPath = cfg::CFG_JoinPath(rootName, "CameraNullFrames", NULL);
        pcVar4 = cfg::CFG_GetPropertyValue(prop, keyPath);
        vehicle->CameraNullFrames = std::atoi(pcVar4 ? pcVar4 : ""/*EMPTYSTR*/);

        keyPath = cfg::CFG_JoinPath(rootName, "CameraFlipDir", NULL);
        vehicle->CameraFlipDir = cfg::CFG_GetPropertyBool(prop, keyPath);
      }

      keyPath = cfg::CFG_JoinPath(rootName, "CarryNullName", NULL);
      vehicle->CarryNullName = cfg::CFG_CopyPropertyValue(prop, keyPath);
      if (vehicle->CarryNullName == NULL) {
        vehicle->CarryNullFrames = 0;
      }
      else {
        keyPath = cfg::CFG_JoinPath(rootName, "CarryNullFrames", NULL);
        pcVar4 = cfg::CFG_GetPropertyValue(prop, keyPath);
        vehicle->CarryNullFrames = std::atoi(pcVar4 ? pcVar4 : ""/*EMPTYSTR*/);
      }

      keyPath = cfg::CFG_JoinPath(rootName, "DrillNullName", NULL);
      vehicle->DrillNullName = cfg::CFG_CopyPropertyValue(prop, keyPath);
      keyPath = cfg::CFG_JoinPath(rootName, "DepositNullName", NULL);
      vehicle->DepositNullName = cfg::CFG_CopyPropertyValue(prop, keyPath);
      keyPath = cfg::CFG_JoinPath(rootName, "DriverNullName", NULL);
      vehicle->DriverNullName = cfg::CFG_CopyPropertyValue(prop, keyPath);
      keyPath = cfg::CFG_JoinPath(rootName, "FireNullName", NULL);
      vehicle->FireNullName = cfg::CFG_CopyPropertyValue(prop, keyPath);

      keyPath = cfg::CFG_JoinPath(rootName, "yPivot", NULL);
      vehicle->yPivot = cfg::CFG_CopyPropertyValue(prop, keyPath);
      keyPath = cfg::CFG_JoinPath(rootName, "xPivot", NULL);
      vehicle->xPivot = cfg::CFG_CopyPropertyValue(prop, keyPath);

      keyPath = cfg::CFG_JoinPath(rootName, "PivotMaxZ", NULL);
      pcVar4 = cfg::CFG_GetPropertyValue(prop, keyPath);
      vehicle->PivotMaxZ = (float)(pcVar4 ? std::atof(pcVar4) : 1.0);

      keyPath = cfg::CFG_JoinPath(rootName, "PivotMinZ", NULL);
      pcVar4 = cfg::CFG_GetPropertyValue(prop, keyPath);
      vehicle->PivotMaxZ = (float)(pcVar4 ? std::atof(pcVar4) : -1.0);

      Res_LoadUpgradeLevels(&vehicle->upgrades,prop,rootName);
      keyPath = cfg::CFG_JoinPath(rootName, "WheelMesh", NULL);
      pcVar4 = cfg::CFG_CopyPropertyValue(prop, keyPath);
      if (pcVar4 != NULL) {
        std::sprintf(lwoFilenameBuffer, "%s\\%s", dirnameBuffer, pcVar4);
        std::free(pcVar4);

        keyPath = cfg::CFG_JoinPath(rootName, "WheelNullName", NULL);
        vehicle->WheelNullName = cfg::CFG_CopyPropertyValue(prop, keyPath);
        if (vehicle->WheelNullName != NULL) {
		      std::memset(&vehicle->lwoWheelMesh, 0, 0x4 * 6);

          vehicle->lwoWheelMesh = Res_LoadResource(vehicle->aeResData1, lwoFilenameBuffer, "LWO", false);
          vehicle->hasWheelNull = true;
		      std::memset(&vehicle->field_0x28, 0, 0x4 * 6);

          if (vehicle->lwoWheelMesh == NULL) {
            vehicle->WheelRadius = 0.0;
            *(undefined4 *)&vehicle->field_0x14 = 0;
            *(undefined4 *)&vehicle->field_0x18 = 0;
            *(undefined4 *)&vehicle->field_0x1c = 0;
            *(undefined4 *)&vehicle->field_0x20 = 0;
            *(undefined4 *)&vehicle->field_0x24 = 0;
          }
          else {
            keyPath = cfg::CFG_JoinPath(rootName, "WheelRadius", 0);
            vehicle->WheelRadius = (float)std::atof(pcVar4 ? pcVar4 : ""/*EMPTYSTR*/);

            if (vehicle->WheelRadius == 0.0f) {
              if (vehicle->lwoWheelMesh->resType == RESOURCE_MESH) {
                FUN_004751d0(vehicle->lwoWheelMesh, &fStack4520);
                vehicle->WheelRadius = (fStack4504 - fStack4516) * 0.5;
                FUN_00474d20(vehicle->lwoWheelMesh, 0, 3);
              }
              else {
                vehicle->WheelRadius = 3.0f;
              }
            }
          }

          vehicle->subdata_1e0 = Res_LoadPolyMesh(prop, rootName, aeNameParts[0], POLY_MEDIUM, 1);
          if (vehicle->aeResData2 != NULL) {
            // std::strcpy(dirnameBuffer, aeNameParts[1]);
            // // uVar8 = 0xffffffff;
            // // pcVar4 = &aeNameParts[1];
            // // do {
            // //   pcVar14 = pcVar4;
            // //   if (uVar8 == 0) break;
            // //   uVar8 -= 1;
            // //   pcVar14 = pcVar4 + 1;
            // //   cVar1 = *pcVar4;
            // //   pcVar4 = pcVar14;
            // // } while (cVar1 != '\0');
            // // uVar8 = ~uVar8;
            // // puVar11 = (undefined4 *)(pcVar14 + -uVar8);
            // // puVar15 = dirnameBuffer;
            // // for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 -= 1) {
            // //   *puVar15 = *puVar11;
            // //   puVar11 = puVar11 + 1;
            // //   puVar15 = puVar15 + 1;
            // // }
            // // for (uVar8 &= 3; uVar8 != 0; uVar8 -= 1) {
            // //   *(undefined *)puVar15 = *(undefined *)puVar11;
            // //   puVar11 = (undefined4 *)((int)puVar11 + 1);
            // //   puVar15 = (undefined4 *)((int)puVar15 + 1);
            // // }
            // numParts = util::stringSplit(dirnameBuffer, apcStack4500 + 1, "\\");
            // if (numParts > 1) {
            //   piVar10 = aiStack4492;
            //   iVar7 = numParts - 1;
            //   do {
            //     iVar2 = *piVar10;
            //     piVar10 = piVar10 + 1;
            //     iVar7 += -1;
            //     *(undefined *)(iVar2 + -1) = '\\';
            //   } while (iVar7 != 0);
            // }
            // std::sprintf(aeFilenameBuffer, "%s\\%s.%s", dirnameBuffer, apcStack4500[numParts], "ae");

            // this simply gets the filename of the path, this is then used to lookup "dirname\\filename\\filename.ae"
            // dirname+filename (dirnameBuffer) and filename (pathParts[numParts - 1])
            std::strcpy(dirnameBuffer, aeNameParts[1]);
            numParts = util::stringSplit(dirnameBuffer, pathParts, "\\");
            for (int j = 1; j < numParts; j++) {
              pathParts[j][-1] = '\\'; // restore separators for dirname to their original character (except that connecting file final?)
            }
            std::sprintf(aeFilenameBuffer, "%s\\%s.%s", dirnameBuffer, pathParts[numParts - 1], "ae");

            root = cfg::CFG_Open(aeFilenameBuffer);
            if (root != NULL) {
              vehicle->subdata_1e4 = Res_LoadPolyMesh(root, rootName, aeNameParts[1], POLY_MEDIUM, 1);
            }
          }

          vehicle->flags = 0x1;
          keyPath = cfg::CFG_JoinPath(rootName, "HoldMissing", 0);
          if (cfg::CFG_GetPropertyBool(prop, keyPath) == BOOL3_TRUE /*1*/) {
            vehicle->flags |= 0x8;
          }

          vehicle->field_60 = 0;
          vehicle->field_5c = 0;
          vehicle->float_64 = -1.0f;
          vehicle->objIndex = index;
          cfg::CFG_Close(prop);
          return true;
        }
      }
      cfg::CFG_Close(prop);
    }
  }
  return false;
}

