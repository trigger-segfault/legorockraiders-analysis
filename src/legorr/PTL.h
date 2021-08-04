#pragma once
#ifndef LEGORR__PTL_H
#define LEGORR__PTL_H



struct PTLProperty
{
	/*0,4*/ int eventIndex;
	/*4,4*/ int actionIndex;
	/*8*/
};


// populated once on boot(?), essentially constant
// <LegoRR.exe @00500190>
static const char* g_Messages_TABLE[65];

// <LegoRR.exe @00556be0>
static PTLProperty g_LEVEL_PTLEVENTS_TABLE[40];

// <LegoRR.exe @00556d20>
static unsigned int g_LEVEL_PTLEVENTS_COUNT;

#pragma region enum PTL_EVENTS
// enum PTL_EVENTS
// {
// 	"Message_Null",
// 	"Message_Select",
// 	"Message_Selected",
// 	"Message_ClearSelection",
// 	"Message_Deselect",
// 	"Message_Goto",
// 	"Message_RockMonsterGoto",
// 	"Message_RockMonsterGotoComplete",
// 	"Message_UserGoto",
// 	"Message_FirstPerson",
// 	"Message_TrackObject",
// 	"Message_TopView",
// 	"Message_PlaySample",
// 	"Message_Dig",
// 	"Message_DigComplete",
// 	"Message_Repair",
// 	"Message_RepairComplete",
// 	"Message_Reinforce",
// 	"Message_ReinforceComplete",
// 	"Message_RockFall",
// 	"Message_RockFallComplete",
// 	"Message_GenerateCrystal",
// 	"Message_GenerateCrystalComplete",
// 	"Message_CollectCrystal",
// 	"Message_CollectCrystalComplete",
// 	"Message_CrystalToRefinery",
// 	"Message_CrystalToRefineryComplete",
// 	"Message_GenerateOre",
// 	"Message_GenerateOreComplete",
// 	"Message_CollectOre",
// 	"Message_CollectOreComplete",
// 	"Message_GenerateRockMonster",
// 	"Message_GenerateRockMonsterComplete",
// 	"Message_GatherRock",
// 	"Message_GatherRockComplete",
// 	"Message_PickRandomFloor",
// 	"Message_PickRandomFloorComplete",
// 	"Message_AttackBuilding",
// 	"Message_AttackBuildingComplete",
// 	"Message_Clear",
// 	"Message_ClearComplete",
// 	"Message_GetIn",
// 	"Message_ManSelectedAndMonsterClicked",
// 	"Message_FollowAttack",
// 	"Message_CollectTool",
// 	"Message_ReduceSelection",
// 	"Message_ClearFallIn",
// 	"Message_ClearFallInComplete",
// 	"Message_BuildPath",
// 	"Message_BuildPathComplete",
// 	"Message_Train",
// 	"Message_TrainComplete",
// 	"Message_GenerateCrystalAndOre",
// 	"Message_GenerateCrystalAndOreComplete",
// 	"Message_GenerateFromCryOre",
// 	"Message_GenerateFromCryOreComplete",
// 	"Message_Upgrade",
// 	"Message_UpgradeComplete",
// 	"Message_ClearBuilding",
// 	"Message_ClearBuildingComplete",
// 	"Message_ClearInitial",
// 	"Message_ClearInitialComplete",
// 	"Message_ClearRemovePath",
// 	"Message_ClearRemovePathComplete",
// 	"Message_Debug_DestroyAll",
// };
#pragma endregion

