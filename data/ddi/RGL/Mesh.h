
#ifndef _RGL_MESH_H_
#define _RGL_MESH_H_

#include "Maths.h"
#include "Textures.h"
#include "Viewports.h"

#define MESH_MINPOLYSIDES					3
#define MESH_MAXPOLYSIDES					3
#define MESH_RENDERLISTSIZE					1000

#define MESH_FLAG_HIDDEN					0x0001
#define MESH_FLAG_HIDEPOLYCALLED			0x0002
#define MESH_FLAG_MULTIREFERENCE			0x0004
#define MESH_FLAG_OPTIMISED					0x0008

#define MESH_GROUPFLAG_HIDDEN				0x0001
#define MESH_GROUPFLAG_NONEVISIBLE			0x0002
//#define MESH_GROUPFLAG_SUBTRACTIVE			0x0004
//#define MESH_GROUPFLAG_ADDITIVE1			0x0008
#define MESH_GROUPFLAG_ZTESTDISABLED		0x0010
#define MESH_GROUPFLAG_ZWRITEDISABLED		0x0020

#define MESH_GROUPFLAG_ZBIASMASK			0xff000000
#define MESH_GROUPFLAG_ZBIASSHIFT			24

#define MESH_CLONEFLAG_HIDDENFACEDATA		0x0001
#define MESH_CLONEFLAG_GROUPS				0x0002
#define MESH_CLONEFLAG_FACEDATA				0x0004
#define MESH_CLONEFLAG_VERTICES				0x0008
#define MESH_CLONEFLAG_TRANSFORMEDVERTICES	0x0010
#define MESH_CLONEFLAG_ADDFACES				0x0020
#define MESH_CLONEFLAG_COMPLETE				0x0040
#define MESH_CLONEFLAG_VERTEXLISTLIST		0x0080

#define MESH_FACEFLAG_FRESH					0x01		// Has be freshly introduced to the scene...
#define MESH_FACEFLAG_HIDDEN				0x02

#define MESH_VERTEXLISTFLAG_TRANSFORMED		0x00000001

//#define MESH_VERTEX_FLAGS					(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1|D3DFVF_DIFFUSE)
#define MESH_VERTEX_FLAGS					(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

#define MESH_VERTEXFLAG_DIFFUSE				0x00000001
#define MESH_VERTEXFLAG_SPECULAR			0x00000002
#define MESH_VERTEXFLAG_NORMAL				0x00000004

#ifdef _RGL

struct MeshGroup {

//	struct Mesh *mesh;

	LPUWORD faceData;
	LPUWORD visibleFaceData;

	UWORD visibleFaceDataSize, totalFaceDataSize, usedFaceDataSize;
	UWORD vPerFace;

	lpTexture texture[D3DDP_MAXTEXCOORD];
	D3DMATERIAL7 material;

	ULONG vertexListIndex;

	UWORD flags, renderFlags;
};

struct MeshFace {

	UWORD group, listIndex;
	UCHAR flags;
};

struct MeshRenderEntry {

	struct Mesh *mesh;
	struct MeshGroup *group;
	struct Frame *frame;
};

#endif // _RGL

struct MeshVertexInfo {

	ULONG size;
	ULONG srcFlags, destFlags;
	ULONG blendPos, normalPos;
	ULONG diffusePos, specularPos;
	ULONG uvPos;						// Only 2d uv's at the moment...
	ULONG blendCount, uvCount;
};

#ifdef _RGL

struct Mesh {

	ULONG referenceCount;

	struct MeshFace *faceArray;
	struct MeshGroup *groupList;

	UWORD groupCount;
	UWORD faceCount, totalFaceCount;
//	UWORD currGroup;

	ULONG maxVertexShare;			// Zero to represent single uv, unrestrained vertex sharing...

	struct Lws *boneScene;
	struct LwsBone *boneList;

	struct MeshVertexList *vertexListList;
	ULONG vertexListCount;

	struct Mesh *cloneChainNext, *clonedFrom;

	UWORD flags, cloneFlags;
};

struct MeshVertexList {

	LPDIRECT3DVERTEXBUFFER7 vertexBuffer;
	LPDIRECT3DVERTEXBUFFER7 visibleVertexBuffer;
	LPDIRECT3DVERTEXBUFFER7 transformedVertexBuffer;
	LPUCHAR vertexBufferMemory;
	ULONG vertexBufferLockCount;

