// (UNUSED) CFGClass.cpp : Defines LegoRR CFG configuration file functions
//

#include "CFGClass.h"
#include "Files.h"


namespace lego {
namespace CFG {
	namespace globals {

		#pragma region /// GLOBALS //////////////////////////////

		// Global singleton string buffer returned by JoinPath.
		// <LegoRR.exe @00507098>
		static char tmp_CFG_JOINPATH[1024];

		#pragma endregion

	} /* namespace globals */

	/*// [globals]
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
	lego::pool::ReservedPool<CFGClass, 32> PoolClass;*/

} /* namespace CFG */
} /* namespace lego */


using namespace lego::CFG;


#pragma region /// CFG FUNCTIONS ////////////////////////

// REQUIRED: pass NULL as final argument (except if keyPath2 == NULL)
// returns a temporary global string that must be used or copied before the next call to this function.
//
// I have no idea if this VA Args handling is implemented correctly, let's hope so.
// 
// <LegoRR.exe @00479210>
const char* __cdecl lego::CFG::CFGClass::JoinPath(const char* keyPath1, ...)
{
	// NOTE: the handling for keyPath3 as VA ARGS is weird, and will entirely depend on compiler behavior
	va_list vl;
	va_start(vl, keyPath1);
	const char* keyPathArg = va_arg(vl, const char*);

	strcpy(globals::tmp_CFG_JOINPATH, keyPath1);
	while (keyPathArg != nullptr) {
		strcat(globals::tmp_CFG_JOINPATH, "::");
		strcat(globals::tmp_CFG_JOINPATH, keyPathArg);
		keyPathArg = va_arg(vl, const char*);
	}
	va_end(vl);
	return globals::tmp_CFG_JOINPATH;
}

// Match a CFG property or block key name with the specified `keyName`.
// if the property key is at depth == 0, and has a '*' in it, wildcard comparison will be performed:
//   for wildcard comparison, anything including and beyond the '*' character is ignored.
//   This is used for "Lego*" to match with full names like "LegoRR", which can define property overrides.
//
// NOTE: This function has been isolated from GetProperty
// <LegoRR.exe -> GetProperty @004795a0>
BOOL __cdecl lego::CFG::CFGClass::IsKeyMatch(const char* keyName, BOOL* out_isWildcard) const
{
	*out_isWildcard = FALSE;
	if (this->depth == 0) {
		// exclude checking beyond '*', so i.e. keyName argument of "LegoRR" will successfully match against property key "Lego*"
		// this condition is only evaluated if this->key contains '*'
		const char* chr = strchr(this->key, '*');
		if (chr != nullptr) {
			size_t length = chr - this->key; // (PTR MATH: index of '*')
			*out_isWildcard = _strnicmp(keyName, this->key, length) == 0;
		}
	}
	return *out_isWildcard || _stricmp(keyName, this->key) == 0;
}

