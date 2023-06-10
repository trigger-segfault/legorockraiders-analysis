
#include <windows.h>
#include <direct.h>

#include "Standard.h"
#include "Errors.h"
#include "Files.h"
#include "Utils.h"
#include "Lists.h"
#include "Mem.h"
#include "Wad.h"

static VOID __cdecl Wad_IncludeFile(LPUCHAR fname, BOOL binary);
static VOID __cdecl Wad_WriteHeader(FILE *fp);
static lpWadEntry __cdecl Wad_FindPathEntry(LPUCHAR path, BOOL binary);

struct WadGlobs {

	BOOL build;
	LPUCHAR nameBuffer;
	ULONG nameBufferUsed, nameBufferSize;
	struct WadEntry *rootEntry;
	struct WadEntry *entryList;
	LPULONG parentIndexList;
	ULONG entryListCount;
	FILE *wadFile;
	ULONG wadFileHeaderSize;
	UCHAR headerFile[FILE_MAXPATH];

} wadGlobs = { 0 };

VOID Wad_Initialise(VOID) {

}

__inline static SLONG Wad_RestoreSeekPosition(lpWadEntry entry) {

	SLONG position = wadGlobs.wadFileHeaderSize + entry->offset + entry->seekPosition;

	if (position != ftell(wadGlobs.wadFile)) {
		return fseek(wadGlobs.wadFile, position, SEEK_SET);
	}
	
	return 0;
}

lpWadEntry Wad_File_Open(LPUCHAR fname, LPUCHAR attribs) {

	if (strstr(attribs, "r")) {

		lpWadEntry entry;
		BOOL binary = (NULL != strstr(attribs, "b"));

		if (wadGlobs.wadFile) {

			if (entry = Wad_FindPathEntry(fname, binary)) {
				if (!(entry->flags & WADENTRY_FLAG_MISSING)) {

					entry->seekPosition = 0;
					entry->flags |= WADENTRY_FLAG_OPEN;

					return entry;

				} else Error_Warn(TRUE, Error_Format("File missing from wad \"%s\"", fname));
			}
#ifdef _WAD_BUILD
		} else {
			Wad_IncludeFile(fname, binary);
#endif // _WAD_BUILD
		}

	}

	return NULL;
}

SLONG Wad_File_Close(lpWadEntry entry) {

	if (wadGlobs.wadFile) {
		entry->flags &= ~WADENTRY_FLAG_OPEN;
	}

	return 0;
}

size_t Wad_File_Read(LPVOID buffer, ULONG blockSize, ULONG count, lpWadEntry entry) {

	if (wadGlobs.wadFile) {
		
		ULONG readBytes = blockSize * count;
		ULONG entries;

		Error_Fatal(!(entry->flags & WADENTRY_FLAG_OPEN), "WadEntry is not open");
		Error_Fatal(entry->seekPosition < 0, "Cannot read from before the start of the file");
		Error_Fatal(entry->seekPosition > (SLONG) entry->size, "Cannot read beyond the end of the file");

		Wad_RestoreSeekPosition(entry);

		entries = min(readBytes, entry->size - entry->seekPosition) / blockSize;
		readBytes = entries * blockSize;

		fread(buffer, 1, readBytes, wadGlobs.wadFile);
		entry->seekPosition += readBytes;

		return entries;
	}

	return 0;
}

SLONG Wad_File_Seek(lpWadEntry entry, SLONG offset, SLONG flags) {

	if (wadGlobs.wadFile) {

		Error_Fatal(!(entry->flags & WADENTRY_FLAG_OPEN), "WadEntry is not open");
		
		switch(flags) {
		case SEEK_SET: entry->seekPosition = offset;				break;
		case SEEK_CUR: entry->seekPosition += offset;				break;
		case SEEK_END: entry->seekPosition = entry->size + offset;	break;
		}
	}

	return 0;
}

SLONG Wad_File_Tell(lpWadEntry entry) {

	if (wadGlobs.wadFile) {

		Error_Fatal(!(entry->flags & WADENTRY_FLAG_OPEN), "WadEntry is not open");
		
		return entry->seekPosition;
	}

	return 0;
}

LPUCHAR Wad_File_GetS(LPUCHAR buffer, ULONG size, lpWadEntry entry) {

	if (wadGlobs.wadFile) {

		ULONG loop, readSize;

		Error_Fatal(!(entry->flags & WADENTRY_FLAG_OPEN), "WadEntry is not open");
		Error_Fatal(entry->flags & WADENTRY_FLAG_BINARY, "Wad_File_GetS() should not be used on binary files");

		Wad_RestoreSeekPosition(entry);

		readSize = min(size - 1, entry->size - entry->seekPosition);
		
		if (readSize) {
		
			for (loop=0 ; loop<readSize ; loop++) {
				buffer[loop] = fgetc(wadGlobs.wadFile);
				if ('\n' == buffer[loop]) break;
			}
			loop++;
			buffer[loop] = '\0';
			entry->seekPosition += loop;

			return buffer;
		}
	}

	return NULL;
}

