// Files.cpp : 
//

#include "Files.h"
#include "../Helpers/Registry.h"
#include "../Helpers/Utils.h"


#pragma region Defines

#define s_Dev_SourceSafe__Files_c "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c"

#define WADFILES_COUNT 10
#define SHARED_WADENTRIES_COUNT 100
#define SHARED_FILEBUFFERS_COUNT 2000

#pragma endregion


#pragma region Globals
namespace lego {
namespace file {
namespace globals {

	// <LegoRR.exe @005349a0>
	static char g_FILEPATH_DATADIR_STRIP[1024];
	// <LegoRR.exe @00534da0>
	static char tmp_FILEPATH_STRIPDATADIR[1024];

	// <LegoRR.exe @005351a0>
	static char tmp_FILEPATH_JOINDATADIR[MAX_PATH /*260*/];
	// <LegoRR.exe @005352a8>
	static char g_FILEPATH_DATADIR_JOIN[MAX_PATH /*260*/];

	// no clue on these two value yet... (maybe actually SafeDisc DRM stuff?)
	// <LegoRR.exe @005353ac>
	static FileOpenCallback g_FileOpenCallback;
	// <LegoRR.exe @005353b0>
	static void* g_FileOpenCallback_CONTEXT;

	// <LegoRR.exe @005353b4>
	static char g_CDROM_DriveLetter;

	// <LegoRR.exe @005353b8>
	static BOOL g_HAS_DATADIR;

	// <LegoRR.exe @005353c0>
	// not used??

	// <LegoRR.exe @005353c4>
	static void* g_UNKPTR_STRUCT48__005353c4;

	// <LegoRR.exe @00545a20 to 005498a0>
	static SharedFileBuffer g_SHARED_FILEBUFFERS_TABLE[SHARED_FILEBUFFERS_COUNT /*2000*/];

	// <LegoRR.exe @005766a0>
	static SharedWADEntry g_SHARED_WADENTRIES_TABLE[SHARED_WADENTRIES_COUNT /*100*/]; // isn't this too small???

	// <LegoRR.exe @00576500>
	static WADFile g_WADFILES_TABLE[WADFILES_COUNT /*10*/];

	// <LegoRR.exe @00576ce0>
	static FileStream* g_ScanFileStream_1;
	// <LegoRR.exe @00576ce4>
	static FileStream* g_ScanFileStream_2;
	// <LegoRR.exe @00576ce8>
	static FileStream* g_ScanFileStream_3;
	// <LegoRR.exe @00576cec>
	static FileStream* g_ScanFileStream_OutputList;
	// <LegoRR.exe @00576cf0>
	static char g_ScanFilename_InputList[1024];
	// <LegoRR.exe @005770f0>
	static char g_ScanFilename_OutputList[1024];

	// <LegoRR.exe @005779e0>
	static char g_ScanRealFiles_FilePaths_TABLE[2000][1024];
	// <LegoRR.exe @0076b9e0>
	static unsigned int g_ScanRealFiles_FilePaths_COUNT;

	// <LegoRR.exe @005774f4>
	static BOOL g_ScanIsFullScreen;

	#pragma region /// CONSTANTS ////////////////////////////

	// <LegoRR.exe @004abf00>
	static const int c_WAD_ANYINDEX = -1; // constant that states WAD entry lookup will check every WAD file

	#pragma endregion

} /* namespace globals */
} /* namespace file */
} /* namespace lego */
#pragma endregion


using namespace lego::file;


#pragma region Functions

// gamename may actually be gamepath (as called from the commandline arguments)
// 
// <LegoRR.exe @0047f3f0>
void __cdecl lego::file::InitFileSystem(const char* gameName, BOOL insistOnCD, const char* regKey)
{
	char currentDir[MAX_PATH /*260*/];
	char dataDir[MAX_PATH /*260*/];
	char wadFile[MAX_PATH /*260*/];
	char errorMessage[1024];
	char cdkeyFile[1024];
	char regValue[1024];


	// assign one of our too Data directory globals...
	_getcwd(currentDir, sizeof(currentDir) /*260*/);

	// The Ghidra decompilation for this was so messed up...
	//  (`currentDir[0] != '\0'` added to circumvent stack safefty jank)
	size_t currentLen = std::strlen(currentDir);
	if (currentLen != 0 && currentDir[currentLen - 1] == '\\') {
		currentDir[currentLen - 1] = '\0';
	}
	std::sprintf(globals::g_FILEPATH_DATADIR_JOIN, "%s\\%s", currentDir, "Data");


	// check for WAD files 0-9
	BOOL hasWADs = FALSE;
	for (int i = 0; i < WADFILES_COUNT /*10*/; i++) {
		std::sprintf(wadFile, "%s%i.wad", gameName, i);
		if (WAD_Open(wadFile) != -1) { // -1 returned for no WAD index (index does not correspond to file number)
			hasWADs = TRUE;
		}
	}


	// assign the other one of our Data directory globals...
	_getcwd(dataDir, sizeof(dataDir));
	std::strcat(dataDir, "\\Data");
	Path_SetDataDir(dataDir);


	// If no CD and game is hungry for CD...
	// loop until user inserts CD and CD is detected,
	//  or until user accepts their fate and presses OK on message box to exit

	BOOL hasCDROM = Path_CheckForCDROM();
#ifndef DEBUG_IGNORECD
	while (!hasCDROM && insistOnCD) {
		std::memset(errorMessage, 0, sizeof(errorMessage));
		std::strcpy(errorMessage, "Error");

		if (!registry::QueryString_FromLocalMachine(regKey, "CDMissing", 0, regValue, sizeof(regValue))) {
			// LAB_0047f59b:
			std::exit(0);
		}
		else {
			registry::QueryString_FromLocalMachine(regKey, "SetupError", 0, errorMessage, sizeof(errorMessage));
			if (MessageBoxA(nullptr, regValue, errorMessage, MB_OKCANCEL /*1*/) == IDCANCEL /*2*/)
				std::exit(0); // exit once the user decides to cancel, otherwise rinse and repeat
		}
		hasCDROM = Path_CheckForCDROM();
	}
#endif

	// no WAD files, find Data directory
	BOOL missingData = FALSE;
	if (!hasCDROM && !hasWADs) {
		missingData = TRUE;
		_finddata32_t fileinfo; // local_e1c
		intptr_t handle = _findfirst32("*.*", &fileinfo);
		if (handle != -1) { // -1 for failure
			do {
				if ((fileinfo.attrib & FILE_ATTRIBUTE_DIRECTORY) && _stricmp(fileinfo.name, "Data") == 0) {
					missingData = FALSE; // data dir found??
					break;
				}
			} while (_findnext32(handle, &fileinfo) == 0);
			_findclose(handle);
		}
	}

	// What the hell is this doing??
	if (insistOnCD) {
		std::sprintf(cdkeyFile, "%s\\%s", "Data", "cd.key");
		FILE* file = std::fopen(cdkeyFile, "r");
		if (file != nullptr) {
			std::fclose(file);
			missingData = TRUE; // has CD?? what....???
		}
	}

	// "delme.dat"
	if (!missingData) { // no CD, and no Data dir?
		_mkdir("Data"); // create Data dir
		std::sprintf(cdkeyFile, "%s\\%s", "Data", "delme.dat");
		FILE* file = std::fopen(cdkeyFile, "r");
		if (file != nullptr) { // data dir must have already existed???
			std::fclose(file);
			_chmod(cdkeyFile, FILE_ATTRIBUTE_NORMAL /*0x80*/);
			std::remove(cdkeyFile);
			return;
		}
		// regardless, after this the function finishes successfully
	}
	else {
		std::memset(errorMessage, 0, sizeof(errorMessage));
		std::strcpy(errorMessage, "Error");

		if (registry::QueryValueOnLocalMachine(regKey, "DataMissing", registry::REGISTRY_STRING /*0*/, regValue, sizeof(regValue))) {
			registry::QueryValueOnLocalMachine(regKey, "SetupError", registry::REGISTRY_STRING /*0*/, errorMessage, sizeof(errorMessage));
			MessageBoxA(nullptr, regValue, errorMessage, MB_OK /*0*/);
		}
		std::exit(0);
	}
}

