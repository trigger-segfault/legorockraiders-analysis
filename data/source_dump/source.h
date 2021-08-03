#pragma once
#include "datatypes.h"
#include "functypes.h"

//00400000


// <LegoRR.exe @00401000>
undefined Main_InitAdvisors(char * keyBasePath, Struct_bc * structbc, undefined4 ptr_1c);
// <LegoRR.exe @004011c0>
void FUN_004011c0(void);
// <LegoRR.exe @00401210>
void FUN_00401210(float param_1);
// <LegoRR.exe @00401240>
float10 Vector2_Distance(Point2F * a, Point2F * b);
// <LegoRR.exe @00401270>
undefined Main_LoadAdvisorAnims(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @004013a0>
BOOL Game_GetAdvisor(char * advisorName, int * out_index);
// <LegoRR.exe @004013e0>
Vector3F * Vector3_CrossProduct(Vector3F * out_vector, Vector3F * a, Vector3F * b);
// <LegoRR.exe @00401430>
BOOL Res_GetAdvisorResource(char * advisorName, int * out_index);
// <LegoRR.exe @00401470>
Vector3F * Vector3_Add(Vector3F * out_vector, Vector3F * a, Vector3F * b);
// <LegoRR.exe @004014a0>
void Main_LoadAdvisorPositions(CFGProperty * root, char * keyBasePath, int screenWidth, int screenHeight);
// <LegoRR.exe @00401630>
Vector3F * Vector3_Subtract(Vector3F * out_vector, Vector3F * a, Vector3F * b);
// <LegoRR.exe @00401660>
Vector3F * Vector3_Scale(Vector3F * out_vector, Vector3F * a, float scalar);
// <LegoRR.exe @00401690>
Vector3F * Vector3_Normalize(Vector3F * ref_vector);
// <LegoRR.exe @004016f0>
undefined Res_AddAdvisorPosition(int param_1, undefined4 param_2, int param_3, undefined4 param_4, int param_5, undefined4 param_6, undefined4 param_7);
// <LegoRR.exe @00401780>
undefined FUN_00401780(int param_1, int param_2, undefined4 param_3, undefined4 param_4);
// <LegoRR.exe @004017d0>
undefined FUN_004017d0(int param_1, undefined4 * param_2, undefined4 * param_3);
// <LegoRR.exe @00401800>
BOOL FUN_00401800(int param_1, int param_2);
// <LegoRR.exe @00401870>
undefined FUN_00401870(int param_1);
// <LegoRR.exe @004018d0>
undefined FUN_004018d0(float param_1);
// <LegoRR.exe @004019b0>
BOOL FUN_004019b0(int param_1, float param_2);
// <LegoRR.exe @00401a60>
void Lego_ClearFlag2__004b41bc(void);
// <LegoRR.exe @00401a70>
undefined FUN_00401a70(float param_1);
// <LegoRR.exe @00401b30>
ProgrammerMode Config_GetProgrammerMode(void);
// <LegoRR.exe @00401b40>
char * Game_GetStartLevel(void);
// <LegoRR.exe @00401b60>
uint Lego_GetFlag1__004b41bc(void);
// <LegoRR.exe @00401b70>
int Config_GetResolutionWidth(void);
// <LegoRR.exe @00401b80>
int Config_GetResolutionHeight(void);
// <LegoRR.exe @00401b90>
ImageFont * FUN_00401b90(ImageFont * font, char * format, ...);
// <LegoRR.exe @00401bc0>
void FUN_00401bc0(ImageFont * param_1, uint * param_2, int * param_3, byte * param_4, ...);
// <LegoRR.exe @00401bf0>
int Game_GetAIPriority(char * aiPriorityName, int * out_index);
// <LegoRR.exe @00401c30>
void ReservedPool<AITask>__Init(void);
// <LegoRR.exe @00401f40>
undefined FUN_00401f40(int param_1, int param_2, Point2I * param_3);
// <LegoRR.exe @00401fa0>
void FUN_00401fa0(AITaskData * aiTask, AIPriorityType priorityIndex);
// <LegoRR.exe @00401fd0>
void Game_SetAITaskValue2(int index, undefined4 aiTaskValue);
// <LegoRR.exe @00401fe0>
void Game_SetIsPriorityDisabled(int priorityIndex, BOOL isDisabled);
// <LegoRR.exe @00401ff0>
BOOL Game_IsPriorityDisabled(int priorityIndex);
// <LegoRR.exe @00402000>
void ReservedPool<AITask>__Cleanup(void);
// <LegoRR.exe @00402040>
undefined FUN_00402040(BOOL param_1);
// <LegoRR.exe @004020b0>
undefined Level_SetNoGather(BOOL noGather);
// <LegoRR.exe @00402120>
undefined4 FUN_00402120(AITaskData * param_1);
// <LegoRR.exe @00402140>
void free2(undefined * param_1);
// <LegoRR.exe @00402150>
undefined FUN_00402150(undefined1 param_1);
// <LegoRR.exe @00402240>
undefined FUN_00402240(AITaskData * * ref_aiTask);
// <LegoRR.exe @00402440>
void FUN_00402440(Point2I * position, BOOL param_2, BOOL param_3);
// <LegoRR.exe @00402530>
void FUN_00402530(AITaskData * aiTask, BOOL param_2);
// <LegoRR.exe @004025a0>
undefined LiveObject_Create_InitCanShoot(LiveObject * liveObj);
// <LegoRR.exe @004025f0>
undefined FUN_004025f0(LiveObject * liveObj);
// <LegoRR.exe @00402630>
BOOL FUN_00402630(AITaskData * aiTask, LiveObject * liveObj);
// <LegoRR.exe @00402650>
void FUN_00402650(LiveObject * liveObj, float param_2);
// <LegoRR.exe @004026d0>
void FUN_004026d0(Point2I * position);
// <LegoRR.exe @00402730>
undefined FUN_00402730(int count);
// <LegoRR.exe @00402780>
undefined FUN_00402780(LiveObject * liveObj);
// <LegoRR.exe @004027c0>
undefined FUN_004027c0(LiveObject * liveObj, TrainedFlags training, BOOL param_3);
// <LegoRR.exe @00402890>
undefined FUN_00402890(LiveObject * liveObj);
// <LegoRR.exe @00402970>
undefined FUN_00402970(undefined4 param_1);
// <LegoRR.exe @004029a0>
BOOL FUN_004029a0(AITaskData * aiTask, Point2I * * param_2);
// <LegoRR.exe @004029d0>
undefined FUN_004029d0(undefined4 liveObj);
// <LegoRR.exe @004029f0>
BOOL FUN_004029f0(AITaskData * aiTask, LiveObject * liveObj);
// <LegoRR.exe @00402a10>
undefined FUN_00402a10(Point2I * param_1, undefined4 param_2);
// <LegoRR.exe @00402a60>
undefined FUN_00402a60(undefined4 param_1);
// <LegoRR.exe @00402a90>
undefined FUN_00402a90(undefined4 param_1, BOOL param_2);
// <LegoRR.exe @00402ae0>
undefined4 FUN_00402ae0(AITaskData * aiTask, Point2I * * param_2);
// <LegoRR.exe @00402b50>
BOOL FUN_00402b50(AITaskData * aiTask, Point2I * * param_2);
// <LegoRR.exe @00402ba0>
BOOL FUN_00402ba0(AITaskData * aiTask, Point2I * * param_2);
// <LegoRR.exe @00402bd0>
BOOL FUN_00402bd0(AITaskData * aiTask, Point2I * * param_2);
// <LegoRR.exe @00402c00>
undefined FUN_00402c00(AITaskData * param_1);
// <LegoRR.exe @00402c60>
BOOL FUN_00402c60(int param_1, int param_2);
// <LegoRR.exe @00402c80>
BOOL FUN_00402c80(Point2I * position, BOOL param_2);
// <LegoRR.exe @00402d70>
undefined FUN_00402d70(Point2I * position);
// <LegoRR.exe @00402df0>
undefined FUN_00402df0(LiveObject * liveObj);
// <LegoRR.exe @00402e60>
undefined FUN_00402e60(LiveObject * liveObj, BOOL param_2);
// <LegoRR.exe @00402ea0>
undefined FUN_00402ea0(LiveObject * liveObj, undefined4 param_2);
// <LegoRR.exe @00402ee0>
undefined FUN_00402ee0(Point2I * position);
// <LegoRR.exe @00402f60>
undefined FUN_00402f60(Point2I * param_1);
// <LegoRR.exe @00402fe0>
undefined FUN_00402fe0(Point2I * param_1, undefined4 param_2);
// <LegoRR.exe @00403010>
undefined FUN_00403010(int * param_1);
// <LegoRR.exe @004030c0>
undefined4 FUN_004030c0(undefined4 param_1);
// <LegoRR.exe @00403110>
undefined4 FUN_00403110(int param_1);
// <LegoRR.exe @004031a0>
undefined FUN_004031a0(int * param_1, int param_2, undefined4 * param_3, int param_4);
// <LegoRR.exe @00403250>
undefined FUN_00403250(LiveObject * liveObj, undefined4 param_2);
// <LegoRR.exe @004032f0>
undefined FUN_004032f0(LiveObject * liveObj);
// <LegoRR.exe @00403320>
undefined FUN_00403320(undefined4 * param_1);
// <LegoRR.exe @00403360>
undefined FUN_00403360(int * param_1);
// <LegoRR.exe @004033d0>
undefined FUN_004033d0(LiveObject * liveObj);
// <LegoRR.exe @00403410>
undefined FUN_00403410(undefined4 * param_1);
// <LegoRR.exe @00403450>
undefined FUN_00403450(LiveObject * liveObj);
// <LegoRR.exe @00403490>
undefined FUN_00403490(LiveObject * liveObj);
// <LegoRR.exe @004034f0>
undefined FUN_004034f0(int * param_1, undefined4 * param_2, undefined4 param_3);
// <LegoRR.exe @00403540>
undefined FUN_00403540(LiveObject * liveObj, undefined4 param_2);
// <LegoRR.exe @00403580>
undefined FUN_00403580(int * param_1, int param_2, undefined4 param_3);
// <LegoRR.exe @004035f0>
undefined FUN_004035f0(int param_1, undefined4 param_2);
// <LegoRR.exe @00403630>
undefined FUN_00403630(int param_1, int param_2, int param_3, int param_4);
// <LegoRR.exe @00403680>
undefined FUN_00403680(ObjectType objType, int objLevel, int objIndex, Point2I * position, undefined4 param_5, Point2F * pointFloat, BOOL param_7);
// <LegoRR.exe @00403740>
undefined FUN_00403740(Point2I * position, ObjectType objType, int objIndex, int objLevel);
// <LegoRR.exe @004037f0>
AITaskData * FUN_004037f0(LiveObject * liveObj, ObjectType objType, int objIndex, int objLevel);
// <LegoRR.exe @00403840>
void FUN_00403840(LiveObject * liveObj);
// <LegoRR.exe @004038d0>
undefined FUN_004038d0(LiveObject * liveObj);
// <LegoRR.exe @00403900>
undefined FUN_00403900(LiveObject * liveObj);
// <LegoRR.exe @00403940>
undefined FUN_00403940(undefined4 liveObj);
// <LegoRR.exe @00403960>
undefined4 FUN_00403960(int * param_1, int param_2);
// <LegoRR.exe @00403980>
undefined FUN_00403980(LiveObject * liveObj);
// <LegoRR.exe @00403a00>
BOOL FUN_00403a00(AITaskData * aiTask, LiveObject * liveObj);
// <LegoRR.exe @00403a20>
undefined FUN_00403a20(LiveObject * liveObj, BOOL param_2);
// <LegoRR.exe @00403a70>
undefined FUN_00403a70(LiveObject * liveObj);
// <LegoRR.exe @00403a90>
undefined FUN_00403a90(LiveObject * liveObj);
// <LegoRR.exe @00403b30>
undefined FUN_00403b30(LiveObject * holderObj, AITaskType taskType, LiveObject * carriedObj);
// <LegoRR.exe @00403c40>
undefined FUN_00403c40(LiveObject * liveObj1, int param_2, LiveObject * liveObj2, BOOL param_4);
// <LegoRR.exe @00403e20>
void FUN_00403e20(LiveObject * liveObj);
// <LegoRR.exe @00403e40>
undefined4 FUN_00403e40(AITaskData * aiTask, LiveObject * liveObj);
// <LegoRR.exe @00403e60>
void FUN_00403e60(LiveObject * liveObj);
// <LegoRR.exe @00403e90>
void FUN_00403e90(LiveObject * liveObj);
// <LegoRR.exe @00403f60>
void FUN_00403f60(AITaskData * aiTask, AIPriorityType priorityIndex);
// <LegoRR.exe @00403fa0>
void FUN_00403fa0(AITaskData * aiTask);
// <LegoRR.exe @00403fd0>
undefined Game_UnkLiveObjectHandleDynamite(LiveObject * liveObj);
// <LegoRR.exe @00404030>
undefined FUN_00404030(LiveObject * liveObj);
// <LegoRR.exe @004040c0>
AITaskData * FUN_004040c0(LiveObject * liveObj);
// <LegoRR.exe @004040e0>
BOOL LiveObject_IsCurrentTaskType(LiveObject * liveObj, AITaskType taskType);
// <LegoRR.exe @00404110>
undefined4 FUN_00404110(LiveObject * liveObj);
// <LegoRR.exe @00404180>
undefined4 FUN_00404180(int param_1, float * param_2);
// <LegoRR.exe @004041b0>
undefined4 FUN_004041b0(LiveObject * liveObj, float * param_2);
// <LegoRR.exe @00404d30>
undefined4 FUN_00404d30(float * param_1, float * param_2, float * param_3);
// <LegoRR.exe @00404e00>
undefined FUN_00404e00(int * param_1);
// <LegoRR.exe @00404e40>
undefined FUN_00404e40(ObjectType objType, int objIndex, int objLevel);
// <LegoRR.exe @00404e80>
undefined4 FUN_00404e80(int * param_1, int * param_2);
// <LegoRR.exe @00404ef0>
undefined4 FUN_00404ef0(int * param_1, LiveObject * liveObj_2, float * param_3, float * param_4, undefined4 * param_5, int param_6, int param_7);
// <LegoRR.exe @00405880>
undefined FUN_00405880(void);
// <LegoRR.exe @00405b40>
undefined FUN_00405b40(void);
// <LegoRR.exe @00406290>
undefined FUN_00406290(undefined4 * param_1, int param_2, LiveObject * liveObj);
// <LegoRR.exe @00406310>
void LiveObject__ReleaseTaskReferences(LiveObject * liveObj);
// <LegoRR.exe @00406330>
undefined FUN_00406330(undefined4 * param_1);
// <LegoRR.exe @00406370>
AITaskData * ReservedPool<AITask>__Next(AITaskType taskType);
// <LegoRR.exe @004063b0>
void ReservedPool<AITask>__Release(AITaskData * param_1, BOOL param_2);
// <LegoRR.exe @004063f0>
void ReservedPool<AITask>__Alloc(void);
// <LegoRR.exe @00406470>
BOOL FUN_00406470(undefined * taskFunction, LiveObject * liveObj);
// <LegoRR.exe @00406500>
IDirectDraw4 * Draw_GetDirectDraw(void);
// <LegoRR.exe @00406510>
IDirectDrawSurface4 * Draw_GetDrawingSurface(void);
// <LegoRR.exe @00406520>
undefined FUN_00406520(float * param_1, float * param_2, float * param_3, float * param_4, float * param_5, float param_6);
// <LegoRR.exe @00406660>
float10 FUN_00406660(float * param_1, float * param_2);
// <LegoRR.exe @00406690>
undefined FUN_00406690(float * param_1, float param_2);
// <LegoRR.exe @004066e0>
float10 FUN_004066e0(uint * param_1);
// <LegoRR.exe @00406750>
undefined FUN_00406750(uint * param_1, float * param_2, float * param_3, float * param_4, float * param_5, uint param_6);
// <LegoRR.exe @004067f0>
uint FUN_004067f0(uint * param_1, float param_2, float * param_3);
// <LegoRR.exe @004068b0>
BOOL Creature_IsCameraFlipDir(CreatureData * creature);
// <LegoRR.exe @004068c0>
BOOL Res_LoadAEFileCreature(CreatureData * creature, undefined4 index, ResourceData * resRoot, char * aeFilename, char * rootName);
// <LegoRR.exe @00406b30>
undefined FUN_00406b30(CreatureData * creature, BOOL param_2);
// <LegoRR.exe @00406b60>
undefined FUN_00406b60(CreatureData * creature, BOOL param_2);
// <LegoRR.exe @00406b90>
undefined FUN_00406b90(CreatureData * creature, int param_2, int param_3);
// <LegoRR.exe @00406bc0>
void FUN_00406bc0(BasicObjectData * basicObjData, BOOL use3rdFrame);
// <LegoRR.exe @00406be0>
void Creature_Duplicate(CreatureData * in_creature, CreatureData * out_creature);
// <LegoRR.exe @00406c40>
void Creature_DoCallbacks(CreatureData * creature, float elapsed);
// <LegoRR.exe @00406c60>
float10 FUN_00406c60(CreatureData * creature, float elapsed, uint param_3);
// <LegoRR.exe @00406cd0>
float10 Creature_GetAnimFloat10(CreatureData * creature);
// <LegoRR.exe @00406cf0>
void Creature_SetOrientation(CreatureData * creature, float x, float y);
// <LegoRR.exe @00406d20>
void Creature_SetPosition(CreatureData * creature, float x, float y, GetSurfaceZCallback * getZcallback, LevelSurfaceMap * surfMap);
// <LegoRR.exe @00406d60>
ResourceData * LiveObject_GetAEResource(BasicObjectData * basicObjData);
// <LegoRR.exe @00406d70>
undefined4 FUN_00406d70(CreatureData * creature, char * activityName, float elapsed);
// <LegoRR.exe @00406df0>
void Creature_Destroy(CreatureData * creature);
// <LegoRR.exe @00406e80>
ResourceData * FUN_00406e80(BasicObjectData * basicObjData, undefined4 name, undefined4 param_3);
// <LegoRR.exe @00406eb0>
ResourceData * Creature_GetCameraNull(CreatureData * creature, int cameraIndex);
// <LegoRR.exe @00406ee0>
ResourceData * Creature_GetDrillNull(CreatureData * creature);
// <LegoRR.exe @00406f10>
ResourceData * Creature_GetCarryNull(CreatureData * creature);
// <LegoRR.exe @00406f40>
ResourceData * Creature_GetDepositNull(CreatureData * creature);
// <LegoRR.exe @00406f70>
BOOL FUN_00406f70(CreatureData * creature);
// <LegoRR.exe @00406fc0>
float10 LiveObject_GetCreatureResFloat(CreatureData * creature);
// <LegoRR.exe @00406fe0>
void Main_Init_Bubble(void);
// <LegoRR.exe @00407170>
undefined Main_Load_Bubbles(CFGProperty * root);
// <LegoRR.exe @00407230>
int Main_GetBubbleIndex(char * bubbleName);
// <LegoRR.exe @00407270>
void Game_ToggleObjectUIsAlwaysVisible(void);
// <LegoRR.exe @00407290>
undefined4 FUN_00407290(void);
// <LegoRR.exe @004072a0>
undefined FUN_004072a0(int param_1);
// <LegoRR.exe @004072d0>
undefined FUN_004072d0(LiveObject * liveObj);
// <LegoRR.exe @00407340>
undefined FUN_00407340(LiveObject * liveObj);
// <LegoRR.exe @00407380>
undefined FUN_00407380(LiveObject * liveObj);
// <LegoRR.exe @004073e0>
undefined FUN_004073e0(int * param_1);
// <LegoRR.exe @00407440>
undefined FUN_00407440(int * param_1, undefined4 param_2);
// <LegoRR.exe @00407470>
undefined FUN_00407470(LiveObject * liveObj);
// <LegoRR.exe @004074d0>
undefined FUN_004074d0(float param_1);
// <LegoRR.exe @004077f0>
undefined FUN_004077f0(undefined4 * param_1, float param_2, int * param_3, undefined4 param_4);
// <LegoRR.exe @00407890>
undefined4 FUN_00407890(int * param_1, float * param_2);
// <LegoRR.exe @00407940>
undefined FUN_00407940(int param_1, undefined4 * param_2);
// <LegoRR.exe @00407c90>
BOOL Res_LoadAEFileBuilding(BuildingData * building, int index, ResourceData * resData, char * filename, char * rootName);
// <LegoRR.exe @00408210>
undefined FUN_00408210(int param_1, int param_2);
// <LegoRR.exe @00408290>
undefined4 FUN_00408290(BuildingData * param_1, undefined4 * out_param_2);
// <LegoRR.exe @004082b0>
void Object_SetOwnerObject(BasicObjectData * basicObjData, LiveObject * liveObj);
// <LegoRR.exe @004082d0>
void LiveObject_BuildingUnkUpgrades(BuildingData * building, char * frameName);
// <LegoRR.exe @004084a0>
undefined4 FUN_004084a0(BuildingData * building, char * activityName, float elapsed);
// <LegoRR.exe @00408520>
int FUN_00408520(BuildingData * param_1, int param_2);
// <LegoRR.exe @00408550>
void Building_Duplicate(BuildingData * in_building, BuildingData * out_building);
// <LegoRR.exe @004085a0>
undefined FUN_004085a0(BuildingData * param_1, BOOL param_2);
// <LegoRR.exe @004085d0>
undefined Object_GetFlag8(BasicObjectData * basicObjData);
// <LegoRR.exe @004085f0>
void Building_SetOrientation(BuildingData * building, float x, float y);
// <LegoRR.exe @00408640>
void Building_SetPosition(BuildingData * building, float x, float y, undefined * getZcallback, LevelSurfaceMap * surfMap);
// <LegoRR.exe @004086a0>
ResourceData * Building_GetCarryNull(BuildingData * building, int carryIndex);
// <LegoRR.exe @004086e0>
ResourceData * Building_GetDepositNull(BuildingData * building);
// <LegoRR.exe @00408710>
ResourceData * Building_GetEntranceNull(BuildingData * building);
// <LegoRR.exe @00408740>
ResourceData * Building_GetToolNull(BuildingData * building, int toolIndex);
// <LegoRR.exe @00408780>
int Res_GetBuildingCarryNullFrames(BuildingData * building);
// <LegoRR.exe @00408790>
float10 FUN_00408790(BuildingData * building, float elapsed, uint param_3);
// <LegoRR.exe @00408860>
float10 Building_GetAnimFloat14_zero(BuildingData * building);
// <LegoRR.exe @00408870>
void LiveObject_ReleaseBuilding(BuildingData * building);
// <LegoRR.exe @004088a0>
BOOL FUN_004088a0(BuildingData * building, int levelBit, BOOL condition);
// <LegoRR.exe @004088d0>
void LiveObject_BuildingChangeUpgradeParts(BuildingData * building, int objLevel);
// <LegoRR.exe @00408900>
float10 FUN_00408900(float * param_1, float * param_2, float * param_3);
// <LegoRR.exe @00408a30>
float10 FUN_00408a30(float * param_1, float * param_2, float * param_3, uint param_4);
// <LegoRR.exe @00408a90>
undefined FUN_00408a90(float * param_1, float * param_2, float * param_3, float * param_4);
// <LegoRR.exe @00408b20>
undefined FUN_00408b20(float * param_1, float * param_2, float * param_3, float * param_4);
// <LegoRR.exe @00408bb0>
uint Game_GetBuildingBase(char * name);
// <LegoRR.exe @00408c10>
undefined FUN_00408c10(undefined4 param_1, LiveObject * liveObj);
// <LegoRR.exe @00408ca0>
undefined4 FUN_00408ca0(undefined4 param_1, int param_2, int param_3);
// <LegoRR.exe @00408d40>
int FUN_00408d40(int param_1, int param_2, int param_3);
// <LegoRR.exe @00408d80>
undefined Level_SpawnCarryableObject(Point2I * position, ObjectType objType, int objIndex, int objLevel, int count);
// <LegoRR.exe @00408df0>
undefined FUN_00408df0(int * param_1, uint * param_2, uint param_3);
// <LegoRR.exe @00408fd0>
BOOL FUN_00408fd0(Point2I * param_1);
// <LegoRR.exe @00408ff0>
int FUN_00408ff0(Point2I * param_1, int * param_2);
// <LegoRR.exe @00409040>
undefined FUN_00409040(int * param_1);
// <LegoRR.exe @00409080>
undefined FUN_00409080(Point2I * position);
// <LegoRR.exe @00409110>
undefined FUN_00409110(undefined4 param_1);
// <LegoRR.exe @004091a0>
uint FUN_004091a0(undefined4 param_1);
// <LegoRR.exe @00409230>
BOOL FUN_00409230(Point2I * position);
// <LegoRR.exe @00409280>
undefined4 * Lego_AllocStruct_d4(Point2I * position);
// <LegoRR.exe @004092e0>
undefined FUN_004092e0(int * param_1);
// <LegoRR.exe @00409380>
undefined4 FUN_00409380(int * param_1, int param_2);
// <LegoRR.exe @004093a0>
undefined4 FUN_004093a0(int * param_1, int param_2);
// <LegoRR.exe @00409480>
undefined FUN_00409480(int param_1);
// <LegoRR.exe @00409530>
undefined FUN_00409530(Point2I * position);
// <LegoRR.exe @004096c0>
undefined4 FUN_004096c0(int objIndex, Point2I * param_2, undefined4 param_3, Point2I * param_4, uint count);
// <LegoRR.exe @00409870>
undefined FUN_00409870(Point2I * param_1);
// <LegoRR.exe @00409900>
void FUN_00409900(void);
// <LegoRR.exe @00409920>
undefined FUN_00409920(undefined * param_1);
// <LegoRR.exe @00409970>
undefined FUN_00409970(int param_1);
// <LegoRR.exe @004099c0>
undefined FUN_004099c0(uint param_1, int * param_2, undefined4 param_3, uint * param_4, uint param_5, int param_6);
// <LegoRR.exe @00409a60>
uint * FUN_00409a60(uint * param_1, int param_2);
// <LegoRR.exe @00409c00>
undefined FUN_00409c00(int * param_1);
// <LegoRR.exe @00409c70>
undefined Lego_SetBool_004b9a54(BOOL param_1);
// <LegoRR.exe @00409c80>
undefined FUN_00409c80(LiveObject * liveObj);
// <LegoRR.exe @00409e50>
undefined FUN_00409e50(LiveObject * liveObj);
// <LegoRR.exe @00409f20>
undefined FUN_00409f20(LiveObject * liveObj);
// <LegoRR.exe @00409ff0>
undefined Main_ShowCreditsFiles(char * textFile, ImageFont * font, char * aviFile);
// <LegoRR.exe @0040a300>
void FUN_0040a300(void);
// <LegoRR.exe @0040a330>
undefined Main_LoadHealthFont(char * dirname, char * fileBaseName);
// <LegoRR.exe @0040a3e0>
undefined FUN_0040a3e0(int * param_1, uint param_2);
// <LegoRR.exe @0040a4f0>
undefined4 * FUN_0040a4f0(void);
// <LegoRR.exe @0040a510>
undefined FUN_0040a510(int param_1, uint param_2);
// <LegoRR.exe @0040a670>
undefined FUN_0040a670(undefined4 param_1, ResourceData * * param_2, int param_3);
// <LegoRR.exe @0040a940>
undefined FUN_0040a940(float param_1);
// <LegoRR.exe @0040a970>
undefined FUN_0040a970(undefined4 * param_1, float param_2);
// <LegoRR.exe @0040aa10>
BOOL FUN_0040aa10(LiveObject * liveObj);
// <LegoRR.exe @0040aa40>
undefined FUN_0040aa40(int param_1);
// <LegoRR.exe @0040aa60>
void FUN_0040aa60(void);
// <LegoRR.exe @0040aaa0>
undefined Main_Load_Dependencies(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @0040add0>
BOOL FUN_0040add0(ObjectType objType, int objIndex, int objLevel);
// <LegoRR.exe @0040ae70>
undefined4 FUN_0040ae70(int * param_1, int * param_2);
// <LegoRR.exe @0040aec0>
undefined FUN_0040aec0(int param_1, int param_2, int param_3, undefined4 * param_4, undefined4 * param_5);
// <LegoRR.exe @0040af30>
undefined FUN_0040af30(ObjectType objType, int objIndex, int objLevel, int param_4);
// <LegoRR.exe @0040b0e0>
void Main_Init_MiscObjectDependencies(void);
// <LegoRR.exe @0040b180>
uint FUN_0040b180(int param_1, int param_2, int param_3);
// <LegoRR.exe @0040b1d0>
void Object_SetDependencyLevelFlag_100(ObjectType objType, int objIndex, int objLevel);
// <LegoRR.exe @0040b210>
uint Object_GetDependencyLevelFlag_100(ObjectType objType, int objIndex, int objLevel);
// <LegoRR.exe @0040b240>
SurfaceTextureGrid * Level_LoadTextureBaseName(char * textureBaseName, uint width, uint height);
// <LegoRR.exe @0040b340>
undefined FUN_0040b340(uint * param_1);
// <LegoRR.exe @0040b3a0>
float10 FUN_0040b3a0(int param_1, int param_2, float * param_3, int param_4);
// <LegoRR.exe @0040b520>
ProMeshData * FUN_0040b520(ResourceData * resData, char * meshName_a, char * meshName_b, float blockSize, SurfaceTextureGrid * surfTextGrid);
// <LegoRR.exe @0040b700>
undefined FUN_0040b700(void * this, int * * param_1);
// <LegoRR.exe @0040b740>
undefined FUN_0040b740(void * this, int param_1);
// <LegoRR.exe @0040b780>
undefined4 FUN_0040b780(int * param_1, uint param_2);
// <LegoRR.exe @0040b7b0>
undefined FUN_0040b7b0(int param_1, int param_2, uint param_3, uint param_4, undefined4 param_5, undefined4 param_6);
// <LegoRR.exe @0040b930>
undefined FUN_0040b930(ResourceData * resData, float param_2, float * param_3, float * param_4, float * param_5, undefined4 param_6, undefined4 param_7, undefined * * param_8, byte param_9);
// <LegoRR.exe @0040bac0>
undefined FUN_0040bac0(ResourceData * resData, float param_2, float * param_3, float * param_4, float * param_5);
// <LegoRR.exe @0040bc90>
undefined FUN_0040bc90(float * param_1, float param_2, float param_3, float param_4, float param_5, float param_6);
// <LegoRR.exe @0040bcf0>
void FUN_0040bcf0(void);
// <LegoRR.exe @0040bd10>
undefined FUN_0040bd10(LiveObject * liveObj);
// <LegoRR.exe @0040bd40>
undefined FUN_0040bd40(Vector3F * position);
// <LegoRR.exe @0040bde0>
undefined FUN_0040bde0(LiveObject * liveObj, Vector3F * param_2);
// <LegoRR.exe @0040bea0>
BOOL Game_GetRockFallStyle(char * param_1, uint * out_index);
// <LegoRR.exe @0040bef0>
undefined Game_SetRockFallStyleIndex(int rockFallStyleIndex);
// <LegoRR.exe @0040bf00>
undefined Boot_Load_RockFallStyles(CFGProperty * root, char * keyBasePath, ResourceData * resData);
// <LegoRR.exe @0040c000>
BOOL FUN_0040c000(ResourceData * resData, char * param_2, int param_3, int param_4, undefined4 param_5);
// <LegoRR.exe @0040c0e0>
BOOL FUN_0040c0e0(undefined4 * param_1, char * filename, int index);
// <LegoRR.exe @0040c160>
BOOL FUN_0040c160(int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8);
// <LegoRR.exe @0040c220>
undefined4 FUN_0040c220(int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7);
// <LegoRR.exe @0040c2d0>
int FUN_0040c2d0(float param_1, undefined4 * param_2, undefined4 * param_3);
// <LegoRR.exe @0040c400>
undefined FUN_0040c400(float param_1);
// <LegoRR.exe @0040c450>
undefined FUN_0040c450(float param_1);
// <LegoRR.exe @0040c4a0>
undefined FUN_0040c4a0(int param_1, int param_2, undefined4 * param_3, undefined4 * param_4);
// <LegoRR.exe @0040c4e0>
int * * FUN_0040c4e0(int param_1, uint param_2);
// <LegoRR.exe @0040c5c0>
undefined FUN_0040c5c0(void * param_1);
// <LegoRR.exe @0040c5f0>
void FUN_0040c5f0(void);
// <LegoRR.exe @0040c650>
undefined FUN_0040c650(ResourceData * resRoot, char * filename);
// <LegoRR.exe @0040c680>
undefined FUN_0040c680(LiveObject * liveObj, Point2F * param_2);
// <LegoRR.exe @0040c760>
undefined FUN_0040c760(float param_1);
// <LegoRR.exe @0040c7d0>
undefined * FUN_0040c7d0(undefined4 param_1);
// <LegoRR.exe @0040c850>
BOOL Res_LoadMiscObject(MiscObjectData * miscObjData, ResourceData * resRoot, char * filename);
// <LegoRR.exe @0040c8c0>
void Res_LoadMiscObjects(CFGProperty * root, char * keyRoot, ResourceData * resRoot);
// <LegoRR.exe @0040caa0>
undefined FUN_0040caa0(int * * param_1, float param_2);
// <LegoRR.exe @0040cb70>
undefined FUN_0040cb70(float param_1);
// <LegoRR.exe @0040cc10>
undefined4 FUN_0040cc10(undefined4 param_1, undefined4 * param_2, undefined4 * param_3);
// <LegoRR.exe @0040ccf0>
void ReservedPool<BlockObject>__Init(LevelData * level);
// <LegoRR.exe @0040cd60>
void ReservedPool<BlockObject>__Cleanup(void);
// <LegoRR.exe @0040cdb0>
undefined FUN_0040cdb0(LevelData * level);
// <LegoRR.exe @0040cdd0>
undefined FUN_0040cdd0(int x, int y);
// <LegoRR.exe @0040ce80>
undefined FUN_0040ce80(LiveObject * liveObj);
// <LegoRR.exe @0040ceb0>
BlockObject * ReservedPool<BlockObject>__Next(LiveObject * liveObj, int x, int y);
// <LegoRR.exe @0040cf60>
void ReservedPool<BlockObject>__Alloc(void);
// <LegoRR.exe @0040cfd0>
undefined FUN_0040cfd0(LiveObject * liveObj);
// <LegoRR.exe @0040d030>
void ReservedPool<BlockObject>__Release(BlockObject * block, int x, int y);
// <LegoRR.exe @0040d0a0>
BOOL FUN_0040d0a0(int x, int y);
// <LegoRR.exe @0040d120>
undefined4 FUN_0040d120(int param_1, int param_2);
// <LegoRR.exe @0040d170>
undefined4 FUN_0040d170(int param_1, int param_2);
// <LegoRR.exe @0040d320>
undefined4 FUN_0040d320(undefined4 param_1, int param_2, int param_3, int param_4);
// <LegoRR.exe @0040d380>
undefined FUN_0040d380(undefined4 param_1);
// <LegoRR.exe @0040d3c0>
undefined FUN_0040d3c0(undefined * param_1, undefined4 param_2);
// <LegoRR.exe @0040d420>
undefined4 FUN_0040d420(undefined4 * param_1, uint param_2, uint param_3);
// <LegoRR.exe @0040d510>
undefined4 FUN_0040d510(LiveObject * param_1, float * param_2);
// <LegoRR.exe @0040d780>
undefined FUN_0040d780(uint param_1, uint param_2, int param_3, float param_4);
// <LegoRR.exe @0040db50>
undefined4 FUN_0040db50(uint param_1, uint param_2, uint param_3, uint param_4);
// <LegoRR.exe @0040dcc0>
undefined FUN_0040dcc0(uint param_1, uint param_2, uint param_3, uint param_4, float * param_5);
// <LegoRR.exe @0040dd70>
undefined4 FUN_0040dd70(int * * param_1);
// <LegoRR.exe @0040dff0>
undefined FUN_0040dff0(LiveObject * liveObj, Point2F * param_2, uint param_3, uint param_4);
// <LegoRR.exe @0040e110>
undefined4 FUN_0040e110(undefined4 param_1, int param_2, uint param_3);
// <LegoRR.exe @0040e280>
undefined FUN_0040e280(int param_1, uint param_2, uint param_3, int param_4);
// <LegoRR.exe @0040e390>
uint FUN_0040e390(int param_1, int param_2);
// <LegoRR.exe @0040e3c0>
undefined Main_Load_Encyclopedia(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @0040e630>
undefined FUN_0040e630(undefined4 * param_1);
// <LegoRR.exe @0040e710>
undefined FUN_0040e710(void);
// <LegoRR.exe @0040e720>
undefined FUN_0040e720(float param_1);
// <LegoRR.exe @0040e800>
undefined FUN_0040e800(int param_1);
// <LegoRR.exe @0040e840>
undefined FUN_0040e840(LiveObject * liveObj);
// <LegoRR.exe @0040e860>
undefined Game_SetErodeTimes(float triggerTime, float erodeTime, float lockTime);
// <LegoRR.exe @0040e8c0>
BOOL Game_GetAvailableErosion__0040e8c0(int * out_index);
// <LegoRR.exe @0040e8f0>
float10 FUN_0040e8f0(Point2I * param_1);
// <LegoRR.exe @0040e940>
undefined FUN_0040e940(Point2I * position, int param_2);
// <LegoRR.exe @0040e9e0>
undefined Game_DoErosionUnk__0040e9e0(float param_1);
// <LegoRR.exe @0040ed30>
undefined Game_ErodeUnk__0040ed30(ErodeState * param_1);
// <LegoRR.exe @0040ed80>
undefined FUN_0040ed80(Point2I * position, int param_2);
// <LegoRR.exe @0040eee0>
undefined4 FUN_0040eee0(int * param_1);
// <LegoRR.exe @0040ef30>
undefined4 FUN_0040ef30(int * param_1, int * param_2);
// <LegoRR.exe @0040f010>
uint FUN_0040f010(float time);
// <LegoRR.exe @0040f0c0>
BOOL FUN_0040f0c0(Point2I * position, int param_2);
// <LegoRR.exe @0040f1e0>
BOOL Level_UpdateFallinsUnk1(Point2I * position);
// <LegoRR.exe @0040f260>
undefined FUN_0040f260(Point2I * param_1, undefined4 param_2, int param_3);
// <LegoRR.exe @0040f510>
undefined Game_SetNumberOfLandSlidesTillCaveIn(int numLandSlides);
// <LegoRR.exe @0040f520>
undefined Game_LandSlideDoCavein(Point2I * position, undefined4 param_2);
// <LegoRR.exe @0040f5f0>
FlockSubdata * LiveObject_FlocksAllocSubdata(Vector3F * vector_1, Vector3F * vector_2, float turn, float speed, float tightness, float goalUpdate, ResourceData * resData);
// <LegoRR.exe @0040f6e0>
undefined Lego_UnkRecurseFreeItem__0040f6e0(undefined * param_1);
// <LegoRR.exe @0040f700>
FlockData * LiveObject_FlocksAllocData(Vector3F * vector_1, Vector3F * vector_2, float turn, float speed, float tightness, ResourceData * resData);
// <LegoRR.exe @0040f780>
undefined Lego_UnkRecurseFree__0040f780(undefined4 * param_1);
// <LegoRR.exe @0040f7c0>
undefined Flocks_FUN_0040f7c0(FlockSubdata * flockSubdata, Vector3F * vector);
// <LegoRR.exe @0040f850>
undefined Flocks_FUN_0040f850(FlockSubdata * flockSubdata, Vector3F * ref_vector);
// <LegoRR.exe @0040fa30>
undefined Flocks_FUN_0040fa30(FlockSubdata * flockSubdata);
// <LegoRR.exe @0040fac0>
undefined Flocks_FUN_0040fac0(undefined4 param_1, FlockSubdata * flockSubdata, float * param_3);
// <LegoRR.exe @0040fbf0>
void Vector3_RandomMultiply(Vector3F * out_vector, float x, float y, float z);
// <LegoRR.exe @0040fc30>
void Flocks_FUN_0040fc30(int * param_1, float * param_2, float * param_3);
// <LegoRR.exe @0040fce0>
undefined FUN_0040fce0(int * param_1, undefined4 * param_2);
// <LegoRR.exe @0040fd10>
void Flocks_FUN_0040fd10(FlockSubdata * flockSubdata, undefined4 param_2);
// <LegoRR.exe @0040fd30>
undefined Flocks_FUN_0040fd30(FlockData * flockData, undefined4 param_2);
// <LegoRR.exe @0040fd70>
void LiveObject_FlocksAddSubdata(FlockData * flockData, FlockSubdata * flockSubdata);
// <LegoRR.exe @0040fd90>
undefined4 * Lego_UnkRecurseFreeDoSomething__0040fd90(undefined4 * param_1);
// <LegoRR.exe @0040fdc0>
undefined Flocks_CallbackForAllSubdata(FlockData * flockData, FlocksCallback * callback, void * context);
// <LegoRR.exe @0040fdf0>
float10 Game_RandomFloat_0_1(void);
// <LegoRR.exe @0040fe00>
undefined FUN_0040fe00(undefined4 param_1, int param_2, float * param_3);
// <LegoRR.exe @0040fe80>
void FUN_0040fe80(int param_1, undefined4 param_2);
// <LegoRR.exe @0040fea0>
void Flocks_SetParameters1(FlockData * param_1, float turn, float speed, float tightness);
// <LegoRR.exe @0040fec0>
void Flocks_SetParametersFromGlobals(undefined4 param_1, FlockSubdata * param_2);
// <LegoRR.exe @0040ff10>
undefined FUN_0040ff10(FlockData * flockData, float param_2, float param_3, float param_4, float param_5);
// <LegoRR.exe @0040ff50>
undefined FUN_0040ff50(int * param_1, undefined4 * param_2);
// <LegoRR.exe @0040ff80>
undefined FUN_0040ff80(undefined4 param_1, int param_2, undefined4 * param_3);
// <LegoRR.exe @0040ffa0>
undefined FUN_0040ffa0(int param_1, undefined4 param_2);
// <LegoRR.exe @0040ffc0>
undefined FUN_0040ffc0(undefined4 param_1, undefined4 * param_2, undefined4 * param_3);
// <LegoRR.exe @0040ffe0>
undefined FUN_0040ffe0(int param_1, undefined4 param_2);
// <LegoRR.exe @00410000>
undefined FUN_00410000(undefined4 param_1, float * param_2, float * param_3);
// <LegoRR.exe @00410160>
undefined FUN_00410160(undefined4 param_1, float * param_2, undefined4 * param_3);
// <LegoRR.exe @004101b0>
undefined4 FUN_004101b0(int param_1);
// <LegoRR.exe @004101e0>
char * replaceTextSpaces(char * str);
// <LegoRR.exe @00410250>
void FUN_00410250(undefined4 param_1, undefined4 param_2, undefined4 param_3, byte * param_4, ...);
// <LegoRR.exe @00410300>
void Main_ShowCredits(void);
// <LegoRR.exe @00410320>
void FUN_00410320(void);
// <LegoRR.exe @00410370>
void FUN_00410370(void);
// <LegoRR.exe @00410380>
char * * FUN_00410380(char * param_1);
// <LegoRR.exe @004103c0>
char * * FUN_004103c0(char * param_1);
// <LegoRR.exe @00410450>
char * FUN_00410450(char * param_1);
// <LegoRR.exe @00410490>
char * FUN_00410490(char * param_1);
// <LegoRR.exe @004104d0>
undefined4 * FUN_004104d0(char * param_1);
// <LegoRR.exe @00410520>
undefined4 * FUN_00410520(undefined4 param_1, char * param_2, char * param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8, undefined4 param_9, undefined4 param_10, undefined4 param_11, undefined4 param_12, undefined4 param_13, undefined4 param_14);
// <LegoRR.exe @004105c0>
undefined FUN_004105c0(int * param_1);
// <LegoRR.exe @00410670>
undefined FUN_00410670(int * * param_1, byte * param_2, int param_3, undefined4 * param_4, int param_5, int param_6, int param_7);
// <LegoRR.exe @00410940>
int * FUN_00410940(uint param_1, int param_2, int param_3, int param_4, int param_5);
// <LegoRR.exe @004109d0>
undefined FUN_004109d0(int * param_1, char * param_2);
// <LegoRR.exe @00410a10>
undefined FUN_00410a10(int * param_1);
// <LegoRR.exe @00410a60>
undefined4 Input_GetMousePositionX(void);
// <LegoRR.exe @00410a70>
undefined4 Input_GetMousePositionY(void);
// <LegoRR.exe @00410a80>
undefined4 Input_GetBool_0076bb3c(void);
// <LegoRR.exe @00410a90>
undefined FUN_00410a90(undefined4 param_1, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @00410ac0>
undefined4 * FUN_00410ac0(undefined4 param_1, float param_2, float param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7);
// <LegoRR.exe @00410b20>
undefined4 * FUN_00410b20(undefined4 param_1, int param_2, int param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8, undefined4 param_9, undefined4 param_10, undefined4 param_11, undefined4 param_12, undefined4 param_13, undefined4 param_14);
// <LegoRR.exe @00410ba0>
undefined FUN_00410ba0(undefined4 * param_1);
// <LegoRR.exe @00410c80>
undefined4 * FUN_00410c80(char * param_1, ImageFont * param_2, ImageFont * param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, int param_7, undefined4 param_8, undefined4 param_9);
// <LegoRR.exe @00410d50>
undefined4 * FUN_00410d50(char * param_1, undefined4 param_2, undefined4 param_3, int param_4, int param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8, int param_9, char * param_10, undefined4 param_11);
// <LegoRR.exe @00410e60>
undefined FUN_00410e60(undefined4 * param_1);
// <LegoRR.exe @00410ee0>
uint FUN_00410ee0(int param_1, char * param_2, int param_3);
// <LegoRR.exe @00411030>
int * FUN_00411030(char * param_1, char * param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, char * param_10);
// <LegoRR.exe @00411190>
undefined4 FUN_00411190(int param_1, int param_2);
// <LegoRR.exe @00411210>
undefined4 FUN_00411210(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
// <LegoRR.exe @00411250>
undefined FUN_00411250(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
// <LegoRR.exe @00411290>
int FUN_00411290(int param_1, undefined4 * param_2, int * param_3);
// <LegoRR.exe @00411420>
uint FUN_00411420(int param_1, int param_2);
// <LegoRR.exe @00411460>
BOOL FUN_00411460(int param_1, int param_2, byte * * param_3, byte * * param_4, byte * * param_5, byte * * param_6);
// <LegoRR.exe @004116c0>
undefined4 FUN_004116c0(int param_1, int * param_2);
// <LegoRR.exe @00411770>
undefined4 FUN_00411770(void);
// <LegoRR.exe @004117a0>
undefined4 FUN_004117a0(int param_1, int param_2, int * * param_3);
// <LegoRR.exe @00411900>
BOOL FUN_00411900(int param_1);
// <LegoRR.exe @00411930>
int FUN_00411930(undefined4 param_1, int param_2);
// <LegoRR.exe @00411e30>
undefined4 Input_GetKeyCharacter(int diKey);
// <LegoRR.exe @00411e40>
undefined FUN_00411e40(int param_1, uint param_2, uint param_3, int param_4, uint param_5);
// <LegoRR.exe @004120a0>
int FUN_004120a0(int param_1);
// <LegoRR.exe @004120c0>
BOOL randomBool_1_In_400(void);
// <LegoRR.exe @004120e0>
undefined FUN_004120e0(int param_1);
// <LegoRR.exe @00412380>
undefined FUN_00412380(int param_1, int param_2, undefined4 * param_3, int * param_4, int param_5, int param_6);
// <LegoRR.exe @00412420>
undefined FUN_00412420(int param_1, int param_2, undefined4 param_3, int param_4);
// <LegoRR.exe @00412680>
undefined FUN_00412680(int * param_1, int * param_2, int * param_3);
// <LegoRR.exe @00412900>
undefined FUN_00412900(int * param_1);
// <LegoRR.exe @00412a20>
undefined FUN_00412a20(int param_1, int param_2);
// <LegoRR.exe @00412b30>
int FUN_00412b30(undefined4 param_1, int param_2, BOOL * out_bool);
// <LegoRR.exe @004138a0>
undefined FUN_004138a0(int param_1);
// <LegoRR.exe @00413990>
void FUN_00413990(void);
// <LegoRR.exe @00413a80>
void FUN_00413a80(void);
// <LegoRR.exe @00413ab0>
undefined MenuLoop_FUN_00413ab0(int param_1);
// <LegoRR.exe @00413d50>
undefined Menu_FUN_00413d50(int * param_1, int param_2);
// <LegoRR.exe @00413d90>
MenuItemType Menu_ParseMenuControlType(char * controlName);
// <LegoRR.exe @00413e30>
char * stringReplaceChar(char * text, char origChar, char newChar);
// <LegoRR.exe @00413e60>
int FUN_00413e60(char * * param_1);
// <LegoRR.exe @00413ec0>
char * * FUN_00413ec0(char * param_1, char * * param_2, char * param_3, char * param_4, char * param_5);
// <LegoRR.exe @00413f40>
undefined FUN_00413f40(int param_1, int param_2, int * * param_3);
// <LegoRR.exe @00413fa0>
undefined4 * FUN_00413fa0(uint param_1);
// <LegoRR.exe @00413ff0>
int * Menu_ParseMenu(undefined param_1, char * menuName, void * dst, void * callback, ...);
// <LegoRR.exe @00414bc0>
int FUN_00414bc0(int * param_1, char * param_2);
// <LegoRR.exe @00414c10>
BOOL Config_IsIntrosEnabled(void);
// <LegoRR.exe @00414c60>
undefined FUN_00414c60(int param_1);
// <LegoRR.exe @00414d10>
undefined FUN_00414d10(int param_1);
// <LegoRR.exe @00414d20>
void SFX_UNKCallsMixer2__00414d20(undefined4 param_1);
// <LegoRR.exe @00414d40>
undefined4 FUN_00414d40(void);
// <LegoRR.exe @00414d80>
undefined FUN_00414d80(BOOL param_1);
// <LegoRR.exe @00414db0>
undefined FUN_00414db0(int param_1);
// <LegoRR.exe @00414dd0>
undefined Music_PlayNext_Not(BOOL isMusicOff);
// <LegoRR.exe @00414df0>
undefined FUN_00414df0(BOOL param_1);
// <LegoRR.exe @00414e10>
undefined FUN_00414e10(int param_1);
// <LegoRR.exe @00414e40>
void FUN_00414e40(void);
// <LegoRR.exe @00414e50>
undefined FUN_00414e50(int param_1);
// <LegoRR.exe @00414ec0>
void FrontEnd_UpdateGameSpeedSlider(void);
// <LegoRR.exe @00414f60>
int FrontEnd_CalcGameSpeedSliderLevel(void);
// <LegoRR.exe @00414fe0>
undefined FUN_00414fe0(undefined4 param_1, int param_2);
// <LegoRR.exe @00415080>
void FUN_00415080(void);
// <LegoRR.exe @004150c0>
void FUN_004150c0(void);
// <LegoRR.exe @00415150>
void FUN_00415150(void);
// <LegoRR.exe @004151f0>
undefined FUN_004151f0(int param_1, char * param_2);
// <LegoRR.exe @00415290>
void FrontEnd_UpdateGameSpeedSliderLevel(void);
// <LegoRR.exe @004152a0>
BOOL FUN_004152a0(undefined4 param_1, int param_2);
// <LegoRR.exe @004153e0>
BOOL Game_UnkParseLevelIdentifier_004153e0(CFGProperty * root, uint * param_2, char * propertyName);
// <LegoRR.exe @00415630>
undefined Avi_Play(int * * param_1, BOOL isSkippable);
// <LegoRR.exe @004156f0>
void Boot_PlayIntroImage(char * imageKeyName, BOOL isSkippable, char * timeKeyName);
// <LegoRR.exe @00415840>
undefined Boot_PlayIntroAVI(char * aviKeyName, BOOL isSkippable);
// <LegoRR.exe @004158c0>
undefined Level_DoVideo__004158c0(char * levelName, int param_2);
// <LegoRR.exe @00415940>
void FUN_00415940(undefined4 param_1);
// <LegoRR.exe @00415c20>
void Save_ClearSaveNumber(void);
// <LegoRR.exe @00415c30>
undefined FUN_00415c30(undefined4 param_1, char * param_2, undefined4 * param_3);
// <LegoRR.exe @00416080>
BOOL FUN_00416080(int levelNumber);
// <LegoRR.exe @004160d0>
BOOL FUN_004160d0(int levelNumber);
// <LegoRR.exe @00416120>
undefined Main_LoadMenus(CFGProperty * root);
// <LegoRR.exe @00416840>
void FUN_00416840(void);
// <LegoRR.exe @00416870>
undefined FUN_00416870(BOOL param_1, BOOL param_2);
// <LegoRR.exe @004168f0>
undefined Menu_FUN_004168f0(int menuId);
// <LegoRR.exe @00416bb0>
undefined4 Menu_Open_FUN_00416bb0(int menuId);
// <LegoRR.exe @00416c30>
BOOL Config_IsFrontEndEnabled(void);
// <LegoRR.exe @00416c80>
BOOL Lego_GetIntNotM1__00558020(void);
// <LegoRR.exe @00416c90>
BOOL Lego_GetIntNotM1__00558024(void);
// <LegoRR.exe @00416ca0>
undefined4 FUN_00416ca0(void);
// <LegoRR.exe @00416d00>
undefined4 Lego_GetInt_0055801c(void);
// <LegoRR.exe @00416d10>
BOOL FUN_00416d10(void);
// <LegoRR.exe @00416d20>
BOOL FUN_00416d20(void);
// <LegoRR.exe @00416d30>
undefined4 * FUN_00416d30(void);
// <LegoRR.exe @00416d50>
int FUN_00416d50(int * param_1, char * param_2);
// <LegoRR.exe @00416da0>
void FUN_00416da0(void);
// <LegoRR.exe @00416e00>
undefined FUN_00416e00(int * param_1, byte * param_2, undefined4 param_3);
// <LegoRR.exe @00416e70>
undefined4 FUN_00416e70(int * param_1, byte * param_2);
// <LegoRR.exe @00416ee0>
undefined FUN_00416ee0(int * param_1, byte * param_2, undefined4 param_3);
// <LegoRR.exe @00416f50>
undefined4 FUN_00416f50(int * param_1, byte * param_2);
// <LegoRR.exe @00416fc0>
int * FUN_00416fc0(int * param_1, byte * param_2);
// <LegoRR.exe @004170f0>
BOOL FUN_004170f0(int param_1, undefined * param_2, undefined4 param_3);
// <LegoRR.exe @00417170>
undefined4 FUN_00417170(undefined4 param_1, int * param_2);
// <LegoRR.exe @00417180>
BOOL FUN_00417180(undefined4 param_1, undefined4 * param_2);
// <LegoRR.exe @004171b0>
undefined4 FUN_004171b0(int param_1, undefined4 param_2);
// <LegoRR.exe @00417200>
undefined4 FUN_00417200(int param_1, undefined4 param_2);
// <LegoRR.exe @00417220>
void FUN_00417220(int * struct14_1, int * struct14_2, BOOL param_3);
// <LegoRR.exe @00417310>
undefined FUN_00417310(int * param_1, int param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5);
// <LegoRR.exe @00417360>
undefined FUN_00417360(undefined4 param_1, undefined4 param_2);
// <LegoRR.exe @00417390>
undefined lego_uses_testercall_FUN_00417390(undefined4 param_1, undefined4 param_2, float param_3);
// <LegoRR.exe @00417630>
undefined FUN_00417630(float param_1, undefined4 param_2);
// <LegoRR.exe @00417710>
undefined4 FUN_00417710(int * param_1, int * param_2);
// <LegoRR.exe @004178e0>
undefined FUN_004178e0(int param_1, int param_2, undefined4 param_3, int param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7);
// <LegoRR.exe @004179c0>
BOOL Game_UnkLoadSaveSlot__004179c0(uint saveIndex, undefined4 * param_2, BOOL param_3);
// <LegoRR.exe @00417b00>
BOOL Save_SPrintfFileUnkWrite__00417b00(undefined4 saveNumber, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, uint param_7);
// <LegoRR.exe @00417d20>
undefined FUN_00417d20(uint param_1);
// <LegoRR.exe @00417d80>
undefined * FUN_00417d80(int saveIndex);
// <LegoRR.exe @00417da0>
undefined * FUN_00417da0(void);
// <LegoRR.exe @00417dc0>
int Save_GetSaveNumber(void);
// <LegoRR.exe @00417dd0>
undefined Save_SetSaveNumber(int saveIndex);
// <LegoRR.exe @00417de0>
undefined FUN_00417de0(uint param_1);
// <LegoRR.exe @00417e50>
undefined FUN_00417e50(undefined4 * param_1);
// <LegoRR.exe @00417e70>
BOOL FUN_00417e70(int param_1, undefined4 * param_2);
// <LegoRR.exe @00417ec0>
int FUN_00417ec0(int param_1);
// <LegoRR.exe @00417ef0>
undefined FUN_00417ef0(undefined4 param_1, undefined4 param_2, undefined4 param_3, uint param_4);
// <LegoRR.exe @00417f10>
undefined4 FUN_00417f10(void);
// <LegoRR.exe @00417f20>
undefined FUN_00417f20(undefined4 param_1);
// <LegoRR.exe @00417f30>
undefined FUN_00417f30(undefined4 param_1, undefined4 param_2, undefined4 param_3, uint param_4);
// <LegoRR.exe @00417f70>
undefined FUN_00417f70(undefined4 * param_1);
// <LegoRR.exe @00417ff0>
undefined FUN_00417ff0(undefined4 * param_1);
// <LegoRR.exe @00418040>
undefined FUN_00418040(undefined4 param_1);
// <LegoRR.exe @00418050>
BOOL FUN_00418050(void);
// <LegoRR.exe @004180c0>
undefined Main_Font_SetDefault(undefined4 font);
// <LegoRR.exe @004180d0>
void FUN_004180d0(void);
// <LegoRR.exe @004180e0>
undefined Main_Load_HelpWindow(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @00418380>
undefined Main_Load_HelpWindowInfo_Levels(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @00418520>
undefined Main_Load_HelpWindow_Buttons(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @00418730>
undefined Game_SetPlaceFlagsState_004dd650(BOOL param_1);
// <LegoRR.exe @00418760>
void FUN_00418760(ObjectType objType, int objIndex, int objLevel, BOOL showHelpWindow);
// <LegoRR.exe @00418850>
undefined FUN_00418850(ObjectType objType, int objIndex, int objLevel);
// <LegoRR.exe @00418900>
void FUN_00418900(void);
// <LegoRR.exe @00418930>
void FUN_00418930(void);
// <LegoRR.exe @00418cd0>
BOOL FUN_00418cd0(uint param_1, uint param_2, int param_3, int param_4, int param_5, float param_6);
// <LegoRR.exe @00418eb0>
undefined FUN_00418eb0(int param_1);
// <LegoRR.exe @00418ef0>
BOOL FUN_00418ef0(int param_1, int param_2, int param_3);
// <LegoRR.exe @00418f60>
undefined FUN_00418f60(undefined4 param_1, float param_2);
// <LegoRR.exe @00419030>
void FUN_00419030(void);
// <LegoRR.exe @00419080>
undefined4 FUN_00419080(int param_1);
// <LegoRR.exe @004190d0>
BOOL FUN_004190d0(void);
// <LegoRR.exe @00419120>
uint FUN_00419120(void);
// <LegoRR.exe @00419130>
undefined FUN_00419130(BOOL param_1, BOOL param_2);
// <LegoRR.exe @00419160>
void Main_Init_Info(ImageFont * font);
// <LegoRR.exe @00419310>
BOOL FUN_00419310(char * param_1, int * param_2);
// <LegoRR.exe @00419350>
undefined4 FUN_00419350(int param_1);
// <LegoRR.exe @00419360>
undefined Main_LoadMessageTabs_InfoOverFlow(char * filename);
// <LegoRR.exe @00419380>
undefined FUN_00419380(BOOL param_1);
// <LegoRR.exe @004193a0>
undefined FUN_004193a0(int param_1, int param_2);
// <LegoRR.exe @004193e0>
undefined FUN_004193e0(int param_1, char * param_2);
// <LegoRR.exe @00419420>
undefined FUN_00419420(int param_1, int param_2);
// <LegoRR.exe @00419460>
undefined FUN_00419460(char * param_1, char * * param_2);
// <LegoRR.exe @00419580>
undefined FUN_00419580(int param_1, int param_2);
// <LegoRR.exe @004195b0>
undefined FUN_004195b0(int param_1, undefined4 param_2);
// <LegoRR.exe @004195d0>
BOOL FUN_004195d0(int param_1, undefined * param_2, undefined4 param_3);
// <LegoRR.exe @00419620>
undefined FUN_00419620(int param_1, int param_2);
// <LegoRR.exe @004196b0>
int FUN_004196b0(int param_1, int param_2);
// <LegoRR.exe @004196e0>
int FUN_004196e0(int param_1, int param_2);
// <LegoRR.exe @00419740>
BOOL FUN_00419740(int param_1, int * param_2);
// <LegoRR.exe @00419760>
undefined FUN_00419760(LiveObject * liveObj);
// <LegoRR.exe @004197f0>
BOOL FUN_004197f0(int * param_1, int * * param_2);
// <LegoRR.exe @00419820>
undefined FUN_00419820(undefined4 param_1);
// <LegoRR.exe @004198d0>
BOOL FUN_004198d0(int * param_1, int * param_2);
// <LegoRR.exe @00419920>
BOOL FUN_00419920(int param_1, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @004199b0>
undefined4 * FUN_004199b0(undefined4 * param_1, undefined4 param_2, char * param_3);
// <LegoRR.exe @00419a10>
void Lego_SetFlag4_004ddd48(BOOL state);
// <LegoRR.exe @00419a30>
uint FUN_00419a30(int param_1);
// <LegoRR.exe @00419a50>
int FUN_00419a50(int param_1);
// <LegoRR.exe @00419a80>
float10 FUN_00419a80(void);
// <LegoRR.exe @00419ab0>
undefined Info_FUN_00419ab0(InfoType infoType, char * param_2, LiveObject * param_3, Point2I * param_4);
// <LegoRR.exe @00419cd0>
void FUN_00419cd0(void);
// <LegoRR.exe @00419d10>
undefined FUN_00419d10(uint param_1);
// <LegoRR.exe @00419d90>
void FUN_00419d90(void);
// <LegoRR.exe @00419db0>
undefined FUN_00419db0(uint param_1);
// <LegoRR.exe @00419e40>
void FUN_00419e40(void);
// <LegoRR.exe @00419e60>
undefined FUN_00419e60(float param_1);
// <LegoRR.exe @00419fb0>
undefined FUN_00419fb0(float param_1);
// <LegoRR.exe @0041a0d0>
undefined4 FUN_0041a0d0(int param_1, int param_2, int param_3);
// <LegoRR.exe @0041a180>
void FUN_0041a180(void);
// <LegoRR.exe @0041a1c0>
void FUN_0041a1c0(void);
// <LegoRR.exe @0041a1f0>
undefined FUN_0041a1f0(float param_1);
// <LegoRR.exe @0041a220>
undefined4 FUN_0041a220(void);
// <LegoRR.exe @0041a230>
undefined Main_InitInterfaceMenuItems(uint param_1, uint param_2, ImageFont * font);
// <LegoRR.exe @0041a590>
void Main_InterfaceAddItems(void);
// <LegoRR.exe @0041a700>
void Main_InterfaceAddItem(int itemIndex, int numParams, ...);
// <LegoRR.exe @0041a780>
void Main_CleanupUnkInteraces(void);
// <LegoRR.exe @0041a850>
undefined FUN_0041a850(void);
// <LegoRR.exe @0041a8c0>
void FUN_0041a8c0(void);
// <LegoRR.exe @0041a8f0>
undefined4 FUN_0041a8f0(char * param_1, int * param_2);
// <LegoRR.exe @0041a930>
void Main_InitSubmenuIconTables(void);
// <LegoRR.exe @0041aa30>
undefined Main_LoadInterfaceBuildImages(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @0041acd0>
undefined Main_LoadInterfaceImages(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @0041af00>
undefined Main_LoadInterfaceSurroundImages(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @0041b0e0>
undefined Main_LoadInterfaceBackButton(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @0041b1a0>
undefined Main_LoadInterfaceDependencies_PlusMinus(char * plus, char * minus);
// <LegoRR.exe @0041b200>
undefined FUN_0041b200(int param_1, Point2I * position);
// <LegoRR.exe @0041b230>
undefined FUN_0041b230(int param_1, Point2I * position);
// <LegoRR.exe @0041b2f0>
int FUN_0041b2f0(int param_1);
// <LegoRR.exe @0041b3a0>
undefined4 FUN_0041b3a0(int param_1);
// <LegoRR.exe @0041b3c0>
void FUN_0041b3c0(void);
// <LegoRR.exe @0041b5b0>
BOOL FUN_0041b5b0(int menuIcon, undefined * callback, void * context);
// <LegoRR.exe @0041b730>
undefined4 FUN_0041b730(uint param_1, uint param_2, int param_3, float * param_4);
// <LegoRR.exe @0041b860>
undefined FUN_0041b860(float param_1);
// <LegoRR.exe @0041b8e0>
undefined4 Lego_GetDat_004ded1c(void);
// <LegoRR.exe @0041b8f0>
undefined4 FUN_0041b8f0(undefined4 * param_1);
// <LegoRR.exe @0041b940>
undefined FUN_0041b940(float param_1);
// <LegoRR.exe @0041b9c0>
undefined FUN_0041b9c0(undefined4 param_1);
// <LegoRR.exe @0041b9d0>
uint GameUnk_DoSomethingWithRenameReplace(uint param_1, uint param_2, int param_3, int param_4, int param_5);
// <LegoRR.exe @0041c0f0>
undefined4 FUN_0041c0f0(uint param_1, uint param_2, undefined4 * param_3, undefined4 * param_4, undefined4 * param_5);
// <LegoRR.exe @0041c370>
void Front_DoF2InterfaceKeyAction(void);
// <LegoRR.exe @0041c3a0>
undefined4 Front_DoMenuIconKey_Action(uint menuIcon, ObjectType objType, int objIndex);
// <LegoRR.exe @0041c420>
undefined FUN_0041c420(int param_1, int param_2, int param_3, float * param_4);
// <LegoRR.exe @0041c610>
undefined4 FUN_0041c610(int param_1, int param_2, int param_3, int param_4, int param_5);
// <LegoRR.exe @0041c6e0>
undefined FUN_0041c6e0(uint menuIcon);
// <LegoRR.exe @0041c730>
undefined FUN_0041c730(int param_1, int param_2);
// <LegoRR.exe @0041c820>
BOOL FUN_0041c820(int param_1, BOOL param_2);
// <LegoRR.exe @0041c880>
uint FUN_0041c880(int param_1, int param_2, int param_3);
// <LegoRR.exe @0041c920>
undefined FUN_0041c920(int param_1, int param_2);
// <LegoRR.exe @0041c950>
undefined FUN_0041c950(int param_1, int param_2, int param_3);
// <LegoRR.exe @0041c990>
uint FUN_0041c990(int param_1);
// <LegoRR.exe @0041c9a0>
uint FUN_0041c9a0(int param_1, int param_2);
// <LegoRR.exe @0041c9e0>
undefined4 FUN_0041c9e0(int param_1);
// <LegoRR.exe @0041ca20>
undefined4 FUN_0041ca20(int param_1, int param_2);
// <LegoRR.exe @0041cac0>
undefined4 FUN_0041cac0(undefined4 param_1, int param_2, int param_3);
// <LegoRR.exe @0041cbb0>
undefined FUN_0041cbb0(int param_1, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @0041cc10>
undefined FUN_0041cc10(undefined4 * param_1, uint param_2, uint param_3);
// <LegoRR.exe @0041cc60>
undefined FUN_0041cc60(float * param_1);
// <LegoRR.exe @0041cdd0>
undefined FUN_0041cdd0(int param_1);
// <LegoRR.exe @0041ce50>
undefined FUN_0041ce50(LiveObject * liveObj);
// <LegoRR.exe @0041ceb0>
undefined FUN_0041ceb0(int * param_1);
// <LegoRR.exe @0041cee0>
undefined FUN_0041cee0(Point2I * position);
// <LegoRR.exe @0041cf10>
undefined FUN_0041cf10(Point2I * param_1);
// <LegoRR.exe @0041cf40>
void FUN_0041cf40(LiveObject * liveObj);
// <LegoRR.exe @0041cf70>
BOOL FUN_0041cf70(uint menuIcon);
// <LegoRR.exe @0041dbd0>
BOOL Game_DoAction__0041dbd0(int param_1);
// <LegoRR.exe @0041e680>
void FUN_0041e680(void);
// <LegoRR.exe @0041e6a0>
undefined NERPs_SetIconFlag4__0041e6a0(int param_1, BOOL state);
// <LegoRR.exe @0041e6d0>
undefined NERPs_FlashSubmenuIcon_internal___0041e6d0(ObjectType objType, int objIndex, BOOL state);
// <LegoRR.exe @0041e710>
LiveObject * Game_GetFirstSelectedObject(void);
// <LegoRR.exe @0041e720>
undefined4 FUN_0041e720(int param_1, undefined4 param_2);
// <LegoRR.exe @0041e740>
undefined4 FUN_0041e740(int param_1);
// <LegoRR.exe @0041e750>
undefined4 NERPs_SetSubmenuIconClicked_internal___0041e750(ObjectType objType, int objIndex, BOOL state);
// <LegoRR.exe @0041e790>
undefined4 FUN_0041e790(int param_1, int param_2);
// <LegoRR.exe @0041e7c0>
undefined4 FUN_0041e7c0(undefined4 param_1, int param_2);
// <LegoRR.exe @0041e800>
undefined4 FUN_0041e800(undefined4 param_1);
// <LegoRR.exe @0041e8c0>
undefined4 FUN_0041e8c0(int param_1, int param_2);
// <LegoRR.exe @0041e900>
undefined FUN_0041e900(uint param_1, uint param_2, uint param_3, uint param_4, float param_5);
// <LegoRR.exe @0041e980>
undefined FUN_0041e980_internal(int param_1, Point2I * position);
// <LegoRR.exe @0041e9f0>
undefined FUN_0041e9f0(float param_1);
// <LegoRR.exe @0041eb60>
undefined FUN_0041eb60(int param_1, int param_2);
// <LegoRR.exe @0041ebd0>
undefined FUN_0041ebd0(float param_1, undefined4 param_2);
// <LegoRR.exe @0041ed90>
undefined FUN_0041ed90(void);
// <LegoRR.exe @0041edb0>
undefined4 FUN_0041edb0(uint param_1, uint param_2, float param_3, float param_4, undefined4 * param_5, undefined4 * param_6, undefined4 * param_7);
// <LegoRR.exe @0041f030>
BOOL FUN_0041f030(ObjectType objType, int objIndex);
// <LegoRR.exe @0041f0c0>
BOOL FUN_0041f0c0(LiveObject * param_1, ObjectType * param_2);
// <LegoRR.exe @0041f160>
undefined FUN_0041f160(void);
// <LegoRR.exe @0041f1a0>
undefined FUN_0041f1a0(undefined4 param_1);
// <LegoRR.exe @0041f1e0>
undefined FUN_0041f1e0(void);
// <LegoRR.exe @0041f220>
undefined FUN_0041f220(undefined4 param_1, undefined4 param_2);
// <LegoRR.exe @0041f270>
undefined FUN_0041f270(undefined4 param_1);
// <LegoRR.exe @0041f2f0>
undefined FUN_0041f2f0(undefined4 param_1);
// <LegoRR.exe @0041f330>
undefined FUN_0041f330(undefined4 param_1);
// <LegoRR.exe @0041f350>
undefined4 FUN_0041f350(undefined * param_1, undefined4 param_2);
// <LegoRR.exe @0041f520>
undefined4 FUN_0041f520(int param_1);
// <LegoRR.exe @0041f540>
undefined4 FUN_0041f540(uint * param_1);
// <LegoRR.exe @0041f570>
undefined4 FUN_0041f570(int param_1);
// <LegoRR.exe @0041f5c0>
undefined4 FUN_0041f5c0(int param_1, int param_2);
// <LegoRR.exe @0041f5f0>
undefined4 FUN_0041f5f0(int * param_1);
// <LegoRR.exe @0041f650>
uint FUN_0041f650(uint param_1);
// <LegoRR.exe @0041f670>
undefined4 FUN_0041f670(int * param_1);
// <LegoRR.exe @0041f750>
bool FUN_0041f750(int param_1, int param_2);
// <LegoRR.exe @0041f770>
undefined4 FUN_0041f770(undefined4 * param_1);
// <LegoRR.exe @0041f7a0>
void Level_IncField8c(void);
// <LegoRR.exe @0041f7b0>
void Level_SubtractCrystals(int crystalCount);
// <LegoRR.exe @0041f7d0>
undefined FUN_0041f7d0(int param_1);
// <LegoRR.exe @0041f810>
int Level_GetCrystalCount(BOOL includeDrained);
// <LegoRR.exe @0041f830>
int Level_GetOreCount(BOOL isProcessed);
// <LegoRR.exe @0041f850>
undefined FUN_0041f850(int param_1);
// <LegoRR.exe @0041f870>
undefined Game_SetFlag1_20000(BOOL state);
// <LegoRR.exe @0041f8a0>
BOOL Game_IsNoclipOn(void);
// <LegoRR.exe @0041f8b0>
void FUN_0041f8b0(void);
// <LegoRR.exe @0041f8c0>
void FUN_0041f8c0(void);
// <LegoRR.exe @0041f8d0>
undefined FUN_0041f8d0(BOOL param_1);
// <LegoRR.exe @0041f910>
void Level_SubtractOre(BOOL isProcessed, int oreCount);
// <LegoRR.exe @0041f950>
BOOL Main_InitGameFunctions(LPCSTR gameName);
// <LegoRR.exe @0041f9b0>
undefined FUN_0041f9b0(void);
// <LegoRR.exe @0041fa70>
float10 Game_GetGameSpeed(void);
// <LegoRR.exe @0041fa80>
BOOL Main_loadLegoCFG(void);
// <LegoRR.exe @00422780>
void Main_LoadMiscObjects(CFGProperty * root);
// <LegoRR.exe @00422fb0>
int FUN_00422fb0(void);
// <LegoRR.exe @00422fe0>
float10 Game_GetFloatFPS_e40(void);
// <LegoRR.exe @00422ff0>
undefined Game_RenameInputUnk(float param_1);
// <LegoRR.exe @00423120>
void Input_UpdateTyping(void);
// <LegoRR.exe @00423210>
BOOL Main_GameUpdate(float elapsed);
// <LegoRR.exe @00424490>
undefined Game_ConsumeOxygen(LiveObject * liveObj, float elapsed);
// <LegoRR.exe @00424530>
undefined FUN_00424530(undefined4 param_1, float param_2);
// <LegoRR.exe @00424660>
undefined FUN_00424660(BOOL isFogEnabled, float elapsed);
// <LegoRR.exe @00424700>
undefined4 FUN_00424700(LiveObject * liveObj, int param_2);
// <LegoRR.exe @00424740>
undefined FUN_00424740(undefined4 liveObj);
// <LegoRR.exe @00424760>
undefined FUN_00424760(int param_1);
// <LegoRR.exe @004247e0>
void FUN_004247e0(LiveObject * liveObj, int param_2, float r, float g, float b);
// <LegoRR.exe @00424c20>
void Game_Exit(void);
// <LegoRR.exe @00424c30>
void Main_GameCleanup(void);
// <LegoRR.exe @00424fd0>
void Game_Exit(void);
// <LegoRR.exe @00424ff0>
BOOL Game_DoHotkeyChecks(undefined4 param_1, float param_2, BOOL * out_t, BOOL * put_r, BOOL * out_shift);
// <LegoRR.exe @00425a70>
undefined FUN_00425a70(undefined1 param_1);
// <LegoRR.exe @00425a90>
undefined4 FUN_00425a90(LiveObject * liveObj, int * param_2);
// <LegoRR.exe @00425b60>
undefined FUN_00425b60(int param_1, uint param_2);
// <LegoRR.exe @00425c00>
undefined Game_UnkSetGameSpeed_UnkBool(undefined4 param_1);
// <LegoRR.exe @00425c10>
void Game_SetGameSpeed(float newGameSpeed);
// <LegoRR.exe @00425c80>
undefined FUN_00425c80(LiveObject * liveObj);
// <LegoRR.exe @00425cb0>
BOOL Game_IsNotBool308__00425cb0(void);
// <LegoRR.exe @00425cc0>
undefined FUN_00425cc0(void);
// <LegoRR.exe @004260f0>
void Lego_unkSlug__004260f0(float param_1);
// <LegoRR.exe @00426160>
void Game_GetVector_45c(Vector3F * param_1);
// <LegoRR.exe @00426180>
undefined FUN_00426180(void);
// <LegoRR.exe @00426210>
void Game_SetMenuNextPosition(Point2F * position);
// <LegoRR.exe @00426250>
void Game_SetMenuPreviousPosition(Point2F * position);
// <LegoRR.exe @00426290>
void FUN_00426290(BOOL param_1, BOOL param_2);
// <LegoRR.exe @004262d0>
void FUN_004262d0(BOOL state);
// <LegoRR.exe @004262f0>
void FUN_004262f0(void);
// <LegoRR.exe @00426350>
void FUN_00426350(float param_1);
// <LegoRR.exe @00426450>
undefined Game_unkGameLoop_FUN_00426450(char * param_1, float param_2, undefined4 param_3, undefined4 param_4, int param_5);
// <LegoRR.exe @00427d30>
void Main_Load_ToolTipInfo(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @00427eb0>
undefined Main_LoadUpgradeNames(CFGProperty * root);
// <LegoRR.exe @00427f50>
void LiveObject_ShowToolTip(LiveObject * liveObj);
// <LegoRR.exe @00428260>
undefined FUN_00428260(int * param_1, int param_2, int param_3, int param_4);
// <LegoRR.exe @004286b0>
undefined4 FUN_004286b0(int * param_1);
// <LegoRR.exe @00428730>
undefined FUN_00428730(int param_1);
// <LegoRR.exe @00428810>
undefined Game_unkDebugKeysInput__00428810(int param_1, int param_2, int * * param_3);
// <LegoRR.exe @00429090>
undefined FUN_00429090(Point2I * position);
// <LegoRR.exe @004290d0>
undefined FUN_004290d0(float param_1, undefined4 param_2);
// <LegoRR.exe @004292e0>
undefined FUN_004292e0(undefined4 param_1);
// <LegoRR.exe @004293a0>
undefined FUN_004293a0(uint param_1, float param_2, float * out_x, float * out_y);
// <LegoRR.exe @004294d0>
undefined4 FUN_004294d0(void);
// <LegoRR.exe @004294f0>
BOOL FUN_004294f0(LiveObject * liveObj);
// <LegoRR.exe @00429520>
undefined FUN_00429520(BOOL param_1, LiveObject * liveObj, int param_3);
// <LegoRR.exe @004296d0>
void Music_CDAudio_PlayNextCallback(void);
// <LegoRR.exe @004296e0>
void Music_PlayNext(BOOL isMusicOn);
// <LegoRR.exe @00429740>
void Config_SetSoundEnabled(BOOL isSoundOn);
// <LegoRR.exe @00429780>
int Level_GetEmergeCreature(void);
// <LegoRR.exe @00429790>
float10 Level_GetObjectUpgradeTime(ObjectType objType);
// <LegoRR.exe @004297b0>
float10 Level_GetTrainTime(void);
// <LegoRR.exe @004297c0>
BOOL Main_loadLevelCFG(char * levelName);
// <LegoRR.exe @0042b220>
undefined4 FUN_0042b220(int param_1, int param_2);
// <LegoRR.exe @0042b260>
BOOL FUN_0042b260(LevelData * level, char * meshBaseName);
// <LegoRR.exe @0042b3b0>
undefined FUN_0042b3b0(int param_1);
// <LegoRR.exe @0042b430>
undefined4 FUN_0042b430(void);
// <LegoRR.exe @0042b440>
BOOL Level_LoadMapFiles(LevelData * level, char * surfaceMap, char * predugMap, int predugParam, char * terrainMap, int terrainParam, char * blockPointersMap, undefined4 blockPointersParam, char * cryOreMap, char cryOreParam, char * erodeMap, char * pathMap, int pathParam, char * textureSet, char * emergeMap, char * aiMap, char * fallinMap);
// <LegoRR.exe @0042b780>
undefined FUN_0042b780(LevelSurfaceMap * param_1);
// <LegoRR.exe @0042ba90>
BOOL Main_LoadTextureType(LevelData * level, char * keyTexturePath);
// <LegoRR.exe @0042bc50>
BOOL Level_LoadPredugMap(LevelData * level, char * filename, int modifier);
// <LegoRR.exe @0042be70>
BOOL Level_LoadErodeMap(LevelData * level, char * filename);
// <LegoRR.exe @0042bf90>
BOOL Level_LoadAIMap(LevelData * level, char * filename);
// <LegoRR.exe @0042c050>
BOOL Level_LoadEmergeMap(LevelData * level, char * filename);
// <LegoRR.exe @0042c260>
undefined4 FUN_0042c260(int param_1, int * param_2, undefined4 * param_3);
// <LegoRR.exe @0042c370>
undefined FUN_0042c370(int param_1, float param_2);
// <LegoRR.exe @0042c3b0>
BOOL Level_LoadTerrainMap(LevelData * level, char * filename, int modifier);
// <LegoRR.exe @0042c4e0>
BOOL Level_GetBlockCryOre(Point2I * position, int * out_crystal, int * out_ore, int * out_crystalAlt, int * out_oreAlt);
// <LegoRR.exe @0042c5d0>
BOOL Level_LoadCryOreMap(LevelData * level, char * filename, char modifier);
// <LegoRR.exe @0042c690>
BOOL Level_LoadPathMap(LevelData * level, char * filename, int modifier);
// <LegoRR.exe @0042c900>
BOOL Level_LoadFallinMap(LevelData * level, char * filename);
// <LegoRR.exe @0042caa0>
undefined Game_UpdateFallins(float time);
// <LegoRR.exe @0042cbc0>
BOOL Level_LoadBlockPointersMap(LevelData * level, char * filename, int modifier);
// <LegoRR.exe @0042cc80>
UpgradeData * Game_GetUpgradeData(char * upgradeName);
// <LegoRR.exe @0042ccd0>
BOOL Boot_Load_VehicleTypes(void);
// <LegoRR.exe @0042ce80>
BOOL Boot_Load_MiniFigureTypes(void);
// <LegoRR.exe @0042d030>
BOOL Boot_Load_RockMonsterTypes(void);
// <LegoRR.exe @0042d1e0>
BOOL Boot_Load_BuildingTypes(void);
// <LegoRR.exe @0042d390>
BOOL Boot_Load_UpgradeTypes(void);
// <LegoRR.exe @0042d530>
void Main_Load_ObjectNames(CFGProperty * root);
// <LegoRR.exe @0042d950>
undefined Main_Load_ObjectTheNames(CFGProperty * root);
// <LegoRR.exe @0042dd70>
undefined FUN_0042dd70(LiveObject * liveObj, uint * param_2, BOOL param_3);
// <LegoRR.exe @0042def0>
undefined FUN_0042def0(LiveObject * liveObj);
// <LegoRR.exe @0042df20>
BOOL FUN_0042df20(uint param_1, int * param_2);
// <LegoRR.exe @0042df50>
BOOL Main_loadObjectListCFG(LevelData * level, char * filename);
// <LegoRR.exe @0042e7e0>
BOOL Game_GetObjectByName(char * objName, ObjectType * out_objType, int * out_objIndex, ResourceData * * opt_resData);
// <LegoRR.exe @0042eca0>
undefined4 game_getResourceCount_FUN_0042eca0(int param_1, int param_2, int * param_3);
// <LegoRR.exe @0042ee70>
int FUN_0042ee70(int param_1);
// <LegoRR.exe @0042eef0>
undefined FUN_0042eef0(char * param_1, Size2F * param_2);
// <LegoRR.exe @0042eff0>
undefined4 Game_freeLevel__0042eff0(void);
// <LegoRR.exe @0042f210>
undefined FUN_0042f210(LevelData * level, int * param_2, int * param_3, int param_4);
// <LegoRR.exe @0042f280>
uint FUN_0042f280(int param_1, int param_2, undefined * param_3, int param_4);
// <LegoRR.exe @0042f620>
undefined Level_UpdateBlockSurfaceUnk(LevelData * level, int x, int y);
// <LegoRR.exe @004301e0>
undefined FUN_004301e0(Point2I * param_1);
// <LegoRR.exe @00430250>
undefined FUN_00430250(Point2I * param_1, undefined4 param_2);
// <LegoRR.exe @004303a0>
undefined FUN_004303a0(int param_1, undefined4 param_2, int * param_3, int * param_4);
// <LegoRR.exe @00430460>
BOOL FUN_00430460(LevelData * level, int in_x, int in_y, int param_4);
// <LegoRR.exe @00430d20>
undefined FUN_00430d20(int * param_1);
// <LegoRR.exe @00430e10>
undefined4 FUN_00430e10(int param_1, uint * param_2, int * param_3);
// <LegoRR.exe @00431020>
undefined FUN_00431020(int * * param_1);
// <LegoRR.exe @00431070>
undefined FUN_00431070(int x, int y);
// <LegoRR.exe @00431100>
undefined Res_Unk_RechargeSparkle(LevelData * level, Point2I * position, BOOL param_3);
// <LegoRR.exe @004312e0>
undefined FUN_004312e0(LevelData * level, float param_2);
// <LegoRR.exe @00431380>
undefined FUN_00431380(LevelData * level, Point2I * position, BOOL param_3);
// <LegoRR.exe @004313f0>
void FUN_004313f0(int * * param_1);
// <LegoRR.exe @00431460>
void FUN_00431460(int param_1);
// <LegoRR.exe @00431490>
LevelData * GetLevel(void);
// <LegoRR.exe @004314a0>
LevelSurfaceMap * GetSurfaceMap(void);
// <LegoRR.exe @004314b0>
undefined FUN_004314b0(uint * param_1, uint param_2);
// <LegoRR.exe @004316b0>
undefined FUN_004316b0(uint param_1, uint param_2, int param_3, float param_4);
// <LegoRR.exe @004318e0>
uint FUN_004318e0(int param_1, int param_2);
// <LegoRR.exe @00431910>
uint Map_GetCoordinate(uint in_sharedIndex, int x, int y);
// <LegoRR.exe @00431960>
undefined4 FUN_00431960(uint param_1, uint param_2, int param_3);
// <LegoRR.exe @004319e0>
undefined4 FUN_004319e0(uint param_1, uint param_2);
// <LegoRR.exe @00431a50>
undefined4 FUN_00431a50(int param_1, int param_2, int param_3, int param_4);
// <LegoRR.exe @00431ba0>
undefined4 FUN_00431ba0(int * param_1, int * param_2, int * param_3, int param_4);
// <LegoRR.exe @00431cd0>
undefined4 FUN_00431cd0(LiveObject * in_liveObj, int param_2, int param_3, int param_4, int param_5, BOOL param_6);
// <LegoRR.exe @00432030>
undefined FUN_00432030(int * param_1);
// <LegoRR.exe @004320a0>
uint FUN_004320a0(int * param_1);
// <LegoRR.exe @004320d0>
undefined FUN_004320d0(void);
// <LegoRR.exe @00432130>
undefined FUN_00432130(void);
// <LegoRR.exe @004321a0>
undefined FUN_004321a0(int * param_1);
// <LegoRR.exe @00432200>
uint FUN_00432200(int * param_1);
// <LegoRR.exe @00432230>
undefined FUN_00432230(void);
// <LegoRR.exe @00432290>
undefined FUN_00432290(int * * param_1);
// <LegoRR.exe @004322f0>
undefined FUN_004322f0(int * param_1);
// <LegoRR.exe @00432320>
undefined FUN_00432320(int * * param_1);
// <LegoRR.exe @00432380>
undefined FUN_00432380(int * param_1, int * param_2);
// <LegoRR.exe @004323c0>
undefined FUN_004323c0(int * param_1, int * param_2);
// <LegoRR.exe @00432400>
undefined FUN_00432400(int x, int y, BOOL param_3);
// <LegoRR.exe @00432450>
uint FUN_00432450(int param_1, int param_2);
// <LegoRR.exe @00432480>
undefined4 return_1(undefined4 param_1);
// <LegoRR.exe @00432490>
undefined FUN_00432490(Point2I * position, int param_2);
// <LegoRR.exe @00432500>
undefined FUN_00432500(int * param_1);
// <LegoRR.exe @00432530>
undefined4 FUN_00432530(Point2I * param_1);
// <LegoRR.exe @00432640>
undefined FUN_00432640(int * param_1, int param_2);
// <LegoRR.exe @004326a0>
BOOL FUN_004326a0(LiveObject * liveObj, uint x, uint y, BOOL param_4, BOOL param_5);
// <LegoRR.exe @00432880>
undefined4 FUN_00432880(int param_1, uint param_2, uint param_3);
// <LegoRR.exe @00432900>
undefined4 FUN_00432900(undefined4 param_1, uint param_2, uint param_3);
// <LegoRR.exe @00432950>
BOOL FUN_00432950(LiveObject * liveObj, uint x, uint y);
// <LegoRR.exe @004329d0>
BOOL FUN_004329d0(int x, int y, BOOL param_3);
// <LegoRR.exe @00432a30>
uint FUN_00432a30(uint param_1, uint param_2);
// <LegoRR.exe @00432a80>
BOOL Level_GetBlockFlags1_8(uint x, uint y);
// <LegoRR.exe @00432ac0>
undefined4 FUN_00432ac0(int param_1, int param_2);
// <LegoRR.exe @00432b00>
BOOL Level_GetBlockFlags1_10Not8(uint x, uint y);
// <LegoRR.exe @00432b50>
uint FUN_00432b50(int param_1, int param_2);
// <LegoRR.exe @00432b80>
int Level_GetBlockRubbleLevel_OrFlag200000(Point2I * position);
// <LegoRR.exe @00432bc0>
uint FUN_00432bc0(Point2I * param_1);
// <LegoRR.exe @00432cc0>
BOOL Level_GetBlockFlags1_20(uint x, uint y);
// <LegoRR.exe @00432d00>
uint Level_GetBlockFlags1_8000000(Point2I * position);
// <LegoRR.exe @00432d30>
undefined Level_SetBlockFlags1_8000000(Point2I * position, BOOL state);
// <LegoRR.exe @00432d90>
BOOL Level_GetBlockFlags1_c0(int x, int y);
// <LegoRR.exe @00432dc0>
BOOL Level_IsBlockExposed(Point2I * position);
// <LegoRR.exe @00432df0>
uint Level_IsBlockSolid(Point2I * position);
// <LegoRR.exe @00432e30>
uint Level_IsBlockLava(Point2I * position);
// <LegoRR.exe @00432e70>
BOOL FUN_00432e70(uint x, uint y);
// <LegoRR.exe @00432ec0>
BOOL FUN_00432ec0(uint x, uint y);
// <LegoRR.exe @00432f00>
uint FUN_00432f00(int param_1, int param_2);
// <LegoRR.exe @00432f30>
uint FUN_00432f30(int param_1, int param_2);
// <LegoRR.exe @00432f60>
uint FUN_00432f60(int * param_1);
// <LegoRR.exe @00432f90>
uint FUN_00432f90(int * param_1);
// <LegoRR.exe @00432fc0>
BOOL Level_IsBlockPowerPath(Point2I * position);
// <LegoRR.exe @00433010>
BOOL Level_GetBlockFlags1_180000(Point2I * position);
// <LegoRR.exe @00433050>
undefined FUN_00433050(int * param_1, int param_2);
// <LegoRR.exe @004330b0>
BOOL FUN_004330b0(LiveObject * liveObj, int x, int y, float param_4, float * optout_value);
// <LegoRR.exe @004331f0>
uint FUN_004331f0(int param_1, int param_2);
// <LegoRR.exe @00433220>
undefined FUN_00433220(uint param_1, uint param_2);
// <LegoRR.exe @00433260>
undefined4 FUN_00433260(uint param_1, uint param_2, uint * param_3);
// <LegoRR.exe @004332b0>
undefined FUN_004332b0(LevelData * level, uint x, uint y);
// <LegoRR.exe @004333f0>
undefined Map_GetDimensions(uint sharedIndex, int * out_width, int * out_height);
// <LegoRR.exe @00433420>
BOOL Main_Load_GraphicsSettings(void);
// <LegoRR.exe @004336a0>
BOOL Main_LoadLighting(void);
// <LegoRR.exe @00433b10>
undefined FUN_00433b10(float param_1, float param_2, int * param_3, int * param_4);
// <LegoRR.exe @00433b40>
BOOL FUN_00433b40(int * param_1, float param_2, int param_3);
// <LegoRR.exe @00433d60>
BOOL FUN_00433d60(int x, int y);
// <LegoRR.exe @00433db0>
undefined FUN_00433db0(ResourceData * resData, uint * param_2, uint param_3, float param_4, float param_5, float param_6, undefined4 param_7, float param_8, int param_9, float param_10, float param_11, float param_12, float param_13, float param_14, float param_15, float param_16, float param_17, int param_18, float param_19, float param_20, float param_21, int param_22, uint param_23, undefined4 param_24, float param_25, undefined4 param_26, float param_27, float param_28, float param_29, float param_30, float param_31);
// <LegoRR.exe @00434380>
BOOL FUN_00434380(int param_1, int param_2);
// <LegoRR.exe @004343b0>
BOOL FUN_004343b0(LevelData * level, uint param_2, uint param_3, undefined4 param_4, uint param_5);
// <LegoRR.exe @00434460>
undefined FUN_00434460(void);
// <LegoRR.exe @004344a0>
BOOL Level_GetBlockUnkField14Test(int x, int y, float param_3, float param_4);
// <LegoRR.exe @00434520>
undefined Main_LoadPanels(CFGProperty * root, uint screenWidth, uint screenHeight);
// <LegoRR.exe @00434640>
void Main_LoadButtons(CFGProperty * root, int screenWidth, uint screenHeight);
// <LegoRR.exe @00434930>
undefined Main_LoadTutorialIcon(CFGProperty * root);
// <LegoRR.exe @00434980>
undefined Boot_Load_Samples(CFGProperty * root, BOOL noReduceSamples);
// <LegoRR.exe @00434a20>
undefined Main_LoadTextMessages(CFGProperty * root);
// <LegoRR.exe @00434b40>
undefined Main_LoadInfoMessages(CFGProperty * root);
// <LegoRR.exe @00434cd0>
undefined Main_LoadToolTips(CFGProperty * root);
// <LegoRR.exe @00434db0>
undefined4 Game_TryPlaceObject(ObjectType objType, int objIndex);
// <LegoRR.exe @00434f40>
undefined FUN_00434f40(int * param_1, int param_2);
// <LegoRR.exe @00434fd0>
undefined Main_LoadSurfaceTypeDescriptions_sound(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @004350a0>
char * FUN_004350a0(int param_1);
// <LegoRR.exe @004350c0>
undefined4 FUN_004350c0(int param_1);
// <LegoRR.exe @004350d0>
undefined FUN_004350d0(int param_1);
// <LegoRR.exe @00435160>
undefined FUN_00435160(Point2I * param_1, int param_2, int param_3);
// <LegoRR.exe @00435230>
undefined FUN_00435230(LevelData * level, int param_2, undefined4 param_3, float param_4);
// <LegoRR.exe @00435480>
undefined4 FUN_00435480(void);
// <LegoRR.exe @004354b0>
undefined4 FUN_004354b0(void);
// <LegoRR.exe @004354f0>
undefined4 FUN_004354f0(byte * param_1, byte * param_2, byte * param_3, byte * param_4);
// <LegoRR.exe @00435870>
BOOL FUN_00435870(void);
// <LegoRR.exe @00435950>
void FUN_00435950(void);
// <LegoRR.exe @00435980>
undefined FUN_00435980(void);
// <LegoRR.exe @004359b0>
undefined FUN_004359b0(int param_1);
// <LegoRR.exe @004359d0>
undefined Game_SetCallToArmsOn(BOOL enableCallToArms);
// <LegoRR.exe @00435a50>
Struct_bc * Lego_AllocStruct_bc__00435a50(ResourceData * resData, int mode);
// <LegoRR.exe @00435cc1>
void Debug_AllowEditModeFunc1(Struct_bc * structbc, BOOL modeDisableUnk);
// <LegoRR.exe @00435cf8>
undefined FUN_00435cf8(int * param_1);
// <LegoRR.exe @00435d3e>
undefined Main_SetCameraMovements(float cameraSpeed, float cameraDropOff, float cameraAcceleration, int mouseScrollIndent);
// <LegoRR.exe @00435d65>
undefined FUN_00435d65(int * param_1, int param_2);
// <LegoRR.exe @00435deb>
undefined FUN_00435deb(int param_1, undefined4 param_2, float param_3, undefined4 param_4, float param_5, float param_6);
// <LegoRR.exe @00435e24>
undefined StructBC_SetObject4_Field14(Struct_bc * param_1, LiveObject * liveObj, undefined4 param_3);
// <LegoRR.exe @00435e3b>
undefined4 FUN_00435e3b(Struct_bc * param_1);
// <LegoRR.exe @00435e46>
undefined FUN_00435e46(int param_1);
// <LegoRR.exe @00435e58>
int Main_GetMouseScrollIndent(void);
// <LegoRR.exe @00435e62>
undefined FUN_00435e62(void * param_1, float param_2, float param_3);
// <LegoRR.exe @00435e8c>
undefined FUN_00435e8c(Struct_bc * param_1, LevelData * level, float param_3, float param_4);
// <LegoRR.exe @00436a53>
undefined FUN_00436a53(Struct_bc * param_1, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @00436a82>
undefined FUN_00436a82(void * param_1, float param_2);
// <LegoRR.exe @00436b22>
undefined FUN_00436b22(void * param_1, float param_2);
// <LegoRR.exe @00436b43>
undefined FUN_00436b43(int param_1, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @00436b75>
undefined FUN_00436b75(void * param_1, float param_2);
// <LegoRR.exe @00436c16>
undefined FUN_00436c16(void * param_1, float param_2);
// <LegoRR.exe @00436c3a>
undefined FUN_00436c3a(Struct_bc * param_1, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @00436c6c>
undefined FUN_00436c6c(void * param_1, float param_2);
// <LegoRR.exe @00436cc7>
undefined FUN_00436cc7(void * param_1, float param_2);
// <LegoRR.exe @00436ceb>
undefined FUN_00436ceb(int param_1, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @00436d0b>
undefined FUN_00436d0b(int * param_1, undefined4 param_2);
// <LegoRR.exe @00436d2d>
undefined FUN_00436d2d(Struct_bc * param_1, float param_2, float param_3);
// <LegoRR.exe @00436d55>
undefined4 FUN_00436d55(int * param_1, uint * param_2, float * param_3);
// <LegoRR.exe @00436d9b>
float10 FUN_00436d9b(int param_1);
// <LegoRR.exe @00436da9>
undefined FUN_00436da9(int param_1, float * param_2, float param_3);
// <LegoRR.exe @00436ee0>
void ReservedPool<LiveObject>__Init(void);
// <LegoRR.exe @00437310>
void ReservedPool<LiveObject>__Cleanup(void);
// <LegoRR.exe @00437370>
undefined FUN_00437370(undefined4 * param_1);
// <LegoRR.exe @00437390>
undefined FUN_00437390(undefined4 * param_1);
// <LegoRR.exe @004373c0>
int FUN_004373c0(int param_1, int param_2);
// <LegoRR.exe @00437410>
undefined Main_LoadToolTipIcons(CFGProperty * root);
// <LegoRR.exe @00437560>
void FUN_00437560(void);
// <LegoRR.exe @004375c0>
undefined FUN_004375c0(LiveObject * in_liveObj, int param_2, float param_3);
// <LegoRR.exe @00437690>
undefined FUN_00437690(uint * param_1, int param_2);
// <LegoRR.exe @00437700>
void FUN_00437700(void);
// <LegoRR.exe @00437720>
int LiveObject_GetOrSubLevelsTable(ObjectType objType, int objIndex, int objLevel, BOOL doSubtract);
// <LegoRR.exe @00437760>
undefined4 LiveObject_GetPreviousLevel(ObjectType objType, int objIndex, int objLevel);
// <LegoRR.exe @00437790>
void Lego_PathLiveLevelsIncrementConditional(BOOL param_1);
// <LegoRR.exe @004377b0>
undefined FUN_004377b0(LiveObject * liveObj);
// <LegoRR.exe @004377d0>
undefined4 FUN_004377d0(LiveObject * liveObj1, LiveObject * liveObj2);
// <LegoRR.exe @00437800>
undefined4 ReservedPool<LiveObject>__Release(LiveObject * liveObj);
// <LegoRR.exe @00437a70>
BOOL FUN_00437a70(LiveObjectPredicate * predicateFunc, LiveObject * liveObj);
// <LegoRR.exe @00437a90>
BOOL FUN_00437a90(LiveObjectPredicate * predicateFunc, void * context, BOOL param_3);
// <LegoRR.exe @00437b40>
void LiveObject_SetCustomName(LiveObject * liveObj, char * customName);
// <LegoRR.exe @00437ba0>
void FUN_00437ba0(void);
// <LegoRR.exe @00437c00>
undefined FUN_00437c00(Point2I * param_1);
// <LegoRR.exe @00437ee0>
undefined FUN_00437ee0(undefined4 param_1, undefined4 param_2, undefined4 param_3, float * param_4, undefined4 param_5, undefined4 param_6, char * param_7, char * param_8);
// <LegoRR.exe @00437f80>
BOOL LiveObject_CanShootObject(LiveObject * liveObj);
// <LegoRR.exe @00437fc0>
LiveObject * LiveObject__Create(int * * srcData, ObjectType objType, int objIndex);
// <LegoRR.exe @00438580>
LiveObject * ReservedPool<LiveObject>__Next(void);
// <LegoRR.exe @004385d0>
void ReservedPool<LiveObject>__Alloc(void);
// <LegoRR.exe @00438650>
int Game_GetNumBuildingsTeleported(int * stack);
// <LegoRR.exe @00438660>
void Game_SetNumBuildingsTeleported(undefined4 numTeleported);
// <LegoRR.exe @00438670>
void LiveObject_SetCrystalPoweredColor(LiveObject * liveObj, BOOL isPowered);
// <LegoRR.exe @00438720>
undefined FUN_00438720(LiveObject * liveObj);
// <LegoRR.exe @00438840>
undefined LiveObject_SetFlag3_80000000(LiveObject * liveObj, BOOL state);
// <LegoRR.exe @00438870>
BOOL FUN_00438870(LiveObject * liveObj, BOOL state);
// <LegoRR.exe @004388d0>
LiveObject * Game_CreateLiveResourceObject(ResourceData * resData, ObjectType objType, int objIndex, int objLevel, float x, float y, float theta);
// <LegoRR.exe @00438930>
undefined4 FUN_00438930(undefined4 * param_1);
// <LegoRR.exe @00438970>
BOOL FUN_00438970(LiveObject * liveObj, LiveObject * * param_2);
// <LegoRR.exe @004389e0>
BOOL FUN_004389e0(undefined4 liveObj, int param_2);
// <LegoRR.exe @00438a30>
BOOL LiveObject_GetBuildingUpgradeCost(LiveObject * liveObj, uint * out_oreCost);
// <LegoRR.exe @00438ab0>
undefined FUN_00438ab0(LiveObject * in_liveObj);
// <LegoRR.exe @00438b70>
BOOL FUN_00438b70(LiveObject * liveObj, int objLevel);
// <LegoRR.exe @00438c20>
undefined4 FUN_00438c20(LiveObject * opt_liveObj, BOOL param_2);
// <LegoRR.exe @00438ca0>
undefined4 FUN_00438ca0(LiveObject * liveObj, BOOL param_2);
// <LegoRR.exe @00438d20>
LiveObject * FUN_00438d20(Point2I * position, ObjectType objType, int objIndex, int objLevel);
// <LegoRR.exe @00438da0>
LiveObject * FUN_00438da0(LiveObject * liveObj, Point2I * position, ObjectType objType, int objLevel);
// <LegoRR.exe @00438e40>
undefined4 FUN_00438e40(LiveObject * liveObj, undefined4 param_2);
// <LegoRR.exe @00438eb0>
undefined4 FUN_00438eb0(LiveObject * liveObj);
// <LegoRR.exe @00438f20>
undefined4 FUN_00438f20(LiveObject * liveObj);
// <LegoRR.exe @00438f90>
undefined4 FUN_00438f90(Point2F * point);
// <LegoRR.exe @00438ff0>
undefined4 FUN_00438ff0(Point2F * point);
// <LegoRR.exe @00439050>
undefined4 FUN_00439050(Point2F * point);
// <LegoRR.exe @004390b0>
undefined4 FUN_004390b0(Point2F * point);
// <LegoRR.exe @00439110>
undefined4 FUN_00439110(LiveObject * liveObj, Point2F * param_2, undefined4 param_3);
// <LegoRR.exe @00439190>
BOOL LiveObject_HasTraining(LiveObject * liveObj, TrainedFlags training);
// <LegoRR.exe @00439220>
BOOL LiveObject_IsDocksBuilding_Unk(LiveObject * liveObj);
// <LegoRR.exe @00439270>
BOOL FUN_00439270(LiveObject * liveObj, int * * param_2);
// <LegoRR.exe @004394c0>
BOOL FUN_004394c0(ObjectType objType);
// <LegoRR.exe @00439500>
BOOL FUN_00439500(LiveObject * liveObj1, LiveObject * liveObj2);
// <LegoRR.exe @00439540>
void Level_GenerateCryOreAt(Point2I * position);
// <LegoRR.exe @00439600>
undefined FUN_00439600(uint * param_1, uint param_2);
// <LegoRR.exe @00439630>
void Level_GenerateCrystal(Point2I * position, uint objLevel, Point2F * opt_point, BOOL showInfoMessage);
// <LegoRR.exe @00439770>
void Level_GenerateOre(Point2I * position, uint objLevel, Point2F * opt_point, BOOL showInfoMessage);
// <LegoRR.exe @004398a0>
char * LiveObject_GetName(LiveObject * liveObj);
// <LegoRR.exe @00439980>
char * Object_GetTypeName(ObjectType objType, int objIndex);
// <LegoRR.exe @00439a50>
char * Object_GetTheName(ObjectType objType, int objIndex);
// <LegoRR.exe @00439b20>
char * Object_GetName(ObjectType objType, int objIndex);
// <LegoRR.exe @00439bf0>
void LiveObject_GetTypeIndex(LiveObject * param_1, int * out_objType, int * out_objIndex);
// <LegoRR.exe @00439c10>
void Main_LoadToolNames(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @00439c50>
void FUN_00439c50(void);
// <LegoRR.exe @00439c80>
BOOL FUN_00439c80(LiveObject * liveObj);
// <LegoRR.exe @00439ce0>
BOOL FUN_00439ce0(LiveObject * liveObj1, LiveObject * liveObj2);
// <LegoRR.exe @00439e40>
BOOL FUN_00439e40(LiveObject * liveObj, undefined4 * param_2);
// <LegoRR.exe @00439e90>
BOOL FUN_00439e90(LiveObject * liveObj1, LiveObject * liveObj2, BOOL param_3);
// <LegoRR.exe @00439f40>
void LiveObject_CompleteVehicleUpgrade(LiveObject * liveObj);
// <LegoRR.exe @00439f90>
BOOL LiveObject_SetLevel_thunk(LiveObject * liveObj, int objLevel);
// <LegoRR.exe @00439fb0>
BOOL LiveObject_IsSmallTeleporter(LiveObject * liveObj);
// <LegoRR.exe @00439fd0>
BOOL LiveObject_IsBigTeleporter(LiveObject * liveObj);
// <LegoRR.exe @00439ff0>
BOOL LiveObject_IsWaterTeleporter(LiveObject * liveObj);
// <LegoRR.exe @0043a010>
BOOL FUN_0043a010(LiveObject * liveObj, Point2I * out_position);
// <LegoRR.exe @0043a0d0>
undefined4 FUN_0043a0d0(LiveObject * liveObj, uint * param_2);
// <LegoRR.exe @0043a100>
undefined4 FUN_0043a100(undefined4 * param_1, uint * param_2);
// <LegoRR.exe @0043a130>
undefined FUN_0043a130(LiveObject * in_liveObj, BOOL param_2);
// <LegoRR.exe @0043a3e0>
int FUN_0043a3e0(int * param_1, float * param_2, float * param_3, int param_4, int param_5);
// <LegoRR.exe @0043a5c0>
BOOL FUN_0043a5c0(LiveObject * liveObj1, LiveObject * liveObj2);
// <LegoRR.exe @0043a8b0>
ResourceData * LiveObject_GetDepositNull(LiveObject * liveObj);
// <LegoRR.exe @0043a910>
int FUN_0043a910(LiveObject * liveObj, ObjectType objType, int objIndex, int objLevel);
// <LegoRR.exe @0043aa80>
BOOL LiveObject_CanSpawnCarryableObject(LiveObject * liveObj, ObjectType objType, int objIndex);
// <LegoRR.exe @0043ab10>
undefined FUN_0043ab10(LiveObject * liveObj, LiveObject * liveObj2);
// <LegoRR.exe @0043abb0>
undefined FUN_0043abb0(undefined4 param_1, int param_2);
// <LegoRR.exe @0043abd0>
undefined FUN_0043abd0(undefined4 param_1, int param_2);
// <LegoRR.exe @0043abf0>
undefined FUN_0043abf0(LiveObject * liveObj);
// <LegoRR.exe @0043ac20>
undefined FUN_0043ac20(LiveObject * liveObj);
// <LegoRR.exe @0043aca0>
undefined FUN_0043aca0(LiveObject * liveObj);
// <LegoRR.exe @0043acb0>
undefined FUN_0043acb0(uint * param_1, undefined4 * param_2);
// <LegoRR.exe @0043ad70>
undefined FUN_0043ad70(uint * param_1);
// <LegoRR.exe @0043aeb0>
undefined FUN_0043aeb0(LiveObject * liveObj);
// <LegoRR.exe @0043af50>
undefined4 FUN_0043af50(int * param_1, undefined4 * param_2);
// <LegoRR.exe @0043b010>
uint * FUN_0043b010(undefined4 * param_1, uint param_2);
// <LegoRR.exe @0043b160>
uint * FUN_0043b160(void);
// <LegoRR.exe @0043b1f0>
uint * FUN_0043b1f0(int * * param_1, float param_2, uint param_3, uint param_4, uint param_5);
// <LegoRR.exe @0043b530>
undefined FUN_0043b530(float param_1);
// <LegoRR.exe @0043b5e0>
void FUN_0043b5e0(void);
// <LegoRR.exe @0043b610>
undefined FUN_0043b610(int * param_1);
// <LegoRR.exe @0043b620>
undefined FUN_0043b620(uint param_1, uint param_2, undefined4 * param_3);
// <LegoRR.exe @0043b670>
BOOL FUN_0043b670(LiveObject * liveObj, int * * param_2);
// <LegoRR.exe @0043b980>
undefined FUN_0043b980(undefined4 param_1, float * param_2, float * param_3);
// <LegoRR.exe @0043ba30>
undefined4 FUN_0043ba30(undefined4 * param_1, int * param_2);
// <LegoRR.exe @0043bae0>
undefined FUN_0043bae0(LiveObject * liveObj, int param_2, int param_3);
// <LegoRR.exe @0043bb10>
undefined FUN_0043bb10(LiveObject * liveObj, ResourceData * resData, undefined4 param_3, undefined4 param_4, int param_5);
// <LegoRR.exe @0043bb90>
BOOL FUN_0043bb90(LiveObject * liveObj, LiveObjectInfo * liveInfo);
// <LegoRR.exe @0043bdb0>
BOOL FUN_0043bdb0(LiveObject * liveObj);
// <LegoRR.exe @0043bde0>
undefined FUN_0043bde0(uint * param_1);
// <LegoRR.exe @0043be80>
undefined FUN_0043be80(int * param_1);
// <LegoRR.exe @0043bf00>
undefined FUN_0043bf00(LiveObject * liveObj);
// <LegoRR.exe @0043c4c0>
BOOL FUN_0043c4c0(ObjectType objType1, int objIndex1, ObjectType objType2, int objIndex2);
// <LegoRR.exe @0043c540>
undefined4 FUN_0043c540(LiveObject * liveObj, float * param_2);
// <LegoRR.exe @0043c570>
undefined FUN_0043c570(float param_1, undefined4 param_2);
// <LegoRR.exe @0043c5b0>
undefined4 FUN_0043c5b0(LiveObject * liveObj, int * param_2);
// <LegoRR.exe @0043c6a0>
undefined4 FUN_0043c6a0(int * param_1);
// <LegoRR.exe @0043c700>
uint LiveObject_GetEquippedBeam(LiveObject * liveObj);
// <LegoRR.exe @0043c750>
undefined4 FUN_0043c750(undefined4 param_1, int param_2, int param_3);
// <LegoRR.exe @0043c780>
undefined FUN_0043c780(uint * param_1);
// <LegoRR.exe @0043c7f0>
undefined FUN_0043c7f0(uint * param_1);
// <LegoRR.exe @0043c830>
undefined FUN_0043c830(LiveObject * liveObj);
// <LegoRR.exe @0043c910>
BOOL FUN_0043c910(LiveObject * liveObj);
// <LegoRR.exe @0043c970>
undefined FUN_0043c970(int * param_1, float param_2);
// <LegoRR.exe @0043cad0>
BOOL FUN_0043cad0(LiveObject * param_1, float * param_2);
// <LegoRR.exe @0043f160>
undefined FUN_0043f160(LiveObject * in_liveObj);
// <LegoRR.exe @0043f3c0>
undefined FUN_0043f3c0(undefined4 param_1, int param_2);
// <LegoRR.exe @0043f3f0>
void Res_ResourceDrawCallback(ResourceData * resData, void * lpValue);
// <LegoRR.exe @0043f410>
BOOL LiveObject_QueueTeleport(LiveObject * liveObj, ObjectType objType, int objIndex);
// <LegoRR.exe @0043f450>
undefined FUN_0043f450(LiveObject * in_liveObj);
// <LegoRR.exe @0043f820>
undefined FUN_0043f820(LiveObject * liveObj);
// <LegoRR.exe @0043f840>
BOOL FUN_0043f840(int param_1, LiveObject * param_2);
// <LegoRR.exe @0043f870>
void LiveObject_TrainMiniFigure_instantunk(LiveObject * liveObj, TrainedFlags trainFlags);
// <LegoRR.exe @0043f960>
void FUN_0043f960(LiveObject * liveObj, float param_2, BOOL param_3, float param_4);
// <LegoRR.exe @0043fa90>
undefined FUN_0043fa90(LiveObject * in_liveObj, float param_2);
// <LegoRR.exe @0043fe00>
undefined4 FUN_0043fe00(int * param_1, float param_2, float param_3);
// <LegoRR.exe @0043fee0>
undefined4 FUN_0043fee0(uint * param_1);
// <LegoRR.exe @00440080>
undefined4 FUN_00440080(int * param_1);
// <LegoRR.exe @00440130>
int FUN_00440130(int * param_1, float * param_2);
// <LegoRR.exe @004402b0>
undefined4 FUN_004402b0(int * param_1);
// <LegoRR.exe @004403f0>
undefined FUN_004403f0(int param_1, int * param_2);
// <LegoRR.exe @00440470>
BOOL FUN_00440470(LiveObject * in_liveObj, int param_2);
// <LegoRR.exe @00440690>
undefined4 FUN_00440690(int * param_1, float * param_2);
// <LegoRR.exe @00440a70>
undefined FUN_00440a70(undefined4 * param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4);
// <LegoRR.exe @00440ac0>
undefined4 FUN_00440ac0(LiveObject * param_1, LiveObject * * param_2);
// <LegoRR.exe @00440b80>
undefined FUN_00440b80(undefined4 * param_1, undefined4 * param_2, undefined4 param_3);
// <LegoRR.exe @00440be0>
undefined4 FUN_00440be0(LiveObject * param_1, LiveObject * * param_2);
// <LegoRR.exe @00440ca0>
void LiveObject_SetActivityUnk(LiveObject * liveObj, ActivityType actType, undefined4 actData);
// <LegoRR.exe @00440cd0>
void LiveObject_UpdateCarrying(LiveObject * in_liveObj);
// <LegoRR.exe @00440eb0>
undefined FUN_00440eb0(LiveObject * liveObj, undefined * * param_2);
// <LegoRR.exe @00440ef0>
undefined FUN_00440ef0(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8);
// <LegoRR.exe @00440f30>
BOOL FUN_00440f30(int * param_1, uint param_2, uint param_3, uint param_4, uint param_5, uint * * param_6, uint * * param_7, uint * param_8, undefined * param_9, undefined4 param_10);
// <LegoRR.exe @004413b0>
BOOL FUN_004413b0(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8, undefined4 param_9, undefined4 param_10);
// <LegoRR.exe @004419c0>
BOOL FUN_004419c0(LiveObject * liveObj, uint param_2, float * param_3, float * param_4, float * param_5);
// <LegoRR.exe @00441c00>
undefined LiveObject_UnkDoRouting_FUN_00441c00(LiveObject * in_liveObj, BOOL param_2);
// <LegoRR.exe @00441df0>
undefined FUN_00441df0(LiveObject * liveObj, BOOL param_2, BOOL param_3);
// <LegoRR.exe @00442160>
undefined LiveObject_ReleaseBoulderUnk(LiveObject * liveObj);
// <LegoRR.exe @00442190>
undefined4 FUN_00442190(LiveObject * liveObj, int * param_2, int param_3);
// <LegoRR.exe @00442390>
undefined Game_GetWeaponUnk(LiveObject * liveObj, int weaponType);
// <LegoRR.exe @004424d0>
void FUN_004424d0(LiveObject * liveObj);
// <LegoRR.exe @00442520>
void LiveObject_GetPosition(LiveObject * liveObj, float * out_x, float * out_y);
// <LegoRR.exe @00442560>
undefined FUN_00442560(LiveObject * liveObj, Point2F * out_point);
// <LegoRR.exe @004425c0>
undefined FUN_004425c0(LiveObject * liveObj, undefined4 theta, Vector3F * param_3);
// <LegoRR.exe @00442740>
float10 FUN_00442740(LiveObject * liveObj);
// <LegoRR.exe @004427b0>
BOOL LiveObject_GetBlockCoordinates(LiveObject * liveObj, int * out_x, int * out_y);
// <LegoRR.exe @00442800>
float10 Res_GetSurfaceMapZ_Callback(float x, float y, LevelSurfaceMap * surfMap);
// <LegoRR.exe @00442820>
float10 FUN_00442820(float param_1, float param_2, LevelSurfaceMap * param_3);
// <LegoRR.exe @004428b0>
undefined FUN_004428b0(LiveObject * liveObj, float x, float y);
// <LegoRR.exe @00442b60>
void FUN_00442b60(LiveObject * liveObj, float x, float y, undefined4 theta, BOOL param_5);
// <LegoRR.exe @00442dd0>
int FUN_00442dd0(LiveObject * in_liveObj, float param_2, float * param_3);
// <LegoRR.exe @00443240>
void FUN_00443240(LiveObject * in_liveObj, float param_2);
// <LegoRR.exe @004437d0>
void FUN_004437d0(LiveObject * liveObj);
// <LegoRR.exe @00443930>
BOOL FUN_00443930(LiveObject * liveObj);
// <LegoRR.exe @004439b0>
BOOL FUN_004439b0(LiveObject * liveObj);
// <LegoRR.exe @004439d0>
BOOL FUN_004439d0(LiveObject * liveObj, uint * param_2, undefined4 * param_3, undefined4 param_4);
// <LegoRR.exe @00443ab0>
void FUN_00443ab0(LiveObject * liveObj);
// <LegoRR.exe @00443b00>
BOOL FUN_00443b00(LiveObject * liveObj, Point2I * position, int * param_3);
// <LegoRR.exe @00443b70>
float FUN_00443b70(LiveObject * in_liveObj, float param_2);
// <LegoRR.exe @00444360>
void FUN_00444360(LiveObject * liveObj);
// <LegoRR.exe @004443b0>
void FUN_004443b0(LiveObject * liveObj, float elapsed);
// <LegoRR.exe @00444520>
BOOL FUN_00444520(LiveObject * liveObj);
// <LegoRR.exe @00444720>
void FUN_00444720(LiveObject * in_liveObj, float * param_2);
// <LegoRR.exe @004448e0>
void FUN_004448e0(LiveObject * liveObj);
// <LegoRR.exe @00444940>
BOOL FUN_00444940(LiveObject * liveObj, int param_2, int param_3, int param_4);
// <LegoRR.exe @00445270>
void FUN_00445270(LiveObject * liveObj, Point2F * point);
// <LegoRR.exe @004454a0>
void FUN_004454a0(LiveObject * in_liveObj);
// <LegoRR.exe @00445600>
BOOL FUN_00445600(LiveObject * liveObj1, LiveObject * * param_2);
// <LegoRR.exe @00445860>
BOOL FUN_00445860(LiveObject * liveObj);
// <LegoRR.exe @004459a0>
void FUN_004459a0(LiveObject * liveObj);
// <LegoRR.exe @00445a30>
BOOL FUN_00445a30(LiveObject * liveObj1, LiveObject * liveObj2);
// <LegoRR.exe @00445af0>
BOOL FUN_00445af0(LiveObject * liveObj1, LiveObject * liveObj2);
// <LegoRR.exe @00446030>
undefined4 FUN_00446030(LiveObject * liveObj, undefined4 param_2, undefined4 param_3, undefined4 param_4);
// <LegoRR.exe @004460b0>
BOOL FUN_004460b0(undefined4 * param_1, int * param_2);
// <LegoRR.exe @004463b0>
BOOL FUN_004463b0(int * * param_1, int * * param_2);
// <LegoRR.exe @004468d0>
void FUN_004468d0(LiveObject * in_liveObj, float elapsed, float * param_3, float * out_float_4);
// <LegoRR.exe @00446b80>
undefined4 FUN_00446b80(int param_1, int param_2, int param_3);
// <LegoRR.exe @00446c80>
BOOL FUN_00446c80(LiveObject * liveObj, uint param_2, uint param_3, int param_4, uint * param_5, int param_6);
// <LegoRR.exe @00447100>
undefined4 FUN_00447100(int * param_1, uint param_2, uint param_3, int param_4);
// <LegoRR.exe @004472ed>
undefined4 FUN_004472ed(undefined param_1, undefined param_2, undefined param_3, undefined8 param_4);
// <LegoRR.exe @00447390>
BOOL FUN_00447390(LiveObject * in_liveObj);
// <LegoRR.exe @00447470>
BOOL FUN_00447470(LiveObject * liveObj, uint x, uint y, LiveObject * liveObj2);
// <LegoRR.exe @004474d0>
undefined4 FUN_004474d0(float * param_1, undefined4 * param_2);
// <LegoRR.exe @00447670>
int FUN_00447670(float * param_1, float param_2, float * param_3, undefined4 * param_4);
// <LegoRR.exe @004477b0>
undefined FUN_004477b0(LiveObject * in_liveObj);
// <LegoRR.exe @00447880>
int FUN_00447880(LiveObject * in_liveObj);
// <LegoRR.exe @004479f0>
undefined4 FUN_004479f0(int param_1);
// <LegoRR.exe @00447a40>
undefined FUN_00447a40(LiveObject * liveObj);
// <LegoRR.exe @00447a90>
void FUN_00447a90(LiveObject * liveObj);
// <LegoRR.exe @00447bc0>
undefined FUN_00447bc0(LiveObject * liveObj);
// <LegoRR.exe @00447be0>
undefined4 FUN_00447be0(int * param_1, int param_2);
// <LegoRR.exe @00447c10>
undefined FUN_00447c10(LiveObject * liveObj, float * param_2, int param_3);
// <LegoRR.exe @00447dc0>
undefined FUN_00447dc0(uint * param_1);
// <LegoRR.exe @00447df0>
float10 FUN_00447df0(LiveObject * in_liveObj, float elapsed);
// <LegoRR.exe @00447f00>
uint Game_UpdateSomeAITasks(LiveObject * liveObj);
// <LegoRR.exe @00448160>
undefined FUN_00448160(LiveObject * param_1, float param_2);
// <LegoRR.exe @00448a80>
undefined FUN_00448a80(int * param_1);
// <LegoRR.exe @00448ac0>
undefined4 FUN_00448ac0(int * param_1, uint * param_2);
// <LegoRR.exe @00448b40>
undefined4 FUN_00448b40(int * param_1, float * param_2);
// <LegoRR.exe @00448c60>
undefined4 FUN_00448c60(undefined4 * param_1);
// <LegoRR.exe @00448d20>
undefined4 FUN_00448d20(int * param_1, float * param_2);
// <LegoRR.exe @00448f10>
undefined4 FUN_00448f10(uint * param_1);
// <LegoRR.exe @00448f50>
int FUN_00448f50(int * param_1, float * param_2, int param_3);
// <LegoRR.exe @00449170>
undefined4 FUN_00449170(int * param_1, int * param_2, int param_3);
// <LegoRR.exe @004492d0>
undefined4 FUN_004492d0(int * param_1);
// <LegoRR.exe @00449360>
undefined4 FUN_00449360(int * param_1, int * param_2, int param_3, int param_4);
// <LegoRR.exe @00449500>
undefined4 FUN_00449500(int * param_1, uint * param_2);
// <LegoRR.exe @00449570>
undefined4 FUN_00449570(int * param_1, float * param_2);
// <LegoRR.exe @004496a0>
undefined4 FUN_004496a0(int * param_1);
// <LegoRR.exe @004496f0>
int FUN_004496f0(int * param_1, float * param_2);
// <LegoRR.exe @004497e0>
int FUN_004497e0(int * param_1, undefined4 * param_2);
// <LegoRR.exe @004498d0>
int FUN_004498d0(LiveObject * liveObj, float * param_2);
// <LegoRR.exe @004499c0>
int FUN_004499c0(LiveObject * in_liveObj);
// <LegoRR.exe @00449b40>
BOOL FUN_00449b40(LiveObject * liveObj, uint x, uint y, float param_4);
// <LegoRR.exe @00449c40>
BOOL FUN_00449c40(LiveObject * liveObj, undefined4 param_2, BOOL * out_bool);
// <LegoRR.exe @00449d30>
void FUN_00449d30(LiveObject * liveObj);
// <LegoRR.exe @00449d80>
BOOL FUN_00449d80(LiveObject * liveObj1, LiveObject * liveObj2);
// <LegoRR.exe @00449ec0>
BOOL FUN_00449ec0(void);
// <LegoRR.exe @00449ee0>
void Flocks_CallbackFUN_00449ee0(FlockData * flockData, FlockSubdata * subdata, void * lpContext);
// <LegoRR.exe @00449f90>
void LiveObject_SetResourceFlag80(LiveObject * liveObj, BOOL state);
// <LegoRR.exe @00449fb0>
BOOL FUN_00449fb0(LiveObject * liveObj);
// <LegoRR.exe @0044a210>
void LiveObject_FUN_0044a210(LiveObject * liveObj, BOOL use3rdFrame);
// <LegoRR.exe @0044a2b0>
BOOL FUN_0044a2b0(LiveObject * liveObj);
// <LegoRR.exe @0044a330>
void FUN_0044a330(LiveObject * liveObj, int param_2, undefined4 param_3, Vector3F * param_4);
// <LegoRR.exe @0044a4c0>
ResourceData * LiveObject_GetResource(LiveObject * liveObj);
// <LegoRR.exe @0044a560>
BOOL LiveObject_GetDrillNullPosition(LiveObject * liveObj, float * out_x, float * out_y);
// <LegoRR.exe @0044a5d0>
undefined FUN_0044a5d0(int * param_1, int param_2, int param_3, float param_4);
// <LegoRR.exe @0044a650>
undefined Level_RegisterRechargeSeam(Point2I * position);
// <LegoRR.exe @0044a690>
undefined4 FUN_0044a690(undefined4 * param_1, undefined4 * param_2);
// <LegoRR.exe @0044a770>
undefined Level_RegisterSlimySlugHole(Point2I * position);
// <LegoRR.exe @0044a7b0>
undefined4 FUN_0044a7b0(undefined4 * param_1, undefined4 * param_2);
// <LegoRR.exe @0044a890>
BOOL FUN_0044a890(LiveObject * liveObj, int * param_2, int * param_3, BOOL param_4, BOOL param_5, BOOL param_6);
// <LegoRR.exe @0044aa60>
BOOL FUN_0044aa60(int param_1, int param_2);
// <LegoRR.exe @0044aa90>
PolyMeshData * Res_LoadPolyMesh(CFGProperty * aeRoot, char * rootName, undefined4 dirname, PolyMode polyMode, uint numCameraFrames);
// <LegoRR.exe @0044abd0>
BOOL FUN_0044abd0(ObjectType objType, int objIndex, BOOL param_3, BOOL param_4, Point2F * param_5, uint x, uint y, BOOL param_8, int * * param_9);
// <LegoRR.exe @0044af80>
undefined Main_LoadObjTtSFXs(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @0044b040>
int LiveObject_GetObjTtSFX(LiveObject * liveObj);
// <LegoRR.exe @0044b080>
void FUN_0044b080(BOOL state);
// <LegoRR.exe @0044b0a0>
undefined FUN_0044b0a0(LiveObject * liveObj);
// <LegoRR.exe @0044b110>
undefined FUN_0044b110(LiveObject * in_liveObj, int param_2, int param_3);
// <LegoRR.exe @0044b250>
undefined FUN_0044b250(int * param_1);
// <LegoRR.exe @0044b270>
undefined FUN_0044b270(LiveObject * in_liveObj);
// <LegoRR.exe @0044b400>
undefined FUN_0044b400(uint x, uint y, uint param_3);
// <LegoRR.exe @0044b510>
undefined FUN_0044b510(LiveObject * liveObj1, LiveObject * liveObj2);
// <LegoRR.exe @0044b610>
BOOL Tool_IsBeamWeapon(ToolType toolIndex);
// <LegoRR.exe @0044b630>
void MiniFigure_EquipTool(LiveObject * liveObj, ToolType toolType);
// <LegoRR.exe @0044b740>
BOOL LiveObject_HasToolEquipped(LiveObject * liveObj, ToolType toolType);
// <LegoRR.exe @0044b780>
undefined4 FUN_0044b780(int * param_1, int param_2);
// <LegoRR.exe @0044b7c0>
int FUN_0044b7c0(int * param_1, float * param_2);
// <LegoRR.exe @0044b940>
void LiveObject_FlocksInit(LiveObject * in_liveObj);
// <LegoRR.exe @0044ba60>
void FlocksMatrix_FUN_0044ba60(int * * param_1, float * matrix, float scalar);
// <LegoRR.exe @0044bb10>
undefined FUN_0044bb10(undefined4 param_1, int param_2, float * param_3);
// <LegoRR.exe @0044bd70>
void Flocks_ReleaseResourceCallback(FlockData * flockData, FlockSubdata * subdata, void * lpContext);
// <LegoRR.exe @0044bda0>
undefined Flocks_ReleaseData(FlockData * flockData);
// <LegoRR.exe @0044bdf0>
undefined FUN_0044bdf0(LiveObject * liveObj, BOOL param_2);
// <LegoRR.exe @0044bef0>
undefined FUN_0044bef0(LiveObject * liveObj, float param_2);
// <LegoRR.exe @0044c0f0>
undefined FUN_0044c0f0(LiveObject * liveObj);
// <LegoRR.exe @0044c1c0>
undefined FUN_0044c1c0(undefined4 * param_1);
// <LegoRR.exe @0044c290>
undefined4 FUN_0044c290(uint * param_1);
// <LegoRR.exe @0044c2f0>
undefined4 FUN_0044c2f0(int * param_1, float param_2);
// <LegoRR.exe @0044c3d0>
undefined FUN_0044c3d0(int param_1);
// <LegoRR.exe @0044c410>
undefined4 FUN_0044c410(int * * param_1, int * * param_2, int * param_3);
// <LegoRR.exe @0044c470>
undefined FUN_0044c470(int * param_1, float param_2);
// <LegoRR.exe @0044c760>
undefined FUN_0044c760(LiveObject * liveObj);
// <LegoRR.exe @0044c7c0>
undefined4 FUN_0044c7c0(LiveObject * liveObj);
// <LegoRR.exe @0044c7f0>
undefined4 FUN_0044c7f0(int * param_1);
// <LegoRR.exe @0044c810>
undefined FUN_0044c810(void);
// <LegoRR.exe @0044c8b0>
BOOL FUN_0044c8b0(LiveObject * liveObj, int * param_2);
// <LegoRR.exe @0044c9d0>
void FUN_0044c9d0(ResourceData * resData1, ResourceData * resData2, float vector_x, float vector_y, float vector_z);
// <LegoRR.exe @0044ca50>
undefined FUN_0044ca50(int param_1);
// <LegoRR.exe @0044ca80>
undefined Main_Load_LightEffects(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @0044cab0>
BOOL Game_loadCFGLightEffectsBlink(CFGProperty * root, char * keyBase);
// <LegoRR.exe @0044cc30>
undefined Game_setLightEffectsBlink(undefined4 red, undefined4 green, undefined4 blue, float maxChange, undefined4 minRange, undefined4 maxRange);
// <LegoRR.exe @0044cc80>
BOOL Game_loadCFGLightEffectsFade(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @0044ced0>
undefined Game_setLightEffectsFade__0044ced0(undefined4 min_red, undefined4 min_green, undefined4 min_blue, undefined4 max_red, undefined4 max_green, undefined4 max_blue, undefined4 time_min, undefined4 time_max, undefined4 fade_min, undefined4 fade_max, undefined4 hold_min, undefined4 hold_max);
// <LegoRR.exe @0044cf60>
BOOL Game_loadCFGLightEffectsMove(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @0044d1b0>
undefined Game_setLightEffectsMove(undefined4 minTime, undefined4 maxTime, undefined4 minSpeed, undefined4 maxSpeed, float minDist, float maxDist, float limit_x, float limit_y, float limit_z);
// <LegoRR.exe @0044d230>
undefined FUN_0044d230(void);
// <LegoRR.exe @0044d260>
undefined FUN_0044d260(float param_1);
// <LegoRR.exe @0044d2b0>
undefined FUN_0044d2b0(void);
// <LegoRR.exe @0044d390>
undefined FUN_0044d390(float param_1);
// <LegoRR.exe @0044d510>
undefined FUN_0044d510(float * param_1);
// <LegoRR.exe @0044d540>
undefined FUN_0044d540(float param_1);
// <LegoRR.exe @0044d9d0>
undefined FUN_0044d9d0(void);
// <LegoRR.exe @0044da20>
undefined FUN_0044da20(float param_1);
// <LegoRR.exe @0044dc60>
undefined4 FUN_0044dc60(float * param_1);
// <LegoRR.exe @0044dce0>
undefined FUN_0044dce0(int param_1);
// <LegoRR.exe @0044dd10>
undefined FUN_0044dd10(float param_1);
// <LegoRR.exe @0044de10>
undefined Main_LoadLoadScreen(char * loadScreen, char * shutdownScreen, ImageFont * font5HI, char * profileFilename, Direction progressDirection, char * progressBar, Rect2F * progressArea, char * loadingText);
// <LegoRR.exe @0044e000>
undefined Log_LoaderProfile(char * filename);
// <LegoRR.exe @0044e0a0>
undefined LoaderProfile_Lookup(char * itemName);
// <LegoRR.exe @0044e180>
void File_funcPtrCallback__0044e180(char * filename, int fileSize, void * lpValue);
// <LegoRR.exe @0044e360>
void Main_ShowShutdownScreen(void);
// <LegoRR.exe @0044e380>
LevelSurfaceMap * Level_CreatureSurfaceMap(ResourceData * in_resData, char * filename, float blockSize, float roughLevel);
// <LegoRR.exe @0044e790>
undefined FUN_0044e790(uint * param_1);
// <LegoRR.exe @0044e930>
undefined FUN_0044e930(void * this, undefined * param_1);
// <LegoRR.exe @0044e970>
undefined FUN_0044e970(LevelSurfaceMap * param_1, uint param_2);
// <LegoRR.exe @0044e990>
undefined Level_FadeInBlock(LevelSurfaceMap * surfaceMap, int * param_2, int * param_3, uint param_4, uint param_5);
// <LegoRR.exe @0044eb20>
undefined FUN_0044eb20(LevelSurfaceMap * surfMap, int x, int y);
// <LegoRR.exe @0044eb40>
undefined FUN_0044eb40(LevelSurfaceMap * param_1);
// <LegoRR.exe @0044eb80>
undefined4 FUN_0044eb80(uint * param_1, uint * param_2, uint param_3, float param_4, float param_5);
// <LegoRR.exe @0044ed90>
undefined FUN_0044ed90(LevelSurfaceMap * param_1, uint * param_2, uint param_3, float param_4);
// <LegoRR.exe @0044f0b0>
undefined FUN_0044f0b0(uint * param_1, uint param_2, uint param_3, int param_4);
// <LegoRR.exe @0044f270>
undefined FUN_0044f270(int param_1, int param_2, int param_3);
// <LegoRR.exe @0044f2b0>
undefined FUN_0044f2b0(uint * param_1, float param_2);
// <LegoRR.exe @0044f350>
undefined FUN_0044f350(int * param_1, float param_2);
// <LegoRR.exe @0044f460>
undefined FUN_0044f460(LevelSurfaceMap * param_1, byte param_2, byte param_3);
// <LegoRR.exe @0044f4e0>
undefined FUN_0044f4e0(LevelSurfaceMap * param_1, undefined4 param_2);
// <LegoRR.exe @0044f4f0>
undefined FUN_0044f4f0(LevelSurfaceMap * param_1, uint param_2, uint param_3, uint param_4, uint param_5);
// <LegoRR.exe @0044f640>
undefined FUN_0044f640(uint * param_1, uint param_2, uint param_3, undefined4 param_4);
// <LegoRR.exe @0044f750>
undefined FUN_0044f750(LevelSurfaceMap * param_1, int param_2);
// <LegoRR.exe @0044f7a0>
uint FUN_0044f7a0(LevelSurfaceMap * surfMap, int x, int y, int index);
// <LegoRR.exe @0044f800>
uint FUN_0044f800(LevelSurfaceMap * surfMap, int x, int y);
// <LegoRR.exe @0044f830>
undefined FUN_0044f830(LevelSurfaceMap * param_1, int param_2, int param_3);
// <LegoRR.exe @0044f880>
undefined FUN_0044f880(int * param_1, int param_2, int param_3, int param_4, float param_5, float param_6, float param_7);
// <LegoRR.exe @0044f900>
BOOL FUN_0044f900(LevelSurfaceMap * surfMap, uint x, uint y, float * out_x, float * out_y);
// <LegoRR.exe @0044f990>
BOOL SurfaceMap_ToBlockCoordinatesNoZ(LevelSurfaceMap * surfaceMap, float in_x, float in_y, int * out_x, int * out_y);
// <LegoRR.exe @0044f9c0>
BOOL SurfaceMap_ToBlockCoordinates(LevelSurfaceMap * surfaceMap, float in_x, float in_y, int * out_x, int * out_y, float * out_unk_z);
// <LegoRR.exe @0044fad0>
undefined FUN_0044fad0(int * param_1, undefined4 param_2, undefined4 param_3, int * param_4, int * param_5);
// <LegoRR.exe @0044fb30>
undefined4 FUN_0044fb30(LevelSurfaceMap * surfaceMap, Point2F * param_2, Point2F * param_3, Point2F * param_4);
// <LegoRR.exe @0044fc00>
float10 SurfaceMap_UnkGetZ(LevelSurfaceMap * surfMap, float x, float y);
// <LegoRR.exe @0044fd70>
undefined FUN_0044fd70(uint * param_1, float param_2, float param_3, undefined4 * param_4);
// <LegoRR.exe @0044fe50>
undefined4 FUN_0044fe50(LevelSurfaceMap * surfMap, float param_2, float param_3, int param_4, float param_5, float * param_6, float * param_7);
// <LegoRR.exe @00450130>
float10 FUN_00450130(int * param_1, float param_2, float param_3);
// <LegoRR.exe @00450320>
undefined FUN_00450320(LevelSurfaceMap * surfMap, int param_2, int param_3, undefined4 * param_4);
// <LegoRR.exe @00450390>
BOOL FUN_00450390(LevelSurfaceMap * surfMap, uint x, uint y, undefined4 * param_4);
// <LegoRR.exe @004504e0>
undefined FUN_004504e0(int * param_1, int param_2, int param_3, undefined4 * param_4);
// <LegoRR.exe @00450580>
uint FUN_00450580(LevelSurfaceMap * param_1, uint x, uint y);
// <LegoRR.exe @004505a0>
BOOL FUN_004505a0(LevelSurfaceMap * surfMap, int param_2, uint param_3, uint param_4, uint * out_x, uint * out_y, float * param_7);
// <LegoRR.exe @00450820>
undefined FUN_00450820(LevelSurfaceMap * surfMap, Vector3F * param_2, Vector3F * param_3, Vector3F * param_4, Point2I * out_coordinates, int unkCount);
// <LegoRR.exe @004508c0>
undefined FUN_004508c0(LevelSurfaceMap * surfMap, int param_2, int param_3, int param_4, undefined * param_5);
// <LegoRR.exe @004509c0>
undefined FUN_004509c0(LevelSurfaceMap * surfMap, int x, int y, BOOL state);
// <LegoRR.exe @004509f0>
undefined FUN_004509f0(int * param_1, int param_2, int param_3);
// <LegoRR.exe @00450a40>
undefined FUN_00450a40(LevelSurfaceMap * surfMap);
// <LegoRR.exe @00450a90>
undefined FUN_00450a90(uint * param_1, uint param_2, uint param_3, float * out_x, float * out_y, float * out_z);
// <LegoRR.exe @00450b50>
float10 SurfaceMap_GetFloat10(LevelSurfaceMap * surfMap);
// <LegoRR.exe @00450b60>
undefined4 FUN_00450b60(int param_1, int param_2, int param_3, int param_4);
// <LegoRR.exe @00450c20>
undefined FUN_00450c20(LevelSurfaceMap * param_1, uint param_2, uint param_3, int param_4);
// <LegoRR.exe @00450d40>
undefined FUN_00450d40(LevelSurfaceMap * surfMap, BOOL param_2);
// <LegoRR.exe @00450e20>
undefined FUN_00450e20(int * param_1, float param_2);
// <LegoRR.exe @004511f0>
undefined FUN_004511f0(uint * param_1, uint param_2, uint param_3);
// <LegoRR.exe @00451440>
undefined4 FUN_00451440(uint * param_1, uint param_2, uint param_3, uint param_4, uint param_5);
// <LegoRR.exe @004514f0>
undefined FUN_004514f0(uint * param_1, uint param_2, uint param_3, uint param_4, undefined4 * param_5);
// <LegoRR.exe @00451590>
undefined4 FUN_00451590(uint * param_1, uint param_2, uint param_3, uint param_4, float * param_5);
// <LegoRR.exe @00451710>
undefined FUN_00451710(uint * param_1, uint param_2, uint param_3, uint param_4, float * param_5);
// <LegoRR.exe @004517b0>
undefined FUN_004517b0(uint * param_1, uint param_2, uint param_3);
// <LegoRR.exe @00451860>
void MapFile_GetDimensions(MapFileInfo * mapFileInfo, int * out_width, int * out_height);
// <LegoRR.exe @00451880>
uint FUN_00451880(int param_1, int param_2, int param_3, int param_4);
// <LegoRR.exe @004518a0>
BOOL FUN_004518a0(LevelSurfaceMap * surfMap, uint x, uint y, Vector3F * param_4, Vector3F * param_5, Vector3F * out_vector);
// <LegoRR.exe @00451c70>
PolyMeshData * Res_CreatePolyMesh(PolyMeshData * lastPolyData, char * partName, char * dirname, char * meshFilename, uint index);
// <LegoRR.exe @00451d70>
PolyMeshData * Res_CreateNullPolyMesh(PolyMeshData * lastPolyData, char * partName, uint index);
// <LegoRR.exe @00451df0>
PolyMeshData * PolyMesh_Duplicate(PolyMeshData * polyData);
// <LegoRR.exe @00451e80>
undefined FUN_00451e80(PolyMeshData * polyData, ResourceData * resData, BOOL param_3, int param_4);
// <LegoRR.exe @00451ef0>
undefined FUN_00451ef0(PolyMeshData * polyData);
// <LegoRR.exe @00451f10>
void PolyMesh_Destroy(PolyMeshData * polyData);
// <LegoRR.exe @00451f90>
void Boot_InitTable_Message(void);
// <LegoRR.exe @00452220>
undefined FUN_00452220(LiveObject * liveObj);
// <LegoRR.exe @00452290>
int Game_LookupPTLEventIndex(char * ptlName);
// <LegoRR.exe @004522d0>
undefined Debug_RegisterSelectedUnitHotkey(byte diKeyCode, undefined4 param_2, undefined4 param_3, undefined4 param_4, Point2I * opt_param_5);
// <LegoRR.exe @00452320>
undefined Level_AddMessageAction(MessageType msgType, undefined4 liveObj, BOOL param_3, undefined4 * param_4);
// <LegoRR.exe @00452390>
void Game_PTL_UNKInit__00452390(void);
// <LegoRR.exe @004526f0>
undefined FUN_004526f0(undefined4 param_1);
// <LegoRR.exe @00452770>
undefined FUN_00452770(LiveObject * liveObj);
// <LegoRR.exe @004527e0>
BOOL FUN_004527e0(undefined4 * param_1, uint * param_2);
// <LegoRR.exe @00452840>
LiveObject * Game_GetSelectedUnits(int * out_count);
// <LegoRR.exe @00452870>
BOOL Game_IsAnyUnitsSelected(void);
// <LegoRR.exe @00452880>
LiveObject * Game_GetPrimarySelectedObject(void);
// <LegoRR.exe @004528a0>
LiveObject * * Game_GetSelectedUnits(void);
// <LegoRR.exe @004528b0>
uint Game_GetNumSelectedUnits(void);
// <LegoRR.exe @004528c0>
void Game_CleanupSelectedUnitsCount(void);
// <LegoRR.exe @004528d0>
BOOL FUN_004528d0(LiveObject * liveObj, uint * out_index);
// <LegoRR.exe @00452910>
BOOL LiveObject_FindIndexOfInTable(LiveObject * * objsTable, uint objsCount, LiveObject * thisObj, uint * out_index);
// <LegoRR.exe @00452950>
BOOL FUN_00452950(LiveObject * liveObj);
// <LegoRR.exe @00452980>
BOOL FUN_00452980(LiveObject * liveObj, int param_2);
// <LegoRR.exe @004529a0>
BOOL FUN_004529a0(LiveObject * liveObj, int param_2, int param_3);
// <LegoRR.exe @00452b30>
BOOL FUN_00452b30(LiveObject * liveObj);
// <LegoRR.exe @00452b80>
void FUN_00452b80(void);
// <LegoRR.exe @00452ea0>
void Game_UnselectAllUnits(void);
// <LegoRR.exe @00452f10>
BOOL FUN_00452f10(LiveObject * liveObj);
// <LegoRR.exe @00452f80>
int FUN_00452f80(void);
// <LegoRR.exe @00453020>
BOOL FUN_00453020(int param_1);
// <LegoRR.exe @004530b0>
BOOL Level_LoadNERPsFile(char * filename);
// <LegoRR.exe @00453130>
BOOL Level_LoadNERPMessageFile(char * filename);
// <LegoRR.exe @004534c0>
undefined4 FUN_004534c0(uint param_1);
// <LegoRR.exe @004534e0>
undefined4 FUN_004534e0(void);
// <LegoRR.exe @004535a0>
undefined NERPs_UnkReserveStack__004535a0(uint * param_1);
// <LegoRR.exe @004535e0>
undefined NERPs_Exec__004535e0(float param_1);
// <LegoRR.exe @00453b60>
int NERPFunc__SetGameSpeed(int * stack);
// <LegoRR.exe @00453bc0>
undefined Lego_SetDatTo_004a773c___00453bc0(undefined4 param_1);
// <LegoRR.exe @00453bd0>
undefined FUN_00453bd0(void);
// <LegoRR.exe @00453be0>
void FUN_00453be0(void);
// <LegoRR.exe @00453cb0>
int NERPFunc__GetMessagesAreUpToDate(int * stack);
// <LegoRR.exe @00453cd0>
int NERPFunc__SupressArrow(int * stack);
// <LegoRR.exe @00453d10>
int NERPFunc__AdvanceMessage(int * stack);
// <LegoRR.exe @00453d30>
int NERPFunc__AllowCameraMovement(int * stack);
// <LegoRR.exe @00453d50>
int NERPFunc__ClickOnlyObjects(int * stack);
// <LegoRR.exe @00453d80>
int NERPFunc__ClickOnlyMap(int * stack);
// <LegoRR.exe @00453db0>
int NERPFunc__ClickOnlyIcon(int * stack);
// <LegoRR.exe @00453de0>
int NERPFunc__ClickOnlyCalltoarms(int * stack);
// <LegoRR.exe @00453e10>
int NERPFunc__DisallowAll(int * stack);
// <LegoRR.exe @00453e40>
int NERPFunc__FlashCallToArmsIcon(int * stack);
// <LegoRR.exe @00453e70>
undefined FUN_00453e70(float param_1);
// <LegoRR.exe @00453f60>
int NERPFunc__GetTimer0(int * stack);
// <LegoRR.exe @00453f70>
int NERPFunc__GetTimer1(int * stack);
// <LegoRR.exe @00453f80>
int NERPFunc__GetTimer2(int * stack);
// <LegoRR.exe @00453f90>
int NERPFunc__GetTimer3(int * stack);
// <LegoRR.exe @00453fa0>
int NERPFunc__SetTimer0(int * stack);
// <LegoRR.exe @00453fd0>
int NERPFunc__SetTimer1(int * stack);
// <LegoRR.exe @00454000>
int NERPFunc__SetTimer2(int * stack);
// <LegoRR.exe @00454030>
int NERPFunc__SetTimer3(int * stack);
// <LegoRR.exe @00454060>
undefined FUN_00454060(float param_1);
// <LegoRR.exe @004542a0>
int NERPFunc__CameraLockOnMonster(int * stack);
// <LegoRR.exe @004542e0>
undefined4 FUN_004542e0(int * param_1, int * * param_2);
// <LegoRR.exe @00454310>
int NERPFunc__CameraLockOnObject(int * stack);
// <LegoRR.exe @00454330>
int NERPFunc__CameraUnlock(int * stack);
// <LegoRR.exe @00454350>
int NERPFunc__CameraZoomIn(int * stack);
// <LegoRR.exe @004543d0>
int NERPFunc__CameraZoomOut(int * stack);
// <LegoRR.exe @00454440>
int NERPFunc__CameraRotate(int * stack);
// <LegoRR.exe @004544e0>
int NERPFunc__GetSelectedRecordObject(int * stack);
// <LegoRR.exe @00454530>
int NERPFunc__SetCrystalPriority(int * stack);
// <LegoRR.exe @00454550>
int NERPFunc__SetMonsterAttackPowerstation(int * stack);
// <LegoRR.exe @004545c0>
undefined4 FUN_004545c0(undefined4 * param_1, uint * param_2);
// <LegoRR.exe @00454660>
int NERPFunc__SetMonsterAttackNowt(int * stack);
// <LegoRR.exe @004546d0>
undefined FUN_004546d0(char * param_1, undefined4 param_2);
// <LegoRR.exe @00454740>
BOOL FUN_00454740(LiveObject * liveObj, int param_2);
// <LegoRR.exe @00454780>
undefined4 FUN_00454780(undefined4 param_1, int param_2, int param_3, int * param_4);
// <LegoRR.exe @004547f0>
int NERPFunc__GetRecordObjectAtTutorial(int * stack);
// <LegoRR.exe @00454860>
int NERPFunc__GetRecordObjectAmountAtTutorial(int * stack);
// <LegoRR.exe @004548c0>
undefined FUN_004548c0(LevelData * level, int param_2, undefined4 param_3, undefined4 * param_4);
// <LegoRR.exe @004549c0>
int NERPFunc__SetRecordObjectPointer(int * stack);
// <LegoRR.exe @004549d0>
undefined FUN_004549d0(int * param_1);
// <LegoRR.exe @004549e0>
int NERPFunc__GetOxygenLevel(int * stack);
// <LegoRR.exe @00454a60>
int NERPFunc__GenerateSlug(int * stack);
// <LegoRR.exe @00454aa0>
int NERPFunc__SetAttackDefer(int * stack);
// <LegoRR.exe @00454ac0>
int NERPFunc__SetCallToArms(int * stack);
// <LegoRR.exe @00454ae0>
int NERPFunc__GetCallToArmsButtonClicked(int * stack);
// <LegoRR.exe @00454af0>
int NERPFunc__SetRockMonster(int * stack);
// <LegoRR.exe @00454b30>
int NERPFunc__GetRockMonstersDestroyed(int * stack);
// <LegoRR.exe @00454b40>
undefined FUN_00454b40(void);
// <LegoRR.exe @00454b50>
void FUN_00454b50(void);
// <LegoRR.exe @00454b60>
int NERPFunc__GetHiddenObjectsFound(int * stack);
// <LegoRR.exe @00454b70>
int NERPFunc__SetHiddenObjectsFound(int * stack);
// <LegoRR.exe @00454b80>
int NERPFunc__SetUpgradeBuildingIconClicked(int * stack);
// <LegoRR.exe @00454ba0>
int NERPFunc__GetUpgradeBuildingIconClicked(int * stack);
// <LegoRR.exe @00454bc0>
int NERPFunc__FlashUpgradeBuildingIcon(int * stack);
// <LegoRR.exe @00454be0>
int NERPFunc__SetGoBackIconClicked(int * stack);
// <LegoRR.exe @00454c00>
int NERPFunc__GetGoBackIconClicked(int * stack);
// <LegoRR.exe @00454c20>
int NERPFunc__FlashGoBackIcon(int * stack);
// <LegoRR.exe @00454c40>
int NERPFunc__GetRockMonsterRunningAway(int * stack);
// <LegoRR.exe @00454c70>
undefined4 FUN_00454c70(int * param_1, int * param_2);
// <LegoRR.exe @00454d20>
int NERPFunc__SetRockMonsterPainThreshold(int * stack);
// <LegoRR.exe @00454d60>
int NERPFunc__SetRockMonsterHealth(int * stack);
// <LegoRR.exe @00454da0>
int NERPFunc__SetPauseGame(int * stack);
// <LegoRR.exe @00454dc0>
int NERPFunc__GetAnyKeyPressed(int * stack);
// <LegoRR.exe @00454dd0>
int NERPFunc__SetIconPos(int * stack);
// <LegoRR.exe @00454e10>
int NERPFunc__SetIconSpace(int * stack);
// <LegoRR.exe @00454e20>
int NERPFunc__SetIconWidth(int * stack);
// <LegoRR.exe @00454e30>
int NERPFunc__SetLevelCompleted(int * stack);
// <LegoRR.exe @00454e40>
int NERPFunc__SetLevelFail(int * stack);
// <LegoRR.exe @00454e60>
int NERPFunc__SetGameFail(int * stack);
// <LegoRR.exe @00454e70>
int NERPFunc__SetTutorialPointer(int * stack);
// <LegoRR.exe @00454e90>
undefined NERPs_SetSubmenuIconClicked__00454e90(char * itemName, BOOL state);
// <LegoRR.exe @00454ed0>
int NERPs_FlashSubmenuIcon__00454ed0(char * itemName, BOOL state);
// <LegoRR.exe @00454f10>
undefined4 FUN_00454f10(undefined4 param_1, int param_2, int param_3, undefined4 * param_4);
// <LegoRR.exe @00454f40>
int NERPFunc__SetTutorialBlockClicks(int * stack);
// <LegoRR.exe @00454f60>
undefined4 FUN_00454f60(undefined4 param_1, uint param_2, int param_3, int * param_4);
// <LegoRR.exe @00454fd0>
int NERPFunc__SetTutorialCrystals(int * stack);
// <LegoRR.exe @00454ff0>
undefined4 FUN_00454ff0(undefined4 param_1, uint param_2, int param_3, undefined4 * param_4);
// <LegoRR.exe @00455050>
int NERPFunc__SetOreAtIconPositions(int * stack);
// <LegoRR.exe @00455070>
int FUN_00455070(char * param_1);
// <LegoRR.exe @004550d0>
int NERPFunc__GetMiniFigureSelected(int * stack);
// <LegoRR.exe @004550e0>
int NERPFunc__GetSmallTruckSelected(int * stack);
// <LegoRR.exe @00455140>
int NERPFunc__GetSmallDiggerSelected(int * stack);
// <LegoRR.exe @004551a0>
int NERPFunc__GetRapidRiderSelected(int * stack);
// <LegoRR.exe @00455200>
int NERPFunc__GetSmallHelicopterSelected(int * stack);
// <LegoRR.exe @00455260>
int NERPFunc__GetGraniteGrinderSelected(int * stack);
// <LegoRR.exe @004552c0>
int NERPFunc__GetChromeCrusherSelected(int * stack);
// <LegoRR.exe @00455320>
undefined4 FUN_00455320(char * param_1);
// <LegoRR.exe @00455360>
undefined4 FUN_00455360(int * param_1, int * param_2);
// <LegoRR.exe @00455390>
int NERPFunc__AddPoweredCrystals(int * stack);
// <LegoRR.exe @004553c0>
int NERPFunc__AddStoredOre(int * stack);
// <LegoRR.exe @004553f0>
undefined4 FUN_004553f0(undefined4 param_1, int param_2, int param_3, int * param_4);
// <LegoRR.exe @00455420>
int NERPFunc__GetTutorialCrystals(int * stack);
// <LegoRR.exe @00455450>
undefined4 FUN_00455450(undefined4 param_1, int param_2, int param_3, int * param_4);
// <LegoRR.exe @00455480>
int NERPFunc__GetTutorialBlockClicks(int * stack);
// <LegoRR.exe @004554b0>
int Level_GetObjectsOfLevel(char * objName, int in_objLevel);
// <LegoRR.exe @00455580>
undefined4 FUN_00455580(int * param_1, int * param_2);
// <LegoRR.exe @004555c0>
uint Game_GetPilotPreviousLevel(char * objName, int objLevel);
// <LegoRR.exe @00455600>
undefined FUN_00455600(char * param_1);
// <LegoRR.exe @00455630>
undefined4 FUN_00455630(int param_1, int param_2);
// <LegoRR.exe @00455680>
int NERPFunc__GetMiniFigureinGraniteGrinder(int * stack);
// <LegoRR.exe @00455690>
int NERPFunc__GetMiniFigureinChromeCrusher(int * stack);
// <LegoRR.exe @004556a0>
int NERPFunc__GetMiniFigureinSmallDigger(int * stack);
// <LegoRR.exe @004556b0>
int NERPFunc__GetMiniFigureinRapidRider(int * stack);
// <LegoRR.exe @004556c0>
int NERPFunc__GetMiniFigureinSmallTruck(int * stack);
// <LegoRR.exe @004556d0>
int NERPFunc__GetMiniFigureinSmallHelicopter(int * stack);
// <LegoRR.exe @004556e0>
int NERPFunc__SetBarracksLevel(int * stack);
// <LegoRR.exe @00455700>
int NERPFunc__SetDocksLevel(int * stack);
// <LegoRR.exe @00455720>
int NERPFunc__SetGeoDomeLevel(int * stack);
// <LegoRR.exe @00455740>
int NERPFunc__SetPowerstationLevel(int * stack);
// <LegoRR.exe @00455760>
int NERPFunc__SetToolStoreLevel(int * stack);
// <LegoRR.exe @00455780>
int NERPFunc__SetGunstationLevel(int * stack);
// <LegoRR.exe @004557a0>
int NERPFunc__SetTeleportPadLevel(int * stack);
// <LegoRR.exe @004557c0>
int NERPFunc__SetSuperTeleportLevel(int * stack);
// <LegoRR.exe @004557e0>
int NERPFunc__SetUpgradeStationLevel(int * stack);
// <LegoRR.exe @00455800>
int NERPFunc__GetBarracksSelected(int * stack);
// <LegoRR.exe @00455810>
int NERPFunc__GetDocksSelected(int * stack);
// <LegoRR.exe @00455820>
int NERPFunc__GetGeoDomeSelected(int * stack);
// <LegoRR.exe @00455830>
int NERPFunc__GetPowerstationSelected(int * stack);
// <LegoRR.exe @00455840>
int NERPFunc__GetToolStoreSelected(int * stack);
// <LegoRR.exe @00455850>
int NERPFunc__GetGunstationSelected(int * stack);
// <LegoRR.exe @00455860>
int NERPFunc__GetTeleportPadSelected(int * stack);
// <LegoRR.exe @00455870>
int NERPFunc__GetSuperTeleportSelected(int * stack);
// <LegoRR.exe @00455880>
int NERPFunc__GetUpgradeStationSelected(int * stack);
// <LegoRR.exe @00455890>
int NERPFunc__GetPoweredBarracksBuilt(int * stack);
// <LegoRR.exe @004558a0>
int NERPFunc__GetPoweredDocksBuilt(int * stack);
// <LegoRR.exe @004558b0>
int NERPFunc__GetPoweredGeodomeBuilt(int * stack);
// <LegoRR.exe @004558c0>
int NERPFunc__GetPoweredPowerstationsBuilt(int * stack);
// <LegoRR.exe @004558d0>
int NERPFunc__GetPoweredToolStoresBuilt(int * stack);
// <LegoRR.exe @004558e0>
int NERPFunc__GetPoweredGunstationsBuilt(int * stack);
// <LegoRR.exe @004558f0>
int NERPFunc__GetPoweredTeleportsBuilt(int * stack);
// <LegoRR.exe @00455900>
int NERPFunc__GetPoweredVehicleTeleportsBuilt(int * stack);
// <LegoRR.exe @00455910>
int NERPFunc__GetPoweredUpgradeStationsBuilt(int * stack);
// <LegoRR.exe @00455920>
int NERPFunc__GetBarracksBuilt(int * stack);
// <LegoRR.exe @00455930>
int NERPFunc__GetDocksBuilt(int * stack);
// <LegoRR.exe @00455940>
int NERPFunc__GetGeodomeBuilt(int * stack);
// <LegoRR.exe @00455950>
int NERPFunc__GetPowerstationsBuilt(int * stack);
// <LegoRR.exe @00455960>
int NERPFunc__GetToolStoresBuilt(int * stack);
// <LegoRR.exe @00455970>
int NERPFunc__GetGunstationsBuilt(int * stack);
// <LegoRR.exe @00455980>
int NERPFunc__GetTeleportsBuilt(int * stack);
// <LegoRR.exe @00455990>
int NERPFunc__GetVehicleTeleportsBuilt(int * stack);
// <LegoRR.exe @004559a0>
int NERPFunc__GetUpgradeStationsBuilt(int * stack);
// <LegoRR.exe @004559b0>
int NERPFunc__GetLevel1BarracksBuilt(int * stack);
// <LegoRR.exe @004559c0>
int NERPFunc__GetLevel1DocksBuilt(int * stack);
// <LegoRR.exe @004559d0>
int NERPFunc__GetLevel1GeodomeBuilt(int * stack);
// <LegoRR.exe @004559e0>
int NERPFunc__GetLevel1PowerstationsBuilt(int * stack);
// <LegoRR.exe @004559f0>
int NERPFunc__GetLevel1ToolStoresBuilt(int * stack);
// <LegoRR.exe @00455a00>
int NERPFunc__GetLevel1GunstationsBuilt(int * stack);
// <LegoRR.exe @00455a10>
int NERPFunc__GetLevel1TeleportsBuilt(int * stack);
// <LegoRR.exe @00455a20>
int NERPFunc__GetLevel1VehicleTeleportsBuilt(int * stack);
// <LegoRR.exe @00455a30>
int NERPFunc__GetLevel1UpgradeStationsBuilt(int * stack);
// <LegoRR.exe @00455a40>
int NERPFunc__GetLevel2BarracksBuilt(int * stack);
// <LegoRR.exe @00455a50>
int NERPFunc__GetLevel2DocksBuilt(int * stack);
// <LegoRR.exe @00455a60>
int NERPFunc__GetLevel2GeodomeBuilt(int * stack);
// <LegoRR.exe @00455a70>
int NERPFunc__GetLevel2PowerstationsBuilt(int * stack);
// <LegoRR.exe @00455a80>
int NERPFunc__GetLevel2ToolStoresBuilt(int * stack);
// <LegoRR.exe @00455a90>
int NERPFunc__GetLevel2GunstationsBuilt(int * stack);
// <LegoRR.exe @00455aa0>
int NERPFunc__GetLevel2TeleportsBuilt(int * stack);
// <LegoRR.exe @00455ab0>
int NERPFunc__GetLevel2VehicleTeleportsBuilt(int * stack);
// <LegoRR.exe @00455ac0>
int NERPFunc__GetLevel2UpgradeStationsBuilt(int * stack);
// <LegoRR.exe @00455ad0>
int NERPFunc__GetBarracksIconClicked(int * stack);
// <LegoRR.exe @00455ae0>
int NERPFunc__GetGeodomeIconClicked(int * stack);
// <LegoRR.exe @00455af0>
int NERPFunc__GetPowerstationIconClicked(int * stack);
// <LegoRR.exe @00455b00>
int NERPFunc__GetToolStoreIconClicked(int * stack);
// <LegoRR.exe @00455b10>
int NERPFunc__GetGunstationIconClicked(int * stack);
// <LegoRR.exe @00455b20>
int NERPFunc__GetTeleportPadIconClicked(int * stack);
// <LegoRR.exe @00455b30>
int NERPFunc__GetVehicleTransportIconClicked(int * stack);
// <LegoRR.exe @00455b40>
int NERPFunc__GetUpgradeStationIconClicked(int * stack);
// <LegoRR.exe @00455b50>
int NERPFunc__SetBarracksIconClicked(int * stack);
// <LegoRR.exe @00455b70>
int NERPFunc__SetGeodomeIconClicked(int * stack);
// <LegoRR.exe @00455b90>
int NERPFunc__SetPowerstationIconClicked(int * stack);
// <LegoRR.exe @00455bb0>
int NERPFunc__SetToolStoreIconClicked(int * stack);
// <LegoRR.exe @00455bd0>
int NERPFunc__SetGunstationIconClicked(int * stack);
// <LegoRR.exe @00455bf0>
int NERPFunc__SetTeleportPadIconClicked(int * stack);
// <LegoRR.exe @00455c10>
int NERPFunc__SetVehicleTransportIconClicked(int * stack);
// <LegoRR.exe @00455c30>
int NERPFunc__SetUpgradeStationIconClicked(int * stack);
// <LegoRR.exe @00455c50>
int NERPFunc__FlashBarracksIcon(int * stack);
// <LegoRR.exe @00455c70>
int NERPFunc__FlashGeodomeIcon(int * stack);
// <LegoRR.exe @00455c90>
int NERPFunc__FlashPowerStationIcon(int * stack);
// <LegoRR.exe @00455cb0>
int NERPFunc__FlashToolStoreIcon(int * stack);
// <LegoRR.exe @00455cd0>
int NERPFunc__FlashGunstationIcon(int * stack);
// <LegoRR.exe @00455cf0>
int NERPFunc__FlashTeleportPadIcon(int * stack);
// <LegoRR.exe @00455d10>
int NERPFunc__FlashVehicleTransportIcon(int * stack);
// <LegoRR.exe @00455d30>
int NERPFunc__FlashUpgradeStationIcon(int * stack);
// <LegoRR.exe @00455d50>
int NERPFunc__GetPathsBuilt(int * stack);
// <LegoRR.exe @00455d60>
int NERPFunc__GetStudCount(int * stack);
// <LegoRR.exe @00455d70>
int NERPFunc__GetSmallHelicoptersOnLevel(int * stack);
// <LegoRR.exe @00455d80>
int NERPFunc__GetGraniteGrindersOnLevel(int * stack);
// <LegoRR.exe @00455d90>
int NERPFunc__GetRapidRidersOnLevel(int * stack);
// <LegoRR.exe @00455da0>
int NERPFunc__GetSmallDiggersOnLevel(int * stack);
// <LegoRR.exe @00455db0>
int NERPFunc__GetSlugsOnLevel(int * stack);
// <LegoRR.exe @00455dc0>
int NERPFunc__GetMiniFiguresOnLevel(int * stack);
// <LegoRR.exe @00455dd0>
int NERPFunc__GetOreRefineriesBuilt(int * stack);
// <LegoRR.exe @00455de0>
int NERPFunc__GetCrystalRefineriesBuilt(int * stack);
// <LegoRR.exe @00455df0>
int NERPFunc__GetTeleportIconClicked(int * stack);
// <LegoRR.exe @00455e10>
int NERPFunc__GetDynamiteClicked(int * stack);
// <LegoRR.exe @00455e30>
int NERPFunc__GetMountIconClicked(int * stack);
// <LegoRR.exe @00455e50>
int NERPFunc__GetTrainIconClicked(int * stack);
// <LegoRR.exe @00455e70>
int NERPFunc__GetDropSonicBlasterIconClicked(int * stack);
// <LegoRR.exe @00455e90>
int NERPFunc__GetGetToolIconClicked(int * stack);
// <LegoRR.exe @00455eb0>
int NERPFunc__GetGetPusherIconClicked(int * stack);
// <LegoRR.exe @00455ed0>
int NERPFunc__GetGetSonicBlasterIconClicked(int * stack);
// <LegoRR.exe @00455ef0>
int NERPFunc__GetTrainSailorIconClicked(int * stack);
// <LegoRR.exe @00455f10>
int NERPFunc__GetTrainPilotIconClicked(int * stack);
// <LegoRR.exe @00455f30>
int NERPFunc__GetTrainDriverIconClicked(int * stack);
// <LegoRR.exe @00455f50>
int NERPFunc__GetGetLaserIconClicked(int * stack);
// <LegoRR.exe @00455f70>
int NERPFunc__GetDismountIconClicked(int * stack);
// <LegoRR.exe @00455f90>
int NERPFunc__GetDigIconClicked(int * stack);
// <LegoRR.exe @00455fb0>
int NERPFunc__GetBuildIconClicked(int * stack);
// <LegoRR.exe @00455fd0>
int NERPFunc__GetLayPathIconClicked(int * stack);
// <LegoRR.exe @00455ff0>
int NERPFunc__GetPlaceFenceIconClicked(int * stack);
// <LegoRR.exe @00456010>
int NERPFunc__SetTeleportIconClicked(int * stack);
// <LegoRR.exe @00456030>
int NERPFunc__SetDynamiteClicked(int * stack);
// <LegoRR.exe @00456050>
int NERPFunc__SetTrainIconClicked(int * stack);
// <LegoRR.exe @00456070>
int NERPFunc__SetTrainDriverIconClicked(int * stack);
// <LegoRR.exe @00456090>
int NERPFunc__SetTrainSailorIconClicked(int * stack);
// <LegoRR.exe @004560b0>
int NERPFunc__SetGetToolIconClicked(int * stack);
// <LegoRR.exe @004560d0>
int NERPFunc__SetDropSonicBlasterIconClicked(int * stack);
// <LegoRR.exe @004560f0>
int NERPFunc__SetGetLaserIconClicked(int * stack);
// <LegoRR.exe @00456110>
int NERPFunc__SetGetPusherIconClicked(int * stack);
// <LegoRR.exe @00456130>
int NERPFunc__SetGetSonicBlasterIconClicked(int * stack);
// <LegoRR.exe @00456150>
int NERPFunc__SetDismountIconClicked(int * stack);
// <LegoRR.exe @00456170>
int NERPFunc__SetTrainPilotIconClicked(int * stack);
// <LegoRR.exe @00456190>
int NERPFunc__SetMountIconClicked(int * stack);
// <LegoRR.exe @004561b0>
int NERPFunc__SetDigIconClicked(int * stack);
// <LegoRR.exe @004561d0>
int NERPFunc__SetBuildIconClicked(int * stack);
// <LegoRR.exe @004561f0>
int NERPFunc__SetLayPathIconClicked(int * stack);
// <LegoRR.exe @00456210>
int NERPFunc__SetPlaceFenceIconClicked(int * stack);
// <LegoRR.exe @00456230>
int NERPFunc__FlashTeleportIcon(int * stack);
// <LegoRR.exe @00456250>
int NERPFunc__FlashDynamiteIcon(int * stack);
// <LegoRR.exe @00456270>
int NERPFunc__FlashMountIcon(int * stack);
// <LegoRR.exe @00456290>
int NERPFunc__FlashTrainIcon(int * stack);
// <LegoRR.exe @004562b0>
int NERPFunc__FlashTrainDriverIcon(int * stack);
// <LegoRR.exe @004562d0>
int NERPFunc__FlashTrainPilotIcon(int * stack);
// <LegoRR.exe @004562f0>
int NERPFunc__FlashTrainSailorIcon(int * stack);
// <LegoRR.exe @00456310>
int NERPFunc__FlashDismountIcon(int * stack);
// <LegoRR.exe @00456330>
int NERPFunc__FlashGetToolIcon(int * stack);
// <LegoRR.exe @00456350>
int NERPFunc__FlashDropSonicBlasterIcon(int * stack);
// <LegoRR.exe @00456370>
int NERPFunc__FlashGetLaserIcon(int * stack);
// <LegoRR.exe @00456390>
int NERPFunc__FlashGetPusherIcon(int * stack);
// <LegoRR.exe @004563b0>
int NERPFunc__FlashGetSonicBlasterIcon(int * stack);
// <LegoRR.exe @004563d0>
int NERPFunc__FlashDigIcon(int * stack);
// <LegoRR.exe @004563f0>
int NERPFunc__FlashBuildIcon(int * stack);
// <LegoRR.exe @00456410>
int NERPFunc__FlashLayPathIcon(int * stack);
// <LegoRR.exe @00456430>
int NERPFunc__FlashPlaceFenceIcon(int * stack);
// <LegoRR.exe @00456450>
int NERPFunc__GetRandom(int * stack);
// <LegoRR.exe @00456460>
int NERPFunc__GetRandomTrueFalse(int * stack);
// <LegoRR.exe @00456470>
int NERPFunc__GetRandom10(int * stack);
// <LegoRR.exe @00456490>
int NERPFunc__GetRandom100(int * stack);
// <LegoRR.exe @004564b0>
int NERPFunc__GetCrystalsPickedUp(int * stack);
// <LegoRR.exe @004564c0>
int NERPFunc__GetCrystalsCurrentlyStored(int * stack);
// <LegoRR.exe @004564d0>
int NERPFunc__False(int * stack);
// <LegoRR.exe @004564e0>
int NERPFunc__GetOrePickedUp(int * stack);
// <LegoRR.exe @004564f0>
int NERPFunc__GetOreCurrentlyStored(int * stack);
// <LegoRR.exe @00456500>
int NERPFunc__GetTutorialFlags(int * stack);
// <LegoRR.exe @00456510>
int NERPFunc__GetR0(int * stack);
// <LegoRR.exe @00456520>
int NERPFunc__GetR1(int * stack);
// <LegoRR.exe @00456530>
int NERPFunc__GetR2(int * stack);
// <LegoRR.exe @00456540>
int NERPFunc__GetR3(int * stack);
// <LegoRR.exe @00456550>
int NERPFunc__GetR4(int * stack);
// <LegoRR.exe @00456560>
int NERPFunc__GetR5(int * stack);
// <LegoRR.exe @00456570>
int NERPFunc__GetR6(int * stack);
// <LegoRR.exe @00456580>
int NERPFunc__GetR7(int * stack);
// <LegoRR.exe @00456590>
int NERPFunc__AddR0(int * stack);
// <LegoRR.exe @004565b0>
int NERPFunc__AddR1(int * stack);
// <LegoRR.exe @004565d0>
int NERPFunc__AddR2(int * stack);
// <LegoRR.exe @004565f0>
int NERPFunc__AddR3(int * stack);
// <LegoRR.exe @00456610>
int NERPFunc__AddR4(int * stack);
// <LegoRR.exe @00456630>
int NERPFunc__AddR5(int * stack);
// <LegoRR.exe @00456650>
int NERPFunc__AddR6(int * stack);
// <LegoRR.exe @00456670>
int NERPFunc__AddR7(int * stack);
// <LegoRR.exe @00456690>
int NERPFunc__SubR0(int * stack);
// <LegoRR.exe @004566b0>
int NERPFunc__SubR1(int * stack);
// <LegoRR.exe @004566d0>
int NERPFunc__SubR2(int * stack);
// <LegoRR.exe @004566f0>
int NERPFunc__SubR3(int * stack);
// <LegoRR.exe @00456710>
int NERPFunc__SubR4(int * stack);
// <LegoRR.exe @00456730>
int NERPFunc__SubR5(int * stack);
// <LegoRR.exe @00456750>
int NERPFunc__SubR6(int * stack);
// <LegoRR.exe @00456770>
int NERPFunc__SubR7(int * stack);
// <LegoRR.exe @00456790>
int NERPFunc__SetR0(int * stack);
// <LegoRR.exe @004567a0>
int NERPFunc__SetR1(int * stack);
// <LegoRR.exe @004567b0>
int NERPFunc__SetR2(int * stack);
// <LegoRR.exe @004567c0>
int NERPFunc__SetR3(int * stack);
// <LegoRR.exe @004567d0>
int NERPFunc__SetR4(int * stack);
// <LegoRR.exe @004567e0>
int NERPFunc__SetR5(int * stack);
// <LegoRR.exe @004567f0>
int NERPFunc__SetR6(int * stack);
// <LegoRR.exe @00456800>
int NERPFunc__SetR7(int * stack);
// <LegoRR.exe @00456810>
int NERPFunc__SetTutorialFlags(int * stack);
// <LegoRR.exe @00456820>
int NERPFunc__GetTrainFlags(int * stack);
// <LegoRR.exe @00456830>
int NERPFunc__SetTrainFlags(int * stack);
// <LegoRR.exe @00456840>
int NERPFunc__GetMonstersOnLevel(int * stack);
// <LegoRR.exe @00456880>
int NERPFunc__GetBuildingsTeleported(int * stack);
// <LegoRR.exe @00456890>
int NERPFunc__SetBuildingsTeleported(int * stack);
// <LegoRR.exe @004568b0>
int NERPFunc__SetMessagePermit(int * stack);
// <LegoRR.exe @00456900>
BOOL NERPs_IsLoaded(void);
// <LegoRR.exe @00456910>
undefined4 NERPs_GetMessageWait(void);
// <LegoRR.exe @00456920>
int NERPFunc__SetMessageWait(int * stack);
// <LegoRR.exe @00456930>
int NERPFunc__SetMessageTimerValues(int * stack);
// <LegoRR.exe @00456980>
int NERPFunc__GetMessageTimer(int * stack);
// <LegoRR.exe @00456990>
int NERPFunc__SetMessage(int * stack);
// <LegoRR.exe @00456a80>
int NERPFunc__SetObjectiveSwitch(int * stack);
// <LegoRR.exe @00456a90>
int NERPFunc__GetObjectiveSwitch(int * stack);
// <LegoRR.exe @00456ab0>
int NERPFunc__GetObjectiveShowing(int * stack);
// <LegoRR.exe @00456ad0>
void FUN_00456ad0(void);
// <LegoRR.exe @00456af0>
undefined Level_NERPMessage_Parse(char * param_1, undefined4 * param_2, BOOL param_3);
// <LegoRR.exe @00456e40>
undefined Level_InitBlockPointersTable(LevelData * level);
// <LegoRR.exe @00456ef0>
int FUN_00456ef0(int param_1, int param_2);
// <LegoRR.exe @00456f20>
void FUN_00456f20(void);
// <LegoRR.exe @00456f70>
undefined FUN_00456f70(int param_1, undefined * param_2, undefined4 param_3);
// <LegoRR.exe @00456fc0>
BOOL Game_UnkTutorialBlockGet(undefined4 param_1, int x, int y, undefined4 * param_4);
// <LegoRR.exe @00457320>
undefined4 FUN_00457320(int * param_1, int param_2);
// <LegoRR.exe @00457390>
undefined4 FUN_00457390(undefined4 * param_1, int param_2);
// <LegoRR.exe @004573f0>
int NERPFunc__MakeSomeoneOnThisBlockPickUpSomethingOnThisBlock(int * stack);
// <LegoRR.exe @00457430>
undefined FUN_00457430(int param_1, undefined4 * param_2);
// <LegoRR.exe @00457520>
int NERPFunc__SetCongregationAtTutorial(int * stack);
// <LegoRR.exe @00457560>
int NERPFunc__SetRockMonsterAtTutorial(int * stack);
// <LegoRR.exe @004575a0>
int NERPFunc__SetCameraGotoTutorial(int * stack);
// <LegoRR.exe @004575e0>
int NERPFunc__GetCameraAtTutorial(int * stack);
// <LegoRR.exe @00457620>
int NERPFunc__GetTutorialBlockIsGround(int * stack);
// <LegoRR.exe @00457660>
int NERPFunc__GetTutorialBlockIsPath(int * stack);
// <LegoRR.exe @004576a0>
int NERPFunc__SetTutorialBlockIsGround(int * stack);
// <LegoRR.exe @004576e0>
int NERPFunc__SetTutorialBlockIsPath(int * stack);
// <LegoRR.exe @00457720>
int NERPFunc__GetUnitAtBlock(int * stack);
// <LegoRR.exe @00457760>
int NERPFunc__GetMonsterAtTutorial(int * stack);
// <LegoRR.exe @004577a0>
void Level_LoadObjectiveText(CFGProperty * root, undefined4 param_2, char * param_3, LevelData * level, char * filename);
// <LegoRR.exe @00458000>
void Level_LoadObjectiveInfo(CFGProperty * root, char * keyRootPath, char * levelName, LevelData * level, int screenWidth, int screenHeight);
// <LegoRR.exe @00458840>
undefined Level_SetCryOreObjectives(LevelData * level, int crystalObjective, int oreObjective);
// <LegoRR.exe @00458880>
undefined Level_SetBlockObjective(LevelData * level, Point2I * position);
// <LegoRR.exe @004588b0>
undefined Level_SetTimerObjective(LevelData * level, float timerObjective, BOOL hitTimeFailObjective);
// <LegoRR.exe @004588e0>
undefined Level_SetConstructionObjective(LevelData * level, int objType, int objIndex);
// <LegoRR.exe @00458910>
undefined4 FUN_00458910(void);
// <LegoRR.exe @00458920>
undefined Game_SetEndTeleportEnabled(undefined4 endTeleportEnabled);
// <LegoRR.exe @00458930>
undefined Level_SetCompleteStatus(LevelCompleteStatus status);
// <LegoRR.exe @00458ba0>
void FUN_00458ba0(void);
// <LegoRR.exe @00458c60>
BOOL Level_IsObjectiveFinished(void);
// <LegoRR.exe @00458c80>
undefined FUN_00458c80(int param_1, int param_2, uint * param_3);
// <LegoRR.exe @00458ea0>
undefined FUN_00458ea0(Struct_830 * param_1, LevelData * level, float param_3, float param_4);
// <LegoRR.exe @00459310>
BOOL FUN_00459310(int param_1, undefined4 * param_2, float param_3);
// <LegoRR.exe @004593c0>
BOOL FUN_004593c0(int * param_1, int param_2);
// <LegoRR.exe @00459450>
undefined LiveObject_UnkRecallMiniFigureName(LiveObject * liveObj);
// <LegoRR.exe @00459500>
BOOL LiveObject_RecallMiniFigure(LiveObject * liveObj);
// <LegoRR.exe @00459560>
void FUN_00459560(void);
// <LegoRR.exe @004595a0>
void Lego_Unk_SORRFile__004595a0(void);
// <LegoRR.exe @00459620>
BOOL FUN_00459620(void);
// <LegoRR.exe @00459690>
undefined4 Lego_GetDat_00500e64(void);
// <LegoRR.exe @004596a0>
BOOL Lego_Write_SORRFile__004596a0(char * filename);
// <LegoRR.exe @00459730>
BOOL Lego_Read_SORRFile__00459730(char * filename);
// <LegoRR.exe @004597f0>
undefined Main_Load_ObjInfo(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @00459820>
BOOL Main_Load_ObjInfo_HealthBar(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @00459bc0>
BOOL Main_Load_ObjInfo_Hunger(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @00459c80>
undefined FUN_00459c80(int param_1, char * param_2);
// <LegoRR.exe @00459d10>
BOOL Main_Load_ObjInfo_Bubble(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @00459dc0>
undefined FUN_00459dc0(int * param_1, int param_2, int param_3);
// <LegoRR.exe @0045a210>
undefined FUN_0045a210(undefined4 param_1, int param_2, int param_3);
// <LegoRR.exe @0045a290>
undefined FUN_0045a290(undefined4 * param_1, int param_2, int param_3);
// <LegoRR.exe @0045a2f0>
void Main_InitPanelButtons(void);
// <LegoRR.exe @0045a500>
void Main_LoadInterfaceButtons_ScrollInfo(void);
// <LegoRR.exe @0045a530>
void FUN_0045a530(void);
// <LegoRR.exe @0045a5a0>
undefined FUN_0045a5a0(byte * param_1, int param_2, undefined4 param_3);
// <LegoRR.exe @0045a630>
BOOL Game_GetPanel(char * panelName, int * out_index);
// <LegoRR.exe @0045a670>
uint FUN_0045a670(int param_1, int param_2, int param_3);
// <LegoRR.exe @0045a6d0>
undefined4 FUN_0045a6d0(int param_1, char * param_2, uint * param_3);
// <LegoRR.exe @0045a720>
undefined FUN_0045a720(uint param_1, undefined4 * param_2, int param_3, int param_4, int param_5, char * format, ...);
// <LegoRR.exe @0045a7c0>
undefined4 * FUN_0045a7c0(int param_1, undefined4 font, Rect2F * rect, uint size);
// <LegoRR.exe @0045a850>
void FUN_0045a850(Struct_830 * param_1, char * param_2, ...);
// <LegoRR.exe @0045a870>
undefined FUN_0045a870(int * * param_1, uint param_2, float param_3);
// <LegoRR.exe @0045a8e0>
undefined FUN_0045a8e0(int * param_1);
// <LegoRR.exe @0045a8f0>
undefined FUN_0045a8f0(int * param_1, undefined4 * param_2, undefined4 * param_3);
// <LegoRR.exe @0045a910>
undefined FUN_0045a910(int param_1, int param_2, int param_3, int param_4, int param_5);
// <LegoRR.exe @0045a9a0>
undefined FUN_0045a9a0(int param_1, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @0045a9c0>
undefined FUN_0045a9c0(int param_1, undefined4 * param_2, undefined4 * param_3);
// <LegoRR.exe @0045a9f0>
undefined FUN_0045a9f0(int param_1, float param_2);
// <LegoRR.exe @0045ac80>
undefined FUN_0045ac80(int param_1);
// <LegoRR.exe @0045ad80>
undefined FUN_0045ad80(int param_1, int param_2, BOOL param_3);
// <LegoRR.exe @0045adc0>
undefined FUN_0045adc0(int param_1);
// <LegoRR.exe @0045adf0>
undefined4 FUN_0045adf0(int param_1);
// <LegoRR.exe @0045ae20>
undefined4 FUN_0045ae20(int param_1);
// <LegoRR.exe @0045ae50>
uint FUN_0045ae50(int param_1);
// <LegoRR.exe @0045ae70>
undefined FUN_0045ae70(int param_1, int param_2, int param_3);
// <LegoRR.exe @0045aeb0>
undefined FUN_0045aeb0(int param_1, int param_2, int param_3);
// <LegoRR.exe @0045aef0>
undefined FUN_0045aef0(int param_1, int param_2, int param_3, int param_4, int * param_5, int param_6, int param_7, int param_8);
// <LegoRR.exe @0045b070>
BOOL FUN_0045b070(float param_1, uint param_2, uint param_3, uint param_4, int param_5, undefined4 * param_6);
// <LegoRR.exe @0045b5d0>
int FUN_0045b5d0(uint * param_1, uint * param_2, int param_3, int param_4, int param_5, int param_6, undefined4 * param_7, undefined4 * param_8);
// <LegoRR.exe @0045b850>
undefined4 FUN_0045b850(undefined4 param_1, float * param_2, int param_3, int param_4);
// <LegoRR.exe @0045b8d0>
undefined FUN_0045b8d0(void);
// <LegoRR.exe @0045b8e0>
undefined FUN_0045b8e0(undefined4 param_1);
// <LegoRR.exe @0045ba00>
void Main_LoadInterfaceButtons_ScrollInfo__internal(void);
// <LegoRR.exe @0045bb10>
void FUN_0045bb10(void);
// <LegoRR.exe @0045bb60>
undefined4 FUN_0045bb60(int param_1, int param_2, int param_3, int param_4, int param_5);
// <LegoRR.exe @0045bbc0>
undefined FUN_0045bbc0(int param_1, int param_2, int param_3, float * param_4, float * param_5);
// <LegoRR.exe @0045bbf0>
undefined FUN_0045bbf0(undefined4 * param_1, undefined4 * param_2);
// <LegoRR.exe @0045bc90>
undefined Main_LoadPanelRotationControl(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @0045bf90>
undefined4 FUN_0045bf90(int param_1, int param_2, float param_3);
// <LegoRR.exe @0045c1e0>
undefined FUN_0045c1e0(int param_1, float param_2);
// <LegoRR.exe @0045c230>
undefined FUN_0045c230(int param_1, int param_2, undefined4 * param_3);
// <LegoRR.exe @0045c270>
undefined Main_LoadRightPanelCrystals(char * smallCrystal, char * usedCrystal, char * noSmallCrystal);
// <LegoRR.exe @0045c300>
undefined Level_LoadRewardQuotaCrystals(CFGProperty * root, char * keyBasePath, char * levelName);
// <LegoRR.exe @0045c390>
undefined FUN_0045c390(uint param_1, uint param_2, undefined4 param_3);
// <LegoRR.exe @0045c600>
undefined Main_LoadAirMeter(char * airJuice, uint param_2, uint param_3, uint param_4, char * noAir, uint param_6, uint param_7);
// <LegoRR.exe @0045c6b0>
undefined FUN_0045c6b0(int param_1, undefined * param_2);
// <LegoRR.exe @0045c760>
undefined FUN_0045c760(undefined4 param_1);
// <LegoRR.exe @0045c770>
undefined FUN_0045c770(int param_1);
// <LegoRR.exe @0045c7e0>
undefined Main_LoadRightPanel_CryOreSidebar(char * sidebar, uint param_2, uint param_3, uint param_4);
// <LegoRR.exe @0045c840>
undefined FUN_0045c840(int param_1, int param_2);
// <LegoRR.exe @0045c8b0>
undefined FUN_0045c8b0(void);
// <LegoRR.exe @0045c930>
undefined4 FUN_0045c930(undefined4 param_1, int param_2, int param_3);
// <LegoRR.exe @0045c970>
uint FUN_0045c970(undefined4 param_1, int param_2, int * param_3);
// <LegoRR.exe @0045caf0>
void Main_InitPointers(void);
// <LegoRR.exe @0045cd30>
undefined FUN_0045cd30(CFGProperty * prop);
// <LegoRR.exe @0045ce90>
undefined4 FUN_0045ce90(char * param_1, int * param_2);
// <LegoRR.exe @0045ced0>
undefined4 FUN_0045ced0(int param_1);
// <LegoRR.exe @0045cee0>
undefined FUN_0045cee0(undefined4 param_1);
// <LegoRR.exe @0045cf00>
undefined FUN_0045cf00(undefined4 param_1, float param_2);
// <LegoRR.exe @0045cf20>
undefined4 FUN_0045cf20(void);
// <LegoRR.exe @0045cf30>
undefined FUN_0045cf30(uint param_1, uint param_2);
// <LegoRR.exe @0045d050>
undefined FUN_0045d050(float param_1);
// <LegoRR.exe @0045d080>
undefined Main_LoadPriorityImages(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @0045d1c0>
undefined FUN_0045d1c0(void);
// <LegoRR.exe @0045d210>
BOOL Level_LoadPriorities(CFGProperty * root, char * keyBasePath, char * keyName);
// <LegoRR.exe @0045d320>
undefined Main_LoadPrioritiesImagePositions(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @0045d3d0>
undefined4 FUN_0045d3d0(uint param_1, uint param_2, int param_3, int param_4, int param_5);
// <LegoRR.exe @0045d5c0>
uint FUN_0045d5c0(int param_1, int param_2, int param_3);
// <LegoRR.exe @0045d630>
undefined FUN_0045d630(undefined4 * param_1, uint param_2, uint param_3);
// <LegoRR.exe @0045d680>
undefined FUN_0045d680(uint param_1);
// <LegoRR.exe @0045d6b0>
undefined FUN_0045d6b0(uint param_1);
// <LegoRR.exe @0045d730>
undefined FUN_0045d730(uint param_1);
// <LegoRR.exe @0045d7b0>
undefined FUN_0045d7b0(uint param_1);
// <LegoRR.exe @0045d810>
undefined FUN_0045d810(undefined4 param_1);
// <LegoRR.exe @0045d900>
undefined FUN_0045d900(int priorityIndex);
// <LegoRR.exe @0045d990>
undefined FUN_0045d990(void);
// <LegoRR.exe @0045daa0>
BOOL Main_loadPTLCFG__0045daa0(char * filename, char * keyBlockPath);
// <LegoRR.exe @0045db30>
void Game_PTLEventToAction__0045db30(MessageAction * out_message);
// <LegoRR.exe @0045db60>
undefined FUN_0045db60(int param_1, undefined4 param_2);
// <LegoRR.exe @0045db70>
void Main_InitUnkVectorTables(void);
// <LegoRR.exe @0045dd50>
int * FUN_0045dd50(LevelSurfaceMap * param_1, int * param_2, int param_3);
// <LegoRR.exe @0045ddb0>
undefined FUN_0045ddb0(undefined * param_1);
// <LegoRR.exe @0045ddc0>
void FUN_0045ddc0(int param_1, float * param_2, undefined4 param_3, undefined4 param_4);
// <LegoRR.exe @0045de80>
void FUN_0045de80(undefined4 param_1, undefined4 param_2);
// <LegoRR.exe @0045e6c0>
uint FUN_0045e6c0(int * param_1);
// <LegoRR.exe @0045e720>
undefined4 FUN_0045e720(int * param_1, int param_2);
// <LegoRR.exe @0045e920>
undefined4 FUN_0045e920(int param_1, uint param_2, uint param_3);
// <LegoRR.exe @0045e990>
undefined4 FUN_0045e990(int * * param_1, uint param_2, uint param_3, float * param_4, int * param_5, int * param_6);
// <LegoRR.exe @0045eae0>
undefined4 FUN_0045eae0(int * * param_1, uint param_2, uint param_3, undefined4 * param_4, undefined4 * param_5);
// <LegoRR.exe @0045ec00>
undefined FUN_0045ec00(int param_1, float * param_2);
// <LegoRR.exe @0045eca0>
undefined4 FUN_0045eca0(int param_1, uint param_2, uint param_3);
// <LegoRR.exe @0045f2f0>
undefined4 Lego_TODORewardLoading(void);
// <LegoRR.exe @0045f4b0>
undefined FUN_0045f4b0(int param_1);
// <LegoRR.exe @0045f4f0>
undefined Lego_RewardLoadFonts__0045f4f0(int param_1);
// <LegoRR.exe @0045f550>
undefined FUN_0045f550(uint * param_1);
// <LegoRR.exe @0045f6a0>
undefined FUN_0045f6a0(uint * param_1);
// <LegoRR.exe @0045f7f0>
undefined FUN_0045f7f0(uint * param_1);
// <LegoRR.exe @0045f8b0>
undefined FUN_0045f8b0(uint * param_1);
// <LegoRR.exe @0045fa10>
void FUN_0045fa10(void);
// <LegoRR.exe @0045fa70>
undefined FUN_0045fa70(int param_1);
// <LegoRR.exe @0045fa90>
undefined FUN_0045fa90(int param_1);
// <LegoRR.exe @0045fab0>
BOOL Main_LoadRewardGraphics(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @0045fdb0>
BOOL Main_LoadRewardSaveAdvanceButtons(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @00460060>
undefined4 Main_initFrontEndReward__00460060(void);
// <LegoRR.exe @00460360>
undefined FUN_00460360(int param_1);
// <LegoRR.exe @00460400>
undefined FUN_00460400(int param_1);
// <LegoRR.exe @004604a0>
undefined lego_freeStructSize_318c__004604a0(void);
// <LegoRR.exe @004604b0>
undefined4 Lego_GetUnkStruct_318c__00553994(undefined4 param_1);
// <LegoRR.exe @004604c0>
void FUN_004604c0(void);
// <LegoRR.exe @004604e0>
void Lego_UnkLevelImportantPilot___004604e0(void);
// <LegoRR.exe @00460550>
undefined FUN_00460550(undefined4 * param_1);
// <LegoRR.exe @004605d0>
undefined4 FUN_004605d0(LiveObject * liveObj, int param_2);
// <LegoRR.exe @00460620>
BOOL FUN_00460620(void);
// <LegoRR.exe @00460bd0>
int FUN_00460bd0(char * param_1, int param_2, int param_3);
// <LegoRR.exe @00460c10>
undefined4 FUN_00460c10(void);
// <LegoRR.exe @004611c0>
BOOL FUN_004611c0(void);
// <LegoRR.exe @00461330>
undefined4 FUN_00461330(void);
// <LegoRR.exe @004616d0>
BOOL Main_waitFrontEndRewards__004616d0(void);
// <LegoRR.exe @00461a50>
undefined FUN_00461a50(uint * param_1, uint param_2, uint param_3);
// <LegoRR.exe @00461f50>
int FUN_00461f50(uint param_1);
// <LegoRR.exe @00462090>
int FUN_00462090(undefined4 * param_1, undefined4 * param_2);
// <LegoRR.exe @004622f0>
undefined FUN_004622f0(void);
// <LegoRR.exe @00462530>
undefined FUN_00462530(void);
// <LegoRR.exe @00462650>
undefined FUN_00462650(undefined4 * param_1, undefined4 * param_2, undefined4 * param_3, undefined4 * param_4);
// <LegoRR.exe @00462720>
undefined FUN_00462720(byte * param_1);
// <LegoRR.exe @00462760>
undefined FUN_00462760(int * param_1, int * param_2, float * param_3);
// <LegoRR.exe @004628c0>
undefined FUN_004628c0(uint * param_1, undefined4 * param_2);
// <LegoRR.exe @004629c0>
undefined FUN_004629c0(float param_1);
// <LegoRR.exe @00462a40>
undefined4 FUN_00462a40(void);
// <LegoRR.exe @00462ac0>
undefined FUN_00462ac0(float param_1);
// <LegoRR.exe @00462af0>
void Lego_DecFloat_00555adc(void);
// <LegoRR.exe @00462b10>
void Lego_DecFloat_00555efc(void);
// <LegoRR.exe @00462b30>
void NERPs_IncDat_00556324(void);
// <LegoRR.exe @00462b40>
void NERPs_IncRockMonstersDestroyed(void);
// <LegoRR.exe @00462b50>
void NERPs_IncDat_0055632c(void);
// <LegoRR.exe @00462b60>
undefined NERPs_AddToFloat_00556330(float param_1);
// <LegoRR.exe @00462b80>
undefined NERPs_AddToFloat_00556120(float param_1);
// <LegoRR.exe @00462ba0>
undefined4 * FUN_00462ba0(undefined4 * param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6);
// <LegoRR.exe @00462c20>
undefined4 FUN_00462c20(int * param_1);
// <LegoRR.exe @00462c90>
undefined4 FUN_00462c90(int param_1, char * param_2, int param_3, undefined4 param_4, undefined4 param_5, uint param_6);
// <LegoRR.exe @00462d70>
undefined FUN_00462d70(int param_1, undefined4 param_2);
// <LegoRR.exe @00462d80>
undefined FUN_00462d80(int param_1, uint param_2);
// <LegoRR.exe @00462d90>
BOOL FUN_00462d90(float * param_1);
// <LegoRR.exe @00463060>
BOOL FUN_00463060(ResourceData * resData, int width, int height);
// <LegoRR.exe @00463120>
BOOL Main_LoadRoofTexture(char * filename);
// <LegoRR.exe @00463190>
undefined FUN_00463190(void * param_1);
// <LegoRR.exe @004631e0>
undefined FUN_004631e0(int param_1, int param_2, undefined4 * param_3, undefined4 * param_4, undefined4 * param_5, undefined4 * param_6);
// <LegoRR.exe @004634f0>
undefined FUN_004634f0(void);
// <LegoRR.exe @00463770>
void FUN_00463770(BOOL use3rdFrame);
// <LegoRR.exe @004637b0>
undefined FUN_004637b0(int param_1, int param_2);
// <LegoRR.exe @00463800>
undefined FUN_00463800(void);
// <LegoRR.exe @00463850>
BOOL FUN_00463850(uint param_1, uint param_2, Vector3F * param_3);
// <LegoRR.exe @00463970>
void Lego_LoadScrollInfoPanel__00463970(char * filename, int index, int param_3, int param_4, int param_5);
// <LegoRR.exe @004639f0>
undefined FUN_004639f0(int param_1, uint param_2, uint param_3);
// <LegoRR.exe @00463a30>
undefined FUN_00463a30(int param_1, int param_2, float * param_3, int param_4, int param_5);
// <LegoRR.exe @00463ad0>
undefined FUN_00463ad0(int param_1, float * param_2, int param_3, undefined4 param_4, char * param_5);
// <LegoRR.exe @00463b60>
int FUN_00463b60(int * param_1, uint param_2, uint param_3, int param_4, int param_5);
// <LegoRR.exe @00463ec0>
undefined4 FUN_00463ec0(undefined4 param_1, float * param_2, int param_3, int param_4);
// <LegoRR.exe @00463f50>
undefined4 FUN_00463f50(int param_1, int param_2, int param_3);
// <LegoRR.exe @00463fe0>
undefined FUN_00463fe0(int index);
// <LegoRR.exe @00464100>
undefined FUN_00464100(float param_1);
// <LegoRR.exe @00464160>
undefined Draw_UnkFuncOfInterestTable__00464160(int index, undefined4 * out_param_2, undefined4 * out_param_3);
// <LegoRR.exe @00464190>
undefined FUN_00464190(int param_1, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @004641c0>
int * * FUN_004641c0(ResourceData * in_resData, float param_2);
// <LegoRR.exe @004643d0>
undefined4 * FUN_004643d0(int * param_1, int param_2, int param_3, int param_4);
// <LegoRR.exe @00464480>
uint FUN_00464480(int * * param_1, int * param_2, int param_3, uint param_4, int param_5, uint * param_6, int param_7);
// <LegoRR.exe @004649e0>
undefined FUN_004649e0(ResourceData * * param_1, BOOL use3rdFrame);
// <LegoRR.exe @00464a00>
void Main_Alloc_SFXNames_HashTable(void);
// <LegoRR.exe @00464ee0>
void Res_ResourceSoundCallback(char * sampleName, ResourceData * resData, void * lpValue);
// <LegoRR.exe @00464f10>
void Audio_SetAudioFlag2(BOOL state);
// <LegoRR.exe @00464f30>
BOOL Snd_GetSFX(char * sfxName, int * out_index);
// <LegoRR.exe @00464fc0>
undefined4 Sample_LoadProperty(char * value, int index);
// <LegoRR.exe @004650e0>
undefined4 Sample_ChooseRandomSound(int propIndex);
// <LegoRR.exe @00465140>
void FUN_00465140(void);
// <LegoRR.exe @00465180>
BOOL FUN_00465180(float param_1);
// <LegoRR.exe @004651b0>
BOOL Snd_FUN_004651b0(int sampleIndex, int * out_param_2);
// <LegoRR.exe @00465220>
void Audio_AddToSoundQueue1(int index, BOOL mode);
// <LegoRR.exe @00465260>
void Snd_Play_FUN_00465260(int in_sampleIndex, BOOL modeChoice);
// <LegoRR.exe @004652d0>
void Sample_PlayRandomAtVolume(int sampleIndex, int volume);
// <LegoRR.exe @004652f0>
int Sample_GetRandomVolume(int sampleIndex);
// <LegoRR.exe @00465310>
void Res_PlayResourceSound(ResourceData * resData, int sampleIndex, BOOL flag2, BOOL flag4, Vector3F * opt_position);
// <LegoRR.exe @00465350>
int Snd_PlayOrInitSoundUnk(IDirect3DRMFrame3 * rmFrame3, int sampleIndex, BOOL flag2, BOOL flag4, Vector3F * opt_position);
// <LegoRR.exe @00465420>
float10 Sample_GetRandomDuration(int sampleIndex);
// <LegoRR.exe @00465450>
void Sample_StopSoundBufferInstance(int sampleBufferIndex);
// <LegoRR.exe @00465460>
void FUN_00465460(float elapsed);
// <LegoRR.exe @00465510>
void thunk_FUN_0047b650(void);
// <LegoRR.exe @00465520>
void Audio_SetFlag1_AndOtherFunc(BOOL isSoundOn, BOOL param_2);
// <LegoRR.exe @00465560>
void Audio_SetFlag1_AndOtherFunc_true(BOOL isSoundOn);
// <LegoRR.exe @00465570>
BOOL Audio_GetFlag8(void);
// <LegoRR.exe @00465580>
void Audio_FUN_00465580_true(BOOL setFlag8);
// <LegoRR.exe @00465590>
void Audio_FUN_00465590(BOOL setFlag8, BOOL doSomething);
// <LegoRR.exe @00465630>
BOOL Audio_GetFlag1(void);
// <LegoRR.exe @00465640>
BOOL Main_InitSmokeAnim_empty(void);
// <LegoRR.exe @00465660>
undefined Main_LoadSmokeAnim(char * dirname, char * filebaseName, uint frames);
// <LegoRR.exe @004656f0>
int * FUN_004656f0(int param_1, uint param_2, uint param_3, int * param_4, float param_5, float param_6, float param_7, float param_8, int param_9, int param_10, uint param_11, int param_12);
// <LegoRR.exe @00465c30>
void FUN_00465c30(void);
// <LegoRR.exe @00465c70>
undefined FUN_00465c70(undefined * param_1, int param_2);
// <LegoRR.exe @00465d50>
undefined FUN_00465d50(BOOL param_1);
// <LegoRR.exe @00465d80>
undefined FUN_00465d80(int param_1, int param_2);
// <LegoRR.exe @00465dc0>
undefined FUN_00465dc0(float param_1);
// <LegoRR.exe @00465f10>
int FUN_00465f10(int param_1, int param_2);
// <LegoRR.exe @004660c0>
undefined FUN_004660c0(int param_1, int param_2, float param_3);
// <LegoRR.exe @00466200>
undefined FUN_00466200(int param_1, int param_2, int param_3, float * param_4);
// <LegoRR.exe @00466480>
undefined Level_AllocBlocksStruct_c_Table(LevelData * level);
// <LegoRR.exe @004664d0>
void Level_FreeBlocksStruct_c_Table(void);
// <LegoRR.exe @004664f0>
void Level_Start(LevelData * level);
// <LegoRR.exe @00466510>
BOOL Level_DoSomethingBlockStruct_c__00466510(uint x, uint y);
// <LegoRR.exe @00466640>
undefined Level_SetBlockStruct_c_Value(int x, int y, undefined4 param_3);
// <LegoRR.exe @004666b0>
BOOL Level_DoSomethingBlock_004666b0(int x, int y, undefined4 * param_3);
// <LegoRR.exe @00466750>
BOOL FUN_00466750(LiveObject * liveObj);
// <LegoRR.exe @00466880>
void FUN_00466880(undefined1 param_1);
// <LegoRR.exe @004668a0>
undefined4 FUN_004668a0(LiveObject * liveObj, float * param_2);
// <LegoRR.exe @00466a10>
undefined FUN_00466a10(int param_1, int param_2);
// <LegoRR.exe @00466aa0>
BOOL Game_ParseStats(CFGProperty * root, char * baseKeyPath);
// <LegoRR.exe @00469d50>
undefined FUN_00469d50(int param_1, undefined4 param_2);
// <LegoRR.exe @00469d80>
int Object_GetCostOre(ObjectType objType, int objIndex, int objLevel);
// <LegoRR.exe @00469db0>
int Object_GetCostCrystal(ObjectType objType, int objIndex, int objLevel);
// <LegoRR.exe @00469de0>
int Object_GetCostRefinedOre(ObjectType objType, int objIndex, int objLevel);
// <LegoRR.exe @00469e10>
int LiveObject_GetCrystalDrain(LiveObject * liveObj);
// <LegoRR.exe @00469e40>
int LiveObject_GetCapacity(LiveObject * liveObj);
// <LegoRR.exe @00469e70>
int LiveObject_GetMaxCarry(LiveObject * liveObj);
// <LegoRR.exe @00469ea0>
int LiveObject_GetCarryStart(LiveObject * liveObj);
// <LegoRR.exe @00469ed0>
BOOL LiveObject_SetLevel(LiveObject * liveObj, uint level);
// <LegoRR.exe @00469f70>
float10 LiveObject_GetRouteSpeed(LiveObject * liveObj);
// <LegoRR.exe @00469f80>
float10 LiveObject_GetDrillTimeType(LiveObject * liveObj, SurfaceType surfaceType);
// <LegoRR.exe @00469fa0>
float10 LiveObject_GetRubbleCoef(LiveObject * liveObj);
// <LegoRR.exe @00469fc0>
float10 LiveObject_GetWakeRadius(LiveObject * liveObj);
// <LegoRR.exe @00469fe0>
float10 LiveObject_GetPathCoef(LiveObject * liveObj);
// <LegoRR.exe @0046a000>
float10 LiveObject_GetCollRadius(LiveObject * liveObj);
// <LegoRR.exe @0046a010>
float10 LiveObject_GetCollHeight(LiveObject * liveObj);
// <LegoRR.exe @0046a020>
float10 LiveObject_GetPickSphere(LiveObject * liveObj);
// <LegoRR.exe @0046a030>
float10 LiveObject_GetPainThreshold(LiveObject * liveObj);
// <LegoRR.exe @0046a050>
float10 LiveObject_GetAlertRadius(LiveObject * liveObj);
// <LegoRR.exe @0046a060>
int LiveObject_GetCollBox(LiveObject * liveObj);
// <LegoRR.exe @0046a070>
float10 LiveObject_GetTrackDist(LiveObject * liveObj);
// <LegoRR.exe @0046a080>
float10 LiveObject_GetHealthDecayRate(LiveObject * liveObj);
// <LegoRR.exe @0046a0a0>
float10 LiveObject_GetEnergyDecayRate(LiveObject * liveObj);
// <LegoRR.exe @0046a0c0>
float10 ObjectStats_GetOxygenCoef(ObjectType objType, int objIndex);
// <LegoRR.exe @0046a0e0>
float10 LiveObject_GetOxygenCoef(LiveObject * liveObj);
// <LegoRR.exe @0046a100>
int LiveObject_GetSurveyRadius(LiveObject * liveObj);
// <LegoRR.exe @0046a120>
ObjectStatsFlags1 LiveObject_GetStatsFlags1(LiveObject * liveObj);
// <LegoRR.exe @0046a140>
ObjectStatsFlags2 LiveObject_GetStatsFlags2(LiveObject * liveObj);
// <LegoRR.exe @0046a160>
ObjectStatsFlags3 LiveObject_GetStatsFlags3(LiveObject * liveObj);
// <LegoRR.exe @0046a180>
ObjectStatsFlags1 Object_GetStatsFlags1(ObjectType objType, int objIndex);
// <LegoRR.exe @0046a1a0>
ObjectStatsFlags2 Object_GetStatsFlags2(ObjectType objType, int objIndex);
// <LegoRR.exe @0046a1c0>
ObjectStatsFlags3 Object_GetStatsFlags3(ObjectType objType, int objIndex);
// <LegoRR.exe @0046a1e0>
float10 LiveObject_GetRepairValue(LiveObject * liveObj);
// <LegoRR.exe @0046a200>
int Object_GetLevels(ObjectType objType, int objIndex);
// <LegoRR.exe @0046a220>
int Object_GetWaterEntrances(ObjectType objType, int objIndex, int objLevel);
// <LegoRR.exe @0046a250>
int LiveObject_GetDrillSoundType(LiveObject * liveObj, BOOL isFade);
// <LegoRR.exe @0046a280>
int LiveObject_GetEngineSound(LiveObject * liveObj);
// <LegoRR.exe @0046a2a0>
float10 LiveObject_GetRestPercent(LiveObject * liveObj);
// <LegoRR.exe @0046a2c0>
float10 LiveObject_GetCarryMinHealth(LiveObject * liveObj);
// <LegoRR.exe @0046a2e0>
float10 LiveObject_GetAttackRadius(LiveObject * liveObj);
// <LegoRR.exe @0046a300>
float10 LiveObject_GetStampRadius(LiveObject * liveObj);
// <LegoRR.exe @0046a320>
int LiveObject_GetNumOfToolsCanCarry(LiveObject * liveObj);
// <LegoRR.exe @0046a340>
float10 LiveObject_GetUpgradeTime(LiveObject * liveObj);
// <LegoRR.exe @0046a360>
float10 LiveObject_GetFunctionCoef(LiveObject * liveObj);
// <LegoRR.exe @0046a380>
int Object_GetUpgradeCostOre(ObjectType objType, int objIndex, int objLevel);
// <LegoRR.exe @0046a3b0>
int Object_GetUpgradeCostStuds(ObjectType objType, int objIndex, int objLevel);
// <LegoRR.exe @0046a3e0>
undefined4 FUN_0046a3e0(int param_1, int * out_index);
// <LegoRR.exe @0046a430>
float10 LiveObject_GetFlocks_Height(LiveObject * liveObj);
// <LegoRR.exe @0046a450>
float10 LiveObject_GetFlocks_Randomness(LiveObject * liveObj);
// <LegoRR.exe @0046a470>
float10 LiveObject_GetFlocks_Turn(LiveObject * liveObj);
// <LegoRR.exe @0046a490>
float10 LiveObject_GetFlocks_Tightness(LiveObject * liveObj);
// <LegoRR.exe @0046a4b0>
float10 LiveObject_GetFlocks_Speed(LiveObject * liveObj);
// <LegoRR.exe @0046a4d0>
int LiveObject_GetFlocks_Size(LiveObject * liveObj);
// <LegoRR.exe @0046a4f0>
float10 LiveObject_GetFlocks_GoalUpdate(LiveObject * liveObj);
// <LegoRR.exe @0046a510>
float10 LiveObject_GetFlocks_AttackTime(LiveObject * liveObj);
// <LegoRR.exe @0046a530>
float10 LiveObject_GetAwarenessRange(LiveObject * liveObj);
// <LegoRR.exe @0046a550>
float10 LiveObject_GetPusherDist(LiveObject * liveObj);
// <LegoRR.exe @0046a570>
float10 LiveObject_GetPusherDamage(LiveObject * liveObj);
// <LegoRR.exe @0046a590>
float10 LiveObject_GetLaserDamage(LiveObject * liveObj);
// <LegoRR.exe @0046a5b0>
float10 LiveObject_GetFreezerDamage(LiveObject * liveObj);
// <LegoRR.exe @0046a5d0>
float10 LiveObject_GetFreezerTime(LiveObject * liveObj);
// <LegoRR.exe @0046a5f0>
undefined LiveObject_SetUnkFlags2(LiveObject * liveObj);
// <LegoRR.exe @0046a630>
undefined Lego_FreeLinkedStruct20(undefined * param_1);
// <LegoRR.exe @0046a650>
void Lego_CleanupLinkedStruct20(void);
// <LegoRR.exe @0046a680>
undefined4 FUN_0046a680(int * param_1, int * param_2);
// <LegoRR.exe @0046a6e0>
float FUN_0046a6e0(void);
// <LegoRR.exe @0046a730>
undefined SetLinkedStruct20_Next(int param_1);
// <LegoRR.exe @0046a750>
undefined4 FUN_0046a750(uint * param_1, uint param_2);
// <LegoRR.exe @0046a780>
undefined4 FUN_0046a780(uint param_1);
// <LegoRR.exe @0046a7d0>
undefined FUN_0046a7d0(uint param_1, uint param_2, uint param_3);
// <LegoRR.exe @0046a880>
undefined4 FUN_0046a880(undefined4 * param_1);
// <LegoRR.exe @0046a9c0>
undefined FUN_0046a9c0(int param_1, float param_2);
// <LegoRR.exe @0046a9f0>
undefined FUN_0046a9f0(float param_1);
// <LegoRR.exe @0046aa20>
uint Game_GetFirstObjectiveFlag(ObjectiveFlags objectiveFlags);
// <LegoRR.exe @0046aab0>
undefined Main_InitTexts(Struct_830 * param_1, Struct_830 * param_2, uint param_3, uint param_4, float param_5);
// <LegoRR.exe @0046ac10>
undefined Main_LoadMsgPanel(char * filename, uint param_2, uint param_3, uint param_4, Rect2F * param_5, Rect2F * param_6, float param_7);
// <LegoRR.exe @0046aca0>
void FUN_0046aca0(void);
// <LegoRR.exe @0046ad50>
void FUN_0046ad50(void);
// <LegoRR.exe @0046ad90>
BOOL Lego_GetTexts(char * textName, int * out_index);
// <LegoRR.exe @0046add0>
undefined FUN_0046add0(int param_1, char * param_2);
// <LegoRR.exe @0046ae70>
undefined FUN_0046ae70(int param_1, char * param_2, int param_3);
// <LegoRR.exe @0046aee0>
undefined FUN_0046aee0(char * param_1, uint param_2);
// <LegoRR.exe @0046af20>
undefined Text_DisplayType(TextType textType, uint param_2, BOOL param_3);
// <LegoRR.exe @0046afc0>
undefined FUN_0046afc0(float param_1);
// <LegoRR.exe @0046b490>
undefined Main_InitToolTips_AndBigStruct(ImageFont * font, int param_2, int param_3, float param_4, int screenWidth, int screenHeight, int param_7, float param_8, float param_9, float param_10);
// <LegoRR.exe @0046b790>
undefined4 FUN_0046b790(char * param_1, int * param_2);
// <LegoRR.exe @0046b7e0>
void Lego_LoadToolTip_HasNLEscape__0046b7e0(int index, char * format, ...);
// <LegoRR.exe @0046b920>
undefined FUN_0046b920(int param_1, int param_2);
// <LegoRR.exe @0046b9c0>
undefined FUN_0046b9c0(int param_1, undefined4 param_2);
// <LegoRR.exe @0046b9f0>
undefined FUN_0046b9f0(int param_1, int param_2);
// <LegoRR.exe @0046ba30>
undefined FUN_0046ba30(int param_1);
// <LegoRR.exe @0046ba60>
undefined FUN_0046ba60(int param_1);
// <LegoRR.exe @0046ba80>
undefined FUN_0046ba80(uint mousex, uint mousey, float milliseconds);
// <LegoRR.exe @0046bb70>
undefined FUN_0046bb70(float param_1, float param_2, float param_3, float param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8, undefined4 param_9, undefined4 param_10, undefined4 param_11, undefined4 param_12, undefined4 param_13, int param_14);
// <LegoRR.exe @0046bef0>
undefined FUN_0046bef0(int param_1, uint param_2, uint param_3);
// <LegoRR.exe @0046c2f0>
undefined FUN_0046c2f0(undefined4 * param_1, undefined4 param_2, undefined4 * param_3, char * param_4);
// <LegoRR.exe @0046c370>
void Upgrade_Duplicate(UpgradeData * in_upgrade, UpgradeData * out_upgrade);
// <LegoRR.exe @0046c3b0>
undefined FUN_0046c3b0(int param_1);
// <LegoRR.exe @0046c3d0>
float10 FUN_0046c3d0(UpgradeData * param_1, float param_2, undefined4 param_3);
// <LegoRR.exe @0046c3f0>
undefined FUN_0046c3f0(UpgradeData * upgrade, char * param_2);
// <LegoRR.exe @0046c420>
void Res_LoadUpgradeLevels(ObjectUpgradesData * upgrades, CFGProperty * aeRoot, char * rootName);
// <LegoRR.exe @0046c600>
void LiveObject_ChangeUpgradeParts(ObjectUpgradesData * upgrades, int objLevel);
// <LegoRR.exe @0046c690>
BOOL Vehicle_IsCameraFlipDir(VehicleData * vehicle);
// <LegoRR.exe @0046c6b0>
uint FUN_0046c6b0(VehicleData * vehicle, char * activityName, float elapsed);
// <LegoRR.exe @0046c7d0>
void LiveObject_VehicleUnkUpgrades(VehicleData * vehicle, char * param_2);
// <LegoRR.exe @0046c9b0>
BOOL Res_LoadAEFileVehicle(VehicleData * vehicle, int index, undefined4 resRoot, undefined4 aeFilename, undefined4 rootName);
// <LegoRR.exe @0046d0d0>
undefined FUN_0046d0d0(int param_1);
// <LegoRR.exe @0046d190>
undefined FUN_0046d190(VehicleData * vehicle, BOOL param_2);
// <LegoRR.exe @0046d1e0>
undefined FUN_0046d1e0(VehicleData * vehicle, BOOL param_2);
// <LegoRR.exe @0046d200>
BOOL FUN_0046d200(VehicleData * vehicle, int levelBit, BOOL condition);
// <LegoRR.exe @0046d240>
undefined4 LiveObject_GetVehicle_UpgradesField8(VehicleData * vehicle);
// <LegoRR.exe @0046d250>
void LiveObject_VehicleChangeUpgradeParts(VehicleData * vehicle, int objLevel);
// <LegoRR.exe @0046d280>
undefined FUN_0046d280(VehicleData * vehicle, BOOL param_2);
// <LegoRR.exe @0046d2b0>
BOOL Vehicle_Duplicate(VehicleData * in_vehicle, VehicleData * out_vehicle);
// <LegoRR.exe @0046d400>
void Vehicle_SetOwnerObject(VehicleData * vehicle, undefined4 liveObj);
// <LegoRR.exe @0046d460>
float10 Vehicle_GetAnimFloat10(VehicleData * vehicle);
// <LegoRR.exe @0046d480>
float10 FUN_0046d480(VehicleData * vehicle, float elapsed, float elapsed2, uint param_4);
// <LegoRR.exe @0046d520>
undefined FUN_0046d520(VehicleData * vehicle);
// <LegoRR.exe @0046d580>
void FUN_0046d580(VehicleData * vehicle, BOOL use3rdFrame);
// <LegoRR.exe @0046d5f0>
BOOL Vehicle_GetFlag2(VehicleData * vehicle);
// <LegoRR.exe @0046d610>
void Vehicle_SetOrientation(VehicleData * vehicle, float x, float y, float z);
// <LegoRR.exe @0046d640>
void Vehicle_SetPosition(VehicleData * vehicle, float x, float y, GetSurfaceZCallback * getZcallback, LevelSurfaceMap * surfMap);
// <LegoRR.exe @0046dca0>
ResourceData * Vehicle_GetAEResource(VehicleData * vehicle);
// <LegoRR.exe @0046dcb0>
ResourceData * Vehicle_GetNull(VehicleData * vehicle, undefined4 nullName, undefined4 nullIndex);
// <LegoRR.exe @0046dd10>
ResourceData * Vehicle_GetCameraNull(VehicleData * vehicle, int cameraIndex);
// <LegoRR.exe @0046dd50>
ResourceData * Vehicle_GetDrillNull(VehicleData * vehicle);
// <LegoRR.exe @0046dd80>
ResourceData * Vehicle_GetDepositNull(VehicleData * vehicle);
// <LegoRR.exe @0046ddb0>
ResourceData * Vehicle_GetDriverNull(VehicleData * vehicle);
// <LegoRR.exe @0046dde0>
ResourceData * Vehicle_GetCarryNull(VehicleData * vehicle, int carryIndex);
// <LegoRR.exe @0046de20>
int Vehicle_GetCarryNullFrames(VehicleData * vehicle);
// <LegoRR.exe @0046de30>
float10 Vehicle_GetFloat14(VehicleData * vehicle);
// <LegoRR.exe @0046de50>
undefined Level_Load_FUN_0046de50(ResourceData * resRoot, LevelData * level);
// <LegoRR.exe @0046dfd0>
void FUN_0046dfd0(ResourceData * resData, LevelData * level);
// <LegoRR.exe @0046e140>
void FUN_0046e140(ResourceData * in_resData, LevelData * level);
// <LegoRR.exe @0046e480>
void FUN_0046e480(BOOL param_1);
// <LegoRR.exe @0046e4e0>
undefined FUN_0046e4e0(LevelData * level, int param_2, uint param_3);
// <LegoRR.exe @0046e5f0>
undefined FUN_0046e5f0(int param_1, uint param_2);
// <LegoRR.exe @0046e650>
undefined FUN_0046e650(LevelData * level, float param_2);
// <LegoRR.exe @0046e8d0>
undefined FUN_0046e8d0(LevelData * level);
// <LegoRR.exe @0046eb60>
undefined4 * FUN_0046eb60(int param_1, int param_2, uint * param_3);
// <LegoRR.exe @0046ec60>
int Struct428_CompareCount(Struct_428 * a, Struct_428 * b);
// <LegoRR.exe @0046ec90>
Struct_428 * Level_LoadSearchStruct428(int y, uint unkParam_x, uint unkParam_xMax);
// <LegoRR.exe @0046ed90>
void Level_LoadAddStruct428(Struct_428 * struct428, uint y, uint unkParam_x, uint unkParam_xMax);
// <LegoRR.exe @0046edf0>
void Level_LoadAddFirstStruct428(uint y, uint unkParam_x, uint unkParam_xMax);
// <LegoRR.exe @0046ee40>
BOOL Boot_Load_WeaponTypes(CFGProperty * root, char * keyBasePath);
// <LegoRR.exe @0046f390>
uint Game_GetWeaponType(char * weaponName);
// <LegoRR.exe @0046f3d0>
float10 FUN_0046f3d0(int param_1);
// <LegoRR.exe @0046f400>
float10 FUN_0046f400(int param_1);
// <LegoRR.exe @0046f430>
float10 FUN_0046f430(int param_1);
// <LegoRR.exe @0046f460>
float10 FUN_0046f460(int param_1, int param_2);
// <LegoRR.exe @0046f490>
float10 Weapon_GetWeaponFloat12c4(int weaponType, LiveObject * liveObj);
// <LegoRR.exe @0046f530>
undefined FUN_0046f530(LiveObject * liveObj, int weaponType, BOOL param_3, float param_4, float * param_5);
// <LegoRR.exe @0046f640>
undefined FUN_0046f640(int * * param_1, float param_2, int param_3);
// <LegoRR.exe @0046f670>
undefined FUN_0046f670(int param_1);
// <LegoRR.exe @0046f810>
undefined FUN_0046f810(float param_1);
// <LegoRR.exe @0046f8d0>
undefined4 FUN_0046f8d0(int * * param_1, float * param_2);
// <LegoRR.exe @0046fa30>
undefined FUN_0046fa30(int * * param_1, int * * param_2, undefined4 * param_3, int * param_4, int param_5);
// <LegoRR.exe @0046fbe0>
undefined FUN_0046fbe0(int * param_1, float param_2);
// <LegoRR.exe @0046fdb0>
undefined4 FUN_0046fdb0(LiveObject * liveObj, float * param_2, float * param_3, uint param_4, uint param_5);
// <LegoRR.exe @0046ff30>
undefined4 FUN_0046ff30(undefined4 param_1, float * param_2, float * param_3, undefined4 param_4, undefined4 param_5);
// <LegoRR.exe @004701b0>
undefined FUN_004701b0(undefined4 param_1, undefined4 * param_2, undefined4 * param_3);
// <LegoRR.exe @00470230>
int Lego_GetNextIndex_Struct2b0_TABLE_00504bc0(void);
// <LegoRR.exe @00470250>
int FUN_00470250(void);
// <LegoRR.exe @00470270>
int * * FUN_00470270(int * * param_1, int * * param_2, int * param_3, float param_4, float param_5, int param_6, float param_7);
// <LegoRR.exe @00470520>
undefined FUN_00470520(undefined4 * param_1, float * param_2, float * param_3, int param_4);
// <LegoRR.exe @00470570>
undefined4 FUN_00470570(undefined4 * param_1, float * param_2, float * param_3, float * param_4, int param_5);
// <LegoRR.exe @00470800>
undefined4 FUN_00470800(undefined4 * param_1, float * param_2, float * param_3, int param_4);
// <LegoRR.exe @004708f0>
undefined4 FUN_004708f0(undefined4 * param_1, float * param_2, float * param_3);
// <LegoRR.exe @00470950>
undefined FUN_00470950(ResourceData * resData, float * param_2, float * param_3);
// <LegoRR.exe @00470a20>
undefined FUN_00470a20(int * param_1, float param_2, float * param_3, float * param_4, float param_5, float param_6, float param_7, float param_8);
// <LegoRR.exe @00471580>
int FUN_00471580(int * param_1);
// <LegoRR.exe @004715b0>
float10 FUN_004715b0(int * param_1, int param_2);
// <LegoRR.exe @004715d0>
undefined FUN_004715d0(int * param_1, undefined4 param_2, int param_3);
// <LegoRR.exe @004715f0>
BOOL FUN_004715f0(int param_1, int param_2, float param_3, float param_4, float param_5);
// <LegoRR.exe @00471630>
undefined4 FUN_00471630(LiveObject * param_1, LiveObject * param_2);
// <LegoRR.exe @004718f0>
undefined FUN_004718f0(undefined4 * param_1);
// <LegoRR.exe @00471b20>
undefined4 FUN_00471b20(undefined4 param_1, undefined4 param_2, undefined4 * param_3, undefined4 * param_4, undefined4 param_5);
// <LegoRR.exe @00471b90>
undefined4 FUN_00471b90(undefined4 * param_1, undefined4 * param_2);
// <LegoRR.exe @00471c20>
undefined4 FUN_00471c20(undefined4 * param_1, undefined4 * param_2);
// <LegoRR.exe @00471ce0>
undefined4 FUN_00471ce0(int param_1, int param_2, int param_3);
// <LegoRR.exe @00471d00>
undefined4 FUN_00471d00(int param_1, int param_2);
// <LegoRR.exe @00471d10>
undefined4 FUN_00471d10(int param_1, int param_2);
// <LegoRR.exe @00471d20>
undefined FUN_00471d20(int param_1, undefined4 * param_2, float param_3, int param_4, int param_5);
// <LegoRR.exe @00471f30>
undefined FUN_00471f30(int param_1, undefined4 * param_2, int param_3);
// <LegoRR.exe @00471f60>
undefined4 FUN_00471f60(undefined4 * param_1, int param_2);
// <LegoRR.exe @00471fa0>
undefined4 FUN_00471fa0(int * param_1);
// <LegoRR.exe @00471fe0>
undefined4 FUN_00471fe0(int * param_1, float param_2, float param_3);
// <LegoRR.exe @004721c0>
undefined4 FUN_004721c0(int * param_1, float param_2, int param_3);
// <LegoRR.exe @00472280>
undefined4 FUN_00472280(int * param_1, float param_2);
// <LegoRR.exe @00472320>
undefined4 FUN_00472320(LiveObject * param_1, int param_2);
// <LegoRR.exe @00472340>
undefined4 FUN_00472340(undefined4 * param_1, undefined4 * param_2);
// <LegoRR.exe @004723f0>
undefined4 FUN_004723f0(undefined4 * param_1, undefined4 * param_2);
// <LegoRR.exe @004724a0>
uint FUN_004724a0(void * this, int * param_1);
// <LegoRR.exe @00472570>
uint FUN_00472570(undefined4 param_1, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @00472650>
int * * Avi_FUN_00472650(void * this, char * param_1, int * param_2, int * param_3);
// <LegoRR.exe @004726f0>
undefined Avi_Close_internal(int * * param_1);
// <LegoRR.exe @00472760>
uint FUN_00472760(int * * param_1);
// <LegoRR.exe @00472820>
int * * Avi_Open(char * aviFilename);
// <LegoRR.exe @00472930>
undefined FUN_00472930(undefined4 * param_1);
// <LegoRR.exe @00472980>
undefined8 Avi_FUN_00472980(int * * param_1);
// <LegoRR.exe @00472990>
BOOL Avi_FUN_00472990(int * * param_1);
// <LegoRR.exe @004729b0>
undefined Avi_Close(int * * param_1);
// <LegoRR.exe @004729d0>
ResourceData * ReservedPool<ResourceData>__Init(char * cfgRootName);
// <LegoRR.exe @00472ac0>
void ReservedPool<ResourceData>__Cleanup(void);
// <LegoRR.exe @00472b80>
void Res_SetSharedTextures(char * filepath);
// <LegoRR.exe @00472ba0>
void Res_ToggleSoundCallback(BOOL state);
// <LegoRR.exe @00472bc0>
void Res_SetDrawCallback(ResourceDrawCallback * callback, void * lpValue);
// <LegoRR.exe @00472be0>
void Res_SetSoundCallback(ResourceSoundCallback * callback, undefined4 lpValue);
// <LegoRR.exe @00472c00>
ResourceData * GetRoot(void);
// <LegoRR.exe @00472c10>
ResourceData * ReservedPool<ResourceData>__Next(ResourceData * param_1);
// <LegoRR.exe @00472d00>
void ReservedPool<ResourceData>__Release(ResourceData * resData);
// <LegoRR.exe @00472d10>
void ReservedPool<ResourceData>__Release_internal(ResourceData * in_resData, BOOL isCleanup);
// <LegoRR.exe @00472f90>
ResourceData * Res_LoadResource(ResourceData * resRoot, char * filenameNoExt, char * resourceName, BOOL isLooping);
// <LegoRR.exe @00473600>
BOOL FUN_00473600(ResourceData * resData, undefined4 param_2);
// <LegoRR.exe @00473630>
BOOL Res_ResourceShortNormal_FUN_00473630(ResourceData * resData, char * activityName);
// <LegoRR.exe @00473720>
BOOL Res_SetLightPenumbra(ResourceData * resData, float penumbra);
// <LegoRR.exe @00473740>
BOOL Res_SetLightUmbra(ResourceData * resData, float umbra);
// <LegoRR.exe @00473760>
BOOL Res_SetLightRange(ResourceData * resData, float range);
// <LegoRR.exe @00473780>
undefined FUN_00473780(ResourceData * param_1, undefined * * param_2);
// <LegoRR.exe @004737b0>
ResourceData * Res_CreateLight(ResourceData * in_resData, D3DRMLightType lightType, float red, float green, float blue);
// <LegoRR.exe @00473820>
ResourceData * Res_Unk_LoadVisualMesh(ResourceData * in_resData, int unkMode);
// <LegoRR.exe @00473940>
IDirect3DRMFrame3 * Res_GetFrame1(ResourceData * resData);
// <LegoRR.exe @00473950>
ResourceData * Res_DuplicateResource(ResourceData * in_resData);
// <LegoRR.exe @00473de0>
void Res_SetFlag80(ResourceData * resData, BOOL state);
// <LegoRR.exe @00473e00>
void Res_UnkSetup3DFrameTransform(ResourceData * resData, BOOL use3rdFrame);
// <LegoRR.exe @00473e60>
BOOL Res_GetFlag8(ResourceData * resData);
// <LegoRR.exe @00473e80>
ResourceData * FUN_00473e80(ResourceData * resData, char * param_2, int param_3, undefined4 * param_4);
// <LegoRR.exe @00473f20>
char * Res_GetNull(ResourceData * resData, char * name, int * opt_index);
// <LegoRR.exe @00474060>
void Res_SetOwnerObject(ResourceData * resData, LiveObject * liveObj);
// <LegoRR.exe @00474070>
LiveObject * Res_GetOwnerObject(ResourceData * resData);
// <LegoRR.exe @00474080>
void Res_SetRootSceneFogEnable(BOOL isFogEnabled);
// <LegoRR.exe @004740d0>
void Res_SetRootSceneFogColor(float red, float green, float blue);
// <LegoRR.exe @00474130>
void Res_SetRootSceneFogMethod(D3DRMSceneFogMethod fogMethod);
// <LegoRR.exe @00474160>
void Res_SetRootSceneFogParams(float rvStart, float rvEnd, float rvDensity);
// <LegoRR.exe @00474180>
undefined FUN_00474180(ResourceData * resData, int param_2);
// <LegoRR.exe @00474230>
BOOL FUN_00474230(IDirect3DRMFrame3 * rmFrame3, int * in_count);
// <LegoRR.exe @00474310>
IDirectDrawSurface4 * FUN_00474310(char * filename, BOOL param_2, uint * out_width, uint * out_height, BOOL * out_bool);
// <LegoRR.exe @004746d0>
BOOL BMP_loadFontAlpha__004746d0(char * filename, int * out_number);
// <LegoRR.exe @004747b0>
DirectXSurfaceTuple * Draw_UnkMakeDirectXSurfaceTuple(char * in_filename, BOOL param_2, uint * out_width, uint * out_height);
// <LegoRR.exe @004749d0>
undefined FUN_004749d0(int * * param_1);
// <LegoRR.exe @00474a20>
undefined FUN_00474a20(int * * param_1, undefined4 param_2, int param_3);
// <LegoRR.exe @00474bb0>
int * FUN_00474bb0(ResourceData * resData, uint param_2, int param_3, int param_4, undefined2 * param_5);
// <LegoRR.exe @00474ce0>
int Res_GetMeshGroupCount(ResourceData * resData);
// <LegoRR.exe @00474d20>
undefined Res_SetMeshGroupQuality(ResourceData * resData, D3DRMRenderQuality customQuality, GraphicsQuality quality);
// <LegoRR.exe @00474da0>
uint FUN_00474da0(ResourceData * resData, int index);
// <LegoRR.exe @00474df0>
void FUN_00474df0(ResourceData * resData, int index, BOOL state);
// <LegoRR.exe @00474ec0>
BOOL Res_Unk_GetMeshAppData_out(IDirect3DRMMesh * * lplpMesh, BOOL * shouldSetMesh);
// <LegoRR.exe @00474f00>
BOOL FUN_00474f00(ResourceData * resData, int param_2, uint * param_3, undefined4 param_4, undefined4 * param_5, uint * param_6, uint * param_7);
// <LegoRR.exe @00474f80>
int FUN_00474f80(ResourceData * resData, int param_2, int param_3, int param_4, int param_5);
// <LegoRR.exe @00474ff0>
int FUN_00474ff0(int * param_1, int param_2, int param_3, int param_4, int param_5);
// <LegoRR.exe @00475060>
undefined FUN_00475060(ResourceData * param_1, int param_2, undefined * * param_3);
// <LegoRR.exe @004750f0>
undefined FUN_004750f0(ResourceData * resData, int groupId, BOOL isCorrectPerspective);
// <LegoRR.exe @00475150>
BOOL FUN_00475150(ResourceData * promeshResData, float blockSize100th_x, float blockSize100th_y, float blockSize100th_z);
// <LegoRR.exe @004751d0>
undefined4 Res_LoadVehicleWheels(ResourceData * wheelRes, float * param_2);
// <LegoRR.exe @004752b0>
void Res_SetMeshColorUnk(ResourceData * resData, int index, float r, float g, float b);
// <LegoRR.exe @004752e0>
void Res_SetMeshColorMultiplier(ResourceData * resData, int index, float r, float g, float b, float unkMultiplier);
// <LegoRR.exe @00475330>
undefined FUN_00475330(int * * param_1, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @00475350>
undefined FUN_00475350(int * * param_1, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @00475370>
void Res_SetLightColor(ResourceData * resData, float r, float g, float b, float alpha);
// <LegoRR.exe @004753e0>
float10 Res_DoAnimElapsedCallbacks(ResourceData * resData, float elapsed);
// <LegoRR.exe @00475400>
float10 Res_DoCallbacks(ResourceData * resData, float elapsed);
// <LegoRR.exe @004755c0>
void Res_UpdateAnimTime(ResourceData * resData);
// <LegoRR.exe @00475650>
float10 Res_GetAnimFloat10(ResourceData * resData);
// <LegoRR.exe @004756b0>
undefined4 Res_GetAnimAppData_Fieldc(ResourceData * resData);
// <LegoRR.exe @004756f0>
void Res_SetFramePosition(ResourceData * resData1, ResourceData * opt_resData2, float x, float y, float z);
// <LegoRR.exe @00475730>
void Res_SetFrameOrientation(ResourceData * resData1, ResourceData * opt_resData2, float x, float y, float z, float ux, float uy, float uz);
// <LegoRR.exe @00475780>
void Res_GetPosition(ResourceData * resData, ResourceData * opt_refResData, Vector3F * out_position);
// <LegoRR.exe @004757c0>
void Res_GetOrientation(ResourceData * resData, ResourceData * opt_refResData, Vector3F * out_dvector, Vector3F * out_uvector);
// <LegoRR.exe @00475840>
void Res_AddRotation(ResourceData * resData, D3DRMCombineType combineType, float x, float y, float z, float theta);
// <LegoRR.exe @00475870>
void Res_AddScale(ResourceData * resData, D3DRMCombineType combineType, float rvX, float rvY, float rvZ);
// <LegoRR.exe @004758a0>
void Res_AddTranslation(ResourceData * resData, D3DRMCombineType combineType, float rvX, float rvY, float rvZ);
// <LegoRR.exe @004758d0>
void Res_IdentityFrameTransform(ResourceData * resData);
// <LegoRR.exe @00475970>
void Res_AddTransform(ResourceData * resData, D3DRMCombineType combineType, Matrix4F * matrix);
// <LegoRR.exe @00475990>
float10 FUN_00475990(ResourceData * resData);
// <LegoRR.exe @004759d0>
undefined FUN_004759d0(ResourceData * resData, ResourceData * resRoot);
// <LegoRR.exe @00475a60>
ResourceData * FUN_00475a60(ResourceData * resData);
// <LegoRR.exe @00475ab0>
float10 Res_GetActFrameFloat14(ResourceData * resData);
// <LegoRR.exe @00475af0>
int FUN_00475af0(IDirect3DRMFrame3 * param_1);
// <LegoRR.exe @00475b40>
ResourceData * Res_Create_unassigned(IDirect3DRMFrame3 * rmFrame3);
// <LegoRR.exe @00475bc0>
void Res_GetRelativeFrames(ResourceData * resData1, ResourceData * opt_resData2, IDirect3DRMFrame3 * * out_curFrame, IDirect3DRMFrame3 * * out_refFrame);
// <LegoRR.exe @00475bf0>
ResourceType Main_GetResourceType(char * resourceName, BOOL * out_noTexture);
// <LegoRR.exe @00475cb0>
void ReservedPool<ResourceData>__Alloc(void);
// <LegoRR.exe @00475d30>
undefined * * FUN_00475d30(ResourceData * resData, int param_2, int param_3, undefined4 param_4);
// <LegoRR.exe @00475ec0>
void Res_InitResourceSubdata(ResourceData * resData, char * name, IDirect3DRMLight * rmLight, IDirect3DRMMesh * rmMesh, Struct_34 * unk_lwo);
// <LegoRR.exe @00475f40>
void FUN_00475f40(ResourceData * resData);
// <LegoRR.exe @00475fd0>
BOOL Res_LoadActFrameResource(ResourceData * resData, char * filename, char * frameName, undefined4 * param_4, int param_5, int param_6, ActFrameResource * lastActFrameRes, undefined4 isLWSFile, undefined4 isLooping);
// <LegoRR.exe @004760d0>
void Res_DestroyAppDataCallback(IDirect3DRMFrame3 * rmFrame3);
// <LegoRR.exe @00476100>
IDirect3DRMFrame3 * Res_GetActFrameChildByName(ResourceData * resData, char * frameName, BOOL use3rdFrame);
// <LegoRR.exe @00476230>
void Res_InitResourceAppData(IDirect3DRMFrame3 * rmFrame3, ResourceData * resData, ActFrameResource * actFrameRes, char * filename, int * param_5, char * frameName, float * param_7, float * param_8, int * param_9, SoundResource * soundRes, undefined4 * param_11);
// <LegoRR.exe @004763a0>
void Res_FreeResourceAppData(IDirect3DRMFrame3 * rmFrame3);
// <LegoRR.exe @004763e0>
ResourceData * Res_GetAppData_Resource(IDirect3DRMFrame3 * rmFrame3);
// <LegoRR.exe @00476400>
char * Res_GetAppData_Filename(IDirect3DRMFrame3 * rmFrame3);
// <LegoRR.exe @00476420>
ActFrameResource * Res_GetAppData_ActFrame(IDirect3DRMFrame3 * rmFrame3);
// <LegoRR.exe @00476440>
undefined4 Res_GetAppData_Fieldc(IDirect3DRMFrame3 * rmFrame3);
// <LegoRR.exe @00476460>
float10 Res_GetAppData_Float10(IDirect3DRMFrame3 * rmFrame3);
// <LegoRR.exe @00476480>
float10 Res_GetAppData_Float14(IDirect3DRMFrame3 * rmFrame3);
// <LegoRR.exe @004764a0>
char * Res_GetAppData_SampleName(IDirect3DRMFrame3 * rmFrame3);
// <LegoRR.exe @004764c0>
undefined4 Res_GetAppData_Field20(IDirect3DRMFrame3 * rmFrame3);
// <LegoRR.exe @004764e0>
void Res_AddTransform3DFrame(IDirect3DRMFrame3 * frame1, IDirect3DRMFrame3 * frame2);
// <LegoRR.exe @00476530>
void Res_SetActFrameName(IDirect3DRMFrame3 * rmFrame3, char * format, ...);
// <LegoRR.exe @004765b0>
undefined FUN_004765b0(int * param_1);
// <LegoRR.exe @004765d0>
undefined4 FUN_004765d0(int * param_1);
// <LegoRR.exe @004765f0>
int * FUN_004765f0(IDirect3DRMFrame3 * rmFrame3, undefined4 param_2, undefined * someFunction, undefined4 param_4);
// <LegoRR.exe @004766d0>
BOOL FUN_004766d0(IDirect3DRMFrame3 * param_1, undefined4 param_2);
// <LegoRR.exe @00476880>
ActFrameResource * Res_ReadActFrameResource(char * filename, IDirect3DRMFrame3 * rmFrame3, uint * out_param_3, BOOL isLWSFile, BOOL isLooping);
// <LegoRR.exe @00476a30>
int FUN_00476a30(char * param_1);
// <LegoRR.exe @00476aa0>
BOOL Res_CreateFrame(char * filename, IDirect3DRMFrame3 * rmFrame3);
// <LegoRR.exe @00476b10>
IDirect3DRMMesh * Res_CreateMesh(void * fileData, uint fileSize, char * filename, IDirect3DRMFrame3 * rmFrame3, BOOL param_5);
// <LegoRR.exe @00476bc0>
HRESULT Res_LoadD3DRMTexture3Callback(char * tex_name, char * * param_2, IDirect3DRMTexture3 * * lplpD3DRMTex);
// <LegoRR.exe @00476eb0>
void FUN_00476eb0(IDirect3DRMTexture3 * rmTexture3);
// <LegoRR.exe @00476fa0>
int FUN_00476fa0(int * param_1, int * param_2);
// <LegoRR.exe @00476fd0>
void Res_DestroyD3DRMSharedTextureCallback(IDirect3DRMTexture3 * lpD3DRMTex, SharedTextureResource * sharedTex);
// <LegoRR.exe @00477010>
void ReservedPool<Struct_20>__Init(void);
// <LegoRR.exe @00477040>
void ReservedPool<Struct_20>__Cleanup(void);
// <LegoRR.exe @00477080>
void * Lego_AllocStruct20_ptr1c(float param_1, float param_2, float param_3, float param_4, ResourceData * resData);
// <LegoRR.exe @00477110>
void * ReservedPool<Struct_20>__Next(int param_1, int param_2, int param_3, int param_4, ResourceData * resData);
// <LegoRR.exe @004771d0>
undefined FUN_004771d0(int param_1, undefined4 * param_2, undefined4 * param_3);
// <LegoRR.exe @00477210>
undefined FUN_00477210(int param_1, ResourceData * resData);
// <LegoRR.exe @00477230>
undefined4 FUN_00477230(int param_1);
// <LegoRR.exe @00477270>
undefined Main_SetTVClipDist_InStruct(int param_1, float tvClipDist);
// <LegoRR.exe @00477290>
undefined FUN_00477290(int param_1);
// <LegoRR.exe @004772b0>
undefined FUN_004772b0(int param_1);
// <LegoRR.exe @004772d0>
undefined FUN_004772d0(int param_1, int param_2);
// <LegoRR.exe @00477410>
void Viewport_FUN_00477410(float param_1, ResourceData * resRoot, undefined4 param_3);
// <LegoRR.exe @004774e0>
void ReservedPool<Struct_20>__Release(void * param_1);
// <LegoRR.exe @00477500>
undefined FUN_00477500(int param_1, float param_2);
// <LegoRR.exe @00477510>
undefined FUN_00477510(int param_1, float param_2);
// <LegoRR.exe @00477530>
undefined FUN_00477530(int param_1);
// <LegoRR.exe @00477550>
undefined FUN_00477550(int param_1, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @00477570>
undefined FUN_00477570(int param_1, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @00477590>
undefined FUN_00477590(int param_1, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @004775d0>
undefined * FUN_004775d0(int param_1);
// <LegoRR.exe @00477630>
void ReservedPool<Struct_20>__Alloc(void);
// <LegoRR.exe @004776a0>
undefined FUN_004776a0(void);
// <LegoRR.exe @00477700>
int stringSplit(char * input, char * * out_parts, char * delimiter);
// <LegoRR.exe @00477770>
int FUN_00477770(char * param_1, byte * * param_2);
// <LegoRR.exe @00477810>
char * _strdup(char * strSource);
// <LegoRR.exe @00477850>
char * formatText(char * text, ...);
// <LegoRR.exe @004778d0>
char * strstri(char * str, char * strSearch);
// <LegoRR.exe @00477930>
uint hash_string(LPCSTR str, BOOL bIgnoreBlanks, BOOL bIgnoreCase);
// <LegoRR.exe @004779d0>
uint parseBoolLiteral(char * text);
// <LegoRR.exe @00477a60>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
// <LegoRR.exe @00477e90>
void Main_DisableTextureManagement_NonVoodoo2(void);
// <LegoRR.exe @00477eb0>
void Boot_ParseCmdFlags(char * args, BOOL * out_nosound, BOOL * out_insistOnCD);
// <LegoRR.exe @004781f0>
void Main_UpdateAndRender__004781f0(BOOL doFillSurface);
// <LegoRR.exe @00478230>
DebugFlags Config_GetDebugFlags(void);
// <LegoRR.exe @00478240>
int Setup_GetDeviceBitsPerPixel(void);
// <LegoRR.exe @00478260>
void Main_DoDirect3DRMUpdate(void);
// <LegoRR.exe @00478290>
BOOL Main_SetGameFunctions(GameFunctions * gameFuncs);
// <LegoRR.exe @004782c0>
DWORD timeGetTime(void);
// <LegoRR.exe @004782d0>
BOOL Win_ShouldHandleMessage(MSG * msg);
// <LegoRR.exe @00478300>
void Win_HandleMessageQueue(void);
// <LegoRR.exe @00478370>
void Win_ShowGameWindow(BOOL isFullScreen, int windowedX, int windowedY, int screenWidth, int screenHeight);
// <LegoRR.exe @00478490>
BOOL Main_Direct3DRMCreate(DeviceMode * device, IUnknown * ddraw1, IDirectDrawSurface4 * ddSurface, BOOL isFullScreen);
// <LegoRR.exe @004785d0>
void Win_AdjustMainWindowedRect(LPRECT lpRect);
// <LegoRR.exe @004785f0>
void Draw_SetDirectXGraphicsQuality(GraphicsQuality quality, BOOL dither, BOOL filter, BOOL mipmap, BOOL linearmipmap, BOOL blend, BOOL sort);
// <LegoRR.exe @00478690>
BOOL Win_SetMainWindowTitle(LPCSTR title);
// <LegoRR.exe @004786b0>
BOOL Win_CreateMainWindow(HINSTANCE hInstance);
// <LegoRR.exe @00478780>
LRESULT Win_WindowProc__FullScreen(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
// <LegoRR.exe @00478980>
LRESULT Win_WindowProc__Windowed(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
// <LegoRR.exe @00478b40>
LRESULT Win_WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
// <LegoRR.exe @00478b90>
void Draw_SetRenderState(uint renderStateType, undefined4 renderStateValue);
// <LegoRR.exe @00478c00>
void Draw_CleanupRenderStates(void);
// <LegoRR.exe @00478c40>
undefined SFX_UNKCallsMixer__00478c40(undefined1 param_1, undefined1 param_2);
// <LegoRR.exe @00478c60>
undefined FUN_00478c60(float * param_1, float * param_2);
// <LegoRR.exe @00478c80>
undefined4 SFX_UnkMixer__00478c80(float * param_1, float * param_2, int param_3);
// <LegoRR.exe @004790b0>
void ReservedPool<CFGProperty>__Init(void);
// <LegoRR.exe @004790e0>
void ReservedPool<CFGProperty>__Cleanup(void);
// <LegoRR.exe @00479120>
CFGProperty * CFG_Open(char * filename);
// <LegoRR.exe @00479210>
char * CFG_JoinPath(char * keyPath1, char * keyPath2, ...);
// <LegoRR.exe @004792b0>
CFGProperty * CFG_GetBlockFirstChild(CFGProperty * root, char * keyPath);
// <LegoRR.exe @004792e0>
CFGProperty * CFG_NextFlatProperty(CFGProperty * prop);
// <LegoRR.exe @00479310>
char * CFG_CopyPropertyValue(CFGProperty * prop, char * keyPath);
// <LegoRR.exe @00479370>
char * CFG_GetPropertyValue(CFGProperty * root, char * keyPath);
// <LegoRR.exe @00479390>
uint CFG_GetPropertyBool(CFGProperty * prop, char * keyPath);
// <LegoRR.exe @004793d0>
float10 CFG_GetPropertyRadians(CFGProperty * root, char * keyPath);
// <LegoRR.exe @00479430>
BOOL CFG_GetPropertyRGBF(CFGProperty * root, char * keyPath, float * out_r, float * out_g, float * out_b);
// <LegoRR.exe @00479500>
void CFG_Close(CFGProperty * root);
// <LegoRR.exe @00479530>
CFGProperty * ReservedPool<CFGProperty>__Next(CFGProperty * previous);
// <LegoRR.exe @00479580>
void ReservedPool<CFGProperty>__Release(CFGProperty * prop);
// <LegoRR.exe @004795a0>
CFGProperty * CFG_GetProperty(CFGProperty * prop, char * keyPath);
// <LegoRR.exe @00479750>
void ReservedPool<CFGProperty>__Alloc(void);
// <LegoRR.exe @004797c0>
Vector3F * Vector3_Random(Vector3F * out_vector);
// <LegoRR.exe @004797d0>
Vector3F * Vector3_Rotate(Vector3F * out_vector, Vector3F * v, Vector3F * axis, float theta);
// <LegoRR.exe @004797f0>
Vector3F * Vector3_VectorSqrtUnk(Vector3F * out_vector, Vector3F * a, Vector3F * b, Vector3F * c);
// <LegoRR.exe @004798f0>
float10 FUN_004798f0(float * param_1, float * param_2, float * param_3, int param_4);
// <LegoRR.exe @00479b60>
short randomInt16(void);
// <LegoRR.exe @00479b70>
float10 Game_ChooseRandomRange(float rangeMin, float rangeMax);
// <LegoRR.exe @00479ba0>
BOOL Vector3_Unk_FUN_00479ba0(Vector3F * out_vector, Vector3F * a, Vector3F * b, Vector3F * c, Vector3F * d);
// <LegoRR.exe @00479cf0>
BOOL Vector3_SubAC_MulD_Div_DotProductBD(float * out_value, Vector3F * a, Vector3F * b, Vector3F * c, Vector3F * d);
// <LegoRR.exe @00479d70>
Vector3F * Vector3_AddScaled(Vector3F * out_vector, Vector3F * a, Vector3F * b, float scalar);
// <LegoRR.exe @00479db0>
Point2F * Vector2_UnkOperation5(Point2F * out_point, Point2F * a, Point2F * b, Point2F * c, Point2F * d);
// <LegoRR.exe @00479e40>
BOOL FUN_00479e40(Point2F * param_1, Point2F * param_2, Point2F * param_3, int count);
// <LegoRR.exe @00479ed0>
BOOL Vector3_CompareUnk1(Vector3F * a, float scalar, Vector3F * b, Vector3F * c);
// <LegoRR.exe @00479fa0>
void FlocksMatrix_FUN_00479fa0(float * inputs, float * matrix_a, float * matrix_b);
// <LegoRR.exe @0047a010>
void FlocksMatrix_FUN_0047a010(float * matrix, float theta);
// <LegoRR.exe @0047a060>
void FlocksMatrix_FUN_0047a060(float * matrix, float theta);
// <LegoRR.exe @0047a0b0>
void FlocksMatrix_FUN_0047a0b0(float * matrix, float theta);
// <LegoRR.exe @0047a100>
void FlocksMatrix_FUN_0047a100(float * matrix, Vector3F * vector);
// <LegoRR.exe @0047a130>
void FlocksMatrix_IdentityUnk(float * matrix);
// <LegoRR.exe @0047a160>
void FlocksMatrix_Clear(float * matrix);
// <LegoRR.exe @0047a170>
void FlocksMatrix_FUN_0047a170(float * matrix_a, float * matrix_b);
// <LegoRR.exe @0047a1a0>
ImageFont * Image_LoadFont(char * filename);
// <LegoRR.exe @0047a410>
undefined FUN_0047a410(ImageFont * font, uint * param_2, int * param_3, byte * param_4, undefined4 * param_5);
// <LegoRR.exe @0047a440>
void FUN_0047a440(ImageFont * font, int param_2, int param_3, char * format, ...);
// <LegoRR.exe @0047a470>
undefined FUN_0047a470(undefined4 * param_1, int param_2, int param_3, byte * param_4, undefined4 * param_5);
// <LegoRR.exe @0047a4a0>
uint FUN_0047a4a0(ImageFont * font, int param_2, int param_3, int param_4, int * param_5, byte * param_6, undefined4 * param_7);
// <LegoRR.exe @0047a730>
int Font_MeasureCharWidthEx(ImageFont * font, int param_2, int param_3, char c, BOOL param_5);
// <LegoRR.exe @0047a7e0>
int Font_MeasureCharWidth(ImageFont * font, char c);
// <LegoRR.exe @0047a800>
undefined4 Font_GetField_be4(ImageFont * font);
// <LegoRR.exe @0047a810>
void ReservedPool<ImageFont>__Release(ImageFont * font);
// <LegoRR.exe @0047a840>
ImageFont * ReservedPool<ImageFont>__Next(ImageBMP * bitmap);
// <LegoRR.exe @0047a880>
void ReservedPool<ImageFont>__Alloc(void);
// <LegoRR.exe @0047a900>
BOOL InitDirectSound(HWND hWnd);
// <LegoRR.exe @0047aac0>
void Main_DirectSoundCleanup(void);
// <LegoRR.exe @0047ab10>
BOOL SFX_IsValidVolumeModifier(int volume);
// <LegoRR.exe @0047ab30>
int Sample_Load(char * in_filename, BOOL isStreamed, BOOL isMultiple, int volumeAdjust);
// <LegoRR.exe @0047ad90>
BOOL Sample__Next(int * out_sfxIndex);
// <LegoRR.exe @0047adc0>
BOOL Sample_CloseStreamed(int sfxIndex);
// <LegoRR.exe @0047ae40>
void Snd_SetListener3DRootFrame(IDirect3DRMFrame3 * rmFrame3);
// <LegoRR.exe @0047ae60>
void Snd_UpdateListener3D(void);
// <LegoRR.exe @0047ae80>
void Snd_UpdateListener3D_internal(IDirect3DRMFrame3 * rmFrame3);
// <LegoRR.exe @0047afd0>
void Snd_SetBuffer3DPosition(IDirectSound3DBuffer * sound3dBuffer, Vector3F * position);
// <LegoRR.exe @0047aff0>
undefined4 * FUN_0047aff0(undefined4 param_1, int param_2);
// <LegoRR.exe @0047b030>
int SFX_UnkAdjustVolumeOrPlay___0047b030(undefined4 unkMode, IDirect3DRMFrame3 * rmFrame3, int sampleIndex, BOOL modeChoice, Vector3F * opt_position);
// <LegoRR.exe @0047b2e0>
undefined FUN_0047b2e0(undefined4 param_1, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @0047b310>
void Sample_PlayAtVolume(int sampleDataIndex, int volume);
// <LegoRR.exe @0047b390>
int Sample_GetVolume(int sampleDataIndex);
// <LegoRR.exe @0047b3b0>
IDirectSoundBuffer * Sample_GetSoundBufferInstance(int sampleBufferIndex);
// <LegoRR.exe @0047b3f0>
void Sample_StopSoundBufferInstance_internal(int sampleBufferIndex);
// <LegoRR.exe @0047b420>
void FUN_0047b420(void);
// <LegoRR.exe @0047b460>
void Res_InitSoundBufferResource(IDirect3DRMFrame3 * rmFrame3, IDirectSound3DBuffer * ds3dBuffer);
// <LegoRR.exe @0047b4e0>
undefined FUN_0047b4e0(undefined4 param_1, int * param_2);
// <LegoRR.exe @0047b560>
undefined FUN_0047b560(undefined4 param_1, int param_2);
// <LegoRR.exe @0047b5a0>
uint FUN_0047b5a0(undefined4 param_1, int param_2, int param_3);
// <LegoRR.exe @0047b5f0>
uint FUN_0047b5f0(undefined4 param_1, int param_2, int * param_3);
// <LegoRR.exe @0047b650>
void FUN_0047b650(void);
// <LegoRR.exe @0047b6d0>
undefined FUN_0047b6d0(IDirect3DRMFrame3 * rmFrame3, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @0047b760>
void Audio_SetMinDistFor3DSoundsOnTopView(float minDist);
// <LegoRR.exe @0047b790>
undefined Main_SetMaxDistFor3DSounds(undefined4 maxDist);
// <LegoRR.exe @0047b7c0>
undefined Audio_SetSoundVolumeModifier(int volume);
// <LegoRR.exe @0047b7f0>
undefined FUN_0047b7f0(int param_1);
// <LegoRR.exe @0047b810>
void Audio_InitSoundBufferVolume(void);
// <LegoRR.exe @0047b840>
BOOL Sample_OpenInMemory(SampleData * sfxData, char * filename, BOOL flag_asterisk);
// <LegoRR.exe @0047b980>
BOOL Sample_CreateSoundBuffers(SampleData * param_1);
// <LegoRR.exe @0047ba50>
BOOL Sample_CopyToSoundBuffer(SampleData * param_1);
// <LegoRR.exe @0047bba0>
float10 Sample_GetDuration(int sfxIndex);
// <LegoRR.exe @0047bc30>
BOOL AudioPlayback_DoLooping__0047bc30(LPSTR filename, BOOL modeChoice, int volume);
// <LegoRR.exe @0047bce0>
BOOL AudioPlayback_Cleanup(BOOL modeChoice);
// <LegoRR.exe @0047bd60>
BOOL Snd_FUN_0047bd60(LPSTR filename, BOOL modeChoice, int volume);
// <LegoRR.exe @0047bef0>
uint FUN_0047bef0(BOOL modeChoice);
// <LegoRR.exe @0047c070>
undefined FUN_0047c070(int param_1);
// <LegoRR.exe @0047c380>
BOOL Vector3_Equals(Vector3F * a, Vector3F * b);
// <LegoRR.exe @0047c3c0>
float10 Main_SetRollOffFor3DSounds(float rollOff);
// <LegoRR.exe @0047c420>
uint Game_GetUnkMask__0047c420(void);
// <LegoRR.exe @0047c430>
void Main_InitDirectXBase(HWND hWnd);
// <LegoRR.exe @0047c480>
BOOL Dlg_PopulateDriverModes(DriverMode * ref_driverModes, uint * out_count);
// <LegoRR.exe @0047c4b0>
BOOL Dlg_DirectDrawDriverEnumerate_Callback(LPGUID lpGuid, LPSTR lpDriverName, LPSTR lpDriverDescription, LPVOID lpContext);
// <LegoRR.exe @0047c5a0>
BOOL Dlg_PopulateDeviceModes(DriverMode * driverMode, DeviceMode * ref_deviceModes, uint * out_count);
// <LegoRR.exe @0047c640>
HRESULT Dlg_DirectDrawDeviceEnumerate_Callback(LPGUID lpGuid, LPSTR lpDeviceDescription, LPSTR lpDeviceName, D3DDEVICEDESC_V1 * lpD3DHWDeviceDesc, D3DDEVICEDESC_V1 * lpD3DHELDeviceDesc, LPVOID lpContext);
// <LegoRR.exe @0047c770>
BOOL Dlg_PopulateScreenModes(DriverMode * driverMode, BOOL isFullScreen, ScreenMode * ref_ScreenModes, uint * out_count);
// <LegoRR.exe @0047c810>
HRESULT Dlg_DirectDrawScreenEnumerate_Callback(DDSURFACEDESC2 * lpDDSurfaceDesc, LPVOID lpContext);
// <LegoRR.exe @0047c8d0>
BOOL Main_DirectDrawCreate(BOOL isFullScreen, DriverMode * driver, DeviceMode * device, ScreenMode * screen, int x, int y, int screenWidth, int screenHeight);
// <LegoRR.exe @0047cb90>
void Draw_Render(void);
// <LegoRR.exe @0047cbb0>
int Image_FUN_0047cbb0(int * param_1, char * param_2);
// <LegoRR.exe @0047cee0>
void Draw_CopyToDrawTarget(void);
// <LegoRR.exe @0047cf10>
void Draw_RenderWindowed(void);
// <LegoRR.exe @0047cfb0>
void Main_CleanupDirectXBase(void);
// <LegoRR.exe @0047d010>
void Main_CalculateTextureUsage(uint * ref_textureUsage);
// <LegoRR.exe @0047d090>
BOOL Draw_GetAvailableVideoMemory(uint * out_totalMem, uint * out_freeMem);
// <LegoRR.exe @0047d0e0>
HRESULT Draw_FillSurface(Rect2F * rect, uint rgbColor);
// <LegoRR.exe @0047d1a0>
BOOL Main_InitClipperRegion(BOOL isFullScreen, int screenWidth, int screenHeight);
// <LegoRR.exe @0047d2c0>
undefined FUN_0047d2c0(undefined4 param_1, int * param_2);
// <LegoRR.exe @0047d590>
uint packNativeRGB(IDirectDrawSurface4 * ddSurface, uint rgbColor);
// <LegoRR.exe @0047d6b0>
int countBits2(uint value);
// <LegoRR.exe @0047d6d0>
void ReservedPool<ImageBMP>__Init(void);
// <LegoRR.exe @0047d6f0>
void ReservedPool<ImageBMP>__Cleanup(void);
// <LegoRR.exe @0047d730>
void ReservedPool<ImageBMP>__Release(ImageBMP * image);
// <LegoRR.exe @0047d750>
BOOL Image_FUN_0047d750(IDirectDrawSurface4 * ddSurface, DDSURFACEDESC2 * surfaceDesc);
// <LegoRR.exe @0047d7e0>
BOOL Image_FUN_0047d7e0(int param_1, DDSURFACEDESC2 * surfaceDesc);
// <LegoRR.exe @0047d9c0>
int countBits(uint value);
// <LegoRR.exe @0047d9e0>
int firstBit(uint value);
// <LegoRR.exe @0047da00>
undefined Image_ReorderPixelsBPP(DDSURFACEDESC2 * surfaceDesc);
// <LegoRR.exe @0047dac0>
BOOL Image_FUN_0047dac0(int param_1, DDSURFACEDESC2 * surfaceDesc);
// <LegoRR.exe @0047dc90>
ImageBMP * Image_LoadBMP(char * filename, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @0047de50>
uint packRGB(byte red, byte green, byte blue);
// <LegoRR.exe @0047de80>
undefined Image_SetFirstColorAsKey(ImageBMP * image);
// <LegoRR.exe @0047deb0>
void Image_unkFogFromFloat__0047deb0(ImageBMP * image, float red_low, float green_low, float blue_low, float red_high, float green_high, float blue_high);
// <LegoRR.exe @0047df70>
undefined Image_Blt__0047df70(ImageBMP * bitmap, float * param_2, float * param_3, float * param_4);
// <LegoRR.exe @0047e120>
void * Image_Lock(ImageBMP * image, uint * out_length, uint * out_bitsPerPixel);
// <LegoRR.exe @0047e190>
undefined Image_Unlock(ImageBMP * image);
// <LegoRR.exe @0047e1b0>
uint Image_GetLastColor24(ImageBMP * image);
// <LegoRR.exe @0047e210>
uint Image_GetUpperBitMask(ImageBMP * image);
// <LegoRR.exe @0047e260>
BOOL Image_FUN_0047e260(ImageBMP * image, int param_2, int param_3);
// <LegoRR.exe @0047e310>
int * * ReservedPool<ImageBMP>__NextImage(int * directDrawSurface4, int width, int height, uint firstColor, uint lastColor);
// <LegoRR.exe @0047e380>
void ReservedPool<ImageBMP>__Alloc(void);
// <LegoRR.exe @0047e3f0>
void Image_Cleanup_FUN_0047e3f0(void);
// <LegoRR.exe @0047e450>
uint unpackNativeRGB(IDirectDrawSurface4 * ddSurface, undefined4 rgbColor);
// <LegoRR.exe @0047e590>
void unpackRGB(uint rgbColor, byte * out_red, byte * out_green, byte * out_blue);
// <LegoRR.exe @0047e5c0>
undefined Image_CreateCapture(ImageBMP * image, int captureWidth, int captureHeight);
// <LegoRR.exe @0047e6a0>
undefined ReservedPool<ImageBMP>__NextCapture(ImageBMP * image, IUnknown * directDrawSurface, int width, int height, uint firstColor, uint lastColor);
// <LegoRR.exe @0047e700>
undefined FUN_0047e700(int * * param_1, char * param_2);
// <LegoRR.exe @0047e720>
undefined4 * FUN_0047e720(void * this, byte param_1);
// <LegoRR.exe @0047e740>
undefined FUN_0047e740(undefined4 * param_1);
// <LegoRR.exe @0047e780>
undefined4 * FUN_0047e780(void * this, int param_1, int param_2, int param_3, char param_4);
// <LegoRR.exe @0047e7d0>
uint FUN_0047e7d0(void * this, int param_1, int param_2, int param_3, char param_4);
// <LegoRR.exe @0047e9d0>
undefined FUN_0047e9d0(int param_1);
// <LegoRR.exe @0047ea00>
undefined4 FUN_0047ea00(int param_1);
// <LegoRR.exe @0047ea10>
undefined4 FUN_0047ea10(int param_1);
// <LegoRR.exe @0047ea20>
undefined FUN_0047ea20();
// <LegoRR.exe @0047ea70>
undefined FUN_0047ea70();
// <LegoRR.exe @0047eaa0>
int FUN_0047eaa0(uint param_1);
// <LegoRR.exe @0047eac0>
undefined4 * Avi_FUN_0047eac0(void * this, char * param_1);
// <LegoRR.exe @0047ec40>
undefined4 * FUN_0047ec40(void * this, byte param_1);
// <LegoRR.exe @0047ec60>
undefined FUN_0047ec60(undefined4 * param_1);
// <LegoRR.exe @0047eca0>
undefined FUN_0047eca0(void * this, int * param_1);
// <LegoRR.exe @0047ede0>
undefined FUN_0047ede0();
// <LegoRR.exe @0047eeb0>
undefined FUN_0047eeb0(void * this, undefined4 param_1);
// <LegoRR.exe @0047ef40>
void InitAVIFile(IDirectDraw4 * ddraw);
// <LegoRR.exe @0047ef50>
undefined4 * Avi_FUN_0047ef50(char * param_1);
// <LegoRR.exe @0047efb0>
uint FUN_0047efb0(undefined4 param_1);
// <LegoRR.exe @0047efc0>
undefined FUN_0047efc0(int param_1, undefined4 param_2);
// <LegoRR.exe @0047f000>
undefined FUN_0047f000(void * param_1, undefined4 param_2);
// <LegoRR.exe @0047f010>
uint FUN_0047f010(int param_1);
// <LegoRR.exe @0047f020>
undefined4 FUN_0047f020(int param_1);
// <LegoRR.exe @0047f030>
undefined FUN_0047f030(undefined * * param_1);
// <LegoRR.exe @0047f040>
uint FUN_0047f040(int param_1);
// <LegoRR.exe @0047f050>
BOOL Main_DirectInputCreate(void);
// <LegoRR.exe @0047f1b0>
void Input_UpdateKeyboardState(void);
// <LegoRR.exe @0047f270>
int Input_GetNumKeysPressed(void);
// <LegoRR.exe @0047f290>
void Input_DirectInputCleanup(void);
// <LegoRR.exe @0047f2d0>
void Input_UpdateMousePosition(void);
// <LegoRR.exe @0047f390>
undefined Input_SetMousePosition(int x, int y);
// <LegoRR.exe @0047f3f0>
void InitFileSystem(char * gamename, BOOL insistOnCD, char * regKey);
// <LegoRR.exe @0047f7b0>
BOOL Path_CheckForCDROM(void);
// <LegoRR.exe @0047f850>
BOOL Path_SetDataDir(char * dirname);
// <LegoRR.exe @0047f8c0>
void printf(char * format, ...);
// <LegoRR.exe @0047f900>
int WAD_Open(char * filename);
// <LegoRR.exe @0047f920>
BOOL Path_GetCDROMDataPath(char * out_filepath, char * filename);
// <LegoRR.exe @0047f960>
int Path_MakeDataSubdir(char * dirname);
// <LegoRR.exe @0047f9a0>
FileStream * File_Open(char * in_filename, char * mode);
// <LegoRR.exe @0047fb10>
int File_Seek(FileStream * file, int offset, int origin);
// <LegoRR.exe @0047fc40>
uint File_Read(byte * out_buffer, uint size, uint count, FileStream * file);
// <LegoRR.exe @0047fd10>
uint File_Write(byte * buffer, uint size, int count, FileStream * file);
// <LegoRR.exe @0047fd80>
int File_Close(FileStream * file);
// <LegoRR.exe @0047fdd0>
int File_Tell(FileStream * file);
// <LegoRR.exe @0047fe20>
BOOL File_Exist(char * in_filename);
// <LegoRR.exe @0047fee0>
int File_GetC(FileStream * file);
// <LegoRR.exe @0047ff60>
int File_GetLength(FileStream * file);
// <LegoRR.exe @0047ffa0>
char * WAD_GetS__internal(char * out_str, int num, FileStream * file);
// <LegoRR.exe @00480000>
char * File_GetS(char * out_str, int num, FileStream * file);
// <LegoRR.exe @00480070>
int File_PrintF(FileStream * file, char * format, ...);
// <LegoRR.exe @004800e0>
FileLocation File_GetLocation(FileStream * file);
// <LegoRR.exe @004800f0>
FileLocation File_FindLocation(char * filename, char * mode);
// <LegoRR.exe @00480160>
BOOL WAD_EntryOpen__internal(WADEntryStream * wadStream, char * filename);
// <LegoRR.exe @00480190>
FileStream * File__New(FileLocation location);
// <LegoRR.exe @004801f0>
void * malloc(uint size);
// <LegoRR.exe @00480200>
void free(void * ptr);
// <LegoRR.exe @00480210>
void File__Dispose(FileStream * file);
// <LegoRR.exe @00480280>
char * Path_StripDataDir(char * filename);
// <LegoRR.exe @00480310>
char * File_GetS_StripLineEnd(char * out_str, int num, FileStream * file);
// <LegoRR.exe @00480360>
byte * File_ReadAllBytes(char * filename, uint * out_length);
// <LegoRR.exe @00480380>
byte * File_ReadAll(char * filename, uint * out_length, BOOL isBinary);
// <LegoRR.exe @00480430>
int File_SharedOpen(char * filename, uint * out_length);
// <LegoRR.exe @004804e0>
char * Path_JoinDataDir(char * filename);
// <LegoRR.exe @00480570>
void File_SetOpenCallback(FileOpenCallback * callback, void * lpValue);
// <LegoRR.exe @00480590>
void Scan_ReadDataDirList(char * listFilename);
// <LegoRR.exe @00480650>
undefined Scan_Directory(char * dirname);
// <LegoRR.exe @00480830>
int Scan_File(char * filename);
// <LegoRR.exe @00480870>
BOOL ReservedPool<Struct_34>__Init(char * sharedTextures);
// <LegoRR.exe @00480910>
BOOL FUN_00480910(void);
// <LegoRR.exe @00480a40>
uint FUN_00480a40(undefined4 param_1);
// <LegoRR.exe @00480a60>
Struct_34 * ReservedPool<Struct_34>__Next(void);
// <LegoRR.exe @00480a90>
void ReservedPool<Struct_34>__Release(Struct_34 * param_1);
// <LegoRR.exe @00480ab0>
void ReservedPool<Struct_34>__Alloc(void);
// <LegoRR.exe @00480b30>
Struct_34 * Res_Unk_CreateUserVisualStruct34(IDirect3DRMFrame3 * rmFrame3, undefined4 param_2, undefined4 unkFlags, undefined4 param_4, int unkMode);
// <LegoRR.exe @00480bc0>
Struct_34 * ReservedPool<Struct_34>__Next_2(Struct_34 * param_1, IDirect3DRMFrame3 * rmFrame3);
// <LegoRR.exe @00480ca0>
int * Res_CreateLWO(char * filename, IDirect3DRMFrame3 * rmFrame3, BOOL isNoTexture);
// <LegoRR.exe @00480d80>
BOOL FUN_00480d80(char * filename, Struct_34 * struct34, undefined4 * struct20, BOOL isNoTexture);
// <LegoRR.exe @00481ae0>
undefined FUN_00481ae0(char * param_1, int param_2, int param_3, int param_4);
// <LegoRR.exe @00481d80>
int * FUN_00481d80(char * str, char * out_str, int * out_value, int * out_unkposition);
// <LegoRR.exe @00481e40>
undefined FUN_00481e40(char * param_1, char * param_2, int * param_3, int param_4);
// <LegoRR.exe @00481f10>
undefined FUN_00481f10(int param_1, int param_2);
// <LegoRR.exe @00482260>
undefined FUN_00482260(int param_1, int param_2, float * param_3, float param_4, float param_5, float param_6, float param_7, float param_8, float param_9, uint param_10);
// <LegoRR.exe @00482300>
undefined4 FUN_00482300(uint * param_1, undefined4 param_2);
// <LegoRR.exe @00482390>
void FUN_00482390(Struct_34 * struct34, IDirect3DRMFrame3 * rmFrame3);
// <LegoRR.exe @00482460>
undefined FUN_00482460(Struct_34 * struct34, int param_2, uint * param_3, undefined4 param_4, undefined4 * param_5, uint * param_6, uint * param_7);
// <LegoRR.exe @004824d0>
undefined4 Res_Struct34_GetField0(Struct_34 * param_1);
// <LegoRR.exe @004824e0>
int FUN_004824e0(Struct_34 * param_1, uint param_2, int param_3, int param_4, undefined2 * param_5);
// <LegoRR.exe @00482610>
void Res_Struct34_SetTable10_Field64(Struct_34 * param_1, int index, undefined4 param_3);
// <LegoRR.exe @00482630>
undefined FUN_00482630(uint * param_1, float param_2, float param_3, float param_4);
// <LegoRR.exe @004826a0>
undefined FUN_004826a0(int param_1, int param_2, int param_3, int param_4, int param_5);
// <LegoRR.exe @00482730>
undefined FUN_00482730_internal(Struct_34 * struct34, int index, int param_3, int param_4, int out_table);
// <LegoRR.exe @004827c0>
undefined FUN_004827c0(int param_1, int param_2, int param_3, int param_4, int param_5, float * param_6, undefined4 * param_7);
// <LegoRR.exe @004828e0>
undefined FUN_004828e0(int param_1, int param_2, int param_3, int param_4, int param_5, undefined4 * param_6, undefined4 * param_7);
// <LegoRR.exe @00482980>
undefined FUN_00482980(Struct_34 * param_1, int index, int param_3, int param_4, int param_5, Vector3F * * param_6, Point2I * param_7);
// <LegoRR.exe @00482a40>
BOOL FUN_00482a40(Struct_34 * struct34, int index);
// <LegoRR.exe @00482a60>
void FUN_00482a60(Struct_34 * struct34, int index, BOOL state);
// <LegoRR.exe @00482a90>
undefined FUN_00482a90(int param_1, int param_2);
// <LegoRR.exe @00482ab0>
BOOL Res_D3DRMUserVisualCallback(IDirect3DRMUserVisual * lpD3DRMUV, Struct_34 * lpArg, D3DRMUserVisualReason lpD3DRMUVreason, IUnknown * lpD3DRMDev, IDirect3DRMViewport * lpD3DRMview);
// <LegoRR.exe @00482d80>
undefined FUN_00482d80(int param_1, undefined4 param_2, float * param_3, int param_4);
// <LegoRR.exe @00482e10>
undefined FUN_00482e10(uint param_1, float * param_2, int param_3);
// <LegoRR.exe @00482f70>
undefined FUN_00482f70(undefined4 param_1, undefined4 param_2);
// <LegoRR.exe @00482fa0>
undefined FUN_00482fa0(undefined4 param_1, undefined4 * param_2);
// <LegoRR.exe @00482ff0>
void Lego_FreeUNKPTR_STRUCT48(void);
// <LegoRR.exe @00483020>
undefined FUN_00483020(int param_1);
// <LegoRR.exe @00483130>
int * * Draw_LoadAnimFrame(char * dirname, char * filename, undefined4 out_width, undefined4 out_height);
// <LegoRR.exe @004832f0>
int FUN_004832f0(int param_1, uint count, char * param_3);
// <LegoRR.exe @00483340>
undefined FUN_00483340(int param_1, int * param_2, char * param_3, undefined4 param_4, undefined4 param_5);
// <LegoRR.exe @00483380>
undefined FUN_00483380(Struct_34 * param_1, int index, undefined * * param_3);
// <LegoRR.exe @00483400>
undefined FUN_00483400(Struct_34 * param_1, int index);
// <LegoRR.exe @00483430>
BOOL Res_Struct34_InitTable10_Item50Default(Struct_34 * param_1, int index);
// <LegoRR.exe @00483500>
BOOL FUN_00483500(Struct_34 * param_1, int index, undefined4 * param_3);
// <LegoRR.exe @00483530>
BOOL FUN_00483530(Struct_34 * param_1, int index, float r, float g, float b, int unkMode);
// <LegoRR.exe @004836c0>
int Res_Struct34_GetTable8_Struct70_Field10(Struct_34 * param_1, int index);
// <LegoRR.exe @004836e0>
BOOL FUN_004836e0(Struct_34 * param_1, int index, float unkMultiplier, int unkMode);
// <LegoRR.exe @00483800>
undefined FUN_00483800(undefined4 * param_1);
// <LegoRR.exe @00483840>
undefined4 FUN_00483840(int * param_1);
// <LegoRR.exe @004838c0>
undefined4 FUN_004838c0(int param_1);
// <LegoRR.exe @00483950>
undefined4 FUN_00483950(undefined4 param_1, float * param_2);
// <LegoRR.exe @00483ad0>
BOOL FUN_00483ad0(int param_1, undefined4 param_2);
// <LegoRR.exe @00483b70>
void Draw_UnkRenderTextureManagement__00483b70(void);
// <LegoRR.exe @00483c00>
void Draw_UnkRenderTextureManagement__00483c00(void);
// <LegoRR.exe @00483c80>
uint FUN_00483c80(uint * param_1, float * param_2, int param_3);
// <LegoRR.exe @00483d30>
undefined4 FUN_00483d30(int param_1);
// <LegoRR.exe @00483d50>
uint FUN_00483d50(undefined4 param_1, undefined4 * param_2, float * param_3, int param_4);
// <LegoRR.exe @00483dc0>
BOOL FUN_00483dc0(undefined4 param_1, int param_2, float * param_3, int param_4);
// <LegoRR.exe @00483e30>
undefined4 FUN_00483e30(void * this, int * param_1, int * param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7);
// <LegoRR.exe @00483f40>
BOOL Lego_CrashesFunc_00483f40(char * param_1, int * param_2);
// <LegoRR.exe @004841c0>
undefined4 FUN_004841c0(undefined4 * param_1);
// <LegoRR.exe @00484220>
BOOL Flic_OpenRead__00484220(char * filename, int * param_2);
// <LegoRR.exe @00484330>
uint FUN_00484330(uint * param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5);
// <LegoRR.exe @00484490>
undefined4 FUN_00484490(uint * param_1);
// <LegoRR.exe @00484520>
undefined4 FUN_00484520(uint * param_1);
// <LegoRR.exe @004845e0>
undefined4 FUN_004845e0(uint * param_1);
// <LegoRR.exe @00484770>
undefined4 FUN_00484770(undefined4 * param_1);
// <LegoRR.exe @004848d0>
undefined4 FUN_004848d0(uint param_1);
// <LegoRR.exe @004849e0>
undefined4 FUN_004849e0(undefined4 * param_1);
// <LegoRR.exe @00484a90>
undefined4 FUN_00484a90(undefined4 * param_1);
// <LegoRR.exe @00484b40>
undefined4 FUN_00484b40(int param_1);
// <LegoRR.exe @00484b90>
undefined4 FUN_00484b90(uint param_1);
// <LegoRR.exe @00484c90>
undefined4 FUN_00484c90(uint param_1);
// <LegoRR.exe @00484de0>
undefined4 FUN_00484de0(uint param_1);
// <LegoRR.exe @00484e50>
int NERPFunc__True(int * stack);
// <LegoRR.exe @00484e60>
undefined FUN_00484e60(int param_1);
// <LegoRR.exe @00484ec0>
undefined4 FUN_00484ec0(int param_1);
// <LegoRR.exe @00484f50>
void logf_removed(char * message, ...);
// <LegoRR.exe @00484f60>
undefined FUN_00484f60(uint param_1);
// <LegoRR.exe @00485110>
undefined FUN_00485110(uint param_1);
// <LegoRR.exe @004852f0>
undefined4 FUN_004852f0(uint param_1);
// <LegoRR.exe @00485380>
uint FUN_00485380(uint param_1, int param_2);
// <LegoRR.exe @004853a0>
undefined4 FUN_004853a0(int param_1);
// <LegoRR.exe @004853b0>
Struct_830 * Lego_unkMakeDrawRegion__004853b0(ImageFont * font, Rect2F * area, uint size);
// <LegoRR.exe @00485420>
undefined Draw_SetStruct830_Flag4(Struct_830 * param_1, BOOL state);
// <LegoRR.exe @00485450>
undefined FUN_00485450(undefined * param_1);
// <LegoRR.exe @00485470>
undefined FUN_00485470(void * param_1, int param_2, int param_3);
// <LegoRR.exe @00485490>
undefined FUN_00485490(void * param_1, uint param_2, uint param_3);
// <LegoRR.exe @004854d0>
undefined FUN_004854d0(int param_1, int param_2, byte * param_3);
// <LegoRR.exe @004854f0>
void Game_DisplayInfoMessage(Struct_830 * param_1, char * param_2, ...);
// <LegoRR.exe @00485510>
undefined FUN_00485510(Struct_830 * param_1, int param_2, char * format, undefined4 * args);
// <LegoRR.exe @004855c0>
undefined FUN_004855c0(int param_1, int param_2, byte * param_3);
// <LegoRR.exe @00485650>
undefined4 FUN_00485650(int * param_1, uint param_2, float param_3, int * param_4);
// <LegoRR.exe @004859d0>
undefined4 FUN_004859d0(int * param_1, float param_2, int * param_3);
// <LegoRR.exe @00485c70>
undefined FUN_00485c70(Struct_830 * param_1);
// <LegoRR.exe @00485cc0>
undefined FUN_00485cc0(int param_1, undefined4 * param_2, undefined4 * param_3);
// <LegoRR.exe @00485ce0>
void Input_Init_KeyNames(void);
// <LegoRR.exe @004860f0>
BOOL Input_ParseKey(char * keyName, byte * out_keyCode);
// <LegoRR.exe @00486140>
void Main_LockSurfaceRect(Rect2F * surfaceRect);
// <LegoRR.exe @00486160>
void Draw_SurfaceLock_Translate(Rect2F * translation);
// <LegoRR.exe @00486270>
void Draw_SurfaceLock_GetTranslation(Rect2F * translation);
// <LegoRR.exe @004862b0>
void Draw_SurfaceLock_FUN_004862b0(undefined4 param_1, undefined4 param_2, int param_3, float param_4, float param_5, float param_6, undefined4 param_7);
// <LegoRR.exe @00486350>
float10 Draw_SurfaceLock_FUN_00486350(undefined4 param_1, int param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6);
// <LegoRR.exe @004864d0>
void Draw_SurfaceLock_FUN_004864d0(undefined4 param_1, int param_2, undefined4 param_3);
// <LegoRR.exe @00486650>
float10 Draw_SurfaceLock_FUN_00486650(undefined4 param_1, undefined4 param_2, uint param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7);
// <LegoRR.exe @00486790>
uint Draw_SurfaceFloatToRGB(undefined4 red, undefined4 green, undefined4 blue);
// <LegoRR.exe @00486810>
BOOL Draw_SurfaceLock(IDirectDrawSurface4 * ddSurface, int mode);
// <LegoRR.exe @00486910>
void Draw_SurfaceUnlock(IDirectDrawSurface4 * ddSurface);
// <LegoRR.exe @00486950>
BOOL Draw_SurfaceSetPixelFunction(int mode);
// <LegoRR.exe @004869e0>
undefined Draw_SurfaceLock_FUN_004869e0(uint param_1, uint param_2, int x, int y, undefined4 nativeColor);
// <LegoRR.exe @00486b40>
void Draw_SetPixel8(int x, int y, uint color);
// <LegoRR.exe @00486b60>
void Draw_SetPixel16_Mode0(int x, int y, uint color);
// <LegoRR.exe @00486b90>
void Draw_SetPixel16_Mode1(int x, int y, uint color);
// <LegoRR.exe @00486bc0>
void Draw_SetPixel16_Mode2(int x, int y, uint color);
// <LegoRR.exe @00486c60>
void Draw_SetPixel24(int x, int y, uint color);
// <LegoRR.exe @00486c90>
void Draw_SetPixel32(int x, int y, uint color);
// <LegoRR.exe @00486cb0>
undefined4 * Res_OpenLWS(char * filename, BOOL isLooping);
// <LegoRR.exe @00487980>
undefined Main_SetSharedObjects(char * dirname, undefined4 getSfxCallback, undefined4 playOrInitCallback, undefined4 getSfxFlag1);
// <LegoRR.exe @00487a20>
void Res_CleanupSharedObjects(void);
// <LegoRR.exe @00487a90>
uint Lego_GetFieldByte2(int param_1);
// <LegoRR.exe @00487aa0>
undefined FUN_00487aa0(int param_1);
// <LegoRR.exe @00487c50>
undefined FUN_00487c50(ushort * param_1, undefined4 param_2);
// <LegoRR.exe @00487cc0>
void * Res_LoadActFrame_Struct38(void * struct38, IDirect3DRMFrame3 * rmFrame3);
// <LegoRR.exe @00487e60>
undefined FUN_00487e60(void * param_1, float param_2);
// <LegoRR.exe @00487f70>
float10 FUN_00487f70(int param_1, float param_2, short * param_3);
// <LegoRR.exe @00488010>
undefined FUN_00488010(int param_1, int param_2);
// <LegoRR.exe @004880a0>
undefined FUN_004880a0(float param_1, int param_2);
// <LegoRR.exe @00488190>
undefined4 FUN_00488190(float param_1, uint param_2);
// <LegoRR.exe @00488280>
float10 FUN_00488280(int param_1, float param_2, ushort * param_3);
// <LegoRR.exe @00488330>
undefined FUN_00488330(int param_1, int param_2, uint param_3);
// <LegoRR.exe @00488390>
undefined FUN_00488390(int param_1, int param_2);
// <LegoRR.exe @00488430>
undefined FUN_00488430(int param_1, float param_2, uint param_3, float param_4);
// <LegoRR.exe @004885a0>
undefined FUN_004885a0(int param_1, float param_2, float * param_3, float * param_4, float * param_5);
// <LegoRR.exe @00488880>
Struct_34 * FUN_00488880(int param_1, char * param_2, undefined4 rmFrame3, int param_4);
// <LegoRR.exe @004889f0>
undefined4 Res_LookupSharedObject(SharedObjectResource * table, uint count, char * resName);
// <LegoRR.exe @00488a50>
void Res_AddSharedObject(SharedObjectResource * table, int * ref_count, char * resName, Struct_34 * struct34);
// <LegoRR.exe @00488a80>
undefined FUN_00488a80(ushort * param_1, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @00488bc0>
undefined FUN_00488bc0(int param_1, char * * param_2);
// <LegoRR.exe @00488c60>
undefined FUN_00488c60(int param_1, float param_2, uint param_3);
// <LegoRR.exe @00488c90>
void Res_FreeActFrameResource_Field4_Struct38(void * struct38);
// <LegoRR.exe @00488d30>
void Res_FreeStruct38_Item_internal(void * struct38, undefined4 * item);
// <LegoRR.exe @00488e10>
BOOL InitSoundSystem(BOOL nosound);
// <LegoRR.exe @00488e50>
BOOL Main_IsSoundEnabled(void);
// <LegoRR.exe @00488e70>
undefined Music_PlayTrack(int trackIndex, int musicState, undefined4 callback);
// <LegoRR.exe @00488eb0>
BOOL Music_CDAudio_Close(void);
// <LegoRR.exe @00488ec0>
undefined Music_Update(BOOL isMusicOn);
// <LegoRR.exe @00488f30>
MMRESULT RIFF_OpenInMemory(HPSTR fileData, LONG fileSize, HMMIO * out_hmmio, HGLOBAL * out_hGlobal, LPMMCKINFO riffTag);
// <LegoRR.exe @00489130>
undefined4 RIFF_OpenStreamed(LPSTR filename);
// <LegoRR.exe @004891d0>
MMRESULT AudioPlayback_OpenMem(LPSTR filename, HMMIO * out_hmmio, HGLOBAL * out_hglobal, LPMMCKINFO mmckinfo);
// <LegoRR.exe @00489380>
undefined RIFF_SeekData(HMMIO * param_1, LPMMCKINFO param_2, MMCKINFO * param_3);
// <LegoRR.exe @004893c0>
uint RIFF_GetSetInfo(HMMIO param_1, uint param_2, int param_3, int param_4, uint * param_5);
// <LegoRR.exe @00489490>
int AudioPlayback_FreeMem(HMMIO * hMmio, HGLOBAL * hGlobal);
// <LegoRR.exe @004894d0>
BOOL Music_CDAudio_Play(int trackIndex);
// <LegoRR.exe @00489520>
BOOL Music_UpdateErrorString(void);
// <LegoRR.exe @00489540>
BOOL Music_IsTrackPlaying(int trackIndex);
// <LegoRR.exe @004895f0>
BOOL Music_CDAudio_Open(int trackIndex);
// <LegoRR.exe @004896b0>
void InitSharedFileBuffers(void);
// <LegoRR.exe @004896d0>
int File_SharedOpen__internal(uint size);
// <LegoRR.exe @00489720>
void File_SharedClose(uint sharedIndex);
// <LegoRR.exe @00489760>
void * File_SharedGetData(uint sharedIndex);
// <LegoRR.exe @00489780>
int * FUN_00489780(float param_1, float param_2, float param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7);
// <LegoRR.exe @004897e0>
ActFrameResource * Res_AllocActFrameResource_Mode0(IDirect3DRMAnimationSet2 * rmAnimSet2, IDirect3DRMFrame3 * rmFrame3, int field1c);
// <LegoRR.exe @00489880>
ActFrameResource * Res_AllocActFrameResource_Mode1(void * struct38, IDirect3DRMFrame3 * rmFrame3, undefined4 field1c);
// <LegoRR.exe @00489920>
ActFrameResource * Res_InitActFrameResource(ActFrameResource * lastActFrameRes, IDirect3DRMFrame3 * rmFrame3, undefined4 * out_param_3);
// <LegoRR.exe @00489a10>
void Res_FreeActFrameResource(ActFrameResource * actFrameRes);
// <LegoRR.exe @00489a90>
BOOL Res_GetActFrameIsLWSFile(ActFrameResource * actFrameRes);
// <LegoRR.exe @00489aa0>
void Res_SetAnimTime(ActFrameResource * actFrameRes, float time, float * opt_float);
// <LegoRR.exe @00489ba0>
BOOL Res_IncActFrameTableCount(IDirect3DRMFrame3 * rmFrame3, int * lpFramesCount);
// <LegoRR.exe @00489bb0>
BOOL Res_AddToActFrameTable(IDirect3DRMFrame3 * rmFrame3, ActFrameResource * actFrameRes);
// <LegoRR.exe @00489bd0>
BOOL FUN_00489bd0(IDirect3DRMFrame3 * rmFrame3, undefined4 param_2, undefined * param_3, undefined4 param_4);
// <LegoRR.exe @00489cb0>
undefined FUN_00489cb0(IDirect3DRMFrame3 * rmFrame3, int * param_2, BOOL param_3);
// <LegoRR.exe @00489df0>
void FUN_00489df0(IDirect3DRMFrame3 * rmFrame3, undefined4 param_2);
// <LegoRR.exe @00489e80>
void FUN_00489e80(IDirect3DRMFrame3 * rmFrame3, undefined4 param_2);
// <LegoRR.exe @00489ef0>
void * Image_LoadBMP__internal(BITMAP_FILE_INFO_STRUCT * bmpData, uint length, D3DRMIMAGE * d3drmImage);
// <LegoRR.exe @0048a030>
undefined BMP_free(D3DRMIMAGE * d3dImage);
// <LegoRR.exe @0048a050>
void DirectX_FormatError(char * name, char * description);
// <LegoRR.exe @0048a090>
uint D3DError(HRESULT result, int moduleIndex, undefined4 sourceFile, undefined4 lineNumber);
// <LegoRR.exe @0048b520>
void Scan_Init(void);
// <LegoRR.exe @0048b540>
void Scan_SetIsFullScreen(BOOL isFullScreen);
// <LegoRR.exe @0048b550>
void Scan_Cleanup(void);
// <LegoRR.exe @0048b5b0>
void Scan_WriteDataDirList(void);
// <LegoRR.exe @0048b5f0>
char * Reg_SplitRootKey(char * fullKey, char * out_rootKey);
// <LegoRR.exe @0048b620>
BOOL Reg_QueryValue_OnLocalMachine(char * regSubKey, char * regValueName, RegistryType valueType, char * out_buffer, uint bufferSize);
// <LegoRR.exe @0048b650>
BOOL Reg_QueryValue(HKEY hKey, char * subKey, char * valueName, RegistryType valueType, char * out_buffer, uint bufferSize);
// <LegoRR.exe @0048b760>
BOOL freadstr(FILE * file, char * out_str);
// <LegoRR.exe @0048b7a0>
int WAD_Open__internal(undefined4 filename);
// <LegoRR.exe @0048bfa0>
WADFile * WAD_Get(int index);
// <LegoRR.exe @0048bfb0>
uint WAD_GetEntrySize(int wadIndex, int entryIndex);
// <LegoRR.exe @0048bfd0>
undefined4 WAD_GetEntryPackedSize(int wadIndex, int entryIndex);
// <LegoRR.exe @0048bff0>
int WAD_Shared__Next(void);
// <LegoRR.exe @0048c010>
int WAD_FindEntry(char * filename, int opt_wadIndex);
// <LegoRR.exe @0048c060>
int WAD_FindEntry__InWAD(char * filename, int wadIndex);
// <LegoRR.exe @0048c0c0>
int WAD__Next(void);
// <LegoRR.exe @0048c100>
int WAD_SharedOpen__InWAD(char * filename, int in_wadIndex);
// <LegoRR.exe @0048c230>
int WAD_SharedOpen(char * filename, int opt_wadIndex);
// <LegoRR.exe @0048c280>
void WAD_Shared__Dispose(int sharedIndex);
// <LegoRR.exe @0048c2b0>
undefined4 WAD_SharedGetData__internal(int sharedIndex);
// <LegoRR.exe @0048c2d0>
uint WAD_SharedGetSize(int sharedIndex);
// <LegoRR.exe @0048c2f0>
byte * WAD_SharedGetData(int sharedIndex);
// <LegoRR.exe @0048c300>
char * FUN_0048c300(char * param_1, char * param_2, uint * param_3, size_t * param_4);
// <LegoRR.exe @0048c380>
undefined4 * FUN_0048c380(char * param_1);
// <LegoRR.exe @0048c3e0>
uint FUN_0048c3e0(char * param_1);
// <LegoRR.exe @0048c440>
undefined FUN_0048c440(undefined4 * param_1, int param_2);
// <LegoRR.exe @0048c490>
undefined4 FUN_0048c490(int * param_1, undefined * param_2);
// <LegoRR.exe @0048c4d0>
undefined4 FUN_0048c4d0(undefined4 * param_1, int * param_2, uint param_3, uint * * param_4, int param_5);
// <LegoRR.exe @0048c620>
undefined4 FUN_0048c620(undefined4 * param_1, uint param_2);
// <LegoRR.exe @0048c6a0>
undefined4 FUN_0048c6a0(undefined4 * param_1, int param_2, uint * * param_3, uint param_4, int param_5);
// <LegoRR.exe @0048c950>
undefined4 FUN_0048c950(undefined4 * param_1, undefined4 param_2, int * * param_3, uint param_4, int * param_5, int param_6);
// <LegoRR.exe @0048cae0>
undefined4 FUN_0048cae0(undefined4 * param_1, int param_2, undefined4 * param_3, uint param_4, int param_5);
// <LegoRR.exe @0048d580>
undefined4 FUN_0048d580(undefined4 param_1, int * param_2, uint * * param_3, uint * * param_4, int * param_5, undefined4 * param_6, int param_7);
// <LegoRR.exe @0048da80>
BOOL Res_Unk_CreateMeshStruct20(char * filename, int * out_struct20, int param_3);
// <LegoRR.exe @0048db30>
undefined4 FUN_0048db30(undefined4 * param_1);
// <LegoRR.exe @0048dbe0>
void __fpmath(int param_1);
// <LegoRR.exe @0048dc00>
undefined FUN_0048dc00(void);
// <LegoRR.exe @0048dc40>
float10 atof(char * text);
// <LegoRR.exe @0048dca0>
int sprintf(char * out_buffer, char * format, ...);
// <LegoRR.exe @0048dd10>
char * strstr(char * str, char * strSearch);
// <LegoRR.exe @0048dd90>
int __atoi_internal(byte * text);
// <LegoRR.exe @0048de30>
int atoi(char * text);
// <LegoRR.exe @0048de40>
void free(void * buffer);
// <LegoRR.exe @0048de90>
void * malloc(uint length);
// <LegoRR.exe @0048deb0>
void * __malloc_internal(uint length, BOOL retry);
// <LegoRR.exe @0048df00>
void * FUN_0048df00(uint length);
// <LegoRR.exe @0048df40>
int * FUN_0048df40(LwoFrame * param_1, uint param_2);
// <LegoRR.exe @0048e0e0>
void qsort(void * base, uint number, uint width, CompareCallback * compare);
// <LegoRR.exe @0048e290>
void __qsort(byte * a, byte * b, uint width, CompareCallback * compare);
// <LegoRR.exe @0048e2f0>
void __memswap(byte * a, byte * b, uint count);
// <LegoRR.exe @0048e320>
longlong __ftol(float10 param_1);
// <LegoRR.exe @0048e350>
undefined FUN_0048e350();
// <LegoRR.exe @0048e36d>
undefined FUN_0048e36d(undefined4 param_1, undefined4 param_2);
// <LegoRR.exe @0048e420>
undefined randomSeed(uint seed);
// <LegoRR.exe @0048e430>
short randomInt16(void);
// <LegoRR.exe @0048e46a>
undefined FUN_0048e46a(void);
// <LegoRR.exe @0048e4a0>
int vsprintf(char * param_1, char * param_2, ...);
// <LegoRR.exe @0048e510>
void * _alloca4k(uint size);
// <LegoRR.exe @0048e540>
float10 FUN_0048e540(uint param_1, uint param_2);
// <LegoRR.exe @0048e640>
int toupper(int c);
// <LegoRR.exe @0048e740>
void FUN_0048e740(void);
// <LegoRR.exe @0048e770>
undefined exit(int status);
// <LegoRR.exe @0048e790>
void quick_exit(int _Code);
// <LegoRR.exe @0048e7b0>
undefined FUN_0048e7b0(UINT param_1, int param_2, int param_3);
// <LegoRR.exe @0048e860>
undefined FUN_0048e860(undefined * * param_1, undefined * * param_2);
// <LegoRR.exe @0048e894>
undefined FUN_0048e894(undefined4 param_1, undefined4 param_2);
// <LegoRR.exe @0048e940>
float10 FUN_0048e940(uint param_1, uint param_2);
// <LegoRR.exe @0048ea30>
char * _strncpy(char * _Dest, char * _Source, size_t _Count);
// <LegoRR.exe @0048eb30>
uint FUN_0048eb30(undefined4 param_1, undefined8 param_2);
// <LegoRR.exe @0048eb50>
void sscanf(char * buffer, char * format, ...);
// <LegoRR.exe @0048eba0>
float10 FUN_0048eba0(uint param_1, uint param_2);
// <LegoRR.exe @0048eca0>
undefined8 __alldiv(uint param_1, uint param_2, uint param_3, uint param_4);
// <LegoRR.exe @0048ed50>
ulonglong __allmul(uint param_1, uint param_2, uint param_3, uint param_4);
// <LegoRR.exe @0048ed90>
void * Avi__malloc_inernal(uint param_1);
// <LegoRR.exe @0048eda0>
undefined4 fclose(FILE * file);
// <LegoRR.exe @0048ee20>
FILE * _fsopen(LPCSTR filename, char * mode, int shflag);
// <LegoRR.exe @0048ee50>
FILE * fopen(LPCSTR filename, char * mode);
// <LegoRR.exe @0048ee70>
undefined FUN_0048ee70(undefined * UNRECOVERED_JUMPTABLE);
// <LegoRR.exe @0048eeb0>
undefined FUN_0048eeb0(undefined4 param_1, undefined * UNRECOVERED_JUMPTABLE);
// <LegoRR.exe @0048eec0>
undefined FUN_0048eec0(PVOID param_1, PEXCEPTION_RECORD param_2);
// <LegoRR.exe @0048ef20>
undefined FUN_0048ef20(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4);
// <LegoRR.exe @0048ef60>
undefined4 FUN_0048ef60(undefined4 param_1, undefined4 param_2, undefined4 param_3, int param_4, int param_5);
// <LegoRR.exe @0048efc0>
undefined FUN_0048efc0(PEXCEPTION_RECORD param_1, PVOID param_2, undefined4 param_3);
// <LegoRR.exe @0048eff0>
undefined4 FUN_0048eff0(undefined4 * param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7);
// <LegoRR.exe @0048f0c0>
undefined4 FUN_0048f0c0(PEXCEPTION_RECORD param_1, PVOID param_2, undefined4 param_3);
// <LegoRR.exe @0048f150>
int FUN_0048f150(int param_1, int param_2, int param_3, uint * param_4, uint * param_5);
// <LegoRR.exe @0048f1d0>
undefined __global_unwind2(PVOID param_1);
// <LegoRR.exe @0048f212>
undefined __local_unwind2(int param_1, int param_2);
// <LegoRR.exe @0048f27a>
int __abnormal_termination(void);
// <LegoRR.exe @0048f29d>
undefined __NLG_Notify1();
// <LegoRR.exe @0048f2a6>
void __NLG_Notify(ulong param_1);
// <LegoRR.exe @0048f2c0>
undefined entry(void);
// <LegoRR.exe @0048f460>
void __amsg_exit(int param_1);
// <LegoRR.exe @0048f490>
uint _unk_FUN_0048f490(uint c, uint charMask);
// <LegoRR.exe @0048f530>
int strncmp(char * _Str1, char * _Str2, size_t _MaxCount);
// <LegoRR.exe @0048f570>
int ftell(FILE * file);
// <LegoRR.exe @0048f720>
int fseek(FILE * file, int offset, int origin);
// <LegoRR.exe @0048f7c0>
uint fwrite(void * out_buffer, uint size, int count, FILE * in_file);
// <LegoRR.exe @0048f910>
int remove(LPCSTR filename);
// <LegoRR.exe @0048f940>
int _chmod(LPCSTR filename, int pmode);
// <LegoRR.exe @0048f990>
int _mkdir(LPCSTR dirname);
// <LegoRR.exe @0048f9c0>
HANDLE _findfirst(LPCSTR filename, _finddata32_t * fileinfo);
// <LegoRR.exe @0048faf0>
int _findnext(HANDLE handle, _finddata32_t * fileinfo);
// <LegoRR.exe @0048fc10>
int _findclose(HANDLE handle);
// <LegoRR.exe @0048fc30>
int __unk_ftime__0048fc30(FILETIME * param_1);
// <LegoRR.exe @0048fcc0>
char * _getcwd(char * out_buffer, int maxlen);
// <LegoRR.exe @0048fce0>
char * _getdcwd(int drive, char * out_buffer, int maxlen);
// <LegoRR.exe @0048fe10>
BOOL __dcwd_exists(int drive);
// <LegoRR.exe @0048fe50>
uint _fread(byte * out_buffer, uint size, uint count, FILE * file);
// <LegoRR.exe @0048ff90>
int FUN_0048ff90(FILE * param_1);
// <LegoRR.exe @0048ffe0>
int __fflush__0048ffe0(FILE * file);
// <LegoRR.exe @00490050>
undefined FUN_00490050(void);
// <LegoRR.exe @00490060>
int FUN_00490060(int param_1);
// <LegoRR.exe @004900e0>
int fgetc(FILE * file);
// <LegoRR.exe @00490110>
char * fgets(char * str, int numChars, FILE * stream);
// <LegoRR.exe @00490190>
int FUN_00490190(char * * param_1, byte * param_2, undefined4 * param_3);
// <LegoRR.exe @004901d0>
int _stricmp(char * _Str1, char * _Str2);
// <LegoRR.exe @00490260>
char * _fullpath(char * out_absPath, LPCSTR relPath, uint maxLength);
// <LegoRR.exe @00490330>
int fscanf(FILE * file, char * format, ...);
// <LegoRR.exe @00490350>
undefined FUN_00490350(char * param_1, undefined4 * param_2, undefined4 * param_3, undefined4 * param_4, undefined4 * param_5);
// <LegoRR.exe @004904d0>
undefined __setdefaultprecision(void);
// <LegoRR.exe @004904f0>
undefined4 FUN_004904f0(void);
// <LegoRR.exe @00490540>
undefined FUN_00490540(void);
// <LegoRR.exe @00490570>
undefined FUN_00490570(char * param_1);
// <LegoRR.exe @004905d0>
undefined FUN_004905d0(char * param_1);
// <LegoRR.exe @00490640>
undefined4 FUN_00490640(double * param_1);
// <LegoRR.exe @00490660>
undefined FUN_00490660(int param_1, byte * * param_2, byte * param_3);
// <LegoRR.exe @004906c0>
undefined * FUN_004906c0(undefined4 param_1, undefined * param_2, int param_3, int param_4);
// <LegoRR.exe @00490800>
undefined4 * FUN_00490800(undefined4 param_1, undefined4 * param_2, uint param_3);
// <LegoRR.exe @00490900>
undefined FUN_00490900(undefined4 param_1, undefined4 * param_2, uint param_3, int param_4);
// <LegoRR.exe @004909b0>
undefined FUN_004909b0(undefined4 param_1, undefined * param_2, int param_3, int param_4);
// <LegoRR.exe @004909e0>
undefined FUN_004909e0(undefined4 param_1, undefined4 * param_2, uint param_3);
// <LegoRR.exe @00490a80>
undefined FUN_00490a80(undefined4 * param_1, int param_2);
// <LegoRR.exe @00490ab0>
undefined * FUN_00490ab0(byte * param_1);
// <LegoRR.exe @00490b60>
uint FUN_00490b60(uint param_1, char * * param_2);
// <LegoRR.exe @00490c90>
int _sprintf_internal_2__00490c90(char * * param_1, char * param_2, char * param_3, ...);
// <LegoRR.exe @00491620>
undefined FUN_00491620(uint param_1, char * * param_2, int * param_3);
// <LegoRR.exe @00491670>
undefined FUN_00491670(uint param_1, int param_2, char * * param_3, int * param_4);
// <LegoRR.exe @004916b0>
undefined FUN_004916b0(char * param_1, int param_2, char * * param_3, int * param_4);
// <LegoRR.exe @004916f0>
undefined4 FUN_004916f0(int * param_1);
// <LegoRR.exe @00491710>
undefined8 FUN_00491710(int * param_1);
// <LegoRR.exe @00491730>
uint FUN_00491730(ushort * * param_1);
// <LegoRR.exe @00491760>
uint * FUN_00491760(uint * param_1, char param_2);
// <LegoRR.exe @00491820>
undefined4 FUN_00491820(void);
// <LegoRR.exe @00491860>
undefined * * FUN_00491860(void);
// <LegoRR.exe @004919d0>
undefined FUN_004919d0(undefined * * param_1);
// <LegoRR.exe @00491a30>
undefined FUN_00491a30(int param_1);
// <LegoRR.exe @00491b00>
int FUN_00491b00(undefined * param_1, int * * param_2, uint * param_3);
// <LegoRR.exe @00491b60>
undefined FUN_00491b60(int param_1, int param_2, byte * param_3);
// <LegoRR.exe @00491bc0>
int * FUN_00491bc0(int * param_1);
// <LegoRR.exe @00491e00>
int FUN_00491e00(int * * param_1, int * param_2, int * param_3);
// <LegoRR.exe @00491f80>
undefined4 FUN_00491f80(int param_1, int * * param_2, int * * param_3, uint param_4);
// <LegoRR.exe @00492050>
BOOL FUN_00492050(uint length);
// <LegoRR.exe @00492070>
undefined __trandisp1();
// <LegoRR.exe @004920d7>
undefined __trandisp2();
// <LegoRR.exe @00492240>
undefined FUN_00492240(undefined param_1, undefined param_2, undefined param_3, undefined param_4, undefined4 param_5, undefined4 param_6);
// <LegoRR.exe @00492257>
undefined __startOneArgErrorHandling(undefined2 param_1, undefined param_2, undefined4 param_3, undefined4 param_4);
// <LegoRR.exe @004922b5>
undefined FUN_004922b5(undefined4 param_1);
// <LegoRR.exe @004922cc>
undefined FUN_004922cc();
// <LegoRR.exe @004922e5>
uint __fload_withFB(undefined4 param_1, int param_2);
// <LegoRR.exe @00492328>
uint FUN_00492328(undefined4 param_1, uint param_2);
// <LegoRR.exe @00492430>
undefined __cintrindisp2(void);
// <LegoRR.exe @0049246e>
undefined __cintrindisp1(void);
// <LegoRR.exe @004924a4>
undefined __ctrandisp2(uint param_1, int param_2, uint param_3, int param_4);
// <LegoRR.exe @004924de>
undefined FUN_004924de();
// <LegoRR.exe @004924e5>
undefined FUN_004924e5();
// <LegoRR.exe @00492615>
undefined __ctrandisp1(uint param_1, int param_2);
// <LegoRR.exe @00492641>
float10 __fload(uint param_1, int param_2);
// <LegoRR.exe @00492e86>
undefined FUN_00492e86(undefined1[12] param_1, undefined1[10] param_2, undefined1[12] param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6);
// <LegoRR.exe @0049308c>
undefined FUN_0049308c();
// <LegoRR.exe @00493410>
float10 FUN_00493410(double param_1);
// <LegoRR.exe @00493430>
float10 __unk_math__00493430(int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4);
// <LegoRR.exe @00493480>
float10 FUN_00493480(uint param_1, uint param_2, uint param_3, undefined4 param_4, uint param_5, undefined4 param_6, uint param_7);
// <LegoRR.exe @00493540>
undefined FUN_00493540(uint * param_1, uint * param_2, byte param_3, uint param_4, uint * param_5, uint * param_6);
// <LegoRR.exe @00493880>
uint FUN_00493880(uint param_1, double * param_2, uint param_3);
// <LegoRR.exe @00493bb0>
float10 __unk_math__00493bb0(int param_1, int param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8, undefined4 param_9);
// <LegoRR.exe @00493c60>
undefined FUN_00493c60(int param_1);
// <LegoRR.exe @00493c90>
undefined * FUN_00493c90(int param_1);
// <LegoRR.exe @00493cc0>
int FUN_00493cc0(uint param_1);
// <LegoRR.exe @00493d00>
float10 FUN_00493d00(undefined4 param_1, undefined4 param_2, short param_3);
// <LegoRR.exe @00493d40>
undefined4 FUN_00493d40(int param_1, uint param_2);
// <LegoRR.exe @00493da0>
float10 FUN_00493da0(uint param_1, uint param_2, int * param_3);
// <LegoRR.exe @00493ea0>
undefined FUN_00493ea0();
// <LegoRR.exe @00493eb0>
undefined FUN_00493eb0();
// <LegoRR.exe @00493ed0>
undefined __unk_math__00493ed0(undefined4 param_1, undefined4 param_2);
// <LegoRR.exe @00493f00>
undefined FUN_00493f00(undefined4 param_1);
// <LegoRR.exe @00493f60>
int FUN_00493f60(LCID param_1, uint param_2, char * param_3, LPCWSTR param_4, LPWSTR param_5, int param_6, UINT param_7);
// <LegoRR.exe @00494180>
char * FUN_00494180(char * param_1, int param_2);
// <LegoRR.exe @004941b0>
int vfscanf(FILE * file, char * format, int * * argptr);
// <LegoRR.exe @00494ef0>
uint FUN_00494ef0(uint param_1);
// <LegoRR.exe @00494f30>
uint FUN_00494f30(byte * * param_1);
// <LegoRR.exe @00494f60>
undefined FUN_00494f60(uint param_1, char * * param_2);
// <LegoRR.exe @00494f80>
uint FUN_00494f80(int * param_1, byte * * param_2);
// <LegoRR.exe @00494fd0>
undefined4 __fdclose__00494fd0(uint fd);
// <LegoRR.exe @004950b0>
undefined __ffree__004950b0(FILE * file);
// <LegoRR.exe @004950f0>
undefined4 * __fsopen_FUN_004950f0(LPCSTR filename, char * mode, uint shflag, undefined4 * param_4);
// <LegoRR.exe @004952c0>
undefined4 * __unk__004952c0(void);
// <LegoRR.exe @00495350>
undefined4 FUN_00495350(PEXCEPTION_RECORD param_1, PVOID param_2, undefined4 param_3, undefined4 param_4, int * param_5, PVOID param_6, PVOID param_7, undefined4 param_8);
// <LegoRR.exe @00495420>
undefined FUN_00495420(PEXCEPTION_RECORD param_1, PVOID param_2, undefined4 param_3, undefined4 param_4, int param_5, char param_6, PVOID param_7, PVOID param_8);
// <LegoRR.exe @004956d0>
undefined FUN_004956d0(PEXCEPTION_RECORD param_1, PVOID param_2, undefined4 param_3, undefined4 param_4, int param_5, int param_6, PVOID param_7, PVOID param_8);
// <LegoRR.exe @004957a0>
undefined FUN_004957a0(int param_1, undefined4 param_2, int param_3, int param_4);
// <LegoRR.exe @00495860>
undefined4 FUN_00495860(int * * param_1);
// <LegoRR.exe @00495880>
undefined FUN_00495880(PEXCEPTION_RECORD param_1, PVOID param_2, undefined4 param_3, undefined4 param_4, int param_5, byte * param_6, byte * param_7, int * param_8, int param_9, PVOID param_10);
// <LegoRR.exe @00495910>
undefined4 FUN_00495910(undefined4 param_1, int param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, int param_6, int param_7);
// <LegoRR.exe @004959fa>
undefined FUN_004959fa(void);
// <LegoRR.exe @00495a60>
undefined4 FUN_00495a60(int * * param_1);
// <LegoRR.exe @00495a90>
undefined FUN_00495a90(int param_1, int param_2, byte * param_3, byte * param_4);
// <LegoRR.exe @00495ca0>
undefined FUN_00495ca0(int param_1);
// <LegoRR.exe @00495d20>
int FUN_00495d20(int param_1, int * param_2);
// <LegoRR.exe @00495d50>
undefined __CallSettingFrame@12(undefined4 param_1, undefined4 param_2, int param_3);
// <LegoRR.exe @00495da0>
undefined FUN_00495da0(void);
// <LegoRR.exe @00495e0e>
undefined FUN_00495e0e(void);
// <LegoRR.exe @00495e30>
undefined FUN_00495e30(void);
// <LegoRR.exe @00495e9e>
undefined FUN_00495e9e(void);
// <LegoRR.exe @00496050>
undefined FUN_00496050(uint param_1);
// <LegoRR.exe @00496070>
undefined4 FUN_00496070(uint param_1, uint param_2, byte param_3);
// <LegoRR.exe @004960b0>
undefined FUN_004960b0(void);
// <LegoRR.exe @004961a0>
undefined FUN_004961a0(void);
// <LegoRR.exe @00496240>
undefined FUN_00496240(byte * param_1, byte * * param_2, byte * param_3, int * param_4, int * param_5);
// <LegoRR.exe @00496450>
LPSTR GetEnvironmentStringsA(void);
// <LegoRR.exe @004965b0>
undefined4 FUN_004965b0(int param_1);
// <LegoRR.exe @004967a0>
UINT FUN_004967a0(int param_1);
// <LegoRR.exe @004967f0>
undefined4 FUN_004967f0(undefined4 param_1);
// <LegoRR.exe @00496850>
undefined FUN_00496850(void);
// <LegoRR.exe @00496880>
undefined FUN_00496880(void);
// <LegoRR.exe @00496890>
undefined FUN_00496890(void);
// <LegoRR.exe @00496b55>
undefined FUN_00496b55(int param_1);
// <LegoRR.exe @00496b70>
undefined FUN_00496b70(void);
// <LegoRR.exe @00496bb0>
undefined FUN_00496bb0(int param_1);
// <LegoRR.exe @00496d90>
LCID _unk_FUN_00496d90(DWORD param_1, LPCSTR param_2, int param_3, LPWORD param_4, UINT param_5, LCID param_6);
// <LegoRR.exe @00496ec0>
DWORD FUN_00496ec0(uint param_1, LONG param_2, DWORD param_3);
// <LegoRR.exe @00496f80>
int __fdwrite__00496f80(uint param_1, char * param_2, char * param_3);
// <LegoRR.exe @004971a0>
undefined __set_doserrno(uint error_value);
// <LegoRR.exe @00497210>
int FUN_00497210(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
// <LegoRR.exe @00497300>
uint __fread_internal__00497300(FILE * file);
// <LegoRR.exe @004973f0>
char * FUN_004973f0(uint param_1, char * param_2, DWORD param_3);
// <LegoRR.exe @00497650>
undefined4 FUN_00497650(uint param_1);
// <LegoRR.exe @004976b0>
undefined FUN_004976b0(void);
// <LegoRR.exe @00497770>
uint FUN_00497770(void);
// <LegoRR.exe @00497790>
undefined4 FUN_00497790(undefined4 * param_1);
// <LegoRR.exe @00497830>
undefined FUN_00497830(int param_1, int * param_2);
// <LegoRR.exe @00497890>
uint FUN_00497890(uint param_1);
// <LegoRR.exe @00497990>
undefined4 * FUN_00497990(undefined4 * param_1, byte * param_2, uint param_3);
// <LegoRR.exe @00497a30>
undefined FUN_00497a30(undefined4 param_1, undefined4 param_2);
// <LegoRR.exe @00497a70>
undefined FUN_00497a70(undefined4 param_1, uint param_2);
// <LegoRR.exe @00497a90>
uint FUN_00497a90(uint param_1);
// <LegoRR.exe @00497b30>
uint FUN_00497b30(uint param_1);
// <LegoRR.exe @00497bc0>
undefined4 FUN_00497bc0(int param_1, int param_2);
// <LegoRR.exe @00497c30>
undefined FUN_00497c30(int param_1, int param_2);
// <LegoRR.exe @00497ca0>
undefined4 FUN_00497ca0(int param_1, int param_2);
// <LegoRR.exe @00497d40>
undefined FUN_00497d40(int param_1, undefined4 * param_2);
// <LegoRR.exe @00497d60>
undefined FUN_00497d60(undefined4 * param_1);
// <LegoRR.exe @00497d70>
undefined4 FUN_00497d70(int * param_1);
// <LegoRR.exe @00497d90>
undefined FUN_00497d90(uint * param_1, int param_2);
// <LegoRR.exe @00497e50>
undefined4 FUN_00497e50(ushort * param_1, uint * param_2, int * param_3);
// <LegoRR.exe @00498020>
undefined FUN_00498020(ushort * param_1, uint * param_2);
// <LegoRR.exe @00498040>
undefined FUN_00498040(ushort * param_1, uint * param_2);
// <LegoRR.exe @00498060>
undefined FUN_00498060(uint * param_1, byte * param_2);
// <LegoRR.exe @004980a0>
undefined FUN_004980a0(uint * param_1, byte * param_2);
// <LegoRR.exe @004980e0>
undefined FUN_004980e0(undefined4 * param_1, int param_2, int param_3);
// <LegoRR.exe @00498180>
undefined * FUN_00498180(undefined1 param_1);
// <LegoRR.exe @00498200>
undefined FUN_00498200(uint * param_1, uint * param_2);
// <LegoRR.exe @004982c0>
undefined4 * FUN_004982c0(undefined4 * param_1, undefined4 * param_2, uint param_3);
// <LegoRR.exe @00498600>
undefined FUN_00498600(void);
// <LegoRR.exe @00498610>
undefined4 FUN_00498610(ushort * param_1, byte * * param_2, byte * param_3, int param_4, int param_5, int param_6, int param_7);
// <LegoRR.exe @00498da0>
undefined FUN_00498da0(int * param_1);
// <LegoRR.exe @00498e00>
uint FUN_00498e00(uint param_1);
// <LegoRR.exe @00498e30>
LPSTR FUN_00498e30(LPSTR param_1, ushort param_2);
// <LegoRR.exe @00498eb0>
undefined8 __aulldiv(uint param_1, uint param_2, uint param_3, uint param_4);
// <LegoRR.exe @00498f20>
undefined8 __aullrem(uint param_1, uint param_2, uint param_3, uint param_4);
// <LegoRR.exe @00498fa0>
undefined __unk__00498fa0(uint param_1, int * param_2, ushort * param_3);
// <LegoRR.exe @004990c0>
uint FUN_004990c0(ushort * param_1, byte * param_2, uint param_3);
// <LegoRR.exe @004991c0>
uint FUN_004991c0(uint param_1);
// <LegoRR.exe @004991f0>
undefined __allshl();
// <LegoRR.exe @00499210>
uint FUN_00499210(uint param_1, char * * param_2);
// <LegoRR.exe @004992a0>
int FUN_004992a0(void);
// <LegoRR.exe @00499360>
undefined4 FUN_00499360(uint param_1, HANDLE param_2);
// <LegoRR.exe @00499410>
undefined4 FUN_00499410(uint param_1);
// <LegoRR.exe @004994b0>
undefined4 FUN_004994b0(uint param_1);
// <LegoRR.exe @00499500>
uint FUN_00499500(LPCSTR param_1, uint param_2, uint param_3, undefined4 param_4);
// <LegoRR.exe @00499920>
undefined FUN_00499920(void);
// <LegoRR.exe @00499940>
undefined FUN_00499940(void);
// <LegoRR.exe @00499950>
uint FUN_00499950(void * param_1, UINT_PTR param_2);
// <LegoRR.exe @00499970>
uint FUN_00499970(LPVOID param_1, UINT_PTR param_2);
// <LegoRR.exe @00499990>
uint FUN_00499990(FARPROC param_1);
// <LegoRR.exe @004999b0>
void _abort(void);
// <LegoRR.exe @004999d0>
int FUN_004999d0(short * param_1);
// <LegoRR.exe @004999f0>
int FUN_004999f0(undefined4 param_1, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @00499a80>
int * FUN_00499a80(int param_1, int param_2);
// <LegoRR.exe @00499b20>
undefined FUN_00499b20(void);
// <LegoRR.exe @00499b40>
undefined FUN_00499b40(void);
// <LegoRR.exe @00499df0>
uint FUN_00499df0(int * param_1);
// <LegoRR.exe @0049a060>
undefined FUN_0049a060(int param_1, int param_2, uint param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10, int param_11);
// <LegoRR.exe @0049a270>
undefined4 FUN_0049a270(uint param_1, uint param_2, uint * param_3);
// <LegoRR.exe @0049a2a0>
undefined FUN_0049a2a0(uint * param_1, uint * param_2);
// <LegoRR.exe @0049a310>
undefined FUN_0049a310(uint * param_1);
// <LegoRR.exe @0049a340>
undefined FUN_0049a340(uint * param_1);
// <LegoRR.exe @0049a370>
undefined FUN_0049a370(char * param_1, int param_2, uint * param_3);
// <LegoRR.exe @0049a470>
undefined4 FUN_0049a470(uint param_1, uint param_2, uint param_3, int param_4, byte param_5, short * param_6);
// <LegoRR.exe @0049a800>
undefined FUN_0049a800(int * param_1, int * param_2);
// <LegoRR.exe @0049aac0>
undefined FUN_0049aac0(int * param_1, uint param_2, int param_3);
// <LegoRR.exe @0049ab50>
int FUN_0049ab50(undefined1 param_1);
// <LegoRR.exe @0049acd0>
undefined4 FUN_0049acd0(int param_1);
// <LegoRR.exe @0049ae50>
undefined * FUN_0049ae50(int param_1);
// <LegoRR.exe @0049aea0>
uint FUN_0049aea0(LPSTR param_1, ushort * param_2, uint param_3);
// <LegoRR.exe @0049b090>
int FUN_0049b090(short * param_1, int param_2);
// <LegoRR.exe @0049b0d0>
byte * FUN_0049b0d0(byte * param_1);
// <LegoRR.exe @0049b160>
int FUN_0049b160(uint param_1, int param_2);
// <LegoRR.exe @0049b1e0>
LPWSTR FUN_0049b1e0(byte * param_1, byte * param_2, LPWSTR param_3);
// <LegoRR.exe @0049b220>
LPCWSTR FUN_0049b220(void);
// <LegoRR.exe @0049b2a0>
int FUN_0049b2a0(LCID param_1, DWORD param_2, byte * param_3, LPWSTR param_4, byte * param_5, char * param_6, UINT param_7);
// <LegoRR.exe @0049b570>
undefined4 FUN_0049b570(uint * param_1, int param_2);
// <LegoRR.exe @0049b780>
int FUN_0049b780(byte * param_1, LPWSTR param_2);
// <LegoRR.exe @0049b800>
undefined4 * FUN_0049b800(char * * param_1);
// <LegoRR.exe @0049b870>
uint * FUN_0049b870(uint * param_1, uint param_2);
// <LegoRR.exe @0049b920>
undefined4 * FUN_0049b920(char * param_1);
// <LegoRR.exe @0049b970>
HRESULT Direct3DRMCreate(IUnknown * * lplpIDirect3DRM);
// <LegoRR.exe @0049b976>
Vector3F * D3DRMVectorRandom(Vector3F * d);
// <LegoRR.exe @0049b97c>
Vector3F * D3DRMVectorRotate(Vector3F * r, Vector3F * v, Vector3F * axis, float theta);
// <LegoRR.exe @0049b982>
HRESULT DirectDrawEnumerateA(DDENUMCALLBACKA * lpCallback, LPVOID lpContext);
// <LegoRR.exe @0049b988>
HRESULT DirectDrawCreate(LPGUID lpGUID, IUnknown * * lplpIDirectDraw, LPUNKNOWN pUnkOuter);
// <LegoRR.exe @0049b98e>
HRESULT AVIStreamInfoA(IUnknown * pIAVIStream, void * pAVIStreamInfoA, LONG lSize);
// <LegoRR.exe @0049b994>
IUnknown * AVIStreamGetFrameOpen(IUnknown * pIAVIStream, BITMAPINFOHEADER * lpbiWanted);
// <LegoRR.exe @0049b99a>
HRESULT AVIStreamOpenFromFileA(IUnknown * * lplpIAVIStream, LPCSTR szFile, DWORD fccType, LONG lParam, UINT mode, CLSID * pclsidHandler);
// <LegoRR.exe @0049b9a0>
ULONG AVIStreamRelease(IUnknown * pIAVIStream);
// <LegoRR.exe @0049b9a6>
LPVOID AVIStreamGetFrame(IUnknown * pIGetFrame, LONG lPos);
// <LegoRR.exe @0049ca68>
HRESULT DirectInputCreateA(HINSTANCE hInst, DWORD dwVersion, IUnknown * * lplpIDirectInput, IUnknown * pUnkOuter);
// <LegoRR.exe @0049ca6e>
HRESULT DirectSoundCreate(LPGUID lpGuid, IDirectSound * * lplpIDirectSound, IUnknown * pUnkOuter);
// <LegoRR.exe @0049ca74>
void RtlUnwind(PVOID TargetFrame, PVOID TargetIp, PEXCEPTION_RECORD ExceptionRecord, PVOID ReturnValue);
// <LegoRR.exe @0049ca80>
uint Rnc_Decompress(byte * srcBuffer, byte * * out_dstBuffer);
// <LegoRR.exe @0049cb00>
short Rnc_Decompress__internal(byte * srcBuffer, byte * dstBuffer);
// <LegoRR.exe @0049cba0>
short Rnc_Decompress_Method1(byte * srcBuffer, byte * dstBuffer);
// <LegoRR.exe @0049cd20>
short Rnc_Decompress_Method2(byte * srcBuffer, byte * dstBuffer);
// <LegoRR.exe @0049cf30>
byte * Rnc_BitStreamInit(byte * srcBuffer, byte * dstBuffer);
// <LegoRR.exe @0049cf80>
uint Rnc_BitStreamAdvance(byte bits);
// <LegoRR.exe @0049cff0>
int Rnc_FUN_0049cff0(byte bits);
// <LegoRR.exe @0049d050>
undefined Rnc_ReadHuffmanTable(HuffmanLeaf * table, byte bits);
// <LegoRR.exe @0049d0c0>
uint Rnc_ReadHuffman(HuffmanLeaf * table);
// <LegoRR.exe @0049d130>
uint Rnc_FUN_0049d130(void);
// <LegoRR.exe @0049d170>
int Rnc_FUN_0049d170(void);
// <LegoRR.exe @0049d210>
undefined Rnc_FUN_0049d210(HuffmanLeaf * table, byte bits);
// <LegoRR.exe @0049d250>
undefined Rnc_FUN_0049d250(HuffmanLeaf * table, byte bits);
// <LegoRR.exe @0049d2c0>
uint Rnc_MirrorBits(uint value, byte param_2);
// <LegoRR.exe @0049d2f0>
BOOL Win_ChooseScreenMode(BOOL showDialog, BOOL isDebug, BOOL isBest, BOOL isWindow, LPCSTR errorMessage);
// <LegoRR.exe @0049d5b0>
INT_PTR Setup_ModeDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
// <LegoRR.exe @0049d8a0>
void Setup_ChangeFullScreenMode(HWND hDlg, BOOL isFullScreen);
// <LegoRR.exe @0049d8f0>
void Setup_RebuildScreenModes(HWND hDlg);
// <LegoRR.exe @0049da40>
void Setup_RebuildDeviceModes(HWND hDlg);
// <LegoRR.exe @0049db30>
void Setup_RegisterScreenMode(int screenWidth, int screenHeight, int bitDepth);
// <LegoRR.exe @0049db90>
BOOL Setup_HasRegisteredScreenMode(int availableIndex);
// <LegoRR.exe @0049dc10>
BOOL Setup_GetScreenMode(char * displayName, uint * out_index);
// <LegoRR.exe @0049dc90>
void Setup_UpdateRadioButtons(HWND hDlg);
// <LegoRR.exe @0049dd70>
int _strnicmp(char * _Str1, char * _Str2, size_t _MaxCount);
// <LegoRR.exe @0049de20>
char * itoa(int value, char * buffer, int radix);
// <LegoRR.exe @0049de60>
undefined __itoa__internal(int value, char * buffer, int radix, BOOL isNegative);
// <LegoRR.exe @0049ded0>
char * _strlwr(char * str);
// <LegoRR.exe @0049df90>
char * _strupr(char * str);
// <LegoRR.exe @0049e050>
undefined Unwind@0049e050(void);
// <LegoRR.exe @0049e05e>
undefined Unwind@0049e05e(void);
// <LegoRR.exe @0049e080>
undefined Unwind@0049e080(void);
// <LegoRR.exe @0049e0a0>
undefined Unwind@0049e0a0(void);