	LPUCHAR vertexRefCount;
	LPUWORD vertexRemapData;
	LPUWORD vertexIncludedData;
	UWORD visibleVertexCount, totalVertexCount, usedVertexCount, internallyUsedVertexCount;
	struct MeshVertexInfo vertexInfo;

	ULONG flags;
};

#endif // _RGL

typedef struct Mesh							*lpMesh;
typedef struct MeshFace						*lpMeshFace;
typedef struct MeshGroup					*lpMeshGroup;
typedef struct MeshVertexInfo				*lpMeshVertexInfo;
typedef struct MeshVertexList				*lpMeshVertexList;
typedef struct MeshRenderEntry				*lpMeshRenderEntry;

#ifndef _AUTOPROTOTYPES
// Auto Prototypes
extern unsigned __int64 __stdcall Int64ShllMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern __int64 __stdcall Int64ShraMod32(__int64 Value,unsigned long ShiftCount);
extern unsigned __int64 __stdcall Int64ShrlMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern void *__cdecl GetFiberData(void );
extern void *__cdecl GetCurrentFiber(void );
extern float __cdecl LWO_REAL(unsigned long n);
extern void __cdecl Mesh_Initialise(void );
extern void __cdecl Mesh_Shutdown(void );
extern void __cdecl Mesh_GetVertexInfo(struct MeshVertexInfo *info,int transformed,unsigned long textureCount,unsigned long blendCount,unsigned long flags);
extern unsigned long __cdecl Mesh_AddVertexList(struct Mesh *mesh,unsigned long vertexCount,struct MeshVertexInfo *vertexInfo);
extern VOID __cdecl Mesh_Optimise(lpMesh mesh);
extern struct Mesh *__cdecl Mesh_Create(unsigned long totalFaceCount,unsigned long maxVertexShare, int multiReference);
static int __cdecl Mesh_CopyVertexBuffer(struct IDirect3DVertexBuffer7 *dest,struct IDirect3DVertexBuffer7 *src,struct MeshVertexInfo *info,unsigned long destStart,unsigned long srcStart,unsigned long count);
extern struct Mesh *__cdecl Mesh_Clone(struct Mesh *original,unsigned long flags);
extern void __cdecl Mesh_Restore(struct Mesh *clone,int attributes);
static void __cdecl Mesh_RemoveClone(struct Mesh *clone);
extern int __cdecl Mesh_Remove(struct Mesh *dead, int removeTextures);
extern struct Mesh *__cdecl Mesh_Load(unsigned char *fname,unsigned long maxVertexShare,unsigned long blendLevels,int useNormals, int useShared,int *original);
extern unsigned short __cdecl Mesh_CreateGroup(struct Mesh *mesh,unsigned long vertexListIndex,unsigned long vPerFace,unsigned long faces);
extern void __cdecl Mesh_AllocateHideInfo(struct Mesh *mesh,unsigned long *maxVisibleVertices);
extern int __cdecl Mesh_LockVertices(struct Mesh *mesh,int lock);
extern int __cdecl Mesh_LockVertices_Index(struct Mesh *mesh,unsigned long index,int lock);
extern void __cdecl Mesh_SetVertexScreenPosition(struct Mesh *mesh,unsigned long index,unsigned short vertex,struct VECTOR4D *position);
extern void __cdecl Mesh_SetVertexPosition(struct Mesh *mesh,unsigned long vertexListIndex,unsigned long vertex,struct VECTOR3D *position);
extern void __cdecl Mesh_SetVertexColour(struct Mesh *mesh,unsigned long vertexListIndex,unsigned long vertex,COLOUR colour);
extern struct VECTOR3D *__cdecl Mesh_GetVertexPosition(struct Mesh *mesh,unsigned long vertexListIndex,unsigned long vertex);
extern VOID *__cdecl Mesh_GetVertexBuffer(struct Mesh *mesh,unsigned long vertexListIndex,unsigned long vertex);
extern void __cdecl Mesh_SetBlendLevel(struct Mesh *mesh,unsigned long vertexListIndex,unsigned long vertex,unsigned long blendIndex,float level);
extern float __cdecl Mesh_GetBlendLevel(struct Mesh *mesh,unsigned long vertexListIndex,unsigned long vertex,unsigned long blendIndex);
extern void __cdecl Mesh_SetVertexNormal(struct Mesh *mesh,unsigned long index,unsigned long vertex,struct VECTOR3D *normal);
extern void __cdecl Mesh_SetVertexUV(struct Mesh *mesh,unsigned long index,unsigned long vertex,unsigned long uvIndex,float tu,float tv);
extern void __cdecl Mesh_SetPolyUV(struct Mesh *mesh,unsigned long vertexListIndex,unsigned long poly,unsigned long uvIndex,float *tu,float *tv);
extern void __cdecl Mesh_SetTexture(struct Mesh *mesh,unsigned long groupID,unsigned long textureIndex,struct Texture *texture);
extern struct Texture *__cdecl Mesh_GetTexture(struct Mesh *mesh,unsigned long groupID,unsigned long textureIndex);
extern void __cdecl Mesh_HidePoly(struct Mesh *mesh,unsigned short poly,int hide);
extern unsigned short __cdecl Mesh_GetGroupCount(struct Mesh *mesh);
extern unsigned long __cdecl Mesh_GetVertexListCount(struct Mesh *mesh);
extern unsigned short __cdecl Mesh_GetVertexCount(struct Mesh *mesh,unsigned long vertexListIndex);
extern VOID __cdecl Mesh_GetVertexUV(lpMesh mesh, ULONG vertexListIndex, ULONG vertex, ULONG uvIndex, REAL *tu, REAL *tv);
extern void __cdecl Mesh_GetBox(struct Mesh *mesh,struct BOX3D *box);
extern void __cdecl Mesh_Translate(struct Mesh *mesh,struct VECTOR3D *offset);
extern void __cdecl Mesh_Scale(struct Mesh *mesh,struct VECTOR3D *scale);
extern unsigned long __cdecl Mesh_GetTotalFaceCount(struct Mesh *mesh);
extern struct VECTOR3D *__cdecl Mesh_GetPolyVertex(struct Mesh *mesh,unsigned long poly,unsigned long index);
extern struct VECTOR3D *__cdecl Mesh_CalculatePolyNormal(struct Mesh *mesh,unsigned long poly,struct VECTOR3D *normal);
extern unsigned short __cdecl Mesh_GetPolyShape(struct Mesh *mesh,unsigned long poly,struct VECTOR3D *shape);
extern void __cdecl Mesh_AddTriangle(struct Mesh *mesh,unsigned long groupID,unsigned short *index);
extern void __cdecl Mesh_Update(struct Mesh *mesh,int hideUnfresh);
extern void __cdecl Mesh_Reset(struct Mesh *mesh);
static void __cdecl Mesh_IncludePoly(struct Mesh *mesh,struct MeshGroup *group,struct MeshFace *face);
extern void __cdecl Mesh_SetBoneList(struct Mesh *mesh,struct Lws *lws,struct LwsBone *boneList);
extern void __cdecl Mesh_AddToRenderList(struct Mesh *mesh,struct Frame *frame);
extern unsigned long __cdecl Mesh_RenderList(ULONG ambientColour);
static void __cdecl Mesh_ClearRenderList(void );
extern int __cdecl Mesh_RenderListSortCallback(const void *a,const void *b);
extern void __cdecl Mesh_TestCode_ClipTest(void );
extern ULONG __cdecl Mesh_GetFaceDataSize(lpMesh mesh, ULONG groupID);
extern LPUWORD __cdecl Mesh_GetFaceData(lpMesh mesh, ULONG groupID);
extern ULONG __cdecl Mesh_GetVertexListIndex(lpMesh mesh, ULONG groupID);
//extern VOID __cdecl Mesh_SetGroupColour(lpMesh mesh, ULONG groupID, REAL r, REAL g, REAL b);
extern VOID __cdecl Mesh_SetGroupAlpha(lpMesh mesh, ULONG groupID, REAL a);
//extern VOID __cdecl Mesh_SetGroupSubtractive(lpMesh mesh, ULONG groupIndex, BOOL on);
extern VOID __cdecl Mesh_SetGroupRenderFlags(lpMesh mesh, ULONG groupIndex, ULONG flags, BOOL set);
extern VOID __cdecl Mesh_SetZBufferMode(lpMesh mesh, ULONG groupIndex, BOOL test, BOOL write);
extern VOID __cdecl Mesh_BeginRender(ULONG ambientColour);
extern ULONG __cdecl Mesh_RenderGroup(struct Mesh *mesh, struct MeshGroup *group, struct Frame *frame, struct Frame *lastRenderedFrame);
extern VOID __cdecl Mesh_EndRender(VOID);
// Auto Prototypes
#endif // !_AUTOPROTOTYPES

#endif // !_RGL_MESH_H_