// Checks for a currently-inserted CDROM drive containing the file "CDROM:\Data\cd.key"
// Does not actually check contents of the file.
// Returns true when found, and assigns global: char g_CDROM_DriveLetter;
// 
// <LegoRR.exe @0047f7b0>
BOOL __cdecl lego::file::Path_CheckForCDROM(void)
{
#ifndef DEBUG_IGNORECD
	char buffer[MAX_PATH /*260*/];
	char rootName[4] = { 'A', ':', '\\', '\0' }; //"A:\\";

	// iterate through all drive letters to find CDROM drive types.
	//  (besides 'A','B' which are reserved for floppies)
	for (char letter = 'C'; letter <= 'Z'; letter++) {
		rootName[0] = letter;
		if (GetDriveTypeA(rootName) == DRIVE_CDROM /*5*/) {
			// confirm this CDROM drive has the file "CDROM:\Data\cd.key"
			std::sprintf(buffer, "%c:\\%s\\%s", letter, "Data", "cd.key");
			FILE* file = std::fopen(buffer, "r");
			if (file != nullptr) {
				std::fclose(file);
				globals::g_CDROM_DriveLetter = letter; // assign drive letter, for later use
				return TRUE;
			}
		}
	}
#endif
	return FALSE;
}

// <LegoRR.exe @0047f850>
BOOL __cdecl lego::file::Path_SetDataDir(const char* dirname)
{
	if (dirname != nullptr) {
		size_t strLength = strlen(dirname);
		if (strLength < sizeof(globals::g_FILEPATH_DATADIR_STRIP) && strLength != 0) {
			std::strcpy(globals::g_FILEPATH_DATADIR_STRIP, dirname);
			globals::g_HAS_DATADIR = TRUE;
			return TRUE;
		}
	}
	globals::g_HAS_DATADIR = FALSE;
	std::memset(globals::g_FILEPATH_DATADIR_STRIP, 0, sizeof(globals::g_FILEPATH_DATADIR_STRIP));
	return FALSE;
}


// Open WAD filename and log something (that was removed on release build)
// returns idx of newly opened WAD (0-9), or -1 on failure of any kind.
//
// <LegoRR.exe @0047f900>
int __cdecl lego::file::WAD_Open(const char* filename)
{
	//lego::logf_removed(nullptr);
	return WAD_Open__internal(filename);
}

// <LegoRR.exe @0047f920>
BOOL __cdecl lego::file::Path_GetCDROMDataPath(char* out_filepath, const char* filename)
{
#ifndef DEBUG_IGNORECD
	if (globals::g_CDROM_DriveLetter != '\0') {
		std::sprintf(out_filepath, "%c:\\%s\\%s", globals::g_CDROM_DriveLetter, "Data", filename);
		return TRUE;
	}
#endif
	return FALSE;
}

// <LegoRR.exe @0047f960>
int __cdecl lego::file::Path_MakeDataSubdir(const char* dirname)
{
	char buffer[MAX_PATH /*260*/];

	std::sprintf(buffer, "%s\\%s", "Data", dirname);
	return _mkdir(buffer);
}


// <LegoRR.exe @0047f9a0>
FileStream* __cdecl lego::file::File_Open(const char* in_filename, const char* mode)
{
	char buffer[MAX_PATH /*260*/];

	const char* message;
	const char* filename = Path_JoinDataDir(in_filename);
	FileLocation location = File_FindLocation(filename, mode);

	FileStream* fileStream;
	if (location == FILELOC_WAD /*0*/) {
		fileStream = File__New(FILELOC_WAD /*0*/);
		if (fileStream == nullptr)
			return nullptr;

		message = Path_StripDataDir(filename);
		if (WAD_EntryOpen__internal(fileStream->wad, message)) {
			filename = Path_StripDataDir(filename);
			//lego::logf_removed("WAD Load %s\n", filename);
			return fileStream;
		}
		filename = Path_StripDataDir(filename);
		message = "WAD Fail %s\n";
	}
	else if (location == FILELOC_STD /*1*/) {
		fileStream = File__New(FILELOC_STD /*1*/);
		if (fileStream == nullptr)
			return nullptr;

		FILE* stdFile = std::fopen(filename, mode);
		fileStream->std = stdFile;
		if (stdFile != nullptr) {
			//lego::logf_removed("STD Load %s\n", filename);
			return fileStream;
		}

		// file not found in datadir, check CDROM (and enforce readonly)
		const char* modeMatch = lego::util::strstri(mode, "w");
		if (modeMatch == nullptr && Path_GetCDROMDataPath(buffer, in_filename)) {
			stdFile = std::fopen(buffer, mode);
			fileStream->std = stdFile;
			if (stdFile != nullptr)
				return fileStream;
		}
		message = "STD Fail %s\n";
	}
	else {
		
		debugf("%s(%i) : Error in call to %s\n", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 330 /*__LINE__*/, "File_Open");
		return nullptr;
	}
	//lego::logf_removed(message, filename);
	File__Dispose(fileStream);
	return nullptr;
}

