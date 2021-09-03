#pragma once

#include "../framework.h"
#include "Maths.h"


namespace Gods98
{; // !<---
	
/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define IMAGE_MAXLISTS			32			// 2^32 - 1 possible images...

#pragma endregion

/**********************************************************************************
 ******** Enumerations
 **********************************************************************************/

#pragma region Enums
	
#define IMAGE_FLAG_INITIALISED	0x00000001
#define IMAGE_FLAG_TRANS		0x00000002
#define IMAGE_FLAG_TEXTURE		0x00000004

#define IMAGE_VERTEXFLAGS		(D3DFVF_DIFFUSE|D3DFVF_XYZRHW|D3DFVF_TEX1)


enum Image_TextureMode
{
	Image_TextureMode_Normal,
	Image_TextureMode_Subtractive,
	Image_TextureMode_Additive,
	Image_TextureMode_Transparent,

	Image_TextureMode_Fixed_Subtractive,		// Not affected by the global intensity value
	Image_TextureMode_Fixed_Additive,
	Image_TextureMode_Fixed_Transparent,

	Image_TextureMode_Count
};
static_assert(sizeof(Image_TextureMode) == 0x4, "");

#pragma endregion

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

typedef struct ImageVertex
{
	/*00,10*/ VECTOR4D position;
	/*10,4*/ unsigned long colour;
	/*14,4*/ float tu;
	/*18,4*/ float tv;
	/*1c*/
} ImageVertex, *lpImageVertex;
static_assert(sizeof(ImageVertex) == 0x1c, "");


typedef struct Image
{
	/*00,4*/ IDirectDrawSurface4* surface;
	//IDirect3DTexture2* texture;
	//D3DTEXTUREHANDLE textureHandle;
	/*04,4*/ unsigned long width;
	/*08,4*/ unsigned long height;
	/*0c,4*/ unsigned long penZero;
	/*10,4*/ unsigned long pen255;
	/*14,4*/ unsigned long penZeroRGB;
	/*18,4*/ unsigned long flags;
	/*1c,4*/ Image *nextFree;
	/*20*/
} Image, *lpImage;
static_assert(sizeof(Image) == 0x20, "");


typedef struct Image_Globs
{
	/*00,80*/ Image* listSet[IMAGE_MAXLISTS];		// Images list
	/*80,4*/ Image* freeList;
	/*84,4*/ unsigned long listCount;						// number of lists.
	/*88,4*/ unsigned long flags;
	/*8c*/
} Image_Globs;
static_assert(sizeof(Image_Globs) == 0x8c, "");

#pragma endregion

/**********************************************************************************
 ******** Globals
 **********************************************************************************/

#pragma region Globals

// <LegoRR.exe @00534908>
extern Image_Globs imageGlobs;

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

/*long __cdecl Image_GetWidth(const Image* p);
long __cdecl Image_GetHeight(const Image* p);*/


// <LegoRR.exe @0047d6d0>
void __cdecl Image_Initialise(void);

// <LegoRR.exe @0047d6f0>
void __cdecl Image_Shutdown(void);

// <LegoRR.exe @0047d730>
void __cdecl Image_Remove(Image* dead);

// <LegoRR.exe @0047d750>
BOOL __cdecl Image_CopyToDataToSurface(IDirectDrawSurface4* surface, D3DRMIMAGE* image);

// <LegoRR.exe @0047d7e0>
BOOL __cdecl Image_8BitSourceCopy(DDSURFACEDESC2* desc, D3DRMIMAGE* image);

// <LegoRR.exe @0047d9c0>
unsigned long __cdecl Image_CountMaskBits(unsigned long mask);

// <LegoRR.exe @0047d9e0>
unsigned long __cdecl Image_CountMaskBitShift(unsigned long mask);

// <LegoRR.exe @0047da00>
void __cdecl Image_FlipSurface(DDSURFACEDESC2* desc);

// <LegoRR.exe @0047dac0>
BOOL __cdecl Image_24BitSourceCopy(DDSURFACEDESC2* desc, D3DRMIMAGE* image);

// <LegoRR.exe @0047dc90>
Image* __cdecl Image_LoadBMPScaled(const char* filename, unsigned long width, unsigned long height);

// <LegoRR.exe @0047de50>
COLORREF __cdecl Image_RGB2CR(unsigned char r, unsigned char g, unsigned char b);

// <LegoRR.exe @0047de80>
void __cdecl Image_SetPenZeroTrans(Image* image);

// <LegoRR.exe @0047deb0>
void __cdecl Image_SetupTrans(Image* image, float lowr, float lowg, float lowb, float highr, float highg, float highb);

// <LegoRR.exe @0047df70>
void __cdecl Image_DisplayScaled(Image* image, const AREA2D* src, const VECTOR2D* destPos, const VECTOR2D* destSize);

// <LegoRR.exe @0047e120>
void* __cdecl Image_LockSurface(Image* image, OUT unsigned long* pitch, OUT unsigned long* bpp);

// <LegoRR.exe @0047e190>
void __cdecl Image_UnlockSurface(Image* image);

// <LegoRR.exe @0047e1b0>
unsigned long __cdecl Image_GetPen255(Image* image);

// <LegoRR.exe @0047e210>
unsigned long __cdecl Image_GetPixelMask(Image* image);

// <LegoRR.exe @0047e260>
BOOL __cdecl Image_GetPixel(Image* image, unsigned long x, unsigned long y, OUT unsigned long* colour);

// <LegoRR.exe @0047e310>
Image* __cdecl Image_Create(IDirectDrawSurface4* surface, unsigned long width, unsigned long height, COLORREF penZero, COLORREF pen255);

// <LegoRR.exe @0047e380>
void __cdecl Image_AddList(void);

// <LegoRR.exe @0047e3f0>
void __cdecl Image_RemoveAll(void);

// <LegoRR.exe @0047e450>
unsigned long __cdecl Image_DDColorMatch(IDirectDrawSurface4* pdds, unsigned long rgb);

// <LegoRR.exe @0047e590>
void __cdecl Image_CR2RGB(COLORREF cr, OUT unsigned char* r, OUT unsigned char* g, OUT unsigned char* b);

// <LegoRR.exe @0047e5c0>
void __cdecl Image_GetScreenshot(OUT Image* image, unsigned long xsize, unsigned long ysize);


// <LegoRR.exe @0047e6a0>
void __cdecl Image_InitFromSurface(Image* newImage, IDirectDrawSurface4* surface,
								unsigned long width, unsigned long height, COLORREF penZero, COLORREF pen255);

// <LegoRR.exe @0047e700>
BOOL __cdecl Image_SaveBMP(Image* image, const char* fname);


/*Image* __cdecl Image_LoadBMPTexture(const char* filename);
void __cdecl Image_GetPenZero(const Image* image, OUT float* r, OUT float* g, OUT float* b);
void __cdecl Image_SetMainViewport(Viewport* vp);
void __cdecl Image_SetAlphaIntensity(float level);
void __cdecl Image_DisplayScaled2(Image* image, const AREA2D* src, const VECTOR2D* destPos, const VECTOR2D* destSize, Image_TextureMode textureMode, float level, const VECTOR2D* uvs);
void __cdecl Image_DisplayScaled(Image* image, const AREA2D* src, const VECTOR2D* destPos, const VECTOR2D* destSize);
void* __cdecl Image_LockSurface(Image* image, unsigned long* pitch, unsigned long* bpp);
void __cdecl Image_UnlockSurface(Image* image);
int __cdecl Image_CopyBMP(IDirectDrawSurface4* pdds, void* hbm, unsigned long x, unsigned long y, unsigned long dx, unsigned long dy);

unsigned long __cdecl Image_RGB2CR(unsigned char r, unsigned char g, unsigned char b);
void __cdecl Image_MyBlt(IDirectDrawSurface* dest, IDirectDrawSurface* src, unsigned long sx, unsigned long sy);


#ifdef DEBUG
	#define Image_CheckInit()			if (!(imageGlobs.flags & IMAGE_FLAG_INITIALISED)) Error_Fatal(TRUE, "Error: Image_Intitialise() Has Not Been Called");
#else
	#define Image_CheckInit()
#endif

#define Image_LoadBMP(n)					Image_LoadBMPScaled((n),0,0)
#define Image_Display(p,l)					Image_DisplayScaled((p),NULL,(l),NULL)

__inline signed long Image_GetWidth(const Image* p) { return p->width; }
__inline signed long Image_GetHeight(const Image* p) { return p->height; }*/

#pragma endregion

}
