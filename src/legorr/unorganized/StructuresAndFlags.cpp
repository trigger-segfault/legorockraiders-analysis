

// <https://kb.rockraidersunited.com/Command-line_parameters>
enum CmdlineFlags : unsigned int
{
	//CMD_UNK_1           = 0x1,
	CMD_FULLSCREEN      = 0x2,       // set when booting the game into fullscreen
	//CMD_UNK_4           = 0x4,
	//CMD_UNK_8           = 0x8,

	//CMD_UNK_10          = 0x10,
	CMD_NM              = 0x20,      // -nm  (no management?, disables texture management for Voodoo2-based cards)
	CMD_BEST            = 0x40,      // -best
	//CMD_UNK_80          = 0x80,

	CMD_WINDOW          = 0x100,     // -window
	CMD_STARTLEVEL      = 0x200,     // -startlevel (requires: no frontend)
	CMD_CLEANSAVES      = 0x400,     // -cleansaves
	//CMD_UNK_800         = 0x800,

	//CMD_UNK_1000        = 0x1000,
	CMD_DEBUG           = 0x2000,    // -debug
	CMD_DUALMOUSE       = 0x4000,    // -dualmouse
	CMD_DEBUGCOMPLETE   = 0x8000,    // -debugcomplete (triggers: -debug)

	CMD_TESTERCALL      = 0x10000,   // -testercall (triggers: -programmer 2)
	CMD_TESTLEVELS      = 0x20000,   // -testlevels
	CMD_FTM             = 0x40000,   // -ftm
	CMD_FVF             = 0x80000,   // -fvf

	CMD_REDUCESAMPLES   = 0x100000,  // -reducesamples
	CMD_SHOWVERSION     = 0x200000,  // -showversion
	CMD_REDUCEANIMATION = 0x400000,  // -reduceanimation
	CMD_REDUCEPROMESHES = 0x800000,  // -reducepromeshes

	CMD_REDUCEFLICS     = 0x1000000, // -reduceflics
	CMD_REDUCEIMAGES    = 0x2000000, // -reduceimages
	//CMD_UNK_4000000     = 0x4000000,
	//CMD_UNK_8000000     = 0x8000000,

	//CMD_UNK_10000000    = 0x10000000,
	//CMD_UNK_20000000    = 0x20000000,
	//CMD_UNK_40000000    = 0x40000000,
	//CMD_UNK_80000000    = 0x80000000,

	// These are parsed, but do not assign a flag
	// CMD_FLAGS           = ??, // -flags      (set as global g_DEBUG_FLAGS)
	// CMD_FPSLOCK         = ??, // -fpslock    (set as global g_FPSLOCK_VSYNC)
	// CMD_PROGRAMMER      = ??, // -programmer (set as global g_PROGRAMMER_MODE)
	// CMD_NOSOUND         = ??, // -nosound    (set as exclusive bool out-value)
	// CMD_INSISTONCD      = ??, // -insistOnCD (set as exclusive bool out-value)
};

// It's likely a lot of these modes where made to run unit tests/etc.
// many could have been removed in the release build.
enum ProgrammerMode : unsigned int
{
	PROGRAMMER_OFF     = 0,
	PROGRAMMER_MODE_1  = 1,
	PROGRAMMER_MODE_2  = 2, // condition for >1 and -testlevels
	PROGRAMMER_MODE_3  = 3, // front end and intros are disabled (>=3)
	PROGRAMMER_MODE_4  = 4, // one check if (> 3)
	PROGRAMMER_MODE_10 = 10, // test level AVI's?
	PROGRAMMER_MODE_11 = 11, // (crashes after title loading bar)
	// more values exist, at least up to and including 10?
};

enum LevelCompleteStatus : int
{
	LEVELSTATUS_NONE            = 0,
	LEVELSTATUS_COMPLETE        = 1,
	LEVELSTATUS_FAILED          = 2,
	LEVELSTATUS_FAILED_CRYSTALS = 3,
	LEVELSTATUS_FAILED_OTHER    = 4,
};

// Flags at <LegoRR.exe @00557ecc>
enum GameFlags1 : unsigned int
{
	GAME1_UNK_FLAGS_GROUP_A = 0x80c20, // unconditionally set in Game_loadLegoCFG

	//GAME1_UNK_1                = 0x1,
	GAME1_UNK_2                = 0x2, // see Game_unkGameLoop?_FUN_00426450
	GAME1_UNK_4                = 0x4, // Set when loading level? (used in & ~mask)
	GAME1_UNK_8                = 0x8, // see Main_GameUpdate
	
	GAME1_SOUNDON              = 0x10,     // Main::SoundOn
	//GAME1_UNK_20               = 0x20,
	//GAME1_UNK_40               = 0x40,
	//GAME1_UNK_80               = 0x80,

	GAME1_UNK_100              = 0x100, // see Game_unkGameLoop?_FUN_00426450 (masked together with 0x200)
	GAME1_UNK_200              = 0x200, // see Game_unkGameLoop?_FUN_00426450 (masked together with 0x100)
	//GAME1_UNK_400              = 0x400,
	GAME1_UNK_800              = 0x800, // see Main_GameUpdate

	GAME1_UNK_1000             = 0x1000, // see Main_GameUpdate
	GAME1_UNK_2000             = 0x2000, // see Game_unkGameLoop?_FUN_00426450
	//GAME1_UNK_4000             = 0x4000,
	GAME1_FOGCOLOURRGB         = 0x8000, // Levels::*::FogColourRGB

	GAME1_HIGHFOGCOLOURRGB     = 0x10000, // Levels::*::HighFogColourRGB
	GAME1_UNK_20000            = 0x20000, // see Main_GameUpdate
	GAME1_UNK_40000            = 0x40000, // see Game_unkGameLoop?_FUN_00426450, Main_GameUpdate
	//GAME1_UNK_80000            = 0x80000,

	GAME1_UNK_100000           = 0x100000, // see FUN_0041cc60, Main_GameUpdate
	GAME1_UNK_200000           = 0x200000, // see FUN_0042dd70, Main_GameUpdate
	GAME1_ONLYBUILDONPATHS     = 0x400000, // Main::OnlyBuildOnPaths (this property is not respected, loaded but unused?)
	GAME1_ALWAYSROCKFALL       = 0x800000, // Main::AlwaysRockFall

	GAME1_UNK_1000000          = 0x1000000, // see Game_unkDebugKeysInput__00428810 (masked / toggled)
	GAME1_UNK_2000000          = 0x2000000, // see Main_GameUpdate
	GAME1_STREAMNERPSSPEACH    = 0x4000000, // Main::StreamNERPSSpeach
	GAME1_UNK_8000000          = 0x8000000, // see Game_unkGameLoop?_FUN_00426450

	GAME1_UNK_10000000         = 0x10000000, // see Game_unkGameLoop?_FUN_00426450
	GAME1_UNK_20000000         = 0x20000000, // see Main_GameUpdate
	//GAME1_UNK_40000000         = 0x40000000,
	GAME1_UNK_80000000         = 0x80000000, // see Main_GameUpdate (used as & ~mask)
};

// Flags at <LegoRR.exe @00557ed0>
enum GameFlags2 : unsigned int
{
	GAME2_CALLTOARMS          = 0x1, // CallToArms "Action Stations" is on
	//GAME2_ACTIONSTATIONS      = 0x1, // CallToArms "Action Stations" is on (alias)
	//GAME2_UNK_2               = 0x2,
	GAME2_UNK_4               = 0x4, // see Game_unkGameLoop?_FUN_00426450 (used as & ~mask)
	GAME2_SHOWDEBUGTOOLTIPS   = 0x8, // Main::ShowDebugToolTips (requires: -programmer)
	
	GAME2_ALLOWDEBUGKEYS      = 0x10, // Main::AllowDebugKeys (requires: -programmer)
	GAME2_ALLOWEDITMODE       = 0x20, // Main::AllowEditMode (requires: -programmer)
	GAME2_UNK_40              = 0x40, // see Game_unkGameLoop?_FUN_00426450
	GAME2_UNK_80              = 0x80, // see Game_unkGameLoop?_FUN_00426450
	
	GAME2_UNK_100             = 0x100, // see Main_GameUpdate
	GAME2_UNK_200             = 0x200, // see Main_GameUpdate
	GAME2_UNK_400             = 0x400, // see Game_unkGameLoop?_FUN_00426450
	GAME2_MUSICON             = 0x800, // Main::MusicOn

	GAME2_UNK_1000            = 0x1000, // see Game_unkGameLoop?_FUN_00426450
	GAME2_NOMULTISELECT       = 0x2000, // NoMultiSelect   (used in Game_unkGameLoop?_FUN_00426450)
	GAME2_UNK_4000            = 0x4000, // see Main_GameUpdate
	GAME2_UNK_8000            = 0x8000, // see Main_GameUpdate

	//GAME2_UNK_10000           = 0x10000,
	GAME2_ALLOWRENAME         = 0x20000, // AllowRename
	GAME2_RECALLOLOBJECTS     = 0x40000, // RecallOLObjects
	GAME2_GENERATESPIDERS     = 0x80000, // GenerateSpiders

	GAME2_DISABLETOOLTIPSOUND = 0x100000, // DisableToolTipSound
	GAME2_NOAUTOEAT           = 0x200000, // NoAutoEat
	//GAME2_UNK_400000          = 0x400000,
	//GAME2_UNK_800000          = 0x800000,
	
	//GAME2_UNK_1000000         = 0x1000000,
	//GAME2_UNK_2000000         = 0x2000000,
	//GAME2_UNK_4000000         = 0x4000000,
	//GAME2_UNK_8000000         = 0x8000000,
	
	//GAME2_UNK_10000000        = 0x10000000,
	//GAME2_UNK_20000000        = 0x20000000,
	//GAME2_UNK_40000000        = 0x40000000,
	//GAME2_UNK_80000000        = 0x80000000,

};
// Flags at <LegoRR.exe @00557ed4>
enum GameFlags3 : unsigned int
{
	GAME3_UNK_1        = 0x1,
	GAME3_UNK_2        = 0x2,
	GAME3_UNK_4        = 0x4,
	GAME3_UNK_8        = 0x8,