// <LegoRR.exe @0047fb10>
int __cdecl lego::file::File_Seek(FileStream* file, long int offset, int origin)
{
	FileLocation location = File_GetLocation(file);
	if (location == FILELOC_WAD /*0*/) {
		switch (origin) {
		case SEEK_SET /*0*/:
			file->wad->position = offset;
			break; // do bounds checks after switch statement

		case SEEK_CUR /*1*/:
			file->wad->position += offset;
			break; // do bounds checks after switch statement

		case SEEK_END /*2*/:
			file->wad->position = (int)WAD_SharedGetSize(file->wad->sharedIndex) + offset;
			return 0; // no bounds checks here...

		default:
			// type is accurate :P
			debugf("Uknown seek mode (%i)", origin);
			return 0;
		}
		// bounds checks
		if (file->wad->position > (int)WAD_SharedGetSize(file->wad->sharedIndex))
			file->wad->position = WAD_SharedGetSize(file->wad->sharedIndex);
		else if (file->wad->position < 0)
			file->wad->position = 0;
		// despite what you'd think, this always returns 0 for WADs, but the EAX result register is clearly set...
		return 0;
	}
	else if (location == FILELOC_STD /*1*/) {
		return std::fseek(file->std, offset, origin);
	}
	else {
		debugf("%s(%i) : Unknown file system in call to %s", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 368 /*__LINE__*/, "File_Seek");
		return 0;
	}
}

// <LegoRR.exe @0047fc40>
size_t __cdecl lego::file::File_Read(void* out_ptr, size_t size, size_t count, FileStream* file)
{
	FileLocation location = File_GetLocation(file);
	if (location == FILELOC_WAD /*0*/) {
		size_t fileSize = (int)WAD_SharedGetSize(file->wad->sharedIndex);
		size_t readSize = count * size;
		int position = file->wad->position;
		if ((int)fileSize < (position + readSize))
			readSize = fileSize - position;
		unsigned char* fileData = WAD_SharedGetData(file->wad->sharedIndex);
		std::memcpy(out_ptr, (fileData + file->wad->position), readSize);
		file->wad->position += readSize;
		return (int)readSize / (int)size; // (partial element size reads may occur)
	}
	else if (location == FILELOC_STD /*1*/) {
		return std::fread(out_ptr, size, count, file->std);
	}
	else {
		debugf("%s(%i) : Unknown file system in call to %s", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 395 /*__LINE__*/, ""/*EMPTYSTR*/);
		return 0;
	}
}

// <LegoRR.exe @0047fd10>
size_t __cdecl lego::file::File_Write(const void* ptr, size_t size, size_t count, FileStream* file)
{
	FileLocation location = File_GetLocation(file);
	if (location == FILELOC_WAD /*0*/) {
		debugf("Cannot write to a file stored in a Wad!");
		return 0;
	}
	if (location == FILELOC_STD /*1*/) {
		return std::fwrite(ptr, size, count, file->std);
	}
	else {
		debugf("%s(%i) : Unknown file system in call to %s", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 414 /*__LINE__*/, "File_Write");
		return 0;
	}
}

// <LegoRR.exe @0047fd80>
int __cdecl lego::file::File_Close(FileStream* file)
{
	FileLocation location = File_GetLocation(file);
	if (location >= 0 && location < 2) { // == FILELOC_WAD || == FILELOC_REAL
		File__Dispose(file);
		return 0;
	}
	debugf("%s(%i) : Unknown file system in call to %s", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 431 /*__LINE__*/, "File_Close");
	return 0;
}

// <LegoRR.exe @0047fdd0>
long int __cdecl lego::file::File_Tell(FileStream* file)
{
	FileLocation location = File_GetLocation(file);
	if (location == FILELOC_WAD /*0*/) {
		return (long int)file->wad->position;
		// return *(int *)(file->stream + 4);
	}
	if (location == FILELOC_STD /*1*/) {
		return std::ftell(file->std);
	}
	debugf("%s(%i) : Unknown file system in call to %s", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 469 /*__LINE__*/, "File_Tell");
	return 0;
}

// <LegoRR.exe @0047fe20>
BOOL __cdecl lego::file::File_Exist(const char* filename)
{
	char buffer[MAX_PATH /*260*/];

	const char* dataFilename = Path_JoinDataDir(filename);
	FileLocation location = File_FindLocation(dataFilename, "r");
	if (location == FILELOC_WAD /*0*/) {
		// brilliant! This fails regardless because the data directory wasn't stripped before calling this...
		// this is really dumb, invalid values from this return -1, and valids values can be 0.
		return WAD_FindEntry(dataFilename, globals::c_WAD_ANYINDEX /*-1*/);
	}
	else if (location == FILELOC_STD /*1*/) {
		// check Data dir path
		FILE* file = std::fopen(dataFilename, "r");
		if (file != nullptr) {
			std::fclose(file);
			return TRUE;
		}

		// check CDROM path
		if (Path_GetCDROMDataPath(buffer, filename)) {
			file = std::fopen(buffer, "r");
			if (file != nullptr) {
				std::fclose(file);
				return TRUE;
			}
		}
	}
	return FALSE; // meanwhile we return 0 here on failure... GAHHH
}

