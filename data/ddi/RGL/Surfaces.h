
#ifndef _RGL_SURFACES_H_
#define _RGL_SURFACES_H_

#ifndef _AUTOPROTOTYPES
// Auto Prototypes
extern VOID Surface_Convert(LPDIRECTDRAWSURFACE7 src, LPDIRECTDRAWSURFACE7 dest);
static VOID Surface_CopyData_8Bit(LPDDSURFACEDESC2 sDesc, LPDDSURFACEDESC2 dDesc);
static VOID Surface_CopyData_Masked(LPDDSURFACEDESC2 sDesc, LPDDSURFACEDESC2 dDesc);
static VOID Surface_GenerateFromPalettizedSurface(LPDDSURFACEDESC2 sDesc, LPDDSURFACEDESC2 dDesc, PALETTEENTRY palette[256]);
static LPDIRECTDRAWPALETTE Surface_GeneratePalettizedSurface(LPDDSURFACEDESC2 sDesc, LPDDSURFACEDESC2 dDesc, ULONG colourCount);
extern void __cdecl Surface_Initialise(void );
extern void __cdecl Surface_Shutdown(void );
extern VOID __cdecl Surface_Remove(LPDIRECTDRAWSURFACE7 surface);
extern LPDIRECTDRAWSURFACE7 __cdecl Surface_GetShared(LPUCHAR fname);
extern VOID __cdecl Surface_RegisterShared(LPUCHAR fname, LPDIRECTDRAWSURFACE7 surface);
// Auto Prototypes
#endif // !_AUTOPROTOTYPES

#endif // !_RGL_SURFACES_H_
