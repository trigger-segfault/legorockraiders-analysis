#pragma once

#include "../../framework.h"
#include "GhidraTypes.h"
#include "EnumTypes.h"
#include "BasicTypes.h"


#pragma pack(push, 1)

namespace lego {
#pragma region Predeclarations


#pragma endregion


#pragma region D3D Enum Types


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
static_assert(sizeof(D3DColorModel) == 0x4, "");

//TD3DRMCombineType
enum D3DRMCombineType : unsigned int
{
    D3DRMCOMBINE_REPLACE = 0,
    D3DRMCOMBINE_BEFORE  = 1,
    D3DRMCOMBINE_AFTER   = 2,
};
static_assert(sizeof(D3DRMCombineType) == 0x4, "");

//TD3DRMFrameConstraint
enum D3DRMFrameConstraint : unsigned int
{
    D3DRMCONSTRAIN_Z = 0, // use only X and Y rotations
    D3DRMCONSTRAIN_Y = 1, // use only X and Z rotations
    D3DRMCONSTRAIN_X = 2, // use only Y and Z rotations
};
static_assert(sizeof(D3DRMFrameConstraint) == 0x4, "");

//TD3DRMLightType
enum D3DRMLightType : unsigned int
{
    D3DRMLIGHT_AMBIENT       = 0,
    D3DRMLIGHT_POINT         = 1,
    D3DRMLIGHT_SPOT          = 2,
    D3DRMLIGHT_DIRECTIONAL   = 3,
    D3DRMLIGHT_PARALLELPOINT = 4,
};
static_assert(sizeof(D3DRMLightType) == 0x4, "");

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
static_assert(sizeof(D3DRMLoadOptions) == 0x4, "");

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
static_assert(sizeof(D3DRMSceneFogMethod) == 0x4, "");

//TD3DRMSortMode
enum D3DRMSortMode : unsigned int
{
	D3DRMSORT_FROMPARENT  = 0, // default
	D3DRMSORT_NONE        = 1, // don't sort child frames
	D3DRMSORT_FRONTTOBACK = 2, // sort child frames front-to-back
	D3DRMSORT_BACKTOFRONT = 3, // sort child frames back-to-front
};
static_assert(sizeof(D3DRMSortMode) == 0x4, "");

//TD3DRMUserVisualReason
enum D3DRMUserVisualReason : unsigned int
{
	D3DRMUSERVISUAL_CANSEE = 0,
	D3DRMUSERVISUAL_RENDER = 1,
};
static_assert(sizeof(D3DRMUserVisualReason) == 0x4, "");


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
static_assert(sizeof(D3DRMShadeMode) == 0x4, "");

//TD3DRMLightMode
enum D3DRMLightMode : unsigned int
{
	D3DRMLIGHT_OFF  = (0   * D3DRMSHADE_MAX) /*0x00*/,
	D3DRMLIGHT_ON   = (1   * D3DRMSHADE_MAX) /*0x08*/,

	D3DRMLIGHT_MASK = (0x7 * D3DRMSHADE_MAX) /*0x38*/, // (unused)
	D3DRMLIGHT_MAX  = (0x8 * D3DRMSHADE_MAX) /*0x40*/,
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMLightMode)
static_assert(sizeof(D3DRMLightMode) == 0x4, "");

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
static_assert(sizeof(D3DRMFillMode) == 0x4, "");

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
static_assert(sizeof(D3DRMRenderQuality) == 0x4, "");

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
static_assert(sizeof(D3DRMRenderMode) == 0x4, "");

enum D3DRMTextureQuality : unsigned int
{
	D3DRMTEXTURE_NEAREST          = 0, // choose nearest texel
	D3DRMTEXTURE_LINEAR           = 1, // interpolate 4 texels
	D3DRMTEXTURE_MIPNEAREST       = 2, // nearest texel in nearest mipmap
	D3DRMTEXTURE_MIPLINEAR        = 3, // interpolate 2 texels from 2 mipmaps
	D3DRMTEXTURE_LINEARMIPNEAREST = 4, // interpolate 4 texels in nearest mipmap
	D3DRMTEXTURE_LINEARMIPLINEAR  = 5, // interpolate 8 texels from 2 mipmaps
};
static_assert(sizeof(D3DRMTextureQuality) == 0x4, "");

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
static_assert(sizeof(D3DRMTextureFlags) == 0x4, "");

#undef D3DRMSHADOW_TRUEALPHA
// (unnamed)
enum D3DRMShadowOptions : unsigned int
{
	D3DRMSHADOW__NONE     = 0, // (custom)

