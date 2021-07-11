// Common.cpp : Defines common utility (and personal helper) functions used by LegoRR / CLGen
//

#include "framework.h"
#include "Common.h"
#include <cstdarg>


using namespace lego;
using namespace lego::util;


int __cdecl lego::debugf(const char* format, ...) {
	char buffer[2048];
	va_list vl;
	va_start(vl, format);
	int result = vsprintf(buffer, format, vl);
	va_end(vl);
	OutputDebugStringA(buffer);
	//OutputDebugStringA("\n");
	return result;
}


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
