//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Main Header File For <LEGO Rock Raiders>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

#ifndef	__MAP3D_H

#define	MAP3DWIDTH	5
#define	MAP3DHEIGHT	5




#define MAP3D_NOTEXTURE						0xff
#define MAP3D_MAXTEXTURES						128
#define MAP3D_MAXSHOW							400

#define MAP3D_HIDEDISTANCE					ToFIXED(10000)

#define MAP3D_FLAGHASHIDDEN					0x00000001
#define MAP3D_FLAGNORMALCHANGED				0x00000002
//#define MAP3D_FLAGSEPARATEMESHES			0x00000004

enum {
	Map3D_North,
	Map3D_East,
	Map3D_South,
	Map3D_West,
	Map3D_NorthEast,
	Map3D_SouthEast,
	Map3D_SouthWest,
	Map3D_NorthWest
};

//#define Map3D_BlockValue(m,x,y)			((m)->blockData[((y)*(m)->blocksWide)+(x)])

#define	BASEMAPTEXTURES	10



typedef	struct Map3D_Texture
{
	Uint16	tPage;
	Uint8		offsetX;
	Uint8		offsetY;
	Uint16	clut;

} Map3D_Texture, *lpMap3D_Texture;

typedef struct Detail_TextureSet
{
	ULONG						width, height;
	Map3D_Texture			*table;

} Detail_TextureSet, *lpDetail_TextureSet;


typedef	struct MAPFACEDATA
{
	Uint16	v0, v1, v2, v3;
} MAPFACEDATA, *lpMAPFACEDATA;

typedef	struct MAPhead
{
	Uint32	id;
	Uint32	size;
	Uint32	width;
	Uint32	height;
} MAPhead, *lpMAPhead;


/* moved to stop compiler whinging */
typedef struct Lego_Block
{
/* these came from map3d_block, some are not used */

	Sint16		topLeftAlt;		/* vertex height used for map */
	Sint16		wobble;
	Sint16		redWobble;
	int			xoff;
	int			yoff;

	UCHAR			red;			/* colour values for the vertex */
	UCHAR			green;
	UCHAR			blue;
	UCHAR			redLit;		/* these are pre-calculated for speed */
	UCHAR			greenLit;
	UCHAR			blueLit;

	UCHAR			lightSetting;		/* a value equating from 0-1, used to find the lit colour values from the unlit */
	UCHAR			blockTexture;
	UCHAR			surfaceType;
	UCHAR			direction;
	short			damage;
	ULONG			flags;		/* too many flags for a Uint16 now, no doubt more will be needed later anyway */
	void			*trigger;

} Lego_Block, *lpLego_Block;



/*
	version 2 of mod map structure
*/
typedef struct modblock2_st
{
	UCHAR			red;			/* colour values for the vertex */
	UCHAR			green;
	UCHAR			blue;
	UCHAR			lightSetting;		/* a value equating from 0-1, used to find the lit colour values from the unlit */
	UCHAR			surfaceType;
	UCHAR			blockTexture;
	UCHAR			direction;
	UCHAR			padByte;
	int			xoff;
	int			yoff;
	Sint16		zoff;
	Uint16		flags;
}	MODBLOCK2;



typedef struct Map3D
{
	ULONG						blocksWide, blocksHigh;
	ULONG						gridWidth, gridHeight;
	ULONG						meshWidth, meshHeight;
	ULONG						meshWide, meshHigh;
	lpMap3D_Texture		textureData;

	REAL						blockSize, roughLevel;
	REAL						xPhysicalOrigin, yPhysicalOrigin;
	REAL						xTempOrigin, yTempOrigin;
	lpLego_Block			blockData;		/* mirror of pointer in currLevel */
	lpDetail_TextureSet	textureSet;

} Map3D, *lpMap3D;

typedef	struct	Map3D_PolyList
{
	Uint16	vert0, vert1, vert2;
	Uint16	norm0;
	Uint16	tPage;
	Uint8		u, v;
} Map3D_PolyList, *lpMap3D_PolyList;

#define	ID_HMD	0x00000050

VOID Map3D_Remove(lpMap3D map);
VOID Map3D_SetTextureSet(lpMap3D map, lpDetail_TextureSet tSet);
VOID Map3D_SetBlockTexture(lpMap3D map, ULONG bx, ULONG by, UCHAR tpos, UCHAR direction);
VOID Map3D_MoveVertex(lpMap3D map, ULONG vx, ULONG vy, REAL dist);
VOID Map3D_HighlightBlock(lpMap3D map, ULONG bx, ULONG by, BOOL on);
BOOL Map3D_BlockRotated(lpMap3D map, ULONG bx, ULONG by);
REAL Map3D_BlockSize(lpMap3D map);
VOID Map3D_MapGetSpecs(LPULONG map, LPULONG w, LPULONG h);
UWORD Map3D_MapBlockValue(LPULONG map, ULONG x, ULONG y, ULONG width);
lpMap3D Map3D_Create(lpContainer root, LPULONG surfMap, REAL blockSize);
VOID Map3D_RotateBlockFaces(lpMap3D map, ULONG bx, ULONG by);

#define	__MAP3D_H
#endif



