#pragma once
//#include "functypes.h"



typedef void* addr;
typedef G98CAnimation Animation_t;
typedef uint32 ddw;
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
	Activity_Type_Invalid        = -1,
};

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
	Advisor_Anim_Invalid    = -1,
};

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
	Advisor_Type_Invalid                     = -1,
};

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
	AI_Priority_Invalid           = -1,
};

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
	AITask_Type_Invalid           = -1,
};

enum BlockOrientation : uint8 // [LegoRR/dummy.c|enum:0x1|type:byte|tags:UNFINISHED]
{
	BLOCKORIENTATION_CORNER = 2,
	BLOCKORIENTATION_OBTUSE = 3,
};

enum BoolTri : uint32 // [common.c|enum:0x4|type:uint] BoolTri, A 3-state boolean for True, False, or Error
{
	BOOL3_FALSE = 0,
	BOOL3_TRUE  = 1,
	BOOL3_ERROR = 2,
};

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
	Bubble_Type_Invalid      = -1,
};

enum Container_Combine_Type : uint32 // [Gods98/Containers.c|enum:0x4|type:uint]
{
	CONTAINER_COMBINE_REPLACE = 0,
	CONTAINER_COMBINE_BEFORE  = 1,
	CONTAINER_COMBINE_AFTER   = 2,
};

enum Container_FogType : uint32 // [Gods98/Containers.c|enum:0x4|type:uint]
{
	CONTAINER_FOG_NONE               = 0,
	CONTAINER_FOG_EXPONENTIAL        = 1,
	CONTAINER_FOG_EXPONENTIALSQUARED = 2,
	CONTAINER_FOG_LINEAR             = 3,
};

enum Container_Light : uint32 // [Gods98/Containers.c|enum:0x4|type:uint]
{
	CONTAINER_LIGHT_AMBIENT       = 0,
	CONTAINER_LIGHT_POINT         = 1,
	CONTAINER_LIGHT_SPOT          = 2,
	CONTAINER_LIGHT_DIRECTIONAL   = 3,
	CONTAINER_LIGHT_PARALLELPOINT = 4,
};

enum Container_MeshType : uint32 // [Gods98/Containers.c|enum:0x4|type:uint]
{
	CONTAINER_MESHTYPE_NORMAL         = 0,
	CONTAINER_MESHTYPE_SEPARATEMESHES = 1,
	CONTAINER_MESHTYPE_IMMEDIATE      = 2,
	CONTAINER_MESHTYPE_TRANSPARENT    = 3,
	CONTAINER_MESHTYPE_ADDITIVE       = 4,
	CONTAINER_MESHTYPE_SUBTRACTIVE    = 5,
};

enum Container_Quality : uint32 // [Gods98/Containers.c|enum:0x4|type:uint]
{
	CONTAINER_QUALITY_WIREFRAME = 0,
	CONTAINER_QUALITY_UNLITFLAT = 1,
	CONTAINER_QUALITY_FLAT      = 2,
	CONTAINER_QUALITY_GOURAUD   = 3,
};

enum Container_SearchMode : uint32 // [Gods98/Containers.c|enum:0x4|type:uint]
{
	CONTAINER_SEARCHMODE_FIRSTMATCH = 0,
	CONTAINER_SEARCHMODE_MATCHCOUNT = 1,
	CONTAINER_SEARCHMODE_NTHMATCH   = 2,
};

enum Container_Type : sint32 // [Gods98/Containers.c|enum:0x4|type:int] known to be signed int
{
	CONTAINER_NULL         = 0,
	CONTAINER_MESH         = 1,
	CONTAINER_FRAME        = 2,
	CONTAINER_ANIM         = 3,
	CONTAINER_FROMACTIVITY = 4,
	CONTAINER_LIGHT        = 5,
	CONTAINER_REFERENCE    = 6,
	CONTAINER_LWS          = 7,
	CONTAINER_LWO          = 8,
	CONTAINER_TYPECOUNT    = 9,
	CONTAINER_INVALID      = -1,
};

enum CryOreType : uint8 // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE]
{
	CRYORE_NONE           = 0,
	CRYORE_CRYSTAL_1      = 1,
	CRYORE_ORE_1          = 2,
	CRYORE_CRYSTAL_1_alt  = 3,
	CRYORE_ORE_1_alt      = 4,
	CRYORE_CRYSTAL_3      = 5,
	CRYORE_ORE_3          = 6,
	CRYORE_CRYSTAL_3_alt  = 7,
	CRYORE_ORE_3_alt      = 8,
	CRYORE_CRYSTAL_5      = 9,
	CRYORE_ORE_5          = 10,
	CRYORE_CRYSTAL_5_alt  = 11,
	CRYORE_ORE_5_alt      = 12,
	CRYORE_CRYSTAL_10     = 13,
	CRYORE_ORE_10         = 14,
	CRYORE_CRYSTAL_10_alt = 15,
	CRYORE_ORE_10_alt     = 16,
	CRYORE_CRYSTAL_25     = 17,
	CRYORE_ORE_25         = 18,
	CRYORE_CRYSTAL_25_alt = 19,
	CRYORE_ORE_25_alt     = 20,
};

enum Direction : sint32 // [common.c|enum:0x4|type:int]
{
	DIRECTION_UP     = 0,
	DIRECTION_RIGHT  = 1,
	DIRECTION_DOWN   = 2,
	DIRECTION_LEFT   = 3,
	DIRECTION__COUNT = 4,
};

enum DrawEffect : uint32 // [Gods98/Draw.c|enum:0x4|type:uint]
{
	DrawEffect_None      = 0,
	DrawEffect_XOR       = 1,
	DrawEffect_HalfTrans = 2,
};

enum ErodeType : uint8 // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE]
{
	ERODE_NONE            = 0,
	ERODE_VERYSLOW_LAVA   = 1,
	ERODE_VERYSLOW_ALWAYS = 2,
	ERODE_SLOW_LAVA       = 3,
	ERODE_SLOW_ALWAYS     = 4,
	ERODE_MEDIUM_LAVA     = 5,
	ERODE_MEDIUM_ALWAYS   = 6,
	ERODE_FAST_LAVA       = 7,
	ERODE_FAST_ALWAYS     = 8,
	ERODE_VERYFAST_LAVA   = 9,
	ERODE_VERYFAST_ALWAYS = 10,
};

enum FallinType : uint8 // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE]
{
	FALLIN_NONE            = 0,
	FALLIN_LOW             = 1,
	FALLIN_MEDIUM          = 2,
	FALLIN_HIGH            = 3,
	FALLIN_VERYHIGH        = 4,
	FALLIN_CAVEIN_LOW      = 5,
	FALLIN_CAVEIN_MEDIUM   = 6,
	FALLIN_CAVEIN_HIGH     = 7,
	FALLIN_CAVEIN_VERYHIGH = 8,
};

enum FileSys : sint32 // [Gods98/Files.c|enum:0x4|type:int] Location of a lego File stream (WAD or REAL)
{
	FileSys_Wad      = 0,
	FileSys_Standard = 1,
	FileSys_Error    = 2,
};

enum FlicDisplayMode : uint32 // [Gods98/Flic.c|enum:0x4|type:uint]
{
	FLICMODE_BYTEPERPIXEL = 0,
	FLICMODE_MODEX        = 1,
	FLICMODE_PLANAR       = 2,
	FLICMODE_TRUECOLOR    = 3,
	FLICMODE_HICOLOR      = 4,
};

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

enum GraphicsQuality : uint32 // [Gods98/Main.c|enum:0x4|type:uint]
{
	QUALITY_WIREFRAME = 0,
	QUALITY_UNLITFLAT = 1,
	QUALITY_FLAT      = 2,
	QUALITY_GOURAUD   = 3,
};

enum Image_TextureMode : uint32 // [Gods98/Images.c|enum:0x4|type:uint]
{
	IMAGE_TEXTUREMODE_NORMAL            = 0,
	IMAGE_TEXTUREMODE_SUBTRACTIVE       = 1,
	IMAGE_TEXTUREMODE_ADDITIVE          = 2,
	IMAGE_TEXTUREMODE_TRANSPARENT       = 3,
	IMAGE_TEXTUREMODE_FIXED_SUBTRACTIVE = 4,
	IMAGE_TEXTUREMODE_FIXED_ADDITIVE    = 5,
	IMAGE_TEXTUREMODE_FIXED_TRANSPARENT = 6,
	IMAGE_TEXTUREMODE_COUNT             = 7,
};

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
	Info_Type_Invalid         = -1,
};

enum Interface_MenuItem : sint32 // [LegoRR/Interface.c|enum:0x4|type:int] "Back" has no official name
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
	Interface_MenuItem_UpgardeCarryRRY       = 70,
	Interface_MenuItem_Encyclopedia          = 71,
	Interface_MenuItem_ClearSelection        = 72,
	Interface_MenuItem_Build                 = 73,
	Interface_MenuItem_Type_Count            = 74,
	Interface_MenuItem_Type_Invalid          = -1,
};

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
	Interface_Menu_Vehicle           = 10,
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
	Interface_Menu_Type_Invalid      = -1,
};

enum Keys : sint32 // [Gods98/Input.c|enum:0x4|type:int|tags:HELPER]
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

enum KeysByte : uint8 // [Gods98/Input.c|enum:0x1|type:byte]
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
	Lego_SurfaceType_Invalid       = -1,
};

enum LegoCamera_Type : sint32 // [LegoRR/LegoCamera.c|enum:0x4|type:int]
{
	LegoCamera_None       = 0,
	LegoCamera_Top        = 1,
	LegoCamera_Radar      = 2,
	LegoCamera_FP         = 3,
	LegoCamera_Type_Count = 4,
};

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

enum LegoObject_ID : sint32 // [LegoRR/dummy.c|enum:0x4|type:int|tags:HELPER]
{
	LegoObject_ID_Ore          = 0,
	LegoObject_ID_ProcessedOre = 1,
	LegoObject_ID_Ore_Count    = 2,
};

enum LegoObject_ToolType : sint32 // [LegoRR/LegoObject.c|enum:0x4|type:int] One of the few enums with extra space before max
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
	LegoObject_ToolType_Invalid    = -1,
};

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

enum LegoObject_UpgradeType : uint32 // [LegoRR/LegoObject.c|enum:0x4|type:uint]
{
	LegoObject_UpgradeType_Drill = 0,
	LegoObject_UpgradeType_Speed = 1,
	LegoObject_UpgradeType_Scan  = 2,
	LegoObject_UpgradeType_Carry = 3,
};

enum LevelStatus : sint32 // [LegoRR/Objective.c|enum:0x4|type:int] Not sure if Objective...
{
	LEVELSTATUS_INCOMPLETE      = 0,
	LEVELSTATUS_COMPLETE        = 1,
	LEVELSTATUS_FAILED          = 2,
	LEVELSTATUS_FAILED_CRYSTALS = 3,
	LEVELSTATUS_FAILED_OTHER    = 4,
};

enum LOD_PolyLevel : sint32 // [LegoRR/MeshLOD.c|enum:0x4|type:int]
{
	LOD_LowPoly    = 0,
	LOD_MediumPoly = 1,
	LOD_HighPoly   = 2,
	LOD_FPPoly     = 3,
};

enum MaterialType : uint32 // [Gods98/Mesh.c|enum:0x4|type:uint]
{
	MATERIAL_DIFFUSE  = 0,
	MATERIAL_AMBIENT  = 1,
	MATERIAL_SPECULAR = 2,
	MATERIAL_EMISSIVE = 3,
	MATERIAL_ALPHA    = 4,
	MATERIAL_POWER    = 5,
};

enum MenuItem_Type : sint32 // [LegoRR/FrontEnd.c|enum:0x4|type:int]
{
	MenuItem_Cycle        = 0,
	MenuItem_Trigger      = 1,
	MenuItem_TextInput    = 2,
	MenuItem_Slider       = 3,
	MenuItem_RealSlider   = 4,
	MenuItem_Next         = 5,
	MenuItem_LevelSelect  = 6,
	MenuItem_Type_Count   = 7,
	MenuItem_Type_Invalid = -1,
};

enum MeshType : uint32 // [Gods98/Mesh.c|enum:0x4|type:uint]
{
	MESH_TYPE_NORM            = 0,
	MESH_TYPE_POSTEFFECT      = 1,
	MESH_TYPE_LIGHTWAVEOBJECT = 2,
};

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
	Message_Type_Invalid                  = -1,
};

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
	Panel_Type_Invalid   = -1,
};

enum PanelButtonCameraControl : sint32 // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
{
	PANELBUTTON_CAMERACONTROL_ZOOMIN         = 0,
	PANELBUTTON_CAMERACONTROL_ZOOMOUT        = 1,
	PANELBUTTON_CAMERACONTROL_CYCLEBUILDINGS = 2,
	PANELBUTTON_CAMERACONTROL_ROTATE         = 3,
	PANELBUTTON_CAMERACONTROL__COUNT         = 4,
	PANELBUTTON_CAMERACONTROL__INVALID       = -1,
};

enum PanelButtonCrystalSideBar : sint32 // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
{
	PANELBUTTON_CRYSTALSIDEBAR_ORE      = 0,
	PANELBUTTON_CRYSTALSIDEBAR_CRYSTALS = 1,
	PANELBUTTON_CRYSTALSIDEBAR__COUNT   = 2,
	PANELBUTTON_CRYSTALSIDEBAR__INVALID = -1,
};

enum PanelButtonEncyclopedia : sint32 // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
{
	PANELBUTTON_ENCYCLOPEDIA_CLOSE    = 0,
	PANELBUTTON_ENCYCLOPEDIA__COUNT   = 1,
	PANELBUTTON_ENCYCLOPEDIA__INVALID = -1,
};

enum PanelButtonInfoDock : sint32 // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
{
	PANELBUTTON_INFODOCK_GOTO     = 0,
	PANELBUTTON_INFODOCK_CLOSE    = 1,
	PANELBUTTON_INFODOCK__COUNT   = 2,
	PANELBUTTON_INFODOCK__INVALID = -1,
};

enum PanelButtonInformation : sint32 // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
{
	PANELBUTTON_INFORMATION_TOGGLE   = 0,
	PANELBUTTON_INFORMATION_FUNCTION = 1,
	PANELBUTTON_INFORMATION__COUNT   = 2,
	PANELBUTTON_INFORMATION__INVALID = -1,
};

enum PanelButtonPriorityList : sint32 // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
{
	PANELBUTTON_PRIORITYLIST_DISABLE1 = 0,
	PANELBUTTON_PRIORITYLIST_DISABLE2 = 1,
	PANELBUTTON_PRIORITYLIST_DISABLE3 = 2,
	PANELBUTTON_PRIORITYLIST_DISABLE4 = 3,
	PANELBUTTON_PRIORITYLIST_DISABLE5 = 4,
	PANELBUTTON_PRIORITYLIST_DISABLE6 = 5,
	PANELBUTTON_PRIORITYLIST_DISABLE7 = 6,
	PANELBUTTON_PRIORITYLIST_DISABLE8 = 7,
	PANELBUTTON_PRIORITYLIST_DISABLE9 = 8,
	PANELBUTTON_PRIORITYLIST_UPONE1   = 9,
	PANELBUTTON_PRIORITYLIST_UPONE2   = 10,
	PANELBUTTON_PRIORITYLIST_UPONE3   = 11,
	PANELBUTTON_PRIORITYLIST_UPONE4   = 12,
	PANELBUTTON_PRIORITYLIST_UPONE5   = 13,
	PANELBUTTON_PRIORITYLIST_UPONE6   = 14,
	PANELBUTTON_PRIORITYLIST_UPONE7   = 15,
	PANELBUTTON_PRIORITYLIST_UPONE8   = 16,
	PANELBUTTON_PRIORITYLIST_CLOSE    = 17,
	PANELBUTTON_PRIORITYLIST_RESET    = 18,
	PANELBUTTON_PRIORITYLIST__COUNT   = 19,
	PANELBUTTON_PRIORITYLIST__INVALID = -1,
};

enum PanelButtonRadar : sint32 // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
{
	PANELBUTTON_RADAR_TOGGLE           = 0,
	PANELBUTTON_RADAR_TAGGEDOBJECTVIEW = 1,
	PANELBUTTON_RADAR_ZOOMIN           = 2,
	PANELBUTTON_RADAR_ZOOMOUT          = 3,
	PANELBUTTON_RADAR_MAPVIEW          = 4,
	PANELBUTTON_RADAR__COUNT           = 5,
	PANELBUTTON_RADAR__INVALID         = -1,
};

enum PanelButtonTopPanel : sint32 // [LegoRR/Panels.c|enum:0x4|type:int|tags:PANELBUTTON]
{
	PANELBUTTON_TOPPANEL_OPTIONS    = 0,
	PANELBUTTON_TOPPANEL_PRIORITIES = 1,
	PANELBUTTON_TOPPANEL_CALLTOARMS = 2,
	PANELBUTTON_TOPPANEL__COUNT     = 3,
	PANELBUTTON_TOPPANEL__INVALID   = -1,
};

enum PanelButtonType : sint32 // [LegoRR/Panels.c|enum:0x4|type:int|tags:REALENUM]
{
	PANELBUTTON__COUNT = 24,
};

enum PathType : uint8 // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE]
{
	PATH_NONE      = 0,
	PATH_RUBBLE    = 1,
	PATH_POWERPATH = 2,
};

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
	Pointer_Type_Invalid             = -1,
};

enum PredugType : uint8 // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE]
{
	PREDUG_WALL             = 0,
	PREDUG_EXPOSED          = 1,
	PREDUG_HIDDEN           = 2,
	PREDUG_EXPOSED_SLUGHOLE = 3,
	PREDUG_HIDDEN_SLUGHOLE  = 4,
};

enum ProgrammerMode : uint32 // [LegoRR/Lego.c|enum:0x4|type:uint] Programmer mode enum
{
	PROGRAMMER_OFF     = 0,
	PROGRAMMER_MODE_1  = 1,
	PROGRAMMER_MODE_2  = 2,
	PROGRAMMER_MODE_3  = 3,
	PROGRAMMER_MODE_10 = 10,
	PROGRAMMER_MODE_11 = 11,
};

enum RegistryType : uint32 // [Gods98/Registry.c|enum:0x4|type:uint] Supported registry information types
{
	REGISTRY_STRING_VALUE = 0,
	REGISTRY_DWORD_VALUE  = 1,
};

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

enum RewardScrollLabelMode : uint32 // [LegoRR/Rewards.c|enum:0x4|type:uint] Inclusive mode, None does nothing, WINDOW also performs IMAGE and TEXT, IMAGE also performs TEXT, TEXT does only that
{
	REWARDSCROLL_MODE_NONE   = 0,
	REWARDSCROLL_MODE_WINDOW = 1,
	REWARDSCROLL_MODE_IMAGE  = 2,
	REWARDSCROLL_MODE_TEXT   = 3,
};

enum RewardUIState : uint32 // [LegoRR/Rewards.c|enum:0x4|type:uint]
{
	REWARDSTATE_0      = 0,
	REWARDSTATE_1      = 1,
	REWARDSTATE_2      = 2,
	REWARDSTATE_3      = 3,
	REWARDSTATE__COUNT = 4,
};

enum RNCCompression : uint8 // [Gods98/Compress.c|enum:0x1|type:byte]
{
	RNC_COMPRESS_STORE = 0,
	RNC_COMPRESS_BEST  = 1,
	RNC_COMPRESS_FAST  = 2,
};

enum RNCError : sint16 // [Gods98/Compress.c|enum:0x2|type:short]
{
	RNC_OK                 = 0,
	RNC_INVALIDCOMPRESSION = 65534,
	RNC_INVALIDFILE        = 65535,
};

enum RockFallType : sint32 // [LegoRR/Effects.c|enum:0x4|type:int]
{
	ROCKFALL_3SIDES        = 0,
	ROCKFALL_OUTSIDECORNER = 1,
	ROCKFALL_VTUNNEL       = 2,
};

enum RouteAction : uint8 // [LegoRR/Text.c|enum:0x1|type:byte]
{
	ROUTE_ACTION_UNK_1       = 1,
	ROUTE_ACTION_REINFORCE   = 2,
	ROUTE_ACTION_BOULDER     = 3,
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

enum ScreenMenuType : sint32 // [LegoRR/FrontEnd.c|enum:0x4|type:int] Types of menus only shown out-of-game
{
	MENU_SCREEN_TITLE       = 0,
	MENU_SCREEN_MISSIONS    = 1,
	MENU_SCREEN_TRAINING    = 2,
	MENU_SCREEN_LOAD_unused = 3,
	MENU_SCREEN_SAVE        = 4,
};

enum SFX_Type : sint32 // [LegoRR/SFX.c|enum:0x4|type:int] SFXType is different from actual Sample indexes, these are hardcoded values that can easily be looked up by ID
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
	SFX_Type_Invalid            = -1,
};

enum Sound3D_Play : uint32 // [Gods98/3DSound.c|enum:0x4|type:uint]
{
	SOUND3D_PLAY_ONFRAME = 0,
	SOUND3D_PLAY_ONPOS   = 1,
	SOUND3D_PLAY_NORMAL  = 2,
};

enum SoundMode : uint32 // [Gods98/Sound.c|enum:0x4|type:uint]
{
	SOUND_ONCE  = 0,
	SOUND_LOOP  = 1,
	SOUND_MULTI = 2,
};

