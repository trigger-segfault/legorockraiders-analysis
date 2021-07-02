


#pragma region SurfaceTypes

// <LegoRR.exe @00557290>
static const char* g_SurfaceTypes_TABLE[18]; // (confirmed size)

// <LegoRR.exe -> inside function @0041fa80>
void InitSurfaceTypes(void) {
	g_SurfaceTypes_TABLE[0] = "Lego_SurfaceType_Tunnel";
	g_SurfaceTypes_TABLE[1] = "Lego_SurfaceType_Immovable";
	g_SurfaceTypes_TABLE[2] = "Lego_SurfaceType_Hard";
	g_SurfaceTypes_TABLE[3] = "Lego_SurfaceType_Medium";
	g_SurfaceTypes_TABLE[4] = "Lego_SurfaceType_Loose";
	g_SurfaceTypes_TABLE[5] = "Lego_SurfaceType_Soil";
	g_SurfaceTypes_TABLE[6] = "Lego_SurfaceType_Lava";
	g_SurfaceTypes_TABLE[7] = "Lego_SurfaceType_Water";
	g_SurfaceTypes_TABLE[8] = "Lego_SurfaceType_OreSeam";
	g_SurfaceTypes_TABLE[9] = "Lego_SurfaceType_Lake";
	g_SurfaceTypes_TABLE[10] = "Lego_SurfaceType_CrystalSeam";
	g_SurfaceTypes_TABLE[11] = "Lego_SurfaceType_RechargeSeam";
	g_SurfaceTypes_TABLE[12] = "Lego_SurfaceType_Rubble";
	g_SurfaceTypes_TABLE[13] = "Lego_SurfaceType_Reinforcement";
	g_SurfaceTypes_TABLE[14] = "Lego_SurfaceType_Path";
	g_SurfaceTypes_TABLE[15] = "Lego_SurfaceType_SlugHole";
	g_SurfaceTypes_TABLE[16] = "Lego_SurfaceType_Undiscovered";
	g_SurfaceTypes_TABLE[17] = "Lego_SurfaceType_Cavern";
}

#pragma endregion


#pragma region Keys

// <LegoRR.exe @005775e0>
static const char* g_Messages_TABLE[256]; // (confirmed size)

