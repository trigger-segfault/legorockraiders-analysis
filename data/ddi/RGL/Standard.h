
#ifndef _RGL_STANDARD_H_
#define _RGL_STANDARD_H_

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>

#define STANDARD_FRAMERATE		25.0f

#define MAX_ULONG				0xffffffff
#define MAX_SLONG				0x7fffffff
#define MAX_UWORD				0xffff
#define MAX_SWORD				0x7fff
#define MAX_UCHAR				0xff
#define MAX_SCHAR				0x7f
#define MAX_REAL				(3.402823466e+38f)

typedef unsigned __int64		U64;
typedef signed __int64			S64;

typedef unsigned long			ULONG;
typedef signed long				SLONG;
typedef unsigned short			UWORD;
typedef signed short			SWORD;
typedef unsigned char			UCHAR;
typedef signed char				SCHAR;

typedef unsigned __int64		*LPU64;
typedef signed __int64			*LPS64;

typedef unsigned long			*LPULONG;
typedef signed long				*LPSLONG;
typedef unsigned short			*LPUWORD;
typedef signed short			*LPSWORD;
typedef unsigned char			*LPUCHAR;
typedef signed char				*LPSCHAR;

#ifndef VOID
typedef void					VOID;
typedef void					*LPVOID;
#endif // !VOID

#ifndef BOOL
typedef int						BOOL;
typedef int						*LPBOOL;
#endif // !BOOL

typedef unsigned long			FLAG;
typedef unsigned long			*LPFLAG;

#ifndef FALSE
enum							{ FALSE=0, TRUE=1 };
#endif

typedef float					REAL, *LPREAL;

typedef struct StandardCallback { VOID (*function)(); LPVOID data; LPVOID localData; } *lpStandardCallback;

typedef struct AREA2Di { ULONG x, y, width, height; }	AREA2Di, *LPAREA2Di;
typedef struct AREA2Dr { REAL x, y, width, height; }	AREA2Dr, *LPAREA2Dr;

typedef struct NCOLOUR { REAL r, g, b, a; }				NCOLOUR, *LPNCOLOUR;
typedef ULONG											COLOUR, *LPCOLOUR;

#define	COLOUR_FROMREALA(a,r,g,b)						(((COLOUR)((a)*255.0f)<<24)|((COLOUR)((r)*255.0f)<<16)|((COLOUR)((g)*255.0f)<<8)|((COLOUR)((b)*255.0f)))
#define	COLOUR_FROMREAL(r,g,b)							(0xff000000|(COLOUR)((r)*255.0f)<<16)|((COLOUR)((g)*255.0f)<<8)|((COLOUR)((b)*255.0f))
#define COLOUR_FROMCHARA(a,r,g,b)						(((a)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff))
#define COLOUR_FROMCHAR(r,g,b)							(0xff000000|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff))
#define COLOUR_GETALPHA(c)								(((c)&0xff000000)>>24)
#define COLOUR_GETRED(c)								(((c)&0x00ff0000)>>16)
#define COLOUR_GETGREEN(c)								(((c)&0x0000ff00)>>8)
#define COLOUR_GETBLUE(c)								((c)&0x000000ff)
#define COLOUR_GETREALALPHA(c)							((REAL)COLOUR_GETALPHA(c)/255.0f)
#define COLOUR_GETREALRED(c)							((REAL)COLOUR_GETRED(c)/255.0f)
#define COLOUR_GETREALGREEN(c)							((REAL)COLOUR_GETGREEN(c)/255.0f)
#define COLOUR_GETREALBLUE(c)							((REAL)COLOUR_GETBLUE(c)/255.0f)

extern VOID AREA2Di2r(LPAREA2Dr r, LPAREA2Di i);
extern VOID AREA2Dr2i(LPAREA2Di i, LPAREA2Dr r);

extern ULONG REALASULONG(REAL r);

//#pragma message ( "REMOVE ME..." )
//#include "..\..\MTrucksPC2\Code\Dialogs.h"


#endif // _RGL_STANDARD_H_
