// GameHook.cpp : Defines functions for hooking the WinMain
//                game loop up to the LegoRR game engine.

#include "GameHook.h"
#include "Main.h"

#include "../Testing/Testing.h"


using namespace lego::game;


#pragma region Functions

// This function is the hook that links the base engine setup to the actual gameplay and game configurations.
// Everything called by this (or functions passed by this) is the only time any of the game-relevant variables are used.
// <LegoRR.exe @0041f950>
BOOL __cdecl lego::game::InitGameFunctions(const char* gameName)
{
    // GameData struct
    //std::memset(&globals::g_Game, 0, sizeof(GameData));
    //globals::g_Game.CfgRootName = exeName;

    main::SetMainWindowTitle(gameName);

    main::GameFunctions gameFuncs = {
        testing::MyGameInitFunction,
        testing::MyGameUpdateFunction,
        testing::MyGameCleanupFunction
    };

    /// We're not actually setting up anything that's part of the game... this is just a skeleton
    /*GameFunctions gameFuncs;
    gameFuncs.Init = Main_loadLegoCFG;
    gameFuncs.Update = Main_GameUpdate;
    gameFuncs.Cleanup = Main_GameCleanup;

    if (globals::g_PROGRAMMER_MODE != PROGRAMMER_MODE_10) {
        gameFuncs.Cleanup = Game_Exit;
    }*/

    return main::SetGameFunctions(&gameFuncs);
}

#pragma endregion
