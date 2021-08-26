
#include <string.h>
#include <ctype.h>
#include <d3drmwin.h>

#include "..\inc\Standard.h"

#include "..\inc\Errors.h"
#include "..\inc\Memory.h"
#include "..\inc\Maths.h"
#include "..\inc\Utils.h"
#include "..\inc\Files.h"
#include "..\inc\Config.h"
#include "..\inc\Keys.h"
#include "..\inc\Main.h"
#include "..\inc\Fonts.h"

Config_Globs configGlobs = { NULL };

/*
VOID Config_Initialise(VOID){
	
	ULONG loop;
	Config *conf;

	for (loop=0 ; loop<CONFIG_MAXCONFIG ; loop++){
		conf = &(confGlobs.configArray[loop]);
		conf->fileData = NULL;
		conf->flags = 0x00000000;
	}
}
*/

VOID Config_Initialise(VOID){
	
	ULONG loop;

	for (loop=0 ; loop<CONFIG_MAXLISTS ; loop++){
		configGlobs.listSet[loop] = NULL;
	}

	configGlobs.freeList = NULL;
	configGlobs.listCount = 0;
	configGlobs.flags = CONFIG_FLAG_INITIALISED;

#ifdef CONFIG_DEVELOPMENTMODE
	if (configGlobs.ctFile) Config_ReadCharacterTable(configGlobs.ctFile);

	// Fill in the unspecified characters with their normal value
	for (loop=1 ; loop<256 ; loop++) if (0 == configGlobs.characterTable[loop]) configGlobs.characterTable[loop] = (UCHAR) loop;

	if (configGlobs.cconvFile) {		// Convert the characters in this file, then exit.

		UCHAR msg[1024];

		if (NULL == configGlobs.ctFile) sprintf(msg, "No character file was specified\nUse -CharTable <language>.cct");
		else {
			lpFile ccfp;
			UCHAR fname[FILE_MAXPATH];
			LPUCHAR buffer;
			ULONG loop, size;

			if (buffer = File_LoadBinary(configGlobs.cconvFile, &size)) {
				sprintf(fname, "%s.cconv", configGlobs.cconvFile);
				if (ccfp = File_Open(fname, "wb")) {
					for (loop=0 ; loop<size ; loop++) buffer[loop] = Config_ConvertCharacter(buffer[loop]);
					File_Write(buffer, 1, size, ccfp);
					File_Close(ccfp);
					sprintf(msg, "Characters converted \"%s\" -> \"%s\" using \"%s\"", configGlobs.cconvFile, fname, configGlobs.ctFile);
				} else sprintf(msg, "Cannot open file \"%s\" for writing", fname);
			} else sprintf(msg, "Cannot open file \"%s\" for reading", configGlobs.cconvFile);
		}

		MessageBox(NULL, msg, "Language Conversion", MB_OK);
		exit(0);
	}

	if (configGlobs.langFile) {
		if (NULL == configGlobs.ctFile) MessageBox(NULL, "WARNING: No character conversion file has been specified.\nCharacters within converted text may not be displayed or stored in output files.\n\nUse -CharTable <language>.cct", "Language Conversion", MB_OK);
		Config_ReadLanguageDatabase(configGlobs.langFile);
		Mem_Free(configGlobs.langFile);
	}
	if (configGlobs.ctFile) Mem_Free(configGlobs.ctFile);

#endif // CONFIG_DEVELOPMENTMODE

}

VOID Config_Shutdown(VOID){

	ULONG loop;

#ifdef _DEBUG
	{
		ULONG list, count, loop;
		lpConfig tempConfig;

		for (list=0 ; list<configGlobs.listCount ; list++){
			if (configGlobs.listSet[list]){
				count = 0x00000001 << list;
				for (loop=0 ; loop<count ; loop++){
					if (tempConfig = &configGlobs.listSet[list][loop]){
						if (tempConfig->nextFree == tempConfig){
							if (FALSE == tempConfig->accessed) {
								tempConfig->accessed = FALSE;
							}
						}
					}
				}
			}
		}
	}
#endif // _DEBUG

	for (loop=0 ; loop<CONFIG_MAXLISTS ; loop++){
		if (configGlobs.listSet[loop]) Mem_Free(configGlobs.listSet[loop]);
	}

	configGlobs.freeList = NULL;
	configGlobs.flags = 0x00000000;
}