enum SurfaceTexture : uint8 // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE,COORDNIBBLE]
{
	TEXTURE_GROUND              = 0,
	TEXTURE_WALL_F_SOIL         = 1,
	TEXTURE_WALL_F_LOOSE        = 2,
	TEXTURE_WALL_F_MEDIUM       = 3,
	TEXTURE_WALL_F_HARD         = 4,
	TEXTURE_WALL_F_IMMOVABLE    = 5,
	TEXTURE_ERODE_LOW           = 6,
	TEXTURE_07                  = 7,
	TEXTURE_RUBBLE_FULL         = 16,
	TEXTURE_RUBBLE_HIGH         = 17,
	TEXTURE_RUBBLE_MEDIUM       = 18,
	TEXTURE_RUBBLE_LOW          = 19,
	TEXTURE_ERODE_MEDIUM        = 22,
	TEXTURE_WALL_F_CRYSTALSEAM  = 32,
	TEXTURE_WALL_R_SOIL         = 33,
	TEXTURE_WALL_R_LOOSE        = 34,
	TEXTURE_WALL_R_MEDIUM       = 35,
	TEXTURE_WALL_R_HARD         = 36,
	TEXTURE_WALL_R_IMMOVABLE    = 37,
	TEXTURE_ERODE_HIGH          = 38,
	TEXTURE_SLUGHOLE            = 48,
	TEXTURE_WALL_C_SOIL         = 49,
	TEXTURE_WALL_C_LOOSE        = 50,
	TEXTURE_WALL_C_MEDIUM       = 51,
	TEXTURE_WALL_C_HARD         = 52,
	TEXTURE_WALL_C_IMMOVABLE    = 53,
	TEXTURE_ERODE_FULL          = 54,
	TEXTURE_WALL_F_ORESEAM      = 64,
	TEXTURE_WATER               = 69,
	TEXTURE_LAVA                = 70,
	TEXTURE_LAVA_NOTHOT         = 71,
	TEXTURE_WALL_O_SOIL         = 81,
	TEXTURE_WALL_O_LOOSE        = 82,
	TEXTURE_WALL_O_MEDIUM       = 83,
	TEXTURE_WALL_O_HARD         = 84,
	TEXTURE_WALL_O_IMMOVABLE    = 85,
	TEXTURE_PATH_4              = 96,
	TEXTURE_PATH_BUILD          = 97,
	TEXTURE_PATH_2              = 98,
	TEXTURE_PATH_C              = 99,
	TEXTURE_PATH_3              = 100,
	TEXTURE_PATH_1              = 101,
	TEXTURE_FOUNDATION_POWERED  = 102,
	TEXTURE_WALL_F_RECHARGESEAM = 103,
	TEXTURE_TUNNEL              = 112,
	TEXTURE_PATH_4_POWERED      = 113,
	TEXTURE_PATH_2_POWERED      = 114,
	TEXTURE_PATH_C_POWERED      = 115,
	TEXTURE_PATH_3_POWERED      = 116,
	TEXTURE_PATH_1_POWERED      = 117,
	TEXTURE_FOUNDATION          = 118,
	TEXTURE_WALL_GAP            = 119,
	TEXTURE__INVALID            = 255,
};

enum TerrainType : uint8 // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE]
{
	TERRAIN_TUNNEL       = 0,
	TERRAIN_IMMOVABLE    = 1,
	TERRAIN_HARD         = 2,
	TERRAIN_MEDIUM       = 3,
	TERRAIN_LOOSE        = 4,
	TERRAIN_SOIL         = 5,
	TERRAIN_LAVA         = 6,
	TERRAIN_WATER_unused = 7,
	TERRAIN_ORESEAM      = 8,
	TERRAIN_LAKE         = 9,
	TERRAIN_CRYSTALSEAM  = 10,
	TERRAIN_RECHARGESEAM = 11,
	TERRAIN_RUBBLE       = 12,
	TERRAIN_REINFORCED   = 13,
	TERRAIN_PATH         = 14,
	TERRAIN_SLUGHOLE     = 15,
	TERRAIN_UNDISCOVERED = 16,
	TERRAIN_CAVERN       = 17,
};

enum Text_Type : sint32 // [LegoRR/Text.c|enum:0x4|type:int]
{
	TEXT_WALK                = 0,
	TEXT_DRILL               = 1,
	TEXT_NODRILL             = 2,
	TEXT_CANTDRILL           = 3,
	TEXT_REINFORCE           = 4,
	TEXT_NOREINFORCE         = 5,
	TEXT_CANTREINFORCE       = 6,
	TEXT_PICKUPCRYSTAL       = 7,
	TEXT_ENCYCLOPEDIA        = 8,
	TEXT_RADARHELP           = 9,
	TEXT_BUILDHELP           = 10,
	TEXT_SELECTIONHELP       = 11,
	TEXT_DRIVE               = 12,
	TEXT_CANTDRIVE           = 13,
	TEXT_MAKETELEPORTER      = 14,
	TEXT_CANNOTPLACEBUILDING = 15,
	TEXT_CRYSTALOREDISABLED  = 16,
	TEXT_CRYSTALFOUND        = 17,
	TEXT_CAVERNDISCOVERED    = 18,
	TEXT_OREFOUND            = 19,
	TEXT_AIRSUPPLYLOW        = 20,
	TEXT_AIRSUPPLYRUNNINGOUT = 21,
	TEXT_SPACETOCONTINUE     = 22,
	TEXT_GAMECOMPLETE        = 23,
	TEXT_MANTRAINED          = 24,
	TEXT_UNITUPGRADED        = 25,
	TEXT__COUNT              = 26,
	TEXT__INVALID            = -1,
};

enum TextureType : sint32 // [LegoRR/dummy.c|enum:0x4|type:int|tags:HELPER,UNUSED]
{
	TEXTURES_ROCK     = 0,
	TEXTURES_LAVA     = 1,
	TEXTURES_ICE      = 2,
	TEXTURES__INVALID = -1,
};

enum ToolTip_Type : sint32 // [LegoRR/ToolTip.c|enum:0x4|type:int]
{
	ToolTip_None                       = 0,
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

enum ViewMode : sint32 // [LegoRR/Lego.c|enum:0x4|type:int]
{
	ViewMode_FP  = 0,
	ViewMode_Top = 1,
};

enum WallHighlightByte : uint8 // [LegoRR/Lego.c|enum:0x1|type:byte] Byte-sized WallHighlightType (white, gray, red, green, blue, dark-yellow)
{
	WALLHIGHLIGHTBYTE_NONE      = 0,
	WALLHIGHLIGHTBYTE_DIG       = 1,
	WALLHIGHLIGHTBYTE_DYNAMITE  = 2,
	WALLHIGHLIGHTBYTE_REINFORCE = 3,
	WALLHIGHLIGHTBYTE_SELECTED  = 4,
	WALLHIGHLIGHTBYTE_TUTORIAL  = 5,
};

enum WallHighlightType : sint32 // [LegoRR/Lego.c|enum:0x4|type:int|tags:BIGENUMALIAS] (white, gray, red, green, blue, dark-yellow)
{
	WALLHIGHLIGHT_NONE      = 0,
	WALLHIGHLIGHT_DIG       = 1,
	WALLHIGHLIGHT_DYNAMITE  = 2,
	WALLHIGHLIGHT_REINFORCE = 3,
	WALLHIGHLIGHT_SELECTED  = 4,
	WALLHIGHLIGHT_TUTORIAL  = 5,
};

enum WeaponKnownType : sint32 // [LegoRR/Weapons.c|enum:0x4|type:int|tags:UNKNOWN] This is not the same as WeponTypes defined in Lego.cfg, these are fixed ID's that are then looked up by value
{
	WEAPONKNOWN_UNK_0   = 0,
	WEAPONKNOWN_LAZER_1 = 1,
	WEAPONKNOWN_PUSHER  = 2,
	WEAPONKNOWN_FREEZER = 3,
	WEAPONKNOWN_LAZER_4 = 4,
};



enum AdvisorPositionFlags : uint32 // [LegoRR/Advisor.c|flags:0x4|type:uint]
{
	ADVISORPOS_NONE    = 0,
	ADVISORPOS_NOPANEL = 0x10000,
	ADVISORPOS_DEFAULT = 0x20000,
	ADVISORPOS_HASTEXT = 0x40000,
};
DEFINE_ENUM_FLAG_OPERATORS(AdvisorPositionFlags);

enum AdvisorStateFlags : uint32 // [LegoRR/Advisor.c|flags:0x4|type:uint]
{
	ADVISORSTATE_NONE  = 0,
	ADVISORSTATE_UNK_1 = 0x1,
	ADVISORSTATE_UNK_2 = 0x2,
};
DEFINE_ENUM_FLAG_OPERATORS(AdvisorStateFlags);

enum AITaskFlags : uint32 // [LegoRR/AITask.c|flags:0x4|type:uint]
{
	AITASK_FLAG_NONE = 0,
};
DEFINE_ENUM_FLAG_OPERATORS(AITaskFlags);

enum BlockFenceGrid_Flags : uint32 // [LegoRR/Detail.c|flags:0x4|type:uint]
{
	FENCEGRID_FLAG_NONE        = 0,
	FENCEGRID_DIRECTION_FLAG_1 = 0x1,
	FENCEGRID_DIRECTION_FLAG_2 = 0x2,
	FENCEGRID_DIRECTION_FLAG_4 = 0x4,
	FENCEGRID_DIRECTION_FLAG_8 = 0x8,
	FENCEGRID_DIRECTION_MASK   = 0xf,
	FENCEGRID_FLAG_UNK_100     = 0x100,
};
DEFINE_ENUM_FLAG_OPERATORS(BlockFenceGrid_Flags);

enum BlockFlags1 : uint32 // [LegoRR/Lego.c|flags:0x4|type:uint]
{
	BLOCK1_NONE                    = 0,
	BLOCK1_RUBBLE_LOW              = 0x1,
	BLOCK1_RUBBLE_MEDIUM           = 0x2,
	BLOCK1_RUBBLE_FULL             = 0x3,
	BLOCK1_SURVEYED                = 0x4,
	BLOCK1_FLOOR                   = 0x8,
	BLOCK1_WALL                    = 0x10,
	BLOCK1_REINFORCED              = 0x20,
	BLOCK1_CORNEROBTUSE            = 0x40,
	BLOCK1_CORNERINNER             = 0x80,
	BLOCK1_UNK_100                 = 0x100,
	BLOCK1_UNK_200                 = 0x200,
	BLOCK1_BUILDINGSOLID           = 0x400,
	BLOCK1_UNK_800                 = 0x800,
	BLOCK1_UNK_1000                = 0x1000,
	BLOCK1_GAP                     = 0x2000,
	BLOCK1_UNK_4000                = 0x4000,
	BLOCK1_BUILDINGPATH            = 0x8000,
	BLOCK1_HIDDEN                  = 0x20000,
	BLOCK1_DESTROYEDCONNECTION_UNK = 0x40000,
	BLOCK1_UNK_80000               = 0x80000,
	BLOCK1_FOUNDATION              = 0x100000,
	BLOCK1_CLEARED_UNK             = 0x200000,
	BLOCK1_UNK_400000              = 0x400000,
	BLOCK1_UNK_800000              = 0x800000,
	BLOCK1_UNK_1000000             = 0x1000000,
	BLOCK1_EXPOSED                 = 0x4000000,
	BLOCK1_BUSY                    = 0x8000000,
	BLOCK1_UNK_10000000            = 0x10000000,
	BLOCK1_PATH                    = 0x20000000,
	BLOCK1_UNK_40000000            = 0x40000000,
	BLOCK1_UNK_80000000            = 0x80000000,
};
DEFINE_ENUM_FLAG_OPERATORS(BlockFlags1);

enum BlockFlags2 : uint32 // [LegoRR/Lego.c|flags:0x4|type:uint]
{
	BLOCK2_NONE             = 0,
	BLOCK2_GENERATEPOWER    = 0x1,
	BLOCK2_UNK_2            = 0x2,
	BLOCK2_TOOLSTORE_UNK    = 0x4,
	BLOCK2_FENCEREQUEST     = 0x8,
	BLOCK2_UNK_10           = 0x10,
	BLOCK2_SLUGHOLE_EXPOSED = 0x20,
	BLOCK2_EMERGE_POINT     = 0x40,
	BLOCK2_EMERGE_TRIGGER   = 0x80,
	BLOCK2_POWERED          = 0x100,
	BLOCK2_SLUGHOLE_HIDDEN  = 0x200,
	BLOCK2_UNK_400          = 0x400,
};
DEFINE_ENUM_FLAG_OPERATORS(BlockFlags2);

enum BlockSpiderWebFlags : uint32 // [LegoRR/SpiderWeb.c|flags:0x4|type:uint]
{
	BLOCKWEB_NONE   = 0,
	BLOCKWEB_ACTIVE = 0x100,
};
DEFINE_ENUM_FLAG_OPERATORS(BlockSpiderWebFlags);

enum BuildingFlags : uint32 // [LegoRR/Building.c|flags:0x4|type:uint]
{
	BUILDING_FLAG_NONE            = 0,
	BUILDING_FLAG_SOURCE          = 0x1,
	BUILDING_FLAG_POWERLEVELSCENE = 0x2,
};
DEFINE_ENUM_FLAG_OPERATORS(BuildingFlags);

enum CameraFlags : uint32 // [LegoRR/LegoCamera.c|flags:0x4|type:uint]
{
	CAMERA_FLAG_NONE          = 0,
	CAMERA_FLAG_TILTRANGE     = 0x1,
	CAMERA_FLAG_ROTATIONRANGE = 0x2,
	CAMERA_FLAG_ZOOMRANGE     = 0x4,
	CAMERA_FLAG_FREEMOVEMENT  = 0x8,
	CAMERA_FLAG_FPSETUP       = 0x10,
};
DEFINE_ENUM_FLAG_OPERATORS(CameraFlags);

enum Config_GlobFlags : uint32 // [Gods98/Memory.c|flags:0x4|type:uint]
{
	CONFIG_GLOB_FLAG_NONE          = 0,
	CONFIG_GLOB_FLAG_INITIALISED   = 0x1,
	CONFIG_GLOB_FLAG_LOADINGCONFIG = 0x2,
};
DEFINE_ENUM_FLAG_OPERATORS(Config_GlobFlags);

enum Container_GlobFlags : uint32 // [Gods98/Containers.c|flags:0x4|type:uint] All flags used by the ResourceManager struct.
{
	CONTAINER_FLAG_NONE           = 0,
	CONTAINER_FLAG_INITIALISED    = 0x1,
	CONTAINER_FLAG_TRIGGERENABLED = 0x40,
};
DEFINE_ENUM_FLAG_OPERATORS(Container_GlobFlags);

enum Container_TextureFlags : uint32 // [Gods98/Containers.c|flags:0x4|type:uint]
{
	CONTAINER_TEXTURE_NONE   = 0,
	CONTAINER_TEXTURE_NOLOAD = 0x1,
};
DEFINE_ENUM_FLAG_OPERATORS(Container_TextureFlags);

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
DEFINE_ENUM_FLAG_OPERATORS(ContainerFlags);

enum CreatureFlags : uint32 // [LegoRR/Creature.c|flags:0x4|type:uint]
{
	CREATURE_FLAG_NONE   = 0,
	CREATURE_FLAG_SOURCE = 0x1,
};
DEFINE_ENUM_FLAG_OPERATORS(CreatureFlags);

enum DependencyFlags : uint32 // [LegoRR/Dependencies.c|flags:0x4|type:uint]
{
	DEPENDENCY_FLAG_NONE        = 0,
	DEPENDENCY_FLAG_HITONCESTAY = 0x1,
	DEPENDENCY_FLAG_UNK_2       = 0x2,
	DEPENDENCY_FLAG_UNK_4       = 0x4,
	DEPENDENCY_FLAG_UNK_8       = 0x8,
	DEPENDENCY_FLAG_UNK_100     = 0x100,
};
DEFINE_ENUM_FLAG_OPERATORS(DependencyFlags);

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
DEFINE_ENUM_FLAG_OPERATORS(Detail_TransformFlags);

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
DEFINE_ENUM_FLAG_OPERATORS(DirectionFlags);

enum Draw_GlobFlags : uint32 // [Gods98/Draw.c|flags:0x4|type:uint]
{
	DRAW_GLOB_FLAG_NONE        = 0,
	DRAW_GLOB_FLAG_INITIALISED = 0x1,
};
DEFINE_ENUM_FLAG_OPERATORS(Draw_GlobFlags);

enum FlicUserFlags : uint32 // [Gods98/Flic.c|flags:0x4|type:uint]
{
	FLICDISK      = 0,
	FLICMEMORY    = 0x1,
	FLICLOOPINGON = 0x2,
	FLICCATCHUPON = 0x4,
	FLICSOUNDOFF  = 0x8,
};
DEFINE_ENUM_FLAG_OPERATORS(FlicUserFlags);

enum FontFlags : uint32 // [Gods98/Fonts.c|flags:0x4|type:uint]
{
	FONT_FLAG_NONE          = 0,
	FONT_FLAG_INITIALISED   = 0x1,
	FONT_FLAG_WINDOWSET     = 0x2,
	FONT_FLAG_WINDOWWRAPPED = 0x4,
};
DEFINE_ENUM_FLAG_OPERATORS(FontFlags);

enum Front_RockWipeFlags : uint8 // [LegoRR/Front.c|flags:0x1|type:byte]
{
	ROCKWIPE_FLAG_NONE  = 0,
	ROCKWIPE_FLAG_UNK_1 = 0x1,
	ROCKWIPE_FLAG_UNK_2 = 0x2,
};
DEFINE_ENUM_FLAG_OPERATORS(Front_RockWipeFlags);

enum GameFlags1 : uint32 // [LegoRR/Lego.c|flags:0x4|type:uint]
{
	GAME1_NONE                  = 0,
	GAME1_RADARON               = 0x2,
	GAME1_LEVELSTART            = 0x4,
	GAME1_USEMUSIC              = 0x8,
	GAME1_USESFX                = 0x10,
	GAME1_USEDETAIL             = 0x20,
	GAME1_SHOWFPS               = 0x40,
	GAME1_SHOWMEMORY            = 0x80,
	GAME1_MULTISELECT           = 0x100,
	GAME1_UNK_200               = 0x200,
	GAME1_DDRAWCLEAR            = 0x400,
	GAME1_RENDERPANELS          = 0x800,
	GAME1_RADAR_MAPVIEW         = 0x1000,
	GAME1_RADAR_TRACKOBJECTVIEW = 0x2000,
	GAME1_UNK_4000              = 0x4000,
	GAME1_FOGCOLOURRGB          = 0x8000,
	GAME1_HIGHFOGCOLOURRGB      = 0x10000,
	GAME1_UNK_20000             = 0x20000,
	GAME1_UNK_40000             = 0x40000,
	GAME1_DYNAMICPM             = 0x80000,
	GAME1_CAMERADISABLED        = 0x100000,
	GAME1_UNK_200000            = 0x200000,
	GAME1_ONLYBUILDONPATHS      = 0x400000,
	GAME1_ALWAYSROCKFALL        = 0x800000,
	GAME1_DEBUG_NONERPS         = 0x1000000,
	GAME1_PAUSED                = 0x2000000,
	GAME1_STREAMNERPSSPEACH     = 0x4000000,
	GAME1_UNK_8000000           = 0x8000000,
	GAME1_LASERTRACKER          = 0x10000000,
	GAME1_UNK_20000000          = 0x20000000,
	GAME1_DEBUG_NOCLIP_FPS      = 0x40000000,
	GAME1_UNK_80000000          = 0x80000000,
};
DEFINE_ENUM_FLAG_OPERATORS(GameFlags1);

enum GameFlags2 : uint32 // [LegoRR/Lego.c|flags:0x4|type:uint]
{
	GAME2_NONE                 = 0,
	GAME2_CALLTOARMS           = 0x1,
	GAME2_UNK_2                = 0x2,
	GAME2_ATTACKDEFER          = 0x4,
	GAME2_SHOWDEBUGTOOLTIPS    = 0x8,
	GAME2_ALLOWDEBUGKEYS       = 0x10,
	GAME2_ALLOWEDITMODE        = 0x20,
	GAME2_UNK_40               = 0x40,
	GAME2_UNK_80               = 0x80,
	GAME2_INOPTIONSMENU        = 0x100,
	GAME2_CAMERAMOVING         = 0x200,
	GAME2_MOUSE_INSIDEGAMEVIEW = 0x400,
	GAME2_MUSICON              = 0x800,
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
DEFINE_ENUM_FLAG_OPERATORS(GameFlags2);

enum GameFlags3 : uint32 // [LegoRR/Lego.c|flags:0x4|type:uint]
{
	GAME3_NONE          = 0,
	GAME3_UNK_1         = 0x1,
	GAME3_UNK_2         = 0x2,
	GAME3_UNK_4         = 0x4,
	GAME3_PICKUPOBJECT  = 0x8,
	GAME3_LOADVEHICLE   = 0x10,
	GAME3_UNK_20        = 0x20,
	GAME3_UNK_40        = 0x40,
	GAME3_PLACEBUILDING = 0x80,
};
DEFINE_ENUM_FLAG_OPERATORS(GameFlags3);

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
DEFINE_ENUM_FLAG_OPERATORS(Graphics_DeviceFlags);

enum Graphics_DriverFlags : uint32 // [Gods98/DirectDraw.c|flags:0x4|type:uint] Valid flag is actually shared: DIRECTDRAW_FLAG_VALID
{
	GRAPHICS_DRIVER_FLAG_NONE     = 0,
	GRAPHICS_DRIVER_FLAG_VALID    = 0x1,
	GRAPHICS_DRIVER_FLAG_PRIMARY  = 0x10,
	GRAPHICS_DRIVER_FLAG_WINDOWOK = 0x20,
};
DEFINE_ENUM_FLAG_OPERATORS(Graphics_DriverFlags);

enum Graphics_ModeFlags : uint32 // [Gods98/DirectDraw.c|flags:0x4|type:uint] Valid flag is actually shared: DIRECTDRAW_FLAG_VALID
{
	GRAPHICS_MODE_FLAG_NONE  = 0,
	GRAPHICS_MODE_FLAG_VALID = 0x1,
};
DEFINE_ENUM_FLAG_OPERATORS(Graphics_ModeFlags);

enum HelpWindowFlags : uint32 // [LegoRR/HelpWindow.c|flags:0x4|type:uint]
{
	HELPWINDOW_NONE    = 0,
	HELPWINDOW_UNK_1   = 0x1,
	HELPWINDOW_UNK_2   = 0x2,
	HELPWINDOW_UNK_4   = 0x4,
	HELPWINDOW_UNK_8   = 0x8,
	HELPWINDOW_UNK_10  = 0x10,
	HELPWINDOW_UNK_20  = 0x20,
	HELPWINDOW_ENABLED = 0x40,
};
DEFINE_ENUM_FLAG_OPERATORS(HelpWindowFlags);

enum ImageFlags : uint32 // [Gods98/Images.c|flags:0x4|type:uint]
{
	IMAGE_FLAG_NONE        = 0,
	IMAGE_FLAG_INITIALISED = 0x1,
	IMAGE_FLAG_TRANS       = 0x2,
	IMAGE_FLAG_TEXTURE     = 0x4,
};
DEFINE_ENUM_FLAG_OPERATORS(ImageFlags);

enum InfoDataFlags : uint32 // [LegoRR/Info.c|flags:0x4|type:uint]
{
	INFOTYPE_FLAG_NONE            = 0,
	INFOTYPE_FLAG_CHANGEGAMESPEED = 0x10000,
	INFOTYPE_FLAG_UNK_20000       = 0x20000,
};
DEFINE_ENUM_FLAG_OPERATORS(InfoDataFlags);

enum InfoMessageFlags : uint32 // [LegoRR/Info.c|flags:0x4|type:uint]
{
	INFO_FLAG_NONE          = 0,
	INFO_FLAG_UNK_1         = 0x1,
	INFO_FLAG_UNK_2         = 0x2,
	INFO_FLAG_UNK_4         = 0x4,
	INFO_FLAG_UNK_8         = 0x8,
	INFO_FLAG_AUTOGAMESPEED = 0x10,
};
DEFINE_ENUM_FLAG_OPERATORS(InfoMessageFlags);

enum InterfaceIconFlags : uint32 // [LegoRR/Interface.c|flags:0x4|type:uint]
{
	INTERFACE_MENUITEM_FLAG_NONE  = 0,
	INTERFACE_MENUITEM_FLAG_FLASH = 0x4,
};
DEFINE_ENUM_FLAG_OPERATORS(InterfaceIconFlags);

enum LegoObject_GlobFlags : uint32 // [LegoRR/LegoObject.c|flags:0x4|type:uint] LegoObject_GlobFlags, ReservedPool LiveObject INITFLAGS
{
	OBJECT_GLOB_FLAG_NONE        = 0,
	OBJECT_GLOB_FLAG_INITIALISED = 0x1,
	OBJECT_GLOB_FLAG_REMOVING    = 0x2,
	OBJECT_GLOB_FLAG_UNK_4       = 0x4,
	OBJECT_GLOB_FLAG_UNK_8       = 0x8,
	OBJECT_GLOB_FLAG_UPDATING    = 0x10,
	OBJECT_GLOB_FLAG_LEVELENDING = 0x20,
	OBJECT_GLOB_FLAG_CYCLEUNITS  = 0x40,
};
DEFINE_ENUM_FLAG_OPERATORS(LegoObject_GlobFlags);

enum LegoObject_UpgradeFlags : uint32 // [LegoRR/LegoObject.c|flags:0x4|type:uint]
{
	UPGRADE_FLAG_NONE  = 0,
	UPGRADE_FLAG_DRILL = 0x1,
	UPGRADE_FLAG_SPEED = 0x2,
	UPGRADE_FLAG_SCAN  = 0x4,
	UPGRADE_FLAG_CARRY = 0x8,
	UPGRADE_FLAGS_ALL  = 0xf,
};
DEFINE_ENUM_FLAG_OPERATORS(LegoObject_UpgradeFlags);

enum LightEffectsFlags : uint32 // [LegoRR/LightEffects.c|flags:0x4|type:uint] LightEffects_GlobFlags, Flags for LightEffectsManager global variable @004ebec8
{
	LIGHTEFFECTS_NONE         = 0,
	LIGHTEFFECTS_HASBLINK     = 0x1,
	LIGHTEFFECTS_HASFADE      = 0x4,
	LIGHTEFFECTS_FADING       = 0x8,
	LIGHTEFFECTS_FADE_FORWARD = 0x10,
	LIGHTEFFECTS_FADE_REVERSE = 0x20,
	LIGHTEFFECTS_HASMOVE      = 0x40,
	LIGHTEFFECTS_MOVING       = 0x80,
	LIGHTEFFECTS_DISABLED     = 0x100,
	LIGHTEFFECTS_DIMOUT       = 0x200,
	LIGHTEFFECTS_DIMIN_DONE   = 0x400,
	LIGHTEFFECTS_DIMOUT_DONE  = 0x1000,
};
DEFINE_ENUM_FLAG_OPERATORS(LightEffectsFlags);

enum LiveFlags1 : uint32 // [LegoRR/LegoObject.c|flags:0x4|type:uint]
{
	LIVEOBJ1_NONE          = 0,
	LIVEOBJ1_MOVING        = 0x1,
	LIVEOBJ1_LIFTING       = 0x2,
	LIVEOBJ1_TURNING       = 0x4,
	LIVEOBJ1_DRILLING      = 0x8,
	LIVEOBJ1_DRILLINGSTART = 0x10,
	LIVEOBJ1_REINFORCING   = 0x40,
	LIVEOBJ1_TURNRIGHT     = 0x80,
	LIVEOBJ1_UNK_100       = 0x100,
	LIVEOBJ1_UNK_200       = 0x200,
	LIVEOBJ1_CARRYING      = 0x400,
	LIVEOBJ1_UNK_800       = 0x800,
	LIVEOBJ1_UNK_1000      = 0x1000,
	LIVEOBJ1_UNK_2000      = 0x2000,
	LIVEOBJ1_UNK_4000      = 0x4000,
	LIVEOBJ1_UNK_8000      = 0x8000,
	LIVEOBJ1_UNK_10000     = 0x10000,
	LIVEOBJ1_UNK_20000     = 0x20000,
	LIVEOBJ1_CLEARING      = 0x40000,
	LIVEOBJ1_PLACING       = 0x80000,
	LIVEOBJ1_UNK_100000    = 0x100000,
	LIVEOBJ1_UNK_200000    = 0x200000,
	LIVEOBJ1_UNK_400000    = 0x400000,
	LIVEOBJ1_UNK_800000    = 0x800000,
	LIVEOBJ1_UNK_1000000   = 0x1000000,
	LIVEOBJ1_CAUGHTINWEB   = 0x2000000,
	LIVEOBJ1_SLIPPING      = 0x4000000,
	LIVEOBJ1_UNK_8000000   = 0x8000000,
	LIVEOBJ1_UNK_10000000  = 0x10000000,
	LIVEOBJ1_REST          = 0x20000000,
	LIVEOBJ1_EATING        = 0x40000000,
	LIVEOBJ1_UNK_80000000  = 0x80000000,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags1);

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
	LIVEOBJ2_UNK_100              = 0x100,
	LIVEOBJ2_UNK_200              = 0x200,
	LIVEOBJ2_TRAINING             = 0x400,
	LIVEOBJ2_UNK_800              = 0x800,
	LIVEOBJ2_UNK_1000             = 0x1000,
	LIVEOBJ2_UNK_2000             = 0x2000,
	LIVEOBJ2_UNK_4000             = 0x4000,
	LIVEOBJ2_UPGRADING            = 0x8000,
	LIVEOBJ2_TRIGGERFRAMECALLBACK = 0x10000,
	LIVEOBJ2_UNK_20000            = 0x20000,
	LIVEOBJ2_UNK_40000            = 0x40000,
	LIVEOBJ2_UNK_80000            = 0x80000,
	LIVEOBJ2_UNK_100000           = 0x100000,
	LIVEOBJ2_UNK_200000           = 0x200000,
	LIVEOBJ2_UNK_400000           = 0x400000,
	LIVEOBJ2_UNK_800000           = 0x800000,
	LIVEOBJ2_UNK_1000000          = 0x1000000,
	LIVEOBJ2_UNK_2000000          = 0x2000000,
	LIVEOBJ2_UNK_4000000          = 0x4000000,
	LIVEOBJ2_UNK_8000000          = 0x8000000,
	LIVEOBJ2_UNK_10000000         = 0x10000000,
	LIVEOBJ2_UNK_20000000         = 0x20000000,
	LIVEOBJ2_UNK_40000000         = 0x40000000,
	LIVEOBJ2_UNK_80000000         = 0x80000000,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags2);

enum LiveFlags3 : uint32 // [LegoRR/LegoObject.c|flags:0x4|type:uint]
{
	LIVEOBJ3_NONE           = 0,
	LIVEOBJ3_UNK_1          = 0x1,
	LIVEOBJ3_UNK_2          = 0x2,
	LIVEOBJ3_UNK_4          = 0x4,
	LIVEOBJ3_UNK_8          = 0x8,
	LIVEOBJ3_UNK_10         = 0x10,
	LIVEOBJ3_UNK_20         = 0x20,
	LIVEOBJ3_UNK_40         = 0x40,
	LIVEOBJ3_UNK_80         = 0x80,
	LIVEOBJ3_CANSELECT      = 0x100,
	LIVEOBJ3_UNK_200        = 0x200,
	LIVEOBJ3_UNK_400        = 0x400,
	LIVEOBJ3_UNK_1000       = 0x1000,
	LIVEOBJ3_UNK_2000       = 0x2000,
	LIVEOBJ3_UNK_4000       = 0x4000,
	LIVEOBJ3_UNK_8000       = 0x8000,
	LIVEOBJ3_UNK_10000      = 0x10000,
	LIVEOBJ3_SIMPLEOBJECT   = 0x20000,
	LIVEOBJ3_UNK_40000      = 0x40000,
	LIVEOBJ3_IGNOREME_UNK   = 0x80000,
	LIVEOBJ3_UNK_100000     = 0x100000,
	LIVEOBJ3_UNK_200000     = 0x200000,
	LIVEOBJ3_UNK_400000     = 0x400000,
	LIVEOBJ3_UNK_800000     = 0x800000,
	LIVEOBJ3_UNK_1000000    = 0x1000000,
	LIVEOBJ3_UNK_2000000    = 0x2000000,
	LIVEOBJ3_CANGATHER      = 0x4000000,
	LIVEOBJ3_UNK_8000000    = 0x8000000,
	LIVEOBJ3_CANROUTERUBBLE = 0x10000000,
	LIVEOBJ3_HASPOWER       = 0x20000000,
	LIVEOBJ3_UNK_40000000   = 0x40000000,
	LIVEOBJ3_POWEROFF       = 0x80000000,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags3);

enum LiveFlags4 : uint32 // [LegoRR/LegoObject.c|flags:0x4|type:uint]
{
	LIVEOBJ4_NONE          = 0,
	LIVEOBJ4_UNK_1         = 0x1,
	LIVEOBJ4_UNK_2         = 0x2,
	LIVEOBJ4_UNK_8         = 0x8,
	LIVEOBJ4_UNK_10        = 0x10,
	LIVEOBJ4_CALLTOARMS_20 = 0x20,
	LIVEOBJ4_UNK_40        = 0x40,
	LIVEOBJ4_UNK_80        = 0x80,
	LIVEOBJ4_UNK_200       = 0x200,
	LIVEOBJ4_UNK_800       = 0x800,
	LIVEOBJ4_UNK_1000      = 0x1000,
	LIVEOBJ4_UNK_2000      = 0x2000,
	LIVEOBJ4_UNK_4000      = 0x4000,
	LIVEOBJ4_UNK_8000      = 0x8000,
	LIVEOBJ4_UNK_10000     = 0x10000,
	LIVEOBJ4_UNK_20000     = 0x20000,
	LIVEOBJ4_UNK_40000     = 0x40000,
	LIVEOBJ4_UNK_80000     = 0x80000,
	LIVEOBJ4_UNK_100000    = 0x100000,
	LIVEOBJ4_UNK_200000    = 0x200000,
	LIVEOBJ4_UNK_400000    = 0x400000,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags4);

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
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags5);

