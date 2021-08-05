#pragma once


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

