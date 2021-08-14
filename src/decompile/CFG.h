// CFG.h : Declares CFG configuration file functions and types.
//
/// STATUS: [COMPLETE]
/// PURPOSE: Provides access to reading a hierarchical property-type configuration
///          file format. Used by multiple file extensions in the game. [.cfg, .ol, .ptl, .ae]
///
/// NAMESPACE: lego::cfg
/// INITIALIZE: Call `ReservedPool_CFGProperty___Init()` once on startup.
///             Call `ReservedPool_CFGProperty___Cleanup()` once on cleanup.
/// GLOBALS: private | temporary return buffer that must be used immediately
/// FILEIO: Uses `file::File_ReadAllBytes(const char*,unsigned int*)`

#pragma once

#include "Common.h"
#include "Pool.h"


#pragma region CFG Macros functions

// Joining a CFG path while automatically including the NULL final argument.
#define CFGJoin(key1, ...) lego::cfg::CFG_JoinPath(key1, __VA_ARGS__ , nullptr)

// Get a CFG property path's property object, or NULL if not found.
#define CFGGet_NoJoin(prop, keyPath) lego::cfg::CFG_GetProperty(prop, keyPath)
// Get a CFG property path's value, or NULL if not found.
#define CFGString_NoJoin(prop, keyPath) lego::cfg::CFG_ReadString(prop, keyPath)
// Malloc a copy of a CFG property path's value, or NULL if not found.
#define CFGCopy_NoJoin(prop, keyPath) lego::cfg::CFG_CopyString(prop, keyPath)
// Test if a CFG property path's value exists.
#define CFGExists_NoJoin(prop, keyPath) (CFGString_NoJoin(prop, keyPath) != nullptr)
// Get a CFG property path's value, or empty string "" if not found.
#define CFGDefault_NoJoin(prop, keyPath) (CFGString_NoJoin(prop, keyPath) ? CFGString_NoJoin(prop, keyPath) : "")
// Get the first child of a CFG property path's block, or NULL if not found, or contains not children.
#define CFGChild_NoJoin(prop, keyPath) lego::cfg::CFG_GetChildren(prop, keyPath)

// Get an integer value from the CFG property path and default to parsing an empty string (-> 0).
#define CFGInt_NoJoin(prop, keyPath)   std::atoi(CFGDefault_NoJoin(prop, keyPath))
// Get an float value from the CFG property path and default to parsing an empty string (-> 0.0f).
#define CFGFloat_NoJoin(prop, keyPath) std::atof(CFGDefault_NoJoin(prop, keyPath))
// Get an float value from the CFG property path and default to parsing an empty string (-> 0.0f).
#define CFGRadians_NoJoin(prop, keyPath) lego::cfg::CFG_ReadRadians(prop, keyPath)
// Get an RGB floating point value from the CFG property path.
#define CFGRGBF_NoJoin(prop, out_r, out_g, out_b, keyPath) lego::cfg::CFG_ReadRGBF(prop, keyPath, out_r, out_g, out_b)
// Get a 3-state boolean value from the CFG property path, where 2 (BOOL3_ERROR) is returned on failure.
#define CFGBool_NoJoin(prop, keyPath) lego::cfg::CFG_ReadBool(prop, keyPath)


// Get a CFG property path's property object, or NULL if not found.
#define CFGGet(prop, key1, ...) lego::cfg::CFG_GetProperty(prop, CFGJoin(key1, __VA_ARGS__ ))
// Get a CFG property path's value, or NULL if not found.
#define CFGString(prop, key1, ...) lego::cfg::CFG_ReadString(prop, CFGJoin(key1, __VA_ARGS__ ))
// Malloc a copy of a CFG property path's value, or NULL if not found.
#define CFGCopy(prop, key1, ...) lego::cfg::CFG_CopyString(prop, CFGJoin(key1, __VA_ARGS__ ))
// Test if a CFG property path's value exists.
#define CFGExists(prop, key1, ...) (CFGString(prop, key1, __VA_ARGS__ ) != nullptr)
// Get a CFG property path's value, or empty string "" if not found.
#define CFGDefault(prop, key1, ...) (CFGString(prop, key1, __VA_ARGS__ ) ? CFGString(prop, key1, __VA_ARGS__ ) : "")
// Get the first child of a CFG property path's block, or NULL if not found, or contains not children.
#define CFGChild(prop, key1, ...) lego::cfg::CFG_GetChildren(prop, CFGJoin(key1, __VA_ARGS__ ))

