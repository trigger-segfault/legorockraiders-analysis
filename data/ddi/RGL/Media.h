
#ifndef _RGL_MEDIA_H
#define _RGL_MEDIA_H

#ifdef _RGL

#include <mmstream.h>
#include <amstream.h>
#include <ddstream.h>

#define MEDIA_FLAG_LOOPING			0x00000001
#define MEDIA_FLAG_DESTRECT			0x00000002
#define MEDIA_FLAG_SRCRECT			0x00000004
#define MEDIA_FLAG_DELAYUPDATE		0x00000008

struct Media {

    IAMMultiMediaStream *stream;
	IDirectDrawMediaStream *ddStream;
    IDirectDrawSurface7 *surface;
    IDirectDrawStreamSample *sample;
	RECT originalRect, srcRect, destRect;
	LPDIRECTDRAWSURFACE7 destSurface;

	ULONG flags;
};
#endif // _RGL

typedef struct Media			*lpMedia;

extern VOID __cdecl Media_Initialise(VOID);
extern lpMedia __cdecl Media_Load(LPUCHAR fname, BOOL looping, BOOL noAudio);
extern VOID __cdecl Media_Remove(lpMedia media);
extern VOID __cdecl Media_GetArea(lpMedia media, LPAREA2Di area);
extern VOID __cdecl Media_SetDestinationTexture(lpMedia media, lpTexture texture);
extern VOID __cdecl Media_SetSourceArea(lpMedia media, LPAREA2Di area);
extern VOID __cdecl Media_SetDestinationArea(lpMedia media, LPAREA2Di area);
extern BOOL __cdecl Media_GetSourceArea(lpMedia media, LPAREA2Di area);
extern BOOL __cdecl Media_GetDestinationArea(lpMedia media, LPAREA2Di area);
extern VOID __cdecl Media_Close(lpMedia media);
extern BOOL __cdecl Media_Update(lpMedia media);
extern U64 __cdecl Media_GetDuration(lpMedia media);
extern U64 __cdecl Media_GetTime(lpMedia media);
extern VOID __cdecl Media_SetTime(lpMedia media, U64 time);
extern VOID __cdecl Media_Run(lpMedia media, BOOL start);
extern BOOL __cdecl Media_IsRunning(lpMedia media);

#endif // _RGL_MEDIA_H
