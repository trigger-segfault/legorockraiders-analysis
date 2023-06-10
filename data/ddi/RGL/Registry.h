
#ifndef _RGL_REGISTRY_H
#define _RGL_REGISTRY_H

#define REGISTRY_MAXNAMELENGTH			127
#define REGISTRY_MAXVALUELENGTH			((3 * REGISTRY_MAXNAMELENGTH) + 16)

enum RegistryKey_Type {
	
	RegistryKey_None = 0,						// REG_NONE
	RegistryKey_String = 1,						// REG_SZ
	RegistryKey_ExpandString = 2,				// REG_EXPAND_SZ
	RegistryKey_BOOL = 3,						// REG_BINARY
	RegistryKey_ULONG = 4,						// REG_DWORD
	RegistryKey_leULONG = 4,					// REG_DWORD_LITTLE_ENDIAN
	RegistryKey_beULONG = 5,					// REG_DWORD_BIG_ENDIAN
	RegistryKey_Link = 6,						// REG_LINK
	RegistryKey_MultiString = 7,				// REG_MULTI_SZ
	RegistryKey_ResourceList = 8,				// REG_RESOURCE_LIST
	RegistryKey_ResourceDescriptor = 9,			// REG_FULL_RESOURCE_DESCRIPTOR
	RegistryKey_ResourceRequirementsList = 10,	// REG_RESOURCE_REQUIREMENTS_LIST

};

extern VOID __cdecl Registry_SetNames(LPUCHAR companyName, LPUCHAR productName);
extern BOOL __cdecl Registry_WriteKey(LPUCHAR keyName, enum RegistryKey_Type type, const LPUCHAR data, ULONG size);
extern BOOL __cdecl Registry_ReadKey(LPUCHAR keyName, enum RegistryKey_Type *type, LPUCHAR data, LPULONG size);

#endif // _RGL_REGISTRY_H

