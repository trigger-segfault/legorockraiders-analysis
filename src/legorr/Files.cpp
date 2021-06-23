
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <windows.h>  // for extended case-insensitive str API?

#include "Common.h"
#include "Files.h"
#include "Util.h"


// gamename may actually be gamepath (as called from the commandline arguments)
// 
// <LegoRR.exe @0047f3f0>
void __cdecl Path_InitDataDir(const char* gamename, BOOL insistOnCD, const char* regKey)
{
	char cVar1;
	// bool hasWADs;
	int iVar3;
	HANDLE handle;
	FILE *file;
	uint uVar4;
	uint uVar5;
	undefined4 *puVar6;
	char *pcVar7;
	char *pcVar8;
	char *pcVar9;
	undefined4 *puVar10;
	int local_f24;
	byte local_e1c;
	char local_e08[MAX_PATH /*260*/];
	char dataDir[MAX_PATH /*260*/];
	// undefined4 local_c00;
	// undefined2 local_bfc;
	// undefined4 local_bfa[254];
	// char local_c00[0x400 /*1024*/];
	char errorMessage[0x400 /*1024*/]; // local_c00
	char cdkeyFile[0x400 /*1024*/]; // local_800
	char regValue[0x400 /*1024*/]; // local_400


	// assign one of our too Data directory globals...
	char currentDir[MAX_PATH /*260*/];
	_getcwd(currentDir, MAX_PATH /*260*/);
	// The Ghidra decompilation for this was so messed up...
	//  (`currentDir[0] != '\0'` added to circumvent stack safefty jank)
	size_t currentLen = strlen(currentDir);
	if (currentLen != 0 && currentDir[currentLen-1] == '\\') {
		currentDir[currentLen-1] = '\0';
	}
	sprintf(g_FILEPATH_DATADIR_2, "%s\\%s", currentDir, "Data");

	// check for WAD files 0-9
	bool hasWADs = false;
	for (int i = 0; i < WADFILES_COUNT /*10*/; i++) {
		sprintf((char *)&local_e1c, "%s%i.wad", gamename, i);
		if (WAD_Open((char *)&local_e1c) != -1) {
			hasWADs = true;
		}
	}
	
	// assign the other one of our Data directory globals...
	_getcwd(dataDir, MAX_PATH);
  	strcat(dataDir, "\\Data");
	Path_SetDataDir(dataDir);

	// If no CD and game is hungry for CD...
	// loop until user inserts CD and CD is detected,
	//  or until user accepts their fate and presses OK on message box to exit
	bool hasCDROM = Path_CheckForCDROM();
	while (!hasCDROM && insistOnCD) {
		memset(errorMessage, 0, 0x400);
		strcpy(errorMessage, "Error");
		// iVar3 = 0xfe;
		// puVar6 = local_bfa;
		// while (iVar3 != 0) {
		// 	iVar3 = iVar3 + -1;
		// 	*puVar6 = 0;
		// 	puVar6 = puVar6 + 1;
		// }
		// *(undefined2 *)puVar6 = 0;
		// local_c00 = s_Error_004abf40._0_4_; // "Error"
		// local_bfc = s_Error_004abf40._4_2_; // "Error"
		iVar3 = reg_query__FUN_0048b620(regKey, "CDMissing", 0, regValue, 0x400);
		if (iVar3 == 0) {
			// LAB_0047f59b:
			exit(0);
		}
		else {
			reg_query__FUN_0048b620(regKey, "SetupError", 0, errorMessage, 0x400);
			iVar3 = MessageBoxA(NULL, regValue, errorMessage, 1);
			if (iVar3 == 2)
				exit(0);
				// goto LAB_0047f59b;
		}
		hasCDROM = Path_CheckForCDROM();
	}

	// no WAD files, find Data directory
	bool missingData = false;
	if (!hasCDROM && !hasWADs) {
		missingData = true;
		_finddata_t fileinfo; // local_e1c
		intptr_t handle = _findfirst("*.*", &fileinfo);
		if (handle != -1) {
			do {
				if ((fileinfo.attrib & FILE_ATTRIBUTE_DIRECTORY) != 0 && _stricmp(fileinfo.name, "Data") == 0) {
					missingData = false; // data dir found??
					break;
				}
			} while (_findnext(handle, &fileinfo) == 0);
			_findclose(handle);
		}
	}

	// What the hell is this doing??
	if (insistOnCD) {
		sprintf(cdkeyFile, "%s\\%s", "Data", "cd.key");
		FILE* file = fopen(cdkeyFile, "r");
		if (file != NULL) {
			fclose(file);
			missingData = true; // has CD?? what....???
		}
	}

	// "delme.dat"
	if (!missingData) { // no CD, and no Data dir?
		_mkdir("Data"); // create Data dir
		sprintf(cdkeyFile, "%s\\%s", "Data", "delme.dat");
		FILE* file = fopen(cdkeyFile, "r");
		if (file != NULL) { // data dir must have already existed???
			fclose(file);
			_chmod(cdkeyFile, FILE_ATTRIBUTE_NORMAL /*0x80*/);
			remove(cdkeyFile);
			return;
		}
		// regardless, after this the function finishes successfully
	}
	else {
		memset(errorMessage, 0, 0x400);
		strcpy(errorMessage, "Error");

		// errorMessage._0_4_ = s_Error_004abf40._0_4_;
		// iVar3 = 0xfe;
		// errorMessage._4_2_ = s_Error_004abf40._4_2_;
		// puVar6 = (undefined4 *)(errorMessage + 6);
		// while (iVar3 != 0) {
		// 	iVar3 = iVar3 + -1;
		// 	*puVar6 = 0;
		// 	puVar6 = puVar6 + 1;
		// }
		// *(undefined2 *)puVar6 = 0;
		iVar3 = reg_query__FUN_0048b620(regKey, "DataMissing", 0, regValue, 0x400);
		if (iVar3 != 0) {
			reg_query__FUN_0048b620(regKey, "SetupError", 0, errorMessage, 0x400);
			MessageBoxA(NULL, regValue, errorMessage, 0);
		}
		exit(0);
	}
}

