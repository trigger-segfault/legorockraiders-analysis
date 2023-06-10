
#include <string.h>
#include <ctype.h>
#include <d3drmwin.h>

#include "Standard.h"

#include "Errors.h"
#include "Language.h"
#include "Mem.h"
#include "Maths.h"
#include "Utils.h"
#include "Files.h"
#include "Lists.h"
#include "Main.h"
#include "Fonts.h"
#include "Config.h"

struct Config_Globs {

	lpList list;
	lpList setList;

	ULONG flags;

#ifndef _RELEASE
	struct Config *debugLastFind;
#endif // !_RELEASE

} configGlobs = { 0 };

#ifdef _DEBUG
BOOL Config_ShutdownCallback(lpConfig config, LPVOID data) {

	Error_Warn(TRUE, "Unremoved Config item");

	return FALSE;
}

BOOL Config_ShutdownCallback2(lpConfigSet set, LPVOID data) {

	Error_Warn(TRUE, "Unremoved ConfigSet");

	return FALSE;
}
#endif // _DEBUG

VOID Config_Shutdown(VOID) {

#ifdef _DEBUG
	List_RunThrough(configGlobs.setList, Config_ShutdownCallback2, NULL);
#endif // _DEBUG
	List_Remove(configGlobs.setList);
	configGlobs.setList = NULL;
#ifdef _DEBUG
	List_RunThrough(configGlobs.list, Config_ShutdownCallback, NULL);
#endif // _DEBUG
	List_Remove(configGlobs.list);
	configGlobs.list = NULL;
}

VOID Config_Initialise(VOID) {

	configGlobs.list = List_Create(sizeof(struct Config));
	configGlobs.setList = List_Create(sizeof(struct ConfigSet));
}

BOOL Config_FindSetCallback(lpConfigSet set, lpConfig config) {

	lpConfig rootConfig;

	for (rootConfig=config ; rootConfig->linkPrev ; rootConfig=rootConfig->linkPrev) ;

	if (set->rootConfig == rootConfig) {
		return TRUE;
	}

	return FALSE;
}

lpConfigSet Config_FindSet(lpConfig config) {

	return List_RunThrough(configGlobs.setList, Config_FindSetCallback, config);
}

VOID Config_RegisterSet(lpConfig config, LPUCHAR fileData) {

	lpConfigSet set = List_ObtainItem(configGlobs.setList);
	set->rootConfig = config;
	set->fileData = fileData;
}

#ifdef _DEBUG
VOID Config_Debug_CheckFileData(lpConfig conf) {

	lpConfigSet set = Config_FindSet(conf);
	UCHAR changeList[1024] = "", change[1024];
	ULONG loop;

	if (0 != memcmp(set->fileData, set->fileDataCopy, set->fileDataCopySize)) {

		for (loop=0 ; loop<set->fileDataCopySize ; ) {
			if (set->fileData[loop] != set->fileDataCopy[loop]) {

				sprintf(change, "\n[%s] -> [%s]", &set->fileDataCopy[loop], &set->fileData[loop]);
				if (strlen(changeList) + strlen(change) > sizeof(changeList)) break;
				strcat(changeList, change);

				loop += strlen(&set->fileDataCopy[loop]);

			} else loop++;
		}
		
		Error_Fatal(TRUE, Error_Format("Config file data has been altered:%s", changeList));
	}
}
#endif // _DEBUG

VOID Config_FreeSet(lpConfig config) {

	lpConfigSet set = Config_FindSet(config);
	Mem_Free(set->fileData);
#ifdef _DEBUG
	Mem_Free(set->fileDataCopy);
#endif // _DEBUG
	List_ReturnItem(configGlobs.setList, set);
}

LPUCHAR Config_GetFileData(lpConfig config) {

	lpConfigSet set;
	
	if (set = Config_FindSet(config)) {
		return set->fileData;
	}

	return NULL;
}

#define _ISSPACE(c) (('\t' == (c)) || ('\n' == (c)) || ('\r' == (c)) || (' ' == (c)))

