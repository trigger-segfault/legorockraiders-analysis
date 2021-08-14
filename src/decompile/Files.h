// Files.h : Declares file system management functions and a custom File I/O API.
//
/// STATUS: [Usable, but still being refactored]
/// PURPOSE: A file system manager for simplifying file I/O when a file's location could
///          be in multiple possible locations. Implements an identical API to C File I/O.
///
/// NAMESPACE: lego::file
/// INITIALIZE: Call `InitFileSystem(const char*,BOOL,const char*)` once on startup.
///             (no cleanup)
/// GLOBALS: private | temporary return buffer that must be used immediately

#pragma once

#include "Common.h"
// This header is included here so that half the API isn't
//  missing when calling `File_OpenSharedBuffer(const char*,unsigned int*)`.
#include "SharedBuffers.h"


#pragma region Defines

#define s_Dev_SourceSafe__Files_c "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c"

#pragma endregion


#pragma region Enums
namespace lego {

/// PUBLIC:
enum FileLocation : int
{
	FILELOC_WAD   = 0,
	FILELOC_STD   = 1,
	FILELOC_ERROR = 2,
};
static_assert(sizeof(FileLocation) == 0x4, "");

} /* namespace lego */
#pragma endregion


#pragma pack(push, 1)

#pragma region Types
namespace lego {

/// PRIVATE:
struct FileWADStream
{
	/*0,4*/ int streamIndex; // index of SharedWADEntry in global table
	/*4,4*/ int position;
	/*8,4*/ unsigned int field_unused_8;
	/*c*/
};
static_assert(sizeof(FileWADStream) == 0xc, "");

/// PUBLIC:
struct FileStream
{
	/*0,4*/ FileLocation location;
	/*4,4*/ union {
		FILE* std; // (referred to as STD "standard" file by engine)
		FileWADStream* wad;
	};
	/*8*/
};
static_assert(sizeof(FileStream) == 0x8, "");


// arguments are: filename, fileSize, lpValue (`lpValue` is passed to File_SetOpenCallback)
typedef void (__cdecl* FileOpenCallback)(const char* filename, unsigned int fileSize, void* lpContext);

} /* namespace lego */
#pragma endregion


#pragma region Globals
namespace lego::file {

/// PRIVATE:
// <LegoRR.exe @005349a0 - 005353bc>
struct FileSystemManager
{
	// <LegoRR.exe @005349a0>
	/*000,400*/ char FILEPATH_DATADIR_STRIP[1024];
	// <LegoRR.exe @00534da0>
	/*400,400*/ char tmp_FILEPATH_STRIPDATADIR[1024];
	// <LegoRR.exe @005351a0>
	/*800,104*/ char tmp_FILEPATH_JOINDATADIR[MAX_PATH /*260*/];
	// <LegoRR.exe @005352a4>
	/*904,4*/ unsigned int reserved1; // (unused 4-byte gap)
	// <LegoRR.exe @005352a8>
	/*908,104*/ char FILEPATH_DATADIR_JOIN[MAX_PATH /*260*/];
	// <LegoRR.exe @005353ac>
	/*a0c,4*/ FileOpenCallback OpenCallback;
	// <LegoRR.exe @005353b0>
	/*a10,4*/ void* OpenCallback_VALUE;
	// <LegoRR.exe @005353b4>
	/*a14,1*/ char CDROMDriveLetter;
	// <LegoRR.exe @005353b5>
	/*a15,3*/ unsigned char reserved2[3]; // (unused 3-byte gap)
	// <LegoRR.exe @005353b8>
	/*a18,4*/ BOOL HasDataDir;
	/*a1c*/
};
static_assert(sizeof(FileSystemManager) == 0xa1c, "");
	
} /* namespace lego::file */
namespace lego::globals {

/// PRIVATE:
// <LegoRR.exe @005349a0 - 005353bc>
extern lego::file::FileSystemManager g_Files;

// /// PRIVATE:
// // <LegoRR.exe @005349a0>
// extern char g_FILEPATH_DATADIR_STRIP[1024];
// // <LegoRR.exe @00534da0>
// extern char tmp_FILEPATH_STRIPDATADIR[1024];

// // (unused 4-byte gap)

// // <LegoRR.exe @005351a0>
// extern char tmp_FILEPATH_JOINDATADIR[MAX_PATH /*260*/];
// // <LegoRR.exe @005352a8>
// extern char g_FILEPATH_DATADIR_JOIN[MAX_PATH /*260*/];

// // <LegoRR.exe @005353ac>
// extern FileOpenCallback g_FileOpenCallback;
// // <LegoRR.exe @005353b0>
// extern void* g_FileOpenCallback_VALUE;

// // <LegoRR.exe @005353b4>
// extern char g_CDROMDriveLetter;

// // (unused 3-byte gap)

// // <LegoRR.exe @005353b8>
// extern BOOL g_HasDataDir;

// /// TODO: move everything below to its respective file

// // <LegoRR.exe @00545a20 -> 005498a0>
// extern SharedFileBuffer g_SHARED_FILEBUFFERS_TABLE[SHARED_FILEBUFFERS_COUNT /*2000*/];


// // <LegoRR.exe @00576ce0>
// extern FileStream* g_ScanFileStream_1;
// // <LegoRR.exe @00576ce4>
// extern FileStream* g_ScanFileStream_2;
// // <LegoRR.exe @00576ce8>
// extern FileStream* g_ScanFileStream_3;
// // <LegoRR.exe @00576cec>
// extern FileStream* g_ScanFileStream_OutputList;
// // <LegoRR.exe @00576cf0>
// extern char g_ScanFilename_InputList[1024];
// // <LegoRR.exe @005770f0>
// extern char g_ScanFilename_OutputList[1024];

// // <LegoRR.exe @005774f4>
// extern BOOL g_ScanIsFullScreen;

// // <LegoRR.exe @005779e0>
// extern char g_ScanRealFiles_FilePaths_TABLE[2000][1024];
// // <LegoRR.exe @0076b9e0>
// extern unsigned int g_ScanRealFiles_FilePaths_COUNT;

} /* namespace logo::globals */
#pragma endregion

