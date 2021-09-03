#pragma once

#include "../Common.h"

namespace lego {
#pragma region Functions

// <LegoRR.exe @004790b0>
void __cdecl ReservedPool_CFGProperty___Init(void);
// <LegoRR.exe @004790e0>
void __cdecl ReservedPool_CFGProperty___Cleanup(void);
// <LegoRR.exe @00479120>
CFGRoot* __cdecl CFG_Open(const char* filename);
// <LegoRR.exe @00479210>
const char* __cdecl CFG_JoinPath(const char* keyPath1, ...);
// <LegoRR.exe @004792b0>
const CFGProperty* __cdecl CFG_GetChildren(const CFGProperty* prop, const char* keyPath);
// <LegoRR.exe @004792e0>
const CFGProperty* __cdecl CFG_NextFlat(const CFGProperty* prop);
// <LegoRR.exe @00479310>
char* __cdecl CFG_CopyString(const CFGProperty* prop, const char* keyPath);
// <LegoRR.exe @00479370>
const char* __cdecl CFG_ReadString(const CFGProperty* prop, const char* keyPath);
// <LegoRR.exe @00479390>
BOOL3 __cdecl CFG_ReadBool(const CFGProperty* prop, const char* keyPath);
// <LegoRR.exe @004793d0>
float __cdecl CFG_ReadRadians(const CFGProperty* prop, const char* keyPath);
// <LegoRR.exe @00479430>
float __cdecl CFG_ReadRGBF(const CFGProperty* prop, const char* keyPath, float* out_r, float* out_g, float* out_b);
// <LegoRR.exe @00479500>
void __cdecl CFG_Close(CFGRoot* root);
// <LegoRR.exe @00479530>
CFGProperty* __cdecl ReservedPool_CFGProperty___Next(CFGProperty* previous);
// <LegoRR.exe @00479580>
void __cdecl ReservedPool_CFGProperty___Release(CFGProperty* prop);
// <LegoRR.exe @004795a0>
const CFGProperty* __cdecl CFG_GetProperty(const CFGProperty* prop, const char* keyPath);
// <LegoRR.exe @00479750>
void __cdecl ReservedPool_CFGProperty___Alloc(void);


#pragma endregion

#pragma region Macro Functions


#pragma endregion
} /* namespace lego */
