#pragma once

#include "../framework.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define MEMORY_MAXHANDLES					2000

#pragma endregion

/**********************************************************************************
 ******** Enumerations
 **********************************************************************************/

#pragma region Enums

#define MEMORY_HANDLE_FLAG_USED				0x00000001

#pragma endregion

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

typedef struct Mem_Handle
{
	/// FIX: stored as LPVOID*, rather than LPVOID
	/*0,4*/ void* addr;
	/*4,4*/ unsigned long flags;
	/*8*/
} Mem_Handle;
static_assert(sizeof(Mem_Handle) == 0x8, "");


typedef struct Mem_Globs
{
	/*0000,3e80*/ Mem_Handle handleList[MEMORY_MAXHANDLES];
	/*3e80,4*/ unsigned long flags;
	/*3e84*/
} Mem_Globs;
static_assert(sizeof(Mem_Globs) == 0x3e84, "");

#pragma endregion

/**********************************************************************************
 ******** Globals
 **********************************************************************************/

#pragma region Globals

// <LegoRR.exe @00545a20>
extern Mem_Globs memGlobs;

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

/*__inline void* __cdecl Mem_Alloc(unsigned long size) { return std::malloc(size); }
__inline void* __cdecl Mem_ReAlloc(void* addr, unsigned long size) { return std::realloc(addr, size); }
__inline void __cdecl Mem_Free(void* addr) { std::free(addr); }*/


// <LegoRR.exe @004896b0>
void __cdecl Mem_Initialise(void);

//void __cdecl Mem_Shutdown(int freeAll);

// <LegoRR.exe @004896d0>
unsigned long __cdecl Mem_AllocHandle(unsigned long size);

// <LegoRR.exe @00489720>
void __cdecl Mem_FreeHandle(unsigned long handle);

// <LegoRR.exe @00489760>
void* __cdecl Mem_AddressHandle(unsigned long handle);

#pragma endregion

}
