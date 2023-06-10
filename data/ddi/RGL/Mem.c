
#include <malloc.h>

#include "Standard.h"
#include "Errors.h"
#include "Utils.h"
#include "Main.h"
#include "Mem.h"

#ifdef _DEBUG

#define MEM_MAXMODULES			256

struct MemModuleData {

	ULONG currAllocated;
	ULONG maxAllocated;
	ULONG totalAllocated;
};

struct MemGlobs {

	LPUCHAR fileNameList[MEM_MAXMODULES];
	ULONG fileNameCount;

	LPVOID *recordList;
	ULONG recordCount, recordListSize, minFreeRecord, maxFreeRecord;

	ULONG currAllocated, maxAllocated, maxAllocatedFile, maxAllocatedLine;

	struct MemModuleData moduleData[MEM_MAXMODULES];

} memGlobs = { 0 };

size_t Mem_Debug_Size(LPVOID addr) {

	LPUWORD realAddr = &((LPUWORD) addr)[-2];

	return _msize(realAddr) - (sizeof(realAddr[0]) + sizeof(realAddr[1]));
}

BOOL Mem_Debug_Dump(LPUCHAR fname, LPUCHAR file, ULONG line) {

	FILE *fp;
	ULONG loop, blockSize, count = 0, size = 0;
	LPUWORD addr;
	UCHAR msg[1024];

	if (NULL == fname || (fp = fopen(fname, "w"))) {

		sprintf(msg, "***********************************************************");
		if (fname) fprintf(fp, "%s(%d) : %s\n", file, line, msg);
		else Error_Out(TRUE, FALSE, file, line, msg);

		sprintf(msg, "**** Memory Dump");
		if (fname) fprintf(fp, "%s(%d) : %s\n", file, line, msg);
		else Error_Out(TRUE, FALSE, file, line, msg);

		sprintf(msg, "***********************************************************");
		if (fname) fprintf(fp, "%s(%d) : %s\n", file, line, msg);
		else Error_Out(TRUE, FALSE, file, line, msg);

		for (loop=0 ; loop<memGlobs.recordCount ; loop++) {
			if (addr = memGlobs.recordList[loop]) {

				blockSize = _msize(memGlobs.recordList[loop]) - (sizeof(addr[0]) + sizeof(addr[1]));

				sprintf(msg, "Unfreed block at 0x%0.8x, size %d byte%s", &addr[2], blockSize, (1==blockSize)?"":"s");
				if (fname) fprintf(fp, "%s(%d) : %s\n", memGlobs.fileNameList[addr[0]], addr[1], msg);
				else Error_Out(TRUE, FALSE, memGlobs.fileNameList[addr[0]], addr[1], msg);

				count++;
				size += blockSize;
			}
		}

		sprintf(msg, "***********************************************************");
		if (fname) fprintf(fp, "%s(%d) : %s\n", file, line, msg);
		else Error_Out(TRUE, FALSE, file, line, msg);

		sprintf(msg, "**** %d unfreed block%s.", count, (1==count)?"":"s");
		if (fname) fprintf(fp, "%s(%d) : %s\n", file, line, msg);
		else Error_Out(TRUE, FALSE, file, line, msg);

		sprintf(msg, "**** %d byte%s left unfreed.", size, (1==size)?"":"s");
		if (fname) fprintf(fp, "%s(%d) : %s\n", file, line, msg);
		else Error_Out(TRUE, FALSE, file, line, msg);

		sprintf(msg, "**** %d maximum simulateously allocated bytes", memGlobs.maxAllocated);
		if (fname) fprintf(fp, "%s(%d) : %s\n", file, line, msg);
		else Error_Out(TRUE, FALSE, file, line, msg);

		sprintf(msg, "**** due to %s(%d)", memGlobs.fileNameList[memGlobs.maxAllocatedFile], memGlobs.maxAllocatedLine);
		if (fname) fprintf(fp, "%s(%d) : %s\n", file, line, msg);
		else Error_Out(TRUE, FALSE, file, line, msg);

		for (loop=0 ; loop<memGlobs.fileNameCount ; loop++) {

			sprintf(msg, "***********************************************************");
			if (fname) fprintf(fp, "%s(%d) : %s\n", file, line, msg);
			else Error_Out(TRUE, FALSE, file, line, msg);

			sprintf(msg, "**** %s: ", memGlobs.fileNameList[loop]);
			if (fname) fprintf(fp, "%s(%d) : %s\n", file, line, msg);
			else Error_Out(TRUE, FALSE, file, line, msg);

			sprintf(msg, "**** %d total, %d max", memGlobs.moduleData[loop].totalAllocated, memGlobs.moduleData[loop].maxAllocated);
			if (fname) fprintf(fp, "%s(%d) : %s\n", file, line, msg);
			else Error_Out(TRUE, FALSE, file, line, msg);
		}

		sprintf(msg, "***********************************************************");
		if (fname) fprintf(fp, "%s(%d) : %s\n", file, line, msg);
		else Error_Out(TRUE, FALSE, file, line, msg);

		if (fname) fclose(fp);

		return TRUE;
	}

	return FALSE;
}