lpConfig Config_Load(LPUCHAR filename){

	lpConfig conf, rootConf = NULL;
	ULONG fileSize, loop;
	LPUCHAR s, fdata;
	BOOL commentMode = FALSE;
	BOOL quoteMode = FALSE;

	configGlobs.flags |= CONFIG_FLAG_LOADINGCONFIG;

	if (fdata = File_LoadBinary(filename, &fileSize)) {

		conf = rootConf = Config_Create(NULL);
		Config_RegisterSet(conf, fdata);

		// Change any return/tab/blah/blah characters to zero...
		// Clear anything after a semi-colon until the next return character.

		for (loop=0 ; loop<fileSize ; loop++){

			s = &fdata[loop];

			if (';' == *s) commentMode = TRUE;
			else if ('\n' == *s) commentMode = FALSE;
			else if ('\"' == *s && !commentMode) quoteMode = !quoteMode;

			if ('\"' == *s || (!quoteMode && (commentMode || _ISSPACE(*s)))) *s = '\0';

			s++;
		}

#ifdef _DEBUG
		{
			lpConfigSet set = Config_FindSet(conf);
			set->fileDataCopy = Mem_Duplicate(fdata);
			set->fileDataCopySize = Mem_Size(fdata);
		}
#endif // _DEBUG

		// Run through the file data and point in the config structures

		for (loop=0 ; loop<fileSize ; loop++) {

			s = &fdata[loop];

			if ('\0' != *s) {
				if ('}' == *s && '\0' == *(s+1)) {
					conf->depth--;
				} else if (NULL == conf->itemName) {
					Error_Fatal(*s == '{', "Config");
					conf->itemName = s;
				} else {
					conf->dataString = s;
					conf = Config_Create(conf);
					if ('{' == *s && '\0' == *(s+1)) conf->depth++;
				}

				for ( ; loop<fileSize ; loop++) {
					if ('\0' == *(s++)) {
						break;
					}
				}
			} else {
				s++;
			}
		}
	}

	configGlobs.flags &= ~CONFIG_FLAG_LOADINGCONFIG;

	return rootConf;
}

LPUCHAR Config_GetScope(lpConfig config) {

	lpConfigSet set;

	if (set = Config_FindSet(config)) {
		if ('\0' != set->currScope[0]) return set->currScope;
	}

	return NULL;
}

VOID Config_SetScope(lpConfig config, LPUCHAR scope) {

	lpConfigSet set;

	if (set = Config_FindSet(config)) {
		if (scope) sprintf(set->currScope, "%s", scope);
		else set->currScope[0] = '\0';
	}
}

LPUCHAR Config_GetRootScope(lpConfig config) {

	lpConfigSet set;

	if (set = Config_FindSet(config)) {
		if ('\0' != set->rootScope[0]) return set->rootScope;
	}

	return NULL;
}

VOID Config_SetRootScope(lpConfig config, LPUCHAR scope) {

	lpConfigSet set;

	if (set = Config_FindSet(config)) {
		if (scope) sprintf(set->rootScope, "%s", scope);
		else set->rootScope[0] = '\0';
	}
}

LPUCHAR Config_BuildStringID(LPUCHAR s, ...){
	
	va_list args;
	static UCHAR string[CONFIG_MAXSTRINGIDLENGTH];
	LPUCHAR curr;

	strcpy(string, s);

	va_start(args, s);
	while (curr = va_arg(args, LPUCHAR)){
		strcat(string, CONFIG_SEPARATOR);
		strcat(string, curr);
	}
	va_end(s);

	return string;
}

__inline LPUCHAR Config_GetItemName(lpConfig conf) {

	return conf->itemName;
}

__inline LPUCHAR Config_GetDataString(lpConfig conf) {

	return conf->dataString;
}

__inline LPUCHAR Config_GetDataStringCopy(lpConfig conf) {

	return Mem_CopyString(conf->dataString);
}

lpConfig Config_FindArray(lpConfig root, LPUCHAR name){

	lpConfig conf;

	if (conf = Config_FindItem(root, name)){
		if (conf->depth < conf->linkNext->depth) return conf->linkNext;
	}
	return NULL;
}

lpConfig Config_GetNextItem(lpConfig start){

	ULONG level = start->depth;
	lpConfig conf = start;

	while(conf){
		if (conf->depth < level) return NULL;
		conf = conf->linkNext;
		if (conf) {
			if (conf->depth == level) return conf;
		}
	}
	return NULL;
}

