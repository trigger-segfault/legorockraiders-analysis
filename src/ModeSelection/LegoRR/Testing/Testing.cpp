// Testing.cpp : Defines game testing and dummy functions.
//

#include "Testing.h"
#include "../Main/Main.h"
#include "../Drawing/DirectDraw.h"
#include "../Drawing/Images.h"
#include "../Drawing/SurfaceLock.h"
#include "../Controls/Input.h"
#include "../IO/Files.h"

#ifndef DEBUG_REMOVEUNUSED
#include "../IO/CFG.h"
#include "../Audio/Sound.h"
#endif


//////// TESTING CONFIG ////////

// Disable testing memory inspection of a running instance of LegoRR.exe

#define DISABLE_MEMORYINSPECT


#ifndef DISABLE_MEMORYINSPECT
#include "MemoryInspect.h"
#endif

using namespace lego;
using namespace testing;

#ifndef DISABLE_MEMORYINSPECT
using namespace inspect;
#endif


#pragma region Globals

//static IDirectDrawSurface4* bmpFont;
#define bmpWidth 130
#define bmpHeight 266
#define fontWidth 13
#define fontHeight 14
#define fontRows 19
#define fontCols 10

static unsigned char* fontData;
static ColourRGBI fontColors[256];
static unsigned int fontColors2[256];
static unsigned char fontPixels[130 * 266];
static unsigned char fontChars[91][fontHeight][fontWidth];
static unsigned int fontCharWidths[91];

static ColourRGBI backColor = { 0, 0, 0 };
static unsigned int backColor2; // = { 0, 0, 0 };

static int mybpp;
static int counter = 0;

// <LegoRR.exe @005775e0>
static const char* g_KEYS_TABLE[256]; // (confirmed size)

#pragma endregion