// Checks for a currently-inserted CDROM drive containing the file "CDROM:\Data\cd.key"
// Does not actually check contents of the file.
// Returns true when found, and assigns global: char g_CDROM_DriveLetter;
// 
// <LegoRR.exe @0047f7b0>
BOOL __cdecl Path_CheckForCDROM(void);
{
	char buffer[MAX_PATH]; // 260
	char rootName[4] = { 'A', ':', '\\', '\0' }; //"A:\\";
	// // if the above is not legal, use this instead
	// char rootName[4];
	// rootName[0] = 'A';
	// rootName[1] = ':';
	// rootName[2] = '\\';
	// rootName[3] = '\0';

	// iterate through all drive letters to find CDROM drive types.
	//  (besides 'A','B' which are reserved for floppies)
	for (char letter = 'C'; letter <= 'Z'; letter++) {
		rootName[0] = letter;
		if (GetDriveTypeA(rootName) == DRIVE_CDROM /*5*/) {
			// confirm this CDROM drive has the file "CDROM:\Data\cd.key"
			sprintf(buffer, "%c:\\%s\\%s", letter, "Data", "cd.key");
			FILE* file = fopen(buffer, "r");
			if (file != NULL) {
				fclose(file);
				g_CDROM_DriveLetter = letter; // assign drive letter, for later use
				return true;
			}
		}
	}
	return false;
}

// <LegoRR.exe @0047f850>
void __cdecl Path_SetDataDir(const char* dirname)
{
	if (dirname != NULL) {
		int strLength = (int)strlen(dirname);
		if (strLength <= 0x400 && strLength != 0) {
			strcpy(g_FILEPATH_DATADIR_1, dirname);
			g_HAS_DATADIR = true;
			return;
		}
	}
	g_HAS_DATADIR = false;
	memset(g_FILEPATH_DATADIR_1, 0, 0x400);
}

// Open WAD filename and log something (that was removed on release build)
// returns idx of newly opened WAD (0-9), or -1 on failure of any kind.
//
// <LegoRR.exe @0047f900>
int __cdecl WAD_Open(char *filename)
{
	logf_removed(NULL);
	return WAD_Open__internal(filename);
}

// <LegoRR.exe @0047f920>
BOOL __cdecl Path_GetCDROMDataPath(char* out_filepath, const char* filename)
{
	if (g_CDROM_DriveLetter != '\0') {
		sprintf(out_filepath, "%c:\\%s\\%s", g_CDROM_DriveLetter, "Data", filename);
		return true;
	}
	return false;
}

// <LegoRR.exe @0047f960>
int __cdecl Path_MakeDataSubdir(const char* dirname)
{
	char buffer[MAX_PATH /*260*/];

	sprintf(buffer, "%s\\%s", "Data", dirname);
	return _mkdir(buffer);
}

