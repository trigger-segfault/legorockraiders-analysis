#pragma once
#include "datatypes.h"
#include "functypes.h"

//00400000


// <LegoRR.exe @00401000>
void __cdecl Advisor_Initialise(char* gameName, LegoCamera* cameraMain, Viewport* viewMain);
// <LegoRR.exe @004011c0>
void __cdecl Advisor_Stop(void);
// <LegoRR.exe @00401210>
void __cdecl Advisor_InitViewport(real32 param_unused);
// <LegoRR.exe @00401240>
real32 __cdecl Maths_Vector2DDistance(Point2F* a, Point2F* b);
// <LegoRR.exe @00401270>
void __cdecl Advisor_LoadAnims(Config* config, char* gameName);
// <LegoRR.exe @004013a0>
bool32 __cdecl Advisor_GetAdvisorType(char* advisorName, Advisor_Type* out_advisorType);
// <LegoRR.exe @004013e0>
Vector3F* __cdecl Maths_Vector3DCrossProduct(Vector3F* out_vector, Vector3F* a, Vector3F* b);
// <LegoRR.exe @00401430>
bool32 __cdecl Advisor_GetAnimType(char* animName, Advisor_Anim* out_animType);
// <LegoRR.exe @00401470>
Vector3F* __cdecl Maths_Vector3DAdd(Vector3F* out_vector, Vector3F* a, Vector3F* b);
// <LegoRR.exe @004014a0>
void __cdecl Advisor_LoadPositions(Config* config, char* gameName, sint32 screenWidth, sint32 screenHeight);
// <LegoRR.exe @00401630>
Vector3F* __cdecl Maths_Vector3DSubtract(Vector3F* out_vector, Vector3F* a, Vector3F* b);
// <LegoRR.exe @00401660>
Vector3F* __cdecl Maths_Vector3DScale(Vector3F* out_vector, Vector3F* a, real32 scalar);
// <LegoRR.exe @00401690>
Vector3F* __cdecl Maths_Vector3DNormalize(Vector3F* ref_vector);
// <LegoRR.exe @004016f0>
void __cdecl Advisor_AddPosition(Advisor_Type advisorType, Advisor_Anim animType, Text_Type textType, SFX_ID sfxID, Panel_Type panelType, real32 x, real32 y);
// <LegoRR.exe @00401780>
void __cdecl Advisor_SetParameters(Advisor_Type advisorType, Panel_Type panelType, real32 x, real32 y);
// <LegoRR.exe @004017d0>
void __cdecl Advisor_GetOrigPos(Advisor_Type advisorType, real32* out_origX, real32* out_origY);
// <LegoRR.exe @00401800>
bool32 __cdecl Advisor_Start(Advisor_Type advisorType, bool32 loop);
// <LegoRR.exe @00401870>
void __cdecl Advisor_PlaySFX(Advisor_Type advisorType);
// <LegoRR.exe @004018d0>
void __cdecl Advisor_Update(real32 elapsed);
// <LegoRR.exe @004019b0>
bool32 __cdecl Advisor_MoveAnimation(Advisor_Anim animType, real32 elapsed);
// <LegoRR.exe @00401a60>
void __cdecl Advisor_End(void);
// <LegoRR.exe @00401a70>
void __cdecl Advisor_ViewportTransform(Advisor_Type advisorType);
// <LegoRR.exe @00401b30>
ProgrammerMode __cdecl Main_ProgrammerMode(void);
// <LegoRR.exe @00401b40>
char* __cdecl Main_GetStartLevel(void);
// <LegoRR.exe @00401b60>
bool32 __cdecl Advisor_IsAnimating(void);
// <LegoRR.exe @00401b70>
sint32 __cdecl appWidth(void);
// <LegoRR.exe @00401b80>
sint32 __cdecl appHeight(void);
// <LegoRR.exe @00401b90>
uint32 __cdecl Font_GetStringWidth(Font* font, char* msg, ...);
// <LegoRR.exe @00401bc0>
void __cdecl Font_GetStringInfo(Font* font, uint32* out_width, uint32* out_lineCount, char* msg, ...);
// <LegoRR.exe @00401bf0>
bool32 __cdecl AIPriority_GetType(char* aiPriorityName, AI_Priority* out_priorityType);
// <LegoRR.exe @00401c30>
void __cdecl AITask_Initialise(void);
// <LegoRR.exe @00401f40>
void __cdecl AITask_FUN_00401f40(AITask_Type taskType, LegoObject* liveObj, Point2I* opt_blockPos);
// <LegoRR.exe @00401fa0>
void __cdecl AITask_SetPriorityType(AITask* aiTask, AI_Priority priorityType);
// <LegoRR.exe @00401fd0>
void __cdecl AITask_Game_SetPriorityValue(AI_Priority priorityType, sint32 aiTaskValue);
// <LegoRR.exe @00401fe0>
void __cdecl AITask_Game_SetPriorityOff(AI_Priority priorityType, bool32 off);
// <LegoRR.exe @00401ff0>
bool32 __cdecl AITask_Game_IsPriorityOff(AI_Priority priorityType);
// <LegoRR.exe @00402000>
void __cdecl AITask_Shutdown(void);
// <LegoRR.exe @00402040>
void __cdecl AITask_CleanupLevel(bool32 end);
// <LegoRR.exe @004020b0>
void __cdecl AITask_Game_SetNoGather(bool32 noGather);
// <LegoRR.exe @00402120>
bool32 __cdecl AITask_Callback_Remove(AITask* aiTask);
// <LegoRR.exe @00402140>
void __cdecl free2(undefined* param_1);
// <LegoRR.exe @00402150>
void __cdecl AITask_UpdateAll(real32 elapsedGame);
// <LegoRR.exe @00402240>
void __cdecl AITask_FUN_00402240(AITask** ref_aiTask);
// <LegoRR.exe @00402440>
void __cdecl AITask_DoDig_AtBlockPos(Point2I* blockPos, bool32 param_2, bool32 param_3);
// <LegoRR.exe @00402530>
void __cdecl AITask_UnkInitRouting_FUN_00402530(AITask* aiTask, bool32 dropCarried);
// <LegoRR.exe @004025a0>
void __cdecl AITask_DoAttackRockMonster_Target(LegoObject* targetObj);
// <LegoRR.exe @004025f0>
void __cdecl AITask_LiveObject_FUN_004025f0(LegoObject* liveObj);
// <LegoRR.exe @00402630>
bool32 __cdecl AITask_IsCollectAndSameTarget(AITask* aiTask, LegoObject* liveObj);
// <LegoRR.exe @00402650>
void __cdecl AITask_DoCollect(LegoObject* liveObj, real32 param_2);
// <LegoRR.exe @004026d0>
void __cdecl AITask_DoBuildPath_AtPosition(Point2I* blockPos);
// <LegoRR.exe @00402730>
void __cdecl AITask_DoGather_Count(sint32 count);
// <LegoRR.exe @00402780>
void __cdecl AITask_DoCollect_Target(LegoObject* targetObj);
// <LegoRR.exe @004027c0>
void __cdecl AITask_DoTrain_Target(LegoObject* targetObj, LegoObject_AbilityFlags trainFlags, bool32 param_3);
// <LegoRR.exe @00402890>
void __cdecl AITask_DoFindDriver_Target(LegoObject* targetObj);
// <LegoRR.exe @00402970>
bool32 __cdecl AITask_RemoveAttackPathReferences(Point2I* blockPos);
// <LegoRR.exe @004029a0>
bool32 __cdecl AITask_Callback_RemoveAttackPathReference(AITask* aiTask, Point2I** pBlockPos);
// <LegoRR.exe @004029d0>
void __cdecl AITask_RemoveAttackRockMonsterReferences(LegoObject* targetObj);
// <LegoRR.exe @004029f0>
bool32 __cdecl AITask_Callback_RemoveAttackRockMonsterReference(AITask* aiTask, LegoObject* targetObj);
// <LegoRR.exe @00402a10>
void __cdecl AITask_RemoveDigReferences(Point2I* blockPos, bool32 digConnection);
// <LegoRR.exe @00402a60>
bool32 __cdecl AITask_RemoveReinforceReferences(Point2I* blockPos);
// <LegoRR.exe @00402a90>
bool32 __cdecl AITask_DelayOrRemoveClearReferences(Point2I* blockPos, bool32 delay);
// <LegoRR.exe @00402ae0>
bool32 __cdecl AITask_Callback_RemoveWallReference(AITask* aiTask, SearchAITaskDeselect_8* search);
// <LegoRR.exe @00402b50>
bool32 __cdecl AITask_Callback_RemoveReinforceReference(AITask* aiTask, Point2I** pBlockPos);
// <LegoRR.exe @00402ba0>
bool32 __cdecl AITask_Callback_RemoveClearReference(AITask* aiTask, Point2I** pBlockPos);
// <LegoRR.exe @00402bd0>
bool32 __cdecl AITask_Callback_DelayClearReference(AITask* aiTask, Point2I** pBlockPos);
// <LegoRR.exe @00402c00>
void __cdecl AITask_RemoveGetToolReferences(AITask* aiTask);
// <LegoRR.exe @00402c60>
bool32 __cdecl AITask_Callback_FindGetToolReference(AITask* aiTask, AITask* otherTask);
// <LegoRR.exe @00402c80>
bool32 __cdecl AITask_DoDynamite_AtBlockPos(Point2I* blockPos, bool32 noRoutingUnk);
// <LegoRR.exe @00402d70>
void __cdecl AITask_DoBirdScarer_AtPosition(Point2I* blockPos);
// <LegoRR.exe @00402df0>
void __cdecl AITask_DoFindLoad(LegoObject* targetObj);
// <LegoRR.exe @00402e60>
void __cdecl AITask_DoRepair_Target(LegoObject* targetObj, bool32 condition);
// <LegoRR.exe @00402ea0>
void __cdecl AITask_QueueGotoEat_Target(LegoObject* liveObj, LegoObject* targetObj);
// <LegoRR.exe @00402ee0>
void __cdecl AITask_DoElecFence(Point2I* blockPos);
// <LegoRR.exe @00402f60>
void __cdecl AITask_DoReinforce_AtBlockPos(Point2I* blockPos);
// <LegoRR.exe @00402fe0>
void __cdecl AITask_DoClear_AtPosition(Point2I* blockPos, Message_Type completeAction);
// <LegoRR.exe @00403010>
void __cdecl AITask_DoGetTool_FromTask(AITask* aiTask);
// <LegoRR.exe @004030c0>
bool32 __cdecl AITask_DoGetTool(LegoObject_ToolType toolType);
// <LegoRR.exe @00403110>
bool32 __cdecl AITask_Game_SelectedUnits_UnkEquippedTool_FUN_00403110(LegoObject_ToolType toolType);
// <LegoRR.exe @004031a0>
void __cdecl AITask_QueueGotoBlock_Group(LegoObject** unitList, uint32 unitCount, Point2I* blockPos, bool32 reevalTasks);
// <LegoRR.exe @00403250>
void __cdecl AITask_DoUpgrade(LegoObject* liveObj, uint32 newObjLevel);
// <LegoRR.exe @004032f0>
void __cdecl AITask_DoDock(LegoObject* liveObj);
// <LegoRR.exe @00403320>
void __cdecl AITask_DoGoto_Congregate(Point2I* blockPos);
// <LegoRR.exe @00403360>
void __cdecl AITask_StopGoto_Congregate(Point2I* blockPos);
// <LegoRR.exe @004033d0>
void __cdecl AITask_DoAttackObject(LegoObject* liveObj);
// <LegoRR.exe @00403410>
void __cdecl AITask_DoAttackPath(Point2I* blockPos);
// <LegoRR.exe @00403450>
void __cdecl AITask_DoRepair(LegoObject* liveObj);
// <LegoRR.exe @00403490>
void __cdecl AITask_LiveObject_FUN_00403490(LegoObject* liveObj);
// <LegoRR.exe @004034f0>
void __cdecl AITask_Game_PTL_GotoOrRMGoto(LegoObject* liveObj, Point2I* blockPos, undefined4 param_3);
// <LegoRR.exe @00403540>
void __cdecl AITask_QueueDepositInObject(LegoObject* liveObj, LegoObject* targetObj);
// <LegoRR.exe @00403580>
void __cdecl AITask_PushFollowObject_Group(LegoObject** unitList, uint32 unitCount, LegoObject* targetObj);
// <LegoRR.exe @004035f0>
void __cdecl AITask_Game_PTL_FollowAttack(LegoObject* liveObj, LegoObject* targetObj);
// <LegoRR.exe @00403630>
void __cdecl AITask_Construction_FUN_00403630(uint32 constructHandle, bool32 checkObjType, LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @00403680>
void __cdecl AITask_DoRequest_ObjectType(LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel, Point2I* blockPos, uint32 param_5, Point2F* pointFloat, bool32 param_7);
// <LegoRR.exe @00403740>
void __cdecl AITask_PlaceRequestObject(Point2I* blockPos, LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel);
// <LegoRR.exe @004037f0>
AITask* __cdecl AITask_DoDeposit_ObjectType(LegoObject* liveObj, LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel);
// <LegoRR.exe @00403840>
void __cdecl AITask_DoRequestObjectCallbacks(LegoObject* liveObj);
// <LegoRR.exe @004038d0>
void __cdecl AITask_LiveObject_FUN_004038d0(LegoObject* liveObj);
// <LegoRR.exe @00403900>
void __cdecl AITask_DoGotoEat(LegoObject* liveObj);
// <LegoRR.exe @00403940>
bool32 __cdecl AITask_LiveObject_FUN_00403940(LegoObject* liveObj);
// <LegoRR.exe @00403960>
bool32 __cdecl AITask_Callback_FUN_00403960(AITask* aiTask, LegoObject* liveObj);
// <LegoRR.exe @00403980>
void __cdecl AITask_RemoveTargetObjectReferences(LegoObject* targetObj);
// <LegoRR.exe @00403a00>
bool32 __cdecl AITask_Callback_RemoveTargetObjectReference(AITask* aiTask, LegoObject* targetObj);
// <LegoRR.exe @00403a20>
void __cdecl AITask_Route_End(LegoObject* liveObj, bool32 completed);
// <LegoRR.exe @00403a70>
void __cdecl AITask_LiveObject_FUN_00403a70(LegoObject* liveObj);
// <LegoRR.exe @00403a90>
void __cdecl AITask_VariousGatherTasks_FUN_00403a90(LegoObject* liveObj);
// <LegoRR.exe @00403b30>
void __cdecl AITask_LiveObject_FUN_00403b30(LegoObject* holderObj, AITask_Type taskType, LegoObject* carriedObj);
// <LegoRR.exe @00403c40>
void __cdecl AITask_LiveObject_SetAITaskUnk(LegoObject* liveObj, AITask_Type taskType, LegoObject* liveObj2, bool32 param_4);
// <LegoRR.exe @00403e20>
bool32 __cdecl AITask_RemoveCollectReferences(LegoObject* targetObj);
// <LegoRR.exe @00403e40>
bool32 __cdecl AITask_Callback_RemoveCollectReference(AITask* aiTask, LegoObject* targetObj);
// <LegoRR.exe @00403e60>
void __cdecl AITask_DoAnimationWait(LegoObject* liveObj);
// <LegoRR.exe @00403e90>
void __cdecl AITask_LiveObject_Unk_UpdateAITask_AnimationWait(LegoObject* liveObj);
// <LegoRR.exe @00403eb0>
sint32 __cdecl AITask_QSortCompare(AITask** task_a, AITask** task_b);
// <LegoRR.exe @00403f60>
AITask* __cdecl AITask_InitTask_1(AITask* aiTask, AI_Priority priorityType);
// <LegoRR.exe @00403fa0>
void __cdecl AITask_Init_2_NoPriority(AITask* aiTask);
// <LegoRR.exe @00403fd0>
void __cdecl AITask_Game_UnkLiveObjectHandleDynamite(LegoObject* liveObj);
// <LegoRR.exe @00404030>
void __cdecl AITask_ReevaluateObjectTasks(LegoObject* liveObj);
// <LegoRR.exe @004040c0>
AITask* __cdecl AITask_GetObjectTaskListTail(LegoObject* liveObj);
// <LegoRR.exe @004040e0>
bool32 __cdecl AITask_LiveObject_IsCurrentTaskType(LegoObject* liveObj, AITask_Type taskType);
// <LegoRR.exe @00404110>
void __cdecl AITask_LiveObject_FUN_00404110(LegoObject* liveObj);
// <LegoRR.exe @00404180>
bool32 __cdecl AITask_Callback_UpdateTask(AITask* aiTask, real32* pElapsedGame);
// <LegoRR.exe @004041b0>
bool32 __cdecl AITask_Callback_UpdateObject(LegoObject* liveObj, real32* pElapsedGame);
// <LegoRR.exe @00404d30>
bool32 __cdecl AITask_LiveObject_FUN_00404d30(LegoObject* in_liveObj, Point2I* blockPos2, real32* param_3);
// <LegoRR.exe @00404e00>
bool32 __cdecl AITask_LiveObject_FUN_00404e00(LegoObject* liveObj);
// <LegoRR.exe @00404e40>
bool32 __cdecl AITask_FUN_00404e40(LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel);
// <LegoRR.exe @00404e80>
bool32 __cdecl AITask_Callback_FUN_00404e80(AITask* aiTask, sint32* param_2);
// <LegoRR.exe @00404ef0>
bool32 __cdecl AITask_FUN_00404ef0(AITask* aiTask, LegoObject* liveObj_2, real32* param_3, real32* param_4, undefined4* param_5, sint32 param_6, sint32 param_7);
// <LegoRR.exe @00405880>
void __cdecl AITask_FUN_00405880(void);
// <LegoRR.exe @00405b40>
void __cdecl AITask_FUN_00405b40(void);
// <LegoRR.exe @00406290>
void __cdecl AITask_FUN_00406290(AITask* aiTask1, AITask* aiTask2, LegoObject* liveObj);
// <LegoRR.exe @00406310>
void __cdecl AITask_RemoveObject48References(LegoObject* obj48);
// <LegoRR.exe @00406330>
AITask* __cdecl AITask_Clone(AITask* aiTask);
// <LegoRR.exe @00406370>
AITask* __cdecl AITask_Create(AITask_Type taskType);
// <LegoRR.exe @004063b0>
void __cdecl AITask_Remove(AITask* aiTask, bool32 levelCleanup);
// <LegoRR.exe @004063f0>
void __cdecl AITask_AddList(void);
// <LegoRR.exe @00406470>
bool32 __cdecl AITask_RunThroughLists(AITask_RunThroughListsCallback callback, void* data);
// <LegoRR.exe @00406500>
IDirectDraw4* __cdecl DirectDraw(void);
// <LegoRR.exe @00406510>
IDirectDrawSurface4* __cdecl DirectDraw_bSurf(void);
// <LegoRR.exe @00406520>
void __cdecl BezierCurve_Curve(Point2F* out_r, Point2F* p0, Point2F* p1, Point2F* p2, Point2F* p3, real32 t);
// <LegoRR.exe @00406660>
real32 __cdecl BezierCurve_Vector2DDistance(Point2F* a, Point2F* b);
// <LegoRR.exe @00406690>
Point2F* __cdecl BezierCurve_Vector2DChangeLength(Point2F* ref_r, real32 newLength);
// <LegoRR.exe @004066e0>
real32 __cdecl BezierCurve_UpdateDistances(BezierCurve* curve);
// <LegoRR.exe @00406750>
void __cdecl BezierCurve_BuildPoints(BezierCurve* curve, Point2F* p0, Point2F* p1, Point2F* p2, Point2F* p3, uint32 count);
// <LegoRR.exe @004067f0>
uint32 __cdecl BezierCurve_Interpolate(BezierCurve* curve, real32 currentDist, Point2F* out_r);
// <LegoRR.exe @004068b0>
bool32 __cdecl Creature_IsCameraFlipDir(CreatureModel* creature);
// <LegoRR.exe @004068c0>
bool32 __cdecl Creature_Load(CreatureModel* creature, LegoObject_ID objID, Container* root, char* filename, char* gameName);
// <LegoRR.exe @00406b30>
void __cdecl Creature_SwapPolyMedium(CreatureModel* creature, bool32 swap);
// <LegoRR.exe @00406b60>
void __cdecl Creature_SwapPolyHigh(CreatureModel* creature, bool32 swap);
// <LegoRR.exe @00406b90>
void __cdecl Creature_SwapPolyFP(CreatureModel* creature, bool32 swap, uint32 cameraNo);
// <LegoRR.exe @00406bc0>
void __cdecl Object_Hide(BasicObjectModel* basicObjData, bool32 hide);
// <LegoRR.exe @00406be0>
void __cdecl Creature_Clone(CreatureModel* srcCreature, CreatureModel* destCreature);
// <LegoRR.exe @00406c40>
void __cdecl Creature_SetAnimationTime(CreatureModel* creature, real32 time);
// <LegoRR.exe @00406c60>
real32 __cdecl Creature_MoveAnimation(CreatureModel* creature, real32 elapsed, uint32 unkFrameNo);
// <LegoRR.exe @00406cd0>
real32 __cdecl Creature_GetAnimationTime(CreatureModel* creature);
// <LegoRR.exe @00406cf0>
void __cdecl Creature_SetOrientation(CreatureModel* creature, real32 xDir, real32 yDir);
// <LegoRR.exe @00406d20>
void __cdecl Creature_SetPosition(CreatureModel* creature, real32 xPos, real32 yPos, GetWorldZCallback zCallback, Map3D* map);
// <LegoRR.exe @00406d60>
Container* __cdecl Object_GetActivityContainer(BasicObjectModel* basicObjData);
// <LegoRR.exe @00406d70>
bool32 __cdecl Creature_SetActivity(CreatureModel* creature, char* activityName, real32 elapsed);
// <LegoRR.exe @00406df0>
void __cdecl Creature_Remove(CreatureModel* creature);
// <LegoRR.exe @00406e80>
Container* __cdecl Object_SearchForPartName(BasicObjectModel* basicObjData, char* name, uint32 frameNo);
// <LegoRR.exe @00406eb0>
Container* __cdecl Creature_GetCameraNull(CreatureModel* creature, sint32 cameraIndex);
// <LegoRR.exe @00406ee0>
Container* __cdecl Creature_GetDrillNull(CreatureModel* creature);
// <LegoRR.exe @00406f10>
Container* __cdecl Creature_GetCarryNull(CreatureModel* creature);
// <LegoRR.exe @00406f40>
Container* __cdecl Creature_GetDepositNull(CreatureModel* creature);
// <LegoRR.exe @00406f70>
bool32 __cdecl Creature_GetThrowNull(CreatureModel* creature);
// <LegoRR.exe @00406fc0>
real32 __cdecl Creature_GetTransCoef(CreatureModel* creature);
// <LegoRR.exe @00406fe0>
void __cdecl Bubble_Initialise(void);
// <LegoRR.exe @00407170>
void __cdecl Bubble_LoadBubbles(Config* config);
// <LegoRR.exe @00407230>
Bubble_Type __cdecl Bubble_GetBubbleType(char* bubbleName);
// <LegoRR.exe @00407270>
void __cdecl Bubble_ToggleObjectUIsAlwaysVisible(void);
// <LegoRR.exe @00407290>
bool32 __cdecl Bubble_GetObjectUIsAlwaysVisible(void);
// <LegoRR.exe @004072a0>
void __cdecl Bubble_LiveObject_UpdateBubbleImage(LegoObject* liveObj);
// <LegoRR.exe @004072d0>
void __cdecl Bubble_RemoveObjectReferences(LegoObject* liveObj);
// <LegoRR.exe @00407340>
void __cdecl Bubble_LiveObject_FUN_00407340(LegoObject* liveObj);
// <LegoRR.exe @00407380>
void __cdecl Bubble_LiveObject_MiniFigure_FUN_00407380(LegoObject* liveObj);
// <LegoRR.exe @004073e0>
void __cdecl Bubble_LiveObject_MiniFIgure_FUN_004073e0(LegoObject* liveObj);
// <LegoRR.exe @00407440>
void __cdecl Bubble_LiveObject_MiniFigure_FUN_00407440(LegoObject* liveObj, real32 param_2);
// <LegoRR.exe @00407470>
void __cdecl Bubble_LiveObject_FUN_00407470(LegoObject* liveObj);
// <LegoRR.exe @004074d0>
void __cdecl Bubble_Unk_DrawObjectUIs_FUN_004074d0(real32 elapsedAbs);
// <LegoRR.exe @004077f0>
void __cdecl Bubble_LiveObject_GetBubbleImage_FUN_004077f0(LegoObject* liveObj, real32 elapsedAbs, Image** out_bubbleImage, Point2F* out_screenPt);
// <LegoRR.exe @00407890>
bool32 __cdecl Bubble_LiveObject_CallbackDraw_FUN_00407890(LegoObject* liveObj, real32* pElapsedAbs);
// <LegoRR.exe @00407940>
void __cdecl Bubble_LiveObject_GetCurrentBubbleImage(LegoObject* liveObj, Image** out_bubbleImage);
// <LegoRR.exe @00407c90>
bool32 __cdecl Building_Load(BuildingModel* building, LegoObject_ID objID, Container* root, char* filename, char* gameName);
// <LegoRR.exe @00408210>
void __cdecl Building_AnimatePowerLevelScene(BuildingModel* building, bool32 forward);
// <LegoRR.exe @00408290>
Point2I* __cdecl Building_GetShapePoints(BuildingModel* building, uint32* optout_shapeCount);
// <LegoRR.exe @004082b0>
void __cdecl Object_SetOwnerObject(BasicObjectModel* basicObjData, LegoObject* liveObj);
// <LegoRR.exe @004082d0>
void __cdecl Building_SetUpgradeActivity(BuildingModel* building, char* activityName);
// <LegoRR.exe @004084a0>
bool32 __cdecl Building_SetActivity(BuildingModel* building, char* activityName, real32 elapsed);
// <LegoRR.exe @00408520>
Container* __cdecl Building_GetCameraNull(BuildingModel* building, uint32 frameNo);
// <LegoRR.exe @00408550>
void __cdecl Building_Clone(BuildingModel* srcBuilding, BuildingModel* destBuilding);
// <LegoRR.exe @004085a0>
void __cdecl Building_Hide(BuildingModel* building, bool32 hide);
// <LegoRR.exe @004085d0>
bool32 __cdecl Object_IsHidden(BasicObjectModel* basicObjData);
// <LegoRR.exe @004085f0>
void __cdecl Building_SetOrientation(BuildingModel* building, real32 xDir, real32 yDir);
// <LegoRR.exe @00408640>
void __cdecl Building_SetPosition(BuildingModel* building, real32 xPos, real32 yPos, GetWorldZCallback zCallback, Map3D* map);
// <LegoRR.exe @004086a0>
Container* __cdecl Building_GetCarryNull(BuildingModel* building, uint32 frameNo);
// <LegoRR.exe @004086e0>
Container* __cdecl Building_GetDepositNull(BuildingModel* building);
// <LegoRR.exe @00408710>
Container* __cdecl Building_GetEntranceNull(BuildingModel* building);
// <LegoRR.exe @00408740>
Container* __cdecl Building_GetToolNull(BuildingModel* building, uint32 frameNo);
// <LegoRR.exe @00408780>
uint32 __cdecl Building_GetCarryNullFrames(BuildingModel* building);
// <LegoRR.exe @00408790>
real32 __cdecl Building_MoveAnimation(BuildingModel* building, real32 elapsed, uint32 unkFrameNo);
// <LegoRR.exe @00408860>
real32 __cdecl Building_GetTransCoef(BuildingModel* building);
// <LegoRR.exe @00408870>
void __cdecl Building_Remove(BuildingModel* building);
// <LegoRR.exe @004088a0>
bool32 __cdecl Building_CanUpgradeType(BuildingModel* building, LegoObject_UpgradeType upgradeType, bool32 current);
// <LegoRR.exe @004088d0>
void __cdecl Building_SetUpgradeLevel(BuildingModel* building, uint32 objLevel);
// <LegoRR.exe @00408900>
real32 __cdecl Collision_Maths_Sub_FUN_00408900(Point2F* param_1, Point2F* param_2, Point2F* param_3);
// <LegoRR.exe @00408a30>
real32 __cdecl Collision_Maths_FUN_00408a30(Point2F* point, Point2F* fromList, Point2F* toList, uint32 count);
// <LegoRR.exe @00408a90>
Point2F* __cdecl Collision_Maths_FUN_00408a90(Point2F* param_1, Point2F* param_2, Point2F* position, Point2F* result);
// <LegoRR.exe @00408b20>
Point2F* __cdecl Collision_MathUnk_Vector2D_FUN_00408b20(Point2F* param_1, Point2F* param_2, Point2F* position, Point2F* result);
// <LegoRR.exe @00408bb0>
uint32 __cdecl Construction_GetBuildingBase(char* baseName);
// <LegoRR.exe @00408c10>
void __cdecl Construction_Zone_PlaceResource(uint32 constructHandle, LegoObject* placedObj);
// <LegoRR.exe @00408ca0>
bool32 __cdecl Construction_Zone_NeedsMoreOfResource(uint32 constructHandle, LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @00408d40>
uint32 __cdecl Construction_Zone_CountOfResourcePlaced(Construction_Zone* construct, LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @00408d80>
void __cdecl Construction_Zone_RequestResource(Point2I* originBlockPos, LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel, uint32 count);
// <LegoRR.exe @00408df0>
void __cdecl Construction_Zone_RequestBarriers(Point2I* originBlockPos, Point2I* shapeBlocks, uint32 shapeCount);
// <LegoRR.exe @00408fd0>
bool32 __cdecl Construction_Zone_ExistsAtBlock(Point2I* originBlockPos);
// <LegoRR.exe @00408ff0>
Construction_Zone* __cdecl Construction_Zone_FindByHandleOrAtBlock(Point2I* optor_originBlockPos, uint32* optor_constructHandle);
// <LegoRR.exe @00409040>
void __cdecl Construction_Zone_CompletePath(Point2I* originBlockPos);
// <LegoRR.exe @00409080>
void __cdecl Construction_Zone_CancelPath(Point2I* originBlockPos);
// <LegoRR.exe @00409110>
void __cdecl Construction_UpdateAll(real32 elapsedGame);
// <LegoRR.exe @004091a0>
bool32 __cdecl Construction_Zone_NoForeignObjectsInside(Construction_Zone* construction);
// <LegoRR.exe @004091c0>
bool32 __cdecl Construction_Zone_ObjectCallback_IsForeignObjectInside(LegoObject* liveObj, Construction_Zone* data);
// <LegoRR.exe @00409230>
bool32 __cdecl Construction_Zone_StartPath(Point2I* originBlockPos);
// <LegoRR.exe @00409280>
Construction_Zone* __cdecl Construction_Zone_Create(Point2I* originBlockPos);
// <LegoRR.exe @004092e0>
void __cdecl Construction_PowerGrid_PowerAdjacentBlocks(Point2I* blockPos);
// <LegoRR.exe @00409380>
bool32 __cdecl Construction_PowerGrid_DrainAdjacentBlocks(Point2I* blockPos, sint32 crystalDrainedAmount);
// <LegoRR.exe @004093a0>
bool32 __cdecl Construction_PowerGrid_DrainAdjacentBlocks_Recurse(Point2I* blockPos, sint32 crystalDrainedAmount);
// <LegoRR.exe @00409480>
void __cdecl Construction_Zone_RequestPathResources(Construction_Zone* construct);
// <LegoRR.exe @00409530>
void __cdecl Construction_Zone_CancelBuilding(Point2I* originBlockPos);
// <LegoRR.exe @004096c0>
uint32 __cdecl Construction_Zone_StartBuilding(LegoObject_ID buildingObjID, Point2I* originBlockPos, Direction direction, Point2I* shapeBlocks, uint32 count);
// <LegoRR.exe @00409870>
void __cdecl Construction_FlattenGround(Point2I* blockPos);
// <LegoRR.exe @00409900>
void __cdecl Construction_RemoveAll(void);
// <LegoRR.exe @00409920>
void __cdecl Construction_Zone_Free(Construction_Zone* construct);
// <LegoRR.exe @00409970>
void __cdecl Construction_Zone_ConsumePlacedResources(Construction_Zone* construct);
// <LegoRR.exe @004099c0>
LegoObject* __cdecl Construction_SpawnBuilding(LegoObject_ID objID, Point2I* originBlockPos, Direction direction, Point2I* shapeBlocks, uint32 shapeCount, bool32 teleportDown);
// <LegoRR.exe @00409a60>
LegoObject* __cdecl Construction_Zone_CompleteBuilding(Construction_Zone* construct, bool32 teleportDown);
// <LegoRR.exe @00409c00>
void __cdecl Construction_DeselectAdjacentDig(Point2I* blockPos);
// <LegoRR.exe @00409c70>
void __cdecl Construction_DisableCryOreDrop(bool32 disabled);
// <LegoRR.exe @00409c80>
void __cdecl Construction_CleanupBuildingFoundation(LegoObject* liveObj);
// <LegoRR.exe @00409e50>
void __cdecl Construction_GenerateCryOreDrop(LegoObject* liveObj);
// <LegoRR.exe @00409f20>
void __cdecl Construction_RemoveBuildingObject(LegoObject* liveObj);
// <LegoRR.exe @00409ff0>
void __cdecl Credits_Play(char* textFile, Font* font, char* aviFile);
// <LegoRR.exe @0040a300>
void __cdecl DamageFont_Cleanup(void);
// <LegoRR.exe @0040a330>
void __cdecl DamageFont_LoadFrames(char* dirName, char* fileBaseName);
// <LegoRR.exe @0040a3e0>
void __cdecl DamageFont_DisplayDamage_OverLiveObject(LegoObject* liveObj, uint32 displayNumber);
// <LegoRR.exe @0040a4f0>
DamageFontData* __cdecl DamageFont_GetNextFree(void);
// <LegoRR.exe @0040a510>
void __cdecl DamageFont_SetDisplayNumber(DamageFontData* healthFont, uint32 displayNumber);
// <LegoRR.exe @0040a670>
void __cdecl DamageFont_MeshRenderCallback(Mesh* mesh, DamageFontData* healthFont, Viewport* view);
// <LegoRR.exe @0040a940>
void __cdecl DamageFont_UpdateAll(real32 elapsedAbs);
// <LegoRR.exe @0040a970>
void __cdecl DamageFont_UpdateSingle(DamageFontData* healthFont, real32 elapsedAbs);
// <LegoRR.exe @0040aa10>
bool32 __cdecl DamageFont_LiveObject_CheckCanShowDamage_Unk(LegoObject* liveObj);
// <LegoRR.exe @0040aa40>
void __cdecl Dependencies_SetEnabled(bool32 on);
// <LegoRR.exe @0040aa60>
void __cdecl Dependencies_Reset_ClearAllLevelFlags_10c(void);
// <LegoRR.exe @0040aaa0>
void __cdecl Dependencies_Initialise(Config* config, char* gameName);
// <LegoRR.exe @0040add0>
bool32 __cdecl Dependencies_Object_FUN_0040add0(LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel);
// <LegoRR.exe @0040ae70>
bool32 __cdecl Dependencies_LiveObject_CallbackCheck_FUN_0040ae70(LegoObject* liveObj, LegoObject* otherObj);
// <LegoRR.exe @0040aec0>
void __cdecl Dependencies_Object_GetRequirements(LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel, DependencyRequirement** out_requirements, uint32* out_count);
// <LegoRR.exe @0040af30>
void __cdecl Dependencies_Object_Unlock(LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel, DependencyUnlocks* unlocks);
// <LegoRR.exe @0040b0e0>
void __cdecl Dependencies_Prepare_Unk(void);
// <LegoRR.exe @0040b180>
bool32 __cdecl Dependencies_Object_IsLevelFlag4(LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel);
// <LegoRR.exe @0040b1d0>
void __cdecl Dependencies_Object_AddLevelFlag_100(LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel);
// <LegoRR.exe @0040b210>
bool32 __cdecl Dependencies_Object_GetLevelFlag_100(LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel);
// <LegoRR.exe @0040b240>
Detail_TextureSet* __cdecl Detail_LoadTextureSet(char* textureBaseName, uint32 width, uint32 height);
// <LegoRR.exe @0040b340>
void __cdecl Detail_FreeTextureSet(Detail_TextureSet* textureSet);
// <LegoRR.exe @0040b3a0>
real32 __cdecl Detail_FUN_0040b3a0(Vector3F* vertPoses, Viewport* view, Point2F* viewportSize, bool32 param_4);
// <LegoRR.exe @0040b520>
Detail_Mesh* __cdecl Detail_LoadMeshes(Container* cont, char* meshName_a, char* meshName_b, real32 blockSize, Detail_TextureSet* textureSet);
// <LegoRR.exe @0040b700>
void __cdecl Detail_FreeMesh(Detail_Mesh* detailMesh);
// <LegoRR.exe @0040b740>
void __cdecl Detail_RemoveMesh_FUN_0040b740(Detail_Mesh* detailMesh);
// <LegoRR.exe @0040b780>
Container_Texture* __cdecl Detail_GetTexture(Detail_TextureSet* textureSet, SurfaceTexture coord_4X_0Y);
// <LegoRR.exe @0040b7b0>
void __cdecl Detail_FUN_0040b7b0(Detail_Mesh* detailMesh, Vector3F* vectPoses4, SurfaceTexture texture, uint8 direction, real32 scaleZ, real32 brightness);
// <LegoRR.exe @0040b930>
void __cdecl Detail_Sub1_Transform(Container* cont, real32 blockSize, Vector3F* p1, Vector3F* p2, Vector3F* p3, real32 scaleZ, real32 brightness, Container_Texture* contTexture, Detail_TransformFlags transformFlags);
// <LegoRR.exe @0040bac0>
void __cdecl Detail_Sub2_FUN_0040bac0(Container* cont, real32 blockSize, Vector3F* p1, Vector3F* p2, Vector3F* p3);
// <LegoRR.exe @0040bc90>
void __cdecl Detail_Matrix_FUN_0040bc90(Matrix4F* out_m, real32 blockWidth, real32 blockHeight, real32 invxP2_y, real32 invxP3_x, real32 invxP3_y);
// <LegoRR.exe @0040bcf0>
void __cdecl Effect_StopAll(void);
// <LegoRR.exe @0040bd10>
void __cdecl Effect_Spawn_BoulderExplode_AtObjectOther(LegoObject* liveObj);
// <LegoRR.exe @0040bd40>
void __cdecl Effect_Spawn_BoulderExplode(Vector3F* position);
// <LegoRR.exe @0040bde0>
void __cdecl Effect_Spawn_SmashPath(LegoObject* optor_liveObj, Vector3F* optor_position);
// <LegoRR.exe @0040bea0>
bool32 __cdecl Effect_GetRockFallStyle(char* name, uint32* out_index);
// <LegoRR.exe @0040bef0>
void __cdecl Effect_SetRockFallStyle(sint32 rockFallStyleIndex);
// <LegoRR.exe @0040bf00>
void __cdecl Effect_Load_RockFallStylesAll(Config* config, char* gameName, Container* root);
// <LegoRR.exe @0040c000>
bool32 __cdecl Effect_Load_RockFallStyle(Container* root, char* filename, sint32 rockFallStyle, sint32 rockFallType, char* itemName);
// <LegoRR.exe @0040c0e0>
bool32 __cdecl Effect_Load_ElectricFenceBeam(Container* root, char* filename, bool32 longBeam);
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
void __cdecl Effect_Load_Explosion(Container* root, char* filename);
// <LegoRR.exe @0040c680>
void __cdecl Effect_Spawn_Explosion(LegoObject* optor_liveObj, Point2F* optor_position);
// <LegoRR.exe @0040c760>
void __cdecl Effect_Update_Explosion(real32 elapsedGame);
// <LegoRR.exe @0040c7d0>
EffectMisc* __cdecl Effect_GetMiscEffectData(MiscEffectType miscEffectType);
// <LegoRR.exe @0040c850>
bool32 __cdecl Effect_Load_Misc(EffectMisc* effectMisc, Container* root, char* filename);
// <LegoRR.exe @0040c8c0>
void __cdecl Effect_Initialise(Config* config, char* gameName, Container* root);
// <LegoRR.exe @0040caa0>
void __cdecl Effect_Update_MiscEffect(EffectMisc* miscEffect, real32 elapsedGame);
// <LegoRR.exe @0040cb70>
void __cdecl Effect_Update_MiscEffectsAll(real32 elapsedGame);
// <LegoRR.exe @0040cc10>
bool32 __cdecl Effect_Spawn_Particle(MiscEffectType miscEffectType, Vector3F* position, Vector3F* opt_dir);
// <LegoRR.exe @0040ccf0>
void __cdecl ElectricFence_Initialise(Lego_Level* level);
// <LegoRR.exe @0040cd60>
void __cdecl ElectricFence_Shutdown(void);
// <LegoRR.exe @0040cdb0>
void __cdecl ElectricFence_Restart(Lego_Level* level);
// <LegoRR.exe @0040cdd0>
void __cdecl ElectricFence_UpdateBlockConnections(sint32 bx, sint32 by);
// <LegoRR.exe @0040ce80>
ElectricFence_Block* __cdecl ElectricFence_CreateFence(LegoObject* liveObj);
// <LegoRR.exe @0040ceb0>
ElectricFence_Block* __cdecl ElectricFence_Create(LegoObject* liveObj, sint32 bx, sint32 by);
// <LegoRR.exe @0040cf60>
void __cdecl ElectricFence_AddList(void);
// <LegoRR.exe @0040cfd0>
void __cdecl ElectricFence_RemoveFence(LegoObject* liveObj);
// <LegoRR.exe @0040d030>
void __cdecl ElectricFence_Remove(ElectricFence_Block* efence, sint32 bx, sint32 by);
// <LegoRR.exe @0040d0a0>
bool32 __cdecl ElectricFence_Debug_PlaceFence(sint32 bx, sint32 by);
// <LegoRR.exe @0040d120>
bool32 __cdecl ElectricFence_Debug_RemoveFence(sint32 bx, sint32 by);
// <LegoRR.exe @0040d170>
bool32 __cdecl ElectricFence_CanPlaceFenceAtBlock(sint32 bx, sint32 by);
// <LegoRR.exe @0040d320>
bool32 __cdecl ElectricFence_CheckBuildingAtBlock(Lego_Level* level, sint32 bx, sint32 by, bool32 checkPowered);
// <LegoRR.exe @0040d380>
void __cdecl ElectricFence_UpdateAll(real32 elapsedGame);
// <LegoRR.exe @0040d3c0>
void __cdecl ElectricFence_RunThroughLists(ElectricFence_RunThroughListsCallback callback, void* data);
// <LegoRR.exe @0040d420>
bool32 __cdecl ElectricFence_FUN_0040d420(LegoObject* liveObj, uint32 bx, uint32 by);
// <LegoRR.exe @0040d510>
bool32 __cdecl ElectricFence_Callback_FUN_0040d510(LegoObject* liveObj, real32* pElapsedGame);
// <LegoRR.exe @0040d650>
bool32 __cdecl ElectricFence_LiveObject_Callback_FUN_0040d650(LegoObject* liveObj, void* data);
// <LegoRR.exe @0040d6a0>
void __cdecl ElectricFence_CallbackUpdate(ElectricFence_Block* efence, real32* pElapsedGame);
// <LegoRR.exe @0040d780>
void __cdecl ElectricFence_Block_FUN_0040d780(uint32 bx, uint32 by, bool32 param_3, real32 param_4);
// <LegoRR.exe @0040db50>
bool32 __cdecl ElectricFence_Block_UnkAreaDistanceBetweenBlocks(uint32 bxFrom, uint32 byFrom, uint32 bxTo, uint32 byTo);
// <LegoRR.exe @0040dcc0>
Vector3F* __cdecl ElectricFence_Block_GetDistanceBetweenBlocks(uint32 bxFrom, uint32 byFrom, uint32 bxTo, uint32 byTo, Vector3F* out_vector);
// <LegoRR.exe @0040dd70>
bool32 __cdecl ElectricFence_LiveObject_FUN_0040dd70(LegoObject* liveObj);
// <LegoRR.exe @0040dff0>
void __cdecl ElectricFence_LiveObject_SparkBlock_FUN_0040dff0(LegoObject* liveObj, Point2F* objWorldPos, uint32 bx, uint32 by);
// <LegoRR.exe @0040e110>
bool32 __cdecl ElectricFence_Block_FUN_0040e110(Lego_Level* level, uint32 bx, uint32 by);
// <LegoRR.exe @0040e280>
void __cdecl ElectricFence_Block_ElecFenceStud_FUN_0040e280(Lego_Level* level, uint32 bx, uint32 by, bool32 addNew);
// <LegoRR.exe @0040e390>
bool32 __cdecl ElectricFence_Block_IsFence(sint32 bx, sint32 by);
// <LegoRR.exe @0040e3c0>
void __cdecl Encyclopedia_Initialise(Config* config, char* gameName);
// <LegoRR.exe @0040e630>
void __cdecl Encyclopedia_SetObject(LegoObject* liveObj);
// <LegoRR.exe @0040e710>
void __cdecl Encyclopedia_UnsetFlag1(void);
// <LegoRR.exe @0040e720>
void __cdecl Encyclopedia_Update(real32 elapsedAbs);
// <LegoRR.exe @0040e800>
void __cdecl Encyclopedia_DrawSelectBox(Viewport* viewMain);
// <LegoRR.exe @0040e840>
void __cdecl Encyclopedia_RemoveCurrentReference(LegoObject* liveObj);
// <LegoRR.exe @0040e860>
void __cdecl Erode_Initialise(real32 triggerTime, real32 erodeTime, real32 lockTime);
// <LegoRR.exe @0040e8c0>
bool32 __cdecl Erode_GetFreeActiveIndex(sint32* out_index);
// <LegoRR.exe @0040e8f0>
real32 __cdecl Erode_GetBlockErodeRate(Point2I* blockPos);
// <LegoRR.exe @0040e940>
void __cdecl Erode_AddActiveBlock(Point2I* blockPos, sint32 unkModulusNum);
// <LegoRR.exe @0040e9e0>
void __cdecl Erode_Update(real32 elapsedGame);
// <LegoRR.exe @0040ed30>
void __cdecl Erode_AddLockedBlock(Point2I* blockPos);
// <LegoRR.exe @0040ed80>
void __cdecl Erode_Block_FUN_0040ed80(Point2I* blockPos, bool32 doState2_else_add3);
// <LegoRR.exe @0040eee0>
bool32 __cdecl Erode_IsBlockLocked(Point2I* blockPos);
// <LegoRR.exe @0040ef30>
bool32 __cdecl Erode_FindAdjacentBlockPos(Point2I* blockPos, Point2I* out_adjacentblockPos);
// <LegoRR.exe @0040f010>
void __cdecl Fallin_Update(real32 elapsedGame);
// <LegoRR.exe @0040f0c0>
bool32 __cdecl Fallin_Block_FUN_0040f0c0(Point2I* blockPos, bool32 allowCaveIn);
// <LegoRR.exe @0040f1e0>
bool32 __cdecl Fallin_Block_UpdateFallinsUnk1(Point2I* blockPos);
// <LegoRR.exe @0040f260>
void __cdecl Fallin_Block_FUN_0040f260(Point2I* blockPos, DirectionFlags fallinDirs, bool32 allowCaveIn);
// <LegoRR.exe @0040f510>
void __cdecl Fallin_Initialise(sint32 numLandSlidesTillCaveIn);
// <LegoRR.exe @0040f520>
void __cdecl Fallin_LandSlideDoCaveIn(Point2I* blockPos, DirectionFlags fallinDirs);
// <LegoRR.exe @0040f5f0>
FlocksItem* __cdecl Flocks_LiveObject_Flocks_CreateSubdata(Vector3F* vector_1, Vector3F* vector_2, real32 turn, real32 speed, real32 tightness, real32 goalUpdate, Container* cont);
// <LegoRR.exe @0040f6e0>
void __cdecl freeNonNull(void* ptr);
// <LegoRR.exe @0040f700>
Flocks* __cdecl Flocks_LiveObject_Flocks_CreateData(Vector3F* vector_1, Vector3F* vector_2, real32 turn, real32 speed, real32 tightness, Container* cont);
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
real32 __cdecl Flocks_MathX_RandRangeOne(void);
// <LegoRR.exe @0040fe00>
void __cdecl Flocks_Callback_FUN_0040fe00(Flocks* flocksData, FlocksItem* subdata, real32* param_3);
// <LegoRR.exe @0040fe80>
void __cdecl Flocks_FUN_0040fe80(Flocks* flocksData, real32 randomness);
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
char* __cdecl Front_Util_ReplaceTextSpaces(char* str);
// <LegoRR.exe @00410250>
void __cdecl Front_LevelSelect_LevelNamePrintF(Font* font, sint32 x, sint32 y, char* msg, ...);
// <LegoRR.exe @00410300>
void __cdecl Front_Callback_TriggerPlayCredits(void);
// <LegoRR.exe @00410320>
void __cdecl Front_RockWipe_Play(void);
// <LegoRR.exe @00410370>
void __cdecl Front_RockWipe_Stop(void);
// <LegoRR.exe @00410380>
Front_Cache* __cdecl Front_Cache_FindByName(char* filename);
// <LegoRR.exe @004103c0>
Front_Cache* __cdecl Front_Cache_Create(char* filename);
// <LegoRR.exe @00410450>
Image* __cdecl Front_Cache_LoadImage(char* filename);
// <LegoRR.exe @00410490>
Font* __cdecl Front_Cache_LoadFont(char* filename);
// <LegoRR.exe @004104d0>
char* __cdecl Front_Util_StrCpy(char* str);
// <LegoRR.exe @00410520>
MenuItem_SelectData* __cdecl Front_MenuItem_CreateSelect(sint32* valuePtr, char* string1, char* string2, sint32 x1, sint32 y1, sint32 width1, sint32 height1, sint32 x2, sint32 y2, sint32 width2, sint32 height2, sint32 field50, MenuItem_SelectCallback callback, Menu* opt_nextMenu);
// <LegoRR.exe @004105c0>
void __cdecl Front_MenuItem_FreeSelect(MenuItem_SelectData* selectData);
// <LegoRR.exe @00410670>
void __cdecl Front_MenuItem_AddSelectItem(MenuItem_SelectData* selectData, char* bannerOrBMPName, bool32 enabled, Font* hiFont, sint32 frontEndX, sint32 frontEndY, bool32 frontEndOpen);
// <LegoRR.exe @00410940>
MenuItem_CycleData* __cdecl Front_MenuItem_CreateCycle(uint32 count, sint32* valuePtr, sint32 x2, sint32 y2, MenuItem_CycleCallback callback);
// <LegoRR.exe @004109d0>
void __cdecl Front_MenuItem_AddCycleName(MenuItem_CycleData* cycleData, char* name);
// <LegoRR.exe @00410a10>
void __cdecl Front_MenuItem_FreeCycle(MenuItem_CycleData* cycleData);
// <LegoRR.exe @00410a60>
sint32 __cdecl msx(void);
// <LegoRR.exe @00410a70>
sint32 __cdecl msy(void);
// <LegoRR.exe @00410a80>
bool32 __cdecl mslb(void);
// <LegoRR.exe @00410a90>
MenuItem_TriggerData* __cdecl Front_MenuItem_CreateTrigger(sint32* valuePtr, bool32 end, MenuItem_TriggerCallback callback);
// <LegoRR.exe @00410ac0>
MenuItem_RealSliderData* __cdecl Front_MenuItem_CreateRealSlider(real32* valuePtr, real32 valueMin, real32 valueMax, real32 step, sint32 x2, sint32 y2, MenuItem_RealSliderCallback callback);
// <LegoRR.exe @00410b20>
MenuItem_SliderData* __cdecl Front_MenuItem_CreateSlider(sint32* valuePtr, sint32 valueMin, sint32 valueMax, sint32 x2, sint32 y2, MenuItem_SliderCallback callback, Image* offBarImage, Image* onBarImage, Image* leftCapImage, Image* rightCapImage, Image* loPlusImage, Image* loMinusImage, Image* hiPlusImage, Image* hiMinusImage);
// <LegoRR.exe @00410ba0>
void __cdecl Front_MenuItem_FreeMenuItem(MenuItem* menuItem);
// <LegoRR.exe @00410c80>
MenuItem* __cdecl Front_MenuItem_CreateBannerItem(char* banner, Font* loFont, Font* hiFont, sint32 x1, sint32 y1, MenuItem_Type itemType, bool32 centered, void* itemData, bool32 notInTuto);
// <LegoRR.exe @00410d50>
MenuItem* __cdecl Front_MenuItem_CreateImageItem(char* banner, Font* loFont, Font* hiFont, char* loImageName, char* hiImageName, sint32 x1, sint32 y1, MenuItem_Type itemType, bool32 centered, char* toolTipName, void* itemData);
// <LegoRR.exe @00410e60>
void __cdecl Front_Menu_FreeMenu(Menu* menu);
// <LegoRR.exe @00410ee0>
bool32 __cdecl Front_Menu_LoadMenuImage(Menu* menu, char* filename, bool32 light);
// <LegoRR.exe @00411030>
Menu* __cdecl Front_Menu_CreateMenu(char* title, char* fullName, Font* menuFont, sint32 positionX, sint32 positionY, bool32 autoCenter, bool32 displayTitle, sint32 centerX, bool32 canScroll, char* anchored_str);
// <LegoRR.exe @00411190>
bool32 __cdecl Front_Menu_AddMenuItem(Menu* menu, MenuItem* menuItem);
// <LegoRR.exe @00411210>
bool32 __cdecl Front_Maths_IsPointInsideRect(sint32 ptX, sint32 ptY, sint32 rcX, sint32 rcY, sint32 rcWidth, sint32 rcHeight);
// <LegoRR.exe @00411250>
bool32 __cdecl Front_Maths_IsPointInsideRect_OptCenterX(sint32 ptX, sint32 ptY, sint32 rcX, sint32 rcY, sint32 rcWidth, sint32 rcHeight, bool32 shouldCenterX);
// <LegoRR.exe @00411290>
sint32 __cdecl Front_MenuItem_Select_CollisionCheck_FUN_00411290(Menu* menu, MenuItem* menuItem, MenuItem_SelectData* selectData);
// <LegoRR.exe @00411420>
bool32 __cdecl Front_Menu_IsLevelItemUnderMouse(Menu* menu, sint32 itemIndex);
// <LegoRR.exe @00411460>
bool32 __cdecl Front_Menu_GetItemBounds(Menu* menu, sint32 itemIndex, sint32* out_rcX, sint32* out_rcY, sint32* out_rcWidth, sint32* out_rcHeight);
// <LegoRR.exe @004116c0>
bool32 __cdecl Front_Menu_FindItemUnderMouse(Menu* menu, sint32* out_itemIndex);
// <LegoRR.exe @00411770>
bool32 __cdecl Front_GetMousePressedState(void);
// <LegoRR.exe @004117a0>
bool32 __cdecl Front_MenuItem_SliderHandleInput(Menu* menu, MenuItem* menuItem, MenuItem_SliderData* sliderData);
// <LegoRR.exe @00411900>
bool32 __cdecl Front_MenuItem_CheckNotInTutoAnyTutorialFlags(MenuItem* menuItem);
// <LegoRR.exe @00411930>
Menu* __cdecl Front_Menu_UpdateMenuItemsInput(real32 elapsed, Menu* menu);
// <LegoRR.exe @00411e30>
uint32 __cdecl Front_Input_GetKeyCharacter(Keys32 diKey);
// <LegoRR.exe @00411e40>
void __cdecl Front_MenuItem_DrawSlider(MenuItem_SliderData* sliderData, uint32 x, uint32 y, sint32 valueIndex, uint32 valueRange);
// <LegoRR.exe @004120a0>
uint32 __cdecl Front_Menu_GetOverlayCount(Menu* menu);
// <LegoRR.exe @004120c0>
bool32 __cdecl Front_Menu_ShouldRandomPlay(void);
// <LegoRR.exe @004120e0>
void __cdecl Front_Menu_UpdateOverlays(Menu* menu);
// <LegoRR.exe @00412380>
void __cdecl Front_MenuItem_DrawSelectItem(sint32 x, sint32 y, Font* font, MenuItem_SelectData* selectData, uint32 selIndex, MenuItem_SelectImageType imageType);
// <LegoRR.exe @00412420>
void __cdecl Front_MenuItem_DrawSaveImage(Menu* menu, sint32 selIndex, MenuItem_SelectData* selectData, bool32 bigSize);
// <LegoRR.exe @00412680>
void __cdecl Front_Menu_DrawLoadSaveText(Menu** pMenu, bool32* ref_currBool, bool32* ref_nextBool);
// <LegoRR.exe @00412900>
void __cdecl Front_MenuItem_DrawSelectTextWindow(Menu** pMenu);
// <LegoRR.exe @00412a20>
void __cdecl Front_Menu_DrawMenuImage(Menu* menu, bool32 light);
// <LegoRR.exe @00412b30>
Menu* __cdecl Front_Menu_Update(real32 elapsed, Menu* menu, bool32* optout_bool);
// <LegoRR.exe @004138a0>
void __cdecl Front_Menu_UpdateMousePosition(Menu* menu);
// <LegoRR.exe @00413990>
void __cdecl Front_LoadSaveSlotImages(void);
// <LegoRR.exe @00413a80>
void __cdecl Front_FreeSaveSlotImages(void);
// <LegoRR.exe @00413ab0>
void __cdecl Front_ScreenMenuLoop(Menu* menu);
// <LegoRR.exe @00413d50>
void __cdecl Front_RunScreenMenu(MenuSet* menuSet, uint32 menuIndex);
// <LegoRR.exe @00413d90>
MenuItem_Type __cdecl Front_MenuItem_ParseTypeString(char* itemTypeName);
// <LegoRR.exe @00413e30>
char* __cdecl Front_Util_StringReplaceChar(char* str, char origChar, char newChar);
// <LegoRR.exe @00413e60>
MenuOverlay_Type __cdecl Front_Menu_GetOverlayType(MenuOverlay* menuOverlay);
// <LegoRR.exe @00413ec0>
MenuOverlay* __cdecl Front_Menu_CreateOverlay(char* filename, MenuOverlay** linkedOverlay, sint32 positionX, sint32 positionY, SFX_ID sfxType);
// <LegoRR.exe @00413f40>
void __cdecl Front_Menu_LoadSliderImages(sint32 numParts, char** stringParts, Image** outImages);
// <LegoRR.exe @00413fa0>
MenuSet* __cdecl Front_CreateMenuSet(uint32 menuCount);
// <LegoRR.exe @00413ff0>
MenuSet* __cdecl Front_LoadMenuSet(Config* unused_config, char* menuName, void* dst, void* callback, ...);
// <LegoRR.exe @00414bc0>
sint32 __cdecl Front_GetMenuIDByName(MenuSet* menuSet, char* name);
// <LegoRR.exe @00414c10>
bool32 __cdecl Front_IsIntrosEnabled(void);
// <LegoRR.exe @00414c60>
void __cdecl Front_Callback_SliderBrightness(sint32 slider_0_10);
// <LegoRR.exe @00414d10>
void __cdecl Front_Callback_SliderSoundVolume(sint32 slider_0_10);
// <LegoRR.exe @00414d20>
void __cdecl Front_Callback_SliderMusicVolume(sint32 slider_0_10);
// <LegoRR.exe @00414d40>
sint32 __cdecl Front_CalcSliderCDVolume(void);
// <LegoRR.exe @00414d80>
void __cdecl Front_Callback_CycleWallDetail(sint32 cycle_High_Low);
// <LegoRR.exe @00414db0>
void __cdecl Front_Callback_CycleAutoGameSpeed(sint32 cycle_On_Off);
// <LegoRR.exe @00414dd0>
void __cdecl Front_Callback_CycleMusic(sint32 cycle_On_Off);
// <LegoRR.exe @00414df0>
void __cdecl Front_Callback_CycleSound(sint32 cycle_On_Off);
// <LegoRR.exe @00414e10>
void __cdecl Front_Callback_CycleHelpWindow(sint32 cycle_Off_On);
// <LegoRR.exe @00414e40>
void __cdecl Front_Callback_TriggerReplayObjective(void);
// <LegoRR.exe @00414e50>
void __cdecl Front_Callback_SliderGameSpeed(sint32 slider_0_5);
// <LegoRR.exe @00414ec0>
void __cdecl Front_UpdateSliderGameSpeed(void);
// <LegoRR.exe @00414f60>
sint32 __cdecl Front_CalcSliderGameSpeed(void);
// <LegoRR.exe @00414fe0>
void __cdecl Front_Callback_SelectLoadSave(real32 elapsedAbs, sint32 selectIndex);
// <LegoRR.exe @00415080>
void __cdecl Front_UpdateOptionsSliders(void);
// <LegoRR.exe @004150c0>
void __cdecl Front_Callback_TriggerBackSave(void);
// <LegoRR.exe @00415150>
void __cdecl Debug_ProgrammerMode11_LoadLevel(void);
// <LegoRR.exe @004151f0>
void __cdecl Front_Save_GetLevelCompleteWithPoints(SaveData* saveData, char* out_buffer);
// <LegoRR.exe @00415290>
void __cdecl Front_UpdateGameSpeedSliderLevel(void);
// <LegoRR.exe @004152a0>
bool32 __cdecl Front_Options_Update(real32 elapsed, Menu_ModalType modalType);
// <LegoRR.exe @004153e0>
bool32 __cdecl Front_LoadLevelSet(Config* config, LevelSet* levelSet, char* levelKey);
// <LegoRR.exe @00415630>
void __cdecl Front_PlayMovie(Movie_t* mov, bool32 skippable);
// <LegoRR.exe @004156f0>
void __cdecl Front_PlayIntroSplash(char* imageKey, bool32 skippable, char* timeKey);
// <LegoRR.exe @00415840>
void __cdecl Front_PlayIntroMovie(char* aviKey, bool32 skippable);
// <LegoRR.exe @004158c0>
void __cdecl Front_PlayLevelMovie(char* levelName, bool32 skippable);
// <LegoRR.exe @00415940>
void __cdecl Front_LoadLevels(MenuSet* unused_mainMenuFull);
// <LegoRR.exe @00415c20>
void __cdecl Front_ResetSaveNumber(void);
// <LegoRR.exe @00415c30>
void __cdecl Front_LoadMenuTextWindow(Config* config, char* gameName, MenuTextWindow* menuWnd);
// <LegoRR.exe @00416080>
bool32 __cdecl Front_LevelSelect_PlayLevelNameSFX(sint32 levelNumber);
// <LegoRR.exe @004160d0>
bool32 __cdecl Front_LevelSelect_PlayTutoLevelNameSFX(sint32 levelNumber);
// <LegoRR.exe @00416120>
void __cdecl Front_Initialise(Config* config);
// <LegoRR.exe @00416840>
void __cdecl Front_SaveOptionParameters(void);
// <LegoRR.exe @00416870>
void __cdecl Front_LoadOptionParameters(bool32 loadOptions, bool32 resetFront);
// <LegoRR.exe @004168f0>
void __cdecl Front_PrepareScreenMenuType(Menu_ScreenType screenType);
// <LegoRR.exe @00416bb0>
void __cdecl Front_RunScreenMenuType(Menu_ScreenType screenType);
// <LegoRR.exe @00416c30>
bool32 __cdecl Front_IsFrontEndEnabled(void);
// <LegoRR.exe @00416c80>
bool32 __cdecl Front_IsMissionSelected(void);
// <LegoRR.exe @00416c90>
bool32 __cdecl Front_IsTutorialSelected(void);
// <LegoRR.exe @00416ca0>
char* __cdecl Front_GetSelectedLevel(void);
// <LegoRR.exe @00416d00>
bool32 __cdecl Front_IsTriggerAppQuit(void);
// <LegoRR.exe @00416d10>
bool32 __cdecl Front_IsTriggerMissionQuit(void);
// <LegoRR.exe @00416d20>
bool32 __cdecl Front_IsTriggerMissionRestart(void);
// <LegoRR.exe @00416d30>
LevelSet* __cdecl Front_Levels_GetTutoOrMissions(void);
// <LegoRR.exe @00416d50>
sint32 __cdecl Front_LevelSet_IndexOf(LevelSet* levelSet, char* levelName);
// <LegoRR.exe @00416da0>
void __cdecl Front_Levels_ResetVisited(void);
// <LegoRR.exe @00416e00>
void __cdecl Front_LevelSet_SetLinkVisited(LevelSet* levelSet, char* levelName, bool32 visited);
// <LegoRR.exe @00416e70>
bool32 __cdecl Front_LevelSet_IsLinkVisited(LevelSet* levelSet, char* levelName);
// <LegoRR.exe @00416ee0>
void __cdecl Front_LevelSet_SetLevelLink(LevelSet* levelSet, char* levelName, LevelLink* link);
// <LegoRR.exe @00416f50>
LevelLink* __cdecl Front_LevelSet_GetLevelLink(LevelSet* levelSet, char* levelName);
// <LegoRR.exe @00416fc0>
LevelLink* __cdecl Front_LevelSet_LoadLevelLinks(LevelSet* levelSet, char* levelName);
// <LegoRR.exe @004170f0>
bool32 __cdecl Front_LevelLink_RunThroughLinks(LevelLink* startLink, LevelLink_RunThroughLinksCallback callback, void* data);
// <LegoRR.exe @00417170>
bool32 __cdecl Front_LevelLink_Callback_IncCount(LevelLink* link, sint32* pCount);
// <LegoRR.exe @00417180>
bool32 __cdecl Front_LevelLink_Callback_FindByLinkIndex(LevelLink* link, SearchLevelLinkFindIndex_10* search);
// <LegoRR.exe @004171b0>
LevelLink* __cdecl Front_LevelLink_FindByLinkIndex(LevelLink* startLink, sint32 linkIndex);
// <LegoRR.exe @00417200>
sint32 __cdecl Front_LevelLink_FindSetIndexOf(LevelLink* startLink, sint32 linkIndex);
// <LegoRR.exe @00417220>
void __cdecl Front_Levels_UpdateAvailable_Recursive(LevelLink* link, SearchLevelSelectInfo_14* search, bool32 unlocked);
// <LegoRR.exe @00417310>
void __cdecl Front_Levels_UpdateAvailable(LevelLink* startLink, SaveReward* opt_saveReward, LevelSet* levelSet, MenuItem_SelectData* selectData, bool32 keepLocked);
// <LegoRR.exe @00417360>
sint32 __cdecl Front_Save_GetLevelScore(uint32 index, SaveData* saveData);
// <LegoRR.exe @00417390>
void __cdecl Front_Callback_SelectMissionItem(real32 elapsedAbs, sint32 selectIndex);
// <LegoRR.exe @00417630>
void __cdecl Front_Callback_SelectTutorialItem(real32 elapsedAbs, sint32 selectIndex);
// <LegoRR.exe @00417710>
bool32 __cdecl Front_LevelInfo_Callback_AddItem(LevelLink* link, SearchLevelSelectAdd* search);
// <LegoRR.exe @004178e0>
void __cdecl MainMenuFull_AddMissionsDisplay(sint32 valueOffset, LevelLink* startLink, LevelSet* levelSet, Menu* menu, SaveData* saveData, Menu* opt_menu58, void* callback);
// <LegoRR.exe @004179c0>
bool32 __cdecl Front_Save_ReadSaveFile(uint32 saveIndex, SaveData* out_saveData, bool32 readOnly);
// <LegoRR.exe @00417b00>
bool32 __cdecl Front_Save_WriteSaveFiles(uint32 saveNumber, SaveData* opt_saveData);
// <LegoRR.exe @00417d20>
void __cdecl Front_Save_LoadAllSaveFiles(void);
// <LegoRR.exe @00417d80>
SaveData* __cdecl Front_Save_GetSaveDataAt(sint32 saveIndex);
// <LegoRR.exe @00417da0>
SaveData* __cdecl Front_Save_GetCurrentSaveData(void);
// <LegoRR.exe @00417dc0>
sint32 __cdecl Front_Save_GetSaveNumber(void);
// <LegoRR.exe @00417dd0>
void __cdecl Front_Save_SetSaveNumber(sint32 saveNumber);
// <LegoRR.exe @00417de0>
void __cdecl Front_Save_SetLevelCompleted(uint32 levelIndex);
// <LegoRR.exe @00417e50>
void __cdecl Front_Save_SetSaveStruct18(SaveStruct_18* savestruct18);
// <LegoRR.exe @00417e70>
bool32 __cdecl Front_Save_SetRewardLevel(sint32 levelIndex, RewardLevel* rewardLevel);
// <LegoRR.exe @00417ec0>
RewardLevel* __cdecl Front_Save_GetRewardLevel(sint32 levelIndex);
// <LegoRR.exe @00417ef0>
bool32 __cdecl Front_Save_WriteCurrentSaveFiles(void);
// <LegoRR.exe @00417f10>
bool32 __cdecl Front_Save_GetBool_540(void);
// <LegoRR.exe @00417f20>
void __cdecl Front_Save_SetBool_540(bool32 state);
// <LegoRR.exe @00417f30>
void __cdecl Front_Save_Write_FUN_00417f30(void);
// <LegoRR.exe @00417f70>
void __cdecl Front_Save_CopySaveData(SaveData* out_saveData);
// <LegoRR.exe @00417ff0>
void __cdecl Front_Save_SetSaveData(SaveData* saveData);
// <LegoRR.exe @00418040>
void __cdecl Front_Save_SetBool_85c(bool32 state);
// <LegoRR.exe @00418050>
bool32 __cdecl Front_Save_FUN_00418050(void);
// <LegoRR.exe @004180c0>
void __cdecl HelpWindow_SetFont(Font* font);
// <LegoRR.exe @004180d0>
void __cdecl HelpWindow_ClearFlag1(void);
// <LegoRR.exe @004180e0>
void __cdecl HelpWindow_Initialise(Config* config, char* gameName);
// <LegoRR.exe @00418380>
void __cdecl HelpWindow_LoadLevelsInfo(Config* config, char* gameName);
// <LegoRR.exe @00418520>
void __cdecl HelpWindow_LoadButtons(Config* config, char* gameName);
// <LegoRR.exe @00418730>
void __cdecl HelpWindow_IfFlag4_AndParam_Clear1_Set2_Else_Clear3(bool32 state);
// <LegoRR.exe @00418760>
void __cdecl HelpWindow_RecallDependencies(LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel, bool32 noHelpWindow);
// <LegoRR.exe @00418850>
void __cdecl HelpWindow_Object_Unlock(LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel);
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
bool32 __cdecl Info_GetInfoType(char* infoName, Info_Type* out_infoType);
// <LegoRR.exe @00419350>
void* __cdecl Info_GetTypePtr4(Info_Type infoType);
// <LegoRR.exe @00419360>
void __cdecl Info_SetOverFlowImageFile(char* filename);
// <LegoRR.exe @00419380>
void __cdecl Info_SetAutoGameSpeed(bool32 autoOn);
// <LegoRR.exe @004193a0>
void __cdecl Info_SetTypeChangeGameSpeed(Info_Type infoType, bool32 changeSpeedOn);
// <LegoRR.exe @004193e0>
void __cdecl Info_SetTypeText(Info_Type infoType, char* text);
// <LegoRR.exe @00419420>
void __cdecl Info_SetTypeFlag_20000(Info_Type infoType, bool32 setFlag20000);
// <LegoRR.exe @00419460>
void __cdecl Info_SetText_internal(char* text, char** pInfoText);
// <LegoRR.exe @00419580>
void __cdecl Info_SetTypeImageFile(Info_Type infoType, char* filename);
// <LegoRR.exe @004195b0>
void __cdecl Info_SetTypeSFX(Info_Type infoType, SFX_ID sfxID);
// <LegoRR.exe @004195d0>
bool32 __cdecl Info_EnumerateMessageInstances(sint32 handle, InfoEnumerateCallback callback, void* data);
// <LegoRR.exe @00419620>
void __cdecl Info_AddMessageInstance(sint32 handle, InfoMessageInstance* instance);
// <LegoRR.exe @004196b0>
InfoMessageInstance* __cdecl Info_GetMessageInstance(sint32 handle, sint32 instanceIndex);
// <LegoRR.exe @004196e0>
InfoMessageInstance* __cdecl Info_RemoveMessageInstance(sint32 handle, sint32 instanceIndex);
// <LegoRR.exe @00419740>
bool32 __cdecl Info_Callback_FindObjectReference(InfoMessageInstance* instance, SearchInfoObject_8* search);
// <LegoRR.exe @00419760>
void __cdecl Info_RemoveObjectReferences(LegoObject* liveObj);
// <LegoRR.exe @004197f0>
bool32 __cdecl Info_Callback_FindBlockPos(InfoMessageInstance* infoInstance, SearchInfoBlockPos_8* search);
// <LegoRR.exe @00419820>
void __cdecl Info_RemoveAllAtBlockPos(Point2I* blockPos);
// <LegoRR.exe @004198d0>
bool32 __cdecl Info_Callback_FindObjectAndBlockPos(InfoMessageInstance* instance, SearchInfoObjectBlockPos_8* search);
// <LegoRR.exe @00419920>
bool32 __cdecl Info_HasTypeAtObjectOrBlockPos(Info_Type infoType, LegoObject* opt_liveObj, Point2I* opt_blockPos);
// <LegoRR.exe @004199b0>
InfoMessageInstance* __cdecl Info_CreateInstance(Point2I* opt_blockPos, LegoObject* opt_liveObj, char* opt_text);
// <LegoRR.exe @00419a10>
void __cdecl Info_SetFlag4(bool32 state);
// <LegoRR.exe @00419a30>
bool32 __cdecl Info_HasTypeText(Info_Type infoType);
// <LegoRR.exe @00419a50>
sint32 __cdecl Info_FindExistingMessageType(Info_Type infoType);
// <LegoRR.exe @00419a80>
real32 __cdecl Info_FUN_00419a80(void);
// <LegoRR.exe @00419ab0>
void __cdecl Info_Send(Info_Type infoType, char* opt_text, LegoObject* opt_liveObj, Point2I* opt_blockPos);
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
Font* __cdecl Interface_GetFont(void);
// <LegoRR.exe @0041a230>
void __cdecl Interface_Initialise(uint32 x_565, uint32 y_18, Font* font);
// <LegoRR.exe @0041a590>
void __cdecl Interface_AddAllMenuItems(void);
// <LegoRR.exe @0041a700>
void __cdecl Interface_AddMenuItems(Interface_MenuType menuType, uint32 numItems, ...);
// <LegoRR.exe @0041a780>
void __cdecl Interface_Shutdown(void);
// <LegoRR.exe @0041a850>
void __cdecl Interface_ClearStates(void);
// <LegoRR.exe @0041a8c0>
void __cdecl Interface_ResetMenu(void);
// <LegoRR.exe @0041a8f0>
bool32 __cdecl Interface_GetMenuItemType(char* menuItemName, Interface_MenuItemType* out_menuItemType);
// <LegoRR.exe @0041a930>
void __cdecl Interface_InitBuildItems(void);
// <LegoRR.exe @0041aa30>
void __cdecl Interface_LoadBuildItems(Config* config, char* gameName);
// <LegoRR.exe @0041acd0>
void __cdecl Interface_LoadMenuItems(Config* config, char* gameName);
// <LegoRR.exe @0041af00>
void __cdecl Interface_LoadItemPanels(Config* config, char* gameName);
// <LegoRR.exe @0041b0e0>
void __cdecl Interface_LoadBackButton(Config* config, char* gameName);
// <LegoRR.exe @0041b1a0>
void __cdecl Interface_LoadPlusMinusImages(char* plusName, char* minusName);
// <LegoRR.exe @0041b200>
void __cdecl Interface_OpenMenu_FUN_0041b200(Interface_MenuType menuType, Point2I* blockPos);
// <LegoRR.exe @0041b230>
void __cdecl Interface_SelectBlock(Interface_MenuType menuType, Point2I* blockPos);
// <LegoRR.exe @0041b2f0>
uint32 __cdecl Interface_GetBuildMenuIconCount(Interface_MenuType interfaceMenuType);
// <LegoRR.exe @0041b3a0>
bool32 __cdecl Interface_NotMainOrFirstPersonMenu(Interface_MenuType interfaceMenuType);
// <LegoRR.exe @0041b3c0>
void __cdecl Interface_FUN_0041b3c0(void);
// <LegoRR.exe @0041b5b0>
bool32 __cdecl Interface_FUN_0041b5b0(Interface_MenuType menuIcon, undefined* callback, void* context);
// <LegoRR.exe @0041b730>
bool32 __cdecl Interface_Callback_FUN_0041b730(Interface_MenuItemType menuIcon, uint32 param_2, sint32 param_3, real32* param_4);
// <LegoRR.exe @0041b860>
void __cdecl Interface_FUN_0041b860(real32 elapsedAbs);
// <LegoRR.exe @0041b8e0>
bool32 __cdecl Interface_GetBool_004ded1c(void);
// <LegoRR.exe @0041b8f0>
Interface_MenuItemType __cdecl Interface_GetPrimaryUnit_PowerIcon(Interface_MenuItemType* ref_menuIcon);
// <LegoRR.exe @0041b940>
void __cdecl Interface_FUN_0041b940(real32 elapsedAbs);
// <LegoRR.exe @0041b9c0>
void __cdecl Interface_SetSFX_004df1f4(SFX_ID sfxType);
// <LegoRR.exe @0041b9d0>
bool32 __cdecl Interface_DoSomethingWithRenameReplace(uint32 param_1, uint32 param_2, sint32 param_3, sint32 param_4, sint32 param_5);
// <LegoRR.exe @0041c0f0>
bool32 __cdecl Interface_FUN_0041c0f0(uint32 param_1, uint32 param_2, undefined4* out_param_3, undefined4* out_param_4, undefined4* out_param_5);
// <LegoRR.exe @0041c240>
bool32 __cdecl Interface_Callback_FUN_0041c240(Interface_MenuItemType menuIcon, LegoObject_Type objType, LegoObject_ID objID, uint32* param_4);
// <LegoRR.exe @0041c370>
void __cdecl Interface_DoF2InterfaceKeyAction(void);
// <LegoRR.exe @0041c3a0>
bool32 __cdecl Interface_CallbackDoMenuIconKeyAction(Interface_MenuItemType menuIcon, LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @0041c420>
void __cdecl Interface_FUN_0041c420(Interface_MenuItemType menuIcon, LegoObject_Type objType, LegoObject_ID objID, real32* param_4);
// <LegoRR.exe @0041c610>
bool32 __cdecl Interface_FUN_0041c610(Interface_MenuItemType menuIcon, sint32 param_2, sint32 param_3, bool32 param_4, bool32 param_5);
// <LegoRR.exe @0041c6e0>
void __cdecl Interface_ChangeIconFlag1_FUN_0041c6e0(Interface_MenuItemType menuIcon);
// <LegoRR.exe @0041c730>
void __cdecl Interface_ChangeObjectIconFlag1_FUN_0041c730(LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @0041c820>
bool32 __cdecl Interface_GetIconUnk_FUN_0041c820(Interface_MenuItemType menuIcon, bool32 param_2);
// <LegoRR.exe @0041c880>
bool32 __cdecl Interface_GetObjectIconUnk_FUN_0041c880(LegoObject_Type objType, LegoObject_ID objID, bool32 param_3);
// <LegoRR.exe @0041c920>
void __cdecl Interface_SetIconFlag8(Interface_MenuItemType menuIcon, bool32 on);
// <LegoRR.exe @0041c950>
void __cdecl Interface_SetObjectIconFlag8(LegoObject_Type objType, LegoObject_ID objID, bool32 on);
// <LegoRR.exe @0041c990>
bool32 __cdecl Interface_GetIconFlag8(Interface_MenuItemType menuIcon);
// <LegoRR.exe @0041c9a0>
bool32 __cdecl Interface_GetObjectIconFlag8(LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @0041c9e0>
Image* __cdecl Interface_FUN_0041c9e0(Interface_MenuItemType menuIcon);
// <LegoRR.exe @0041ca20>
Image* __cdecl Interface_GetBuildImageByObjectType(LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @0041cac0>
Image* __cdecl Interface_GetObjectBuildImage(LegoObject_Type objType, LegoObject_ID objID, bool32 param_3);
// <LegoRR.exe @0041cbb0>
void __cdecl Interface_SetDat_004decd8_004decdc(Interface_MenuItemType menuIcon, LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @0041cc10>
void __cdecl Interface_FUN_0041cc10(Point2F* point, uint32 unkWidth, uint32 unkHeight);
// <LegoRR.exe @0041cc60>
void __cdecl Interface_DrawHoverOutline(Area2F* area);
// <LegoRR.exe @0041cdd0>
void __cdecl Interface_ChangeMenu_IfVehicleMounted_IsLiveObject(LegoObject* liveObj);
// <LegoRR.exe @0041ce50>
void __cdecl Interface_ChangeMenu_IfPrimarySelectedVehicle_IsLiveObject(LegoObject* liveObj);
// <LegoRR.exe @0041ceb0>
void __cdecl Interface_BackToMain_IfSelectedWall_IsBlockPos(Point2I* blockPos);
// <LegoRR.exe @0041cee0>
void __cdecl Interface_BackToMain_IfSelectedGroundOrConstruction_IsBlockPos(Point2I* blockPos);
// <LegoRR.exe @0041cf10>
void __cdecl Interface_BackToMain_IfSelectedRubble_IsBlockPos(Point2I* blockPos);
// <LegoRR.exe @0041cf40>
void __cdecl Interface_BackToMain_IfLiveObject_IsSelected_OrFlags3_200000(LegoObject* liveObj);
// <LegoRR.exe @0041cf70>
bool32 __cdecl Interface_HandleMenuItem(Interface_MenuItemType menuIcon);
// <LegoRR.exe @0041dbd0>
bool32 __cdecl Interface_DoAction_FUN_0041dbd0(Interface_MenuItemType menuIcon);
// <LegoRR.exe @0041e680>
void __cdecl Interface_BackToMain(void);
// <LegoRR.exe @0041e6a0>
void __cdecl Interface_SetIconFlash(Interface_MenuItemType menuIcon, bool32 flash);
// <LegoRR.exe @0041e6d0>
void __cdecl Interface_SetSubmenuIconFlash(LegoObject_Type objType, LegoObject_ID objID, bool32 flash);
// <LegoRR.exe @0041e710>
LegoObject* __cdecl Interface_GetPrimarySelectedUnit(void);
// <LegoRR.exe @0041e720>
sint32 __cdecl Interface_SetIconClicked(Interface_MenuItemType menuIcon, sint32 clickedCount);
// <LegoRR.exe @0041e740>
sint32 __cdecl Interface_GetIconClicked(Interface_MenuItemType menuIcon);
// <LegoRR.exe @0041e750>
sint32 __cdecl Interface_SetSubmenuIconClicked(LegoObject_Type objType, LegoObject_ID objID, sint32 clickedCount);
// <LegoRR.exe @0041e790>
sint32 __cdecl Interface_GetSubmenuIconClicked(LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @0041e7c0>
bool32 __cdecl Interface_SetAdvisorPointToFashingIcon(Interface_MenuItemType menuIcon, bool32 setFlag40);
// <LegoRR.exe @0041e800>
Advisor_Type __cdecl Interface_GetAdvisorType_FromIcon(Interface_MenuItemType menuIcon);
// <LegoRR.exe @0041e8c0>
bool32 __cdecl Interface_GetObjectBool_FUN_0041e8c0(LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @0041e900>
void __cdecl Interface_SetScrollParameters(uint32 xEnd, uint32 yEnd, uint32 xStart, uint32 yStart, real32 timerFloat_750);
// <LegoRR.exe @0041e980>
void __cdecl Interface_UnkSlideOffScreen_FUN_0041e980_internal(Interface_MenuType menuType, Point2I* opt_blockPos);
// <LegoRR.exe @0041e9f0>
void __cdecl Interface_FUN_0041e9f0(real32 elapsedAbs);
// <LegoRR.exe @0041eb60>
void __cdecl Interface_DrawTeleportQueueNumber(LegoObject_Type objType, LegoObject_ID objID, Point2F* screenPt);
// <LegoRR.exe @0041ebd0>
void __cdecl Interface_FUN_0041ebd0(real32 xScreen, real32 yScreen);
// <LegoRR.exe @0041ed90>
void __cdecl Interface_SetFloat1494To25_AndUnsetFlags800(void);
// <LegoRR.exe @0041edb0>
bool32 __cdecl Interface_FUN_0041edb0(uint32 param_1, uint32 param_2, real32 x, real32 y, LegoObject_Type* out_objType, LegoObject_ID* out_objID, uint32* out_objLevel);
// <LegoRR.exe @0041f030>
bool32 __cdecl Interface_HasTeleporterForObject(LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @0041f0c0>
bool32 __cdecl Interface_Callback_HasObject(LegoObject* liveObj, SearchInterfaceFindObject* search);
// <LegoRR.exe @0041f160>
bool32 __cdecl Interface_HasUpgradeStation(void);
// <LegoRR.exe @0041f1a0>
bool32 __cdecl Interface_HasStatsFlags2(StatsFlags2 statsFlags2);
// <LegoRR.exe @0041f1e0>
bool32 __cdecl Interface_HasToolStore(void);
// <LegoRR.exe @0041f220>
bool32 __cdecl Interface_HasObjectOfTypeID(LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @0041f270>
bool32 __cdecl Interface_HasObjectWithAbilities(LegoObject_AbilityFlags abilityFlags);
// <LegoRR.exe @0041f2c0>
bool32 __cdecl Interface_Callback_ReqestDigBlock(LegoObject* liveObj, Point2I* blockPos);
// <LegoRR.exe @0041f2f0>
bool32 __cdecl Interface_ReqestDigBlock(Point2I* blockPos);
// <LegoRR.exe @0041f310>
bool32 __cdecl Interface_Callback_RequestReinforceBlock(LegoObject* liveObj, Point2I* blockPos);
// <LegoRR.exe @0041f330>
bool32 __cdecl Interface_RequestReinforceBlock(Point2I* blockPos);
// <LegoRR.exe @0041f350>
bool32 __cdecl Interface_DoSelectedUnits_Callback(LegoObject_RunThroughListsCallback callback, void* data);
// <LegoRR.exe @0041f3a0>
bool32 __cdecl Interface_ObjectCallback_IsCarryingButNotStoring(LegoObject* liveObj, void* unused);
// <LegoRR.exe @0041f3c0>
bool32 __cdecl Interface_ObjectCallback_IsEnergyBelowMax(LegoObject* liveObj, void* unused);
// <LegoRR.exe @0041f3e0>
bool32 __cdecl Interface_ObjectCallback_IsHealthBelowMax(LegoObject* liveObj, void* unused);
// <LegoRR.exe @0041f400>
bool32 __cdecl Interface_ObjectCallback_FUN_0041f400(LegoObject* liveObj, void* unused);
// <LegoRR.exe @0041f520>
bool32 __cdecl Interface_ObjectCallback_SetFlags4_8_HealthM1(LegoObject* liveObj, void* unused);
// <LegoRR.exe @0041f540>
bool32 __cdecl Interface_ObjectCallback_GoEatIfEnergyBelowMax(LegoObject* liveObj, void* unused);
// <LegoRR.exe @0041f570>
bool32 __cdecl Interface_ObjectCallback_RequestRepairIfHealthBelowMax(LegoObject* liveObj, void* unused);
// <LegoRR.exe @0041f5a0>
bool32 __cdecl Interface_ObjectCallback_DoesNotHaveToolEquipped(LegoObject* liveObj, LegoObject_ToolType toolType);
// <LegoRR.exe @0041f5c0>
bool32 __cdecl Interface_ObjectCallback_GoGetToolIfNotEquipped(LegoObject* liveObj, LegoObject_ToolType toolType);
// <LegoRR.exe @0041f5f0>
bool32 __cdecl Interface_ObjectCallback_FUN_0041f5f0(LegoObject* liveObj, void* unused);
// <LegoRR.exe @0041f650>
bool32 __cdecl Interface_CheckPrimaryUnitHasAbility(LegoObject_AbilityFlags abilityFlag);
// <LegoRR.exe @0041f670>
bool32 __cdecl Interface_Block_FUN_0041f670(Point2I* blockPos);
// <LegoRR.exe @0041f750>
bool32 __cdecl Interface_ObjectCallback_HasToolEquipped_2(LegoObject* liveObj, LegoObject_ToolType toolType);
// <LegoRR.exe @0041f770>
bool32 __cdecl Interface_ObjectCallback_PlaceBirdScarerIfEquipped(LegoObject* liveObj, void* unused);
// <LegoRR.exe @0041f7a0>
void __cdecl Level_IncCrystalsStored(void);
// <LegoRR.exe @0041f7b0>
void __cdecl Level_SubtractCrystalsStored(sint32 crystalAmount);
// <LegoRR.exe @0041f7d0>
void __cdecl Level_AddCrystalsDrained(sint32 crystalDrainedAmount);
// <LegoRR.exe @0041f810>
sint32 __cdecl Level_GetCrystalCount(bool32 includeDrained);
// <LegoRR.exe @0041f830>
sint32 __cdecl Level_GetOreCount(bool32 isProcessed);
// <LegoRR.exe @0041f850>
void __cdecl Level_AddStolenCrystals(sint32 stolenCrystalAmount);
// <LegoRR.exe @0041f870>
void __cdecl Lego_SetRadarNoTrackObject(bool32 noTrackObj);
// <LegoRR.exe @0041f8a0>
bool32 __cdecl Lego_IsNoclipOn(void);
// <LegoRR.exe @0041f8b0>
void __cdecl Level_IncCrystalsPickedUp(void);
// <LegoRR.exe @0041f8c0>
void __cdecl Level_IncOrePickedUp(void);
// <LegoRR.exe @0041f8d0>
void __cdecl Level_IncOreStored(bool32 isProcessed);
// <LegoRR.exe @0041f910>
void __cdecl Level_SubtractOreStored(bool32 isProcessed, sint32 oreAmount);
// <LegoRR.exe @0041f950>
bool32 __cdecl Gods_Go(char* programName);
// <LegoRR.exe @0041f9b0>
void __cdecl Lego_StartLevelEnding(void);
// <LegoRR.exe @0041fa70>
real32 __cdecl Lego_GetGameSpeed(void);
// <LegoRR.exe @0041fa80>
bool32 __cdecl Lego_Initialise(void);
// <LegoRR.exe @00422780>
void __cdecl Lego_LoadMiscObjects(Config* config);
// <LegoRR.exe @00422fb0>
Container* __cdecl Lego_GetCurrentCamera_Container(void);
// <LegoRR.exe @00422fe0>
real32 __cdecl Lego_GetElapsedAbs(void);
// <LegoRR.exe @00422ff0>
void __cdecl Lego_DrawRenameInput(real32 elapsedAbs);
// <LegoRR.exe @00423120>
void __cdecl Lego_HandleRenameInput(void);
// <LegoRR.exe @00423210>
bool32 __cdecl Lego_MainLoop(real32 elapsed);
// <LegoRR.exe @00424490>
void __cdecl Level_ConsumeObjectOxygen(LegoObject* liveObj, real32 elapsed);
// <LegoRR.exe @00424530>
void __cdecl Level_UpdateEffects(Lego_Level* level, real32 elapsedGame);
// <LegoRR.exe @00424660>
void __cdecl Lego_UpdateSceneFog(bool32 fogEnabled, real32 elapsed);
// <LegoRR.exe @00424700>
bool32 __cdecl Lego_DrawObjectLaserTrackerBox(LegoObject* liveObj, Viewport* viewMain);
// <LegoRR.exe @00424740>
void __cdecl Lego_DrawAllLaserTrackerBoxes(Viewport* viewMain);
// <LegoRR.exe @00424760>
void __cdecl Lego_DrawAllSelectedUnitBoxes(Viewport* viewMain);
// <LegoRR.exe @004247e0>
void __cdecl Lego_DrawObjectSelectionBox(LegoObject* liveObj, Viewport* view, real32 r, real32 g, real32 b);
// <LegoRR.exe @00424c20>
void __cdecl Lego_Shutdown_Quick(void);
// <LegoRR.exe @00424c30>
void __cdecl Lego_Shutdown_Full(void);
// <LegoRR.exe @00424fd0>
void __cdecl Lego_Exit(void);
// <LegoRR.exe @00424ff0>
bool32 __cdecl Lego_HandleKeys(real32 elapsedGame, real32 param_2, bool32* out_keyDownT, bool32* out_keyDownR, bool32* out_keyDownAnyShift);
// <LegoRR.exe @00425a70>
bool32 __cdecl Lego_UpdateAll3DSounds(bool32 stopAll);
// <LegoRR.exe @00425a90>
bool32 __cdecl Lego_UpdateObject3DSounds(LegoObject* liveObj, bool32* pStopAll);
// <LegoRR.exe @00425b60>
void __cdecl Lego_SetPaused(bool32 checkCamDisableFlag, bool32 paused);
// <LegoRR.exe @00425c00>
void __cdecl Lego_LockGameSpeed(bool32 locked);
// <LegoRR.exe @00425c10>
void __cdecl Lego_SetGameSpeed(real32 newGameSpeed);
// <LegoRR.exe @00425c80>
void __cdecl Lego_TrackObjectInRadar(LegoObject* liveObj);
// <LegoRR.exe @00425cb0>
bool32 __cdecl Lego_IsFirstPersonView(void);
// <LegoRR.exe @00425cc0>
void __cdecl Lego_HandleRadarInput(void);
// <LegoRR.exe @004260f0>
void __cdecl Lego_UpdateSlug_FUN_004260f0(real32 elapsedGame);
// <LegoRR.exe @00426160>
void __cdecl Lego_GetMouseWorldPosition(Vector3F* out_mouseWorldPos);
// <LegoRR.exe @00426180>
void __cdecl Lego_UnkCameraTrack_InRadar_FUN_00426180(void);
// <LegoRR.exe @00426210>
void __cdecl Lego_SetMenuNextPosition(Point2F* position);
// <LegoRR.exe @00426250>
void __cdecl Lego_SetMenuPreviousPosition(Point2F* position);
// <LegoRR.exe @00426290>
void __cdecl Lego_SetFlags2_40_And_2_unkCamera(bool32 onFlag40, bool32 onFlag2);
// <LegoRR.exe @004262d0>
void __cdecl Lego_SetFlags2_80(bool32 state);
// <LegoRR.exe @004262f0>
void __cdecl Lego_UnkObjective_CompleteSub_FUN_004262f0(void);
// <LegoRR.exe @00426350>
void __cdecl Lego_UpdateTopdownCamera(real32 elapsedAbs);
// <LegoRR.exe @00426450>
void __cdecl Lego_HandleWorld(real32 elapsedGame, real32 elapsedAbs, bool32 keyDownT, bool32 keyDownR, bool32 keyDownAnyShift);
// <LegoRR.exe @00427d30>
void __cdecl Lego_LoadToolTipInfos(Config* config, char* gameName_unused);
// <LegoRR.exe @00427eb0>
void __cdecl Lego_LoadUpgradeNames(Config* config);
// <LegoRR.exe @00427f50>
void __cdecl Lego_ShowObjectToolTip(LegoObject* liveObj);
// <LegoRR.exe @00428260>
void __cdecl Lego_ShowBlockToolTip(Point2I* mouseBlockPos, bool32 showConstruction, bool32 playSound, bool32 showCavern);
// <LegoRR.exe @004286b0>
bool32 __cdecl Level_BlockPointerCheck(Point2I* blockPos);
// <LegoRR.exe @00428730>
void __cdecl Lego_SetPointerSFX(PointerSFX_Type pointerSFXType);
// <LegoRR.exe @00428810>
void __cdecl Lego_HandleDebugKeys(sint32 bx, sint32 by, LegoObject* liveObj, real32 gameCtrlElapsed);
// <LegoRR.exe @00429040>
void __cdecl Lego_XYCallback_AddVisibleSmoke(sint32 bx, sint32 by);
// <LegoRR.exe @00429090>
Container_Texture* __cdecl Lego_GetBlockDetail_ContainerTexture(Point2I* blockPos);
// <LegoRR.exe @004290d0>
void __cdecl Lego_UnkUpdateMapsWorldUnk_FUN_004290d0(real32 elapsedAbs, bool32 pass2);
// <LegoRR.exe @004292e0>
void __cdecl Lego_DrawDragSelectionBox(Lego_Level* level);
// <LegoRR.exe @004293a0>
void __cdecl Lego_MainView_MouseTransform(uint32 mouseX, uint32 mouseY, real32* out_xPos, real32* out_yPos);
// <LegoRR.exe @004294d0>
Container* __cdecl Lego_GetCurrentViewLight(void);
// <LegoRR.exe @004294f0>
bool32 __cdecl Lego_IsFPObject(LegoObject* liveObj);
// <LegoRR.exe @00429520>
void __cdecl Lego_SetViewMode(ViewMode viewMode, LegoObject* liveObj, uint32 cameraFrame);
// <LegoRR.exe @004296d0>
void __cdecl Lego_CDTrackPlayNextCallback(void);
// <LegoRR.exe @004296e0>
void __cdecl Lego_SetMusicOn(bool32 isMusicOn);
// <LegoRR.exe @00429740>
void __cdecl Lego_SetSoundOn(bool32 isSoundOn);
// <LegoRR.exe @00429780>
LegoObject_ID __cdecl Lego_GetEmergeCreatureID(void);
// <LegoRR.exe @00429790>
real32 __cdecl Lego_GetObjectUpgradeTime(LegoObject_Type objType);
// <LegoRR.exe @004297b0>
real32 __cdecl Lego_GetTrainTime(void);
// <LegoRR.exe @004297c0>
bool32 __cdecl Lego_LoadLevel(char* levelName);
// <LegoRR.exe @0042b220>
bool32 __cdecl Level_AddCryOreToToolStore(LegoObject* liveObj, SearchAddCryOre_c* search);
// <LegoRR.exe @0042b260>
bool32 __cdecl Lego_LoadDetailMeshes(Lego_Level* level, char* meshBaseName);
// <LegoRR.exe @0042b3b0>
void __cdecl Lego_FreeDetailMeshes(Lego_Level* level);
// <LegoRR.exe @0042b430>
RadarMap* __cdecl Lego_GetRadarMap(void);
// <LegoRR.exe @0042b440>
bool32 __cdecl Lego_LoadMapSet(Lego_Level* level, char* surfaceMap, char* predugMap, sint32 predugParam, char* terrainMap, sint32 terrainParam, char* blockPointersMap, sint32 blockPointersParam, char* cryOreMap, char cryOreParam, char* erodeMap, char* pathMap, sint32 pathParam, char* textureSet, char* emergeMap, char* aiMap, char* fallinMap);
// <LegoRR.exe @0042b780>
void __cdecl Lego_InitTextureMappings(Map3D* map);
// <LegoRR.exe @0042ba90>
bool32 __cdecl Lego_LoadTextureSet(Lego_Level* level, char* keyTexturePath);
// <LegoRR.exe @0042bc50>
bool32 __cdecl Lego_LoadPreDugMap(Lego_Level* level, char* filename, sint32 modifier);
// <LegoRR.exe @0042be70>
bool32 __cdecl Lego_LoadErodeMap(Lego_Level* level, char* filename);
// <LegoRR.exe @0042bf90>
bool32 __cdecl Lego_LoadAIMap(Lego_Level* level, char* filename);
// <LegoRR.exe @0042c050>
bool32 __cdecl Lego_LoadEmergeMap(Lego_Level* level, char* filename);
// <LegoRR.exe @0042c260>
bool32 __cdecl Level_HandleEmergeTriggers(Lego_Level* level, Point2I* blockPos, Point2I* out_emergeBlockPos);
// <LegoRR.exe @0042c370>
void __cdecl Level_Emerge_FUN_0042c370(Lego_Level* level, real32 elapsedAbs);
// <LegoRR.exe @0042c3b0>
bool32 __cdecl Lego_LoadTerrainMap(Lego_Level* level, char* filename, sint32 modifier);
// <LegoRR.exe @0042c4e0>
bool32 __cdecl Lego_GetBlockCryOre(Point2I* blockPos, uint32* out_crystalLv0, uint32* out_crystalLv1, uint32* out_oreLv0, uint32* out_oreLv1);
// <LegoRR.exe @0042c5d0>
bool32 __cdecl Lego_LoadCryOreMap(Lego_Level* level, char* filename, char modifier);
// <LegoRR.exe @0042c690>
bool32 __cdecl Lego_LoadPathMap(Lego_Level* level, char* filename, sint32 modifier);
// <LegoRR.exe @0042c900>
bool32 __cdecl Lego_LoadFallinMap(Lego_Level* level, char* filename);
// <LegoRR.exe @0042caa0>
void __cdecl Lego_UpdateFallins(real32 elapsedGame);
// <LegoRR.exe @0042cbc0>
bool32 __cdecl Lego_LoadBlockPointersMap(Lego_Level* level, char* filename, sint32 modifier);
// <LegoRR.exe @0042cc80>
Upgrade_PartModel* __cdecl Lego_GetUpgradePartModel(char* upgradeName);
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
void __cdecl Lego_LoadObjectNames(Config* config);
// <LegoRR.exe @0042d950>
void __cdecl Lego_LoadObjectTheNames(Config* config);
// <LegoRR.exe @0042dd70>
void __cdecl Lego_Goto(LegoObject* liveObj, Point2I* blockPos, bool32 smooth);
// <LegoRR.exe @0042def0>
void __cdecl Lego_RemoveRecordObject(LegoObject* liveObj);
// <LegoRR.exe @0042df20>
bool32 __cdecl Lego_GetRecordObject(uint32 recordObjPtr, LegoObject** out_liveObj);
// <LegoRR.exe @0042df50>
bool32 __cdecl Lego_LoadOLObjectList(Lego_Level* level, char* filename);
// <LegoRR.exe @0042e7e0>
bool32 __cdecl Lego_GetObjectByName(char* objName, LegoObject_Type* out_objType, LegoObject_ID* out_objID, Container** optout_model);
// <LegoRR.exe @0042eca0>
bool32 __cdecl Lego_GetObjectTypeModel(LegoObject_Type objType, LegoObject_ID objID, Container** out_model);
// <LegoRR.exe @0042ee70>
sint32 __cdecl Lego_GetObjectTypeIDCount(LegoObject_Type objType);
// <LegoRR.exe @0042eef0>
void __cdecl Lego_PlayMovie_old(char* fName, Point2F* opt_screenPt);
// <LegoRR.exe @0042eff0>
char* __cdecl Level_Free(void);
// <LegoRR.exe @0042f210>
void __cdecl Level_Block_SetFlags1_200_AndUpdateSurface_LevelStruct428(Lego_Level* level, uint32 bx, uint32 by, bool32 setFlag200);
// <LegoRR.exe @0042f280>
SurfaceTexture __cdecl Level_Block_ChoosePathTexture(sint32 bx, sint32 by, uint8* ref_direction, bool32 powered);
// <LegoRR.exe @0042f620>
void __cdecl Level_BlockUpdateSurface(Lego_Level* level, sint32 bx, sint32 by, bool32 reserved);
// <LegoRR.exe @004301e0>
void __cdecl Level_Block_Proc_FUN_004301e0(Point2I* blockPos);
// <LegoRR.exe @00430250>
void __cdecl AITask_DoClearTypeAction(Point2I* blockPos, Message_Type completeAction);
// <LegoRR.exe @004303a0>
void __cdecl Level_Debug_WKey_NeedsBlockFlags1_8_FUN_004303a0(Lego_Level* level, bool32 unused, uint32 bx, uint32 by);
// <LegoRR.exe @00430460>
bool32 __cdecl Level_DestroyWall(Lego_Level* level, uint32 bx, uint32 by, bool32 isHiddenCavern);
// <LegoRR.exe @00430d20>
void __cdecl Level_Block_FUN_00430d20(Point2I* blockPos);
// <LegoRR.exe @00430e10>
bool32 __cdecl Level_DestroyWallConnection(Lego_Level* level, uint32 bx, uint32 by);
// <LegoRR.exe @00431020>
void __cdecl Level_Block_RemoveReinforcement(Point2I* blockPos);
// <LegoRR.exe @00431070>
void __cdecl Level_Block_Reinforce(sint32 bx, sint32 by);
// <LegoRR.exe @00431100>
void __cdecl Level_BlockActivity_Create(Lego_Level* level, Point2I* blockPos, bool32 staticEffect);
// <LegoRR.exe @004312e0>
void __cdecl Level_BlockActivity_UpdateAll(Lego_Level* level, real32 elapsedGame);
// <LegoRR.exe @00431380>
void __cdecl Level_BlockActivity_Destroy(Lego_Level* level, Point2I* blockPos, bool32 wallDestroyed);
// <LegoRR.exe @004313f0>
void __cdecl Level_BlockActivity_Remove(Lego_BlockActivity* blockAct);
// <LegoRR.exe @00431460>
void __cdecl Level_BlockActivity_RemoveAll(Lego_Level* level);
// <LegoRR.exe @00431490>
Lego_Level* __cdecl Lego_GetLevel(void);
// <LegoRR.exe @004314a0>
Map3D* __cdecl Lego_GetMap(void);
// <LegoRR.exe @004314b0>
void __cdecl Level_UncoverHiddenCavern(uint32 bx, uint32 by);
// <LegoRR.exe @004316b0>
void __cdecl Lego_PTL_RockFall(uint32 bx, uint32 by, sint32 param_3, bool32 param_4);
// <LegoRR.exe @004318e0>
Lego_SurfaceType __cdecl Lego_GetBlockTerrain(sint32 bx, sint32 by);
// <LegoRR.exe @00431910>
uint32 __cdecl MapShared_GetBlock(uint32 memHandle, sint32 bx, sint32 by);
// <LegoRR.exe @00431960>
bool32 __cdecl Level_FindSelectedUnit_BlockCheck_FUN_00431960(uint32 bx, uint32 by, bool32 param_3);
// <LegoRR.exe @004319e0>
bool32 __cdecl Level_FindSelectedLiveObject_BlockReinforce_FUN_004319e0(uint32 bx, uint32 by);
// <LegoRR.exe @00431a50>
bool32 __cdecl Level_BlockCheck_SelectPlace_FUN_00431a50(sint32 bx, sint32 by, bool32 param_3, bool32 param_4);
// <LegoRR.exe @00431ba0>
bool32 __cdecl LiveObject_FUN_00431ba0(LegoObject* liveObj, Point2I* blockPos, Point2I* out_blockOffPos, bool32 param_4);
// <LegoRR.exe @00431cd0>
sint32 __cdecl Lego_GetCrossTerrainType(LegoObject* liveObj, sint32 bx1, sint32 by1, sint32 bx2, sint32 by2, bool32 param_6);
// <LegoRR.exe @00432030>
void __cdecl Level_PowerGrid_AddPoweredBlock(Point2I* blockPos);
// <LegoRR.exe @004320a0>
bool32 __cdecl Level_Block_IsPowered(Point2I* blockPos);
// <LegoRR.exe @004320d0>
void __cdecl Level_PowerGrid_UpdateLevelBlocks_PointsAAC(void);
// <LegoRR.exe @00432130>
void __cdecl Level_PowerGrid_ClearBlockPowered_100_Points28C(void);
// <LegoRR.exe @004321a0>
void __cdecl Level_PowerGrid_AddDrainPowerBlock(Point2I* blockPos);
// <LegoRR.exe @00432200>
bool32 __cdecl Level_PowerGrid_IsDrainPowerBlock(Point2I* blockPos);
// <LegoRR.exe @00432230>
void __cdecl Legel_PowerGrid_ClearDrainPowerBlocks(void);
// <LegoRR.exe @00432290>
void __cdecl Level_Block_UnsetBuildingTile(Point2I* blockPos);
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
void __cdecl Level_Block_SetBusyFloor(Point2I* blockPos, bool32 busyFloor);
// <LegoRR.exe @004326a0>
bool32 __cdecl LiveObject_BlockCheck_FUN_004326a0(LegoObject* liveObj, uint32 bx, uint32 by, bool32 param_4, bool32 param_5);
// <LegoRR.exe @00432880>
bool32 __cdecl LiveObject_CanDynamiteBlockPos(LegoObject* liveObj, uint32 bx, uint32 by);
// <LegoRR.exe @00432900>
bool32 __cdecl Level_Block_IsGround_alt(LegoObject* liveObj, uint32 bx, uint32 by);
// <LegoRR.exe @00432950>
bool32 __cdecl LiveObject_CanReinforceBlock(LegoObject* liveObj, uint32 bx, uint32 by);
// <LegoRR.exe @004329d0>
bool32 __cdecl Level_Block_IsSolidBuilding(uint32 bx, uint32 by, bool32 includeToolStore);
// <LegoRR.exe @00432a30>
bool32 __cdecl Level_Block_IsRockFallFX(uint32 bx, uint32 by);
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
bool32 __cdecl Level_Block_IsGap(uint32 bx, uint32 by);
// <LegoRR.exe @00432f30>
bool32 __cdecl Level_Block_IsCornerInner(uint32 bx, uint32 by);
// <LegoRR.exe @00432f60>
bool32 __cdecl Level_Block_IsPathBuilding(Point2I* blockPos);
// <LegoRR.exe @00432f90>
bool32 __cdecl Level_Block_IsGeneratePower(Point2I* blockPos);
// <LegoRR.exe @00432fc0>
bool32 __cdecl Level_Block_IsPath(Point2I* blockPos);
// <LegoRR.exe @00433010>
bool32 __cdecl Level_Block_IsFoundationOrBusyFloor(Point2I* blockPos);
// <LegoRR.exe @00433050>
void __cdecl Level_Block_SetDozerClearing(Point2I* blockPos, bool32 state);
// <LegoRR.exe @004330b0>
bool32 __cdecl LiveObject_GetDamageFromSurface(LegoObject* liveObj, sint32 bx, sint32 by, real32 elapsedGame, real32* optout_damage);
// <LegoRR.exe @004331f0>
uint32 __cdecl Level_Block_GetDirection(uint32 bx, uint32 by);
// <LegoRR.exe @00433220>
void __cdecl Level_Block_SetSurveyed(uint32 bx, uint32 by);
// <LegoRR.exe @00433260>
bool32 __cdecl Level_Block_GetSurfaceType(uint32 bx, uint32 by, Lego_SurfaceType* out_surfaceType);
// <LegoRR.exe @004332b0>
void __cdecl Level_Block_LowerRoofVertices(Lego_Level* level, uint32 bx, uint32 by);
// <LegoRR.exe @004333f0>
void __cdecl MapShared_GetDimensions(uint32 memHandle, uint32* out_width, uint32* out_height);
// <LegoRR.exe @00433420>
bool32 __cdecl Lego_LoadGraphicsSettings(void);
// <LegoRR.exe @004336a0>
bool32 __cdecl Lego_LoadLighting(void);
// <LegoRR.exe @00433b10>
bool32 __cdecl Lego_WorldToBlockPos_NoZ(real32 xPos, real32 yPos, sint32* out_bx, sint32* out_by);
// <LegoRR.exe @00433b40>
bool32 __cdecl LiveObject_FUN_00433b40(LegoObject* liveObj, real32 param_2, bool32 param_3);
// <LegoRR.exe @00433d60>
bool32 __cdecl Level_Block_IsMeshHidden(uint32 bx, uint32 by);
// <LegoRR.exe @00433db0>
void __cdecl Lego_FPHighPolyBlocks_FUN_00433db0(Container* contCamera, Viewport* view, real32 fpClipBlocksMult, real32 highPolyBlocksMult);
// <LegoRR.exe @00434380>
sint32 __cdecl Lego_QsortCompareUnk_FUN_00434380(sint32 param_1, sint32 param_2);
// <LegoRR.exe @004343b0>
bool32 __cdecl Level_Block_Detail_FUN_004343b0(Lego_Level* level, uint32 bx, uint32 by, real32 scaleZ, real32 brightness);
// <LegoRR.exe @00434460>
void __cdecl Level_RemoveAll_ProMeshes(void);
// <LegoRR.exe @004344a0>
bool32 __cdecl Level_Block_Damage(uint32 bx, uint32 by, real32 param_3, real32 param_4);
// <LegoRR.exe @00434520>
void __cdecl Lego_LoadPanels(Config* config, uint32 screenWidth, uint32 screenHeight);
// <LegoRR.exe @00434640>
void __cdecl Lego_LoadPanelButtons(Config* config, uint32 screenWidth, uint32 screenHeight);
// <LegoRR.exe @00434930>
void __cdecl Lego_LoadTutorialIcon(Config* config);
// <LegoRR.exe @00434980>
void __cdecl Lego_LoadSamples(Config* config, bool32 noReduceSamples);
// <LegoRR.exe @00434a20>
void __cdecl Lego_LoadTextMessages(Config* config);
// <LegoRR.exe @00434b40>
void __cdecl Lego_LoadInfoMessages(Config* config);
// <LegoRR.exe @00434cd0>
void __cdecl Lego_LoadToolTips(Config* config);
// <LegoRR.exe @00434db0>
bool32 __cdecl Lego_TryTeleportObject(LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @00434f40>
void __cdecl Level_Block_UpdateSurveyRadius_FUN_00434f40(Point2I* blockPos, sint32 surveyRadius);
// <LegoRR.exe @00434fd0>
void __cdecl Lego_LoadSurfaceTypeDescriptions_sound(Config* config, char* gameName);
// <LegoRR.exe @004350a0>
char* __cdecl Lego_GetSurfaceTypeDescription(Lego_SurfaceType surfaceType);
// <LegoRR.exe @004350c0>
SFX_ID __cdecl Lego_GetSurfaceTypeSFX(Lego_SurfaceType surfaceType);
// <LegoRR.exe @004350d0>
void __cdecl Level_SetPointer_FromSurfaceType(Lego_SurfaceType surfaceType);
// <LegoRR.exe @00435160>
void __cdecl Level_GenerateFallin_InRadius(Point2I* blockPos, sint32 radius, bool32 param_3);
// <LegoRR.exe @00435230>
void __cdecl Level_UpdateTutorialBlockFlashing(Lego_Level* level, Viewport* viewMain, real32 elapsedGame, real32 elapsedAbs);
// <LegoRR.exe @00435480>
bool32 __cdecl Front_LeftButtonInputUnk_FUN_00435480(void);
// <LegoRR.exe @004354b0>
bool32 __cdecl Front_DrawDialogContrastOverlay(void);
// <LegoRR.exe @004354f0>
sint32 __cdecl SaveMenu_ConfirmMessage_FUN_004354f0(char* titleText, char* message, char* okText, char* cancelText);
// <LegoRR.exe @00435870>
bool32 __cdecl Lego_EndLevel(void);
// <LegoRR.exe @00435950>
void __cdecl Lego_ClearSomeFlags3_FUN_00435950(void);
// <LegoRR.exe @00435980>
void __cdecl Lego_UnkTeleporterInit_FUN_00435980(void);
// <LegoRR.exe @004359b0>
void __cdecl Lego_SetAttackDefer(bool32 defer);
// <LegoRR.exe @004359d0>
void __cdecl Lego_SetCallToArmsOn(bool32 callToArms);
// <LegoRR.exe @00435a50>
LegoCamera* __cdecl Camera_Create(Container* root, LegoCamera_Type camType);
// <LegoRR.exe @00435cc1>
void __cdecl Camera_EnableFreeMovement(LegoCamera* cam, bool32 on);
// <LegoRR.exe @00435cf8>
void __cdecl Camera_Free(LegoCamera* cam);
// <LegoRR.exe @00435d3e>
void __cdecl Camera_InitCameraMovements(real32 cameraSpeed, real32 cameraDropOff, real32 cameraAcceleration, sint32 mouseScrollIndent);
// <LegoRR.exe @00435d65>
void __cdecl Camera_CopyFPPositionOrientation(LegoCamera* dstCamera, LegoCamera* srcCamera);
// <LegoRR.exe @00435deb>
void __cdecl Camera_TrackObject(LegoCamera* cam, LegoObject* liveObj, real32 trackFloat_8, real32 trackDist, real32 trackTilt, real32 trackRotationSpeed);
// <LegoRR.exe @00435e24>
void __cdecl Camera_SetFPObject(LegoCamera* cam, LegoObject* liveObj, sint32 cameraFrame);
// <LegoRR.exe @00435e3b>
sint32 __cdecl Camera_GetFPCameraFrame(LegoCamera* cam);
// <LegoRR.exe @00435e46>
void __cdecl Camera_StopMovement(LegoCamera* cam);
// <LegoRR.exe @00435e58>
sint32 __cdecl Camera_GetMouseScrollIndent(void);
// <LegoRR.exe @00435e62>
void __cdecl Camera_Shake(LegoCamera* cam, real32 intensity, real32 duration);
// <LegoRR.exe @00435e8c>
void __cdecl Camera_Update(LegoCamera* cam, Lego_Level* level, real32 elapsedAbs, real32 elapsedGame);
// <LegoRR.exe @00436a53>
void __cdecl Camera_SetTiltRange(LegoCamera* cam, real32 minTilt, real32 maxTilt);
// <LegoRR.exe @00436a82>
void __cdecl Camera_SetTilt(LegoCamera* cam, real32 tilt);
// <LegoRR.exe @00436b22>
void __cdecl Camera_AddTilt(LegoCamera* cam, real32 tiltAmount);
// <LegoRR.exe @00436b43>
void __cdecl Camera_SetRotationRange(LegoCamera* cam, real32 minYaw, real32 maxYaw);
// <LegoRR.exe @00436b75>
void __cdecl Camera_SetRotation(LegoCamera* cam, real32 yaw);
// <LegoRR.exe @00436c16>
void __cdecl Camera_AddRotation(LegoCamera* cam, real32 yawAmount);
// <LegoRR.exe @00436c3a>
void __cdecl Camera_SetZoomRange(LegoCamera* cam, real32 minDist, real32 maxDist);
// <LegoRR.exe @00436c6c>
void __cdecl Camera_SetZoom(LegoCamera* cam, real32 dist);
// <LegoRR.exe @00436cc7>
void __cdecl Camera_AddZoom(LegoCamera* cam, real32 distAmount);
// <LegoRR.exe @00436ceb>
void __cdecl Camera_AddTranslation2D(LegoCamera* cam, real32 translateX, real32 translateY);
// <LegoRR.exe @00436d0b>
void __cdecl Camera_GetTopdownPosition(LegoCamera* cam, Vector3F* out_position);
// <LegoRR.exe @00436d2d>
void __cdecl Camera_SetTopdownPosition(LegoCamera* cam, real32 x, real32 y);
// <LegoRR.exe @00436d55>
bool32 __cdecl Camera_GetTopdownWorldPos(LegoCamera* cam, Map3D* surfMap, Vector3F* out_worldPos);
// <LegoRR.exe @00436d9b>
real32 __cdecl Camera_GetRotation(LegoCamera* cam);
// <LegoRR.exe @00436da9>
void __cdecl Camera_Move(LegoCamera* cam, Vector3F* ref_dir, real32 elapsedAbs);
// <LegoRR.exe @00436ee0>
void __cdecl LegoObject_Initialise(void);
// <LegoRR.exe @00437310>
void __cdecl LegoObject_Shutdown(void);
// <LegoRR.exe @00437370>
void __cdecl Object_Save_CopyStruct18(SaveStruct_18* out_saveStruct18);
// <LegoRR.exe @00437390>
void __cdecl Object_Save_OverwriteStruct18(SaveStruct_18* saveStruct18);
// <LegoRR.exe @004373c0>
sint32 __cdecl LegoObject_GetObjectsBuilt(LegoObject_Type objType, bool32 excludeToolStore);
// <LegoRR.exe @00437410>
void __cdecl Object_LoadToolTipIcons(Config* config);
// <LegoRR.exe @00437560>
void __cdecl LegoObject_CleanupLevel(void);
// <LegoRR.exe @004375c0>
void __cdecl LegoObject_Weapon_FUN_004375c0(LegoObject* liveObj, sint32 weaponID, real32 coef);
// <LegoRR.exe @00437690>
bool32 __cdecl LegoObject_DoOpeningClosing(LegoObject* liveObj, bool32 open);
// <LegoRR.exe @00437700>
void __cdecl LegoObject_CleanupObjectLevels(void);
// <LegoRR.exe @00437720>
uint32 __cdecl LegoObject_GetLevelObjectsBuilt(LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel, bool32 currentLevel);
// <LegoRR.exe @00437760>
uint32 __cdecl LegoObject_GetPreviousLevelObjectsBuilt(LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel);
// <LegoRR.exe @00437790>
void __cdecl LegoObject_IncLevelPathsBuilt(bool32 incCurrent);
// <LegoRR.exe @004377b0>
void __cdecl LegoObject_RemoveRouteToReferences(LegoObject* routeToObj);
// <LegoRR.exe @004377d0>
bool32 __cdecl LegoObject_Callback_RemoveRouteToReference(LegoObject* liveObj, LegoObject* routeToObj);
// <LegoRR.exe @00437800>
bool32 __cdecl LegoObject_Remove(LegoObject* liveObj);
// <LegoRR.exe @00437a70>
bool32 __cdecl LegoObject_RunThroughListsSkipUpgradeParts(LegoObject_RunThroughListsCallback callback, void* search);
// <LegoRR.exe @00437a90>
bool32 __cdecl LegoObject_RunThroughLists(LegoObject_RunThroughListsCallback callback, void* search, bool32 skipUpgradeParts);
// <LegoRR.exe @00437b40>
void __cdecl LegoObject_SetCustomName(LegoObject* liveObj, char* opt_customName);
// <LegoRR.exe @00437ba0>
void __cdecl HiddenObject_RemoveAll(void);
// <LegoRR.exe @00437c00>
void __cdecl HiddenObject_ExposeBlock(Point2I* blockPos);
// <LegoRR.exe @00437ee0>
void __cdecl HiddenObject_Add(void* objModel, LegoObject_Type objType, LegoObject_ID objID, Point2F* worldPos, real32 heading, real32 health, char* thisOLName, char* drivingOLName);
// <LegoRR.exe @00437f80>
bool32 __cdecl LegoObject_CanShootObject(LegoObject* liveObj);
// <LegoRR.exe @00437fc0>
LegoObject* __cdecl LegoObject_Create(sint32** objModel, LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @00438580>
LegoObject* __cdecl LegoObject_Create_internal(void);
// <LegoRR.exe @004385d0>
void __cdecl LegoObject_AddList(void);
// <LegoRR.exe @00438650>
sint32 __cdecl LegoObject_GetNumBuildingsTeleported(sint32* stack);
// <LegoRR.exe @00438660>
void __cdecl LegoObject_SetNumBuildingsTeleported(uint32 numTeleported);
// <LegoRR.exe @00438670>
void __cdecl LegoObject_SetCrystalPoweredColour(LegoObject* liveObj, bool32 powered);
// <LegoRR.exe @00438720>
void __cdecl LegoObject_FUN_00438720(LegoObject* liveObj);
// <LegoRR.exe @00438840>
void __cdecl LegoObject_SetPowerOn(LegoObject* liveObj, bool32 on);
// <LegoRR.exe @00438870>
bool32 __cdecl LegoObject_IsActive(LegoObject* liveObj, bool32 ignoreUnpowered);
// <LegoRR.exe @004388d0>
LegoObject* __cdecl LegoObject_CreateInWorld(void* objModel, LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel, real32 xPos, real32 yPos, real32 heading);
// <LegoRR.exe @00438930>
LegoObject* __cdecl LegoObject_FindPoweredBuildingAtBlockPos(Point2I* blockPos);
// <LegoRR.exe @00438970>
bool32 __cdecl LegoObject_Callback_FindPoweredBuildingAtBlockPos(LegoObject* liveObj, SearchObjectBlockXY_c* search);
// <LegoRR.exe @004389e0>
bool32 __cdecl LegoObject_AddThisDrainedCrystals(LegoObject* liveObj, sint32 crystalCount);
// <LegoRR.exe @00438a30>
bool32 __cdecl LegoObject_GetBuildingUpgradeCost(LegoObject* liveObj, uint32* optout_oreCost);
// <LegoRR.exe @00438ab0>
void __cdecl LegoObject_FUN_00438ab0(LegoObject* in_liveObj);
// <LegoRR.exe @00438b70>
bool32 __cdecl LegoObject_HasEnoughOreToUpgrade(LegoObject* liveObj, sint32 objLevel);
// <LegoRR.exe @00438c20>
undefined4 __cdecl LegoObject_Search_FUN_00438c20(LegoObject* opt_liveObj, bool32 param_2);
// <LegoRR.exe @00438ca0>
undefined4 __cdecl LegoObject_Search_FUN_00438ca0(LegoObject* liveObj, bool32 param_2);
// <LegoRR.exe @00438d20>
LegoObject* __cdecl LegoObject_FUN_00438d20(Point2I* blockPos, LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel);
// <LegoRR.exe @00438da0>
LegoObject* __cdecl LegoObject_FindResourceProcessingBuilding(LegoObject* liveObj, Point2I* blockPos, LegoObject_Type objType, uint32 objLevel);
// <LegoRR.exe @00438e40>
undefined4 __cdecl LegoObject_Search_FUN_00438e40(LegoObject* liveObj, undefined4 param_2);
// <LegoRR.exe @00438eb0>
undefined4 __cdecl LegoObject_Search_FUN_00438eb0(LegoObject* liveObj);
// <LegoRR.exe @00438f20>
undefined4 __cdecl LegoObject_Search_FUN_00438f20(LegoObject* liveObj);
// <LegoRR.exe @00438f90>
LegoObject* __cdecl LegoObject_FindBigTeleporter(Point2F* worldPos);
// <LegoRR.exe @00438ff0>
LegoObject* __cdecl LegoObject_FindSmallTeleporter(Point2F* worldPos);
// <LegoRR.exe @00439050>
LegoObject* __cdecl LegoObject_FindWaterTeleporter(Point2F* worldPos);
// <LegoRR.exe @004390b0>
LegoObject* __cdecl Level_GetBuildingAtPosition(Point2F* worldPos);
// <LegoRR.exe @00439110>
undefined4 __cdecl LegoObject_Search_FUN_00439110(LegoObject* liveObj, Point2F* opt_worldPos, LegoObject_AbilityFlags trainedType);
// <LegoRR.exe @00439190>
bool32 __cdecl LegoObject_HasTraining(LegoObject* liveObj, LegoObject_AbilityFlags training);
// <LegoRR.exe @00439220>
bool32 __cdecl LegoObject_IsDocksBuilding_Unk(LegoObject* liveObj);
// <LegoRR.exe @00439270>
bool32 __cdecl LegoObject_CallbackSearch_FUN_00439270(LegoObject* liveObj, sint32** search);
// <LegoRR.exe @004394c0>
bool32 __cdecl LegoObject_CanStoredObjectTypeBeSpawned(LegoObject_Type objType);
// <LegoRR.exe @00439500>
bool32 __cdecl LegoObject_Callback_CanSpawnStoredObjects(LegoObject* liveObj1, LegoObject* spawnObj);
// <LegoRR.exe @00439540>
void __cdecl LegoObject_PTL_GenerateFromCryOre(Point2I* blockPos);
// <LegoRR.exe @00439600>
void __cdecl LegoObject_PTL_GenerateCrystalsAndOre(Point2I* blockPos, uint32 objLevel);
// <LegoRR.exe @00439630>
void __cdecl Level_GenerateCrystal(Point2I* blockPos, uint32 objLevel, Point2F* opt_worldPos, bool32 showInfoMessage);
// <LegoRR.exe @00439770>
void __cdecl Level_GenerateOre(Point2I* blockPos, uint32 objLevel, Point2F* opt_worldPos, bool32 showInfoMessage);
// <LegoRR.exe @004398a0>
char* __cdecl LegoObject_GetLangName(LegoObject* liveObj);
// <LegoRR.exe @00439980>
char* __cdecl Object_GetTypeName(LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @00439a50>
char* __cdecl Object_GetLangTheName(LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @00439b20>
char* __cdecl Object_GetLangName(LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @00439bf0>
void __cdecl LegoObject_GetTypeAndID(LegoObject* liveObj, LegoObject_Type* out_objType, LegoObject_ID* out_objID);
// <LegoRR.exe @00439c10>
void __cdecl Object_LoadToolNames(Config* config, char* gameName);
// <LegoRR.exe @00439c50>
void __cdecl LegoObject_RequestPowerGridUpdate(void);
// <LegoRR.exe @00439c80>
bool32 __cdecl LegoObject_VehicleMaxCarryChecksTime_FUN_00439c80(LegoObject* liveObj);
// <LegoRR.exe @00439ce0>
bool32 __cdecl LegoObject_TryCollectObject(LegoObject* liveObj, LegoObject* targetObj);
// <LegoRR.exe @00439e40>
bool32 __cdecl LegoObject_FUN_00439e40(LegoObject* liveObj, LegoObject* otherObj);
// <LegoRR.exe @00439e90>
bool32 __cdecl LegoObject_FUN_00439e90(LegoObject* liveObj, LegoObject* targetObj, bool32 param_3);
// <LegoRR.exe @00439f40>
void __cdecl LegoObject_CompleteVehicleUpgrade(LegoObject* liveObj);
// <LegoRR.exe @00439f90>
bool32 __cdecl LegoObject_SetLevel(LegoObject* liveObj, uint32 newLevel);
// <LegoRR.exe @00439fb0>
bool32 __cdecl LegoObject_IsSmallTeleporter(LegoObject* liveObj);
// <LegoRR.exe @00439fd0>
bool32 __cdecl LegoObject_IsBigTeleporter(LegoObject* liveObj);
// <LegoRR.exe @00439ff0>
bool32 __cdecl LegoObject_IsWaterTeleporter(LegoObject* liveObj);
// <LegoRR.exe @0043a010>
bool32 __cdecl LegoObject_UnkGetTerrainCrossBlock_FUN_0043a010(LegoObject* liveObj, Point2I* optout_blockPos);
// <LegoRR.exe @0043a0d0>
bool32 __cdecl LegoObject_UnkGetTerrainGetOutAtLandBlock_FUN_0043a0d0(LegoObject* liveObj, Point2I* out_blockPos);
// <LegoRR.exe @0043a100>
bool32 __cdecl LegoObject_CheckUnkGetInAtLand_FUN_0043a100(LegoObject* liveObj, Point2I* blockPos);
// <LegoRR.exe @0043a130>
void __cdecl LegoObject_DropCarriedObject(LegoObject* liveObj, bool32 putAway);
// <LegoRR.exe @0043a3e0>
bool32 __cdecl LegoObject_TryRequestOrDumpCarried(LegoObject* liveObj, Point2I* blockPos, Point2F* worldPos, bool32 place, bool32 setRouteFlag8);
// <LegoRR.exe @0043a5c0>
bool32 __cdecl LegoObject_TryDepositCarried(LegoObject* liveObj, LegoObject* destObj);
// <LegoRR.exe @0043a8b0>
Container* __cdecl LegoObject_GetDepositNull(LegoObject* liveObj);
// <LegoRR.exe @0043a910>
LegoObject* __cdecl LegoObject_FUN_0043a910(LegoObject* liveObj, LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel);
// <LegoRR.exe @0043aa80>
bool32 __cdecl LegoObject_CanSpawnCarryableObject(LegoObject* liveObj, LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @0043ab10>
void __cdecl LegoObject_PutAwayCarriedObject(LegoObject* liveObj, LegoObject* carriedObj);
// <LegoRR.exe @0043abb0>
void __cdecl LegoObject_AddCrystalsStored(LegoObject* unused_liveObj, uint32 crystalAmount);
// <LegoRR.exe @0043abd0>
void __cdecl LegoObject_AddOreStored(LegoObject* liveObj_unused, uint32 oreAmount);
// <LegoRR.exe @0043abf0>
void __cdecl LegoObject_WaterVehicle_Unregister(LegoObject* liveObj);
// <LegoRR.exe @0043ac20>
void __cdecl LegoObject_WaterVehicle_Register(LegoObject* liveObj);
// <LegoRR.exe @0043aca0>
void __cdecl LegoObject_RegisterVehicle__callsForWater(LegoObject* liveObj);
// <LegoRR.exe @0043acb0>
void __cdecl LegoObject_FUN_0043acb0(LegoObject* liveObj1, LegoObject* liveObj2);
// <LegoRR.exe @0043ad70>
void __cdecl LegoObject_RockMonster_FUN_0043ad70(LegoObject* liveObj);
// <LegoRR.exe @0043aeb0>
void __cdecl LegoObject_FUN_0043aeb0(LegoObject* liveObj);
// <LegoRR.exe @0043af50>
bool32 __cdecl LegoObject_Callback_TryStampMiniFigureWithCrystal(LegoObject* targetObj, LegoObject* stamperObj);
// <LegoRR.exe @0043b010>
LegoObject* __cdecl LegoObject_TryGenerateSlug(LegoObject* originObj, LegoObject_ID objID);
// <LegoRR.exe @0043b160>
LegoObject* __cdecl LegoObject_TryGenerateRMonsterAtRandomBlock(void);
// <LegoRR.exe @0043b1f0>
LegoObject* __cdecl LegoObject_TryGenerateRMonster(CreatureModel* objModel, LegoObject_Type objType, LegoObject_ID objID, uint32 bx, uint32 by);
// <LegoRR.exe @0043b530>
void __cdecl LegoObject_UpdateAll(real32 elapsedGame);
// <LegoRR.exe @0043b5e0>
void __cdecl LegoObject_RemoveAll(void);
// <LegoRR.exe @0043b610>
bool32 __cdecl LegoObject_Callback_Remove(LegoObject* liveObj, void* data_unused);
// <LegoRR.exe @0043b620>
bool32 __cdecl LegoObject_DoPickSphereSelection(uint32 mouseX, uint32 mouseY, LegoObject** selectedObj);
// <LegoRR.exe @0043b670>
bool32 __cdecl LegoObject_Callback_PickSphereSelection(LegoObject* liveObj, SearchObjectMouseXY_c* search);
// <LegoRR.exe @0043b980>
void __cdecl LegoObject_DoDragSelection(Viewport* view, Point2F* dragStart, Point2F* dragEnd);
// <LegoRR.exe @0043ba30>
bool32 __cdecl LegoObject_CallbackDoSelection(LegoObject* liveObj, SearchViewportWindow_14* search);
// <LegoRR.exe @0043bae0>
void __cdecl LegoObject_SwapPolyFP(LegoObject* liveObj, uint32 cameraNo, bool32 on);
// <LegoRR.exe @0043bb10>
void __cdecl LegoObject_FP_SetRanges(LegoObject* liveObj, Container* cont, real32 medPolyRange, real32 highPolyRange, bool32 onCont);
// <LegoRR.exe @0043bb90>
bool32 __cdecl LegoObject_FP_Callback_SwapPolyMeshParts(LegoObject* liveObj, LiveObjectInfo* liveInfo);
// <LegoRR.exe @0043bdb0>
bool32 __cdecl LegoObject_Check_LotsOfFlags1AndFlags2_FUN_0043bdb0(LegoObject* liveObj);
// <LegoRR.exe @0043bde0>
void __cdecl LegoObject_FUN_0043bde0(LegoObject* liveObj);
// <LegoRR.exe @0043be80>
void __cdecl LegoObject_FinishEnteringWallHole(LegoObject* liveObj);
// <LegoRR.exe @0043bf00>
void __cdecl LegoObject_TeleportUp(LegoObject* liveObj);
// <LegoRR.exe @0043c4c0>
bool32 __cdecl LegoObject_CanSupportOxygenForType(LegoObject_Type consumerType, LegoObject_ID consumerID, LegoObject_Type producerType, LegoObject_ID producerID);
// <LegoRR.exe @0043c540>
bool32 __cdecl LegoObject_Callback_SumOfOxygenCoefs(LegoObject* liveObj, real32* oxygenCoef);
// <LegoRR.exe @0043c570>
void __cdecl LegoObject_UpdateAllRadarSurvey(real32 elapsedGame, bool32 isRadarMapView);
// <LegoRR.exe @0043c5b0>
bool32 __cdecl LegoObject_Callback_UpdateRadarSurvey(LegoObject* liveObj, bool32* pIsRadarMapView);
// <LegoRR.exe @0043c6a0>
bool32 __cdecl LegoObject_FUN_0043c6a0(LegoObject* liveObj);
// <LegoRR.exe @0043c700>
WeaponKnownType __cdecl LegoObject_GetEquippedBeam(LegoObject* liveObj);
// <LegoRR.exe @0043c750>
bool32 __cdecl LegoObject_FUN_0043c750(LegoObject* liveObj, LegoObject* routeToObject, WeaponKnownType knownWeapon);
// <LegoRR.exe @0043c780>
void __cdecl LegoObject_Proc_FUN_0043c780(LegoObject* liveObj);
// <LegoRR.exe @0043c7f0>
void __cdecl LegoObject_Proc_FUN_0043c7f0(LegoObject* liveObj);
// <LegoRR.exe @0043c830>
void __cdecl LegoObject_UpdatePowerConsumption(LegoObject* liveObj);
// <LegoRR.exe @0043c910>
bool32 __cdecl LegoObject_CheckCanSteal(LegoObject* liveObj);
// <LegoRR.exe @0043c970>
void __cdecl LegoObject_FUN_0043c970(LegoObject* liveObj, real32 elapsed);
// <LegoRR.exe @0043cad0>
bool32 __cdecl LegoObject_Callback_Update(LegoObject* liveObj, real32* pElapsed);
// <LegoRR.exe @0043f160>
void __cdecl LegoObject_ProcCarriedObjects_FUN_0043f160(LegoObject* in_liveObj);
// <LegoRR.exe @0043f3c0>
void __cdecl LegoObject_ClearFlags4_40_AndSameForObject2FC(LegoObject* unused_liveObj, LegoObject* liveObj);
// <LegoRR.exe @0043f3f0>
void __cdecl LegoObject_TriggerFrameCallback(Container* cont, void* data);
// <LegoRR.exe @0043f410>
bool32 __cdecl LegoObject_QueueTeleport(LegoObject* liveObj, LegoObject_Type objType, sint32 objID);
// <LegoRR.exe @0043f450>
void __cdecl LegoObject_FUN_0043f450(LegoObject* liveObj);
// <LegoRR.exe @0043f820>
bool32 __cdecl LegoObject_RemoveTeleportDownReference(LegoObject* teleportDownObj);
// <LegoRR.exe @0043f840>
bool32 __cdecl LegoObject_Callback_RemoveTeleportDownReference(LegoObject* liveObj, LegoObject* teleportDownObj);
// <LegoRR.exe @0043f870>
void __cdecl LegoObject_TrainMiniFigure_instantunk(LegoObject* liveObj, LegoObject_AbilityFlags trainFlags);
// <LegoRR.exe @0043f960>
void __cdecl LegoObject_AddDamage2(LegoObject* liveObj, real32 damage, bool32 showVisual, real32 elapsed);
// <LegoRR.exe @0043fa90>
void __cdecl LegoObject_UnkUpdateEnergyHealth(LegoObject* in_liveObj, real32 elapsed);
// <LegoRR.exe @0043fe00>
bool32 __cdecl LegoObject_MiniFigurePlayHurtSND(LegoObject* in_liveObj, real32 elapsed, real32 damage);
// <LegoRR.exe @0043fee0>
bool32 __cdecl LegoObject_FUN_0043fee0(LegoObject* carriedObj);
// <LegoRR.exe @00440080>
bool32 __cdecl LegoObject_UnkCarryingVehicle_FUN_00440080(LegoObject* liveObj);
// <LegoRR.exe @00440130>
bool32 __cdecl LegoObject_TryFindLoad_FUN_00440130(LegoObject* in_liveObj, LegoObject* targetObj);
// <LegoRR.exe @004402b0>
bool32 __cdecl LegoObject_TryDock_FUN_004402b0(LegoObject* in_liveObj);
// <LegoRR.exe @004403f0>
void __cdecl LegoObject_TryDock_AtBlockPos_FUN_004403f0(LegoObject* liveObj, Point2I* blockPos);
// <LegoRR.exe @00440470>
bool32 __cdecl LegoObject_FUN_00440470(LegoObject* liveObj, bool32 param_2);
// <LegoRR.exe @00440690>
bool32 __cdecl LegoObject_TryFindDriver_FUN_00440690(LegoObject* liveObj, LegoObject* drivableObj);
// <LegoRR.exe @00440a70>
void __cdecl LegoObject_DoDynamiteExplosionRadiusCallbacks(LegoObject* liveObj, real32 damageRadius, real32 maxDamage, real32 wakeRadius);
// <LegoRR.exe @00440ac0>
bool32 __cdecl LegoObject_Callback_DynamiteExplosion(LegoObject* liveObj, SearchDynamiteRadius* search);
// <LegoRR.exe @00440b80>
void __cdecl LegoObject_DoBirdScarerRadiusCallbacks(LegoObject* optor_liveObj, Point2F* optor_position, real32 radius);
// <LegoRR.exe @00440be0>
bool32 __cdecl LegoObject_Callback_BirdScarer(LegoObject* liveObj, SearchDynamiteRadius* search);
// <LegoRR.exe @00440ca0>
void __cdecl LegoObject_SetActivity(LegoObject* liveObj, Activity_Type activityType, uint32 repeatCount);
// <LegoRR.exe @00440cd0>
void __cdecl LegoObject_UpdateCarrying(LegoObject* in_liveObj);
// <LegoRR.exe @00440eb0>
void __cdecl LegoObject_InitBoulderMesh_FUN_00440eb0(LegoObject* liveObj, Container_Texture* contTexture);
// <LegoRR.exe @00440ef0>
bool32 __cdecl LegoObject_Route_ScoreNoCallback_FUN_00440ef0(LegoObject* liveObj, uint32 bx, uint32 by, uint32 bx2, uint32 by2, sint32** out_param_6, sint32** out_param_7, sint32* out_count);
// <LegoRR.exe @00440f30>
bool32 __cdecl LegoObject_Route_ScoreSub_FUN_00440f30(LegoObject* liveObj, uint32 bx, uint32 by, uint32 bx2, uint32 by2, uint32** out_param_6, uint32** out_param_7, uint32* out_count, undefined* callback, void* data);
// <LegoRR.exe @004413b0>
bool32 __cdecl LegoObject_Route_Score_FUN_004413b0(LegoObject* liveObj, uint32 bx, uint32 by, uint32 bx2, uint32 by2, sint32** out_new_bxs, sint32** out_new_bys, sint32* out_count, void* callback, void* data);
// <LegoRR.exe @004419c0>
bool32 __cdecl LegoObject_Route_AllocPtr_FUN_004419c0(LegoObject* liveObj, uint32 count, real32* param_3, real32* param_4, real32* param_5);
// <LegoRR.exe @00441c00>
void __cdecl LegoObject_Route_End(LegoObject* liveObj, bool32 completed);
// <LegoRR.exe @00441df0>
void __cdecl LegoObject_Interrupt(LegoObject* liveObj, bool32 actStand, bool32 dropCarried);
// <LegoRR.exe @00442160>
void __cdecl LegoObject_DestroyBoulder_AndCreateExplode(LegoObject* liveObj);
// <LegoRR.exe @00442190>
bool32 __cdecl LegoObject_Proc_FUN_00442190(LegoObject* liveObj, LegoObject* targetObj, WeaponKnownType knownWeapon);
// <LegoRR.exe @00442390>
void __cdecl LegoObject_GetWeaponUnk(LegoObject* liveObj, WeaponKnownType knownWeapon);
// <LegoRR.exe @004424d0>
void __cdecl LegoObject_UnkActivityCrumble_FUN_004424d0(LegoObject* liveObj);
// <LegoRR.exe @00442520>
void __cdecl LegoObject_GetPosition(LegoObject* liveObj, real32* out_x, real32* out_y);
// <LegoRR.exe @00442560>
void __cdecl LegoObject_GetFaceDirection(LegoObject* liveObj, Point2F* out_direction);
// <LegoRR.exe @004425c0>
void __cdecl LegoObject_UnkUpdateOrientation(LegoObject* liveObj, real32 theta, Vector3F* opt_vecDir);
// <LegoRR.exe @00442740>
real32 __cdecl LegoObject_GetHeading(LegoObject* liveObj);
// <LegoRR.exe @004427b0>
bool32 __cdecl LegoObject_GetBlockPos(LegoObject* liveObj, sint32* out_bx, sint32* out_by);
// <LegoRR.exe @00442800>
real32 __cdecl LegoObject_GetWorldZCallback(real32 xPos, real32 yPos, Map3D* map);
// <LegoRR.exe @00442820>
real32 __cdecl LegoObject_GetWorldZCallback_Lake(real32 xPos, real32 yPos, Map3D* map);
// <LegoRR.exe @004428b0>
void __cdecl LegoObject_UpdateRoutingVectors_FUN_004428b0(LegoObject* liveObj, real32 xDir, real32 yDir);
// <LegoRR.exe @00442b60>
void __cdecl LegoObject_SetPositionAndHeading(LegoObject* liveObj, real32 xPos, real32 yPos, real32 theta, bool32 assignHeading);
// <LegoRR.exe @00442dd0>
sint32 __cdecl LegoObject_FP_UpdateMovement(LegoObject* liveObj, real32 elapsed, real32* out_transSpeed);
// <LegoRR.exe @00443240>
void __cdecl LegoObject_UpdateWorldStickyPosition(LegoObject* liveObj, real32 elapsed);
// <LegoRR.exe @004437d0>
void __cdecl LegoObject_UpdateDriverStickyPosition(LegoObject* liveObj);
// <LegoRR.exe @00443930>
bool32 __cdecl LegoObject_TryWaiting(LegoObject* liveObj);
// <LegoRR.exe @004439b0>
bool32 __cdecl LegoObject_IsRockMonsterCanGather(LegoObject* liveObj);
// <LegoRR.exe @004439d0>
bool32 __cdecl LegoObject_FUN_004439d0(LegoObject* liveObj, Point2I* blockPos, Point2I* out_blockPos, undefined4 unused);
// <LegoRR.exe @00443ab0>
void __cdecl LegoObject_RockMonster_DoWakeUp(LegoObject* liveObj);
// <LegoRR.exe @00443b00>
bool32 __cdecl LegoObject_CheckBlock_FUN_00443b00(LegoObject* liveObj, Point2I* blockPos, bool32* pAllowWall);
// <LegoRR.exe @00443b70>
void __cdecl LegoObject_Route_UpdateMovement(LegoObject* liveObj, real32 elapsed);
// <LegoRR.exe @00444360>
void __cdecl LegoObject_TryDock_AtObject2FC(LegoObject* liveObj);
// <LegoRR.exe @004443b0>
void __cdecl LegoObject_UpdateCarryingEnergy(LegoObject* liveObj, real32 elapsed);
// <LegoRR.exe @00444520>
bool32 __cdecl LegoObject_FUN_00444520(LegoObject* liveObj);
// <LegoRR.exe @00444720>
void __cdecl LegoObject_TryRunAway(LegoObject* liveObj, Point2F* dir);
// <LegoRR.exe @004448e0>
void __cdecl LegoObject_DoSlip(LegoObject* liveObj);
// <LegoRR.exe @00444940>
bool32 __cdecl LegoObject_RoutingUnk_FUN_00444940(LegoObject* liveObj, bool32 useRoutingPos, bool32 flags3_8, bool32 notFlags1_10000);
// <LegoRR.exe @00445270>
void __cdecl LegoObject_FaceTowardsCamera(LegoObject* liveObj, Point2F* camWorldPos);
// <LegoRR.exe @004454a0>
void __cdecl LegoObject_Route_CurveSolid_FUN_004454a0(LegoObject* liveObj);
// <LegoRR.exe @00445600>
bool32 __cdecl LegoObject_Callback_CurveSolidCollRadius_FUN_00445600(LegoObject* liveObj, LegoObject** pOtherObj);
// <LegoRR.exe @00445860>
bool32 __cdecl LegoObject_Route_SolidBlockCheck_FUN_00445860(LegoObject* liveObj);
// <LegoRR.exe @004459a0>
void __cdecl LegoObject_FUN_004459a0(LegoObject* liveObj, real32 elapsed);
// <LegoRR.exe @00445a30>
bool32 __cdecl LegoObject_Callback_ScareTrainedMiniFiguresAwayFromTickingDynamite(LegoObject* liveObj, LegoObject* otherObj);
// <LegoRR.exe @00445af0>
bool32 __cdecl LegoObject_Callback_FUN_00445af0(LegoObject* liveObj, LegoObject* otherObj);
// <LegoRR.exe @00446030>
LegoObject* __cdecl LegoObject_DoCollisionCallbacks_FUN_00446030(LegoObject* liveObj, Point2F* param_2, real32 param_3, bool32 param_4);
// <LegoRR.exe @004460b0>
bool32 __cdecl LegoObject_CallbackCollisionRadius_FUN_004460b0(LegoObject* in_liveObj, sint32* search);
// <LegoRR.exe @004463b0>
bool32 __cdecl LegoObject_CallbackCollisionBox_FUN_004463b0(LegoObject* in_liveObj, SearchCollision_14* search);
// <LegoRR.exe @004468d0>
void __cdecl LegoObject_CalculateSpeeds(LegoObject* liveObj, real32 elapsed, real32* out_routeSpeed, real32* out_transSpeed);
// <LegoRR.exe @00446b80>
bool32 __cdecl LegoObject_RoutingPtr_Realloc_FUN_00446b80(LegoObject* liveObj, uint32 bx, uint32 by);
// <LegoRR.exe @00446c80>
bool32 __cdecl LegoObject_BlockRoute_FUN_00446c80(LegoObject* liveObj, uint32 bx, uint32 by, bool32 useWideRange, Direction* optout_direction, bool32 countIs8);
// <LegoRR.exe @00447100>
bool32 __cdecl LegoObject_RouteToDig_FUN_00447100(LegoObject* liveObj, uint32 bx, uint32 by, bool32 tunnelDig);
// <LegoRR.exe @00447390>
bool32 __cdecl LegoObject_PTL_GatherRock(LegoObject* liveObj);
// <LegoRR.exe @00447470>
bool32 __cdecl LegoObject_RoutingNoCarry_FUN_00447470(LegoObject* liveObj, uint32 bx, uint32 by, LegoObject* boulderObj);
// <LegoRR.exe @004474d0>
bool32 __cdecl LegoObject_PTL_AttackBuilding(LegoObject* liveObj1, LegoObject* targetObj);
// <LegoRR.exe @00447670>
sint32 __cdecl LegoObject_FUN_00447670(LegoObject* in_liveObj, sint32 bx, sint32 by, LegoObject* liveObj2);
// <LegoRR.exe @004477b0>
void __cdecl LegoObject_FUN_004477b0(LegoObject* liveObj);
// <LegoRR.exe @00447880>
sint32 __cdecl LegoObject_FUN_00447880(LegoObject* in_liveObj);
// <LegoRR.exe @004479f0>
bool32 __cdecl LegoObject_Add25EnergyAndSetHealth(LegoObject* liveObj);
// <LegoRR.exe @00447a40>
void __cdecl LegoObject_FUN_00447a40(LegoObject* liveObj);
// <LegoRR.exe @00447a90>
void __cdecl LegoObject_Routing_FUN_00447a90(LegoObject* liveObj);
// <LegoRR.exe @00447bc0>
void __cdecl LegoObject_DoBuildingsCallback_AttackByBoulder(LegoObject* liveObj);
// <LegoRR.exe @00447be0>
bool32 __cdecl LegoObject_CallbackBoulderAttackBuilding_FUN_00447be0(LegoObject* liveObj, LegoObject* buildingLiveObj);
// <LegoRR.exe @00447c10>
void __cdecl LegoObject_Hit(LegoObject* liveObj, Point2F* dir, bool32 reactToHit);
// <LegoRR.exe @00447dc0>
void __cdecl LegoObject_TeleportDownBuilding(LegoObject* liveObj);
// <LegoRR.exe @00447df0>
real32 __cdecl LegoObject_MoveAnimation(LegoObject* liveObj, real32 elapsed);
// <LegoRR.exe @00447f00>
bool32 __cdecl LegoObject_UpdateActivityChange(LegoObject* liveObj);
// <LegoRR.exe @00448160>
void __cdecl LegoObject_SimpleObject_FUN_00448160(LegoObject* in_liveObj, real32 elapsed);
// <LegoRR.exe @00448a80>
void __cdecl LegoObject_Debug_DropActivateDynamite(LegoObject* liveObj);
// <LegoRR.exe @00448ac0>
bool32 __cdecl LegoObject_TryDynamite_FUN_00448ac0(LegoObject* liveObj, Point2I* blockPos);
// <LegoRR.exe @00448b40>
bool32 __cdecl LegoObject_PlaceCarriedBirdScarerAt(LegoObject* liveObj, Point2I* blockPos);
// <LegoRR.exe @00448c60>
bool32 __cdecl LegoObject_PlaceBirdScarer_AndTickDown(LegoObject* liveObj);
// <LegoRR.exe @00448d20>
bool32 __cdecl LegoObject_TryElecFence_FUN_00448d20(LegoObject* liveObj, Point2I* blockPos);
// <LegoRR.exe @00448f10>
bool32 __cdecl LegoObject_TryBuildPath_FUN_00448f10(LegoObject* liveObj);
// <LegoRR.exe @00448f50>
bool32 __cdecl LegoObject_TryUpgrade_FUN_00448f50(LegoObject* in_liveObj, LegoObject* targetObj, sint32 targetObjLevel);
// <LegoRR.exe @00449170>
bool32 __cdecl LegoObject_TryTrain_FUN_00449170(LegoObject* liveObj, LegoObject* targetObj, bool32 set_0xE_or0xF);
// <LegoRR.exe @004492d0>
bool32 __cdecl LegoObject_TryRechargeCarried(LegoObject* liveObj);
// <LegoRR.exe @00449360>
bool32 __cdecl LegoObject_TryRepairDrainObject(LegoObject* liveObj, LegoObject* targetObj, bool32 setRouteFlag20, bool32 setLive4Flag400000);
// <LegoRR.exe @00449500>
bool32 __cdecl LegoObject_TryReinforceBlock(LegoObject* liveObj, Point2I* blockPos);
// <LegoRR.exe @00449570>
bool32 __cdecl LegoObject_TryClear_FUN_00449570(LegoObject* liveObj, Point2I* blockPos);
// <LegoRR.exe @004496a0>
bool32 __cdecl LegoObject_MiniFigureHasBeamEquipped(LegoObject* liveObj);
// <LegoRR.exe @004496f0>
bool32 __cdecl LegoObject_TryAttackRockMonster_FUN_004496f0(LegoObject* liveObj, LegoObject* targetObj);
// <LegoRR.exe @004497e0>
bool32 __cdecl LegoObject_TryAttackObject_FUN_004497e0(LegoObject* in_liveObj, LegoObject* targetObj);
// <LegoRR.exe @004498d0>
bool32 __cdecl LegoObject_TryAttackPath_FUN_004498d0(LegoObject* liveObj, Point2I* blockPos);
// <LegoRR.exe @004499c0>
bool32 __cdecl LegoObject_TryDepart_FUN_004499c0(LegoObject* liveObj);
// <LegoRR.exe @00449b40>
bool32 __cdecl LegoObject_RouteToFaceBlock(LegoObject* liveObj, uint32 bx, uint32 by, real32 distFrom);
// <LegoRR.exe @00449c40>
bool32 __cdecl LegoObject_Update_Reinforcing(LegoObject* liveObj, real32 unused_elapsed, bool32* out_finished);
// <LegoRR.exe @00449d30>
void __cdecl LegoObject_GoEat_unk(LegoObject* liveObj);
// <LegoRR.exe @00449d80>
bool32 __cdecl LegoObject_TryGoEat_FUN_00449d80(LegoObject* liveObj1, LegoObject* liveObj2);
// <LegoRR.exe @00449ec0>
void __cdecl LegoObject_HideAllCertainObjects(void);
// <LegoRR.exe @00449ee0>
void __cdecl LegoObject_FlocksCallback_FUN_00449ee0(Flocks* flockData, FlocksItem* subdata, void* data);
// <LegoRR.exe @00449f90>
void __cdecl LegoObject_Hide2(LegoObject* liveObj, bool32 hide2);
// <LegoRR.exe @00449fb0>
bool32 __cdecl LegoObject_Callback_HideCertainObjects(LegoObject* liveObj, void* unused);
// <LegoRR.exe @0044a210>
void __cdecl LegoObject_Hide(LegoObject* liveObj, bool32 hide);
// <LegoRR.exe @0044a2b0>
bool32 __cdecl LegoObject_IsHidden(LegoObject* liveObj);
// <LegoRR.exe @0044a330>
void __cdecl LegoObject_FP_GetPositionAndHeading(LegoObject* liveObj, sint32 cameraFrame, Vector3F* out_worldPos, Vector3F* out_dir);
// <LegoRR.exe @0044a4c0>
Container* __cdecl LegoObject_GetActivityContainer(LegoObject* liveObj);
// <LegoRR.exe @0044a560>
bool32 __cdecl LegoObject_GetDrillNullPosition(LegoObject* liveObj, real32* out_xPos, real32* out_yPos);
// <LegoRR.exe @0044a5d0>
void __cdecl LegoObject_FP_Move(LegoObject* liveObj, sint32 forward, sint32 strafe, real32 rotate);
// <LegoRR.exe @0044a650>
void __cdecl LegoObject_RegisterRechargeSeam(Point2I* blockPos);
// <LegoRR.exe @0044a690>
bool32 __cdecl LegoObject_FindNearestRechargeSeam(LegoObject* liveObj, Point2I* optout_blockPos);
// <LegoRR.exe @0044a770>
void __cdecl LegoObject_RegisterSlimySlugHole(Point2I* blockPos);
// <LegoRR.exe @0044a7b0>
bool32 __cdecl LegoObject_FindNearestSlugHole(LegoObject* liveObj, Point2I* optout_blockPos);
// <LegoRR.exe @0044a890>
bool32 __cdecl LegoObject_FindNearestWall(LegoObject* liveObj, sint32* out_bx, sint32* out_by, bool32 min1BlockDist, bool32 allowCorner, bool32 allowReinforced);
// <LegoRR.exe @0044aa60>
bool32 __cdecl LegoObject_QsortCompareWallDistances(Vector3F* a, Vector3F* b);
// <LegoRR.exe @0044aa90>
MeshLOD* __cdecl LegoObject_LoadMeshLOD(Config* act, char* gameName, char* dirname, LOD_PolyLevel polyLOD, uint32 numCameraFrames);
// <LegoRR.exe @0044abd0>
bool32 __cdecl LegoObject_UnkBuildingPlaceDirection(LegoObject_Type objType, sint32 objID, bool32 param_3, bool32 param_4, Point2F* mouseWorldPos, uint32 mouseBlockX, uint32 mouseBlockY, bool32 param_8, SelectPlace* selectPlace);
// <LegoRR.exe @0044af80>
void __cdecl LegoObject_LoadObjTtsSFX(Config* config, char* gameName);
// <LegoRR.exe @0044b040>
sint32 __cdecl LegoObject_GetObjTtSFX(LegoObject* liveObj);
// <LegoRR.exe @0044b080>
void __cdecl LegoObject_SetLevelEnding(bool32 ending);
// <LegoRR.exe @0044b0a0>
void __cdecl LegoObject_FUN_0044b0a0(LegoObject* liveObj);
// <LegoRR.exe @0044b110>
void __cdecl LegoObject_SpawnDropCrystals_FUN_0044b110(LegoObject* in_liveObj, sint32 crystalCount, bool32 param_3);
// <LegoRR.exe @0044b250>
void __cdecl LegoObject_CallsSpawnDropCrystals_FUN_0044b250(LegoObject* liveObj);
// <LegoRR.exe @0044b270>
void __cdecl LegoObject_GenerateTinyRMs_FUN_0044b270(LegoObject* in_liveObj);
// <LegoRR.exe @0044b400>
void __cdecl LegoObject_GenerateSmallSpiders(uint32 bx, uint32 by, uint32 randSeed);
// <LegoRR.exe @0044b510>
void __cdecl LegoObject_DoThrowLegoman(LegoObject* liveObj, LegoObject* thrownObj);
// <LegoRR.exe @0044b610>
bool32 __cdecl LegoObject_Tool_IsBeamWeapon(LegoObject_ToolType toolType);
// <LegoRR.exe @0044b630>
void __cdecl LegoObject_MiniFigure_EquipTool(LegoObject* liveObj, LegoObject_ToolType toolType);
// <LegoRR.exe @0044b740>
bool32 __cdecl LegoObject_HasToolEquipped(LegoObject* liveObj, LegoObject_ToolType toolType);
// <LegoRR.exe @0044b780>
bool32 __cdecl LegoObject_TaskHasTool_FUN_0044b780(LegoObject* in_liveObj, AITask_Type taskType);
// <LegoRR.exe @0044b7c0>
sint32 __cdecl LegoObject_DoGetTool(LegoObject* liveObj, LegoObject_ToolType toolType);
// <LegoRR.exe @0044b940>
void __cdecl LegoObject_Flocks_Initialise(LegoObject* in_liveObj);
// <LegoRR.exe @0044ba60>
void __cdecl LegoObject_FlocksMatrix_FUN_0044ba60(Container* cont, Matrix4F* ref_matrix, real32 scalar);
// <LegoRR.exe @0044bb10>
void __cdecl LegoObject_Flocks_Callback_SubdataOrientationAnim(Flocks* flocksData, FlocksItem* subdata, real32* pElapsed);
// <LegoRR.exe @0044bd70>
void __cdecl LegoObject_Flocks_Container_ReleaseCallback(Flocks* flockData, FlocksItem* subdata, void* data);
// <LegoRR.exe @0044bda0>
void __cdecl LegoObject_Flocks_Free(Flocks* flockData);
// <LegoRR.exe @0044bdf0>
void __cdecl LegoObject_Flocks_SetParameters(LegoObject* liveObj, bool32 additive);
// <LegoRR.exe @0044bef0>
void __cdecl LegoObject_Flocks_FUN_0044bef0(LegoObject* liveObj, real32 elapsed);
// <LegoRR.exe @0044c0f0>
void __cdecl LegoObject_FlocksDestroy(LegoObject* liveObj);
// <LegoRR.exe @0044c1c0>
void __cdecl LegoObject_Flocks_Update_FUN_0044c1c0(real32* pElapsed);
// <LegoRR.exe @0044c290>
bool32 __cdecl LegoObject_DestroyRockMonster_FUN_0044c290(LegoObject* liveObj);
// <LegoRR.exe @0044c2f0>
bool32 __cdecl LegoObject_Freeze(LegoObject* liveObj, real32 freezerTime);
// <LegoRR.exe @0044c3d0>
void __cdecl LegoObject_FUN_0044c3d0(LegoObject* liveObj);
// <LegoRR.exe @0044c410>
bool32 __cdecl LegoObject_Push(LegoObject* liveObj, Point2F* pushVec2D, real32 pushDist);
// <LegoRR.exe @0044c470>
void __cdecl LegoObject_UpdatePushing(LegoObject* liveObj, real32 elapsed);
// <LegoRR.exe @0044c760>
void __cdecl LegoObject_TryEnterLaserTrackerMode(LegoObject* liveObj);
// <LegoRR.exe @0044c7c0>
bool32 __cdecl LegoObject_Callback_UnkLaserTrackerToggleUnset_FUN_0044c7c0(LegoObject* liveObj, void* unused);
// <LegoRR.exe @0044c7f0>
bool32 __cdecl LegoObject_MiniFigureHasBeamEquipped2(LegoObject* liveObj);
// <LegoRR.exe @0044c810>
void __cdecl LegoObject_CameraCycleUnits(void);
// <LegoRR.exe @0044c8b0>
bool32 __cdecl LegoObject_Callback_CameraCycleFindUnit(LegoObject* liveObj, bool32* opt_pNoBuildings);
// <LegoRR.exe @0044c9d0>
void __cdecl LightEffects_Initialise(Container* rootSpotlight, Container* rootLight, real32 initialRed, real32 initialGreen, real32 initialBlue);
// <LegoRR.exe @0044ca20>
void __cdecl LightEffects_ResetColor(void);
// <LegoRR.exe @0044ca50>
void __cdecl LightEffects_SetDisabled(bool32 isDisabled);
// <LegoRR.exe @0044ca80>
bool32 __cdecl LightEffects_Load(Config* config, char* gameName);
// <LegoRR.exe @0044cab0>
bool32 __cdecl LightEffects_LoadBlink(Config* config, char* gameName);
// <LegoRR.exe @0044cc30>
void __cdecl LightEffects_SetBlink(real32 redMax, real32 greenMax, real32 blueMax, real32 changeMax, real32 waitMin, real32 waitMax);
// <LegoRR.exe @0044cc80>
bool32 __cdecl LightEffects_LoadFade(Config* config, char* gameName);
// <LegoRR.exe @0044ced0>
void __cdecl LightEffects_SetFade(real32 redMin, real32 greenMin, real32 blueMin, real32 redMax, real32 greenMax, real32 blueMax, real32 waitMin, real32 waitMax, real32 speedMin, real32 speedMax, real32 holdMin, real32 holdMax);
// <LegoRR.exe @0044cf60>
bool32 __cdecl LightEffects_LoadMove(Config* config, char* gameName);
// <LegoRR.exe @0044d1b0>
void __cdecl LightEffects_SetMove(real32 waitMin, real32 waitMax, real32 speedMin, real32 speedMax, real32 distMin, real32 distMax, real32 limitX, real32 limitY, real32 limitZ);
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
Map3D* __cdecl Map3D_Create(Container* root, char* filename, real32 blockSize, real32 roughLevel);
// <LegoRR.exe @0044e790>
void __cdecl Map3D_InitRoughness(Map3D* map);
// <LegoRR.exe @0044e930>
void __cdecl Map3D_Remove(Map3D* map);
// <LegoRR.exe @0044e970>
void __cdecl Map3D_SetTextureNoFade(Map3D* map, SurfaceTexture texture);
// <LegoRR.exe @0044e990>
void __cdecl Map3D_SetBlockFadeInTexture(Map3D* map, sint32 bx, sint32 by, SurfaceTexture newTexture, uint8 direction);
// <LegoRR.exe @0044eb20>
bool32 __cdecl Map3D_IsBlockMeshHidden(Map3D* map, sint32 bx, sint32 by);
// <LegoRR.exe @0044eb40>
void __cdecl Map3D_UpdateAllBlockNormals(Map3D* map);
// <LegoRR.exe @0044eb80>
bool32 __cdecl Map3D_CheckBuildingTolerance(Map3D* map, Point2I* shapePoints, uint32 shapeCount, real32 buildTolerance, real32 buildMaxVariation);
// <LegoRR.exe @0044ed90>
void __cdecl Map3D_FlattenShapeVertices(Map3D* map, Point2I* shapePoints, uint32 shapeCount, real32 mult_4_0);
// <LegoRR.exe @0044f0b0>
void __cdecl Map3D_SetBlockRotated(Map3D* map, uint32 bx, uint32 by, bool32 on);
// <LegoRR.exe @0044f270>
void __cdecl Map3D_SetBlockVertexModified(Map3D* map, uint32 vx, uint32 vy);
// <LegoRR.exe @0044f2b0>
void __cdecl Map3D_Update(Map3D* map, real32 elapsedGame);
// <LegoRR.exe @0044f350>
void __cdecl Map3D_UpdateFadeInTransitions(Map3D* map, real32 elapsedGame);
// <LegoRR.exe @0044f460>
void __cdecl Map3D_AddTextureMapping(Map3D* map, SurfaceTexture texA, SurfaceTexture texB);
// <LegoRR.exe @0044f4e0>
void __cdecl Map3D_SetTextureSet(Map3D* map, Detail_TextureSet* tset);
// <LegoRR.exe @0044f4f0>
void __cdecl Map3D_SetBlockTexture(Map3D* map, uint32 bx, uint32 by, SurfaceTexture newTexture, uint8 direction);
// <LegoRR.exe @0044f640>
void __cdecl Map3D_MoveBlockVertices(Map3D* map, uint32 bx, uint32 by, real32 zDist);
// <LegoRR.exe @0044f750>
void __cdecl Map3D_SetPerspectiveCorrectionAll(Map3D* map, bool32 on);
// <LegoRR.exe @0044f7a0>
WallHighlightType __cdecl Map3D_SetBlockHighlight(Map3D* map, sint32 bx, sint32 by, WallHighlightType highlightType);
// <LegoRR.exe @0044f800>
WallHighlightType __cdecl Map3D_GetBlockHighlight(Map3D* map, sint32 bx, sint32 by);
// <LegoRR.exe @0044f830>
void __cdecl Map3D_ClearBlockHighlight(Map3D* map, sint32 bx, sint32 by);
// <LegoRR.exe @0044f880>
void __cdecl Map3D_Block_SetColour(Map3D* map, sint32 bx, sint32 by, bool32 setColour, real32 r, real32 g, real32 b);
// <LegoRR.exe @0044f900>
bool32 __cdecl Map3D_BlockToWorldPos(Map3D* map, uint32 bx, uint32 by, real32* out_x, real32* out_y);
// <LegoRR.exe @0044f990>
bool32 __cdecl Map3D_WorldToBlockPos_NoZ(Map3D* map, real32 in_x, real32 in_y, sint32* out_bx, sint32* out_by);
// <LegoRR.exe @0044f9c0>
bool32 __cdecl Map3D_WorldToBlockPos(Map3D* map, real32 in_x, real32 in_y, sint32* out_bx, sint32* out_by, real32* out_unk_z);
// <LegoRR.exe @0044fad0>
void __cdecl Map3D_FUN_0044fad0(Map3D* map, real32 in_x, real32 in_y, sint32* out_x, sint32* out_y);
// <LegoRR.exe @0044fb30>
bool32 __cdecl Map3D_FUN_0044fb30(Map3D* map, Point2F* wPos2D, Point2F* optout_blockPosf, Point2F* optout_centerDir);
// <LegoRR.exe @0044fc00>
real32 __cdecl Map3D_GetWorldZ(Map3D* map, real32 xPos, real32 yPos);
// <LegoRR.exe @0044fd70>
void __cdecl Map3D_FUN_0044fd70(Map3D* map, real32 in_x, real32 in_y, Vector3F* out_vector);
// <LegoRR.exe @0044fe50>
bool32 __cdecl Map3D_FUN_0044fe50(Map3D* map, real32 xPos, real32 yPos, bool32 diagonal, real32 unkMultiplier, real32* out_xOut, real32* out_yOut);
// <LegoRR.exe @00450130>
real32 __cdecl Map3D_UnkCameraXYFunc_RetZunk(Map3D* map, real32 xPos, real32 yPos);
// <LegoRR.exe @00450320>
void __cdecl Map3D_GetBlockFirstVertexPosition(Map3D* map, sint32 vx, sint32 vy, Vector3F* out_vector);
// <LegoRR.exe @00450390>
bool32 __cdecl Map3D_GetBlockVertexPositions(Map3D* map, uint32 bx, uint32 by, Vector3F* out_vertPoses);
// <LegoRR.exe @004504e0>
void __cdecl Map3D_GetBlockVertexPositions_NoRot(Map3D* map, uint32 bx, uint32 by, Vector3F* out_vertPoses);
// <LegoRR.exe @00450580>
bool32 __cdecl Map3D_IsInsideDimensions(Map3D* map, uint32 bx, uint32 by);
// <LegoRR.exe @004505a0>
bool32 __cdecl Map3D_GetIntersections(Map3D* map, Viewport* view, uint32 mouseX, uint32 mouseY, uint32* out_bx, uint32* out_by, Vector3F* out_vector);
// <LegoRR.exe @00450820>
bool32 __cdecl Map3D_Intersections_Sub1_FUN_00450820(Map3D* map, Vector3F* rayOrigin, Vector3F* ray, Vector3F* out_endPoint, Point2I* out_blockPos, sint32 unkCount);
// <LegoRR.exe @004508c0>
void __cdecl Map3D_AddVisibleBlocksInRadius_AndDoCallbacks(Map3D* map, sint32 bx, sint32 by, sint32 radius, XYCallback opt_callback);
// <LegoRR.exe @004509c0>
void __cdecl Map3D_HideBlock(Map3D* map, sint32 bx, sint32 by, bool32 hide);
// <LegoRR.exe @004509f0>
void __cdecl Map3D_AddVisibleBlock(Map3D* map, sint32 bx, sint32 by);
// <LegoRR.exe @00450a40>
void __cdecl Map3D_HideVisibleBlocksList(Map3D* map);
// <LegoRR.exe @00450a90>
void __cdecl Map3D_BlockVertexToWorldPos(Map3D* map, uint32 bx, uint32 by, real32* out_xPos, real32* out_yPos, real32* out_zPos);
// <LegoRR.exe @00450b50>
real32 __cdecl Map3D_BlockSize(Map3D* map);
// <LegoRR.exe @00450b60>
sint32 __cdecl Map3D_CheckRoutingComparison_FUN_00450b60(sint32 param_1, sint32 param_2, sint32 param_3, sint32 param_4);
// <LegoRR.exe @00450c20>
void __cdecl Map3D_SetBlockUVWobbles(Map3D* map, uint32 bx, uint32 by, bool32 on);
// <LegoRR.exe @00450d40>
void __cdecl Map3D_SetEmissive(Map3D* map, bool32 on);
// <LegoRR.exe @00450e20>
void __cdecl Map3D_UpdateTextureUVs(Map3D* map, real32 elapsedGame);
// <LegoRR.exe @004511f0>
void __cdecl Map3D_UpdateBlockNormals(Map3D* map, uint32 bx, uint32 by);
// <LegoRR.exe @00451440>
bool32 __cdecl Map3D_BlockPairHasTextureMatch(Map3D* map, uint32 bx1, uint32 by1, uint32 bx2, uint32 by2);
// <LegoRR.exe @004514f0>
void __cdecl Map3D_SetBlockDirectionNormal(Map3D* map, uint32 bx, uint32 by, Direction direction, Vector3F* normal);
// <LegoRR.exe @00451590>
bool32 __cdecl Map3D_GetBlockDirectionNormal(Map3D* map, uint32 bx, uint32 by, Direction direction, Vector3F* out_normal);
// <LegoRR.exe @00451710>
void __cdecl Map3D_MoveBlockDirectionVertex(Map3D* map, uint32 bx, uint32 by, Direction direction, Vector3F* vertDist);
// <LegoRR.exe @004517b0>
void __cdecl Map3D_GenerateBlockPlaneNormals(Map3D* map, uint32 bx, uint32 by);
// <LegoRR.exe @00451860>
void __cdecl Map3D_MapFileGetSpecs(MapFileInfo* mapFileInfo, uint32* out_width, uint32* out_height);
// <LegoRR.exe @00451880>
uint16 __cdecl Map3D_MapFileBlockValue(MapFileInfo* mapFile, uint32 bx, uint32 by, uint32 gridWidth);
// <LegoRR.exe @004518a0>
bool32 __cdecl Map3D_Intersections_Sub2_FUN_004518a0(Map3D* map, uint32 bx, uint32 by, Vector3F* rayOrigin, Vector3F* ray, Vector3F* out_vector);
// <LegoRR.exe @00451c70>
MeshLOD* __cdecl MeshLOD_Create(MeshLOD* opt_prevMeshLOD, char* partName, char* dirname, char* meshName, uint32 setID);
// <LegoRR.exe @00451d70>
MeshLOD* __cdecl MeshLOD_CreateEmpty(MeshLOD* opt_prevMeshLOD, char* partName, uint32 setID);
// <LegoRR.exe @00451df0>
MeshLOD* __cdecl MeshLOD_Clone(MeshLOD* srcMeshLOD);
// <LegoRR.exe @00451e80>
void __cdecl MeshLOD_SwapTarget(MeshLOD* meshLOD, Container* contActTarget, bool32 restore, uint32 setID);
// <LegoRR.exe @00451ef0>
void __cdecl MeshLOD_RemoveTargets(MeshLOD* meshLOD);
// <LegoRR.exe @00451f10>
void __cdecl MeshLOD_Free(MeshLOD* meshLOD);
// <LegoRR.exe @00451f90>
void __cdecl Message_Initialise(void);
// <LegoRR.exe @00452220>
void __cdecl Message_RemoveLiveObject(LegoObject* liveObj);
// <LegoRR.exe @00452290>
Message_Type __cdecl Message_LookupPTLEventIndex(char* ptlName);
// <LegoRR.exe @004522d0>
void __cdecl Message_Debug_RegisterSelectedUnitHotkey(Keys8 key, Message_Type messageType, LegoObject* argumentObj, undefined4 argument2, Point2I* opt_position);
// <LegoRR.exe @00452320>
void __cdecl Message_AddMessageAction(Message_Type messageType, LegoObject* argument1Obj, undefined4 argument2, Point2I* opt_blockPos);
// <LegoRR.exe @00452390>
void __cdecl Message_PTL_Update(void);
// <LegoRR.exe @004526f0>
void __cdecl Message_PTL_PickRandomFloor(LegoObject* liveObj);
// <LegoRR.exe @00452770>
void __cdecl Message_RemoveObjectReference(LegoObject* liveObj);
// <LegoRR.exe @004527e0>
bool32 __cdecl Message_CopySelectedUnits(LegoObject*** out_unitsList, uint32* out_unitsCount);
// <LegoRR.exe @00452840>
LegoObject** __cdecl Message_GetSelectedUnits2(uint32* out_count);
// <LegoRR.exe @00452870>
bool32 __cdecl Message_AnyUnitSelected(void);
// <LegoRR.exe @00452880>
LegoObject* __cdecl Message_GetPrimarySelectedUnit(void);
// <LegoRR.exe @004528a0>
LegoObject** __cdecl Message_GetSelectedUnits(void);
// <LegoRR.exe @004528b0>
uint32 __cdecl Message_GetNumSelectedUnits(void);
// <LegoRR.exe @004528c0>
void __cdecl Message_CleanupSelectedUnitsCount(void);
// <LegoRR.exe @004528d0>
bool32 __cdecl Message_LiveObject_Check_IsSelected_OrFlags3_200000(LegoObject* liveObj, uint32* out_index);
// <LegoRR.exe @00452910>
bool32 __cdecl Message_FindIndexOfObject(LegoObject** objsTable, uint32 objsCount, LegoObject* thisObj, uint32* out_index);
// <LegoRR.exe @00452950>
bool32 __cdecl Message_LiveObject_Check_FUN_00452950(LegoObject* liveObj);
// <LegoRR.exe @00452980>
bool32 __cdecl Message_PTL_Select_LiveObject(LegoObject* liveObj, bool32 noDoubleSelect);
// <LegoRR.exe @004529a0>
bool32 __cdecl Message_LiveObject_DoSelect_FUN_004529a0(LegoObject* liveObj, bool32 noDoubleSelect, bool32 interrupt);
// <LegoRR.exe @00452b30>
bool32 __cdecl Message_LiveObject_Check_FUN_00452b30(LegoObject* liveObj);
// <LegoRR.exe @00452b80>
void __cdecl Message_PTL_ReduceSelection(void);
// <LegoRR.exe @00452ea0>
void __cdecl Message_PTL_ClearSelection(void);
// <LegoRR.exe @00452f10>
bool32 __cdecl Message_PTL_Deselect_LiveObject(LegoObject* liveObj);
// <LegoRR.exe @00452f80>
uint32 __cdecl Message_PTL_Debug_DestroyAll(void);
// <LegoRR.exe @00453020>
bool32 __cdecl Message_PTL_FirstPerson(uint32 cameraFrame);
// <LegoRR.exe @004530b0>
bool32 __cdecl NERPsFile_LoadScriptFile(char* filename);
// <LegoRR.exe @00453130>
bool32 __cdecl NERPsFile_LoadMessageFile(char* filename);
// <LegoRR.exe @004534c0>
char* __cdecl NERPsFile_GetMessageLine(uint32 lineIndex);
// <LegoRR.exe @004534e0>
bool32 __cdecl NERPsFile_Free(void);
// <LegoRR.exe @004535a0>
void __cdecl NERPsRuntime_LoadLiteral(NERPsInstruction* ref_instruction);
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
void __cdecl NERPsRuntime_EndExecute(real32 elapsedAbs);
// <LegoRR.exe @004542a0>
sint32 __cdecl NERPFunc__CameraLockOnMonster(sint32* stack);
// <LegoRR.exe @004542e0>
bool32 __cdecl NERPsRuntime_LiveObject_GetIfRockMonsterAnd_FUN_004542e0(LegoObject* liveObj, LegoObject** out_liveObj);
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
bool32 __cdecl NERPs_LiveObject_Callback_FUN_004545c0(LegoObject* liveObj, uint32* param_2);
// <LegoRR.exe @00454660>
sint32 __cdecl NERPFunc__SetMonsterAttackNowt(sint32* stack);
// <LegoRR.exe @004546d0>
void __cdecl NERPs_SetObjectsLevel(char* objName, uint32 objLevel);
// <LegoRR.exe @00454740>
bool32 __cdecl NERPs_LiveObject_Callback_SetLevelOfObjects(LegoObject* liveObj, SearchSetObjectsLevel_8c* search);
// <LegoRR.exe @00454780>
bool32 __cdecl NERPs_LiveObject_Callback_CountRecordObjectsAtBlock(BlockPointer* blockPointer, sint32 bx, sint32 by, SearchCountRecordObjects_8* search);
// <LegoRR.exe @004547f0>
sint32 __cdecl NERPFunc__GetRecordObjectAtTutorial(sint32* stack);
// <LegoRR.exe @00454860>
sint32 __cdecl NERPFunc__GetRecordObjectAmountAtTutorial(sint32* stack);
// <LegoRR.exe @004548c0>
void __cdecl NERPsRuntime_DrawTutorialIcon(Lego_Level* level, Viewport* viewMain, real32 elapsedGame, real32 elapsedAbs);
// <LegoRR.exe @004549c0>
sint32 __cdecl NERPFunc__SetRecordObjectPointer(sint32* stack);
// <LegoRR.exe @004549d0>
sint32 __cdecl NERPs_GetIconClicked(Interface_MenuItemType* pMenuIcon);
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
void __cdecl NERPsRuntime_IncHiddenObjectsFound(LegoObject_Type unused_objType);
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
bool32 __cdecl NERPs_LiveObject_Callback_SetRockMonsterHealthType(LegoObject* liveObj, SearchSetObjectHealthPain_c* search);
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
bool32 __cdecl NERPs_SetOreAtBlock(BlockPointer* blockPointer, uint32 bx, uint32 by, sint32* pGenerateOre);
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
bool32 __cdecl NERPs_LiveObject_Callback_ByObjectTypeIndex_IsDriving(LegoObject* liveObj1, LegoObject* liveObj_template);
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
bool32 __cdecl NERPsRuntime_LiveObjectCallback_GetPoweredObjectsBuilt(LegoObject* liveObj, SearchObjectTypeCount_c* search);
// <LegoRR.exe @004555c0>
uint32 __cdecl NERPsRuntime_GetPreviousLevelObjectsBuilt(char* objName, sint32 objLevel);
// <LegoRR.exe @00455600>
sint32 __cdecl NERPs_SubMenu_GetBuildingVehicleIcon_ByObjectName(char* objName);
// <LegoRR.exe @00455630>
bool32 __cdecl NERPsRuntime_FlashIcon(Interface_MenuItemType menuIcon, bool32 flash);
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
void __cdecl NERPs_Level_NERPMessage_Parse(char* text, char* out_buffer, bool32 updateTimer);
// <LegoRR.exe @00456e40>
void __cdecl NERPs_InitBlockPointersTable(Lego_Level* level);
// <LegoRR.exe @00456ef0>
BlockPointer* __cdecl NERPs_GetBlockPointer(Lego_Level* level, sint32 blockPointerID);
// <LegoRR.exe @00456f20>
void __cdecl NERPs_FreeBlockPointers(void);
// <LegoRR.exe @00456f70>
void __cdecl NERPsRuntime_EnumerateBlockPointers(sint32 blockPointerID, NERPsBlockPointerCallback callback, void* data);
// <LegoRR.exe @00456fc0>
bool32 __cdecl NERPsRuntime_TutorialActionCallback(BlockPointer* unused, uint32 bx, uint32 by, SearchNERPsTutorialAction* search);
// <LegoRR.exe @00457320>
bool32 __cdecl NERPs_LiveObject_CallbackCheck_FUN_00457320(LegoObject* liveObj, sint32 level);
// <LegoRR.exe @00457390>
bool32 __cdecl NERPs_LiveObject_Callback_SetBool3f8IfAtBlockPos_FUN_00457390(LegoObject* liveObj, SearchNERPsTutorialAction* search);
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
void __cdecl Objective_LoadObjectiveText(Config* config, char* gameName, char* levelName, Lego_Level* level, char* filename);
// <LegoRR.exe @00458000>
void __cdecl Objective_LoadLevel(Config* config, char* gameName, char* levelName, Lego_Level* level, uint32 screenWidth, uint32 screenHeight);
// <LegoRR.exe @00458840>
void __cdecl Objective_SetCryOreObjectives(Lego_Level* level, uint32 crystals, uint32 ore);
// <LegoRR.exe @00458880>
void __cdecl Objective_SetBlockObjective(Lego_Level* level, Point2I* blockPos);
// <LegoRR.exe @004588b0>
void __cdecl Objective_SetTimerObjective(Lego_Level* level, real32 timer, bool32 hitTimeFail);
// <LegoRR.exe @004588e0>
void __cdecl Objective_SetConstructionObjective(Lego_Level* level, LegoObject_Type objType, sint32 objID);
// <LegoRR.exe @00458910>
bool32 __cdecl Objective_IsObjectiveAchieved(void);
// <LegoRR.exe @00458920>
void __cdecl Objective_SetEndTeleportEnabled(bool32 on);
// <LegoRR.exe @00458930>
void __cdecl Objective_SetStatus(LevelStatus status);
// <LegoRR.exe @00458ba0>
void __cdecl Objective_ProgrammerModeGT3_FUN_00458ba0(void);
// <LegoRR.exe @00458c60>
bool32 __cdecl Objective_IsEnded(void);
// <LegoRR.exe @00458c80>
bool32 __cdecl Objective_HandleKeys(bool32 spaceKeyHeld, bool32 leftButtonReleasedUnk, bool32* out_gotoNextLevel);
// <LegoRR.exe @00458ea0>
void __cdecl Objective_Update(TextWindow* textWnd, Lego_Level* level, real32 elapsedGame, real32 elapsedAbs);
// <LegoRR.exe @00459310>
bool32 __cdecl Objective_CheckCompleted(Lego_Level* level, bool32* out_timerFailed, real32 elapsed);
// <LegoRR.exe @004593c0>
bool32 __cdecl Objective_Callback_CountObjects(LegoObject* liveObj, ObjectiveData* objective);
// <LegoRR.exe @00459450>
void __cdecl ObjectRecall_StoreMiniFigure(LegoObject* liveObj);
// <LegoRR.exe @00459500>
bool32 __cdecl ObjectRecall_RecallMiniFigure(LegoObject* liveObj);
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
void __cdecl ObjInfo_Initialise(Config* config, char* gameName);
// <LegoRR.exe @00459820>
bool32 __cdecl ObjInfo_LoadHealthBar(Config* config, char* gameName);
// <LegoRR.exe @00459bc0>
bool32 __cdecl ObjInfo_LoadHunger(Config* config, char* gameName);
// <LegoRR.exe @00459c80>
void __cdecl ObjInfo_LoadHungerImages(Config* config, char* gameName);
// <LegoRR.exe @00459d10>
bool32 __cdecl ObjInfo_LoadBubble(Config* config, char* gameName);
// <LegoRR.exe @00459dc0>
void __cdecl ObjInfo_DrawHealthBar(LegoObject* liveObj, sint32 screenX, sint32 screenY);
// <LegoRR.exe @0045a210>
void __cdecl ObjInfo_DrawHungerImage(LegoObject* liveObj, sint32 screenX, sint32 screenY);
// <LegoRR.exe @0045a290>
void __cdecl ObjInfo_DrawBubbleImage(Image* image, sint32 screenX, sint32 screenY);
// <LegoRR.exe @0045a2f0>
void __cdecl Panel_Initialise(void);
// <LegoRR.exe @0045a500>
void __cdecl Panel_LoadInterfaceButtons_ScrollInfo(void);
// <LegoRR.exe @0045a530>
void __cdecl Panel_ResetAll(void);
// <LegoRR.exe @0045a5a0>
void __cdecl Panel_LoadImage(char* filename, Panel_Type panelType, uint32 flags);
// <LegoRR.exe @0045a630>
bool32 __cdecl Panel_GetPanelType(char* panelName, Panel_Type* out_panelType);
// <LegoRR.exe @0045a670>
bool32 __cdecl Panel_TestScreenImageCollision(Panel_Type panelType, sint32 screenX, sint32 screenY);
// <LegoRR.exe @0045a6d0>
bool32 __cdecl Panel_GetButtonType(Panel_Type panelType, char* buttonName, PanelButtonType* out_buttonType);
// <LegoRR.exe @0045a720>
uint32 __cdecl Panel_PrintF(Panel_Type panelType, Font* font, sint32 x, sint32 y, bool32 center, char* msg, ...);
// <LegoRR.exe @0045a7c0>
PanelTextWindow* __cdecl Panel_TextWindow_Create(Panel_Type panelType, Font* font, Area2F* rect, uint32 size);
// <LegoRR.exe @0045a850>
void __cdecl Panel_TextWindow_PrintF(PanelTextWindow* panelWnd, char* msg, ...);
// <LegoRR.exe @0045a870>
void __cdecl Panel_TextWindow_Update(PanelTextWindow* textWnd, uint32 posFromEnd, real32 elapsed);
// <LegoRR.exe @0045a8e0>
void __cdecl Panel_TextWindow_Clear(PanelTextWindow* panelWnd);
// <LegoRR.exe @0045a8f0>
void __cdecl Panel_TextWindow_GetInfo(PanelTextWindow* panelWnd, uint32* out_linesCount, uint32* out_linesCapacity);
// <LegoRR.exe @0045a910>
void __cdecl Panel_SetArea(Panel_Type panelType, sint32 xOut, sint32 yOut, sint32 xIn, sint32 yIn);
// <LegoRR.exe @0045a9a0>
void __cdecl Panel_SetXYField3(Panel_Type panelType, real32 x, real32 y);
// <LegoRR.exe @0045a9c0>
void __cdecl Panel_GetXYField3(Panel_Type panelType, real32* out_x, real32* out_y);
// <LegoRR.exe @0045a9f0>
void __cdecl Panel_FUN_0045a9f0(Panel_Type panelType, real32 elapsedAbs);
// <LegoRR.exe @0045ac80>
void __cdecl Panel_Display_FUN_0045ac80(Panel_Type panelType);
// <LegoRR.exe @0045ad80>
void __cdecl Panel_Button_SetFlags_10(Panel_Type panelType, PanelButtonType buttonType, bool32 state);
// <LegoRR.exe @0045adc0>
void __cdecl Panel_ChangeFlags_BasedOnState(Panel_Type panelType);
// <LegoRR.exe @0045adf0>
bool32 __cdecl Panel_IsFlags_4_Not8(Panel_Type panelType);
// <LegoRR.exe @0045ae20>
bool32 __cdecl Panel_IsFlags_2_Not8(Panel_Type panelType);
// <LegoRR.exe @0045ae50>
bool32 __cdecl Panel_IsFlags_8(Panel_Type panelType);
// <LegoRR.exe @0045ae70>
void __cdecl Panel_Button_SetFlag_20(Panel_Type panelType, PanelButtonType buttonType, bool32 setFlag20);
// <LegoRR.exe @0045aeb0>
void __cdecl Panel_Button_SetFlag_8_OrUnset_c(Panel_Type panelType, PanelButtonType buttonType, bool32 setFlag8);
// <LegoRR.exe @0045aef0>
void __cdecl Panel_CreateButtons(Panel_Type panelType, uint32 count, sint32 param_3, sint32 param_4, sint32* param_5, sint32 param_6, sint32 param_7, sint32 param_8);
// <LegoRR.exe @0045b070>
bool32 __cdecl Panel_CheckCollision(real32 elapsedAbs, uint32 mouseX, uint32 mouseY, bool32 leftButton, bool32 leftButtonLast, bool32* out_panelCollision);
// <LegoRR.exe @0045b5d0>
bool32 __cdecl Panel_InputProc_FUN_0045b5d0(Panel_Type* out_panelType, PanelButtonType* out_panelButton, sint32 mouseX, sint32 mouseY, bool32 leftButton, bool32 leftButtonLast, bool32* optout_param_7, bool32* optout_panelCollision);
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
void __cdecl Panel_RotationControl_Initialise(Config* config, char* gameName);
// <LegoRR.exe @0045bf90>
bool32 __cdecl Panel_RotationControl_FUN_0045bf90(sint32 mouseX, sint32 mouseY, real32 elapsedAbs);
// <LegoRR.exe @0045c1e0>
void __cdecl Panel_RotationControl_MoveDist(bool32 doAdd, real32 amount);
// <LegoRR.exe @0045c230>
void __cdecl Panel_GetButtonRect(Panel_Type panelType, PanelButtonType buttonType, Area2F* out_rect);
// <LegoRR.exe @0045c270>
void __cdecl Panel_Crystals_Initialise(char* smallCrystal, char* usedCrystal, char* noSmallCrystal);
// <LegoRR.exe @0045c300>
void __cdecl Panel_Crystals_LoadRewardQuota(Config* config, char* gameName, char* levelName);
// <LegoRR.exe @0045c390>
void __cdecl Panel_Crystals_Draw(uint32 crystals, uint32 usedCrystals, real32 elapsedGame_unused);
// <LegoRR.exe @0045c600>
void __cdecl Panel_AirMeter_Initialise(char* airJuiceName, uint32 juiceX, uint32 juiceY, uint32 juiceLength, char* noAirName, uint32 noAirX, uint32 noAirY);
// <LegoRR.exe @0045c6b0>
void __cdecl Panel_AirMeter_DrawJuice(Panel_Type panelType, real32 oxygen);
// <LegoRR.exe @0045c760>
void __cdecl Panel_AirMeter_SetOxygenLow(bool32 o2Low);
// <LegoRR.exe @0045c770>
void __cdecl Panel_AirMeter_DrawOxygenLow(Panel_Type panelType);
// <LegoRR.exe @0045c7e0>
void __cdecl Panel_CryOreSideBar_Initialise(char* sidebarName, uint32 xPos, uint32 yPos, uint32 meterOffset);
// <LegoRR.exe @0045c840>
void __cdecl Panel_CryOreSideBar_ChangeOreMeter(bool32 increment, uint32 amount);
// <LegoRR.exe @0045c8b0>
void __cdecl Panel_CryOreSideBar_Draw(void);
// <LegoRR.exe @0045c930>
bool32 __cdecl Panel_SetCurrentAdvisorFromButton(Panel_Type panelType, PanelButtonType buttonType, bool32 setFlag2);
// <LegoRR.exe @0045c970>
bool32 __cdecl Panel_GetAdvisorTypeFromButton(Panel_Type panelType, PanelButtonType buttonType, Advisor_Type* out_advisorType);
// <LegoRR.exe @0045caf0>
void __cdecl Pointer_Initialise(void);
// <LegoRR.exe @0045cd30>
void __cdecl Pointer_LoadPointers(Config* config);
// <LegoRR.exe @0045ce90>
bool32 __cdecl Pointer_GetType(char* name, Pointer_Type* out_pointerType);
// <LegoRR.exe @0045ced0>
Image* __cdecl Pointer_GetImage(Pointer_Type pointerType);
// <LegoRR.exe @0045cee0>
void __cdecl Pointer_SetCurrent_IfTimerFinished(Pointer_Type pointerType);
// <LegoRR.exe @0045cf00>
void __cdecl Pointer_SetCurrent(Pointer_Type pointerType, real32 timer);
// <LegoRR.exe @0045cf20>
Pointer_Type __cdecl Pointer_GetCurrentType(void);
// <LegoRR.exe @0045cf30>
void __cdecl Pointer_DrawPointer(uint32 mouseX, uint32 mouseY);
// <LegoRR.exe @0045d050>
void __cdecl Pointer_Update(real32 elapsedAbs);
// <LegoRR.exe @0045d080>
void __cdecl Priorities_LoadImages(Config* config, char* gameName);
// <LegoRR.exe @0045d1c0>
void __cdecl Priorities_Reset(void);
// <LegoRR.exe @0045d210>
bool32 __cdecl Priorities_LoadLevel(Config* config, char* gameName, char* levelName);
// <LegoRR.exe @0045d320>
void __cdecl Priorities_LoadPositions(Config* config, char* gameName);
// <LegoRR.exe @0045d3d0>
bool32 __cdecl Priorities_HandleInput(uint32 mouseX, uint32 mouseY, bool32 leftButton, bool32 leftButtonLast, bool32 leftReleased);
// <LegoRR.exe @0045d5c0>
bool32 __cdecl Priorities_ChangePriorityPressed(uint32 orderIndex, bool32 leftButton, bool32 leftButtonLast);
// <LegoRR.exe @0045d630>
void __cdecl Priorities_SetHoverArea(Point2F* point, uint32 widthM1, uint32 heightM1);
// <LegoRR.exe @0045d680>
void __cdecl Priorities_MovePriorityUpOrTop(uint32 orderIndex);
// <LegoRR.exe @0045d6b0>
void __cdecl Priorities_MovePriorityTop(uint32 orderIndex);
// <LegoRR.exe @0045d730>
void __cdecl Priorities_MovePriorityUp(uint32 orderIndex);
// <LegoRR.exe @0045d7b0>
void __cdecl Priorities_TurnPriorityOff(uint32 orderIndex);
// <LegoRR.exe @0045d810>
void __cdecl Priorities_MoveCursorToPriorityUpButton(uint32 orderIndex);
// <LegoRR.exe @0045d900>
void __cdecl Priorities_MoveCursorToPriorityImage(uint32 orderIndex);
// <LegoRR.exe @0045d990>
void __cdecl Priorities_Draw(void);
// <LegoRR.exe @0045daa0>
bool32 __cdecl PTL_Initialise(char* filename, char* gameName);
// <LegoRR.exe @0045db30>
void __cdecl PTL_EventToAction(MessageAction* ref_message);
// <LegoRR.exe @0045db60>
void __cdecl RadarMap_SetTVTiltOrZoom(RadarMap* radarMap, real32 tvTiltOrZoom);
// <LegoRR.exe @0045db70>
void __cdecl RadarMap_Initialise(void);
// <LegoRR.exe @0045dd50>
RadarMap* __cdecl RadarMap_Create(Map3D* map, Area2F* radarViewRect, real32 tvTiltOrZoom);
// <LegoRR.exe @0045ddb0>
void __cdecl RadarMap_Free_UnwindMultiUse(RadarMap* radarMap);
// <LegoRR.exe @0045ddc0>
void __cdecl RadarMap_DrawDotCircle_FUN_0045ddc0(RadarMap* radarMap, Point2F* param_2, real32 param_3, real32 param_4);
// <LegoRR.exe @0045de80>
void __cdecl RadarMap_Draw_FUN_0045de80(RadarMap* radarMap, Point2F* position);
// <LegoRR.exe @0045e6c0>
bool32 __cdecl RadarMap_CanLiveObjectShowOnRadar(LegoObject* liveObj);
// <LegoRR.exe @0045e720>
bool32 __cdecl RadarMap_LiveObject_Callback_FUN_0045e720(LegoObject* liveObj, RadarMap* radarMap);
// <LegoRR.exe @0045e920>
bool32 __cdecl RadarMap_InsideRadarScreen(RadarMap* radarMap, uint32 mouseX, uint32 mouseY);
// <LegoRR.exe @0045e990>
bool32 __cdecl RadarMap_ScreenToWorldBlockPos(RadarMap* radarMap, uint32 mouseX, uint32 mouseY, Point2F* optout_worldPos, sint32* out_bx, sint32* out_by);
// <LegoRR.exe @0045eae0>
bool32 __cdecl RadarMap_TrySelectObject(RadarMap* radarMap, uint32 mouseX, uint32 mouseY, LegoObject** out_liveObj, Point2F* optout_objPosition);
// <LegoRR.exe @0045eba0>
bool32 __cdecl RadarMap_LiveObjectCallback_InsideSquareRadius(LegoObject* liveObj, SearchRadarObjectRadius_10* search);
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
bool32 __cdecl Reward_LoadGraphics(Config* config, char* gameName);
// <LegoRR.exe @0045fdb0>
bool32 __cdecl Reward_LoadButtons(Config* config, char* gameName);
// <LegoRR.exe @00460060>
bool32 __cdecl Reward_CreateLevel(void);
// <LegoRR.exe @00460360>
void __cdecl Reward_LoadLevelItemImportance(RewardLevelItem* rewardItem);
// <LegoRR.exe @00460400>
void __cdecl Reward_LoadLevelItemQuota(RewardLevelItem* rewardItem);
// <LegoRR.exe @004604a0>
void __cdecl Reward_FreeLevel(void);
// <LegoRR.exe @004604b0>
RewardLevel* __cdecl GetRewardLevel2(undefined4 unused_rewardID);
// <LegoRR.exe @004604c0>
RewardLevel* __cdecl GetRewardLevel(void);
// <LegoRR.exe @004604e0>
void __cdecl RewardQuota_CountUnits(void);
// <LegoRR.exe @00460550>
RewardBuildingCounts* __cdecl RewardQuota_CountBuildings(RewardBuildingCounts* out_buildingCounts);
// <LegoRR.exe @004605d0>
bool32 __cdecl RewardQuota_LiveObjectCallback_CountBuildings(LegoObject* liveObj, RewardBuildingCounts* search);
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
void __cdecl Reward_DrawItem(RewardLevelItem* rewardItem, RewardItemFlags flags, Reward_Type rewardType);
// <LegoRR.exe @00461f50>
void __cdecl Reward_DrawScore(Reward_Type rewardType);
// <LegoRR.exe @00462090>
void __cdecl Reward_HandleButtons(RewardUIState* out_state, bool32* out_saved);
// <LegoRR.exe @004622f0>
void __cdecl Reward_GotoSaveMenu(void);
// <LegoRR.exe @00462530>
void __cdecl Reward_GotoAdvance(void);
// <LegoRR.exe @00462650>
void __cdecl Reward_HandleDebugKeys(Reward_Type* ref_rewardType, RewardUIState* ref_state, bool32* ref_finished, real32* ref_timer);
// <LegoRR.exe @00462720>
void __cdecl Reward_PlayFlic(RewardLevelItem* rewardItem);
// <LegoRR.exe @00462760>
void __cdecl Reward_UpdateState(Reward_Type* ref_rewardType, RewardUIState* ref_state, real32* ref_timer);
// <LegoRR.exe @004628c0>
void __cdecl Reward_DrawAllValues(Reward_Type* in_rewardType, bool32* out_finished);
// <LegoRR.exe @004629c0>
void __cdecl Reward_LoopUpdate(real32 elapsed);
// <LegoRR.exe @00462a40>
bool32 __cdecl Reward_LoopBegin(void);
// <LegoRR.exe @00462ac0>
void __cdecl RewardQuota_UpdateTimers(real32 elapsedGame);
// <LegoRR.exe @00462af0>
void __cdecl RewardQuota_WallDestroyed(void);
// <LegoRR.exe @00462b10>
void __cdecl RewardQuota_CavernDiscovered(void);
// <LegoRR.exe @00462b30>
void __cdecl RewardQuota_RockMonsterGenerated(void);
// <LegoRR.exe @00462b40>
void __cdecl RewardQuota_RockMonsterDestroyed(void);
// <LegoRR.exe @00462b50>
void __cdecl RewardQuota_RockMonsterAttacked(void);
// <LegoRR.exe @00462b60>
void __cdecl RewardQuota_RockMonsterDamageDealt(real32 damage);
// <LegoRR.exe @00462b80>
void __cdecl RewardQuota_MiniFigureDamageTaken(real32 damage);
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
bool32 __cdecl Roof_Initialise(Container* root, uint32 width, uint32 height);
// <LegoRR.exe @00463120>
bool32 __cdecl Roof_SetTexture(char* filename);
// <LegoRR.exe @00463190>
void __cdecl Roof_Shutdown(void);
// <LegoRR.exe @004631e0>
void __cdecl Roof_SetBlockRoofVertices(uint32 bx, uint32 by, Vector3F* vertPos0, Vector3F* vertPos1, Vector3F* vertPos2, Vector3F* vertPos3);
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
void __cdecl ScrollInfo_Update(bool32 index);
// <LegoRR.exe @00464100>
sint64 __cdecl ScrollInfo_MathX_RoundToLL(real32 x);
// <LegoRR.exe @00464160>
void __cdecl ScrollInfo_GetSubStruct28_Fields1C_20(bool32 index, sint32* out_field1c, sint32* out_field20);
// <LegoRR.exe @00464190>
void __cdecl ScrollInfo_SetSubStruct28_Fields1C_20(bool32 index, sint32 field1c, sint32 field20);
// <LegoRR.exe @004641c0>
SelectPlace* __cdecl SelectPlace_Create(Container* root, real32 tileDepth);
// <LegoRR.exe @004643d0>
Point2I* __cdecl SelectPlace_TransformShapePoints(Point2I* translation, Point2I* shapePoints, sint32 shapeCount, Direction rotation);
// <LegoRR.exe @00464480>
Point2I* __cdecl SelectPlace_CheckAndUpdate(SelectPlace* selectPlace, Point2I* blockPos, Point2I* shapePoints, uint32 shapeCount, Direction direction, Map3D* surfMap, sint32 waterEntrances);
// <LegoRR.exe @004649e0>
void __cdecl SelectPlace_Hide(SelectPlace* selectPlace, bool32 hide);
// <LegoRR.exe @00464a00>
void __cdecl SFX_Initialise(void);
// <LegoRR.exe @00464ee0>
void __cdecl SFX_Container_SoundTriggerCallback(char* sfxName, Container* cont, void* data);
// <LegoRR.exe @00464f10>
void __cdecl SFX_SetSamplePopulateMode(bool32 on);
// <LegoRR.exe @00464f30>
bool32 __cdecl SFX_GetType(char* sfxName, SFX_ID* out_sfxID);
// <LegoRR.exe @00464fc0>
bool32 __cdecl SFX_LoadSampleProperty(char* value, SFX_ID sfxID);
// <LegoRR.exe @004650e0>
sint32 __cdecl SFX_Random_GetSound3DHandle(SFX_ID sfxID);
// <LegoRR.exe @00465140>
void __cdecl SFX_StopGlobalSample(void);
// <LegoRR.exe @00465180>
bool32 __cdecl SFX_SetGlobalSampleDurationIfLE0_AndNullifyHandle(real32 duration);
// <LegoRR.exe @004651b0>
bool32 __cdecl SFX_Random_SetAndPlayGlobalSample(SFX_ID sfxID, sint32* optout_handle);
// <LegoRR.exe @00465220>
void __cdecl SFX_AddToQueue(SFX_ID sfxID, SoundMode mode);
// <LegoRR.exe @00465260>
sint32 __cdecl SFX_Random_Play_OrAddToQueue(SFX_ID sfxID, bool32 loop);
// <LegoRR.exe @004652d0>
void __cdecl SFX_Random_SetBufferVolume(SFX_ID sfxID, sint32 volume);
// <LegoRR.exe @004652f0>
sint32 __cdecl SFX_Random_GetBufferVolume(SFX_ID sfxID);
// <LegoRR.exe @00465310>
sint32 __cdecl SFX_Container_Random_Play_OrInitSoundUnk(Container* cont, SFX_ID sfxID, bool32 loop, bool32 sound3D, Vector3F* opt_wPos);
// <LegoRR.exe @00465350>
sint32 __cdecl SFX_Random_Play_OrInitSoundUnk(IDirect3DRMFrame3* frame, SFX_ID sfxID, bool32 loop, bool32 sound3D, Vector3F* opt_wPos);
// <LegoRR.exe @00465420>
real32 __cdecl SFX_Random_GetSamplePlayTime(SFX_ID sfxID);
// <LegoRR.exe @00465450>
void __cdecl SFX_Sound3D_StopSound(sint32 sound3DHandle);
// <LegoRR.exe @00465460>
void __cdecl SFX_Update(real32 elapsed);
// <LegoRR.exe @00465510>
void __cdecl SFX_Sound3D_Update(void);
// <LegoRR.exe @00465520>
void __cdecl SFX_SetSoundOn(bool32 soundOn, bool32 stopAll);
// <LegoRR.exe @00465560>
void __cdecl SFX_SetSoundOn_AndStopAll(bool32 soundOn);
// <LegoRR.exe @00465570>
bool32 __cdecl SFX_IsQueueMode(void);
// <LegoRR.exe @00465580>
void __cdecl SFX_SetQueueMode_AndFlush(bool32 on);
// <LegoRR.exe @00465590>
void __cdecl SFX_SetQueueMode(bool32 on, bool32 flushQueued);
// <LegoRR.exe @00465630>
bool32 __cdecl SFX_IsSoundOn(void);
// <LegoRR.exe @00465640>
bool32 __cdecl Smoke_Initialise(void);
// <LegoRR.exe @00465660>
void __cdecl Smoke_LoadTextures(char* dirname, char* basename, uint32 textureCount);
// <LegoRR.exe @004656f0>
Smoke* __cdecl Smoke_CreateSmokeArea(Container* optin_attachedCont, uint32 bx, uint32 by, Vector3F* dirVec, real32 r, real32 g, real32 b, real32 thickness, real32 animSpeed, Smoke_Type smokeType, uint32 randomness, SFX_ID sfxID);
// <LegoRR.exe @00465c30>
void __cdecl Smoke_RemoveAll(void);
// <LegoRR.exe @00465c70>
void __cdecl Smoke_Remove(Smoke* smoke, Container* attachedCont);
// <LegoRR.exe @00465d50>
void __cdecl Smoke_HideAll(bool32 hide);
// <LegoRR.exe @00465d80>
void __cdecl Smoke_Hide(Smoke* smoke, bool32 hide);
// <LegoRR.exe @00465dc0>
void __cdecl Smoke_Update(real32 elapsedGame);
// <LegoRR.exe @00465f10>
void __cdecl Smoke_Group_Show(Smoke* smoke, uint32 groupID);
// <LegoRR.exe @004660c0>
void __cdecl Smoke_Group_Update(Smoke* smoke, uint32 groupID, real32 elapsedGame);
// <LegoRR.exe @004661a0>
void __cdecl Smoke_MeshRenderCallback(Mesh* mesh, Smoke* data, Viewport* view);
// <LegoRR.exe @00466200>
void __cdecl Smoke_Group_MeshRenderCallback(Smoke* smoke, uint32 groupID, Viewport* view, Vector3F* lightPos);
// <LegoRR.exe @00466480>
void __cdecl SpiderWeb_Initialise(Lego_Level* level);
// <LegoRR.exe @004664d0>
void __cdecl SpiderWeb_Shutdown(void);
// <LegoRR.exe @004664f0>
void __cdecl SpiderWeb_Restart(Lego_Level* level);
// <LegoRR.exe @00466510>
bool32 __cdecl SpiderWeb_SpawnAt(uint32 bx, uint32 by);
// <LegoRR.exe @00466640>
void __cdecl SpiderWeb_Add(sint32 bx, sint32 by, LegoObject* webObj);
// <LegoRR.exe @004666b0>
bool32 __cdecl SpiderWeb_GetAngle(sint32 bx, sint32 by, real32* out_theta);
// <LegoRR.exe @00466750>
bool32 __cdecl SpiderWeb_CheckCollision(LegoObject* liveObj);
// <LegoRR.exe @00466880>
bool32 __cdecl SpiderWeb_Update(real32 elapsedGame);
// <LegoRR.exe @004668a0>
bool32 __cdecl SpiderWeb_LiveObjectCallback(LegoObject* liveObj, real32* pElapsedGame);
// <LegoRR.exe @00466a10>
void __cdecl SpiderWeb_Remove(sint32 bx, sint32 by);
// <LegoRR.exe @00466aa0>
bool32 __cdecl Stats_Initialise(Config* config, char* gameName);
// <LegoRR.exe @00469d50>
void __cdecl Stats_AddToolTaskType(LegoObject_ToolType toolType, AITask_Type taskType);
// <LegoRR.exe @00469d80>
uint32 __cdecl Stats_GetCostOre(LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel);
// <LegoRR.exe @00469db0>
uint32 __cdecl Stats_GetCostCrystal(LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel);
// <LegoRR.exe @00469de0>
uint32 __cdecl Stats_GetCostRefinedOre(LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel);
// <LegoRR.exe @00469e10>
sint32 __cdecl StatsObject_GetCrystalDrain(LegoObject* liveObj);
// <LegoRR.exe @00469e40>
uint32 __cdecl StatsObject_GetCapacity(LegoObject* liveObj);
// <LegoRR.exe @00469e70>
uint32 __cdecl StatsObject_GetMaxCarry(LegoObject* liveObj);
// <LegoRR.exe @00469ea0>
uint32 __cdecl StatsObject_GetCarryStart(LegoObject* liveObj);
// <LegoRR.exe @00469ed0>
bool32 __cdecl StatsObject_SetObjectLevel(LegoObject* liveObj, uint32 newLevel);
// <LegoRR.exe @00469f70>
real32 __cdecl StatsObject_GetRouteSpeed(LegoObject* liveObj);
// <LegoRR.exe @00469f80>
real32 __cdecl StatsObject_GetDrillTimeType(LegoObject* liveObj, Lego_SurfaceType surfaceType);
// <LegoRR.exe @00469fa0>
real32 __cdecl StatsObject_GetRubbleCoef(LegoObject* liveObj);
// <LegoRR.exe @00469fc0>
real32 __cdecl StatsObject_GetWakeRadius(LegoObject* liveObj);
// <LegoRR.exe @00469fe0>
real32 __cdecl StatsObject_GetPathCoef(LegoObject* liveObj);
// <LegoRR.exe @0046a000>
real32 __cdecl StatsObject_GetCollRadius(LegoObject* liveObj);
// <LegoRR.exe @0046a010>
real32 __cdecl StatsObject_GetCollHeight(LegoObject* liveObj);
// <LegoRR.exe @0046a020>
real32 __cdecl StatsObject_GetPickSphere(LegoObject* liveObj);
// <LegoRR.exe @0046a030>
real32 __cdecl StatsObject_GetPainThreshold(LegoObject* liveObj);
// <LegoRR.exe @0046a050>
real32 __cdecl StatsObject_GetAlertRadius(LegoObject* liveObj);
// <LegoRR.exe @0046a060>
Size2F* __cdecl StatsObject_GetCollBox(LegoObject* liveObj);
// <LegoRR.exe @0046a070>
real32 __cdecl StatsObject_GetTrackDist(LegoObject* liveObj);
// <LegoRR.exe @0046a080>
real32 __cdecl StatsObject_GetHealthDecayRate(LegoObject* liveObj);
// <LegoRR.exe @0046a0a0>
real32 __cdecl StatsObject_GetEnergyDecayRate(LegoObject* liveObj);
// <LegoRR.exe @0046a0c0>
real32 __cdecl Stats_GetOxygenCoef(LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @0046a0e0>
real32 __cdecl StatsObject_GetOxygenCoef(LegoObject* liveObj);
// <LegoRR.exe @0046a100>
uint32 __cdecl StatsObject_GetSurveyRadius(LegoObject* liveObj);
// <LegoRR.exe @0046a120>
StatsFlags1 __cdecl StatsObject_GetStatsFlags1(LegoObject* liveObj);
// <LegoRR.exe @0046a140>
StatsFlags2 __cdecl StatsObject_GetStatsFlags2(LegoObject* liveObj);
// <LegoRR.exe @0046a160>
StatsFlags3 __cdecl StatsObject_GetStatsFlags3(LegoObject* liveObj);
// <LegoRR.exe @0046a180>
StatsFlags1 __cdecl Stats_GetStatsFlags1(LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @0046a1a0>
StatsFlags2 __cdecl Stats_GetStatsFlags2(LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @0046a1c0>
StatsFlags3 __cdecl Stats_GetStatsFlags3(LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @0046a1e0>
real32 __cdecl StatsObject_GetRepairValue(LegoObject* liveObj);
// <LegoRR.exe @0046a200>
uint32 __cdecl Stats_GetLevels(LegoObject_Type objType, LegoObject_ID objID);
// <LegoRR.exe @0046a220>
uint32 __cdecl Stats_GetWaterEntrances(LegoObject_Type objType, LegoObject_ID objID, uint32 objLevel);
// <LegoRR.exe @0046a250>
SFX_ID __cdecl StatsObject_GetDrillSoundType(LegoObject* liveObj, bool32 fade);
// <LegoRR.exe @0046a280>
SFX_ID __cdecl StatsObject_GetEngineSound(LegoObject* liveObj);
// <LegoRR.exe @0046a2a0>
real32 __cdecl StatsObject_GetRestPercent(LegoObject* liveObj);
// <LegoRR.exe @0046a2c0>
real32 __cdecl StatsObject_GetCarryMinHealth(LegoObject* liveObj);
// <LegoRR.exe @0046a2e0>
real32 __cdecl StatsObject_GetAttackRadius(LegoObject* liveObj);
// <LegoRR.exe @0046a300>
real32 __cdecl StatsObject_GetStampRadius(LegoObject* liveObj);
// <LegoRR.exe @0046a320>
uint32 __cdecl StatsObject_GetNumOfToolsCanCarry(LegoObject* liveObj);
// <LegoRR.exe @0046a340>
real32 __cdecl StatsObject_GetUpgradeTime(LegoObject* liveObj);
// <LegoRR.exe @0046a360>
real32 __cdecl StatsObject_GetFunctionCoef(LegoObject* liveObj);
// <LegoRR.exe @0046a380>
uint32 __cdecl Stats_GetUpgradeCostOre(LegoObject_Type objType, LegoObject_ID objID, LegoObject_UpgradeType upgradeType);
// <LegoRR.exe @0046a3b0>
uint32 __cdecl Stats_GetUpgradeCostStuds(LegoObject_Type objType, LegoObject_ID objID, LegoObject_UpgradeType upgradeType);
// <LegoRR.exe @0046a3e0>
bool32 __cdecl Stats_FindToolFromTaskType(AITask_Type taskType, LegoObject_ToolType* out_toolType);
// <LegoRR.exe @0046a430>
real32 __cdecl StatsObject_GetFlocks_Height(LegoObject* liveObj);
// <LegoRR.exe @0046a450>
real32 __cdecl StatsObject_GetFlocks_Randomness(LegoObject* liveObj);
// <LegoRR.exe @0046a470>
real32 __cdecl StatsObject_GetFlocks_Turn(LegoObject* liveObj);
// <LegoRR.exe @0046a490>
real32 __cdecl StatsObject_GetFlocks_Tightness(LegoObject* liveObj);
// <LegoRR.exe @0046a4b0>
real32 __cdecl StatsObject_GetFlocks_Speed(LegoObject* liveObj);
// <LegoRR.exe @0046a4d0>
uint32 __cdecl StatsObject_GetFlocks_Size(LegoObject* liveObj);
// <LegoRR.exe @0046a4f0>
real32 __cdecl StatsObject_GetFlocks_GoalUpdate(LegoObject* liveObj);
// <LegoRR.exe @0046a510>
real32 __cdecl StatsObject_GetFlocks_AttackTime(LegoObject* liveObj);
// <LegoRR.exe @0046a530>
real32 __cdecl StatsObject_GetAwarenessRange(LegoObject* liveObj);
// <LegoRR.exe @0046a550>
real32 __cdecl StatsObject_GetPusherDist(LegoObject* liveObj);
// <LegoRR.exe @0046a570>
real32 __cdecl StatsObject_GetPusherDamage(LegoObject* liveObj);
// <LegoRR.exe @0046a590>
real32 __cdecl StatsObject_GetLaserDamage(LegoObject* liveObj);
// <LegoRR.exe @0046a5b0>
real32 __cdecl StatsObject_GetFreezerDamage(LegoObject* liveObj);
// <LegoRR.exe @0046a5d0>
real32 __cdecl StatsObject_GetObjectFreezerTime(LegoObject* liveObj);
// <LegoRR.exe @0046a5f0>
void __cdecl StatsObject_Debug_ToggleObjectPower(LegoObject* liveObj);
// <LegoRR.exe @0046a630>
void __cdecl Teleporter_RemoveAll(TeleporterService* teleporter);
// <LegoRR.exe @0046a650>
void __cdecl Teleporter_Restart(void);
// <LegoRR.exe @0046a680>
bool32 __cdecl Teleporter_LiveObjectCallback_Service(LegoObject* liveObj, SearchTeleporter_10* search);
// <LegoRR.exe @0046a6e0>
Point2F __cdecl Teleporter_GetCameraPosition(void);
// <LegoRR.exe @0046a730>
void __cdecl Teleporter_Add(TeleporterService* teleporter);
// <LegoRR.exe @0046a750>
bool32 __cdecl Teleporter_LiveObjectCallback_Unk(LegoObject* liveObj, TeleportObjectType teleportObjType);
// <LegoRR.exe @0046a780>
bool32 __cdecl Teleporter_ServiceAll(TeleportObjectType teleportObjTypes);
// <LegoRR.exe @0046a7d0>
void __cdecl Teleporter_Start(TeleportObjectType teleportObjType, uint32 modeFlags, uint32 teleportFlags);
// <LegoRR.exe @0046a880>
bool32 __cdecl Teleporter_LiveObjectCallback_Update(LegoObject* liveObj, void* data_unused);
// <LegoRR.exe @0046a9c0>
bool32 __cdecl Teleporter_UpdateService(TeleporterService* teleporter, real32 elapsedGame);
// <LegoRR.exe @0046a9f0>
void __cdecl Teleporter_Update(real32 elapsedGame);
// <LegoRR.exe @0046aa20>
LegoObject_Type __cdecl Teleporter_GetServiceObjectType(TeleportObjectType teleportObjType);
// <LegoRR.exe @0046aab0>
void __cdecl Text_Load(TextWindow* param_1, TextWindow* param_2, sint32 imageX, sint32 imageY, real32 pauseTime);
// <LegoRR.exe @0046ac10>
void __cdecl Text_Initialise(char* filename, uint32 param_2, uint32 param_3, uint32 unused_int, Area2F* param_5, Area2F* unused_rect, real32 param_7);
// <LegoRR.exe @0046aca0>
void __cdecl Text_UpdatePositionAndSize(void);
// <LegoRR.exe @0046ad50>
void __cdecl Text_Clear(void);
// <LegoRR.exe @0046ad90>
bool32 __cdecl Text_GetTextType(char* textName, Text_Type* out_textType);
// <LegoRR.exe @0046add0>
void __cdecl Text_SetMessage(Text_Type textType, char* textMessage);
// <LegoRR.exe @0046ae70>
void __cdecl Text_SetMessageWithImage(Text_Type textType, char* message, char* filename, char* sfxName);
// <LegoRR.exe @0046aee0>
void __cdecl Text_SetNERPsMessage(char* text, bool32 unkFlags);
// <LegoRR.exe @0046af20>
void __cdecl Text_DisplayMessage(Text_Type textType, bool32 changeTiming, bool32 setFlag4);
// <LegoRR.exe @0046afc0>
void __cdecl Text_Update(real32 elapsedAbs);
// <LegoRR.exe @0046b490>
void __cdecl ToolTip_Initialise(Font* font, sint32 value2, sint32 value1, real32 float1, uint32 width, uint32 height, sint32 value32, real32 red, real32 green, real32 blue);
// <LegoRR.exe @0046b790>
bool32 __cdecl ToolTip_GetType(char* toolTipName, ToolTip_Type* out_toolTipType);
// <LegoRR.exe @0046b7e0>
void __cdecl ToolTip_SetText(ToolTip_Type toolTipType, char* msg, ...);
// <LegoRR.exe @0046b920>
void __cdecl ToolTip_AddIcon(ToolTip_Type toolTipType, Image* image);
// <LegoRR.exe @0046b9c0>
void __cdecl ToolTip_SetSFX(ToolTip_Type toolTipType, SFX_ID sfxType);
// <LegoRR.exe @0046b9f0>
void __cdecl ToolTip_SetFlag10(ToolTip_Type toolTipType, bool32 state);
// <LegoRR.exe @0046ba30>
void __cdecl ToolTip_AddFlag4(ToolTip_Type toolTipType);
// <LegoRR.exe @0046ba60>
void __cdecl ToolTip_ResetTimer(ToolTip_Type toolTipType);
// <LegoRR.exe @0046ba80>
void __cdecl ToolTip_Update(uint32 mousex, uint32 mousey, real32 elapsedAbs);
// <LegoRR.exe @0046bb70>
void __cdecl ToolTip_DrawBox(Area2F valueRect, real32 rcRed, real32 rcGreen, real32 rcBlue, real32 ln1Red, real32 ln1Green, real32 ln1Blue, real32 ln2Red, real32 ln2Green, real32 ln2Blue, bool32 halfTrans);
// <LegoRR.exe @0046bef0>
void __cdecl ToolTip_Draw(ToolTipData* toolTip, uint32 x, uint32 y);
// <LegoRR.exe @0046c2f0>
void __cdecl Upgrade_Part_Load(Upgrade_PartModel* upgradePart, sint32 objID, Container* root, char* filename);
// <LegoRR.exe @0046c370>
void __cdecl Upgrade_Part_Clone(Upgrade_PartModel* srcUpgradePart, Upgrade_PartModel* destUpgradePart);
// <LegoRR.exe @0046c3b0>
void __cdecl Upgrade_Part_Remove(Upgrade_PartModel* upgradePart);
// <LegoRR.exe @0046c3d0>
real32 __cdecl Upgrade_Part_MoveAnimation(Upgrade_PartModel* upgradePart, real32 elapsed, uint32 unused_unkFrameNo);
// <LegoRR.exe @0046c3f0>
bool32 __cdecl Upgrade_Part_SetActivity(Upgrade_PartModel* upgradePart, char* activityName);
// <LegoRR.exe @0046c420>
void __cdecl Upgrade_Load(UpgradesModel* upgrades, Config* act, char* gameName);
// <LegoRR.exe @0046c600>
void __cdecl Upgrade_SetUpgradeLevel(UpgradesModel* upgrades, uint32 objLevel);
// <LegoRR.exe @0046c690>
bool32 __cdecl Vehicle_IsCameraFlipDir(VehicleModel* vehicle);
// <LegoRR.exe @0046c6b0>
bool32 __cdecl Vehicle_SetActivity(VehicleModel* vehicle, char* activityName, real32 elapsed);
// <LegoRR.exe @0046c7d0>
void __cdecl Vehicle_SetUpgradeActivity(VehicleModel* vehicle, char* activityName);
// <LegoRR.exe @0046c9b0>
bool32 __cdecl Vehicle_Load(VehicleModel* vehicle, sint32 objID, Container* root, char* aeFilename, char* gameName);
// <LegoRR.exe @0046d0d0>
void __cdecl Vehicle_Remove(VehicleModel* vehicle);
// <LegoRR.exe @0046d190>
void __cdecl Vehicle_SwapPolyMedium(VehicleModel* vehicle, bool32 swap);
// <LegoRR.exe @0046d1e0>
void __cdecl Vehicle_SwapPolyHigh(VehicleModel* vehicle, bool32 swap);
// <LegoRR.exe @0046d200>
bool32 __cdecl Vehicle_CanUpgradeType(VehicleModel* vehicle, LegoObject_UpgradeType upgradeType, bool32 current);
// <LegoRR.exe @0046d240>
uint32 __cdecl Vehicle_GetUpgradeLevel(VehicleModel* vehicle);
// <LegoRR.exe @0046d250>
void __cdecl Vehicle_SetUpgradeLevel(VehicleModel* vehicle, uint32 objLevel);
// <LegoRR.exe @0046d280>
void __cdecl Vehicle_HideWheels(VehicleModel* vehicle, bool32 hide);
// <LegoRR.exe @0046d2b0>
bool32 __cdecl Vehicle_Clone(VehicleModel* srcVehicle, VehicleModel* destVehicle);
// <LegoRR.exe @0046d400>
void __cdecl Vehicle_SetOwnerObject(VehicleModel* vehicle, LegoObject* liveObj);
// <LegoRR.exe @0046d460>
real32 __cdecl Vehicle_GetAnimationTime(VehicleModel* vehicle);
// <LegoRR.exe @0046d480>
real32 __cdecl Vehicle_MoveAnimation(VehicleModel* vehicle, real32 elapsed1, real32 elapsed2, uint32 unkFrameNo);
// <LegoRR.exe @0046d520>
void __cdecl Vehicle_PopulateWheels(VehicleModel* vehicle);
// <LegoRR.exe @0046d580>
void __cdecl Vehicle_Hide(VehicleModel* vehicle, bool32 hide);
// <LegoRR.exe @0046d5f0>
bool32 __cdecl Vehicle_IsHidden(VehicleModel* vehicle);
// <LegoRR.exe @0046d610>
void __cdecl Vehicle_SetOrientation(VehicleModel* vehicle, real32 xDir, real32 yDir, real32 zDir);
// <LegoRR.exe @0046d640>
void __cdecl Vehicle_SetPosition(VehicleModel* vehicle, real32 xPos, real32 yPos, GetWorldZCallback zCallback, Map3D* map);
// <LegoRR.exe @0046dca0>
Container* __cdecl Vehicle_GetActivityContainer(VehicleModel* vehicle);
// <LegoRR.exe @0046dcb0>
Container* __cdecl Vehicle_GetNull(VehicleModel* vehicle, char* nullName, uint32 nullFrameNo);
// <LegoRR.exe @0046dd10>
Container* __cdecl Vehicle_GetCameraNull(VehicleModel* vehicle, uint32 frameNo);
// <LegoRR.exe @0046dd50>
Container* __cdecl Vehicle_GetDrillNull(VehicleModel* vehicle);
// <LegoRR.exe @0046dd80>
Container* __cdecl Vehicle_GetDepositNull(VehicleModel* vehicle);
// <LegoRR.exe @0046ddb0>
Container* __cdecl Vehicle_GetDriverNull(VehicleModel* vehicle);
// <LegoRR.exe @0046dde0>
Container* __cdecl Vehicle_GetCarryNull(VehicleModel* vehicle, uint32 frameNo);
// <LegoRR.exe @0046de20>
uint32 __cdecl Vehicle_GetCarryNullFrames(VehicleModel* vehicle);
// <LegoRR.exe @0046de30>
real32 __cdecl Vehicle_GetTransCoef(VehicleModel* vehicle);
// <LegoRR.exe @0046de50>
void __cdecl Water_Initialise(Container* root, Lego_Level* level);
// <LegoRR.exe @0046dfd0>
void __cdecl Water_InitGroups(Container* root, Lego_Level* level);
// <LegoRR.exe @0046e140>
void __cdecl Water_InitVertices(Container* root, Lego_Level* level);
// <LegoRR.exe @0046e480>
void __cdecl Water_Debug_LogContainerMesh(bool32 logWithValues);
// <LegoRR.exe @0046e4e0>
void __cdecl Water_Block_DestroyWallComplete(Lego_Level* level, uint32 bx, uint32 by);
// <LegoRR.exe @0046e5f0>
void __cdecl Water_Block_Debug_WKey(uint32 bx, uint32 by);
// <LegoRR.exe @0046e650>
void __cdecl Water_Update(Lego_Level* level, real32 elapsedGame);
// <LegoRR.exe @0046e8d0>
void __cdecl Water_UpdateMap3DBlocks(Lego_Level* level);
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
bool32 __cdecl Weapon_Initialise(Config* config, char* gameName);
// <LegoRR.exe @0046f390>
uint32 __cdecl Weapon_GetWeaponIDByName(char* weaponName);
// <LegoRR.exe @0046f3d0>
real32 __cdecl Weapon_GetRechargeTime(sint32 weaponID);
// <LegoRR.exe @0046f400>
real32 __cdecl Weapon_GetDischargeRate(sint32 weaponID);
// <LegoRR.exe @0046f430>
real32 __cdecl Weapon_GetWeaponRange(sint32 weaponID);
// <LegoRR.exe @0046f460>
real32 __cdecl Weapon_GetWallDestroyTime(sint32 weaponID, Lego_SurfaceType surfaceType);
// <LegoRR.exe @0046f490>
real32 __cdecl Weapon_GetDamageForObject(sint32 weaponID, LegoObject* liveObj);
// <LegoRR.exe @0046f530>
void __cdecl Weapon_GenericDamageObject(LegoObject* liveObj, sint32 weaponID, bool32 unkSlowDeathBool, real32 elapsed, Point2F* dir);
// <LegoRR.exe @0046f640>
void __cdecl Weapon_GunDamageObject(LegoObject* liveObj, real32 damage, bool32 reactToHit);
// <LegoRR.exe @0046f670>
void __cdecl Weapon_Projectile_FUN_0046f670(Weapon_Projectile* projectile);
// <LegoRR.exe @0046f810>
void __cdecl Weapon_Update(real32 elapsedGame);
// <LegoRR.exe @0046f8d0>
bool32 __cdecl Weapon_LegoObject_Callback_FUN_0046f8d0(LegoObject* liveObj, real32* pElapsed);
// <LegoRR.exe @0046fa30>
void __cdecl Weapon_GunHitObject(LegoObject* liveObj, Vector3F* dir, Vector3F* opt_worldPos, sint32 weaponID, WeaponKnownType knownWeapon);
// <LegoRR.exe @0046fbe0>
void __cdecl Weapon_Projectile_UpdatePath(Weapon_Projectile* projectile, real32 elapsed);
// <LegoRR.exe @0046fdb0>
bool32 __cdecl Weapon_Projectile_AddStraightPath(LegoObject* liveObj, Vector3F* fromPos, Vector3F* toPos, sint32 weaponID, WeaponKnownType knownWeapon);
// <LegoRR.exe @0046ff30>
bool32 __cdecl Weapon_Projectile_AddCurvedPath(LegoObject* liveObj, Vector3F* fromPos, Vector3F* toPos, sint32 weaponID, WeaponKnownType knownWeapon);
// <LegoRR.exe @004701b0>
void __cdecl Weapon_GetObjectTypeAndID_ByKnownWeaponType(WeaponKnownType knownWeapon, LegoObject_Type* out_objType, LegoObject_ID* out_objID);
// <LegoRR.exe @00470230>
sint32 __cdecl Weapon_Projectile_GetNextAvailable(void);
// <LegoRR.exe @00470250>
sint32 __cdecl Weapon_Lazer_GetNextAvailable(void);
// <LegoRR.exe @00470270>
LegoObject* __cdecl Weapon_FireLazer(Vector3F* fromPos, Vector3F* dir, LegoObject* liveObj, real32 elapsed, real32 weaponRange, sint32 weaponID, real32 coef);
// <LegoRR.exe @00470520>
bool32 __cdecl Weapon_LegoObject_Collision_FUN_00470520(LegoObject* liveObj, Point2F* param_2, Point2F* param_3, bool32 param_4);
// <LegoRR.exe @00470570>
bool32 __cdecl Weapon_LegoObject_CollisionBox_FUN_00470570(LegoObject* liveObj, Point2F* param_2, Point2F* param_3, Point2F* optout_point, bool32 param_5);
// <LegoRR.exe @00470800>
bool32 __cdecl Weapon_LegoObject_CollisionRadius_FUN_00470800(LegoObject* liveObj, Point2F* param_2, Point2F* param_3, bool32 param_4);
// <LegoRR.exe @004708f0>
bool32 __cdecl Weapon_LegoObject_TestCollision_FUN_004708f0(LegoObject* liveObj, Point2F* fromPos, Point2F* scalar2D);
// <LegoRR.exe @00470950>
void __cdecl Weapon_Lazer_Add(Container* cont, Vector3F* fromPos, Vector3F* toPos);
// <LegoRR.exe @00470a20>
void __cdecl Weapon_Lazer_InitMesh(Mesh* mesh, real32 thickness, Vector3F* fromPos, Vector3F* toPos, real32 red, real32 green, real32 blue, real32 alpha);
// <LegoRR.exe @00471580>
WeaponsModel* __cdecl Weapon_LegoObject_GetWeaponsModel(LegoObject* liveObj);
// <LegoRR.exe @004715b0>
real32 __cdecl Weapon_LegoObject_GetWeaponTimer(LegoObject* liveObj, uint32 frameNo);
// <LegoRR.exe @004715d0>
void __cdecl Weapon_LegoObject_SetWeaponTimer(LegoObject* liveObj, real32 timer, uint32 frameNo);
// <LegoRR.exe @004715f0>
bool32 __cdecl Weapon_MathUnk_CheckVectorsZScalar_InRange(Vector3F* vectorPos, Vector3F* vectorScaled, real32 minZ, real32 maxZ, real32 scalar);
// <LegoRR.exe @00471630>
bool32 __cdecl Weapon_LegoObject_Callback_FUN_00471630(LegoObject* liveObj, SearchData18_2* search);
// <LegoRR.exe @004718f0>
void __cdecl Weapon_LegoObject_FUN_004718f0(SearchData18_2* search);
// <LegoRR.exe @00471b20>
bool32 __cdecl Weapon_DoCallbacksSearch_FUN_00471b20(Vector3F* vecCector, Vector3F* vecDistance, LegoObject** out_liveObj, real32* ref_float_4, undefined4 param_5);
// <LegoRR.exe @00471b90>
bool32 __cdecl Weapon_LegoObject_DoCallbacksSearch_FUN_00471b90(LegoObject* liveObj, LegoObject* otherObj);
// <LegoRR.exe @00471c20>
bool32 __cdecl Weapon_LegoObject_SeeThroughWalls_FUN_00471c20(LegoObject* liveObj, LegoObject* otherObj);
// <LegoRR.exe @00471ce0>
Container* __cdecl Weapon_GetFireNull(WeaponsModel* weapons, uint32 frameNo, uint32 pairNo);
// <LegoRR.exe @00471d00>
Container* __cdecl Weapon_GetXPivotNull(WeaponsModel* weapons, uint32 frameNo);
// <LegoRR.exe @00471d10>
Container* __cdecl Weapon_GetYPivotNull(WeaponsModel* weapons, uint32 frameNo);
// <LegoRR.exe @00471d20>
void __cdecl Weapon_PivotTracker(WeaponsModel* weapons, Vector3F* targetWorldPos, real32 elapsed, bool32 assignTarget, uint32 frameNo);
// <LegoRR.exe @00471f30>
void __cdecl Weapon_GetVectors44(WeaponsModel* weapons, Vector3F* out_vector44, uint32 frameNo);
// <LegoRR.exe @00471f60>
bool32 __cdecl Weapon_LegoObject_GetCollCenterPosition(LegoObject* liveObj, Vector3F* out_vector);
// <LegoRR.exe @00471fa0>
bool32 __cdecl Weapon_LegoObject_IsActiveTracker(LegoObject* liveObj);
// <LegoRR.exe @00471fe0>
bool32 __cdecl Weapon_LegoObject_UpdateLaserTracker(LegoObject* liveObj, real32 elapsed, uint32 frameNo);
// <LegoRR.exe @004721c0>
bool32 __cdecl Weapon_LegoObject_UpdateNonLaserTracker(LegoObject* liveObj, real32 elapsed, uint32 frameNo);
// <LegoRR.exe @00472280>
bool32 __cdecl Weapon_LegoObject_UpdateTracker(LegoObject* liveObj, real32 elapsed);
// <LegoRR.exe @00472320>
bool32 __cdecl Weapon_Callback_RemoveProjectileReference(LegoObject* liveObj, LegoObject* projectileObj);
// <LegoRR.exe @00472340>
bool32 __cdecl Weapon_LegoObject_WithinWeaponRange(LegoObject* liveObj, LegoObject* otherObj);
// <LegoRR.exe @004723f0>
bool32 __cdecl Weapon_LegoObject_WithinAwarenessRange(LegoObject* liveObj, LegoObject* otherObj);
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
Container* __cdecl Container_GetRoot(void);
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
void __cdecl Container_Mesh_SetQuality(Container* cont, D3DRMGroupIndex groupID, Graphics_Quality quality);
// <LegoRR.exe @00474da0>
bool32 __cdecl Container_Mesh_IsGroupHidden(Container* cont, D3DRMGroupIndex group);
// <LegoRR.exe @00474df0>
void __cdecl Container_Mesh_HideGroup(Container* cont, D3DRMGroupIndex group, bool32 hide);
// <LegoRR.exe @00474ec0>
bool32 __cdecl Container_Mesh_HandleSeperateMeshGroups(IDirect3DRMMesh** ref_mesh, D3DRMGroupIndex* ref_groupID);
// <LegoRR.exe @00474f00>
bool32 __cdecl Container_Mesh_GetGroup(Container* cont, D3DRMGroupIndex groupID, uint32* out_vertexCount, uint32* out_faceCount, uint32* out_vPerFace, uint32* out_faceDataSize, uint32* out_faceData);
// <LegoRR.exe @00474f80>
uint32 __cdecl Container_Mesh_GetVertices(Container* cont, D3DRMGroupIndex groupID, uint32 index, uint32 count, Vertex* out_retArray);
// <LegoRR.exe @00474ff0>
uint32 __cdecl Container_Mesh_SetVertices(Container* cont, D3DRMGroupIndex groupID, uint32 index, uint32 count, Vertex* values);
// <LegoRR.exe @00475060>
void __cdecl Container_Mesh_SetTexture(Container* cont, D3DRMGroupIndex groupID, Container_Texture* ref_itext);
// <LegoRR.exe @004750f0>
void __cdecl Container_Mesh_SetPerspectiveCorrection(Container* cont, D3DRMGroupIndex groupID, bool32 on);
// <LegoRR.exe @00475150>
bool32 __cdecl Container_Mesh_Scale(Container* cont, real32 x, real32 y, real32 z);
// <LegoRR.exe @004751d0>
bool32 __cdecl Container_Mesh_GetBox(Container* cont, Box3F* out_box);
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
real32 __cdecl Container_MoveAnimation(Container* cont, real32 delta);
// <LegoRR.exe @00475400>
real32 __cdecl Container_SetAnimationTime(Container* cont, real32 time);
// <LegoRR.exe @004755c0>
void __cdecl Container_ForceAnimationUpdate(Container* cont);
// <LegoRR.exe @00475650>
real32 __cdecl Container_GetAnimationTime(Container* cont);
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
void __cdecl Container_AddRotation(Container* cont, Container_Combine combine, real32 x, real32 y, real32 z, real32 angle);
// <LegoRR.exe @00475870>
void __cdecl Container_AddScale(Container* cont, Container_Combine combine, real32 x, real32 y, real32 z);
// <LegoRR.exe @004758a0>
void __cdecl Container_AddTranslation(Container* cont, Container_Combine combine, real32 x, real32 y, real32 z);
// <LegoRR.exe @004758d0>
void __cdecl Container_ClearTransform(Container* cont);
// <LegoRR.exe @00475970>
void __cdecl Container_AddTransform(Container* cont, Container_Combine combine, Matrix4F* mat);
// <LegoRR.exe @00475990>
real32 __cdecl Container_GetZXRatio(Container* cont);
// <LegoRR.exe @004759d0>
void __cdecl Container_SetParent(Container* child, Container* parent);
// <LegoRR.exe @00475a60>
Container* __cdecl Container_GetParent(Container* cont);
// <LegoRR.exe @00475ab0>
real32 __cdecl Container_GetTransCoef(Container* cont);
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
real32 __cdecl Container_Frame_GetCurrTime(IDirect3DRMFrame3* frame);
// <LegoRR.exe @00476480>
real32 __cdecl Container_Frame_GetTransCo(IDirect3DRMFrame3* frame);
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
Viewport* __cdecl Viewport_Create(real32 xposf, real32 yposf, real32 widthf, real32 heightf, Container* contCamera);
// <LegoRR.exe @00477110>
Viewport* __cdecl Viewport_CreatePixel(sint32 xPos, sint32 yPos, uint32 width, uint32 height, Container* contCamera);
// <LegoRR.exe @004771d0>
void __cdecl Viewport_GetSize(Viewport* view, uint32* out_width, uint32* out_height);
// <LegoRR.exe @00477210>
void __cdecl Viewport_SetCamera(Viewport* view, Container* contCamera);
// <LegoRR.exe @00477230>
Container* __cdecl Viewport_GetCamera(Viewport* view);
// <LegoRR.exe @00477270>
void __cdecl Viewport_SetBackClip(Viewport* view, real32 dist);
// <LegoRR.exe @00477290>
real32 __cdecl Viewport_GetBackClip(Viewport* view);
// <LegoRR.exe @004772b0>
real32 __cdecl Viewport_GetFrontClip(Viewport* view);
// <LegoRR.exe @004772d0>
void __cdecl Viewport_Clear(Viewport* view, bool32 full);
// <LegoRR.exe @00477410>
void __cdecl Viewport_Render(Viewport* view, Container* root, real32 delta);
// <LegoRR.exe @004774e0>
void __cdecl Viewport_Remove(Viewport* view);
// <LegoRR.exe @00477500>
void __cdecl Viewport_SmoothSetField(Viewport* view, real32 fov);
// <LegoRR.exe @00477510>
void __cdecl Viewport_SetField(Viewport* view, real32 fov);
// <LegoRR.exe @00477530>
real32 __cdecl Viewport_GetField(Viewport* view);
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
char* __cdecl Util_StrCpy(char* strSource);
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
MainCLFlags __cdecl Main_GetCLFlags(void);
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
bool32 __cdecl Main_SetupDirect3D(Graphics_Device* dev, IDirectDraw* ddraw1, IDirectDrawSurface4* backSurf, bool32 doubleBuffered);
// <LegoRR.exe @004785d0>
void __cdecl Main_AdjustWindowRect(LPRECT lpRect);
// <LegoRR.exe @004785f0>
void __cdecl Main_Setup3D(Graphics_Quality renderQuality, bool32 dither, bool32 linearFilter, bool32 mipMap, bool32 mipMapLinear, bool32 blendTransparency, bool32 sortTransparency);
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
Config* __cdecl Config_Load(char* filename);
// <LegoRR.exe @00479210>
char* __cdecl Config_BuildStringID(char* keyPath1, ...);
// <LegoRR.exe @004792b0>
Config* __cdecl Config_FindArray(Config* prop, char* keyPath);
// <LegoRR.exe @004792e0>
Config* __cdecl Config_GetNextItem(Config* prop);
// <LegoRR.exe @00479310>
char* __cdecl Config_GetStringValue(Config* prop, char* keyPath);
// <LegoRR.exe @00479370>
char* __cdecl Config_GetTempStringValue(Config* prop, char* keyPath);
// <LegoRR.exe @00479390>
BoolTri __cdecl Config_GetBoolValue(Config* prop, char* keyPath);
// <LegoRR.exe @004793d0>
real32 __cdecl Config_GetAngle(Config* prop, char* keyPath);
// <LegoRR.exe @00479430>
bool32 __cdecl Config_GetRGBValue(Config* prop, char* keyPath, real32* out_r, real32* out_g, real32* out_b);
// <LegoRR.exe @00479500>
void __cdecl Config_Free(Config* root);
// <LegoRR.exe @00479530>
Config* __cdecl Config_Create(Config* prev);
// <LegoRR.exe @00479580>
void __cdecl Config_Remove(Config* prop);
// <LegoRR.exe @004795a0>
Config* __cdecl Config_FindItem(Config* prop, char* keyPath);
// <LegoRR.exe @00479750>
void __cdecl Config_AddList(void);
// <LegoRR.exe @004797c0>
Vector3F* __cdecl Maths_Vector3DRandom(Vector3F* out_vector);
// <LegoRR.exe @004797d0>
Vector3F* __cdecl Maths_Vector3DRotate(Vector3F* out_vector, Vector3F* v, Vector3F* axis, real32 theta);
// <LegoRR.exe @004797f0>
Vector3F* __cdecl Maths_PlaneNormal(Vector3F* out_vector, Vector3F* p1, Vector3F* p2, Vector3F* p3);
// <LegoRR.exe @004798f0>
real32 __cdecl Maths_TriangleAreaZ(Vector3F* p1, Vector3F* p2, Vector3F* p3, bool32 bfc);
// <LegoRR.exe @00479b60>
sint16 __cdecl Maths_Rand(void);
// <LegoRR.exe @00479b70>
real32 __cdecl Maths_RandRange(real32 low, real32 high);
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
sint32 __cdecl Sound3D_Play2(Sound3DPlay mode, IDirect3DRMFrame3* frame, sint32 soundTableIndex, bool32 loop, Vector3F* opt_wPos);
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
real32 __cdecl Sound3D_GetSamplePlayTime(sint32 handle);
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
real32 __cdecl Sound3D_SetRollOffFactor(real32 rollOff);
// <LegoRR.exe @0047c420>
sint32 __cdecl Sound3D_MinVolume(void);
// <LegoRR.exe @0047c430>
void __cdecl DirectDraw_Initialise(HWND hWnd);
// <LegoRR.exe @0047c480>
bool32 __cdecl DirectDraw_EnumDrivers(Graphics_Driver* ref_list, uint32* out_count);
// <LegoRR.exe @0047c4b0>
bool32 __stdcall DirectDraw_EnumDriverCallback(LPGUID lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID lpContext);
// <LegoRR.exe @0047c5a0>
bool32 __cdecl DirectDraw_EnumDevices(Graphics_Driver* driver, Graphics_Device* ref_list, uint32* out_count);
// <LegoRR.exe @0047c640>
HRESULT __stdcall DirectDraw_EnumDeviceCallback(LPGUID lpGuid, LPSTR lpDeviceDescription, LPSTR lpDeviceName, D3DDEVICEDESC_V1* lpHWDesc, D3DDEVICEDESC_V1* lpHELDesc, LPVOID lpContext);
// <LegoRR.exe @0047c770>
bool32 __cdecl DirectDraw_EnumModes(Graphics_Driver* driver, bool32 fullScreen, Graphics_Mode* ref_list, uint32* out_count);
// <LegoRR.exe @0047c810>
HRESULT __stdcall DirectDraw_EnumModeCallback(DDSURFACEDESC2* lpDDSurfaceDesc, LPVOID lpContext);
// <LegoRR.exe @0047c8d0>
bool32 __cdecl DirectDraw_Setup(bool32 fullscreen, Graphics_Driver* driver, Graphics_Device* device, Graphics_Mode* screen, uint32 xPos, uint32 yPos, uint32 width, uint32 height);
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
FileSys __cdecl _File_GetSystem(File* f);
// <LegoRR.exe @004800f0>
FileSys __cdecl _File_CheckSystem(char* fName, char* mode);
// <LegoRR.exe @00480160>
bool32 __cdecl _File_OpenWad(WADFILE* wad, char* fName);
// <LegoRR.exe @00480190>
File* __cdecl _File_Alloc(FileSys fType);
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
Mesh* __cdecl Mesh_CreateOnFrame(IDirect3DRMFrame3* frame, MeshRenderCallback renderFunc, uint32 renderFlags, void* data, Mesh_Type type);
// <LegoRR.exe @00480bc0>
Mesh* __cdecl Mesh_Clone(Mesh* mesh, IDirect3DRMFrame3* frame);
// <LegoRR.exe @00480ca0>
Mesh* __cdecl Mesh_Load(char* filename, IDirect3DRMFrame3* frame, bool32 noTextures);
// <LegoRR.exe @00480d80>
bool32 __cdecl Mesh_ParseLWO(char* basePath, Mesh* mesh, APPOBJ* lightWaveObject, bool32 noTextures);
// <LegoRR.exe @00481ae0>
void __cdecl Mesh_GetSurfInfo(char* basePath, APPOBJ* lightWaveObject, Mesh_LightWave_Surface* lightWaveSurf, bool32 noTextures);
// <LegoRR.exe @00481d80>
bool32 __cdecl Mesh_GetTextureSeqInfo(char* tname, char* out_tfname, sint32* out_tstart, sint32* out_tnumlen);
// <LegoRR.exe @00481e40>
void __cdecl Mesh_GetNextInSequence(char* baseName, char* out_nextTextName, uint32* ref_texNum, uint32 tnumlen);
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
void __cdecl Mesh_SetVertices(Mesh* mesh, D3DRMGroupIndex groupID, uint32 index, uint32 count, Vertex* vertices);
// <LegoRR.exe @00482730>
void __cdecl Mesh_GetVertices(Mesh* mesh, D3DRMGroupIndex groupID, uint32 index, uint32 count, Vertex* out_vertices);
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
bool32 __cdecl Mesh_SetGroupColour(Mesh* mesh, D3DRMGroupIndex groupID, real32 r, real32 g, real32 b, Mesh_Colour type);
// <LegoRR.exe @004836c0>
D3DMaterial* __cdecl Mesh_GetGroupMaterial(Mesh* mesh, D3DRMGroupIndex groupID);
// <LegoRR.exe @004836e0>
bool32 __cdecl Mesh_SetGroupMaterialValues(Mesh* mesh, D3DRMGroupIndex groupID, real32 value, Mesh_Colour matType);
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
bool32 __cdecl Key_Find(char* name, Keys8* out_keyCode);
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
real32 __cdecl Draw_DotCircle(Point2F* pos, uint32 radius, uint32 dots, real32 r, real32 g, real32 b, DrawEffect effect);
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
real32 __cdecl Lws_FindPrevKey(Lws_Node* node, real32 time, uint16* prev);
// <LegoRR.exe @00488010>
void __cdecl Lws_AnimateTextures(Lws_Info* scene, Lws_Node* node);
// <LegoRR.exe @004880a0>
void __cdecl Lws_HandleTrigger(Lws_Info* scene, Lws_Node* node);
// <LegoRR.exe @00488190>
bool32 __cdecl Lws_KeyPassed(Lws_Info* scene, uint32 key);
// <LegoRR.exe @00488280>
real32 __cdecl Lws_FindPrevDissolve(Lws_Node* node, real32 time, uint16* prev);
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
void __cdecl Mem_Free(void* buffer);
// <LegoRR.exe @0048de90>
void* __cdecl Mem_Alloc(uint32 size);
// <LegoRR.exe @0048df40>
void* __cdecl Mem_ReAlloc(void* memblock, uint32 size);
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
sint32 __cdecl sscanf(char* buffer, char* format, ...);
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

