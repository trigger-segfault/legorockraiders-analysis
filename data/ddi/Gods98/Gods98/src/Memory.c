/**********************************************************************************
 **
 ** Memory.c:	 Memory allocation functions with storage loss stats
 **
 ** Copyright (C) Data Design Interactive.
 **
 **
 ** Written by Robert Wilson 03/03/98
 **
 **********************************************************************************/

#include "..\inc\Standard.h"

#include "..\inc\Errors.h"
#include "..\inc\Memory.h"

#include "windows.h"

static Mem_Globs memGlobs;

VOID Mem_Initialise(VOID){

	ULONG loop;

#ifdef _DEBUG

	for (loop=0 ; loop<MEMORY_DEBUG_MAXNUMALLOC ; loop++){
		memGlobs.debugEntry[loop].addr = NULL;
		memGlobs.debugEntry[loop].allocLine = 0;
		memGlobs.debugEntry[loop].allocFile = NULL;
		memGlobs.debugEntry[loop].flags = 0;
	}

	memGlobs.debugAllocCount = 0;
	memGlobs.maxSimul = memGlobs.totalAlloc = memGlobs.totalDeAlloc = 0;
	memGlobs.endStopID = memGlobs.endStopAddr = 0;

#endif // _DEBUG

	for (loop=0 ; loop<MEMORY_MAXHANDLES ; loop++){
		memGlobs.handleList[loop].addr = NULL;
		memGlobs.handleList[loop].flags = 0x00000000;
	}


}

VOID Mem_Shutdown(BOOL freeAll){

#ifdef _DEBUG

	{
		ULONG loop, count=0, sub;
		UCHAR example[21];

		for (loop=0 ; loop<MEMORY_DEBUG_MAXNUMALLOC ; loop++){
			if ((memGlobs.debugEntry[loop].flags & MEMORY_DEBUG_FLAG_UNFREED) &&
				(memGlobs.debugEntry[loop].flags & MEMORY_DEBUG_FLAG_REPORT)) {

				for (sub=0 ; sub<min(20,memGlobs.debugEntry[loop].size) ; sub++){
					if (isprint((((LPUCHAR)memGlobs.debugEntry[loop].addr)[sub]))) example[sub] = ((LPUCHAR)memGlobs.debugEntry[loop].addr)[sub];
					else example[sub] = '.';
				}
				example[sub] = '\0';
				Error_Debug(Error_Format("%s(%i): %i bytes of memory @0x%0.8x unfreed (ID #%i) [\"%s\"].\n", memGlobs.debugEntry[loop].allocFile, memGlobs.debugEntry[loop].allocLine, memGlobs.debugEntry[loop].size, memGlobs.debugEntry[loop].addr, memGlobs.debugEntry[loop].id, example));
				count++;
			}
		}
		if (freeAll) {
			for (loop=0 ; loop<MEMORY_DEBUG_MAXNUMALLOC ; loop++){
				if (memGlobs.debugEntry[loop].flags & MEMORY_DEBUG_FLAG_UNFREED){
					free(memGlobs.debugEntry[loop].addr);
				}
			}
		}

		Error_Debug("\nMemory Usage Statistics:\n");
		Error_Debug(Error_Format("Total of %d calls to Mem_Alloc() %d unfreed\n", memGlobs.debugAllocCount, count));
		Error_Debug(Error_Format("Maximum of %d bytes allocated at any one time\n", memGlobs.maxSimul));
		Error_Debug(Error_Format("%d bytes allocated, %d bytes freed, %d bytes lost\n", memGlobs.totalAlloc, memGlobs.totalDeAlloc, memGlobs.totalAlloc - memGlobs.totalDeAlloc));
	}

#endif // _DEBUG

}

/*********************************************************************
 ****** Debug Memory Functions
 *********************************************************************/

#ifdef _DEBUG

VOID Mem_Record(BOOL on) {

	memGlobs.recordMalloc = on;
}

