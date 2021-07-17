// MemoryInspect.h : 
//

#pragma once

#include "../Common.h"


namespace inspect {

#pragma region Types

typedef size_t RVAddress;

#pragma endregion


#pragma region Functions

void __cdecl InitMemoryInspect();

void __cdecl CleanupMemoryInspect();

RVAddress __cdecl ResolvePointer(RVAddress address);

size_t __cdecl ReadMemory(RVAddress address, void* out_buffer, size_t size);

BOOL __cdecl IsMemoryOpen();

#pragma endregion


} /* namespace inspect */
