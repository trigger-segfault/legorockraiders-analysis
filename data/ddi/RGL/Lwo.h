
#ifndef _RGL_LWO_H_
#define _RGL_LWO_H_

#include "Maths.h"

#define LWO_FILESUFFIX						".lwo"

#define LWO_MAGIC_FORM						'MROF'
#define LWO_MAGIC_LWOB						'BOWL'
#define LWO_MAGIC_PNTS						'STNP'
#define LWO_MAGIC_SRFS						'SFRS'
#define LWO_MAGIC_SURF						'FRUS'
#define LWO_MAGIC_CRVS						'SVRC'
#define LWO_MAGIC_POLS						'SLOP'
#define LWO_MAGIC_COLR						'RLOC'
#define LWO_MAGIC_FLAG						'GALF'
#define LWO_MAGIC_TIMG						'GMIT'
#define LWO_MAGIC_TFLG						'GLFT'
#define LWO_MAGIC_TSIZ						'ZIST'
#define LWO_MAGIC_TCTR						'RTCT'
#define LWO_MAGIC_TREF						'FERT'

#define LWO_ULONG(n)						(((n)<<24)|(((n)<<8)&0x00ff0000)|(((n)>>8)&0x0000ff00)|(((n)>>24)))
#define LWO_UWORD(n)						((UWORD) ((((UWORD)(n))<<8)|(((UWORD)(n))>>8)))
__inline REAL LWO_REAL(ULONG n)				{ ULONG temp = LWO_ULONG(n); return *((LPREAL) &temp); }

#define LWO_TEXTUREFLAG_XAXIS				0x0001
#define LWO_TEXTUREFLAG_YAXIS				0x0002
#define LWO_TEXTUREFLAG_ZAXIS				0x0004
#define LWO_TEXTUREFLAG_WORLDCOORD			0x0008
#define LWO_TEXTUREFLAG_NEGATIVEIMAGE		0x0010
#define LWO_TEXTUREFLAG_PIXELBLENDING		0x0020
#define LWO_TEXTUREFLAG_ANTIALIASING		0x0040
#define LWO_TEXTUREFLAG_SEQUENCE			0x0080
#define LWO_TEXTUREFLAG_MAX					0x0100

#define LWO_SURFACEFLAG_LUMINOUS			0x0001
#define LWO_SURFACEFLAG_OUTLINE				0x0002
#define LWO_SURFACEFLAG_SMOOTHING			0x0004
#define LWO_SURFACEFLAG_COLOURHIGHLIGHTS	0x0008
#define LWO_SURFACEFLAG_COLOURFILTER		0x0010
#define LWO_SURFACEFLAG_OPAQUEEDGE			0x0020
#define LWO_SURFACEFLAG_TRANSPARENTEDGE		0x0040
#define LWO_SURFACEFLAG_SHARPTERMINATOR		0x0080
#define LWO_SURFACEFLAG_DOUBLESIDED			0x0100
#define LWO_SURFACEFLAG_ADDITIVE			0x0200

#define LWO_MAXVERTEXSURFACE				10

struct LwoPoly {

	ULONG pointCount;
	ULONG polyIndex;
	ULONG surface;
	VECTOR3D normal;
};

struct LwoSurface {

	LPUCHAR name;
	ULONG nameSkip;
	COLOUR colour;
	UWORD flags, textureFlags;
	LPUCHAR texture;
	VECTOR3D textureSize;
	VECTOR3D textureCenter;
};

struct Lwo {

	LPVECTOR3D pointList;
	LPVECTOR3D normalList;
	struct LwoPoly *polyList;
	struct LwoSurface *surfaceList;
	LPUWORD polyData;
	LPUCHAR nameData;
	LPUCHAR path;

	ULONG pointCount, polyCount, polyDataSize, surfaceCount;
};

struct LwoSplitSurfaceData {

	ULONG sharingSurfaces[LWO_MAXVERTEXSURFACE];
	ULONG remapVertex[LWO_MAXVERTEXSURFACE];
	ULONG sharingCount;
};

typedef struct Lwo						*lpLwo;
typedef struct LwoPoly					*lpLwoPoly;
typedef struct LwoSurface				*lpLwoSurface;
typedef struct LwoSplitSurfaceData		*lpLwoSplitSurfaceData;

// Auto Prototypes
extern unsigned __int64 __stdcall Int64ShllMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern __int64 __stdcall Int64ShraMod32(__int64 Value,unsigned long ShiftCount);
extern unsigned __int64 __stdcall Int64ShrlMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern void *__cdecl GetFiberData(void );
extern void *__cdecl GetCurrentFiber(void );
extern float __cdecl LWO_REAL(unsigned long n);
extern struct Lwo *__cdecl Lwo_Load(unsigned char *fname);
extern void __cdecl Lwo_Free(struct Lwo *lwo);
static void __cdecl Lwo_ParsePoints(struct Lwo *lwo,unsigned long *list,unsigned long chunkSize);
static void __cdecl Lwo_ParsePolys(struct Lwo *lwo,unsigned short *list,unsigned long chunkSize);
static void __cdecl Lwo_ParseSurfaceNames(struct Lwo *lwo,unsigned char *list,unsigned long chunkSize);
static void __cdecl Lwo_ParseSurfaceInfo(struct Lwo *lwo,unsigned char *list,unsigned long chunkSize);
static void __cdecl Lwo_ParseSurfaceSubChunk(struct LwoSurface *surface,unsigned long type,unsigned long *data);
static void __cdecl Lwo_GenerateFaceNormals(struct Lwo *lwo);
extern void __cdecl Lwo_GenerateNormals(struct Lwo *lwo);
extern void __cdecl Lwo_GetUV(struct LwoSurface *surface,struct VECTOR3D *point,float *tu,float *tv);
extern struct Mesh *__cdecl Lwo_BuildMesh(struct Lwo *lwo,unsigned long maxVertexShare,unsigned long blendLevels);
extern struct Mesh *__cdecl Lwo_BuildMeshVertexUV(struct Lwo *lwo,unsigned long blendLevels);
extern struct Mesh *__cdecl Lwo_BuildMeshPolyUV(struct Lwo *lwo,unsigned long maxVertexShare,unsigned long blendLevels);
// Auto Prototypes

#endif // !_RGL_LWO_H_
