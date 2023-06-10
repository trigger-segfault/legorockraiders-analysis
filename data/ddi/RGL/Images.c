
#include <ddraw.h>

#include "Standard.h"
#include "Textures.h"
#include "Surfaces.h"
#include "GfxFile.h"
#include "DirectX.h"
#include "Render.h"
#include "Errors.h"
#include "Lists.h"
#include "Files.h"
#include "Maths.h"
#include "DXT.h"
#include "Images.h"

struct ImageGlobs {

	struct List *list;
	struct List *sharedObjectList;

} imageGlobs = { 0 };

VOID Image_Initialise(VOID) {

	imageGlobs.list = List_Create(sizeof(struct Image));
	imageGlobs.sharedObjectList = File_CreateSharedObjectList();
}

#ifdef _DEBUG
BOOL Image_ShutdownCallback(lpImage image, LPVOID data) {

	Error_Warn(TRUE, "Unremoved image");

	return FALSE;
}
#endif // _DEBUG

VOID Image_Shutdown(VOID) {

#ifdef _DEBUG
	List_RunThrough(imageGlobs.list, Image_ShutdownCallback, NULL);
#endif // _DEBUG
	List_Remove(imageGlobs.list);
	imageGlobs.list = NULL;
	File_RemoveSharedObjectList(imageGlobs.sharedObjectList);
	imageGlobs.sharedObjectList = NULL;
}

lpList Image_GetSharedObjectList(VOID) {

	return imageGlobs.sharedObjectList;
}

lpImage Image_Grab(LPAREA2Di area) {

	lpImage image = List_ObtainItem(imageGlobs.list);
	DDSURFACEDESC2 desc;
	HRESULT r;

	DirectX_InitStruct(&desc);

	if (SUCCEEDED(r = DirectX_BackSurf()->lpVtbl->GetSurfaceDesc(DirectX_BackSurf(), &desc))) {

		desc.dwFlags |= DDSD_CAPS;
		desc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;

		if (area) {
			desc.dwWidth = (ULONG) area->width;
			desc.dwHeight = (ULONG) area->height;
		}

		if (SUCCEEDED(r = DirectX_DirectDraw()->lpVtbl->CreateSurface(DirectX_DirectDraw(), &desc, &image->surface, NULL))) {

			RECT srcRect;

			if (area) {
				srcRect.left = area->x;
				srcRect.top = area->y;
				srcRect.right = area->x + area->width;
				srcRect.bottom = area->y + area->height;
			}

			r = image->surface->lpVtbl->Blt(image->surface, NULL, DirectX_BackSurf(), area?&srcRect:NULL, DDBLT_WAIT, NULL);
			Error_DirectX(r, "Blt");

			image->type = ImageType_Surface;

			return image;

		} else Error_DirectX(r, "CreateSurface");
	} else Error_DirectX(r, "GetSurfaceDesc");

	List_ReturnItem(imageGlobs.list, image);

	return NULL;
}

VOID Image_SetRenderFlags(lpImage image, UWORD renderFlags, BOOL set) {

	Error_Fatal(ImageType_Texture != image->type, "Image is not a texture image");

	if (set) image->renderFlags |= renderFlags;
	else image->renderFlags &= ~renderFlags;
}

lpImage Image_Load(LPUCHAR fname, BOOL textureMode, BOOL useShared) {

	lpImage image = NULL;

//	if (useShared && (image = File_FindSharedObject(fname, FileObjectType_Image))) {
	if (useShared && (image = File_FindSharedObject(imageGlobs.sharedObjectList, fname))) {
		if ((textureMode && image->type != ImageType_Texture) ||
			(!textureMode && image->type == ImageType_Texture)) {

			image = NULL;
		}
	}

	if (NULL == image) {

		if (textureMode) {

			lpTexture texture;
			
			if (texture = Texture_Load(fname, useShared)) {
				image = List_ObtainItem(imageGlobs.list);
				image->texture = texture;
				image->type = ImageType_Texture;
				image->alphaLevel = 1.0f;
			}

		} else {

			LPDIRECTDRAWSURFACE7 surface;

//			if (surface = DXT_LoadImage(fname)) {
//				image = List_ObtainItem(imageGlobs.list);
//				image->surface = surface;
//				image->type = ImageType_Surface;
//			}

			if (surface = GfxFile_LoadSurface(fname, useShared)) {
				image = List_ObtainItem(imageGlobs.list);
				image->surface = surface;
				image->type = ImageType_Surface;
			}
		}

//		if (image && useShared) File_RegisterSharedObject(fname, image, FileObjectType_Image);
		if (image && useShared) File_RegisterSharedObject(imageGlobs.sharedObjectList, fname, image);
	}

	return image;
}