/*
LPUCHAR Wad_File_GetS(LPUCHAR buffer, ULONG size, lpWadEntry entry) {

	if (wadGlobs.wadFile) {

		ULONG loop, position, readSize;

		Error_Fatal(!(entry->flags & WADENTRY_FLAG_OPEN), "WadEntry is not open");
		Error_Fatal(entry->flags & WADENTRY_FLAG_BINARY, "Wad_File_GetS() should not be used on binary files");

		position = wadGlobs.wadFileHeaderSize + entry->offset + entry->seekPosition;
		if (entry->size - entry->seekPosition < size) {

			readSize = entry->size - entry->seekPosition;
			buffer[readSize] = '\0';

		} else readSize = size;

		if (readSize) {

			fseek(wadGlobs.wadFile, position, SEEK_SET);
			fread(buffer, 1, readSize, wadGlobs.wadFile);

			for (loop=1 ; loop<readSize ; loop++) {
				if ('\n' == buffer[loop - 1]) {
					buffer[loop] = '\0';
					entry->seekPosition += loop;
					break;
				}
			}

			if (loop == readSize) {
				entry->seekPosition = entry->size;
			}

			return buffer;
		}
	}

	return NULL;
}
*/

__inline static lpWadEntry Wad_CreateEntry(LPULONG newIndex, ULONG flags) {

	lpWadEntry entry;

	Error_Overflow(wadGlobs.entryListCount, WAD_BUILD_ENTRYLISTSIZE);

	if (newIndex) *newIndex = wadGlobs.entryListCount;
	entry = &wadGlobs.entryList[wadGlobs.entryListCount++];
	entry->childListIndex = -1;
	entry->nextSiblingIndex = -1;
	entry->index = -1;
	entry->flags = flags;

	return entry;
}

__inline static lpWadEntry Wad_GetEntry(ULONG index) {

	if (-1 == index) return NULL;

	Error_Fatal(index >= wadGlobs.entryListCount, "Index is out of range");

	return &wadGlobs.entryList[index];
}

__inline static BOOL Wad_IsDirectory(lpWadEntry entry) {

	return (NULL != Wad_GetEntry(entry->childListIndex));
}

__inline static LPUCHAR Wad_GetEntryName(lpWadEntry entry) {

	if (-1 == entry->index) return NULL;
	return &wadGlobs.nameBuffer[entry->index];
}

BOOL Wad_Load(LPUCHAR wadFileName, BOOL full) {

	FILE *wfp;
	BOOL result = FALSE;
	ULONG headerSize;

	Error_Fatal(full && wadGlobs.build, "Cannot load a wad while in build mode");

	if (wfp = fopen(wadFileName, "rb")) {
		if (headerSize = Wad_ReadHeader(wfp, full)) {

			if (full) {

				wadGlobs.wadFile = wfp;
				wadGlobs.wadFileHeaderSize = headerSize;
				
			} else fclose(wfp);

			
			return TRUE;
		}
	}

	return FALSE;
}

static lpWadEntry Wad_FindChildEntry(lpWadEntry parent, LPUCHAR name, BOOL binary) {

	lpWadEntry child;

	for (child=Wad_GetEntry(parent->childListIndex) ; child ; child=Wad_GetEntry(child->nextSiblingIndex)) {

		if (Wad_IsDirectory(child) ||
			(binary && (child->flags & WADENTRY_FLAG_BINARY)) ||
			(!binary && !(child->flags & WADENTRY_FLAG_BINARY))) {

			if (0 == stricmp(name, Wad_GetEntryName(child))) return child;
		}
	}

	return NULL;
}

static lpWadEntry Wad_FindPathEntry(LPUCHAR path, BOOL binary) {

	UCHAR buffer[FILE_MAXPATH];
	LPUCHAR argv[WAD_BUILD_MAXDEPTH];
	ULONG argc, loop;
	lpWadEntry entry = wadGlobs.rootEntry;

	sprintf(buffer, "%s", path);
	argc = Util_Tokenise(buffer, argv, WAD_BUILD_MAXDEPTH, "\\", FALSE);

	for (loop=0 ; loop<argc ; loop++) {
		if (NULL == (entry = Wad_FindChildEntry(entry, argv[loop], binary))) return NULL;
	}

	return entry;
}

