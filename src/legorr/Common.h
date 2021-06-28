
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


#pragma region /// DEFINES //////////////////////////////

// When checking this memory address with OllyDbg, the value was 00000000h, meaning this **may** be a reference to an empty string!
// Ghidra's identifier for this location has been changed to: ""/*EMPTYSTR*/
//   allowing to inline the string value, while also commenting its usage everywhere.
// Original name assigned by Ghidra: "lpWindowName_ 004b9a14"  (space kept to prevent from replace-all)
// 
// Displayed as: ""/*EMPTYSTR*/, Runtime value: {'\0','\0','\0','\0'}
// <LegoRR.exe @004b9a14>  XREF[292]:
#define c_EMPTYSTR ""/*EMPTYSTR*/
//static char c_EMPTYSTR[4] = {'\0','\0','\0','\0'};

// Time unit (25 frames per second) as a double-precision floating point
#define TIME_UNIT  25.0
// Time unit (25 frames per second) as a single-precision floating point
#define TIME_UNITF 25.0f

#pragma endregion


#pragma region /// BASIC TYPES //////////////////////////

// Many boolean returns from LegoRR functions may have a 3rd return state for error, this enum is for that.
enum BOOL3
{
	BOOL3_FALSE = 0, // false
	BOOL3_TRUE  = 1, // true
	BOOL3_ERROR = 2, // error
};

struct LegoPoint2f
{
	/*0,4*/ float x;
	/*4,4*/ float y;
	/*8*/
};
struct LegoSize2f
{
	/*0,4*/ float width;
	/*4,4*/ float height;
	/*8*/
};
struct LegoRange2f
{
	/*0,4*/ float min;
	/*4,4*/ float max;
	/*8*/
};
struct LegoRGBf
{
	/*0,4*/ float red;
	/*4,4*/ float green;
	/*8,4*/ float blue;
	/*c*/
};
struct LegoRGBAf
{
	/*00,4*/ float red;
	/*04,4*/ float green;
	/*08,4*/ float blue;
	/*0c,4*/ float alpha;
	/*10*/
};

#pragma endregion


#endif /* LEGORR__COMMON_H */
