

// <https://kb.rockraidersunited.com/Command-line_parameters>
enum CmdlineFlags : unsigned int
{
	CMD_NONE            = 0,

	CMD_UNK_1           = 0x1,
	CMD_FULLSCREEN      = 0x2,       // set when booting the game into fullscreen
	//CMD_UNK_4           = 0x4,
	CMD_MIPMAP          = 0x8,       // set by FUN_004785f0 if both Filter and MipMap config options are TRUE

	CMD_UNK_10          = 0x10,
	CMD_NM              = 0x20,      // -nm  (no management?, disables texture management for Voodoo2-based cards)
	CMD_BEST            = 0x40,      // -best
	CMD_UNK_80          = 0x80,

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
DEFINE_ENUM_FLAG_OPERATORS(CmdlineFlags)

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
	GAME1_NONE                 = 0,

	GAME1_UNK_FLAGS_GROUP_A = 0x80c20, // unconditionally set in Game_loadLegoCFG

	//GAME1_UNK_1                = 0x1,
	GAME1_UNK_2                = 0x2, // see Game_unkGameLoop?_FUN_00426450
	GAME1_UNK_4                = 0x4, // Set when loading level? (used in & ~mask)
	GAME1_MUSICON              = 0x8, // see Main_GameUpdate
	
	GAME1_SOUNDON              = 0x10,     // Main::SoundOn
	//GAME1_UNK_20               = 0x20,
	GAME1_FRAMERATEMONITOR     = 0x40, // (LCtrl+F) Debug key that enables Frame rate monitor
	GAME1_MEMORYMONITOR        = 0x80, // (LCtrl+G) Debug key that enables Memory monitor

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
	GAME1_PAUSED               = 0x2000000, // see Main_GameUpdate
	GAME1_STREAMNERPSSPEACH    = 0x4000000, // Main::StreamNERPSSpeach
	GAME1_UNK_8000000          = 0x8000000, // see Game_unkGameLoop?_FUN_00426450

	GAME1_UNK_10000000         = 0x10000000, // see Game_unkGameLoop?_FUN_00426450
	GAME1_UNK_20000000         = 0x20000000, // see Main_GameUpdate
	GAME1_DEBUG_CTRLENTER      = 0x40000000, // (LCtrl+Enter)
	GAME1_UNK_80000000         = 0x80000000, // see Main_GameUpdate (used as & ~mask)
};
DEFINE_ENUM_FLAG_OPERATORS(GameFlags1)

// Flags at <LegoRR.exe @00557ed0>
enum GameFlags2 : unsigned int
{
	GAME2_NONE                = 0,

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
DEFINE_ENUM_FLAG_OPERATORS(GameFlags2)

// Flags at <LegoRR.exe @00557ed4>
enum GameFlags3 : unsigned int
{
	GAME3_NONE         = 0,

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
DEFINE_ENUM_FLAG_OPERATORS(GameFlags3)




EBP <- EAX <- dwRBitMask
ESI <- dwGBitMask
EDI <- dwBBitMask

EBX <- countBits(dwRBitMask)
local_90 <- countBits(dwGBitMask)
local_8c <- countBits(dwBBitMask)

EBP <- firstBit(dwRBitMask)
local_88 <- firstBit(dwGBitMask)
EAX <- firstBit(dwBBitMask)


DL <- countBits(dwGBitMask)


((out_green & 0xff) >> (8 - bits_green)) << first_green

((out_blue  & 0xff) >> (8 - bits_blue )) << first_blue
((out_red   & 0xff) >> (8 - bits_red  ))
(8 - (out_green & 0xff)) << 8

(out_blue & 0xff)

    iVar4 = util::countBits(s.ddpfPixelFormat.dwRBitMask);
    iVar2 = util::countBits(s.ddpfPixelFormat.dwGBitMask);
    cVar8 = (char)iVar2;
    iVar2 = util::countBits(s.ddpfPixelFormat.dwBBitMask);
    cVar9 = (char)iVar2;
    iVar2 = util::firstBit(s.ddpfPixelFormat.dwRBitMask);
    iVar3 = util::firstBit(s.ddpfPixelFormat.dwGBitMask);
    bVar1 = (byte)iVar3;
    iVar3 = util::firstBit(s.ddpfPixelFormat.dwBBitMask);

	#define count_red   iVar4
	#define count_green cVar8
	#define count_blue  cVar9

	#define first_red   iVar2
	#define first_green bVar1
	#define first_blue  iVar3

DWORD dwRBitMask = surface.ddpfPixelFormat.dwRBitMask;
DWORD dwGBitMask = surface.ddpfPixelFormat.dwGBitMask;
DWORD dwBBitMask = surface.ddpfPixelFormat.dwBBitMask;

// maximum 8-bits per channel
// lowers resolution
uVar5 =
	((out_green & 0xff) >> (8U - countBits(dwGBitMask))) << firstBit(dwGBitMask) |
	((out_blue  & 0xff) >> (8U - countBits(dwRBitMask))) << firstBit(dwRBitMask) |
	((out_red   & 0xff) >> (8U - countBits(dwBBitMask))) << firstBit(dwBBitMask);

uVar5 =
	((out_green & 0xff) >> (8U - count_green)) << first_green |
	((out_blue  & 0xff) >> (8U - count_red))   << first_red   |
	((out_red   & 0xff) >> (8U - count_blue))  << first_blue;

uVar5 =
	((_out_blue & 0xff) >> (8U - count_green & 0x1f)) << (first_green & 0x1f) |
		(((unsigned int)pDVar7 & 0xff) >> (8U - count_red & 0x1f)) << (first_red & 0x1f) |
		((unaff_ESI & 0xff) >> (8U - count_blue & 0x1f)) << (first_blue & 0x1f);

    uVar5 = ((_out_blue & 0xff) >> (8U - cVar8 & 0x1f)) << (bVar1 & 0x1f) |
            (((uint)pDVar7 & 0xff) >> (8U - (char)iVar4 & 0x1f)) << ((byte)iVar2 & 0x1f) |
            ((unaff_ESI & 0xff) >> (8U - cVar9 & 0x1f)) << ((byte)iVar3 & 0x1f);


struct ImageBMP // Struct_20
{
	/*00,4*/ IDirectDrawSurface4* ddSurface;
	/*04,4*/ int width;
	/*08,4*/ int height;
	/*0c,4*/ unsigned int firstColor24;
	/*10,4*/ unsigned int lastColor24;
	/*14,4*/ unsigned int firstColor;
	/*18,4*/ unsigned int field_18; // (init: 0)
	/*1c,4*/ ReservedPool<ImageBMP>* m_next;
	/*20*/
};
struct ImageFont
{
	/*000,4*/ ImageBMP* bitmap;
	/*bf0,4*/ ImageFont* m_next;
	/*bf4*/
};

typedef enum _D3DRMPALETTEFLAGS
{   D3DRMPALETTE_FREE,                  /* renderer may use this entry freely */
    D3DRMPALETTE_READONLY,              /* fixed but may be used by renderer */
    D3DRMPALETTE_RESERVED               /* may not be used by renderer */
} D3DRMPALETTEFLAGS, *LPD3DRMPALETTEFLAGS;

typedef struct _D3DRMPALETTEENTRY
{   unsigned char red;          /* 0 .. 255 */
    unsigned char green;        /* 0 .. 255 */
    unsigned char blue;         /* 0 .. 255 */
    unsigned char flags;        /* one of D3DRMPALETTEFLAGS */
} D3DRMPALETTEENTRY, *LPD3DRMPALETTEENTRY;

typedef DWORD D3DCOLOR;

// <https://github.com/defunkt/quake/blob/63e82d566a86d0380803189a53d48af42413ea42/WinQuake/dxsdk/SDK/INC/D3DRMDEF.H#L121>
struct D3DRMIMAGE
{
	/*00,8*/ Size2I size;
	/*08,8*/ Point2I aspect;
	// /*00,4*/ int width;
	// /*04,4*/ int height;
	// /*08,4*/ int aspectx; // 1 (planes? layers? frames?)
	// /*0c,4*/ int aspecty; // 1 (planes? layers? frames?)
	/*10,4*/ int bitsPerPixel;
	/*14,4*/ BOOL isRGB; // (RGB and not indexed palette?)
	/*18,4*/ unsigned int stride;
	/*1c,4*/ unsigned char* pixels; // memory to render into (first buffer)
	/*20,4*/ unsigned char* doubleBuffer; // second rendering buffer for double buffering, set to NULL for single buffering.
	/*24,10*/ ColourRGBAI mask; // mask channels (default: 0xfc for 8-bit only)
	// /*24,4*/ unsigned int red_mask; // 0xfc (8-bit only)  // font related?
	// /*28,4*/ unsigned int green_mask; // 0xfc (8-bit only)  // font related?
	// /*2c,4*/ unsigned int blue_mask; // 0xfc (8-bit only)  // font related?
	// /*30,4*/ unsigned int alpha_mask; // 0xfc (8-bit only)  // font related?
	/*34,4*/ unsigned int numColors;
	/*38,4*/ LegoRGB* colors; // pointer -> LegoRGB[256] (malloc)
	/*3c*/
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


enum Direction : int
{
    DIRECTION_UP    = 0,
    DIRECTION_RIGHT = 1,
    DIRECTION_DOWN  = 2,
    DIRECTION_LEFT  = 3,
};


// Flags at <LegoRR.exe @00500e68>
enum ObjInfoFlags : unsigned int
{
	OBJINFO_NONE               = 0,

