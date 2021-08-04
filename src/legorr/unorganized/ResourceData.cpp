

#pragma region Enums

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

// const
//   D3DRMSHADE_FLAT = 0;
//   D3DRMSHADE_GOURAUD = 1;
//   D3DRMSHADE_PHONG = 2;
//   D3DRMSHADE_MASK = 7;
//   D3DRMSHADE_MAX = 8;

// type
//   PD3DRMLightMode = ^TD3DRMLightMode;
//   TD3DRMLightMode = WORD;

// const
//   D3DRMLIGHT_OFF  = 0 * D3DRMSHADE_MAX;
//   D3DRMLIGHT_ON   = 1 * D3DRMSHADE_MAX;
//   D3DRMLIGHT_MASK = 7 * D3DRMSHADE_MAX;
//   D3DRMLIGHT_MAX  = 8 * D3DRMSHADE_MAX;

// type
//   PD3DRMFillMode = ^TD3DRMFillMode;
//   TD3DRMFillMode = WORD;

// const
//   D3DRMFILL_POINTS    = 0 * D3DRMLIGHT_MAX;
//   D3DRMFILL_WIREFRAME = 1 * D3DRMLIGHT_MAX;
//   D3DRMFILL_SOLID     = 2 * D3DRMLIGHT_MAX;
//   D3DRMFILL_MASK      = 7 * D3DRMLIGHT_MAX;
//   D3DRMFILL_MAX       = 8 * D3DRMLIGHT_MAX;

// type
//   PD3DRMRenderQuality = ^TD3DRMRenderQuality;
//   TD3DRMRenderQuality = DWORD;

// const
//   D3DRMRENDER_WIREFRAME   =
//       (D3DRMSHADE_FLAT + D3DRMLIGHT_OFF + D3DRMFILL_WIREFRAME);
//   D3DRMRENDER_UNLITFLAT   =
//       (D3DRMSHADE_FLAT + D3DRMLIGHT_OFF + D3DRMFILL_SOLID);
//   D3DRMRENDER_FLAT        =
//       (D3DRMSHADE_FLAT + D3DRMLIGHT_ON + D3DRMFILL_SOLID);
//   D3DRMRENDER_GOURAUD     =
//       (D3DRMSHADE_GOURAUD + D3DRMLIGHT_ON + D3DRMFILL_SOLID);
//   D3DRMRENDER_PHONG       =
//       (D3DRMSHADE_PHONG + D3DRMLIGHT_ON + D3DRMFILL_SOLID);



// D3DRMViewportClear2


#pragma endregion


#pragma region Structs

//D3DRMVector
struct Vector3F
{
    /*0,4*/ float x;
    /*4,4*/ float y;
    /*8,4*/ float z;
    /*c*/
};

//D3DRMVector4D
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
//   PD3DRMQuaternion = ^TD3DRMQuaternion;
//   TD3DRMQuaternion = packed record
//     s: TD3DValue;
//     v: TD3DVector;
//   end;

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

struct D3DRMMeshLoadContext
{
  /*00,4*/ unsigned int fileSize;
  /*04,4*/ void* fileData;
  /*08,4*/ BOOL bool_8;
  /*0c,4*/ const char* filename;
  /*10*/
};

#pragma endregion


// Other name parts: "<ResourceName>:NOTEXTURE"
enum ResourceType : int
{
	RESOURCE__INVALID = -1,

	RESOURCE_NULL     = 0, // "NULL"  (ext: "")
	RESOURCE_MESH     = 1, // "MESH"  (ext: "x")
	RESOURCE_FRAME    = 2, // "FRAME" (ext: "x")
	RESOURCE_ANIM     = 3, // "ANIM"  (ext: "x")
	RESOURCE_ACT      = 4, // "ACT"   (ext: "ae") (loads "ae"-extension CFG file : g_FILEEXT_AE)
	RESOURCE_LIGHT    = 5, // NULL    (ext: "")   (explicit)
	RESOURCE_unassigned=6, // NULL    (ext: NULL) (implicit)
	RESOURCE_LWS      = 7, // "LWS"   (ext: NULL)
	RESOURCE_LWO      = 8, // "LWO"   (ext: NULL)
};
static const char* ResourceNames[] = {
	"NULL",
	"MESH",
	"FRAME",
	"ANIM",
	"ACT",
	NULL,    // (LIGHT)
	NULL,    // (not assigned)
	"LWS",
	"LWO",
};
static const char* ResourceExtensions[] = {
	"",   // NULL
	"x",  // MESH
	"x",  // FRAME
	"x",  // ANIM
	"ae", // ACT
	"",   // (LIGHT)
	NULL, // (not assigned)
	NULL, // (LWS, not assigned)
	NULL, // (LWO, not assigned)
};

struct LiveObject;
struct ResourceData;

struct LwoFrame
{
	/*70*/
};
struct ActStruct_14
{
	/*00,4*/ ResourceData* resData; // (init: DuplicateResource src resData)
	/*04,4*/ undefined4 field_4;  // (init: 0)
	/*08,4*/ undefined4 field_8;  // (init: 0)
	/*0c,4*/ IDirect3DRMFrame3* frame_c; // (init: resData->frame2)
	/*10,4*/ BOOL isUsed; // (init: 1)
	/*14*/
};

struct Struct_34
{
	/*00,4*/ unsigned int count_0;
	/*04,4*/ undefined4 field_4;
	/*08,4*/ LwoFrame* lwoTable_8;
	/*0c,4*/ IDirect3DRMUserVisual* userVisual_c;
	/*10,4*/ IDirect3DRMViewport2* viewport_10;
	/*14,4*/ undefined4 param4_14;
	/*18,4*/ unsigned int unkFlags3_18;
	/*1c,4*/ void* ptr_1c;
	/*20,4*/ unsigned int refCount_20;
	/*24,4*/ Struct_34* struct34_24; // not sure about this
	/*28,4*/ IDirect3DRMFrame3* frame_28;
	/*2c,4*/ unsigned int flags;
	/*30,4*/ Struct_34* pool_m_next;
	/*34*/
};

struct ResourceSubdata
{
	/*00,4*/ char* name; // const char*??
	/*04,4*/ IDirect3DRMLight* light;
	/*08,4*/ IDirect3DRMMesh* mesh;
	/*0c,4*/ Struct_34* struct34_c; // uservisual?
	/*10*/
};

enum DS3DMode : unsigned int
{
	DS3DMODE_NORMAL       = 0x0,
	DS3DMODE_HEADRELATIVE = 0x1,
	DS3DMODE_DISABLE      = 0x2,
};

struct SoundResource
{
	/*00,4*/ IDirectSound3DBuffer* sound3dBuffer;
	/*04,4*/ undefined4 field_4;
	/*08,4*/ undefined4 field_8;
	/*0c,4*/ undefined4 field_c;
	/*10,4*/ SoundResource* previous;
	/*14*/
};

struct ActivityFrameResource
{
	/*00,4*/ ActivityFrameResource* previous_0;
	/*04,4*/ void* struct38_4;  // (if bool_c)
	/*08,4*/ IDirect3DRMAnimationSet2* animSet; // (if !bool_c)
	/*0c,4*/ BOOL boolMode; // (0 for different behavior, refCount?)
	/*10,4*/ IDirect3DRMFrame3* frame_10; // (if !bool_c)
	/*14,4*/ IDirect3DRMFrame3** framesTable; // (if !bool_c) table of COM objects, length is count_18
	/*18,4*/ unsigned int framesCount; // (if !bool_c)
	/*1c,4*/ undefined4 field_1c;
	/*20*/
};

// <LegoRR.exe @00489920>
undefined4* __cdecl lego::res::Res_InitActivityFrameResource(undefined4* param_1, IDirect3DRMFrame3* rmFrame3, undefined4* out_param_3)
{
	IDirect3DRMFrame3 **lplpD3DRMFrame;
	// undefined4 *puVar1;
	undefined4 *puVar2;
	void *pvVar3;
	int iVar4;
	undefined4 *puVar5;
	IDirect3DRMFrame3 *unaff_retaddr;
	undefined4 local_20;
	undefined4 uStack28;
	undefined4 *local_8;
	
	ActivityFrameResource* puVar1 = (ActivityFrameResource*)std::malloc(sizeof(ActivityFrameResource) /*0x20*/);
	iVar4 = 8;
	puVar2 = param_1;
	puVar5 = puVar1;
	if (param_1[3] == 0) {
		std::memset(puVar1, 0, sizeof(ActivityFrameResource) /*0x20*/);
		// for (; iVar4 != 0; iVar4 += -1) {
		// 	*puVar5 = 0;
		// 	puVar5 = puVar5 + 1;
		// }
		//IDirect3DRMFrame3->AddTransform(this, TD3DRMCombineType rctCombine, Matrix4F* rmMatrix)
		(**(code **)(*(int *)param_1[2] + 0x38))((int *)param_1[2]);
		puVar1[2] = 0;
		*puVar1 = param_1;
		lplpD3DRMFrame = (IDirect3DRMFrame3 **)(puVar1 + 4);
		globals::g_IDirect3DRM3->CreateFrame(rmFrame3, &puVar1[4]);
		pvVar3 = std::malloc(param_1[6] << 2); // count_18 * 4 (sizeof(IUnknown*))
		puVar1[5] = pvVar3;
		FUN_00489cb0((undefined **)param_1[4], (int *)*lplpD3DRMFrame, param_1[3]);
		puVar1[6] = param_1[6];
		if (out_param_3 != NULL) {
			*out_param_3 = param_1[7];
		}
		local_20 = puVar1[5];
		uStack28 = 0;
		FUN_00489bd0((int *)*lplpD3DRMFrame, 0, FUN_00489bb0, &stack0xffffffcc);
	}
	else {
		std::memcpy(puVar1, param_1, sizeof(ActivityFrameResource) /*0x20*/);
		// for (; iVar4 != 0; iVar4 += -1) {
		// 	*puVar5 = *puVar2;
		// 	puVar2 = puVar2 + 1;
		// 	puVar5 = puVar5 + 1;
		// }
		puVar2 = FUN_00487cc0((undefined4 *)param_1[1], rmFrame3);
		puVar1[1] = puVar2;
		*out_param_3 = 0;
		if (out_param_3 != NULL) {
			*out_param_3 = param_1[7];
			// return puVar1;
		}
	}
	return puVar1;
}

