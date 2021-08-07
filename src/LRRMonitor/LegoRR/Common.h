// Common.h : Declares common utility (and personal helper) functions used by LegoRR / CLGen.
//

#pragma once

#include "../framework.h"
#include "Model/BasicEnums.h"
#include "Model/BasicTypes.h"
//#include "../resource.h"

#define makeFunc(addr, ret, name, ...) static ret (__cdecl* name )( __VA_ARGS__ ) = (( ret (__cdecl*)( __VA_ARGS__ )) 0x ##addr )

#define makeGlob(addr, type, name) static type name = (( type ) 0x ##addr )

#define defineGlob(addr, type) (( type *) 0x ## addr)

#define defineGlobPtr(addr, type) *(( type *) 0x ## addr)


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

#undef D3DCOLOR_MONO
#undef D3DCOLOR_RGB
//TD3DColorModel
enum D3DColorModel : unsigned int
{
	D3DCOLOR__NONE = 0, // (custom)

	D3DCOLOR_MONO = 0x1,
	D3DCOLOR_RGB  = 0x2,
};
//TD3DRMColorModel
typedef D3DColorModel D3DRMColorModel;

//TD3DRMCombineType
enum D3DRMCombineType : unsigned int
{
    D3DRMCOMBINE_REPLACE = 0,
    D3DRMCOMBINE_BEFORE  = 1,
    D3DRMCOMBINE_AFTER   = 2,
};

//TD3DRMFrameConstraint
enum D3DRMFrameConstraint : unsigned int
{
    D3DRMCONSTRAIN_Z = 0, // use only X and Y rotations
    D3DRMCONSTRAIN_Y = 1, // use only X and Z rotations
    D3DRMCONSTRAIN_X = 2, // use only Y and Z rotations
};

//TD3DRMLightType
enum D3DRMLightType : unsigned int
{
    D3DRMLIGHT_AMBIENT       = 0,
    D3DRMLIGHT_POINT         = 1,
    D3DRMLIGHT_SPOT          = 2,
    D3DRMLIGHT_DIRECTIONAL   = 3,
    D3DRMLIGHT_PARALLELPOINT = 4,
};

#undef D3DRMLOAD_FROMFILE
#undef D3DRMLOAD_FROMRESOURCE
#undef D3DRMLOAD_FROMMEMORY
#undef D3DRMLOAD_FROMSTREAM
#undef D3DRMLOAD_FROMURL
#undef D3DRMLOAD_BYNAME
#undef D3DRMLOAD_BYPOSITION
#undef D3DRMLOAD_BYGUID
#undef D3DRMLOAD_FIRST
#undef D3DRMLOAD_INSTANCEBYREFERENCE
#undef D3DRMLOAD_INSTANCEBYCOPYING
#undef D3DRMLOAD_ASYNCHRONOUS
//TD3DRMLoadOptions
enum D3DRMLoadOptions : unsigned int
{
    D3DRMLOAD_FROMFILE            = 0x00000000,
    D3DRMLOAD_FROMRESOURCE        = 0x00000001,
    D3DRMLOAD_FROMMEMORY          = 0x00000002,
    D3DRMLOAD_FROMSTREAM          = 0x00000004,
    D3DRMLOAD_FROMURL             = 0x00000008,
    
    D3DRMLOAD_BYNAME              = 0x00000010,
    D3DRMLOAD_BYPOSITION          = 0x00000020,
    D3DRMLOAD_BYGUID              = 0x00000040,
    D3DRMLOAD_FIRST               = 0x00000080,

    D3DRMLOAD_INSTANCEBYREFERENCE = 0x00000100,
    D3DRMLOAD_INSTANCEBYCOPYING   = 0x00000200,

    D3DRMLOAD_ASYNCHRONOUS        = 0x00000400,
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMLoadOptions)