	OBJINFO_HUNGERIMAGES       = 0x1,
	OBJINFO_HEALTHBAR          = 0x2, // (show healthbars)
	//OBJINFO_UNK_4              = 0x4,
	OBJINFO_HEALTHBAR_VERTICAL = 0x8, // (only included if OBJINFO_HEALTHBAR)
	OBJINFO_BUBBLEIMAGES       = 0x10,
};
DEFINE_ENUM_FLAG_OPERATORS(ObjInfoFlags)


enum TextureTypes : int
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


enum D3DRMTEXTUREQUALITY
{
	D3DRMTEXTURE_NEAREST          = 0, /* choose nearest texel */
    D3DRMTEXTURE_LINEAR           = 1, /* interpolate 4 texels */
    D3DRMTEXTURE_MIPNEAREST       = 2, /* nearest texel in nearest mipmap  */
    D3DRMTEXTURE_MIPLINEAR        = 3, /* interpolate 2 texels from 2 mipmaps */
    D3DRMTEXTURE_LINEARMIPNEAREST = 4, /* interpolate 4 texels in nearest mipmap */
    D3DRMTEXTURE_LINEARMIPLINEAR  = 5, /* interpolate 8 texels from 2 mipmaps */
};

// if (!Filter)
//  quality = D3DRMTEXTURE_NEAREST         /*0*/;
// else if (!MipMap)
//  quality = D3DRMTEXTURE_LINEAR          /*1*/;
// else if (!LinearMipMap)
//  quality = D3DRMTEXTURE_MIPLINEAR       /*3*/;
// else
//  quality = D3DRMTEXTURE_LINEARMIPLINEAR /*5*/;

// Options: Sort and Blend seemed to be ignored

// typedef enum _D3DRMSHADEMODE {
//     D3DRMSHADE_FLAT     = 0,
//     D3DRMSHADE_GOURAUD  = 1,
//     D3DRMSHADE_PHONG    = 2,

//     D3DRMSHADE_MASK     = 7,
//     D3DRMSHADE_MAX      = 8
// } D3DRMSHADEMODE, *LPD3DRMSHADEMODE;
// typedef enum _D3DRMLIGHTMODE {
//     D3DRMLIGHT_OFF      = 0 * D3DRMSHADE_MAX,
//     D3DRMLIGHT_ON       = 1 * D3DRMSHADE_MAX,

//     D3DRMLIGHT_MASK     = 7 * D3DRMSHADE_MAX,
//     D3DRMLIGHT_MAX      = 8 * D3DRMSHADE_MAX
// } D3DRMLIGHTMODE, *LPD3DRMLIGHTMODE;
// typedef enum _D3DRMFILLMODE {
//     D3DRMFILL_POINTS    = 0 * D3DRMLIGHT_MAX,
//     D3DRMFILL_WIREFRAME = 1 * D3DRMLIGHT_MAX,
//     D3DRMFILL_SOLID     = 2 * D3DRMLIGHT_MAX,

//     D3DRMFILL_MASK      = 7 * D3DRMLIGHT_MAX,
//     D3DRMFILL_MAX       = 8 * D3DRMLIGHT_MAX
// } D3DRMFILLMODE, *LPD3DRMFILLMODE;
// #define D3DRMRENDER_WIREFRAME   (D3DRMSHADE_FLAT+D3DRMLIGHT_OFF+D3DRMFILL_WIREFRAME)
// #define D3DRMRENDER_UNLITFLAT   (D3DRMSHADE_FLAT+D3DRMLIGHT_OFF+D3DRMFILL_SOLID)
// #define D3DRMRENDER_FLAT        (D3DRMSHADE_FLAT+D3DRMLIGHT_ON+D3DRMFILL_SOLID)
// #define D3DRMRENDER_GOURAUD     (D3DRMSHADE_GOURAUD+D3DRMLIGHT_ON+D3DRMFILL_SOLID)
// #define D3DRMRENDER_PHONG       (D3DRMSHADE_PHONG+D3DRMLIGHT_ON+D3DRMFILL_SOLID)
enum GraphicsQuality : int
{
	QUALITY_WIREFRAME = 0, // D3DRMRENDER_WIREFRAME = 0x40 = (D3DRMSHADE_FLAT | D3DRMLIGHT_OFF | D3DRMFILL_WIREFRAME) /*0x0 | 0x0 | 0x40*/
	QUALITY_UNLITFLAT = 1, // D3DRMRENDER_UNLITFLAT = 0x80 = (D3DRMSHADE_FLAT | D3DRMLIGHT_OFF | D3DRMFILL_SOLID)     /*0x0 | 0x0 | 0x80*/
	                       // not parsable (anything other than the other 3 names will return an error)
	                       // however this value is still checked when actually setting graphics quality
	QUALITY_FLAT      = 2, // D3DRMRENDER_FLAT      = 0x88 = (D3DRMSHADE_FLAT    | D3DRMLIGHT_ON | D3DRMFILL_SOLID)   /*0x0 | 0x8 | 0x80*/
	QUALITY_GOURAUD   = 3, // D3DRMRENDER_GOURAUD   = 0x89 = (D3DRMSHADE_GOURAUD | D3DRMLIGHT_ON | D3DRMFILL_SOLID)   /*0x1 | 0x8 | 0x80*/
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

enum ObjectType : int
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

struct LiveObjectData
{
	/*000,4*/ ObjectType objType; // ObjType 0 may be intentionally used as NONE
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
	/*408*/ ReservedPool<LiveObjectData>* m_next;
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

// <LegoRR.exe @00475bc0>
void __cdecl Res_GetResourcePairFrames(ResourceData* resData1, ResourceData* resData2, IDirect3DRMFrame3** out_frame1, IDirect3DRMFrame3** out_frame2)
{
  *out_frame1 = resData1->frame1;
  if (resData2 == nullptr) {
    *out_frame2 = pool::globals::ReservedPool<ResourceData>__g_ROOT->frame1;
  }
  else {
  	*out_frame2 = resData2->frame1;
  }
}

// <LegoRR.exe @004756f0>
void __cdecl Res_SetResourceFramePosition(ResourceData* resData1, ResourceData* resData2, float x, float y, float z)
{
  Res_GetResourcePairFrames
            (resData1,resData2,(IDirect3DRMFrame3 **)&resData2,(IDirect3DRMFrame3 **)&resData1);
  (*(code *)resData2->frame1[0x3c].lpVtbl)(resData2,resData1,x,y,z);
  return;
}

struct GameData
{
	/*DAT_005570c0*/

	/*000,4*/ CFGProperty* g_LegoCfgRoot;
	/*004,4*/ const char* g_CFG_ROOTPATH;
	/*008,4*/ undefined4 field_8;
	/*00c,4*/ undefined4 field_c;
	/*010,4*/ GraphicsQuality Quality; //g_GraphicsQuality; // DAT_005570d0
	/*014,4*/ void* level; // g_LEVEL_STRUCTPTR_SIZE_284__005570d4
	/*018,4*/ void* PTR_005570d8;
	/*01c,4*/ void* PTR_005570dc;
	/*020,4*/ undefined4 DAT_005570e0;
	/*024,4*/ void* PTR_005570e4; //DAT_005570e4;
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
	/*348,4*/ unsigned int g_HPBlocks;
	/*34c,c*/ ColourRGBF g_FogColourRGB;
	/*358,c*/ ColourRGBF g_HighFogColourRGB;
	/*364,4*/ float g_LEVEL_UNK_FLOAT_00557424;
	/*368,c*/ ColourRGBF g_PowerCrystalRGB;
	/*374,c*/ ColourRGBF g_UnpoweredCrystalRGB;
	/*380,4*/ int INT_00557440;
	/*384,4*/ int INT_00557444;
	/*388,4*/ int INT_00557448;
	/*38c,4*/ LiveObjectData* PTR_0055744c;
	/*390,4*/ LiveObjectData* PTR_00557450;
	/*394,4*/ LiveObjectData* PTR_00557454;
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
	/*dd8,4*/ unsigned int g_MouseScrollBorder; // 00557e98
	/*ddc,4*/ char* g_HealthText;
	/*de0,4*/ char* g_EnergyText;
	/*de4,4*/ char* g_CrystalsText;
	/*de8,4*/ char* g_OreText;
	/*dec,4*/ char* g_StudsText;
	/*df0,4*/ char* g_ToolsText;
	/*df4,4*/ char* g_CarryObjectText;
	/*df8,4*/ char* g_DrivenByText;
	/*dfc,4*/ char* g_OreRequiredText;
	/*e00,4*/ BOOL g_IsFallinsEnabled; // opposite of Lego.cfg "NoFallins" setting
	/*e04,4*/ float g_MinDistFor3DSoundsOnTopView;
	/*e08,4*/ unsigned int g_GAME_UNK_BOOL_00557ec8; // may not be bool, value tested against 0 and 1
	/*e0c,4*/ GameFlags1 g_GAME_GameFlags1;
	/*e10,4*/ GameFlags2 g_GAME_GameFlags2;
	/*e14,4*/ GameFlags3 g_GAME_GameFlags3; // only first byte is used(?)
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
	/*ed8,4*/ int g_BuildingUpgradeCostOre;
	/*edc,4*/ int g_BuildingUpgradeCostStuds;
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
	SAMPLE_NONE     = 0,

	SAMPLE_ISUSED   = 0x1,
	SAMPLE_VOLUME   = 0x2, // '#%d#' specifier
	SAMPLE_MULTIPLE = 0x4, // '*' specifier (and not '@' specifier)
	SAMPLE_STREAMED = 0x8, // '@' specifier
};
DEFINE_ENUM_FLAG_OPERATORS(SampleFlags)

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
	FILELOC_STD   = 1, // standard file
	FILELOC_ERROR = 2,
};


enum WADEntryFlags : unsigned int
{
	WADENTRY_NONE  = 0,

	WADENTRY_UNK_1 = 0x1, // common value seen for all entries
	WADENTRY_UNK_2 = 0x2, // causes complex load behavior (uses size2)
};
DEFINE_ENUM_FLAG_OPERATORS(WADEntryFlags)

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
	/*08,4*/ int wadIndex;
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
	/*4,4*/ union {
	            FILE* std; // (referred to as STD "standard" file by engine)
	            WADEntryStream* wad;
	        };
	/*8*/
};

enum FileBufferFlags : unsigned int
{
	FILEBUFFER_NONE   = 0,

	FILEBUFFER_ISUSED = 0x1,
	//FILEBUFFER_UNK_2  = 0x2,
	//FILEBUFFER_UNK_4  = 0x4,
	//FILEBUFFER_UNK_8  = 0x8,
};
DEFINE_ENUM_FLAG_OPERATORS(FileBufferFlags)

struct SharedFileBuffer
{
	/*0,4*/ void* fileData;
	/*4,4*/ FileBufferFlags flags; // 0x1 == BOOL isUsed
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
	/*0,4*/ GameInitFunction Init;
	/*4,4*/ GameUpdateFunction Update;
	/*8,4*/ GameCleanupFunction Cleanup;
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


struct LegoTextureInfo
{
	/*0,4*/ const char* name;
	/*4,4*/ undefined4* field_4;
	/*8*/
};

// called exclusively by
// <LegoRR.exe @00472f90>
int** __cdecl Main_loadAECFG_4__ReduceAnimation__00472f90(undefined4* param_1, char* param_2, const char* resourceName, BOOL param_4);

// <LegoRR.exe @00475bf0>
ResourceType __cdecl Main_GetResourceType(const char* resourceName, BOOL* out_noTexture);

// Other name parts: "<ResourceName>:NOTEXTURE"
enum ResourceType
{
	RESOURCE_INVALID  = -1,