// <LegoRR.exe @00488c90>
void __cdecl lego::res::Res_FreeActivityFrameResource_Field4(undefined *param_1)
{
	int iVar1;
	undefined *puVar2;
	ushort uVar3;
	
	do {
		iVar1 = *(int *)(param_1 + 0x30);
		puVar2 = *(undefined **)(param_1 + 0x2c);
		*(int *)(param_1 + 0x30) = iVar1 + -1;
		if (iVar1 + -1 == 0) {
			uVar3 = 0;
			if (*(short *)(param_1 + 0x24) != 0) {
				do {
					FUN_00488d30((int)param_1,(undefined4 *)(*(int *)(param_1 + 0x20) + (uint)uVar3 * 0x34));
					uVar3 += 1;
				} while (uVar3 < *(ushort *)(param_1 + 0x24));
			}
			if (*(int *)(param_1 + 0x2c) == 0) {
				std::free(*(void **)(param_1 + 0x20));
				std::free(*(void **)(param_1 + 8));
				if (*(short *)(param_1 + 0x28) != 0) {
					std::free(*(void **)(param_1 + 0x18));
				}
			}
			std::free(*(void **)(param_1 + 0x14));
			std::free(param_1);
		}
		param_1 = puVar2;
	} while (puVar2 != NULL);
	return;
}

// <LegoRR.exe @00465350>
int __cdecl lego::snd::Snd_PlayOrInitSoundUnk(IDirect3DRMFrame3* rmFrame3, const int sampleIndex, BOOL flag2, BOOL flag4, const Vector3F* opt_position);

// <LegoRR.exe @00465630>
BOOL __cdecl Snd_GetSFXFlag_1(void);

// <LegoRR.exe @00464f30>
BOOL __cdecl Snd_GetSFX(const char* sfxName, int* out_index);


// <https://github.com/Krakean/lightalloy/blob/master/Source/Common/DirectShow/DXTypes.pas>
typedef float D3DValue;
typedef int D3DFixed;
typedef unsigned int D3DColor;
typedef long long ReferenceTime;

