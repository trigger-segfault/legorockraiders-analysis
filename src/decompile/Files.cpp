// Files.h : Defines file system management functions and a custom File I/O API.
//
/// STATUS: [Usable, but still being refactored]

#include "Files.h"
// This header is included in "Files.h" so that half the API isn't
//  missing when calling `File_OpenSharedBuffer(const char*,unsigned int*)`.
//#include "SharedBuffers.h"
#include "StringUtils.h"
#include "Registry.h"
#include "WAD.h"


using namespace lego;
using namespace lego::file;


#pragma region Globals

// // <LegoRR.exe @005349a0>
// char lego::file::g_FILEPATH_DATADIR_STRIP[1024];
// // <LegoRR.exe @00534da0>
// char lego::file::tmp_FILEPATH_STRIPDATADIR[1024];

// // (unused 4-byte gap)

// // <LegoRR.exe @005351a0>
// char lego::file::tmp_FILEPATH_JOINDATADIR[MAX_PATH /*260*/];
// // <LegoRR.exe @005352a8>
// char lego::file::g_FILEPATH_DATADIR_JOIN[MAX_PATH /*260*/];

// // <LegoRR.exe @005353ac>
// FileOpenCallback lego::file::g_FileOpenCallback;
// // <LegoRR.exe @005353b0>
// void* lego::file::g_FileOpenCallback_VALUE;

// // <LegoRR.exe @005353b4>
// char lego::file::g_CDROMDriveLetter;

// // (unused 3-byte gap)

// // <LegoRR.exe @005353b8>
// BOOL lego::file::g_HasDataDir;

/// PRIVATE:
// <LegoRR.exe @005349a0 - 005353bc>
FileSystemManager lego::globals::g_Files;

#pragma endregion


#pragma region Functions

// This function is guaranteed to fail if `insistOnCD` is true, due to some logic errors.
// The argument `wadBasename` determines the name of WAD files to look for: "<wadBasename>#.wad".
//  This is always the same as the base executable name (without extension, i.e. "LegoRR").
// <LegoRR.exe @0047f3f0>
void __cdecl lego::file::InitFileSystem(const char* wadBasename, BOOL insistOnCD, const char* regKey)
{
	char currentDir[MAX_PATH /*260*/];
	char dataDir[MAX_PATH /*260*/];
	char wadFile[MAX_PATH /*260*/];
	char errorMessage[1024];
	char cdkeyFile[1024];
	char regValue[1024];

	// assign one of our too Data directory globals...
	::_getcwd(currentDir, sizeof(currentDir) /*260*/);

	// The Ghidra decompilation for this was so messed up...
	//  (`currentDir[0] != '\0'` added to circumvent stack safefty jank)
	size_t currentLen = std::strlen(currentDir);
	if (currentLen != 0 && currentDir[currentLen - 1] == '\\') {
		currentDir[currentLen - 1] = '\0';
	}
	std::sprintf(globals::g_Files.FILEPATH_DATADIR_JOIN, "%s\\%s", currentDir, "Data");


	// check for WAD files 0-9
	BOOL hasWADs = false;
	for (int i = 0; i < WADFILES_COUNT /*10*/; i++) {
		std::sprintf(wadFile, "%s%i.wad", wadBasename, i);
		// -1 returned for no WAD index (index does not correspond to file number)
		if (File_OpenWAD(wadFile) != -1) {
			hasWADs = true;
		}
	}


	// assign the other one of our Data directory globals...
	::_getcwd(dataDir, sizeof(dataDir));
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

		if (!registry::Registry_QueryStringOnLM(regKey, "CDMissing", REGISTRY_STRING /*0*/, regValue, sizeof(regValue))) {
			std::exit(0);
		}
		else {
			registry::Registry_QueryStringOnLM(regKey, "SetupError", REGISTRY_STRING /*0*/, errorMessage, sizeof(errorMessage));
			if (::MessageBoxA(nullptr, regValue, errorMessage, MB_OKCANCEL /*1*/) == IDCANCEL /*2*/)
				std::exit(0); // exit once the user decides to cancel, otherwise rinse and repeat
		}
		hasCDROM = Path_CheckForCDROM();
	}