	RESOURCE_NULL     = 0, // "NULL"  (ext: "")
	RESOURCE_MESH     = 1, // "MESH"  (ext: "x")
	RESOURCE_FRAME    = 2, // "FRAME" (ext: "x")
	RESOURCE_ANIM     = 3, // "ANIM"  (ext: "x")
	RESOURCE_ACT      = 4, // "ACT"   (ext: "ae") (loads "ae"-extension CFG file : g_FILEEXT_AE)
	RESOURCE_empty    = 5, // NULL    (ext: "")   (explicit)
	RESOURCE_unassigned = 6,//NULL    (ext: NULL) (implicit)
	RESOURCE_LWS      = 7, // "LWS"   (ext: NULL)
	RESOURCE_LWO      = 8, // "LWO"   (ext: NULL)
};

// CPU Dump
// Address   Hex dump                                         ASCII
// 0076BDD8  F4 23 4A 00|14 50 4A 00|BC BA 4A 00|DC 2D 4A 00| �#J.PJ.��J.�-J.
// 0076BDE8  B4 29 4A 00|00 00 00 00|00 00 00 00|E0 23 4A 00| �)J.........�#J.
// 0076BDF8  5C 2D 4A 00|14 9A 4B 00|C4 BA 4A 00|C4 BA 4A 00| \-J.�K.ĺJ.ĺJ.
// 0076BE08  C4 BA 4A 00|C4 29 4A 00|14 9A 4B 00|00 00 00 00| ĺJ.�)J.�K.....
// 0076BE18  00 00 00 00|00 00 00 00|14 68 50 00|             ........hP.


struct ResourceData // originally Struct_2c
{
	/*00,4*/ IDirect3DRMFrame3* frame1;
	/*04,4*/ IDirect3DRMFrame3* frame2;
	/*08,4*/ IDirect3DRMFrame3* frame3;
	/*0c,4*/ void* struct10_c;
	/*10,4*/ ResourceType resType;
	/*14,4*/ unsigned int flags_14;
	/*18,4*/ undefined4 field_18;
	/*1c,4*/ undefined4 field_1c;
	/*20,4*/ undefined4 field_20;
	/*24,4*/ undefined4 field_24;

	/*28,4*/ pool::PoolItem<ResourceData>* pool_m_next;
	/*2c*/
};

// DAT_0076bd80
struct ResourceManager
{
	// DAT_0076bd80
	/*0000,50*/ pool::PoolItem<Struct_2c>* pool_g_TABLE[20]; // PTR_0076bd80
	/*0050,4*/  pool::PoolItem<Struct_2c>* pool_g_NEXT; // PTR_0076bdd0
	/*0054,4*/  pool::PoolItem<Struct_2c>* pool_g_ROOT; // PTR_0076bdd4
	/*0058,24*/ char* Types_TABLE[9]; // PTR_0076bdd8
	/*007c,24*/ char* Extensions_TABLE[9]; // PTR_0076bdfc
	// /*007c,4*/  char* PTR_0076bdfc; // "" // PTR_0076bdfc
	// /*0080,4*/  char* g_KEYNAME_x_1; // "x" // PTR_0076be00
	// /*0084,4*/  char* g_KEYNAME_x_2; // "x" // PTR_0076be04
	// /*0088,4*/  char* g_KEYNAME_x_3; // "x" // PTR_0076be08
	// /*008c,4*/  char* g_FILEEXT_AE; // "ae" // PTR_0076be0c
	// /*0090,4*/  char* PTR_0076be10; // "" // PTR_0076be10
	// /*0094,4*/  undefined4 field_94; // DAT_0076be14
	// /*0098,4*/  undefined4 field_98; // DAT_0076be18
	// /*009c,4*/  undefined4 field_9c; // DAT_0076be1c
	/*00a0,4*/  char* CfgRootName; // "LegoRR" (exename)  // PTR_0076be20
	/*00a4,4*/  undefined4 DAT_0076be24; // DAT_0076be24
	/*00a8,4*/  undefined4 field_a8; // DAT_0076be28
	/*00ac,4*/  undefined4 field_ac; // referenced by addr to get last item of g_Textures_TABLE // DAT_0076be2c
	/*00b0,4*/  undefined4 field_b0; // DAT_0076be30
	/*00b4,1f40*/ LegoTextureInfo Textures_TABLE[1000]; // PTR_0076be34
	/*1ff4,4*/  unsigned int Textures_COUNT; // DAT_0076dd74
	/*1ff8,4*/  undefined4* soundCallback; // PTR_0076dd78
	/*1ffc,4*/  void* soundCallback_VALUE; // DAT_0076dd7c
	/*2000,4*/  undefined4* drawCallback; // PTR_0076dd80
	/*2004,4*/  void* drawCallback_VALUE; // DAT_0076dd84
	/*2008,4*/  char* SharedTextures; // PTR_0076dd88
	/*200c,4*/  unsigned int UnkFogColorref; // DAT_0076dd8c
	/*2010,4*/  unsigned int pool_g_COUNT; // DAT_0076dd90
	/*2014,4*/  unsigned int pool_g_INITFLAGS; // DAT_0076dd94
	/*2018*/
};

//   PD3DRMSortMode = ^TD3DRMSortMode;
//   TD3DRMSortMode = (
//     D3DRMSORT_FROMPARENT,       (* default *)
//     D3DRMSORT_NONE,             (* don't sort child frames *)
//     D3DRMSORT_FRONTTOBACK,      (* sort child frames front-to-back *)
//     D3DRMSORT_BACKTOFRONT       (* sort child frames back-to-front *)
//   );

// <LegoRR.exe @0076bd80>
static ResourceManager g_Res;

// <LegoRR.exe @004729d0>
ResourceData* __cdecl pool::ReservedPool<ResourceData>::Init(const char* cfgRootName)
{
	ResourceData *pRVar1;
	int iVar2;
	ResourceData **ppRVar3;
	

	std::memset(&g_Res, 0, sizeof(ResourceManager));
	
	
	std::memset(&g_Res.pool_g_TABLE, 0, sizeof(g_Res.pool_g_TABLE));
	//pool::ReservedPool<ResourceData,20>::Init();

	g_Res.Extensions_TABLE[1] = "x";
	g_Res.Extensions_TABLE[2] = "x";
	g_Res.Extensions_TABLE[3] = "x";
	g_Res.Types_TABLE[0] = "NULL";
	g_Res.Types_TABLE[1] = "MESH";
	g_Res.Types_TABLE[2] = "FRAME";
	g_Res.Types_TABLE[3] = "ANIM";
	g_Res.Types_TABLE[7] = "LWS";
	g_Res.Types_TABLE[8] = "LWO";
	g_Res.Types_TABLE[4] = "ACT";
	g_Res.Types_TABLE[5] = (char *)0x0;
	g_Res.Extensions_TABLE[0] = ""/*EMPTYSTR*/;
	g_Res.Extensions_TABLE[4] = "ae";
	g_Res.Extensions_TABLE[5] = ""/*EMPTYSTR*/;
	g_Res.CfgRootName = cfgRootName;
	g_Res.pool_g_NEXT = NULL;
	g_Res.pool_g_COUNT = 0;
	g_Res.pool_g_INITFLAGS = 0x1;
	g_Res.Textures_COUNT = 0;
	g_Res.SharedTextures = NULL;
	ResourceData* resRoot = pool::ReservedPool<ResourceData,20>::Next();
	g_Res.pool_g_ROOT = resRoot;
	
	// function SetSortMode (d3drmSM: TD3DRMSortMode) : HResult; stdcall;
	// <https://github.com/Krakean/lightalloy/blob/4504cfb1d9c3e1eb19e26bad6177931f0960c9e9/Source/Common/DirectShow/Direct3DRM.pas#L1297>
	resRoot->frame1->SetSortMode(1);


	ppRVar3 = globals::ReservedPool<ResourceData>__g_TABLE;
	for (iVar2 = 0x806; iVar2 != 0; iVar2 += -1) {
		*ppRVar3 = (ResourceData *)0x0;
		ppRVar3 = ppRVar3 + 1;
	}
	ppRVar3 = globals::ReservedPool<ResourceData>__g_TABLE;
	for (iVar2 = 0x14; iVar2 != 0; iVar2 += -1) {
		*ppRVar3 = (ResourceData *)0x0;
		ppRVar3 = ppRVar3 + 1;
	}
	g_Res.Extensions_TABLE[1] = "x";
	g_Res.Extensions_TABLE[2] = "x";
	g_Res.Extensions_TABLE[3] = "x";
	g_Res.Types_TABLE[0] = "NULL";
	g_Res.Types_TABLE[1] = "MESH";
	g_Res.Types_TABLE[2] = "FRAME";
	g_Res.Types_TABLE[3] = "ANIM";
	g_Res.Types_TABLE[7] = "LWS";
	g_Res.Types_TABLE[8] = "LWO";
	g_Res.Types_TABLE[4] = "ACT";
	g_Res.Types_TABLE[5] = (char *)0x0;
	g_Res.Extensions_TABLE[0] = ""/*EMPTYSTR*/;
	g_Res.Extensions_TABLE[4] = "ae";
	g_Res.Extensions_TABLE[5] = ""/*EMPTYSTR*/;
	lego::globals::g_Resource_CfgRootName = cfgRootName;
	globals::ReservedPool<ResourceData>__g_NEXT = (ResourceData *)0x0;
	globals::ReservedPool<ResourceData>__g_COUNT = 0;
	globals::ReservedPool<ResourceData>__g_INITFLAGS = 1;
	lego::globals::g_Textures_COUNT = 0;
	lego::globals::g_SharedTextures = (char *)0x0;
	pRVar1 = ReservedPool<ResourceData>__Next((ResourceData *)0x0);
	globals::ReservedPool<ResourceData>__g_ROOT = pRVar1;
	(*(code *)pRVar1->frame1->lpVtbl->SetSortMode)(pRVar1->frame1,1);
	return pRVar1;
}



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
	OBJECTIVE_NONE               = 0,
	OBJECTIVE_DEFAULT            = 0x10, // if no other flags are set by the end

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
	//OBJECTIVE_UNK_2000           = 0x2000,
	//OBJECTIVE_UNK_4000           = 0x4000,
	//OBJECTIVE_UNK_8000           = 0x8000,
};
DEFINE_ENUM_FLAG_OPERATORS(ObjectiveFlags)

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
	/*3c*/
};


enum LevelBlockFlags1 : unsigned int
{
	BLOCK1_NONE          = 0,

	BLOCK1_RUBBLE_LOW    = 0x1,
	BLOCK1_RUBBLE_MEDIUM = 0x2,
	BLOCK1_RUBBLE_FULL   = 0x3,
	//BLOCK1_UNK_4         = 0x4,
	BLOCK1_UNK_8         = 0x8,

	BLOCK1_UNK_10        = 0x10,
	BLOCK1_REINFORCED    = 0x20,
	BLOCK1_UNK_40        = 0x40,
	BLOCK1_UNK_80        = 0x80,

	//BLOCK1_UNK_100       = 0x100,
	BLOCK1_UNK_200       = 0x200,
	BLOCK1_UNK_400       = 0x400,
	BLOCK1_UNK_800       = 0x800,

	BLOCK1_UNK_1000      = 0x1000,
	//BLOCK1_UNK_2000      = 0x2000,
	BLOCK1_UNK_4000      = 0x4000,
	BLOCK1_UNK_8000      = 0x8000,

	//BLOCK1_UNK_10000     = 0x10000,
	BLOCK1_HIDDEN        = 0x20000,
	//BLOCK1_UNK_40000     = 0x40000,
	BLOCK1_UNK_80000     = 0x80000,
	
	BLOCK1_UNK_100000    = 0x100000,
	BLOCK1_UNK_200000    = 0x200000,
	BLOCK1_UNK_400000    = 0x400000,
	//BLOCK1_UNK_800000    = 0x800000,

