#pragma once

#include "../framework.h"
#include "Files.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define LBUF_LEN 256

#pragma endregion

 /**********************************************************************************
  ******** Enumerations
  **********************************************************************************/

#pragma region Enums

// srfTexFlags bit enumeration
enum
{
	TF_AXIS_X = 0,
	TF_AXIS_Y,
	TF_AXIS_Z,
	TF_WORLD_COORD,
	TF_NEGATIVE_IMAGE,
	TF_PIXEL_BLENDING,
	TF_ANTIALIASING,
	TF_SEQUENCE,
	TF_MAX,
};

#define	TFM_AXIS_X				(1<<TF_AXIS_X)
#define	TFM_AXIS_Y				(1<<TF_AXIS_Y)
#define	TFM_AXIS_Z				(1<<TF_AXIS_Z)
#define	TFM_WORLD_COORD			(1<<TF_WORLD_COORD)
#define	TFM_NEGATIVE_IMAGE		(1<<TF_NEGATIVE_IMAGE)
#define	TFM_PIXEL_BLENDING		(1<<TF_PIXEL_BLENDING)
#define	TFM_ANTIALIASING		(1<<TF_ANTIALIASING)
#define	TFM_SEQUENCE			(1<<TF_SEQUENCE)


// srfFlags bit enumeration
enum
{
    SF_LUMINOUS = 0,
	SF_OUTLINE,
	SF_SMOOTHING,
	SF_COLORHIGHLIGHTS,
	SF_COLORFILTER,
    SF_OPAQUEEDGE,			//\ These two should not be set together
	SF_TRANSPARENTEDGE,		///
	SF_SHARPTERMINATOR,
	SF_DOUBLESIDED,
    SF_ADDITIVE,
	SF_MAX,
};

#define SFM_LUMINOUS				(1<<SF_LUMINOUS)
#define SFM_OUTLINE					(1<<SF_OUTLINE)
#define SFM_SMOOTHING				(1<<SF_SMOOTHING)
#define SFM_COLORHIGHLIGHTS			(1<<SF_COLORHIGHLIGHTS)
#define SFM_COLORFILTER				(1<<SF_COLORFILTER)
#define SFM_OPAQUEEDGE				(1<<SF_OPAQUEEDGE)
#define SFM_TRANSPARENTEDGE			(1<<SF_TRANSPARENTEDGE)
#define SFM_SHARPTERMINATOR			(1<<SF_SHARPTERMINATOR)
#define SFM_DOUBLESIDED				(1<<SF_DOUBLESIDED)
#define SFM_ADDITIVE				(1<<SF_ADDITIVE)


enum
{
	MT_PLANAR = 0,
	MT_CYLINDRICAL,
	MT_SPHERICAL,
	MT_MAX
};

#pragma endregion

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

typedef struct
{
	/*0,4*/ unsigned long srflCount;
	/*4,4*/ char** srflName;
	/*8*/
} LWSURFLIST;
static_assert(sizeof(LWSURFLIST) == 0x8, "");


typedef struct
{
	/*0,4*/ unsigned long lwVertCount;
	/*4,4*/ unsigned long lwPolyCount;
	/*8,4*/ unsigned long lwSurfaceCount;
	/*c*/
} LWSIZE;
static_assert(sizeof(LWSIZE) == 0xc, "");


typedef struct
{
	/*0,4*/ unsigned long plyCount;
	/*4,4*/ unsigned long plySurface;
	/*8,4*/ unsigned short* plyData;
	/*c*/
} LWPOLY;
static_assert(sizeof(LWPOLY) == 0xc, "");


typedef struct
{
	/*0,1*/ unsigned char colRed;
	/*1,1*/ unsigned char colGreen;
	/*2,1*/ unsigned char colBlue;
	/*3,1*/ unsigned char colAlpha;
	/*4*/
} LWRGB;
static_assert(sizeof(LWRGB) == 0x4, "");


typedef struct
{
	/*0,4*/ float tdX;
	/*4,4*/ float tdY;
	/*8,4*/ float tdZ;
	/*c*/
} TEXDATA;
static_assert(sizeof(TEXDATA) == 0xc, "");