#ifdef _DEBUG

LPUCHAR Config_GetStringCopyDebug(lpConfig root, LPUCHAR stringID, ULONG line, LPUCHAR file){

	lpConfig conf;
	LPUCHAR str;

	if (conf = Config_FindItem(root, stringID)){
		if (conf->dataString){
			str = Mem_Debug_Alloc(strlen(conf->dataString) + 1, file, line);
			strcpy(str, conf->dataString);
			return str;
		}
	}
	
	return NULL;
}

#else 

LPUCHAR Config_GetStringCopy(lpConfig root, LPUCHAR stringID){

	lpConfig conf;
	LPUCHAR str;

	if (conf = Config_FindItem(root, stringID)){
		if (conf->dataString){
			str = Mem_Alloc(strlen(conf->dataString) + 1);
			strcpy(str, conf->dataString);
			return str;
		}
	}
	
	return NULL;
}

VOID Config_SetStringValue(lpConfig root, LPUCHAR stringID, LPUCHAR string){

	lpConfig conf;

	if (conf = Config_FindItem(root, stringID)){
		if (conf->dataString){
			Mem_Free(conf->dataString);
		}
		conf->dataString=Mem_Alloc(strlen(string) + 1);
		sprintf(conf->dataString, "%s", string);
	}
}

#endif //_DEBUG

LPUCHAR Config_GetString(lpConfig root, LPUCHAR stringID){

	lpConfig conf;

	if (conf = Config_FindItem(root, stringID)){
		return conf->dataString;
	}
	
	return NULL;
}

LPUCHAR Config_GetLanguageString(lpConfig root, LPUCHAR stringID) {

	LPUCHAR string;

	if (string = Config_GetString(root, stringID)) return Language_GetString(Language_FindEnum(string));
	else return NULL;
}

ULONG Config_GetBoolValue(lpConfig root, LPUCHAR stringID){

	LPUCHAR string;
	ULONG res = 2;

	if (string = Config_GetStringCopy(root, stringID)){
	
		res = Util_GetBoolFromString(string);
		Mem_Free(string);
	}

	return res;
}

REAL Config_GetAngle(lpConfig root, LPUCHAR stringID){

	REAL degrees;

	if (degrees = Config_GetRealValue(root, stringID)){
		return (degrees / 360.0f) * (2.0f * M_PI);
	}

	return 0.0f;
}

BOOL Config_GetRGBValue(lpConfig root, LPUCHAR stringID, LPREAL r, LPREAL g, LPREAL b){

	LPUCHAR argv[100], string;
	BOOL res = FALSE;

	if (string = Config_GetStringCopy(root, stringID)){

		if (3 == Util_Tokenise(string, argv, 999, ":", TRUE)){
		
			*r = atoi(argv[0]) / 255.0f;
			*g = atoi(argv[1]) / 255.0f;
			*b = atoi(argv[2]) / 255.0f;

			res = TRUE;

		} else Error_Warn(TRUE, Error_Format("Invalid RBG entry '%s'", Config_GetString(root, stringID)));

		Mem_Free(string);
	}

	return res;
}

BOOL Config_GetCoord(lpConfig root, LPUCHAR stringID, LPREAL x, LPREAL y, LPREAL z){

	LPUCHAR argv[100], string;
	BOOL res = FALSE;

	Error_Fatal(!x||!y, "Null passed as x or y");

	if (string = Config_GetStringCopy(root, stringID)){

		if (NULL == z) {
			if (2 != Util_Tokenise(string, argv, 999, ",", TRUE)) Error_Warn(TRUE, Error_Format("Invalid 2D Coordinate entry '%s'", string));
		} else if (3 == Util_Tokenise(string, argv, 999, ",", TRUE)) *z = (REAL) atof(argv[2]);
		else {
			Error_Warn(TRUE, Error_Format("Invalid 3D Coordinate entry '%s'", string));
			res = FALSE;
		}
		
		*x = (REAL) atof(argv[0]);
		*y = (REAL) atof(argv[1]);

		Mem_Free(string);
		res = TRUE;
	}

	return res;
}

