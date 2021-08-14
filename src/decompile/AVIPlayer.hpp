// AVIPlayer.hpp : Header file for the C++ AVIPlayer implementation.
//
/// STATUS: [COMPLETE]
/// PURPOSE: See "AVIPlayer.h" for details.

#pragma once

#include "Common.h"


#pragma region Classes
namespace lego::video {

#pragma pack(push, 1)

#pragma region AVIRenderer class

/// PRIVATE:
class AVIRenderer
{
public:
	// /*00,4*/ vftable;
	/*04,4*/ unsigned int field_unused_4;
	/*08,1*/ bool isLocked;
	/*09,3*/ unsigned char reserved1[3];
	/*0c,4*/ int depth;
	/*10,4*/ IDirectDrawPalette* ddPalette;
	/*14,1*/ bool bool_unused_14;
	/*15,1*/ bool bool_unused_15;
	/*16,1*/ bool isBPP15;
	/*17,1*/ bool isOpen;
	/*18,4*/ IDirectDrawSurface4* ddSurface4;
	/*1c,7c*/ DDSURFACEDESC2 surfDesc;
	/*98*/

	
	// <LegoRR.exe @0047e720>
	// AVIRenderer* deletor(unsigned char flag);
	// <LegoRR.exe @0047e740>
	~AVIRenderer();
	// <LegoRR.exe @0047e780>
	AVIRenderer(int width, int height, int bpp, bool useVideoMemory, int unused);

private:
	// <LegoRR.exe @0047e7d0>
	void InitSurface(int width, int height, int bpp, bool useVideoMemory);
	// <LegoRR.exe @0047e9d0>
	void InitSurfaceDesc(int unused);
public:
	// Virtual functions, possibly extending from some unseen base class, never used.
	// <LegoRR.exe @0047ea00>
	virtual unsigned int GetWidth() const;
	// <LegoRR.exe @0047ea10>
	virtual unsigned int GetHeight() const;
private:
	// <LegoRR.exe @0047ea20>
	bool LockSurface();
	// <LegoRR.exe @0047ea70>
	bool UnlockSurface();
	// <LegoRR.exe @0047eaa0>
	int countBits(unsigned int value) const;
};
static_assert(sizeof(AVIRenderer) == 0x98, "");

#pragma endregion


#pragma region AVIPlayer class

/// PRIVATE:
class AVIPlayer
{
public:
	// /*00,4*/ vftable;
	/*04,4*/ IAVIStream* aviStream;
	/*08,4*/ IGetFrame* aviFrame;
	/*0c,8c*/ AVISTREAMINFOA streamInfo;
	/*98,1*/ bool bool_unused_98;
	/*99,1*/ bool isOpen;
	/*9a,2*/ unsigned short reserved1;
	/*9c,10*/ RECT rect;
	/*ac,4*/ float startTime;
	/*b0,4*/ float currentTime;
	/*b4,4*/ float rate;
	/*b8,4*/ unsigned int position;
	/*bc,4*/ unsigned int reserved2;
	/*c0,4*/ AVIRenderer* renderer;
	/*c4*/

	
	// <LegoRR.exe @0047eac0>
	AVIPlayer(const char* filename);
	// <LegoRR.exe @0047ec40>
	// AVIPlayer* deletor(unsigned char flag);
	// <LegoRR.exe @0047ec60>
	~AVIPlayer();

private:
	// <LegoRR.exe @0047eca0>
	bool UpdateFrame(void* frameData);
public:
	// <LegoRR.exe @0047ede0>
	bool Update();
	// <LegoRR.exe @0047eea0>
	unsigned int GetLength() const;
	// <LegoRR.exe @0047eeb0>
	void SetPosition(unsigned int newPosition);
	// <LegoRR.exe @0047ef20>
	unsigned int GetPosition() const;
};
static_assert(sizeof(AVIPlayer) == 0xc4, "");

#pragma endregion

#pragma pack(pop)


#pragma region C funtion declarations (used in Ghidra)

/// CPP: declared in individual classes
#if 0
/// PRIVATE:
// <LegoRR.exe @0047e720>
AVIRenderer* __thiscall AVIRenderer___deletor(AVIRenderer *this, unsigned char flag);
// <LegoRR.exe @0047e740>
void __thiscall AVIRenderer___dtor(AVIRenderer* this);
// <LegoRR.exe @0047e780>
AVIRenderer* __thiscall AVIRenderer___ctor(AVIRenderer* this, int width, int height, int bpp, bool useVideoMemory, int unused);
// <LegoRR.exe @0047e7d0>
bool __thiscall AVIRenderer__InitSurface(AVIRenderer* this, int width, int height, int bpp, bool useVideoMemory);
// <LegoRR.exe @0047e9d0>
void __thiscall AVIRenderer__InitSurfaceDesc(AVIRenderer *this, int unused);
// <LegoRR.exe @0047ea00>
unsigned int __thiscall AVIRenderer__GetWidth(const AVIRenderer* this);
// <LegoRR.exe @0047ea10>
unsigned int __thiscall AVIRenderer__GetHeight(const AVIRenderer* this);
// <LegoRR.exe @0047ea20>
bool __thiscall AVIRenderer__LockSurface(AVIRenderer* this);
// <LegoRR.exe @0047ea70>
bool __thiscall AVIRenderer__UnlockSurface(AVIRenderer* this);
// <LegoRR.exe @0047eaa0>
int __thiscall AVIRenderer__countBits(const AVIRenderer* this, unsigned int value);

// <LegoRR.exe @0047eac0>
AVIPlayer* __thiscall AVIPlayer___ctor(AVIPlayer* this, const char* filename);
// <LegoRR.exe @0047ec40>
AVIPlayer* __thiscall AVIPlayer___deletor(AVIPlayer* this, unsigned char flag);
// <LegoRR.exe @0047ec60>
void __thiscall AVIPlayer___dtor(AVIPlayer* this);
// <LegoRR.exe @0047eca0>
bool __thiscall AVIPlayer__UpdateFrame(AVIPlayer* this, void* frameData);
// <LegoRR.exe @0047ede0>
bool __thiscall AVIPlayer__Update(AVIPlayer* this);
// <LegoRR.exe @0047eea0>
unsigned int __thiscall AVIPlayer__GetLength(const AVIPlayer* this);
// <LegoRR.exe @0047eeb0>
void __thiscall AVIPlayer__SetPosition(AVIPlayer* this, unsigned int newPosition);
// <LegoRR.exe @0047ef20>
unsigned int __thiscall AVIPlayer__GetPosition(const AVIPlayer* this);
#endif

#pragma endregion

} /* namespace lego::video */
#pragma endregion
