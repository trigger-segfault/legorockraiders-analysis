#pragma once

#include "../framework.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define COMPRESSION_UNPACK_BUFFER_EXTEND 20000

#pragma endregion

/**********************************************************************************
 ******** Enumerations
 **********************************************************************************/

#pragma region Enums

#define RNC_COMPRESS_BEST 1
#define RNC_COMPRESS_FAST 2

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @0049ca80>
unsigned int __cdecl RNC_Uncompress(void* bufferIn, void** bufferOut);

#pragma endregion

}
