
//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Container.c - [Container Code]
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#define	MAXCHILDCONTAINERS				32
#define	MAX_CONTAINERS					185		// (this must NOT exceed 256)

#define CONTAINER_FRAMENAMELEN			20
#define CONTAINER_ACTIVITYFRAMEPREFIX	"ActFrame"
#define CONTAINER_SCALESTRING			"SCALE"

#define CONTAINER_MAXLISTS				20			// Maximum of 2^20 - 1 containers
#define CONTAINER_MAXTEXTURES			1000
#define CONTAINER_MESHGROUPBLOCKSIZE	20

#define CONTAINER_FLAG_INITIALISED		0x00000001
#define CONTAINER_FLAG_TRIGGERSAMPLE	0x00000002
#define CONTAINER_FLAG_MESHSWAPPED		0x00000004
#define CONTAINER_FLAG_HIDDEN			0x00000008

#define CONTAINER_NULLSTRING				"NULL"
#define CONTAINER_MESHSTRING				"MESH"
#define CONTAINER_MESHNOTEXTURESTRING	"MESH:NOTEXTURE"
#define CONTAINER_FRAMESTRING			"FRAME"
#define CONTAINER_ANIMSTRING				"ANIM"
#define CONTAINER_ACTIVITYSTRING		"ACT"

#define CONTAINER_ULONG_NULL			-1

#define CONTAINER_TRASHVALUE			0xdeaddead

#define CONTAINER_TEXTURE_NOLOAD		0x00000001

#define	MAXCHILDREN	40



enum
{
	Container_Invalid = -1,
	Container_Null,
	Container_Mesh,
	Container_Frame,
	Container_Anim,
	Container_FromActivity,

	Container_Light,

	Container_Reference,

	Container_TypeCount,
};


enum {
	Container_Light_Ambient,
	Container_Light_Point,
	Container_Light_Spot,
	Container_Light_Directional,
	Container_Light_ParallelPoint
};

enum {
	Container_Combine_Replace,
	Container_Combine_Before,
	Container_Combine_After
};

enum {
	Container_Quality_Wireframe,
	Container_Quality_UnlitFlat,
	Container_Quality_Flat,
	Container_Quality_Gouraud
};

enum {
    Container_Fog_Linear,
    Container_Fog_Exponential,
    Container_Fog_ExponentialSquared
};


#define Container_SetWorldRotation(c,x,y,z,a)				Container_SetRotation((c),(x),(y),(z))
#define Container_SetWorldPosition(c,x,y,z)					Container_SetPosition((c),(x),(y),(z))
#define Container_SetWorldOrientation(c,dx,dy,dz,ux,uy,uz)	Container_SetOrientation((c),NULL,(dx),(dy),(dz),(ux),(uy),(uz))
#define Container_GetWorldRotation(c,ax,a)					Container_GetRotation((c),(ax),(a))
#define Container_GetWorldPosition(c,p)						Container_GetPosition((c),(p))
#define Container_GetWorldOrientation(c,d,u)				Container_GetOrientation((c),NULL,(d),(u))

#define Container_MakePointLight(c,r,g,b)					Container_MakeLight((c),Container_Light_Point,(r),(g),(b));
#define Container_MakeSpotLight(c,r,g,b)					Container_MakeLight((c),Container_Light_Spot,(r),(g),(b));
#define Container_MakeAmbientLight(c,r,g,b)					Container_MakeLight((c),Container_Light_Ambient,(r),(g),(b));
#define Container_MakeDirectionalLight(c,r,g,b)				Container_MakeLight((c),Container_Light_Directional,(r),(g),(b));
#define Container_MakeParallelPointLight(c,r,g,b)			Container_MakeLight((c),Container_Light_ParallelPoint,(r),(g),(b));

#define Container_MakeMesh(r)								Container_MakeMesh2((r),FALSE)
#define	Container_SetMesh(c,t)								Container_Map_SetMesh(c,t)
#define	Container_SetModel(c,m)								Container_Mesh_SetModel(c,m)

typedef	struct ORIENT
{
	VECTOR	up;
	VECTOR	dir;
} ORIENT, *lpORIENT;

typedef	struct	COORDS
{
	VECTOR			rot;
	VECTOR			pos;
	ORIENT			orientation;
	MATRIX			omatu;
	MATRIX			omatd;
	GsCOORDUNIT		coord;
} COORDS, *lpCOORDS;

