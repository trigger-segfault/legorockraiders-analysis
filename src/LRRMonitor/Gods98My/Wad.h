#pragma once

#include "../framework.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Forward Declarations
 **********************************************************************************/

#pragma region Forward Declarations

#pragma endregion

/**********************************************************************************
 ******** Function Typedefs
 **********************************************************************************/

#pragma region Function Typedefs

// percent    = integer [0,100]
// debug      = TRUE for debug-specific messages (mostly compression-related)
// currentMsg = progress message for current file. (not passed when stateMsg is passed)
// stateMsg   = message for current progress state/pass etc. (only passed when changed)
typedef void (__cdecl* WadProgressUpdate)(int percent, BOOL debug, const char* currentMsg, const char* stateMsg);

#pragma endregion

/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define MAX_WADS 10

// Number of WADS you can have at one time
#define MAX_OPEN_FILES 100
#define MAX_FILE_COMPRESSION_SIZE (1024*1024)

#pragma endregion

/**********************************************************************************
 ******** Enumerations
 **********************************************************************************/

#pragma region Enums

#define WAD_FILE_UNCOMPRESSED (1 << 0)
#define WAD_FILE_RNCOMPRESSED (1 << 1)
#define WAD_FILE_IS_IN_WAD    (1 << 2)

#pragma endregion

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

typedef struct _WadEntry
{
	/*00,4*/ int compression;		// Is the file compressed
	/*04,4*/ int fileLength;			// Length of the file in wad
	/*08,4*/ int decompressedLength;	// Decompressed length of file
	/*0c,4*/ union {
		int addr;
		void* ptr;
	};
	/*10*/
} WadEntry;
static_assert(sizeof(WadEntry) == 0x10, "");


typedef struct _Wad
{
	/*00,4*/ char* fName;
	/*04,4*/ BOOL active;
	/*08,4*/ HANDLE hFile;
	/*0c,4*/ HANDLE hFileMapping;
	/*10,4*/ FILE* fWad;					// File handle of the wad
										// Each of the file names in the wad
	/*14,4*/ char** fileNames;			// Names of actual files
	/*18,4*/ char** wadNames;			// Names within wad
	/*1c,4*/ WadEntry* wadEntries;
	/*20,4*/ int numFiles;
	/*24*/
} Wad;
static_assert(sizeof(Wad) == 0x24, "");


typedef struct _Wad_FileHandle
{
	/*00,4*/ void* data;					// Pointer to the file data
	/*04,4*/ BOOL active;				// Is this handle active already
	/*08,4*/ int wadFile;				// Wad file this handle uses
	/*0c,4*/ int indexOfFileInWad;		// Index of the file in the wad structure
	/*10*/
} Wad_FileHandle;
static_assert(sizeof(Wad_FileHandle) == 0x10, "");


typedef struct Wad_Globs
{
	/*000,4*/ DWORD computerNameLength; // (address not known)
	/*004,4*/ BOOL wadLogFileAccess;    // (address not known)
	/*008,4*/ FILE* s_ErrorFile_f;      // (address not known)
	/*00c,168*/ Wad wads[MAX_WADS];				// Wad structures
	/*174,28*/ int references[MAX_WADS];		// Current count of references to the wad file
	/*19c,10*/ char computerName[16];    // (address not known)
	/*1ac,640*/ Wad_FileHandle fileHandles[MAX_OPEN_FILES];
	/*7ec*/
} Wad_Globs;
static_assert(sizeof(Wad_Globs) == 0x7ec, "");

#pragma endregion

/**********************************************************************************
 ******** Globals
 **********************************************************************************/

#pragma region Globals

//extern Wad_FileHandle fileHandles[MAX_OPEN_FILES];
// <LegoRR.exe @005764f4>
extern Wad_Globs wadGlobs;

#pragma endregion

/**********************************************************************************
 ******** Macros
 **********************************************************************************/

#pragma region Macros

#define WAD(which) wadGlobs.wads[which]
#define CURWAD wadGlobs.wads[wadGlobs.activeWad]

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @0048b760>
BOOL __cdecl GetFileName(FILE* f, char* str);

////////////////////////////////////////////////////
//////////// The interface for wads ////////////////
////////////////////////////////////////////////////

////////////////////////////////////////////////////
// Open the wad and map in the file data.
// Returns a handle to the wad file.

// <LegoRR.exe @0048b7a0>
int __cdecl Wad_Load(const char* fName);

// <LegoRR.exe @0048bfa0>
Wad* __cdecl Wad_Get(int wadNo);

////////////////////////////////////////////////////
// Close an open wad

//void __cdecl Wad_Close(int wadNo);

////////////////////////////////////////////////////
// Save a wad file to the disk.
// Returns WAD_ERROR on failure.

/*int __cdecl Wad_Save(const char* wadName,		// Wad to write to
			 char** fNames,		// List of files to compress
			 char** wNames,		// names of files within wad
			 unsigned* flags,	// Flags for each file
			 int numFiles,
			 int wadHandle,
			 WadProgressUpdate ProgressUpdate
			 );*/

////////////////////////////////////////////////////
// If you pass TRUE to this then all file access
// will be written out to file.log.

//void __cdecl Wad_LogFileAccess(BOOL mode);

////////////////////////////////////////////////////
// Data access in wads

////////////////////////////////////////////////////
// Wad information fucntions

//BOOL __cdecl Wad_FileCompressed(int wadNo, int fileNo);

// <LegoRR.exe @0048bfb0>
int __cdecl Wad_FileLength(int wadNo, int fileNo);

// <LegoRR.exe @0048bfd0>
BOOL __cdecl Wad_FileCompressed(int wadNo, int fileNo);

// <LegoRR.exe @0048bff0>
int __cdecl Wad_FindFreeFileHandle(void);

// <LegoRR.exe @0048c010>
int __cdecl Wad_IsFileInWad(const char* fName, int wadNo);

// <LegoRR.exe @0048c060>
int _Wad_IsFileInWad(char* fName, int wadNo);

// <LegoRR.exe @0048c0c0>
int __cdecl Wad_GetFreeWadSlot(void);

////////////////////////////////////////////////////
// Wad operations

// <LegoRR.exe @0048c100>
int _Wad_FileOpen(char* fName, int wadNo);

// <LegoRR.exe @0048c230>
int __cdecl Wad_FileOpen(const char* fName, int wadNo);

// <LegoRR.exe @0048c280>
void __cdecl Wad_FileClose(int handle);

// <LegoRR.exe @0048c2b0>
void* __cdecl Wad_FileGetPointer(int handle);

////////////////////////////////////////////////////
// Wad dialogs

// <LegoRR.exe @0048c2d0>
int __cdecl Wad_hLength(int handle);
// <LegoRR.exe @0048c2f0>
void* __cdecl Wad_hData(int handle);

/*void __cdecl Wad_Error(const char* msg, ...);
extern char computerName[];
extern DWORD computerNameLength;
extern BOOL wadLogFileAccess;
BOOL __cdecl wad_fcheck(const char*);
int __cdecl wad_flength(FILE*);*/

#pragma endregion

}
