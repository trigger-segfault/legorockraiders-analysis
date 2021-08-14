// Registry.cpp : Defines common registry functions used by LegoRR / CLGen.
//
/// STATUS: [COMPLETE]

#include "Registry.h"


using namespace lego;
using namespace lego::registry;


#pragma region Functions

// <LegoRR.exe @0048b5f0>
// <CLGen.exe @00401660>
const char* __cdecl lego::registry::Registry_SplitRootKey(const char* fullKey, char* out_rootKey)
{
	*out_rootKey = '\0';
	// find first separator
	while (*fullKey != '\0' && *fullKey != '\\') {
		*out_rootKey++ = *fullKey++;
	}

	if (*fullKey == '\\')
		fullKey++; // skip separator
	*out_rootKey = '\0';

	return fullKey; // return key path after base key
}

// <LegoRR.exe @0048b620>
BOOL __cdecl lego::registry::Registry_QueryValueOnLM(const char* key, const char* valueName, RegistryType valueType, void* out_buffer, unsigned int bufferSize)
{
	return Registry_QueryValue((HKEY)HKEY_LOCAL_MACHINE /*0x80000002*/, key, valueName, valueType, out_buffer, bufferSize);
}

// <CLGen.exe @00401690>
BOOL __cdecl lego::registry::Registry_SetValueOnLM(const char* key, const char* valueName, RegistryType valueType, const void* in_buffer, unsigned int bufferSize)
{
	return Registry_SetValue((HKEY)HKEY_LOCAL_MACHINE /*0x80000002*/, key, valueName, valueType, in_buffer, bufferSize);
}

// valueType must be 0 (REGISTRY_STRING) or 1 (REGISTRY_NUMBER),
//  but otherwise, both values do the same thing.
// <LegoRR.exe @0048b650>
BOOL __cdecl lego::registry::Registry_QueryValue(HKEY hKey, const char* subKey, const char* valueName, RegistryType valueType, void* out_buffer, unsigned int bufferSize)
{
	char rootSubKey[100];

	const char* splitSubKey = Registry_SplitRootKey(subKey, rootSubKey);
	if (rootSubKey[0] != '\0') {
		// rootSubKey isn't empty, we have more keys to recurse through
		HKEY hSubKey;
		::RegCreateKeyA(hKey, rootSubKey, &hSubKey);
		if (hSubKey == nullptr)
			return false;

		// recursively open/create subkeys to get to where we need
		BOOL recurseResult = Registry_QueryValue(hSubKey, splitSubKey, valueName, valueType, out_buffer, bufferSize);
		::RegCloseKey(hSubKey);
		return recurseResult;
	}

	DWORD outValueType = REG_NONE /*0*/;
	LSTATUS result = ERROR_SUCCESS /*0*/; // dummy init to satisfy switch statement restrictions
	switch (valueType) {
	case REGISTRY_STRING /*0*/:
		result = ::RegQueryValueExA(hKey, valueName, nullptr, &outValueType, (LPBYTE)out_buffer, (LPDWORD)&bufferSize);
		return (result == ERROR_SUCCESS /*0*/);
	case REGISTRY_NUMBER /*1*/:
		result = ::RegQueryValueExA(hKey, valueName, nullptr, &outValueType, (LPBYTE)out_buffer, (LPDWORD)&bufferSize);
		return (result == ERROR_SUCCESS /*0*/);
	default:
		return false;
	}
}

// valueType must be 0 (REGISTRY_STRING) or 1 (REGISTRY_NUMBER).
// <CLGen.exe @004016c0>
BOOL __cdecl lego::registry::Registry_SetValue(HKEY hKey, const char* subKey, const char* valueName, RegistryType valueType, const void* in_buffer, unsigned int bufferSize)
{
	char rootSubKey[100];

	const char* splitSubKey = Registry_SplitRootKey(subKey, rootSubKey);
	if (rootSubKey[0] != '\0') {
		// rootSubKey isn't empty, we have more keys to recurse through
		HKEY hSubKey;
		::RegCreateKeyA(hKey, rootSubKey, &hSubKey);
		if (hSubKey == nullptr)
			return false;

		// recursively open/create subkeys to get to where we need
		BOOL recurseResult = Registry_SetValue(hSubKey, splitSubKey, valueName, valueType, in_buffer, bufferSize);
		::RegCloseKey(hSubKey);
		return recurseResult;
	}

	switch (valueType) {
	case REGISTRY_STRING /*0*/:
		::RegSetValueExA(hKey, valueName, 0, REG_SZ /*1*/, (const BYTE*)in_buffer, bufferSize);
		return true;
	case REGISTRY_NUMBER /*1*/:
		::RegSetValueExA(hKey, valueName, 0, REG_DWORD /*4*/, (const BYTE*)in_buffer, bufferSize);
		return true;
	default:
		return false;
	}
}

#pragma endregion