// entire function just initializes this array (and zeros out unused slots)
// <LegoRR.exe @00485ce0>
static void __cdecl InitKeyNames(void) {
    // memset(g_KEYS_TABLE, 0, 256 * sizeof(unsigned char*));
    for (int i = 0; i < 256; i++)
        g_KEYS_TABLE[i] = nullptr;

    g_KEYS_TABLE[1] = "KEY_ESCAPE";
    g_KEYS_TABLE[2] = "KEY_ONE";
    g_KEYS_TABLE[3] = "KEY_TWO";
    g_KEYS_TABLE[4] = "KEY_THREE";
    g_KEYS_TABLE[5] = "KEY_FOUR";
    g_KEYS_TABLE[6] = "KEY_FIVE";
    g_KEYS_TABLE[7] = "KEY_SIX";
    g_KEYS_TABLE[8] = "KEY_SEVEN";
    g_KEYS_TABLE[9] = "KEY_EIGHT";
    g_KEYS_TABLE[10] = "KEY_NINE";
    g_KEYS_TABLE[11] = "KEY_ZERO";
    g_KEYS_TABLE[12] = "KEY_MINUS";
    g_KEYS_TABLE[13] = "KEY_EQUALS";
    g_KEYS_TABLE[14] = "KEY_BACKSPACE";
    g_KEYS_TABLE[15] = "KEY_TAB";
    g_KEYS_TABLE[16] = "KEY_Q";
    g_KEYS_TABLE[17] = "KEY_W";
    g_KEYS_TABLE[18] = "KEY_E";
    g_KEYS_TABLE[19] = "KEY_R";
    g_KEYS_TABLE[20] = "KEY_T";
    g_KEYS_TABLE[21] = "KEY_Y";
    g_KEYS_TABLE[22] = "KEY_U";
    g_KEYS_TABLE[23] = "KEY_I";
    g_KEYS_TABLE[24] = "KEY_O";
    g_KEYS_TABLE[25] = "KEY_P";
    g_KEYS_TABLE[26] = "KEY_LEFTBRACE";
    g_KEYS_TABLE[27] = "KEY_RIGHTBRACE";
    g_KEYS_TABLE[28] = "KEY_RETURN";
    g_KEYS_TABLE[29] = "KEY_LEFTCTRL";
    g_KEYS_TABLE[30] = "KEY_A";
    g_KEYS_TABLE[31] = "KEY_S";
    g_KEYS_TABLE[32] = "KEY_D";
    g_KEYS_TABLE[33] = "KEY_F";
    g_KEYS_TABLE[34] = "KEY_G";
    g_KEYS_TABLE[35] = "KEY_H";
    g_KEYS_TABLE[36] = "KEY_J";
    g_KEYS_TABLE[37] = "KEY_K";
    g_KEYS_TABLE[38] = "KEY_L";
    g_KEYS_TABLE[39] = "KEY_SEMICOLON";
    g_KEYS_TABLE[40] = "KEY_AT";
    g_KEYS_TABLE[41] = "KEY_RSINGLEQUOTE";
    g_KEYS_TABLE[42] = "KEY_LEFTSHIFT";
    g_KEYS_TABLE[43] = "KEY_HASH";
    g_KEYS_TABLE[44] = "KEY_Z";
    g_KEYS_TABLE[45] = "KEY_X";
    g_KEYS_TABLE[46] = "KEY_C";
    g_KEYS_TABLE[47] = "KEY_V";
    g_KEYS_TABLE[48] = "KEY_B";
    g_KEYS_TABLE[49] = "KEY_N";
    g_KEYS_TABLE[50] = "KEY_M";
    g_KEYS_TABLE[51] = "KEY_LEFTARROW";
    g_KEYS_TABLE[52] = "KEY_RIGHTARROW";
    g_KEYS_TABLE[53] = "KEY_QUESTIONMARK";
    g_KEYS_TABLE[54] = "KEY_RIGHTSHIFT";
    g_KEYS_TABLE[55] = "KEYPAD_ASTERISK";
    g_KEYS_TABLE[56] = "KEY_ALT";
    g_KEYS_TABLE[57] = "KEY_SPACE";
    g_KEYS_TABLE[58] = "KEY_CAPLOCK";
    g_KEYS_TABLE[59] = "KEY_F1";
    g_KEYS_TABLE[60] = "KEY_F2";
    g_KEYS_TABLE[61] = "KEY_F3";
    g_KEYS_TABLE[62] = "KEY_F4";
    g_KEYS_TABLE[63] = "KEY_F5";
    g_KEYS_TABLE[64] = "KEY_F6";
    g_KEYS_TABLE[65] = "KEY_F7";
    g_KEYS_TABLE[66] = "KEY_F8";
    g_KEYS_TABLE[67] = "KEY_F9";
    g_KEYS_TABLE[68] = "KEY_F10";
    g_KEYS_TABLE[69] = "KEYPAD_NUMLOCK";
    g_KEYS_TABLE[70] = "KEY_SCROLLLOCK";
    g_KEYS_TABLE[71] = "KEYPAD_7";
    g_KEYS_TABLE[72] = "KEYPAD_8";
    g_KEYS_TABLE[73] = "KEYPAD_9";
    g_KEYS_TABLE[74] = "KEYPAD_MINUS";
    g_KEYS_TABLE[75] = "KEYPAD_4";
    g_KEYS_TABLE[76] = "KEYPAD_5";
    g_KEYS_TABLE[77] = "KEYPAD_6";
    g_KEYS_TABLE[78] = "KEYPAD_PLUS";
    g_KEYS_TABLE[79] = "KEYPAD_1";
    g_KEYS_TABLE[80] = "KEYPAD_2";
    g_KEYS_TABLE[81] = "KEYPAD_3";
    g_KEYS_TABLE[82] = "KEYPAD_0";
    g_KEYS_TABLE[83] = "KEYPAD_DELETE";
    g_KEYS_TABLE[86] = "KEY_BACKSLASH";
    g_KEYS_TABLE[87] = "KEY_F11";
    g_KEYS_TABLE[88] = "KEY_F12";
    g_KEYS_TABLE[156] = "KEYPAD_ENTER";
    g_KEYS_TABLE[157] = "KEY_RIGHTCTRL";
    g_KEYS_TABLE[181] = "KEYPAD_FORWARDSLASH";
    g_KEYS_TABLE[183] = "KEY_PRINTSCREEN";
    g_KEYS_TABLE[184] = "KEY_ALTGR";
    g_KEYS_TABLE[199] = "KEY_HOME";
    g_KEYS_TABLE[200] = "KEY_CURSORUP";
    g_KEYS_TABLE[201] = "KEY_PGUP";
    g_KEYS_TABLE[203] = "KEY_CURSORLEFT";
    g_KEYS_TABLE[205] = "KEY_CURSORRIGHT";
    g_KEYS_TABLE[207] = "KEY_END";
    g_KEYS_TABLE[208] = "KEY_CURSORDOWN";
    g_KEYS_TABLE[209] = "KEY_PGDN";
    g_KEYS_TABLE[210] = "KEY_INSERT";
    g_KEYS_TABLE[211] = "KEY_DELETE";
}


