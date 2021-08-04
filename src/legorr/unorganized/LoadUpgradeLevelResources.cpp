
enum PolyMode
{
  POLY_LOW    = 0,
  POLY_MEDIUM = 1,
  POLY_HIGH   = 2,
  POLY_FP     = 3,
};

struct ObjectUpgradePartData
{
	/*00,4*/ unsigned int level;
	/*04,4*/ int NullInstance; // 0-indexed, but 1-indexed in .ae file
	/*08,4*/ char* NullObjectName;
	/*0c,4*/ char* WeaponName;
	/*10,4*/ UpgradeData* upgradeData;
	/*14*/
};
// ; '000' represents a three bit binary number for each type of upgrade...
// ; All the parts in every section will be removed when any other level is selected...
// ; Format (No spaces are allowed in the second column:
// ; <Upgrade part (defined in Lego.cfg)>	[TAB]	<Null object name>,<Null instance (1-n)>
// ;	Object			Null
// ;Binary sequence order is [carry] [scan] [speed] [drill]
// ;therefore a vehicle with carry and speed upgrade will be 1010

#define LvlCarry(levelMask) (((int)(level) >> 3) & 0x1)
#define LvlScan(levelMask)  (((int)(level) >> 2) & 0x1)
#define LvlSpeed(levelMask) (((int)(level) >> 1) & 0x1)
#define LvlDrill(levelMask) (((int)(level) >> 0) & 0x1)


struct ObjectUpgradesData
{
	/*00,4*/ ObjectUpgradePartData* parts; // always allocated as ObjectUpgradePartData[200]
	/*04,4*/ unsigned int count;
	/*08,4*/ unsigned int field_8;
	/*0c,4*/ unsigned int levelMask; // 0-15 mask: [3][2][1][0] [carry][scan][speed][drill]
	/*10*/
};

// struct ObjectUpgradesData
// {
//   /*000,140*/ UpgradeLevelData levels[16];
//   /*140,*/

//   // ???

//   /*fa0*/ // (4000)
// };

struct UpgradeData
{
	/*00,4*/ int objIndex;
	/*04,4*/ ResourceData* aeResData;
	/*08,4*/ unsigned int field_8;
	/*0c,4*/ unsigned int field_c;
	/*10*/
};

// Base object data type used by Upgrades/Mini-Figures/RockRaiders/Buildings
struct AEObjectData
{
	/*00,4*/ int objIndex;
	/*04,4*/ ResourceData* aeResData;
	/*08,4*/ unsigned int field_8;
	/*0c,4*/ unsigned int field_c;
};

struct CreatureData
{
	/*00,4*/ int objIndex;
	/*04,4*/ ResourceData* aeResData;


	/*74*/
};

struct BuildingData
{
	/*000,4*/ int objIndex;
	/*004,4*/ ResourceData* aeResData;  // ACT, true
	/*008,4*/ char* CarryNullName;
	/*00c,4*/ char* CameraNullName;
	/*010,4*/ char* DepositNullName;
	/*014,4*/ char* EntranceNullName;
	/*018,4*/ char* ToolNullName;
	/*01c,4*/ char* FireNullName;     // "Immafiringmahlazer!!!!"... that kind of "Fire"
	/*020,4*/ char* yPivot;
	/*024,4*/ char* xPivot;

	// ???

	/*070,4*/ int CarryNullFrames
	/*074,4*/ int CameraNullFrames
	/*078,4*/ int ToolNullFrames
	/*07c,4*/ ResourceData* PowerLevelScene;  // LWS, true
	/*080,4*/ unsigned int field_80;
	/*084,4*/ Point2I* shapePoints; // Always an allocated array of Point2I[10] (0x50 bytes)
	/*088,4*/ unsigned int shapeCount;
	/*08c,10*/ ObjectUpgradesData upgrades;

	// ???

	/*0d0,4*/ float PivotMaxZ;
	/*0d4,4*/ float PivotMinZ;

	// ???

