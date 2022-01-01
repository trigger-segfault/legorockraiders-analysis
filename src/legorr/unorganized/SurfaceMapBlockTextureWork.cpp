
/* WARNING: Switch with 1 destination removed at 0x0042fd79 : 5 cases all go to same destination */
/* WARNING: Switch with 1 destination removed at 0x0042fdd8 : 5 cases all go to same destination */

void __cdecl lego::game::Level_UpdateBlockSurfaceUnk(LevelData *level,int bx,int by)

{
  LevelBlock *pLVar1;
  LevelBlock *pLVar2;
  SurfaceMap *surfMap;
  int iVar3;
  LevelBlockFlags1 LVar4;
  LevelBlockFlags2 LVar5;
  LevelBlockFlags1 LVar6;
  BOOL BVar7;
  SurfaceMapStruct_2a8 *pSVar8;
  FeatureFlags FVar9;
  uint *puVar10;
  uint extraout_ECX;
  uint uVar11;
  uint extraout_EDX;
  uint uVar12;
  float local_60;
  int local_5c;
  float local_58;
  float local_54;
  Point2I *local_50;
  SurfaceMap *local_4c;
  Vector3F local_48;
  int local_3c;
  Point2I local_38;
  uint local_30 [5];
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar3 = (level->dimensions).width;
  if (iVar3 - 1U <= (uint)bx) {
    return;
  }
  if ((level->dimensions).height - 1U <= (uint)by) {
    return;
  }
  local_4c = level->surfaceMap;
  iVar3 = by * iVar3 + bx;
  local_5c = 0;
  local_30[0] = 0;
  LVar4 = level->blocks[iVar3].flags1 & BLOCK1_POWERPATH;
  local_30[1] = 0;
  pLVar1 = level->blocks + iVar3;
  local_30[2] = 1;
  local_30[3] = 0;
  local_30[4] = 1;
  local_1c = 1;
  local_18 = 0;
  local_14 = 1;
  local_3c = 1;
  if ((LVar4 == BLOCK1_NONE) || ((pLVar1->flags2 & BLOCK2_UNK_400) != BLOCK2_NONE)) {
    if ((LVar4 == BLOCK1_NONE) && ((pLVar1->flags2 & BLOCK2_UNK_400) != BLOCK2_NONE)) {
      unk::Lego_PathLiveLevelsIncrementConditional(0);
      LVar5 = pLVar1->flags2 & ~BLOCK2_UNK_400;
      goto LAB_0042f6d5;
    }
  }
  else {
    unk::Lego_PathLiveLevelsIncrementConditional(1);
    LVar5 = pLVar1->flags2 | BLOCK2_UNK_400;
LAB_0042f6d5:
    pLVar1->flags2 = LVar5;
  }
  iVar3 = (level->dimensions).width;
  pLVar2 = level->blocks;
  local_50 = &local_38;
  uVar11 = 0;
                    /* Get surrounding blocks for orientation? */
  puVar10 = local_30;
  do {
    if (pLVar2[(puVar10[1] + by) * iVar3 + bx + *puVar10].predug == PREDUG_EXPOSED) {
      local_48.x = (float)((uint)local_48.x & 0xffffff00 | uVar11 & 0xff);
      local_5c += 1;
    }
    else {
      *(char *)&local_50->x = (char)uVar11;
      local_50 = (Point2I *)((int)&local_50->x + 1);
    }
    uVar11 += 1;
    puVar10 = puVar10 + 2;
  } while (uVar11 < 4);
  LVar4 = pLVar1->flags1;
  LVar6 = LVar4 & ~(BLOCK1_UNK_8|BLOCK1_UNK_10|BLOCK1_UNK_40|BLOCK1_UNK_80|BLOCK1_UNK_2000);
  pLVar1->flags1 = LVar6;
  if (local_5c == 4) {
    local_38.x = bx;
    local_38.y = by;
    pLVar1->flags1 =
         LVar4 & ~(BLOCK1_UNK_8|BLOCK1_UNK_10|BLOCK1_REINFORCED|BLOCK1_UNK_40|BLOCK1_UNK_80|
                  BLOCK1_UNK_2000) | (BLOCK1_UNK_4|BLOCK1_UNK_8);
    pLVar1->field_3 = 0;
    if ((LVar4 & BLOCK1_UNK_8) == BLOCK1_NONE) {
      local_48.x = (float)bx;
      local_48.y = (float)by;
      FUN_00402a10(&local_38,0);
      Level_FUN_00431380(level,(Point2I *)&local_48,1);
      if ((globals::g_Game.flags1 & GAME1_ALWAYSROCKFALL) != GAME1_NONE) {
        Level_AddMessageAction
                  (MESSAGE_DIG_COMPLETE,0,
                   (uint)(globals::g_Game.level)->blocks
                         [((globals::g_Game.level)->dimensions).width * by + bx].field_3,
                   (Point2I *)&local_48);
      }
    }
    if ((pLVar1->flags1 & BLOCK1_UNK_400000) == BLOCK1_NONE) {
      if ((((((globals::g_Game.level)->blocks
              [((globals::g_Game.level)->dimensions).width * local_38.y + local_38.x].flags1 &
             BLOCK1_UNK_400) == BLOCK1_NONE) &&
           ((*(byte *)&(globals::g_Game.level)->blocks
                       [((globals::g_Game.level)->dimensions).width * local_38.y + local_38.x].
                       flags2 & 4) == 0)) &&
          ((*(byte *)((int)&(globals::g_Game.level)->blocks
                            [((globals::g_Game.level)->dimensions).width * local_38.y + local_38.x].
                            flags1 + 1) & 0x80) == 0)) &&
         (BVar7 = FUN_00408fd0(&local_38), BVar7 == 0)) {
        iVar3 = ((globals::g_Game.level)->dimensions).width * local_38.y + local_38.x;
        (globals::g_Game.level)->blocks[iVar3].flags1 =
             (globals::g_Game.level)->blocks[iVar3].flags1 & ~BLOCK1_UNK_200000;
        iVar3 = ((globals::g_Game.level)->dimensions).width * local_38.y + local_38.x;
        (globals::g_Game.level)->blocks[iVar3].flags1 =
             (globals::g_Game.level)->blocks[iVar3].flags1 & ~BLOCK1_POWERPATH;
        iVar3 = ((globals::g_Game.level)->dimensions).width * local_38.y + local_38.x;
        (globals::g_Game.level)->blocks[iVar3].flags1 =
             (globals::g_Game.level)->blocks[iVar3].flags1 & ~BLOCK1_UNK_40000000;
        Level_UnkLiveObjInitFlagsToggle_AndClearNumDrained();
        FUN_00402970(&local_38);
        util::logf_removed((char *)&local_38);
        iVar3 = 4;
        do {
          ai::AITask_DoClear_AtPosition(&local_38,MESSAGE_CLEAR_COMPLETE);
          iVar3 += -1;
        } while (iVar3 != 0);
        iVar3 = ((globals::g_Game.level)->dimensions).width * local_38.y + local_38.x;
        (globals::g_Game.level)->blocks[iVar3].flags1 =
             (globals::g_Game.level)->blocks[iVar3].flags1 | BLOCK1_RUBBLE_FULL;
      }
      iVar3 = ((globals::g_Game.level)->dimensions).width * local_38.y + local_38.x;
      (globals::g_Game.level)->blocks[iVar3].flags1 =
           (globals::g_Game.level)->blocks[iVar3].flags1 | BLOCK1_UNK_400000;
      FUN_0041ceb0(&local_38);
    }
    BVar7 = Level_FUN_0040e110(level,bx,by);
    Level_FUN_0040e280(level,bx,by,(uint)(BVar7 != 0));
    if ((pLVar1->terrain == TERRAIN_LAVA) ||
       (LVar4 = pLVar1->flags1, (LVar4 & BLOCK1_UNK_80000000) != BLOCK1_NONE)) {
      FUN_0040ed80(&local_38,1);
      if ((pLVar1->flags1 & BLOCK1_UNK_200) == BLOCK1_NONE) {
        if (pLVar1->field_7 == 4) {
          pLVar1->texture = TEXTURE_LAVA;
          SurfaceMap_FUN_00450c20(level->surfaceMap,bx,by,TRUE);
          if ((pLVar1->flags1 & BLOCK1_UNK_4000) == BLOCK1_NONE) {
            if ((int)pLVar1->randomness % 3 == 0) {
              local_48.x = 0.1;
              local_48.y = 0.1;
              local_48.z = -1.0;
              pSVar8 = Game_UnkSmokeFrames_FUN_004656f0
                                 (0,bx,by,&local_48,0.6,0.4,0.0,1.0,0.3,0,(int)pLVar1->randomness,
                                  0x26);
              pLVar1->field_1c = pSVar8;
              pLVar1->flags1 = pLVar1->flags1 | BLOCK1_UNK_4000;
            }
          }
          else {
            FUN_00465d80(pLVar1->field_1c,FALSE);
          }
        }
        else {
          SurfaceMap_FUN_00450c20(level->surfaceMap,bx,by,FALSE);
          switch(pLVar1->field_7) {
          case 0:
            pLVar1->texture = TEXTURE_ERODE_LOW;
            break;
          case 1:
            pLVar1->texture = TEXTURE_ERODE_MEDIUM;
            break;
          case 2:
            pLVar1->texture = TEXTURE_ERODE_HIGH;
            break;
          case 3:
            pLVar1->texture = TEXTURE_ERODE_FULL;
          }
        }
      }
      else {
        SurfaceMap_FUN_00450c20(level->surfaceMap,bx,by,FALSE);
        pLVar1->texture = TEXTURE_LAVA_NOTHOT;
        if ((pLVar1->flags1 & BLOCK1_UNK_4000) != BLOCK1_NONE) {
          FUN_00465d80(pLVar1->field_1c,TRUE);
        }
      }
    }
    else {
      if (pLVar1->terrain == TERRAIN_LAKE) {
        pLVar1->texture = TEXTURE_WATER;
        SurfaceMap_FUN_00450c20(level->surfaceMap,bx,by,TRUE);
      }
      else {
        if ((LVar4 & BLOCK1_UNK_100000) == BLOCK1_NONE) {
          if ((LVar4 & BLOCK1_POWERPATH) == BLOCK1_NONE) {
            if ((*(byte *)&pLVar1->flags2 & BLOCK2_SLUGHOLE_EXPOSED) == 0) {
              if ((LVar4 & BLOCK1_UNK_200000) == BLOCK1_NONE) {
                switch(LVar4 & BLOCK1_RUBBLE_FULL) {
                case BLOCK1_NONE:
                  pLVar1->texture = TEXTURE_RUBBLE_LOW;
                  break;
                case BLOCK1_RUBBLE_LOW:
                  pLVar1->texture = TEXTURE_RUBBLE_MEDIUM;
                  break;
                case BLOCK1_RUBBLE_MEDIUM:
                  pLVar1->texture = TEXTURE_RUBBLE_HIGH;
                  break;
                case BLOCK1_RUBBLE_FULL:
                  pLVar1->texture = TEXTURE_RUBBLE_FULL;
                }
              }
              else {
                if ((LVar4 & BLOCK1_UNK_40000000) == BLOCK1_NONE) {
                  pLVar1->texture = TEXTURE_GROUND;
                }
                else {
                  pLVar1->texture = TEXTURE_PATH_BUILD;
                }
              }
            }
            else {
              pLVar1->texture = TEXTURE_SLUGHOLE;
            }
          }
          else {
            uVar11 = FUN_0042f280(bx,by,&pLVar1->field_3,pLVar1->flags2 & BLOCK2_UNK_100);
            pLVar1->texture = (SurfaceTexture)uVar11;
          }
        }
        else {
          if ((pLVar1->flags2 & BLOCK2_UNK_100) == BLOCK2_NONE) {
            pLVar1->texture = TEXTURE_PLATE;
          }
          else {
            pLVar1->texture = TEXTURE_PLATE_POWERED;
          }
        }
      }
    }
    goto switchD_0042fb8d_caseD_4;
  }
  if (local_5c != 2) {
    if ((local_5c != 1) && (local_5c != 3)) {
      if (((LVar4 & BLOCK1_UNK_4) == BLOCK1_NONE) || (pLVar1->terrain - 1 < 5)) {
        pLVar1->texture = TEXTURE_TUNNEL;
      }
      pLVar1->field_3 = 0;
      goto switchD_0042fb8d_caseD_4;
    }
    pLVar1->flags1 =
         LVar4 & ~(BLOCK1_UNK_8|BLOCK1_UNK_10|BLOCK1_REINFORCED|BLOCK1_UNK_40|BLOCK1_UNK_80|
                  BLOCK1_UNK_2000) | (BLOCK1_UNK_4|BLOCK1_UNK_10);
    if (local_5c == 1) {
      if (true) {
        if (true) {
          switch(pLVar1->terrain) {
          case TERRAIN_IMMOVABLE:
          case TERRAIN_WATER_unused:
            goto switchD_0042fe25_caseD_1;
          case TERRAIN_HARD:
            goto switchD_0042fe25_caseD_2;
          case TERRAIN_MEDIUM:
            goto switchD_0042fe25_caseD_3;
          case TERRAIN_LOOSE:
            goto switchD_0042fe25_caseD_4;
          case TERRAIN_SOIL:
            goto switchD_0042fe25_caseD_5;
          }
        }
      }
      else {
        if (true) {
          switch(pLVar1->terrain) {
          case TERRAIN_IMMOVABLE:
          case TERRAIN_WATER_unused:
switchD_0042fe25_caseD_1:
            pLVar1->texture = TEXTURE_WALL_C_IMMOVABLE;
            break;
          case TERRAIN_HARD:
switchD_0042fe25_caseD_2:
            pLVar1->texture = TEXTURE_WALL_C_HARD;
            break;
          case TERRAIN_MEDIUM:
switchD_0042fe25_caseD_3:
            pLVar1->texture = TEXTURE_WALL_C_MEDIUM;
            break;
          case TERRAIN_LOOSE:
switchD_0042fe25_caseD_4:
            pLVar1->texture = TEXTURE_WALL_C_LOOSE;
            break;
          case TERRAIN_SOIL:
switchD_0042fe25_caseD_5:
            pLVar1->texture = TEXTURE_WALL_C_SOIL;
          }
        }
      }
      pLVar1->flags1 =
           LVar4 & ~(BLOCK1_UNK_8|BLOCK1_UNK_10|BLOCK1_REINFORCED|BLOCK1_UNK_40|BLOCK1_UNK_80|
                    BLOCK1_UNK_2000) | (BLOCK1_UNK_4|BLOCK1_UNK_10|BLOCK1_UNK_40);
      local_38.y = by;
      pLVar1->field_3 = SUB41(local_48.x,0) + 2U & 3;
      local_38.x = bx;
      Level_FUN_00431380(level,&local_38,TRUE);
    }
    else {
      if (local_5c == 3) {
        if (true) {
          if (true) {
            switch(pLVar1->terrain) {
            case TERRAIN_IMMOVABLE:
            case TERRAIN_WATER_unused:
              goto switchD_0042febf_caseD_1;
            case TERRAIN_HARD:
              goto switchD_0042febf_caseD_2;
            case TERRAIN_MEDIUM:
              goto switchD_0042febf_caseD_3;
            case TERRAIN_LOOSE:
              goto switchD_0042febf_caseD_4;
            case TERRAIN_SOIL:
              goto switchD_0042febf_caseD_5;
            }
          }
        }
        else {
                    /* Duplicate code. Unreachable, but contains effects of above switch */
          if (true) {
            switch(pLVar1->terrain) {
            case TERRAIN_IMMOVABLE:
            case TERRAIN_WATER_unused:
switchD_0042febf_caseD_1:
              pLVar1->texture = TEXTURE_WALL_O_IMMOVABLE;
              break;
            case TERRAIN_HARD:
switchD_0042febf_caseD_2:
              pLVar1->texture = TEXTURE_WALL_O_HARD;
              break;
            case TERRAIN_MEDIUM:
switchD_0042febf_caseD_3:
              pLVar1->texture = TEXTURE_WALL_O_MEDIUM;
              break;
            case TERRAIN_LOOSE:
switchD_0042febf_caseD_4:
              pLVar1->texture = TEXTURE_WALL_O_LOOSE;
              break;
            case TERRAIN_SOIL:
switchD_0042febf_caseD_5:
              pLVar1->texture = TEXTURE_WALL_O_SOIL;
            }
          }
        }
        local_48.x = (float)bx;
        local_48.y = (float)by;
        Level_FUN_00431380(level,(Point2I *)&local_48,TRUE);
        FUN_00402a60(&local_48);
        pLVar1->field_3 = (byte)local_38.x;
        pLVar1->flags1 = pLVar1->flags1 | BLOCK1_UNK_80;
      }
    }
    surfMap = local_4c;
    SurfaceMap_FUN_00450a90(local_4c,bx,by,&local_60,&local_60,&local_58);
    SurfaceMap_FUN_00450a90(surfMap,bx + 1U,by + 1U,&local_60,&local_60,&local_54);
    local_48.x = local_58 - local_54;
    SurfaceMap_FUN_00450a90(surfMap,bx + 1U,by,&local_60,&local_60,&local_58);
    SurfaceMap_FUN_00450a90(surfMap,bx,by + 1U,&local_60,&local_60,&local_54);
    SurfaceMap_FUN_0044f0b0
              (surfMap,bx,by,
               (uint)((ushort)((ushort)(ABS(local_48.x) < ABS(local_58 - local_54)) << 8 |
                              (ushort)(ABS(local_48.x) == ABS(local_58 - local_54)) << 0xe) == 0));
    local_38.x = bx;
    local_38.y = by;
    Level_FUN_00431380(level,&local_38,1);
    goto switchD_0042fb8d_caseD_4;
  }
  local_30[1] = 1;
  local_30[2] = 1;
  local_8 = 1;
  local_30[0] = 0;
  local_18 = 0;
  local_10 = 0;
  local_1c = 3;
  local_14 = 3;
  local_4 = 3;
  uVar11 = 0;
  local_30[3] = 2;
  local_30[4] = 2;
  local_c = 2;
  pLVar1->flags1 = LVar6 | (BLOCK1_UNK_4|BLOCK1_UNK_10);
  puVar10 = local_30 + 1;
  do {
    if ((puVar10[-1] == (local_38.x & 0xffU)) && (*puVar10 == ((uint)local_38.x >> 8 & 0xff))) {
      bx._0_1_ = (byte)uVar11;
      goto LAB_0042fc43;
    }
    uVar11 += 1;
    puVar10 = puVar10 + 2;
  } while (uVar11 < 6);
LAB_0042fc43:
  if (3 < (byte)bx) {
    if (pLVar1->terrain - 1 < 5) {
      pLVar1->texture = TEXTURE_WALL_GAP;
    }
    pLVar1->flags1 =
         LVar4 & 0xffff0000 |
         (uint)CONCAT11((char)(LVar6 >> 8),(char)(LVar6 | (BLOCK1_UNK_4|BLOCK1_UNK_10))) |
         BLOCK1_UNK_2000;
    pLVar1->field_3 = (byte)bx - 4;
    SurfaceMap_FUN_0044f0b0(local_4c,bx,by,(byte)((byte)bx - 4) & 1);
    goto switchD_0042fb8d_caseD_4;
  }
  if ((LVar4 & BLOCK1_REINFORCED) == BLOCK1_NONE) {
    if ((int)pLVar1->randomness % 10 == 0) {
      if (true) {
        switch(pLVar1->terrain) {
        case TERRAIN_IMMOVABLE:
        case TERRAIN_WATER_unused:
          goto switchD_0042fce8_caseD_1;
        case TERRAIN_HARD:
          goto switchD_0042fce8_caseD_2;
        case TERRAIN_MEDIUM:
          goto switchD_0042fce8_caseD_3;
        case TERRAIN_LOOSE:
          goto switchD_0042fce8_caseD_4;
        case TERRAIN_SOIL:
          goto switchD_0042fce8_caseD_5;
        case TERRAIN_ORESEAM:
          goto switchD_0042fce8_caseD_8;
        case TERRAIN_CRYSTALSEAM:
          goto switchD_0042fce8_caseD_a;
        case TERRAIN_RECHARGESEAM:
          goto switchD_0042fce8_caseD_b;
        }
      }
    }
    else {
      if (true) {
        switch(pLVar1->terrain) {
        case TERRAIN_IMMOVABLE:
        case TERRAIN_WATER_unused:
switchD_0042fce8_caseD_1:
          pLVar1->texture = TEXTURE_WALL_F_IMMOVABLE;
          pLVar1->field_3 = (byte)bx;
          goto switchD_0042fb8d_caseD_4;
        case TERRAIN_HARD:
switchD_0042fce8_caseD_2:
          pLVar1->texture = TEXTURE_WALL_F_HARD;
          pLVar1->field_3 = (byte)bx;
          goto switchD_0042fb8d_caseD_4;
        case TERRAIN_MEDIUM:
switchD_0042fce8_caseD_3:
          pLVar1->texture = TEXTURE_WALL_F_MEDIUM;
          pLVar1->field_3 = (byte)bx;
          goto switchD_0042fb8d_caseD_4;
        case TERRAIN_LOOSE:
switchD_0042fce8_caseD_4:
          pLVar1->texture = TEXTURE_WALL_F_LOOSE;
          pLVar1->field_3 = (byte)bx;
          goto switchD_0042fb8d_caseD_4;
        case TERRAIN_SOIL:
switchD_0042fce8_caseD_5:
          pLVar1->texture = TEXTURE_WALL_F_SOIL;
          pLVar1->field_3 = (byte)bx;
          goto switchD_0042fb8d_caseD_4;
        case TERRAIN_ORESEAM:
switchD_0042fce8_caseD_8:
          pLVar1->texture = TEXTURE_WALL_F_ORESEAM;
          pLVar1->field_3 = (byte)bx;
          goto switchD_0042fb8d_caseD_4;
        case TERRAIN_CRYSTALSEAM:
switchD_0042fce8_caseD_a:
          pLVar1->texture = TEXTURE_WALL_F_CRYSTALSEAM;
          pLVar1->field_3 = (byte)bx;
          goto switchD_0042fb8d_caseD_4;
        case TERRAIN_RECHARGESEAM:
switchD_0042fce8_caseD_b:
          pLVar1->texture = TEXTURE_WALL_F_RECHARGESEAM;
        }
      }
    }
  }
  else {
    if (true) {
      switch(pLVar1->terrain) {
      case TERRAIN_IMMOVABLE:
      case TERRAIN_WATER_unused:
        pLVar1->texture = TEXTURE_WALL_R_IMMOVABLE;
        pLVar1->field_3 = (byte)bx;
        break;
      case TERRAIN_HARD:
        pLVar1->texture = TEXTURE_WALL_R_HARD;
        pLVar1->field_3 = (byte)bx;
        break;
      case TERRAIN_MEDIUM:
        pLVar1->texture = TEXTURE_WALL_R_MEDIUM;
        pLVar1->field_3 = (byte)bx;
        break;
      case TERRAIN_LOOSE:
        pLVar1->texture = TEXTURE_WALL_R_LOOSE;
        pLVar1->field_3 = (byte)bx;
        break;
      case TERRAIN_SOIL:
        pLVar1->texture = TEXTURE_WALL_R_SOIL;
        pLVar1->field_3 = (byte)bx;
        break;
      default:
        goto switchD_0042fce8_caseD_6;
      }
      goto switchD_0042fb8d_caseD_4;
    }
  }
switchD_0042fce8_caseD_6:
  pLVar1->field_3 = (byte)bx;
switchD_0042fb8d_caseD_4:
  LVar4 = pLVar1->flags1;
  if ((((LVar4 & BLOCK1_UNK_4) != BLOCK1_NONE) && ((LVar4 & BLOCK1_UNK_800000) != BLOCK1_NONE)) &&
     ((pLVar1->terrain == TERRAIN_IMMOVABLE ||
      ((pLVar1->terrain == TERRAIN_WATER_unused || ((LVar4 & BLOCK1_UNK_8) != BLOCK1_NONE)))))) {
    pLVar1->flags1 = LVar4 & ~BLOCK1_UNK_800000;
    SurfaceMap_FUN_0044f830(level->surfaceMap,bx,by);
  }
  FVar9 = main::Main_GetCLFlags();
  iVar3 = local_3c;
  if ((FVar9 & FEATURE_BLOCKFADEIN) == FEATURE_NONE) {
    iVar3 = 0;
  }
  uVar11 = extraout_ECX & 0xffffff00 | (uint)pLVar1->field_3;
  uVar12 = extraout_EDX & 0xffffff00 | (uint)pLVar1->texture;
  if (iVar3 == 0) {
    SurfaceMap_UpdateBlockVisual(level->surfaceMap,bx,by,uVar12,uVar11);
  }
  else {
    SurfaceMap_FadeInBlock(level->surfaceMap,bx,by,uVar12,uVar11);
  }
  if (level->UseRoof != BOOL3_FALSE) {
    Level_Block_FUN_004332b0(level,bx,by);
  }
  return;
}

