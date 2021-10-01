#pragma once


typedef void* addr;
typedef G98CAnimation Animation_t;
typedef uint32 ddw;
typedef Main_StateChangeData Mesh_TextureStateChangeData;
typedef G98CMovie Movie_t;


typedef bool32 (__cdecl* AnimCloneWalkTreeCallback)(IDirect3DRMFrame3*, void*);
typedef void (__cdecl* ContainerActivityCallback)(Container*, void*);
typedef void (__cdecl* ContainerSoundTriggerCallback)(char*, Container*, void*);
typedef void (__cdecl* ContainerTriggerFrameCallback)(Container*, void*);
typedef bool32 (__cdecl* ContainerWalkTreeCallback)(IDirect3DRMFrame3*, void*);
typedef void (__cdecl* DrawPixelFunc)(sint32, sint32, uint32);
typedef void (__cdecl* ElectricFenceEnumerateCallback)(BlockElectricFence*, void*);
typedef void (__cdecl* FileLoadCallback)(char*, uint32, void*);
typedef void (__cdecl* FlocksCallback)(Flocks*, FlocksItem*, void*);
typedef float10 (__cdecl* GetSurfaceZFunc)(real32, real32, SurfaceMap*);
typedef bool32 (__cdecl* InfoEnumerateCallback)(InfoMessageInstance*, void*);
typedef bool32 (__cdecl* LevelIdentifierCallback)(LevelIdentifier*, void*);
typedef bool32 (__cdecl* LwsFindSFXIDFunc)(char*, uint32*);
typedef sint32 (__cdecl* LwsPlaySample3DFunc)(IDirect3DRMFrame3*, uint32, bool32, bool32, Vector3F*);
typedef bool32 (__cdecl* LwsSoundEnabledFunc)(void);
typedef bool32 (__cdecl* MainStateInitialise)(void);
typedef bool32 (__cdecl* MainStateMainLoop)(real32);
typedef void (__cdecl* MainStateShutdown)(void);
typedef void (__cdecl* MainWindowCallback)(HWND, UINT, WPARAM, LPARAM);
typedef void (__cdecl* MenuItemCycleCallback)(sint32);
typedef void (__cdecl* MenuItemRealSliderCallback)(real32);
typedef void (__cdecl* MenuItemSliderCallback)(sint32);
typedef void (__cdecl* MenuItemTriggerCallback)(void);
typedef void (__cdecl* MeshRenderCallback)(Mesh*, void*, Viewport*);
typedef bool32 (__cdecl* NERPsBlockPointerCallback)(BlockPointer*, uint32, uint32, void*);
typedef sint32 (__cdecl* NERPsFunction)(sint32*);
typedef bool32 (__cdecl* SearchLiveObjectCallback)(LiveObject*, void*);
typedef void (__cdecl* SoundCDStopCallback)(void);
typedef void (__cdecl* XYCallback)(sint32, sint32);


enum AbilityType : sint32 // [LegoRR/LegoObject.c|enum:0x4|type:int]
{
	ABILITY_PILOT    = 0,
	ABILITY_SAILOR   = 1,
	ABILITY_DRIVER   = 2,
	ABILITY_DYNAMITE = 3,
	ABILITY_REPAIR   = 4,
	ABILITY_SCANNER  = 5,
	ABILITY__INVALID = -1,
};

enum ActivityType : sint32 // [LegoRR/LegoObject.c|enum:0x4|type:int]
{
	ACTIVITY_STAND               = 0,
	ACTIVITY_ROUTE               = 1,
	ACTIVITY_ROUTERUBBLE         = 2,
	ACTIVITY_RUNPANIC            = 3,
	ACTIVITY_DRILL               = 4,
	ACTIVITY_TELEPORT            = 5,
	ACTIVITY_WALK                = 6,
	ACTIVITY_REINFORCE           = 7,
	ACTIVITY_REVERSE             = 8,
	ACTIVITY_TURNLEFT            = 9,
	ACTIVITY_TURNRIGHT           = 10,
	ACTIVITY_CANTDO              = 11,
	ACTIVITY_EMERGE              = 12,
	ACTIVITY_ENTER               = 13,
	ACTIVITY_ENTERREIN           = 14,
	ACTIVITY_COLLECT             = 15,
	ACTIVITY_GATHER              = 16,
	ACTIVITY_CARRY               = 17,
	ACTIVITY_CARRYRUBBLE         = 18,
	ACTIVITY_THROW               = 19,
	ACTIVITY_CARRYTURNLEFT       = 20,
	ACTIVITY_CARRYTURNRIGHT      = 21,
	ACTIVITY_CARRYSTAND          = 22,
	ACTIVITY_HITLEFT             = 23,
	ACTIVITY_HITRIGHT            = 24,
	ACTIVITY_HITFRONT            = 25,
	ACTIVITY_HITBACK             = 26,
	ACTIVITY_HITHARD             = 27,
	ACTIVITY_DYNAMITE            = 28,
	ACTIVITY_DESPOSIT            = 29,
	ACTIVITY_CLEAR               = 30,
	ACTIVITY_PLACE               = 31,
	ACTIVITY_REPAIR              = 32,
	ACTIVITY_SLIP                = 33,
	ACTIVITY_REST                = 34,
	ACTIVITY_EAT                 = 35,
	ACTIVITY_STAMP               = 36,
	ACTIVITY_THROWMAN            = 37,
	ACTIVITY_THROWNBYROCKMONSTER = 38,
	ACTIVITY_GETUP               = 39,
	ACTIVITY_BUILDPATH           = 40,
	ACTIVITY_UPGRADE             = 41,
	ACTIVITY_EXPLODE             = 42,
	ACTIVITY_UNPOWERED           = 43,
	ACTIVITY_FIRELASER           = 44,
	ACTIVITY_FREEZED             = 45,
	ACTIVITY_FREEZESTART         = 46,
	ACTIVITY_FREEZEMELT          = 47,
	ACTIVITY_RECHARGE            = 48,
	ACTIVITY_WAKEUP              = 49,
	ACTIVITY_TRAIN               = 50,
	ACTIVITY_FLOATON             = 51,
	ACTIVITY_FLOATOFF            = 52,
	ACTIVITY_OPENING             = 53,
	ACTIVITY_CLOSING             = 54,
	ACTIVITY_OPEN                = 55,
	ACTIVITY_WAITING1            = 56,
	ACTIVITY_WAITING2            = 57,
	ACTIVITY_WAITING3            = 58,
	ACTIVITY_WAITING4            = 59,
	ACTIVITY_WAITING5            = 60,
	ACTIVITY_WAITING6            = 61,
	ACTIVITY_WAITING7            = 62,
	ACTIVITY_WAITING8            = 63,
	ACTIVITY_WAITING9            = 64,
	ACTIVITY_WAITING10           = 65,
	ACTIVITY_WAITING11           = 66,
	ACTIVITY_WAITING12           = 67,
	ACTIVITY_WAITING13           = 68,
	ACTIVITY_WAITING14           = 69,
	ACTIVITY_WAITING15           = 70,
	ACTIVITY_WAITING16           = 71,
	ACTIVITY_WAITING17           = 72,
	ACTIVITY_WAITING18           = 73,
	ACTIVITY_WAITING19           = 74,
	ACTIVITY_WAITING20           = 75,
	ACTIVITY_WAITING21           = 76,
	ACTIVITY_CRUMBLE             = 77,
	ACTIVITY_TELEPORTIN          = 78,
	ACTIVITY__INVALID            = -1,
};

enum AdvisorAnimType : sint32 // [LegoRR/Advisor.c|enum:0x4|type:int]
{
	ADVISORANIM_POINTTOMAP = 0,
	ADVISORANIM_POINT_N    = 1,
	ADVISORANIM_POINT_NE   = 2,
	ADVISORANIM_POINT_E    = 3,
	ADVISORANIM_POINT_SE   = 4,
	ADVISORANIM_POINT_S    = 5,
	ADVISORANIM_POINT_SW   = 6,
	ADVISORANIM_POINT_W    = 7,
	ADVISORANIM_POINT_NW   = 8,
	ADVISORANIM_POINT_UP   = 9,
	ADVISORANIM_TALK_TOP   = 10,
	ADVISORANIM__COUNT     = 11,
	ADVISORANIM__INVALID   = -1,
};

enum AdvisorType : sint32 // [LegoRR/Advisor.c|enum:0x4|type:int]
{
	ADVISOR_OBJECTIVE                        = 0,
	ADVISOR_OBJECTIVEACHIEVED                = 1,
	ADVISOR_OBJECTIVEFAILED                  = 2,
	ADVISOR_ICONPOINT_NORMAL                 = 3,
	ADVISOR_ICONPOINT_BACKBUTTON             = 4,
	ADVISOR_ICONPOINT_TOPBUTTONS             = 5,
	ADVISOR_PANELPOINT_RADARTOGGLE           = 6,
	ADVISOR_PANELPOINT_RADARTOGGLEOBJECTVIEW = 7,
	ADVISOR_PANELPOINT_RADARZOOMIN           = 8,
	ADVISOR_PANELPOINT_RADARZOOMOUT          = 9,
	ADVISOR_PANELPOINT_RADARMAPVIEW          = 10,
	ADVISOR_PANELPOINT_INFODOCKGOTO          = 11,
	ADVISOR_PANELPOINT_INFODOCKCLOSE         = 12,
	ADVISOR_PANELPOINT_TOPPANELINFO          = 13,
	ADVISOR_PANELPOINT_TOPPANELOPTIONS       = 14,
	ADVISOR_PANELPOINT_TOPPANELPRIORITIES    = 15,
	ADVISOR_PANELPOINT_TOPPANELCALLTOARMS    = 16,
	ADVISOR_PANELPOINT_TOPPANELGOBACK        = 17,
	ADVISOR_PANELPOINT_CONTROLZOOMIN         = 18,
	ADVISOR_PANELPOINT_CONTROLZOOMOUT        = 19,
	ADVISOR_TALKINGAME                       = 20,
	ADVISOR__COUNT                           = 21,
	ADVISOR__INVALID                         = -1,
};

enum AIPriorityType : sint32 // [LegoRR/AITask.c|enum:0x4|type:int]
{
	AI_PRIORITY_CRYSTAL           = 0,
	AI_PRIORITY_ORE               = 1,
	AI_PRIORITY_DEFAULTCOLLECT    = 2,
	AI_PRIORITY_DESTRUCTION       = 3,
	AI_PRIORITY_CONSTRUCTION      = 4,
	AI_PRIORITY_REQUEST           = 5,
	AI_PRIORITY_REINFORCE         = 6,
	AI_PRIORITY_REPAIR            = 7,
	AI_PRIORITY_CLEARING          = 8,
	AI_PRIORITY_STORAGE           = 9,
	AI_PRIORITY_REFINING          = 10,
	AI_PRIORITY_HEALTHLOW         = 11,
	AI_PRIORITY_GETIN             = 12,
	AI_PRIORITY_UPGRADE           = 13,
	AI_PRIORITY_BUILDPATH         = 14,
	AI_PRIORITY_ATTACKROCKMONSTER = 15,
	AI_PRIORITY_BARRIER           = 16,
	AI_PRIORITY_FINDLOAD          = 17,
	AI_PRIORITY_RECHARGE          = 18,
	AI_PRIORITY_UPGRADEBUILDING   = 19,
	AI_PRIORITY_GATHER            = 20,
	AI_PRIORITY_STEAL             = 21,
	AI_PRIORITY_PUNCH             = 22,
	AI_PRIORITY_DEPART            = 23,
	AI_PRIORITY_ATTACKPATH        = 24,
	AI_PRIORITY_ATTACKOBJECT      = 25,
	AI_PRIORITY_CONGREGATE        = 26,
	AI_PRIORITY__COUNT            = 27,
	AI_PRIORITY__INVALID          = -1,
};

