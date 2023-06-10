
#include <ddraw.h>

#include "Standard.h"
#include "Errors.h"
#include "GfxFile.h"
#include "Textures.h"
#include "DirectX.h"
#include "Render.h"
#include "Maths.h"
#include "Files.h"
#include "Utils.h"
#include "Lists.h"
#include "Mem.h"

struct Texture {

	union {
		struct IDirectDrawSurface7 *surface;
		struct IDirectDrawSurface7 **surfaceList;
	};

	REAL animTime;
	ULONG appData;
	UWORD flags;
	SWORD priority;

#ifdef _DEBUG
	LPUCHAR name;
#endif // _DEBUG
};

struct TextureGlobs {

	struct List *list;
	struct List *sharedObjectList;

	VOID (*preLoadCallback)(LPUCHAR fname, LPULONG colourKey, LPBOOL useColourKey, LPULONG depth, LPVOID data);
	LPVOID preLoadCallbackData;
	VOID (*postLoadCallback)(LPUCHAR fname, lpTexture texture, LPVOID data);
	LPVOID postLoadCallbackData;

	enum TextureFilterType defaultMinFilter;
	enum TextureFilterType defaultMagFilter;
	enum TextureFilterType defaultMipFilter;

} textureGlobs = { 0 };

lpList Texture_GetSharedObjectList(VOID) {

	return textureGlobs.sharedObjectList;
}

VOID Texture_Initialise(VOID) {

	textureGlobs.list = List_Create(sizeof(struct Texture));
	textureGlobs.sharedObjectList = File_CreateSharedObjectList();

	textureGlobs.defaultMinFilter = TextureFilterType_Point;
	textureGlobs.defaultMagFilter = TextureFilterType_Point;
}

#ifdef _DEBUG
BOOL Texture_ShutdownCallback(lpTexture texture, LPVOID data) {

	Error_Warn(TRUE, Error_Format("Unremoved texture named \"%s\"", texture->name));

	return FALSE;
}
#endif // _DEBUG

VOID Texture_Shutdown(VOID) {

#ifdef _DEBUG
	List_RunThrough(textureGlobs.list, Texture_ShutdownCallback, NULL);
#endif // _DEBUG
	List_Remove(textureGlobs.list);
	textureGlobs.list = NULL;
	File_RemoveSharedObjectList(textureGlobs.sharedObjectList);
	textureGlobs.sharedObjectList = NULL;
}

VOID Texture_SetDefaultFilterMode(enum TextureFilterType defaultMinFilter, enum TextureFilterType defaultMagFilter, enum TextureFilterType defaultMipFilter) {

	textureGlobs.defaultMinFilter = defaultMinFilter;
	textureGlobs.defaultMagFilter = defaultMagFilter;
	textureGlobs.defaultMipFilter = defaultMipFilter;
}

VOID Texture_SetPreLoadCallback(VOID (*Callback)(LPUCHAR fname, LPULONG colourKey, LPBOOL useColourKey, LPULONG depth, LPVOID data), LPVOID data) {

	textureGlobs.preLoadCallback = Callback;
	textureGlobs.preLoadCallbackData = data;
}

VOID Texture_SetPostLoadCallback(VOID (*Callback)(LPUCHAR fname, lpTexture texture, LPVOID data), LPVOID data) {

	textureGlobs.postLoadCallback = Callback;
	textureGlobs.postLoadCallbackData = data;
}

VOID Texture_SetAppData(lpTexture texture, ULONG data) {

	List_CheckItem(textureGlobs.list, texture);

	texture->appData = data;
}

VOID Texture_SetPriority(lpTexture texture, SWORD priority) {

	List_CheckItem(textureGlobs.list, texture);

	texture->priority = priority;
}

__inline SWORD Texture_GetPriority(lpTexture texture) {

	List_CheckItem(textureGlobs.list, texture);

	return texture->priority;
}