// <LegoRR.exe @0047f9a0>
LegoFileStream* __cdecl File_Open(const char* in_filename, const char* mode)
{
	char *filename;
	uint uVar1;
	FILE *realFile;
	char *message;
	BOOL BVar3;
	LegoFileStream* legoFile;
	char buffer[MAX_PATH /*260*/];

	filename = Path_JoinDataDir(in_filename);
	LegoFileLocation location = File_FindLocation(filename, mode);
	if (location == FILELOC_WAD /*0*/) {
		legoFile = File__New(FILELOC_WAD /*0*/);
		if (legoFile == NULL) {
			return NULL;
		}
		message = Path_StripDataDir(filename);
		if (WAD_EntryOpen__internal(legoFile->data.wad, message) != false) {
			filename = Path_StripDataDir(filename);
			logf_removed("WAD Load %s\n", filename);
			return legoFile;
		}
		filename = Path_StripDataDir(filename);
		message = "WAD Fail %s\n";
	}
	else if (location == FILELOC_REAL /*1*/) {
		legoFile = File__New(FILELOC_REAL /*1*/);
		if (legoFile == NULL)
			return NULL;

		realFile = fopen(filename, mode);
		legoFile->stream.real = realFile;
		if (realFile != NULL) {
			logf_removed("STD Load %s\n", filename);
			return legoFile;
		}

		// file not found in datadir, check CDROM (and enforce readonly)
		const char* modeMatch = strstri(mode, "w");
		if (modeMatch == NULL && Path_GetCDROMDataPath(buffer, in_filename) != false) {
			realFile = fopen(buffer, mode);
			legoFile->stream.real = realFile;
			if (realFile != NULL)
				return legoFile;
		}
		message = "STD Fail %s\n";
	}
	else {
		printf("%s(%i) : Error in call to %s\n", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 0x14a, "File_Open");
		return NULL;
	}
	logf_removed(message, filename);
	File__Dispose(legoFile);
	return NULL;
}

// <LegoRR.exe @0047fb10>
int __cdecl File_Seek(LegoFileStream* file, long int offset, int origin)
{
	///TODO: decompile me
}

// <LegoRR.exe @0047fc40>
size_t __cdecl File_Read(void* out_ptr, size_t size, size_t count, LegoFileStream* file)
{
	///TODO: decompile me
}

// <LegoRR.exe @0047fd10>
size_t __cdecl File_Write(const void* ptr, size_t size, size_t count, LegoFileStream* file)
{
	LegoFileLocation location = File_GetLocation(file);
	if (location == FILELOC_WAD /*0*/) {
		printf("Cannot write to a file stored in a Wad!");
		return 0;
	}
	if (location == FILELOC_REAL /*1*/) {
		return fwrite(ptr, size, count, file->stream.real);
	}
	printf("%s(%i) : Unknown file system in call to %s", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 0x19e, "File_Write");
	return 0;
}

// <LegoRR.exe @0047fd80>
int __cdecl File_Close(LegoFileStream* file)
{
	LegoFileLocation location = File_GetLocation(file);
	if (location >= 0 && location < 2) { // == FILELOC_WAD || == FILELOC_REAL
		File__Dispose(file);
		return 0;
	}
	printf("%s(%i) : Unknown file system in call to %s", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 0x1af, "File_Close");
	return 0;
}

// <LegoRR.exe @0047fdd0>
long int __cdecl File_Tell(LegoFileStream* file)
{
	LegoFileLocation location = File_GetLocation(file);
	if (location == FILELOC_WAD /*0*/) {
		return (long int)file->stream.wad->position;
		// return *(int *)(file->stream + 4);
	}
	if (location == FILELOC_REAL /*1*/) {
		return ftell(file->stream.real);
	}
	printf("%s(%i) : Unknown file system in call to %s", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 0x1d5, "File_Tell");
	return 0;
}

// <LegoRR.exe @0047fe20>
BOOL __cdecl File_Exist(const char* filename)
{
	const char* dataFilename = Path_JoinDataDir(filename);
	LegoFileLocation location = File_FindLocation(dataFilename, "r");
	if (location == FILELOC_REAL /*1*/) {
		FILE* file = fopen(dataFilename, "r");
		if (file != NULL) {
			fclose(file);
			return true;
		}
		if (Path_GetCDROMDataPath(buffer, filename) != false) {
			file = fopen(buffer, "r");
			if (file != NULL) {
				fclose(file);
				return true;
			}
		}
	}
	else if (location == FILELOC_WAD /*0*/) {
		// brilliant! This fails regardless because the data directory wasn't stripped before calling this...
		// this is really dumb, invalid values from this return -1, and valids values can be 0.
		return WAD_FindEntry(dataFilename, g_WAD_ANYINDEX /*-1*/);
	}
	return false; // meanwhile we return 0 here on failure... GAHHH
}

// <LegoRR.exe @0047fee0>
int __cdecl File_GetC(LegoFileStream* file)
{
	///TODO: decompile me
}

// <LegoRR.exe @0047ff60>
long int __cdecl File_GetLength(LegoFileStream* file)
{
	int offset = File_Tell(file);
	File_Seek(file, 0, SEEK_END /*2*/);
	long int length = File_Tell(file);
	File_Seek(file, offset, SEEK_SET /*0*/);
	return length;
}

