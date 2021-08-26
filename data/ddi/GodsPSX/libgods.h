
//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Header File For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#ifndef	_LIBGODS_H_

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// include all playstation library stuff
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <kernel.h>
#include <inline_c.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libpress.h>
#include <libgs.h>
#include <libcd.h>
#include <libsn.h>
#include <libmath.h>
#include <libsnd.h>
#include <libspu.h>
#include <libhmd.h>
#include <gtemac.h>
#include <libtap.h>
//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Typedefs go here
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

typedef	void				VOID;
typedef	unsigned char	Uint8;
typedef	unsigned char	UCHAR;
typedef	unsigned short	ANGLE;
typedef	unsigned short	Uint16;
typedef	unsigned short	UWORD;
typedef	unsigned long	Uint32;
typedef	unsigned long	BOOL;
typedef	unsigned long	ULONG;
typedef	signed char		byte;
typedef	signed char		Sint8;
typedef	signed char		SCHAR;
typedef	signed short	Sint16;
typedef	signed short	SWORD;
typedef	signed short	word;
typedef	signed long		Sint32;
typedef	signed long		SLONG;
typedef	signed long		FIXED;
typedef	signed long		REAL;
typedef ULONG				COLOUR;

typedef	SLONG*	LPREAL;
typedef	SLONG*	LPSLONG;
typedef	ULONG*	LPULONG;
typedef	ULONG*	LPBOOL;
typedef	UCHAR*	LPUCHAR;
typedef	SCHAR*	LPSCHAR;
typedef	UWORD*	LPUWORD;
typedef	SWORD*	LPSWORD;
typedef ULONG*	LPCOLOUR;
typedef	VOID*		LPVOID;


typedef	RECT*				lpRECT;
typedef	DR_AREA*			lpDR_AREA;
typedef	TIM_IMAGE*		lpTIM_IMAGE;
typedef	PACKET*			lpPACKET;
typedef	GsDOBJ2*			lpGsDOBJ2;
typedef	GsF_LIGHT*		lpGsF_LIGHT;
typedef	lpGsDOBJ2*		lplpGsDOBJ2;
typedef	GsOT_TAG*		lpGsOT_TAG;
typedef	VECTOR*			LPVECTOR;
typedef	SVECTOR*			lpSVECTOR;

typedef	REAL	D3DRMMATRIX4D[4][4];

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Defines Go Here
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#ifndef	ext
#define	ext					extern
#endif

#ifndef	NULL
#define	NULL					0
#endif

#define	ON						1
#define	YES					1
#define	TRUE					1
#define	OK						1

#define	NO						0
#define	OFF					0
#define	FALSE					0

#define	FAIL					-1

#define	DCACHE				(Uint32*)0x1f800000

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// General Structures Go Here
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

typedef struct AREA2D
{
	Sint32	x, y;
	Sint32	width, height;
} AREA2D, *LPAREA2D;

typedef struct VECTOR2D
{
	REAL		x, y;
} VECTOR2D, *LPVECTOR2D;

typedef struct VECTOR3D
{
	REAL		x, y, z;
} VECTOR3D, *LPVECTOR3D;

typedef struct VECTOR4D
{
	REAL x, y, z, w;

} VECTOR4D, *LPVECTOR4D;

typedef struct VERTEX3D
{
	VECTOR3D position;
	VECTOR3D normal;
	REAL tu, tv;
	COLOUR colour;

} VERTEX3D, *LPVERTEX3D;

typedef struct BOX3D
{
	VECTOR3D min, max;

} BOX3D, *LPBOX3D;

typedef	struct	POLY_T3
{
	Uint8		ilen, olen, flag, mode;
	Uint8		u0, v0;
	Uint16	CBA;
	Uint8		u1, v1;
	Uint16	TSB;
	Uint8		u2, v2;
	Uint16	pad0;
	Uint16	Norm0;
	Uint16	Vert0, Vert1, Vert2;
} POLY_T3, *lpPOLY_T3;