#undef D3DRMFOGMETHOD_VERTEX
#undef D3DRMFOGMETHOD_TABLE
#undef D3DRMFOGMETHOD_ANY
// Values for flags in Frame3::SetSceneFogMethod
enum D3DRMSceneFogMethod : unsigned int
{
	D3DRMFOGMETHOD__NONE  = 0, // (custom)

	D3DRMFOGMETHOD_VERTEX = 0x00000001,
	D3DRMFOGMETHOD_TABLE  = 0x00000002,
	D3DRMFOGMETHOD_ANY    = 0x00000004,
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMSceneFogMethod)

//TD3DRMSortMode
enum D3DRMSortMode : unsigned int
{
	D3DRMSORT_FROMPARENT  = 0, // default
	D3DRMSORT_NONE        = 1, // don't sort child frames
	D3DRMSORT_FRONTTOBACK = 2, // sort child frames front-to-back
	D3DRMSORT_BACKTOFRONT = 3, // sort child frames back-to-front
};

//TD3DRMUserVisualReason
enum D3DRMUserVisualReason : unsigned int
{
	D3DRMUSERVISUAL_CANSEE = 0,
	D3DRMUSERVISUAL_RENDER = 1,
};


//TD3DRMShadeMode
enum D3DRMShadeMode : unsigned int
{
	D3DRMSHADE_FLAT    = 0,
	D3DRMSHADE_GOURAUD = 1,
	D3DRMSHADE_PHONG   = 2,

	D3DRMSHADE_MASK    = 0x7, // (unused)
	D3DRMSHADE_MAX     = 0x8,
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMShadeMode)

//TD3DRMLightMode
enum D3DRMLightMode : unsigned int
{
	D3DRMLIGHT_OFF  = (0   * D3DRMSHADE_MAX) /*0x00*/,
	D3DRMLIGHT_ON   = (1   * D3DRMSHADE_MAX) /*0x08*/,

	D3DRMLIGHT_MASK = (0x7 * D3DRMSHADE_MAX) /*0x38*/, // (unused)
	D3DRMLIGHT_MAX  = (0x8 * D3DRMSHADE_MAX) /*0x40*/,
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMLightMode)

//TD3DRMFillMode
enum D3DRMFillMode : unsigned int
{
	D3DRMFILL_POINTS    = (0   * D3DRMLIGHT_MAX) /*0x00*/, // (unused)
	D3DRMFILL_WIREFRAME = (1   * D3DRMLIGHT_MAX) /*0x40*/,
	D3DRMFILL_SOLID     = (2   * D3DRMLIGHT_MAX) /*0x80*/,

	D3DRMFILL_MASK      = (0x7 * D3DRMLIGHT_MAX) /*0x1c0*/, // (unused)
	D3DRMFILL_MAX       = (0x8 * D3DRMLIGHT_MAX) /*0x200*/, // (unused)
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMFillMode)

#undef D3DRMRENDER_WIREFRAME
#undef D3DRMRENDER_UNLITFLAT
#undef D3DRMRENDER_FLAT
#undef D3DRMRENDER_GOURAUD
#undef D3DRMRENDER_PHONG
//TD3DRMRenderQuality
enum D3DRMRenderQuality : unsigned int
{
	D3DRMRENDER__NONE     = 0, // (custom)

	D3DRMRENDER_WIREFRAME = (D3DRMSHADE_FLAT    + D3DRMLIGHT_OFF + D3DRMFILL_WIREFRAME) /*0x40*/,
	D3DRMRENDER_UNLITFLAT = (D3DRMSHADE_FLAT    + D3DRMLIGHT_OFF + D3DRMFILL_SOLID)     /*0x80*/,
	D3DRMRENDER_FLAT      = (D3DRMSHADE_FLAT    + D3DRMLIGHT_ON  + D3DRMFILL_SOLID)     /*0x88*/,
	D3DRMRENDER_GOURAUD   = (D3DRMSHADE_GOURAUD + D3DRMLIGHT_ON  + D3DRMFILL_SOLID)     /*0x89*/,
	D3DRMRENDER_PHONG     = (D3DRMSHADE_PHONG   + D3DRMLIGHT_ON  + D3DRMFILL_SOLID)     /*0x8a*/,
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMRenderQuality)

