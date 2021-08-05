#include "WAD.h"
// Only needed for File__logf <0047f8c0>
#include "Files.h"

using namespace lego;
using namespace lego::wad;


// #pragma region Defines

// #define WAD_SIGNATURE "WWAD"

// #pragma endregion


#pragma region Globals

// Search for an entry in any of the currently-open WAD files.
// <LegoRR.exe @004abf00>
const int lego::wad::WADFILE_ANY = -1;

// <LegoRR.exe @00576500>
WADFile lego::wad::g_WADFiles_TABLE[WADFILES_COUNT /*10*/];

// <LegoRR.exe @005766a0>
WADStream lego::wad::g_WADStreams_TABLE[WADSTREAMS_COUNT /*100*/]; // isn't this too small???

#pragma endregion


#pragma region Functions

// NOTE: This is not a CRT function, it's again, DDI implementing a
// function that you'd commonly expect to see used.
// Read null-terminated string from file. (DOES NOT CHECK FOR EOF!!)
// always returns true.
// 
// <LegoRR.exe @0048b760>
BOOL __cdecl lego::wad::WAD_freadstr(FILE* file, char* out_str)
{
	/// this doesn't even check for EOF... BAD BAD BAD!
	/// SANITY: check for -1 (EOF)
	char c = (char)std::fgetc(file);
	while (c != '\0') {
		*out_str++ = c;
		c = (char)std::fgetc(file);
	}
	*out_str = '\0'; // null-terminate
	return true;
}

// Open and read data into WAD file.
// returns idx of newly opened WAD (0-9), or -1 on failure of any kind.
// 
// <LegoRR.exe @0048b7a0>
int __cdecl lego::wad::WAD_Open(const char* filename)
{
	char signature[4];

	int idx = WAD__Next(); // prepare and get next available WAD index
	if (idx == -1) {
		/// FAIL: no more WAD files to load (max 10 can be loaded at once)
		return -1; //goto WADOpen_end;
	}

	FILE* file = std::fopen(filename, "rb");
	WAD_Get(idx)->file = file;
	if (file == nullptr) {
		/// FAIL: could not open WAD file
		return -1; //goto WADOpen_end;
	}

	WAD_Get(idx)->isUsed = true;

	// signature check "WWAD"
	if (std::fread(signature, 1, 4, file) != 4 || std::memcmp(signature, "WWAD", 4) != 0) {
		/// FAIL: could not read file signature, or signature did not match "WWAD"
		goto WADOpen_close;
	}

	// read number of file entries
	if (std::fread(&WAD_Get(idx)->count, 1, 4, file) != 4) {
		/// FAIL: could not read file entry count
		goto WADOpen_close;
	}

	// allocate buffers to store relative and absolute entry file paths
	WAD_Get(idx)->reldirs = (char**)std::malloc(WAD_Get(idx)->count * sizeof(char*)); // count * 4 (probably for pointers)
	WAD_Get(idx)->absdirs = (char**)std::malloc(WAD_Get(idx)->count * sizeof(char*)); // count * 4 (probably for pointers)
	if (WAD_Get(idx)->reldirs == nullptr || WAD_Get(idx)->absdirs == nullptr) {
		/// FAIL: could not allocate reldirs or absdirs buffers
		goto WADOpen_allocs;
	}

	// zero out memory, so that, on failure, we don't try to free strings that haven't yet been allocated
	std::memset(WAD_Get(idx)->reldirs, 0, WAD_Get(idx)->count * sizeof(char*)); // count * 4
	std::memset(WAD_Get(idx)->absdirs, 0, WAD_Get(idx)->count * sizeof(char*)); // count * 4

	char strBuffer[4096]; // temp buffer used for reading C-String reldirs/absdirs one-by-one

	// read WAD file relative directories
	for (int i = 0; i < (int)WAD_Get(idx)->count; i++) {
		if (!WAD_freadstr(file, strBuffer)) {
			/// FAIL: could not read cstring
			// although WAD_freadstr never returns false...
			goto WADOpen_reldirs;
		}

		WAD_Get(idx)->reldirs[i] = ::_strdup(strBuffer);
		file::File__logf("%s\n", WAD_Get(idx)->reldirs[i]);
	}

	// read WAD file absolute directories
	for (int i = 0; i < (int)WAD_Get(idx)->count; i++) {
		if (!WAD_freadstr(file, strBuffer)) {
			/// FAIL: could not read cstring
			// although WAD_freadstr never returns false...
			goto WADOpen_absdirs;
		}

		WAD_Get(idx)->absdirs[i] = ::_strdup(strBuffer);
		file::File__logf("%s\n", WAD_Get(idx)->absdirs[i]);
	}

	// read WAD file entry metadata
	WAD_Get(idx)->entries = (WADEntry*)std::malloc(WAD_Get(idx)->count * sizeof(WADEntry)); // count * 4
	if (WAD_Get(idx)->entries == nullptr) {
		/// FAIL: could not allocate entries buffer
		goto WADOpen_absdirs;
	}

	// read in entry data directly from file into entries buffer
	if (std::fread(WAD_Get(idx)->entries, 1, WAD_Get(idx)->count * sizeof(WADEntry), file) // count * 16
		== (WAD_Get(idx)->count * sizeof(WADEntry))) // count * 16
	{
		// successfully read all entries. WE'RE DONE!!!!!!
		return idx;
	}

	/// FAIL: could not read entire file entries buffer

//WADOpen_entries:
	if (WAD_Get(idx)->entries != nullptr) {
		std::free(WAD_Get(idx)->entries);
	}

WADOpen_absdirs:
	// failure, clean up half-finished WAD file reading
	// although WAD_freadstr never returns false...
	if (WAD_Get(idx)->absdirs != nullptr) {
		// cleanup allocated absolute directory file paths
		for (int j = 0; j < (int)WAD_Get(idx)->count; j++) {
			if (WAD_Get(idx)->absdirs[j] != nullptr) {
				std::free(WAD_Get(idx)->absdirs[j]);
			}
		}
	}

WADOpen_reldirs:
	// failure, clean up half-finished WAD file reading
	// although WAD_freadstr never returns false...
	if (WAD_Get(idx)->reldirs != nullptr) {
		// cleanup allocated relative directory file paths
		for (int j = 0; j < (int)WAD_Get(idx)->count; j++) {
			if (WAD_Get(idx)->reldirs[j] != nullptr) {
				std::free(WAD_Get(idx)->reldirs[j]);
			}
		}
	}

WADOpen_allocs:
	// failure, free reldirs and absdirs buffers
	if (WAD_Get(idx)->reldirs != nullptr)
		std::free(WAD_Get(idx)->reldirs);
	if (WAD_Get(idx)->absdirs != nullptr)
		std::free(WAD_Get(idx)->absdirs);

WADOpen_close:
	std::fclose(file);

//WADOpen_end:
	return -1;
}