// <LegoRR.exe @00451f90>
void __cdecl Boot_InitPTLEventNamesTable(void)
{
	g_Messages_TABLE[0] = "Message_Null";
	g_Messages_TABLE[1] = "Message_Select";
	g_Messages_TABLE[2] = "Message_Selected";
	g_Messages_TABLE[3] = "Message_ClearSelection";
	g_Messages_TABLE[4] = "Message_Deselect";
	g_Messages_TABLE[5] = "Message_Goto";
	g_Messages_TABLE[6] = "Message_RockMonsterGoto";
	g_Messages_TABLE[7] = "Message_RockMonsterGotoComplete";
	g_Messages_TABLE[8] = "Message_UserGoto";
	g_Messages_TABLE[9] = "Message_FirstPerson";
	g_Messages_TABLE[10] = "Message_TrackObject";
	g_Messages_TABLE[11] = "Message_TopView";
	g_Messages_TABLE[12] = "Message_PlaySample";
	g_Messages_TABLE[13] = "Message_Dig";
	g_Messages_TABLE[14] = "Message_DigComplete";
	g_Messages_TABLE[15] = "Message_Repair";
	g_Messages_TABLE[16] = "Message_RepairComplete";
	g_Messages_TABLE[17] = "Message_Reinforce";
	g_Messages_TABLE[18] = "Message_ReinforceComplete";
	g_Messages_TABLE[19] = "Message_RockFall";
	g_Messages_TABLE[20] = "Message_RockFallComplete";
	g_Messages_TABLE[21] = "Message_GenerateCrystal";
	g_Messages_TABLE[22] = "Message_GenerateCrystalComplete";
	g_Messages_TABLE[23] = "Message_CollectCrystal";
	g_Messages_TABLE[24] = "Message_CollectCrystalComplete";
	g_Messages_TABLE[25] = "Message_CrystalToRefinery";
	g_Messages_TABLE[26] = "Message_CrystalToRefineryComplete";
	g_Messages_TABLE[27] = "Message_GenerateOre";
	g_Messages_TABLE[28] = "Message_GenerateOreComplete";
	g_Messages_TABLE[29] = "Message_CollectOre";
	g_Messages_TABLE[30] = "Message_CollectOreComplete";
	g_Messages_TABLE[31] = "Message_GenerateRockMonster";
	g_Messages_TABLE[32] = "Message_GenerateRockMonsterComplete";
	g_Messages_TABLE[33] = "Message_GatherRock";
	g_Messages_TABLE[34] = "Message_GatherRockComplete";
	g_Messages_TABLE[35] = "Message_PickRandomFloor";
	g_Messages_TABLE[36] = "Message_PickRandomFloorComplete";
	g_Messages_TABLE[37] = "Message_AttackBuilding";
	g_Messages_TABLE[38] = "Message_AttackBuildingComplete";
	g_Messages_TABLE[39] = "Message_Clear";
	g_Messages_TABLE[40] = "Message_ClearComplete";
	g_Messages_TABLE[41] = "Message_GetIn";
	g_Messages_TABLE[42] = "Message_ManSelectedAndMonsterClicked";
	g_Messages_TABLE[43] = "Message_FollowAttack";
	g_Messages_TABLE[44] = "Message_CollectTool";
	g_Messages_TABLE[45] = "Message_ReduceSelection";
	g_Messages_TABLE[46] = "Message_ClearFallIn";
	g_Messages_TABLE[47] = "Message_ClearFallInComplete";
	g_Messages_TABLE[48] = "Message_BuildPath";
	g_Messages_TABLE[49] = "Message_BuildPathComplete";
	g_Messages_TABLE[50] = "Message_Train";
	g_Messages_TABLE[51] = "Message_TrainComplete";
	g_Messages_TABLE[52] = "Message_GenerateCrystalAndOre";
	g_Messages_TABLE[53] = "Message_GenerateCrystalAndOreComplete";
	g_Messages_TABLE[54] = "Message_GenerateFromCryOre";
	g_Messages_TABLE[55] = "Message_GenerateFromCryOreComplete";
	g_Messages_TABLE[56] = "Message_Upgrade";
	g_Messages_TABLE[57] = "Message_UpgradeComplete";
	g_Messages_TABLE[58] = "Message_ClearBuilding";
	g_Messages_TABLE[59] = "Message_ClearBuildingComplete";
	g_Messages_TABLE[60] = "Message_ClearInitial";
	g_Messages_TABLE[61] = "Message_ClearInitialComplete";
	g_Messages_TABLE[62] = "Message_ClearRemovePath";
	g_Messages_TABLE[63] = "Message_ClearRemovePathComplete";
	g_Messages_TABLE[64] = "Message_Debug_DestroyAll";
}

// <LegoRR.exe @00452290>
int __cdecl Game_LookupPTLEventIndex(const char* ptlName)
{
	int cmpResult = 0; // this value is never used, just keeps the compiler from complaining.
	for (int i = 0; i < 65; i++) {
		cmpResult= _stricmp(g_Messages_TABLE[i] + 8, ptlName);
		if (cmpResult == 0)
			return i;
	}
	return cmpResult; // I kid you not, failure just returns the result of _stricmp, which could totally be 1 or -1 (don't screw up the PTL names I guess...)
	// int iVar1;
	// char **ppcVar2;
	// int iVar3;

	// iVar3 = 0;
	// ppcVar2 = g_Messages_TABLE;
	// do {
	// 	iVar1 = _stricmp(*ppcVar2 + 8, ptlName);
	// 	if (iVar1 == 0) {
	// 		return iVar3;
	// 	}
	// 	ppcVar2 = ppcVar2 + 1;
	// 	iVar3 += 1;
	// } while (ppcVar2 < &DAT_00500294);
	// return iVar1;
}

