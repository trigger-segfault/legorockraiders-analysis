// All information supposedly related to LegoRR file I/O
// Many of the standard File_ functions that have C f_ counterparts are the REAL-deal names.
//  Their names are present in log strings, and a log string also list the file definition as Files.c

#ifndef LEGORR__FILES_H
#define LEGORR__FILES_H

#define s_Dev_SourceSafe__Files_c "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Files.c"

#include "Common.h"


#pragma region /// TYPES ////////////////////////////////

enum LegoFileLocation
{
	FILELOC_WAD = 0,
	FILELOC_REAL = 1,
	FILELOC_ERROR = 2,
};

struct LegoWADEntry
{
	/*00,4*/ unsigned int version; // field_0; // might actually be flags, 0x2 has special meaning that causes some extra functions to get called
	/*04,4*/ unsigned int size; // field_4;
	/*08,4*/ unsigned int size2; // field_8;
	/*0c,4*/ unsigned int offset; // field_c;
	/*10*/
};

struct LegoWADFile
{
	/*00,4*/ unsigned int field_0;
	/*04,4*/ BOOL isUsed; // 1 if in-use? // field_4;
	/*08,4*/ unsigned int field_8;
	/*0c,4*/ unsigned int field_c;
	/*10,4*/ FILE* file; // field_10; // file is kept open on sucessful read
	/*14,4*/ char** absdirs; // field_14;
	/*18,4*/ char** reldirs; // field_18;
	/*1c,4*/ LegoWADEntry* entries; // field_1c;
	/*20,4*/ unsigned int count; // field_20;
	/*24*/
};

struct LegoSharedWADEntry
{
	/*00,4*/ void* fileData;
	/*04,4*/ BOOL isUsed;
	/*08,4*/ int wadIndex
	/*0c,4*/ int entryIndex;
	/*10*/
};

struct LegoWADStream
{
	/*0,4*/ int sharedIndex;
	/*4,4*/ unsigned int position;
	/*8,4*/ unsigned int field_8;
	/*c*/
};

union LegoStreamType
{
    FILE* real;
	LegoWADStream* wad;
};

struct LegoFileStream
{
	/*0,4*/ LegoFileLocation location;
	/*4,4*/ LegoStreamType stream;
	/*8*/
};

struct LegoFileBuffer;
{
	/*0,4*/ void* buffer;
	/*4,4*/ unsigned int flags; // 0x1 == BOOL isUsed
	/*8*/
};

#pragma endregion


#pragma region /// DEFINES //////////////////////////////

#define WADFILES_COUNT 10
#define SHARED_WADENTRIES_COUNT 100

#pragma endregion


#pragma region /// CONSTANTS ////////////////////////////

// <LegoRR.exe @004abf00>
static int c_WAD_ANYINDEX = -1; // constant that states WAD entry lookup will check every WAD file

#pragma endregion


#pragma region /// GLOBALS //////////////////////////////

// <LegoRR.exe @00576500>
static LegoWADFile g_WADFILES_TABLE[WADFILES_COUNT /*10*/];

// <LegoRR.exe @005349a0>
static char g_FILEPATH_DATADIR_1[0x400 /*1024*/];
// <LegoRR.exe @00534da0>
static char tmp_FILEPATH_STRIPDATADIR[0x400 /*1024*/];

// <LegoRR.exe @005351a0>
static char tmp_FILEPATH_JOINDATADIR[0x108 /*264*/]; // is this actually MAX_PATH /*0x104*/ /*260*/ ??
// <LegoRR.exe @005352a8>
static char g_FILEPATH_DATADIR_2[MAX_PATH /*0x104*/ /*260*/];

// no clue on these two value yet... (maybe actually SafeDisc DRM stuff?)
// <LegoRR.exe @005353ac>
static void* g_WAD_unkFuncPtr_A_005353ac;
// <LegoRR.exe @005353b0>
static unsigned int g_WAD_unkFuncValue_A_005353b0;

// <LegoRR.exe @005353b4>
static char g_CDROM_DriveLetter;