	//BLOCK1_UNK_1000000   = 0x1000000,
	//BLOCK1_UNK_2000000   = 0x2000000,
	BLOCK1_EXPOSED       = 0x4000000,
	BLOCK1_UNK_8000000   = 0x8000000,

	//BLOCK1_UNK_10000000  = 0x10000000,
	BLOCK1_POWERPATH     = 0x20000000,
	BLOCK1_UNK_40000000  = 0x40000000,
	BLOCK1_UNK_80000000  = 0x80000000,
};
DEFINE_ENUM_FLAG_OPERATORS(LevelBlockFlags1)

enum LevelBlockFlags2 : unsigned int
{
	BLOCK2_NONE             = 0,

	//BLOCK2_UNK_1            = 0x1,
	//BLOCK2_UNK_2            = 0x2,
	//BLOCK2_UNK_4            = 0x4,
	//BLOCK2_UNK_8            = 0x8,

	//BLOCK2_UNK_10           = 0x10,
	BLOCK2_SLUGHOLE_EXPOSED = 0x20,
	BLOCK2_EMERGE_POINT     = 0x40,
	BLOCK2_EMERGE_TRIGGER   = 0x80,

	//BLOCK2_UNK_100          = 0x100,
	BLOCK2_SLUGHOLE_HIDDEN  = 0x200,
	//BLOCK2_UNK_400          = 0x400,
	//BLOCK2_UNK_800          = 0x800,
};
DEFINE_ENUM_FLAG_OPERATORS(LevelBlockFlags2)

enum LiveObjectFlags1 : unsigned int
{
	LIVEOBJ1_NONE     = 0,

	LIVEOBJ1_MOVING   = 0x1, // moving
	LIVEOBJ1_LEFTING  = 0x2,
	LIVEOBJ1_TURNING  = 0x4,
	
	LIVEOBJ1_REINFORCING = 0x40,
	LIVEOBJ1_TURNRIGHT = 0x80,

	LIVEOBJ1_CARRYING = 0x400,

	LIVEOBJ1_CLEARING = 0x40000,
	LIVEOBJ1_PLACING  = 0x80000,

	LIVEOBJ1_REST     = 0x20000000,
	LIVEOBJ1_EATING   = 0x40000000,
};
enum LiveObjectFlags2 : unsigned int
{
	LIVEOBJ2_NONE      = 0,
	LIVEOBJ2_DRIVING   = 0x8,

	LIVEOBJ2_TRAINING  = 0x400,
	LIVEOBJ2_UNK_800   = 0x800,
	LIVEOBJ2_UPGRADING = 0x8000,
};
enum LiveObjectFlags3 : unsigned int
{
	LIVEOBJ3_NONE     = 0,

	LIVEOBJ3_BARRIEREXPANDED = 0x20000,
};
enum LiveObjectAbilities : unsigned char
{
	ABILITY_PILOT  = 0x1,
	ABILITY_DRIVER = 0x4,
};


enum MAPCryOreBlock : short
{
	CRYORE_NONE         = 0,

	CRYORE_CRYSTAL_1_A  = 1,
	CRYORE_ORE_1_A      = 2,
	CRYORE_CRYSTAL_1_B  = 3,
	CRYORE_ORE_1_B      = 4,

	CRYORE_CRYSTAL_3_A  = 5,
	CRYORE_ORE_3_A      = 6,
	CRYORE_CRYSTAL_3_B  = 7,
	CRYORE_ORE_3_B      = 8,

	CRYORE_CRYSTAL_5_A  = 9,
	CRYORE_ORE_5_A      = 10,
	CRYORE_CRYSTAL_5_B  = 11,
	CRYORE_ORE_5_B      = 12,

	CRYORE_CRYSTAL_10_A = 13,
	CRYORE_ORE_10_A     = 14,
	CRYORE_CRYSTAL_10_B = 15,
	CRYORE_ORE_10_B     = 16,

	CRYORE_CRYSTAL_25_A = 17,
	CRYORE_ORE_25_A     = 18,
	CRYORE_CRYSTAL_25_B = 19,
	CRYORE_ORE_25_B     = 20,
};

enum MAPEmergeBlock : short
{
	EMERGE_NONE         = 0,

	EMERGE_TRIGGER      = 1,
	EMERGE_EMERGE       = 2,
	EMERGE_UNUSED_3     = 3,
	EMERGE_UNUSED_4     = 4,
	EMERGE_UNUSED_5     = 5,
	EMERGE_UNUSED_6     = 6,

	EMERGE_INCREMENT    = 6,
};
enum MAPErosionBlock : short
{
	EROSION_NONE             = 0,

	EROSION_LAVA_VERYSLOW    = 1,
	EROSION_ALWAYS_VERYSLOW  = 2,

	EROSION_LAVA_SLOW        = 3,
	EROSION_ALWAYS_SLOW      = 4,

	EROSION_LAVA_MEDIUM      = 5,
	EROSION_ALWAYS_MEDIUM    = 6,

	EROSION_LAVA_FAST        = 7,
	EROSION_ALWAYS_FAST      = 8,

	EROSION_LAVA_VERYFAST    = 9,
	EROSION_ALWAYS_VERYFAST  = 10,

///TODO: What speed does reverse erosion take place in?
	EROSION_REVERSE_VERYFAST = 12,

	EROSION_REVERSE_FAST     = 14,

	EROSION_REVERSE_MEDIUM   = 16,

	EROSION_REVERSE_SLOW     = 18,

	EROSION_REVERSE_VERYSLOW = 20,

///TODO: What speed does reverse erosion take place in?
/*	EROSION_REVERSE_VERYSLOW = 12,

	EROSION_REVERSE_SLOW     = 14,

	EROSION_REVERSE_MEDIUM   = 16,

	EROSION_REVERSE_FAST     = 18,

	EROSION_REVERSE_VERYFAST = 20,*/
};

struct LevelBlock
{
	 // 4:?,5:cryore,6:erode
	/*04,4*/ undefined4 blockpointers_4;
	/*08,4*/ undefined4 path_8;
	/*0c,4*/ unsigned int flags_c;


	/*34,4*/ undefined4 ai_34;
	/*38,4*/ undefined4 fallin_38;
	/*3c,4*/ undefined4 fallin_3c;
	/*48*/
};

struct LevelTerrain_1c
{
	/*1c*/
};

struct ObjectiveData
{
	// field offsets listed asL ObjectiveData,LevelData,size
	/*00,0bc,4*/ void* ObjectiveImage; // bmp
	/*04,0c0,4*/ int ObjectiveImage_width_x; //???
	/*08,0c4,4*/ int ObjectiveImage_height_y; //???
	/*0c,0c8,4*/ void* ObjectiveAcheivedImage; // bmp
	/*10,0cc,4*/ int ObjectiveAcheivedImage_width_x; //???
	/*14,0d0,4*/ int ObjectiveAcheivedImage_height_y; //???
	/*18,0d4,4*/ void* ObjectiveFailedImage; // bmp
	/*1c,0d8,4*/ int ObjectiveFailedImage_width_x; //???
	/*20,0dc,4*/ int ObjectiveFailedImage_height_y; //???
	/*24,0e0,4*/ void* ObjectiveAcheivedAVI; //???
	/*28,0e4,4*/ int ObjectiveAcheivedAVI_width_x; //???
	/*2c,0e8,4*/ int ObjectiveAcheivedAVI_height_y; //???
	/*30,0ec,4*/ undefined4 field_30;
	/*34,0f0,4*/ undefined4 field_34;
	/*38,0f4,4*/ int CrystalObjective; // number of crystals needed if non-zero
	/*3c,0f8,4*/ int OreObjective; // number of ore needed if non-zero
	/*40,0fc,8*/ Point2I BlockObjective;
	/*48,104,4*/ float TimerObjective; // (mult: 25.0, flags, format: "time:HitTimeFailObjective")
	/*4c,108,4*/ int ConstructionObjective_type;
	/*50,10c,4*/ int ConstructionObjective_index;
	/*54*/
};

struct LevelData
{
	/*000,4*/ char* levelName; // (format: "Levels::level")
	/*004,4*/ LevelSurfaceMap* surfaceMap;
	/*008,4*/ undefined4 field_8;
	/*00c,4*/ undefined4 field_c;

	/*014,8*/ Size2I dimensions;
	/*01c,4*/ float BlockSize;
	/*020,4*/ float DigDepth;
	/*024,4*/ float RoofHeight;
	/*028,4*/ float RoughLevel;
	/*02c,4*/ BOOL3 UseRoof;
	/*030,4*/ BOOL3 SafeCaverns;
	/*034,4*/ float SelBoxHeight;

	/*074,4*/ int field_74; // observed: 8
	/*078,4*/ int field_78; // observed: 8
	/*07c,4*/ void* ptr_7c;
	/*080,4*/ void* ptr_80;
	/*084,4*/ LevelStruct_3c* struct3c_84;
	/*088,4*/ LevelTerrain_1c* terrain1c_88;
	/*08c,4*/ undefined4 field_8c; // (init: 0)
	/*090,4*/ undefined4 field_90; // (init: 0)
	/*094,4*/ undefined4 field_94; // (init: 0)


	/*0a0,4*/ undefined4 field_a0; // (init: 0)
	/*0a4,4*/ undefined4 field_a4; // (init: 0)
	/*0a8,4*/ undefined4 field_a8; // (init: 0)

	/*0b0,4*/ int EmergeCreature; // (searches for object index by name, expects RockMonsterType)
	/*0b4,4*/ char* NextLevel;
	/*0b8,4*/ LevelBlock* blocks; // grid of blocks [y][x]

	///OBJECTIVEDATA:
	/*0bc,4*/ void* ObjectiveImage;
	/*0c0,4*/ int ObjectiveImage_width_x; //???
	/*0c4,4*/ int ObjectiveImage_height_y; //???
	/*0c8,4*/ void* ObjectiveAcheivedImage;
	/*0cc,4*/ int ObjectiveAcheivedImage_width_x; //???
	/*0d0,4*/ int ObjectiveAcheivedImage_height_y; //???
	/*0d4,4*/ void* ObjectiveFailedImage;
	/*0d8,4*/ int ObjectiveFailedImage_width_x; //???
	/*0dc,4*/ int ObjectiveFailedImage_height_y; //???
	/*0e0,4*/ void* ObjectiveAcheivedAVI;
	/*0e4,4*/ int ObjectiveAcheivedAVI_width_x; //???
	/*0e8,4*/ int ObjectiveAcheivedAVI_height_y; //???
	/*0ec,4*/ undefined4 objective_0ec;
	/*0f0,4*/ undefined4 objective_0f0;
	/*0f4,4*/ int CrystalObjective;
	/*0f8,4*/ int OreObjective;
	/*0fc,8*/ Point2I BlockObjective;
	/*104,4*/ float TimerObjective; // (mult: 25.0, flags, format: "time:HitTimeFailObjective")
	/*108,4*/ int ConstructionObjective_type;
	/*10c,4*/ int ConstructionObjective_index;
	///END OF OBJECTIVE DATA
	/*110,4*/ BOOL hasBlockPointers;