// <LegoRR.exe @0047fee0>
int __cdecl lego::file::File_GetC(FileStream* file)
{
	FileLocation location = File_GetLocation(file);
	if (location == FILELOC_WAD /*0*/) {
		if ((int)(WAD_SharedGetSize(file->wad->sharedIndex) - 1) <= file->wad->position)
			return -1; // end of stream

		unsigned char* fileData = WAD_SharedGetData(file->wad->sharedIndex);
		return fileData[file->wad->position++];
	}
	else if (location == FILELOC_STD /*1*/) {
		return std::fgetc(file->std);
	}
	else {
		debugf("%s(%i) : Unknown file system in call to %s", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 545 /*__LINE__*/, "File_GetC");
		return 0;
	}
}

// <LegoRR.exe @0047ff60>
long int __cdecl lego::file::File_GetLength(FileStream* file)
{
	int origOffset = File_Tell(file);
	File_Seek(file, 0, SEEK_END /*2*/);
	long int length = File_Tell(file);
	File_Seek(file, origOffset, SEEK_SET /*0*/);
	return length;
}

// <LegoRR.exe @0047ffa0>
char* __cdecl lego::file::WAD_GetS__internal(char* out_str, int num, FileStream* file)
{
	int length = 0;
	char c = (char)File_GetC(file);
	out_str[0] = c;
	// the out_str[length] != -1 is actually checking the int return from File_GetC,
	//  but it will prevent usage of byte 0xff in any locales with multibyte character encodings.
	while (c != '\0' && out_str[length] != '\n' && out_str[length] != -1 && length != num) { // negative num value for INSTANT memory corruption :)
		c = (char)File_GetC(file);
		out_str[++length] = c;
	}
	// an explanation on the weird length incrementing
	// this ALWAYS puts a minimum of one character into the buffer (but this may be a bug)
	// this does not respect the argument num :)
	out_str[length + 1] = '\0';
	return (length != 0 ? out_str : nullptr);
}

// <LegoRR.exe @00480000>
char* __cdecl lego::file::File_GetS(char* out_str, int num, FileStream* file)
{
	FileLocation location = File_GetLocation(file);
	if (location == FILELOC_WAD /*0*/) {
		return WAD_GetS__internal(out_str, num, file);
	}
	else if (location != FILELOC_STD /*1*/) {
		return std::fgets(out_str, num, file->std);
	}
	else {
		debugf("%s(%i) : Unknown file system in call to %s", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 587 /*__LINE__*/, "File_GetS");
		return nullptr;
	}
}

// <LegoRR.exe @00480070>
int __cdecl lego::file::File_PrintF(FileStream* file, const char* format, ...)
{
	FileLocation location = File_GetLocation(file);
	if (location == FILELOC_WAD /*0*/) {
		debugf("\"fprintf\" is unsupprted for wad files");
		return 0;
	}
	else if (location == FILELOC_STD /*1*/) {
		va_list vl;
		va_start(vl, format);
		std::vfprintf(file->std, format, vl);
		//FUN_00490190(file->std, format, (undefined4*)&stack0x0000000c);
		va_end(vl);
		return 0;
	}
	else {
		debugf("%s(%i) : Unknown file system in call to %s", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 612 /*__LINE__*/, "File_PrintF");
		return 0;
	}
}

// <LegoRR.exe @004800e0>
FileLocation __cdecl lego::file::File_GetLocation(FileStream* file)
{
	return file->location;
}

// Returns 0 if file is found in WAD
// Returns 1 if arguments are valid.
// Otherwise, returns 2.
// 
// <LegoRR.exe @004800f0>
FileLocation __cdecl lego::file::File_FindLocation(const char* filename, const char* mode)
{
	if (filename != nullptr && mode != nullptr && std::strlen(filename) != 0 && std::strlen(mode) != 0) {
		if (*mode != 'w' && *mode != 'W') { // only check for WAD entries with read mode
			filename = Path_StripDataDir(filename);
			int entryIndex = WAD_FindEntry(filename, globals::c_WAD_ANYINDEX /*-1*/);
			if (entryIndex != -1)
				return FILELOC_WAD /*0*/;
		}
		return FILELOC_STD /*1*/; // as long as the arguments were valid, return STD
	}
	return FILELOC_ERROR /*2*/; //BOOL3_ERROR;
}

// <LegoRR.exe @00480160>
BOOL __cdecl lego::file::WAD_EntryOpen__internal(WADEntryStream* wadStream, const char* filename)
{
	wadStream->field_8 = 0;
	wadStream->position = 0;
	int sharedIndex = WAD_SharedOpen(filename, globals::c_WAD_ANYINDEX /*-1*/);
	wadStream->sharedIndex = sharedIndex;
	return (sharedIndex != -1);
}

// <LegoRR.exe @00480190>
FileStream* __cdecl lego::file::File__New(FileLocation location)
{
	if (location == FILELOC_WAD /*0*/) {
		FileStream* file = (FileStream*)File__New__alloc(sizeof(FileStream) /*8*/);
		if (file != nullptr) {
			file->location = FILELOC_WAD /*0*/;

			WADEntryStream* wadFile = (WADEntryStream*)File__New__alloc(sizeof(WADEntryStream) /*0xc*/);
			file->wad = wadFile;
			if (wadFile != nullptr) {
				return file;
			}
			File__New__free(file);
		}
	}
	else if (location == FILELOC_STD /*1*/) {
		FileStream* file = (FileStream*)File__New__alloc(sizeof(FileStream) /*8*/);
		// SANITY: no null check here... heh
		file->location = FILELOC_STD /*1*/;
		return file;
	}
	return nullptr;
}

// <LegoRR.exe @004801f0>
void* __cdecl lego::file::File__New__alloc(size_t size)
{
	return std::malloc(size);
}

// <LegoRR.exe @00480200>
void __cdecl lego::file::File__New__free(void* ptr)
{
	std::free(ptr);
}

// <LegoRR.exe @00480210>
void __cdecl lego::file::File__Dispose(FileStream* file)
{
	if (file != nullptr) {
		FileLocation location = File_GetLocation(file);
		if (location == FILELOC_WAD /*0*/) {
			if (file->wad != nullptr) {
				WAD_Shared__Dispose(file->wad->sharedIndex);
				File__New__free(file->wad);
			}
			File__New__free(file);
		}
		else if (location == FILELOC_STD /*1*/) {
			if (file->std != nullptr) {
				std::fclose(file->std);
			}
			File__New__free(file);
		}
	}
}


