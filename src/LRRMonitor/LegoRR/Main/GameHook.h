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

enum ObjectType2
{
    OBJECT_TVCAMERA = -1,
    OBJECT_NONE = 0,

    OBJECT_VEHICLE = 1,
    OBJECT_MINIFIGURE = 2,
    OBJECT_ROCKMONSTER = 3,
    OBJECT_BUILDING = 4,
    OBJECT_BOULDER = 5,
    OBJECT_POWERCRYSTAL = 6,
    OBJECT_ORE = 7,
    OBJECT_DYNAMITE = 8,
    OBJECT_BARRIER = 9,
    OBJECT_UPGRADEPART = 10,
    OBJECT_ELECTRICFENCE = 11,
    OBJECT_SPIDERWEB = 12,
    OBJECT_OOHSCARY = 13,
    OBJECT_ELECTRICFENCESTUD = 14,
    OBJECT_PATH = 15,
    OBJECT_PUSHER = 16,
    OBJECT_FREEZER = 17,
    OBJECT_ICECUBE = 18,
    OBJECT_LASERSHOT = 19,
};
static_assert(sizeof(ObjectType2) == 0x4, "");

#define TELEPORT_TYPE(t) TELEPORT_SERVIVE_## t = (1<<(((int)OBJECT_## t)-1))
enum TeleportServiceFlags
{
    TELEPORT_SERVIVE_NONE = 0,
    //TELEPORT_TYPE(NONE),
    TELEPORT_TYPE(VEHICLE),
    TELEPORT_TYPE(MINIFIGURE),
    TELEPORT_TYPE(ROCKMONSTER),
    TELEPORT_TYPE(BUILDING),
    TELEPORT_TYPE(BOULDER),
    TELEPORT_TYPE(POWERCRYSTAL),
    TELEPORT_TYPE(ORE),
    TELEPORT_TYPE(DYNAMITE),
    TELEPORT_TYPE(BARRIER),
    TELEPORT_TYPE(UPGRADEPART),
    TELEPORT_TYPE(ELECTRICFENCE),
    TELEPORT_TYPE(SPIDERWEB),
    TELEPORT_TYPE(OOHSCARY),
    TELEPORT_TYPE(ELECTRICFENCESTUD),
    TELEPORT_TYPE(PATH),
    TELEPORT_TYPE(PUSHER),
    TELEPORT_TYPE(FREEZER),
    TELEPORT_TYPE(ICECUBE),
    TELEPORT_TYPE(LASERSHOT),
};
static_assert(sizeof(TeleportServiceFlags) == 0x4, "");

// <LegoRR.exe @0046aa20>
ObjectType2 __cdecl Teleporter_GetServiceObjectType(TeleportServiceFlags serviceType);

// <LegoRR.exe @00477a60>
int APIENTRY MyWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow);

#pragma endregion


} /* namespace game */
} /* namespace lego */
