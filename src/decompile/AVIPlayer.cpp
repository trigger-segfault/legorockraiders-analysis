// AVIPlayer.cpp : Definitions file for the C++ AVIPlayer implementation and C wrapper.
//
/// STATUS: [COMPLETE]

#include "AVIPlayer.hpp"
#include "AVIPlayer.h"

#include "Files.h"


using namespace lego;
using namespace lego::video;


#pragma region Globals

// <LegoRR.exe @00534998>
bool lego::globals::g_AVIPlayer_IsDisabled = false; // dummy init

// <LegoRR.exe @0053499c>
IDirectDraw4 lego::globals::g_AVIPlayer_IDirectDraw4;

#pragma endregion


#pragma region AVIRenderer class definition

// <LegoRR.exe @0047e720>
// AVIRenderer* lego::video::AVIRenderer::deletor(unsigned char flag)
// {
// 	this->~AVIRenderer();
// 	if (flag & 0x1) {
// 		std::free(this);
// 		// (FUN_0045ddb0(void* ptr))
// 		//game::LevelStruct3C_Free_Unwind((LevelStruct_3c *)this) /*<LegoRR.exe @0045ddb0>*/;
// 	}
// 	return this;
// }

// <LegoRR.exe @0047e740>
lego::video::AVIRenderer::~AVIRenderer()
{
	//this->vftable = &AVIRenderer___vftable /*<LegoRR.exe @0049f9a0>*/;

	if (this->ddSurface4 != nullptr) {
		this->ddSurface4->Release();
		this->ddSurface4 = nullptr;
	}

	if (this->ddPalette != nullptr) {
		this->ddPalette->Release();
		this->ddPalette = nullptr;
	}
}

// <LegoRR.exe @0047e780>
lego::video::AVIRenderer::AVIRenderer(int width, int height, int bpp, bool useVideoMemory, int unused)
{
	this->field_unused_4 = 0;
	this->bool_unused_15 = false;
	this->isBPP15 = false;
	this->ddSurface4 = nullptr;
	this->isOpen = false;
	//this->vftable = &AVIRenderer___vftable /*<LegoRR.exe @0049f9a0>*/;
	this->InitSurfaceDesc(unused);
	if (this->InitSurface(width, height, bpp, useVideoMemory)) {
		this->isOpen = true;
	}
}

