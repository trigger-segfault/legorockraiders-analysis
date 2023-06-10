
#ifndef _RGL_MEMORY_H_
#define _RGL_MEMORY_H_

#include <stdlib.h>

// Auto Prototypes
extern void *__cdecl Mem_ReAllocClear(void *mem,unsigned long newSize);
extern unsigned char *__cdecl Mem_CopyString(unsigned char *str);
extern void *__cdecl Mem_Copy(void *dest,void *source,unsigned long size);
extern void *__cdecl Mem_CopyDuplicate(void *dest,void *source);
extern void *__cdecl Mem_Set(void *dest,unsigned char value,unsigned long size);
extern long __cdecl Mem_Compare(void *target,void *test,unsigned long size);
extern void *__cdecl Mem_Duplicate(void *source);
extern void *__cdecl Mem_Debug_Alloc(unsigned long size, unsigned char *file, unsigned long line);
extern void *__cdecl Mem_Debug_AllocClear(unsigned long size, unsigned char *file, unsigned long line);
extern void __cdecl Mem_Debug_Free(void *addr, unsigned char *file, unsigned long line);
extern void *__cdecl Mem_Debug_ReAlloc(void *addr, unsigned long size, unsigned char *file, unsigned long line);
extern void *__cdecl Mem_Debug_ReAllocClear(void *addr, unsigned long newSize, unsigned char *file, unsigned long line);
extern BOOL __cdecl Mem_Debug_Dump(LPUCHAR fname, LPUCHAR file, ULONG line);
extern size_t __cdecl Mem_Debug_Size(LPVOID addr);
extern LPUCHAR __cdecl Mem_Debug_CopyString(LPUCHAR str, LPUCHAR file, ULONG line);
extern void *__cdecl Mem_Debug_Duplicate(void *source, LPUCHAR file, ULONG line);
extern VOID __cdecl Mem_Debug_Ditch(VOID);
extern LPVOID __cdecl Mem_Alloc(ULONG size);
extern LPVOID __cdecl Mem_AllocClear(ULONG size);
extern VOID __cdecl Mem_Free(LPVOID addr);
extern LPVOID __cdecl Mem_ReAlloc(LPVOID addr, ULONG newSize);
extern ULONG __cdecl Mem_Size(LPVOID addr);
// Auto Prototypes

#ifdef _DEBUG
#define Mem_Alloc(s)				Mem_Debug_Alloc((s),__FILE__,__LINE__)
#define Mem_AllocClear(s)			Mem_Debug_AllocClear((s),__FILE__,__LINE__)
#define Mem_Free(a)					Mem_Debug_Free((a),__FILE__,__LINE__)
#define Mem_ReAlloc(a,s)			Mem_Debug_ReAlloc((a),(s),__FILE__,__LINE__)
#define Mem_ReAllocClear(a,n)		Mem_Debug_ReAllocClear((a),(n),__FILE__,__LINE__)
#define Mem_Size(a)					Mem_Debug_Size(a)
#define Mem_CopyString(s)			Mem_Debug_CopyString((s),__FILE__,__LINE__)
#define Mem_Duplicate(a)			Mem_Debug_Duplicate((a),__FILE__,__LINE__)
#define Mem_Dump(f)					Mem_Debug_Dump((f),__FILE__,__LINE__)
#else // _DEBUG
#define Mem_Dump(f)
#endif // _DEBUG

#endif // !_RGL_MEMORY_H_
