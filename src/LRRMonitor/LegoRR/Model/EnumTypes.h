#pragma once
#include "../../framework.h"

namespace lego {
#pragma region Enums

// Disable "the enum type E is unscoped" warnings
#pragma warning( push )
#pragma warning( disable: 26812 )


#pragma region Framework: Basic Enums

// Many boolean returns from LegoRR functions may have a 3rd return state for error, this enum is for that.
enum BOOL3 : int
{
	BOOL3_FALSE = 0, // false
	BOOL3_TRUE  = 1, // true
	BOOL3_ERROR = 2, // error
};
static_assert(sizeof(BOOL3) == 0x4, "");

// 4-way direction enum
enum Direction : int
{
	DIRECTION__INVALID = -1,

	DIRECTION_UP       = 0,
	DIRECTION_RIGHT    = 1,
	DIRECTION_DOWN     = 2,
	DIRECTION_LEFT     = 3,

	DIRECTION__COUNT   = 4,
};
static_assert(sizeof(Direction) == 0x4, "");

// 8-way direction enum
enum Angle : int
{
	ANGLE__INVALID  = -1,

	ANGLE_UP        = 0,
	ANGLE_UPRIGHT   = 1,
	ANGLE_RIGHT     = 2,
	ANGLE_DOWNRIGHT = 3,
	ANGLE_DOWN      = 4,
	ANGLE_DOWNLEFT  = 5,
	ANGLE_LEFT      = 6,
	ANGLE_UPLEFT    = 7,

	ANGLE__COUNT    = 8,
};
static_assert(sizeof(Angle) == 0x4, "");


// It's likely a lot of these modes where made to run unit tests/etc.
// many could have been removed in the release build.
enum ProgrammerMode : unsigned int
{
	PROGRAMMER_OFF     = 0,
	PROGRAMMER_MODE_1  = 1,
	PROGRAMMER_MODE_2  = 2, // condition for >1 and -testercall
	PROGRAMMER_MODE_3  = 3, // front end and intros are disabled (>=3)
	PROGRAMMER_MODE_4  = 4, // one check if (> 3)
	PROGRAMMER_MODE_10 = 10, // test level AVI's?
	PROGRAMMER_MODE_11 = 11, // (crashes after title loading bar)
	// more values exist, at least up to and including 10?
};
static_assert(sizeof(ProgrammerMode) == 0x4, "");

// <https://kb.rockraidersunited.com/Command-line_parameters>
// All usages/assignments of CmdlineFlags are now known.
enum CmdlineFlags : unsigned int
{
	CMD_NONE               = 0,

	CMD_D3DRMUPDATED       = 0x1,       // [volatile] related to Direct3DRM->Update (needs calling?)
	CMD_FULLSCREEN         = 0x2,       // set when booting the game into fullscreen
	CMD_TEXTUREVIDEOMEMORY = 0x4,       // [writeonly] (set, but never checked for) DEVICEMODE_TEXTUREVIDEOMEMORY
	CMD_MIPMAP             = 0x8,       // set in GameInit if both Filter and MipMap config options are TRUE

	CMD_NOFPSLOCK          = 0x10,      // [readonly] (assigns WinMain gameloop frame rate to 0.0)
	CMD_NM                 = 0x20,      // "-nm"  (no texture management?, disables texture management for Voodoo2-based cards, assigned if "-ftm" is NOT set and TextureUsage (x byteDepth) is <= to free video memory)
	CMD_BEST               = 0x40,      // "-best"
	CMD_FPSLOCK30          = 0x80,      // [readonly] (assigns WinMain gameloop frame rate to (25.0 / 30.0), equivalent of "-fpslock 30")

	CMD_WINDOW             = 0x100,     // "-window"
	CMD_STARTLEVEL         = 0x200,     // "-startlevel <level>" (requires: FrontEnd FALSE)
	CMD_CLEANSAVES         = 0x400,     // "-cleansaves"
	//CMD_UNK_800            = 0x800,

	//CMD_UNK_1000           = 0x1000,
	CMD_DEBUG              = 0x2000,    // "-debug"
	CMD_DUALMOUSE          = 0x4000,    // "-dualmouse"
	CMD_DEBUGCOMPLETE      = 0x8000,    // "-debugcomplete" (triggers: "-debug")

	CMD_TESTERCALL         = 0x10000,   // "-testercall" (triggers: "-programmer 2", but does not overwrite real "-programmer" argument)
	CMD_TESTLEVELS         = 0x20000,   // "-testlevels"
	CMD_FTM                = 0x40000,   // "-ftm"
	CMD_FVF                = 0x80000,   // "-fvf"

	CMD_REDUCESAMPLES      = 0x100000,  // "-reducesamples"
	CMD_SHOWVERSION        = 0x200000,  // "-showversion"
	CMD_REDUCEANIMATION    = 0x400000,  // "-reduceanimation"
	CMD_REDUCEPROMESHES    = 0x800000,  // "-reducepromeshes"

	CMD_REDUCEFLICS        = 0x1000000, // "-reduceflics"
	CMD_REDUCEIMAGES       = 0x2000000, // "-reduceimages"
	//CMD_UNK_4000000        = 0x4000000,
	//CMD_UNK_8000000        = 0x8000000,

	//CMD_UNK_10000000       = 0x10000000,
	//CMD_UNK_20000000       = 0x20000000,
	//CMD_UNK_40000000       = 0x40000000,
	//CMD_UNK_80000000       = 0x80000000,

	// These are parsed, but do not assign a flag
	// CMD_FLAGS              = ??, // -flags      (set as global g_DEBUG_FLAGS)
	// CMD_FPSLOCK            = ??, // -fpslock    (set as global g_FPSLOCK_VSYNC)
	// CMD_PROGRAMMER         = ??, // -programmer (set as global g_PROGRAMMER_MODE)
	// CMD_NOSOUND            = ??, // -nosound    (set as exclusive bool out-value)
	// CMD_INSISTONCD         = ??, // -insistOnCD (set as exclusive bool out-value)
};
DEFINE_ENUM_FLAG_OPERATORS(CmdlineFlags)
static_assert(sizeof(CmdlineFlags) == 0x4, "");


enum FeatureFlags : unsigned int
{
	FEATURE_NONE        = 0,

