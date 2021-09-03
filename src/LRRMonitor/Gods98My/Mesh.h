#pragma once

#include "../framework.h"
#include "Maths.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Forward Declarations
 **********************************************************************************/

#pragma region Forward Declarations

struct Container_Texture;
struct APPOBJ;
struct Viewport;

#pragma endregion

/**********************************************************************************
 ******** Function Typedefs
 **********************************************************************************/

#pragma region Function Typedefs

typedef void (__cdecl* MeshRenderCallback)(Mesh* mesh, void* data, Viewport* vp);

#pragma endregion

/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define MESH_MAXTEXTURESEQENCE			100

#define MESH_MAXLISTS			20

#define MESH_TEXTURELISTSIZE		2048

#define MESH_DEFLISTSIZE			10
#define MESH_LISTINCREASE			150			// Increase list size by 150% when it is full...

#define MESH_MAXTEXTURESTAGESTATES	50

#pragma endregion

/**********************************************************************************
 ******** Enumerations
 **********************************************************************************/

#pragma region Enums

//MESH RENDER FLAGS FOR RENDER DESC
//#define MESH_FLAG_ZB_ENABLE				0x00000100
//#define MESH_FLAG_ZB_WRITE				0x00000200
#define MESH_FLAG_RENDER_ALPHA11		0x00000400
#define MESH_FLAG_RENDER_ALPHASA1		0x00000800
#define MESH_FLAG_RENDER_ALPHATRANS		0x00001000
#define MESH_FLAG_RENDER_ALPHASA0		0x20000000
#define MESH_FLAG_RENDER_ALLALPHA		(MESH_FLAG_RENDER_ALPHASA0|MESH_FLAG_RENDER_ALPHA11|MESH_FLAG_RENDER_ALPHASA1|MESH_FLAG_RENDER_ALPHATRANS)
#define MESH_FLAG_TRANSFORM_PARENTPOS	0x00002000
#define MESH_FLAG_TRANSFORM_IDENTITY	0x00004000
#define MESH_FLAG_STIPPLE				0x00008000
#define MESH_FLAG_RENDER_ALPHAMOD		0x00010000
#define MESH_FLAG_RENDER_ALPHATEX		0x00020000
#define MESH_FLAG_RENDER_ALPHADIFFUSE	0x00040000
#define MESH_FLAG_ALPHAENABLE			0x00080000
#define MESH_FLAG_TEXTURECOLOURONLY		0x00100000
#define MESH_FLAG_HASBEENCLONED			0x00200000
#define MESH_FLAG_TRANSTEXTURE			0x00400000
#define MESH_FLAG_RENDER_FILTERNEAREST	0x00800000
#define MESH_FLAG_FACECAMERA			0x01000000
#define MESH_FLAG_FACECAMERADONE		0x02000000
#define MESH_FLAG_RENDER_DOUBLESIDED	0x04000000
#define MESH_FLAG_HIGHZBIAS				0x08000000
#define MESH_FLAG_ALPHAHIDDEN			0x10000000

#define MESH_RENDERFLAGS_LWONORM		( MESH_FLAG_TRANSFORM_PARENTPOS )
#define MESH_RENDERFLAGS_LWOALPHA		( MESH_FLAG_RENDER_ALPHATRANS | MESH_FLAG_TRANSFORM_PARENTPOS )


#define MESH_FLAG_HIDDEN			0x00000001
#define MESH_FLAG_POSTEFFECT		0x00000002
#define MESH_FLAG_LWO				0x00000004

//#define MESH_DEFAULTRENDERFLAGS	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_RESERVED1 | D3DFVF_TEX1 )
#define MESH_DEFAULTRENDERFLAGS		D3DFVF_VERTEX


enum Mesh_Colour
{
	Mesh_Colour_Diffuse,
	Mesh_Colour_Ambient,
	Mesh_Colour_Specular,
	Mesh_Colour_Emissive,

	Mesh_Colour_Alpha,
	Mesh_Colour_Power
};
static_assert(sizeof(Mesh_Colour) == 0x4, "");


enum Mesh_Type
{	
	Mesh_Type_Norm,
	Mesh_Type_PostEffect,
	Mesh_Type_LightWaveObject,
};
static_assert(sizeof(Mesh_Type) == 0x4, "");


