
#ifndef _RGL_ERRORS_H_
#define _RGL_ERRORS_H_

#ifdef _DEBUG
#ifdef _RGL

enum ErrorDirectXModule {

	ErrorDirectXModule_DirectDraw,
	ErrorDirectXModule_Direct3D,
	ErrorDirectXModule_Direct3DRM,
	ErrorDirectXModule_DirectXFile,
	ErrorDirectXModule_DirectInput,

	ErrorDirectXModule_Count
};

#define Error_RegisterHR(h)				Error_RegisterHRFunc((h), #h)
#define Error_RegisterDXMName(m)		errorGlobs.dxName[m]=&(#m)[strlen("ErrorDirectXModule_")];

#endif // _RGL

/************************************************************************************************************************
 **** Typedefs available outside the library...
 ************************************************************************************************************************/

#endif // _DEBUG

#ifndef _AUTOPROTOTYPES
// Auto Prototypes
extern unsigned __int64 __stdcall Int64ShllMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern __int64 __stdcall Int64ShraMod32(__int64 Value,unsigned long ShiftCount);
extern unsigned __int64 __stdcall Int64ShrlMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern void *__cdecl GetFiberData(void );
extern void *__cdecl GetCurrentFiber(void );
extern void __cdecl Error_SetErrorFunction(unsigned char *name);
extern unsigned char *__cdecl Error_GetErrorFunction(void );
extern void __cdecl Error_RegisterHRFunc(unsigned long hr,unsigned char *name);
extern void __cdecl Error_RegisterHResults(void );
extern void __cdecl Error_Initialise(void );
extern void __cdecl Error_Shutdown(void );
extern void __cdecl Error_Exit(void );
extern void __cdecl Error_FullScreenMode(int fullScreen);
extern void __cdecl Error_DirectXFunc(long r,unsigned char *function,unsigned char *file,unsigned long line);
extern void __cdecl Error_Out(int condition,int fatal,unsigned char *file,unsigned long line,unsigned char *msg,...);
extern unsigned char *__cdecl Error_Format(unsigned char *msg,...);
// Auto Prototypes
#endif // !_AUTOPROTOTYPES

#ifdef _DEBUG

#include <ddraw.h>

#define Error_Fatal(c,m)				Error_Out((c),TRUE,__FILE__,__LINE__,(m))
#define Error_Warn(c,m)					Error_Out((c),FALSE,__FILE__,__LINE__,(m))
#define Error_Failed(f)					Error_Out(TRUE,FALSE,__FILE__,__LINE__,"Failed call to function %s()",(f))
#define Error_Overflow(c,m)				Error_Out((c)>=(m),TRUE,__FILE__,__LINE__,"%s has overflowed '%s' (%i)",#c,#m,(m))
#define Error_DirectX(r,f)				Error_DirectXFunc((r),(f),__FILE__,__LINE__);
#else // _DEBUG
#define Error_Fatal(c,m)
#define Error_Warn(c,m)
#define Error_Failed(f)
#define Error_Overflow(c,m)
#define Error_DirectX(r,f)
#endif // _DEBUG

#endif // !_RGL_ERRORS_H_