//TD3DColorValue
struct D3DColorValue
{
	/*00,4*/ float r;
	/*04,4*/ float g;
	/*08,4*/ float b;
	/*0c,4*/ float a;
	/*10*/
};
//TD3DVector
struct D3DVector
{
	/*0,4*/ float x;
	/*4,4*/ float y;
	/*8,4*/ float z;
	/*c*/
};
//TD3DRect
struct D3DRect
{
	/*00,4*/ int x1;
	/*04,4*/ int y1;
	/*08,4*/ int x2;
	/*0c,4*/ int y2;
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

typedef int (__cdecl* PlayOrInitSampleCallback)(IDirect3DRMFrame3* rmFrame3, const int sampleIndex, BOOL flag2, BOOL flag4, const Vector3F* opt_position);
typedef BOOL (__cdecl* GetSampleCallback)(const char* sfxName, int* out_index);
typedef BOOL (__cdecl* GetSoungsFlag1Callback)

typedef void (__cdecl* ResourceSoundCallback)(const char* sampleName, ResourceData* resData, void* lpValue);

typedef void (__cdecl* ResourceDrawCallback)(ResourceData* resData, void* lpValue);

typedef void (__cdecl* D3DRMFrame3MoveCallback)(IDirect3DRMFrame3* lpD3DRMFrame, void* lpArg, float delta);
typedef void (__cdecl* D3DRMObjectCallback)(IDirect3DRMObject* lpD3DRMObj, void* lpArg);

typedef void (__cdecl* D3DRMUpdateCallback)(IDirect3DRMDevice lpD3DRMDev, void* lpArg, int iRectCount, const )

typedef void (__cdecl* D3DRMDevice3UpdateCallback)(IDirect3DRMDevice3 lpD3DRMDev, void* lpArg, int iRectCount)

// typedef float10 (__cdecl* GetSurfaceZCallback)(float x, float y, LevelSurfaceMap* surfMap);
typedef float (__cdecl* GetSurfaceZCallback)(float x, float y, LevelSurfaceMap* surfMap);

struct ResourceAppData
{
	/*00,4*/ ResourceData* resData;   // (init: resData)
	/*04,4*/ char* filename;          // (init: 0)
	/*08,4*/ const char* frameName;   // (init: param_6, must release this name???)
	/*0c,4*/ undefined4 field_c;     // (init: *param_5 ?? 0)
	/*10,4*/ float float_10;          // (init: *param_7 ?? 0)
	/*14,4*/ float float_14;          // (init: *param_8 ?? 0)
	/*18,4*/ const char* sampleName;  // (init: param_9)
	/*1c,4*/ ActivityFrameResource* actFrameRes; // (init: param_3)
	/*20,4*/ undefined4 field_20;   // (init: *param_11 ?? 0)
	/*24,4*/ SoundResource* soundRes; // (init: param_10)
	/*28*/
};

struct ResourceData
{
    /*00,4*/ IDirect3DRMFrame3* frame1;
    /*04,4*/ IDirect3DRMFrame3* frame2;
    /*08,4*/ IDirect3DRMFrame3* frame3;
    /*0c,4*/ ResourceSubdata* subdata_c;
	/*10,4*/ ResourceType resType;
	/*14,4*/ undefined4 flags_14;
	/*18,4*/ undefined4 field_18;
	/*1c,4*/ undefined4 field_1c;
	/*20,4*/ LiveObject* ownerObj;
	/*24,4*/ ActStruct_14* actstruct_24;
	/*28,4*/ ResourceData* pool_m_next;
    /*2c*/
};

struct SharedTextureResource
{
	/*0,4*/ char* name;
	/*4,4*/ undefined4 field_4;
	/*8*/
};

// DAT_0076bd80
struct ResourceManager
{
	// DAT_0076bd80
	/*0000,50*/ ResourceData* pool_g_TABLE[20]; // PTR_0076bd80
	/*0050,4*/  ResourceData* pool_g_NEXT; // PTR_0076bdd0
	/*0054,4*/  ResourceData* pool_g_ROOT; // PTR_0076bdd4
	/*0058,24*/ char* Types_TABLE[9]; // PTR_0076bdd8
	/*007c,24*/ char* Extensions_TABLE[9]; // PTR_0076bdfc
	/*00a0,4*/  const char* CfgRootName; // "LegoRR" (exename)  // PTR_0076be20
	/*00a4,4*/  undefined4 DAT_0076be24; // DAT_0076be24
	/*00a8,4*/  undefined4 field_a8; // DAT_0076be28
	/*00ac,4*/  undefined4 field_ac; // referenced by addr to get last item of g_Textures_TABLE // DAT_0076be2c
	/*00b0,4*/  undefined4 field_b0; // DAT_0076be30
	/*00b4,1f40*/ SharedTextureResource Textures_TABLE[1000]; // PTR_0076be34
	/*1ff4,4*/  unsigned int Textures_COUNT; // DAT_0076dd74
	/*1ff8,4*/  undefined4* soundCallback; // PTR_0076dd78
	/*1ffc,4*/  void* soundCallback_VALUE; // DAT_0076dd7c
	/*2000,4*/  undefined4* drawCallback; // PTR_0076dd80
	/*2004,4*/  void* drawCallback_VALUE; // DAT_0076dd84
	/*2008,4*/  char* SharedTextures; // PTR_0076dd88
	/*200c,4*/  unsigned int SceneFogColor; // DAT_0076dd8c
	/*2010,4*/  unsigned int pool_g_COUNT; // DAT_0076dd90
	/*2014,4*/  unsigned int pool_g_INITFLAGS; // DAT_0076dd94
	/*2018*/
};

// <LegoRR.exe @0076bd80>
static ResourceManager g_Res;

// <LegoRR.exe @00534884>
static IDirect3DRMFrame3* g_SoundBufferFrames_TABLE[20];

//IDirectSound3DBuffer->SetMaxDistance(float flMaxDistance, DWORD dwApply)
//IDirectSound3DBuffer->SetMinDistance(float flMinDistance, DWORD dwApply)
//IDirectSound3DBuffer->SetMode(DWORD dwMode, DWORD dwApply)
// (dwMode = DS3DMODE_NORMAL (0x0), dwApply = TRUE (0x1))
//IDirectSound3DBuffer->SetMode(DWORD dwMode, DWORD dwApply)
// (dwMode = DS3DMODE_DISABLE (0x2), dwApply = TRUE (0x1))
//IDirectSound3DBuffer->SetPosition(float x, float y, float z, DWORD dwApply)
//IDirect3DRMFrame3->GetVisuals(this, DWORD* lpdwCount, IDirect3DRMVisualArray** lplpVisuals)
// (NOTE: lightalloy's implementation is missing an argument)
//IDirectSound3DListener->SetPosition(float x, float y, float z, DWORD dwApply)

// <LegoRR.exe @0047b460>
void __cdecl lego::res::Res_InitSoundBufferResource(IDirect3DRMFrame3 *rmFrame3,IDirectSound3DBuffer *ds3dBuffer)
{
	// IDirect3DRMFrame3 **ppIVar1;
	// int iVar2;
	
	ResourceAppData* appData = (ResourceAppData*)rmFrame3->GetAppData();
	SoundResource* soundRes = (SoundResource*)msvc::malloc(sizeof(SoundResource) /*0x14*/);
	// if (appData == nullptr) {
	// 	soundRes->previous = nullptr;
	// }
	// else {
	// 	soundRes->previous = appData->soundRes;
	// }
	soundRes->previous = (appData != nullptr ? appData->soundRes : nullptr);
	soundRes->sound3dBuffer = ds3dBuffer;
	soundRes->field_4 = 0;
	soundRes->field_8 = 0;
	soundRes->field_c = 0;
	Res_InitResourceAppData(rmFrame3, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, soundRes, nullptr);
	for (int i = 0; i < 20; i++) {
		if (g_SoundBufferFrames_TABLE[i] == nullptr)
			g_SoundBufferFrames_TABLE[i] = rmFrame3;
	}
	// iVar2 = 0;
	// ppIVar1 = globals::g_SoundBufferFrames_TABLE;
	// do {
	// 	if (*ppIVar1 == NULL) {
	// 		globals::g_SoundBufferFrames_TABLE[iVar2] = rmFrame3;
	// 		return;
	// 	}
	// 	ppIVar1 = ppIVar1 + 1;
	// 	iVar2 += 1;
	// } while (ppIVar1 < &DAT_005348d4);
	return;
}

// <LegoRR.exe @004729d0>
ResourceData* __cdecl InitResourceManager(const char* cfgRootName)
{
	std::memset(&g_Res, 0, sizeof(ResourceManager));
	
	std::memset(&g_Res.pool_g_TABLE, 0, sizeof(ResourceManager::pool_g_TABLE) /*80*/);

	g_Res.Types_TABLE[0] = "NULL";
	g_Res.Types_TABLE[1] = "MESH";
	g_Res.Types_TABLE[2] = "FRAME";
	g_Res.Types_TABLE[3] = "ANIM";
	g_Res.Types_TABLE[4] = "ACT";
	g_Res.Types_TABLE[5] = nullptr;
	//g_Res.Types_TABLE[5] = nullptr; // implicit, not assigned
	g_Res.Types_TABLE[7] = "LWS";
	g_Res.Types_TABLE[8] = "LWO";

	g_Res.Extensions_TABLE[0] = "";
	g_Res.Extensions_TABLE[1] = "x";
	g_Res.Extensions_TABLE[2] = "x";
	g_Res.Extensions_TABLE[3] = "x";
	g_Res.Extensions_TABLE[4] = "ae";
	g_Res.Extensions_TABLE[5] = nullptr;
	//g_Res.Extensions_TABLE[6] = nullptr; // implicit, not assigned
	//g_Res.Extensions_TABLE[7] = nullptr; // implicit, not assigned
	//g_Res.Extensions_TABLE[8] = nullptr; // implicit, not assigned

	g_Res.CfgRootName = cfgRootName;
	g_Res.pool_g_NEXT = nullptr;
	g_Res.pool_g_COUNT = 0;
	g_Res.pool_g_INITFLAGS = 0x1;
	g_Res.Textures_COUNT = 0;
	g_Res.SharedTextures = nullptr;
	g_Res.pool_g_Root = ResourcePool__Next(nullptr);
	g_Res.pool_g_Root->frame1->SetSortMode(D3DRMSORT_NONE /*1*/);
	return g_Res.pool_g_Root;
}


// <LegoRR.exe @00475400>
float10 __cdecl lego::res::Res_DoCallbacks(ResourceData* param_1, float param_2)
{
    float fVar1;
  IDirect3DRMFrame3 *rmFrame3;
  int iVar2;
  uint uVar3;
  uint uVar4;
  float10 fVar5;
  int *local_14;
  float local_10;
  
  local_14 = (int *)nullptr;
  local_10 = 0.0;
  if (resData->resType == RESOURCE_ACT) {
    rmFrame3 = Res_GetActFrameChildByName(resData, resData->subdata_c->name, 0);
    if ((rmFrame3 != nullptr) &&
       (local_14 = (int *)Res_GetAppData_Field1c(rmFrame3), (*(unsigned char *)&resData->flags_14 & 0x2) != 0))
    {
      iVar2 = Res_GetAppData_Field18(rmFrame3);
      if ((iVar2 != 0) &&
         ((globals::g_UnkSoundCallback != nullptr &&
          (((unsigned char)pool::globals::ReservedPool<ResourceData>__g_INITFLAGS & 0x40) != 0)))) {
        (*globals::g_UnkSoundCallback)(iVar2,resData,globals::g_UnkSoundCallback_VALUE);
      }
      resData->flags_14 = resData->flags_14 & 0xfffffffd;
    }
  }
  else {
    rmFrame3 = (IDirect3DRMFrame3 *)param_2;
    if (resData->resType == RESOURCE_ANIM) {
      local_14 = (int *)Res_GetAppData_Field1c(resData->frame2);
      rmFrame3 = resData->frame2;
    }
  }
  if (local_14 != (int *)nullptr) {
    uVar4 = resData->flags_14 & 8;
    fVar5 = FUN_00475650(resData);
    uVar3 = Res_GetAppData_Fieldc(rmFrame3);
    lego::res::Res_InitResourceAppData(rmFrame3,(ResourceData *)0x0,(char *)0x0,(char *)0x0,(int *)0x0,(int **)0x0,
                 (int **)&param_2,(int *)0x0,(int *)0x0,(int **)0x0);
    if (uVar3 != 0) {
      uVar3 -= 1;
      fVar1 = (float)(ulonglong)uVar3;
      if ((unsigned short)((unsigned short)(param_2 < fVar1) << 8 | (unsigned short)(param_2 == fVar1) << 0xe) == 0) {
        local_10 = param_2 - fVar1;
        uVar4 = 0;
      }
    }
    if (uVar4 == 0) {
      uVar4 = Res_GetAppData_Field20(rmFrame3);
      fVar1 = (float)(unsigned long long)uVar4;
      if ((((uVar3 != 1) &&
           (FUN_00489aa0(local_14, param_2, (float *)0x0), globals::g_UnkDrawCallback != nullptr))
          && (fVar1 != 0.0)) && (((float)fVar5 < fVar1 && (fVar1 <= param_2)))) {
        (*globals::g_UnkDrawCallback)(resData,globals::g_UnkDrawCallback_VALUE);
        return (float10)local_10;
      }
    }
    else {
      resData->flags_14 |= 0x20;
    }
  }
  return (float10)local_10;
}

// <LegoRR.exe @00476230>
void __cdecl lego::res::Res_InitResourceAppData(IDirect3DRMFrame3* rmFrame3, ResourceData* resData, void* actFrameRes, const char* filename, undefined4* param_5, char* frameName, float* param_7, float* param_8, void* param_9, SoundResource* soundRes, undefined4* param_11)
{
	ResourceAppData* appData = (ResourceAppData*)rmFrame3->GetAppData();
	if (appData == nullptr) {
		appData = (ResourceAppData*)std::malloc(sizeof(ResourceAppData) /*0x28*/);
		appData->actFrameRes = actFrameRes;
		appData->resData = resData;
		appData->filename = nullptr;
		appData->field_c = (param_5 != nullptr ? *param_5 : 0);
		// if (param_5 != nullptr)
		// 	appData->field_c = *param_5;
		// else
		// 	appData->field_c = 0;
			
		appData->frameName = frameName;

		appData->float_10 = (param_7 != nullptr ? *param_7 : 0.0f);
		appData->float_14 = (param_8 != nullptr ? *param_8 : 0.0f);
		// if (param_7 != nullptr)
		// 	appData->float_10 = *param_7;
		// else
		// 	appData->float_10 = 0.0f;
		// if (param_8 != nullptr)
		// 	appData->float_14 = *param_8;
		// else
		// 	appData->float_14 = 0.0f;
		
		appData->field_20 = (param_11 != nullptr ? *param_11 : 0);

		appData->sampleName = sampleName;
		appData->soundRes = soundRes;

		// *(undefined4*)((int)appData + 0x1c) = actFrameRes;
		// *(ResourceData*)((int)appData + 0x0) = resData;
		// *(char**)((int)appData + 0x4) = nullptr;
		// if (param_5 != nullptr)
		// 	*(undefined4*)((int)appData + 0xc) = *(undefined4*)param_5;
		// else
		// 	*(undefined4*)((int)appData + 0xc) = 0;

		// *(char*)((int)appData + 0x8) = frameName;

		// if (param_7 != nullptr)
		// 	*(float*)((int)appData + 0x10) = *(float*)param_7;
		// else
		// 	*(float*)((int)appData + 0x10) = 0.0f;
		// if (param_8 != nullptr)
		// 	*(float*)((int)appData + 0x14) = *(float*)param_8;
		// else
		// 	*(float*)((int)appData + 0x14) = 0.0f;

		// if (param_11 != nullptr)
		// 	*(undefined4*)((int)appData + 0x20) = *(undefined4*)param_11;
		// else
		// 	*(undefined4*)((int)appData + 0x20) = 0;

		// *(undefined4*)((int)appData + 0x18) = sampleName;
		// *(undefined4*)((int)appData + 0x24) = soundRes;

		/// NOTE: despite changes being made to appData after this call,
		///       it's still a pointer to that appData, so all is good.
		rmFrame3->SetAppData((DWORD)appData);
	}
	else {
		if (resData != nullptr) appData->resData = resData;

		if (actFrameRes != nullptr) appData->actFrameRes = actFrameRes;

		if (filename != nullptr && appData->filename != nullptr)
			std::free((void*)appData->filename);

		if (param_5 != nullptr)  appData->field_c   = *param_5;

		if (frameName != nullptr) appData->frameName  = frameName;

		if (param_7 != nullptr)  appData->float_10   = *param_7;
		if (param_8 != nullptr)  appData->float_14   = *param_8;

		if (sampleName != nullptr) appData->sampleName = sampleName;
		if (soundRes != nullptr) appData->soundRes = soundRes;

		if (param_11 != nullptr)  appData->field_20 = *param_11;


		// if (resData != nullptr)
		// 	*(ResourceData*)((int)appData + 0x0) = resData;

		// if (actFrameRes != nullptr)
		// 	*(undefined4*)((int)appData + 0x1c) = actFrameRes;

		// if (param_4 != nullptr && *(char**)((int)appData + 0x4) != nullptr)
		// 	std::free(*(char**)((int)appData + 0x4));

		// if (param_5 != nullptr)
		// 	*(undefined4*)((int)appData + 0xc) = *(undefined4*)param_5;

		// if (frameName != nullptr)
		// 	*(char*)((int)appData + 0x8) = frameName;

		// if (param_7 != nullptr)
		// 	*(float*)((int)appData + 0x10) = *(float*)param_7;
		// if (param_8 != nullptr)
		// 	*(float*)((int)appData + 0x14) = *(float*)param_8;

		// if (sampleName != nullptr)
		// 	*(undefined4*)((int)appData + 0x18) = sampleName;

		// if (soundRes != nullptr)
		// 	*(undefined4*)((int)appData + 0x24) = soundRes;

		// if (param_11 != nullptr)
		// 	*(undefined4*)((int)appData + 0x20) = *(undefined4*)param_11;
	}

	if (filename != nullptr) {
		appData->filename = _strdup(filename);

		// *(char*)((int)appData + 0x4) = _strdup(param_4);
	}
  
//   appData = (IDirect3DRMFrame3 **)(*rmFrame3->lpVtbl->GetAppData)((IUnknown *)rmFrame3);
//   if (appData == NULL) {
//     appData = (IDirect3DRMFrame3 **)std::malloc(0x28);
//     appData[7] = (IDirect3DRMFrame3 *)resData;
//     *appData = rmFrame3;
//     appData[1] = NULL;
//     if (param_4 == NULL) {
//       appData[3] = NULL;
//     }
//     else {
//       appData[3] = *(IDirect3DRMFrame3 **)param_4;
//     }
//     appData[2] = (IDirect3DRMFrame3 *)param_5;
//     if (frameName == NULL) {
//       appData[4] = NULL;
//     }
//     else {
//       appData[4] = (IDirect3DRMFrame3 *)*frameName;
//     }
//     if (param_7 == NULL) {
//       appData[5] = NULL;
//     }
//     else {
//       appData[5] = (IDirect3DRMFrame3 *)*param_7;
//     }
//     if (soundRes == NULL) {
//       appData[8] = NULL;
//     }
//     else {
//       appData[8] = (IDirect3DRMFrame3 *)*soundRes;
//     }
//     appData[6] = (IDirect3DRMFrame3 *)param_8;
//     appData[9] = (IDirect3DRMFrame3 *)param_9;
//     (*rmFrame3->lpVtbl->SetAppData)((IUnknown *)rmFrame3,(DWORD)appData);
//   }
//   else {
//     if (rmFrame3 != NULL) {
//       *appData = rmFrame3;
//     }
//     if (resData != NULL) {
//       appData[7] = (IDirect3DRMFrame3 *)resData;
//     }
//     if ((param_3 != NULL) && (appData[1] != NULL)) {
//       std::free(appData[1]);
//     }
//     if (param_4 != NULL) {
//       appData[3] = *(IDirect3DRMFrame3 **)param_4;
//     }
//     if (param_5 != NULL) {
//       appData[2] = (IDirect3DRMFrame3 *)param_5;
//     }
//     if (frameName != NULL) {
//       appData[4] = (IDirect3DRMFrame3 *)*frameName;
//     }
//     if (param_7 != NULL) {
//       appData[5] = (IDirect3DRMFrame3 *)*param_7;
//     }
//     if (param_8 != NULL) {
//       appData[6] = (IDirect3DRMFrame3 *)param_8;
//     }
//     if (param_9 != NULL) {
//       appData[9] = (IDirect3DRMFrame3 *)param_9;
//     }
//     if (soundRes != NULL) {
//       appData[8] = (IDirect3DRMFrame3 *)*soundRes;
//     }
//   }
//   if (param_3 != NULL) {
//     uVar3 = 0xffffffff;
//     pcVar6 = param_3;
//     do {
//       if (uVar3 == 0) break;
//       uVar3 -= 1;
//       cVar1 = *pcVar6;
//       pcVar6 = pcVar6 + 1;
//     } while (cVar1 != '\0');
//     pIVar2 = (IDirect3DRMFrame3 *)std::malloc(~uVar3);
//     uVar3 = 0xffffffff;
//     appData[1] = pIVar2;
//     do {
//       pcVar6 = param_3;
//       if (uVar3 == 0) break;
//       uVar3 -= 1;
//       pcVar6 = param_3 + 1;
//       cVar1 = *param_3;
//       param_3 = pcVar6;
//     } while (cVar1 != '\0');
//     uVar3 = ~uVar3;
//     ppIVar5 = (IDirect3DRMFrame3Vtbl **)(pcVar6 + -uVar3);
//     for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 -= 1) {
//       pIVar2->lpVtbl = *ppIVar5;
//       ppIVar5 = ppIVar5 + 1;
//       pIVar2 = pIVar2 + 1;
//     }
//     for (uVar3 &= 3; uVar3 != 0; uVar3 -= 1) {
//       *(undefined *)&pIVar2->lpVtbl = *(undefined *)ppIVar5;
//       ppIVar5 = (IDirect3DRMFrame3Vtbl **)((int)ppIVar5 + 1);
//       pIVar2 = (IDirect3DRMFrame3 *)((int)&pIVar2->lpVtbl + 1);
//     }
//   }
//   return;
}

// <LegoRR.exe @004763a0>
void __cdecl lego::res::Res_FreeResourceAppData(IDirect3DRMObject* rmFrame3)
{
	ResourceAppData* appData = (ResourceAppData*)rmFrame3->GetAppData();
	if (appData != nullptr) {
		if (appData->filename != nullptr)
			std::free((void*)appData->filename);
		}
		std::free(appData);
	}
	rmFrame3->SetAppData((DWORD)nullptr);
	return;