	FEATURE_BLOCKFADEIN = 0x8000, // when specified, all blocks transition (fade) into their new state,
								  // Walls selected for drilling will fade to color, Power paths will fade into power.
								  // Rubble fades in when paths are destroyed, etc... Really neat!
};
DEFINE_ENUM_FLAG_OPERATORS(FeatureFlags)
static_assert(sizeof(FeatureFlags) == 0x4, "");

#pragma endregion


#pragma region Framework: Input Enums

// Keys use the same numbering as used by DirectInput's "DIK_*" enums.
enum Keys : unsigned char
{
    KEY_NONE            = 0,   // Not a real KEY enum name

    KEY_ESCAPE          = 1,   // ESC
    KEY_ONE             = 2,   // '1'
    KEY_TWO             = 3,   // '2'
    KEY_THREE           = 4,   // '3'
    KEY_FOUR            = 5,   // '4'
    KEY_FIVE            = 6,   // '5'
    KEY_SIX             = 7,   // '6'
    KEY_SEVEN           = 8,   // '7'
    KEY_EIGHT           = 9,   // '8'
    KEY_NINE            = 10,  // '9'
    KEY_ZERO            = 11,  // '0'
    KEY_MINUS           = 12,  // '-'
    KEY_EQUALS          = 13,  // '='
    KEY_BACKSPACE       = 14,  // BACK
    KEY_TAB             = 15,  // '\t'
    KEY_Q               = 16,  // 'Q'
    KEY_W               = 17,  // 'W'
    KEY_E               = 18,  // 'E'
    KEY_R               = 19,  // 'R'
    KEY_T               = 20,  // 'T'
    KEY_Y               = 21,  // 'Y'
    KEY_U               = 22,  // 'U'
    KEY_I               = 23,  // 'I'
    KEY_O               = 24,  // 'O'
    KEY_P               = 25,  // 'P'
    KEY_LEFTBRACE       = 26,  // '{'
    KEY_RIGHTBRACE      = 27,  // '}'
    KEY_RETURN          = 28,  // Enter
    KEY_LEFTCTRL        = 29,  // LCtrl
    KEY_A               = 30,  // 'A'
    KEY_S               = 31,  // 'S'
    KEY_D               = 32,  // 'D'
    KEY_F               = 33,  // 'F'
    KEY_G               = 34,  // 'G'
    KEY_H               = 35,  // 'H'
    KEY_J               = 36,  // 'J'
    KEY_K               = 37,  // 'K'
    KEY_L               = 38,  // 'L'
    KEY_SEMICOLON       = 39,  // ';'
    KEY_AT              = 40,  // '"' [English U.S.], '@' [English U.K. ...I think]
    KEY_RSINGLEQUOTE    = 41,  // '~' [English U.S.], ??? [English U.K. ...could be '`' or '\'']
    KEY_LEFTSHIFT       = 42,  // LShift key
    KEY_HASH            = 43,  // '|' [English U.S.], '#' [English U.K. ...I think]
    KEY_Z               = 44,  // 'Z'
    KEY_X               = 45,  // 'X'
    KEY_C               = 46,  // 'C'
    KEY_V               = 47,  // 'V'
    KEY_B               = 48,  // 'B'
    KEY_N               = 49,  // 'N'
    KEY_M               = 50,  // 'M'
    KEY_LEFTARROW       = 51,  // '<'
    KEY_RIGHTARROW      = 52,  // '>'
    KEY_QUESTIONMARK    = 53,  // '?'
    KEY_RIGHTSHIFT      = 54,  // RShift
    KEYPAD_ASTERISK     = 55,  // Numpad '*' (Multiply)
    KEY_ALT             = 56,  // LAlt (LMenu)
    KEY_SPACE           = 57,  // ' ' Space bar
    KEY_CAPLOCK         = 58,  // CAPS lock
    KEY_F1              = 59,  // F1
    KEY_F2              = 60,  // F2
    KEY_F3              = 61,  // F3
    KEY_F4              = 62,  // F4
    KEY_F5              = 63,  // F5
    KEY_F6              = 64,  // F6
    KEY_F7              = 65,  // F7
    KEY_F8              = 66,  // F8
    KEY_F9              = 67,  // F9
    KEY_F10             = 68,  // F10
    KEYPAD_NUMLOCK      = 69,  // NUM lock key
    KEY_SCROLLLOCK      = 70,  // SCR lock key
    KEYPAD_7            = 71,  // Numpad '7'
    KEYPAD_8            = 72,  // Numpad '8'
    KEYPAD_9            = 73,  // Numpad '9'
    KEYPAD_MINUS        = 74,  // Numpad '-' (Subtract)
    KEYPAD_4            = 75,  // Numpad '4'
    KEYPAD_5            = 76,  // Numpad '5'
    KEYPAD_6            = 77,  // Numpad '6'
    KEYPAD_PLUS         = 78,  // Numpad '+' (Add)
    KEYPAD_1            = 79,  // Numpad '1'
    KEYPAD_2            = 80,  // Numpad '2'
    KEYPAD_3            = 81,  // Numpad '3'
    KEYPAD_0            = 82,  // Numpad '0'
    KEYPAD_DELETE       = 83,  // Numpad '.' (Decimal, DEL)
    KEY_BACKSLASH       = 86,  // OEM_102: <> or \| on RT 102-key keyboard (Non-U.S.)
    KEY_F11             = 87,  // F11
    KEY_F12             = 88,  // F12
    KEYPAD_ENTER        = 156, // Numpad Enter (Return)
    KEY_RIGHTCTRL       = 157, // RCtrl
    KEYPAD_FORWARDSLASH = 181, // Numpad '/' (Divide)
    KEY_PRINTSCREEN     = 183, // PRNT SCR
    KEY_ALTGR           = 184, // RAlt (RMenu): Non-English modifier key for foreign characters 
    KEY_HOME            = 199, // Home
    KEY_CURSORUP        = 200, // Up arrow key
    KEY_PGUP            = 201, // Page up (Prior)
    KEY_CURSORLEFT      = 203, // Left arrow key
    KEY_CURSORRIGHT     = 205, // Right arrow key
    KEY_END             = 207, // End
    KEY_CURSORDOWN      = 208, // Down arrow key
    KEY_PGDN            = 209, // Page down (Next)
    KEY_INSERT          = 210, // INS
    KEY_DELETE          = 211, // DEL
};
static_assert(sizeof(Keys) == 0x1, "");

#pragma endregion


#pragma region Framework: IO Enums

// Location of a lego File stream (WAD or REAL)
// Same as BOOL3
enum FileLocation : int
{
	FILELOC_WAD   = 0,
	FILELOC_STD   = 1,
	FILELOC_ERROR = 2,
};
static_assert(sizeof(FileLocation) == 0x4, "");

enum WADEntryFlags : unsigned int
{
	WADENTRY_NONE            = 0,