enum LoaderFlags : uint32 // [LegoRR/Loader.c|flags:0x4|type:uint]
{
	LOADER_FLAG_NONE    = 0,
	LOADER_FLAG_ENABLED = 0x1,
};
DEFINE_ENUM_FLAG_OPERATORS(LoaderFlags);

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
DEFINE_ENUM_FLAG_OPERATORS(LWSRFFLAGS);

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
DEFINE_ENUM_FLAG_OPERATORS(LWTEXFLAGS);

enum LWTEXMAPTYPE : uint32 // [Gods98/Lwt.c|flags:0x4|type:uint]
{
	MT_PLANAR      = 0,
	MT_CYLINDRICAL = 0x1,
	MT_SPHERICAL   = 0x2,
	MT_MAX         = 0x3,
};
DEFINE_ENUM_FLAG_OPERATORS(LWTEXMAPTYPE);

enum MainCLFlags : uint32 // [LegoRR/Lego.c|flags:0x4|type:uint] Flags specified by the "-flags #" command line argument (which has to be in decimal...)
{
	CL_FLAG_NONE      = 0,
	CL_FLAG_BLOCKFADE = 0x8000,
};
DEFINE_ENUM_FLAG_OPERATORS(MainCLFlags);

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
DEFINE_ENUM_FLAG_OPERATORS(MainFlags);

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
DEFINE_ENUM_FLAG_OPERATORS(Map3D_BlockFlags);

enum Map3D_TransitionFlags : uint8 // [LegoRR/Map3D.c|flags:0x1|type:byte]
{
	MAP3DTRANS_FLAG_NONE = 0,
	MAP3DTRANS_FLAG_USED = 0x1,
};
DEFINE_ENUM_FLAG_OPERATORS(Map3D_TransitionFlags);

enum Map3DFlags : uint32 // [LegoRR/Map3D.c|flags:0x4|type:uint]
{
	MAP3D_FLAG_NONE           = 0,
	MAP3D_FLAG_VERTEXMODIFIED = 0x2,
	MAP3D_FLAG_EMISSIVE_4     = 0x4,
};
DEFINE_ENUM_FLAG_OPERATORS(Map3DFlags);

enum Mem_HandleFlags : uint32 // [Gods98/Memory.c|flags:0x4|type:uint] Flags for SharedBuffer struct
{
	MEMORY_HANDLE_FLAG_NONE = 0,
	MEMORY_HANDLE_FLAG_USED = 0x1,
};
DEFINE_ENUM_FLAG_OPERATORS(Mem_HandleFlags);

enum MeshLODFlags : uint32 // [LegoRR/MeshLOD.c|flags:0x4|type:uint]
{
	MESHLOD_FLAG_NONE     = 0,
	MESHLOD_FLAG_CLONED   = 0x1,
	MESHLOD_FLAG_MEMBLOCK = 0x2,
};
DEFINE_ENUM_FLAG_OPERATORS(MeshLODFlags);

enum ObjectiveFlags : uint32 // [LegoRR/Objective.c|flags:0x4|type:uint]
{
	OBJECTIVE_NONE               = 0,
	OBJECTIVE_UNK_1              = 0x1,
	OBJECTIVE_COMPLETE           = 0x2,
	OBJECTIVE_FAILED             = 0x4,
	OBJECTIVE_UNK_8              = 0x8,
	OBJECTIVE_SHOWADVISOR        = 0x10,
	OBJECTIVE_SHOWACHEIVEADVISOR = 0x20,
	OBJECTIVE_HITTIMEFAIL        = 0x40,
	OBJECTIVE_SHOWFAILEDADVISOR  = 0x80,
	OBJECTIVE_CRYSTAL            = 0x100,
	OBJECTIVE_ORE                = 0x200,
	OBJECTIVE_BLOCK              = 0x400,
	OBJECTIVE_TIMER              = 0x800,
	OBJECTIVE_CONSTRUCTION       = 0x1000,
};
DEFINE_ENUM_FLAG_OPERATORS(ObjectiveFlags);

enum ObjInfoFlags : uint32 // [LegoRR/ObjInfo.c|flags:0x4|type:uint]
{
	OBJINFO_NONE               = 0,
	OBJINFO_HUNGERIMAGES       = 0x1,
	OBJINFO_HEALTHBAR          = 0x2,
	OBJINFO_HEALTHBAR_VERTICAL = 0x8,
	OBJINFO_BUBBLEIMAGES       = 0x10,
};
DEFINE_ENUM_FLAG_OPERATORS(ObjInfoFlags);

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
DEFINE_ENUM_FLAG_OPERATORS(RewardItemFlags);

enum RewardScrollFlags : uint32 // [LegoRR/Rewards.c|flags:0x4|type:uint]
{
	REWARDSCROLL_NONE  = 0,
	REWARDSCROLL_UNK_1 = 0x1,
	REWARDSCROLL_UNK_2 = 0x2,
};
DEFINE_ENUM_FLAG_OPERATORS(RewardScrollFlags);

enum RewardScrollLabelFlags : uint32 // [LegoRR/Rewards.c|flags:0x4|type:uint]
{
	REWARDSCROLL_LABEL_NONE     = 0,
	REWARDSCROLL_LABEL_CENTERED = 0x1,
	REWARDSCROLL_LABEL_NOSCROLL = 0x2,
};
DEFINE_ENUM_FLAG_OPERATORS(RewardScrollLabelFlags);

enum RoofFlags : uint32 // [LegoRR/Roof.c|flags:0x4|type:uint]
{
	ROOF_NONE          = 0,
	ROOF_HIDDEN        = 0x1,
	ROOF_NEEDUPDATE    = 0x2,
	ROOF_SHIFTVERTICES = 0x4,
};
DEFINE_ENUM_FLAG_OPERATORS(RoofFlags);

enum RouteFlags : uint8 // [LegoRR/LegoObject.c|flags:0x1|type:byte]
{
	ROUTE_FLAG_NONE         = 0,
	ROUTE_DIRECTION_MASK    = 0x3,
	ROUTE_FLAG_GOTOBUILDING = 0x4,
	ROUTE_FLAG_UNK_8        = 0x8,
	ROUTE_UNK_MASK_c        = 0xc,
	ROUTE_FLAG_UNK_10       = 0x10,
	ROUTE_FLAG_UNK_20       = 0x20,
	ROUTE_FLAG_UNK_40       = 0x40,
};
DEFINE_ENUM_FLAG_OPERATORS(RouteFlags);

enum SaveRewardFlags : uint32 // [LegoRR/Rewards.c|flags:0x4|type:uint]
{
	SAVEREWARD_NONE  = 0,
	SAVEREWARD_UNK_1 = 0x1,
	SAVEREWARD_UNK_2 = 0x2,
};
DEFINE_ENUM_FLAG_OPERATORS(SaveRewardFlags);

enum SFX_GlobFlags : uint32 // [LegoRR/SFX.c|flags:0x4|type:uint]
{
	SFX_GLOB_FLAG_NONE         = 0,
	SFX_GLOB_FLAG_SOUNDON      = 0x1,
	SFX_GLOB_FLAG_POPULATEMODE = 0x2,
	SFX_GLOB_FLAG_UNK_8        = 0x8,
};
DEFINE_ENUM_FLAG_OPERATORS(SFX_GlobFlags);

enum SFX_InstanceFlags : uint32 // [LegoRR/SFX.c|flags:0x4|type:uint]
{
	SFX_INSTANCE_FLAG_NONE = 0,
};
DEFINE_ENUM_FLAG_OPERATORS(SFX_InstanceFlags);

enum Sound3DFlags : uint32 // [LegoRR/SFX.c|flags:0x4|type:uint]
{
	SAMPLE_NONE     = 0,
	SAMPLE_ISUSED   = 0x1,
	SAMPLE_VOLUME   = 0x2,
	SAMPLE_MULTIPLE = 0x4,
	SAMPLE_STREAMED = 0x8,
};
DEFINE_ENUM_FLAG_OPERATORS(Sound3DFlags);

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
DEFINE_ENUM_FLAG_OPERATORS(StatsFlags1);

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
DEFINE_ENUM_FLAG_OPERATORS(StatsFlags2);

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
DEFINE_ENUM_FLAG_OPERATORS(StatsFlags3);

enum SurfaceMapStruct2A8Flags : uint32 // [LegoRR/???|flags:0x4|type:uint]
{
	SURFMAP_STRUCT2A8_NONE   = 0,
	SURFMAP_STRUCT2A8_HIDDEN = 0x1,
	SURFMAP_STRUCT2A8_UNK_2  = 0x2,
	SURFMAP_STRUCT2A8_UNK_4  = 0x4,
	SURFMAP_STRUCT2A8_UNK_8  = 0x8,
	SURFMAP_STRUCT2A8_UNK_10 = 0x10,
};
DEFINE_ENUM_FLAG_OPERATORS(SurfaceMapStruct2A8Flags);

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
DEFINE_ENUM_FLAG_OPERATORS(TeleportObjectType);

enum ToolTipFlags : uint32 // [LegoRR/ToolTip.c|flags:0x4|type:uint]
{
	TOOLTIP_FLAG_NONE   = 0,
	TOOLTIP_FLAG_UNK_1  = 0x1,
	TOOLTIP_FLAG_UNK_2  = 0x2,
	TOOLTIP_FLAG_UNK_4  = 0x4,
	TOOLTIP_FLAG_UNK_8  = 0x8,
	TOOLTIP_FLAG_UNK_10 = 0x10,
};
DEFINE_ENUM_FLAG_OPERATORS(ToolTipFlags);