// <LegoRR.exe @0045daa0>
BOOL __cdecl Main_loadPTLCFG__0045daa0(const char* filename, const char* keyBlockPath)
{
	uint uVar1;
	CFGProperty *root;
	CFGProperty *prop;
	int iVar2;

	g_LEVEL_PTLEVENTS_COUNT = 0;
	CFGProperty* root = CFG_readFile(filename);
	if (root != NULL) {
		CFGProperty* prop = CFG_getBlockFirstChild(root, keyBlockPath);
		unsigned int index = g_LEVEL_PTLEVENTS_COUNT;
		while (prop != NULL) {
			g_LEVEL_PTLEVENTS_COUNT = index + 1; // this redundant line is kept for failure scenarios

			// int ptlIndex = Game_LookupPTLEventIndex(prop->key);
			g_LEVEL_PTLEVENTS_TABLE[index].eventIndex = Game_LookupPTLEventIndex(prop->key);
			// ptlIndex = Game_LookupPTLEventIndex(prop->value);
			g_LEVEL_PTLEVENTS_TABLE[index].actionIndex = Game_LookupPTLEventIndex(prop->value);
			prop = CFG_nextFlatProperty(prop);

			index++;
		}
		g_LEVEL_PTLEVENTS_COUNT = index;
		CFG__cleanup(root);
		return true;
	}
	return false;
}

// {
// 	uint uVar1;
// 	CFGProperty *root;
// 	CFGProperty *prop;
// 	int iVar2;

// 	g_LEVEL_PTLEVENTS_COUNT = 0;
// 	root = CFG_readFile(filename);
// 	if (root != NULL) {
// 		prop = CFG_getBlockFirstChild(root,keyPath);
// 		uVar1 = g_LEVEL_PTLEVENTS_COUNT;
// 		while (prop != (CFGProperty *)0x0) {
// 		g_LEVEL_PTLEVENTS_COUNT = uVar1 + 1;
// 		iVar2 = Game_LookupPTLEventIndex(prop->key);
// 		g_LEVEL_PTLEVENTS_TABLE[uVar1].eventIndex = iVar2;
// 		iVar2 = Game_LookupPTLEventIndex(prop->value);
// 		g_LEVEL_PTLEVENTS_TABLE[uVar1].actionIndex = iVar2;
// 		prop = CFG_nextFlatProperty(prop);
// 		uVar1 = g_LEVEL_PTLEVENTS_COUNT;
// 		}
// 		g_LEVEL_PTLEVENTS_COUNT = uVar1;
// 		CFG__cleanup(root);
// 		return true;
// 	}
// 	return false;
// }


// param_1 is some unknown large structure of something like 0x800 bytes in size,
// the passed ptr is the location of the eventIndex to transform, assigns over the eventIndex
// <LegoRR.exe @0045db30>
void __cdecl Game_PTLEventToAction__0045db30(int* param_1)
{
	uint uVar1;
	PTLProperty *pPVar2;

	uVar1 = 0;
	if (g_LEVEL_PTLEVENTS_COUNT != 0) {
		pPVar2 = g_LEVEL_PTLEVENTS_TABLE;
		while (*param_1 != pPVar2->eventIndex) {
			uVar1 += 1;
			pPVar2 = pPVar2 + 1;
			if (g_LEVEL_PTLEVENTS_COUNT <= uVar1) {
				return;
			}
		}
		*param_1 = pPVar2->actionIndex;
	}
	return;
}

// <LegoRR.exe @0050029c>
static unsigned int g_GAME_UNK_COUNT__0050029c;

// <LegoRR.exe @00452770>
void __cdecl FUN_00452770(undefined4* param_1)
{
	FUN_00452220((int)param_1);
	FUN_00452f10((uint)param_1);
	if (DAT_00557160 == param_1) {
		FUN_00429520(1, (int *)0x0, 0);
		DAT_00557160 = (undefined4 *)0x0;
	}
	if (*(undefined4 **)(DAT_005570e8 + 4) == param_1) {
		*(undefined4 *)(DAT_005570e8 + 4) = 0;
		FUN_00442520(param_1, &DAT_005573f8, &DAT_005573fc);
		g_GAME_GameFlags1 |= 0x4000;
	}
	return;
}