#undef D3DRMRENDERMODE_BLENDEDTRANSPARENCY
#undef D3DRMRENDERMODE_SORTEDTRANSPARENCY
#undef D3DRMRENDERMODE_LIGHTINMODELSPACE
#undef D3DRMRENDERMODE_VIEWDEPENDENTSPECULAR
enum D3DRMRenderMode : unsigned int
{
	D3DRMRENDERMODE__NONE                 = 0, // (custom)

	D3DRMRENDERMODE_BLENDEDTRANSPARENCY   = 0x1,
	D3DRMRENDERMODE_SORTEDTRANSPARENCY    = 0x2,
	D3DRMRENDERMODE_LIGHTINMODELSPACE     = 0x8,
	D3DRMRENDERMODE_VIEWDEPENDENTSPECULAR = 0x16,
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMRenderMode)

enum D3DRMTextureQuality : unsigned int
{
	D3DRMTEXTURE_NEAREST          = 0, // choose nearest texel
	D3DRMTEXTURE_LINEAR           = 1, // interpolate 4 texels
	D3DRMTEXTURE_MIPNEAREST       = 2, // nearest texel in nearest mipmap
	D3DRMTEXTURE_MIPLINEAR        = 3, // interpolate 2 texels from 2 mipmaps
	D3DRMTEXTURE_LINEARMIPNEAREST = 4, // interpolate 4 texels in nearest mipmap
	D3DRMTEXTURE_LINEARMIPLINEAR  = 5, // interpolate 8 texels from 2 mipmaps
};

#undef D3DRMTEXTURE_FORCERESIDENT
#undef D3DRMTEXTURE_STATIC
#undef D3DRMTEXTURE_DOWNSAMPLEPOINT
#undef D3DRMTEXTURE_DOWNSAMPLEBILINEAR
#undef D3DRMTEXTURE_DOWNSAMPLEREDUCEDEPTH
#undef D3DRMTEXTURE_DOWNSAMPLENONE
#undef D3DRMTEXTURE_CHANGEDPIXELS
#undef D3DRMTEXTURE_CHANGEDPALETTE
#undef D3DRMTEXTURE_INVALIDATEONLY
// (unnamed)
enum D3DRMTextureFlags : unsigned int
{
	D3DRMTEXTURE__NONE                  = 0, // (custom)

	D3DRMTEXTURE_FORCERESIDENT          = 0x00000001, // texture should be kept in video memory
	D3DRMTEXTURE_STATIC                 = 0x00000002, // texture will not change
	D3DRMTEXTURE_DOWNSAMPLEPOINT        = 0x00000004, // point filtering should be used when downsampling
	D3DRMTEXTURE_DOWNSAMPLEBILINEAR     = 0x00000008, // bilinear filtering should be used when downsampling
	D3DRMTEXTURE_DOWNSAMPLEREDUCEDEPTH  = 0x00000010, // reduce bit depth when downsampling
	D3DRMTEXTURE_DOWNSAMPLENONE         = 0x00000020, // texture should never be downsampled
	D3DRMTEXTURE_CHANGEDPIXELS          = 0x00000040, // pixels have changed
	D3DRMTEXTURE_CHANGEDPALETTE         = 0x00000080, // palette has changed
	D3DRMTEXTURE_INVALIDATEONLY         = 0x00000100, // dirty regions are invalid
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMTextureFlags)

#undef D3DRMSHADOW_TRUEALPHA
// (unnamed)
enum D3DRMShadowOptions : unsigned int
{
	D3DRMSHADOW__NONE     = 0, // (custom)

	D3DRMSHADOW_TRUEALPHA = 0x00000001, // shadow should render without artifacts when true alpha is on
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMShadowOptions)