enum TrainedFlags : uint32 // [LegoRR/LegoObject.c|flags:0x4|type:uint|tags:DUPLICATE] These can be substituted for LiveFlags5
{
	TRAINED_NONE     = 0,
	TRAINED_PILOT    = 0x1,
	TRAINED_SAILOR   = 0x2,
	TRAINED_DRIVER   = 0x4,
	TRAINED_DYNAMITE = 0x8,
	TRAINED_REPAIR   = 0x10,
	TRAINED_SCANNER  = 0x20,
};
DEFINE_ENUM_FLAG_OPERATORS(TrainedFlags);

enum TutorialFlags : uint32 // [LegoRR/NERPs.c|flags:0x4|type:uint]
{
	TUTORIAL_NONE     = 0,
	TUTORIAL_UNK_2    = 0x2,
	TUTORIAL_UNK_4    = 0x4,
	TUTORIAL_UNK_8    = 0x8,
	TUTORIAL_UNK_10   = 0x10,
	TUTORIAL_UNK_20   = 0x20,
	TUTORIAL_UNK_40   = 0x40,
	TUTORIAL_UNK_80   = 0x80,
	TUTORIAL_UNK_100  = 0x100,
	TUTORIAL_UNK_200  = 0x200,
	TUTORIAL_UNK_400  = 0x400,
	TUTORIAL_UNK_800  = 0x800,
	TUTORIAL_UNK_1000 = 0x1000,
};
DEFINE_ENUM_FLAG_OPERATORS(TutorialFlags);

enum VehicleFlags : uint32 // [LegoRR/Vehicle.c|flags:0x4|type:uint]
{
	VEHICLE_FLAG_NONE        = 0,
	VEHICLE_FLAG_SOURCE      = 0x1,
	VEHICLE_FLAG_HIDDEN      = 0x2,
	VEHICLE_FLAG_NOACTIVITY1 = 0x4,
	VEHICLE_FLAG_HOLDMISSING = 0x8,
};
DEFINE_ENUM_FLAG_OPERATORS(VehicleFlags);

enum Wad_EntryFlags : uint32 // [Gods98/Wad.c|flags:0x4|type:uint]
{
	WADENTRY_FLAG_NONE         = 0,
	WADENTRY_FLAG_UNCOMPRESSED = 0x1,
	WADENTRY_FLAG_RNCOMPRESSED = 0x2,
	WADENTRY_FLAG_IS_IN_WAD    = 0x4,
};
DEFINE_ENUM_FLAG_OPERATORS(Wad_EntryFlags);

enum WaterFlags : uint32 // [LegoRR/Water.c|flags:0x4|type:uint]
{
	WATER_NONE       = 0,
	WATER_HIDDEN_UNK = 0x1,
	WATER_STATE_A    = 0x2,
	WATER_STATE_B    = 0x4,
};
DEFINE_ENUM_FLAG_OPERATORS(WaterFlags);



union File_union // [Gods98/Files.c|union:0x4]
{
	/*0,4*/	FILE* std; // Standard file stream
	/*0,4*/	WADFILE* wad; // WAD file stream
	/*4*/
};

union MenuItem_Data_union // [LegoRR/FrontEnd.c|union:0x4]
{
	/*0,4*/	MenuItem_CycleData* cycle;
	/*0,4*/	MenuItem_TriggerData* trigger;
	/*0,4*/	MenuItem_SliderData* slider;
	/*0,4*/	MenuItem_RealSliderData* realSlider;
	/*0,4*/	Menu* next;
	/*4*/
};



struct Advisor_Globs // [LegoRR/Advisor.c|struct:0x410|tags:GLOBS]
{
	/*000,54*/	char* positionName[21];
	/*054,2f4*/	AdvisorPositionData advisorPositions[21];
	/*348,2c*/	char* animName[11];
	/*374,84*/	AdvisorAnimData advisorAnims[11];
	/*3f8,4*/	Advisor_Type currentType;
	/*3fc,4*/	Container* cameraCont;
	/*400,4*/	Viewport* viewMain;
	/*404,4*/	real32 position_Z; // Always set to 0.96f  (was probably configurable at one point)
	/*408,4*/	Container* lightCont;
	/*40c,4*/	AdvisorStateFlags flags;
	/*410*/
};

struct AdvisorAnimData // [LegoRR/Advisor.c|struct:0xc]
{
	/*0,4*/	Container* resData;
	/*4,4*/	real32 loopStartTime; // ignored when not looping
	/*8,4*/	real32 loopEndTime; // ignored when not looping
	/*c*/
};

struct AdvisorPositionData // [LegoRR/Advisor.c|struct:0x24]
{
	/*00,4*/	Advisor_Anim animType;
	/*04,4*/	Text_Type textType;
	/*08,4*/	sint32 sfxIndex;
	/*0c,4*/	Panel_Type panelType;
	/*10,8*/	Point2F point1;
	/*18,8*/	Point2F point2; // Identical to point1
	/*20,4*/	AdvisorPositionFlags flags; // (init: 0x20000), 0x10000 = NULL panel, 0x40000 = non-NULL text
	/*24*/
};

struct AITask // [LegoRR/AITask.c|struct:0x68|tags:LISTSET]
{
	/*00,4*/	AITask_Type taskType;
	/*04,4*/	undefined4 field_4;
	/*08,8*/	Point2I blockPos;
	/*10,4*/	LegoObject* object_10;
	/*14,4*/	real32 unkExpiryTime;
	/*18,4*/	real32 float_18;
	/*1c,4*/	uint32 priorityValue;
	/*20,4*/	LegoObject_Type objType;
	/*24,4*/	sint32 objIndex;
	/*28,4*/	sint32 objLevel;
	/*2c,4*/	undefined4 field_2c;
	/*30,8*/	Point2F pointf_30; // probably a table
	/*38,4*/	LegoObject_ToolType toolType;
	/*3c,4*/	undefined4 mode_3c;
	/*40,4*/	LegoObject** unitList;
	/*44,4*/	uint32 unitListCount;
	/*48,4*/	LegoObject* object_48;
	/*4c,4*/	AI_Priority priorityType;
	/*50,4*/	uint32 taskStartTime;
	/*54,4*/	Message_Type completeAction;
	/*58,4*/	AITask* aiTask_58;
	/*5c,4*/	AITaskFlags flags; // not set means ptr_40 is assigned
	/*60,4*/	AITask* next; // assigned to DAT_004b4358
	/*64,4*/	AITask* nextFree; // (for listSet)
	/*68*/
};

struct AITask_Globs // [LegoRR/AITask.c|struct:0x4e9c|tags:GLOBS]
{
	/*0000,30*/	AITask* listSet[12];
	/*0030,4*/	AITask* freeList;
	/*0034,4*/	uint32 listCount;
	/*0038,7c*/	char* aitaskName[31];
	/*00b4,6c*/	char* priorityName[27];
	/*0120,6c*/	uint32 priorityValues[27];
	/*018c,4*/	AITask* AITaskUnkPtr;
	/*0190,4*/	AITask* AITaskDataNext;
	/*0194,c8*/	LegoObject* liveObjsTable_1[50];
	/*025c,4*/	uint32 liveObjsCount_1;
	/*0260,c8*/	LegoObject* liveObjsTable_2[50];
	/*0328,4*/	uint32 liveObjsCount_2;
	/*032c,4b00*/	uint32 requestObjCounts[20][15][16];
	/*4e2c,6c*/	bool32 disabledPriorities[27];
	/*4e98,4*/	uint32 flags;
	/*4e9c*/
};

struct Animation_Globs // [Gods98/Animation.c|struct:0x8|tags:GLOBS]
{
	/*0,1*/	bool g98NoAvis; // (global variable)
	/*1,3*/	uint8 padding1[3];
	/*4,4*/	IDirectDraw4* ddraw; // (global variable)
	/*8*/
};

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

struct Area2F // [common.c|struct:0x10] also Area2F
{
	/*00,4*/	real32 x;
	/*04,4*/	real32 y;
	/*08,4*/	real32 width;
	/*0c,4*/	real32 height;
	/*10*/
};

struct Area2I // [common.c|struct:0x10] also Area2I
{
	/*00,4*/	sint32 x;
	/*04,4*/	sint32 y;
	/*08,4*/	sint32 width;
	/*0c,4*/	sint32 height;
	/*10*/
};

struct BasicObjectModel // [LegoRR/dummy.c|struct:0x8] This is a dummy structure that is used for CreatureData, BuildingData, and UpgradeData (for functions using these structures that have been merged together). It's highly likely this similarity is only due to linked functions performing the same behavior and being grouped together.
{
	/*0,4*/	sint32 objID;
	/*4,4*/	Container* contAct; // ACT, true
	/*8*/
};

struct BezierCurve // [LegoRR/Routing.c|struct:0x25c]
{
	/*000,4*/	uint32 count;
	/*004,190*/	Point2F points[50];
	/*194,c8*/	real32 distances[50];
	/*25c*/
};

#pragma pack(push, 2)
struct BITMAP_FILE_INFO_STRUCT // [Gods98/dummy.c|struct:0x3a|pack:2] Helper struct to combine both BITMAPFILEHEADER, BITMAPINFOHEADER, and palette data into one field
{
	/*00,10*/	BITMAPFILEHEADER hdr;
	/*10,28*/	BITMAPINFOHEADER bmi;
	/*38,4*/	RGBQUAD bmiColors[1];
	/*3c*/
};
#pragma pack(pop)

struct BlockConstruction // [LegoRR/Construction.c|struct:0xd4]
{
	/*00,4*/	sint32 objID;
	/*04,4*/	Direction direction;
	/*08,4*/	sint32 int_8;
	/*0c,8*/	Point2I pointi_c;
	/*14,4*/	Point2I* shapePoints;
	/*18,4*/	uint32 shapeCount;
	/*1c,8*/	undefined field_0x1c_0x23[8];
	/*24,4*/	BlockConstruction* next_24;
	/*28,4*/	undefined field_0x28_0x2b[4];
	/*2c,4*/	LegoObject* liveObjs_2c[1];
	/*30,9c*/	undefined field_0x30_0xcb[156];
	/*cc,4*/	uint32 liveObjsCount_cc;
	/*d0,4*/	uint32 flags;
	/*d4*/
};

struct BlockElectricFence // [LegoRR/ElectricFence.c|struct:0x14|tags:LISTSET]
{
	/*00,4*/	LegoObject* attachedObject;
	/*04,8*/	Point2I blockPos;
	/*0c,4*/	real32 timer;
	/*10,4*/	BlockElectricFence* nextFree; // (for listSet)
	/*14*/
};

struct BlockFenceGrid // [LegoRR/ElectricFence.c|struct:0xc|tags:BLOCKGRID] Note that the size when allocating fenceGrid is mistakenly 0x14, but lookup is performed with size 0xc
{
	/*0,4*/	BlockElectricFence* efence;
	/*4,4*/	LegoObject* studObj; // Glowing lime stud  object placed between 2-block-wide connections
	/*8,4*/	BlockFenceGrid_Flags flags;
	/*c*/
};

struct BlockPointer // [LegoRR/NERPs.c|struct:0xc]
{
	/*0,8*/	Point2I blockPos;
	/*8,4*/	uint32 id;
	/*c*/
};

struct BlockSpiderWeb // [LegoRR/SpiderWeb.c|struct:0xc]
{
	/*0,4*/	LegoObject* object; // "SpiderWeb" LiveObject
	/*4,4*/	real32 health; // Assumed as health, init: 100.0f
	/*8,4*/	BlockSpiderWebFlags flags;
	/*c*/
};

struct Box2F // [common.c|struct:0x10]
{
	/*00,4*/	real32 x1;
	/*04,4*/	real32 y1;
	/*08,4*/	real32 x2;
	/*0c,4*/	real32 y2;
	/*10*/
};

struct Box2I // [common.c|struct:0x10]
{
	/*00,4*/	sint32 x1;
	/*04,4*/	sint32 y1;
	/*08,4*/	sint32 x2;
	/*0c,4*/	sint32 y2;
	/*10*/
};

struct Box3F // [common.c|struct:0x18] Box3F
{
	/*00,c*/	Vector3F min;
	/*0c,c*/	Vector3F max;
	/*18*/
};

struct Bubble_Globs // [LegoRR/Bubble.c|struct:0x4f4|tags:GLOBS]
{
	/*000,4*/	bool32 ObjectUIsAlwaysVisible; // Object Display HUD/UI over entities in-game
	/*004,9c*/	Image* bubbleImages[39];
	/*0a0,9c*/	char* bubbleName[39];
	/*13c,48*/	undefined1 reserved1[72];
	/*184,a0*/	BubbleData table1[20];
	/*224,a0*/	BubbleData table2[20];
	/*2c4,a0*/	BubbleData table3[20];
	/*364,190*/	BubbleData bigTable[50];
	/*4f4*/
};

struct BubbleData // [LegoRR/Bubble.c|struct:0x8]
{
	/*0,4*/	LegoObject* object_0;
	/*4,4*/	real32 float_4;
	/*8*/
};

struct BuildingModel // [LegoRR/Building.c|struct:0x14c]
{
	/*000,4*/	sint32 objID;
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
	/*07c,4*/	Container* powerLevelScene; // (ae: PowerLevelScene, LWS, true)
	/*080,4*/	real32 powerLevelTimer;
	/*084,4*/	Point2I* shapePoints; // (ae: Shape) Point2I[10]
	/*088,4*/	uint32 shapeCount; // (ae: Shape)
	/*08c,14*/	UpgradesModel upgrades;
	/*0a0,a8*/	WeaponsModel weapons;
	/*148,4*/	BuildingFlags flags; // (0x1: original that holds memory [broken], 0x2: PowerLevel scene playing)
	/*14c*/
};

struct Camera_Globs // [LegoRR/LegoCamera.c|struct:0x10|tags:GLOBS]
{
	/*00,4*/	real32 maxSpeed; // (cfg: CameraSpeed) maximum move speed of camera
	/*04,4*/	real32 deceleration; // (cfg: CameraDropOff) movement deceleration
	/*08,4*/	real32 acceleration; // (cfg: CameraAcceleration) movement acceleration
	/*0c,4*/	sint32 mouseScrollIndent; // (cfg: MouseScrollIndent) area around window borders for mouse movement
	/*10*/
};

struct ColourRGBAF // [common.c|struct:0x10]
{
	/*00,4*/	real32 red;
	/*04,4*/	real32 green;
	/*08,4*/	real32 blue;
	/*0c,4*/	real32 alpha;
	/*10*/
};

struct ColourRGBAI // [common.c|struct:0x10]
{
	/*00,4*/	uint32 red;
	/*04,4*/	uint32 green;
	/*08,4*/	uint32 blue;
	/*0c,4*/	uint32 alpha;
	/*10*/
};

#pragma pack(push, 1)
struct ColourRGBAPacked // [common.c|struct:0x4|pack:1]
{
	/*0,1*/	uint8 red;
	/*1,1*/	uint8 green;
	/*2,1*/	uint8 blue;
	/*3,1*/	uint8 alpha;
	/*4*/
};
#pragma pack(pop)

struct ColourRGBF // [common.c|struct:0xc]
{
	/*0,4*/	real32 red;
	/*4,4*/	real32 green;
	/*8,4*/	real32 blue;
	/*c*/
};

struct ColourRGBI // [common.c|struct:0xc]
{
	/*0,4*/	uint32 red;
	/*4,4*/	uint32 green;
	/*8,4*/	uint32 blue;
	/*c*/
};

#pragma pack(push, 1)
struct ColourRGBPacked // [common.c|struct:0x3|pack:1]
{
	/*0,1*/	uint8 red;
	/*1,1*/	uint8 green;
	/*2,1*/	uint8 blue;
	/*3*/
};
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

struct Config_Globs // [Gods98/Config.c|struct:0x48c|tags:GLOBS]
{
	/*000,400*/	char s_JoinPath_string[1024]; // (not part of Manager, static array in JoinPath func)
	/*400,80*/	Config* listSet[32];
	/*480,4*/	Config* freeList;
	/*484,4*/	uint32 listCount;
	/*488,4*/	Config_GlobFlags flags;
	/*48c*/
};

struct Construction_Globs // [LegoRR/Construction.c|struct:0x38|tags:GLOBS]
{
	/*00,4*/	uint32 uint_0; // (related to Construction->int_8)
	/*04,4*/	BlockConstruction* construct_4;
	/*08,14*/	undefined4 reserved1Table[5]; // (probably related to unused buildingBaseTable)
	/*1c,14*/	char* buildingBaseTable[5];
	/*30,4*/	uint32 buildingBaseCount;
	/*34,4*/	bool32 disableCryOreDrop;
	/*38*/
};

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

struct Container_CloneData // [Gods98/Containers.c|struct:0x14] structure assigned to ResourceData->field_24 (allocated for ACT,ANIM resource types)
{
	/*00,4*/	Container* clonedFrom; // NULL if this is the original
	/*04,4*/	Container** cloneTable; // List of clones (NULL for unused elements)
	/*08,4*/	uint32 cloneCount; // Total number of clones made and clone's number in the list.
	/*0c,4*/	IDirect3DRMFrame3* cloneNumber; // (init: ResourceData->frame2 IDirect3DRMFrame3 * ???)
	/*10,4*/	bool32 used; // (init: 1)
	/*14*/
};

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

struct Container_Texture // [Gods98/Containers.c|struct:0xc]
{
	/*0,4*/	IDirectDrawSurface4* surface;
	/*4,4*/	IDirect3DRMTexture3* texture;
	/*8,4*/	bool32 colourKey;
	/*c*/
};

struct Container_TextureData // [Gods98/Containers.c|struct:0x8]
{
	/*0,4*/	char* xFileName;
	/*4,4*/	uint32 flags;
	/*8*/
};

struct Container_TextureRef // [Gods98/Containers.c|struct:0x8]
{
	/*0,4*/	char* filename;
	/*4,4*/	IDirect3DRMTexture3* texture;
	/*8*/
};

struct Container_TypeData // [Gods98/Containers.c|struct:0x10]
{
	/*00,4*/	char* name;
	/*04,4*/	IDirect3DRMLight* light;
	/*08,4*/	IDirect3DRMMesh* mesh;
	/*0c,4*/	Mesh* transMesh;
	/*10*/
};

struct Coord2U // [common.c|struct:0x4] Point2U structure using short-sized integers (name is based off the WINAPI console structure COORD, using the same layout)
{
	/*0,2*/	uint16 x;
	/*2,2*/	uint16 y;
	/*4*/
};

struct CreatureModel // [LegoRR/Creature.c|struct:0x74] Possibly alphabetically correct names: Bipedal, BasicUnit, etc... (has to be before Bubble, and possible after BezierCurve or AI(Task?))
{
	/*00,4*/	sint32 objID;
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

struct CryTuple_8 // [LegoRR/FrontEnd.c|struct:0x8]
{
	/*0,4*/	uint32 cryCount;
	/*4,4*/	uint32 unkCount;
	/*8*/
};

struct DamageFont_Globs // [LegoRR/DamageFont.c|struct:0x16c|tags:GLOBS]
{
	/*000,28*/	Container_Texture* fontTextDigitsTable[10];
	/*028,4*/	Container_Texture* fontTextMinus;
	/*02c,140*/	DamageFontData instanceTable[10];
	/*16c*/
};

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

struct Dependencies_Globs // [LegoRR/Dependencies.c|struct:0xe5b4|tags:GLOBS]
{
	/*0000,e5b0*/	DependencyData table[20][15];
	/*e5b0,4*/	bool32 disabled; // (Debug feature with F11 key)
	/*e5b4*/
};

struct DependencyData // [LegoRR/Dependencies.c|struct:0xc4]
{
	/*00,40*/	uint32 numRequirements[16]; // [levels:16]
	/*40,40*/	DependencyRequirement* requirements[16]; // [levels:16][*numRequired] Ptr to table of size numRequired
	/*80,4*/	bool32 manualLevel; // Force requirements for specific level if key format: "<HitOnceStay|*>:Object:<#>"
	/*84,40*/	DependencyFlags levelFlags[16]; // [levels:16] (1 = HitOnceStay)
	/*c4*/
};

struct DependencyRequirement // [LegoRR/Dependencies.c|struct:0x10]
{
	/*00,4*/	LegoObject_Type objType;
	/*04,4*/	sint32 objIndex;
	/*08,4*/	sint32 objLevel;
	/*0c,4*/	bool32 hasLevel;
	/*10*/
};

struct DependencyUnlocks // [LegoRR/Dependencies.c|struct:0x204]
{
	/*000,80*/	LegoObject_Type objTypes[32];
	/*080,80*/	sint32 objIndexes[32];
	/*100,80*/	sint32 objLevels[32];
	/*180,80*/	bool32 objHasLevels[32]; // (unlocks for a specific level)
	/*200,4*/	uint32 count;
	/*204*/
};

struct Detail_Mesh // [LegoRR/???|struct:0x340]
{
	/*000,8*/	Container* promesh_ab[2];
	/*008,320*/	undefined4 table_ab[2][100];
	/*328,4*/	real32 BlockSize;
	/*32c,4*/	undefined4 field_32c;
	/*330,c*/	undefined field_0x330_0x33b[12];
	/*33c,4*/	Detail_TextureSet* textureSet;
	/*340*/
};

struct Detail_TextureSet // [LegoRR/???|struct:0xc]
{
	/*0,8*/	Size2I gridSize;
	/*8,4*/	Container_Texture** gridSurfaces;
	/*c*/
};

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

struct Draw_Rect // [Gods98/Draw.c|struct:0x1c]
{
	/*00,10*/	Area2F rect;
	/*10,4*/	real32 r;
	/*14,4*/	real32 g;
	/*18,4*/	real32 b;
	/*1c*/
};

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

struct EffectElectricFenceBeam // [LegoRR/Effects.c|struct:0xf4]
{
	/*00,4*/	Container* cont; // LWS:true
	/*04,78*/	Container* contTable[30];
	/*7c,78*/	bool32 finishedTable[30];
	/*f4*/
};

struct EffectMisc // [LegoRR/Effects.c|struct:0x38]
{
	/*00,28*/	Container* contTable[10];
	/*28,4*/	uint32 count; // (max of 10)
	/*2c,4*/	undefined4 field_2c;
	/*30,4*/	Container* cont; // LWS,true | LWO,true
	/*34,4*/	undefined4 field_34;
	/*38*/
};

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

struct ElectricFence_Globs // [LegoRR/ElectricFence.c|struct:0x90|tags:GLOBS]
{
	/*00,4*/	BlockFenceGrid* fenceGrid; // BlockElectricFence[width * height]
	/*04,4*/	Lego_Level* level;
	/*08,80*/	BlockElectricFence* listSet[32];
	/*88,4*/	BlockElectricFence* freeList;
	/*8c,4*/	uint32 listCount; // (no flags)
	/*90*/
};

struct EmergeBlock // [LegoRR/Lego.c|struct:0xc]
{
	/*0,8*/	Point2I blockPos;
	/*8,4*/	bool32 used;
	/*c*/
};

struct EmergeTrigger // [LegoRR/Lego.c|struct:0x4c]
{
	/*00,4*/	undefined4 field_0;
	/*04,8*/	Point2I blockPos;
	/*0c,4*/	real32 timeout;
	/*10,3c*/	EmergeBlock emergePoints[5];
	/*4c*/
};

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
	/*20,4*/	uint32 flags;
	/*24*/
};

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