	// void* appData = (void*)rmFrame3->GetAppData();
	// if (appData != nullptr) {
	// 	if (*(void **)((int)appData + 4) != nullptr) {
	// 		std::free(*(void**)((int)appData + 0x4));
	// 	}
	// 	std::free(appData);
	// }
	// rmFrame3->SetAppData((DWORD)nullptr);
	// return;
}

// <LegoRR.exe @004763e0>
// undefined4 __cdecl lego::res::Res_GetAppData_Field0(IDirect3DRMObject* rmFrame3)
ResourceData* __cdecl lego::res::Res_GetAppData_Resource(IDirect3DRMObject* rmFrame3)
{
	ResourceAppData* appData = (ResourceAppData*)rmFrame3->GetAppData();
	if (appData != nullptr) {
		return appData->resData;
		// return *(undefined4*)((int)appData + 0x0);
	}
	return nullptr;
}
// <LegoRR.exe @00476400>
// void* __cdecl lego::res::Res_GetAppData_Field4(IDirect3DRMObject* rmFrame3)
const char* __cdecl lego::res::Res_GetAppData_Filename(IDirect3DRMObject* rmFrame3)
{
	ResourceAppData* appData = (ResourceAppData*)rmFrame3->GetAppData();
	if (appData != nullptr) {
		return appData->filename;
		// return *(void**)((int)appData + 0x4);
	}
	return nullptr;
}
// <LegoRR.exe @00476420>
// undefined4 __cdecl lego::res::Res_GetAppData_Field1c(IDirect3DRMObject* rmFrame3)
void* __cdecl lego::res::Res_GetAppData_ActFrame(IDirect3DRMObject* rmFrame3)
{
	ResourceAppData* appData = (ResourceAppData*)rmFrame3->GetAppData();
	if (appData != nullptr) {
		return appData->actFrameRes;
		// return *(undefined4*)((int)appData + 0x1c);
	}
	return nullptr;
}
// <LegoRR.exe @00476440>
// undefined4 __cdecl lego::res::Res_GetAppData_Fieldc(IDirect3DRMObject* rmFrame3)
undefined4 __cdecl lego::res::Res_GetAppData_Fieldc(IDirect3DRMObject* rmFrame3)
{
	ResourceAppData* appData = (ResourceAppData*)rmFrame3->GetAppData();
	if (appData != nullptr) {
		return appData->field_c;
		// return *(undefined4*)((int)appData + 0xc);
	}
	return 0;
}
// <LegoRR.exe @00476460>
// float10 __cdecl lego::res::Res_GetAppData_Float10(IDirect3DRMObject* rmFrame3)
float10 __cdecl lego::res::Res_GetAppData_Float10(IDirect3DRMObject* rmFrame3)
{
	ResourceAppData* appData = (ResourceAppData*)rmFrame3->GetAppData();
	if (appData != nullptr) {
		return appData->float_10;
		// return *(float*)((int)appData + 0x10);
	}
	return 0.0f;
}
// <LegoRR.exe @00476480>
// float10 __cdecl lego::res::Res_GetAppData_Float14(IDirect3DRMObject* rmFrame3)
float10 __cdecl lego::res::Res_GetAppData_Float14(IDirect3DRMObject* rmFrame3)
{
	ResourceAppData* appData = (ResourceAppData*)rmFrame3->GetAppData();
	if (appData != nullptr) {
		return appData->float_14;
		// return *(float*)((int)appData + 0x14);
	}
	return 0.0f;
}
// <LegoRR.exe @004764a0>
// undefined4 __cdecl lego::res::Res_GetAppData_Field18(IDirect3DRMObject* rmFrame3)
const char* __cdecl lego::res::Res_GetAppData_SampleName(IDirect3DRMObject* rmFrame3)
{
	ResourceAppData* appData = (ResourceAppData*)rmFrame3->GetAppData();
	if (appData != nullptr) {
		return appData->sampleName;
		// return *(undefined4*)((int)appData + 0x18);
	}
	return nullptr;
}
// <LegoRR.exe @004764c0>
// undefined4 __cdecl lego::res::Res_GetAppData_Field20(IDirect3DRMObject* rmFrame3)
undefined4 __cdecl lego::res::Res_GetAppData_Field20(IDirect3DRMObject* rmFrame3)
{
	ResourceAppData* appData = (ResourceAppData*)rmFrame3->GetAppData();
	if (appData != nullptr) {
		return appData->field_20;
		// return *(undefined4*)((int)appData + 0x20);
	}
	return 0;
}

