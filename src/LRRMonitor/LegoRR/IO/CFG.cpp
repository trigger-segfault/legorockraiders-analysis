#include "CFG.h"

using namespace lego;

#define makeFunc(addr, ret, name, ...) static ret (__cdecl* name )( __VA_ARGS__ ) = (( ret (__cdecl*)( __VA_ARGS__ )) 0x ##addr )

#define makeGlob(addr, type, name) static type name = (( type ) 0x ##addr )

#define defineGlobal(addr, type) (( type *) 0x ## addr)


//static void(__cdecl* CFG_Close)(lego::CFG* cfg) = (void(__cdecl*)(lego::CFG* cfg))0x00479500;
//static void(__cdecl* CFG_Open)(const char* filename) = (void(__cdecl*)(lego::CFG * cfg))0x00479120;


#define makeGlob(addr, type, name) static type name = (( type ) 0x ##addr )

#define defineGlobal(addr, type) (( type *) 0x ## addr)

//#define tmp_CFG_JOINPATH ((char*)0x00507098)
//#define tmp_CFG_JOINPATH  defineGlobal(00507098,  char*)

makeGlob(00507098,  char*, tmp_CFG_JOINPATH);

makeFunc(00479120,  lego::CFG*,         CFG_Open,               const char* filename);
makeFunc(004792b0,  const CFGProperty*, CFG_GetBlockFirstChild, const CFGProperty* prop, const char* keyPath);
makeFunc(004792e0,  const CFGProperty*, CFG_NextFlatProperty,   const CFGProperty* prop);
makeFunc(00479310,  char*,              CFG_CopyPropertyValue,  const CFGProperty* prop, const char* keyPath);
makeFunc(00479370,  const char*,        CFG_GetPropertyValue,   const CFGProperty* prop, const char* keyPath);
makeFunc(00479390,  BOOL3,              CFG_GetPropertyBool,    const CFGProperty* prop, const char* keyPath);
makeFunc(004793d0,  float,              CFG_GetPropertyRadians, const CFGProperty* prop, const char* keyPath);
makeFunc(00479430,  BOOL,               CFG_GetPropertyRGBF,    const CFGProperty* prop, const char* keyPath, float* out_r, float* out_g, float* out_b);
makeFunc(00479500,  void,               CFG_Close,              lego::CFG* cfg);
makeFunc(004795a0,  const CFGProperty*, CFG_GetProperty,        const CFGProperty* prop, const char* keyPath);

// Open and read all the properties of a CFG file, and return the root property.
// 
// <LegoRR.exe @00479120>
lego::CFG* __cdecl lego::CFG::Open(const char* filename)
{
	return CFG_Open(filename);
}
// Essentially walk through the tree, and return all unused properties to the pool
// 
// <LegoRR.exe @00479500>
void lego::CFG::Close()
{
	CFG_Close(this);
	//ptr CFG_Close = (ptr)0x00479500;
}


bool lego::CFG::IsOpen() const
{
	return !this->IsDisposed();
}

/*lego::CFG::CFG(const char* filename)
{

}

lego::CFG::~CFG()
{
	if (!this->IsDisposed())
		this->Close();
}*/
bool lego::CFGProperty::IsDisposed() const
{
	return this != this->pool_next;
}

class CFG : CFGProperty
{
	// Open and read all the properties of a CFG file, and return the root property.
	// 
	// <LegoRR.exe @00479120>
	CFG* __cdecl Open(const char* filename);

	// Open and read all the properties of a CFG file, and return the root property.
	// 
	// <LegoRR.exe @00479120>
	CFG(const char* filename);
	~CFG();

	// Essentially walk through the tree, and return all unused properties to the pool
	// 
	// <LegoRR.exe @00479500>
	void Close();
};

// char[1024]
//#define tmp_CFG_JOINPATH ((char*)0x00507098)

