#pragma once

#include "Common.h"


#pragma region LRRCE

// Community Edition requires that this function be exported by LRRCE.DLL
// This requires `extern "C"` and `__cdecl` to avoid function name mangling.
extern "C" __declspec(dllexport) void __cdecl Dummy(void);

// Entry point, where we inject any desired functions.
BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved);


extern HINSTANCE g_hDllInstance;

extern FILE* logFile;
#define logmsg(msg, ...) if (logFile) { std::fprintf(logFile, msg, __VA_ARGS__); std::fflush(logFile); }

#pragma endregion