// <LegoRR.exe @004764e0>
void __cdecl lego::res::Res_AddTransform3DFrame(IDirect3DRMFrame3* frame1, IDirect3DRMFrame3* frame2)
{
	//IDirect3DRMFrame3->GetParent(this, IDirect3DRMFrame3** lplpParent)
	IDirect3DRMFrame3* parentFrame;
	frame2->GetParent(&parentFrame);
	//IDirect3DRMFrame3->GetTransform(this, IDirect3DRMFrame3* lpRefFrame, Matrix4F** rmMatrix)
	// (this = frame2, lpRefFrame = GetParent)
	frame2->GetTransform(parentFrame, &matrix);
	//IDirect3DRMFrame3->Release(this)
	// (this = GetParent)
	parentFrame->Release();

	//IDirect3DRMFrame3->AddChild(this, IDirect3DRMFrame3*lpD3DRMFrameChild)
	// (this = frame1, lpChild = frame2)
	frame1->AddChild(frame2);

	//IDirect3DRMFrame3->AddTransform(this, TD3DRMCombineType rctCombine, Matrix4F* rmMatrix)
	// (this = frame2)
	frame2->AddTransform(D3DRMCOMBINE_REPLACE /*0*/, &matrix);
	return;
}

// <LegoRR.exe @00475fd0>
BOOL __cdecl FUN_00475fd0(ResourceData* resData, const char* filename, const char* frameName, undefined4* param_4, int param_5, int param_6, undefined4* param_7, BOOL isLWSFile, BOOL isLooping)
{
	HRESULT HVar1;
	undefined4 *puVar2;
	IDirect3DRMFrame3* local_208;
	unsigned int out_local_204; // local_204
	char buffer[512]; // local_200
	
	std::sprintf(buffer, "%s.%s", filename, g_Res.Extensions_TABLE[RESOURCE_ANIM /*3*/] /*"x"*/);


	IDirect3DRMFrame3* newFrame; // local_208
	if (globals::g_IDirect3DRM3->CreateFrame(resData->frame3, &newFrame) == 0) {
		lego::res::Res_SetActFrameName(newFrame, "%s_%s", "ActFrame", frameName);
		if (param_7 == nullptr) {
			puVar2 = FUN_00476880(buffer, newFrame, &out_local_204, isLWSFile, isLooping);
		}
		else {
			puVar2 = FUN_00489920(param_7, newFrame, &out_local_204);
		}
		lego::res::Res_InitResourceAppData(newFrame, resData, (char *)puVar2,filename,(int *)&local_204,NULL,NULL,
					(int *)&param_4,(int *)param_6,NULL);

		lego::res::Res_InitResourceAppData(local_208, resData, (char *)puVar2,filename,(int *)&local_204,NULL,NULL,
					(int *)&param_4,(int *)param_6,NULL);
		return true;
	}
	return false;
}
// <LegoRR.exe @00475fd0>
BOOL __cdecl FUN_00475fd0(ResourceData* resData, char* param_2, int* param_3, undefined4* param_4, int param_5, int param_6, undefined4* param_7, BOOL isLWSFile, BOOL isLooping)
{
  HRESULT HVar1;
  undefined4 *puVar2;
  IDirect3DRMFrame3 *local_208;
  uint local_204;
  char local_200[512];
  
  msvc::sprintf(local_200, "%s.%s", param_2, globals::g_ResourceExts_TABLE[3]);
  HVar1 = (*lego::globals::g_IDirect3DRM3->lpVtbl->CreateFrame)
                    (lego::globals::g_IDirect3DRM3,resData->frame3,&local_208);
  if (HVar1 == 0) {
    lego::res::Res_SetActFrameName(local_208,"%s_%s","ActFrame",param_3);
    if (param_7 == NULL) {
      puVar2 = FUN_00476880(local_200,local_208,&local_204,isLWSFile,isLooping);
    }
    else {
      puVar2 = FUN_00489920(param_7,local_208,&local_204);
    }
    lego::res::Res_InitResourceAppData
              (local_208,resData,(char *)puVar2,param_2,(int *)&local_204,NULL,NULL,
               (float *)&param_4,(int *)param_6,NULL,&param_5);
    return 1;
  }
  return 0;
}


// <LegoRR.exe @00476530>
void __cdecl lego::res::Res_SetActFrameName(IDirect3DRMFrame3* rmFrame3, const char* format, ...)
{
	int iVar1;
	int **ppiVar2;
	char buffer[1024];
	
	// char buffer[2048];
	std::va_list vl_1;
	va_start(vl_1, format);
	///TODO: does std:: version cause problems?
	int length = std::vsprintf(buffer, format, vl_1);
	va_end(vl_1);

	char* lpName = (char*)std::malloc(length + 1);
	
	///TODO: can va_list be re-used???
	std::va_list vl_2;
	va_start(vl_2, format);
	///TODO: does std:: version cause problems?
	std::vsprintf(lpName, format, vl_2);
	va_end(vl_2);
	rmFrame3->SetName(lpName);
	lego::res::Res_InitResourceAppData(rmFrame3, nullptr, nullptr, nullptr, nullptr, lpName, nullptr, nullptr, nullptr, nullptr, nullptr);
	return;

	// OutputDebugStringA(buffer);
	// //OutputDebugStringA("\n");
	// return result;
	// std::vsprintf
	// iVar1 = std::_sprintf_internal_1__0048e4a0(buffer, format, &stack0x0000000c);
	// ppiVar2 = (int **)std::malloc(iVar1 + 1);
	// std::_sprintf_internal_1__0048e4a0((char *)ppiVar2, format, &stack0x0000000c);
	// (*rmFrame3->lpVtbl->SetName)((IUnknown *)rmFrame3,(LPCSTR)ppiVar2);
	// lego::res::Res_InitResourceAppData(rmFrame3,NULL,NULL,NULL,NULL,ppiVar2,NULL,NULL,NULL,NULL);
	// return;
}

