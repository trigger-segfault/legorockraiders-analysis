#include <windows.h>
#include "..\inc\registry.h"

LPUCHAR Registry_GetKeyFromPath(LPUCHAR path, LPUCHAR str)
{

	*str = 0;
	while (*path && *path != '\\')
	{
		*str = *path;
		path++;
		str++;
	}

	if (*path == '\\') path++;
	*str = 0;

	return path;
}


static BOOL Registry_SetValue_Recursive(HKEY parent, 
										LPUCHAR path, 
										LPUCHAR key, 
										ULONG dataType,
										LPVOID data, 
										ULONG dataSize)
{
	HKEY localKey;
	char str[100];
	LPUCHAR newPath;

	newPath = Registry_GetKeyFromPath(path, str);

	if (!str[0])
	{
		// Set the value
		switch (dataType)
		{
		case REGISTRY_STRING_VALUE:
			RegSetValueEx(parent, key, 0, REG_SZ, (LPUCHAR) data, dataSize);
			return TRUE;
		case REGISTRY_DWORD_VALUE:
			RegSetValueEx(parent, key, 0, REG_DWORD, (LPUCHAR) data, dataSize);
			return TRUE;
		default:
			return FALSE;
		}
	}
	else
	{
		BOOL retVal; 

		// Open the key and recurse
		RegCreateKey(parent, str, &localKey);

		if (!localKey) return FALSE;

		retVal = Registry_SetValue_Recursive(localKey, newPath, key, dataType, data, dataSize);
		
		RegCloseKey(localKey);

		return retVal;
	}
}

BOOL Registry_SetValue(LPUCHAR path, 
					   LPUCHAR key, 
					   ULONG dataType,
					   LPVOID data, 
					   ULONG dataSize)
{
	return Registry_SetValue_Recursive(HKEY_LOCAL_MACHINE, path, key, dataType, data, dataSize);
}

static BOOL Registry_GetValue_Recursive(HKEY parent, LPUCHAR path, LPUCHAR key, ULONG dataType, LPVOID data, ULONG dataSize)
{
	HKEY localKey;
	char str[100];
	LPUCHAR newPath;

	newPath = Registry_GetKeyFromPath(path, str);

	if (!str[0])
	{
		ULONG _dataSize = dataSize;
		ULONG _dataType = 0;

		// Set the value
		switch (dataType)
		{
		case REGISTRY_STRING_VALUE:
			return RegQueryValueEx(parent, key, 0, &_dataType, (LPUCHAR) data, &_dataSize) == ERROR_SUCCESS;
		case REGISTRY_DWORD_VALUE:
			return RegQueryValueEx(parent, key, 0, &_dataType, (LPUCHAR) data, &_dataSize) == ERROR_SUCCESS;
		default:
			return FALSE;
		}
	}
	else
	{
		BOOL retVal; 

		// Open the key and recurse
		RegCreateKey(parent, str, &localKey);

		if (!localKey) return FALSE;

		retVal = Registry_GetValue_Recursive(localKey, newPath, key, dataType, data, dataSize);
		
		RegCloseKey(localKey);

		return retVal;
	}
}

BOOL Registry_GetValue(LPUCHAR path, LPUCHAR key, ULONG dataType, LPVOID data, ULONG dataSize)
{
	return Registry_GetValue_Recursive(HKEY_LOCAL_MACHINE, path, key, dataType, data, dataSize);
}