#endif

	// no WAD files, find Data directory
	BOOL missingData = false;
	if (!hasCDROM && !hasWADs) {
		missingData = true;
		_finddata32_t fileinfo; // local_e1c
		intptr_t handle = ::_findfirst32("*.*", &fileinfo);
		if (handle != -1) { // -1 for failure
			do {
				if ((fileinfo.attrib & FILE_ATTRIBUTE_DIRECTORY) && ::_stricmp(fileinfo.name, "Data") == 0) {
					missingData = false; // data dir found??
					break;
				}
			} while (::_findnext32(handle, &fileinfo) == 0);
			::_findclose(handle);
		}
	}

	// What the hell is this doing??
	if (insistOnCD) {
		std::sprintf(cdkeyFile, "%s\\%s", "Data", "cd.key");
		FILE* file = std::fopen(cdkeyFile, "r");
		if (file != nullptr) {
			std::fclose(file);
			missingData = true; // has CD?? what....???
		}
	}

	// "delme.dat"
	if (!missingData) { // no CD, and no Data dir?
		::_mkdir("Data"); // create Data dir
		std::sprintf(cdkeyFile, "%s\\%s", "Data", "delme.dat");
		FILE* file = std::fopen(cdkeyFile, "r");
		if (file != nullptr) { // data dir must have already existed???
			std::fclose(file);
			::_chmod(cdkeyFile, FILE_ATTRIBUTE_NORMAL /*0x80*/);
			std::remove(cdkeyFile);
			return;
		}
		// regardless, after this the function finishes successfully
	}
	else {
		std::memset(errorMessage, 0, sizeof(errorMessage));
		std::strcpy(errorMessage, "Error");

		if (registry::Registry_QueryValueOnLM(regKey, "DataMissing", REGISTRY_STRING /*0*/, regValue, sizeof(regValue))) {
			registry::Registry_QueryValueOnLM(regKey, "SetupError", REGISTRY_STRING /*0*/, errorMessage, sizeof(errorMessage));
			::MessageBoxA(nullptr, regValue, errorMessage, MB_OK /*0*/);
		}
		std::exit(0);
	}
	return;
}

// Checks for a currently-inserted CDROM drive containing the file "CDROM:\Data\cd.key"
// Does not actually check contents of the file.
// Returns true when found, and assigns global: char g_CDROMDriveLetter;
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
		if (::GetDriveTypeA(rootName) == DRIVE_CDROM /*5*/) {
			// confirm this CDROM drive has the file "CDROM:\Data\cd.key"
			std::sprintf(buffer, "%c:\\%s\\%s", letter, "Data", "cd.key");
			FILE* file = std::fopen(buffer, "r");
			if (file != nullptr) {
				std::fclose(file);
				globals::g_Files.CDROMDriveLetter = letter; // assign drive letter, for later use
				return true;
			}
		}
	}
#endif
	return false;
}

// <LegoRR.exe @0047f850>
BOOL __cdecl lego::file::Path_SetDataDir(const char* dirname)
{
	if (dirname != nullptr) {
		size_t strLength = std::strlen(dirname);
		if (strLength < sizeof(globals::g_Files.FILEPATH_DATADIR_STRIP) && strLength != 0) {
			std::strcpy(globals::g_Files.FILEPATH_DATADIR_STRIP, dirname);
			globals::g_Files.HasDataDir = true;
			return true;
		}
	}
	globals::g_HasDataDir = false;
	std::memset(globals::g_Files.FILEPATH_DATADIR_STRIP, 0, sizeof(globals::g_Files.FILEPATH_DATADIR_STRIP));
	return false;
}

// <LegoRR.exe @0047f8c0>
void __cdecl lego::file::File__logf(const char* format, ...)
{
	char buffer[1024];

	std::va_list vl;
	va_start(vl, format);
	std::vsprintf(buffer, format, vl);
	va_end(vl);

	::OutputDebugStringA(buffer);
}

// Open WAD filename and log something (that was removed on release build)
// returns idx of newly opened WAD (0-9), or -1 on failure of any kind.
//
// <LegoRR.exe @0047f900>
int __cdecl lego::file::File_OpenWAD(const char* filename)
{
	lego::logf_removed(nullptr);
	return wad::WAD_Open(filename);
}

// <LegoRR.exe @0047f920>
BOOL __cdecl lego::file::Path_GetCDROMDataPath(char* out_filepath, const char* filename)
{
#ifndef DEBUG_IGNORECD
	if (globals::g_Files.CDROMDriveLetter != '\0') {
		std::sprintf(out_filepath, "%c:\\%s\\%s", globals::g_Files.CDROMDriveLetter, "Data", filename);
		return true;
	}
#endif
	return false;
}