VOID Mem_Debug_Ditch(VOID) {

	ULONG loop;

	for (loop=0 ; loop<memGlobs.recordCount ; loop++) {
		free(memGlobs.recordList[loop]);
	}

	Main_Abort();
}

static ULONG Mem_Debug_GetFileNameIndex(LPUCHAR file) {

	ULONG loop;

	for (loop=0 ; loop<memGlobs.fileNameCount ; loop++) {
		if (0 == stricmp(file, memGlobs.fileNameList[loop])) {
			return loop;
		}
	}

	Error_Overflow(memGlobs.fileNameCount, MEM_MAXMODULES);

	memGlobs.fileNameList[memGlobs.fileNameCount] = malloc(strlen(file) + 1);
	sprintf(memGlobs.fileNameList[memGlobs.fileNameCount], "%s", file);

	return memGlobs.fileNameCount++;
}

LPVOID Mem_Debug_Alloc(ULONG size, LPUCHAR file, ULONG line) {

	LPUWORD addr = malloc(sizeof(addr[0]) + sizeof(addr[1]) + size);
	ULONG useRecord = -1;

	addr[0] = (UWORD) Mem_Debug_GetFileNameIndex(file);
	addr[1] = (UWORD) line;

	memGlobs.currAllocated += size;
	if (memGlobs.currAllocated > memGlobs.maxAllocated) {
		memGlobs.maxAllocated = memGlobs.currAllocated;
		memGlobs.maxAllocatedFile = addr[0];
		memGlobs.maxAllocatedLine = addr[1];
	}
	memGlobs.moduleData[addr[0]].totalAllocated += Mem_Debug_Size(&addr[2]);
	memGlobs.moduleData[addr[0]].currAllocated += Mem_Debug_Size(&addr[2]);
	memGlobs.moduleData[addr[0]].maxAllocated = max(memGlobs.moduleData[addr[0]].maxAllocated, memGlobs.moduleData[addr[0]].currAllocated);

	if (memGlobs.recordCount > memGlobs.minFreeRecord) {
		for ( ; memGlobs.minFreeRecord<memGlobs.maxFreeRecord ; memGlobs.minFreeRecord++) {
			if (NULL == memGlobs.recordList[memGlobs.minFreeRecord]) {
				useRecord = memGlobs.minFreeRecord++;
				break;
			}
		}
	}

	if (-1 == useRecord) {
		if (memGlobs.recordCount == memGlobs.recordListSize) {
			memGlobs.recordListSize += max(10, memGlobs.recordListSize / 10);
			memGlobs.recordList = realloc(memGlobs.recordList, sizeof(memGlobs.recordList[0]) * memGlobs.recordListSize);
		}
		useRecord = memGlobs.recordCount++;
		memGlobs.minFreeRecord = memGlobs.recordCount;
		memGlobs.maxFreeRecord = 0;
	}

	memGlobs.recordList[useRecord] = addr;

	return &addr[2];
}

LPVOID Mem_Debug_AllocClear(ULONG size, LPUCHAR file, ULONG line) {

	LPVOID addr;

	if (addr = Mem_Debug_Alloc(size, file, line)) {
		memset(addr, 0, Mem_Size(addr));
	}

	return addr;
}

VOID Mem_Debug_Free(LPVOID addr, LPUCHAR file, ULONG line) {

	ULONG loop;

	if (NULL != addr) {
	
		LPUWORD realAddr = &((LPUWORD) addr)[-2];

		memGlobs.currAllocated -= Mem_Debug_Size(addr);
		memGlobs.moduleData[realAddr[0]].currAllocated -= Mem_Debug_Size(addr);

		for (loop=0 ; loop<memGlobs.recordCount ; loop++) {
			if (realAddr == memGlobs.recordList[loop]) {
				memGlobs.recordList[loop] = NULL;
				break;
			}
		}

		Error_Fatal(loop == memGlobs.recordCount, "Memory allocation not found (Mem_Alloc() not used)");

		memGlobs.minFreeRecord = min(memGlobs.minFreeRecord, loop);
		memGlobs.maxFreeRecord = max(memGlobs.maxFreeRecord, loop + 1);

		free(realAddr);

	} else Error_Fatal(TRUE, "NULL passed to Mem_Free()");
}

LPVOID Mem_Debug_ReAlloc(LPVOID addr, ULONG size, LPUCHAR file, ULONG line) {

	// Force the block to be copied to ensure no pointers to it are being kept...

	LPVOID newAddr = Mem_Debug_Alloc(size, file, line);
	ULONG oldSize = addr?_msize(&((LPUWORD) addr)[-2]):0;

	memcpy(newAddr, addr, min(oldSize, size));
	if (NULL != addr) Mem_Debug_Free(addr, file, line);

	return newAddr;
}