typedef	struct TMDobj
{
	lpSVECTOR	VertT;
	Uint32		VertN;
	lpSVECTOR	NormT;
	Uint32		NormN;
	LPVOID		PrimT;
	Uint32		PrimN;
	Sint32		Scale;
} TMDobj, *lpTMDobj;

typedef	struct	TMDhead
{
	Uint32	id;
	Uint32	flags;
	Uint32	numObjects;
} TMDhead, *lpTMDhead;


typedef	struct	DIRECT3DRMMESH
{
	lpCOORDS		coords;
	LPVOID		model;
	lpSVECTOR	vertices;
	lpSVECTOR	normals;
	Uint16		numVertices; 
	LPVOID		polys;
	LPVOID		temp;
} DIRECT3DRMMESH, *LPDIRECT3DRMMESH;


typedef struct Container_SearchData
{
	LPUCHAR		string;
	ULONG			stringLen;
	BOOL			caseSensitive;

} Container_SearchData, *lpContainer_SearchData;


typedef struct Container_Texture
{
	ULONG 	dummy;
	lpImage	image;

} Container_Texture, *lpContainer_Texture;

typedef struct Container_TextureRef
{
	LPUCHAR 					fileName;
	lpContainer_Texture	texture;

} Container_TextureRef, *lpContainer_TextureRef;

typedef struct Container_TextureData
{
	LPUCHAR	xFileName;
	ULONG		flags;

} Container_TextureData, *lpContainer_TextureData;

typedef struct Container_TypeData
{
	LPUCHAR name;
	lpGsF_LIGHT light;
	LPDIRECT3DRMMESH mesh;

} Container_TypeData, *lpContainer_TypeData;



typedef enum
{
	TYPE_CONTAINER,
	TYPE_HMDCAMERA,
	TYPE_CAMERA,
	TYPE_LIGHT,
	TYPE_DECAL=0x40,
	TYPE_FLOOR_DECAL,			/* quad aligned with floor */
	TYPE_INTERNAL_DECAL,		/* render function provided by container call-back */
	TYPE_POLY,
	TYPE_MESH=0x80,
	TYPE_HMD,
	TYPE_TMD,
	TYPE_PMD,
	TYPE_SMD,
	TYPE_RMD,
	TYPE_STATIC_HMD,			// these are handled differently to normal HMD and shouldn't contain any animation
	MAX_CONTAINER_TYPES
} ContainerType;


enum
{
	RENDER_FLAGS_NONE			=0,
	RENDER_FLAGS_CLIP_POINT		=1,
	RENDER_FLAGS_CLIPPED		=2,
	RENDER_FLAGS_CLIP_BOTTOM	=4,		/* used to clip sprite bottom in liquid */
	RENDER_FLAGS_INVISIBLE		=8,		/* tell it not to draw */
}	RenderFlags;


typedef	struct Container
{
	ContainerType		type;

	Uint16				Hidden:1;
	Uint16				TriggerSample:1;
	Uint16				in_use:1;

	int					renderFlags;
	LPVOID				modelData;
	LPVOID				userData;
	COORDS				coords;
	Uint8					activitySeq;		/* activity for mesh or sprite, extra data for sprites held in userData */

// Cheesy Scott, very cheesy
// BEGIN ScottN
// Added some more functionality to the sprite stuff  ie.   call back when it gets to the end of a sequence

	Uint8					old_activity_seq;		// activity for mesh or sprite, extra data for sprites held in userData */
	void					(*callback)();			// callback function for when we get to an animation frame
	Uint8					callback_frame;

// END ScottN


	Uint8					id;
	Uint8					red;
	Uint8					green;
	Uint8					blue;
	FIXED					scale;
	short					transX;		/* screen coords after last transformation */
	short					transY;
	short					clipSize;
	short					ScreenXClip;
	short					ScreenYClip;
	void					(*renderCallback)();
	LPVOID				owner;							/* pointer to the OBJECT that owns this container */
	struct Container	*parent;						// used for the static models
	//struct Container	*next;
// Active subdivision handling stuff added by julian
	Uint8					ASStatus;
	int							ASDepth;
	int							ASMaxPolyWidth;
	int							ASMaxPolyHeight;


} Container, *lpContainer;


typedef enum
{
	SF_ACTION_COMPLETE	=	1,
	SF_AUTO_LOOP			=	2,
	SF_TRANSLUCENT			=	4,	

}	SPRITE_FLAGS;