//TD3DRMPaletteFlags
enum D3DRMPaletteFlags : unsigned int
{
    D3DRMPALETTE_FREE     = 0x0, // renderer may use this entry freely
    D3DRMPALETTE_READONLY = 0x1, // fixed but may be used by renderer
    D3DRMPALETTE_RESERVED = 0x2, // may not be used by renderer
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMPaletteFlags)

//TD3DRMWrapType
enum D3DRMWrapType : unsigned int
{
	D3DRMWRAP_FLAT     = 0,
	D3DRMWRAP_CYLINDER = 1,
	D3DRMWRAP_SPHERE   = 2,
	D3DRMWRAP_CHROME   = 3,
	D3DRMWRAP_SHEET    = 4,
	D3DRMWRAP_BOX      = 5,
};

#undef D3DRMWIREFRAME_CULL
#undef D3DRMWIREFRAME_HIDDENLINE
// (unnamed)
enum D3DRMWireframeOptions : unsigned int
{
	D3DRMWIREFRAME__NONE      = 0, // (custom)

	D3DRMWIREFRAME_CULL       = 0x1, // cull backfaces
	D3DRMWIREFRAME_HIDDENLINE = 0x2, // lines are obscured by closer objects
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMWireframeOptions)

//TD3DRMProjectionType
enum D3DRMProjectionType : unsigned int
{
	D3DRMPROJECT_PERSPECTIVE           = 0,
	D3DRMPROJECT_ORTHOGRAPHIC          = 1,
	D3DRMPROJECT_RIGHTHANDPERSPECTIVE  = 2, // Only valid pre-DX6
	D3DRMPROJECT_RIGHTHANDORTHOGRAPHIC = 3, // Only valid pre-DX6
};

#undef D3DRMOPTIONS_LEFTHANDED
#undef D3DRMOPTIONS_RIGHTHANDED
// (unnamed)
enum D3DRMOptions : unsigned int
{
	D3DRMOPTIONS__NONE       = 0, // (custom)

	D3DRMOPTIONS_LEFTHANDED  = 0x00000001, // Default
	D3DRMOPTIONS_RIGHTHANDED = 0x00000002,
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMOptions)

//TD3DRMXOFFormat
enum D3DRMXOFFormat : unsigned int
{
    D3DRMXOF_BINARY     = 0,
    D3DRMXOF_COMPRESSED = 1,
    D3DRMXOF_TEXT       = 2,
};


#undef D3DRMXOFSAVE_NORMALS
#undef D3DRMXOFSAVE_TEXTURECOORDINATES
#undef D3DRMXOFSAVE_MATERIALS
#undef D3DRMXOFSAVE_TEXTURENAMES
#undef D3DRMXOFSAVE_ALL
#undef D3DRMXOFSAVE_TEMPLATES
#undef D3DRMXOFSAVE_TEXTURETOPOLOGY
//TD3DRMSaveOptions
enum D3DRMSaveOptions : unsigned int
{
	D3DRMXOFSAVE__NONE              = 0, // (custom)

	D3DRMXOFSAVE_NORMALS            = 0x1,
	D3DRMXOFSAVE_TEXTURECOORDINATES = 0x2,
	D3DRMXOFSAVE_MATERIALS          = 0x4,
	D3DRMXOFSAVE_TEXTURENAMES       = 0x8,
	D3DRMXOFSAVE_ALL                = 0xf,
	D3DRMXOFSAVE_TEMPLATES          = 0x10,
	D3DRMXOFSAVE_TEXTURETOPOLOGY    = 0x20,
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMSaveOptions)

//TD3DRMColorSource
enum D3DRMColorSource : unsigned int
{
    D3DRMCOLOR_FROMFACE   = 0,
    D3DRMCOLOR_FROMVERTEX = 1,
};

