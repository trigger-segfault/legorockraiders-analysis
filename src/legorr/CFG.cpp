
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>  // for extended case-insensitive str API?

#include "Common.h"
#include "CFG.h"
#include "Files.h"
#include "Util.h"


#pragma region /// TYPES ////////////////////////////////

// CFG Property (node) structure
// this type is used for the root, block properties, and key/value properties.
struct CFGProperty
{
	/*00,4*/ char* rootFileText; // the entire CFG file text (only stored for root property)
	/*04,4*/ char* key;   // init: NULL
	/*08,4*/ char* value; // init: NULL
	/*0c,4*/ unsigned int depth;    // init: 0 (if root)
	/*10,4*/ unsigned int field_10; // init: 0 (unknown usage)
	/*14,4*/ CFGProperty* propNext; // init: NULL
	/*18,4*/ CFGProperty* propPrevious;  // init: NULL (if root)

	/*1c,4*/ CFGProperty* nextAvailable; // probably STL linked list thing(?), if so, then it's not an accessible part of the structure.
	/*20*/
};

#pragma endregion


#pragma region /// GLOBALS //////////////////////////////

// global singleton string buffer returned by CFG_joinPath
// <LegoRR.exe @00507098>
static char tmp_CFG_JOINPATH[1024];

// some form of allocation for adding another CFG property, this could just be STL std::list<> garbage
// <LegoRR.exe @00507518>
static CFGProperty* g_CFG_AvailableProperty = NULL;

#pragma endregion


#pragma region /// CFG FUNCTIONS ////////////////////////

// REQUIRED: pass NULL as final argument (except if keyPath2 == NULL)
// returns a temporary global string that must be used or copied before the next call to this function.
//
// I have no idea if this VA Args handling is implemented correctly, let's hope so.
// 
// <LegoRR.exe @00479210>
const char* __cdecl CFG_joinPath(const char* keyPath1, const char* keyPath2, const char* keyPath3, ...)
{
	// NOTE: the handling for keyPath3 as VA ARGS is weird, and will entirely depend on compiler behavior
	const char** nextArgPtr = &keyPath3; // VA ARGS awkwardness...
	const char* currentArg = keyPath2;

	strcpy(tmp_CFG_JOINPATH, keyPath1);
	while (currentArg != NULL) {
		strcat(tmp_CFG_JOINPATH, "::");
		strcat(currentArg);
		currentArg = *nextArgPtr;
		nextArgPtr++;  // next argument in VA ARGS stack
	}
	return tmp_CFG_JOINPATH;
}

// Match a CFG property or block key name with the specified `keyName`.
// if the property key is at depth == 0, and has a '*' in it, wildcard comparison will be performed:
//   for wildcard comparison, anything including and beyond the '*' character is ignored.
//   This is used for "Lego*" to match with full names like "LegoRR", which can define property overrides.
//
// NOTE: This function has been isolated from CFG_getProperty
// <LegoRR.exe -> CFG_getProperty>
bool __cdecl CFG_isKeyMatch(const CFGProperty* prop, const char* keyName, bool* out_isWildcard)
{
	*out_isWildcard = false;
	if (prop->depth == 0) {
		// exclude checking beyond '*', so i.e. keyName argument of "LegoRR" will successfully match against property key "Lego*"
		// this condition is only evaluated if prop->key contains '*'
		const char* chr = strchr(prop->key, '*');
		if (chr != NULL) {
			size_t length = chr - prop->key; // (index of '*')
			*out_isWildcard = _strnicmp(keyName, prop->key, length) == 0;
		}
	}
	return *out_isWildcard || _stricmp(keyName, prop->key) == 0;
}