	GAME3_UNK_10       = 0x10,
	GAME3_UNK_20       = 0x20,
	GAME3_UNK_40       = 0x40,
	GAME3_UNK_80       = 0x80, // see FUN_00434db0

	_GAME3_MASK_ff     = 0xff, // see FUN_00435950 (used in & ~mask)

	///NOTE: flags only seem to go up to 0xff

	//GAME3_UNK_100      = 0x100,
	//GAME3_UNK_200      = 0x200,
	//GAME3_UNK_400      = 0x400,
	//GAME3_UNK_800      = 0x800,

	//GAME3_UNK_1000     = 0x1000,
	//GAME3_UNK_2000     = 0x2000,
	//GAME3_UNK_4000     = 0x4000,
	//GAME3_UNK_8000     = 0x8000,

	//GAME3_UNK_10000    = 0x10000,
	//GAME3_UNK_20000    = 0x20000,
	//GAME3_UNK_40000    = 0x40000,
	//GAME3_UNK_80000    = 0x80000,

	//GAME3_UNK_100000   = 0x100000,
	//GAME3_UNK_200000   = 0x200000,
	//GAME3_UNK_400000   = 0x400000,
	//GAME3_UNK_800000   = 0x800000,
	
	//GAME3_UNK_1000000  = 0x1000000,
	//GAME3_UNK_2000000  = 0x2000000,
	//GAME3_UNK_4000000  = 0x4000000,
	//GAME3_UNK_8000000  = 0x8000000,
	
	//GAME3_UNK_10000000 = 0x10000000,
	//GAME3_UNK_20000000 = 0x20000000,
	//GAME3_UNK_40000000 = 0x40000000,
	//GAME3_UNK_80000000 = 0x80000000,
};


struct LegoBMP {
	/*00,4*/ unsigned int width;
	/*04,4*/ unsigned int height;
	/*08,4*/ unsigned int field_8; // 1 (planes? layers? frames?)
	/*0c,4*/ unsigned int field_c; // 1 (planes? layers? frames?)
	/*10,4*/ unsigned int bitsPerPixel;
	/*14,4*/ BOOL isRGB; // (RGB and not indexed palette?)
	/*18,4*/ unsigned int stride;
	/*1c,4*/ unsigned char* pixels;
	/*20,4*/ unsigned int field_20; // 0
	/*24,4*/ unsigned int field_24; // 0xfc (8-bit only)  // font related?
	/*28,4*/ unsigned int field_28; // 0xfc (8-bit only)  // font related?
	/*2c,4*/ unsigned int field_2c; // 0xfc (8-bit only)  // font related?
	/*30,4*/ unsigned int field_30; // 0xfc (8-bit only)  // font related?
	/*34,4*/ unsigned int numColors;
	/*38,4*/ LegoRGB* colors; // pointer -> LegoRGB[256] (malloc)
	/*3c*/
};

struct LEVEL_STRUCTPTR_SIZE_284__005570d4
{
	/*1fc,4*/ float float_1fc;
	/*284*/
};

struct CFGProperty
{
	/*00,4*/ char* fileText; // the entire CFG file text (only stored for root property)
	/*04,4*/ char* key;   // init: NULL
	/*08,4*/ char* value; // init: NULL
	/*0c,4*/ unsigned int depth;    // init: 0 (if root)
	/*10,4*/ unsigned int field_10; // init: 0 (unknown usage)
	/*14,4*/ CFGProperty* next; // init: NULL
	/*18,4*/ CFGProperty* previous;  // init: NULL (if root)

	/*1c,4*/ ReservedPool<CFGProperty>* m_next;
	/*20*/
};


// Flags at <LegoRR.exe @00500e68>
enum ObjInfoFlags : unsigned int
{
	OBJINFO_HUNGERIMAGES       = 0x1,
	OBJINFO_HEALTHBAR          = 0x2, // (show healthbars)
	//OBJINFO_UNK_4              = 0x4,
	OBJINFO_HEALTHBAR_VERTICAL = 0x8, // (only included if OBJINFO_HEALTHBAR)
	OBJINFO_BUBBLEIMAGES       = 0x10,
};


enum Textures : int
{
	TEXTURE_ROCK = 0,
	TEXTURE_LAVA = 1,
	TEXTURE_ICE  = 2,
};

enum MenuItemType : int
{
	MENUITEM_INVALID    = -1,
	MENUITEM_CYCLE      = 0, // toggle between 2 or more states (pass a data address)
	MENUITEM_TRIGGER    = 1, // (pass a function)
	MENUITEM_TEXTINPUT  = 2, // (not supported)
	MENUITEM_SLIDER     = 3,
	MENUITEM_REALSLIDER = 4,
	MENUITEM_NEXT       = 5, // goto another submenu Menu%d in same same full Menu
};


enum GraphicsQuality : int
{
	QUALITY_WIREFRAME = 0,
	//QUALITY_UNK_1     = 1,
	QUALITY_FLAT      = 2,
	QUALITY_GOURAUD   = 3,
};


struct Struct_2c
{
	/*00,4*/
	/*28,4*/ ReservedPool<Struct_2c>* m_next;
	/*2c*/
};

struct Struct_830
{

	/*830*/
};

enum MiscObjectType : int
{
	OBJECT_TVCAMERA      = -1,
	//OBJECT_UNK_0         = 0, // (not seen yet, invalid?)
	OBJECT_NONE          = 0,
	OBJECT_VEHICLE       = 1, // [table]
	OBJECT_MINIFIGURE    = 2, // [table]
	OBJECT_ROCKMONSTER   = 3, // [table]
	OBJECT_BUILDING      = 4, // [table]
	OBJECT_BOULDER       = 5,
	OBJECT_POWERCRYSTAL  = 6,
	/*alias*/ OBJECT_CRYSTAL = OBJECT_POWERCRYSTAL,
	OBJECT_ORE           = 7, // [normal, processed]
	OBJECT_DYNAMITE      = 8,
	OBJECT_BARRIER       = 9,
	//OBJECT_UNK_10        = 10, // (not seen yet)
	OBJECT_ELECTRICFENCE = 11,
	OBJECT_SPIDERWEB     = 12,
	OBJECT_OOHSCARY      = 13,
	//OBJECT_UNK_14        = 14, // (not seen yet)

	OBJECT_PATH          = 15,
	/*alias*/ OBJECT_POWERPATH = OBJECT_PATH,
	OBJECT_PUSHER        = 16,
	OBJECT_FREEZER       = 17,
	//OBJECT_UNK_18        = 18, // (not seen yet)
	OBJECT_LASERSHOT     = 19,
};
enum OreType : int
{
	ORE_NORMAL            = 0,
	ORE_PROCESSED         = 1, // (refined, stud)
	/*alias*/ ORE_STUD    = ORE_PROCESSED,
	/*alias*/ ORE_REFINED = ORE_PROCESSED,
};
enum RockMonsterType : int
{
	///TODO: Are these orders mandatory? (I know some of the game has rock monster types hardcoded, but maybe only be name)
	ROCK_MONSTER = 0,
	LAVA_MONSTER = 1,
	ICE_MONSTER  = 2,
};


struct BuildingData
{

	/*148,4*/ unsigned int flags;
	/*14c*/
};
struct MiniFigureData
{

	/*74*/
};
struct RockMonsterData
{

	/*74*/
};
struct VehicleData
{

	/*1e0,4*/ ObjectSubdata* subdata_1e0;
	/*1e4,4*/ ObjectSubdata* subdata_1e4;
	/*1e8,4*/ unsigned int flags;
	/*1ec*/
};
struct UpgradeData
{
	/*10*/
};
struct CreatureData
{
	/*04,4*/ void* ptr_4;

	/*64,4*/ ObjectSubdata* subdata_64;
	/*68,4*/ ObjectSubdata* subdata_68;
	/*6c,4*/ ObjectSubdata* subdata_6c;
	/*70,4*/ unsigned int flags;
	/*74*/
};
struct ObjectSubdata
{
	/*00,4*/ unsigned int field_0;
	/*04,4*/ unsigned int field_4;
	/*08,4*/ unsigned int field_8;
	/*0c,4*/ unsigned int field_c;
	/*10,4*/ unsigned int subflags;
	/*14*/ ObjectSubdata* next;
	/*18*/
};
struct ObjectBigSubdata
{

};

struct MiscObject10Data
{
	/*00,4*/ unsigned int field_0;
	/*04,4*/ unsigned int field_4;
	/*08,4*/ unsigned int field_8;
	/*0c,4*/ unsigned int field_c;
	/*10*/
};

struct MiscObjectData
{
	/*000,4*/ MiscObjectType objType; // ObjType 0 may be intentionally used as NONE
	/*004,4*/ int objIndex;

	/*00c,4*/ VehicleData* vehicle;
	/*010,4*/ MiniFigureData* miniFigure;
	/*014,4*/ RockMonsterData* rockMonster;
	/*018,4*/ BuildingData* building;
	/*01c,4*/ OtherObjectData* other;
	/*020,4*/ MiscObject10Data* object10;

	/*2f4,4*/ float float_2f4; // assigned -1.0f
	/*2f8,4*/ float float_2f8; // assigned -1.0f

	/*328,4*/ unsigned int field_328;

	/*334,4*/ unsigned int field_334;

	/*340,4*/ float float_340; // assigned -1.0f
	/*344,4*/ float float_344; // assigned -1.0f

	/*3e8,4*/ unsigned int field_3e8; // assigned 0 (flags?)
	/*3ec,4*/ unsigned int field_3ec;
	/*3f0,4*/ unsigned int field_3f0; // assigned 0 (flags?)
	/*408*/ ReservedPool<MiscObjectData>* m_next;
	/*40c*/
};