// <LegoRR.exe @005353b8>
static BOOL g_HAS_DATADIR;

// <LegoRR.exe @005353c0>
// not used??

// <LegoRR.exe @005353c4>
static void* g_UNKPTR_STRUCT48__005353c4;

// <LegoRR.exe @00545a20 to 005498a0>
static LegoFileBuffer g_UNKFILE_BUFFERS_TABLE[2000];

// <LegoRR.exe @005766a0>
static LegoSharedWADEntry g_SHARED_WADENTRIES_TABLE[SHARED_WADENTRIES_COUNT /*100*/]; // isn't this too small???

#pragma endregion


#pragma region /// FUNCTIONS ////////////////////////////

// gamename may actually be gamepath (as called from the commandline arguments)
// 
// <LegoRR.exe @0047f3f0>
void __cdecl Path_InitDataDir(const char* gamename, BOOL insistOnCD, const char* regKey);

// Checks for a currently-inserted CDROM drive containing the file "CDROM:\Data\cd.key"
// Does not actually check contents of the file.
// Returns true when found, and assigns global: char g_CDROM_DriveLetter;
// 
// <LegoRR.exe @0047f7b0>
BOOL __cdecl Path_CheckForCDROM(void);

// <LegoRR.exe @0047f850>
void __cdecl Path_SetDataDir(const char* dirname);

// Open WAD filename and log something (that was removed on release build)
// returns idx of newly opened WAD (0-9), or -1 on failure of any kind.
//
// <LegoRR.exe @0047f900>
int __cdecl WAD_Open(char *filename);

// <LegoRR.exe @0047f920>
BOOL __cdecl Path_GetCDROMDataPath(char* out_filepath, const char* filename);

// <LegoRR.exe @0047f960>
int __cdecl Path_MakeDataSubdir(const char* dirname);

// <LegoRR.exe @0047f9a0>
LegoFileStream* __cdecl File_Open(const char* in_filename, const char* mode);

// <LegoRR.exe @0047fb10>
int __cdecl File_Seek(LegoFileStream* file, long int offset, int origin);

// <LegoRR.exe @0047fc40>
size_t __cdecl File_Read(void* out_ptr, size_t size, size_t count, LegoFileStream* file);

// <LegoRR.exe @0047fd10>
size_t __cdecl File_Write(const void* ptr, size_t size, size_t count, LegoFileStream* file);

// <LegoRR.exe @0047fd80>
int __cdecl File_Close(LegoFileStream* file);

// <LegoRR.exe @0047fdd0>
long int __cdecl File_Tell(LegoFileStream* file);

// <LegoRR.exe @0047fe20>
BOOL __cdecl File_Exist(const char* filename);

// <LegoRR.exe @0047fee0>
int __cdecl File_GetC(LegoFileStream* file);

// <LegoRR.exe @0047ff60>
long int __cdecl File_GetLength(LegoFileStream* file);

// <LegoRR.exe @0047ffa0>
char* __cdecl File_GetS__internal(char* out_str, int num, LegoFileStream* file);

// <LegoRR.exe @00480000>
char* __cdecl File_GetS(char* out_str, int num, LegoFileStream* file);

// <LegoRR.exe @00480070>
int __cdecl File_PrintF(LegoFileStream* file, const char* format, ...);

// <LegoRR.exe @004800e0>
LegoFileLocation __cdecl File_GetLocation(LegoFileStream* file);

// Returns 0 if file is found in WAD
// Returns 1 if arguments are valid and mode is "r"/"R".
// Otherwise, returns 0.
// 
// <LegoRR.exe @004800f0>
LegoFileLocation __cdecl File_FindLocation(const char* filename, const char* mode);


// <LegoRR.exe @00480160>
BOOL __cdecl WAD_EntryOpen__internal(LegoWADStream* wadStream, const char* filename);

// <LegoRR.exe @00480190>
LegoFileStream* __cdecl File__New(LegoFileLocation location);

// <LegoRR.exe @004801f0>
void* __cdecl File__New__alloc(size_t size);