// <LegoRR.exe @0047f960>
int __cdecl lego::file::Path_MakeDataSubdir(const char* dirname)
{
	char buffer[MAX_PATH /*260*/];

	std::sprintf(buffer, "%s\\%s", "Data", dirname);
	return ::_mkdir(buffer);
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
		fileStream = File__Create(FILELOC_WAD /*0*/);
		if (fileStream == nullptr)
			return nullptr;

		message = Path_StripDataDir(filename);
		if (File_OpenWADEntry(fileStream->wad, message)) {
			filename = Path_StripDataDir(filename);
			lego::logf_removed("WAD Load %s\n", filename);
			return fileStream;
		}
		filename = Path_StripDataDir(filename);
		message = "WAD Fail %s\n";
	}
	else if (location == FILELOC_STD /*1*/) {
		fileStream = File__Create(FILELOC_STD /*1*/);
		if (fileStream == nullptr)
			return nullptr;

		FILE* stdFile = std::fopen(filename, mode);
		fileStream->std = stdFile;
		if (stdFile != nullptr) {
			lego::logf_removed("STD Load %s\n", filename);
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
		File__logf("%s(%i) : Error in call to %s\n", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 330 /*__LINE__*/, "File_Open");
		return nullptr;
	}
	lego::logf_removed(message, filename);
	File__Destroy(fileStream);
	return nullptr;
}

// <LegoRR.exe @0047fb10>
int __cdecl lego::file::File_Seek(FileStream* file, long offset, int origin)
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
			file->wad->position = (int)wad::WAD_StreamGetSize(file->wad->streamIndex) + offset;
			return 0; // no bounds checks here...

		default:
			// typo is "correct" :P
			File__logf("Uknown seek mode (%i)", origin);
			return 0;
		}
		// bounds checks
		if (file->wad->position > (int)wad::WAD_StreamGetSize(file->wad->streamIndex))
			file->wad->position = wad::WAD_StreamGetSize(file->wad->streamIndex);
		else if (file->wad->position < 0)
			file->wad->position = 0;
		// despite what you'd think, this always returns 0 for WADs, but the EAX result register is clearly set...
		return 0;
	}
	else if (location == FILELOC_STD /*1*/) {
		return std::fseek(file->std, offset, origin);
	}
	File__logf("%s(%i) : Unknown file system in call to %s", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 368 /*__LINE__*/, "File_Seek");
	return 0;
}

// <LegoRR.exe @0047fc40>
size_t __cdecl lego::file::File_Read(void* out_ptr, size_t size, size_t count, FileStream* file)
{
	FileLocation location = File_GetLocation(file);
	if (location == FILELOC_WAD /*0*/) {
		size_t fileSize = (int)wad::WAD_StreamGetSize(file->wad->streamIndex);
		size_t readSize = count * size;
		int position = file->wad->position;
		if ((int)fileSize < (position + readSize))
			readSize = fileSize - position;

		unsigned char* fileData = wad::WAD_StreamGetData(file->wad->streamIndex);
		std::memcpy(out_ptr, (fileData + file->wad->position), readSize);
		file->wad->position += readSize;
		return (int)readSize / (int)size; // (partial element size reads may occur)
	}
	else if (location == FILELOC_STD /*1*/) {
		return std::fread(out_ptr, size, count, file->std);
	}
	File__logf("%s(%i) : Unknown file system in call to %s", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 395 /*__LINE__*/, ""/*EMPTYSTR*/);
	return 0;
}

// <LegoRR.exe @0047fd10>
size_t __cdecl lego::file::File_Write(const void* ptr, size_t size, size_t count, FileStream* file)
{
	FileLocation location = File_GetLocation(file);
	if (location == FILELOC_WAD /*0*/) {
		File__logf("Cannot write to a file stored in a Wad!");
		return 0;
	}
	else if (location == FILELOC_STD /*1*/) {
		return std::fwrite(ptr, size, count, file->std);
	}
	File__logf("%s(%i) : Unknown file system in call to %s", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 414 /*__LINE__*/, "File_Write");
	return 0;
}