// <LegoRR.exe @00452220>
void __cdecl FUN_00452220(int param_1)
{
	int iVar1;
	int iVar2;
	uint uVar3;
	uint uVar4;
	undefined4 *puVar5;
	undefined4 *puVar6;

	uVar4 = 0;
	uVar3 = *(unsigned int*)(&DAT_004fff20 + DAT_004fff28 * 4);
	if (uVar3 != 0) {
		do {
			iVar1 = uVar4 + DAT_004fff28 * 0x800;
			if (param_1 == *(int*)(&DAT_004ebf24 + iVar1 * 0x14)) {
				uVar3 -= 1;
				iVar2 = 5;
				puVar5 = (undefined4 *)(&DAT_004ebf20 + (DAT_004fff28 * 0x800 + uVar3) * 0x14);
				puVar6 = (undefined4 *)(&DAT_004ebf20 + iVar1 * 0x14);
				while (iVar2 != 0) {
					iVar2 += -1;
					*puVar6 = *puVar5;
					puVar5 = puVar5 + 1;
					puVar6 = puVar6 + 1;
				}
				*(unsigned int*)(&DAT_004fff20 + DAT_004fff28 * 4) = uVar3;
			}
			uVar4 += 1;
		} while (uVar4 < uVar3);
	}
	return;
}




enum NERPSFuncArgs
{
	NERPS_ARGS_0          = 0, // takes 0 arguments, returns value
	NERPS_ARGS_1          = 1, // takes 1 arguments, returns value
	NERPS_ARGS_2          = 2, // takes 2 arguments, returns value
	NERPS_ARGS_0_NORETURN = 3, // takes 0 arguments, no return
	NERPS_ARGS_1_NORETURN = 4, // takes 1 arguments, no return
	NERPS_ARGS_2_NORETURN = 5, // takes 2 arguments, no return
	NERPS_ARGS_3_NORETURN = 6, // takes 3 arguments, no return
	NERPS_END_OF_LIST     = 7, // invalid (end of list)
};

typedef int (__cdecl *NERPSFuncPtr)(int*);

struct NERPSFunction
{
	const char* funcName;
	NERPSFuncPtr function;
	NERPSFuncArgs arguments;
};

// last item is "**End Of List**"
// <LegoRR.exe @004a6948 -> 004a7710>
static NERPSFunction g_NERPS_FUNCTIONS[294];

// <LegoRR.exe @00500958>
static int g_NERPS_REGISTERS[8];

// <LegoRR.exe @005009a0>
static float g_NERPS_TIMERS[4];