__inline BOOL Wad_FileExists(LPUCHAR fname) {

	if (wadGlobs.wadFile) {
		if (Wad_FindPathEntry(fname, FALSE) || Wad_FindPathEntry(fname, TRUE)) return TRUE;
	}

	return FALSE;
}

static VOID Wad_BuildParentList(VOID) {

	ULONG loop, childIndex;
	lpWadEntry entry;

	wadGlobs.parentIndexList = Mem_Alloc(sizeof(wadGlobs.parentIndexList[0]) * WAD_BUILD_ENTRYLISTSIZE);
	memset(wadGlobs.parentIndexList, 0xff, sizeof(wadGlobs.parentIndexList[0]) * WAD_BUILD_ENTRYLISTSIZE);

	for (loop=0 ; loop<wadGlobs.entryListCount ; loop++) {

		entry = &wadGlobs.entryList[loop];

		for (childIndex=entry->childListIndex ; Wad_GetEntry(childIndex) ; childIndex=Wad_GetEntry(childIndex)->nextSiblingIndex) {

			wadGlobs.parentIndexList[childIndex] = loop;
		}
	}
}

static ULONG Wad_GetParentIndex(ULONG childIndex) {

	return wadGlobs.parentIndexList[childIndex];
}

ULONG Wad_ReadHeader(FILE *wfp, BOOL full) {

	struct WadHeader header;
	ULONG result = 0;

	Error_Fatal(NULL != wadGlobs.nameBuffer, "Name buffer has already been allocated");

	fread(&header, sizeof(header), 1, wfp);

	if (WAD_MAGIC == header.magic) {

		wadGlobs.entryListCount = header.entryCount;
		if (full) wadGlobs.entryList = Mem_AllocClear(sizeof(wadGlobs.entryList[0]) * wadGlobs.entryListCount);
		fread(wadGlobs.entryList, sizeof(wadGlobs.entryList[0]), header.entryCount, wfp);
		wadGlobs.rootEntry = &wadGlobs.entryList[0];

		wadGlobs.nameBufferUsed = wadGlobs.nameBufferSize = header.nameListSize;
		wadGlobs.nameBuffer = Mem_Alloc(wadGlobs.nameBufferSize);
		fread(wadGlobs.nameBuffer, 1, header.nameListSize, wfp);

		if (!full) Wad_BuildParentList();

		result = header.totalSize;

#ifdef _DEBUG
		Wad_Debug_Dump("waddump2.txt");
#endif // _DEBUG

	} else Error_Fatal(TRUE, "Invalid wad file");

	return result;
}

#ifdef _WAD_BUILD

__inline static LPUCHAR Wad_GetPath(ULONG entryIndex) {

	static UCHAR path[FILE_MAXPATH];
	ULONG entryPath[WAD_BUILD_MAXDEPTH];
	lpWadEntry entry = Wad_GetEntry(entryIndex);
	SLONG depth;
	BOOL changed = FALSE;

	sprintf(path, "%s", File_GetActualPath("", TRUE));
	entryPath[0] = entryIndex;

	for (depth=0 ; -1 != entryPath[depth] ; ) {

		depth++;

		entryPath[depth] = Wad_GetParentIndex(entryPath[depth - 1]);

	}

	for (depth-- ; depth>=0 ; depth--) {
		if (Wad_GetEntryName(Wad_GetEntry(entryPath[depth]))) {
			strcat(path, Wad_GetEntryName(Wad_GetEntry(entryPath[depth])));
			if (depth) strcat(path, "\\");
			changed = TRUE;
		}
	}

	if (changed) return path;
	else return NULL;
}