static void __cdecl DrawClear(int x, int y, int x2, int y2) {
    for (int dy = y; dy < y2; dy++) {
        if (dy >= 0 && dy < GetResolutionHeight()) {
            for (int dx = x; dx < x2; dx++) {
                if (dx >= 0 && dx < GetResolutionWidth()) {
                    draw::Draw_SetSurfacePixel(dx, dy, backColor2);
                }
            }
        }
    }
}

static void __cdecl DrawFontChar(int x, int y, char c) {
    if (c < ' ' || c > 'z')
        return;
    //if ()
    int idx = (c - ' ');
    int srcx = (idx % fontCols) * fontWidth;
    int srcy = (idx / fontCols) * fontHeight;
    int endx = srcx + fontWidth;
    int endy = srcy + fontHeight;
    for (int j = 0; j < fontHeight; j++) {
        int dy = j + y;
        if (dy >= 0 && dy < GetResolutionHeight()) {
            for (int i = 0; i < fontWidth; i++) {
                int dx = i + x;
                if (dx >= 0 && dx < GetResolutionWidth()) {
                    unsigned char pixel = fontChars[idx][j][i];
                    unsigned int color = (pixel != 0xff /*&& pixel != 0x00*/ ? fontColors2[pixel] : backColor2);
                    draw::Draw_SetSurfacePixel(dx, dy, color);
                }
            }
        }
    }
}

#ifndef DISABLE_MEMORYINSPECT

#define RV_CDTRACKS (RVAddress)0x00557f10
#define RV_GAMEDATA (RVAddress)0x005570c0

struct Struct_2c
{
    /*00,4*/ unsigned int field_0;
    /*04,4*/ unsigned int field_4;
    /*08,4*/ unsigned int field_8;
    /*0c,4*/ unsigned int field_c;
    /*10,4*/ unsigned int field_10;
    /*14,4*/ unsigned int field_14;
    /*18,4*/ unsigned int field_18;
    /*1c,4*/ unsigned int field_1c;
    /*20,4*/ unsigned int field_20;
    /*24,4*/ unsigned int field_24;
    /*28,4*/ unsigned int field_28;
    /*2c*/
};

typedef unsigned int undefined4;
typedef void Struct_830;
typedef void VehicleData;
typedef void MiniFigureData;
typedef void RockMonsterData;
typedef void BuildingData;
typedef void UpgradeData;
typedef void MiscObjectData;
typedef unsigned int GameFlags1;
typedef unsigned int GameFlags2;
typedef unsigned int GameFlags3;

#ifdef DEBUG_REMOVEUNUSED
namespace lego {
namespace CFG {
    struct CFGProperty { int dummy; };
}
}
#endif

struct GameData
{
    /*DAT_005570c0*/