	WADENTRY_UNK_STORE       = 0x1,
	WADENTRY_RNC_COMPRESSION = 0x2,
};
DEFINE_ENUM_FLAG_OPERATORS(WADEntryFlags)
static_assert(sizeof(WADEntryFlags) == 0x4, "");

enum FileBufferFlags : unsigned int
{
	FILEBUFFER_NONE   = 0,

	FILEBUFFER_ISUSED = 0x1,
};
DEFINE_ENUM_FLAG_OPERATORS(FileBufferFlags)
static_assert(sizeof(FileBufferFlags) == 0x4, "");

enum RegistryType : unsigned int
{
	REGISTRY_STRING = 0,
	REGISTRY_NUMBER = 1,
};
static_assert(sizeof(RegistryType) == 0x4, "");

#pragma endregion


#pragma region Framework: ModeSelection Enums

enum DriverModeFlags : unsigned int
{
	DRIVERMODE_NONE      = 0,

	DRIVERMODE_ISUSED    = 0x1,

	DRIVERMODE_NOGUID_10 = 0x10,
	DRIVERMODE_NOGUID_20 = 0x20,
};
DEFINE_ENUM_FLAG_OPERATORS(DriverModeFlags)
static_assert(sizeof(DriverModeFlags) == 0x4, "");

enum DeviceModeFlags : unsigned int
{
	DEVICEMODE_NONE                = 0,

	DEVICEMODE_ISUSED              = 0x1,

	DEVICEMODE_BPP_8               = 0x10,
	DEVICEMODE_BPP_16              = 0x20,
	DEVICEMODE_BPP_24              = 0x40,
	DEVICEMODE_BPP_32              = 0x80,

	DEVICEMODE_COLORMODEL_RGB      = 0x1000,
	DEVICEMODE_HARDWARE            = 0x2000,
	DEVICEMODE_TEXTUREVIDEOMEMORY  = 0x4000,
	DEVICEMODE_TEXTURESYSTEMMEMORY = 0x8000,
};
DEFINE_ENUM_FLAG_OPERATORS(DeviceModeFlags)
static_assert(sizeof(DeviceModeFlags) == 0x4, "");

enum ScreenModeFlags : unsigned int
{
	SCREENMODE_NONE   = 0,

	SCREENMODE_ISUSED = 0x1,
};
DEFINE_ENUM_FLAG_OPERATORS(ScreenModeFlags)
static_assert(sizeof(ScreenModeFlags) == 0x4, "");

#pragma endregion


#pragma region Framework: Resource Enums

// Other name parts: "<ResourceName>:NOTEXTURE"
enum class ResourceType : int
{
	Invalid = -1,

	Null = 0, // "NULL"  (ext: "")
	Mesh = 1, // "MESH"  (ext: "x")
	Frame = 2, // "FRAME" (ext: "x")
	Anim = 3, // "ANIM"  (ext: "x")
	Act = 4, // "ACT"   (ext: "ae") (loads "ae"-extension CFG file : g_FILEEXT_AE)
	empty = 5, // NULL    (ext: "")   (explicit)
	unassigned = 6, // NULL    (ext: NULL) (implicit)
	Lws = 7, // "LWS"   (ext: NULL)
	Lwo = 8, // "LWO"   (ext: NULL)

	Count = 9,
};
static_assert(sizeof(ResourceType) == 0x4, "");

enum GraphicsQuality : int
{
	QUALITY_WIREFRAME = 0,
	QUALITY_UNLITFLAT = 1,
	QUALITY_FLAT      = 2,
	QUALITY_GOURAUD   = 3,
	
	// There is no exact number assigned to this. But in certain contexts,
	//  passing anything not in the above list to a function,
	//  will allow directly defining the D3DRM render mode.
	QUALITY_CUSTOM    = 4, 
};
static_assert(sizeof(GraphicsQuality) == 0x4, "");

enum ResourceDataFlags : unsigned int
{
	RESDATA_NONE   = 0,

	RESDATA_UNK_2  = 0x2,

	RESDATA_UNK_8  = 0x8,
	RESDATA_UNK_10 = 0x10,
	RESDATA_UNK_20 = 0x20,

	RESDATA_UNK_80 = 0x80,
};
DEFINE_ENUM_FLAG_OPERATORS(ResourceDataFlags)
static_assert(sizeof(ResourceDataFlags) == 0x4, "");

enum ResourceManagerFlags : unsigned int
{
	RESMANAGER_NONE          = 0,

	RESMANAGER_ISINIT        = 0x1,

	RESMANAGER_SOUNDCALLBACK = 0x40,
};
DEFINE_ENUM_FLAG_OPERATORS(ResourceManagerFlags)
static_assert(sizeof(ResourceManagerFlags) == 0x4, "");

enum PolyMode : int
{
	POLY_LOW    = 0,
	POLY_MEDIUM = 1,
	POLY_HIGH   = 2,
	POLY_FP     = 3,
};
static_assert(sizeof(PolyMode) == 0x4, "");

#pragma endregion


#pragma region Framework: NERPs Enums

enum NERPSFunctionArgs : int
{
	NERPS_ARGS_0          = 0, // int func(void);
	NERPS_ARGS_1          = 1, // int func(int);
	NERPS_ARGS_2          = 2, // int func(int, int);
	NERPS_ARGS_0_NORETURN = 3, // void func(void);
	NERPS_ARGS_1_NORETURN = 4, // void func(int);
	NERPS_ARGS_2_NORETURN = 5, // void func(int, int);
	NERPS_ARGS_3_NORETURN = 6, // void func(int, int, int);
	NERPS_END_OF_LIST     = 7, // End of NERPs functions list "**End Of List**"
};
static_assert(sizeof(NERPSFunctionArgs) == 0x4, "");

#pragma endregion


#pragma region Framework: Audio Enums

enum SampleFlags : unsigned int
{
	SAMPLE_NONE     = 0,

