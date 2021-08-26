
#ifndef _GODS98_MESH_H_
#define _GODS98_MESH_H_

#define MESH_MAXTEXTURESEQENCE			100

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


#define MESH_MAXLISTS			20


#define MESH_TEXTURELISTSIZE		2048



enum Mesh_Colour
{
	Mesh_Colour_Diffuse,
	Mesh_Colour_Ambient,
	Mesh_Colour_Specular,
	Mesh_Colour_Emissive,

	Mesh_Colour_Alpha,
	Mesh_Colour_Power

};


enum Mesh_Type
{	
	Mesh_Type_Norm,
	Mesh_Type_PostEffect,
	Mesh_Type_LightWaveObject,

};


enum Mesh_WrapType 
{
	Mesh_WrapType_XAxis,
	Mesh_WrapType_YAxis,
	Mesh_WrapType_ZAxis

};



typedef struct Container_Texture *lpMesh_Texture;

#ifdef _GODS98COMPILE

#include "..\Inc\Maths.h"
#include "..\Inc\Viewports.h"
#include "..\Inc\lwt.h"



#define MESH_DEFLISTSIZE			10
#define MESH_LISTINCREASE			150			// Increase list size by 150% when it is full...


#define MESH_FLAG_HIDDEN			0x00000001
#define MESH_FLAG_POSTEFFECT		0x00000002
#define MESH_FLAG_LWO				0x00000004


#define MESH_MAXTEXTURESTAGESTATES	50


//#define MESH_DEFAULTRENDERFLAGS	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_RESERVED1 | D3DFVF_TEX1 )
#define MESH_DEFAULTRENDERFLAGS		D3DFVF_VERTEX



typedef struct lpMesh_LightWave_SurfaceTAG
{
	lpMesh_Texture *textureSeq;
	lpMesh_Texture texture;
	ULONG numInTexSeq;
	VECTOR4D colour;
	REAL diffuse;
	REAL emissive;
	REAL specular;
	REAL power;
	REAL transparency;
	ULONG flags;
	ULONG texFlags;

	SLONG texSeqOffset;

} Mesh_LightWave_Surface, *lpMesh_LightWave_Surface;


typedef struct Mesh_TextureStateChangeDataTAG
{
	ULONG origValue;
	BOOL changed;

} Mesh_TextureStateChangeData , *lpMesh_TextureStateChangeData ;


typedef struct Mesh_RenderDescTAG
{
	VOID (*renderCallback)( struct Mesh *mesh, LPVOID data, lpViewport vp );
	LPVOID renderCallbackData;

	ULONG renderFlags;

} Mesh_RenderDesc, *lpMesh_RenderDesc;


typedef struct Mesh_VertexTAG
{
	VECTOR3D position;
	VECTOR3D normal;
//	DWORD dwDiffuseRGBA;
	REAL tu, tv;

} Mesh_Vertex, *lpMesh_Vertex;


typedef struct Mesh_GroupTAG
{
	ULONG faceDataSize, vertexCount;
	LPUWORD faceData;
	lpMesh_Vertex vertices;

	D3DMATERIAL material;
	LPDIRECT3DTEXTURE2 imText;

	ULONG renderFlags;

	lpMesh_LightWave_Surface lightWaveSurfaceInfo;

	ULONG flags;

} Mesh_Group, *lpMesh_Group;


typedef struct Mesh
{
	ULONG groupCount, listSize;
	lpMesh_Group groupList;

	LPDIRECT3DRMUSERVISUAL uv;

	Mesh_RenderDesc renderDesc;
	lpMesh_LightWave_Surface lightWaveSurf;

	ULONG numOfRefs;
	struct Mesh *clonedFrom;
	LPDIRECT3DRMFRAME3 frameCreatedOn;

	//BOX3D boundingBox;

	ULONG flags;

	struct Mesh *nextFree;

	int 	(*textureRenderCallback)(LPVOID data);
	LPVOID	textureRenderCallbackData;

} Mesh, *lpMesh;


typedef struct Mesh_PostRenderInfoTAG
{
	lpMesh mesh;
	D3DMATRIX matWorld;

	struct Mesh_PostRenderInfoTAG *next;

} Mesh_PostRenderInfo, *lpMesh_PostRenderInfo;


typedef struct Mesh_TextureReference {

	LPDIRECTDRAWSURFACE4 surface;
	LPUCHAR path;

	BOOL trans;

} Mesh_TextureReference, *lpMesh_TextureReference;


