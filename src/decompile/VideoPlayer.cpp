// VideoPlayer.cpp : Definitions file for the C++ VideoPlayer implementation and C wrapper.
//
/// STATUS: [COMPLETE]

#include "VideoPlayer.hpp"
#include "VideoPlayer.h"


using namespace lego;
using namespace lego::video;


#pragma region VideoPlayer class definition

// <LegoRR.exe @004724a0>
bool lego::video::VideoPlayer::CreateSampleDDrawStreams(IAMMultiMediaStream* amMediaStream)
{
	this->errorCode = amMediaStream->GetMediaStream(&idl::MSPID_PrimaryVideo, &this->mediaStream);
	if (this->errorCode >= 0) {

		this->errorCode = this->mediaStream->QueryInterface(&idl::IID_IDirectDrawMediaStream, (void**)&this->ddMediaStream);
		if (this->errorCode >= 0) {

			// IDirectDrawMediaStream->CreateSample(this, IDirectDrawSurface* pSurface, const RECT* pRect, DWORD dwFlags, IDirectDrawStreamSample** ppSample)
			this->errorCode = this->ddMediaStream->CreateSample(nullptr, nullptr, 0, &this->ddStreamSample);
			if (this->errorCode >= 0) {

				// IDirectDrawStreamSample->GetSurface(this, IDirectDrawSurface** ppDirectDrawSurface, RECT* pRect)
				this->errorCode = this->ddStreamSample->GetSurface(&this->ddSampleSurface, &this->rect);
				if (this->errorCode >= 0) {

					this->errorCode = this->ddSampleSurface->QueryInterface(&idl::IID_IDirectDrawSurface3, (void**)&this->ddDrawSurface);
					if (this->errorCode >= 0) {

						this->errorCode = amMediaStream->SetState(STREAMSTATE_RUN /*0x1*/);
						if (this->errorCode >= 0)
							return true;

					}
				}
			}
		}
	}

	// hoh boy... failure is not an option...
	this->mediaStream->Release(); // failure to GetMediaStream this->mediaStream will probably crash here
	this->ddMediaStream->Release(); // failure to QueryInterface this->ddMediaStream will probably crash here
	this->ddStreamSample->Release(); // failure to CreateSample this->ddStreamSample will probably crash here
	this->ddSampleSurface->Release(); // failure to GetSurface this->ddSampleSurface will probably crash here

	return (this->errorCode >= 0);
}

// <LegoRR.exe @00472570>
bool lego::video::VideoPlayer::CreateAMMultiMediaStream(const char* filename, IAMMultiMediaStream** lplpAMMMStream, IDirectDraw2* ddraw2)
{
	IAMMultiMediaStream* amMMStream = nullptr; // dummy init
	wchar_t wfilenameBuffer[MAX_PATH /*260*/];

	HRESULT hresult = ::CoCreateInstance(&idl::CLSID_AMMultiMediaStream, nullptr, CLSCTX_INPROC_HANDLER /*0x1*/,
		&idl::IID_IAMMultiMediaStream, &amMMStream);
	if (hresult >= 0) {

		hresult = amMMStream->Initialize(STREAMTYPE_READ /*0x0*/, 0 /*separate-thread Filter Graph*/, nullptr);
		if (hresult >= 0) {

			hresult = amMMStream->AddMediaStream((IUnknown *)ddraw2, &idl::MSPID_PrimaryVideo, 0 /*no flags*/, nullptr);
			if (hresult >= 0) {

				hresult = amMMStream->AddMediaStream(nullptr, &idl::MSPID_PrimaryAudio, AMMSF_ADDDEFAULTRENDERER /*0x1*/, nullptr);
				if (hresult < 0)
					hresult = 0; // failure is just outright ignored here?

				// The IAMMultiMediaStream::OpenFile function only supports unicode,
				//  so convert our filename to wide chars.
				MultiByteToWideChar(CP_ACP /*0x0*/, 0 /*no flags*/, filename, -1 /*null-terminated*/,
					wfilenameBuffer, sizeof(wfilenameBuffer) /*MAX_PATH, 260*/);

				amMMStream->OpenFile(wfilenameBuffer, 0);

				*lplpAMMMStream = amMMStream; // assign to output
				amMMStream->AddRef(); // add ref for release at the bottom, kinda lazy
			}
		}
	}
	amMMStream->Release(); // failure to CoCreate amMMStream will probably crash here
	return (hresult >= 0);
}

// <LegoRR.exe @00472650>
lego::video::VideoPlayer::VideoPlayer(const char* filename, IDirectDrawSurface3* ddSurface3, IDirectDraw2* ddraw2)
{
	this->mediaStream = nullptr;
	this->ddMediaStream = nullptr;
	this->ddSampleSurface = nullptr;
	this->ddDrawSurface = nullptr;
	this->ddStreamSample = nullptr;
	this->ddRenderSurface = ddSurface3;
	this->ddraw2 = ddraw2;

	::CoInitialize(nullptr);

	if (filename != nullptr && std::strlen(filename) != 0) {
		this->filename = ::_strdup(filename);

		if (this->CreateAMMultiMediaStream(filename, &this->amMediaStream, ddraw2)) {
			this->CreateSampleDDrawStreams(this->amMediaStream);
		}
	}
	return this;
}

