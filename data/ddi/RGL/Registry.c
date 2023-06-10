
#include <windows.h>

#include "Standard.h"
#include "Errors.h"
#include "Registry.h"

struct RegistryGlobs {

	UCHAR companyName[REGISTRY_MAXNAMELENGTH + 1];
	UCHAR productName[REGISTRY_MAXNAMELENGTH + 1];

} registryGlobs;

VOID Registry_SetNames(LPUCHAR companyName, LPUCHAR productName) {

	Error_Overflow(strlen(companyName), REGISTRY_MAXNAMELENGTH);
	Error_Overflow(strlen(companyName), REGISTRY_MAXNAMELENGTH);

	sprintf(registryGlobs.companyName, "%s", companyName);
	sprintf(registryGlobs.productName, "%s", productName);
}

static BOOL Registry_OpenProductNameKey(PHKEY pnKey) {

	HKEY swKey, cnKey;
	BOOL result = FALSE;

	if ('\0' != registryGlobs.companyName[0] && '\0' != registryGlobs.productName[0]) {
		if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE", 0, KEY_CREATE_SUB_KEY, &swKey)) {
			if (ERROR_SUCCESS == RegCreateKeyEx(swKey, registryGlobs.companyName, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_CREATE_SUB_KEY, NULL, &cnKey, NULL)) {
				if (ERROR_SUCCESS == RegCreateKeyEx(cnKey, registryGlobs.productName, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, pnKey, NULL)) {

					result = TRUE;

				} else Error_Fatal(TRUE, "Could not open product registry key");

				RegCloseKey(cnKey);

			} else Error_Fatal(TRUE, "Could not open company registry key");

			RegCloseKey(swKey);

		} else Error_Fatal(TRUE, "Cannot open HKEY_LOCAL_MACHINE\\SOFTWARE");

	} else Error_Fatal(TRUE, "Company/product names have not been setup correctly");

	return result;
}

BOOL Registry_WriteKey(LPUCHAR keyName, enum RegistryKey_Type type, const LPUCHAR data, ULONG size) {

	HKEY pnKey;
	BOOL result = FALSE;

	if (Registry_OpenProductNameKey(&pnKey)) {

		if (ERROR_SUCCESS == RegSetValueEx(pnKey, keyName, 0, type, data, size)) {

			result = TRUE;

		} else Error_Fatal(TRUE, "Could not write registry key");

		RegCloseKey(pnKey);
	}

	return result;
}

BOOL Registry_ReadKey(LPUCHAR keyName, enum RegistryKey_Type *type, LPUCHAR data, LPULONG size) {

	HKEY pnKey;
	BOOL result = FALSE;

	if (Registry_OpenProductNameKey(&pnKey)) {

		if (ERROR_SUCCESS == RegQueryValueEx(pnKey, keyName, 0, type, data, size)) {

			result = TRUE;

		} else Error_Fatal(TRUE, "Could not write registry key");

		RegCloseKey(pnKey);
	}

	return result;
}
