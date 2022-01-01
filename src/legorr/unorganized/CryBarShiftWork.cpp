
void __cdecl
lego::front::CryOreSidebar_DrawCrystals(uint crystals,uint usedCrystals,float elapsedGame_unused)

{
  CryOre_CrystalsStruct_18 *cryTable;
  uint uVar1;
  int iVar2;
  uint *puVar3;
  CryOre_CrystalsStruct_18 *pCryTable;
  uint uVar4;
  uint *puVar5;
  CryTuple_8 (*paCVar6) [6];
  int *piVar7;
  uint uVar8;
  uint uVar9;
  ImageBMP *image;
  Point2F destPos;
  uint baseCounts [2];
  CryTuple_8 tableCounts [2] [6];
  
                    /* [26] is the hardcoded max displayable crystals in the sidebar */
  tableCounts[0][0].cryCount = 0;
  baseCounts[0] = 0;
  piVar7 = &tableCounts[0].unkCount;
  for (iVar2 = 0x17; iVar2 != 0; iVar2 += -1) {
    *piVar7 = 0;
    piVar7 = piVar7 + 1;
  }
  baseCounts[1] = 0;
                    /* shift both all/used crystals tables down by one
                        [0] <- [1] ... [5] <- count */
  pCryTable = globs::s_CryShift_Table;
  do {
    iVar2 = 2;
    cryTable = pCryTable;
    do {
      cryTable->table[0] = cryTable->table[1];
      cryTable = cryTable + 1;
      iVar2 += -1;
    } while (iVar2 != 0);
    pCryTable = (CryOre_CrystalsStruct_18 *)(pCryTable->table + 1);
  } while (pCryTable < (CryOre_CrystalsStruct_18 *)&globs::s_CryShift_Table[0].count);
  globs::s_CryShift_Table[0].count = crystals;
  destPos.x = (float)tableCounts;
  globs::s_CryShift_Table[1].count = usedCrystals;
  uVar4 = 0;
  puVar3 = baseCounts;

    /* shift both all/used crystals tables down by one
        [0] <- [1] ... [5] <- count */
  for (int j = 0; j < 5; j++) {
    for (int i = 0; i < 2; i++) {
      globs::s_CryShift_Table[i][j] = globs::s_CryShift_Table[i][j + 1];
    }
  }
  globs::s_CryShift_Table[0].count = crystals;
  globs::s_CryShift_Table[1].count = usedCrystals;

  baseCounts[0] = 0;
  baseCounts[1] = 0;
  std::memset(tableCounts, 0, sizeof(tableCounts));
  tableCounts[0][0].cryCount = 0;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 6; j++) {
      int k;
      for (k = 0; k < baseCounts[i]; k++) {
        if (tableCounts[i][k].cryCount == globs::s_CryShift_Table[i].table[j]) {
          tableCounts[i][k].unkCount += 1;
        }
      }

      if (k == baseCounts[i]) {
        tableCounts[i][k].cryCount = globs::s_CryShift_Table[i].table[j];
        tableCounts[i][k].unkCount = 1;
        baseCounts[i] += 1;
      }
    }
  }
  
  for (int i = 0; i < 2; i++) {
    int maxFound = 0;
    for (int k = 0; k < baseCounts[i]; k++) {
      if (tableCounts[i][k].cryCount == globs::s_CryShift_Table[i].table[k]) {
        //tableCounts[i][k].unkCount += 1;

        if (maxFound < tableCounts[i][k].unkCount) {
          maxFound = tableCounts[i][k].unkCount;
          if (i == 0) {
            crystals = tableCounts[0][k].unkCount;
          }
          else {
            // crystals = tableCounts[0][k].unkCount;
            usedCrystals = tableCounts[i][k].cryCount;
          }
        }
      }
    }
  }

  Panel_PrintF(PANEL_CRYSTALSIDEBAR,globs::legoGlobs.bmpToolTipFont,0x29,0x1d5,1,"%i",crystals);
	if (globals::g_RightPanel_NoSmallCrystal_bmp != NULL) {
				/* More hardcoded screen resolution positions */
    destPos.x = 624.0;
    destPos.y = 429.0;
    for (uVar4 = globals::g_RewardsQuotaCrystals; uVar4 != 0; uVar4 -= 1) {
      lego::image::Image_DisplayScaled
          (globals::g_RightPanel_NoSmallCrystal_bmp,NULL,&destPos,NULL);
      destPos.y = destPos.y - 17.0;
    }
    }
    if (globals::g_RightPanel_SmallCrystal_bmp != NULL) {
    uVar4 = 0;
    if (globals::g_RewardsQuotaCrystals < crystals) {
      crystals = globals::g_RewardsQuotaCrystals;
    }
    if (globals::g_RewardsQuotaCrystals < usedCrystals) {
      usedCrystals = globals::g_RewardsQuotaCrystals;
    }
          /* More hardcoded screen resolution positions */
    destPos.x = 624.0;
    destPos.y = 429.0;
    image = globals::g_RightPanel_SmallCrystal_bmp;
    uVar8 = usedCrystals;
    if (globals::g_RightPanel_UsedCrystal_bmp != NULL) {
      for (; image = globals::g_RightPanel_UsedCrystal_bmp,
        globals::g_RightPanel_UsedCrystal_bmp = image, uVar8 != 0; uVar8 = uVar8 - 1) {
        lego::image::Image_DisplayScaled(globals::g_RightPanel_SmallCrystal_bmp,NULL,&destPos,NULL);
        destPos.y = destPos.y - 17.0;
        uVar4 = usedCrystals;
      }
    }
    if (uVar4 < crystals) {
      iVar2 = crystals - uVar4;
      do {
      lego::image::Image_DisplayScaled(image,NULL,&destPos,NULL);
      destPos.y = destPos.y - 17.0;
      iVar2 += -1;
		} while (iVar2 != 0);
	}

    destPos.x = (float)((int)destPos.x + 0x30);
    puVar3 = puVar3 + 1;
                    /* end of last loop
                       if (i >= 12) (aka, i >= 2, where i is a multiple of 6) */
    if (0xb < uVar4) {
      uVar4 = 0;
      do {
        uVar8 = baseCounts[uVar4];
        uVar9 = 0;
        if (uVar8 != 0) {
          paCVar6 = tableCounts;
          puVar3 = (uint *)&tableCounts[uVar4][0].unkCount;
          do {
            uVar1 = *puVar3;
            if (uVar9 < uVar1) {
              uVar9 = uVar1;
              if (uVar4 == 0) {
                crystals = (*paCVar6)[0].cryCount;
              }
              else {
                usedCrystals = puVar3[-1];
              }
            }
            paCVar6 = (CryTuple_8 (*) [6])(*paCVar6 + 1);
            puVar3 = puVar3 + 2;
            uVar8 -= 1;
          } while (uVar8 != 0);
        }
        uVar4 += 1;
      } while (uVar4 < 2);

  do {
    uVar8 = 0;
    do {
      uVar9 = *puVar3;
      uVar1 = 0;
      if (uVar9 != 0) {
        puVar5 = (uint *)destPos.x;
        do {
          if (*puVar5 == globs::s_CryShift_Table[0].table[uVar8 + uVar4]) {
            tableCounts[uVar1 + uVar4].unkCount += 1;
            break;
          }
          uVar1 += 1;
          puVar5 = puVar5 + 2;
        } while (uVar1 < uVar9);
      }
      if (uVar1 == uVar9) {
        tableCounts[uVar1 + uVar4].cryCount = globs::s_CryShift_Table[0].table[uVar8 + uVar4];
        tableCounts[uVar1 + uVar4].unkCount = 1;
        *puVar3 += 1;
      }
      uVar8 += 1;
    } while (uVar8 < 6);
    uVar4 += 6;
    destPos.x = (float)((int)destPos.x + 0x30);
    puVar3 = puVar3 + 1;
                    /* end of last loop
                       if (i >= 12) (aka, i >= 2, where i is a multiple of 6) */
    if (0xb < uVar4) {
      uVar4 = 0;
      do {
        uVar8 = baseCounts[uVar4];
        uVar9 = 0;
        if (uVar8 != 0) {
          paCVar6 = tableCounts;
          puVar3 = (uint *)&tableCounts[uVar4][0].unkCount;
          do {
            uVar1 = *puVar3;
            if (uVar9 < uVar1) {
              uVar9 = uVar1;
              if (uVar4 == 0) {
                crystals = (*paCVar6)[0].cryCount;
              }
              else {
                usedCrystals = puVar3[-1];
              }
            }
            paCVar6 = (CryTuple_8 (*) [6])(*paCVar6 + 1);
            puVar3 = puVar3 + 2;
            uVar8 -= 1;
          } while (uVar8 != 0);
        }
        uVar4 += 1;
      } while (uVar4 < 2);
      Panel_PrintF(PANEL_CRYSTALSIDEBAR,globs::legoGlobs.bmpToolTipFont,0x29,0x1d5,1,"%i",crystals);
      if (globals::g_RightPanel_NoSmallCrystal_bmp != NULL) {
                    /* More hardcoded screen resolution positions */
        destPos.x = 624.0;
        destPos.y = 429.0;
        for (uVar4 = globals::g_RewardsQuotaCrystals; uVar4 != 0; uVar4 -= 1) {
          lego::image::Image_DisplayScaled
                    (globals::g_RightPanel_NoSmallCrystal_bmp,NULL,&destPos,NULL);
          destPos.y = destPos.y - 17.0;
        }
      }
      if (globals::g_RightPanel_SmallCrystal_bmp != NULL) {
        uVar4 = 0;
        if (globals::g_RewardsQuotaCrystals < crystals) {
          crystals = globals::g_RewardsQuotaCrystals;
        }
        if (globals::g_RewardsQuotaCrystals < usedCrystals) {
          usedCrystals = globals::g_RewardsQuotaCrystals;
        }
                    /* More hardcoded screen resolution positions */
        destPos.x = 624.0;
        destPos.y = 429.0;
        image = globals::g_RightPanel_SmallCrystal_bmp;
        uVar8 = usedCrystals;
        if (globals::g_RightPanel_UsedCrystal_bmp != NULL) {
          for (; image = globals::g_RightPanel_UsedCrystal_bmp,
              globals::g_RightPanel_UsedCrystal_bmp = image, uVar8 != 0; uVar8 = uVar8 - 1) {
            lego::image::Image_DisplayScaled
                      (globals::g_RightPanel_SmallCrystal_bmp,NULL,&destPos,NULL);
            destPos.y = destPos.y - 17.0;
            uVar4 = usedCrystals;
          }
        }
        if (uVar4 < crystals) {
          iVar2 = crystals - uVar4;
          do {
            lego::image::Image_DisplayScaled(image,NULL,&destPos,NULL);
            destPos.y = destPos.y - 17.0;
            iVar2 += -1;
          } while (iVar2 != 0);
        }
      }
      return;
    }
  } while( true );
}