// Returns LegoWADFile at idx in table. (0-9)
// 
// <LegoRR.exe @0048bfa0>
WADFile* __cdecl lego::wad::WAD_Get(int wadIndex)
{
	return &globals::g_WADFiles_TABLE[wadIndex];
}

// <LegoRR.exe @0048bfb0>
uint __cdecl lego::wad::WAD_GetEntrySize(int wadIndex, int entryIndex)
{
	return WAD_Get(wadIndex)->entries[entryIndex].orig_size;
}

// <LegoRR.exe @0048bfd0>
uint __cdecl lego::wad::WAD_GetEntryPackedSize(int wadIndex, int entryIndex)
{
	return WAD_Get(wadIndex)->entries[entryIndex].pack_size;
}

// <LegoRR.exe @0048bff0>
int __cdecl lego::wad::WAD_Stream__Next(void)
{
	for (int i = 0; i < WADSTREAMS_COUNT /*100*/; i++) {
		if (!globals::g_WADStreams_TABLE[i].isUsed) {
			return i;
		}
	}
	return -1;
}

// Returns the file index found 
// Returns -1 on failure or not found.
// 
// <LegoRR.exe @0048c010>
int __cdecl lego::wad::WAD_FindEntry(const char* filename, int opt_wadIndex)
{
	if (opt_wadIndex != -1)
		return WAD_FindEntryInWAD(filename, opt_wadIndex);

	// Search through WADs in reverse order (highest number has highest priority)
	for (int wadIndex = WADFILES_COUNT - 1 /*10-1=9*/; wadIndex >= 0; wadIndex--) {
		if (!WAD_Get(wadIndex)->isUsed)
			continue;
		
		int entryIndex = WAD_FindEntryInWAD(filename, wadIndex);
		if (entryIndex != -1)
			return entryIndex;
	}
	return -1;
}

// Returns the file index in the specified WAD matching the reldir filepath.
// Returns -1 on failure or not found.
// 
// <LegoRR.exe @0048c060>
int __cdecl lego::wad::WAD_FindEntryInWAD(const char* filename, int wadIndex)
{
	for (int i = 0; i < (int)globals::g_WADFiles_TABLE[wadIndex].count; i++) {
		if (::_stricmp(globals::g_WADFiles_TABLE[wadIndex].reldirs[i], filename) == 0)
			return i;
	}
	return -1;
}

