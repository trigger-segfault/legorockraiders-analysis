
#ifndef LEGORR__CFG_H
#define LEGORR__CFG_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>  // for extended case-insensitive str API?

#include "Common.h"


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
const char* __cdecl CFG_joinPath(const char* keyPath1, const char* keyPath2, const char* keyPath3, ...);

// Match a CFG property or block key name with the specified `keyName`.
// if the property key is at depth == 0, and has a '*' in it, wildcard comparison will be performed:
//   for wildcard comparison, anything including and beyond the '*' character is ignored.
//   This is used for "Lego*" to match with full names like "LegoRR", which can define property overrides.
//
// NOTE: This function has been isolated from CFG_getProperty
// <LegoRR.exe -> CFG_getProperty>
bool __cdecl CFG_isKeyMatch(const CFGProperty* prop, const char* keyName, bool* out_isWildcard);

// prop points to the starting property to search from, it DOES NOT need to be the Lego* root property block
// 
// <LegoRR.exe @004795a0>
CFGProperty* __cdecl CFG_getProperty(CFGProperty* prop, const char* keyPath);

// <LegoRR.exe @004792b0>
CFGProperty* __cdecl CFG_getBlockFirstChild(CFGProperty* prop, const char* keyPath);

// <LegoRR.exe @00479370>
char* __cdecl CFG_getPropertyValue(CFGProperty* prop, const char* keyPath);

// <LegoRR.exe @00479310>
char* __cdecl CFG_copyPropertyValue(CFGProperty* prop, const char* keyPath);

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
CFGProperty* __cdecl CFG_nextFlatProperty(const CFGProperty* prop);

// Converts RGB channels from int [0-255], -> float [0.0f-1.0f]
// 
// <LegoRR.exe @00479430>
bool __cdecl CFG_parsePropertyRGB(CFGProperty* prop, const char* keyPath, float* out_r, float* out_g, float* out_b);

// returns 0 or 1 on success, and 2 on failure
// 
// <LegoRR.exe @004779d0>
BOOL3 __cdecl CFG_parseBoolLiteral(const char* text);

// returns 0 or 1 on success, and 2 on failure
// 
// <LegoRR.exe @00479390>
BOOL3 __cdecl CFG_getPropertyBool(CFGProperty* prop, const char* keyPath);

// Quite a lot of functions call this even when nothing in that block uses format strings.
// Guess this means we'll need to sanitize basically anything using '%' characters...
// 
// <LegoRR.exe @00477850>
char* __cdecl CFG_formatText(const char* text, ...);

// <LegoRR.exe @00479530>
CFGProperty* __cdecl CFG_allocNextProperty(CFGProperty* previous);

// Normalize whitespace characters -> '\0'
// includes handling of ';' comments
// newlines only require '\n' (no '\r' is needed)
// this essentially tokenizes the entire text file buffer without allocating more space.
//
// NOTE: This function has been isolated from CFG_readFile
// <LegoRR.exe -> CFG_readFile>
void __cdecl CFG_zeroWhiteSpace(char* text, unsigned int length);

// Open and read all the properties of a CFG file, and return the root property.
// 
// <LegoRR.exe @00479120>
CFGProperty* __cdecl CFG_readFile(const char *filename);

// Return this unused property to the pool
// 
// <LegoRR.exe @00479580>
void __cdecl CFG__cleanup_setNextAvail(CFGProperty* prop);

// Essentially walk through the tree, and return all unused properties to the pool
// 
// <LegoRR.exe @00479500>
void __cdecl CFG__cleanup(CFGProperty* root);

#pragma endregion


#endif /* LEGORR__CFG_H */