static BOOL Wad_BuildList(FILE *wfp, BOOL write) {

	FILE *ifp;
	ULONG loop, position = 0, size, sub;
	lpWadEntry entry;
	LPUCHAR path;
	LPVOID buffer = NULL;
	ULONG bufferSize = 0;
	UCHAR blankBuffer[WAD_BUILD_FILEALIGN] = { 0 };

	for (loop=0 ; loop<wadGlobs.entryListCount ; loop++) {

		entry = &wadGlobs.entryList[loop];

		if (!Wad_IsDirectory(entry)) {

			BOOL binary = ((entry->flags & WADENTRY_FLAG_BINARY) == WADENTRY_FLAG_BINARY);

			if (path = Wad_GetPath(loop)) {
				if (!(entry->flags & WADENTRY_FLAG_MISSING)) {
					if (ifp = fopen(path, binary?"rb":"r")) {

						if (write) {

							ULONG blockSize;

							if (entry->size > bufferSize) {
								bufferSize = entry->size;
								if (buffer) Mem_Free(buffer);
								buffer = Mem_Alloc(bufferSize);
							}

							if (binary) {
								fread(buffer, 1, entry->size, ifp);
								fwrite(buffer, 1, entry->size, wfp);
							} else {
								for (sub=0 ; sub<entry->size ; sub++) {
									fputc(fgetc(ifp), wfp);
								}
							}

							blockSize = ((entry->size + (WAD_BUILD_FILEALIGN - 1)) / WAD_BUILD_FILEALIGN) * WAD_BUILD_FILEALIGN;
							fwrite(blankBuffer, 1, blockSize - entry->size, wfp);

						} else {

							if (binary) {
								fseek(ifp, 0, SEEK_END);
								size = ftell(ifp);
							} else {
								for (size=0 ; EOF!=fgetc(ifp) ; size++) ;
							}

							entry->offset = position;
							entry->size = size;
							position += ((size + (WAD_BUILD_FILEALIGN - 1)) / WAD_BUILD_FILEALIGN) * WAD_BUILD_FILEALIGN;

						}

						fclose(ifp);

					} else {
						
						UCHAR msg[1024];

						if (write) {

							sprintf(msg, "Aborting: Cannot read file \"%s\"", path);
							MessageBox(NULL, msg, "Wad Build Error", MB_OK);
							break;

						} else {

							sprintf(msg, "Cannot include file \"%s\"", path);
							if (IDOK == MessageBox(NULL, msg, "Wad Build", MB_OKCANCEL)) {

								entry->flags |= WADENTRY_FLAG_MISSING;

							} else break;

						}
					}
				}
			}
		}
	}

	if (buffer) Mem_Free(buffer);

	return (loop == wadGlobs.entryListCount);
}

BOOL Wad_Build(LPUCHAR wadFileName) {

	FILE *wfp;
	BOOL result = FALSE;

	Error_Fatal(NULL == wadGlobs.nameBuffer || 0 == wadGlobs.entryListCount, "Cannot build wad - Empty header file");

	if (wfp = fopen(wadFileName, "wb")) {

		if (result = Wad_BuildList(wfp, FALSE)) {
			Wad_WriteHeader(wfp);
			result = Wad_BuildList(wfp, TRUE);
		}

		fclose(wfp);

		if (!result) remove(wadFileName);
	}

	return result;
}

VOID Wad_SetBuild(LPUCHAR headerFile) {

	wadGlobs.build = TRUE;

	wadGlobs.entryList = Mem_AllocClear(sizeof(wadGlobs.entryList[0]) * WAD_BUILD_ENTRYLISTSIZE);

	if (NULL == headerFile || !Wad_Load(headerFile, FALSE)) {
		wadGlobs.rootEntry = Wad_CreateEntry(NULL, 0);
	}
	sprintf(wadGlobs.headerFile, "%s", headerFile);
}

static VOID Wad_WriteHeader(FILE *fp) {

	struct WadHeader header;

	header.magic = WAD_MAGIC;
	header.entryCount = wadGlobs.entryListCount;
	header.nameListSize = (((wadGlobs.nameBufferUsed + 3) / 4) * 4);
	header.totalSize = sizeof(header) + (header.entryCount * sizeof(wadGlobs.entryList[0])) + header.nameListSize;

	fwrite(&header, sizeof(header), 1, fp);
	fwrite(wadGlobs.entryList, sizeof(wadGlobs.entryList[0]), wadGlobs.entryListCount, fp);
	fwrite(wadGlobs.nameBuffer, 1, header.nameListSize, fp);
}

static ULONG Wad_AddName(LPUCHAR name) {

	ULONG length = strlen(name) + 1;
	ULONG location = wadGlobs.nameBufferUsed;

	if (wadGlobs.nameBufferUsed + length + 3 > wadGlobs.nameBufferSize) {
		wadGlobs.nameBufferSize += 1024;
		wadGlobs.nameBuffer = Mem_ReAlloc(wadGlobs.nameBuffer, wadGlobs.nameBufferSize);
	}

	sprintf(&wadGlobs.nameBuffer[location], "%s", name);
	wadGlobs.nameBufferUsed += length;

	return location;
}