// <LegoRR.exe @0047ffa0>
char* __cdecl File_GetS__internal(char* out_str, int num, LegoFileStream* file)
{
	///TODO: decompile me
}

// <LegoRR.exe @00480000>
char* __cdecl File_GetS(char* out_str, int num, LegoFileStream* file)
{
	///TODO: decompile me
}

// <LegoRR.exe @00480070>
int __cdecl File_PrintF(LegoFileStream* file, const char* format, ...)
{
	///TODO: decompile me
}

// <LegoRR.exe @004800e0>
LegoFileLocation __cdecl File_GetLocation(LegoFileStream* file)
{
	return file->location;
}

// Returns 0 if file is found in WAD
// Returns 1 if arguments are valid and mode is "r"/"R".
// Otherwise, returns 0.
// 
// <LegoRR.exe @004800f0>
LegoFileLocation __cdecl File_FindLocation(const char* filename, const char* mode)
{
	if (filename != NULL && mode != NULL && strlen(filename) != 0 && strlen(mode) != 0) {
		if (*mode != 'w' && *mode != 'W') {
			filename = Path_StripDataDir(filename);
			int entryIndex = WAD_FindEntry(filename, g_WAD_ANYINDEX /*-1*/);
			if (entryIndex != -1)
				return FILELOC_WAD /*0*/; //false /*0*/;
		}
		return FILELOC_REAL /*1*/; //true /*1*/;
	}
	return FILELOC_ERROR /*2*/; //BOOL3_ERROR;
}

// <LegoRR.exe @00480160>
BOOL __cdecl WAD_EntryOpen__internal(LegoWADStream* wadStream, const char* filename)
{  
	wadStream->field_8 = 0;
	wadStream->position = 0;
	int sharedIndex = WAD_SharedOpen(filename, g_WAD_ANYINDEX /*-1*/);
	wadStream->sharedIndex = sharedIndex;
	return (sharedIndex != -1);
}

// <LegoRR.exe @00480190>
LegoFileStream* __cdecl File__New(LegoFileLocation location)
{
	if (location == FILELOC_REAL /*1*/) {
		LegoFileStream* file = File__New__alloc(sizeof(LegoFileStream) /*8*/);
		// SANITY: no null check here... heh
		file->location = FILELOC_REAL /*1*/; //true;
		return file;
	}
	if (location == FILELOC_WAD /*0*/) {
		LegoFileStream* file = File__New__alloc(sizeof(LegoFileStream) /*8*/);
		if (file != NULL) {
			file->location = FILELOC_WAD /*0*/; //false;

			LegoWADStream* wadFile = (LegoWADStream*)File__New__alloc(sizeof(LegoWADStream) /*0xc*/);
			file->stream.wad = wadFile;
			if (wadFile != NULL) {
				return file;
			}
			File__New__free(file);
		}
	}
	return NULL;
}

// <LegoRR.exe @004801f0>
void* __cdecl File__New__alloc(size_t size)
{
	return malloc(size);
}

// <LegoRR.exe @00480200>
void __cdecl File__New__free(void* ptr)
{
	free(ptr);
}

// <LegoRR.exe @00480210>
void __cdecl File__Dispose(LegoFileStream* file)
{
	LegoFileLocation LVar1;

	if (file != NULL) {
		LegoFileLocation location = File_GetLocation(file);
		if (location == FILELOC_REAL /*1*/) {
			if (file->stream.real != NULL) {
				fclose(file->stream.real);
			}
		}
		else if (location == FILELOC_WAD /*0*/) {
			if (file->stream.wad != NULL) {
				WAD_Shared__Dispose(file->stream.wad);
				File__New__free(file->stream.wad);
			}
		}
		else {
			return;
		}
		File__New__free(file);
	}
}

// Strips the Data directory from the filename path, using global g_FILEPATH_DATADIR_1 as a comparison.
// Returns a temporary buffer that must be used before this function is next called.
// 
// <LegoRR.exe @00480280>
const char* __cdecl Path_StripDataDir(const char* filename)
{
	if (g_HAS_DATADIR == false)
		return filename;

	int datadirLen = (int)strlen(g_FILEPATH_DATADIR_1);
	if (strlen(filename) <= datadirLen) // shorter than DATADIR, can't start with datadir
		return filename;
	
	char c = filename[datadirLen]; // backup original char here (which *should* be path separator, but could potentially be something else)
	filename[datadirLen] = '\0';   // then replace that char with null-terminator
	if (_stricmp(filename, g_FILEPATH_DATADIR_1) == 0) { // compare filename and datadir (could be replaced with strnicmp)
		sprintf(g_TMP_FILEPATH_STRIPDATADIR, "%s", filename + datadirLen + 1);
		filename[datadirLen] = c; // restore char
		return g_TMP_FILEPATH_STRIPDATADIR;
	}
	filename[datadirLen] = c; // restore char
	return filename;
}