	/*118,4*/ void* ptr_118;



	/*1f4,4*/ BOOL StartFP;
	/*1f8,4*/ BOOL NoDrain;
	/*1fc,4*/ float field_1fc; // (init: 100.0, Oxygen level?)
	/*200,4*/ float OxygenRate; // (mult: 0.001)
	/*204,4*/ float field_204; // (init: 100.0, Oxygen level?)
	/*208,4*/ float BuildingTolerance; // (default: 4.0)
	/*20c,4*/ float BuildingMaxVariation; // (default: 6.0)
	/*210,50*/ float UpgradeTimes[20]; // [objType] (mult: 25.0, 1:Vehicle, 2:MiniFigure, 3:Building)
	/// OVERLOADS:
	// /*214,4*/ float VehicleUpgradeTime; // (mult: 25.0)
	// /*218,4*/ float MinifigureUpgradeTime; // (mult: 25.0)
	// /*220,4*/ float BuildingUpgradeTime; // (mult: 25.0)
	/*260,4*/ float TrainTime; // (mult: 25.0)
	/*264,4*/ float EmergeTimeOut; // (default: 1500.0)
	/*268,4*/ float SlugTime; // (default: 60.0, mult: 25.0 (applies to default))
	/*26c,4*/ int Slug; // (default: 20, searches for object index by name, expects RockMonsterType)
	/*270,4*/ char* FullName; // (replace '_' with ' ')
	/*274,4*/ TextureTypes BoulderAnimation; // (texture index, hardcoded: Rock, Lava, Ice)
	/*278,4*/ float MaxStolen;
	/*27c,4*/ LevelCompleteStatus status; // (init: 0) 2 is used for Crystal failure as well
	/*280,4*/ BOOL IsStartTeleportEnabled; // (! DisableStartTeleport)
	/*284*/
};


enum DriverModeFlags : unsigned int
{
	DRIVERMODE_NONE      = 0,

	DRIVERMODE_ISUSED    = 0x1, // this table item is valid
	//DRIVERMODE_UNK_2     = 0x2,
	//DRIVERMODE_UNK_4     = 0x4,
	//DRIVERMODE_UNK_8     = 0x8,

	DRIVERMODE_NOGUID_10 = 0x10, // drive info does not have a GUID associated with it(?)
	DRIVERMODE_NOGUID_20 = 0x20, // drive info does not have a GUID associated with it(?)
};
DEFINE_ENUM_FLAG_OPERATORS(DriverModeFlags)

enum DeviceModeFlags : unsigned int
{
	DEVICEMODE_NONE                = 0,

	DEVICEMODE_ISUSED              = 0x1, // this table item is valid
	//DEVICEMODE_UNK_2               = 0x2,
	//DEVICEMODE_UNK_4               = 0x4,
	//DEVICEMODE_UNK_8               = 0x8,

	DEVICEMODE_BPP_8               = 0x10, // supports 8-bit color mode
	DEVICEMODE_BPP_16              = 0x20, // supports 16-bit color mode
	DEVICEMODE_BPP_24              = 0x40, // supports 24-bit color mode
	DEVICEMODE_BPP_32              = 0x80, // supports 32-bit color mode

	DEVICEMODE_COLORMODEL_RGB      = 0x1000, // uses RGB color model (vs. mono?)
	DEVICEMODE_HARDWARE            = 0x2000, // hardware support(?)
	DEVICEMODE_TEXTUREVIDEOMEMORY  = 0x4000,
	DEVICEMODE_TEXTURESYSTEMMEMORY = 0x8000,
};
DEFINE_ENUM_FLAG_OPERATORS(DeviceModeFlags)

enum ScreenModeFlags : unsigned int
{
	SCREENMODE_NONE      = 0,

	SCREENMODE_ISUSED    = 0x1, // this table item is valid
	//SCREENMODE_UNK_2               = 0x2,
	//SCREENMODE_UNK_4               = 0x4,
	//SCREENMODE_UNK_8               = 0x8,
};
DEFINE_ENUM_FLAG_OPERATORS(ScreenModeFlags)

struct DriverMode
{
	/*000,10*/  GUID guid;
	/*010,100*/ char displayName[256];
	/*110,4*/   DriverModeFlags flags;
	/*114*/
};

struct DeviceMode
{
	/*000,10*/  GUID guid;
	/*010,100*/ char displayName[256];
	/*110,4*/   DeviceModeFlags flags;
	/*114*/
};

struct ScreenMode
{
	/*000,4*/   int screenWidth;
	/*004,4*/   int screenHeight;
	/*008,4*/   int bitDepth;
	/*00c,100*/ char displayName[256];
	/*10c,4*/   ScreenModeFlags flags;
	/*110*/
};


struct ErodeState
{
	/*0,4*/ undefined4 field_0;
	/*4,4*/ undefined4 field_4;
	/*8*/
};

// <LegoRR.exe @005570c0 -> 00557fb8>
struct GameData
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
	STATS1_NONE                   = 0,

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
DEFINE_ENUM_FLAG_OPERATORS(ObjectStatsFlags1)

enum ObjectStatsFlags2 : unsigned int
{
	STATS2_NONE                   = 0,

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
DEFINE_ENUM_FLAG_OPERATORS(ObjectStatsFlags2)

enum ObjectStatsFlags3 : unsigned int
{
	STATS3_NONE                   = 0,

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
DEFINE_ENUM_FLAG_OPERATORS(ObjectStatsFlags3)



enum ObjectStatsFlags1 : unsigned int
{
	STATS1_NONE                   = 0,

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
DEFINE_ENUM_FLAG_OPERATORS(ObjectStatsFlags1)

enum ObjectStatsFlags2 : unsigned int
{
	STATS2_NONE                   = 0,

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
DEFINE_ENUM_FLAG_OPERATORS(ObjectStatsFlags2)

enum ObjectStatsFlags3 : unsigned int
{
	STATS3_NONE                   = 0,

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
DEFINE_ENUM_FLAG_OPERATORS(ObjectStatsFlags3)

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

// object stats table (starts at 004e4944)

// DAT_004e8184 points to Path object type

//                              DAT_004e8184                                    XREF[1]:     FUN_00437790:0043779f(RW)  
//        004e8184                               ??         ??