struct UnkStruct
{
	/*00,4*/ 
	/*04,4*/ 
	/*08,4*/ char* keyName; // copied key name (owner of this buffer)
	/*0c,4*/ unsigned int index;
	/*10,4*/ unsigned int field_10; // set to 0x2, or 0x0 for "NULL"
	/*14,4*/ UnkStruct* unkPrevious;
};


struct LegoCFGBigStruct
{
	/*DAT_005570c0*/

	/*000,4*/ CFGProperty g_LegoCfgRoot;
	/*004,4*/ const char* g_CFG_ROOTPATH;
	/*008,4*/ undefined4 field_8;
	/*00c,4*/ undefined4 field_c;
	/*010,4*/ GraphicsQuality g_GraphicsQuality; // DAT_005570d0
	/*014,4*/ void* g_LEVEL_STRUCTPTR_SIZE_284__005570d4; // g_LEVEL_STRUCTPTR_SIZE_284__005570d4
	/*018,4*/ undefined4 DAT_005570d8;
	/*01c,4*/ undefined4 DAT_005570dc;
	/*020,4*/ undefined4 DAT_005570e0;
	/*024,4*/ void* PTR_005570e4; //DAT_005570e0;
	/*028,4*/ undefined4 DAT_005570e8;
	/*02c,4*/ undefined4 DAT_005570ec;
	/*030,4*/ Struct_2c* PTR_005570f0; // DAT_005570f0;
	/*034,4*/ undefined4 DAT_005570f4;
	/*038,4*/ Struct_2c* PTR_005570f8; //DAT_005570f8;
	/*03c,4*/ Struct_2c* PTR_005570fc; //DAT_005570fc;
	/*040,4*/ Struct_2c* PTR_00557100; //DAT_00557100;
	/*044,4*/ Struct_2c* PTR_00557104; //DAT_00557104;
	/*048,4*/ Struct_2c* PTR_00557108; //DAT_00557108;
	/*04c,4*/ Struct_2c* PTR_0055710c; //DAT_0055710c;
	/*050,4*/ float FLOAT_00557110; // DAT_00557110;
	/*054,4*/ float g_tvclipdist; // FLOAT_00557114; //DAT_00557114;
	/*058,4*/ undefined4 field_58;
	/*05c,4*/ undefined4 field_5c;
	/*060,4*/ undefined4 field_60;
	/*064,4*/ void* g_FONT_FONT5_HI;
	/*068,4*/ void* g_FONT_ToolTipFont;
	/*06c,4*/ void* g_FONT_DeskTopFont;
	/*070,4*/ void* g_FONT_font5_HI;
	/*074,4*/ void* g_FONT_MbriefFONT;
	/*078,4*/ void* g_FONT_MbriefFONT2;
	/*07c,4*/ void* g_FONT_RSFont;
	/*080,4*/ Struct_830* PTR_00557140; //DAT_00557140;
	/*084,4*/ Struct_830* PTR_00557144; //DAT_00557144;
	/*088,4*/ float FLOAT_00557148; // DAT_00557148;
	/*08c,4*/ float FLOAT_0055714c; // DAT_0055714c;
	/*090,4*/ float FLOAT_00557150; // DAT_00557150;
	/*094,4*/ float FLOAT_00557154; // DAT_00557154;
	/*098,4*/ BOOL BOOL_00557158; // DAT_00557158;
	/*09c,4*/ float FLOAT_0055715c; // DAT_0055715c;
	/*0a0,4*/ undefined4 DAT_00557160;
	/*0a4,4*/ float FLOAT_00557164; // DAT_00557164;
	/*0a8,4*/ float FLOAT_00557168; // DAT_00557168;
	/*0ac,4*/ float FLOAT_0055716c; // DAT_0055716c;
	/*0b0,4*/ float FLOAT_00557170; // DAT_00557170;
	/*0b4,4*/ float FLOAT_00557174; // DAT_00557174;
	/*0b8,4*/ float FLOAT_00557178; // DAT_00557178;
	/*0bc,4*/ float FLOAT_0055717c; // DAT_0055717c;
	/*0c0,4*/ undefined4 DAT_00557180;
	/*0c4,4*/ undefined4 DAT_00557184;
	/*0c8,4*/ BOOL BOOL_00557188; // DAT_00557188;
	/*0cc,4*/ char* g_ObjectNames_PowerCrystal;
	/*0d0,4*/ char* g_ObjectNames_Ore;
	/*0d4,4*/ char* g_ObjectNames_ProcessedOre;
	/*0d8,4*/ char* g_ObjectNames_Dynamite;
	/*0dc,4*/ char* g_ObjectNames_Barrier;
	/*0e0,4*/ char* g_ObjectNames_ElectricFence;
	/*0e4,4*/ char* g_ObjectNames_SpiderWeb;
	/*0e8,4*/ char* g_ObjectNames_OohScary;
	/*0ec,4*/ char* g_ObjectNames_Path;
	/*0f0,4*/ char* g_ObjectTheNames_PowerCrystal;
	/*0f4,4*/ char* g_ObjectTheNames_Ore;
	/*0f8,4*/ char* g_ObjectTheNames_ProcessedOre;
	/*0fc,4*/ char* g_ObjectTheNames_Dynamite;
	/*100,4*/ char* g_ObjectTheNames_Barrier;
	/*104,4*/ char* g_ObjectTheNames_ElectricFence;
	/*108,4*/ char* g_ObjectTheNames_SpiderWeb;
	/*10c,4*/ char* g_ObjectTheNames_OohScary;
	/*110,4*/ char* g_ObjectTheNames_Path;
	/*114,4*/ VehicleData* g_VehicleData_TABLE;
	/*118,4*/ MiniFigureData* g_MiniFigureData_TABLE;
	/*11c,4*/ RockMonsterData* g_RockMonsterData_TABLE;
	/*120,4*/ BuildingData* g_BuildingData_TABLE;
	/*124,4*/ UpgradeData* g_UpgradeData_TABLE;
	/*128,4*/ char** g_VehicleTypes_TABLE;
	/*12c,4*/ char** g_MiniFigureTypes_TABLE;
	/*130,4*/ char** g_RockMonsterTypes_TABLE;
	/*134,4*/ char** g_BuildingTypes_TABLE;
	/*138,4*/ char** g_UpgradeTypes_TABLE;
	/*13c,2c*/ char* g_ToolTypes_TABLE[11];
	/*168,2c*/ char* g_ToolNames_TABLE[11];
	/*194,4*/ char** g_ObjectNames_VehicleTypes_TABLE;
	/*198,4*/ char** g_ObjectNames_MiniFigureTypes_TABLE;
	/*19c,4*/ char** g_ObjectNames_RockMonsterTypes_TABLE;
	/*1a0,4*/ char** g_ObjectNames_BuildingTypes_TABLE;
	/*1a4,4*/ char** g_ObjectNames_UpgradeTypes_TABLE;
	/*1a8,4*/ char** g_ObjectTheNames_VehicleTypes_TABLE;
	/*1ac,4*/ char** g_ObjectTheNames_MiniFigureTypes_TABLE;
	/*1b0,4*/ char** g_ObjectTheNames_RockMonsterTypes_TABLE;
	/*1b4,4*/ char** g_ObjectTheNames_BuildingTypes_TABLE;
	/*1b8,4*/ char** g_ObjectTheNames_UpgradeTypes_TABLE;
	/*1bc,4*/ unsigned int g_VehicleTypes_COUNT;
	/*1c0,4*/ unsigned int g_MiniFigureTypes_COUNT;
	/*1c4,4*/ unsigned int g_RockMonsterTypes_COUNT;
	/*1c8,4*/ unsigned int g_BuildingTypes_COUNT;
	/*1cc,4*/ unsigned int g_UpgradeTypes_COUNT;
	/*1d0,48*/ char* g_SurfaceTypes_TABLE[18];
	/*218,48*/ char* g_SurfaceTypeDescriptions_name_TABLE[18];
	/*260,48*/ void* g_SurfaceTypeDescriptions_sound_TABLE[18];
	/*2a8,4*/ undefined4 g_RES_BOULDER;
	/*2ac,4*/ undefined4 DAT_0055736c;
	/*2b0,4*/ undefined4 DAT_00557370;
	/*2b4,4*/ undefined4 g_RES_POWERCRYSTAL;
	/*2b8,4*/ undefined4 g_RES_DYNAMITE;
	/*2bc,8*/ undefined4 g_RES_ORES_TABLE[2];
	/*2c4,4*/ undefined4 g_RES_OOHSCARY;
	/*2c8,4*/ undefined4 g_RES_BARRIER;
	/*2cc,4*/ undefined4 g_RES_ELECTRICFENCE;
	/*2d0,4*/ undefined4 g_RES_SPIDERWEB;
	/*2d4,4*/ undefined4 DAT_00557394;
	/*2d8,4*/ undefined4 DAT_00557398;
	/*2dc,4*/ undefined4 DAT_0055739c;
	/*2e0,4*/ undefined4 g_RES_PUSHER;
	/*2e4,4*/ undefined4 g_RES_FREEZER;
	/*2e8,4*/ undefined4 DAT_005573a8;
	/*2ec,4*/ undefined4 DAT_005573ac;
	/*2f0,4*/ undefined4 g_RES_LASERSHOT;
	/*2f4,4*/ undefined4 DAT_005573b4;
	/*2f8,28*/ undefined4 g_UNK_TABLE__005573b8[10];
	/*320,4*/ unsigned int UINT_005573e0;
	/*324,4*/ float FLOAT_005573e4;
	/*328,4*/ float FLOAT_005573e8;
	/*32c,4*/ float FLOAT_005573ec;
	/*330,4*/ float FLOAT_005573f0;
	/*334,4*/ float FLOAT_005573f4;
	/*338,4*/ undefined4 DAT_005573f8;
	/*33c,4*/ undefined4 DAT_005573fc;
	/*340,4*/ float g_MedPolyRange;
	/*344,4*/ float g_HighPolyRange;
	/*348,4*/ unsigned4 int g_HPBlocks;
	/*34c,c*/ ColourRGBF g_FogColourRGB;
	/*358,c*/ ColourRGBF g_HighFogColourRGB;
	/*364,4*/ float g_LEVEL_UNK_FLOAT_00557424;
	/*368,c*/ ColourRGBF g_PowerCrystalRGB;
	/*374,c*/ ColourRGBF g_UnpoweredCrystalRGB;
	/*380,4*/ int INT_00557440;
	/*384,4*/ int INT_00557444;
	/*388,4*/ int INT_00557448;
	/*38c,4*/ MiscObjectData* PTR_0055744c;
	/*390,4*/ MiscObjectData* PTR_00557450;
	/*394,4*/ MiscObjectData* PTR_00557454;
	/*398,4*/ float g_MinEnergyForEat;
	/*39c,4*/ void* PTR_0055745c; // bmp?
	/*3a0,4*/ undefined4 field_3a0;
	/*3a4,4*/ float g_DynamiteDamageRadius;
	/*3a8,4*/ float g_DynamiteMaxDamage;
	/*3ac,4*/ float g_DynamiteWakeRadius;
	/*3b0,4*/ float g_BirdScarerRadius;
	/*3b4,50*/ undefined4 UNK_ARRAY_00557474[20];
	/*404,50*/ undefined4 UNK_ARRAY_005574c4[20];
	/*454,4*/ unsigned int UINT_00557514; // count for above 2 arrays
	/*458,4*/ float g_MiniFigureRunAway;
	/*45c,4*/ float FLOAT_0055751c;
	/*460,4*/ float FLOAT_00557520;
	/*464,4*/ float FLOAT_00557524;
	/*468,320*/ undefined4 UNK_ARRAY_00557528[200];
	/*788,4*/ unsigned int UINT_00557848;
	/*78c,320*/ undefined4 UNK_ARRAY_0055784c[200];
	/*aac,320*/ undefined4 UNK_ARRAY_00557b6c[200];
	/*dcc,4*/ unsigned int UINT_00557e8c;
	/*dd0,4*/ unsigned int UINT_00557e90;
	/*dd4,4*/ unsigned int g_MaxReturnedCrystals;
	/*dd8,4*/ unsigned int g_MouseScrollBorder;
	/*ddc,4*/ char* g_HealthText;
	/*de0,4*/ char* g_EnergyText;
	/*de4,4*/ char* g_CrystalsText;
	/*de8,4*/ char* g_OreText;
	/*dec,4*/ char* g_StudsText;
	/*df0,4*/ char* g_ToolsText;
	/*df4,4*/ char* g_CarryObjectText;
	/*df8,4*/ char* g_DrivenByText;
	/*dfc,4*/ char* g_OreRequiredText;
	/*e00,4*/ BOOL g_YesFallins; // opposite of Lego.cfg "NoFallins" setting
	/*e04,4*/ float g_MinDistFor3DSoundsOnTopView;
	/*e08,4*/ unsigned int g_GAME_UNK_BOOL_00557ec8; // may not be bool, value tested against 0 and 1
	/*e0c,4*/ unsigned int g_GAME_GameFlags1;
	/*e10,4*/ unsigned int g_GAME_GameFlags2;
	/*e14,4*/ unsigned int g_GAME_GameFlags3; // only first byte is used(?)
	/*e18,4*/ float g_InitialSlugTime;
	// /*e1c,4*/ float g_NextButton_x;
	// /*e20,4*/ float g_NextButton_y;
	/*e1c,8*/ Point2F g_NextButton;
	/*e24,8*/ Point2F g_BackButtonPos;
	// /*e24,4*/ float g_BackButtonPos_x;
	// /*e28,4*/ float g_BackButtonPos_y;
	/*e2c,4*/ void* PTR_00557eec; // bmp?
	/*e30,4*/ void* PTR_00557ef0; // bmp?
	/*e34,4*/ void* PTR_00557ef4; // bmp?
	/*e38,4*/ float g_LEVEL_FogRate;
	/*e3c,4*/ float FLOAT_00557efc;
	/*e40,4*/ float FLOAT_00557f00; // assigned to Game_Update param_1 float fpsSync
	/*e44,4*/ float g_DrainTime;
	/*e48,4*/ unsigned int g_ReinforceHits;
	/*e4c,4*/ unsigned int g_CDStartTrack;
	/*e50,4*/ unsigned int g_CDTracks;
	/*e54,4*/ unsigned int g_LEVEL_FallinMultiplier;
	/*e58,4*/ BOOL BOOL_00557f18;
	/*e5c,4*/ undefined4 DAT_00557f1c;
	/*e60,4*/ undefined4 DAT_00557f20;
	/*e64,4*/ undefined4 DAT_00557f24;
	/*e68,4*/ undefined4 DAT_00557f28;
	/*e6c,c*/ ColourRGBF g_DragBoxRGB;
	/*e78,4*/ void* PTR_00557f38;
	/*e7c,4*/ void* PTR_00557f3c;
	/*e80,4*/ void* PTR_00557f40;
	/*e84,4*/ void* PTR_00557f44;
	/*e88,4*/ void* PTR_00557f48;
	/*e8c,4*/ void* PTR_00557f4c;
	/*e90,4*/ char* g_CreditsTextFile;
	/*e94,4*/ char* g_CreditsBackAVI;
	/*e98,40*/ char* g_UpgradeNames_TABLE[16];
	/*ed8,4*/ unsigned int g_BuildingUpgradeCostOre;
	/*edc,4*/ unsigned int g_BuildingUpgradeCostStuds;
	/*ee0,4*/ undefined4 DAT_00557fa0;
	/*ee4,4*/ float FLOAT_00557fa4;
	/*ee8,4*/ float FLOAT_00557fa8;
	/*eec,4*/ char* g_RenameReplace;
	/*ef0,4*/ char* g_EndGameAVI1;
	/*ef4,4*/ char* g_EndGameAVI2;
	/*ef8*/
};


