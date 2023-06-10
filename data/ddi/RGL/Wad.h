
#ifndef _RGL_WAD_H
#define _RGL_WAD_H

#include "Files.h"

#pragma message ( "Remove for final build" )
#define _WAD_BUILD

#define WAD_BUILD_ENTRYLISTSIZE			10000
#define WAD_BUILD_MAXDEPTH				20
#define WAD_BUILD_FILEALIGN				4

#define WAD_MAGIC						'HDAW'

#define WADENTRY_FLAG_BINARY			0x00000001
#define WADENTRY_FLAG_OPEN				0x00000002
#define WADENTRY_FLAG_MISSING			0x00000004

struct WadEntry {

	ULONG index;
	ULONG offset, size;
	SLONG seekPosition;
	ULONG flags;

	ULONG childListIndex;
	ULONG nextSiblingIndex;
};

struct WadHeader {

	ULONG magic, totalSize;
	ULONG entryCount, nameListSize;
};

typedef struct WadEntry				*lpWadEntry;
typedef struct WadHeader			*lpWadHeader;

extern VOID __cdecl Wad_Initialise(VOID);
extern lpWadEntry __cdecl Wad_File_Open(LPUCHAR fname, LPUCHAR attribs);
extern SLONG __cdecl Wad_File_Close(lpWadEntry entry);
extern size_t __cdecl Wad_File_Read(LPVOID buffer, ULONG blockSize, ULONG count, lpWadEntry entry);
extern size_t __cdecl Wad_File_Write(LPVOID buffer, ULONG blockSize, ULONG count, lpWadEntry entry);
extern SLONG __cdecl Wad_File_Seek(lpWadEntry entry, SLONG offset, SLONG flags);
extern SLONG __cdecl Wad_File_Tell(lpWadEntry entry);
extern LPUCHAR __cdecl Wad_File_GetS(LPUCHAR buffer, ULONG size, lpWadEntry entry);
extern VOID __cdecl Wad_SetBuild(LPUCHAR headerFile);
extern VOID __cdecl Wad_Debug_Dump(LPUCHAR fname);
extern ULONG __cdecl Wad_ReadHeader(FILE *wfp, BOOL full);
extern BOOL __cdecl Wad_Load(LPUCHAR wadFileName, BOOL full);
extern VOID __cdecl Wad_Extract(LPUCHAR dirName);
extern BOOL __cdecl Wad_Build(LPUCHAR wadFileName);
extern BOOL __cdecl Wad_SaveHeaderFile(VOID);
extern BOOL __cdecl Wad_FileExists(LPUCHAR fname);

#endif // _RGL_WAD_H
