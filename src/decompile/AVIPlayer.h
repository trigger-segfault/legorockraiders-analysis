// AVIPlayer.h : Header file for the C AVIPlayer wrapper around the C++ implementation.
//
/// STATUS: [COMPLETE]
/// PURPOSE: AVIPlayer is only by the Credits looping starfield background AVI.
///          This uses the AVIFile API, and thus is likely restricted to this file format.
///          This is likely used over the VideoPlayer class, since it offers more flexibility
///          with rendering, which allows drawing the credits text over-top and manually handling
///          video looping.
///
/// NAMESPACE: lego::video
/// INITIALIZE: Call `InitAVIPlayer(IDirectDraw4*)` once on startup. `IDirectDraw4*` is not owned by this module.
///             (no cleanup)
/// GLOBALS: private
/// FILEIO: Looks for a loose file ONLY in the local Data directory.

#pragma once

#include "Common.h"


#pragma region AVIPlayer C wrapper type
namespace lego {

/// PUBLIC:
// dummy type definition for C wrapper around AVIPlayer C++ class
typedef void AVIPlayer_t;

} /* namespace lego */
#pragma endregion


#pragma region Globals
namespace lego::globals {

/// PRIVATE:
// <LegoRR.exe @00534998>
extern bool g_AVIPlayer_IsDisabled;
// <LegoRR.exe @0053499c>
extern IDirectDraw4 g_AVIPlayer_IDirectDraw4;

} /* namespace lego::globals */
#pragma endregion


#pragma region AVIPlayer C wrapper functions
namespace lego::video {

/// PUBLIC:
// <LegoRR.exe @0047ef40>
void __cdecl InitAVIPlayer(IDirectDraw4* ddraw4);
// <LegoRR.exe @0047ef50>
AVIPlayer_t* __cdecl AVIPlayer_Open(const char* filename);
// <LegoRR.exe @0047efb0>
BOOL __cdecl AVIPlayer_Update(AVIPlayer_t* aviPlayer);
// <LegoRR.exe @0047efc0>
void __cdecl AVIPlayer_Draw(AVIPlayer_t* aviPlayer, const RECT* rect);
// <LegoRR.exe @0047f000>
void __cdecl AVIPlayer_SetPosition(AVIPlayer_t* aviPlayer, unsigned int newPosition);
// <LegoRR.exe @0047f010>
unsigned int __cdecl AVIPlayer_GetPosition(const AVIPlayer_t* aviPlayer);
// <LegoRR.exe @0047f020>
unsigned int __cdecl AVIPlayer_GetLength(const AVIPlayer_t* aviPlayer);
// Better description would be "Destroy", as it frees the memory.
// <LegoRR.exe @0047f030>
void __cdecl AVIPlayer_Close(AVIPlayer_t* aviPlayer);
// <LegoRR.exe @0047f040>
BOOL __cdecl AVIPlayer_IsOpen(const AVIPlayer_t* aviPlayer);

} /* namespace lego::video */
#pragma endregion

