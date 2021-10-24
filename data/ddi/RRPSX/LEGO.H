//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Main Header File For <LEGO Rock Raiders>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

#ifndef	__LEGO_H

//#define		__PAL
#define		__CDVERSION

#ifndef __CDVERSION
#define MAPEDIT
#define DEBUG_CONSOLE
#endif



#define LEGO_CONFIG_FILENAME					"Lego.cfg"
#define LEGO_CONFIG_MAINNAME					"Main"

#define LEGO_MAXMULTISELECT					100

#define LEGO_MAXTEXTUREVARIATIONS			5
#define LEGO_MAXVISIBLEBLOCKS				100	

#define LEGO_FLAG_ROOFHIDDEN					0x000000001
#define LEGO_FLAG_SHOWTRACKVP				0x000000002
#define LEGO_FLAG_RESETTIME					0x000000004
#define LEGO_FLAG_USEMUSIC					0x000000008
#define LEGO_FLAG_USESFX						0x000000010
#define LEGO_FLAG_USEDETAIL					0x000000020
#define LEGO_FLAG_SHOWFPS						0x000000040
#define LEGO_FLAG_SHOWMEMORY					0x000000080
#define LEGO_FLAG_MULTISELECT				0x000000100
#define LEGO_FLAG_DDRAWCLEAR					0x000000200
#define LEGO_FLAG_RENDERPANELS				0x000000400


#define MAP3DBLOCK_FLAGROTATED				0x00000001
#define MAP3DBLOCK_VERTEXWOBBLES			0x00000002	/* used by water or lava */
#define MAP3DBLOCK_UVWOBBLES					0x00000004	/* used by water or lava to move uv's */
#define MAP3DBLOCK_REDWOBBLES				0x00000008	/* lava to modify red component in a vertex */


#define LEGOBLOCK_FLAG_INNERCORNER			0x00000010
#define LEGOBLOCK_FLAG_DELAYDIG				0x00000020
#define LEGOBLOCK_FLAG_DIGSELECTED			0x00000040
#define LEGOBLOCK_FLAG_USE_TRANS_Z			0x00000080
#define LEGOBLOCK_FLAG_HAS_PILLAR			0x00000100
#define LEGOBLOCK_FLAG_BLOCK_DUG			0x00000200
#define LEGOBLOCK_FLAG_SURVEYED				0x00000400
#define MAP3DBLOCK_HIGHLIGHT					0x00000800	/* new */
#define MAP3DBLOCK_GENERATENORMAL			0x00001000
#define MAP3DBLOCK_VERTEXLEVELED			0x00002000
#define MAP3DBLOCK_VERTEXMOVED				0x00004000
#define MAP3DBLOCK_VERTEXMODIFIED			0x00008000	/* can be set more than once, flag for vertex re-generation optimization */
#define LEGOBLOCK_FLAG_FLOOR					0x00010000
#define LEGOBLOCK_FLAG_WALL					0x00020000
#define LEGOBLOCK_FLAG_REINFORCED			0x00040000

// No variations/reinforced corners....

#define LEGO_TEXTURE_UNKNOWN					0x05

#define LEGO_TEXTURE_FLOOR_STD				0x00
#define LEGO_TEXTURE_FLOOR_STD2				0x00
#define LEGO_TEXTURE_FLOOR_STD3				0x00
#define LEGO_TEXTURE_FLOOR_REIN				0x00
#define LEGO_TEXTURE_FLOOR_LAVA				0x06
#define LEGO_TEXTURE_FLOOR_WATER			0x07
#define LEGO_TEXTURE_FLOOR_DOZED			0x00
#define LEGO_TEXTURE_ALLFLOORS				{ LEGO_TEXTURE_FLOOR_STD, LEGO_TEXTURE_FLOOR_STD2, LEGO_TEXTURE_FLOOR_STD3, LEGO_TEXTURE_FLOOR_REIN, LEGO_TEXTURE_FLOOR_LAVA, LEGO_TEXTURE_FLOOR_WATER, LEGO_TEXTURE_FLOOR_DOZED }
														
#define LEGO_TEXTURE_SURFACE_STD			0x10	// 0x70
#define LEGO_TEXTURE_SURFACE_IMM			0x10	// 0x70
#define LEGO_TEXTURE_SURFACE_HARD			0x10	// 0x70
#define LEGO_TEXTURE_SURFACE_MED			0x10	// 0x70
#define LEGO_TEXTURE_SURFACE_LOOSE			0x10	// 0x70
#define LEGO_TEXTURE_SURFACE_SOIL			0x10	// 0x70
#define LEGO_TEXTURE_ALLSURFACES			{ LEGO_TEXTURE_SURFACE_STD, LEGO_TEXTURE_SURFACE_IMM, LEGO_TEXTURE_SURFACE_HARD, LEGO_TEXTURE_SURFACE_MED, LEGO_TEXTURE_SURFACE_LOOSE, LEGO_TEXTURE_SURFACE_SOIL }

