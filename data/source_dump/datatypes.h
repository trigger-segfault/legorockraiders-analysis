#pragma once
//#include "functypes.h"



typedef void* addr;
typedef G98CAnimation Animation_t;
typedef uint32 ddw;
typedef uint32 LegoObject_ID;
typedef Main_StateChangeData Mesh_TextureStateChangeData;
typedef G98CMovie Movie_t;


enum Activity_Type : sint32 // [LegoRR/LegoObject.c|enum:0x4|type:int]
{
	Activity_Stand               = 0,
	Activity_Route               = 1,
	Activity_RouteRubble         = 2,
	Activity_RunPanic            = 3,
	Activity_Drill               = 4,
	Activity_Teleport            = 5,
	Activity_Walk                = 6,
	Activity_Reinforce           = 7,
	Activity_Reverse             = 8,
	Activity_TurnLeft            = 9,
	Activity_TurnRight           = 10,
	Activity_CantDo              = 11,
	Activity_Emerge              = 12,
	Activity_Enter               = 13,
	Activity_EnterRein           = 14,
	Activity_Collect             = 15,
	Activity_Gather              = 16,
	Activity_Carry               = 17,
	Activity_CarryRubble         = 18,
	Activity_Throw               = 19,
	Activity_CarryTurnLeft       = 20,
	Activity_CarryTurnRight      = 21,
	Activity_CarryStand          = 22,
	Activity_HitLeft             = 23,
	Activity_HitRight            = 24,
	Activity_HitFront            = 25,
	Activity_HitBack             = 26,
	Activity_HitHard             = 27,
	Activity_Dynamite            = 28,
	Activity_Deposit             = 29,
	Activity_Clear               = 30,
	Activity_Place               = 31,
	Activity_Repair              = 32,
	Activity_Slip                = 33,
	Activity_Rest                = 34,
	Activity_Eat                 = 35,
	Activity_Stamp               = 36,
	Activity_ThrowMan            = 37,
	Activity_ThrownByRockMonster = 38,
	Activity_GetUp               = 39,
	Activity_BuildPath           = 40,
	Activity_Upgrade             = 41,
	Activity_Explode             = 42,
	Activity_Unpowered           = 43,
	Activity_FireLaser           = 44,
	Activity_Freezed             = 45,
	Activity_FreezeStart         = 46,
	Activity_FreezeMelt          = 47,
	Activity_Recharge            = 48,
	Activity_WakeUp              = 49,
	Activity_Train               = 50,
	Activity_FloatOn             = 51,
	Activity_FloatOff            = 52,
	Activity_Opening             = 53,
	Activity_Closing             = 54,
	Activity_Open                = 55,
	Activity_Waiting1            = 56,
	Activity_Waiting2            = 57,
	Activity_Waiting3            = 58,
	Activity_Waiting4            = 59,
	Activity_Waiting5            = 60,
	Activity_Waiting6            = 61,
	Activity_Waiting7            = 62,
	Activity_Waiting8            = 63,
	Activity_Waiting9            = 64,
	Activity_Waiting10           = 65,
	Activity_Waiting11           = 66,
	Activity_Waiting12           = 67,
	Activity_Waiting13           = 68,
	Activity_Waiting14           = 69,
	Activity_Waiting15           = 70,
	Activity_Waiting16           = 71,
	Activity_Waiting17           = 72,
	Activity_Waiting18           = 73,
	Activity_Waiting19           = 74,
	Activity_Waiting20           = 75,
	Activity_Waiting21           = 76,
	Activity_Crumble             = 77,
	Activity_TeleportIn          = 78,
	Activity_Type_Count          = 79,
};
assert_sizeof(Activity_Type, 0x4);

enum Advisor_Anim : sint32 // [LegoRR/Advisor.c|enum:0x4|type:int]
{
	Advisor_Anim_PointToMap = 0,
	Advisor_Anim_Point_N    = 1,
	Advisor_Anim_Point_NE   = 2,
	Advisor_Anim_Point_E    = 3,
	Advisor_Anim_Point_SE   = 4,
	Advisor_Anim_Point_S    = 5,
	Advisor_Anim_Point_SW   = 6,
	Advisor_Anim_Point_W    = 7,
	Advisor_Anim_Point_NW   = 8,
	Advisor_Anim_Point_Up   = 9,
	Advisor_Anim_Talk_Top   = 10,
	Advisor_Anim_Count      = 11,
};
assert_sizeof(Advisor_Anim, 0x4);

enum Advisor_Type : sint32 // [LegoRR/Advisor.c|enum:0x4|type:int] "Acheived" is a source-accurate, but misspelled name
{
	Advisor_Objective                        = 0,
	Advisor_ObjectiveAcheived                = 1,
	Advisor_ObjectiveAchieved                = 1,
	Advisor_ObjectiveFailed                  = 2,
	Advisor_IconPoint_Normal                 = 3,
	Advisor_IconPoint_BackButton             = 4,
	Advisor_IconPoint_TopButtons             = 5,
	Advisor_PanelPoint_RadarToggle           = 6,
	Advisor_PanelPoint_RadarTaggedObjectView = 7,
	Advisor_PanelPoint_RadarZoomIn           = 8,
	Advisor_PanelPoint_RadarZoomOut          = 9,
	Advisor_PanelPoint_RadarMapView          = 10,
	Advisor_PanelPoint_InfoDockGoto          = 11,
	Advisor_PanelPoint_InfoDockClose         = 12,
	Advisor_PanelPoint_TopPanelInfo          = 13,
	Advisor_PanelPoint_TopPanelOptions       = 14,
	Advisor_PanelPoint_TopPanelPriorities    = 15,
	Advisor_PanelPoint_TopPanelCallToArms    = 16,
	Advisor_PanelPoint_TopPanelGoBack        = 17,
	Advisor_PanelPoint_ControlZoomIn         = 18,
	Advisor_PanelPoint_ControlZoomOut        = 19,
	Advisor_TalkInGame                       = 20,
	Advisor_Type_Count                       = 21,
};
assert_sizeof(Advisor_Type, 0x4);

enum AI_Priority : sint32 // [LegoRR/AITask.c|enum:0x4|type:int]
{
	AI_Priority_Crystal           = 0,
	AI_Priority_Ore               = 1,
	AI_Priority_DefaultCollect    = 2,
	AI_Priority_Destruction       = 3,
	AI_Priority_Construction      = 4,
	AI_Priority_Request           = 5,
	AI_Priority_Reinforce         = 6,
	AI_Priority_Repair            = 7,
	AI_Priority_Clearing          = 8,
	AI_Priority_Storage           = 9,
	AI_Priority_Refining          = 10,
	AI_Priority_HealthLow         = 11,
	AI_Priority_GetIn             = 12,
	AI_Priority_Upgrade           = 13,
	AI_Priority_BuildPath         = 14,
	AI_Priority_AttackRockMonster = 15,
	AI_Priority_Barrier           = 16,
	AI_Priority_FindLoad          = 17,
	AI_Priority_Recharge          = 18,
	AI_Priority_UpgradeBuilding   = 19,
	AI_Priority_Gather            = 20,
	AI_Priority_Steal             = 21,
	AI_Priority_Punch             = 22,
	AI_Priority_Depart            = 23,
	AI_Priority_AttackPath        = 24,
	AI_Priority_AttackObject      = 25,
	AI_Priority_Congregate        = 26,
	AI_Priority_Count             = 27,
};
assert_sizeof(AI_Priority, 0x4);

enum AITask_Type : sint32 // [LegoRR/AITask.c|enum:0x4|type:int]
{
	AITask_Type_Goto              = 0,
	AITask_Type_Follow            = 1,
	AITask_Type_FollowAttack      = 2,
	AITask_Type_Collect           = 3,
	AITask_Type_Gather            = 4,
	AITask_Type_Deposit           = 5,
	AITask_Type_Dump              = 6,
	AITask_Type_Request           = 7,
	AITask_Type_Dig               = 8,
	AITask_Type_Dynamite          = 9,
	AITask_Type_Repair            = 10,
	AITask_Type_Reinforce         = 11,
	AITask_Type_Clear             = 12,
	AITask_Type_Wait              = 13,
	AITask_Type_AnimationWait     = 14,
	AITask_Type_ElecFence         = 15,
	AITask_Type_Eat               = 16,
	AITask_Type_GotoEat           = 17,
	AITask_Type_FindDriver        = 18,
	AITask_Type_GetTool           = 19,
	AITask_Type_BirdScarer        = 20,
	AITask_Type_Upgrade           = 21,
	AITask_Type_BuildPath         = 22,
	AITask_Type_Train             = 23,
	AITask_Type_Depart            = 24,
	AITask_Type_AttackPath        = 25,
	AITask_Type_AttackRockMonster = 26,
	AITask_Type_Recharge          = 27,
	AITask_Type_Dock              = 28,
	AITask_Type_AttackObject      = 29,
	AITask_Type_FindLoad          = 30,
	AITask_Type_Count             = 31,
};
assert_sizeof(AITask_Type, 0x4);

enum BlockOrientation : uint8 // [LegoRR/dummy.c|enum:0x1|type:byte|tags:UNFINISHED]
{
	BLOCKORIENTATION_CORNER = 2,
	BLOCKORIENTATION_OBTUSE = 3,
};
assert_sizeof(BlockOrientation, 0x1);

enum BoolTri : uint32 // [common.c|enum:0x4|type:uint] BoolTri, A 3-state boolean for True, False, or Error
{
	BOOL3_FALSE = 0,
	BOOL3_TRUE  = 1,
	BOOL3_ERROR = 2,
};
assert_sizeof(BoolTri, 0x4);

enum Bubble_Type : sint32 // [LegoRR/Bubble.c|enum:0x4|type:int]
{
	Bubble_CantDo            = 0,
	Bubble_Idle              = 1,
	Bubble_CollectCrystal    = 2,
	Bubble_CollectOre        = 3,
	Bubble_CollectStud       = 4,
	Bubble_CollectDynamite   = 5,
	Bubble_CollectBarrier    = 6,
	Bubble_CollectElecFence  = 7,
	Bubble_CollectDrill      = 8,
	Bubble_CollectSpade      = 9,
	Bubble_CollectHammer     = 10,
	Bubble_CollectSpanner    = 11,
	Bubble_CollectLaser      = 12,
	Bubble_CollectPusher     = 13,
	Bubble_CollectFreezer    = 14,
	Bubble_CollectBirdScarer = 15,
	Bubble_CarryCrystal      = 16,
	Bubble_CarryOre          = 17,
	Bubble_CarryStud         = 18,
	Bubble_CarryDynamite     = 19,
	Bubble_CarryBarrier      = 20,
	Bubble_CarryElecFence    = 21,
	Bubble_Goto              = 22,
	Bubble_Dynamite          = 23,
	Bubble_Reinforce         = 24,
	Bubble_Drill             = 25,
	Bubble_Repair            = 26,
	Bubble_Dig               = 27,
	Bubble_Flee              = 28,
	Bubble_PowerOff          = 29,
	Bubble_CallToArms        = 30,
	Bubble_ElecFence         = 31,
	Bubble_Eat               = 32,
	Bubble_Drive             = 33,
	Bubble_Upgrade           = 34,
	Bubble_BuildPath         = 35,
	Bubble_Train             = 36,
	Bubble_Recharge          = 37,
	Bubble_Request           = 38,
	Bubble_Type_Count        = 39,
};
assert_sizeof(Bubble_Type, 0x4);

enum Container_Combine : uint32 // [Gods98/Containers.c|enum:0x4|type:uint]
{
	Container_Combine_Replace = 0,
	Container_Combine_Before  = 1,
	Container_Combine_After   = 2,
};
assert_sizeof(Container_Combine, 0x4);

enum Container_FogMode : uint32 // [Gods98/Containers.c|enum:0x4|type:uint]
{
	Container_FogMode_None               = 0,
	Container_FogMode_Exponential        = 1,
	Container_FogMode_ExponentialSquared = 2,
	Container_FogMode_Linear             = 3,
};
assert_sizeof(Container_FogMode, 0x4);

enum Container_Light : uint32 // [Gods98/Containers.c|enum:0x4|type:uint]
{
	Container_Light_Ambient       = 0,
	Container_Light_Point         = 1,
	Container_Light_Spot          = 2,
	Container_Light_Directional   = 3,
	Container_Light_ParallelPoint = 4,
};
assert_sizeof(Container_Light, 0x4);

enum Container_MeshType : uint32 // [Gods98/Containers.c|enum:0x4|type:uint]
{
	Container_MeshType_Normal         = 0,
	Container_MeshType_SeperateMeshes = 1,
	Container_MeshType_Immediate      = 2,
	Container_MeshType_Transparent    = 3,
	Container_MeshType_Additive       = 4,
	Container_MeshType_Subtractive    = 5,
};
assert_sizeof(Container_MeshType, 0x4);

enum Container_Quality : uint32 // [Gods98/Containers.c|enum:0x4|type:uint]
{
	Container_Quality_Wireframe = 0,
	Container_Quality_UnlitFlat = 1,
	Container_Quality_Flat      = 2,
	Container_Quality_Gouraud   = 3,
	Container_Quality_Phong     = 4,
};
assert_sizeof(Container_Quality, 0x4);

enum Container_SearchMode : uint32 // [Gods98/Containers.c|enum:0x4|type:uint]
{
	Container_SearchMode_FirstMatch = 0,
	Container_SearchMode_MatchCount = 1,
	Container_SearchMode_NthMatch   = 2,
};
assert_sizeof(Container_SearchMode, 0x4);

enum Container_Type : sint32 // [Gods98/Containers.c|enum:0x4|type:int]
{
	Container_Type_Null         = 0,
	Container_Type_Mesh         = 1,
	Container_Type_Frame        = 2,
	Container_Type_Anim         = 3,
	Container_Type_FromActivity = 4,
	Container_Type_Light        = 5,
	Container_Type_Reference    = 6,
	Container_Type_LWS          = 7,
	Container_Type_LWO          = 8,
	Container_Type_Count        = 9,
	Container_Type_Invalid      = -1,
};
assert_sizeof(Container_Type, 0x4);

enum Direction : sint32 // [common.c|enum:0x4|type:int]
{
	DIRECTION_UP     = 0,
	DIRECTION_RIGHT  = 1,
	DIRECTION_DOWN   = 2,
	DIRECTION_LEFT   = 3,
	DIRECTION__COUNT = 4,
};
assert_sizeof(Direction, 0x4);

enum DrawEffect : uint32 // [Gods98/Draw.c|enum:0x4|type:uint]
{
	DrawEffect_None      = 0,
	DrawEffect_XOR       = 1,
	DrawEffect_HalfTrans = 2,
};
assert_sizeof(DrawEffect, 0x4);

enum FileSys : sint32 // [Gods98/Files.c|enum:0x4|type:int] Location of a lego File stream (WAD or REAL)
{
	FileSys_Wad      = 0,
	FileSys_Standard = 1,
	FileSys_Error    = 2,
};
assert_sizeof(FileSys, 0x4);

enum FlicDisplayMode : uint32 // [Gods98/Flic.c|enum:0x4|type:uint]
{
	FLICMODE_BYTEPERPIXEL = 0,
	FLICMODE_MODEX        = 1,
	FLICMODE_PLANAR       = 2,
	FLICMODE_TRUECOLOR    = 3,
	FLICMODE_HICOLOR      = 4,
};
assert_sizeof(FlicDisplayMode, 0x4);

enum FlicError : sint32 // [Gods98/Flic.c|enum:0x4|type:int]
{
	FLICNOERROR            = 0,
	FLICFINISHED           = 1,
	FLICINVALIDHANDLE      = 3000,
	FLICNOMOREHANDLES      = 3001,
	FLICNOTENOUGHMEMORY    = 3002,
	FLICINVALIDFILE        = 3003,
	FLICFILENOTFOUND       = 3004,
	FLICFILEERROR          = 3005,
	FLICOFFPORTAL          = 3006,
	FLICFRAMEDOESNOTEXIST  = 3007,
	FLICREPLAYNOTSUPPORTED = 3008,
	FLICNOMOREFRAMES       = 3009,
	FLICSOUNDHEADERERROR   = 3010,
	FLICERROR              = -1,
};
assert_sizeof(FlicError, 0x4);

enum Graphics_Quality : uint32 // [Gods98/Main.c|enum:0x4|type:uint] Phong is unused.
{
	Wireframe = 0,
	UnlitFlat = 1,
	Flat      = 2,
	Gouraud   = 3,
	Phong     = 4,
};
assert_sizeof(Graphics_Quality, 0x4);

enum Image_TextureMode : uint32 // [Gods98/Images.c|enum:0x4|type:uint]
{
	Image_TextureMode_Normal            = 0,
	Image_TextureMode_Subtractive       = 1,
	Image_TextureMode_Additive          = 2,
	Image_TextureMode_Transparent       = 3,
	Image_TextureMode_Fixed_Subtractive = 4,
	Image_TextureMode_Fixed_Additive    = 5,
	Image_TextureMode_Fixed_Transparent = 6,
	Image_TextureMode_Count             = 7,
};
assert_sizeof(Image_TextureMode, 0x4);

enum Info_Type : sint32 // [LegoRR/Info.c|enum:0x4|type:int]
{
	Info_CrystalFound         = 0,
	Info_OreSeamFound         = 1,
	Info_RockMonster          = 2,
	Info_LavaRockMonster      = 3,
	Info_IceRockMonster       = 4,
	Info_UnderAttack          = 5,
	Info_Landslide            = 6,
	Info_CaveIn               = 7,
	Info_Constructed          = 8,
	Info_CavernLocated        = 9,
	Info_LegoManDeath         = 10,
	Info_VehicleDeath         = 11,
	Info_BuildingDeath        = 12,
	Info_DynamitePlaced       = 13,
	Info_NoPower              = 14,
	Info_PowerDrain           = 15,
	Info_AirDepleting         = 16,
	Info_AirLow               = 17,
	Info_AirOut               = 18,
	Info_AirRestored          = 19,
	Info_TrainDriver          = 20,
	Info_TrainDynamite        = 21,
	Info_TrainRepair          = 22,
	Info_TrainPilot           = 23,
	Info_TrainSailor          = 24,
	Info_TrainScanner         = 25,
	Info_OreCollected         = 26,
	Info_WallDug              = 27,
	Info_WallReinforced       = 28,
	Info_CrystalPower         = 29,
	Info_LavaErode            = 30,
	Info_SlugEmerge           = 31,
	Info_PathCompleted        = 32,
	Info_FoundMinifigure      = 33,
	Info_CanUpgradeMinifigure = 34,
	Info_CanTrainMinifigure   = 35,
	Info_CrystalSeamFound     = 36,
	Info_GenericSeamFound     = 37,
	Info_GenericDeath         = 38,
	Info_GenericMonster       = 39,
	Info_Type_Count           = 40,
};
assert_sizeof(Info_Type, 0x4);

enum Interface_MenuItemType : sint32 // [LegoRR/Interface.c|enum:0x4|type:int] "Back" has no official name
{
	Interface_MenuItem_Back                  = 0,
	Interface_MenuItem_TeleportMan           = 1,
	Interface_MenuItem_BuildBuilding         = 2,
	Interface_MenuItem_BuildSmallVehicle     = 3,
	Interface_MenuItem_BuildLargeVehicle     = 4,
	Interface_MenuItem_LayPath               = 5,
	Interface_MenuItem_RemovePath            = 6,
	Interface_MenuItem_RepairLava            = 7,
	Interface_MenuItem_GeologistTest         = 8,
	Interface_MenuItem_ClearRubble           = 9,
	Interface_MenuItem_Dam                   = 10,
	Interface_MenuItem_Dig                   = 11,
	Interface_MenuItem_Reinforce             = 12,
	Interface_MenuItem_Dynamite              = 13,
	Interface_MenuItem_PlaceFence            = 14,
	Interface_MenuItem_DeselectDig           = 15,
	Interface_MenuItem_CancelConstruction    = 16,
	Interface_MenuItem_SelectMan             = 17,
	Interface_MenuItem_SelectVehicle         = 18,
	Interface_MenuItem_SelectBuilding        = 19,
	Interface_MenuItem_VehiclePickUp         = 20,
	Interface_MenuItem_MinifigurePickUp      = 21,
	Interface_MenuItem_UnLoadVehicle         = 22,
	Interface_MenuItem_UnLoadMinifigure      = 23,
	Interface_MenuItem_GetIn                 = 24,
	Interface_MenuItem_GetOut                = 25,
	Interface_MenuItem_GotoDock              = 26,
	Interface_MenuItem_LegoManGoto           = 27,
	Interface_MenuItem_VehicleGoto           = 28,
	Interface_MenuItem_VehicleDig            = 29,
	Interface_MenuItem_LegoManDig            = 30,
	Interface_MenuItem_GoFeed                = 31,
	Interface_MenuItem_DeleteMan             = 32,
	Interface_MenuItem_DropBirdScarer        = 33,
	Interface_MenuItem_PowerOn               = 34,
	Interface_MenuItem_PowerOff              = 35,
	Interface_MenuItem_Repair                = 36,
	Interface_MenuItem_MakeTeleporterPrimary = 37,
	Interface_MenuItem_EjectCrystal          = 38,
	Interface_MenuItem_EjectOre              = 39,
	Interface_MenuItem_DeleteBuilding        = 40,
	Interface_MenuItem_DeleteVehicle         = 41,
	Interface_MenuItem_DeleteElectricFence   = 42,
	Interface_MenuItem_Attack                = 43,
	Interface_MenuItem_GotoTopView           = 44,
	Interface_MenuItem_GotoFirstPerson       = 45,
	Interface_MenuItem_GotoSecondPerson      = 46,
	Interface_MenuItem_TrackObject           = 47,
	Interface_MenuItem_GetTool               = 48,
	Interface_MenuItem_GetDrill              = 49,
	Interface_MenuItem_GetSpade              = 50,
	Interface_MenuItem_GetHammer             = 51,
	Interface_MenuItem_GetSpanner            = 52,
	Interface_MenuItem_GetLaser              = 53,
	Interface_MenuItem_GetPusherGun          = 54,
	Interface_MenuItem_GetFreezerGun         = 55,
	Interface_MenuItem_GetBirdScarer         = 56,
	Interface_MenuItem_TrainSkill            = 57,
	Interface_MenuItem_TrainDriver           = 58,
	Interface_MenuItem_TrainEngineer         = 59,
	Interface_MenuItem_TrainGeologist        = 60,
	Interface_MenuItem_TrainPilot            = 61,
	Interface_MenuItem_TrainSailor           = 62,
	Interface_MenuItem_TrainDynamite         = 63,
	Interface_MenuItem_UpgradeMan            = 64,
	Interface_MenuItem_UpgradeBuilding       = 65,
	Interface_MenuItem_UpgradeVehicle        = 66,
	Interface_MenuItem_UpgradeEngine         = 67,
	Interface_MenuItem_UpgardeDrill          = 68,
	Interface_MenuItem_UpgardeScan           = 69,
	Interface_MenuItem_UpgardeCarry          = 70,
	Interface_MenuItem_Encyclopedia          = 71,
	Interface_MenuItem_ClearSelection        = 72,
	Interface_MenuItem_Build                 = 73,
	Interface_MenuItem_Type_Count            = 74,
	Interface_MenuItem_Type_Invalid          = -1,
};
assert_sizeof(Interface_MenuItemType, 0x4);

enum Interface_MenuType : sint32 // [LegoRR/Interface.c|enum:0x4|type:int]
{
	Interface_Menu_Main              = 0,
	Interface_Menu_Ground            = 1,
	Interface_Menu_Erode             = 2,
	Interface_Menu_PlaceFence        = 3,
	Interface_Menu_Construction      = 4,
	Interface_Menu_Rubble            = 5,
	Interface_Menu_UNK_6             = 6,
	Interface_Menu_Wall              = 7,
	Interface_Menu_Tracker           = 8,
	Interface_Menu_LegoMan           = 9,
	Interface_Menu_LandVehicle       = 10,
	Interface_Menu_WaterVehicle      = 11,
	Interface_Menu_UnmannedVehicle   = 12,
	Interface_Menu_Building          = 13,
	Interface_Menu_ElectricFence     = 14,
	Interface_Menu_FP                = 15,
	Interface_Menu_GetTool           = 16,
	Interface_Menu_TrainSkill        = 17,
	Interface_Menu_UpgradeVehicle    = 18,
	Interface_Menu_BuildBuilding     = 19,
	Interface_Menu_BuildSmallVehicle = 20,
	Interface_Menu_BuildLargeVehicle = 21,
	Interface_Menu_Type_Count        = 22,
	Interface_Menu_Encyclopedia      = 23,
};
assert_sizeof(Interface_MenuType, 0x4);

enum Keys32 : sint32 // [Gods98/Input.c|enum:0x4|type:int|tags:HELPER] 32-bit sized Keys enum
{
	KEY__NONE           = 0,
	KEY_ESCAPE          = 1,
	KEY_ONE             = 2,
	KEY_TWO             = 3,
	KEY_THREE           = 4,
	KEY_FOUR            = 5,
	KEY_FIVE            = 6,
	KEY_SIX             = 7,
	KEY_SEVEN           = 8,
	KEY_EIGHT           = 9,
	KEY_NINE            = 10,
	KEY_ZERO            = 11,
	KEY_MINUS           = 12,
	KEY_EQUALS          = 13,
	KEY_BACKSPACE       = 14,
	KEY_TAB             = 15,
	KEY_Q               = 16,
	KEY_W               = 17,
	KEY_E               = 18,
	KEY_R               = 19,
	KEY_T               = 20,
	KEY_Y               = 21,
	KEY_U               = 22,
	KEY_I               = 23,
	KEY_O               = 24,
	KEY_P               = 25,
	KEY_LEFTBRACE       = 26,
	KEY_RIGHTBRACE      = 27,
	KEY_RETURN          = 28,
	KEY_LEFTCTRL        = 29,
	KEY_A               = 30,
	KEY_S               = 31,
	KEY_D               = 32,
	KEY_F               = 33,
	KEY_G               = 34,
	KEY_H               = 35,
	KEY_J               = 36,
	KEY_K               = 37,
	KEY_L               = 38,
	KEY_SEMICOLON       = 39,
	KEY_AT              = 40,
	KEY_RSINGLEQUOTE    = 41,
	KEY_LEFTSHIFT       = 42,
	KEY_HASH            = 43,
	KEY_Z               = 44,
	KEY_X               = 45,
	KEY_C               = 46,
	KEY_V               = 47,
	KEY_B               = 48,
	KEY_N               = 49,
	KEY_M               = 50,
	KEY_LEFTARROW       = 51,
	KEY_RIGHTARROW      = 52,
	KEY_QUESTIONMARK    = 53,
	KEY_RIGHTSHIFT      = 54,
	KEYPAD_ASTERISK     = 55,
	KEY_ALT             = 56,
	KEY_SPACE           = 57,
	KEY_CAPLOCK         = 58,
	KEY_F1              = 59,
	KEY_F2              = 60,
	KEY_F3              = 61,
	KEY_F4              = 62,
	KEY_F5              = 63,
	KEY_F6              = 64,
	KEY_F7              = 65,
	KEY_F8              = 66,
	KEY_F9              = 67,
	KEY_F10             = 68,
	KEYPAD_NUMLOCK      = 69,
	KEY_SCROLLLOCK      = 70,
	KEYPAD_7            = 71,
	KEYPAD_8            = 72,
	KEYPAD_9            = 73,
	KEYPAD_MINUS        = 74,
	KEYPAD_4            = 75,
	KEYPAD_5            = 76,
	KEYPAD_6            = 77,
	KEYPAD_PLUS         = 78,
	KEYPAD_1            = 79,
	KEYPAD_2            = 80,
	KEYPAD_3            = 81,
	KEYPAD_0            = 82,
	KEYPAD_DELETE       = 83,
	KEY_BACKSLASH       = 86,
	KEY_F11             = 87,
	KEY_F12             = 88,
	KEYPAD_ENTER        = 156,
	KEY_RIGHTCTRL       = 157,
	KEYPAD_FORWARDFLASH = 181,
	KEY_PRINTSCREEN     = 183,
	KEY_ALTGR           = 184,
	KEY_HOME            = 199,
	KEY_CURSORUP        = 200,
	KEY_PGUP            = 201,
	KEY_CURSORLEFT      = 203,
	KEY_END             = 207,
	KEY_CURSORDOWN      = 208,
	KEY_PGDN            = 209,
	KEY_INSERT          = 210,
	KEY_DELETE          = 211,
};
assert_sizeof(Keys32, 0x4);

enum Keys8 : uint8 // [Gods98/Input.c|enum:0x1|type:byte] Byte-sized Keys enum
{
	KEY__NONE           = 0,
	KEY_ESCAPE          = 1,
	KEY_ONE             = 2,
	KEY_TWO             = 3,
	KEY_THREE           = 4,
	KEY_FOUR            = 5,
	KEY_FIVE            = 6,
	KEY_SIX             = 7,
	KEY_SEVEN           = 8,
	KEY_EIGHT           = 9,
	KEY_NINE            = 10,
	KEY_ZERO            = 11,
	KEY_MINUS           = 12,
	KEY_EQUALS          = 13,
	KEY_BACKSPACE       = 14,
	KEY_TAB             = 15,
	KEY_Q               = 16,
	KEY_W               = 17,
	KEY_E               = 18,
	KEY_R               = 19,
	KEY_T               = 20,
	KEY_Y               = 21,
	KEY_U               = 22,
	KEY_I               = 23,
	KEY_O               = 24,
	KEY_P               = 25,
	KEY_LEFTBRACE       = 26,
	KEY_RIGHTBRACE      = 27,
	KEY_RETURN          = 28,
	KEY_LEFTCTRL        = 29,
	KEY_A               = 30,
	KEY_S               = 31,
	KEY_D               = 32,
	KEY_F               = 33,
	KEY_G               = 34,
	KEY_H               = 35,
	KEY_J               = 36,
	KEY_K               = 37,
	KEY_L               = 38,
	KEY_SEMICOLON       = 39,
	KEY_AT              = 40,
	KEY_RSINGLEQUOTE    = 41,
	KEY_LEFTSHIFT       = 42,
	KEY_HASH            = 43,
	KEY_Z               = 44,
	KEY_X               = 45,
	KEY_C               = 46,
	KEY_V               = 47,
	KEY_B               = 48,
	KEY_N               = 49,
	KEY_M               = 50,
	KEY_LEFTARROW       = 51,
	KEY_RIGHTARROW      = 52,
	KEY_QUESTIONMARK    = 53,
	KEY_RIGHTSHIFT      = 54,
	KEYPAD_ASTERISK     = 55,
	KEY_ALT             = 56,
	KEY_SPACE           = 57,
	KEY_CAPLOCK         = 58,
	KEY_F1              = 59,
	KEY_F2              = 60,
	KEY_F3              = 61,
	KEY_F4              = 62,
	KEY_F5              = 63,
	KEY_F6              = 64,
	KEY_F7              = 65,
	KEY_F8              = 66,
	KEY_F9              = 67,
	KEY_F10             = 68,
	KEYPAD_NUMLOCK      = 69,
	KEY_SCROLLLOCK      = 70,
	KEYPAD_7            = 71,
	KEYPAD_8            = 72,
	KEYPAD_9            = 73,
	KEYPAD_MINUS        = 74,
	KEYPAD_4            = 75,
	KEYPAD_5            = 76,
	KEYPAD_6            = 77,
	KEYPAD_PLUS         = 78,
	KEYPAD_1            = 79,
	KEYPAD_2            = 80,
	KEYPAD_3            = 81,
	KEYPAD_0            = 82,
	KEYPAD_DELETE       = 83,
	KEY_BACKSLASH       = 86,
	KEY_F11             = 87,
	KEY_F12             = 88,
	KEYPAD_ENTER        = 156,
	KEY_RIGHTCTRL       = 157,
	KEYPAD_FORWARDFLASH = 181,
	KEY_PRINTSCREEN     = 183,
	KEY_ALTGR           = 184,
	KEY_HOME            = 199,
	KEY_CURSORUP        = 200,
	KEY_PGUP            = 201,
	KEY_CURSORLEFT      = 203,
	KEY_END             = 207,
	KEY_CURSORDOWN      = 208,
	KEY_PGDN            = 209,
	KEY_INSERT          = 210,
	KEY_DELETE          = 211,
};
assert_sizeof(Keys8, 0x1);

enum Lego_CryOreType : uint8 // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE]
{
	Lego_CryOreType_None           = 0,
	Lego_CryOreType_Crystal_Lv0_1  = 1,
	Lego_CryOreType_Ore_Lv0_1      = 2,
	Lego_CryOreType_Crystal_Lv1_1  = 3,
	Lego_CryOreType_Ore_Lv1_1      = 4,
	Lego_CryOreType_Crystal_Lv0_3  = 5,
	Lego_CryOreType_Ore_Lv0_3      = 6,
	Lego_CryOreType_Crystal_Lv1_3  = 7,
	Lego_CryOreType_Ore_Lv1_3      = 8,
	Lego_CryOreType_Crystal_Lv0_5  = 9,
	Lego_CryOreType_Ore_Lv0_5      = 10,
	Lego_CryOreType_Crystal_Lv1_5  = 11,
	Lego_CryOreType_Ore_Lv1_5      = 12,
	Lego_CryOreType_Crystal_Lv0_10 = 13,
	Lego_CryOreType_Ore_Lv0_10     = 14,
	Lego_CryOreType_Crystal_Lv1_10 = 15,
	Lego_CryOreType_Ore_Lv01_10    = 16,
	Lego_CryOreType_Crystal_Lv0_25 = 17,
	Lego_CryOreType_Ore_Lv0_25     = 18,
	Lego_CryOreType_Crystal_Lv1_25 = 19,
	Lego_CryOreType_Ore_Lv1_25     = 20,
};
assert_sizeof(Lego_CryOreType, 0x1);

enum Lego_ErodeType : uint8 // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE]
{
	Lego_ErodeType_None              = 0,
	Lego_ErodeType_Adjacent_VerySlow = 1,
	Lego_ErodeType_Source_VerySlow   = 2,
	Lego_ErodeType_Adjacent_Slow     = 3,
	Lego_ErodeType_Source_Slow       = 4,
	Lego_ErodeType_Adjacent_Medium   = 5,
	Lego_ErodeType_Source_Medium     = 6,
	Lego_ErodeType_Adjacent_Fast     = 7,
	Lego_ErodeType_Source_Fast       = 8,
	Lego_ErodeType_Adjacent_VeryFast = 9,
	Lego_ErodeType_Source_VeryFast   = 10,
};
assert_sizeof(Lego_ErodeType, 0x1);

enum Lego_FallInType : uint8 // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE]
{
	Lego_FallInType_None            = 0,
	Lego_FallInType_Normal_Low      = 1,
	Lego_FallInType_Normal_Medium   = 2,
	Lego_FallInType_Normal_High     = 3,
	Lego_FallInType_Normal_VeryHigh = 4,
	Lego_FallInType_Danger_Low      = 5,
	Lego_FallInType_Danger_Medium   = 6,
	Lego_FallInType_Danger_High     = 7,
	Lego_FallInType_Danger_VeryHigh = 8,
};
assert_sizeof(Lego_FallInType, 0x1);

enum Lego_PathType : uint8 // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE]
{
	Lego_PathType_None   = 0,
	Lego_PathType_Rubble = 1,
	Lego_PathType_Path   = 2,
};
assert_sizeof(Lego_PathType, 0x1);

enum Lego_PredugType : uint8 // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE]
{
	Lego_PredugType_Wall             = 0,
	Lego_PredugType_Cavern_Exposed   = 1,
	Lego_PredugType_Cavern_Hidden    = 2,
	Lego_PredugType_SlugHole_Exposed = 3,
	Lego_PredugType_SlugHole_Hidden  = 4,
};
assert_sizeof(Lego_PredugType, 0x1);

enum Lego_SurfaceType : sint32 // [LegoRR/Lego.c|enum:0x4|type:int|tags:BIGENUMALIAS] See TerrainType for byte-sized enum version.
{
	Lego_SurfaceType_Tunnel        = 0,
	Lego_SurfaceType_Immovable     = 1,
	Lego_SurfaceType_Hard          = 2,
	Lego_SurfaceType_Medium        = 3,
	Lego_SurfaceType_Loose         = 4,
	Lego_SurfaceType_Soil          = 5,
	Lego_SurfaceType_Lava          = 6,
	Lego_SurfaceType_Water         = 7,
	Lego_SurfaceType_OreSeam       = 8,
	Lego_SurfaceType_Lake          = 9,
	Lego_SurfaceType_CrystalSeam   = 10,
	Lego_SurfaceType_RechargeSeam  = 11,
	Lego_SurfaceType_Rubble        = 12,
	Lego_SurfaceType_Reinforcement = 13,
	Lego_SurfaceType_Path          = 14,
	Lego_SurfaceType_SlugHole      = 15,
	Lego_SurfaceType_Undiscovered  = 16,
	Lego_SurfaceType_Cavern        = 17,
	Lego_SurfaceType_Count         = 18,
};
assert_sizeof(Lego_SurfaceType, 0x4);

enum Lego_SurfaceType8 : uint8 // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE] byte-sized alias for Lego_SurfaceType
{
	Lego_SurfaceType8_Tunnel        = 0,
	Lego_SurfaceType8_Immovable     = 1,
	Lego_SurfaceType8_Hard          = 2,
	Lego_SurfaceType8_Medium        = 3,
	Lego_SurfaceType8_Loose         = 4,
	Lego_SurfaceType8_Soil          = 5,
	Lego_SurfaceType8_Lava          = 6,
	Lego_SurfaceType8_Water         = 7,
	Lego_SurfaceType8_OreSeam       = 8,
	Lego_SurfaceType8_Lake          = 9,
	Lego_SurfaceType8_CrystalSeam   = 10,
	Lego_SurfaceType8_RechargeSeam  = 11,
	Lego_SurfaceType8_Rubble        = 12,
	Lego_SurfaceType8_Reinforcement = 13,
	Lego_SurfaceType8_Path          = 14,
	Lego_SurfaceType8_SlugHole      = 15,
	Lego_SurfaceType8_Undiscovered  = 16,
	Lego_SurfaceType8_Cavern        = 17,
};
assert_sizeof(Lego_SurfaceType8, 0x1);

enum LegoCamera_Type : sint32 // [LegoRR/LegoCamera.c|enum:0x4|type:int]
{
	LegoCamera_None       = 0,
	LegoCamera_Top        = 1,
	LegoCamera_Radar      = 2,
	LegoCamera_FP         = 3,
	LegoCamera_Type_Count = 4,
};
assert_sizeof(LegoCamera_Type, 0x4);

enum LegoObject_AbilityType : sint32 // [LegoRR/LegoObject.c|enum:0x4|type:int]
{
	LegoObject_AbilityType_Pilot    = 0,
	LegoObject_AbilityType_Sailor   = 1,
	LegoObject_AbilityType_Driver   = 2,
	LegoObject_AbilityType_Dynamite = 3,
	LegoObject_AbilityType_Repair   = 4,
	LegoObject_AbilityType_Scanner  = 5,
	LegoObject_AbilityType_Count    = 6,
	LegoObject_AbilityType_Invalid  = -1,
};
assert_sizeof(LegoObject_AbilityType, 0x4);

enum LegoObject_IDs : sint32 // [LegoRR/dummy.c|enum:0x4|type:int|tags:HELPER]
{
	LegoObject_ID_Ore          = 0,
	LegoObject_ID_ProcessedOre = 1,
	LegoObject_ID_Ore_Count    = 2,
};
assert_sizeof(LegoObject_IDs, 0x4);

enum LegoObject_ToolType : sint32 // [LegoRR/LegoObject.c|enum:0x4|type:int] One of the few enums with extra space before max. All items after FreezerGun are special tools.
{
	LegoObject_ToolType_Drill      = 0,
	LegoObject_ToolType_Spade      = 1,
	LegoObject_ToolType_Hammer     = 2,
	LegoObject_ToolType_Spanner    = 3,
	LegoObject_ToolType_Laser      = 4,
	LegoObject_ToolType_PusherGun  = 5,
	LegoObject_ToolType_BirdScarer = 6,
	LegoObject_ToolType_FreezerGun = 7,
	LegoObject_ToolType_Barrier    = 8,
	LegoObject_ToolType_Dynamite   = 9,
	LegoObject_ToolType_CryOre     = 10,
	LegoObject_ToolType_Count      = 11,
};
assert_sizeof(LegoObject_ToolType, 0x4);

enum LegoObject_Type : sint32 // [LegoRR/LegoObject.c|enum:0x4|type:int]
{
	LegoObject_None              = 0,
	LegoObject_Vehicle           = 1,
	LegoObject_MiniFigure        = 2,
	LegoObject_RockMonster       = 3,
	LegoObject_Building          = 4,
	LegoObject_Boulder           = 5,
	LegoObject_PowerCrystal      = 6,
	LegoObject_Ore               = 7,
	LegoObject_Dynamite          = 8,
	LegoObject_Barrier           = 9,
	LegoObject_UpgradePart       = 10,
	LegoObject_ElectricFence     = 11,
	LegoObject_SpiderWeb         = 12,
	LegoObject_OohScary          = 13,
	LegoObject_ElectricFenceStud = 14,
	LegoObject_Path              = 15,
	LegoObject_Pusher            = 16,
	LegoObject_Freezer           = 17,
	LegoObject_IceCube           = 18,
	LegoObject_LaserShot         = 19,
	LegoObject_Type_Count        = 20,
	LegoObject_TVCamera          = -1,
};
assert_sizeof(LegoObject_Type, 0x4);

enum LegoObject_UpgradeType : uint32 // [LegoRR/LegoObject.c|enum:0x4|type:uint]
{
	LegoObject_UpgradeType_Drill = 0,
	LegoObject_UpgradeType_Speed = 1,
	LegoObject_UpgradeType_Scan  = 2,
	LegoObject_UpgradeType_Carry = 3,
};
assert_sizeof(LegoObject_UpgradeType, 0x4);

enum LevelStatus : uint32 // [LegoRR/Objective.c|enum:0x4|type:uint] Not sure if Objective...
{
	LEVELSTATUS_INCOMPLETE      = 0,
	LEVELSTATUS_COMPLETE        = 1,
	LEVELSTATUS_FAILED          = 2,
	LEVELSTATUS_FAILED_CRYSTALS = 3,
	LEVELSTATUS_FAILED_OTHER    = 4,
};
assert_sizeof(LevelStatus, 0x4);

enum LOD_PolyLevel : sint32 // [LegoRR/MeshLOD.c|enum:0x4|type:int]
{
	LOD_LowPoly    = 0,
	LOD_MediumPoly = 1,
	LOD_HighPoly   = 2,
	LOD_FPPoly     = 3,
};
assert_sizeof(LOD_PolyLevel, 0x4);

enum Menu_ModalType : uint32 // [LegoRR/FrontEnd.c|enum:0x4|type:uint] Types of menus only shown over-top of gameplay. (Count treated as Invalid)
{
	Menu_Modal_Paused  = 0,
	Menu_Modal_Options = 1,
	Menu_Modal_Count   = 2,
};
assert_sizeof(Menu_ModalType, 0x4);

enum Menu_ScreenType : uint32 // [LegoRR/FrontEnd.c|enum:0x4|type:uint] Types of menus only shown out-of-game. (Load is purely speculataion)
{
	Menu_Screen_Title       = 0,
	Menu_Screen_Missions    = 1,
	Menu_Screen_Training    = 2,
	Menu_Screen_Load_unused = 3,
	Menu_Screen_Save        = 4,
	Menu_Screen_Count       = 5,
};
assert_sizeof(Menu_ScreenType, 0x4);

enum MenuItem_SelectImageType : uint32 // [LegoRR/FrontEnd.c|enum:0x4|type:uint]
{
	MenuItem_SelectImage_Light  = 0,
	MenuItem_SelectImage_Dark   = 1,
	MenuItem_SelectImage_Locked = 2,
	MenuItem_SelectImage_Count  = 3,
};
assert_sizeof(MenuItem_SelectImageType, 0x4);

enum MenuItem_Type : sint32 // [LegoRR/FrontEnd.c|enum:0x4|type:int]
{
	MenuItem_Type_Cycle      = 0,
	MenuItem_Type_Trigger    = 1,
	MenuItem_Type_TextInput  = 2,
	MenuItem_Type_Slider     = 3,
	MenuItem_Type_RealSlider = 4,
	MenuItem_Type_Next       = 5,
	MenuItem_Type_Select     = 6,
	MenuItem_Type_Count      = 7,
	MenuItem_Type_Invalid    = -1,
};
assert_sizeof(MenuItem_Type, 0x4);

enum MenuOverlay_Type : sint32 // [LegoRR/FrontEnd.c|enum:0x4|type:int] Based on extension: .flh (default), .avi, .bmp, .lws
{
	MenuOverlay_Type_Flic      = 0,
	MenuOverlay_Type_Animation = 1,
	MenuOverlay_Type_Image     = 2,
	MenuOverlay_Type_Lws       = 3,
	MenuOverlay_Type_Count     = 4,
	MenuOverlay_Type_Invalid   = -1,
};
assert_sizeof(MenuOverlay_Type, 0x4);

enum Mesh_Colour : uint32 // [Gods98/Mesh.c|enum:0x4|type:uint]
{
	Mesh_Colour_Diffuse  = 0,
	Mesh_Colour_Ambient  = 1,
	Mesh_Colour_Specular = 2,
	Mesh_Colour_Emissive = 3,
	Mesh_Colour_Alpha    = 4,
	Mesh_Colour_Power    = 5,
};
assert_sizeof(Mesh_Colour, 0x4);

enum Mesh_Type : uint32 // [Gods98/Mesh.c|enum:0x4|type:uint]
{
	Mesh_Type_Norm            = 0,
	Mesh_Type_PostEffect      = 1,
	Mesh_Type_LightWaveObject = 2,
};
assert_sizeof(Mesh_Type, 0x4);

enum Message_Type : sint32 // [LegoRR/Message.c|enum:0x4|type:int]
{
	Message_Null                          = 0,
	Message_Select                        = 1,
	Message_Selected                      = 2,
	Message_ClearSelection                = 3,
	Message_Deselect                      = 4,
	Message_Goto                          = 5,
	Message_RockMonsterGoto               = 6,
	Message_RockMonsterGotoComplete       = 7,
	Message_UserGoto                      = 8,
	Message_FirstPerson                   = 9,
	Message_TrackObject                   = 10,
	Message_TopView                       = 11,
	Message_PlaySample                    = 12,
	Message_Dig                           = 13,
	Message_DigComplete                   = 14,
	Message_Repair                        = 15,
	Message_RepairComplete                = 16,
	Message_Reinforce                     = 17,
	Message_ReinforceComplete             = 18,
	Message_RockFall                      = 19,
	Message_RockFallComplete              = 20,
	Message_GenerateCrystal               = 21,
	Message_GenerateCrystalComplete       = 22,
	Message_CollectCrystal                = 23,
	Message_CollectCrystalComplete        = 24,
	Message_CrystalToRefinery             = 25,
	Message_CrystalToRefineryComplete     = 26,
	Message_GenerateOre                   = 27,
	Message_GenerateOreComplete           = 28,
	Message_CollectOre                    = 29,
	Message_CollectOreComplete            = 30,
	Message_GenerateRockMonster           = 31,
	Message_GenerateRockMonsterComplete   = 32,
	Message_GatherRock                    = 33,
	Message_GatherRockComplete            = 34,
	Message_PickRandomFloor               = 35,
	Message_PickRandomFloorComplete       = 36,
	Message_AttackBuilding                = 37,
	Message_AttackBuildingComplete        = 38,
	Message_Clear                         = 39,
	Message_ClearComplete                 = 40,
	Message_GetIn                         = 41,
	Message_ManSelectedAndMonsterClicked  = 42,
	Message_FollowAttack                  = 43,
	Message_CollectTool                   = 44,
	Message_ReduceSelection               = 45,
	Message_ClearFallIn                   = 46,
	Message_ClearFallInComplete           = 47,
	Message_BuildPath                     = 48,
	Message_BuildPathComplete             = 49,
	Message_Train                         = 50,
	Message_TrainComplete                 = 51,
	Message_GenerateCrystalAndOre         = 52,
	Message_GenerateCrystalAndOreComplete = 53,
	Message_GenerateFromCryOre            = 54,
	Message_GenerateFromCryOreComplete    = 55,
	Message_Upgrade                       = 56,
	Message_UpgradeComplete               = 57,
	Message_ClearBuilding                 = 58,
	Message_ClearBuildingComplete         = 59,
	Message_ClearInitial                  = 60,
	Message_ClearInitialComplete          = 61,
	Message_ClearRemovePath               = 62,
	Message_ClearRemovePathComplete       = 63,
	Message_Debug_DestroyAll              = 64,
	Message_Type_Count                    = 65,
};
assert_sizeof(Message_Type, 0x4);

enum MiscEffectType : sint32 // [LegoRR/Effects.c|enum:0x4|type:int] Need a better name for this.
{
	MISCOBJECT_LAZERHIT          = 0,
	MISCOBJECT_PUSHERHIT         = 1,
	MISCOBJECT_FREEZERHIT        = 2,
	MISCOBJECT_PATHDUST          = 3,
	MISCOBJECT_LAVAEROSIONSMOKE1 = 4,
	MISCOBJECT_LAVAEROSIONSMOKE2 = 5,
	MISCOBJECT_LAVAEROSIONSMOKE3 = 6,
	MISCOBJECT_LAVAEROSIONSMOKE4 = 7,
	MISCOBJECT_BIRDSCARER        = 8,
	MISCOBJECT_UPGRADEEFFECT     = 9,
};
assert_sizeof(MiscEffectType, 0x4);

enum NERPsFunctionArgs : uint32 // [LegoRR/NERPs.c|enum:0x4|type:uint]
{
	NERPS_ARGS_0          = 0,
	NERPS_ARGS_1          = 1,
	NERPS_ARGS_2          = 2,
	NERPS_ARGS_0_NORETURN = 3,
	NERPS_ARGS_1_NORETURN = 4,
	NERPS_ARGS_2_NORETURN = 5,
	NERPS_ARGS_3_NORETURN = 6,
	NERPS_END_OF_LIST     = 7,
};
assert_sizeof(NERPsFunctionArgs, 0x4);

enum NERPsOpcode : uint16 // [LegoRR/NERPs.c|enum:0x2|type:ushort]
{
	OP_PUSH  = 0,
	OP_CMP   = 1,
	OP_CALL  = 2,
	OP_LABEL = 4,
	OP_GOTO  = 8,
};
assert_sizeof(NERPsOpcode, 0x2);

enum NERPsTutorialAction : uint32 // [LegoRR/NERPs.c|enum:0x4|type:uint]
{
	NERPS_TUTORIAL_NONE                            = 0,
	NERPS_TUTORIAL_GETBLOCKISGROUND                = 1,
	NERPS_TUTORIAL_SETBLOCKISGROUND                = 2,
	NERPS_TUTORIAL_GETBLOCKISPATH                  = 3,
	NERPS_TUTORIAL_SETBLOCKISPATH                  = 4,
	NERPS_TUTORIAL_SETCAMERAGOTOTUTORIAL           = 5,
	NERPS_TUTORIAL_GETCAMERAATTUTORIAL             = 6,
	NERPS_TUTORIAL_SETROCKMONSTERATTUTORIAL        = 7,
	NERPS_TUTORIAL_SETCONGREGATIONATTUTORIAL_START = 8,
	NERPS_TUTORIAL_SETCONGREGATIONATTUTORIAL_STOP  = 9,
	NERPS_TUTORIAL_GETUNITATBLOCK                  = 10,
	NERPS_TUTORIAL_SETTUTORIALPOINTER_UNK          = 11,
	NERPS_TUTORIAL_MAKESOMEONEPICKUP               = 12,
	NERPS_TUTORIAL_GETMONSTERATTUTORIAL            = 13,
};
assert_sizeof(NERPsTutorialAction, 0x4);

enum Panel_Type : sint32 // [LegoRR/Panels.c|enum:0x4|type:int]
{
	Panel_Radar          = 0,
	Panel_RadarFill      = 1,
	Panel_RadarOverlay   = 2,
	Panel_Messages       = 3,
	Panel_MessagesSide   = 4,
	Panel_CrystalSideBar = 5,
	Panel_TopPanel       = 6,
	Panel_Information    = 7,
	Panel_PriorityList   = 8,
	Panel_CameraControl  = 9,
	Panel_InfoDock       = 10,
	Panel_Encyclopedia   = 11,
	Panel_Type_Count     = 12,
};
assert_sizeof(Panel_Type, 0x4);

enum PanelButton_Type : sint32 // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
{
	PanelButton_CameraControl_ZoomIn         = 0,
	PanelButton_CrystalSideBar_Ore           = 0,
	PanelButton_Encyclopedia_Close           = 0,
	PanelButton_InfoDock_Goto                = 0,
	PanelButton_Information_Toggle           = 0,
	PanelButton_PriorityList_Disable1        = 0,
	PanelButton_Radar_Toggle                 = 0,
	PanelButton_TopPanel_Options             = 0,
	PanelButton_CameraControl_ZoomOut        = 1,
	PanelButton_CrystalSideBar_Crystals      = 1,
	PanelButton_Encyclopedia_Count           = 1,
	PanelButton_InfoDock_Close               = 1,
	PanelButton_Information_Function         = 1,
	PanelButton_PriorityList_Disable2        = 1,
	PanelButton_Radar_TaggedObjectView       = 1,
	PanelButton_TopPanel_Priorities          = 1,
	PanelButton_CameraControl_CycleBuildings = 2,
	PanelButton_CrystalSideBar_Count         = 2,
	PanelButton_InfoDock_Count               = 2,
	PanelButton_Information_Count            = 2,
	PanelButton_PriorityList_Disable3        = 2,
	PanelButton_Radar_ZoomIn                 = 2,
	PanelButton_TopPanel_CallToArms          = 2,
	PanelButton_CameraControl_Rotate         = 3,
	PanelButton_PriorityList_Disable4        = 3,
	PanelButton_Radar_ZoomOut                = 3,
	PanelButton_TopPanel_Count               = 3,
	PanelButton_CameraControl_Count          = 4,
	PanelButton_PriorityList_Disable5        = 4,
	PanelButton_Radar_MapView                = 4,
	PanelButton_PriorityList_Disable6        = 5,
	PanelButton_Radar_Count                  = 5,
	PanelButton_PriorityList_Disable7        = 6,
	PanelButton_PriorityList_Disable8        = 7,
	PanelButton_PriorityList_Disable9        = 8,
	PanelButton_PriorityList_UpOne1          = 9,
	PanelButton_PriorityList_UpOne2          = 10,
	PanelButton_PriorityList_UpOne3          = 11,
	PanelButton_PriorityList_UpOne4          = 12,
	PanelButton_PriorityList_UpOne5          = 13,
	PanelButton_PriorityList_UpOne6          = 14,
	PanelButton_PriorityList_UpOne7          = 15,
	PanelButton_PriorityList_UpOne8          = 16,
	PanelButton_PriorityList_Close           = 17,
	PanelButton_PriorityList_Reset           = 18,
	PanelButton_PriorityList_Count           = 19,
	PanelButton_Type_Count                   = 24,
};
assert_sizeof(PanelButton_Type, 0x4);

enum PanelButtonCameraControl : sint32 // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
{
	PanelButton_CameraControl_ZoomIn         = 0,
	PanelButton_CameraControl_ZoomOut        = 1,
	PanelButton_CameraControl_CycleBuildings = 2,
	PanelButton_CameraControl_Rotate         = 3,
	PanelButton_CameraControl_Count          = 4,
};
assert_sizeof(PanelButtonCameraControl, 0x4);

enum PanelButtonCrystalSideBar : sint32 // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
{
	PanelButton_CrystalSideBar_Ore      = 0,
	PanelButton_CrystalSideBar_Crystals = 1,
	PanelButton_CrystalSideBar_Count    = 2,
};
assert_sizeof(PanelButtonCrystalSideBar, 0x4);

enum PanelButtonEncyclopedia : sint32 // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
{
	PanelButton_Encyclopedia_Close = 0,
	PanelButton_Encyclopedia_Count = 1,
};
assert_sizeof(PanelButtonEncyclopedia, 0x4);

enum PanelButtonInfoDock : sint32 // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
{
	PanelButton_InfoDock_Goto  = 0,
	PanelButton_InfoDock_Close = 1,
	PanelButton_InfoDock_Count = 2,
};
assert_sizeof(PanelButtonInfoDock, 0x4);

enum PanelButtonInformation : sint32 // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
{
	PanelButton_Information_Toggle   = 0,
	PanelButton_Information_Function = 1,
	PanelButton_Information_Count    = 2,
};
assert_sizeof(PanelButtonInformation, 0x4);

enum PanelButtonPriorityList : sint32 // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
{
	PanelButton_PriorityList_Disable1 = 0,
	PanelButton_PriorityList_Disable2 = 1,
	PanelButton_PriorityList_Disable3 = 2,
	PanelButton_PriorityList_Disable4 = 3,
	PanelButton_PriorityList_Disable5 = 4,
	PanelButton_PriorityList_Disable6 = 5,
	PanelButton_PriorityList_Disable7 = 6,
	PanelButton_PriorityList_Disable8 = 7,
	PanelButton_PriorityList_Disable9 = 8,
	PanelButton_PriorityList_UpOne1   = 9,
	PanelButton_PriorityList_UpOne2   = 10,
	PanelButton_PriorityList_UpOne3   = 11,
	PanelButton_PriorityList_UpOne4   = 12,
	PanelButton_PriorityList_UpOne5   = 13,
	PanelButton_PriorityList_UpOne6   = 14,
	PanelButton_PriorityList_UpOne7   = 15,
	PanelButton_PriorityList_UpOne8   = 16,
	PanelButton_PriorityList_Close    = 17,
	PanelButton_PriorityList_Reset    = 18,
	PanelButton_PriorityList_Count    = 19,
};
assert_sizeof(PanelButtonPriorityList, 0x4);

enum PanelButtonRadar : sint32 // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
{
	PanelButton_Radar_Toggle           = 0,
	PanelButton_Radar_TaggedObjectView = 1,
	PanelButton_Radar_ZoomIn           = 2,
	PanelButton_Radar_ZoomOut          = 3,
	PanelButton_Radar_MapView          = 4,
	PanelButton_Radar_Count            = 5,
};
assert_sizeof(PanelButtonRadar, 0x4);

enum PanelButtonTopPanel : sint32 // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
{
	PanelButton_TopPanel_Options    = 0,
	PanelButton_TopPanel_Priorities = 1,
	PanelButton_TopPanel_CallToArms = 2,
	PanelButton_TopPanel_Count      = 3,
};
assert_sizeof(PanelButtonTopPanel, 0x4);

enum PanelButtonType : sint32 // [LegoRR/Panels.c|enum:0x4|type:int|tags:REALENUM] DEFINE ONLY
{
	PANELBUTTON_TYPE_COUNT = 24,
};
assert_sizeof(PanelButtonType, 0x4);

enum Pointer_Type : sint32 // [LegoRR/Pointer.c|enum:0x4|type:int]
{
	Pointer_Standard                 = 0,
	Pointer_Blank                    = 1,
	Pointer_Selected                 = 2,
	Pointer_Drill                    = 3,
	Pointer_CantDrill                = 4,
	Pointer_Clear                    = 5,
	Pointer_Go                       = 6,
	Pointer_CantGo                   = 7,
	Pointer_Teleport                 = 8,
	Pointer_CantTeleport             = 9,
	Pointer_Reinforce                = 10,
	Pointer_CantReinforce            = 11,
	Pointer_RadarPan                 = 12,
	Pointer_TrackObject              = 13,
	Pointer_Help                     = 14,
	Pointer_CantHelp                 = 15,
	Pointer_PutDown                  = 16,
	Pointer_GetIn                    = 17,
	Pointer_GetOut                   = 18,
	Pointer_TutorialBlockInfo        = 19,
	Pointer_Okay                     = 20,
	Pointer_NotOkay                  = 21,
	Pointer_CanBuild                 = 22,
	Pointer_CannotBuild              = 23,
	Pointer_Dynamite                 = 24,
	Pointer_CantDynamite             = 25,
	Pointer_PickUp                   = 26,
	Pointer_CantPickUp               = 27,
	Pointer_PickUpOre                = 28,
	Pointer_LegoManCantDig           = 29,
	Pointer_VehicleCantDig           = 30,
	Pointer_LegoManDig               = 31,
	Pointer_VehicleDig               = 32,
	Pointer_LegoManCantPickUp        = 33,
	Pointer_VehicleCantPickUp        = 34,
	Pointer_LegoManPickUp            = 35,
	Pointer_VehiclePickUp            = 36,
	Pointer_LegoManCantGo            = 37,
	Pointer_VehicleCantGo            = 38,
	Pointer_LegoManGo                = 39,
	Pointer_VehicleGo                = 40,
	Pointer_LegoManClear             = 41,
	Pointer_VehicleClear             = 42,
	Pointer_SurfaceType_Immovable    = 43,
	Pointer_SurfaceType_Hard         = 44,
	Pointer_SurfaceType_Medium       = 45,
	Pointer_SurfaceType_Loose        = 46,
	Pointer_SurfaceType_Soil         = 47,
	Pointer_SurfaceType_Lava         = 48,
	Pointer_SurfaceType_Water        = 49,
	Pointer_SurfaceType_OreSeam      = 50,
	Pointer_SurfaceType_Lake         = 51,
	Pointer_SurfaceType_CrystalSeam  = 52,
	Pointer_SurfaceType_RechargeSeam = 53,
	Pointer_CantZoom                 = 54,
	Pointer_Zoom                     = 55,
	Pointer_Type_Count               = 56,
};
assert_sizeof(Pointer_Type, 0x4);

enum PointerSFX_Type : uint32 // [LegoRR/Lego.c|enum:0x4|type:uint] Argument for Lego_SetPointerSFX (FUN_00428730)
{
	PointerSFX_Okay                  = 0,
	PointerSFX_NotOkay               = 1,
	PointerSFX_NotOkay_ImmovableRock = 2,
	PointerSFX_Okay_TopPriority      = 3,
	PointerSFX_Okay_Wall             = 4,
	PointerSFX_Okay_Floor            = 5,
};
assert_sizeof(PointerSFX_Type, 0x4);

enum ProgrammerMode : uint32 // [LegoRR/Lego.c|enum:0x4|type:uint] Programmer mode enum
{
	PROGRAMMER_OFF     = 0,
	PROGRAMMER_MODE_1  = 1,
	PROGRAMMER_MODE_2  = 2,
	PROGRAMMER_MODE_3  = 3,
	PROGRAMMER_MODE_10 = 10,
	PROGRAMMER_MODE_11 = 11,
};
assert_sizeof(ProgrammerMode, 0x4);

enum RegistryType : uint32 // [Gods98/Registry.c|enum:0x4|type:uint] Supported registry information types
{
	REGISTRY_STRING_VALUE = 0,
	REGISTRY_DWORD_VALUE  = 1,
};
assert_sizeof(RegistryType, 0x4);

enum Reward_Type : sint32 // [LegoRR/Rewards.c|enum:0x4|type:int]
{
	Reward_Crystals      = 0,
	Reward_Ore           = 1,
	Reward_Diggable      = 2,
	Reward_Constructions = 3,
	Reward_Caverns       = 4,
	Reward_Figures       = 5,
	Reward_RockMonsters  = 6,
	Reward_Oxygen        = 7,
	Reward_Timer         = 8,
	Reward_Score         = 9,
	Reward_Type_Count    = 10,
	Reward_Type_Invalid  = -1,
};
assert_sizeof(Reward_Type, 0x4);

enum RewardScrollLabelMode : uint32 // [LegoRR/Rewards.c|enum:0x4|type:uint] Inclusive mode, None does nothing, WINDOW also performs IMAGE and TEXT, IMAGE also performs TEXT, TEXT does only that
{
	REWARDSCROLL_MODE_NONE   = 0,
	REWARDSCROLL_MODE_WINDOW = 1,
	REWARDSCROLL_MODE_IMAGE  = 2,
	REWARDSCROLL_MODE_TEXT   = 3,
};
assert_sizeof(RewardScrollLabelMode, 0x4);

enum RewardUIState : uint32 // [LegoRR/Rewards.c|enum:0x4|type:uint]
{
	REWARDSTATE_0      = 0,
	REWARDSTATE_1      = 1,
	REWARDSTATE_2      = 2,
	REWARDSTATE_3      = 3,
	REWARDSTATE__COUNT = 4,
};
assert_sizeof(RewardUIState, 0x4);

enum RNCCompression : uint8 // [Gods98/Compress.c|enum:0x1|type:byte]
{
	RNC_COMPRESS_STORE = 0,
	RNC_COMPRESS_BEST  = 1,
	RNC_COMPRESS_FAST  = 2,
};
assert_sizeof(RNCCompression, 0x1);

enum RNCError : sint16 // [Gods98/Compress.c|enum:0x2|type:short]
{
	RNC_OK                 = 0,
	RNC_INVALIDCOMPRESSION = 65534,
	RNC_INVALIDFILE        = 65535,
};
assert_sizeof(RNCError, 0x2);

enum RockFallType : sint32 // [LegoRR/Effects.c|enum:0x4|type:int]
{
	ROCKFALL_3SIDES        = 0,
	ROCKFALL_OUTSIDECORNER = 1,
	ROCKFALL_VTUNNEL       = 2,
};
assert_sizeof(RockFallType, 0x4);

enum RouteAction : uint8 // [LegoRR/Text.c|enum:0x1|type:byte]
{
	ROUTE_ACTION_UNK_1       = 1,
	ROUTE_ACTION_REINFORCE   = 2,
	ROUTE_ACTION_GATHERROCK  = 3,
	ROUTE_ACTION_CLEAR       = 4,
	ROUTE_ACTION_UNK_5       = 5,
	ROUTE_ACTION_REPAIRDRAIN = 6,
	ROUTE_ACTION_STORE       = 7,
	ROUTE_ACTION_DROP        = 8,
	ROUTE_ACTION_PLACE       = 9,
	ROUTE_ACTION_UNK_10      = 10,
	ROUTE_ACTION_EAT         = 11,
	ROUTE_ACTION_UNK_12      = 12,
	ROUTE_ACTION_UNK_13      = 13,
	ROUTE_ACTION_TRAIN       = 14,
	ROUTE_ACTION_UPGRADE     = 15,
	ROUTE_ACTION_UNK_16      = 16,
	ROUTE_ACTION_UNK_17      = 17,
	ROUTE_ACTION_RECHARGE    = 18,
	ROUTE_ACTION_DOCK        = 19,
	ROUTE_ACTION_ATTACK      = 20,
	ROUTE_ACTION_21          = 21,
};
assert_sizeof(RouteAction, 0x1);

enum SFX_ID : sint32 // [LegoRR/SFX.c|enum:0x4|type:int] SFXType is different from actual Sample indexes, these are hardcoded values that can easily be looked up by ID
{
	SFX_NULL                    = 0,
	SFX_Stamp                   = 1,
	SFX_Drill                   = 2,
	SFX_DrillFade               = 3,
	SFX_RockBreak               = 4,
	SFX_Drip                    = 5,
	SFX_Ambient                 = 6,
	SFX_AmbientLoop             = 7,
	SFX_Step                    = 8,
	SFX_RockMonster             = 9,
	SFX_RockMonster2            = 10,
	SFX_RockMonsterStep         = 11,
	SFX_MFDeposit               = 12,
	SFX_ButtonPressed           = 13,
	SFX_MFLift                  = 14,
	SFX_MFThrow                 = 15,
	SFX_Walker                  = 16,
	SFX_YesSir                  = 17,
	SFX_Build                   = 18,
	SFX_Okay                    = 19,
	SFX_NotOkay                 = 20,
	SFX_InterfaceSlideOnScreen  = 21,
	SFX_InterfaceSlideOffScreen = 22,
	SFX_PanelSlideOnScreen      = 23,
	SFX_PanelSlideOffScreen     = 24,
	SFX_Siren                   = 25,
	SFX_CrystalRecharge         = 26,
	SFX_Laser                   = 27,
	SFX_LaserHit                = 28,
	SFX_LazerRecharge           = 29,
	SFX_TopPriority             = 30,
	SFX_ImmovableRock           = 31,
	SFX_Wall                    = 32,
	SFX_Floor                   = 33,
	SFX_BoulderHit              = 34,
	SFX_Place                   = 35,
	SFX_PlaceOre                = 36,
	SFX_PlaceCrystal            = 37,
	SFX_Lava                    = 38,
	SFX_RockWipe                = 39,
	SFX_FallIn                  = 40,
	SFX_MusicLoop               = 41,
	SFX_CaptainSlide            = 42,
	SFX_Dynamite                = 43,
	SFX_AmbientMusicLoop        = 44,
	SFX_Preload_Count           = 45,
	SFX_ID_Invalid              = -1,
};
assert_sizeof(SFX_ID, 0x4);

enum Smoke_Type : uint32 // [LegoRR/Smoke.c|enum:0x4|type:uint]
{
	Smoke_Type_Looping   = 0,
	Smoke_Type_Attach    = 1,
	Smoke_Type_Dissipate = 2,
};
assert_sizeof(Smoke_Type, 0x4);

enum Sound3DPlay : uint32 // [Gods98/3DSound.c|enum:0x4|type:uint]
{
	Sound3DPlay_OnFrame = 0,
	Sound3DPlay_OnPos   = 1,
	Sound3DPlay_Normal  = 2,
};
assert_sizeof(Sound3DPlay, 0x4);

enum SoundMode : uint32 // [Gods98/Sound.c|enum:0x4|type:uint]
{
	SoundMode_Once  = 0,
	SoundMode_Loop  = 1,
	SoundMode_Multi = 2,
};
assert_sizeof(SoundMode, 0x4);

enum SurfaceTexture : uint8 // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE,COORDNIBBLE]
{
	TEXTURE_FLOOR_STD                = 0x{self.value:02},
	TEXTURE_WALL_SOIL                = 0x{self.value:02},
	TEXTURE_WALL_LOOSE               = 0x{self.value:02},
	TEXTURE_WALL_MED                 = 0x{self.value:02},
	TEXTURE_WALL_HARD                = 0x{self.value:02},
	TEXTURE_WALL_IMM                 = 0x{self.value:02},
	TEXTURE_FLOOR_ERODE_LOW          = 0x{self.value:02},
	TEXTURE_FLOOR_07                 = 0x{self.value:02},
	TEXTURE_FLOOR_RUBBLE_MAX         = 0x{self.value:02},
	TEXTURE_FLOOR_RUBBLE_HIGH        = 0x{self.value:02},
	TEXTURE_FLOOR_RUBBLE_MED         = 0x{self.value:02},
	TEXTURE_FLOOR_RUBBLE_LOW         = 0x{self.value:02},
	TEXTURE_FLOOR_ERODE_MED          = 0x{self.value:02},
	TEXTURE_WALL_CRYSTALSEAM         = 0x{self.value:02},
	TEXTURE_REINWALL_SOIL            = 0x{self.value:02},
	TEXTURE_REINWALL_LOOSE           = 0x{self.value:02},
	TEXTURE_REINWALL_MED             = 0x{self.value:02},
	TEXTURE_REINWALL_HARD            = 0x{self.value:02},
	TEXTURE_REINWALL_IMM             = 0x{self.value:02},
	TEXTURE_FLOOR_ERODE_HIGH         = 0x{self.value:02},
	TEXTURE_FLOOR_SLUGHOLE           = 0x{self.value:02},
	TEXTURE_INCORNER_SOIL            = 0x{self.value:02},
	TEXTURE_INCORNER_LOOSE           = 0x{self.value:02},
	TEXTURE_INCORNER_MED             = 0x{self.value:02},
	TEXTURE_INCORNER_HARD            = 0x{self.value:02},
	TEXTURE_INCORNER_IMM             = 0x{self.value:02},
	TEXTURE_FLOOR_ERODE_MAX          = 0x{self.value:02},
	TEXTURE_WALL_ORESEAM             = 0x{self.value:02},
	TEXTURE_FLOOR_WATER              = 0x{self.value:02},
	TEXTURE_FLOOR_LAVA               = 0x{self.value:02},
	TEXTURE_FLOOR_LAVA_NOTHOT        = 0x{self.value:02},
	TEXTURE_OUTCORNER_SOIL           = 0x{self.value:02},
	TEXTURE_OUTCORNER_LOOSE          = 0x{self.value:02},
	TEXTURE_OUTCORNER_MED            = 0x{self.value:02},
	TEXTURE_OUTCORNER_HARD           = 0x{self.value:02},
	TEXTURE_OUTCORNER_IMM            = 0x{self.value:02},
	TEXTURE_FLOOR_PATH_4SIDES        = 0x{self.value:02},
	TEXTURE_FLOOR_PATH_LAYED         = 0x{self.value:02},
	TEXTURE_FLOOR_PATH_2SIDES        = 0x{self.value:02},
	TEXTURE_FLOOR_PATH_CORNER        = 0x{self.value:02},
	TEXTURE_FLOOR_PATH_3SIDES        = 0x{self.value:02},
	TEXTURE_FLOOR_PATH_1SIDES        = 0x{self.value:02},
	TEXTURE_FLOOR_POWERED_FOUNDATION = 0x{self.value:02},
	TEXTURE_WALL_RECHARGESEAM        = 0x{self.value:02},
	TEXTURE_ROOF_STD                 = 0x{self.value:02},
	TEXTURE_FLOOR_POWERED_4SIDES     = 0x{self.value:02},
	TEXTURE_FLOOR_POWERED_2SIDES     = 0x{self.value:02},
	TEXTURE_FLOOR_POWERED_CORNER     = 0x{self.value:02},
	TEXTURE_FLOOR_POWERED_3SIDES     = 0x{self.value:02},
	TEXTURE_FLOOR_POWERED_1SIDES     = 0x{self.value:02},
	TEXTURE_FLOOR_PATH_FOUNDATION    = 0x{self.value:02},
	TEXTURE_DIAGONAL_STD             = 0x{self.value:02},
	TEXTURE__INVALID                 = 0x{self.value:02},
};
assert_sizeof(SurfaceTexture, 0x1);

enum Text_Type : sint32 // [LegoRR/Text.c|enum:0x4|type:int]
{
	Text_Walk                = 0,
	Text_Drill               = 1,
	Text_NoDrill             = 2,
	Text_CantDrill           = 3,
	Text_Reinforce           = 4,
	Text_NoReinforce         = 5,
	Text_CantReinforce       = 6,
	Text_PickupCrystal       = 7,
	Text_Encyclopedia        = 8,
	Text_RadarHelp           = 9,
	Text_BuildHelp           = 10,
	Text_SelectionHelp       = 11,
	Text_Drive               = 12,
	Text_CantDrive           = 13,
	Text_MakeTeleporter      = 14,
	Text_CannotPlaceBuilding = 15,
	Text_CrystalOreDisabled  = 16,
	Text_CrystalFound        = 17,
	Text_CavernDiscovered    = 18,
	Text_OreFound            = 19,
	Text_AirSupplyLow        = 20,
	Text_AirSupplyRunningOut = 21,
	Text_SpaceToContinue     = 22,
	Text_GameCompleted       = 23,
	Text_ManTrained          = 24,
	Text_UnitUpgraded        = 25,
	Text_Type_Count          = 26,
};
assert_sizeof(Text_Type, 0x4);

enum TextureType : sint32 // [LegoRR/dummy.c|enum:0x4|type:int|tags:HELPER,UNUSED]
{
	TEXTURES_ROCK     = 0,
	TEXTURES_LAVA     = 1,
	TEXTURES_ICE      = 2,
	TEXTURES__INVALID = -1,
};
assert_sizeof(TextureType, 0x4);

enum ToolTip_Type : sint32 // [LegoRR/ToolTip.c|enum:0x4|type:int]
{
	ToolTip_Null                       = 0,
	ToolTip_RadarBlock                 = 1,
	ToolTip_UnitSelect                 = 2,
	ToolTip_Construction               = 3,
	ToolTip_InterfaceMenu              = 4,
	ToolTip_InterfaceMenuBackButton    = 5,
	ToolTip_MapBlock                   = 6,
	ToolTip_Priority                   = 7,
	ToolTip_InfoMenuContinue           = 8,
	ToolTip_InfoMenuDisableFuture      = 9,
	ToolTip_RadarToggle                = 10,
	ToolTip_RadarObjectView            = 11,
	ToolTip_RadarZoomIn                = 12,
	ToolTip_RadarZoomOut               = 13,
	ToolTip_RadarMapView               = 14,
	ToolTip_InfoDockGoto               = 15,
	ToolTip_InfoDockClose              = 16,
	ToolTip_TopPanelCallToArms         = 17,
	ToolTip_TopPanelInfo               = 18,
	ToolTip_TopPanelOptions            = 19,
	ToolTip_TopPanelPriorities         = 20,
	ToolTip_PriorityDisable            = 21,
	ToolTip_PriorityUpOne              = 22,
	ToolTip_PriorityReset              = 23,
	ToolTip_CamControlZoomIn           = 24,
	ToolTip_CamControlZoomOut          = 25,
	ToolTip_CamControlCycle            = 26,
	ToolTip_CamControlRotate           = 27,
	ToolTip_SideBar_Ore                = 28,
	ToolTip_SideBar_Crystals           = 29,
	ToolTip_Close                      = 30,
	ToolTip_PreviousMessage            = 31,
	ToolTip_NextMessage                = 32,
	ToolTip_More                       = 33,
	ToolTip_Back                       = 34,
	ToolTip_CamControlCycleMinifigures = 35,
	ToolTip_Reward_Save                = 36,
	ToolTip_Reward_Advance             = 37,
	ToolTip_FrontEnd_Back              = 38,
	ToolTip_Type_Count                 = 39,
};
assert_sizeof(ToolTip_Type, 0x4);

enum ViewMode : sint32 // [LegoRR/Lego.c|enum:0x4|type:int]
{
	ViewMode_FP  = 0,
	ViewMode_Top = 1,
};
assert_sizeof(ViewMode, 0x4);

enum WallHighlightType : sint32 // [LegoRR/Lego.c|enum:0x4|type:int|tags:BIGENUMALIAS] (white, gray, red, green, blue, dark-yellow)
{
	WALLHIGHLIGHT_NONE      = 0,
	WALLHIGHLIGHT_DIG       = 1,
	WALLHIGHLIGHT_DYNAMITE  = 2,
	WALLHIGHLIGHT_REINFORCE = 3,
	WALLHIGHLIGHT_SELECTED  = 4,
	WALLHIGHLIGHT_TUTORIAL  = 5,
};
assert_sizeof(WallHighlightType, 0x4);

enum WallHighlightType8 : uint8 // [LegoRR/Lego.c|enum:0x1|type:byte] Byte-sized WallHighlightType (white, gray, red, green, blue, dark-yellow)
{
	WALLHIGHLIGHT8_NONE      = 0,
	WALLHIGHLIGHT8_DIG       = 1,
	WALLHIGHLIGHT8_DYNAMITE  = 2,
	WALLHIGHLIGHT8_REINFORCE = 3,
	WALLHIGHLIGHT8_SELECTED  = 4,
	WALLHIGHLIGHT8_TUTORIAL  = 5,
};
assert_sizeof(WallHighlightType8, 0x1);

enum Weapon_KnownType : sint32 // [LegoRR/Weapons.c|enum:0x4|type:int|tags:UNKNOWN] This is not the same as WeponTypes defined in Lego.cfg, these are fixed ID's that are then looked up by value. Boulder is never used.
{
	Weapon_KnownType_None    = 0,
	Weapon_KnownType_Laser   = 1,
	Weapon_KnownType_Pusher  = 2,
	Weapon_KnownType_Freezer = 3,
	Weapon_KnownType_Boulder = 4,
};
assert_sizeof(Weapon_KnownType, 0x4);



enum Advisor_GlobFlags : uint32 // [LegoRR/Advisor.c|flags:0x4|type:uint]
{
	ADVISOR_GLOB_FLAG_NONE      = 0,
	ADVISOR_GLOB_FLAG_ANIMATING = 0x1,
	ADVISOR_GLOB_FLAG_LOOPING   = 0x2,
};
flags_end(Advisor_GlobFlags, 0x4);

enum AdvisorFlags : uint32 // [LegoRR/Advisor.c|flags:0x4|type:uint]
{
	ADVISOR_FLAG_NONE    = 0,
	ADVISOR_FLAG_NOPANEL = 0x10000,
	ADVISOR_FLAG_USED    = 0x20000,
	ADVISOR_FLAG_HASTEXT = 0x40000,
};
flags_end(AdvisorFlags, 0x4);

enum AITask_GlobFlags : uint32 // [LegoRR/AITask.c|flags:0x4|type:uint]
{
	AITASK_GLOB_FLAG_NONE           = 0,
	AITASK_GLOB_FLAG_INITIALISED    = 0x1,
	AITASK_GLOB_FLAG_REMOVING       = 0x2,
	AITASK_GLOB_FLAG_UPDATINGOBJECT = 0x4,
	AITASK_GLOB_FLAG_DISABLEUPDATES = 0x80000000,
};
flags_end(AITask_GlobFlags, 0x4);

enum AITaskFlags : uint32 // [LegoRR/AITask.c|flags:0x4|type:uint]
{
	AITASK_FLAG_NONE               = 0,
	AITASK_FLAG_PERFORMING         = 0x1,
	AITASK_FLAG_UPDATED            = 0x2,
	AITASK_FLAG_VOLATILE           = 0x4,
	AITASK_FLAG_DIGCONNECTION      = 0x8,
	AITASK_FLAG_REALLOCATE         = 0x10,
	AITASK_FLAG_REMOVING           = 0x20,
	AITASK_FLAG_DUPLICATE          = 0x40,
	AITASK_FLAG_NOTIMELIMIT        = 0x80,
	AITASK_FLAG_IMMEDIATESELECTION = 0x100,
	AITASK_FLAG_CLONED             = 0x200,
	AITASK_FLAG_CARRYTASK          = 0x400,
	AITASK_FLAG_FACEOUT            = 0x800,
	AITASK_FLAG_WAITINGFORTOOL     = 0x1000,
	AITASK_FLAG_CREATUREREALLOCATE = 0x2000,
	AITASK_FLAG_FALLINCLEAR        = 0x4000,
	AITASK_FLAG_WAITINGFORTRAIN    = 0x8000,
	AITASK_FLAG_MAXIMUMPRIORITY    = 0x10000,
	AITASK_FLAG_MANUALYSELECTED    = 0x20000,
	AITASK_FLAG_PAUSEDDUPLICATION  = 0x40000,
	AITASK_FLAG_DISABLED           = 0x80000,
	AITASK_FLAG_ACCEPTCARRYING     = 0x100000,
	AITASK_FLAG_UPGRADEBUILDING    = 0x200000,
};
flags_end(AITaskFlags, 0x4);

enum BlockActivityFlags : uint8 // [LegoRR/Lego.c|flags:0x1|type:byte] 0x1 does not directly affect other flags, 0x2 is used to remove the activity after destroying has finished.
{
	BLOCKACT_FLAG_NONE       = 0,
	BLOCKACT_FLAG_STANDING   = 0x1,
	BLOCKACT_FLAG_REMOVING   = 0x2,
	BLOCKACT_FLAG_DESTROYING = 0x4,
};
flags_end(BlockActivityFlags, 0x1);

enum BlockFlags1 : uint32 // [LegoRR/Lego.c|flags:0x4|type:uint]
{
	BLOCK1_NONE                = 0,
	BLOCK1_RUBBLE_LOW          = 0x1,
	BLOCK1_RUBBLE_MEDIUM       = 0x2,
	BLOCK1_RUBBLE_FULL         = 0x3,
	BLOCK1_SURVEYED            = 0x4,
	BLOCK1_FLOOR               = 0x8,
	BLOCK1_WALL                = 0x10,
	BLOCK1_REINFORCED          = 0x20,
	BLOCK1_INCORNER            = 0x40,
	BLOCK1_OUTCORNER           = 0x80,
	BLOCK1_HIGHPOLY            = 0x100,
	BLOCK1_NOTHOT              = 0x200,
	BLOCK1_BUILDINGSOLID       = 0x400,
	BLOCK1_ROCKFALLFX          = 0x800,
	BLOCK1_LANDSLIDING         = 0x1000,
	BLOCK1_DIAGONAL            = 0x2000,
	BLOCK1_SMOKE               = 0x4000,
	BLOCK1_BUILDINGPATH        = 0x8000,
	BLOCK1_HIDDEN              = 0x20000,
	BLOCK1_DESTROYEDCONNECTION = 0x40000,
	BLOCK1_BUSY_FLOOR          = 0x80000,
	BLOCK1_FOUNDATION          = 0x100000,
	BLOCK1_CLEARED             = 0x200000,
	BLOCK1_EXPOSEDFLOORCHECKS  = 0x400000,
	BLOCK1_DIGREQUEST          = 0x800000,
	BLOCK1_UNUSED_PATHTYPE     = 0x1000000,
	BLOCK1_EXPOSED             = 0x4000000,
	BLOCK1_BUSY_WALL           = 0x8000000,
	BLOCK1_DOZERCLEARING       = 0x10000000,
	BLOCK1_PATH                = 0x20000000,
	BLOCK1_LAYEDPATH           = 0x40000000,
	BLOCK1_ERODEACTIVE         = 0x80000000,
};
flags_end(BlockFlags1, 0x4);

enum BlockFlags2 : uint32 // [LegoRR/Lego.c|flags:0x4|type:uint]
{
	BLOCK2_NONE              = 0,
	BLOCK2_GENERATEPOWER     = 0x1,
	BLOCK2_DRAINPOWER_TEMP   = 0x2,
	BLOCK2_TOOLSTORE         = 0x4,
	BLOCK2_FENCEREQUEST      = 0x8,
	BLOCK2_ERODELOCKED       = 0x10,
	BLOCK2_SLUGHOLE_EXPOSED  = 0x20,
	BLOCK2_EMERGE_POINT      = 0x40,
	BLOCK2_EMERGE_TRIGGER    = 0x80,
	BLOCK2_POWERED           = 0x100,
	BLOCK2_SLUGHOLE_HIDDEN   = 0x200,
	BLOCK2_PATHSBUILTCOUNTED = 0x400,
};
flags_end(BlockFlags2, 0x4);

enum BuildingFlags : uint32 // [LegoRR/Building.c|flags:0x4|type:uint]
{
	BUILDING_FLAG_NONE             = 0,
	BUILDING_FLAG_SOURCE           = 0x1,
	BUILDING_FLAG_UPDATEPOWERLEVEL = 0x2,
};
flags_end(BuildingFlags, 0x4);

enum CameraFlags : uint32 // [LegoRR/LegoCamera.c|flags:0x4|type:uint]
{
	CAMERA_FLAG_NONE          = 0,
	CAMERA_FLAG_TILTRANGE     = 0x1,
	CAMERA_FLAG_ROTATIONRANGE = 0x2,
	CAMERA_FLAG_ZOOMRANGE     = 0x4,
	CAMERA_FLAG_FREEMOVEMENT  = 0x8,
	CAMERA_FLAG_FPSETUP       = 0x10,
};
flags_end(CameraFlags, 0x4);

enum Config_GlobFlags : uint32 // [Gods98/Memory.c|flags:0x4|type:uint]
{
	CONFIG_GLOB_FLAG_NONE          = 0,
	CONFIG_GLOB_FLAG_INITIALISED   = 0x1,
	CONFIG_GLOB_FLAG_LOADINGCONFIG = 0x2,
};
flags_end(Config_GlobFlags, 0x4);

enum Construction_ZoneFlags : uint32 // [LegoRR/Construction.c|flags:0x4|type:uint]
{
	CONSTRUCTION_FLAG_NONE      = 0,
	CONSTRUCTION_FLAG_READY     = 0x1,
	CONSTRUCTION_FLAG_LAYPATH   = 0x2,
	CONSTRUCTION_FLAG_REQUESTED = 0x4,
	CONSTRUCTION_FLAG_USESTUDS  = 0x8,
};
flags_end(Construction_ZoneFlags, 0x4);

enum Container_GlobFlags : uint32 // [Gods98/Containers.c|flags:0x4|type:uint] All flags used by the ResourceManager struct.
{
	CONTAINER_FLAG_NONE           = 0,
	CONTAINER_FLAG_INITIALISED    = 0x1,
	CONTAINER_FLAG_TRIGGERENABLED = 0x40,
};
flags_end(Container_GlobFlags, 0x4);

enum Container_TextureFlags : uint32 // [Gods98/Containers.c|flags:0x4|type:uint]
{
	CONTAINER_TEXTURE_NONE   = 0,
	CONTAINER_TEXTURE_NOLOAD = 0x1,
};
flags_end(Container_TextureFlags, 0x4);

enum ContainerFlags : uint32 // [Gods98/Containers.c|flags:0x4|type:uint]
{
	CONTAINER_FLAG_NONE             = 0,
	CONTAINER_FLAG_TRIGGERSAMPLE    = 0x2,
	CONTAINER_FLAG_MESHSWAPPED      = 0x4,
	CONTAINER_FLAG_HIDDEN           = 0x8,
	CONTAINER_FLAG_DEADREFERENCE    = 0x10,
	CONTAINER_FLAG_ANIMATIONSKIPPED = 0x20,
	CONTAINER_FLAG_HIDDEN2          = 0x80,
};
flags_end(ContainerFlags, 0x4);

enum CreatureFlags : uint32 // [LegoRR/Creature.c|flags:0x4|type:uint]
{
	CREATURE_FLAG_NONE   = 0,
	CREATURE_FLAG_SOURCE = 0x1,
};
flags_end(CreatureFlags, 0x4);

enum DependencyFlags : uint32 // [LegoRR/Dependencies.c|flags:0x4|type:uint]
{
	DEPENDENCY_FLAG_NONE        = 0,
	DEPENDENCY_FLAG_HITONCESTAY = 0x1,
	DEPENDENCY_FLAG_UNK_2       = 0x2,
	DEPENDENCY_FLAG_UNK_4       = 0x4,
	DEPENDENCY_FLAG_UNK_8       = 0x8,
	DEPENDENCY_FLAG_UNK_100     = 0x100,
};
flags_end(DependencyFlags, 0x4);

enum Detail_TransformFlags : uint8 // [LegoRR/Detail.c|flags:0x1|type:byte]
{
	DETAIL_TRANSFORM_FLAG_NONE   = 0,
	DETAIL_ROTATE_FLAG_X1_DEG90  = 0x1,
	DETAIL_ROTATE_FLAG_X1_DEGM90 = 0x2,
	DETAIL_ROTATE_FLAG_Y1_DEG90  = 0x4,
	DETAIL_ROTATE_FLAG_Y1_DEGM90 = 0x8,
	DETAIL_ROTATE_FLAG_Z1_DEG90  = 0x10,
	DETAIL_ROTATE_FLAG_Z1_DEGM90 = 0x20,
	DETAIL_TRANSLATE_FLAG_Y10    = 0x40,
	DETAIL_TRANSLATE_FLAG_YM10   = 0x80,
};
flags_end(Detail_TransformFlags, 0x1);

enum DirectionFlags : uint32 // [LegoRR/Lego.c|flags:0x4|type:uint]
{
	DIRECTION_FLAG_NONE = 0,
	DIRECTION_FLAG_N    = 0x1,
	DIRECTION_FLAG_E    = 0x2,
	DIRECTION_FLAG_NE   = 0x3,
	DIRECTION_FLAG_S    = 0x4,
	DIRECTION_FLAG_NS   = 0x5,
	DIRECTION_FLAG_SE   = 0x6,
	DIRECTION_FLAG_NSE  = 0x7,
	DIRECTION_FLAG_W    = 0x8,
	DIRECTION_FLAG_NW   = 0x9,
	DIRECTION_FLAG_EW   = 0xa,
	DIRECTION_FLAG_NEW  = 0xb,
	DIRECTION_FLAG_SW   = 0xc,
	DIRECTION_FLAG_NSW  = 0xd,
	DIRECTION_FLAG_SEW  = 0xe,
	DIRECTION_FLAG_NSEW = 0xf,
};
flags_end(DirectionFlags, 0x4);

enum Draw_GlobFlags : uint32 // [Gods98/Draw.c|flags:0x4|type:uint]
{
	DRAW_GLOB_FLAG_NONE        = 0,
	DRAW_GLOB_FLAG_INITIALISED = 0x1,
};
flags_end(Draw_GlobFlags, 0x4);

enum ElectricFence_GridFlags : uint32 // [LegoRR/ElectricFence.c|flags:0x4|type:uint]
{
	FENCEGRID_FLAG_NONE            = 0,
	FENCEGRID_DIRECTION_FLAG_UP    = 0x1,
	FENCEGRID_DIRECTION_FLAG_RIGHT = 0x2,
	FENCEGRID_DIRECTION_FLAG_DOWN  = 0x4,
	FENCEGRID_DIRECTION_FLAG_LEFT  = 0x8,
	FENCEGRID_DIRECTION_MASK       = 0xf,
	FENCEGRID_FLAG_UNK_100         = 0x100,
};
flags_end(ElectricFence_GridFlags, 0x4);

enum Encyclopedia_GlobFlags : uint32 // [LegoRR/Encyclopedia.c|flags:0x4|type:uint]
{
	ENCYCLOPEDIA_GLOB_FLAG_NONE      = 0,
	ENCYCLOPEDIA_GLOB_FLAG_ACTIVE    = 0x1,
	ENCYCLOPEDIA_GLOB_FLAG_NEEDSTEXT = 0x2,
};
flags_end(Encyclopedia_GlobFlags, 0x4);

enum FlicUserFlags : uint32 // [Gods98/Flic.c|flags:0x4|type:uint]
{
	FLICDISK      = 0,
	FLICMEMORY    = 0x1,
	FLICLOOPINGON = 0x2,
	FLICCATCHUPON = 0x4,
	FLICSOUNDOFF  = 0x8,
};
flags_end(FlicUserFlags, 0x4);

enum FlocksFlags : uint32 // [LegoRR/Flocks.c|flags:0x4|type:uint]
{
	FLOCKS_FLAG_NONE  = 0,
	FLOCKS_FLAG_UNK_1 = 0x1,
};
flags_end(FlocksFlags, 0x4);

enum FontFlags : uint32 // [Gods98/Fonts.c|flags:0x4|type:uint]
{
	FONT_FLAG_NONE          = 0,
	FONT_FLAG_INITIALISED   = 0x1,
	FONT_FLAG_WINDOWSET     = 0x2,
	FONT_FLAG_WINDOWWRAPPED = 0x4,
};
flags_end(FontFlags, 0x4);

enum Front_RockWipeFlags : uint32 // [LegoRR/Front.c|flags:0x4|type:uint]
{
	ROCKWIPE_FLAG_NONE      = 0,
	ROCKWIPE_FLAG_ANIMATING = 0x1,
	ROCKWIPE_FLAG_NOINPUT   = 0x2,
};
flags_end(Front_RockWipeFlags, 0x4);

enum GameFlags1 : uint32 // [LegoRR/Lego.c|flags:0x4|type:uint]
{
	GAME1_NONE                  = 0,
	GAME1_RADARON               = 0x2,
	GAME1_LEVELSTART            = 0x4,
	GAME1_MUSICPLAYING          = 0x8,
	GAME1_USESFX                = 0x10,
	GAME1_USEDETAIL             = 0x20,
	GAME1_SHOWFPS               = 0x40,
	GAME1_SHOWMEMORY            = 0x80,
	GAME1_MULTISELECTING        = 0x100,
	GAME1_MOUSEBUSY             = 0x200,
	GAME1_DDRAWCLEAR            = 0x400,
	GAME1_RENDERPANELS          = 0x800,
	GAME1_RADAR_MAPVIEW         = 0x1000,
	GAME1_RADAR_TRACKOBJECTVIEW = 0x2000,
	GAME1_RADAR_TRACKOBJECTLOST = 0x4000,
	GAME1_FOGCOLOURRGB          = 0x8000,
	GAME1_HIGHFOGCOLOURRGB      = 0x10000,
	GAME1_RADAR_NOTRACKOBJECT   = 0x20000,
	GAME1_VERTEXMODE            = 0x40000,
	GAME1_DYNAMICPM             = 0x80000,
	GAME1_FREEZEINTERFACE       = 0x100000,
	GAME1_CAMERAGOTO            = 0x200000,
	GAME1_ONLYBUILDONPATHS      = 0x400000,
	GAME1_ALWAYSROCKFALL        = 0x800000,
	GAME1_DEBUG_NONERPS         = 0x1000000,
	GAME1_PAUSED                = 0x2000000,
	GAME1_STREAMNERPSSPEACH     = 0x4000000,
	GAME1_LEVELENDING           = 0x8000000,
	GAME1_LASERTRACKER          = 0x10000000,
	GAME1_DEBUG_SHOWVERTEXMODE  = 0x20000000,
	GAME1_DEBUG_NOCLIP_FPS      = 0x40000000,
	GAME1_VERTEXLOCKONPOINTER   = 0x80000000,
};
flags_end(GameFlags1, 0x4);

enum GameFlags2 : uint32 // [LegoRR/Lego.c|flags:0x4|type:uint]
{
	GAME2_NONE                 = 0,
	GAME2_CALLTOARMS           = 0x1,
	GAME2_LEVELEXITING         = 0x2,
	GAME2_ATTACKDEFER          = 0x4,
	GAME2_SHOWDEBUGTOOLTIPS    = 0x8,
	GAME2_ALLOWDEBUGKEYS       = 0x10,
	GAME2_ALLOWEDITMODE        = 0x20,
	GAME2_MESSAGE_HASNEXT      = 0x40,
	GAME2_MESSAGE_HASREPEAT    = 0x80,
	GAME2_INOPTIONSMENU        = 0x100,
	GAME2_CAMERAMOVING         = 0x200,
	GAME2_MOUSE_INSIDEGAMEVIEW = 0x400,
	GAME2_MUSICREADY           = 0x800,
	GAME2_INMENU               = 0x1000,
	GAME2_NOMULTISELECT        = 0x2000,
	GAME2_MENU_HASNEXT         = 0x4000,
	GAME2_MENU_HASPREVIOUS     = 0x8000,
	GAME2_ALLOWRENAME          = 0x20000,
	GAME2_RECALLOLOBJECTS      = 0x40000,
	GAME2_GENERATESPIDERS      = 0x80000,
	GAME2_DISABLETOOLTIPSOUND  = 0x100000,
	GAME2_NOAUTOEAT            = 0x200000,
};
flags_end(GameFlags2, 0x4);

enum GameFlags3 : uint32 // [LegoRR/Lego.c|flags:0x4|type:uint] Flags for the current user action.
{
	GAME3_NONE          = 0,
	GAME3_ENCYCLOPEDIA  = 0x1,
	GAME3_LEGOMANGOTO   = 0x2,
	GAME3_VEHICLEGOTO   = 0x4,
	GAME3_PICKUPOBJECT  = 0x8,
	GAME3_LOADVEHICLE   = 0x10,
	GAME3_LEGOMANDIG    = 0x20,
	GAME3_VEHICLEDIG    = 0x40,
	GAME3_PLACEBUILDING = 0x80,
};
flags_end(GameFlags3, 0x4);

enum Graphics_DeviceFlags : uint32 // [Gods98/DirectDraw.c|flags:0x4|type:uint] Valid flag is actually shared: DIRECTDRAW_FLAG_VALID
{
	GRAPHICS_DEVICE_FLAG_NONE          = 0,
	GRAPHICS_DEVICE_FLAG_VALID         = 0x1,
	GRAPHICS_DEVICE_FLAG_DEPTH8        = 0x10,
	GRAPHICS_DEVICE_FLAG_DEPTH16       = 0x20,
	GRAPHICS_DEVICE_FLAG_DEPTH24       = 0x40,
	GRAPHICS_DEVICE_FLAG_DEPTH32       = 0x80,
	GRAPHICS_DEVICE_FLAG_ZBUFF8        = 0x100,
	GRAPHICS_DEVICE_FLAG_ZBUFF16       = 0x200,
	GRAPHICS_DEVICE_FLAG_ZBUFF24       = 0x400,
	GRAPHICS_DEVICE_FLAG_ZBUFF32       = 0x800,
	GRAPHICS_DEVICE_FLAG_COLOUR        = 0x1000,
	GRAPHICS_DEVICE_FLAG_HARDWARE      = 0x2000,
	GRAPHICS_DEVICE_FLAG_VIDEOTEXTURE  = 0x4000,
	GRAPHICS_DEVICE_FLAG_SYSTEMTEXTURE = 0x8000,
};
flags_end(Graphics_DeviceFlags, 0x4);

enum Graphics_DriverFlags : uint32 // [Gods98/DirectDraw.c|flags:0x4|type:uint] Valid flag is actually shared: DIRECTDRAW_FLAG_VALID
{
	GRAPHICS_DRIVER_FLAG_NONE     = 0,
	GRAPHICS_DRIVER_FLAG_VALID    = 0x1,
	GRAPHICS_DRIVER_FLAG_PRIMARY  = 0x10,
	GRAPHICS_DRIVER_FLAG_WINDOWOK = 0x20,
};
flags_end(Graphics_DriverFlags, 0x4);

enum Graphics_ModeFlags : uint32 // [Gods98/DirectDraw.c|flags:0x4|type:uint] Valid flag is actually shared: DIRECTDRAW_FLAG_VALID
{
	GRAPHICS_MODE_FLAG_NONE  = 0,
	GRAPHICS_MODE_FLAG_VALID = 0x1,
};
flags_end(Graphics_ModeFlags, 0x4);

enum HelpWindow_GlobFlags : uint32 // [LegoRR/HelpWindow.c|flags:0x4|type:uint]
{
	HELPWINDOW_GLOB_FLAG_NONE    = 0,
	HELPWINDOW_GLOB_FLAG_UNK_1   = 0x1,
	HELPWINDOW_GLOB_FLAG_UNK_2   = 0x2,
	HELPWINDOW_GLOB_FLAG_UNK_4   = 0x4,
	HELPWINDOW_GLOB_FLAG_UNK_8   = 0x8,
	HELPWINDOW_GLOB_FLAG_UNK_10  = 0x10,
	HELPWINDOW_GLOB_FLAG_UNK_20  = 0x20,
	HELPWINDOW_GLOB_FLAG_ENABLED = 0x40,
};
flags_end(HelpWindow_GlobFlags, 0x4);

enum ImageFlags : uint32 // [Gods98/Images.c|flags:0x4|type:uint]
{
	IMAGE_FLAG_NONE        = 0,
	IMAGE_FLAG_INITIALISED = 0x1,
	IMAGE_FLAG_TRANS       = 0x2,
	IMAGE_FLAG_TEXTURE     = 0x4,
};
flags_end(ImageFlags, 0x4);

enum Info_GlobFlags : uint32 // [LegoRR/Info.c|flags:0x4|type:uint]
{
	INFO_GLOB_FLAG_NONE          = 0,
	INFO_GLOB_FLAG_UNK_1         = 0x1,
	INFO_GLOB_FLAG_UNK_2         = 0x2,
	INFO_GLOB_FLAG_UNK_4         = 0x4,
	INFO_GLOB_FLAG_UNK_8         = 0x8,
	INFO_GLOB_FLAG_AUTOGAMESPEED = 0x10,
};
flags_end(Info_GlobFlags, 0x4);

enum InfoDataFlags : uint32 // [LegoRR/Info.c|flags:0x4|type:uint]
{
	INFOTYPE_FLAG_NONE            = 0,
	INFOTYPE_FLAG_CHANGEGAMESPEED = 0x10000,
	INFOTYPE_FLAG_UNK_20000       = 0x20000,
};
flags_end(InfoDataFlags, 0x4);

enum Interface_GlobFlags : uint32 // [LegoRR/Interface.c|flags:0x4|type:uint]
{
	INTERFACE_GLOB_FLAG_NONE     = 0,
	INTERFACE_GLOB_FLAG_UNK_4    = 0x4,
	INTERFACE_GLOB_FLAG_UNK_20   = 0x20,
	INTERFACE_GLOB_FLAG_UNK_40   = 0x40,
	INTERFACE_GLOB_FLAG_UNK_80   = 0x80,
	INTERFACE_GLOB_FLAG_UNK_100  = 0x100,
	INTERFACE_GLOB_FLAG_UNK_200  = 0x200,
	INTERFACE_GLOB_FLAG_UNK_400  = 0x400,
	INTERFACE_GLOB_FLAG_UNK_800  = 0x800,
	INTERFACE_GLOB_FLAG_UNK_1000 = 0x1000,
	INTERFACE_GLOB_FLAG_UNK_2000 = 0x2000,
	INTERFACE_GLOB_FLAG_UNK_4000 = 0x4000,
};
flags_end(Interface_GlobFlags, 0x4);

enum Interface_MenuItemFlags : uint32 // [LegoRR/Interface.c|flags:0x4|type:uint]
{
	INTERFACE_MENUITEM_FLAG_NONE  = 0,
	INTERFACE_MENUITEM_FLAG_UNK_1 = 0x1,
	INTERFACE_MENUITEM_FLAG_UNK_2 = 0x2,
	INTERFACE_MENUITEM_FLAG_FLASH = 0x4,
	INTERFACE_MENUITEM_FLAG_UNK_8 = 0x8,
};
flags_end(Interface_MenuItemFlags, 0x4);

enum LegoObject_AbilityFlags : uint32 // [LegoRR/LegoObject.c|flags:0x4|type:uint] These can be substituted for LiveFlags5
{
	ABILITY_FLAG_NONE     = 0,
	ABILITY_FLAG_PILOT    = 0x1,
	ABILITY_FLAG_SAILOR   = 0x2,
	ABILITY_FLAG_DRIVER   = 0x4,
	ABILITY_FLAG_DYNAMITE = 0x8,
	ABILITY_FLAG_REPAIR   = 0x10,
	ABILITY_FLAG_SCANNER  = 0x20,
};
flags_end(LegoObject_AbilityFlags, 0x4);

enum LegoObject_GlobFlags : uint32 // [LegoRR/LegoObject.c|flags:0x4|type:uint] LegoObject_GlobFlags, ReservedPool LiveObject INITFLAGS
{
	OBJECT_GLOB_FLAG_NONE             = 0,
	OBJECT_GLOB_FLAG_INITIALISED      = 0x1,
	OBJECT_GLOB_FLAG_REMOVING         = 0x2,
	OBJECT_GLOB_FLAG_POWERUPDATING    = 0x4,
	OBJECT_GLOB_FLAG_POWERNEEDSUPDATE = 0x8,
	OBJECT_GLOB_FLAG_UPDATING         = 0x10,
	OBJECT_GLOB_FLAG_LEVELENDING      = 0x20,
	OBJECT_GLOB_FLAG_CYCLEUNITS       = 0x40,
};
flags_end(LegoObject_GlobFlags, 0x4);

enum LegoObject_UpgradeFlags : uint32 // [LegoRR/LegoObject.c|flags:0x4|type:uint]
{
	UPGRADE_FLAG_NONE  = 0,
	UPGRADE_FLAG_DRILL = 0x1,
	UPGRADE_FLAG_SPEED = 0x2,
	UPGRADE_FLAG_SCAN  = 0x4,
	UPGRADE_FLAG_CARRY = 0x8,
	UPGRADE_FLAGS_ALL  = 0xf,
};
flags_end(LegoObject_UpgradeFlags, 0x4);

enum LightEffects_GlobFlags : uint32 // [LegoRR/LightEffects.c|flags:0x4|type:uint] LightEffects_GlobFlags, Flags for LightEffectsManager global variable @004ebec8
{
	LIGHTFX_GLOB_FLAG_NONE         = 0,
	LIGHTFX_GLOB_FLAG_HASBLINK     = 0x1,
	LIGHTFX_GLOB_FLAG_HASFADE      = 0x4,
	LIGHTFX_GLOB_FLAG_FADING       = 0x8,
	LIGHTFX_GLOB_FLAG_FADE_FORWARD = 0x10,
	LIGHTFX_GLOB_FLAG_FADE_REVERSE = 0x20,
	LIGHTFX_GLOB_FLAG_HASMOVE      = 0x40,
	LIGHTFX_GLOB_FLAG_MOVING       = 0x80,
	LIGHTFX_GLOB_FLAG_DISABLED     = 0x100,
	LIGHTFX_GLOB_FLAG_DIMOUT       = 0x200,
	LIGHTFX_GLOB_FLAG_DIMIN_DONE   = 0x400,
	LIGHTFX_GLOB_FLAG_DIMOUT_DONE  = 0x1000,
};
flags_end(LightEffects_GlobFlags, 0x4);

enum LiveFlags1 : uint32 // [LegoRR/LegoObject.c|flags:0x4|type:uint]
{
	LIVEOBJ1_NONE              = 0,
	LIVEOBJ1_MOVING            = 0x1,
	LIVEOBJ1_LIFTING           = 0x2,
	LIVEOBJ1_TURNING           = 0x4,
	LIVEOBJ1_DRILLING          = 0x8,
	LIVEOBJ1_DRILLINGSTART     = 0x10,
	LIVEOBJ1_UNUSED_20         = 0x20,
	LIVEOBJ1_REINFORCING       = 0x40,
	LIVEOBJ1_TURNRIGHT         = 0x80,
	LIVEOBJ1_EXPANDING         = 0x100,
	LIVEOBJ1_GATHERINGROCK     = 0x200,
	LIVEOBJ1_CARRYING          = 0x400,
	LIVEOBJ1_UNK_800           = 0x800,
	LIVEOBJ1_GETTINGHIT        = 0x1000,
	LIVEOBJ1_STORING           = 0x2000,
	LIVEOBJ1_UNK_4000          = 0x4000,
	LIVEOBJ1_WAITING           = 0x8000,
	LIVEOBJ1_UNK_10000         = 0x10000,
	LIVEOBJ1_ENTERING_WALLHOLE = 0x20000,
	LIVEOBJ1_CLEARING          = 0x40000,
	LIVEOBJ1_PLACING           = 0x80000,
	LIVEOBJ1_CRUMBLING         = 0x100000,
	LIVEOBJ1_TELEPORTINGDOWN   = 0x200000,
	LIVEOBJ1_TELEPORTINGUP     = 0x400000,
	LIVEOBJ1_RUNNINGAWAY       = 0x800000,
	LIVEOBJ1_REPAIRDRAINING    = 0x1000000,
	LIVEOBJ1_CAUGHTINWEB       = 0x2000000,
	LIVEOBJ1_SLIPPING          = 0x4000000,
	LIVEOBJ1_SCAREDBYPLAYER    = 0x8000000,
	LIVEOBJ1_UNUSED_10000000   = 0x10000000,
	LIVEOBJ1_RESTING           = 0x20000000,
	LIVEOBJ1_EATING            = 0x40000000,
	LIVEOBJ1_CANTDO            = 0x80000000,
};
flags_end(LiveFlags1, 0x4);

enum LiveFlags2 : uint32 // [LegoRR/LegoObject.c|flags:0x4|type:uint]
{
	LIVEOBJ2_NONE                 = 0,
	LIVEOBJ2_THROWING             = 0x1,
	LIVEOBJ2_THROWN               = 0x2,
	LIVEOBJ2_UNK_4                = 0x4,
	LIVEOBJ2_DRIVING              = 0x8,
	LIVEOBJ2_UNK_10               = 0x10,
	LIVEOBJ2_UNK_20               = 0x20,
	LIVEOBJ2_UNK_40               = 0x40,
	LIVEOBJ2_UNK_80               = 0x80,
	LIVEOBJ2_UNK_100              = 0x100,
	LIVEOBJ2_BUILDPATH            = 0x200,
	LIVEOBJ2_TRAINING             = 0x400,
	LIVEOBJ2_UNK_800              = 0x800,
	LIVEOBJ2_DAMAGE_UNK_1000      = 0x1000,
	LIVEOBJ2_SHOWDAMAGENUMBERS    = 0x2000,
	LIVEOBJ2_PUSHED               = 0x4000,
	LIVEOBJ2_UPGRADING            = 0x8000,
	LIVEOBJ2_TRIGGERFRAMECALLBACK = 0x10000,
	LIVEOBJ2_UNK_20000            = 0x20000,
	LIVEOBJ2_UNK_40000            = 0x40000,
	LIVEOBJ2_UNK_80000            = 0x80000,
	LIVEOBJ2_UNK_100000           = 0x100000,
	LIVEOBJ2_UNK_200000           = 0x200000,
	LIVEOBJ2_FIRINGLASER          = 0x400000,
	LIVEOBJ2_FIRINGPUSHER         = 0x800000,
	LIVEOBJ2_FIRINGFREEZER        = 0x1000000,
	LIVEOBJ2_ACTIVEELECTRICFENCE  = 0x2000000,
	LIVEOBJ2_UNK_4000000          = 0x4000000,
	LIVEOBJ2_FROZEN               = 0x8000000,
	LIVEOBJ2_RECHARGING           = 0x10000000,
	LIVEOBJ2_UNK_20000000         = 0x20000000,
	LIVEOBJ2_DAMAGESHAKING        = 0x40000000,
	LIVEOBJ2_UNK_80000000         = 0x80000000,
};
flags_end(LiveFlags2, 0x4);

enum LiveFlags3 : uint32 // [LegoRR/LegoObject.c|flags:0x4|type:uint]
{
	LIVEOBJ3_NONE                = 0,
	LIVEOBJ3_UNK_1               = 0x1,
	LIVEOBJ3_CANDIG              = 0x2,
	LIVEOBJ3_CANREINFORCE        = 0x4,
	LIVEOBJ3_CANTURN             = 0x8,
	LIVEOBJ3_CANFIRSTPERSON      = 0x10,
	LIVEOBJ3_CANCARRY            = 0x20,
	LIVEOBJ3_CANPICKUP           = 0x40,
	LIVEOBJ3_CANYESSIR           = 0x80,
	LIVEOBJ3_CANSELECT           = 0x100,
	LIVEOBJ3_UNK_200             = 0x200,
	LIVEOBJ3_UNK_400             = 0x400,
	LIVEOBJ3_UNUSED_800          = 0x800,
	LIVEOBJ3_CENTERBLOCKIDLE     = 0x1000,
	LIVEOBJ3_UNK_2000            = 0x2000,
	LIVEOBJ3_UNK_4000            = 0x4000,
	LIVEOBJ3_CANDYNAMITE         = 0x8000,
	LIVEOBJ3_UNK_10000           = 0x10000,
	LIVEOBJ3_SIMPLEOBJECT        = 0x20000,
	LIVEOBJ3_CANDAMAGE           = 0x40000,
	LIVEOBJ3_UPGRADEPART         = 0x80000,
	LIVEOBJ3_ALLOWCULLING_UNK    = 0x100000,
	LIVEOBJ3_SELECTED            = 0x200000,
	LIVEOBJ3_AITASK_UNK_400000   = 0x400000,
	LIVEOBJ3_REMOVING            = 0x800000,
	LIVEOBJ3_UNK_1000000         = 0x1000000,
	LIVEOBJ3_UNK_2000000         = 0x2000000,
	LIVEOBJ3_CANGATHER           = 0x4000000,
	LIVEOBJ3_MONSTER_UNK_8000000 = 0x8000000,
	LIVEOBJ3_CANROUTERUBBLE      = 0x10000000,
	LIVEOBJ3_HASPOWER            = 0x20000000,
	LIVEOBJ3_UNK_40000000        = 0x40000000,
	LIVEOBJ3_POWEROFF            = 0x80000000,
};
flags_end(LiveFlags3, 0x4);

enum LiveFlags4 : uint32 // [LegoRR/LegoObject.c|flags:0x4|type:uint]
{
	LIVEOBJ4_NONE               = 0,
	LIVEOBJ4_LASERTRACKERMODE   = 0x1,
	LIVEOBJ4_DOUBLESELECTREADY  = 0x2,
	LIVEOBJ4_UNK_4              = 0x4,
	LIVEOBJ4_UNK_8              = 0x8,
	LIVEOBJ4_UNK_10             = 0x10,
	LIVEOBJ4_CALLTOARMS         = 0x20,
	LIVEOBJ4_DOCKOCCUPIED       = 0x40,
	LIVEOBJ4_ENTRANCEOCCUPIED   = 0x80,
	LIVEOBJ4_USEDBYCONSTRUCTION = 0x100,
	LIVEOBJ4_DONTSHOWHELPWINDOW = 0x200,
	LIVEOBJ4_CRYORECOSTDROPPED  = 0x800,
	LIVEOBJ4_UNK_1000           = 0x1000,
	LIVEOBJ4_UNK_2000           = 0x2000,
	LIVEOBJ4_UNK_4000           = 0x4000,
	LIVEOBJ4_UNK_8000           = 0x8000,
	LIVEOBJ4_UNK_10000          = 0x10000,
	LIVEOBJ4_UNK_20000          = 0x20000,
	LIVEOBJ4_UNK_40000          = 0x40000,
	LIVEOBJ4_ENGINESOUNDPLAYING = 0x80000,
	LIVEOBJ4_DRILLSOUNDPLAYING  = 0x100000,
	LIVEOBJ4_UNK_200000         = 0x200000,
	LIVEOBJ4_UNK_400000         = 0x400000,
};
flags_end(LiveFlags4, 0x4);

enum LiveFlags5 : uint32 // [LegoRR/LegoObject.c|flags:0x4|type:uint] These flags contain LiveObject abilities, and are the one of the fields stored/restored with ObjectRecall.
{
	LIVEOBJ5_NONE             = 0,
	LIVEOBJ5_ABILITY_PILOT    = 0x1,
	LIVEOBJ5_ABILITY_SAILOR   = 0x2,
	LIVEOBJ5_ABILITY_DRIVER   = 0x4,
	LIVEOBJ5_ABILITY_DYNAMITE = 0x8,
	LIVEOBJ5_ABILITY_REPAIR   = 0x10,
	LIVEOBJ5_ABILITY_SCANNER  = 0x20,
};
flags_end(LiveFlags5, 0x4);

enum Loader_GlobFlags : uint32 // [LegoRR/Loader.c|flags:0x4|type:uint]
{
	LOADER_GLOB_FLAG_NONE    = 0,
	LOADER_GLOB_FLAG_ENABLED = 0x1,
};
flags_end(Loader_GlobFlags, 0x4);

enum LWSRFFLAGS : uint32 // [Gods98/Lwt.c|flags:0x4|type:uint]
{
	SFM_LUMINOUS        = 0x1,
	SFM_OUTLINE         = 0x2,
	SFM_SMOOTHING       = 0x4,
	SFM_COLORHIGHLIGHTS = 0x8,
	SFM_COLORFILTER     = 0x10,
	SFM_OPAQUEEDGE      = 0x20,
	SFM_TRANSPARENTEDGE = 0x40,
	SFM_SHARPTERMINATOR = 0x80,
	SFM_DOUBLESIDED     = 0x100,
	SFM_ADDITIVE        = 0x200,
};
flags_end(LWSRFFLAGS, 0x4);

enum LWTEXFLAGS : uint32 // [Gods98/Lwt.c|flags:0x4|type:uint]
{
	TFM_AXIS_X         = 0x1,
	TFM_AXIS_Y         = 0x2,
	TFM_AXIS_Z         = 0x4,
	TFM_WORLD_COORD    = 0x8,
	TFM_NEGATIVE_IMAGE = 0x10,
	TFM_PIXEL_BLENDING = 0x20,
	TFM_ANTIALIASING   = 0x40,
	TFM_SEQUENCE       = 0x80,
};
flags_end(LWTEXFLAGS, 0x4);

enum LWTEXMAPTYPE : uint32 // [Gods98/Lwt.c|flags:0x4|type:uint]
{
	MT_PLANAR      = 0,
	MT_CYLINDRICAL = 0x1,
	MT_SPHERICAL   = 0x2,
	MT_MAX         = 0x3,
};
flags_end(LWTEXMAPTYPE, 0x4);

enum MainCLFlags : uint32 // [LegoRR/Lego.c|flags:0x4|type:uint] Flags specified by the "-flags #" command line argument (which has to be in decimal...)
{
	CL_FLAG_NONE      = 0,
	CL_FLAG_BLOCKFADE = 0x8000,
};
flags_end(MainCLFlags, 0x4);

enum MainFlags : uint32 // [Gods98/Main.c|flags:0x4|type:uint] Command line argument flags set when starting the game
{
	MAIN_FLAG_NONE                   = 0,
	MAIN_FLAG_UPDATED                = 0x1,
	MAIN_FLAG_FULLSCREEN             = 0x2,
	MAIN_FLAG_VIDEOTEXTURE           = 0x4,
	MAIN_FLAG_MIPMAPENABLED          = 0x8,
	MAIN_FLAG_PAUSED                 = 0x10,
	MAIN_FLAG_DONTMANAGETEXTURES     = 0x20,
	MAIN_FLAG_BEST                   = 0x40,
	MAIN_FLAG_DUMPMODE               = 0x80,
	MAIN_FLAG_WINDOW                 = 0x100,
	MAIN_FLAG_STARTLEVEL             = 0x200,
	MAIN_FLAG_CLEANSAVES             = 0x400,
	MAIN_FLAG_SAVELANGFILE           = 0x800,
	MAIN_FLAG_LANGDUMPUNKNOWN        = 0x1000,
	MAIN_FLAG_DEBUGMODE              = 0x2000,
	MAIN_FLAG_DUALMOUSE              = 0x4000,
	MAIN_FLAG_DEBUGCOMPLETE          = 0x8000,
	MAIN_FLAG_TESTERCALL             = 0x10000,
	MAIN_FLAG_LEVELSOPEN             = 0x20000,
	MAIN_FLAG_FORCETEXTUREMANAGEMENT = 0x40000,
	MAIN_FLAG_FORCEVERTEXFOG         = 0x80000,
	MAIN_FLAG_REDUCESAMPLES          = 0x100000,
	MAIN_FLAG_SHOWVERSION            = 0x200000,
	MAIN_FLAG_REDUCEANIMATION        = 0x400000,
	MAIN_FLAG_REDUCEPROMESHES        = 0x800000,
	MAIN_FLAG_REDUCEFLICS            = 0x1000000,
	MAIN_FLAG_REDUCEIMAGES           = 0x2000000,
};
flags_end(MainFlags, 0x4);

enum Map3D_BlockFlags : uint8 // [LegoRR/Map3D.c|flags:0x1|type:byte] Flags for SurfaceMapStruct_28->byte_19
{
	MAP3DBLOCK_FLAG_NONE           = 0,
	MAP3DBLOCK_FLAG_ROTATED        = 0x1,
	MAP3DBLOCK_FLAG_VERTEXMODIFIED = 0x4,
	MAP3DBLOCK_FLAG_VERTEXLEVELED  = 0x8,
	MAP3DBLOCK_FLAG_UVWOBBLES      = 0x10,
	MAP3DBLOCK_FLAG_UNK_20         = 0x20,
	MAP3DBLOCK_FLAG_UNK_40         = 0x40,
};
flags_end(Map3D_BlockFlags, 0x1);

enum Map3D_TransitionFlags : uint8 // [LegoRR/Map3D.c|flags:0x1|type:byte]
{
	MAP3DTRANS_FLAG_NONE = 0,
	MAP3DTRANS_FLAG_USED = 0x1,
};
flags_end(Map3D_TransitionFlags, 0x1);

enum Map3DFlags : uint32 // [LegoRR/Map3D.c|flags:0x4|type:uint]
{
	MAP3D_FLAG_NONE           = 0,
	MAP3D_FLAG_VERTEXMODIFIED = 0x2,
	MAP3D_FLAG_EMISSIVE_4     = 0x4,
};
flags_end(Map3DFlags, 0x4);

enum Mem_HandleFlags : uint32 // [Gods98/Memory.c|flags:0x4|type:uint] Flags for SharedBuffer struct
{
	MEMORY_HANDLE_FLAG_NONE = 0,
	MEMORY_HANDLE_FLAG_USED = 0x1,
};
flags_end(Mem_HandleFlags, 0x4);

enum MenuFlags : uint32 // [LegoRR/FrontEnd.c|flags:0x4|type:uint]
{
	MENU_FLAG_NONE        = 0,
	MENU_FLAG_HASPOSITION = 0x1,
	MENU_FLAG_CANSCROLL   = 0x2,
};
flags_end(MenuFlags, 0x4);

enum MenuItem_SelectItemFlags : uint32 // [LegoRR/FrontEnd.c|flags:0x4|type:uint]
{
	SELECTITEM_FLAG_NONE      = 0,
	SELECTITEM_FLAG_HASBANNER = 0x1,
	SELECTITEM_FLAG_HASIMAGE  = 0x2,
	SELECTITEM_FLAG_ENABLED   = 0x4,
};
flags_end(MenuItem_SelectItemFlags, 0x4);

enum MeshLODFlags : uint32 // [LegoRR/MeshLOD.c|flags:0x4|type:uint]
{
	MESHLOD_FLAG_NONE     = 0,
	MESHLOD_FLAG_CLONED   = 0x1,
	MESHLOD_FLAG_MEMBLOCK = 0x2,
};
flags_end(MeshLODFlags, 0x4);

enum Objective_GlobFlags : uint32 // [LegoRR/Objective.c|flags:0x4|type:uint] STATUSREADY means next status has been set, but has not been "updated" yet? HITTIMEFAIL is unused and replaced by SHOWACHIEVEDADVISOR.
{
	OBJECTIVE_GLOB_FLAG_NONE                = 0,
	OBJECTIVE_GLOB_FLAG_BRIEFING            = 0x1,
	OBJECTIVE_GLOB_FLAG_COMPLETED           = 0x2,
	OBJECTIVE_GLOB_FLAG_FAILED              = 0x4,
	OBJECTIVE_GLOB_FLAG_STATUSREADY         = 0x8,
	OBJECTIVE_GLOB_FLAG_SHOWBRIEFINGADVISOR = 0x10,
	OBJECTIVE_GLOB_FLAG_SHOWACHIEVEDADVISOR = 0x20,
	OBJECTIVE_GLOB_FLAG_HITTIMEFAIL         = 0x40,
	OBJECTIVE_GLOB_FLAG_SHOWFAILEDADVISOR   = 0x80,
	OBJECTIVE_GLOB_FLAG_CRYSTAL             = 0x100,
	OBJECTIVE_GLOB_FLAG_ORE                 = 0x200,
	OBJECTIVE_GLOB_FLAG_BLOCK               = 0x400,
	OBJECTIVE_GLOB_FLAG_TIMER               = 0x800,
	OBJECTIVE_GLOB_FLAG_CONSTRUCTION        = 0x1000,
};
flags_end(Objective_GlobFlags, 0x4);

enum ObjInfo_GlobFlags : uint32 // [LegoRR/ObjInfo.c|flags:0x4|type:uint]
{
	OBJINFO_GLOB_FLAG_NONE               = 0,
	OBJINFO_GLOB_FLAG_HUNGERIMAGES       = 0x1,
	OBJINFO_GLOB_FLAG_HEALTHBAR          = 0x2,
	OBJINFO_GLOB_FLAG_HEALTHBAR_VERTICAL = 0x8,
	OBJINFO_GLOB_FLAG_BUBBLEIMAGES       = 0x10,
};
flags_end(ObjInfo_GlobFlags, 0x4);

enum Panel_GlobFlags : uint32 // [LegoRR/Panels.c|flags:0x4|type:uint] Todo...
{
	PANEL_GLOB_FLAG_NONE                 = 0,
	PANEL_GLOB_FLAG_ROTATECONTROL_ACTIVE = 0x1,
	PANEL_GLOB_FLAG_PRIORITIES_TOP       = 0x2,
	PANEL_GLOB_FLAG_PRIORITIES_UP        = 0x4,
	PANEL_GLOB_FLAG_ROTATECONTROL_UP     = 0x10,
	PANEL_GLOB_FLAG_ROTATECONTROL_DOWN   = 0x20,
	PANEL_GLOB_FLAG_ROTATECONTROL_LEFT   = 0x40,
	PANEL_GLOB_FLAG_ROTATECONTROL_RIGHT  = 0x80,
};
flags_end(Panel_GlobFlags, 0x4);

enum PanelButtonFlags : uint32 // [LegoRR/Panels.c|flags:0x4|type:uint]
{
	PANELBUTTON_FLAG_NONE              = 0,
	PANELBUTTON_FLAG_HOVER             = 0x2,
	PANELBUTTON_FLAG_DOWN              = 0x4,
	PANELBUTTON_FLAG_TOGGLED           = 0x8,
	PANELBUTTON_FLAG_HIDDEN            = 0x10,
	PANELBUTTON_FLAG_TOGGLEABLE        = 0x20,
	PANELBUTTON_FLAG_UNUSED_HOVERFLASH = 0x40,
};
flags_end(PanelButtonFlags, 0x4);

enum PanelDataFlags : uint32 // [LegoRR/Panels.c|flags:0x4|type:uint] Todo...
{
	PANEL_FLAG_NONE     = 0,
	PANEL_FLAG_HASIMAGE = 0x1,
	PANEL_FLAG_OPEN     = 0x2,
	PANEL_FLAG_CLOSED   = 0x4,
	PANEL_FLAG_SLIDING  = 0x8,
};
flags_end(PanelDataFlags, 0x4);

enum Priorities_GlobFlags : uint32 // [LegoRR/Priorities.c|flags:0x4|type:uint]
{
	PRIORITIES_GLOB_FLAG_NONE    = 0,
	PRIORITIES_GLOB_FLAG_HOVER   = 0x1,
	PRIORITIES_GLOB_FLAG_PRESSED = 0x2,
};
flags_end(Priorities_GlobFlags, 0x4);

enum RewardItemFlags : uint32 // [LegoRR/Rewards.c|flags:0x4|type:uint]
{
	REWARDITEM_FLAG_NONE               = 0,
	REWARDITEM_FLAG_VALUETEXT          = 0x1,
	REWARDITEM_FLAG_IMAGES             = 0x2,
	REWARDITEM_FLAG_FLIC               = 0x4,
	REWARDITEM_FLAG_NAMETEXT           = 0x10,
	REWARDITEM_FLAG_NAMETEXT_HALFTRANS = 0x20,
	REWARDITEM_FLAG_BOXIMAGES          = 0x40,
};
flags_end(RewardItemFlags, 0x4);

enum RewardScrollFlags : uint32 // [LegoRR/Rewards.c|flags:0x4|type:uint]
{
	REWARDSCROLL_NONE  = 0,
	REWARDSCROLL_UNK_1 = 0x1,
	REWARDSCROLL_UNK_2 = 0x2,
};
flags_end(RewardScrollFlags, 0x4);

enum RewardScrollLabelFlags : uint32 // [LegoRR/Rewards.c|flags:0x4|type:uint]
{
	REWARDSCROLL_LABEL_NONE     = 0,
	REWARDSCROLL_LABEL_CENTERED = 0x1,
	REWARDSCROLL_LABEL_NOSCROLL = 0x2,
};
flags_end(RewardScrollLabelFlags, 0x4);

enum RoofFlags : uint32 // [LegoRR/Roof.c|flags:0x4|type:uint]
{
	ROOF_FLAG_NONE          = 0,
	ROOF_FLAG_HIDDEN        = 0x1,
	ROOF_FLAG_NEEDUPDATE    = 0x2,
	ROOF_FLAG_SHIFTVERTICES = 0x4,
};
flags_end(RoofFlags, 0x4);

enum RouteFlags : uint8 // [LegoRR/LegoObject.c|flags:0x1|type:byte]
{
	ROUTE_FLAG_NONE         = 0,
	ROUTE_DIRECTION_MASK    = 0x3,
	ROUTE_FLAG_GOTOBUILDING = 0x4,
	ROUTE_FLAG_UNK_8        = 0x8,
	ROUTE_UNK_MASK_c        = 0xc,
	ROUTE_FLAG_UNK_10       = 0x10,
	ROUTE_FLAG_UNK_20       = 0x20,
	ROUTE_FLAG_RUNAWAY      = 0x40,
};
flags_end(RouteFlags, 0x1);

enum SaveRewardFlags : uint32 // [LegoRR/Rewards.c|flags:0x4|type:uint]
{
	SAVEREWARD_FLAG_NONE      = 0,
	SAVEREWARD_FLAG_COMPLETED = 0x1,
	SAVEREWARD_FLAG_TUTORIAL  = 0x2,
};
flags_end(SaveRewardFlags, 0x4);

enum SFX_GlobFlags : uint32 // [LegoRR/SFX.c|flags:0x4|type:uint]
{
	SFX_GLOB_FLAG_NONE         = 0,
	SFX_GLOB_FLAG_SOUNDON      = 0x1,
	SFX_GLOB_FLAG_POPULATEMODE = 0x2,
	SFX_GLOB_FLAG_QUEUEMODE    = 0x8,
};
flags_end(SFX_GlobFlags, 0x4);

enum SFX_InstanceFlags : uint32 // [LegoRR/SFX.c|flags:0x4|type:uint]
{
	SFX_INSTANCE_FLAG_NONE    = 0,
	SFX_INSTANCE_FLAG_SOUND3D = 0x1,
	SFX_INSTANCE_FLAG_LOOPING = 0x2,
	SFX_INSTANCE_FLAG_ONFRAME = 0x4,
};
flags_end(SFX_InstanceFlags, 0x4);

enum SmokeFlags : uint32 // [LegoRR/Smoke.c|flags:0x4|type:uint] SMOKE_FLAG_UNK_4 is hopelessly broken, and impossible to reverse.
{
	SMOKE_FLAG_NONE         = 0,
	SMOKE_FLAG_HIDDEN       = 0x1,
	SMOKE_FLAG_OWNCONTAINER = 0x2,
	SMOKE_FLAG_BROKEN_UNK_4 = 0x4,
	SMOKE_FLAG_REPEATCOUNT  = 0x8,
	SMOKE_FLAG_REPEATEND    = 0x10,
	SMOKE_FLAG_SFXFAILED    = 0x20,
};
flags_end(SmokeFlags, 0x4);

enum Sound3DFlags : uint32 // [LegoRR/SFX.c|flags:0x4|type:uint]
{
	SAMPLE_NONE     = 0,
	SAMPLE_ISUSED   = 0x1,
	SAMPLE_VOLUME   = 0x2,
	SAMPLE_MULTIPLE = 0x4,
	SAMPLE_STREAMED = 0x8,
};
flags_end(Sound3DFlags, 0x4);

enum SpiderWeb_BlockFlags : uint32 // [LegoRR/SpiderWeb.c|flags:0x4|type:uint]
{
	BLOCKWEB_FLAG_NONE   = 0,
	BLOCKWEB_FLAG_ACTIVE = 0x100,
};
flags_end(SpiderWeb_BlockFlags, 0x4);

enum StatsFlags1 : uint32 // [LegoRR/Stats.c|flags:0x4|type:uint]
{
	STATS1_NONE                  = 0,
	STATS1_SINGLEWIDTHDIG        = 0x1,
	STATS1_PROCESSORE            = 0x2,
	STATS1_PROCESSCRYSTAL        = 0x4,
	STATS1_STOREOBJECTS          = 0x8,
	STATS1_SMALLTELEPORTER       = 0x10,
	STATS1_BIGTELEPORTER         = 0x20,
	STATS1_WATERTELEPORTER       = 0x40,
	STATS1_COLLRADIUS            = 0x80,
	STATS1_COLLBOX               = 0x100,
	STATS1_CAUSESLIP             = 0x200,
	STATS1_RANDOMMOVE            = 0x400,
	STATS1_CANSCARE              = 0x800,
	STATS1_RANDOMENTERWALL       = 0x1000,
	STATS1_SCAREDBYPLAYER        = 0x2000,
	STATS1_SNAXULIKE             = 0x4000,
	STATS1_GRABMINIFIGURE        = 0x8000,
	STATS1_CANCLEARRUBBLE        = 0x10000,
	STATS1_CANBEDRIVEN           = 0x20000,
	STATS1_CANSCARESCORPION      = 0x40000,
	STATS1_CANSTEAL              = 0x80000,
	STATS1_TOOLSTORE             = 0x100000,
	STATS1_FLOCKS                = 0x200000,
	STATS1_FLOCKS_DEBUG          = 0x400000,
	STATS1_FLOCKS_SMOOTH         = 0x800000,
	STATS1_CROSSWATER            = 0x1000000,
	STATS1_CROSSLAND             = 0x2000000,
	STATS1_FLOCKS_ONGROUND       = 0x4000000,
	STATS1_FLOCKS_QUICKDESTROY   = 0x8000000,
	STATS1_FLOCKS_ANIMATEBYPITCH = 0x10000000,
	STATS1_ROUTEAVOIDANCE        = 0x20000000,
	STATS1_BUMPDAMAGE            = 0x40000000,
	STATS1_MANTELEPORTER         = 0x80000000,
};
flags_end(StatsFlags1, 0x4);

enum StatsFlags2 : uint32 // [LegoRR/Stats.c|flags:0x4|type:uint]
{
	STATS2_NONE                   = 0,
	STATS2_SCAREDBYBIGBANGS       = 0x1,
	STATS2_UPGRADEBUILDING        = 0x2,
	STATS2_TRAINPILOT             = 0x4,
	STATS2_TRAINSAILOR            = 0x8,
	STATS2_TRAINDRIVER            = 0x10,
	STATS2_TRAINDYNAMITE          = 0x20,
	STATS2_TRAINREPAIR            = 0x40,
	STATS2_TRAINSCANNER           = 0x80,
	STATS2_TRACKER                = 0x100,
	STATS2_GENERATEPOWER          = 0x200,
	STATS2_SELFPOWERED            = 0x400,
	STATS2_POWERBUILDING          = 0x600,
	STATS2_USEBIGTELEPORTER       = 0x800,
	STATS2_USESMALLTELEPORTER     = 0x1000,
	STATS2_USEWATERTELEPORTER     = 0x2000,
	STATS2_ATTACKPATHS            = 0x4000,
	STATS2_SPLITONZEROHEALTH      = 0x8000,
	STATS2_CANBEHITBYFENCE        = 0x10000,
	STATS2_CANDOUBLESELECT        = 0x20000,
	STATS2_CANBESHOTAT            = 0x40000,
	STATS2_DRAINPOWER             = 0x80000,
	STATS2_USEHOLES               = 0x100000,
	STATS2_CROSSLAVA              = 0x200000,
	STATS2_USELEGOMANTELEPORTER   = 0x400000,
	STATS2_DAMAGECAUSESCALLTOARMS = 0x800000,
	STATS2_CANFREEZE              = 0x1000000,
	STATS2_CANLASER               = 0x2000000,
	STATS2_CANPUSH                = 0x4000000,
	STATS2_DONTSHOWDAMAGE         = 0x8000000,
	STATS2_REMOVEREINFORCEMENT    = 0x10000000,
	STATS2_DONTSHOWONRADAR        = 0x20000000,
	STATS2_INVISIBLEDRIVER        = 0x40000000,
	STATS2_UNSELECTABLE           = 0x80000000,
};
flags_end(StatsFlags2, 0x4);

enum StatsFlags3 : uint32 // [LegoRR/Stats.c|flags:0x4|type:uint]
{
	STATS3_NONE                = 0,
	STATS3_CARRYVEHICLES       = 0x1,
	STATS3_VEHICLECANBECARRIED = 0x2,
	STATS3_CANSTRAFE           = 0x4,
	STATS3_CLASSASLARGE        = 0x8,
	STATS3_GETOUTATLAND        = 0x10,
	STATS3_GETINATLAND         = 0x20,
	STATS3_TAKECARRYINGDRIVERS = 0x40,
	STATS3_SHOWHEALTHBAR       = 0x80,
	STATS3_NEEDSPILOT          = 0x100,
	STATS3_ENTERTOOLSTORE      = 0x200,
};
flags_end(StatsFlags3, 0x4);

enum TeleportObjectType : uint32 // [LegoRR/Teleporter.c|flags:0x4|type:uint|tags:FLAGASENUM]
{
	TELEPORT_SERVIVE_NONE          = 0,
	TELEPORT_SERVIVE_VEHICLE       = 0x1,
	TELEPORT_SERVIVE_MINIFIGURE    = 0x2,
	TELEPORT_SERVIVE_ROCKMONSTER   = 0x4,
	TELEPORT_SERVIVE_BUILDING      = 0x8,
	TELEPORT_SERVIVE_BOULDER       = 0x10,
	TELEPORT_SERVIVE_POWERCRYSTAL  = 0x20,
	TELEPORT_SERVIVE_ORE           = 0x40,
	TELEPORT_SERVIVE_DYNAMITE      = 0x80,
	TELEPORT_SERVIVE_BARRIER       = 0x100,
	TELEPORT_SERVIVE_UPGRADEPART   = 0x200,
	TELEPORT_SERVIVE_ELECTRICFENCE = 0x400,
	TELEPORT_SERVIVE_SPIDERWEB     = 0x800,
	TELEPORT_SERVIVE_OOHSCARY      = 0x1000,
};
flags_end(TeleportObjectType, 0x4);

enum Text_GlobFlags : uint32 // [LegoRR/Text.c|flags:0x4|type:uint]
{
	TEXT_GLOB_FLAG_NONE  = 0,
	TEXT_GLOB_FLAG_UNK_1 = 0x1,
	TEXT_GLOB_FLAG_UNK_4 = 0x4,
};
flags_end(Text_GlobFlags, 0x4);

enum ToolTipFlags : uint32 // [LegoRR/ToolTip.c|flags:0x4|type:uint] Note flags 0x1 and 0x2 are indistinguishable from one another.
{
	TOOLTIP_FLAG_NONE         = 0,
	TOOLTIP_FLAG_ENABLED1     = 0x1,
	TOOLTIP_FLAG_ENABLED2     = 0x2,
	TOOLTIP_FLAG_ACTIVE       = 0x4,
	TOOLTIP_FLAG_IMAGECONTENT = 0x8,
	TOOLTIP_FLAG_RIGHTALIGN   = 0x10,
};
flags_end(ToolTipFlags, 0x4);

enum TutorialFlags : uint32 // [LegoRR/NERPs.c|flags:0x4|type:uint]
{
	TUTORIAL_NONE               = 0,
	TUTORIAL_FLAG_NOICONS       = 0x1,
	TUTORIAL_FLAG_NOBLOCKACTION = 0x2,
	TUTORIAL_FLAG_NOMAP         = 0x4,
	TUTORIAL_FLAG_NOOBJECTS     = 0x8,
	TUTORIAL_FLAG_NORADAR       = 0x10,
	TUTORIAL_FLAG_NOOPTIONS     = 0x20,
	TUTORIAL_FLAG_NOPRIORITIES  = 0x40,
	TUTORIAL_FLAG_NOCALLTOARMS  = 0x80,
	TUTORIAL_FLAG_NOINFO        = 0x100,
	TUTORIAL_FLAG_NOMULTISELECT = 0x200,
	TUTORIAL_FLAG_NOCYCLEUNITS  = 0x400,
	TUTORIAL_FLAG_NOHELPWINDOW  = 0x800,
	TUTORIAL_FLAG_NOCAMERA      = 0x1000,
};
flags_end(TutorialFlags, 0x4);

enum VehicleFlags : uint32 // [LegoRR/Vehicle.c|flags:0x4|type:uint]
{
	VEHICLE_FLAG_NONE        = 0,
	VEHICLE_FLAG_SOURCE      = 0x1,
	VEHICLE_FLAG_HIDDEN      = 0x2,
	VEHICLE_FLAG_NOACTIVITY1 = 0x4,
	VEHICLE_FLAG_HOLDMISSING = 0x8,
};
flags_end(VehicleFlags, 0x4);

enum Wad_EntryFlags : uint32 // [Gods98/Wad.c|flags:0x4|type:uint]
{
	WADENTRY_FLAG_NONE         = 0,
	WADENTRY_FLAG_UNCOMPRESSED = 0x1,
	WADENTRY_FLAG_RNCOMPRESSED = 0x2,
	WADENTRY_FLAG_IS_IN_WAD    = 0x4,
};
flags_end(Wad_EntryFlags, 0x4);

enum WaterFlags : uint32 // [LegoRR/Water.c|flags:0x4|type:uint]
{
	WATER_FLAG_NONE    = 0,
	WATER_FLAG_VISIBLE = 0x1,
	WATER_FLAG_FULL    = 0x2,
	WATER_FLAG_SETTLED = 0x4,
};
flags_end(WaterFlags, 0x4);



union File_union // [Gods98/Files.c|union:0x4]
{
	/*0,4*/	FILE* std; // Standard file stream
	/*0,4*/	WADFILE* wad; // WAD file stream
	/*4*/
};
assert_sizeof(File_union, 0x4);

union MenuItem_Data_union // [LegoRR/FrontEnd.c|union:0x4]
{
	/*0,4*/	MenuItem_CycleData* cycle;
	/*0,4*/	MenuItem_TriggerData* trigger;
	/*0,4*/	MenuItem_TextInputData* textInput;
	/*0,4*/	MenuItem_SliderData* slider;
	/*0,4*/	MenuItem_RealSliderData* realSlider;
	/*0,4*/	MenuItem_SelectData* select;
	/*0,4*/	Menu* next;
	/*4*/
};
assert_sizeof(MenuItem_Data_union, 0x4);



struct Advisor_Globs // [LegoRR/Advisor.c|struct:0x410|tags:GLOBS]
{
	/*000,54*/	char* positionName[21];
	/*054,2f4*/	AdvisorPositionData positions[21];
	/*348,2c*/	char* animName[11];
	/*374,84*/	AdvisorAnimData anims[11];
	/*3f8,4*/	Advisor_Type currType;
	/*3fc,4*/	Container* cameraCont;
	/*400,4*/	Viewport* viewMain;
	/*404,4*/	real32 viewZ; // Z position of every advisor type (init: 0.96f)
	/*408,4*/	Container* lightCont;
	/*40c,4*/	Advisor_GlobFlags flags;
	/*410*/
};
assert_sizeof(Advisor_Globs, 0x410);

struct AdvisorAnimData // [LegoRR/Advisor.c|struct:0xc]
{
	/*0,4*/	Container* cont;
	/*4,4*/	real32 loopStartTime; // ignored when not looping
	/*8,4*/	real32 loopEndTime; // ignored when not looping
	/*c*/
};
assert_sizeof(AdvisorAnimData, 0xc);

struct AdvisorPositionData // [LegoRR/Advisor.c|struct:0x24]
{
	/*00,4*/	Advisor_Anim animType;
	/*04,4*/	Text_Type textType;
	/*08,4*/	SFX_ID sfxID;
	/*0c,4*/	Panel_Type panelType;
	/*10,4*/	real32 x; // Mutable x position
	/*14,4*/	real32 y; // Mutable y position
	/*18,4*/	real32 origX; // Immutable x position (set once)
	/*1c,4*/	real32 origY; // Immutable y position (set once)
	/*20,4*/	AdvisorFlags flags; // (init: 0x20000), 0x10000 = NULL panel, 0x40000 = non-NULL text
	/*24*/
};
assert_sizeof(AdvisorPositionData, 0x24);

struct AITask // [LegoRR/AITask.c|struct:0x68|tags:LISTSET]
{
	/*00,4*/	AITask_Type taskType;
	/*04,4*/	AITask* referrerTask; // Passed from certain Message_Events. Assigned but never used.
	/*08,8*/	Point2I blockPos;
	/*10,4*/	LegoObject* targetObject;
	/*14,4*/	real32 time; // Count-down timer.
	/*18,4*/	real32 timeIn; // Count-down timer.
	/*1c,4*/	sint32 priorityValue; // Field is known to be signed (range: 0,99).
	/*20,4*/	LegoObject_Type objType;
	/*24,4*/	LegoObject_ID objID;
	/*28,4*/	uint32 objLevel;
	/*2c,4*/	uint32 constructHandle;
	/*30,8*/	Point2F blockOffset;
	/*38,4*/	LegoObject_ToolType toolType;
	/*3c,4*/	LegoObject_AbilityType trainFlags;
	/*40,4*/	LegoObject** unitList;
	/*44,4*/	uint32 unitListCount;
	/*48,4*/	LegoObject* assignedToObject; // Likely related to tasks with a two-object relation. Like training at a building.
	/*4c,4*/	AI_Priority priorityType;
	/*50,4*/	uint32 creationTime; // Timestamp of task creation in `AITask_Create`, obtained from `Main_GetTime()`.
	/*54,4*/	Message_Type completeAction;
	/*58,4*/	AITask* getToolTask; // (bi-directional link between GetTool and GetTool_FromText)
	/*5c,4*/	AITaskFlags flags;
	/*60,4*/	AITask* next; // Next in linked lists for `aiGlobs.AITaskUnkPtr`, `aiGlobs.AITaskDataNext`, and `LegoObject::aiTask`.
	/*64,4*/	AITask* nextFree; // (for listSet)
	/*68*/
};
assert_sizeof(AITask, 0x68);

struct AITask_Globs // [LegoRR/AITask.c|struct:0x4e9c|tags:GLOBS]
{
	/*0000,30*/	AITask* listSet[12];
	/*0030,4*/	AITask* freeList;
	/*0034,4*/	uint32 listCount;
	/*0038,7c*/	char* aitaskName[31];
	/*00b4,6c*/	char* priorityName[27];
	/*0120,6c*/	sint32 priorityValues[27];
	/*018c,4*/	AITask* pendingTaskList;
	/*0190,4*/	AITask* creatureTaskList;
	/*0194,c8*/	LegoObject* freeUnitList[50];
	/*025c,4*/	uint32 freeUnitCount;
	/*0260,c8*/	LegoObject* freeCreatureList[50];
	/*0328,4*/	uint32 freeCreatureCount;
	/*032c,4b00*/	uint32 requestObjCounts[20][15][16];
	/*4e2c,6c*/	bool32 disabledPriorities[27];
	/*4e98,4*/	AITask_GlobFlags flags;
	/*4e9c*/
};
assert_sizeof(AITask_Globs, 0x4e9c);

struct Animation_Globs // [Gods98/Animation.c|struct:0x8|tags:GLOBS]
{
	/*0,1*/	bool g98NoAvis; // (global variable)
	/*1,3*/	uint8 padding1[3];
	/*4,4*/	IDirectDraw4* ddraw; // (global variable)
	/*8*/
};
assert_sizeof(Animation_Globs, 0x8);

struct AnimClone // [Gods98/AnimClone.c|struct:0x20]
{
	/*00,4*/	AnimClone* clonedFrom;
	/*04,4*/	Lws_Info* scene; // LWS struct
	/*08,4*/	IDirect3DRMAnimationSet2* animSet; // (not LWS)
	/*0c,4*/	bool32 lws;
	/*10,4*/	IDirect3DRMFrame3* root; // (not LWS)
	/*14,4*/	IDirect3DRMFrame3** partArray; // (not LWS) table of COM objects, length is count_18
	/*18,4*/	uint32 partCount; // (not LWS)
	/*1c,4*/	uint32 frameCount;
	/*20*/
};
assert_sizeof(AnimClone, 0x20);

struct APPOBJ // [Gods98/Lwt.c|struct:0x20] LightWave lwt APPOBJ
{
	/*00,4*/	char* aoPath;
	/*04,c*/	LWSIZE aoSize;
	/*10,4*/	real32* aoVerts;
	/*14,4*/	LWPOLY* aoPoly;
	/*18,4*/	LWSURFACE* aoSurface;
	/*1c,4*/	File* aoFileUV;
	/*20*/
};
assert_sizeof(APPOBJ, 0x20);

struct Area2F // [common.c|struct:0x10] also Area2F
{
	/*00,4*/	real32 x;
	/*04,4*/	real32 y;
	/*08,4*/	real32 width;
	/*0c,4*/	real32 height;
	/*10*/
};
assert_sizeof(Area2F, 0x10);

struct Area2I // [common.c|struct:0x10] also Area2I
{
	/*00,4*/	sint32 x;
	/*04,4*/	sint32 y;
	/*08,4*/	sint32 width;
	/*0c,4*/	sint32 height;
	/*10*/
};
assert_sizeof(Area2I, 0x10);

struct BasicObjectModel // [LegoRR/dummy.c|struct:0x8] This is a dummy structure that is used for CreatureData, BuildingData, and UpgradeData (for functions using these structures that have been merged together). It's highly likely this similarity is only due to linked functions performing the same behavior and being grouped together.
{
	/*0,4*/	LegoObject_ID objID;
	/*4,4*/	Container* contAct; // ACT, true
	/*8*/
};
assert_sizeof(BasicObjectModel, 0x8);

struct BezierCurve // [LegoRR/Routing.c|struct:0x25c]
{
	/*000,4*/	uint32 count;
	/*004,190*/	Point2F points[50];
	/*194,c8*/	real32 distances[50];
	/*25c*/
};
assert_sizeof(BezierCurve, 0x25c);

#pragma pack(push, 2)
struct BITMAP_FILE_INFO_STRUCT // [Gods98/dummy.c|struct:0x3a|pack:2] Helper struct to combine both BITMAPFILEHEADER, BITMAPINFOHEADER, and palette data into one field
{
	/*00,10*/	BITMAPFILEHEADER hdr;
	/*10,28*/	BITMAPINFOHEADER bmi;
	/*38,4*/	RGBQUAD bmiColors[1];
	/*3c*/
};
assert_sizeof(BITMAP_FILE_INFO_STRUCT, 0x3c);
#pragma pack(pop)

struct BlockPointer // [LegoRR/NERPs.c|struct:0xc]
{
	/*0,8*/	Point2I blockPos;
	/*8,4*/	BlockPointer* next; // Linked list of BlockPointers with same ID.
	/*c*/
};
assert_sizeof(BlockPointer, 0xc);

struct Box2F // [common.c|struct:0x10]
{
	/*00,4*/	real32 x1;
	/*04,4*/	real32 y1;
	/*08,4*/	real32 x2;
	/*0c,4*/	real32 y2;
	/*10*/
};
assert_sizeof(Box2F, 0x10);

struct Box2I // [common.c|struct:0x10]
{
	/*00,4*/	sint32 x1;
	/*04,4*/	sint32 y1;
	/*08,4*/	sint32 x2;
	/*0c,4*/	sint32 y2;
	/*10*/
};
assert_sizeof(Box2I, 0x10);

struct Box3F // [common.c|struct:0x18] Box3F
{
	/*00,c*/	Vector3F min;
	/*0c,c*/	Vector3F max;
	/*18*/
};
assert_sizeof(Box3F, 0x18);

struct Bubble // [LegoRR/Bubble.c|struct:0x8]
{
	/*0,4*/	LegoObject* object;
	/*4,4*/	real32 remainingTimer;
	/*8*/
};
assert_sizeof(Bubble, 0x8);

struct Bubble_Globs // [LegoRR/Bubble.c|struct:0x4f4|tags:GLOBS]
{
	/*000,4*/	bool32 alwaysVisible; // Object Display HUD/UI over entities in-game
	/*004,9c*/	Image* bubbleImage[39];
	/*0a0,9c*/	char* bubbleName[39];
	/*13c,48*/	undefined1 reserved1[72];
	/*184,a0*/	Bubble healthBarList[20]; // Not a bubble image, but this tracks how long to show the bar after being damaged like normal bubbles.
	/*224,a0*/	Bubble bubbleList[20]; // All other types of bubbles.
	/*2c4,a0*/	Bubble powerOffList[20]; // Flashing no-power icons.
	/*364,190*/	Bubble callToArmsList[50]; // Action stations bubbles.
	/*4f4*/
};
assert_sizeof(Bubble_Globs, 0x4f4);

struct BuildingModel // [LegoRR/Building.c|struct:0x14c]
{
	/*000,4*/	LegoObject_ID objID;
	/*004,4*/	Container* contAct; // (ACT, true)
	/*008,4*/	char* carryNullName; // (ae: CarryNullName)
	/*00c,4*/	char* cameraNullName; // (ae: CameraNullName)
	/*010,4*/	char* depositNullName; // (ae: DepositNullName)
	/*014,4*/	char* entranceNullName; // (ae: EntranceNullName)
	/*018,4*/	char* toolNullName; // (ae: ToolNullName)
	/*01c,4*/	char* fireNullName; // (ae: FireNullName) "fire laser"
	/*020,4*/	char* yPivot; // (ae: yPivot)
	/*024,4*/	char* xPivot; // (ae: xPivot)
	/*028,18*/	Container* carryNulls[6];
	/*040,10*/	Container* cameraNulls[4];
	/*050,18*/	Container* toolNulls[6]; // (note: index five is never observed may be array size [5])
	/*068,4*/	Container* depositNull;
	/*06c,4*/	Container* entranceNull;
	/*070,4*/	uint32 carryNullFrames; // (ae: CarryNullFrames)
	/*074,4*/	uint32 cameraNullFrames; // (ae: CameraNullFrames)
	/*078,4*/	uint32 toolNullFrames; // (ae: ToolNullFrames)
	/*07c,4*/	Container* contPowerLevel; // (ae: PowerLevelScene, LWS, true) Scene used as some sort of power meter with diminishing returns during increment.
	/*080,4*/	real32 powerLevel;
	/*084,4*/	Point2I* shapePoints; // (ae: Shape) Point2I[10]
	/*088,4*/	uint32 shapeCount; // (ae: Shape)
	/*08c,14*/	UpgradesModel upgrades;
	/*0a0,a8*/	WeaponsModel weapons;
	/*148,4*/	BuildingFlags flags; // (0x1: original that holds memory [broken], 0x2: PowerLevel scene playing)
	/*14c*/
};
assert_sizeof(BuildingModel, 0x14c);

struct Camera_Globs // [LegoRR/LegoCamera.c|struct:0x10|tags:GLOBS]
{
	/*00,4*/	real32 maxSpeed; // (cfg: CameraSpeed) maximum move speed of camera
	/*04,4*/	real32 deceleration; // (cfg: CameraDropOff) movement deceleration
	/*08,4*/	real32 acceleration; // (cfg: CameraAcceleration) movement acceleration
	/*0c,4*/	sint32 mouseScrollIndent; // (cfg: MouseScrollIndent) area around window borders for mouse movement
	/*10*/
};
assert_sizeof(Camera_Globs, 0x10);

struct ColourRGBAF // [common.c|struct:0x10]
{
	/*00,4*/	real32 red;
	/*04,4*/	real32 green;
	/*08,4*/	real32 blue;
	/*0c,4*/	real32 alpha;
	/*10*/
};
assert_sizeof(ColourRGBAF, 0x10);

struct ColourRGBAI // [common.c|struct:0x10]
{
	/*00,4*/	uint32 red;
	/*04,4*/	uint32 green;
	/*08,4*/	uint32 blue;
	/*0c,4*/	uint32 alpha;
	/*10*/
};
assert_sizeof(ColourRGBAI, 0x10);

#pragma pack(push, 1)
struct ColourRGBAPacked // [common.c|struct:0x4|pack:1]
{
	/*0,1*/	uint8 red;
	/*1,1*/	uint8 green;
	/*2,1*/	uint8 blue;
	/*3,1*/	uint8 alpha;
	/*4*/
};
assert_sizeof(ColourRGBAPacked, 0x4);
#pragma pack(pop)

struct ColourRGBF // [common.c|struct:0xc]
{
	/*0,4*/	real32 red;
	/*4,4*/	real32 green;
	/*8,4*/	real32 blue;
	/*c*/
};
assert_sizeof(ColourRGBF, 0xc);

struct ColourRGBI // [common.c|struct:0xc]
{
	/*0,4*/	uint32 red;
	/*4,4*/	uint32 green;
	/*8,4*/	uint32 blue;
	/*c*/
};
assert_sizeof(ColourRGBI, 0xc);

#pragma pack(push, 1)
struct ColourRGBPacked // [common.c|struct:0x3|pack:1]
{
	/*0,1*/	uint8 red;
	/*1,1*/	uint8 green;
	/*2,1*/	uint8 blue;
	/*3*/
};
assert_sizeof(ColourRGBPacked, 0x3);
#pragma pack(pop)

struct Config // [Gods98/Config.c|struct:0x20|tags:LISTSET] CFG file property node
{
	/*00,4*/	char* fileData; // Entire file text data for root CFGProperty only
	/*04,4*/	char* key; // Property or block key name
	/*08,4*/	char* value; // Property value or block open brace
	/*0c,4*/	uint32 depth; // Block-depth of property
	/*10,4*/	uint32 itemHashCode; // Hash of item (unused)
	/*14,4*/	Config* linkNext; // Next property in linked list
	/*18,4*/	Config* linkPrev; // Previous property in linked list
	/*1c,4*/	Config* nextFree; // (internal) used for allocation while reading(?)
	/*20*/
};
assert_sizeof(Config, 0x20);

struct Config_Globs // [Gods98/Config.c|struct:0x48c|tags:GLOBS]
{
	/*000,400*/	char s_JoinPath_string[1024]; // (not part of Manager, static array in JoinPath func)
	/*400,80*/	Config* listSet[32];
	/*480,4*/	Config* freeList;
	/*484,4*/	uint32 listCount;
	/*488,4*/	Config_GlobFlags flags;
	/*48c*/
};
assert_sizeof(Config_Globs, 0x48c);

struct Construction_Globs // [LegoRR/Construction.c|struct:0x38|tags:GLOBS]
{
	/*00,4*/	uint32 nextHandleValue; // Next handle value used when creating a construction zone.
	/*04,4*/	Construction_Zone* constructList; // Head of linked list.
	/*08,14*/	undefined4 unused_buildingBaseTable[5]; // (probably related to unused buildingBaseTable)
	/*1c,14*/	char* buildingBaseName[5]; // empty table, no names
	/*30,4*/	uint32 buildingBaseCount;
	/*34,4*/	bool32 disableCryOreDrop;
	/*38*/
};
assert_sizeof(Construction_Globs, 0x38);

struct Construction_Zone // [LegoRR/Construction.c|struct:0xd4]
{
	/*00,4*/	LegoObject_ID objID; // Always used for Buildings, but for only for Paths in shared functions.
	/*04,4*/	Direction direction; // Direction of Building object when completed.
	/*08,4*/	uint32 handleValue; // Unique handle for this construction zone.
	/*0c,8*/	Point2I originBlockPos; // Alternate handle to construction zone. Used as the primary tile for resource placement. Block position of Building object when completed.
	/*14,4*/	Point2I* shapeBlocks; // Only used by Buildings, transformed shape to match originBlockPos.
	/*18,4*/	uint32 shapeCount;
	/*1c,4*/	uint32 requestCount; // Number of resources requested. Must be matched by placeCount to finish construction.
	/*20,4*/	uint32 placedCount;
	/*24,4*/	Construction_Zone* next; // Next in linked list.
	/*28,4*/	real32 float_28; // (ready: 125.0 , unused, possibly old timer for delay before construction)
	/*2c,a0*/	LegoObject* placedObjects[40];
	/*cc,4*/	uint32 placedCount2; // Always identical to placedCount, no difference in usage.
	/*d0,4*/	Construction_ZoneFlags flags;
	/*d4*/
};
assert_sizeof(Construction_Zone, 0xd4);

struct Container // [Gods98/Containers.c|struct:0x2c|tags:LISTSET]
{
	/*00,4*/	IDirect3DRMFrame3* masterFrame; // (frame1)
	/*04,4*/	IDirect3DRMFrame3* activityFrame; // (frame2)
	/*08,4*/	IDirect3DRMFrame3* hiddenFrame; // (frame3)
	/*0c,4*/	Container_TypeData* typeData;
	/*10,4*/	Container_Type type;
	/*14,4*/	ContainerFlags flags;
	/*18,4*/	ContainerActivityCallback activityCallback;
	/*1c,4*/	void* activityCallbackData;
	/*20,4*/	void* userData; // (often LiveObject*)
	/*24,4*/	Container_CloneData* cloneData; // Only used by animsets.
	/*28,4*/	Container* nextFree;
	/*2c*/
};
assert_sizeof(Container, 0x2c);

struct Container_AppData // [Gods98/Containers.c|struct:0x28]
{
	/*00,4*/	Container* ownerContainer;
	/*04,4*/	char* animSetFileName; // For the dodgy Animation Set clone stuff...
	/*08,4*/	char* frameName; // For freeing the allocation for SetName...
	/*0c,4*/	uint32 frameCount;
	/*10,4*/	real32 currTime;
	/*14,4*/	real32 transCo; // Standard translation during amimset loop.
	/*18,4*/	char* activitySample; // Sample to play when activity is called...
	/*1c,4*/	AnimClone* animClone;
	/*20,4*/	uint32 trigger;
	/*24,4*/	Sound3D_SoundFrameRecord* soundList; // For 'Sound3D'
	/*28*/
};
assert_sizeof(Container_AppData, 0x28);

struct Container_CloneData // [Gods98/Containers.c|struct:0x14] structure assigned to ResourceData->field_24 (allocated for ACT,ANIM resource types)
{
	/*00,4*/	Container* clonedFrom; // NULL if this is the original
	/*04,4*/	Container** cloneTable; // List of clones (NULL for unused elements)
	/*08,4*/	uint32 cloneCount; // Total number of clones made and clone's number in the list.
	/*0c,4*/	IDirect3DRMFrame3* cloneNumber; // (init: ResourceData->frame2 IDirect3DRMFrame3 * ???)
	/*10,4*/	bool32 used; // (init: 1)
	/*14*/
};
assert_sizeof(Container_CloneData, 0x14);

struct Container_Globs // [Gods98/Containers.c|struct:0x2018|tags:GLOBS]
{
	/*0000,50*/	Container* listSet[20];
	/*0050,4*/	Container* freeList;
	/*0054,4*/	Container* rootContainer;
	/*0058,24*/	char* typeName[9];
	/*007c,24*/	char* extensionName[9];
	/*00a0,4*/	char* gameName;
	/*00a4,10*/	IDirect3DRMVisual* visualArray[4];
	/*00b4,1f40*/	Container_TextureRef textureSet[1000];
	/*1ff4,4*/	uint32 textureCount;
	/*1ff8,4*/	ContainerSoundTriggerCallback soundTriggerCallback;
	/*1ffc,4*/	void* soundTriggerData;
	/*2000,4*/	ContainerTriggerFrameCallback triggerFrameCallback;
	/*2004,4*/	void* triggerFrameData;
	/*2008,4*/	char* sharedDir;
	/*200c,4*/	uint32 fogColour;
	/*2010,4*/	uint32 listCount;
	/*2014,4*/	Container_GlobFlags flags;
	/*2018*/
};
assert_sizeof(Container_Globs, 0x2018);

struct Container_SearchData // [Gods98/Containers.c|struct:0x1c|tags:SEARCH]
{
	/*00,4*/	char* string;
	/*04,4*/	uint32 stringLen;
	/*08,4*/	bool32 caseSensitive;
	/*0c,4*/	IDirect3DRMFrame3* resultFrame;
	/*10,4*/	uint32 count;
	/*14,4*/	Container_SearchMode mode;
	/*18,4*/	uint32 matchNumber;
	/*1c*/
};
assert_sizeof(Container_SearchData, 0x1c);

struct Container_Texture // [Gods98/Containers.c|struct:0xc]
{
	/*0,4*/	IDirectDrawSurface4* surface;
	/*4,4*/	IDirect3DRMTexture3* texture;
	/*8,4*/	bool32 colourKey;
	/*c*/
};
assert_sizeof(Container_Texture, 0xc);

struct Container_TextureData // [Gods98/Containers.c|struct:0x8]
{
	/*0,4*/	char* xFileName;
	/*4,4*/	uint32 flags;
	/*8*/
};
assert_sizeof(Container_TextureData, 0x8);

struct Container_TextureRef // [Gods98/Containers.c|struct:0x8]
{
	/*0,4*/	char* filename;
	/*4,4*/	IDirect3DRMTexture3* texture;
	/*8*/
};
assert_sizeof(Container_TextureRef, 0x8);

struct Container_TypeData // [Gods98/Containers.c|struct:0x10]
{
	/*00,4*/	char* name;
	/*04,4*/	IDirect3DRMLight* light;
	/*08,4*/	IDirect3DRMMesh* mesh;
	/*0c,4*/	Mesh* transMesh;
	/*10*/
};
assert_sizeof(Container_TypeData, 0x10);

struct Coord2U // [common.c|struct:0x4] Point2U structure using short-sized integers (name is based off the WINAPI console structure COORD, using the same layout)
{
	/*0,2*/	uint16 x;
	/*2,2*/	uint16 y;
	/*4*/
};
assert_sizeof(Coord2U, 0x4);

struct CreatureModel // [LegoRR/Creature.c|struct:0x74] Possibly alphabetically correct names: Bipedal, BasicUnit, etc... (has to be before Bubble, and possible after BezierCurve or AI(Task?))
{
	/*00,4*/	LegoObject_ID objID;
	/*04,4*/	Container* contAct; // (ACT, true)
	/*08,18*/	undefined reserved1[24];
	/*20,4*/	char* cameraNullName; // (ae: CameraNullName)
	/*24,4*/	uint32 cameraNullFrames; // (ae: CameraNullFrames)
	/*28,4*/	BoolTri cameraFlipDir; // (ae: CameraFlipDir)
	/*2c,4*/	char* drillNullName; // (ae: DrillNullName)
	/*30,4*/	char* footStepNullName; // (ae: FootStepNullName)
	/*34,4*/	char* carryNullName; // (ae: CarryNullName)
	/*38,4*/	char* throwNullName; // (ae: ThrowNullName)
	/*3c,4*/	char* depositNullName; // (ae: DepositNullName)
	/*40,4*/	Container* drillNull;
	/*44,4*/	Container* footStepNull; // (unused)
	/*48,4*/	Container* carryNull;
	/*4c,4*/	Container* throwNull;
	/*50,4*/	Container* depositNull;
	/*54,10*/	Container* cameraNulls[4];
	/*64,4*/	MeshLOD* polyMedium; // (ae: MediumPoly)
	/*68,4*/	MeshLOD* polyHigh; // (ae: HighPoly)
	/*6c,4*/	MeshLOD* polyFP; // (ae: FPPoly::Camera#)
	/*70,4*/	CreatureFlags flags; // (0x1: original that holds memory)
	/*74*/
};
assert_sizeof(CreatureModel, 0x74);

struct CryTuple_8 // [LegoRR/FrontEnd.c|struct:0x8]
{
	/*0,4*/	uint32 cryCount;
	/*4,4*/	uint32 unkCount;
	/*8*/
};
assert_sizeof(CryTuple_8, 0x8);

struct DamageFont_Globs // [LegoRR/DamageFont.c|struct:0x16c|tags:GLOBS]
{
	/*000,28*/	Container_Texture* fontTextDigitsTable[10];
	/*028,4*/	Container_Texture* fontTextMinus;
	/*02c,140*/	DamageFontData instanceTable[10];
	/*16c*/
};
assert_sizeof(DamageFont_Globs, 0x16c);

struct DamageFontData // [LegoRR/DamageFont.c|struct:0x20]
{
	/*00,4*/	Container* ownerCont;
	/*04,4*/	Mesh* mesh;
	/*08,4*/	uint32 groupCount;
	/*0c,4*/	real32 float_c;
	/*10,4*/	real32 float_10;
	/*14,4*/	real32 timerDown;
	/*18,4*/	real32 timerUp;
	/*1c,4*/	uint32 flags;
	/*20*/
};
assert_sizeof(DamageFontData, 0x20);

struct Dependencies_Globs // [LegoRR/Dependencies.c|struct:0xe5b4|tags:GLOBS]
{
	/*0000,e5b0*/	DependencyData table[20][15];
	/*e5b0,4*/	bool32 disabled; // (Debug feature with F11 key)
	/*e5b4*/
};
assert_sizeof(Dependencies_Globs, 0xe5b4);

struct DependencyData // [LegoRR/Dependencies.c|struct:0xc4]
{
	/*00,40*/	uint32 numRequirements[16]; // [levels:16]
	/*40,40*/	DependencyRequirement* requirements[16]; // [levels:16][*numRequired] Ptr to table of size numRequired
	/*80,4*/	bool32 manualLevel; // Force requirements for specific level if key format: "<HitOnceStay|*>:Object:<#>"
	/*84,40*/	DependencyFlags levelFlags[16]; // [levels:16] (1 = HitOnceStay)
	/*c4*/
};
assert_sizeof(DependencyData, 0xc4);

struct DependencyRequirement // [LegoRR/Dependencies.c|struct:0x10]
{
	/*00,4*/	LegoObject_Type objType;
	/*04,4*/	LegoObject_ID objID;
	/*08,4*/	uint32 objLevel;
	/*0c,4*/	bool32 hasLevel;
	/*10*/
};
assert_sizeof(DependencyRequirement, 0x10);

struct DependencyUnlocks // [LegoRR/Dependencies.c|struct:0x204]
{
	/*000,80*/	LegoObject_Type objTypes[32];
	/*080,80*/	LegoObject_ID objIDs[32];
	/*100,80*/	uint32 objLevels[32];
	/*180,80*/	bool32 objHasLevels[32]; // (unlocks for a specific level)
	/*200,4*/	uint32 count;
	/*204*/
};
assert_sizeof(DependencyUnlocks, 0x204);

struct Detail_Mesh // [LegoRR/Detail.c|struct:0x340]
{
	/*000,8*/	Container* promesh_ab[2];
	/*008,320*/	Container* clones_ab[2][100];
	/*328,4*/	real32 BlockSize;
	/*32c,4*/	uint32 cloneCount;
	/*330,c*/	undefined field_0x330_0x33b[12];
	/*33c,4*/	Detail_TextureSet* textureSet;
	/*340*/
};
assert_sizeof(Detail_Mesh, 0x340);

struct Detail_TextureSet // [LegoRR/Detail.c|struct:0xc]
{
	/*0,8*/	Size2I gridSize;
	/*8,4*/	Container_Texture** gridSurfaces;
	/*c*/
};
assert_sizeof(Detail_TextureSet, 0xc);

struct DirectDraw_Globs // [Gods98/DirectDraw.c|struct:0x48|tags:GLOBS]
{
	/*00,4*/	HWND hWnd;
	/*04,4*/	IDirectDraw4* lpDirectDraw;
	/*08,4*/	IDirectDrawSurface4* fSurf; // "RenderTarget" surface
	/*0c,4*/	IDirectDrawSurface4* bSurf; // "DrawTarget" surface
	/*10,4*/	IDirectDrawSurface4* zSurf; // (unused)
	/*14,4*/	IDirectDrawClipper* lpFrontClipper; // "RenderTarget" clipper
	/*18,4*/	IDirectDrawClipper* lpBackClipper; // "DrawTarget" clipper
	/*1c,4*/	Graphics_Driver* driverList;
	/*20,4*/	Graphics_Driver* selectedDriver; // (unused)
	/*24,4*/	Graphics_Device* deviceList;
	/*28,4*/	Graphics_Device* selectedDevice; // (unused)
	/*2c,4*/	Graphics_Mode* modeList; // "ScreenModes"
	/*30,4*/	uint32 driverCount;
	/*34,4*/	uint32 deviceCount;
	/*38,4*/	uint32 modeCount; // "ScreenModes"
	/*3c,4*/	bool32 fullScreen;
	/*40,4*/	uint32 width;
	/*44,4*/	uint32 height;
	/*48*/
};
assert_sizeof(DirectDraw_Globs, 0x48);

struct Draw_Globs // [Gods98/Draw.c|struct:0x4c|tags:GLOBS]
{
	/*00,4*/	DrawPixelFunc drawPixelFunc;
	/*04,8*/	Point2F clipStart;
	/*0c,8*/	Point2F clipEnd;
	/*14,10*/	RECT lockRect;
	/*24,4*/	void* buffer;
	/*28,4*/	uint32 pitch;
	/*2c,4*/	uint32 bpp;
	/*30,4*/	uint32 redMask;
	/*34,4*/	uint32 greenMask;
	/*38,4*/	uint32 blueMask;
	/*3c,4*/	uint32 redBits;
	/*40,4*/	uint32 greenBits;
	/*44,4*/	uint32 blueBits;
	/*48,4*/	Draw_GlobFlags flags;
	/*4c*/
};
assert_sizeof(Draw_Globs, 0x4c);

struct Draw_Rect // [Gods98/Draw.c|struct:0x1c]
{
	/*00,10*/	Area2F rect;
	/*10,4*/	real32 r;
	/*14,4*/	real32 g;
	/*18,4*/	real32 b;
	/*1c*/
};
assert_sizeof(Draw_Rect, 0x1c);

struct Dxbug_Globs // [Gods98/Dxbug.c|struct:0x818|tags:GLOBS] DirectX (dxbug.c) debugging loose static variables
{
	/*000,4*/	HRESULT errnum;
	/*004,4*/	sint32 line;
	/*008,4*/	sint32 DXModuleNameNumber;
	/*00c,4*/	sint32 DXNumErrorsSet;
	/*010,4*/	char* file;
	/*014,4*/	uint32 reserved1;
	/*018,800*/	char DXErrorString[2048]; // Last error that was set (actually [1024], but the space is unused)
	/*818*/
};
assert_sizeof(Dxbug_Globs, 0x818);

struct Effect_Globs // [LegoRR/Effects.c|struct:0xc78|tags:GLOBS]
{
	/*000,30*/	uint32 rockFallCompletedTypes[12]; // (size not related to [style:3])
	/*030,30*/	uint32 rockFallCompletedIndexes[12]; // (size not related to [style:3])
	/*060,7b0*/	EffectRockFall rockFallEffects[12]; // [style:3][type:4] LWS:true, or ANIM:true
	/*810,10*/	char* rockFallStyleName[4];
	/*820,4*/	uint32 rockFallStyleCount;
	/*824,4*/	sint32 rockFallStyleIndex;
	/*828,38*/	EffectMisc lazerHitEffect; // LWS:true, or LWO:true
	/*860,38*/	EffectMisc pusherHitEffect; // LWS:true, or LWO:true
	/*898,38*/	EffectMisc freezerHitEffect; // LWS:true, or LWO:true
	/*8d0,38*/	EffectMisc pathDustEffect; // LWS:true, or LWO:true
	/*908,e0*/	EffectMisc lavaErosionSmokeEffects[4]; // [1-4] LWS:true, or LWO:true
	/*9e8,38*/	EffectMisc birdScarerEffect; // LWS:true, or LWO:true
	/*a20,38*/	EffectMisc upgradeEffect; // LWS:true, or LWO:true
	/*a58,10*/	Container* boulderExplodeContTable[4];
	/*a68,10*/	Container* smashPathContTable[4];
	/*a78,1e8*/	EffectElectricFenceBeam efenceEffects[2]; // [shortBeam,longBeam]
	/*c60,4*/	Container* explosionCont; // LWS:true
	/*c64,10*/	Container* explosionContTable[4];
	/*c74,4*/	uint32 explosionCount;
	/*c78*/
};
assert_sizeof(Effect_Globs, 0xc78);

struct EffectElectricFenceBeam // [LegoRR/Effects.c|struct:0xf4]
{
	/*00,4*/	Container* cont; // LWS:true
	/*04,78*/	Container* contTable[30];
	/*7c,78*/	bool32 finishedTable[30];
	/*f4*/
};
assert_sizeof(EffectElectricFenceBeam, 0xf4);

struct EffectMisc // [LegoRR/Effects.c|struct:0x38]
{
	/*00,28*/	Container* contTable[10];
	/*28,4*/	uint32 count; // (max of 10)
	/*2c,4*/	undefined4 field_2c;
	/*30,4*/	Container* cont; // LWS,true | LWO,true
	/*34,4*/	undefined4 field_34;
	/*38*/
};
assert_sizeof(EffectMisc, 0x38);

struct EffectRockFall // [LegoRR/Effects.c|struct:0xa4]
{
	/*00,4*/	Container* cont; // LWS:true, or ANIM:true
	/*04,10*/	Container* contTable[4];
	/*14,10*/	uint32 xBlockPosTable[4];
	/*24,10*/	uint32 yBlockPosTable[4];
	/*34,10*/	bool32 finishedTable[4];
	/*44,4*/	char* itemName; // (temporary stack buffer, BROKEN AF)
	/*48,4*/	sint32 itemFrameCount;
	/*4c,48*/	undefined field_0x4c_0x93[72];
	/*94,10*/	undefined4 bitfieldTable_94[4];
	/*a4*/
};
assert_sizeof(EffectRockFall, 0xa4);

struct ElectricFence_Block // [LegoRR/ElectricFence.c|struct:0x14|tags:LISTSET]
{
	/*00,4*/	LegoObject* attachedObject;
	/*04,8*/	Point2I blockPos;
	/*0c,4*/	real32 timer;
	/*10,4*/	ElectricFence_Block* nextFree; // (for listSet)
	/*14*/
};
assert_sizeof(ElectricFence_Block, 0x14);

struct ElectricFence_Globs // [LegoRR/ElectricFence.c|struct:0x90|tags:GLOBS]
{
	/*00,4*/	ElectricFence_GridBlock* fenceGrid; // BlockElectricFence[width * height]
	/*04,4*/	Lego_Level* level;
	/*08,80*/	ElectricFence_Block* listSet[32];
	/*88,4*/	ElectricFence_Block* freeList;
	/*8c,4*/	uint32 listCount; // (no flags)
	/*90*/
};
assert_sizeof(ElectricFence_Globs, 0x90);

struct ElectricFence_GridBlock // [LegoRR/ElectricFence.c|struct:0xc|tags:BLOCKGRID] Note that the size when allocating fenceGrid is mistakenly 0x14, but lookup is performed with size 0xc
{
	/*0,4*/	ElectricFence_Block* efence;
	/*4,4*/	LegoObject* studObj; // Glowing lime stud  object placed between 2-block-wide connections
	/*8,4*/	ElectricFence_GridFlags flags;
	/*c*/
};
assert_sizeof(ElectricFence_GridBlock, 0xc);

struct EmergeBlock // [LegoRR/Lego.c|struct:0xc]
{
	/*0,8*/	Point2I blockPos;
	/*8,4*/	bool32 used;
	/*c*/
};
assert_sizeof(EmergeBlock, 0xc);

struct EmergeTrigger // [LegoRR/Lego.c|struct:0x4c]
{
	/*00,4*/	undefined4 field_0;
	/*04,8*/	Point2I blockPos;
	/*0c,4*/	real32 timeout;
	/*10,3c*/	EmergeBlock emergePoints[5];
	/*4c*/
};
assert_sizeof(EmergeTrigger, 0x4c);

struct Encyclopedia_Globs // [LegoRR/Encyclopedia.c|struct:0x24|tags:GLOBS]
{
	/*00,4*/	File** vehicleFiles;
	/*04,4*/	File** minifigureFiles;
	/*08,4*/	File** rockmonsterFiles;
	/*0c,4*/	File** buildingFiles;
	/*10,4*/	File* powercrystalFile;
	/*14,4*/	File* oreFile;
	/*18,4*/	File* currentObjFile;
	/*1c,4*/	LegoObject* currentObj;
	/*20,4*/	Encyclopedia_GlobFlags flags;
	/*24*/
};
assert_sizeof(Encyclopedia_Globs, 0x24);

struct Erode_Globs // [LegoRR/Erode.c|struct:0xfa14|tags:GLOBS]
{
	/*0000,3e80*/	Point2I UnkBlocksList[2000];
	/*3e80,4*/	uint32 UnkBlocksCount;
	/*3e84,3e80*/	Point2I activeBlocks[2000];
	/*7d04,1f40*/	bool32 activeStates[2000];
	/*9c44,1f40*/	real32 activeTimers[2000]; // (countdown timers)
	/*bb84,1f40*/	Point2I lockedBlocks[1000];
	/*dac4,fa0*/	real32 lockedTimers[1000]; // (countdown timers)
	/*ea64,fa0*/	bool32 lockedStates[1000];
	/*fa04,4*/	real32 elapsedTimer; // (count-up elapsed timer)
	/*fa08,4*/	real32 ErodeTriggerTime; // (init: Lego.cfg)
	/*fa0c,4*/	real32 ErodeErodeTime; // (init: Lego.cfg)
	/*fa10,4*/	real32 ErodeLockTime; // (init: Lego.cfg)
	/*fa14*/
};
assert_sizeof(Erode_Globs, 0xfa14);

struct Error_Globs // [Gods98/Errors.c|struct:0x818|tags:GLOBS]
{
	/*000,4*/	File* dumpFile;
	/*004,4*/	File* loadLogFile;
	/*008,4*/	File* loadErrorLogFile;
	/*00c,4*/	File* redundantLogFile;
	/*010,400*/	char loadLogName[1024];
	/*410,400*/	char redundantLogName[1024];
	/*810,4*/	bool32 warnCalled;
	/*814,4*/	bool32 fullScreen;
	/*818*/
};
assert_sizeof(Error_Globs, 0x818);

struct Fallin_Globs // [LegoRR/Fallin.c|struct:0x4|tags:GLOBS] Just a single field for Fallins (most other settings are found in Lego_Globs)
{
	/*0,4*/	uint32 NumberOfLandSlidesTillCaveIn;
	/*4*/
};
assert_sizeof(Fallin_Globs, 0x4);

struct File // [Gods98/Files.c|struct:0x8]
{
	/*0,4*/	FileSys type;
	/*4,4*/	File_union stream;
	/*8*/
};
assert_sizeof(File, 0x8);

struct File_Globs // [Gods98/Files.c|struct:0xa20|tags:GLOBS]
{
	/*000,400*/	char wadBasePath[1024];
	/*400,400*/	char s_GetWadName_wadedName[1024];
	/*800,104*/	char s_VerifyFilename_full[260];
	/*904,4*/	FILE* s_ErrorFile_f; // (address not known)
	/*908,104*/	char dataDir[260];
	/*a0c,4*/	FileLoadCallback loadCallback;
	/*a10,4*/	void* loadCallbackData;
	/*a14,1*/	char cdLetter;
	/*a15,3*/	undefined1 padding1[3];
	/*a18,4*/	bool32 basePathSet;
	/*a1c,4*/	bool32 fileLogFileAccess; // (address not known)
	/*a20*/
};
assert_sizeof(File_Globs, 0xa20);

struct FileCheck_Globs // [Gods98/Files.c|struct:0x1f4004|tags:GLOBS] Loose static variables for File_CheckRedundantFiles in Files.c
{
	/*000000,1f4000*/	char loadedList[2000][1024]; // MAYBE USE LINKED LIST
	/*1f4000,4*/	uint32 numInList;
	/*1f4004*/
};
assert_sizeof(FileCheck_Globs, 0x1f4004);

struct Flic // [Gods98/Flic.c|struct:0x6e8] (official: FLICSTRUCT)
{
	/*000,4*/	FlicUserFlags userflags;
	/*004,4*/	sint32 fsXc; // (init: 0)
	/*008,4*/	sint32 fsYc; // (init: 0)
	/*00c,4*/	sint32 fsXsize;
	/*010,4*/	sint32 fsYsize;
	/*014,4*/	uint8* rambufferhandle;
	/*018,4*/	uint8* destportalhandle;
	/*01c,100*/	char filename[256];
	/*11c,300*/	ColourRGBPacked fsPalette256[256];
	/*41c,200*/	uint16 fsPalette64k[256];
	/*61c,4*/	sint32 framerate; // (init: 0x190000)
	/*620,4*/	sint32 lastticks;
	/*624,4*/	sint32 currentframe; // (init: 0)
	/*628,4*/	sint32 overallframe; // (init: 0)
	/*62c,4*/	sint32 mode;
	/*630,4*/	sint32 ringframe;
	/*634,4*/	sint32 pointerposition; // (init: 0 if flags1, else 0x80)
	/*638,4*/	uint32 fsPitch;
	/*63c,4*/	IDirectDrawSurface4* fsSurface;
	/*640,88*/	FLICHEADERSTRUCT fsHeader;
	/*6c8,4*/	File* filehandle;
	/*6cc,4*/	void* fsSPtr;
	/*6d0,4*/	void* fsSource;
	/*6d4,4*/	FlicDisplayMode fsDisplayMode;
	/*6d8,4*/	sint32 fsBitPlanes;
	/*6dc,4*/	sint32 fsLoadBufferSize;
	/*6e0,4*/	void* fsLoadBuffer;
	/*6e4,4*/	bool32 is15bit; // true if green mask == 0x3e0
	/*6e8*/
};
assert_sizeof(Flic, 0x6e8);

struct FLICHEADERSTRUCT // [Gods98/Flic.c|struct:0x88]
{
	/*00,4*/	sint32 size; // Size of FLIC including this header
	/*04,2*/	uint16 magic; // File type [0x1234, 0x9119, 0xaf11, 0xaf12, 0xaf43]
	/*06,2*/	uint16 frames; // Number of frames in first segment
	/*08,2*/	uint16 width; // FLIC width in pixels
	/*0a,2*/	uint16 height; // FLIC height in pixels
	/*0c,2*/	uint16 depth; // Bits per pixel (usually 8)
	/*0e,2*/	uint16 flags; // Set to zero or to three
	/*10,2*/	uint16 speed; // Delay between frames
	/*12,2*/	uint16 padding1;
	/*14,4*/	sint32 next;
	/*18,4*/	sint32 frit;
	/*1c,52*/	char expand[82];
	/*6e,2*/	uint16 padding2;
	/*70,4*/	sint32 NewPack;
	/*74,4*/	sint32 SoundID;
	/*78,4*/	sint32 SoundRate;
	/*7c,1*/	char SoundChannels;
	/*7d,1*/	char SoundBPS;
	/*7e,2*/	uint16 padding3;
	/*80,4*/	sint32 SoundChunkSize;
	/*84,2*/	sint16 SoundNumPreRead;
	/*86,2*/	uint16 padding4;
	/*88*/
};
assert_sizeof(FLICHEADERSTRUCT, 0x88);

struct Flocks // [LegoRR/Flocks.c|struct:0x28] The singular flocks unit, which holds all items flying within it.
{
	/*00,4*/	FlocksItem* flocksSubdata1; // (is this a doubly-linked list?)
	/*04,4*/	FlocksItem* flocksSubdata2;
	/*08,4*/	uint32 numSubdata;
	/*0c,4*/	bool32 hasVector1;
	/*10,4*/	bool32 hasVector2;
	/*14,4*/	undefined4 field_14;
	/*18,4*/	real32 floatx_18;
	/*1c,4*/	undefined4 field_1c;
	/*20,4*/	real32 floaty_20;
	/*24,4*/	FlocksFlags flags; // (observed flags: 0x1, )
	/*28*/
};
assert_sizeof(Flocks, 0x28);

struct Flocks_Globs // [LegoRR/Flocks.c|struct:0x10|tags:GLOBS]
{
	/*00,4*/	real32 Turn;
	/*04,4*/	real32 Speed;
	/*08,4*/	real32 Tightness;
	/*0c,4*/	real32 GoalUpdate;
	/*10*/
};
assert_sizeof(Flocks_Globs, 0x10);

struct FlocksItem // [LegoRR/Flocks.c|struct:0xa0]  An individual item flying in a single Flocks unit.
{
	/*00,c*/	Vector3F vector_0;
	/*0c,c*/	Vector3F vector_c;
	/*18,c*/	Vector3F vector_18;
	/*24,4*/	real32 rotationY_24;
	/*28,4*/	real32 rotationX_28;
	/*2c,4*/	real32 rotationZ_2c;
	/*30,4*/	real32 float_30;
	/*34,4*/	real32 float_34;
	/*38,4*/	real32 GoalUpdate1;
	/*3c,4*/	real32 Turn1;
	/*40,4*/	real32 Speed1;
	/*44,4*/	real32 Tightness1;
	/*48,4*/	real32 GoalUpdate2;
	/*4c,4*/	real32 Turn2;
	/*50,4*/	real32 Speed2;
	/*54,4*/	real32 Tightness2;
	/*58,40*/	Matrix4F matrix;
	/*98,4*/	Container* cont;
	/*9c,4*/	FlocksItem* subdataNext;
	/*a0*/
};
assert_sizeof(FlocksItem, 0xa0);

struct Font // [Gods98/Fonts.c|struct:0xbf4|tags:LISTSET] (official: Font)
{
	/*000,4*/	Image* image;
	/*004,be0*/	Area2F posSet[10][19];
	/*be4,4*/	uint32 fontHeight;
	/*be8,4*/	uint32 tabWidth;
	/*bec,4*/	FontFlags flags;
	/*bf0,4*/	Font* nextFree;
	/*bf4*/
};
assert_sizeof(Font, 0xbf4);

struct Font_Globs // [Gods98/Fonts.c|struct:0x8c|tags:GLOBS]
{
	/*00,80*/	Font* listSet[32]; // Fonts list
	/*80,4*/	Font* freeList;
	/*84,4*/	uint32 listCount; // number of lists.
	/*88,4*/	uint32 flags;
	/*8c*/
};
assert_sizeof(Font_Globs, 0x8c);

struct Front_Cache // [LegoRR/FrontEnd.c|struct:0x10] Cache for image/fonts loaded from menus
{
	/*00,4*/	char* path;
	/*04,4*/	Image* image;
	/*08,4*/	Font* font;
	/*0c,4*/	Front_Cache* next;
	/*10*/
};
assert_sizeof(Front_Cache, 0x10);

struct Front_Globs // [LegoRR/FrontEnd.c|struct:0x884|tags:GLOBS]
{
	/*000,4*/	MenuSet* pausedMenuSet; // (cfg: Menu::PausedMenu)
	/*004,4*/	MenuSet* mainMenuSet; // (cfg: Menu::MainMenuFull)
	/*008,4*/	MenuSet* optionsMenuSet; // (cfg: Menu::OptionsMenu)
	/*00c,4*/	MenuSet* saveMenuSet; // (cfg: Menu::SaveMenu)
	/*010,14*/	LevelSet tutorialLevels; // (cfg: Main::TutorialStartLevel)
	/*024,14*/	LevelSet missionLevels; // (cfg: Main::StartLevel)
	/*038,4*/	LevelLink* startMissionLink; // (cfg: Main::StartLevel)
	/*03c,4*/	LevelLink* startTutorialLink; // (cfg: Main::TutorialStartLevel)
	/*040,8*/	undefined8 reserved1a;
	/*048,8*/	undefined8 reserved1b; // (split up to prevent auto-field detection as array access)
	/*050,4*/	sint32 triggerCredits; // [trigger: 1=play credits]
	/*054,8*/	undefined8 reserved2;
	/*05c,4*/	sint32 triggerQuitApp; // [trigger: 1=yes quit game]
	/*060,4*/	sint32 selectMissionIndex; // [select: -1, or pressed mission item index]
	/*064,4*/	sint32 selectTutorialIndex; // [select: -1, or pressed tutorial item index]
	/*068,4*/	sint32 selectLoadSaveIndex; // [select: -1, or pressed save item index]
	/*06c,4*/	sint32 triggerContinueMission; // [trigger: 1=close pause menu]
	/*070,4*/	sint32 sliderGameSpeed; // [slider: 0-5]
	/*074,4*/	sint32 sliderSFXVolume; // [slider: 0-10]
	/*078,4*/	sint32 sliderMusicVolume; // [slider: 0-10]
	/*07c,4*/	sint32 sliderBrightness; // [slider: 0-10]
	/*080,4*/	sint32 cycleHelpWindow; // [cycle: Off,On]
	/*084,4*/	sint32 triggerReplayObjective; // [trigger: 1=replay]
	/*088,4*/	sint32 triggerQuitMission; // [trigger: 1=quit level]
	/*08c,4*/	sint32 triggerRestartMission; // [trigger: 1=restart level]
	/*090,4*/	sint32 cycleWallDetail; // [cycle: High,Low]
	/*094,4*/	sint32 cycleMusicOn; // [cycle: On,Off]
	/*098,4*/	sint32 cycleSFXOn; // [cycle: On,Off]
	/*09c,4*/	sint32 cycleAutoGameSpeed; // [cycle: On,Off]
	/*0a0,4*/	sint32 triggerBackSave; // [trigger: 1=leave save menu]
	/*0a4,8*/	Point2I overlayPosition;
	/*0ac,4*/	Flic* overlayImageOrFlic; // Image* or Flic* type
	/*0b0,4*/	uint32 overlayStartTime; // starting Main_GetTime (milliseconds)
	/*0b4,4*/	uint32 overlayCurrTime; // current Main_GetTime (milliseconds)
	/*0b8,4*/	Font* versionFont; // (file: bmpMbriefFONT2)
	/*0bc,4*/	char* versionString; // (cfg: Main::Version)
	/*0c0,450*/	SaveData saveData[6];
	/*510,4*/	sint32 saveNumber;
	/*514,4*/	char* strDefaultLevelBMPS; // (cfg: Menu::DefaultLevelBMPS) memory storage
	/*518,4*/	undefined4 reserved3;
	/*51c,8*/	Point2I scrollOffset; // Offset position in level select (or anywhere else with a larger menu image)
	/*524,8*/	undefined4 reserved4[2];
	/*52c,4*/	Container* rockWipeAnim;
	/*530,4*/	Front_RockWipeFlags rockWipeFlags;
	/*534,4*/	real32 rockWipeTimer; // RockWipe animation timer in animation frames units.
	/*538,4*/	real32 rockWipeLastUpdateTime; // Main_GetTime should NEVER be stored as a float
	/*53c,4*/	Container* rockWipeLight;
	/*540,4*/	bool32 saveMenuHasNoData;
	/*544,4*/	bool32 saveMenuHasSaved; // True when leaving the save menu without using the back button.
	/*548,4*/	bool32 saveMenuKeepOpen; // Used in a loop to continue showing the save menu.
	/*54c,8*/	Size2I saveImageBigSize;
	/*554,40*/	char langLoadGame[64];
	/*594,40*/	char langSaveGame[64];
	/*5d4,4*/	MenuTextWindow* saveTextWnd;
	/*5d8,4*/	MenuTextWindow* saveLevelWnd;
	/*5dc,80*/	char langOverwriteTitle[128];
	/*65c,100*/	char langOverwriteMessage[256];
	/*75c,80*/	char langOverwriteOK[128];
	/*7dc,80*/	char langOverwriteCancel[128];
	/*85c,4*/	bool32 shouldClearUnlockedLevels;
	/*860,4*/	undefined4 reserved5;
	/*864,4*/	undefined4 unused_zero_864; // (init: 0) Set to 0 and never touched?
	/*868,4*/	sint32 maxLevelScreens;
	/*86c,8*/	undefined4 reserved6[2];
	/*874,4*/	uint32 levelSelectHoverNumber;
	/*878,4*/	uint32 levelSelectLastNumber;
	/*87c,4*/	bool32 levelSelectSFXStopped;
	/*880,4*/	real32 levelSelectSFXTimer;
	/*884*/
};
assert_sizeof(Front_Globs, 0x884);

struct G98CAnimation // [Gods98/Animation.c|struct:0xc4|tags:CLASS,VIRTUAL]
{
	/*00,4*/	G98CAnimationVtbl* vftable;
	/*04,4*/	IAVIStream* m_aviStream;
	/*08,4*/	IGetFrame* m_decompressFn;
	/*0c,8c*/	AVISTREAMINFOA m_aviStreamInfo;
	/*98,1*/	bool m_colourKeySet; // (init: 0)
	/*99,1*/	bool m_init; // (init: 0, 1 on open / has renderer)
	/*9a,2*/	uint16 padding1;
	/*9c,10*/	RECT m_movieRect; // (copied from streamInfo.rcFrame)
	/*ac,4*/	real32 m_startTime; // (init: timeGetTime() * 0.001)
	/*b0,4*/	real32 m_currTime; // (milliseconds, just like startTime)
	/*b4,4*/	real32 m_aviTimeScale;
	/*b8,4*/	uint32 m_currFrame; // (init: 0)
	/*bc,4*/	uint32 m_length; // (unused)
	/*c0,4*/	G98CSurface* m_movieSurf;
	/*c4*/
};
assert_sizeof(G98CAnimation, 0xc4);

struct G98CAnimationVtbl // [Gods98/Animation.c|struct:0x4|tags:VFTABLE]
{
	/*0,4*/	G98CAnimation* (* deletor)(G98CAnimation*, uint8);
	/*4*/
};
assert_sizeof(G98CAnimationVtbl, 0x4);

struct G98CMovie // [Gods98Other/Movie.c|struct:0x38|tags:CLASS]
{
	/*00,4*/	IAMMultiMediaStream* m_amStream;
	/*04,4*/	HRESULT m_err;
	/*08,4*/	IMediaStream* m_sampleBaseStream;
	/*0c,4*/	IDirectDrawMediaStream* m_sampleStream;
	/*10,4*/	IDirectDrawSurface* m_baseSurf; // base surface for IDirectDrawStreamSample* m_sample
	/*14,4*/	IDirectDrawSurface3* m_surf; // DDS3 surface for IDirectDrawStreamSample* m_sample
	/*18,4*/	IDirectDrawStreamSample* m_sample;
	/*1c,4*/	IDirectDrawSurface3* m_bSurf; // render target passed in by constructor
	/*20,10*/	RECT m_movieRect; // rect for IDirectDrawStreamSample* m_sample
	/*30,4*/	char* m_filename;
	/*34,4*/	IDirectDraw2* m_ddraw2;
	/*38*/
};
assert_sizeof(G98CMovie, 0x38);

struct G98CSurface // [Gods98/Animation.c|struct:0x98|tags:CLASS,VIRTUAL]
{
	/*00,4*/	G98CSurfaceVtbl* vftable;
	/*04,4*/	IDirectDrawClipper* m_clipper; // Clipper (init: 0, unused)
	/*08,1*/	bool m_surfaceLocked; // Is the surface currently locked
	/*09,3*/	uint8 padding1[3];
	/*0c,4*/	sint32 m_bpp; // Bits per pixel of the surface.
	/*10,4*/	IDirectDrawPalette* m_palette; // The Direct Draw palette
	/*14,1*/	bool m_colourKeyed; // Set to true if the surface has a transparent colour key.
	/*15,1*/	bool m_squashToEdge; // Squah the image up at the edge of the screen
	/*16,1*/	bool m_15bit; // The 16 bit mode is really fifteen bit
	/*17,1*/	bool m_surfaceInited; // Is the surface initialised
	/*18,4*/	IDirectDrawSurface4* m_surf; // Direct Draw surface.
	/*1c,7c*/	DDSURFACEDESC2 m_desc; // Description of the surface
	/*98*/
};
assert_sizeof(G98CSurface, 0x98);

struct G98CSurfaceVtbl // [Gods98/Animation.c|struct:0xc|tags:VFTABLE]
{
	/*0,4*/	G98CSurface* (* deletor)(G98CSurface*, uint8);
	/*4,4*/	sint32 (* Width)(G98CSurface*);
	/*8,4*/	sint32 (* Height)(G98CSurface*);
	/*c*/
};
assert_sizeof(G98CSurfaceVtbl, 0xc);

struct GameControl_Globs // [LegoRR/???|struct:0x180|tags:GLOBS]
{
	/*000,4*/	sint32 msy_Last_1;
	/*004,4*/	sint32 msx_Last_1;
	/*008,8*/	Point2F pointf_8;
	/*010,4*/	undefined4 reserved1;
	/*014,4*/	bool32 mslb_Last_1;
	/*018,4*/	bool32 renameUseQuotes;
	/*01c,4*/	undefined4 reserved2;
	/*020,100*/	bool typingState_Map[256];
	/*120,4*/	real32 dbgUpgradeChangeTimer;
	/*124,4*/	real32 dbgSpeedChangeTimer;
	/*128,4*/	real32 dbgRollOffChangeTimer;
	/*12c,4*/	real32 sceneFogDelta; // Delta value used in Lego_UpdateSceneFog ((M_PI*2)/fogRate * elapsed).
	/*130,4*/	bool32 handleKeysLastLeftMouseButtonDown; // Tracks mouse released state in Lego_HandleKeys
	/*134,4*/	real32 dbgCursorLightLevel;
	/*138,4*/	bool32 isGameSpeedLocked; // When this is TRUE, game speed can only be lowered when calling `Game_SetGameSpeed`.
	/*13c,4*/	bool32 mslb_Last_3;
	/*140,4*/	bool32 mslb_Last_4;
	/*144,8*/	Point2F pointf_144;
	/*14c,4*/	bool32 mslb_Last_5;
	/*150,4*/	bool32 mslb_Last_6;
	/*154,4*/	bool32 mslb_Last_0;
	/*158,4*/	bool32 mslr_Last_0;
	/*15c,4*/	real32 handleWorldNoMouseButtonsElapsed; // Duration that neither left or right mouse buttons have been down for (in game time).
	/*160,4*/	bool32 bool_160;
	/*164,4*/	LegoObject* toolTipObject;
	/*168,4*/	bool32 dbgF10InvertLighting;
	/*16c,4*/	bool32 dbgF9DisableLightEffects;
	/*170,4*/	undefined4 reserved3;
	/*174,4*/	LegoObject* dbgGetInVehicle; // (K debug key, assigned to selected vehicle, pressing K with a rock raider will tell them to get in this registered vehicle)
	/*178,4*/	Direction direction_178;
	/*17c,4*/	real32 timerTutorialBlockFlash;
	/*180*/
};
assert_sizeof(GameControl_Globs, 0x180);

struct Graphics_Device // [Gods98/DirectDraw.c|struct:0x114]
{
	/*000,10*/	GUID guid;
	/*010,100*/	char desc[256]; // "name (description)"
	/*110,4*/	Graphics_DeviceFlags flags;
	/*114*/
};
assert_sizeof(Graphics_Device, 0x114);

struct Graphics_Driver // [Gods98/DirectDraw.c|struct:0x114]
{
	/*000,10*/	GUID guid;
	/*010,100*/	char desc[256]; // "name (description)"
	/*110,4*/	Graphics_DriverFlags flags;
	/*114*/
};
assert_sizeof(Graphics_Driver, 0x114);

struct Graphics_Mode // [Gods98/DirectDraw.c|struct:0x110]
{
	/*000,4*/	uint32 width;
	/*004,4*/	uint32 height;
	/*008,4*/	uint32 bitDepth;
	/*00c,100*/	char desc[256]; // "WxH (BPP bit)", "WxH" (windowed)
	/*10c,4*/	Graphics_ModeFlags flags;
	/*110*/
};
assert_sizeof(Graphics_Mode, 0x110);

struct HelpWindow_Globs // [LegoRR/HelpWindow.c|struct:0xd6c|tags:GLOBS]
{
	/*000,4*/	Font* font;
	/*004,8*/	Point2F TextWindowPosition;
	/*00c,4*/	real32 TextWindowBottom; // (Position.y + height)
	/*010,4*/	Image* BackgroundImage;
	/*014,8*/	Point2F BackgroundPosition;
	/*01c,70*/	MenuButton Buttons[4]; // [Continue, CancelFutureButton, NULL, NULL]
	/*08c,4*/	TextWindow* textWnd;
	/*090,3c0*/	char* VehicleInfos[15][16];
	/*450,3c0*/	char* MiniFigureInfos[15][16];
	/*810,3c0*/	char* BuildingInfos[15][16];
	/*bd0,4*/	char* CanBuildMessage;
	/*bd4,4*/	char* CanTransportMessage;
	/*bd8,4*/	char* CanBuildAndTransportMessage;
	/*bdc,4*/	char* activeObjName;
	/*be0,4*/	LegoObject_Type activeObjType;
	/*be4,4*/	LegoObject_ID activeObjID;
	/*be8,4*/	uint32 activeObjLevel;
	/*bec,78*/	LegoObject_Type unlockedObjTypes[30];
	/*c64,78*/	LegoObject_ID unlockedObjIndexes[30];
	/*cdc,78*/	uint32 unlockedObjLevels[30];
	/*d54,4*/	uint32 unlockedCount;
	/*d58,4*/	real32 float_d58;
	/*d5c,4*/	real32 float_d5c;
	/*d60,4*/	uint32 count_d60;
	/*d64,4*/	undefined4 field_d64;
	/*d68,4*/	HelpWindow_GlobFlags flags;
	/*d6c*/
};
assert_sizeof(HelpWindow_Globs, 0xd6c);

struct HelpWindowInfoLevels // [LegoRR/HelpWindow.c|struct:0x40]
{
	/*00,40*/	char* levels[16];
	/*40*/
};
assert_sizeof(HelpWindowInfoLevels, 0x40);

struct HiddenObject // [LegoRR/LegoObject.c|struct:0x2c] Name is only guessed
{
	/*00,8*/	Point2I blockPos; // (ol: xPos, yPos -> blockPos)
	/*08,8*/	Point2F worldPos; // (ol: xPos, yPos)
	/*10,4*/	real32 heading; // (ol: heading -> radians)
	/*14,4*/	void* model; // (ol: type)
	/*18,4*/	LegoObject_Type type; // (ol: type)
	/*1c,4*/	LegoObject_ID id; // (ol: type)
	/*20,4*/	real32 health; // (ol: health)
	/*24,4*/	char* olistID; // (ol: Object%i)
	/*28,4*/	char* olistDrivingID; // (ol: driving)
	/*2c*/
};
assert_sizeof(HiddenObject, 0x2c);

struct HuffmanLeaf // [Gods98/Compress.c|struct:0x10]
{
	/*00,4*/	uint32 value_1;
	/*04,2*/	uint16 count_1;
	/*06,2*/	undefined2 padding1;
	/*08,4*/	uint32 value_2;
	/*0c,2*/	uint16 count_2; // (bit_depth)
	/*0e,2*/	undefined2 padding2;
	/*10*/
};
assert_sizeof(HuffmanLeaf, 0x10);

struct Image // [Gods98/Images.c|struct:0x20|tags:LISTSET]
{
	/*00,4*/	IDirectDrawSurface4* surface; // IDirectDrawSurface4
	/*04,4*/	uint32 width;
	/*08,4*/	uint32 height;
	/*0c,4*/	uint32 penZero; // Palette entry 0
	/*10,4*/	uint32 pen255; // Palette entry 255
	/*14,4*/	uint32 penZeroRGB; // Palette entry 0 (as unpacked RGB)
	/*18,4*/	ImageFlags flags; // 2 is font?
	/*1c,4*/	Image* nextFree;
	/*20*/
};
assert_sizeof(Image, 0x20);

struct Image_Globs // [Gods98/Images.c|struct:0x8c|tags:GLOBS]
{
	/*00,80*/	Image* listSet[32]; // Images list
	/*80,4*/	Image* freeList;
	/*84,4*/	uint32 listCount; // number of lists.
	/*88,4*/	uint32 flags;
	/*8c*/
};
assert_sizeof(Image_Globs, 0x8c);

struct Info_Globs // [LegoRR/Info.c|struct:0x6f4|tags:GLOBS]
{
	/*000,a0*/	char* infoName[40];
	/*0a0,320*/	InfoData infoDataTable[40];
	/*3c0,320*/	InfoMessage infoMessageTable[40];
	/*6e0,4*/	uint32 infoMessageCount;
	/*6e4,4*/	Font* font;
	/*6e8,4*/	Image* OverFlowImage;
	/*6ec,4*/	sint32 int_6ec;
	/*6f0,4*/	Info_GlobFlags flags;
	/*6f4*/
};
assert_sizeof(Info_Globs, 0x6f4);

struct InfoData // [LegoRR/Info.c|struct:0x14]
{
	/*00,4*/	char* text;
	/*04,4*/	void* ptr_4; // struct size of >= 0xc (int field_4, inf field_8)
	/*08,4*/	SFX_ID sfxType;
	/*0c,4*/	real32 float_c;
	/*10,4*/	InfoDataFlags flags;
	/*14*/
};
assert_sizeof(InfoData, 0x14);

struct InfoMessage // [LegoRR/Info.c|struct:0x14]
{
	/*00,4*/	InfoMessageInstance* instance;
	/*04,4*/	uint32 instanceCount;
	/*08,4*/	Info_Type infoType;
	/*0c,4*/	real32 float_c;
	/*10,4*/	InfoMessage* next;
	/*14*/
};
assert_sizeof(InfoMessage, 0x14);

struct InfoMessageInstance // [LegoRR/Info.c|struct:0x14]
{
	/*00,8*/	Point2I blockPos; // (-1, -1) for NULL blockPos
	/*08,4*/	LegoObject* object;
	/*0c,4*/	char* text;
	/*10,4*/	InfoMessageInstance* next;
	/*14*/
};
assert_sizeof(InfoMessageInstance, 0x14);

struct Init_Globs // [Gods98Init/Init.c|struct:0x1d444|tags:GLOBS]
{
	/*00000,4*/	uint32 driverCount;
	/*00004,4*/	uint32 deviceCount;
	/*00008,4*/	uint32 modeCount;
	/*0000c,1590*/	Graphics_Driver drivers[20];
	/*0159c,1590*/	Graphics_Device devices[20];
	/*02b2c,d480*/	Graphics_Mode modes[200];
	/*0ffac,4*/	Graphics_Driver* selDriver;
	/*0ffb0,4*/	Graphics_Device* selDevice;
	/*0ffb4,4*/	Graphics_Mode* selMode;
	/*0ffb8,4*/	bool32 selFullScreen;
	/*0ffbc,4*/	bool32 wasFullScreen; // Previous fullscreen state when Windowed button is disabled due to lack of support
	/*0ffc0,d480*/	Graphics_Mode validModes[200];
	/*1d440,4*/	uint32 validModeCount;
	/*1d444*/
};
assert_sizeof(Init_Globs, 0x1d444);

struct Input_Globs // [Gods98/Input.c|struct:0x280|tags:GLOBS]
{
	/*000,100*/	bool prevKey_Map[256];
	/*100,4*/	IDirectInputA* lpdi;
	/*104,4*/	IDirectInputDeviceA* lpdiKeyboard;
	/*108,4*/	IDirectInputDeviceA* lpdiMouse;
	/*10c,4*/	bool32 fKeybdAcquired;
	/*110,4*/	bool32 fMouseAcquired;
	/*114,10*/	RECT MouseBounds; // Bounding box in which mouse may move
	/*124,4*/	sint32 msx; // Current position of the mouse
	/*128,4*/	sint32 msy; // Current position of the mouse
	/*12c,4*/	sint32 prev_msx; // Previous position of the mouse
	/*130,4*/	sint32 prev_msy; // Previous position of the mouse
	/*134,4*/	sint32 diffx; // Relative movement of mouse cursor
	/*138,4*/	sint32 diffy; // Relative movement of mouse cursor
	/*13c,4*/	bool32 mslb; // Mouse buttons
	/*140,4*/	bool32 msrb; // Mouse buttons
	/*144,4*/	bool32 mslblast;
	/*148,4*/	bool32 mslbheld;
	/*14c,4*/	bool32 lClicked;
	/*150,4*/	bool32 rClicked;
	/*154,4*/	bool32 lDoubleClicked;
	/*158,4*/	bool32 rDoubleClicked;
	/*15c,4*/	bool32 caps;
	/*160,10*/	DIMOUSESTATE dims;
	/*170,c*/	DIcallbackData cbd;
	/*17c,1*/	char Input_KeyTemp;
	/*17d,3*/	uint8 padding1[3];
	/*180,100*/	bool Key_Map[256];
	/*280*/
};
assert_sizeof(Input_Globs, 0x280);

struct Interface_Globs // [LegoRR/Interface.c|struct:0x14ac|tags:GLOBS]
{
	/*0000,4*/	Font* font;
	/*0004,2c*/	Image* iconPanelImages[11]; // (cfg: InterfaceSurroundImages[0]) g_InterfaceSurroundImages
	/*0030,58*/	Point2F iconPanelIconOffsets[11]; // (cfg: InterfaceSurroundImages[1,2])
	/*0088,2c*/	Image* iconPanelNoBackImages[11]; // (cfg: InterfaceSurroundImages[5])
	/*00b4,58*/	Point2F iconPanelNoBackIconOffsets[11]; // (cfg: InterfaceSurroundImages[6,7])
	/*010c,4*/	Image* backButtonImage_hl; // (cfg: InterfaceBackButton[2])
	/*0110,4*/	Image* backButtonImage_pr; // (cfg: InterfaceBackButton[3])
	/*0114,58*/	Point2F iconPanelBackButtonOffsets[11]; // (cfg: InterfaceSurroundImages[3,4]) Point2F_ARRAY_004dde6c
	/*016c,8*/	Size2I backButtonSize; // (cfg: InterfaceBackButton[0,1])
	/*0174,4*/	char* backButtonText; // (cfg: InterfaceBackButton[4])
	/*0178,128*/	char* menuItemName[74];
	/*02a0,128*/	Image* menuItemIcons[74];
	/*03c8,128*/	Image* menuItemIcons_no[74];
	/*04f0,128*/	Image* menuItemIcons_pr[74];
	/*0618,128*/	char* langMenuItemTexts[74];
	/*0740,128*/	SFX_ID sfxMenuItemTexts[74];
	/*0868,4a*/	Keys8 menuItemF2keys[74];
	/*08b2,2*/	undefined2 padding1;
	/*08b4,128*/	Interface_MenuItemFlags menuItemFlags[74]; // (0x4: flashing)
	/*09dc,4*/	Image** vehicleItemIcons;
	/*09e0,4*/	Image** buildingItemIcons;
	/*09e4,4*/	Image** vehicleItemIcons_no;
	/*09e8,4*/	Image** buildingItemIcons_no;
	/*09ec,4*/	Image** vehicleItemIcons_pr;
	/*09f0,4*/	Image** buildingItemIcons_pr;
	/*09f4,128*/	char* langMenuItemTexts_no[74];
	/*0b1c,128*/	SFX_ID sfxMenuItemTexts_no[74];
	/*0c44,4*/	Keys8* vehicleItemF2Keys;
	/*0c48,4*/	Keys8* buildingItemF2Keys;
	/*0c4c,4*/	Interface_MenuItemFlags* vehicleItemFlags;
	/*0c50,4*/	Interface_MenuItemFlags* buildingItemFlags;
	/*0c54,128*/	uint32 menuItemClicks[74];
	/*0d7c,4*/	uint32* vehicleItemClicks;
	/*0d80,4*/	uint32* buildingItemClicks;
	/*0d84,128*/	bool32 menuItemUnkBools[74]; // (default: false)
	/*0eac,c0*/	Interface_Menu menuList[24];
	/*0f6c,8*/	Point2I selBlockPos;
	/*0f74,4*/	Interface_MenuType currMenuType;
	/*0f78,8*/	Point2F currMenuPosition; // (init: 565,18) Current sliding position of menu. Point2F_004decd0
	/*0f80,4*/	LegoObject_Type objType_f80;
	/*0f84,4*/	LegoObject_ID objID_f84;
	/*0f88,8*/	Point2F slideStartPosition; // Point2F_004dece0
	/*0f90,8*/	Point2F slideEndPosition; // (init: pointf_f78) Point2F_004dece8
	/*0f98,4*/	real32 slideSpeed; // (init: 750.0f / 25.0f)
	/*0f9c,8*/	Point2I highlightBlockPos;
	/*0fa4,4*/	Interface_MenuType nextMenuType;
	/*0fa8,4*/	Interface_MenuItemType menuItemType_fa8;
	/*0fac,4*/	undefined4 field_fac;
	/*0fb0,4*/	undefined4 field_fb0;
	/*0fb4,10*/	Area2F areaf_fb4;
	/*0fc4,4*/	bool32 flashingState; // For block and icon flashing. false = off, true = on.
	/*0fc8,4*/	real32 timer_fc8;
	/*0fcc,4*/	Advisor_Type advisorType_fcc;
	/*0fd0,4*/	Interface_MenuItemType menuItemType_fd0;
	/*0fd4,4*/	LegoObject_Type objType_fd4;
	/*0fd8,4*/	LegoObject_ID objID_fd8;
	/*0fdc,4b0*/	bool32 objectBools[20][15];
	/*148c,4*/	Image* dependenciesPlusImage;
	/*1490,4*/	Image* dependenciesMinusImage;
	/*1494,4*/	real32 float_1494;
	/*1498,4*/	WallHighlightType origWallHighlight; // (backup for when a wall has a queued action, but we want it to show the selected colour)
	/*149c,4*/	SFX_ID sfxType_149c;
	/*14a0,4*/	Interface_GlobFlags flags;
	/*14a4,4*/	SFX_ID sfxType_14a4;
	/*14a8,4*/	bool32 sfxPlaying;
	/*14ac*/
};
assert_sizeof(Interface_Globs, 0x14ac);

struct Interface_Menu // [LegoRR/Interface.c|struct:0x8] Simple list of icons-by-enum for an interface menu.
{
	/*0,4*/	Interface_MenuItemType* iconList;
	/*4,4*/	uint32 iconCount;
	/*8*/
};
assert_sizeof(Interface_Menu, 0x8);

struct Key_Globs // [Gods98/Keys.c|struct:0x400|tags:GLOBS]
{
	/*000,400*/	char* keyName[256];
	/*400*/
};
assert_sizeof(Key_Globs, 0x400);

#pragma pack(push, 1)
struct Lego_Block // [LegoRR/Lego.c|struct:0x48|pack:1]
{
	/*00,1*/	Lego_PredugType predug;
	/*01,1*/	SurfaceTexture texture;
	/*02,1*/	Lego_SurfaceType8 terrain;
	/*03,1*/	uint8 direction; // clockwise (does not determine corner/wall type)
	/*04,1*/	uint8 blockpointer;
	/*05,1*/	Lego_CryOreType cryOre;
	/*06,1*/	Lego_ErodeType erodeSpeed;
	/*07,1*/	uint8 erodeLevel; // 0 = low, 1 = med, 2 = high, 3 = max, 4 = lava
	/*08,4*/	BlockFlags1 flags1;
	/*0c,4*/	BlockFlags2 flags2;
	/*10,4*/	Construction_Zone* construct;
	/*14,4*/	real32 damage; // drill damage [0.0-1.0]
	/*18,4*/	Lego_BlockActivity* activity;
	/*1c,4*/	Smoke* smoke;
	/*20,2*/	sint16 randomness; // (sometimes sign-extended)
	/*22,2*/	uint16 seamDigCount; // Number of times a seam has been dug (destroyed at 4).
	/*24,4*/	uint32 numLandSlides;
	/*28,4*/	uint32 clickCount;
	/*2c,4*/	sint32 generateCrystals;
	/*30,4*/	sint32 generateOre;
	/*34,1*/	uint8 aiNode;
	/*35,3*/	undefined field_0x35_0x37[3];
	/*38,4*/	bool32 fallinUpper; // (fallin upper: 1 if fallin > 4)
	/*3c,4*/	sint32 fallinIntensity; // (fallin scale: 1-4)
	/*40,4*/	real32 fallinTimer; // (randomized with full fallin value)
	/*44,4*/	bool32 tutoHighlightState; // Tutorial block highlight color (false = tutorial color, true = normal).
	/*48*/
};
assert_sizeof(Lego_Block, 0x48);
#pragma pack(pop)

struct Lego_BlockActivity // [LegoRR/Lego.c|struct:0x1c] An effect or activity container attached to an individual block (only one per block max).
{
	/*00,4*/	Container* cont;
	/*04,8*/	Point2I blockPos;
	/*0c,1*/	BlockActivityFlags flags; // (0x1=?, 0x2=?, 0x4=?)
	/*0d,3*/	undefined field_0xd_0xf[3];
	/*10,4*/	Lego_BlockActivity* next;
	/*14,4*/	Lego_BlockActivity* previous;
	/*18,4*/	bool32 staticEffect; // (0 = reinforcement, 1 = recharge seam twinkle?)
	/*1c*/
};
assert_sizeof(Lego_BlockActivity, 0x1c);

struct Lego_Globs // [LegoRR/Lego.c|struct:0xf00|tags:GLOBS]
{
	/*000,4*/	Config* config;
	/*004,4*/	char* gameName;
	/*008,4*/	undefined4 field_8;
	/*00c,4*/	undefined4 field_c;
	/*010,4*/	Graphics_Quality quality; // (cfg: Main::Quality)
	/*014,4*/	Lego_Level* currLevel;
	/*018,4*/	Container* rootCont; // containerGlobs.root
	/*01c,4*/	Viewport* viewMain; // Viewport area: (0.0,0.0 - 1.0x1.0)
	/*020,4*/	Viewport* viewTrack; // Viewport area: (16,14 - 151x151)
	/*024,4*/	LegoCamera* cameraMain;
	/*028,4*/	LegoCamera* cameraTrack;
	/*02c,4*/	LegoCamera* cameraFP;
	/*030,4*/	Container* spotlightTop;
	/*034,4*/	Container* spotlightTrack;
	/*038,4*/	Container* pointLightFP;
	/*03c,4*/	Container* dirLightFP;
	/*040,4*/	Container* ambientLight;
	/*044,4*/	Container* rootSpotlight;
	/*048,4*/	Container* rootLight;
	/*04c,4*/	Container* dirLightCallToArms;
	/*050,4*/	real32 FPClipBlocks; // (cfg: Main::FPClipBlocks)
	/*054,4*/	real32 TVClipDist; // (cfg: Main::TVClipDist)
	/*058,4*/	undefined4 field_58;
	/*05c,4*/	undefined4 field_5c;
	/*060,4*/	undefined4 field_60;
	/*064,4*/	Font* fontStandard; // Loader, Debug text, Level Select window, Pull-out info icon window, (unused) Info, Encyclopedia(?).
	/*068,4*/	Font* fontToolTip; // ToolTip, CryOre count, Unit custom name, Teleporter queued, Interface UPG(???), Info icon count.
	/*06c,4*/	Font* fontTallYellow; // (unused) Block / Vertex mode for unimplemented SingleWidthDig feature.
	/*070,4*/	Font* fontTextWindow; // TextMessage window (same as fontStandard).
	/*074,4*/	Font* fontBriefingLo; // Dark text color used by most menus that share the briefing menu background.
	/*078,4*/	Font* fontBriefingHi; // Bright text color used by most menus that share the briefing menu background.
	/*07c,4*/	Font* fontCredits; // Credits roll only.
	/*080,4*/	TextWindow* textOnlyWindow;
	/*084,4*/	TextWindow* textImageWindow; // Same as textOnlyWindow, but used instead when there's an image.
	/*088,8*/	Point2F gotoNewPos; // Upcoming/current 2D world position used when programatically moving the camera.
	/*090,8*/	Point2F gotoTargetPos; // Desired 2D world position used when programatically moving the camera (using Smooth option)
	/*098,4*/	bool32 gotoSmooth; // When false, gotoNewPos is the target position (aka, camera smoothing).
	/*09c,4*/	real32 gameSpeed;
	/*0a0,4*/	LegoObject* objectFP;
	/*0a4,c*/	Vector3F vectorDragStartUnk_a4;
	/*0b0,4*/	real32 float_b0;
	/*0b4,4*/	real32 float_b4;
	/*0b8,4*/	real32 float_b8;
	/*0bc,4*/	real32 float_bc;
	/*0c0,8*/	Point2I digVertexBlockPos; // Drilling pointer block position for unused Vertex Mode (SingleWidthDig).
	/*0c8,4*/	bool32 digVertexShowPointer; // Used with: digVertexBlockPos
	/*0cc,4*/	char* langPowerCrystal_name; // (cfg: ObjectNames)
	/*0d0,4*/	char* langOre_name; // (cfg: ObjectNames)
	/*0d4,4*/	char* langProcessedOre_name; // (cfg: ObjectNames)
	/*0d8,4*/	char* langDynamite_name; // (cfg: ObjectNames)
	/*0dc,4*/	char* langBarrier_name; // (cfg: ObjectNames)
	/*0e0,4*/	char* langElectricFence_name; // (cfg: ObjectNames)
	/*0e4,4*/	char* langSpiderWeb_name; // (cfg: ObjectNames)
	/*0e8,4*/	char* langOohScary_name; // (cfg: ObjectNames)
	/*0ec,4*/	char* langPath_name; // (cfg: ObjectNames)
	/*0f0,4*/	char* langPowerCrystal_theName; // (cfg: ObjectTheNames)
	/*0f4,4*/	char* langOre_theName; // (cfg: ObjectTheNames)
	/*0f8,4*/	char* langProcessedOre_theName; // (cfg: ObjectTheNames)
	/*0fc,4*/	char* langDynamite_theName; // (cfg: ObjectTheNames)
	/*100,4*/	char* langBarrier_theName; // (cfg: ObjectTheNames)
	/*104,4*/	char* langElectricFence_theName; // (cfg: ObjectTheNames)
	/*108,4*/	char* langSpiderWeb_theName; // (cfg: ObjectTheNames)
	/*10c,4*/	char* langOohScary_theName; // (cfg: ObjectTheNames)
	/*110,4*/	char* langPath_theName; // (cfg: ObjectTheNames)
	/*114,4*/	VehicleModel* vehicleData; // (cfg: VehicleTypes)
	/*118,4*/	CreatureModel* miniFigureData; // (cfg: MiniFigureTypes)
	/*11c,4*/	CreatureModel* rockMonsterData; // (cfg: RockMonsterTypes)
	/*120,4*/	BuildingModel* buildingData; // (cfg: BuildingTypes)
	/*124,4*/	Upgrade_PartModel* upgradeData; // (cfg: UpgradeTypes)
	/*128,4*/	char** vehicleName; // (cfg: VehicleTypes)
	/*12c,4*/	char** miniFigureName; // (cfg: MiniFigureTypes)
	/*130,4*/	char** rockMonsterName; // (cfg: RockMonsterTypes)
	/*134,4*/	char** buildingName; // (cfg: BuildingTypes)
	/*138,4*/	char** upgradeName; // (cfg: UpgradeTypes)
	/*13c,2c*/	char* toolName[11];
	/*168,2c*/	char* langTool_name[11]; // (cfg: ToolNames)
	/*194,4*/	char** langVehicle_name; // (cfg: ObjectNames)
	/*198,4*/	char** langMiniFigure_name; // (cfg: ObjectNames)
	/*19c,4*/	char** langRockMonster_name; // (cfg: ObjectNames)
	/*1a0,4*/	char** langBuilding_name; // (cfg: ObjectNames)
	/*1a4,4*/	char** langUpgrade_name; // (cfg: ObjectNames) never specified in Lego.cfg
	/*1a8,4*/	char** langVehicle_theName; // (cfg: ObjectTheNames)
	/*1ac,4*/	char** langMiniFigure_theName; // (cfg: ObjectTheNames)
	/*1b0,4*/	char** langRockMonster_theName; // (cfg: ObjectTheNames)
	/*1b4,4*/	char** langBuilding_theName; // (cfg: ObjectTheNames)
	/*1b8,4*/	char** langUpgrade_theName; // (cfg: ObjectTheNames) never specified in Lego.cfg
	/*1bc,4*/	uint32 vehicleCount; // (cfg: VehicleTypes)
	/*1c0,4*/	uint32 miniFigureCount; // (cfg: MiniFigureTypes)
	/*1c4,4*/	uint32 rockMonsterCount; // (cfg: RockMonsterTypes)
	/*1c8,4*/	uint32 buildingCount; // (cfg: BuildingTypes)
	/*1cc,4*/	uint32 upgradeCount; // (cfg: UpgradeTypes)
	/*1d0,48*/	char* surfaceName[18];
	/*218,48*/	char* langSurface_name[18]; // (cfg: SurfaceTypeDescriptions)
	/*260,48*/	SFX_ID langSurface_sound[18]; // (cfg: SurfaceTypeDescriptions)
	/*2a8,4*/	Container* contBoulder;
	/*2ac,4*/	Container* contBoulderExplode;
	/*2b0,4*/	Container* contBoulderExplodeIce;
	/*2b4,4*/	Container* contCrystal;
	/*2b8,4*/	Container* contDynamite;
	/*2bc,8*/	Container* contOresTable[2];
	/*2c4,4*/	Container* contOohScary;
	/*2c8,4*/	Container* contBarrier;
	/*2cc,4*/	Container* contElectricFence;
	/*2d0,4*/	Container* contSpiderWeb;
	/*2d4,4*/	Container* contRechargeSparkle;
	/*2d8,4*/	Container* contMiniTeleportUp;
	/*2dc,4*/	Container* contElectricFenceStud;
	/*2e0,4*/	Container* contPusher;
	/*2e4,4*/	Container* contFreezer;
	/*2e8,4*/	Container* contIceCube;
	/*2ec,4*/	Container* contSmashPath;
	/*2f0,4*/	Container* contLaserShot;
	/*2f4,4*/	SelectPlace* selectPlace;
	/*2f8,28*/	LegoObject* recordObjs[10];
	/*320,4*/	uint32 recordObjsCount;
	/*324,10*/	Area2F radarScreenRect;
	/*334,4*/	real32 radarZoom;
	/*338,8*/	Point2F radarCenter;
	/*340,4*/	real32 MedPolyRange; // (cfg: Main::MedPolyRange)
	/*344,4*/	real32 HighPolyRange; // (cfg: Main::HighPolyRange)
	/*348,4*/	sint32 HPBlocks; // (cfg: Main::HPBlocks)
	/*34c,c*/	ColourRGBF FogColourRGB; // (cfg: Level::FogColourRGB)
	/*358,c*/	ColourRGBF HighFogColourRGB; // (cfg: Level::HighFogColourRGB)
	/*364,4*/	real32 float_364; // level-related?
	/*368,c*/	ColourRGBF PowerCrystalRGB; // (cfg: Main::PowerCrystalRGB)
	/*374,c*/	ColourRGBF UnpoweredCrystalRGB; // (cfg: Main::UnpoweredCrystalRGB)
	/*380,4*/	LegoObject_Type placeObjType;
	/*384,4*/	LegoObject_ID placeObjID;
	/*388,4*/	Direction placeObjDirection;
	/*38c,4*/	LegoObject* placeDestSmallTeleporter;
	/*390,4*/	LegoObject* placeDestBigTeleporter;
	/*394,4*/	LegoObject* placeDestWaterTeleporter;
	/*398,4*/	real32 MinEnergyForEat; // (cfg: Main::MinEnergyForEat)
	/*39c,4*/	Image* TutorialIcon; // (cfg: Main::TutorialIcon)
	/*3a0,4*/	undefined4 field_3a0;
	/*3a4,4*/	real32 DynamiteDamageRadius; // (cfg: Main::DynamiteDamageRadius)
	/*3a8,4*/	real32 DynamiteMaxDamage; // (cfg: Main::DynamiteMaxDamage)
	/*3ac,4*/	real32 DynamiteWakeRadius; // (cfg: Main::DynamiteWakeRadius)
	/*3b0,4*/	real32 BirdScarerRadius; // (cfg: Main::BirdScarerRadius)
	/*3b4,50*/	LegoObject_Type objTeleportQueueTypes_TABLE[20];
	/*404,50*/	LegoObject_ID objTeleportQueueIDs_TABLE[20];
	/*454,4*/	uint32 objTeleportQueue_COUNT;
	/*458,4*/	real32 MiniFigureRunAway; // (cfg: Main::MiniFigureRunAway)
	/*45c,c*/	Vector3F mouseWorldPos;
	/*468,320*/	Point2I powerDrainBlocks[100]; // Temporary list used during powergrid calculation.
	/*788,4*/	uint32 powerDrainCount;
	/*78c,320*/	Point2I poweredBlocks[100]; // Related to power grid calculation.
	/*aac,320*/	Point2I unpoweredBlocks[100];
	/*dcc,4*/	uint32 poweredBlockCount;
	/*dd0,4*/	uint32 unpoweredBlockCount;
	/*dd4,4*/	uint32 MaxReturnedCrystals; // (cfg: Main::MaxReturnedCrystals)
	/*dd8,4*/	sint32 MouseScrollBorder; // (cfg: Main::MouseScrollBorder)
	/*ddc,4*/	char* langHealth_toolTip; // (cfg: ToolTipInfo::HealthText)
	/*de0,4*/	char* langEnergy_toolTip; // (cfg: ToolTipInfo::EnergyText)
	/*de4,4*/	char* langCrystals_toolTip; // (cfg: ToolTipInfo::CrystalsText)
	/*de8,4*/	char* langOre_toolTip; // (cfg: ToolTipInfo::OreText)
	/*dec,4*/	char* langStuds_toolTip; // (cfg: ToolTipInfo::StudsText)
	/*df0,4*/	char* langTools_toolTip; // (cfg: ToolTipInfo::ToolsText)
	/*df4,4*/	char* langCarryObject_toolTip; // (cfg: ToolTipInfo::CarryObjectText)
	/*df8,4*/	char* langDrivenBy_toolTip; // (cfg: ToolTipInfo::DrivenByText)
	/*dfc,4*/	char* langOreRequired_toolTip; // (cfg: ToolTipInfo::OreRequiredText)
	/*e00,4*/	bool32 IsFallinsEnabled; // (cfg not: Level::NoFallins)
	/*e04,4*/	real32 MinDistFor3DSoundsOnTopView; // (cfg: Main::MinDistFor3DSoundsOnTopView)
	/*e08,4*/	ViewMode viewMode; // FirstPerson or TopDown
	/*e0c,4*/	GameFlags1 flags1;
	/*e10,4*/	GameFlags2 flags2;
	/*e14,4*/	GameFlags3 flags3; // only first byte is used(?)
	/*e18,4*/	real32 InitialSlugTime; // (cfg: Level::InitialSlugTime)
	/*e1c,8*/	Point2F NextButtonPos; // (cfg: Main::NextButtonPos<WxH>)
	/*e24,8*/	Point2F RepeatButtonPos; // (cfg: Main::BackButtonPos<WxH>)
	/*e2c,4*/	Image* NextButtonImage; // (cfg: Main::NextButton<WxH>)
	/*e30,4*/	Image* RepeatButtonImage; // (cfg: Main::BackButton<WxH>)
	/*e34,4*/	Image* BackArrowImage; // (cfg: Main::BackArrow)
	/*e38,4*/	real32 FogRate; // (cfg: Level::FogRate)
	/*e3c,4*/	real32 timerGame_e3c;
	/*e40,4*/	real32 elapsedAbs;
	/*e44,4*/	real32 DrainTime; // (cfg: Main::DrainTime)
	/*e48,4*/	uint32 ReinforceHits; // (cfg: Main::ReinforceHits)
	/*e4c,4*/	uint32 CDStartTrack; // (cfg: Main::CDStartTrack)
	/*e50,4*/	uint32 CDTracks; // (cfg: Main::CDTracks)
	/*e54,4*/	uint32 FallinMultiplier; // (cfg: Level::FallinMultiplier)
	/*e58,4*/	bool32 hasFallins;
	/*e5c,8*/	Point2F menuNextPoint;
	/*e64,8*/	Point2F menuPrevPoint;
	/*e6c,c*/	ColourRGBF DragBoxRGB; // (cfg: Level::DragBoxRGB)
	/*e78,4*/	Image* DialogImage; // (cfg: Dialog::Image)
	/*e7c,4*/	Image* DialogContrastOverlay; // (cfg: Dialog::ContrastOverlay)
	/*e80,4*/	TextWindow* DialogTextWndTitle; // (cfg: Dialog::TitleWindow)
	/*e84,4*/	TextWindow* DialogTextWndMessage; // (cfg: Dialog::TextWindow)
	/*e88,4*/	TextWindow* DialogTextWndOK; // (cfg: Dialog::OKWindow)
	/*e8c,4*/	TextWindow* DialogTextWndCancel; // (cfg: Dialog::CancelWindow)
	/*e90,4*/	char* CreditsTextFile; // (cfg: Main::CreditsTextFile)
	/*e94,4*/	char* CreditsBackAVI; // (cfg: Main::CreditsBackAVI)
	/*e98,40*/	char* langUpgradeLevel_name[16]; // (cfg: UpgradeNames)
	/*ed8,4*/	sint32 BuildingUpgradeCostOre; // (cfg: Main::BuildingUpgradeCostOre)
	/*edc,4*/	sint32 BuildingUpgradeCostStuds; // (cfg: Main::BuildingUpgradeCostStuds)
	/*ee0,4*/	char* renameInput;
	/*ee4,8*/	Point2F renamePosition;
	/*eec,4*/	char* RenameReplace; // (cfg: Main::RenameReplace)
	/*ef0,4*/	char* EndGameAVI1; // (cfg: Level::EndGameAVI1)
	/*ef4,4*/	char* EndGameAVI2; // (cfg: Level::EndGameAVI2)
	/*ef8,8*/	Point2I mouseBlockPos; // (static, Game_unkGameLoop_FUN_00426450)
	/*f00*/
};
assert_sizeof(Lego_Globs, 0xf00);

struct Lego_Level // [LegoRR/Lego.c|struct:0x284]
{
	/*000,4*/	char* name; // (format: "Levels::level")
	/*004,4*/	Map3D* map;
	/*008,4*/	EmergeTrigger* emergeTriggers;
	/*00c,4*/	uint32 emergeCount;
	/*010,4*/	undefined4 unused_rewardID; // Presumably used to lookup level rewards by some constant ID value.
	/*014,4*/	uint32 width;
	/*018,4*/	uint32 height;
	/*01c,4*/	real32 BlockSize;
	/*020,4*/	real32 DigDepth;
	/*024,4*/	real32 RoofHeight;
	/*028,4*/	real32 RoughLevel;
	/*02c,4*/	BoolTri UseRoof;
	/*030,4*/	BoolTri SafeCaverns;
	/*034,4*/	real32 SelBoxHeight;
	/*038,4*/	undefined4 field_0x38;
	/*03c,4*/	undefined4 field_0x3c;
	/*040,4*/	undefined4 field_0x40;
	/*044,4*/	undefined4 field_0x44;
	/*048,4*/	undefined4 field_0x48;
	/*04c,4*/	undefined4 field_0x4c;
	/*050,4*/	undefined4 field_0x50;
	/*054,4*/	undefined4 field_0x54;
	/*058,4*/	undefined4 field_0x58;
	/*05c,4*/	undefined4 field_0x5c;
	/*060,4*/	undefined4 field_0x60;
	/*064,4*/	undefined4 field_0x64;
	/*068,4*/	undefined4 field_0x68;
	/*06c,4*/	undefined4 field_0x6c;
	/*070,4*/	undefined4 field_0x70;
	/*074,8*/	Size2I textureSetSize; // surface texture width and height
	/*07c,4*/	Detail_TextureSet* textureSet;
	/*080,4*/	Detail_Mesh** promeshGrid;
	/*084,4*/	RadarMap* radarMap;
	/*088,4*/	Lego_BlockActivity* blockActLast; // Tail of doubly-linked list of block effects.
	/*08c,4*/	sint32 crystals; // (init: 0) Total number of Crystals stored.
	/*090,4*/	undefined4 unused_crystals_90; // (init: 0, unused) Presumably once for Crystals.
	/*094,4*/	sint32 crystalsPickedUp; // (init: 0) Used by NERPs:GetCrystalsPickedUp.
	/*098,4*/	sint32 crystalsDrained; // Crystals stored, but in-use powering buildings.
	/*09c,4*/	sint32 crystalsStolen; // For checking MaxStolen failure condition.
	/*0a0,4*/	sint32 ore; // (init: 0) Total number of normal Ore stored. (EXCLUDES STUDS)
	/*0a4,4*/	undefined4 unused_ore_a4; // (init: 0, unused) Presumably once for Ore.
	/*0a8,4*/	sint32 orePickedUp; // (init: 0) Used by NERPs:GetOrePickedUp.
	/*0ac,4*/	sint32 studs; // (init: 0) Total number of Studs stored. (1 stud == 5 ore)
	/*0b0,4*/	sint32 EmergeCreature; // (searches for Object ID by name, expects RockMonsterType)
	/*0b4,4*/	char* nextLevelID; // (cfg: NextLevel)
	/*0b8,4*/	Lego_Block* blocks; // grid of blocks [y][x]
	/*0bc,54*/	ObjectiveData objective;
	/*110,4*/	bool32 hasBlockPointers;
	/*114,e0*/	BlockPointer* blockPointers[56];
	/*1f4,4*/	bool32 StartFP;
	/*1f8,4*/	bool32 NoDrain;
	/*1fc,4*/	real32 oxygenLevel; // (init: 100.0, Oxygen level?)
	/*200,4*/	real32 OxygenRate;
	/*204,4*/	real32 oxygenLevelMessage; // Tracks change in oxygen since the last message (new message after change of 5%).
	/*208,4*/	real32 BuildingTolerance; // (default: 4.0)
	/*20c,4*/	real32 BuildingMaxVariation; // (default: 6.0)
	/*210,50*/	real32 UpgradeTimes[20]; // [objType] (mult: 25.0, 1:Vehicle, 2:MiniFigure, 3:Building)
	/*260,4*/	real32 TrainTime; // (mult: 25.0)
	/*264,4*/	real32 EmergeTimeOut; // (default: 1500.0)
	/*268,4*/	real32 SlugTime; // (default: 60.0, mult: 25.0 (applies to default))
	/*26c,4*/	sint32 Slug; // (default: 20 (invalid), searches for object index by name, expects RockMonsterType)
	/*270,4*/	char* FullName; // (replace '_' with ' ')
	/*274,4*/	TextureType BoulderAnimation; // (texture index, hardcoded: Rock, Lava, Ice)
	/*278,4*/	real32 MaxStolen;
	/*27c,4*/	LevelStatus status; // (init: 0) 2 is used for Crystal failure as well
	/*280,4*/	bool32 IsStartTeleportEnabled; // (! DisableStartTeleport)
	/*284*/
};
assert_sizeof(Lego_Level, 0x284);

struct LegoCamera // [LegoRR/LegoCamera.c|struct:0xbc] May be camera data (which is related to- but not the same as viewports)
{
	/*00,4*/	LegoCamera_Type type;
	/*04,4*/	LegoObject* trackObj;
	/*08,4*/	real32 trackRadarZoomSpeed;
	/*0c,4*/	real32 trackRadarZoom;
	/*10,4*/	real32 trackRadarRotationSpeed; // A constant yaw H rotation speed applied to tracked radar objects
	/*14,4*/	sint32 trackFPCameraFrame; // CameraFrameIndex for FP object SwapPolyFP
	/*18,c*/	Vector3F moveVector; // current 3D (really 2D) movement and directional speed
	/*24,4*/	Container* contCam; // only cont parented for FP type (child of contRoot if FP)
	/*28,4*/	Container* cont2; // child of contRoot
	/*2c,4*/	Container* cont3; // child of contRoot
	/*30,4*/	Container* cont4; // child of cont2
	/*34,4*/	Container* contListener; // child of cont4 (topdown type only)
	/*38,40*/	undefined reserved1[64];
	/*78,4*/	real32 tilt; // (init: 0.0f) current tilt (Pitch, V Rotation)
	/*7c,8*/	Range2F tiltRange; // min/max tilt (Pitch, V Rotation)
	/*84,4*/	real32 rotation; // (init: 0.0f) current yaw (Angle, H Rotation)
	/*88,8*/	Range2F rotationRange; // min/max yaw (Angle, H Rotation)
	/*90,4*/	real32 zoom; // (init: 200.0f) current dist (Zoom)
	/*94,8*/	Range2F zoomRange; // min/max dist (Zoom)
	/*9c,4*/	real32 moveSpeed; // current 3D (really 2D) movement speed
	/*a0,4*/	real32 shakeIntensity;
	/*a4,4*/	real32 shakeDuration;
	/*a8,4*/	real32 shakeTimer; // count-up timer until shakeDuration
	/*ac,c*/	Vector3F shakeVector;
	/*b8,4*/	CameraFlags flags;
	/*bc*/
};
assert_sizeof(LegoCamera, 0xbc);

struct LegoObject // [LegoRR/LegoObject.c|struct:0x40c|tags:LISTSET]
{
	/*000,4*/	LegoObject_Type type;
	/*004,4*/	LegoObject_ID id;
	/*008,4*/	char* customName; // max size is 11 (NOT null-terminated)
	/*00c,4*/	VehicleModel* vehicle; // Model for vehicle objects only.
	/*010,4*/	CreatureModel* miniFigure; // Model for mini-figure objects only.
	/*014,4*/	CreatureModel* rockMonster; // Model for monster objects only.
	/*018,4*/	BuildingModel* building; // Model for building objects only.
	/*01c,4*/	Container* other; // Model for simple objects only.
	/*020,4*/	Upgrade_PartModel* upgradePart; // First upgrade part model in linked list of parts.
	/*024,4*/	RoutingBlock* routeBlocks; // Unknown pointer, likely in large allocated table
	/*028,4*/	uint32 routeBlocksTotal; // total blocks to travel for current route
	/*02c,4*/	uint32 routeBlocksCurrent; // number of blocks traveled (up to routingBlocksTotal)
	/*030,25c*/	BezierCurve routeCurve; // BezierCurve/Catmull-rom spline data
	/*28c,4*/	real32 routeCurveTotalDist;
	/*290,4*/	real32 routeCurveCurrDist;
	/*294,4*/	real32 routeCurveInitialDist; // Used as spill-over when distance traveled is beyond routeCurveTotalDist.
	/*298,8*/	Point2F point_298;
	/*2a0,c*/	Vector3F tempPosition; // Last position used for finding new face direction when moving.
	/*2ac,c*/	Vector3F faceDirection; // 1.0 to -1.0 directions that determine rotation with atan2
	/*2b8,4*/	real32 faceDirectionLength; // faceDirection length (faceDirection may be Vector4F...)
	/*2bc,4*/	sint32 strafeSignFP; // (direction sign only, does higher numbers do not affect speed)
	/*2c0,4*/	sint32 forwardSignFP; // (direction sign only, does higher numbers do not affect speed)
	/*2c4,4*/	real32 rotateSpeedFP;
	/*2c8,c*/	Vector3F dirVector_2c8; // Always (0.0f, 0.0f, 0.0f)
	/*2d4,4*/	real32 animTime;
	/*2d8,4*/	uint32 animRepeat; // Number of times an activity animation is set to repeat (i.e. number of jumping jacks/reinforce hits). Zero is default.
	/*2dc,4*/	Container* cameraNull;
	/*2e0,4*/	uint32 cameraFrame;
	/*2e4,4*/	Container* contMiniTeleportUp;
	/*2e8,4*/	char* activityName1;
	/*2ec,4*/	char* activityName2; // Seems to be used with related objects like driven, swapped with activityName1.
	/*2f0,4*/	AITask* aiTask; // Linked list of tasks (or null). Linked using the `AITask::next` field.
	/*2f4,8*/	Point2F targetBlockPos; // (init: -1.0f, -1.0f)
	/*2fc,4*/	LegoObject* routeToObject;
	/*300,4*/	LegoObject* interactObject; // Used in combination with routeToObject for Upgrade station and RM boulders.
	/*304,4*/	LegoObject* carryingThisObject;
	/*308,18*/	LegoObject* carriedObjects[6]; // (includes carried vehicles)
	/*320,4*/	uint32 carryingIndex; // Index of carried object in holder's carriedObjects list.
	/*324,4*/	uint32 numCarriedObjects;
	/*328,4*/	uint32 carryNullFrames;
	/*32c,4*/	Flocks* flocks;
	/*330,4*/	uint32 objLevel;
	/*334,4*/	ObjectStats* stats;
	/*338,4*/	real32 aiTimer_338;
	/*33c,4*/	real32 carryRestTimer_33c;
	/*340,4*/	real32 health; // (init: -1.0f)
	/*344,4*/	real32 energy; // (init: -1.0f)
	/*348,4*/	sint32* stolenCrystalLevels; // (alloc: new int[6]) Each element is the count stolen for a level, index 0 only seems to be used for recovery
	/*34c,4*/	LOD_PolyLevel polyLOD;
	/*350,4*/	sint32 drillSoundHandle; // Handle returned by SFX_Play functions
	/*354,4*/	sint32 engineSoundHandle; // Handle returned by SFX_Play functions
	/*358,4*/	real32 weaponSlowDeath;
	/*35c,4*/	uint32 weaponID;
	/*360,4*/	real32 weaponRechargeTimer;
	/*364,4*/	LegoObject* freezeObject; // (bi-directional link between frozen RockMonster and IceCube)
	/*368,4*/	real32 freezeTimer;
	/*36c,4*/	LegoObject* driveObject; // (bi-directional link between driver and driven)
	/*370,14*/	LegoObject_ToolType carriedTools[5];
	/*384,4*/	uint32 numCarriedTools;
	/*388,4*/	real32 bubbleTimer;
	/*38c,4*/	Image* bubbleImage;
	/*390,4*/	uint32 teleporter_modeFlags;
	/*394,4*/	uint32 teleporter_teleportFlags;
	/*398,4*/	TeleporterService* teleporter;
	/*39c,c*/	Vector3F beamVector_39c; // (used for unkWeaponTypes 1-3 "Lazer", "Pusher", "Freezer")
	/*3a8,c*/	Vector3F weaponVector_3a8; // (used for unkWeaponType 4 "Lazer")
	/*3b4,8*/	Point2F pushingVec2D;
	/*3bc,4*/	real32 pushingDist;
	/*3c0,4*/	LegoObject* throwObject; // (bi-directional link between thrower and thrown)
	/*3c4,4*/	LegoObject* projectileObject; // Projectile fired from weapon.
	/*3c8,4*/	undefined4 field_3c8; // (unused?)
	/*3cc,4*/	LegoObject* teleportDownObject;
	/*3d0,4*/	real32 damageNumbers; // Used to display damage text over objects.
	/*3d4,4*/	real32 elapsedTime1; // elapsed time counter 1
	/*3d8,4*/	real32 elapsedTime2; // elapsed time counter 2
	/*3dc,4*/	real32 eatWaitTimer; // Unit will try to find food once the timer reaches 125.
	/*3e0,4*/	LiveFlags1 flags1; // State flags for the object's current activity/behavior.
	/*3e4,4*/	LiveFlags2 flags2;
	/*3e8,4*/	LiveFlags3 flags3;
	/*3ec,4*/	LiveFlags4 flags4;
	/*3f0,4*/	LegoObject_AbilityFlags abilityFlags; // (orig: flags5) Trained ability flags, and saved in ObjectRecall.
	/*3f4,4*/	undefined4 field_3f4; // (set to zero with tool equipped and never read?)
	/*3f8,4*/	bool32 bool_3f8;
	/*3fc,4*/	real32 hurtSoundTimer; // Timer resets after reaching (hurtSoundDuration x 2)
	/*400,4*/	real32 hurtSoundDuration;
	/*404,4*/	LegoObject_UpgradeType upgradingType; // New upgrade type added as mask to vehicle level when upgrade is finished.
	/*408,4*/	LegoObject* nextFree; // (for listSet)
	/*40c*/
};
assert_sizeof(LegoObject, 0x40c);

struct LegoObject_Globs // [LegoRR/LegoObject.c|struct:0xc644|tags:GLOBS]
{
	/*0000,80*/	LegoObject* listSet[32];
	/*0080,4*/	LegoObject* freeList;
	/*0084,4b0*/	SFX_ID objectTtSFX[20][15]; // [objType:20][objIndex:15] (cfg: ObjTtSFXs)
	/*0534,13c*/	char* activityName[79]; // [activityType:79]
	/*0670,4*/	void* UnkSurfaceGrid_1_TABLE;
	/*0674,4*/	void* UnkSurfaceGrid_2_TABLE;
	/*0678,4*/	uint32 UnkSurfaceGrid_COUNT;
	/*067c,4*/	real32 radarSurveyCycleTimer; // Timer for how often survey scans update.
	/*0680,4*/	uint32 listCount;
	/*0684,4*/	LegoObject_GlobFlags flags;
	/*0688,2c*/	uint32 toolNullIndex[11]; // [toolType:11]
	/*06b4,4b00*/	uint32 objectTotalLevels[20][15][16]; // [objType:20][objIndex:15][objLevel:16]
	/*51b4,4b00*/	uint32 objectPrevLevels[20][15][16]; // [objType:20][objIndex:15][objLevel:16]
	/*9cb4,4*/	uint32 NERPs_TrainFlags;
	/*9cb8,4*/	LegoObject* minifigureObj_9cb8;
	/*9cbc,a0*/	Point2I slugHoleBlocks[20];
	/*9d5c,50*/	Point2I rechargeSeamBlocks[10];
	/*9dac,4*/	uint32 slugHoleCount;
	/*9db0,4*/	uint32 rechargeSeamCount;
	/*9db4,2260*/	HiddenObject hiddenObjects[200];
	/*c014,4*/	uint32 hiddenObjectCount;
	/*c018,4*/	real32 dischargeBuildup; // When >= 1.0f, consume one crystal.
	/*c01c,18*/	SaveStruct_18 savestruct18_c01c;
	/*c034,400*/	LegoObject* cycleUnits[256];
	/*c434,4*/	uint32 cycleUnitCount;
	/*c438,4*/	uint32 cycleBuildingCount;
	/*c43c,190*/	LegoObject* liveObjArray100_c43c[100]; // Used for water docking vehicles?
	/*c5cc,4*/	uint32 uintCount_c5cc; // Count for liveObjArray100_c43c
	/*c5d0,18*/	char* abilityName[6]; // [abilityType:6]
	/*c5e8,18*/	Image* ToolTipIcons_Abilities[6]; // [abilityType:6] (cfg: ToolTipIcons)
	/*c600,2c*/	Image* ToolTipIcons_Tools[11]; // [toolType:11] (cfg: ToolTipIcons)
	/*c62c,4*/	Image* ToolTipIcon_Blank; // (cfg: ToolTipIcons::Blank)
	/*c630,4*/	Image* ToolTipIcon_Ore; // (cfg: ToolTipIcons::Ore)
	/*c634,4*/	uint32 BuildingsTeleported;
	/*c638,4*/	real32 s_sound3DUpdateTimer;
	/*c63c,4*/	undefined4 s_stepCounter_c63c; // (static, counter %4 for step SFX)
	/*c640,4*/	void** s_FlocksDestroy_c640; // (static, Struct 0x10, used in Flocks activities (QUICK_DESTROY??))
	/*c644*/
};
assert_sizeof(LegoObject_Globs, 0xc644);

struct LegoUpdate_Globs // [LegoRR/Lego.c|struct:0x14|tags:GLOBS] (miscellaneous static function variables used during game update loop)
{
	/*00,4*/	real32 renameInputTimer; // (ram: 12.5)
	/*04,4*/	real32 dripSFXTimer; // (ram: 75.0)
	/*08,4*/	real32 ambientSFXTimer; // (ram: 250.0)
	/*0c,4*/	real32 dbgRollOffFactorValue; // (ram: 1.0)
	/*10,4*/	real32 currentBaseLightLevel; // (ram: 0.7)
	/*14*/
};
assert_sizeof(LegoUpdate_Globs, 0x14);

struct LevelLink // [LegoRR/FrontEnd.c|struct:0x14]
{
	/*00,4*/	sint32 setIndex; // Index in LevelSet
	/*04,4*/	LevelLink** linkLevels;
	/*08,4*/	uint32 linkCount;
	/*0c,4*/	undefined4 field_c;
	/*10,4*/	bool32 visited; // True if reached in RunThroughRecurse callback.
	/*14*/
};
assert_sizeof(LevelLink, 0x14);

struct LevelSet // [LegoRR/FrontEnd.c|struct:0x14]
{
	/*00,4*/	sint32 count;
	/*04,4*/	char** idNames;
	/*08,4*/	char** langNames;
	/*0c,4*/	LevelLink** levels;
	/*10,4*/	bool32* visitedList; // True if this level has been loaded from level links (probably makes them require unlock)
	/*14*/
};
assert_sizeof(LevelSet, 0x14);

struct LightEffects_Globs // [LegoRR/LightEffects.c|struct:0xf4|tags:GLOBS] LightEffects module globals @004ebdd8
{
	/*00,4*/	Container* rootSpotlight; // [Cont+Move] init
	/*04,4*/	Container* rootLight; // [Move] init (Reference used when getting position of rootSpotlight)
	/*08,c*/	ColourRGBF initialRGB; // [Color] init
	/*14,c*/	ColourRGBF currentRGB; // [Color+Blink+Fade] init+update
	/*20,c*/	ColourRGBF blinkRGBMax; // [Blink] init (cfg: BlinkRGBMax)
	/*2c,4*/	real32 blinkWait; // [Blink] update. Time between end of blink and next blink.
	/*30,8*/	Range2F blinkWaitRange; // [Blink] init (cfg: RandomRangeForTimeBetweenBlinks, mult: 25.0)
	/*38,4*/	real32 blinkChange; // [Blink] update
	/*3c,4*/	real32 blinkChangeMax; // [Blink] init (cfg: MaxChangeAllowed, div: 255.0)
	/*40,c*/	ColourRGBF fadeDestRGB; // [Fade] update
	/*4c,c*/	ColourRGBF fadeRGBMin; // [Fade] init (cfg: FadeRGBMin)
	/*58,c*/	ColourRGBF fadeRGBMax; // [Fade] init (cfg: FadeRGBMax)
	/*64,4*/	real32 fadeWait; // [Fade] update. Time between end of fade and next fade.
	/*68,8*/	Range2F fadeWaitRange; // [Fade] init (cfg: RandomRangeForTimeBetweenFades, mult: 25.0)
	/*70,c*/	ColourRGBF fadeSpeedRGB; // [Fade] update
	/*7c,8*/	Range2F fadeSpeedRange; // [Fade] init (cfg: RandomRangeForFadeTimeFade, mult: 25.0)
	/*84,4*/	real32 fadeHold; // [Fade] update. Time between peak of fade before reversing.
	/*88,8*/	Range2F fadeHoldRange; // [Fade] init (cfg: RandomRangeForHoldTimeOfFade, mult: 25.0)
	/*90,c*/	ColourRGBF fadePosRGB; // [Fade] update
	/*9c,c*/	Vector3F movePosition; // [Move] init+update (3D position of rootSpotlight)
	/*a8,c*/	Vector3F moveLimit; // [Move] init (cfg: MoveLimit)
	/*b4,4*/	real32 moveWait; // [Move] update. Time between end of move and next move.
	/*b8,8*/	Range2F moveWaitRange; // [Move] init (cfg: RandomRangeForTimeBetweenMoves, mult: 25.0)
	/*c0,4*/	real32 moveSpeed; // [Move] update
	/*c4,8*/	Range2F moveSpeedRange; // [Move] init (cfg: RandomRangeForSpeedOfMove, mult: 25.0)
	/*cc,c*/	Vector3F moveVector; // [Move] update
	/*d8,4*/	real32 moveDist; // [Move] update
	/*dc,8*/	Range2F moveDistRange; // [Move] init (cfg: RandomRangeForDistOfMove)
	/*e4,c*/	undefined1 reserved1[12]; // possibly an unused Vector3F/ColourRGBF
	/*f0,4*/	LightEffects_GlobFlags flags; // [all] init+update
	/*f4*/
};
assert_sizeof(LightEffects_Globs, 0xf4);

struct LiveObjectInfo // [LegoRR/search.c|struct:0x1c] This is some search info, that needs to be fixed up. Lot's of assumptions were made when creating this.
{
	/*00,4*/	LegoObject* liveObj;
	/*04,4*/	bool32 intbool_4;
	/*08,8*/	Point2F point_8;
	/*10,c*/	Vector3F vector_10;
	/*1c*/
};
assert_sizeof(LiveObjectInfo, 0x1c);

struct Loader_Globs // [LegoRR/Loader.c|struct:0x290|tags:GLOBS]
{
	/*000,4*/	Image* LoadScreen;
	/*004,4*/	Font* font;
	/*008,258*/	LoaderSection sectionList[50];
	/*260,4*/	LoaderSection* current; // current section being loaded
	/*264,4*/	Image* ShutdownScreen;
	/*268,4*/	Image* ProgressBar;
	/*26c,10*/	Area2F ProgressWindow;
	/*27c,4*/	Direction ProgressDirection; // expand direction of progress bar: U, R, D, L
	/*280,4*/	char* LoadingText;
	/*284,4*/	uint32 LoadingWidth; // measured width of font with LoadingText
	/*288,4*/	real32 progressLast; // percentage of filesize for section (stores percent of last render)
	/*28c,4*/	Loader_GlobFlags flags; // (1 = show loading bar)
	/*290*/
};
assert_sizeof(Loader_Globs, 0x290);

struct LoaderSection // [LegoRR/Loader.c|struct:0xc]
{
	/*0,4*/	char* name; // Name of the section files are being loaded from
	/*4,4*/	uint32 currentSize; // Current total size of files loaded for this section
	/*8,4*/	uint32 totalSize; // Predefined total "expected" size for files to load from this section
	/*c*/
};
assert_sizeof(LoaderSection, 0xc);

struct LWPOLY // [Gods98/Lwt.c|struct:0xc]
{
	/*0,4*/	uint32 plyCount;
	/*4,4*/	uint32 plySurface;
	/*8,4*/	uint16* plyData;
	/*c*/
};
assert_sizeof(LWPOLY, 0xc);

#pragma pack(push, 1)
struct LWRGB // [Gods98/Lwt.c|struct:0x4|pack:1] (an alias for ColourRGBAPacked)
{
	/*0,1*/	uint8 colRed;
	/*1,1*/	uint8 colGreen;
	/*2,1*/	uint8 colBlue;
	/*3,1*/	uint8 colAlpha;
	/*4*/
};
assert_sizeof(LWRGB, 0x4);
#pragma pack(pop)

struct Lws_Globs // [Gods98/Lws.c|struct:0x402c|tags:GLOBS]
{
	/*0000,1f40*/	Lws_MeshPath meshPathList[1000]; // For full path to files...
	/*1f40,1f40*/	Lws_MeshPath meshPathListShared[1000]; // For shared files...
	/*3e80,4*/	char* sharedDir;
	/*3e84,4*/	uint32 meshPathCount;
	/*3e88,4*/	uint32 meshPathCountShared;
	/*3e8c,190*/	real32 staticDissolveLevel[100];
	/*401c,4*/	uint32 staticDissolveCount;
	/*4020,4*/	LwsFindSFXIDFunc FindSFXIDFunc;
	/*4024,4*/	LwsSoundEnabledFunc SoundEnabledFunc;
	/*4028,4*/	LwsPlaySample3DFunc PlaySample3DFunc;
	/*402c*/
};
assert_sizeof(Lws_Globs, 0x402c);

struct Lws_Info // [Gods98/Lws.c|struct:0x38]
{
	/*00,2*/	uint16 firstFrame;
	/*02,2*/	uint16 lastFrame;
	/*04,4*/	real32 fps;
	/*08,4*/	char* filePath;
	/*0c,4*/	real32 lastTime;
	/*10,4*/	real32 time;
	/*14,4*/	IDirect3DRMFrame3* frameList;
	/*18,4*/	Lws_SoundTrigger* triggerList;
	/*1c,4*/	Lws_Node* masterNode;
	/*20,4*/	Lws_Node* nodeList;
	/*24,2*/	uint16 nodeCount;
	/*26,2*/	uint16 nodeListSize;
	/*28,2*/	uint16 triggerCount;
	/*2a,2*/	uint16 padding1;
	/*2c,4*/	Lws_Info* clonedFrom;
	/*30,4*/	uint32 referenceCount;
	/*34,1*/	uint8 flags;
	/*35,3*/	uint8 padding2[3];
	/*38*/
};
assert_sizeof(Lws_Info, 0x38);

struct Lws_KeyInfo // [Gods98/Lws.c|struct:0x28]
{
	/*00,c*/	Vector3F position;
	/*0c,c*/	Vector3F hpb;
	/*18,c*/	Vector3F scale;
	/*24,2*/	uint16 frame;
	/*26,2*/	uint16 padding1;
	/*28*/
};
assert_sizeof(Lws_KeyInfo, 0x28);

struct Lws_MeshPath // [Gods98/Lws.c|struct:0x8]
{
	/*0,4*/	char* path;
	/*4,4*/	Mesh* mesh;
	/*8*/
};
assert_sizeof(Lws_MeshPath, 0x8);

struct Lws_Node // [Gods98/Lws.c|struct:0x34]
{
	/*00,4*/	char* name;
	/*04,2*/	uint16 reference;
	/*06,2*/	uint16 frameIndex;
	/*08,1*/	uint8 triggerIndex;
	/*09,3*/	uint8 padding1[3];
	/*0c,c*/	Vector3F pivotVector;
	/*18,4*/	Lws_KeyInfo* keyList;
	/*1c,4*/	real32* dissolveLevel;
	/*20,4*/	uint16* dissolveFrame;
	/*24,2*/	uint16 keyCount;
	/*26,2*/	uint16 dissolveCount;
	/*28,1*/	uint8 flags;
	/*29,3*/	uint8 padding2[3];
	/*2c,4*/	Lws_Node* childList;
	/*30,4*/	Lws_Node* next;
	/*34*/
};
assert_sizeof(Lws_Node, 0x34);

struct Lws_SoundTrigger // [Gods98/Lws.c|struct:0xd0]
{
	/*00,4*/	uint32 sfxID;
	/*04,32*/	uint16 frameStartList[25];
	/*36,32*/	uint16 frameEndList[25];
	/*68,64*/	uint32 loopUID[25];
	/*cc,2*/	uint16 count;
	/*ce,2*/	uint16 padding1;
	/*d0*/
};
assert_sizeof(Lws_SoundTrigger, 0xd0);

struct LWSIZE // [Gods98/Lwt.c|struct:0xc]
{
	/*0,4*/	uint32 lwVertCount;
	/*4,4*/	uint32 lwPolyCount;
	/*8,4*/	uint32 lwSurfaceCount;
	/*c*/
};
assert_sizeof(LWSIZE, 0xc);

struct LWSURFACE // [Gods98/Lwt.c|struct:0x54]
{
	/*00,4*/	char* srfName;
	/*04,4*/	LWSURFACE* srfNextSurf;
	/*08,4*/	char* srfPath;
	/*0c,4*/	LWRGB srfCol;
	/*10,4*/	char srfTCLR[4];
	/*14,4*/	LWTEXFLAGS srfTexFlags;
	/*18,4*/	LWSRFFLAGS srfFlags;
	/*1c,4*/	LWTEXMAPTYPE srfTexType;
	/*20,4*/	uint32 srfTexWrap;
	/*24,c*/	TEXDATA srfTexSize;
	/*30,c*/	TEXDATA srfTexCentre;
	/*3c,4*/	real32 srfLuminous;
	/*40,4*/	real32 srfTransparent;
	/*44,4*/	real32 srfDiffuse;
	/*48,4*/	real32 srfReflect;
	/*4c,4*/	real32 srfSpecular;
	/*50,4*/	real32 srfSpecPower;
	/*54*/
};
assert_sizeof(LWSURFACE, 0x54);

struct LWSURFLIST // [Gods98/Lwt.c|struct:0x8]
{
	/*0,4*/	uint32 srflCount;
	/*4,4*/	char** srflName;
	/*8*/
};
assert_sizeof(LWSURFLIST, 0x8);

struct Main_Globs // [Gods98/Main.c|struct:0x898|tags:GLOBS]
{
	/*000,4*/	HWND hWnd;
	/*004,4*/	HINSTANCE hInst;
	/*008,4*/	bool32 active;
	/*00c,4*/	bool32 exit;
	/*010,4*/	char* className;
	/*014,100*/	char programName[256];
	/*114,4*/	IDirect3DRM3* lpD3DRM;
	/*118,4*/	IDirect3DRMDevice3* device;
	/*11c,4*/	IDirect3DDevice3* imDevice;
	/*120,4*/	D3DRMSceneFogMethod fogMethod;
	/*124,4*/	uint32 appWidth;
	/*128,4*/	uint32 appHeight;
	/*12c,c*/	Main_State currState;
	/*138,4*/	bool32 stateSet;
	/*13c,4*/	real32 fixedFrameTiming;
	/*140,640*/	Main_StateChangeData renderStateData[200];
	/*780,4*/	uint32 style;
	/*784,4*/	MainFlags flags;
	/*788,4*/	ProgrammerMode programmerLevel;
	/*78c,80*/	char startLevel[128];
	/*80c,80*/	char languageName[128];
	/*88c,4*/	MainCLFlags clFlags;
	/*890,4*/	HACCEL accels;
	/*894,4*/	MainWindowCallback windowCallback;
	/*898*/
};
assert_sizeof(Main_Globs, 0x898);

struct Main_State // [Gods98/Main.c|struct:0xc] (unrelated to Main_StateChangeData)
{
	/*0,4*/	MainStateInitialise Initialise;
	/*4,4*/	MainStateMainLoop MainLoop;
	/*8,4*/	MainStateShutdown Shutdown;
	/*c*/
};
assert_sizeof(Main_State, 0xc);

struct Main_StateChangeData // [Gods98/Main.c|struct:0x8] The item's render state type is determined by the index in its table
{
	/*0,4*/	uint32 origValue; // not restricted to just uint value types, pointers, floats, signed ints, etc.
	/*4,4*/	bool32 changed;
	/*8*/
};
assert_sizeof(Main_StateChangeData, 0x8);

struct Map3D // [LegoRR/Map3D.c|struct:0x73d4]
{
	/*0000,4*/	uint32 blockWidth; // gridWidth - 1
	/*0004,4*/	uint32 blockHeight; // gridHeight - 1
	/*0008,4*/	uint32 gridWidth; // full map width
	/*000c,4*/	uint32 gridHeight; // full map height
	/*0010,4*/	real32 blockSize; // (cfg: BlockSize)
	/*0014,4*/	real32 roughLevel; // (cfg: RoughLevel)
	/*0018,8*/	Size2F worldDimensions_fnegx; // (-width, +height) * BlockSize / 2.0f  (smallDimensions)
	/*0020,4*/	real32 float_20; // (some sort of maximum)
	/*0024,4*/	Container* mesh; // Mesh for Map3D_Blocks
	/*0028,4*/	Map3D_Block* blocks3D; // [*:dimensions]
	/*002c,4*/	Detail_TextureSet* textureSet;
	/*0030,4*/	IDirect3DRMMaterial2* material; // (UNUSED: And never released!!!)
	/*0034,4000*/	uint8 texsGrid[128][128]; // [MAP3D_MAXTEXTURES][MAP3D_MAXTEXTURES]
	/*4034,80*/	uint8 texsNum[128]; // [MAP3D_MAXTEXTURES]
	/*40b4,200*/	bool32 texsNoFade[128]; // [MAP3D_MAXTEXTURES] True for textures that cannot fade transition
	/*42b4,7d0*/	Coord2U visibleBlocksTable[500]; // (related to FP detail)
	/*4a84,4*/	uint32 visibleBlocksNum;
	/*4a88,2710*/	Coord2U uvBlocksTable[2500]; // Blocks that require UV updates (EMISSIVE or UVWOBBLES)
	/*7198,4*/	uint32 uvBlocksNum;
	/*719c,230*/	Map3D_TransitionBlock transBlocks[10]; // [BASEMAPTEXTURES??]
	/*73cc,4*/	Container* transMesh; // Mesh for Map3D_TransitionBlocks
	/*73d0,4*/	Map3DFlags flagsMap;
	/*73d4*/
};
assert_sizeof(Map3D, 0x73d4);

struct Map3D_Block // [LegoRR/Map3D.c|struct:0x28]
{
	/*00,c*/	Vector3F normalA; // Maths_PlaneNormal of vertex positions 0,1,3
	/*0c,c*/	Vector3F normalB; // Maths_PlaneNormal of vertex positions 1,2,3
	/*18,1*/	SurfaceTexture texture;
	/*19,1*/	Map3D_BlockFlags flags3D;
	/*1a,1*/	uint8 heightValue; // height block value taken from high.map file
	/*1b,1*/	undefined1 padding1;
	/*1c,8*/	Point2F uvCoord;
	/*24,1*/	uint8 highlight; // (WallHighlightType)
	/*25,3*/	undefined1 padding2[3];
	/*28*/
};
assert_sizeof(Map3D_Block, 0x28);

struct Map3D_TransitionBlock // [LegoRR/Map3D.c|struct:0x38]
{
	/*00,4*/	D3DRMGroupIndex groupID; // (init: -1, no group created yet)
	/*04,4*/	real32 timer; // count-up timer [0.05f-1.0f]
	/*08,8*/	Point2I blockPos;
	/*10,20*/	Point2F uvCoords[4];
	/*30,4*/	undefined4 reserved1;
	/*34,1*/	Map3D_TransitionFlags flags; // (0x1 = visible, only flag)
	/*35,3*/	undefined1 padding1[3];
	/*38*/
};
assert_sizeof(Map3D_TransitionBlock, 0x38);

#pragma pack(push, 2)
struct MapFileInfo // [LegoRR/dummy.c|struct:0x12|pack:2]
{
	/*00,4*/	char Signature[4]; // "MAP "
	/*04,4*/	uint32 fileSize;
	/*08,8*/	Size2I dimensions;
	/*10,2*/	uint16 blocks[1];
	/*12*/
};
assert_sizeof(MapFileInfo, 0x12);
#pragma pack(pop)

struct Matrix4F // [common.c|struct:0x40]
{
	/*00,40*/	real32 values[4][4];
	/*40*/
};
assert_sizeof(Matrix4F, 0x40);

struct Mem_Globs // [Gods98/Memory.c|struct:0x3e84|tags:GLOBS]
{
	/*0000,3e80*/	Mem_Handle handleList[2000];
	/*3e80,4*/	uint32 flags; // (unused)
	/*3e84*/
};
assert_sizeof(Mem_Globs, 0x3e84);

struct Mem_Handle // [Gods98/Memory.c|struct:0x8]
{
	/*0,4*/	void* addr;
	/*4,4*/	Mem_HandleFlags flags; // 1 = isUsed
	/*8*/
};
assert_sizeof(Mem_Handle, 0x8);

struct Menu // [LegoRR/FrontEnd.c|struct:0xa0] A singular menu screen contained within a MenuSet structure.
{
	/*00,4*/	char* title; // (cfg: Menu::Title)
	/*04,4*/	char* fullName; // (cfg: Menu::FullName)
	/*08,4*/	uint32 titleLength; // (init: strlen(title))
	/*0c,4*/	Font* menuFont; // (cfg: Menu::MenuFont)
	/*10,4*/	Image* menuImage; // (cfg: Menu::MenuImage)
	/*14,4*/	Image* menuImageDark; // (cfg: Menu::MenuImageDark)
	/*18,4*/	MenuItem** items; // (cfg: Menu::Item1, Item2...)
	/*1c,4*/	sint32 itemCount; // (cfg: Menu::ItemCount) Number of used slots in items
	/*20,4*/	sint32 itemCapacity; // Total number of slots allocated in items
	/*24,4*/	sint32 itemFocus; // Index of item with keyboard focus
	/*28,4*/	bool32 closed; // Signals the menu(screen?) has been closed?
	/*2c,8*/	Point2I position; // (cfg: Menu::Position)
	/*34,4*/	MenuFlags flags; // flags [0x1, 0x2, ...]
	/*38,8*/	Point2F currPosition;
	/*40,4*/	MenuOverlay* overlays; // (cfg: Menu::Overlay1, Overlay2...)
	/*44,4*/	bool32 autoCenter; // (cfg: Menu::AutoCenter)
	/*48,4*/	bool32 displayTitle; // (cfg: Menu::DisplayTitle)
	/*4c,4*/	bool32 anchored; // (cfg: Menu::Anchored)
	/*50,8*/	Point2I anchoredPosition; // (cfg: Menu::Anchored)
	/*58,4*/	sint32 centerX;
	/*5c,40*/	char name[64]; // Name of menu in Lego.cfg
	/*9c,4*/	BoolTri playRandom; // (cfg: Menu::PlayRandom)
	/*a0*/
};
assert_sizeof(Menu, 0xa0);

struct MenuButton // [LegoRR/FrontEnd.c|struct:0x1c]
{
	/*00,10*/	Area2F window;
	/*10,4*/	Image* HiImage;
	/*14,4*/	Image* LoImage;
	/*18,4*/	char* Text;
	/*1c*/
};
assert_sizeof(MenuButton, 0x1c);

struct MenuItem // [LegoRR/FrontEnd.c|struct:0x3c]
{
	/*00,4*/	char* banner; // (cfg: type:[3|5]) Label text
	/*04,4*/	uint32 length;
	/*08,4*/	Font* fontHi; // (cfg: Menu::HiFont)
	/*0c,4*/	Font* fontLo; // (cfg: Menu::LoFont)
	/*10,4*/	MenuItem_Data_union itemData; // (cfg: type:[0,*])
	/*14,4*/	MenuItem_Type itemType; // (cfg: type:[0])
	/*18,4*/	sint32 x1; // (cfg: type:[1])
	/*1c,4*/	sint32 y1; // (cfg: type:[2])
	/*20,4*/	sint32 centerOffLo;
	/*24,4*/	sint32 centerOffHi;
	/*28,4*/	bool32 isImageItem; // Only true if imageHi is loaded (should be renamed)
	/*2c,4*/	Image* imageLo;
	/*30,4*/	Image* imageHi;
	/*34,4*/	ToolTip_Type toolTipType;
	/*38,4*/	bool32 notInTuto; // (string value is unchecked, but "NotInTuto" is the only seen usage)
	/*3c*/
};
assert_sizeof(MenuItem, 0x3c);

struct MenuItem_CycleData // [LegoRR/FrontEnd.c|struct:0x1c]
{
	/*00,4*/	char** nameList; // (cfg: Cycle:[7...])
	/*04,4*/	uint32 cycleCount; // (cfg: Cycle:[6])
	/*08,4*/	sint32 nameCount; // (cfg: Cycle:[7...])
	/*0c,4*/	sint32* valuePtr;
	/*10,4*/	sint32 x2; // (cfg: Cycle:[3])
	/*14,4*/	sint32 y2; // (cfg: Cycle:[4])
	/*18,4*/	MenuItem_CycleCallback callback;
	/*1c*/
};
assert_sizeof(MenuItem_CycleData, 0x1c);

struct MenuItem_RealSliderData // [LegoRR/FrontEnd.c|struct:0x1c]
{
	/*00,4*/	real32* valuePtr;
	/*04,4*/	real32 valueMin; // (cfg: RealSlider:[6])
	/*08,4*/	real32 valueMax; // (cfg: RealSlider:[7])
	/*0c,4*/	real32 valueStep; // (cfg: RealSlider:[8])
	/*10,4*/	sint32 x2; // (cfg: RealSlider:[3])
	/*14,4*/	sint32 y2; // (cfg: RealSlider:[4])
	/*18,4*/	MenuItem_RealSliderCallback callback;
	/*1c*/
};
assert_sizeof(MenuItem_RealSliderData, 0x1c);

struct MenuItem_SelectData // [LegoRR/FrontEnd.c|struct:0x5c]
{
	/*00,4*/	MenuItem_SelectItem* selItemList;
	/*04,c*/	uint32* widths[3]; // (image Hi,Lo,Locked widths, 3 identical for font string width) see Menu_SelectImageType
	/*10,c*/	uint32* heights[3]; // (image Hi,Lo,Locked heights, 3 identical for font height) see Menu_SelectImageType
	/*1c,4*/	uint32 selItemCount;
	/*20,4*/	char* string1;
	/*24,4*/	char* string2;
	/*28,4*/	sint32* valuePtr;
	/*2c,4*/	sint32 x2;
	/*30,4*/	sint32 y2;
	/*34,4*/	sint32 selItemHeight;
	/*38,4*/	sint32 scrollCount; // Max number of select items visible in scroll area.
	/*3c,4*/	sint32 xString1;
	/*40,4*/	sint32 yString1;
	/*44,4*/	sint32 xString2;
	/*48,4*/	sint32 yString2;
	/*4c,4*/	sint32 scrollStart; // Index offset of visible scroll area.
	/*50,4*/	undefined4 field_50;
	/*54,4*/	MenuItem_SelectCallback callback;
	/*58,4*/	Menu* nextMenu; // Optional menu to transition to after making a selection.
	/*5c*/
};
assert_sizeof(MenuItem_SelectData, 0x5c);

struct MenuItem_SelectItem // [LegoRR/FrontEnd.c|struct:0x20]
{
	/*00,4*/	MenuItem_SelectItemFlags flags; // [0x1 = print name over image, 0x2, 0x4]
	/*04,4*/	char* banner;
	/*08,c*/	Image* images[3]; // (cfg: Level::MenuBMP[0,2,3]) see Menu_SelectImageType
	/*14,4*/	sint32 frontEndX; // (cfg: Level::FrontEndX)
	/*18,4*/	sint32 frontEndY; // (cfg: Level::FrontEndY)
	/*1c,4*/	bool32 frontEndOpen; // (cfg: Level::FrontEndOpen)
	/*20*/
};
assert_sizeof(MenuItem_SelectItem, 0x20);

struct MenuItem_SliderData // [LegoRR/FrontEnd.c|struct:0x38]
{
	/*00,4*/	sint32* valuePtr;
	/*04,4*/	sint32 valueMin; // (cfg: Slider:[6])
	/*08,4*/	sint32 valueMax; // (cfg: Slider:[7])
	/*0c,4*/	sint32 x2; // (cfg: Slider:[3])
	/*10,4*/	sint32 y2; // (cfg: Slider:[4])
	/*14,4*/	MenuItem_SliderCallback callback;
	/*18,4*/	Image* imageBarOff; // (cfg: Slider:[8] "OffBar")
	/*1c,4*/	Image* imageBarOn; // (cfg: Slider:[9] "OnBar")
	/*20,4*/	Image* imageCapLeft; // (cfg: Slider:[10] "Leftcap")
	/*24,4*/	Image* imageCapRight; // (cfg: Slider:[11] "Rightcap")
	/*28,4*/	Image* imagePlusLo; // (cfg: Slider:[12] "Plus")
	/*2c,4*/	Image* imageMinusLo; // (cfg: Slider:[13] "Minus")
	/*30,4*/	Image* imagePlusHi; // (cfg: Slider:[14] "PlusHi")
	/*34,4*/	Image* imageMinusHi; // (cfg: Slider:[15] "MinusHi")
	/*38*/
};
assert_sizeof(MenuItem_SliderData, 0x38);

struct MenuItem_TextInputData // [LegoRR/FrontEnd.c|struct:0x18]
{
	/*00,4*/	char* valuePtr;
	/*04,4*/	sint32 length;
	/*08,4*/	sint32 caretPos; // Character index of cursor.
	/*0c,4*/	sint32 maxLength; // Maximum length of value buffer.
	/*10,4*/	sint32 x2;
	/*14,4*/	sint32 y2;
	/*18*/
};
assert_sizeof(MenuItem_TextInputData, 0x18);

struct MenuItem_TriggerData // [LegoRR/FrontEnd.c|struct:0xc]
{
	/*0,4*/	sint32* valuePtr;
	/*4,4*/	bool32 end; // (cfg: Trigger:[4]) End/close the current MenuSet
	/*8,4*/	MenuItem_TriggerCallback callback;
	/*c*/
};
assert_sizeof(MenuItem_TriggerData, 0xc);

struct MenuItemCallbackPair // [LegoRR/dummy.c|struct:0x8]
{
	/*0,4*/	void* value;
	/*4,4*/	void* callback;
	/*8*/
};
assert_sizeof(MenuItemCallbackPair, 0x8);

struct MenuOverlay // [LegoRR/FrontEnd.c|struct:0x20]
{
	/*00,4*/	char* filename;
	/*04,4*/	MenuOverlay_Type overlayType; // (.flh, .bmp, .avi, .lws)
	/*08,4*/	undefined4 field_8;
	/*0c,8*/	Point2I position;
	/*14,4*/	SFX_ID sfxType;
	/*18,4*/	MenuOverlay* previous;
	/*1c,4*/	undefined4 field_1c;
	/*20*/
};
assert_sizeof(MenuOverlay, 0x20);

struct MenuSet // [LegoRR/FrontEnd.c|struct:0x8] A collection of menus that may interact with one another (i.e. MainMenuFull, PausedMenu)
{
	/*0,4*/	Menu** menus; // (cfg: MenuSet::Menu1, Menu2...)
	/*4,4*/	uint32 menuCount; // (cfg: MenuSet::MenuCount)
	/*8*/
};
assert_sizeof(MenuSet, 0x8);

struct MenuTextWindow // [LegoRR/FrontEnd.c|struct:0x728] Menu/FrontEnd text structure, see CFG blocks: SaveText, LevelText
{
	/*000,4*/	TextWindow* textWindow;
	/*004,4*/	Image* PanelImage;
	/*008,10*/	Area2F WindowArea;
	/*018,10*/	Area2F PanelArea;
	/*028,100*/	char LoadText[256];
	/*128,100*/	char SaveText[256];
	/*228,100*/	char SlotText[256]; // format: %d (save number)
	/*328,100*/	char LoadSelText[256]; // format: %d (save number)
	/*428,100*/	char SaveSelText[256]; // format: %d (save number)
	/*528,100*/	char LevelText[256];
	/*628,100*/	char TutorialText[256];
	/*728*/
};
assert_sizeof(MenuTextWindow, 0x728);

struct Mesh // [Gods98/Mesh.c|struct:0x34|tags:LISTSET]
{
	/*00,4*/	uint32 groupCount; // seems to be a count
	/*04,4*/	uint32 listSize;
	/*08,4*/	Mesh_Group* groupList; // table ptr? -> 0x10 (struct: 0x70)
	/*0c,4*/	IDirect3DRMUserVisual* uv;
	/*10,c*/	Mesh_RenderDesc renderDesc;
	/*1c,4*/	Mesh_LightWave_Surface* lightWaveSurf;
	/*20,4*/	uint32 numOfRefs;
	/*24,4*/	Mesh* clonedFrom;
	/*28,4*/	IDirect3DRMFrame3* frameCreatedOn;
	/*2c,4*/	uint32 flags;
	/*30,4*/	Mesh* nextFree;
	/*34*/
};
assert_sizeof(Mesh, 0x34);

struct Mesh_Globs // [Gods98/Mesh.c|struct:0xc21c|tags:GLOBS]
{
	/*0000,4*/	Mesh* postRenderList;
	/*0004,4*/	Mesh_PostRenderInfo* postRenderMeshList;
	/*0008,190*/	Main_StateChangeData stateData[50];
	/*0198,4*/	char* sharedTextureDir;
	/*019c,6000*/	Mesh_TextureReference textureList[2048];
	/*619c,6000*/	Mesh_TextureReference textureListShared[2048];
	/*c19c,4*/	uint32 textureCount;
	/*c1a0,4*/	uint32 textureCountShared;
	/*c1a4,4*/	DWORD oldTextureRM;
	/*c1a8,4*/	DWORD oldMatIM;
	/*c1ac,4*/	IDirect3DTexture2* oldTextureIM;
	/*c1b0,4*/	DWORD currTextureRM;
	/*c1b4,4*/	DWORD currMatIM;
	/*c1b8,4*/	IDirect3DTexture2* currTextureIM;
	/*c1bc,4*/	DWORD matHandle;
	/*c1c0,4*/	IDirect3DMaterial3* imMat;
	/*c1c4,50*/	Mesh* listSet[20];
	/*c214,4*/	Mesh* freeList;
	/*c218,4*/	uint32 listCount; // (yeah, no uint flags)
	/*c21c*/
};
assert_sizeof(Mesh_Globs, 0xc21c);

struct Mesh_Group // [Gods98/Mesh.c|struct:0x70]
{
	/*00,4*/	uint32 faceDataSize;
	/*04,4*/	uint32 vertexCount;
	/*08,4*/	uint16* faceData;
	/*0c,4*/	Mesh_Vertex* vertices;
	/*10,50*/	D3DMaterial material;
	/*60,4*/	IDirect3DTexture2* imText;
	/*64,4*/	uint32 renderFlags;
	/*68,4*/	Mesh_LightWave_Surface* lightWaveSurfaceInfo;
	/*6c,4*/	uint32 flags;
	/*70*/
};
assert_sizeof(Mesh_Group, 0x70);

struct Mesh_LightWave_Surface // [Gods98/Mesh.c|struct:0x3c]
{
	/*00,4*/	Container_Texture** textureSeq;
	/*04,4*/	Container_Texture* texture;
	/*08,4*/	uint32 numInTexSeq;
	/*0c,10*/	ColourRGBAF colour;
	/*1c,4*/	real32 diffuse;
	/*20,4*/	real32 emissive;
	/*24,4*/	real32 specular;
	/*28,4*/	real32 power;
	/*2c,4*/	real32 transparency;
	/*30,4*/	uint32 flags;
	/*34,4*/	uint32 texFlags;
	/*38,4*/	sint32 texSeqOffset;
	/*3c*/
};
assert_sizeof(Mesh_LightWave_Surface, 0x3c);

struct Mesh_PostRenderInfo // [Gods98/Mesh.c|struct:0x48]
{
	/*00,4*/	Mesh* mesh;
	/*04,40*/	Matrix4F matWorld;
	/*44,4*/	Mesh_PostRenderInfo* next;
	/*48*/
};
assert_sizeof(Mesh_PostRenderInfo, 0x48);

struct Mesh_RenderDesc // [Gods98/Mesh.c|struct:0xc]
{
	/*0,4*/	MeshRenderCallback renderCallback;
	/*4,4*/	void* renderCallbackData;
	/*8,4*/	uint32 renderFlags; // determines a lot of render states
	/*c*/
};
assert_sizeof(Mesh_RenderDesc, 0xc);

struct Mesh_TextureReference // [Gods98/Mesh.c|struct:0xc]
{
	/*0,4*/	IDirectDrawSurface4* surface;
	/*4,4*/	char* path;
	/*8,4*/	bool32 trans;
	/*c*/
};
assert_sizeof(Mesh_TextureReference, 0xc);

struct Mesh_Vertex // [Gods98/Mesh.c|struct:0x20] Untransformed/unlit vertices
{
	/*00,c*/	Vector3F position; // Homogeneous coordinates
	/*0c,c*/	Vector3F normal; // Normal
	/*18,4*/	real32 tu; // Texture coordinates
	/*1c,4*/	real32 tv; // Texture coordinates
	/*20*/
};
assert_sizeof(Mesh_Vertex, 0x20);

struct MeshLOD // [LegoRR/MeshPoly.c|struct:0x18]
{
	/*00,4*/	Container* contMeshOrigin; // (LWO|MESH, true)
	/*04,4*/	Container* contMeshTarget;
	/*08,4*/	char* partName; // name of LoadObject file.lwo
	/*0c,4*/	uint32 setID; // MeshLOD's may contain multiple sets of the same parts, this specifies which set its from.
	/*10,4*/	MeshLODFlags flags; // (1 = dont free partName/cont_0,  2 = unk dtor behavior)
	/*14,4*/	MeshLOD* next;
	/*18*/
};
assert_sizeof(MeshLOD, 0x18);

struct Message_Event // [LegoRR/Message.c|struct:0x14]
{
	/*00,4*/	Message_Type type;
	/*04,4*/	LegoObject* argumentObj; // (this argument is only used for objects)
	/*08,4*/	undefined4 argument2; // (this can be many types, and depends on the message)
	/*0c,8*/	Point2I blockPos;
	/*14*/
};
assert_sizeof(Message_Event, 0x14);

struct Message_Globs // [LegoRR/Message.c|struct:0x14380|tags:GLOBS]
{
	/*00000,14000*/	Message_Event eventLists[2][2048];
	/*14000,8*/	uint32 eventCounts[2];
	/*14008,4*/	bool32 eventAB; // Whether to use index 0 or 1 of eventLists, eventCounts.
	/*1400c,190*/	LegoObject* selectedUnitList[100];
	/*1419c,a*/	Keys8 hotKeyKeyList[10];
	/*141a6,2*/	undefined2 padding1;
	/*141a8,c8*/	Message_Event hotKeyEventList[10];
	/*14270,104*/	char* messageName[65];
	/*14374,4*/	undefined4 reserved1;
	/*14378,4*/	uint32 selectedUnitCount;
	/*1437c,4*/	uint32 hotKeyCount;
	/*14380*/
};
assert_sizeof(Message_Globs, 0x14380);

struct NERPMessageImage // [LegoRR/NERPs.c|struct:0x8]
{
	/*0,4*/	char* key;
	/*4,4*/	Image* image;
	/*8*/
};
assert_sizeof(NERPMessageImage, 0x8);

struct NERPMessageSound // [LegoRR/NERPs.c|struct:0x8]
{
	/*0,4*/	char* key;
	/*4,4*/	sint32 sound3DHandle;
	/*8*/
};
assert_sizeof(NERPMessageSound, 0x8);

struct NERPsFile_Globs // [LegoRR/NERPs.c|struct:0xb4|tags:GLOBS]
{
	/*00,4*/	bool32 camIsLockedOn;
	/*04,4*/	uint32 camLockOnRecord; // Record object pointer (0-indexed).
	/*08,8*/	Point2F camLockOnPos; // Assigned based on the lock-on object, but never used.
	/*10,4*/	LegoObject* camLockOnObject;
	/*14,4*/	bool32 camIsZooming;
	/*18,4*/	real32 camZoomTotal; // Total amount to zoom specified by NERPs function.
	/*1c,4*/	real32 camZoomMoved; // Amount of the total that has been zoomed. (amount left == total - moved)
	/*20,4*/	bool32 camIsRotating;
	/*24,4*/	real32 camRotTotal; // Total amount to rotate specified by NERPs function.
	/*28,4*/	real32 camRotMoved; // Amount of the total that has been rotated. (amount left == total - moved)
	/*2c,4*/	NERPsInstruction* instructions; // (script fileData)
	/*30,4*/	uint32 scriptSize; // (script fileSize)
	/*34,2c*/	undefined4 reserved1[11];
	/*60,4*/	char* messageBuffer; // (message fileData)
	/*64,4*/	uint32 lineCount;
	/*68,4*/	char** lineList;
	/*6c,4*/	uint32 imageCount;
	/*70,4*/	NERPMessageImage* imageList; // :imageKey filePath
	/*74,4*/	uint32 soundCount;
	/*78,4*/	NERPMessageSound* soundList; // $soundKey filePath
	/*7c,24*/	uint32 lineIndexArray_7c[9];
	/*a0,4*/	uint32 uint_a0;
	/*a4,4*/	sint32 int_a4; // (signedness known due to constant comparison)
	/*a8,4*/	uint32 uint_a8;
	/*ac,4*/	sint32 RecordObjectPointer;
	/*b0,4*/	bool32 AdvisorTalkingMode;
	/*b4*/
};
assert_sizeof(NERPsFile_Globs, 0xb4);

struct NERPsFunctionSignature // [LegoRR/NERPs.c|struct:0xc]
{
	/*0,4*/	char* name;
	/*4,4*/	NERPsFunction function;
	/*8,4*/	NERPsFunctionArgs arguments;
	/*c*/
};
assert_sizeof(NERPsFunctionSignature, 0xc);

struct NERPsInstruction // [LegoRR/NERPs.c|struct:0x4]
{
	/*0,2*/	sint16 value;
	/*2,2*/	NERPsOpcode opcode;
	/*4*/
};
assert_sizeof(NERPsInstruction, 0x4);

struct NERPsRuntime_Globs // [LegoRR/NERPs.c|struct:0x68|tags:GLOBS]
{
	/*00,20*/	sint32 registers[8];
	/*20,4*/	bool32 messagePermit; // allows NERPs messages to display in the TextMessage panel. (see: NERPFunc__SetMessagePermit)
	/*24,4*/	undefined4 reserved1;
	/*28,4*/	TutorialFlags tutorialFlags; // (this is the last field in a structure starting at 0x00)
	/*2c,4*/	bool32 timerbool_2c; // used by UpdateTimers
	/*30,4*/	bool32 nextArrowDisabled; // (see: NERPFunc__SetMessage)
	/*34,4*/	real32 messageTimer; // (see: NERPFunc__GetMessageTimer)
	/*38,4*/	sint32 hiddenObjectsFound; // (see: NERPFunc__SetHiddenObjectsFound)
	/*3c,4*/	bool32 messageWait; // (see: NERPFunc__SetMessageWait)
	/*40,4*/	bool32 logFuncCalls; // (always 0)
	/*44,4*/	undefined4 reserved2;
	/*48,10*/	real32 timers[4];
	/*58,4*/	bool32 supressArrow; // (see: NERPFunc__SupressArrow)
	/*5c,4*/	bool32 allowCameraMovement; // (see: NERPFunc__AllowCameraMovement)
	/*60,4*/	real32 tutorialIconTimer;
	/*64,4*/	bool32 objectiveSwitch; // (see: NERPFunc__SetObjectiveSwitch)
	/*68*/
};
assert_sizeof(NERPsRuntime_Globs, 0x68);

struct Objective_Globs // [LegoRR/Objective.c|struct:0x28c|tags:GLOBS] Globals for objective messages (Chief briefing, etc).
{
	/*000,4*/	Objective_GlobFlags flags;
	/*004,4*/	File* file; // PTRFileStream_00500bc4
	/*008,80*/	char filename[128]; // CHAR_ARRAY_00500bc8
	/*088,10*/	char* messages[4]; // [Briefing,Completion,Failure,CrystalFailure] Strings containing text of entire status message (pages are separated with '\a').
	/*098,180*/	undefined reserved1[384]; // (possibly unused array of char[3][128])
	/*218,10*/	uint32 currentPages[4]; // (1-indexed) Current page number of the displayed status type. (g_Objective_StatusUnkCounts)
	/*228,10*/	uint32 currentPageStates[4]; // (1-indexed) State tracking for page to switch to (this is only used to check if the above field needs to trigger an update). (g_Objective_StatusUnkCounts2)
	/*238,10*/	uint32 pageCounts[4]; // Number of pages for the specific status. (g_Objective_StatusBellCounts)
	/*248,10*/	TextWindow* textWindows[4]; // Text windows for the specific status. (g_Objective_StatusTextWindows)
	/*258,c*/	TextWindow* pageTextWindows[3]; // PTRTextWindow_00500e18, PTRTextWindow_00500e1c, PTRTextWindow_00500e20
	/*264,4*/	TextWindow* beginTextWindow; // Unknown usage, only worked with when line "[BEGIN]" is found (PTRTextWindow_00500e24)
	/*268,4*/	undefined4 reserved2;
	/*26c,4*/	bool32 hasBeginText; // True when text has been assigned to beginTextWindow (BOOL_00500e2c)
	/*270,4*/	bool32 achieved; // True if the level was has ended successfully. (g_LevelIsComplete)
	/*274,4*/	bool32 objectiveSwitch; // (see: NERPFunc__SetObjectiveSwitch)
	/*278,4*/	char* soundName;
	/*27c,4*/	sint32 soundHandle; // (init: -1 when unused) INT_00500e3c
	/*280,4*/	real32 soundTimer; // (init: (playTime - 1.5f) * 25.0f) FLOAT_00500e40
	/*284,4*/	bool32 showing; // True when an objective is currently being shown or changed to(?)
	/*288,4*/	bool32 endTeleportEnabled; // (cfg: ! DisableEndTeleport, default: false (enabled))
	/*28c*/
};
assert_sizeof(Objective_Globs, 0x28c);

struct ObjectiveData // [LegoRR/???|struct:0x54]
{
	/*00,4*/	Image* panelImage; // (cfg: ObjectiveImage<W>x<H>[0])
	/*04,8*/	Point2F panelImagePosition; // (cfg: ObjectiveImage<W>x<H>[1,2])
	/*0c,4*/	Image* achievedImage; // (cfg: ObjectiveAcheivedImage<W>x<H>[0]) unused
	/*10,8*/	Point2F achievedImagePosition; // (cfg: ObjectiveAcheivedImage<W>x<H>[1,2]) unused
	/*18,4*/	Image* failedImage; // (cfg: ObjectiveFailedImage<W>x<H>[0]) unused
	/*1c,8*/	Point2F failedImagePosition; // (cfg: ObjectiveFailedImage<W>x<H>[1,2]) unused
	/*24,4*/	char* achievedVideoName; // (cfg: ObjectiveAcheivedAVI[0]) filename
	/*28,8*/	Point2F achievedVideoPosition; // (cfg: ObjectiveAcheivedAVI[1,2])
	/*30,4*/	bool32 noAchievedVideo; // True if cfg:ObjectiveAcheivedAVI was not parsed correctly (or does not eixst?)
	/*34,4*/	bool32 achievedVideoPlayed;
	/*38,4*/	uint32 crystals; // (cfg: CrystalObjective) number of crystals needed if non-zero
	/*3c,4*/	uint32 ore; // (cfg: OreObjective) number of ore needed if non-zero
	/*40,8*/	Point2I blockPos; // (cfg: BlockObjective)
	/*48,4*/	real32 timer; // (cfg: TimerObjective, mult: 25.0, flags, format: "time:HitTimeFailObjective")
	/*4c,4*/	LegoObject_Type constructionType; // (cfg: ConstructionObjective)
	/*50,4*/	sint32 constructionID; // (cfg: ConstructionObjective)
	/*54*/
};
assert_sizeof(ObjectiveData, 0x54);

struct ObjectRecall_Globs // [LegoRR/ObjectRecall.c|struct:0x18|tags:GLOBS]
{
	/*00,4*/	ObjectRecallEntry* recallList;
	/*04,4*/	uint32 recallUsed;
	/*08,4*/	uint32 recallCapacity;
	/*0c,4*/	ObjectRecallEntry* recallNewList;
	/*10,4*/	uint32 recallNewCount;
	/*14,4*/	bool32 loaded;
	/*18*/
};
assert_sizeof(ObjectRecall_Globs, 0x18);

struct ObjectRecallEntry // [LegoRR/ObjectRecall.c|struct:0x14] Object recall structure (for .osf file)
{
	/*00,4*/	LegoObject_AbilityFlags abilityFlags; // LiveFlags5
	/*04,4*/	uint32 level;
	/*08,c*/	char customName[12];
	/*14*/
};
assert_sizeof(ObjectRecallEntry, 0x14);

struct ObjectStats // [LegoRR/Stats.c|struct:0x150]
{
	/*000,1e*/	char unused_typeName[30];
	/*01e,2*/	undefined2 padding;
	/*020,4*/	real32 RouteSpeed; // (leveled)
	/*024,48*/	real32 DrillTimes[18]; // (leveled, table of surface type times)
	/*06c,4*/	real32 CollRadius; // (effect: flags1 | 0x80)
	/*070,4*/	real32 AlertRadius;
	/*074,4*/	real32 CollHeight;
	/*078,4*/	real32 PickSphere;
	/*07c,4*/	real32 TrackDist;
	/*080,4*/	real32 HealthDecayRate;
	/*084,4*/	real32 EnergyDecayRate;
	/*088,4*/	real32 RepairValue; // (leveled)
	/*08c,4*/	real32 RestPercent;
	/*090,4*/	real32 CarryMinHealth;
	/*094,4*/	real32 StampRadius;
	/*098,4*/	real32 AttackRadius;
	/*09c,4*/	real32 WakeRadius; // (default: 20.0)
	/*0a0,8*/	Size2F CollBox; // (requires: invalid/no CollRadius, effect: flag 0x100, CollRadius = min(w,h) * 0.5)
	/*0a8,4*/	sint32 BuildingBase; // (from: FUN_00408bb0, invalid: -1, either ptr or basenumber)
	/*0ac,4*/	sint32 SurveyRadius; // (leveled)
	/*0b0,4*/	sint32 CostOre;
	/*0b4,4*/	sint32 CostCrystal;
	/*0b8,4*/	sint32 CostRefinedOre;
	/*0bc,4*/	sint32 CrystalDrain; // (leveled)
	/*0c0,4*/	SFX_ID DrillSound; // (from: FUN_00464f30, invalid: 2 "SFX_Drill")
	/*0c4,4*/	SFX_ID DrillFadeSound; // (from: FUN_00464f30, invalid: 3 "SFX_DrillFade")
	/*0c8,4*/	SFX_ID EngineSound; // (from: FUN_00464f30, invalid: 0 "SFX_Bodge")
	/*0cc,4*/	sint32 NumOfToolsCanCarry; // (leveled)
	/*0d0,4*/	sint32 WaterEntrances;
	/*0d4,4*/	real32 RubbleCoef; // (default: 1.0)
	/*0d8,4*/	real32 PathCoef; // (default: 1.0)
	/*0dc,4*/	real32 OxygenCoef; // (negative consumes oxygen)
	/*0e0,4*/	sint32 Capacity;
	/*0e4,4*/	real32 AwarenessRange; // (default: 0.0)
	/*0e8,4*/	real32 PainThreshold; // (default: 0.0)
	/*0ec,4*/	sint32 MaxCarry; // (leveled)
	/*0f0,4*/	sint32 CarryStart; // (leveled)
	/*0f4,4*/	real32 UpgradeTime; // (leveled, mult: 25.0)
	/*0f8,4*/	real32 FunctionCoef; // (leveled)
	/*0fc,4*/	sint32 UpgradeCostOre; // Carry:Scan:Speed:Drill (requires all 4)
	/*100,4*/	sint32 UpgradeCostStuds; // Carry:Scan:Speed:Drill (requires all 4)
	/*104,4*/	real32 unused_viewAngle;
	/*108,4*/	real32 unused_viewDist;
	/*10c,4*/	real32 FreezerTime; // (default: 0.0)
	/*110,4*/	real32 FreezerDamage; // (default: 0.0)
	/*114,4*/	real32 PusherDist; // (default: 0.0)
	/*118,4*/	real32 PusherDamage; // (default: 0.0)
	/*11c,4*/	real32 LaserDamage; // (default: 0.0)
	/*120,4*/	real32 Flocks_Turn; // (default: 0.06)
	/*124,4*/	real32 Flocks_Speed; // (default: 2.0)
	/*128,4*/	real32 Flocks_Tightness; // (default: 2.0)
	/*12c,4*/	real32 Flocks_GoalUpdate; // (default: 2.0)
	/*130,4*/	real32 Flocks_Height; // (default: 30.0)
	/*134,4*/	real32 Flocks_Randomness; // (default: 2.0)
	/*138,4*/	real32 Flocks_AttackTime; // (default: 300.0)
	/*13c,4*/	sint32 Flocks_Size; // (default: 5)
	/*140,4*/	real32 RandomMoveTime; // (default: 200.0)
	/*144,4*/	StatsFlags1 flags1;
	/*148,4*/	StatsFlags2 flags2;
	/*14c,4*/	StatsFlags3 flags3;
	/*150*/
};
assert_sizeof(ObjectStats, 0x150);

struct ObjInfo_Globs // [LegoRR/ObjInfo.c|struct:0x78|tags:GLOBS]
{
	/*00,4*/	ObjInfo_GlobFlags flags;
	/*04,8*/	Point2F HealthBarPosition;
	/*0c,8*/	Size2F HealthBarWidthHeight;
	/*14,4*/	uint32 HealthBarBorderSize;
	/*18,c*/	real32 HealthBarBorderRGB_r[3]; // [normal, hi, lo]
	/*24,c*/	real32 HealthBarBorderRGB_g[3]; // [normal, hi, lo]
	/*30,c*/	real32 HealthBarBorderRGB_b[3]; // [normal, hi, lo]
	/*3c,c*/	ColourRGBF HealthBarRGB;
	/*48,c*/	ColourRGBF HealthBarBackgroundRGB;
	/*54,8*/	Point2F HungerPosition;
	/*5c,14*/	Image* HungerImages[5];
	/*70,8*/	Point2F BubblePosition;
	/*78*/
};
assert_sizeof(ObjInfo_Globs, 0x78);

struct Panel_Globs // [LegoRR/Panels.c|struct:0x7b8|tags:GLOBS]
{
	/*000,30*/	char* panelName[12];
	/*030,240*/	PanelData panelTable[12];
	/*270,480*/	char* panelButtonName[12][24];
	/*6f0,4*/	Panel_Type currentPanel;
	/*6f4,4*/	PanelButtonType currentButton;
	/*6f8,4*/	PanelTextWindow* infoTextWnd;
	/*6fc,4*/	PanelTextWindow* encyclopediaTextWnd;
	/*700,4*/	Image* crystalSmallImage; // Hard: "Interface\\RightPanel\\SmallCrystal.bmp"
	/*704,4*/	Image* crystalNoSmallImage; // Hard: "Interface\\RightPanel\\NoSmallCrystal.bmp"
	/*708,4*/	Image* crystalUsedImage; // Hard: "Interface\\RightPanel\\UsedCrystal.bmp"
	/*70c,4*/	uint32 crystalQuota;
	/*710,4*/	Image* airMeterJuiceImage; // Hard: "Interface\\AirMeter\\msgpanel_air_juice.bmp"
	/*714,4*/	Image* airMeterNoAirImage; // Hard: "Interface\\AirMeter\\msgpanel_noair.bmp"
	/*718,8*/	Point2F airMeterJuiceOffset; // Hard: (85, 6) Offset relative to top-left corner of MsgPanel
	/*720,4*/	uint32 airMeterJuiceLength; // Hard: 236
	/*724,8*/	Point2F airMeterNoAirOffset; // Hard: (21, 0) Offset relative to top-left corner of MsgPanel
	/*72c,4*/	bool32 airMeterOxygenLow; // Oxygen level is 10% or less.
	/*730,4*/	Image* cryOreSideBarImage; // Hard: "Interface\\RightPanel\\crystalsidebar_ore.bmp"
	/*734,8*/	Point2F cryOreSideBarOffset; // Hard: (615, 434)
	/*73c,4*/	uint32 cryOreMeterOffset; // Hard: 423
	/*740,4*/	real32 cryOreMeterValue;
	/*744,8*/	Point2I rotateCenter;
	/*74c,4*/	sint32 rotateRadius;
	/*750,8*/	Point2F rotateUpOffset;
	/*758,8*/	Point2F rotateDownOffset;
	/*760,8*/	Point2F rotateLeftOffset;
	/*768,8*/	Point2F rotateRightOffset;
	/*770,4*/	Image* rotateUpImage;
	/*774,4*/	Image* rotateDownImage;
	/*778,4*/	Image* rotateLeftImage;
	/*77c,4*/	Image* rotateRightImage;
	/*780,4*/	Panel_GlobFlags flags;
	/*784,4*/	undefined4 reserved;
	/*788,30*/	uint32 s_crystalShifts[2][6]; // static function variable for delayed change in crystal meter
	/*7b8*/
};
assert_sizeof(Panel_Globs, 0x7b8);

struct PanelButtonData // [LegoRR/Panels.c|struct:0x2c]
{
	/*00,10*/	Rect2F rect;
	/*10,4*/	Image* imageHover;
	/*14,4*/	Image* imagePressed;
	/*18,4*/	Image* image;
	/*1c,4*/	undefined4 reserved1; // Unused and unset?
	/*20,4*/	ToolTip_Type toolTipType;
	/*24,4*/	sint32 clickCount;
	/*28,4*/	PanelButtonFlags flags;
	/*2c*/
};
assert_sizeof(PanelButtonData, 0x2c);

struct PanelData // [LegoRR/Panels.c|struct:0x30]
{
	/*00,4*/	Image* imageOrFlic;
	/*04,4*/	bool32 isFlic;
	/*08,8*/	Point2F openPos;
	/*10,8*/	Point2F closedPos;
	/*18,8*/	Point2F position;
	/*20,4*/	undefined4 reserved1; // Unused, but set to 0.
	/*24,4*/	PanelButtonData* buttonList;
	/*28,4*/	uint32 buttonCount;
	/*2c,4*/	PanelDataFlags flags;
	/*30*/
};
assert_sizeof(PanelData, 0x30);

struct PanelTextWindow // [LegoRR/Panels.c|struct:0x10] A Panel-based wrapper around the TextWindow class
{
	/*00,4*/	TextWindow* textWindow;
	/*04,8*/	Point2F position;
	/*0c,4*/	PanelData* panel;
	/*10*/
};
assert_sizeof(PanelTextWindow, 0x10);

struct Point2F // [common.c|struct:0x8] also Vector2F
{
	/*0,4*/	real32 x;
	/*4,4*/	real32 y;
	/*8*/
};
assert_sizeof(Point2F, 0x8);

struct Point2I // [common.c|struct:0x8]
{
	/*0,4*/	sint32 x;
	/*4,4*/	sint32 y;
	/*8*/
};
assert_sizeof(Point2I, 0x8);

struct Pointer_Globs // [LegoRR/Pointer.c|struct:0x468|tags:GLOBS]
{
	/*000,4*/	Pointer_Type currType;
	/*004,e0*/	Image* images[56]; // (each item is either an ImageBMP or ImageFlic)
	/*0e4,e0*/	bool32 imageIsFlic[56];
	/*1c4,1c0*/	Point2I flicOffsets[56];
	/*384,e0*/	char* pointerName[56];
	/*464,4*/	real32 timer; // Countdown timer to change pointer(?)
	/*468*/
};
assert_sizeof(Pointer_Globs, 0x468);

struct Priorities_Globs // [LegoRR/Priorities.c|struct:0x4c0|tags:GLOBS]
{
	/*000,6c*/	char* langPriorityName[27]; // [AI_Priority_Count]
	/*06c,6c*/	Image* priorityImage[27]; // [AI_Priority_Count]
	/*0d8,6c*/	Image* priorityPressImage[27]; // [AI_Priority_Count]
	/*144,6c*/	Image* priorityOffImage[27]; // [AI_Priority_Count]
	/*1b0,6c*/	SFX_ID sfxPriorityName[27]; // [AI_Priority_Count]
	/*21c,6c*/	AI_Priority buttonTypes[27]; // Priority types for each button at index.
	/*288,d8*/	Point2F buttonPoints[27]; // Positions for each button at index.
	/*360,6c*/	AI_Priority initialTypes[27]; // Initial button positions on level start, and when reset.
	/*3cc,6c*/	uint32 initialValues[27]; // Initial values set by AITask_Game_SetPriorityValue for each button at index
	/*438,6c*/	bool32 initialOff[27]; // Initial OFF state for each button at index
	/*4a4,4*/	uint32 count; // Number of priority buttons for level.
	/*4a8,10*/	Area2F hoverArea;
	/*4b8,4*/	uint32 pressIndex;
	/*4bc,4*/	Priorities_GlobFlags flags;
	/*4c0*/
};
assert_sizeof(Priorities_Globs, 0x4c0);

struct PTL_Globs // [LegoRR/PTL.c|struct:0x144|tags:GLOBS]
{
	/*000,140*/	PTL_Property table[40];
	/*140,4*/	uint32 count;
	/*144*/
};
assert_sizeof(PTL_Globs, 0x144);

struct PTL_Property // [LegoRR/PTL.c|struct:0x8] Property loaded from a level's PTL config file (contains lookup index for actions)
{
	/*0,4*/	Message_Type fromType; // The original "posted" event message type.
	/*4,4*/	Message_Type toType; // The output "translated" event message type.
	/*8*/
};
assert_sizeof(PTL_Property, 0x8);

struct RadarMap // [LegoRR/RadarMap.c|struct:0x3c]
{
	/*00,4*/	Map3D* map;
	/*04,10*/	Area2F screenRect; // Passed value of (16.0f, 13.0f, 151.0f, 151.0f).
	/*14,4*/	real32 zoom; // Always assigned a value in the range [10,20], with 15 being the default. Higher values being more zoomed-in.
	/*18,4*/	real32 blockSize;
	/*1c,8*/	Point2F centerPos;
	/*24,10*/	Area2F worldRect;
	/*34,4*/	Draw_Rect* drawRectList;
	/*38,4*/	uint32 drawRectCount;
	/*3c*/
};
assert_sizeof(RadarMap, 0x3c);

struct RadarMap_Globs // [LegoRR/RadarMap.c|struct:0x3f4|tags:GLOBS]
{
	/*000,168*/	ColourRGBF colourTable[30]; // (constant, RGBf [0,255] -> [0,1] on RadarMap_Initialise)
	/*168,8*/	Point2I highlightBlockPos; // (init: (-1, -1)) Unused, but can highlight a radar map block in rgb(255,  0,  0).
	/*170,140*/	Vector4F arrowPointsFrom[20];
	/*2b0,140*/	Vector4F arrowPointsTo[20];
	/*3f0,4*/	uint32 arrowPointCount;
	/*3f4*/
};
assert_sizeof(RadarMap_Globs, 0x3f4);

struct RadarStructF_10 // [LegoRR/RadarMap.c|struct:0x10]
{
	/*00,4*/	real32 width; // [0,1] as ratio of appWidth
	/*04,4*/	real32 height; // [0,1] as ratio of appHeight
	/*08,4*/	real32 field_8;
	/*0c,4*/	real32 float_c; // (init: 1.0)
	/*10*/
};
assert_sizeof(RadarStructF_10, 0x10);

struct Range2F // [common.c|struct:0x8]
{
	/*0,4*/	real32 min;
	/*4,4*/	real32 max;
	/*8*/
};
assert_sizeof(Range2F, 0x8);

struct Rect2F // [common.c|struct:0x10]
{
	/*00,4*/	real32 left;
	/*04,4*/	real32 top;
	/*08,4*/	real32 right;
	/*0c,4*/	real32 bottom;
	/*10*/
};
assert_sizeof(Rect2F, 0x10);

struct Rect2I // [common.c|struct:0x10]
{
	/*00,4*/	sint32 left;
	/*04,4*/	sint32 top;
	/*08,4*/	sint32 right;
	/*0c,4*/	sint32 bottom;
	/*10*/
};
assert_sizeof(Rect2I, 0x10);

struct Reward_Globs // [LegoRR/Rewards.c|struct:0x3250|tags:GLOBS]
{
	/*0000,4*/	bool32 display; // (cfg: Display, default: false) Is the rewards screen shown on mission end?
	/*0004,4*/	bool32 centerText; // (cfg: CentreText, default: false)
	/*0008,4*/	undefined4 reserved1;
	/*000c,4*/	real32 timer; // (cfg: Timer, default: 76.9375f)
	/*0010,4*/	RewardLevel* base; // base reward state template
	/*0014,4*/	RewardLevel* level; // level requirements reward state
	/*0018,4*/	Image* wallpaper; // (cfg: Wallpaper)
	/*001c,318c*/	RewardLevel current; // current reward state, modified during gameplay
	/*31a8,4*/	real32 scrollSpeed; // (cfg: ScrollSpeed)
	/*31ac,4*/	real32 vertSpacing; // (cfg: VertSpacing)
	/*31b0,c*/	undefined4 reserved2[3];
	/*31bc,4*/	char* fontName; // (cfg: Font)
	/*31c0,4*/	Font* font; // (cfg: Font)
	/*31c4,4*/	char* titleFontName; // (cfg: TitleFont)
	/*31c8,4*/	Font* titleFont; // (cfg: TitleFont)
	/*31cc,4*/	char* backFontName; // (cfg: BackFont)
	/*31d0,4*/	Font* backFont; // (cfg: BackFont)
	/*31d4,4*/	Config* config;
	/*31d8,4*/	char* gameName;
	/*31dc,4*/	RewardScroll* scroll;
	/*31e0,8*/	Point2F saveButtonPosition; // (cfg: SaveButton[4,5])
	/*31e8,4*/	Image* saveButton; // (cfg: SaveButton[0])
	/*31ec,4*/	Image* saveButton_hi; // (cfg: SaveButton[1])
	/*31f0,4*/	Image* saveButton_in; // (cfg: SaveButton[2])
	/*31f4,4*/	Image* saveButton_dim; // (cfg: SaveButton[3])
	/*31f8,8*/	Point2F advanceButtonPosition; // (cfg: AdvanceButton[4,5])
	/*3200,4*/	Image* advanceButton; // (cfg: AdvanceButton[0])
	/*3204,4*/	Image* advanceButton_hi; // (cfg: AdvanceButton[1])
	/*3208,4*/	Image* advanceButton_in; // (cfg: AdvanceButton[2])
	/*320c,4*/	Image* advanceButton_dim; // (cfg: AdvanceButton[3])
	/*3210,4*/	char* completeText; // (cfg: CompleteText)
	/*3214,4*/	char* failedText; // (cfg: FailedText)
	/*3218,4*/	char* quitText; // (cfg: QuitText)
	/*321c,8*/	Point2I textPos; // (cfg: TextPos)
	/*3224,20*/	char statusMessage[32];
	/*3244,4*/	bool32 displayText; // (cfg: DisplayText, default: true)
	/*3248,4*/	bool32 displayImages; // (cfg: DisplayImages, default: true)
	/*324c,4*/	bool32 displayFlics; // (cfg: DisplayFlics, default: true)
	/*3250*/
};
assert_sizeof(Reward_Globs, 0x3250);

struct RewardBuildingCounts // [LegoRR/Rewards.c|struct:0x198]
{
	/*000,190*/	char* nameTable[100];
	/*190,4*/	uint32 count;
	/*194,4*/	uint32 numPrevLevels_unk;
	/*198*/
};
assert_sizeof(RewardBuildingCounts, 0x198);

struct RewardLevel // [LegoRR/Rewards.c|struct:0x318c]
{
	/*0000,4*/	bool32 Enabled;
	/*0004,4*/	bool32 saveHasCapture;
	/*0008,20*/	Image saveCaptureImage;
	/*0028,198*/	RewardBuildingCounts buildingCounts;
	/*01c0,4*/	sint32 Modifier;
	/*01c4,4*/	undefined field_0x1c4_0x1c7[4];
	/*01c8,4*/	undefined4 field_1c8;
	/*01cc,4*/	uint32 uintConstructCount_1cc;
	/*01d0,4*/	uint32 uintConstruct_1d0;
	/*01d4,1900*/	char buildingNameBuffers[100][64];
	/*1ad4,30*/	undefined field_0x1ad4_0x1b03[48];
	/*1b04,4*/	real32 float_1b04;
	/*1b08,4*/	real32 float_1b08;
	/*1b0c,4*/	real32 float_1b0c;
	/*1b10,1d4*/	undefined field_0x1b10_0x1ce3[468];
	/*1ce4,4*/	sint32 itemCount; // (init: 10)
	/*1ce8,4*/	RewardLevelItem* itemPtr; // (init: &items_TABLE)
	/*1cec,14a0*/	RewardLevelItem items[10];
	/*318c*/
};
assert_sizeof(RewardLevel, 0x318c);

struct RewardLevelItem // [LegoRR/Rewards.c|struct:0x210]
{
	/*000,4*/	RewardItemFlags flags; // (0x4 = flic)
	/*004,20*/	char name[32];
	/*024,4*/	real32 Importance;
	/*028,4*/	sint32 Quota;
	/*02c,4*/	undefined field_0x2c_0x2f[4];
	/*030,4*/	real32 countdownRatio; // Elapsed / Countdown Timers
	/*034,4*/	real32 countdown; // Countdown timer
	/*038,4*/	real32 percentFloat;
	/*03c,4*/	uint32 numGenerated;
	/*040,4*/	uint32 numDestroyed;
	/*044,4*/	uint32 numAttacked; // For every weapon attack
	/*048,4*/	real32 damageTaken;
	/*04c,4*/	undefined field_0x4c_0x4f[4];
	/*050,4*/	sint32 percentInt;
	/*054,80*/	char Text[128]; // (TODO: size me)
	/*0d4,80*/	char valueText[128];
	/*154,8*/	Point2I TextPosition;
	/*15c,8*/	Point2I ImagePosition;
	/*164,8*/	Point2I BoxImagePosition;
	/*16c,80*/	char FlicName[128]; // (TODO: size me)
	/*1ec,8*/	Size2I FlicSize;
	/*1f4,8*/	Point2I FlicPosition;
	/*1fc,4*/	Flic* Flic;
	/*200,4*/	Image* Image;
	/*204,4*/	Font* Font;
	/*208,4*/	char* SoundName;
	/*20c,4*/	Image* BoxImage;
	/*210*/
};
assert_sizeof(RewardLevelItem, 0x210);

struct RewardScroll // [LegoRR/Rewards.c|struct:0x28]
{
	/*00,4*/	real32 yInitial; // (init: appHeight() / 20.0f)
	/*04,4*/	real32 xPos; // (init: 0.0f)
	/*08,4*/	real32 yPos; // (init: appHeight() / 20.0f) scrollCountdown??
	/*0c,4*/	real32 width; // (init: appWidth())
	/*10,4*/	real32 height; // (init: appHeight() - appHeight() / 3.5f)
	/*14,4*/	real32 scrollSpeed;
	/*18,4*/	real32 curScrollY; // (init: set to 400.0 after Create function)
	/*1c,4*/	uint32 labelCount;
	/*20,4*/	RewardScrollLabel** labels;
	/*24,4*/	RewardScrollFlags flags;
	/*28*/
};
assert_sizeof(RewardScroll, 0x28);

struct RewardScrollLabel // [LegoRR/Rewards.c|struct:0x20]
{
	/*00,4*/	RewardScrollLabelMode mode; // (0=none, 1=txtWnd+, 2=image+, 3=font+)
	/*04,4*/	real32 xPos;
	/*08,4*/	real32 yPos; // (vertSpacing?)
	/*0c,4*/	TextWindow* textWnd;
	/*10,4*/	Image* image;
	/*14,4*/	char* text;
	/*18,4*/	Font* font;
	/*1c,4*/	RewardScrollLabelFlags flags; // ( 1 = centered??, 2 = ? )
	/*20*/
};
assert_sizeof(RewardScrollLabel, 0x20);

struct RNC_Globs // [Gods98/Compress.c|struct:0x32c|tags:GLOBS]
{
	/*000,1*/	uint8 BitCount; // Never greater than 16
	/*001,3*/	undefined1 padding1[3];
	/*004,14*/	undefined4 reserved1[5]; // Probably used for missing compression functions
	/*018,100*/	HuffmanLeaf HuffmanTable_Raw[16];
	/*118,100*/	HuffmanLeaf HuffmanTable_Dst[16];
	/*218,100*/	HuffmanLeaf HuffmanTable_Len[16];
	/*318,4*/	uint8* Input; // Input ptr at current read position
	/*31c,4*/	uint8* Output;
	/*320,1*/	uint8 ByteBuffer; // buffer for method2 "fast"
	/*321,3*/	undefined1 padding2[3];
	/*324,4*/	uint32 BitBuffer; // buffer for method1 "best" (4-byte int, but should only ever be 2-bytes)
	/*328,4*/	uint8* OutputEnd;
	/*32c*/
};
assert_sizeof(RNC_Globs, 0x32c);

#pragma pack(push, 1)
struct RNC_Header // [Gods98/Compress.c|struct:0x12|pack:1] After this structure is the RNC data payload
{
	/*00,3*/	char signature[3]; // "RNC"
	/*03,1*/	RNCCompression compression; // (0=store, 1=best, 2=fast)
	/*04,4*/	uint32 beOrigSize;
	/*08,4*/	uint32 bePackedSize;
	/*0c,2*/	uint16 beOrigCRC;
	/*0e,2*/	uint16 bePackedCRC; // Checksum of the RNC data
	/*10,1*/	uint8 leeway; // Difference between compressed and uncompressed data in largest pack chunk (if larger than decompressed data)
	/*11,1*/	uint8 packChunks; // Amount of pack chunks
	/*12*/
};
assert_sizeof(RNC_Header, 0x12);
#pragma pack(pop)

#pragma pack(push, 1)
struct RNC_HeaderInfo // [Gods98/Compress.c|struct:0x13|pack:1] After this structure is the RNC data payload
{
	/*00,3*/	char signature[3]; // "RNC"
	/*03,1*/	RNCCompression compression; // (0=store, 1=best, 2=fast)
	/*04,4*/	uint32 beOrigSize;
	/*08,4*/	uint32 bePackedSize;
	/*0c,2*/	uint16 beOrigCRC;
	/*0e,2*/	uint16 bePackedCRC; // Checksum of the RNC data
	/*10,1*/	uint8 leeway; // Difference between compressed and uncompressed data in largest pack chunk (if larger than decompressed data)
	/*11,1*/	uint8 packChunks; // Amount of pack chunks
	/*12,1*/	uint8 data[1];
	/*13*/
};
assert_sizeof(RNC_HeaderInfo, 0x13);
#pragma pack(pop)

struct Roof_Globs // [LegoRR/Roof.c|struct:0x7f0|tags:GLOBS] A level's roof mesh displayed in the world (only when in FP)
{
	/*000,4*/	Container* contMesh; // MakeMesh2:IMMEDIATE
	/*004,8*/	Size2I dimensions;
	/*00c,4*/	bool32 hidden;
	/*010,4*/	bool32 needsUpdate; // Similar to the ROOF_NEEDSUPDATE flag, but is true if any blocks have to be updated
	/*014,4*/	Container_Texture* texture;
	/*018,4*/	RoofBlock* grid; // Allocation size of 8, may be same as struct type below
	/*01c,7d0*/	RoofBlock* visibleTable[500]; // items are either null, or point to a block in grid
	/*7ec,4*/	uint32 visibleCount; // (not sure if "visible" is correct)
	/*7f0*/
};
assert_sizeof(Roof_Globs, 0x7f0);

struct RoofBlock // [LegoRR/Roof.c|struct:0x8] Mesh group for a single block in the world's roof. (only used for FP)
{
	/*0,4*/	D3DRMGroupIndex groupID;
	/*4,4*/	RoofFlags flags; // (0x1 = hidde, 0x2 = needsUpdate, 0x4 = shiftVertices)
	/*8*/
};
assert_sizeof(RoofBlock, 0x8);

struct RoutingBlock // [LegoRR/Routing.c|struct:0x14]
{
	/*00,8*/	Point2I blockPos;
	/*08,8*/	Point2F blockOffset; // In range of [0.0,1.0], where 0.5 is the center of the block.
	/*10,1*/	RouteFlags flagsByte;
	/*11,1*/	RouteAction actionByte;
	/*12,2*/	undefined field_0x12_0x13[2];
	/*14*/
};
assert_sizeof(RoutingBlock, 0x14);

struct RROSFileHeader // [LegoRR/ObjectRecall.c|struct:0x8] For .osf Object Recall save files
{
	/*0,4*/	char signature[4];
	/*4,4*/	uint32 count;
	/*8*/
};
assert_sizeof(RROSFileHeader, 0x8);

struct SaveData // [LegoRR/save.c|struct:0xb8]
{
	/*00,4*/	undefined4 field_0x0;
	/*04,4*/	sint32 SliderMusicVolume;
	/*08,4*/	sint32 SliderSoundVolume;
	/*0c,4*/	sint32 SliderGameSpeed;
	/*10,4*/	sint32 SliderBrightness;
	/*14,4*/	undefined4 field_0x14;
	/*18,4*/	uint32 missionsCount;
	/*1c,18*/	SaveStruct_18 saveStruct18_1c;
	/*34,4*/	SaveReward* missionsTable; // std::malloc(count_18 * 0x3190)
	/*38,4*/	undefined4 field_0x38;
	/*3c,4*/	undefined4 field_0x3c;
	/*40,4*/	undefined4 field_0x40;
	/*44,4*/	undefined4 field_0x44;
	/*48,4*/	undefined4 field_0x48;
	/*4c,4*/	undefined4 field_0x4c;
	/*50,4*/	undefined4 field_0x50;
	/*54,4*/	undefined4 field_0x54;
	/*58,4*/	undefined4 field_0x58;
	/*5c,4*/	undefined4 field_0x5c;
	/*60,4*/	undefined4 field_0x60;
	/*64,4*/	undefined4 field_0x64;
	/*68,4*/	undefined4 field_0x68;
	/*6c,4*/	undefined4 field_0x6c;
	/*70,4*/	undefined4 field_0x70;
	/*74,4*/	undefined4 field_0x74;
	/*78,4*/	undefined4 field_0x78;
	/*7c,4*/	undefined4 field_0x7c;
	/*80,4*/	undefined4 field_0x80;
	/*84,4*/	undefined4 field_0x84;
	/*88,4*/	undefined4 field_0x88;
	/*8c,4*/	undefined4 field_0x8c;
	/*90,4*/	undefined4 field_0x90;
	/*94,4*/	undefined4 field_0x94;
	/*98,4*/	undefined4 field_0x98;
	/*9c,4*/	undefined4 field_0x9c;
	/*a0,4*/	undefined4 field_0xa0;
	/*a4,4*/	undefined4 field_0xa4;
	/*a8,4*/	undefined4 field_0xa8;
	/*ac,4*/	undefined4 field_0xac;
	/*b0,4*/	undefined4 field_0xb0;
	/*b4,4*/	undefined4 field_0xb4;
	/*b8*/
};
assert_sizeof(SaveData, 0xb8);

struct SaveReward // [LegoRR/save.c|struct:0x3190]
{
	/*0000,4*/	SaveRewardFlags flags;
	/*0004,318c*/	RewardLevel reward;
	/*3190*/
};
assert_sizeof(SaveReward, 0x3190);

struct SaveStruct_18 // [LegoRR/save.c|struct:0x18]
{
	/*00,18*/	undefined field_0x0_0x17[24];
	/*18*/
};
assert_sizeof(SaveStruct_18, 0x18);

struct ScrollInfoStruct_20 // [LegoRR/ScrollInfo.c|struct:0x20]
{
	/*00,4*/	Image* image;
	/*04,8*/	Point2F pointOrSize;
	/*0c,4*/	ScrollInfoSubStruct_1c* ptr1c_c;
	/*10,4*/	ScrollInfoSubStruct_1c* ptr1c_10;
	/*14,4*/	ScrollInfoSubStruct_28* substruct28;
	/*18,4*/	Panel_Type panelType;
	/*1c,4*/	uint32 flags; // (1 = used, 4 = hasImage)
	/*20*/
};
assert_sizeof(ScrollInfoStruct_20, 0x20);

struct ScrollInfoSubStruct_1c // [LegoRR/ScrollInfo.c|struct:0x1c]
{
	/*00,8*/	Point2F point1;
	/*08,8*/	Point2F point2;
	/*10,4*/	Image* image1;
	/*14,4*/	Image* image2;
	/*18,4*/	uint32 flags;
	/*1c*/
};
assert_sizeof(ScrollInfoSubStruct_1c, 0x1c);

struct ScrollInfoSubStruct_28 // [LegoRR/ScrollInfo.c|struct:0x28]
{
	/*00,8*/	Point2F point1;
	/*08,8*/	Point2F point2;
	/*10,4*/	undefined4 field_10;
	/*14,4*/	undefined4 field_14;
	/*18,4*/	Image* image;
	/*1c,4*/	sint32 intM1_1c;
	/*20,4*/	sint32 int_20;
	/*24,4*/	bool32 bool_24;
	/*28*/
};
assert_sizeof(ScrollInfoSubStruct_28, 0x28);

struct SearchAddCryOre_c // [LegoRR/search.c|struct:0xc]
{
	/*0,4*/	undefined4 field_0;
	/*4,4*/	uint32 crystalCount;
	/*8,4*/	uint32 oreCount; // normal ore
	/*c*/
};
assert_sizeof(SearchAddCryOre_c, 0xc);

struct SearchAITaskDeselect_8 // [LegoRR/search.c|struct:0x8]
{
	/*0,4*/	Point2I* blockPos;
	/*4,4*/	bool32 digConnection; // If the task is AITask_Type_Dig, then this must match flag 0x8 (DIGCONNECTION).
	/*8*/
};
assert_sizeof(SearchAITaskDeselect_8, 0x8);

struct SearchCollision_14 // [LegoRR/search.c|struct:0x14] LiveObject_DoCollisionCallbacks_FUN_00446030
{
	/*00,4*/	LegoObject* targetObj;
	/*04,4*/	Point2F* pointf_4;
	/*08,4*/	real32 float_8;
	/*0c,4*/	LegoObject* result;
	/*10,4*/	bool32 bool_10;
	/*14*/
};
assert_sizeof(SearchCollision_14, 0x14);

struct SearchDynamiteRadius // [LegoRR/search.c|struct:0x18] Used for both dynamite and birdScarer
{
	/*00,4*/	LegoObject* liveObj;
	/*04,8*/	Point2F worldPos;
	/*0c,4*/	real32 radius;
	/*10,4*/	real32 maxDamage; // (dynamite only)
	/*14,4*/	real32 wakeRadius; // (dynamite only)
	/*18*/
};
assert_sizeof(SearchDynamiteRadius, 0x18);

struct SearchInfoBlockPos_8 // [LegoRR/search.c|struct:0x8]
{
	/*0,4*/	Point2I* pBlockPos;
	/*4,4*/	uint32 index;
	/*8*/
};
assert_sizeof(SearchInfoBlockPos_8, 0x8);

struct SearchInfoObject_8 // [LegoRR/search.c|struct:0x8]
{
	/*0,4*/	LegoObject* object;
	/*4,4*/	uint32 index;
	/*8*/
};
assert_sizeof(SearchInfoObject_8, 0x8);

struct SearchInfoObjectBlockPos_8 // [LegoRR/search.c|struct:0x8]
{
	/*0,4*/	LegoObject* optObject;
	/*4,4*/	Point2I* optBlockPos;
	/*8*/
};
assert_sizeof(SearchInfoObjectBlockPos_8, 0x8);

struct SearchInterfaceFindObject // [LegoRR/search.c|struct:0x18]
{
	/*00,4*/	LegoObject_Type objType; // (condition: flags & 0x1)
	/*04,4*/	LegoObject_ID objID; // (condition: flags & 0x1)
	/*08,4*/	StatsFlags1 statsFlags1; // (condition: nonzero)
	/*0c,4*/	StatsFlags2 statsFlags2; // (condition: nonzero)
	/*10,4*/	LegoObject_AbilityFlags abilityFlags; // (condition: flags & 0x2)
	/*14,4*/	uint32 flags; // (0x1: objType/objID, 0x2: abilityFlags)
	/*18*/
};
assert_sizeof(SearchInterfaceFindObject, 0x18);

struct SearchLevelLinkFindIndex_10 // [LegoRR/search.c|struct:0x10]
{
	/*00,4*/	LevelLink* resultLink; // Output level link identifier (not modified on failure)
	/*04,4*/	sint32 searchIndex; // Link index to search for
	/*08,4*/	sint32 currentIndex; // Current index in linked list.
	/*0c,4*/	sint32 resultIndex; // Link index of found result, should end up equal to searchIndex, or 0 on failure.
	/*10*/
};
assert_sizeof(SearchLevelLinkFindIndex_10, 0x10);

struct SearchLevelSelectAdd // [LegoRR/search.c|struct:0x10]
{
	/*00,4*/	LevelSet* levelSet;
	/*04,4*/	Menu* menu_4; // in_submenu (param_4)
	/*08,4*/	MenuItem_SelectData* itemData; // (init: 0)
	/*0c,4*/	SaveData* currSave; // param_5
	/*10*/
};
assert_sizeof(SearchLevelSelectAdd, 0x10);

struct SearchLevelSelectInfo_14 // [LegoRR/search.c|struct:0x14]
{
	/*00,4*/	SaveReward* saveReward; // (optional)
	/*04,4*/	LevelSet* levelSet;
	/*08,4*/	MenuItem_SelectData* selectData;
	/*0c,4*/	uint32 index;
	/*10,4*/	bool32 keepLocked; // (check whether complete or unlocked???)
	/*14*/
};
assert_sizeof(SearchLevelSelectInfo_14, 0x14);

struct SearchNERPsCountRecordObjects // [LegoRR/search.c|struct:0x8]
{
	/*0,4*/	uint32 count;
	/*4,4*/	LegoObject* liveObj;
	/*8*/
};
assert_sizeof(SearchNERPsCountRecordObjects, 0x8);

struct SearchNERPsSetMonsterAttack // [LegoRR/search.c|struct:0xc]
{
	/*0,4*/	uint32 sflags2Exclude; // (type: StatsFlags2) Fails the search if the target object has any of these flags (and is not 0xffffffff).
	/*4,4*/	uint32 sflags2Include; // (type: StatsFlags2) Fails the search if the target object has none of these flags (and is not 0xffffffff).
	/*8,4*/	bool32 stopAttacking; // EXACT BOOL (0 = start attacking, 1 = stop attacking)
	/*c*/
};
assert_sizeof(SearchNERPsSetMonsterAttack, 0xc);

struct SearchNERPsSetObjectHealthPain // [LegoRR/search.c|struct:0xc]
{
	/*0,4*/	uint32 type; // (0 = runningAway, 1 = painThreshold, 2 = Health)
	/*4,4*/	uint32 runningAwayCount; // Only for healthType 0 (incremented)
	/*8,4*/	real32 painHealthValue; // Only for healthTypes 1,2 (assigns)
	/*c*/
};
assert_sizeof(SearchNERPsSetObjectHealthPain, 0xc);

struct SearchNERPsTutorialAction // [LegoRR/search.c|struct:0x2c]
{
	/*00,4*/	NERPsTutorialAction action;
	/*04,4*/	sint32 blockPointerIdx;
	/*08,4*/	sint32 result;
	/*0c,8*/	undefined field_0xc_0x13[8];
	/*14,8*/	Point2I blockPos;
	/*1c,4*/	undefined4 fieldBool_1c;
	/*20,4*/	undefined4 fieldBool_20;
	/*24,4*/	LegoObject* object_24;
	/*28,4*/	sint32 int_28;
	/*2c*/
};
assert_sizeof(SearchNERPsTutorialAction, 0x2c);

struct SearchObjectBlockXY_c // [LegoRR/search.c|struct:0xc]
{
	/*0,4*/	LegoObject* resultObj;
	/*4,4*/	sint32 bx;
	/*8,4*/	sint32 by;
	/*c*/
};
assert_sizeof(SearchObjectBlockXY_c, 0xc);

struct SearchObjectMouseXY_c // [LegoRR/search.c|struct:0xc]
{
	/*0,4*/	LegoObject** refObj;
	/*4,4*/	real32 mouseX;
	/*8,4*/	real32 mouseY;
	/*c*/
};
assert_sizeof(SearchObjectMouseXY_c, 0xc);

struct SearchObjectTypeCount_c // [LegoRR/search.c|struct:0xc]
{
	/*0,4*/	LegoObject_Type objType;
	/*4,4*/	sint32 objIndex;
	/*8,4*/	uint32 count;
	/*c*/
};
assert_sizeof(SearchObjectTypeCount_c, 0xc);

struct SearchRadarObjectInArea // [LegoRR/search.c|struct:0x10]
{
	/*00,4*/	LegoObject* object;
	/*04,8*/	Point2F worldPos;
	/*0c,4*/	real32 radius; // BlockSize -or- (BlockSize / 6.0)
	/*10*/
};
assert_sizeof(SearchRadarObjectInArea, 0x10);

struct SearchSetObjectsLevel_8c // [LegoRR/search.c|struct:0x8c]
{
	/*00,80*/	char objName[128];
	/*80,4*/	uint32 objLevel;
	/*84,4*/	LegoObject_Type objType;
	/*88,4*/	LegoObject_IDs objID;
	/*8c*/
};
assert_sizeof(SearchSetObjectsLevel_8c, 0x8c);

struct SearchTeleporter_10 // [LegoRR/search.c|struct:0x10] Teleporter_Creat_FUN_0046a7d0
{
	/*00,4*/	LegoObject_Type objType;
	/*04,4*/	uint32 modeFlags;
	/*08,4*/	uint32 teleportFlags;
	/*0c,4*/	TeleporterService* teleporter;
	/*10*/
};
assert_sizeof(SearchTeleporter_10, 0x10);

struct SearchViewportWindow_14 // [LegoRR/search.c|struct:0x14]
{
	/*00,4*/	Viewport* view;
	/*04,8*/	Point2F dragStart;
	/*0c,8*/	Point2F dragEnd;
	/*14*/
};
assert_sizeof(SearchViewportWindow_14, 0x14);

struct SearchWeapons18_2 // [LegoRR/search.c|struct:0x18]
{
	/*00,4*/	LegoObject* foundObject;
	/*04,4*/	real32 ref_float_4;
	/*08,4*/	Vector3F* fromPos;
	/*0c,4*/	Vector3F* fromToDistance;
	/*10,4*/	bool32 success;
	/*14,4*/	LegoObject* ignoreObject;
	/*18*/
};
assert_sizeof(SearchWeapons18_2, 0x18);

struct SelectPlace // [LegoRR/SelectPlace.c|struct:0x8] Building selection highlight shown on map when placing
{
	/*0,4*/	Container* contMesh;
	/*4,4*/	real32 tileDepth; // (init: 5.0) Z height of each coloured square when drawing the building placement grid.
	/*8*/
};
assert_sizeof(SelectPlace, 0x8);

struct SFX_Globs // [LegoRR/SFX.c|struct:0x1770|tags:GLOBS]
{
	/*0000,f78*/	SFX_Property samplePropTable[495];
	/*0f78,640*/	SFX_Property sampleGroupTable[200];
	/*15b8,4*/	uint32* hashNameList;
	/*15bc,4*/	uint32 hashNameCount;
	/*15c0,4*/	uint32 sampleGroupCount;
	/*15c4,4*/	SFX_GlobFlags flags;
	/*15c8,f0*/	SFX_Instance sfxInstanceTable[10];
	/*16b8,4*/	uint32 sfxInstanceCount;
	/*16bc,4*/	real32 globalSampleDuration; // Duration is multiplied by 25.0
	/*16c0,4*/	sint32 globalSampleSoundHandle;
	/*16c4,4*/	SFX_ID globalSampleSFXType;
	/*16c8,28*/	SFX_ID soundQueueSFXTable_1[10];
	/*16f0,28*/	SoundMode soundQueueModesTable_1[10];
	/*1718,28*/	SFX_ID soundQueueSFXTable_2[10];
	/*1740,28*/	SoundMode soundQueueModesTable_2[10];
	/*1768,4*/	uint32 soundQueueCount_1;
	/*176c,4*/	uint32 soundQueueCount_2;
	/*1770*/
};
assert_sizeof(SFX_Globs, 0x1770);

struct SFX_Instance // [LegoRR/SFX.c|struct:0x18]
{
	/*00,4*/	sint32 sampleIndex;
	/*04,4*/	IDirect3DRMFrame3* frame; // what happened to hiding D3DRM behind Containers and 3DSound?
	/*08,c*/	Vector3F position;
	/*14,4*/	SFX_InstanceFlags flags;
	/*18*/
};
assert_sizeof(SFX_Instance, 0x18);

struct SFX_Property // [LegoRR/SFX.c|struct:0x8]
{
	/*0,4*/	sint32 sound3DHandle;
	/*4,4*/	SFX_Property* next; // next group property
	/*8*/
};
assert_sizeof(SFX_Property, 0x8);

struct Size2F // [common.c|struct:0x8]
{
	/*0,4*/	real32 width;
	/*4,4*/	real32 height;
	/*8*/
};
assert_sizeof(Size2F, 0x8);

struct Size2I // [common.c|struct:0x8]
{
	/*0,4*/	sint32 width;
	/*4,4*/	sint32 height;
	/*8*/
};
assert_sizeof(Size2I, 0x8);

struct Smoke // [LegoRR/Smoke.c|struct:0x2a8]
{
	/*000,258*/	Smoke_Group groupList[10];
	/*258,4*/	real32 newSmokeTimer; // Countdown timer until another smoke group is added.
	/*25c,c*/	Vector3F sfxOrigin; // Originating position of SFX when played in world.
	/*268,c*/	Vector3F dirVec; // Base move direction vector for smoke groups before randomness is applied.
	/*274,c*/	ColourRGBF colour;
	/*280,4*/	uint32 groupCount;
	/*284,4*/	sint32 numRepeats; // (Dissipate) Number of repeats from 0-4 before vanishing.
	/*288,4*/	real32 animSpeed; // Speed of creating new groups and applied to movement speed.
	/*28c,4*/	Container* cont; // Attached or created container for mesh.
	/*290,4*/	Mesh* mesh;
	/*294,4*/	SmokeFlags flags;
	/*298,4*/	Smoke* next; // Next Smoke in doubly-linked list.
	/*29c,4*/	Smoke* previous; // Previous Smoke in doubly-linked list.
	/*2a0,4*/	SFX_ID sfxID;
	/*2a4,4*/	sint32 sound3DPlayHandle;
	/*2a8*/
};
assert_sizeof(Smoke, 0x2a8);

struct Smoke_Globs // [LegoRR/Smoke.c|struct:0x34|tags:GLOBS]
{
	/*00,28*/	Container_Texture* textureList[10];
	/*28,4*/	Smoke* firstSmoke; // A doublely-linked list, each node has next/previous as well
	/*2c,4*/	Smoke* lastSmoke;
	/*30,4*/	uint32 textureCount;
	/*34*/
};
assert_sizeof(Smoke_Globs, 0x34);

struct Smoke_Group // [LegoRR/Smoke.c|struct:0x3c]
{
	/*00,4*/	bool32 used;
	/*04,c*/	Vector3F randVec; // (init: Smoke_Group_Show, stored randomness applied to dirVec to get moveVec, unused)
	/*10,c*/	Vector3F moveVec; // (init: Smoke_Group_Show, readonly)
	/*1c,c*/	Vector3F position; // (init: Container_GetPosition, updated)
	/*28,4*/	real32 float_28;
	/*2c,4*/	real32 float_2c;
	/*30,4*/	real32 timer_30; // Count-up timer related to alpha (never used for anything).
	/*34,4*/	sint32 int_34; // (random: [40,69]) Related to constant scalar 0.7f
	/*38,4*/	real32 timerUp_38; // Count-up timer (used for rendering).
	/*3c*/
};
assert_sizeof(Smoke_Group, 0x3c);

struct Sound3D_Globs // [Gods98/3DSound.c|struct:0x2d34c|tags:GLOBS]
{
	/*00000,4*/	IDirectSound* lpDSnd;
	/*00004,4*/	IDirectSoundBuffer* lpDSBuff;
	/*00008,4*/	IDirectSound3DListener* lp3DListenerInfo;
	/*0000c,4*/	IDirectSoundBuffer* lpDSStreamBuff;
	/*00010,4*/	IDirectSoundBuffer* lpDSLoopStreamBuff;
	/*00014,5c*/	Sound3D_StreamData streamData;
	/*00070,5c*/	Sound3D_StreamData loopStreamData;
	/*000cc,4*/	Sound3D_SoundRecord* soundRecord;
	/*000d0,4*/	IDirect3DRMFrame3* listenerFrame;
	/*000d4,4*/	real32 minDistanceForAttentuation;
	/*000d8,4*/	real32 maxDistance;
	/*000dc,4*/	sint32 volume;
	/*000e0,2d1e0*/	Sound3D_SoundData soundTable[600];
	/*2d2c0,4*/	bool32 intialised;
	/*2d2c4,4*/	sint32 windowsVolume;
	/*2d2c8,4*/	uint32 flags;
	/*2d2cc,50*/	IDirect3DRMFrame3* updateFrameList[20];
	/*2d31c,4*/	uint32 reserved1;
	/*2d320,c*/	Vector3F s_ListenerCallback_oldPos;
	/*2d32c,4*/	uint32 reserved2;
	/*2d330,c*/	Vector3F s_ListenerCallback_oldOrien;
	/*2d33c,4*/	uint32 reserved3;
	/*2d340,c*/	Vector3F s_ListenerCallback_oldOrienUp;
	/*2d34c*/
};
assert_sizeof(Sound3D_Globs, 0x2d34c);

struct Sound3D_SoundData // [Gods98/3DSound.c|struct:0x134]
{
	/*000,104*/	char filename[260];
	/*104,4*/	uint32 size;
	/*108,4*/	uint32 avgBytesPerSec; // Only set for streaming buffers
	/*10c,4*/	sint32 frequency;
	/*110,4*/	sint32 volume;
	/*114,4*/	sint32 offset;
	/*118,4*/	uint8* data;
	/*11c,4*/	WAVEFORMATEX* waveFormat;
	/*120,c*/	IDirectSoundBuffer* dSoundBuffers[3]; // ([] = max simultaneous 3D sounds)
	/*12c,4*/	uint32 bufferIndex; // (official: voice)
	/*130,4*/	Sound3DFlags flags;
	/*134*/
};
assert_sizeof(Sound3D_SoundData, 0x134);

struct Sound3D_SoundFrameRecord // [Gods98/3DSound.c|struct:0x14]
{
	/*00,4*/	IDirectSound3DBuffer* sound3DBuff;
	/*04,c*/	Vector3F pos;
	/*10,4*/	Sound3D_SoundFrameRecord* next;
	/*14*/
};
assert_sizeof(Sound3D_SoundFrameRecord, 0x14);

struct Sound3D_SoundRecord // [Gods98/3DSound.c|struct:0x10]
{
	/*00,4*/	IDirect3DRMFrame3* frame;
	/*04,4*/	IDirectSoundBuffer* soundBuff;
	/*08,4*/	IDirectSound3DBuffer* sound3DBuff;
	/*0c,4*/	Sound3D_SoundRecord* next;
	/*10*/
};
assert_sizeof(Sound3D_SoundRecord, 0x10);

struct Sound3D_StreamData // [Gods98/3DSound.c|struct:0x5c]
{
	/*00,4*/	bool32 fileOpen; // paused/playing/used?
	/*04,54*/	Sound3D_WaveData wiWave;
	/*58,4*/	bool32 playing; // paused/playing/used?
	/*5c*/
};
assert_sizeof(Sound3D_StreamData, 0x5c);

struct Sound3D_WaveData // [Gods98/3DSound.c|struct:0x54]
{
	/*00,4*/	WAVEFORMATEX* waveFormat; // Wave Format data structure (hGlobal)
	/*04,4*/	HMMIO hmmio; // MM I/O handle for the WAVE
	/*08,14*/	MMCKINFO mmck; // Multimedia RIFF chunk
	/*1c,14*/	MMCKINFO mmckInRIFF; // Use in opening a WAVE file
	/*30,4*/	DWORD dwBufferSize; // Size of the entire buffer
	/*34,4*/	DWORD dwNotifySize; // size of each notification period.
	/*38,4*/	DWORD dwNextWriteOffset; // Offset to next buffer segment
	/*3c,4*/	DWORD dwProgress; // Used with above to show prog.
	/*40,4*/	DWORD dwNextProgressCheck;
	/*44,4*/	DWORD dwLastPos; // the last play position returned by GetCurrentPos().
	/*48,4*/	bool32 bDonePlaying; // Signals early abort to timer
	/*4c,4*/	bool32 bLoopFile; // Should we loop playback?
	/*50,4*/	bool32 bFoundEnd; // Timer found file end
	/*54*/
};
assert_sizeof(Sound3D_WaveData, 0x54);

struct Sound_Globs // [Gods98/Sound.c|struct:0x1b8|tags:GLOBS]
{
	/*000,4*/	uint32 useSound; // Number of sounds in soundList
	/*004,4*/	bool32 initialised;
	/*008,190*/	uint32 soundList[100];
	/*198,4*/	sint32 currTrack;
	/*19c,4*/	bool32 loopCDTrack;
	/*1a0,4*/	SoundCDStopCallback CDStopCallback;
	/*1a4,4*/	bool32 updateCDTrack;
	/*1a8,4*/	uint32 s_Update_lastUpdate;
	/*1ac,8*/	undefined4 reserved1[2];
	/*1b4,4*/	MCIERROR mciErr;
	/*1b8*/
};
assert_sizeof(Sound_Globs, 0x1b8);

struct SpiderWeb_Block // [LegoRR/SpiderWeb.c|struct:0xc]
{
	/*0,4*/	LegoObject* object; // "SpiderWeb" LiveObject
	/*4,4*/	real32 health; // Assumed as health, init: 100.0f
	/*8,4*/	SpiderWeb_BlockFlags flags;
	/*c*/
};
assert_sizeof(SpiderWeb_Block, 0xc);

struct SpiderWeb_Globs // [LegoRR/SpiderWeb.c|struct:0x8|tags:GLOBS]
{
	/*0,4*/	SpiderWeb_Block* webBlocks;
	/*4,4*/	Lego_Level* level;
	/*8*/
};
assert_sizeof(SpiderWeb_Globs, 0x8);

struct Stats_Globs // [LegoRR/Stats.c|struct:0x5b0|tags:GLOBS]
{
	/*000,50*/	ObjectStats** objectStats[20]; // [objType:20][*objIndex][*objLevel]
	/*050,4b0*/	uint32 objectLevels[20][15]; // [objType:20][objIndex:15]
	/*500,b0*/	ToolStats toolStats[11]; // [toolType:11]
	/*5b0*/
};
assert_sizeof(Stats_Globs, 0x5b0);

struct Teleporter_Globs // [LegoRR/Teleporter.c|struct:0x10|tags:GLOBS]
{
	/*00,4*/	uint32 count;
	/*04,4*/	sint32 intValue_40; // (const: 40)
	/*08,4*/	TeleporterService* current;
	/*0c,4*/	real32 floatValue_3_0; // (const: 3.0)
	/*10*/
};
assert_sizeof(Teleporter_Globs, 0x10);

struct TeleporterService // [LegoRR/Teleporter.c|struct:0x20]
{
	/*00,8*/	Point2F cameraPos; // (init: if flags 0x2)
	/*08,4*/	real32 float_8; // (init: 0 if flags 0x2)
	/*0c,4*/	real32 float_c; // (init: 3.0 if flags 0x2)
	/*10,4*/	uint32 count; // (init: 0)
	/*14,4*/	sint32 int_14; // (init: 40 if flags 0x1)
	/*18,4*/	uint32 flags; // (init: flags)
	/*1c,4*/	TeleporterService* next;
	/*20*/
};
assert_sizeof(TeleporterService, 0x20);

struct TEXDATA // [Gods98/Lwt.c|struct:0xc] (an alias for Vector3F)
{
	/*0,4*/	real32 tdX;
	/*4,4*/	real32 tdY;
	/*8,4*/	real32 tdZ;
	/*c*/
};
assert_sizeof(TEXDATA, 0xc);

struct Text_Globs // [LegoRR/Text.c|struct:0x4dc|tags:GLOBS]
{
	/*000,68*/	char* textName[26];
	/*068,68*/	char* textMessages[26];
	/*0d0,68*/	Image* textImages[26];
	/*138,340*/	char textImagesSFX[26][32];
	/*478,4*/	Text_Type currType;
	/*47c,4*/	uint32 textCount;
	/*480,4*/	uint32 jankCounter; // See Text_Update for description. Jank is in the name for a reason...
	/*484,4*/	char* currText; // Pointer to NERPsMessage raw text
	/*488,4*/	real32 float_488;
	/*48c,4*/	TextWindow* textOnlyWindow;
	/*490,4*/	TextWindow* textImageWindow; // Same as textOnlyWindow, but used instead when there's an image.
	/*494,4*/	undefined4 reserved1;
	/*498,4*/	uint32 uint_498;
	/*49c,10*/	Area2F MsgPanel_Rect1;
	/*4ac,4*/	real32 float_4ac;
	/*4b0,4*/	real32 MsgPanel_Float20;
	/*4b4,4*/	real32 MsgPanel_Float42;
	/*4b8,4*/	real32 float_4b8;
	/*4bc,10*/	Area2F MsgPanel_Rect2;
	/*4cc,8*/	Point2I TextImagePosition;
	/*4d4,4*/	Text_GlobFlags TextPanelFlags; // (0x1: ?, 0x4: ?)
	/*4d8,4*/	real32 TextPauseTime;
	/*4dc*/
};
assert_sizeof(Text_Globs, 0x4dc);

struct TextWindow // [Gods98/TextWindow.c|struct:0x830] Probably a text rendering area (official: TextWindow)
{
	/*000,4*/	Font* font;
	/*004,10*/	Area2F windowSize;
	/*014,4*/	void* windowBuffer;
	/*018,400*/	char secondBuffer[1024];
	/*418,4*/	uint32 bufferSize;
	/*41c,4*/	uint32 bufferEnd;
	/*420,400*/	uint32 lines[256]; // list of line numbers by char offset?
	/*820,4*/	uint32 linesCount;
	/*824,4*/	sint32 linesCapacity;
	/*828,4*/	real32 displayDelay;
	/*82c,4*/	uint32 flags;
	/*830*/
};
assert_sizeof(TextWindow, 0x830);

struct ToolStats // [LegoRR/Stats.c|struct:0x10]
{
	/*00,c*/	AITask_Type taskTypes[3]; // Up to 3 AITaskTypes can be associated with a tool
	/*0c,4*/	uint32 taskCount;
	/*10*/
};
assert_sizeof(ToolStats, 0x10);

struct ToolTip // [LegoRR/ToolTip.c|struct:0x27c]
{
	/*000,4*/	real32 timer;
	/*004,200*/	char textBuffer[512];
	/*204,4*/	uint32 textWidth;
	/*208,4*/	uint32 textLineCount;
	/*20c,50*/	Image* iconList[20];
	/*25c,4*/	uint32 iconCount;
	/*260,4*/	sint32 iconsY;
	/*264,4*/	sint32 iconsHeight;
	/*268,4*/	sint32 iconsX;
	/*26c,4*/	sint32 iconsWidth;
	/*270,4*/	Image* image; // Supplied with SetText prefixed with an at sign.
	/*274,4*/	SFX_ID sfxType;
	/*278,4*/	ToolTipFlags flags; // (flag 0x8 IMAGE is not for "iconList")
	/*27c*/
};
assert_sizeof(ToolTip, 0x27c);

struct ToolTip_Globs // [LegoRR/ToolTip.c|struct:0x61c4|tags:GLOBS]
{
	/*0000,4*/	Font* font; // (init only)
	/*0004,4*/	uint32 fontHeight; // (init only)
	/*0008,4*/	uint32 borderThickness; // (init only)
	/*000c,4*/	uint32 paddingThickness; // (init only)
	/*0010,4*/	uint32 appWidth; // (init only) Likely the bounds where tooltips are allowed to display.
	/*0014,4*/	uint32 appHeight; // (init only)
	/*0018,4*/	sint32 offsetY; // (init only) Y offset from cursor?
	/*001c,4*/	real32 hoverTime; // Duration before showing tooltip  (init only)
	/*0020,24*/	real32 rgbFloats[9]; // [r:g:b(3)][norm:hi:lo(3)]  (init only)
	/*0044,9c*/	char* toolTipName[39]; // (init only)
	/*00e0,60e4*/	ToolTip toolTips[39];
	/*61c4*/
};
assert_sizeof(ToolTip_Globs, 0x61c4);

struct Upgrade_PartInfo // [LegoRR/Upgrade.c|struct:0x14]
{
	/*00,4*/	uint32 level; // (ae: key Level%i%i%i%i)
	/*04,4*/	uint32 nullFrameNo; // (ae: value[1])
	/*08,4*/	char* nullObjectName; // (ae: value[0])
	/*0c,4*/	char* weaponName; // (ae: value[2], optional)
	/*10,4*/	Upgrade_PartModel* upgradeData;
	/*14*/
};
assert_sizeof(Upgrade_PartInfo, 0x14);

struct Upgrade_PartModel // [LegoRR/Upgrade.c|struct:0x10]
{
	/*00,4*/	LegoObject_ID objID;
	/*04,4*/	Container* cont; // (LWO|ACT|MESH, true)
	/*08,4*/	LegoObject* nextObject;
	/*0c,4*/	Upgrade_PartInfo* partInfo; // (not too sure about this type match)
	/*10*/
};
assert_sizeof(Upgrade_PartModel, 0x10);

struct UpgradesModel // [LegoRR/Upgrade.c|struct:0x14]
{
	/*00,4*/	Upgrade_PartInfo* parts; // always ObjectUpgradePartData[200]
	/*04,4*/	uint32 partCount;
	/*08,4*/	uint32 currentLevel;
	/*0c,4*/	LegoObject_UpgradeFlags levelFlags; // [carry][scan][speed][drill]
	/*10,4*/	LegoObject* firstObject;
	/*14*/
};
assert_sizeof(UpgradesModel, 0x14);

struct Vector3F // [common.c|struct:0xc]
{
	/*0,4*/	real32 x;
	/*4,4*/	real32 y;
	/*8,4*/	real32 z;
	/*c*/
};
assert_sizeof(Vector3F, 0xc);

struct Vector4F // [common.c|struct:0x10] D3DRMVector4D
{
	/*00,4*/	real32 x;
	/*04,4*/	real32 y;
	/*08,4*/	real32 z;
	/*0c,4*/	real32 w;
	/*10*/
};
assert_sizeof(Vector4F, 0x10);

struct VehicleModel // [LegoRR/Vehicle.c|struct:0x1ec]
{
	/*000,4*/	LegoObject_ID objID;
	/*004,4*/	char* wheelNullName; // (ae: WheelNullName)
	/*008,4*/	Container* contAct1; // (ACT, true)
	/*00c,4*/	Container* contAct2; // (ACT, true) Optional second ae file (seen for Grannit Grinder legs) This container has priority for finding null frames
	/*010,18*/	Container* contWheels[6]; // (ae:WheelMesh, LWO, false) Table for wheel nulls that are assigned a position calculated by wheelRefNulls
	/*028,18*/	Container* wheelNulls[6]; // Root wheel nulls that are used to calculate terrain-relative positioning
	/*040,4*/	uint32 wheelNullFrames;
	/*044,18*/	undefined reserved1[24];
	/*05c,c*/	Vector3F wheelLastUp; // Last up orientation of vehicle with wheels.
	/*068,4*/	real32 wheelRadius; // (ae: WheelRadius)
	/*06c,48*/	Vector3F wheelLastPositions[6]; // Last position of wheelNulls, used to calculate wheel turning.
	/*0b4,4*/	char* drillNullName; // (ae: DrillNullName)
	/*0b8,4*/	char* depositNullName; // (ae: DepositNullName)
	/*0bc,4*/	char* fireNullName; // (ae: FireNullName) "fire laser"
	/*0c0,4*/	char* driverNullName; // (ae: DriverNullName)
	/*0c4,4*/	char* yPivot; // (ae: xPivot)
	/*0c8,4*/	char* xPivot; // (ae: yPivot)
	/*0cc,4*/	Container* drillNull;
	/*0d0,4*/	Container* depositNull;
	/*0d4,4*/	Container* driverNull;
	/*0d8,4*/	BoolTri cameraFlipDir; // (ae: CameraFlipDir)
	/*0dc,4*/	char* carryNullName; // (ae: CarryNullName)
	/*0e0,4*/	char* cameraNullName; // (ae: CameraNullName)
	/*0e4,1c*/	Container* carryNulls[7];
	/*100,c*/	undefined reserved2[12];
	/*10c,10*/	Container* cameraNulls[4];
	/*11c,4*/	uint32 carryNullFrames; // (ae: CarryNullFrames)
	/*120,4*/	uint32 cameraNullFrames; // (ae: CameraNullFrames)
	/*124,14*/	UpgradesModel upgrades;
	/*138,a8*/	WeaponsModel weapons;
	/*1e0,4*/	MeshLOD* polyMedium1; // (ae: MediumPoly from contAct1)
	/*1e4,4*/	MeshLOD* polyMedium2; // (ae: MediumPoly from contAct2)
	/*1e8,4*/	VehicleFlags flags; // (0x1: original that holds memory, 0x4: ?, 0x8: HoldMissing TRUE)
	/*1ec*/
};
assert_sizeof(VehicleModel, 0x1ec);

struct Vertex // [common.c|struct:0x24] Vertex3F, Extension of D3DVertex with color field
{
	/*00,c*/	Vector3F position; // Homogeneous coordinates
	/*0c,c*/	Vector3F normal; // Normal
	/*18,4*/	real32 tu; // Texture coordinates
	/*1c,4*/	real32 tv; // Texture coordinates
	/*20,4*/	uint32 colour;
	/*24*/
};
assert_sizeof(Vertex, 0x24);

struct Viewport // [Gods98/Viewports.c|struct:0x20|tags:LISTSET]
{
	/*00,4*/	real32 xoffset; // Position on viewport normalised to between 0.0 and 1.0
	/*04,4*/	real32 yoffset; // Position on viewport normalised to between 0.0 and 1.0
	/*08,4*/	real32 width; // Width and height of the viewport normalised as above
	/*0c,4*/	real32 height; // Width and height of the viewport normalised as above
	/*10,4*/	IDirect3DRMViewport2* lpVP; // Pointer to D3D(RM) viewport interface
	/*14,4*/	real32 smoothFOV; // (init: 0)
	/*18,4*/	bool32 rendering;
	/*1c,4*/	Viewport* nextFree;
	/*20*/
};
assert_sizeof(Viewport, 0x20);

struct Viewport_Globs // [Gods98/Viewports.c|struct:0x8c|tags:GLOBS]
{
	/*00,80*/	Viewport* listSet[32];
	/*80,4*/	Viewport* freeList;
	/*84,4*/	uint32 listCount;
	/*88,4*/	uint32 flags;
	/*8c*/
};
assert_sizeof(Viewport_Globs, 0x8c);

struct Wad // [Gods98/Wad.c|struct:0x24] LegoRR WAD File information
{
	/*00,4*/	char* fName; // (unused)
	/*04,4*/	bool32 active; // 1 if WAD is in-use
	/*08,4*/	HANDLE hFile;
	/*0c,4*/	HANDLE hFileMapping;
	/*10,4*/	FILE* fWad; // File handle of the wad
	/*14,4*/	char** fileNames; // Names of actual files
	/*18,4*/	char** wadNames; // Names within wad
	/*1c,4*/	WadEntry* wadEntries;
	/*20,4*/	sint32 numFiles; // number of file entries
	/*24*/
};
assert_sizeof(Wad, 0x24);

struct Wad_FileHandle // [Gods98/Wad.c|struct:0x10]
{
	/*00,4*/	void* data; // Pointer to the file data
	/*04,4*/	bool32 active; // Is this handle active already
	/*08,4*/	sint32 wadNo; // Wad file this handle uses
	/*0c,4*/	sint32 fileNo; // Index of the file in the wad structure
	/*10*/
};
assert_sizeof(Wad_FileHandle, 0x10);

struct Wad_Globs // [Gods98/Wad.c|struct:0x7ec|tags:GLOBS]
{
	/*000,4*/	DWORD computerNameLength; // (address not known)
	/*004,4*/	bool32 wadLogFileAccess; // (address not known)
	/*008,4*/	FILE* s_ErrorFile_f; // (address not known)
	/*00c,168*/	Wad wads[10]; // Wad structures
	/*174,28*/	sint32 references[10]; // Current count of references to the wad file
	/*19c,10*/	char computerName[16]; // (address not known)
	/*1ac,640*/	Wad_FileHandle fileHandles[100];
	/*7ec*/
};
assert_sizeof(Wad_Globs, 0x7ec);

struct WadEntry // [Gods98/Wad.c|struct:0x10] WAD file entry metadata contained within LegoWADFile structure
{
	/*00,4*/	Wad_EntryFlags compression; // usually 1, 2 for RNC compression
	/*04,4*/	sint32 fileLength; // Compressed packed size
	/*08,4*/	sint32 decompressedLength; // Original unpacked size (same as packedSize when uncompressed)
	/*0c,4*/	sint32 addr; // absolute file offset
	/*10*/
};
assert_sizeof(WadEntry, 0x10);

struct WADFILE // [Gods98/Files.c|struct:0xc] Used as one of the stream types for the File struct (as opposed to the C API FILE* struct)
{
	/*0,4*/	sint32 hFile; // Handle to file in the wad
	/*4,4*/	sint32 streamPos; // Position in stream of the file.  Indexes are from 0-length-1 inclusive.
	/*8,4*/	bool32 eof; // Has the file hit EOF.
	/*c*/
};
assert_sizeof(WADFILE, 0xc);

struct Water_Globs // [LegoRR/Water.c|struct:0x29ec|tags:GLOBS] Module globals for the unfinished "Water flooding" feature.
{
	/*0000,2990*/	Water_Pool poolList[10]; // Table of isolated pools (reservoirs) of water.
	/*2990,4*/	uint32 poolCount;
	/*2994,50*/	Water_PoolMergePair mergeList[10]; // Pools that need to be merged at the end of Initialise. (This can be retired by using a better flood-fill algorithm).
	/*29e4,4*/	uint32 mergeCount;
	/*29e8,4*/	real32 digDepth; // (assigned, but never used)
	/*29ec*/
};
assert_sizeof(Water_Globs, 0x29ec);

struct Water_Pool // [LegoRR/Water.c|struct:0x428]
{
	/*000,320*/	Point2F blocks[100]; // Blocks are coordinates on the map that are part of this pool.
	/*320,4*/	uint32 blockCount;
	/*324,f0*/	Water_PoolDrain drainList[10]; // Drains are sources where water can flow away into.
	/*414,4*/	uint32 drainCount;
	/*418,4*/	real32 highWaterLevel; // (init: -10000.0, or vertPos if PREDUG)
	/*41c,4*/	real32 currWaterLevel;
	/*420,4*/	Container* contMeshTrans;
	/*424,4*/	WaterFlags flags;
	/*428*/
};
assert_sizeof(Water_Pool, 0x428);

struct Water_PoolDrain // [LegoRR/Water.c|struct:0x18]
{
	/*00,4*/	uint32 blockIndex; // The index of the block in the Water_Pool that this drain is connected to.
	/*04,4*/	Direction direction; // The direction water drains in.
	/*08,4*/	real32 drainWaterLevel;
	/*0c,4*/	real32 elapsedUp_c; // elapsed count-up timer
	/*10,4*/	real32 elapsedDown_10; // elapsed count-down timer
	/*14,4*/	bool32 active; // Actively draining pool down to drainWaterLevel.
	/*18*/
};
assert_sizeof(Water_PoolDrain, 0x18);

struct Water_PoolMergePair // [LegoRR/Water.c|struct:0x8] This struct seems to be used solely for qsort ordering by pointsCount(?)
{
	/*0,4*/	Water_Pool* mainPool; // Pool to take on the extra blocks of otherPool.
	/*4,4*/	Water_Pool* removedPool; // Pool to be merged into mainPool and then erased.
	/*8*/
};
assert_sizeof(Water_PoolMergePair, 0x8);

struct Weapon_Globs // [LegoRR/Weapons.c|struct:0x1b90|tags:GLOBS]
{
	/*0000,4*/	uint32 weaponCount;
	/*0004,4*/	char** weaponNameList;
	/*0008,4*/	WeaponStats* weaponStatsList;
	/*000c,a0*/	Weapon_Lazer lazerList[10];
	/*00ac,1ae0*/	Weapon_Projectile projectileList[10];
	/*1b8c,4*/	Config* config;
	/*1b90*/
};
assert_sizeof(Weapon_Globs, 0x1b90);

struct Weapon_Lazer // [LegoRR/???|struct:0x10]
{
	/*00,4*/	Mesh* innerMesh; // Inner bright beam.
	/*04,4*/	Mesh* outerMesh; // Outer blue-ish beam glow.
	/*08,4*/	Container* cont;
	/*0c,4*/	real32 timer; // Countdown duration in frames.
	/*10*/
};
assert_sizeof(Weapon_Lazer, 0x10);

struct Weapon_Projectile // [LegoRR/Weapons.c|struct:0x2b0] Seen in a table of [10]. This is likely an extension of the Weapons module.
{
	/*000,4*/	bool32 isCurvedPath;
	/*004,25c*/	BezierCurve curve;
	/*260,4*/	real32 totalDistance; // Curved paths only.
	/*264,4*/	real32 currDistance; // Curved paths only.
	/*268,c*/	Vector3F initialPos;
	/*274,c*/	Vector3F currPos;
	/*280,c*/	Vector3F lastPos;
	/*28c,4*/	real32 speed;
	/*290,c*/	Vector3F dir;
	/*29c,4*/	undefined4 unused_29c; // assigned to 0 but unused
	/*2a0,4*/	LegoObject* shooterObject;
	/*2a4,4*/	LegoObject* projectileObject;
	/*2a8,4*/	sint32 weaponID;
	/*2ac,4*/	Weapon_KnownType knownWeapon;
	/*2b0*/
};
assert_sizeof(Weapon_Projectile, 0x2b0);

struct WeaponsModel // [LegoRR/Weapons.c|struct:0xa8]
{
	/*00,18*/	Container* fireNullPairs[3][2];
	/*18,c*/	Container* xPivotNulls[3];
	/*24,c*/	Container* yPivotNulls[3];
	/*30,4*/	real32 pivotMaxZ; // (ae: PivotMaxZ)
	/*34,4*/	real32 pivotMinZ; // (ae: PivotMinZ)
	/*38,c*/	bool32 fireNullPairFrames[3]; // (valid: [0,1])
	/*44,24*/	Vector3F fireDirections[3];
	/*68,24*/	Vector3F targetWorldPoses[3];
	/*8c,c*/	Upgrade_PartInfo* parts[3];
	/*98,c*/	real32 timers[3];
	/*a4,4*/	uint32 count;
	/*a8*/
};
assert_sizeof(WeaponsModel, 0xa8);

struct WeaponStats // [LegoRR/Weapons.c|struct:0x4b68]
{
	/*0000,4b00*/	real32 objectCoefs[20][15][16]; // (cfg: [object] l:e:v:e:l:s, inits: -1.0f)
	/*4b00,4*/	bool32 isSlowDeath; // (cfg: SlowDeath exists)
	/*4b04,4*/	real32 slowDeathInitialCoef; // (cfg: SlowDeath[0]) Initial damage multiplier.
	/*4b08,4*/	real32 slowDeathDuration; // (cfg: SlowDeath[1])
	/*4b0c,4*/	real32 rechargeTime; // (cfg: RechargeTime, default: 0.0f)
	/*4b10,4*/	real32 damage; // (cfg: DefaultDamage, default: 0.0f)
	/*4b14,4*/	real32 dischargeRate; // (cfg: DischargeRate)
	/*4b18,4*/	sint32 ammo; // (cfg: Ammo, unused?)
	/*4b1c,4*/	real32 weaponRange; // (cfg: WeaponRange, default: 150.0f)
	/*4b20,48*/	real32 wallDestroyTimes[18]; // (cfg: WallDestroyTime_[surface], defaults: 5.0f)
	/*4b68*/
};
assert_sizeof(WeaponStats, 0x4b68);


