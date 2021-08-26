
#ifndef _GODS98_FILES_H_
#define _GODS98_FILES_H_

#include "Standard.h"

#define FILE_DATADIRNAME				"Data"
#define FILE_KEYFILENAME				"cd.key"
#define FILE_DELMEFILENAME				"delme.dat"
//#define FILE_KEYFILENAME				"lego.cfg"
#define FILE_MAXPATH					260

enum {
	File_SeekSet,
	File_SeekCur,
	File_SeekEnd
};

#ifdef _GODS98_USEWAD_

#define WAD_ERROR -1

///////////////////////////////////////////////////////////////////////////////////////////
// Types and structures
//		FileSys - the file system used ie. wad or normal
//		WADFILE - structure to represent a wad file
//		File    - strucrure to represent a file (of either type)
///////////////////////////////////////////////////////////////////////////////////////////

#define StdFile(f) ((FILE*)((f)->std))
#define WadFile(f) ((WADFILE*)((f)->wad))

typedef enum _FileSystemType
{
	FileSystem_Wad,		// Wad file
	FileSystem_Std,		// Standard C Libraries
	FileSystem_Err		// Error code
} FileSys;

typedef struct _WADFILE
{
	int hFile;			// Handle to file in the wad
	int streamPos;		// Position in stream of the file.  Indexes are from 0-length-1 inclusive.
	BOOL eof;			// Has the file hit EOF.
} WADFILE;

typedef struct File_Dummy
{
	FileSys type;
	union 
	{
		void *std;
		WADFILE *wad;
	};
} File, *lpFile;

///////////////////////////////////////////////////////////////////////////////////////////
// Static functions
///////////////////////////////////////////////////////////////////////////////////////////

static FileSys		_File_GetSystem(lpFile f);
static FileSys		_File_CheckSystem(char *fName, char *mode);
static lpFile		_File_Alloc(FileSys fType);
static void			_File_Dealloc(lpFile file);
static void			_File_Free(void *ptr);
static void *		_File_Malloc(int size);
static BOOL			_File_OpenWad(WADFILE *wad, char *fName);
static char *		_File_GetWadName(char *fName);

///////////////////////////////////////////////////////////////////////////////////////////
// Enternal functions
///////////////////////////////////////////////////////////////////////////////////////////

// C library implementation
extern void			File_MakeDir(unsigned char *path);
extern lpFile		File_Open(char *fName, char *mode);
extern int			File_Seek(lpFile f, int pos, int mdoe);
extern int			File_Read(void *buffer, int size, int count, lpFile f);
extern int			File_Write(void *buffer, int size, int count, lpFile f);
extern int			File_Close(lpFile f);
extern int			File_Tell(lpFile f);
extern int			File_Flush(lpFile f);
extern BOOL			File_Exists(char *fName);
extern int			File_Length(lpFile f);
extern char *		File_GetS(char *fgetsBuffer, int num, lpFile f);
extern int			File_GetC(lpFile f);
extern int			File_EOF(lpFile f);
extern int			File_PrintF(lpFile file, char *msg, ...);
extern int			File_ScanF(lpFile file, char *msg, ...);

// Extra functions for using with Wads.
extern int			File_LoadWad(char *fName);
extern void			File_CloseWad(int hWad);
extern void			File_SetActiveWad(int wadHandle);
extern BOOL			File_SetBaseSearchPath(char *basePath);
extern void			File_LogFileAccess(BOOL mode);

///////////////////////////////////////////////////////////////////////////////////////////
// Definitions to patch call to ansi stdC libs into this file system.
///////////////////////////////////////////////////////////////////////////////////////////

#ifdef _DEFINE_ANSI_TO_INTERNAL_FILE_SYSTEM

#define FILE    File
#define fopen   File_Open
#define fclose  File_Close
#define fwrite  File_Write
#define fread   File_Read
#define fwrite  File_Write
#define fseek   File_Seek
#define ftell   File_Tell
#define fflush  File_Flush
#define flen    File_Length
#define fgets   File_GetS
#define fgetc   File_GetC
#define fprintf File_PrintF
#define fscanf  File_ScanF
#define fcheck	File_Exists

#endif //_DEFINE_ANSI_TO_INTERNAL_FILE_SYSTEM

extern unsigned char *__cdecl File_GetLine(unsigned char *buffer,unsigned long size,struct File_Dummy *file);
extern void *__cdecl File_LoadBinary(unsigned char *filename,unsigned long *sizeptr);
extern void *__cdecl File_LoadASCII(unsigned char *filename,unsigned long *sizeptr);
static void *__cdecl File_Load(unsigned char *filename,unsigned long *sizeptr,int binary);
extern unsigned long __cdecl File_LoadBinaryHandle(unsigned char *filename,unsigned long *sizeptr);
extern int __cdecl File_FileExists(unsigned char *name);
extern unsigned char *__cdecl File_VerifyFilename(unsigned char *filename);
extern void __cdecl File_SetLoadCallback(void (__cdecl *Callback)(unsigned char *,unsigned long ,void *),void *data);
static void __cdecl File_CheckFile(unsigned char *fileName);
static void __cdecl File_CheckDirectory(unsigned char *dirName);
extern void __cdecl File_CheckRedundantFiles(unsigned char *logName);
extern void __cdecl File_Initialise(unsigned char *, int insistOnCD, unsigned char *registryLocation);
extern ULONG __cdecl File_VPrintF(lpFile file, LPUCHAR msg, va_list args);
extern BOOL __cdecl File_GetCDFilePath(LPUCHAR path, LPUCHAR fname);
extern void __cdecl File_SetDataDir(unsigned char *newDataDir);

#else // _GODS98_USEWAD_

typedef struct File_Dummy { ULONG null; } *lpFile;

extern VOID __cdecl File_MakeDir(LPUCHAR path);

#ifndef _GENPROTFILE
#include "..\Src\Files.prot"
#endif // _GENPROTFILE

#endif // _GODS98_USEWAD_

typedef struct File_Globs {

	UCHAR dataDir[FILE_MAXPATH];
	UCHAR exeDir[FILE_MAXPATH];
	UCHAR langDir[FILE_MAXPATH];
	VOID (*loadCallback)();
	LPVOID loadCallbackData;
	BOOL langCheck;
	UCHAR cdLetter;

} File_Globs, *lpFile_Globs;

extern File_Globs fileGlobs;

#endif // _GODS98_FILES_H_