// all parameters are directly passed to File_GetS, then some operation on string is performed
// 
// <LegoRR.exe @00480310>
char* __cdecl File_UNK_calls_GetS_00480310(char* out_str, int num, LegoFileStream* file)
{
	///TODO: decompile me
}

// <LegoRR.exe @00480360>
unsigned char* __cdecl File_ReadAllBytes(const char* filename, unsigned int* out_length)
{
	return File_ReadAll(filename, out_length, true);
}

// <LegoRR.exe @00480380>
unsigned char* __cdecl File_ReadAll(const char* filename, unsigned int* out_length, BOOL isBinary)
{
	LegoFileStream* file = File_Open(filename, isBinary ? "rb" : "r");
	if (file != NULL) {
		File_Seek(file, 0, SEEK_END /*2*/);
		int length = File_Tell(file);

		if (g_WAD_unkFuncPtr_A_005353ac != (code*)NULL) {
			(*g_WAD_unkFuncPtr_A_005353ac)(filename, length, g_WAD_unkFuncValue_A_005353b0);
		}
		unsigned char buffer = (unsigned char*)malloc(length);
		if (buffer != NULL) {
			File_Seek(file, 0, SEEK_SET /*0*/);
			File_Read(buffer, 1, length, file);
			if (out_length != NULL) {
				*out_length = length;
			}
		}
		File_Close(file);
		return buffer;
	}
	return NULL;
}

// <LegoRR.exe @00480430>
int __cdecl File_UNK_ReadAllBytesTableBuffer_00480430(const char* filename, size_t* out_length)
{
	///TODO: decompile me
}

// Join filename path with global g_FILEPATH_DATADIR_2.
// Returns a temporary buffer that must be used before this function is next called.
// 
// <LegoRR.exe @004804e0>
const char* __cdecl Path_JoinDataDir(const char* filename)
{
	char buffer[MAX_PATH /*260*/];

	if (filename != NULL) {
		if (*filename == '\\')
			filename++;

		sprintf(buffer, "%s\\%s", g_FILEPATH_DATADIR_2, filename);
		if (_fullpath(g_TMP_FILEPATH_JOINDATADIR, buffer, MAX_PATH /*260*/) != NULL) {

			if (_strncmp(g_TMP_FILEPATH_JOINDATADIR, g_FILEPATH_DATADIR_2, strlen(g_FILEPATH_DATADIR_2)) == 0) {
				return g_TMP_FILEPATH_JOINDATADIR;
			}
		}
	}
	return NULL;
}

// <LegoRR.exe @00480570>
void __cdecl WAD_setFunctPtrValue_A__00480570(void* unkFuncPtr, unsigned int unkValue);
{
	g_WAD_unkFuncPtr_A_005353ac = unkFuncPtr;
	g_WAD_unkFuncValue_A_005353b0 = unkValue;
}

// <LegoRR.exe @00480590>
void __cdecl Path_ScanRealFiles__UNK__00480590(const char* filename)
{
	///TODO: decompile me
}

// <LegoRR.exe @00480650>
void __cdecl File_Find(const char* dirname)
{
	char buffer[0x400 /*1024*/]; // local_400

	strcpy(buffer, dirname);
	strcat(buffer, "\\*.*");

	_finddata_t finddata;
	intptr_t handle = _findfirst(buffer, &finddata);
	if (handle != -1) {
		do {
			if (strcmp(finddata.name, ".") != 0 && strcmp(finddata.name, "..") != 0) {
				strlen(dirname);
				strcpy(buffer, dirname);
				strcat(buffer, "\\");
			}

			if ((filedata.attrib & FILE_ATTRIBUTE_DIRECTORY /*0x10*/) == 0) {
				FUN_00480830((char *)buffer); // an actual file
			}
			else {
				File_Find((char *)buffer); // a directory, recurse with this function
			}
		} while (_findnext(handle, &finddata) == 0);
		_findclose(handle);
	}
}

// <LegoRR.exe @00480830>
void __cdecl FUN_00480830(const char* filename)
{
	///TODO: decompile me
}

// called in one of the LegoRR main initialization functions <LegoRR.exe @00477a60>
// 
// <LegoRR.exe @004896b0>
void __cdecl File_UNK_InitTableBuffers_004896b0(void)
{
	for (int index = 0; index < 2000; index++) {
		g_UNKFILE_BUFFERS_TABLE[index].buffer = NULL;
		g_UNKFILE_BUFFERS_TABLE[index].flags = 0U;
	}
}

