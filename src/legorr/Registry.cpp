#include "Registry.h"
#include <windows.h>

// [internal]
// <LegoRR.exe @0048b5f0>
static const char* __cdecl Reg_SplitRootKey(const char* fullKey, char* out_rootKey)
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

// [visible]
// <LegoRR.exe @0048b620>
BOOL __cdecl Reg_QueryString_FromLocalMachine(const char* subKey, const char* valueName, RegistryValueType valueType, char* out_buffer, unsigned int bufferSize)
{
	return Reg_QueryString((HKEY)HKEY_LOCAL_MACHINE /*0x80000002*/, subKey, valueName, valueType, out_buffer, bufferSize);
}

// [internal]
// valueType must be 0 (REG_NONE) or 1 (REG_SZ)... but otherwise, both values do the same thing
// <LegoRR.exe @0048b650>
BOOL __cdecl Reg_QueryString(HKEY hKey, const char* subKey, const char* valueName, RegistryValueType valueType, char* out_buffer, unsigned int bufferSize)
{
	char rootSubKey[100];

	const char* splitSubKey = Reg_SplitRootKey(subKey, rootSubKey);
	if (*rootSubKey != '\0') {
		// rootSubKey isn't empty, we have more keys to recurse through
		HKEY hSubKey;
		RegCreateKeyA(hKey, rootSubKey, &hSubKey);
		if (hSubKey == nullptr)
			return FALSE;

		// recursively open subkeys to get to where we need
		BOOL recurseResult = Reg_QueryString(hSubKey, splitSubKey, valueName, valueType, out_buffer, bufferSize);
		RegCloseKey(hSubKey);
		return recurseResult;
	}

	DWORD outValueType = REG_NONE /*0*/;
	if (valueType == REGVALUE_SZ /*1*/) {
		LSTATUS result = RegQueryValueExA(hKey, valueName, nullptr, &outValueType, (LPBYTE)out_buffer, (LPDWORD)&bufferSize);
		return (result == ERROR_SUCCESS /*0*/);
	}
	else if (valueType == REGVALUE_NONE /*0*/) {
		LSTATUS result = RegQueryValueExA(hKey, valueName, nullptr, &outValueType, (LPBYTE)out_buffer, (LPDWORD)&bufferSize);
		return (result == ERROR_SUCCESS /*0*/);
	}
	return FALSE;
}