struct SampleProperty
{
	/*0,4*/ int sampleIndex;
	/*4,4*/ SampleProperty* next;
	/*8*/
};

// Parse in Samples block
// Order: *, #, @
enum SampleFlags : unsigned int
{
	SAMPLE_ISUSED   = 0x1,
	SAMPLE_VOLUME   = 0x2, // '#%d#' specifier
	SAMPLE_MULTIPLE = 0x4, // '*' specifier (and not '@' specifier)
	SAMPLE_STREAMED = 0x8, // '@' specifier
};

struct SampleData
{
	/*0,104*/ char filename[MAX_PATH /*260*/];       // 00507698
	/*104,4*/ unsigned int fileLength; // field_104; // 0050779c
	/*108,4*/ unsigned int avgBytesPerSec; // avgBytesPerSec // 005077a0
	/*10c,4*/ unsigned int field_10c;
	/*110,4*/ int volumeAdjust;  // '#%d#' (-10000 to 0)
	/*114,4*/ unsigned int field_114;
	/*118,4*/ HGLOBAL hGlobal_118;
	/*11c,4*/ HGLOBAL hGlobal_11c;
	/*120,4*/ unsigned int field_120;
	/*124,4*/ unsigned int field_124;
	/*128,4*/ unsigned int field_128;
	/*12c,4*/ unsigned int field_12c;
	/*130,4*/ SampleFlags flags; // 005077c8  (0x1 == isUsed)
	/*134*/
};

struct PTLProperty
{
	/*0,4*/ int eventIndex;
	/*4,4*/ int actionIndex;
	/*8*/
};

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

enum NERPSFunctionArgs : int
{
	NERPS_ARGS_0          = 0, // takes 0 arguments, returns value
	NERPS_ARGS_1          = 1, // takes 1 arguments, returns value
	NERPS_ARGS_2          = 2, // takes 2 arguments, returns value (never used)
	NERPS_ARGS_0_NORETURN = 3, // takes 0 arguments, no return
	NERPS_ARGS_1_NORETURN = 4, // takes 1 arguments, no return
	NERPS_ARGS_2_NORETURN = 5, // takes 2 arguments, no return
	NERPS_ARGS_3_NORETURN = 6, // takes 3 arguments, no return
	NERPS_END_OF_LIST     = 7, // invalid (end of list)
};

typedef int (__cdecl *NERPSFunction)(int*); // argument is pointer to first item in stack

struct NERPSFunctionSignature
{
	/*0,4*/ const char* name;
	/*4,4*/ NERPSFunction* function;
	/*8,4*/ NERPSFunctionArgs arguments;
	/*c*/
};

enum FileLocation : int
{
	FILELOC_WAD   = 0,
	FILELOC_REAL  = 1,
	FILELOC_STD   = 1,
	FILELOC_ERROR = 2,
};


enum WADEntryFlags : unsigned int
{
	WADENTRY_UNK_1 = 0x1, // common value seen for all entries
	WADENTRY_UNK_2 = 0x2, // causes complex load behavior (uses size2)
};

struct WADEntry
{
	/*00,4*/ WADEntryFlags flags; // (originally version)
	/*04,4*/ unsigned int size;
	/*08,4*/ unsigned int size2; // may be decompressed size?
	/*0c,4*/ unsigned int offset; // absolute file offset to data
	/*10*/
};

struct WADFile
{
	/*00,4*/ unsigned int field_0;
	/*04,4*/ BOOL isUsed; // 1 if in-use
	/*08,4*/ unsigned int field_8;
	/*0c,4*/ unsigned int field_c;
	/*10,4*/ FILE* file; // file is kept open on sucessful read
	/*14,4*/ char** absdirs /*[count]*/; // absolute paths when WAD was built
	/*18,4*/ char** reldirs /*[count]*/; // file paths relative to WAD
	/*1c,4*/ WADEntry* entries /*[count]*/;
	/*20,4*/ unsigned int count;
	/*24*/
};