struct Fallin_Globs // [LegoRR/Fallin.c|struct:0x4|tags:GLOBS] Just a single field for Fallins (most other settings are found in Lego_Globs)
{
	/*0,4*/	uint32 NumberOfLandSlidesTillCaveIn;
	/*4*/
};

struct File // [Gods98/Files.c|struct:0x8]
{
	/*0,4*/	FileSys type;
	/*4,4*/	File_union stream;
	/*8*/
};

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

struct FileCheck_Globs // [Gods98/Files.c|struct:0x1f4004|tags:GLOBS] Loose static variables for File_CheckRedundantFiles in Files.c
{
	/*000000,1f4000*/	char loadedList[2000][1024]; // MAYBE USE LINKED LIST
	/*1f4000,4*/	uint32 numInList;
	/*1f4004*/
};

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

struct Flocks // [LegoRR/Flocks.c|struct:0x28] The singular flocks unit, which holds all items flying within it.
{
	/*00,4*/	FlocksItem* flocksSubdata1; // (is this a doubly-linked list?)
	/*04,4*/	FlocksItem* flocksSubdata2;
	/*08,4*/	uint32 numSubdata;
	/*0c,4*/	uint32 hasVector1;
	/*10,4*/	uint32 hasVector2;
	/*14,4*/	undefined4 field_14;
	/*18,4*/	undefined4 field_18;
	/*1c,4*/	undefined4 field_1c;
	/*20,4*/	undefined4 field_20;
	/*24,4*/	undefined4 field_24;
	/*28*/
};

struct Flocks_Globs // [LegoRR/Flocks.c|struct:0x10|tags:GLOBS] (struct name changed to "BatFlocks" instead of "Flocks" to avoid annoying autocorrect when setting type in Ghidra)
{
	/*00,4*/	real32 Turn;
	/*04,4*/	real32 Speed;
	/*08,4*/	real32 Tightness;
	/*0c,4*/	real32 GoalUpdate;
	/*10*/
};

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
	/*98,4*/	Container* resData_98;
	/*9c,4*/	FlocksItem* subdataNext_9c;
	/*a0*/
};

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

struct Font_Globs // [Gods98/Fonts.c|struct:0x8c|tags:GLOBS]
{
	/*00,80*/	Font* listSet[32]; // Fonts list
	/*80,4*/	Font* freeList;
	/*84,4*/	uint32 listCount; // number of lists.
	/*88,4*/	uint32 flags;
	/*8c*/
};

struct Front_Globs // [LegoRR/FrontEnd.c|struct:0x884|tags:GLOBS]
{
	/*000,4*/	MenuSet* pausedMenuSet;
	/*004,4*/	MenuSet* mainMenuSet;
	/*008,4*/	MenuSet* optionsMenuSet;
	/*00c,4*/	MenuSet* saveMenuSet;
	/*010,14*/	LevelSet tutorialLevels;
	/*024,14*/	LevelSet missionLevels;
	/*038,4*/	LevelInfo* startMissionInfo;
	/*03c,4*/	LevelInfo* startTutorialInfo;
	/*040,10*/	undefined4 reserved1[4];
	/*050,4*/	sint32 triggerCredits; // [trigger: 1=play credits]
	/*054,8*/	undefined4 reserved2[2];
	/*05c,4*/	sint32 triggerYesQuit; // [trigger: 1=yes, quit game]
	/*060,4*/	sint32 unusedMissionNumber; // (always -1)
	/*064,4*/	sint32 unusedTutorialNumber; // (always -1)
	/*068,4*/	sint32 currLevelSel; // [levelselect: index=hoverLevel?]
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
	/*0b0,4*/	uint32 overlayStartTime; // starting Main_GetTime (millliseconds)
	/*0b4,4*/	uint32 overlayCurrTime; // current Main_GetTime (millliseconds)
	/*0b8,4*/	Font* versionFont; // (file: bmpMbriefFONT2)
	/*0bc,4*/	char* versionString; // (cfg: Main::Version)
	/*0c0,450*/	SaveData saveData[6];
	/*510,4*/	sint32 saveNumber;
	/*514,4*/	char* strDefaultLevelBMPS; // (cfg: Menu::DefaultLevelBMPS) memory storage
	/*518,4*/	undefined4 reserved3;
	/*51c,8*/	Point2F scrollOffset; // Offset position in level select (or anywhere else with a larger menu image)
	/*524,8*/	undefined4 reserved4[2];
	/*52c,4*/	Container* rockWipeAnim;
	/*530,1*/	Front_RockWipeFlags rockWipeFlags;
	/*531,3*/	undefined padding1[3];
	/*534,4*/	real32 rockWipeSFXTimer;
	/*538,4*/	real32 rockWipeSFXStartTime;
	/*53c,4*/	Container* rockWipeLight;
	/*540,4*/	bool32 saveBool_540;
	/*544,4*/	bool32 isLoadModeBool_544;
	/*548,4*/	bool32 saveBool_548;
	/*54c,8*/	Size2I saveImageBigSize;
	/*554,40*/	char langLoadGame[64];
	/*594,40*/	char langSaveGame[64];
	/*5d4,4*/	MenuTextWindow* saveTextWnd;
	/*5d8,4*/	MenuTextWindow* saveLevelWnd;
	/*5dc,80*/	char langOverwriteTitle[128];
	/*65c,100*/	char langOverwriteMessage[256];
	/*75c,80*/	char langOverwriteOK[128];
	/*7dc,80*/	char langOverwriteCancel[128];
	/*85c,4*/	bool32 saveBool_85c;
	/*860,4*/	undefined4 reserved5;
	/*864,4*/	undefined4 unused_zero_864; // (init: 0) Set to 0 and never touched?
	/*868,4*/	sint32 maxLevelScreens;
	/*86c,8*/	undefined4 reserved6[2];
	/*874,4*/	uint32 levelSelectHoverNumber;
	/*878,4*/	uint32 levelSelectLastNumber;
	/*87c,4*/	bool32 levelSelectSFXPlaying;
	/*880,4*/	real32 levelSelectSFXTimer;
	/*884*/
};

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

struct G98CAnimationVtbl // [Gods98/Animation.c|struct:0x4|tags:VFTABLE]
{
	/*0,4*/	G98CAnimation* (* deletor)(G98CAnimation*, uint8);
	/*4*/
};

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

struct G98CSurfaceVtbl // [Gods98/Animation.c|struct:0xc|tags:VFTABLE]
{
	/*0,4*/	G98CSurface* (* deletor)(G98CSurface*, uint8);
	/*4,4*/	sint32 (* Width)(G98CSurface*);
	/*8,4*/	sint32 (* Height)(G98CSurface*);
	/*c*/
};

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
	/*12c,4*/	real32 float_12c;
	/*130,4*/	sint32 msbl_last_2_unknum;
	/*134,4*/	real32 dbgCursorLightLevel;
	/*138,4*/	bool32 isGameSpeedLocked; // When this is TRUE, game speed can only be lowered when calling `Game_SetGameSpeed`.
	/*13c,4*/	bool32 mslb_Last_3;
	/*140,4*/	bool32 mslb_Last_4;
	/*144,8*/	Point2F pointf_144;
	/*14c,4*/	bool32 mslb_Last_5;
	/*150,4*/	bool32 mslb_Last_6;
	/*154,4*/	bool32 mslb_Last_0;
	/*158,4*/	bool32 mslr_Last_0;
	/*15c,4*/	real32 elapsed_15c;
	/*160,4*/	bool32 bool_160;
	/*164,4*/	LegoObject* object_164;
	/*168,4*/	bool32 dbgF10InvertLighting;
	/*16c,4*/	bool32 dbgF9DisableLightEffects;
	/*170,4*/	undefined4 reserved3;
	/*174,4*/	LegoObject* dbgGetInVehicle; // (K debug key, assigned to selected vehicle, pressing K with a rock raider will tell them to get in this registered vehicle)
	/*178,4*/	Direction direction_178;
	/*17c,4*/	real32 timerTutorialBlockFlash;
	/*180*/
};

struct Graphics_Device // [Gods98/DirectDraw.c|struct:0x114]
{
	/*000,10*/	GUID guid;
	/*010,100*/	char desc[256]; // "name (description)"
	/*110,4*/	Graphics_DeviceFlags flags;
	/*114*/
};

struct Graphics_Driver // [Gods98/DirectDraw.c|struct:0x114]
{
	/*000,10*/	GUID guid;
	/*010,100*/	char desc[256]; // "name (description)"
	/*110,4*/	Graphics_DriverFlags flags;
	/*114*/
};

struct Graphics_Mode // [Gods98/DirectDraw.c|struct:0x110]
{
	/*000,4*/	uint32 width;
	/*004,4*/	uint32 height;
	/*008,4*/	uint32 bitDepth;
	/*00c,100*/	char desc[256]; // "WxH (BPP bit)", "WxH" (windowed)
	/*10c,4*/	Graphics_ModeFlags flags;
	/*110*/
};

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
	/*be4,4*/	sint32 activeObjIndex;
	/*be8,4*/	sint32 activeObjLevel;
	/*bec,78*/	LegoObject_Type unlockedObjTypes[30];
	/*c64,78*/	sint32 unlockedObjIndexes[30];
	/*cdc,78*/	sint32 unlockedObjLevels[30];
	/*d54,4*/	uint32 unlockedCount;
	/*d58,4*/	real32 float_d58;
	/*d5c,4*/	real32 float_d5c;
	/*d60,4*/	uint32 count_d60;
	/*d64,4*/	undefined4 field_d64;
	/*d68,4*/	HelpWindowFlags flags;
	/*d6c*/
};

struct HelpWindowInfoLevels // [LegoRR/HelpWindow.c|struct:0x40]
{
	/*00,40*/	char* levels[16];
	/*40*/
};

struct HiddenObject // [LegoRR/LegoObject.c|struct:0x2c] Name is only guessed
{
	/*00,8*/	Point2I blockPos; // (ol: xPos, yPos -> blockPos)
	/*08,8*/	Point2F worldPos; // (ol: xPos, yPos)
	/*10,4*/	real32 heading; // (ol: heading -> radians)
	/*14,4*/	void* model; // (ol: type)
	/*18,4*/	LegoObject_Type type; // (ol: type)
	/*1c,4*/	sint32 id; // (ol: type)
	/*20,4*/	real32 health; // (ol: health)
	/*24,4*/	char* olistID; // (ol: Object%i)
	/*28,4*/	char* olistDrivingID; // (ol: driving)
	/*2c*/
};

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

struct Image_Globs // [Gods98/Images.c|struct:0x8c|tags:GLOBS]
{
	/*00,80*/	Image* listSet[32]; // Images list
	/*80,4*/	Image* freeList;
	/*84,4*/	uint32 listCount; // number of lists.
	/*88,4*/	uint32 flags;
	/*8c*/
};

struct ImageCacheItem // [LegoRR/FrontEnd.c|struct:0x10] Cache for image/fonts loaded from menus
{
	/*00,4*/	char* filename;
	/*04,4*/	Image* image;
	/*08,4*/	Font* font;
	/*0c,4*/	ImageCacheItem* next;
	/*10*/
};

struct Info_Globs // [LegoRR/Info.c|struct:0x6f4|tags:GLOBS]
{
	/*000,a0*/	char* infoName[40];
	/*0a0,320*/	InfoData infoDataTable[40];
	/*3c0,320*/	InfoMessage infoMessageTable[40];
	/*6e0,4*/	uint32 infoMessageCount;
	/*6e4,4*/	Font* font;
	/*6e8,4*/	Image* OverFlowImage;
	/*6ec,4*/	sint32 int_6ec;
	/*6f0,4*/	InfoMessageFlags flags;
	/*6f4*/
};

struct InfoData // [LegoRR/Info.c|struct:0x14]
{
	/*00,4*/	char* text;
	/*04,4*/	void* ptr_4; // struct size of >= 0xc (int field_4, inf field_8)
	/*08,4*/	SFX_Type sfxType;
	/*0c,4*/	real32 float_c;
	/*10,4*/	InfoDataFlags flags;
	/*14*/
};

struct InfoMessage // [LegoRR/Info.c|struct:0x14]
{
	/*00,4*/	InfoMessageInstance* instance;
	/*04,4*/	uint32 instanceCount;
	/*08,4*/	Info_Type infoType;
	/*0c,4*/	real32 float_c;
	/*10,4*/	InfoMessage* next;
	/*14*/
};

struct InfoMessageInstance // [LegoRR/Info.c|struct:0x14]
{
	/*00,8*/	Point2I blockPos; // (-1, -1) for NULL blockPos
	/*08,4*/	LegoObject* object;
	/*0c,4*/	char* text;
	/*10,4*/	InfoMessageInstance* next;
	/*14*/
};

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

struct InterfaceMenuItem // [LegoRR/Interface.c|struct:0x8]
{
	/*0,4*/	Interface_MenuItem* iconList;
	/*4,4*/	uint32 numIcons;
	/*8*/
};

struct ItemStruct_34 // [LegoRR/???|struct:0x10]
{
	/*00,4*/	Mesh* mesh1;
	/*04,4*/	Mesh* mesh2;
	/*08,4*/	Container* cont;
	/*0c,4*/	real32 time;
	/*10*/
};

struct Key_Globs // [Gods98/Keys.c|struct:0x400|tags:GLOBS]
{
	/*000,400*/	char* keyName[256];
	/*400*/
};

#pragma pack(push, 1)
struct Lego_Block // [LegoRR/Lego.c|struct:0x48|pack:1]
{
	/*00,1*/	PredugType predug;
	/*01,1*/	SurfaceTexture texture;
	/*02,1*/	TerrainType terrain;
	/*03,1*/	uint8 direction; // clockwise (does not determine corner/wall type)
	/*04,1*/	uint8 blockpointer;
	/*05,1*/	CryOreType cryOre;
	/*06,1*/	ErodeType erodeSpeed;
	/*07,1*/	uint8 field_7;
	/*08,4*/	BlockFlags1 flags1;
	/*0c,4*/	BlockFlags2 flags2;
	/*10,4*/	BlockConstruction* construct;
	/*14,4*/	real32 damage; // drill damage [0.0-1.0]
	/*18,4*/	LevelStruct_1c* struct1c_18;
	/*1c,4*/	SurfaceMapStruct_2a8* smokeptr_1c;
	/*20,2*/	sint16 randomness;
	/*22,2*/	sint16 short_22; // (some num value, observed: != 4)
	/*24,4*/	uint32 numLandSlides;
	/*28,4*/	uint32 clickCount;
	/*2c,4*/	sint32 generateCrystals;
	/*30,4*/	sint32 generateOre;
	/*34,1*/	uint8 aiNode;
	/*35,3*/	undefined field_0x35_0x37[3];
	/*38,4*/	bool32 fallinUpper; // (fallin upper: 1 if fallin > 4)
	/*3c,4*/	sint32 fallinIntensity; // (fallin scale: 1-4)
	/*40,4*/	real32 fallinTimer; // (randomized with full fallin value)
	/*44,4*/	undefined4 field_44;
	/*48*/
};
#pragma pack(pop)

struct Lego_Globs // [LegoRR/Lego.c|struct:0xf00|tags:GLOBS]
{
	/*000,4*/	Config* config;
	/*004,4*/	char* gameName;
	/*008,4*/	undefined4 field_8;
	/*00c,4*/	undefined4 field_c;
	/*010,4*/	GraphicsQuality quality; // (cfg: Main::Quality)
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
	/*04c,4*/	Container* dirLightFPDefault;
	/*050,4*/	real32 FPClipBlocks; // (cfg: Main::FPClipBlocks)
	/*054,4*/	real32 TVClipDist; // (cfg: Main::TVClipDist)
	/*058,4*/	undefined4 field_58;
	/*05c,4*/	undefined4 field_5c;
	/*060,4*/	undefined4 field_60;
	/*064,4*/	Font* bmpFONT5_HI;
	/*068,4*/	Font* bmpToolTipFont;
	/*06c,4*/	Font* bmpDeskTopFont;
	/*070,4*/	Font* bmpfont5_HI;
	/*074,4*/	Font* bmpMbriefFONT;
	/*078,4*/	Font* bmpMbriefFONT2;
	/*07c,4*/	Font* bmpRSFont;
	/*080,4*/	TextWindow* textWnd_80;
	/*084,4*/	TextWindow* textWnd_84;
	/*088,10*/	Point2F gotoPositions_88[2];
	/*098,4*/	bool32 gotoBool_98;
	/*09c,4*/	real32 gameSpeed;
	/*0a0,4*/	LegoObject* objectFP;
	/*0a4,c*/	Vector3F vectorDragStartUnk_a4;
	/*0b0,4*/	real32 float_b0;
	/*0b4,4*/	real32 float_b4;
	/*0b8,4*/	real32 float_b8;
	/*0bc,4*/	real32 float_bc;
	/*0c0,8*/	Point2I pointi_c0;
	/*0c8,4*/	bool32 bool_c8;
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
	/*260,48*/	SFX_Type langSurface_sound[18]; // (cfg: SurfaceTypeDescriptions)
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
	/*334,4*/	real32 tvTiltOrZoom_334;
	/*338,8*/	Point2F tvFaceDirection_338;
	/*340,4*/	real32 MedPolyRange; // (cfg: Main::MedPolyRange)
	/*344,4*/	real32 HighPolyRange; // (cfg: Main::HighPolyRange)
	/*348,4*/	sint32 HPBlocks; // (cfg: Main::HPBlocks)
	/*34c,c*/	ColourRGBF FogColourRGB; // (cfg: Level::FogColourRGB)
	/*358,c*/	ColourRGBF HighFogColourRGB; // (cfg: Level::HighFogColourRGB)
	/*364,4*/	real32 float_364; // level-related?
	/*368,c*/	ColourRGBF PowerCrystalRGB; // (cfg: Main::PowerCrystalRGB)
	/*374,c*/	ColourRGBF UnpoweredCrystalRGB; // (cfg: Main::UnpoweredCrystalRGB)
	/*380,4*/	LegoObject_Type placeObjType;
	/*384,4*/	sint32 placeObjIndex;
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
	/*404,50*/	sint32 objTeleportQueueIndexes_TABLE[20];
	/*454,4*/	uint32 objTeleportQueue_COUNT;
	/*458,4*/	real32 MiniFigureRunAway; // (cfg: Main::MiniFigureRunAway)
	/*45c,c*/	Vector3F vector_45c;
	/*468,320*/	Point2I blockPts_468[100];
	/*788,4*/	uint32 blockPtsCount_788;
	/*78c,640*/	Point2I points2x100_78c[2][100];
	/*dcc,8*/	uint32 pointsCount2_dcc[2];
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
	/*e24,8*/	Point2F BackButtonPos; // (cfg: Main::BackButtonPos<WxH>)
	/*e2c,4*/	Image* NextButtonImage; // (cfg: Main::NextButton<WxH>)
	/*e30,4*/	Image* BackButtonImage; // (cfg: Main::BackButton<WxH>)
	/*e34,4*/	Image* BackArrowImage; // (cfg: Main::BackArrow<WxH>)
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
	/*ef8,8*/	Point2I s_mouseBlockPos_ef8; // (static, Game_unkGameLoop_FUN_00426450)
	/*f00*/
};