// prop points to the starting property to search from, it DOES NOT need to be the Lego* root property block
// 
// <LegoRR.exe @004795a0>
const CFGClass* lego::CFG::CFGClass::GetProperty(const char* keyPath) const
{
	// split keyPath into parts by "::"
	// create copy of keyPath, because stringSplit modifies the input string
	char* inputPath = _strdup(keyPath);
	char* parts[100];
	int numParts = lego::util::stringSplit(inputPath, parts, "::");

	const CFGClass* result = nullptr;
	const CFGClass* prop = this;

	while (prop != nullptr) {
		BOOL isWildcard = FALSE;
		unsigned int depth = numParts - 1;
		// check for top-level key match
		if (prop->depth != depth || !prop->IsKeyMatch(parts[depth], &isWildcard)) {
			prop = prop->next;
			continue;
		}

		// key matched, now try to match all parent keys up to root, by walking up the tree
		const CFGClass* previous = prop->previous;

		// SANITY: Add `&& depth > 0` to check
		// (from the looks of it, CFG files can potentially have unbalanced block indents that go below 0)
		while (previous != nullptr) {
			if (previous->depth == depth - 1) { // is this property the starting block of previous?
				if (!previous->IsKeyMatch(parts[depth - 1], &isWildcard))
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

// <LegoRR.exe @004792b0>
const CFGClass* lego::CFG::CFGClass::GetBlockFirstChild(const char* keyPath) const
{
	const CFGClass* prop = this->GetProperty(keyPath);
	// Nevermind, this is a function to get children...
	//   ~~A property is only designated a block if it contains children (the next property in the linked list is block->depth + 1)~~
	// Another instance of a check to propNext without null-checks... *sigh*
	if (prop != nullptr && prop->depth < prop->next->depth)
		return prop->next;

	return nullptr;
}

// <LegoRR.exe @00479370>
const char* lego::CFG::CFGClass::GetPropertyValue(const char* keyPath) const
{
	const CFGClass* prop = this->GetProperty(keyPath);
	if (prop != nullptr)
		return prop->value;

	return nullptr;
}

// <LegoRR.exe @00479310>
char* lego::CFG::CFGClass::CopyPropertyValue(const char* keyPath) const
{
	const CFGClass* prop = this->GetProperty(keyPath);
	if (prop == nullptr || prop->value == nullptr)
		return nullptr;

	// char* value = malloc(strlen(prop->value) + 1);
	// return strcpy(value, prop->value);
	return _strdup(prop->value);
}

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
const CFGClass* lego::CFG::CFGClass::NextFlatProperty() const
{
	const CFGClass* prop = this;
	unsigned int currentDepth = prop->depth;
	// only break on property of lower depth, as that means we've exited the block
	while (prop != nullptr && prop->depth >= currentDepth) {

		// SANITY: Add null checks before accessing prop->depth
		prop = prop->next;
		if (prop->depth == currentDepth)
			return prop; // next same-depth property found in current block
	}
	return nullptr;
}

// Converts RGB channels from int [0-255], -> float [0.0f-1.0f]
// 
// <LegoRR.exe @00479430>
BOOL lego::CFG::CFGClass::GetPropertyRGBF(const char* keyPath, float* out_r, float* out_g, float* out_b) const
{
	char* value = this->CopyPropertyValue(keyPath);
	if (value != nullptr) {
		// this may cause all kinds of unexpected behavior if the property value has more than 2 ':'s
		char* parts[3];
		int numParts = lego::util::stringSplit(value, parts, ":");
		if (numParts == 3) {
			// * float32:0x3b808081 (0.003921569)
			*out_r = (float)(std::atoi(parts[0]) * (1.0 / 255.0));
			*out_g = (float)(std::atoi(parts[1]) * (1.0 / 255.0));
			*out_b = (float)(std::atoi(parts[2]) * (1.0 / 255.0));
		}
		std::free(value);
		return (numParts == 3);
	}
	return FALSE;
}

// Gets a floating point value in degrees and transforms it into radians.
// 
// <LegoRR.exe @004793d0>
float __cdecl lego::CFG::CFGClass::GetPropertyRadians(const char* keyPath) const
{
	const char* propValue = this->GetPropertyValue(keyPath);
	if (propValue == NULL) {
		propValue = ""/*EMPTYSTR*/;
	}
	else {
		propValue = this->GetPropertyValue(keyPath);
	}
	double result = std::atof(propValue);
	if (result != 0.0) {
		return (float)(result / 360.0f * (float)(M_PI * 2));
		//return (float)(result * 0.002777778 * 6.283185); // 61 0b 36 3b  // db 0f c9 40
		// * float32:0x3b360b61 * float32:0x40c90fdb   
	}
	return 0.0f;
}

// returns 0 or 1 on success, and 2 on failure
// 
// <LegoRR.exe @00479390>
lego::BOOL3 __cdecl lego::CFG::CFGClass::GetPropertyBool(const char* keyPath) const
{
	BOOL3 result = BOOL3_ERROR /*2*/; // error result
	// usage of CFG_copyPropertyValue over CFG_getPropertyValue here seems pointless, since the value is never modified
	char* value = this->CopyPropertyValue(keyPath);
	if (value != nullptr) {
		result = util::parseBoolLiteral(value);
		std::free(value);
	}
	return result;
}

// <LegoRR.exe @00479530>
CFGClass* __cdecl lego::CFG::CFGClass::CFG__Next(CFGClass* previous)
{
	/*if (Pool.g_NEXT == nullptr) {
		// no next property is allocated, make more (assigns Pool.g_NEXT)
		Pool.Alloc();
	}*/

	/*pool::PoolItem<CFGClass>* poolProp = Pool.g_NEXT;
	pool::PoolItem<CFGClass>* poolNext = Pool.g_NEXT->m_next;
	// break link to m_next for our new property
	poolProp->m_next = poolProp;
	// assign Pool.g_NEXT to newly prepared m_next
	//  (which may potentially be NULL, in which case, the top of this function is triggered on next call)
	Pool.g_NEXT = poolNext;
	CFGClass* prop = &poolProp.m_item;*/

	CFGClass* prop = Pool.Next();

	prop->key = nullptr;
	prop->value = nullptr;
	prop->next = nullptr;
	if (previous != nullptr) {
		previous->next = prop;
		prop->previous = previous;
		prop->depth = previous->depth;
		prop->fileText = nullptr; // field not used by non-root properties.
	}
	else {
		prop->previous = nullptr;
		prop->depth = 0;
	}
	return prop;
}

// Normalize whitespace characters -> '\0'
// includes handling of ';' comments
// newlines only require '\n' (no '\r' is needed)
// this essentially tokenizes the entire text file buffer without allocating more space.
//
// NOTE: This function has been isolated from Open
// <LegoRR.exe -> Open @00479120>
void __cdecl lego::CFG::CFGClass::ZeroWhiteSpace(char* text, unsigned int length)
{
	BOOL isComment = FALSE;
	for (unsigned int i = 0; i < length; i++, text++) {
		char c = *text;
		if (c == ';')
			isComment = TRUE; // whitespace until EOL
		else if (c == '\n')    // (surprisingly no requirement for "\r\n")
			isComment = FALSE; // end any existing comment

		if (isComment || c == '\t' || c == '\n' || c == '\r' || c == ' ') {
			*text = '\0'; // normalize whitespace char
		}
	}
}

// Open and read all the properties of a CFG file, and return the root property.
// 
// <LegoRR.exe @00479120>
CFGClass* __cdecl lego::CFG::CFGClass::Open(const char* filename)
{
	// read entire cfg file, it looks like...
	unsigned int length;
	char* text = (char*)file::File_ReadAllBytes(filename, &length);
	if (text == nullptr)
		return nullptr;  // failed to read file, return null

	CFGClass* root = CFG__Next(nullptr); // NULL, root property
	root->fileText = text;
	if (length == 0)
		return root;  // empty file, still return valid CFG root node

	// normalize whitespace characters -> '\0'
	// and handle ';' comments
	ZeroWhiteSpace(text, length);

	CFGClass* prop = root;
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
			prop = CFG__Next(prop);

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

// Essentially walk through the tree, and return all unused properties to the pool
// 
// <LegoRR.exe @00479500>
void lego::CFG::CFGClass::Close()
{
	std::free(this->fileText); // free the buffer containing the entire CFG file text

	CFGClass* prop = this;
	while (prop != nullptr) {
		Pool.Release(prop);
		prop = const_cast<CFGClass*>(prop->next);
	}
}

#pragma endregion