// <LegoRR.exe @00480200>
void __cdecl File__New__free(void* ptr);

// <LegoRR.exe @00480210>
void __cdecl File__Dispose(LegoFileStream* file); // something like File_Close_internal

// Strips the Data directory from the filename path, using global g_FILEPATH_DATADIR_1 as a comparison.
// Returns a temporary buffer that must be used before this function is next called.
// 
// <LegoRR.exe @00480280>
const char* __cdecl Path_StripDataDir(const char* filename);

// all parameters are directly passed to File_GetS, then some operation on string is performed
// 
// <LegoRR.exe @00480310>
char* __cdecl File_UNK_calls_GetS_00480310(char* out_str, int num, LegoFileStream* file); 

// <LegoRR.exe @00480360>
unsigned char* __cdecl File_ReadAllBytes(const char* filename, unsigned int* out_length);

// <LegoRR.exe @00480380>
unsigned char* __cdecl File_ReadAll(const char* filename, unsigned int* out_length, BOOL isBinary);

// <LegoRR.exe @00480430>
int __cdecl File_UNK_ReadAllBytesTableBuffer_00480430(const char* filename, size_t* out_length);

// Join filename path with global g_FILEPATH_DATADIR_2.
// Returns a temporary buffer that must be used before this function is next called.
// 
// <LegoRR.exe @004804e0>
const char* __cdecl Path_JoinDataDir(const char* filename);


// <LegoRR.exe @00480570>
void __cdecl WAD_setFunctPtrValue_A__00480570(void* unkFuncPtr, unsigned int unkValue);

// <LegoRR.exe @00480590>
void __cdecl Path_ScanRealFiles__UNK__00480590(const char* filename);

// <LegoRR.exe @00480650>
void __cdecl File_Find(const char* dirname);

// called by File_Find
// 
// <LegoRR.exe @00480830>
void __cdecl FUN_00480830(const char* filename);

// called in one of the LegoRR main initialization functions <LegoRR.exe @00477a60>
// 
// <LegoRR.exe @004896b0>
void __cdecl File_UNK_InitTableBuffers_004896b0(void);

// <LegoRR.exe @004896d0>
int __cdecl File_UNK_AllocTableBuffer_004896d0(size_t size);

// <LegoRR.exe @00489720>
void __cdecl File_UNK_FreeTableBuffer_00489720(unsigned int index);

// <LegoRR.exe @00489760>
void* __cdecl File_UNK_GetTableBuffer_00489760(unsigned int index);

// Open and read data into WAD file.
// returns idx of newly opened WAD (0-9), or -1 on failure of any kind.
// 
// <LegoRR.exe @0048b7a0>
int __cdecl WAD_Open__internal(const char* filename);

// Returns LegoWADFile at wadIndex in table. (0-9)
// 
// <LegoRR.exe @0048bfa0>
LegoWADFile* __cdecl WAD_Get(int wadIndex);

// <LegoRR.exe @0048bfb0>
size_t __cdecl WAD_GetEntrySize2(int wadIndex, int entryIndex);

// <LegoRR.exe @0048bfd0>
size_t __cdecl WAD_GetEntrySize(int wadIndex, int entryIndex);

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
unsigned int __cdecl WAD_SharedGetSize2(int sharedIndex);

// <LegoRR.exe @0048c2f0>
unsigned char* __cdecl WAD_SharedGetData(int sharedIndex);

// Haven't really looked into this, but it's called when WADEntry.version & 0x2 flag is set... weird
// Maybe it's the SafeDisc CD DRM garbage...?
// 
// <LegoRR.exe @0049ca80>
size_t __cdecl WAD_UNK_Decompress__0049ca80(unsigned char* srcBuffer, unsigned char** out_dstBuffer);

// <LegoRR.exe @0049cb00>
int __cdecl WAD_UNK_Decompress__internal__0049cb00(unsigned char* srcBuffer, unsigned char* dstBuffer);

#pragma endregion


#endif /* LEGORR__FILES_H */