// <LegoRR.exe @004896d0>
int __cdecl File_UNK_AllocTableBuffer_004896d0(size_t size)
{
	for (int index = 0; index < 2000; index++) {
		if ((g_UNKFILE_BUFFERS_TABLE[index].flags & 0x1) == 0) { // not isUsed
			void* buffer = malloc(size);
			g_UNKFILE_BUFFERS_TABLE[index].buffer = buffer;
			g_UNKFILE_BUFFERS_TABLE[index].flags |= 0x1; // isUsed
			return index;
		}
	}
	return -1;
}

// <LegoRR.exe @00489720>
void __cdecl File_UNK_FreeTableBuffer_00489720(unsigned int index)
{
	if (index < 2000 && (g_UNKFILE_BUFFERS_TABLE[index].flags & 0x1) != 0) { // isUsed
		free(g_UNKFILE_BUFFERS_TABLE[index].buffer);
		g_UNKFILE_BUFFERS_TABLE[index].buffer = NULL;
		g_UNKFILE_BUFFERS_TABLE[index].flags = 0U; // not isUsed
	}
}

// <LegoRR.exe @00489760>
void* __cdecl File_UNK_GetTableBuffer_00489760(unsigned int index)
{
	if (index < 2000 && (g_UNKFILE_BUFFERS_TABLE[index].flags & 0x1) != 0) { // isUsed
		return g_UNKFILE_BUFFERS_TABLE[index].buffer;
	}
	return NULL;
}


// Open and read data into WAD file.
// returns idx of newly opened WAD (0-9), or -1 on failure of any kind.
// 
// <LegoRR.exe @0048b7a0>
int __cdecl WAD_Open__internal(const char* filename)
{
	int idx = WAD__Next(); // prepare and get next available WAD index
	if (idx == -1) {
		// FAIL: no more WAD files to load (max 10 can be loaded at once)
		goto cleanup_end;
	}
	
	FILE* file = fopen(filename, "rb");
	WAD_Get(idx)->file = file;
	if (file == NULL) {
		// FAIL: could not open WAD file
		goto cleanup_end;
	}
	
	WAD_Get(idx)->isUsed = true;

	char signature[4];
	
	// signature check "WWAD"
	if (fread(signature, 1, 4, file) != 4 || memcmp(signature, "WWAD", 4) != 0) {
		// FAIL: could not read file signature, or signature did not match "WWAD"
		goto cleanup_close;
	}

	// read number of file entries
	if (fread(&WAD_Get(idx)->count, 1, 4, file) != 4) {
		// FAIL: could not read file entry count
		goto cleanup_close;
	}

	// allocate buffers to store relative and absolute entry file paths
	WAD_Get(idx)->reldirs = malloc(WAD_Get(idx)->count * sizeof(char*)); // count * 4 (probably for pointers)
	WAD_Get(idx)->absdirs = malloc(WAD_Get(idx)->count * sizeof(char*)); // count * 4 (probably for pointers)
	if (WAD_Get(idx)->reldirs == NULL || WAD_Get(idx)->absdirs == NULL) {
		// FAIL: could not allocate reldirs or absdirs buffers
		goto cleanup_allocs;
	}

	// zero out memory, so that, on failure, we don't try to free strings that haven't yet been allocated
	memset(WAD_Get(idx)->reldirs, 0, WAD_Get(idx)->count * sizeof(char*)); // count * 4
	memset(WAD_Get(idx)->absdirs, 0, WAD_Get(idx)->count * sizeof(char*)); // count * 4

	char strBuffer[4096]; // temp buffer used for reading C-String reldirs/absdirs one-by-one
	
	// read WAD file relative directories
	for (int i = 0; i < (int)WAD_Get(idx)->count; i++) {
		if (freadstr(file, strBuffer) == false) {
			// FAIL: could not read cstring
			// although freadstr never returns false...
			goto cleanup_reldirs;
		}

		WAD_Get(idx)->reldirs[i] = _strdup(strBuffer);
		printf("%s\n", WAD_Get(idx)->reldirs[i]);
	}
	
	// read WAD file absolute directories
	for (int i = 0; i < (int)WAD_Get(idx)->count; i++) {
		if (freadstr(file, strBuffer) == false) {
			// FAIL: could not read cstring
			// although freadstr never returns false...
			goto cleanup_absdirs;
		}

		WAD_Get(idx)->absdirs[i] = _strdup(strBuffer);
		printf("%s\n", WAD_Get(idx)->absdirs[i]);
	}

	// read WAD file entry metadata
	WAD_Get(idx)->entries = malloc(WAD_Get(idx)->count * sizeof(LegoWADEntry)); // count * 4
	if (WAD_Get(idx)->entries == NULL) {
		// FAIL: could not allocate entries buffer
		goto cleanup_absdirs;
	}
	
	// read in entry data directly from file into entries buffer
	if (fread(WAD_Get(idx)->entries, 1, WAD_Get(idx)->count * sizeof(LegoWADEntry)) // count * 16
		== (WAD_Get(idx)->count * sizeof(LegoWADEntry))) // count * 16
	{
		// successfully read all entries. WE'RE DONE!!!!!!
		return idx;
	}

	// FAIL: could not read entire file entries buffer

cleanup_entries:
	if (WAD_Get(idx)->entries != NULL) {
		free(WAD_Get(idx)->entries);
	}

cleanup_absdirs:
	if (WAD_Get(idx)->absdirs != NULL) {
		// cleanup allocated absolute directory file paths
		for (int j = 0; j < (int)WAD_Get(idx)->count; j++) {
			if (WAD_Get(idx)->absdirs[j] != NULL) {
				free(WAD_Get(idx)->absdirs[j]);
			}
		}
		// free(WAD_Get(idx)->absdirs);
	}

cleanup_reldirs:
	// failure, clean up half-finished WAD file reading
	// although freadstr never returns false...
	if (WAD_Get(idx)->reldirs != NULL) {
		// cleanup allocated relative directory file paths
		for (int j = 0; j < (int)WAD_Get(idx)->count; j++) {
			if (WAD_Get(idx)->reldirs[j] != NULL) {
				free(WAD_Get(idx)->reldirs[j]);
			}
		}
		// free(WAD_Get(idx)->reldirs);
	}
	// goto cleanup_allocs;
	// if (WAD_Get(idx)->absdirs != NULL) {
	// 	free(WAD_Get(idx)->absdirs);
	// }
	// fclose(file);
	// goto cleanup_end;
	// goto cleanup_close;

cleanup_allocs:
	// fclose(file);
	if (WAD_Get(idx)->reldirs != NULL)
		free(WAD_Get(idx)->reldirs);
	if (WAD_Get(idx)->absdirs != NULL)
		free(WAD_Get(idx)->absdirs);
	// goto cleanup_end;
	// goto cleanup_close;

cleanup_close:
	fclose(file);

cleanup_end:
	return -1;
}