// <LegoRR.exe @00475ec0>
void __cdecl lego::res::Res_InitResourceSubdata(ResourceData* resData, char* name, IDirect3DRMLight* rmLight, IDirect3DRMMesh* rmMesh, Struct_34* unk_lwo)
{
	if (resData->subdata_c == nullptr) {
		resData->subdata_c = (ResourceSubdata*)std::malloc(sizeof(ResourceSubdata) /*0x10*/);
		resData->subdata_c->name       = name;
		resData->subdata_c->light      = rmLight;
		resData->subdata_c->mesh       = rmMesh;
		resData->subdata_c->struct34_c = unk_lwo;
	}
	else {
		if (name    != nullptr)  resData->subdata_c->name       = name;
		if (rmLight != nullptr)  resData->subdata_c->light      = rmLight;
		if (rmMesh  != nullptr)  resData->subdata_c->mesh       = rmMesh;
		if (unk_lwo != nullptr)  resData->subdata_c->struct34_c = unk_lwo;
	}
}

// <LegoRR.exe @00464ee0>
void __cdecl lego::unk::Lego_unkSoundCallback__00464ee0(char* param_1, undefined4* param_2, void* lpValue)
{
	BOOL BVar1;
	int out_local_2; // param_1
	
	BVar1 = res::Res_GetSFX(param_1, (int *)&out_local_2);
	if (BVar1 != 0) {
		FUN_00465310(param_2, out_local_2, 0, 1, (undefined4 *)nullptr);
	}
}

// <LegoRR.exe @00472be0>
void __cdecl lego::res::Res_SetSoundCallback(undefined4 callback,void *lpValue)
{
	globals::g_UnkSoundCallback = callback;
	globals::g_UnkSoundCallback_VALUE = lpValue;
	pool::globals::ReservedPool<ResourceData>__g_INITFLAGS =
		pool::globals::ReservedPool<ResourceData>__g_INITFLAGS | 0x40;
}

// <LegoRR.exe @00472c00>
ResourceData* __cdecl lego::res::GetReservedPool<ResourceData>__g_ROOT(void)
{
  	return g_Res.pool_g_ROOT;
}


// <LegoRR.exe @00475bc0>
void __cdecl Res_GetResourceFramePairs(ResourceData* resData1, ResourceData* opt_resData2, IDirect3DRMFrame3** out_frame1, IDirect3DRMFrame3** out_frame2)
{
  *out_frame1 = resData1->frame1;
  if (opt_resData2 == nullptr) {
    *out_frame2 = pool::globals::ReservedPool<ResourceData>__g_ROOT->frame1;
  }
  else {
  	*out_frame2 = opt_resData2->frame1;
  }
}

// <LegoRR.exe @004756f0>
void __cdecl Res_SetFramePosition(ResourceData* resData1, ResourceData* opt_resData2, float x, float y, float z)
{
  IDirect3DRMFrame3* frame1, frame2;
  Res_GetResourceFramePairs(resData1, opt_resData2, &frame1, &frame2);

  //IDirect3DRMFrame3->SetPosition(this, IDirect3DRMFrame3* lpRef, float rvX, float rvY, float rvZ)
  frame1->SetPosition(frame2, x, y, z);
}

// <LegoRR.exe @00475730>
void __cdecl Res_SetFrameOrientation(ResourceData* resData1, ResourceData* opt_resData2, float x, float y, float z, float ux, float uy, float uz)
{
  IDirect3DRMFrame3* frame1, frame2;
  Res_GetResourceFramePairs(resData1, opt_resData2, &frame1, &frame2);

  //IDirect3DRMFrame3->SetOrientation(this, IDirect3DRMFrame3* lpRef, float rvDx, float rvDy, float rvDz, float rvUx, float rvUy, float rvUz)
  frame1->SetOrientation(frame2, dx, dy, dz, ux, uy, uz);
}

// <LegoRR.exe @00475780>
void __cdecl Res_GetFramePosition(ResourceData* resData1, ResourceData* opt_resData2, Vector3F* out_position)
{
  IDirect3DRMFrame3* frame1, frame2;
  Res_GetResourceFramePairs(resData1, opt_resData2, &frame1, &frame2);

  //IDirect3DRMFrame3->GetPosition(this, IDirect3DRMFrame3* lpRef, Vector3F* lprvPos)
  frame1->GetPosition(frame2, (D3DVECTOR*)out_position);
}

// <LegoRR.exe @004757c0>
void __cdecl Res_GetFrameOrientation(ResourceData* resData1, ResourceData* opt_resData2, Vector3F* out_dvector, Vector3F* out_uvector)
{
  IDirect3DRMFrame3* frame1, frame2;
  Res_GetResourceFramePairs(resData1, opt_resData2, &frame1, &frame2);

  Vector3F dvector, uvector;
  //IDirect3DRMFrame3->GetOrientation(this, IDirect3DRMFrame3* lpRef, Vector3F* lprvDir, Vector3F* lprvUp)
  frame1->GetOrientation(frame2, (D3DVECTOR*)&dvector, (D3DVECTOR*)&uvector);
  if (out_dvector != nullptr) {
    out_dvector->x = dvector->x;
    out_dvector->y = dvector->y;
    out_dvector->z = dvector->z;
  }
  if (out_uvector != nullptr) {
    out_uvector->x = uvector->x;
    out_uvector->y = uvector->y;
    out_uvector->z = uvector->z;
  }
}

// <LegoRR.exe @00475840>
void __cdecl Res_AddFrameRotation(ResourceData* resData, D3DRMCombineType combineType, float x, float y, float z, float theta)
{
  //enum D3DRMCombineType
  //  D3DRMCOMBINE_REPLACE = 0,
  //  D3DRMCOMBINE_BEFORE  = 1,
  //  D3DRMCOMBINE_AFTER   = 2,

  //IDirect3DRMFrame3->AddRotation(this, D3DRMCombineType rctCombine, float rvX, float rvY, float rvZ, float rvTheta)
  resData->frame1->AddRotation(combineType, x, y, z, theta);
}

//enum D3DRMCombineType
//  D3DRMCOMBINE_REPLACE = 0,
//  D3DRMCOMBINE_BEFORE  = 1,
//  D3DRMCOMBINE_AFTER   = 2,

//IDirect3DRMFrame3->AddScale(this, D3DRMCombineType rctCombine, float rvX, float rvY, float rvZ)

// <LegoRR.exe @00475870>
void __cdecl lego::res::Res_AddFrameScale(ResourceData* resData, D3DRMCombineType combineType, float x,float y,float z)
{
  //enum D3DRMCombineType
  //  D3DRMCOMBINE_REPLACE = 0,
  //  D3DRMCOMBINE_BEFORE  = 1,
  //  D3DRMCOMBINE_AFTER   = 2,

  //IDirect3DRMFrame3->AddScale(this, D3DRMCombineType rctCombine, float rvX, float rvY, float rvZ)
  resData->frame1->AddScale(combineType, x, y, z);
}

// <LegoRR.exe @004758a0>
void __cdecl Res_AddFrameTranslation(ResourceData* resData, D3DRMCombineType combineType, float x, float y, float z)
{
  //enum D3DRMCombineType
  //  D3DRMCOMBINE_REPLACE = 0,
  //  D3DRMCOMBINE_BEFORE  = 1,
  //  D3DRMCOMBINE_AFTER   = 2,

  //IDirect3DRMFrame3->AddTranslation(this, D3DRMCombineType rctCombine, float rvX, float rvY, float rvZ)
  resData->frame1->AddTranslation(combineType, x, y, z);
}

// <LegoRR.exe @004758d0>
void __cdecl Res_IdentityFrameTransform(ResourceData* resData)
{
  // <https://en.wikipedia.org/wiki/Identity_matrix>
  Matrix4F identity = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f },
  };
  // Matrix4F identity;
  // identity.values[0][0] = 1.0;
  // identity.values[1][0] = 0.0;
  // identity.values[2][0] = 0.0;
  // identity.values[3][0] = 0.0;
  // identity.values[0][1] = 0.0;
  // identity.values[1][1] = 1.0;
  // identity.values[2][1] = 0.0;
  // identity.values[3][1] = 0.0;
  // identity.values[0][2] = 0.0;
  // identity.values[1][2] = 0.0;
  // identity.values[2][2] = 1.0;
  // identity.values[3][2] = 0.0;
  // identity.values[0][3] = 0.0;
  // identity.values[1][3] = 0.0;
  // identity.values[2][3] = 0.0;
  // identity.values[3][3] = 1.0;
  Res_AddFrameTransform(resData, D3DRMCOMBINE_REPLACE /*0*/, &identity);
}

// <LegoRR.exe @00475970>
void __cdecl Res_AddFrameTransform(ResourceData* resData, D3DRMCombineType combineType, Matrix4F* matrix)
{
  //IDirect3DRMFrame3->AddTransform(this, D3DRMCombineType rctCombine, D3DRMMatrix4D* rmMatrix)
  resData->frame1->AddTransform(combineType, matrix);
}


// type
//   TD3DRMLoadOptions = DWORD;

// const
//   D3DRMLOAD_FROMFILE  = $00;
//   D3DRMLOAD_FROMRESOURCE = $01;
//   D3DRMLOAD_FROMMEMORY = $02;
//   D3DRMLOAD_FROMSTREAM = $04;
//   D3DRMLOAD_FROMURL = $08;