enum Mesh_WrapType 
{
	Mesh_WrapType_XAxis,
	Mesh_WrapType_YAxis,
	Mesh_WrapType_ZAxis
};
static_assert(sizeof(Mesh_WrapType) == 0x4, "");

#pragma endregion

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

//struct Container_Texture;
//typedef struct Container_Texture *lpMesh_Texture;


typedef struct lpMesh_LightWave_SurfaceTAG
{
	/*00,4*/ Container_Texture* *textureSeq;
	/*04,4*/ Container_Texture* texture;
	/*08,4*/ unsigned long numInTexSeq;
	/*0c,10*/ VECTOR4D colour;
	/*1c,4*/ float diffuse;
	/*20,4*/ float emissive;
	/*24,4*/ float specular;
	/*28,4*/ float power;
	/*2c,4*/ float transparency;
	/*30,4*/ unsigned long flags;
	/*34,4*/ unsigned long texFlags;
	/*38,4*/ long texSeqOffset;
	/*3c*/
} Mesh_LightWave_Surface, *lpMesh_LightWave_Surface;
static_assert(sizeof(Mesh_LightWave_Surface) == 0x3c, "");


typedef struct Mesh_TextureStateChangeDataTAG
{
	/*0,4*/ unsigned long origValue;
	/*4,4*/ BOOL changed;
	/*8*/
} Mesh_TextureStateChangeData , *lpMesh_TextureStateChangeData ;
static_assert(sizeof(Mesh_TextureStateChangeData) == 0x8, "");


typedef struct Mesh_RenderDescTAG
{
	/*0,4*/ MeshRenderCallback renderCallback;
	/*4,4*/ void* renderCallbackData;
	/*8,4*/ unsigned long renderFlags;
	/*c*/
} Mesh_RenderDesc, *lpMesh_RenderDesc;
static_assert(sizeof(Mesh_RenderDesc) == 0xc, "");


typedef struct Mesh_VertexTAG
{
	/*00,c*/ VECTOR3D position;
	/*0c,c*/ VECTOR3D normal;
//	unsigned long dwDiffuseRGBA;
	/*18,4*/ float tu;
	/*1c,4*/ float tv;
	/*20*/
} Mesh_Vertex, *lpMesh_Vertex;
static_assert(sizeof(Mesh_Vertex) == 0x20, "");


typedef struct Mesh_GroupTAG
{
	/*00,4*/ unsigned long faceDataSize;
	/*04,4*/ unsigned long vertexCount;
	/*08,4*/ unsigned short* faceData;
	/*0c,4*/ Mesh_Vertex* vertices;
	/*10,50*/ D3DMATERIAL material;
	/*60,4*/ IDirect3DTexture2* imText;
	/*64,4*/ unsigned long renderFlags;
	/*68,4*/ Mesh_LightWave_Surface* lightWaveSurfaceInfo;
	/*6c,4*/ unsigned long flags;
	/*70*/
} Mesh_Group, *lpMesh_Group;
static_assert(sizeof(Mesh_Group) == 0x70, "");


typedef struct Mesh
{
	/*00,4*/ unsigned long groupCount;
	/*04,4*/ unsigned long listSize;
	/*08,4*/ Mesh_Group* groupList;
	/*0c,4*/ IDirect3DRMUserVisual* uv;
	/*10,c*/ Mesh_RenderDesc renderDesc;
	/*1c,4*/ Mesh_LightWave_Surface* lightWaveSurf;
	/*20,4*/ unsigned long numOfRefs;
	/*24,4*/ Mesh* clonedFrom;
	/*28,4*/ IDirect3DRMFrame3* frameCreatedOn;
	//BOX3D boundingBox;
	/*2c,4*/ unsigned long flags;
	/*30,4*/ Mesh* nextFree;
	/*34*/
} Mesh, *lpMesh;
static_assert(sizeof(Mesh) == 0x34, "");


typedef struct Mesh_PostRenderInfoTAG
{
	/*00,4*/ Mesh* mesh;
	/*04,40*/ D3DMATRIX matWorld;
	/*44,4*/ Mesh_PostRenderInfo* next;
	/*48*/
} Mesh_PostRenderInfo, *lpMesh_PostRenderInfo;
static_assert(sizeof(Mesh_PostRenderInfo) == 0x48, "");