#ifdef CONFIG_DEVELOPMENTMODE

#pragma message ( "  ******* CONFIG_DEVELOPMENTMODE defined - Text language conversion will occur *******" )

VOID Config_SetCharacterTable(LPUCHAR fname) {

	configGlobs.ctFile = Util_StrCpy(fname);
}

VOID Config_SetCharacterConvertFile(LPUCHAR fname) {

	configGlobs.cconvFile = Util_StrCpy(fname);
}

static VOID Config_ReadCharacterTable(LPUCHAR fname) {

	lpFile ctfp;
	UCHAR line[128];
	LPUCHAR argv[10];
	ULONG argc, lineNum = 0;

	if (ctfp = File_Open(fname, "r")) {
		while (File_GetLine(line, sizeof(line), ctfp)) {
			lineNum++;
			argc = Util_Tokenise(line, argv, "[");
			Error_Fatal((2!=argc)||(1!=strlen(argv[0]))||(']'!=argv[1][strlen(argv[1])-1]), Error_Format("Invalid character conversion table: line %i", lineNum));
			Error_Fatal(0!=configGlobs.characterTable[argv[0][0]], Error_Format("Character number %i (%c) specified twice: line %i", argv[0][0], argv[0][0], lineNum));
			configGlobs.characterTable[argv[0][0]] = atoi(argv[1]);
		}
		File_Close(ctfp);
	} else {
		UCHAR msg[1024];
		sprintf(msg, "Cannot open file \"%s\" for reading", fname);
		MessageBox(NULL, msg, "Language Conversion", MB_OK);
		exit(0);
	}
}

UCHAR Config_ConvertCharacter(UCHAR c) {

	return configGlobs.characterTable[c];
}

VOID Config_SetLanguageDatabase(LPUCHAR langFile) {

	configGlobs.langFile = Util_StrCpy(langFile);
}

static VOID Config_ReadLanguageDatabase(LPUCHAR langFile) {

	ULONG size, loop, argc, lineNum = 0, index = 0;
	LPUCHAR lastLine, s;
	LPUCHAR argv[10];

	Error_Fatal(0!=configGlobs.languageLines, "Config_ReadLanguageDatabase() called twice");

	if (configGlobs.languageBuffer = File_LoadASCII(langFile, &size)) {

		for (loop=0 ; loop<size ; loop++) if ('\n' == configGlobs.languageBuffer[loop]) configGlobs.languageLines++;
		configGlobs.languageData = Mem_Alloc(sizeof(Config_LanguageData) * configGlobs.languageLines);

		lastLine = configGlobs.languageBuffer;
		for (loop=0 ; loop<size ; loop++) {
			if ('\n' == configGlobs.languageBuffer[loop]) {
				configGlobs.languageBuffer[loop] = '\0';
				argc = Util_Tokenise(lastLine, argv, "\t");
//				if ('\r' == argv[3][strlen(argv[3])-1]) argv[3][strlen(argv[3])-1] = '\0';
				lineNum++;
				Error_Fatal(4!=argc, Error_Format("Language file (line %i)", lineNum));

				// Remap the characters specified in the translation file to their equivilent in the font page.
				for (s=argv[3] ; '\0'!=*s ; s++) {
					if (0x91 == *s || 0x92 == *s || 0xb4 == *s) *s = '\'';
					else if (0x96 == *s) *s = '-';
					else *s = Config_ConvertCharacter(*s);
				}

				// Special check to convert wacky apostrophies to the correct ones in the original string...
				for (s=argv[0] ; '\0'!=*s ; s++) if (0x91 == *s || 0x92 == *s || 0xb4 == *s) *s = '\'';

				if (strlen(argv[0]) > 1) {
					if (' ' == argv[0][strlen(argv[0])-1]) argv[0][strlen(argv[0])-1] = '\0';
				}

				configGlobs.languageData[index].original = argv[0];
				configGlobs.languageData[index].translation = argv[3];
				configGlobs.languageData[index].section = argv[2];

				lastLine = &configGlobs.languageBuffer[loop+1];
				index++;
			}
		}
		configGlobs.languageLines = index;
	}
}

