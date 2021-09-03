#pragma once

#include "../framework.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

// DirectX (dxbug.c) debugging loose static variables
typedef struct Dxbug_Globs
{
	/*000,4*/ HRESULT errnum;
	/*004,4*/ int line;
	/*008,4*/ int DXModuleNameNumber;
	/*00c,4*/ int DXNumErrorsSet;
	/*010,4*/ const char* file;
	/*014,4*/ unsigned int reserved1;
	/*018,800*/ char DXErrorString[2048]; // Last error that was set (actually [1024], but the space is unused)
	/*818*/
} Dxbug_Globs;
static_assert(sizeof(Dxbug_Globs) == 0x818, "");

#pragma endregion

/**********************************************************************************
 ******** Globals
 **********************************************************************************/

#pragma region Globals

// <LegoRR.exe @004ac788>
extern const char* DXModuleName[8];// = { "Unknown module", "Direct3D Retained Mode", "Direct Input", "Direct Draw", "Direct Sound", "Direct Play", "Direct3D Immediate mode", "IUknown Interface" };

// <LegoRR.exe @005498a8>
extern Dxbug_Globs dxbugGlobs;

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @0048a050>
void __cdecl SE(const char* error, const char* errdesc);

// <LegoRR.exe @0048a090>
HRESULT __cdecl Error_SetDXError(HRESULT err, int DXModule, char* File, int Line);

#pragma endregion

}