// REQUIRED: pass NULL as final argument (except if keyPath2 == NULL)
// returns a temporary global string that must be used or copied before the next call to this function.
//
// I have no idea if this VA Args handling is implemented correctly, let's hope so.
// 
// <LegoRR.exe @00479210>
const char* __cdecl lego::CFG::JoinPath(const char* keyPath1, ...)
{
	// NOTE: the handling for keyPath3 as VA ARGS is weird, and will entirely depend on compiler behavior
	va_list vl;
	va_start(vl, keyPath1);
	const char* keyPathArg = va_arg(vl, const char*);

	strcpy(tmp_CFG_JOINPATH, keyPath1);
	while (keyPathArg != nullptr) {
		strcat(tmp_CFG_JOINPATH, "::");
		strcat(tmp_CFG_JOINPATH, keyPathArg);
		keyPathArg = va_arg(vl, const char*);
	}
	va_end(vl);
	return tmp_CFG_JOINPATH;
}

// <LegoRR.exe @004792b0>
const CFGProperty* CFGProperty::GetBlockFirstChild(const char* keyPath) const
{
	return CFG_GetBlockFirstChild(this, keyPath);
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
const CFGProperty* CFGProperty::NextFlatProperty() const
{
	return CFG_NextFlatProperty(this);
}

// <LegoRR.exe @00479310>
char* CFGProperty::CopyPropertyValue(const char* keyPath) const
{
	return CFG_CopyPropertyValue(this, keyPath);
}

// <LegoRR.exe @00479370>
const char* CFGProperty::GetPropertyValue(const char* keyPath) const
{
	return CFG_GetPropertyValue(this, keyPath);
}

// returns 0 or 1 on success, and 2 on failure
// 
// <LegoRR.exe @00479390>
BOOL3 CFGProperty::GetPropertyBool(const char* keyPath) const
{
	return CFG_GetPropertyBool(this, keyPath);
}

// Gets a floating point value in degrees and transforms it into radians.
// 
// <LegoRR.exe @004793d0>
float CFGProperty::GetPropertyRadians(const char* keyPath) const
{
	return CFG_GetPropertyRadians(this, keyPath);
}

// Converts RGB channels from int [0-255], -> float [0.0f-1.0f]
// 
// <LegoRR.exe @00479430>
BOOL CFGProperty::GetPropertyRGBF(const char* keyPath, float* out_r, float* out_g, float* out_b) const
{
	return CFG_GetPropertyRGBF(this, keyPath, out_r, out_g, out_b);
}

/*// Essentially walk through the tree, and return all unused properties to the pool
// 
// <LegoRR.exe @00479500>
void CFGProperty::Close()
{
	return CFG_Close(this, keyPath);
}*/

/*// Contains the following ReservedPool<CFGProperty> function:
// <LegoRR.exe @00479530>
//CFGProperty* __cdecl pool::ReservedPool<CFGProperty>::Next(CFGProperty* previous);
// 
// <LegoRR.exe @00479530>
CFGProperty* CFG__Next(CFGProperty* previous);*/

// <LegoRR.exe @00479580>
//void __cdecl pool::ReservedPool<CFGProperty>::Release(CFGProperty* prop);

// Match a CFG property or block key name with the specified `keyName`.
// if the property key is at depth == 0, and has a '*' in it, wildcard comparison will be performed:
//   for wildcard comparison, anything including and beyond the '*' character is ignored.
//   This is used for "Lego*" to match with full names like "LegoRR", which can define property overrides.
//
// NOTE: This function has been isolated from GetProperty
// <LegoRR.exe -> GetProperty @004795a0>
//BOOL IsKeyMatch(const char* keyName, BOOL* out_isWildcard) const;

// prop points to the starting property to search from, it DOES NOT need to be the Lego* root property block
// 
// <LegoRR.exe @004795a0>
const CFGProperty* CFGProperty::GetProperty(const char* keyPath) const
{
	return CFG_GetProperty(this, keyPath);
}