// prop points to the starting property to search from, it DOES NOT need to be the Lego* root property block
// 
// <LegoRR.exe @004795a0>
CFGProperty* __cdecl CFG_getProperty(CFGProperty* prop, const char* keyPath)
{
	// split keyPath into parts by "::"
	// create copy of keyPath, because stringSplit modifies the input string
	char* inputPath = (char*)malloc(strlen(keyPath) + 1);
	char* parts[100];
	int numParts = stringSplit(inputPath, parts, "::");

	CFGProperty* result = NULL;

	while (prop != NULL) {
		bool isWildcard = false;
		unsigned int depth = numParts - 1;
		// check for top-level key match
		if (prop->depth != depth || !CFG_isKeyMatch(prop, parts[depth], &isWildcard)) {
			prop = prop->propNext;
			continue;
		}

		// key matched, now try to match all parent keys up to root, by walking up the tree
		CFGProperty* previous = prop->propPrevious;

		// SANITY: Add `&& depth > 0` to check
		// (from the looks of it, CFG files can potentially have unbalanced block indents that go below 0)
		while (previous != NULL) {
			if (previous->depth == depth - 1) { // is this property the starting block of previous?
				if (!CFG_isKeyMatch(previous, parts[depth - 1], &isWildcard))
					break;  // no match, stop checking this path
				depth--;
			}
			previous = previous->propPrevious;
		}

		if (depth == 0) { // have we matched all keys up to (and including) root?
			result = prop;
			// if exact match result is found, exit the loop
			//  otherwise keep searching in-case an exact match exists, which would overwrite the wildcard match
			//  e.g. "LegoRR" has precedence over "Lego*" (but only if a property is defined in "LegoRR")
			if (!isWildcard)
				break;
		}
		prop = prop->propNext;
	}

	free(inputPath); // free allocated string for parts comparison
	return result;
}

// <LegoRR.exe @004792b0>
CFGProperty* __cdecl CFG_getBlockFirstChild(CFGProperty* prop, const char* keyPath)
{
	prop = CFG_getProperty(prop, keyPath);
	// Nevermind, this is a function to get children...
	//   ~~A property is only designated a block if it contains children (the next property in the linked list is block->depth + 1)~~
	// Another instance of a check to propNext without null-checks... *sigh*
	if (prop != NULL && prop->depth < prop->propNext->depth)
		return prop->propNext;

	return NULL;
}

// <LegoRR.exe @00479370>
char* __cdecl CFG_getPropertyValue(CFGProperty* prop, const char* keyPath)
{
	prop = CFG_getProperty(prop, keyPath);
	if (prop != NULL)
		return prop->value;

	return NULL;
}

// <LegoRR.exe @00479310>
char* __cdecl CFG_copyPropertyValue(CFGProperty* prop, const char* keyPath)
{
	prop = CFG_getProperty(prop, keyPath);
	if (prop == NULL || prop->value == NULL)
		return NULL;

	char* value = malloc(strlen(prop->value) + 1);
	return strcpy(value, prop->value);
}

// This WILL CRASH if the passed property is the last property in the list of `depth <= prop->depth`
// Example:
// LegoRR {		; Settings for the final version
//   Main {
//     MusicOn   TRUE  ; <- prop
//   }
// }
// Pasing CFGProperty(LegoRR::Main::MusicOn) will search until another property of same depth or lower depth,
// but there is none, and it will eventually run into a NULL prop->nextProp
//
// YES, this is guarded by the LegoRR { } namespace, since it's doubtful this function is used there.
// But it's a pretty blatant potential bug, that may affect Object Lists or PTL files.
//
// NOTE: This can also return blocks on the same level. (not just key/Value properties)
// <LegoRR.exe @004792e0>
CFGProperty* __cdecl CFG_nextFlatProperty(const CFGProperty* prop)
{
	unsigned int currentDepth = prop->depth;
	// only break on property of lower depth, as that means we've exited the block
	while (prop != NULL && prop->depth >= currentDepth) {
		
		// SANITY: Add null checks before accessing prop->depth
		prop = prop->propNext;
		if (prop->depth == currentDepth)
			return prop; // next same-depth property found in current block
	}
	return NULL;
}