	/*144,4*/ unsigned int count_144; // unknown count
	/*148,4*/ unsigned int flags;
	/*14c*/
};


struct VehicleData
{
	/*000,4*/ int objIndex;
	/*004,4*/ char* WheelNullName;
	/*008,4*/ ResourceData* aeResData1
	/*00c,4*/ ResourceData* aeResData2; // Optional second ae file (seen for Grannit Grinder legs)
	/*010,4*/ ResourceData* WheelMesh; // LWO, false

	// ???

	/*040,4*/ BOOL hasWheelNull;

	// ???

	/*05c,4*/ unsigned int field_5c;
	/*060,4*/ unsigned int field_60;
	/*064,4*/ float float_64;
	/*068,4*/ float WheelRadius; // default: 3.0, or checks mesh file(?)

	// ???
	
	/*0b4,4*/ char* DrillNullName;
	/*0b8,4*/ char* DepositNullName;
	/*0bc,4*/ char* FireNullName;  // "fire laser"
	/*0c0,4*/ char* DriverNullName;
	/*0c4,4*/ char* yPivot;
	/*0c8,4*/ char* xPivot;

	// ???

  /*0d8,4*/ BOOL3 CameraFlipDir;
  /*0dc,4*/ char* CarryNullName;
  /*0e0,4*/ char* CameraNullName;

  // ???

  /*11c,4*/ int CarryNullFrames;
  /*120,4*/ int CameraNullFrames;
  /*124,10*/ ObjectUpgradesData upgrades;

	// ???

	/*168,4*/ float PivotMaxZ;
	/*16c,4*/ float PivotMinZ;

	// ???

	/*1e0,4*/ void* subdata_1e0;
	/*1e4,4*/ void* subdata_1e4;
	/*1e8,4*/ unsigned int flags; // CFG:HoldMissing==TRUE : 0x8
	/*1ec*/
};


void __cdecl lego::res::Res_LoadUpgradeLevels(ObjectUpgradesData* upgrades, const CFGProperty* aeRoot, const char* rootName)

