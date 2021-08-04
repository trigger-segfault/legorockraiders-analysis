#pragma once
#ifndef LEGORR__UTIL_H
#define LEGORR__UTIL_H

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>  // for BOOL typedef?



// Does what it says on the tin, returns str.
// 
// <LegoRR.exe @00413e30>
char* __cdecl stringReplaceChar(char* str, char origChar, char newChar);

// Split string into parts at the appearance of each delimiter (cannot overlap)
// parts are stored in out_parts, which MUST contain enough room for the number of parts found.
//   (this can cause a buttload of issues with malformed CFG values)
// if the input string is empty, 0 is returned, and out_parts[0] is not assigned.
// 
// Returns the number of matches/
// Changes str by zeroing all found delimiters (case sensitive).
// Found parts are output to parts, which points to an array of strings,
// WHICH MUST be able to hold all found matches. This function is a huge point of failure.
//
// <LegoRR.exe @00477700>
int __cdecl stringSplit(char* str, char** parts, const char* delimiter);

// NOTE: There is no CRT function for this, and never has been. So this must be implemented by DDI.
// Returns NULL if no match is found, or a pointer to the first match in str if found.
// If str or strSearch is empty, returns NULL.
// 
// <LegoRR.exe @004778d0>
char* __cdecl strstri(char* str, const char* strSearch);

// This seems to actually be a logging function that has had its functionality stripped for release builds
// I've noticed functions that push variable number of arguments and then clear those from the stack after this call.
// Whether this function takes a minimum of 1 argument isn't too clear though.
// Examples include logging "WAD Fail" in the File_Open function
// A function that's called in a lot of places that does absolutely nothing.
// Might be some pseudo-polymorphic thing(?)
//
// <LegoRR.exe @00484f50>
void __cdecl logf_removed(const char* message, ...);
void __cdecl nocall(void); // what signature is detected as

// NOTE: This is not a CRT function, it's again, DDI implementing a
// function that you'd commonly expect to see used.
// Read null-terminated string from file. (DOES NOT CHECK FOR EOF!!)
// always returns true.
// 
// <LegoRR.exe @0048b760>
BOOL __cdecl freadstr(FILE* file, char* out_str);


#endif /* LEGORR__UTIL_H */
