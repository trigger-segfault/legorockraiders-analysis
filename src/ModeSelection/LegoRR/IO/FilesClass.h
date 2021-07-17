// (UNUSED) FilesClass.h : 
//

#pragma once

#include "../Common.h"


namespace lego {
namespace file {

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

struct WADEntry
{
	/*00,4*/ WADEntryFlags flags;    // (always observed as 0x1, which is assumed to be "STORE"?)
	/*04,4*/ unsigned int pack_size; // size in WAD file
	/*08,4*/ unsigned int orig_size; // original decompressed file size
	/*0c,4*/ unsigned int offset;    // absolute file offset to data
	/*10*/
};

class WADFileClass
{
public:
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

	// Open WAD filename and log something (that was removed on release build)
	// returns idx of newly opened WAD (0-9), or -1 on failure of any kind.
	//
	// <LegoRR.exe @0047f900>
	static int __cdecl Open(const char* filename);

	// not a real function
	void Close();

private:
	// Open and read data into WAD file.
	// returns idx of newly opened WAD (0-9), or -1 on failure of any kind.
	// 
	// <LegoRR.exe @0048b7a0>
	int Open__internal(const char* filename);
	static int __cdecl Open__internal_wrapper(const char* filename);
public:
	// Returns LegoWADFile at wadIndex in table. (0-9)
	// 
	// <LegoRR.exe @0048bfa0>
	static WADFileClass* __cdecl Get(int wadIndex);

	// <LegoRR.exe @0048bfb0>
	static size_t __cdecl GetEntrySize(int wadIndex, int entryIndex);

	// <LegoRR.exe @0048bfd0>
	static size_t __cdecl GetEntryPackedSize(int wadIndex, int entryIndex);

	/*// <LegoRR.exe @0048bff0>
	static int __cdecl Shared__Next(void);*/

	// Returns the file index found 
	// Returns -1 on failure or not found.
	// 
	// <LegoRR.exe @0048c010>
	int __cdecl FindEntry(const char* filename, int opt_wadIndex = -1);

	// Returns the file index in the specified WAD matching the reldir filepath.
	// Returns -1 on failure or not found.
	// 
	// <LegoRR.exe @0048c060>
	int __cdecl FindEntry__InWAD(const char* filename, int wadIndex);

private:
	// Returns idx of next available LegoWADFile in table (0-9). -1 when none are available.
	//
	// <LegoRR.exe @0048c0c0>
	static int __cdecl WAD__Next(void);
public:
	/*// Reads a WAD from filename into a shared file table, and returns the index in the table
	// 
	// <LegoRR.exe @0048c100>
	int __cdecl SharedOpen__InWAD(const char* filename, int wadIndex);

	// Reads a WAD from filename into a shared file table, and returns the index in the table.
	// if opt_wadIndex is -1, all WAD files will be searched for the file name
	// 
	// <LegoRR.exe @0048c230>
	static int SharedOpen(const char* filename, int opt_wadIndex = -1);

	// <LegoRR.exe @0048c280>
	void Shared__Dispose(int sharedIndex);

private:
	// <LegoRR.exe @0048c2b0>
	unsigned char* SharedGetData__internal(int sharedIndex) const;
public:
	// <LegoRR.exe @0048c2d0>
	unsigned int SharedGetSize(int sharedIndex) const;

	// <LegoRR.exe @0048c2f0>
	unsigned char* SharedGetData(int sharedIndex) const;*/
};

class SharedWADEntryClass
{
public:
	/*00,4*/ void* fileData;
	/*04,4*/ BOOL isUsed;
	/*08,4*/ int wadIndex;
	/*0c,4*/ int entryIndex;
	/*10*/

	// <LegoRR.exe @0048bff0>
	static int __cdecl Shared__Next(void);

	// Reads a WAD from filename into a shared file table, and returns the index in the table
	// 
	// <LegoRR.exe @0048c100>
	int __cdecl SharedOpen__InWAD(const char* filename, int wadIndex);

	// Reads a WAD from filename into a shared file table, and returns the index in the table.
	// if opt_wadIndex is -1, all WAD files will be searched for the file name
	// 
	// <LegoRR.exe @0048c230>
	static int SharedOpen(const char* filename, int opt_wadIndex = -1);

	// <LegoRR.exe @0048c280>
	void Shared__Dispose(int sharedIndex);

private:
	// <LegoRR.exe @0048c2b0>
	unsigned char* SharedGetData__internal(int sharedIndex) const;
public:
	// <LegoRR.exe @0048c2d0>
	unsigned int SharedGetSize(int sharedIndex) const;

	// <LegoRR.exe @0048c2f0>
	unsigned char* SharedGetData(int sharedIndex) const;
};

struct WADEntryStream
{
	/*0,4*/ int sharedIndex; // index of SharedWADEntry in global table
	/*4,4*/ int position;
	/*8,4*/ unsigned int field_8;
	/*c*/
};

/*union FileStreamSystem
{
	FILE* std; // file, (referred to as STD "standard" file by engine)
	WADEntryStream* wad;
};*/

class SharedFileClass
{
public:
	int sharedIndex;

	bool IsOpen() const;
};

bool operator== (const SharedFileClass& c1, const SharedFileClass& c2)
{
	return (c1.sharedIndex == c2.sharedIndex);
}

bool operator!= (const SharedFileClass& c1, const SharedFileClass& c2)
{
	return (c1.sharedIndex != c2.sharedIndex);
}

class FileStreamClass
{
public:
	/*0,4*/ FileLocation location;
	// /*4,4*/ FileStreamSystem stream;
	/*4,4*/ union {
		FILE* std; // (referred to as STD "standard" file by engine)
		WADEntryStream* wad;
	};
	/*8*/



// <LegoRR.exe @0047f9a0>
	static FileStreamClass* __cdecl Open(const char* in_filename, const char* mode);