/* these are unique for each container */
typedef	struct	anim_data_st
{
	SPR_ACTIVITY_SET	*activitySet;
	int					animTotal;
	Uint8					animIndex;			/* frame index */
	Uint8					animRepeatCount;	/* repeat action count, 255==infinite */

	Uint8					clutIndex;			/* colour scheme */
	Uint8					brightness;			/* take a wild stab... */ 
	SPRITE_FLAGS		flags;

}	SPRITE_ANIM_DATA, *lpSPRITE_ANIM_DATA;


typedef struct Container_CloneData
{
	lpContainer clonedFrom;				// NULL if this is the original
	lpContainer *cloneTable;			// List of clones (NULL for unused elements)
	ULONG cloneCount, cloneNumber;		// Total number of clones made and clone's number in the list.
	BOOL used;
} Container_CloneData, *lpContainer_CloneData;


typedef struct Container_AppData
{
	lpContainer ownerContainer;

	LPUCHAR animSetFileName;			// For the dodgy Animation Set clone stuff...
	LPUCHAR frameName;					// For freeing the allocation for SetName...

	ULONG frameCount;
	REAL currTime;
	REAL transCo;						// Standard translation during amimset loop.

} Container_AppData;

typedef struct Container_MeshAppData
{

	LPDIRECT3DRMMESH *meshList;
	ULONG usedCount, listSize;
	BOOL groupZeroHidden, firstAddGroup;

} Container_MeshAppData, *lpContainer_MeshAppData;


typedef struct Container_Globs
{
	lpContainer listSet[MAX_CONTAINERS];		/* changed to a linear list */
	lpContainer rootContainer;

	LPUCHAR gameName;

	ULONG list_index;
	ULONG flags;

} Container_Globs;


lpContainer			Container_Create(lpContainer parent);
void 					Container_AddList(void);
lpContainer			Container_Initialise(LPUCHAR gameName);
void						Container_Remove(lpContainer dead);
void						Container_Remove2(lpContainer dead, BOOL kill);
void						Container_SetParent(lpContainer parent, lpContainer child);
VOID						Container_SetRotation(lpContainer cont, REAL x, REAL y, REAL z);
VOID 					Container_SetRotationIndex(lpContainer cont, int index, REAL x, REAL y, REAL z);
VOID						Container_SetPosition(lpContainer cont, REAL x, REAL y, REAL z);
VOID 					Container_SetPositionIndex(lpContainer cont, int index, REAL x, REAL y, REAL z);
VOID						Container_GetPosition(lpContainer cont, LPVECTOR3D pos);
VOID 					Container_GetRotation(lpContainer cont, LPVECTOR3D rot);

VOID						Container_SetOrientation(lpContainer cont, lpContainer ref, REAL dirx, REAL diry, REAL dirz, REAL upx, REAL upy, REAL upz);
lpContainer			Container_Load(lpContainer parent, LPUCHAR filename, LPUCHAR typestr);
VOID 					Container_Hide(lpContainer cont, BOOL hide);
lpContainer			Container_Load(lpContainer parent, LPUCHAR filename, LPUCHAR typestr);
ULONG					Container_ParseTypeString(LPUCHAR str, LPBOOL noTexture);
VOID						Container_AddRotation(lpContainer cont, ULONG combine, REAL x, REAL y, REAL z, REAL angle);
VOID						Container_AddScale(lpContainer cont, ULONG combine, REAL x, REAL y, REAL z);
VOID						Container_AddTranslation(lpContainer cont, ULONG combine, REAL x, REAL y, REAL z);
VOID						Container_AddTransform(lpContainer cont, ULONG combine, MATRIX4D mat);
lpContainer_Texture	Container_LoadTexture(LPUCHAR fname, LPULONG width, LPULONG height);
VOID						Container_SetTexture(lpContainer cont, lpContainer_Texture itext);
VOID						Container_FreeTexture(lpContainer_Texture text);
VOID						Container_Transform(lpContainer cont, LPVECTOR3D dest, LPVECTOR3D src);
VOID						Container_InverseTransform(lpContainer cont, LPVECTOR3D dest, LPVECTOR3D src);
lpContainer			Container_Clone(lpContainer orig);

VOID						Container_SetUserData(lpContainer cont, LPVOID data);
LPVOID					Container_GetUserData(lpContainer cont);
VOID						Container_Move(lpContainer root, REAL delta);