	SAMPLE_ISUSED   = 0x1,
	SAMPLE_VOLUME   = 0x2,
	SAMPLE_MULTIPLE = 0x4,
	SAMPLE_STREAMED = 0x8,
};
DEFINE_ENUM_FLAG_OPERATORS(SampleFlags)
static_assert(sizeof(SampleFlags) == 0x4, "");

enum AudioFlags : unsigned int
{
	AUDIO_NONE    = 0,

	AUDIO_SOUNDON = 0x1,
	AUDIO_UNK_2   = 0x2,

	AUDIO_UNK_8   = 0x8,
};
DEFINE_ENUM_FLAG_OPERATORS(AudioFlags)
static_assert(sizeof(AudioFlags) == 0x4, "");

#pragma endregion


#pragma region Framework: FrontEnd Enums

enum MenuItemType : int
{
	MENUITEM__INVALID   = -1,

	MENUITEM_CYCLE      = 0,
	MENUITEM_TRIGGER    = 1,
	MENUITEM_TEXTINPUT  = 2,
	MENUITEM_SLIDER     = 3,
	MENUITEM_REALSLIDER = 4,
	MENUITEM_NEXT       = 5,

	MENUITEM__COUNT     = 6,
};
static_assert(sizeof(MenuItemType) == 0x4, "");

#pragma endregion


#pragma region Game: Object Enums

enum class ObjectType : int
{
	TVCamera = -1, // not used in-game, may only be for loading in .ol files
	None = 0,
	Vehicle = 1, // [table]
	MiniFigure = 2, // [table]
	RockMonster = 3, // [table]
	Building = 4, // [table]
	Boulder = 5,
	PowerCrystal = 6,
	Ore = 7, // [normal, processed]
	Dynamite = 8,
	Barrier = 9,
	Upgrade = 10, // [table] upgrade part attached to live vehicles, these are defined in a Vehicle's .ae file
	ElectricFence = 11,
	SpiderWeb = 12,
	SonicBlaster = 13, // sonic blaster when carried and used like Dynamite (which may only be possible with debug keys)
	ElectricFenceStud = 14, // yellow beacon between electric fence connections, only present when distance is 2 blocks
	Path = 15, // (never seen as a live object)
	PusherShot = 16,
	FreezerShot = 17,
	IceCube = 18, // ice block created by frozen creatures
	LaserShot = 19, // this does not include "instant" lasers, like from vehicles, and the mining laser

	Count = 20,
};
static_assert(sizeof(ObjectType) == 0x4, "");


enum class ToolType : int
{
	Invalid = -1,
	Drill = 0,
	Shovel = 1, // "Spade"
	Hammer = 2,
	Spanner = 3,
	LaserBeam = 4,
	PusherBeam = 5,
	SonicBlaster = 6,
	FreezerBeam = 7,

	Count = 8,
};
static_assert(sizeof(ToolType) == 0x4, "");

enum OreType : int
{
	ORE_NORMAL    = 0,
	ORE_PROCESSED = 1,
};
static_assert(sizeof(OreType) == 0x4, "");

#pragma endregion


#pragma region Game: LevelBlockFlags

enum LevelBlockFlags1 : unsigned int
{
	BLOCK1_NONE          = 0,

	BLOCK1_RUBBLE_LOW    = 0x0,
	BLOCK1_RUBBLE_MEDIUM = 0x1,
	BLOCK1_RUBBLE_HIGH   = 0x2,
	BLOCK1_RUBBLE_FULL   = 0x3,

	BLOCK1_UNK_8         = 0x8,
	BLOCK1_UNK_10        = 0x10,
	BLOCK1_REINFORCED    = 0x20,
	BLOCK1_UNK_40        = 0x40,
	BLOCK1_UNK_80        = 0x80,

	BLOCK1_UNK_200       = 0x200,
	BLOCK1_UNK_400       = 0x400,
	BLOCK1_UNK_800       = 0x800,
	BLOCK1_UNK_1000      = 0x1000,

	BLOCK1_UNK_4000      = 0x4000,
	BLOCK1_UNK_8000      = 0x8000,

	BLOCK1_HIDDEN        = 0x20000,

	BLOCK1_UNK_80000     = 0x80000,
	BLOCK1_UNK_100000    = 0x100000,
	BLOCK1_UNK_200000    = 0x200000,
	BLOCK1_UNK_400000    = 0x400000,

	BLOCK1_EXPOSED       = 0x4000000,
	BLOCK1_UNK_8000000   = 0x8000000,

	BLOCK1_POWERPATH     = 0x20000000,
	BLOCK1_UNK_40000000  = 0x40000000,
	BLOCK1_UNK_80000000  = 0x80000000,
};
DEFINE_ENUM_FLAG_OPERATORS(LevelBlockFlags1)
static_assert(sizeof(LevelBlockFlags1) == 0x4, "");

enum LevelBlockFlags2 : unsigned int
{
	BLOCK2_NONE = 0,

	BLOCK2_SLUGHOLE_EXPOSED = 0x20,
	BLOCK2_EMERGE_POINT     = 0x40,
	BLOCK2_EMERGE_TRIGGER   = 0x80,

	BLOCK2_SLUGHOLE_HIDDEN  = 0x200,
};
DEFINE_ENUM_FLAG_OPERATORS(LevelBlockFlags2)
static_assert(sizeof(LevelBlockFlags2) == 0x4, "");

#pragma endregion


#pragma region Game: LiveFlags

enum LiveFlags1 : unsigned int
{
	LIVEOBJ1_NONE          = 0,

