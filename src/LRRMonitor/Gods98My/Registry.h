#pragma once

#include "../framework.h"


namespace Gods98
{; // !<---

///////////////////////////////////////////////////////////
// Simple registry API

/**********************************************************************************
 ******** Enumerations
 **********************************************************************************/

#pragma region Enums

// Supported registry information types
enum
{
	REGISTRY_STRING_VALUE,
	REGISTRY_DWORD_VALUE
};

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @0048b5f0>
// <CLGen.exe @00401660>
const char* __cdecl Registry_GetKeyFromPath(const char* path, OUT char* str);


// <CLGen.exe @00401690>
BOOL __cdecl Registry_SetValue(const char* path,
					   const char* key, 
					   unsigned long dataType,
					   const void* data, 
					   unsigned long dataSize);


// <LegoRR.exe @0048b620>
BOOL __cdecl Registry_GetValue(const char* path,
					   const char* key, 
					   unsigned long dataType, 
					   OUT void* data, 
					   unsigned long dataSize);

// <CLGen.exe @004016c0>
BOOL __cdecl Registry_SetValue_Recursive(HKEY parent,
										const char* path, 
										const char* key, 
										unsigned long dataType,
										const void* data, 
										unsigned long dataSize);

// <LegoRR.exe @0048b650>
BOOL __cdecl Registry_GetValue_Recursive(HKEY parent,
										const char* path,
										const char* key,
										unsigned long dataType,
										OUT void* data,
										unsigned long dataSize);

#pragma endregion

}
