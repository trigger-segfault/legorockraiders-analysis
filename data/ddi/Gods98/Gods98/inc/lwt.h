
#ifndef _LWT_H_
#define _LWT_H_

#include "..\inc\Files.h"


typedef struct
{
	ULONG lwVertCount;
	ULONG lwPolyCount;
	ULONG lwSurfaceCount;

} LWSIZE;


typedef struct
{
	ULONG plyCount;
	ULONG plySurface;
	WORD *plyData;

} LWPOLY;


typedef struct
{
	UCHAR colRed;
	UCHAR colGreen;
	UCHAR colBlue;
	UCHAR colAlpha;

} LWRGB;


typedef struct
{
	REAL tdX;
	REAL tdY;
	REAL tdZ;

} TEXDATA;


typedef struct _LWSURFACE
{
	UCHAR	*srfName;
	struct _LWSURFACE *srfNextSurf;
	UCHAR	*srfPath;
	LWRGB	srfCol;
	UCHAR	srfTCLR[4];
	ULONG	srfTexFlags;
	ULONG	srfFlags;
	ULONG	srfTexType;
	ULONG	srfTexWrap;
	TEXDATA srfTexSize;
	TEXDATA srfTexCentre;
	REAL srfLuminous;
	REAL srfTransparent;
	REAL srfDiffuse;
	REAL srfReflect;
	REAL srfSpecular;
	REAL srfSpecPower;

} LWSURFACE;


typedef struct APPOBJTAG
{
	UCHAR		*aoPath;
	LWSIZE		aoSize;
	REAL		*aoVerts;
	LWPOLY		*aoPoly;
	LWSURFACE	*aoSurface;

	lpFile aoFileUV;

} APPOBJ;


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


BOOL LoadLWOB(UCHAR *fn, LWSIZE *size, REAL **verts, LWPOLY **polys, LWSURFACE **surf, lpFile *fileUV, BOOL dflag);
BOOL FreeLWOB(APPOBJ *ao);

BOOL LoadAppObj(UCHAR *fn, APPOBJ **ao, BOOL flag);

#endif _LWT_H_