// Strips the Data directory from the filename path, using global g_FILEPATH_DATADIR_1 as a comparison.
// Returns a temporary buffer that must be used before this function is next called.
// 
// <LegoRR.exe @00480280>
const char* __cdecl lego::file::Path_StripDataDir(const char* filename)
{
	if (!globals::g_HAS_DATADIR)
		return filename;

	int datadirLen = (int)std::strlen(globals::g_FILEPATH_DATADIR_STRIP);
	if ((int)std::strlen(filename) <= datadirLen) // shorter than DATADIR, can't start with datadir
		return filename;

	char c = filename[datadirLen]; // backup original char here (which *should* be path separator, but could potentially be something else)
	const_cast<char*>(filename)[datadirLen] = '\0';   // then replace that char with null-terminator
	if (_stricmp(filename, globals::g_FILEPATH_DATADIR_STRIP) == 0) { // compare filename and datadir (could be replaced with strnicmp)
		std::sprintf(globals::tmp_FILEPATH_STRIPDATADIR, "%s", filename + datadirLen + 1);
		const_cast<char*>(filename)[datadirLen] = c; // restore char
		return globals::tmp_FILEPATH_STRIPDATADIR;
	}
	const_cast<char*>(filename)[datadirLen] = c; // restore char
	return filename;
}

// all parameters are directly passed to File_GetS, then some operation on string is performed
// 
// <LegoRR.exe @00480310>
char* __cdecl lego::file::File_GetS_StripLineEnd(char* out_str, int num, FileStream* file)
{
	char* result = File_GetS(out_str, num, file);
	// generally File_GetS should return at least one character, but these are some dangurous assumptions?
	int len = (int)std::strlen(out_str);

	if (out_str[len - 1] == '\0')
		out_str[len - 1] = '\0'; // strip LF

	if ((len - 1) != 0 && out_str[len - 2] == '\r')
		out_str[len - 2] = '\0'; // strip CRLF (regardless if last char is LF)

	return result;
}

// <LegoRR.exe @00480360>
unsigned char* __cdecl lego::file::File_ReadAllBytes(const char* filename, unsigned int* out_length)
{
	return File_ReadAll(filename, out_length, TRUE /*isBinary*/);
}

// <LegoRR.exe @00480380>
unsigned char* __cdecl lego::file::File_ReadAll(const char* filename, unsigned int* out_length, BOOL isBinary)
{
	FileStream* file = File_Open(filename, isBinary ? "rb" : "r");
	if (file != nullptr) {
		File_Seek(file, 0, SEEK_END /*2*/);
		int length = File_Tell(file);

		if (globals::g_FileOpenCallback != nullptr)
			globals::g_FileOpenCallback(filename, length, globals::g_FileOpenCallback_CONTEXT);

		unsigned char* buffer = (unsigned char*)std::malloc(length);
		if (buffer != nullptr) {
			File_Seek(file, 0, SEEK_SET /*0*/);
			File_Read(buffer, 1, length, file);
			if (out_length != nullptr) {
				*out_length = length;
			}
		}
		File_Close(file);
		return buffer;
	}
	return nullptr;
}

// <LegoRR.exe @00480430>
int __cdecl lego::file::File_SharedOpen(const char* filename, size_t* out_length)
{
	FileStream* file = File_Open(filename, "rb");
	if (file != nullptr) {
		File_Seek(file, 0, SEEK_END /*2*/);
		size_t length = File_Tell(file);

		if (globals::g_FileOpenCallback != nullptr)
			globals::g_FileOpenCallback(filename, length, globals::g_FileOpenCallback_CONTEXT);

		int sharedIndex = File_SharedOpen__internal(length);
		if (sharedIndex != -1) {
			void* out_buffer = File_SharedGetData(sharedIndex);
			File_Seek(file, 0, SEEK_SET /*0*/);
			File_Read(out_buffer, 1, length, file);
			if (out_length != nullptr) {
				*out_length = length;
			}

			File_Close(file);
			return sharedIndex;
		}
		File_Close(file);
	}
	return -1;
}

// Join filename path with global g_FILEPATH_DATADIR_2.
// Returns a temporary buffer that must be used before this function is next called.
// 
// <LegoRR.exe @004804e0>
const char* __cdecl lego::file::Path_JoinDataDir(const char* filename)
{
	char buffer[MAX_PATH /*260*/];

	if (filename != nullptr) {
		if (*filename == '\\')
			filename++;

		std::sprintf(buffer, "%s\\%s", globals::g_FILEPATH_DATADIR_JOIN, filename);
		if (_fullpath(globals::tmp_FILEPATH_JOINDATADIR, buffer, MAX_PATH /*260*/) != nullptr) {

			if (std::strncmp(globals::tmp_FILEPATH_JOINDATADIR, globals::g_FILEPATH_DATADIR_JOIN, std::strlen(globals::g_FILEPATH_DATADIR_JOIN)) == 0) {
				return globals::tmp_FILEPATH_JOINDATADIR;
			}
		}
	}
	return nullptr;
}

// <LegoRR.exe @00480570>
void __cdecl lego::file::File_SetOpenCallback(FileOpenCallback callback, void* lpContext)
{
	globals::g_FileOpenCallback = callback;
	globals::g_FileOpenCallback_CONTEXT = lpContext;
}

