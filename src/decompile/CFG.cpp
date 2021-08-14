// CFG.cpp : Defines CFG configuration file functions and types.
//
/// STATUS: [COMPLETE]

#include "CFG.h"
#include "File.h"
#include "StringUtils.h"


using namespace lego;
using namespace lego::cfg;


#pragma region Globals

// /// PRIVATE:
// // Global singleton string buffer returned by CFG_JoinPath.
// // <LegoRR.exe @00507098>
// char tmp_CFG_JOINPATH[1024];
// // <LegoRR.exe @00507498>
// pool::PoolItem<CFGNode>* ReservedPool_CFGProperty___g_TABLE[32];
// // <LegoRR.exe @00507518>
// pool::PoolItem<CFGNode>* ReservedPool_CFGProperty___g_NEXT;
// // <LegoRR.exe @0050751c>
// unsigned int ReservedPool_CFGProperty___g_COUNT;
// // <LegoRR.exe @00507520>
// BOOL ReservedPool_CFGProperty___g_ISINIT;

// <LegoRR.exe @00507098 - 00507524>
CFGManager lego::globals::g_CFG;

#pragma endregion


#pragma region Custom Functions
namespace lego::cfg {

/// CUSTOM: Helper function for use within CFG_GetProperty
// Match a CFG property or block key name with the specified `keyName`.
// if the property key is at depth == 0, and has a '*' in it, wildcard comparison will be performed:
//   for wildcard comparison, anything including and beyond the '*' character is ignored.
//   This is used for "Lego*" to match with full names like "LegoRR", which can define property overrides.
//
// NOTE: This function has been isolated from CFG_GetProperty
// <LegoRR.exe -> CFG_GetProperty @004795a0>
static BOOL __cdecl CFG_IsKeyMatch(lego::cfg::CFGProperty* prop, const char* keyName, BOOL* out_isWildcard)
{
	*out_isWildcard = false;
	if (prop->depth == 0) {
		// exclude checking beyond '*', so i.e. keyName argument of "LegoRR" will successfully match against property key "Lego*"
		// this condition is only evaluated if prop->key contains '*'
		const char* chr = std::strchr(prop->key, '*');
		if (chr != nullptr) {
			size_t length = chr - prop->key; // (PTR MATH: index of '*')
			*out_isWildcard = ::_strnicmp(keyName, prop->key, length) == 0;
		}
	}
	return *out_isWildcard || ::_stricmp(keyName, prop->key) == 0;
}

/// CUSTOM: Helper function for use within CFG_Open
// Normalize whitespace characters -> '\0'
// includes handling of ';' comments
// newlines only require '\n' (no '\r' is needed)
// this essentially tokenizes the entire text file buffer without allocating more space.
//
// NOTE: This function has been isolated from Open
// <LegoRR.exe -> CFG_Open @00479120>
static void __cdecl CFG_ZeroWhiteSpace(char* text, unsigned int length)
{
	BOOL isComment = false;
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

} /* namespace lego::cfg */
#pragma endregion


#pragma region Functions

// <LegoRR.exe @004790b0>
// void __cdecl lego::cfg::InitCFGManager(void)
// {
// 	std::memset(globals::g_CFG.pool_TABLE, 0, sizeof(globals::g_CFG.pool_TABLE) /*0x80*/);
// 	globals::g_CFG.pool_NEXT = nullptr;
// 	globals::g_CFG.pool_COUNT = 0;
// 	globals::g_CFG.pool_ISINIT = true;
// }
void __cdecl lego::cfg::ReservedPool_CFGProperty___Init(void)
{
	std::memset(globals::g_CFG.pool_TABLE, 0, sizeof(globals::g_CFG.pool_TABLE) /*0x80*/);
	globals::g_CFG.pool_NEXT = nullptr;
	globals::g_CFG.pool_COUNT = 0;
	globals::g_CFG.pool_ISINIT = true;
}

// <LegoRR.exe @004790e0>
// void __cdecl lego::cfg::CleanupCFGManager(void)
// {
// 	for (int i = 0; i < _countof(globals::g_CFG.pool_TABLE); i++) {
// 		if (globals::g_CFG.pool_TABLE[i] != nullptr)
// 			std::free(globals::g_CFG.pool_TABLE[i]);
// 	}
// 	globals::g_CFG.pool_NEXT = nullptr;
// 	globals::g_CFG.pool_ISINIT = false;
// }
void __cdecl lego::cfg::ReservedPool_CFGProperty___Cleanup(void)
{
	for (int i = 0; i < _countof(globals::g_CFG.pool_TABLE); i++) {
		if (globals::g_CFG.pool_TABLE[i] != nullptr)
			std::free(globals::g_CFG.pool_TABLE[i]);
	}
	globals::g_CFG.pool_NEXT = nullptr;
	globals::g_CFG.pool_ISINIT = false;
}

// <LegoRR.exe @00479120>
CFGRoot* __cdecl lego::cfg::CFG_Open(const char* filename)
{
	// read entire cfg file, it looks like...
	/// SANITY: This does not read the file with an extra character for null terminators.
	///         This will crash if your CFG file does not end with whitespace or a comments.

	unsigned int length = 0; // dummy init
	char* text = (char*)file::File_ReadAllBytes(filename, &length);
	if (text == nullptr)
		return nullptr;  // failed to read file, return null

	CFGRoot* root = ReservedPool_CFGProperty___Next(nullptr); // NULL, root property
	root->fileText = text;
	if (length == 0)
		return root;  // empty file, still return valid CFG root node

	// normalize whitespace characters -> '\0'
	// and handle ';' comments
	/// HELPER: Inserted 
	CFG_ZeroWhiteSpace(text, length);

	CFGNode* prop = (CFGNode*)root;
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
		else if (prop->key == nullptr) {
			// first non-whitespace, assign property key from here
			prop->key = text;
		}
		else {
			// second non-whitespace, assign property value -OR- block indent char "{"
			prop->value = text; // assigned even if value is "{" for block open

			// create next property node
			prop = ReservedPool_CFGProperty___Next(prop);

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

// <LegoRR.exe @00479210>
const char* __cdecl lego::cfg::CFG_JoinPath(const char* keyPath1, ...)
{
	// NOTE: the handling for keyPath3 as VA ARGS is weird, and will entirely depend on compiler behavior
	std::va_list vl;
	va_start(vl, keyPath1);
	const char* keyPathArg = va_arg(vl, const char*);

	std::strcpy(globals::g_CFG.tmp_CFG_JOINPATH, keyPath1);
	while (keyPathArg != nullptr) {
		std::strcat(globals::g_CFG.tmp_CFG_JOINPATH, "::");
		std::strcat(globals::g_CFG.tmp_CFG_JOINPATH, keyPathArg);
		keyPathArg = va_arg(vl, const char*);
	}
	va_end(vl);
	return globals::g_CFG.tmp_CFG_JOINPATH;
}

// <LegoRR.exe @004792b0>
CFGProperty* __cdecl lego::cfg::CFG_GetChildren(CFGProperty* prop, const char* keyPath)
{
	prop = CFG_GetProperty(prop, keyPath);
	// Nevermind, this is a function to get children...
	//   ~~A property is only designated a block if it contains children (the next property in the linked list is block->depth + 1)~~
	// Another instance of a check to propNext without null-checks... *sigh*
	if (prop != nullptr && prop->depth < prop->next->depth)
		return prop->next;

	return nullptr;
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
CFGProperty* __cdecl lego::cfg::CFG_NextFlat(CFGProperty* prop)
{
	unsigned int currentDepth = prop->depth;
	// only break on property of lower depth, as that means we've exited the block
	while (prop != nullptr && prop->depth >= currentDepth) {

		/// SANITY: Add null checks before accessing prop->depth
		prop = prop->next;
		if (prop->depth == currentDepth)
			return prop; // next same-depth property found in current block
	}
	return nullptr;
}

// <LegoRR.exe @00479310>
char* __cdecl lego::cfg::CFG_CopyString(CFGProperty* prop, const char* keyPath)
{
	prop = CFG_GetProperty(prop, keyPath);
	if (prop != nullptr && prop->value != nullptr)
		return ::_strdup(prop->value);

	return nullptr;
}

// <LegoRR.exe @00479370>
const char* __cdecl lego::cfg::CFG_ReadString(CFGProperty* prop, const char* keyPath)
{
	prop = CFG_GetProperty(prop, keyPath);
	if (prop != nullptr)
		return prop->value;

	return nullptr;
}

// <LegoRR.exe @00479390>
BOOL3 __cdecl lego::cfg::CFG_ReadBool(CFGProperty* prop, const char* keyPath)
{
	BOOL3 result = BOOL3_ERROR /*2*/; // error result

	// usage of CFG_CopyString over CFG_ReadString here seems pointless,
	//  since the value is never modified.
	// Though maybe util::parseBool requires a non-const string,
	//  and is a block box that *may* modify the value.
	char* str = CFG_CopyString(prop, keyPath);
	if (str != nullptr) {
		result = util::parseBool(str);
		std::free(str);
	}
	return result;
}

// <LegoRR.exe @004793d0>
float __cdecl lego::cfg::CFG_ReadRadians(CFGProperty* prop, const char* keyPath)
{
	// Definitely a preprocessor
	const char* propValue = (CFG_ReadString(prop, keyPath) ? CFG_ReadString(prop, keyPath) : "");
	if (propValue == nullptr) {
		propValue = ""/*EMPTYSTR*/;
	}
	else {
		propValue = CFG_ReadString(prop, keyPath);
	}

	double result = std::atof(propValue);
	if (result != 0.0) {
		return (result / 360.0f * (float)(M_PI * 2));
		//return (float)(result * 0.002777778 * 6.283185); // 61 0b 36 3b  // db 0f c9 40
		// * float32:0x3b360b61 * float32:0x40c90fdb   
	}
	return 0.0f;
}

// <LegoRR.exe @00479430>
BOOL __cdecl lego::cfg::CFG_ReadRGBF(CFGProperty* prop, const char* keyPath, float* out_r, float* out_g, float* out_b)
{
	char* str = CFG_CopyString(prop, keyPath);
	if (str != nullptr) {
		// this may cause all kinds of unexpected behavior if the property value has more than 2 ':'s
		char* parts[3];
		int numParts = util::stringSplit(str, parts, ":");
		if (numParts == 3) {
			// * float32:0x3b808081 (0.003921569)
			*out_r = (float)(std::atoi(parts[0]) * (float)(1.0 / 255.0));
			*out_g = (float)(std::atoi(parts[1]) * (float)(1.0 / 255.0));
			*out_b = (float)(std::atoi(parts[2]) * (float)(1.0 / 255.0));
		}
		std::free(str);
		return (numParts == 3);
	}
	return false;
}

// <LegoRR.exe @00479500>
void __cdecl lego::cfg::CFG_Close(CFGRoot* root)
{
	std::free(root->fileText); // free the buffer containing the entire CFG file text

	CFGNode* prop = (CFGNode*)root;
	while (prop != nullptr) {
		ReservedPool_CFGProperty___Release(prop);
		prop = prop->next;
	}
}

/// PRIVATE:
// <LegoRR.exe @00479530>
// void CFG__PoolNext(void);
CFGNode* __cdecl lego::cfg::ReservedPool_CFGProperty___Next(CFGNode* previous)
{
	/// SHORTHAND: CFGProperty* prop = ReservedPool<CFGNode>::Next()
	// if no next property is available, allocate more (assigns globals::g_CFG.pool_NEXT)
	if (globals::g_CFG.pool_NEXT == nullptr)
		ReservedPool_CFGProperty___Alloc();
	// break link to m_next for our new property (assign to self)
	pool::PoolItem<CFGProperty>* newProp = globals::g_CFG.pool_NEXT;
	pool::PoolItem<CFGProperty>* poolNext = globals::g_CFG.pool_NEXT->m_next;
	newProp->m_next = newProp;
	// assign globals::g_CFG.pool_NEXT to newly prepared m_next
	//  (which may potentially be NULL, in which case, the top of this function is triggered on next call)
	globals::g_CFG.pool_NEXT = poolNext;

	CFGProperty* prop = &newProp.m_item;


	prop->key   = nullptr;
	prop->value = nullptr;
	prop->next  = nullptr;
	if (previous != nullptr) {
		previous->next = prop;
		prop->previous = previous;
		prop->depth    = previous->depth;
		prop->fileText = nullptr; // field not used by non-root properties.
	}
	else { // Root CFG node
		prop->previous = nullptr;
		prop->depth    = 0;
	}
	return prop;
}

// <LegoRR.exe @00479580>
// void CFG__PoolRelease(void);
void __cdecl lego::cfg::ReservedPool_CFGProperty___Release(CFGNode* prop)
{
	prop->pool_m_next = globals::ReservedPool<CFGProperty>__g_NEXT;
	globals::ReservedPool<CFGProperty>__g_NEXT = prop;
}

/// PUBLIC:
// <LegoRR.exe @004795a0>
CFGProperty* __cdecl lego::cfg::CFG_GetProperty(CFGProperty* prop, const char* keyPath)
{
	// split keyPath into parts by "::"
	// create copy of keyPath, because stringSplit modifies the input string
	char* inputPath = ::_strdup(keyPath);
	char* parts[100];
	int numParts = lego::util::stringSplit(inputPath, parts, "::");

	CFGProperty* result = nullptr;

	while (prop != nullptr) {
		BOOL isWildcard = false;
		unsigned int depth = numParts - 1;
		// check for top-level key match
		if (prop->depth != depth || !CFG_IsKeyMatch(prop, parts[depth], &isWildcard)) {
			prop = prop->next;
			continue;
		}

		// key matched, now try to match all parent keys up to root, by walking up the tree
		CFGProperty* previous = prop->previous;

		// SANITY: Add `&& depth > 0` to check
		// (from the looks of it, CFG files can potentially have unbalanced block indents that go below 0)
		while (previous != nullptr) {
			if (previous->depth == depth - 1) { // is this property the starting block of previous?
				if (!CFG_IsKeyMatch(previous, parts[depth - 1], &isWildcard))
					break;  // no match, stop checking this path
				depth--;
			}
			previous = previous->previous;
		}

		if (depth == 0) { // have we matched all keys up to (and including) root?
			result = prop;
			// if exact match result is found, exit the loop
			//  otherwise keep searching in-case an exact match exists, which would overwrite the wildcard match
			//  e.g. "LegoRR" has precedence over "Lego*" (but only if a property is defined in "LegoRR")
			if (!isWildcard)
				break;
		}
		prop = prop->next;
	}

	std::free(inputPath); // free allocated string for parts comparison
	return result;
}

/// PRIVATE:
// <LegoRR.exe @00479750>
void __cdecl lego::cfg::ReservedPool_CFGProperty___Alloc(void)
{
	unsigned int count = 1 << globals::g_CFG.pool_COUNT;
	pool::PoolItem<CFGNode>* nextPool = (pool::PoolItem<CFGNode>*)std::malloc(count * sizeof(pool::PoolItem<CFGNode>));

	/// DEBUG: asserts are for testing only
	assert(nextPool != nullptr);

	globals::g_CFG.pool_TABLE[globals::g_CFG.pool_COUNT] = nextPool;
	if (nextPool != nullptr && count != 0) {
		globals::g_CFG.pool_COUNT++;
		for (unsigned int i = 1; i < count; i++)
			nextPool[i - 1].m_next = &nextPool[i];
		nextPool[count - 1].m_next = globals::g_CFG.pool_NEXT;
		
		/// DEBUG: asserts are for testing only
		assert(nextPool[count - 1].m_next == nullptr);

		globals::g_CFG.pool_NEXT = &nextPool[0];
	}
}

#pragma endregion