VOID Image_Remove(lpImage image) {

	if (File_ReleaseSharedObject(imageGlobs.sharedObjectList, image)) {
		
		if (ImageType_Surface == image->type) Surface_Remove(image->surface);
		else if (ImageType_Texture == image->type) Texture_Remove(image->texture);

		List_ReturnItem(imageGlobs.list, image);
	}
}

VOID Image_SetColourKey(lpImage image, COLOUR colour) {

	// Set the colour key of the specified image assuming that
	// the pixel format is the same as that of the back surface.

	DDCOLORKEY key;

	key.dwColorSpaceLowValue = key.dwColorSpaceHighValue = DirectX_ColourMatchPacked(colour);

	image->surface->lpVtbl->SetColorKey(image->surface, DDCKEY_SRCBLT, &key);
	image->flags |= IMAGE_FLAG_COLOURKEYED;
}

VOID Image_GetSize(lpImage image, LPULONG width, LPULONG height) {

	DDSURFACEDESC2 desc;
	HRESULT r;

	switch (image->type)
	{
	case	ImageType_Surface	:	DirectX_InitStruct(&desc);
									r = image->surface->lpVtbl->GetSurfaceDesc(image->surface, &desc);
									Error_DirectX(r, "GetSurfaceDesc");
									if (width) *width = desc.dwWidth;
									if (height) *height = desc.dwHeight;
									break;

	case	ImageType_Texture	:	if (width) *width = Texture_GetWidth(image->texture);
									if (height) *height = Texture_GetHeight(image->texture);
									break;

	}
}

VOID Image_SetAlphaLevel(lpImage image, REAL level) {

	image->alphaLevel = max(0.0f, level);
	image->alphaLevel = min(image->alphaLevel, 1.0f);
}

