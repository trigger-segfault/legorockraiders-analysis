#pragma once

#include "../framework.h"
#include "Files.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define ERROR_LOADLOG			"Errors\\loadLog.dmp"
#define ERROR_LOADERRORLOG		"Errors\\loadErrorLog.dmp"
#define ERROR_REDUNDANTLOG		"Errors\\redundantFiles.dmp"

#pragma endregion

/**********************************************************************************
 ******** Enumerations
 **********************************************************************************/

#pragma region Enums

typedef enum Error_LoadErrorTAG
{
	Error_LoadError_InvalidFName,
	Error_LoadError_UnableToOpen,
	Error_LoadError_UnableToOpenForWrite,
	Error_LoadError_UnableToVerifyName,
	Error_LoadError_RMTexture,

	Error_LoadError_Count
};
static_assert(sizeof(Error_LoadErrorTAG) == 0x4, "");

#pragma endregion

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

typedef struct Error_Globs
{
	/*000,4*/ File_Dummy* dumpFile;
	/*004,4*/ File_Dummy* loadLogFile;
	/*008,4*/ File_Dummy* loadErrorLogFile;
	/*00c,4*/ File_Dummy* redundantLogFile;
	/*010,400*/ char loadLogName[1024];
	/*410,400*/ char redundantLogName[1024];
	/*810,4*/ BOOL warnCalled;
	/*814,4*/ BOOL fullScreen;
	/*818*/
} Error_Globs;
static_assert(sizeof(Error_Globs) == 0x818, "");

#pragma endregion

/**********************************************************************************
 ******** Globals
 **********************************************************************************/

#pragma region Globals

// <LegoRR.exe @00576ce0>
extern Error_Globs errorGlobs;

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @0048b520>
void __cdecl Error_Initialise(void);

// <LegoRR.exe @0048b540>
void __cdecl Error_FullScreen(BOOL on);

// <LegoRR.exe @0048b550>
void __cdecl Error_CloseLog(void);

// <LegoRR.exe @0048b5b0>
void __cdecl Error_Shutdown(void);

#pragma endregion

}
