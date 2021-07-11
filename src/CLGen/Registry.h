// Registry.h : Declares common registry types and functions used by LegoRR / CLGen
//

#pragma once

#include "framework.h"

namespace lego {
namespace registry {

	// Supported registry value types for reading and writing
	enum RegistryType : unsigned int
	{
		REGISTRY_STRING = 0, // REG_SZ    (1)
		REGISTRY_NUMBER = 1, // REG_DWORD (4)
	};

	// <LegoRR.exe @0048b5f0>
	// <CLGen.exe @00401660>
	//const char* __cdecl SplitRootKey(const char* fullKey, char* out_rootKey);

	// The `QueryValue` functions are unused by CLGen.exe,
	//  but are included due to being the "other half" of the Registry functions seen in LegoRR.

	// <LegoRR.exe @0048b620>
	BOOL __cdecl QueryValue_OnLocalMachine(const char* subKey, const char* valueName, RegistryType valueType, void* out_buffer, unsigned int bufferSize);

	// valueType must be 0 (REGISTRY_STRING) or 1 (REGISTRY_NUMBER),
	//  but otherwise, both values do the same thing.
	// <LegoRR.exe @0048b650>
	BOOL __cdecl QueryValue(HKEY hKey, const char* subKey, const char* valueName, RegistryType valueType, void* out_buffer, unsigned int bufferSize);

	// <CLGen.exe @00401690>
	BOOL __cdecl SetValue_OnLocalMachine(const char* subKey, const char* valueName, RegistryType valueType, const void* in_buffer, unsigned int bufferSize);

	// valueType must be 0 (REGISTRY_STRING) or 1 (REGISTRY_NUMBER).
	// <CLGen.exe @004016c0>
	BOOL __cdecl SetValue(HKEY hKey, LPCSTR subKey, LPCSTR valueName, RegistryType valueType, const void* in_buffer, unsigned int bufferSize);

} /* namespace registry */
} /* namespace lego */