{
  uint *puVar1;
  char cVar2;
  undefined4 *puVar3;
  char *pcVar4;
  // const CFGProperty* prop;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  char *pcVar9;
  // unsigned int level;
  char* parts[3];
  char buffer[256];
  
  upgrades->count = 0;
  upgrades->data = (ObjectUpgradePartData*)std::malloc(4000 /*0xfa0*/ /*sizeof(ObjectUpgradePartData[200])*/ /*sizeof(ObjectUpgradePartData) * 200*/);
  std::memset(upgrades->data, 0, 4000 /*0xfa0*/ /*sizeof(ObjectUpgradePartData[200])*/ /*sizeof(ObjectUpgradePartData) * 200*/);
  // // param_1[1] = 0;
  // puVar3 = (undefined4 *)std::malloc(4000);
  // // *param_1 = (int)puVar3;
  // upgrades->data = puVar3;
  // std::memset(puVar3, 0, 4000);
  // for (iVar5 = 1000; iVar5 != 0; iVar5 += -1) {
  //   *puVar3 = 0;
  //   puVar3 = puVar3 + 1;
  // }
  // unsigned int level = 0;

  for (unsigned int level = 0; level < 16; level++) {

    std::sprintf(buffer, "Level%i%i%i%i", 
        LvlCarry(level),  // (level>>3) & 1,
        LvlSpeed(level),  // (level>>2) & 1,
        LvlScan(level),   // (level>>1) & 1,
        LvlDrill(level)); // (level>>0) & 1);

    const char* keyPath = cfg::CFG_JoinPath(rootName, "Upgrades", buffer, NULL);

    const CFGProperty* prop = cfg::CFG_GetBlockFirstChild(aeRoot, keyPath);
    if (prop == NULL)
      continue;

    // param_1[3] = param_1[3] | level;
    upgrades->levelMask |= level;
    for (; prop != NULL; prop = cfg::CFG_NextFlatProperty(prop)) {
      // uVar6 = 0xffffffff;
      ObjectUpgradePartData* upgradePart = &upgrades->data->levels[upgrades->count];
      // puVar1 = (uint *)(upgrades->data + upgrades->count * 0x14);
      // puVar1 = (uint *)(*param_1 + param_1[1] * 0x14);
      // pcVar4 = prop->value;
      std::strcpy(buffer, prop->value);
      // do {
      //   pcVar9 = pcVar4;
      //   if (uVar6 == 0) break;
      //   uVar6--;
      //   pcVar9 = pcVar4 + 1;
      //   cVar2 = *pcVar4;
      //   pcVar4 = pcVar9;
      // } while (cVar2 != '\0');
      // uVar6 = ~uVar6;
      // puVar3 = (undefined4 *)(pcVar9 + -uVar6);
      // puVar8 = (undefined4 *)buffer;
      // for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 -= 1) {
      //   *puVar8++ = *puVar3++;
      // }
      // for (uVar6 &= 3; uVar6 != 0; uVar6 -= 1) {
      //   *(undefined *)puVar8 = *(undefined *)puVar3;
      //   puVar3 = (undefined4 *)((int)puVar3 + 1);
      //   puVar8 = (undefined4 *)((int)puVar8 + 1);
      // }
      int numParts = util::stringSplit(buffer, parts, ",");
      if (numParts == 3) {
        // uVar6 = 0xffffffff;
        // pcVar4 = parts[2];
        // do {
        //   if (uVar6 == 0) break;
        //   uVar6 -= 1;
        //   cVar2 = *pcVar4;
        //   pcVar4 = pcVar4 + 1;
        // } while (cVar2 != '\0');
        // puVar3 = (undefined4 *)std::malloc(~uVar6);
        // uVar6 = 0xffffffff;
        // puVar1[3] = (uint)puVar3;
        // pcVar4 = parts[2];
        // do {
        //   pcVar9 = pcVar4;
        //   if (uVar6 == 0) break;
        //   uVar6 -= 1;
        //   pcVar9 = pcVar4 + 1;
        //   cVar2 = *pcVar4;
        //   pcVar4 = pcVar9;
        // } while (cVar2 != '\0');
        // uVar6 = ~uVar6;
        // puVar8 = (undefined4 *)(pcVar9 + -uVar6);
        // for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 -= 1) {
        //   *puVar3 = *puVar8;
        //   puVar8 = puVar8 + 1;
        //   puVar3 = puVar3 + 1;
        // }
        // for (uVar6 &= 3; uVar6 != 0; uVar6 -= 1) {
        //   *(undefined *)puVar3 = *(undefined *)puVar8;
        //   puVar8 = (undefined4 *)((int)puVar8 + 1);
        //   puVar3 = (undefined4 *)((int)puVar3 + 1);
        // }
        upgradePart->WeaponName = _strdup(parts[2]);
      }
      // puVar1[2] = _strdup(parts[0]);
      // *puVar1 = level;
      // puVar1[1] = std::atoi(parts[1]) - 1;
      // puVar1[4] = Game_GetUpgradeData(prop->key);

      upgradePart->NullObjectName = _strdup(parts[0]);
      upgradePart->level = level;
      upgradePart->NullInstance = std::atoi(parts[1]) - 1;
      upgradePart->upgradeData = Game_GetUpgradeData(prop->key);
      // param_1[1]++;
      upgrades->count++;
    }
    // }

    // level++;
    // if (level > 0xf) {
    //   if (upgrades->count == 0) {
    //     std::free(upgrades->data);
    //     upgrades->data = NULL;
    //   }
    //   // if (param_1[1] == 0) {
    //   //   std::free((void *)*param_1);
    //   //   *param_1 = 0;
    //   // }
    //   return;
    // }
  } //while( true );

  if (upgrades->count == 0) {
    std::free(upgrades->data);
    upgrades->data = NULL;
  }
  // if (param_1[1] == 0) {
  //   std::free((void *)*param_1);
  //   *param_1 = 0;
  // }
}

