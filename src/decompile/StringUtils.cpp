// StringUtils.cpp : Defines common string-based helper functions.
//
/// STATUS: [COMPLETE]

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
int __cdecl lego::util::stringSplit(char* input, char** out_parts, const char* delimiter)
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
int __cdecl lego::util::whitespaceSplit(char* input, char** out_parts);
{
	int numParts = 0; // zero parts if empty string
	if (*input != '\0') {
		// assign first part (minimum of 1 when string is not empty)
		out_parts[numParts++] = input;

		do {
			// check for match with whitespace
			if (std::isspace(*input)) {
				*input = '\0'; // erase start of whitespace, terminate string

				do { // consume remaining whitespace, we don't want empty tokens
					input++; // this naturally breaks on null-terminator char
				} while (std::isspace(*input));
				
				// This will also assign null terminator characters if at the end of the file.
				//  However, this doesn't happen since this function is only used in a place where
				//  empty lines are read while stripping newline characters.

				// In this case, an empty line with no whitespace must be the end of the file.
				out_parts[numParts++] = input;
			}
			else {
				input++; // part of existing token
			}
		} while (*input != '\0');
	}
	return numParts;
}

// (ignored, already provided by Microsoft C runtime, but likely not actually part of C runtime)
// <LegoRR.exe @00477810>
//char* _strdup(const char* strSource);

// Quite a lot of functions call this even when nothing in that block uses format strings.
// Guess this means we'll need to sanitize basically anything using '%' characters...
// <LegoRR.exe @00477850>
char* __cdecl lego::util::formatText(const char* text, ...)
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
// <LegoRR.exe @004778d0>
char* __cdecl lego::util::strstri(char* str, const char* strSearch)
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
const char* __cdecl lego::util::strstri(const char* str, const char* strSearch)
{
	return (const char*)lego::util::strstri(const_cast<char*>(str), strSearch);
}

// String hashing used for SFX name lookup table.
// contains the magic number `0x600937` for multiplication.
// see: <https://github.com/microsoft/Windows-classic-samples/blob/master/Samples/Win7Samples/begin/sdkdiff/utils.cpp>
// <LegoRR.exe @00477930>
unsigned int __cdecl lego::util::hash_string(const char* str, BOOL bIgnoreBlanks, BOOL bIgnoreCase)
{
	unsigned int hashValue = 0;
	int hashMultiplier = 0x600937; // multiply this constant by itself after every (counted) character
	int charCount = 1;

	while (*str != '\0') {
		if (bIgnoreBlanks) {
			while (std::isspace(*(unsigned char*)str))
				str++;
		}

		// signedness is important for identical hashing behavior
		int c = *(unsigned char*)str;
		if (bIgnoreCase) {
			c = (unsigned char)std::toupper(c);
		}

		hashValue += (charCount * hashMultiplier) * c;
		hashMultiplier *= 0x600937;
		charCount++;

		str++;
	}
	return hashValue;
}

// Returns 0 or 1 on success, and 2 on failure.
// <LegoRR.exe @004779d0>
BOOL3 __cdecl lego::util::parseBool(const char* str)
{
	if (::_stricmp(str, "YES") == 0 || ::_stricmp(str, "TRUE") == 0 || ::_stricmp(str, "ON") == 0)
		return BOOL3_TRUE /*1*/; // true

	if (::_stricmp(str, "NO") == 0 || ::_stricmp(str, "FALSE") == 0 || ::_stricmp(str, "OFF") == 0)
		return BOOL3_FALSE /*0*/; // false

	return BOOL3_ERROR /*2*/; // error result
}

#pragma endregion

