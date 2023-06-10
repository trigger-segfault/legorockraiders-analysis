
#ifndef _RGL_IMAGES_H_
#define _RGL_IMAGES_H_

#ifdef _RGL

#include <ddraw.h>

#define IMAGE_FLAG_COLOURKEYED			0x0001

enum ImageType {

	ImageType_Surface,
	ImageType_Texture,
};

struct Image {

	enum ImageType type;

	union {
		LPDIRECTDRAWSURFACE7 surface;
		struct Texture *texture;
	};

	REAL alphaLevel;

	UWORD flags, renderFlags;
};

#endif // _RGL

typedef struct Image			*lpImage;

// Auto Prototypes
extern unsigned __int64 __stdcall Int64ShllMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern __int64 __stdcall Int64ShraMod32(__int64 Value,unsigned long ShiftCount);
extern unsigned __int64 __stdcall Int64ShrlMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern void *__cdecl GetFiberData(void );
extern void *__cdecl GetCurrentFiber(void );
extern void __cdecl Image_Initialise(void );
extern VOID __cdecl Image_SetRenderFlags(lpImage image, UWORD renderFlags, BOOL set);
extern struct Image *__cdecl Image_Load(unsigned char *fname, int texture, int useShared);
extern struct Image *__cdecl Image_Grab(LPAREA2Di area);
extern VOID __cdecl Image_SetColourKey(lpImage image, COLOUR colour);
extern void __cdecl Image_GetSize(struct Image *image,unsigned long *width,unsigned long *height);
extern VOID __cdecl Image_SetAlphaLevel(lpImage image, REAL level);
extern VOID __cdecl Image_DisplayArea(lpImage image, LPAREA2Dr srcArea, LPAREA2Dr destArea);
extern void __cdecl Image_Display(struct Image *image,unsigned long x,unsigned long y);
extern struct List *__cdecl Image_GetSharedObjectList(void);
extern void __cdecl Image_Remove(struct Image *image);
extern ULONG __cdecl Image_GetWidth(lpImage image);
extern ULONG __cdecl Image_GetHeight(lpImage image);
extern VOID __cdecl Image_Shutdown(VOID);
// Auto Prototypes

#endif // !_RGL_IMAGES_H_