VOID Image_DisplayArea(lpImage image, LPAREA2Dr srcArea, LPAREA2Dr destArea) {

	if (image->type == ImageType_Texture) {

		D3DVIEWPORT7 viewport;
		struct LocalVertex { VECTOR4D position; COLOUR colour; VECTOR2D uv; } vertexList[4];
		COLOUR colour = COLOUR_FROMREAL(image->alphaLevel, image->alphaLevel, image->alphaLevel);
		HRESULT r;

		if (destArea) {

			vertexList[0].position.x = destArea->x;
			vertexList[0].position.y = destArea->y;
			vertexList[1].position.x = destArea->x + destArea->width;
			vertexList[1].position.y = destArea->y;
			vertexList[2].position.x = destArea->x + destArea->width;
			vertexList[2].position.y = destArea->y + destArea->height;
			vertexList[3].position.x = destArea->x;
			vertexList[3].position.y = destArea->y + destArea->height;

		} else {

			vertexList[0].position.x = 0.0f;
			vertexList[0].position.y = 0.0f;
			vertexList[1].position.x = (REAL) DirectX_GetWidth();
			vertexList[1].position.y = 0.0f;
			vertexList[2].position.x = (REAL) DirectX_GetWidth();
			vertexList[2].position.y = (REAL) DirectX_GetHeight();
			vertexList[3].position.x = 0.0f;
			vertexList[3].position.y = (REAL) DirectX_GetHeight();

		}

		if (srcArea) {

			vertexList[0].uv.x = srcArea->x / Image_GetWidth(image);
			vertexList[0].uv.y = srcArea->y / Image_GetHeight(image);
			vertexList[1].uv.x = (srcArea->x + srcArea->width) / Image_GetWidth(image);
			vertexList[1].uv.y = srcArea->y / Image_GetHeight(image);
			vertexList[2].uv.x = (srcArea->x + srcArea->width) / Image_GetWidth(image);
			vertexList[2].uv.y = (srcArea->y + srcArea->height) / Image_GetHeight(image);
			vertexList[3].uv.x = srcArea->x / Image_GetWidth(image);
			vertexList[3].uv.y = (srcArea->y + srcArea->height) / Image_GetHeight(image);

		} else {

			vertexList[0].uv.x = 0.0f;
			vertexList[0].uv.y = 0.0f;
			vertexList[1].uv.x = 1.0f;
			vertexList[1].uv.y = 0.0f;
			vertexList[2].uv.x = 1.0f;
			vertexList[2].uv.y = 1.0f;
			vertexList[3].uv.x = 0.0f;
			vertexList[3].uv.y = 1.0f;
		
		}

		vertexList[0].position.z = 0.0f;
		vertexList[0].position.w = 1.0f;
		vertexList[0].colour = colour;
		vertexList[1].position.z = 0.0f;
		vertexList[1].position.w = 1.0f;
		vertexList[1].colour = colour;
		vertexList[2].position.z = 0.0f;
		vertexList[2].position.w = 1.0f;
		vertexList[2].colour = colour;
		vertexList[3].position.z = 0.0f;
		vertexList[3].position.w = 1.0f;
		vertexList[3].colour = colour;

		viewport.dwX = 0;
		viewport.dwY = 0;
		viewport.dwWidth = DirectX_GetWidth();
		viewport.dwHeight = DirectX_GetHeight();
		viewport.dvMinZ = 0.0f;
		viewport.dvMaxZ = 1.0f;

		DirectX_Device()->lpVtbl->SetViewport(DirectX_Device(), &viewport);

		Render_BeginScene();

		Render_SetupAlphaStates(image->renderFlags);
		Render_SetState(D3DRENDERSTATE_LIGHTING, FALSE);
		
		Texture_Set(image->texture, 0);

		r = DirectX_Device()->lpVtbl->DrawPrimitive(DirectX_Device(), D3DPT_TRIANGLEFAN, D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1, vertexList, 4, 0);
		Error_DirectX(r, "DrawPrimitive");

		Render_EndScene();

	} else if (image->type == ImageType_Surface) {

		RECT srcRect, destRect;
		HRESULT r;

		if (srcArea) {

			if (srcArea->width < 1.0f || srcArea->height < 1.0f) return;

			srcRect.left = (SLONG) srcArea->x;
			srcRect.top = (SLONG) srcArea->y;
			srcRect.right = (SLONG) (srcArea->x + srcArea->width);
			srcRect.bottom = (SLONG) (srcArea->y + srcArea->height);


		} else {

			ULONG width, height;

			Image_GetSize(image, &width, &height);

			srcRect.left = 0;
			srcRect.top = 0;
			srcRect.right = width;
			srcRect.bottom = height;
		}

		if (destArea) {

			if (destArea->width < 1.0f && destArea->height < 1.0f) return;
		
			destRect.left = (SLONG) destArea->x;
			destRect.top = (SLONG) destArea->y;
			destRect.right = (SLONG) (destArea->x + destArea->width);
			destRect.bottom = (SLONG) (destArea->y + destArea->height);

		} else {
		
			destRect.left = 0;
			destRect.top = 0;
			destRect.right = DirectX_GetWidth();
			destRect.bottom = DirectX_GetHeight();

		}

		if (image->flags & IMAGE_FLAG_COLOURKEYED) r = DirectX_BackSurf()->lpVtbl->Blt(DirectX_BackSurf(), &destRect, image->surface, &srcRect, DDBLT_WAIT|DDBLT_KEYSRC, NULL);
		else r = DirectX_BackSurf()->lpVtbl->Blt(DirectX_BackSurf(), &destRect, image->surface, &srcRect, DDBLT_WAIT, NULL);

/*		{
			DDBLTFX bltFX;

			DirectX_InitStruct(&bltFX);
			bltFX.ddckSrcColorkey.dwColorSpaceLowValue = 0;
			bltFX.ddckSrcColorkey.dwColorSpaceHighValue = 0;

			r = DirectX_BackSurf()->lpVtbl->Blt(DirectX_BackSurf(), &destRect, image->surface, &srcRect, DDBLT_WAIT|DDBLT_KEYSRCOVERRIDE, &bltFX);
		}
*/
		Error_DirectX(r, "Blt");
	}
}

__inline VOID Image_Display(lpImage image, ULONG x, ULONG y) {

	AREA2Dr srcArea, destArea;
	ULONG width, height;

	Image_GetSize(image, &width, &height);

	srcArea.x = 0;
	srcArea.y = 0;
	srcArea.width = (REAL) width;
	srcArea.height = (REAL) height;

	destArea.x = (REAL) x;
	destArea.y = (REAL) y;
	destArea.width = (REAL) (width);
	destArea.height = (REAL) (height);


	Image_DisplayArea(image, &srcArea, &destArea);
}

ULONG Image_GetWidth(lpImage image) {

	DDSURFACEDESC2 desc;
	HRESULT r;

	switch (image->type)
	{
	case	ImageType_Surface	:	DirectX_InitStruct(&desc);
									r = image->surface->lpVtbl->GetSurfaceDesc(image->surface, &desc);
									Error_DirectX(r, "GetSurfaceDesc");
									return desc.dwWidth;
									break;

	case	ImageType_Texture	:	return Texture_GetWidth(image->texture);
									break;

	}

return 0;
}

ULONG Image_GetHeight(lpImage image) {

	DDSURFACEDESC2 desc;
	HRESULT r;

	switch (image->type)
	{
	case	ImageType_Surface	:	DirectX_InitStruct(&desc);
									r = image->surface->lpVtbl->GetSurfaceDesc(image->surface, &desc);
									Error_DirectX(r, "GetSurfaceDesc");
									return desc.dwHeight;
									break;

	case	ImageType_Texture	:	return Texture_GetHeight(image->texture);
									break;

	}

return 0;

}