lpContainer			Container_MakeMesh2(lpContainer parent, BOOL seperateGroups);
lpContainer			Container_MakeMeshSeperateGroups(lpContainer root);
VOID						Container_Mesh_SetQuality(lpContainer cont, ULONG groupID, ULONG quality);
ULONG					Container_Mesh_GetVertices(lpContainer cont, ULONG groupID, ULONG index, ULONG count, LPVERTEX3D retArray);
ULONG					Container_Mesh_SetVertices(lpContainer cont, ULONG groupID, ULONG index, ULONG count, LPVERTEX3D values);
ULONG					Container_Mesh_AddGroup(lpContainer cont, ULONG vertexCount, ULONG faceCount, ULONG vPerFace, LPULONG faceData);
BOOL						Container_Mesh_IsGroupHidden(lpContainer cont, ULONG group);
VOID						Container_Mesh_HideGroup(lpContainer cont, ULONG group, BOOL hide);
BOOL						Container_Mesh_GetGroup(lpContainer cont, ULONG groupID, LPULONG vertexCount, LPULONG faceCount, LPULONG vPerFace, LPULONG faceDataSize, LPULONG faceData);
ULONG					Container_Mesh_GetGroupCount(lpContainer cont);
VOID						Container_Mesh_SetTexture(lpContainer cont, ULONG groupID, lpContainer_Texture itext);
lpContainer_Texture Container_Mesh_GetTexture(lpContainer cont, ULONG groupID);
VOID						Container_Mesh_SetPerspectiveCorrection(lpContainer cont, ULONG groupID, BOOL on);
VOID						Container_Mesh_SetMaterial(lpContainer cont, ULONG groupID, lpMaterial material);
BOOL						Container_Mesh_Scale(lpContainer cont, REAL x, REAL y, REAL z);
VOID						Container_Mesh_SetColourAlpha(lpContainer cont, ULONG groupID, REAL r, REAL g, REAL b, REAL a);
VOID						Container_Mesh_GetColourAlpha(lpContainer cont, ULONG groupID, LPREAL r, LPREAL g, LPREAL b, LPREAL a);
VOID						Container_Mesh_SetColour(lpContainer cont, ULONG groupID, REAL r, REAL g, REAL b);
VOID						Container_Mesh_GetColour(lpContainer cont, ULONG groupID, LPREAL r, LPREAL g, LPREAL b);
ULONG					Container_Mesh_SetAppData(LPDIRECT3DRMMESH mesh, ULONG data);
ULONG					Container_Mesh_GetAppData(LPDIRECT3DRMMESH mesh);
LPDIRECT3DRMMESH		Container_Mesh_CreateMesh(LPDIRECT3DRMMESH *mesh);

void						Container_Mesh_SetPolyList(lpContainer cont, LPULONG list, ULONG size);
void						Container_Mesh_SetVertexList(lpContainer cont, LPULONG list, ULONG size);
void						Container_Mesh_SetNormalList(lpContainer cont, LPULONG list, ULONG size);
LPVOID					Container_Mesh_GetPolyList(lpContainer cont);
LPVOID					Container_Mesh_GetNormalList(lpContainer cont);
LPVOID					Container_Mesh_GetVertexList(lpContainer cont);

LPUCHAR					Container_FormatPartName(lpContainer cont, LPUCHAR partname, ULONG instance);
lpContainer			Container_SearchTree(lpContainer root, LPUCHAR name);
VOID						Container_GetOrientation(lpContainer cont, lpContainer ref, LPVECTOR3D dir, LPVECTOR3D up);
REAL						Container_GetZXRatio(lpContainer cont);
REAL						Container_GetTransCoef(lpContainer cont);
REAL						Container_MoveAnimation(lpContainer cont, REAL delta);
REAL						Container_SetAnimationTime(lpContainer cont, REAL time);
REAL						Container_GetAnimationTime(lpContainer cont);
ULONG					Container_GetAnimationFrames(lpContainer cont);
BOOL						Container_Mesh_GetBox(lpContainer cont, LPBOX3D box);
VOID						Container_Mesh_Swap(lpContainer target, lpContainer origin, BOOL restore);
BOOL						Container_SetActivity(lpContainer cont, LPUCHAR actname);
BOOL						Container_SetActivityByType(lpContainer cont, int activity_type);
VOID						Container_SetTypeData(lpContainer cont, LPUCHAR name, lpGsF_LIGHT light, LPDIRECT3DRMMESH mesh);

