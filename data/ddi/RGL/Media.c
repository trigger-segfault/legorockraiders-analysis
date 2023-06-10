
#include "Standard.h"
#include "Textures.h"
#include "DirectX.h"
#include "Errors.h"
#include "Sound.h"
#include "Files.h"
#include "Lists.h"
#include "Media.h"

#pragma comment ( lib, "amstrmid" )

static IAMMultiMediaStream *__cdecl Media_OpenMMStream(LPUCHAR fname, BOOL noAudio);
static BOOL __cdecl Media_Setup(lpMedia media);

struct MediaGlobs {

	struct List *list;

} mediaGlobs = { 0 };

VOID Media_Initialise(VOID) {

	mediaGlobs.list = List_Create(sizeof(struct Media));
}

#ifdef _DEBUG
BOOL Media_Debug_ShutdownCallback(lpMedia media, LPVOID data) {

	Error_Fatal(TRUE, "Unremoved media");

	return FALSE;
}
#endif // _DEBUG

VOID Media_Shutdown(VOID) {

#ifdef _DEBUG
	List_RunThrough(mediaGlobs.list, Media_Debug_ShutdownCallback, NULL);
#endif // _DEBUG

}

lpMedia Media_Load(LPUCHAR fname, BOOL looping, BOOL noAudio) {

	ULONG r;
	lpMedia media = List_ObtainItem(mediaGlobs.list);

	if (media->stream = Media_OpenMMStream(File_GetActualPath(fname, FALSE), noAudio)) {
		if (Media_Setup(media)) {

			if (looping) media->flags |= MEDIA_FLAG_LOOPING;

			return media;
		}
		r = media->stream->lpVtbl->Release(media->stream);
	}

	List_ReturnItem(mediaGlobs.list, media);

	return NULL;
}

VOID Media_Remove(lpMedia media) {

	Error_Fatal(NULL == media, "NULL passed to Media_Remove()");

	Media_Close(media);

	List_ReturnItem(mediaGlobs.list, media);
}

VOID Media_SetDestinationTexture(lpMedia media, lpTexture texture) {

	media->destSurface = Texture_GetSurface(texture);
}

VOID Media_GetArea(lpMedia media, LPAREA2Di area) {

	area->x = media->originalRect.left;
	area->y = media->originalRect.top;
	area->width = media->originalRect.right - media->originalRect.left;
	area->height = media->originalRect.bottom - media->originalRect.top;
}

VOID Media_SetSourceArea(lpMedia media, LPAREA2Di area) {

	if (area) {

		media->srcRect.left = area->x;
		media->srcRect.top = area->y;
		media->srcRect.right = area->x + area->width;
		media->srcRect.bottom = area->y + area->height;

		media->flags |= MEDIA_FLAG_SRCRECT;

	} else media->flags &= ~MEDIA_FLAG_SRCRECT;
}

VOID Media_SetDestinationArea(lpMedia media, LPAREA2Di area) {

	if (area) {

		media->destRect.left = area->x;
		media->destRect.top = area->y;
		media->destRect.right = area->x + area->width;
		media->destRect.bottom = area->y + area->height;

		media->flags |= MEDIA_FLAG_DESTRECT;

	} else media->flags &= ~MEDIA_FLAG_DESTRECT;
}

BOOL Media_GetSourceArea(lpMedia media, LPAREA2Di area) {

	if (media->flags & MEDIA_FLAG_SRCRECT) {
	
		area->x = media->srcRect.left;
		area->y = media->srcRect.top;
		area->width = media->srcRect.right - media->srcRect.left;
		area->height = media->srcRect.bottom - media->srcRect.top;

		return TRUE;
	}

	return FALSE;
}

BOOL Media_GetDestinationArea(lpMedia media, LPAREA2Di area) {

	if (media->flags & MEDIA_FLAG_DESTRECT) {
	
		area->x = media->destRect.left;
		area->y = media->destRect.top;
		area->width = media->destRect.right - media->destRect.left;
		area->height = media->destRect.bottom - media->destRect.top;

		return TRUE;
	}

	return FALSE;
}

static IAMMultiMediaStream *Media_OpenMMStream(LPUCHAR fname, BOOL noAudio) {

	IAMMultiMediaStream *stream;
	HRESULT r;
	ULONG count;

	if (!Sound_IsInitialised()) noAudio = TRUE;

	if (SUCCEEDED(r = CoCreateInstance(&CLSID_AMMultiMediaStream, NULL, CLSCTX_INPROC_SERVER, &IID_IAMMultiMediaStream, &stream))) {
		if (SUCCEEDED(r = stream->lpVtbl->Initialize(stream, STREAMTYPE_READ, 0, NULL))) {
			if (SUCCEEDED(r = stream->lpVtbl->AddMediaStream(stream, (struct IUnknown *) DirectX_DirectDraw(), &MSPID_PrimaryVideo, 0, NULL))) {
				if (noAudio || SUCCEEDED(r = stream->lpVtbl->AddMediaStream(stream, NULL, &MSPID_PrimaryAudio, AMMSF_ADDDEFAULTRENDERER, NULL))) {

					WCHAR wPath[MAX_PATH];
					MultiByteToWideChar(CP_ACP, 0, fname, -1, wPath, sizeof(wPath) / sizeof(wPath[0]));

					if (S_OK == (stream->lpVtbl->OpenFile(stream, wPath, 0))) {

						return stream;
					}

				} else Error_DirectX(r, "AddMediaStream");
			} else Error_DirectX(r, "AddMediaStream");
		} else Error_DirectX(r, "Initialize");

		count = stream->lpVtbl->Release(stream);

	} else Error_DirectX(r, "CoCreateInstance");

	return NULL;
}