typedef struct Mesh_TextureReference {

	/*0,4*/ IDirectDrawSurface4* surface;
	/*4,4*/ char* path;
	/*8,4*/ BOOL trans;
	/*c*/
} Mesh_TextureReference, *lpMesh_TextureReference;
static_assert(sizeof(Mesh_TextureReference) == 0xc, "");


typedef struct Mesh_GlobsTAG
{
	/*0000,4*/ Mesh* postRenderList;
	/*0004,4*/ Mesh_PostRenderInfo* postRenderMeshList;
	/*0008,190*/ Mesh_TextureStateChangeData stateData[MESH_MAXTEXTURESTAGESTATES];
	/*0198,4*/ char* sharedTextureDir;
	/*019c,6000*/ Mesh_TextureReference textureList[MESH_TEXTURELISTSIZE];
	/*619c,6000*/ Mesh_TextureReference textureListShared[MESH_TEXTURELISTSIZE];
	/*c19c,4*/ unsigned long textureCount;
	/*c1a0,4*/ unsigned long textureCountShared;
	/*c1a4,4*/ D3DTEXTUREHANDLE oldTextureRM;
	/*c1a8,4*/ D3DMATERIALHANDLE oldMatIM;
	/*c1ac,4*/ IDirect3DTexture2* oldTextureIM;
	/*c1b0,4*/ D3DTEXTUREHANDLE currTextureRM;
	/*c1b4,4*/ D3DMATERIALHANDLE currMatIM;
	/*c1b8,4*/ IDirect3DTexture2* currTextureIM;
	/*c1bc,4*/ D3DMATERIALHANDLE matHandle;
	/*c1c0,4*/ IDirect3DMaterial3* imMat;
	//unsigned long ambientLight;
	/*c1c4,50*/ Mesh* listSet[MESH_MAXLISTS];
	/*c214,4*/ Mesh* freeList;
	/*c218,4*/ unsigned long listCount;
	/*c21c*/
} Mesh_Globs;
static_assert(sizeof(Mesh_Globs) == 0xc21c, "");

#pragma endregion

/**********************************************************************************
 ******** Globals
 **********************************************************************************/

#pragma region Globals

// <LegoRR.exe @005353c0>
extern Mesh_Globs meshGlobs;

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @00480870>
BOOL __cdecl Mesh_Initialise(const char* sharedTextureDir);

// <LegoRR.exe @00480910>
BOOL __cdecl Mesh_CreateGlobalMaterial(void);

// <LegoRR.exe @00480a40>
BOOL __cdecl Mesh_SetMaterial(D3DMATERIAL* newMaterial);

// <LegoRR.exe @00480a60>
Mesh* __cdecl Mesh_ObtainFromList(void);

// <LegoRR.exe @00480a90>
void __cdecl Mesh_ReturnToList(Mesh* dead);

// <LegoRR.exe @00480ab0>
void __cdecl Mesh_AddList(void);

// <LegoRR.exe @00480b30>
Mesh* __cdecl Mesh_CreateOnFrame(IDirect3DRMFrame3* frame, MeshRenderCallback renderFunc,
								unsigned long renderFlags, void* data, unsigned long type);

// <LegoRR.exe @00480bc0>
Mesh* __cdecl Mesh_Clone(Mesh* mesh, IDirect3DRMFrame3* frame);

// <LegoRR.exe @00480ca0>
Mesh* __cdecl Mesh_Load(const char* fname, IDirect3DRMFrame3* frame, BOOL noTextures);

// <LegoRR.exe @00480d80>
BOOL __cdecl Mesh_ParseLWO(const char* basePath, Mesh* mesh, APPOBJ* lightWaveObject, BOOL noTextures);

// <LegoRR.exe @00481ae0>
void __cdecl Mesh_GetSurfInfo(const char* basePath, APPOBJ* lightWaveObject, Mesh_LightWave_Surface* lightWaveSurf/*[]*/, BOOL noTextures);

// <LegoRR.exe @00481d80>
BOOL __cdecl Mesh_GetTextureSeqInfo(const char* tname, OUT char* tfname, OUT unsigned long* tstart, OUT unsigned long* tnumlen);

// <LegoRR.exe @00481e40>
void __cdecl Mesh_GetNextInSequence(const char* baseName, const char* nextTextName, OUT unsigned long* texNum, unsigned long tnumlen);

// <LegoRR.exe @00481f10>
void __cdecl Mesh_UViewMesh(APPOBJ* lightWaveObject, const VECTOR2D* textCoords);

