// VideoPlayer.h : Header file for the C VideoPlayer wrapper around the C++ implementation.
//
/// STATUS: [COMPLETE]
/// PURPOSE: VideoPlayer is used by all types of AVI video playback EXCEPT the credits starfield loop
///          This uses the IAMMultiMediaStream system, so this is why other video types are supported.
///
/// NAMESPACE: lego::video
/// INITIALIZE: (none)
/// FILEIO: Looks for a loose file in either the local Data directory or CDROM directory.

#pragma once

#include "Common.h"


#pragma region VideoPlayer C wrapper type
namespace lego {

/// PUBLIC:
// dummy type definition for C wrapper around VideoPlayer C++ class
typedef void VideoPlayer_t;

} /* namespace lego */
#pragma endregion


#pragma region VideoPlayer C wrapper functions
namespace lego::video {

/// PUBLIC:
// <LegoRR.exe @00472820>
VideoPlayer_t* __cdecl VideoPlayer_Open(const char* filename);
// cannot be const, due to using IDirectDraw-type interface
// <LegoRR.exe @00472930>
void __cdecl VideoPlayer_GetSize(VideoPlayer_t* videoPlayer, unsigned int* out_width, unsigned int* out_height);
// cannot be const, due to using IMultiMedia-type interface
// <LegoRR.exe @00472980>
long long __cdecl VideoPlayer_GetDuration(VideoPlayer_t* videoPlayer);
// float speed parameter is unused (name is assumed as 1.0f is always passed)
// <LegoRR.exe @00472990>
BOOL __cdecl VideoPlayer_Update(VideoPlayer_t* videoPlayer, float speed, const RECT* rect);
// <LegoRR.exe @004729b0>
void __cdecl VideoPlayer_Close(VideoPlayer_t* videoPlayer);

} /* namespace lego::video */
#pragma endregion