// Get an integer value from the CFG property path and default to parsing an empty string (-> 0).
#define CFGInt(prop, key1, ...)   std::atoi(CFGDefault(prop, key1, __VA_ARGS__ ))
// Get an float value from the CFG property path and default to parsing an empty string (-> 0.0f).
#define CFGFloat(prop, key1, ...) std::atof(CFGDefault(prop, key1, __VA_ARGS__ ))
// Get an float value from the CFG property path and default to parsing an empty string (-> 0.0f).
#define CFGRadians(prop, key1, ...) lego::cfg::CFG_ReadRadians(prop, CFGJoin(key1, __VA_ARGS__ ))
// Get an RGB floating point value from the CFG property path.
#define CFGRGBF(prop, out_r, out_g, out_b, key1, ...) lego::cfg::CFG_ReadRGBF(prop, CFGJoin(key1, __VA_ARGS__ ), out_r, out_g, out_b)
// Get a 3-state boolean value from the CFG property path, where 2 (BOOL3_ERROR) is returned on failure.
#define CFGBool(prop, key1, ...) lego::cfg::CFG_ReadBool(prop, CFGJoin(key1, __VA_ARGS__ ))

#pragma endregion


#pragma pack(push, 1)

#pragma region Types
namespace lego {

/// PUBLIC:
struct CFGNode
{
	/// PRIVATE:
	/*00,4*/ char* fileText; // the entire CFG file text (only stored for root property)
	/// PUBLIC:
	/*04,4*/ const char* key;   // init: NULL
	/*08,4*/ const char* value; // init: NULL
	/// PRIVATE:
	/*0c,4*/ unsigned int depth;    // init: 0 (if root)
	/*10,4*/ unsigned int field_10; // init: 0 (unknown usage)
	/*14,4*/ CFGNode* next; // init: NULL
	/*18,4*/ CFGNode* previous;  // init: NULL (if root)
	// /*1c,4*/ ReservedPool<CFGProperty>* pool_m_next;
	/*20*/
};
static_assert(sizeof(CFGNode) == 0x1c, "");
static_assert(sizeof(pool::PoolItem<CFGNode>) == 0x20, "");

// Root CFG file node.
typedef CFGNode CFGRoot;
// Any node in a CFG tree, constant and non-modifiable.
typedef const CFGNode CFGProperty;

} /* namespace lego */
#pragma endregion


#pragma region Globals
namespace lego::cfg {

/// PRIVATE:
// <LegoRR.exe @00507098 - 00507524>
struct CFGManager
{
	// Global singleton string buffer returned by CFG_JoinPath.
	// <LegoRR.exe @00507098>
	/*000,400*/ char tmp_CFG_JOINPATH[1024];
	// <LegoRR.exe @00507498>
	/*400,80*/  pool::PoolItem<CFGNode>* pool_TABLE[32];
	// <LegoRR.exe @00507518>
	/*480,4*/   pool::PoolItem<CFGNode>* pool_NEXT;
	// <LegoRR.exe @0050751c>
	/*484,4*/   unsigned int pool_COUNT;
	// <LegoRR.exe @00507520>
	/*488,4*/   BOOL pool_ISINIT;
	/*48c*/
};
static_assert(sizeof(CFGManager) == 0x48c, "");

} /* namespace lego::cfg */
namespace lego::globals {

// /// PRIVATE:
// // Global singleton string buffer returned by CFG_JoinPath.
// // <LegoRR.exe @00507098>
// extern char tmp_CFG_JOINPATH[1024];
// // <LegoRR.exe @00507498>
// extern pool::PoolItem<CFGNode>* ReservedPool_CFGProperty___g_TABLE[32];
// // <LegoRR.exe @00507518>
// extern pool::PoolItem<CFGNode>* ReservedPool_CFGProperty___g_NEXT;
// // <LegoRR.exe @0050751c>
// extern unsigned int ReservedPool_CFGProperty___g_COUNT;
// // <LegoRR.exe @00507520>
// extern BOOL ReservedPool_CFGProperty___g_ISINIT;

/// PRIVATE:
// <LegoRR.exe @00507098 - 00507524>
extern lego::cfg::CFGManager g_CFG;

} /* namespace lego::globals */
#pragma endregion

