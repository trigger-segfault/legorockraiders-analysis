
#include "Util.h"

// Does what it says on the tin, returns str.
// 
// <LegoRR.exe @00413e30>
char* __cdecl stringReplaceChar(char* str, char origChar, char newChar)
{
	for (char* s = str; *s != '\0'; s++) {

		if (*s == origChar)
			*s = newChar;
	}
	return str;
}

// Split string into parts at the appearance of each delimiter (cannot overlap)
// parts are stored in out_parts, which MUST contain enough room for the number of parts found.
//   (this can cause a buttload of issues with malformed CFG values)
// if the input string is empty, 0 is returned, and out_parts[0] is not assigned.
//
// all 3 arguments are required (except out_parts when input is empty)
// <LegoRR.exe @00477700>
int __cdecl stringSplit(char* input, char** out_parts, const char* delimiter)
{
	size_t delimiterLength = strlen(delimiter);

	int numParts = 0; // zero parts if empty string
	if (*input != '\0') {
		// assign first part (minimum of 1 when string is not empty)
		out_parts[numParts++] = input;
		do {
			// check for match with delimiter
			if (strncmp(delimiter, input, delimiterLength) == 0) {
				*input = '\0'; // erase start of delimiter, terminate string
				out_parts[numParts++] = input + delimiterLength;
			}
			input++;
		} while (*input != '\0');
	}
	return numParts;
}

// NOTE: There is no CRT function for this, and never has been. So this must be implemented by DDI.
// Returns NULL if no match is found, or a pointer to the first match in str if found.
// If str or strSearch is empty, returns NULL.
// 
// <LegoRR.exe @004778d0>
char* __cdecl strstri(char* str, const char* strSearch)
{
	size_t strLength = strlen(str);
	size_t searchLength = strlen(strSearch);

	if (searchLength != 0) {
		for (size_t i = 0; i < strLength; i++, str++) {

			if (_strnicmp(str, strSearch, searchLength) == 0)
				return str;
		}
	}
	return NULL;
}

// This seems to actually be a logging function that has had its functionality stripped for release builds
// I've noticed functions that push variable number of arguments and then clear those from the stack after this call.
// Whether this function takes a minimum of 1 argument isn't too clear though.
// Examples include logging "WAD Fail" in the File_Open function
// A function that's called in a lot of places that does absolutely nothing.
// Might be some pseudo-polymorphic thing(?)
//
// <LegoRR.exe @00484f50>
void __cdecl logf_removed(const char* message, ...)
{
	return;
}
void __cdecl nocall(void) // what signature is detected as
{
	return;
}

// NOTE: This is not a CRT function, it's again, DDI implementing a
// function that you'd commonly expect to see used.
// Read null-terminated string from file. (DOES NOT CHECK FOR EOF!!)
// always returns true.
// 
// <LegoRR.exe @0048b760>
BOOL __cdecl freadstr(FILE* file, char* out_str)
{
	// this doesn't even check for EOF... BAD BAD BAD!
	// SANITY: check for -1 (EOF)
	char c = (char)fgetc(file);
	while (c != '\0') {
		*out_str++ = c;
		c = (char)fgetc(file);
	}
	*out_str = '\0'; // null-terminate
	return true;
}
