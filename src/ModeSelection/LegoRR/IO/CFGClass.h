// (UNUSED) CFGClass.h : Declares LegoRR CFG configuration file functions and types
//

#pragma once

#include "../Common.h"
#include "../Helpers/Pool.h"


namespace lego {
namespace CFG {

class CFGClass
{
private:
	/*00,4*/ char* fileText; // the entire CFG file text (only stored for root property)
public:
	/*04,4*/ const char* key;   // init: NULL
	/*08,4*/ const char* value; // init: NULL
	/*0c,4*/ unsigned int depth;    // init: 0 (if root)
	/*10,4*/ unsigned int field_10; // init: 0 (unknown usage)
	/*14,4*/ const CFGClass* next; // init: NULL
	/*18,4*/ const CFGClass* previous;  // init: NULL (if root)


	#pragma region /// CFG FUNCTIONS ////////////////////////

	// <LegoRR.exe @004790b0>
	//void __cdecl pool::ReservedPool<CFGClass>::Init(void);

	// <LegoRR.exe @004790e0>
	//void __cdecl pool::ReservedPool<CFGClass>::Cleanup(void);

private:
	// Normalize whitespace characters -> '\0'
	// includes handling of ';' comments
	// newlines only require '\n' (no '\r' is needed)
	// this essentially tokenizes the entire text file buffer without allocating more space.
	//
	// NOTE: This function has been isolated from Open
	// <LegoRR.exe -> Open @00479120>
	static void __cdecl ZeroWhiteSpace(char* text, unsigned int length);

public:
	// Open and read all the properties of a CFG file, and return the root property.
	// 
	// <LegoRR.exe @00479120>
	static CFGClass* __cdecl Open(const char* filename);

	// REQUIRED: pass NULL as final argument (except if keyPath2 == NULL)
	// returns a temporary global string that must be used or copied before the next call to this function.
	//
	// I have no idea if this VA Args handling is implemented correctly, let's hope so.
	// 
	// <LegoRR.exe @00479210>
	static const char* __cdecl JoinPath(const char* keyPath1, ...);

	// <LegoRR.exe @004792b0>
	const CFGClass* GetBlockFirstChild(const char* keyPath) const;

	// This WILL CRASH if the passed property is the last property in the list of `depth <= prop->depth`
	// Example:
	// LegoRR {		; Settings for the final version
	//   Main {
	//     MusicOn   TRUE  ; <- prop
	//   }
	// }
	// Pasing CFGClass(LegoRR::Main::MusicOn) will search until another property of same depth or lower depth,
	// but there is none, and it will eventually run into a NULL prop->nextProp
	//
	// YES, this is guarded by the LegoRR { } namespace, since it's doubtful this function is used there.
	// But it's a pretty blatant potential bug, that may affect Object Lists or PTL files.
	//
	// NOTE: This can also return blocks on the same level. (not just key/Value properties)
	// <LegoRR.exe @004792e0>
	const CFGClass* NextFlatProperty() const;

	// <LegoRR.exe @00479310>
	char* CopyPropertyValue(const char* keyPath) const;

	// <LegoRR.exe @00479370>
	const char* GetPropertyValue(const char* keyPath) const;

	// returns 0 or 1 on success, and 2 on failure
	// 
	// <LegoRR.exe @00479390>
	BOOL3 GetPropertyBool(const char* keyPath) const;

	// Gets a floating point value in degrees and transforms it into radians.
	// 
	// <LegoRR.exe @004793d0>
	float GetPropertyRadians(const char* keyPath) const;

	// Converts RGB channels from int [0-255], -> float [0.0f-1.0f]
	// 
	// <LegoRR.exe @00479430>
	BOOL GetPropertyRGBF(const char* keyPath, float* out_r, float* out_g, float* out_b) const;

	// Essentially walk through the tree, and return all unused properties to the pool
	// 
	// <LegoRR.exe @00479500>
	void Close();

private:
	// Contains the following ReservedPool<CFGClass> function:
	// <LegoRR.exe @00479530>
	//CFGClass* __cdecl pool::ReservedPool<CFGClass>::Next(CFGClass* previous);
	// 
	// <LegoRR.exe @00479530>
	static CFGClass* __cdecl CFG__Next(CFGClass* previous);
public:

	// <LegoRR.exe @00479580>
	//void __cdecl pool::ReservedPool<CFGClass>::Release(CFGClass* prop);

	// Match a CFG property or block key name with the specified `keyName`.
	// if the property key is at depth == 0, and has a '*' in it, wildcard comparison will be performed:
	//   for wildcard comparison, anything including and beyond the '*' character is ignored.
	//   This is used for "Lego*" to match with full names like "LegoRR", which can define property overrides.
	//
	// NOTE: This function has been isolated from GetProperty
	// <LegoRR.exe -> GetProperty @004795a0>
	BOOL IsKeyMatch(const char* keyName, BOOL* out_isWildcard) const;

	// prop points to the starting property to search from, it DOES NOT need to be the Lego* root property block
	// 
	// <LegoRR.exe @004795a0>
	const CFGClass* __cdecl GetProperty(const char* keyPath) const;