struct Lego_Level // [LegoRR/Lego.c|struct:0x284]
{
	/*000,4*/	char* name; // (format: "Levels::level")
	/*004,4*/	Map3D* map;
	/*008,4*/	EmergeTrigger* emergeTriggers;
	/*00c,4*/	uint32 emergeCount;
	/*010,4*/	undefined4 field_10;
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
	/*088,4*/	LevelStruct_1c* terrain1c_88;
	/*08c,4*/	sint32 numCrystals; // (init: 0) total number of crystals
	/*090,4*/	undefined4 field_90; // (init: 0)
	/*094,4*/	undefined4 field_94; // (init: 0)
	/*098,4*/	sint32 numUnusedCrystals; // crystals available for use (not powering buildings)
	/*09c,4*/	undefined4 field_9c;
	/*0a0,4*/	sint32 numOre; // (init: 0)
	/*0a4,4*/	undefined4 field_a4; // (init: 0)
	/*0a8,4*/	undefined4 field_a8; // (init: 0)
	/*0ac,4*/	sint32 numProcessedOre;
	/*0b0,4*/	sint32 EmergeCreature; // (searches for object index by name, expects RockMonsterType)
	/*0b4,4*/	char* nextLevel; // (cfg: NextLevel)
	/*0b8,4*/	Lego_Block* blocks; // grid of blocks [y][x]
	/*0bc,54*/	ObjectiveData objective;
	/*110,4*/	bool32 hasBlockPointers;
	/*114,e0*/	BlockPointer* blockPointers[56];
	/*1f4,4*/	bool32 StartFP;
	/*1f8,4*/	bool32 NoDrain;
	/*1fc,4*/	real32 oxygenLevel; // (init: 100.0, Oxygen level?)
	/*200,4*/	real32 OxygenRate;
	/*204,4*/	real32 float_204; // (init: 100.0, Oxygen level?)
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

struct LegoCamera // [LegoRR/LegoCamera.c|struct:0xbc] May be camera data (which is related to- but not the same as viewports)
{
	/*00,4*/	LegoCamera_Type type;
	/*04,4*/	LegoObject* trackObj;
	/*08,4*/	real32 trackRadarZoomSpeed;
	/*0c,4*/	real32 trackRadarZoom;
	/*10,4*/	real32 trackRadarRotationSpeed; // A constant yaw H rotation speed applied to tracked radar objects
	/*14,4*/	sint32 trackFPCameraFrame; // CameraFrameIndex for FP object SwapPolyFP
	/*18,c*/	Vector3F moveVector; // current 3D (really 2D) movement and directional speed
	/*24,4*/	Container* contCam; // only cont created for FP type (child of contRoot if FP)
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

struct LegoObject // [LegoRR/LegoObject.c|struct:0x40c|tags:LISTSET]
{
	/*000,4*/	LegoObject_Type type;
	/*004,4*/	sint32 id;
	/*008,4*/	char* customName; // max size is 11 (NOT null-terminated)
	/*00c,4*/	VehicleModel* vehicle;
	/*010,4*/	CreatureModel* miniFigure;
	/*014,4*/	CreatureModel* rockMonster;
	/*018,4*/	BuildingModel* building;
	/*01c,4*/	Container* other;
	/*020,4*/	Upgrade_PartModel* upgradePart; // First upgrade part model in linked list of parts.
	/*024,4*/	RoutingBlock* routeBlocks; // Unknown pointer, likely in large allocated table
	/*028,4*/	uint32 routeBlockTotal; // total blocks to travel for current route
	/*02c,4*/	uint32 routeBlockeCurrent; // number of blocks traveled (up to routingBlocksTotal)
	/*030,25c*/	BezierCurve routeCurve; // BezierCurve/Catmull-rom spline data
	/*28c,c*/	Vector3F vector_28c;
	/*298,8*/	Point2F point_298;
	/*2a0,c*/	Vector3F vector_2a0; // Used with faceDirection calculation.
	/*2ac,c*/	Vector3F faceDirection; // 1.0 to -1.0 directions that determine rotation with atan2
	/*2b8,4*/	real32 faceDirectionLength_2b8; // faceDirection length (faceDirection may be Vector4F...)
	/*2bc,4*/	sint32 strafeSignFP; // (direction sign only, does higher numbers do not affect speed)
	/*2c0,4*/	sint32 forwardSignFP; // (direction sign only, does higher numbers do not affect speed)
	/*2c4,4*/	real32 rotateSpeedFP;
	/*2c8,4*/	undefined4 field_2c8;
	/*2cc,4*/	undefined4 field_2cc;
	/*2d0,4*/	undefined4 field_2d0;
	/*2d4,4*/	real32 animTime;
	/*2d8,4*/	uint32 animRepeat; // Number of times an activity animation is set to repeat (i.e. number of jumping jacks/reinforce hits). Zero is default.
	/*2dc,4*/	Container* cont_2dc;
	/*2e0,4*/	sint32 index_2e0;
	/*2e4,4*/	Container* cont_2e4;
	/*2e8,4*/	char* activityName1;
	/*2ec,4*/	char* activityName2; // Seems to be used with related objects like driven, swapped with activityName1.
	/*2f0,4*/	AITask* aiTask;
	/*2f4,8*/	Point2F point_2f4; // (init: -1.0f, -1.0f)
	/*2fc,4*/	LegoObject* boulderObject; // other half of boulderHolderObject
	/*300,4*/	LegoObject* boulderHolderObject; // other half of boulderObject (todo: better name)
	/*304,4*/	LegoObject* carryingThisObject;
	/*308,1c*/	LegoObject* carriedObjects[7]; // (includes carried vehicles)
	/*324,4*/	uint32 numCarriedObjects;
	/*328,4*/	uint32 carryNullFrames;
	/*32c,4*/	Flocks* flocks;
	/*330,4*/	uint32 objLevel;
	/*334,4*/	ObjectStats* stats;
	/*338,4*/	real32 float_338;
	/*33c,4*/	real32 float_33c;
	/*340,4*/	real32 health; // (init: -1.0f)
	/*344,4*/	real32 energy; // (init: -1.0f)
	/*348,4*/	sint32* stealTableptr_348; // element size is 0x4
	/*34c,4*/	LOD_PolyLevel polyLOD;
	/*350,4*/	sint32 soundHandle_350;
	/*354,4*/	SFX_Type soundHandle_354; // (engine sound only?)
	/*358,4*/	undefined4 field_358;
	/*35c,4*/	undefined4 field_35c;
	/*360,4*/	undefined4 field_360;
	/*364,4*/	LegoObject* object_364;
	/*368,4*/	real32 float_368;
	/*36c,4*/	LegoObject* driveObject; // (bi-directional link between driver and driven)
	/*370,14*/	LegoObject_ToolType carriedTools[5];
	/*384,4*/	uint32 numCarriedTools;
	/*388,4*/	real32 float_388;
	/*38c,4*/	Image* bubbleImage;
	/*390,4*/	undefined4 teleporter_field_390;
	/*394,4*/	undefined4 teleporter_field_394;
	/*398,4*/	TeleporterService* teleporter;
	/*39c,4*/	undefined4 field_39c;
	/*3a0,4*/	undefined4 field_3a0;
	/*3a4,4*/	undefined4 field_3a4;
	/*3a8,4*/	undefined4 field_3a8;
	/*3ac,4*/	undefined4 field_3ac;
	/*3b0,4*/	undefined4 field_3b0;
	/*3b4,8*/	Point2F pushingVec2D;
	/*3bc,4*/	real32 pushingDist;
	/*3c0,4*/	LegoObject* throwObject; // (bi-directional link between thrower and thrown)
	/*3c4,4*/	LegoObject* object_3c4;
	/*3c8,4*/	undefined4 field_3c8;
	/*3cc,4*/	LegoObject* object_3cc;
	/*3d0,4*/	undefined4 field_3d0;
	/*3d4,4*/	real32 elapsedTime1; // elapsed time counter 1
	/*3d8,4*/	real32 elapsedTime2; // elapsed time counter 2
	/*3dc,4*/	real32 activityElapsedTime; // elapsed time since last order?
	/*3e0,4*/	LiveFlags1 flags1;
	/*3e4,4*/	LiveFlags2 flags2;
	/*3e8,4*/	LiveFlags3 flags3; // (assigned 0, flags?)
	/*3ec,4*/	LiveFlags4 flags4;
	/*3f0,4*/	LiveFlags5 flags5; // ability flags, and saved in ObjectRecall
	/*3f4,4*/	undefined4 field_3f4;
	/*3f8,4*/	undefined4 field_3f8;
	/*3fc,4*/	real32 floatSnd_3fc;
	/*400,4*/	real32 floatSnd_400;
	/*404,4*/	undefined4 field_404;
	/*408,4*/	LegoObject* nextFree; // (for listSet)
	/*40c*/
};

struct LegoObject_Globs // [LegoRR/LegoObject.c|struct:0xc644|tags:GLOBS]
{
	/*0000,80*/	LegoObject* listSet[32];
	/*0080,4*/	LegoObject* freeList;
	/*0084,4b0*/	SFX_Type objectTtSFX[20][15]; // [objType:20][objIndex:15] (cfg: ObjTtSFXs)
	/*0534,13c*/	char* activityName[79]; // [activityType:79]
	/*0670,4*/	void* UnkSurfaceGrid_1_TABLE;
	/*0674,4*/	void* UnkSurfaceGrid_2_TABLE;
	/*0678,4*/	uint32 UnkSurfaceGrid_COUNT;
	/*067c,4*/	real32 radarElapsed_67c;
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
	/*c018,4*/	real32 float_c018;
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
	/*c638,4*/	real32 LiveManager_TimerUnk;
	/*c63c,4*/	undefined4 s_stepCounter_c63c; // (static, counter %4 for step SFX)
	/*c640,4*/	void** s_FlocksDestroy_c640; // (static, Struct 0x10, used in Flocks activities (QUICK_DESTROY??))
	/*c644*/
};

struct LegoUpdate_Globs // [LegoRR/Lego.c|struct:0x14|tags:GLOBS] (miscellaneous static function variables used during game update loop)
{
	/*00,4*/	real32 renameInputTimer; // (ram: 12.5)
	/*04,4*/	real32 dripSFXTimer; // (ram: 75.0)
	/*08,4*/	real32 ambientSFXTimer; // (ram: 250.0)
	/*0c,4*/	real32 dbgRollOffFactorValue; // (ram: 1.0)
	/*10,4*/	real32 currentBaseLightLevel; // (ram: 0.7)
	/*14*/
};

struct LevelInfo // [LegoRR/FrontEnd.c|struct:0x14]
{
	/*00,4*/	sint32 index; // Index in LevelCollection
	/*04,4*/	LevelInfo** LevelLinks;
	/*08,4*/	uint32 NumLinks;
	/*0c,4*/	undefined4 field_c;
	/*10,4*/	undefined4 field_10; // (is locked/unlocked?)
	/*14*/
};

struct LevelSet // [LegoRR/FrontEnd.c|struct:0x14]
{
	/*00,4*/	sint32 count;
	/*04,4*/	char** LevelNames;
	/*08,4*/	char** FullNames;
	/*0c,4*/	LevelInfo** LevelList;
	/*10,4*/	bool32* IsLinked; // True if this level has been loaded from level links (probably makes them require unlock)
	/*14*/
};

struct LevelStruct_1c // [LegoRR/Lego.c|struct:0x1c] related to Terrain map?
{
	/*00,4*/	Container* resData;
	/*04,8*/	Point2I blockPos;
	/*0c,4*/	uint32 flags;
	/*10,4*/	LevelStruct_1c* next;
	/*14,4*/	LevelStruct_1c* previous;
	/*18,4*/	bool32 bool_18;
	/*1c*/
};

struct LightEffects_Globs // [LegoRR/LightEffects.c|struct:0xf4|tags:GLOBS] LightEffects module globals @004ebdd8
{
	/*00,4*/	Container* resSpotlight; // [Res+Move] init
	/*04,4*/	Container* resRootLight; // [Move] init
	/*08,c*/	ColourRGBF initialRGB; // [Color] init
	/*14,c*/	ColourRGBF currentRGB; // [Color+Blink+Fade] init+update
	/*20,c*/	ColourRGBF BlinkRGBMax; // [Blink] init
	/*2c,4*/	real32 blinkTime; // [Blink] update
	/*30,8*/	Range2F RandomRangeForTimeBetweenBlinks; // [Blink] init
	/*38,4*/	real32 blinkChange; // [Blink] update
	/*3c,4*/	real32 MaxChangeAllowed; // [Blink] init
	/*40,c*/	ColourRGBF fadeDestRGB; // [Fade] update
	/*4c,c*/	ColourRGBF FadeRGBMin; // [Fade] init
	/*58,c*/	ColourRGBF FadeRGBMax; // [Fade] init
	/*64,4*/	real32 fadeTime; // [Fade] update
	/*68,8*/	Range2F RandomRangeForTimeBetweenFades; // [Fade] init
	/*70,c*/	ColourRGBF fadeSpeedRGB; // [Fade] update
	/*7c,8*/	Range2F RandomRangeForFadeTimeFade; // [Fade] init
	/*84,4*/	real32 fadeHoldTime; // [Fade] update
	/*88,8*/	Range2F RandomRangeForHoldTimeOfFade; // [Fade] init
	/*90,c*/	ColourRGBF fadePosRGB; // [Fade] update
	/*9c,c*/	Vector3F resPosition; // [Move] init+update
	/*a8,c*/	Vector3F MoveLimit; // [Move] init
	/*b4,4*/	real32 moveTime; // [Move] update
	/*b8,8*/	Range2F RandomRangeForTimeBetweenMoves; // [Move] init
	/*c0,4*/	real32 moveSpeed; // [Move] update
	/*c4,8*/	Range2F RandomRangeForSpeedOfMove; // [Move] init
	/*cc,c*/	Vector3F vectorMove; // [Move] update
	/*d8,4*/	real32 moveDist; // [Move] update
	/*dc,8*/	Range2F RandomRangeForDistOfMove; // [Move] init
	/*e4,c*/	undefined1 reserved1[12]; // possibly an unused Vector3F/ColourRGBF
	/*f0,4*/	LightEffectsFlags flags; // [all] init+update
	/*f4*/
};

struct LiveObjectInfo // [LegoRR/search.c|struct:0x1c] This is some search info, that needs to be fixed up. Lot's of assumptions were made when creating this.
{
	/*00,4*/	LegoObject* liveObj;
	/*04,4*/	bool32 intbool_4;
	/*08,8*/	Point2F point_8;
	/*10,c*/	Vector3F vector_10;
	/*1c*/
};

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
	/*28c,4*/	LoaderFlags flags; // (1 = show loading bar)
	/*290*/
};

struct LoaderSection // [LegoRR/Loader.c|struct:0xc]
{
	/*0,4*/	char* name; // Name of the section files are being loaded from
	/*4,4*/	uint32 currentSize; // Current total size of files loaded for this section
	/*8,4*/	uint32 totalSize; // Predefined total "expected" size for files to load from this section
	/*c*/
};

struct LWPOLY // [Gods98/Lwt.c|struct:0xc]
{
	/*0,4*/	uint32 plyCount;
	/*4,4*/	uint32 plySurface;
	/*8,4*/	uint16* plyData;
	/*c*/
};

#pragma pack(push, 1)
struct LWRGB // [Gods98/Lwt.c|struct:0x4|pack:1] (an alias for ColourRGBAPacked)
{
	/*0,1*/	uint8 colRed;
	/*1,1*/	uint8 colGreen;
	/*2,1*/	uint8 colBlue;
	/*3,1*/	uint8 colAlpha;
	/*4*/
};
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

struct Lws_KeyInfo // [Gods98/Lws.c|struct:0x28]
{
	/*00,c*/	Vector3F position;
	/*0c,c*/	Vector3F hpb;
	/*18,c*/	Vector3F scale;
	/*24,2*/	uint16 frame;
	/*26,2*/	uint16 padding1;
	/*28*/
};

struct Lws_MeshPath // [Gods98/Lws.c|struct:0x8]
{
	/*0,4*/	char* path;
	/*4,4*/	Mesh* mesh;
	/*8*/
};

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

struct LWSIZE // [Gods98/Lwt.c|struct:0xc]
{
	/*0,4*/	uint32 lwVertCount;
	/*4,4*/	uint32 lwPolyCount;
	/*8,4*/	uint32 lwSurfaceCount;
	/*c*/
};

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

struct LWSURFLIST // [Gods98/Lwt.c|struct:0x8]
{
	/*0,4*/	uint32 srflCount;
	/*4,4*/	char** srflName;
	/*8*/
};

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

struct Main_State // [Gods98/Main.c|struct:0xc] (unrelated to Main_StateChangeData)
{
	/*0,4*/	MainStateInitialise Initialise;
	/*4,4*/	MainStateMainLoop MainLoop;
	/*8,4*/	MainStateShutdown Shutdown;
	/*c*/
};

struct Main_StateChangeData // [Gods98/Main.c|struct:0x8] The item's render state type is determined by the index in its table
{
	/*0,4*/	uint32 origValue; // not restricted to just uint value types, pointers, floats, signed ints, etc.
	/*4,4*/	bool32 changed;
	/*8*/
};

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
	/*73cc,4*/	Container* transMesh; // Mesh for Map3D_TransBlocks
	/*73d0,4*/	Map3DFlags flagsMap;
	/*73d4*/
};

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

#pragma pack(push, 2)
struct MapFileInfo // [LegoRR/dummy.c|struct:0x12|pack:2]
{
	/*00,4*/	char Signature[4]; // "MAP "
	/*04,4*/	uint32 fileSize;
	/*08,8*/	Size2I dimensions;
	/*10,2*/	uint16 blocks[1];
	/*12*/
};
#pragma pack(pop)

struct Matrix4F // [common.c|struct:0x40]
{
	/*00,40*/	real32 values[4][4];
	/*40*/
};

struct Mem_Globs // [Gods98/Memory.c|struct:0x3e84|tags:GLOBS]
{
	/*0000,3e80*/	Mem_Handle handleList[2000];
	/*3e80,4*/	uint32 flags; // (unused)
	/*3e84*/
};

struct Mem_Handle // [Gods98/Memory.c|struct:0x8]
{
	/*0,4*/	void* addr;
	/*4,4*/	Mem_HandleFlags flags; // 1 = isUsed
	/*8*/
};

struct Menu // [LegoRR/FrontEnd.c|struct:0xa0] A singular menu screen contained within a MenuSet structure.
{
	/*00,4*/	char* title; // (cfg: Menu::Title)
	/*04,4*/	char* fullName; // (cfg: Menu::FullName)
	/*08,4*/	uint32 titleLength; // (init: strlen(title))
	/*0c,4*/	Font* menuFont; // (cfg: Menu::MenuFont)
	/*10,4*/	Image* menuImage; // (cfg: Menu::MenuImage)
	/*14,4*/	Image* menuImageDark; // (cfg: Menu::MenuImageDark)
	/*18,4*/	MenuItem* items; // (cfg: Menu::Item1, Item2...)
	/*1c,4*/	sint32 itemCount; // (cfg: Menu::ItemCount) Number of used slots in items
	/*20,4*/	sint32 itemCapacity; // Total number of slots allocated in items
	/*24,4*/	sint32 itemFocus; // Index of item with keyboard focus
	/*28,4*/	bool32 bool_28;
	/*2c,8*/	Point2I position; // (cfg: Menu::Position)
	/*34,4*/	uint32 flags_34; // flags [0x1, 0x2, ...]
	/*38,8*/	Point2F currPosition;
	/*40,4*/	MenuOverlay* overlays; // (cfg: Menu::Overlay1, Overlay2...)
	/*44,4*/	bool32 autoCenter; // (cfg: Menu::AutoCenter)
	/*48,4*/	bool32 displayTitle; // (cfg: Menu::DisplayTitle)
	/*4c,4*/	bool32 anchored; // (cfg: Menu::Anchored)
	/*50,8*/	Point2I anchoredPosition; // (cfg: Menu::Anchored)
	/*58,4*/	sint32 flags_58; // (0x2 = CanScroll)
	/*5c,40*/	char name[64]; // Name of menu in Lego.cfg
	/*9c,4*/	BoolTri playRandom; // (cfg: Menu::PlayRandom)
	/*a0*/
};

struct MenuButton // [LegoRR/FrontEnd.c|struct:0x1c]
{
	/*00,10*/	Area2F window;
	/*10,4*/	Image* HiImage;
	/*14,4*/	Image* LoImage;
	/*18,4*/	char* Text;
	/*1c*/
};

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
	/*28,4*/	bool32 isImageItem; // (1 = hasImages?)
	/*2c,4*/	Image* imageLo;
	/*30,4*/	Image* imageHi;
	/*34,4*/	ToolTip_Type toolTipType;
	/*38,4*/	bool32 notInTuto; // (string value is unchecked, but "NotInTuto" is the only seen usage)
	/*3c*/
};

struct MenuItem_CycleData // [LegoRR/FrontEnd.c|struct:0x1c]
{
	/*00,4*/	char** nameList; // (cfg: Cycle:[7...])
	/*04,4*/	uint32 cycleCount;
	/*08,4*/	sint32 nameCount; // (cfg: Cycle:[6])
	/*0c,4*/	sint32* value;
	/*10,4*/	sint32 x2; // (cfg: Cycle:[3])
	/*14,4*/	sint32 y2; // (cfg: Cycle:[4])
	/*18,4*/	MenuItemCycleCallback callback;
	/*1c*/
};

struct MenuItem_LevelData // [LegoRR/FrontEnd.c|struct:0x20]
{
	/*00,4*/	uint32 flags; // [0x1 = print name over image, 0x2, 0x4]
	/*04,4*/	char* strImageNames; // memory allocation for cfg: Level::MenuBMP (needed for ImageCache)
	/*08,4*/	Image* imageHi; // (cfg: Level::MenuBMP[0])
	/*0c,4*/	Image* imageLo; // (cfg: Level::MenuBMP[1])
	/*10,4*/	Image* imageLockedOverlay; // (cfg: Level::MenuBMP[2])
	/*14,4*/	sint32 frontEndX; // (cfg: Level::FrontEndX)
	/*18,4*/	sint32 frontEndY; // (cfg: Level::FrontEndY)
	/*1c,4*/	bool32 frontEndOpen; // (cfg: Level::FrontEndOpen)
	/*20*/
};