typedef struct Mesh_GlobsTAG
{
	lpMesh postRenderList;

	lpMesh_PostRenderInfo postRenderMeshList;

	Mesh_TextureStateChangeData stateData[MESH_MAXTEXTURESTAGESTATES];

	LPUCHAR sharedTextureDir;
	struct Mesh_TextureReference textureList[MESH_TEXTURELISTSIZE];
	struct Mesh_TextureReference textureListShared[MESH_TEXTURELISTSIZE];
	ULONG textureCount, textureCountShared;

	D3DTEXTUREHANDLE oldTextureRM;
	D3DMATERIALHANDLE oldMatIM;
	LPDIRECT3DTEXTURE2 oldTextureIM;

	D3DTEXTUREHANDLE currTextureRM;
	D3DMATERIALHANDLE currMatIM;
	LPDIRECT3DTEXTURE2 currTextureIM;

	D3DMATERIALHANDLE matHandle;
	LPDIRECT3DMATERIAL3 imMat;

	ULONG ambientLight;

	struct Mesh *listSet[MESH_MAXLISTS];
	struct Mesh *freeList;

	ULONG listCount;

} Mesh_Globs, *lpMesh_Globs;

static BOOL Mesh_CanRenderGroup( lpMesh_Group group );

#else 

typedef struct Mesh_VertexTAG	*lpMesh_Vertex;
typedef struct Mesh_GroupTAG	*lpMesh_Group;
typedef struct Mesh				*lpMesh;

#endif // _GODS98COMPILE

#ifdef _DEBUG

#define Mesh_Debug_CheckIMDevice_Ptr()		{ if (NULL==lpIMDevice()) return (LPVOID) 1; }
#define Mesh_Debug_CheckIMDevice_Void()		{ if (NULL==lpIMDevice()) return; }
#define Mesh_Debug_CheckIMDevice_Int()		{ if (NULL==lpIMDevice()) return 1; }

#else

#define Mesh_Debug_CheckIMDevice_Ptr()
#define Mesh_Debug_CheckIMDevice_Void()
#define Mesh_Debug_CheckIMDevice_Int()

#endif // _DEBUG

#define Mesh_Create( c, f, rf, d )						Mesh_CreateOnFrame( (c->activityFrame), (f), (rf), (d), Mesh_Type_Norm )
#define Mesh_CreatePostEffect( c, f, rf, d )			Mesh_CreateOnFrame( (c->activityFrame), (f), (rf), (d), Mesh_Type_PostEffect )
#define Mesh_LoadLightWaveObject( n, c )				Mesh_Load( (n), (c->activityFrame) )
#define Mesh_RemoveFromContainer(m,c)					Mesh_Remove((m),(c)->activityFrame)

#define Mesh_SetWorldTransform( m )						Mesh_SetTransform( TRANSFORMSTATE_WORLD, (m) )

#define Mesh_SetGroupDiffuse( m, n, r, g, b )				Mesh_SetGroupColour( (m), (n), (r), (g), (b), Mesh_Colour_Diffuse )
#define Mesh_SetGroupAmbient( m, n, r, g, b )				Mesh_SetGroupColour( (m), (n), (r), (g), (b), Mesh_Colour_Ambient )
#define Mesh_SetGroupSpecular( m, n, r, g, b )				Mesh_SetGroupColour( (m), (n), (r), (g), (b), Mesh_Colour_Specular )
#define Mesh_SetGroupEmissive( m, n, r, g, b )				Mesh_SetGroupColour( (m), (n), (r), (g), (b), Mesh_Colour_Emissive )
#define Mesh_SetGroupPower( m, n, p )						Mesh_SetGroupMaterialValues( (m), (n), (p), Mesh_Colour_Power )
#define Mesh_SetGroupAlpha( m, n, a )						Mesh_SetGroupMaterialValues( (m), (n), (a), Mesh_Colour_Alpha )

#define Mesh_GetGroupDiffuse( m, n, r, g, b )				Mesh_GetGroupColour( (m), (n), (r), (g), (b), Mesh_Colour_Diffuse )
#define Mesh_GetGroupAmbient( m, n, r, g, b )				Mesh_GetGroupColour( (m), (n), (r), (g), (b), Mesh_Colour_Ambient )
#define Mesh_GetGroupSpecular( m, n, r, g, b )				Mesh_GetGroupColour( (m), (n), (r), (g), (b), Mesh_Colour_Specular )
#define Mesh_GetGroupEmissive( m, n, r, g, b )				Mesh_GetGroupColour( (m), (n), (r), (g), (b), Mesh_Colour_Emissive )
#define Mesh_GetGroupPower( m, n, p )						Mesh_GetGroupMaterialValues( (m), (n), (p), Mesh_Colour_Power )
#define Mesh_GetGroupAlpha( m, n, a )						Mesh_GetGroupMaterialValues( (m), (n), (a), Mesh_Colour_Alpha )

#ifndef _GENPROTFILE
#include "..\Src\Mesh.prot"
#endif // !_GENPROTFILE

#endif // !_GODS98_MESH_H_