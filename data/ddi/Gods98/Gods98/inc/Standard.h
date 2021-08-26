
#ifndef _GODS98_STANDARD_H_
#define _GODS98_STANDARD_H_

#define _GODS98_DX6				// DirectX6 version of Gods98

#define LEGO_IMMEDIATEMODEMAP

//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>

#define STANDARD_FRAMERATE		25.0f

_CRTIMP int __cdecl sprintf(char *, const char *, ...);
_CRTIMP int __cdecl sscanf(const char *, const char *, ...);
_CRTIMP int __cdecl _vsnprintf(char *, size_t, const char *, va_list);
_CRTIMP int __cdecl vsprintf(char *, const char *, va_list);

#define itemcount(l)	(sizeof(l)/sizeof(l[0]))

typedef unsigned char	UCHAR;
typedef signed char		SCHAR;
typedef unsigned long	ULONG;
typedef signed long		SLONG;
typedef unsigned short	UWORD;
typedef signed short	SWORD;
#ifndef VOID
typedef void			VOID;
#endif
typedef int				BOOL;

typedef UCHAR *			LPUCHAR;
typedef SCHAR *			LPSCHAR;
typedef UWORD *			LPUWORD;
typedef SWORD *			LPSWORD;
typedef ULONG *			LPULONG;
typedef SLONG *			LPSLONG;
typedef LPUCHAR			STRING;
typedef float			REAL;
typedef REAL *			LPREAL;
typedef VOID *			LPVOID;
typedef BOOL *			LPBOOL;

typedef struct Block {

	SLONG x, y;

} Block, *lpBlock;

#ifndef FALSE
enum {
	FALSE = 0,
	TRUE = 1
};
#endif

#include "..\Inc\Maths.h"

__inline BOOL Block_Compare(lpBlock a, lpBlock b)			{ return (a->x==b->x&&a->y==b->y); }
__inline BOOL Block_Adjacent(lpBlock a, lpBlock b)			{ return ((a->x == b->x && 1 == abs(a->y - b->y)) || (a->y == b->y && 1 == abs(a->x - b->x))); }
__inline lpBlock Block_FromString(lpBlock b, LPUCHAR str)	{ LPUCHAR y; b->x = atoi(str); y = strstr(str, ","); y++; b->y = atoi(y); return b; }
__inline lpBlock Block_Rotate(lpBlock b, SLONG dir)			{ SLONG swap; dir = (dir + (1<<15)) % 4; switch(dir) { case 0: break; case 1: swap = b->x; b->x = -b->y; b->y = swap; break; case 2: b->x = -b->x; b->y = -b->y; break; case 3: swap = b->x; b->x = b->y; b->y = -swap; break; } return b; }
__inline lpBlock Block_Random(lpBlock b, lpBlock size)		{ b->x = Maths_Rand() % size->x ; b->y = Maths_Rand() % size->y; return b; }

#endif // _GODS98_STANDARD_H_