LPVOID Mem_Debug_ReAllocClear(LPVOID addr, ULONG newSize, LPUCHAR file, ULONG line) {

	ULONG oldSize = addr?Mem_Size(addr):0;
	LPVOID newAddr = Mem_Debug_ReAlloc(addr, newSize, file, line);

	if (Mem_Size(newAddr) > oldSize) memset(&((LPUCHAR)newAddr)[oldSize], 0, Mem_Size(newAddr) - oldSize);
	return newAddr;
}

__inline LPUCHAR Mem_Debug_CopyString(LPUCHAR str, LPUCHAR file, ULONG line) {

	LPUCHAR ds = Mem_Debug_Alloc(strlen(str)+1, file, line);
	strcpy(ds, str);
	return ds;
}

#else // _DEBUG

__inline LPVOID Mem_ReAllocClear(LPVOID mem, ULONG newSize) {

	ULONG oldSize = mem?Mem_Size(mem):0;
	LPVOID newMem = Mem_ReAlloc(mem, newSize);

	if (Mem_Size(newMem) > oldSize) memset(&((LPUCHAR)newMem)[oldSize], 0, Mem_Size(newMem) - oldSize);
	return newMem;
}

__inline LPUCHAR Mem_CopyString(LPUCHAR str) {

	LPUCHAR ds = Mem_Alloc(strlen(str)+1);
	strcpy(ds, str);
	return ds;
}

__inline LPVOID Mem_Alloc(ULONG size) {

	return malloc(size);
}

__inline LPVOID Mem_AllocClear(ULONG size) {
	
	LPVOID addr = Mem_Alloc(size);
	memset(addr, 0, Mem_Size(addr));

	return addr;
}

__inline VOID Mem_Free(LPVOID addr) {
	
	free(addr);
}

__inline LPVOID Mem_ReAlloc(LPVOID addr, ULONG newSize) {
	
	return realloc(addr, newSize);
}

__inline ULONG Mem_Size(LPVOID addr) {
	
	return _msize(addr);
}

#endif // _DEBUG

__inline LPVOID Mem_Copy(LPVOID dest, LPVOID source, ULONG size) {

	Error_Fatal(NULL==dest, "Null passed as destination to Mem_Copy()");
	Error_Fatal(NULL==source, "Null passed as source to Mem_Copy()");
	Error_Fatal(0==size, "Zero passed as size to Mem_Copy()");

	return memcpy(dest, source, size);
}

__inline LPVOID Mem_CopyDuplicate(LPVOID dest, LPVOID source) {

	ULONG destSize, sourceSize;

	Error_Fatal(NULL==dest, "Null passed as destination to Mem_CopyDuplicate()");
	Error_Fatal(NULL==source, "Null passed as source to Mem_CopyDuplicate()");

	destSize = Mem_Size(dest);
	sourceSize = Mem_Size(source);

	Error_Fatal(sourceSize != destSize, "Blocks are of different sizes");

	if (sourceSize == destSize) return Mem_Copy(dest, source, sourceSize);
	
	return NULL;
}

__inline LPVOID Mem_Set(LPVOID dest, UCHAR value, ULONG size) {

	return memset(dest, value, size);
}

__inline SLONG Mem_Compare(LPVOID target, LPVOID test, ULONG size) {

	Error_Fatal(NULL==target, "Null passed as target to Mem_Compare()");
	Error_Fatal(NULL==test, "Null passed as test to Mem_Compare()");
	Error_Fatal(0==size, "Zero passed as size to Mem_Compare()");

	return memcmp(target, test, size);
}

#ifdef _DEBUG

__inline LPVOID Mem_Debug_Duplicate(LPVOID source, LPUCHAR file, ULONG line) {

	LPVOID dest = NULL;
	ULONG size;

	Error_Fatal(NULL == source, "NULL passed to Mem_Duplicate()");
	
	if (size = Mem_Size(source)) {
		if (dest = Mem_Debug_Alloc(size, file, line)) Mem_Copy(dest, source, size);
	}

	Error_Fatal(NULL==dest, Error_Format("Failed to Mem_Alloc(%i bytes) in Mem_Duplicate()", size));

	return dest;
}

#else

__inline LPVOID Mem_Duplicate(LPVOID source) {

	LPVOID dest = NULL;
	ULONG size;

	Error_Fatal(NULL == source, "NULL passed to Mem_Duplicate()");

	if (size = Mem_Size(source)) {
		if (dest = Mem_Alloc(size)) Mem_Copy(dest, source, size);
	}

	Error_Fatal(NULL==dest, Error_Format("Failed to Mem_Alloc(%i bytes) in Mem_Duplicate()", size));

	return dest;
}

#endif // _DEBUG
