
#ifndef LEGORR__COMMON_H
#define LEGORR__COMMON_H

// Common includes

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>  // for BOOL typedef and WINAPI functions/constants


#pragma region /// GHIDRA TYPES /////////////////////////

// types used by Ghidra for unknown data of a certain size, easier to keep these in for easy reference.
typedef unsigned char      undefined;
typedef unsigned short     undefined2;
typedef unsigned int       undefined4;
typedef unsigned long long undefined8;

#pragma endregion


#pragma region /// BASIC TYPES //////////////////////////

// Many boolean returns from LegoRR functions may have a 3rd return state for error, this enum is for that.
enum BOOL3
{
	BOOL3_FALSE = 0, // false
	BOOL3_TRUE  = 1, // true
	BOOL3_ERROR = 2, // error
};

#pragma endregion


#endif /* LEGORR__COMMON_H */
