#pragma once
#ifndef LEGORR__REGISTRY_H
#define LEGORR__REGISTRY_H

#include <windows.h>  // for BOOL typedef?

/*#ifndef REG_NONE
#define REG_NONE 0
#else
static_assert(REG_NONE == 0)
#endif

#ifndef REG_SZ
#define REG_SZ 1
#else
static_assert(REG_SZ == 1)
#endif*/

#pragma region /// TYPES ////////////////////////////////

enum RegistryValueType : unsigned int
{
	REGVALUE_NONE   = REG_NONE /*0*/,
	REGVALUE_STRING = REG_SZ   /*1*/,
};

#pragma endregion


#pragma region /// FUNCTIONS ////////////////////////////

// [internal]
// <LegoRR.exe @0048b5f0>
const char* __cdecl Reg_SplitRootKey(const char* fullKey, char* out_rootKey);

// [visible]
// <LegoRR.exe @0048b620>
BOOL __cdecl Reg_QueryString_FromLocalMachine(const char* subKey, const char* valueName, RegistryValueType valueType, char* out_buffer, unsigned int bufferSize);

// valueType must be 0 (REG_NONE) or 1 (REG_SZ)... but otherwise, both values do the same thing
// [internal]
// <LegoRR.exe @0048b650>
BOOL __cdecl Reg_QueryString(HKEY hKey, const char* subKey, const char* valueName, RegistryValueType valueType, char* out_buffer, unsigned int bufferSize);

#pragma endregion


#endif /* LEGORR__REGISTRY_H */