typedef REAL MATRIX4D[4][4];

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Macros Go Here
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#define	WHOLE(_n_)			(_n_&~(ONE-1))
#define	FRACT(_n_)			(_n_&(ONE-1))
#define	ToFIXED(_n_)		((_n_)*ONE)
#define	FromFIXED(_n_)		((_n_)/ONE)
#define	ToFIXEDANG(_a_)	(((_a_)*ONE)/360)
#define	FromFIXEDANG(_a_)	(((_a_)*360)/ONE)
#define	MAX(x, y)			(Sint32)(((Sint32)x>(Sint32)y) ? x:y)
#define	MIN(x, y)			(Sint32)(((Sint32)x<(Sint32)y) ? x:y)
#define	max(x, y)			(Sint32)(((Sint32)x>(Sint32)y) ? x:y)
#define	min(x, y)			(Sint32)(((Sint32)x<(Sint32)y) ? x:y)

//#define Asm_MulFIX(a,b)	((long)((((long)(a))*((long)(b)))>>12))
//#define Asm_DivFIX(a,b)	((long)((((long)(a))<<12)/((long)(b))))


#define	appWidth()			gfxGlobs.scrW
#define	appHeight()			gfxGlobs.scrH

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// G.O.D.S Include Go Here
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#define UTIL_DEFSTRINGLEN		512





/************************************************************************************************************************************************
		Define up some cool data cache based variables based on 68k registers
************************************************************************************************************************************************/
extern int d0 __attribute__ ((section("cachedata")));
extern int d1 __attribute__ ((section("cachedata")));
extern int d2 __attribute__ ((section("cachedata")));
extern int d3 __attribute__ ((section("cachedata")));
extern int d4 __attribute__ ((section("cachedata")));
extern int d5 __attribute__ ((section("cachedata")));
extern int d6 __attribute__ ((section("cachedata")));
extern int d7 __attribute__ ((section("cachedata")));

extern long a0 __attribute__ ((section("cachedata")));
extern long a1 __attribute__ ((section("cachedata")));
extern long a2 __attribute__ ((section("cachedata")));
extern long a3 __attribute__ ((section("cachedata")));
extern long a4 __attribute__ ((section("cachedata")));
extern long a5 __attribute__ ((section("cachedata")));
extern long a6 __attribute__ ((section("cachedata")));
extern long a7 __attribute__ ((section("cachedata")));

extern CVECTOR Dcvec1 __attribute__ ((section("cachedata")));
extern VECTOR Dvec1 __attribute__ ((section("cachedata")));
extern VECTOR Dvec2 __attribute__ ((section("cachedata")));
extern SVECTOR Dsvec1 __attribute__ ((section("cachedata")));
extern SVECTOR Dsvec2 __attribute__ ((section("cachedata")));


//#define	MEMORY_TRACKING			/* if defined, will track memory allocation */

/*
#include	<gods/main.h>	
#include	<gods/maths.h>	
#include 	<gods/3d.h>
#include	<gods/material.h>	
#include	<gods/image.h>	
#include	<gods/activity.h>	
#include	<gods/contain.h>	
#include	<gods/mem.h>		
#include	<gods/file.h>	
#include	<gods/sound.h>	
#include	<gods/input.h>	
#include	<gods/config.h>	
#include	<gods/graphics.h>
#include	<gods/viewport.h>
#include	<gods/fonts.h>	
#include	<gods/textwind.h>
#include	<gods/draw.h>
#include	<gods/error.h>
#include	<gods/hmd.h>
#include	<gods/asmcode.h>	
*/

#include	"ctrller.h"
#include	"main.h"
#include	"maths.h"	
#include 	"3d.h"
#include	"material.h"
#include	"file.h"		
#include	"image.h"	
#include	"activity.h"	
#include	"contain.h"
#include	"contain2.h"
#include	"tmd.h"
#include	"collisio.h"
#include	"sprite.h"
#include	"mem.h"		
#include	"sound.h"	
#include	"sfx.h"	
#include	"input.h"	
#include	"config.h"	
#include	"graphics.h"
#include	"viewport.h"
#include	"fonts.h"	
#include	"textwind.h"
#include	"draw.h"
#include	"error.h"
#include	"hmd.h"
#include	"asmcode.h"
#include	"card.h"

#define	_LIBGODS_MAIN_H_
#endif	!_LIBGODS_MAIN_H_ 
