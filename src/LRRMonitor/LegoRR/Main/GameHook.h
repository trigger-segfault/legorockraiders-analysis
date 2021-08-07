// GameHook.h : Declares functions for hooking the WinMain
//              game loop up to the LegoRR game engine.
//

#pragma once

#include "../Common.h"
#include "../Model/Model.h"


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
//BOOL __cdecl InitGameFunctions(const char* gameName);


// <LegoRR.exe @004786b0>
BOOL __cdecl CreateMainWindow(HINSTANCE hInstance, int nCmdShow);

// <LegoRR.exe @00478b40>
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// <LegoRR.exe @00478290>
BOOL __cdecl SetGameFunctions(GameFunctions* gameFuncs);

// <LegoRR.exe @00478690>
void __cdecl SetMainWindowTitle(const char* title);

// <LegoRR.exe @00438670>
void __cdecl LiveObject_SetIsCrystalPowered(LiveObject* liveObj, BOOL isPowered);

// <LegoRR.exe @00469ed0>
BOOL __cdecl LiveObject_SetLevel(LiveObject* liveObj, unsigned int level);

// <LegoRR.exe @00474060>
void __cdecl Res_SetOwnerObject(ResourceData* resData, LiveObject* liveObj);

// <LegoRR.exe @00474ce0>
//int __cdecl Res_GetMeshGroupCount(ResourceData* resData);

// <LegoRR.exe @004752e0>
//void __cdecl Res_SetMeshColorMultiplier(ResourceData* resData, int index, float r, float g, float b, float unkMultiplier);

// <LegoRR.exe @004752b0>
//void __cdecl Res_SetMeshColorUnk(ResourceData* resData, int index, float r, float g, float b);

// <LegoRR.exe @0044b400>
void __cdecl Level_GenerateSmallSpiders(unsigned int x, unsigned int y, unsigned int randSeed);

#pragma endregion


} /* namespace game */
} /* namespace lego */