LPVOID Mem_AllocDebug(ULONG size, ULONG line, LPUCHAR file){

	LPVOID mem;
	ULONG loop;

	if (!size) {
		Error_Debug(Error_Format("%s(%i): Error: Zero passed to Mem_Alloc()\n", file, line));
		Error_Fatal(TRUE, "Memory Allocation Error");
	}

	if (NULL == (mem = malloc(size))){
		Error_Warn(TRUE, Error_Format("%s(%i): Unable to allocate %i bytes of memory", file, line, size));
		return NULL;
	}

	for (loop=memGlobs.lastAlloc ; loop<MEMORY_DEBUG_MAXNUMALLOC ; loop++){
		if (!(memGlobs.debugEntry[loop].flags & MEMORY_DEBUG_FLAG_UNFREED)) break;
	}
	if (loop==MEMORY_DEBUG_MAXNUMALLOC) {
		for (loop=0; loop<memGlobs.lastAlloc ; loop++){
			if (!(memGlobs.debugEntry[loop].flags & MEMORY_DEBUG_FLAG_UNFREED)) break;
		}
	}

	memGlobs.totalAlloc += size;
	if (memGlobs.totalAlloc - memGlobs.totalDeAlloc > memGlobs.maxSimul)
		memGlobs.maxSimul = memGlobs.totalAlloc - memGlobs.totalDeAlloc;

	if (loop == MEMORY_DEBUG_MAXNUMALLOC) {
		Error_Warn(TRUE, Error_Format("More than %d simultaneous allocations - cannot log", MEMORY_DEBUG_MAXNUMALLOC));
	} else {
		memGlobs.debugEntry[loop].addr = mem;
		memGlobs.debugEntry[loop].allocLine = line;
		memGlobs.debugEntry[loop].allocFile = file;
		memGlobs.debugEntry[loop].size = size;
		memGlobs.debugEntry[loop].id = memGlobs.debugAllocCount;
		memGlobs.debugEntry[loop].flags |= MEMORY_DEBUG_FLAG_UNFREED;
		if (memGlobs.recordMalloc) memGlobs.debugEntry[loop].flags |= MEMORY_DEBUG_FLAG_REPORT;
		memGlobs.lastAlloc = loop;
	}
	
	for (loop=0 ; loop<memGlobs.endStopID ; loop++){
		if (memGlobs.debugAllocCount == memGlobs.stopID[loop]) Error_DebugBreak();
	}
	for (loop=0 ; loop<memGlobs.endStopAddr ; loop++){
		if (mem == memGlobs.stopAddr[loop]) Error_DebugBreak();
	}

	memGlobs.debugAllocCount++;

	return mem;
}

VOID Mem_FreeDebug(LPVOID addr, ULONG line, LPUCHAR file){

	SLONG loop;
	ULONG sub, found = 0;

	if (!addr) {
		Error_Debug(Error_Format("%s(%i): Warning: NULL passed as memory address to Mem_Free()\n", file, line));
		return;
	}

	for (loop=memGlobs.lastAlloc ; loop>=0 ; loop--){
		if (memGlobs.debugEntry[loop].flags & MEMORY_DEBUG_FLAG_UNFREED){
			if (memGlobs.debugEntry[loop].addr == addr){
				memGlobs.totalDeAlloc += memGlobs.debugEntry[loop].size;
				memGlobs.debugEntry[loop].flags &= ~MEMORY_DEBUG_FLAG_UNFREED;
				memGlobs.debugEntry[loop].flags &= ~MEMORY_DEBUG_FLAG_REPORT;
				found = 1;
				break;
			}
		}
	}
	if (loop < 0) {
		for (loop=memGlobs.lastAlloc ; loop<MEMORY_DEBUG_MAXNUMALLOC ; loop++){
			if (memGlobs.debugEntry[loop].flags & MEMORY_DEBUG_FLAG_UNFREED){
				if (memGlobs.debugEntry[loop].addr == addr){
					memGlobs.totalDeAlloc += memGlobs.debugEntry[loop].size;
					memGlobs.debugEntry[loop].flags &= ~MEMORY_DEBUG_FLAG_UNFREED;
					memGlobs.debugEntry[loop].flags &= ~MEMORY_DEBUG_FLAG_REPORT;
					found = 1;
					break;
				}
			}
		}
	}

	for (sub=0 ; sub<memGlobs.endStopID ; sub++){
		if (loop == (SLONG) memGlobs.stopID[sub]) Error_DebugBreak();
	}
	for (sub=0 ; sub<memGlobs.endStopAddr ; sub++){
		if (addr == memGlobs.stopAddr[sub]) Error_DebugBreak();
	}

	if (found) free(addr);
	else //Error_Fatal(TRUE, Error_Format("%s(%i): Warning - Attempt to free an unallocated address (0x%0.8x)\n", file, line, addr));
		Error_Debug(Error_Format("%s(%i): Warning - Attempt to free an unallocated address (0x%0.8x)\n", file, line, addr));
}

LPVOID Mem_ReAllocDebug(LPVOID addr, ULONG size, ULONG line, LPUCHAR file){

	LPVOID newAddr;
	ULONG loop, oldsize;

	if (addr) {

		if (size) {

			for (loop=0 ; loop<MEMORY_DEBUG_MAXNUMALLOC ; loop++){
				if (memGlobs.debugEntry[loop].flags & MEMORY_DEBUG_FLAG_UNFREED){
					if (memGlobs.debugEntry[loop].addr == addr){
						oldsize = memGlobs.debugEntry[loop].size;
						break;
					}
				}
			}

			if (loop == MEMORY_DEBUG_MAXNUMALLOC) Error_Out(TRUE, "%s(%i): Fatal: %s\n", file, line, "Attempt to Mem_ReAlloc() non-Mem_Alloc()ed or freed memory\nOr MEMORY_DEBUG_MAXNUMALLOC overflowed!!!");

			if (newAddr = malloc(size)){

				memGlobs.debugEntry[loop].addr = newAddr;
				memGlobs.debugEntry[loop].size = size;
				memcpy(newAddr, addr, min(size, oldsize));

				// Adjust the total allocation counter...
				memGlobs.totalAlloc += size - oldsize;

				free(addr);
				return newAddr;

			} else Error_Debug(Error_Format("%s(%i): Error: Unable to reallocate %i bytes of memory", file, line, size));

		} else Mem_FreeDebug(addr, line, file);

	} else {

		return Mem_AllocDebug(size, line, file);

	}

	return NULL;
}

