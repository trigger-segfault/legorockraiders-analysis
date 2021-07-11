// Common.h : Declares common utility (and personal helper) functions used by LegoRR / CLGen
//

#pragma once

#include "framework.h"

namespace lego {
	
	// Print to Visual Studio debug output window, for use with windows GUI applications
	int __cdecl debugf(const char* format, ...);

	namespace util {

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
		// <CLGen.exe @00401440>
		int __cdecl stringSplit(char* str, char** parts, const char* delimiter);

	} /* namespace util */

} /* namespace lego */
