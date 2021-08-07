#pragma once

#include "BasicTypes.h"
#include "BasicEnums.h"


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


struct ActFrameResource
{
	/*00,4*/ ActFrameResource* previous;
	/*04,4*/ void* lwsStruct38; // LWS struct
	/*08,4*/ IDirect3DRMAnimationSet2* animSet; // (not LWS)
	/*0c,4*/ BOOL isLWSFile;
	/*10,4*/ IDirect3DRMFrame3* rootFrame; // (not LWS)
	/*14,4*/ IDirect3DRMFrame3** framesTable; // (not LWS) table of COM objects, length is count_18
	/*18,4*/ uint framesCount; // (not LWS)
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
	/*0058,24*/ char* Types_TABLE[9]; // PTR_0076bdd8
	/*007c,24*/ char* Extensions_TABLE[9]; // PTR_0076bdfc
	/*00a0,4*/ char* CfgRootName; // PTR_0076be20
	/*00a4,4*/ undefined4 DAT_0076be24; // DAT_0076be24
	/*00a8,4*/ undefined4 field_a8; // DAT_0076be28
	/*00ac,4*/ undefined4 field_ac; // referenced by addr to get last item of g_Textures_TABLE
	/*00b0,4*/ undefined4 field_b0; // DAT_0076be30
	/*00b4,1f40*/ SharedTextureResource Textures_TABLE[1000]; // PTR_0076be34
	/*1ff4,4*/ uint Textures_COUNT; // DAT_0076dd74
	/*1ff8,4*/ pointer soundCallback; // PTR_0076dd78
	/*1ffc,4*/ void* soundCallback_VALUE; // PTR_0076dd7c
	/*2000,4*/ pointer drawCallback; // PTR_0076dd80
	/*2004,4*/ void* drawCallback_VALUE; // PTR_0076dd84
	/*2008,4*/ char* SharedTextures; // PTR_0076dd88
	/*200c,4*/ uint SceneFogColor; // DAT_0076dd8c
	/*2010,4*/ uint pool_g_COUNT; // DAT_0076dd90
	/*2014,4*/ uint pool_g_INITFLAGS; // DAT_0076dd94
	/*2018*/
};
static_assert(sizeof(ResourceManager) == 0x2018, "");


struct SharedObjectResource
{
	/*0,4*/ char* resName;
	/*4,4*/ Struct_34* lwoStruct34;
	/*8*/
};
static_assert(sizeof(SharedObjectResource) == 0x8, "");

struct LwoFrame
{
	/*00,4*/ uint dwSize;
	/*04,60*/ undefined field_0x4_0x64[0x60];
	/*64,4*/ undefined4 field_64;
	/*68,4*/ undefined field_0x68_0x6c[0x4];
	/*6c,4*/ uint flags;
	/*70*/
};
static_assert(sizeof(LwoFrame) == 0x70, "");

struct ObjectUpgradePartData
{
	/*00,4*/ uint level;
	/*04,4*/ int NullInstance;
	/*08,4*/ char* NullObjectName;
	/*0c,4*/ char* WeaponName;
	/*10,4*/ UpgradeData* upgradeData;
	/*14*/
};
static_assert(sizeof(ObjectUpgradePartData) == 0x14, "");

struct ObjectUpgradesData
{
	/*00,4*/ ObjectUpgradePartData* parts; // always ObjectUpgradePartData[200]
	/*04,4*/ uint count;
	/*08,4*/ int currentLevel;
	/*0c,4*/ uint levelsMask; // [carry][scan][speed][drill]
	/*10,4*/ LiveObject** upgradeObjs;
	/*14*/
};
static_assert(sizeof(ObjectUpgradesData) == 0x14, "");


struct CreatureData
{
	/*00,4*/ int objIndex;
	/*04,4*/ ResourceData* aeResData; // ACT, true
	/*08,4*/ undefined4 field_8;
	/*0c,14*/ undefined field_0xc_0x20[0x14];
	/*20,4*/ char* CameraNullName;
	/*24,4*/ uint CameraNullFrames;
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
	/*70,4*/ uint flags;
	/*74*/
};
static_assert(sizeof(CreatureData) == 0x74, "");


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
	/*070,4*/ uint CarryNullFrames;
	/*074,4*/ uint CameraNullFrames;
	/*078,4*/ uint ToolNullFrames;
	/*07c,4*/ ResourceData* PowerLevelScene; // LWS, true
	/*080,4*/ undefined4 field_80;
	/*084,4*/ Point2I* shapePoints; // Point2I[10]
	/*088,4*/ uint shapeCount;
	/*08c,14*/ ObjectUpgradesData upgrades;
	/*0a0,30*/ undefined field_0xa0_0xd0[0x30];
	/*0d0,4*/ float PivotMaxZ;
	/*0d4,4*/ float PivotMinZ;
	/*0d8,6c*/ undefined field_0xd8_0x144[0x6c];
	/*144,4*/ uint count_144;
	/*148,4*/ uint flags;
	/*14c*/
};
static_assert(sizeof(BuildingData) == 0x14c, "");


struct PolyMeshData
{
	/*00,4*/ undefined4 field_0;
	/*04,4*/ undefined4 field_4;
	/*08,4*/ char* partName; // name of LoadObject file.lwo
	/*0c,4*/ uint index;
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
	/*040,4*/ uint numWheelNulls;
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
	/*11c,4*/ uint CarryNullFrames;
	/*120,4*/ uint CameraNullFrames;
	/*124,14*/ ObjectUpgradesData upgrades;
	/*138,30*/ undefined field_0x138_0x168[0x30];
	/*168,4*/ float PivotMaxZ;
	/*16c,4*/ float PivotMinZ;
	/*170,54*/ undefined field_0x170_0x1c4[0x54];
	/*1c4,18*/ undefined4 table6_1c4[6];
	/*1dc,4*/ undefined4 field_1dc;
	/*1e0,4*/ PolyMeshData* subdata_1e0;
	/*1e4,4*/ PolyMeshData* subdata_1e4;
	/*1e8,4*/ uint flags; // HoldMissing TRUE -> 0x8
	/*1ec*/
};
static_assert(sizeof(VehicleData) == 0x1ec, "");


struct Struct_34
{
	/*00,4*/ uint count_0; // seems to be a count
	/*04,4*/ undefined4 field_4;
	/*08,4*/ LwoFrame* lwoTable_8; // table ptr? -> 0x10 (struct: 0x70)
	/*0c,4*/ IDirect3DRMUserVisual* userVisual_c;
	/*10,4*/ IDirect3DRMViewport2* viewport_10; // IDirect3DRMViewport2 ?
	/*14,4*/ undefined4 param4_14;
	/*18,4*/ undefined4 unkFlags3_18;
	/*1c,4*/ void* ptr_1c;
	/*20,4*/ uint refCount_20;
	/*24,4*/ Struct_34* struct34_24;
	/*28,4*/ IDirect3DRMFrame3* frame_28;
	/*2c,4*/ uint flags;
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