	// <LegoRR.exe @0047fb10>
	int Seek(long int offset, int origin);

	// <LegoRR.exe @0047fc40>
	size_t Read(void* out_ptr, size_t size, size_t count);

	// <LegoRR.exe @0047fd10>
	size_t Write(const void* ptr, size_t size, size_t count);

	// <LegoRR.exe @0047fd80>
	int Close();

	// <LegoRR.exe @0047fdd0>
	long int Tell() const;

	// <LegoRR.exe @0047fe20>
	static BOOL __cdecl Exist(const char* filename);

	// <LegoRR.exe @0047fee0>
	int GetC();

	// <LegoRR.exe @0047ff60>
	long int GetLength();

private:
	// <LegoRR.exe @0047ffa0>
	char* WAD_GetS__internal(char* out_str, int num);
public:

	// <LegoRR.exe @00480000>
	char* GetS(char* out_str, int num);

	// <LegoRR.exe @00480070>
	int PrintF(const char* format, ...);

	// <LegoRR.exe @004800e0>
	FileLocation __cdecl GetLocation() const;

	// Returns 0 if file is found in WAD
	// Returns 1 if arguments are valid and mode is "r"/"R".
	// Otherwise, returns 0.
	// 
	// <LegoRR.exe @004800f0>
	static FileLocation __cdecl FindLocation(const char* filename, const char* mode);

private:
// <LegoRR.exe @00480190>
	static FileStreamClass* __cdecl File__New(FileLocation location);
public:
	// just an alias for std::malloc(size_t)
	// <LegoRR.exe @004801f0>
	//void* __cdecl File__New__alloc(size_t size);

	// just an alias for std::free(void* ptr)
	// <LegoRR.exe @00480200>
	//void __cdecl File__New__free(void* ptr);

private:
	// <LegoRR.exe @00480210>
	void File__Dispose(); // something like File_Close_internal

public:
	// all parameters are directly passed to File_GetS, then some operation on string is performed
	// 
	// <LegoRR.exe @00480310>
	char* GetS_StripLineEnd(char* out_str, int num);


	// <LegoRR.exe @00480570>
	static void __cdecl SetOpenCallback(FileOpenCallback callback, void* lpValue);


	// <LegoRR.exe @00480360>
	static unsigned char* __cdecl ReadAllBytes(const char* filename, unsigned int* out_length);

	// <LegoRR.exe @00480380>
	static unsigned char* __cdecl ReadAll(const char* filename, unsigned int* out_length, BOOL isBinary);
};

enum FileBufferFlags : unsigned int
{
	FILEBUFFER_NONE   = 0,

	FILEBUFFER_ISUSED = 0x1,
	//FILEBUFFER_UNK_2  = 0x2,
	//FILEBUFFER_UNK_4  = 0x4,
	//FILEBUFFER_UNK_8  = 0x8,
};
DEFINE_ENUM_FLAG_OPERATORS(FileBufferFlags)

struct SharedFileBuffer
{
	/*0,4*/ void* fileData;
	/*4,4*/ FileBufferFlags flags; // 0x1 == BOOL isUsed
	/*8*/
};

// arguments are: filename, fileSize, lpValue (value passed to File_SetOpenCallback)
typedef void(__cdecl* FileOpenCallback)(const char* filename, int length, void* lpContext);

// Only usage of the above FileFuncPtr
// <LegoRR.exe @0044e180>
//void __cdecl File_funcPtrCallback__0044e180(const char* filename, int length, void* lpContext);



#pragma region Functions

// gamename may actually be gamepath (as called from the commandline arguments)
// 
// <LegoRR.exe @0047f3f0>
void __cdecl InitFileSystem(const char* gamename, BOOL insistOnCD, const char* regKey);

// Checks for a currently-inserted CDROM drive containing the file "CDROM:\Data\cd.key"
// Does not actually check contents of the file.
// Returns true when found, and assigns global: char g_CDROM_DriveLetter;
// 
// <LegoRR.exe @0047f7b0>
BOOL __cdecl Path_CheckForCDROM(void);

// <LegoRR.exe @0047f850>
BOOL __cdecl Path_SetDataDir(const char* dirname);


// <LegoRR.exe @0047f920>
BOOL __cdecl Path_GetCDROMDataPath(char* out_filepath, const char* filename);

// <LegoRR.exe @0047f960>
int __cdecl Path_MakeDataSubdir(const char* dirname);


// <LegoRR.exe @00480160>
BOOL __cdecl WAD_EntryOpen__internal(WADEntryStream* wadStream, const char* filename);

// Strips the Data directory from the filename path, using global g_FILEPATH_DATADIR_1 as a comparison.
// Returns a temporary buffer that must be used before this function is next called.
// 
// <LegoRR.exe @00480280>
const char* __cdecl Path_StripDataDir(const char* filename);

// <LegoRR.exe @00480430>
int __cdecl File_SharedOpen(const char* filename, size_t* out_length);

// Join filename path with global g_FILEPATH_DATADIR_2.
// Returns a temporary buffer that must be used before this function is next called.
// 
// <LegoRR.exe @004804e0>
const char* __cdecl Path_JoinDataDir(const char* filename);


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
void __cdecl InitSharedFileBuffers(void);

// <LegoRR.exe @004896d0>
int __cdecl File_SharedOpen__internal(size_t size);

// <LegoRR.exe @00489720>
void __cdecl File_SharedClose(int sharedIndex);

// <LegoRR.exe @00489760>
unsigned char* __cdecl File_SharedGetData(int sharedIndex);

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