// <LegoRR.exe @00480590>
void __cdecl lego::file::Scan_ReadDataDirList(const char* filename)
{
	/*char cVar1;
	FILE* file;
	int iVar2;
	uint uVar3;
	uint uVar4;
	undefined4* puVar5;
	char* pcVar6;
	char* pcVar7;
	char(*pacVar8)[1024];*/
	char buffer[1024];

	FileStream* file = File_Open(filename, "r");
	if (file == nullptr)
		return;

	if (file != nullptr) {
		globals::g_ScanRealFiles_FilePaths_COUNT = 0;
		int scanLength = std::fscanf((FILE*)file, "%s", buffer); // what...!???
		while (scanLength != -1) {
			char* filepath = globals::g_ScanRealFiles_FilePaths_TABLE[globals::g_ScanRealFiles_FilePaths_COUNT];
			globals::g_ScanRealFiles_FilePaths_COUNT++;
			std::strcpy(filepath, buffer);

			scanLength = std::fscanf((FILE*)file, "%s", buffer); // This really isn't how it works!, FILE* is at FileStream: offset 0x4!!!!
		}
		Scan_Directory(globals::g_FILEPATH_DATADIR_JOIN);
		std::fclose((FILE*)file); // what the hell.....
	}
}
// <LegoRR.exe @00480650>
void __cdecl lego::file::Scan_Directory(const char* dirname)
{
	char buffer[1024];

	strcpy(buffer, dirname);
	strcat(buffer, "\\*.*");

	_finddata32_t finddata;
	intptr_t handle = _findfirst32(buffer, &finddata);
	if (handle != -1) {
		do {
			if (strcmp(finddata.name, ".") != 0 && strcmp(finddata.name, "..") != 0) {
				strcpy(buffer, dirname);
				strcat(buffer, "\\");
			}

			if (!(finddata.attrib & FILE_ATTRIBUTE_DIRECTORY /*0x10*/)) {
				Scan_File(buffer); // an actual file
			}
			else {
				Scan_Directory(buffer); // a directory, recurse with this function
			}
		} while (_findnext32(handle, &finddata) == 0);
		_findclose(handle);
	}
}

// Chances are high that there was a preprocessor-removed functionality in here.
// This straight up does nothing, because not even the return is used.
// <LegoRR.exe @00480830>
int __cdecl lego::file::Scan_File(const char* filename)
{
	for (unsigned int i = 0; i < globals::g_ScanRealFiles_FilePaths_COUNT; i++) {
		if (_stricmp(filename, globals::g_ScanRealFiles_FilePaths_TABLE[i]) == 0)
			return 0;
	}
	return (int)globals::g_ScanRealFiles_FilePaths_COUNT;
}

// called in one of the LegoRR main initialization functions <LegoRR.exe @00477a60>
// 
// <LegoRR.exe @004896b0>
void __cdecl lego::file::InitSharedFileBuffers(void)
{
	for (int i = 0; i < SHARED_FILEBUFFERS_COUNT; i++) {
		globals::g_SHARED_FILEBUFFERS_TABLE[i].fileData = nullptr;
		globals::g_SHARED_FILEBUFFERS_TABLE[i].flags = (FileBufferFlags)0;
	}
}

// <LegoRR.exe @004896d0>
int __cdecl lego::file::File_SharedOpen__internal(size_t size)
{
	for (int i = 0; i < SHARED_FILEBUFFERS_COUNT; i++) {
		if (!(globals::g_SHARED_FILEBUFFERS_TABLE[i].flags & FILEBUFFER_ISUSED)) { // not isUsed
			void* buffer = std::malloc(size);
			globals::g_SHARED_FILEBUFFERS_TABLE[i].fileData = buffer;
			globals::g_SHARED_FILEBUFFERS_TABLE[i].flags |= FILEBUFFER_ISUSED; // isUsed
			return i;
		}
	}
	return -1;
}

// <LegoRR.exe @00489720>
void __cdecl lego::file::File_SharedClose(int sharedIndex)
{
	unsigned int i = (unsigned int)sharedIndex;
	if ((unsigned int)i < SHARED_FILEBUFFERS_COUNT && (globals::g_SHARED_FILEBUFFERS_TABLE[i].flags & FILEBUFFER_ISUSED)) { // isUsed
		std::free(globals::g_SHARED_FILEBUFFERS_TABLE[i].fileData);
		globals::g_SHARED_FILEBUFFERS_TABLE[i].fileData = nullptr;
		globals::g_SHARED_FILEBUFFERS_TABLE[i].flags = (FileBufferFlags)0; // not isUsed
	}
}

// <LegoRR.exe @00489760>
unsigned char* __cdecl lego::file::File_SharedGetData(int sharedIndex)
{
	unsigned int i = (unsigned int)sharedIndex;
	if ((unsigned int)i < SHARED_FILEBUFFERS_COUNT && (globals::g_SHARED_FILEBUFFERS_TABLE[i].flags & FILEBUFFER_ISUSED)) { // isUsed
		return (unsigned char*)globals::g_SHARED_FILEBUFFERS_TABLE[i].fileData;
	}
	return nullptr;
}


// <LegoRR.exe @0048b520>
void __cdecl lego::file::InitFileScanning(void)
{
	globals::g_ScanFileStream_1 = nullptr;
	globals::g_ScanFileStream_2 = nullptr;
	globals::g_ScanFileStream_3 = nullptr;
	globals::g_ScanFileStream_OutputList = nullptr;
	globals::g_ScanIsFullScreen = FALSE;
}

// <LegoRR.exe @0048b540>
void __cdecl lego::file::Scan_SetIsFullScreen(BOOL isFullScreen)
{
	globals::g_ScanIsFullScreen = isFullScreen;
}

// <LegoRR.exe @0048b550>
void __cdecl lego::file::Scan_Cleanup(void)
{
	if (globals::g_ScanFileStream_1 != nullptr)
		File_Close(globals::g_ScanFileStream_1);

	if (globals::g_ScanFileStream_2 != nullptr)
		File_Close(globals::g_ScanFileStream_2);

	if (globals::g_ScanFileStream_3 != nullptr)
		File_Close(globals::g_ScanFileStream_3);

	globals::g_ScanFileStream_1 = nullptr;
	globals::g_ScanFileStream_2 = nullptr;
	globals::g_ScanFileStream_3 = nullptr;
}

// <LegoRR.exe @0048b5b0>
void __cdecl lego::file::Scan_WriteDataDirList(void)
{
	Scan_Cleanup();

	globals::g_ScanFileStream_OutputList = File_Open(globals::g_ScanFilename_OutputList, "w");
	if (globals::g_ScanFileStream_OutputList != nullptr) {
		Scan_ReadDataDirList(globals::g_ScanFilename_InputList);
		File_Close(globals::g_ScanFileStream_OutputList);
	}
}


