// SharedBuffers.h : Defines a system for allocating global buffers of data, that can be accessed
//                   without passing around a pointer. Only used for files, but it doesn't have to be.
//
/// STATUS: [COMPLETE]

#include "SharedBuffers.h"


using namespace lego;
using namespace lego::file;


#pragma region Globals

// /// PRIVATE:
// // <LegoRR.exe @00545a20 -> 005498a0>
// SharedBuffersManager lego::globals::g_SharedBufs;

/// PRIVATE:
// <LegoRR.exe @00545a20 -> 005498a0>
SharedBuffer lego::globals::g_SharedBuffers_TABLE[SHAREDBUFFERS_COUNT /*2000*/];

#pragma endregion


#pragma region Functions

// <LegoRR.exe @004896b0>
void __cdecl lego::file::InitSharedBuffers(void)
{
	// lazy solution for below
	//std::memset(globals::g_SharedBuffers_TABLE, 0, sizeof(globals::g_SharedBuffers_TABLE));
	for (int i = 0; i < SHAREDBUFFERS_COUNT; i++) {
		globals::g_SharedBuffers_TABLE[i].bufferData = nullptr;
		globals::g_SharedBuffers_TABLE[i].flags = SHAREDBUFFER_NONE /*0x0*/; // !isUsed
	}
}

// <LegoRR.exe @004896d0>
int __cdecl lego::file::SharedBuffer_Open(size_t size)
{
	for (int i = 0; i < SHAREDBUFFERS_COUNT; i++) {
		if (!(globals::g_SharedBuffers_TABLE[i].flags & SHAREDBUFFER_ISUSED)) { // !isUsed
			void* buffer = std::malloc(size);
			globals::g_SharedBuffers_TABLE[i].bufferData = buffer;
			globals::g_SharedBuffers_TABLE[i].flags |= SHAREDBUFFER_ISUSED; // isUsed
			return i;
		}
	}
	return -1;
}

// <LegoRR.exe @00489720>
void __cdecl lego::file::SharedBuffer_Close(int sharedIndex)
{
	unsigned int i = (unsigned int)sharedIndex;
	if ((unsigned int)i < SHAREDBUFFERS_COUNT && (globals::g_SharedBuffers_TABLE[i].flags & SHAREDBUFFER_ISUSED)) { // isUsed
		std::free(globals::g_SharedBuffers_TABLE[i].bufferData);
		globals::g_SharedBuffers_TABLE[i].bufferData = nullptr;
		globals::g_SharedBuffers_TABLE[i].flags = SHAREDBUFFER_NONE /*0x0*/; // !isUsed
	}
}

// <LegoRR.exe @00489760>
void* __cdecl lego::file::SharedBuffer_GetData(int sharedIndex)
{
	unsigned int i = (unsigned int)sharedIndex;
	if ((unsigned int)i < SHAREDBUFFERS_COUNT && (globals::g_SharedBuffers_TABLE[i].flags & SHAREDBUFFER_ISUSED)) { // isUsed
		return globals::g_SharedBuffers_TABLE[i].bufferData;
	}
	return nullptr;
}

#pragma endregion