// <LegoRR.exe @0047fd80>
int __cdecl lego::file::File_Close(FileStream* file)
{
	FileLocation location = File_GetLocation(file);
	if (location >= 0 && location < 2) { // == FILELOC_WAD || == FILELOC_REAL
		File__Destroy(file);
		return 0;
	}
	File__logf("%s(%i) : Unknown file system in call to %s", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 431 /*__LINE__*/, "File_Close");
	return 0;
}

// <LegoRR.exe @0047fdd0>
long __cdecl lego::file::File_Tell(FileStream* file)
{
	FileLocation location = File_GetLocation(file);
	if (location == FILELOC_WAD /*0*/) {
		return (long)file->wad->position;
		// return *(int *)(file->stream + 4);
	}
	if (location == FILELOC_STD /*1*/) {
		return (long)std::ftell(file->std);
	}
	File__logf("%s(%i) : Unknown file system in call to %s", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 469 /*__LINE__*/, "File_Tell");
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
		return wad::WAD_FindEntry(dataFilename, globals::WADFILE_ANY /*-1*/);
	}
	else if (location == FILELOC_STD /*1*/) {
		// check Data dir path
		FILE* file = std::fopen(dataFilename, "r");
		if (file != nullptr) {
			std::fclose(file);
			return true;
		}

		// check CDROM path
		if (Path_GetCDROMDataPath(buffer, filename)) {
			file = std::fopen(buffer, "r");
			if (file != nullptr) {
				std::fclose(file);
				return true;
			}
		}
	}
	return false; // meanwhile we return 0 here on failure... GAHHH
}

// <LegoRR.exe @0047fee0>
int __cdecl lego::file::File_GetC(FileStream* file)
{
	FileLocation location = File_GetLocation(file);
	if (location == FILELOC_WAD /*0*/) {
		if ((int)(wad::WAD_StreamGetSize(file->wad->streamIndex) - 1) <= file->wad->position)
			return -1; // end of stream

		unsigned char* fileBuffer = (unsigned char*)wad::WAD_StreamGetData(file->wad->streamIndex);
		return fileBuffer[file->wad->position++];
	}
	else if (location == FILELOC_STD /*1*/) {
		return std::fgetc(file->std);
	}
	File__logf("%s(%i) : Unknown file system in call to %s", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 545 /*__LINE__*/, "File_GetC");
	return 0;
}

// <LegoRR.exe @0047ff60>
long __cdecl lego::file::File_GetLength(FileStream* file)
{
	int origOffset = File_Tell(file);
	File_Seek(file, 0, SEEK_END /*2*/);
	int length = File_Tell(file);
	File_Seek(file, origOffset, SEEK_SET /*0*/);
	return length;
}

// <LegoRR.exe @0047ffa0>
char* __cdecl lego::file::File_GetS_WAD__internal(char* out_str, int num, FileStream* file)
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
		return File_GetS_WAD__internal(out_str, num, file);
	}
	else if (location != FILELOC_STD /*1*/) {
		return std::fgets(out_str, num, file->std);
	}
	File__logf("%s(%i) : Unknown file system in call to %s", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 587 /*__LINE__*/, "File_GetS");
	return nullptr;
}

// <LegoRR.exe @00480070>
int __cdecl lego::file::File_PrintF(FileStream* file, const char* format, ...)
{
	FileLocation location = File_GetLocation(file);
	if (location == FILELOC_WAD /*0*/) {
		File__logf("\"fprintf\" is unsupprted for wad files");
		return 0;
	}
	else if (location == FILELOC_STD /*1*/) {
		std::va_list vl;
		va_start(vl, format);
		std::vfprintf(file->std, format, vl);
		va_end(vl);
		return 0;
	}
	File__logf("%s(%i) : Unknown file system in call to %s", "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c", 612 /*__LINE__*/, "File_PrintF");
	return 0;
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
			int entryIndex = wad::WAD_FindEntry(filename, globals::WADFILE_ANY /*-1*/);
			if (entryIndex != -1)
				return FILELOC_WAD /*0*/;
		}
		return FILELOC_STD /*1*/; // as long as the arguments were valid, return STD
	}
	return FILELOC_ERROR /*2*/; //BOOL3_ERROR;
}