	D3DRMSHADOW_TRUEALPHA = 0x00000001, // shadow should render without artifacts when true alpha is on
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMShadowOptions)
static_assert(sizeof(D3DRMShadowOptions) == 0x4, "");

//TD3DRMPaletteFlags
enum D3DRMPaletteFlags : unsigned int
{
    D3DRMPALETTE_FREE     = 0x0, // renderer may use this entry freely
    D3DRMPALETTE_READONLY = 0x1, // fixed but may be used by renderer
    D3DRMPALETTE_RESERVED = 0x2, // may not be used by renderer
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMPaletteFlags)
static_assert(sizeof(D3DRMPaletteFlags) == 0x4, "");

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
static_assert(sizeof(D3DRMWrapType) == 0x4, "");

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
static_assert(sizeof(D3DRMWireframeOptions) == 0x4, "");

//TD3DRMProjectionType
enum D3DRMProjectionType : unsigned int
{
	D3DRMPROJECT_PERSPECTIVE           = 0,
	D3DRMPROJECT_ORTHOGRAPHIC          = 1,
	D3DRMPROJECT_RIGHTHANDPERSPECTIVE  = 2, // Only valid pre-DX6
	D3DRMPROJECT_RIGHTHANDORTHOGRAPHIC = 3, // Only valid pre-DX6
};
static_assert(sizeof(D3DRMProjectionType) == 0x4, "");

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
static_assert(sizeof(D3DRMOptions) == 0x4, "");

//TD3DRMXOFFormat
enum D3DRMXOFFormat : unsigned int
{
    D3DRMXOF_BINARY     = 0,
    D3DRMXOF_COMPRESSED = 1,
    D3DRMXOF_TEXT       = 2,
};
static_assert(sizeof(D3DRMXOFFormat) == 0x4, "");


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
static_assert(sizeof(D3DRMSaveOptions) == 0x4, "");

//TD3DRMColorSource
enum D3DRMColorSource : unsigned int
{
    D3DRMCOLOR_FROMFACE   = 0,
    D3DRMCOLOR_FROMVERTEX = 1,
};
static_assert(sizeof(D3DRMColorSource) == 0x4, "");

//TD3DRMMaterialMode
enum D3DRMMaterialMode : unsigned int
{
	D3DRMMATERIAL_FROMMESH   = 0,
	D3DRMMATERIAL_FROMPARENT = 1,
	D3DRMMATERIAL_FROMFRAME  = 2,
};
static_assert(sizeof(D3DRMMaterialMode) == 0x4, "");

//TD3DRMFogMode
enum D3DRMFogMode : unsigned int
{
    D3DRMFOG_LINEAR             = 0, // linear between start and end
    D3DRMFOG_EXPONENTIAL        = 1, // density * exp(-distance)
    D3DRMFOG_EXPONENTIALSQUARED = 2, // density * exp(-distance*distance)
};
static_assert(sizeof(D3DRMFogMode) == 0x4, "");

//TD3DRMZBufferMode
enum D3DRMZBufferMode : unsigned int
{
    D3DRMZBUFFER_FROMPARENT = 0, // default
    D3DRMZBUFFER_ENABLE     = 1, // enable zbuffering
    D3DRMZBUFFER_DISABLE    = 2, // disable zbuffering
};
static_assert(sizeof(D3DRMZBufferMode) == 0x4, "");

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
static_assert(sizeof(D3DRMMaterialOverrideFlags) == 0x4, "");

#undef D3DRMDEVICE_NOZBUFFER
// (unnamed)
enum D3DRMCreateDeviceFromSurfaceFlags : unsigned int
{
	D3DRMDEVICE__NONE     = 0, // (custom)

	D3DRMDEVICE_NOZBUFFER = 0x00000001,
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMCreateDeviceFromSurfaceFlags)
static_assert(sizeof(D3DRMCreateDeviceFromSurfaceFlags) == 0x4, "");


//TD3DRMMapping
enum D3DRMMapping : unsigned int
{
	D3DRMMAP__NONE        = 0, // (custom)

	D3DRMMAP_WRAPU        = 0x1,
	D3DRMMAP_WRAPV        = 0x2,
	D3DRMMAP_PERSPCORRECT = 0x4,
};
DEFINE_ENUM_FLAG_OPERATORS(D3DRMMapping)
static_assert(sizeof(D3DRMMapping) == 0x4, "");


#undef DS3DMODE_NORMAL
#undef DS3DMODE_HEADRELATIVE
#undef DS3DMODE_DISABLE
enum DS3DMode : unsigned int
{
	DS3DMODE_NORMAL = 0x0,
	DS3DMODE_HEADRELATIVE = 0x1,
	DS3DMODE_DISABLE = 0x2,
};
static_assert(sizeof(DS3DMode) == 0x4, "");

//TD3DTransformStateType
enum D3DTransformStateType : unsigned int
{
	D3DTRANSFORMSTATE__NONE      = 0, // (custom)

	D3DTRANSFORMSTATE_WORLD      = 0x1,
	D3DTRANSFORMSTATE_VIEW       = 0x2,
	D3DTRANSFORMSTATE_PROJECTION = 0x3,
	D3DTRANSFORMSTATE_WORLD1     = 0x4,  // 2nd matrix to blend
	D3DTRANSFORMSTATE_WORLD2     = 0x5,  // 3rd matrix to blend
	D3DTRANSFORMSTATE_WORLD3     = 0x6,  // 4th matrix to blend
	D3DTRANSFORMSTATE_TEXTURE0   = 0x10,
	D3DTRANSFORMSTATE_TEXTURE1   = 0x11,
	D3DTRANSFORMSTATE_TEXTURE2   = 0x12,
	D3DTRANSFORMSTATE_TEXTURE3   = 0x13,
	D3DTRANSFORMSTATE_TEXTURE4   = 0x14,
	D3DTRANSFORMSTATE_TEXTURE5   = 0x15,
	D3DTRANSFORMSTATE_TEXTURE6   = 0x16,
	D3DTRANSFORMSTATE_TEXTURE7   = 0x17,
};
static_assert(sizeof(D3DTransformStateType) == 0x4, "");


#pragma endregion


#pragma region D3D Structure Types

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

#pragma pack(pop)
