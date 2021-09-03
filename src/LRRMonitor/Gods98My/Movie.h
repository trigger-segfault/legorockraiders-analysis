#pragma once

#include "../framework.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Typedefs
 **********************************************************************************/

#pragma region Typedefs

 // C wrapper typedef around actual class
//typedef void* lpMovie;
typedef void Movie_t;

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @00472820>
Movie_t* __cdecl Movie_Load(const char* fName);

// <LegoRR.exe @00472930>
void __cdecl Movie_GetSize(Movie_t* movie, OUT unsigned long* width, OUT unsigned long* height);

// <LegoRR.exe @00472980>
long long __cdecl Movie_GetLength(Movie_t* movie);

// <LegoRR.exe @00472990>
BOOL __cdecl Movie_Update(Movie_t* movie);

// <LegoRR.exe @004729b0>
void __cdecl Movie_Free(Movie_t* movie);

#pragma endregion

}
