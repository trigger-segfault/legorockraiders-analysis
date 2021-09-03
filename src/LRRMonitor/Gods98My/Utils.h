#pragma once

#include "../framework.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define UTIL_DEFSTRINGLEN		512
#define UTIL_LARGENUMBER		6293815		// For Util_HashString()
#define UTIL_MAXSTRINGLENGTH	256

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

//typedef char* Util_StringMatrix[4][4];


//char* __cdecl Util_GetLine(char** buffer, char* bufferEnd);

// <LegoRR.exe @00477700>
unsigned long __cdecl Util_Tokenise(IN OUT char* string, OUT char** argv, const char* sep);

// <LegoRR.exe @00477770>
unsigned long __cdecl Util_WSTokenise(IN OUT char* string, OUT char** argv);

// (char* ::_strdup(const char*))
// <LegoRR.exe @00477810>
char* __cdecl Util_StrCpy(const char* string);

// <LegoRR.exe @00477850>
char* __cdecl Util_RemoveUnderscores(const char* string, ...);

// <LegoRR.exe @004778d0>
char* __cdecl Util_StrIStr(char* str1, const char* str2);
// <LegoRR.exe @004778d0>
const char* __cdecl Util_StrIStr(const char* str1, const char* str2);

// <LegoRR.exe @00477930>
unsigned long __cdecl Util_HashString(const char* string, BOOL bIgnoreBlanks, BOOL upperCase);

//BOOL __cdecl Util_IsNumber(const char* string);

// <LegoRR.exe @004779d0>
unsigned long __cdecl Util_GetBoolFromString(const char* string);

/*VOID __cdecl Util_MultiplyStringMatrix(Util_StringMatrix r, Util_StringMatrix a, Util_StringMatrix b);
VOID __cdecl Util_PrintStringMatrix(Util_StringMatrix r);
VOID __cdecl Util_TransposeStringMatrix(Util_StringMatrix m);
VOID __cdecl Util_FreeStringMatrix(Util_StringMatrix m);*/

#pragma endregion

}

