// Common.h : Declares common utility (and personal helper) functions used by LegoRR / CLGen.
//

#pragma once

#include "../framework.h"
#include "../resource.h"


namespace lego {

#pragma region Defines

// When checking this memory address with OllyDbg, the value was 00000000h, meaning this **may** be a reference to an empty string!
// Ghidra's identifier for this location has been changed to: ""/*EMPTYSTR*/
//   allowing to inline the string value, while also commenting its usage everywhere.
// Original name assigned by Ghidra: "lpWindowName_ 004b9a14"  (space kept to prevent from replace-all)
// 
// Displayed as: ""/*EMPTYSTR*/, Runtime value: {'\0','\0','\0','\0'}
// <LegoRR.exe @004b9a14>  XREF[292]:
#define c_EMPTYSTR  ""/*EMPTYSTR*/
//static char c_EMPTYSTR[4] = {'\0','\0','\0','\0'};

// Time unit (25 frames per second) as a double-precision floating point
#define TIME_UNIT   25.0
// Time unit (25 frames per second) as a single-precision floating point
#define TIME_UNITF  25.0f

// Size of block (in 3D-space units) as an integer
#define BLOCK_UNIT  40
// Size of block (in 3D-space units) as a single-precision floating point
#define BLOCK_UNITF 40.0f

#define s_RegistryKey "SOFTWARE\\LEGO Media\\Games\\Rock Raiders"

#pragma endregion


#pragma region Types

// Many boolean returns from LegoRR functions may have a 3rd return state for error, this enum is for that.
enum BOOL3 : BOOL
{
	BOOL3_FALSE = 0, // false
	BOOL3_TRUE  = 1, // true
	BOOL3_ERROR = 2, // error
};
	
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
DEFINE_ENUM_FLAG_OPERATORS(CmdlineFlags)


enum DebugFlags : unsigned int
{
	DEBUGFLAG_NONE        = 0,

	DEBUGFLAG_BLOCKFADEIN = 0x8000, // when specified, all blocks transition (fade) into their new state,
		                            // Walls selected for drilling will fade to color, Power paths will fade into power.
									// Rubble fades in when paths are destroyed, etc... Really neat!
};
DEFINE_ENUM_FLAG_OPERATORS(DebugFlags)


//struct RenderStateItem
//{
//	/*0,4*/ unsigned int value; // not guaranteed to be uint, sometimes signed int, sometimes BOOL, etc...
//	/*4,4*/ BOOL isUsed;
//	/*8*/
//};

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
struct Rect2I
{
	/*00,4*/ int x;
	/*04,4*/ int y;
	/*08,4*/ int width;
	/*0c,4*/ int height;
	/*10*/
};
struct Rect2F
{
	/*00,4*/ float x;
	/*04,4*/ float y;
	/*08,4*/ float width;
	/*0c,4*/ float height;
	/*10*/
};
struct ColourRGBI
{
	/*0,4*/ unsigned int red;
	/*4,4*/ unsigned int green;
	/*8,4*/ unsigned int blue;
	/*c*/
};
struct ColourRGBF
{
	/*0,4*/ float red;
	/*4,4*/ float green;
	/*8,4*/ float blue;
	/*c*/
};
// (used as short hand for D3DRMIMAGE mask channels)
struct ColourRGBAI
{
	/*00,4*/ unsigned int red;
	/*04,4*/ unsigned int green;
	/*08,4*/ unsigned int blue;
	/*0c,4*/ unsigned int alpha;
	/*10*/
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

#pragma region Globals

namespace globals {