struct SharedWADEntry
{
	/*00,4*/ void* fileData;
	/*04,4*/ BOOL isUsed;
	/*08,4*/ int wadIndex
	/*0c,4*/ int entryIndex;
	/*10*/
};

struct WADEntryStream
{
	/*0,4*/ int sharedIndex; // index of SharedWADEntry in global table
	/*4,4*/ unsigned int position;
	/*8,4*/ unsigned int field_8;
	/*c*/
};

union FileStreamData
{
	FILE* std; // file, (referred to as STD "standard" file by engine)
	WADEntryStream* wad;
};

struct FileStream
{
	/*0,4*/ FileLocation location;
	// /*4,4*/ FileStreamData stream;
	/*4,4*/ union
	/*4,4*/ {
	/*4,4*/ 	FILE* std; // (referred to as STD "standard" file by engine)
	/*4,4*/ 	WADEntryStream* wad;
	/*4,4*/ };
	/*8*/
};

enum FileBufferFlags : unsigned int
{
	FILEBUFFER_ISUSED = 0x1,
	//FILEBUFFER_UNK_2  = 0x2,
	//FILEBUFFER_UNK_4  = 0x4,
	//FILEBUFFER_UNK_8  = 0x8,
};

struct SharedFileBuffer;
{
	/*0,4*/ void* fileData;
	/*4,4*/ unsigned int flags; // 0x1 == BOOL isUsed
	/*8*/
};

// arguments are: filename, fileSize, lpValue (value passed to File_SetOpenCallback)
typedef void (__cdecl *FileOpenCallback)(const char*, int, void*);

// Only usage of the above FileFuncPtr
// <LegoRR.exe @0044e180>
void __cdecl File_funcPtrCallback__0044e180(const char* filename, int fileSize, void* lpValue);


typedef void (__cdecl *MusicCallback)(void);

typedef BOOL (__cdecl *GameInitFunction)(void);
typedef BOOL (__cdecl *GameUpdateFunction)(float); // float argument is supposedly game time (in which case it's never reset)... or time elapsed since last update
typedef void (__cdecl *GameCleanupFunction)(void);

struct GameFunctions
{
	/*0,4*/ GameInitFunction* init;
	/*4,4*/ GameUpdateFunction* update;
	/*8,4*/ GameCleanupFunction* cleanup;
	/*c*/
};

#pragma region /// DEFINES //////////////////////////////

// When checking this memory address with OllyDbg, the value was 00000000h, meaning this **may** be a reference to an empty string!
// Ghidra's identifier for this location has been changed to: ""/*EMPTYSTR*/
//   allowing to inline the string value, while also commenting its usage everywhere.
// Original name assigned by Ghidra: "lpWindowName_ 004b9a14"  (space kept to prevent from replace-all)
// 
// Displayed as: ""/*EMPTYSTR*/, Runtime value: {'\0','\0','\0','\0'}
// <LegoRR.exe @004b9a14>  XREF[292]:
#define c_EMPTYSTR ""/*EMPTYSTR*/
//static char c_EMPTYSTR[4] = {'\0','\0','\0','\0'};

// Time unit (25 frames per second) as a double-precision floating point
#define TIME_UNIT  25.0
// Time unit (25 frames per second) as a single-precision floating point
#define TIME_UNITF 25.0f

// Size of block (in 3D-space units) as an integer
#define BLOCK_UNIT 40
// Size of block (in 3D-space units) as a single-precision floating point
#define BLOCK_UNITF 40.0f

#define s_RegistryKey "SOFTWARE\\LEGO Media\\Games\\Rock Raiders"

#pragma endregion


#pragma region /// BASIC TYPES //////////////////////////

// Many boolean returns from LegoRR functions may have a 3rd return state for error, this enum is for that.
enum BOOL3 : int
{
	BOOL3_FALSE = 0, // false
	BOOL3_TRUE  = 1, // true
	BOOL3_ERROR = 2, // error
};

struct Point2I
{
	/*0,4*/ int x;
	/*4,4*/ int y;
	/*8*/
};
struct Point2F
{
	/*0,4*/ float x;
	/*4,4*/ float y;
	/*8*/
};
struct Size2I
{
	/*0,4*/ int width;
	/*4,4*/ int height;
	/*8*/
};
struct Size2F
{
	/*0,4*/ float width;
	/*4,4*/ float height;
	/*8*/
};
struct Range2I
{
	/*0,4*/ int min;
	/*4,4*/ int max;
	/*8*/
};
struct Range2F
{
	/*0,4*/ float min;
	/*4,4*/ float max;
	/*8*/
};
struct ColourRGBI
{
	/*0,4*/ int red;
	/*4,4*/ int green;
	/*8,4*/ int blue;
	/*c*/
};
struct ColourRGBF
{
	/*0,4*/ float red;
	/*4,4*/ float green;
	/*8,4*/ float blue;
	/*c*/
};
// never observed
struct ColourRGBAF
{
	/*00,4*/ float red;
	/*04,4*/ float green;
	/*08,4*/ float blue;
	/*0c,4*/ float alpha;
	/*10*/
};

#pragma endregion

enum LegoRRResources : int
{
	LEGORR_MAIN_ICON            = 1,
	LEGORR_MODESELECTION_DIALOG = 101,
	LEGORR_MAIN_ICONGROUP       = 113,
};
enum CLGenResources : int
{
	CLGEN_MAIN_ICON             = 1,
	CLGEN_SELECTOR_DIALOG       = 101,
	CLGEN_MAIN_ICONGROUP        = 103,
};
enum LegoRRDialogControls : int
{
	LEGORR_ID_OK                     = 1, // IDOK
	LEGORR_ID_CANCEL                 = 2, // IDCANCEL
	LEGORR_ID_DRIVER_LISTBOX         = 1000,
	LEGORR_ID_DEVICE_LISTBOX         = 1002,
	LEGORR_ID_SCREENMODES_LISTBOX    = 1003, // Screen Modes | Window Sizes
	LEGORR_ID_FULLSCREEN_RADIOBUTTON = 1004,
	LEGORR_ID_WINDOW_RADIOBUTTON     = 1005,
	LEGORR_ID_SCREENMODES_LABEL      = 1006,

	LEGORR_ID_DEVICE_LABEL           = -1, // (no ID)
	LEGORR_ID_DRIVER_LABEL           = -1, // (no ID)
};
enum CLGenDialogControls : int
{
	CLGEN_ID_OK                  = 1, // IDOK
	CLGEN_ID_CANCEL              = 2, // IDCANCEL
	CLGEN_ID_SELECT_DROPDOWNLIST = 1001,
	CLGEN_ID_SELECT_LABEL        = 1006,
};

  pcVar5 = cfg::CFG_joinPath(globals::g_CFG_ROOTPATH,levelName,"surfacemap",0);
  local_1a0 = cfg::CFG_copyPropertyValue(root,pcVar5);
  pcVar5 = cfg::CFG_joinPath(globals::g_CFG_ROOTPATH,levelName,"predugmap",0);
  local_1a8 = cfg::CFG_copyPropertyValue(root,pcVar5);
  pcVar5 = cfg::CFG_joinPath(globals::g_CFG_ROOTPATH,levelName,"terrainmap",0);
  local_194 = (int *)cfg::CFG_copyPropertyValue(root,pcVar5);
  pcVar5 = cfg::CFG_joinPath(globals::g_CFG_ROOTPATH,levelName,"blockPointersMap",0);
  local_198 = cfg::CFG_copyPropertyValue(root,pcVar5);
  pcVar5 = cfg::CFG_joinPath(globals::g_CFG_ROOTPATH,levelName,"CryOreMap",0);
  local_1ac = cfg::CFG_copyPropertyValue(root,pcVar5);
  pcVar5 = cfg::CFG_joinPath(globals::g_CFG_ROOTPATH,levelName,"ErodeMap",0);
  local_18c = cfg::CFG_copyPropertyValue(root,pcVar5);
  pcVar5 = cfg::CFG_joinPath(globals::g_CFG_ROOTPATH,levelName,"EmergeMap",0);
  local_184 = cfg::CFG_copyPropertyValue(root,pcVar5);
  pcVar5 = cfg::CFG_joinPath(globals::g_CFG_ROOTPATH,levelName,"AIMap",0);
  local_188 = cfg::CFG_copyPropertyValue(root,pcVar5);
  pcVar5 = cfg::CFG_joinPath(globals::g_CFG_ROOTPATH,levelName,"PathMap",0);
  local_1a4 = cfg::CFG_copyPropertyValue(root,pcVar5);
  pcVar5 = cfg::CFG_joinPath(globals::g_CFG_ROOTPATH,levelName,"FallinMap",0);
  local_190 = cfg::CFG_copyPropertyValue(root,pcVar5);
  pcVar5 = cfg::CFG_joinPath(globals::g_CFG_ROOTPATH,levelName,"textureset",0);
  local_178 = (char *)cfg::CFG_getPropertyValue(root,pcVar5);
  pcVar5 = cfg::CFG_joinPath(globals::g_CFG_ROOTPATH,levelName,"EmergeTimeOut",0);
  iVar4 = cfg::CFG_getPropertyValue(root,pcVar5);

// EmergeMap ???




FUN_0042b440(
	(int)buffer,
	(uint)local_1a0,  // surfacemap
	(int)local_1a8,   // predugmap
	local_1b0,
	local_194,        // terrainmap
	(int)local_19c,
	(uint)local_198,  // blockPointersMap
	local_1b8,
	(uint)local_1ac,  // CryOreMap
	local_1c0._0_1_,
	(uint)local_18c,  // ErodeMap
	(uint)local_1a4,  // PathMap
	(int)local_1bc,
	local_178,        // textureset
	(uint)pcVar5,     // EmergeMap
	(uint)local_188,  // AIMap
	(uint)local_190); // FallinMap


