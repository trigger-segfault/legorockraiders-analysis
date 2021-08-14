// WAD.h : Declares WAD file reading functions.
//
/// STATUS: [COMPLETE]
/// PURPOSE: Functions to open and access file entry data contained within WAD files.
///          This is wrapped entirely within the FileSystem ("Files.h") manager.
///
/// NAMESPACE: lego::wad
/// INITIALIZE: (none)
/// GLOBALS: private

#pragma once

#include "Common.h"


#pragma region Defines

// Maximum number of open WAD files.
#define WADFILES_COUNT 10
// Maximum number of simultaneously open WADStreams... *yikes*
#define WADSTREAMS_COUNT 100
// Signifies a "NULL" WADStreamHandle value.
#define WADSTREAM_INVALID -1

#pragma endregion


#pragma region Flags
namespace lego {

/// PRIVATE:
enum WADEntryFlags : unsigned int
{
	WADENTRY_NONE       = 0,

	WADENTRY_STORE      = 0x1, // common value seen for all entries (flag is never observed, just seen in file)
	WADENTRY_COMPRESSED = 0x2, // file is stored using RNC (Rob Northern Compression)
};
DEFINE_ENUM_FLAG_OPERATORS(WADEntryFlags)
static_assert(sizeof(WADEntryFlags) == 0x4, "");

} /* namespace lego::globals */
#pragma endregion


#pragma pack(push, 1)

#pragma region Types
namespace lego {

/// PRIVATE:
struct WADEntry
{
	/*00,4*/ WADEntryFlags flags;    // (always observed as 0x1, which is assumed to be "STORE"?)
	/*04,4*/ unsigned int pack_size; // size in WAD file
	/*08,4*/ unsigned int orig_size; // original decompressed file size
	/*0c,4*/ unsigned int offset;    // absolute file offset to data
	/*10*/
};
static_assert(sizeof(WADEntry) == 0x10, "");

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
static_assert(sizeof(WADFile) == 0x24, "");

struct WADStream
{
	/*00,4*/ void* fileData;
	/*04,4*/ BOOL isUsed;
	/*08,4*/ int wadIndex;
	/*0c,4*/ int entryIndex;
	/*10*/
};
static_assert(sizeof(WADStream) == 0x10, "");

} /* namespace lego */
#pragma endregion


#pragma region Globals
namespace lego::wad {

/// PRIVATE:
// <LegoRR.exe @00576500 - 00576ce0>
struct WADManager
{
	// <LegoRR.exe @00576500>
	/*000,168*/ WADFile WADFiles_TABLE[WADFILES_COUNT /*10*/];
	// (unused 56-byte gap, would have room for 11th WADFile, with some bytes leftover)
	// <LegoRR.exe @00576668>
	/*168,38*/ unsigned char reserved1[56];
	// <LegoRR.exe @005766a0>
	/*1a0,640*/ WADStream WADStreams_TABLE[WADSTREAMS_COUNT /*100*/]; // isn't this too small???
	/*7e0*/
};
static_assert(sizeof(WADManager) == 0x7e0, "");

} /* namespace lego::wad */
namespace lego::globals {
	
/// PUBLIC:
// Search for an entry in any of the currently-open WAD files.
// <LegoRR.exe @004abf00>
extern const int WADFILE_ANY;


/// PRIVATE:
// <LegoRR.exe @00576500 - 00576ce0>
extern lego::wad::WADManager g_WAD;

// /// PRIVATE:
// // <LegoRR.exe @00576500>
// extern WADFile g_WADFiles_TABLE[WADFILES_COUNT /*10*/];

// // (unused 56-byte gap, would have room for 11th WADFile, with some bytes leftover)

// // <LegoRR.exe @005766a0>
// extern WADStream g_WADStreams_TABLE[WADSTREAMS_COUNT /*100*/]; // isn't this too small???

} /* namespace lego::globals */
#pragma endregion

#pragma pack(pop)


#pragma region Functions
namespace lego::wad {

/// PRIVATE:
// NOTE: This is not a CRT function, it's again, DDI implementing a
// function that you'd commonly expect to see used.
// Read null-terminated string from file. (DOES NOT CHECK FOR EOF!!)
// always returns true.
// <LegoRR.exe @0048b760>
BOOL __cdecl WAD__ReadCString(FILE* file, char* out_str);

/// PUBLIC:
// Open and read data into WAD file.
// returns idx of newly opened WAD (0-9), or -1 on failure of any kind.
// <LegoRR.exe @0048b7a0>
int __cdecl WAD_Open(const char* filename);

/// PRIVATE:
// Returns WADFile at idx in table. (0-9)
// This feels so excessive...
// <LegoRR.exe @0048bfa0>
WADFile* __cdecl WAD_Get(int wadIndex);
// <LegoRR.exe @0048bfb0>
unsigned int __cdecl WAD_GetEntrySize(int wadIndex, int entryIndex);
// <LegoRR.exe @0048bfd0>
unsigned int __cdecl WAD_GetEntryPackedSize(int wadIndex, int entryIndex);
// <LegoRR.exe @0048bff0>
int __cdecl WAD_Stream__Next(void);

/// PUBLIC:
// Returns the file index found 
// Returns -1 on failure or not found.
// <LegoRR.exe @0048c010>
int __cdecl WAD_FindEntry(const char* filename, int opt_wadIndex);

/// PRIVATE:
// Returns the file index in the specified WAD matching the reldir filepath.
// Returns -1 on failure or not found.
// <LegoRR.exe @0048c060>
int __cdecl WAD_FindEntryInWAD(const char* filename, int wadIndex);
// Returns idx of next available LegoWADFile in table (0-9). -1 when none are available.
// <LegoRR.exe @0048c0c0>
int __cdecl WAD__Next(void);
// Reads a WAD entry by filename into a shared file table, and returns the index in the table.
// <LegoRR.exe @0048c100>
int __cdecl WAD_StreamOpenInWAD(const char* filename, int in_wadIndex);

/// PUBLIC:
// Reads a WAD entry by filename into a shared file table, and returns the index in the table.
// if opt_wadIndex is -1, all WAD files will be searched for the file name.
// <LegoRR.exe @0048c230>
int __cdecl WAD_StreamOpen(const char* filename, int opt_wadIndex);
// <LegoRR.exe @0048c280>
void __cdecl WAD_StreamClose(int streamIndex);

/// PRIVATE:
// <LegoRR.exe @0048c2b0>
void* __cdecl WAD_StreamGetData__internal(int streamIndex);

/// PUBLIC:
// <LegoRR.exe @0048c2d0>
unsigned int __cdecl WAD_StreamGetSize(int streamIndex);
// <LegoRR.exe @0048c2f0>
void* __cdecl WAD_StreamGetData(int streamIndex);

} /* namespace lego::wad */
#pragma endregion