// Converts RGB channels from int [0-255], -> float [0.0f-1.0f]
// 
// <LegoRR.exe @00479430>
bool __cdecl CFG_parsePropertyRGB(CFGProperty* prop, const char* keyPath, float* out_r, float* out_g, float* out_b)
{
	char* value = CFG_copyPropertyValue(root, keyPath);
	if (value != NULL) {
		// this may cause all kinds of unexpected behavior if the property value has more than 2 ':'s
		char* parts[3];
		int numParts = stringSplit(value, parts, ":");
		if (numParts == 3) {
			*out_r = (float)atoi(parts[0]) * 0.00392157f; // 1.0f / 255.0f
			*out_g = (float)atoi(parts[1]) * 0.00392157f;
			*out_b = (float)atoi(parts[2]) * 0.00392157f;
		}
		free(value);
		return (numParts == 3);
	}
	return false;
}

// returns 0 or 1 on success, and 2 on failure
// 
// <LegoRR.exe @004779d0>
BOOL3 __cdecl CFG_parseBoolLiteral(const char* text)
{
	if (_stricmp(text, "YES") == 0)
		return BOOL3_TRUE /*1*/; // true
	
	if (_stricmp(text, "TRUE") == 0)
		return BOOL3_TRUE /*1*/; // true
	
	if (_stricmp(text, "ON") == 0)
		return BOOL3_TRUE /*1*/; // true
	
	if (_stricmp(text, "NO") == 0)
		return BOOL3_FALSE /*0*/; // false
	
	if (_stricmp(text, "FALSE") == 0)
		return BOOL3_FALSE /*0*/; // false
	
	if (_stricmp(text, "OFF") == 0)
		return BOOL3_FALSE /*0*/; // false
	
	return BOOL3_ERROR /*2*/; // error result
	
	// original ending of function. It's cryptic, but it'll return 2 for any iVar1 != 0, otherwise 0
	//int iVar1 = _stricmp(text,s_OFF_004a5120);
	//return -(unsigned int)(iVar1 != 0) & 2;
}

// returns 0 or 1 on success, and 2 on failure
// 
// <LegoRR.exe @00479390>
BOOL3 __cdecl CFG_getPropertyBool(CFGProperty* prop, const char* keyPath)
{
	BOOL3 result = BOOL3_ERROR /*2*/; // error result
	// usage of CFG_copyPropertyValue over CFG_getPropertyValue here seems pointless, since the value is never modified
	char* value = CFG_copyPropertyValue(prop, keyPath);
	if (value != NULL) {
		result = CFG_parseBoolLiteral(value);
		free(value);
	}
	return result;
}

// Quite a lot of functions call this even when nothing in that block uses format strings.
// Guess this means we'll need to sanitize basically anything using '%' characters...
// 
// <LegoRR.exe @00477850>
char* __cdecl CFG_formatText(const char* text, ...)
{
	char fmtBuffer [256];
	char replBuffer [256];

	sprintf(fmtBuffer, text, ...); // however the hell these VA ARGS are being passed.....

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
	return _strdup(outStr, replBuffer);
}

// <LegoRR.exe @00479530>
CFGProperty* __cdecl CFG_allocNextProperty(CFGProperty* previous)
{
	if (g_CFG_AvailableProperty == NULL) {
		// no next property is allocated, make more (assigns g_CFG_AvailableProperty)
		// this is possible some STL std::list<> jank (and the std::list<> is a global variable)
		CFG__allocNewProperties();
	}
	CFGProperty* prop = g_CFG_AvailableProperty;

	CFGProperty* nextAvailable = g_CFG_AvailableProperty->nextAvailable;
	// break link to nextAvailable for our new property
	prop->nextAvailable = prop;
	// assign g_CFG_AvailableProperty to newly prepared nextAvailable
	//  (which may potentially be NULL, in which case, the top of this function is triggered on next call)
	g_CFG_AvailableProperty = nextAvailable;

	prop->key = NULL;
	prop->value = NULL;
	prop->propNext = NULL;
	if (previous != NULL) {
		previous->propNext = prop;
		prop->propPrevious = previous;
		prop->depth = previous->depth;
		prop->rootFileText = NULL; // field not used by non-root properties.
	}
	else {
		prop->propPrevious = NULL;
		prop->depth = 0;
	}
	return prop;
}