// <LegoRR.exe @00452390>
void __cdecl Game_PTL_UNKInit__00452390(void)
{
	int iVar1;
	undefined4 *puVar2;
	uint *puVar3;
	uint uVar4;
	int iVar5;

	if ((g_GAME_GameFlags1 & 0x100000) == 0) {
		for (int i = 0; i < g_GAME_UNK_COUNT__0050029c; i++) {
			if ((&DAT_0076bb80)[ DAT_005000bc[i] ] != '\0') {
				FUN_00452320(DAT_005000c8[i].field_0, DAT_005000c8[i].field_4, DAT_005000c8[i].field_8, &DAT_005000c8[i].field_c)
				// FUN_00452320(puVar2[-2], puVar2[-1], *puVar2, puVar2 + 1);
			}
		}
	}
	// if ((g_GAME_GameFlags1 & 0x100000) == 0 && (uVar4 = 0, g_GAME_UNK_COUNT__0050029c != 0)) {
	// 	puVar2 = &DAT_005000d0;
	// 	do {
	// 		if ((&DAT_0076bb80)[(byte)(&DAT_005000bc)[uVar4]] != '\0') {
	// 			FUN_00452320(puVar2[-2],puVar2[-1],*puVar2,puVar2 + 1);
	// 		}
	// 		uVar4 += 1;
	// 		puVar2 = puVar2 + 5;
	// 	} while (uVar4 < g_GAME_UNK_COUNT__0050029c);
	// }

	uVar4 = 0;
	if (*(int *)(&DAT_004fff20 + DAT_004fff28 * 4) != 0) {
		do {
			Game_PTLEventToAction__0045db30((int *)(&DAT_004ebf20 + (DAT_004fff28 * 0x800 + uVar4) * 0x14));
			uVar4 += 1;
		} while (uVar4 < *(uint *)(&DAT_004fff20 + DAT_004fff28 * 4));
	}
	iVar5 = *(int *)(&DAT_004fff20 + DAT_004fff28 * 4);
	iVar1 = DAT_004fff28 * 0xa000;
	*(undefined4 *)(&DAT_004fff20 + DAT_004fff28 * 4) = 0;
	DAT_004fff28 = (uint)(DAT_004fff28 == 0);
	*(undefined4 *)(&DAT_004fff20 + DAT_004fff28 * 4) = 0;
	if (iVar5 != 0) {
		puVar3 = (uint *)(&DAT_004ebf28 + iVar1);
		do {
			switch(puVar3[-2]) {
			case 1:  // PTLEVENT_Select
				FUN_00452980((int **)puVar3[-1], *puVar3);
				break;
			case 3:  // PTLEVENT_ClearSelection
				FUN_00452ea0();
				break;
			case 4:  // PTLEVENT_Deselect
				FUN_00452f10(puVar3[-1]);
				break;
			case 5:  // PTLEVENT_Goto
			case 6:  // PTLEVENT_RockMonsterGoto
				FUN_004034f0((int *)puVar3[-1], puVar3 + 1, *puVar3);
				break;
			case 8:  // PTLEVENT_UserGoto
				FUN_004031a0(&DAT_004fff2c, DAT_00500298, puVar3 + 1, *puVar3);
				break;
			case 9:  // PTLEVENT_FirstPerson
				FUN_00453020(*puVar3);
				break;
			case 10: // PTLEVENT_TrackObject
				if (DAT_00500298 != 0) {
					FUN_00425c80(DAT_004fff2c);
				}
				break;
			case 11: // PTLEVENT_TopView  //0xb:
				FUN_00429520(1, (int *)NULL, 0);
				break;
			case 12: // PTLEVENT_PlaySample  //0xc:
				FUN_00465260(*puVar3, 0);
				break;
			case 19: // PTLEVENT_RockFall  //0x13:
				FUN_004316b0(puVar3[1], puVar3[2], *puVar3 & 0xffff, (float)(*puVar3 >> 0x10));
				break;
			case 21: // PTLEVENT_GenerateCrystal  //0x15:
				FUN_00439630(puVar3 + 1, 0, (float*)NULL, 1);
				break;
			case 23: // PTLEVENT_CollectCrystal  //0x17:
				FUN_00402650((int *)puVar3[-1], 0);
				break;
			case 25: // PTLEVENT_CrystalToRefinery  //0x19:
				FUN_00403540(puVar3[-1], *puVar3);
				break;
			case 27: // PTLEVENT_GenerateOre  //0x1b:
				FUN_00439770(puVar3 + 1, 0, (float*)NULL, 1);
				break;
			case 29: // PTLEVENT_CollectOre  //0x1d:
				FUN_00402650((int *)puVar3[-1], 0);
				break;
			case 31: // PTLEVENT_GenerateRockMonster  //0x1f:
				FUN_0043b160();
				break;
			case 33: // PTLEVENT_GatherRock  //0x21:
				FUN_00447390((int *)puVar3[-1]);
				break;
			case 35: // PTLEVENT_PickRandomFloor  //0x23:
				FUN_004526f0(puVar3[-1]);
				break;
			case 37: // PTLEVENT_AttackBuilding  //0x25:
				FUN_004474d0((float *)puVar3[-1], (undefined4 *)*puVar3);
				break;
			case 43: // PTLEVENT_FollowAttack  //0x2b:
				FUN_004035f0(puVar3[-1], *puVar3);
				break;
			case 45: // PTLEVENT_ReduceSelection  //0x2d:
				FUN_00452b80();
				break;
			case 52: // PTLEVENT_GenerateCrystalAndOre  //0x34:
				FUN_00439600(puVar3 + 1, 0);
				break;
			case 54: // PTLEVENT_GenerateFromCryOre  //0x36:
				FUN_00439540(puVar3 + 1);
				break;
			case 64: // PTLEVENT_Debug_DestroyAll  //0x40:
				FUN_00452f80();
				break;
			}
			puVar3 += 5;
			iVar5--;
		} while (iVar5 != 0);
	}
	return;
}