// <LegoRR.exe @0047e7d0>
void lego::video::AVIRenderer::InitSurface(int width, int height, int bpp, bool useVideoMemory)
{
	D3DRMPALETTEENTRY palette[256];

	// (this->surfDesc.dwFlags - should initially be 0)
	this->surfDesc.dwFlags |= DDSD_CAPS /*0x1*/;
	this->depth = bpp;

	if (width != 0) {
		this->surfDesc.dwFlags |= DDSD_WIDTH /*0x4*/;
		this->surfDesc.dwWidth = width;
	}
	if (height != 0) {
		this->surfDesc.dwFlags |= DDSD_HEIGHT /*0x2*/;
		this->surfDesc.dwHeight = height;
	}

	if (width == 0 && height == 0) {
		this->surfDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE /*0x200*/;
	}
	else {
		this->surfDesc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN /*0x40*/;
		if (useVideoMemory)
			this->surfDesc.ddsCaps.dwCaps |= DDSCAPS_VIDEOMEMORY /*0x4000*/;
		else
			this->surfDesc.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY /*0x800*/;
	}

	if (bpp != 0) {
		this->surfDesc.dwFlags |= DDSD_PIXELFORMAT /*0x1000*/;
		this->surfDesc.ddpfPixelFormat.dwSize = sizeof(this->surfDesc.ddpfPixelFormat) /*0x20*/;

		// specify as 16-bpp when proper depth is 15-bpp
		this->surfDesc.ddpfPixelFormat.dwRGBBitCount = (bpp != 15 ? bpp : 16);

		if (bpp == 24) { // 24-bpp
			this->surfDesc.ddpfPixelFormat.dwRBitMask = 0xff0000;
			this->surfDesc.ddpfPixelFormat.dwGBitMask = 0x00ff00;
			this->surfDesc.ddpfPixelFormat.dwBBitMask = 0x0000ff;
			this->surfDesc.ddpfPixelFormat.dwFlags = DDPF_RGB /*0x40*/;
		}
		else if (bpp == 16) { // 16-bpp (proper)
			this->surfDesc.ddpfPixelFormat.dwRBitMask = 0xf800; // 0b1111100000000000
			this->surfDesc.ddpfPixelFormat.dwGBitMask = 0x07e0; // 0b0000011111100000
			this->surfDesc.ddpfPixelFormat.dwBBitMask = 0x001f; // 0b0000000000011111
			this->surfDesc.ddpfPixelFormat.dwFlags = DDPF_RGB /*0x40*/;
		}
		else if (bpp == 15) { // 15-bpp (treated as 16-bpp)
			this->surfDesc.ddpfPixelFormat.dwRBitMask = 0x7c00; // 0b0111110000000000
			this->surfDesc.ddpfPixelFormat.dwGBitMask = 0x03e0; // 0b0000001111100000
			this->surfDesc.ddpfPixelFormat.dwBBitMask = 0x001f; // 0b0000000000011111
			this->surfDesc.ddpfPixelFormat.dwFlags = DDPF_RGB /*0x40*/;
		}
		else if (bpp == 8) { // 8-bpp (indexed)
			this->surfDesc.ddpfPixelFormat.dwRBitMask = 0xff0000;
			this->surfDesc.ddpfPixelFormat.dwGBitMask = 0x00ff00;
			this->surfDesc.ddpfPixelFormat.dwBBitMask = 0x0000ff;
			this->surfDesc.ddpfPixelFormat.dwFlags = DDPF_RGB | DDPF_PALETTEINDEXED8 /*0x40 | 0x20*/;
		}
	}

	if (globals::g_AVIPlayer_IDirectDraw4->CreateSurface(&this->surfDesc, &this->ddSurface4, nullptr) == 0) {
		this->LockSurface();
		this->UnlockSurface(); // yup... this really happens... maybe a safety check?

		
		if (this->surfDesc.ddpfPixelFormat.dwRGBBitCount == 8) {
			std::memset(palette, 0, sizeof(palette) /*0x400*/);

			if (globals::g_AVIPlayer_IDirectDraw4->CreatePalette(DDPCAPS_8BIT /*0x4*/, palette, &this->ddPalette, nullptr) == 0) {

				if (this->ddSurface4->SetPalette(this->ddPalette) != 0)
					return false;  // failure
			}
		}

		// (in assembly, this really is checked even after the `== 8` comparison, it's a bit of jumping around though)
		if (this->surfDesc.ddpfPixelFormat.dwRGBBitCount == 16) {
			// Count number of bits to check if we're actually using 15-bpp handling.
			//  (when surface considers it as 16-bpp)
			int bits = (this->countBits(this->surfDesc.ddpfPixelFormat.dwRBitMask) +
						this->countBits(this->surfDesc.ddpfPixelFormat.dwGBitMask) +
						this->countBits(this->surfDesc.ddpfPixelFormat.dwBBitMask));
			if (bits == 15)
				this->isBPP15 = true;
			// int rbits = this->countBits(this->surfDesc.ddpfPixelFormat.dwRBitMask);
			// int gbits = this->countBits(this->surfDesc.ddpfPixelFormat.dwGBitMask);
			// int bbits = this->countBits(this->surfDesc.ddpfPixelFormat.dwBBitMask);
			// if ((rbits + gbits + bbits) == 15)
			// 	this->isBPP15 = true;
		}

		return true;
	}
	return false;
}

