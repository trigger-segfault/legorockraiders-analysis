#include "CFG2.h"
#include "../Model/External.h"

using namespace lego;


#pragma region Custom Functions

/// CUSTOM: Helper function for use within CFG_GetProperty
// Match a CFG property or block key name with the specified `keyName`.
// if the property key is at depth == 0, and has a '*' in it, wildcard comparison will be performed:
//   for wildcard comparison, anything including and beyond the '*' character is ignored.
//   This is used for "Lego*" to match with full names like "LegoRR", which can define property overrides.
//
// NOTE: This function has been isolated from GetProperty
// <LegoRR.exe -> CFG_GetProperty @004795a0>
static BOOL __cdecl CFG_IsKeyMatch(const CFGProperty* prop, const char* keyName, BOOL* out_isWildcard)
{
	*out_isWildcard = FALSE;
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
static void __cdecl CFG_ZeroWhiteSpace(char* text, uint length)
{
	BOOL isComment = false;
	for (uint i = 0; i < length; i++, text++) {
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

#pragma endregion


#pragma region Functions

// <LegoRR.exe @004790b0>
void __cdecl lego::ReservedPool_CFGProperty___Init(void)
{
	std::memset(external::ReservedPool_CFGProperty___g_TABLE, 0, sizeof(external::ReservedPool_CFGProperty___g_TABLE));
	external::ReservedPool_CFGProperty___g_NEXT = nullptr;
	external::ReservedPool_CFGProperty___g_COUNT = 0;
	external::ReservedPool_CFGProperty___g_ISINIT = true;
}

// <LegoRR.exe @004790e0>
void __cdecl lego::ReservedPool_CFGProperty___Cleanup(void)
{
	for (int i = 0; i < _countof(external::ReservedPool_CFGProperty___g_TABLE); i++) {
		if (external::ReservedPool_CFGProperty___g_TABLE[i] != nullptr)
			std::free(external::ReservedPool_CFGProperty___g_TABLE[i]);
	}
	external::ReservedPool_CFGProperty___g_NEXT = nullptr;
	external::ReservedPool_CFGProperty___g_ISINIT = true;
}

// <LegoRR.exe @00479120>
CFGRoot* __cdecl lego::CFG_Open(const char* filename)
{
	// read entire cfg file, it looks like...
	/// SANITY: This does not read the file with an extra character for null terminators.
	///         This will crash if your CFG file does not end with whitespace or a comments.
	uint length;
	char* text = (char*)external::File_ReadAllBytes(filename, &length);
	if (text == nullptr)
		return nullptr;  // failed to read file, return null

	CFGRoot* root = lego::ReservedPool_CFGProperty___Next(nullptr); // NULL, root property
	root->fileText = text;
	if (length == 0)
		return root;  // empty file, still return valid CFG root node

	// normalize whitespace characters -> '\0'
	// and handle ';' comments
	/// HELPER: Inserted 
	CFG_ZeroWhiteSpace(text, length);

	CFGProperty* prop = (CFGProperty*)root;
	// read properties until EOF (length)
	for (uint i = 0; i < length; i++, text++) {
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
			prop = lego::ReservedPool_CFGProperty___Next(prop);

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
const char* __cdecl lego::CFG_JoinPath(const char* keyPath1, ...)
{
	// NOTE: the handling for keyPath3 as VA ARGS is weird, and will entirely depend on compiler behavior
	std::va_list vl;
	va_start(vl, keyPath1);
	const char* keyPathArg = va_arg(vl, const char*);

	std::strcpy(external::tmp_CFG_JOINPATH, keyPath1);
	while (keyPathArg != nullptr) {
		std::strcat(external::tmp_CFG_JOINPATH, "::");
		std::strcat(external::tmp_CFG_JOINPATH, keyPathArg);
		keyPathArg = va_arg(vl, const char*);
	}
	va_end(vl);
	return external::tmp_CFG_JOINPATH;
}

// <LegoRR.exe @004792b0>
const CFGProperty* __cdecl lego::CFG_GetChildren(const CFGProperty* prop, const char* keyPath)
{
}

// <LegoRR.exe @004792e0>
const CFGProperty* __cdecl lego::CFG_NextFlat(const CFGProperty* prop)
{

}

// <LegoRR.exe @00479310>
char* __cdecl lego::CFG_CopyString(const CFGProperty* prop, const char* keyPath)
{

}

// <LegoRR.exe @00479370>
const char* __cdecl lego::CFG_ReadString(const CFGProperty* prop, const char* keyPath)
{

}

// <LegoRR.exe @00479390>
BOOL3 __cdecl lego::CFG_ReadBool(const CFGProperty* prop, const char* keyPath)
{

}

// <LegoRR.exe @004793d0>
float __cdecl lego::CFG_ReadRadians(const CFGProperty* prop, const char* keyPath)
{

}

// <LegoRR.exe @00479430>
float __cdecl lego::CFG_ReadRGBF(const CFGProperty* prop, const char* keyPath, float* out_r, float* out_g, float* out_b)
{

}

// <LegoRR.exe @00479500>
void __cdecl lego::CFG_Close(CFGRoot* root)
{

}

// <LegoRR.exe @00479530>
CFGProperty* __cdecl lego::ReservedPool_CFGProperty___Next(CFGProperty* previous)
{

}

// <LegoRR.exe @00479580>
void __cdecl lego::ReservedPool_CFGProperty___Release(CFGProperty* prop)
{

}

// <LegoRR.exe @004795a0>
const CFGProperty* __cdecl lego::CFG_GetProperty(const CFGProperty* prop, const char* keyPath)
{

}

// <LegoRR.exe @00479750>
void __cdecl lego::ReservedPool_CFGProperty___Alloc(void)
{

}

#pragma endregion