// <LegoRR.exe @00480160>
BOOL __cdecl lego::file::File_OpenWADEntry(WADEntryStream* wadStream, const char* filename)
{
	wadStream->field_unused_8 = 0;
	wadStream->position = 0;
	int streamIndex = wad::WAD_StreamOpen(filename, globals::WADFILE_ANY /*-1*/);
	wadStream->streamIndex = streamIndex;
	return (streamIndex != -1);
}

// <LegoRR.exe @00480190>
FileStream* __cdecl lego::file::File__Create(FileLocation location)
{
	if (location == FILELOC_WAD /*0*/) {
		FileStream* file = (FileStream*)File__malloc(sizeof(FileStream) /*8*/);
		if (file != nullptr) {
			file->location = FILELOC_WAD /*0*/;

			WADEntryStream* wadFile = (WADEntryStream*)File__malloc(sizeof(WADEntryStream) /*0xc*/);
			file->wad = wadFile;
			if (wadFile != nullptr) {
				return file;
			}
			File__free(file);
		}
	}
	else if (location == FILELOC_STD /*1*/) {
		FileStream* file = (FileStream*)File__malloc(sizeof(FileStream) /*8*/);
		// SANITY: no null check here... heh
		file->location = FILELOC_STD /*1*/;
		return file;
	}
	return nullptr;
}

// <LegoRR.exe @004801f0>
void* __cdecl lego::file::File__malloc(size_t size)
{
	// presumably contained logging information at one point
	return std::malloc(size);
}

// <LegoRR.exe @00480200>
void __cdecl lego::file::File__free(void* ptr)
{
	// presumably contained logging information at one point
	std::free(ptr);
}

// <LegoRR.exe @00480210>
void __cdecl lego::file::File__Destroy(FileStream* file)
{
	if (file != nullptr) {
		FileLocation location = File_GetLocation(file);
		if (location == FILELOC_WAD /*0*/) {
			if (file->wad != nullptr) {
				wad::WAD_StreamClose(file->wad->streamIndex);
				File__free(file->wad);
			}
			File__free(file);
		}
		else if (location == FILELOC_STD /*1*/) {
			if (file->std != nullptr) {
				std::fclose(file->std);
			}
			File__free(file);
		}
	}
}


// Strips the Data directory from the filename path, using global g_FILEPATH_DATADIR_1 as a comparison.
// Returns a temporary buffer that must be used before this function is next called.
// 
// <LegoRR.exe @00480280>
const char* __cdecl lego::file::Path_StripDataDir(const char* filename)
{
	if (!globals::g_Files.HasDataDir)
		return filename;

	int datadirLen = (int)std::strlen(globals::g_Files.FILEPATH_DATADIR_STRIP);
	if ((int)std::strlen(filename) <= datadirLen) // shorter than DATADIR, can't start with datadir
		return filename;

	char c = filename[datadirLen]; // backup original char here (which *should* be path separator, but could potentially be something else)
	const_cast<char*>(filename)[datadirLen] = '\0';   // then replace that char with null-terminator
	
	if (::_stricmp(filename, globals::g_Files.FILEPATH_DATADIR_STRIP) == 0) { // compare filename and datadir (could be replaced with strnicmp)
		std::sprintf(globals::g_Files.tmp_FILEPATH_STRIPDATADIR, "%s", filename + datadirLen + 1);
		const_cast<char*>(filename)[datadirLen] = c; // restore char
		return globals::g_Files.tmp_FILEPATH_STRIPDATADIR;
	}
	const_cast<char*>(filename)[datadirLen] = c; // restore char
	return filename;
}

// all parameters are directly passed to File_GetS, then some operation on string is performed
// 
// <LegoRR.exe @00480310>
char* __cdecl lego::file::File_ReadLine(char* out_str, int num, FileStream* file)
{
	char* result = File_GetS(out_str, num, file);
	// generally File_GetS should return at least one character, but these are some dangurous assumptions?
	int len = (int)std::strlen(out_str);

	if (out_str[len - 1] == '\n')
		out_str[len - 1] = '\0'; // strip LF

	if ((len - 1) != 0 && out_str[len - 2] == '\r')
		out_str[len - 2] = '\0'; // strip CRLF (regardless if last char is LF)

	return result;
}

// <LegoRR.exe @00480360>
unsigned char* __cdecl lego::file::File_ReadAllBytes(const char* filename, unsigned int* out_length)
{
	return (unsigned char*)File_ReadAll(filename, out_length, true /*isBinary*/);
}