static BOOL Media_Setup(lpMedia media) {

    IMediaStream *primaryVidStream;
    IDirectDrawSurface *surface;

	HRESULT r;

	if (S_OK == (r = media->stream->lpVtbl->GetMediaStream(media->stream, &MSPID_PrimaryVideo, &primaryVidStream))) {
		if (S_OK == (r = primaryVidStream->lpVtbl->QueryInterface(primaryVidStream, &IID_IDirectDrawMediaStream, &media->ddStream))) {

			primaryVidStream->lpVtbl->Release(primaryVidStream);
			
			if (S_OK == (r = media->ddStream->lpVtbl->CreateSample(media->ddStream, NULL, NULL, 0, &media->sample))) {
				if (S_OK == (r = media->sample->lpVtbl->GetSurface(media->sample, &surface, &media->originalRect))) {
					if (DD_OK == (r = surface->lpVtbl->QueryInterface(surface, &IID_IDirectDrawSurface7, &media->surface))) {

						surface->lpVtbl->Release(surface);

						return TRUE;

					} else Error_DirectX(r, "QueryInterface");

					surface->lpVtbl->Release(surface);
					surface = NULL;

				} else Error_DirectX(r, "GetSurface");

				media->sample->lpVtbl->Release(media->sample);
				media->sample = NULL;

			} else Error_DirectX(r, "CreateSample");

			media->ddStream->lpVtbl->Release(media->ddStream);
			media->ddStream = NULL;

		} else Error_DirectX(r, "QueryInterface");

		primaryVidStream->lpVtbl->Release(primaryVidStream);

	} else Error_DirectX(r, "QueryInterface");

	return FALSE;
}

VOID Media_Close(lpMedia media) {

	ULONG r;

	r = media->surface->lpVtbl->Release(media->surface);
	r = media->sample->lpVtbl->Release(media->sample);
	r = media->ddStream->lpVtbl->Release(media->ddStream);
	r = media->stream->lpVtbl->Release(media->stream);
}

U64 Media_GetDuration(lpMedia media) {

	STREAM_TIME duration;

	media->stream->lpVtbl->GetDuration(media->stream, &duration);

	return duration;
}

U64 Media_GetTime(lpMedia media) {

	STREAM_TIME currTime;

	media->stream->lpVtbl->GetTime(media->stream, &currTime);

	return currTime;
}

VOID Media_SetTime(lpMedia media, U64 time) {

	media->stream->lpVtbl->Seek(media->stream, time);
}

BOOL Media_IsRunning(lpMedia media) {

	STREAM_STATE state;

	if (S_OK == media->stream->lpVtbl->GetState(media->stream, &state)) {
		return (STREAMSTATE_RUN == state);
	}

	return FALSE;
}

VOID Media_Run(lpMedia media, BOOL run) {

	media->stream->lpVtbl->SetState(media->stream, run?STREAMSTATE_RUN:STREAMSTATE_STOP);
}

static VOID Media_Blit(lpMedia media, LPDIRECTDRAWSURFACE7 surface) {

	RECT srcRect, destRect;
	HRESULT r;

	if (media->flags & MEDIA_FLAG_SRCRECT) srcRect = media->srcRect;
	else srcRect = media->originalRect;

	if (media->flags & MEDIA_FLAG_DESTRECT) destRect = media->destRect;
	else {

		DDSURFACEDESC2 desc;

		DirectX_InitStruct(&desc);
		surface->lpVtbl->GetSurfaceDesc(surface, &desc);

		destRect.top = 0;
		destRect.left = 0;
		destRect.right = desc.dwWidth;
		destRect.bottom = desc.dwHeight;
	}

	r = surface->lpVtbl->Blt(surface, &destRect, media->surface, &srcRect, DDBLT_WAIT, NULL);
	Error_DirectX(r, "Blt");
}

BOOL Media_Update(lpMedia media) {

	if (media) {

		STREAM_TIME duration, currTime;
		HRESULT r;

		// If the media is to be written directly to the back buffer, then perform a
		// synchronous update (block the update until the frame is ready to be rendered,
		// reducing the framerate of the game to that of the movie!).
		// If another surface is specified then the update will be asynchronous.

		if (media->destSurface) {

			if (media->flags & MEDIA_FLAG_DELAYUPDATE) {
				if (SUCCEEDED(r = media->sample->lpVtbl->CompletionStatus(media->sample, 0, 0))) {
					media->flags &= ~MEDIA_FLAG_DELAYUPDATE;
					Media_Blit(media, media->destSurface);
				}
			} else {
				if (SUCCEEDED(r = media->sample->lpVtbl->Update(media->sample, SSUPDATE_ASYNC, NULL, NULL, 0))) {
					Media_Blit(media, media->destSurface);
				} else {
					media->flags |= MEDIA_FLAG_DELAYUPDATE;
				}
			}


		} else {
			
			if (SUCCEEDED(r = media->sample->lpVtbl->Update(media->sample, 0, NULL, NULL, 0))) {
				Media_Blit(media, DirectX_BackSurf());
			}

		}

		media->stream->lpVtbl->GetDuration(media->stream, &duration);
		media->stream->lpVtbl->GetTime(media->stream, &currTime);

		if (currTime >= duration) {
			
			if (media->flags & MEDIA_FLAG_LOOPING) media->stream->lpVtbl->Seek(media->stream, 0);
			else return TRUE;

		}
	}

	return FALSE;
}