enum VK_CODES
{
	VK_LBUTTON = 1,
	VK_RBUTTON = 2,
	VK_CANCEL = 3, // Control-break processing
	VK_MBUTTON = 4,
	VK_XBUTTON1 = 5,
	VK_XBUTTON2 = 6,
};

if ((g_GAME_GameFlags2 & GAME2_ALLOWDEBUGKEYS /*0x10*/) != 0) {
	// Add debug keys?
	Game_UNK_WITHCOUNT__004522d0(2, 9,  0, 0, (undefined4 *)NULL);
	Game_UNK_WITHCOUNT__004522d0(3, 9,  0, 1, (undefined4 *)NULL);
	Game_UNK_WITHCOUNT__004522d0(5, 10, 0, 0, (undefined4 *)NULL);
	Game_UNK_WITHCOUNT__004522d0(4, 11, 0, 0, (undefined4 *)NULL);
}

struct UNKDATA_005000c8
{
	/*00,4*/ unsigned int field_0;  // assigned by param_2
	/*04,4*/ unsigned int field_4;  // assigned by param_3
	/*08,4*/ BOOL field_8;  // assigned by param_4 (bool_4)

	// likely combined structure
	/*0c,4*/ unsigned int field_c;  // assigned by param_5[0] (optional)
	/*10,4*/ unsigned int field_10; // assigned by param_5[1] (optional)
	/*14*/
};


static unsigned char DAT_005000bc[0xc];             // assigned by param_1
static UNKDATA_005000c8 DAT_005000c8[0xc]; // assigned by param_2 through param_5

static UNKDATA_005000c8 DAT_004ebf20[0xc];

// void __cdecl Game_PTL_UNKInit__00452390(void)

	if ((g_GAME_GameFlags1 & 0x100000) == 0) {
		for (int i = 0; i < g_GAME_UNK_COUNT__0050029c; i++) {
			if ((&DAT_0076bb80)[ DAT_005000bc[i] ] != '\0') {
				FUN_00452320(DAT_005000c8[i].field_0, DAT_005000c8[i].field_4, DAT_005000c8[i].field_8, &DAT_005000c8[i].field_c)
				// FUN_00452320(puVar2[-2], puVar2[-1], *puVar2, puVar2 + 1);
			}
		}
	}

//   if ((g_GAME_GameFlags1 & 0x100000) == 0 && (uVar4 = 0, g_GAME_UNK_COUNT__0050029c != 0)) {
//     puVar2 = &DAT_005000d0;
//     do {
//       if ((&DAT_0076bb80)[(byte)(&DAT_005000bc)[uVar4]] != '\0') {
//         FUN_00452320(puVar2[-2],puVar2[-1],*puVar2,puVar2 + 1);
//       }
//       uVar4 += 1;
//       puVar2 = puVar2 + 5;
//     } while (uVar4 < g_GAME_UNK_COUNT__0050029c);
//   }

// <LegoRR.exe @00452320>
void __cdecl FUN_00452320(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4* param_4)
{
	uint uVar1;
	int iVar2;

	uVar1 = *(uint *)(&DAT_004fff20 + DAT_004fff28 * 4);
	if (uVar1 < 0x800) {
		iVar2 = DAT_004fff28 * 0x800;
		*(uint *)(&DAT_004fff20 + DAT_004fff28 * 4) = uVar1 + 1;
		iVar2 = (iVar2 + uVar1) * 0x14;
		memset(&DAT_004ebf20 + iVar2, 0, 0x14);
		*(undefined4 *)(&DAT_004ebf20 + iVar2) = 0;
		*(undefined4 *)(&DAT_004ebf24 + iVar2) = 0;
		*(undefined4 *)(&DAT_004ebf28 + iVar2) = 0;
		*(undefined4 *)(&DAT_004ebf2c + iVar2) = 0;
		*(undefined4 *)(&DAT_004ebf30 + iVar2) = 0;
		*(undefined4 *)(&DAT_004ebf20 + iVar2) = param_1;
		*(undefined4 *)(&DAT_004ebf24 + iVar2) = param_2;
		*(undefined4 *)(&DAT_004ebf28 + iVar2) = param_3;
		if (param_4 != (undefined4 *)0x0) {
			*(undefined4 *)(&DAT_004ebf2c + iVar2) = *param_4;
			*(undefined4 *)(&DAT_004ebf30 + iVar2) = param_4[1];
		}
	}
	return;
}