//TD3DRMMaterialMode
enum D3DRMMaterialMode : unsigned int
{
	D3DRMMATERIAL_FROMMESH   = 0,
	D3DRMMATERIAL_FROMPARENT = 1,
	D3DRMMATERIAL_FROMFRAME  = 2,
};

//TD3DRMFogMode
enum D3DRMFogMode : unsigned int
{
    D3DRMFOG_LINEAR             = 0, // linear between start and end
    D3DRMFOG_EXPONENTIAL        = 1, // density * exp(-distance)
    D3DRMFOG_EXPONENTIALSQUARED = 2, // density * exp(-distance*distance)
};

//TD3DRMZBufferMode
enum D3DRMZBufferMode : unsigned int
{
    D3DRMZBUFFER_FROMPARENT = 0, // default
    D3DRMZBUFFER_ENABLE     = 1, // enable zbuffering
    D3DRMZBUFFER_DISABLE    = 2, // disable zbuffering
};

#undef D3DRMMATERIALOVERRIDE_DIFFUSE_ALPHAONLY
#undef D3DRMMATERIALOVERRIDE_DIFFUSE_RGBONLY
#undef D3DRMMATERIALOVERRIDE_DIFFUSE
#undef D3DRMMATERIALOVERRIDE_AMBIENT
#undef D3DRMMATERIALOVERRIDE_EMISSIVE
#undef D3DRMMATERIALOVERRIDE_SPECULAR
#undef D3DRMMATERIALOVERRIDE_POWER
#undef D3DRMMATERIALOVERRIDE_TEXTURE
#undef D3DRMMATERIALOVERRIDE_DIFFUSE_ALPHAMULTIPLY
#undef D3DRMMATERIALOVERRIDE_ALL
// (unnamed)
enum D3DRMMaterialOverrideFlags : unsigned int
{
	D3DRMMATERIALOVERRIDE__NONE                 = 0, // (custom)

	D3DRMMATERIALOVERRIDE_DIFFUSE_ALPHAONLY     = 0x00000001,
	D3DRMMATERIALOVERRIDE_DIFFUSE_RGBONLY       = 0x00000002,
	D3DRMMATERIALOVERRIDE_DIFFUSE               = 0x00000003,
	D3DRMMATERIALOVERRIDE_AMBIENT               = 0x00000004,
	D3DRMMATERIALOVERRIDE_EMISSIVE              = 0x00000008,
	D3DRMMATERIALOVERRIDE_SPECULAR              = 0x00000010,
	D3DRMMATERIALOVERRIDE_POWER                 = 0x00000020,
	D3DRMMATERIALOVERRIDE_TEXTURE               = 0x00000040,
	D3DRMMATERIALOVERRIDE_DIFFUSE_ALPHAMULTIPLY = 0x00000080,
	D3DRMMATERIALOVERRIDE_ALL                   = 0x000000ff,
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMMaterialOverrideFlags)

#undef D3DRMDEVICE_NOZBUFFER
// (unnamed)
enum D3DRMCreateDeviceFromSurfaceFlags : unsigned int
{
	D3DRMDEVICE__NONE     = 0, // (custom)

	D3DRMDEVICE_NOZBUFFER = 0x00000001,
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMCreateDeviceFromSurfaceFlags)


//TD3DRMMapping
enum D3DRMMapping : unsigned int
{
	D3DRMMAP__NONE        = 0, // (custom)

	D3DRMMAP_WRAPU        = 0x1,
	D3DRMMAP_WRAPV        = 0x2,
	D3DRMMAP_PERSPCORRECT = 0x4,
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMMapping)



#undef DS3DMODE_NORMAL
#undef DS3DMODE_HEADRELATIVE
#undef DS3DMODE_DISABLE
enum DS3DMode : unsigned int
{
	DS3DMODE_NORMAL = 0x0,
	DS3DMODE_HEADRELATIVE = 0x1,
	DS3DMODE_DISABLE = 0x2,
};

