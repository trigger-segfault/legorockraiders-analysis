#pragma once


namespace lego {

#pragma region Defines

// Maximum number of open WAD files.
#define WADFILES_COUNT 10
// Maximum number of simultaneously open WADStreams... *yikes*
#define WADSTREAMS_COUNT 100
// Signifies a "NULL" WADStreamHandle value.
#define WADSTREAM_INVALID -1
// #define WADSTREAM_INVALID ((WADStreamHandle)-1)

#pragma endregion


#pragma region Flags

/// INTERNAL:
enum WADEntryFlags : unsigned int
{
	WADENTRY_NONE       = 0,

	WADENTRY_STORE      = 0x1, // common value seen for all entries (flag is never observed, just seen in file)
	WADENTRY_COMPRESSED = 0x2, // file is stored using RNC (Rob Northern Compression)
};
DEFINE_ENUM_FLAG_OPERATORS(WADEntryFlags)

#pragma endregion


#pragma region Types

/// INTERNAL:
struct WADEntry
{
	/*00,4*/ WADEntryFlags flags;    // (always observed as 0x1, which is assumed to be "STORE"?)
	/*04,4*/ uint pack_size; // size in WAD file
	/*08,4*/ uint orig_size; // original decompressed file size
	/*0c,4*/ uint offset;    // absolute file offset to data
	/*10*/
};

struct WADFile
{
	/*00,4*/ uint field_0;
	/*04,4*/ BOOL isUsed; // 1 if in-use
	/*08,4*/ uint field_8;
	/*0c,4*/ uint field_c;
	/*10,4*/ FILE* file; // file is kept open on sucessful read
	/*14,4*/ char** absdirs /*[count]*/; // absolute paths when WAD was built
	/*18,4*/ char** reldirs /*[count]*/; // file paths relative to WAD
	/*1c,4*/ WADEntry* entries /*[count]*/;
	/*20,4*/ int count;
	/*24*/
};

struct WADStream
{
	/*00,4*/ void* fileData;
	/*04,4*/ BOOL isUsed;
	/*08,4*/ int wadIndex;
	/*0c,4*/ int entryIndex;
	/*10*/
};

//typedef int WADStreamHandle;

#pragma endregion


#pragma region Globals
namespace globals {
	
	/// PUBLIC:
	// Search for an entry in any of the currently-open WAD files.
	// <LegoRR.exe @004abf00>
	extern const int WADFILE_ANY;

	/// INTERNAL:
	// <LegoRR.exe @00576500>
	extern WADFile g_WADFiles_TABLE[WADFILES_COUNT /*10*/];

	// (unused 0x38-byte gap, would have room for 11th WADFile)

	// <LegoRR.exe @005766a0>
	extern WADStream g_WADStreams_TABLE[WADSTREAMS_COUNT /*100*/]; // isn't this too small???

} /* namespace globals */
#pragma endregion


#pragma region Functions
namespace wad {

/// INTERNAL:
// NOTE: This is not a CRT function, it's again, DDI(?) implementing a
// function that you'd commonly expect to see used.
// Read null-terminated string from file. (DOES NOT CHECK FOR EOF!!)
// always returns true.
// 
// <LegoRR.exe @0048b760>
BOOL __cdecl WAD_freadstr(FILE* file, char* out_str);

/// PUBLIC:
// <LegoRR.exe @0048b7a0>
int __cdecl WAD_Open(const char* filename);

/// INTERNAL:
// <LegoRR.exe @0048bfa0>
WADFile* __cdecl WAD_Get(int wadIndex);
// <LegoRR.exe @0048bfb0>
uint __cdecl WAD_GetEntrySize(int wadIndex, int entryIndex);
// <LegoRR.exe @0048bfd0>
uint __cdecl WAD_GetEntryPackedSize(int wadIndex, int entryIndex);
// <LegoRR.exe @0048bff0>
int __cdecl WAD_Stream__Next(void);

/// PUBLIC:
// <LegoRR.exe @0048c010>
int __cdecl WAD_FindEntry(const char* filename, int opt_wadIndex);

/// INTERNAL:
// <LegoRR.exe @0048c060>
int __cdecl WAD_FindEntryInWAD(const char* filename, int wadIndex);
// <LegoRR.exe @0048c0c0>
int __cdecl WAD__Next(void);
// <LegoRR.exe @0048c100>
int __cdecl WAD_StreamOpenInWAD(const char* filename, int in_wadIndex);

/// PUBLIC:
// <LegoRR.exe @0048c230>
int __cdecl WAD_StreamOpen(const char* filename, int opt_wadIndex);
// <LegoRR.exe @0048c280>
void __cdecl WAD_StreamClose(int streamIndex);

/// INTERNAL:
// <LegoRR.exe @0048c2b0>
void* __cdecl WAD_StreamGetData__internal(int streamIndex);

/// PUBLIC:
// <LegoRR.exe @0048c2d0>
uint __cdecl WAD_StreamGetSize(int streamIndex);
// <LegoRR.exe @0048c2f0>
void* __cdecl WAD_StreamGetData(int streamIndex);

} /* namespace wad */
#pragma endregion


} /* namespace lego */