typedef struct _LWSURFACE
{
	/*00,4*/ char*	srfName;
	/*04,4*/ LWSURFACE* srfNextSurf;
	/*08,4*/ char*	srfPath;
	/*0c,4*/ LWRGB	srfCol;
	/*10,4*/ char	srfTCLR[4];
	/*14,4*/ unsigned long	srfTexFlags;
	/*18,4*/ unsigned long	srfFlags;
	/*0c,4*/ unsigned long	srfTexType;
	/*20,4*/ unsigned long	srfTexWrap;
	/*24,c*/ TEXDATA srfTexSize;
	/*30,c*/ TEXDATA srfTexCentre;
	/*3c,4*/ float srfLuminous;
	/*40,4*/ float srfTransparent;
	/*44,4*/ float srfDiffuse;
	/*48,4*/ float srfReflect;
	/*4c,4*/ float srfSpecular;
	/*50,4*/ float srfSpecPower;
	/*54*/
} LWSURFACE;
static_assert(sizeof(LWSURFACE) == 0x54, "");


typedef struct APPOBJTAG
{
	/*00,4*/ char*		aoPath;
	/*04,c*/ LWSIZE		aoSize;
	/*10,4*/ float*		aoVerts;
	/*14,4*/ LWPOLY*	aoPoly;
	/*18,4*/ LWSURFACE*	aoSurface;
	/*1c,4*/ File_Dummy* aoFileUV;
	/*20*/
} APPOBJ;
static_assert(sizeof(APPOBJ) == 0x20, "");

#pragma endregion

/**********************************************************************************
 ******** Macros
 **********************************************************************************/

#pragma region Macros

#define LWVALUE(n) (((n>>24)&0xff) + ((n>>8)&0xff00) + ((n<<8)&0xff0000) + ((n<<24)&0xff000000))
#define LWSVALUE(n) (((n>>8)&0xff) + ((n<<8)&0xff00))
#define LWSPVALUE(n) ((((*n)>>8)&0xff) + (((*n)<<8)&0xff00))

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @0048c300>
char* __cdecl lwExtractString(const char* str1, const char* str2, OPTIONAL OUT unsigned long* pos, OPTIONAL OUT unsigned long* len);

// "YASD" Yet another `char* ::_strdup(const char*)`
// <LegoRR.exe @0048c380>
char* __cdecl stringAlloc(const char* str);

// <LegoRR.exe @0048c3e0>
unsigned long __cdecl texMapType(const char* str);

// <LegoRR.exe @0048c440>
void __cdecl surfFree(LWSURFACE* srf, BOOL flag);

// <LegoRR.exe @0048c490>
BOOL __cdecl LWD3D(unsigned char** p, float* f);

// <LegoRR.exe @0048c4d0>
BOOL __cdecl PNTSprc(File_Dummy* file, LWSIZE* sizeData, long csize, float** verts, BOOL dflag);

// <LegoRR.exe @0048c620>
BOOL __cdecl CRVSprc(File_Dummy* file, long csize, BOOL dflag);

// <LegoRR.exe @0048c6a0>
BOOL __cdecl POLSprc(File_Dummy* file, LWSIZE* sizeData, LWPOLY** polys, long csize, BOOL dflag);

// <LegoRR.exe @0048c950>
BOOL __cdecl SRFSprc(File_Dummy* file, LWSIZE* sizeData, LWSURFLIST** srfl, long csize, OUT unsigned long* srflCount, BOOL dflag);

// <LegoRR.exe @0048cae0>
BOOL __cdecl SURFprc(File_Dummy* file, LWSIZE* sizeData, LWSURFACE** surf, long csize, BOOL dflag);

// <LegoRR.exe @0048d580>
BOOL __cdecl LoadLWOB(const char* fn, LWSIZE* size, float** verts, LWPOLY** polys, LWSURFACE** surf, File_Dummy** fileUV, BOOL dflag);

// <LegoRR.exe @0048da80>
BOOL __cdecl LoadAppObj(const char* fn, APPOBJ** ao, BOOL flag);

// <LegoRR.exe @0048db30>
BOOL __cdecl FreeLWOB(APPOBJ* ao);

#pragma endregion

}
