// Files.h : 
//

#pragma once

#include "../Common.h"


namespace lego {
namespace file {

#pragma region Types

enum FileLocation : int
{
	FILELOC_WAD   = 0,
	FILELOC_STD   = 1,
	FILELOC_ERROR = 2,
};

enum WADEntryFlags : unsigned int
{
	WADENTRY_NONE       = 0,

	WADENTRY_STORE      = 0x1, // common value seen for all entries (flag is never observed, just seen in file)
	WADENTRY_COMPRESSED = 0x2, // file is stored using RNC (Rob Northern Compression)
};
DEFINE_ENUM_FLAG_OPERATORS(WADEntryFlags)

enum FileBufferFlags : unsigned int
{
	FILEBUFFER_NONE = 0,

	FILEBUFFER_ISUSED = 0x1,
	//FILEBUFFER_UNK_2  = 0x2,
	//FILEBUFFER_UNK_4  = 0x4,
	//FILEBUFFER_UNK_8  = 0x8,
};
DEFINE_ENUM_FLAG_OPERATORS(FileBufferFlags)


struct WADEntry
{
	/*00,4*/ WADEntryFlags flags;    // (always observed as 0x1, which is assumed to be "STORE"?)
	/*04,4*/ unsigned int pack_size; // size in WAD file
	/*08,4*/ unsigned int orig_size; // original decompressed file size
	/*0c,4*/ unsigned int offset;    // absolute file offset to data
	/*10*/
};

struct WADFile
{
	/*00,4*/ unsigned int field_0;
	/*04,4*/ BOOL isUsed; // 1 if in-use
	/*08,4*/ unsigned int field_8;
	/*0c,4*/ unsigned int field_c;
	/*10,4*/ FILE* file; // file is kept open on sucessful read
	/*14,4*/ char** absdirs /*[count]*/; // absolute paths when WAD was built
	/*18,4*/ char** reldirs /*[count]*/; // file paths relative to WAD
	/*1c,4*/ WADEntry* entries /*[count]*/;
	/*20,4*/ int count;
	/*24*/
};

struct SharedWADEntry
{
	/*00,4*/ void* fileData;
	/*04,4*/ BOOL isUsed;
	/*08,4*/ int wadIndex;
	/*0c,4*/ int entryIndex;
	/*10*/
};

struct WADEntryStream
{
	/*0,4*/ int sharedIndex; // index of SharedWADEntry in global table
	/*4,4*/ int position;
	/*8,4*/ unsigned int field_8;
	/*c*/
};

struct FileStream
{
	/*0,4*/ FileLocation location;
	/*4,4*/ union {
		FILE* std; // (referred to as STD "standard" file by engine)
		WADEntryStream* wad;
	};
	/*8*/
};

struct SharedFileBuffer
{
	/*0,4*/ void* fileData;
	/*4,4*/ FileBufferFlags flags; // 0x1 == BOOL isUsed
	/*8*/
};

// arguments are: filename, fileSize, lpValue (value passed to File_SetOpenCallback)
typedef void(__cdecl* FileOpenCallback)(const char* filename, int length, void* lpContext);

//// Only usage of the above FileFuncPtr
//// <LegoRR.exe @0044e180>
//void __cdecl File_funcPtrCallback__0044e180(const char* filename, int length, void* lpContext);

#pragma endregion


#pragma region Globals

namespace globals {
} /* namespace globals */

#pragma endregion


#pragma region Functions

// gameName may actually be gamepath (as called from the commandline arguments)
// 
// <LegoRR.exe @0047f3f0>
void __cdecl InitFileSystem(const char* gameName, BOOL insistOnCD, const char* regKey);

// Checks for a currently-inserted CDROM drive containing the file "CDROM:\Data\cd.key"
// Does not actually check contents of the file.
// Returns true when found, and assigns global: char g_CDROM_DriveLetter;
// 
// <LegoRR.exe @0047f7b0>
BOOL __cdecl Path_CheckForCDROM(void);

// <LegoRR.exe @0047f850>
BOOL __cdecl Path_SetDataDir(const char* dirname);

// Open WAD filename and log something (that was removed on release build)
// returns idx of newly opened WAD (0-9), or -1 on failure of any kind.
//
// <LegoRR.exe @0047f900>
int __cdecl WAD_Open(const char* filename);

// <LegoRR.exe @0047f920>
BOOL __cdecl Path_GetCDROMDataPath(char* out_filepath, const char* filename);

// <LegoRR.exe @0047f960>
int __cdecl Path_MakeDataSubdir(const char* dirname);

// <LegoRR.exe @0047f9a0>
FileStream* __cdecl File_Open(const char* in_filename, const char* mode);

// <LegoRR.exe @0047fb10>
int __cdecl File_Seek(FileStream* file, long int offset, int origin);

// <LegoRR.exe @0047fc40>
size_t __cdecl File_Read(void* out_ptr, size_t size, size_t count, FileStream* file);

// <LegoRR.exe @0047fd10>
size_t __cdecl File_Write(const void* ptr, size_t size, size_t count, FileStream* file);

// <LegoRR.exe @0047fd80>
int __cdecl File_Close(FileStream* file);

// <LegoRR.exe @0047fdd0>
long int __cdecl File_Tell(FileStream* file);

// <LegoRR.exe @0047fe20>
BOOL __cdecl File_Exist(const char* filename);

// <LegoRR.exe @0047fee0>
int __cdecl File_GetC(FileStream* file);

// <LegoRR.exe @0047ff60>
long int __cdecl File_GetLength(FileStream* file);

// <LegoRR.exe @0047ffa0>
char* __cdecl WAD_GetS__internal(char* out_str, int num, FileStream* file);

// <LegoRR.exe @00480000>
char* __cdecl File_GetS(char* out_str, int num, FileStream* file);

// <LegoRR.exe @00480070>
int __cdecl File_PrintF(FileStream* file, const char* format, ...);

// <LegoRR.exe @004800e0>
FileLocation __cdecl File_GetLocation(FileStream* file);

// Returns 0 if file is found in WAD
// Returns 1 if arguments are valid and mode is "r"/"R".
// Otherwise, returns 0.
// 
// <LegoRR.exe @004800f0>
FileLocation __cdecl File_FindLocation(const char* filename, const char* mode);


// <LegoRR.exe @00480160>
BOOL __cdecl WAD_EntryOpen__internal(WADEntryStream* wadStream, const char* filename);

// <LegoRR.exe @00480190>
FileStream* __cdecl File__New(FileLocation location);

// <LegoRR.exe @004801f0>
void* __cdecl File__New__alloc(size_t size);

// <LegoRR.exe @00480200>
void __cdecl File__New__free(void* ptr);

// <LegoRR.exe @00480210>
void __cdecl File__Dispose(FileStream* file); // something like File_Close_internal

// Strips the Data directory from the filename path, using global g_FILEPATH_DATADIR_1 as a comparison.
// Returns a temporary buffer that must be used before this function is next called.
// 
// <LegoRR.exe @00480280>
const char* __cdecl Path_StripDataDir(const char* filename);

// all parameters are directly passed to File_GetS, then some operation on string is performed
// 
// <LegoRR.exe @00480310>
char* __cdecl File_GetS_StripLineEnd(char* out_str, int num, FileStream* file);

// <LegoRR.exe @00480360>
unsigned char* __cdecl File_ReadAllBytes(const char* filename, unsigned int* out_length);

// <LegoRR.exe @00480380>
unsigned char* __cdecl File_ReadAll(const char* filename, unsigned int* out_length, BOOL isBinary);

// <LegoRR.exe @00480430>
int __cdecl File_SharedOpen(const char* filename, size_t* out_length);

// Join filename path with global g_FILEPATH_DATADIR_2.
// Returns a temporary buffer that must be used before this function is next called.
// 
// <LegoRR.exe @004804e0>
const char* __cdecl Path_JoinDataDir(const char* filename);


// <LegoRR.exe @00480570>
void __cdecl File_SetOpenCallback(FileOpenCallback callback, void* lpValue);

/*// <LegoRR.exe @00480590>
void __cdecl Path_ScanRealFiles__UNK__00480590(const char* filename);

// <LegoRR.exe @00480650>
void __cdecl File_Find(const char* dirname);

// called by File_Find
// 
// <LegoRR.exe @00480830>
void __cdecl FUN_00480830(const char* filename);*/

// <LegoRR.exe @00480590>
void __cdecl Scan_ReadDataDirList(const char* filename);

// <LegoRR.exe @00480650>
void __cdecl Scan_Directory(const char* dirname);

// Chances are high that there was a preprocessor-removed functionality in here.
// This straight up does nothing, because not even the return is used.
// <LegoRR.exe @00480830>
int __cdecl Scan_File(const char* filename);

// called in one of the LegoRR main initialization functions <LegoRR.exe @00477a60>
// 
// <LegoRR.exe @004896b0>
void __cdecl InitSharedFileBuffers(void);

// <LegoRR.exe @004896d0>
int __cdecl File_SharedOpen__internal(size_t size);

// <LegoRR.exe @00489720>
void __cdecl File_SharedClose(int sharedIndex);

// <LegoRR.exe @00489760>
unsigned char* __cdecl File_SharedGetData(int sharedIndex);

// <LegoRR.exe @0048b520>
void __cdecl InitFileScanning(void);

// <LegoRR.exe @0048b540>
void __cdecl Scan_SetIsFullScreen(BOOL isFullScreen);

// <LegoRR.exe @0048b550>
void __cdecl Scan_Cleanup(void);

// <LegoRR.exe @0048b5b0>
void __cdecl Scan_WriteDataDirList(void);

// Open and read data into WAD file.
// returns idx of newly opened WAD (0-9), or -1 on failure of any kind.
// 
// <LegoRR.exe @0048b7a0>
int __cdecl WAD_Open__internal(const char* filename);

// Returns LegoWADFile at wadIndex in table. (0-9)
// 
// <LegoRR.exe @0048bfa0>
WADFile* __cdecl WAD_Get(int wadIndex);

// <LegoRR.exe @0048bfb0>
size_t __cdecl WAD_GetEntrySize(int wadIndex, int entryIndex);

// <LegoRR.exe @0048bfd0>
size_t __cdecl WAD_GetEntryPackedSize(int wadIndex, int entryIndex);

// <LegoRR.exe @0048bff0>
int __cdecl WAD_Shared__Next(void);

// Returns the file index found 
// Returns -1 on failure or not found.
// 
// <LegoRR.exe @0048c010>
int __cdecl WAD_FindEntry(const char* filename, int opt_wadIndex = -1);

// Returns the file index in the specified WAD matching the reldir filepath.
// Returns -1 on failure or not found.
// 
// <LegoRR.exe @0048c060>
int __cdecl WAD_FindEntry__InWAD(const char* filename, int wadIndex);

// Returns idx of next available LegoWADFile in table (0-9). -1 when none are available.
//
// <LegoRR.exe @0048c0c0>
int __cdecl WAD__Next(void);

// Reads a WAD from filename into a shared file table, and returns the index in the table
// 
// <LegoRR.exe @0048c100>
int __cdecl WAD_SharedOpen__InWAD(const char* filename, int wadIndex);

// Reads a WAD from filename into a shared file table, and returns the index in the table.
// if opt_wadIndex is -1, all WAD files will be searched for the file name
// 
// <LegoRR.exe @0048c230>
int __cdecl WAD_SharedOpen(const char* filename, int opt_wadIndex = -1);

// <LegoRR.exe @0048c280>
void __cdecl WAD_Shared__Dispose(int sharedIndex);

// <LegoRR.exe @0048c2b0>
unsigned char* __cdecl WAD_SharedGetData__internal(int sharedIndex);

// <LegoRR.exe @0048c2d0>
unsigned int __cdecl WAD_SharedGetSize(int sharedIndex);

// <LegoRR.exe @0048c2f0>
unsigned char* __cdecl WAD_SharedGetData(int sharedIndex);

// RNC (Rob Northern Compression)
// Haven't really looked into this, but it's called when WADEntry.version & 0x2 flag is set... weird
// Maybe it's the SafeDisc CD DRM garbage...?
// 
// <LegoRR.exe @0049ca80>
size_t __cdecl RNC_Decompress(unsigned char* srcBuffer, unsigned char** out_dstBuffer);

// <LegoRR.exe @0049cb00>
int __cdecl RNC_Decompress__internal(unsigned char* srcBuffer, unsigned char* dstBuffer);

#pragma endregion


} /* namespace file */
} /* namespace lego */