VOID Mem_Debug_StopAtID(ULONG id){

	if (MEMORY_DEBUG_MAXSTOPS == memGlobs.endStopID) Error_Fatal(TRUE, "Too many stops specified");
	memGlobs.stopID[memGlobs.endStopID++] = id;
}

VOID Mem_Debug_StopAtAddress(LPVOID addr){

	if (MEMORY_DEBUG_MAXSTOPS == memGlobs.endStopAddr) Error_Fatal(TRUE, "Too many stops specified");
	memGlobs.stopAddr[memGlobs.endStopAddr++] = addr;
}

VOID Mem_Debug_FillWith(LPVOID addr, ULONG value, ULONG size){

	ULONG loop;

	for (loop=0 ; loop<(size/4) ; loop++) ((LPULONG)addr)[loop] = value;
	for (loop=0 ; loop<(size%4) ; loop++) ((LPUCHAR)addr)[size-loop] = ((LPUCHAR)&value)[4-loop];
}

int Mem_Debug_DumpMemorySort(const void *elem1, const void *elem2) {

	struct Mem_Debug_Entry *a = (struct Mem_Debug_Entry *) elem1;
	struct Mem_Debug_Entry *b = (struct Mem_Debug_Entry *) elem2;

	if (a->addr < b->addr) return -1;
	if (a->addr > b->addr) return 1;

	return 0;
}

VOID Mem_Debug_DumpMemory(LPUCHAR fname) {

#include <stdio.h>

	FILE *ofp;
	ULONG loop;

	qsort(memGlobs.debugEntry, MEMORY_DEBUG_MAXNUMALLOC, sizeof(memGlobs.debugEntry[0]), Mem_Debug_DumpMemorySort);

	if (ofp = fopen(fname, "w")) {
		for (loop=0 ; loop<MEMORY_DEBUG_MAXNUMALLOC ; loop++) {
			if (memGlobs.debugEntry[loop].flags & MEMORY_DEBUG_FLAG_UNFREED) {
				fprintf(ofp, "0x%0.8x - 0x%0.8x (%0.5d bytes) in %s(%i)\n", memGlobs.debugEntry[loop].addr, (ULONG) memGlobs.debugEntry[loop].addr + memGlobs.debugEntry[loop].size, memGlobs.debugEntry[loop].size, memGlobs.debugEntry[loop].allocFile, memGlobs.debugEntry[loop].allocLine);
			}
		}
		fclose(ofp);
	}
}

#endif

/*********************************************************************
 ****** Backwards compatibility handle functions
 *********************************************************************/

#ifdef _DEBUG
ULONG Mem_AllocHandleDebug(ULONG size, ULONG line, LPUCHAR file){
#else
ULONG Mem_AllocHandle(ULONG size){
#endif //_DEBUG

	// Simple backwards compatability routine...

	ULONG loop;

	for (loop=0 ; loop<MEMORY_MAXHANDLES ; loop++){
		if (!(memGlobs.handleList[loop].flags & MEMORY_HANDLE_FLAG_USED)){

#ifdef _DEBUG
			memGlobs.handleList[loop].addr = Mem_AllocDebug(size, line, file);
#else
			memGlobs.handleList[loop].addr = Mem_Alloc(size);
#endif //_DEBUG

			memGlobs.handleList[loop].flags |= MEMORY_HANDLE_FLAG_USED;
			return loop;
		}
	}

	Error_Fatal(TRUE, "Run out of memory handles");
	return -1;
}

VOID Mem_FreeHandle(ULONG handle){

	if (handle >= 0 && handle < MEMORY_MAXHANDLES){
		if (memGlobs.handleList[handle].flags & MEMORY_HANDLE_FLAG_USED){
			Mem_Free(memGlobs.handleList[handle].addr);
			memGlobs.handleList[handle].addr = NULL;
			memGlobs.handleList[handle].flags = 0x000000000;
		} else Error_Warn(TRUE, "Handle has already been freed");
	} else Error_Warn(TRUE, "Handle is out of range");
}

LPVOID Mem_AddressHandle(ULONG handle){

	if (handle >= 0 && handle < MEMORY_MAXHANDLES){
		if (memGlobs.handleList[handle].flags & MEMORY_HANDLE_FLAG_USED){

			return memGlobs.handleList[handle].addr;

		} else Error_Warn(TRUE, "Handle has already been freed");
	} else Error_Warn(TRUE, "Handle is out of range");

	return NULL;
}


LPVOID Check_Alloc(ULONG size, LPUCHAR file, ULONG line) {
	return malloc(size);
}
LPVOID Check_ReAlloc(LPVOID addr, ULONG size, LPUCHAR file, ULONG line){
	return realloc(addr, size);
}
VOID Check_Free(LPVOID addr, LPUCHAR file, ULONG line){
	free(addr);
}