// <LegoRR.exe @0047e9d0>
void lego::video::AVIRenderer::InitSurfaceDesc(int unused)
{
	std::memset(&this->surfDesc, 0, sizeof(this->surfDesc) /*0x7c*/);
	this->surfDesc.dwSize = sizeof(this->surfDesc) /*0x7c*/;

	this->ddSurface4 = nullptr;
	this->ddPalette = nullptr;
	this->isLocked = false;
	this->bool_unused_14 = false;
}

// <LegoRR.exe @0047ea00>
unsigned int lego::video::AVIRenderer::GetWidth() const
{
	return this->surfDesc.dwWidth;
}

// <LegoRR.exe @0047ea10>
unsigned int lego::video::AVIRenderer::GetHeight() const
{
	return this->surfDesc.dwHeight;
}

// <LegoRR.exe @0047ea20>
bool lego::video::AVIRenderer::LockSurface()
{
	if (!this->isLocked) {
		std::memset(&this->surfDesc, 0, sizeof(this->surfDesc) /*0x7c*/);
		this->surfDesc.dwSize = sizeof(this->surfDesc) /*0x7c*/;

		if (this->ddSurface4->Lock(nullptr, &this->surfDesc, DDLOCK_NOSYSLOCK | DDLOCK_WAIT /*0x800 | 0x1*/, nullptr) == 0) {
			this->isLocked = true;
			return true;
		}
	}
	return false;
}

// <LegoRR.exe @0047ea70>
bool lego::video::AVIRenderer::UnlockSurface()
{
	if (this->isLocked && this->ddSurface4->Unlock(nullptr) == 0) {
		this->isLocked = false;
		return true;
	}
	return false;
}

// <LegoRR.exe @0047eaa0>
int lego::video::AVIRenderer::countBits(unsigned int value) const
{
	int count = 0;
	for (unsigned int k = 0; k < 32; k++) {
		if (value & (0x1 << k))
			count++;
	}
	return count;
}

#pragma endregion


#pragma region AVIPlayer class definition

// <LegoRR.exe @0047eac0>
lego::video::AVIPlayer::AVIPlayer(const char* filename)
{
	this->bool_unused_98 = false;
	this->isOpen = false;
	this->renderer = nullptr;
	//this->vftable = &AVIPlayer___vftable /*<LegoRR.exe @0049f9b0>*/;
	const char* datadirFilename = lego::file::Path_JoinDataDir(filename);
	this->aviFrame  = nullptr;
	this->aviStream = nullptr;
	std::memset(&this->streamInfo, 0, sizeof(this->streamInfo) /*0x8c*/);

	this->rect.top    = 0;
	this->rect.bottom = 0;
	this->rect.left   = 0;
	this->rect.right  = 0;

	if (!globals::g_AVIPlayer_IsDisabled) {
		// fccType "sdiv" (as DWORD = 0x73646976) mmioFOURCC('v','i','d','s')
		DWORD fccType = streamtypeVIDEO /*mmioFOURCC('v','i','d','s') "sdiv"*/;
		if (::AVIStreamOpenFromFileA(&this->aviStream, datadirFilename, fccType, 0, 0, nullptr) != 0)
			return; // failure
			
		this->aviFrame = ::AVIStreamGetFrameOpen(this->aviStream, (BITMAPINFOHEADER*)AVIGETFRAMEF_BESTDISPLAYFMT /*0x1*/);
		if (this->aviFrame == nullptr)
			return; // failure

		if (::AVIStreamInfoA(this->aviStream, &this->streamInfo, sizeof(this->streamInfo) /*0x8c*/) != 0)
			return; // failure

		DWORD dwTime = ::timeGetTime();
		this->isOpen = true;
		this->position = 0;
		this->rect.top    = this->streamInfo.rcFrame.top;
		this->rect.bottom = this->streamInfo.rcFrame.bottom;
		this->rect.left   = this->streamInfo.rcFrame.left;
		this->rect.right  = this->streamInfo.rcFrame.right;
		this->startTime = (float)(unsigned long long)dwTime * 0.001f; // milliseconds (uint) -> seconds (float)
		this->renderer = new AVIRenderer(this->rect.right - this->rect.left,
										 this->rect.bottom - this->rect.top,
										 0 /*no bpp override*/, false /*!useVideoMemory*/, 0 /*unused*/);
	}
}

