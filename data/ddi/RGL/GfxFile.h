
#ifndef _RGL_GFXFILE_H_
#define _RGL_GFXFILE_H_

#define GFXFILE_BMPMAGIC				'MB'

/*
struct GfxFilePaletteEntry {

	UCHAR r, g, b, flags;
};

typedef struct GfxFilePaletteEntry		*lpGfxFilePaletteEntry;
*/

// Auto Prototypes
extern unsigned __int64 __stdcall Int64ShllMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern __int64 __stdcall Int64ShraMod32(__int64 Value,unsigned long ShiftCount);
extern unsigned __int64 __stdcall Int64ShrlMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern void *__cdecl GetFiberData(void );
extern void *__cdecl GetCurrentFiber(void );
extern void __cdecl GfxFile_Initialise(void );
extern struct IDirectDrawSurface7 *__cdecl GfxFile_LoadSurface(unsigned char *fname,int useShared);
extern struct IDirectDrawSurface7 *__cdecl GfxFile_GetSharedTextureSurface(unsigned char *fname);
extern struct IDirectDrawSurface7 *__cdecl GfxFile_LoadTextureSurface(unsigned char *fname,int registerShared, ULONG depth, LPULONG colourKey);
extern unsigned char *__cdecl GfxFile_ParseBMP(unsigned char *fname,unsigned long *width,unsigned long *height,unsigned long *depth,struct tagPALETTEENTRY *palette);
extern struct IDirectDrawSurface7 *__cdecl GfxFile_CreateTextureSurface(unsigned char *imageData,unsigned long width,unsigned long height,unsigned long depth,struct tagPALETTEENTRY *palette,unsigned long textureDepth, unsigned long *colourKey);
extern struct IDirectDrawSurface7 *__cdecl GfxFile_CreatePlaneSurface(unsigned char *imageData,unsigned long width,unsigned long height);
// Auto Prototypes

#endif // !_RGL_GFXFILE_H_
