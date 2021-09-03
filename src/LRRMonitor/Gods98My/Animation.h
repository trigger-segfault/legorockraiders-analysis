#pragma once

#include "../framework.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Typedefs
 **********************************************************************************/

#pragma region Typedefs

// C wrapper typedef around actual class
//typedef void* lpAnimation;
typedef void Animation_t;

#pragma endregion

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

typedef struct Animation_Globs
{
	/*0,1*/ bool g98NoAvis;
	/*1,3*/ unsigned char padding1[3];
	/*4,4*/ IDirectDraw4* ddraw;
	/*8*/
} Animation_Globs;
static_assert(sizeof(Animation_Globs) == 0x8, "");

#pragma endregion

/**********************************************************************************
 ******** Globals
 **********************************************************************************/

#pragma region Globals

// <LegoRR.exe @00534998>
extern Animation_Globs animationGlobs;

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @0047ef40>
void __cdecl Animation_Initialise(IDirectDraw4* directDraw);

// <LegoRR.exe @0047ef50>
Animation_t* __cdecl Animation_Load(const char* fName);

// <LegoRR.exe @0047efb0>
BOOL __cdecl Animation_Update(Animation_t* anim);

// <LegoRR.exe @0047efc0>
void __cdecl Animation_BlitToBackBuffer(Animation_t* anim, const RECT* dest);

// <LegoRR.exe @0047f000>
void __cdecl Animation_SetTime(Animation_t* anim, unsigned int time);

// <LegoRR.exe @0047f010>
unsigned int __cdecl Animation_GetTime(Animation_t* anim);

// <LegoRR.exe @0047f020>
unsigned int __cdecl Animation_GetLength(Animation_t* anim);

// <LegoRR.exe @0047f030>
void __cdecl Animation_Free(Animation_t* anim);

// <LegoRR.exe @0047f040>
BOOL __cdecl Animation_IsOk(Animation_t* anim);

#pragma endregion

}
