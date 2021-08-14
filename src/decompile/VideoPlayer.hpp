// VideoPlayer.hpp : Header file for the C++ VideoPlayer implementation.
//
/// STATUS: [COMPLETE]
/// PURPOSE: See "VideoPlayer.h" for details.

#pragma once

#include "Common.h"


#pragma region Classes
namespace lego::video {

#pragma pack(push, 1)

#pragma region VideoPlayer class

/// PRIVATE:
class VideoPlayer
{
public:
	// (no vftable)
	/*00,4*/ IAMMultiMediaStream* amMediaStream;
	/*04,4*/ HRESULT errorCode;
	/*08,4*/ IMediaStream* mediaStream;
	/*0c,4*/ IDirectDrawMediaStream* ddMediaStream;
	/*10,4*/ IDirectDrawSurface* ddSampleSurface;
	/*14,4*/ IDirectDrawSurface3* ddDrawSurface;
	/*18,4*/ IDirectDrawStreamSample* ddStreamSample;
	/*1c,4*/ IDirectDrawSurface3* ddRenderSurface;
	/*2c,10*/ RECT rect;
	/*30,4*/ char* filename;
	/*34,4*/ IDirectDraw2* ddraw2;
	/*38*/

private:
	// <LegoRR.exe @004724a0>
	bool CreateSampleDDrawStreams(IAMMultiMediaStream* amMediaStream);
	// <LegoRR.exe @00472570>
	bool CreateAMMultiMediaStream(const char* filename, IAMMultiMediaStream** lplpAMMMStream, IDirectDraw2* ddraw2);

public:
	// <LegoRR.exe @00472650>
	VideoPlayer(const char* filename, IDirectDrawSurface3* ddSurface3, IDirectDraw2* ddraw2);
	// <LegoRR.exe @004726f0>
	~VideoPlayer();

	// float speed parameter is unused (name is assumed as 1.0f is always passed)
	// <LegoRR.exe @00472760>
	bool Update(float speed, const RECT* rect);
	// cannot be const, due to using IMultiMedia-type interface
	// <LegoRR.exe @004727f0>
	long long GetDuration();
};
static_assert(sizeof(VideoPlayer) == 0x38, "");

#pragma endregion

#pragma pack(pop)


#pragma region C funtion declarations (used in Ghidra)

/// CPP: declared in individual classes
#if 0
/// PRIVATE:
// <LegoRR.exe @004724a0>
bool __thiscall VideoPlayer__CreateSampleDDrawStreams(VideoPlayer* this, IAMMultiMediaStream* amMediaStream);
// <LegoRR.exe @00472570>
bool __thiscall VideoPlayer__CreateAMMultiMediaStream(VideoPlayer* this, const char* filename, IAMMultiMediaStream** lplpAMMMStream, IDirectDraw2* ddraw2);
// <LegoRR.exe @00472650>
VideoPlayer* __thiscall VideoPlayer___ctor(VideoPlayer* this, const char* filename, IDirectDrawSurface3* ddSurface3, IDirectDraw2* ddraw2);
// <LegoRR.exe @004726f0>
void __thiscall VideoPlayer___dtor(VideoPlayer* this);
// float speed parameter is unused (name is assumed as 1.0f is always passed)
// <LegoRR.exe @00472760>
bool __thiscall VideoPlayer__Update(VideoPlayer* this, float speed, const RECT* rect);
// cannot be const, due to using IMultiMedia-type interface
// <LegoRR.exe @004727f0>
long long __thiscall VideoPlayer__GetDuration(VideoPlayer* this);
#endif

#pragma endregion

} /* namespace lego::video */
#pragma endregion