LPUCHAR Config_ConvertString(LPUCHAR s, LPUCHAR sectionName, LPULONG size, BOOL spaceToUnderscore) {

	static UCHAR result[1024];
	UCHAR string[1024];
	lpConfig_LanguageData data;
	ULONG loop, type, mode;
	SLONG match;

	sprintf(string, "%s", s);
	if (strlen(string) > 1) {
		if (' ' == string[strlen(string)-1]) string[strlen(string)-1] = '\0';
	}

	for (mode=0 ; mode<2 ; mode++) {
		for (type=((NULL==sectionName)?1:0) ; type<2 ; type++) {
			for (loop=0 ; loop<configGlobs.languageLines ; loop++) {
				data = &configGlobs.languageData[loop];

				if (0 == mode) match = strcmp(string, data->original);
				else match = stricmp(string, data->original);

				if (0 == match) {
					if (1 == type || 0 == stricmp(sectionName, data->section)) {
						Error_Fatal(('\0' == data->translation[0]), Error_Format("Missing translation for \"%s\"", s));
						*size = sprintf(result, "%s", data->translation);
						goto skip;
					}
				}
			}
		}
	}

skip:			// Waaaaahhhhhhhhhh!!!!!

	if (loop == configGlobs.languageLines) {
		*size = sprintf(result, "%s", string);
		Error_Fatal(configGlobs.unknownPhraseCount==CONFIG_MAXUNKNOWNPHRASES, "CONFIG_MAXUNKNOWNPHRASES too small");
		configGlobs.unknownPhrases[configGlobs.unknownPhraseCount].original = Util_StrCpy(string);
		if (sectionName) configGlobs.unknownPhrases[configGlobs.unknownPhraseCount].section = Util_StrCpy(sectionName);
		else configGlobs.unknownPhrases[configGlobs.unknownPhraseCount].original = CONFIG_UNNAMEDSECTION;
		configGlobs.unknownPhraseCount++;
	}

	if (spaceToUnderscore) {
		for (loop=0 ; loop<*size ; loop++) {
			if (' ' == result[loop]) result[loop] = '_';
		}
	}

	if (configGlobs.flags & CONFIG_FLAG_LOADINGCONFIG) {
		// Replace any semi-colons in the translated string with one that won't be removed by the config loader...
		for (loop=0 ; loop<*size ; loop++) if (';' == result[loop]) result[loop] = FONT_LASTCHARACTER + 1;
	}

	return result;
}

int Config_UnknownPhraseSort(const void *elem1, const void *elem2) {

	ULONG indexA = *((LPULONG) elem1);
	ULONG indexB = *((LPULONG) elem2);
	lpConfig_LanguageData a = &configGlobs.unknownPhrases[indexA];
	lpConfig_LanguageData b = &configGlobs.unknownPhrases[indexB];
	SLONG result;

	result = strcmp(a->section, b->section);
	if (0 == result) result = strcmp(a->original, b->original);

	return result;
}