struct MenuItem_LevelSelectData // [LegoRR/FrontEnd.c|struct:0x5c]
{
	/*00,4*/	MenuItem_LevelData* levelsList;
	/*04,c*/	sint32* widths[3];
	/*10,c*/	sint32* heights[3];
	/*1c,4*/	sint32 levelCount;
	/*20,4*/	char* string1;
	/*24,4*/	char* string2;
	/*28,4*/	sint32* value;
	/*2c,10*/	Area2I rect1;
	/*3c,10*/	Area2I rect2;
	/*4c,4*/	undefined4 field_4c;
	/*50,4*/	undefined4 field_50;
	/*54,4*/	pointer callback;
	/*58,4*/	undefined4 field_58;
	/*5c*/
};

struct MenuItem_RealSliderData // [LegoRR/FrontEnd.c|struct:0x1c]
{
	/*00,4*/	real32* value;
	/*04,4*/	real32 valueMin; // (cfg: RealSlider:[6])
	/*08,4*/	real32 valueMax; // (cfg: RealSlider:[7])
	/*0c,4*/	real32 valueStep; // (cfg: RealSlider:[8])
	/*10,4*/	sint32 x2; // (cfg: RealSlider:[3])
	/*14,4*/	sint32 y2; // (cfg: RealSlider:[4])
	/*18,4*/	MenuItemRealSliderCallback callback;
	/*1c*/
};