enum AITaskType : sint32 // [LegoRR/AITask.c|enum:0x4|type:int]
{
	AITASK_GOTO              = 0,
	AITASK_FOLLOW            = 1,
	AITASK_FOLLOWATTACK      = 2,
	AITASK_COLLECT           = 3,
	AITASK_GATHER            = 4,
	AITASK_DEPOSITE          = 5,
	AITASK_DUMP              = 6,
	AITASK_REQUEST           = 7,
	AITASK_DIG               = 8,
	AITASK_DYNAMITE          = 9,
	AITASK_REPAIR            = 10,
	AITASK_REINFORCE         = 11,
	AITASK_CLEAR             = 12,
	AITASK_WAIT              = 13,
	AITASK_ANIMATIONWAIT     = 14,
	AITASK_ELECFENCE         = 15,
	AITASK_EAT               = 16,
	AITASK_GOTOEAT           = 17,
	AITASK_FINDDRIVER        = 18,
	AITASK_GETTOOL           = 19,
	AITASK_BIRDSCARER        = 20,
	AITASK_UPGRADE           = 21,
	AITASK_BUILDPATH         = 22,
	AITASK_TRAIN             = 23,
	AITASK_DEPART            = 24,
	AITASK_ATTACKPATH        = 25,
	AITASK_ATTACKROCKMONSTER = 26,
	AITASK_RECHARGE          = 27,
	AITASK_DOCK              = 28,
	AITASK_ATTACKOBJECT      = 29,
	AITASK_FINDLOAD          = 30,
	AITASK__INVALID          = -1,
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

enum BubbleType : sint32 // [LegoRR/Bubble.c|enum:0x4|type:int]
{
	BUBBLE_CANTDO              = 0,
	BUBBLE_IDLE                = 1,
	BUBBLE_COLLECTCRYSTAL      = 2,
	BUBBLE_COLLECTORE          = 3,
	BUBBLE_COLLECTSTUD         = 4,
	BUBBLE_COLLECTDYNAMITE     = 5,
	BUBBLE_COLLECTBARRIER      = 6,
	BUBBLE_COLLECTELECFENCE    = 7,
	BUBBLE_COLLECTDRILL        = 8,
	BUBBLE_COLLECTSHOVEL       = 9,
	BUBBLE_COLLECTHAMMER       = 10,
	BUBBLE_COLLECTSPANNER      = 11,
	BUBBLE_COLLECTLASERBEAM    = 12,
	BUBBLE_COLLECTPUSHERBEAM   = 13,
	BUBBLE_COLLECTFREEZERBEAM  = 14,
	BUBBLE_COLLECTSONICBLASTER = 15,
	BUBBLE_CARRYCRYSTAL        = 16,
	BUBBLE_CARRYORE            = 17,
	BUBBLE_CARRYSTUD           = 18,
	BUBBLE_CARRYDYNAMITE       = 19,
	BUBBLE_CARRYBARRIER        = 20,
	BUBBLE_CARRYELECFENCE      = 21,
	BUBBLE_GOTO                = 22,
	BUBBLE_DYNAMITE            = 23,
	BUBBLE_REINFORCE           = 24,
	BUBBLE_DRILL               = 25,
	BUBBLE_REPAIR              = 26,
	BUBBLE_DIG                 = 27,
	BUBBLE_FLEE                = 28,
	BUBBLE_POWEROFF            = 29,
	BUBBLE_CALLTOARMS          = 30,
	BUBBLE_ELECFENCE           = 31,
	BUBBLE_EAT                 = 32,
	BUBBLE_DRIVE               = 33,
	BUBBLE_UPGRADE             = 34,
	BUBBLE_BUILDPATH           = 35,
	BUBBLE_TRAIN               = 36,
	BUBBLE_RECHARGE            = 37,
	BUBBLE_REQUEST             = 38,
	BUBBLE__INVALID            = -1,
};

enum CameraType : sint32 // [LegoRR/LegoCamera.c|enum:0x4|type:int]
{
	CAMERATYPE_NONE        = 0,
	CAMERATYPE_TOPDOWN     = 1,
	CAMERATYPE_RADAR       = 2,
	CAMERATYPE_FIRSTPERSON = 3,
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
	DRAWEFFECT_NONE      = 0,
	DRAWEFFECT_XOR       = 1,
	DRAWEFFECT_HALFTRANS = 2,
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

enum FileSystemType : sint32 // [Gods98/Files.c|enum:0x4|type:int] Location of a lego File stream (WAD or REAL)
{
	FILESYSTEM_WAD = 0,
	FILESYSTEM_STD = 1,
	FILESYSTEM_ERR = 2,
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

enum InfoType : sint32 // [LegoRR/Info.c|enum:0x4|type:int]
{
	INFO_CRYSTALFOUND         = 0,
	INFO_ORESEAMFOUND         = 1,
	INFO_ROCKMONSTER          = 2,
	INFO_LAVAROCKMONSTER      = 3,
	INFO_ICEROCKMONSTER       = 4,
	INFO_UNDERATTACK          = 5,
	INFO_LANDSLIDE            = 6,
	INFO_CAVEIN               = 7,
	INFO_CONSTRUCTED          = 8,
	INFO_CAVERNLOCATED        = 9,
	INFO_LEGOMANDEATH         = 10,
	INFO_VEHICLEDEATH         = 11,
	INFO_BUILDINGDEATH        = 12,
	INFO_DYNAMITEPLACED       = 13,
	INFO_NOPOWER              = 14,
	INFO_POWERDRAIN           = 15,
	INFO_AIRDEPLETING         = 16,
	INFO_AIRLOW               = 17,
	INFO_AIROUT               = 18,
	INFO_AIRRESTORED          = 19,
	INFO_TRAINDRIVER          = 20,
	INFO_TRAINDYNAMITE        = 21,
	INFO_TRAINREPAIR          = 22,
	INFO_TRAINPILOT           = 23,
	INFO_TRAINSAILOR          = 24,
	INFO_TRAINSCANNER         = 25,
	INFO_ORECOLLECTED         = 26,
	INFO_WALLDUG              = 27,
	INFO_WALLREINFORCED       = 28,
	INFO_CRYSTALPOWER         = 29,
	INFO_LAVAERODE            = 30,
	INFO_SLUGEMERGE           = 31,
	INFO_PATHCOMPLETED        = 32,
	INFO_FOUNDMINIFIGURE      = 33,
	INFO_CANUPGRADEMINIFIGURE = 34,
	INFO_CANTRAINMINIFIGURE   = 35,
	INFO_CRYSTALSEAMFOUND     = 36,
	INFO_GENERICSEAMFOUND     = 37,
	INFO_GENERICDEATH         = 38,
	INFO_GENERICMONSTER       = 39,
	INFO__INVALID             = -1,
};

enum InterfaceMenuType : sint32 // [LegoRR/Interface.c|enum:0x4|type:int]
{
	INTERFACE_MENU_MAIN              = 0,
	INTERFACE_MENU_GROUND            = 1,
	INTERFACE_MENU_ERODE             = 2,
	INTERFACE_MENU_PLACEFENCE        = 3,
	INTERFACE_MENU_CONSTRUCTION      = 4,
	INTERFACE_MENU_RUBBLE            = 5,
	INTERFACE_MENU_WALL              = 7,
	INTERFACE_MENU_TRACKER           = 8,
	INTERFACE_MENU_LEGOMAN           = 9,
	INTERFACE_MENU_VEHICLE           = 10,
	INTERFACE_MENU_WATERVEHICLE      = 11,
	INTERFACE_MENU_UNMANNEDVEHICLE   = 12,
	INTERFACE_MENU_BUILDING          = 13,
	INTERFACE_MENU_ELECTRICFENCE     = 14,
	INTERFACE_MENU_FIRSTPERSON       = 15,
	INTERFACE_MENU_GETTOOL           = 16,
	INTERFACE_MENU_TRAINSKILL        = 17,
	INTERFACE_MENU_UPGRADEVEHICLE    = 18,
	INTERFACE_MENU_BUILDBUILDING     = 19,
	INTERFACE_MENU_BUILDSMALLVEHICLE = 20,
	INTERFACE_MENU_BUILDLARGEVEHICLE = 21,
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

enum LevelCompleteStatus : sint32 // [LegoRR/Objective.c|enum:0x4|type:int] Not sure if Objective...
{
	LEVELSTATUS_NONE            = 0,
	LEVELSTATUS_COMPLETE        = 1,
	LEVELSTATUS_FAILED          = 2,
	LEVELSTATUS_FAILED_CRYSTALS = 3,
	LEVELSTATUS_FAILED_OTHER    = 4,
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

enum MenuIcon : sint32 // [LegoRR/Interface.c|enum:0x4|type:int]
{
	INTERFACE_MENUITEM_BACKTODEFAULT         = 0,
	INTERFACE_MENUITEM_TELEPORTMAN           = 1,
	INTERFACE_MENUITEM_BUILDBUILDING         = 2,
	INTERFACE_MENUITEM_BUILDSMALLVEHICLE     = 3,
	INTERFACE_MENUITEM_BUILDLARGEVEHICLE     = 4,
	INTERFACE_MENUITEM_LAYPATH               = 5,
	INTERFACE_MENUITEM_REMOVEPATH            = 6,
	INTERFACE_MENUITEM_REPAIRLAVA            = 7,
	INTERFACE_MENUITEM_GEOLOGISTTEST         = 8,
	INTERFACE_MENUITEM_CLEARRUBBLE           = 9,
	INTERFACE_MENUITEM_DAM                   = 10,
	INTERFACE_MENUITEM_DIG                   = 11,
	INTERFACE_MENUITEM_REINFORCE             = 12,
	INTERFACE_MENUITEM_DYNAMITE              = 13,
	INTERFACE_MENUITEM_PLACEFENCE            = 14,
	INTERFACE_MENUITEM_DESELECTDIG           = 15,
	INTERFACE_MENUITEM_CANCELCONSTRUCTION    = 16,
	INTERFACE_MENUITEM_SELECTMAN             = 17,
	INTERFACE_MENUITEM_SELECTVEHICLE         = 18,
	INTERFACE_MENUITEM_SELECTBUILDING        = 19,
	INTERFACE_MENUITEM_VEHICLEPICKUP         = 20,
	INTERFACE_MENUITEM_MINIFIGUREPICKUP      = 21,
	INTERFACE_MENUITEM_UNLOADVEHICLE         = 22,
	INTERFACE_MENUITEM_UNLOADMINIFIGURE      = 23,
	INTERFACE_MENUITEM_GETIN                 = 24,
	INTERFACE_MENUITEM_GETOUT                = 25,
	INTERFACE_MENUITEM_GOTODOCK              = 26,
	INTERFACE_MENUITEM_LEGOMANGOTO           = 27,
	INTERFACE_MENUITEM_VEHICLEGOTO           = 28,
	INTERFACE_MENUITEM_VEHICLEDIG            = 29,
	INTERFACE_MENUITEM_LEGOMANDIG            = 30,
	INTERFACE_MENUITEM_GOFEED                = 31,
	INTERFACE_MENUITEM_DELETEMAN             = 32,
	INTERFACE_MENUITEM_DROPBIRDSCARER        = 33,
	INTERFACE_MENUITEM_POWERON               = 34,
	INTERFACE_MENUITEM_POWEROFF              = 35,
	INTERFACE_MENUITEM_REPAIR                = 36,
	INTERFACE_MENUITEM_MAKETELEPORTERPRIMARY = 37,
	INTERFACE_MENUITEM_EJECTCRYSTAL          = 38,
	INTERFACE_MENUITEM_EJECTORE              = 39,
	INTERFACE_MENUITEM_DELETEBUILDING        = 40,
	INTERFACE_MENUITEM_DELETEVEHICLE         = 41,
	INTERFACE_MENUITEM_DELETEELECTRICFENCE   = 42,
	INTERFACE_MENUITEM_ATTACK                = 43,
	INTERFACE_MENUITEM_GOTOTOPVIEW           = 44,
	INTERFACE_MENUITEM_GOTOFIRSTPERSON       = 45,
	INTERFACE_MENUITEM_GOTOSECONDPERSON      = 46,
	INTERFACE_MENUITEM_TRACKOBJECT           = 47,
	INTERFACE_MENUITEM_GETTOOL               = 48,
	INTERFACE_MENUITEM_GETDRILL              = 49,
	INTERFACE_MENUITEM_GETSPADE              = 50,
	INTERFACE_MENUITEM_GETHAMMER             = 51,
	INTERFACE_MENUITEM_GETSPANNER            = 52,
	INTERFACE_MENUITEM_GETLASER              = 53,
	INTERFACE_MENUITEM_GETPUSHERGUN          = 54,
	INTERFACE_MENUITEM_GETFREEZERGUN         = 55,
	INTERFACE_MENUITEM_GETBIRDSCARER         = 56,
	INTERFACE_MENUITEM_TRAINSKILL            = 57,
	INTERFACE_MENUITEM_TRAINDRIVER           = 58,
	INTERFACE_MENUITEM_TRAINENGINEER         = 59,
	INTERFACE_MENUITEM_TRAINGEOLOGIST        = 60,
	INTERFACE_MENUITEM_TRAINPILOT            = 61,
	INTERFACE_MENUITEM_TRAINSAILOR           = 62,
	INTERFACE_MENUITEM_TRAINDYNAMITE         = 63,
	INTERFACE_MENUITEM_UPGRADEMAN            = 64,
	INTERFACE_MENUITEM_UPGRADEBUILDING       = 65,
	INTERFACE_MENUITEM_UPGRADEVEHICLE        = 66,
	INTERFACE_MENUITEM_UPGRADEENGINE         = 67,
	INTERFACE_MENUITEM_UPGRADEDRILL          = 68,
	INTERFACE_MENUITEM_UPGRADESCAN           = 69,
	INTERFACE_MENUITEM_UPGRADECARRY          = 70,
	INTERFACE_MENUITEM_ENCYCLOPEDIA          = 71,
	INTERFACE_MENUITEM_CLEARSELECTION        = 72,
	INTERFACE_MENUITEM_BUILD                 = 73,
	INTERFACE_MENUITEM__COUNT                = 74,
};

enum MenuItemType : sint32 // [LegoRR/FrontEnd.c|enum:0x4|type:int]
{
	MENUITEM_CYCLE      = 0,
	MENUITEM_TRIGGER    = 1,
	MENUITEM_TEXTINPUT  = 2,
	MENUITEM_SLIDER     = 3,
	MENUITEM_REALSLIDER = 4,
	MENUITEM_NEXT       = 5,
	MENUITEM_MISSIONS   = 6,
	MENUITEM__COUNT     = 7,
	MENUITEM__INVALID   = -1,
};

enum MeshType : uint32 // [Gods98/Mesh.c|enum:0x4|type:uint]
{
	MESH_TYPE_NORM            = 0,
	MESH_TYPE_POSTEFFECT      = 1,
	MESH_TYPE_LIGHTWAVEOBJECT = 2,
};

enum MessageType : sint32 // [LegoRR/Message.c|enum:0x4|type:int]
{
	MESSAGE_NULL                           = 0,
	MESSAGE_SELECT                         = 1,
	MESSAGE_SELECTED                       = 2,
	MESSAGE_CLEARSELECT                    = 3,
	MESSAGE_DESELECT                       = 4,
	MESSAGE_GOTO                           = 5,
	MESSAGE_ROCKMONSTERGOTO                = 6,
	MESSAGE_ROCKMONSTERGOTO_COMPLETE       = 7,
	MESSAGE_USERGOTO                       = 8,
	MESSAGE_FIRSTPERSON                    = 9,
	MESSAGE_TRACKOBJECT                    = 10,
	MESSAGE_TOPVIEW                        = 11,
	MESSAGE_PLAYSAMPLE                     = 12,
	MESSAGE_DIG                            = 13,
	MESSAGE_DIG_COMPLETE                   = 14,
	MESSAGE_REPAIR                         = 15,
	MESSAGE_REPAIR_COMPLETE                = 16,
	MESSAGE_REINFORCE                      = 17,
	MESSAGE_REINFORCE_COMPLETE             = 18,
	MESSAGE_ROCKFALL                       = 19,
	MESSAGE_ROCKFALL_COMPLETE              = 20,
	MESSAGE_GENERATECRYSTAL                = 21,
	MESSAGE_GENERATECRYSTAL_COMPLETE       = 22,
	MESSAGE_COLLECTCRYSTAL                 = 23,
	MESSAGE_COLLECTCRYSTAL_COMPLETE        = 24,
	MESSAGE_CRYSTALTOREFINERY              = 25,
	MESSAGE_CRYSTALTOREFINERY_COMPLETE     = 26,
	MESSAGE_GENERATEORE                    = 27,
	MESSAGE_GENERATEORE_COMPLETE           = 28,
	MESSAGE_COLLECTORE                     = 29,
	MESSAGE_COLLECTORE_COMPLETE            = 30,
	MESSAGE_GENERATEROCKMONSTER            = 31,
	MESSAGE_GENERATEROCKMONSTER_COMPLETE   = 32,
	MESSAGE_GATHERROCK                     = 33,
	MESSAGE_GATHERROCK_COMPLETE            = 34,
	MESSAGE_PICKRANDOMFLOOR                = 35,
	MESSAGE_PICKRANDOMFLOOR_COMPLETE       = 36,
	MESSAGE_ATTACKBUILDING                 = 37,
	MESSAGE_ATTACKBUILDING_COMPLETE        = 38,
	MESSAGE_CLEAR                          = 39,
	MESSAGE_CLEAR_COMPLETE                 = 40,
	MESSAGE_GETIN                          = 41,
	MESSAGE_MANSELECTEDANDMONSTERCLICKED   = 42,
	MESSAGE_FOLLOWATTACK                   = 43,
	MESSAGE_COLLECTTOOL                    = 44,
	MESSAGE_REDUCESELECTION                = 45,
	MESSAGE_CLEARFALLIN                    = 46,
	MESSAGE_CLEARFALLIN_COMPLETE           = 47,
	MESSAGE_BUILDPATH                      = 48,
	MESSAGE_BUILDPATH_COMPLETE             = 49,
	MESSAGE_TRAIN                          = 50,
	MESSAGE_TRAIN_COMPLETE                 = 51,
	MESSAGE_GENERATECRYSTALANDORE          = 52,
	MESSAGE_GENERATECRYSTALANDORE_COMPLETE = 53,
	MESSAGE_GENERATEFROMCRYORE             = 54,
	MESSAGE_GENERATEFROMCRYORE_COMPLETE    = 55,
	MESSAGE_UPGRADE                        = 56,
	MESSAGE_UPGRADE_COMPLETE               = 57,
	MESSAGE_CLEARBUILDING                  = 58,
	MESSAGE_CLEARBUILDING_COMPLETE         = 59,
	MESSAGE_CLEARINITIAL                   = 60,
	MESSAGE_CLEARINITIAL_COMPLETE          = 61,
	MESSAGE_CLEARREMOVEPATH                = 62,
	MESSAGE_CLEARREMOVEPATH_COMPLETE       = 63,
	MESSAGE_DEBUG_DESTROYALL               = 64,
	MESSAGE__INVALID                       = -1,
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

enum ObjectType : sint32 // [LegoRR/LegoObject.c|enum:0x4|type:int]
{
	OBJECT_NONE              = 0,
	OBJECT_VEHICLE           = 1,
	OBJECT_MINIFIGURE        = 2,
	OBJECT_ROCKMONSTER       = 3,
	OBJECT_BUILDING          = 4,
	OBJECT_BOULDER           = 5,
	OBJECT_POWERCRYSTAL      = 6,
	OBJECT_ORE               = 7,
	OBJECT_DYNAMITE          = 8,
	OBJECT_BARRIER           = 9,
	OBJECT_UPGRADEPART       = 10,
	OBJECT_ELECTRICFENCE     = 11,
	OBJECT_SPIDERWEB         = 12,
	OBJECT_OOHSCARY          = 13,
	OBJECT_ELECTRICFENCESTUD = 14,
	OBJECT_PATH              = 15,
	OBJECT_PUSHER            = 16,
	OBJECT_FREEZER           = 17,
	OBJECT_ICECUBE           = 18,
	OBJECT_LASERSHOT         = 19,
	OBJECT_TVCAMERA          = -1,
};

enum OreType : sint32 // [LegoRR/dummy.c|enum:0x4|type:int|tags:HELPER]
{
	ORE_NORMAL    = 0,
	ORE_PROCESSED = 1,
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

enum PanelType : sint32 // [LegoRR/Panels.c|enum:0x4|type:int]
{
	PANEL_RADAR          = 0,
	PANEL_RADARFILL      = 1,
	PANEL_RADAROVERLAY   = 2,
	PANEL_MESSAGES       = 3,
	PANEL_MESSAGESIDE    = 4,
	PANEL_CRYSTALSIDEBAR = 5,
	PANEL_TOPPANEL       = 6,
	PANEL_INFORMATION    = 7,
	PANEL_PRIORITYLIST   = 8,
	PANEL_CAMERACONTROL  = 9,
	PANEL_INFODOCK       = 10,
	PANEL_ENCYCLOPEDIA   = 11,
	PANEL__COUNT         = 12,
	PANEL__INVALID       = -1,
};

enum PathType : uint8 // [LegoRR/Lego.c|enum:0x1|type:byte|tags:MAPFILE]
{
	PATH_NONE      = 0,
	PATH_RUBBLE    = 1,
	PATH_POWERPATH = 2,
};

enum PointerType : sint32 // [LegoRR/Pointer.c|enum:0x4|type:int]
{
	POINTER_STANDARD                 = 0,
	POINTER_BLANK                    = 1,
	POINTER_SELECTED                 = 2,
	POINTER_DRILL                    = 3,
	POINTER_CANTDRILL                = 4,
	POINTER_CLEAR                    = 5,
	POINTER_GO                       = 6,
	POINTER_CANTGO                   = 7,
	POINTER_TELEPORT                 = 8,
	POINTER_CANTTELEPORT             = 9,
	POINTER_REINFORCE                = 10,
	POINTER_CANTREINFORCE            = 11,
	POINTER_RADARPAN                 = 12,
	POINTER_TRACKOBJECT              = 13,
	POINTER_HELP                     = 14,
	POINTER_CANTHELP                 = 15,
	POINTER_PUTDOWN                  = 16,
	POINTER_GETIN                    = 17,
	POINTER_GETOUT                   = 18,
	POINTER_TUTORIALBLOCKINFO        = 19,
	POINTER_OKAY                     = 20,
	POINTER_NOTOKAY                  = 21,
	POINTER_CANBUILD                 = 22,
	POINTER_CANNOTBUILD              = 23,
	POINTER_DYNAMITE                 = 24,
	POINTER_CANTDYNAMITE             = 25,
	POINTER_PICKUP                   = 26,
	POINTER_CANTPICKUP               = 27,
	POINTER_PICKUPORE                = 28,
	POINTER_LEGOMANCANTDIG           = 29,
	POINTER_VEHICLECANTDIG           = 30,
	POINTER_LEGOMANDIG               = 31,
	POINTER_VEHICLEDIG               = 32,
	POINTER_LEGOMANCANTPICKUP        = 33,
	POINTER_VEHICLECANTPICKUP        = 34,
	POINTER_LEGOMANPICKUP            = 35,
	POINTER_VEHICLEPICKUP            = 36,
	POINTER_LEGOMANCANTGO            = 37,
	POINTER_VEHICLECANTGO            = 38,
	POINTER_LEGOMANGO                = 39,
	POINTER_VEHICLEGO                = 40,
	POINTER_LEGOMANCLEAR             = 41,
	POINTER_VEHICLECLEAR             = 42,
	POINTER_SURFACETYPE_IMMOVABLE    = 43,
	POINTER_SURFACETYPE_HARD         = 44,
	POINTER_SURFACETYPE_MEDIUM       = 45,
	POINTER_SURFACETYPE_LOOSE        = 46,
	POINTER_SURFACETYPE_SOIL         = 47,
	POINTER_SURFACETYPE_LAVA         = 48,
	POINTER_SURFACETYPE_WATER_unused = 49,
	POINTER_SURFACETYPE_ORESEAM      = 50,
	POINTER_SURFACETYPE_LAKE         = 51,
	POINTER_SURFACETYPE_CRYSTALSEAM  = 52,
	POINTER_SURFACETYPE_RECHARGESEAM = 53,
	POINTER_CANTZOOM                 = 54,
	POINTER_ZOOM                     = 55,
};

enum PolyMode : sint32 // [LegoRR/???|enum:0x4|type:int]
{
	POLY_LOW    = 0,
	POLY_MEDIUM = 1,
	POLY_HIGH   = 2,
	POLY_FP     = 3,
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

enum RewardItemType : sint32 // [LegoRR/Rewards.c|enum:0x4|type:int]
{
	REWARDTYPE_CRYSTALS      = 0,
	REWARDTYPE_ORE           = 1,
	REWARDTYPE_DIGGABLE      = 2,
	REWARDTYPE_CONSTRUCTIONS = 3,
	REWARDTYPE_CAVERNS       = 4,
	REWARDTYPE_FIGURES       = 5,
	REWARDTYPE_ROCKMONSTERS  = 6,
	REWARDTYPE_OXYGEN        = 7,
	REWARDTYPE_TIMER         = 8,
	REWARDTYPE_SCORE         = 9,
	REWARDTYPE__COUNT        = 10,
	REWARDTYPE__INVALID      = -1,
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

enum ScreenMenuType : sint32 // [LegoRR/FrontEnd.c|enum:0x4|type:int] Types of menus only shown out-of-game
{
	MENU_SCREEN_TITLE       = 0,
	MENU_SCREEN_MISSIONS    = 1,
	MENU_SCREEN_TRAINING    = 2,
	MENU_SCREEN_LOAD_unused = 3,
	MENU_SCREEN_SAVE        = 4,
};

enum SFXType : sint32 // [LegoRR/SFX.c|enum:0x4|type:int] SFXType is different from actual Sample indexes, these are hardcoded values that can easily be looked up by ID
{
	SFX_NULL                    = 0,
	SFX_STAMP                   = 1,
	SFX_DRILL                   = 2,
	SFX_DRILLFADE               = 3,
	SFX_ROCKBREAK               = 4,
	SFX_DRIP                    = 5,
	SFX_AMBIENT                 = 6,
	SFX_AMBIENTLOOP             = 7,
	SFX_STEP                    = 8,
	SFX_ROCKMONSTER             = 9,
	SFX_ROCKMONSTER2            = 10,
	SFX_ROCKMONSTERSTEP         = 11,
	SFX_MFDEPOSIT               = 12,
	SFX_BUTTONPRESSED           = 13,
	SFX_MFLIFT                  = 14,
	SFX_MFTHROW                 = 15,
	SFX_WALKER                  = 16,
	SFX_YESSIR                  = 17,
	SFX_BUILD                   = 18,
	SFX_OKAY                    = 19,
	SFX_NOTOKAY                 = 20,
	SFX_INTERFACESLIDEONSCREEN  = 21,
	SFX_INTERFACESLIDEOFFSCREEN = 22,
	SFX_PANELSLIDEONSCREEN      = 23,
	SFX_PANELSLIDEOFFSCREEN     = 24,
	SFX_SIREN                   = 25,
	SFX_CRYSTALRECHARGE         = 26,
	SFX_LASER                   = 27,
	SFX_LASERHIT                = 28,
	SFX_LAZERRECHARGE           = 29,
	SFX_TOPPRIORITY             = 30,
	SFX_IMMOVABLEROCK           = 31,
	SFX_WALL                    = 32,
	SFX_FLOOR                   = 33,
	SFX_BOULDERHIT              = 34,
	SFX_PLACE                   = 35,
	SFX_PLACEORE                = 36,
	SFX_PLACECRYSTAL            = 37,
	SFX_LAVA                    = 38,
	SFX_ROCKWIPE                = 39,
	SFX_FALLIN                  = 40,
	SFX_MUSICLOOP               = 41,
	SFX_CAPTAINSLIDE            = 42,
	SFX_DYNAMITE                = 43,
	SFX_AMBIENTMUSICLOOP        = 44,
	SFX__INVALID                = -1,
};

enum Sound3DPlayMode : uint32 // [Gods98/3DSound.c|enum:0x4|type:uint]
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

enum SurfaceType : sint32 // [LegoRR/Lego.c|enum:0x4|type:int|tags:BIGENUMALIAS] See TerrainType for byte-sized enum version.
{
	SURFACE_TUNNEL        = 0,
	SURFACE_IMMOVABLE     = 1,
	SURFACE_HARD          = 2,
	SURFACE_MEDIUM        = 3,
	SURFACE_LOOSE         = 4,
	SURFACE_SOIL          = 5,
	SURFACE_LAVA          = 6,
	SURFACE_WATER_unused  = 7,
	SURFACE_ORESEAM       = 8,
	SURFACE_LAKE          = 9,
	SURFACE_CRYSTALSEAM   = 10,
	SURFACE_RECHARGESEAM  = 11,
	SURFACE_RUBBLE        = 12,
	SURFACE_REINFORCEMENT = 13,
	SURFACE_PATH          = 14,
	SURFACE_SLUGHOLE      = 15,
	SURFACE_UNDISCOVERED  = 16,
	SURFACE_CAVERN        = 17,
	SURFACE__INVALID      = -1,
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

enum TextType : sint32 // [LegoRR/Text.c|enum:0x4|type:int]
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

enum ToolTipType : sint32 // [LegoRR/ToolTip.c|enum:0x4|type:int]
{
	TOOLTIP_NULL                       = 0,
	TOOLTIP_RADARBLOCK                 = 1,
	TOOLTIP_UNITSELECTED               = 2,
	TOOLTIP_CONSTRUCTION               = 3,
	TOOLTIP_INTERFACEMENU              = 4,
	TOOLTIP_INTERFACEMENUBACKBUTTON    = 5,
	TOOLTIP_MAPBLOCK                   = 6,
	TOOLTIP_PRIORITY                   = 7,
	TOOLTIP_INFOMENUCONTINUE           = 8,
	TOOLTIP_INFOMENUDISABLEFUTURE      = 9,
	TOOLTIP_RADARTOGGLE                = 10,
	TOOLTIP_RADAROBJECTVIEW            = 11,
	TOOLTIP_RADARZOOMIN                = 12,
	TOOLTIP_RADARZOOMOUT               = 13,
	TOOLTIP_RADARMAPVIEW               = 14,
	TOOLTIP_INFODOCKGOTO               = 15,
	TOOLTIP_INFODOCKCLOSE              = 16,
	TOOLTIP_TOPPANELCALLTOARMS         = 17,
	TOOLTIP_TOPPANELINFO               = 18,
	TOOLTIP_TOPPANELOPTIONS            = 19,
	TOOLTIP_TOPPANELPRIORITIES         = 20,
	TOOLTIP_PRIORITYDISABLE            = 21,
	TOOLTIP_PRIORITYUPONE              = 22,
	TOOLTIP_PRIORITYRESET              = 23,
	TOOLTIP_CAMCONTROLZOOMIN           = 24,
	TOOLTIP_CAMCONTROLZOOMOUT          = 25,
	TOOLTIP_CAMCONTROLCYCLE            = 26,
	TOOLTIP_CAMCONTROLROTATE           = 27,
	TOOLTIP_SIDEBAR_ORE                = 28,
	TOOLTIP_SIDEBAR_CRYSTAL            = 29,
	TOOLTIP_CLOSE                      = 30,
	TOOLTIP_PREVIOUSMESSAGE            = 31,
	TOOLTIP_NEXTMESSAGE                = 32,
	TOOLTIP_MORE                       = 33,
	TOOLTIP_BACK                       = 34,
	TOOLTIP_CAMCONTROLCYCLEMINIFIGURES = 35,
	TOOLTIP_REWARD_SAVE                = 36,
	TOOLTIP_REWARD_ADVANCE             = 37,
	TOOLTIP_FRONTEND_BACK              = 38,
};

enum ToolType : sint32 // [LegoRR/LegoObject.c|enum:0x4|type:int]
{
	TOOL_DRILL      = 0,
	TOOL_SPADE      = 1,
	TOOL_HAMMER     = 2,
	TOOL_SPANNER    = 3,
	TOOL_LASER      = 4,
	TOOL_PUSHERGUN  = 5,
	TOOL_BIRDSCARER = 6,
	TOOL_FREEZERGUN = 7,
	TOOL__INVALID   = -1,
};

enum ViewMode : sint32 // [LegoRR/Lego.c|enum:0x4|type:int]
{
	VIEW_FIRSTPERSON = 0,
	VIEW_TOPDOWN     = 1,
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

enum AudioFlags : uint32 // [LegoRR/SFX.c|flags:0x4|type:uint] SFX_GlobFlags
{
	AUDIO_SOUNDON      = 0x1,
	AUDIO_POPULATEMODE = 0x2,
	AUDIO_UNK_8        = 0x8,
};
DEFINE_ENUM_FLAG_OPERATORS(AudioFlags);

enum BlockSpiderWebFlags : uint32 // [LegoRR/SpiderWeb.c|flags:0x4|type:uint]
{
	BLOCKWEB_NONE   = 0,
	BLOCKWEB_ACTIVE = 0x100,
};
DEFINE_ENUM_FLAG_OPERATORS(BlockSpiderWebFlags);

enum CameraFlags : uint32 // [LegoRR/LegoCamera.c|flags:0x4|type:uint]
{
	CAMERA_NONE         = 0,
	CAMERA_TILTRANGE    = 0x1,
	CAMERA_YAWRANGE     = 0x2,
	CAMERA_DISTRANGE    = 0x4,
	CAMERA_FREEMOVEMENT = 0x8,
	CAMERA_UNK_10       = 0x10,
};
DEFINE_ENUM_FLAG_OPERATORS(CameraFlags);

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

enum DependencyFlags : uint32 // [LegoRR/Dependencies.c|flags:0x4|type:uint]
{
	DEPENDENCY_NONE        = 0,
	DEPENDENCY_HITONCESTAY = 0x1,
	DEPENDENCY_UNK_2       = 0x2,
	DEPENDENCY_UNK_4       = 0x4,
	DEPENDENCY_UNK_8       = 0x8,
	DEPENDENCY_UNK_100     = 0x100,
};
DEFINE_ENUM_FLAG_OPERATORS(DependencyFlags);

enum DirectDraw_DeviceFlags : uint32 // [Gods98/DirectDraw.c|flags:0x4|type:uint] Valid flag is actually shared: DIRECTDRAW_FLAG_VALID
{
	DIRECTDRAW_FLAG_DEVICE_NONE          = 0,
	DIRECTDRAW_FLAG_DEVICE_VALID         = 0x1,
	DIRECTDRAW_FLAG_DEVICE_DEPTH8        = 0x10,
	DIRECTDRAW_FLAG_DEVICE_DEPTH16       = 0x20,
	DIRECTDRAW_FLAG_DEVICE_DEPTH24       = 0x40,
	DIRECTDRAW_FLAG_DEVICE_DEPTH32       = 0x80,
	DIRECTDRAW_FLAG_DEVICE_ZBUFF8        = 0x100,
	DIRECTDRAW_FLAG_DEVICE_ZBUFF16       = 0x200,
	DIRECTDRAW_FLAG_DEVICE_ZBUFF24       = 0x400,
	DIRECTDRAW_FLAG_DEVICE_ZBUFF32       = 0x800,
	DIRECTDRAW_FLAG_DEVICE_COLOUR        = 0x1000,
	DIRECTDRAW_FLAG_DEVICE_HARDWARE      = 0x2000,
	DIRECTDRAW_FLAG_DEVICE_VIDEOTEXTURE  = 0x4000,
	DIRECTDRAW_FLAG_DEVICE_SYSTEMTEXTURE = 0x8000,
};
DEFINE_ENUM_FLAG_OPERATORS(DirectDraw_DeviceFlags);

enum DirectDraw_DriverFlags : uint32 // [Gods98/DirectDraw.c|flags:0x4|type:uint] Valid flag is actually shared: DIRECTDRAW_FLAG_VALID
{
	DIRECTDRAW_FLAG_DRIVER_NONE     = 0,
	DIRECTDRAW_FLAG_DRIVER_VALID    = 0x1,
	DIRECTDRAW_FLAG_DRIVER_PRIMARY  = 0x10,
	DIRECTDRAW_FLAG_DRIVER_WINDOWOK = 0x20,
};
DEFINE_ENUM_FLAG_OPERATORS(DirectDraw_DriverFlags);

enum DirectDraw_ModeFlags : uint32 // [Gods98/DirectDraw.c|flags:0x4|type:uint] Valid flag is actually shared: DIRECTDRAW_FLAG_VALID
{
	DIRECTDRAW_FLAG_MODE_NONE  = 0,
	DIRECTDRAW_FLAG_MODE_VALID = 0x1,
};
DEFINE_ENUM_FLAG_OPERATORS(DirectDraw_ModeFlags);

enum FeatureFlags : uint32 // [LegoRR/Lego.c|flags:0x4|type:uint] Flags specified by the "-flags #" command line argument (which has to be in decimal...)
{
	FEATURE_NONE        = 0,
	FEATURE_BLOCKFADEIN = 0x8000,
};
DEFINE_ENUM_FLAG_OPERATORS(FeatureFlags);

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

enum GameFlags1 : uint32 // [LegoRR/Lego.c|flags:0x4|type:uint]
{
	GAME1_NONE                  = 0,
	GAME1_RADARON               = 0x2,
	GAME1_LEVELSTART            = 0x4,
	GAME1_MUSICON               = 0x8,
	GAME1_SOUNDON               = 0x10,
	GAME1_WALLPROMESHES         = 0x20,
	GAME1_FRAMERATEMONITOR      = 0x40,
	GAME1_MEMORYMONITOR         = 0x80,
	GAME1_DRAGGINGBOX_UNK       = 0x100,
	GAME1_UNK_200               = 0x200,
	GAME1_CLEAR                 = 0x400,
	GAME1_PANELS                = 0x800,
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

enum LevelBlockFlags1 : uint32 // [LegoRR/Lego.c|flags:0x4|type:uint]
{
	BLOCK1_NONE                    = 0,
	BLOCK1_RUBBLE_LOW              = 0x1,
	BLOCK1_RUBBLE_MEDIUM           = 0x2,
	BLOCK1_RUBBLE_FULL             = 0x3,
	BLOCK1_SURVEYED                = 0x4,
	BLOCK1_GROUND                  = 0x8,
	BLOCK1_WALL_UNK                = 0x10,
	BLOCK1_REINFORCED              = 0x20,
	BLOCK1_CORNEROBTUSE            = 0x40,
	BLOCK1_CORNERINNER             = 0x80,
	BLOCK1_UNK_100                 = 0x100,
	BLOCK1_UNK_200                 = 0x200,
	BLOCK1_BUILDINGSOLID           = 0x400,
	BLOCK1_UNK_800                 = 0x800,
	BLOCK1_UNK_1000                = 0x1000,
	BLOCK1_UNK_2000                = 0x2000,
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
DEFINE_ENUM_FLAG_OPERATORS(LevelBlockFlags1);

enum LevelBlockFlags2 : uint32 // [LegoRR/Lego.c|flags:0x4|type:uint]
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
DEFINE_ENUM_FLAG_OPERATORS(LevelBlockFlags2);

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
	LIVEOBJ1_NONE         = 0,
	LIVEOBJ1_MOVING       = 0x1,
	LIVEOBJ1_LIFTING      = 0x2,
	LIVEOBJ1_TURNING      = 0x4,
	LIVEOBJ1_UNK_8        = 0x8,
	LIVEOBJ1_UNK_10       = 0x10,
	LIVEOBJ1_REINFORCING  = 0x40,
	LIVEOBJ1_TURNRIGHT    = 0x80,
	LIVEOBJ1_UNK_100      = 0x100,
	LIVEOBJ1_UNK_200      = 0x200,
	LIVEOBJ1_CARRYING     = 0x400,
	LIVEOBJ1_UNK_800      = 0x800,
	LIVEOBJ1_UNK_1000     = 0x1000,
	LIVEOBJ1_UNK_2000     = 0x2000,
	LIVEOBJ1_UNK_4000     = 0x4000,
	LIVEOBJ1_UNK_8000     = 0x8000,
	LIVEOBJ1_UNK_10000    = 0x10000,
	LIVEOBJ1_UNK_20000    = 0x20000,
	LIVEOBJ1_CLEARING     = 0x40000,
	LIVEOBJ1_PLACING      = 0x80000,
	LIVEOBJ1_UNK_100000   = 0x100000,
	LIVEOBJ1_UNK_200000   = 0x200000,
	LIVEOBJ1_UNK_400000   = 0x400000,
	LIVEOBJ1_UNK_800000   = 0x800000,
	LIVEOBJ1_UNK_1000000  = 0x1000000,
	LIVEOBJ1_CAUGHTINWEB  = 0x2000000,
	LIVEOBJ1_UNK_4000000  = 0x4000000,
	LIVEOBJ1_UNK_10000000 = 0x10000000,
	LIVEOBJ1_REST         = 0x20000000,
	LIVEOBJ1_EATING       = 0x40000000,
	LIVEOBJ1_UNK_80000000 = 0x80000000,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags1);

enum LiveFlags2 : uint32 // [LegoRR/LegoObject.c|flags:0x4|type:uint]
{
	LIVEOBJ2_NONE         = 0,
	LIVEOBJ2_UNK_1        = 0x1,
	LIVEOBJ2_UNK_2        = 0x2,
	LIVEOBJ2_UNK_4        = 0x4,
	LIVEOBJ2_DRIVING      = 0x8,
	LIVEOBJ2_UNK_10       = 0x10,
	LIVEOBJ2_UNK_20       = 0x20,
	LIVEOBJ2_UNK_40       = 0x40,
	LIVEOBJ2_UNK_100      = 0x100,
	LIVEOBJ2_UNK_200      = 0x200,
	LIVEOBJ2_TRAINING     = 0x400,
	LIVEOBJ2_UNK_800      = 0x800,
	LIVEOBJ2_UNK_1000     = 0x1000,
	LIVEOBJ2_UNK_2000     = 0x2000,
	LIVEOBJ2_UNK_4000     = 0x4000,
	LIVEOBJ2_UPGRADING    = 0x8000,
	LIVEOBJ2_UNK_10000    = 0x10000,
	LIVEOBJ2_UNK_20000    = 0x20000,
	LIVEOBJ2_UNK_40000    = 0x40000,
	LIVEOBJ2_UNK_80000    = 0x80000,
	LIVEOBJ2_UNK_100000   = 0x100000,
	LIVEOBJ2_UNK_200000   = 0x200000,
	LIVEOBJ2_UNK_400000   = 0x400000,
	LIVEOBJ2_UNK_800000   = 0x800000,
	LIVEOBJ2_UNK_1000000  = 0x1000000,
	LIVEOBJ2_UNK_2000000  = 0x2000000,
	LIVEOBJ2_UNK_4000000  = 0x4000000,
	LIVEOBJ2_UNK_8000000  = 0x8000000,
	LIVEOBJ2_UNK_10000000 = 0x10000000,
	LIVEOBJ2_UNK_20000000 = 0x20000000,
	LIVEOBJ2_UNK_40000000 = 0x40000000,
	LIVEOBJ2_UNK_80000000 = 0x80000000,
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

enum LiveManagerFlags : uint32 // [LegoRR/LegoObject.c|flags:0x4|type:uint] LegoObject_GlobFlags, ReservedPool LiveObject INITFLAGS
{
	LIVEMANAGER_NONE   = 0,
	LIVEMANAGER_ISUSED = 0x1,
	LIVEMANAGER_UNK_20 = 0x20,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveManagerFlags);

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

enum MainFlags : uint32 // [Gods98/Main.c|flags:0x4|type:uint] Command line argument flags set when starting the game
{
	CMD_NONE               = 0,
	CMD_D3DRMUPDATED       = 0x1,
	CMD_FULLSCREEN         = 0x2,
	CMD_TEXTUREVIDEOMEMORY = 0x4,
	CMD_MIPMAP             = 0x8,
	CMD_NOFPSLOCK          = 0x10,
	CMD_NM                 = 0x20,
	CMD_BEST               = 0x40,
	CMD_FPSLOCK30          = 0x80,
	CMD_WINDOW             = 0x100,
	CMD_STARTLEVEL         = 0x200,
	CMD_CLEANSAVES         = 0x400,
	CMD_DEBUG              = 0x2000,
	CMD_DUALMOUSE          = 0x4000,
	CMD_DEBUGCOMPLETE      = 0x8000,
	CMD_TESTERCALL         = 0x10000,
	CMD_TESTLEVELS         = 0x20000,
	CMD_FTM                = 0x40000,
	CMD_FVF                = 0x80000,
	CMD_REDUCESAMPLES      = 0x100000,
	CMD_SHOWVERSION        = 0x200000,
	CMD_REDUCEANIMATION    = 0x400000,
	CMD_REDUCEPROMESHES    = 0x800000,
	CMD_REDUCEFLICS        = 0x1000000,
	CMD_REDUCEIMAGES       = 0x2000000,
};
DEFINE_ENUM_FLAG_OPERATORS(MainFlags);

enum Mem_HandleFlags : uint32 // [Gods98/Memory.c|flags:0x4|type:uint] Flags for SharedBuffer struct
{
	MEMORY_HANDLE_FLAG_NONE = 0,
	MEMORY_HANDLE_FLAG_USED = 0x1,
};
DEFINE_ENUM_FLAG_OPERATORS(Mem_HandleFlags);

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

enum ObjectStatsFlags1 : uint32 // [LegoRR/Stats.c|flags:0x4|type:uint]
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
DEFINE_ENUM_FLAG_OPERATORS(ObjectStatsFlags1);

enum ObjectStatsFlags2 : uint32 // [LegoRR/Stats.c|flags:0x4|type:uint]
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
DEFINE_ENUM_FLAG_OPERATORS(ObjectStatsFlags2);

enum ObjectStatsFlags3 : uint32 // [LegoRR/Stats.c|flags:0x4|type:uint]
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
DEFINE_ENUM_FLAG_OPERATORS(ObjectStatsFlags3);

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
	REWARDITEM_NONE               = 0,
	REWARDITEM_VALUETEXT          = 0x1,
	REWARDITEM_IMAGES             = 0x2,
	REWARDITEM_FLIC               = 0x4,
	REWARDITEM_NAMETEXT           = 0x10,
	REWARDITEM_NAMETEXT_HALFTRANS = 0x20,
	REWARDITEM_BOXIMAGES          = 0x40,
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

enum SampleFlags : uint32 // [LegoRR/SFX.c|flags:0x4|type:uint]
{
	SAMPLE_NONE     = 0,
	SAMPLE_ISUSED   = 0x1,
	SAMPLE_VOLUME   = 0x2,
	SAMPLE_MULTIPLE = 0x4,
	SAMPLE_STREAMED = 0x8,
};
DEFINE_ENUM_FLAG_OPERATORS(SampleFlags);

enum SurfaceMapFlags : uint32 // [LegoRR/Map3D.c|flags:0x4|type:uint]
{
	SURFMAP_NONE  = 0,
	SURFMAP_UNK_2 = 0x2,
};
DEFINE_ENUM_FLAG_OPERATORS(SurfaceMapFlags);

enum SurfaceMapStruct28Flags : uint8 // [LegoRR/Map3D.c|flags:0x1|type:byte] Flags for SurfaceMapStruct_28->byte_19
{
	SURFMAP_STRUCT28_NONE   = 0,
	SURFMAP_STRUCT28_UNK_1  = 0x1,
	SURFMAP_STRUCT28_UNK_4  = 0x4,
	SURFMAP_STRUCT28_UNK_8  = 0x8,
	SURFMAP_STRUCT28_UNK_10 = 0x10,
	SURFMAP_STRUCT28_UNK_20 = 0x20,
	SURFMAP_STRUCT28_UNK_40 = 0x40,
};
DEFINE_ENUM_FLAG_OPERATORS(SurfaceMapStruct28Flags);

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

enum WadEntryFlags : uint32 // [Gods98/Wad.c|flags:0x4|type:uint]
{
	WAD_FILE_NONE         = 0,
	WAD_FILE_UNCOMPRESSED = 0x1,
	WAD_FILE_RNCOMPRESSED = 0x2,
	WAD_FILE_IS_IN_WAD    = 0x4,
};
DEFINE_ENUM_FLAG_OPERATORS(WadEntryFlags);

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

union MenuItemData_union // [LegoRR/FrontEnd.c|union:0x4]
{
	/*0,4*/	MenuItemCycle* cycle;
	/*0,4*/	MenuItemTrigger* trigger;
	/*0,4*/	MenuItemSlider* slider;
	/*0,4*/	MenuItemRealSlider* realSlider;
	/*0,4*/	SubMenu* next;
	/*4*/
};



struct Advisor_Globs // [LegoRR/Advisor.c|struct:0x410|tags:GLOBS]
{
	/*000,54*/	char* positionName[21];
	/*054,2f4*/	AdvisorPositionData advisorPositions[21];
	/*348,2c*/	char* animName[11];
	/*374,84*/	AdvisorAnimData advisorAnims[11];
	/*3f8,4*/	AdvisorType currentType;
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
	/*00,4*/	AdvisorAnimType animType;
	/*04,4*/	TextType textType;
	/*08,4*/	sint32 sfxIndex;
	/*0c,4*/	PanelType panelType;
	/*10,8*/	Point2F point1;
	/*18,8*/	Point2F point2; // Identical to point1
	/*20,4*/	AdvisorPositionFlags flags; // (init: 0x20000), 0x10000 = NULL panel, 0x40000 = non-NULL text
	/*24*/
};

struct AI_Globs // [LegoRR/AITask.c|struct:0x4e9c|tags:GLOBS]
{
	/*0000,30*/	AITaskData* listSet[12];
	/*0030,4*/	AITaskData* freeList;
	/*0034,4*/	uint32 listCount;
	/*0038,7c*/	char* aitaskName[31];
	/*00b4,6c*/	char* priorityName[27];
	/*0120,6c*/	uint32 priorityValues[27];
	/*018c,4*/	AITaskData* AITaskUnkPtr;
	/*0190,4*/	AITaskData* AITaskDataNext;
	/*0194,c8*/	LiveObject* liveObjsTable_1[50];
	/*025c,4*/	uint32 liveObjsCount_1;
	/*0260,c8*/	LiveObject* liveObjsTable_2[50];
	/*0328,4*/	uint32 liveObjsCount_2;
	/*032c,4b00*/	uint32 requestObjCounts[20][15][16];
	/*4e2c,6c*/	bool32 disabledPriorities[27];
	/*4e98,4*/	uint32 flags;
	/*4e9c*/
};

struct AITaskData // [LegoRR/AITask.c|struct:0x68|tags:LISTSET]
{
	/*00,4*/	AITaskType taskType;
	/*04,4*/	undefined4 field_4;
	/*08,8*/	Point2I blockPos;
	/*10,4*/	LiveObject* object_10;
	/*14,4*/	real32 unkExpiryTime;
	/*18,4*/	real32 float_18;
	/*1c,4*/	uint32 priorityValue;
	/*20,4*/	ObjectType objType;
	/*24,4*/	sint32 objIndex;
	/*28,4*/	sint32 objLevel;
	/*2c,4*/	undefined4 field_2c;
	/*30,8*/	Point2F pointf_30; // probably a table
	/*38,4*/	ToolType toolType;
	/*3c,4*/	undefined4 mode_3c;
	/*40,4*/	void* ptr_40;
	/*44,4*/	undefined4 field_44;
	/*48,4*/	LiveObject* object_48;
	/*4c,4*/	AIPriorityType priorityType;
	/*50,4*/	uint32 taskStartTime;
	/*54,4*/	MessageType completeAction;
	/*58,4*/	AITaskData* aiTask_58;
	/*5c,4*/	uint32 flags_5c; // not set means ptr_40 is assigned
	/*60,4*/	AITaskData* next; // assigned to DAT_004b4358
	/*64,4*/	AITaskData* nextFree; // (for listSet)
	/*68*/
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

struct BasicObjectData // [LegoRR/dummy.c|struct:0x8] This is a dummy structure that is used for CreatureData, BuildingData, and UpgradeData (for functions using these structures that have been merged together). It's highly likely this similarity is only due to linked functions performing the same behavior and being grouped together.
{
	/*0,4*/	sint32 objIndex;
	/*4,4*/	Container* aeResData; // ACT, true
	/*8*/
};

struct BatFlocks_Globs // [LegoRR/Flocks.c|struct:0x10|tags:GLOBS] (struct name changed to "BatFlocks" instead of "Flocks" to avoid annoying autocorrect when setting type in Ghidra)
{
	/*00,4*/	real32 Turn;
	/*04,4*/	real32 Speed;
	/*08,4*/	real32 Tightness;
	/*0c,4*/	real32 GoalUpdate;
	/*10*/
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
	/*00,4*/	sint32 objIndex;
	/*04,4*/	Direction direction;
	/*08,4*/	sint32 int_8;
	/*0c,8*/	Point2I pointi_c;
	/*14,4*/	Point2I* shapePoints;
	/*18,4*/	uint32 shapeCount;
	/*1c,8*/	undefined field_0x1c_0x23[8];
	/*24,4*/	BlockConstruction* next_24;
	/*28,4*/	undefined field_0x28_0x2b[4];
	/*2c,4*/	LiveObject* liveObjs_2c[1];
	/*30,9c*/	undefined field_0x30_0xcb[156];
	/*cc,4*/	uint32 liveObjsCount_cc;
	/*d0,4*/	uint32 flags;
	/*d4*/
};

struct BlockElectricFence // [LegoRR/ElectricFence.c|struct:0x14|tags:LISTSET]
{
	/*00,4*/	LiveObject* attachedObject;
	/*04,8*/	Point2I blockPos;
	/*0c,4*/	real32 timer;
	/*10,4*/	BlockElectricFence* nextFree; // (for listSet)
	/*14*/
};

struct BlockPointer // [LegoRR/NERPs.c|struct:0xc]
{
	/*0,8*/	Point2I blockPos;
	/*8,4*/	uint32 id;
	/*c*/
};

struct BlockSpiderWeb // [LegoRR/SpiderWeb.c|struct:0xc]
{
	/*0,4*/	LiveObject* object; // "SpiderWeb" LiveObject
	/*4,4*/	real32 health; // Assumed as health, init: 100.0f
	/*8,4*/	BlockSpiderWebFlags flags;
	/*c*/
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
	/*0,4*/	LiveObject* object_0;
	/*4,4*/	real32 float_4;
	/*8*/
};

struct BuildingData // [LegoRR/Building.c|struct:0x14c]
{
	/*000,4*/	sint32 objIndex;
	/*004,4*/	Container* contAct; // ACT, true
	/*008,4*/	char* CarryNullName;
	/*00c,4*/	char* CameraNullName;
	/*010,4*/	char* DepositNullName;
	/*014,4*/	char* EntranceNullName;
	/*018,4*/	char* ToolNullName;
	/*01c,4*/	char* FireNullName; // "fire laser"
	/*020,4*/	char* yPivot;
	/*024,4*/	char* xPivot;
	/*028,18*/	Container* carryFramesTable_28[6];
	/*040,10*/	Container* cameraFramesTable_40[4];
	/*050,18*/	undefined field_0x50_0x67[24];
	/*068,4*/	undefined4 field_68;
	/*06c,4*/	undefined4 field_6c;
	/*070,4*/	uint32 CarryNullFrames;
	/*074,4*/	uint32 CameraNullFrames;
	/*078,4*/	uint32 ToolNullFrames;
	/*07c,4*/	Container* contPowerLevelScene; // LWS, true
	/*080,4*/	undefined4 field_80;
	/*084,4*/	Point2I* shapePoints; // Point2I[10]
	/*088,4*/	uint32 shapeCount;
	/*08c,14*/	ObjectUpgradesData upgrades;
	/*0a0,30*/	undefined field_0xa0_0xcf[48];
	/*0d0,4*/	real32 PivotMaxZ;
	/*0d4,4*/	real32 PivotMinZ;
	/*0d8,6c*/	undefined field_0xd8_0x143[108];
	/*144,4*/	uint32 count_144;
	/*148,4*/	uint32 flags;
	/*14c*/
};

struct Camera // [LegoRR/LegoCamera.c|struct:0xbc] May be camera data (which is related to- but not the same as viewports)
{
	/*00,4*/	CameraType camType;
	/*04,4*/	LiveObject* trackObj;
	/*08,4*/	real32 trackRadarFloat_8;
	/*0c,4*/	real32 trackRadarDist;
	/*10,4*/	real32 trackRadarYawSpeed; // A constant yaw H rotation speed applied to tracked radar objects
	/*14,4*/	undefined4 trackFPCameraFrame; // CameraFrameIndex for FP object SwapPolyFP
	/*18,c*/	Vector3F moveVector; // current 3D (really 2D) movement and directional speed
	/*24,4*/	Container* contCam; // only cont created for FP type (child of contRoot if FP)
	/*28,4*/	Container* cont2; // child of contRoot
	/*2c,4*/	Container* cont3; // child of contRoot
	/*30,4*/	Container* cont4; // child of cont2
	/*34,4*/	Container* contListener; // child of cont4 (topdown type only)
	/*38,40*/	undefined reserved1[64];
	/*78,4*/	real32 tilt; // (init: 0.0f) current tilt (Pitch, V Rotation)
	/*7c,8*/	Range2F tiltRange; // min/max tilt (Pitch, V Rotation)
	/*84,4*/	real32 yaw; // (init: 0.0f) current yaw (Angle, H Rotation)
	/*88,8*/	Range2F yawRange; // min/max yaw (Angle, H Rotation)
	/*90,4*/	real32 dist; // (init: 200.0f) current dist (Zoom)
	/*94,8*/	Range2F distRange; // min/max dist (Zoom)
	/*9c,4*/	real32 moveSpeed; // current 3D (really 2D) movement speed
	/*a0,4*/	real32 shakeIntensity;
	/*a4,4*/	real32 shakeDuration;
	/*a8,4*/	real32 shakeFloat_a8;
	/*ac,c*/	Vector3F shakeVector;
	/*b8,4*/	CameraFlags flags;
	/*bc*/
};

struct Camera_Globs // [LegoRR/LegoCamera.c|struct:0x10|tags:GLOBS]
{
	/*00,4*/	real32 CameraSpeed; // (cfg: CameraSpeed) maximum move speed of camera
	/*04,4*/	real32 CameraDropOff; // (cfg: CameraDropOff) movement deceleration
	/*08,4*/	real32 CameraAcceleration; // (cfg: CameraAcceleration) movement acceleration
	/*0c,4*/	sint32 MouseScrollIndent; // (cfg: MouseScrollIndent) area around window borders for mouse movement
	/*10*/
};

struct CFGProperty // [Gods98/Config.c|struct:0x20|tags:LISTSET] CFG file property node
{
	/*00,4*/	char* fileData; // Entire file text data for root CFGProperty only
	/*04,4*/	char* key; // Property or block key name
	/*08,4*/	char* value; // Property value or block open brace
	/*0c,4*/	uint32 depth; // Block-depth of property
	/*10,4*/	uint32 itemHashCode; // Hash of item (unused)
	/*14,4*/	CFGProperty* linkNext; // Next property in linked list
	/*18,4*/	CFGProperty* linkPrev; // Previous property in linked list
	/*1c,4*/	CFGProperty* nextFree; // (internal) used for allocation while reading(?)
	/*20*/
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

struct Config_Globs // [Gods98/Config.c|struct:0x48c|tags:GLOBS]
{
	/*000,400*/	char s_JoinPath_string[1024]; // (not part of Manager, static array in JoinPath func)
	/*400,80*/	CFGProperty* listSet[32];
	/*480,4*/	CFGProperty* freeList;
	/*484,4*/	uint32 listCount;
	/*488,4*/	uint32 flags;
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

struct Coord2I // [common.c|struct:0x4] Point2I structure using short-sized integers (name is based off the WINAPI console structure COORD, using the same ,layout)
{
	/*0,2*/	sint16 sx;
	/*2,2*/	sint16 sy;
	/*4*/
};

struct CreatureData // [LegoRR/Creature.c|struct:0x74] Possibly alphabetically correct names: Bipedal, BasicUnit, etc... (has to be before Bubble, and possible after BezierCurve or AI(Task?))
{
	/*00,4*/	sint32 objIndex;
	/*04,4*/	Container* contAct; // ACT, true
	/*08,4*/	undefined4 field_8;
	/*0c,14*/	undefined field_0xc_0x1f[20];
	/*20,4*/	char* CameraNullName;
	/*24,4*/	uint32 CameraNullFrames;
	/*28,4*/	BoolTri CameraFlipDir;
	/*2c,4*/	char* DrillNullName;
	/*30,4*/	char* FootStepNullName;
	/*34,4*/	char* CarryNullName;
	/*38,4*/	char* ThrowNullName;
	/*3c,4*/	char* DepositNullName;
	/*40,4*/	undefined4 field_40;
	/*44,4*/	undefined4 field_44;
	/*48,4*/	Container* cont_48;
	/*4c,4*/	Container* cont_4c;
	/*50,4*/	undefined4 field_50;
	/*54,10*/	Container* cameraFramesTable_54[4];
	/*64,4*/	PolyMeshData* polyMedium;
	/*68,4*/	PolyMeshData* polyHigh;
	/*6c,4*/	PolyMeshData* polyFP;
	/*70,4*/	uint32 flags;
	/*74*/
};

struct CryTuple_8 // [LegoRR/FrontEnd.c|struct:0x8]
{
	/*0,4*/	uint32 cryCount;
	/*4,4*/	uint32 unkCount;
	/*8*/
};

struct D3DRMBox // [common.c|struct:0x18] Box3F
{
	/*00,c*/	Vector3F min;
	/*0c,c*/	Vector3F max;
	/*18*/
};

struct Vertex3F // [common.c|struct:0x24] Vertex3F, Extension of D3DVertex with color field
{
	/*00,c*/	Vector3F position; // Homogeneous coordinates
	/*0c,c*/	Vector3F normal; // Normal
	/*18,4*/	real32 tu; // Texture coordinates
	/*1c,4*/	real32 tv; // Texture coordinates
	/*20,4*/	DWORD colour;
	/*24*/
};

struct DamageFont_Globs // [LegoRR/DamageFont.c|struct:0x16c|tags:GLOBS]
{
	/*000,28*/	Container_Texture* fontTextDigitsTable[10];
	/*028,4*/	Container_Texture* fontTextMinus;
	/*02c,140*/	HealthFontData instanceTable[10];
	/*16c*/
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
	/*00,4*/	ObjectType objType;
	/*04,4*/	sint32 objIndex;
	/*08,4*/	sint32 objLevel;
	/*0c,4*/	bool32 hasLevel;
	/*10*/
};

struct DependencyUnlocks // [LegoRR/Dependencies.c|struct:0x204]
{
	/*000,80*/	ObjectType objTypes[32];
	/*080,80*/	sint32 objIndexes[32];
	/*100,80*/	sint32 objLevels[32];
	/*180,80*/	bool32 objHasLevels[32]; // (unlocks for a specific level)
	/*200,4*/	uint32 count;
	/*204*/
};

struct DirectDraw_Device // [Gods98/DirectDraw.c|struct:0x114]
{
	/*000,10*/	GUID guid;
	/*010,100*/	char desc[256]; // "name (description)"
	/*110,4*/	DirectDraw_DeviceFlags flags;
	/*114*/
};

struct DirectDraw_Driver // [Gods98/DirectDraw.c|struct:0x114]
{
	/*000,10*/	GUID guid;
	/*010,100*/	char desc[256]; // "name (description)"
	/*110,4*/	DirectDraw_DriverFlags flags;
	/*114*/
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
	/*1c,4*/	DirectDraw_Driver* driverList;
	/*20,4*/	DirectDraw_Driver* selectedDriver; // (unused)
	/*24,4*/	DirectDraw_Device* deviceList;
	/*28,4*/	DirectDraw_Device* selectedDevice; // (unused)
	/*2c,4*/	DirectDraw_Mode* modeList; // "ScreenModes"
	/*30,4*/	uint32 driverCount;
	/*34,4*/	uint32 deviceCount;
	/*38,4*/	uint32 modeCount; // "ScreenModes"
	/*3c,4*/	bool32 fullScreen;
	/*40,4*/	uint32 width;
	/*44,4*/	uint32 height;
	/*48*/
};

struct DirectDraw_Mode // [Gods98/DirectDraw.c|struct:0x110]
{
	/*000,4*/	uint32 width;
	/*004,4*/	uint32 height;
	/*008,4*/	uint32 bitDepth;
	/*00c,100*/	char desc[256]; // "WxH (BPP bit)", "WxH" (windowed)
	/*10c,4*/	DirectDraw_ModeFlags flags;
	/*110*/
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
	/*48,4*/	uint32 flags;
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
	/*00,4*/	BlockElectricFence* fenceGrid; // BlockElectricFence[width * height]
	/*04,4*/	LevelData* level;
	/*08,80*/	BlockElectricFence* listSet[32];
	/*88,4*/	BlockElectricFence* freeList;
	/*8c,4*/	uint32 listCount; // (no flags)
	/*90*/
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
	/*1c,4*/	LiveObject* currentObj;
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
	/*0,4*/	FileSystemType type;
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
	/*164,4*/	LiveObject* object_164;
	/*168,4*/	bool32 dbgF10InvertLighting;
	/*16c,4*/	bool32 dbgF9CameraEditMode;
	/*170,4*/	undefined4 reserved3;
	/*174,4*/	LiveObject* dbgGetInVehicle; // (K debug key, assigned to selected vehicle, pressing K with a rock raider will tell them to get in this registered vehicle)
	/*178,4*/	Direction direction_178;
	/*17c,4*/	real32 timerTutorialBlockFlash;
	/*180*/
};

struct HealthFontData // [LegoRR/DamageFont.c|struct:0x20]
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
	/*be0,4*/	ObjectType activeObjType;
	/*be4,4*/	sint32 activeObjIndex;
	/*be8,4*/	sint32 activeObjLevel;
	/*bec,78*/	ObjectType unlockedObjTypes[30];
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
	/*00,8*/	Point2I blockPos;
	/*08,8*/	Point2F worldPos;
	/*10,4*/	real32 heading;
	/*14,4*/	void* objSrcData;
	/*18,4*/	ObjectType objType;
	/*1c,4*/	sint32 objIndex;
	/*20,4*/	real32 health;
	/*24,4*/	char* thisOLName;
	/*28,4*/	char* drivingOLName;
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
	/*08,4*/	SFXType sfxType;
	/*0c,4*/	real32 float_c;
	/*10,4*/	InfoDataFlags flags;
	/*14*/
};

struct InfoMessage // [LegoRR/Info.c|struct:0x14]
{
	/*00,4*/	InfoMessageInstance* instance;
	/*04,4*/	uint32 instanceCount;
	/*08,4*/	InfoType infoType;
	/*0c,4*/	real32 float_c;
	/*10,4*/	InfoMessage* next;
	/*14*/
};

struct InfoMessageInstance // [LegoRR/Info.c|struct:0x14]
{
	/*00,8*/	Point2I blockPos; // (-1, -1) for NULL blockPos
	/*08,4*/	LiveObject* object;
	/*0c,4*/	char* text;
	/*10,4*/	InfoMessageInstance* next;
	/*14*/
};

struct Init_Globs // [Gods98Init/Init.c|struct:0x1d444|tags:GLOBS]
{
	/*00000,4*/	uint32 driverCount;
	/*00004,4*/	uint32 deviceCount;
	/*00008,4*/	uint32 modeCount;
	/*0000c,1590*/	DirectDraw_Driver drivers[20];
	/*0159c,1590*/	DirectDraw_Device devices[20];
	/*02b2c,d480*/	DirectDraw_Mode modes[200];
	/*0ffac,4*/	DirectDraw_Driver* selDriver;
	/*0ffb0,4*/	DirectDraw_Device* selDevice;
	/*0ffb4,4*/	DirectDraw_Mode* selMode;
	/*0ffb8,4*/	bool32 selFullScreen;
	/*0ffbc,4*/	bool32 wasFullScreen; // Previous fullscreen state when Windowed button is disabled due to lack of support
	/*0ffc0,d480*/	DirectDraw_Mode validModes[200];
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
	/*0,4*/	MenuIcon* iconList;
	/*4,4*/	uint32 numIcons;
	/*8*/
};

struct ItemStruct_34 // [LegoRR/???|struct:0x10]
{
	/*00,4*/	Mesh* struct34_1;
	/*04,4*/	Mesh* struct34_2;
	/*08,4*/	Container* resData;
	/*0c,4*/	real32 time;
	/*10*/
};

struct Key_Globs // [Gods98/Keys.c|struct:0x400|tags:GLOBS]
{
	/*000,400*/	char* keyName[256];
	/*400*/
};

struct Lego_Globs // [LegoRR/Lego.c|struct:0xf00|tags:GLOBS]
{
	/*000,4*/	CFGProperty* config;
	/*004,4*/	char* gameName;
	/*008,4*/	undefined4 field_8;
	/*00c,4*/	undefined4 field_c;
	/*010,4*/	GraphicsQuality Quality;
	/*014,4*/	LevelData* level;
	/*018,4*/	Container* contRoot; // containerGlobs.root
	/*01c,4*/	Viewport* viewMain; // Viewport area: (0.0,0.0 - 1.0x1.0)
	/*020,4*/	Viewport* viewRadar; // Viewport area: (16,14 - 151x151)
	/*024,4*/	Camera* cameraMain;
	/*028,4*/	Camera* cameraRadar;
	/*02c,4*/	Camera* cameraFP;
	/*030,4*/	Container* contTopSpotlight;
	/*034,4*/	Container* contTrackSpotlight;
	/*038,4*/	Container* contFPLight;
	/*03c,4*/	Container* contFPRotLight;
	/*040,4*/	Container* contAmbientLight;
	/*044,4*/	Container* contRootSpotlight;
	/*048,4*/	Container* contRootLight;
	/*04c,4*/	Container* contFPRotLightDefault;
	/*050,4*/	real32 FPClipBlocks;
	/*054,4*/	real32 TVClipDist;
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
	/*0a0,4*/	LiveObject* objectFP;
	/*0a4,c*/	Vector3F vectorDragStartUnk_a4;
	/*0b0,4*/	real32 float_b0;
	/*0b4,4*/	real32 float_b4;
	/*0b8,4*/	real32 float_b8;
	/*0bc,4*/	real32 float_bc;
	/*0c0,8*/	Point2I pointi_c0;
	/*0c8,4*/	bool32 bool_c8;
	/*0cc,4*/	char* ObjectNames_PowerCrystal;
	/*0d0,4*/	char* ObjectNames_Ore;
	/*0d4,4*/	char* ObjectNames_ProcessedOre;
	/*0d8,4*/	char* ObjectNames_Dynamite;
	/*0dc,4*/	char* ObjectNames_Barrier;
	/*0e0,4*/	char* ObjectNames_ElectricFence;
	/*0e4,4*/	char* ObjectNames_SpiderWeb;
	/*0e8,4*/	char* ObjectNames_OohScary;
	/*0ec,4*/	char* ObjectNames_Path;
	/*0f0,4*/	char* ObjectTheNames_PowerCrystal;
	/*0f4,4*/	char* ObjectTheNames_Ore;
	/*0f8,4*/	char* ObjectTheNames_ProcessedOre;
	/*0fc,4*/	char* ObjectTheNames_Dynamite;
	/*100,4*/	char* ObjectTheNames_Barrier;
	/*104,4*/	char* ObjectTheNames_ElectricFence;
	/*108,4*/	char* ObjectTheNames_SpiderWeb;
	/*10c,4*/	char* ObjectTheNames_OohScary;
	/*110,4*/	char* ObjectTheNames_Path;
	/*114,4*/	VehicleData* VehicleData_TABLE;
	/*118,4*/	CreatureData* MiniFigureData_TABLE;
	/*11c,4*/	CreatureData* RockMonsterData_TABLE;
	/*120,4*/	BuildingData* BuildingData_TABLE;
	/*124,4*/	UpgradeData* UpgradeData_TABLE;
	/*128,4*/	char** VehicleTypes_TABLE;
	/*12c,4*/	char** MiniFigureTypes_TABLE;
	/*130,4*/	char** RockMonsterTypes_TABLE;
	/*134,4*/	char** BuildingTypes_TABLE;
	/*138,4*/	char** UpgradeTypes_TABLE;
	/*13c,2c*/	char* ToolTypes_TABLE[11];
	/*168,2c*/	char* ToolNames_TABLE[11];
	/*194,4*/	char** ObjectNames_VehicleTypes_TABLE;
	/*198,4*/	char** ObjectNames_MiniFigureTypes_TABLE;
	/*19c,4*/	char** ObjectNames_RockMonsterTypes_TABLE;
	/*1a0,4*/	char** ObjectNames_BuildingTypes_TABLE;
	/*1a4,4*/	char** ObjectNames_UpgradeTypes_TABLE;
	/*1a8,4*/	char** ObjectTheNames_VehicleTypes_TABLE;
	/*1ac,4*/	char** ObjectTheNames_MiniFigureTypes_TABLE;
	/*1b0,4*/	char** ObjectTheNames_RockMonsterTypes_TABLE;
	/*1b4,4*/	char** ObjectTheNames_BuildingTypes_TABLE;
	/*1b8,4*/	char** ObjectTheNames_UpgradeTypes_TABLE;
	/*1bc,4*/	uint32 VehicleTypes_COUNT;
	/*1c0,4*/	uint32 MiniFigureTypes_COUNT;
	/*1c4,4*/	uint32 RockMonsterTypes_COUNT;
	/*1c8,4*/	uint32 BuildingTypes_COUNT;
	/*1cc,4*/	uint32 UpgradeTypes_COUNT;
	/*1d0,48*/	char* SurfaceTypes_TABLE[18];
	/*218,48*/	char* SurfaceTypeDescriptions_name_TABLE[18];
	/*260,48*/	SFXType SurfaceTypeDescriptions_sound_TABLE[18];
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
	/*2f8,28*/	LiveObject* recordObjs[10];
	/*320,4*/	uint32 recordObjsCount;
	/*324,10*/	Area2F radarScreenRect;
	/*334,4*/	real32 tvTiltOrZoom_334;
	/*338,8*/	Point2F tvFaceDirection_338;
	/*340,4*/	real32 MedPolyRange;
	/*344,4*/	real32 HighPolyRange;
	/*348,4*/	sint32 HPBlocks;
	/*34c,c*/	ColourRGBF FogColourRGB;
	/*358,c*/	ColourRGBF HighFogColourRGB;
	/*364,4*/	real32 float_364; // level-related?
	/*368,c*/	ColourRGBF PowerCrystalRGB;
	/*374,c*/	ColourRGBF UnpoweredCrystalRGB;
	/*380,4*/	ObjectType placeObjType;
	/*384,4*/	sint32 placeObjIndex;
	/*388,4*/	Direction placeObjDirection;
	/*38c,4*/	LiveObject* placeDestSmallTeleporter;
	/*390,4*/	LiveObject* placeDestBigTeleporter;
	/*394,4*/	LiveObject* placeDestWaterTeleporter;
	/*398,4*/	real32 MinEnergyForEat;
	/*39c,4*/	Image* TutorialIcon;
	/*3a0,4*/	undefined4 field_3a0;
	/*3a4,4*/	real32 DynamiteDamageRadius;
	/*3a8,4*/	real32 DynamiteMaxDamage;
	/*3ac,4*/	real32 DynamiteWakeRadius;
	/*3b0,4*/	real32 BirdScarerRadius;
	/*3b4,50*/	ObjectType objTeleportQueueTypes_TABLE[20];
	/*404,50*/	sint32 objTeleportQueueIndexes_TABLE[20];
	/*454,4*/	uint32 objTeleportQueue_COUNT;
	/*458,4*/	real32 MiniFigureRunAway;
	/*45c,c*/	Vector3F vector_45c;
	/*468,320*/	Point2I blockPts_468[100];
	/*788,4*/	uint32 blockPtsCount_788;
	/*78c,640*/	Point2I points2x100_78c[2][100];
	/*dcc,8*/	uint32 pointsCount2_dcc[2];
	/*dd4,4*/	uint32 MaxReturnedCrystals;
	/*dd8,4*/	sint32 MouseScrollBorder;
	/*ddc,4*/	char* HealthText;
	/*de0,4*/	char* EnergyText;
	/*de4,4*/	char* CrystalsText;
	/*de8,4*/	char* OreText;
	/*dec,4*/	char* StudsText;
	/*df0,4*/	char* ToolsText;
	/*df4,4*/	char* CarryObjectText;
	/*df8,4*/	char* DrivenByText;
	/*dfc,4*/	char* OreRequiredText;
	/*e00,4*/	bool32 IsFallinsEnabled; // (not "NoFallins")
	/*e04,4*/	real32 MinDistFor3DSoundsOnTopView;
	/*e08,4*/	ViewMode viewMode; // FirstPerson or TopDown
	/*e0c,4*/	GameFlags1 flags1;
	/*e10,4*/	GameFlags2 flags2;
	/*e14,4*/	GameFlags3 flags3; // only first byte is used(?)
	/*e18,4*/	real32 InitialSlugTime;
	/*e1c,8*/	Point2F NextButtonPos;
	/*e24,8*/	Point2F BackButtonPos;
	/*e2c,4*/	Image* NextButtonImage;
	/*e30,4*/	Image* BackButtonImage;
	/*e34,4*/	Image* BackArrowImage;
	/*e38,4*/	real32 FogRate;
	/*e3c,4*/	real32 timerGame_e3c;
	/*e40,4*/	real32 elapsedAbs;
	/*e44,4*/	real32 DrainTime;
	/*e48,4*/	uint32 ReinforceHits;
	/*e4c,4*/	uint32 CDStartTrack;
	/*e50,4*/	uint32 CDTracks;
	/*e54,4*/	uint32 FallinMultiplier;
	/*e58,4*/	bool32 hasFallins;
	/*e5c,8*/	Point2F menuNextPoint;
	/*e64,8*/	Point2F menuPrevPoint;
	/*e6c,c*/	ColourRGBF DragBoxRGB;
	/*e78,4*/	Image* DialogImage;
	/*e7c,4*/	Image* DialogContrastOverlay;
	/*e80,4*/	TextWindow* DialogTextWndTitle;
	/*e84,4*/	TextWindow* DialogTextWndMessage;
	/*e88,4*/	TextWindow* DialogTextWndOK;
	/*e8c,4*/	TextWindow* DialogTextWndCancel;
	/*e90,4*/	char* CreditsTextFile;
	/*e94,4*/	char* CreditsBackAVI;
	/*e98,40*/	char* UpgradeNames_TABLE[16];
	/*ed8,4*/	sint32 BuildingUpgradeCostOre;
	/*edc,4*/	sint32 BuildingUpgradeCostStuds;
	/*ee0,4*/	char* renameInput;
	/*ee4,8*/	Point2F renamePosition;
	/*eec,4*/	char* RenameReplace;
	/*ef0,4*/	char* EndGameAVI1;
	/*ef4,4*/	char* EndGameAVI2;
	/*ef8,8*/	Point2I s_mouseBlockPos_ef8; // (static, Game_unkGameLoop_FUN_00426450)
	/*f00*/
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

#pragma pack(push, 1)
struct LevelBlock // [LegoRR/Lego.c|struct:0x48|pack:1]
{
	/*00,1*/	PredugType predug;
	/*01,1*/	SurfaceTexture texture;
	/*02,1*/	TerrainType terrain;
	/*03,1*/	uint8 field_3; // possibly direction (& 3, and x - 4, etc.)
	/*04,1*/	uint8 blockpointer;
	/*05,1*/	CryOreType cryOre;
	/*06,1*/	ErodeType erodeSpeed;
	/*07,1*/	uint8 field_7;
	/*08,4*/	LevelBlockFlags1 flags1;
	/*0c,4*/	LevelBlockFlags2 flags2;
	/*10,4*/	BlockConstruction* construct;
	/*14,4*/	real32 float_14;
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

struct LevelCollection // [LegoRR/FrontEnd.c|struct:0x14]
{
	/*00,4*/	sint32 count;
	/*04,4*/	char** LevelNames;
	/*08,4*/	char** FullNames;
	/*0c,4*/	LevelIdentifier** LevelList;
	/*10,4*/	bool32* IsLinked; // True if this level has been loaded from level links (probably makes them require unlock)
	/*14*/
};

struct LevelData // [LegoRR/Lego.c|struct:0x284]
{
	/*000,4*/	char* levelName; // (format: "Levels::level")
	/*004,4*/	SurfaceMap* surfaceMap;
	/*008,4*/	void* ptrtable_8;
	/*00c,4*/	uint32 count_c;
	/*010,4*/	undefined4 field_10;
	/*014,8*/	Size2I dimensions;
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
	/*074,8*/	Size2I surfTextSize; // surface texture width and height
	/*07c,4*/	SurfaceTextureGrid* surfTextGrid;
	/*080,4*/	ProMeshData** promeshGrid;
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
	/*0b4,4*/	char* NextLevel;
	/*0b8,4*/	LevelBlock* blocks; // grid of blocks [y][x]
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
	/*27c,4*/	LevelCompleteStatus status; // (init: 0) 2 is used for Crystal failure as well
	/*280,4*/	bool32 IsStartTeleportEnabled; // (! DisableStartTeleport)
	/*284*/
};

struct LevelIdentifier // [LegoRR/FrontEnd.c|struct:0x14]
{
	/*00,4*/	sint32 index; // Index in LevelCollection
	/*04,4*/	LevelIdentifier** LevelLinks;
	/*08,4*/	uint32 NumLinks;
	/*0c,4*/	undefined4 field_c;
	/*10,4*/	undefined4 field_10; // (is locked/unlocked?)
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

struct LiveObject // [LegoRR/LegoObject.c|struct:0x40c|tags:LISTSET]
{
	/*000,4*/	ObjectType objType;
	/*004,4*/	sint32 objIndex;
	/*008,4*/	char* customName; // max size is 11 (NOT null-terminated)
	/*00c,4*/	VehicleData* vehicle;
	/*010,4*/	CreatureData* miniFigure;
	/*014,4*/	CreatureData* rockMonster;
	/*018,4*/	BuildingData* building;
	/*01c,4*/	Container* other;
	/*020,4*/	UpgradeData* upgrade;
	/*024,4*/	RoutingBlock* routeptr_24; // Unknown pointer, likely in large allocated table
	/*028,4*/	uint32 routingBlocksTotal; // total blocks to travel for current route
	/*02c,4*/	uint32 routingBlocksCurrent; // number of blocks traveled (up to routingBlocksTotal)
	/*030,4*/	sint32 routing_count_0; // Usually 50 (max), start of RoutingData
	/*034,190*/	Point2F routing_points_4[50];
	/*1c4,c8*/	real32 rounting_distances_194[50];
	/*28c,c*/	Vector3F vector_28c;
	/*298,8*/	Point2F point_298;
	/*2a0,c*/	Vector3F vector_2a0;
	/*2ac,c*/	Vector3F faceDirection; // 1.0 to -1.0 directions that determine rotation with atan2
	/*2b8,4*/	real32 float_2b8;
	/*2bc,4*/	sint32 strafeSpeed_2bc;
	/*2c0,4*/	sint32 forwardSpeed_2c0;
	/*2c4,4*/	real32 rotateSpeed_2c4;
	/*2c8,4*/	undefined4 field_2c8;
	/*2cc,4*/	undefined4 field_2cc;
	/*2d0,4*/	undefined4 field_2d0;
	/*2d4,4*/	real32 float_2d4;
	/*2d8,4*/	bool32 unkbool_2d8;
	/*2dc,4*/	Container* resData_2dc;
	/*2e0,4*/	sint32 index_2e0;
	/*2e4,4*/	Container* resData_2e4;
	/*2e8,4*/	char* aitaskName1;
	/*2ec,4*/	char* aitaskName2;
	/*2f0,4*/	AITaskData* aitask_2f0;
	/*2f4,8*/	Point2F point_2f4; // (assigned -1.0f)
	/*2fc,4*/	LiveObject* object_2fc; // other half of object_300
	/*300,4*/	LiveObject* object_300; // other half of object_2fc
	/*304,4*/	LiveObject* carryingThisObject;
	/*308,1c*/	LiveObject* carriedObjects[7];
	/*324,4*/	uint32 numCarriedObjects;
	/*328,4*/	uint32 field_328;
	/*32c,4*/	Flocks* flocksData_32c;
	/*330,4*/	uint32 objLevel;
	/*334,4*/	ObjectStats* stats;
	/*338,4*/	real32 float_338;
	/*33c,4*/	real32 float_33c;
	/*340,4*/	real32 health; // (assigned -1.0f)
	/*344,4*/	real32 energy; // (assigned -1.0f)
	/*348,4*/	sint32* stealTableptr_348; // element size is 0x4
	/*34c,4*/	PolyMode polyMode_34c;
	/*350,4*/	sint32 soundHandle_350;
	/*354,4*/	SFXType soundHandle_354; // (engine sound only?)
	/*358,4*/	undefined4 field_358;
	/*35c,4*/	undefined4 field_35c;
	/*360,4*/	undefined4 field_360;
	/*364,4*/	LiveObject* object_364;
	/*368,4*/	real32 float_368;
	/*36c,4*/	LiveObject* drivenObject; // same as drivingThisObject
	/*370,14*/	ToolType carriedTools[5];
	/*384,4*/	uint32 numCarriedTools;
	/*388,4*/	undefined4 field_388;
	/*38c,4*/	Image* bubbleImage_38c;
	/*390,4*/	undefined4 teleporter_field_390;
	/*394,4*/	undefined4 teleporter_field_394;
	/*398,4*/	TeleporterService* teleporter_398;
	/*39c,4*/	undefined4 field_39c;
	/*3a0,4*/	undefined4 field_3a0;
	/*3a4,4*/	undefined4 field_3a4;
	/*3a8,4*/	undefined4 field_3a8;
	/*3ac,4*/	undefined4 field_3ac;
	/*3b0,4*/	undefined4 field_3b0;
	/*3b4,c*/	Vector3F vector_3b4;
	/*3c0,4*/	LiveObject* object_3c0;
	/*3c4,4*/	LiveObject* object_3c4;
	/*3c8,4*/	undefined4 field_3c8;
	/*3cc,4*/	LiveObject* object_3cc;
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
	/*408,4*/	LiveObject* nextFree; // (for listSet)
	/*40c*/
};

struct LiveObject_Globs // [LegoRR/LegoObject.c|struct:0xc644|tags:GLOBS]
{
	/*0000,80*/	LiveObject* listSet[32];
	/*0080,4*/	LiveObject* freeList;
	/*0084,4b0*/	sint32 ObjTtSFX_TABLE[20][15]; // [objType:20][objIndex:15]
	/*0534,13c*/	char* Activities_TABLE[79]; // [activityType:79]
	/*0670,4*/	void* UnkSurfaceGrid_1_TABLE;
	/*0674,4*/	void* UnkSurfaceGrid_2_TABLE;
	/*0678,4*/	uint32 UnkSurfaceGrid_COUNT;
	/*067c,4*/	real32 radarElapsed_67c;
	/*0680,4*/	uint32 listCount;
	/*0684,4*/	LiveManagerFlags flags;
	/*0688,2c*/	sint32 ToolNullIndexes_TABLE[11]; // [toolType:11] (tool priorities, behavior types?)
	/*06b4,4b00*/	uint32 ObjectLevels_Current_TABLE[20][15][16]; // [objType:20][objIndex:15][objLevel:16]
	/*51b4,4b00*/	uint32 ObjectLevels_Previous_TABLE[20][15][16]; // [objType:20][objIndex:15][objLevel:16]
	/*9cb4,4*/	uint32 NERPs_TrainFlags;
	/*9cb8,4*/	LiveObject* minifigureObj_9cb8; // MINIFIGOBJ_004e9448
	/*9cbc,a0*/	Point2I SlugHoles_TABLE[20];
	/*9d5c,50*/	Point2I RechargeSeams_TABLE[10];
	/*9dac,4*/	uint32 SlugHoles_COUNT;
	/*9db0,4*/	uint32 RechargeSeams_COUNT;
	/*9db4,2260*/	HiddenObject hiddenObjects[200];
	/*c014,4*/	uint32 hiddenObjectCount;
	/*c018,4*/	real32 float_c018; // FLOAT_004eb7a8
	/*c01c,18*/	SaveStruct_18 savestruct18_c01c;
	/*c034,400*/	LiveObject* liveObjArray256_c034[256]; // PTRLiveObject_ARRAY_004eb7c4
	/*c434,4*/	uint32 count_c434; // COUNT_004ebbc4
	/*c438,4*/	uint32 countBuildingsOnly_c438; // COUNTBuildingsOnly_004ebbc8
	/*c43c,190*/	LiveObject* liveObjArray100_c43c[100]; // Used for water docking vehicles?
	/*c5cc,4*/	uint32 uintCount_c5cc;
	/*c5d0,18*/	char* AbilityTypes_TABLE[6]; // [abilityType:6]
	/*c5e8,18*/	Image* ToolTipIcons_Abilities[6]; // [abilityType:6]
	/*c600,2c*/	Image* ToolTipIcons_Tools_TABLE[11]; // [toolType:11]
	/*c62c,4*/	Image* ToolTipIcon_Blank;
	/*c630,4*/	Image* ToolTipIcon_Ore;
	/*c634,4*/	uint32 BuildingsTeleported;
	/*c638,4*/	real32 LiveManager_TimerUnk;
	/*c63c,4*/	undefined4 s_stepCounter_c63c; // (static, counter %4 for step SFX) DAT_004ebdcc
	/*c640,4*/	void** s_FlocksDestroy_c640; // (static, Struct 0x10, used in Flocks activities (QUICK_DESTROY??)) PTR_004ebdd0
	/*c644*/
};

struct LiveObjectInfo // [LegoRR/search.c|struct:0x1c] This is some search info, that needs to be fixed up. Lot's of assumptions were made when creating this.
{
	/*00,4*/	LiveObject* liveObj;
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

struct LTRBRect2F // [common.c|struct:0x10]
{
	/*00,4*/	real32 left;
	/*04,4*/	real32 top;
	/*08,4*/	real32 right;
	/*0c,4*/	real32 bottom;
	/*10*/
};

struct LTRBRect2I // [common.c|struct:0x10]
{
	/*00,4*/	sint32 left;
	/*04,4*/	sint32 top;
	/*08,4*/	sint32 right;
	/*0c,4*/	sint32 bottom;
	/*10*/
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
	/*88c,4*/	FeatureFlags clFlags;
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

struct MenuButton // [LegoRR/FrontEnd.c|struct:0x1c]
{
	/*00,10*/	Area2F window;
	/*10,4*/	Image* HiImage;
	/*14,4*/	Image* LoImage;
	/*18,4*/	char* Text;
	/*1c*/
};

struct MenuCollection // [LegoRR/FrontEnd.c|struct:0x8]
{
	/*0,4*/	SubMenu** menus;
	/*4,4*/	uint32 count;
	/*8*/
};

struct MenuItem // [LegoRR/FrontEnd.c|struct:0x3c]
{
	/*00,4*/	char* banner;
	/*04,4*/	uint32 length;
	/*08,4*/	Font* HiFont;
	/*0c,4*/	Font* LoFont;
	/*10,4*/	MenuItemData_union itemData;
	/*14,4*/	MenuItemType itemType;
	/*18,4*/	sint32 x1;
	/*1c,4*/	sint32 y1;
	/*20,4*/	sint32 LoCenterOff;
	/*24,4*/	sint32 HiCenterOff;
	/*28,4*/	bool32 isImageItem; // (1 = hasImages?)
	/*2c,4*/	Image* LoImage;
	/*30,4*/	Image* HiImage;
	/*34,4*/	ToolTipType toolTipType;
	/*38,4*/	bool32 NotInTuto; // (string value is unchecked, but "NotInTuto" is only seen usage)
	/*3c*/
};

struct MenuItemCallbackPair // [LegoRR/dummy.c|struct:0x8]
{
	/*0,4*/	void* value;
	/*4,4*/	void* callback;
	/*8*/
};

struct MenuItemCycle // [LegoRR/FrontEnd.c|struct:0x1c]
{
	/*00,4*/	char** nameList;
	/*04,4*/	uint32 cycleCount;
	/*08,4*/	sint32 nameCount;
	/*0c,4*/	sint32* value;
	/*10,4*/	sint32 x2;
	/*14,4*/	sint32 y2;
	/*18,4*/	MenuItemCycleCallback callback;
	/*1c*/
};

struct MenuItemLevelIdentifier // [LegoRR/FrontEnd.c|struct:0x20]
{
	/*00,4*/	uint32 flags; // [0x1, 0x2, 0x4]
	/*04,4*/	char* MenuBMPName;
	/*08,4*/	Image* HiImage;
	/*0c,4*/	Image* LoImage;
	/*10,4*/	Image* LockedOverlayImage;
	/*14,4*/	sint32 FrontEndX;
	/*18,4*/	sint32 FrontEndY;
	/*1c,4*/	bool32 FrontEndOpen;
	/*20*/
};

struct MenuItemMissions // [LegoRR/FrontEnd.c|struct:0x5c]
{
	/*00,4*/	MenuItemLevelIdentifier* levelsList;
	/*04,c*/	sint32* widths[3];
	/*10,c*/	sint32* heights[3];
	/*1c,4*/	sint32 levelsCount;
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

struct MenuItemRealSlider // [LegoRR/FrontEnd.c|struct:0x1c]
{
	/*00,4*/	real32* value;
	/*04,4*/	real32 LowLimit;
	/*08,4*/	real32 HighLimit;
	/*0c,4*/	real32 Step;
	/*10,4*/	sint32 x2;
	/*14,4*/	sint32 y2;
	/*18,4*/	MenuItemRealSliderCallback callback;
	/*1c*/
};

struct MenuItemSlider // [LegoRR/FrontEnd.c|struct:0x38]
{
	/*00,4*/	sint32* value;
	/*04,4*/	sint32 LowLimit;
	/*08,4*/	sint32 HighLimit;
	/*0c,4*/	sint32 x2;
	/*10,4*/	sint32 y2;
	/*14,4*/	MenuItemSliderCallback callback;
	/*18,4*/	Image* OffBarImage;
	/*1c,4*/	Image* OnBarImage;
	/*20,4*/	Image* LeftCapImage;
	/*24,4*/	Image* RightCapImage;
	/*28,4*/	Image* LoPlusImage;
	/*2c,4*/	Image* LoMinusImage;
	/*30,4*/	Image* HiPlusImage;
	/*34,4*/	Image* HiMinusImage;
	/*38*/
};

struct MenuItemTrigger // [LegoRR/FrontEnd.c|struct:0xc]
{
	/*0,4*/	sint32* value;
	/*4,4*/	bool32 end;
	/*8,4*/	MenuItemTriggerCallback callback;
	/*c*/
};

struct MenuOverlay // [LegoRR/FrontEnd.c|struct:0x20]
{
	/*00,4*/	char* filename;
	/*04,4*/	sint32 overlayType; // (bmp, avi, lws, flh?)
	/*08,4*/	undefined4 field_8;
	/*0c,8*/	Point2I position;
	/*14,4*/	SFXType sfxType;
	/*18,4*/	MenuOverlay* previous;
	/*1c,4*/	undefined4 field_1c;
	/*20*/
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

struct Message_Globs // [LegoRR/Message.c|struct:0x14380|tags:GLOBS]
{
	/*00000,14000*/	MessageAction messageTableX2[2][2048];
	/*14000,8*/	uint32 messageCountX2[2];
	/*14008,4*/	bool32 messageX2Bool;
	/*1400c,190*/	LiveObject* selectedUnitList[100];
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
	/*00,4*/	MessageType event;
	/*04,4*/	LiveObject* argumentObj; // (this argument is only used for live objects, but it's not necessarily true that it's the same in source)
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
	/*04,4*/	LiveObject* Camera_LockedOnTarget;
	/*08,8*/	Point2I pointi_8;
	/*10,4*/	LiveObject* object_10;
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
	/*4c,4*/	ObjectType ConstructionObjectiveObjType;
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
	/*0c0,4*/	SFXType DrillSound; // (from: FUN_00464f30, invalid: 2 "SFX_Drill")
	/*0c4,4*/	SFXType DrillFadeSound; // (from: FUN_00464f30, invalid: 3 "SFX_DrillFade")
	/*0c8,4*/	SFXType EngineSound; // (from: FUN_00464f30, invalid: 0 "SFX_Bodge")
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
	/*144,4*/	ObjectStatsFlags1 flags1;
	/*148,4*/	ObjectStatsFlags2 flags2;
	/*14c,4*/	ObjectStatsFlags3 flags3;
	/*150*/
};

struct ObjectUpgradePartData // [LegoRR/Upgrade.c|struct:0x14]
{
	/*00,4*/	uint32 level;
	/*04,4*/	sint32 NullInstance;
	/*08,4*/	char* NullObjectName;
	/*0c,4*/	char* WeaponName;
	/*10,4*/	UpgradeData* upgradeData;
	/*14*/
};

struct ObjectUpgradesData // [LegoRR/Upgrade.c|struct:0x14]
{
	/*00,4*/	ObjectUpgradePartData* parts; // always ObjectUpgradePartData[200]
	/*04,4*/	uint32 count;
	/*08,4*/	sint32 currentLevel;
	/*0c,4*/	uint32 levelsMask; // [carry][scan][speed][drill]
	/*10,4*/	LiveObject** upgradeObjs;
	/*14*/
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

struct P1P2Rect2F // [common.c|struct:0x10]
{
	/*00,4*/	real32 x1;
	/*04,4*/	real32 y1;
	/*08,4*/	real32 x2;
	/*0c,4*/	real32 y2;
	/*10*/
};

struct P1P2Rect2I // [common.c|struct:0x10]
{
	/*00,4*/	sint32 x1;
	/*04,4*/	sint32 y1;
	/*08,4*/	sint32 x2;
	/*0c,4*/	sint32 y2;
	/*10*/
};

struct Panel_Globs // [LegoRR/Panels.c|struct:0x7b8|tags:GLOBS]
{
	/*000,30*/	char* panelName[12];
	/*030,240*/	PanelData panelTable[12];
	/*270,480*/	char* panelButtonName[12][24];
	/*6f0,4*/	PanelType currentPanel;
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
	/*000,4*/	PointerType currentType;
	/*004,e0*/	Image* pointerImages[56]; // (each item is either an ImageBMP or ImageFlic)
	/*0e4,e0*/	bool32 pointerIsFlic[56];
	/*1c4,1c0*/	Point2I pointerFlicPositions[56];
	/*384,e0*/	char* pointerName[56];
	/*464,4*/	real32 timer; // Countdown timer to change pointer(?)
	/*468*/
};

struct PolyMeshData // [LegoRR/MeshPoly.c|struct:0x18]
{
	/*00,4*/	Container* contMeshOrigin;
	/*04,4*/	Container* contMeshTarget;
	/*08,4*/	char* partName; // name of LoadObject file.lwo
	/*0c,4*/	uint32 index;
	/*10,4*/	uint32 flags; // (1 = dont free partName/cont_0,  2 = unk dtor behavior)
	/*14,4*/	PolyMeshData* next;
	/*18*/
};

struct Priorities_Globs // [LegoRR/Priorities.c|struct:0x4c0|tags:GLOBS]
{
	/*000,6c*/	char* priorityText[27];
	/*06c,6c*/	Image* priorityImage[27];
	/*0d8,6c*/	Image* priorityPressImage[27];
	/*144,6c*/	Image* priorityOffImage[27];
	/*1b0,6c*/	SFXType prioritySFX[27];
	/*21c,6c*/	AIPriorityType priorityTypeTable_1[27];
	/*288,d8*/	Point2F priorityPoints[27];
	/*360,6c*/	AIPriorityType priorityTypeTable_2[27];
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

struct ProMeshData // [LegoRR/???|struct:0x340]
{
	/*000,8*/	Container* promesh_ab[2];
	/*008,320*/	undefined4 table_ab[2][100];
	/*328,4*/	real32 BlockSize;
	/*32c,4*/	undefined4 field_32c;
	/*330,c*/	undefined field_0x330_0x33b[12];
	/*33c,4*/	SurfaceTextureGrid* surfTextGrid;
	/*340*/
};

struct PTL_Globs // [LegoRR/PTL.c|struct:0x144|tags:GLOBS]
{
	/*000,140*/	PTLProperty table[40];
	/*140,4*/	uint32 count;
	/*144*/
};

struct PTLProperty // [LegoRR/PTL.c|struct:0x8] Property loaded from a level's PTL config file (contains lookup index for actions)
{
	/*0,4*/	MessageType eventIndex;
	/*4,4*/	MessageType actionIndex;
	/*8*/
};

struct RadarMap // [LegoRR/RadarMap.c|struct:0x3c]
{
	/*00,4*/	SurfaceMap* surfMap;
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
	/*31d4,4*/	CFGProperty* cfgRoot;
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
	/*10,1*/	uint8 flagsByte_10;
	/*11,1*/	uint8 byte_11;
	/*12,2*/	undefined field_0x12_0x13[2];
	/*14*/
};

struct RoutingData // [LegoRR/Routing.c|struct:0x25c]
{
	/*000,4*/	uint32 count;
	/*004,190*/	Point2F points[50];
	/*194,c8*/	real32 distances[50];
	/*25c*/
};

struct RROSFileHeader // [LegoRR/ObjectRecall.c|struct:0x8] For .osf Object Recall save files
{
	/*0,4*/	char signature[4];
	/*4,4*/	uint32 count;
	/*8*/
};

struct SampleProperty // [LegoRR/SFX.c|struct:0x8]
{
	/*0,4*/	sint32 sampleIndex;
	/*4,4*/	SampleProperty* next;
	/*8*/
};

struct SaveData // [LegoRR/save.c|struct:0xb8]
{
	/*00,4*/	undefined4 field_0x0;
	/*04,4*/	undefined4 field_0x4;
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
	/*18,4*/	PanelType panelType;
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
	/*00,4*/	LiveObject* targetObj;
	/*04,4*/	Point2F* pointf_4;
	/*08,4*/	real32 float_8;
	/*0c,4*/	LiveObject* result;
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
	/*00,4*/	LiveObject* liveObj;
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
	/*0,4*/	LiveObject* object;
	/*4,4*/	uint32 index;
	/*8*/
};

struct SearchInfoObjectBlockPos_8 // [LegoRR/search.c|struct:0x8]
{
	/*0,4*/	LiveObject* optObject;
	/*4,4*/	Point2I* optBlockPos;
	/*8*/
};

struct SearchLevelIdentifier_10 // [LegoRR/search.c|struct:0x10]
{
	/*00,4*/	LevelIdentifier* result; // output level identifier (not modified on failure)
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
	/*24,4*/	LiveObject* object_24;
	/*28,4*/	sint32 int_28;
	/*2c*/
};

struct SearchObjectTypeCount_c // [LegoRR/search.c|struct:0xc]
{
	/*0,4*/	ObjectType objType;
	/*4,4*/	sint32 objIndex;
	/*8,4*/	uint32 count;
	/*c*/
};

struct SearchRadarObjectRadius_10 // [LegoRR/search.c|struct:0x10]
{
	/*00,4*/	LiveObject* object;
	/*04,8*/	Point2F worldPos;
	/*0c,4*/	real32 radius; // BlockSize -or- (BlockSize / 6.0)
	/*10*/
};

struct SearchTeleporter_10 // [LegoRR/search.c|struct:0x10] Teleporter_Creat_FUN_0046a7d0
{
	/*00,4*/	ObjectType objType;
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
	/*0000,f78*/	SampleProperty samplePropTable[495];
	/*0f78,640*/	SampleProperty sampleGroupTable[200];
	/*15b8,4*/	uint32* hashNameList;
	/*15bc,4*/	uint32 hashNameCount;
	/*15c0,4*/	uint32 sampleGroupCount;
	/*15c4,4*/	AudioFlags audioFlags;
	/*15c8,f0*/	Sound3DInstance sfxInstanceTable[10];
	/*16b8,4*/	uint32 sfxInstanceCount;
	/*16bc,4*/	real32 globalSampleDuration; // Duration is multiplied by 25.0
	/*16c0,4*/	sint32 globalSampleSoundHandle;
	/*16c4,4*/	SFXType globalSampleSFXType;
	/*16c8,28*/	SFXType soundQueueSFXTable_1[10];
	/*16f0,28*/	SoundMode soundQueueModesTable_1[10];
	/*1718,28*/	SFXType soundQueueSFXTable_2[10];
	/*1740,28*/	SoundMode soundQueueModesTable_2[10];
	/*1768,4*/	uint32 soundQueueCount_1;
	/*176c,4*/	uint32 soundQueueCount_2;
	/*1770*/
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
	/*130,4*/	SampleFlags flags;
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

struct Sound3DInstance // [LegoRR/SFX.c|struct:0x18]
{
	/*00,4*/	sint32 sampleIndex;
	/*04,4*/	IDirect3DRMFrame3* frame;
	/*08,c*/	Vector3F position;
	/*14,4*/	uint32 flags;
	/*18*/
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
	/*4,4*/	LevelData* level;
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
	/*004,25c*/	RoutingData routing;
	/*260,4*/	undefined4 unseen_260;
	/*264,4*/	real32 float_264;
	/*268,c*/	Vector3F vector_268;
	/*274,c*/	Vector3F vector_274;
	/*280,c*/	Vector3F position_280;
	/*28c,4*/	real32 float_28c;
	/*290,c*/	Vector3F vector_290;
	/*29c,4*/	undefined4 field_29c;
	/*2a0,4*/	undefined4 field_2a0;
	/*2a4,4*/	LiveObject* object_2a4;
	/*2a8,4*/	sint32 weaponType;
	/*2ac,4*/	undefined4 field_2ac;
	/*2b0*/
};

struct SubMenu // [LegoRR/FrontEnd.c|struct:0xa0]
{
	/*00,4*/	char* string_0;
	/*04,4*/	char* string_4;
	/*08,4*/	uint32 length_8; // (init: strlen(param_1))
	/*0c,4*/	Font* MenuFont; // (init: param_3)
	/*10,4*/	Image* MenuImage;
	/*14,4*/	Image* MenuImageDark;
	/*18,4*/	MenuItem* Items;
	/*1c,4*/	sint32 ItemCount;
	/*20,4*/	sint32 int_20; // (init: 15)
	/*24,4*/	undefined4 field_24;
	/*28,4*/	undefined4 field_28;
	/*2c,8*/	Point2I Position;
	/*34,4*/	uint32 uint_34;
	/*38,8*/	undefined field_0x38_0x3f[8];
	/*40,4*/	MenuOverlay* Overlays;
	/*44,4*/	bool32 AutoCenter;
	/*48,4*/	bool32 DisplayTitle;
	/*4c,4*/	bool32 isAnchored;
	/*50,8*/	Point2I AnchoredPosition;
	/*58,4*/	sint32 flags_58; // (0x2 = CanScroll)
	/*5c,40*/	char CfgName[64];
	/*9c,4*/	BoolTri PlayRandom;
	/*a0*/
};

struct SurfaceBlock // [LegoRR/Map3D.c|struct:0x28]
{
	/*00,c*/	Vector3F vector_0;
	/*0c,c*/	Vector3F vector_c;
	/*18,1*/	SurfaceTexture texture;
	/*19,1*/	SurfaceMapStruct28Flags byteflags_19;
	/*1a,1*/	uint8 heightValue; // height block value taken from high.map file
	/*1b,1*/	undefined field_0x1b;
	/*1c,8*/	Point2F textuv_1c;
	/*24,1*/	uint8 highlight; // (WallHighlightType)
	/*25,3*/	undefined field_0x25_0x27[3];
	/*28*/
};

struct SurfaceMap // [LegoRR/Map3D.c|struct:0x73d4] size 0x73d4... dear god.... no...
{
	/*0000,8*/	Size2I smallDimensions; // full map dimensions - 1
	/*0008,8*/	Size2I dimensions; // full map dimensions
	/*0010,4*/	real32 BlockSize;
	/*0014,4*/	real32 RoughLevel;
	/*0018,8*/	Size2F worldDimensions_fnegx; // (-width, +height) * BlockSize / 2.0f  (smallDimensions)
	/*0020,4*/	real32 float_20;
	/*0024,4*/	Container* contMesh_24;
	/*0028,4*/	SurfaceBlock* blocks3D; // malloc(dimensions * 0x28)
	/*002c,4*/	undefined4 field_2c;
	/*0030,4*/	IDirect3DRMMaterial2* rmMaterial2; // Material related
	/*0034,4000*/	uint8 texsGrid[128][128];
	/*4034,80*/	uint8 texsNum[128];
	/*40b4,200*/	undefined4 flat_40b4[128];
	/*42b4,7d0*/	Coord2I smallCoordsTable[500];
	/*4a84,4*/	uint32 smallCoordsNum;
	/*4a88,2710*/	Coord2I largeCoordsTable[2500];
	/*7198,4*/	uint32 largeCoordsNum;
	/*719c,230*/	SurfaceMapStruct38 table38_719c[10];
	/*73cc,4*/	Container* contMesh_73cc; // (used for table38_719c)
	/*73d0,4*/	SurfaceMapFlags flags_73d0;
	/*73d4*/
};

struct SurfaceMapStruct38 // [LegoRR/Map3D.c|struct:0x38]
{
	/*00,4*/	D3DRMGroupIndex groupID;
	/*04,4*/	real32 timer; // countdown timer
	/*08,8*/	Point2I blockPos;
	/*10,20*/	Point2F pointfsTable_10[4];
	/*30,4*/	undefined field_0x30_0x33[4];
	/*34,4*/	uint32 flags; // (0x1 = visible?)
	/*38*/
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

struct SurfaceTextureGrid // [LegoRR/???|struct:0xc]
{
	/*0,8*/	Size2I gridSize;
	/*8,4*/	Container_Texture** gridSurfaces;
	/*c*/
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
	/*478,4*/	TextType currentType;
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
	/*00,c*/	AITaskType taskTypes[3]; // Up to 3 AITaskTypes can be associated with a tool
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
	/*274,4*/	SFXType sfxType;
	/*278,4*/	ToolTipFlags flags; // (flag 0x8 IMAGE is not for "iconList")
	/*27c*/
};

struct UpgradeData // [LegoRR/Upgrade.c|struct:0x10]
{
	/*00,4*/	sint32 objectIndex;
	/*04,4*/	Container* aeResData; // ACT, true
	/*08,4*/	LiveObject* object_8;
	/*0c,4*/	undefined4 field_c;
	/*10*/
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

struct VehicleData // [LegoRR/Vehicle.c|struct:0x1ec]
{
	/*000,4*/	sint32 objIndex;
	/*004,4*/	char* WheelNullName;
	/*008,4*/	Container* contAct_1;
	/*00c,4*/	Container* contAct_2; // Optional second ae file (seen for Grannit Grinder legs)
	/*010,18*/	Container* WheelMeshes[6]; // LWO, false
	/*028,18*/	undefined4 wheel_fields_28[6];
	/*040,4*/	uint32 numWheelNulls;
	/*044,18*/	undefined field_0x44_0x5b[24];
	/*05c,4*/	undefined4 field_5c;
	/*060,4*/	undefined4 field_60;
	/*064,4*/	real32 float_64;
	/*068,4*/	real32 WheelRadius;
	/*06c,48*/	undefined field_0x6c_0xb3[72];
	/*0b4,4*/	char* DrillNullName;
	/*0b8,4*/	char* DepositNullName;
	/*0bc,4*/	char* FireNullName; // "fire laser"
	/*0c0,4*/	char* DriverNullName;
	/*0c4,4*/	char* yPivot;
	/*0c8,4*/	char* xPivot;
	/*0cc,4*/	undefined4 field_cc;
	/*0d0,4*/	undefined4 field_d0;
	/*0d4,4*/	Container* resData_d4;
	/*0d8,4*/	BoolTri CameraFlipDir;
	/*0dc,4*/	char* CarryNullName;
	/*0e0,4*/	char* CameraNullName;
	/*0e4,1c*/	Container* carryFramesTable_e4[7];
	/*100,c*/	undefined field_0x100_0x10b[12];
	/*10c,10*/	Container* cameraFramesTable_10c[4];
	/*11c,4*/	uint32 CarryNullFrames;
	/*120,4*/	uint32 CameraNullFrames;
	/*124,14*/	ObjectUpgradesData upgrades;
	/*138,30*/	undefined field_0x138_0x167[48];
	/*168,4*/	real32 PivotMaxZ;
	/*16c,4*/	real32 PivotMinZ;
	/*170,54*/	undefined field_0x170_0x1c3[84];
	/*1c4,18*/	Container* table6_1c4[6];
	/*1dc,4*/	undefined4 field_1dc;
	/*1e0,4*/	PolyMeshData* polyMedium_1;
	/*1e4,4*/	PolyMeshData* polyMedium_2;
	/*1e8,4*/	uint32 flags; // HoldMissing TRUE -> 0x8
	/*1ec*/
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

struct Wad_Globs // [Gods98/Wad.c|struct:0x7ec|tags:GLOBS]
{
	/*000,4*/	DWORD computerNameLength; // (address not known)
	/*004,4*/	bool32 wadLogFileAccess; // (address not known)
	/*008,4*/	FILE* s_ErrorFile_f; // (address not known)
	/*00c,168*/	Wad wads[10]; // Wad structures
	/*174,28*/	sint32 references[10]; // Current count of references to the wad file
	/*19c,10*/	char computerName[16]; // (address not known)
	/*1ac,640*/	Wad_Handle fileHandles[100];
	/*7ec*/
};

struct Wad_Handle // [Gods98/Wad.c|struct:0x10]
{
	/*00,4*/	void* data; // Pointer to the file data
	/*04,4*/	bool32 active; // Is this handle active already
	/*08,4*/	sint32 wadFile; // Wad file this handle uses
	/*0c,4*/	sint32 indexOfFileInWad; // Index of the file in the wad structure
	/*10*/
};

struct WadEntry // [Gods98/Wad.c|struct:0x10] WAD file entry metadata contained within LegoWADFile structure
{
	/*00,4*/	WadEntryFlags compression; // usually 1, 2 for RNC compression
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
	/*1b8c,4*/	CFGProperty* cfgRoot;
	/*1b90*/
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