VOID Config_DumpUnknownPhrases(LPUCHAR fname) {

	lpFile file;
	ULONG loop, useIndex;

	if (configGlobs.unknownPhraseCount) {

		LPULONG indexList = Mem_Alloc(sizeof(ULONG) * configGlobs.unknownPhraseCount);
		
		for (loop=0 ; loop<configGlobs.unknownPhraseCount ; loop++) indexList[loop] = loop;
		qsort(indexList, configGlobs.unknownPhraseCount, sizeof(ULONG), Config_UnknownPhraseSort);

		if (file = File_Open(fname, "w")) {
			for (loop=0 ; loop<configGlobs.unknownPhraseCount ; loop++) {
				useIndex = indexList[loop];
				File_PrintF(file, "%s\t1024 Characters\t%s\tUntranslated\n", configGlobs.unknownPhrases[useIndex].original, configGlobs.unknownPhrases[useIndex].section);
/*				{
					UCHAR backward[1024];
					ULONG sub, length = strlen(configGlobs.unknownPhrases[loop].original);
					for (sub=0 ; sub<length ; sub++) {
						backward[sub] = configGlobs.unknownPhrases[loop].original[length - (sub + 1)];
					}
					backward[length] = '\0';
					File_PrintF(file, "%s\t1024 Characters\t%s\t%s\n", configGlobs.unknownPhrases[loop].original, configGlobs.unknownPhrases[loop].section, backward);
				}*/
			}
			configGlobs.unknownPhraseCount = 0;
			File_Close(file);
		}

		Mem_Free(indexList);
	}
}

LPVOID Config_LoadConvertedText(LPUCHAR fname, LPULONG fileSize) {

	LPUCHAR oData, cData;
	ULONG size, loop, newMax, newSize = 0;
	LPVOID rVal = NULL;
	BOOL bs = FALSE, section = FALSE;
	LPUCHAR keyStart = NULL;
	ULONG length;
	BOOL replaced = FALSE;
	UCHAR sectionName[128] = CONFIG_UNNAMEDSECTION;

	if (oData = File_LoadBinary(fname, &size)) {
		newMax = (size * CONFIG_CONVERTIONINCPC) / 100;
		if (cData = Mem_Alloc(newMax)) {
			for (loop=0 ; loop<size ; loop++) {
				Error_Fatal(newSize==newMax, "Converted file too large (CONFIG_CONVERTIONINCPC too small)");

				cData[newSize++] = oData[loop];

				if (bs && '[' == oData[loop]) {
					Error_Fatal(keyStart, "\\[ found after \\[");
					keyStart = &cData[newSize];
					if ('#' == oData[loop+1]) section = TRUE;
				} else if (bs && ']' == oData[loop]) {
					Error_Fatal(NULL == keyStart, "\\] found before \\]");
					cData[newSize-2] = '\0';
					newSize -= strlen(keyStart) + 4;
					if (section) {
						sprintf(sectionName, "%s", &keyStart[1]);
						section = FALSE;
					} else {
						sprintf(&cData[newSize], "%s", Config_ConvertString(keyStart, sectionName, &length, TRUE));
						newSize += length;
					}
					keyStart = NULL;
					replaced = TRUE;
				}
				
				if ('\\' == oData[loop]) bs = TRUE;
				else bs = FALSE;

			}
		
			Error_Fatal(keyStart, "End of file in text conversion block");

			cData = Mem_ReAlloc(cData, newSize);
			if (fileSize) *fileSize = newSize;
			rVal = cData;

			if (replaced && Main_GetLanguage()) {
				UCHAR dump[FILE_MAXPATH];
				lpFile lfp;
				sprintf(dump, "%s.%s", fname, Main_GetLanguage());
				if (lfp = File_Open(dump, "wb")) {
					File_Write(cData, 1, newSize, lfp);
					File_Close(lfp);
				}
			}

			if (Main_DumpUnknownPhrases()) {
				UCHAR dump[FILE_MAXPATH];
				sprintf(dump, "%s.untranslated", fname);
				Config_DumpUnknownPhrases(dump);
			}
		}
		Mem_Free(oData);
	}

	return rVal;
}

#endif // CONFIG_DEVELOPMENTMODE

#define _ISSPACE(c) (('\t' == (c)) || ('\n' == (c)) || ('\r' == (c)) || (' ' == (c)))