// Open and read data into WAD file.
// returns idx of newly opened WAD (0-9), or -1 on failure of any kind.
// 
// <LegoRR.exe @0048b7a0>
int __cdecl lego::file::WAD_Open__internal(const char* filename)
{
	char signature[4];
	FILE* file;
	int idx = WAD__Next(); // prepare and get next available WAD index
	if (idx == -1) {
		// FAIL: no more WAD files to load (max 10 can be loaded at once)
		goto WADOpen_end;
	}

	file = std::fopen(filename, "rb");
	WAD_Get(idx)->file = file;
	if (file == nullptr) {
		// FAIL: could not open WAD file
		goto WADOpen_end;
	}

	WAD_Get(idx)->isUsed = TRUE;


	// signature check "WWAD"
	if (std::fread(signature, 1, 4, file) != 4 || std::memcmp(signature, "WWAD", 4) != 0) {
		// FAIL: could not read file signature, or signature did not match "WWAD"
		goto WADOpen_close;
	}

	// read number of file entries
	if (std::fread(&WAD_Get(idx)->count, 1, 4, file) != 4) {
		// FAIL: could not read file entry count
		goto WADOpen_close;
	}

	// allocate buffers to store relative and absolute entry file paths
	WAD_Get(idx)->reldirs = (char**)std::malloc(WAD_Get(idx)->count * sizeof(char*)); // count * 4 (probably for pointers)
	WAD_Get(idx)->absdirs = (char**)std::malloc(WAD_Get(idx)->count * sizeof(char*)); // count * 4 (probably for pointers)
	if (WAD_Get(idx)->reldirs == nullptr || WAD_Get(idx)->absdirs == nullptr) {
		// FAIL: could not allocate reldirs or absdirs buffers
		goto WADOpen_allocs;
	}

	// zero out memory, so that, on failure, we don't try to free strings that haven't yet been allocated
	std::memset(WAD_Get(idx)->reldirs, 0, WAD_Get(idx)->count * sizeof(char*)); // count * 4
	std::memset(WAD_Get(idx)->absdirs, 0, WAD_Get(idx)->count * sizeof(char*)); // count * 4

	char strBuffer[4096]; // temp buffer used for reading C-String reldirs/absdirs one-by-one

	// read WAD file relative directories
	for (int i = 0; i < (int)WAD_Get(idx)->count; i++) {
		if (!lego::util::freadstr(file, strBuffer)) {
			// FAIL: could not read cstring
			// although freadstr never returns false...
			goto WADOpen_reldirs;
		}

		WAD_Get(idx)->reldirs[i] = _strdup(strBuffer);
		debugf("%s\n", WAD_Get(idx)->reldirs[i]);
	}

	// read WAD file absolute directories
	for (int i = 0; i < (int)WAD_Get(idx)->count; i++) {
		if (!lego::util::freadstr(file, strBuffer)) {
			// FAIL: could not read cstring
			// although freadstr never returns false...
			goto WADOpen_absdirs;
		}

		WAD_Get(idx)->absdirs[i] = _strdup(strBuffer);
		debugf("%s\n", WAD_Get(idx)->absdirs[i]);
	}

	// read WAD file entry metadata
	WAD_Get(idx)->entries = (WADEntry*)std::malloc(WAD_Get(idx)->count * sizeof(WADEntry)); // count * 4
	if (WAD_Get(idx)->entries == nullptr) {
		// FAIL: could not allocate entries buffer
		goto WADOpen_absdirs;
	}

	// read in entry data directly from file into entries buffer
	if (std::fread(WAD_Get(idx)->entries, 1, WAD_Get(idx)->count * sizeof(WADEntry), file) // count * 16
		== (WAD_Get(idx)->count * sizeof(WADEntry))) // count * 16
	{
		// successfully read all entries. WE'RE DONE!!!!!!
		return idx;
	}

	// FAIL: could not read entire file entries buffer

//WADOpen_entries:
	if (WAD_Get(idx)->entries != nullptr) {
		std::free(WAD_Get(idx)->entries);
	}

WADOpen_absdirs:
	if (WAD_Get(idx)->absdirs != nullptr) {
		// cleanup allocated absolute directory file paths
		for (int j = 0; j < (int)WAD_Get(idx)->count; j++) {
			if (WAD_Get(idx)->absdirs[j] != nullptr) {
				std::free(WAD_Get(idx)->absdirs[j]);
			}
		}
		// free(WAD_Get(idx)->absdirs);
	}

WADOpen_reldirs:
	// failure, clean up half-finished WAD file reading
	// although freadstr never returns false...
	if (WAD_Get(idx)->reldirs != nullptr) {
		// cleanup allocated relative directory file paths
		for (int j = 0; j < (int)WAD_Get(idx)->count; j++) {
			if (WAD_Get(idx)->reldirs[j] != nullptr) {
				std::free(WAD_Get(idx)->reldirs[j]);
			}
		}
		// std::free(WAD_Get(idx)->reldirs);
	}
	// goto cleanup_allocs;
	// if (WAD_Get(idx)->absdirs != nullptr) {
	// 	std::free(WAD_Get(idx)->absdirs);
	// }
	// std::fclose(file);
	// goto WADOpen_end;
	// goto WADOpen_close;

WADOpen_allocs:
	// std::fclose(file);
	if (WAD_Get(idx)->reldirs != nullptr)
		std::free(WAD_Get(idx)->reldirs);
	if (WAD_Get(idx)->absdirs != nullptr)
		std::free(WAD_Get(idx)->absdirs);
	// goto WADOpen_end;
	// goto WADOpen_close;

WADOpen_close:
	std::fclose(file);

WADOpen_end:
	return -1;
}


// Returns LegoWADFile at idx in table. (0-9)
// 
// <LegoRR.exe @0048bfa0>
WADFile* __cdecl lego::file::WAD_Get(int wadIndex)
{
	return &globals::g_WADFILES_TABLE[wadIndex];
}

// <LegoRR.exe @0048bfb0>
size_t __cdecl lego::file::WAD_GetEntrySize(int wadIndex, int entryIndex)
{
	return WAD_Get(wadIndex)->entries[entryIndex].orig_size;
}

// <LegoRR.exe @0048bfd0>
size_t __cdecl lego::file::WAD_GetEntryPackedSize(int wadIndex, int entryIndex)
{
	return WAD_Get(wadIndex)->entries[entryIndex].pack_size;
}

// <LegoRR.exe @0048bff0>
int __cdecl lego::file::WAD_Shared__Next(void)
{
	for (int i = 0; i < SHARED_WADENTRIES_COUNT /*100*/; i++) {
		if (!globals::g_SHARED_WADENTRIES_TABLE[i].isUsed) {
			return i;
		}
	}
	return -1;
}