// Normalize whitespace characters -> '\0'
// includes handling of ';' comments
// newlines only require '\n' (no '\r' is needed)
// this essentially tokenizes the entire text file buffer without allocating more space.
//
// NOTE: This function has been isolated from CFG_readFile
// <LegoRR.exe -> CFG_readFile>
void __cdecl CFG_zeroWhiteSpace(char* text, unsigned int length)
{
	bool isComment = false;
	for (unsigned int i = 0; i < length; i++, text++) {
		char c = *text;
		if (c == ';')
			isComment = true; // whitespace until EOL
		else if (c == '\n')    // (surprisingly no requirement for "\r\n")
			isComment = false; // end any existing comment
		
		if (isComment || c == '\t' || c == '\n' || c == '\r' || c == ' ') {
			*text = '\0'; // normalize whitespace char
		}
	}
}

// Open and read all the properties of a CFG file, and return the root property.
// 
// <LegoRR.exe @00479120>
CFGProperty* __cdecl CFG_readFile(const char *filename)
{
	// read entire cfg file, it looks like...
	unsigned int length;
	char* text = (char*)File_ReadAllBytes(filename, &length);
	if (text == NULL)
		return NULL;  // failed to read file, return null

	CFGProperty* root = CFG_allocNextProperty(NULL); // NULL, root property
	root->rootFileText = text;
	if (length == 0)
		return root;  // empty file, still return valid CFG root node

	// normalize whitespace characters -> '\0'
	// and handle ';' comments
	CFG_zeroWhiteSpace(text, length);

	CFGProperty* prop = root;
	// read properties until EOF (length)
	for (unsigned int i = 0; i < length; i++, text++) {
		char c = *text;
		if (c == '\0')
			continue; // "whitespace"... continue

		// if (strcmp(text, "}") == 0) {
		if (c == '}' && text[1] == '\0') { // match EXACTLY "}" (whitespace separated)
			// end of block  (no checks for imbalanced braces with depth < 0)
			prop->depth--;
		}
		else if (prop->key == NULL) {
			// first non-whitespace, assign property key from here
			prop->key = text;
		}
		else {
			// second non-whitespace, assign property value -OR- block indent char "{"
			prop->value = text; // assigned even if value is "{" for block open

			// create next property node
			prop = CFG_allocNextProperty(prop);

			if (c == '{' && text[1] == '\0') { // match EXACTLY "{" (whitespace separated)
				// start of block
				prop->depth++;
			}
		}

		// skip remaining non-whitespace
		// LOGIC: first iteration is always true text[0] != '\0'
		while (i < length && *text != '\0') {
			i++; text++;
		}
	}
	return root;
}

// Return this unused property to the pool
// 
// <LegoRR.exe @00479580>
void __cdecl CFG__cleanup_setNextAvail(CFGProperty* prop)
{
	prop->nextAvailable = g_CFG_AvailableProperty;
	g_CFG_AvailableProperty = prop;
}

// Essentially walk through the tree, and return all unused properties to the pool
// 
// <LegoRR.exe @00479500>
void __cdecl CFG__cleanup(CFGProperty* root)
{
	free(root->rootFileText); // free the buffer containing the entire CFG file text

	CFGProperty *prop = root;
	while (prop != NULL) {
		CFG__cleanup_setNextAvail(prop);
		prop = prop->propNext;
	}
}

#pragma endregion
