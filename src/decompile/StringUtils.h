#pragma once


namespace lego {

#pragma region Enums

// Many boolean returns from LegoRR functions may have a 3rd return state for error, this enum is for that.
enum BOOL3 : BOOL
{
	BOOL3_FALSE = 0, // false
	BOOL3_TRUE  = 1, // true
	BOOL3_ERROR = 2, // error
};

#pragma endregion


#pragma region Functions
namespace util {

// Split string into parts at the appearance of each delimiter (cannot overlap)
// parts are stored in out_parts, which MUST contain enough room for the number of parts found.
//   (this can cause a buttload of issues with malformed CFG values)
// if the input string is empty, 0 is returned, and out_parts[0] is not assigned.
//
// all 3 arguments are required (except out_parts when input is empty)
// <LegoRR.exe @00477700>
// <CLGen.exe @00401440>
int stringSplit(char* input, char** out_parts, const char* delimiter);

// <LegoRR.exe @00477770>
int FUN_00477770(char* param_1, byte** param_2);

// <LegoRR.exe @00477810>
// (ignored, already provided by C runtime)
//char* _strdup(const char* strSource);

// Quite a lot of functions call this even when nothing in that block uses format strings.
// Guess this means we'll need to sanitize basically anything using '%' characters...
// 
// <LegoRR.exe @00477850>
char* formatText(const char* text, ...);

// NOTE: There is no CRT function for this, and never has been. So this must be implemented by DDI.
// Returns NULL if no match is found, or a pointer to the first match in str if found.
// If str or strSearch is empty, returns NULL.
// 
// <LegoRR.exe @004778d0>
char* strstri(char* str, const char* strSearch);
// (duplicate for const version of strstri)
const char* strstri(const char* str, const char* strSearch);

// String hashing used for SFX name lookup table
//
// <LegoRR.exe @00477930>
uint hash_string(const char* str, BOOL bIgnoreBlanks, BOOL bIgnoreCase);

// returns 0 or 1 on success, and 2 on failure
// 
// <LegoRR.exe @004779d0>
BOOL3 parseBoolLiteral(const char* str);

} /* namespace util */
#pragma endregion


} /* namespace lego */

