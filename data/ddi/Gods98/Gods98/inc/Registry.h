
#include "..\Inc\Standard.h"

///////////////////////////////////////////////////////////
// Simple registry API

// Supported registry information types
enum {
	REGISTRY_STRING_VALUE,
	REGISTRY_DWORD_VALUE
};

BOOL Registry_SetValue(LPUCHAR path, 
					   LPUCHAR key, 
					   ULONG dataType,
					   LPVOID data, 
					   ULONG dataSize);
BOOL Registry_GetValue(LPUCHAR path, 
					   LPUCHAR key, 
					   ULONG dataType, 
					   LPVOID data, 
					   ULONG dataSize);