// Returns LegoWADFile at idx in table. (0-9)
// 
// <LegoRR.exe @0048bfa0>
LegoWADFile* __cdecl WAD_Get(int wadIndex)
{
	return &g_WADFILES_TABLE[wadIndex];
}

// <LegoRR.exe @0048bfb0>
size_t __cdecl WAD_GetEntrySize2(int wadIndex, int entryIndex)
{
	return WAD_Get(wadIndex)->entries[entryIndex].size2;
}

// <LegoRR.exe @0048bfd0>
size_t __cdecl WAD_GetEntrySize(int wadIndex, int entryIndex)
{
	return WAD_Get(wadIndex)->entries[entryIndex].size;
}

// <LegoRR.exe @0048bff0>
int __cdecl WAD_Shared__Next(void)
{
	for (int i = 0; i < SHARED_WADENTRIES_COUNT /*100*/; i++) {
		if (g_SHARED_WADENTRIES_TABLE[i].isUsed == false) {
			return i;
		}
	}
	return -1;
}

// Returns the file index found 
// Returns -1 on failure or not found.
// 
// <LegoRR.exe @0048c010>
int __cdecl WAD_FindEntry(const char* filename, int opt_wadIndex = -1)
{
	if (opt_wadIndex != -1) {
		return WAD_FindEntry__InWAD(filename, opt_wadIndex);
	}

	for (int wadIndex = WADFILES_COUNT - 1 /*10-1=9*/; wadIndex >= 0; wadIndex--) {
		if (WAD_Get(index)->isUsed == false)
			continue;
		int entryIndex = WAD_FindEntry__InWAD(filename, wadIndex);
		if (entryIndex != -1)
			return entryIndex;
	}
	return -1;
}

// Returns the file index in the specified WAD matching the reldir filepath.
// Returns -1 on failure or not found.
// 
// <LegoRR.exe @0048c060>
int __cdecl WAD_FindEntry__InWAD(const char* filename, int wadIndex)
{
	for (int j = 0; j < (int)g_WADFILES_TABLE[wadIndex].count; j++) {
		if (_stricmp(g_WADFILES_TABLE[wadIndex].reldirs[j], filename) == 0)
			return j;
	}
	return -1;
}

// Returns idx of next available LegoWADFile in table (0-9). -1 when none are available.
//
// <LegoRR.exe @0048c0c0>
int __cdecl WAD__Next(void)
{
	for (int i = 0; i < WADFILES_COUNT /*10*/; i++) {
		if (g_WADFILES_TABLE[i].isUsed == false) { // NOTE: field_4 is checked, not field_0
			// clear memory, and prepare for usage
			memset(&g_WADFILES_TABLE[i], 0, sizeof(LegoWADFile));
			return i;
		}
	}
	return -1;
}