// Returns idx of next available LegoWADFile in table (0-9). -1 when none are available.
//
// <LegoRR.exe @0048c0c0>
int __cdecl lego::wad::WAD__Next(void)
{
	for (int i = 0; i < WADFILES_COUNT /*10*/; i++) {
		if (!globals::g_WADFiles_TABLE[i].isUsed) { // NOTE: field_4 is checked, not field_0
			// clear memory, and prepare for usage
			std::memset(&globals::g_WADFiles_TABLE[i], 0, sizeof(WADFile) /*0x24*/);
			return i;
		}
	}
	return -1;
}

// Reads a WAD from filename into a shared file table, and returns the index in the table
// 
// <LegoRR.exe @0048c100>
int __cdecl lego::wad::WAD_StreamOpenInWAD(const char* filename, int wadIndex)
{
	int idx = WAD_Stream__Next();
	if (idx == -1)
		return -1;

	int entryIndex = WAD_FindEntry(filename, wadIndex);
	if (entryIndex == -1)
		return -1;

	uint entrySize = WAD_GetEntryPackedSize(wadIndex, entryIndex);
	void* buffer = std::malloc(entrySize);
	if (buffer == nullptr)
		return -1;

	uint entryOffset = WAD_Get(wadIndex)->entries[entryIndex].offset;
	std::fseek(WAD_Get(wadIndex)->file, entryOffset, 0);
	entrySize = WAD_GetEntryPackedSize(wadIndex, entryIndex);
	if (std::fread(buffer, entrySize, 1, WAD_Get(wadIndex)->file) != 1) {
		std::free(buffer);
		return -1;
	}

	void* fileData = buffer;
	if (WAD_Get(wadIndex)->entries[entryIndex].flags & WADENTRY_COMPRESSED /*0x2*/) { // flag 0x2 == compressed???
		fileData = nullptr;
		/// COMPRESSION: Rob Northern compression
		/// SOURCES:
		/// <https://github.com/lab313ru/rnc_propack_source>
		/// <https://segaretro.org/Rob_Northen_compression>
		/// <https://moddingwiki.shikadi.net/wiki/Rob_Northern_Compression>

		// This compression is (thankfully) never used in LRR WAD files :)
		// Some glitches(?) will cause failure to load certain compressed WAD entries
		//  (possibly due to streaming issues, since .wav files were affected)

		rnc::RNC_Decompress(buffer, &fileData);
		// Data decompressed to new buffer stored in fileData, free original buffer.
		std::free(buffer);
	}
	globals::g_WADStreams_TABLE[idx].fileData   = fileData;
	globals::g_WADStreams_TABLE[idx].isUsed     = true;
	globals::g_WADStreams_TABLE[idx].wadIndex   = wadIndex;
	globals::g_WADStreams_TABLE[idx].entryIndex = entryIndex;
	return idx;
}

// Reads a WAD from filename into a shared file table, and returns the index in the table.
// if opt_wadIndex is -1, all WAD files will be searched for the file name
// 
// <LegoRR.exe @0048c230>
int __cdecl lego::wad::WAD_StreamOpen(const char* filename, int opt_wadIndex)
{
	if (opt_wadIndex != -1)
		return WAD_StreamOpenInWAD(filename, opt_wadIndex);

	for (int wadIndex = WADFILES_COUNT - 1 /*10-1=9*/; wadIndex >= 0; wadIndex--) {
		if (!WAD_Get(wadIndex)->isUsed)
			continue;

		int streamIndex = WAD_StreamOpenInWAD(filename, wadIndex);
		if (streamIndex != -1)
			return streamIndex;
	}
	return -1;
}

// <LegoRR.exe @0048c280>
void __cdecl lego::wad::WAD_StreamClose(int streamIndex)
{
	if (globals::g_WADStreams_TABLE[streamIndex].isUsed) {
		std::free(globals::g_WADStreams_TABLE[streamIndex].fileData);
		globals::g_WADStreams_TABLE[streamIndex].isUsed = false;
	}
}

// <LegoRR.exe @0048c2b0>
void* __cdecl lego::wad::WAD_StreamGetData__internal(int streamIndex)
{
	if (globals::g_WADStreams_TABLE[streamIndex].isUsed) {
		return globals::g_WADStreams_TABLE[streamIndex].fileData;
	}
	return nullptr;
}

// <LegoRR.exe @0048c2d0>
uint __cdecl lego::wad::WAD_StreamGetSize(int streamIndex)
{
	return WAD_GetEntrySize(globals::g_WADStreams_TABLE[streamIndex].wadIndex,
		globals::g_WADStreams_TABLE[streamIndex].entryIndex);
}

// <LegoRR.exe @0048c2f0>
void* __cdecl lego::wad::WAD_StreamGetData(int streamIndex)
{
	return WAD_StreamGetData__internal(streamIndex);
}

#pragma endregion

