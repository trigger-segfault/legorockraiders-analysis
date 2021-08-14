// Common.h : Declares common utility (and personal helper) functions used by LegoRR / CLGen.
//

#pragma once

// #include "../framework.h"
// #include "../resource.h"


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


#pragma region Enums
namespace lego {

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

} /* namespace lego */
#pragma endregion


#pragma pack(push, 1)

#pragma region Types
namespace lego {

#pragma region Colour Types

struct ColourRGBI
{
	/*0,4*/ unsigned int red;
	/*4,4*/ unsigned int green;
	/*8,4*/ unsigned int blue;
	/*c*/
};
static_assert(sizeof(ColourRGBI) == 0xc, "");

struct ColourRGBF
{
	/*0,4*/ float red;
	/*4,4*/ float green;
	/*8,4*/ float blue;
	/*c*/
};
static_assert(sizeof(ColourRGBF) == 0xc, "");

// (used as short hand for D3DRMIMAGE mask channels)
struct ColourRGBAI
{
	/*00,4*/ unsigned int red;
	/*04,4*/ unsigned int green;
	/*08,4*/ unsigned int blue;
	/*0c,4*/ unsigned int alpha;
	/*10*/
};
static_assert(sizeof(ColourRGBAI) == 0x10, "");

struct ColourRGBAF
{
	/*00,4*/ float red;
	/*04,4*/ float green;
	/*08,4*/ float blue;
	/*0c,4*/ float alpha;
	/*10*/
};
static_assert(sizeof(ColourRGBAF) == 0x10, "");

struct ColourRGBPacked
{
	union {
		struct {
			/*0,1*/ unsigned char red;
			/*1,1*/ unsigned char green;
			/*2,1*/ unsigned char blue;
			/*3,1*/ unsigned char reserved;
			/*4*/
		};
		/*0,4*/ unsigned int rgbColor;
		/*4*/
	};
};
static_assert(sizeof(ColourRGBPacked) == 0x4, "");

struct ColourRGBAPacked
{
	union {
		struct {
			/*0,1*/ unsigned char red;
			/*1,1*/ unsigned char green;
			/*2,1*/ unsigned char blue;
			/*3,1*/ unsigned char alpha;
			/*4*/
		};
		/*0,4*/ unsigned int rgbaColor;
		/*4*/
	};
};
static_assert(sizeof(ColourRGBAPacked) == 0x4, "");

#pragma endregion


#pragma region Geometry Types

//struct RenderStateItem
//{
//	/*0,4*/ unsigned int value; // not guaranteed to be uint, sometimes signed int, sometimes BOOL, etc...
//	/*4,4*/ BOOL isUsed;
//	/*8*/
//};

//POINT
struct Point2I
{
	/*0,4*/ int x;
	/*4,4*/ int y;
	/*8*/
};
static_assert(sizeof(Point2I) == 0x8, "");

struct Point2F
{
	/*0,4*/ float x;
	/*4,4*/ float y;
	/*8*/
};
static_assert(sizeof(Point2F) == 0x8, "");

//TD3DVector
struct Vector3F
{
	/*0,4*/ float x;
	/*4,4*/ float y;
	/*8,4*/ float z;
	/*c*/
};
static_assert(sizeof(Vector3F) == 0xc, "");

//TD3DRMVector4D
struct Vector4F
{
	/*00,4*/ float x;
	/*04,4*/ float y;
	/*08,4*/ float z;
	/*0c,4*/ float w;
	/*10*/
};
static_assert(sizeof(Vector4F) == 0x10, "");

struct Size2I
{
	/*0,4*/ int width;
	/*4,4*/ int height;
	/*8*/
};
static_assert(sizeof(Size2I) == 0x8, "");

struct Size2F
{
	/*0,4*/ float width;
	/*4,4*/ float height;
	/*8*/
};
static_assert(sizeof(Size2F) == 0x8, "");

struct Rect2I
{
	union {
		struct {
			/*00,4*/ int x;
			/*04,4*/ int y;
			/*08,4*/ int width;
			/*0c,4*/ int height;
			/*10*/
		};
		struct {
			/*00,8*/ Point2I point;
			/*08,8*/ Size2I  size;
			/*10*/
		};
	};
};
static_assert(sizeof(Rect2I) == 0x10, "");

struct Rect2F
{
	union {
		struct {
			/*00,4*/ float x;
			/*04,4*/ float y;
			/*08,4*/ float width;
			/*0c,4*/ float height;
			/*10*/
		};
		struct {
			/*00,8*/ Point2F point;
			/*08,8*/ Size2F  size;
			/*10*/
		};
	};
};
static_assert(sizeof(Rect2F) == 0x10, "");

struct P1P2Rect2I
{
	union {
		struct {
			/*00,4*/ int x1;
			/*04,4*/ int y1;
			/*08,4*/ int x2;
			/*0c,4*/ int y2;
			/*10*/
		};
		struct {
			/*00,8*/ Point2I p1;
			/*08,8*/ Point2I p2;
			/*10*/
		};
	};
};
static_assert(sizeof(P1P2Rect2I) == 0x10, "");

struct P1P2Rect2F
{
	union {
		struct {
			/*00,4*/ float x1;
			/*04,4*/ float y1;
			/*08,4*/ float x2;
			/*0c,4*/ float y2;
			/*10*/
		};
		struct {
			/*00,8*/ Point2F p1;
			/*08,8*/ Point2F p2;
			/*10*/
		};
	};
};
static_assert(sizeof(P1P2Rect2F) == 0x10, "");

//RECT
struct LTRBRect2I
{
	/*00,4*/ int left;
	/*04,4*/ int top;
	/*08,4*/ int right;
	/*0c,4*/ int bottom;
	/*10*/
};
static_assert(sizeof(LTRBRect2I) == 0x10, "");

struct LTRBRect2F
{
	/*00,4*/ float left;
	/*04,4*/ float top;
	/*08,4*/ float right;
	/*0c,4*/ float bottom;
	/*10*/
};
static_assert(sizeof(LTRBRect2F) == 0x10, "");

#pragma endregion


#pragma region D3D Types

// (custom)
struct D3DStateItem
{
	/*0,4*/ DWORD value; // not guaranteed to be uint, sometimes signed int, sometimes BOOL, maybe even func ptr, etc...
	/*4,4*/ BOOL isUsed;
	/*8*/
};
static_assert(sizeof(D3DStateItem) == 0x8, "");

//TD3DRMMatrix4D
//struct Matrix4F
//{
//	/*00,40*/ float values[4][4];
//	/*40*/
//};
//TD3DRMMatrix4D
typedef float Matrix4F[4][4];
static_assert(sizeof(Matrix4F) == 0x40, "");

//TD3DRMQuaternion
struct Quaternion3F
{
	/*00,4*/ float s;
	/*04,c*/ Vector3F v;
	/*10*/
};
static_assert(sizeof(Quaternion3F) == 0x10, "");

//TD3DRMRay
struct Ray3F
{
	/*00,c*/ Vector3F dir;
	/*0c,c*/ Vector3F pos;
	/*18*/
};
static_assert(sizeof(Ray3F) == 0x18, "");

//TD3DRMBox
struct Box3F
{
	/*00,c*/ Vector3F min;
	/*0c,c*/ Vector3F max;
	/*18*/
};
static_assert(sizeof(Box3F) == 0x18, "");

//TD3DHVertex
struct D3DHVertex
{
	/*00,4*/ unsigned int dwFlags; // Homogeneous clipping flags
	/*04,4*/ float hx;
	/*08,4*/ float hy;
	/*0c,4*/ float hz;
	/*10*/
};
static_assert(sizeof(D3DHVertex) == 0x10, "");

//TD3DTLVertex
struct D3DTLVertex
{
	/*00,4*/ float sx; // Screen coordinates
	/*04,4*/ float sy;
	/*08,4*/ float sz;
	/*0c,4*/ float rhw; // Reciprocal of homogeneous w
	/*10*/
};
static_assert(sizeof(D3DTLVertex) == 0x10, "");

#pragma endregion

} /* namespace lego */
#pragma endregion

#pragma pack(pop)