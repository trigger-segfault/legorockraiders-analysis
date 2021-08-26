#ifndef _WAD_H_
#define _WAD_H_

#ifdef __cplusplus
extern "C"{
#endif

typedef enum _bool { false, true } bool;

#define WAD_FILE_UNCOMPRESSED (1 << 0)
#define WAD_FILE_RNCOMPRESSED (1 << 1)
#define WAD_FILE_IS_IN_WAD    (1 << 2)

typedef struct _WadEntry
{
	int compression;		// Is the file compressed
	int fileLength;			// Length of the file in wad
	int decompressedLength;	// Decompressed length of file
	union
	{
		int addr;
		void *ptr;
	};
} WadEntry;

typedef struct _Wad
{
	char *fName;
	BOOL active;
	HANDLE hFile, hFileMapping;
	FILE *fWad;					// File handle of the wad

	// Each of the file names in the wad
	char **fileNames;			// Names of actual files
	char **wadNames;			// Names within wad
	WadEntry *wadEntries;
	int numFiles;
} Wad;

////////////////////////////////////////////////////
//////////// The interface for wads ////////////////
////////////////////////////////////////////////////

////////////////////////////////////////////////////
// Open the wad and map in the file data.
// Returns a handle to the wad file.

int Wad_Load(char *fName);

////////////////////////////////////////////////////
// Close an open wad

void Wad_Close(int wadNo);

////////////////////////////////////////////////////
// Save a wad file to the disk.
// Returns WAD_ERROR on failure.

int Wad_Save(char *wadName,		// Wad to write to
			 char **fNames,		// List of files to compress
			 char **wNames,		// names of files within wad
			 unsigned *flags,	// Flags for each file
			 int numFiles,
			 int wadHandle,
			 void (*ProgressUpdate)(int, BOOL, char *, char *)
			 );

////////////////////////////////////////////////////
// If you pass TRUE to this then all file access
// will be written out to file.log.

void Wad_LogFileAccess(BOOL mode);

////////////////////////////////////////////////////
// Data access in wads

int Wad_hLength(int handle);
void *Wad_hData(int handle);

////////////////////////////////////////////////////
// Wad information fucntions

Wad *Wad_Get(int wadNo);
BOOL Wad_FileCompressed(int wadNo, int fileNo);
int Wad_FileLength(int wadNo, int fileNo);
int Wad_FindFreeFileHandle();
int Wad_IsFileInWad(char *fName, int wadNo);
int Wad_GetFreeWadSlot();

////////////////////////////////////////////////////
// Wad operations

int Wad_FileOpen(char *fName, int wadNo);
void Wad_FileClose(int handle);
void *Wad_FileGetPointer(int handle);

////////////////////////////////////////////////////
// Wad dialogs

void Wad_Error(char *msg, ...);
extern char computerName[];
extern DWORD computerNameLength;
extern BOOL wadLogFileAccess;
extern BOOL wad_fcheck(char *);
extern int wad_flength(FILE *);

////////////////////////////////////////////////////
// Wad defines

#define MAX_WADS 10

#ifdef __cplusplus
}
#endif

#endif//_WAD_H_