/*
VOID Texture_SetFilterMode(lpTexture texture, BOOL mag, enum TextureFilterType mode) {

	ULONG type;

	switch (mode) {
	case TextureFilterType_Point:			type = (mag?D3DTFG_POINT:D3DTFN_POINT);					break;
	case TextureFilterType_Linear:			type = (mag?D3DTFG_LINEAR:D3DTFN_LINEAR);				break;
	case TextureFilterType_FlatCubic:		type = (mag?D3DTFG_FLATCUBIC:-1);						break;
	case TextureFilterType_GaussianCubic:	type = (mag?D3DTFG_GAUSSIANCUBIC:-1);					break;
	case TextureFilterType_Anisotropic:		type = (mag?D3DTFG_ANISOTROPIC:D3DTFN_ANISOTROPIC);		break;
	default:
		Error_Fatal(TRUE, "Invalid emumeration");
		type = D3DTFG_POINT;
		break;
	}

	if (-1 == type) {
		Error_Fatal(TRUE, Error_Format("Unsupported filter mode (%d) for texture %s", type, mag?"magnification":"minification"));
		type = D3DTFG_POINT;
	}

	if (mag) {
		type <<= TEXTURE_MINMASKBITS;
		texture->flags &= ~TEXTURE_FLAG_MAGMASK;
	} else {
		texture->flags &= ~TEXTURE_FLAG_MINMASK;
	}

	texture->flags |= type;
}
*/

VOID Texture_SetFilterMode(lpTexture texture, enum TextureFilterType minMode, enum TextureFilterType magMode, enum TextureFilterType mipMode) {

	ULONG minFilter, magFilter, mipFilter;

	List_CheckItem(textureGlobs.list, texture);

	switch (minMode) {
	case TextureFilterType_Point:			minFilter = D3DTFN_POINT;			break;
	case TextureFilterType_Linear:			minFilter = D3DTFN_LINEAR;			break;
	case TextureFilterType_Anisotropic:		minFilter = D3DTFN_ANISOTROPIC;		break;
	default:
		Error_Fatal(TRUE, Error_Format("Unsupported filter mode (%d) for texture minification"));
		minFilter = D3DTFN_POINT;
		break;
	}

	switch (magMode) {
	case TextureFilterType_Point:			magFilter = D3DTFG_POINT;			break;
	case TextureFilterType_Linear:			magFilter = D3DTFG_LINEAR;			break;
	case TextureFilterType_FlatCubic:		magFilter = D3DTFG_FLATCUBIC;		break;
	case TextureFilterType_GaussianCubic:	magFilter = D3DTFG_GAUSSIANCUBIC;	break;
	case TextureFilterType_Anisotropic:		magFilter = D3DTFG_ANISOTROPIC;		break;
	default:
		Error_Fatal(TRUE, Error_Format("Unsupported filter mode (%d) for texture minification"));
		magFilter = D3DTFG_POINT;
		break;
	}

	switch (mipMode) {
	case TextureFilterType_None:			mipFilter = D3DTFP_NONE;			break;
	case TextureFilterType_Point:			mipFilter = D3DTFP_POINT;			break;
	case TextureFilterType_Linear:			mipFilter = D3DTFP_LINEAR;			break;
	default:
		Error_Fatal(TRUE, Error_Format("Unsupported filter mode (%d) for texture minification"));
		mipFilter = D3DTFP_NONE;
		break;
	}

	texture->flags &= ~(TEXTURE_FLAG_MINMASK | TEXTURE_FLAG_MAGMASK | TEXTURE_FLAG_MIPMASK);
	texture->flags |= minFilter;
	texture->flags |= magFilter << TEXTURE_MINMASKBITS;
	texture->flags |= mipFilter << (TEXTURE_MINMASKBITS + TEXTURE_MAGMASKBITS);
}

__inline enum _D3DTEXTUREMINFILTER Texture_GetMinFilter(lpTexture texture) {

	List_CheckItem(textureGlobs.list, texture);

	return (texture->flags & TEXTURE_FLAG_MINMASK);
}

__inline enum _D3DTEXTUREMAGFILTER Texture_GetMagFilter(lpTexture texture) {

	List_CheckItem(textureGlobs.list, texture);

	return (texture->flags & TEXTURE_FLAG_MAGMASK) >> TEXTURE_MINMASKBITS;
}

