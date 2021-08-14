// Registry.h : Declares common registry types and functions used by LegoRR / CLGen.
//
/// STATUS: [COMPLETE]
/// PURPOSE: Windows Registry read/write access for SZ (STRING) and DWORD types.
///
/// NAMESPACE: lego::registry
/// INITIALIZE: (none)

#pragma once

#include "Common.h"


#pragma region Enums
namespace lego {

// Supported registry value types for reading and writing
enum RegistryType : unsigned int
{
	REGISTRY_STRING = 0, // REG_SZ    (1)
	REGISTRY_NUMBER = 1, // REG_DWORD (4)
};
static_assert(sizeof(RegistryType) == 0x4, "");

} /* namespace lego */
#pragma endregion



#pragma region Functions
namespace lego::registry {

/// PRIVATE:
// <LegoRR.exe @0048b5f0>
// <CLGen.exe @00401660>
const char* __cdecl Registry_SplitRootKey(const char* fullKey, char* out_rootKey);

/// PUBLIC:
// <LegoRR.exe @0048b620>
BOOL __cdecl Registry_QueryValueOnLM(const char* key, const char* valueName, RegistryType valueType, void* out_buffer, unsigned int bufferSize);
// The `SetValue` functions are unused by Lego.exe,
//  but are included due to being the "other half" of the Registry functions seen in CLGen.
// <CLGen.exe @00401690>
BOOL __cdecl Registry_SetValueOnLM(const char* key, const char* valueName, RegistryType valueType, const void* in_buffer, unsigned int bufferSize);

/// PRIVATE: [might be public, but unused]
// valueType must be 0 (REGISTRY_STRING) or 1 (REGISTRY_NUMBER),
//  but otherwise, both values do the same thing.
// <LegoRR.exe @0048b650>
BOOL __cdecl Registry_QueryValue(HKEY hKey, const char* subKey, const char* valueName, RegistryType valueType, void* out_buffer, unsigned int bufferSize);
// valueType must be 0 (REGISTRY_STRING) or 1 (REGISTRY_NUMBER).
// <CLGen.exe @004016c0>
BOOL __cdecl Registry_SetValue(HKEY hKey, const char* subKey, const char* valueName, RegistryType valueType, const void* in_buffer, unsigned int bufferSize);

} /* namespace lego::registry */
#pragma endregion