// <LegoRR.exe @00482260>
void __cdecl Mesh_GetTextureUVsWrap(unsigned long vertexCount, OUT VECTOR3D* vertices, OUT VECTOR2D* coords,
	float sx, float sy, float sz, float px, float py, float pz, unsigned long flags);

// <LegoRR.exe @00482300>
BOOL __cdecl Mesh_SetTextureTime2(Mesh* mesh, float frame);

// <LegoRR.exe @00482390>
void __cdecl Mesh_Remove(Mesh* mesh, IDirect3DRMFrame3* frame);

// <LegoRR.exe @00482460>
Mesh_Group* __cdecl Mesh_GetGroup(Mesh* mesh, unsigned long groupID, OUT unsigned long* vertexCount,
								OUT unsigned long* faceCount, OUT unsigned long* vPerFace,
								OUT unsigned long* faceDataSize, OUT unsigned long* faceData);

// <LegoRR.exe @004824d0>
unsigned long __cdecl Mesh_GetGroupCount(Mesh* mesh);

// <LegoRR.exe @004824e0>
long __cdecl Mesh_AddGroup(Mesh* mesh, unsigned long vertexCount, unsigned long faceCount,
						unsigned long vPerFace, const unsigned long* faceData);

// <LegoRR.exe @00482610>
void __cdecl Mesh_AlterGroupRenderFlags(Mesh* mesh, unsigned long groupID, unsigned long newFlags);

// <LegoRR.exe @00482630>
void __cdecl Mesh_Scale(Mesh* mesh, float x, float y, float z);

// <LegoRR.exe @004826a0>
void __cdecl Mesh_SetVertices(Mesh* mesh, unsigned long groupID, unsigned long index,
							unsigned long count, const VERTEX3D* vertices);

// <LegoRR.exe @00482730>
void __cdecl Mesh_GetVertices(Mesh* mesh, unsigned long groupID, unsigned long index,
							unsigned long count, OUT VERTEX3D* vertices);

// <LegoRR.exe @004827c0>
void __cdecl Mesh_SetVertices_PointNormalAt(Mesh* mesh, unsigned long groupID, unsigned long index,
							unsigned long count, VECTOR3D* vertices, VECTOR3D* position, float (*textCoords)[2]);

// <LegoRR.exe @004828e0>
void __cdecl Mesh_SetVertices_SameNormal(Mesh* mesh, unsigned long groupID, unsigned long index,
							unsigned long count, VECTOR3D* vertices, VECTOR3D* normal, float (*textCoords)[2]);

// <LegoRR.exe @00482980>
void __cdecl Mesh_SetVertices_VNT(Mesh* mesh, unsigned long groupID, unsigned long index, unsigned long count,
								VECTOR3D* vertices, VECTOR3D** normal, VECTOR2D* textCoords);

// <LegoRR.exe @00482a40>
BOOL __cdecl Mesh_IsGroupHidden(Mesh* mesh, unsigned long groupID);

// <LegoRR.exe @00482a60>
void __cdecl Mesh_HideGroup(Mesh* mesh, unsigned long groupID, BOOL hide);

// <LegoRR.exe @00482a90>
void __cdecl Mesh_Hide(Mesh* mesh, BOOL hide);

// <LegoRR.exe @00482ab0>
BOOL __cdecl Mesh_RenderCallback(LPDIRECT3DRMUSERVISUAL lpD3DRMUV, LPVOID lpArg, D3DRMUSERVISUALREASON lpD3DRMUVreason, LPDIRECT3DRMDEVICE lpD3DRMDev, LPDIRECT3DRMVIEWPORT lpD3DRMview);

// <LegoRR.exe @00482d80>
void __cdecl Mesh_SetMeshRenderDesc(Mesh* mesh, Viewport* vp, const D3DMATRIX* matWorld, BOOL alphaBlend);

// <LegoRR.exe @00482e10>
void __cdecl Mesh_SetRenderDesc(unsigned long flags, const D3DMATRIX* matWorld, BOOL alphaBlend);

// <LegoRR.exe @00482f70>
void __cdecl Mesh_SetAlphaRender(D3DBLEND src, D3DBLEND dest);

// <LegoRR.exe @00482fa0>
void __cdecl Mesh_AddToPostRenderList(Mesh* mesh, const D3DMATRIX* matWorld);