// <LegoRR.exe @004726f0>
lego::video::VideoPlayer::~VideoPlayer()
{
	if (this->mediaStream != nullptr)
		this->mediaStream->Release();
		
	if (this->ddMediaStream != nullptr)
		this->ddMediaStream->Release();
		
	if (this->ddStreamSample != nullptr)
		this->ddStreamSample->Release();
		
	if (this->ddSampleSurface != nullptr)
		this->ddSampleSurface->Release();
		
	if (this->ddRenderSurface != nullptr)
		this->ddRenderSurface->Release();
		
	if (this->ddraw2 != nullptr)
		this->ddraw2->Release();
		
	if (this->amMediaStream != nullptr)
		this->amMediaStream->Release();

	if (this->filename != nullptr)
		std::free(this->filename);
}

// float speed parameter is unused (name is assumed as 1.0f is always passed)
// <LegoRR.exe @00472760>
bool lego::video::VideoPlayer::Update(float speed, const RECT* rect)
{
	if (this->ddStreamSample == nullptr)
		return false;

	// Update playback (and renders to draw surface?)
	if (this->ddStreamSample->Update(0 /*no flags*/, nullptr, nullptr, nullptr) != 0) {
		// On failure... SHUTDOWN EVERYTHING!
		this->mediaStream->Release();
		this->mediaStream = nullptr;

		this->ddMediaStream->Release();
		this->ddMediaStream = nullptr;

		this->ddStreamSample->Release();
		this->ddStreamSample = nullptr;

		this->ddSampleSurface->Release();
		this->ddSampleSurface = nullptr;

		if (this->amMediaStream != nullptr) {
			this->amMediaStream->Release();
			this->amMediaStream = nullptr;
		}
		return false;
	}

	// Copy from draw surface to render surface
	HRESULT hresult = this->ddRenderSurface->Blt(rect, this->ddDrawSurface, nullptr, DDBLT_WAIT /*0x1000000*/, nullptr);
	return (hresult == 0);
}

// cannot be const, due to using IMultiMedia-type interface
// <LegoRR.exe @004727f0>
long long lego::video::VideoPlayer::GetDuration()
{
	long long duration = 0LL; // dummy init
	this->amMediaStream->GetDuration(&duration);
	// __alldiv - 64-bit integer division in 32-bit environments
	return duration / 10000LL; // some playback rate constant??
}

#pragma endregion


#pragma region VideoPlayer C wrapper functions

// <LegoRR.exe @00472820>
VideoPlayer_t* __cdecl lego::video::VideoPlayer_Open(const char* filename)
{
	char cdFileBuffer[512];

	/* actual start of C++ function */
	const char* filenameDataDir = file::Path_JoinDataDir(filenameNoDataDir);

	draw::Draw_GetDirectDraw()->QueryInterface(&idl::IID_IDirectDraw2, (void**)&ddraw2);
	draw::Draw_GetDrawingSurface()->QueryInterface(&idl::IID_IDirectDrawSurface3, (void**)&ddSurface3);

	FILE* stream = std::fopen(filenameDataDir, "r"); // the "r" rather than "rb" seems like a bad idea...
	if (stream != nullptr) {
		// Open file in local Data folder.
		// Close file stream, since it's only the equivalent of "file exists"
		std::fclose(stream);
		
		return (VideoPlayer_t*)new VideoPlayer(filenameDataDir, ddSurface3, ddraw2);
	}
	else if (file::Path_GetCDROMDataPath(cdFileBuffer, filename)) {
		// File not found in local Data folder, Try open in CDROM/Data folder.
		// Does not check if the file exists here.

		return (VideoPlayer_t*)new VideoPlayer(This, cdFileBuffer, ddSurface3, ddraw2);
	}

	// file not found in local data dir, and CDROM not found (doesn't check if exists on CDROM)
	return nullptr;
}

// cannot be const, due to using IDirectDraw-type interface
// <LegoRR.exe @00472930>
void __cdecl lego::video::VideoPlayer_GetSize(VideoPlayer_t* videoPlayer, unsigned int* out_width, unsigned int* out_height)
{
	DDSURFACEDESC surfDesc;
	std::memset(&surfDesc, 0, sizeof(surfDesc) /*0x6c*/);
	surfDesc.dwSize = sizeof(surfDesc) /*0x6c*/;

	videoPlayer->ddDrawSurface->GetSurfaceDesc(&surfDesc);

	*out_width  = surfDesc.dwWidth;
	*out_height = surfDesc.dwHeight;
}

// cannot be const, due to using IMultiMedia-type interface
// <LegoRR.exe @00472980>
long long __cdecl lego::video::VideoPlayer_GetDuration(VideoPlayer_t* videoPlayer)
{
	return ((VideoPlayer*)videoPlayer)->GetDuration();
}

// float speed parameter is unused (name is assumed as 1.0f is always passed)
// <LegoRR.exe @00472990>
BOOL __cdecl lego::video::VideoPlayer_Update(VideoPlayer_t* videoPlayer, float speed, const RECT* rect)
{
	return ((VideoPlayer*)videoPlayer)->Update(speed, rect);
}

// <LegoRR.exe @004729b0>
void __cdecl lego::video::VideoPlayer_Close(VideoPlayer_t* videoPlayer)
{
	if (videoPlayer != nullptr) {
		// extra cast here only because I'm wary about awkward behavior of the C++ delete keyword.
		VideoPlayer* videoPlayerClass = (VideoPlayer*)videoPlayer;
		delete videoPlayerClass;

		// delete videoPlayer;
		//VideoPlayer___dtor((VideoPlayer *)videoPlayer);
		/* This function is multi-purpose (the linker assigned functions with the same
		functionality to different areas). So distinguishing is annoying */
		//game::LevelStruct3C_Free_Unwind((LevelStruct_3c *)videoPlayer);
	}
}

#pragma endregion