//   D3DRMLOAD_BYNAME = $10;
//   D3DRMLOAD_BYPOSITION = $20;
//   D3DRMLOAD_BYGUID = $40;
//   D3DRMLOAD_FIRST = $80;

//   D3DRMLOAD_INSTANCEBYREFERENCE = $100;
//   D3DRMLOAD_INSTANCEBYCOPYING = $200;

//   D3DRMLOAD_ASYNCHRONOUS = $400;



//IDirect3DRMFrame3->GetChildren(this, IDirect3DRMFrameArray* lplpChildren)

//IDirect3DRM3->CreateLightRGB(this, TD3DRMLightType ltLightType, float vRed, float vGreen, float vBlue, IDirect3DRMLight** lplpD3DRMLight)
//IDirect3DRM3->CreateMeshBuilder(this, IDirect3DRMMeshBuilder3** lplpD3DRMMeshBuilder)
//IDirect3DRMMeshBuilder3->Load(this, void* lpvObjSource, void* lpvObjID, TD3DRMLoadOptions d3drmLOFlags, TD3DRMLoadTexture3Callback d3drmLoadTextureProc, void* lpvArg)

//IDirect3DRMMeshBuilder3->CreateMesh(this, IDirect3DRMMesh** lplpD3DRMMesh)
//IDirect3DRMFrame3->AddVisual(this, IDirect3DRMVisual* lpD3DRMVisual)
//IDirect3DRM3->CreateUserVisual(this, TD3DRMUserVisualCallback fn, void* lpArg, IDirect3DRMUserVisual** lplpD3DRMUV)
//IDirect3DDevice3->GetTransform(this, TD3DTransformStateType dtstTransformStateType, TD3DMatrix* lpD3DMatrix)
//IDirect3DRMViewport->QueryInterface(this, IID_IDirect3DRMViewport2, IDirect3DRMViewport2** lplpOut)
//IDirect3DRMFrame3->GetScene(this, IDirect3DRMFrame3** lplpRoot)
//IDirect3DRMFrame3->LookAt(this, IDirect3DRMFrame3* lpTarget, IDirect3DRMFrame3* lpRef, TD3DRMFrameConstraint rfcConstraint)
//IDirect3DRMViewport2->GetCamera(this, IDirect3DRMFrame3** lplpCamera)
//IDirect3DRMFrame3->GetParent(this, IDirect3DRMFrame3** lplpParent)
//HRESULT GetParent(IDirect3DRMFrame3* this, IDirect3DRMFrame3** lplpParent)
//IDirect3DRMFrame3->DeleteChild(this, IDirect3DRMFrame3* lpChild)
//IDirect3DRMFrame3->GetTransform(this, IDirect3DRMFrame3* lpRefFrame, Matrix4F** rmMatrix)
//IDirect3DRMUserVisual->SetAppData(this, Struct_34* ulData)
//IDirect3DRMAnimationSet2->Load(this, void* lpvObjSource, void* lpvObjID, TD3DRMLoadOptions drd3mLOFlags, TD3DRMLoadTexture3Callback d3drmLoadTextureProc, void* lpArgLTP, IDirect3DRMFrame3* lpParentFrame)
//IDirect3DRM3->CreateAnimationSet(this, IDirect3DRMAnimationSet2** lplpD3DRMAnimationSet)
//IDirect3DRM3->CreateFrame(this, IDirect3DRMFrame3* lpD3DRMFrame, IDirect3DRMFrame3** lplpD3DRMFrame)
//HRESULT CreateFrame(IDirect3DRM3* this, IDirect3DRMFrame3* lpD3DRMFrame, IDirect3DRMFrame3** lplpD3DRMFrame)
//IDirect3DRMAnimationSet2->SetTime(this, float rvTime)
//IDirect3DRMMesh->SetGroupMapping(int id, D3DRMMapping value)
//    D3DRMMAP_WRAPU        = 0x1,
//    D3DRMMAP_WRAPV        = 0x2,
//    D3DRMMAP_PERSPCORRECT = 0x4,
//IDirect3DRMAnimationSet2->SetTime(IDirect3DRMAnimationSet2* this, float rvTime)
//HRESULT func(IDirect3DRMFrame3 *, IDirect3DRMFrame3 *, Matrix4F*)
//HRESULT func(IDirect3DRMFrame3* this, IDirect3DRMFrame3** lplpParent)
//HRESULT func(IDirect3DRMFrame3 *, D3DRMCombineType, Matrix4F *)
//IDirect3DRMFrame->QueryInterface(this, IID_IDirect3DRMFrame3, IDirect3DRMFrame3** lplpOut)
//IDirect3DRMFrame->Release(this)

//IDirect3DRMFrame3->QueryInterface(this, IID_IDirect3DRMFrame, IDirect3DRMFrame** lplpOut)

//HRESULT QueryInterface(IUnknown* this, IID_IDirect3DRMFrame3, IDirect3DRMFrame3** lplpOut)
//IDirect3DRMFrame3->GetName(this, DWORD* lpdwSize, LPSTR lpName)
//IDirect3DRMFrame3->SetName(this, LPCSTR lpName)
//HRESULT GetTransform(IDirect3DRMFrame3* this, IDirect3DRMFrame3* lpRefFrame, Matrix4F** rmMatrix)
//IDirect3DRMFrame3->AddTransform(this, TD3DRMCombineType rctCombine, Matrix4F* rmMatrix)

//HRESULT AddTransform(IDirect3DRMFrame3* this, D3DRMCombineType rctCombine, Matrix4F* rmMatrix)
//IDirect3DRMFrame3->GetChildren(this, IDirect3DRMFrameArray** lplpChildren)
//HRESULT GetChildren(IDirect3DRMFrame3* this, IDirect3DRMFrameArray** lplpChildren)
//uint GetSize(IDirect3DRMFrameArray* this)
//HRESULT GetElement(IDirect3DRMFrameArray* this, DWORD index, IDirect3DRMFrame** lplpD3DRMFrame)
//IDirect3DRMFrameArray->GetElement(this, DWORD index, IDirect3DRMFrame** lplpD3DRMFrame)
//IDirect3DRMLight->SetEnableFrame(this, IDirect3DRMFrame* lpEnableFrame);

//HRESULT SetEnableFrame(IDirect3DRMLight* this, IDirect3DRMFrame* lpEnableFrame);

//HRESULT GetVisuals(IDirect3DRMFrame3* , DWORD* lpdwCount, undefined4)


int (__cdecl* TD3DRMUserVisualCallback)(IDirect3DRMUserVisual* lpD3DRMUV, void* lpArg, D3DRMUserVisualReason lpD3DRMUVreason, IDirect3DRMDevice* lpD3DRMDev, IDirect3DRMViewport* lpD3DRMview);

  TD3DRMUserVisualCallback = function (lpD3DRMUV: IDirect3DRMUserVisual;
      lpArg: Pointer; lpD3DRMUVreason: TD3DRMUserVisualReason;
      : IDirect3DRMDevice* lpD3DRMDev, IDirect3DRMViewport* lpD3DRMview
      ) : Integer; cdecl;
  // TD3DRMLoadTextureCallback = function (tex_name: PAnsiChar; lpArg: Pointer;
  //     out lpD3DRMTex: IDirect3DRMTexture) : HResult; cdecl;
  TD3DRMLoadTexture3Callback = function (tex_name: PAnsiChar; lpArg: Pointer;
      out lpD3DRMTex: IDirect3DRMTexture3) : HResult; cdecl;
  // TD3DRMLoadCallback = procedure (lpObject: IDirect3DRMObject;
  //     const ObjectGuid: TGUID; lpArg: Pointer); cdecl;

/* WARNING: Could not reconcile some variable overlaps */