// only called by Game_loadLevelCFG when ALLOWDEBUGKEYS game flag is set
// <LegoRR.exe @004522d0>
void __cdecl Game_UNK_WITHCOUNT__004522d0(unsigned char byte_1, undefined4 param_2, undefined4 param_3, BOOL bool_4, undefined4* param_5)
{
	DAT_005000bc[g_GAME_UNK_COUNT__0050029c] = byte_1; //param_1;

	DAT_005000c8[g_GAME_UNK_COUNT__0050029c].field_0 = param_2;
	DAT_005000c8[g_GAME_UNK_COUNT__0050029c].field_4 = param_3;
	DAT_005000c8[g_GAME_UNK_COUNT__0050029c].field_8 = bool_4; //param_4;
	if (param_5 != NULL) {
		DAT_005000c8[g_GAME_UNK_COUNT__0050029c].field_c  = param_5[0];
		DAT_005000c8[g_GAME_UNK_COUNT__0050029c].field_10 = param_5[1];
	}
	g_GAME_UNK_COUNT__0050029c++;

	// int iVar1;
	// uint uVar2;
	// // // (&DAT_005000bc)[g_GAME_UNK_COUNT__0050029c] = param_1;
	// // uVar2 = g_GAME_UNK_COUNT__0050029c;
	// // iVar1 = g_GAME_UNK_COUNT__0050029c * 0x14;
	// // // (&DAT_005000c8)[g_GAME_UNK_COUNT__0050029c * 5] = param_2;
	// // (&DAT_005000c8)[uVar2 * 5] = param_2;
	// // (&DAT_005000cc)[uVar2 * 5] = param_3;
	// // (&DAT_005000d0)[uVar2 * 5] = bool_4;
	// // // (&DAT_005000cc)[uVar2 * 5] = param_3;
	// if (param_5 != NULL) {
	// 	DAT_005000c8[g_GAME_UNK_COUNT__0050029c].field_c  = param_5[0];
	// 	DAT_005000c8[g_GAME_UNK_COUNT__0050029c].field_10 = param_5[1];
	// 	// *(undefined4 *)(&DAT_005000d4 + iVar1) = param_5[0];
	// 	// *(undefined4 *)(&DAT_005000d8 + iVar1) = param_5[1];
	// }
	// g_GAME_UNK_COUNT__0050029c++;
}


  g_NAMETABLE_SurfaceTypes[0] = "Lego_SurfaceType_Tunnel";
  g_NAMETABLE_SurfaceTypes[1] = "Lego_SurfaceType_Immovable";
  g_NAMETABLE_SurfaceTypes[2] = "Lego_SurfaceType_Hard";
  g_NAMETABLE_SurfaceTypes[3] = "Lego_SurfaceType_Medium";
  g_NAMETABLE_SurfaceTypes[4] = "Lego_SurfaceType_Loose";
  g_NAMETABLE_SurfaceTypes[5] = "Lego_SurfaceType_Soil";
  g_NAMETABLE_SurfaceTypes[6] = "Lego_SurfaceType_Lava";
  g_NAMETABLE_SurfaceTypes[7] = "Lego_SurfaceType_Water";
  g_NAMETABLE_SurfaceTypes[8] = "Lego_SurfaceType_OreSeam";
  g_NAMETABLE_SurfaceTypes[9] = "Lego_SurfaceType_Lake";
  g_NAMETABLE_SurfaceTypes[10] = "Lego_SurfaceType_CrystalSeam";
  g_NAMETABLE_SurfaceTypes[11] = "Lego_SurfaceType_RechargeSeam";
  g_NAMETABLE_SurfaceTypes[12] = "Lego_SurfaceType_Rubble";
  g_NAMETABLE_SurfaceTypes[13] = "Lego_SurfaceType_Reinforcement";
  g_NAMETABLE_SurfaceTypes[14] = "Lego_SurfaceType_Path";
  g_NAMETABLE_SurfaceTypes[15] = "Lego_SurfaceType_SlugHole";
  g_NAMETABLE_SurfaceTypes[16] = "Lego_SurfaceType_Undiscovered";
  g_NAMETABLE_SurfaceTypes[17] = "Lego_SurfaceType_Cavern";


#endif /* LEGORR__PTL_H */