	// <LegoRR.exe @00479750>
	//void __cdecl pool::ReservedPool<CFGClass>::Alloc(void);





	// Return this unused property to the pool
	// 
	// <LegoRR.exe @00479580>
	//void __cdecl CFG__cleanup_setNextAvail(CFGClass* prop);


	// [globals]
	// <LegoRR.exe @00507498> : g_TABLE
	// <LegoRR.exe @00507518> : g_NEXT
	// <LegoRR.exe @0050751c> : g_COUNT
	// <LegoRR.exe @00507520> : g_ISINIT
	// [functions]
	// <LegoRR.exe @004790b0> : Init()
	// <LegoRR.exe @004790e0> : Cleanup()
	// <LegoRR.exe @00479750> : Alloc()
	// <LegoRR.exe @00479530> : Next()    // contained within CFG structure constructor function
	// <LegoRR.exe @00479580> : Release()
	//static lego::pool::ReservedPool<CFGClass, 32> Pool;

	#pragma endregion

	#pragma region CFG Macro Functions

	// Joining a CFG path while automatically including the NULL final argument.
	#define CFGJoin(key1, ...) lego::CFG::CFGClass::JoinPath((key1), __VA_ARGS__ , NULL)
	// Get a CFG property path's property object, or NULL if not found.
	#define CFGGet(root, key1, ...) (root)->GetProperty(CFGJoin((key1), __VA_ARGS__ ))
	// Get a CFG property path's value, or NULL if not found.
	#define CFGValue(root, key1, ...) (root)->GetPropertyValue(CFGJoin((key1), __VA_ARGS__ ))
	// Malloc a copy of a CFG property path's value, or NULL if not found.
	#define CFGCopy(root, key1, ...) (root)->CopyPropertyValue(CFGJoin((key1), __VA_ARGS__ ))
	// Test if a CFG property path's value exists.
	#define CFGExists(root, key1, ...) (CFGValue((root), (key1), __VA_ARGS__ ) != NULL)
	// Get a CFG property path's value, or empty string "" if not found.
	#define CFGDefault(root, key1, ...) (CFGExists((root), (key1), __VA_ARGS__ ) ? CFGValue((root), (key1), __VA_ARGS__ ) : "")
	// Get the first child of a CFG property path's block, or NULL if not found, or contains not children.
	#define CFGChild(root, key1, ...) (root)->GetBlockFirstChild(CFGJoin((key1), __VA_ARGS__ ))

	// Get an integer value from the CFG property path and default to parsing an empty string (-> 0).
	#define CFGGetInt(root, key1, ...)   std::atoi(CFGDefault((root), (key1), __VA_ARGS__ ))
	// Get an float value from the CFG property path and default to parsing an empty string (-> 0.0f).
	#define CFGGetFloat(root, key1, ...) std::atof(CFGDefault((root), (key1), __VA_ARGS__ ))
	// Get an float value from the CFG property path and default to parsing an empty string (-> 0.0f).
	#define CFGGetRadians(root, key1, ...) (root)->GetPropertyRadians(CFGJoin((key1), __VA_ARGS__ ))
	// Get an RGB floating point value from the CFG property path.
	#define CFGGetRGBF(root, out_r, out_g, out_b, key1, ...) (root)->GetPropertyRGBF(CFGJoin((key1), __VA_ARGS__ ), (out_r), (out_g), (out_b))
	// Get a 3-state boolean value from the CFG property path, where 2 (BOOL3_ERROR) is returned on failure.
	#define CFGGetBool(root, key1, ...) (root)->GetPropertyBool(CFGJoin((key1), __VA_ARGS__ ))
	// Get a boolean value from the CFG property path, where the value defaults to false when not found (ensure value == True).
	#define CFGGetBoolIsTrue(root, key1, ...) (CFGBool((root), (key1), __VA_ARGS__ ) == BOOL3_TRUE)
	// Get a boolean value from the CFG property path, where the value defaults to true when not found (ensure value != False).
	#define CFGGetBoolIsNotFalse(root, key1, ...) (CFGBool((root), (key1), __VA_ARGS__ ) != BOOL3_FALSE)

	#pragma endregion


	///*1c,4*/ ReservedPool<CFGClass>* m_next;
	/*20*/

public:
	// [globals]
	// <LegoRR.exe @00507498> : g_TABLE
	// <LegoRR.exe @00507518> : g_NEXT
	// <LegoRR.exe @0050751c> : g_COUNT
	// <LegoRR.exe @00507520> : g_ISINIT
	// [functions]
	// <LegoRR.exe @004790b0> : Init()
	// <LegoRR.exe @004790e0> : Cleanup()
	// <LegoRR.exe @00479750> : Alloc()
	// <LegoRR.exe @00479530> : Next()    // contained within CFG structure constructor function
	// <LegoRR.exe @00479580> : Release()
	static lego::pool::ReservedPool<CFGClass, 32> Pool;
};


} /* namespace CFG */
} /* namespace lego */