// Returns the file index found 
// Returns -1 on failure or not found.
// 
// <LegoRR.exe @0048c010>
int __cdecl lego::file::WAD_FindEntry(const char* filename, int opt_wadIndex)
{
	if (opt_wadIndex != -1)
		return WAD_FindEntry__InWAD(filename, opt_wadIndex);

	for (int wadIndex = WADFILES_COUNT - 1 /*10-1=9*/; wadIndex >= 0; wadIndex--) {
		if (!WAD_Get(wadIndex)->isUsed)
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
int __cdecl lego::file::WAD_FindEntry__InWAD(const char* filename, int wadIndex)
{
	for (int i = 0; i < (int)globals::g_WADFILES_TABLE[wadIndex].count; i++) {
		if (_stricmp(globals::g_WADFILES_TABLE[wadIndex].reldirs[i], filename) == 0)
			return i;
	}
	return -1;
}

// Returns idx of next available LegoWADFile in table (0-9). -1 when none are available.
//
// <LegoRR.exe @0048c0c0>
int __cdecl lego::file::WAD__Next(void)
{
	for (int i = 0; i < WADFILES_COUNT /*10*/; i++) {
		if (!globals::g_WADFILES_TABLE[i].isUsed) { // NOTE: field_4 is checked, not field_0
			// clear memory, and prepare for usage
			std::memset(&globals::g_WADFILES_TABLE[i], 0, sizeof(WADFile));
			return i;
		}
	}
	return -1;
}

// Reads a WAD from filename into a shared file table, and returns the index in the table
// 
// <LegoRR.exe @0048c100>
int __cdecl lego::file::WAD_SharedOpen__InWAD(const char* filename, int wadIndex)
{
	int idx = WAD_Shared__Next();
	if (idx == -1)
		return -1;

	int entryIndex = WAD_FindEntry(filename, wadIndex);
	if (entryIndex == -1)
		return -1;

	size_t entrySize = WAD_GetEntryPackedSize(wadIndex, entryIndex);
	unsigned char* buffer = (unsigned char*)std::malloc(entrySize);
	if (buffer == nullptr)
		return -1;

	size_t entryOffset = WAD_Get(wadIndex)->entries[entryIndex].offset;
	std::fseek(WAD_Get(wadIndex)->file, entryOffset, 0);
	entrySize = WAD_GetEntryPackedSize(wadIndex, entryIndex);
	if (std::fread(buffer, entrySize, 1, WAD_Get(wadIndex)->file) != 1) {
		std::free(buffer);
		return -1;
	}

	unsigned char* fileData = buffer;
	if (WAD_Get(wadIndex)->entries[entryIndex].flags & WADENTRY_COMPRESSED /*0x2*/) { // flag 0x2 == compressed???
		fileData = nullptr;
		RNC_Decompress(buffer, &fileData);
		std::free(buffer); // data decompressed(?) to new buffer stored in fileData, free original buffer
	}
	globals::g_SHARED_WADENTRIES_TABLE[idx].fileData   = fileData;
	globals::g_SHARED_WADENTRIES_TABLE[idx].isUsed     = TRUE;
	globals::g_SHARED_WADENTRIES_TABLE[idx].wadIndex   = wadIndex;
	globals::g_SHARED_WADENTRIES_TABLE[idx].entryIndex = entryIndex;
	return idx;
}

// Reads a WAD from filename into a shared file table, and returns the index in the table.
// if opt_wadIndex is -1, all WAD files will be searched for the file name
// 
// <LegoRR.exe @0048c230>
int __cdecl lego::file::WAD_SharedOpen(const char* filename, int opt_wadIndex)
{
	if (opt_wadIndex != -1)
		return WAD_SharedOpen__InWAD(filename, opt_wadIndex);

	for (int wadIndex = WADFILES_COUNT - 1 /*10-1=9*/; wadIndex >= 0; wadIndex--) {
		if (!WAD_Get(wadIndex)->isUsed)
			continue;

		int sharedIndex = WAD_SharedOpen__InWAD(filename, wadIndex);
		if (sharedIndex != -1)
			return sharedIndex;
	}
	return -1;
}

// <LegoRR.exe @0048c280>
void __cdecl lego::file::WAD_Shared__Dispose(int sharedIndex)
{
	if (globals::g_SHARED_WADENTRIES_TABLE[sharedIndex].isUsed) {
		std::free(globals::g_SHARED_WADENTRIES_TABLE[sharedIndex].fileData);
		globals::g_SHARED_WADENTRIES_TABLE[sharedIndex].isUsed = FALSE;
	}
}

// <LegoRR.exe @0048c2b0>
unsigned char* __cdecl lego::file::WAD_SharedGetData__internal(int sharedIndex)
{
	if (globals::g_SHARED_WADENTRIES_TABLE[sharedIndex].isUsed) {
		return (unsigned char*)globals::g_SHARED_WADENTRIES_TABLE[sharedIndex].fileData;
	}
	return nullptr;
}

// <LegoRR.exe @0048c2d0>
unsigned int __cdecl lego::file::WAD_SharedGetSize(int sharedIndex)
{
	return WAD_GetEntrySize(globals::g_SHARED_WADENTRIES_TABLE[sharedIndex].wadIndex,
		globals::g_SHARED_WADENTRIES_TABLE[sharedIndex].entryIndex);
}

// <LegoRR.exe @0048c2f0>
unsigned char* __cdecl lego::file::WAD_SharedGetData(int sharedIndex)
{
	return WAD_SharedGetData__internal(sharedIndex);
}

// Haven't really looked into this, but it's called when WADEntry.version & 0x2 flag is set... weird
// Maybe it's the SafeDisc CD DRM garbage...?
// 
// <LegoRR.exe @0049ca80>
size_t __cdecl lego::file::RNC_Decompress(unsigned char* srcBuffer, unsigned char** out_dstBuffer)
{
	///TODO: decompile me
	return 0;
}

// <LegoRR.exe @0049cb00>
int __cdecl lego::file::RNC_Decompress__internal(unsigned char* srcBuffer, unsigned char* dstBuffer)
{
	///TODO: decompile me
	return 0;
}

#pragma endregion
