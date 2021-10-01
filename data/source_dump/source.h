#pragma once
#include "datatypes.h"

//00400000


// <LegoRR.exe @00401000>
void __cdecl Advisor_Initialise(char* rootPath, Camera* cameraMain, Viewport* viewMain);
// <LegoRR.exe @004011c0>
void __cdecl Advisor_Cleanup(void);
// <LegoRR.exe @00401210>
void __cdecl Advisor_InitViewport(real32 param_unused);
// <LegoRR.exe @00401240>
float10 __cdecl Maths_Vector2DDistance(Point2F* a, Point2F* b);
// <LegoRR.exe @00401270>
void __cdecl Advisor_LoadAdvisorAnims(CFGProperty* root, char* keyRoot);
// <LegoRR.exe @004013a0>
bool32 __cdecl Advisor_GetAdvisorType(char* advisorName, AdvisorType* out_advisorType);
// <LegoRR.exe @004013e0>
Vector3F* __cdecl Maths_Vector3DCrossProduct(Vector3F* out_vector, Vector3F* a, Vector3F* b);
// <LegoRR.exe @00401430>
bool32 __cdecl Advisor_GetAnimType(char* animName, AdvisorAnimType* out_animType);
// <LegoRR.exe @00401470>
Vector3F* __cdecl Maths_Vector3DAdd(Vector3F* out_vector, Vector3F* a, Vector3F* b);
// <LegoRR.exe @004014a0>
void __cdecl Advisor_LoadAdvisorPositions(CFGProperty* root, char* keyRoot, sint32 screenWidth, sint32 screenHeight);
// <LegoRR.exe @00401630>
Vector3F* __cdecl Maths_Vector3DSubtract(Vector3F* out_vector, Vector3F* a, Vector3F* b);
// <LegoRR.exe @00401660>
Vector3F* __cdecl Maths_Vector3DScale(Vector3F* out_vector, Vector3F* a, real32 scalar);
// <LegoRR.exe @00401690>
Vector3F* __cdecl Maths_Vector3DNormalize(Vector3F* ref_vector);
// <LegoRR.exe @004016f0>
void __cdecl Advisor_AddAdvisorPosition(AdvisorType advisorType, AdvisorAnimType animType, TextType textType, sint32 sfxIndex, PanelType panelType, real32 x, real32 y);
// <LegoRR.exe @00401780>
void __cdecl Advisor_SetParameters(AdvisorType advisorType, PanelType panelType, real32 x1, real32 y1);
// <LegoRR.exe @004017d0>
void __cdecl Advisor_GetPoint2(AdvisorType advisorType, real32* out_x2, real32* out_y2);
// <LegoRR.exe @00401800>
bool32 __cdecl Advisor_SetCurrentAdvisor(AdvisorType advisorType, bool32 setFlag2);
// <LegoRR.exe @00401870>
void __cdecl Advisor_SetCurrentSound(AdvisorType advisorType);
// <LegoRR.exe @004018d0>
void __cdecl Advisor_Update(real32 elapsed);
// <LegoRR.exe @004019b0>
bool32 __cdecl Advisor_UpdateAnimation(AdvisorAnimType animType, real32 elapsed);
// <LegoRR.exe @00401a60>
void __cdecl Advisor_ClearFlag2(void);
// <LegoRR.exe @00401a70>
void __cdecl Advisor_ViewportTransform(AdvisorType advisorType);
// <LegoRR.exe @00401b30>
ProgrammerMode __cdecl Main_ProgrammerMode(void);
// <LegoRR.exe @00401b40>
char* __cdecl Main_GetStartLevel(void);
// <LegoRR.exe @00401b60>
bool32 __cdecl Advisor_GetFlag1(void);
// <LegoRR.exe @00401b70>
sint32 __cdecl appWidth(void);
// <LegoRR.exe @00401b80>
sint32 __cdecl appHeight(void);
// <LegoRR.exe @00401b90>
uint32 __cdecl Font_GetStringWidth(Font* font, char* msg, ...);
// <LegoRR.exe @00401bc0>
void __cdecl Font_GetStringInfo(Font* font, uint32* out_width, uint32* out_lineCount, char* msg, ...);
// <LegoRR.exe @00401bf0>
bool32 __cdecl AIPriority_GetType(char* aiPriorityName, AIPriorityType* out_priorityType);
// <LegoRR.exe @00401c30>
void __cdecl AITask_Initialise(void);
// <LegoRR.exe @00401f40>
void __cdecl AITask_FUN_00401f40(AITaskType taskType, LiveObject* liveObj, Point2I* opt_position);
// <LegoRR.exe @00401fa0>
void __cdecl AITask_SetPriorityType(AITaskData* aiTask, AIPriorityType priorityType);
// <LegoRR.exe @00401fd0>
void __cdecl AITask_Game_SetAITaskValue2(sint32 index, uint32 aiTaskValue);
// <LegoRR.exe @00401fe0>
void __cdecl AITask_Game_SetIsPriorityDisabled(sint32 priorityIndex, bool32 isDisabled);
// <LegoRR.exe @00401ff0>
bool32 __cdecl AITask_Game_IsPriorityDisabled(sint32 priorityIndex);
// <LegoRR.exe @00402000>
void __cdecl AITask_Shutdown(void);
// <LegoRR.exe @00402040>
void __cdecl AITask_Reset_Or_ClearFlag2(bool32 unsetFlag2);
// <LegoRR.exe @004020b0>
void __cdecl AITask_Game_SetNoGather(bool32 noGather);
// <LegoRR.exe @00402120>
bool32 __cdecl AITask_RemoveCallback(AITaskData* aiTask);
// <LegoRR.exe @00402140>
void __cdecl free2(undefined* param_1);
// <LegoRR.exe @00402150>
void __cdecl AITask_Update(real32 elapsedGame);
// <LegoRR.exe @00402240>
void __cdecl AITask_FUN_00402240(AITaskData** ref_aiTask);
// <LegoRR.exe @00402440>
void __cdecl AITask_DoDig_AtBlockPos(Point2I* blockPos, bool32 param_2, bool32 param_3);
// <LegoRR.exe @00402530>
void __cdecl AITask_UnkInitRouting_FUN_00402530(AITaskData* aiTask, bool32 param_2);
// <LegoRR.exe @004025a0>
void __cdecl AITask_DoAttackRockMonster_Target(LiveObject* targetObj);
// <LegoRR.exe @004025f0>
void __cdecl AITask_LiveObject_FUN_004025f0(LiveObject* liveObj);
// <LegoRR.exe @00402630>
bool32 __cdecl AITask_IsCollectAndSameTarget(AITaskData* aiTask, LiveObject* liveObj);
// <LegoRR.exe @00402650>
void __cdecl AITask_DoCollect(LiveObject* liveObj, real32 param_2);
// <LegoRR.exe @004026d0>
void __cdecl AITask_DoBuildPath_AtPosition(Point2I* position);
// <LegoRR.exe @00402730>
void __cdecl AITask_DoGather_Count(sint32 count);
// <LegoRR.exe @00402780>
void __cdecl AITask_DoCollect_Target(LiveObject* targetObj);
// <LegoRR.exe @004027c0>
void __cdecl AITask_DoTrain_Target(LiveObject* targetObj, TrainedFlags training, bool32 param_3);
// <LegoRR.exe @00402890>
void __cdecl AITask_DoFindDriver_Target(LiveObject* targetObj);
// <LegoRR.exe @00402970>
bool32 __cdecl AITask_DoCallbacks_IfAttackPath_FUN_00402970(Point2I* blockPos);
// <LegoRR.exe @004029a0>
bool32 __cdecl AITask_Callback_IfAttackPath_FUN_004029a0(AITaskData* aiTask, Point2I** param_2);
// <LegoRR.exe @004029d0>
bool32 __cdecl AITask_LiveObject_DoCallbacks_FUN_004029d0(LiveObject* liveObj);
// <LegoRR.exe @004029f0>
bool32 __cdecl AITask_Callback_FUN_004029f0(AITaskData* aiTask, LiveObject* liveObj);
// <LegoRR.exe @00402a10>
void __cdecl AITask_Block_FUN_00402a10(Point2I* blockPos, sint32 param_2);
// <LegoRR.exe @00402a60>
bool32 __cdecl AITask_Block_FUN_00402a60(Point2I* blockPos);
// <LegoRR.exe @00402a90>
bool32 __cdecl AITask_DoCallbacks_Block_FUN_00402a90(Point2I* blockPos, bool32 param_2);
// <LegoRR.exe @00402ae0>
bool32 __cdecl AITask_Callback_FUN_00402ae0(AITaskData* aiTask, Point2I** pBlockPos);
// <LegoRR.exe @00402b50>
bool32 __cdecl AITask_Callback_FUN_00402b50(AITaskData* aiTask, Point2I** param_2);
// <LegoRR.exe @00402ba0>
bool32 __cdecl AITask_Callback_FUN_00402ba0(AITaskData* aiTask, Point2I** param_2);
// <LegoRR.exe @00402bd0>
bool32 __cdecl AITask_Callback_FUN_00402bd0(AITaskData* aiTask, Point2I** param_2);
// <LegoRR.exe @00402c00>
void __cdecl AITask_Release_2(AITaskData* aiTask);
// <LegoRR.exe @00402c60>
bool32 __cdecl AITask_Callback_IsSameTaskAsField58(AITaskData* aiTask, AITaskData* otherTask);
// <LegoRR.exe @00402c80>
bool32 __cdecl AITask_DoDynamite_AtBlockPos(Point2I* blockPos, bool32 noRoutingUnk);
// <LegoRR.exe @00402d70>
void __cdecl AITask_DoBirdScarer_AtPosition(Point2I* blockPos);
// <LegoRR.exe @00402df0>
void __cdecl AITask_DoFindLoad(LiveObject* targetObj);
// <LegoRR.exe @00402e60>
void __cdecl AITask_DoRepair_Target(LiveObject* targetObj, bool32 condition);
// <LegoRR.exe @00402ea0>
void __cdecl AITask_DoGotoEat_Target(LiveObject* liveObj, LiveObject* targetObj);
// <LegoRR.exe @00402ee0>
void __cdecl AITask_DoElecFence(Point2I* position);
// <LegoRR.exe @00402f60>
void __cdecl AITask_DoReinforce_AtBlockPos(Point2I* blockPos);
// <LegoRR.exe @00402fe0>
void __cdecl AITask_DoClear_AtPosition(Point2I* position, MessageType completeAction);
// <LegoRR.exe @00403010>
void __cdecl AITask_DoGetTool_FromTask(AITaskData* in_aiTask);
// <LegoRR.exe @004030c0>
bool32 __cdecl AITask_DoGetTool(ToolType toolType);
// <LegoRR.exe @00403110>
bool32 __cdecl AITask_Game_SelectedUnits_UnkEquippedTool_FUN_00403110(ToolType toolType);
// <LegoRR.exe @004031a0>
void __cdecl AITask_Game_PTL_UserGoto(LiveObject** liveObjsTable, sint32 count, Point2I* position, bool32 param_4);
// <LegoRR.exe @00403250>
void __cdecl AITask_DoUpgrade(LiveObject* liveObj, sint32 newObjLevel);
// <LegoRR.exe @004032f0>
void __cdecl AITask_DoDock(LiveObject* liveObj);
// <LegoRR.exe @00403320>
void __cdecl AITask_DoGoto_Congregate(Point2I* blockPos);
// <LegoRR.exe @00403360>
void __cdecl AITask_StopGoto_Congregate(Point2I* blockPos);
// <LegoRR.exe @004033d0>
void __cdecl AITask_DoAttackObject(LiveObject* liveObj);
// <LegoRR.exe @00403410>
void __cdecl AITask_DoAttackPath(Point2I* position);
// <LegoRR.exe @00403450>
void __cdecl AITask_DoRepair(LiveObject* liveObj);
// <LegoRR.exe @00403490>
void __cdecl AITask_LiveObject_FUN_00403490(LiveObject* liveObj);
// <LegoRR.exe @004034f0>
void __cdecl AITask_Game_PTL_GotoOrRMGoto(LiveObject* liveObj, Point2I* position, undefined4 param_3);
// <LegoRR.exe @00403540>
void __cdecl AITask_Game_PTL_CrystalToRefinery(LiveObject* liveObj, LiveObject* targetObj);
// <LegoRR.exe @00403580>
void __cdecl AITask_DoFollow_Group(LiveObject** liveObjsTable, sint32 count, LiveObject* targetObj);
// <LegoRR.exe @004035f0>
void __cdecl AITask_Game_PTL_FollowAttack(LiveObject* liveObj, LiveObject* targetObj);
// <LegoRR.exe @00403630>
void __cdecl AITask_FUN_00403630(sint32 param_1, sint32 param_2, sint32 param_3, sint32 param_4);
// <LegoRR.exe @00403680>
void __cdecl AITask_DoRequest_ObjectType(ObjectType objType, sint32 objLevel, sint32 objIndex, Point2I* blockPos, undefined4 param_5, Point2F* pointFloat, bool32 param_7);
// <LegoRR.exe @00403740>
void __cdecl AITask_PlaceRequestObject(Point2I* blockPos, ObjectType objType, sint32 objIndex, sint32 objLevel);
// <LegoRR.exe @004037f0>
AITaskData* __cdecl AITask_DoDeposit_ObjectType(LiveObject* liveObj, ObjectType objType, sint32 objIndex, sint32 objLevel);
// <LegoRR.exe @00403840>
void __cdecl AITask_DoRequestObjectCallbacks(LiveObject* liveObj);
// <LegoRR.exe @004038d0>
void __cdecl AITask_LiveObject_FUN_004038d0(LiveObject* liveObj);
// <LegoRR.exe @00403900>
void __cdecl AITask_DoGotoEat(LiveObject* liveObj);
// <LegoRR.exe @00403940>
bool32 __cdecl AITask_LiveObject_FUN_00403940(LiveObject* liveObj);
// <LegoRR.exe @00403960>
bool32 __cdecl AITask_Callback_FUN_00403960(AITaskData* aiTask, LiveObject* liveObj);
// <LegoRR.exe @00403980>
void __cdecl AITask_LiveObject_FUN_00403980(LiveObject* liveObj);
// <LegoRR.exe @00403a00>
bool32 __cdecl AITask_Callback_FUN_00403a00(AITaskData* aiTask, LiveObject* liveObj);
// <LegoRR.exe @00403a20>
void __cdecl AITask_LiveObject_FUN_00403a20(LiveObject* liveObj, bool32 param_2);
// <LegoRR.exe @00403a70>
void __cdecl AITask_LiveObject_FUN_00403a70(LiveObject* liveObj);
// <LegoRR.exe @00403a90>
void __cdecl AITask_VariousGatherTasks_FUN_00403a90(LiveObject* liveObj);
// <LegoRR.exe @00403b30>
void __cdecl AITask_LiveObject_FUN_00403b30(LiveObject* holderObj, AITaskType taskType, LiveObject* carriedObj);
// <LegoRR.exe @00403c40>
void __cdecl AITask_LiveObject_SetAITaskUnk(LiveObject* liveObj1, AITaskType taskType, LiveObject* liveObj2, bool32 param_4);
// <LegoRR.exe @00403e20>
bool32 __cdecl AITask_LiveObject_FUN_00403e20(LiveObject* liveObj);
// <LegoRR.exe @00403e40>
bool32 __cdecl AITask_Callback_FUN_00403e40(AITaskData* aiTask, LiveObject* liveObj);
// <LegoRR.exe @00403e60>
void __cdecl AITask_DoAnimationWait(LiveObject* liveObj);
// <LegoRR.exe @00403e90>
void __cdecl AITask_LiveObject_Unk_UpdateAITask_AnimationWait(LiveObject* liveObj);
// <LegoRR.exe @00403eb0>
sint32 __cdecl AITask_QSortCompare(AITaskData** task_a, AITaskData** task_b);
// <LegoRR.exe @00403f60>
AITaskData* __cdecl AITask_InitTask_1(AITaskData* aiTask, AIPriorityType priorityType);
// <LegoRR.exe @00403fa0>
void __cdecl AITask_Init_2_NoPriority(AITaskData* aiTask);
// <LegoRR.exe @00403fd0>
void __cdecl AITask_Game_UnkLiveObjectHandleDynamite(LiveObject* liveObj);
// <LegoRR.exe @00404030>
void __cdecl AITask_LiveObject_FUN_00404030(LiveObject* liveObj);
// <LegoRR.exe @004040c0>
AITaskData* __cdecl AITask_LiveObject_AITask2F0_GetLast(LiveObject* liveObj);
// <LegoRR.exe @004040e0>
bool32 __cdecl AITask_LiveObject_IsCurrentTaskType(LiveObject* liveObj, AITaskType taskType);
// <LegoRR.exe @00404110>
AITaskData* __cdecl AITask_LiveObject_FUN_00404110(LiveObject* liveObj);
// <LegoRR.exe @00404180>
bool32 __cdecl AITask_Callback_FUN_00404180(AITaskData* aiTask, real32* param_2);
// <LegoRR.exe @004041b0>
bool32 __cdecl AITask_LiveObject_Callback_DoAITask(LiveObject* liveObj, real32* param_2);
// <LegoRR.exe @00404d30>
bool32 __cdecl AITask_LiveObject_FUN_00404d30(LiveObject* in_liveObj, real32* param_2, real32* param_3);
// <LegoRR.exe @00404e00>
bool32 __cdecl AITask_LiveObject_FUN_00404e00(LiveObject* liveObj);
// <LegoRR.exe @00404e40>
bool32 __cdecl AITask_FUN_00404e40(ObjectType objType, sint32 objIndex, sint32 objLevel);
// <LegoRR.exe @00404e80>
bool32 __cdecl AITask_Callback_FUN_00404e80(AITaskData* aiTask, sint32* param_2);
// <LegoRR.exe @00404ef0>
bool32 __cdecl AITask_FUN_00404ef0(AITaskData* aiTask, LiveObject* liveObj_2, real32* param_3, real32* param_4, undefined4* param_5, sint32 param_6, sint32 param_7);
// <LegoRR.exe @00405880>
void __cdecl AITask_FUN_00405880(void);
// <LegoRR.exe @00405b40>
void __cdecl AITask_FUN_00405b40(void);
// <LegoRR.exe @00406290>
void __cdecl AITask_FUN_00406290(AITaskData* aiTask1, AITaskData* aiTask2, LiveObject* liveObj);
// <LegoRR.exe @00406310>
void __cdecl AITask_LiveObject_ReleaseTaskReferences(LiveObject* liveObj);
// <LegoRR.exe @00406330>
AITaskData* __cdecl AITask_FUN_00406330(AITaskData* aiTask);
// <LegoRR.exe @00406370>
AITaskData* __cdecl AITask_Create(AITaskType taskType);
// <LegoRR.exe @004063b0>
void __cdecl AITask_Remove(AITaskData* aiTask, bool32 noRelease2);
// <LegoRR.exe @004063f0>
void __cdecl AITask_AddList(void);
// <LegoRR.exe @00406470>
bool32 __cdecl AITask_DoUnkCallbacks(undefined* taskFunction, LiveObject* liveObj);
// <LegoRR.exe @00406500>
IDirectDraw4* __cdecl DirectDraw(void);
// <LegoRR.exe @00406510>
IDirectDrawSurface4* __cdecl DirectDraw_bSurf(void);
// <LegoRR.exe @00406520>
void __cdecl Routing_Maths_Vector2D_FUN_00406520(Point2F* out_point, Point2F* param_2, Point2F* param_3, Point2F* param_4, Point2F* param_5, real32 scalar);
// <LegoRR.exe @00406660>
float10 __cdecl Routing_Maths_Vector2DDistance(Point2F* a, Point2F* b);
// <LegoRR.exe @00406690>
Point2F* __cdecl Routing_Maths_Vector2DChangeLength(Point2F* ref_point, real32 newLength);
// <LegoRR.exe @004066e0>
float10 __cdecl Routing_UpdateDistances_RetTotal(RoutingData* route);
// <LegoRR.exe @00406750>
void __cdecl Routing_DoMath_FUN_00406750(RoutingData* route, Point2F* a, Point2F* b, Point2F* c, Point2F* d, uint32 count);
// <LegoRR.exe @004067f0>
uint32 __cdecl Routing_Calculate_FUN_004067f0(RoutingData* route, real32 scalar, Point2F* out_point);
// <LegoRR.exe @004068b0>
bool32 __cdecl Creature_IsCameraFlipDir(CreatureData* creature);
// <LegoRR.exe @004068c0>
bool32 __cdecl Creature_LoadActivityFile(CreatureData* creature, sint32 objIndex, Container* resRoot, char* aeFilename, char* rootName);
// <LegoRR.exe @00406b30>
void __cdecl Creature_SwapPolyMedium(CreatureData* creature, bool32 swap);
// <LegoRR.exe @00406b60>
void __cdecl Creature_SwapPolyHigh(CreatureData* creature, bool32 swap);
// <LegoRR.exe @00406b90>
void __cdecl Creature_SwapPolyFP(CreatureData* creature, bool32 swap, sint32 cameraFrameIndex);
// <LegoRR.exe @00406bc0>
void __cdecl Object_HideAll(BasicObjectData* basicObjData, bool32 hide);
// <LegoRR.exe @00406be0>
void __cdecl Creature_Duplicate(CreatureData* in_creature, CreatureData* out_creature);
// <LegoRR.exe @00406c40>
void __cdecl Creature_DoCallbacks(CreatureData* creature, real32 elapsed);
// <LegoRR.exe @00406c60>
float10 __cdecl Creature_FUN_00406c60(CreatureData* creature, real32 elapsed, uint32 param_3);
// <LegoRR.exe @00406cd0>
float10 __cdecl Creature_GetAnimFloat10(CreatureData* creature);
// <LegoRR.exe @00406cf0>
void __cdecl Creature_SetOrientation(CreatureData* creature, real32 x, real32 y);
// <LegoRR.exe @00406d20>
void __cdecl Creature_SetPosition(CreatureData* creature, real32 x, real32 y, GetSurfaceZFunc getSurfaceZFunc, SurfaceMap* surfMap);
// <LegoRR.exe @00406d60>
Container* __cdecl Object_GetActivityContainer(BasicObjectData* basicObjData);
// <LegoRR.exe @00406d70>
bool32 __cdecl Creature_SetActivity_AndRemoveCarryCameraFrames(CreatureData* creature, char* activityName, real32 elapsed);
// <LegoRR.exe @00406df0>
void __cdecl Creature_Destroy(CreatureData* creature);
// <LegoRR.exe @00406e80>
Container* __cdecl Object_SearchForPartName(BasicObjectData* basicObjData, char* name, sint32 instance);
// <LegoRR.exe @00406eb0>
Container* __cdecl Creature_GetCameraNull(CreatureData* creature, sint32 cameraIndex);
// <LegoRR.exe @00406ee0>
Container* __cdecl Creature_GetDrillNull(CreatureData* creature);
// <LegoRR.exe @00406f10>
Container* __cdecl Creature_GetCarryNull(CreatureData* creature);
// <LegoRR.exe @00406f40>
Container* __cdecl Creature_GetDepositNull(CreatureData* creature);
// <LegoRR.exe @00406f70>
bool32 __cdecl Creature_GetThrowNull(CreatureData* creature);
// <LegoRR.exe @00406fc0>
float10 __cdecl Creature_GetTransCoef(CreatureData* creature);
// <LegoRR.exe @00406fe0>
void __cdecl Bubble_Initialise(void);
// <LegoRR.exe @00407170>
void __cdecl Bubble_LoadCFG(CFGProperty* root);
// <LegoRR.exe @00407230>
BubbleType __cdecl Bubble_GetBubbleType(char* bubbleName);
// <LegoRR.exe @00407270>
void __cdecl Bubble_ToggleObjectUIsAlwaysVisible(void);
// <LegoRR.exe @00407290>
bool32 __cdecl Bubble_GetObjectUIsAlwaysVisible(void);
// <LegoRR.exe @004072a0>
void __cdecl Bubble_LiveObject_UpdateBubbleImage(LiveObject* liveObj);
// <LegoRR.exe @004072d0>
void __cdecl Bubble_LiveObject_FUN_004072d0(LiveObject* liveObj);
// <LegoRR.exe @00407340>
void __cdecl Bubble_LiveObject_FUN_00407340(LiveObject* liveObj);
// <LegoRR.exe @00407380>
void __cdecl Bubble_LiveObject_MiniFigure_FUN_00407380(LiveObject* liveObj);
// <LegoRR.exe @004073e0>
void __cdecl Bubble_LiveObject_MiniFIgure_FUN_004073e0(LiveObject* liveObj);
// <LegoRR.exe @00407440>
void __cdecl Bubble_LiveObject_MiniFigure_FUN_00407440(LiveObject* liveObj, real32 param_2);
// <LegoRR.exe @00407470>
void __cdecl Bubble_LiveObject_FUN_00407470(LiveObject* liveObj);
// <LegoRR.exe @004074d0>
void __cdecl Bubble_Unk_DrawObjectUIs_FUN_004074d0(real32 elapsedAbs);
// <LegoRR.exe @004077f0>
void __cdecl Bubble_LiveObject_GetBubbleImage_FUN_004077f0(LiveObject* liveObj, real32 param_2, Image** out_bubbleImage, Point2F* param_4);
// <LegoRR.exe @00407890>
bool32 __cdecl Bubble_LiveObject_CallbackDraw_FUN_00407890(LiveObject* liveObj, real32* param_2);
// <LegoRR.exe @00407940>
void __cdecl Bubble_LiveObject_GetCurrentBubbleImage(LiveObject* liveObj, Image** out_bubbleImage);
// <LegoRR.exe @00407c90>
bool32 __cdecl Building_LoadActivityFile(BuildingData* building, sint32 objIndex, Container* resData, char* filename, char* rootName);
// <LegoRR.exe @00408210>
void __cdecl Building_FUN_00408210(BuildingData* building, bool32 unkAddSubInverse);
// <LegoRR.exe @00408290>
Point2I* __cdecl Building_GetShapePoints(BuildingData* building, uint32* out_shapeCount);
// <LegoRR.exe @004082b0>
void __cdecl Object_SetOwnerObject(BasicObjectData* basicObjData, LiveObject* liveObj);
// <LegoRR.exe @004082d0>
void __cdecl Building_SetUpgradeActivity(BuildingData* building, char* activityName);
// <LegoRR.exe @004084a0>
bool32 __cdecl Building_SetActivity_AndRemoveCarryCameraFrames(BuildingData* building, char* activityName, real32 elapsed);
// <LegoRR.exe @00408520>
Container* __cdecl Building_GetCameraNull(BuildingData* building, sint32 cameraIndex);
// <LegoRR.exe @00408550>
void __cdecl Building_Duplicate(BuildingData* in_building, BuildingData* out_building);
// <LegoRR.exe @004085a0>
void __cdecl Building_HideAll(BuildingData* building, bool32 hide);
// <LegoRR.exe @004085d0>
bool32 __cdecl Object_IsHidden(BasicObjectData* basicObjData);
// <LegoRR.exe @004085f0>
void __cdecl Building_SetOrientation(BuildingData* building, real32 x, real32 y);
// <LegoRR.exe @00408640>
void __cdecl Building_SetPosition(BuildingData* building, real32 x, real32 y, undefined* getZcallback, SurfaceMap* surfMap);
// <LegoRR.exe @004086a0>
Container* __cdecl Building_GetCarryNull(BuildingData* building, sint32 carryIndex);
// <LegoRR.exe @004086e0>
Container* __cdecl Building_GetDepositNull(BuildingData* building);
// <LegoRR.exe @00408710>
Container* __cdecl Building_GetEntranceNull(BuildingData* building);
// <LegoRR.exe @00408740>
Container* __cdecl Building_GetToolNull(BuildingData* building, sint32 toolIndex);
// <LegoRR.exe @00408780>
sint32 __cdecl Building_GetCarryNullFrames(BuildingData* building);
// <LegoRR.exe @00408790>
float10 __cdecl Building_FUN_00408790(BuildingData* building, real32 elapsed, uint32 param_3);
// <LegoRR.exe @00408860>
float10 __cdecl Building_GetAnimFloat14_zero(BuildingData* building);
// <LegoRR.exe @00408870>
void __cdecl Building_Destroy(BuildingData* building);
// <LegoRR.exe @004088a0>
bool32 __cdecl Object_Debug_ChangeUpgradeModel(BuildingData* building, sint32 levelBit, bool32 condition);
// <LegoRR.exe @004088d0>
void __cdecl Building_ChangeUpgradeParts(BuildingData* building, sint32 objLevel);
// <LegoRR.exe @00408900>
float10 __cdecl Collision_Maths_Sub_FUN_00408900(Point2F* param_1, Point2F* param_2, Point2F* param_3);
// <LegoRR.exe @00408a30>
float10 __cdecl Collision_Maths_FUN_00408a30(Point2F* point, Point2F* fromList, Point2F* toList, uint32 count);
// <LegoRR.exe @00408a90>
Point2F* __cdecl Collision_Maths_FUN_00408a90(Point2F* param_1, Point2F* param_2, Point2F* position, Point2F* out_point);
// <LegoRR.exe @00408b20>
Point2F* __cdecl Collision_MathUnk_Vector2D_FUN_00408b20(Point2F* param_1, Point2F* param_2, Point2F* position, Point2F* out_point);
// <LegoRR.exe @00408bb0>
uint32 __cdecl Construction_GetBuildingBase(char* name);
// <LegoRR.exe @00408c10>
void __cdecl Construction_FUN_00408c10(sint32 param_1, LiveObject* liveObj);
// <LegoRR.exe @00408ca0>
bool32 __cdecl Construction_FUN_00408ca0(sint32 param_1, sint32 param_2, sint32 param_3);
// <LegoRR.exe @00408d40>
sint32 __cdecl Construction_FUN_00408d40(BlockConstruction* param_1, ObjectType objType, sint32 objIndex);
// <LegoRR.exe @00408d80>
void __cdecl Construction_SpawnCarryableObject(Point2I* blockPos, ObjectType objType, sint32 objIndex, sint32 objLevel, uint32 count);
// <LegoRR.exe @00408df0>
void __cdecl Construction_FUN_00408df0(Point2I* blockPos, uint32* param_2, uint32 param_3);
// <LegoRR.exe @00408fd0>
bool32 __cdecl Construction_BlockCheck_FUN_00408fd0(Point2I* blockPos);
// <LegoRR.exe @00408ff0>
BlockConstruction* __cdecl Construction_BlockCheck_FUN_00408ff0(Point2I* blockPos, sint32* opt_param_2);
// <LegoRR.exe @00409040>
void __cdecl Construction_Block_FUN_00409040(Point2I* blockPos);
// <LegoRR.exe @00409080>
void __cdecl Construction_Cancel2(Point2I* blockPos);
// <LegoRR.exe @00409110>
void __cdecl Construction_Update(real32 elapsedGame);
// <LegoRR.exe @004091a0>
bool32 __cdecl Construction_LiveObject_DoBlockStructD4_Callbacks_FUN_004091a0(BlockConstruction* param_1);
// <LegoRR.exe @004091c0>
bool32 __cdecl Construction_LiveObject_Callback_FindIn_BlockStructD4Table(LiveObject* liveObj, BlockConstruction* data);
// <LegoRR.exe @00409230>
bool32 __cdecl Construction_LayPath(Point2I* blockPos);
// <LegoRR.exe @00409280>
BlockConstruction* __cdecl Construction_CreateBlock(Point2I* blockPos);
// <LegoRR.exe @004092e0>
void __cdecl Construction_Level_Block_FUN_004092e0(Point2I* blockPos);
// <LegoRR.exe @00409380>
bool32 __cdecl Construction_Level_Blocks_UnkPowerCrystalProc_FUN_00409380(Point2I* blockPos, sint32 crystalCount);
// <LegoRR.exe @004093a0>
bool32 __cdecl Construction_Level_Block_UnkDrainedPower_FUN_004093a0(Point2I* blockPos, sint32 crystalCount);
// <LegoRR.exe @00409480>
void __cdecl Construction_FUN_00409480(BlockConstruction* construct);
// <LegoRR.exe @00409530>
void __cdecl Construction_Cancel(Point2I* blockPos);
// <LegoRR.exe @004096c0>
sint32 __cdecl Construction_Start(sint32 objIndex, Point2I* blockPos, Direction direction, Point2I* shapePoints, uint32 count);
// <LegoRR.exe @00409870>
void __cdecl Construction_FlattenGround(Point2I* blockPos);
// <LegoRR.exe @00409900>
void __cdecl Construction_RemoveAll(void);
// <LegoRR.exe @00409920>
void __cdecl Construction_Free(BlockConstruction* param_1);
// <LegoRR.exe @00409970>
void __cdecl Construction_FUN_00409970(BlockConstruction* param_1);
// <LegoRR.exe @004099c0>
LiveObject* __cdecl Construction_AddShape_FUN_004099c0(uint32 param_1, Point2I* blockPos, Direction param_3, Point2I* shapePoints, uint32 shapeCount, bool32 teleportDown);
// <LegoRR.exe @00409a60>
LiveObject* __cdecl Construction_Complete(BlockConstruction* construct, bool32 teleportDown);
// <LegoRR.exe @00409c00>
void __cdecl Construction_Block_FUN_00409c00(Point2I* blockPos);
// <LegoRR.exe @00409c70>
void __cdecl Game_DisableCryOreDrop(bool32 param_1);
// <LegoRR.exe @00409c80>
void __cdecl LiveObject_Building_Remove_FUN_00409c80(LiveObject* liveObj);
// <LegoRR.exe @00409e50>
void __cdecl LiveObject_GenerateCryOre_FromCosts(LiveObject* liveObj);
// <LegoRR.exe @00409f20>
void __cdecl LiveObject_BuildingDestroy(LiveObject* liveObj);
// <LegoRR.exe @00409ff0>
void __cdecl Credits_Play(char* textFile, Font* font, char* aviFile);
// <LegoRR.exe @0040a300>
void __cdecl DamageFont_Cleanup(void);
// <LegoRR.exe @0040a330>
void __cdecl DamageFont_LoadFrames(char* dirName, char* fileBaseName);
// <LegoRR.exe @0040a3e0>
void __cdecl DamageFont_DisplayDamage_OverLiveObject(LiveObject* liveObj, uint32 displayNumber);
// <LegoRR.exe @0040a4f0>
HealthFontData* __cdecl DamageFont_GetNextFree(void);
// <LegoRR.exe @0040a510>
void __cdecl DamageFont_SetDisplayNumber(HealthFontData* healthFont, uint32 displayNumber);
// <LegoRR.exe @0040a670>
void __cdecl DamageFont_MeshRenderCallback(Mesh* mesh, HealthFontData* healthFont, Viewport* view);
// <LegoRR.exe @0040a940>
void __cdecl DamageFont_UpdateAll(real32 elapsedAbs);
// <LegoRR.exe @0040a970>
void __cdecl DamageFont_UpdateSingle(HealthFontData* healthFont, real32 elapsedAbs);
// <LegoRR.exe @0040aa10>
bool32 __cdecl DamageFont_LiveObject_CheckCanShowDamage_Unk(LiveObject* liveObj);
// <LegoRR.exe @0040aa40>
void __cdecl Dependencies_Debug_SetBuildingPrerequisits(bool32 on);
// <LegoRR.exe @0040aa60>
void __cdecl Dependencies_Reset_ClearAllLevelFlags_10c(void);
// <LegoRR.exe @0040aaa0>
void __cdecl Dependencies_Initialise(CFGProperty* root, char* rootPath);
// <LegoRR.exe @0040add0>
bool32 __cdecl Dependencies_Object_FUN_0040add0(ObjectType objType, sint32 objIndex, sint32 objLevel);
// <LegoRR.exe @0040ae70>
bool32 __cdecl Dependencies_LiveObject_CallbackCheck_FUN_0040ae70(LiveObject* liveObj, LiveObject* otherObj);
// <LegoRR.exe @0040aec0>
void __cdecl Dependencies_Object_GetRequirements(ObjectType objType, sint32 objIndex, sint32 objLevel, DependencyRequirement** out_requirements, uint32* out_count);
// <LegoRR.exe @0040af30>
void __cdecl Dependencies_Object_Unlock(ObjectType objType, sint32 objIndex, sint32 objLevel, DependencyUnlocks* unlocks);
// <LegoRR.exe @0040b0e0>
void __cdecl Dependencies_Prepare_Unk(void);
// <LegoRR.exe @0040b180>
bool32 __cdecl Dependencies_Object_IsLevelFlag4(ObjectType objType, sint32 objIndex, sint32 objLevel);
// <LegoRR.exe @0040b1d0>
void __cdecl Dependencies_Object_AddLevelFlag_100(ObjectType objType, sint32 objIndex, sint32 objLevel);
// <LegoRR.exe @0040b210>
bool32 __cdecl Dependencies_Object_GetLevelFlag_100(ObjectType objType, sint32 objIndex, sint32 objLevel);
// <LegoRR.exe @0040b240>
SurfaceTextureGrid* __cdecl DynamicPM_LoadTextureBaseName(char* textureBaseName, uint32 width, uint32 height);
// <LegoRR.exe @0040b340>
void __cdecl DynamicPM_Free_SurfaceTextureGrid(SurfaceTextureGrid* surfTextGrid);
// <LegoRR.exe @0040b3a0>
float10 __cdecl DynamicPM_FUN_0040b3a0(sint32 param_1, Viewport* view, Point2F* param_3, bool32 param_4);
// <LegoRR.exe @0040b520>
ProMeshData* __cdecl DynamicPM_LoadPromesh_AB(Container* resData, char* meshName_a, char* meshName_b, real32 blockSize, SurfaceTextureGrid* surfTextGrid);
// <LegoRR.exe @0040b700>
void __cdecl DynamicPM_Free(ProMeshData* promesh);
// <LegoRR.exe @0040b740>
void __cdecl DynamicPM_Remove_FUN_0040b740(ProMeshData* promesh);
// <LegoRR.exe @0040b780>
Container_Texture* __cdecl DynamicPM_SurfaceTextureGrid_GetTexture(SurfaceTextureGrid* param_1, SurfaceTexture coord_4X_0Y);
// <LegoRR.exe @0040b7b0>
void __cdecl DynamicPM_FUN_0040b7b0(ProMeshData* promesh, Vector3F* vectPoses4, SurfaceTexture texture, uint8 param_4, undefined4 param_5, undefined4 param_6);
// <LegoRR.exe @0040b930>
void __cdecl DynamicPM_Sub1_FUN_0040b930(Container* cont, real32 param_2, Vector3F* position, Vector3F* dir, Vector3F* up, real32 scaleZ, real32 brightness, Container_Texture* contTexture, uint8 unkFlags1to80);
// <LegoRR.exe @0040bac0>
void __cdecl DynamicPM_Sub2_FUN_0040bac0(Container* cont, real32 param_2, Vector3F* position, Vector3F* dir, Vector3F* up);
// <LegoRR.exe @0040bc90>
void __cdecl DynamicPM_Matrix_FUN_0040bc90(Matrix4F* out_matrix, real32 param_2, real32 param_3, real32 param_4, real32 param_5, real32 param_6);
// <LegoRR.exe @0040bcf0>
void __cdecl Effect_StopAll(void);
// <LegoRR.exe @0040bd10>
void __cdecl Effect_Spawn_BoulderExplode_AtObjectOther(LiveObject* liveObj);
// <LegoRR.exe @0040bd40>
void __cdecl Effect_Spawn_BoulderExplode(Vector3F* position);
// <LegoRR.exe @0040bde0>
void __cdecl Effect_Spawn_SmashPath(LiveObject* optor_liveObj, Vector3F* optor_position);
// <LegoRR.exe @0040bea0>
bool32 __cdecl Effect_GetRockFallStyle(char* name, uint32* out_index);
// <LegoRR.exe @0040bef0>
void __cdecl Effect_SetRockFallStyle(sint32 rockFallStyleIndex);
// <LegoRR.exe @0040bf00>
void __cdecl Effect_Load_RockFallStylesAll(CFGProperty* root, char* rootPath, Container* contRoot);
// <LegoRR.exe @0040c000>
bool32 __cdecl Effect_Load_RockFallStyle(Container* contRoot, char* filename, sint32 rockFallStyle, sint32 rockFallType, char* itemName);
// <LegoRR.exe @0040c0e0>
bool32 __cdecl Effect_Load_ElectricFenceBeam(Container* resRoot, char* filename, bool32 isLongBeam);
// <LegoRR.exe @0040c160>
bool32 __cdecl Effect_Spawn_RockFall(RockFallType rockFallType, sint32 bx, sint32 by, real32 x, real32 y, real32 z, real32 dirX, real32 dirY);
// <LegoRR.exe @0040c220>
bool32 __cdecl Effect_ElectricFenceBeam_Spawn(bool32 longBeam, real32 xPos, real32 yPos, real32 zPos, real32 xDir, real32 yDir, real32 zDir);
// <LegoRR.exe @0040c2d0>
uint32 __cdecl Effect_UpdateAll(real32 elapsedGame, uint32** out_rockFallTypes, uint32** out_rockFallSubtypes);
// <LegoRR.exe @0040c400>
void __cdecl Effect_Update_BoulderExplode(real32 elapsedGame);
// <LegoRR.exe @0040c450>
void __cdecl Effect_Update_SmashPath(real32 elapsedGame);
// <LegoRR.exe @0040c4a0>
void __cdecl Effect_GetBlockPos_RockFall(RockFallType rockFallType, sint32 index, uint32* out_bx, uint32* out_by);
// <LegoRR.exe @0040c4e0>
Container* __cdecl Effect_Unk_RockFall_FUN_0040c4e0(uint32 bx, uint32 by);
// <LegoRR.exe @0040c5c0>
void __cdecl Effect_RemoveAll_BoulderExplode(void);
// <LegoRR.exe @0040c5f0>
void __cdecl Effect_RemoveAll_RockFall(void);
// <LegoRR.exe @0040c650>
void __cdecl Effect_Load_Explosion(Container* contRoot, char* filename);
// <LegoRR.exe @0040c680>
void __cdecl Effect_Spawn_Explosion(LiveObject* optor_liveObj, Point2F* optor_position);
// <LegoRR.exe @0040c760>
void __cdecl Effect_Update_Explosion(real32 elapsedGame);
// <LegoRR.exe @0040c7d0>
EffectMisc* __cdecl Effect_GetMiscEffectData(MiscEffectType miscEffectType);
// <LegoRR.exe @0040c850>
bool32 __cdecl Effect_Load_Misc(EffectMisc* effectMisc, Container* contRoot, char* filename);
// <LegoRR.exe @0040c8c0>
void __cdecl Effect_Initialise(CFGProperty* root, char* rootPath, Container* cont);
// <LegoRR.exe @0040caa0>
void __cdecl Effect_Update_MiscEffect(EffectMisc* miscEffect, real32 elapsedGame);
// <LegoRR.exe @0040cb70>
void __cdecl Effect_Update_MiscEffectsAll(real32 elapsedGame);
// <LegoRR.exe @0040cc10>
bool32 __cdecl Effect_Spawn_Particle(MiscEffectType miscEffectType, Vector3F* position, Vector3F* opt_dir);
// <LegoRR.exe @0040ccf0>
void __cdecl ElectricFence_Initialise(LevelData* level);
// <LegoRR.exe @0040cd60>
void __cdecl ElectricFence_Shutdown(void);
// <LegoRR.exe @0040cdb0>
void __cdecl ElectricFence_ResetAll(LevelData* level);
// <LegoRR.exe @0040cdd0>
void __cdecl ElectricFence_UpdateBlockConnections(sint32 bx, sint32 by);
// <LegoRR.exe @0040ce80>
void __cdecl ElectricFence_AssignBlockObject(LiveObject* liveObj);
// <LegoRR.exe @0040ceb0>
BlockElectricFence* __cdecl ElectricFence_Create(LiveObject* liveObj, sint32 x, sint32 y);
// <LegoRR.exe @0040cf60>
void __cdecl ElectricFence_AddList(void);
// <LegoRR.exe @0040cfd0>
void __cdecl ElectricFence_LiveObject_Destroy(LiveObject* liveObj);
// <LegoRR.exe @0040d030>
void __cdecl ElectricFence_Remove(BlockElectricFence* block, sint32 x, sint32 y);
// <LegoRR.exe @0040d0a0>
bool32 __cdecl ElectricFence_Debug_PlaceFence(sint32 bx, sint32 by);
// <LegoRR.exe @0040d120>
bool32 __cdecl ElectricFence_Debug_RemoveFence(sint32 bx, sint32 by);
// <LegoRR.exe @0040d170>
bool32 __cdecl ElectricFence_CanPlaceFenceAtBlock(sint32 bx, sint32 by);
// <LegoRR.exe @0040d320>
bool32 __cdecl ElectricFence_Block_FUN_0040d320(LevelData* level, sint32 bx, sint32 by, bool32 param_4);
// <LegoRR.exe @0040d380>
void __cdecl ElectricFence_Update(real32 elapsedGame);
// <LegoRR.exe @0040d3c0>
void __cdecl ElectricFence_EnumerateObjects(ElectricFenceEnumerateCallback callback, void* data);
// <LegoRR.exe @0040d420>
bool32 __cdecl ElectricFence_FUN_0040d420(LiveObject* liveObj, uint32 param_2, uint32 param_3);
// <LegoRR.exe @0040d510>
bool32 __cdecl ElectricFence_Callback_FUN_0040d510(LiveObject* liveObj, real32* pElapsedGame);
// <LegoRR.exe @0040d650>
bool32 __cdecl ElectricFence_LiveObject_Callback_FUN_0040d650(LiveObject* liveObj, void* data);
// <LegoRR.exe @0040d6a0>
void __cdecl ElectricFence_CallbackUpdate(BlockElectricFence* efence, real32* pElapsedGame);
// <LegoRR.exe @0040d780>
void __cdecl ElectricFence_Block_FUN_0040d780(uint32 bx, uint32 by, bool32 param_3, real32 param_4);
// <LegoRR.exe @0040db50>
bool32 __cdecl ElectricFence_Block_UnkAreaDistanceBetweenBlocks(uint32 bxFrom, uint32 byFrom, uint32 bxTo, uint32 byTo);
// <LegoRR.exe @0040dcc0>
Vector3F* __cdecl ElectricFence_Block_GetDistanceBetweenBlocks(uint32 bxFrom, uint32 byFrom, uint32 bxTo, uint32 byTo, Vector3F* out_vector);
// <LegoRR.exe @0040dd70>
bool32 __cdecl ElectricFence_LiveObject_FUN_0040dd70(LiveObject* liveObj);
// <LegoRR.exe @0040dff0>
void __cdecl ElectricFence_LiveObject_SparkBlock_FUN_0040dff0(LiveObject* liveObj, Point2F* param_2, uint32 bx, uint32 by);
// <LegoRR.exe @0040e110>
bool32 __cdecl ElectricFence_Block_FUN_0040e110(LevelData* level, uint32 bx, uint32 by);
// <LegoRR.exe @0040e280>
void __cdecl ElectricFence_Block_ElecFenceStud_FUN_0040e280(LevelData* level, uint32 bx, uint32 by, sint32 param_4);
// <LegoRR.exe @0040e390>
bool32 __cdecl ElectricFence_Block_IsFence(sint32 bx, sint32 by);
// <LegoRR.exe @0040e3c0>
void __cdecl Encyclopedia_Initialise(CFGProperty* root, char* keyBasePath);
// <LegoRR.exe @0040e630>
void __cdecl Encyclopedia_SetObject(LiveObject* liveObj);
// <LegoRR.exe @0040e710>
void __cdecl Encyclopedia_UnsetFlag1(void);
// <LegoRR.exe @0040e720>
void __cdecl Encyclopedia_Update(real32 elapsedAbs);
// <LegoRR.exe @0040e800>
void __cdecl Encyclopedia_DrawSelectBox(Viewport* viewMain);
// <LegoRR.exe @0040e840>
void __cdecl Encyclopedia_LiveObject_ClearPtr_004c8ea4_IfEqual(LiveObject* liveObj);
// <LegoRR.exe @0040e860>
void __cdecl Erode_Initialise(real32 triggerTime, real32 erodeTime, real32 lockTime);
// <LegoRR.exe @0040e8c0>
bool32 __cdecl Erode_GetFreeActiveIndex(sint32* out_index);
// <LegoRR.exe @0040e8f0>
float10 __cdecl Erode_GetBlockErodeRate(Point2I* blockPos);
// <LegoRR.exe @0040e940>
void __cdecl Erode_AddActiveBlock(Point2I* position, sint32 unkModulusNum);
// <LegoRR.exe @0040e9e0>
void __cdecl Erode_Update(real32 elapsedGame);
// <LegoRR.exe @0040ed30>
void __cdecl Erode_AddLockedBlock(Point2I* blockPos);
// <LegoRR.exe @0040ed80>
void __cdecl Erode_Block_FUN_0040ed80(Point2I* blockPos, bool32 doState2_else_add3);
// <LegoRR.exe @0040eee0>
bool32 __cdecl Erode_IsBlockLocked(Point2I* blockPos);
// <LegoRR.exe @0040ef30>
bool32 __cdecl Erode_FUN_0040ef30(Point2I* blockPos, Point2I* out_blockPos);
// <LegoRR.exe @0040f010>
uint32 __cdecl Fallin_Update(real32 elapsedGame);
// <LegoRR.exe @0040f0c0>
bool32 __cdecl Fallin_Block_FUN_0040f0c0(Point2I* blockPos, bool32 param_2);
// <LegoRR.exe @0040f1e0>
bool32 __cdecl Fallin_Block_UpdateFallinsUnk1(Point2I* blockPos);
// <LegoRR.exe @0040f260>
void __cdecl Fallin_Block_FUN_0040f260(Point2I* blockPos, sint32 unkIntensity, bool32 param_3);
// <LegoRR.exe @0040f510>
void __cdecl Fallin_Initialise(sint32 numLandSlidesTillCaveIn);
// <LegoRR.exe @0040f520>
void __cdecl Fallin_LandSlideDoCaveIn(Point2I* blockPos, sint32 unkIntensity);
// <LegoRR.exe @0040f5f0>
FlocksItem* __cdecl Flocks_LiveObject_Flocks_CreateSubdata(Vector3F* vector_1, Vector3F* vector_2, real32 turn, real32 speed, real32 tightness, real32 goalUpdate, Container* resData);
// <LegoRR.exe @0040f6e0>
void __cdecl freeNonNull(void* ptr);
// <LegoRR.exe @0040f700>
Flocks* __cdecl Flocks_LiveObject_Flocks_CreateData(Vector3F* vector_1, Vector3F* vector_2, real32 turn, real32 speed, real32 tightness, Container* resData);
// <LegoRR.exe @0040f780>
void __cdecl Flocks_FreeData(Flocks* flocksData);
// <LegoRR.exe @0040f7c0>
void __cdecl Flocks_Subdata_MathChangeRotationX(FlocksItem* flockSubdata, Vector3F* vector);
// <LegoRR.exe @0040f850>
void __cdecl Flocks_Subdata_MathChangeRotationsYZ(FlocksItem* subdata, Vector3F* ref_vector);
// <LegoRR.exe @0040fa30>
void __cdecl Flocks_Subdata_Matrix_MultRotXYZ(FlocksItem* subdata);
// <LegoRR.exe @0040fac0>
void __cdecl Flocks_Callback_SubdataMoveAndTurn(Flocks* unused_flocksData, FlocksItem* subdata, real32* pElapsed);
// <LegoRR.exe @0040fbf0>
void __cdecl Flocks_MathX_Vector3DRandomMultiply(Vector3F* out_vector, real32 x, real32 y, real32 z);
// <LegoRR.exe @0040fc30>
void __cdecl Flocks_Callback_SubdataMoveTightness(Flocks* flocksData, FlocksItem* subData, real32* pElapsed);
// <LegoRR.exe @0040fce0>
void __cdecl Flocks_SetVector2(Flocks* flocksData, Vector3F* vector2);
// <LegoRR.exe @0040fd10>
void __cdecl Flocks_Subdata_MoveAndTurn(FlocksItem* subdata, real32 elapsed);
// <LegoRR.exe @0040fd30>
void __cdecl Flocks_Subdata_UpdateMove(Flocks* flocksData, real32 elapsed);
// <LegoRR.exe @0040fd70>
void __cdecl Flocks_LiveObject_Flocks_AddSubdata(Flocks* flockData, FlocksItem* subdata);
// <LegoRR.exe @0040fd90>
FlocksItem* __cdecl Flocks_Free_SubdataRecurse(Flocks* flocksData);
// <LegoRR.exe @0040fdc0>
void __cdecl Flocks_CallbackForAllSubdata(Flocks* flockData, FlocksCallback callback, void* data);
// <LegoRR.exe @0040fdf0>
float10 __cdecl Flocks_MathX_RandRangeOne(void);
// <LegoRR.exe @0040fe00>
void __cdecl Flocks_Callback_FUN_0040fe00(Flocks* flocksData, FlocksItem* subdata, real32* param_3);
// <LegoRR.exe @0040fe80>
void __cdecl Flocks_FUN_0040fe80(Flocks* flocksData, real32 param_2);
// <LegoRR.exe @0040fea0>
void __cdecl Flocks_SetParameters1(Flocks* flocksData, real32 turn, real32 speed, real32 tightness);
// <LegoRR.exe @0040fec0>
void __cdecl Flocks_Callback_SetSubdataParametersFromGlobals(Flocks* flocksData, FlocksItem* subdata);
// <LegoRR.exe @0040ff10>
void __cdecl Flocks_SetGlobal_AndAllSubdataParameters(Flocks* flockData, real32 turn, real32 speed, real32 tightness, real32 goalUpdate);
// <LegoRR.exe @0040ff50>
void __cdecl Flocks_SetVector1(Flocks* flocksData, Vector3F* vector1);
// <LegoRR.exe @0040ff80>
void __cdecl Flocks_Callback_SetSubdataVectorC(Flocks* flocksData, FlocksItem* subdata, Vector3F* vector);
// <LegoRR.exe @0040ffa0>
void __cdecl Flocks_SetAllSubdataVectorC(Flocks* flocksData, Vector3F* vector);
// <LegoRR.exe @0040ffc0>
void __cdecl Flocks_Callback_SetSubdataVector0(Flocks* flocksData, FlocksItem* subdata, Vector3F* vector);
// <LegoRR.exe @0040ffe0>
void __cdecl Flocks_SetAllSubdataVector0(Flocks* flocksData, Vector3F* vector);
// <LegoRR.exe @00410000>
void __cdecl Flocks_Callback_FUN_00410000(Flocks* flocksData, FlocksItem* subdata, real32* pElapsed);
// <LegoRR.exe @00410160>
void __cdecl Flocks_Callback_CompareVecs_0_c(Flocks* flocksData, FlocksItem* subdata, bool32* pSuccess);
// <LegoRR.exe @004101b0>
bool32 __cdecl Flocks_CompareAllVecs_0_c(Flocks* flocksData);
// <LegoRR.exe @004101e0>
char* __cdecl replaceTextSpaces(char* str);
// <LegoRR.exe @00410250>
void __cdecl Missions_PrintF_LevelName(Font* font, sint32 x, sint32 y, char* format, ...);
// <LegoRR.exe @00410300>
void __cdecl MainMenuFull_TriggerShowCredits(void);
// <LegoRR.exe @00410320>
void __cdecl Front_PlayRockWipe_AndUnk(void);
// <LegoRR.exe @00410370>
void __cdecl Front_UnsetFlag3_005584f0(void);
// <LegoRR.exe @00410380>
ImageCacheItem* __cdecl ImageCache_FindByName(char* filename);
// <LegoRR.exe @004103c0>
ImageCacheItem* __cdecl ImageCache_Get(char* filename);
// <LegoRR.exe @00410450>
Image* __cdecl ImageCache_LoadImage(char* filename);
// <LegoRR.exe @00410490>
Font* __cdecl ImageCache_LoadFont(char* filename);
// <LegoRR.exe @004104d0>
char* __cdecl _strdup2(char* str);
// <LegoRR.exe @00410520>
MenuItemMissions* __cdecl Menu_CreateMissionsDisplay(void* value, char* string1, char* string2, sint32 param_4, sint32 param_5, sint32 param_6, sint32 param_7, sint32 param_8, sint32 param_9, sint32 param_10, sint32 param_11, sint32 param_12, void* callback, undefined4 param_14);
// <LegoRR.exe @004105c0>
void __cdecl Menu_FreeSubMenuItem_Count(sint32* param_1);
// <LegoRR.exe @00410670>
void __cdecl Missions_AddLevel(MenuItemMissions* missions, char* menuBMPName, bool32 unkMode, Font* hiFont, sint32 frontEndX, sint32 frontEndY, bool32 frontEndOpen);
// <LegoRR.exe @00410940>
MenuItemCycle* __cdecl Menu_CreateCycle(uint32 count, void* value, sint32 x2, sint32 y2, void* callback);
// <LegoRR.exe @004109d0>
void __cdecl Menu_AddCycleName(MenuItemCycle* cycleData, char* name);
// <LegoRR.exe @00410a10>
void __cdecl Menu_FreeCycle(MenuItemCycle* cycleData);
// <LegoRR.exe @00410a60>
sint32 __cdecl msx(void);
// <LegoRR.exe @00410a70>
sint32 __cdecl msy(void);
// <LegoRR.exe @00410a80>
bool32 __cdecl mslb(void);
// <LegoRR.exe @00410a90>
MenuItemTrigger* __cdecl Menu_CreateTrigger(void* value, bool32 end, void* callback);
// <LegoRR.exe @00410ac0>
MenuItemRealSlider* __cdecl Menu_CreateRealSlider(void* value, real32 lowLimit, real32 highLimit, real32 step, sint32 x2, sint32 y2, void* callback);
// <LegoRR.exe @00410b20>
MenuItemSlider* __cdecl Menu_CreateSlider(void* value, sint32 lowLimit, sint32 highLimit, sint32 x2, sint32 y2, void* callback, Image* offBarImage, Image* onBarImage, Image* leftCapImage, Image* rightCapImage, Image* loPlusImage, Image* loMinusImage, Image* hiPlusImage, Image* hiMinusImage);
// <LegoRR.exe @00410ba0>
void __cdecl Menu_FreeMenuItem(MenuItem* menuItem);
// <LegoRR.exe @00410c80>
MenuItem* __cdecl Menu_CreateBannerItem(char* banner, Font* loFont, Font* hiFont, sint32 x1, sint32 y1, MenuItemType itemType, bool32 centered, void* itemData, bool32 isNext6);
// <LegoRR.exe @00410d50>
MenuItem* __cdecl Menu_CreateImageItem(char* banner, Font* loFont, Font* hiFont, char* loImageName, char* hiImageName, sint32 x1, sint32 y1, MenuItemType itemType, bool32 centered, char* toolTipName, void* itemData);
// <LegoRR.exe @00410e60>
void __cdecl Menu_FreeSubMenu(SubMenu* submenu);
// <LegoRR.exe @00410ee0>
bool32 __cdecl Menu_LoadMenuImage(SubMenu* param_1, char* param_2, bool32 isLightImage);
// <LegoRR.exe @00411030>
SubMenu* __cdecl Menu_CreateSubMenu(char* title, char* fullName, Font* menuFont, sint32 positionX, sint32 positionY, bool32 autoCenter, bool32 displayTitle, sint32 param_8, bool32 canScroll, char* anchored_str);
// <LegoRR.exe @00411190>
bool32 __cdecl Menu_AddSubMenuItem(SubMenu* submenu, MenuItem* menuItem);
// <LegoRR.exe @00411210>
bool32 __cdecl MathX_IsPointInsideRect(sint32 ptX, sint32 ptY, sint32 rcX, sint32 rcY, sint32 rcWidth, sint32 rcHeight);
// <LegoRR.exe @00411250>
bool32 __cdecl MathX_IsPointInsideRect_OptCenterX(sint32 ptX, sint32 ptY, sint32 rcX, sint32 rcY, sint32 rcWidth, sint32 rcHeight, bool32 shouldCenterX);
// <LegoRR.exe @00411290>
sint32 __cdecl Front_SubmenuItem_CollisionCheck_FUN_00411290(SubMenu* submenu, MenuItem* item, sint32* itemData);
// <LegoRR.exe @00411420>
bool32 __cdecl Front_SubmenuItem_FUN_00411420(SubMenu* submenu, sint32 itemIndex);
// <LegoRR.exe @00411460>
bool32 __cdecl Front_Submenu_FUN_00411460(SubMenu* submenu, sint32 itemIndex, sint32* out_rcX, sint32* out_rcY, sint32* out_rcWidth, sint32* out_rcHeight);
// <LegoRR.exe @004116c0>
bool32 __cdecl Front_Submenu_FUN_004116c0(SubMenu* submenu, sint32* out_itemResult);
// <LegoRR.exe @00411770>
bool32 __cdecl Front_GetMousePressedState(void);
// <LegoRR.exe @004117a0>
bool32 __cdecl Front_Submenu_Slider_FUN_004117a0(SubMenu* param_1, sint32 param_2, sint32** param_3);
// <LegoRR.exe @00411900>
bool32 __cdecl Front_SubmenuItemCheckHasTutorialFlags(MenuItem* item);
// <LegoRR.exe @00411930>
SubMenu* __cdecl Front_Submenu_FUN_00411930(undefined4 param_1, SubMenu* submenu);
// <LegoRR.exe @00411e30>
sint32 __cdecl Input_GetKeyCharacter(sint32 diKey);
// <LegoRR.exe @00411e40>
void __cdecl FUN_00411e40(sint32 param_1, uint32 param_2, uint32 param_3, sint32 param_4, uint32 param_5);
// <LegoRR.exe @004120a0>
sint32 __cdecl Lego_CountLinkedStruct1C_At40(sint32 param_1);
// <LegoRR.exe @004120c0>
bool32 __cdecl randomBool_1_In_400(void);
// <LegoRR.exe @004120e0>
void __cdecl Front_FUN_004120e0(sint32 param_1);
// <LegoRR.exe @00412380>
void __cdecl Front_UnkDraw_FUN_00412380(sint32 param_1, sint32 param_2, undefined4* param_3, sint32* param_4, sint32 param_5, sint32 param_6);
// <LegoRR.exe @00412420>
void __cdecl SaveMenu_UnkCfgLoad_FUN_00412420(sint32 param_1, sint32 param_2, undefined4 param_3, sint32 param_4);
// <LegoRR.exe @00412680>
void __cdecl Front_FUN_00412680(SubMenu** pSubmenu, sint32* param_2, sint32* param_3);
// <LegoRR.exe @00412900>
void __cdecl Struct728_FUN_00412900(SubMenu** pSubmenu);
// <LegoRR.exe @00412a20>
void __cdecl SaveMenu_Draw_FUN_00412a20(sint32 param_1, bool32 param_2);
// <LegoRR.exe @00412b30>
SubMenu* __cdecl SaveMenu_FUN_00412b30(undefined4 param_1, SubMenu* submenu, bool32* out_bool);
// <LegoRR.exe @004138a0>
void __cdecl Menu_Submenu_FUN_004138a0(SubMenu* submenu);
// <LegoRR.exe @00413990>
void __cdecl Front_LoadSaveSlotImages(void);
// <LegoRR.exe @00413a80>
void __cdecl Front_FreeSaveSlotImages(void);
// <LegoRR.exe @00413ab0>
void __cdecl Front_ScreenSubmenuLoop(SubMenu* submenu);
// <LegoRR.exe @00413d50>
void __cdecl Front_RunScreenMenu(MenuCollection* menuCol, sint32 submenuIndex);
// <LegoRR.exe @00413d90>
MenuItemType __cdecl Menu_ParseMenuControlType(char* controlName);
// <LegoRR.exe @00413e30>
char* __cdecl stringReplaceChar(char* text, char origChar, char newChar);
// <LegoRR.exe @00413e60>
sint32 __cdecl Menu_GetOverlayType(char** param_1);
// <LegoRR.exe @00413ec0>
MenuOverlay* __cdecl Menu_CreateOverlay(char* filename, MenuOverlay** ref_overlay, sint32 positionX, sint32 positionY, SFXType sfxType);
// <LegoRR.exe @00413f40>
void __cdecl Menu_LoadSliderImages(sint32 numParts, char** stringParts, Image** outImages);
// <LegoRR.exe @00413fa0>
MenuCollection* __cdecl Menu_CreateCollection(uint32 count);
// <LegoRR.exe @00413ff0>
MenuCollection* __cdecl Menu_ParseMenu(CFGProperty* root_unused, char* menuName, void* dst, void* callback, ...);
// <LegoRR.exe @00414bc0>
sint32 __cdecl Menu_GetSubMenuIDByName(MenuCollection* menuCol, char* name);
// <LegoRR.exe @00414c10>
bool32 __cdecl FrontEnd_IsIntrosEnabled(void);
// <LegoRR.exe @00414c60>
void __cdecl PausedMenu_SliderBrightness(sint32 slider_0_10);
// <LegoRR.exe @00414d10>
void __cdecl PausedMenu_SliderSoundVolume(sint32 slider_0_10);
// <LegoRR.exe @00414d20>
void __cdecl PausedMenu_SliderMusicVolume(sint32 slider_0_10);
// <LegoRR.exe @00414d40>
sint32 __cdecl PausedMenu_CalcSliderCDVolume(void);
// <LegoRR.exe @00414d80>
void __cdecl PausedMenu_CycleWallDetail(sint32 cycle_High_Low);
// <LegoRR.exe @00414db0>
void __cdecl PausedMenu_CycleAutoGameSpeed(sint32 cycle_On_Off);
// <LegoRR.exe @00414dd0>
void __cdecl PausedMenu_CycleMusic(sint32 cycle_On_Off);
// <LegoRR.exe @00414df0>
void __cdecl PausedMenu_CycleSound(sint32 cycle_On_Off);
// <LegoRR.exe @00414e10>
void __cdecl PausedMenu_CycleHelpWindow(sint32 cycle_Off_On);
// <LegoRR.exe @00414e40>
void __cdecl PausedMenu_TriggerReplayObjective(void);
// <LegoRR.exe @00414e50>
void __cdecl PausedMenu_SliderGameSpeed(sint32 slider_0_5);
// <LegoRR.exe @00414ec0>
void __cdecl FrontEnd_UpdateSliderGameSpeed(void);
// <LegoRR.exe @00414f60>
sint32 __cdecl PausedMenu_CalcSliderGameSpeed(void);
// <LegoRR.exe @00414fe0>
void __cdecl Front_TutorialsCallback_FUN_00414fe0(real32 elapsedAbs, sint32 saveIndex);
// <LegoRR.exe @00415080>
void __cdecl Front_UpdatePausedMenuSliders(void);
// <LegoRR.exe @004150c0>
void __cdecl SaveMenu_TriggerBack(void);
// <LegoRR.exe @00415150>
void __cdecl Debug_ProgrammerMode11_LoadLevel(void);
// <LegoRR.exe @004151f0>
void __cdecl Save_GetLevelCompleteWithPoints(SaveData* saveData, char* out_buffer);
// <LegoRR.exe @00415290>
void __cdecl FrontEnd_UpdateGameSpeedSliderLevel(void);
// <LegoRR.exe @004152a0>
bool32 __cdecl Front_FUN_004152a0(real32 elapsed, bool32 param_2);
// <LegoRR.exe @004153e0>
bool32 __cdecl LevelCollection_Load(CFGProperty* root, LevelCollection* levelCol, char* levelKey);
// <LegoRR.exe @00415630>
void __cdecl Front_PlayMovie(Movie_t* mov, bool32 skippable);
// <LegoRR.exe @004156f0>
void __cdecl Front_ShowIntroSplash(char* imageKey, bool32 skippable, char* timeKey);
// <LegoRR.exe @00415840>
void __cdecl Front_ShowIntroMovie(char* aviKey, bool32 skippable);
// <LegoRR.exe @004158c0>
void __cdecl Level_DoVideo__004158c0(char* levelName, sint32 param_2);
// <LegoRR.exe @00415940>
void __cdecl Menu_LoadAllMissions(MenuCollection* mainMenuCol);
// <LegoRR.exe @00415c20>
void __cdecl Save_ClearSaveNumber(void);
// <LegoRR.exe @00415c30>
void __cdecl MenuTextWindow_Load(CFGProperty* root, char* rootPath, MenuTextWindow* menuWnd);
// <LegoRR.exe @00416080>
bool32 __cdecl Missions_StreamLevelNameSFX(sint32 levelNumber);
// <LegoRR.exe @004160d0>
bool32 __cdecl Missions_StreamTutorialLevelNameSFX(sint32 levelNumber);
// <LegoRR.exe @00416120>
void __cdecl Menu_LoadMenus(CFGProperty* root);
// <LegoRR.exe @00416840>
void __cdecl PausedMenu_UpdateUnkStruct_FromSliderValues(void);
// <LegoRR.exe @00416870>
void __cdecl Front_SetOptionParameters(bool32 fromSave, bool32 reset);
// <LegoRR.exe @004168f0>
void __cdecl Menu_FUN_004168f0(ScreenMenuType menuId);
// <LegoRR.exe @00416bb0>
bool32 __cdecl Front_RunScreenMenuType(ScreenMenuType screenMenuType);
// <LegoRR.exe @00416c30>
bool32 __cdecl Front_IsFrontEndEnabled(void);
// <LegoRR.exe @00416c80>
bool32 __cdecl Front_IsMenuLabelUnkValue1_NotM1(void);
// <LegoRR.exe @00416c90>
bool32 __cdecl Front_GetUnkTutoOrMissions(void);
// <LegoRR.exe @00416ca0>
char* __cdecl Front_GetSelectedLevel(void);
// <LegoRR.exe @00416d00>
sint32 __cdecl Front_IsTriggerAppQuit(void);
// <LegoRR.exe @00416d10>
bool32 __cdecl Front_IsTriggerMissionQuit(void);
// <LegoRR.exe @00416d20>
bool32 __cdecl Front_IsTriggerMissionRestart(void);
// <LegoRR.exe @00416d30>
LevelCollection* __cdecl LevelCollections_GetTutorialOrMissions(void);
// <LegoRR.exe @00416d50>
sint32 __cdecl LevelCollection_IndexOf(LevelCollection* levelCol, char* levelName);
// <LegoRR.exe @00416da0>
void __cdecl LevelCollections_ClearAllLinks(void);
// <LegoRR.exe @00416e00>
void __cdecl LevelCollection_SetLinked(LevelCollection* levelCol, char* levelName, bool32 isLinked);
// <LegoRR.exe @00416e70>
bool32 __cdecl LevelCollection_IsLinked(LevelCollection* levelCol, char* levelName);
// <LegoRR.exe @00416ee0>
void __cdecl LevelCollection_SetIdentifier(LevelCollection* levelCol, char* levelName, LevelIdentifier* identifier);
// <LegoRR.exe @00416f50>
LevelIdentifier* __cdecl LevelCollection_GetIdentifier(LevelCollection* levelCol, char* levelName);
// <LegoRR.exe @00416fc0>
LevelIdentifier* __cdecl LevelCollection_LoadLinks(LevelCollection* levelCol, char* levelName);
// <LegoRR.exe @004170f0>
bool32 __cdecl LevelIdentifier_RecurseCallbacks(LevelIdentifier* identifier, LevelIdentifierCallback callback, void* data);
// <LegoRR.exe @00417170>
bool32 __cdecl LevelIdentifier_Callback_IncCount(LevelIdentifier* identifier, sint32* pCount);
// <LegoRR.exe @00417180>
bool32 __cdecl LevelIdentifier_SearchCallback_FUN_00417180(LevelIdentifier* identifier, SearchLevelIdentifier_10* search);
// <LegoRR.exe @004171b0>
LevelIdentifier* __cdecl LevelIdentifier_FindByUnkCallbacks_FUN_004171b0(LevelIdentifier* identifier, sint32 searchIndex);
// <LegoRR.exe @00417200>
sint32 __cdecl LevelIdentifier_FUN_00417200(LevelIdentifier* identifier, sint32 param_2);
// <LegoRR.exe @00417220>
void __cdecl LevelIdentifier_FUN_00417220(LevelIdentifier* identifier, sint32* ref_struct14_2, bool32 param_3);
// <LegoRR.exe @00417310>
void __cdecl LevelIdentifier_FUN_00417310(LevelIdentifier* identifier, sint32 param_2, LevelCollection* levelCol, MenuItemTrigger* param_4, undefined4 param_5);
// <LegoRR.exe @00417360>
sint64 __cdecl Missions_SaveData_GetUnkField_FUN_00417360(sint32 index, SaveData* saveData);
// <LegoRR.exe @00417390>
void __cdecl Missions_StartMenuItemCallback_uses_testercall(real32 elapsed, sint32 searchIndex);
// <LegoRR.exe @00417630>
void __cdecl Missions_TutorialMenuItemCallback(real32 elapsed, sint32 searchIndex);
// <LegoRR.exe @00417710>
bool32 __cdecl Missions_AddLevelCallback(LevelIdentifier* identifier, sint32* search);
// <LegoRR.exe @004178e0>
void __cdecl MainMenuFull_AddMissionsDisplay(sint32 valueOffset, LevelIdentifier* startIdentifier, sint32* pLevelCount, SubMenu* in_submenu, undefined4 param_5, undefined4 param_6, void* callback);
// <LegoRR.exe @004179c0>
bool32 __cdecl Save_ReadSaveFile(uint32 saveIndex, SaveData* out_saveData, bool32 param_3);
// <LegoRR.exe @00417b00>
bool32 __cdecl Save_SPrintfFileUnkWrite__00417b00(uint32 saveNumber, SaveData* saveData);
// <LegoRR.exe @00417d20>
void __cdecl Front_StructB8_HasClearSaves_FUN_00417d20(void);
// <LegoRR.exe @00417d80>
SaveData* __cdecl Save_GetSaveData_OfNumber(sint32 saveIndex);
// <LegoRR.exe @00417da0>
SaveData* __cdecl Save_GetCurrentSaveData(void);
// <LegoRR.exe @00417dc0>
sint32 __cdecl Save_GetSaveNumber(void);
// <LegoRR.exe @00417dd0>
void __cdecl Save_SetSaveNumber(sint32 saveIndex);
// <LegoRR.exe @00417de0>
void __cdecl Front_LevelSave_Unk_FUN_00417de0(uint32 levelIndex);
// <LegoRR.exe @00417e50>
void __cdecl SaveStruct18_FUN_00417e50(SaveStruct_18* param_1);
// <LegoRR.exe @00417e70>
bool32 __cdecl Front_CopyRewardToSave(sint32 levelIndex, RewardLevel* reward);
// <LegoRR.exe @00417ec0>
sint32 __cdecl LevelIndex_FUN_00417ec0(sint32 levelIndex);
// <LegoRR.exe @00417ef0>
bool32 __cdecl Front_FUN_00417ef0(void);
// <LegoRR.exe @00417f10>
bool32 __cdecl Front_GetBool_00558500(void);
// <LegoRR.exe @00417f20>
void __cdecl Front_SetBool_00558500(bool32 state);
// <LegoRR.exe @00417f30>
void __cdecl Front_FUN_00417f30(void);
// <LegoRR.exe @00417f70>
void __cdecl Save_CopyData(SaveData* out_saveData);
// <LegoRR.exe @00417ff0>
void __cdecl Save_OverwriteData(SaveData* saveData);
// <LegoRR.exe @00418040>
void __cdecl Front_SetBool_0055881c(bool32 state);
// <LegoRR.exe @00418050>
bool32 __cdecl Front_SaveData_FUN_00418050(void);
// <LegoRR.exe @004180c0>
void __cdecl HelpWindow_SetFont(Font* font);
// <LegoRR.exe @004180d0>
void __cdecl HelpWindow_ClearFlag1(void);
// <LegoRR.exe @004180e0>
void __cdecl HelpWindow_Initialise(CFGProperty* root, char* rootPath);
// <LegoRR.exe @00418380>
void __cdecl HelpWindow_LoadLevelsInfo(CFGProperty* root, char* rootPath);
// <LegoRR.exe @00418520>
void __cdecl HelpWindow_LoadButtons(CFGProperty* root, char* rootPath);
// <LegoRR.exe @00418730>
void __cdecl HelpWindow_IfFlag4_AndParam_Clear1_Set2_Else_Clear3(bool32 state);
// <LegoRR.exe @00418760>
void __cdecl HelpWindow_RecallDependencies(ObjectType objType, sint32 objIndex, sint32 objLevel, bool32 noHelpWindow);
// <LegoRR.exe @00418850>
void __cdecl HelpWindow_Object_Unlock(ObjectType objType, sint32 objIndex, sint32 objLevel);
// <LegoRR.exe @00418900>
void __cdecl HelpWindow_Close_FUN_00418900(void);
// <LegoRR.exe @00418930>
void __cdecl HelpWindow_FUN_00418930(void);
// <LegoRR.exe @00418cd0>
bool32 __cdecl HelpWindow_FUN_00418cd0(uint32 mouseX, uint32 mouseY, bool32 leftButton, bool32 leftLast, bool32 leftReleased, real32 elapsed);
// <LegoRR.exe @00418eb0>
void __cdecl HelpWindow_ToolTip_FUN_00418eb0(sint32 param_1);
// <LegoRR.exe @00418ef0>
bool32 __cdecl HelpWindow_FUN_00418ef0(sint32 param_1, sint32 param_2, sint32 param_3);
// <LegoRR.exe @00418f60>
void __cdecl HelpWindow_FUN_00418f60(undefined4 param_1, real32 elapsed);
// <LegoRR.exe @00419030>
void __cdecl HelpWindow_DrawButtons(void);
// <LegoRR.exe @00419080>
Image* __cdecl HelpWindow_GetButtonImage(sint32 buttonIndex);
// <LegoRR.exe @004190d0>
bool32 __cdecl HelpWindow_IsEnabled_AndFlags_3_AndNoTutorialFlags(void);
// <LegoRR.exe @00419120>
bool32 __cdecl HelpWindow_IsEnabled(void);
// <LegoRR.exe @00419130>
void __cdecl HelpWindow_SetEnabled(bool32 toggle, bool32 enable);
// <LegoRR.exe @00419160>
void __cdecl Info_Initialise(Font* font);
// <LegoRR.exe @00419310>
bool32 __cdecl Info_GetInfoType(char* infoName, InfoType* out_infoType);
// <LegoRR.exe @00419350>
void* __cdecl Info_GetTypePtr4(InfoType infoType);
// <LegoRR.exe @00419360>
void __cdecl Info_SetOverFlowImageFile(char* filename);
// <LegoRR.exe @00419380>
void __cdecl Info_SetAutoGameSpeed(bool32 autoOn);
// <LegoRR.exe @004193a0>
void __cdecl Info_SetTypeChangeGameSpeed(InfoType infoType, bool32 changeSpeedOn);
// <LegoRR.exe @004193e0>
void __cdecl Info_SetTypeText(InfoType infoType, char* text);
// <LegoRR.exe @00419420>
void __cdecl Info_SetTypeFlag_20000(InfoType infoType, bool32 setFlag20000);
// <LegoRR.exe @00419460>
void __cdecl Info_SetText_internal(char* text, char** pInfoText);
// <LegoRR.exe @00419580>
void __cdecl Info_SetTypeImageFile(InfoType infoType, char* filename);
// <LegoRR.exe @004195b0>
void __cdecl Info_SetTypeSFX(InfoType infoType, SFXType sfxType);
// <LegoRR.exe @004195d0>
bool32 __cdecl Info_EnumerateMessageInstances(sint32 handle, InfoEnumerateCallback callback, void* data);
// <LegoRR.exe @00419620>
void __cdecl Info_AddMessageInstance(sint32 handle, InfoMessageInstance* instance);
// <LegoRR.exe @004196b0>
InfoMessageInstance* __cdecl Info_GetMessageInstance(sint32 handle, sint32 instanceIndex);
// <LegoRR.exe @004196e0>
InfoMessageInstance* __cdecl Info_RemoveMessageInstance(sint32 handle, sint32 instanceIndex);
// <LegoRR.exe @00419740>
bool32 __cdecl Info_LiveObject_Release_internal_FUN_00419740(InfoMessageInstance* instance, SearchInfoObject_8* search);
// <LegoRR.exe @00419760>
void __cdecl Info_RemoveAllForObject(LiveObject* liveObj);
// <LegoRR.exe @004197f0>
bool32 __cdecl Info_Callback_FindBlockPos(InfoMessageInstance* infoInstance, SearchInfoBlockPos_8* search);
// <LegoRR.exe @00419820>
void __cdecl Info_RemoveAllAtBlockPos(Point2I* blockPos);
// <LegoRR.exe @004198d0>
bool32 __cdecl Info_Callback_FindObjectAndBlockPos(InfoMessageInstance* instance, SearchInfoObjectBlockPos_8* search);
// <LegoRR.exe @00419920>
bool32 __cdecl Info_HasTypeAtObjectOrBlockPos(InfoType infoType, LiveObject* opt_liveObj, Point2I* opt_blockPos);
// <LegoRR.exe @004199b0>
InfoMessageInstance* __cdecl Info_CreateInstance(Point2I* opt_blockPos, LiveObject* opt_liveObj, char* opt_text);
// <LegoRR.exe @00419a10>
void __cdecl Info_SetFlag4(bool32 state);
// <LegoRR.exe @00419a30>
bool32 __cdecl Info_HasTypeText(InfoType infoType);
// <LegoRR.exe @00419a50>
sint32 __cdecl Info_FindExistingMessageType(InfoType infoType);
// <LegoRR.exe @00419a80>
float10 __cdecl Info_FUN_00419a80(void);
// <LegoRR.exe @00419ab0>
void __cdecl Info_Send(InfoType infoType, char* opt_text, LiveObject* opt_liveObj, Point2I* opt_blockPos);
// <LegoRR.exe @00419cd0>
void __cdecl Info_GotoFirst(void);
// <LegoRR.exe @00419d10>
void __cdecl Info_UpdateMessage(uint32 handle);
// <LegoRR.exe @00419d90>
void __cdecl Info_PopFirstMessage(void);
// <LegoRR.exe @00419db0>
void __cdecl Info_RemoveMessage(uint32 handle);
// <LegoRR.exe @00419e40>
void __cdecl Info_ClearAllMessages(void);
// <LegoRR.exe @00419e60>
void __cdecl Info_Draw(real32 elapsedAbs);
// <LegoRR.exe @00419fb0>
void __cdecl Info_DrawPanel(real32 elapsedAbs);
// <LegoRR.exe @0041a0d0>
bool32 __cdecl Info_Update_FUN_0041a0d0(sint32 mouseX, sint32 mouseY, bool32 leftReleased);
// <LegoRR.exe @0041a180>
void __cdecl Info_FUN_0041a180(void);
// <LegoRR.exe @0041a1c0>
void __cdecl Info_UpdateInt6EC_FromScrollInfo(void);
// <LegoRR.exe @0041a1f0>
void __cdecl Info_FUN_0041a1f0(real32 elapsed);
// <LegoRR.exe @0041a220>
Font* __cdecl Interface_GetFont_FUN_004ddd58(void);
// <LegoRR.exe @0041a230>
void __cdecl Interface_Initialise(uint32 x_565, uint32 y_18, Font* font);
// <LegoRR.exe @0041a590>
void __cdecl Interface_AddAllMenuItems(void);
// <LegoRR.exe @0041a700>
void __cdecl Interface_AddMenuItem(InterfaceMenuType interfaceMenuType, sint32 numParams, ...);
// <LegoRR.exe @0041a780>
void __cdecl Interface_FreeInterfaceIcons(void);
// <LegoRR.exe @0041a850>
void __cdecl Interface_LevelFree_FUN_0041a850(void);
// <LegoRR.exe @0041a8c0>
void __cdecl Interface_ResetUnkValues(void);
// <LegoRR.exe @0041a8f0>
bool32 __cdecl Interface_GetMenuItemType(char* menuItemName, sint32* out_menuItemType);
// <LegoRR.exe @0041a930>
void __cdecl Interface_InitSubmenuIconTables(void);
// <LegoRR.exe @0041aa30>
void __cdecl Interface_LoadInterfaceBuildImages(CFGProperty* root, char* keyBasePath);
// <LegoRR.exe @0041acd0>
void __cdecl Interface_LoadInterfaceImages(CFGProperty* root, char* keyBasePath);
// <LegoRR.exe @0041af00>
void __cdecl Interface_LoadInterfaceSurroundImages(CFGProperty* root, char* keyBasePath);
// <LegoRR.exe @0041b0e0>
void __cdecl Interface_LoadInterfaceBackButton(CFGProperty* root, char* keyBasePath);
// <LegoRR.exe @0041b1a0>
void __cdecl Interface_LoadInterfaceDependencies_PlusMinus(char* plus, char* minus);
// <LegoRR.exe @0041b200>
void __cdecl Interface_OpenMenu_FUN_0041b200(InterfaceMenuType interfaceMenuType, Point2I* blockPos);
// <LegoRR.exe @0041b230>
void __cdecl Interface_SelectBlock(InterfaceMenuType interfaceMenuType, Point2I* blockPos);
// <LegoRR.exe @0041b2f0>
sint32 __cdecl Interface_FUN_0041b2f0(InterfaceMenuType interfaceMenuType);
// <LegoRR.exe @0041b3a0>
bool32 __cdecl Interface_NotMainOrFirstPersonMenu(InterfaceMenuType interfaceMenuType);
// <LegoRR.exe @0041b3c0>
void __cdecl Interface_FUN_0041b3c0(void);
// <LegoRR.exe @0041b5b0>
bool32 __cdecl Interface_FUN_0041b5b0(InterfaceMenuType menuIcon, undefined* callback, void* context);
// <LegoRR.exe @0041b730>
bool32 __cdecl Interface_Callback_FUN_0041b730(MenuIcon menuIcon, uint32 param_2, sint32 param_3, real32* param_4);
// <LegoRR.exe @0041b860>
void __cdecl Interface_FUN_0041b860(real32 elapsedAbs);
// <LegoRR.exe @0041b8e0>
bool32 __cdecl Interface_GetBool_004ded1c(void);
// <LegoRR.exe @0041b8f0>
MenuIcon __cdecl Interface_GetPrimaryUnit_PowerIcon(MenuIcon* ref_menuIcon);
// <LegoRR.exe @0041b940>
void __cdecl Interface_FUN_0041b940(real32 elapsedAbs);
// <LegoRR.exe @0041b9c0>
void __cdecl Interface_SetDat_004df1f4(SFXType param_1);
// <LegoRR.exe @0041b9d0>
bool32 __cdecl Interface_DoSomethingWithRenameReplace(uint32 param_1, uint32 param_2, sint32 param_3, sint32 param_4, sint32 param_5);
// <LegoRR.exe @0041c0f0>
bool32 __cdecl Interface_FUN_0041c0f0(uint32 param_1, uint32 param_2, undefined4* param_3, undefined4* param_4, undefined4* param_5);
// <LegoRR.exe @0041c240>
bool32 __cdecl Interface_Callback_FUN_0041c240(MenuIcon in_menuIcon, ObjectType objType, sint32 objIndex, uint32* param_4);
// <LegoRR.exe @0041c370>
void __cdecl Interface_DoF2InterfaceKeyAction(void);
// <LegoRR.exe @0041c3a0>
bool32 __cdecl Interface_CallbackDoMenuIconKeyAction(MenuIcon menuIcon, ObjectType objType, sint32 objIndex);
// <LegoRR.exe @0041c420>
void __cdecl Interface_FUN_0041c420(MenuIcon menuIcon, ObjectType objType, sint32 objIndex, real32* param_4);
// <LegoRR.exe @0041c610>
bool32 __cdecl Interface_FUN_0041c610(MenuIcon menuIcon, sint32 param_2, sint32 param_3, sint32 param_4, sint32 param_5);
// <LegoRR.exe @0041c6e0>
void __cdecl Interface_FUN_0041c6e0(MenuIcon menuIcon);
// <LegoRR.exe @0041c730>
void __cdecl Interface_FUN_0041c730(ObjectType objType, sint32 objIndex);
// <LegoRR.exe @0041c820>
bool32 __cdecl Interface_FUN_0041c820(MenuIcon menuIcon, bool32 param_2);
// <LegoRR.exe @0041c880>
bool32 __cdecl Interface_FUN_0041c880(ObjectType objType, sint32 objIndex, bool32 param_3);
// <LegoRR.exe @0041c920>
void __cdecl Interface_FUN_0041c920(MenuIcon menuIcon, bool32 setFlag8);
// <LegoRR.exe @0041c950>
void __cdecl Interface_FUN_0041c950(ObjectType objType, sint32 objIndex, bool32 param_3);
// <LegoRR.exe @0041c990>
bool32 __cdecl Interface_FUN_0041c990(MenuIcon menuIcon);
// <LegoRR.exe @0041c9a0>
bool32 __cdecl Interface_FUN_0041c9a0(ObjectType objType, sint32 objIndex);
// <LegoRR.exe @0041c9e0>
Image* __cdecl Interface_FUN_0041c9e0(MenuIcon menuIcon);
// <LegoRR.exe @0041ca20>
Image* __cdecl Interface_GetBuildImageByObjectType(ObjectType objType, sint32 objIndex);
// <LegoRR.exe @0041cac0>
Image* __cdecl Interface_GetObjectBuildImage(ObjectType objType, sint32 objIndex, bool32 param_3);
// <LegoRR.exe @0041cbb0>
void __cdecl Interface_SetDat_004decd8_004decdc(MenuIcon menuIcon, ObjectType objType, sint32 objIndex);
// <LegoRR.exe @0041cc10>
void __cdecl Interface_FUN_0041cc10(Point2F* point, uint32 unkWidth, uint32 unkHeight);
// <LegoRR.exe @0041cc60>
void __cdecl Interface_Front_DrawLineListUnk_FUN_0041cc60(Area2F* rect);
// <LegoRR.exe @0041cdd0>
void __cdecl Interface_ChangeMenu_IfVehicleMounted_IsLiveObject(LiveObject* liveObj);
// <LegoRR.exe @0041ce50>
void __cdecl Interface_ChangeMenu_IfPrimarySelectedVehicle_IsLiveObject(LiveObject* liveObj);
// <LegoRR.exe @0041ceb0>
void __cdecl Interface_BackToMain_IfSelectedWall_IsBlockPos(Point2I* blockPos);
// <LegoRR.exe @0041cee0>
void __cdecl Interface_BackToMain_IfSelectedGroundOrConstruction_IsBlockPos(Point2I* blockPos);
// <LegoRR.exe @0041cf10>
void __cdecl Interface_IfSelectedRubble_IsBlockPos(Point2I* blockPos);
// <LegoRR.exe @0041cf40>
void __cdecl Interface_BackToMain_IfLiveObject_IsSelected_OrFlags3_200000(LiveObject* liveObj);
// <LegoRR.exe @0041cf70>
bool32 __cdecl Interface_HandleIcon_FUN_0041cf70(MenuIcon menuIcon);
// <LegoRR.exe @0041dbd0>
bool32 __cdecl Interface_DoAction_FUN_0041dbd0(MenuIcon menuIcon);
// <LegoRR.exe @0041e680>
void __cdecl Interface_BackToMain(void);
// <LegoRR.exe @0041e6a0>
void __cdecl Interface_SetIconFlash(MenuIcon menuIcon, bool32 flash);
// <LegoRR.exe @0041e6d0>
void __cdecl Interface_SetSubmenuIconFlash(ObjectType objType, sint32 objIndex, bool32 flash);
// <LegoRR.exe @0041e710>
LiveObject* __cdecl Interface_GetPrimarySelectedUnit(void);
// <LegoRR.exe @0041e720>
sint32 __cdecl Interface_SetIconClicked(MenuIcon menuIcon, sint32 clickedCount);
// <LegoRR.exe @0041e740>
sint32 __cdecl Interface_GetIconClicked(MenuIcon menuIcon);
// <LegoRR.exe @0041e750>
sint32 __cdecl Interface_SetSubmenuIconClicked(ObjectType objType, sint32 objIndex, sint32 clickedCount);
// <LegoRR.exe @0041e790>
sint32 __cdecl Interface_GetSubmenuIconClicked(ObjectType objType, sint32 objIndex);
// <LegoRR.exe @0041e7c0>
bool32 __cdecl Interface_SetAdvisorPointToFashingIcon(MenuIcon menuIcon, bool32 setFlag40);
// <LegoRR.exe @0041e800>
AdvisorType __cdecl Interface_GetAdvisorType_FromIcon(MenuIcon menuIcon);
// <LegoRR.exe @0041e8c0>
bool32 __cdecl Interface_FUN_0041e8c0(ObjectType objType, sint32 objIndex);
// <LegoRR.exe @0041e900>
void __cdecl Interface_SetUnkPositions1(uint32 x1_565, uint32 y1_18, uint32 x2_appWidthPlus10, uint32 y2_18, real32 param_5);
// <LegoRR.exe @0041e980>
void __cdecl Interface_UnkSlideOffScreen_FUN_0041e980_internal(InterfaceMenuType interfaceMenuType, Point2I* position);
// <LegoRR.exe @0041e9f0>
void __cdecl Interface_FUN_0041e9f0(real32 elapsedAbs);
// <LegoRR.exe @0041eb60>
void __cdecl Interface_FUN_0041eb60(sint32 param_1, sint32 param_2, Point2F* param_3);
// <LegoRR.exe @0041ebd0>
void __cdecl Interface_FUN_0041ebd0(real32 param_1, real32 param_2);
// <LegoRR.exe @0041ed90>
void __cdecl Interface_SetFloatTo25_004df1ec_AndUnsetFlags800_004df1f8(void);
// <LegoRR.exe @0041edb0>
bool32 __cdecl Interface_FUN_0041edb0(uint32 param_1, uint32 param_2, real32 param_3, real32 param_4, undefined4* param_5, undefined4* param_6, undefined4* param_7);
// <LegoRR.exe @0041f030>
bool32 __cdecl Interface_Object_FindTeleporter_FUN_0041f030(ObjectType objType, sint32 objIndex);
// <LegoRR.exe @0041f0c0>
bool32 __cdecl Interface_LiveObject_CallbackCheck_FUN_0041f0c0(LiveObject* liveObj, ObjectType* search);
// <LegoRR.exe @0041f160>
bool32 __cdecl Interface_FUN_0041f160(void);
// <LegoRR.exe @0041f1a0>
bool32 __cdecl Interface_FUN_0041f1a0(undefined4 param_1);
// <LegoRR.exe @0041f1e0>
bool32 __cdecl Interface_FUN_0041f1e0(void);
// <LegoRR.exe @0041f220>
bool32 __cdecl Interface_FUN_0041f220(undefined4 param_1, undefined4 param_2);
// <LegoRR.exe @0041f270>
bool32 __cdecl Interface_FUN_0041f270(undefined4 param_1);
// <LegoRR.exe @0041f2c0>
bool32 __cdecl Interface_LiveObject_Callback_FUN_0041f2c0(LiveObject* liveObj, Point2I* param_2);
// <LegoRR.exe @0041f2f0>
bool32 __cdecl Interface_ReqestDigBlock(Point2I* blockPos);
// <LegoRR.exe @0041f310>
bool32 __cdecl Interface_LiveObjectCallback_RequestReinforceBlock(LiveObject* liveObj, Point2I* blockPos);
// <LegoRR.exe @0041f330>
bool32 __cdecl Interface_RequestReinforceBlock(Point2I* blockPos);
// <LegoRR.exe @0041f350>
bool32 __cdecl Interface_DoSelectedUnits_Callback(undefined* callback, sint32 lpContext);
// <LegoRR.exe @0041f3a0>
bool32 __cdecl Interface_LiveObjectCallback_FUN_0041f3a0(LiveObject* liveObj);
// <LegoRR.exe @0041f3c0>
bool32 __cdecl Interface_LiveObjectCallback_IsEnergyLessThan100(LiveObject* liveObj);
// <LegoRR.exe @0041f3e0>
bool32 __cdecl Interface_LiveObjectCallback_IsHealthLessThan100(LiveObject* liveObj);
// <LegoRR.exe @0041f400>
bool32 __cdecl Interface_LiveObjectCallback_FUN_0041f400(LiveObject* liveObj);
// <LegoRR.exe @0041f520>
bool32 __cdecl Interface_LiveObjectCallback_FUN_0041f520(LiveObject* liveObj);
// <LegoRR.exe @0041f540>
bool32 __cdecl Interface_LiveObjectCallback_GoEatIfEnergyIsLessThan100(LiveObject* liveObj);
// <LegoRR.exe @0041f570>
bool32 __cdecl Interface_LiveObjectCallback_GoRepairIfHealthLessThan100(LiveObject* liveObj);
// <LegoRR.exe @0041f5a0>
bool32 __cdecl Interface_LiveObjectCallback_DoesNotHaveToolEquipped(LiveObject* liveObj, ToolType toolType);
// <LegoRR.exe @0041f5c0>
bool32 __cdecl Interface_LiveObjectCallback_GoGetToolIfNotEquipped(LiveObject* liveObj, ToolType toolType);
// <LegoRR.exe @0041f5f0>
bool32 __cdecl Interface_LiveObjectCallback_FUN_0041f5f0(LiveObject* liveObj);
// <LegoRR.exe @0041f650>
bool32 __cdecl Interface_FUN_0041f650(uint32 param_1);
// <LegoRR.exe @0041f670>
bool32 __cdecl Interface_Block_FUN_0041f670(Point2I* blockPos);
// <LegoRR.exe @0041f750>
bool32 __cdecl Interface_LiveObjectCallback_HasToolEquipped_2(LiveObject* liveObj, ToolType toolType);
// <LegoRR.exe @0041f770>
bool32 __cdecl Interface_LiveObjectCallback_FUN_0041f770(LiveObject* liveObj);
// <LegoRR.exe @0041f7a0>
void __cdecl Level_IncCrystals(void);
// <LegoRR.exe @0041f7b0>
void __cdecl Level_SubtractCrystals(sint32 crystalCount);
// <LegoRR.exe @0041f7d0>
void __cdecl Level_AddDrainedCrystals(sint32 drainedCrystalCount);
// <LegoRR.exe @0041f810>
sint32 __cdecl Level_GetCrystalCount(bool32 includeDrained);
// <LegoRR.exe @0041f830>
sint32 __cdecl Level_GetOreCount(bool32 isProcessed);
// <LegoRR.exe @0041f850>
void __cdecl Level_AddToField9c(sint32 value);
// <LegoRR.exe @0041f870>
void __cdecl Game_SetFlag1_20000_unkCameraRadarHasTrackObj(bool32 state);
// <LegoRR.exe @0041f8a0>
bool32 __cdecl Game_IsNoclipOn(void);
// <LegoRR.exe @0041f8b0>
void __cdecl Level_IncField94(void);
// <LegoRR.exe @0041f8c0>
void __cdecl Level_IncFieldA8(void);
// <LegoRR.exe @0041f8d0>
void __cdecl Level_IncOre(OreType isProcessed);
// <LegoRR.exe @0041f910>
void __cdecl Level_SubtractOre(bool32 isProcessed, sint32 oreCount);
// <LegoRR.exe @0041f950>
bool32 __cdecl Gods_Go(char* programName);
// <LegoRR.exe @0041f9b0>
void __cdecl Lego_SetLoadFlag_StartTeleporter(void);
// <LegoRR.exe @0041fa70>
float10 __cdecl Game_GetGameSpeed(void);
// <LegoRR.exe @0041fa80>
bool32 __cdecl Lego_Initialise(void);
// <LegoRR.exe @00422780>
void __cdecl Lego_LoadMiscObjects(CFGProperty* root);
// <LegoRR.exe @00422fb0>
Container* __cdecl Lego_GetCurrentCamera_Container(void);
// <LegoRR.exe @00422fe0>
float10 __cdecl Lego_GetElapsedAbs(void);
// <LegoRR.exe @00422ff0>
void __cdecl Lego_RenameInputUnk(real32 elapsedAbs);
// <LegoRR.exe @00423120>
void __cdecl Lego_Input_UpdateTyping(void);
// <LegoRR.exe @00423210>
bool32 __cdecl Lego_MainLoop(real32 elapsed);
// <LegoRR.exe @00424490>
void __cdecl LiveObject_ConsumeOxygen(LiveObject* liveObj, real32 elapsed);
// <LegoRR.exe @00424530>
void __cdecl Level_FUN_00424530(LevelData* level, real32 elapsedGame);
// <LegoRR.exe @00424660>
void __cdecl Game_UpdateSceneFog(bool32 isFogEnabled, real32 elapsed);
// <LegoRR.exe @00424700>
bool32 __cdecl LiveObject_Callback_DrawRedBox_IfFlags4_1(LiveObject* liveObj, Viewport* viewMain);
// <LegoRR.exe @00424740>
bool32 __cdecl Game_DrawRedBoxes_AroundUnitsWithFlags4_1(Viewport* viewMain);
// <LegoRR.exe @00424760>
void __cdecl Game_DrawSelectedUnitBoxes(Viewport* viewMain);
// <LegoRR.exe @004247e0>
void __cdecl LiveObject_DrawSelectedBox(LiveObject* liveObj, Viewport* param_2, real32 r, real32 g, real32 b);
// <LegoRR.exe @00424c20>
void __cdecl Lego_Shutdown(void);
// <LegoRR.exe @00424c30>
void __cdecl Lego_Shutdown_Debug(void);
// <LegoRR.exe @00424fd0>
void __cdecl Lego_Exit(void);
// <LegoRR.exe @00424ff0>
bool32 __cdecl Lego_HandleKeys(real32 elapsedGame, real32 param_2, bool32* out_t, bool32* put_r, bool32* out_shift);
// <LegoRR.exe @00425a70>
bool32 __cdecl Lego_UpdateAll3DSounds(bool32 stopAll);
// <LegoRR.exe @00425a90>
bool32 __cdecl Lego_LiveObjectCallback_UpdateAll3DSounds(LiveObject* liveObj, bool32* pStopAll);
// <LegoRR.exe @00425b60>
void __cdecl Game_SetPaused(bool32 checkCamDisableFlag, bool32 paused);
// <LegoRR.exe @00425c00>
void __cdecl Game_LockGameSpeed(bool32 locked);
// <LegoRR.exe @00425c10>
void __cdecl Game_SetGameSpeed(real32 newGameSpeed);
// <LegoRR.exe @00425c80>
void __cdecl Game_TrackObjectInRadar(LiveObject* liveObj);
// <LegoRR.exe @00425cb0>
bool32 __cdecl Game_IsFirstPersonView(void);
// <LegoRR.exe @00425cc0>
void __cdecl Lego_Unk_HasRadarCtrl_FUN_00425cc0(void);
// <LegoRR.exe @004260f0>
void __cdecl Lego_UpdateSlug_FUN_004260f0(real32 elapsedGame);
// <LegoRR.exe @00426160>
void __cdecl Game_GetVector_45c(Vector3F* out_vector);
// <LegoRR.exe @00426180>
void __cdecl Lego_UnkCameraTrack_InRadar_FUN_00426180(void);
// <LegoRR.exe @00426210>
void __cdecl Game_SetMenuNextPosition(Point2F* position);
// <LegoRR.exe @00426250>
void __cdecl Game_SetMenuPreviousPosition(Point2F* position);
// <LegoRR.exe @00426290>
void __cdecl Game_SetFlags2_40_And_2_unkCamera(bool32 onFlag40, bool32 onFlag2);
// <LegoRR.exe @004262d0>
void __cdecl Game_SetFlags2_80(bool32 state);
// <LegoRR.exe @004262f0>
void __cdecl Lego_UnkObjective_CompleteSub_FUN_004262f0(void);
// <LegoRR.exe @00426350>
void __cdecl Game_UpdateTopdownCamera(real32 elapsedAbs);
// <LegoRR.exe @00426450>
void __cdecl Game_unkGameLoop_FUN_00426450(real32 elapsedGame, real32 elapsedAbs, undefined4 param_3, undefined4 param_4, sint32 param_5);
// <LegoRR.exe @00427d30>
void __cdecl Lego_LoadToolTipInfos(CFGProperty* root, char* rootPath);
// <LegoRR.exe @00427eb0>
void __cdecl Lego_LoadUpgradeNames(CFGProperty* root);
// <LegoRR.exe @00427f50>
void __cdecl Lego_ShowObjectToolTip(LiveObject* liveObj);
// <LegoRR.exe @00428260>
void __cdecl Lego_ShowBlockToolTip(Point2I* mouseBlockPos, bool32 showConstruction, bool32 silent, bool32 showCavern);
// <LegoRR.exe @004286b0>
bool32 __cdecl Level_BlockPointerCheck(Point2I* blockPos);
// <LegoRR.exe @00428730>
void __cdecl Game_SetPointer_AndPlayEnumSFX(sint32 unkEnum);
// <LegoRR.exe @00428810>
void __cdecl Lego_HandleDebugKeys(sint32 bx, sint32 by, LiveObject* liveObj);
// <LegoRR.exe @00429040>
void __cdecl SurfaceMap_LevelXYCallback_FUN_00429040(sint32 x, sint32 y);
// <LegoRR.exe @00429090>
Container_Texture* __cdecl Lego_DynamicPM_GatherRockSurfaceTexture_FUN_00429090(Point2I* textCoord);
// <LegoRR.exe @004290d0>
void __cdecl Lego_UnkUpdateMapsWorldUnk_FUN_004290d0(real32 elapsedAbs, bool32 pass2);
// <LegoRR.exe @004292e0>
void __cdecl Level_DrawDragSelectionBox(LevelData* level);
// <LegoRR.exe @004293a0>
void __cdecl Game_MainView_MouseTransform(uint32 mouseX, uint32 mouseY, real32* out_x, real32* out_y);
// <LegoRR.exe @004294d0>
Container* __cdecl Lego_GetCurrentViewLight(void);
// <LegoRR.exe @004294f0>
bool32 __cdecl LiveObject_Check_FUN_004294f0(LiveObject* liveObj);
// <LegoRR.exe @00429520>
void __cdecl Lego_SetViewMode(ViewMode viewMode, LiveObject* liveObj, sint32 fpCameraFrame);
// <LegoRR.exe @004296d0>
void __cdecl Music_CDAudio_PlayNextCallback(void);
// <LegoRR.exe @004296e0>
void __cdecl Music_PlayNext(bool32 isMusicOn);
// <LegoRR.exe @00429740>
void __cdecl Lego_SetSoundEnabled(bool32 isSoundOn);
// <LegoRR.exe @00429780>
sint32 __cdecl Lego_GetEmergeCreature(void);
// <LegoRR.exe @00429790>
float10 __cdecl Lego_GetObjectUpgradeTime(ObjectType objType);
// <LegoRR.exe @004297b0>
float10 __cdecl Lego_GetTrainTime(void);
// <LegoRR.exe @004297c0>
bool32 __cdecl Lego_LoadLevel(char* levelName);
// <LegoRR.exe @0042b220>
bool32 __cdecl LiveObject_Callback_AddCryOre(LiveObject* liveObj, SearchAddCryOre_c* search);
// <LegoRR.exe @0042b260>
bool32 __cdecl WorldMesh_LoadPromeshGrid(LevelData* level, char* meshBaseName);
// <LegoRR.exe @0042b3b0>
void __cdecl Level_Free_ProMeshGrid(LevelData* level);
// <LegoRR.exe @0042b430>
RadarMap* __cdecl Lego_GetRadarMap(void);
// <LegoRR.exe @0042b440>
bool32 __cdecl Lego_LoadMapSet(LevelData* level, char* surfaceMap, char* predugMap, sint32 predugParam, char* terrainMap, sint32 terrainParam, char* blockPointersMap, sint32 blockPointersParam, char* cryOreMap, char cryOreParam, char* erodeMap, char* pathMap, sint32 pathParam, char* textureSet, char* emergeMap, char* aiMap, char* fallinMap);
// <LegoRR.exe @0042b780>
void __cdecl SurfaceMap_InitTextureCoords(SurfaceMap* surfMap);
// <LegoRR.exe @0042ba90>
bool32 __cdecl Lego_LoadTextureSet(LevelData* level, char* keyTexturePath);
// <LegoRR.exe @0042bc50>
bool32 __cdecl Lego_LoadPreDugMap(LevelData* level, char* filename, sint32 modifier);
// <LegoRR.exe @0042be70>
bool32 __cdecl Lego_LoadErodeMap(LevelData* level, char* filename);
// <LegoRR.exe @0042bf90>
bool32 __cdecl Lego_LoadAIMap(LevelData* level, char* filename);
// <LegoRR.exe @0042c050>
bool32 __cdecl Lego_LoadEmergeMap(LevelData* level, char* filename);
// <LegoRR.exe @0042c260>
bool32 __cdecl Level_UnkEmerge_FUN_0042c260(LevelData* level, Point2I* in_position, undefined4* out_unkPosition);
// <LegoRR.exe @0042c370>
void __cdecl Level_FUN_0042c370(LevelData* level, real32 elapsedAbs);
// <LegoRR.exe @0042c3b0>
bool32 __cdecl Lego_LoadTerrainMap(LevelData* level, char* filename, sint32 modifier);
// <LegoRR.exe @0042c4e0>
bool32 __cdecl Lego_GetBlockCryOre(Point2I* position, sint32* out_crystal, sint32* out_ore, sint32* out_crystalAlt, sint32* out_oreAlt);
// <LegoRR.exe @0042c5d0>
bool32 __cdecl Lego_LoadCryOreMap(LevelData* level, char* filename, char modifier);
// <LegoRR.exe @0042c690>
bool32 __cdecl Lego_LoadPathMap(LevelData* level, char* filename, sint32 modifier);
// <LegoRR.exe @0042c900>
bool32 __cdecl Lego_LoadFallinMap(LevelData* level, char* filename);
// <LegoRR.exe @0042caa0>
void __cdecl Game_UpdateFallins(real32 elapsedGame);
// <LegoRR.exe @0042cbc0>
bool32 __cdecl Lego_LoadBlockPointersMap(LevelData* level, char* filename, sint32 modifier);
// <LegoRR.exe @0042cc80>
UpgradeData* __cdecl Game_GetUpgradeData(char* upgradeName);
// <LegoRR.exe @0042ccd0>
bool32 __cdecl Lego_LoadVehicleTypes(void);
// <LegoRR.exe @0042ce80>
bool32 __cdecl Lego_LoadMiniFigureTypes(void);
// <LegoRR.exe @0042d030>
bool32 __cdecl Lego_LoadRockMonsterTypes(void);
// <LegoRR.exe @0042d1e0>
bool32 __cdecl Lego_LoadBuildingTypes(void);
// <LegoRR.exe @0042d390>
bool32 __cdecl Lego_LoadUpgradeTypes(void);
// <LegoRR.exe @0042d530>
void __cdecl Lego_LoadObjectNames(CFGProperty* root);
// <LegoRR.exe @0042d950>
void __cdecl Lego_LoadObjectTheNames(CFGProperty* root);
// <LegoRR.exe @0042dd70>
void __cdecl Lego_GotoInfo(LiveObject* liveObj, Point2I* blockPos, bool32 gotoBool);
// <LegoRR.exe @0042def0>
void __cdecl Game_RemoveRecordObject(LiveObject* liveObj);
// <LegoRR.exe @0042df20>
bool32 __cdecl Game_GetRecordObject(uint32 recordObjPtr, LiveObject** out_liveObj);
// <LegoRR.exe @0042df50>
bool32 __cdecl Game_LoadOLObjectList(LevelData* level, char* filename);
// <LegoRR.exe @0042e7e0>
bool32 __cdecl Object_GetObjectByName(char* objName, ObjectType* out_objType, sint32* out_objIndex, Container** opt_resData);
// <LegoRR.exe @0042eca0>
bool32 __cdecl Object_GetTypeResource(ObjectType objType, sint32 objIndex, Container** out_resData);
// <LegoRR.exe @0042ee70>
sint32 __cdecl Object_GetTypeCount(ObjectType objType);
// <LegoRR.exe @0042eef0>
void __cdecl Lego_PlayMovie_old(char* fName, Point2F* opt_point);
// <LegoRR.exe @0042eff0>
char* __cdecl Level_Free(void);
// <LegoRR.exe @0042f210>
void __cdecl Level_Block_SetFlags1_200_AndUpdateSurface_LevelStruct428(LevelData* level, uint32 bx, uint32 by, bool32 setFlag200);
// <LegoRR.exe @0042f280>
uint32 __cdecl FUN_0042f280(sint32 param_1, sint32 param_2, undefined* param_3, sint32 param_4);
// <LegoRR.exe @0042f620>
void __cdecl Level_BlockUpdateSurface(LevelData* level, sint32 bx, sint32 by, bool32 reserved);
// <LegoRR.exe @004301e0>
void __cdecl Level_Block_Proc_FUN_004301e0(Point2I* blockPos);
// <LegoRR.exe @00430250>
void __cdecl AITask_DoClearTypeAction(Point2I* position, MessageType completeAction);
// <LegoRR.exe @004303a0>
void __cdecl Level_Debug_WKey_NeedsBlockFlags1_8_FUN_004303a0(LevelData* level, bool32 unused, uint32 bx, uint32 by);
// <LegoRR.exe @00430460>
bool32 __cdecl Level_DestroyWall(LevelData* level, uint32 bx, uint32 by, bool32 isHiddenCavern);
// <LegoRR.exe @00430d20>
void __cdecl Level_Block_FUN_00430d20(Point2I* blockPos);
// <LegoRR.exe @00430e10>
bool32 __cdecl Level_DestroyWallConnection(LevelData* level, uint32 bx, uint32 by);
// <LegoRR.exe @00431020>
void __cdecl Level_Block_RemoveReinforcement(Point2I* blockPos);
// <LegoRR.exe @00431070>
void __cdecl Level_Block_Reinforce(sint32 bx, sint32 by);
// <LegoRR.exe @00431100>
void __cdecl Level_LevelStruct1C_Create_Res_Unk_RechargeSparkle(LevelData* level, Point2I* blockPos, bool32 bool18);
// <LegoRR.exe @004312e0>
void __cdecl Level_LevelStruct1C_FUN_004312e0(LevelData* level, real32 elapsedGame);
// <LegoRR.exe @00431380>
void __cdecl Level_Block_LevelStruct1C_DoActivityDestroy(LevelData* level, Point2I* blockPos, bool32 requireNotBool18);
// <LegoRR.exe @004313f0>
void __cdecl Level_Remove_LevelStruct1C_AndFree(LevelStruct_1c* param_1);
// <LegoRR.exe @00431460>
void __cdecl Level_FreeAll_LevelStruct1Cs_FUN_00431460(LevelData* level);
// <LegoRR.exe @00431490>
LevelData* __cdecl Lego_GetLevel(void);
// <LegoRR.exe @004314a0>
SurfaceMap* __cdecl Lego_GetMap(void);
// <LegoRR.exe @004314b0>
void __cdecl Level_UncoverHiddenCavern(uint32 bx, uint32 by);
// <LegoRR.exe @004316b0>
void __cdecl Game_PTL_RockFall(uint32 bx, uint32 by, sint32 param_3, bool32 param_4);
// <LegoRR.exe @004318e0>
SurfaceType __cdecl Lego_GetBlockTerrain(sint32 bx, sint32 by);
// <LegoRR.exe @00431910>
uint32 __cdecl MapShared_GetBlock(uint32 memHandle, sint32 bx, sint32 by);
// <LegoRR.exe @00431960>
bool32 __cdecl Level_FindSelectedUnit_BlockCheck_FUN_00431960(uint32 bx, uint32 by, bool32 param_3);
// <LegoRR.exe @004319e0>
bool32 __cdecl Level_FindSelectedLiveObject_BlockReinforce_FUN_004319e0(uint32 bx, uint32 by);
// <LegoRR.exe @00431a50>
bool32 __cdecl Level_BlockCheck_SelectPlace_FUN_00431a50(sint32 bx, sint32 by, bool32 param_3, bool32 param_4);
// <LegoRR.exe @00431ba0>
bool32 __cdecl LiveObject_FUN_00431ba0(LiveObject* liveObj, Point2I* param_2, Point2I* out_point, bool32 param_4);
// <LegoRR.exe @00431cd0>
sint32 __cdecl LiveObject_Routing_GetCrossTerrainType(LiveObject* in_liveObj, sint32 bx1, sint32 by1, sint32 bx2, sint32 by2, bool32 param_6);
// <LegoRR.exe @00432030>
void __cdecl Level_Block_SetPowered_AddToTable(Point2I* blockPos);
// <LegoRR.exe @004320a0>
bool32 __cdecl Level_Block_IsPowered(Point2I* blockPos);
// <LegoRR.exe @004320d0>
void __cdecl Game_UpdateLevelBlocks_PointsAAC(void);
// <LegoRR.exe @00432130>
void __cdecl Game_LevelClearBlockFlag2_100_Points28C(void);
// <LegoRR.exe @004321a0>
void __cdecl Level_Block_AddPowerPathDrainTemp_ToTable_Unk(Point2I* blockPos);
// <LegoRR.exe @00432200>
bool32 __cdecl Level_Block_IsPowerPathDrainTemp_Unk(Point2I* blockPos);
// <LegoRR.exe @00432230>
void __cdecl Game_UnkProcessBlockPtsTable_UnsetsFlag2_2(void);
// <LegoRR.exe @00432290>
void __cdecl Level_Block_UnsetFlags1_108400PwrPath_AndUnsetFlags2_4_UpdateSurface(Point2I* blockPos);
// <LegoRR.exe @004322f0>
void __cdecl Level_Block_UnsetGeneratePower(Point2I* blockPos);
// <LegoRR.exe @00432320>
void __cdecl Level_Block_SetToolStoreBuilding(Point2I* blockPos);
// <LegoRR.exe @00432380>
void __cdecl Level_Block_SetSolidBuilding(sint32 bx, sint32 by);
// <LegoRR.exe @004323c0>
void __cdecl Level_Block_SetPathBuilding(sint32 bx, sint32 by);
// <LegoRR.exe @00432400>
void __cdecl Level_Block_SetFenceRequest(sint32 bx, sint32 by, bool32 state);
// <LegoRR.exe @00432450>
bool32 __cdecl Level_Block_IsFenceRequest(sint32 bx, sint32 by);
// <LegoRR.exe @00432480>
bool32 __cdecl Level_IsBuildPathBoolUnk_true(Point2I* blockPos);
// <LegoRR.exe @00432490>
void __cdecl Level_Block_SetLayedPath(Point2I* blockPos, bool32 state);
// <LegoRR.exe @00432500>
void __cdecl Level_Block_SetGeneratePower(Point2I* blockPos);
// <LegoRR.exe @00432530>
bool32 __cdecl Level_Block_SetPath(Point2I* blockPos);
// <LegoRR.exe @00432640>
void __cdecl Level_Block_SetFlags1_80000(Point2I* blockPos, bool32 condition);
// <LegoRR.exe @004326a0>
bool32 __cdecl LiveObject_BlockCheck_FUN_004326a0(LiveObject* liveObj, uint32 bx, uint32 by, bool32 param_4, bool32 param_5);
// <LegoRR.exe @00432880>
bool32 __cdecl LiveObject_CanDynamiteBlockPos(LiveObject* liveObj, uint32 bx, uint32 by);
// <LegoRR.exe @00432900>
bool32 __cdecl Level_Block_IsGround_alt(LiveObject* liveObj, uint32 bx, uint32 by);
// <LegoRR.exe @00432950>
bool32 __cdecl LiveObject_CanReinforceBlock(LiveObject* liveObj, uint32 bx, uint32 by);
// <LegoRR.exe @004329d0>
bool32 __cdecl Level_Block_IsSolidBuilding(uint32 bx, uint32 by, bool32 allowToolStore);
// <LegoRR.exe @00432a30>
bool32 __cdecl Level_Block_IsFlags1_800(uint32 bx, uint32 by);
// <LegoRR.exe @00432a80>
bool32 __cdecl Level_Block_IsGround(uint32 bx, uint32 by);
// <LegoRR.exe @00432ac0>
bool32 __cdecl Level_Block_IsSeamWall(uint32 bx, uint32 by);
// <LegoRR.exe @00432b00>
bool32 __cdecl Level_Block_IsWall(uint32 bx, uint32 by);
// <LegoRR.exe @00432b50>
bool32 __cdecl Level_Block_IsDestroyedConnection(uint32 bx, uint32 by);
// <LegoRR.exe @00432b80>
uint32 __cdecl Level_Block_GetRubbleLayers(Point2I* blockPos);
// <LegoRR.exe @00432bc0>
bool32 __cdecl Level_Block_ClearRubbleLayer(Point2I* blockPos);
// <LegoRR.exe @00432cc0>
bool32 __cdecl Level_Block_IsReinforced(uint32 bx, uint32 by);
// <LegoRR.exe @00432d00>
bool32 __cdecl Level_Block_IsBusy(Point2I* blockPos);
// <LegoRR.exe @00432d30>
void __cdecl Level_Block_SetBusy(Point2I* blockPos, bool32 state);
// <LegoRR.exe @00432d90>
bool32 __cdecl Level_Block_IsCorner(uint32 bx, uint32 by);
// <LegoRR.exe @00432dc0>
bool32 __cdecl Level_Block_IsExposed(Point2I* blockPos);
// <LegoRR.exe @00432df0>
bool32 __cdecl Level_Block_IsImmovable(Point2I* blockPos);
// <LegoRR.exe @00432e30>
bool32 __cdecl Level_Block_IsLava(Point2I* blockPos);
// <LegoRR.exe @00432e70>
bool32 __cdecl Level_Block_IsNotWallOrGround(uint32 bx, uint32 by);
// <LegoRR.exe @00432ec0>
bool32 __cdecl Level_Block_IsSurveyed(uint32 bx, uint32 by);
// <LegoRR.exe @00432f00>
bool32 __cdecl Level_Block_IsFlags1_2000(uint32 bx, uint32 by);
// <LegoRR.exe @00432f30>
bool32 __cdecl Level_Block_IsCornerInner(uint32 bx, uint32 by);
// <LegoRR.exe @00432f60>
bool32 __cdecl Level_Block_IsPathBuilding(Point2I* blockPos);
// <LegoRR.exe @00432f90>
bool32 __cdecl Level_Block_IsGeneratePower(Point2I* blockPos);
// <LegoRR.exe @00432fc0>
bool32 __cdecl Level_Block_IsPath(Point2I* blockPos);
// <LegoRR.exe @00433010>
bool32 __cdecl Level_Block_IsAnyFlags1_80000_Foundation(Point2I* blockPos);
// <LegoRR.exe @00433050>
void __cdecl Level_Block_SetFlags1_10000000(Point2I* blockPos, bool32 state);
// <LegoRR.exe @004330b0>
bool32 __cdecl LiveObject_GetRockFallInDamage_Unk(LiveObject* liveObj, sint32 bx, sint32 by, real32 elapsed, real32* optout_value);
// <LegoRR.exe @004331f0>
uint32 __cdecl Level_Block_GetField3__routingRelated(uint32 bx, uint32 by);
// <LegoRR.exe @00433220>
void __cdecl Level_Block_SetSurveyed(uint32 bx, uint32 by);
// <LegoRR.exe @00433260>
bool32 __cdecl Level_Block_GetSurfaceType(uint32 bx, uint32 by, SurfaceType* out_surfaceType);
// <LegoRR.exe @004332b0>
void __cdecl Level_Block_LowerRoofVertices(LevelData* level, uint32 bx, uint32 by);
// <LegoRR.exe @004333f0>
void __cdecl MapShared_GetDimensions(uint32 sharedIndex, uint32* out_width, uint32* out_height);
// <LegoRR.exe @00433420>
bool32 __cdecl Lego_LoadGraphicsSettings(void);
// <LegoRR.exe @004336a0>
bool32 __cdecl Lego_LoadLighting(void);
// <LegoRR.exe @00433b10>
bool32 __cdecl Lego_WorldToBlockPos_NoZ(real32 in_x, real32 in_y, sint32* out_bx, sint32* out_by);
// <LegoRR.exe @00433b40>
bool32 __cdecl LiveObject_FUN_00433b40(LiveObject* liveObj, real32 param_2, bool32 param_3);
// <LegoRR.exe @00433d60>
bool32 __cdecl Level_Block_IsMeshHidden(uint32 bx, uint32 by);
// <LegoRR.exe @00433db0>
void __cdecl Lego_FPHighPolyBlocks_FUN_00433db0(Container* contCamera, Viewport* view, real32 fpClipBlocksMult, real32 highPolyBlocksMult);
// <LegoRR.exe @00434380>
sint32 __cdecl Lego_QsortCompareUnk_FUN_00434380(sint32 param_1, sint32 param_2);
// <LegoRR.exe @004343b0>
bool32 __cdecl Level_Block_ProMesh_FUN_004343b0(LevelData* level, uint32 bx, uint32 by, undefined4 param_4, uint32 param_5);
// <LegoRR.exe @00434460>
void __cdecl Level_RemoveAll_ProMeshes(void);
// <LegoRR.exe @004344a0>
bool32 __cdecl Level_Block_GetUnkField14Test(uint32 bx, uint32 by, real32 param_3, real32 param_4);
// <LegoRR.exe @00434520>
void __cdecl Lego_LoadPanels(CFGProperty* root, uint32 screenWidth, uint32 screenHeight);
// <LegoRR.exe @00434640>
void __cdecl Lego_LoadPanelButtons(CFGProperty* root, uint32 screenWidth, uint32 screenHeight);
// <LegoRR.exe @00434930>
void __cdecl Lego_LoadTutorialIcon(CFGProperty* root);
// <LegoRR.exe @00434980>
void __cdecl Lego_LoadSamples(CFGProperty* root, bool32 noReduceSamples);
// <LegoRR.exe @00434a20>
void __cdecl Lego_LoadTextMessages(CFGProperty* root);
// <LegoRR.exe @00434b40>
void __cdecl Lego_LoadInfoMessages(CFGProperty* root);
// <LegoRR.exe @00434cd0>
void __cdecl Lego_LoadToolTips(CFGProperty* root);
// <LegoRR.exe @00434db0>
bool32 __cdecl Game_TryTeleportObject(ObjectType objType, sint32 objIndex);
// <LegoRR.exe @00434f40>
void __cdecl Level_Block_UpdateSurveyRadius_FUN_00434f40(Point2I* blockPos, sint32 surveyRadius);
// <LegoRR.exe @00434fd0>
void __cdecl Lego_LoadSurfaceTypeDescriptions_sound(CFGProperty* root, char* rootPath);
// <LegoRR.exe @004350a0>
char* __cdecl Game_GetSurfaceTypeDescription(SurfaceType surfaceType);
// <LegoRR.exe @004350c0>
SFXType __cdecl Game_GetSurfaceTypeSFX(SurfaceType surfaceType);
// <LegoRR.exe @004350d0>
void __cdecl Level_SetPointer_FromSurfaceType(SurfaceType surfaceType);
// <LegoRR.exe @00435160>
void __cdecl Level_GenerateFallin_InRadius(Point2I* blockPos, sint32 radius, bool32 param_3);
// <LegoRR.exe @00435230>
void __cdecl Level_UpdateTutorialBlockFlashing(LevelData* level, Viewport* viewMain, real32 elapsedGame, real32 elapsedAbs);
// <LegoRR.exe @00435480>
bool32 __cdecl Front_LeftButtonInputUnk_FUN_00435480(void);
// <LegoRR.exe @004354b0>
bool32 __cdecl Front_DrawDialogContrastOverlay(void);
// <LegoRR.exe @004354f0>
sint32 __cdecl SaveMenu_ConfirmMessage_FUN_004354f0(char* titleText, char* message, char* okText, char* cancelText);
// <LegoRR.exe @00435870>
bool32 __cdecl Lego_EndLevel(void);
// <LegoRR.exe @00435950>
void __cdecl LegoGame_ClearSomeFlags3_FUN_00435950(void);
// <LegoRR.exe @00435980>
void __cdecl LegoGame_UnkTeleporterInit_FUN_00435980(void);
// <LegoRR.exe @004359b0>
void __cdecl LegoGame_SetAttackDefer(bool32 defer);
// <LegoRR.exe @004359d0>
void __cdecl LegoGame_SetCallToArmsOn(bool32 callToArms);
// <LegoRR.exe @00435a50>
Camera* __cdecl Camera_Create(Container* contRoot, CameraType camType);
// <LegoRR.exe @00435cc1>
void __cdecl Camera_Debug_EnableFreeMovement(Camera* cam, bool32 on);
// <LegoRR.exe @00435cf8>
void __cdecl Camera_Free(Camera* cam);
// <LegoRR.exe @00435d3e>
void __cdecl Camera_SetCameraMovements(real32 cameraSpeed, real32 cameraDropOff, real32 cameraAcceleration, sint32 mouseScrollIndent);
// <LegoRR.exe @00435d65>
void __cdecl Camera_CopyPositionOrientation_IfFirstPerson(Camera* dstCamera, Camera* srcCamera);
// <LegoRR.exe @00435deb>
void __cdecl Camera_TrackObject(Camera* cam, LiveObject* liveObj, real32 trackFloat_8, real32 trackDist, real32 trackTilt, real32 trackRotationSpeed);
// <LegoRR.exe @00435e24>
void __cdecl Camera_SetFPObject(Camera* cam, LiveObject* liveObj, sint32 cameraFrame);
// <LegoRR.exe @00435e3b>
sint32 __cdecl Camera_GetFPCameraFrame(Camera* cam);
// <LegoRR.exe @00435e46>
void __cdecl Camera_StopMovement(Camera* cam);
// <LegoRR.exe @00435e58>
sint32 __cdecl Camera_GetMouseScrollIndent(void);
// <LegoRR.exe @00435e62>
void __cdecl Camera_Shake(Camera* cam, real32 intensity, real32 duration);
// <LegoRR.exe @00435e8c>
void __cdecl Camera_Update(Camera* cam, LevelData* level, real32 elapsedAbs, real32 elapsedGame);
// <LegoRR.exe @00436a53>
void __cdecl Camera_SetTiltRange(Camera* cam, real32 minTilt, real32 maxTilt);
// <LegoRR.exe @00436a82>
void __cdecl Camera_SetTilt(Camera* cam, real32 tilt);
// <LegoRR.exe @00436b22>
void __cdecl Camera_AddTilt(Camera* cam, real32 tiltAmount);
// <LegoRR.exe @00436b43>
void __cdecl Camera_SetYawRange(Camera* cam, real32 minYaw, real32 maxYaw);
// <LegoRR.exe @00436b75>
void __cdecl Camera_SetYaw(Camera* cam, real32 yaw);
// <LegoRR.exe @00436c16>
void __cdecl Camera_AddYaw(Camera* cam, real32 yawAmount);
// <LegoRR.exe @00436c3a>
void __cdecl Camera_SetDistRange(Camera* cam, real32 minDist, real32 maxDist);
// <LegoRR.exe @00436c6c>
void __cdecl Camera_SetDist(Camera* cam, real32 dist);
// <LegoRR.exe @00436cc7>
void __cdecl Camera_AddDist(Camera* cam, real32 distAmount);
// <LegoRR.exe @00436ceb>
void __cdecl Camera_AddTranslation2D(Camera* cam, real32 translateX, real32 translateY);
// <LegoRR.exe @00436d0b>
void __cdecl Camera_GetTopdownPosition(Camera* cam, Vector3F* out_position);
// <LegoRR.exe @00436d2d>
void __cdecl Camera_SetTopdownPosition(Camera* cam, real32 x, real32 y);
// <LegoRR.exe @00436d55>
bool32 __cdecl Camera_GetTopdownWorldPos(Camera* cam, SurfaceMap* surfMap, Vector3F* out_worldPos);
// <LegoRR.exe @00436d9b>
float10 __cdecl Camera_GetYaw(Camera* cam);
// <LegoRR.exe @00436da9>
void __cdecl Camera_Move(Camera* cam, Vector3F* ref_dir, real32 elapsedAbs);
// <LegoRR.exe @00436ee0>
void __cdecl LiveManager_Initialise(void);
// <LegoRR.exe @00437310>
void __cdecl LiveManager_Shutdown(void);
// <LegoRR.exe @00437370>
void __cdecl Save_CopyStruct18(SaveStruct_18* out_saveStruct18);
// <LegoRR.exe @00437390>
void __cdecl Save_OverwriteStruct18(SaveStruct_18* saveStruct18);
// <LegoRR.exe @004373c0>
sint32 __cdecl LiveManager_FUN_004373c0(ObjectType objType, bool32 param_2);
// <LegoRR.exe @00437410>
void __cdecl LiveManager_LoadToolTipIcons(CFGProperty* root);
// <LegoRR.exe @00437560>
void __cdecl LiveManager_FUN_00437560(void);
// <LegoRR.exe @004375c0>
void __cdecl LiveObject_Weapon_FUN_004375c0(LiveObject* in_liveObj, sint32 weaponType, real32 param_3);
// <LegoRR.exe @00437690>
bool32 __cdecl LiveObject_FUN_00437690(LiveObject* liveObj, bool32 condition);
// <LegoRR.exe @00437700>
void __cdecl LiveManager_FUN_00437700(void);
// <LegoRR.exe @00437720>
uint32 __cdecl LiveObject_GetLevelObjectsBuilt(ObjectType objType, sint32 objIndex, sint32 objLevel, bool32 currentLevel);
// <LegoRR.exe @00437760>
uint32 __cdecl LiveObject_GetPreviousLevelObjectsBuilt(ObjectType objType, sint32 objIndex, sint32 objLevel);
// <LegoRR.exe @00437790>
void __cdecl LiveObject_IncLevelPathsBuilt(bool32 incCurrent);
// <LegoRR.exe @004377b0>
void __cdecl LiveObject_FUN_004377b0(LiveObject* liveObj);
// <LegoRR.exe @004377d0>
bool32 __cdecl LiveObject_Callback_UnkDoRouting_IfObject2FC(LiveObject* liveObj1, LiveObject* liveObj2);
// <LegoRR.exe @00437800>
bool32 __cdecl LiveObject_Remove(LiveObject* liveObj);
// <LegoRR.exe @00437a70>
bool32 __cdecl Search_LiveObjects_SkipIgnoreMes(SearchLiveObjectCallback predicateFunc, void* search);
// <LegoRR.exe @00437a90>
bool32 __cdecl Search_LiveObjects(SearchLiveObjectCallback callback, void* search, bool32 skipIgnoreMeObjs);
// <LegoRR.exe @00437b40>
void __cdecl LiveObject_SetCustomName(LiveObject* liveObj, char* customName);
// <LegoRR.exe @00437ba0>
void __cdecl HiddenObject_RemoveAll(void);
// <LegoRR.exe @00437c00>
void __cdecl HiddenObject_ExposeBlock(Point2I* blockPos);
// <LegoRR.exe @00437ee0>
void __cdecl HiddenObject_Add(void* objSrcData, ObjectType objType, sint32 objIndex, Point2F* worldPos, real32 heading, real32 health, char* thisOLName, char* drivingOLName);
// <LegoRR.exe @00437f80>
bool32 __cdecl LiveObject_CanShootObject(LiveObject* liveObj);
// <LegoRR.exe @00437fc0>
LiveObject* __cdecl LiveObject_Create(sint32** srcData, ObjectType objType, sint32 objIndex);
// <LegoRR.exe @00438580>
LiveObject* __cdecl LiveObject_Create_internal(void);
// <LegoRR.exe @004385d0>
void __cdecl LiveManager_AddList(void);
// <LegoRR.exe @00438650>
sint32 __cdecl LiveManage_GetNumBuildingsTeleported(sint32* stack);
// <LegoRR.exe @00438660>
void __cdecl LiveManage_SetNumBuildingsTeleported(uint32 numTeleported);
// <LegoRR.exe @00438670>
void __cdecl LiveObject_SetCrystalPoweredColor(LiveObject* liveObj, bool32 isPowered);
// <LegoRR.exe @00438720>
void __cdecl LiveObject_FUN_00438720(LiveObject* liveObj);
// <LegoRR.exe @00438840>
void __cdecl LiveObject_SetFlag3_80000000(LiveObject* liveObj, bool32 state);
// <LegoRR.exe @00438870>
bool32 __cdecl LiveObject_CheckCondition_AndIsPowered(LiveObject* liveObj, bool32 state);
// <LegoRR.exe @004388d0>
LiveObject* __cdecl LiveObject_CreateInWorld(void* objSrcData, ObjectType objType, sint32 objIndex, sint32 objLevel, real32 xPos, real32 yPos, real32 heading);
// <LegoRR.exe @00438930>
LiveObject* __cdecl Game_Unk_DoSearchCallbacks_Unique(Point2I* blockPos);
// <LegoRR.exe @00438970>
bool32 __cdecl LiveManage_FUN_00438970(LiveObject* liveObj, LiveObject** param_2);
// <LegoRR.exe @004389e0>
bool32 __cdecl LiveObject_AddThisDrainedCrystals(LiveObject* liveObj, sint32 crystalCount);
// <LegoRR.exe @00438a30>
bool32 __cdecl LiveObject_GetBuildingUpgradeCost(LiveObject* liveObj, uint32* out_oreCost);
// <LegoRR.exe @00438ab0>
void __cdecl LiveObject_FUN_00438ab0(LiveObject* in_liveObj);
// <LegoRR.exe @00438b70>
bool32 __cdecl FUN_00438b70(LiveObject* liveObj, sint32 objLevel);
// <LegoRR.exe @00438c20>
undefined4 __cdecl FUN_00438c20(LiveObject* opt_liveObj, bool32 param_2);
// <LegoRR.exe @00438ca0>
undefined4 __cdecl LiveObject_FUN_00438ca0(LiveObject* liveObj, bool32 param_2);
// <LegoRR.exe @00438d20>
LiveObject* __cdecl FUN_00438d20(Point2I* blockPos, ObjectType objType, sint32 objIndex, sint32 objLevel);
// <LegoRR.exe @00438da0>
LiveObject* __cdecl LiveObject_FUN_00438da0(LiveObject* liveObj, Point2I* blockPos, ObjectType objType, sint32 objLevel);
// <LegoRR.exe @00438e40>
undefined4 __cdecl FUN_00438e40(LiveObject* liveObj, undefined4 param_2);
// <LegoRR.exe @00438eb0>
undefined4 __cdecl FUN_00438eb0(LiveObject* liveObj);
// <LegoRR.exe @00438f20>
undefined4 __cdecl FUN_00438f20(LiveObject* liveObj);
// <LegoRR.exe @00438f90>
LiveObject* __cdecl Game_FindBigTeleporter(Point2F* point);
// <LegoRR.exe @00438ff0>
LiveObject* __cdecl Game_FindSmallTeleporter(Point2F* point);
// <LegoRR.exe @00439050>
LiveObject* __cdecl Game_FindWaterTeleporter(Point2F* point);
// <LegoRR.exe @004390b0>
LiveObject* __cdecl Level_GetBuildingAtPosition(Point2F* point);
// <LegoRR.exe @00439110>
undefined4 __cdecl FUN_00439110(LiveObject* liveObj, Point2F* param_2, TrainedFlags trainedType);
// <LegoRR.exe @00439190>
bool32 __cdecl LiveObject_HasTraining(LiveObject* liveObj, TrainedFlags training);
// <LegoRR.exe @00439220>
bool32 __cdecl LiveObject_IsDocksBuilding_Unk(LiveObject* liveObj);
// <LegoRR.exe @00439270>
bool32 __cdecl LiveObject_CallbackSearch_FUN_00439270(LiveObject* liveObj, sint32** search);
// <LegoRR.exe @004394c0>
bool32 __cdecl Game_CanStoredObjectTypeBeSpawned(ObjectType objType);
// <LegoRR.exe @00439500>
bool32 __cdecl LiveObject_Callback_CanSpawnStoredObjects(LiveObject* liveObj1, LiveObject* spawnObj);
// <LegoRR.exe @00439540>
void __cdecl Game_PTL_GenerateFromCryOre(Point2I* position);
// <LegoRR.exe @00439600>
void __cdecl Game_PTL_GenerateCrystalsAndOre(Point2I* blockPos, uint32 objLevel);
// <LegoRR.exe @00439630>
void __cdecl Level_GenerateCrystal(Point2I* blockPos, uint32 objLevel, Point2F* opt_worldPos, bool32 showInfoMessage);
// <LegoRR.exe @00439770>
void __cdecl Level_GenerateOre(Point2I* blockPos, uint32 objLevel, Point2F* opt_point, bool32 showInfoMessage);
// <LegoRR.exe @004398a0>
char* __cdecl LiveObject_GetName(LiveObject* liveObj);
// <LegoRR.exe @00439980>
char* __cdecl Object_GetTypeName(ObjectType objType, sint32 objIndex);
// <LegoRR.exe @00439a50>
char* __cdecl Object_GetTheName(ObjectType objType, sint32 objIndex);
// <LegoRR.exe @00439b20>
char* __cdecl Object_GetName(ObjectType objType, sint32 objIndex);
// <LegoRR.exe @00439bf0>
void __cdecl LiveObject_GetTypeIndex(LiveObject* param_1, sint32* out_objType, sint32* out_objIndex);
// <LegoRR.exe @00439c10>
void __cdecl Main_LoadToolNames(CFGProperty* root, char* keyBasePath);
// <LegoRR.exe @00439c50>
void __cdecl LiveManager_InitFlagsToggle_AndClearNumDrained(void);
// <LegoRR.exe @00439c80>
bool32 __cdecl LiveObject_VehicleMaxCarryChecksTime_FUN_00439c80(LiveObject* liveObj);
// <LegoRR.exe @00439ce0>
bool32 __cdecl LiveObject_TryCollect_FUN_00439ce0(LiveObject* liveObj1, LiveObject* targetObj);
// <LegoRR.exe @00439e40>
bool32 __cdecl LiveObject_FUN_00439e40(LiveObject* liveObj, LiveObject* otherObj);
// <LegoRR.exe @00439e90>
bool32 __cdecl LiveObject_FUN_00439e90(LiveObject* liveObj1, LiveObject* liveObj2, bool32 param_3);
// <LegoRR.exe @00439f40>
void __cdecl LiveObject_CompleteVehicleUpgrade(LiveObject* liveObj);
// <LegoRR.exe @00439f90>
bool32 __cdecl LiveObject_SetLevel_thunk(LiveObject* liveObj, sint32 objLevel);
// <LegoRR.exe @00439fb0>
bool32 __cdecl LiveObject_IsSmallTeleporter(LiveObject* liveObj);
// <LegoRR.exe @00439fd0>
bool32 __cdecl LiveObject_IsBigTeleporter(LiveObject* liveObj);
// <LegoRR.exe @00439ff0>
bool32 __cdecl LiveObject_IsWaterTeleporter(LiveObject* liveObj);
// <LegoRR.exe @0043a010>
bool32 __cdecl LiveObject_UnkGetTerrainCrossBlock_FUN_0043a010(LiveObject* liveObj, Point2I* out_blockPos);
// <LegoRR.exe @0043a0d0>
bool32 __cdecl LiveObject_UnkGetTerrainGetOutAtLandBlock_FUN_0043a0d0(LiveObject* liveObj, Point2I* out_blockPos);
// <LegoRR.exe @0043a100>
bool32 __cdecl LiveObject_CheckUnkGetInAtLand_FUN_0043a100(LiveObject* liveObj, Point2I* param_2);
// <LegoRR.exe @0043a130>
void __cdecl LiveObject_DropCarriedObject_FUN_0043a130(LiveObject* in_liveObj, bool32 param_2);
// <LegoRR.exe @0043a3e0>
sint32 __cdecl LiveObject_TryRequestOrDump_FUN_0043a3e0(LiveObject* liveObj, Point2I* blockPos, Point2F* param_3, bool32 param_4, bool32 param_5);
// <LegoRR.exe @0043a5c0>
bool32 __cdecl LiveObject_TryDeposit_FUN_0043a5c0(LiveObject* liveObj1, LiveObject* targetObj);
// <LegoRR.exe @0043a8b0>
Container* __cdecl LiveObject_GetDepositNull(LiveObject* liveObj);
// <LegoRR.exe @0043a910>
LiveObject* __cdecl LiveObject_FUN_0043a910(LiveObject* liveObj, ObjectType objType, sint32 objIndex, sint32 objLevel);
// <LegoRR.exe @0043aa80>
bool32 __cdecl LiveObject_CanSpawnCarryableObject(LiveObject* liveObj, ObjectType objType, sint32 objIndex);
// <LegoRR.exe @0043ab10>
void __cdecl LiveObject_FUN_0043ab10(LiveObject* liveObj, LiveObject* liveObj2);
// <LegoRR.exe @0043abb0>
void __cdecl Level_AddCrystals__unusedLiveObject(LiveObject* liveObj_unused, uint32 crystalCount);
// <LegoRR.exe @0043abd0>
void __cdecl Level_AddOre__unusedLiveObject(LiveObject* liveObj_unused, uint32 oreCount);
// <LegoRR.exe @0043abf0>
void __cdecl LiveObject_WaterVehicle_Unregister(LiveObject* liveObj);
// <LegoRR.exe @0043ac20>
void __cdecl LiveObject_WaterVehicle_Register(LiveObject* liveObj);
// <LegoRR.exe @0043aca0>
void __cdecl LiveObject_RegisterVehicle__callsForWater(LiveObject* liveObj);
// <LegoRR.exe @0043acb0>
void __cdecl LiveObject_FUN_0043acb0(LiveObject* liveObj1, LiveObject* liveObj2);
// <LegoRR.exe @0043ad70>
void __cdecl LiveObject_RockMonster_FUN_0043ad70(LiveObject* liveObj);
// <LegoRR.exe @0043aeb0>
void __cdecl LiveObject_FUN_0043aeb0(LiveObject* liveObj);
// <LegoRR.exe @0043af50>
bool32 __cdecl LiveObject_Callback_MiniFigureWithCrystal_InStampRadius_FUN_0043af50(LiveObject* liveObj, LiveObject* otherLiveObj);
// <LegoRR.exe @0043b010>
LiveObject* __cdecl LiveObject_TryGenerateSlug(LiveObject* liveObj, uint32 objIndex);
// <LegoRR.exe @0043b160>
LiveObject* __cdecl Game_PTL_GenerateRockMonster(void);
// <LegoRR.exe @0043b1f0>
LiveObject* __cdecl Game_TryGeneratedRockMonsterLiveObject(sint32** objSrc, ObjectType objType, sint32 objIndex, uint32 bx, uint32 by);
// <LegoRR.exe @0043b530>
void __cdecl LiveManager_UpdateAll(real32 elapsedGame);
// <LegoRR.exe @0043b5e0>
void __cdecl LiveManager_Cleanup_FUN_0043b5e0(void);
// <LegoRR.exe @0043b610>
bool32 __cdecl LiveObject_Callback_Release(LiveObject* liveObj, void* unused);
// <LegoRR.exe @0043b620>
void __cdecl LiveManager_DoPickSphereCallbacks_MouseXY(uint32 mouseX, uint32 mouseY, undefined4* ref_param_3);
// <LegoRR.exe @0043b670>
bool32 __cdecl LiveObject_Callback_FUN_0043b670(LiveObject* liveObj, sint32** param_2);
// <LegoRR.exe @0043b980>
void __cdecl LiveManager_DoSelection(Viewport* view, Point2F* dragStart, Point2F* dragEnd);
// <LegoRR.exe @0043ba30>
bool32 __cdecl LiveObject_CallbackDoSelection(LiveObject* liveObj, SearchViewportWindow_14* search);
// <LegoRR.exe @0043bae0>
void __cdecl LiveObject_SwapPolyFP(LiveObject* liveObj, sint32 cameraFrameIndex, bool32 on);
// <LegoRR.exe @0043bb10>
void __cdecl LiveObject_FP_SetRanges(LiveObject* liveObj, Container* resData, real32 medPolyRange, real32 highPolyRange, bool32 param_5);
// <LegoRR.exe @0043bb90>
bool32 __cdecl LiveObject_FP_Callback_SwapPolyMeshParts(LiveObject* liveObj, LiveObjectInfo* liveInfo);
// <LegoRR.exe @0043bdb0>
bool32 __cdecl LiveObject_Check_LotsOfFlags1AndFlags2_FUN_0043bdb0(LiveObject* liveObj);
// <LegoRR.exe @0043bde0>
void __cdecl LiveObject_FUN_0043bde0(LiveObject* liveObj);
// <LegoRR.exe @0043be80>
void __cdecl LiveObject_FUN_0043be80(LiveObject* liveObj);
// <LegoRR.exe @0043bf00>
void __cdecl LiveObject_TeleportUp(LiveObject* liveObj);
// <LegoRR.exe @0043c4c0>
bool32 __cdecl Object_DoOxygenCheck_FUN_0043c4c0(ObjectType objType1, sint32 objIndex1, ObjectType objType2, sint32 objIndex2);
// <LegoRR.exe @0043c540>
bool32 __cdecl LiveObject_OxygenCallback_FUN_0043c540(LiveObject* liveObj, real32* param_2);
// <LegoRR.exe @0043c570>
void __cdecl LiveManager_UnkRadar_FUN_0043c570(real32 elapsedGame, bool32 isRadarMapView);
// <LegoRR.exe @0043c5b0>
bool32 __cdecl LiveObject_Callback_FUN_0043c5b0(LiveObject* liveObj, bool32* pIsRadarMapView);
// <LegoRR.exe @0043c6a0>
bool32 __cdecl LiveObject_FUN_0043c6a0(LiveObject* liveObj);
// <LegoRR.exe @0043c700>
uint32 __cdecl LiveObject_GetEquippedBeam(LiveObject* liveObj);
// <LegoRR.exe @0043c750>
bool32 __cdecl LiveObject_FUN_0043c750(LiveObject* liveObj, LiveObject* object2FC, sint32 param_3);
// <LegoRR.exe @0043c780>
void __cdecl LiveObject_Proc_FUN_0043c780(LiveObject* liveObj);
// <LegoRR.exe @0043c7f0>
void __cdecl LiveObject_Proc_FUN_0043c7f0(LiveObject* liveObj);
// <LegoRR.exe @0043c830>
void __cdecl LiveObject_UpdatePowerConsumption(LiveObject* liveObj);
// <LegoRR.exe @0043c910>
bool32 __cdecl LiveObject_CheckCanSteal(LiveObject* liveObj);
// <LegoRR.exe @0043c970>
void __cdecl LiveObject_FUN_0043c970(LiveObject* liveObj, real32 elapsed);
// <LegoRR.exe @0043cad0>
bool32 __cdecl Game_LiveObjectLargeCallback(LiveObject* in_liveObj, real32* lpElapsed);
// <LegoRR.exe @0043f160>
void __cdecl LiveObject_ProcCarriedObjects_FUN_0043f160(LiveObject* in_liveObj);
// <LegoRR.exe @0043f3c0>
void __cdecl LiveObject_ClearFlags4_40_AndSameForObject2FC(LiveObject* unused_liveObj, LiveObject* liveObj);
// <LegoRR.exe @0043f3f0>
void __cdecl Game_Container_TriggerFrameCallback(Container* cont, void* data);
// <LegoRR.exe @0043f410>
bool32 __cdecl LiveObject_QueueTeleport(LiveObject* liveObj, ObjectType objType, sint32 objIndex);
// <LegoRR.exe @0043f450>
void __cdecl LiveObject_FUN_0043f450(LiveObject* liveObj);
// <LegoRR.exe @0043f820>
bool32 __cdecl LiveObject_RemoveObject3CC(LiveObject* liveObj);
// <LegoRR.exe @0043f840>
bool32 __cdecl LiveObject_CallbackRemoveObject3CC(LiveObject* liveObj, LiveObject* otherObj);
// <LegoRR.exe @0043f870>
void __cdecl LiveObject_TrainMiniFigure_instantunk(LiveObject* liveObj, TrainedFlags trainFlags);
// <LegoRR.exe @0043f960>
void __cdecl LiveObject_AddDamage2(LiveObject* liveObj, real32 damage, bool32 param_3, real32 param_4);
// <LegoRR.exe @0043fa90>
void __cdecl LiveObject_UnkUpdateEnergyHealth(LiveObject* in_liveObj, real32 elapsed);
// <LegoRR.exe @0043fe00>
bool32 __cdecl LiveObject_MiniFigurePlayHurtSND(LiveObject* in_liveObj, real32 elapsed, real32 damage);
// <LegoRR.exe @0043fee0>
bool32 __cdecl LiveObject_FUN_0043fee0(LiveObject* carriedObj);
// <LegoRR.exe @00440080>
bool32 __cdecl LiveObject_UnkCarryingVehicle_FUN_00440080(LiveObject* liveObj);
// <LegoRR.exe @00440130>
bool32 __cdecl LiveObject_TryFindLoad_FUN_00440130(LiveObject* in_liveObj, LiveObject* targetObj);
// <LegoRR.exe @004402b0>
bool32 __cdecl LiveObject_TryDock_FUN_004402b0(LiveObject* in_liveObj);
// <LegoRR.exe @004403f0>
void __cdecl LiveObject_TryDock_AtBlockPos_FUN_004403f0(LiveObject* liveObj, Point2I* blockPos);
// <LegoRR.exe @00440470>
bool32 __cdecl LiveObject_FUN_00440470(LiveObject* liveObj, bool32 param_2);
// <LegoRR.exe @00440690>
bool32 __cdecl LiveObject_TryFindDriver_FUN_00440690(LiveObject* in_liveObj, LiveObject* targetObj);
// <LegoRR.exe @00440a70>
bool32 __cdecl Game_DoDynamiteExplosionCallbacks(LiveObject* liveObj, real32 damageRadius, real32 maxDamage, real32 wakeRadius);
// <LegoRR.exe @00440ac0>
bool32 __cdecl LiveObject_Callback_DynamiteRadius(LiveObject* liveObj, SearchDynamiteRadius* search);
// <LegoRR.exe @00440b80>
void __cdecl Game_DoBirdScarerRadiusCallbacks_FUN_00440b80(LiveObject* optor_liveObj, Point2F* optor_position, real32 radius);
// <LegoRR.exe @00440be0>
bool32 __cdecl LiveObject_CallbackProc_FUN_00440be0(LiveObject* liveObj, LiveObject** search);
// <LegoRR.exe @00440ca0>
void __cdecl LiveObject_SetActivityUnk(LiveObject* liveObj, ActivityType actType, bool32 unkbool2d8);
// <LegoRR.exe @00440cd0>
void __cdecl LiveObject_UpdateCarrying(LiveObject* in_liveObj);
// <LegoRR.exe @00440eb0>
void __cdecl LiveObject_InitBoulderMesh_FUN_00440eb0(LiveObject* liveObj, Container_Texture* contTexture);
// <LegoRR.exe @00440ef0>
bool32 __cdecl LiveObject_FUN_00440ef0(LiveObject* liveObj, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8);
// <LegoRR.exe @00440f30>
bool32 __cdecl LiveObject_FUN_00440f30(LiveObject* liveObj, uint32 param_2, uint32 param_3, uint32 param_4, uint32 param_5, uint32** param_6, uint32** param_7, uint32* param_8, undefined* param_9, undefined4 param_10);
// <LegoRR.exe @004413b0>
bool32 __cdecl LiveObject_FUN_004413b0(LiveObject* liveObj, uint32 bx, uint32 by, uint32 param_4, uint32 param_5, uint32** param_6, uint32** param_7, real32* param_8, void* callback, undefined4 param_10);
// <LegoRR.exe @004419c0>
bool32 __cdecl LiveObject_RoutingPtr_Alloc_FUN_004419c0(LiveObject* liveObj, uint32 count, real32* param_3, real32* param_4, real32* param_5);
// <LegoRR.exe @00441c00>
void __cdecl LiveObject_UnkDoRouting_FUN_00441c00(LiveObject* in_liveObj, bool32 param_2);
// <LegoRR.exe @00441df0>
void __cdecl LiveObject_FUN_00441df0(LiveObject* liveObj, bool32 param_2, bool32 param_3);
// <LegoRR.exe @00442160>
void __cdecl LiveObject_DestroyBoulder_AndCreateExplode(LiveObject* liveObj);
// <LegoRR.exe @00442190>
bool32 __cdecl LiveObject_Proc_FUN_00442190(LiveObject* liveObj, LiveObject* targetObj, sint32 param_3);
// <LegoRR.exe @00442390>
void __cdecl Game_GetWeaponUnk(LiveObject* liveObj, sint32 weaponType);
// <LegoRR.exe @004424d0>
void __cdecl LiveObject_UnkActivityCrumble_FUN_004424d0(LiveObject* liveObj);
// <LegoRR.exe @00442520>
void __cdecl LiveObject_GetPosition(LiveObject* liveObj, real32* out_x, real32* out_y);
// <LegoRR.exe @00442560>
void __cdecl LiveObject_GetFaceDirection(LiveObject* liveObj, Point2F* out_direction);
// <LegoRR.exe @004425c0>
void __cdecl LiveObject_UnkUpdateOrientation(LiveObject* liveObj, real32 theta, Vector3F* dvector);
// <LegoRR.exe @00442740>
float10 __cdecl LiveObject_GetHeading(LiveObject* liveObj);
// <LegoRR.exe @004427b0>
bool32 __cdecl LiveObject_GetBlockPos(LiveObject* liveObj, sint32* out_bx, sint32* out_by);
// <LegoRR.exe @00442800>
float10 __cdecl SurfaceMap_GetSurfaceZ(real32 x, real32 y, SurfaceMap* surfMap);
// <LegoRR.exe @00442820>
float10 __cdecl SurfaceMap_LevelCallback_FUN_00442820(real32 x, real32 y, SurfaceMap* surfMap);
// <LegoRR.exe @004428b0>
void __cdecl LiveObject_FUN_004428b0(LiveObject* liveObj, real32 x, real32 y);
// <LegoRR.exe @00442b60>
void __cdecl LiveObject_SetPositionAndHeading(LiveObject* liveObj, real32 xPos, real32 yPos, real32 heading, bool32 includeHeading);
// <LegoRR.exe @00442dd0>
sint32 __cdecl LiveObject_FUN_00442dd0(LiveObject* in_liveObj, real32 param_2, real32* param_3);
// <LegoRR.exe @00443240>
void __cdecl LiveObject_RockFall_FUN_00443240(LiveObject* in_liveObj, real32 param_2);
// <LegoRR.exe @004437d0>
void __cdecl LiveObject_UpdateDriverObjectPositions_FUN_004437d0(LiveObject* liveObj);
// <LegoRR.exe @00443930>
bool32 __cdecl LiveObject_FUN_00443930(LiveObject* liveObj);
// <LegoRR.exe @004439b0>
bool32 __cdecl LiveObject_IsRockMonsterCanGather(LiveObject* liveObj);
// <LegoRR.exe @004439d0>
bool32 __cdecl LiveObject_FUN_004439d0(LiveObject* liveObj, Point2I* blockPos, Point2I* out_pointUnkForI, undefined4 unused);
// <LegoRR.exe @00443ab0>
void __cdecl LiveObject_RockMonster_DoWakeUp(LiveObject* liveObj);
// <LegoRR.exe @00443b00>
bool32 __cdecl LiveObject_FUN_00443b00(LiveObject* liveObj, Point2I* blockPos, bool32* pAlsoCheckBlockFlags1_10Not8);
// <LegoRR.exe @00443b70>
real32 __cdecl LiveObject_LargeFlagsSwitch_FUN_00443b70(LiveObject* in_liveObj, real32 param_2);
// <LegoRR.exe @00444360>
void __cdecl LiveObject_TryDock_AtObject2FC(LiveObject* liveObj);
// <LegoRR.exe @004443b0>
void __cdecl LiveObject_FUN_004443b0(LiveObject* liveObj, real32 elapsed);
// <LegoRR.exe @00444520>
bool32 __cdecl LiveObject_FUN_00444520(LiveObject* liveObj);
// <LegoRR.exe @00444720>
void __cdecl LiveObject_FUN_00444720(LiveObject* liveObj, Point2F* param_2);
// <LegoRR.exe @004448e0>
void __cdecl AI_LiveObject_DoSlip(LiveObject* liveObj);
// <LegoRR.exe @00444940>
bool32 __cdecl LiveObject_RoutingUnk_FUN_00444940(LiveObject* liveObj, sint32 param_2, sint32 param_3, sint32 param_4);
// <LegoRR.exe @00445270>
void __cdecl LiveObject_FUN_00445270(LiveObject* liveObj, Point2F* point);
// <LegoRR.exe @004454a0>
void __cdecl LiveObject_FUN_004454a0(LiveObject* in_liveObj);
// <LegoRR.exe @00445600>
bool32 __cdecl LiveObject_Callback_FUN_00445600(LiveObject* liveObj1, LiveObject** param_2);
// <LegoRR.exe @00445860>
bool32 __cdecl LiveObject_FUN_00445860(LiveObject* liveObj);
// <LegoRR.exe @004459a0>
void __cdecl LiveObject_FUN_004459a0(LiveObject* liveObj);
// <LegoRR.exe @00445a30>
bool32 __cdecl LiveObject_Callback_FUN_00445a30(LiveObject* liveObj1, LiveObject* liveObj2);
// <LegoRR.exe @00445af0>
bool32 __cdecl LiveObject_Callback_FUN_00445af0(LiveObject* liveObj1, LiveObject* liveObj2);
// <LegoRR.exe @00446030>
LiveObject* __cdecl LiveObject_DoCollisionCallbacks_FUN_00446030(LiveObject* liveObj, Point2F* param_2, real32 param_3, bool32 param_4);
// <LegoRR.exe @004460b0>
bool32 __cdecl LiveObject_CallbackCollisionRadius_FUN_004460b0(LiveObject* in_liveObj, sint32* search);
// <LegoRR.exe @004463b0>
bool32 __cdecl LiveObject_CallbackCollisionBox_FUN_004463b0(LiveObject* in_liveObj, SearchCollision_14* search);
// <LegoRR.exe @004468d0>
void __cdecl LiveObject_Callback_FUN_004468d0(LiveObject* in_liveObj, real32 elapsed, real32* param_3, real32* out_float_4);
// <LegoRR.exe @00446b80>
bool32 __cdecl LiveObject_RoutingPtr_Realloc_FUN_00446b80(LiveObject* liveObj, uint32 bx, uint32 by);
// <LegoRR.exe @00446c80>
bool32 __cdecl LiveObject_BlockRoute_FUN_00446c80(LiveObject* liveObj, uint32 bx, uint32 by, bool32 param_4, uint32* out_param_5, bool32 countIs8);
// <LegoRR.exe @00447100>
bool32 __cdecl LiveObject_RouteToDig_FUN_00447100(LiveObject* liveObj, uint32 bx, uint32 by, bool32 tunnelDig);
// <LegoRR.exe @00447390>
bool32 __cdecl Game_PTL_GatherRock(LiveObject* in_liveObj);
// <LegoRR.exe @00447470>
bool32 __cdecl LiveObject_RoutingNoCarry_FUN_00447470(LiveObject* liveObj, uint32 x, uint32 y, LiveObject* liveObj2);
// <LegoRR.exe @004474d0>
bool32 __cdecl Game_PTL_AttackBuilding(LiveObject* liveObj1, LiveObject* targetObj);
// <LegoRR.exe @00447670>
sint32 __cdecl LiveObject_FUN_00447670(LiveObject* in_liveObj, real32 param_2, real32* param_3, LiveObject* liveObj2);
// <LegoRR.exe @004477b0>
void __cdecl LiveObject_FUN_004477b0(LiveObject* in_liveObj);
// <LegoRR.exe @00447880>
sint32 __cdecl LiveObject_FUN_00447880(LiveObject* in_liveObj);
// <LegoRR.exe @004479f0>
bool32 __cdecl LiveObject_Add25EnergyAndSetHealth(LiveObject* liveObj);
// <LegoRR.exe @00447a40>
void __cdecl LiveObject_FUN_00447a40(LiveObject* liveObj);
// <LegoRR.exe @00447a90>
void __cdecl LiveObject_FUN_00447a90(LiveObject* liveObj);
// <LegoRR.exe @00447bc0>
void __cdecl LiveObject_DoBuildingsCallback_AttackByBoulder(LiveObject* liveObj);
// <LegoRR.exe @00447be0>
bool32 __cdecl LiveObject_CallbackBoulderAttackBuilding_FUN_00447be0(LiveObject* liveObj, LiveObject* buildingLiveObj);
// <LegoRR.exe @00447c10>
void __cdecl LiveObject_FUN_00447c10(LiveObject* liveObj, Point2F* param_2, bool32 param_3);
// <LegoRR.exe @00447dc0>
void __cdecl LiveObject_TeleportDownBuilding(LiveObject* liveObj);
// <LegoRR.exe @00447df0>
float10 __cdecl LiveObject_FUN_00447df0(LiveObject* in_liveObj, real32 elapsed);
// <LegoRR.exe @00447f00>
bool32 __cdecl LiveObject_Container_ActivityUpdate_Check(LiveObject* liveObj);
// <LegoRR.exe @00448160>
void __cdecl LiveObject_FUN_00448160(LiveObject* in_liveObj, real32 elapsed);
// <LegoRR.exe @00448a80>
void __cdecl LiveObject_Debug_DropActivateDynamite(LiveObject* liveObj);
// <LegoRR.exe @00448ac0>
bool32 __cdecl LiveObject_TryDynamite_FUN_00448ac0(LiveObject* liveObj, Point2I* blockPos);
// <LegoRR.exe @00448b40>
bool32 __cdecl LiveObject_PlaceCarriedBirdScarerAt(LiveObject* liveObj, Point2I* blockPos);
// <LegoRR.exe @00448c60>
bool32 __cdecl LiveObject_PlaceBirdScarer_AndTickDown(LiveObject* liveObj);
// <LegoRR.exe @00448d20>
bool32 __cdecl LiveObject_TryElecFence_FUN_00448d20(LiveObject* liveObj, Point2I* blockPos);
// <LegoRR.exe @00448f10>
bool32 __cdecl LiveObject_TryBuildPath_FUN_00448f10(LiveObject* liveObj);
// <LegoRR.exe @00448f50>
bool32 __cdecl LiveObject_TryUpgrade_FUN_00448f50(LiveObject* in_liveObj, LiveObject* targetObj, sint32 targetObjLevel);
// <LegoRR.exe @00449170>
bool32 __cdecl LiveObject_TryTrain_FUN_00449170(LiveObject* liveObj, LiveObject* targetObj, bool32 set_0xE_or0xF);
// <LegoRR.exe @004492d0>
bool32 __cdecl LiveObject_TryRecharge_FUN_004492d0(LiveObject* liveObj);
// <LegoRR.exe @00449360>
bool32 __cdecl LiveObject_TryRepair_FUN_00449360(LiveObject* in_liveObj, LiveObject* targetObj, bool32 param_3, bool32 param_4);
// <LegoRR.exe @00449500>
bool32 __cdecl LiveObject_TryReinforce_FUN_00449500(LiveObject* liveObj, Point2I* blockPos);
// <LegoRR.exe @00449570>
bool32 __cdecl LiveObject_TryClear_FUN_00449570(LiveObject* liveObj, Point2I* blockPos);
// <LegoRR.exe @004496a0>
bool32 __cdecl LiveObject_MiniFigureHasBeamEquipped(LiveObject* liveObj);
// <LegoRR.exe @004496f0>
bool32 __cdecl LiveObject_TryAttackRockMonster_FUN_004496f0(LiveObject* liveObj, LiveObject* targetObj);
// <LegoRR.exe @004497e0>
bool32 __cdecl LiveObject_TryAttackObject_FUN_004497e0(LiveObject* in_liveObj, LiveObject* targetObj);
// <LegoRR.exe @004498d0>
bool32 __cdecl LiveObject_TryAttackPath_FUN_004498d0(LiveObject* liveObj, Point2I* blockPos);
// <LegoRR.exe @004499c0>
bool32 __cdecl LiveObject_TryDepart_FUN_004499c0(LiveObject* liveObj);
// <LegoRR.exe @00449b40>
bool32 __cdecl LiveObject_RoutingPointerBlocks_FUN_00449b40(LiveObject* liveObj, uint32 x, uint32 y, real32 param_4);
// <LegoRR.exe @00449c40>
bool32 __cdecl LiveObject_Reinforcing_FUN_00449c40(LiveObject* liveObj, undefined4 param_2, bool32* out_bool);
// <LegoRR.exe @00449d30>
void __cdecl LiveObject_GoEat_unk(LiveObject* liveObj);
// <LegoRR.exe @00449d80>
bool32 __cdecl LiveObject_TryGoEat_FUN_00449d80(LiveObject* liveObj1, LiveObject* liveObj2);
// <LegoRR.exe @00449ec0>
bool32 __cdecl LiveManager_AllCallback_FUN_00449ec0(void);
// <LegoRR.exe @00449ee0>
void __cdecl LiveObject_FlocksCallback_FUN_00449ee0(Flocks* flockData, FlocksItem* subdata, void* lpContext);
// <LegoRR.exe @00449f90>
void __cdecl LiveObject_Hide2(LiveObject* liveObj, bool32 hide2);
// <LegoRR.exe @00449fb0>
bool32 __cdecl LiveObject_Callback_FUN_00449fb0(LiveObject* liveObj, void* unused);
// <LegoRR.exe @0044a210>
void __cdecl LiveObject_HideAll(LiveObject* liveObj, bool32 hide);
// <LegoRR.exe @0044a2b0>
bool32 __cdecl LiveObject_IsHidden(LiveObject* liveObj);
// <LegoRR.exe @0044a330>
void __cdecl LiveObject_FP_GetPositionAndHeading(LiveObject* liveObj, sint32 cameraFrame, Vector3F* out_position, Vector3F* out_dir);
// <LegoRR.exe @0044a4c0>
Container* __cdecl LiveObject_GetContainer(LiveObject* liveObj);
// <LegoRR.exe @0044a560>
bool32 __cdecl LiveObject_GetDrillNullPosition(LiveObject* liveObj, real32* out_x, real32* out_y);
// <LegoRR.exe @0044a5d0>
void __cdecl LiveObject_FPMove(LiveObject* liveObj, sint32 forward, sint32 strafe, real32 rotate);
// <LegoRR.exe @0044a650>
void __cdecl Level_RegisterRechargeSeam(Point2I* blockPos);
// <LegoRR.exe @0044a690>
bool32 __cdecl LiveObject_FindRechargeSeam_FUN_0044a690(LiveObject* liveObj, Point2I* out_seamBlockPos);
// <LegoRR.exe @0044a770>
void __cdecl Level_RegisterSlimySlugHole(Point2I* position);
// <LegoRR.exe @0044a7b0>
bool32 __cdecl LiveObject_NearestSlugHole_FUN_0044a7b0(LiveObject* liveObj, Point2I* out_blockPos);
// <LegoRR.exe @0044a890>
bool32 __cdecl LiveObject_FUN_0044a890(LiveObject* liveObj, sint32* param_2, sint32* param_3, bool32 param_4, bool32 param_5, bool32 param_6);
// <LegoRR.exe @0044aa60>
bool32 __cdecl Lego_QsortCompare_FUN_0044aa60(sint32 param_1, sint32 param_2);
// <LegoRR.exe @0044aa90>
PolyMeshData* __cdecl Res_LoadPolyMesh(CFGProperty* aeRoot, char* rootName, char* dirname, PolyMode polyMode, uint32 numCameraFrames);
// <LegoRR.exe @0044abd0>
bool32 __cdecl Game_UnkBuildingPlaceDirection(ObjectType objType, sint32 objIndex, bool32 param_3, bool32 param_4, Point2F* mouseWorldPos, uint32 mouseBlockX, uint32 mouseBlockY, bool32 param_8, SelectPlace* selectPlace);
// <LegoRR.exe @0044af80>
void __cdecl ObjTts_Initialise(CFGProperty* root, char* keyBasePath);
// <LegoRR.exe @0044b040>
sint32 __cdecl LiveObject_GetObjTtSFX(LiveObject* liveObj);
// <LegoRR.exe @0044b080>
void __cdecl LiveManager_SetFlag20(bool32 state);
// <LegoRR.exe @0044b0a0>
void __cdecl LiveObject_FUN_0044b0a0(LiveObject* liveObj);
// <LegoRR.exe @0044b110>
void __cdecl LiveObject_SpawnDropCrystals_FUN_0044b110(LiveObject* in_liveObj, sint32 crystalCount, bool32 param_3);
// <LegoRR.exe @0044b250>
void __cdecl LiveObject_CallsSpawnDropCrystals_FUN_0044b250(LiveObject* liveObj);
// <LegoRR.exe @0044b270>
void __cdecl LiveObject_GenerateTinyRMs_FUN_0044b270(LiveObject* in_liveObj);
// <LegoRR.exe @0044b400>
void __cdecl Level_GenerateSmallSpiders(uint32 x, uint32 y, uint32 randSeed);
// <LegoRR.exe @0044b510>
void __cdecl AI_LiveObject_DoThrowLegoman(LiveObject* liveObj1, LiveObject* liveObj2);
// <LegoRR.exe @0044b610>
bool32 __cdecl Tool_IsBeamWeapon(ToolType toolType);
// <LegoRR.exe @0044b630>
void __cdecl MiniFigure_EquipTool(LiveObject* liveObj, ToolType toolType);
// <LegoRR.exe @0044b740>
bool32 __cdecl LiveObject_HasToolEquipped(LiveObject* liveObj, ToolType toolType);
// <LegoRR.exe @0044b780>
bool32 __cdecl LiveObject_TaskHasTool_FUN_0044b780(LiveObject* in_liveObj, AITaskType taskType);
// <LegoRR.exe @0044b7c0>
sint32 __cdecl LiveObject_DoGetTool(LiveObject* liveObj, ToolType toolType);
// <LegoRR.exe @0044b940>
void __cdecl LiveObject_Flocks_Initialise(LiveObject* in_liveObj);
// <LegoRR.exe @0044ba60>
void __cdecl FlocksMatrix_FUN_0044ba60(Container* resData, Matrix4F* ref_matrix, real32 scalar);
// <LegoRR.exe @0044bb10>
void __cdecl Flocks_Callback_SubdataOrientationAnim(Flocks* flocksData, FlocksItem* subdata, real32* pElapsed);
// <LegoRR.exe @0044bd70>
void __cdecl Flocks_Container_ReleaseCallback(Flocks* flockData, FlocksItem* subdata, void* lpContext);
// <LegoRR.exe @0044bda0>
void __cdecl Flocks_Free(Flocks* flockData);
// <LegoRR.exe @0044bdf0>
void __cdecl LiveObject_Flocks_SetParameters(LiveObject* liveObj, bool32 additive);
// <LegoRR.exe @0044bef0>
void __cdecl LiveObject_Flocks_FUN_0044bef0(LiveObject* liveObj, real32 elapsed);
// <LegoRR.exe @0044c0f0>
void __cdecl LiveObject_FlocksDestroy(LiveObject* liveObj);
// <LegoRR.exe @0044c1c0>
void __cdecl Flocks_Update_FUN_0044c1c0(real32* pElapsed);
// <LegoRR.exe @0044c290>
bool32 __cdecl LiveObject_DestroyRockMonster_FUN_0044c290(LiveObject* liveObj);
// <LegoRR.exe @0044c2f0>
bool32 __cdecl LiveObject_FUN_0044c2f0(LiveObject* liveObj, real32 elapsed);
// <LegoRR.exe @0044c3d0>
void __cdecl LiveObject_FUN_0044c3d0(LiveObject* liveObj);
// <LegoRR.exe @0044c410>
bool32 __cdecl LiveObject_Unk_AndSetVector3B4(LiveObject* liveObj, Point2F* param_2, real32 param_3);
// <LegoRR.exe @0044c470>
void __cdecl LiveObject_FUN_0044c470(LiveObject* liveObj, real32 elapsed);
// <LegoRR.exe @0044c760>
void __cdecl LiveObject_FUN_0044c760(LiveObject* liveObj);
// <LegoRR.exe @0044c7c0>
bool32 __cdecl LiveObject_Callback_UnkLaserTrackerToggleUnset_FUN_0044c7c0(LiveObject* liveObj, void* unused);
// <LegoRR.exe @0044c7f0>
bool32 __cdecl LiveObject_MiniFigureHasBeamEquipped2(LiveObject* liveObj);
// <LegoRR.exe @0044c810>
void __cdecl LiveManager_CheckMouseIntersections_FUN_0044c810(void);
// <LegoRR.exe @0044c8b0>
bool32 __cdecl LiveObject_Callback_CheckIntersections_FUN_0044c8b0(LiveObject* liveObj, bool32* pFalseForBuildings);
// <LegoRR.exe @0044c9d0>
void __cdecl LightEffects_Initialise(Container* resRootSpotlight, Container* resRootLight, real32 initialRed, real32 initialGreen, real32 initialBlue);
// <LegoRR.exe @0044ca20>
void __cdecl LightEffects_ResetColor(void);
// <LegoRR.exe @0044ca50>
void __cdecl LightEffects_SetDisabled(bool32 isDisabled);
// <LegoRR.exe @0044ca80>
bool32 __cdecl LightEffects_Load(CFGProperty* root, char* rootPath);
// <LegoRR.exe @0044cab0>
bool32 __cdecl LightEffects_LoadBlink(CFGProperty* root, char* rootPath);
// <LegoRR.exe @0044cc30>
void __cdecl LightEffects_SetBlink(real32 red, real32 green, real32 blue, real32 maxChange, real32 minRange, real32 maxRange);
// <LegoRR.exe @0044cc80>
bool32 __cdecl LightEffects_LoadFade(CFGProperty* root, char* rootPath);
// <LegoRR.exe @0044ced0>
void __cdecl LightEffects_SetFade(real32 minRed, real32 minGreen, real32 minBlue, real32 maxRed, real32 maxGreen, real32 maxBlue, real32 minTime, real32 maxTime, real32 minFade, real32 maxFade, real32 minHold, real32 maxHold);
// <LegoRR.exe @0044cf60>
bool32 __cdecl LightEffects_LoadMove(CFGProperty* root, char* rootPath);
// <LegoRR.exe @0044d1b0>
void __cdecl LightEffects_SetMove(real32 minTime, real32 maxTime, real32 minSpeed, real32 maxSpeed, real32 minDist, real32 maxDist, real32 limitX, real32 limitY, real32 limitZ);
// <LegoRR.exe @0044d230>
void __cdecl LightEffects_InvalidatePosition(void);
// <LegoRR.exe @0044d260>
void __cdecl LightEffects_Update(real32 elapsed);
// <LegoRR.exe @0044d2b0>
void __cdecl LightEffects_UpdateResource(void);
// <LegoRR.exe @0044d390>
void __cdecl LightEffects_UpdateBlink(real32 elapsed);
// <LegoRR.exe @0044d510>
void __cdecl LightEffects_UpdateBlink_FlipSign(real32* ref_value);
// <LegoRR.exe @0044d540>
void __cdecl LightEffects_UpdateFade(real32 elapsed);
// <LegoRR.exe @0044d9d0>
void __cdecl LightEffects_RandomizeFadeSpeedRGB(void);
// <LegoRR.exe @0044da20>
void __cdecl LightEffects_UpdateMove(real32 elapsed);
// <LegoRR.exe @0044dc60>
bool32 __cdecl LightEffects_CheckMoveLimit(Vector3F* vector);
// <LegoRR.exe @0044dce0>
void __cdecl LightEffects_SetDimmerMode(bool32 isDimoutMode);
// <LegoRR.exe @0044dd10>
void __cdecl LightEffects_UpdateDimmer(real32 elapsed);
// <LegoRR.exe @0044de10>
void __cdecl Loader_Initialise(char* loadScreenName, char* shutdownScreenName, Font* font5HI, char* profileName, Direction progressDirection, char* progressBarName, Area2F* progressWindow, char* loadingText);
// <LegoRR.exe @0044e000>
void __cdecl Loader_Shutdown(char* filename);
// <LegoRR.exe @0044e0a0>
void __cdecl Loader_display_loading_bar(char* section);
// <LegoRR.exe @0044e180>
void __cdecl Loader_FileLoadCallback(char* filename, uint32 fileSize, void* data);
// <LegoRR.exe @0044e360>
void __cdecl Loader_display_shutdown(void);
// <LegoRR.exe @0044e380>
SurfaceMap* __cdecl Map3D_LoadSurfaceMap(Container* in_resData, char* filename, real32 blockSize, real32 roughLevel);
// <LegoRR.exe @0044e790>
void __cdecl Map3D_LoadRough_FUN_0044e790(SurfaceMap* surfMap);
// <LegoRR.exe @0044e930>
void __cdecl Map3D_Free(SurfaceMap* surfMap);
// <LegoRR.exe @0044e970>
void __cdecl Map3D_SetArray40B4_IndexToTrue(SurfaceMap* surfMap, uint32 index);
// <LegoRR.exe @0044e990>
void __cdecl Map3D_FadeInBlock(SurfaceMap* surfMap, sint32 x, sint32 y, SurfaceTexture texture, uint8 field3);
// <LegoRR.exe @0044eb20>
bool32 __cdecl Map3D_IsBlockMeshHidden(SurfaceMap* surfMap, sint32 bx, sint32 by);
// <LegoRR.exe @0044eb40>
void __cdecl Map3D_UpdateAll_BlockTexturesAndVertices(SurfaceMap* surfMap);
// <LegoRR.exe @0044eb80>
bool32 __cdecl Map3D_CheckBuildingTolerance(SurfaceMap* surfMap, Point2I* shapePoints, uint32 shapeCount, real32 buildTolerance, real32 buildMaxVariation);
// <LegoRR.exe @0044ed90>
void __cdecl Map3D_FUN_0044ed90(SurfaceMap* surfMap, Point2I* shapePoints, uint32 shapeCount, real32 param_4);
// <LegoRR.exe @0044f0b0>
void __cdecl Map3D_Block_ShiftVertices_AndInitPlaneNormals(SurfaceMap* surfMap, uint32 bx, uint32 by, bool32 shiftUp);
// <LegoRR.exe @0044f270>
void __cdecl Map3D_SetFlags2_AndStruct28_SetFlag19_4(SurfaceMap* surfMap, uint32 bx, uint32 by);
// <LegoRR.exe @0044f2b0>
void __cdecl Map3D_Update(SurfaceMap* surfMap, real32 elapsedGame);
// <LegoRR.exe @0044f350>
void __cdecl Map3D_Update_Pass2_VertexColors(SurfaceMap* surfMap, real32 elapsedGame);
// <LegoRR.exe @0044f460>
void __cdecl Map3D_AddTextureCoordMapping(SurfaceMap* surfMap, SurfaceTexture texA, SurfaceTexture texB);
// <LegoRR.exe @0044f4e0>
void __cdecl Map3D_SetField_2c(SurfaceMap* surfMap, undefined4 field2c);
// <LegoRR.exe @0044f4f0>
void __cdecl Map3D_UpdateBlockVisual(SurfaceMap* surfMap, uint32 x, uint32 y, SurfaceTexture texure, uint8 field3);
// <LegoRR.exe @0044f640>
void __cdecl Map3D_Unk_ChangeWallDepth(SurfaceMap* surfMap, uint32 bx, uint32 by, real32 digDepth);
// <LegoRR.exe @0044f750>
void __cdecl Map3D_SetPerspectiveCorrectionAll(SurfaceMap* surfMap, bool32 on);
// <LegoRR.exe @0044f7a0>
WallHighlightType __cdecl Map3D_Block_SetHighlightType(SurfaceMap* surfMap, sint32 bx, sint32 by, WallHighlightType highlightType);
// <LegoRR.exe @0044f800>
WallHighlightType __cdecl Map3D_Block_GetHighlightType(SurfaceMap* surfMap, sint32 bx, sint32 by);
// <LegoRR.exe @0044f830>
void __cdecl Map3D_Block_ClearHighlight(SurfaceMap* surfMap, sint32 bx, sint32 by);
// <LegoRR.exe @0044f880>
void __cdecl Map3D_Block_SetColour(SurfaceMap* surfMap, sint32 bx, sint32 by, bool32 setColour, real32 r, real32 g, real32 b);
// <LegoRR.exe @0044f900>
bool32 __cdecl Map3D_BlockToWorldPos(SurfaceMap* surfMap, uint32 bx, uint32 by, real32* out_x, real32* out_y);
// <LegoRR.exe @0044f990>
bool32 __cdecl Map3D_WorldToBlockPos_NoZ(SurfaceMap* surfMap, real32 in_x, real32 in_y, sint32* out_bx, sint32* out_by);
// <LegoRR.exe @0044f9c0>
bool32 __cdecl Map3D_WorldToBlockPos(SurfaceMap* surfMap, real32 in_x, real32 in_y, sint32* out_bx, sint32* out_by, real32* out_unk_z);
// <LegoRR.exe @0044fad0>
void __cdecl Map3D_FUN_0044fad0(SurfaceMap* surfMap, real32 in_x, real32 in_y, sint32* out_x, sint32* out_y);
// <LegoRR.exe @0044fb30>
bool32 __cdecl Map3D_FUN_0044fb30(SurfaceMap* surfMap, Point2F* param_2, Point2F* param_3, Point2F* param_4);
// <LegoRR.exe @0044fc00>
float10 __cdecl Map3D_GetWorldZ(SurfaceMap* surfMap, real32 x, real32 y);
// <LegoRR.exe @0044fd70>
void __cdecl Map3D_FUN_0044fd70(SurfaceMap* surfMap, real32 in_x, real32 in_y, Vector3F* out_vector);
// <LegoRR.exe @0044fe50>
bool32 __cdecl Map3D_FUN_0044fe50(SurfaceMap* surfMap, real32 in_x, real32 in_y, bool32 condition, real32 unkMultiplier, real32* out_x, real32* out_y);
// <LegoRR.exe @00450130>
float10 __cdecl Map3D_UnkCameraXYFunc_RetZunk(SurfaceMap* surfMap, real32 x, real32 y);
// <LegoRR.exe @00450320>
void __cdecl Map3D_FUN_00450320(SurfaceMap* surfMap, sint32 sx, sint32 sy, Vector3F* out_vector);
// <LegoRR.exe @00450390>
bool32 __cdecl Map3D_GetBlockVertexPositions2(SurfaceMap* surfMap, uint32 bx, uint32 by, Vector3F* out_vertPoses);
// <LegoRR.exe @004504e0>
void __cdecl Map3D_GetBlockVertexPositions1(SurfaceMap* surfMap, uint32 bx, uint32 by, Vector3F* out_vertPoses);
// <LegoRR.exe @00450580>
bool32 __cdecl Map3D_IsInsideDimensions(SurfaceMap* surfMap, uint32 bx, uint32 by);
// <LegoRR.exe @004505a0>
bool32 __cdecl Map3D_GetIntersections(SurfaceMap* surfMap, Viewport* view, uint32 mouseX, uint32 mouseY, uint32* out_bx, uint32* out_by, Vector3F* out_vector);
// <LegoRR.exe @00450820>
bool32 __cdecl Map3D_Intersections_Sub1_FUN_00450820(SurfaceMap* surfMap, Vector3F* rayOrigin, Vector3F* ray, Vector3F* out_endPoint, Point2I* out_blockPos, sint32 unkCount);
// <LegoRR.exe @004508c0>
void __cdecl Map3D_AddCoordsInRadius_AndDoCallbacks(SurfaceMap* surfMap, sint32 in_bx, sint32 in_by, sint32 radius, XYCallback opt_callback);
// <LegoRR.exe @004509c0>
void __cdecl Map3D_DoForBlockIndex_Mesh_FUN_00474df0(SurfaceMap* surfMap, sint32 x, sint32 y, bool32 state);
// <LegoRR.exe @004509f0>
void __cdecl Map3D_AddBlockCoord(SurfaceMap* surfMap, sint32 cx, sint32 vy);
// <LegoRR.exe @00450a40>
void __cdecl Map3D_DoForCoordsAndClear_Mesh_FUN_00474df0(SurfaceMap* surfMap);
// <LegoRR.exe @00450a90>
void __cdecl Map3D_BlockVertexToWorldPos(SurfaceMap* surfMap, uint32 bx, uint32 by, real32* out_x, real32* out_y, real32* out_z);
// <LegoRR.exe @00450b50>
float10 __cdecl Map3D_GetBlockSize(SurfaceMap* surfMap);
// <LegoRR.exe @00450b60>
sint32 __cdecl Map3D_CheckComparison_FUN_00450b60(sint32 param_1, sint32 param_2, sint32 param_3, sint32 param_4);
// <LegoRR.exe @00450c20>
void __cdecl Map3D_Block_TextCoords_FUN_00450c20(SurfaceMap* surfMap, uint32 bx, uint32 by, bool32 param_4);
// <LegoRR.exe @00450d40>
void __cdecl Map3D_Coords_SetEmissive(SurfaceMap* surfMap, bool32 doEmissive);
// <LegoRR.exe @00450e20>
void __cdecl Map3D_Update_Pass1_CoordsTextureUVs(SurfaceMap* surfMap, real32 elapsedGame);
// <LegoRR.exe @004511f0>
void __cdecl Map3D_Block_UpdateTextureAndVertices(SurfaceMap* surfMap, uint32 bx, uint32 by);
// <LegoRR.exe @00451440>
bool32 __cdecl Map3D_BlockPair_HasTextureMatch(SurfaceMap* surfMap, uint32 bx1, uint32 by1, uint32 bx2, uint32 by2);
// <LegoRR.exe @004514f0>
void __cdecl Map3D_Block_SetIndexVertexNormal(SurfaceMap* surfMap, uint32 bx, uint32 by, uint32 vertIndex, Vector3F* vertNormal);
// <LegoRR.exe @00451590>
bool32 __cdecl Map3D_Block_GetUnkDirectionVector0_or_C(SurfaceMap* surfMap, uint32 bx, uint32 by, Direction direction, Vector3F* out_vector);
// <LegoRR.exe @00451710>
void __cdecl Map3D_Block_SetIndexVertexPosition(SurfaceMap* surfMap, uint32 bx, uint32 by, uint32 vertIndex, Vector3F* vertPosition);
// <LegoRR.exe @004517b0>
void __cdecl Map3D_Block_InitPlaneNormals(SurfaceMap* surfMap, uint32 bx, uint32 by);
// <LegoRR.exe @00451860>
void __cdecl MapFile_GetDimensions(MapFileInfo* mapFileInfo, uint32* out_width, uint32* out_height);
// <LegoRR.exe @00451880>
uint16 __cdecl MapFile_GetBlock(MapFileInfo* mapFile, sint32 x, sint32 y, sint32 width);
// <LegoRR.exe @004518a0>
bool32 __cdecl Map3D_Intersections_Sub2_FUN_004518a0(SurfaceMap* surfMap, uint32 bx, uint32 by, Vector3F* param_4, Vector3F* param_5, Vector3F* out_vector);
// <LegoRR.exe @00451c70>
PolyMeshData* __cdecl MeshPoly_Create(PolyMeshData* lastPolyData, char* partName, char* dirname, char* meshFilename, uint32 index);
// <LegoRR.exe @00451d70>
PolyMeshData* __cdecl MeshPoly_CreateNull(PolyMeshData* lastPolyData, char* partName, uint32 index);
// <LegoRR.exe @00451df0>
PolyMeshData* __cdecl MeshPoly_Duplicate(PolyMeshData* polyData);
// <LegoRR.exe @00451e80>
void __cdecl MeshPoly_Container_SwapFrame(PolyMeshData* polyData, Container* contAct, bool32 restore, sint32 frameIndex);
// <LegoRR.exe @00451ef0>
void __cdecl MeshPoly_RemoveTarget(PolyMeshData* polyData);
// <LegoRR.exe @00451f10>
void __cdecl MeshPoly_Destroy(PolyMeshData* polyData);
// <LegoRR.exe @00451f90>
void __cdecl Message_Initialise(void);
// <LegoRR.exe @00452220>
void __cdecl Message_LiveObject_FUN_00452220(LiveObject* liveObj);
// <LegoRR.exe @00452290>
sint32 __cdecl Message_LookupPTLEventIndex(char* ptlName);
// <LegoRR.exe @004522d0>
void __cdecl Message_Debug_RegisterSelectedUnitHotkey(KeysByte key, MessageType messageType, LiveObject* argumentObj, undefined4 argument2, Point2I* opt_position);
// <LegoRR.exe @00452320>
void __cdecl Message_AddMessageAction(MessageType messageType, LiveObject* argument1Obj, undefined4 argument2, Point2I* opt_blockPos);
// <LegoRR.exe @00452390>
void __cdecl Message_PTL_Update(void);
// <LegoRR.exe @004526f0>
void __cdecl Message_PTL_PickRandomFloor(LiveObject* liveObj);
// <LegoRR.exe @00452770>
void __cdecl Message_LiveObject_FUN_00452770(LiveObject* liveObj);
// <LegoRR.exe @004527e0>
bool32 __cdecl Message_CopySelectedUnits(LiveObject** out_unitsTable, uint32* out_unitsCount);
// <LegoRR.exe @00452840>
LiveObject** __cdecl Message_GetSelectedUnits2(uint32* out_count);
// <LegoRR.exe @00452870>
bool32 __cdecl Message_IsAnyUnitsSelected(void);
// <LegoRR.exe @00452880>
LiveObject* __cdecl Message_GetPrimarySelectedUnit(void);
// <LegoRR.exe @004528a0>
LiveObject** __cdecl Message_GetSelectedUnits(void);
// <LegoRR.exe @004528b0>
uint32 __cdecl Message_GetNumSelectedUnits(void);
// <LegoRR.exe @004528c0>
void __cdecl Message_CleanupSelectedUnitsCount(void);
// <LegoRR.exe @004528d0>
bool32 __cdecl Message_LiveObject_Check_IsSelected_OrFlags3_200000(LiveObject* liveObj, uint32* out_index);
// <LegoRR.exe @00452910>
bool32 __cdecl LiveObject_FindIndexOfInTable(LiveObject** objsTable, uint32 objsCount, LiveObject* thisObj, uint32* out_index);
// <LegoRR.exe @00452950>
bool32 __cdecl Message_LiveObject_Check_FUN_00452950(LiveObject* liveObj);
// <LegoRR.exe @00452980>
bool32 __cdecl Message_PTL_Select_LiveObject(LiveObject* liveObj, sint32 param_2);
// <LegoRR.exe @004529a0>
bool32 __cdecl Message_LiveObject_DoSelect_FUN_004529a0(LiveObject* liveObj, bool32 param_2, bool32 param_3);
// <LegoRR.exe @00452b30>
bool32 __cdecl Message_LiveObject_Check_FUN_00452b30(LiveObject* liveObj);
// <LegoRR.exe @00452b80>
void __cdecl Message_PTL_ReduceSelection(void);
// <LegoRR.exe @00452ea0>
void __cdecl Message_PTL_ClearSelection(void);
// <LegoRR.exe @00452f10>
bool32 __cdecl Message_PTL_Deselect_LiveObject(LiveObject* liveObj);
// <LegoRR.exe @00452f80>
uint32 __cdecl Message_PTL_Debug_DestroyAll(void);
// <LegoRR.exe @00453020>
bool32 __cdecl Message_PTL_FirstPerson(sint32 camField14);
// <LegoRR.exe @004530b0>
bool32 __cdecl NERPsFile_LoadScriptFile(char* filename);
// <LegoRR.exe @00453130>
bool32 __cdecl NERPsFile_LoadMessageFile(char* filename);
// <LegoRR.exe @004534c0>
char* __cdecl NERPsFile_GetMessageLine(uint32 lineIndex);
// <LegoRR.exe @004534e0>
bool32 __cdecl NERPsFile_Free(void);
// <LegoRR.exe @004535a0>
void __cdecl NERPsRuntime_ReserveStack_Unk(uint32* param_1);
// <LegoRR.exe @004535e0>
void __cdecl NERPsRuntime_Execute(real32 elapsedAbs);
// <LegoRR.exe @00453b60>
sint32 __cdecl NERPFunc__SetGameSpeed(sint32* stack);
// <LegoRR.exe @00453bc0>
void __cdecl NERPs_SetHasNextButton(bool32 hasNextButton);
// <LegoRR.exe @00453bd0>
void __cdecl NERPs_PlayUnkSampleIndex_IfDat_004a773c(void);
// <LegoRR.exe @00453be0>
void __cdecl NERPsRuntime_AdvanceMessage(void);
// <LegoRR.exe @00453cb0>
sint32 __cdecl NERPFunc__GetMessagesAreUpToDate(sint32* stack);
// <LegoRR.exe @00453cd0>
sint32 __cdecl NERPFunc__SupressArrow(sint32* stack);
// <LegoRR.exe @00453d10>
sint32 __cdecl NERPFunc__AdvanceMessage(sint32* stack);
// <LegoRR.exe @00453d30>
sint32 __cdecl NERPFunc__AllowCameraMovement(sint32* stack);
// <LegoRR.exe @00453d50>
sint32 __cdecl NERPFunc__ClickOnlyObjects(sint32* stack);
// <LegoRR.exe @00453d80>
sint32 __cdecl NERPFunc__ClickOnlyMap(sint32* stack);
// <LegoRR.exe @00453db0>
sint32 __cdecl NERPFunc__ClickOnlyIcon(sint32* stack);
// <LegoRR.exe @00453de0>
sint32 __cdecl NERPFunc__ClickOnlyCalltoarms(sint32* stack);
// <LegoRR.exe @00453e10>
sint32 __cdecl NERPFunc__DisallowAll(sint32* stack);
// <LegoRR.exe @00453e40>
sint32 __cdecl NERPFunc__FlashCallToArmsIcon(sint32* stack);
// <LegoRR.exe @00453e70>
void __cdecl NERPsRuntime_UpdateTimers(real32 elapsed);
// <LegoRR.exe @00453f60>
sint32 __cdecl NERPFunc__GetTimer0(sint32* stack);
// <LegoRR.exe @00453f70>
sint32 __cdecl NERPFunc__GetTimer1(sint32* stack);
// <LegoRR.exe @00453f80>
sint32 __cdecl NERPFunc__GetTimer2(sint32* stack);
// <LegoRR.exe @00453f90>
sint32 __cdecl NERPFunc__GetTimer3(sint32* stack);
// <LegoRR.exe @00453fa0>
sint32 __cdecl NERPFunc__SetTimer0(sint32* stack);
// <LegoRR.exe @00453fd0>
sint32 __cdecl NERPFunc__SetTimer1(sint32* stack);
// <LegoRR.exe @00454000>
sint32 __cdecl NERPFunc__SetTimer2(sint32* stack);
// <LegoRR.exe @00454030>
sint32 __cdecl NERPFunc__SetTimer3(sint32* stack);
// <LegoRR.exe @00454060>
void __cdecl NERPsRuntime_FUN_00454060(real32 elapsedAbs);
// <LegoRR.exe @004542a0>
sint32 __cdecl NERPFunc__CameraLockOnMonster(sint32* stack);
// <LegoRR.exe @004542e0>
bool32 __cdecl NERPsRuntime_LiveObject_GetIfRockMonsterAnd_FUN_004542e0(LiveObject* liveObj, LiveObject** out_liveObj);
// <LegoRR.exe @00454310>
sint32 __cdecl NERPFunc__CameraLockOnObject(sint32* stack);
// <LegoRR.exe @00454330>
sint32 __cdecl NERPFunc__CameraUnlock(sint32* stack);
// <LegoRR.exe @00454350>
sint32 __cdecl NERPFunc__CameraZoomIn(sint32* stack);
// <LegoRR.exe @004543d0>
sint32 __cdecl NERPFunc__CameraZoomOut(sint32* stack);
// <LegoRR.exe @00454440>
sint32 __cdecl NERPFunc__CameraRotate(sint32* stack);
// <LegoRR.exe @004544e0>
sint32 __cdecl NERPFunc__GetSelectedRecordObject(sint32* stack);
// <LegoRR.exe @00454530>
sint32 __cdecl NERPFunc__SetCrystalPriority(sint32* stack);
// <LegoRR.exe @00454550>
sint32 __cdecl NERPFunc__SetMonsterAttackPowerstation(sint32* stack);
// <LegoRR.exe @004545c0>
bool32 __cdecl NERPs_LiveObject_Callback_FUN_004545c0(LiveObject* liveObj, uint32* param_2);
// <LegoRR.exe @00454660>
sint32 __cdecl NERPFunc__SetMonsterAttackNowt(sint32* stack);
// <LegoRR.exe @004546d0>
void __cdecl NERPs_FUN_004546d0(char* objName, undefined4 param_2);
// <LegoRR.exe @00454740>
bool32 __cdecl NERPs_LiveObject_Callback_FUN_00454740(LiveObject* liveObj, sint32 param_2);
// <LegoRR.exe @00454780>
bool32 __cdecl NERPs_LiveObject_Callback_IsOnBlock_FUN_00454780(undefined4 param_1, sint32 bx, sint32 by, sint32* ref_param_4);
// <LegoRR.exe @004547f0>
sint32 __cdecl NERPFunc__GetRecordObjectAtTutorial(sint32* stack);
// <LegoRR.exe @00454860>
sint32 __cdecl NERPFunc__GetRecordObjectAmountAtTutorial(sint32* stack);
// <LegoRR.exe @004548c0>
void __cdecl NERPsRuntime_DrawTutorialIcon(LevelData* level, Viewport* viewMain, real32 elapsedGame, real32 elapsedAbs);
// <LegoRR.exe @004549c0>
sint32 __cdecl NERPFunc__SetRecordObjectPointer(sint32* stack);
// <LegoRR.exe @004549d0>
void __cdecl NERPs_FUN_004549d0(sint32* param_1);
// <LegoRR.exe @004549e0>
sint32 __cdecl NERPFunc__GetOxygenLevel(sint32* stack);
// <LegoRR.exe @00454a60>
sint32 __cdecl NERPFunc__GenerateSlug(sint32* stack);
// <LegoRR.exe @00454aa0>
sint32 __cdecl NERPFunc__SetAttackDefer(sint32* stack);
// <LegoRR.exe @00454ac0>
sint32 __cdecl NERPFunc__SetCallToArms(sint32* stack);
// <LegoRR.exe @00454ae0>
sint32 __cdecl NERPFunc__GetCallToArmsButtonClicked(sint32* stack);
// <LegoRR.exe @00454af0>
sint32 __cdecl NERPFunc__SetRockMonster(sint32* stack);
// <LegoRR.exe @00454b30>
sint32 __cdecl NERPFunc__GetRockMonstersDestroyed(sint32* stack);
// <LegoRR.exe @00454b40>
void __cdecl NERPsRuntime_IncHiddenObjectsFound(ObjectType unused_objType);
// <LegoRR.exe @00454b50>
void __cdecl NERPsRuntime_ClearHiddenObjectsFound(void);
// <LegoRR.exe @00454b60>
sint32 __cdecl NERPFunc__GetHiddenObjectsFound(sint32* stack);
// <LegoRR.exe @00454b70>
sint32 __cdecl NERPFunc__SetHiddenObjectsFound(sint32* stack);
// <LegoRR.exe @00454b80>
sint32 __cdecl NERPFunc__SetUpgradeBuildingIconClicked(sint32* stack);
// <LegoRR.exe @00454ba0>
sint32 __cdecl NERPFunc__GetUpgradeBuildingIconClicked(sint32* stack);
// <LegoRR.exe @00454bc0>
sint32 __cdecl NERPFunc__FlashUpgradeBuildingIcon(sint32* stack);
// <LegoRR.exe @00454be0>
sint32 __cdecl NERPFunc__SetGoBackIconClicked(sint32* stack);
// <LegoRR.exe @00454c00>
sint32 __cdecl NERPFunc__GetGoBackIconClicked(sint32* stack);
// <LegoRR.exe @00454c20>
sint32 __cdecl NERPFunc__FlashGoBackIcon(sint32* stack);
// <LegoRR.exe @00454c40>
sint32 __cdecl NERPFunc__GetRockMonsterRunningAway(sint32* stack);
// <LegoRR.exe @00454c70>
bool32 __cdecl NERPs_LiveObject_Callback_RockMonster_FUN_00454c70(LiveObject* liveObj, sint32* param_2);
// <LegoRR.exe @00454d20>
sint32 __cdecl NERPFunc__SetRockMonsterPainThreshold(sint32* stack);
// <LegoRR.exe @00454d60>
sint32 __cdecl NERPFunc__SetRockMonsterHealth(sint32* stack);
// <LegoRR.exe @00454da0>
sint32 __cdecl NERPFunc__SetPauseGame(sint32* stack);
// <LegoRR.exe @00454dc0>
sint32 __cdecl NERPFunc__GetAnyKeyPressed(sint32* stack);
// <LegoRR.exe @00454dd0>
sint32 __cdecl NERPFunc__SetIconPos(sint32* stack);
// <LegoRR.exe @00454e10>
sint32 __cdecl NERPFunc__SetIconSpace(sint32* stack);
// <LegoRR.exe @00454e20>
sint32 __cdecl NERPFunc__SetIconWidth(sint32* stack);
// <LegoRR.exe @00454e30>
sint32 __cdecl NERPFunc__SetLevelCompleted(sint32* stack);
// <LegoRR.exe @00454e40>
sint32 __cdecl NERPFunc__SetLevelFail(sint32* stack);
// <LegoRR.exe @00454e60>
sint32 __cdecl NERPFunc__SetGameFail(sint32* stack);
// <LegoRR.exe @00454e70>
sint32 __cdecl NERPFunc__SetTutorialPointer(sint32* stack);
// <LegoRR.exe @00454e90>
sint32 __cdecl NERPsRuntime_SetSubmenuIconClicked(char* itemName, sint32 clickedCount);
// <LegoRR.exe @00454ed0>
sint32 __cdecl NERPsRuntime_FlashSubmenuIcon(char* objName, bool32 flash);
// <LegoRR.exe @00454f10>
bool32 __cdecl NERPsRuntime_Enumerate_SetTutorialBlockClicks(BlockPointer* blockPointer, uint32 bx, uint32 by, sint32* pClickCount);
// <LegoRR.exe @00454f40>
sint32 __cdecl NERPFunc__SetTutorialBlockClicks(sint32* stack);
// <LegoRR.exe @00454f60>
bool32 __cdecl NERPsRuntime_Enumerate_SetTutorialCrystals(BlockPointer* blockPointer, uint32 bx, uint32 by, sint32* pCrystalCount);
// <LegoRR.exe @00454fd0>
sint32 __cdecl NERPFunc__SetTutorialCrystals(sint32* stack);
// <LegoRR.exe @00454ff0>
bool32 __cdecl NERPs_FUN_00454ff0(undefined4 unused, uint32 bx, sint32 by, sint32* pGenerateOre);
// <LegoRR.exe @00455050>
sint32 __cdecl NERPFunc__SetOreAtIconPositions(sint32* stack);
// <LegoRR.exe @00455070>
sint32 __cdecl NERPsRuntime_CountSelectedUnits_ByObjectName(char* objName);
// <LegoRR.exe @004550d0>
sint32 __cdecl NERPFunc__GetMiniFigureSelected(sint32* stack);
// <LegoRR.exe @004550e0>
sint32 __cdecl NERPFunc__GetSmallTruckSelected(sint32* stack);
// <LegoRR.exe @00455140>
sint32 __cdecl NERPFunc__GetSmallDiggerSelected(sint32* stack);
// <LegoRR.exe @004551a0>
sint32 __cdecl NERPFunc__GetRapidRiderSelected(sint32* stack);
// <LegoRR.exe @00455200>
sint32 __cdecl NERPFunc__GetSmallHelicopterSelected(sint32* stack);
// <LegoRR.exe @00455260>
sint32 __cdecl NERPFunc__GetGraniteGrinderSelected(sint32* stack);
// <LegoRR.exe @004552c0>
sint32 __cdecl NERPFunc__GetChromeCrusherSelected(sint32* stack);
// <LegoRR.exe @00455320>
bool32 __cdecl NERPs_Game_DoCallbacks_ByObjectName(char* objName);
// <LegoRR.exe @00455360>
bool32 __cdecl NERPs_LiveObject_Callback_ByObjectTypeIndex_IsDriving(LiveObject* liveObj1, LiveObject* liveObj_template);
// <LegoRR.exe @00455390>
sint32 __cdecl NERPFunc__AddPoweredCrystals(sint32* stack);
// <LegoRR.exe @004553c0>
sint32 __cdecl NERPFunc__AddStoredOre(sint32* stack);
// <LegoRR.exe @004553f0>
bool32 __cdecl NERPsRuntime_Callback_GetTutorialCrystals(BlockPointer* blockPointer, uint32 bx, uint32 by, sint32* out_tutorialCrystals);
// <LegoRR.exe @00455420>
sint32 __cdecl NERPFunc__GetTutorialCrystals(sint32* stack);
// <LegoRR.exe @00455450>
bool32 __cdecl NERPsRuntime_Callback_GetTutorialBlockClicks(BlockPointer* blockPointer, uint32 bx, uint32 by, sint32* out_clicks);
// <LegoRR.exe @00455480>
sint32 __cdecl NERPFunc__GetTutorialBlockClicks(sint32* stack);
// <LegoRR.exe @004554b0>
sint32 __cdecl NERPsRuntime_GetLevelObjectsBuilt(char* objName, sint32 objLevel);
// <LegoRR.exe @00455580>
bool32 __cdecl NERPsRuntime_LiveObjectCallback_GetPoweredObjectsBuilt(LiveObject* liveObj, SearchObjectTypeCount_c* search);
// <LegoRR.exe @004555c0>
uint32 __cdecl NERPsRuntime_GetPreviousLevelObjectsBuilt(char* objName, sint32 objLevel);
// <LegoRR.exe @00455600>
sint32 __cdecl NERPs_SubMenu_GetBuildingVehicleIcon_ByObjectName(char* objName);
// <LegoRR.exe @00455630>
bool32 __cdecl NERPsRuntime_FlashIcon(MenuIcon menuIcon, bool32 flash);
// <LegoRR.exe @00455680>
sint32 __cdecl NERPFunc__GetMiniFigureinGraniteGrinder(sint32* stack);
// <LegoRR.exe @00455690>
sint32 __cdecl NERPFunc__GetMiniFigureinChromeCrusher(sint32* stack);
// <LegoRR.exe @004556a0>
sint32 __cdecl NERPFunc__GetMiniFigureinSmallDigger(sint32* stack);
// <LegoRR.exe @004556b0>
sint32 __cdecl NERPFunc__GetMiniFigureinRapidRider(sint32* stack);
// <LegoRR.exe @004556c0>
sint32 __cdecl NERPFunc__GetMiniFigureinSmallTruck(sint32* stack);
// <LegoRR.exe @004556d0>
sint32 __cdecl NERPFunc__GetMiniFigureinSmallHelicopter(sint32* stack);
// <LegoRR.exe @004556e0>
sint32 __cdecl NERPFunc__SetBarracksLevel(sint32* stack);
// <LegoRR.exe @00455700>
sint32 __cdecl NERPFunc__SetDocksLevel(sint32* stack);
// <LegoRR.exe @00455720>
sint32 __cdecl NERPFunc__SetGeoDomeLevel(sint32* stack);
// <LegoRR.exe @00455740>
sint32 __cdecl NERPFunc__SetPowerstationLevel(sint32* stack);
// <LegoRR.exe @00455760>
sint32 __cdecl NERPFunc__SetToolStoreLevel(sint32* stack);
// <LegoRR.exe @00455780>
sint32 __cdecl NERPFunc__SetGunstationLevel(sint32* stack);
// <LegoRR.exe @004557a0>
sint32 __cdecl NERPFunc__SetTeleportPadLevel(sint32* stack);
// <LegoRR.exe @004557c0>
sint32 __cdecl NERPFunc__SetSuperTeleportLevel(sint32* stack);
// <LegoRR.exe @004557e0>
sint32 __cdecl NERPFunc__SetUpgradeStationLevel(sint32* stack);
// <LegoRR.exe @00455800>
sint32 __cdecl NERPFunc__GetBarracksSelected(sint32* stack);
// <LegoRR.exe @00455810>
sint32 __cdecl NERPFunc__GetDocksSelected(sint32* stack);
// <LegoRR.exe @00455820>
sint32 __cdecl NERPFunc__GetGeoDomeSelected(sint32* stack);
// <LegoRR.exe @00455830>
sint32 __cdecl NERPFunc__GetPowerstationSelected(sint32* stack);
// <LegoRR.exe @00455840>
sint32 __cdecl NERPFunc__GetToolStoreSelected(sint32* stack);
// <LegoRR.exe @00455850>
sint32 __cdecl NERPFunc__GetGunstationSelected(sint32* stack);
// <LegoRR.exe @00455860>
sint32 __cdecl NERPFunc__GetTeleportPadSelected(sint32* stack);
// <LegoRR.exe @00455870>
sint32 __cdecl NERPFunc__GetSuperTeleportSelected(sint32* stack);
// <LegoRR.exe @00455880>
sint32 __cdecl NERPFunc__GetUpgradeStationSelected(sint32* stack);
// <LegoRR.exe @00455890>
sint32 __cdecl NERPFunc__GetPoweredBarracksBuilt(sint32* stack);
// <LegoRR.exe @004558a0>
sint32 __cdecl NERPFunc__GetPoweredDocksBuilt(sint32* stack);
// <LegoRR.exe @004558b0>
sint32 __cdecl NERPFunc__GetPoweredGeodomeBuilt(sint32* stack);
// <LegoRR.exe @004558c0>
sint32 __cdecl NERPFunc__GetPoweredPowerstationsBuilt(sint32* stack);
// <LegoRR.exe @004558d0>
sint32 __cdecl NERPFunc__GetPoweredToolStoresBuilt(sint32* stack);
// <LegoRR.exe @004558e0>
sint32 __cdecl NERPFunc__GetPoweredGunstationsBuilt(sint32* stack);
// <LegoRR.exe @004558f0>
sint32 __cdecl NERPFunc__GetPoweredTeleportsBuilt(sint32* stack);
// <LegoRR.exe @00455900>
sint32 __cdecl NERPFunc__GetPoweredVehicleTeleportsBuilt(sint32* stack);
// <LegoRR.exe @00455910>
sint32 __cdecl NERPFunc__GetPoweredUpgradeStationsBuilt(sint32* stack);
// <LegoRR.exe @00455920>
sint32 __cdecl NERPFunc__GetBarracksBuilt(sint32* stack);
// <LegoRR.exe @00455930>
sint32 __cdecl NERPFunc__GetDocksBuilt(sint32* stack);
// <LegoRR.exe @00455940>
sint32 __cdecl NERPFunc__GetGeodomeBuilt(sint32* stack);
// <LegoRR.exe @00455950>
sint32 __cdecl NERPFunc__GetPowerstationsBuilt(sint32* stack);
// <LegoRR.exe @00455960>
sint32 __cdecl NERPFunc__GetToolStoresBuilt(sint32* stack);
// <LegoRR.exe @00455970>
sint32 __cdecl NERPFunc__GetGunstationsBuilt(sint32* stack);
// <LegoRR.exe @00455980>
sint32 __cdecl NERPFunc__GetTeleportsBuilt(sint32* stack);
// <LegoRR.exe @00455990>
sint32 __cdecl NERPFunc__GetVehicleTeleportsBuilt(sint32* stack);
// <LegoRR.exe @004559a0>
sint32 __cdecl NERPFunc__GetUpgradeStationsBuilt(sint32* stack);
// <LegoRR.exe @004559b0>
sint32 __cdecl NERPFunc__GetLevel1BarracksBuilt(sint32* stack);
// <LegoRR.exe @004559c0>
sint32 __cdecl NERPFunc__GetLevel1DocksBuilt(sint32* stack);
// <LegoRR.exe @004559d0>
sint32 __cdecl NERPFunc__GetLevel1GeodomeBuilt(sint32* stack);
// <LegoRR.exe @004559e0>
sint32 __cdecl NERPFunc__GetLevel1PowerstationsBuilt(sint32* stack);
// <LegoRR.exe @004559f0>
sint32 __cdecl NERPFunc__GetLevel1ToolStoresBuilt(sint32* stack);
// <LegoRR.exe @00455a00>
sint32 __cdecl NERPFunc__GetLevel1GunstationsBuilt(sint32* stack);
// <LegoRR.exe @00455a10>
sint32 __cdecl NERPFunc__GetLevel1TeleportsBuilt(sint32* stack);
// <LegoRR.exe @00455a20>
sint32 __cdecl NERPFunc__GetLevel1VehicleTeleportsBuilt(sint32* stack);
// <LegoRR.exe @00455a30>
sint32 __cdecl NERPFunc__GetLevel1UpgradeStationsBuilt(sint32* stack);
// <LegoRR.exe @00455a40>
sint32 __cdecl NERPFunc__GetLevel2BarracksBuilt(sint32* stack);
// <LegoRR.exe @00455a50>
sint32 __cdecl NERPFunc__GetLevel2DocksBuilt(sint32* stack);
// <LegoRR.exe @00455a60>
sint32 __cdecl NERPFunc__GetLevel2GeodomeBuilt(sint32* stack);
// <LegoRR.exe @00455a70>
sint32 __cdecl NERPFunc__GetLevel2PowerstationsBuilt(sint32* stack);
// <LegoRR.exe @00455a80>
sint32 __cdecl NERPFunc__GetLevel2ToolStoresBuilt(sint32* stack);
// <LegoRR.exe @00455a90>
sint32 __cdecl NERPFunc__GetLevel2GunstationsBuilt(sint32* stack);
// <LegoRR.exe @00455aa0>
sint32 __cdecl NERPFunc__GetLevel2TeleportsBuilt(sint32* stack);
// <LegoRR.exe @00455ab0>
sint32 __cdecl NERPFunc__GetLevel2VehicleTeleportsBuilt(sint32* stack);
// <LegoRR.exe @00455ac0>
sint32 __cdecl NERPFunc__GetLevel2UpgradeStationsBuilt(sint32* stack);
// <LegoRR.exe @00455ad0>
sint32 __cdecl NERPFunc__GetBarracksIconClicked(sint32* stack);
// <LegoRR.exe @00455ae0>
sint32 __cdecl NERPFunc__GetGeodomeIconClicked(sint32* stack);
// <LegoRR.exe @00455af0>
sint32 __cdecl NERPFunc__GetPowerstationIconClicked(sint32* stack);
// <LegoRR.exe @00455b00>
sint32 __cdecl NERPFunc__GetToolStoreIconClicked(sint32* stack);
// <LegoRR.exe @00455b10>
sint32 __cdecl NERPFunc__GetGunstationIconClicked(sint32* stack);
// <LegoRR.exe @00455b20>
sint32 __cdecl NERPFunc__GetTeleportPadIconClicked(sint32* stack);
// <LegoRR.exe @00455b30>
sint32 __cdecl NERPFunc__GetVehicleTransportIconClicked(sint32* stack);
// <LegoRR.exe @00455b40>
sint32 __cdecl NERPFunc__GetUpgradeStationIconClicked(sint32* stack);
// <LegoRR.exe @00455b50>
sint32 __cdecl NERPFunc__SetBarracksIconClicked(sint32* stack);
// <LegoRR.exe @00455b70>
sint32 __cdecl NERPFunc__SetGeodomeIconClicked(sint32* stack);
// <LegoRR.exe @00455b90>
sint32 __cdecl NERPFunc__SetPowerstationIconClicked(sint32* stack);
// <LegoRR.exe @00455bb0>
sint32 __cdecl NERPFunc__SetToolStoreIconClicked(sint32* stack);
// <LegoRR.exe @00455bd0>
sint32 __cdecl NERPFunc__SetGunstationIconClicked(sint32* stack);
// <LegoRR.exe @00455bf0>
sint32 __cdecl NERPFunc__SetTeleportPadIconClicked(sint32* stack);
// <LegoRR.exe @00455c10>
sint32 __cdecl NERPFunc__SetVehicleTransportIconClicked(sint32* stack);
// <LegoRR.exe @00455c30>
sint32 __cdecl NERPFunc__SetUpgradeStationIconClicked(sint32* stack);
// <LegoRR.exe @00455c50>
sint32 __cdecl NERPFunc__FlashBarracksIcon(sint32* stack);
// <LegoRR.exe @00455c70>
sint32 __cdecl NERPFunc__FlashGeodomeIcon(sint32* stack);
// <LegoRR.exe @00455c90>
sint32 __cdecl NERPFunc__FlashPowerStationIcon(sint32* stack);
// <LegoRR.exe @00455cb0>
sint32 __cdecl NERPFunc__FlashToolStoreIcon(sint32* stack);
// <LegoRR.exe @00455cd0>
sint32 __cdecl NERPFunc__FlashGunstationIcon(sint32* stack);
// <LegoRR.exe @00455cf0>
sint32 __cdecl NERPFunc__FlashTeleportPadIcon(sint32* stack);
// <LegoRR.exe @00455d10>
sint32 __cdecl NERPFunc__FlashVehicleTransportIcon(sint32* stack);
// <LegoRR.exe @00455d30>
sint32 __cdecl NERPFunc__FlashUpgradeStationIcon(sint32* stack);
// <LegoRR.exe @00455d50>
sint32 __cdecl NERPFunc__GetPathsBuilt(sint32* stack);
// <LegoRR.exe @00455d60>
sint32 __cdecl NERPFunc__GetStudCount(sint32* stack);
// <LegoRR.exe @00455d70>
sint32 __cdecl NERPFunc__GetSmallHelicoptersOnLevel(sint32* stack);
// <LegoRR.exe @00455d80>
sint32 __cdecl NERPFunc__GetGraniteGrindersOnLevel(sint32* stack);
// <LegoRR.exe @00455d90>
sint32 __cdecl NERPFunc__GetRapidRidersOnLevel(sint32* stack);
// <LegoRR.exe @00455da0>
sint32 __cdecl NERPFunc__GetSmallDiggersOnLevel(sint32* stack);
// <LegoRR.exe @00455db0>
sint32 __cdecl NERPFunc__GetSlugsOnLevel(sint32* stack);
// <LegoRR.exe @00455dc0>
sint32 __cdecl NERPFunc__GetMiniFiguresOnLevel(sint32* stack);
// <LegoRR.exe @00455dd0>
sint32 __cdecl NERPFunc__GetOreRefineriesBuilt(sint32* stack);
// <LegoRR.exe @00455de0>
sint32 __cdecl NERPFunc__GetCrystalRefineriesBuilt(sint32* stack);
// <LegoRR.exe @00455df0>
sint32 __cdecl NERPFunc__GetTeleportIconClicked(sint32* stack);
// <LegoRR.exe @00455e10>
sint32 __cdecl NERPFunc__GetDynamiteClicked(sint32* stack);
// <LegoRR.exe @00455e30>
sint32 __cdecl NERPFunc__GetMountIconClicked(sint32* stack);
// <LegoRR.exe @00455e50>
sint32 __cdecl NERPFunc__GetTrainIconClicked(sint32* stack);
// <LegoRR.exe @00455e70>
sint32 __cdecl NERPFunc__GetDropSonicBlasterIconClicked(sint32* stack);
// <LegoRR.exe @00455e90>
sint32 __cdecl NERPFunc__GetGetToolIconClicked(sint32* stack);
// <LegoRR.exe @00455eb0>
sint32 __cdecl NERPFunc__GetGetPusherIconClicked(sint32* stack);
// <LegoRR.exe @00455ed0>
sint32 __cdecl NERPFunc__GetGetSonicBlasterIconClicked(sint32* stack);
// <LegoRR.exe @00455ef0>
sint32 __cdecl NERPFunc__GetTrainSailorIconClicked(sint32* stack);
// <LegoRR.exe @00455f10>
sint32 __cdecl NERPFunc__GetTrainPilotIconClicked(sint32* stack);
// <LegoRR.exe @00455f30>
sint32 __cdecl NERPFunc__GetTrainDriverIconClicked(sint32* stack);
// <LegoRR.exe @00455f50>
sint32 __cdecl NERPFunc__GetGetLaserIconClicked(sint32* stack);
// <LegoRR.exe @00455f70>
sint32 __cdecl NERPFunc__GetDismountIconClicked(sint32* stack);
// <LegoRR.exe @00455f90>
sint32 __cdecl NERPFunc__GetDigIconClicked(sint32* stack);
// <LegoRR.exe @00455fb0>
sint32 __cdecl NERPFunc__GetBuildIconClicked(sint32* stack);
// <LegoRR.exe @00455fd0>
sint32 __cdecl NERPFunc__GetLayPathIconClicked(sint32* stack);
// <LegoRR.exe @00455ff0>
sint32 __cdecl NERPFunc__GetPlaceFenceIconClicked(sint32* stack);
// <LegoRR.exe @00456010>
sint32 __cdecl NERPFunc__SetTeleportIconClicked(sint32* stack);
// <LegoRR.exe @00456030>
sint32 __cdecl NERPFunc__SetDynamiteClicked(sint32* stack);
// <LegoRR.exe @00456050>
sint32 __cdecl NERPFunc__SetTrainIconClicked(sint32* stack);
// <LegoRR.exe @00456070>
sint32 __cdecl NERPFunc__SetTrainDriverIconClicked(sint32* stack);
// <LegoRR.exe @00456090>
sint32 __cdecl NERPFunc__SetTrainSailorIconClicked(sint32* stack);
// <LegoRR.exe @004560b0>
sint32 __cdecl NERPFunc__SetGetToolIconClicked(sint32* stack);
// <LegoRR.exe @004560d0>
sint32 __cdecl NERPFunc__SetDropSonicBlasterIconClicked(sint32* stack);
// <LegoRR.exe @004560f0>
sint32 __cdecl NERPFunc__SetGetLaserIconClicked(sint32* stack);
// <LegoRR.exe @00456110>
sint32 __cdecl NERPFunc__SetGetPusherIconClicked(sint32* stack);
// <LegoRR.exe @00456130>
sint32 __cdecl NERPFunc__SetGetSonicBlasterIconClicked(sint32* stack);
// <LegoRR.exe @00456150>
sint32 __cdecl NERPFunc__SetDismountIconClicked(sint32* stack);
// <LegoRR.exe @00456170>
sint32 __cdecl NERPFunc__SetTrainPilotIconClicked(sint32* stack);
// <LegoRR.exe @00456190>
sint32 __cdecl NERPFunc__SetMountIconClicked(sint32* stack);
// <LegoRR.exe @004561b0>
sint32 __cdecl NERPFunc__SetDigIconClicked(sint32* stack);
// <LegoRR.exe @004561d0>
sint32 __cdecl NERPFunc__SetBuildIconClicked(sint32* stack);
// <LegoRR.exe @004561f0>
sint32 __cdecl NERPFunc__SetLayPathIconClicked(sint32* stack);
// <LegoRR.exe @00456210>
sint32 __cdecl NERPFunc__SetPlaceFenceIconClicked(sint32* stack);
// <LegoRR.exe @00456230>
sint32 __cdecl NERPFunc__FlashTeleportIcon(sint32* stack);
// <LegoRR.exe @00456250>
sint32 __cdecl NERPFunc__FlashDynamiteIcon(sint32* stack);
// <LegoRR.exe @00456270>
sint32 __cdecl NERPFunc__FlashMountIcon(sint32* stack);
// <LegoRR.exe @00456290>
sint32 __cdecl NERPFunc__FlashTrainIcon(sint32* stack);
// <LegoRR.exe @004562b0>
sint32 __cdecl NERPFunc__FlashTrainDriverIcon(sint32* stack);
// <LegoRR.exe @004562d0>
sint32 __cdecl NERPFunc__FlashTrainPilotIcon(sint32* stack);
// <LegoRR.exe @004562f0>
sint32 __cdecl NERPFunc__FlashTrainSailorIcon(sint32* stack);
// <LegoRR.exe @00456310>
sint32 __cdecl NERPFunc__FlashDismountIcon(sint32* stack);
// <LegoRR.exe @00456330>
sint32 __cdecl NERPFunc__FlashGetToolIcon(sint32* stack);
// <LegoRR.exe @00456350>
sint32 __cdecl NERPFunc__FlashDropSonicBlasterIcon(sint32* stack);
// <LegoRR.exe @00456370>
sint32 __cdecl NERPFunc__FlashGetLaserIcon(sint32* stack);
// <LegoRR.exe @00456390>
sint32 __cdecl NERPFunc__FlashGetPusherIcon(sint32* stack);
// <LegoRR.exe @004563b0>
sint32 __cdecl NERPFunc__FlashGetSonicBlasterIcon(sint32* stack);
// <LegoRR.exe @004563d0>
sint32 __cdecl NERPFunc__FlashDigIcon(sint32* stack);
// <LegoRR.exe @004563f0>
sint32 __cdecl NERPFunc__FlashBuildIcon(sint32* stack);
// <LegoRR.exe @00456410>
sint32 __cdecl NERPFunc__FlashLayPathIcon(sint32* stack);
// <LegoRR.exe @00456430>
sint32 __cdecl NERPFunc__FlashPlaceFenceIcon(sint32* stack);
// <LegoRR.exe @00456450>
sint32 __cdecl NERPFunc__GetRandom(sint32* stack);
// <LegoRR.exe @00456460>
sint32 __cdecl NERPFunc__GetRandomTrueFalse(sint32* stack);
// <LegoRR.exe @00456470>
sint32 __cdecl NERPFunc__GetRandom10(sint32* stack);
// <LegoRR.exe @00456490>
sint32 __cdecl NERPFunc__GetRandom100(sint32* stack);
// <LegoRR.exe @004564b0>
sint32 __cdecl NERPFunc__GetCrystalsPickedUp(sint32* stack);
// <LegoRR.exe @004564c0>
sint32 __cdecl NERPFunc__GetCrystalsCurrentlyStored(sint32* stack);
// <LegoRR.exe @004564d0>
sint32 __cdecl NERPFunc__False(sint32* stack);
// <LegoRR.exe @004564e0>
sint32 __cdecl NERPFunc__GetOrePickedUp(sint32* stack);
// <LegoRR.exe @004564f0>
sint32 __cdecl NERPFunc__GetOreCurrentlyStored(sint32* stack);
// <LegoRR.exe @00456500>
TutorialFlags __cdecl NERPFunc__GetTutorialFlags(sint32* stack);
// <LegoRR.exe @00456510>
sint32 __cdecl NERPFunc__GetR0(sint32* stack);
// <LegoRR.exe @00456520>
sint32 __cdecl NERPFunc__GetR1(sint32* stack);
// <LegoRR.exe @00456530>
sint32 __cdecl NERPFunc__GetR2(sint32* stack);
// <LegoRR.exe @00456540>
sint32 __cdecl NERPFunc__GetR3(sint32* stack);
// <LegoRR.exe @00456550>
sint32 __cdecl NERPFunc__GetR4(sint32* stack);
// <LegoRR.exe @00456560>
sint32 __cdecl NERPFunc__GetR5(sint32* stack);
// <LegoRR.exe @00456570>
sint32 __cdecl NERPFunc__GetR6(sint32* stack);
// <LegoRR.exe @00456580>
sint32 __cdecl NERPFunc__GetR7(sint32* stack);
// <LegoRR.exe @00456590>
sint32 __cdecl NERPFunc__AddR0(sint32* stack);
// <LegoRR.exe @004565b0>
sint32 __cdecl NERPFunc__AddR1(sint32* stack);
// <LegoRR.exe @004565d0>
sint32 __cdecl NERPFunc__AddR2(sint32* stack);
// <LegoRR.exe @004565f0>
sint32 __cdecl NERPFunc__AddR3(sint32* stack);
// <LegoRR.exe @00456610>
sint32 __cdecl NERPFunc__AddR4(sint32* stack);
// <LegoRR.exe @00456630>
sint32 __cdecl NERPFunc__AddR5(sint32* stack);
// <LegoRR.exe @00456650>
sint32 __cdecl NERPFunc__AddR6(sint32* stack);
// <LegoRR.exe @00456670>
sint32 __cdecl NERPFunc__AddR7(sint32* stack);
// <LegoRR.exe @00456690>
sint32 __cdecl NERPFunc__SubR0(sint32* stack);
// <LegoRR.exe @004566b0>
sint32 __cdecl NERPFunc__SubR1(sint32* stack);
// <LegoRR.exe @004566d0>
sint32 __cdecl NERPFunc__SubR2(sint32* stack);
// <LegoRR.exe @004566f0>
sint32 __cdecl NERPFunc__SubR3(sint32* stack);
// <LegoRR.exe @00456710>
sint32 __cdecl NERPFunc__SubR4(sint32* stack);
// <LegoRR.exe @00456730>
sint32 __cdecl NERPFunc__SubR5(sint32* stack);
// <LegoRR.exe @00456750>
sint32 __cdecl NERPFunc__SubR6(sint32* stack);
// <LegoRR.exe @00456770>
sint32 __cdecl NERPFunc__SubR7(sint32* stack);
// <LegoRR.exe @00456790>
sint32 __cdecl NERPFunc__SetR0(sint32* stack);
// <LegoRR.exe @004567a0>
sint32 __cdecl NERPFunc__SetR1(sint32* stack);
// <LegoRR.exe @004567b0>
sint32 __cdecl NERPFunc__SetR2(sint32* stack);
// <LegoRR.exe @004567c0>
sint32 __cdecl NERPFunc__SetR3(sint32* stack);
// <LegoRR.exe @004567d0>
sint32 __cdecl NERPFunc__SetR4(sint32* stack);
// <LegoRR.exe @004567e0>
sint32 __cdecl NERPFunc__SetR5(sint32* stack);
// <LegoRR.exe @004567f0>
sint32 __cdecl NERPFunc__SetR6(sint32* stack);
// <LegoRR.exe @00456800>
sint32 __cdecl NERPFunc__SetR7(sint32* stack);
// <LegoRR.exe @00456810>
sint32 __cdecl NERPFunc__SetTutorialFlags(sint32* stack);
// <LegoRR.exe @00456820>
sint32 __cdecl NERPFunc__GetTrainFlags(sint32* stack);
// <LegoRR.exe @00456830>
sint32 __cdecl NERPFunc__SetTrainFlags(sint32* stack);
// <LegoRR.exe @00456840>
sint32 __cdecl NERPFunc__GetMonstersOnLevel(sint32* stack);
// <LegoRR.exe @00456880>
sint32 __cdecl NERPFunc__GetBuildingsTeleported(sint32* stack);
// <LegoRR.exe @00456890>
sint32 __cdecl NERPFunc__SetBuildingsTeleported(sint32* stack);
// <LegoRR.exe @004568b0>
sint32 __cdecl NERPFunc__SetMessagePermit(sint32* stack);
// <LegoRR.exe @00456900>
bool32 __cdecl NERPsRuntime_IsMessagePermit(void);
// <LegoRR.exe @00456910>
bool32 __cdecl NERPsRuntime_GetMessageWait(void);
// <LegoRR.exe @00456920>
sint32 __cdecl NERPFunc__SetMessageWait(sint32* stack);
// <LegoRR.exe @00456930>
sint32 __cdecl NERPFunc__SetMessageTimerValues(sint32* stack);
// <LegoRR.exe @00456980>
sint32 __cdecl NERPFunc__GetMessageTimer(sint32* stack);
// <LegoRR.exe @00456990>
sint32 __cdecl NERPFunc__SetMessage(sint32* stack);
// <LegoRR.exe @00456a80>
sint32 __cdecl NERPFunc__SetObjectiveSwitch(sint32* stack);
// <LegoRR.exe @00456a90>
sint32 __cdecl NERPFunc__GetObjectiveSwitch(sint32* stack);
// <LegoRR.exe @00456ab0>
sint32 __cdecl NERPFunc__GetObjectiveShowing(sint32* stack);
// <LegoRR.exe @00456ad0>
void __cdecl NERPs_PlayUnkSampleIndex(void);
// <LegoRR.exe @00456af0>
void __cdecl NERPs_Level_NERPMessage_Parse(char* text, undefined4* param_2, bool32 param_3);
// <LegoRR.exe @00456e40>
void __cdecl NERPs_InitBlockPointersTable(LevelData* level);
// <LegoRR.exe @00456ef0>
BlockPointer* __cdecl NERPs_GetBlockPointer(LevelData* level, sint32 blockPointerIdx);
// <LegoRR.exe @00456f20>
void __cdecl NERPs_BlockPointers_FUN_00456f20(void);
// <LegoRR.exe @00456f70>
void __cdecl NERPsRuntime_EnumerateBlockPointers(sint32 blockPointerIdx, NERPsBlockPointerCallback callback, void* data);
// <LegoRR.exe @00456fc0>
bool32 __cdecl NERPsRuntime_TutorialActionCallback(undefined4 unused, sint32 bx, sint32 by, SearchNERPsTutorialAction* search);
// <LegoRR.exe @00457320>
bool32 __cdecl NERPs_LiveObject_CallbackCheck_FUN_00457320(LiveObject* liveObj, sint32 level);
// <LegoRR.exe @00457390>
bool32 __cdecl NERPs_LiveObject_Callback_SetField3f8_FUN_00457390(LiveObject* liveObj, sint32 param_2);
// <LegoRR.exe @004573f0>
sint32 __cdecl NERPFunc__MakeSomeoneOnThisBlockPickUpSomethingOnThisBlock(sint32* stack);
// <LegoRR.exe @00457430>
void __cdecl NERPsRuntime_SetTutorialPointer(sint32 blockPointerIdx, sint32 unkMode0_1);
// <LegoRR.exe @00457520>
sint32 __cdecl NERPFunc__SetCongregationAtTutorial(sint32* stack);
// <LegoRR.exe @00457560>
sint32 __cdecl NERPFunc__SetRockMonsterAtTutorial(sint32* stack);
// <LegoRR.exe @004575a0>
sint32 __cdecl NERPFunc__SetCameraGotoTutorial(sint32* stack);
// <LegoRR.exe @004575e0>
sint32 __cdecl NERPFunc__GetCameraAtTutorial(sint32* stack);
// <LegoRR.exe @00457620>
sint32 __cdecl NERPFunc__GetTutorialBlockIsGround(sint32* stack);
// <LegoRR.exe @00457660>
sint32 __cdecl NERPFunc__GetTutorialBlockIsPath(sint32* stack);
// <LegoRR.exe @004576a0>
sint32 __cdecl NERPFunc__SetTutorialBlockIsGround(sint32* stack);
// <LegoRR.exe @004576e0>
sint32 __cdecl NERPFunc__SetTutorialBlockIsPath(sint32* stack);
// <LegoRR.exe @00457720>
sint32 __cdecl NERPFunc__GetUnitAtBlock(sint32* stack);
// <LegoRR.exe @00457760>
sint32 __cdecl NERPFunc__GetMonsterAtTutorial(sint32* stack);
// <LegoRR.exe @004577a0>
void __cdecl Objective_Level_LoadObjectiveText(CFGProperty* root, undefined4 param_2, char* param_3, LevelData* level, char* filename);
// <LegoRR.exe @00458000>
void __cdecl Objective_Level_LoadObjectiveInfo(CFGProperty* root, char* rootPath, char* levelName, LevelData* level, sint32 screenWidth, sint32 screenHeight);
// <LegoRR.exe @00458840>
void __cdecl Objective_SetCryOreObjectives(LevelData* level, sint32 crystalObjective, sint32 oreObjective);
// <LegoRR.exe @00458880>
void __cdecl Objective_SetBlockObjective(LevelData* level, Point2I* blockPos);
// <LegoRR.exe @004588b0>
void __cdecl Objective_SetTimerObjective(LevelData* level, real32 timerObjective, bool32 hitTimeFailObjective);
// <LegoRR.exe @004588e0>
void __cdecl Objective_SetConstructionObjective(LevelData* level, ObjectType objType, sint32 objIndex);
// <LegoRR.exe @00458910>
bool32 __cdecl Objective_IsLevelComplete(void);
// <LegoRR.exe @00458920>
void __cdecl Objective_SetEndTeleportEnabled(bool32 endTeleportEnabled);
// <LegoRR.exe @00458930>
void __cdecl Objective_SetCompleteStatus(LevelCompleteStatus status);
// <LegoRR.exe @00458ba0>
void __cdecl Objective_ProgrammerModeGT3_FUN_00458ba0(void);
// <LegoRR.exe @00458c60>
bool32 __cdecl Objective_IsObjectiveFinished(void);
// <LegoRR.exe @00458c80>
bool32 __cdecl Objective_HandleKeys(bool32 spaceKeyHeld, bool32 leftButtonReleasedUnk, bool32* out_gotoNextLevel);
// <LegoRR.exe @00458ea0>
void __cdecl Objective_Update(TextWindow* textWnd, LevelData* level, real32 elapsedGame, real32 elapsedAbs);
// <LegoRR.exe @00459310>
bool32 __cdecl Objective_Level_FUN_00459310(LevelData* level, bool32* out_bool, real32 elapsed);
// <LegoRR.exe @004593c0>
bool32 __cdecl Objective_LiveObjectCallback_FUN_004593c0(LiveObject* liveObj, ObjectiveData* objective);
// <LegoRR.exe @00459450>
void __cdecl ObjectRecall_StoreMiniFigure(LiveObject* liveObj);
// <LegoRR.exe @00459500>
bool32 __cdecl ObjectRecall_RecallMiniFigure(LiveObject* liveObj);
// <LegoRR.exe @00459560>
void __cdecl ObjectRecall_Save_FreeObjectRecall(void);
// <LegoRR.exe @004595a0>
void __cdecl ObjectRecall_Save_CopyToNewObjectRecallData(void);
// <LegoRR.exe @00459620>
bool32 __cdecl ObjectRecall_Save_CreateNewObjectRecall(void);
// <LegoRR.exe @00459690>
bool32 __cdecl ObjectRecall_IsLoaded(void);
// <LegoRR.exe @004596a0>
bool32 __cdecl ObjectRecall_SaveRROSFile(char* filename);
// <LegoRR.exe @00459730>
bool32 __cdecl ObjectRecall_LoadRROSFile(char* filename);
// <LegoRR.exe @004597f0>
void __cdecl ObjInfo_Initialise(CFGProperty* root, char* rootPath);
// <LegoRR.exe @00459820>
bool32 __cdecl ObjInfo_LoadHealthBar(CFGProperty* root, char* rootPath);
// <LegoRR.exe @00459bc0>
bool32 __cdecl ObjInfo_LoadHunger(CFGProperty* root, char* rootPath);
// <LegoRR.exe @00459c80>
void __cdecl ObjInfo_LoadHungerImages(CFGProperty* root, char* rootPath);
// <LegoRR.exe @00459d10>
bool32 __cdecl ObjInfo_LoadBubble(CFGProperty* root, char* rootPath);
// <LegoRR.exe @00459dc0>
void __cdecl ObjInfo_DrawHealthBar(LiveObject* liveObj, sint32 screenX, sint32 screenY);
// <LegoRR.exe @0045a210>
void __cdecl ObjInfo_DrawHungerImage(LiveObject* liveObj, sint32 screenX, sint32 screenY);
// <LegoRR.exe @0045a290>
void __cdecl ObjInfo_DrawBubbleImage(Image* image, sint32 screenX, sint32 screenY);
// <LegoRR.exe @0045a2f0>
void __cdecl Panel_Initialise(void);
// <LegoRR.exe @0045a500>
void __cdecl Panel_LoadInterfaceButtons_ScrollInfo(void);
// <LegoRR.exe @0045a530>
void __cdecl Panel_ResetAll(void);
// <LegoRR.exe @0045a5a0>
void __cdecl Panel_LoadImage(char* filename, PanelType panelType, uint32 flags);
// <LegoRR.exe @0045a630>
bool32 __cdecl Panel_GetPanelType(char* panelName, PanelType* out_panelType);
// <LegoRR.exe @0045a670>
bool32 __cdecl Panel_TestScreenImageCollision(PanelType panelType, sint32 screenX, sint32 screenY);
// <LegoRR.exe @0045a6d0>
bool32 __cdecl Panel_GetButtonType(PanelType panelType, char* buttonName, PanelButtonType* out_buttonType);
// <LegoRR.exe @0045a720>
uint32 __cdecl Panel_PrintF(PanelType panelType, Font* font, sint32 x, sint32 y, bool32 center, char* msg, ...);
// <LegoRR.exe @0045a7c0>
PanelTextWindow* __cdecl Panel_TextWindow_Create(PanelType panelType, Font* font, Area2F* rect, uint32 size);
// <LegoRR.exe @0045a850>
void __cdecl Panel_TextWindow_PrintF(PanelTextWindow* panelWnd, char* msg, ...);
// <LegoRR.exe @0045a870>
void __cdecl Panel_TextWindow_Update(PanelTextWindow* textWnd, uint32 posFromEnd, real32 elapsed);
// <LegoRR.exe @0045a8e0>
void __cdecl Panel_TextWindow_Clear(PanelTextWindow* panelWnd);
// <LegoRR.exe @0045a8f0>
void __cdecl Panel_TextWindow_GetInfo(PanelTextWindow* panelWnd, uint32* out_linesCount, uint32* out_linesCapacity);
// <LegoRR.exe @0045a910>
void __cdecl Panel_SetArea(PanelType panelType, sint32 xOut, sint32 yOut, sint32 xIn, sint32 yIn);
// <LegoRR.exe @0045a9a0>
void __cdecl Panel_SetXYField3(PanelType panelType, real32 x, real32 y);
// <LegoRR.exe @0045a9c0>
void __cdecl Panel_GetXYField3(PanelType panelType, real32* out_x, real32* out_y);
// <LegoRR.exe @0045a9f0>
void __cdecl Panel_FUN_0045a9f0(PanelType panelType, real32 elapsedAbs);
// <LegoRR.exe @0045ac80>
void __cdecl Panel_Display_FUN_0045ac80(PanelType panelType);
// <LegoRR.exe @0045ad80>
void __cdecl Panel_Button_SetFlags_10(PanelType panelType, PanelButtonType buttonType, bool32 state);
// <LegoRR.exe @0045adc0>
void __cdecl Panel_ChangeFlags_BasedOnState(PanelType panelType);
// <LegoRR.exe @0045adf0>
bool32 __cdecl Panel_IsFlags_4_Not8(PanelType panelType);
// <LegoRR.exe @0045ae20>
bool32 __cdecl Panel_IsFlags_2_Not8(PanelType panelType);
// <LegoRR.exe @0045ae50>
bool32 __cdecl Panel_IsFlags_8(PanelType panelType);
// <LegoRR.exe @0045ae70>
void __cdecl Panel_Button_SetFlag_20(PanelType panelType, PanelButtonType buttonType, bool32 setFlag20);
// <LegoRR.exe @0045aeb0>
void __cdecl Panel_Button_SetFlag_8_OrUnset_c(PanelType panelType, PanelButtonType buttonType, bool32 setFlag8);
// <LegoRR.exe @0045aef0>
void __cdecl Panel_CreateButtons(PanelType panelType, uint32 count, sint32 param_3, sint32 param_4, sint32* param_5, sint32 param_6, sint32 param_7, sint32 param_8);
// <LegoRR.exe @0045b070>
bool32 __cdecl Panel_UnkUpdate_FUN_0045b070(real32 elapsedAbs, uint32 mouseX, uint32 mouseY, bool32 leftButton, bool32 leftButtonLast, bool32* out_panelCollision);
// <LegoRR.exe @0045b5d0>
bool32 __cdecl Panel_InputProc_FUN_0045b5d0(PanelType* out_panelType, PanelButtonType* out_panelButton, sint32 mouseX, sint32 mouseY, bool32 leftButton, bool32 leftButtonLast, bool32* optout_param_7, bool32* optout_panelCollision);
// <LegoRR.exe @0045b850>
bool32 __cdecl Panel_TestMouseInsideOutInArea_FUN_0045b850(PanelData* panel, Area2F* area, sint32 mouseX, sint32 mouseY);
// <LegoRR.exe @0045b8d0>
void __cdecl Panel_UnsetFlag_6(void);
// <LegoRR.exe @0045b8e0>
void __cdecl Panel_PriorityList_FUN_0045b8e0(PanelButtonPriorityList buttonType);
// <LegoRR.exe @0045ba00>
void __cdecl Panel_ScrollInfo_Initialise(void);
// <LegoRR.exe @0045bb10>
void __cdecl Panel_Encyclopedia_Initialise(void);
// <LegoRR.exe @0045bb60>
bool32 __cdecl Panel_MathX_TestInsideCircle(sint32 x, sint32 y, sint32 centerX, sint32 centerY, sint32 radius);
// <LegoRR.exe @0045bbc0>
void __cdecl Panel_Maths_XY_Div_Radius(sint32 x, sint32 y, sint32 radius, real32* out_x, real32* out_y);
// <LegoRR.exe @0045bbf0>
void __cdecl Panel_RotationControl_GetMouseXY_FUN_0045bbf0(sint32* out_mouseX, sint32* out_mouseY, sint32 param_3, sint32 param_4, sint32 param_5);
// <LegoRR.exe @0045bc90>
void __cdecl Panel_RotationControl_Initialise(CFGProperty* root, char* rootPath);
// <LegoRR.exe @0045bf90>
bool32 __cdecl Panel_RotationControl_FUN_0045bf90(sint32 mouseX, sint32 mouseY, real32 elapsedAbs);
// <LegoRR.exe @0045c1e0>
void __cdecl Panel_RotationControl_MoveDist(bool32 doAdd, real32 amount);
// <LegoRR.exe @0045c230>
void __cdecl Panel_GetButtonRect(PanelType panelType, PanelButtonType buttonType, Area2F* out_rect);
// <LegoRR.exe @0045c270>
void __cdecl Panel_Crystals_Initialise(char* smallCrystal, char* usedCrystal, char* noSmallCrystal);
// <LegoRR.exe @0045c300>
void __cdecl Panel_Crystals_LoadRewardQuota(CFGProperty* root, char* rootPath, char* levelName);
// <LegoRR.exe @0045c390>
void __cdecl Panel_Crystals_Draw(uint32 crystals, uint32 usedCrystals, real32 elapsedGame_unused);
// <LegoRR.exe @0045c600>
void __cdecl Panel_AirMeter_Initialise(char* airJuiceName, uint32 juiceX, uint32 juiceY, uint32 juiceLength, char* noAirName, uint32 noAirX, uint32 noAirY);
// <LegoRR.exe @0045c6b0>
void __cdecl Panel_AirMeter_SetOxygen(PanelType panelType, real32 oxygen);
// <LegoRR.exe @0045c760>
void __cdecl Panel_AirMeter_SetAirBeat_UnkBool(bool32 state);
// <LegoRR.exe @0045c770>
void __cdecl Panel_AirMeter_FUN_0045c770(PanelType panelType);
// <LegoRR.exe @0045c7e0>
void __cdecl Panel_CryOreSideBar_Initialise(char* sidebarName, uint32 xPos, uint32 yPos, uint32 meterOffset);
// <LegoRR.exe @0045c840>
void __cdecl Panel_CryOreSideBar_ChangeOreMeter(bool32 increment, uint32 amount);
// <LegoRR.exe @0045c8b0>
void __cdecl Panel_CryOreSideBar_Draw(void);
// <LegoRR.exe @0045c930>
bool32 __cdecl Panel_SetCurrentAdvisorFromButton(PanelType panelType, PanelButtonType buttonType, bool32 setFlag2);
// <LegoRR.exe @0045c970>
bool32 __cdecl Panel_GetAdvisorTypeFromButton(PanelType panelType, PanelButtonType buttonType, AdvisorType* out_advisorType);
// <LegoRR.exe @0045caf0>
void __cdecl Pointer_Initialise(void);
// <LegoRR.exe @0045cd30>
void __cdecl Pointer_LoadPointers(CFGProperty* root);
// <LegoRR.exe @0045ce90>
bool32 __cdecl Pointer_GetType(char* name, PointerType* out_pointerType);
// <LegoRR.exe @0045ced0>
Image* __cdecl Pointers_GetImage(PointerType pointerType);
// <LegoRR.exe @0045cee0>
void __cdecl Pointer_SetCurrent_IfTimerFinished(PointerType pointerType);
// <LegoRR.exe @0045cf00>
void __cdecl Pointer_SetCurrent(PointerType pointerType, real32 timer);
// <LegoRR.exe @0045cf20>
PointerType __cdecl Pointer_GetCurrentType(void);
// <LegoRR.exe @0045cf30>
void __cdecl Pointer_DrawPointer(uint32 mouseX, uint32 mouseY);
// <LegoRR.exe @0045d050>
void __cdecl Pointer_Update(real32 elapsedAbs);
// <LegoRR.exe @0045d080>
void __cdecl Priorities_InitialiseImages(CFGProperty* root, char* keyBasePath);
// <LegoRR.exe @0045d1c0>
void __cdecl Priorities_Reset(void);
// <LegoRR.exe @0045d210>
bool32 __cdecl Priorities_LoadLevel(CFGProperty* root, char* rootPath, char* levelName);
// <LegoRR.exe @0045d320>
void __cdecl Priorities_InitialisePositions(CFGProperty* root, char* rootPath);
// <LegoRR.exe @0045d3d0>
bool32 __cdecl Priorities_UnkUpdate_FUN_0045d3d0(uint32 mouseX, uint32 mouseY, bool32 leftButton, bool32 param_4, bool32 param_5);
// <LegoRR.exe @0045d5c0>
bool32 __cdecl Priorities_FUN_0045d5c0(sint32 param_1, sint32 param_2, sint32 param_3);
// <LegoRR.exe @0045d630>
void __cdecl Priorities_FUN_0045d630(Point2F* param_1, uint32 param_2, uint32 param_3);
// <LegoRR.exe @0045d680>
void __cdecl Priorities_FUN_0045d680(uint32 param_1);
// <LegoRR.exe @0045d6b0>
void __cdecl Priorities_FUN_0045d6b0(uint32 param_1);
// <LegoRR.exe @0045d730>
void __cdecl Priorities_MovePriorityUp(uint32 index);
// <LegoRR.exe @0045d7b0>
void __cdecl Priorities_DisablePriority(uint32 index);
// <LegoRR.exe @0045d810>
void __cdecl Priorities_FUN_0045d810(undefined4 param_1);
// <LegoRR.exe @0045d900>
void __cdecl Priorities_FUN_0045d900(sint32 priorityIndex);
// <LegoRR.exe @0045d990>
void __cdecl Priorities_Update(void);
// <LegoRR.exe @0045daa0>
bool32 __cdecl PTL_Initialise(char* filename, char* rootPath);
// <LegoRR.exe @0045db30>
void __cdecl PTL_EventToAction(MessageAction* ref_message);
// <LegoRR.exe @0045db60>
void __cdecl RadarMap_SetTVTiltOrZoom(RadarMap* radarMap, real32 tvTiltOrZoom);
// <LegoRR.exe @0045db70>
void __cdecl RadarMap_Initialise(void);
// <LegoRR.exe @0045dd50>
RadarMap* __cdecl RadarMap_Create(SurfaceMap* surfMap, Area2F* radarViewRect, real32 tvTiltOrZoom);
// <LegoRR.exe @0045ddb0>
void __cdecl RadarMap_Free_UnwindMultiUse(RadarMap* radarMap);
// <LegoRR.exe @0045ddc0>
void __cdecl RadarMap_DrawDotCircle_FUN_0045ddc0(RadarMap* radarMap, Point2F* param_2, real32 param_3, real32 param_4);
// <LegoRR.exe @0045de80>
void __cdecl RadarMap_Draw_FUN_0045de80(RadarMap* radarMap, Point2F* position);
// <LegoRR.exe @0045e6c0>
bool32 __cdecl RadarMap_CanLiveObjectShowOnRadar(LiveObject* liveObj);
// <LegoRR.exe @0045e720>
bool32 __cdecl RadarMap_LiveObject_Callback_FUN_0045e720(LiveObject* liveObj, RadarMap* radarMap);
// <LegoRR.exe @0045e920>
bool32 __cdecl RadarMap_InsideRadarScreen(RadarMap* radarMap, uint32 mouseX, uint32 mouseY);
// <LegoRR.exe @0045e990>
bool32 __cdecl RadarMap_ScreenToWorldBlockPos(RadarMap* radarMap, uint32 mouseX, uint32 mouseY, Point2F* optout_worldPos, sint32* out_bx, sint32* out_by);
// <LegoRR.exe @0045eae0>
bool32 __cdecl RadarMap_TrySelectObject(RadarMap* radarMap, uint32 mouseX, uint32 mouseY, LiveObject** out_liveObj, Point2F* optout_objPosition);
// <LegoRR.exe @0045eba0>
bool32 __cdecl RadarMap_LiveObjectCallback_InsideSquareRadius(LiveObject* liveObj, SearchRadarObjectRadius_10* search);
// <LegoRR.exe @0045ec00>
void __cdecl RadarMap_FUN_0045ec00(RadarMap* radarMap, Area2F* ref_param_2);
// <LegoRR.exe @0045eca0>
bool32 __cdecl RadarMap_DrawBlock(Draw_Rect* drawRect, uint32 bx, uint32 by);
// <LegoRR.exe @0045f2f0>
bool32 __cdecl Reward_Initialise(void);
// <LegoRR.exe @0045f4b0>
void __cdecl Reward_LoadItemSounds(RewardLevelItem* rewardItem);
// <LegoRR.exe @0045f4f0>
void __cdecl Reward_LoadItemFonts(RewardLevelItem* rewardItem);
// <LegoRR.exe @0045f550>
void __cdecl Reward_LoadItemBoxImages(RewardLevelItem* rewardItem);
// <LegoRR.exe @0045f6a0>
void __cdecl Reward_LoadItemImages(RewardLevelItem* rewardItem);
// <LegoRR.exe @0045f7f0>
void __cdecl Reward_LoadItemText(RewardLevelItem* rewardItem);
// <LegoRR.exe @0045f8b0>
void __cdecl Reward_LoadItemFlics(RewardLevelItem* rewardItem);
// <LegoRR.exe @0045fa10>
void __cdecl Reward_Shutdown(void);
// <LegoRR.exe @0045fa70>
void __cdecl Reward_FreeItemImage(RewardLevelItem* rewardItem);
// <LegoRR.exe @0045fa90>
void __cdecl Reward_FreeItemFont(RewardLevelItem* rewardItem);
// <LegoRR.exe @0045fab0>
bool32 __cdecl Reward_LoadGraphics(CFGProperty* root, char* rootPath);
// <LegoRR.exe @0045fdb0>
bool32 __cdecl Reward_LoadButtons(CFGProperty* root, char* rootPath);
// <LegoRR.exe @00460060>
bool32 __cdecl Reward_CreateLevel(void);
// <LegoRR.exe @00460360>
void __cdecl Reward_LoadLevelItemImportance(RewardLevelItem* rewardItem);
// <LegoRR.exe @00460400>
void __cdecl Reward_LoadLevelItemQuota(RewardLevelItem* rewardItem);
// <LegoRR.exe @004604a0>
void __cdecl Reward_FreeLevel(void);
// <LegoRR.exe @004604b0>
RewardLevel* __cdecl GetRewardLevel2(undefined4 unused_levelField10);
// <LegoRR.exe @004604c0>
RewardLevel* __cdecl GetRewardLevel(void);
// <LegoRR.exe @004604e0>
void __cdecl Reward_CountUnits(void);
// <LegoRR.exe @00460550>
RewardBuildingCounts* __cdecl Reward_CountBuildings(RewardBuildingCounts* out_buildingCounts);
// <LegoRR.exe @004605d0>
bool32 __cdecl Reward_LiveObjectCallback_CountBuildings(LiveObject* liveObj, RewardBuildingCounts* search);
// <LegoRR.exe @00460620>
bool32 __cdecl Reward_Prepare(void);
// <LegoRR.exe @00460bd0>
uint32 __cdecl Reward_GetLevelObjectsBuilt(char* objName, sint32 objLevel, bool32 currentLevel);
// <LegoRR.exe @00460c10>
bool32 __cdecl Reward_PrepareCalculate(void);
// <LegoRR.exe @004611c0>
bool32 __cdecl Reward_PrepareScroll(void);
// <LegoRR.exe @00461330>
bool32 __cdecl Reward_PrepareValueText(void);
// <LegoRR.exe @004616d0>
bool32 __cdecl Reward_Show(void);
// <LegoRR.exe @00461a50>
void __cdecl Reward_DrawItem(RewardLevelItem* rewardItem, RewardItemFlags flags, RewardItemType rewardType);
// <LegoRR.exe @00461f50>
void __cdecl Reward_DrawScore(RewardItemType rewardType);
// <LegoRR.exe @00462090>
void __cdecl Reward_HandleButtons(RewardUIState* out_state, bool32* out_saved);
// <LegoRR.exe @004622f0>
void __cdecl Reward_GotoSaveMenu(void);
// <LegoRR.exe @00462530>
void __cdecl Reward_GotoAdvance(void);
// <LegoRR.exe @00462650>
void __cdecl Reward_HandleDebugKeys(RewardItemType* ref_rewardType, RewardUIState* ref_state, bool32* ref_finished, real32* ref_timer);
// <LegoRR.exe @00462720>
void __cdecl Reward_PlayFlic(RewardLevelItem* rewardItem);
// <LegoRR.exe @00462760>
void __cdecl Reward_UpdateState(RewardItemType* ref_rewardType, RewardUIState* ref_state, real32* ref_timer);
// <LegoRR.exe @004628c0>
void __cdecl Reward_DrawAllValues(RewardItemType* in_rewardType, bool32* out_finished);
// <LegoRR.exe @004629c0>
void __cdecl Reward_LoopUpdate(real32 elapsed);
// <LegoRR.exe @00462a40>
bool32 __cdecl Reward_LoopBegin(void);
// <LegoRR.exe @00462ac0>
void __cdecl Rewards_UpdateTimers(real32 elapsedGame);
// <LegoRR.exe @00462af0>
void __cdecl Rewards_WallDestroyed(void);
// <LegoRR.exe @00462b10>
void __cdecl Rewards_CavernDiscovered(void);
// <LegoRR.exe @00462b30>
void __cdecl Rewards_RockMonsterGenerated(void);
// <LegoRR.exe @00462b40>
void __cdecl Rewards_RockMonsterDestroyed(void);
// <LegoRR.exe @00462b50>
void __cdecl Rewards_RockMonsterAttacked(void);
// <LegoRR.exe @00462b60>
void __cdecl Rewards_RockMonsterDamageDealt(real32 damage);
// <LegoRR.exe @00462b80>
void __cdecl Rewards_MiniFigureDamageTaken(real32 damage);
// <LegoRR.exe @00462ba0>
RewardScroll* __cdecl RewardScroll_Create(RewardScroll** out_scroll, real32 zero, real32 heightDiv20, real32 width, real32 bottomSubDiv3pt5, real32 scrollSpeed);
// <LegoRR.exe @00462c20>
bool32 __cdecl RewardScroll_Free(RewardScroll** ref_scroll);
// <LegoRR.exe @00462c90>
RewardScrollLabel* __cdecl RewardScroll_AddLabel(RewardScroll* scroll, char* text, Font* font, real32 xPos, real32 yPos, RewardScrollLabelFlags labelFlags);
// <LegoRR.exe @00462d70>
void __cdecl RewardScroll_SetDelay_Unk(RewardScroll* scroll, real32 curScrollY);
// <LegoRR.exe @00462d80>
void __cdecl RewardScroll_AddFlags(RewardScroll* scroll, RewardScrollFlags flags);
// <LegoRR.exe @00462d90>
bool32 __cdecl RewardScroll_DrawLabels(RewardScroll* scroll);
// <LegoRR.exe @00463060>
bool32 __cdecl Roof_Initialise(Container* contRoot, sint32 width, sint32 height);
// <LegoRR.exe @00463120>
bool32 __cdecl Roof_SetTexture(char* filename);
// <LegoRR.exe @00463190>
void __cdecl Roof_Shutdown(void);
// <LegoRR.exe @004631e0>
void __cdecl Roof_LowerBlockRoofVertices(uint32 bx, uint32 by, Vector3F* vertPos0, Vector3F* vertPos1, Vector3F* vertPos2, Vector3F* vertPos3);
// <LegoRR.exe @004634f0>
void __cdecl Roof_Update(void);
// <LegoRR.exe @00463770>
void __cdecl Roof_Hide(bool32 hide);
// <LegoRR.exe @004637b0>
void __cdecl Roof_AddVisibleBlock(uint32 bx, uint32 by);
// <LegoRR.exe @00463800>
void __cdecl Roof_HideAllVisibleBlocks(void);
// <LegoRR.exe @00463850>
bool32 __cdecl Roof_GetBlockPlaneNormal(uint32 bx, uint32 by, Vector3F* out_normal);
// <LegoRR.exe @00463970>
void __cdecl ScrollInfo_Initialise(char* filename, bool32 index, uint32 unkFlags, sint32 param_4, sint32 param_5);
// <LegoRR.exe @004639f0>
void __cdecl ScrollInfo_SetXYOrSize_Unk(bool32 index, uint32 x_or_width, uint32 y_or_height);
// <LegoRR.exe @00463a30>
void __cdecl ScrollInfo_AddStruct1C(bool32 index, bool32 use50InsteadOf4c, Area2F* rect, char* opt_filename1, char* opt_filename2);
// <LegoRR.exe @00463ad0>
void __cdecl ScrollInfo_AddCreateStruct28(bool32 index, Area2F* area, sint32 number, sint32 param_4, char* filename);
// <LegoRR.exe @00463b60>
bool32 __cdecl ScrollInfo_Mouse_FUN_00463b60(sint32* out_param_1, uint32 mouseX, uint32 mouseY, bool32 param_4, bool32 param_5);
// <LegoRR.exe @00463ec0>
bool32 __cdecl ScrollInfo_FUN_00463ec0(ScrollInfoStruct_20* param_1, ScrollInfoSubStruct_1c* param_2, sint32 mouseX, sint32 mouseY);
// <LegoRR.exe @00463f50>
bool32 __cdecl ScrollInfo_FUN_00463f50(ScrollInfoStruct_20* param_1, sint32 mouseX, sint32 mouseY);
// <LegoRR.exe @00463fe0>
void __cdecl ScrollInfo_FUN_00463fe0(bool32 index);
// <LegoRR.exe @00464100>
sint64 __cdecl ScrollInfo_MathX_RoundToLL(real32 x);
// <LegoRR.exe @00464160>
void __cdecl ScrollInfo_GetSubStruct28_Fields1C_20(bool32 index, sint32* out_field1c, sint32* out_field20);
// <LegoRR.exe @00464190>
void __cdecl ScrollInfo_SetSubStruct28_Fields1C_20(bool32 index, sint32 field1c, sint32 field20);
// <LegoRR.exe @004641c0>
SelectPlace* __cdecl SelectPlace_Create(Container* contRoot, real32 float5_0);
// <LegoRR.exe @004643d0>
Point2I* __cdecl SelectPlace_TransformShapePoints(Point2I* translation, Point2I* shapePoints, sint32 shapeCount, Direction rotation);
// <LegoRR.exe @00464480>
uint32 __cdecl SelectPlace_DrawTiles(SelectPlace* selectPlace, Point2I* blockPos, Point2I* shapePoints, uint32 shapeCount, Direction direction, SurfaceMap* surfMap, sint32 waterEntrances);
// <LegoRR.exe @004649e0>
void __cdecl SelectPlace_Hide(SelectPlace* selectPlace, bool32 hide);
// <LegoRR.exe @00464a00>
void __cdecl SFX_InitHashNames(void);
// <LegoRR.exe @00464ee0>
void __cdecl SFX_Container_SoundTriggerCallback(char* sampleName, Container* cont, void* data);
// <LegoRR.exe @00464f10>
void __cdecl SFX_SetSamplePopulateMode(bool32 populate);
// <LegoRR.exe @00464f30>
bool32 __cdecl SFX_GetType(char* sfxName, SFXType* out_sfxType);
// <LegoRR.exe @00464fc0>
bool32 __cdecl SFX_Sample_LoadProperty(char* value, sint32 index);
// <LegoRR.exe @004650e0>
sint32 __cdecl SFX_Sample_Random_GetSoundHandle(SFXType sfxType);
// <LegoRR.exe @00465140>
void __cdecl SFX_StopGlobalSample(void);
// <LegoRR.exe @00465180>
bool32 __cdecl SFX_SetGlobalSampleDurationIfLE0_AndNullifyHandle(real32 duration);
// <LegoRR.exe @004651b0>
bool32 __cdecl SFX_Sample_Random_SetAndPlayGlobalSample(SFXType sfxType, sint32* out_handle);
// <LegoRR.exe @00465220>
void __cdecl SFX_Sample_AddToQueue(SFXType sfxType, SoundMode mode);
// <LegoRR.exe @00465260>
sint32 __cdecl SFX_Sample_Random_Play_OrAddToQueue(SFXType sfxType, bool32 loop);
// <LegoRR.exe @004652d0>
void __cdecl SFX_Sample_Random_SetBufferVolume(SFXType sfxType, sint32 volume);
// <LegoRR.exe @004652f0>
sint32 __cdecl SFX_Sample_Random_GetBufferVolume(SFXType sfxType);
// <LegoRR.exe @00465310>
void __cdecl SFX_Sample_Container_Random_Play_OrInitSoundUnk(Container* cont, SFXType sfxType, bool32 loop, bool32 sound3D, Vector3F* opt_position);
// <LegoRR.exe @00465350>
sint32 __cdecl SFX_Sample_Random_Play_OrInitSoundUnk(IDirect3DRMFrame3* frame, SFXType sfxType, bool32 loop, bool32 sound3D, Vector3F* opt_position);
// <LegoRR.exe @00465420>
float10 __cdecl SFX_Sample_Random_GetSamplePlayTime(SFXType sfxType);
// <LegoRR.exe @00465450>
void __cdecl SFX_Sample_Sound3D_StopSound(sint32 handle);
// <LegoRR.exe @00465460>
void __cdecl SFX_Update(real32 elapsed);
// <LegoRR.exe @00465510>
void __cdecl SFX_Sound3D_Update(void);
// <LegoRR.exe @00465520>
void __cdecl SFX_SetSoundStates_IsOn_StopAll(bool32 isSoundOn, bool32 stopAll);
// <LegoRR.exe @00465560>
void __cdecl SFX_StopAll_AndSetSoundState_IsOn(bool32 isSoundOn);
// <LegoRR.exe @00465570>
bool32 __cdecl SFX_GetFlag8(void);
// <LegoRR.exe @00465580>
void __cdecl SFX_PlayQueuedInstances_SetFlag8To(bool32 setFlag8);
// <LegoRR.exe @00465590>
void __cdecl SFX_SetFlag8To_AndOptPlayQueuedInstances(bool32 setFlag8, bool32 playQueued);
// <LegoRR.exe @00465630>
bool32 __cdecl SFX_IsSoundOn(void);
// <LegoRR.exe @00465640>
bool32 __cdecl Smoke_Initialise(void);
// <LegoRR.exe @00465660>
void __cdecl Smoke_LoadTextures(char* dirname, char* basename, uint32 count);
// <LegoRR.exe @004656f0>
SurfaceMapStruct_2a8* __cdecl Smoke_CreateSmokeArea(sint32 zero_1, uint32 bx, uint32 by, Vector3F* vector_pt1_pt1_m1, real32 r, real32 g, real32 b, real32 param_8, real32 param_9, sint32 mode0, uint32 randomness, sint32 value38);
// <LegoRR.exe @00465c30>
void __cdecl Smoke_RemoveAll(void);
// <LegoRR.exe @00465c70>
void __cdecl Smoke_Remove(SurfaceMapStruct_2a8* param_1, Container* cont28c);
// <LegoRR.exe @00465d50>
void __cdecl Smoke_HideAll(bool32 hide);
// <LegoRR.exe @00465d80>
void __cdecl Smoke_Hide(SurfaceMapStruct_2a8* param_1, bool32 hide);
// <LegoRR.exe @00465dc0>
void __cdecl Smoke_Update(real32 elapsedGame);
// <LegoRR.exe @00465f10>
sint32 __cdecl Smoke_Group_UpdateUnhide_FUN_00465f10(SurfaceMapStruct_2a8* param_1, D3DRMGroupIndex groupID);
// <LegoRR.exe @004660c0>
void __cdecl Smoke_Group_Update_FUN_004660c0(SurfaceMapStruct_2a8* param_1, D3DRMGroupIndex groupID, real32 elapsedGame);
// <LegoRR.exe @004661a0>
void __cdecl Smoke_MeshRenderCallback(Mesh* mesh, SurfaceMapStruct_2a8* data, Viewport* view);
// <LegoRR.exe @00466200>
void __cdecl Smoke_Group_MeshRenderCallback(SurfaceMapStruct_2a8* param_1, D3DRMGroupIndex groupID, Viewport* view, Vector3F* lightPos);
// <LegoRR.exe @00466480>
void __cdecl SpiderWeb_Initialise(LevelData* level);
// <LegoRR.exe @004664d0>
void __cdecl SpiderWeb_Shutdown(void);
// <LegoRR.exe @004664f0>
void __cdecl SpiderWeb_ResetAll(LevelData* level);
// <LegoRR.exe @00466510>
bool32 __cdecl SpiderWeb_SpawnAt(uint32 bx, uint32 by);
// <LegoRR.exe @00466640>
void __cdecl SpiderWeb_Add(sint32 bx, sint32 by, LiveObject* webObj);
// <LegoRR.exe @004666b0>
bool32 __cdecl SpiderWeb_GetAngle(sint32 bx, sint32 by, real32* out_theta);
// <LegoRR.exe @00466750>
bool32 __cdecl SpiderWeb_CheckCollision(LiveObject* liveObj);
// <LegoRR.exe @00466880>
bool32 __cdecl SpiderWeb_Update(real32 elapsedGame);
// <LegoRR.exe @004668a0>
bool32 __cdecl SpiderWeb_LiveObjectCallback(LiveObject* liveObj, real32* pElapsedGame);
// <LegoRR.exe @00466a10>
void __cdecl SpiderWeb_Remove(sint32 bx, sint32 by);
// <LegoRR.exe @00466aa0>
bool32 __cdecl Stats_Initialise(CFGProperty* root, char* rootPath);
// <LegoRR.exe @00469d50>
void __cdecl Stats_AddToolTaskType(ToolType toolType, AITaskType taskType);
// <LegoRR.exe @00469d80>
sint32 __cdecl Stats_GetCostOre(ObjectType objType, sint32 objIndex, sint32 objLevel);
// <LegoRR.exe @00469db0>
sint32 __cdecl Stats_GetCostCrystal(ObjectType objType, sint32 objIndex, sint32 objLevel);
// <LegoRR.exe @00469de0>
sint32 __cdecl Stats_GetCostRefinedOre(ObjectType objType, sint32 objIndex, sint32 objLevel);
// <LegoRR.exe @00469e10>
sint32 __cdecl StatsObject_GetCrystalDrain(LiveObject* liveObj);
// <LegoRR.exe @00469e40>
sint32 __cdecl StatsObject_GetCapacity(LiveObject* liveObj);
// <LegoRR.exe @00469e70>
sint32 __cdecl StatsObject_GetMaxCarry(LiveObject* liveObj);
// <LegoRR.exe @00469ea0>
sint32 __cdecl StatsObject_GetCarryStart(LiveObject* liveObj);
// <LegoRR.exe @00469ed0>
bool32 __cdecl StatsObject_SetObjectLevel(LiveObject* liveObj, uint32 level);
// <LegoRR.exe @00469f70>
float10 __cdecl StatsObject_GetRouteSpeed(LiveObject* liveObj);
// <LegoRR.exe @00469f80>
float10 __cdecl StatsObject_GetDrillTimeType(LiveObject* liveObj, SurfaceType surfaceType);
// <LegoRR.exe @00469fa0>
float10 __cdecl StatsObject_GetRubbleCoef(LiveObject* liveObj);
// <LegoRR.exe @00469fc0>
float10 __cdecl StatsObject_GetWakeRadius(LiveObject* liveObj);
// <LegoRR.exe @00469fe0>
float10 __cdecl StatsObject_GetPathCoef(LiveObject* liveObj);
// <LegoRR.exe @0046a000>
float10 __cdecl StatsObject_GetCollRadius(LiveObject* liveObj);
// <LegoRR.exe @0046a010>
float10 __cdecl StatsObject_GetCollHeight(LiveObject* liveObj);
// <LegoRR.exe @0046a020>
float10 __cdecl StatsObject_GetPickSphere(LiveObject* liveObj);
// <LegoRR.exe @0046a030>
float10 __cdecl StatsObject_GetPainThreshold(LiveObject* liveObj);
// <LegoRR.exe @0046a050>
float10 __cdecl StatsObject_GetAlertRadius(LiveObject* liveObj);
// <LegoRR.exe @0046a060>
sint32 __cdecl StatsObject_GetCollBox(LiveObject* liveObj);
// <LegoRR.exe @0046a070>
float10 __cdecl StatsObject_GetTrackDist(LiveObject* liveObj);
// <LegoRR.exe @0046a080>
float10 __cdecl StatsObject_GetHealthDecayRate(LiveObject* liveObj);
// <LegoRR.exe @0046a0a0>
float10 __cdecl StatsObject_GetEnergyDecayRate(LiveObject* liveObj);
// <LegoRR.exe @0046a0c0>
float10 __cdecl Stats_GetOxygenCoef(ObjectType objType, sint32 objIndex);
// <LegoRR.exe @0046a0e0>
float10 __cdecl StatsObject_GetOxygenCoef(LiveObject* liveObj);
// <LegoRR.exe @0046a100>
sint32 __cdecl StatsObject_GetSurveyRadius(LiveObject* liveObj);
// <LegoRR.exe @0046a120>
ObjectStatsFlags1 __cdecl StatsObject_GetStatsFlags1(LiveObject* liveObj);
// <LegoRR.exe @0046a140>
ObjectStatsFlags2 __cdecl StatsObject_GetStatsFlags2(LiveObject* liveObj);
// <LegoRR.exe @0046a160>
ObjectStatsFlags3 __cdecl StatsObject_GetStatsFlags3(LiveObject* liveObj);
// <LegoRR.exe @0046a180>
ObjectStatsFlags1 __cdecl Stats_GetStatsFlags1(ObjectType objType, sint32 objIndex);
// <LegoRR.exe @0046a1a0>
ObjectStatsFlags2 __cdecl Stats_GetStatsFlags2(ObjectType objType, sint32 objIndex);
// <LegoRR.exe @0046a1c0>
ObjectStatsFlags3 __cdecl Stats_GetStatsFlags3(ObjectType objType, sint32 objIndex);
// <LegoRR.exe @0046a1e0>
float10 __cdecl StatsObject_GetRepairValue(LiveObject* liveObj);
// <LegoRR.exe @0046a200>
uint32 __cdecl Stats_GetLevels(ObjectType objType, sint32 objIndex);
// <LegoRR.exe @0046a220>
sint32 __cdecl Stats_GetWaterEntrances(ObjectType objType, sint32 objIndex, sint32 objLevel);
// <LegoRR.exe @0046a250>
SFXType __cdecl StatsObject_GetDrillSoundType(LiveObject* liveObj, bool32 fade);
// <LegoRR.exe @0046a280>
SFXType __cdecl StatsObject_GetEngineSound(LiveObject* liveObj);
// <LegoRR.exe @0046a2a0>
float10 __cdecl StatsObject_GetRestPercent(LiveObject* liveObj);
// <LegoRR.exe @0046a2c0>
float10 __cdecl StatsObject_GetCarryMinHealth(LiveObject* liveObj);
// <LegoRR.exe @0046a2e0>
float10 __cdecl StatsObject_GetAttackRadius(LiveObject* liveObj);
// <LegoRR.exe @0046a300>
float10 __cdecl StatsObject_GetStampRadius(LiveObject* liveObj);
// <LegoRR.exe @0046a320>
sint32 __cdecl StatsObject_GetNumOfToolsCanCarry(LiveObject* liveObj);
// <LegoRR.exe @0046a340>
float10 __cdecl StatsObject_GetUpgradeTime(LiveObject* liveObj);
// <LegoRR.exe @0046a360>
float10 __cdecl StatsObject_GetFunctionCoef(LiveObject* liveObj);
// <LegoRR.exe @0046a380>
sint32 __cdecl Stats_GetUpgradeCostOre(ObjectType objType, sint32 objIndex, sint32 objLevel);
// <LegoRR.exe @0046a3b0>
sint32 __cdecl Stats_GetUpgradeCostStuds(ObjectType objType, sint32 objIndex, sint32 objLevel);
// <LegoRR.exe @0046a3e0>
bool32 __cdecl Stats_FindToolFromTaskType(AITaskType taskType, ToolType* out_toolType);
// <LegoRR.exe @0046a430>
float10 __cdecl StatsObject_GetFlocks_Height(LiveObject* liveObj);
// <LegoRR.exe @0046a450>
float10 __cdecl StatsObject_GetFlocks_Randomness(LiveObject* liveObj);
// <LegoRR.exe @0046a470>
float10 __cdecl StatsObject_GetFlocks_Turn(LiveObject* liveObj);
// <LegoRR.exe @0046a490>
float10 __cdecl StatsObject_GetFlocks_Tightness(LiveObject* liveObj);
// <LegoRR.exe @0046a4b0>
float10 __cdecl StatsObject_GetFlocks_Speed(LiveObject* liveObj);
// <LegoRR.exe @0046a4d0>
sint32 __cdecl StatsObject_GetFlocks_Size(LiveObject* liveObj);
// <LegoRR.exe @0046a4f0>
float10 __cdecl StatsObject_GetFlocks_GoalUpdate(LiveObject* liveObj);
// <LegoRR.exe @0046a510>
float10 __cdecl StatsObject_GetFlocks_AttackTime(LiveObject* liveObj);
// <LegoRR.exe @0046a530>
float10 __cdecl StatsObject_GetAwarenessRange(LiveObject* liveObj);
// <LegoRR.exe @0046a550>
float10 __cdecl StatsObject_GetPusherDist(LiveObject* liveObj);
// <LegoRR.exe @0046a570>
float10 __cdecl StatsObject_GetPusherDamage(LiveObject* liveObj);
// <LegoRR.exe @0046a590>
float10 __cdecl StatsObject_GetLaserDamage(LiveObject* liveObj);
// <LegoRR.exe @0046a5b0>
float10 __cdecl StatsObject_GetFreezerDamage(LiveObject* liveObj);
// <LegoRR.exe @0046a5d0>
float10 __cdecl StatsObject_GetObjectFreezerTime(LiveObject* liveObj);
// <LegoRR.exe @0046a5f0>
void __cdecl StatsObject_Debug_ToggleObjectPower(LiveObject* liveObj);
// <LegoRR.exe @0046a630>
void __cdecl Teleporter_Free(TeleporterService* param_1);
// <LegoRR.exe @0046a650>
void __cdecl Teleporter_RemoveAll(void);
// <LegoRR.exe @0046a680>
bool32 __cdecl Teleporter_LiveObjectCallback_Service(LiveObject* liveObj, SearchTeleporter_10* search);
// <LegoRR.exe @0046a6e0>
Point2F __cdecl Teleporter_GetCameraPosition(void);
// <LegoRR.exe @0046a730>
void __cdecl Teleporter_Add(TeleporterService* param_1);
// <LegoRR.exe @0046a750>
bool32 __cdecl Teleporter_LiveObjectCallback_Unk(LiveObject* liveObj, TeleportObjectType teleportObjType);
// <LegoRR.exe @0046a780>
bool32 __cdecl Teleporter_ServiceAll(TeleportObjectType teleportObjTypes);
// <LegoRR.exe @0046a7d0>
void __cdecl Teleporter_Start(TeleportObjectType teleportObjType, uint32 modeFlags, uint32 teleportFlags);
// <LegoRR.exe @0046a880>
bool32 __cdecl Teleporter_LiveObjectCallback_Update(LiveObject* liveObj, void* data_unused);
// <LegoRR.exe @0046a9c0>
bool32 __cdecl Teleporter_UpdateService(TeleporterService* teleporter, real32 elapsedGame);
// <LegoRR.exe @0046a9f0>
void __cdecl Teleporter_Update(real32 elapsedGame);
// <LegoRR.exe @0046aa20>
ObjectType __cdecl Teleporter_GetServiceObjectType(TeleportObjectType teleportObjType);
// <LegoRR.exe @0046aab0>
void __cdecl Text_Load(TextWindow* param_1, TextWindow* param_2, sint32 imageX, sint32 imageY, real32 pauseTime);
// <LegoRR.exe @0046ac10>
void __cdecl Text_Initialise(char* filename, uint32 param_2, uint32 param_3, uint32 unused_int, Area2F* param_5, Area2F* unused_rect, real32 param_7);
// <LegoRR.exe @0046aca0>
void __cdecl Text_UpdatePositionAndSize(void);
// <LegoRR.exe @0046ad50>
void __cdecl Text_Clear(void);
// <LegoRR.exe @0046ad90>
bool32 __cdecl Text_GetTextType(char* textName, TextType* out_textType);
// <LegoRR.exe @0046add0>
void __cdecl Text_SetMessage(TextType textType, char* textMessage);
// <LegoRR.exe @0046ae70>
void __cdecl Text_SetMessageWithImage(TextType textType, char* message, char* filename, char* sfxName);
// <LegoRR.exe @0046aee0>
void __cdecl Text_SetNERPsMessage(char* text, uint32 unkFlags);
// <LegoRR.exe @0046af20>
void __cdecl Text_DisplayMessage(TextType textType, bool32 changeTiming, bool32 setFlag4);
// <LegoRR.exe @0046afc0>
void __cdecl Text_Update(real32 elapsedAbs);
// <LegoRR.exe @0046b490>
void __cdecl ToolTip_Initialise(Font* font, sint32 value2, sint32 value1, real32 float1, uint32 width, uint32 height, sint32 value32, real32 red, real32 green, real32 blue);
// <LegoRR.exe @0046b790>
bool32 __cdecl ToolTip_GetType(char* toolTipName, ToolTipType* out_toolTipType);
// <LegoRR.exe @0046b7e0>
void __cdecl ToolTip_SetText(ToolTipType toolTipType, char* msg, ...);
// <LegoRR.exe @0046b920>
void __cdecl ToolTip_AddIcon(ToolTipType toolTipType, Image* image);
// <LegoRR.exe @0046b9c0>
void __cdecl ToolTip_SetSFX(ToolTipType toolTipType, SFXType sfxType);
// <LegoRR.exe @0046b9f0>
void __cdecl ToolTip_SetFlag10(ToolTipType toolTipType, bool32 state);
// <LegoRR.exe @0046ba30>
void __cdecl ToolTip_AddFlag4(ToolTipType toolTipType);
// <LegoRR.exe @0046ba60>
void __cdecl ToolTip_ResetTimer(ToolTipType toolTipType);
// <LegoRR.exe @0046ba80>
void __cdecl ToolTip_Update(uint32 mousex, uint32 mousey, real32 elapsedAbs);
// <LegoRR.exe @0046bb70>
void __cdecl ToolTip_DrawBox(Area2F valueRect, real32 rcRed, real32 rcGreen, real32 rcBlue, real32 ln1Red, real32 ln1Green, real32 ln1Blue, real32 ln2Red, real32 ln2Green, real32 ln2Blue, bool32 halfTrans);
// <LegoRR.exe @0046bef0>
void __cdecl ToolTip_Draw(ToolTipData* toolTip, uint32 x, uint32 y);
// <LegoRR.exe @0046c2f0>
void __cdecl Upgrade_LoadActivityFile(UpgradeData* out_upgrade, sint32 objIndex, Container* resRoot, char* filename);
// <LegoRR.exe @0046c370>
void __cdecl Upgrade_Duplicate(UpgradeData* in_upgrade, UpgradeData* out_upgrade);
// <LegoRR.exe @0046c3b0>
void __cdecl Upgrade_Destroy(UpgradeData* upgrade);
// <LegoRR.exe @0046c3d0>
float10 __cdecl Upgrade_DoAnimElapsedCallbacks(UpgradeData* upgrade, real32 elapsed, bool32 unused_bool);
// <LegoRR.exe @0046c3f0>
bool32 __cdecl Upgrade_SetActivity(UpgradeData* upgrade, char* activityName);
// <LegoRR.exe @0046c420>
void __cdecl Upgrade_LoadUpgradeLevels(ObjectUpgradesData* upgrades, CFGProperty* aeRoot, char* rootName);
// <LegoRR.exe @0046c600>
void __cdecl Upgrade_ChangeUpgradeParts(ObjectUpgradesData* upgrades, sint32 objLevel);
// <LegoRR.exe @0046c690>
bool32 __cdecl Vehicle_IsCameraFlipDir(VehicleData* vehicle);
// <LegoRR.exe @0046c6b0>
bool32 __cdecl Vehicle_SetActivity_AndRemoveCarryCameraFrames(VehicleData* vehicle, char* activityName, real32 elapsed);
// <LegoRR.exe @0046c7d0>
void __cdecl Vehicle_SetUpgradeActivity(VehicleData* vehicle, char* activityName);
// <LegoRR.exe @0046c9b0>
bool32 __cdecl Vehicle_LoadActivityFile(VehicleData* vehicle, sint32 objIndex, Container* resRoot, char* aeFilename, char* rootName);
// <LegoRR.exe @0046d0d0>
void __cdecl Vehicle_Destroy(VehicleData* vehicle);
// <LegoRR.exe @0046d190>
void __cdecl Vehicle_SwapPolyMedium(VehicleData* vehicle, bool32 swap);
// <LegoRR.exe @0046d1e0>
void __cdecl Vehicle_SwapPolyHigh(VehicleData* vehicle, bool32 swap);
// <LegoRR.exe @0046d200>
bool32 __cdecl Vehicle_HasUpgradeLevelMask(VehicleData* vehicle, sint32 levelBit, bool32 condition);
// <LegoRR.exe @0046d240>
sint32 __cdecl Vehicle_GetUpgradesCurrentLevel(VehicleData* vehicle);
// <LegoRR.exe @0046d250>
void __cdecl Vehicle_ChangeUpgradeParts(VehicleData* vehicle, sint32 objLevel);
// <LegoRR.exe @0046d280>
void __cdecl Vehicle_HideWheels(VehicleData* vehicle, bool32 hide);
// <LegoRR.exe @0046d2b0>
bool32 __cdecl Vehicle_Duplicate(VehicleData* in_vehicle, VehicleData* out_vehicle);
// <LegoRR.exe @0046d400>
void __cdecl Vehicle_SetOwnerObject(VehicleData* vehicle, void* liveObj);
// <LegoRR.exe @0046d460>
float10 __cdecl Vehicle_GetAnimationTime(VehicleData* vehicle);
// <LegoRR.exe @0046d480>
float10 __cdecl Vehicle_FUN_0046d480(VehicleData* vehicle, real32 elapsed, real32 elapsed2, uint32 param_4);
// <LegoRR.exe @0046d520>
void __cdecl Vehicle_Wheels_FUN_0046d520(VehicleData* vehicle);
// <LegoRR.exe @0046d580>
void __cdecl Vehicle_HideAll(VehicleData* vehicle, bool32 hide);
// <LegoRR.exe @0046d5f0>
bool32 __cdecl Vehicle_GetFlag2(VehicleData* vehicle);
// <LegoRR.exe @0046d610>
void __cdecl Vehicle_SetOrientation(VehicleData* vehicle, real32 x, real32 y, real32 z);
// <LegoRR.exe @0046d640>
void __cdecl Vehicle_SetPosition(VehicleData* vehicle, real32 x, real32 y, GetSurfaceZFunc getSurfaceZFunc, SurfaceMap* surfMap);
// <LegoRR.exe @0046dca0>
Container* __cdecl Vehicle_GetActivityContainer(VehicleData* vehicle);
// <LegoRR.exe @0046dcb0>
Container* __cdecl Vehicle_GetNull(VehicleData* vehicle, char* nullName, sint32 nullIndex);
// <LegoRR.exe @0046dd10>
Container* __cdecl Vehicle_GetCameraNull(VehicleData* vehicle, sint32 cameraIndex);
// <LegoRR.exe @0046dd50>
Container* __cdecl Vehicle_GetDrillNull(VehicleData* vehicle);
// <LegoRR.exe @0046dd80>
Container* __cdecl Vehicle_GetDepositNull(VehicleData* vehicle);
// <LegoRR.exe @0046ddb0>
Container* __cdecl Vehicle_GetDriverNull(VehicleData* vehicle);
// <LegoRR.exe @0046dde0>
Container* __cdecl Vehicle_GetCarryNull(VehicleData* vehicle, sint32 carryIndex);
// <LegoRR.exe @0046de20>
sint32 __cdecl Vehicle_GetCarryNullFrames(VehicleData* vehicle);
// <LegoRR.exe @0046de30>
float10 __cdecl Vehicle_GetTransCoef(VehicleData* vehicle);
// <LegoRR.exe @0046de50>
void __cdecl Water_Initialise(Container* contRoot, LevelData* level);
// <LegoRR.exe @0046dfd0>
void __cdecl Water_InitGroups(Container* contRoot, LevelData* level);
// <LegoRR.exe @0046e140>
void __cdecl Water_InitVertices(Container* contRoot, LevelData* level);
// <LegoRR.exe @0046e480>
void __cdecl Water_Debug_LogContainerMesh(bool32 logWithValues);
// <LegoRR.exe @0046e4e0>
void __cdecl Water_Block_DestroyWallComplete(LevelData* level, uint32 bx, uint32 by);
// <LegoRR.exe @0046e5f0>
void __cdecl Water_Block_Debug_WKey(uint32 bx, uint32 by);
// <LegoRR.exe @0046e650>
void __cdecl Water_Update(LevelData* level, real32 elapsedGame);
// <LegoRR.exe @0046e8d0>
void __cdecl Water_UpdateMap3DBlocks(LevelData* level);
// <LegoRR.exe @0046eb60>
WaterEntry* __cdecl Water_Block_SubDestroyWall_AndDebug_WKey(uint32 bx, uint32 by, uint32* out_pointIndex);
// <LegoRR.exe @0046ec60>
sint32 __cdecl Water_QsortCompare(WaterEntry* a, WaterEntry* b);
// <LegoRR.exe @0046ec90>
WaterEntry* __cdecl Water_InitSearchAddPairs(sint32 y, uint32 xAlign, uint32 xMax);
// <LegoRR.exe @0046ed90>
void __cdecl Water_InitAddPoint(WaterEntry* entry, uint32 y, uint32 xAlign, uint32 xMax);
// <LegoRR.exe @0046edf0>
void __cdecl Water_InitAddPointFirst(uint32 y, uint32 xAlign, uint32 xMax);
// <LegoRR.exe @0046ee40>
bool32 __cdecl Weapon_Initialise(CFGProperty* root, char* rootPath);
// <LegoRR.exe @0046f390>
uint32 __cdecl Weapon_GetWeaponTypeByName(char* weaponName);
// <LegoRR.exe @0046f3d0>
float10 __cdecl Weapon_GetRechargeTime(sint32 weaponType);
// <LegoRR.exe @0046f400>
float10 __cdecl Weapon_GetDischargeRate(sint32 weaponType);
// <LegoRR.exe @0046f430>
float10 __cdecl Weapon_GetWeaponRange(sint32 weaponType);
// <LegoRR.exe @0046f460>
float10 __cdecl Weapon_GetWallDestroyTime(sint32 weaponType, SurfaceType surfaceType);
// <LegoRR.exe @0046f490>
float10 __cdecl Weapon_GetDamageForLiveObject(sint32 weaponType, LiveObject* liveObj);
// <LegoRR.exe @0046f530>
void __cdecl Weapon_LiveObject_FUN_0046f530(LiveObject* liveObj, sint32 weaponType, bool32 param_3, real32 param_4, Point2F* param_5);
// <LegoRR.exe @0046f640>
void __cdecl Weapon_LiveObject_FUN_0046f640(LiveObject* liveObj, real32 param_2, sint32 param_3);
// <LegoRR.exe @0046f670>
void __cdecl Weapon_Struct2B0_FUN_0046f670(Struct_2b0* param_1);
// <LegoRR.exe @0046f810>
void __cdecl Weapon_Struct2B0_Update_Table_FUN_0046f810(real32 elapsedGame);
// <LegoRR.exe @0046f8d0>
bool32 __cdecl Weapon_LiveObject_Callback_FUN_0046f8d0(LiveObject* liveObj, real32* lpElapsed);
// <LegoRR.exe @0046fa30>
void __cdecl Weapon_LiveObject_FUN_0046fa30(LiveObject* liveObj, sint32** param_2, Vector3F* param_3, sint32* param_4, sint32 param_5);
// <LegoRR.exe @0046fbe0>
void __cdecl Weapon_Struct2B0_FUN_0046fbe0(Struct_2b0* param_1, real32 elapsed);
// <LegoRR.exe @0046fdb0>
bool32 __cdecl Weapon_Struct2B0_FUN_0046fdb0(LiveObject* liveObj, Vector3F* param_2, Vector3F* param_3, uint32 weaponType, uint32 param_5);
// <LegoRR.exe @0046ff30>
bool32 __cdecl Weapon_UpdateRoutingUnk_FUN_0046ff30(undefined4 param_1, Vector3F* param_2, Vector3F* param_3, sint32 param_4, WeaponKnownType knownWeapon);
// <LegoRR.exe @004701b0>
void __cdecl Weapon_GetObjectTypeIndex_ByKnownWeaponType(WeaponKnownType knownWeapon, ObjectType* out_objType, sint32* out_objIndex);
// <LegoRR.exe @00470230>
sint32 __cdecl Weapon_Struct2B0_Table_FUN_00504bc0(void);
// <LegoRR.exe @00470250>
sint32 __cdecl Weapon_ItemStruct34_GetTableCount(void);
// <LegoRR.exe @00470270>
LiveObject* __cdecl Weapon_DoLaserUnk_FUN_00470270(Vector3F* sndPosition, Vector3F* param_2, LiveObject* in_liveObj, real32 param_4, real32 param_5, sint32 weaponType, real32 param_7);
// <LegoRR.exe @00470520>
bool32 __cdecl LiveObject_Collision_FUN_00470520(LiveObject* liveObj, Point2F* param_2, Point2F* param_3, bool32 param_4);
// <LegoRR.exe @00470570>
bool32 __cdecl LiveObject_CollisionBox_FUN_00470570(LiveObject* liveObj, Point2F* param_2, Point2F* param_3, Point2F* optout_point, bool32 param_5);
// <LegoRR.exe @00470800>
bool32 __cdecl LiveObject_CollisionRadius_FUN_00470800(LiveObject* liveObj, Point2F* param_2, Point2F* param_3, bool32 param_4);
// <LegoRR.exe @004708f0>
bool32 __cdecl LiveObject_TestCollision_FUN_004708f0(LiveObject* liveObj, Point2F* param_2, Point2F* param_3);
// <LegoRR.exe @00470950>
void __cdecl Weapon_ItemStruct34_FUN_00470950(Container* resData, Vector3F* vector1, Vector3F* vector2);
// <LegoRR.exe @00470a20>
void __cdecl Struct34_FUN_00470a20(Mesh* param_1, real32 scalar, Vector3F* vector1, Vector3F* vector2, real32 param_5, real32 param_6, real32 param_7, real32 param_8);
// <LegoRR.exe @00471580>
void* __cdecl LiveObject_GetBuildingVehicleFields_138_a0(LiveObject* liveObj);
// <LegoRR.exe @004715b0>
float10 __cdecl LiveObject_PtrGetter_FUN_004715b0(LiveObject* liveObj, sint32 param_2);
// <LegoRR.exe @004715d0>
void __cdecl LiveObject_PtrSetter_FUN_004715d0(LiveObject* liveObj, undefined4 param_2, sint32 param_3);
// <LegoRR.exe @004715f0>
bool32 __cdecl MathUnk_CheckVectorsZScalar_InRange(Vector3F* vectorPos, Vector3F* vectorScaled, real32 minZ, real32 maxZ, real32 scalar);
// <LegoRR.exe @00471630>
bool32 __cdecl LiveObject_Callback_FUN_00471630(LiveObject* liveObj, SearchData18_2* search);
// <LegoRR.exe @004718f0>
void __cdecl FUN_004718f0(SearchData18_2* search);
// <LegoRR.exe @00471b20>
bool32 __cdecl Game_DoCallbacksSearch_FUN_00471b20(Vector3F* vecCector, Vector3F* vecDistance, LiveObject** out_liveObj, real32* ref_float_4, undefined4 param_5);
// <LegoRR.exe @00471b90>
bool32 __cdecl LiveObject_DoCallbacksSearch_FUN_00471b90(LiveObject* liveObj1, LiveObject* liveObj2);
// <LegoRR.exe @00471c20>
bool32 __cdecl LiveObject_SeeThroughWalls_FUN_00471c20(LiveObject* liveObj, LiveObject* liveObj2);
// <LegoRR.exe @00471ce0>
undefined4 __cdecl UnkStruct_Getter_FUN_00471ce0(sint32 param_1, sint32 param_2, sint32 param_3);
// <LegoRR.exe @00471d00>
undefined4 __cdecl UnkStruct_Getter_FUN_00471d00(sint32 param_1, sint32 param_2);
// <LegoRR.exe @00471d10>
undefined4 __cdecl UnkStruct_Getter_FUN_00471d10(sint32 param_1, sint32 param_2);
// <LegoRR.exe @00471d20>
void __cdecl UnkStruct_FUN_00471d20(sint32 param_1, undefined4* param_2, real32 param_3, sint32 param_4, sint32 param_5);
// <LegoRR.exe @00471f30>
void __cdecl UnkStructC_GetTable44_Vector_FUN_00471f30(sint32 param_1, Vector3F* out_vector44, sint32 index);
// <LegoRR.exe @00471f60>
bool32 __cdecl LiveObject_GetCollCenterPosition(LiveObject* liveObj, Vector3F* out_vector);
// <LegoRR.exe @00471fa0>
bool32 __cdecl LiveObject_UnkTracker_FUN_00471fa0(LiveObject* liveObj);
// <LegoRR.exe @00471fe0>
bool32 __cdecl LiveObject_FUN_00471fe0(LiveObject* in_liveObj, real32 param_2, real32 param_3);
// <LegoRR.exe @004721c0>
bool32 __cdecl LiveObject_FUN_004721c0(LiveObject* liveObj, real32 param_2, sint32 param_3);
// <LegoRR.exe @00472280>
bool32 __cdecl LiveObject_FUN_00472280(LiveObject* liveObj, real32 param_2);
// <LegoRR.exe @00472320>
bool32 __cdecl LiveObject_SetField_3c4(LiveObject* liveObj, sint32 field3c4);
// <LegoRR.exe @00472340>
bool32 __cdecl LiveObject_FUN_00472340(LiveObject* liveObj, undefined4* param_2);
// <LegoRR.exe @004723f0>
bool32 __cdecl LiveObject_FUN_004723f0(LiveObject* liveObj, undefined4* param_2);
// <LegoRR.exe @004724a0>
bool __thiscall G98CMovie__InitSample(G98CMovie* this, IAMMultiMediaStream* lpAMMMStream);
// <LegoRR.exe @00472570>
bool __thiscall G98CMovie__OpenAMStream(G98CMovie* this, char* fName, IAMMultiMediaStream** lplpAMMMStream, IDirectDraw2* ddraw2);
// <LegoRR.exe @00472650>
G98CMovie* __thiscall G98CMovie___ctor(G98CMovie* this, char* fName, IDirectDrawSurface3* bSurf3, IDirectDraw2* ddraw2);
// <LegoRR.exe @004726f0>
void __thiscall G98CMovie___dtor(G98CMovie* this);
// <LegoRR.exe @00472760>
bool __thiscall G98CMovie__Update(G98CMovie* this, real32 speed, RECT* destRect);
// <LegoRR.exe @004727f0>
sint64 __thiscall G98CMovie__GetDuration(G98CMovie* this);
// <LegoRR.exe @00472820>
Movie_t* __cdecl Movie_Load(char* fName);
// <LegoRR.exe @00472930>
void __cdecl Movie_GetSize(Movie_t* mov, uint32* out_width, uint32* out_height);
// <LegoRR.exe @00472980>
sint64 __cdecl Movie_GetDuration(Movie_t* mov);
// <LegoRR.exe @00472990>
bool32 __cdecl Movie_Update(Movie_t* mov, real32 speed, RECT* destRect);
// <LegoRR.exe @004729b0>
void __cdecl Movie_Free(Movie_t* mov);
// <LegoRR.exe @004729d0>
Container* __cdecl Container_Initialise(char* gameName);
// <LegoRR.exe @00472ac0>
void __cdecl Container_Shutdown(void);
// <LegoRR.exe @00472b80>
void __cdecl Container_SetSharedTextureDirectory(char* path);
// <LegoRR.exe @00472ba0>
void __cdecl Container_EnableSoundTriggers(bool32 on);
// <LegoRR.exe @00472bc0>
void __cdecl Container_SetTriggerFrameCallback(ContainerTriggerFrameCallback callback, void* data);
// <LegoRR.exe @00472be0>
void __cdecl Container_SetSoundTriggerCallback(ContainerSoundTriggerCallback callback, void* data);
// <LegoRR.exe @00472c00>
Container* __cdecl GetRoot(void);
// <LegoRR.exe @00472c10>
Container* __cdecl Container_Create(Container* opt_parent);
// <LegoRR.exe @00472d00>
void __cdecl Container_Remove(Container* cont);
// <LegoRR.exe @00472d10>
void __cdecl Container_Remove2(Container* in_cont, bool32 kill);
// <LegoRR.exe @00472f90>
Container* __cdecl Container_Load(Container* parent, char* filename, char* typestr, bool32 looping);
// <LegoRR.exe @00473600>
bool32 __cdecl Container_IsCurrentActivity(Container* cont, char* actname);
// <LegoRR.exe @00473630>
bool32 __cdecl Container_SetActivity(Container* cont, char* actname);
// <LegoRR.exe @00473720>
bool32 __cdecl Container_Light_SetSpotPenumbra(Container* spotlight, real32 angle);
// <LegoRR.exe @00473740>
bool32 __cdecl Container_Light_SetSpotUmbra(Container* spotlight, real32 angle);
// <LegoRR.exe @00473760>
bool32 __cdecl Container_Light_SetSpotRange(Container* spotlight, real32 dist);
// <LegoRR.exe @00473780>
void __cdecl Container_Light_SetEnableContainer(Container* light, Container* enable);
// <LegoRR.exe @004737b0>
Container* __cdecl Container_MakeLight(Container* parent, D3DRMLightType type, real32 r, real32 g, real32 b);
// <LegoRR.exe @00473820>
Container* __cdecl Container_MakeMesh2(Container* parent, Container_MeshType type);
// <LegoRR.exe @00473940>
IDirect3DRMFrame3* __cdecl Container_GetMasterFrame(Container* cont);
// <LegoRR.exe @00473950>
Container* __cdecl Container_Clone(Container* orig);
// <LegoRR.exe @00473de0>
void __cdecl Container_Hide2(Container* cont, bool32 hide);
// <LegoRR.exe @00473e00>
void __cdecl Container_Hide(Container* cont, bool32 hide);
// <LegoRR.exe @00473e60>
bool32 __cdecl Container_IsHidden(Container* cont);
// <LegoRR.exe @00473e80>
Container* __cdecl Container_SearchTree(Container* root, char* name, Container_SearchMode mode, uint32* ref_count);
// <LegoRR.exe @00473f20>
char* __cdecl Container_FormatPartName(Container* cont, char* partname, sint32* opt_instance);
// <LegoRR.exe @00474060>
void __cdecl Container_SetUserData(Container* cont, void* data);
// <LegoRR.exe @00474070>
void* __cdecl Container_GetUserData(Container* cont);
// <LegoRR.exe @00474080>
void __cdecl Container_EnableFog(bool32 on);
// <LegoRR.exe @004740d0>
void __cdecl Container_SetFogColour(real32 r, real32 g, real32 b);
// <LegoRR.exe @00474130>
void __cdecl Container_SetFogMode(D3DRMSceneFogMethod mode);
// <LegoRR.exe @00474160>
void __cdecl Container_SetFogParams(real32 start, real32 end, real32 density);
// <LegoRR.exe @00474180>
void __cdecl Container_SetPerspectiveCorrection(Container* cont, bool32 on);
// <LegoRR.exe @00474230>
bool32 __cdecl Container_SetPerspectiveCorrectionCallback(IDirect3DRMFrame3* frame, bool32* lpArg_on);
// <LegoRR.exe @00474310>
IDirectDrawSurface4* __cdecl Container_LoadTextureSurface(char* fname, bool32 managed, uint32* out_width, uint32* out_height, bool32* out_trans);
// <LegoRR.exe @004746d0>
bool32 __cdecl Container_GetDecalColour(char* fname, uint32* out_colour);
// <LegoRR.exe @004747b0>
Container_Texture* __cdecl Container_LoadTexture2(char* fname, bool32 immediate, uint32* out_width, uint32* out_height);
// <LegoRR.exe @004749d0>
void __cdecl Container_FreeTexture(Container_Texture* text);
// <LegoRR.exe @00474a20>
void __cdecl Container_Mesh_Swap(Container* target, Container* origin, bool32 restore);
// <LegoRR.exe @00474bb0>
uint32 __cdecl Container_Mesh_AddGroup(Container* cont, uint32 vertexCount, uint32 faceCount, uint32 vPerFace, uint32* faceData);
// <LegoRR.exe @00474ce0>
uint32 __cdecl Container_Mesh_GetGroupCount(Container* cont);
// <LegoRR.exe @00474d20>
void __cdecl Container_Mesh_SetQuality(Container* cont, D3DRMGroupIndex groupID, GraphicsQuality quality);
// <LegoRR.exe @00474da0>
bool32 __cdecl Container_Mesh_IsGroupHidden(Container* cont, D3DRMGroupIndex group);
// <LegoRR.exe @00474df0>
void __cdecl Container_Mesh_HideGroup(Container* cont, D3DRMGroupIndex group, bool32 hide);
// <LegoRR.exe @00474ec0>
bool32 __cdecl Container_Mesh_HandleSeperateMeshGroups(IDirect3DRMMesh** ref_mesh, D3DRMGroupIndex* ref_groupID);
// <LegoRR.exe @00474f00>
bool32 __cdecl Container_Mesh_GetGroup(Container* cont, D3DRMGroupIndex groupID, uint32* out_vertexCount, uint32* out_faceCount, uint32* out_vPerFace, uint32* out_faceDataSize, uint32* out_faceData);
// <LegoRR.exe @00474f80>
uint32 __cdecl Container_Mesh_GetVertices(Container* cont, D3DRMGroupIndex groupID, uint32 index, uint32 count, Vertex3F* out_retArray);
// <LegoRR.exe @00474ff0>
uint32 __cdecl Container_Mesh_SetVertices(Container* cont, D3DRMGroupIndex groupID, uint32 index, uint32 count, Vertex3F* values);
// <LegoRR.exe @00475060>
void __cdecl Container_Mesh_SetTexture(Container* cont, D3DRMGroupIndex groupID, Container_Texture* ref_itext);
// <LegoRR.exe @004750f0>
void __cdecl Container_Mesh_SetPerspectiveCorrection(Container* cont, D3DRMGroupIndex groupID, bool32 on);
// <LegoRR.exe @00475150>
bool32 __cdecl Container_Mesh_Scale(Container* cont, real32 x, real32 y, real32 z);
// <LegoRR.exe @004751d0>
bool32 __cdecl Container_Mesh_GetBox(Container* cont, D3DRMBox* out_box);
// <LegoRR.exe @004752b0>
void __cdecl Container_Mesh_SetEmissive(Container* cont, D3DRMGroupIndex groupID, real32 r, real32 g, real32 b);
// <LegoRR.exe @004752e0>
void __cdecl Container_Mesh_SetColourAlpha(Container* cont, D3DRMGroupIndex groupID, real32 r, real32 g, real32 b, real32 a);
// <LegoRR.exe @00475330>
void __cdecl Container_Transform(Container* cont, Vector3F* out_vector, Vector3F* in_vector);
// <LegoRR.exe @00475350>
void __cdecl Container_InverseTransform(Container* cont, Vector3F* out_vector, Vector3F* in_vector);
// <LegoRR.exe @00475370>
void __cdecl Container_SetColourAlpha(Container* cont, real32 r, real32 g, real32 b, real32 a);
// <LegoRR.exe @004753e0>
float10 __cdecl Container_MoveAnimation(Container* cont, real32 delta);
// <LegoRR.exe @00475400>
float10 __cdecl Container_SetAnimationTime(Container* cont, real32 time);
// <LegoRR.exe @004755c0>
void __cdecl Container_ForceAnimationUpdate(Container* cont);
// <LegoRR.exe @00475650>
float10 __cdecl Container_GetAnimationTime(Container* cont);
// <LegoRR.exe @004756b0>
uint32 __cdecl Container_GetAnimationFrames(Container* cont);
// <LegoRR.exe @004756f0>
void __cdecl Container_SetPosition(Container* cont, Container* opt_ref, real32 x, real32 y, real32 z);
// <LegoRR.exe @00475730>
void __cdecl Container_SetOrientation(Container* cont, Container* opt_ref, real32 dirx, real32 diry, real32 dirz, real32 upx, real32 upy, real32 upz);
// <LegoRR.exe @00475780>
void __cdecl Container_GetPosition(Container* cont, Container* opt_ref, Vector3F* out_pos);
// <LegoRR.exe @004757c0>
void __cdecl Container_GetOrientation(Container* cont, Container* opt_ref, Vector3F* out_dir, Vector3F* out_up);
// <LegoRR.exe @00475840>
void __cdecl Container_AddRotation(Container* cont, D3DRMCombineType combine, real32 x, real32 y, real32 z, real32 angle);
// <LegoRR.exe @00475870>
void __cdecl Container_AddScale(Container* cont, D3DRMCombineType combine, real32 x, real32 y, real32 z);
// <LegoRR.exe @004758a0>
void __cdecl Container_AddTranslation(Container* cont, D3DRMCombineType combine, real32 x, real32 y, real32 z);
// <LegoRR.exe @004758d0>
void __cdecl Container_ClearTransform(Container* cont);
// <LegoRR.exe @00475970>
void __cdecl Container_AddTransform(Container* cont, D3DRMCombineType combine, Matrix4F* mat);
// <LegoRR.exe @00475990>
float10 __cdecl Container_GetZXRatio(Container* cont);
// <LegoRR.exe @004759d0>
void __cdecl Container_SetParent(Container* child, Container* parent);
// <LegoRR.exe @00475a60>
Container* __cdecl Container_GetParent(Container* cont);
// <LegoRR.exe @00475ab0>
float10 __cdecl Container_GetTransCoef(Container* cont);
// <LegoRR.exe @00475af0>
Container* __cdecl Container_SearchOwner(IDirect3DRMFrame3* in_frame);
// <LegoRR.exe @00475b40>
Container* __cdecl Container_Frame_GetContainer(IDirect3DRMFrame3* frame);
// <LegoRR.exe @00475bc0>
void __cdecl Container_GetFrames(Container* cont, Container* opt_ref, IDirect3DRMFrame3** out_contFrame, IDirect3DRMFrame3** out_refFrame);
// <LegoRR.exe @00475bf0>
Container_Type __cdecl Container_ParseTypeString(char* str, bool32* out_noTexture);
// <LegoRR.exe @00475cb0>
void __cdecl Container_AddList(void);
// <LegoRR.exe @00475d30>
uint32 __cdecl Container_GetActivities(Container* cont, IDirect3DRMFrame3** out_frameList, AnimClone** out_acList, char** out_nameList);
// <LegoRR.exe @00475ec0>
void __cdecl Container_SetTypeData(Container* cont, char* name, IDirect3DRMLight* light, IDirect3DRMMesh* mesh, Mesh* transMesh);
// <LegoRR.exe @00475f40>
void __cdecl Container_FreeTypeData(Container* cont);
// <LegoRR.exe @00475fd0>
bool32 __cdecl Container_AddActivity2(Container* cont, char* filename, char* actname, real32 transCo, uint32 trigger, char* sample, AnimClone* origClone, bool32 lws, bool32 looping);
// <LegoRR.exe @004760d0>
void __cdecl Container_Frame_ReferenceDestroyCallback(IDirect3DRMFrame3* lpD3DRMobj, void* lpArg);
// <LegoRR.exe @00476100>
IDirect3DRMFrame3* __cdecl Container_Frame_Find(Container* cont, char* findName, bool32 hidden);
// <LegoRR.exe @00476230>
void __cdecl Container_Frame_SetAppData(IDirect3DRMFrame3* frame, Container* owner, AnimClone* animClone, char* asfname, uint32* frameCount, char* frameName, real32* currTime, real32* transCo, char* actSample, Sound3D_SoundFrameRecord* soundRecord, uint32* trigger);
// <LegoRR.exe @004763a0>
void __cdecl Container_Frame_RemoveAppData(IDirect3DRMFrame3* frame);
// <LegoRR.exe @004763e0>
Container* __cdecl Container_Frame_GetOwner(IDirect3DRMFrame3* frame);
// <LegoRR.exe @00476400>
char* __cdecl Container_Frame_GetAnimSetFileName(IDirect3DRMFrame3* frame);
// <LegoRR.exe @00476420>
AnimClone* __cdecl Container_Frame_GetAnimClone(IDirect3DRMFrame3* frame);
// <LegoRR.exe @00476440>
uint32 __cdecl Container_Frame_GetFrameCount(IDirect3DRMFrame3* frame);
// <LegoRR.exe @00476460>
float10 __cdecl Container_Frame_GetCurrTime(IDirect3DRMFrame3* frame);
// <LegoRR.exe @00476480>
float10 __cdecl Container_Frame_GetTransCo(IDirect3DRMFrame3* frame);
// <LegoRR.exe @004764a0>
char* __cdecl Container_Frame_GetSample(IDirect3DRMFrame3* frame);
// <LegoRR.exe @004764c0>
uint32 __cdecl Container_Frame_GetTrigger(IDirect3DRMFrame3* frame);
// <LegoRR.exe @004764e0>
void __cdecl Container_Frame_SafeAddChild(IDirect3DRMFrame3* parent, IDirect3DRMFrame3* child);
// <LegoRR.exe @00476530>
void __cdecl Container_Frame_FormatName(IDirect3DRMFrame3* frame, char* msg, ...);
// <LegoRR.exe @004765b0>
void __cdecl Container_Frame_FreeName(IDirect3DRMFrame3* frame);
// <LegoRR.exe @004765d0>
char* __cdecl Container_Frame_GetName(IDirect3DRMFrame3* frame);
// <LegoRR.exe @004765f0>
bool32 __cdecl Container_Frame_WalkTree(IDirect3DRMFrame3* frame, uint32 level, ContainerWalkTreeCallback Callback, void* data);
// <LegoRR.exe @004766d0>
bool32 __cdecl Container_Frame_SearchCallback(IDirect3DRMFrame3* frame, Container_SearchData* search);
// <LegoRR.exe @00476880>
AnimClone* __cdecl Container_LoadAnimSet(char* fname, IDirect3DRMFrame3* frame, uint32* out_frameCount, bool32 lws, bool32 looping);
// <LegoRR.exe @00476a30>
uint32 __cdecl Container_GetAnimFileFrameCount(char* fileData);
// <LegoRR.exe @00476aa0>
bool32 __cdecl Container_FrameLoad(char* fname, IDirect3DRMFrame3* frame);
// <LegoRR.exe @00476b10>
IDirect3DRMMesh* __cdecl Container_MeshLoad(void* file_data, uint32 file_size, char* file_name, IDirect3DRMFrame3* frame, bool32 noTexture);
// <LegoRR.exe @00476bc0>
HRESULT __cdecl Container_TextureLoadCallback(char* name, Container_TextureData* textureData, IDirect3DRMTexture3** texture);
// <LegoRR.exe @00476eb0>
void __cdecl Container_YFlipTexture(IDirect3DRMTexture3* texture);
// <LegoRR.exe @00476fa0>
sint32 __cdecl Container_TextureSetSort(Container_TextureRef* a, Container_TextureRef* b);
// <LegoRR.exe @00476fd0>
void __cdecl Container_TextureDestroyCallback(IDirect3DRMTexture3* lpD3DRMobj, Container_TextureRef* textRef);
// <LegoRR.exe @00477010>
void __cdecl Viewport_Initialise(void);
// <LegoRR.exe @00477040>
void __cdecl Viewport_Shutdown(void);
// <LegoRR.exe @00477080>
Viewport* __cdecl Viewport_Create(real32 xposf, real32 yposf, real32 widthf, real32 heightf, Container* resData);
// <LegoRR.exe @00477110>
Viewport* __cdecl Viewport_CreatePixel(sint32 xPos, sint32 yPos, uint32 width, uint32 height, Container* resCamera);
// <LegoRR.exe @004771d0>
void __cdecl Viewport_GetSize(Viewport* view, uint32* out_width, uint32* out_height);
// <LegoRR.exe @00477210>
void __cdecl Viewport_SetCamera(Viewport* view, Container* resCamera);
// <LegoRR.exe @00477230>
Container* __cdecl Viewport_GetCamera(Viewport* view);
// <LegoRR.exe @00477270>
void __cdecl Viewport_SetBackClip(Viewport* view, real32 dist);
// <LegoRR.exe @00477290>
float10 __cdecl Viewport_GetBackClip(Viewport* view);
// <LegoRR.exe @004772b0>
float10 __cdecl Viewport_GetFrontClip(Viewport* view);
// <LegoRR.exe @004772d0>
void __cdecl Viewport_Clear(Viewport* view, bool32 full);
// <LegoRR.exe @00477410>
void __cdecl Viewport_Render(Viewport* view, Container* resRoot, real32 delta);
// <LegoRR.exe @004774e0>
void __cdecl Viewport_Remove(Viewport* view);
// <LegoRR.exe @00477500>
void __cdecl Viewport_SmoothSetField(Viewport* view, real32 fov);
// <LegoRR.exe @00477510>
void __cdecl Viewport_SetField(Viewport* view, real32 fov);
// <LegoRR.exe @00477530>
float10 __cdecl Viewport_GetField(Viewport* view);
// <LegoRR.exe @00477550>
void __cdecl Viewport_InverseTransform(Viewport* view, Vector3F* out_vector, Vector4F* transform4d);
// <LegoRR.exe @00477570>
void __cdecl Viewport_Transform(Viewport* view, Vector4F* out_transform4d, Vector3F* vector);
// <LegoRR.exe @00477590>
Point2F* __cdecl Viewport_WorldToScreen(Viewport* view, Point2F* out_screenPt, Vector3F* in_worldVec);
// <LegoRR.exe @004775d0>
IDirect3DRMFrame3* __cdecl Viewport_GetScene(Viewport* view);
// <LegoRR.exe @00477630>
void __cdecl Viewport_AddList(void);
// <LegoRR.exe @004776a0>
void __cdecl Viewport_RemoveAll(void);
// <LegoRR.exe @00477700>
sint32 __cdecl Util_Tokenise(char* input, char** out_parts, char* delimiter);
// <LegoRR.exe @00477770>
sint32 __cdecl Util_WSTokenise(char* input, char** out_parts);
// <LegoRR.exe @00477810>
char* __cdecl _strdup(char* strSource);
// <LegoRR.exe @00477850>
char* __cdecl Util_RemoveUnderscores(char* text, ...);
// <LegoRR.exe @004778d0>
char* __cdecl Util_StrIStr(char* str, char* strSearch);
// <LegoRR.exe @00477930>
uint32 __cdecl Util_HashString(char* str, bool32 bIgnoreBlanks, bool32 upperCase);
// <LegoRR.exe @004779d0>
BoolTri __cdecl Util_GetBoolFromString(char* str);
// <LegoRR.exe @00477a60>
sint32 __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, sint32 nShowCmd);
// <LegoRR.exe @00477e90>
void __cdecl Main_DisableTextureManagement(void);
// <LegoRR.exe @00477eb0>
void __cdecl Main_ParseCommandLine(char* lpszCmdLine, bool32* out_nosound, bool32* out_insistOnCD);
// <LegoRR.exe @004781f0>
void __cdecl Main_LoopUpdate(bool32 clear);
// <LegoRR.exe @00478230>
FeatureFlags __cdecl Main_GetCLFlags(void);
// <LegoRR.exe @00478240>
sint32 __cdecl Main_GetWindowsBitDepth(void);
// <LegoRR.exe @00478260>
void __cdecl Main_Finalise3D(void);
// <LegoRR.exe @00478290>
bool32 __cdecl Main_SetState(Main_State* state);
// <LegoRR.exe @004782c0>
uint32 __cdecl Main_GetTime(void);
// <LegoRR.exe @004782d0>
bool32 __cdecl Main_DispatchMessage(MSG* msg);
// <LegoRR.exe @00478300>
void __cdecl Main_HandleIO(void);
// <LegoRR.exe @00478370>
void __cdecl Main_SetupDisplay(bool32 fullScreen, uint32 xPos, uint32 yPos, uint32 width, uint32 height);
// <LegoRR.exe @00478490>
bool32 __cdecl Main_SetupDirect3D(DirectDraw_Device* dev, IDirectDraw* ddraw1, IDirectDrawSurface4* backSurf, bool32 doubleBuffered);
// <LegoRR.exe @004785d0>
void __cdecl Main_AdjustWindowRect(LPRECT lpRect);
// <LegoRR.exe @004785f0>
void __cdecl Main_Setup3D(GraphicsQuality renderQuality, bool32 dither, bool32 linearFilter, bool32 mipMap, bool32 mipMapLinear, bool32 blendTransparency, bool32 sortTransparency);
// <LegoRR.exe @00478690>
void __cdecl Main_SetTitle(char* title);
// <LegoRR.exe @004786b0>
bool32 __cdecl Main_InitApp(HINSTANCE hInstance);
// <LegoRR.exe @00478780>
LRESULT __cdecl Main_WndProc_Fullscreen(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
// <LegoRR.exe @00478980>
LRESULT __cdecl Main_WndProc_Windowed(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
// <LegoRR.exe @00478b40>
LRESULT __stdcall Main_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
// <LegoRR.exe @00478b90>
void __cdecl Main_ChangeRenderState(D3DRenderStateType dwRenderStateType, D3DRenderStateType dwRenderState);
// <LegoRR.exe @00478c00>
void __cdecl Main_RestoreStates(void);
// <LegoRR.exe @00478c40>
bool32 __cdecl Main_SetCDVolume(real32 leftVolume, real32 rightVolume);
// <LegoRR.exe @00478c60>
bool32 __cdecl Main_GetCDVolume(real32* out_leftVolume, real32* out_rightVolume);
// <LegoRR.exe @00478c80>
bool32 __cdecl Main_CDVolume(real32* ref_leftVolume, real32* ref_rightVolume, bool32 set);
// <LegoRR.exe @004790b0>
void __cdecl Config_Initialise(void);
// <LegoRR.exe @004790e0>
void __cdecl Config_Shutdown(void);
// <LegoRR.exe @00479120>
CFGProperty* __cdecl CFG_Open(char* filename);
// <LegoRR.exe @00479210>
char* __cdecl CFG_JoinPath(char* keyPath1, ...);
// <LegoRR.exe @004792b0>
CFGProperty* __cdecl CFG_GetChildren(CFGProperty* prop, char* keyPath);
// <LegoRR.exe @004792e0>
CFGProperty* __cdecl CFG_NextFlat(CFGProperty* prop);
// <LegoRR.exe @00479310>
char* __cdecl CFG_CopyString(CFGProperty* prop, char* keyPath);
// <LegoRR.exe @00479370>
char* __cdecl CFG_ReadString(CFGProperty* prop, char* keyPath);
// <LegoRR.exe @00479390>
BoolTri __cdecl CFG_ReadBool(CFGProperty* prop, char* keyPath);
// <LegoRR.exe @004793d0>
float10 __cdecl CFG_ReadRadians(CFGProperty* prop, char* keyPath);
// <LegoRR.exe @00479430>
bool32 __cdecl CFG_ReadRGBF(CFGProperty* prop, char* keyPath, real32* out_r, real32* out_g, real32* out_b);
// <LegoRR.exe @00479500>
void __cdecl CFG_Close(CFGProperty* root);
// <LegoRR.exe @00479530>
CFGProperty* __cdecl Config_Create(CFGProperty* prev);
// <LegoRR.exe @00479580>
void __cdecl Config_Remove(CFGProperty* prop);
// <LegoRR.exe @004795a0>
CFGProperty* __cdecl CFG_GetProperty(CFGProperty* prop, char* keyPath);
// <LegoRR.exe @00479750>
void __cdecl Config_AddList(void);
// <LegoRR.exe @004797c0>
Vector3F* __cdecl Maths_Vector3DRandom(Vector3F* out_vector);
// <LegoRR.exe @004797d0>
Vector3F* __cdecl Maths_Vector3DRotate(Vector3F* out_vector, Vector3F* v, Vector3F* axis, real32 theta);
// <LegoRR.exe @004797f0>
Vector3F* __cdecl Maths_PlaneNormal(Vector3F* out_vector, Vector3F* p1, Vector3F* p2, Vector3F* p3);
// <LegoRR.exe @004798f0>
float10 __cdecl Maths_TriangleAreaZ(Vector3F* p1, Vector3F* p2, Vector3F* p3, bool32 bfc);
// <LegoRR.exe @00479b60>
sint16 __cdecl Maths_Rand(void);
// <LegoRR.exe @00479b70>
float10 __cdecl Maths_RandRange(real32 low, real32 high);
// <LegoRR.exe @00479ba0>
bool32 __cdecl Maths_RayPlaneIntersection(Vector3F* out_endPoint, Vector3F* rayOrigin, Vector3F* ray, Vector3F* planePoint, Vector3F* planeNormal);
// <LegoRR.exe @00479cf0>
bool32 __cdecl Maths_RayPlaneDistance(real32* out_dist, Vector3F* rayOrigin, Vector3F* ray, Vector3F* planePoint, Vector3F* planeNormal);
// <LegoRR.exe @00479d70>
Vector3F* __cdecl Maths_RayEndPoint(Vector3F* out_endPoint, Vector3F* rayOrigin, Vector3F* ray, real32 dist);
// <LegoRR.exe @00479db0>
Point2F* __cdecl Maths_Vector2DIntersection(Point2F* out_intersection, Point2F* start1, Point2F* vector1, Point2F* start2, Point2F* vector2);
// <LegoRR.exe @00479e40>
bool32 __cdecl Maths_PointInsidePoly(Point2F* point, Point2F* fromList, Point2F* toList, uint32 count);
// <LegoRR.exe @00479ed0>
bool32 __cdecl Maths_RaySphereIntersection(Vector3F* center, real32 radius, Vector3F* camera, Vector3F* line);
// <LegoRR.exe @00479fa0>
void __cdecl Matrix_Mult(Matrix4F* out_matrix, Matrix4F* right, Matrix4F* left);
// <LegoRR.exe @0047a010>
void __cdecl Matrix_RotX(Matrix4F* out_matrix, real32 rot);
// <LegoRR.exe @0047a060>
void __cdecl Matrix_RotY(Matrix4F* out_matrix, real32 rot);
// <LegoRR.exe @0047a0b0>
void __cdecl Matrix_RotZ(Matrix4F* out_matrix, real32 rot);
// <LegoRR.exe @0047a100>
void __cdecl Matrix_Translate(Matrix4F* out_matrix, Vector3F* trans);
// <LegoRR.exe @0047a130>
void __cdecl Matrix_Identity(Matrix4F* out_matrix);
// <LegoRR.exe @0047a160>
void __cdecl Matrix_Zero(Matrix4F* out_matrix);
// <LegoRR.exe @0047a170>
void __cdecl Matrix_Copy(Matrix4F* out_matrix, Matrix4F* src);
// <LegoRR.exe @0047a1a0>
Font* __cdecl Font_Load(char* fname);
// <LegoRR.exe @0047a410>
void __cdecl Font_VGetStringInfo(Font* font, uint32* out_width, uint32* out_lineCount, char* msg, va_list argptr);
// <LegoRR.exe @0047a440>
uint32 __cdecl Font_PrintF(Font* font, sint32 x, sint32 y, char* msg, ...);
// <LegoRR.exe @0047a470>
uint32 __cdecl Font_VPrintF(Font* font, sint32 x, sint32 y, char* msg, va_list argptr);
// <LegoRR.exe @0047a4a0>
uint32 __cdecl Font_VPrintF2(Font* font, sint32 x, sint32 y, bool32 render, uint32* out_lineCount, char* msg, va_list argptr);
// <LegoRR.exe @0047a730>
uint32 __cdecl Font_OutputChar(Font* font, sint32 x, sint32 y, char c, bool32 render);
// <LegoRR.exe @0047a7e0>
uint32 __cdecl Font_GetCharWidth(Font* font, char c);
// <LegoRR.exe @0047a800>
uint32 __cdecl Font_GetHeight(Font* font);
// <LegoRR.exe @0047a810>
void __cdecl Font_Remove(Font* font);
// <LegoRR.exe @0047a840>
Font* __cdecl Font_Create(Image* image);
// <LegoRR.exe @0047a880>
void __cdecl Font_AddList(void);
// <LegoRR.exe @0047a900>
bool32 __cdecl Sound3D_Initialise(HWND hWnd);
// <LegoRR.exe @0047aac0>
void __cdecl Sound3D_ShutDown(void);
// <LegoRR.exe @0047ab10>
bool32 __cdecl Sound3D_CheckVolumeLimits(sint32 vol);
// <LegoRR.exe @0047ab30>
sint32 __cdecl Sound3D_Load(char* fName, bool32 stream, bool32 simultaneous, sint32 volume);
// <LegoRR.exe @0047ad90>
bool32 __cdecl Sound3D_GetFreeSoundIndex(uint32* out_soundTableIndex);
// <LegoRR.exe @0047adc0>
bool32 __cdecl Sound3D_Remove(sint32 soundTableIndex);
// <LegoRR.exe @0047ae40>
void __cdecl Sound3D_MakeListener(IDirect3DRMFrame3* frame);
// <LegoRR.exe @0047ae60>
void __cdecl Sound3D_UpdateListener(void);
// <LegoRR.exe @0047ae80>
void __cdecl Sound3D_ListenerCallback(IDirect3DRMFrame3* obj, void* arg, real32 delta);
// <LegoRR.exe @0047afd0>
void __cdecl Sound3D_SetWorldPos(IDirectSound3DBuffer* sound3DBuff, Vector3F* wPos, Vector3F* vel);
// <LegoRR.exe @0047aff0>
bool32 __cdecl Sound3D_CheckAlreadyExists(IDirect3DRMFrame3* frame, IDirectSound3DBuffer* sound3DBuff);
// <LegoRR.exe @0047b030>
sint32 __cdecl Sound3D_Play2(Sound3DPlayMode mode, IDirect3DRMFrame3* frame, sint32 soundTableIndex, bool32 loop, Vector3F* opt_wPos);
// <LegoRR.exe @0047b2e0>
void __cdecl Sound3D_AddSoundRecord(IDirect3DRMFrame3* frame, IDirectSoundBuffer* soundBuff, IDirectSound3DBuffer* sound3DBuff);
// <LegoRR.exe @0047b310>
void __cdecl Sound3D_SetBufferVolume(sint32 handle, sint32 newvolume);
// <LegoRR.exe @0047b390>
sint32 __cdecl Sound3D_GetBufferVolume(sint32 handle);
// <LegoRR.exe @0047b3b0>
IDirectSoundBuffer* __cdecl Sound3D_GetSoundBuffer(sint32 handle);
// <LegoRR.exe @0047b3f0>
void __cdecl Sound3D_StopSound(sint32 handle);
// <LegoRR.exe @0047b420>
void __cdecl Sound3D_StopAllSounds(void);
// <LegoRR.exe @0047b460>
void __cdecl Sound3D_AttachSound(IDirect3DRMFrame3* frame, IDirectSound3DBuffer* sound3DBuff);
// <LegoRR.exe @0047b4e0>
void __cdecl Sound3D_RemoveSound(IDirect3DRMFrame3* frame, IDirectSound3DBuffer* sound3DBuff);
// <LegoRR.exe @0047b560>
void __cdecl Sound3D_RemoveSoundRecord(IDirect3DRMFrame3* frame, IDirectSound3DBuffer* sound3DBuff);
// <LegoRR.exe @0047b5a0>
bool32 __cdecl Sound3D_RecurseRemoveSoundRecord(IDirect3DRMFrame3* owner, IDirectSound3DBuffer* sound3DBuff, Sound3D_SoundRecord* record);
// <LegoRR.exe @0047b5f0>
bool32 __cdecl Sound3D_RecurseRemoveSound(IDirect3DRMFrame3* owner, IDirectSound3DBuffer* sound3DBuff, Sound3D_SoundFrameRecord* record);
// <LegoRR.exe @0047b650>
void __cdecl Sound3D_Update(void);
// <LegoRR.exe @0047b6d0>
void __cdecl Sound3D_SoundCallback(IDirect3DRMFrame3* tFrame, void* arg, real32 delay);
// <LegoRR.exe @0047b760>
void __cdecl Sound3D_SetMinDistForAtten(real32 dist);
// <LegoRR.exe @0047b790>
void __cdecl Sound3D_SetMaxDist(real32 dist);
// <LegoRR.exe @0047b7c0>
void __cdecl Sound3D_SetGlobalVolume(sint32 vol);
// <LegoRR.exe @0047b7f0>
void __cdecl Sound3D_SetGlobalVolumePrescaled(sint32 vol_0_10);
// <LegoRR.exe @0047b810>
void __cdecl Sound3D_SetVolumeToDefault(void);
// <LegoRR.exe @0047b840>
bool32 __cdecl Sound3D_LoadSample(Sound3D_SoundData* out_sound, char* fName, bool32 simultaneous);
// <LegoRR.exe @0047b980>
bool32 __cdecl Sound3D_CreateSoundBuffer(Sound3D_SoundData* sound);
// <LegoRR.exe @0047ba50>
bool32 __cdecl Sound3D_SendSoundToBuffer(Sound3D_SoundData* sound);
// <LegoRR.exe @0047bba0>
float10 __cdecl Sound3D_GetSamplePlayTime(sint32 handle);
// <LegoRR.exe @0047bc30>
bool32 __cdecl Sound3D_Stream_Play(char* fName, bool32 loop, sint32 volume);
// <LegoRR.exe @0047bce0>
bool32 __cdecl Sound3D_Stream_Stop(bool32 looping);
// <LegoRR.exe @0047bd60>
bool32 __cdecl Sound3D_Stream_BufferSetup(char* waveFName, bool32 loop, sint32 volume);
// <LegoRR.exe @0047bef0>
bool32 __cdecl Sound3D_Stream_FillDataBuffer(bool32 looping);
// <LegoRR.exe @0047c070>
void __cdecl Sound3D_Stream_CheckPosition(bool32 looping);
// <LegoRR.exe @0047c380>
bool32 __cdecl Sound3D_D3DVectorEqual(Vector3F* a, Vector3F* b);
// <LegoRR.exe @0047c3c0>
float10 __cdecl Sound3D_SetRollOffFactor(real32 rollOff);
// <LegoRR.exe @0047c420>
sint32 __cdecl Sound3D_MinVolume(void);
// <LegoRR.exe @0047c430>
void __cdecl DirectDraw_Initialise(HWND hWnd);
// <LegoRR.exe @0047c480>
bool32 __cdecl DirectDraw_EnumDrivers(DirectDraw_Driver* ref_list, uint32* out_count);
// <LegoRR.exe @0047c4b0>
bool32 __stdcall DirectDraw_EnumDriverCallback(LPGUID lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID lpContext);
// <LegoRR.exe @0047c5a0>
bool32 __cdecl DirectDraw_EnumDevices(DirectDraw_Driver* driver, DirectDraw_Device* ref_list, uint32* out_count);
// <LegoRR.exe @0047c640>
HRESULT __stdcall DirectDraw_EnumDeviceCallback(LPGUID lpGuid, LPSTR lpDeviceDescription, LPSTR lpDeviceName, D3DDEVICEDESC_V1* lpHWDesc, D3DDEVICEDESC_V1* lpHELDesc, LPVOID lpContext);
// <LegoRR.exe @0047c770>
bool32 __cdecl DirectDraw_EnumModes(DirectDraw_Driver* driver, bool32 fullScreen, DirectDraw_Mode* ref_list, uint32* out_count);
// <LegoRR.exe @0047c810>
HRESULT __stdcall DirectDraw_EnumModeCallback(DDSURFACEDESC2* lpDDSurfaceDesc, LPVOID lpContext);
// <LegoRR.exe @0047c8d0>
bool32 __cdecl DirectDraw_Setup(bool32 fullscreen, DirectDraw_Driver* driver, DirectDraw_Device* device, DirectDraw_Mode* screen, uint32 xPos, uint32 yPos, uint32 width, uint32 height);
// <LegoRR.exe @0047cb90>
void __cdecl DirectDraw_Flip(void);
// <LegoRR.exe @0047cbb0>
bool32 __cdecl DirectDraw_SaveBMP(IDirectDrawSurface4* surface, char* fname);
// <LegoRR.exe @0047cee0>
void __cdecl DirectDraw_ReturnFrontBuffer(void);
// <LegoRR.exe @0047cf10>
void __cdecl DirectDraw_BlitBuffers(void);
// <LegoRR.exe @0047cfb0>
void __cdecl DirectDraw_Shutdown(void);
// <LegoRR.exe @0047d010>
void __cdecl DirectDraw_AdjustTextureUsage(uint32* ref_textureUsage);
// <LegoRR.exe @0047d090>
bool32 __cdecl DirectDraw_GetAvailTextureMem(uint32* out_total, uint32* out_avil);
// <LegoRR.exe @0047d0e0>
HRESULT __cdecl DirectDraw_Clear(Area2F* window, uint32 colour);
// <LegoRR.exe @0047d1a0>
bool32 __cdecl DirectDraw_CreateClipper(bool32 fullscreen, uint32 width, uint32 height);
// <LegoRR.exe @0047d2c0>
void __cdecl DirectDraw_Blt8To16(IDirectDrawSurface4* target, IDirectDrawSurface4* source, D3DRMPaletteEntry* palette);
// <LegoRR.exe @0047d590>
uint32 __cdecl DirectDraw_GetColour(IDirectDrawSurface4* surf, uint32 colour);
// <LegoRR.exe @0047d6b0>
uint32 __cdecl DirectDraw_GetNumberOfBits(uint32 mask);
// <LegoRR.exe @0047d6d0>
void __cdecl Image_Initialise(void);
// <LegoRR.exe @0047d6f0>
void __cdecl Image_Shutdown(void);
// <LegoRR.exe @0047d730>
void __cdecl Image_Remove(Image* image);
// <LegoRR.exe @0047d750>
bool32 __cdecl Image_CopyToDataToSurface(IDirectDrawSurface4* surface, D3DRMImage* image);
// <LegoRR.exe @0047d7e0>
bool32 __cdecl Image_8BitSourceCopy(DDSURFACEDESC2* desc, D3DRMImage* image);
// <LegoRR.exe @0047d9c0>
uint32 __cdecl Image_CountMaskBits(uint32 mask);
// <LegoRR.exe @0047d9e0>
uint32 __cdecl Image_CountMaskBitShift(uint32 mask);
// <LegoRR.exe @0047da00>
void __cdecl Image_FlipSurface(DDSURFACEDESC2* desc);
// <LegoRR.exe @0047dac0>
bool32 __cdecl Image_24BitSourceCopy(DDSURFACEDESC2* desc, D3DRMImage* image);
// <LegoRR.exe @0047dc90>
Image* __cdecl Image_LoadBMPScaled(char* fileName, uint32 width, uint32 height);
// <LegoRR.exe @0047de50>
COLORREF __cdecl Image_RGB2CR(uint8 red, uint8 green, uint8 blue);
// <LegoRR.exe @0047de80>
void __cdecl Image_SetPenZeroTrans(Image* image);
// <LegoRR.exe @0047deb0>
void __cdecl Image_SetupTrans(Image* image, real32 red_low, real32 green_low, real32 blue_low, real32 red_high, real32 green_high, real32 blue_high);
// <LegoRR.exe @0047df70>
void __cdecl Image_DisplayScaled(Image* image, Area2F* src, Point2F* destPos, Size2F* destSize);
// <LegoRR.exe @0047e120>
void* __cdecl Image_LockSurface(Image* image, uint32* out_pitch, uint32* out_bpp);
// <LegoRR.exe @0047e190>
void __cdecl Image_UnlockSurface(Image* image);
// <LegoRR.exe @0047e1b0>
uint32 __cdecl Image_GetPen255(Image* image);
// <LegoRR.exe @0047e210>
uint32 __cdecl Image_GetPixelMask(Image* image);
// <LegoRR.exe @0047e260>
bool32 __cdecl Image_GetPixel(Image* image, uint32 x, uint32 y, uint32* out_colour);
// <LegoRR.exe @0047e310>
Image* __cdecl Image_Create(IDirectDrawSurface4* surface, uint32 width, uint32 height, COLORREF penZero, COLORREF pen255);
// <LegoRR.exe @0047e380>
void __cdecl Image_AddList(void);
// <LegoRR.exe @0047e3f0>
void __cdecl Image_RemoveAll(void);
// <LegoRR.exe @0047e450>
DWORD __cdecl Image_DDColorMatch(IDirectDrawSurface4* pdds, DWORD rgb);
// <LegoRR.exe @0047e590>
void __cdecl Image_CR2RGB(COLORREF cr, uint8* out_r, uint8* out_g, uint8* out_b);
// <LegoRR.exe @0047e5c0>
void __cdecl Image_GetScreenshot(Image* ref_image, uint32 xsize, uint32 ysize);
// <LegoRR.exe @0047e6a0>
void __cdecl Image_InitFromSurface(Image* ref_newImage, IDirectDrawSurface4* surface, uint32 width, uint32 height, COLORREF penZero, COLORREF pen255);
// <LegoRR.exe @0047e700>
bool32 __cdecl Image_SaveBMP(Image* image, char* fname);
// <LegoRR.exe @0047e720>
G98CSurface* __thiscall G98CSurface___deletor(void* this, G98CSurface* This, uint8 flag);
// <LegoRR.exe @0047e740>
void __thiscall G98CSurface___dtor(G98CSurface* this);
// <LegoRR.exe @0047e780>
G98CSurface* __thiscall G98CSurface___ctor(G98CSurface* this, sint32 width, sint32 height, sint32 bpp, bool vram, bool fullScreen);
// <LegoRR.exe @0047e7d0>
bool __thiscall G98CSurface__Init(G98CSurface* this, sint32 width, sint32 height, sint32 bpp, bool vram);
// <LegoRR.exe @0047e9d0>
void __thiscall G98CSurface__PreInit(G98CSurface* this, bool fullscreen);
// <LegoRR.exe @0047ea00>
sint32 __thiscall G98CSurface__Width(void* this, G98CSurface* This);
// <LegoRR.exe @0047ea10>
sint32 __thiscall G98CSurface__Height(void* this, G98CSurface* This);
// <LegoRR.exe @0047ea20>
bool __thiscall G98CSurface__Lock(G98CSurface* this);
// <LegoRR.exe @0047ea70>
bool __thiscall G98CSurface__Unlock(G98CSurface* this);
// <LegoRR.exe @0047eaa0>
sint32 __thiscall G98CSurface__CountMaskBits(G98CSurface* this, uint32 mask);
// <LegoRR.exe @0047eac0>
G98CAnimation* __thiscall G98CAnimation___ctor(G98CAnimation* this, char* filename);
// <LegoRR.exe @0047ec40>
G98CAnimation* __thiscall G98CAnimation___deletor(void* this, G98CAnimation* This, uint8 flag);
// <LegoRR.exe @0047ec60>
void __thiscall G98CAnimation___dtor(G98CAnimation* this);
// <LegoRR.exe @0047eca0>
void __thiscall G98CAnimation__BMICopy(G98CAnimation* this, BITMAPINFO* bmi);
// <LegoRR.exe @0047ede0>
bool __thiscall G98CAnimation__Update(G98CAnimation* this);
// <LegoRR.exe @0047eea0>
uint32 __thiscall G98CAnimation__Length(G98CAnimation* this);
// <LegoRR.exe @0047eeb0>
void __thiscall G98CAnimation__SetTime(G98CAnimation* this, uint32 time);
// <LegoRR.exe @0047ef20>
uint32 __thiscall G98CAnimation__GetTime(G98CAnimation* this);
// <LegoRR.exe @0047ef40>
void __cdecl Animation_Initialise(IDirectDraw4* directDraw);
// <LegoRR.exe @0047ef50>
Animation_t* __cdecl Animation_Load(char* fName);
// <LegoRR.exe @0047efb0>
bool32 __cdecl Animation_Update(Animation_t* anim);
// <LegoRR.exe @0047efc0>
void __cdecl Animation_BlitToBackBuffer(Animation_t* anim, RECT* destRect);
// <LegoRR.exe @0047f000>
void __cdecl Animation_SetTime(Animation_t* anim, uint32 time);
// <LegoRR.exe @0047f010>
uint32 __cdecl Animation_GetTime(Animation_t* anim);
// <LegoRR.exe @0047f020>
uint32 __cdecl Animation_GetLength(Animation_t* anim);
// <LegoRR.exe @0047f030>
void __cdecl Animation_Free(Animation_t* anim);
// <LegoRR.exe @0047f040>
bool32 __cdecl Animation_IsOk(Animation_t* anim);
// <LegoRR.exe @0047f050>
bool32 __cdecl Input_InitKeysAndDI(void);
// <LegoRR.exe @0047f1b0>
void __cdecl Input_ReadKeys(void);
// <LegoRR.exe @0047f270>
uint32 __cdecl Input_AnyKeyPressed(void);
// <LegoRR.exe @0047f290>
void __cdecl Input_ReleaseKeysAndDI(void);
// <LegoRR.exe @0047f2d0>
void __cdecl Input_ReadMouse2(void);
// <LegoRR.exe @0047f390>
bool32 __cdecl Input_SetCursorPos(sint32 x, sint32 y);
// <LegoRR.exe @0047f3f0>
void __cdecl File_Initialise(char* programName, bool32 insistOnCD, char* registryLocation);
// <LegoRR.exe @0047f7b0>
bool32 __cdecl File_FindDataCD(void);
// <LegoRR.exe @0047f850>
bool32 __cdecl File_SetBaseSearchPath(char* basePath);
// <LegoRR.exe @0047f8c0>
void __cdecl File_Error(char* msg, ...);
// <LegoRR.exe @0047f900>
sint32 __cdecl File_LoadWad(char* fName);
// <LegoRR.exe @0047f920>
bool32 __cdecl File_GetCDFilePath(char* out_path, char* fname);
// <LegoRR.exe @0047f960>
sint32 __cdecl File_MakeDir(char* path);
// <LegoRR.exe @0047f9a0>
File* __cdecl File_Open(char* fName, char* mode);
// <LegoRR.exe @0047fb10>
sint32 __cdecl File_Seek(File* f, sint32 pos, sint32 origin);
// <LegoRR.exe @0047fc40>
sint32 __cdecl File_Read(void* out_buffer, sint32 size, sint32 count, File* f);
// <LegoRR.exe @0047fd10>
sint32 __cdecl File_Write(void* buffer, sint32 size, sint32 count, File* f);
// <LegoRR.exe @0047fd80>
sint32 __cdecl File_Close(File* f);
// <LegoRR.exe @0047fdd0>
sint32 __cdecl File_Tell(File* f);
// <LegoRR.exe @0047fe20>
bool32 __cdecl File_Exists(char* fName);
// <LegoRR.exe @0047fee0>
sint32 __cdecl File_GetC(File* f);
// <LegoRR.exe @0047ff60>
sint32 __cdecl File_Length(File* f);
// <LegoRR.exe @0047ffa0>
char* __cdecl File_InternalFGetS(char* out_str, sint32 num, File* f);
// <LegoRR.exe @00480000>
char* __cdecl File_GetS(char* out_str, sint32 num, File* f);
// <LegoRR.exe @00480070>
sint32 __cdecl File_PrintF(File* f, char* msg, ...);
// <LegoRR.exe @004800e0>
FileSystemType __cdecl _File_GetSystem(File* f);
// <LegoRR.exe @004800f0>
FileSystemType __cdecl _File_CheckSystem(char* fName, char* mode);
// <LegoRR.exe @00480160>
bool32 __cdecl _File_OpenWad(WADFILE* wad, char* fName);
// <LegoRR.exe @00480190>
File* __cdecl _File_Alloc(FileSystemType fType);
// <LegoRR.exe @004801f0>
void* __cdecl _File_Malloc(sint32 size);
// <LegoRR.exe @00480200>
void __cdecl _File_Free(void* ptr);
// <LegoRR.exe @00480210>
void __cdecl _File_Dealloc(File* file);
// <LegoRR.exe @00480280>
char* __cdecl _File_GetWadName(char* fName);
// <LegoRR.exe @00480310>
char* __cdecl File_GetLine(char* out_str, uint32 size, File* file);
// <LegoRR.exe @00480360>
uint8* __cdecl File_LoadBinary(char* filename, uint32* out_size);
// <LegoRR.exe @00480380>
void* __cdecl File_Load(char* filename, uint32* out_size, bool32 binary);
// <LegoRR.exe @00480430>
uint32 __cdecl File_LoadBinaryHandle(char* filename, uint32* out_size);
// <LegoRR.exe @004804e0>
char* __cdecl File_VerifyFilename(char* filename);
// <LegoRR.exe @00480570>
void __cdecl File_SetLoadCallback(FileLoadCallback callback, void* data);
// <LegoRR.exe @00480590>
void __cdecl File_CheckRedundantFiles(char* logName);
// <LegoRR.exe @00480650>
void __cdecl File_CheckDirectory(char* dirName);
// <LegoRR.exe @00480830>
void __cdecl File_CheckFile(char* fileName);
// <LegoRR.exe @00480870>
bool32 __cdecl Mesh_Initialise(char* sharedTextureDir);
// <LegoRR.exe @00480910>
bool32 __cdecl Mesh_CreateGlobalMaterial(void);
// <LegoRR.exe @00480a40>
bool32 __cdecl Mesh_SetMaterial(D3DMaterial* newMaterial);
// <LegoRR.exe @00480a60>
Mesh* __cdecl Mesh_ObtainFromList(void);
// <LegoRR.exe @00480a90>
void __cdecl Mesh_ReturnToList(Mesh* mesh);
// <LegoRR.exe @00480ab0>
void __cdecl Mesh_AddList(void);
// <LegoRR.exe @00480b30>
Mesh* __cdecl Mesh_CreateOnFrame(IDirect3DRMFrame3* frame, MeshRenderCallback renderFunc, uint32 renderFlags, void* data, MeshType type);
// <LegoRR.exe @00480bc0>
Mesh* __cdecl Mesh_Clone(Mesh* mesh, IDirect3DRMFrame3* frame);
// <LegoRR.exe @00480ca0>
Mesh* __cdecl Mesh_Load(char* filename, IDirect3DRMFrame3* frame, bool32 noTextures);
// <LegoRR.exe @00480d80>
bool32 __cdecl Mesh_ParseLWO(char* basePath, Mesh* mesh, APPOBJ* lightWaveObject, bool32 noTextures);
// <LegoRR.exe @00481ae0>
void __cdecl Mesh_GetSurfInfo(char* basePath, APPOBJ* param_2, Mesh_LightWave_Surface* lightWaveSurf, bool32 noTextures);
// <LegoRR.exe @00481d80>
bool32 __cdecl Mesh_GetTextureSeqInfo(char* tname, char* out_tfname, sint32* out_tstart, sint32* out_tnumlen);
// <LegoRR.exe @00481e40>
void __cdecl Mesh_GetNextInSequence(char* baseName, char* out_nextTextName, uint32* out_texNum, uint32 tnumlen);
// <LegoRR.exe @00481f10>
void __cdecl Mesh_UViewMesh(APPOBJ* lightWaveObject, Point2F* textCoords);
// <LegoRR.exe @00482260>
void __cdecl Mesh_GetTextureUVsWrap(uint32 vertexCount, Vector3F* vertices, Point2F* coords, real32 sx, real32 sy, real32 sz, real32 px, real32 py, real32 pz, LWTEXFLAGS flags);
// <LegoRR.exe @00482300>
bool32 __cdecl Mesh_SetTextureTime2(Mesh* mesh, real32 frame);
// <LegoRR.exe @00482390>
void __cdecl Mesh_Remove(Mesh* mesh, IDirect3DRMFrame3* frame);
// <LegoRR.exe @00482460>
Mesh_Group* __cdecl Mesh_GetGroup(Mesh* mesh, D3DRMGroupIndex groupID, uint32* out_vertexCount, uint32* unused_out_faceCount, uint32* out_vPerFace, uint32* out_faceDataSize, uint32* out_faceData);
// <LegoRR.exe @004824d0>
uint32 __cdecl Mesh_GetGroupCount(Mesh* mesh);
// <LegoRR.exe @004824e0>
sint32 __cdecl Mesh_AddGroup(Mesh* mesh, uint32 vertexCount, uint32 faceCount, uint32 vPerFace, uint32* faceData);
// <LegoRR.exe @00482610>
void __cdecl Mesh_AlterGroupRenderFlags(Mesh* mesh, D3DRMGroupIndex groupID, uint32 newFlags);
// <LegoRR.exe @00482630>
void __cdecl Mesh_Scale(Mesh* mesh, real32 x, real32 y, real32 z);
// <LegoRR.exe @004826a0>
void __cdecl Mesh_SetVertices(Mesh* mesh, D3DRMGroupIndex groupID, uint32 index, uint32 count, Vertex3F* vertices);
// <LegoRR.exe @00482730>
void __cdecl Mesh_GetVertices(Mesh* mesh, D3DRMGroupIndex groupID, uint32 index, uint32 count, Vertex3F* out_vertices);
// <LegoRR.exe @004827c0>
void __cdecl Mesh_SetVertices_PointNormalAt(Mesh* mesh, D3DRMGroupIndex groupID, uint32 index, uint32 count, Vector3F* vertices, Vector3F* position, Point2F* textCoords);
// <LegoRR.exe @004828e0>
void __cdecl Mesh_SetVertices_SameNormal(Mesh* mesh, D3DRMGroupIndex groupID, uint32 index, uint32 count, Vector3F* vertices, Vector3F* normal, Point2F* textCoords);
// <LegoRR.exe @00482980>
void __cdecl Mesh_SetVertices_VNT(Mesh* mesh, D3DRMGroupIndex groupID, uint32 index, uint32 count, Vector3F* vertices, Vector3F** normal, Point2I* textCoords);
// <LegoRR.exe @00482a40>
bool32 __cdecl Mesh_IsGroupHidden(Mesh* mesh, D3DRMGroupIndex groupID);
// <LegoRR.exe @00482a60>
void __cdecl Mesh_HideGroup(Mesh* mesh, D3DRMGroupIndex groupID, bool32 hide);
// <LegoRR.exe @00482a90>
void __cdecl Mesh_Hide(Mesh* mesh, bool32 hide);
// <LegoRR.exe @00482ab0>
bool32 __cdecl Mesh_RenderCallback(IDirect3DRMUserVisual* lpD3DRMUV, Mesh* lpArg, D3DRMUserVisualReason lpD3DRMUVreason, IUnknown* lpD3DRMDev, IDirect3DRMViewport* lpD3DRMview);
// <LegoRR.exe @00482d80>
void __cdecl Mesh_SetMeshRenderDesc(Mesh* mesh, Viewport* view, Matrix4F* matWorld, bool32 alphaBlend);
// <LegoRR.exe @00482e10>
void __cdecl Mesh_SetRenderDesc(uint32 flags, Matrix4F* matWorld, bool32 alphaBlend);
// <LegoRR.exe @00482f70>
void __cdecl Mesh_SetAlphaRender(D3DBlend src, D3DBlend dest);
// <LegoRR.exe @00482fa0>
void __cdecl Mesh_AddToPostRenderList(Mesh* mesh, Matrix4F* matWorld);
// <LegoRR.exe @00482ff0>
void __cdecl Mesh_ClearPostRenderList(void);
// <LegoRR.exe @00483020>
void __cdecl Mesh_PostRenderAll(Viewport* view);
// <LegoRR.exe @00483130>
Container_Texture* __cdecl Mesh_LoadTexture(char* baseDir, char* name, uint32* out_width, uint32* out_height);
// <LegoRR.exe @004832f0>
Mesh_TextureReference* __cdecl Mesh_SearchTexturePathList(Mesh_TextureReference* list, uint32 count, char* path);
// <LegoRR.exe @00483340>
void __cdecl Mesh_AddTexturePathEntry(Mesh_TextureReference* list, uint32* ref_count, char* path, IDirectDrawSurface4* surface, bool32 trans);
// <LegoRR.exe @00483380>
void __cdecl Mesh_SetGroupTexture(Mesh* mesh, D3DRMGroupIndex groupID, Container_Texture* mt);
// <LegoRR.exe @00483400>
void __cdecl Mesh_RemoveGroupTexture(Mesh* mesh, D3DRMGroupIndex groupID);
// <LegoRR.exe @00483430>
bool32 __cdecl Mesh_CreateGroupMaterial(Mesh* mesh, D3DRMGroupIndex groupID);
// <LegoRR.exe @00483500>
bool32 __cdecl Mesh_SetGroupMaterial(Mesh* mesh, D3DRMGroupIndex groupID, D3DMaterial* mat);
// <LegoRR.exe @00483530>
bool32 __cdecl Mesh_SetGroupColour(Mesh* mesh, D3DRMGroupIndex groupID, real32 r, real32 g, real32 b, MaterialType matType);
// <LegoRR.exe @004836c0>
D3DMaterial* __cdecl Mesh_GetGroupMaterial(Mesh* mesh, D3DRMGroupIndex groupID);
// <LegoRR.exe @004836e0>
bool32 __cdecl Mesh_SetGroupMaterialValues(Mesh* mesh, D3DRMGroupIndex groupID, real32 value, MaterialType matType);
// <LegoRR.exe @00483800>
void __cdecl Mesh_SetIdentityMatrix(Matrix4F* out_matrix);
// <LegoRR.exe @00483840>
bool32 __cdecl Mesh_SetCurrentViewport(IDirect3DRMViewport* rmViewport);
// <LegoRR.exe @004838c0>
bool32 __cdecl Mesh_SetCurrentGODSViewport(Viewport* view);
// <LegoRR.exe @00483950>
bool32 __cdecl Mesh_SetTransform(D3DTransformStateType state, Matrix4F* matrix);
// <LegoRR.exe @00483ad0>
bool32 __cdecl Mesh_ChangeTextureStageState(D3DTextureStageStateType dwRenderStateType, DWORD dwRenderState);
// <LegoRR.exe @00483b70>
void __cdecl Mesh_StoreTextureAndMat(void);
// <LegoRR.exe @00483c00>
void __cdecl Mesh_RestoreTextureAndMat(void);
// <LegoRR.exe @00483c80>
bool32 __cdecl Mesh_RenderMesh(Mesh* mesh, Matrix4F* matWorld, bool32 alphaBlend);
// <LegoRR.exe @00483d30>
bool32 __cdecl Mesh_CanRenderGroup(Mesh_Group* group);
// <LegoRR.exe @00483d50>
bool32 __cdecl Mesh_RenderGroup(Mesh* mesh, Mesh_Group* group, Matrix4F* matWorld, bool32 alphaBlend);
// <LegoRR.exe @00483dc0>
bool32 __cdecl Mesh_SetGroupRenderDesc(Mesh* mesh, Mesh_Group* group, Matrix4F* matWorld, bool32 alphaBlend);
// <LegoRR.exe @00483e30>
bool32 __cdecl Mesh_RenderTriangleList(DWORD matHandle, IDirect3DTexture2* texture, DWORD renderFlags, Mesh_Vertex* vertices, DWORD vertexCount, WORD* faceData, DWORD indexCount);
// <LegoRR.exe @00483f40>
bool32 __cdecl Flic_Setup(char* filename, Flic** out_fsp, FlicUserFlags flags);
// <LegoRR.exe @004841c0>
bool32 __cdecl Flic_Close(Flic* fsp);
// <LegoRR.exe @00484220>
bool32 __cdecl Flic_LoadHeader(char* filename, Flic** fsp);
// <LegoRR.exe @00484330>
bool32 __cdecl Flic_Animate(Flic* fsp, Area2F* destArea, bool32 advance, bool32 trans);
// <LegoRR.exe @00484490>
FlicError __cdecl Flic_Memory(Flic* fsp);
// <LegoRR.exe @00484520>
FlicError __cdecl Flic_Load(Flic* fsp);
// <LegoRR.exe @004845e0>
FlicError __cdecl Flic_FindChunk(Flic* fsp);
// <LegoRR.exe @00484770>
bool32 __cdecl Flic_FrameChunk(Flic* fsp);
// <LegoRR.exe @004848d0>
FlicError __cdecl Flic_DoChunk(Flic* fsp);
// <LegoRR.exe @004849e0>
FlicError __cdecl Flic_LoadPointers(Flic* fsp);
// <LegoRR.exe @00484a90>
FlicError __cdecl Flic_LoadPalette64(Flic* fsp);
// <LegoRR.exe @00484b40>
bool32 __cdecl Flic_Copy(Flic* fsp);
// <LegoRR.exe @00484b90>
bool32 __cdecl FlicBRunDepackHiColor(Flic* fsp);
// <LegoRR.exe @00484c90>
bool32 __cdecl FlicBRunDepackHiColorFlic32k(Flic* fsp);
// <LegoRR.exe @00484de0>
bool32 __cdecl Flic_BrunDepack(Flic* fsp);
// <LegoRR.exe @00484e50>
sint32 __cdecl NERPFunc__True(sint32* stack);
// <LegoRR.exe @00484e60>
void __cdecl FlicCreateHiColorTable(Flic* fsp);
// <LegoRR.exe @00484ec0>
bool32 __cdecl Flic_Palette256(Flic* fsp);
// <LegoRR.exe @00484f50>
void __cdecl logf_removed(char* message, ...);
// <LegoRR.exe @00484f60>
void __cdecl FlicDeltaWordHiColor(Flic* fsp);
// <LegoRR.exe @00485110>
void __cdecl FlicDeltaWordHiColorFlic32k(Flic* fsp);
// <LegoRR.exe @004852f0>
bool32 __cdecl Flic_DeltaWord(Flic* fsp);
// <LegoRR.exe @00485380>
uint16 __cdecl getFlicCol(uint8 n, Flic* fsp);
// <LegoRR.exe @004853a0>
uint32 __cdecl Flic_GetHeight(Flic* fsp);
// <LegoRR.exe @004853b0>
TextWindow* __cdecl TextWindow_Create(Font* font, Area2F* area, uint32 size);
// <LegoRR.exe @00485420>
void __cdecl TextWindow_EnableCentering(TextWindow* textWnd, bool32 enable);
// <LegoRR.exe @00485450>
void __cdecl TextWindow_Remove(TextWindow* textWnd);
// <LegoRR.exe @00485470>
void __cdecl TextWindow_ChangePosition(TextWindow* textWnd, sint32 xpos, sint32 ypos);
// <LegoRR.exe @00485490>
void __cdecl TextWindow_ChangeSize(TextWindow* textWnd, uint32 width, uint32 height);
// <LegoRR.exe @004854d0>
void __cdecl TextWindow_PagePrintF(TextWindow* textWnd, sint32 page, char* format, ...);
// <LegoRR.exe @004854f0>
void __cdecl TextWindow_PrintF(TextWindow* textWnd, char* format, ...);
// <LegoRR.exe @00485510>
void __cdecl TextWindow_VPrintF(TextWindow* textWnd, sint32 page, char* format, va_list argptr);
// <LegoRR.exe @004855c0>
void __cdecl TextWindow_PrintFOverlay(TextWindow* textWnd, bool32 oneFrame, char* format, ...);
// <LegoRR.exe @00485650>
bool32 __cdecl TextWindow_Update(TextWindow* textWnd, uint32 posFromEnd, real32 elapsed, sint32* out_lowestPoint);
// <LegoRR.exe @004859d0>
bool32 __cdecl TextWindow_UpdateOverlay(TextWindow* textWnd, real32 elapsed, sint32* out_lowestPoint);
// <LegoRR.exe @00485c70>
void __cdecl TextWindow_Clear(TextWindow* textWnd);
// <LegoRR.exe @00485cc0>
void __cdecl TextWindow_GetInfo(TextWindow* textWnd, uint32* out_linesCount, uint32* out_linesCapacity);
// <LegoRR.exe @00485ce0>
void __cdecl Keys_Initialise(void);
// <LegoRR.exe @004860f0>
bool32 __cdecl Key_Find(char* name, KeysByte* out_keyCode);
// <LegoRR.exe @00486140>
void __cdecl Draw_Initialise(Area2F* window);
// <LegoRR.exe @00486160>
void __cdecl Draw_SetClipWindow(Area2F* window);
// <LegoRR.exe @00486270>
void __cdecl Draw_GetClipWindow(Area2F* out_window);
// <LegoRR.exe @004862b0>
void __cdecl Draw_LineListEx(Point2F* fromList, Point2F* toList, uint32 count, real32 r, real32 g, real32 b, DrawEffect effect);
// <LegoRR.exe @00486350>
void __cdecl Draw_RectListEx(Area2F* rectList, uint32 count, real32 r, real32 g, real32 b, DrawEffect effect);
// <LegoRR.exe @004864d0>
void __cdecl Draw_RectList2Ex(Draw_Rect* rectList, uint32 count, DrawEffect effect);
// <LegoRR.exe @00486650>
float10 __cdecl Draw_DotCircle(Point2F* pos, uint32 radius, uint32 dots, real32 r, real32 g, real32 b, DrawEffect effect);
// <LegoRR.exe @00486790>
uint32 __cdecl Draw_GetColour(real32 r, real32 g, real32 b);
// <LegoRR.exe @00486810>
bool32 __cdecl Draw_LockSurface(IDirectDrawSurface4* surface, DrawEffect effect);
// <LegoRR.exe @00486910>
void __cdecl Draw_UnlockSurface(IDirectDrawSurface4* surface);
// <LegoRR.exe @00486950>
bool32 __cdecl Draw_SetDrawPixelFunc(DrawEffect effect);
// <LegoRR.exe @004869e0>
void __cdecl Draw_LineActual(sint32 x1, sint32 y1, sint32 x2, sint32 y2, uint32 colour);
// <LegoRR.exe @00486b40>
void __cdecl Draw_Pixel8(sint32 x, sint32 y, uint32 value);
// <LegoRR.exe @00486b60>
void __cdecl Draw_Pixel16(sint32 x, sint32 y, uint32 value);
// <LegoRR.exe @00486b90>
void __cdecl Draw_Pixel16XOR(sint32 x, sint32 y, uint32 value);
// <LegoRR.exe @00486bc0>
void __cdecl Draw_Pixel16HalfTrans(sint32 x, sint32 y, uint32 value);
// <LegoRR.exe @00486c60>
void __cdecl Draw_Pixel24(sint32 x, sint32 y, uint32 value);
// <LegoRR.exe @00486c90>
void __cdecl Draw_Pixel32(sint32 x, sint32 y, uint32 value);
// <LegoRR.exe @00486cb0>
Lws_Info* __cdecl Lws_Parse(char* fname, bool32 looping);
// <LegoRR.exe @00487980>
void __cdecl Lws_Initialise(char* sharedDir, LwsFindSFXIDFunc FindSFXID, LwsPlaySample3DFunc PlaySample3D, LwsSoundEnabledFunc SoundEnabled);
// <LegoRR.exe @00487a20>
void __cdecl Lws_Shutdown(void);
// <LegoRR.exe @00487a90>
uint32 __cdecl Lws_GetFrameCount(Lws_Info* scene);
// <LegoRR.exe @00487aa0>
void __cdecl Lws_SetupSoundTriggers(Lws_Info* scene);
// <LegoRR.exe @00487c50>
void __cdecl Lws_LoadMeshes(Lws_Info* scene, IDirect3DRMFrame3* parent);
// <LegoRR.exe @00487cc0>
Lws_Info* __cdecl Lws_Clone(Lws_Info* scene, IDirect3DRMFrame3* parent);
// <LegoRR.exe @00487e60>
void __cdecl Lws_SetTime(Lws_Info* scene, real32 time);
// <LegoRR.exe @00487f70>
float10 __cdecl Lws_FindPrevKey(Lws_Node* node, real32 time, uint16* prev);
// <LegoRR.exe @00488010>
void __cdecl Lws_AnimateTextures(Lws_Info* scene, Lws_Node* node);
// <LegoRR.exe @004880a0>
void __cdecl Lws_HandleTrigger(Lws_Info* scene, Lws_Node* node);
// <LegoRR.exe @00488190>
bool32 __cdecl Lws_KeyPassed(Lws_Info* scene, uint32 key);
// <LegoRR.exe @00488280>
float10 __cdecl Lws_FindPrevDissolve(Lws_Node* node, real32 time, uint16* prev);
// <LegoRR.exe @00488330>
void __cdecl Lws_InterpolateDissolve(Lws_Info* scene, Lws_Node* node, uint16 prev, real32 delta);
// <LegoRR.exe @00488390>
void __cdecl Lws_SetDissolveLevel(Lws_Info* scene, Lws_Node* node, real32 level);
// <LegoRR.exe @00488430>
void __cdecl Lws_InterpolateKeys(Lws_Info* scene, Lws_Node* node, uint16 key, real32 delta);
// <LegoRR.exe @004885a0>
void __cdecl Lws_SetupNodeTransform(Lws_Info* scene, Lws_Node* node, Vector3F* pos, Vector3F* hpb, Vector3F* scale);
// <LegoRR.exe @00488880>
Mesh* __cdecl Lws_LoadMesh(char* baseDir, char* fname, IDirect3DRMFrame3* frame, bool32 noTextures);
// <LegoRR.exe @004889f0>
Mesh* __cdecl Lws_SearchMeshPathList(Lws_MeshPath* list, uint32 count, char* path);
// <LegoRR.exe @00488a50>
void __cdecl Lws_AddMeshPathEntry(Lws_MeshPath* ref_list, uint32* ref_count, char* path, Mesh* mesh);
// <LegoRR.exe @00488a80>
void __cdecl Lws_CreateFrames(Lws_Info* scene, Lws_Node* node, IDirect3DRMFrame3* parent, uint16* ref_frameCount);
// <LegoRR.exe @00488bc0>
void __cdecl Lws_LoadNodes(Lws_Info* scene, Lws_Node* node);
// <LegoRR.exe @00488c60>
void __cdecl Lws_SetAbsoluteKey(Lws_Info* scene, Lws_Node* node, uint16 key);
// <LegoRR.exe @00488c90>
void __cdecl Lws_Free(Lws_Info* scene);
// <LegoRR.exe @00488d30>
void __cdecl Lws_FreeNode(Lws_Info* scene, Lws_Node* node);
// <LegoRR.exe @00488e10>
bool32 __cdecl Sound_Initialise(bool32 nosound);
// <LegoRR.exe @00488e50>
bool32 __cdecl Sound_IsInitialised(void);
// <LegoRR.exe @00488e70>
bool32 __cdecl Sound_PlayCDTrack(uint32 track, SoundMode mode, SoundCDStopCallback stopCallback);
// <LegoRR.exe @00488eb0>
bool32 __cdecl Sound_StopCD(void);
// <LegoRR.exe @00488ec0>
void __cdecl Sound_Update(bool32 cdtrack);
// <LegoRR.exe @00488f30>
sint32 __cdecl WaveOpenFile(void* fileData, uint32 fileSize, HMMIO* out_phmmioIn, WAVEFORMATEX** out_ppwfxInfo, MMCKINFO* out_pckInRIFF);
// <LegoRR.exe @00489130>
uint32 __cdecl GetWaveAvgBytesPerSec(char* pszFileName);
// <LegoRR.exe @004891d0>
sint32 __cdecl WaveOpenFile2(char* pszFileName, HMMIO* out_phmmioIn, WAVEFORMATEX** out_ppwfxInfo, MMCKINFO* out_pckInRIFF);
// <LegoRR.exe @00489380>
sint32 __cdecl WaveStartDataRead(HMMIO* phmmioIn, MMCKINFO* pckIn, MMCKINFO* pckInRIFF);
// <LegoRR.exe @004893c0>
sint32 __cdecl WaveReadFile(HMMIO hmmioIn, uint32 cbRead, uint8* pbDest, MMCKINFO* pckIn, uint32* cbActualRead);
// <LegoRR.exe @00489490>
sint32 __cdecl WaveCloseReadFile(HMMIO* phmmio, WAVEFORMATEX** ppwfxSrc);
// <LegoRR.exe @004894d0>
bool32 __cdecl Restart_CDTrack(sint32 track);
// <LegoRR.exe @00489520>
void __cdecl ReportCDError(void);
// <LegoRR.exe @00489540>
bool32 __cdecl Status_CDTrack(sint32 track);
// <LegoRR.exe @004895f0>
bool32 __cdecl Play_CDTrack(sint32 track);
// <LegoRR.exe @00489660>
bool32 __cdecl Stop_CDTrack(void);
// <LegoRR.exe @004896b0>
void __cdecl Mem_Initialise(void);
// <LegoRR.exe @004896d0>
uint32 __cdecl Mem_AllocHandle(uint32 size);
// <LegoRR.exe @00489720>
void __cdecl Mem_FreeHandle(uint32 handle);
// <LegoRR.exe @00489760>
void* __cdecl Mem_AddressHandle(uint32 handle);
// <LegoRR.exe @00489780>
IDirect3DRMMaterial2* __cdecl Material_Create(real32 emissiveRed, real32 emissiveGreen, real32 emissiveBlue, real32 specularRed, real32 specularGreen, real32 specularBlue, real32 power);
// <LegoRR.exe @004897e0>
AnimClone* __cdecl AnimClone_Register(IDirect3DRMAnimationSet2* animSet, IDirect3DRMFrame3* root, uint32 frameCount);
// <LegoRR.exe @00489880>
AnimClone* __cdecl AnimClone_RegisterLws(void* struct38, IDirect3DRMFrame3* rmFrame3, undefined4 field1c);
// <LegoRR.exe @00489920>
AnimClone* __cdecl AnimClone_Make(AnimClone* lastActFrameRes, IDirect3DRMFrame3* parent, uint32* out_frameCount);
// <LegoRR.exe @00489a10>
void __cdecl AnimClone_Remove(AnimClone* actFrameRes);
// <LegoRR.exe @00489a90>
bool32 __cdecl AnimClone_IsLws__Flic_GetWidth(AnimClone* clone);
// <LegoRR.exe @00489aa0>
void __cdecl AnimClone_SetTime(AnimClone* clone, real32 time, real32* out_oldTime);
// <LegoRR.exe @00489ba0>
bool32 __cdecl AnimClone_FrameCountCallback(IDirect3DRMFrame3* frame, sint32* lpFramesCount);
// <LegoRR.exe @00489bb0>
bool32 __cdecl AnimClone_SetupFrameArrayCallback(IDirect3DRMFrame3* frame, AnimClone* actFrameRes);
// <LegoRR.exe @00489bd0>
bool32 __cdecl AnimClone_WalkTree(IDirect3DRMFrame3* frame, uint32 level, AnimCloneWalkTreeCallback Callback, IDirect3DRMFrame3* data);
// <LegoRR.exe @00489cb0>
void __cdecl AnimClone_CreateCopy(IDirect3DRMFrame3* orig, IDirect3DRMFrame3* clone, bool32 lws);
// <LegoRR.exe @00489df0>
void __cdecl AnimClone_CloneLwsMesh(IDirect3DRMFrame3* rmFrame3, IDirect3DRMFrame3* param_2);
// <LegoRR.exe @00489e80>
void __cdecl AnimClone_ReferenceVisuals(IDirect3DRMFrame3* orig, IDirect3DRMFrame3* clone);
// <LegoRR.exe @00489ef0>
void __cdecl BMP_Parse(BITMAP_FILE_INFO_STRUCT* data, uint32 size, D3DRMImage* istruct);
// <LegoRR.exe @0048a030>
void __cdecl BMP_Cleanup(D3DRMImage* istruct);
// <LegoRR.exe @0048a050>
void __cdecl SE(char* error, char* errorDesc);
// <LegoRR.exe @0048a090>
HRESULT __cdecl Error_SetDXError(HRESULT err, sint32 DXModule, char* File, sint32 Line);
// <LegoRR.exe @0048b520>
void __cdecl Error_Initialise(void);
// <LegoRR.exe @0048b540>
void __cdecl Error_FullScreen(bool32 on);
// <LegoRR.exe @0048b550>
void __cdecl Error_CloseLog(void);
// <LegoRR.exe @0048b5b0>
void __cdecl Error_Shutdown(void);
// <LegoRR.exe @0048b5f0>
char* __cdecl Registry_GetKeyFromPath(char* path, char* out_str);
// <LegoRR.exe @0048b620>
bool32 __cdecl Registry_GetValue(char* path, char* key, RegistryType dataType, char* out_data, uint32 dataSize);
// <LegoRR.exe @0048b650>
bool32 __cdecl Registry_GetValue_Recursive(HKEY parent, char* path, char* key, RegistryType dataType, char* out_data, uint32 dataSize);
// <LegoRR.exe @0048b760>
bool32 __cdecl GetFileName(FILE* f, char* out_str);
// <LegoRR.exe @0048b7a0>
sint32 __cdecl Wad_Load(char* fName);
// <LegoRR.exe @0048bfa0>
Wad* __cdecl Wad_Get(sint32 wadNo);
// <LegoRR.exe @0048bfb0>
sint32 __cdecl Wad_FileLength(sint32 wadNo, sint32 fileNo);
// <LegoRR.exe @0048bfd0>
sint32 __cdecl Wad_FileCompressedLength(sint32 wadNo, sint32 fileNo);
// <LegoRR.exe @0048bff0>
sint32 __cdecl Wad_FindFreeFileHandle(void);
// <LegoRR.exe @0048c010>
sint32 __cdecl Wad_IsFileInWad(char* fName, sint32 opt_wadNo);
// <LegoRR.exe @0048c060>
sint32 __cdecl _Wad_IsFileInWad(char* fName, sint32 wadNo);
// <LegoRR.exe @0048c0c0>
sint32 __cdecl Wad_GetFreeWadSlot(void);
// <LegoRR.exe @0048c100>
sint32 __cdecl _Wad_FileOpen(char* fName, sint32 wadNo);
// <LegoRR.exe @0048c230>
sint32 __cdecl Wad_FileOpen(char* fName, sint32 opt_wadNo);
// <LegoRR.exe @0048c280>
void __cdecl Wad_FileClose(sint32 handle);
// <LegoRR.exe @0048c2b0>
void* __cdecl Wad_FileGetPointer(sint32 handle);
// <LegoRR.exe @0048c2d0>
sint32 __cdecl Wad_hLength(sint32 handle);
// <LegoRR.exe @0048c2f0>
void* __cdecl Wad_hData(sint32 handle);
// <LegoRR.exe @0048c300>
char* __cdecl lwExtractString(char* str1, char* str2, uint32* out_pos, uint32* out_len);
// <LegoRR.exe @0048c380>
char* __cdecl stringAlloc(char* str);
// <LegoRR.exe @0048c3e0>
uint32 __cdecl texMapType(char* shapeName);
// <LegoRR.exe @0048c440>
void __cdecl surfFree(LWSURFACE* srf, bool32 flag);
// <LegoRR.exe @0048c490>
bool32 __cdecl LWD3D(uint8** p, real32* f);
// <LegoRR.exe @0048c4d0>
bool32 __cdecl PNTSprc(File* file, LWSIZE* sizeData, sint32 csize, real32** verts, bool32 dflag);
// <LegoRR.exe @0048c620>
bool32 __cdecl CRVSprc(File* file, sint32 csize, bool32 dflag);
// <LegoRR.exe @0048c6a0>
bool32 __cdecl POLSprc(File* file, LWSIZE* sizeData, LWPOLY** polys, sint32 csize, bool32 dflag);
// <LegoRR.exe @0048c950>
bool32 __cdecl SRFSprc(File* file, LWSIZE* sizeData, LWSURFLIST** srfl, sint32 csize, uint32* srflCount, bool32 dflag);
// <LegoRR.exe @0048cae0>
bool32 __cdecl SURFprc(File* file, LWSIZE* sizeData, LWSURFACE** surf, sint32 csize, bool32 dflag);
// <LegoRR.exe @0048d580>
bool32 __cdecl LoadLWOB(char* fn, LWSIZE* sd, real32** verts, LWPOLY** polys, LWSURFACE** surfs, File** out_fileUV, bool32 dflag);
// <LegoRR.exe @0048da80>
bool32 __cdecl LoadAppObj(char* fn, APPOBJ** out_ao, bool32 flag);
// <LegoRR.exe @0048db30>
bool32 __cdecl FreeLWOB(APPOBJ* ao);
// <LegoRR.exe @0048dc40>
float10 __cdecl atof(char* str);
// <LegoRR.exe @0048dca0>
sint32 __cdecl sprintf(char* out_buffer, char* format, ...);
// <LegoRR.exe @0048dd10>
char* __cdecl strstr(char* str, char* strSearch);
// <LegoRR.exe @0048de30>
sint32 __cdecl atoi(char* str);
// <LegoRR.exe @0048de40>
void __cdecl free(void* buffer);
// <LegoRR.exe @0048de90>
void* __cdecl malloc(uint32 size);
// <LegoRR.exe @0048df40>
void* __cdecl realloc(void* memblock, uint32 size);
// <LegoRR.exe @0048e0e0>
void __cdecl qsort(void* base, uint32 number, uint32 width, QsortCompare compare);
// <LegoRR.exe @0048e350>
float10 __cdecl acos(float10 x);
// <LegoRR.exe @0048e420>
void __cdecl srand(uint32 seed);
// <LegoRR.exe @0048e430>
sint32 __cdecl rand(void);
// <LegoRR.exe @0048e46a>
float10 __cdecl fmod(float10 x, float10 y);
// <LegoRR.exe @0048e4a0>
sint32 __cdecl vsprintf(char* buffer, char* format, va_list argptr);
// <LegoRR.exe @0048e510>
void* __stdcall _alloca4k(uint32 size);
// <LegoRR.exe @0048e540>
float10 __cdecl floor(double x);
// <LegoRR.exe @0048e640>
sint32 __cdecl toupper(sint32 c);
// <LegoRR.exe @0048e770>
void __cdecl exit(sint32 status);
// <LegoRR.exe @0048e790>
void __cdecl quick_exit(sint32 _Code);
// <LegoRR.exe @0048e894>
float10 __cdecl sqrt(double x);
// <LegoRR.exe @0048e940>
float10 __cdecl fabs(double x);
// <LegoRR.exe @0048ea30>
char* __cdecl strncpy(char* _Dest, char* _Source, uint32 _Count);
// <LegoRR.exe @0048eb30>
sint32 __cdecl _finite(double x);
// <LegoRR.exe @0048eb50>
void __cdecl sscanf(char* buffer, char* format, ...);
// <LegoRR.exe @0048eba0>
float10 __cdecl ceil(double x);
// <LegoRR.exe @0048ed90>
void* __cdecl operator_new(uint32 size);
// <LegoRR.exe @0048eda0>
sint32 __cdecl fclose(FILE* stream);
// <LegoRR.exe @0048ee20>
FILE* __cdecl _fsopen(LPCSTR filename, char* mode, sint32 shflag);
// <LegoRR.exe @0048ee50>
FILE* __cdecl fopen(LPCSTR filename, char* mode);
// <LegoRR.exe @0048f2c0>
void __cdecl entry(void);
// <LegoRR.exe @0048f490>
bool32 __cdecl _isctype(sint32 c, uint32 desc);
// <LegoRR.exe @0048f530>
sint32 __cdecl strncmp(char* _Str1, char* _Str2, uint32 _MaxCount);
// <LegoRR.exe @0048f570>
sint32 __cdecl ftell(FILE* stream);
// <LegoRR.exe @0048f720>
sint32 __cdecl fseek(FILE* stream, sint32 offset, sint32 origin);
// <LegoRR.exe @0048f7c0>
uint32 __cdecl fwrite(void* out_buffer, uint32 size, uint32 count, FILE* stream);
// <LegoRR.exe @0048f910>
sint32 __cdecl remove(LPCSTR filename);
// <LegoRR.exe @0048f940>
sint32 __cdecl _chmod(LPCSTR filename, sint32 pmode);
// <LegoRR.exe @0048f990>
sint32 __cdecl _mkdir(LPCSTR dirname);
// <LegoRR.exe @0048f9c0>
HANDLE __cdecl _findfirst32(LPCSTR filename, _finddata32_t* fileinfo);
// <LegoRR.exe @0048faf0>
sint32 __cdecl _findnext32(HANDLE handle, _finddata32_t* fileinfo);
// <LegoRR.exe @0048fc10>
sint32 __cdecl _findclose(HANDLE handle);
// <LegoRR.exe @0048fcc0>
char* __cdecl _getcwd(char* out_buffer, sint32 maxlen);
// <LegoRR.exe @0048fce0>
char* __cdecl _getdcwd(sint32 drive, char* out_buffer, sint32 maxlen);
// <LegoRR.exe @0048fe50>
uint32 __cdecl fread(void* out_buffer, uint32 size, uint32 count, FILE* stream);
// <LegoRR.exe @0048ffe0>
sint32 __cdecl fflush(FILE* stream);
// <LegoRR.exe @004900e0>
sint32 __cdecl fgetc(FILE* stream);
// <LegoRR.exe @00490110>
char* __cdecl fgets(char* str, sint32 numChars, FILE* stream);
// <LegoRR.exe @00490190>
sint32 __cdecl vfprintf(FILE* stream, char* format, va_list argptr);
// <LegoRR.exe @004901d0>
sint32 __cdecl _stricmp(char* _Str1, char* _Str2);
// <LegoRR.exe @00490260>
char* __cdecl _fullpath(char* out_absPath, LPCSTR relPath, uint32 maxLength);
// <LegoRR.exe @00490330>
sint32 __cdecl fscanf(FILE* stream, char* format, ...);
// <LegoRR.exe @00490350>
void __cdecl _splitpath(char* path, char* drive, char* dir, char* fname, char* ext);
// <LegoRR.exe @00493ea0>
uint32 __cdecl _status87(void);
// <LegoRR.exe @00493eb0>
uint32 __cdecl _clear87(void);
// <LegoRR.exe @00493ed0>
uint32 __cdecl _control87(uint32 new, uint32 mask);
// <LegoRR.exe @004941b0>
sint32 __cdecl vfscanf(FILE* stream, char* format, va_list argptr);
// <LegoRR.exe @00497890>
sint32 __cdecl tolower(sint32 c);
// <LegoRR.exe @004991c0>
sint32 __cdecl isspace(sint32 c);
// <LegoRR.exe @004999b0>
void __cdecl abort(void);
// <LegoRR.exe @0049b970>
HRESULT __stdcall Direct3DRMCreate(IUnknown** lplpIDirect3DRM);
// <LegoRR.exe @0049b976>
Vector3F* __stdcall D3DRMVectorRandom(Vector3F* d);
// <LegoRR.exe @0049b97c>
Vector3F* __stdcall D3DRMVectorRotate(Vector3F* r, Vector3F* v, Vector3F* axis, real32 theta);
// <LegoRR.exe @0049b982>
HRESULT __stdcall DirectDrawEnumerateA(DDENUMCALLBACKA* lpCallback, LPVOID lpContext);
// <LegoRR.exe @0049b988>
HRESULT __stdcall DirectDrawCreate(LPGUID lpGUID, IDirectDraw** lplpIDirectDraw, LPUNKNOWN pUnkOuter);
// <LegoRR.exe @0049b98e>
HRESULT __stdcall AVIStreamInfoA(IAVIStream* pIAVIStream, AVISTREAMINFOA* pAVIStreamInfoA, LONG lSize);
// <LegoRR.exe @0049b994>
IGetFrame* __stdcall AVIStreamGetFrameOpen(IAVIStream* pIAVIStream, BITMAPINFOHEADER* lpbiWanted);
// <LegoRR.exe @0049b99a>
HRESULT __stdcall AVIStreamOpenFromFileA(IAVIStream** lplpIAVIStream, LPCSTR szFile, DWORD fccType, LONG lParam, UINT mode, CLSID* pclsidHandler);
// <LegoRR.exe @0049b9a0>
ULONG __stdcall AVIStreamRelease(IAVIStream* pIAVIStream);
// <LegoRR.exe @0049b9a6>
LPVOID __stdcall AVIStreamGetFrame(IGetFrame* pIGetFrame, LONG lPos);
// <LegoRR.exe @0049b9ac>
void __stdcall AVIFileInit(void);
// <LegoRR.exe @0049ca68>
HRESULT __stdcall DirectInputCreateA(HINSTANCE hInst, DWORD dwVersion, IUnknown** lplpIDirectInput, IUnknown* pUnkOuter);
// <LegoRR.exe @0049ca6e>
HRESULT __stdcall DirectSoundCreate(LPGUID lpGuid, IDirectSound** lplpIDirectSound, IUnknown* pUnkOuter);
// <LegoRR.exe @0049ca74>
void __cdecl RtlUnwind(PVOID TargetFrame, PVOID TargetIp, PEXCEPTION_RECORD ExceptionRecord, PVOID ReturnValue);
// <LegoRR.exe @0049ca80>
uint32 __cdecl RNC_Uncompress(void* bufferIn, void** out_bufferOut);
// <LegoRR.exe @0049cb00>
RNCError __cdecl _RNC_Uncompress(RNC_HeaderInfo* bufferIn, uint8* bufferOut);
// <LegoRR.exe @0049cba0>
RNCError __cdecl RNC_M1_Uncompress(RNC_HeaderInfo* bufferIn, uint8* bufferOut);
// <LegoRR.exe @0049cd20>
RNCError __cdecl RNC_M2_Uncompress(RNC_HeaderInfo* bufferIn, uint8* bufferOut);
// <LegoRR.exe @0049cf30>
void __cdecl RNC_BitStreamInit(RNC_HeaderInfo* bufferIn, uint8* bufferOut);
// <LegoRR.exe @0049cf80>
uint32 __cdecl RNC_M1_BitStreamAdvance(uint8 bits);
// <LegoRR.exe @0049cff0>
uint32 __cdecl RNC_M2_BitStreamAdvance(uint8 bits);
// <LegoRR.exe @0049d050>
void __cdecl RNC_M1_ReadHuffmanTable(HuffmanLeaf* table, uint8 bits);
// <LegoRR.exe @0049d0c0>
uint16 __cdecl RNC_M1_ReadHuffman(HuffmanLeaf* table);
// <LegoRR.exe @0049d130>
uint16 __cdecl RNC_M2_ReadLengthCode(void);
// <LegoRR.exe @0049d170>
uint16 __cdecl RNC_M2_ReadOffsetCode(void);
// <LegoRR.exe @0049d210>
void __cdecl RNC_M1_HuffmanReset(HuffmanLeaf* table, uint8 bits);
// <LegoRR.exe @0049d250>
void __cdecl RNC_M1_HuffmanAssignValues(HuffmanLeaf* table, uint8 bits);
// <LegoRR.exe @0049d2c0>
uint32 __cdecl RNC_M1_MirrorBits(uint32 value, uint8 bits);
// <LegoRR.exe @0049d2f0>
bool32 __cdecl Init_Initialise(bool32 setup, bool32 debug, bool32 best, bool32 window, char* noHALMsg);
// <LegoRR.exe @0049d5b0>
INT_PTR __stdcall Init_DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
// <LegoRR.exe @0049d8a0>
void __cdecl Init_SetFullScreen(HWND hDlg, bool32 on);
// <LegoRR.exe @0049d8f0>
void __cdecl Init_SetModeList(HWND hDlg);
// <LegoRR.exe @0049da40>
void __cdecl Init_SetDeviceList(HWND hDlg);
// <LegoRR.exe @0049db30>
void __cdecl Init_AddValidMode(uint32 width, uint32 height, uint32 depth);
// <LegoRR.exe @0049db90>
bool32 __cdecl Init_IsValidMode(uint32 modeIndex);
// <LegoRR.exe @0049dc10>
bool32 __cdecl Init_GetMode(char* name, uint32* out_modeIndex);
// <LegoRR.exe @0049dc90>
void __cdecl Init_HandleWindowButton(HWND hDlg);
// <LegoRR.exe @0049dd70>
sint32 __cdecl _strnicmp(char* _Str1, char* _Str2, uint32 _MaxCount);
// <LegoRR.exe @0049de20>
char* __cdecl itoa(sint32 value, char* buffer, sint32 radix);
// <LegoRR.exe @0049ded0>
char* __cdecl _strlwr(char* str);
// <LegoRR.exe @0049df90>
char* __cdecl _strupr(char* str);