// entire function just initializes this array (and zeros out unused slots)
// <LegoRR.exe @00485ce0>
void InitKeys(void) {
	// memset(g_KEYS_TABLE, 0, 256 * sizeof(char*));
	for (int i = 0; i < 256; i++)
		g_KEYS_TABLE[i] = NULL;

	g_KEYS_TABLE[1] = "KEY_ESCAPE";
	g_KEYS_TABLE[2] = "KEY_ONE";
	g_KEYS_TABLE[3] = "KEY_TWO";
	g_KEYS_TABLE[4] = "KEY_THREE";
	g_KEYS_TABLE[5] = "KEY_FOUR";
	g_KEYS_TABLE[6] = "KEY_FIVE";
	g_KEYS_TABLE[7] = "KEY_SIX";
	g_KEYS_TABLE[8] = "KEY_SEVEN";
	g_KEYS_TABLE[9] = "KEY_EIGHT";
	g_KEYS_TABLE[10] = "KEY_NINE";
	g_KEYS_TABLE[11] = "KEY_ZERO";
	g_KEYS_TABLE[12] = "KEY_MINUS";
	g_KEYS_TABLE[13] = "KEY_EQUALS";
	g_KEYS_TABLE[14] = "KEY_BACKSPACE";
	g_KEYS_TABLE[15] = "KEY_TAB";
	g_KEYS_TABLE[16] = "KEY_Q";
	g_KEYS_TABLE[17] = "KEY_W";
	g_KEYS_TABLE[18] = "KEY_E";
	g_KEYS_TABLE[19] = "KEY_R";
	g_KEYS_TABLE[20] = "KEY_T";
	g_KEYS_TABLE[21] = "KEY_Y";
	g_KEYS_TABLE[22] = "KEY_U";
	g_KEYS_TABLE[23] = "KEY_I";
	g_KEYS_TABLE[24] = "KEY_O";
	g_KEYS_TABLE[25] = "KEY_P";
	g_KEYS_TABLE[26] = "KEY_LEFTBRACE";
	g_KEYS_TABLE[27] = "KEY_RIGHTBRACE";
	g_KEYS_TABLE[28] = "KEY_RETURN";
	g_KEYS_TABLE[29] = "KEY_LEFTCTRL";
	g_KEYS_TABLE[30] = "KEY_A";
	g_KEYS_TABLE[31] = "KEY_S";
	g_KEYS_TABLE[32] = "KEY_D";
	g_KEYS_TABLE[33] = "KEY_F";
	g_KEYS_TABLE[34] = "KEY_G";
	g_KEYS_TABLE[35] = "KEY_H";
	g_KEYS_TABLE[36] = "KEY_J";
	g_KEYS_TABLE[37] = "KEY_K";
	g_KEYS_TABLE[38] = "KEY_L";
	g_KEYS_TABLE[39] = "KEY_SEMICOLON";
	g_KEYS_TABLE[40] = "KEY_AT";
	g_KEYS_TABLE[41] = "KEY_RSINGLEQUOTE";
	g_KEYS_TABLE[42] = "KEY_LEFTSHIFT";
	g_KEYS_TABLE[43] = "KEY_HASH";
	g_KEYS_TABLE[44] = "KEY_Z";
	g_KEYS_TABLE[45] = "KEY_X";
	g_KEYS_TABLE[46] = "KEY_C";
	g_KEYS_TABLE[47] = "KEY_V";
	g_KEYS_TABLE[48] = "KEY_B";
	g_KEYS_TABLE[49] = "KEY_N";
	g_KEYS_TABLE[50] = "KEY_M";
	g_KEYS_TABLE[51] = "KEY_LEFTARROW";
	g_KEYS_TABLE[52] = "KEY_RIGHTARROW";
	g_KEYS_TABLE[53] = "KEY_QUESTIONMARK";
	g_KEYS_TABLE[54] = "KEY_RIGHTSHIFT";
	g_KEYS_TABLE[55] = "KEYPAD_ASTERISK";
	g_KEYS_TABLE[56] = "KEY_ALT";
	g_KEYS_TABLE[57] = "KEY_SPACE";
	g_KEYS_TABLE[58] = "KEY_CAPLOCK";
	g_KEYS_TABLE[59] = "KEY_F1";
	g_KEYS_TABLE[60] = "KEY_F2";
	g_KEYS_TABLE[61] = "KEY_F3";
	g_KEYS_TABLE[62] = "KEY_F4";
	g_KEYS_TABLE[63] = "KEY_F5";
	g_KEYS_TABLE[64] = "KEY_F6";
	g_KEYS_TABLE[65] = "KEY_F7";
	g_KEYS_TABLE[66] = "KEY_F8";
	g_KEYS_TABLE[67] = "KEY_F9";
	g_KEYS_TABLE[68] = "KEY_F10";
	g_KEYS_TABLE[69] = "KEYPAD_NUMLOCK";
	g_KEYS_TABLE[70] = "KEY_SCROLLLOCK";
	g_KEYS_TABLE[71] = "KEYPAD_7";
	g_KEYS_TABLE[72] = "KEYPAD_8";
	g_KEYS_TABLE[73] = "KEYPAD_9";
	g_KEYS_TABLE[74] = "KEYPAD_MINUS";
	g_KEYS_TABLE[75] = "KEYPAD_4";
	g_KEYS_TABLE[76] = "KEYPAD_5";
	g_KEYS_TABLE[77] = "KEYPAD_6";
	g_KEYS_TABLE[78] = "KEYPAD_PLUS";
	g_KEYS_TABLE[79] = "KEYPAD_1";
	g_KEYS_TABLE[80] = "KEYPAD_2";
	g_KEYS_TABLE[81] = "KEYPAD_3";
	g_KEYS_TABLE[82] = "KEYPAD_0";
	g_KEYS_TABLE[83] = "KEYPAD_DELETE";
	g_KEYS_TABLE[86] = "KEY_BACKSLASH";
	g_KEYS_TABLE[87] = "KEY_F11";
	g_KEYS_TABLE[88] = "KEY_F12";
	g_KEYS_TABLE[156] = "KEYPAD_ENTER";
	g_KEYS_TABLE[157] = "KEY_RIGHTCTRL";
	g_KEYS_TABLE[181] = "KEYPAD_FORWARDSLASH";
	g_KEYS_TABLE[183] = "KEY_PRINTSCREEN";
	g_KEYS_TABLE[184] = "KEY_ALTGR";
	g_KEYS_TABLE[199] = "KEY_HOME";
	g_KEYS_TABLE[200] = "KEY_CURSORUP";
	g_KEYS_TABLE[201] = "KEY_PGUP";
	g_KEYS_TABLE[203] = "KEY_CURSORLEFT";
	g_KEYS_TABLE[205] = "KEY_CURSORRIGHT";
	g_KEYS_TABLE[207] = "KEY_END";
	g_KEYS_TABLE[208] = "KEY_CURSORDOWN";
	g_KEYS_TABLE[209] = "KEY_PGDN";
	g_KEYS_TABLE[210] = "KEY_INSERT";
	g_KEYS_TABLE[211] = "KEY_DELETE";
}

