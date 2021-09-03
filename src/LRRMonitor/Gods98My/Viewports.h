#pragma once

#include "../framework.h"
#include "Maths.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Forward Declarations
 **********************************************************************************/

#pragma region Forward Declarations

struct Container;

#pragma endregion

/**********************************************************************************
 ******** Function Typedefs
 **********************************************************************************/

#pragma region Function Typedefs

#pragma endregion

/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define VIEWPORT_MAXLISTS			32			// 2^32 - 1 possible viewports...

#pragma endregion

/**********************************************************************************
 ******** Enumerations
 **********************************************************************************/

#pragma region Enums

#define VIEWPORT_FLAG_INITIALISED	0x00000001

#pragma endregion

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

typedef struct Viewport
{
	/*00,4*/ float xoffset;
	/*04,4*/ float yoffset;			// Position on viewport normalised to between 0.0 and 1.0
	/*08,4*/ float width;
	/*0c,4*/ float height;				// Width and height of the viewport normalised as above
	/*10,4*/ IDirect3DRMViewport2* lpVP;		// Pointer to D3D viewport interface
	/*14,4*/ float smoothFOV;
	/*18,4*/ BOOL rendering;
	/*1c,4*/ Viewport* nextFree;
	/*20*/
} Viewport, *lpViewport;
static_assert(sizeof(Viewport) == 0x20, "");


typedef struct Viewport_PickInfo
{
	/*00,4*/ Container* pickCont;
	/*04,4*/ unsigned long group;
	/*08,4*/ unsigned long face;
	/*0c,c*/ VECTOR3D position;
	/*18*/
} Viewport_PickInfo, *lpViewport_PickInfo;
static_assert(sizeof(Viewport_PickInfo) == 0x18, "");


typedef struct Viewport_Pick
{
	/*0,4*/ Viewport_PickInfo* pickArray;
	/*4,4*/ unsigned long pickCount;
	/*8*/
} Viewport_Pick, *lpViewport_Pick;
static_assert(sizeof(Viewport_Pick) == 0x8, "");


typedef struct Viewport_Globs
{
	/*00,80*/ Viewport* listSet[VIEWPORT_MAXLISTS];
	/*80,4*/ Viewport* freeList;
	/*84,4*/ unsigned long listCount;
	/*88,4*/ unsigned long flags;
	/*8c*/
} Viewport_Globs;
static_assert(sizeof(Viewport_Globs) == 0x8c, "");

#pragma endregion

/**********************************************************************************
 ******** Globals
 **********************************************************************************/

#pragma region Globals

// <LegoRR.exe @0076bce0>
extern Viewport_Globs viewportGlobs;

#pragma endregion

/**********************************************************************************
 ******** Macros
 **********************************************************************************/

#pragma region Macros

#ifdef DEBUG
	#define Viewport_CheckInit()			if (!(viewportGlobs.flags & VIEWPORT_FLAG_INITIALISED)) Error_Fatal(TRUE, "Error: Viewport_Intitialise() Has Not Been Called");
#else
	#define Viewport_CheckInit()
#endif

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @00477010>
void __cdecl Viewport_Initialise(void);

// <LegoRR.exe @00477040>
void __cdecl Viewport_Shutdown(void);

// <LegoRR.exe @00477080>
Viewport* __cdecl Viewport_Create(float xPos, float yPos, float width, float height, Container* camera);

// <LegoRR.exe @00477110>
Viewport* __cdecl Viewport_CreatePixel(long xPos, long yPos, unsigned long width, unsigned long height, Container* camera);

// <LegoRR.exe @004771d0>
void __cdecl Viewport_GetSize(Viewport* vp, OUT unsigned long* width, OUT unsigned long* height);

// <LegoRR.exe @00477210>
void __cdecl Viewport_SetCamera(Viewport* vp, Container* cont);

// <LegoRR.exe @00477230>
Container* __cdecl Viewport_GetCamera(Viewport* vp);

// <LegoRR.exe @00477270>
Container* __cdecl Viewport_SetBackClip(Viewport* vp, float dist);

// <LegoRR.exe @00477290>
float __cdecl Viewport_GetBackClip(Viewport* vp);

// <LegoRR.exe @004772b0>
float __cdecl Viewport_GetFrontClip(Viewport* vp);

// <LegoRR.exe @004772d0>
void __cdecl Viewport_Clear(Viewport* vp, BOOL full);

// <LegoRR.exe @00477410>
void __cdecl Viewport_Clear(Viewport* vp, Container* root, float delta);

// <LegoRR.exe @004774e0>
void __cdecl Viewport_Remove(Viewport* dead);

// <LegoRR.exe @00477500>
void __cdecl Viewport_SmoothSetField(Viewport* vp, float fov);

// <LegoRR.exe @00477510>
void __cdecl Viewport_SetField(Viewport* vp, float fov);

// <LegoRR.exe @00477530>
float __cdecl Viewport_GetField(Viewport* vp);

// <LegoRR.exe @00477550>
void __cdecl Viewport_InverseTransform(Viewport* vp, OUT VECTOR3D* dest, const VECTOR4D* src);

// <LegoRR.exe @00477570>
void __cdecl Viewport_Transform(Viewport* vp, OUT VECTOR4D* dest, const VECTOR3D* src);

// <LegoRR.exe @00477590>
VECTOR2D* __cdecl Viewport_WorldToScreen(Viewport* vp, OUT VECTOR2D* screen, const VECTOR3D* world);

// <LegoRR.exe @004775d0>
IDirect3DRMFrame3* __cdecl Viewport_GetScene(Viewport* vp);

// <LegoRR.exe @00477630>
void __cdecl Viewport_AddList(void);

// <LegoRR.exe @004776a0>
void __cdecl Viewport_RemoveAll(void);

#pragma endregion

}