void						Container_Map_SetMesh(lpContainer cont, ContainerType type);
void						Container_Map_SetVertices(lpContainer cont, Uint16 x, Uint16 y, LPUWORD vert, Uint16 wide);
void						Container_Map_GetVertices(lpContainer cont, Uint16 x, Uint16 y, LPUWORD vert, Uint16 wide);
lpSVECTOR				Container_Map_GetNormal(lpContainer cont, Uint16 x, Uint16 y, Uint16 w, Uint16 n);
void						Container_Map_PlaneNormal(lpContainer cont, Uint32 id, Uint16 v0, Uint16 v1, Uint16 v2);

lpContainer_Texture	Container_Texture_LoadTexture(LPUCHAR fname, lpContainer_Texture* texture);
LPBOX3D					Container_Mesh_MeshGetBox(LPDIRECT3DRMMESH obj, LPBOX3D box);
//LPDIRECT3DRMMESH		Container_MeshLoad(LPVOID fdata, ULONG fsize, LPDIRECT3DRMFRAME2 frame, BOOL noTexture);
VOID						Container_Light_SetEnableContainer(lpContainer light, lpContainer enable);

BOOL						Container_FindRoot(lpContainer cont, lpContainer *root);

lpContainer			Container_ApplyMesh(lpContainer parent, LPVOID model, ContainerType type);




void						Container_SetRenderFlags(lpContainer cont, int flags);
void						Container_Mesh_SetModel(lpContainer cont, LPVOID mod);
LPVOID					Container_Mesh_GetModel(lpContainer cont);
void						Container_Mesh_SetMesh(lpContainer cont, LPDIRECT3DRMMESH mesh);
LPDIRECT3DRMMESH		Container_Mesh_GetMesh(lpContainer cont);

lpContainer			Container_LoadHMDModel(lpContainer root, LPUCHAR fname,int modeflags);
lpContainer 			Container_CreateSprite(lpContainer parent, SPR_ACTIVITY_SET *activitySet);
lpContainer			Container_CreateFloorSprite(lpContainer parent, SPR_ACTIVITY_SET *activitySet);
BOOL						Container_SetSpriteActivitySet(lpContainer cont, SPR_ACTIVITY_SET *activitySet);

void						Container_SpriteSetFrameFromRotation(lpContainer cont, Uint8 frame, int angle);
void 					Container_SpriteSetSpriteBrightness(lpContainer cont, Uint8 brightness);
void						Container_SpriteSetSpriteClut(lpContainer cont, Uint8 clutIndex);
void 					Container_SpriteSetSpriteSize(lpContainer cont, Uint16 size);
void 					Container_UpdateAnimation(lpContainer cont, int update);

BOOL						Container_SetCameraViewpoint(lpContainer camera, int clx, int cly, int clz);
BOOL						Container_SetCameraPosition(lpContainer camera, int cpx, int cpy, int cpz);
BOOL						Container_SetCamera(lpContainer camera, int cpx, int cpy, int cpz, int clx, int cly, int clz);
lpContainer			Container_CreateCameraContainer(lpContainer parent);
void						Container_SetScale(lpContainer cont, int scale);

BOOL						Image_DisplayFloorSprite(SPRITE_SET *set, int frame, lpContainer cont);
BOOL						Image_DisplayFloorSpriteIndex(SPRITE_SET *set, int frame_offset, lpContainer cont);


void						Container_SetScaleBlock(lpContainer cont, int index, int scale);
void					Container_SetScaleBlockSeparate(lpContainer cont, int index, int scaleX, int scaleY, int scaleZ);
void 					Container_SetRenderCallback(lpContainer cont, void (*Callback)(lpContainer callbackCont));
void 					Container_StartAnimation(lpContainer cont,int seq, int frames, int speed);
void 					Container_PauseAnimation(lpContainer cont);
void						Container_UnPauseAnimation(lpContainer cont);
void 					Container_SetAnimSpeed(lpContainer cont, int speed);
void						Container_SetRGB(lpContainer cont, Uint8 red, Uint8 green, Uint8 blue);

short 					Container_GetScreenX(lpContainer cont);
short 					Container_GetScreenY(lpContainer cont);

void					Container_SetCallback(lpContainer cont, short frame, void (*Callback)(void));
void					Container_GetAnimationFrame(lpContainer cont, int *anim_frame, int *max_frame);
short					Container_GetActivity( lpContainer cont );


lpContainer				Container_LoadStaticHMDModel(lpContainer root, LPUCHAR fname, int modeflags);
lpContainer				Container_StaticClone(lpContainer orig);

