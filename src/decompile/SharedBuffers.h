// SharedBuffers.h : Declares a system for allocating global buffers of data, that can be accessed
//                   without passing around a pointer. Only used for files, but it doesn't have to be.
//
/// STATUS: [COMPLETE]
/// PURPOSE: A system exclusively for reading and opening a file all at once in memory.
///          The file is then immediately closed. This is an extremely lazy solution.
///          This API is **only** used when reading level Map files.
///
/// NAMESPACE: lego::file
/// INITIALIZE: Call `InitSharedBuffers()` once on startup.
///             (no cleanup)
/// GLOBALS: private

#pragma once

#include "Common.h"



#pragma region Defines

#define SHAREDBUFFERS_COUNT 2000

#pragma endregion


#pragma region Flags
namespace lego {

/// PRIVATE:
enum SharedBufferFlags : unsigned int
{
	SHAREDBUFFER_NONE = 0,

	SHAREDBUFFER_ISUSED = 0x1,
};
DEFINE_ENUM_FLAG_OPERATORS(SharedBufferFlags)
static_assert(sizeof(SharedBufferFlags) == 0x4, "");

} /* namespace lego */
#pragma endregion


#pragma pack(push, 1)

#pragma region Types

/// PRIVATE:
struct SharedBuffer
{
	/*0,4*/ void* bufferData;
	/*4,4*/ SharedBufferFlags flags; // 0x1 == BOOL isUsed
	/*8*/
};
static_assert(sizeof(SharedBuffer) == 0x8, "");

#pragma endregion


#pragma region Globals
namespace lego::file {

// /// PRIVATE:
// // <LegoRR.exe @005349a0 - 005353bc>
// struct SharedBuffersManager
// {
// 	// <LegoRR.exe @00545a20 -> 005498a0>
// 	/*0,3e80*/ SharedBuffer SharedBuffers_TABLE[SHAREDBUFFERS_COUNT /*2000*/];
// 	/*3e80*/
// };
// static_assert(sizeof(SharedBuffersManager) == 0x3e80, "");
	
} /* namespace lego::file */
namespace lego::globals {

// /// PRIVATE:
// // <LegoRR.exe @00545a20 -> 005498a0>
// extern lego::file::SharedBuffersManager g_SharedBufs;

/// PRIVATE:
// <LegoRR.exe @00545a20 -> 005498a0>
extern SharedBuffer g_SharedBuffers_TABLE[SHAREDBUFFERS_COUNT /*2000*/];

} /* namespace logo::globals */
#pragma endregion

#pragma pack(pop)


#pragma region Functions
namespace lego::file {

/// PUBLIC:
// <LegoRR.exe @004896b0>
void __cdecl InitSharedBuffers(void);
// <LegoRR.exe @004896d0>
int __cdecl SharedBuffer_Open(size_t size);
// <LegoRR.exe @00489720>
void __cdecl SharedBuffer_Close(int sharedIndex);
// <LegoRR.exe @00489760>
void* __cdecl SharedBuffer_GetData(int sharedIndex);

} /* namespace lego::file */
#pragma endregion