// It's likely a lot of these modes where made to run unit tests/etc.
// many could have been removed in the release build.
enum ProgrammerMode : unsigned int
{
	PROGRAMMER_OFF = 0,
	PROGRAMMER_MODE_1 = 1,
	PROGRAMMER_MODE_2 = 2, // condition for >1 and -testercall
	PROGRAMMER_MODE_3 = 3, // front end and intros are disabled (>=3)
	PROGRAMMER_MODE_4 = 4, // one check if (> 3)
	PROGRAMMER_MODE_10 = 10, // test level AVI's?
	PROGRAMMER_MODE_11 = 11, // (crashes after title loading bar)
	// more values exist, at least up to and including 10?
};

// <https://kb.rockraidersunited.com/Command-line_parameters>
// All usages/assignments of CmdlineFlags are now known.
enum CmdlineFlags : unsigned int
{
	CMD_NONE = 0,

	CMD_D3DRMUPDATED = 0x1,       // [volatile] related to Direct3DRM->Update (needs calling?)
	CMD_FULLSCREEN = 0x2,       // set when booting the game into fullscreen
	CMD_TEXTUREVIDEOMEMORY = 0x4,       // [writeonly] (set, but never checked for) DEVICEMODE_TEXTUREVIDEOMEMORY
	CMD_MIPMAP = 0x8,       // set in GameInit if both Filter and MipMap config options are TRUE

	CMD_NOFPSLOCK = 0x10,      // [readonly] (assigns WinMain gameloop frame rate to 0.0)
	CMD_NM = 0x20,      // "-nm"  (no texture management?, disables texture management for Voodoo2-based cards, assigned if "-ftm" is NOT set and TextureUsage (x byteDepth) is <= to free video memory)
	CMD_BEST = 0x40,      // "-best"
	CMD_FPSLOCK30 = 0x80,      // [readonly] (assigns WinMain gameloop frame rate to (25.0 / 30.0), equivalent of "-fpslock 30")

	CMD_WINDOW = 0x100,     // "-window"
	CMD_STARTLEVEL = 0x200,     // "-startlevel <level>" (requires: FrontEnd FALSE)
	CMD_CLEANSAVES = 0x400,     // "-cleansaves"
	//CMD_UNK_800            = 0x800,

	//CMD_UNK_1000           = 0x1000,
	CMD_DEBUG = 0x2000,    // "-debug"
	CMD_DUALMOUSE = 0x4000,    // "-dualmouse"
	CMD_DEBUGCOMPLETE = 0x8000,    // "-debugcomplete" (triggers: "-debug")

	CMD_TESTERCALL = 0x10000,   // "-testercall" (triggers: "-programmer 2", but does not overwrite real "-programmer" argument)
	CMD_TESTLEVELS = 0x20000,   // "-testlevels"
	CMD_FTM = 0x40000,   // "-ftm"
	CMD_FVF = 0x80000,   // "-fvf"

	CMD_REDUCESAMPLES = 0x100000,  // "-reducesamples"
	CMD_SHOWVERSION = 0x200000,  // "-showversion"
	CMD_REDUCEANIMATION = 0x400000,  // "-reduceanimation"
	CMD_REDUCEPROMESHES = 0x800000,  // "-reducepromeshes"

	CMD_REDUCEFLICS = 0x1000000, // "-reduceflics"
	CMD_REDUCEIMAGES = 0x2000000, // "-reduceimages"
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


enum FeatureFlags : unsigned int
{
	FEATURE_NONE = 0,

	FEATURE_BLOCKFADEIN = 0x8000, // when specified, all blocks transition (fade) into their new state,
									// Walls selected for drilling will fade to color, Power paths will fade into power.
									// Rubble fades in when paths are destroyed, etc... Really neat!
};
DEFINE_ENUM_FLAG_OPERATORS(FeatureFlags)


