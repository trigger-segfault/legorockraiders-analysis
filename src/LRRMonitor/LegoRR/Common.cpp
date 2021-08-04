// Common.cpp : Defines common utility (and personal helper) functions used by LegoRR / CLGen.
//

#include "Common.h"
//#include "Main/Main.h"

#pragma region Globals
namespace lego {
namespace globals {

	/*// [INCLUSIVE]:
	// <LegoRR.exe @00506f84>  XREF[82]
	CmdlineFlags g_CMDLINE_FLAGS;
	// [INCLUSIVE/ACCESSOR]: ParseCmdFlags, WinMain functions, game functions, GetProgrammerMode (accessor)
	// <LegoRR.exe @00506f88>  XREF[17]
	ProgrammerMode g_PROGRAMMER_MODE;
	// [EXCLUSIVE/ACCESSOR]: ParseCmdFlags, GetStartLevel (accessor)
	// <LegoRR.exe @00506f8c>  XREF[3,1]
	char g_STARTLEVEL[256];
	// [EXCLUSIVE/ACCESSOR]: ParseCmdFlags, GetDebugFlags (accessor)
	// <LegoRR.exe @0050708c>  XREF[2]
	DebugFlags g_DEBUG_FLAGS; // 0x8000 (block fade)*/

} /* namespace globals */
} /* namespace lego */
#pragma endregion


using namespace lego;
//using namespace lego::util;


#pragma region Custom Helper Functions

int __cdecl lego::debugoutf(const char* format, ...) {
	char buffer[2048];
	va_list argptr;
	va_start(argptr, format);
	int result = vsnprintf(buffer, sizeof(buffer), format, argptr);
	va_end(argptr);
	OutputDebugStringA(buffer);
	//OutputDebugStringA("\n");
	return result;
}

#pragma endregion


#pragma region Functions

/*// <LegoRR.exe @00401b30>
ProgrammerMode __cdecl lego::GetProgrammerMode(void)
{
	return globals::g_PROGRAMMER_MODE;
}

// <LegoRR.exe @00401b40>
const char* __cdecl lego::GetStartLevel(void)
{
	if (globals::g_CMDLINE_FLAGS & CMD_STARTLEVEL)
		return globals::g_STARTLEVEL;
	return nullptr;
}

// <LegoRR.exe @00401b70>
int __cdecl lego::GetResolutionWidth(void)
{
	return main::globals::g_RESOLUTION.width;
}

// <LegoRR.exe @00401b80>
int __cdecl lego::GetResolutionHeight(void)
{
	return main::globals::g_RESOLUTION.height;
}

// <LegoRR.exe @00478230>
FeatureFlags __cdecl lego::GetFeatureFlags(void)
{
	return globals::g_DEBUG_FLAGS;
}*/

#pragma endregion