// <LegoRR.exe @00482ff0>
void __cdecl Mesh_ClearPostRenderList(void);

// <LegoRR.exe @00483020>
void __cdecl Mesh_PostRenderAll(Viewport* vp);

// <LegoRR.exe @00483130>
Container_Texture* __cdecl Mesh_LoadTexture(const char* baseDir, const char* name, OUT unsigned long* width, OUT unsigned long* height);

// <LegoRR.exe @004832f0>
Mesh_TextureReference* __cdecl Mesh_SearchTexturePathList(Mesh_TextureReference* list, unsigned long count, const char* path);

// <LegoRR.exe @00483340>
void __cdecl Mesh_AddTexturePathEntry(Mesh_TextureReference* list, IN OUT unsigned long* count, const char* path, IDirectDrawSurface4* surface, BOOL trans);

// <LegoRR.exe @00483380>
void __cdecl Mesh_SetGroupTexture(Mesh* mesh, unsigned long groupID, Container_Texture* mt);

// <LegoRR.exe @00483400>
void __cdecl Mesh_RemoveGroupTexture(Mesh* mesh, unsigned long groupID);

// <LegoRR.exe @00483430>
BOOL __cdecl Mesh_CreateGroupMaterial(Mesh* mesh, unsigned long groupID);

// <LegoRR.exe @00483500>
BOOL __cdecl Mesh_SetGroupMaterial(Mesh* mesh, unsigned long groupID, const D3DMATERIAL* mat);

// <LegoRR.exe @00483530>
BOOL __cdecl Mesh_SetGroupColour(Mesh* mesh, unsigned long groupID, float r, float g, float b, unsigned long type);

// <LegoRR.exe @004836c0>
const D3DMATERIAL* __cdecl Mesh_GetGroupMaterial(Mesh* mesh, unsigned long groupID);

// <LegoRR.exe @004836e0>
BOOL __cdecl Mesh_SetGroupMaterialValues(Mesh* mesh, unsigned long groupID, float value, unsigned long type);

// <LegoRR.exe @00483800>
void __cdecl Mesh_SetIdentityMatrix(OUT MATRIX4D m);

// <LegoRR.exe @00483840>
BOOL __cdecl Mesh_SetCurrentViewport(IDirect3DRMViewport* view);

// <LegoRR.exe @004838c0>
BOOL __cdecl Mesh_SetCurrentGODSViewport(Viewport* vp);

/// TODO: is this the correct matrix ptr level?
//BOOL __cdecl Mesh_SetTransform(D3DTRANSFORMSTATETYPE state, MATRIX4D* matrix);
// <LegoRR.exe @00483950>
BOOL __cdecl Mesh_SetTransform(D3DTRANSFORMSTATETYPE state, const MATRIX4D matrix);

// <LegoRR.exe @00483ad0>
BOOL __cdecl Mesh_ChangeTextureStageState(D3DTEXTURESTAGESTATETYPE dwRenderStateType, unsigned long dwRenderState);

// <LegoRR.exe @00483b70>
void __cdecl Mesh_StoreTextureAndMat(void);

// <LegoRR.exe @00483c00>
void __cdecl Mesh_RestoreTextureAndMat(void);

// <LegoRR.exe @00483c80>
BOOL __cdecl Mesh_RenderMesh(Mesh* mesh, const D3DMATRIX* matWorld, BOOL alphaBlend);

// <LegoRR.exe @00483d30>
BOOL __cdecl Mesh_CanRenderGroup(Mesh_Group* group);

// <LegoRR.exe @00483d50>
BOOL __cdecl Mesh_RenderGroup(Mesh* mesh, Mesh_Group* group, const D3DMATRIX* matWorld, BOOL alphaBlend);

// <LegoRR.exe @00483dc0>
BOOL __cdecl Mesh_SetGroupRenderDesc(Mesh* mesh, Mesh_Group* group, const D3DMATRIX* matWorld, BOOL alphaBlend);

// <LegoRR.exe @00483e30>
BOOL __cdecl Mesh_RenderTriangleList(D3DMATERIALHANDLE matHandle, IDirect3DTexture2* texture, unsigned long renderFlags,
	Mesh_Vertex* vertices, unsigned long vertexCount, unsigned short* faceData, unsigned long indexCount);

#pragma endregion

}