// g_GAME_GameFlags1 |= GAME1_UNK_4
// "Seed" -> util::randomSeed(atoi(CFG_getPropertyValue()))
// "FallinMultiplier" -> g_LEVEL_FallinMultiplier = msvc::atoi() or 1;
// "NoMultiSelect" ->  g_GAME_GameFlags2 |&= GAME2_NOMULTISELECT
// "NoAutoEat" ->  g_GAME_GameFlags2 |&= GAME2_NOAUTOEAT
// "EndGameAVI1" -> g_EndGameAVI1
// "EndGameAVI2" -> g_EndGameAVI2
// "AllowRename" -> g_GAME_GameFlags2 |&= GAME2_ALLOWRENAME
// "RecallOLObjects" -> g_GAME_GameFlags2 |&= GAME2_RECALLOLOBJECTS
// "GenerateSpiders" -> g_GAME_GameFlags2 |&= GAME2_GENERATESPIDERS
// "DisableToolTipSound" -> g_GAME_GameFlags2 |&= GAME2_DISABLETOOLTIPSOUND
// "DisableEndTeleport" -> Game_SetEndTeleportEnabled(parseBool() != 1)
void __cdecl Game_SetEndTeleportEnabled(BOOL endTeleportEnabled) {
	g_IsEndTeleportEnabled = endTeleportEnabled;
}
///TODO: "DragBoxRGB" ->
// "InitialSlugTime" -> g_InitialSlugTime (default: 60.0, mult: 25.0)
// "RockFallStyle" -> Game_SetRockFallStyleIndex(name), g_RockFallStyleIndex
// "NoFallins" -> g_IsFallinsEnabled (parseBool() != 1)
// "FogColourRGB" -> g_FogColourRGB, g_GAME_GameFlags1 |&= GAME1_FOGCOLOURRGB

// "HighFogColourRGB" -> g_HighFogColourRGB, g_GAME_GameFlags1 |= GAME1_HIGHFOGCOLOURRGB
//    "FogRate" -> g_LEVEL_FogRate (default: 1500.0)

// Game_SetErodeTimes()
// "ErodeTriggerTime" -> (default: 10.0)
// "ErodeErodeTime" -> (default: 5.0)
// "ErodeLockTime" -> (default: 60.0)

// Game_SetNumberOfLandSlidesTillCaveIn()
// "NumberOfLandSlidesTillCaveIn" -> (default: 3)


enum ObjectiveFlags : unsigned int
{
	OBJECTIVE_DEFAULT = 0x10, // if no other flags are set by the end

	OBJECTIVE_UNK_1              = 0x1,
	OBJECTIVE_COMPLETE           = 0x2,
	OBJECTIVE_FAILED             = 0x4,
	OBJECTIVE_UNK_8              = 0x8,
	OBJECTIVE_SHOWADVISOR        = 0x10, // ! "DontShowObjectiveAdvisor"
	OBJECTIVE_SHOWACHEIVEADVISOR = 0x20, // ! "DontShowObjectiveAcheiveAdvisor"
	OBJECTIVE_HITTIMEFAIL        = 0x20, // "HitTimeFailObjective" same as OBJECTIVE_SHOWACHEIVEADVISOR???
	OBJECTIVE_SHOWFAILEDADVISOR  = 0x80, // ! "DontShowObjectiveFailedAdvisor"
	OBJECTIVE_CRYSTAL            = 0x100, // "CrystalObjective"
	OBJECTIVE_ORE                = 0x200, // "OreObjective"
	OBJECTIVE_BLOCK              = 0x400, // "BlockObjective"
	OBJECTIVE_TIMER              = 0x800, // "TimerObjective"
	OBJECTIVE_CONSTRUCTION       = 0x1000, // "ConstructionObjective"
};
// <LegoRR.exe @00500bc0>
static ObjectiveFlags g_ObjectiveFlags;

// setup by func: FUN_0044e380
struct LevelSurfaceMap
{
	/// my god...

	/*008,8*/ Size2I dimensions;


	/*73d4*/
};

// setup by func: FUN_0045dd50 with created surface map
struct LevelStruct_3c
{

};

struct LevelBlock
{
	 // 4:?,5:cryore,6:erode
	/*04,4*/ undefined4 blockpointers_4;
	/*08,4*/ undefined4 path_8;
	/*0c,4*/ unsigned int flags_c;


	/*34,4*/ undefined4 ai_34;
	/*38,4*/ undefined4 fallin_38;
	/*38,4*/ undefined4 fallin_3c;
	/*48*/
};

struct LevelTerrain_1c
{
	/*1c*/
};

struct LevelData
{
	/*000,4*/ char* levelName;
	/*004,4*/ LevelSurfaceMap* surfaceMap;

	/*00c,4*/ field_8;
	/*00c,4*/ field_c;

	/*014,8*/ Size2I dimensions;
	/*01c,4*/ float BlockSize;
	/*020,4*/ float DigDepth;
	/*024,4*/ float RoofHeight;
	/*028,4*/ float RoughLevel;
	/*02c,4*/ BOOL3 UseRoof;
	/*030,4*/ BOOL3 SafeCaverns;
	/*034,4*/ float SelBoxHeight;

	/*084,4*/ LevelStruct_3c* field_84;

	/*088,4*/ LevelTerrain_1c* field_88;
	/*08c,4*/ undefined4 field_8c; // (init: 0)
	/*090,4*/ undefined4 field_90; // (init: 0)
	/*094,4*/ undefined4 field_94; // (init: 0)



	/*0a0,4*/ undefined4 field_a0; // (init: 0)
	/*0a4,4*/ undefined4 field_a4; // (init: 0)
	/*0a8,4*/ undefined4 field_a8; // (init: 0)


	/*0b4,4*/ char* NextLevel;
	/*0b8,4*/ LevelBlock* blocks;

	///OBJECTIVEDATA:
	/*0bc,4*/ void* ObjectiveImage;
	/*0c0,4*/ int ObjectiveImage_width_x; //???
	/*0c4,4*/ int ObjectiveImage_height_y; //???
	/*0c8,4*/ void* ObjectiveAcheivedImage;
	/*0cc,4*/ int ObjectiveAcheivedImage_width_x; //???
	/*0d0,4*/ int ObjectiveAcheivedImage_height_y; //???
	/*0c8,4*/ void* ObjectiveAcheivedImage;
	/*0cc,4*/ int ObjectiveAcheivedImage_width_x; //???
	/*0d0,4*/ int ObjectiveAcheivedImage_height_y; //???
	/*0d4,4*/ void* ObjectiveFailedImage;
	/*0d8,4*/ int ObjectiveFailedImage_width_x; //???
	/*0dc,4*/ int ObjectiveFailedImage_height_y; //???
	/*0e0,4*/ void* ObjectiveAcheivedAVI;
	/*0e4,4*/ int ObjectiveAcheivedAVI_width_x; //???
	/*0e8,4*/ int ObjectiveAcheivedAVI_height_y; //???
	/*0f4,4*/ int CrystalObjective;
	/*0f8,4*/ int OreObjective;
	/*0fc,8*/ Point2I BlockObjective;
	/*104,4*/ float TimerObjective; // (mult: 25.0, flags, format: "time:HitTimeFailObjective")
	/*108,4*/ int ConstructionObjective_type;
	/*10c,4*/ int ConstructionObjective_index;
	///END OF OBJECTIVE DATA
	/*110,4*/ BOOL hasBlockPointers;

	/*1f4,4*/ BOOL StartFP;
	/*1f8,4*/ BOOL NoDrain;
	/*1fc,4*/ float field_1fc; // (init: 100.0, Oxygen level?)
	/*200,4*/ float OxygenRate;
	/*204,4*/ float field_1fc; // (init: 100.0, Oxygen level?)
	/*208,4*/ float BuildingTolerance; // (default: 4.0)
	/*20c,4*/ float BuildingMaxVariation; // (default: 6.0)
	/*210,50*/ float UpgradeTimes[20]; // [objType] (mult: 25.0)
	/// OVERLOADS:
	// /*214,4*/ float VehicleUpgradeTime; // (mult: 25.0)
	// /*218,4*/ float MinifigureUpgradeTime; // (mult: 25.0)
	// /*220,4*/ float BuildingUpgradeTime; // (mult: 25.0)
	/*260,4*/ float TrainTime; // (mult: 25.0)
	/*264,4*/ float EmergeTimeOut; // (default: 1500.0)
	/*268,4*/ float SlugTime; // (default: 60.0, mult: 25.0)
	/*26c,4*/ int Slug; // (default: 20, searches for object index by name, expects RockMonsterType)
	/*270,4*/ char* FullName; // (replace '_' -> ' ')
	/*274,4*/ Textures BoulderAnimation;
	/*278,4*/ float MaxStolen;
	/*27c,4*/ LevelCompleteStatus status; // (init: 0) 2 is used for Crystal failure as well
	/*280,4*/ BOOL IsStartTeleportEnabled; // (! DisableStartTeleport)
	/*284*/
};


struct LegoScreenMode
{
	/*000,4*/ int screenWidth;
	/*004,4*/ int screenHeight;
	/*008,4*/ int bitDepth;

	/*110*/
};

struct ErodeState
{
	/*0,4*/ undefined4 field_0;
	/*4,4*/ undefined4 field_4;
	/*8*/
};

// <LegoRR.exe @005570c0 -> 00557fb8>
struct LegoCFGBigStruct
{
	/*ef8*/
};

/// GLOBALS //////////////////////////////
// <LegoRR.exe @00506f84>
static CmdlineFlags g_CMDLINE_FLAGS = 0;
// <LegoRR.exe @00506f88>
static unsigned int g_PROGRAMMER_MODE = 0;

// <LegoRR.exe @00506f8c>
static char g_STARTLEVEL[256];
// <LegoRR.exe @0050693c>
static float g_FPSLOCK_VSYNC = 0.0f;
// <LegoRR.exe @0050708c>
static unsigned int g_DEBUG_FLAGS = 0;