	LIVEOBJ1_MOVING        = 0x1,
	LIVEOBJ1_UNK_2_LEFTING = 0x2,
	LIVEOBJ1_TURNING       = 0x4,

	LIVEOBJ1_REINFORCING   = 0x40,

	LIVEOBJ1_TURNRIGHT     = 0x80,

	LIVEOBJ1_CARRYING      = 0x400,

	LIVEOBJ1_CLEARING      = 0x40000,
	LIVEOBJ1_PLACING       = 0x80000,

	LIVEOBJ1_REST          = 0x20000000,
	LIVEOBJ1_EATING        = 0x40000000,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags1)
static_assert(sizeof(LiveFlags1) == 0x4, "");

enum LiveFlags2 : unsigned int
{
	LIVEOBJ2_NONE        = 0,

	LIVEOBJ2_DRIVING     = 0x8,

	LIVEOBJ2_TRAINING    = 0x400,
	LIVEOBJ2_UNK_800     = 0x800,

	LIVEOBJ2_UPGRADING   = 0x8000,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags2)
static_assert(sizeof(LiveFlags2) == 0x4, "");

enum LiveFlags3 : unsigned int
{
	LIVEOBJ3_NONE         = 0,

	LIVEOBJ3_SIMPLEOBJECT = 0x20000,

	LIVEOBJ3_UNK_80000    = 0x80000,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags3)
static_assert(sizeof(LiveFlags3) == 0x4, "");

enum LiveFlags4 : unsigned int
{
	LIVEOBJ4_NONE = 0,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags4)
static_assert(sizeof(LiveFlags4) == 0x4, "");

enum LiveFlags5 : unsigned int
{
	LIVEOBJ5_NONE = 0,
};
DEFINE_ENUM_FLAG_OPERATORS(LiveFlags5)
static_assert(sizeof(LiveFlags5) == 0x4, "");

#pragma endregion


#pragma region Game: AI Enums

enum ActivityType : int
{
	ACTIVITY__INVALID            = -1,

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
	ACTIVITY_DESPOSITE           = 29,
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

	ACTIVITY__COUNT              = 79,
};
static_assert(sizeof(ActivityType) == 0x4, "");

enum AITaskType : int
{
	AITASK__INVALID          = -1,

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
	AITASK_SONICBLASTER      = 20,
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

	AITASK__COUNT            = 31,
};
static_assert(sizeof(AITaskType) == 0x4, "");

enum AIPriorityType : int
{
	AIPRIORITY__INVALID          = -1,

	AIPRIORITY_CRYSTAL           = 0,
	AIPRIORITY_ORE               = 1,
	AIPRIORITY_DEFAULTCOLLECT    = 2,
	AIPRIORITY_DESTRUCTION       = 3,
	AIPRIORITY_CONSTRUCTION      = 4,
	AIPRIORITY_REQUEST           = 5,
	AIPRIORITY_REINFORCE         = 6,
	AIPRIORITY_REPAIR            = 7,
	AIPRIORITY_CLEARING          = 8,
	AIPRIORITY_STORAGE           = 9,
	AIPRIORITY_REFINING          = 10,
	AIPRIORITY_HEALTHLOW         = 11,
	AIPRIORITY_GETIN             = 12,
	AIPRIORITY_UPGRADE           = 13,
	AIPRIORITY_BUILDPATH         = 14,
	AIPRIORITY_ATTACKROCKMONSTER = 15,
	AIPRIORITY_BARRIER           = 16,
	AIPRIORITY_FINDLOAD          = 17,
	AIPRIORITY_RECHARGE          = 18,
	AIPRIORITY_UPGRADEBUILDING   = 19,
	AIPRIORITY_GATHER            = 20,
	AIPRIORITY_STEAL             = 21,
	AIPRIORITY_PUNCH             = 22,
	AIPRIORITY_DEPART            = 23,
	AIPRIORITY_ATTACKPATH        = 24,
	AIPRIORITY_ATTACKOBJECT      = 25,
	AIPRIORITY_CONGREGATE        = 26,

	AIPRIORITY__COUNT            = 27,
};
static_assert(sizeof(AIPriorityType) == 0x4, "");

#pragma endregion


#pragma region Game: ObjectStatsFlags

enum ObjectStatsFlags1 : unsigned int
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
DEFINE_ENUM_FLAG_OPERATORS(ObjectStatsFlags1)
static_assert(sizeof(ObjectStatsFlags1) == 0x4, "");

enum ObjectStatsFlags2 : unsigned int
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
	STATS2_GENERATEPOWER          = 0x200, // Not used directly, half of "PowerBuilding" property
	STATS2_SELFPOWERED            = 0x400,
	STATS2_POWERBUILDING          = 0x200 | 0x400, // STATS2_GENERATEPOWER | STATS2_SELFPOWERED
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
DEFINE_ENUM_FLAG_OPERATORS(ObjectStatsFlags2)
static_assert(sizeof(ObjectStatsFlags2) == 0x4, "");

enum ObjectStatsFlags3 : unsigned int
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
DEFINE_ENUM_FLAG_OPERATORS(ObjectStatsFlags3)
static_assert(sizeof(ObjectStatsFlags3) == 0x4, "");

#pragma endregion


#pragma region Game: GameFlags

enum GameFlags1 : unsigned int
{
	GAME1_NONE                  = 0,
	
	//GAME1_UNK_1                 = 0x1,
	GAME1_RADARON               = 0x2,
	GAME1_UNK_4                 = 0x4,
	GAME1_MUSICON               = 0x8,

	GAME1_SOUNDON               = 0x10,
	GAME1_WALLPROMESHES         = 0x20,
	GAME1_FRAMERATEMONITOR      = 0x40,
	GAME1_MEMORYMONITOR         = 0x80,

	GAME1_UNK_100               = 0x100,
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
DEFINE_ENUM_FLAG_OPERATORS(GameFlags1)
static_assert(sizeof(GameFlags1) == 0x4, "");

enum GameFlags2 : unsigned int
{
	GAME2_NONE                 = 0,

