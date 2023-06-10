
#ifndef _RGL_UVIEW_H_
#define _RGL_UVIEW_H_

#define UVIEW_FILESUFFIX						".uv"
#define UVIEW_MAXARGS							10
#define UVIEW_MAXCHANNELS						8
#define UVIEW_VERTEXLISTBLOCKSIZE				100

#define UVIEW_MAXPOLYSIDES						4

#define UVIEW_NORMALTOLERANCE					0.01f
#define UVIEW_UVTOLERANCE						0.01f

#define UVIEWVERTEX_FLAG_UV						0x0000001
#define UVIEWVERTEX_FLAG_NORMAL					0x0000002
#define UVIEWVERTEX_FLAG_COLOUR					0x0000004

#define UVIEWSURFACE_FLAG_ADDITIVE				0x0000001
#define UVIEWSURFACE_FLAG_SUBTRACTIVE			0x0000002

struct UViewVertex {

	REAL u, v;
	VECTOR3D position;
	VECTOR3D normal;
	COLOUR colour;

	ULONG polyIndex;
	ULONG useVertex;
	ULONG flags;
};

struct UViewPoly {

	ULONG surface;
	ULONG vertexCount;
	ULONG vertexListIndex;
};

struct UViewChannel {

	LPUCHAR fileName;
	struct Texture *texture;
	ULONG flags;
};

typedef struct UViewChannel				UViewSurface[UVIEW_MAXCHANNELS];

struct UView {

	LPUCHAR path;

	UViewSurface *surfaceList;

	ULONG surfaceCount, polyCount;
	struct UViewPoly *polyList;

	struct UViewVertex *vertexGlobalList;
	ULONG vertexGlobalListSize, vertexGlobalCount;
};

typedef struct UView				*lpUView;
typedef struct UViewPoly			*lpUViewPoly;
typedef struct UViewVertex			*lpUViewVertex;
typedef struct UViewChannel			*lpUViewChannel;

// Auto Prototypes
extern float __cdecl LWO_REAL(unsigned long n);
extern unsigned __int64 __stdcall Int64ShllMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern __int64 __stdcall Int64ShraMod32(__int64 Value,unsigned long ShiftCount);
extern unsigned __int64 __stdcall Int64ShrlMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern void *__cdecl GetFiberData(void );
extern void *__cdecl GetCurrentFiber(void );
extern struct Mesh *__cdecl UView_MakeMesh(struct Lwo *lwo,unsigned char *fname, unsigned long blendCount, int useNormals);
static void __cdecl UView_GetVertexList(struct UView *uView,struct UViewPoly *poly);
static struct UView *__cdecl UView_ParseFile(struct Lwo *lwo,unsigned char *fname);
static void __cdecl UView_Free(struct UView *uView);
extern BOOL __cdecl UView_UVEqual(REAL ua, REAL va, REAL ub, REAL vb);
extern BOOL __cdecl UView_NormalEqual(LPVECTOR3D a, LPVECTOR3D b);
extern BOOL __cdecl UView_PositionEqual(LPVECTOR3D a, LPVECTOR3D b, REAL tolerance);
// Auto Prototypes

#endif // !_RGL_UVIEW_H_