    /*000,4*/ CFG::CFGProperty* g_LegoCfgRoot;
    /*004,4*/ const char* g_CFG_ROOTPATH;
    /*008,4*/ undefined4 field_8;
    /*00c,4*/ undefined4 field_c;
    /*010,4*/ main::GraphicsQuality Quality; //g_GraphicsQuality; // DAT_005570d0
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

#define ReadPtr(name) \
    do { if (!gameData.name) break; \
        RVAddress rvptr_ = inspect::ResolvePointer((RVAddress)gameData.name); \
        if (rvptr_) { MyBuffer* bufptr_ = (MyBuffer*)std::malloc(sizeof(MyBuffer)); \
        std::memset(bufptr_, 0, sizeof(MyBuffer)); \
        ptrBuffers[((signed long long)&gameData.name - (signed long long)&gameData) / 4] = bufptr_; \
        inspect::ReadMemory(rvptr_, bufptr_, sizeof(MyBuffer)); \
    } } while (0)

struct MyBuffer {
    unsigned int d[1024 * 3];
};
#endif

BOOL __cdecl testing::MyGameInitFunction(void)
{
    _finddata32_t fileinfo;
    intptr_t handle = _findfirst32("*.*", &fileinfo);
    debugf("_findfirst\n");
    if (handle != -1) {
        do {
            debugf("_findnext  %c  %s\n", (char)((fileinfo.attrib & FILE_ATTRIBUTE_DIRECTORY) ? 'D' : ' '), fileinfo.name);
            if ((fileinfo.attrib & FILE_ATTRIBUTE_DIRECTORY) != 0 && _stricmp(fileinfo.name, "Data") == 0) {
                debugf("Data found!!\n");
                break;
            }
        } while (_findnext32(handle, &fileinfo) == 0);
        _findclose(handle);
        debugf("_findclose\n");
    }

    #ifndef DISABLE_MEMORYINSPECT
    MyBuffer* ptrBuffers[0xef8 / 4];
    std::memset(ptrBuffers, 0, sizeof(ptrBuffers));
    inspect::InitMemoryInspect();
    unsigned int gameDataBuf[0xef8 / 4];
    unsigned int cdTracks = 0;
    GameData gameData;
    assert(sizeof(gameDataBuf) == sizeof(gameData));
    if (inspect::ReadMemory(RV_GAMEDATA, &gameDataBuf, sizeof(gameDataBuf)) != sizeof(gameDataBuf)) {
        debugf("FAILED: ReadMemory(RV_GAMEDATA)\n");
    }
    else {
        std::memcpy(&gameData, gameDataBuf, sizeof(gameDataBuf));
        debugf("GAMEDATA:\n");
        for (size_t i = 0; i < (sizeof(gameDataBuf) / 4); i++) {
            debugf(" [%0.3x] : %0.8x (%.12i) <%f>\n", (unsigned int)i*4, gameDataBuf[i], *(int*)&gameDataBuf[i], *(float*)&gameDataBuf[i]);
        }
        ReadPtr(g_LegoCfgRoot);
        ReadPtr(g_CFG_ROOTPATH);
        ReadPtr(level);
        ReadPtr(PTR_005570d8);
        ReadPtr(PTR_005570dc);
        ReadPtr(PTR_005570e4);

        ReadPtr(PTR_005570f0);
        ReadPtr(PTR_005570f8);
        ReadPtr(PTR_005570fc);
        ReadPtr(PTR_00557100);
        ReadPtr(PTR_00557104);
        ReadPtr(PTR_00557108);
        ReadPtr(PTR_0055710c);
        ReadPtr(g_FONT_FONT5_HI);
        ReadPtr(g_FONT_ToolTipFont);
        ReadPtr(g_FONT_DeskTopFont);
        ReadPtr(g_FONT_font5_HI);
        ReadPtr(g_FONT_MbriefFONT);
        ReadPtr(g_FONT_MbriefFONT2);
        ReadPtr(g_FONT_RSFont);
        ReadPtr(PTR_00557140);
        ReadPtr(PTR_00557144);
        debugf("GameData : %0.8x\n", gameData.g_LegoCfgRoot);
    }
    for (size_t i = 0; i < (sizeof(ptrBuffers) / sizeof(MyBuffer*)); i++) {
        if (ptrBuffers[i]) {
            std::free(ptrBuffers[i]);
            ptrBuffers[i] = nullptr;
        }
    }
    /*if (inspect::ReadMemory(RV_CDTRACKS, &cdTracks, 4) != 4) {
        debugf("FAILED: ReadMemory(RV_CDTRACKS)\n");
    }
    else {
        debugf("CDTRACKS: %u\n", cdTracks);
    }*/
    //SetGameWindowTitle(globals::g_ExeName); // "LEGO Rock Raiders (interface)");
    #endif

    mybpp = main::GetDeviceBitsPerPixel();
    InitKeyNames();
    unsigned int outLength = 0;
    size_t length;
    fontData = file::File_ReadAllBytes("Interface/Fonts/Font5_Hi.bmp", &outLength);
    if (fontData == nullptr) {
        debugf("FAILED: File_ReadAllBytes\n");
    }
    length = outLength;
    /*FILE* file = std::fopen("C:/Users/Onii-chan/OneDrive/Games/LRR_/games/base+master+dgv2554+d3drm+cafe/Data/Interface/Fonts/Font5_Hi.bmp", "rb");
    std::fseek(file, 0, SEEK_END);
    size_t length = (size_t)std::ftell(file);
    std::fseek(file, 0, SEEK_SET);
    fontData = (unsigned char*)std::malloc(length);
    if (!std::fread(fontData, length, 1, file)) {
        debugf("FAILED: fread\n");
        return FALSE;
    }
    std::fclose(file);
    file = nullptr;*/
    std::memset(fontColors, 0, sizeof(fontColors));
    //int numColors = *(unsigned int*)(fontData + 0x32)
    for (int i = 0; i < 256; i++) {
        fontColors[i].red   = fontData[0x36 + i * 4 + 2];
        fontColors[i].green = fontData[0x36 + i * 4 + 1];
        fontColors[i].blue  = fontData[0x36 + i * 4 + 0];
        fontColors2[i] = image::packNativeRGB(draw::GetDrawingSurface(),
            fontColors[i].red | (fontColors[i].green << 8) | (fontColors[i].blue << 16));
    }
    backColor2 = image::packNativeRGB(draw::GetDrawingSurface(), 0);
    int stride = (bmpWidth + 3) & ~0x3;
    for (int j = 0; j < bmpHeight; j++) {
        int row = j / fontHeight;
        int fy = j % fontHeight;
        for (int i = 0; i < bmpWidth; i++) {
            int col = i / fontWidth;
            int idx = col + row * fontCols;
            if (idx > 90)
                continue;
            int fx = i % fontWidth;
            int bidx = (bmpHeight - 1 - j) * stride + i;
            unsigned char pixel = fontData[0x436 + bidx];
            fontChars[idx][fy][fx] = pixel;
            if (fontCharWidths[idx] == 0)
                fontCharWidths[idx] = fontWidth;
            if (pixel == 0xff && fontCharWidths[idx] == fontWidth) {
                fontCharWidths[idx] = fx;
            }
        }
    }

    #ifndef DEBUG_REMOVEUNUSED
    sound::Music_PlayNext(TRUE);
    #endif

    ShowCursor(TRUE);

    srand((unsigned int)(nullptr));

    return TRUE;
}


BOOL __cdecl testing::MyGameUpdateFunction(float ellapsed)
{
    int mx = input::GetMousePositionX();
    int my = input::GetMousePositionY();
    int dx = input::globals::g_MouseDeltaPosition.x;
    int dy = input::globals::g_MouseDeltaPosition.y;
    if ((dx || dy)) {
        counter++;
    }

    #ifndef DEBUG_REMOVEUNUSED
    sound::Music_Update(TRUE);
    #endif

    if (fontData != nullptr) {
    if (/*(dx != 0 || dy != 0) &&*/ mx >= 0 && mx < GetResolutionWidth() && my >= 0 && my < GetResolutionHeight()) {
        Rect2F rect = { 0.0f, 0.0f, (float)GetResolutionWidth(), (float)fontHeight + 9.0f };
        if (draw::FillSurface(&rect, backColor2) != 0) {
            debugf("FAILED: Draw_SurfaceFillBack\n");
            return FALSE;
        }
        if (!draw::Draw_SurfaceLock(draw::GetDrawingSurface(), 0)) {
            debugf("FAILED: Draw_SurfaceLock\n");
            return FALSE;
        }
        draw::Draw_SurfaceLock_Translate(nullptr);

        if ((dx || dy) && (GetCapture() == main::globals::g_hWnd || (lego::globals::g_CMDLINE_FLAGS & CMD_FULLSCREEN))) {
            unsigned int color = (unsigned int)(rand() & 0xfff) | (((unsigned int)rand() & 0xfff) << 12);// &0xffffffff;
            draw::Draw_SetSurfacePixel(mx, my, color);
        }

        unsigned int color = (*(unsigned int*)&ellapsed) & 0xffffff;
        DrawClear(0, 0, GetResolutionWidth(), fontHeight * 5 + 11);
        char buffer[4096];
        int len = std::sprintf(buffer, "ellapse: %f", ellapsed);
        int ty = 8;
        for (int i = 0, x = 3; i < len; i++) {
            DrawFontChar(x, ty, buffer[i]);
            if (buffer[i] >= ' ' && buffer[i] <= 'z') {
                x += fontCharWidths[buffer[i] - ' '];
            }
        }
        ty += fontHeight + 2;
        len = std::sprintf(buffer, "movements: %i", counter);
        for (int i = 0, x = 3; i < len; i++) {
            DrawFontChar(x, ty, buffer[i]);
            if (buffer[i] >= ' ' && buffer[i] <= 'z') {
                x += fontCharWidths[buffer[i] - ' '];
            }
        }
        //buffer[0] = '\0';
        len = std::sprintf(buffer, "keys: ");
        for (int k = 0, kk = 0; k < 256; k++) {
            if (input::globals::g_KeyboardState_Current_TABLE[k] && g_KEYS_TABLE[k]) {
                //const char* keyName = g_KEYS_TABLE[k];
                if (k == DIK_ESCAPE)
                    return FALSE;
                if (kk++)
                    strcat(buffer, ", ");
                strcat(buffer, g_KEYS_TABLE[k]);
            }
        }
        ty += fontHeight + 2;
        len = (int)std::strlen(buffer);
        //len = std::sprintf(buffer, "keys: %s", counter);
        for (int i = 0, x = 3; i < len; i++) {
            DrawFontChar(x, ty, buffer[i]);
            if (buffer[i] >= ' ' && buffer[i] <= 'z') {
                x += fontCharWidths[buffer[i] - ' '];
            }
        }

        ty += fontHeight + 2;
        len = std::sprintf(buffer, "screen: %ix%i (%i-bit)   mouse: %i,%i (%i,%i)  buttons: %i,%i", GetResolutionWidth(), GetResolutionHeight(), mybpp, mx, my, dx, dy, input::globals::g_LeftButtonState, input::globals::g_RightButtonState);// directx::GetDeviceBitsPerPixel());
        for (int i = 0, x = 3; i < len; i++) {
            DrawFontChar(x, ty, buffer[i]);
            if (buffer[i] >= ' ' && buffer[i] <= 'z') {
                x += fontCharWidths[buffer[i] - ' '];
            }
        }

        draw::Draw_SurfaceUnlock(draw::GetDrawingSurface());
    }
    }

    #ifndef DEBUG_REMOVEUNUSED
    //KEY_M /*50*/
    if (!input::globals::g_KeyboardState_Previous_TABLE[50] && input::globals::g_KeyboardState_Current_TABLE[50])
        sound::Music_PlayNext(TRUE);
    #endif

    return TRUE;
}

BOOL __cdecl testing::MyGameUpdateFunctionOld(float ellapsed)
{
    int x = input::GetMousePositionX();
    int y = input::GetMousePositionY();
    int dx = input::globals::g_MouseDeltaPosition.x;
    int dy = input::globals::g_MouseDeltaPosition.y;
    if ((dx != 0 || dy != 0) && x >= 0 && x < GetResolutionWidth() && y >= 0 && y < GetResolutionHeight()) {
        if (!draw::Draw_SurfaceLock(draw::GetDrawingSurface(), 0)) {
            debugf("FAILED: Draw_SurfaceLock\n");
            return FALSE;
        }
        draw::Draw_SurfaceLock_Translate(nullptr);

        unsigned int color = (*(unsigned int*)&ellapsed) & 0xffffff;

        draw::Draw_SetSurfacePixel(x, y, color);

        draw::Draw_SurfaceUnlock(draw::GetDrawingSurface());
    }
    return TRUE;
}

void __cdecl testing::MyGameCleanupFunction(void)
{
    #ifndef DISABLE_MEMORYINSPECT
    inspect::CleanupMemoryInspect();
    #endif

    if (fontData != nullptr) {
        std::free(fontData);
        fontData = nullptr;
    }
}

