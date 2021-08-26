
#ifndef _GODS98_MEMORY_H_
#define _GODS98_MEMORY_H_

#include "Standard.h"

#ifdef _DEBUG

//	#define MEMORY_DEBUG_MAXNUMALLOC		(2 * 1024 * 1024)
	#define MEMORY_DEBUG_MAXNUMALLOC		(50 * 1024)
	#define MEMORY_DEBUG_MAXSTOPS			100
	#define MEMORY_DEBUG_FLAG_UNFREED		0x00000001
	#define MEMORY_DEBUG_FLAG_REPORT		0x00000002

	typedef struct Mem_Debug_Entry {

		LPVOID addr;
		ULONG allocLine;
		LPUCHAR allocFile;
		ULONG size;
		ULONG id;

		ULONG flags;

	} Mem_Debug_Entry;

#endif // _DEBUG

#define MEMORY_MAXHANDLES					2000
#define MEMORY_HANDLE_FLAG_USED				0x00000001

typedef struct Mem_Handle {

	LPVOID *addr;
	ULONG flags;

} Mem_Handle;


typedef struct Mem_Globs {

#ifdef _DEBUG

	Mem_Debug_Entry debugEntry[MEMORY_DEBUG_MAXNUMALLOC];
	ULONG debugAllocCount;
	ULONG lastAlloc;
	ULONG maxSimul;
	ULONG totalAlloc;
	ULONG totalDeAlloc;
	ULONG stopID[MEMORY_DEBUG_MAXSTOPS];
	LPVOID stopAddr[MEMORY_DEBUG_MAXSTOPS];
	ULONG endStopID, endStopAddr;
	BOOL recordMalloc;

#endif // _DEBUG

	Mem_Handle handleList[MEMORY_MAXHANDLES];
	ULONG flags;

} Mem_Globs, *lpMem_Globs;

#ifdef _DEBUG

	#define Mem_Alloc(s)			Mem_AllocDebug((s),__LINE__,__FILE__)
	#define Mem_Free(a)				{Mem_FreeDebug((a),__LINE__,__FILE__);a=NULL;}
	#define Mem_ReAlloc(a,s)		Mem_ReAllocDebug((a),(s),__LINE__,__FILE__)
	#define Mem_AllocHandle(s)		Mem_AllocHandleDebug((s),__LINE__,__FILE__)
	#define Mem_StopAtID(i)			Mem_Debug_StopAtID((i))
	#define Mem_StopAtAddress(a)	Mem_Debug_StopAtAddress((LPVOID)(a))
	#define Mem_DebugTrash(a,v,s)	Mem_Debug_FillWith((a),(v),(s))

#else
	
	#define Mem_StopAtID(i)			(i)
	#define Mem_StopAtAddress(i)	(i)
	#define Mem_DebugTrash(a,v,s)

#endif // _DEBUG


/*********************************************************************
 ****** Non-Debug Memory Functions
 *********************************************************************/
//#define _CHECKMEM
#ifdef _CHECKMEM
#pragma message("Memory checking enabled")
	LPVOID Check_Alloc(ULONG size, LPUCHAR file, ULONG line);
	LPVOID Check_ReAlloc(LPVOID addr, ULONG size, LPUCHAR file, ULONG line);
	VOID Check_Free(LPVOID addr, LPUCHAR file, ULONG line);
#define Mem_Alloc(x) Check_Alloc(x, __FILE__, __LINE__)
#define Mem_ReAlloc(x,y) Check_ReAlloc(x, y, __FILE__, __LINE__)
#define Mem_Free(x) Check_Free(x, __FILE__, __LINE__)
#else
#ifndef _DEBUG

__inline LPVOID Mem_Alloc(ULONG size) { return malloc(size); }
__inline LPVOID Mem_ReAlloc(LPVOID addr, ULONG size)	{ return realloc(addr, size); }
__inline VOID Mem_Free(LPVOID addr)						{ free(addr); }

#endif // !_DEBUG
#endif // _CHECKMEM

/* Prototypes */

extern void __cdecl Mem_Initialise(void );
extern void __cdecl Mem_Shutdown(int freeAll);
#ifdef _DEBUG
extern VOID __cdecl Mem_Record(BOOL on);
extern void *__cdecl Mem_AllocDebug(unsigned long size,unsigned long line,unsigned char *file);
extern void __cdecl Mem_FreeDebug(void *addr,unsigned long line,unsigned char *file);
extern void *__cdecl Mem_ReAllocDebug(void *addr,unsigned long size,unsigned long line,unsigned char *file);
extern void __cdecl Mem_Debug_StopAtID(unsigned long id);
extern void __cdecl Mem_Debug_StopAtAddress(void *addr);
extern unsigned long __cdecl Mem_AllocHandleDebug(unsigned long size,unsigned long line,unsigned char *file);
extern void __cdecl Mem_Debug_FillWith(void *addr,unsigned long value,unsigned long size);
#else
#ifndef _CHECKMEM
extern void *__cdecl Mem_Alloc(unsigned long size);
extern void __cdecl Mem_Free(void *addr);
extern void *__cdecl Mem_ReAlloc(void *addr,unsigned long size);
#endif // CHECKMEM
extern unsigned long __cdecl Mem_AllocHandle(unsigned long size);
#endif // _DEBUG
extern void __cdecl Mem_FreeHandle(unsigned long handle);
extern void *__cdecl Mem_AddressHandle(unsigned long handle);

#endif // _GODS98_MEMORY_H_