// <LegoRR.exe @00476100>
undefined ** __cdecl Res_GetActFrameChildByName(ResourceData* resData, const char* frameName, BOOL use3rdFrame)
{
  int *piVar1;
  int iVar2;
  IDirect3DRMFrameArray *pIVar3;
  char *_Str1;
  int *unaff_EBX;
  int *unaff_EBP;
  code **ppcVar4;
  code **unaff_EDI;
  IDirect3DRMFrameArray *pIVar5;
  int *piStack572;
  IDirect3DRMFrameArray *pIStack568;
  undefined *puStack564;
  int *piStack560;
  IDirect3DRMFrame3 *pIStack556;
  IDirect3DRMFrameArray **ppIStack552;
  code **ppcVar6;

  IDirect3DRMFrame3* rmFrame3;
  IDirect3DRMFrameArray* rmArray;
  IDirect3DRMFrame* rmFrameBase;
  unsigned int dwNameSize;
  unsigned int dwSize;
  char nameBuffer[512];
  
  IDirect3DRMFrame3* srcFrame = (!use3rdFrame ? resData->frame2 : resData->frame3);

  IDirect3DRMFrame3* resultFrame = nullptr;

  if (srcFrame->GetChildren(&rmArray) == 0) {
    unsigned int dwArraySize = rmArray->GetSize();
    for (unsigned int i = 0; i < dwArraySize; i++) {
      rmArray->GetElement(i, &rmFrameBase);
      // cast up to IDirect3DRMFrame3* and release base IDirect3DRMFrame*
      rmFrameBase->QueryInterface(IID_IDirect3DRMFrame3, (void**)&rmFrame3);
      rmFrameBase->Release();

      unsigned int dwNameSize = 0; // dummy initialize
      rmFrame3->GetName(&dwNameSize, nullptr);
      if (dwNameSize != 0) {
        char* lpName = (char*)std::malloc(dwNameSize);
        rmFrame3->GetName(&dwNameSize, lpName);

        /// OPTIMIZE: this buffer should only have to be prepared once
        std::sprintf(nameBuffer, "%s_%s", "ActFrame", frameName);
        if (_stricmp(lpName, nameBuffer) == 0) {
          resultFrame = rmFrame3;
        }

        std::free(lpName);
      }
      /// CRITICAL: Don't release the frame if we're returning it... WTF
      rmFrame3->Release();
    }
    rmArray->Release();
  }
  return resultFrame;

  ppcVar4 = (code **)0x0;
  if (use3rdFrame == 0) {
    pIStack556 = resData->frame2;
  }
  else {
    pIStack556 = resData->frame3;
  }
  ppIStack552 = &rmArray;
                    /* IDirect3DRMFrame3->GetChildren(this, IDirect3DRMFrameArray** lplpChildren) */
  piStack560 = (int *)0x476135;
  piVar1 = unaff_EBX;
  iVar2 = (*(code *)pIStack556->lpVtbl->GetChildren)();
  piStack560 = piVar1;
  if (iVar2 == 0) {
                    /* DWORD IDirect3DRMFrameArray->GetSize(this) */
    puStack564 = (undefined *)0x476147;
    pIVar3 = (IDirect3DRMFrameArray *)(**(code **)(*piStack560 + 0xc))();
    pIVar5 = (IDirect3DRMFrameArray *)0x0;
    piStack572 = unaff_EBP;
    rmArray = pIVar3;
    if (pIVar3 != (IDirect3DRMFrameArray *)0x0) {
      do {
        puStack564 = &stack0xfffffde8;
                    /* IDirect3DRMFrameArray->GetElement(this, DWORD index, IDirect3DRMFrame** lplpD3DRMFrame) */
        pIStack568 = pIVar5;
        unaff_EBP = piStack572;
        (**(code **)(*piStack572 + 0x10))();
                    /* IDirect3DRMFrame->QueryInterface(this, IID_IDirect3DRMFrame3,
                       IDirect3DRMFrame3** lplpOut) */
        ppcVar6 = unaff_EDI;
        (**(code **)*unaff_EDI)(unaff_EDI,&directx::iid::IID_IDirect3DRMFrame3,&pIStack556);
                    /* IDirect3DRMFrame->Release(this) */
        (**(code **)(*piStack560 + 8))(piStack560);
                    /* IDirect3DRMFrame3->GetName(this, DWORD* lpdwSize, LPSTR lpName) */
        (**(code **)(*piStack572 + 0x24))(piStack572,&piStack560,0);
        if (piStack572 != (int *)0x0) {
          _Str1 = (char *)std::malloc((int)piStack572 + 1);
          (**(code **)(*unaff_EDI + 0x24))(unaff_EDI,&piStack572,_Str1);
          std::sprintf((char *)&puStack564,"%s_%s","ActFrame",nameBuffer._508_4_);
          iVar2 = _stricmp(_Str1,(char *)&puStack564);
          if (iVar2 == 0) {
            ppcVar4 = unaff_EDI;
          }
          std::free(_Str1);
          pIVar3 = pIStack568;
        }
                    /* IDirect3DRMFrame3->Release(this) */
        (**(code **)(*unaff_EDI + 8))(unaff_EDI);
      } while ((ppcVar4 == (code **)0x0) &&
              (pIVar5 = (IDirect3DRMFrameArray *)((int)&pIVar5->lpVtbl + 1), unaff_EDI = ppcVar6,
              piStack572 = unaff_EBP, pIVar5 < pIVar3));
    }
                    /* IDirect3DRMFrameArray->Release(this) */
    pIStack568 = (IDirect3DRMFrameArray *)0x47621c;
    (**(code **)(*unaff_EBP + 8))();
  }
  return ppcVar4;
}



// <LegoRR.exe @00476b10>
IDirect3DRMMesh* __cdecl Res_CreateMesh(void* fileData, unsigned int fileSize, const char* filename, IDirect3DRMFrame3* rmFrame3, BOOL param_5)
{
  int iVar1;
  int *piVar2;
  IDirect3DRM3 *pIStack24;
  void **ppvStack20;
  undefined local_10 [8];
  void *local_8;
  int *local_4;

  unsigned int local_4 = fileSize;
  void* local_8 = fileData;
  unsigned int local_c = 0x0;
  const char* local_10 = filename;

  IDirect3DRMMeshBuilder3* rmMeshBuilder3; // fileData
  IDirect3DRMMesh* rmMesh; // fileSize



  if (globals::g_IDirect3DRM3->CreateMeshBuilder(&rmMeshBuilder3) == 0) {
    unsigned int local_c = 0x0;
    if (param_5) {
      local_c = 0x1;
    }
    if (rmMeshBuilder3->Load(fileData, nullptr, D3DRMLOAD_FROMMEMORY /*0x2*/, FUN_00476bc0, (void*)filename) == 0) {
      rmMeshBuilder3->CreateMesh(&rmMesh);
      rmMeshBuilder3->Release();
      if (rmFrame3->AddVisual(rmMesh) == 0) {
        return rmMesh;
      }
    }
    /// CRITICAL: releasing IDirect3DRMMeshBuilder3 twice (on failure)
    rmMeshBuilder3->Release();
  }
  return nullptr;
  
  local_8 = fileData;
  local_4 = (int *)fileSize;
  ppvStack20 = &fileData;
  pIStack24 = globals::g_IDirect3DRM3;
                    /* IDirect3DRM3->CreateMeshBuilder(this, IDirect3DRMMeshBuilder3**
                       lplpD3DRMMeshBuilder) */
  ppvStack20 = (void **)(*(code *)globals::g_IDirect3DRM3->lpVtbl->CreateMeshBuilder)();
  if (ppvStack20 == (void **)0x0) {
    pIStack24 = (IDirect3DRM3 *)fileData;
    if (filename != (char *)0x0) {
      ppvStack20 = (void **)0x1;
    }
    piVar2 = (int *)0x2;
                    /* IDirect3DRMMeshBuilder3->Load(this, void* lpvObjSource, void* lpvObjID,
                       TD3DRMLoadOptions d3drmLOFlags, TD3DRMLoadTexture3Callback
                       d3drmLoadTextureProc, void* lpvArg) */
    iVar1 = (**(code **)(*local_4 + 0x2c))(local_4,local_10,0,2,FUN_00476bc0);
    if (iVar1 == 0) {
                    /* IDirect3DRMMeshBuilder3->CreateMesh(this, IDirect3DRMMesh** lplpD3DRMMesh) */
      (*(code *)pIStack24[0x30].lpVtbl)(&pIStack24,&pIStack24);
      (**(code **)(*piVar2 + 8))(piVar2);
                    /* IDirect3DRMFrame3->AddVisual(this, IDirect3DRMVisual* lpD3DRMVisual) */
      iVar1 = (*(code *)pIStack24[0x12].lpVtbl)(&pIStack24,piVar2);
      if (iVar1 == 0) {
        return (int *)pIStack24;
      }
    }
    (*(code *)pIStack24[2].lpVtbl)(&pIStack24);
  }
  return (int *)0x0;
}


// <LegoRR.exe @00482ab0>
BOOL __cdecl Res_D3DRMUserVisualCallback(IDirect3DRMUserVisual* lpD3DRMUV, undefined** lpArg, D3DRMUserVisualReason lpD3DRMUVreason, IDirect3DRMDevice* lpD3DRMDev, IDirect3DRMViewport* lpD3DRMview);


// <LegoRR.exe @00480b30>
undefined4* __cdecl Res_UnkCreateUserVisual(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5)
{
  int **ppiVar1;
  undefined4 *puVar2;
  int *unaff_EDI;
  int *piVar3;
  
  puVar2 = pool::ReservedPool<Struct_34>__Next();
  GetReservedPool<ResourceData>__g_ROOT();
  ppiVar1 = (int **)(puVar2 + 3);
                    /* IDirect3DRM3->CreateUserVisual(this, TD3DRMUserVisualCallback fn, void*
                       lpArg, IDirect3DRMUserVisual** lplpD3DRMUV) */
  globals::g_IDirect3DRM3->CreateUserVisual(Res_D3DRMUserVisualCallback, );
  piVar3 = unaff_EDI;
  (**(code **)(*unaff_EDI + 0x48))(unaff_EDI,*ppiVar1);
  (**(code **)(**ppiVar1 + 0x18))(*ppiVar1,puVar2);
  puVar2[5] = ppiVar1;
  puVar2[10] = unaff_EDI;
  puVar2[4] = Res_D3DRMUserVisualCallback;
  puVar2[6] = puVar2;
  if (piVar3 == (int *)0x1) {
    puVar2[8] = 1;
    puVar2[0xb] = puVar2[0xb] | 2;
    return puVar2;
  }
  if (piVar3 == (int *)0x2) {
    puVar2[0xb] = puVar2[0xb] | 4;
  }
  puVar2[8] = 1;
  return puVar2;
}