#pragma endregion


#pragma region PTL Messages

// <LegoRR.exe @00500190>
static const char* g_Messages_TABLE[65];

// entire function just initializes this array
// <LegoRR.exe @00451f90>
void InitMessages(void) {
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

#pragma endregion


#pragma region Activities

// <LegoRR.exe @004dfcc4>
static const char* g_Activities_TABLE[79];

// <LegoRR.exe -> inside function @00436ee0>
void InitActivities(void) {
	g_Activities_TABLE[0] = "Activity_Stand";
	g_Activities_TABLE[1] = "Activity_Route";
	g_Activities_TABLE[2] = "Activity_RouteRubble";
	g_Activities_TABLE[3] = "Activity_RunPanic";
	g_Activities_TABLE[4] = "Activity_Drill";
	g_Activities_TABLE[5] = "Activity_Teleport";
	g_Activities_TABLE[6] = "Activity_Walk";
	g_Activities_TABLE[7] = "Activity_Reinforce";
	g_Activities_TABLE[8] = "Activity_Reverse";
	g_Activities_TABLE[9] = "Activity_TurnLeft";
	g_Activities_TABLE[10] = "Activity_TurnRight";
	g_Activities_TABLE[11] = "Activity_CantDo";
	g_Activities_TABLE[12] = "Activity_Emerge";
	g_Activities_TABLE[13] = "Activity_Enter";
	g_Activities_TABLE[14] = "Activity_EnterRein";
	g_Activities_TABLE[15] = "Activity_Collect";
	g_Activities_TABLE[16] = "Activity_Gather";
	g_Activities_TABLE[17] = "Activity_Carry";
	g_Activities_TABLE[18] = "Activity_CarryRubble";
	g_Activities_TABLE[19] = "Activity_Throw";
	g_Activities_TABLE[20] = "Activity_CarryTurnLeft";
	g_Activities_TABLE[21] = "Activity_CarryTurnRight";
	g_Activities_TABLE[22] = "Activity_CarryStand";
	g_Activities_TABLE[23] = "Activity_HitLeft";
	g_Activities_TABLE[24] = "Activity_HitRight";
	g_Activities_TABLE[25] = "Activity_HitFront";
	g_Activities_TABLE[26] = "Activity_HitBack";
	g_Activities_TABLE[27] = "Activity_HitHard";
	g_Activities_TABLE[28] = "Activity_Dynamite";
	g_Activities_TABLE[29] = "Activity_Deposit";
	g_Activities_TABLE[30] = "Activity_Clear";
	g_Activities_TABLE[31] = "Activity_Place";
	g_Activities_TABLE[32] = "Activity_Repair";
	g_Activities_TABLE[33] = "Activity_Slip";
	g_Activities_TABLE[34] = "Activity_Rest";
	g_Activities_TABLE[35] = "Activity_Eat";
	g_Activities_TABLE[36] = "Activity_Stamp";
	g_Activities_TABLE[37] = "Activity_ThrowMan";
	g_Activities_TABLE[38] = "Activity_ThrownByRockMonster";
	g_Activities_TABLE[39] = "Activity_GetUp";
	g_Activities_TABLE[40] = "Activity_BuildPath";
	g_Activities_TABLE[41] = "Activity_Upgrade";
	g_Activities_TABLE[42] = "Activity_Explode";
	g_Activities_TABLE[43] = "Activity_Unpowered";
	g_Activities_TABLE[44] = "Activity_FireLaser";
	g_Activities_TABLE[45] = "Activity_Freezed";
	g_Activities_TABLE[46] = "Activity_FreezeStart";
	g_Activities_TABLE[47] = "Activity_FreezeMelt";
	g_Activities_TABLE[48] = "Activity_Recharge";
	g_Activities_TABLE[49] = "Activity_WakeUp";
	g_Activities_TABLE[50] = "Activity_Train";
	g_Activities_TABLE[51] = "Activity_FloatOn";
	g_Activities_TABLE[52] = "Activity_FloatOff";
	g_Activities_TABLE[53] = "Activity_Opening";
	g_Activities_TABLE[54] = "Activity_Closing";
	g_Activities_TABLE[55] = "Activity_Open";
	g_Activities_TABLE[56] = "Activity_Waiting1";
	g_Activities_TABLE[57] = "Activity_Waiting2";
	g_Activities_TABLE[58] = "Activity_Waiting3";
	g_Activities_TABLE[59] = "Activity_Waiting4";
	g_Activities_TABLE[60] = "Activity_Waiting5";
	g_Activities_TABLE[61] = "Activity_Waiting6";
	g_Activities_TABLE[62] = "Activity_Waiting7";
	g_Activities_TABLE[63] = "Activity_Waiting8";
	g_Activities_TABLE[64] = "Activity_Waiting9";
	g_Activities_TABLE[65] = "Activity_Waiting10";
	g_Activities_TABLE[66] = "Activity_Waiting11";
	g_Activities_TABLE[67] = "Activity_Waiting12";
	g_Activities_TABLE[68] = "Activity_Waiting13";
	g_Activities_TABLE[69] = "Activity_Waiting14";
	g_Activities_TABLE[70] = "Activity_Waiting15";
	g_Activities_TABLE[71] = "Activity_Waiting16";
	g_Activities_TABLE[72] = "Activity_Waiting17";
	g_Activities_TABLE[73] = "Activity_Waiting18";
	g_Activities_TABLE[74] = "Activity_Waiting19";
	g_Activities_TABLE[75] = "Activity_Waiting20";
	g_Activities_TABLE[76] = "Activity_Waiting21";
	g_Activities_TABLE[77] = "Activity_Crumble";
	g_Activities_TABLE[78] = "Activity_TeleportIn";
}

#pragma endregion


#pragma region AbilityTypes

// <LegoRR.exe @004ebd60>
static const char* g_AbilityTypes_TABLE[6];

// <LegoRR.exe -> inside function @00436ee0>
void InitAbilityTypes(void) {
	g_AbilityTypes_TABLE[0] = "LegoObject_AbilityType_Pilot";
	g_AbilityTypes_TABLE[1] = "LegoObject_AbilityType_Sailor";
	g_AbilityTypes_TABLE[2] = "LegoObject_AbilityType_Driver";
	g_AbilityTypes_TABLE[3] = "LegoObject_AbilityType_Dynamite";
	g_AbilityTypes_TABLE[4] = "LegoObject_AbilityType_Repair";
	g_AbilityTypes_TABLE[5] = "LegoObject_AbilityType_Scanner";
}

#pragma endregion


#pragma region ToolTypes

// <LegoRR.exe @005571fc>
static const char* g_ToolTypes_TABLE[11]; // (confirmed size)

// <LegoRR.exe -> inside function @00436ee0>
void InitToolTypes(void) {
	g_ToolTypes_TABLE[0] = "LegoObject_ToolType_Drill";
	g_ToolTypes_TABLE[1] = "LegoObject_ToolType_Spade";
	g_ToolTypes_TABLE[2] = "LegoObject_ToolType_Hammer";
	g_ToolTypes_TABLE[3] = "LegoObject_ToolType_Spanner";
	g_ToolTypes_TABLE[4] = "LegoObject_ToolType_Laser";
	g_ToolTypes_TABLE[5] = "LegoObject_ToolType_PusherGun";
	g_ToolTypes_TABLE[6] = "LegoObject_ToolType_BirdScarer";
	g_ToolTypes_TABLE[7] = "LegoObject_ToolType_FreezerGun";
}

#pragma endregion


#pragma region Advisors

// <LegoRR.exe @004b3db0>
static const char* g_Advisors_TABLE[21]; // (confirmed size)
// <LegoRR.exe @004b40f8>
static const char* g_AdvisorAnims_TABLE[11]; // (confirmed size)

// <LegoRR.exe -> inside function @00401000>
void InitAdvisors(void) { 
	g_Advisors_TABLE[0] = "Advisor_Objective";
	g_Advisors_TABLE[1] = "Advisor_ObjectiveAcheived";
	g_Advisors_TABLE[2] = "Advisor_ObjectiveFailed";
	g_Advisors_TABLE[3] = "Advisor_IconPoint_Normal";
	g_Advisors_TABLE[4] = "Advisor_IconPoint_BackButton";
	g_Advisors_TABLE[5] = "Advisor_IconPoint_TopButtons";
	g_Advisors_TABLE[6] = "Advisor_PanelPoint_RadarToggle";
	g_Advisors_TABLE[7] = "Advisor_PanelPoint_RadarTaggedObjectView";
	g_Advisors_TABLE[8] = "Advisor_PanelPoint_RadarZoomIn";
	g_Advisors_TABLE[9] = "Advisor_PanelPoint_RadarZoomOut";
	g_Advisors_TABLE[10] = "Advisor_PanelPoint_RadarMapView";
	g_Advisors_TABLE[11] = "Advisor_PanelPoint_InfoDockGoto";
	g_Advisors_TABLE[12] = "Advisor_PanelPoint_InfoDockClose";
	g_Advisors_TABLE[13] = "Advisor_PanelPoint_TopPanelInfo";
	g_Advisors_TABLE[14] = "Advisor_PanelPoint_TopPanelOptions";
	g_Advisors_TABLE[15] = "Advisor_PanelPoint_TopPanelPriorities";
	g_Advisors_TABLE[16] = "Advisor_PanelPoint_TopPanelCallToArms";
	g_Advisors_TABLE[17] = "Advisor_PanelPoint_TopPanelGoBack";
	g_Advisors_TABLE[18] = "Advisor_PanelPoint_ControlZoomIn";
	g_Advisors_TABLE[19] = "Advisor_PanelPoint_ControlZoomOut";
	g_Advisors_TABLE[20] = "Advisor_TalkInGame";

	g_AdvisorAnims_TABLE[0] = "Advisor_Anim_PointToMap";
	g_AdvisorAnims_TABLE[1] = "Advisor_Anim_Point_N";
	g_AdvisorAnims_TABLE[2] = "Advisor_Anim_Point_NE";
	g_AdvisorAnims_TABLE[3] = "Advisor_Anim_Point_E";
	g_AdvisorAnims_TABLE[4] = "Advisor_Anim_Point_SE";
	g_AdvisorAnims_TABLE[5] = "Advisor_Anim_Point_S";
	g_AdvisorAnims_TABLE[6] = "Advisor_Anim_Point_SW";
	g_AdvisorAnims_TABLE[7] = "Advisor_Anim_Point_W";
	g_AdvisorAnims_TABLE[8] = "Advisor_Anim_Point_NW";
	g_AdvisorAnims_TABLE[9] = "Advisor_Anim_Point_Up";
	g_AdvisorAnims_TABLE[10] = "Advisor_Anim_Talk_Top";
}

#pragma endregion


#pragma region AITasks, AI_Priorities, Unknown

// <LegoRR.exe @004b41c8>
static undefined4 g_AITaskValues1_TABLE[12]; // (confirmed size)
// <LegoRR.exe @004b4200>
static const char* g_AITaskTypes_TABLE[31]; // (confirmed size)
// <LegoRR.exe @004b427c>
static const char* g_AIPriorities_TABLE[27]; // (confirmed size)
// <LegoRR.exe @004b42e8>
static unsigned int g_AITaskValues2_TABLE[27]; // (confirmed size)

// <LegoRR.exe -> inside function @00401c30>
void InitAIPriorities(void) {
	for (int i = 0; i < 12; i++)
		g_AITaskValues1_TABLE[i] = 0;

	g_AITaskTypes_TABLE[0] = "AITask_Type_Goto";
	g_AITaskTypes_TABLE[1] = "AITask_Type_Follow";
	g_AITaskTypes_TABLE[2] = "AITask_Type_FollowAttack";
	g_AITaskTypes_TABLE[3] = "AITask_Type_Collect";
	g_AITaskTypes_TABLE[4] = "AITask_Type_Gather";
	g_AITaskTypes_TABLE[12] = "AITask_Type_Clear";
	g_AITaskTypes_TABLE[5] = "AITask_Type_Deposit";
	g_AITaskTypes_TABLE[6] = "AITask_Type_Dump";
	g_AITaskTypes_TABLE[7] = "AITask_Type_Request";
	g_AITaskTypes_TABLE[10] = "AITask_Type_Repair";
	g_AITaskTypes_TABLE[8] = "AITask_Type_Dig";
	g_AITaskTypes_TABLE[9] = "AITask_Type_Dynamite";
	g_AITaskTypes_TABLE[11] = "AITask_Type_Reinforce";
	g_AITaskTypes_TABLE[13] = "AITask_Type_Wait";
	g_AITaskTypes_TABLE[14] = "AITask_Type_AnimationWait";
	g_AITaskTypes_TABLE[15] = "AITask_Type_ElecFence";
	g_AITaskTypes_TABLE[16] = "AITask_Type_Eat";
	g_AITaskTypes_TABLE[17] = "AITask_Type_GotoEat";
	g_AITaskTypes_TABLE[18] = "AITask_Type_FindDriver";
	g_AITaskTypes_TABLE[19] = "AITask_Type_GetTool";
	g_AITaskTypes_TABLE[20] = "AITask_Type_BirdScarer";
	g_AITaskTypes_TABLE[21] = "AITask_Type_Upgrade";
	g_AITaskTypes_TABLE[22] = "AITask_Type_BuildPath";
	g_AITaskTypes_TABLE[23] = "AITask_Type_Train";
	g_AITaskTypes_TABLE[24] = "AITask_Type_Depart";
	g_AITaskTypes_TABLE[25] = "AITask_Type_AttackPath";
	g_AITaskTypes_TABLE[26] = "AITask_Type_AttackRockMonster";
	g_AITaskTypes_TABLE[27] = "AITask_Type_Recharge";
	g_AITaskTypes_TABLE[28] = "AITask_Type_Dock";
	g_AITaskTypes_TABLE[29] = "AITask_Type_AttackObject";
	g_AITaskTypes_TABLE[30] = "AITask_Type_FindLoad";

	g_AIPriorities_TABLE[0] = "AI_Priority_Crystal";
	g_AIPriorities_TABLE[1] = "AI_Priority_Ore";
	g_AIPriorities_TABLE[2] = "AI_Priority_DefaultCollect";
	g_AIPriorities_TABLE[3] = "AI_Priority_Destruction";
	g_AIPriorities_TABLE[4] = "AI_Priority_Construction";
	g_AIPriorities_TABLE[5] = "AI_Priority_Request";
	g_AIPriorities_TABLE[6] = "AI_Priority_Reinforce";
	g_AIPriorities_TABLE[7] = "AI_Priority_Repair";
	g_AIPriorities_TABLE[8] = "AI_Priority_Clearing";
	g_AIPriorities_TABLE[9] = "AI_Priority_Storage";
	g_AIPriorities_TABLE[10] = "AI_Priority_Refining";
	g_AIPriorities_TABLE[11] = "AI_Priority_HealthLow";
	g_AIPriorities_TABLE[12] = "AI_Priority_GetIn";
	g_AIPriorities_TABLE[13] = "AI_Priority_Upgrade";
	g_AIPriorities_TABLE[14] = "AI_Priority_BuildPath";
	g_AIPriorities_TABLE[15] = "AI_Priority_AttackRockMonster";
	g_AIPriorities_TABLE[16] = "AI_Priority_Barrier";
	g_AIPriorities_TABLE[17] = "AI_Priority_FindLoad";
	g_AIPriorities_TABLE[18] = "AI_Priority_Recharge";
	g_AIPriorities_TABLE[19] = "AI_Priority_UpgradeBuilding";
	g_AIPriorities_TABLE[20] = "AI_Priority_Gather";
	g_AIPriorities_TABLE[21] = "AI_Priority_Steal";
	g_AIPriorities_TABLE[22] = "AI_Priority_Punch";
	g_AIPriorities_TABLE[23] = "AI_Priority_Depart";
	g_AIPriorities_TABLE[24] = "AI_Priority_AttackPath";
	g_AIPriorities_TABLE[26] = "AI_Priority_Congregate";
	g_AIPriorities_TABLE[25] = "AI_Priority_AttackObject";

	for (int i = 0; i < 27; i++)
		g_AITaskValues2_TABLE[i] = 0x31;
	
	g_AITaskValues2_TABLE[0] = 0x37;
	g_AITaskValues2_TABLE[3] = 0x28;
	g_AITaskValues2_TABLE[4] = 0x3c;
	g_AITaskValues2_TABLE[5] = 0x14;
	g_AITaskValues2_TABLE[6] = 0x46;
	g_AITaskValues2_TABLE[8] = 0x14;
	g_AITaskValues2_TABLE[9] = 0x5;
	g_AITaskValues2_TABLE[10] = 0xf;
	g_AITaskValues2_TABLE[15] = 0x38;
	g_AITaskValues2_TABLE[19] = 0x63; //99;
	g_AITaskValues2_TABLE[20] = 0x31;
	g_AITaskValues2_TABLE[21] = 0x5a;
	g_AITaskValues2_TABLE[22] = 0x31;
	g_AITaskValues2_TABLE[23] = 0x0;
	g_AITaskValues2_TABLE[24] = 0x14;
	g_AITaskValues2_TABLE[25] = 0x1e;
	g_AITaskValues2_TABLE[26] = 0x63; //99; // max value may be 99 (for a size of 100 in whatever is being referenced)
}

#pragma endregion


#pragma region Bubbles

// <LegoRR.exe @00558900>
static const char* g_Bubbles_TABLE[39]; // (confirmed size)

// entire function just initializes this array
// <LegoRR.exe @00406fe0>
void InitBubbles(void) {
	g_Bubbles_TABLE[0] = "Bubble_CantDo";
	g_Bubbles_TABLE[1] = "Bubble_Idle";
	g_Bubbles_TABLE[2] = "Bubble_CollectCrystal";
	g_Bubbles_TABLE[3] = "Bubble_CollectOre";
	g_Bubbles_TABLE[4] = "Bubble_CollectStud";
	g_Bubbles_TABLE[5] = "Bubble_CollectDynamite";
	g_Bubbles_TABLE[6] = "Bubble_CollectBarrier";
	g_Bubbles_TABLE[7] = "Bubble_CollectElecFence";
	g_Bubbles_TABLE[8] = "Bubble_CollectDrill";
	g_Bubbles_TABLE[9] = "Bubble_CollectSpade";
	g_Bubbles_TABLE[10] = "Bubble_CollectHammer";
	g_Bubbles_TABLE[11] = "Bubble_CollectSpanner";
	g_Bubbles_TABLE[12] = "Bubble_CollectLaser";
	g_Bubbles_TABLE[13] = "Bubble_CollectPusher";
	g_Bubbles_TABLE[14] = "Bubble_CollectFreezer";
	g_Bubbles_TABLE[15] = "Bubble_CollectBirdScarer";
	g_Bubbles_TABLE[16] = "Bubble_CarryCrystal";
	g_Bubbles_TABLE[17] = "Bubble_CarryOre";
	g_Bubbles_TABLE[18] = "Bubble_CarryStud";
	g_Bubbles_TABLE[19] = "Bubble_CarryDynamite";
	g_Bubbles_TABLE[20] = "Bubble_CarryBarrier";
	g_Bubbles_TABLE[21] = "Bubble_CarryElecFence";
	g_Bubbles_TABLE[22] = "Bubble_Goto";
	g_Bubbles_TABLE[23] = "Bubble_Dynamite";
	g_Bubbles_TABLE[24] = "Bubble_Reinforce";
	g_Bubbles_TABLE[25] = "Bubble_Drill";
	g_Bubbles_TABLE[26] = "Bubble_Repair";
	g_Bubbles_TABLE[27] = "Bubble_Dig";
	g_Bubbles_TABLE[28] = "Bubble_Flee";
	g_Bubbles_TABLE[29] = "Bubble_PowerOff";
	g_Bubbles_TABLE[30] = "Bubble_CallToArms";
	g_Bubbles_TABLE[31] = "Bubble_ElecFence";
	g_Bubbles_TABLE[32] = "Bubble_Eat";
	g_Bubbles_TABLE[33] = "Bubble_Drive";
	g_Bubbles_TABLE[34] = "Bubble_Upgrade";
	g_Bubbles_TABLE[35] = "Bubble_BuildPath";
	g_Bubbles_TABLE[36] = "Bubble_Train";
	g_Bubbles_TABLE[37] = "Bubble_Recharge";
	g_Bubbles_TABLE[38] = "Bubble_Request";
}

#pragma endregion


#pragma region Texts

// <LegoRR.exe @00504190>
static const char* g_Texts_TABLE[26]; // (confirmed size)

// <LegoRR.exe -> inside function @0046aab0>
void InitTexts(void) {                       
	g_Texts_TABLE[0] = "Text_Walk";
	g_Texts_TABLE[1] = "Text_Drill";
	g_Texts_TABLE[2] = "Text_NoDrill";
	g_Texts_TABLE[3] = "Text_CantDrill";
	g_Texts_TABLE[4] = "Text_Reinforce";
	g_Texts_TABLE[5] = "Text_NoReinforce";
	g_Texts_TABLE[6] = "Text_CantReinforce";
	g_Texts_TABLE[7] = "Text_PickupCrystal";
	g_Texts_TABLE[8] = "Text_Encyclopedia";
	g_Texts_TABLE[9] = "Text_RadarHelp";
	g_Texts_TABLE[10] = "Text_BuildHelp";
	g_Texts_TABLE[11] = "Text_SelectionHelp";
	g_Texts_TABLE[12] = "Text_Drive";
	g_Texts_TABLE[13] = "Text_CantDrive";
	g_Texts_TABLE[14] = "Text_MakeTeleporter";
	g_Texts_TABLE[15] = "Text_CannotPlaceBuilding";
	g_Texts_TABLE[16] = "Text_CrystalOreDisabled";
	g_Texts_TABLE[17] = "Text_CrystalFound";
	g_Texts_TABLE[18] = "Text_CavernDiscovered";
	g_Texts_TABLE[19] = "Text_OreFound";
	g_Texts_TABLE[20] = "Text_AirSupplyLow";
	g_Texts_TABLE[21] = "Text_AirSupplyRunningOut";
	g_Texts_TABLE[22] = "Text_SpaceToContinue";
	g_Texts_TABLE[23] = "Text_GameCompleted";
	g_Texts_TABLE[24] = "Text_ManTrained";
	g_Texts_TABLE[25] = "Text_UnitUpgraded";
}

#pragma endregion


#pragma region Infos

// <LegoRR.exe @004dd658>
static const char* g_Infos_TABLE[40];

// <LegoRR.exe -> inside function @00419160>
void InitInfos(void) {
	g_Infos_TABLE[0] = "Info_CrystalFound";
	g_Infos_TABLE[1] = "Info_OreSeamFound";
	g_Infos_TABLE[2] = "Info_RockMonster";
	g_Infos_TABLE[3] = "Info_LavaRockMonster";
	g_Infos_TABLE[4] = "Info_IceRockMonster";
	g_Infos_TABLE[5] = "Info_UnderAttack";
	g_Infos_TABLE[6] = "Info_Landslide";
	g_Infos_TABLE[7] = "Info_CaveIn";
	g_Infos_TABLE[8] = "Info_Constructed";
	g_Infos_TABLE[9] = "Info_CavernLocated";
	g_Infos_TABLE[10] = "Info_LegoManDeath";
	g_Infos_TABLE[11] = "Info_VehicleDeath";
	g_Infos_TABLE[12] = "Info_BuildingDeath";
	g_Infos_TABLE[13] = "Info_DynamitePlaced";
	g_Infos_TABLE[14] = "Info_NoPower";
	g_Infos_TABLE[15] = "Info_PowerDrain";
	g_Infos_TABLE[16] = "Info_AirDepleting";
	g_Infos_TABLE[17] = "Info_AirLow";
	g_Infos_TABLE[18] = "Info_AirOut";
	g_Infos_TABLE[19] = "Info_AirRestored";
	g_Infos_TABLE[20] = "Info_TrainDriver";
	g_Infos_TABLE[21] = "Info_TrainDynamite";
	g_Infos_TABLE[22] = "Info_TrainRepair";
	g_Infos_TABLE[23] = "Info_TrainPilot";
	g_Infos_TABLE[24] = "Info_TrainSailor";
	g_Infos_TABLE[25] = "Info_TrainScanner";
	g_Infos_TABLE[26] = "Info_OreCollected";
	g_Infos_TABLE[27] = "Info_WallDug";
	g_Infos_TABLE[28] = "Info_WallReinforced";
	g_Infos_TABLE[29] = "Info_CrystalPower";
	g_Infos_TABLE[30] = "Info_LavaErode";
	g_Infos_TABLE[31] = "Info_SlugEmerge";
	g_Infos_TABLE[32] = "Info_PathCompleted";
	g_Infos_TABLE[33] = "Info_FoundMinifigure";
	g_Infos_TABLE[34] = "Info_CanUpgradeMinifigure";
	g_Infos_TABLE[35] = "Info_CanTrainMinifigure";
	g_Infos_TABLE[36] = "Info_CrystalSeamFound";
	g_Infos_TABLE[37] = "Info_GenericSeamFound";
	g_Infos_TABLE[38] = "Info_GenericDeath";
	g_Infos_TABLE[39] = "Info_GenericMonster";
}

#pragma endregion