#define LEGO_TEXTURE_WALL_IMM				0x05
#define LEGO_TEXTURE_WALL_HARD				0x04
#define LEGO_TEXTURE_WALL_MED				0x03
#define LEGO_TEXTURE_WALL_LOOSE				0x02
#define LEGO_TEXTURE_WALL_SOIL				0x01
#define LEGO_TEXTURE_WALL_IMM2				0x05
#define LEGO_TEXTURE_WALL_HARD2				0x04
#define LEGO_TEXTURE_WALL_MED2				0x03
#define LEGO_TEXTURE_WALL_LOOSE2			0x02
#define LEGO_TEXTURE_WALL_SOIL2				0x01
#define LEGO_TEXTURE_ALLWALLS				{ LEGO_TEXTURE_WALL_IMM, LEGO_TEXTURE_WALL_HARD, LEGO_TEXTURE_WALL_MED, LEGO_TEXTURE_WALL_LOOSE, LEGO_TEXTURE_WALL_SOIL, LEGO_TEXTURE_WALL_IMM2, LEGO_TEXTURE_WALL_HARD2, LEGO_TEXTURE_WALL_MED2, LEGO_TEXTURE_WALL_LOOSE2, LEGO_TEXTURE_WALL_SOIL2 }
														
#define LEGO_TEXTURE_REINWALL_IMM			0x25
#define LEGO_TEXTURE_REINWALL_HARD			0x24
#define LEGO_TEXTURE_REINWALL_MED			0x23
#define LEGO_TEXTURE_REINWALL_LOOSE		0x22
#define LEGO_TEXTURE_REINWALL_SOIL			0x21
#define LEGO_TEXTURE_ALLREINWALLS			{ LEGO_TEXTURE_REINWALL_IMM, LEGO_TEXTURE_REINWALL_HARD, LEGO_TEXTURE_REINWALL_MED, LEGO_TEXTURE_REINWALL_LOOSE, LEGO_TEXTURE_REINWALL_SOIL }

#define LEGO_TEXTURE_INCORNER_IMM			0x35
#define LEGO_TEXTURE_INCORNER_HARD			0x34
#define LEGO_TEXTURE_INCORNER_MED			0x33
#define LEGO_TEXTURE_INCORNER_LOOSE		0x32
#define LEGO_TEXTURE_INCORNER_SOIL			0x31
#define LEGO_TEXTURE_ALLINCORNERS			{ LEGO_TEXTURE_INCORNER_IMM, LEGO_TEXTURE_INCORNER_HARD, LEGO_TEXTURE_INCORNER_MED, LEGO_TEXTURE_INCORNER_LOOSE, LEGO_TEXTURE_INCORNER_SOIL }

#define LEGO_TEXTURE_REININCORNER_IMM		0x35
#define LEGO_TEXTURE_REININCORNER_HARD	0x34
#define LEGO_TEXTURE_REININCORNER_MED		0x33
#define LEGO_TEXTURE_REININCORNER_LOOSE	0x32
#define LEGO_TEXTURE_REININCORNER_SOIL	0x31
#define LEGO_TEXTURE_ALLREININCORNERS		{ LEGO_TEXTURE_REININCORNER_IMM, LEGO_TEXTURE_REININCORNER_HARD, LEGO_TEXTURE_REININCORNER_MED, LEGO_TEXTURE_REININCORNER_LOOSE, LEGO_TEXTURE_REININCORNER_SOIL }

#define LEGO_TEXTURE_OUTCORNER_IMM			0x55
#define LEGO_TEXTURE_OUTCORNER_HARD		0x54
#define LEGO_TEXTURE_OUTCORNER_MED			0x53
#define LEGO_TEXTURE_OUTCORNER_LOOSE		0x52
#define LEGO_TEXTURE_OUTCORNER_SOIL		0x51
#define LEGO_TEXTURE_ALLOUTCORNERS			{ LEGO_TEXTURE_OUTCORNER_IMM, LEGO_TEXTURE_OUTCORNER_HARD, LEGO_TEXTURE_OUTCORNER_MED, LEGO_TEXTURE_OUTCORNER_LOOSE, LEGO_TEXTURE_OUTCORNER_SOIL }

#define LEGO_TEXTURE_REINOUTCORNER_IMM	0x55
#define LEGO_TEXTURE_REINOUTCORNER_HARD	0x54
#define LEGO_TEXTURE_REINOUTCORNER_MED	0x53
#define LEGO_TEXTURE_REINOUTCORNER_LOOSE	0x52
#define LEGO_TEXTURE_REINOUTCORNER_SOIL	0x51
#define LEGO_TEXTURE_ALLREINOUTCORNERS	{ LEGO_TEXTURE_REINOUTCORNER_IMM, LEGO_TEXTURE_REINOUTCORNER_HARD, LEGO_TEXTURE_REINOUTCORNER_MED, LEGO_TEXTURE_REINOUTCORNER_LOOSE, LEGO_TEXTURE_REINOUTCORNER_SOIL }

#define LEGO_TEXTURE_COUNT					64