#pragma pack(pop)


#pragma region Functions
namespace lego::cfg {

/// PUBLIC:
// <LegoRR.exe @004790b0>
//void __cdecl InitCFGManager(void);
void __cdecl ReservedPool_CFGProperty___Init(void);
// <LegoRR.exe @004790e0>
//void __cdecl CleanupCFGManager(void);
void __cdecl ReservedPool_CFGProperty___Cleanup(void);
// Opens and reads an entire CFG file (using FileSystem I/O).
// <LegoRR.exe @00479120>
CFGRoot* __cdecl CFG_Open(const char* filename);
// Joins names together to form a CFG path, that can be used to look up nested properties.
// REQUIRED: pass NULL as final argument after `keyPath1`.
// NOTE: returns a temporary global string buffer that MUST be used or copied immediately
//  before the next call to this function.
// <LegoRR.exe @00479210>
const char* __cdecl CFG_JoinPath(const char* keyPath1, ...);
// Gets the first child CFG property of a block.
// Returns null if the block is not found, or it has no children.
// <LegoRR.exe @004792b0>
CFGProperty* __cdecl CFG_GetChildren(CFGProperty* prop, const char* keyPath);
// Gets the next child property in the same block-level block, relative to `prop`.
// Unlike other CFG-based lookup, having multiple blocks WILL NOT work here.
// <LegoRR.exe @004792e0>
CFGProperty* __cdecl CFG_NextFlat(CFGProperty* prop);
// Reads and returns a copy of a string value. If non-null, the
//  caller must use `std::free(void*)` to destroy the returned string.
// <LegoRR.exe @00479310>
char* __cdecl CFG_CopyString(CFGProperty* prop, const char* keyPath);
// Reads a string value.
// <LegoRR.exe @00479370>
const char* __cdecl CFG_ReadString(CFGProperty* prop, const char* keyPath);
// Reads a bool literal, parsed using StringUtils.h (`lego::util::parsePool(const char*)`).
// Returns BOOL3_ERROR (0x2) on failure, either due to the property not existing,
//  or not being a valid literal name.
// <LegoRR.exe @00479390>
BOOL3 __cdecl CFG_ReadBool(CFGProperty* prop, const char* keyPath);
// Reads a floating point value in degrees and returns the value converted to radians.
// <LegoRR.exe @004793d0>
float __cdecl CFG_ReadRadians(CFGProperty* prop, const char* keyPath);
// Reads an rgb value formatted as "R:G:B", using channels in the range [0-255].
// Stores the results in `out_*` arguments as floats in the range [0.0f-1.0f].
// <LegoRR.exe @00479430>
BOOL __cdecl CFG_ReadRGBF(CFGProperty* prop, const char* keyPath, float* out_r, float* out_g, float* out_b);
// Closes an opened CFG file.
// Must pass the same `CFGRoot*` node returned by `CFG_Open(const char*)`.
// <LegoRR.exe @00479500>
void __cdecl CFG_Close(CFGRoot* root);

/// PRIVATE:
// <LegoRR.exe @00479530>
// void CFG__PoolNext(void);
CFGNode* __cdecl ReservedPool_CFGProperty___Next(CFGNode* previous);
// <LegoRR.exe @00479580>
// void CFG__PoolRelease(void);
void __cdecl ReservedPool_CFGProperty___Release(CFGNode* prop);

/// PUBLIC:
// Lookup and return CFG property.
// <LegoRR.exe @004795a0>
CFGProperty* __cdecl CFG_GetProperty(CFGProperty* prop, const char* keyPath);

/// PRIVATE:
// <LegoRR.exe @00479750>
void __cdecl ReservedPool_CFGProperty___Alloc(void);

} /* namespace lego::cfg */
#pragma endregion