// Reads a WAD from filename into a shared file table, and returns the index in the table
// 
// <LegoRR.exe @0048c100>
int __cdecl WAD_SharedOpen__InWAD(const char* filename, int wadIndex)
{
	int idx = WAD_Shared__Next();
	if (idx == -1)
		return -1;

	int entryIndex = WAD_FindEntry(filename, wadIndex);
	if (entryIndex == -1)
		return -1;

	size_t entrySize = WAD_GetEntrySize(wadIndex, entryIndex);
	unsigned char* buffer = (unsigned char*)malloc(entrySize);
	if (buffer == NULL)
		return -1;

	size_t entryOffset = WAD_Get(wadIndex)->entries[entryIndex].offset;
	fseek(WAD_Get(wadIndex)->file, entryOffset, 0);
	size_t entrySize = WAD_GetEntrySize(wadIndex, entryIndex);
	if (fread(buffer, entrySize, 1, WAD_Get(wadIndex)->file) != 1) {
		free(buffer);
		return -1;
	}

	unsigned char* fileData = buffer;
	if ((WAD_Get(wadIndex)->entries[entryIndex].version & 2) != 0) { // flag 0x2 == compressed???
		fileData = NULL;
		WAD_UNK_Decompress__0049ca80(buffer, &fileData);
		free(buffer); // data decompressed(?) to new buffer stored in fileData, free original buffer
	}
	g_SHARED_WADENTRIES_TABLE[idx].fileData = fileData;
	g_SHARED_WADENTRIES_TABLE[idx].isUsed = true;
	g_SHARED_WADENTRIES_TABLE[idx].wadIndex = wadIndex;
	g_SHARED_WADENTRIES_TABLE[idx].entryIndex = entryIndex;
	return idx;
}

// Reads a WAD from filename into a shared file table, and returns the index in the table.
// if opt_wadIndex is -1, all WAD files will be searched for the file name
// 
// <LegoRR.exe @0048c230>
int __cdecl WAD_SharedOpen(const char* filename, int opt_wadIndex = -1)
{
	if (opt_wadIndex != -1) {
		return WAD_SharedOpen__InWAD(filename, opt_wadIndex);
	}

	for (int wadIndex = WADFILES_COUNT - 1 /*10-1=9*/; wadIndex >= 0; wadIndex--) {
		if (WAD_Get(index)->isUsed == false)
			continue;
		int sharedIndex = WAD_SharedOpen__InWAD(filename, wadIndex);
		if (sharedIndex != -1)
			return sharedIndex;
	}
	return -1;
}

// <LegoRR.exe @0048c280>
void __cdecl WAD_Shared__Dispose(int sharedIndex)
{
	if (g_SHARED_WADENTRIES_TABLE[sharedIndex].isUsed != false) {
		free(g_SHARED_WADENTRIES_TABLE[sharedIndex].fileData);
		g_SHARED_WADENTRIES_TABLE[sharedIndex].isUsed = false;
	}
}

// <LegoRR.exe @0048c2b0>
unsigned char* __cdecl WAD_SharedGetData__internal(int sharedIndex)
{
	if (g_SHARED_WADENTRIES_TABLE[sharedIndex].isUsed != false) {
		return g_SHARED_WADENTRIES_TABLE[sharedIndex].fileData;
	}
	return NULL;
}

// <LegoRR.exe @0048c2d0>
unsigned int __cdecl WAD_SharedGetSize2(int sharedIndex)
{
	return WAD_GetEntrySize2(g_SHARED_WADENTRIES_TABLE[sharedIndex].wadIndex,
                        	 g_SHARED_WADENTRIES_TABLE[sharedIndex].entryIndex);
}

// <LegoRR.exe @0048c2f0>
unsigned char* __cdecl WAD_SharedGetData(int sharedIndex)
{
	return WAD_SharedGetData__internal(sharedIndex);
}

// Haven't really looked into this, but it's called when WADEntry.version & 0x2 flag is set... weird
// Maybe it's the SafeDisc CD DRM garbage...?
// 
// <LegoRR.exe @0049ca80>
size_t __cdecl WAD_UNK_Decompress__0049ca80(unsigned char* srcBuffer, unsigned char** out_dstBuffer)
{
	///TODO: decompile me
}

// <LegoRR.exe @0049cb00>
int __cdecl WAD_UNK_Decompress__internal__0049cb00(unsigned char* srcBuffer, unsigned char* dstBuffer)
{
	///TODO: decompile me
}