	/*// <LegoRR.exe @0054155c>
	extern unsigned int COUNT_0054155c;
	// <LegoRR.exe @00541560>
	extern unsigned int COUNT_00541560;
	// <LegoRR.exe @00541564>
	extern DWORD g_Direct3D_TextureHandle_New;
	// <LegoRR.exe @00541568>
	extern DWORD g_Direct3D_LightState_New;
	// <LegoRR.exe @0054156c>
	extern IDirect3DTexture2* g_IDirect3DTexture2_New;
	// <LegoRR.exe @00541570>
	extern DWORD g_Direct3D_TextureHandle_Old;
	// <LegoRR.exe @00541574>
	extern DWORD g_Direct3D_LightState_Old;
	// <LegoRR.exe @00541578>
	extern IDirect3DTexture2* g_IDirect3DTexture2_Old;
	// <LegoRR.exe @0054157c>
	extern DWORD g_Direct3D_MaterialHandle;
	// <LegoRR.exe @00541580>
	extern IDirect3DMaterial3* g_IDirect3DMaterial3;
	// <LegoRR.exe @00541584>
	//ReservedPool<Struct_34> start

	// [INCLUSIVE]: WinMain functions, Input.c function, GetDeviceBitsPerPixel
	// <LegoRR.exe @00506800>
	extern HWND g_hWnd;
	// [INCLUSIVE]: WinMain, ChooseScreenMode, Input.c function
	// <LegoRR.exe @00506804>
	extern HINSTANCE g_hInstance;
	// [INCLUSIVE]: WinMain functions, Input.c function
	// <LegoRR.exe @00506808>
	extern BOOL g_IsFocused;
	// [EXCLUSIVE]: WinMain, GameWindowProc functions
	// <LegoRR.exe @0050680c>
	extern BOOL g_IsClosing;
	// [EXCLUSIVE]: WinMain, CreateMainWindow
	// <LegoRR.exe @00506810>
	extern const char* g_WindowClassName;
	// [EXCLUSIVE]: WinMain
	// <LegoRR.exe @00506814>
	extern char g_ExeName[256];

	// [UNKNOWN]:
	// <LegoRR.exe @00506914>
	extern IDirect3DRM3* g_IDirect3DRM3;
	// [UNKNOWN]:
	// <LegoRR.exe @00506918>
	extern IDirect3DRMDevice3* g_IDirect3DRMDevice3;
	// [UNKNOWN]:
	// <LegoRR.exe @0050691c>
	extern IDirect3DDevice3* g_IDirect3DDevice3;
	// D3DRMFOGMETHOD_VERTEX = 0x1,
	// D3DRMFOGMETHOD_TABLE  = 0x2,
	// D3DRMFOGMETHOD_ANY    = 0x4,
	// [EXCLUSIVE]: Direct3DRMCreate, SetRootSceneFodMode
	// <LegoRR.exe @00506920>  XREF[3]
	extern unsigned int g_SceneFogMethod;
	// [INCLUSIVE]:
	// <LegoRR.exe @00506924>  XREF[15,12=27]
	extern Size2I g_RESOLUTION;
	// [EXCLUSIVE]: WinMain, SetGameFunctions
	// <LegoRR.exe @0050692c>  XREF[3,7]
	extern GameFunctions g_GameFunctions;
	// [EXCLUSIVE]: WinMain, SetGameFunctions
	// <LegoRR.exe @00506938>  XREF[3]
	extern BOOL g_GameFunctions_ISINIT;
	// [INCLUSIVE]:
	// <LegoRR.exe @0050693c>  XREF[5]
	extern float g_FPSLOCK_VSYNC;
	// [EXCLUSIVE]: SetRenderState, Cleanup(Update?)RenderStates
	// <LegoRR.exe @00506940>  XREF[3,7]
	extern RenderStateItem g_RenderStates_TABLE[200];
	// <LegoRR.exe @00506f80>  XREF[3]
	// [EXCLUSIVE]: AdjustGameWindowedRect, ShowGameWindow
	extern DWORD g_WindowStyle;
	// [INCLUSIVE]:
	// <LegoRR.exe @00506f84>  XREF[82]
	extern CmdlineFlags g_CMDLINE_FLAGS;
	// [INCLUSIVE/ACCESSOR]: ParseCmdFlags, WinMain functions, game functions, GetProgrammerMode (accessor)
	// <LegoRR.exe @00506f88>  XREF[17]
	extern ProgrammerMode g_PROGRAMMER_MODE;
	// [EXCLUSIVE/ACCESSOR]: ParseCmdFlags, GetStartLevel (accessor)
	// <LegoRR.exe @00506f8c>  XREF[3,1]
	extern char g_STARTLEVEL[256];
	// [EXCLUSIVE/ACCESSOR]: ParseCmdFlags, GetDebugFlags (accessor)
	// <LegoRR.exe @0050708c>  XREF[2]
	extern DebugFlags g_DEBUG_FLAGS; // 0x8000 (block fade)
	*/

	// [INCLUSIVE]:
	// <LegoRR.exe @00506f84>  XREF[82]
	extern CmdlineFlags g_CMDLINE_FLAGS;
	// [INCLUSIVE/ACCESSOR]: ParseCmdFlags, WinMain functions, game functions, GetProgrammerMode (accessor)
	// <LegoRR.exe @00506f88>  XREF[17]
	extern ProgrammerMode g_PROGRAMMER_MODE;
	// [EXCLUSIVE/ACCESSOR]: ParseCmdFlags, GetStartLevel (accessor)
	// <LegoRR.exe @00506f8c>  XREF[3,1]
	extern char g_STARTLEVEL[256];
	// [EXCLUSIVE/ACCESSOR]: ParseCmdFlags, GetDebugFlags (accessor)
	// <LegoRR.exe @0050708c>  XREF[2]
	extern DebugFlags g_DEBUG_FLAGS; // 0x8000 (block fade)

	/*// <LegoRR.exe @0076bb3c>
	extern BOOL g_LeftButtonState;
	// <LegoRR.exe @0076bb40>
	extern BOOL g_RightButtonState;

	// <LegoRR.exe @0076bb4c>
	extern BOOL BOOL_0076bb4c;
	// <LegoRR.exe @0076bb50>
	extern BOOL BOOL_0076bb50;
	// <LegoRR.exe @0076bb54>
	extern BOOL BOOL_0076bb54;
	// <LegoRR.exe @0076bb58>
	extern BOOL g_RightButtonDoubleClicked;*/

	// <LegoRR.exe @005774f4>
	//static BOOL g_IsFullScreen;
} /* namespace globals */

#pragma endregion


#pragma region Custom Helper Functions

int __cdecl debugoutf(const char* format, ...);
#define printf lego::debugoutf
#define debugf lego::debugoutf

#pragma endregion


#pragma region Functions

// <LegoRR.exe @00401b30>
ProgrammerMode __cdecl GetProgrammerMode(void);

// <LegoRR.exe @00401b40>
const char* __cdecl GetStartLevel(void);

// <LegoRR.exe @00401b70>
int __cdecl GetResolutionWidth(void);

// <LegoRR.exe @00401b80>
int __cdecl GetResolutionHeight(void);

// <LegoRR.exe @00478230>
unsigned int __cdecl GetDebugFlags(void);

#pragma endregion

} /* namespace lego */
