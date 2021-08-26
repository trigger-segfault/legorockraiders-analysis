
#ifndef _GODS98_VIEWPORTS_H_
#define _GODS98_VIEWPORTS_H_

#include "Maths.h"
#include "Containers.h"

/**********************************************************************************
 **
 ** Viewport.h: Viewport Object Header for GODS
 **
 ** Copyright (C) Data Design Interactive.
 **
 **
 ** Written by <>
 **
 **********************************************************************************/

/**********************************************************************************
 ******** Viewport Defaults and Enumeration
 **********************************************************************************/

#define VIEWPORT_MAXLISTS			32			// 2^32 - 1 possible viewports...

#define VIEWPORT_FLAG_INITIALISED	0x00000001

/**********************************************************************************
 ******** Viewport Macros
 **********************************************************************************/

#ifdef DEBUG
	#define Viewport_CheckInit()			if (!(viewportGlobs.flags & VIEWPORT_FLAG_INITIALISED)) Error_Fatal(TRUE, "Error: Viewport_Intitialise() Has Not Been Called");
#else
	#define Viewport_CheckInit()
#endif

/**********************************************************************************
 ******** Viewport Structure
 **********************************************************************************/

#ifndef _GODS98COMPILE

typedef LPVOID LPDIRECT3DRMVIEWPORT2;

#endif // _GODS98COMPILE

typedef struct Viewport {

	REAL xoffset, yoffset;			// Position on viewport normalised to between 0.0 and 1.0
	REAL width, height;				// Width and height of the viewport normalised as above
	LPDIRECT3DRMVIEWPORT2 lpVP;		// Pointer to D3D viewport interface
	REAL smoothFOV;
	BOOL rendering;

	struct Viewport *nextFree;

} Viewport, *lpViewport;

typedef struct Viewport_Globs {

	Viewport *listSet[VIEWPORT_MAXLISTS];
	Viewport *freeList;

	ULONG listCount;
	ULONG flags;

} Viewport_Globs, *lpViewport_Globs;

typedef struct Viewport_PickInfo {

	lpContainer pickCont;
	ULONG group, face;
	VECTOR3D position;

} Viewport_PickInfo, *lpViewport_PickInfo;

typedef struct Viewport_Pick {

	lpViewport_PickInfo pickArray;
	ULONG pickCount;

} Viewport_Pick, *lpViewport_Pick;

#ifdef _GODS98COMPILE

extern Viewport_Globs viewportGlobs;
__inline LPDIRECT3DRMVIEWPORT2 Debug_View() { return viewportGlobs.listSet[0][0].lpVP; }

#endif // _GODS98COMPILE


/**********************************************************************************
 ******** Viewport Prototypes
 **********************************************************************************/

#ifndef _GENPROTFILE
#include "..\src\Viewports.prot"
#endif // _GENPROTFILE

extern VOID __cdecl Viewport_ClearZBuffer(lpViewport vp);

#endif // _GODS98_VIEWPORTS_H_
