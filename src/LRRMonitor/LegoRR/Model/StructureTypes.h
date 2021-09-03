#pragma once

#include "../../framework.h"
#include "GhidraTypes.h"
#include "EnumTypes.h"
#include "BasicTypes.h"
#include "FunctionTypes.h"
#include "D3DTypes.h"


#pragma pack(push, 1)

namespace lego {
#pragma region Predeclarations

struct ResourceData;
struct LiveObject;
struct LevelBlock;
struct Level;
struct FlockData;
struct LwoFrame;
struct FlockSubdata;
struct ResourceSubdata;
struct ActStruct_14;
struct CreatureData;
struct Struct_34;
struct ObjectStats;
struct UpgradeData;
struct ObjectUpgradePartData;
struct ObjectUpgradesData;
struct BuildingData;
struct PolyMeshData;
struct VehicleData;
struct Struct_830;
struct Struct_bc;
struct GameManager;
struct LevelStruct_3c;
struct LevelStruct_1c;
struct SurfaceMapStruct38;
struct ImageBMP;
struct SurfaceTextureGrid;
struct LevelSurfaceMap;
struct DirectXSurfaceTuple;
struct BlockPointer;
struct LevelData;
struct ObjectiveData;
struct ImageFont;
struct FileStream;
struct FileWADStream;
struct LoaderProfileItem;
struct HelpWindowInfoLevels;
struct WADEntry;
struct WADFile;
struct RenderStateItem;
struct DeviceMode;
struct DriverMode;
struct ScreenMode;
struct SharedObjectResource;
struct ToolTipData;
struct ErodeState;
struct SharedTextureResource;
struct FileBuffer;
struct MiscObjectDependencies;
struct WADStream;
struct ResourceManager;
struct NERPSFunctionSignature;
struct SampleProperty;
struct SampleData;
struct AudioPlaybackData;
struct NERPMessageSound;
struct AdvisorAnimData;
struct SelectedUnitHotkey;
struct BasicObjectData;
struct ItemStruct_428;
struct Struct_428;
struct MapFileInfo;
struct BlockObject;
struct Struct_b8__00558080;
struct Struct_8__00558bc4;
struct PairStruct_428;
struct SoundResource;
struct ResourceAppData;
struct ActFrameResource;
struct MessageAction;
struct ProMeshData;
struct LevelIdentifier;
struct Sound3DInstance;
struct LiveObjectInfo;
struct MiscObjectData;
struct StructF_10;
struct CFGProperty;

#pragma endregion


#pragma region Structure Types

struct GameFunctions
{
	/*0,4*/ GameInitFunction Init;
	/*4,4*/ GameUpdateFunction Update;
	/*8,4*/ GameCleanupFunction Cleanup;
	/*c*/
};
static_assert(sizeof(GameFunctions) == 0xc, "");


struct StructF_10
{
	/*00,4*/ float float_0;
	/*04,4*/ float float_4;
	/*08,4*/ undefined4 field_8;
	/*0c,4*/ float float_c;
	/*10*/
};
static_assert(sizeof(StructF_10) == 0x10, "");

struct LevelIdentifier
{
	/*00,4*/ undefined4 field_0;
	/*04,4*/ undefined4 field_4;
	/*08,4*/ undefined4 field_8;
	/*0c,4*/ undefined4 field_c;
	/*10,4*/ undefined4 field_10;
	/*14*/
};
static_assert(sizeof(LevelIdentifier) == 0x14, "");

struct Sound3DInstance
{
	/*00,4*/ int sampleIndex;
	/*04,4*/ IDirect3DRMFrame3* frame;
	/*08,c*/ Vector3F position;
	/*14,4*/ unsigned int flags;
	/*18*/
};
static_assert(sizeof(Sound3DInstance) == 0x18, "");

struct LiveObjectInfo
{
	/*00,4*/ LiveObject* liveObj;
	/*04,4*/ BOOL intbool_4;
	/*08,8*/ Point2F point_8;
	/*10,c*/ Vector3F vector_10;
	/*1c*/
};
static_assert(sizeof(LiveObjectInfo) == 0x1c, "");

struct MiscObjectData
{
	/*00,30*/ undefined field_0x0_0x30[0x30];
	/*30,4*/ ResourceData* resData; // LWS,true | LWO,true
	/*34,4*/ undefined field_0x34_0x38[0x4];
	/*38*/
};
static_assert(sizeof(MiscObjectData) == 0x38, "");

struct ProMeshData
{
	/*000,4*/ ResourceData* promesh_a;
	/*004,4*/ ResourceData* promesh_b;
	/*008,190*/ undefined4 table_a[100];
	/*198,190*/ undefined4 table_b[100];
	/*328,4*/ float BlockSize;
	/*32c,4*/ undefined4 field_32c;
	/*330,c*/ undefined field_0x330_0x33c[0xc];
	/*33c,4*/ SurfaceTextureGrid* surfTextGrid;
	/*340*/
};
static_assert(sizeof(ProMeshData) == 0x340, "");

struct MessageAction
{
	/*00,4*/ MessageType event;
	/*04,4*/ LiveObject* object_4;
	/*08,4*/ undefined4 field_8;
	/*0c,4*/ undefined4 field_c;
	/*10,4*/ undefined4 field_10;
	/*14*/
};
static_assert(sizeof(MessageAction) == 0x14, "");

struct ActFrameResource
{
	/*00,4*/ ActFrameResource* previous;
	/*04,4*/ void* lwsStruct38; // LWS struct
	/*08,4*/ IDirect3DRMAnimationSet2* animSet; // (not LWS)
	/*0c,4*/ BOOL isLWSFile;
	/*10,4*/ IDirect3DRMFrame3* rootFrame; // (not LWS)
	/*14,4*/ IDirect3DRMFrame3** framesTable; // (not LWS) table of COM objects, length is count_18
	/*18,4*/ unsigned int framesCount; // (not LWS)
	/*1c,4*/ undefined4 field_1c;
	/*20*/
};
static_assert(sizeof(ActFrameResource) == 0x20, "");

struct ResourceAppData
{
	/*00,4*/ ResourceData* resData;
	/*04,4*/ char* filename;
	/*08,4*/ char* frameName;
	/*0c,4*/ undefined4 field_c;
	/*10,4*/ float float_10;
	/*14,4*/ float float_14;
	/*18,4*/ char* sampleName;
	/*1c,4*/ ActFrameResource* actFrameRes;
	/*20,4*/ undefined4 field_20;
	/*24,4*/ SoundResource* soundRes;
	/*28*/
};
static_assert(sizeof(ResourceAppData) == 0x28, "");


struct SoundResource
{
	/*00,4*/ IDirectSound3DBuffer* sound3dBuffer;
	/*04,4*/ undefined4 field_4;
	/*08,4*/ undefined4 field_8;
	/*0c,4*/ undefined4 field_c;
	/*10,4*/ SoundResource* previous;
	/*14*/
};
static_assert(sizeof(SoundResource) == 0x14, "");

struct Struct_8__00558bc4
{
	/*0,4*/ LiveObject* object_0;
	/*4,4*/ float float_4;
	/*8*/
};
static_assert(sizeof(Struct_8__00558bc4) == 0x8, "");

struct PairStruct_428
{
	/*0,4*/ Struct_428* first;
	/*4,4*/ Struct_428* second;
	/*8*/
};
static_assert(sizeof(PairStruct_428) == 0x8, "");

struct Struct_b8__00558080
{
	/*00,b8*/ undefined field_0x0_0xb8[0xb8];
	/*b8*/
};
static_assert(sizeof(Struct_b8__00558080) == 0xb8, "");

struct MapFileInfo
{
	/*00,4*/ char Signature[4]; // "MAP "
	/*04,4*/ unsigned int fileSize;
	/*08,8*/ Size2I dimensions;
	/*10,2*/ unsigned short blocks[1];
	/*12*/
};
static_assert(sizeof(MapFileInfo) == 0x12, "");

struct BlockObject
{
	/*00,4*/ LiveObject* attachedObject;
	/*04,8*/ Point2I position;
	/*0c,4*/ undefined4 field_c;
	/*10,4*/ BlockObject* pool_m_next;
	/*14*/
};
static_assert(sizeof(BlockObject) == 0x14, "");

struct ItemStruct_428
{
	/*00,4*/ unsigned int index;
	/*04,4*/ Direction direction;
	/*08,4*/ undefined4 field_8;
	/*0c,4*/ undefined4 field_c;
	/*10,4*/ undefined4 field_10;
	/*14,4*/ undefined4 field_14;
	/*18*/
};
static_assert(sizeof(ItemStruct_428) == 0x18, "");

struct Struct_428
{
	/*000,320*/ Point2F points[100];
	/*320,4*/ unsigned int pointsCount;
	/*324,f0*/ ItemStruct_428 items[10];
	/*414,4*/ unsigned int itemsCount;
	/*418,4*/ undefined4 field_418;
	/*41c,4*/ undefined4 field_41c;
	/*420,4*/ undefined4 field_420;
	/*424,4*/ undefined4 field_424;
	/*428*/
};
static_assert(sizeof(Struct_428) == 0x428, "");

struct BasicObjectData
{
	/*0,4*/ int objIndex;
	/*4,4*/ ResourceData* aeResData; // ACT, true
	/*8*/
};
static_assert(sizeof(BasicObjectData) == 0x8, "");



struct SelectedUnitHotkey
{
	/*00,4*/ int field_0;
	/*04,4*/ int field_4;
	/*08,4*/ BOOL bool_8;
	/*0c,4*/ int field_c;
	/*10,4*/ int field_10;
	/*14*/
};
static_assert(sizeof(SelectedUnitHotkey) == 0x14, "");

struct AdvisorAnimData
{
	/*0,4*/ ResourceData* resData;
	/*4,4*/ float loopStartTime; // ignored when not looping
	/*8,4*/ float loopEndTime; // ignored when not looping
	/*c*/
};
static_assert(sizeof(AdvisorAnimData) == 0xc, "");

struct AudioPlaybackData
{
	/*00,4*/ BOOL isUsed1; // paused/playing/used?
	/*04,4*/ WAVEFORMATEX* waveFormat; // hGlobal
	/*08,4*/ HMMIO hMmio;
	/*0c,14*/ MMCKINFO mmckInfo;
	/*20,14*/ MMCKINFO mmckInfoData;
	/*34,4*/ unsigned int bufferBytesSize;
	/*38,4*/ unsigned int totalFrames; // probably
	/*3c,4*/ unsigned int playback_3c;
	/*40,4*/ unsigned int playback_40;
	/*44,4*/ unsigned int playback_44; // thought to be totalSamples
	/*48,4*/ unsigned int playback_48;
	/*4c,4*/ undefined4 field_4c;
	/*50,4*/ BOOL modeChoice;
	/*54,4*/ undefined4 field_54;
	/*58,4*/ BOOL isUsed2; // paused/playing/used?
	/*5c*/
};
static_assert(sizeof(AudioPlaybackData) == 0x5c, "");

struct NERPMessageSound
{
	/*0,4*/ char* key;
	/*4,4*/ int sampleIndex;
	/*8*/
};
static_assert(sizeof(NERPMessageSound) == 0x8, "");

struct SampleProperty
{
	/*0,4*/ int sampleIndex;
	/*4,4*/ SampleProperty* next;
	/*8*/
};
static_assert(sizeof(SampleProperty) == 0x8, "");

struct SampleData
{
	/*000,104*/ char filename[260];
	/*104,4*/ unsigned int length;
	/*108,4*/ unsigned int avgBytesPerSec;
	/*10c,4*/ unsigned int frequency;
	/*110,4*/ int volume;
	/*114,4*/ undefined4 offset;
	/*118,4*/ HGLOBAL hGlobal_118;
	/*11c,4*/ HGLOBAL hGlobal_11c;
	/*120,4*/ IDirectSoundBuffer* dSoundBuffer1;
	/*124,4*/ IDirectSoundBuffer* dSoundBuffer2;
	/*128,4*/ IDirectSoundBuffer* dSoundBuffer3;
	/*12c,4*/ undefined4 bufferIndex;
	/*130,4*/ SampleFlags flags;
	/*134*/
};
static_assert(sizeof(SampleData) == 0x134, "");


struct SharedTextureResource
{
	/*0,4*/ char* name;
	/*4,4*/ IDirect3DRMTexture3* texture;
	/*8*/
};
static_assert(sizeof(SharedTextureResource) == 0x8, "");

struct ResourceManager
{
	/*0000,50*/ ResourceData* pool_g_TABLE[20]; // PTR_0076bd80
	/*0050,4*/ ResourceData* pool_g_NEXT; // PTR_0076bd84
	/*0054,4*/ ResourceData* pool_g_ROOT; // PTR_0076bd88
	/*0058,24*/ const char* Types_TABLE[9]; // PTR_0076bdd8
	/*007c,24*/ const char* Extensions_TABLE[9]; // PTR_0076bdfc
	/*00a0,4*/ char* CfgRootName; // PTR_0076be20
	/*00a4,4*/ undefined4 DAT_0076be24; // DAT_0076be24
	/*00a8,4*/ undefined4 field_a8; // DAT_0076be28
	/*00ac,4*/ undefined4 field_ac; // referenced by addr to get last item of g_Textures_TABLE
	/*00b0,4*/ undefined4 field_b0; // DAT_0076be30
	/*00b4,1f40*/ SharedTextureResource Textures_TABLE[1000]; // PTR_0076be34
	/*1ff4,4*/ unsigned int Textures_COUNT; // DAT_0076dd74
	/*1ff8,4*/ pointer soundCallback; // PTR_0076dd78
	/*1ffc,4*/ void* soundCallback_VALUE; // PTR_0076dd7c
	/*2000,4*/ pointer drawCallback; // PTR_0076dd80
	/*2004,4*/ void* drawCallback_VALUE; // PTR_0076dd84
	/*2008,4*/ char* SharedTextures; // PTR_0076dd88
	/*200c,4*/ unsigned int SceneFogColor; // DAT_0076dd8c
	/*2010,4*/ unsigned int pool_g_COUNT; // DAT_0076dd90
	/*2014,4*/ unsigned int pool_g_INITFLAGS; // DAT_0076dd94
	/*2018*/
};
static_assert(sizeof(ResourceManager) == 0x2018, "");


struct NERPSFunctionSignature
{
	/*0,4*/ const char* name;
	/*4,4*/ int (*function)(int*);
	/*8,4*/ NERPSFunctionArgs arguments;
	/*c*/
};
static_assert(sizeof(NERPSFunctionSignature) == 0xc, "");


struct MiscObjectDependencies
{
	/*00,4*/ undefined4 field_0;
	/*04,40*/ unsigned int levels_flags[16];
	/*44,40*/ undefined4 levels_field_44[16];
	/*84,40*/ undefined4 levels_field_84[16];
	/*c4*/
};
static_assert(sizeof(MiscObjectDependencies) == 0xc4, "");


struct ErodeState
{
	/*0,4*/ undefined4 field_0;
	/*4,4*/ undefined4 field_4;
	/*8*/
};
static_assert(sizeof(ErodeState) == 0x8, "");


struct ToolTipData
{
	/*000,4*/ float float_0;
	/*004,200*/ char tooltipText[512];
	/*204,58*/ undefined field_0x204_0x25c[0x58];
	/*25c,4*/ undefined4 field_25c;
	/*260,4*/ undefined4 field_260;
	/*264,4*/ undefined4 field_264;
	/*268,4*/ undefined4 field_268;
	/*26c,4*/ undefined4 field_26c;
	/*270,4*/ ImageBMP* tooltipImage;
	/*274,4*/ undefined4 field_274;
	/*278,4*/ unsigned int flags;
	/*27c*/
};
static_assert(sizeof(ToolTipData) == 0x27c, "");

struct SharedObjectResource
{
	/*0,4*/ char* resName;
	/*4,4*/ Struct_34* lwoStruct34;
	/*8*/
};
static_assert(sizeof(SharedObjectResource) == 0x8, "");

// The item's render state type is determined by the index in its table
struct RenderStateItem
{
	/*0,4*/ DWORD value;
	/*4,4*/ BOOL isUsed;
	/*8*/
};
static_assert(sizeof(RenderStateItem) == 0x8, "");

struct ImageFont
{
	/*000,4*/ ImageBMP* bitmap;
	/*004,be0*/ undefined field_0x4_0xbe4[0xbe0];
	/*be4,4*/ undefined4 field_be4;
	/*be8,8*/ undefined field_0xbe8_0xbf0[0x8];
	/*bf0,4*/ ImageFont* pool_m_next;
	/*bf4*/
};
static_assert(sizeof(ImageFont) == 0xbf4, "");

#pragma region Framework: IO Structures

struct FileStream {
	/*0,4*/ FileLocation location;
	/*4,4*/ union {
		FILE* std; // Standard file stream
		FileWADStream* wad; // WAD file stream
	};
	/*8*/
};
static_assert(sizeof(FileStream) == 0x8, "");

struct FileWADStream
{
	/*0,4*/ int sharedIndex;
	/*4,4*/ int position;
	/*8,4*/ undefined4 field_8;
	/*c*/
};
static_assert(sizeof(FileWADStream) == 0xc, "");

// WAD file entry metadata contained within LegoWADFile structure
struct WADEntry
{
	/*00,4*/ WADEntryFlags flags; // usually 1, 2 for RNC compression
	//undefined field_0x1;
	//undefined field_0x2;
	//undefined field_0x3;
	/*04,4*/ unsigned int packedSize; // Compressed packed size
	/*08,4*/ unsigned int origSize; // Original unpacked size (same as packedSize when uncompressed)
	/*0c,4*/ unsigned int offset; // absolute file offset
	/*10*/
};
static_assert(sizeof(WADEntry) == 0x10, "");

// LegoRR WAD File information
struct WADFile
{
	/*00,4*/ undefined4 field_0;
	/*04,4*/ BOOL isUsed; // 1 if WAD is in-use
	/*08,4*/ undefined4 field_8;
	/*0c,4*/ undefined4 field_c;
	/*10,4*/ FILE* file; // file I/O
	/*14,4*/ char** absdirs; // source file paths when WAD was built
	/*18,4*/ char** reldirs; // relative file paths inside WAD
	/*1c,4*/ WADEntry* entries; // file entry metadata
	/*20,4*/ unsigned int count; // number of file entries
	/*24*/
};
static_assert(sizeof(WADFile) == 0x24, "");

struct WADStream
{
	/*00,4*/ void* fileData;
	/*04,4*/ BOOL isUsed;
	/*08,4*/ int wadIndex;
	/*0c,4*/ int entryIndex;
	/*10*/
};
static_assert(sizeof(WADStream) == 0x10, "");

struct FileBuffer
{
	/*0,4*/ void* fileData;
	/*4,4*/ FileBufferFlags flags; // 1 = isUsed
	/*8*/
};
static_assert(sizeof(FileBuffer) == 0x8, "");


#pragma pack(push, 4)

struct HuffmanLeaf
{
	/*00,4*/ unsigned int value_1;
	/*04,2*/ unsigned short count_1;
	/*06,2*/
	/*08,4*/ unsigned int value_2;
	/*0c,2*/ unsigned short count_2;
	/*0e,2*/
	/*10*/
};
static_assert(sizeof(HuffmanLeaf) == 0x10, "");

#pragma pack(pop)

struct CFGProperty
{
	/*00,4*/ char* fileText; // the entire CFG file text (only stored for root property)
	/*04,4*/ const char* key;   // init: NULL
	/*08,4*/ const char* value; // init: NULL
	/*0c,4*/ unsigned int depth;    // init: 0 (if root)
	/*10,4*/ unsigned int field_10; // init: 0 (unknown usage)
	/*14,4*/ CFGProperty* next; // init: NULL
	/*18,4*/ CFGProperty* previous;  // init: NULL (if root)
	/*1c,4*/ CFGProperty* pool_m_next;
	/*20*/
};
static_assert(sizeof(CFGProperty) == 0x20, "");

typedef CFGProperty CFGRoot;


#pragma endregion


struct LoaderProfileItem
{
	/*0,4*/ char* name;
	/*4,4*/ undefined4 field_4;
	/*8,4*/ undefined4 field_8;
	/*c*/
};
static_assert(sizeof(LoaderProfileItem) == 0xc, "");

struct SurfaceTextureGrid
{
	/*0,8*/ Size2I gridSize;
	/*8,4*/ DirectXSurfaceTuple** gridSurfaces;
	/*c*/
};
static_assert(sizeof(SurfaceTextureGrid) == 0xc, "");

struct HelpWindowInfoLevels
{
	/*00,40*/ char* levels[16];
	/*40*/
};
static_assert(sizeof(HelpWindowInfoLevels) == 0x40, "");

struct InterfaceMenuItem
{
	/*0,4*/ int* parameters;
	/*4,4*/ unsigned int numParams;
	/*8*/
};
static_assert(sizeof(InterfaceMenuItem) == 0x8, "");

// Property loaded from a level's PTL config file (contains lookup index for actions)
struct PTLProperty
{
	/*0,4*/ MessageType eventIndex;
	/*4,4*/ MessageType actionIndex;
	/*8*/
};
static_assert(sizeof(PTLProperty) == 0x8, "");

struct DriverMode
{
	/*000,10*/ GUID guid;
	/*010,100*/ char displayName[256]; // "name (description)"
	/*110,4*/ DriverModeFlags flags;
	/*114*/
};
static_assert(sizeof(DriverMode) == 0x114, "");

struct DeviceMode
{
	/*000,10*/ GUID guid;
	/*010,100*/ char displayName[256]; // "name (description)"
	/*110,4*/ DeviceModeFlags flags;
	/*114*/
};
static_assert(sizeof(DeviceMode) == 0x114, "");

struct ScreenMode
{
	/*000,4*/ int screenWidth;
	/*004,4*/ int screenHeight;
	/*008,4*/ int bitDepth;
	/*00c,100*/ char displayName[256]; // "WxH (BPP bit)", "WxH" (windowed)
	/*10c,4*/ ScreenModeFlags flags;
	/*110*/
};
static_assert(sizeof(ScreenMode) == 0x110, "");

struct ImageBMP
{
	/*00,4*/ IDirectDrawSurface4* ddSurface; // IDirectDrawSurface4
	/*04,4*/ int width;
	/*08,4*/ int height;
	/*0c,4*/ unsigned int firstColor24;
	/*10,4*/ unsigned int lastColor24;
	/*14,4*/ unsigned int firstColorNative;
	/*18,4*/ unsigned int flags; // 2 is font?
	/*1c,4*/ ImageBMP* pool_m_next;
	/*20*/
};
static_assert(sizeof(ImageBMP) == 0x20, "");

struct SurfaceMapStruct38
{
	/*00,4*/ undefined4 field_0;
	/*04,4*/ float float_4;
	/*08,4*/ undefined4 field_8;
	/*0c,4*/ undefined4 field_c;
	/*10,20*/ undefined4 table_10[8];
	/*30,4*/ undefined field_0x30_0x34[0x4];
	/*34,4*/ unsigned int flags;
	/*38*/
};
static_assert(sizeof(SurfaceMapStruct38) == 0x38, "");

struct ObjectiveData
{
	/*00,4*/ void* ObjectiveImage; // bmp
	/*04,4*/ int ObjectiveImage_width_x; // ???
	/*08,4*/ int ObjectiveImage_height_y; // ???
	/*0c,4*/ void* ObjectiveAcheivedImage; // bmp
	/*10,4*/ int ObjectiveAcheivedImage_width_x; // ???
	/*14,4*/ int ObjectiveAcheivedImage_height_y; // ???
	/*18,4*/ void* ObjectiveFailedImage; // bmp
	/*1c,4*/ int ObjectiveFailedImage_width_x; // ???
	/*20,4*/ int ObjectiveFailedImage_height_y; // ???
	/*24,4*/ void* ObjectiveAcheivedAVI; // ???
	/*28,4*/ int ObjectiveAcheivedAVI_width_x; // ???
	/*2c,4*/ int ObjectiveAcheivedAVI_height_y; // ???
	/*30,4*/ undefined4 field_30;
	/*34,4*/ undefined4 field_34;
	/*38,4*/ int CrystalObjective; // number of crystals needed if non-zero
	/*3c,4*/ int OreObjective; // number of ore needed if non-zero
	/*40,8*/ Point2I BlockObjective;
	/*48,4*/ float TimerObjective; // (mult: 25.0, flags, format: "time:HitTimeFailObjective")
	/*4c,4*/ int ConstructionObjective_type;
	/*50,4*/ int ConstructionObjective_index;
	/*54*/
};
static_assert(sizeof(ObjectiveData) == 0x54, "");

struct LevelData
{
	/*000,4*/ char* levelName; // (format: "Levels::level")
	/*004,4*/ LevelSurfaceMap* surfaceMap;
	/*008,4*/ undefined4 field_8;
	/*00c,4*/ undefined4 field_c;
	/*010,4*/ undefined4 field_10;
	/*014,8*/ Size2I dimensions;
	/*01c,4*/ float BlockSize;
	/*020,4*/ float DigDepth;
	/*024,4*/ float RoofHeight;
	/*028,4*/ float RoughLevel;
	/*02c,4*/ BOOL3 UseRoof;
	/*030,4*/ BOOL3 SafeCaverns;
	/*034,4*/ float SelBoxHeight;
	/*038,4*/ undefined4 field_0x38;
	/*03c,4*/ undefined4 field_0x3c;
	/*040,4*/ undefined4 field_0x40;
	/*044,4*/ undefined4 field_0x44;
	/*048,4*/ undefined4 field_0x48;
	/*04c,4*/ undefined4 field_0x4c;
	/*050,4*/ undefined4 field_0x50;
	/*054,4*/ undefined4 field_0x54;
	/*058,4*/ undefined4 field_0x58;
	/*05c,4*/ undefined4 field_0x5c;
	/*060,4*/ undefined4 field_0x60;
	/*064,4*/ undefined4 field_0x64;
	/*068,4*/ undefined4 field_0x68;
	/*06c,4*/ undefined4 field_0x6c;
	/*070,4*/ undefined4 field_0x70;
	/*074,8*/ Size2I surfTextSize; // surface texture width and height
	/*07c,4*/ SurfaceTextureGrid* surfTextGrid;
	/*080,4*/ undefined4 field_0x80;
	/*084,4*/ LevelStruct_3c* struct3c_84;
	/*088,4*/ LevelStruct_1c* terrain1c_88;
	/*08c,4*/ int numCrystals; // (init: 0)
	/*090,4*/ undefined4 field_90; // (init: 0)
	/*094,4*/ undefined4 field_94; // (init: 0)
	/*098,4*/ int numDrainedCrystals; // assumption
	/*09c,4*/ undefined4 field_9c;
	/*0a0,4*/ int numOre; // (init: 0)
	/*0a4,4*/ undefined4 field_a4; // (init: 0)
	/*0a8,4*/ undefined4 field_a8; // (init: 0)
	/*0ac,4*/ int numProcessedOre;
	/*0b0,4*/ int EmergeCreature; // (searches for object index by name, expects RockMonsterType)
	/*0b4,4*/ char* NextLevel;
	/*0b8,4*/ LevelBlock* blocks; // grid of blocks [y][x]
	/*0bc,54*/ ObjectiveData objective;
	/*110,4*/ BOOL hasBlockPointers;
	/*114,e0*/ BlockPointer* blockPointers[56];
	/*1f4,4*/ BOOL StartFP;
	/*1f8,4*/ BOOL NoDrain;
	/*1fc,4*/ float oxygenLevel; // (init: 100.0, Oxygen level?)
	/*200,4*/ float OxygenRate;
	/*204,4*/ float float_204; // (init: 100.0, Oxygen level?)
	/*208,4*/ float BuildingTolerance; // (default: 4.0)
	/*20c,4*/ float BuildingMaxVariation; // (default: 6.0)
	/*210,50*/ float UpgradeTimes[20]; // [objType] (mult: 25.0, 1:Vehicle, 2:MiniFigure, 3:Building)
	/*260,4*/ float TrainTime; // (mult: 25.0)
	/*264,4*/ float EmergeTimeOut; // (default: 1500.0)
	/*268,4*/ float SlugTime; // (default: 60.0, mult: 25.0 (applies to default))
	/*26c,4*/ int Slug; // (default: 20 (invalid), searches for object index by name, expects RockMonsterType)
	/*270,4*/ char* FullName; // (replace '_' with ' ')
	/*274,4*/ TextureType BoulderAnimation; // (texture index, hardcoded: Rock, Lava, Ice)
	/*278,4*/ float MaxStolen;
	/*27c,4*/ LevelCompleteStatus status; // (init: 0) 2 is used for Crystal failure as well
	/*280,4*/ BOOL IsStartTeleportEnabled; // (! DisableStartTeleport)
	/*284*/
};
static_assert(sizeof(LevelData) == 0x284, "");

struct BlockPointer
{
	/*0,8*/ Point2I position;
	/*8,4*/ unsigned int id;
	/*c*/
};
static_assert(sizeof(BlockPointer) == 0xc, "");

struct DirectXSurfaceTuple
{
	/*0,4*/ IDirectDrawSurface4* surface;
	/*4,4*/ IDirect3DRMTexture3* texture;
	/*8,4*/ undefined4 field_8;
	/*c*/
};
static_assert(sizeof(DirectXSurfaceTuple) == 0xc, "");

// size 0x73d4... dear god.... no...
struct LevelSurfaceMap
{
	/*0000,8*/ Size2I smallDimensions; // full map dimensions - 1
	/*0008,8*/ Size2I dimensions; // full map dimensions
	/*0010,4*/ float BlockSize;
	/*0014,4*/ float RoughLevel;
	/*0018,8*/ Size2F blockDimensions_neg; // smallDimensions * BlockSize * 0.5 (width is negative??)
	/*0020,4*/ float float_20;
	/*0024,4*/ ResourceData* resData_24;
	/*0028,4*/ undefined4 field_28;
	/*002c,4*/ undefined4 field_2c;
	/*0030,4*/ undefined4 field_30;
	/*0034,4000*/ undefined field_0x34_0x4034[0x4000];
	/*4034,80*/ undefined4 flat_4034[32];
	/*40b4,200*/ undefined4 flat_40b4[128];
	/*42b4,7d0*/ unsigned short table_42b4[1000];
	/*4a84,4*/ unsigned int count_4a84;
	/*4a88,2710*/ undefined field_0x4a88_0x7198[0x2710];
	/*7198,4*/ undefined4 field_7198;
	/*719c,230*/ SurfaceMapStruct38 table38_719c[10];
	/*73cc,4*/ ResourceData* resData_73cc;
	/*73d0,4*/ undefined4 field_73d0;
	/*73d4*/
};
static_assert(sizeof(LevelSurfaceMap) == 0x73d4, "");

struct LevelStruct_3c
{
	/*00,4*/ undefined4 field_0;
	/*04,4*/ undefined4 field_4;
	/*08,4*/ undefined4 field_8;
	/*0c,4*/ undefined4 field_c;
	/*10,4*/ undefined4 field_10;
	/*14,4*/ undefined4 field_14;
	/*18,4*/ undefined4 field_18;
	/*1c,4*/ undefined4 field_1c;
	/*20,4*/ undefined4 field_20;
	/*24,4*/ undefined4 field_24;
	/*28,4*/ undefined4 field_28;
	/*2c,4*/ undefined4 field_2c;
	/*30,4*/ undefined4 field_30;
	/*34,4*/ undefined4 field_34;
	/*38,4*/ undefined4 field_38;
	/*3c*/
};
static_assert(sizeof(LevelStruct_3c) == 0x3c, "");

struct GameManager
{
	/*000,4*/ CFGProperty* LegoCfgRoot; // g_LegoCfgRoot
	/*004,4*/ char* CfgRootName; // g_CFG_ROOTPATH
	/*008,4*/ undefined4 field_8;
	/*00c,4*/ undefined4 field_c;
	/*010,4*/ GraphicsQuality Quality; // g_GraphicsQuality
	/*014,4*/ LevelData* level; // g_LEVEL_STRUCTPTR_SIZE_284__005570d4
	/*018,4*/ ResourceData* resRoot; // DAT_005570d8
	/*01c,4*/ void* ptr_1c; // PTR_005570dc
	/*020,4*/ undefined4 field_20; // DAT_005570e0
	/*024,4*/ Struct_bc* structbc_24; // PTR_005570e4
	/*028,4*/ Struct_bc* structbc_28; // DAT_005570e8
	/*02c,4*/ Struct_bc* structbc_2c; // DAT_005570ec
	/*030,4*/ ResourceData* struct2c_30; // PTR_005570f0
	/*034,4*/ ResourceData* struct2c_34; // DAT_005570f4
	/*038,4*/ ResourceData* struct2c_38; // PTR_005570f8
	/*03c,4*/ ResourceData* struct2c_3c; // PTR_005570fc
	/*040,4*/ ResourceData* struct2c_40; // PTR_00557100
	/*044,4*/ ResourceData* struct2c_44; // PTR_00557104
	/*048,4*/ ResourceData* struct2c_48; // PTR_00557108
	/*04c,4*/ ResourceData* struct2c_4c; // PTR_0055710c
	/*050,4*/ float FPClipBlocks; // FLOAT_00557110
	/*054,4*/ float TVClipDist; // g_tvclipdist
	/*058,4*/ undefined4 field_58;
	/*05c,4*/ undefined4 field_5c;
	/*060,4*/ undefined4 field_60;
	/*064,4*/ ImageFont* bmpFONT5_HI; // g_FONT_FONT5_HI
	/*068,4*/ ImageFont* bmpToolTipFont; // g_FONT_ToolTipFont
	/*06c,4*/ ImageFont* bmpDeskTopFont; // g_FONT_DeskTopFont
	/*070,4*/ ImageFont* bmpfont5_HI; // g_FONT_font5_HI
	/*074,4*/ ImageFont* bmpMbriefFONT; // g_FONT_MbriefFONT
	/*078,4*/ ImageFont* bmpMbriefFONT2; // g_FONT_MbriefFONT2
	/*07c,4*/ ImageFont* bmpRSFont; // g_FONT_RSFont
	/*080,4*/ Struct_830* struct830_80; // PTR_00557140
	/*084,4*/ Struct_830* struct830_84; // PTR_00557144
	/*088,4*/ float float_88; // FLOAT_00557148
	/*08c,4*/ float float_8c; // FLOAT_0055714c
	/*090,4*/ float float_90; // FLOAT_00557150
	/*094,4*/ float float_94; // FLOAT_00557154
	/*098,4*/ BOOL bool_98; // BOOL_00557158
	/*09c,4*/ float gameSpeed; // FLOAT_0055715c
	/*0a0,4*/ LiveObject* object_a0; // DAT_00557160
	/*0a4,4*/ float float_a4; // FLOAT_00557164
	/*0a8,4*/ float float_a8; // FLOAT_00557168
	/*0ac,4*/ float float_ac; // FLOAT_0055716c
	/*0b0,4*/ float float_b0; // FLOAT_00557170
	/*0b4,4*/ float float_b4; // FLOAT_00557174
	/*0b8,4*/ float float_b8; // FLOAT_00557178
	/*0bc,4*/ float float_bc; // FLOAT_0055717c
	/*0c0,4*/ undefined4 field_c0; // DAT_00557180
	/*0c4,4*/ undefined4 field_c4; // DAT_0055718c
	/*0c8,4*/ BOOL bool_c8; // DAT_00557188
	/*0cc,4*/ char* ObjectNames_PowerCrystal; // g_ObjectNames_PowerCrystal
	/*0d0,4*/ char* ObjectNames_Ore; // g_ObjectNames_Ore
	/*0d4,4*/ char* ObjectNames_ProcessedOre; // g_ObjectNames_ProcessedOre
	/*0d8,4*/ char* ObjectNames_Dynamite; // g_ObjectNames_Dynamite
	/*0dc,4*/ char* ObjectNames_Barrier; // g_ObjectNames_Barrier
	/*0e0,4*/ char* ObjectNames_ElectricFence; // g_ObjectNames_ElectricFence
	/*0e4,4*/ char* ObjectNames_SpiderWeb; // g_ObjectNames_SpiderWeb
	/*0e8,4*/ char* ObjectNames_OohScary; // g_ObjectNames_OohScary
	/*0ec,4*/ char* ObjectNames_Path; // g_ObjectNames_Path
	/*0f0,4*/ char* ObjectTheNames_PowerCrystal; // g_ObjectTheNames_PowerCrystal
	/*0f4,4*/ char* ObjectTheNames_Ore; // g_ObjectTheNames_Ore
	/*0f8,4*/ char* ObjectTheNames_ProcessedOre; // g_ObjectTheNames_ProcessedOre
	/*0fc,4*/ char* ObjectTheNames_Dynamite; // g_ObjectTheNames_Dynamite
	/*100,4*/ char* ObjectTheNames_Barrier; // g_ObjectTheNames_Barrier
	/*104,4*/ char* ObjectTheNames_ElectricFence; // g_ObjectTheNames_ElectricFence
	/*108,4*/ char* ObjectTheNames_SpiderWeb; // g_ObjectTheNames_SpiderWeb
	/*10c,4*/ char* ObjectTheNames_OohScary; // g_ObjectTheNames_OohScary
	/*110,4*/ char* ObjectTheNames_Path; // g_ObjectTheNames_Path
	/*114,4*/ VehicleData* VehicleData_TABLE; // g_VehicleData_TABLE
	/*118,4*/ CreatureData* MiniFigureData_TABLE; // g_MiniFigureData_TABLE
	/*11c,4*/ CreatureData* RockMonsterData_TABLE; // g_RockMonsterData_TABLE
	/*120,4*/ BuildingData* BuildingData_TABLE; // g_BuildingData_TABLE
	/*124,4*/ UpgradeData* UpgradeData_TABLE; // g_UpgradeData_TABLE
	/*128,4*/ char** VehicleTypes_TABLE; // g_VehicleTypes_TABLE
	/*12c,4*/ char** MiniFigureTypes_TABLE; // g_MiniFigureTypes_TABLE
	/*130,4*/ char** RockMonsterTypes_TABLE; // g_RockMonsterTypes_TABLE
	/*134,4*/ char** BuildingTypes_TABLE; // g_BuildingTypes_TABLE
	/*138,4*/ char** UpgradeTypes_TABLE; // g_UpgradeTypes_TABLE
	/*13c,2c*/ const char* ToolTypes_TABLE[11]; // g_ToolTypes_TABLE
	/*168,2c*/ char* ToolNames_TABLE[11]; // g_ToolNames_TABLE
	/*194,4*/ char** ObjectNames_VehicleTypes_TABLE; // g_ObjectNames_VehicleTypes_TABLE
	/*198,4*/ char** ObjectNames_MiniFigureTypes_TABLE; // g_ObjectNames_MiniFigureTypes_TABLE
	/*19c,4*/ char** ObjectNames_RockMonsterTypes_TABLE; // g_ObjectNames_RockMonsterTypes_TABLE
	/*1a0,4*/ char** ObjectNames_BuildingTypes_TABLE; // g_ObjectNames_BuildingTypes_TABLE
	/*1a4,4*/ char** ObjectNames_UpgradeTypes_TABLE; // g_ObjectNames_UpgradeTypes_TABLE
	/*1a8,4*/ char** ObjectTheNames_VehicleTypes_TABLE; // g_ObjectTheNames_VehicleTypes_TABLE
	/*1ac,4*/ char** ObjectTheNames_MiniFigureTypes_TABLE; // g_ObjectTheNames_MiniFigureTypes_TABLE
	/*1b0,4*/ char** ObjectTheNames_RockMonsterTypes_TABLE; // g_ObjectTheNames_RockMonsterTypes_TABLE
	/*1b4,4*/ char** ObjectTheNames_BuildingTypes_TABLE; // g_ObjectTheNames_BuildingTypes_TABLE
	/*1b8,4*/ char** ObjectTheNames_UpgradeTypes_TABLE; // g_ObjectTheNames_UpgradeTypes_TABLE
	/*1bc,4*/ unsigned int VehicleTypes_COUNT; // g_VehicleTypes_COUNT
	/*1c0,4*/ unsigned int MiniFigureTypes_COUNT; // g_MiniFigureTypes_COUNT
	/*1c4,4*/ unsigned int RockMonsterTypes_COUNT; // g_RockMonsterTypes_COUNT
	/*1c8,4*/ unsigned int BuildingTypes_COUNT; // g_BuildingTypes_COUNT
	/*1cc,4*/ unsigned int UpgradeTypes_COUNT; // g_UpgradeTypes_COUNT
	/*1d0,48*/ const char* SurfaceTypes_TABLE[18]; // g_SurfaceTypes_TABLE
	/*218,48*/ char* SurfaceTypeDescriptions_name_TABLE[18]; // g_SurfaceTypeDescriptions_name_TABLE
	/*260,48*/ void* SurfaceTypeDescriptions_sound_TABLE[18]; // g_SurfaceTypeDescriptions_sound_TABLE
	/*2a8,4*/ ResourceData* RES_Boulder; // g_RES_BOULDER
	/*2ac,4*/ ResourceData* RES_BoulderExplode; // DAT_0055736c
	/*2b0,4*/ ResourceData* RES_BoulderExplodeIce; // DAT_00557370
	/*2b4,4*/ ResourceData* RES_Crystal; // g_RES_POWERCRYSTAL
	/*2b8,4*/ ResourceData* RES_Dynamite; // g_RES_DYNAMITE
	/*2bc,8*/ ResourceData* RES_Ores_TABLE[2]; // g_RES_ORES_TABLE
	/*2c4,4*/ ResourceData* RES_OohScary; // g_RES_OOHSCARY
	/*2c8,4*/ ResourceData* RES_Barrier; // g_RES_BARRIER
	/*2cc,4*/ ResourceData* RES_ElectricFence; // g_RES_ELECTRICFENCE
	/*2d0,4*/ ResourceData* RES_SpiderWeb; // g_RES_SPIDERWEB
	/*2d4,4*/ ResourceData* RES_RechargeSparkle; // DAT_00557394
	/*2d8,4*/ ResourceData* RES_MiniTeleportUp; // DAT_00557398
	/*2dc,4*/ ResourceData* RES_ElectricFenceStud; // DAT_0055739c
	/*2e0,4*/ ResourceData* RES_Pusher; // g_RES_PUSHER
	/*2e4,4*/ ResourceData* RES_Freezer; // g_RES_FREEZER
	/*2e8,4*/ ResourceData* RES_IceCube; // DAT_005573a8
	/*2ec,4*/ ResourceData* RES_SmashPath; // DAT_005573ac
	/*2f0,4*/ ResourceData* RES_LaserShot; // g_RES_LASERSHOT
	/*2f4,4*/ ResourceData** RES_2f4_TABLEUNK; // DAT_005573b4
	/*2f8,28*/ undefined4 table10_2f8[10]; // g_UNK_TABLE__005573b8
	/*330,4*/ unsigned int count10_320; // UINT_005573e0
	/*324,4*/ float float_324; // FLOAT_005573e4
	/*328,4*/ float float_328; // FLOAT_005573e8
	/*32c,4*/ float float_32c; // FLOAT_005573ec
	/*330,4*/ float float_330; // FLOAT_005573f0
	/*334,4*/ float tvTiltOrZoom_334;
	/*338,8*/ Point2F tvFaceDirection_338;
	/*340,4*/ float MedPolyRange; // g_MedPolyRange
	/*344,4*/ float HighPolyRange; // g_HighPolyRange
	/*348,4*/ int HPBlocks; // g_HPBlocks
	/*34c,c*/ ColourRGBF FogColourRGB; // g_FogColourRGB
	/*358,c*/ ColourRGBF HighFogColourRGB; // g_HighFogColourRGB
	/*364,4*/ float float_364; // g_LEVEL_UNK_FLOAT_00557424
	/*368,c*/ ColourRGBF PowerCrystalRGB; // g_PowerCrystalRGB
	/*374,c*/ ColourRGBF UnpoweredCrystalRGB; // g_UnpoweredCrystalRGB
	/*380,4*/ ObjectType placeObjType; // INT_00557440
	/*384,4*/ int placeObjIndex; // INT_00557444
	/*388,4*/ Direction placeObjDirection; // INT_00557448
	/*38c,4*/ LiveObject* placeDestSmallTeleporter; // PTR_0055744c
	/*390,4*/ LiveObject* placeDestBigTeleporter; // PTR_00557450
	/*394,4*/ LiveObject* placeDestWaterTeleporter; // PTR_00557454
	/*398,4*/ float MinEnergyForEat; // g_MinEnergyForEat
	/*39c,4*/ ImageBMP* TutorialIcon; // bmp? PTR_0055745c
	/*3a0,4*/ undefined4 field_3a0;
	/*3a4,4*/ float DynamiteDamageRadius; // g_DynamiteDamageRadius
	/*3a8,4*/ float DynamiteMaxDamage; // g_DynamiteMaxDamage
	/*3ac,4*/ float DynamiteWakeRadius; // g_DynamiteWakeRadius
	/*3b0,4*/ float BirdScarerRadius; // g_BirdScarerRadius
	/*3b4,50*/ ObjectType objTeleportQueueTypes_TABLE[20]; // UNK_ARRAY_00557474
	/*404,50*/ int objTeleportQueueIndexes_TABLE[20]; // UNK_ARRAY_005574c4
	/*454,4*/ unsigned int objTeleportQueue_COUNT; // count for above 2 arrays, UINT_00557514
	/*458,4*/ float MiniFigureRunAway; // g_MiniFigureRunAway
	/*45c,c*/ Vector3F vector_45c; // FLOAT_0055751c
	/*468,320*/ undefined4 table200_468[200]; // UNK_ARRAY_00557528
	/*788,4*/ unsigned int count_788; // UINT_00557848
	/*78c,320*/ undefined4 table200_78c[200]; // UNK_ARRAY_0055784c
	/*aac,320*/ undefined4 table200_aac[200]; // UNK_ARRAY_00557b6c
	/*dcc,4*/ unsigned int count_dcc; // UINT_00557e8c
	/*dd0,4*/ unsigned int count_dd0; // UINT_00557e90
	/*dd4,4*/ unsigned int MaxReturnedCrystals; // g_MaxReturnedCrystals
	/*dd8,4*/ unsigned int MouseScrollBorder; // g_MouseScrollBorder
	/*ddc,4*/ char* HealthText; // g_HealthText
	/*de0,4*/ char* EnergyText; // g_EnergyText
	/*de4,4*/ char* CrystalsText; // g_CrystalsText
	/*de8,4*/ char* OreText; // g_OreText
	/*dec,4*/ char* StudsText; // g_StudsText
	/*df0,4*/ char* ToolsText; // g_ToolsText
	/*df4,4*/ char* CarryObjectText; // g_CarryObjectText
	/*df8,4*/ char* DrivenByText; // g_DrivenByText
	/*dfc,4*/ char* OreRequiredText; // g_OreRequiredText
	/*e00,4*/ BOOL IsFallinsEnabled; // (! "NoFallins"), g_YesFallins
	/*e04,4*/ float MinDistFor3DSoundsOnTopView; // g_MinDistFor3DSoundsOnTopView
	/*e08,4*/ unsigned int unkbool_308; // (may not be bool, compared with 0, and 1) g_GAME_UNK_BOOL_00557ec8
	/*e0c,4*/ GameFlags1 flags1; // g_GAME_GameFlags1
	/*e10,4*/ GameFlags2 flags2; // g_GAME_GameFlags2
	/*e14,4*/ GameFlags3 flags3; // only first byte is used(?), g_GAME_GameFlags3
	/*e18,4*/ float InitialSlugTime; // g_InitialSlugTime
	/*e1c,8*/ Point2F NextButtonPos; // g_NextButton
	/*e24,8*/ Point2F BackButtonPos; // g_BackButtonPos
	/*e2c,4*/ ImageBMP* NextButton; // bmp? PTR_00557eec
	/*e30,4*/ ImageBMP* BackButton; // bmp? PTR_00557ef0
	/*e34,4*/ ImageBMP* BackArrow; // bmp? PTR_00557ef4
	/*e38,4*/ float FogRate; // g_LEVEL_FogRate
	/*e3c,4*/ float float_e3c; // FLOAT_00557efc
	/*e40,4*/ float floatfps_e40; // assigned to Game_Update param_1 float fpsSync, FLOAT_00557f00
	/*e44,4*/ float DrainTime; // g_DrainTime
	/*e48,4*/ unsigned int ReinforceHits; // g_ReinforceHits
	/*e4c,4*/ unsigned int CDStartTrack; // g_CDStartTrack
	/*e50,4*/ unsigned int CDTracks; // g_CDTracks
	/*e54,4*/ unsigned int FallinMultiplier; // g_LEVEL_FallinMultiplier
	/*e58,4*/ BOOL hasFallins; // BOOL_00557f18
	/*e5c,8*/ Point2F menuNextPoint; // DAT_00557f1c
	/*e64,8*/ Point2F menuPrevPoint; // DAT_00557f24
	/*e6c,c*/ ColourRGBF DragBoxRGB; // g_DragBoxRGB
	/*e78,4*/ ImageBMP* DialogImage; // PTR_00557f38
	/*e7c,4*/ ImageBMP* DialogContrastOverlay; // PTR_00557f3c
	/*e80,4*/ void* drawregion_e80; // PTR_00557f40
	/*e84,4*/ void* drawregion_e84; // PTR_00557f44
	/*e88,4*/ void* drawregion_e88; // PTR_00557f48
	/*e8c,4*/ void* drawregion_e8c; // PTR_00557f4c
	/*e90,4*/ char* CreditsTextFile; // g_CreditsTextFile
	/*e94,4*/ char* CreditsBackAVI; // g_CreditsBackAVI
	/*e98,40*/ char* UpgradeNames_TABLE[16]; // g_UpgradeNames_TABLE
	/*ed8,4*/ int BuildingUpgradeCostOre; // g_BuildingUpgradeCostOre
	/*edc,4*/ int BuildingUpgradeCostStuds; // g_BuildingUpgradeCostStuds
	/*ee0,4*/ char* renameInput; // DAT_00557fa0
	/*ee4,4*/ float float_ee4; // FLOAT_00557fa4
	/*ee8,4*/ float float_ee8; // FLOAT_00557fa8
	/*eec,4*/ char* RenameReplace; // g_RenameReplace
	/*ef0,4*/ char* EndGameAVI1; // g_EndGameAVI1
	/*ef4,4*/ char* EndGameAVI2; // g_EndGameAVI2
	/*ef8*/
};
static_assert(sizeof(GameManager) == 0xef8, "");


struct Struct_bc
{
	/*00,4*/ undefined4 mode_0;
	/*04,4*/ LiveObject* object_4;
	/*08,4*/ float float_8;
	/*0c,4*/ float float_c;
	/*10,4*/ float float_10;
	/*14,4*/ undefined4 field_14;
	/*18,c*/ Vector3F vector_18;
	/*24,4*/ ResourceData* resData_24;
	/*28,4*/ ResourceData* resData_28;
	/*2c,4*/ ResourceData* resData_2c;
	/*30,4*/ ResourceData* resData_30;
	/*34,4*/ undefined4 tableunk_34;
	/*38,58*/ undefined field_0x38_0x90[0x58];
	/*90,4*/ float float_90;
	/*94,c*/ undefined field_0x94_0xa0[0xc];
	/*a0,c*/ Vector3F vector_a0;
	/*ac,c*/ Vector3F vector_ac;
	/*b8,4*/ unsigned int flags;
	/*bc*/
};
static_assert(sizeof(Struct_bc) == 0xbc, "");

// Probably a text rendering area
struct Struct_830
{
	/*000,4*/ ImageFont* font;
	/*004,10*/ Rect2F area;
	/*014,4*/ void* allocData;
	/*018,400*/ undefined field_0x18_0x418[0x400];
	/*418,4*/ unsigned int allocSize;
	/*41c,410*/ undefined field_0x41c_0x82c[0x410];
	/*82c,4*/ unsigned int flags;
	/*830*/
};
static_assert(sizeof(Struct_830) == 0x830, "");

struct LwoFrame
{
	/*00,4*/ unsigned int dwSize;
	/*04,60*/ undefined field_0x4_0x64[0x60];
	/*64,4*/ undefined4 field_64;
	/*68,4*/ undefined field_0x68_0x6c[0x4];
	/*6c,4*/ unsigned int flags;
	/*70*/
};
static_assert(sizeof(LwoFrame) == 0x70, "");

struct ObjectUpgradePartData
{
	/*00,4*/ unsigned int level;
	/*04,4*/ int NullInstance;
	/*08,4*/ char* NullObjectName;
	/*0c,4*/ char* WeaponName;
	/*10,4*/ UpgradeData* upgradeData;
	/*14*/
};
static_assert(sizeof(ObjectUpgradePartData) == 0x14, "");

struct FlockSubdata
{
	/*00,c*/ Vector3F vector_0;
	/*0c,c*/ Vector3F vector_c;
	/*18,c*/ Vector3F vector_18;
	/*24,4*/ float float_24;
	/*28,4*/ float float_28;
	/*2c,4*/ float float_2c;
	/*30,4*/ float float_30;
	/*34,4*/ undefined4 field_34;
	/*38,4*/ float GoalUpdate1;
	/*3c,4*/ float Turn1;
	/*40,4*/ float Speed1;
	/*44,4*/ float Tightness1;
	/*48,4*/ float GoalUpdate2;
	/*4c,4*/ float Turn2;
	/*50,4*/ float Speed2;
	/*54,4*/ float Tightness2;
	///*58,40*/ float matrix[16];
	/*58,40*/ Matrix4F matrix;
	/*98,4*/ ResourceData* resData_98;
	/*9c,4*/ FlockSubdata* subdataNext_9c;
	/*a0*/
};
static_assert(sizeof(FlockSubdata) == 0xa0, "");

struct ObjectUpgradesData
{
	/*00,4*/ ObjectUpgradePartData* parts; // always ObjectUpgradePartData[200]
	/*04,4*/ unsigned int count;
	/*08,4*/ int currentLevel;
	/*0c,4*/ unsigned int levelsMask; // [carry][scan][speed][drill]
	/*10,4*/ LiveObject** upgradeObjs;
	/*14*/
};
static_assert(sizeof(ObjectUpgradesData) == 0x14, "");

struct BuildingData
{
	/*000,4*/ int objIndex;
	/*004,4*/ ResourceData* aeResData; // ACT, true
	/*008,4*/ char* CarryNullName;
	/*00c,4*/ char* CameraNullName;
	/*010,4*/ char* DepositNullName;
	/*014,4*/ char* EntranceNullName;
	/*018,4*/ char* ToolNullName;
	/*01c,4*/ char* FireNullName; // "fire laser"
	/*020,4*/ char* yPivot;
	/*024,4*/ char* xPivot;
	/*028,18*/ undefined4 carryFramesTable_28[6];
	/*040,10*/ undefined4 cameraFramesTable_40[4];
	/*050,18*/ undefined field_0x50_0x68[0x18];
	/*068,4*/ undefined4 field_68;
	/*06c,4*/ undefined4 field_6c;
	/*070,4*/ unsigned int CarryNullFrames;
	/*074,4*/ unsigned int CameraNullFrames;
	/*078,4*/ unsigned int ToolNullFrames;
	/*07c,4*/ ResourceData* PowerLevelScene; // LWS, true
	/*080,4*/ undefined4 field_80;
	/*084,4*/ Point2I* shapePoints; // Point2I[10]
	/*088,4*/ unsigned int shapeCount;
	/*08c,14*/ ObjectUpgradesData upgrades;
	/*0a0,30*/ undefined field_0xa0_0xd0[0x30];
	/*0d0,4*/ float PivotMaxZ;
	/*0d4,4*/ float PivotMinZ;
	/*0d8,6c*/ undefined field_0xd8_0x144[0x6c];
	/*144,4*/ unsigned int count_144;
	/*148,4*/ unsigned int flags;
	/*14c*/
};
static_assert(sizeof(BuildingData) == 0x14c, "");


struct PolyMeshData
{
	/*00,4*/ undefined4 field_0;
	/*04,4*/ undefined4 field_4;
	/*08,4*/ char* partName; // name of LoadObject file.lwo
	/*0c,4*/ unsigned int index;
	/*10,4*/ int int_10;
	/*14,4*/ PolyMeshData* previous;
	/*18*/
};
static_assert(sizeof(PolyMeshData) == 0x18, "");

struct VehicleData
{
	/*000,4*/ int objIndex;
	/*004,4*/ char* WheelNullName;
	/*008,4*/ ResourceData* aeResData1;
	/*00c,4*/ ResourceData* aeResData2; // Optional second ae file (seen for Grannit Grinder legs)
	/*010,18*/ ResourceData* WheelMeshes[6]; // LWO, false
	/*028,18*/ undefined4 wheel_fields_28[6];
	/*040,4*/ unsigned int numWheelNulls;
	/*044,18*/ undefined field_0x44_0x5c[0x18];
	/*05c,4*/ undefined4 field_5c;
	/*060,4*/ undefined4 field_60;
	/*064,4*/ float float_64;
	/*068,4*/ float WheelRadius;
	/*06c,48*/ undefined field_0x6c_0xb4[0x48];
	/*0b4,4*/ char* DrillNullName;
	/*0b8,4*/ char* DepositNullName;
	/*0bc,4*/ char* FireNullName; // "fire laser"
	/*0c0,4*/ char* DriverNullName;
	/*0c4,4*/ char* yPivot;
	/*0c8,4*/ char* xPivot;
	/*0cc,4*/ undefined4 field_cc;
	/*0d0,4*/ undefined4 field_d0;
	/*0d4,4*/ ResourceData* resData_d4;
	/*0d8,4*/ BOOL3 CameraFlipDir;
	/*0dc,4*/ char* CarryNullName;
	/*0e0,4*/ char* CameraNullName;
	/*0e4,1c*/ undefined4 carryFramesTable_e4[7];
	/*100,c*/ undefined field_0x100_0x10c[0xc];
	/*10c,10*/ undefined4 cameraFramesTable_10c[4];
	/*11c,4*/ unsigned int CarryNullFrames;
	/*120,4*/ unsigned int CameraNullFrames;
	/*124,14*/ ObjectUpgradesData upgrades;
	/*138,30*/ undefined field_0x138_0x168[0x30];
	/*168,4*/ float PivotMaxZ;
	/*16c,4*/ float PivotMinZ;
	/*170,54*/ undefined field_0x170_0x1c4[0x54];
	/*1c4,18*/ undefined4 table6_1c4[6];
	/*1dc,4*/ undefined4 field_1dc;
	/*1e0,4*/ PolyMeshData* subdata_1e0;
	/*1e4,4*/ PolyMeshData* subdata_1e4;
	/*1e8,4*/ unsigned int flags; // HoldMissing TRUE -> 0x8
	/*1ec*/
};
static_assert(sizeof(VehicleData) == 0x1ec, "");


struct FlockData
{
	/*00,4*/ FlockSubdata* flocksSubdata1;
	/*04,4*/ FlockSubdata* flocksSubdata2;
	/*08,4*/ unsigned int numSubdata;
	/*0c,4*/ unsigned int hasVector1;
	/*10,4*/ unsigned int hasVector2;
	/*14,4*/ undefined4 field_14;
	/*18,4*/ undefined4 field_18;
	/*1c,4*/ undefined4 field_1c;
	/*20,4*/ undefined4 field_20;
	/*24,4*/ undefined4 field_24;
	/*28*/
};
static_assert(sizeof(FlockData) == 0x28, "");

struct Struct_34
{
	/*00,4*/ unsigned int count_0; // seems to be a count
	/*04,4*/ undefined4 field_4;
	/*08,4*/ LwoFrame* lwoTable_8; // table ptr? -> 0x10 (struct: 0x70)
	/*0c,4*/ IDirect3DRMUserVisual* userVisual_c;
	/*10,4*/ IDirect3DRMViewport2* viewport_10; // IDirect3DRMViewport2 ?
	/*14,4*/ undefined4 param4_14;
	/*18,4*/ undefined4 unkFlags3_18;
	/*1c,4*/ void* ptr_1c;
	/*20,4*/ unsigned int refCount_20;
	/*24,4*/ Struct_34* struct34_24;
	/*28,4*/ IDirect3DRMFrame3* frame_28;
	/*2c,4*/ unsigned int flags;
	/*30,4*/ Struct_34* pool_m_next;
	/*34*/
};
static_assert(sizeof(Struct_34) == 0x34, "");

struct ResourceSubdata
{
	/*00,4*/ char* name;
	/*04,4*/ IDirect3DRMLight* light;
	/*08,4*/ IDirect3DRMMesh* mesh;
	/*0c,4*/ Struct_34* struct34_c;
	/*10*/
};
static_assert(sizeof(ResourceSubdata) == 0x10, "");

struct ActStruct_14 { // structure assigned to ResourceData->field_24 (allocated for ACT,ANIM resource types)
	/*00,4*/ ResourceData* resData; // (init: source of DuplicateResource)
	/*04,4*/ undefined4 field_4; // (init: 0)
	/*08,4*/ undefined4 field_8; // (init: 0)
	/*0c,4*/ IDirect3DRMFrame3* frame; // (init: ResourceData->frame2)
	/*10,4*/ BOOL isUsed; // (init: 1)
	/*14*/
};
static_assert(sizeof(ActStruct_14) == 0x14, "");

struct ResourceData
{
	/*00,4*/ IDirect3DRMFrame3* frame1;
	/*04,4*/ IDirect3DRMFrame3* frame2;
	/*08,4*/ IDirect3DRMFrame3* frame3;
	/*0c,4*/ ResourceSubdata* subdata_c;
	/*10,4*/ ResourceType resType;
	/*14,4*/ ResourceDataFlags flags;
	/*18,4*/ undefined4 field_18;
	/*1c,4*/ undefined4 field_1c;
	/*20,4*/ LiveObject* ownerObj;
	/*24,4*/ ActStruct_14* actstruct_24;
	/*28,4*/ ResourceData* pool_m_next;
	/*2c*/
};
static_assert(sizeof(ResourceData) == 0x2c, "");

// related to Terrain map?
struct LevelStruct_1c
{
	/*00,4*/ ResourceData* resData;
	/*04,8*/ Point2I position;
	/*0c,4*/ undefined4 field_c;
	/*10,4*/ LevelStruct_1c* next;
	/*14,4*/ LevelStruct_1c* previous;
	/*18,4*/ BOOL bool_18;
	/*1c*/
};
static_assert(sizeof(LevelStruct_1c) == 0x1c, "");

struct LevelBlock
{
	/*00,1*/ PredugType predug;
	/*01,1*/ SurfaceTexture texture;
	/*02,1*/ TerrainType terrain;
	/*03,1*/ unsigned char field_3;
	/*04,1*/ unsigned char blockpointer;
	/*05,1*/ CryOreType cryOre;
	/*06,1*/ ErodeType erodeSpeed;
	/*07,1*/ unsigned char field_7;
	/*08,4*/ LevelBlockFlags1 flags1;
	/*0c,4*/ LevelBlockFlags2 flags2;
	/*10,4*/ undefined4 field_10;
	/*14,4*/ float float_14;
	/*18,4*/ LevelStruct_1c* struct1c_18;
	/*1c,4*/ undefined4 field_1c;
	/*20,2*/ short randomness;
	/*22,1*/ undefined field_0x22;
	/*23,1*/ undefined field_0x23;
	/*24,4*/ unsigned int numLandSlides;
	/*28,4*/ unsigned int clickCount;
	/*2c,4*/ undefined4 field_2c;
	/*30,4*/ undefined4 field_30;
	/*34,1*/ unsigned char aiNode;
	/*35,1*/ undefined field_0x35;
	/*36,1*/ undefined field_0x36;
	/*37,1*/ undefined field_0x37;
	/*38,4*/ BOOL fallinUpper;
	/*3c,4*/ float fallinIntensity;
	/*40,4*/ float fallinTimer;
	/*44,4*/ undefined4 field_44;
	/*48*/
};
static_assert(sizeof(LevelBlock) == 0x48, "");


struct CreatureData
{
	/*00,4*/ int objIndex;
	/*04,4*/ ResourceData* aeResData; // ACT, true
	/*08,4*/ undefined4 field_8;
	/*0c,14*/ undefined field_0xc_0x20[0x14];
	/*20,4*/ char* CameraNullName;
	/*24,4*/ unsigned int CameraNullFrames;
	/*28,4*/ BOOL3 CameraFlipDir;
	/*2c,4*/ char* DrillNullName;
	/*30,4*/ char* FootStepNullName;
	/*34,4*/ char* CarryNullName;
	/*38,4*/ char* ThrowNullName;
	/*3c,4*/ char* DepositNullName;
	/*40,4*/ undefined4 field_40;
	/*44,4*/ undefined4 field_44;
	/*48,4*/ ResourceData* resData_48;
	/*4c,4*/ undefined4 field_4c;
	/*50,4*/ undefined4 field_50;
	/*54,10*/ undefined4 cameraFramesTable_54[4];
	/*64,4*/ PolyMeshData* subdata_64;
	/*68,4*/ PolyMeshData* subdata_68;
	/*6c,4*/ PolyMeshData* subdata_6c;
	/*70,4*/ unsigned int flags;
	/*74*/
};
static_assert(sizeof(CreatureData) == 0x74, "");


struct AITaskData
{
	/*00,4*/ AITaskType taskType;
	/*04,4*/ undefined4 field_4;
	/*08,8*/ Point2I position;
	/*10,4*/ LiveObject* object_10;
	/*14,4*/ float unkExpiryTime;
	/*18,4*/ float float_18;
	/*1c,4*/ unsigned int priorityValue;
	/*20,4*/ ObjectType objType;
	/*24,4*/ int objIndex;
	/*28,4*/ int objLevel;
	/*2c,4*/ undefined4 field_2c;
	/*30,8*/ Point2F pointf_30; // probably a table
	/*38,4*/ undefined field_0x38_0x3c[0x4];
	/*3c,4*/ undefined4 mode_3c;
	/*40,4*/ void* ptr_40;
	/*44,4*/ undefined field_0x44_0x48[0x4];
	/*48,4*/ LiveObject* object_48;
	/*4c,4*/ AIPriorityType priorityType;
	/*50,4*/ unsigned int taskStartTime;
	/*54,8*/ undefined field_0x54_0x5c[0x8];
	/*5c,4*/ unsigned int flags_5c; // not set means ptr_40 is assigned
	/*60,4*/ AITaskData* next; // assigned to DAT_004b4358
	/*64,4*/ AITaskData* pool_m_next;
	/*68*/
};
static_assert(sizeof(AITaskData) == 0x68, "");

struct LiveObject
{
	/*000,4*/ ObjectType objType;
	/*004,4*/ int objIndex;
	/*008,4*/ char* customName; // max size is 11 (NOT null-terminated)
	/*00c,4*/ VehicleData* vehicle;
	/*010,4*/ CreatureData* miniFigure;
	/*014,4*/ CreatureData* rockMonster;
	/*018,4*/ BuildingData* building;
	/*01c,4*/ ResourceData* other;
	/*020,4*/ UpgradeData* upgrade;
	/*024,4*/ void* routeptr_24; // Unknown pointer, likely in large allocated table
	/*028,4*/ unsigned int routingBlocksTotal; // total blocks to travel for current route
	/*02c,4*/ unsigned int routingBlocksCurrent; // number of blocks traveled (up to routingBlocksTotal)
	/*030,4*/ int value_30; // Usually 50 (0x32)
	/*034,190*/ float floats_34[100];
	/*1c4,c8*/ float floats_1c4[50];
	/*28c,c*/ Vector3F vector_28c;
	/*298,8*/ Point2F point_298;
	/*2a0,c*/ Vector3F vector_2a0;
	/*2ac,c*/ Vector3F faceDirection; // 1.0 to -1.0 directions that determine rotation with atan2
	/*2b8,4*/ float float_2b8;
	/*2bc,4*/ undefined4 field_2bc;
	/*2c0,4*/ undefined4 field_2c0;
	/*2c4,4*/ undefined4 field_2c4;
	/*2c8,4*/ undefined4 field_2c8;
	/*2cc,4*/ undefined4 field_2cc;
	/*2d0,4*/ undefined4 field_2d0;
	/*2d4,4*/ float float_2d4;
	/*2d8,4*/ BOOL unkbool_2d8;
	/*2dc,4*/ ResourceData* resData_2dc;
	/*2e0,4*/ int index_2e0;
	/*2e4,4*/ ResourceData* resData_2e4;
	/*2e8,4*/ const char* aitaskName1;
	/*2ec,4*/ const char* aitaskName2;
	/*2f0,4*/ AITaskData* aitask_2f0;
	/*2f4,8*/ Point2F point_2f4; // (assigned -1.0f)
	/*2fc,4*/ LiveObject* object_2fc; // other half of object_300
	/*300,4*/ LiveObject* object_300; // other half of object_2fc
	/*304,4*/ LiveObject* carryingThisObject;
	/*308,1c*/ LiveObject* carriedObjects[7];
	/*324,4*/ unsigned int numCarriedObjects;
	/*328,4*/ unsigned int field_328;
	/*32c,4*/ FlockData* flocksData_32c;
	/*330,4*/ unsigned int objLevel;
	/*334,4*/ ObjectStats* stats;
	/*338,4*/ float float_338;
	/*33c,4*/ float float_33c;
	/*340,4*/ float health; // (assigned -1.0f)
	/*344,4*/ float energy; // (assigned -1.0f)
	/*348,4*/ int* tableptr_348; // element size is 0x4
	/*34c,4*/ BOOL mode_34c;
	/*350,4*/ undefined4 field_350;
	/*354,4*/ undefined4 field_354;
	/*358,4*/ undefined4 field_358;
	/*35c,4*/ undefined4 field_35c;
	/*360,4*/ undefined4 field_360;
	/*364,4*/ undefined4 field_364;
	/*368,4*/ undefined4 field_368;
	/*36c,4*/ LiveObject* drivenObject; // same as drivingThisObject
	/*370,14*/ ToolType carriedTools[5];
	/*384,4*/ unsigned int numCarriedTools;
	/*388,4*/ undefined4 field_388;
	/*38c,4*/ undefined4 field_38c;
	/*390,4*/ undefined4 field_390;
	/*394,4*/ undefined4 field_394;
	/*398,4*/ undefined4 field_398;
	/*39c,4*/ undefined4 field_39c;
	/*3a0,4*/ undefined4 field_3a0;
	/*3a4,4*/ undefined4 field_3a4;
	/*3a8,4*/ undefined4 field_3a8;
	/*3ac,4*/ undefined4 field_3ac;
	/*3b0,4*/ undefined4 field_3b0;
	/*3b4,4*/ undefined4 field_3b4;
	/*3b8,4*/ undefined4 field_3b8;
	/*3bc,4*/ undefined4 field_3bc;
	/*3c0,4*/ LiveObject* object_3c0;
	/*3c4,4*/ undefined4 field_3c4;
	/*3c8,4*/ undefined4 field_3c8;
	/*3cc,4*/ LiveObject* object_3cc;
	/*3d0,4*/ undefined4 field_3d0;
	/*3d4,4*/ float elapsedTime1; // elapsed time counter 1
	/*3d8,4*/ float elapsedTime2; // elapsed time counter 2
	/*3dc,4*/ float activityElapsedTime; // elapsed time since last order?
	/*3e0,4*/ LiveFlags1 flags1_3e0;
	/*3e4,4*/ LiveFlags2 flags2_3e4;
	/*3e8,4*/ LiveFlags3 flags3_3e8; // (assigned 0, flags?)
	/*3ec,4*/ LiveFlags4 flags4_3ec;
	/*3f0,4*/ LiveFlags5 flags5_3f0; // (assigned 0, flags?)
	/*3f4,4*/ undefined4 field_3f4;
	/*3f8,4*/ undefined4 field_3f8;
	/*3fc,4*/ undefined4 field_3fc;
	/*400,4*/ undefined4 field_400;
	/*404,4*/ undefined4 field_404;
	/*408,4*/ LiveObject* pool_m_next;
	/*40c*/
};
static_assert(sizeof(LiveObject) == 0x40c, "");

struct ObjectStats
{
	/*000,4*/ undefined4 field_0; // == 0x30 for built-in object stats
	/*004,4*/ undefined4 field_4;
	/*008,4*/ undefined4 field_8;
	/*00c,4*/ undefined4 field_c;
	/*010,4*/ undefined4 field_10;
	/*014,4*/ undefined4 field_14;
	/*018,4*/ undefined4 field_18;
	/*01c,4*/ undefined4 field_1c;
	/*020,4*/ float RouteSpeed; // (leveled)
	/*024,48*/ float DrillTimes[18]; // (leveled, table of surface type times)
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
	/*0a8,4*/ int BuildingBase; // (from: FUN_00408bb0, invalid: -1, either ptr or basenumber)
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
	/*0fc,4*/ int UpgradeCostOre; // Carry:Scan:Speed:Drill (requires all 4)
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
	/*144,4*/ ObjectStatsFlags1 flags1;
	/*148,4*/ ObjectStatsFlags2 flags2;
	/*14c,4*/ ObjectStatsFlags3 flags3;
	/*150*/
};
static_assert(sizeof(ObjectStats) == 0x150, "");


#pragma endregion
} /* namespace lego */

#pragma pack(pop)