	GAME2_CALLTOARMS           = 0x1,
	//GAME2_UNK_2                = 0x2,
	GAME2_UNK_4                = 0x4,
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
	//GAME2_UNK_10000            = 0x10000,
	GAME2_ALLOWRENAME          = 0x20000,
	GAME2_RECALLOLOBJECTS      = 0x40000,
	GAME2_GENERATESPIDERS      = 0x80000,
	GAME2_DISABLETOOLTIPSOUND  = 0x100000,
	GAME2_NOAUTOEAT            = 0x200000,
};
DEFINE_ENUM_FLAG_OPERATORS(GameFlags2)
static_assert(sizeof(GameFlags2) == 0x4, "");

enum GameFlags3 : unsigned int
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
DEFINE_ENUM_FLAG_OPERATORS(GameFlags3)
static_assert(sizeof(GameFlags3) == 0x4, "");

#pragma endregion


enum TextureType : int
{
	TEXTURES__INVALID = -1,

	TEXTURES_ROCK = 0,
	TEXTURES_LAVA = 1,
	TEXTURES_ICE  = 2,
};
static_assert(sizeof(TextureType) == 0x4, "");

enum AbilityType : int
{
	ABILITY__INVALID = -1,

	ABILITY_PILOT    = 0,
	ABILITY_SAILOR   = 1,
	ABILITY_DRIVER   = 2,
	ABILITY_DYNAMITE = 3,
	ABILITY_REPAIR   = 4,
	ABILITY_SCANNER  = 5,

	ABILITY__COUNT   = 6,
};
static_assert(sizeof(AbilityType) == 0x4, "");

enum TrainedFlags : unsigned int
{
	TRAINED_NONE     = 0,

	TRAINED_PILOT    = 0x1,
	TRAINED_SAILOR   = 0x2,
	TRAINED_DRIVER   = 0x4,
	TRAINED_DYNAMITE = 0x8,
	TRAINED_REPAIR   = 0x10,
	TRAINED_SCANNER  = 0x20,
};
DEFINE_ENUM_FLAG_OPERATORS(TrainedFlags)
static_assert(sizeof(TrainedFlags) == 0x4, "");


#pragma region Game: Objective Enums

enum LevelCompleteStatus : int
{
	LEVELSTATUS_NONE            = 0,
	LEVELSTATUS_COMPLETE        = 1,
	LEVELSTATUS_FAILED          = 2,
	LEVELSTATUS_FAILED_CRYSTALS = 3,
	LEVELSTATUS_FAILED_OTHER    = 4,
};
static_assert(sizeof(LevelCompleteStatus) == 0x4, "");

enum ObjectiveFlags : unsigned int
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
DEFINE_ENUM_FLAG_OPERATORS(ObjectiveFlags)
static_assert(sizeof(ObjectiveFlags) == 0x4, "");

#pragma endregion


enum ObjInfoFlags : unsigned int
{
	OBJINFO_BUBBLEIMAGES = 16,
	OBJINFO_HEALTHBAR = 2,
	OBJINFO_HEALTHBAR_VERTICAL = 8,
	OBJINFO_HUNGERIMAGES = 1,
	OBJINFO_NONE = 0
};
DEFINE_ENUM_FLAG_OPERATORS(ObjInfoFlags)
static_assert(sizeof(ObjInfoFlags) == 0x4, "");


#pragma region Game: Advisor Enums

enum AdvisorType : int
{
	ADVISOR__INVALID                         = -1,

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
};
static_assert(sizeof(AdvisorType) == 0x4, "");

enum AdvisorAnim : int
{
	ADVISORANIM__INVALID   = -1,

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
};
static_assert(sizeof(AdvisorAnim) == 0x4, "");

#pragma endregion


#pragma region Game: Map Enums

// Block Pointers map [tuto.map]
typedef unsigned char BlockPointerValue;

// CryOre map [cror.map]
enum CryOreType : unsigned char
{
	CRYORE_NONE           = 0x00,

	CRYORE_LV0_CRYSTAL_1  = 0x01,
	CRYORE_LV0_ORE_1      = 0x02,
	CRYORE_LV1_CRYSTAL_1  = 0x03,
	CRYORE_LV1_ORE_1      = 0x04,

	CRYORE_LV0_CRYSTAL_3  = 0x05,
	CRYORE_LV0_ORE_3      = 0x06,
	CRYORE_LV1_CRYSTAL_3  = 0x07,
	CRYORE_LV1_ORE_3      = 0x08,

	CRYORE_LV0_CRYSTAL_5  = 0x09,
	CRYORE_LV0_ORE_5      = 0x0a,
	CRYORE_LV1_CRYSTAL_5  = 0x0b,
	CRYORE_LV1_ORE_5      = 0x0c,

	CRYORE_LV0_CRYSTAL_10 = 0x0d,
	CRYORE_LV0_ORE_10     = 0x0e,
	CRYORE_LV1_CRYSTAL_10 = 0x0f,
	CRYORE_LV1_ORE_10     = 0x10,

	CRYORE_LV0_CRYSTAL_25 = 0x11,
	CRYORE_LV0_ORE_25     = 0x12,
	CRYORE_LV1_CRYSTAL_25 = 0x13,
	CRYORE_LV1_ORE_25     = 0x14,
};
static_assert(sizeof(CryOreType) == 0x1, "");

// Emerge map [emrg.map]
enum EmergeType : unsigned char
{
	EMERGE_NONE     = 0x00,

	EMERGE_TRIGGER  = 0x01,
	EMERGE_POINT    = 0x02,
	EMERGE_UNUSED_3 = 0x03,
	EMERGE_UNUSED_4 = 0x04,
	EMERGE_UNUSED_5 = 0x05,
	EMERGE_UNUSED_6 = 0x06,

	EMERGE_INCREMENT = 0x6,
};
static_assert(sizeof(EmergeType) == 0x1, "");

// Erode map [erod.map]
enum ErodeType : unsigned char
{
	ERODE_NONE            = 0x00,