enum ObjectStatsFlags1 : unsigned int
{
	STATS1_SingleWidthDig         = 0x1, // (leveled)
	STATS1_ProcessOre             = 0x2,
	STATS1_ProcessCrystal         = 0x4,
	STATS1_StoreObjects           = 0x8,

	STATS1_SmallTeleporter        = 0x10,
	STATS1_BigTeleporter          = 0x20,
	STATS1_WaterTeleporter        = 0x40,
	STATS1_CollRadius             = 0x80,

	STATS1_CollBox                = 0x100, // (only with not CollRadius)
	STATS1_CauseSlip              = 0x200,
	STATS1_RandomMove             = 0x400,
	STATS1_CanScare               = 0x800,

	STATS1_RandomEnterWall        = 0x1000,
	STATS1_ScaredByPlayer         = 0x2000,
	STATS1_SnaxULike              = 0x4000,
	STATS1_GrabMinifigure         = 0x8000,

	STATS1_CanClearRubble         = 0x10000,
	STATS1_CanBeDriven            = 0x20000,
	STATS1_CanScareScorpion       = 0x40000,
	STATS1_CanSteal               = 0x80000,

	STATS1_ToolStore              = 0x100000,
	STATS1_Flocks                 = 0x200000,
	STATS1_Flocks_Debug           = 0x400000,
	STATS1_Flocks_Smooth          = 0x800000,

	STATS1_CrossWater             = 0x1000000,
	STATS1_CrossLand              = 0x2000000,
	STATS1_Flocks_OnGround        = 0x4000000,
	STATS1_Flocks_QuickDestroy    = 0x8000000,

	STATS1_Flocks_AnimateByPitch  = 0x10000000,
	STATS1_RouteAvoidance         = 0x20000000,
	STATS1_BumpDamage             = 0x40000000,
	STATS1_ManTeleporter          = 0x80000000,
};
enum ObjectStatsFlags2 : unsigned int
{
	STATS2_ScaredByBigBangs       = 0x1,
	STATS2_UpgradeBuilding        = 0x2,
	STATS2_TrainPilot             = 0x4, // (leveled)
	STATS2_TrainSailor            = 0x8, // (leveled)

	STATS2_TrainDriver            = 0x10, // (leveled)
	STATS2_TrainDynamite          = 0x20, // (leveled)
	STATS2_TrainRepair            = 0x40, // (leveled)
	STATS2_TrainScanner           = 0x80, // (leveled)

	STATS2_Tracker                = 0x100, // (has mounted laser?)
	STATS2_GeneratePower          = 0x200, // (not a stand-alone flag, always combined with SelfPowered)
	STATS2_SelfPowered            = 0x400,
	STATS2_PowerBuilding          = 0x600,
	STATS2_UseBigTeleporter       = 0x800,

	STATS2_UseSmallTeleporter     = 0x1000,
	STATS2_UseWaterTeleporter     = 0x2000,
	STATS2_AttackPaths            = 0x4000,
	STATS2_SplitOnZeroHealth      = 0x8000,

	STATS2_CanBeHitByFence        = 0x10000,
	STATS2_CanDoubleSelect        = 0x20000,
	STATS2_CanBeShotAt            = 0x40000,
	STATS2_DrainPower             = 0x80000,

	STATS2_UseHoles               = 0x100000,
	STATS2_CrossLava              = 0x200000,
	STATS2_UseLegoManTeleporter   = 0x400000,
	STATS2_DamageCausesCallToArms = 0x800000,

	STATS2_CanFreeze              = 0x1000000,
	STATS2_CanLaser               = 0x2000000,
	STATS2_CanPush                = 0x4000000,
	STATS2_DontShowDamage         = 0x8000000, // (don't show RPG damage number effect)

	STATS2_RemoveReinforcement    = 0x10000000,
	STATS2_DontShowOnRadar        = 0x20000000,
	STATS2_InvisibleDriver        = 0x40000000,
	STATS2_Unselectable           = 0x80000000,
};
enum ObjectStatsFlags3 : unsigned int
{
	STATS3_CarryVehicles          = 0x1,
	STATS3_VehicleCanBeCarried    = 0x2,
	STATS3_CanStrafe              = 0x4,
	STATS3_ClassAsLarge           = 0x8,

	STATS3_GetOutAtLand           = 0x10,
	STATS3_GetInAtLand            = 0x20,
	STATS3_TakeCarryingDrivers    = 0x40,
	STATS3_ShowHealthBar          = 0x80,

	STATS3_NeedsPilot             = 0x100, // NEVER SEEN
	STATS3_EnterToolStore         = 0x200,
	//STATS3_UNK_400                = 0x400,
	//STATS3_UNK_800                = 0x800,

	//STATS3_UNK_1000               = 0x1000,
	//STATS3_UNK_2000               = 0x2000,
	//STATS3_UNK_4000               = 0x4000,
	//STATS3_UNK_8000               = 0x8000,

	//STATS3_UNK_10000              = 0x10000,
	//STATS3_UNK_20000              = 0x20000,
	//STATS3_UNK_40000              = 0x40000,
	//STATS3_UNK_80000              = 0x80000,

	//STATS3_UNK_100000             = 0x100000,
	//STATS3_UNK_200000             = 0x200000,
	//STATS3_UNK_400000             = 0x400000,
	//STATS3_UNK_800000             = 0x800000,

	//STATS3_UNK_1000000            = 0x1000000,
	//STATS3_UNK_2000000            = 0x2000000,
	//STATS3_UNK_4000000            = 0x4000000,
	//STATS3_UNK_8000000            = 0x8000000,

	//STATS3_UNK_10000000           = 0x10000000,
	//STATS3_UNK_20000000           = 0x20000000,
	//STATS3_UNK_40000000           = 0x40000000,
	//STATS3_UNK_80000000           = 0x80000000,
};



enum ObjectStatsFlags1 : unsigned int
{
	STATS1_SINGLEWIDTHDIG         = 0x1, // (leveled)
	STATS1_PROCESSORE             = 0x2,
	STATS1_PROCESSCRYSTAL         = 0x4,
	STATS1_STOREOBJECTS           = 0x8,

	STATS1_SMALLTELEPORTER        = 0x10,
	STATS1_BIGTELEPORTER          = 0x20,
	STATS1_WATERTELEPORTER        = 0x40,
	STATS1_COLLRADIUS             = 0x80,

	STATS1_COLLBOX                = 0x100, // (only with not CollRadius)
	STATS1_CAUSESLIP              = 0x200,
	STATS1_RANDOMMOVE             = 0x400,
	STATS1_CANSCARE               = 0x800,

	STATS1_RANDOMENTERWALL        = 0x1000,
	STATS1_SCAREDBYPLAYER         = 0x2000,
	STATS1_SNAXULIKE              = 0x4000,
	STATS1_GRABMINIFIGURE         = 0x8000,

	STATS1_CANCLEARRUBBLE         = 0x10000,
	STATS1_CANBEDRIVEN            = 0x20000,
	STATS1_CANSCARESCORPION       = 0x40000,
	STATS1_CANSTEAL               = 0x80000,

	STATS1_TOOLSTORE              = 0x100000,
	STATS1_FLOCKS                 = 0x200000,
	STATS1_FLOCKS_DEBUG           = 0x400000,
	STATS1_FLOCKS_SMOOTH          = 0x800000,

	STATS1_CROSSWATER             = 0x1000000,
	STATS1_CROSSLAND              = 0x2000000,
	STATS1_FLOCKS_ONGROUND        = 0x4000000,
	STATS1_FLOCKS_QUICKDESTROY    = 0x8000000,

	STATS1_FLOCKS_ANIMATEBYPITCH  = 0x10000000,
	STATS1_ROUTEAVOIDANCE         = 0x20000000,
	STATS1_BUMPDAMAGE             = 0x40000000,
	STATS1_MANTELEPORTER          = 0x80000000,
};
enum ObjectStatsFlags2 : unsigned int
{
	STATS2_SCAREDBYBIGBANGS       = 0x1,
	STATS2_UPGRADEBUILDING        = 0x2,
	STATS2_TRAINPILOT             = 0x4, // (leveled)
	STATS2_TRAINSAILOR            = 0x8, // (leveled)

	STATS2_TRAINDRIVER            = 0x10, // (leveled)
	STATS2_TRAINDYNAMITE          = 0x20, // (leveled)
	STATS2_TRAINREPAIR            = 0x40, // (leveled)
	STATS2_TRAINSCANNER           = 0x80, // (leveled)

	STATS2_TRACKER                = 0x100, // (has mounted laser?)
	STATS2_GENERATEPOWER          = 0x200, // (not a stand-alone flag, always combined with SelfPowered)
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
	STATS2_DONTSHOWDAMAGE         = 0x8000000, // (don't show RPG damage number effect)

	STATS2_REMOVEREINFORCEMENT    = 0x10000000,
	STATS2_DONTSHOWONRADAR        = 0x20000000,
	STATS2_INVISIBLEDRIVER        = 0x40000000,
	STATS2_UNSELECTABLE           = 0x80000000,
};
enum ObjectStatsFlags3 : unsigned int
{
	STATS3_CARRYVEHICLES          = 0x1,
	STATS3_VEHICLECANBECARRIED    = 0x2,
	STATS3_CANSTRAFE              = 0x4,
	STATS3_CLASSASLARGE           = 0x8,

	STATS3_GETOUTATLAND           = 0x10,
	STATS3_GETINATLAND            = 0x20,
	STATS3_TAKECARRYINGDRIVERS    = 0x40,
	STATS3_SHOWHEALTHBAR          = 0x80,

	STATS3_NEEDSPILOT             = 0x100, // NEVER SEEN
	STATS3_ENTERTOOLSTORE         = 0x200,
	//STATS3_UNK_400                = 0x400,
	//STATS3_UNK_800                = 0x800,

	//STATS3_UNK_1000               = 0x1000,
	//STATS3_UNK_2000               = 0x2000,
	//STATS3_UNK_4000               = 0x4000,
	//STATS3_UNK_8000               = 0x8000,