// <LegoRR.exe @00480380>
void* __cdecl lego::file::File_ReadAll(const char* filename, unsigned int* out_length, BOOL isBinary)
{
	FileStream* file = File_Open(filename, isBinary ? "rb" : "r");
	if (file != nullptr) {
		File_Seek(file, 0, SEEK_END /*2*/);
		int length = File_Tell(file);

		if (globals::g_Files.OpenCallback != nullptr)
			globals::g_Files.OpenCallback(filename, (unsigned int)length, globals::g_Files.OpenCallback_VALUE);

		void* buffer = std::malloc(length);
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
int __cdecl lego::file::File_OpenSharedBuffer(const char* filename, unsigned int* out_length)
{
	FileStream* file = File_Open(filename, "rb");
	if (file != nullptr) {
		File_Seek(file, 0, SEEK_END /*2*/);
		long length = File_Tell(file);

		if (globals::g_Files.OpenCallback != nullptr)
			globals::g_Files.OpenCallback(filename, (unsigned int)length, globals::g_Files.OpenCallback_VALUE);

		int bufferIndex = SharedBuffer_Open(length);
		if (bufferIndex != -1) {
			void* out_buffer = SharedBuffer_GetData(bufferIndex);
			// In the case of WAD file entries, this method is horribly inefficient.
			//  Two allocations, and 3+ if using RNC compression...
			File_Seek(file, 0, SEEK_SET /*0*/);
			File_Read(out_buffer, 1, length, file);
			if (out_length != nullptr) {
				*out_length = length;
			}

			File_Close(file);
			return bufferIndex;
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

		std::sprintf(buffer, "%s\\%s", globals::g_Files.FILEPATH_DATADIR_JOIN, filename);
		if (::_fullpath(globals::g_Files.tmp_FILEPATH_JOINDATADIR, buffer, MAX_PATH /*260*/) != nullptr) {

			if (std::strncmp(globals::g_Files.tmp_FILEPATH_JOINDATADIR, globals::g_Files.FILEPATH_DATADIR_JOIN, std::strlen(globals::g_Files.FILEPATH_DATADIR_JOIN)) == 0) {
				return globals::g_Files.tmp_FILEPATH_JOINDATADIR;
			}
		}
	}
	return nullptr;
}

// <LegoRR.exe @00480570>
void __cdecl lego::file::File_SetOpenCallback(FileOpenCallback callback, void* lpValue)
{
	globals::g_Files.OpenCallback = callback;
	globals::g_Files.OpenCallback_VALUE = lpValue;
}

// <LegoRR.exe @00480590>
void __cdecl lego::file::Scan_ReadDataDirList(const char* filename)
{
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
		Scan_Directory(globals::g_Files.FILEPATH_DATADIR_JOIN);
		std::fclose((FILE*)file); // what the hell.....
	}
}
// <LegoRR.exe @00480650>
void __cdecl lego::file::Scan_Directory(const char* dirname)
{
	char buffer[1024];

	std::strcpy(buffer, dirname);
	std::strcat(buffer, "\\*.*");

	_finddata32_t finddata;
	intptr_t handle = ::_findfirst32(buffer, &finddata);
	if (handle != -1) {
		do {
			if (std::strcmp(finddata.name, ".") != 0 && std::strcmp(finddata.name, "..") != 0) {
				std::strcpy(buffer, dirname);
				std::strcat(buffer, "\\");
			}

			if (!(finddata.attrib & FILE_ATTRIBUTE_DIRECTORY /*0x10*/)) {
				Scan_File(buffer); // an actual file
			}
			else {
				Scan_Directory(buffer); // a directory, recurse with this function
			}
		} while (::_findnext32(handle, &finddata) == 0);
		::_findclose(handle);
	}
}

// Chances are high that there was a preprocessor-removed functionality in here.
// This straight up does nothing, because not even the return is used.
// <LegoRR.exe @00480830>
int __cdecl lego::file::Scan_File(const char* filename)
{
	for (unsigned int i = 0; i < globals::g_ScanRealFiles_FilePaths_COUNT; i++) {
		if (::_stricmp(filename, globals::g_ScanRealFiles_FilePaths_TABLE[i]) == 0)
			return 0; // preprocessor removed
	}
	return (int)globals::g_ScanRealFiles_FilePaths_COUNT;
}

#pragma endregion