	ERODE_VERYSLOW_LAVA   = 0x01,
	ERODE_VERYSLOW_ALWAYS = 0x02,
	ERODE_SLOW_LAVA       = 0x03,
	ERODE_SLOW_ALWAYS     = 0x04,
	ERODE_MEDIUM_LAVA     = 0x05,
	ERODE_MEDIUM_ALWAYS   = 0x06,
	ERODE_FAST_LAVA       = 0x07,
	ERODE_FAST_ALWAYS     = 0x08,
	ERODE_VERYFAST_LAVA   = 0x09,
	ERODE_VERYFAST_ALWAYS = 0x0a,
};
static_assert(sizeof(ErodeType) == 0x1, "");

// Fallin map [fall.map]
enum FallinType : unsigned char
{
	FALLIN_NONE            = 0x00,

	FALLIN_LOW             = 0x01,
	FALLIN_MEDIUM          = 0x02,
	FALLIN_HIGH            = 0x03,
	FALLIN_VERYHIGH        = 0x04,
	FALLIN_CAVEIN_LOW      = 0x05,
	FALLIN_CAVEIN_MEDIUM   = 0x06,
	FALLIN_CAVEIN_HIGH     = 0x07,
	FALLIN_CAVEIN_VERYHIGH = 0x08,
};
static_assert(sizeof(FallinType) == 0x1, "");

// Path map [path.map]
enum PathType : unsigned char
{
	PATH_NONE      = 0x00,
	PATH_RUBBLE    = 0x01,
	PATH_POWERPATH = 0x02,
};
static_assert(sizeof(PathType) == 0x1, "");

// Predug map [dugg.map]
enum PredugType : unsigned char
{
	PREDUG_WALL             = 0x00, // Undug wall (in exposed or hidden cavern)
	PREDUG_EXPOSED          = 0x01, // Exposed tile
	PREDUG_HIDDEN           = 0x02, // Undiscovered cavern tile
	PREDUG_EXPOSED_SLUGHOLE = 0x03, // Exposed Slimy Slug Hole
	PREDUG_HIDDEN_SLUGHOLE  = 0x04, // Undiscovered cavern Slimy Slug Hole
};
static_assert(sizeof(PredugType) == 0x1, "");

// Surface map [high.map]
typedef unsigned short SurfaceValue;

// Terrain map [surf.map]
enum TerrainType : unsigned char
{
	TERRAIN_TUNNEL       = 0x00, // Tunnel (ceiling)
	TERRAIN_IMMOVABLE    = 0x01, // Immovable "Solid" wall
	TERRAIN_HARD         = 0x02, // Hard wall
	TERRAIN_MEDIUM       = 0x03, // Medium "Loose" wall
	TERRAIN_LOOSE        = 0x04, // Loose "Dirt" wall
	TERRAIN_SOIL         = 0x05, // [unused] Soil wall
	TERRAIN_LAVA         = 0x06, // Lava lake
	TERRAIN_WATER_unused = 0x07, // [unused] "flood water"
	TERRAIN_ORESEAM      = 0x08, // Ore Seam wall
	TERRAIN_LAKE         = 0x09, // Lake "Water"
	TERRAIN_CRYSTALSEAM  = 0x0a, // "Energy" Crystal Seam wall
	TERRAIN_RECHARGESEAM = 0x0b, // Recharge Seam wall
	TERRAIN_RUBBLE       = 0x0c, // Rubble pile (at any level)
	TERRAIN_REINFORCED   = 0x0d, // Reinforced wall type
	TERRAIN_PATH         = 0x0e, // Power Path (TODO: does this include Building Power Path plates?)
	TERRAIN_SLUGHOLE     = 0x0f, // Slimy Slug Hole
	TERRAIN_UNDISCOVERED = 0x10, // Undiscovered Cavern
	TERRAIN_CAVERN       = 0x11, // Exposed Cavern "Cavern floor"
};
static_assert(sizeof(TerrainType) == 0x1, "");

// AI map [???.map]

// [World\WorldTextures\BIOMESplit\BIOME*.bmp]
enum SurfaceTexture : unsigned char
{
	TEXTURE_GROUND              = 0x00, // Ground (floor)
	TEXTURE_WALL_F_SOIL         = 0x01, // Soil wall (forward)
	TEXTURE_WALL_F_LOOSE        = 0x02, // Loose "Dirt" wall (forward)
	TEXTURE_WALL_F_MEDIUM       = 0x03, // Medium "Loose" wall (forward)
	TEXTURE_WALL_F_HARD         = 0x04, // Hard wall (forward)
	TEXTURE_WALL_F_IMMOVABLE    = 0x05, // Immovable "Solid" wall (forward)
	TEXTURE_ERODE_LOW           = 0x06, // Erode level 1/4 (min)
	TEXTURE_07                  = 0x07, // [unused, Ice Biome] Hand-drawn lightning bolt over ground texture

	TEXTURE_RUBBLE_FULL         = 0x10, // Rubble level 4/4 (max)
	TEXTURE_RUBBLE_HIGH         = 0x11, // Rubble level 3/4
	TEXTURE_RUBBLE_MEDIUM       = 0x12, // Rubble level 2/4
	TEXTURE_RUBBLE_LOW          = 0x13, // Rubble level 1/4 (min)

	TEXTURE_ERODE_MEDIUM        = 0x16, // Erode level 2/4

	TEXTURE_WALL_F_CRYSTALSEAM  = 0x20, // "Energy" Crystal Seam wall (forward)
	TEXTURE_WALL_R_SOIL         = 0x21, // Soil wall (forward) [reinforced)
	TEXTURE_WALL_R_LOOSE        = 0x22, // Loose "Dirt" wall (forward) [reinforced)
	TEXTURE_WALL_R_MEDIUM       = 0x23, // Medium "Loose" wall (forward) [reinforced)
	TEXTURE_WALL_R_HARD         = 0x24, // Hard wall (forward) [reinforced)
	TEXTURE_WALL_R_IMMOVABLE    = 0x25, // Immovable "Solid" wall (forward) [reinforced)
	TEXTURE_ERODE_HIGH          = 0x26, // Erode level 3/4