// <LegoRR.exe @0047ec40>
// AVIPlayer* lego::video::AVIPlayer::deletor(unsigned char flag)
// {
// 	this->~AVIPlayer();
// 	if (flag & 0x1) {
// 		std::free(this);
// 		// (FUN_0045ddb0(void* ptr))
// 		//game::LevelStruct3C_Free_Unwind((LevelStruct_3c *)this) /*<LegoRR.exe @0045ddb0>*/;
// 	}
// 	return this;
// }

// <LegoRR.exe @0047ec60>
lego::video::AVIPlayer::~AVIPlayer()
{
	//this->vftable = &AVIPlayer___vftable /*<LegoRR.exe @0049f9b0>*/;

	if (!globals::g_AVIPlayer_IsDisabled) {

		if (this->aviStream != nullptr) {
			::AVIStreamRelease(this->aviStream);
		}

		if (this->renderer != nullptr) {
			// this->renderer->vftable->deletor(0x1);
			delete this->renderer;
		}
	}
}

// <LegoRR.exe @0047eca0>
bool lego::video::AVIPlayer::UpdateFrame(void* frameData)
{
	bool result = false;
	if (!this->renderer->isLocked && this->renderer->LockSurface())
		result = true;

	int width  = this->rect.right - this->rect.left;
	int height = this->rect.bottom - this->rect.top;
	int stride = (int)this->renderer->surfDesc.lPitch;
	// int stride_2 = (int)this->renderer->surfDesc.lPitch / 2;

	unsigned int depth = 15;
	if (!this->renderer->isBPP15)
		depth = this->renderer->surfDesc.ddpfPixelFormat.dwRGBBitCount;

	// "Corporate needs you to find the differences between these two code blocks."
	// 
	// Originally 2 duplicate code blocks performing IDENTICAL functionality were here.
	//  First was `if (depth == 15)`, then second was check if depth is 15-bpp *again*,
	//  then do THE SAME loop `if (depth == 16)`.
	/// CHANGE: swap out the first `depth == 15` confition for `depth == 15 || depth == 16` in a single block

	/// LIMITATION: Only 16-bpp-type depths are supported here
	if (depth == 15 || depth == 16) { // 15-bpp (treated as 16-bpp) || 16-bpp (proper)
		// pointer to start of last row (we need to copy *and* vertically flip data)
		unsigned char* srcRow = (unsigned char*)((unsigned char*)frameData + *(int *)frameData + (height - 1) * stride);
		unsigned char* dstRow = (unsigned char*)this->renderer->surfDesc.lpSurface;

		for (int y = 0; y < height; y++) {
			std::memcpy(dstData, srcData, (size_t)(width * 2));

			srcRow -= stride; // previous row
			dstRow += stride; // next row
		}
	}

	if (result)
		result = this->renderer->UnlockSurface();

	return result;
}

// <LegoRR.exe @0047ede0>
bool lego::video::AVIPlayer::Update()
{
	if (!this->isOpen || globals::g_AVIPlayer_IsDisabled)
		return false;

	void* frameData = ::AVIStreamGetFrame(this->aviFrame, this->position);
	if (frameData != nullptr) {
		this->UpdateFrame(frameData);

		DWORD dwTime = ::timeGetTime();
		this->rate = (float)(unsigned long long)this->streamInfo.dwRate / (float)(unsigned long long)this->streamInfo.dwScale;
		this->currentTime = (float)(unsigned long long)dwTime * 0.001f; // milliseconds (uint) -> seconds (float)

		// __ftol (std::round ??)
		this->position = (unsigned int)std::round((this->currentTime - this->startTime) * this->rate);
	}
	return true; // returns true regardless of nullptr IGetFrame*
}