VOID Config_Free(lpConfig root){

	lpConfig next;

	Error_Fatal(NULL == root, "NULL passed to Config_Free()");
	Error_Fatal(NULL == Config_GetFileData(root), "Only pass the root (loaded) config structure to Config_Free()");

	Config_FreeSet(root);

	while (root) {
		next = root->linkNext;
		Config_Remove(root);
		root = next;
	}
}

#ifndef _RELEASE
LPUCHAR Config_Debug_GetLastFind(VOID) {

	static UCHAR msg[1024];

	if (configGlobs.debugLastFind) {
		sprintf(msg, "%s %s", configGlobs.debugLastFind->itemName, configGlobs.debugLastFind->dataString);
		return msg;
	}

	return NULL;
}
#endif // !_RELEASE

/*********************************************************************************
 ****** Static Library Functions
 ********************************************************************************/

static lpConfig Config_Create(lpConfig prev) {

	lpConfig newConfig;

	Config_CheckInit();

	newConfig = List_ObtainItem(configGlobs.list);
	newConfig->linkPrev = prev;

	if (prev) {
		prev->linkNext = newConfig;
		newConfig->depth = prev->depth;
	}

	return newConfig;
}

static VOID Config_Remove(lpConfig dead) {

	Config_CheckInit();

	Error_Fatal(!dead, "NULL passed to Config_Remove()");

	List_ReturnItem(configGlobs.list, dead);
}

lpConfig Config_FindItem(lpConfig conf, char *stringID){

	// Search the list for the given item.
	
	LPUCHAR argv[CONFIG_MAXDEPTH];
	ULONG count, currDepth;
	lpConfig backConf, foundConf = NULL;
	UCHAR tempstring[CONFIG_MAXSTRINGIDLENGTH];
	BOOL wildcard;
	lpConfigSet set = Config_FindSet(conf);

	Error_Fatal(NULL == set, "Cannot find config set");
	Config_CheckItem(conf);

	if (set->rootScope[0] && set->currScope[0]) sprintf(tempstring, "%s::%s::%s", set->rootScope, set->currScope, stringID);
	else if (set->currScope[0]) sprintf(tempstring, "%s::%s", set->currScope, stringID);
	else if (set->rootScope[0]) sprintf(tempstring, "%s::%s", set->rootScope, stringID);
	else sprintf(tempstring, "%s", stringID);

	count = Util_Tokenise(tempstring, argv, CONFIG_MAXDEPTH, "::", TRUE);

	// First find anything that matches the depth of the request
	// then see if the hierarchy matches the request.

	while(conf) {

		if (conf->depth == count - 1){

			wildcard = FALSE;

			if (1 == count) {
				LPUCHAR s;
				ULONG index = 0;
				for (s=conf->itemName ; '\0'!=*s ; s++) { if ('*' == *s) break; index++; }
				if ('*' == *s) {
					wildcard = !strnicmp(argv[count - 1], conf->itemName, index);
				}
			}

			if (wildcard || 0 == stricmp(argv[count - 1], conf->itemName)){

				wildcard = FALSE;

				// Look backwards down the list to check the hierarchy.
				currDepth = count - 1;
				backConf = conf;
				while(backConf){
					if (backConf->depth == currDepth - 1){
						if (1 == currDepth) {
							LPUCHAR s;
							ULONG index = 0;
							for (s=backConf->itemName ; '\0'!=*s ; s++) { if ('*' == *s) break; index++; }
							if ('*' == *s) {
								wildcard = !strnicmp(argv[currDepth - 1], backConf->itemName, index);
							}
						}

						if (wildcard || 0 == stricmp(argv[currDepth - 1], backConf->itemName)){
							currDepth--;
						} else break;
					}
					backConf = backConf->linkPrev;
				}
				if (0 == currDepth) {
					foundConf = conf;
					if (!wildcard) break;
				}
			}
		}
		conf = conf->linkNext;
	}

#ifdef _DEBUG
	if (foundConf) {
		configGlobs.debugLastFind = foundConf;
		foundConf->accessed = TRUE;
	} else {
		foundConf = NULL;
	}
#endif // _DEBUG

	return foundConf;
}
