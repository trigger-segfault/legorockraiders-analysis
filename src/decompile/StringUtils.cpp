#include "StringUtils.h"


using namespace lego;
using namespace lego::util;


#pragma region Functions

// Split string into parts at the appearance of each delimiter (cannot overlap)
// parts are stored in out_parts, which MUST contain enough room for the number of parts found.
//   (this can cause a buttload of issues with malformed CFG values)
// if the input string is empty, 0 is returned, and out_parts[0] is not assigned.
//
// all 3 arguments are required (except out_parts when input is empty)
// <LegoRR.exe @00477700>
// <CLGen.exe @00401440>
int lego::util::stringSplit(char* input, char** out_parts, const char* delimiter)
{
	size_t delimiterLength = std::strlen(delimiter);

	int numParts = 0; // zero parts if empty string
	if (*input != '\0') {
		// assign first part (minimum of 1 when string is not empty)
		out_parts[numParts++] = input;
		do {
			// check for match with delimiter
			if (std::strncmp(delimiter, input, delimiterLength) == 0) {
				*input = '\0'; // erase start of delimiter, terminate string
				out_parts[numParts++] = input + delimiterLength;
			}
			input++;
		} while (*input != '\0');
	}
	return numParts;
}

// <LegoRR.exe @00477770>
int lego::util::FUN_00477770(char* param_1, byte** param_2)
{
	/// TODO: seems to be some character conversion (for multibyte?)
	///       may be provided by C runtime.
}

// <LegoRR.exe @00477810>
// (ignored, already provided by C runtime)
//char* _strdup(const char* strSource);

// Quite a lot of functions call this even when nothing in that block uses format strings.
// Guess this means we'll need to sanitize basically anything using '%' characters...
// 
// <LegoRR.exe @00477850>
char* lego::util::formatText(const char* text, ...)
{
	char fmtBuffer[256];
	char replBuffer[256];

	std::va_list vl;
	va_start(vl, text);
	std::vsprintf(fmtBuffer, text, vl); // however the hell these VA ARGS are being passed.....
	va_end(vl);

	const char* fmtStr = fmtBuffer;
	char* outStr = replBuffer;
	while (*fmtStr != '\0') {
		char c = *fmtStr;
		if (c == '\\' && fmtStr[1] == 'n') {
			*outStr++ = '\n';
			fmtStr++;
		}
		else if (c == '_') {
			*outStr++ = ' ';
		}
		else {
			*outStr++ = c;
		}
	}
	*outStr = '\0';
	return ::_strdup(replBuffer);
}

// NOTE: There is no CRT function for this, and never has been. So this must be implemented by DDI.
// Returns NULL if no match is found, or a pointer to the first match in str if found.
// If str or strSearch is empty, returns NULL.
// 
// <LegoRR.exe @004778d0>
char* lego::util::strstri(char* str, const char* strSearch)
{
	size_t strLength = std::strlen(str);
	size_t searchLength = std::strlen(strSearch);

	if (searchLength != 0) {
		for (size_t i = 0; i < strLength; i++, str++) {

			if (::_strnicmp(str, strSearch, searchLength) == 0)
				return str;
		}
	}
	return nullptr;
}
// (duplicate for const version of strstri)
const char* lego::util::strstri(const char* str, const char* strSearch)
{
	return (const char*)strstri(const_cast<char*>(str), strSearch);
}

// String hashing used for SFX name lookup table
//
// <LegoRR.exe @00477930>
uint lego::util::hash_string(const char* str, BOOL bIgnoreBlanks, BOOL bIgnoreCase)
{
	/// TODO: <https://github.com/microsoft/Windows-classic-samples/blob/master/Samples/Win7Samples/begin/sdkdiff/utils.cpp>
	///       contains magic number 0x600937 for multiplication.
}

// returns 0 or 1 on success, and 2 on failure
// 
// <LegoRR.exe @004779d0>
BOOL3 lego::util::parseBoolLiteral(const char* str)
{
	if (::_stricmp(str, "YES") == 0 || ::_stricmp(str, "TRUE") == 0 || ::_stricmp(str, "ON") == 0)
		return BOOL3_TRUE /*1*/; // true

	if (::_stricmp(str, "NO") == 0 || ::_stricmp(str, "FALSE") == 0 || ::_stricmp(str, "OFF") == 0)
		return BOOL3_FALSE /*0*/; // false

	return BOOL3_ERROR /*2*/; // error result
}

#pragma endregion

