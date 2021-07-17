// GameHook.h : Declares functions for hooking the WinMain
//              game loop up to the LegoRR game engine.
//

#pragma once

#include "../Common.h"


namespace lego {
namespace game {

#pragma region Types

#pragma endregion


#pragma region Globals

namespace globals {
} /* namespace globals */

#pragma endregion


#pragma region Functions

// This function is the hook that links the base engine setup to the actual gameplay and game configurations.
// Everything called by this (or functions passed by this) is the only time any of the game-relevant variables are used.
// <LegoRR.exe @0041f950>
BOOL __cdecl InitGameFunctions(const char* gameName);

#pragma endregion


} /* namespace game */
} /* namespace lego */