	//struct RenderStateItem
	//{
	//	/*0,4*/ unsigned int value; // not guaranteed to be uint, sometimes signed int, sometimes BOOL, etc...
	//	/*4,4*/ BOOL isUsed;
	//	/*8*/
	//};
#if 0
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
	struct Vector3F
	{
		/*0,4*/ float x;
		/*4,4*/ float y;
		/*8,4*/ float z;
		/*c*/
	};
	struct Vector4F
	{
		/*00,4*/ float x;
		/*04,4*/ float y;
		/*08,4*/ float z;
		/*0c,4*/ float w;
		/*10*/
	};
	//TD3DRMQuaternion
	struct Quaternion3F
	{
		/*00,4*/ float s;
		/*04,4*/ Vector3F v;
		/*10*/
	};

	//TD3DRMRay
	struct Ray3F
	{
		/*00,c*/ Vector3F dir;
		/*0c,c*/ Vector3F pos;
		/*18*/
	};

	//TD3DRMBox
	struct Box3F
	{
		/*00,c*/ Vector3F min;
		/*0c,c*/ Vector3F max;
		/*18*/
	};

	//TD3DRMMatrix4D
	struct Matrix4F
	{
		/*00,40*/ float values[4][4];
		/*40*/
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
struct P1P2Rect2I
{
	/*00,4*/ int x1;
	/*04,4*/ int y1;
	/*08,4*/ int x2;
	/*0c,4*/ int y2;
	/*10*/
};
struct P1P2Rect2F
{
	/*00,4*/ float x1;
	/*04,4*/ float y1;
	/*08,4*/ float x2;
	/*0c,4*/ float y2;
	/*10*/
};
struct LTRBRect2I
{
	/*00,4*/ int left;
	/*04,4*/ int top;
	/*08,4*/ int right;
	/*0c,4*/ int bottom;
	/*10*/
};
struct LTRBRect2F
{
	/*00,4*/ float left;
	/*04,4*/ float top;
	/*08,4*/ float right;
	/*0c,4*/ float bottom;
	/*10*/
};
//TD3DHVertex
struct D3DHVertex
{
	/*00,4*/ unsigned int dwFlags; // Homogeneous clipping flags
	/*04,4*/ float hx;
	/*08,4*/ float hy;
	/*0c,4*/ float hz;
	/*10*/
};
//TD3DTLVertex
struct D3DTLVertex
{
	/*00,4*/ float sx; // Screen coordinates
	/*04,4*/ float sy;
	/*08,4*/ float sz;
	/*0c,4*/ float rhw; // Reciprocal of homogeneous w
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
#endif

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
		/*extern CmdlineFlags g_CMDLINE_FLAGS;
		// [INCLUSIVE/ACCESSOR]: ParseCmdFlags, WinMain functions, game functions, GetProgrammerMode (accessor)
		// <LegoRR.exe @00506f88>  XREF[17]
		extern ProgrammerMode g_PROGRAMMER_MODE;
		// [EXCLUSIVE/ACCESSOR]: ParseCmdFlags, GetStartLevel (accessor)
		// <LegoRR.exe @00506f8c>  XREF[3,1]
		extern char g_STARTLEVEL[256];
		// [EXCLUSIVE/ACCESSOR]: ParseCmdFlags, GetDebugFlags (accessor)
		// <LegoRR.exe @0050708c>  XREF[2]
		extern FeatureFlags g_DEBUG_FLAGS; // 0x8000 (block fade)*/

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

	/*// <LegoRR.exe @00401b30>
	ProgrammerMode __cdecl GetProgrammerMode(void);

	// <LegoRR.exe @00401b40>
	const char* __cdecl GetStartLevel(void);

	// <LegoRR.exe @00401b70>
	int __cdecl GetResolutionWidth(void);

	// <LegoRR.exe @00401b80>
	int __cdecl GetResolutionHeight(void);

	// <LegoRR.exe @00478230>
	FeatureFlags __cdecl GetFeatureFlags(void);*/

#pragma endregion

} /* namespace lego */
