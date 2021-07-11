// Registry.cpp : Defines common registry functions used by LegoRR / CLGen
//

#include "framework.h"
#include "Registry.h"


namespace lego {
namespace registry {

	// <LegoRR.exe @0048b5f0>
	// <CLGen.exe @00401660>
	static const char* __cdecl SplitRootKey(const char* fullKey, char* out_rootKey);

} /* namespace registry */
} /* namespace lego */


using namespace lego::registry;


// <LegoRR.exe @0048b5f0>
// <CLGen.exe @00401660>
static const char* __cdecl lego::registry::SplitRootKey(const char* fullKey, char* out_rootKey)
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
BOOL __cdecl lego::registry::QueryValue_OnLocalMachine(const char* subKey, const char* valueName, RegistryType valueType, void* out_buffer, unsigned int bufferSize)
{
	return QueryValue((HKEY)HKEY_LOCAL_MACHINE /*0x80000002*/, subKey, valueName, valueType, out_buffer, bufferSize);
}

// valueType must be 0 (REGISTRY_STRING) or 1 (REGISTRY_NUMBER),
//  but otherwise, both values do the same thing.
// <LegoRR.exe @0048b650>
BOOL __cdecl lego::registry::QueryValue(HKEY hKey, const char* subKey, const char* valueName, RegistryType valueType, void* out_buffer, unsigned int bufferSize)
{
	char rootSubKey[100];

	const char* splitSubKey = SplitRootKey(subKey, rootSubKey);
	if (*rootSubKey != '\0') {
		// rootSubKey isn't empty, we have more keys to recurse through
		HKEY hSubKey;
		RegCreateKeyA(hKey, rootSubKey, &hSubKey);
		if (hSubKey == nullptr)
			return FALSE;

		// recursively open/create subkeys to get to where we need
		BOOL recurseResult = QueryValue(hSubKey, splitSubKey, valueName, valueType, out_buffer, bufferSize);
		RegCloseKey(hSubKey);
		return recurseResult;
	}

	DWORD outValueType = REG_NONE /*0*/;
	LSTATUS result = ERROR_SUCCESS /*0*/; // dummy init to satisfy switch statement restrictions
	switch (valueType) {
	case REGISTRY_STRING /*0*/:
		result = RegQueryValueExA(hKey, valueName, nullptr, &outValueType, (LPBYTE)out_buffer, (LPDWORD)&bufferSize);
		return (result == ERROR_SUCCESS /*0*/);
	case REGISTRY_NUMBER /*1*/:
		result = RegQueryValueExA(hKey, valueName, nullptr, &outValueType, (LPBYTE)out_buffer, (LPDWORD)&bufferSize);
		return (result == ERROR_SUCCESS /*0*/);
	default:
		return FALSE;
	}
}

// <CLGen.exe @00401690>
BOOL __cdecl lego::registry::SetValue_OnLocalMachine(const char* subKey, const char* valueName, RegistryType valueType, const void* in_buffer, unsigned int bufferSize)
{
	return SetValue((HKEY)HKEY_LOCAL_MACHINE /*0x80000002*/, subKey, valueName, valueType, in_buffer, bufferSize);
}

// valueType must be 0 (REGISTRY_STRING) or 1 (REGISTRY_NUMBER).
// <CLGen.exe @004016c0>
BOOL __cdecl lego::registry::SetValue(HKEY hKey, LPCSTR subKey, LPCSTR valueName, RegistryType valueType, const void* in_buffer, unsigned int bufferSize)
{
	char rootSubKey[100];

	const char* splitSubKey = SplitRootKey(subKey, rootSubKey);
	if (*rootSubKey != '\0') {
		// rootSubKey isn't empty, we have more keys to recurse through
		HKEY hSubKey;
		RegCreateKeyA(hKey, rootSubKey, &hSubKey);
		if (hSubKey == nullptr)
			return FALSE;

		// recursively open/create subkeys to get to where we need
		BOOL recurseResult = SetValue(hSubKey, splitSubKey, valueName, valueType, in_buffer, bufferSize);
		RegCloseKey(hSubKey);
		return recurseResult;
	}

	switch (valueType) {
	case REGISTRY_STRING /*0*/:
		RegSetValueExA(hKey, valueName, 0, REG_SZ /*1*/, (const BYTE*)in_buffer, bufferSize);
		return TRUE;
	case REGISTRY_NUMBER /*1*/:
		RegSetValueExA(hKey, valueName, 0, REG_DWORD /*4*/, (const BYTE*)in_buffer, bufferSize);
		return TRUE;
	default:
		return FALSE;
	}
}