#pragma pack(pop)


#pragma region Functions
namespace lego::file {

/// PUBLIC:
// This function is guaranteed to fail if `insistOnCD` is true, due to some logic errors.
// The argument `wadBasename` determines the name of WAD files to look for: "<wadBasename>#.wad".
//  This is always the same as the base executable name (without extension, i.e. "LegoRR").
// <LegoRR.exe @0047f3f0>
void __cdecl InitFileSystem(const char* wadBasename, BOOL insistOnCD, const char* regKey);

/// PRIVATE:
// <LegoRR.exe @0047f7b0>
BOOL __cdecl Path_CheckForCDROM(void);
// <LegoRR.exe @0047f850>
BOOL __cdecl Path_SetDataDir(const char* dirname);

/// PRIVATE: visible to WAD.c
// <LegoRR.exe @0047f8c0>
void __cdecl File__logf(const char* format, ...);

// <LegoRR.exe @0047f900>
int __cdecl File_OpenWAD(const char* filename);
// <LegoRR.exe @0047f920>
BOOL __cdecl Path_GetCDROMDataPath(char* out_filepath, const char* filename)
// <LegoRR.exe @0047f960>
int __cdecl Path_MakeDataSubdir(const char* dirname);
// <LegoRR.exe @0047f9a0>
FileStream* __cdecl File_Open(const char* in_filename, const char* mode);
// <LegoRR.exe @0047fb10>
int __cdecl File_Seek(FileStream* file, long offset, int origin);
// <LegoRR.exe @0047fc40>
size_t __cdecl File_Read(void* out_buffer, size_t size, size_t count, FileStream* file);
// <LegoRR.exe @0047fd10>
size_t __cdecl File_Write(const void* buffer, size_t size, size_t count, FileStream* file);
// <LegoRR.exe @0047fd80>
int __cdecl File_Close(FileStream* file);
// <LegoRR.exe @0047fdd0>
long __cdecl File_Tell(FileStream* file);
// <LegoRR.exe @0047fe20>
BOOL __cdecl File_Exist(const char* filename);
// <LegoRR.exe @0047fee0>
int __cdecl File_GetC(FileStream* file);
// <LegoRR.exe @0047ff60>
long __cdecl File_GetLength(FileStream* file);

/// PRIVATE:
// <LegoRR.exe @0047ffa0>
char* __cdecl File_GetS_WAD__internal(char* out_str, int num, FileStream* file);

/// PUBLIC:
// <LegoRR.exe @00480000>
char* __cdecl File_GetS(char* out_str, int num, FileStream* file);
// <LegoRR.exe @00480070>
int __cdecl File_PrintF(FileStream* file, const char* format, ...);

/// PRIVATE: [might be public, but unused]
// <LegoRR.exe @004800e0>
FileLocation __cdecl File_GetLocation(FileStream* file);
// <LegoRR.exe @004800f0>
FileLocation __cdecl File_FindLocation(const char* filename, const char* mode);
/// PRIVATE:
// <LegoRR.exe @00480160>
BOOL __cdecl File_OpenWADEntry(FileWADStream* wadStream, const char* filename);
// <LegoRR.exe @00480190>
FileStream* __cdecl File__Create(FileLocation location);
// <LegoRR.exe @004801f0>
void* __cdecl File__malloc(size_t size);
// <LegoRR.exe @00480200>
void __cdecl File__free(void* ptr);
// <LegoRR.exe @00480210>
void __cdecl File__Destroy(FileStream* file);
// <LegoRR.exe @00480280>
const char* __cdecl Path_StripDataDir(const char* filename);

/// PUBLIC:
// Identical to `File_GetS`, but removes the line terminator ("\n" or "\r\n") from the string.
// <LegoRR.exe @00480310>
char* __cdecl File_ReadLine(char* out_str, int num, FileStream* file);
// <LegoRR.exe @00480360>
unsigned char* __cdecl File_ReadAllBytes(const char* filename, unsigned int* out_length);
// <LegoRR.exe @00480380>
void* __cdecl File_ReadAll(const char* filename, unsigned int* out_length, BOOL isBinary);
// Opens and reads a file all at once and returns a handle to be used with the "SharedBuffers" API.
// <LegoRR.exe @00480430>
int __cdecl File_OpenSharedBuffer(const char* filename, unsigned int* out_length);
// <LegoRR.exe @004804e0>
const char* __cdecl Path_JoinDataDir(const char* filename);
// <LegoRR.exe @00480570>
void __cdecl File_SetOpenCallback(FileOpenCallback callback, void* lpValue);
// <LegoRR.exe @00480590>
void __cdecl Scan_ReadDataDirList(const char* listFilename);
// <LegoRR.exe @00480650>
void __cdecl Scan_Directory(const char* dirname);
// <LegoRR.exe @00480830>
int __cdecl Scan_File(const char* filename);

} /* namespace lego::file */
#pragma endregion