// <LegoRR.exe @0047eea0>
unsigned int lego::video::AVIPlayer::GetLength() const
{
	if (!globals::g_AVIPlayer_IsDisabled)
		return this->streamInfo.dwLength;
	return 0;
}

// <LegoRR.exe @0047eeb0>
void lego::video::AVIPlayer::SetPosition(unsigned int newPosition)
{
	if (!globals::g_AVIPlayer_IsDisabled) {
		this->position = newPosition;

		DWORD dwTime = ::timeGetTime();
		this->currentTime = (float)(unsigned long long)dwTime * 0.001f; // milliseconds (uint) -> seconds (float)
		this->startTime = this->currentTime - ((float)(unsigned long long)this->position / this->rate);
	}
}

// <LegoRR.exe @0047ef20>
unsigned int lego::video::AVIPlayer::GetPosition() const
{
	if (!globals::g_AVIPlayer_IsDisabled)
		return this->position;
	return 0;
}

#pragma endregion


#pragma region AVIPlayer C wrapper functions

// <LegoRR.exe @0047ef40>
void __cdecl lego::video::InitAVIPlayer(IDirectDraw4* ddraw4)
{
	globals::g_AVIPlayer_IDirectDraw4 = ddraw4;

	::AVIFileInit();
}

// <LegoRR.exe @0047ef50>
AVIPlayer_t* __cdecl lego::video::AVIPlayer_Open(const char* filename)
{
	return (AVIPlayer_t*)new AVIPlayer(filename);
}

// <LegoRR.exe @0047efb0>
BOOL __cdecl lego::video::AVIPlayer_Update(AVIPlayer_t* aviPlayer)
{
	return ((AVIPlayer*)aviPlayer)->Update();
}

// <LegoRR.exe @0047efc0>
void __cdecl lego::video::AVIPlayer_Draw(AVIPlayer_t* aviPlayer, const RECT* rect)
{
	if (((AVIPlayer*)aviPlayer)->isOpen) {
		draw::Draw_GetDrawingSurface()->Blt(rect, ((AVIPlayer*)aviPlayer)->renderer->ddSurface4,
			nullptr, DDBLT_WAIT /*0x1000000*/, nullptr);
	}
	return;
}

// <LegoRR.exe @0047f000>
void __cdecl lego::video::AVIPlayer_SetPosition(AVIPlayer_t* aviPlayer, unsigned int newPosition)
{
	((AVIPlayer*)aviPlayer)->SetPosition(newPosition);
}

// <LegoRR.exe @0047f010>
unsigned int __cdecl lego::video::AVIPlayer_GetPosition(const AVIPlayer_t* aviPlayer)
{
	return ((const AVIPlayer*)aviPlayer)->GetPosition();
}

// <LegoRR.exe @0047f020>
unsigned int __cdecl lego::video::AVIPlayer_GetLength(const AVIPlayer_t* aviPlayer)
{
	return ((const AVIPlayer*)aviPlayer)->GetLength();
}

// Better description would be "Destroy", as it frees the memory.
// <LegoRR.exe @0047f030>
void __cdecl lego::video::AVIPlayer_Close(AVIPlayer_t* aviPlayer)
{
	if (aviPlayer != nullptr) {
		// extra cast here only because I'm wary about awkward behavior of the C++ delete keyword.
		AVIPlayer* aviPlayerClass = (AVIPlayer*)aviPlayer;
		delete aviPlayerClass;

		// //aviPlayer->vftable->deletor((AVIPlayer*)aviPlayer, 0x1);
		// delete (AVIPlayer*)aviPlayer;
	}
}

// <LegoRR.exe @0047f040>
BOOL __cdecl lego::video::AVIPlayer_IsOpen(const AVIPlayer_t* aviPlayer)
{
	return ((const AVIPlayer*)aviPlayer)->isOpen;
}

#pragma endregion