struct MenuItem_SliderData // [LegoRR/FrontEnd.c|struct:0x38]
{
	/*00,4*/	sint32* value;
	/*04,4*/	sint32 valueMin; // (cfg: Slider:[6])
	/*08,4*/	sint32 valueMax; // (cfg: Slider:[7])
	/*0c,4*/	sint32 x2; // (cfg: Slider:[3])
	/*10,4*/	sint32 y2; // (cfg: Slider:[4])
	/*14,4*/	MenuItemSliderCallback callback;
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

struct MenuItem_TriggerData // [LegoRR/FrontEnd.c|struct:0xc]
{
	/*0,4*/	sint32* value;
	/*4,4*/	bool32 end; // (cfg: Trigger:[4]) End/close the current MenuSet
	/*8,4*/	MenuItemTriggerCallback callback;
	/*c*/
};

struct MenuItemCallbackPair // [LegoRR/dummy.c|struct:0x8]
{
	/*0,4*/	void* value;
	/*4,4*/	void* callback;
	/*8*/
};

struct MenuOverlay // [LegoRR/FrontEnd.c|struct:0x20]
{
	/*00,4*/	char* filename;
	/*04,4*/	sint32 overlayType; // (bmp, avi, lws, flh?)
	/*08,4*/	undefined4 field_8;
	/*0c,8*/	Point2I position;
	/*14,4*/	SFX_Type sfxType;
	/*18,4*/	MenuOverlay* previous;
	/*1c,4*/	undefined4 field_1c;
	/*20*/
};

struct MenuSet // [LegoRR/FrontEnd.c|struct:0x8] A collection of menus that may interact with one another (i.e. MainMenuFull, PausedMenu)
{
	/*0,4*/	Menu** menus; // (cfg: MenuSet::Menu1, Menu2...)
	/*4,4*/	uint32 menuCount; // (cfg: MenuSet::MenuCount)
	/*8*/
};

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

struct Mesh_PostRenderInfo // [Gods98/Mesh.c|struct:0x48]
{
	/*00,4*/	Mesh* mesh;
	/*04,40*/	Matrix4F matWorld;
	/*44,4*/	Mesh_PostRenderInfo* next;
	/*48*/
};

struct Mesh_RenderDesc // [Gods98/Mesh.c|struct:0xc]
{
	/*0,4*/	MeshRenderCallback renderCallback;
	/*4,4*/	void* renderCallbackData;
	/*8,4*/	uint32 renderFlags; // determines a lot of render states
	/*c*/
};

struct Mesh_TextureReference // [Gods98/Mesh.c|struct:0xc]
{
	/*0,4*/	IDirectDrawSurface4* surface;
	/*4,4*/	char* path;
	/*8,4*/	bool32 trans;
	/*c*/
};

struct Mesh_Vertex // [Gods98/Mesh.c|struct:0x20] Untransformed/unlit vertices
{
	/*00,c*/	Vector3F position; // Homogeneous coordinates
	/*0c,c*/	Vector3F normal; // Normal
	/*18,4*/	real32 tu; // Texture coordinates
	/*1c,4*/	real32 tv; // Texture coordinates
	/*20*/
};

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

struct Message_Globs // [LegoRR/Message.c|struct:0x14380|tags:GLOBS]
{
	/*00000,14000*/	MessageAction messageTableX2[2][2048];
	/*14000,8*/	uint32 messageCountX2[2];
	/*14008,4*/	bool32 messageX2Bool;
	/*1400c,190*/	LegoObject* selectedUnitList[100];
	/*1419c,a*/	KeysByte hotkeyList[10];
	/*141a6,2*/	undefined2 padding1;
	/*141a8,c8*/	MessageAction hotkeyMessages[10];
	/*14270,104*/	char* messageName[65];
	/*14374,4*/	undefined4 reserved1;
	/*14378,4*/	uint32 selectedUnitCount;
	/*1437c,4*/	uint32 hotkeyCount;
	/*14380*/
};

struct MessageAction // [LegoRR/Message.c|struct:0x14]
{
	/*00,4*/	Message_Type event;
	/*04,4*/	LegoObject* argumentObj; // (this argument is only used for live objects, but it's not necessarily true that it's the same in source)
	/*08,4*/	undefined4 argument2; // (this can be any types, and depends on the message)
	/*0c,8*/	Point2I position;
	/*14*/
};

struct NERPMessageSound // [LegoRR/NERPs.c|struct:0x8]
{
	/*0,4*/	char* key;
	/*4,4*/	sint32 sampleIndex;
	/*8*/
};

struct NERPsFile_Globs // [LegoRR/NERPs.c|struct:0xb4|tags:GLOBS]
{
	/*00,4*/	bool32 Camera_IsLockedOn;
	/*04,4*/	LegoObject* Camera_LockedOnTarget;
	/*08,8*/	Point2I pointi_8;
	/*10,4*/	LegoObject* object_10;
	/*14,4*/	bool32 bool_14;
	/*18,4*/	real32 float_18;
	/*1c,4*/	real32 float_1c;
	/*20,4*/	bool32 bool_20;
	/*24,4*/	real32 float_24;
	/*28,4*/	real32 float_28;
	/*2c,4*/	void* fileData;
	/*30,4*/	uint32 fileSize;
	/*34,2c*/	undefined4 reserved1[11];
	/*60,4*/	char* messageBuffer;
	/*64,4*/	uint32 messageLineCount;
	/*68,4*/	char** messageLineList;
	/*6c,4*/	uint32 messageCount;
	/*70,4*/	void* messageList;
	/*74,4*/	uint32 soundCount;
	/*78,4*/	NERPMessageSound* soundList;
	/*7c,4*/	undefined4 soundsUNKCOUNT;
	/*80,4*/	undefined4 field_80;
	/*84,4*/	undefined4 field_84;
	/*88,4*/	undefined4 field_88;
	/*8c,4*/	undefined4 field_8c;
	/*90,4*/	undefined4 field_90;
	/*94,4*/	undefined4 field_94;
	/*98,4*/	undefined4 field_98;
	/*9c,4*/	undefined4 field_9c;
	/*a0,4*/	uint32 uint_a0;
	/*a4,4*/	sint32 int_a4; // (signedness known due to constant comparison)
	/*a8,4*/	uint32 uint_a8;
	/*ac,4*/	sint32 RecordObjectPointer;
	/*b0,4*/	bool32 AdvisorTalkingMode;
	/*b4*/
};

struct NERPsFunctionSignature // [LegoRR/NERPs.c|struct:0xc]
{
	/*0,4*/	char* name;
	/*4,4*/	NERPsFunction function;
	/*8,4*/	NERPsFunctionArgs arguments;
	/*c*/
};

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

struct ObjectiveData // [LegoRR/???|struct:0x54]
{
	/*00,4*/	Image* ObjectiveImage; // bmp
	/*04,8*/	Point2F ObjectiveImagePosition;
	/*0c,4*/	Image* ObjectiveAcheivedImage; // bmp
	/*10,8*/	Point2F ObjectiveAcheivedImagePosition;
	/*18,4*/	Image* ObjectiveFailedImage; // bmp
	/*1c,8*/	Point2F ObjectiveFailedImagePosition;
	/*24,4*/	char* ObjectiveAcheivedAVIFilename; // filename
	/*28,8*/	Point2F ObjectiveAcheivedAVIPosition;
	/*30,4*/	undefined4 field_30;
	/*34,4*/	undefined4 field_34;
	/*38,4*/	uint32 CrystalObjective; // number of crystals needed if non-zero
	/*3c,4*/	uint32 OreObjective; // number of ore needed if non-zero
	/*40,8*/	Point2I BlockObjective;
	/*48,4*/	real32 TimerObjective; // (mult: 25.0, flags, format: "time:HitTimeFailObjective")
	/*4c,4*/	LegoObject_Type ConstructionObjectiveObjType;
	/*50,4*/	sint32 ConstructionObjectiveObjIndex;
	/*54*/
};

struct ObjectRecall_Globs // [LegoRR/ObjectRecall.c|struct:0x18|tags:GLOBS]
{
	/*00,4*/	SaveObjectRecall* recallList;
	/*04,4*/	uint32 recallUsed;
	/*08,4*/	uint32 recallCapacity;
	/*0c,4*/	SaveObjectRecall* recallNewList;
	/*10,4*/	uint32 recallNewCount;
	/*14,4*/	bool32 loaded;
	/*18*/
};

struct ObjectStats // [LegoRR/Stats.c|struct:0x150]
{
	/*000,4*/	undefined4 field_0;
	/*004,4*/	undefined4 field_4;
	/*008,4*/	undefined4 field_8;
	/*00c,4*/	undefined4 field_c;
	/*010,4*/	undefined4 field_10;
	/*014,4*/	undefined4 field_14;
	/*018,4*/	undefined4 field_18;
	/*01c,4*/	undefined4 field_1c;
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
	/*0c0,4*/	SFX_Type DrillSound; // (from: FUN_00464f30, invalid: 2 "SFX_Drill")
	/*0c4,4*/	SFX_Type DrillFadeSound; // (from: FUN_00464f30, invalid: 3 "SFX_DrillFade")
	/*0c8,4*/	SFX_Type EngineSound; // (from: FUN_00464f30, invalid: 0 "SFX_Bodge")
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
	/*104,4*/	undefined4 field_104;
	/*108,4*/	undefined4 field_108;
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

struct ObjInfo_Globs // [LegoRR/ObjInfo.c|struct:0x78|tags:GLOBS]
{
	/*00,4*/	ObjInfoFlags flags;
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
	/*72c,4*/	bool32 airMeterUnkBeatBool;
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
	/*780,4*/	uint32 flags;
	/*784,4*/	undefined4 reserved;
	/*788,30*/	uint32 s_crystalShifts[2][6]; // static function variable for delayed change in crystal meter
	/*7b8*/
};

struct PanelData // [LegoRR/Panels.c|struct:0x30]
{
	/*00,4*/	Image* imageOrFlic;
	/*04,4*/	bool32 isFlic;
	/*08,8*/	Point2F xyOut;
	/*10,8*/	Point2F xyIn;
	/*18,8*/	Point2F xyOutIn;
	/*20,4*/	undefined4 field_20;
	/*24,4*/	void* buttonList;
	/*28,4*/	uint32 buttonCount;
	/*2c,4*/	uint32 flags;
	/*30*/
};

struct PanelTextWindow // [LegoRR/Panels.c|struct:0x10] A Panel-based wrapper around the TextWindow class
{
	/*00,4*/	TextWindow* textWindow;
	/*04,8*/	Point2F position;
	/*0c,4*/	PanelData* panel;
	/*10*/
};

struct Point2F // [common.c|struct:0x8] also Vector2F
{
	/*0,4*/	real32 x;
	/*4,4*/	real32 y;
	/*8*/
};

struct Point2I // [common.c|struct:0x8]
{
	/*0,4*/	sint32 x;
	/*4,4*/	sint32 y;
	/*8*/
};

struct Pointer_Globs // [LegoRR/Pointer.c|struct:0x468|tags:GLOBS]
{
	/*000,4*/	Pointer_Type currentType;
	/*004,e0*/	Image* pointerImages[56]; // (each item is either an ImageBMP or ImageFlic)
	/*0e4,e0*/	bool32 pointerIsFlic[56];
	/*1c4,1c0*/	Point2I pointerFlicPositions[56];
	/*384,e0*/	char* pointerName[56];
	/*464,4*/	real32 timer; // Countdown timer to change pointer(?)
	/*468*/
};

struct Priorities_Globs // [LegoRR/Priorities.c|struct:0x4c0|tags:GLOBS]
{
	/*000,6c*/	char* priorityText[27];
	/*06c,6c*/	Image* priorityImage[27];
	/*0d8,6c*/	Image* priorityPressImage[27];
	/*144,6c*/	Image* priorityOffImage[27];
	/*1b0,6c*/	SFX_Type prioritySFX[27];
	/*21c,6c*/	AI_Priority priorityTypeTable_1[27];
	/*288,d8*/	Point2F priorityPoints[27];
	/*360,6c*/	AI_Priority priorityTypeTable_2[27];
	/*3cc,6c*/	undefined4 priorityUnk[27];
	/*438,6c*/	bool32 priorityActive[27];
	/*4a4,4*/	uint32 count;
	/*4a8,4*/	real32 float_4a8;
	/*4ac,4*/	real32 float_4ac;
	/*4b0,4*/	real32 float_4b0;
	/*4b4,4*/	real32 float_4b4;
	/*4b8,4*/	undefined4 field_4b8;
	/*4bc,4*/	uint32 flags;
	/*4c0*/
};

struct PTL_Globs // [LegoRR/PTL.c|struct:0x144|tags:GLOBS]
{
	/*000,140*/	PTL_Property table[40];
	/*140,4*/	uint32 count;
	/*144*/
};

struct PTL_Property // [LegoRR/PTL.c|struct:0x8] Property loaded from a level's PTL config file (contains lookup index for actions)
{
	/*0,4*/	Message_Type eventIndex;
	/*4,4*/	Message_Type actionIndex;
	/*8*/
};

struct RadarMap // [LegoRR/RadarMap.c|struct:0x3c]
{
	/*00,4*/	Map3D* surfMap;
	/*04,10*/	Area2F screenRect;
	/*14,4*/	real32 arrowTiltOrZoom;
	/*18,4*/	real32 BlockSize;
	/*1c,8*/	Point2F arrowPos;
	/*24,10*/	Area2F worldRect;
	/*34,4*/	Draw_Rect* drawRectList;
	/*38,4*/	uint32 drawRectCount;
	/*3c*/
};

struct RadarMap_Globs // [LegoRR/RadarMap.c|struct:0x3f4|tags:GLOBS]
{
	/*000,168*/	ColourRGBF colourTable[30]; // (constant, RGBf [0,255] -> [0,1] on RadarMap_Initialise)
	/*168,4*/	sint32 strucfUnkInt_1; // (init: -1)
	/*16c,4*/	sint32 strucfUnkInt_2; // (init: -1)
	/*170,140*/	RadarStructF_10 structfTable_1[20];
	/*2b0,140*/	RadarStructF_10 structfTable_2[20];
	/*3f0,4*/	uint32 structfCount;
	/*3f4*/
};

struct RadarStructF_10 // [LegoRR/RadarMap.c|struct:0x10]
{
	/*00,4*/	real32 width; // [0,1] as ratio of appWidth
	/*04,4*/	real32 height; // [0,1] as ratio of appHeight
	/*08,4*/	undefined4 field_8;
	/*0c,4*/	real32 float_c; // (init: 1.0)
	/*10*/
};

struct Range2F // [common.c|struct:0x8]
{
	/*0,4*/	real32 min;
	/*4,4*/	real32 max;
	/*8*/
};

struct Area2F // [common.c|struct:0x10]
{
	/*00,4*/	real32 left;
	/*04,4*/	real32 top;
	/*08,4*/	real32 right;
	/*0c,4*/	real32 bottom;
	/*10*/
};

struct Area2I // [common.c|struct:0x10]
{
	/*00,4*/	sint32 left;
	/*04,4*/	sint32 top;
	/*08,4*/	sint32 right;
	/*0c,4*/	sint32 bottom;
	/*10*/
};

struct Reward_Globs // [LegoRR/Rewards.c|struct:0x3250|tags:GLOBS]
{
	/*0000,4*/	bool32 Display; // is the rewards screen shown on mission end?
	/*0004,4*/	bool32 CenterText;
	/*0008,4*/	undefined4 reserved1;
	/*000c,4*/	real32 Timer;
	/*0010,4*/	RewardLevel* base; // base reward state template
	/*0014,4*/	RewardLevel* level; // level requirements reward state
	/*0018,4*/	Image* Wallpaper;
	/*001c,318c*/	RewardLevel current; // current reward state, modified during gameplay
	/*31a8,4*/	real32 ScrollSpeed;
	/*31ac,4*/	real32 VertSpacing;
	/*31b0,c*/	undefined4 padding2[3];
	/*31bc,4*/	char* FontName;
	/*31c0,4*/	Font* Font;
	/*31c4,4*/	char* TitleFontName;
	/*31c8,4*/	Font* TitleFont;
	/*31cc,4*/	char* BackFontName;
	/*31d0,4*/	Font* BackFont;
	/*31d4,4*/	Config* cfgRoot;
	/*31d8,4*/	char* gameName;
	/*31dc,4*/	RewardScroll* scroll;
	/*31e0,8*/	Point2F SaveButtonPosition;
	/*31e8,4*/	Image* SaveButton;
	/*31ec,4*/	Image* SaveButton_hi;
	/*31f0,4*/	Image* SaveButton_in;
	/*31f4,4*/	Image* SaveButton_dim;
	/*31f8,8*/	Point2F AdvanceButtonPosition;
	/*3200,4*/	Image* AdvanceButton;
	/*3204,4*/	Image* AdvanceButton_hi;
	/*3208,4*/	Image* AdvanceButton_in;
	/*320c,4*/	Image* AdvanceButton_dim;
	/*3210,4*/	char* CompleteText;
	/*3214,4*/	char* FailedText;
	/*3218,4*/	char* QuitText;
	/*321c,8*/	Point2I TextPos;
	/*3224,20*/	char StatusMessage[32];
	/*3244,4*/	bool32 DisplayText;
	/*3248,4*/	bool32 DisplayImages;
	/*324c,4*/	bool32 DisplayFlics;
	/*3250*/
};

struct RewardBuildingCounts // [LegoRR/Rewards.c|struct:0x198]
{
	/*000,190*/	char* nameTable[100];
	/*190,4*/	uint32 count;
	/*194,4*/	uint32 numPrevLevels_unk;
	/*198*/
};

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

struct RoofBlock // [LegoRR/Roof.c|struct:0x8] Mesh group for a single block in the world's roof. (only used for FP)
{
	/*0,4*/	D3DRMGroupIndex groupID;
	/*4,4*/	RoofFlags flags; // (0x1 = hidde, 0x2 = needsUpdate, 0x4 = shiftVertices)
	/*8*/
};

struct RoutingBlock // [LegoRR/Routing.c|struct:0x14]
{
	/*00,8*/	Point2I blockPos;
	/*08,8*/	Point2F worldPos;
	/*10,1*/	RouteFlags flagsByte;
	/*11,1*/	RouteAction actionByte;
	/*12,2*/	undefined field_0x12_0x13[2];
	/*14*/
};

struct RROSFileHeader // [LegoRR/ObjectRecall.c|struct:0x8] For .osf Object Recall save files
{
	/*0,4*/	char signature[4];
	/*4,4*/	uint32 count;
	/*8*/
};

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

struct SaveObjectRecall // [LegoRR/ObjectRecall.c|struct:0x14] Object recall structure (for .osf file)
{
	/*00,4*/	LiveFlags5 flags5;
	/*04,4*/	uint32 level;
	/*08,c*/	char customName[12];
	/*14*/
};

struct SaveStruct_18 // [LegoRR/save.c|struct:0x18]
{
	/*00,18*/	undefined field_0x0_0x17[24];
	/*18*/
};

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

struct ScrollInfoSubStruct_1c // [LegoRR/ScrollInfo.c|struct:0x1c]
{
	/*00,8*/	Point2F point1;
	/*08,8*/	Point2F point2;
	/*10,4*/	Image* image1;
	/*14,4*/	Image* image2;
	/*18,4*/	uint32 flags;
	/*1c*/
};

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

struct SearchAddCryOre_c // [LegoRR/search.c|struct:0xc]
{
	/*0,4*/	undefined4 field_0;
	/*4,4*/	uint32 crystalCount;
	/*8,4*/	uint32 oreCount; // normal ore
	/*c*/
};

struct SearchCollision_14 // [LegoRR/search.c|struct:0x14] LiveObject_DoCollisionCallbacks_FUN_00446030
{
	/*00,4*/	LegoObject* targetObj;
	/*04,4*/	Point2F* pointf_4;
	/*08,4*/	real32 float_8;
	/*0c,4*/	LegoObject* result;
	/*10,4*/	bool32 bool_10;
	/*14*/
};

struct SearchData18_2 // [LegoRR/search.c|struct:0x18]
{
	/*00,4*/	undefined4 field_0;
	/*04,4*/	real32 ref_float_4;
	/*08,4*/	Vector3F* vectorp_8;
	/*0c,4*/	Vector3F* vectorp_c;
	/*10,4*/	bool32 field_10;
	/*14,4*/	undefined4 field_14;
	/*18*/
};

struct SearchDynamiteRadius // [LegoRR/search.c|struct:0x18]
{
	/*00,4*/	LegoObject* liveObj;
	/*04,8*/	Point2F position;
	/*0c,4*/	real32 damageRadius;
	/*10,4*/	real32 maxDamage;
	/*14,4*/	real32 wakeRadius;
	/*18*/
};

struct SearchInfoBlockPos_8 // [LegoRR/search.c|struct:0x8]
{
	/*0,4*/	Point2I* pBlockPos;
	/*4,4*/	uint32 index;
	/*8*/
};

struct SearchInfoObject_8 // [LegoRR/search.c|struct:0x8]
{
	/*0,4*/	LegoObject* object;
	/*4,4*/	uint32 index;
	/*8*/
};

struct SearchInfoObjectBlockPos_8 // [LegoRR/search.c|struct:0x8]
{
	/*0,4*/	LegoObject* optObject;
	/*4,4*/	Point2I* optBlockPos;
	/*8*/
};

struct SearchLevelIdentifier_10 // [LegoRR/search.c|struct:0x10]
{
	/*00,4*/	LevelInfo* result; // output level identifier (not modified on failure)
	/*04,4*/	sint32 searchIndex; // (target index to search for)
	/*08,4*/	sint32 currentIndex; // (counter index of individual linked levels)
	/*0c,4*/	sint32 resultIndex; // (equal to searchIndex on success)
	/*10*/
};

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

struct SearchObjectTypeCount_c // [LegoRR/search.c|struct:0xc]
{
	/*0,4*/	LegoObject_Type objType;
	/*4,4*/	sint32 objIndex;
	/*8,4*/	uint32 count;
	/*c*/
};

struct SearchRadarObjectRadius_10 // [LegoRR/search.c|struct:0x10]
{
	/*00,4*/	LegoObject* object;
	/*04,8*/	Point2F worldPos;
	/*0c,4*/	real32 radius; // BlockSize -or- (BlockSize / 6.0)
	/*10*/
};

struct SearchTeleporter_10 // [LegoRR/search.c|struct:0x10] Teleporter_Creat_FUN_0046a7d0
{
	/*00,4*/	LegoObject_Type objType;
	/*04,4*/	uint32 modeFlags;
	/*08,4*/	uint32 teleportFlags;
	/*0c,4*/	TeleporterService* teleporter;
	/*10*/
};

struct SearchViewportWindow_14 // [LegoRR/search.c|struct:0x14]
{
	/*00,4*/	Viewport* view;
	/*04,8*/	Point2F dragStart;
	/*0c,8*/	Point2F dragEnd;
	/*14*/
};

struct SelectPlace // [LegoRR/SelectPlace.c|struct:0x8] Building selection highlight shown on map when placing
{
	/*0,4*/	Container* contMesh;
	/*4,4*/	real32 floatValue; // (init: 5.0)
	/*8*/
};

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
	/*16c4,4*/	SFX_Type globalSampleSFXType;
	/*16c8,28*/	SFX_Type soundQueueSFXTable_1[10];
	/*16f0,28*/	SoundMode soundQueueModesTable_1[10];
	/*1718,28*/	SFX_Type soundQueueSFXTable_2[10];
	/*1740,28*/	SoundMode soundQueueModesTable_2[10];
	/*1768,4*/	uint32 soundQueueCount_1;
	/*176c,4*/	uint32 soundQueueCount_2;
	/*1770*/
};

struct SFX_Instance // [LegoRR/SFX.c|struct:0x18]
{
	/*00,4*/	sint32 sampleIndex;
	/*04,4*/	IDirect3DRMFrame3* frame; // what happened to hiding D3DRM behind Containers and 3DSound?
	/*08,c*/	Vector3F position;
	/*14,4*/	SFX_InstanceFlags flags;
	/*18*/
};

struct SFX_Property // [LegoRR/SFX.c|struct:0x8]
{
	/*0,4*/	sint32 sound3DHandle;
	/*4,4*/	SFX_Property* next; // next group property
	/*8*/
};

struct Size2F // [common.c|struct:0x8]
{
	/*0,4*/	real32 width;
	/*4,4*/	real32 height;
	/*8*/
};

struct Size2I // [common.c|struct:0x8]
{
	/*0,4*/	sint32 width;
	/*4,4*/	sint32 height;
	/*8*/
};

struct Smoke_Globs // [LegoRR/Smoke.c|struct:0x34|tags:GLOBS]
{
	/*00,28*/	Container_Texture* textureList[10];
	/*28,4*/	SurfaceMapStruct_2a8* firstSmoke; // A doublely-linked list, each node has next/previous as well
	/*2c,4*/	SurfaceMapStruct_2a8* lastSmoke;
	/*30,4*/	uint32 count;
	/*34*/
};

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

struct Sound3D_SoundFrameRecord // [Gods98/3DSound.c|struct:0x14]
{
	/*00,4*/	IDirectSound3DBuffer* sound3DBuff;
	/*04,c*/	Vector3F pos;
	/*10,4*/	Sound3D_SoundFrameRecord* next;
	/*14*/
};

struct Sound3D_SoundRecord // [Gods98/3DSound.c|struct:0x10]
{
	/*00,4*/	IDirect3DRMFrame3* frame;
	/*04,4*/	IDirectSoundBuffer* soundBuff;
	/*08,4*/	IDirectSound3DBuffer* sound3DBuff;
	/*0c,4*/	Sound3D_SoundRecord* next;
	/*10*/
};

struct Sound3D_StreamData // [Gods98/3DSound.c|struct:0x5c]
{
	/*00,4*/	bool32 fileOpen; // paused/playing/used?
	/*04,54*/	Sound3D_WaveData wiWave;
	/*58,4*/	bool32 playing; // paused/playing/used?
	/*5c*/
};

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

struct SpiderWeb_Globs // [LegoRR/SpiderWeb.c|struct:0x8|tags:GLOBS]
{
	/*0,4*/	BlockSpiderWeb* webBlocks;
	/*4,4*/	Lego_Level* level;
	/*8*/
};

struct Stats_Globs // [LegoRR/Stats.c|struct:0x5b0|tags:GLOBS]
{
	/*000,50*/	ObjectStats** objectStats[20]; // [objType:20][*objIndex][*objLevel]
	/*050,4b0*/	uint32 objectLevels[20][15]; // [objType:20][objIndex:15]
	/*500,b0*/	ToolStats toolStats[11]; // [toolType:11]
	/*5b0*/
};

struct Struct_2b0 // [LegoRR/Weapons.c|struct:0x2b0] Seen in a table of [10]. This is likely an extension of the Weapons module.
{
	/*000,4*/	undefined4 unseen_0;
	/*004,25c*/	BezierCurve routing;
	/*260,4*/	undefined4 unseen_260;
	/*264,4*/	real32 float_264;
	/*268,c*/	Vector3F vector_268;
	/*274,c*/	Vector3F vector_274;
	/*280,c*/	Vector3F position_280;
	/*28c,4*/	real32 float_28c;
	/*290,c*/	Vector3F vector_290;
	/*29c,4*/	undefined4 field_29c;
	/*2a0,4*/	undefined4 field_2a0;
	/*2a4,4*/	LegoObject* object_2a4;
	/*2a8,4*/	sint32 weaponType;
	/*2ac,4*/	undefined4 field_2ac;
	/*2b0*/
};

struct SurfaceMapStruct_2a8 // [LegoRR/Map3D.c|struct:0x2a8]
{
	/*000,258*/	SurfaceMapStruct_3c groupList[10];
	/*258,4*/	real32 float_258;
	/*25c,c*/	Vector3F vector_25c;
	/*268,c*/	Vector3F vector_268;
	/*274,c*/	ColourRGBF colour;
	/*280,4*/	uint32 groupCount;
	/*284,4*/	sint32 int_284;
	/*288,4*/	real32 float_288;
	/*28c,4*/	Container* resData_28c;
	/*290,4*/	Mesh* mesh;
	/*294,4*/	SurfaceMapStruct2A8Flags flags_294;
	/*298,4*/	SurfaceMapStruct_2a8* next;
	/*29c,4*/	SurfaceMapStruct_2a8* previous;
	/*2a0,4*/	undefined4 field_2a0;
	/*2a4,4*/	sint32 soundHandle;
	/*2a8*/
};

struct SurfaceMapStruct_3c // [LegoRR/Map3D.c|struct:0x3c]
{
	/*00,4*/	bool32 used_0;
	/*04,c*/	Vector3F vector_4;
	/*10,c*/	Vector3F vector_10;
	/*1c,c*/	Vector3F vector_1c;
	/*28,4*/	real32 float_28;
	/*2c,4*/	real32 float_2c;
	/*30,4*/	real32 float_30; // timer
	/*34,4*/	sint32 int_34; // (std::rand() % 30) + 40
	/*38,4*/	undefined4 field_38;
	/*3c*/
};

struct Teleporter_Globs // [LegoRR/Teleporter.c|struct:0x10|tags:GLOBS]
{
	/*00,4*/	uint32 count;
	/*04,4*/	sint32 intValue_40; // (const: 40)
	/*08,4*/	TeleporterService* current;
	/*0c,4*/	real32 floatValue_3_0; // (const: 3.0)
	/*10*/
};

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

struct TEXDATA // [Gods98/Lwt.c|struct:0xc] (an alias for Vector3F)
{
	/*0,4*/	real32 tdX;
	/*4,4*/	real32 tdY;
	/*8,4*/	real32 tdZ;
	/*c*/
};

struct Text_Globs // [LegoRR/Text.c|struct:0x4dc|tags:GLOBS]
{
	/*000,68*/	char* textName[26];
	/*068,68*/	char* textMessages[26];
	/*0d0,68*/	Image* textImages[26];
	/*138,340*/	char textImagesSFX[26][32];
	/*478,4*/	Text_Type currentType;
	/*47c,4*/	uint32 textCount;
	/*480,4*/	uint32 textFlags;
	/*484,4*/	undefined4 field_484;
	/*488,4*/	real32 float_488;
	/*48c,4*/	TextWindow* textWnd_48c;
	/*490,4*/	TextWindow* textWnd_490;
	/*494,4*/	undefined4 reserved1;
	/*498,4*/	uint32 uint_498;
	/*49c,10*/	Area2F MsgPanel_Rect1;
	/*4ac,4*/	real32 float_4ac;
	/*4b0,4*/	real32 MsgPanel_Float20;
	/*4b4,4*/	real32 MsgPanel_Float42;
	/*4b8,4*/	real32 float_4b8;
	/*4bc,10*/	Area2F MsgPanel_Rect2;
	/*4cc,8*/	Point2I TextImagePosition;
	/*4d4,4*/	uint32 TextPanelFlags;
	/*4d8,4*/	real32 TextPauseTime;
	/*4dc*/
};

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

struct ToolStats // [LegoRR/Stats.c|struct:0x10]
{
	/*00,c*/	AITask_Type taskTypes[3]; // Up to 3 AITaskTypes can be associated with a tool
	/*0c,4*/	uint32 taskCount;
	/*10*/
};

struct ToolTip_Globs // [LegoRR/ToolTip.c|struct:0x61c4|tags:GLOBS]
{
	/*0000,4*/	Font* font; // (init only)
	/*0004,4*/	uint32 fontHeight; // (init only)
	/*0008,4*/	uint32 int2_8; // (init only)
	/*000c,4*/	sint32 int1_c; // (init only)
	/*0010,4*/	uint32 width; // (init only)
	/*0014,4*/	uint32 height; // (init only)
	/*0018,4*/	sint32 int32_18; // (init only)
	/*001c,4*/	real32 hoverTime; // Duration before showing tooltip  (init only)
	/*0020,24*/	real32 rgbFloats[9]; // [r:g:b(3)][norm:hi:lo(3)]  (init only)
	/*0044,9c*/	char* toolTipTexts[39]; // (init only)
	/*00e0,60e4*/	ToolTipData toolTipDatas[39];
	/*61c4*/
};

struct ToolTipData // [LegoRR/ToolTip.c|struct:0x27c]
{
	/*000,4*/	real32 timer;
	/*004,200*/	char textBuffer[512];
	/*204,4*/	uint32 textWidth;
	/*208,4*/	uint32 textLineCount;
	/*20c,50*/	Image* iconList[20];
	/*25c,4*/	uint32 iconCount;
	/*260,4*/	sint32 field_260;
	/*264,4*/	undefined4 field_264;
	/*268,4*/	undefined4 field_268;
	/*26c,4*/	sint32 field_26c; // box width?
	/*270,4*/	Image* tooltipImage;
	/*274,4*/	SFX_Type sfxType;
	/*278,4*/	ToolTipFlags flags; // (flag 0x8 IMAGE is not for "iconList")
	/*27c*/
};

struct Upgrade_PartInfo // [LegoRR/Upgrade.c|struct:0x14]
{
	/*00,4*/	uint32 level; // (ae: key Level%i%i%i%i)
	/*04,4*/	uint32 nullFrameNo; // (ae: value[1])
	/*08,4*/	char* nullObjectName; // (ae: value[0])
	/*0c,4*/	char* weaponName; // (ae: value[2], optional)
	/*10,4*/	Upgrade_PartModel* upgradeData;
	/*14*/
};

struct Upgrade_PartModel // [LegoRR/Upgrade.c|struct:0x10]
{
	/*00,4*/	sint32 objID;
	/*04,4*/	Container* cont; // (LWO|ACT|MESH, true)
	/*08,4*/	LegoObject* nextObject;
	/*0c,4*/	Upgrade_PartInfo* partInfo; // (not too sure about this type match)
	/*10*/
};

struct UpgradesModel // [LegoRR/Upgrade.c|struct:0x14]
{
	/*00,4*/	Upgrade_PartInfo* parts; // always ObjectUpgradePartData[200]
	/*04,4*/	uint32 partCount;
	/*08,4*/	uint32 currentLevel;
	/*0c,4*/	LegoObject_UpgradeFlags levelFlags; // [carry][scan][speed][drill]
	/*10,4*/	LegoObject* firstObject;
	/*14*/
};

struct Vector3F // [common.c|struct:0xc]
{
	/*0,4*/	real32 x;
	/*4,4*/	real32 y;
	/*8,4*/	real32 z;
	/*c*/
};

struct Vector4F // [common.c|struct:0x10] D3DRMVector4D
{
	/*00,4*/	real32 x;
	/*04,4*/	real32 y;
	/*08,4*/	real32 z;
	/*0c,4*/	real32 w;
	/*10*/
};

struct VehicleModel // [LegoRR/Vehicle.c|struct:0x1ec]
{
	/*000,4*/	sint32 objID;
	/*004,4*/	char* wheelNullName; // (ae: WheelNullName)
	/*008,4*/	Container* contAct1; // (ACT, true)
	/*00c,4*/	Container* contAct2; // (ACT, true) Optional second ae file (seen for Grannit Grinder legs) This container has priority for finding null frames
	/*010,18*/	Container* wheelNulls[6]; // (ae:WheelMesh, LWO, false) Table for wheel nulls that are assigned a position calculated by wheelRefNulls
	/*028,18*/	Container* wheelRefNulls[6]; // Root wheel nulls that are used to calculate terrain-relative positioning
	/*040,4*/	uint32 wheelNullFrames;
	/*044,18*/	undefined reserved1[24];
	/*05c,c*/	Vector3F wheelVector_5c; // another vector used in wheelNulls positioning
	/*068,4*/	real32 wheelRadius; // (ae: WheelRadius)
	/*06c,48*/	Vector3F wheelNullPositions[6]; // Live position of wheelNulls
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

struct Vertex // [common.c|struct:0x24] Vertex3F, Extension of D3DVertex with color field
{
	/*00,c*/	Vector3F position; // Homogeneous coordinates
	/*0c,c*/	Vector3F normal; // Normal
	/*18,4*/	real32 tu; // Texture coordinates
	/*1c,4*/	real32 tv; // Texture coordinates
	/*20,4*/	uint32 colour;
	/*24*/
};

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

struct Viewport_Globs // [Gods98/Viewports.c|struct:0x8c|tags:GLOBS]
{
	/*00,80*/	Viewport* listSet[32];
	/*80,4*/	Viewport* freeList;
	/*84,4*/	uint32 listCount;
	/*88,4*/	uint32 flags;
	/*8c*/
};

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

struct Wad_FileHandle // [Gods98/Wad.c|struct:0x10]
{
	/*00,4*/	void* data; // Pointer to the file data
	/*04,4*/	bool32 active; // Is this handle active already
	/*08,4*/	sint32 wadNo; // Wad file this handle uses
	/*0c,4*/	sint32 fileNo; // Index of the file in the wad structure
	/*10*/
};

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

struct WadEntry // [Gods98/Wad.c|struct:0x10] WAD file entry metadata contained within LegoWADFile structure
{
	/*00,4*/	Wad_EntryFlags compression; // usually 1, 2 for RNC compression
	/*04,4*/	sint32 fileLength; // Compressed packed size
	/*08,4*/	sint32 decompressedLength; // Original unpacked size (same as packedSize when uncompressed)
	/*0c,4*/	sint32 addr; // absolute file offset
	/*10*/
};

struct WADFILE // [Gods98/Files.c|struct:0xc] Used as one of the stream types for the File struct (as opposed to the C API FILE* struct)
{
	/*0,4*/	sint32 hFile; // Handle to file in the wad
	/*4,4*/	sint32 streamPos; // Position in stream of the file.  Indexes are from 0-length-1 inclusive.
	/*8,4*/	bool32 eof; // Has the file hit EOF.
	/*c*/
};

struct Water_Globs // [LegoRR/Water.c|struct:0x29ec|tags:GLOBS] Module globals for the unfinished "Water flooding" feature.
{
	/*0000,2990*/	WaterEntry entryTable[10];
	/*2990,4*/	uint32 entryCount;
	/*2994,50*/	WaterEntryPair pairTable[10];
	/*29e4,4*/	uint32 pairCount;
	/*29e8,4*/	real32 digDepth; // (assigned, but never used)
	/*29ec*/
};

struct WaterEntry // [LegoRR/Water.c|struct:0x428]
{
	/*000,320*/	Point2F points[100];
	/*320,4*/	uint32 pointCount;
	/*324,f0*/	WaterEntryGroup groups[10];
	/*414,4*/	uint32 groupCount;
	/*418,4*/	real32 dig_z_418; // (init: -10000.0, or vertPos if PREDUG)
	/*41c,4*/	real32 dig_z2_41c;
	/*420,4*/	Container* contMeshTrans;
	/*424,4*/	WaterFlags flags; // (0x1 = visible/active?)
	/*428*/
};

struct WaterEntryGroup // [LegoRR/Water.c|struct:0x18]
{
	/*00,4*/	uint32 index;
	/*04,4*/	Direction direction;
	/*08,4*/	real32 float_maxDirZ_8;
	/*0c,4*/	real32 elapsedUp_c; // elapsed count-up timer
	/*10,4*/	real32 elapsedDown_10; // elapsed count-down timer
	/*14,4*/	bool32 bool_14;
	/*18*/
};

struct WaterEntryPair // [LegoRR/Water.c|struct:0x8] This struct seems to be used solely for qsort ordering by pointsCount(?)
{
	/*0,4*/	WaterEntry* first;
	/*4,4*/	WaterEntry* second;
	/*8*/
};

struct Weapon_Globs // [LegoRR/Weapons.c|struct:0x1b90|tags:GLOBS]
{
	/*0000,4*/	uint32 weaponCount;
	/*0004,4*/	char** weaponNameList;
	/*0008,4*/	WeaponStats* weaponStatsList;
	/*000c,a0*/	ItemStruct_34 ItemStruct34Unk_TABLE[10];
	/*00ac,1ae0*/	Struct_2b0 Struct2B0Unk_TABLE[10];
	/*1b8c,4*/	Config* config;
	/*1b90*/
};

struct WeaponsModel // [LegoRR/Weapons.c|struct:0xa8]
{
	/*00,18*/	Container* fireNullPairs[3][2];
	/*18,c*/	Container* xPivotNulls[3];
	/*24,c*/	Container* yPivotNulls[3];
	/*30,4*/	real32 pivotMaxZ; // (ae: PivotMaxZ)
	/*34,4*/	real32 pivotMinZ; // (ae: PivotMinZ)
	/*38,c*/	bool32 fireNullPairFrames[3]; // (valid: [0,1])
	/*44,24*/	Vector3F vectors3_44[3];
	/*68,24*/	Vector3F vectors3_68[3];
	/*8c,c*/	Upgrade_PartInfo* weaponParts[3];
	/*98,c*/	real32 weaponTimers[3];
	/*a4,4*/	uint32 weaponCount;
	/*a8*/
};

struct WeaponStats // [LegoRR/Weapons.c|struct:0x4b68]
{
	/*0000,4b00*/	real32 ObjectRatios[20][15][16]; // (inits: -1.0f)
	/*4b00,4*/	bool32 isSlowDeath; // (init: false)
	/*4b04,4*/	real32 SlowDeath_initial; // Initial damage percent
	/*4b08,4*/	real32 SlowDeath_duration;
	/*4b0c,4*/	real32 RechargeTime; // (init: 0.0f)
	/*4b10,4*/	real32 DefaultDamage; // (init: 0.0f)
	/*4b14,4*/	real32 DischargeRate;
	/*4b18,4*/	sint32 Ammo;
	/*4b1c,4*/	real32 WeaponRange; // (init: 150.0f)
	/*4b20,48*/	real32 WallDestroyTimes[18]; // (defaults: 5.0f)
	/*4b68*/
};

