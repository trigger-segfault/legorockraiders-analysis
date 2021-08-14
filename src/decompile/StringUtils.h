// StringUtils.h : Declares common string-based helper functions.
//
/// STATUS: [COMPLETE]
/// PURPOSE: Widely-used helper functions used for parsing strings, duplicating strings, and hashing strings.
///
/// NAMESPACE: lego::util
/// INITIALIZE: (none)

#pragma once

#include "Common.h"


#pragma region Enums
namespace lego {

/// PUBLIC:
// Many boolean returns from LegoRR functions may have a 3rd return state for error, this enum is for that.
enum BOOL3 : BOOL /*int*/
{
	BOOL3_FALSE = 0, // false
	BOOL3_TRUE  = 1, // true
	BOOL3_ERROR = 2, // error
};
static_assert(sizeof(BOOL3) == 0x4, "");

} /* namespace lego */
#pragma endregion


#pragma region Functions
namespace lego::util {

/// PUBLIC:
// Split string into parts at the appearance of each delimiter (cannot overlap)
// parts are stored in out_parts, which MUST contain enough room for the number of parts found.
//   (this can cause a buttload of issues with malformed CFG values)
// if the input string is empty, 0 is returned, and out_parts[0] is not assigned.
//
// all 3 arguments are required (except out_parts when input is empty)
// <LegoRR.exe @00477700>
// <CLGen.exe @00401440>
int __cdecl stringSplit(char* input, char** out_parts, const char* delimiter);

// <LegoRR.exe @00477770>
int __cdecl whitespaceSplit(char* input, char** out_parts);

// (ignored, already provided by Microsoft C runtime, but likely not actually part of C runtime)
// <LegoRR.exe @00477810>
//char* _strdup(const char* strSource);

// Quite a lot of functions call this even when nothing in that block uses format strings.
// Guess this means we'll need to sanitize basically anything using '%' characters...
// <LegoRR.exe @00477850>
char* __cdecl formatText(const char* text, ...);

// NOTE: There is no CRT function for this, and never has been. So this must be implemented by DDI.
// Returns NULL if no match is found, or a pointer to the first match in str if found.
// If str or strSearch is empty, returns NULL.
// <LegoRR.exe @004778d0>
char* __cdecl strstri(char* str, const char* strSearch);
// (duplicate for const version of strstri)
const char* __cdecl strstri(const char* str, const char* strSearch);

// String hashing used for SFX name lookup table.
// contains the magic number `0x600937` for multiplication.
// see: <https://github.com/microsoft/Windows-classic-samples/blob/master/Samples/Win7Samples/begin/sdkdiff/utils.cpp>
// <LegoRR.exe @00477930>
unsigned int __cdecl hash_string(const char* str, BOOL bIgnoreBlanks, BOOL bIgnoreCase);

// Returns 0 or 1 on success, and 2 on failure.
// <LegoRR.exe @004779d0>
BOOL3 __cdecl parseBool(const char* str);

} /* namespace lego::util */
#pragma endregion