__inline enum _D3DTEXTUREMIPFILTER Texture_GetMipFilter(lpTexture texture) {

	List_CheckItem(textureGlobs.list, texture);

	return (texture->flags & TEXTURE_FLAG_MIPMASK) >> (TEXTURE_MINMASKBITS + TEXTURE_MAGMASKBITS);
}

__inline VOID Texture_SetFlags(lpTexture texture, ULONG flags) {

	List_CheckItem(textureGlobs.list, texture);

	Error_Fatal((flags & TEXTURE_FLAG_MINMASK) || (flags & TEXTURE_FLAG_MAGMASK), "Invalid flags");

	texture->flags |= flags;
}

__inline VOID Texture_UnsetFlags(lpTexture texture, ULONG flags) {

	List_CheckItem(textureGlobs.list, texture);

	Error_Fatal((flags & TEXTURE_FLAG_MINMASK) || (flags & TEXTURE_FLAG_MAGMASK), "Invalid flags");

	texture->flags &= ~flags;
}

__inline BOOL Texture_AllFlagsSet(lpTexture texture, ULONG flags) {

	ULONG testFlags = texture->flags & ~(TEXTURE_FLAG_MINMASK|TEXTURE_FLAG_MAGMASK);

	List_CheckItem(textureGlobs.list, texture);

	Error_Fatal((flags & TEXTURE_FLAG_MINMASK) || (flags & TEXTURE_FLAG_MAGMASK), "Invalid flags");

	return ((testFlags & flags) == flags);
}

__inline BOOL Texture_AnyFlagsSet(lpTexture texture, ULONG flags) {

	List_CheckItem(textureGlobs.list, texture);

	Error_Fatal((flags & TEXTURE_FLAG_MINMASK) || (flags & TEXTURE_FLAG_MAGMASK), "Invalid flags");

	return (texture->flags & flags)?TRUE:FALSE;
}

ULONG Texture_GetAppData(lpTexture texture) {

	List_CheckItem(textureGlobs.list, texture);

	return texture->appData;
}

ULONG Texture_GetWidth(lpTexture texture) {

	DDSURFACEDESC2 desc;
	LPDIRECTDRAWSURFACE7 surface;

	List_CheckItem(textureGlobs.list, texture);

	DirectX_InitStruct(&desc);

	surface = Texture_GetSurface(texture);
	surface->lpVtbl->GetSurfaceDesc(surface, &desc);

	return desc.dwWidth;
}

ULONG Texture_GetHeight(lpTexture texture) {

	DDSURFACEDESC2 desc;
	LPDIRECTDRAWSURFACE7 surface;

	List_CheckItem(textureGlobs.list, texture);

	DirectX_InitStruct(&desc);

	surface = Texture_GetSurface(texture);
	surface->lpVtbl->GetSurfaceDesc(surface, &desc);

	return desc.dwHeight;
}

__inline REAL Texture_GetTime(lpTexture texture) {

	return texture->animTime;
}

VOID Texture_SetTime(lpTexture texture, REAL time) {

	if (texture->flags & TEXTURE_FLAG_ANIMATED) {

		time = max(0.0f, time);

		if (time > texture->animTime) {

			ULONG loop;
			ULONG start = (ULONG) texture->animTime;
			ULONG end = (ULONG) time + 1;

			for (loop=start ; loop<end ; loop++) {
				if (NULL == texture->surfaceList[loop]) {
					break;
				}
			}

			if (loop < end) {
			
				texture->animTime = Maths_Mod(time, (REAL) loop);
				return;

			}
		}
		
		texture->animTime = time;
	}
}

__inline LPDIRECTDRAWSURFACE7 Texture_GetSurface(lpTexture texture) {

	if (texture->flags & TEXTURE_FLAG_ANIMATED) {

		return texture->surfaceList[(ULONG) texture->animTime];

	} else return texture->surface;
}

__inline VOID Texture_Set(lpTexture texture, ULONG index) {

	if (texture) Render_SetTexture(index, texture->surface);
	else Render_SetTexture(index, NULL);
}

