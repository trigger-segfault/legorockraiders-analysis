
#ifndef LEGORR__NERPS_H
#define LEGORR__NERPS_H

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>  // for BOOL typedef?


#pragma region /// TYPES ////////////////////////////////

enum NERPSFuncArgs
{
	NERPS_ARGS_0          = 0, // takes 0 arguments, returns value
	NERPS_ARGS_1          = 1, // takes 1 arguments, returns value
	NERPS_ARGS_2          = 2, // takes 2 arguments, returns value
	NERPS_ARGS_0_NORETURN = 3, // takes 0 arguments, no return
	NERPS_ARGS_1_NORETURN = 4, // takes 1 arguments, no return
	NERPS_ARGS_2_NORETURN = 5, // takes 2 arguments, no return
	NERPS_ARGS_3_NORETURN = 6, // takes 3 arguments, no return
	NERPS_END_OF_LIST     = 7, // invalid (end of list)
};

typedef int (__cdecl *NERPSFuncPtr)(int*);

struct NERPSFunction
{
	const char* funcName;
	NERPSFuncPtr function;
	NERPSFuncArgs arguments;
};

#pragma endregion


#pragma region /// DEFINES //////////////////////////////

// functionality for this is hardcoded
#define NERPSFUNC_STOP 0

#pragma endregion


#pragma region /// GLOBALS //////////////////////////////

// last item is "**End Of List**"
// <LegoRR.exe @004a6948 -> 004a7710>
extern NERPSFunction g_NERPS_FUNCTIONS[294]; // defined in NERPs_FunctionsArray.cpp

// <LegoRR.exe @00500958>
static int g_NERPS_REGISTERS[8];

// <LegoRR.exe @005009a0>
static float g_NERPS_TIMERS[4];

#pragma endregion


#endif /* LEGORR__NERPS_H */