static VOID Wad_IncludeFile(LPUCHAR fname, BOOL binary) {

	if (wadGlobs.build) {

		UCHAR path[FILE_MAXPATH];
		LPUCHAR argv[WAD_BUILD_MAXDEPTH];
		ULONG argc, loop, newIndex;
		lpWadEntry parentEntry = wadGlobs.rootEntry, entry;
		FILE *ifp;

		sprintf(path, "Data\\%s", fname);
		if (ifp = fopen(path, "rb")) {

			fclose(ifp);
			ifp = NULL;

			sprintf(path, "%s", fname);
			argc = Util_Tokenise(path, argv, sizeof(argv) / sizeof(argv[0]), "\\", FALSE);

			for (loop=0 ; loop<argc ; loop++) {

				if (NULL == (entry = Wad_FindChildEntry(parentEntry, argv[loop], binary))) {

					entry = Wad_CreateEntry(&newIndex, binary?WADENTRY_FLAG_BINARY:0);

					entry->index = Wad_AddName(argv[loop]);
					entry->nextSiblingIndex = parentEntry->childListIndex;
					parentEntry->childListIndex = newIndex;
				}

				parentEntry = entry;
			}
		}
	}
}

BOOL Wad_SaveHeaderFile(VOID) {

	if ('\0' != wadGlobs.headerFile[0]) {

		FILE *fp;

		if (fp = fopen(wadGlobs.headerFile, "wb")) {

			Wad_WriteHeader(fp);
			fclose(fp);

			return TRUE;
		}
	}

	return FALSE;
}

static VOID Wad_ExtractFile_Rec(lpWadEntry entry, LPUCHAR path) {

	UCHAR fname[FILE_MAXPATH];
	lpWadEntry child;
	ULONG added = 0;

	if (Wad_IsDirectory(entry)) {
	
		if (Wad_GetEntryName(entry)) {
			strcat(path, "\\");
			strcat(path, Wad_GetEntryName(entry));
			added = 1 + strlen(Wad_GetEntryName(entry));
		}

		mkdir(path);

	} else {

		FILE *tfp, *efp;
		BOOL exists;

		sprintf(fname, "%s\\%s", path, Wad_GetEntryName(entry));

		// If the file is stored twice (ASCII and binary copies) then ensure the binary is not overwritten.

		if (tfp = fopen(fname, "rb")) {
			exists = TRUE;
			fclose(tfp);
		} else exists = FALSE;
		
		if (FALSE == exists || (entry->flags & WADENTRY_FLAG_BINARY)) {
			if (efp = fopen(fname, (entry->flags & WADENTRY_FLAG_BINARY)?"wb":"w")) {

				LPUCHAR buffer = Mem_Alloc(entry->size);
					
				Wad_RestoreSeekPosition(entry);
				fread(buffer, 1, entry->size, wadGlobs.wadFile);

				if (entry->flags & WADENTRY_FLAG_BINARY) fwrite(buffer, 1, entry->size, efp);
				else {

					ULONG loop;

					for (loop=0 ; loop<entry->size ; loop++) {
						fputc(buffer[loop], efp);
					}
				}

				Mem_Free(buffer);

				fclose(efp);
			}
		} else fclose(tfp);
	}

	for (child=Wad_GetEntry(entry->childListIndex) ; child ; child=Wad_GetEntry(child->nextSiblingIndex)) {

		Wad_ExtractFile_Rec(child, path);
	}

	path[strlen(path) - added] = '\0';
}

VOID Wad_Extract(LPUCHAR dirName) {

	if (wadGlobs.wadFile) {

		UCHAR path[FILE_MAXPATH];

		sprintf(path, "%s", dirName);

		Wad_ExtractFile_Rec(wadGlobs.rootEntry, path);
	}
}

#ifdef _DEBUG

static VOID Wad_Debug_Dump_Rec(FILE *fp, lpWadEntry entry, ULONG depth) {

	ULONG loop;
	lpWadEntry child;

	for (loop=0 ; loop<depth ; loop++) fprintf(fp, "\t");

	fprintf(fp, "%s%s%s (%c)\n", Wad_IsDirectory(entry)?"[":"", Wad_GetEntryName(entry), Wad_IsDirectory(entry)?"]":"", Wad_IsDirectory(entry)?('d'):((entry->flags & WADENTRY_FLAG_BINARY)?('b'):('a')));

	for (child=Wad_GetEntry(entry->childListIndex) ; child ; child=Wad_GetEntry(child->nextSiblingIndex)) {
		Wad_Debug_Dump_Rec(fp, child, depth + 1);
	}
}

VOID Wad_Debug_Dump(LPUCHAR fname) {

	FILE *fp;

	if (wadGlobs.rootEntry) {
		if (fp = fopen(fname, "w")) {

			Wad_Debug_Dump_Rec(fp, wadGlobs.rootEntry, 0);

			fclose(fp);
		}
	}
}

#endif // _DEBUG

#endif // _WAD_BUILD