	TEXTURE_SLUGHOLE            = 0x30, // Slimy slug hole
	TEXTURE_WALL_C_SOIL         = 0x31, // Soil wall (acute-corner)
	TEXTURE_WALL_C_LOOSE        = 0x32, // Loose "Dirt" wall (acute-corner)
	TEXTURE_WALL_C_MEDIUM       = 0x33, // Medium "Loose" wall (acute-corner)
	TEXTURE_WALL_C_HARD         = 0x34, // Hard wall (acute-corner)
	TEXTURE_WALL_C_IMMOVABLE    = 0x35, // Immovable "Solid" wall (acute-corner)
	TEXTURE_ERODE_FULL          = 0x36, // Erode level 4/4 (max)

	TEXTURE_WALL_F_ORESEAM      = 0x40, // Ore Seam wall (forward)

	TEXTURE_WATER               = 0x45, // Water lake
	TEXTURE_LAVA                = 0x46, // Lava lake
	TEXTURE_LAVA_NOTHOT         = 0x47, // [unused] Lava with text "NO HOT" drawn on it

	TEXTURE_WALL_O_SOIL         = 0x51, // Soil wall (obtuse-corner)
	TEXTURE_WALL_O_LOOSE        = 0x52, // Loose "Dirt" wall (obtuse-corner)
	TEXTURE_WALL_O_MEDIUM       = 0x53, // Medium "Loose" wall (obtuse-corner)
	TEXTURE_WALL_O_HARD         = 0x54, // Hard wall (obtuse-corner)
	TEXTURE_WALL_O_IMMOVABLE    = 0x55, // Immovable "Solid" wall (obtuse-corner)

	TEXTURE_PATH_4              = 0x60, // 4-sides Power Path
	TEXTURE_PATH_BUILD          = 0x61, // Power Path stud waiting to be built
	TEXTURE_PATH_2              = 0x62, // 2-sided Power Path (straight)
	TEXTURE_PATH_C              = 0x63, // 2-sided Power Path (corner)
	TEXTURE_PATH_3              = 0x64, // 3-sided Power Path
	TEXTURE_PATH_1              = 0x65, // 1-sided Power Path
	TEXTURE_PLATE_POWERED       = 0x66, // Square building Power Path plate [powered]
	TEXTURE_WALL_F_RECHARGESEAM = 0x67, // Recharge Seam wall (forward)

	TEXTURE_TUNNEL              = 0x70, // Tunnel as seen in top-down view (ceiling)
	TEXTURE_PATH_4_POWERED      = 0x71, // 4-sided Power Path [powered]
	TEXTURE_PATH_2_POWERED      = 0x72, // 2-sided Power Path (vertical) [powered]
	TEXTURE_PATH_C_POWERED      = 0x73, // 2-sided Power Path (corner) [powered]
	TEXTURE_PATH_3_POWERED      = 0x74, // 3-sided Power Path [powered]
	TEXTURE_PATH_1_POWERED      = 0x75, // 1-sided Power Path [powered]
	TEXTURE_PLATE               = 0x76, // Square building Power Path plate
	TEXTURE_WALL_GAP            = 0x77, // Gap for diagonally-connected wall
};
static_assert(sizeof(SurfaceTexture) == 0x1, "");

#pragma endregion



enum BubbleType : int
{
	BUBBLE__INVALID          = -1,

	BUBBLE_CANTDO            = 0,
	BUBBLE_IDLE              = 1,
	BUBBLE_COLLECTCRYSTAL    = 2,
	BUBBLE_COLLECTORE        = 3,
	BUBBLE_COLLECTSTUD       = 4,
	BUBBLE_COLLECTDYNAMITE   = 5,
	BUBBLE_COLLECTBARRIER    = 6,
	BUBBLE_COLLECTELECFENCE  = 7,
	BUBBLE_COLLECTDRILL      = 8,
	BUBBLE_COLLECTSPADE      = 9,
	BUBBLE_COLLECTHAMMER     = 10,
	BUBBLE_COLLECTSPANNER    = 11,
	BUBBLE_COLLECTLASER      = 12,
	BUBBLE_COLLECTPUSHER     = 13,
	BUBBLE_COLLECTFREEZER    = 14,
	BUBBLE_COLLECTBIRDSCARER = 15,
	BUBBLE_CARRYCRYSTAL      = 16,
	BUBBLE_CARRYORE          = 17,
	BUBBLE_CARRYSTUD         = 18,
	BUBBLE_CARRYDYNAMITE     = 19,
	BUBBLE_CARRYBARRIER      = 20,
	BUBBLE_CARRYELECFENCE    = 21,
	BUBBLE_GOTO              = 22,
	BUBBLE_DYNAMITE          = 23,
	BUBBLE_REINFORCE         = 24,
	BUBBLE_DRILL             = 25,
	BUBBLE_REPAIR            = 26,
	BUBBLE_DIG               = 27,
	BUBBLE_FLEE              = 28,
	BUBBLE_POWEROFF          = 29,
	BUBBLE_CALLTOARMS        = 30,
	BUBBLE_ELECFENCE         = 31,
	BUBBLE_EAT               = 32,
	BUBBLE_DRIVE             = 33,
	BUBBLE_UPGRADE           = 34,
	BUBBLE_BUILDPATH         = 35,
	BUBBLE_TRAIN             = 36,
	BUBBLE_RECHARGE          = 37,
	BUBBLE_REQUEST           = 38,

	BUBBLE__COUNT            = 39,
};
static_assert(sizeof(BubbleType) == 0x4, "");

enum InfoType : int
{
	INFO__INVALID             = -1,

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

	INFO__COUNT               = 40,
};
static_assert(sizeof(InfoType) == 0x4, "");

enum MessageType : int
{
	MESSAGE__INVALID                       = -1,
	
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
};
static_assert(sizeof(MessageType) == 0x4, "");

enum TextType : int
{
	TEXT__INVALID            = -1,

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
};
static_assert(sizeof(TextType) == 0x4, "");

enum PanelType : int
{
	PANEL__INVALID       = -1,

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
};
static_assert(sizeof(PanelType) == 0x4, "");

enum RewardItemType : int
{
	REWARDTYPE__INVALID      = -1,

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
};
static_assert(sizeof(RewardItemType) == 0x4, "");


#pragma warning( pop )

#pragma endregion
} /* namespace lego */
