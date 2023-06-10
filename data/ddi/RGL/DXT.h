
#ifndef _RGL_DXT_H
#define _RGL_DXT_H

#include <dxtrans.h>

#define DXTFLAG_INITIALISED		0x00000001

// Auto Prototypes
extern unsigned __int64 __stdcall Int64ShllMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern __int64 __stdcall Int64ShraMod32(__int64 Value,unsigned long ShiftCount);
extern unsigned __int64 __stdcall Int64ShrlMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern void *__cdecl GetFiberData(void );
extern void *__cdecl GetCurrentFiber(void );
extern void __cdecl DXT_Initialise(void );
extern struct IDirectDrawSurface7 *__cdecl DXT_LoadImage(unsigned char *fname);
// Auto Prototypes

#endif // !_RGL_DXT_H
