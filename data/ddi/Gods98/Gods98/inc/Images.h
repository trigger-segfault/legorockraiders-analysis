
#ifndef _GODS98_IMAGES_H_
#define _GODS98_IMAGES_H_

#ifdef _GODS98COMPILE
#include <ddraw.h>
#include <d3d.h>
#endif // _GODS98COMPILE
#include "Standard.h"

/**********************************************************************************
 **
 ** Image.h: Image Object Header for GODS
 **
 ** Copyright (C) Data Design Interactive.
 **
 **
 ** Written by Robert Wilson 20/01/98
 **
 **********************************************************************************/

/**********************************************************************************
 ******** Image Defaults and Enumeration
 **********************************************************************************/

#define IMAGE_MAXLISTS			32			// 2^32 - 1 possible images...

#define IMAGE_FLAG_INITIALISED	0x00000001
#define IMAGE_FLAG_TRANS		0x00000002
#define IMAGE_FLAG_TEXTURE		0x00000004

#define IMAGE_VERTEXFLAGS		(D3DFVF_DIFFUSE|D3DFVF_XYZRHW|D3DFVF_TEX1)

enum Image_TextureMode {

	Image_TextureMode_Normal,
	Image_TextureMode_Subtractive,
	Image_TextureMode_Additive,
	Image_TextureMode_Transparent,

	Image_TextureMode_Fixed_Subtractive,		// Not affected by the global intensity value
	Image_TextureMode_Fixed_Additive,
	Image_TextureMode_Fixed_Transparent,

	Image_TextureMode_Count
};

typedef struct ImageVertex {

	VECTOR4D position;
	ULONG colour;
	REAL tu, tv;

} ImageVertex, *lpImageVertex;

/**********************************************************************************
 ******** Image Structure
 **********************************************************************************/

#ifndef _GODS98COMPILE
typedef LPVOID	LPDIRECTDRAWSURFACE4;
typedef LPVOID	LPDIRECT3DTEXTURE2;
typedef ULONG	D3DTEXTUREHANDLE;
#endif // _GODS98COMPILE

typedef struct Image {

	LPDIRECTDRAWSURFACE4 surface;
	LPDIRECT3DTEXTURE2 texture;
	D3DTEXTUREHANDLE textureHandle;

	ULONG width, height;
	ULONG penZero, pen255, penZeroRGB;

	ULONG flags;

	struct Image *nextFree;

} Image, *lpImage;

#ifdef _GODS98COMPILE

typedef struct Image_Globs {

	lpImage listSet[IMAGE_MAXLISTS];		// Images list
	lpImage freeList;

/*	lpImage frontBuffer;					// front buffer (currently displayed).
	lpImage backBuffer;					// back buffer (for next image).
	BOOL isBackBufferInVidMem;				// Is the back buffer in video memory.
	BOOL isPageFlipped;						// Are we in page flipping mode.
	BOOL asyncBlit;							// Should we perform blits asyncronously.
	BOOL canHWBlit;							// Used for optimisation.
*/

//	LPDIRECT3DMATERIAL3 textureMaterial;
//	D3DMATERIALHANDLE textureMaterialHandle;
//	D3DMATERIAL mat;

	LPDIRECT3DVIEWPORT3 useViewport;
	REAL alphaIntensity;

	ULONG listCount;						// number of lists.
	ULONG flags;

} Image_Globs, *lpImage_Globs;

#endif _GODS98COMPILE

//typedef LPVOID lpImage_Texture;

 /**********************************************************************************
 ******** Image Macros
 **********************************************************************************/

VOID Image_GetScreenshot(lpImage image, ULONG xsize, ULONG ysize);
BOOL Image_SaveBMP(lpImage image, LPUCHAR fname);

#ifdef DEBUG
	#define Image_CheckInit()			if (!(imageGlobs.flags & IMAGE_FLAG_INITIALISED)) Error_Fatal(TRUE, "Error: Image_Intitialise() Has Not Been Called");
#else
	#define Image_CheckInit()
#endif

#define Image_LoadBMP(n)					Image_LoadBMPScaled((n),0,0)
#define Image_Display(p,l)					Image_DisplayScaled((p),NULL,(l),NULL)

__inline SLONG Image_GetWidth(lpImage p)	{ return p->width; }
__inline SLONG Image_GetHeight(lpImage p)	{ return p->height; }

/**********************************************************************************
 ******** Image Prototypes
 **********************************************************************************/

#ifndef _GENPROTFILE
#include "..\Src\Images.prot"
#endif // _GENPROTFILE

#endif // _GODS98_IMAGES_H_