        // 004e9443                               ??         ??
        //                      lego::globals::nerps::g_NERPS_TrainFlags        XREF[4]:     FUN_0043f870:0043f890(R), 
        //                                                                                   FUN_0043f870:0043f89a(W), 
        //                                                                                   NERPFunc__GetTrainFlags:00456820
        //                                                                                   NERPFunc__SetTrainFlags:00456836
        // 004e9444                               uint       ??
        //                      MINIFIGOBJ_004e9448                             XREF[5]:     Main_loadLevelCFG:0042b0c6(R), 
        //                                                                                   Main_loadLevelCFG:0042b0d9(R), 
        //                                                                                   Main_loadObjectListCFG:0042e57f(
        //                                                                                   Main_loadObjectListCFG:0042e58d(
        //                                                                                   Game_freeLevel__0042eff0:0042f07
        // 004e9448                               void *     NaP



struct ObjectLevels
{

};

// <LegoRR.exe @00503bd8> // distance = 80 (0x50), so not all object types support stats
static ObjectStats** g_ObjectStats_TABLE[20]; //[objType][objIndex][objLevel]
// <LegoRR.exe @00503c28>
static int g_ObjectLevels_TABLE[20][15]; // 15 * number of object types

*(char **)(&DAT_00503c28 + (local_148 + local_14c * 0xf) * 4) = local_134;

//static ObjectTypeData DAT_00503bd8[]; // object types data

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


struct ItemStruct_428
{
	/*00,4*/ int index;
	/*04,4*/ Direction direction;
	/*08,4*/ unsigned int field_8;
	/*0c,4*/ unsigned int field_c;
	/*10,4*/ unsigned int field_10;
	/*14,4*/ unsigned int field_14;
	/*18*/
};
struct Struct_428
{
	/*000,320*/ Point2F points[100];
	/*320,4*/ unsigned int count; // number of points?
	/*324,f0*/ ItemStruct_428 items[10];
	/*414,4*/ unsigned int itemsCount;
	/*418,4*/ unsigned int field_418;
	/*41c,4*/ unsigned int field_41c;
	/*420,4*/ unsigned int field_420;
	/*424,4*/ unsigned int field_424;
	/*428*/
};
struct PairStruct_428
{
	/*0,4*/ Struct_428* first;
	/*4,4*/ Struct_428* second;
	/*8*/
};

// <LegoRR.exe @0054a520>
static Struct_428 Struct_428_ARRAY_0054a520[10];
// <LegoRR.exe @0054ceb0>
static unsigned int Struct_428_COUNT_0054ceb0; // count of Struct_428 Struct_428_ARRAY_0054a520[10] table
// <LegoRR.exe @0054ceb4>
static PairStruct_428 PairStruct_428_ARRAY_0054ceb4[10];
// <LegoRR.exe @0054cf04>
static unsigned int PairStruct_428_COUNT_0054cf04; // count of PairStruct_428 PairStruct_428_ARRAY_0054ceb4[10] table


// <LegoRR.exe @0046ed90>
void __cdecl lego::game::Level_LoadAddStruct428(Struct_428* struct428, unsigned int y, unsigned int unkParam_x, unsigned int unkParam_xMax)
{
	for (; unkParam_x < unkParam_xMax; unkParam_x++) {
		struct428->points[struct428->count].x = (float)(unsigned long long)unkParam_x;
		struct428->points[struct428->count].y = (float)(unsigned long long)y;
		struct428->count++;
		// unkParam_x++;
	}
	// if (unkParam_x < unkParam_xMax) {
	// 	do {
	// 		struct428->points[struct428->count].x = (float)(ulonglong)unkParam_x;
	// 		struct428->points[struct428->count].y = (float)(ulonglong)y;
	// 		unkParam_x += 1;
	// 		struct428->count = struct428->count + 1;
	// 	} while (unkParam_x < unkParam_xMax);
	// }
	return;
}

// <LegoRR.exe @0046edf0>
void __cdecl lego::game::Level_LoadAddFirstStruct428(unsigned int y, unsigned int unkParam_x, unsigned int unkParam_xMax)
{
	Struct_428* struct428 = &Struct_428_ARRAY_0054a52[Struct_428_COUNT_0054ceb0];
	Struct_428_ARRAY_0054a520[Struct_428_COUNT_0054ceb0].count = 0;
	Level_LoadAddStruct428(struct428, y, unkParam_x, unkParam_xMax);
	Struct_428_COUNT_0054ceb0++;
	return;
}

// <LegoRR.exe @0046ec90>
Struct_428* __cdecl lego::game::Level_LoadSearchStruct428(int y, unsigned int unkParam_x, unsigned int unkParam_xMax)
{
	float *pfVar1;
	const Point2F* pfVar2; // pfVar2
	uint uVar3;
	float *pfVar4;
	float *pfVar5;
	float fVar6;
	
	Struct_428* first = nullptr;
	if (y == 0)
		return nullptr;
	
	for (; unkParam_x < unkParam_xMax; unkParam_x++) {
		//j = uVar3
		for (unsigned int i = 0; i < Struct_428_COUNT_0054ceb0; i++) { //uVar3++

			for (unsigned int j = 0; j < Struct_428_ARRAY_0054a520[i].count; j++) {

				Struct_428* current = &Struct_428_ARRAY_0054a520[i];

				if ((float)(unsigned long long)unkParam_x == Struct_428_ARRAY_0054a520[i].points[j].x &&
					(float)(unsigned long long)(y - 1)    == Struct_428_ARRAY_0054a520[i].points[j].y)
				{
					if (first == nullptr) {
						first = current;
					}
					else if (first != current) {
						PairStruct_428_ARRAY_0054ceb4[PairStruct_428_COUNT_0054cf04].first  = first;
						PairStruct_428_ARRAY_0054ceb4[PairStruct_428_COUNT_0054cf04].second = current;
						PairStruct_428_COUNT_0054cf04++;
					}
				}
			}
		}
	}
	return first; //result;


            pSVar2 = pSVar1;
            pSVar5 = pSVar4;
            do {
              pSVar4 = pSVar5;
              if (((((float)(ulonglong)unkParam_x == pSVar2->points[0].x) &&
                   ((float)(ulonglong)(y - 1) == pSVar2->points[0].y)) &&
                  (pSVar4 = pSVar1, pSVar5 != NULL)) && (pSVar4 = pSVar5, pSVar5 != pSVar1)) {
                PairStruct_428_ARRAY_0054ceb4[PairStruct_428_COUNT_0054cf04].first = pSVar5;
                PairStruct_428_ARRAY_0054ceb4[PairStruct_428_COUNT_0054cf04].second = pSVar1;
                PairStruct_428_COUNT_0054cf04 += 1;
              }
              uVar6 += 1;
              pSVar2 = (Struct_428 *)(pSVar2->points + 1);
              pSVar5 = pSVar4;
            } while (uVar6 < pSVar1->count);

	if (y != 0 && unkParam_x < unkParam_xMax) {
		do {
			uVar3 = 0;
			if (Struct_428_COUNT_0054ceb0 != 0) {
				pfVar1 = (float*)&Struct_428_ARRAY_0054a520; // const Point2F[100]
				do {
					fVar6 = 0.0;
					if (pfVar1[200] != 0.0) {
						Struct_428* pfVar2 = pfVar1;
						Struct_428* pfVar5 = pfVar4;
						do {
							pfVar4 = pfVar5;
							// if (((float)(unsigned long long)unkParam_x == *pfVar2 &&
							// 	(float)(unsigned long long)(y - 1) == pfVar2[1] && (pfVar4 = pfVar1, pfVar5 != nullptr)) && (pfVar4 = pfVar5, pfVar5 != pfVar1))
							if ((float)(unsigned long long)unkParam_x == *pfVar2 &&
								(float)(unsigned long long)(y - 1) == pfVar2[1]) // && (pfVar4 = pfVar1, pfVar5 != nullptr)) && (pfVar4 = pfVar5, pfVar5 != pfVar1))
							{
								pfVar4 = (pfVar5 != nullptr ? pfVar5 : pfVar1);
								if (pfVar5 != pfVar1) {

								}
								(&PairStruct_428_ARRAY_0054ceb4)[PairStruct_428_COUNT_0054cf04 * 2 + 0] = pfVar5;
								(&PairStruct_428_ARRAY_0054ceb4)[PairStruct_428_COUNT_0054cf04 * 2 + 1] = pfVar1;
								PairStruct_428_COUNT_0054cf04++;
							}
							fVar6 = (float)((int)fVar6 + 1);
							pfVar2 = pfVar2 + 2;
							pfVar5 = pfVar4;
						} while ((uint)fVar6 < (uint)pfVar1[200]);
					}
					uVar3 += 1;
					pfVar1 = pfVar1 + 0x10a;
				} while (uVar3 < Struct_428_COUNT_0054ceb0);
			}
			unkParam_x += 1;
		} while (unkParam_x < unkParam_xMax);
	}
	return pfVar4;
}

// <LegoRR.exe @0046ec60>
int __cdecl lego::game::util::Struct428_CompareCount(Struct_428* a, Struct_428* b)
{
	if (a->count < b->count)
		return -1;
	else if (a->count > b->count)
		return 1;
	return 0;
}

// <LegoRR.exe @0046de50>
void __cdecl lego::game::Level_Load_FUN_0046de50(ResourceData* resRoot, LevelData* level)
{
	undefined4* puVar1;
	int iVar2;
	float* pfVar3;
	unsigned int uVar4;
	int iVar5;
	int* piVar6;
	unsigned int uVar7;
	unsigned int uVar8;
	undefined4* puVar9;
	unsigned int uVar10;
	undefined4* puVar11;
	unsigned int uVar12;
	undefined4* puVar13;
	unsigned int local_4;
	
	// uVar8 = 0;
	Struct_428_COUNT_0054ceb0 = 0;
	PairStruct_428_COUNT_0054cf04 = 0;
	lego::globals::g_LevelUnk_DigDepth = level->DigDepth;
	for (unsigned int y = 0; y < (unsigned int)level->dimensions.height; y++) {
		for (unsigned int x = 0; x < (unsigned int)level->dimensions.width; x++) {
			unsigned int unkParam_xMax = 0;
			unsigned int unkParam_x = 0;
			if (level->blocks[y * level->dimensions.width + x].terrain == TERRAIN_WATER_unused /*0x7*/) {
				if (unkParam_x == unkParam_xMax) {
					unkParam_x = x;
				}
				unkParam_xMax = x + 1;
			}
			else {
				if (unkParam_x != unkParam_xMax) {
					Struct_428* pSVar2 = Level_LoadSearchStruct428(y, unkParam_x, unkParam_xMax);
					if (pSVar2 == nullptr) {
						Level_LoadAddFirstStruct428(y, unkParam_x, unkParam_xMax);
					}
					else {
						Level_LoadAddStruct428(pSVar2, y, unkParam_x, unkParam_xMax);
					}
				}
				unkParam_xMax = 0;
				unkParam_x = 0;
			}
		}
	}

	// local_4 = 0;
	for (unsigned int i = 0; i < PairStruct_428_COUNT_0054cf04; i++) {
		Struct_428* first = PairStruct_428_ARRAY_0054ceb4[i].first;
		Struct_428* second = PairStruct_428_ARRAY_0054ceb4[i].second;
		if (pSVar2->count != 0) {
			// some form of overlapped copying...?
			// ... my head...
			std::memset(&first->points[first->count], &second->points[0], sizeof(Point2F) * second->count);
			first->count += second->count;
			second->count = 0;
		}
	}

	// 			Point2F* pPVar11 = pSVar1->points + pSVar1->count;
	// 			Struct_428* pSVar10 = pSVar2;
	// 			for (uVar7 = (pSVar2->count << 3) >> 2; uVar7 != 0; uVar7 -= 1) {
	// 				pPVar11->x = pSVar10->points[0].x;
	// 				pSVar10 = (Struct_428 *)&pSVar10->points[0].y;
	// 				pPVar11 = (Point2F *)(&pPVar11->x + 1);
	// 			}
	// 			for (iVar4 = 0; iVar4 != 0; iVar4 += -1) {
	// 				*(undefined *)&pPVar11->x = *(undefined *)&pSVar10->points[0].x;
	// 				pSVar10 = (Struct_428 *)((int)&pSVar10->points[0].x + 1);
	// 				pPVar11 = (Point2F *)((int)&pPVar11->x + 1);
	// 			}
	// 			pSVar1->count = pSVar1->count + pSVar2->count;
	// 			pSVar2->count = 0;
	// 	}
	// }
	// if (PairStruct_428_COUNT_0054cf04 != 0) {
	// 	ppSVar8 = &PairStruct_428_ARRAY_0054ceb4[0].second;
	// 	do {
	// 		pSVar2 = *ppSVar8;
	// 		pSVar1 = ppSVar8[-1];
	// 		if (pSVar2->count != 0) {
	// 			pSVar10 = pSVar2;
	// 			pPVar11 = pSVar1->points + pSVar1->count;
	// 			std::memset(&pSVar1->points[pSVar1->count], &pSVar2->points[0], sizeof(Point2F) * pSVar2->count);
	// 			for (uVar7 = (pSVar2->count << 3) >> 2; uVar7 != 0; uVar7 -= 1) {
	// 				pPVar11->x = pSVar10->points[0].x;
	// 				pSVar10 = (Struct_428 *)&pSVar10->points[0].y;
	// 				pPVar11 = (Point2F *)(&pPVar11->x + 1);
	// 			}
	// 			for (iVar4 = 0; iVar4 != 0; iVar4 += -1) {
	// 				*(undefined *)&pPVar11->x = *(undefined *)&pSVar10->points[0].x;
	// 				pSVar10 = (Struct_428 *)((int)&pSVar10->points[0].x + 1);
	// 				pPVar11 = (Point2F *)((int)&pPVar11->x + 1);
	// 			}
	// 			pSVar1->count = pSVar1->count + pSVar2->count;
	// 			pSVar2->count = 0;
	// 		}
	// 		local_4 += 1;
	// 		ppSVar8 = ppSVar8 + 2;
	// 	} while (local_4 < PairStruct_428_COUNT_0054cf04);
	// }
	std::qsort(Struct_428_ARRAY_0054a520, Struct_428_COUNT_0054ceb0, sizeof(Struct_428) /*0x428*/, FUN_0046ec60);
	uVar7 = 0;
	// truncate count to number of structs with non-zero count
	for (unsigned int i = 0; i < Struct_428_COUNT_0054ceb0; i++) {
		if (Struct_428_ARRAY_0054a520[i].count == 0) {
			Struct_428_COUNT_0054ceb0 = i; 
		}
	}
	// if (Struct_428_COUNT_0054ceb0 != 0) {
	// 	puVar5 = &Struct_428_ARRAY_0054a520[0].count;
	// 	uVar9 = Struct_428_COUNT_0054ceb0;
	// 	do {
	// 		if (*puVar5 == 0) {
	// 			uVar9 = uVar7;
	// 			Struct_428_COUNT_0054ceb0 = uVar7;
	// 		}
	// 		uVar7 += 1;
	// 		puVar5 = puVar5 + 0x10a;
	// 	} while (uVar7 < uVar9);
	// }
	FUN_0046dfd0(resRoot, level);
	FUN_0046e140(resRoot, level);
	return;
}


// <LegoRR.exe @0046dfd0>
void __cdecl FUN_0046dfd0(ResourceData* resData, LevelData* level)
{
	TerrainType TVar1;
	int iVar2;
	int iVar3;
	int iVar4;
	unsigned int uVar5;
	float *pfVar6;
	long long lVar7;
	Point2F* local_30;
	unsigned int local_2c;
	unsigned int* local_28;
	unsigned int index;
	// Point2F DIRECTIONS[4];
	// DIRECTIONS[0].x = 0.0;
	// DIRECTIONS[0].y = -1.0;
	// DIRECTIONS[1].x = 1.0;
	// DIRECTIONS[1].y = 0.0;
	// DIRECTIONS[2].x = 0.0;
	// DIRECTIONS[2].y = 1.0;
	// DIRECTIONS[3].x = -1.0;
	// DIRECTIONS[3].y = 0.0;

	// see Direction enum: { DIRECTION_UP, DIRECTION_RIGHT, DIRECTION_DOWN, DIRECTION_LEFT }
	const Point2F DIRECTIONS[4] = {
		{  0.0f, -1.0f },
		{  1.0f,  0.0f },
		{  0.0f,  1.0f },
		{ -1.0f,  0.0f },
	};
	for (unsigned int i = 0; i < Struct_428_COUNT_0054ceb0; i++) {
		
		// Struct_428_ARRAY_0054a520[i].itemsCount = 0;
		Struct_428* struct428 = &Struct_428_ARRAY_0054a520[i];
		struct428->itemsCount = 0;

		for (unsigned int j = 0; j < struct428->count; j++) {

			for (int k = 0; k < 4; k++) {
				// lVar7 = __ftol((float10)dir->x + (float10)local_30->x);
				// x = (int)lVar7;
				// lVar7 = __ftol((float10)local_30->y + (float10)dir->y);
				// y = (int)lVar7;
				int x = (struct428->points[j].x + DIRECTIONS[k].x);
				int y = (struct428->points[j].y + DIRECTIONS[k].y);
				if ((x >= 0 && x < level->dimensions.width) && (y >= 0 && y < level->dimensions.height) &&
					(level->blocks[y * level->dimensions.width + x].terrain != TERRAIN_WATER_unused /*0x7*/) &&
					(level->blocks[y * level->dimensions.width + x].terrain != TERRAIN_IMMOVABLE /*0x1*/))
				{
					struct428->items[struct428->itemsCount].index = j; // point index
					struct428->items[struct428->itemsCount].direction = (Direction)k; // direction index
					struct428->itemsCount++;
					break;
				}
			}
		}
	}
	// index = 0;
	// if (Struct_428_COUNT_0054ceb0 != 0) {
	// 	local_28 = &Struct_428_ARRAY_0054a520[0].count;
	// 	do {
	// 		local_30 = (Point2F *)(local_28 + -200);
	// 		local_28[0x3d] = 0;
	// 		local_2c = 0;
	// 		if (*local_28 != 0) {
	// 			do {
	// 				uVar5 = 0;
	// 				Point2F* dir = &DIRECTIONS[0];
	// 				do {
	// 					lVar7 = __ftol((float10)dir->x + (float10)local_30->x);
	// 					iVar3 = (int)lVar7;
	// 					lVar7 = __ftol((float10)local_30->y + (float10)dir->y);
	// 					iVar4 = (int)lVar7;
	// 					if (((iVar3 >= 0 && (iVar2 = level->dimensions.width, iVar3 < iVar2)) &&
	// 						(iVar4 >= 0)) && (((iVar4 < level->dimensions.height &&
	// 						(TVar1 = level->blocks[iVar4 * iVar2 + iVar3].terrain,
	// 						TVar1 != TERRAIN_WATER_unused)) && (TVar1 != TERRAIN_IMMOVABLE))))
	// 					{
	// 						local_28[local_28[0x3d] * 6 + 1] = local_2c;
	// 						local_28[local_28[0x3d] * 6 + 2] = uVar5;
	// 						local_28[0x3d]++;
	// 						break;
	// 					}
	// 					uVar5++;
	// 					dir++;
	// 				} while (uVar5 < 4);
	// 				local_30++;
	// 				local_2c++;
	// 			} while (local_2c < *local_28);
	// 		}
	// 		index++;
	// 		local_28 += 0x10a;
	// 	} while (index < Struct_428_COUNT_0054ceb0);
	// }
	return;
}


// <LegoRR.exe @0046e140>
void __cdecl FUN_0046e140(ResourceData* in_resData, LevelData* level)
{
	int iVar1;
	undefined4 uVar2;
	uint uVar3;
	ResourceData *resData;
	int *index;
	undefined4 *puVar4;
	uint uVar5;
	undefined4 *puVar6;
	float *pfVar7;
	float *pfVar8;
	float *pfVar9;
	longlong lVar10;
	longlong lVar11;
	uint local_138;
	uint *local_134;
	float *local_130;
	int local_12c;
	uint local_128;
	undefined4 local_118 [4];
	undefined4 local_108 [4];
	undefined4 local_f8;
	undefined4 local_f4;
	undefined4 local_f0;
	undefined4 local_ec;
	undefined4 local_e8;
	undefined4 local_e4;
	float local_e0 [5];
	undefined4 local_cc;
	undefined4 local_c8;
	undefined4 local_c4;
	undefined4 local_c0;
	undefined4 local_bc;
	float local_b8 [10];
	undefined local_90 [4];
	undefined4 local_8c [35];


	Point2F angles[8] = {
		{  0.0f,  0.0f },
		{ -1.0f,  0.0f },
		{  1.0f,  1.0f },
		{  0.0f,  0.0f },
		{  0.0f,  1.0f },
		{  0.0f,  0.0f },


		{  0.0f,  1.0f },
		{  1.0f,  0.0f },
		{  0.0f,  0.0f },
	};
	
	local_f4 = 1;
	local_ec = 1;
	local_e0[0] = 0.0;
	local_e0[1] = 0.0;
	local_e0[2] = 1.0;
	local_e0[3] = 0.0;
	local_e0[4] = 1.0;
	local_cc = 0x3f800000;
	local_c8 = 0;
	local_c4 = 0x3f800000;
	local_f8 = 0;
	local_f0 = 3;
	local_e8 = 2;
	local_e4 = 3;
	local_118[0] = 0;
	local_118[1] = 0x3f800000;
	local_118[2] = 0x3f800000;
	local_118[3] = 0;
	local_108[0] = 0;
	local_108[1] = 0;
	local_108[2] = 0x3f800000;
	local_108[3] = 0x3f800000;
	local_128 = 0;
	if (Struct_428_COUNT_0054ceb0 != 0) {
		local_134 = &Struct_428_ARRAY_0054a520[0].pointsCount;
		do {
			pfVar9 = (float *)(local_134 + -200);
			local_134[0x3e] = 0xc61c4000;
			local_138 = 0;
			pfVar7 = pfVar9;
			if (*local_134 != 0) {
				do {
					puVar6 = &local_c0;
					lVar10 = __ftol((float10)pfVar7[1]);
					uVar3 = (uint)lVar10;
					lVar10 = __ftol((float10)*pfVar7);
					FUN_00450390(level->surfaceMap,(uint)lVar10,uVar3,puVar6);
					local_130 = local_b8;
					pfVar8 = local_e0;
					local_12c = 4;
					do {
						lVar10 = __ftol((float10)pfVar8[1] + (float10)pfVar7[1]);
						iVar1 = (level->dimensions).width;
						lVar11 = __ftol((float10)*pfVar7 + (float10)*pfVar8);
						if (level->blocks[(int)lVar10 * iVar1 + (int)lVar11].predug == PREDUG_WALL)
						{
							if ((ushort)((ushort)(*local_130 < (float)local_134[0x3e]) << 8 |
										(ushort)(*local_130 == (float)local_134[0x3e]) << 0xe) == 0)
							{
								local_134[0x3e] = (uint)*local_130;
							}
						}
						else {
							local_134[0x41] |= 1;
						}
						pfVar8 = pfVar8 + 2;
						local_130 = local_130 + 3;
						local_12c += -1;
					} while (local_12c != 0);
					local_138 += 1;
					pfVar7 = pfVar7 + 2;
				} while (local_138 < *local_134);
			}
			local_134[0x3f] = local_134[0x3e];
			resData = lego::res::Res_Unk_LoadVisualMesh(in_resData, 3);
			local_134[0x40] = (uint)resData;
			lego::res::Res_UnkSetup3DFrameTransform(resData, ~local_134[0x41] & 1);
			local_138 = 0;
			if (*local_134 != 0) {
				do {
					index = FUN_00474bb0((ResourceData *)local_134[0x40], 4, 2, 3, (undefined2 *)&local_f8);
					FUN_004752e0((ResourceData *)local_134[0x40], (int)index, 0.0, 0.3, 0.8, 0.6);
					puVar6 = &local_c0;
					lVar10 = __ftol((float10)pfVar9[1]);
					uVar3 = (uint)lVar10;
					lVar10 = __ftol((float10)*pfVar9);
					FUN_00450390(level->surfaceMap, (uint)lVar10, uVar3, puVar6);
					puVar6 = &local_bc;
					puVar4 = local_8c;
					uVar3 = 0;
					do {
						puVar4[-1] = puVar6[-1];
						*puVar4 = *puVar6;
						puVar4[1] = local_134[0x3e];
						uVar5 = uVar3 + 4;
						puVar6 = puVar6 + 3;
						puVar4[2] = 0;
						puVar4[3] = 0;
						puVar4[4] = 0xbf800000;
						uVar2 = *(undefined4 *)((int)local_118 + uVar3);
						puVar4[7] = 0;
						puVar4[5] = uVar2;
						puVar4[6] = *(undefined4 *)((int)local_108 + uVar3);
						puVar4 = puVar4 + 9;
						uVar3 = uVar5;
					} while (uVar5 < 0x10);
					FUN_00474ff0((int *)local_134[0x40], local_138, 0, 4, (int)local_90);
					local_138 += 1;
					pfVar9 = pfVar9 + 2;
				} while (local_138 < *local_134);
			}
			local_128 += 1;
			local_134 = local_134 + 0x10a;
		} while (local_128 < Struct_428_COUNT_0054ceb0);
	}
	return;
}