	//STATS3_UNK_10000              = 0x10000,
	//STATS3_UNK_20000              = 0x20000,
	//STATS3_UNK_40000              = 0x40000,
	//STATS3_UNK_80000              = 0x80000,

	//STATS3_UNK_100000             = 0x100000,
	//STATS3_UNK_200000             = 0x200000,
	//STATS3_UNK_400000             = 0x400000,
	//STATS3_UNK_800000             = 0x800000,

	//STATS3_UNK_1000000            = 0x1000000,
	//STATS3_UNK_2000000            = 0x2000000,
	//STATS3_UNK_4000000            = 0x4000000,
	//STATS3_UNK_8000000            = 0x8000000,

	//STATS3_UNK_10000000           = 0x10000000,
	//STATS3_UNK_20000000           = 0x20000000,
	//STATS3_UNK_40000000           = 0x40000000,
	//STATS3_UNK_80000000           = 0x80000000,
};

// one struct created for each of an object's levels
struct ObjectStats
{
	/*000,4*/ undefined4 field_0;
	/*004,4*/ undefined4 field_4;
	/*008,4*/ undefined4 field_8;
	/*00c,4*/ undefined4 field_c;
	/*010,4*/ undefined4 field_10;
	/*014,4*/ undefined4 field_14;
	/*018,4*/ undefined4 field_18;
	/*01c,4*/ undefined4 field_1c;
	/*020,4*/ float RouteSpeed; // (leveled)
	          /// DRILL TIMES: float[18] (leveled, mult: 25.0) other times are unused? Index may be related to SurfaceTypes
	// /*024,48*/ float DrillTimes[18];
	/*024,4*/ float field_DrillTime_0;
	/*028,4*/ float field_DrillTime_1;
	/*02c,4*/ float HardDrillTime; // (leveled)
	/*030,4*/ float MedDrillTime; // (leveled)
	/*034,4*/ float LooseDrillTime; // (leveled)
	/*038,4*/ float SoilDrillTime // (leveled, is this rubble clear speed? Or unused?)
	/*03c,4*/ float field_DrillTime_6;
	/*040,4*/ float field_DrillTime_7;
	/*044,4*/ float SeamDrillTime_A; // (leveled, property: SeamDrillTime) ore or crystal?
	/*048,4*/ float field_DrillTime_9;
	/*04c,4*/ float SeamDrillTime_B; // (leveled, property: SeamDrillTime) ore or crystal?
	/*050,4*/ float field_DrillTime_11;
	/*054,4*/ float field_DrillTime_12;
	/*058,4*/ float field_DrillTime_13;
	/*05c,4*/ float field_DrillTime_14;
	/*060,4*/ float field_DrillTime_15;
	/*064,4*/ float field_DrillTime_16;
	/*068,4*/ float field_DrillTime_17;
	          /// END DRILL TIMES
	/*06c,4*/ float CollRadius; // (effect: flags1 | 0x80)
	/*070,4*/ float AlertRadius;
	/*074,4*/ float CollHeight;
	/*078,4*/ float PickSphere;
	/*07c,4*/ float TrackDist;
	/*080,4*/ float HealthDecayRate;
	/*084,4*/ float EnergyDecayRate;
	/*088,4*/ float RepairValue; // (leveled)
	/*08c,4*/ float RestPercent;
	/*090,4*/ float CarryMinHealth;
	/*094,4*/ float StampRadius;
	/*098,4*/ float AttackRadius;
	/*09c,4*/ float WakeRadius; // (default: 20.0)
	/*0a0,8*/ Size2F CollBox; // (requires: invalid/no CollRadius, effect: flag 0x100, CollRadius = min(w,h) * 0.5)
	// /*0a0,4*/ float CollBox_width; // (requires: invalid CollRadius, effect: flag 0x100, CollRadius = min(w,h) * 0.5)
	// /*0a4,4*/ float CollBox_height; // (requires: invalid CollRadius)
	/*0a8,4*/ undefined4 BuildingBase; // (from: FUN_00408bb0, invalid: -1, either ptr or basenumber) // NEVER SEEN
	/*0ac,4*/ int SurveyRadius; // (leveled)
	/*0b0,4*/ int CostOre;
	/*0b4,4*/ int CostCrystal;
	/*0b8,4*/ int CostRefinedOre;
	/*0bc,4*/ int CrystalDrain; // (leveled)
	/*0c0,4*/ int DrillSound; // (from: FUN_00464f30, invalid: 2 "SFX_Drill")
	/*0c4,4*/ int DrillFadeSound; // (from: FUN_00464f30, invalid: 3 "SFX_DrillFade")
	/*0c8,4*/ int EngineSound; // (from: FUN_00464f30, invalid: 0 "SFX_Bodge")
	/*0cc,4*/ int NumOfToolsCanCarry; // (leveled)
	/*0d0,4*/ int WaterEntrances;
	/*0d4,4*/ float RubbleCoef; // (default: 1.0)
	/*0d8,4*/ float PathCoef; // (default: 1.0)
	/*0dc,4*/ float OxygenCoef; // (negative consumes oxygen)
	/*0e0,4*/ int Capacity;
	/*0e4,4*/ float AwarenessRange; // (default: 0.0)
	/*0e8,4*/ float PainThreshold; // (default: 0.0)
	/*0ec,4*/ int MaxCarry; // (leveled)
	/*0f0,4*/ int CarryStart; // (leveled)
	/*0f4,4*/ float UpgradeTime; // (leveled, mult: 25.0)
	/*0f8,4*/ float FunctionCoef; // (leveled)
	/*0fc,4*/ int UpgradeCostOre;   // Carry:Scan:Speed:Drill (requires all 4)
	/*100,4*/ int UpgradeCostStuds; // Carry:Scan:Speed:Drill (requires all 4)
	/*104,4*/ undefined4 field_104;
	/*108,4*/ undefined4 field_108;
	/*10c,4*/ float FreezerTime; // (default: 0.0)
	/*110,4*/ float FreezerDamage; // (default: 0.0)
	/*114,4*/ float PusherDist; // (default: 0.0)
	/*118,4*/ float PusherDamage; // (default: 0.0)
	/*11c,4*/ float LaserDamage; // (default: 0.0)
	/*120,4*/ float Flocks_Turn; // (default: 0.06)
	/*124,4*/ float Flocks_Speed; // (default: 2.0)
	/*128,4*/ float Flocks_Tightness; // (default: 2.0)
	/*12c,4*/ float Flocks_GoalUpdate; // (default: 2.0)
	/*130,4*/ float Flocks_Height; // (default: 30.0)
	/*134,4*/ float Flocks_Randomness; // (default: 2.0)
	/*138,4*/ float Flocks_AttackTime; // (default: 300.0)
	/*13c,4*/ int Flocks_Size; // (default: 5)
	/*140,4*/ float RandomMoveTime; // (default: 200.0)
	/*144,4*/ ObjectFlags1 flags1;
	/*148,4*/ ObjectFlags2 flags2;
	/*14c,4*/ ObjectFlags3 flags3;
	/*150*/
};

struct ObjectLevels
{

};

// <LegoRR.exe @00503bd8> // distance = 80 (0x50), so not all object types support stats
static ObjectStats** g_ObjectStats_TABLE[20]; //[objType][objIndex][objLevel]
// <LegoRR.exe @00503c28>
static int g_ObjectLevels_TABLE[20][15]; // 15 * number of object types

*(char **)(&DAT_00503c28 + (local_148 + local_14c * 0xf) * 4) = local_134;

//static ObjectType DAT_00503bd8[]; // object types

	Samples {
		SFX_Bodge
		!SFX_Drip
		SFX_Drill
		SFX_DrillFade
		SFX_RockBreak
		SFX_FallIn
      ;...

[Carry][Scan][Speed][Drill]

        iVar10 = 0;
        pcVar4 = local_134;
        do {
          *(char ***)( + 0x6c + iVar10) = local_12c;
          *(float *)( + 0x70 + iVar10) = local_114;
 //iVar2 = *(int *)(*(int *)(&DAT_00503bd8 + local_14c*4) + local_148*4);
          *(float *)(/*iVar2*/ + 0xa0 + iVar10) = local_f0;
          *(float *)(/*iVar2*/ + 0xa4 + iVar10) = local_ec;
          *(char **)( + 0x78 + iVar10) = local_130;
          *(float *)( + 0x7c + iVar10) = local_120;
          *(char **)( + 0x74 + iVar10) = local_118;
          *(float *)( + 0x80 + iVar10) = local_110;
          *(float *)( + 0x84 + iVar10) = local_100;
          *(char **)( + 0xa8 + iVar10) = local_144;
          *(int *)( + 0xc0 + iVar10) = local_e0;
          *(int *)( + 0xc4 + iVar10) = local_e8;
          *(BOOL *)( + 0xc8 /*200*/ + iVar10) = local_e4;
          *(float *)( + 0x8c + iVar10) = local_10c;
          iVar10 += 0x150;
          pcVar4--;
          *(float *)( /*0x90*/ -0xc0 + iVar10) = local_104;
          *(float *)( /*0x94*/ -0xbc + iVar10) = local_fc;
          *(float *)( /*0x98*/ -0xb8 + iVar10) = local_f8;
          *(float *)( /*0xd0*/ -0x80 + iVar10) = local_f4;
          *(float *)( /*0xd4*/ -0x7c + iVar10) = local_11c;
          *(char ***)(/*0xd8*/ -0x78 + iVar10) = local_138;
          *(float *)( /*0xdc*/ - 0x74 + iVar10) = local_108;
          *(int *)(   /*0xe0*/ - 0x70 + iVar10) = local_dc;
          *(int *)(   /*0xb4*/ - 0x9c + iVar10) = local_d8;
          *(int *)(   /*0xb0*/ - 0xa0 + iVar10) = local_d4;
          *(char **)( /*0xb8*/ - 0x98 + iVar10) = local_124;
        } while (pcVar4 != (char *)0x0);
      }
