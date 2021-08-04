#pragma once
#ifndef LEGORR__MAIN_H
#define LEGORR__MAIN_H

#define s_Dev_SourceSafe__Main_c "C:\\Dev\\SourceSafe\\gods98_dx6\\gods98\\src\\Main.c"

#include "Common.h"


// calls `Direct3DRMCreate`
// <LegoRR.exe @00478490>
BOOL __cdecl Main_Direct3DRMCreate(int param_1, undefined** param_2, code** param_3, undefined4 param_4);

// calls `DirectDrawCreate`
// if (condition != 0) calls `ShowCursor(FALSE)`
// <LegoRR.exe @0047c8d0>
BOOL __cdecl Main_DirectDrawCreate(BOOL condition, unsigned int param_2, undefined4 param_3, int* param_4, int param_5, int param_6, int screenWidth, int screenHeight);

// <LegoRR.exe @0047d1a0>
BOOL __cdecl Main_CreateRectRgn(BOOL condition, int screenWidth, int screenHeight);


#endif /* LEGORR__MAIN_H */