Config *Config_Load(LPUCHAR filename){

	Config *conf, *rootConf = NULL;
	ULONG fileSize, loop;
	LPUCHAR s, fdata;
	BOOL commentMode = FALSE;

	configGlobs.flags |= CONFIG_FLAG_LOADINGCONFIG;

#ifdef CONFIG_DEVELOPMENTMODE
	if (fdata = Config_LoadConvertedText(filename, &fileSize)){
#else // CONFIG_DEVELOPMENTMODE
	if (fdata = File_LoadBinary(filename, &fileSize)){
#endif // CONFIG_DEVELOPMENTMODE

		conf = rootConf = Config_Create(NULL);
		rootConf->fileData = fdata;

		// Change any return/tab/blah/blah characters to zero...
		// Clear anything after a semi-colon until the next return character.

		for (s=rootConf->fileData,loop=0 ; loop<fileSize ; loop++){

			if (';' == *s) commentMode = TRUE;
			else if ('\n' == *s) commentMode = FALSE;

			if (commentMode || _ISSPACE(*s)) *s = '\0';

			s++;
		}

		// Replace the semi-colons that were removed by the language converter...
		for (loop=0 ; loop<fileSize ; loop++) if (FONT_LASTCHARACTER + 1 == rootConf->fileData[loop]) rootConf->fileData[loop] = ';';

		// Run through the file data and point in the config structures

		for (s=rootConf->fileData,loop=0 ; loop<fileSize ; loop++){
			if ('\0' != *s){
				if ('}' == *s && '\0' == *(s+1)) conf->depth--;
				else if (NULL == conf->itemName) 
				{
					Error_Fatal(*s == '{', "Config");
					conf->itemName = s;
				}
				else {
					conf->dataString = s;
					conf = Config_Create(conf);
					if ('{' == *s && '\0' == *(s+1)) conf->depth++;
				}

				for ( ; loop<fileSize ; loop++) if ('\0' == *(s++)) break;
			} else s++;
		}

	}

	configGlobs.flags &= ~CONFIG_FLAG_LOADINGCONFIG;

	return rootConf;
}

LPUCHAR Config_BuildStringID(LPUCHAR s, ...){
	
	va_list args;
	static UCHAR string[1024];
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

lpConfig Config_FindArray(lpConfig root, LPUCHAR name){

	lpConfig conf;

	if (conf = Config_FindItem(root, name)){
		if (conf->depth < conf->linkNext->depth) return conf->linkNext;
	}
	return NULL;
}

Config *Config_GetNextItem(Config *start){

	ULONG level = start->depth;
	Config *conf = start;

	while(conf){
		if (conf->depth < level) return NULL;
		conf = conf->linkNext;
		if (conf->depth == level) return conf;
	}
	return NULL;
}

#ifdef _DEBUG

LPUCHAR Config_GetStringValueDebug(Config *root, LPUCHAR stringID, ULONG line, LPUCHAR file){

	Config *conf;
	LPUCHAR str;

	if (conf = Config_FindItem(root, stringID)){
		if (conf->dataString){
			str = Mem_AllocDebug(strlen(conf->dataString) + 1, line, file);
			strcpy(str, conf->dataString);
			return str;
		}
	}
	
	return NULL;
}

#else 

LPUCHAR Config_GetStringValue(Config *root, LPUCHAR stringID){

	Config *conf;
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

#endif //_DEBUG

LPUCHAR Config_GetTempStringValue(Config *root, LPUCHAR stringID){

	Config *conf;

	if (conf = Config_FindItem(root, stringID)){
		return conf->dataString;
	}
	
	return NULL;
}

ULONG Config_GetBoolValue(Config *root, LPUCHAR stringID){

	LPUCHAR string;
	ULONG res = 2;

	if (string = Config_GetStringValue(root, stringID)){
	
		res = Util_GetBoolFromString(string);
		Mem_Free(string);
	}

	return res;
}

REAL Config_GetAngle(Config *root, LPUCHAR stringID){

	REAL degrees;

	if (degrees = Config_GetRealValue(root, stringID)){
		return (degrees / 360.0f) * (2.0f * M_PI);
	}

	return 0.0f;
}

BOOL Config_GetRGBValue(Config *root, LPUCHAR stringID, LPREAL r, LPREAL g, LPREAL b){

	LPUCHAR argv[100], string;
	BOOL res = FALSE;

	if (string = Config_GetStringValue(root, stringID)){
		if (3 == Util_Tokenise(string, argv, ":")){
			*r = atoi(argv[0]) / 255.0f;
			*g = atoi(argv[1]) / 255.0f;
			*b = atoi(argv[2]) / 255.0f;

			res = TRUE;

		} else Error_Warn(TRUE, Error_Format("Invalid RBG entry '%s'", Config_GetTempStringValue(root, stringID)));

		Mem_Free(string);
	}

	return res;
}

BOOL Config_GetCoord(Config *root, LPUCHAR stringID, LPREAL x, LPREAL y, LPREAL z){

	LPUCHAR argv[100], string;
	BOOL res = FALSE;

	Error_Fatal(!x||!y, "Null passed as x or y");

	if (string = Config_GetStringValue(root, stringID)){
		if (NULL == z) {
			if (2 != Util_Tokenise(string, argv, ",")) Error_Warn(TRUE, Error_Format("Invalid 2D Coordinate entry '%s'", string));
		} else if (3 == Util_Tokenise(string, argv, ",")) *z = (REAL) atof(argv[2]);
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

BOOL Config_GetKey(lpConfig root, LPUCHAR stringID, LPUCHAR key) {

	LPUCHAR string;

	if (string = Config_GetTempStringValue(root, stringID)){
		return Key_Find(string, key);
	}

	return FALSE;
}


VOID Config_Free(lpConfig root){

	lpConfig next;

	Error_Fatal(NULL==root->fileData, "Only pass the root (loaded) config structure to Config_Free()");

	Mem_Free(root->fileData);
	while(root){
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

static lpConfig Config_Create(lpConfig prev){

	lpConfig newConfig;

	Config_CheckInit();

	if (NULL == configGlobs.freeList) Config_AddList();
	
	newConfig = configGlobs.freeList;
	configGlobs.freeList = newConfig->nextFree;
	newConfig->nextFree = newConfig;

	newConfig->itemName = NULL;
	newConfig->dataString = NULL;
	newConfig->linkNext = NULL;
	
	if (NULL != prev) {
		prev->linkNext = newConfig;
		newConfig->linkPrev = prev;
		newConfig->depth = prev->depth;
//		newConfig->fileData = prev->fileData;
		newConfig->fileData = NULL;
	} else {
		newConfig->depth = 0;
		newConfig->linkPrev = NULL;
	}

#ifdef _DEBUG
	newConfig->accessed = FALSE;
#endif // _DEBUG

	return newConfig;
}

static VOID Config_Remove(lpConfig dead){

	Config_CheckInit();
	Error_Fatal(!dead, "NULL passed to Config_Remove()");

#ifdef _DEBUG
	if (configGlobs.debugLastFind == dead) configGlobs.debugLastFind = NULL;
#endif // _DEBUG

	dead->nextFree = configGlobs.freeList;
	configGlobs.freeList = dead;
}
 
 
 /*
static Config *Config_Create(Config *prev){
	
	// For now just search through the list and return a free item.

	ULONG loop;
	Config *conf = NULL;

	for (loop=0 ; loop<CONFIG_MAXCONFIG ; loop++){
		if (!(confGlobs.configArray[loop].flags & CONFIG_FLAG_USED)){
			conf = &(confGlobs.configArray[loop]);
			conf->itemName = NULL;
			conf->dataString = NULL;
			conf->linkNext = NULL;
			
			if (NULL != prev) {
				prev->linkNext = conf;
				conf->linkPrev = prev;
				conf->depth = prev->depth;
				conf->fileData = prev->fileData;
			} else {
				conf->depth = 0;
				conf->linkPrev = NULL;
			}

			conf->flags |= CONFIG_FLAG_USED;

			break;
		}
	}

	if (!conf) Error_Fatal(TRUE, "Could not allocate config item");

	return conf;
}
*/

lpConfig Config_FindItem(lpConfig conf, char *stringID){

	// Search the list for the given item.
	
	LPUCHAR argv[CONFIG_MAXDEPTH];
	ULONG count, currDepth;
	Config *backConf, *foundConf = NULL;
	LPUCHAR tempstring = Mem_Alloc(strlen(stringID)+1);
	BOOL wildcard;

	strcpy(tempstring, stringID);

	count = Util_Tokenise(tempstring, argv, "::");

	// First find anything that matches the depth of the request
	// then see if the hierarchy matches the request.

	while(conf){
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

	Mem_Free(tempstring);

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

/*********************************************************************************
 ****** Debug Code
 ********************************************************************************/

#ifdef _DEBUG

VOID Config_DumpStructure(Config *conf){

	ULONG depth = 0, loop;

	while(conf){

		for (loop=0 ; loop<conf->depth ; loop++) Error_Debug(Error_Format("\t"));
		Error_Debug(Error_Format("[%s](%s) (%d)\n", conf->itemName, conf->dataString, conf->depth));

		conf = conf->linkNext;
	}
}

/*
VOID Config_WriteBinary(lpConfig root, LPUCHAR fname) {

	lpConfig conf, subConf;
	lpFile ofp;

	if (ofp = File_Open(fname, "wb") {

		// Generate the hash codes...
		for (conf=root ; conf->linkNext ; conf=conf->linkNext) conf->itemHashCode = Util_HashString(conf->itemName, FALSE);

		// Check to see if any different strings produced the same code (2^32 against, but hey)...
		Error_CheckWarn(FALSE);
		for (conf=root ; conf->linkNext ; conf=conf->linkNext) {
			for (subConf=root ; subConf->linkNext ; subConf=subConf->linkNext) {
				if (0 != strcmp(conf->itemName, subConf->itemName)) {
					Error_Warn(conf->itemHashCode==subConf->itemHashCode, Error_Format(">%s< and >%s< produce the same has code", conf->itemName, subConf->itemName));
				}
			}
		}
		Error_CheckWarn(TRUE);

		File_Write(CONFIG_BINARYFILEID, 1, strlen(CONFIG_BINARYFILEID), ofp);
		for (conf=root ; conf->linkNext ; conf=conf->linkNext) {
			
		}

		File_Close(ofp);
	}
}
*/
#endif // _DEBUG

/**********************************************************************************
 ******** Config Static Functions
 **********************************************************************************/

static VOID Config_AddList(VOID){

	lpConfig list;
	ULONG loop, count;

	Config_CheckInit();

	Error_Fatal(configGlobs.listCount+1 >= CONFIG_MAXLISTS, "Run out of lists");

	count = 0x00000001 << configGlobs.listCount;

	if (list = configGlobs.listSet[configGlobs.listCount] = 
		Mem_Alloc(sizeof(Config) * count)){

		configGlobs.listCount++;

		for (loop=1 ; loop<count ; loop++){

			list[loop-1].nextFree = &list[loop];
		}
		list[count-1].nextFree = configGlobs.freeList;
		configGlobs.freeList = list;

	} else Error_Fatal(TRUE, Error_Format("Unable to allocate %d bytes of memory for new list.\n", sizeof(Config) * count));
}

static VOID Config_RunThroughLists(VOID){

	ULONG list, count, loop;
	lpConfig tempConfig;

	for (list=0 ; list<configGlobs.listCount ; list++){
		if (configGlobs.listSet[list]){
			count = 0x00000001 << list;
			for (loop=0 ; loop<count ; loop++){
				if (tempConfig = &configGlobs.listSet[list][loop]){
					if (tempConfig->nextFree == tempConfig){

						// This is a valid unremoved config....
	
					}
				}
			}
		}
	}
}

