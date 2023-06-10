
#ifndef _RGL_TEXTURES_H_
#define _RGL_TEXTURES_H_

#define TEXTURE_MAXANIMFRAMES			100

#define TEXTURE_MINMASKBITS				3
#define TEXTURE_MAGMASKBITS				3

#define TEXTURE_FLAG_MINMASK			0x0007
#define TEXTURE_FLAG_MAGMASK			0x0038
#define TEXTURE_FLAG_MIPMASK			0x01c0
#define TEXTURE_FLAG_COLOURKEYED		0x0200
#define TEXTURE_FLAG_ANIMATED			0x0400

enum TextureFilterType {

	TextureFilterType_None,
	TextureFilterType_Point,
	TextureFilterType_Linear,
	TextureFilterType_FlatCubic,
	TextureFilterType_GaussianCubic,
	TextureFilterType_Anisotropic,

};

typedef struct Texture				*lpTexture;

#ifdef _RGL
extern enum _D3DTEXTUREMINFILTER __cdecl Texture_GetMinFilter(lpTexture texture);
extern enum _D3DTEXTUREMAGFILTER __cdecl Texture_GetMagFilter(lpTexture texture);
extern enum _D3DTEXTUREMIPFILTER __cdecl Texture_GetMipFilter(lpTexture texture);
extern struct IDirectDrawSurface7 *__cdecl Texture_GetSurface(lpTexture texture);
#endif // _RGL

// Auto Prototypes
extern VOID __cdecl Texture_Initialise(VOID);
extern VOID __cdecl Texture_SetDefaultFilterMode(enum TextureFilterType defaultMinFilter, enum TextureFilterType defaultMagFilter, enum TextureFilterType defaultMipFilter);
extern VOID __cdecl Texture_SetPreLoadCallback(VOID (*Callback)(LPUCHAR fname, LPULONG colourKey, LPBOOL useColourKey, LPULONG depth, LPVOID data), LPVOID data);
extern VOID __cdecl Texture_SetPostLoadCallback(VOID (*Callback)(LPUCHAR fname, lpTexture texture, LPVOID data), LPVOID data);
extern VOID __cdecl Texture_SetAppData(lpTexture texture, ULONG data);
extern VOID __cdecl Texture_SetFilterMode(lpTexture texture, enum TextureFilterType minMode, enum TextureFilterType magMode, enum TextureFilterType mipMode);
extern VOID __cdecl Texture_SetFlags(lpTexture texture, ULONG flags);
extern VOID __cdecl Texture_UnsetFlags(lpTexture texture, ULONG flags);
extern BOOL __cdecl Texture_AllFlagsSet(lpTexture texture, ULONG flags);
extern BOOL __cdecl Texture_AnyFlagsSet(lpTexture texture, ULONG flags);
extern ULONG __cdecl Texture_GetAppData(lpTexture texture);
extern ULONG __cdecl Texture_GetWidth(lpTexture texture);
extern ULONG __cdecl Texture_GetHeight(lpTexture texture);
extern lpTexture __cdecl Texture_Load(LPUCHAR fname, BOOL useShared);
extern VOID __cdecl Texture_SetPriority(lpTexture texture, SWORD priority);
extern SWORD __cdecl Texture_GetPriority(lpTexture texture);
extern struct List *__cdecl Texture_GetSharedObjectList(void );
extern int __cdecl Texture_Remove(struct Texture *texture);
extern VOID __cdecl Texture_Shutdown(VOID);
extern VOID __cdecl Texture_Set(struct Texture *texture, unsigned long index);
extern VOID __cdecl Texture_SetTime(lpTexture texture, REAL time);
extern REAL __cdecl Texture_GetTime(lpTexture texture);
// Auto Prototypes

#endif // !_RGL_TEXTURES_H_