BOOL Texture_Remove(lpTexture texture) {

	ULONG index, count;

	List_CheckItem(textureGlobs.list, texture);

	if (File_ReleaseSharedObject(textureGlobs.sharedObjectList, texture)) {

		Render_ResetTextures();

		if (texture->flags & TEXTURE_FLAG_ANIMATED) {

			for (index=0 ; texture->surfaceList[index] ; index++) {
				count = texture->surfaceList[index]->lpVtbl->Release(texture->surfaceList[index]);
				Error_Fatal(count, Error_Format("Texture surface was not removed, %d references left", count));
			}

		} else {
			
			count = texture->surface->lpVtbl->Release(texture->surface);
			Error_Fatal(count, Error_Format("Texture surface was not removed, %d references left", count));

		}

#ifdef _DEBUG
		Mem_Free(texture->name);
#endif // _DEBUG

		List_ReturnItem(textureGlobs.list, texture);

		return TRUE;
	}

	return FALSE;
}

lpTexture Texture_Load(LPUCHAR fname, BOOL useShared) {

	ULONG colourKey, depth = 16;
	BOOL useKey = FALSE;
	lpTexture texture = NULL;
	LPDIRECTDRAWSURFACE7 surf;
	UCHAR buffer[FILE_MAXPATH], path[FILE_MAXPATH];
	LPUCHAR s, t = NULL, dir, argv[TEXTURE_MAXANIMFRAMES];
	ULONG loop, argc, count = 0;

	if (fname) {

		if (useShared) texture = File_FindSharedObject(textureGlobs.sharedObjectList, fname);

		if (NULL == texture) {

			if (textureGlobs.preLoadCallback) {
				textureGlobs.preLoadCallback(fname, &colourKey, &useKey, &depth, textureGlobs.preLoadCallbackData);
			}

			sprintf(buffer, "%s", fname);
			argc = Util_Tokenise(buffer, argv, sizeof(argv) / sizeof(argv[0]), ";", TRUE);
			for (s=argv[0] ; '\0'!=*s ; s++) if ('\\' == *s) t = s;
			if (t) {
			
				dir = argv[0];
				*t = '\0';
				argv[0] = t + 1;

			} else dir = NULL;

			texture = List_ObtainItem(textureGlobs.list);

			if (argc > 1) {
				texture->surfaceList = Mem_AllocClear(sizeof(texture->surfaceList[0]) * (argc + 1));
				texture->flags |= TEXTURE_FLAG_ANIMATED;
			}

			for (loop=0 ; loop<argc ; loop++) {

				if (dir) sprintf(path, "%s\\%s", dir, argv[loop]);
				else sprintf(path, "%s", argv[loop]);

				if (surf = GfxFile_LoadTextureSurface(path, useShared, depth, useKey?&colourKey:NULL)) {

					count++;

					if (texture->flags & TEXTURE_FLAG_ANIMATED) texture->surfaceList[loop] = surf;
					else texture->surface = surf;

				}
			}

			if (count) {

				if (useKey) texture->flags |= TEXTURE_FLAG_COLOURKEYED;
				if (useShared) File_RegisterSharedObject(textureGlobs.sharedObjectList, fname, texture);

				Texture_SetFilterMode(texture, textureGlobs.defaultMinFilter, textureGlobs.defaultMagFilter, textureGlobs.defaultMipFilter);
#ifdef _DEBUG
				texture->name = Mem_CopyString(fname);
#endif // _DEBUG

				if (textureGlobs.postLoadCallback) textureGlobs.postLoadCallback(fname, texture, textureGlobs.postLoadCallbackData);
	
			} else {

				if (texture->flags & TEXTURE_FLAG_ANIMATED) Mem_Free(texture->surfaceList);
				List_ReturnItem(textureGlobs.list, texture);
				texture = NULL;

			}
		}

		Error_Warn(NULL == texture, Error_Format("Cannot load Texture file %s", fname));

	} else Error_Fatal(TRUE, "NULL passed as texture file name");

	return texture;
}