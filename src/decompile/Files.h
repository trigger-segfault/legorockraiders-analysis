#pragma once
// #include "WAD.h"

namespace lego {

#pragma region Defines

#define s_Dev_SourceSafe__Files_c "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c"

#define SHARED_FILEBUFFERS_COUNT 2000

#pragma endregion


#pragma region Enums

/// PUBLIC:
enum FileLocation : int
{
	FILELOC_WAD   = 0,
	FILELOC_STD   = 1,
	FILELOC_ERROR = 2,
};

#pragma endregion


#pragma region Flags

/// INTERNAL:
enum FileBufferFlags : unsigned int
{
	FILEBUFFER_NONE = 0,

	FILEBUFFER_ISUSED = 0x1,
	//FILEBUFFER_UNK_2  = 0x2,
	//FILEBUFFER_UNK_4  = 0x4,
	//FILEBUFFER_UNK_8  = 0x8,
};
DEFINE_ENUM_FLAG_OPERATORS(FileBufferFlags)


#pragma endregion


#pragma region Types

/// INTERNAL:
struct FileWADStream
{
	/*0,4*/ int streamIndex; // index of SharedWADEntry in global table
	/*4,4*/ int position;
	/*8,4*/ uint field_8;
	/*c*/
};

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

/// INTERNAL:
struct SharedFileBuffer
{
	/*0,4*/ void* fileData;
	/*4,4*/ FileBufferFlags flags; // 0x1 == BOOL isUsed
	/*8*/
};

// arguments are: filename, fileSize, lpValue (value passed to File_SetOpenCallback)
typedef void (__cdecl* FileOpenCallback)(const char* filename, uint fileSize, void* lpContext);

#pragma endregion


#pragma region Globals
namespace globals {

	/// INTERNAL:
	// <LegoRR.exe @005349a0>
	extern char g_FILEPATH_DATADIR_STRIP[1024];
	// <LegoRR.exe @00534da0>
	extern char tmp_FILEPATH_STRIPDATADIR[1024];

	// (unused 4-byte gap)

	// <LegoRR.exe @005351a0>
	extern char tmp_FILEPATH_JOINDATADIR[MAX_PATH /*260*/];
	// <LegoRR.exe @005352a8>
	extern char g_FILEPATH_DATADIR_JOIN[MAX_PATH /*260*/];

	// no clue on these two value yet... (maybe actually SafeDisc DRM stuff?)
	// <LegoRR.exe @005353ac>
	extern FileOpenCallback g_FileOpenCallback;
	// <LegoRR.exe @005353b0>
	extern void* g_FileOpenCallback_VALUE;

	// <LegoRR.exe @005353b4>
	extern char g_CDROMDriveLetter;

	// (unused 4-byte gap)
	
	// <LegoRR.exe @005353b8>
	extern BOOL g_HasDataDir;

	// <LegoRR.exe @005353c0>
	// not used??

	/// TODO: move everything below to its respective file

	// <LegoRR.exe @00545a20 -> 005498a0>
	extern SharedFileBuffer g_SHARED_FILEBUFFERS_TABLE[SHARED_FILEBUFFERS_COUNT /*2000*/];


	// <LegoRR.exe @00576ce0>
	extern FileStream* g_ScanFileStream_1;
	// <LegoRR.exe @00576ce4>
	extern FileStream* g_ScanFileStream_2;
	// <LegoRR.exe @00576ce8>
	extern FileStream* g_ScanFileStream_3;
	// <LegoRR.exe @00576cec>
	extern FileStream* g_ScanFileStream_OutputList;
	// <LegoRR.exe @00576cf0>
	extern char g_ScanFilename_InputList[1024];
	// <LegoRR.exe @005770f0>
	extern char g_ScanFilename_OutputList[1024];
	
	// <LegoRR.exe @005774f4>
	extern BOOL g_ScanIsFullScreen;

	// <LegoRR.exe @005779e0>
	extern char g_ScanRealFiles_FilePaths_TABLE[2000][1024];
	// <LegoRR.exe @0076b9e0>
	extern uint g_ScanRealFiles_FilePaths_COUNT;

} /* namespace globals */
#pragma endregion


#pragma region Functions
namespace file {

/// PUBLIC:
// <LegoRR.exe @0047f3f0>
void __cdecl InitFileSystem(const char* gameName, BOOL insistOnCD, const char* regKey);

/// INTERNAL:
// <LegoRR.exe @0047f7b0>
BOOL __cdecl Path_CheckForCDROM(void);
// <LegoRR.exe @0047f850>
BOOL __cdecl Path_SetDataDir(const char* dirname);

/// PUBLIC: Also visible to WAD.c
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
int __cdecl File_Seek(FileStream* file, int offset, int origin);
// <LegoRR.exe @0047fc40>
uint __cdecl File_Read(void* out_buffer, uint size, uint count, FileStream* file);
// <LegoRR.exe @0047fd10>
uint __cdecl File_Write(const void* buffer, uint size, int count, FileStream* file);
// <LegoRR.exe @0047fd80>
int __cdecl File_Close(FileStream* file);
// <LegoRR.exe @0047fdd0>
int __cdecl File_Tell(FileStream* file);
// <LegoRR.exe @0047fe20>
BOOL __cdecl File_Exist(const char* filename);
// <LegoRR.exe @0047fee0>
int __cdecl File_GetC(FileStream* file);
// <LegoRR.exe @0047ff60>
int __cdecl File_GetLength(FileStream* file);

/// INTERNAL:
// <LegoRR.exe @0047ffa0>
char* __cdecl File_GetS_WAD__internal(char* out_str, int num, FileStream* file);

/// PUBLIC:
// <LegoRR.exe @00480000>
char* __cdecl File_GetS(char* out_str, int num, FileStream* file);
// <LegoRR.exe @00480070>
int __cdecl File_PrintF(FileStream* file, const char* format, ...);

/// INTERNAL:
// <LegoRR.exe @004800e0>
FileLocation __cdecl File_GetLocation(FileStream* file);
// <LegoRR.exe @004800f0>
FileLocation __cdecl File_FindLocation(const char* filename, const char* mode);
// <LegoRR.exe @00480160>
BOOL __cdecl File_OpenWADEntry(FileWADStream* wadStream, const char* filename);
// <LegoRR.exe @00480190>
FileStream* __cdecl File__New(FileLocation location);
// <LegoRR.exe @004801f0>
void* __cdecl File__malloc(uint size);
// <LegoRR.exe @00480200>
void __cdecl File__free(void* ptr);
// <LegoRR.exe @00480210>
void __cdecl File__Dispose(FileStream* file);
// <LegoRR.exe @00480280>
const char* __cdecl Path_StripDataDir(const char* filename);

/// PUBLIC:
// <LegoRR.exe @00480310>
char* __cdecl File_GetS_StripLineEnd(char* out_str, int num, FileStream* file);
// <LegoRR.exe @00480360>
byte* __cdecl File_ReadAllBytes(const char* filename, uint* out_length);
// <LegoRR.exe @00480380>
byte* __cdecl File_ReadAll(const char* filename, uint* out_length, BOOL isBinary);
// <LegoRR.exe @00480430>
int __cdecl File_BufferOpen(const char* filename, uint* out_length);
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

} /* namespace file */
#pragma endregion


} /* namespace lego */