enum {
	Lego_SurfaceType_floor,
	Lego_SurfaceType_Soil,
	Lego_SurfaceType_Loose,
	Lego_SurfaceType_Medium,
	Lego_SurfaceType_Hard,
	Lego_SurfaceType_Immovable,
	Lego_SurfaceType_Lava,
	Lego_SurfaceType_Water,
	Lego_SurfaceType_Tunnel,
	Lego_SurfaceType_ReinHard,

	Lego_SurfaceType_Count
};

enum
{
	Lego_TVCameraObject = -1
};

#define LEGO_ROOFPOLYS					400
#define LEGO_MAXDIG						10


enum
{
	ViewMode_FP,
	ViewMode_Top
};


#define blockValue(l,x,y)					((l)->blockData[(((ULONG)y)*(l)->width)+((ULONG)x)])
#define mapBlockValue(l,x,y)					((l)->blockData[(((ULONG)y)*(l)->gridWidth)+((ULONG)x)])

#define Lego_SameBlock(ax,ay,bx,by)	((ax)==(bx)&&(ay)==(by))
#define Lego_DigBlockSetup(l,x,y)		Lego_DigBlock((l),(x),(y),TRUE)






typedef struct Lego_Level
{
	LPUCHAR					name;

	lpMap3D					map;

	ULONG						levelNumber;
	ULONG						width, height;
	REAL						blockSize, digDepth;
	ULONG						tWidth, tHeight;
	lpDetail_TextureSet	detailTSet;
	LPUCHAR					nextLevel;
	lpLego_Block			blockData;

} Lego_Level, *lpLego_Level;

typedef	struct Lego_Globs
{
	lpConfig			config;

	LPUCHAR			gameName;
	LPUCHAR			surfMap;
	LPUCHAR			dugMap;

	lpLego_Level	currLevel;
	lpContainer		rootCont;
	lpViewport		mainView, trackView;
	lpFont			stdFont;
	lpTextWindow	messageWin;
	ULONG				mode;
	ULONG				flags;
	short				pauseFlag;
	int				frameCount;
	int				lastUpdate;
	int				vblankCount;
	int				updateTime;
	int				vblankCycles;
	int				elapsedTime;			/* game time in seconds */

	int				level;
	int				nextLevel;
	char				levelPath[64];

} Lego_Globs, *lpLego_Globs;

ext	Lego_Globs	legoGlobs;


typedef struct uv_st
{
	unsigned char tu0;
	unsigned char tv0;
	unsigned char tu1;
	unsigned char tv1;
	unsigned char tu2;
	unsigned char tv2;
	unsigned char tu3;
	unsigned char tv3;
} TEXTURE_UV;



void				Gods_Go(void);
BOOL				Lego_Initialise(void);
void				Lego_Shutdown(void);
BOOL				Lego_MainLoop(REAL time);

BOOL				Lego_SetupLights(void);
BOOL				Lego_Setup3D(void);
VOID				Lego_EnableMusic(BOOL on);
VOID				Lego_EnableSFX(BOOL on);

BOOL				Lego_LoadLevel(LPUCHAR levelName);
BOOL				Lego_LoadMapSet(lpLego_Level level, LPUCHAR textureset);
BOOL				Lego_LoadObjectList(lpLego_Level level, LPUCHAR fname);
BOOL				Lego_LoadTextureSet(lpLego_Level level, LPUCHAR textname);
BOOL				Lego_LoadPreDug(lpLego_Level level, LPUCHAR fname);
BOOL				Lego_LoadTerrain(lpLego_Level level, LPUCHAR fname);

lpLego_Level	Lego_GetLevel(VOID);
lpMap3D			Lego_GetMap(VOID);

BOOL Lego_IsFloor(ULONG x, ULONG y);
BOOL Lego_IsWall(ULONG x, ULONG y);
BOOL Lego_IsSurface(ULONG x, ULONG y);
BOOL Lego_FindObjectType(LPUCHAR name, LPULONG type, LPULONG ref);

VOID Lego_CorrectBlock(lpLego_Level level, ULONG bx, ULONG by);
VOID Lego_SetSharpTextures(lpMap3D map);
BOOL Lego_LoadDetailSet(lpLego_Level level, LPUCHAR meshBaseName);
VOID Lego_MapGetSpecs(lpMAPhead map, ULONG *w, ULONG *h);
ULONG Lego_MapBlockValue(lpMAPhead map, ULONG x, ULONG y);
VOID Lego_DigBlock(lpLego_Level level, ULONG bx, ULONG by, BOOL setup);
VOID Lego_SetBlockType(lpLego_Level level, ULONG bx, ULONG by, ULONG type);
ULONG Lego_GetBlockType(ULONG x, ULONG y);
VOID Lego_FloodOpenArea(ULONG bx, ULONG by);

VOID Lego_DrawSelectionBox(lpLego_Level level);

VOID Map3D_GenerateSurfaceHMD(lpLego_Level current_level, Sint16 mx, Sint16 my);

void Lego_ResetGameClock(void);
void Lego_SetGameClock(int time);
void Lego_RecalculateVertexAngles(void);


#define	__LEGO_H
#endif