	if (level->dimensions.height != 0) {
		do {
			uVar10 = 0;
			uVar12 = 0;
			uVar7 = 0;
			uVar4 = (level->dimensions).width;
			if (uVar4 != 0) {
				do {
					if (level->blocks[uVar8 * uVar4 + uVar7].terrain == TERRAIN_WATER_unused) {
						if (uVar12 == uVar10) {
							uVar12 = uVar7;
						}
						uVar10 = uVar7 + 1;
					}
					else {
						if (uVar12 != uVar10) {
							pfVar3 = lego::game::Level_LoadSearchStruct428(uVar8,uVar12,uVar10);
							if (pfVar3 == NULL) {
								FUN_0046edf0(uVar8,uVar12,uVar10);
							}
							else {
								FUN_0046ed90((int)pfVar3,uVar8,uVar12,uVar10);
							}
						}
						uVar10 = 0;
						uVar12 = 0;
					}
					uVar4 = (level->dimensions).width;
					uVar7 += 1;
				} while (uVar7 < uVar4);
			}
			uVar8 += 1;
		} while (uVar8 < (uint)(level->dimensions).height);
	}
	local_4 = 0;
	if (PairStruct_428_COUNT_0054cf04 != 0) {
		puVar9 = &DAT_0054ceb8;
		do {
		puVar1 = (undefined4 *)*puVar9;
		iVar2 = puVar9[-1];
		if (puVar1[200] != 0) {
			puVar11 = puVar1;
			puVar13 = (undefined4 *)(iVar2 + *(int *)(iVar2 + 800) * 8);
			for (uVar8 = (uint)(puVar1[200] << 3) >> 2; uVar8 != 0; uVar8 -= 1) {
			*puVar13 = *puVar11;
			puVar11 = puVar11 + 1;
			puVar13 = puVar13 + 1;
			}
			for (iVar5 = 0; iVar5 != 0; iVar5 += -1) {
			*(undefined *)puVar13 = *(undefined *)puVar11;
			puVar11 = (undefined4 *)((int)puVar11 + 1);
			puVar13 = (undefined4 *)((int)puVar13 + 1);
			}
			*(int *)(iVar2 + 800) = *(int *)(iVar2 + 800) + puVar1[200];
			puVar1[200] = 0;
		}
		local_4 += 1;
		puVar9 = puVar9 + 2;
		} while (local_4 < PairStruct_428_COUNT_0054cf04);
	}
	std::qsort(&Struct_428_ARRAY_0054a520,Struct_428_COUNT_0054ceb0,0x428,FUN_0046ec60);
	uVar8 = 0;
	if (Struct_428_COUNT_0054ceb0 != 0) {
		piVar6 = &DAT_0054a840;
		uVar10 = Struct_428_COUNT_0054ceb0;
		do {
		if (*piVar6 == 0) {
			uVar10 = uVar8;
			Struct_428_COUNT_0054ceb0 = uVar8;
		}
		uVar8 += 1;
		piVar6 = piVar6 + 0x10a;
		} while (uVar8 < uVar10);
	}
	FUN_0046dfd0(resRoot,level);
	FUN_0046e140(resRoot,level);
	return;
}

void memSwap(void* ptr1, void* ptr2, unsigned int count)
{
	if (ptr1 != ptr2) {
		char* swap_ptr1 = (char*)ptr1;
		char* swap_ptr2 = (char*)ptr2;
		while (count-- != 0) {
			char swap = *swap_ptr1;
			*swap_ptr1++ = *swap_ptr2;
			*swap_ptr2++ = swap;
		}
	}
}
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int data1[] = {1,2,3,4,5,6,7,8,9,0};
// int data2[] = {-1,-2,-3,-4,-5,-6,-7,-8,-0,-10};

// memSwap(data1, data2, sizeof(data1));
// printf("data1 ="); for (int i = 0; i < 10; i++) printf(" %3i", data1[i]);

// printf("\ndata2 ="); for (int i = 0; i < 10; i++) printf(" %3i", data2[i]);
// printf("\n\n[swaping...]\n")
// printf("\ndata1 ="); for (int i = 0; i < 10; i++) printf(" %3i", data1[i]);

// printf("\ndata2 ="); for (int i = 0; i < 10; i++) printf(" %3i", data2[i]);
// printf("\n");
// printf("data1 = %3i %3i %3i %3i %3i %3i %3i %3i %3i %3i", data1[0], data1[1], data1[2], data1[3], data1[4], data1[5], data1[0])

typedef int (__cdecl* CompareCallback)(void* item1, void* item2);

void __cdecl lego::util::memSwap(void* ptr1, void* ptr2, unsigned int count)
{
	if (ptr1 != ptr2) {
		char* swap_ptr1 = (char*)ptr1;
		char* swap_ptr2 = (char*)ptr2;
		while (count-- != 0) {
			char swap = *swap_ptr1;
			*swap_ptr1++ = *swap_ptr2;
			*swap_ptr2++ = swap;
		}
	}
}

// <LegoRR.exe @0048e2f0>
void __cdecl lego::util::memSwap(void* ptr1, void* ptr2, unsigned int count)
{
	if (ptr1 != ptr2) {
		char* swap_ptr1 = (char*)ptr1;
		char* swap_ptr2 = (char*)ptr2;
		while (count-- != 0) {
			char swap = *swap_ptr1;
			*swap_ptr1++ = *swap_ptr2;
			*swap_ptr2++ = swap;
		}
	}
}

// <LegoRR.exe @0048e2f0>
void __cdecl lego::util::memSwap(unsigned char* ptr1, unsigned char* ptr2, unsigned int count)
{
	if (ptr1 != ptr2) {
		while (count-- != 0) {
			unsigned char swap = *ptr1;
			*ptr1++ = *ptr2;
			*ptr2++ = swap;
		}
	}
}

// <LegoRR.exe @0048e290>
void __cdecl FUN_0048e290(unsigned char* ptr1, unsigned char* ptr2, unsigned int elementSize, CompareCallback compare)
{
	unsigned char* dest1, item1;
	
	while (ptr1 < ptr2) {
		item1 = ptr1 + elementSize;
		dest1 = ptr1;
		for (; item1 <= ptr2; item1 += elementSize) {
			if (compare(item1, dest1) > 0) {
				dest1 = item1;
			}
		}
		lego::util::memSwap(dest1, ptr2, elementSize);
		ptr2 -= elementSize;
	}
	return;
}

// <LegoRR.exe @0048e290>
void __cdecl FUN_0048e290(unsigned char* ptr1, unsigned char* ptr2, unsigned int elementSize, CompareCallback compare)
{
	unsigned char* puVar1;
	int iVar2;
	unsigned char* puVar3;

	unsigned char* item = ptr1 + elementSize;
	// puVar1 = ptr1 + elementSize;
	dest = ptr1;
	while (ptr1 < ptr2) {
		for (; item <= ptr2; item += elementSize) {
			iVar2 = ;
			if ((*(code *)compare)(item, dest) > 0) {
				dest = item;
			}
		}
		lego::util::memSwap(dest, ptr2, elementSize);
		ptr2 -= elementSize;
		item += elementSize;
		dest = ptr1;
	}
	if (param_1 < param_2) {
		puVar1 = param_1 + elementSize;
		puVar3 = param_1;
		do {
			for (; puVar1 <= param_2; puVar1 = puVar1 + elementSize) {
				iVar2 = (*(code *)compare)(puVar1, puVar3);
				if (iVar2 > 0) {
					puVar3 = puVar1;
				}
			}
			lego::util::memSwap(puVar3, param_2, elementSize);
			param_2 -= elementSize;
			puVar1 = param_1 + elementSize;
			puVar3 = param_1;
		} while (param_1 < param_2);
	}
	return;
}

/// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/qsort?view=msvc-160>
// <LegoRR.exe @0048e0e0>
void __cdecl qsort(void* base, size_t number, size_t width, int (__cdecl* compare)(const void *, const void *));
// Sorting algorithm
// <LegoRR.exe @0048e0e0>
void __cdecl qsort(unsigned char* param_1, unsigned int count, unsigned int elementSize, CompareCallback compare)
{
	uint uVar1;
	int iVar2;
	undefined *puVar3;
	undefined *puVar4;
	// undefined *local_100;
	// undefined4 *local_fc;
	// undefined4 *local_f8;
	// int local_f4;
	unsigned int local_f0[30];
	unsigned int local_78[30];
	
	if (count < 2 || elementSize == 0)
		return;

	unsigned char* local_100 = param_1 + (count - 1) * elementSize; // last element
	unsigned int* local_fc = local_f0;
	unsigned int* local_f8 = local_78;
	int local_f4 = 0;

	while (local_f4 >= 0) {
		// unsigned int uVar1 = (unsigned int)(local_100 - (int)param_1) / elementSize + 1;
		if (((unsigned int)(local_100 - (int)param_1) / elementSize) >= 8) {
		// if (uVar1 > 8) {
			lego::util::memSwap(param_1 + (uVar1 / 2) * elementSize, param_1, elementSize);
			puVar4 = local_100 + elementSize;
			// puVar3 = param_1;
		// LAB_0048e1ae:
			puVar3 = param_1 + elementSize;
			if (puVar3 <= local_100) {
				while ( compare(puVar3, param_1) < 1) {
					puVar3 += elementSize;
				}
				// do {
				// 	iVar2 = compare(puVar3, param_1);
				//  (iVar2 <= 0);
			}
			// if (puVar3 <= local_100) goto code_r0x0048e1b8;
			// goto LAB_0048e1c8;

			do {
				puVar4 -= elementSize;
				if (puVar4 <= param_1) break;
				// iVar2 = compare(puVar4, param_1);
			} while (compare(puVar4, param_1) >= 0);
			if (puVar3 <= puVar4) {
				lego::util::memSwap(puVar3, puVar4, elementSize);
				goto LAB_0048e1ae;
			}
		}
		else {
			FUN_0048e290(param_1, local_100, elementSize, compare);
		}
	}

LAB_0048e134:
	uVar1 = (uint)(local_100 - (int)param_1) / elementSize + 1;
	if (uVar1 > 8) {
		lego::util::memSwap(param_1 + (uVar1 / 2) * elementSize, param_1, elementSize);
		puVar4 = local_100 + elementSize;
		puVar3 = param_1;
	LAB_0048e1ae:
		puVar3 = puVar3 + elementSize;
		if (puVar3 <= local_100) goto code_r0x0048e1b8;
		goto LAB_0048e1c8;
	}
	FUN_0048e290(param_1, local_100, elementSize, compare);
	goto LAB_0048e155;
code_r0x0048e1b8:
	// iVar2 = compare(puVar3, param_1);
	if (compare(puVar3, param_1) < 1) goto LAB_0048e1ae;
LAB_0048e1c8:
	do {
		puVar4 = puVar4 - elementSize;
		if (puVar4 <= param_1) break;
		// iVar2 = compare(puVar4, param_1);
	} while (compare(puVar4, param_1) >= 0);
	if (puVar3 <= puVar4) {
		lego::util::memSwap(puVar3, puVar4, elementSize);
		goto LAB_0048e1ae;
	}
	lego::util::memSwap(param_1, puVar4, elementSize);
	if ((int)(puVar4 + (-1 - (int)param_1)) < (int)(local_100  - (int)puVar3)) {
		if (puVar3 < local_100) {
			*local_f8++ = puVar3;
			*local_fc++ = local_100;
			local_f4++;
			// local_f8++;
			// local_fc++;
		}
		if (param_1 + elementSize < puVar4) {
			local_100 = puVar4 - elementSize;
			goto LAB_0048e134;
		}
	}
	else {
		if (param_1 + elementSize < puVar4) {
			*local_f8++ = param_1;
			*local_fc++ = puVar4 - elementSize;
			local_f4++;
			// local_f8++;
			// local_fc++;
		}
		param_1 = puVar3;
		if (puVar3 < local_100) goto LAB_0048e134;
	}
LAB_0048e155:
	local_f4--;
	local_f8--;
	local_fc--;
	if (local_f4 < 0) {
		return;
	}
	local_100 = (undefined *)*local_fc;
	param_1 = (undefined *)*local_f8;
	goto LAB_0048e134;
}


