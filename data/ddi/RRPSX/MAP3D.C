//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// 3D Map File For <LEGO [Rock Raiders]>
//
// Started:	10-07-98
// Coding:	Glenn Benson
// Graphics:
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Include all Header Files
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
#include	"..\inc\globals.h"


Sint16				old_mx=-1,old_my=-1;


#define	SCALEVAL	1


VOID Map3D_Remove(lpMap3D map)
{
	//Container_Remove(map->meshCont);
	Mem_Free(map->blockData);
	Mem_Free(map);
}




VOID Map3D_SetTextureSet(lpMap3D map, lpDetail_TextureSet tSet)
{
	map->textureSet = tSet;
}



/*
	slim and lovely version using lego_block structure only
*/
VOID Map3D_SetBlockTexture(lpMap3D map, ULONG bx, ULONG by, UCHAR tpos, UCHAR direction)
{
	if (bx >= 0 && by >= 0 && bx < map->blocksWide && by < map->blocksHigh)
	{

		Uint16	id=(by*map->gridWidth)+bx;		/* note lego block map is one wider than old 3dmap */

		map->blockData[id].direction=direction;
		map->blockData[id].blockTexture=((tpos&0xf0)>>1)+(tpos&0x0f);		//==y*8+x
	}
}



VOID Map3D_MoveVertex(lpMap3D map, ULONG vx, ULONG vy, REAL dist)
{

/*
	we use topLeftAlt as the vertex height here now

*/

	if (!(mapBlockValue(map, vx, vy).flags &	MAP3DBLOCK_VERTEXMOVED))
	{
		mapBlockValue(map, vx, vy).flags |=(MAP3DBLOCK_VERTEXMOVED|MAP3DBLOCK_VERTEXMODIFIED);
		mapBlockValue(map, vx, vy).topLeftAlt-=FromFIXED(dist);
	}	

	if (!(mapBlockValue(map, vx+1, vy).flags &	MAP3DBLOCK_VERTEXMOVED))
	{
		mapBlockValue(map, vx+1, vy).flags |=(MAP3DBLOCK_VERTEXMOVED|MAP3DBLOCK_VERTEXMODIFIED);
		mapBlockValue(map, vx+1, vy).topLeftAlt-=FromFIXED(dist);
	}	

	if (!(mapBlockValue(map, vx+1, vy+1).flags &	MAP3DBLOCK_VERTEXMOVED))
	{
		mapBlockValue(map, vx+1, vy+1).flags |=(MAP3DBLOCK_VERTEXMOVED|MAP3DBLOCK_VERTEXMODIFIED);
		mapBlockValue(map, vx+1, vy+1).topLeftAlt-=FromFIXED(dist);
	}	

	if (!(mapBlockValue(map, vx, vy+1).flags &	MAP3DBLOCK_VERTEXMOVED))
	{
		mapBlockValue(map, vx, vy+1).flags |=(MAP3DBLOCK_VERTEXMOVED|MAP3DBLOCK_VERTEXMODIFIED);
		mapBlockValue(map, vx, vy+1).topLeftAlt-=FromFIXED(dist);
	}	
}



VOID Map3D_HighlightBlock(lpMap3D map, ULONG bx, ULONG by, BOOL on)
{
	if (bx >= 0 && by >= 0 && bx < map->blocksWide && by < map->blocksHigh)
	{

		Uint16	id=(by*map->gridWidth)+bx;		/* note lego block map is one wider than old 3dmap */

		if (on)				
			map->blockData[id].flags |= MAP3DBLOCK_HIGHLIGHT;
		else
			map->blockData[id].flags &= ~MAP3DBLOCK_HIGHLIGHT;
	}
}




BOOL Map3D_BlockRotated(lpMap3D map, ULONG bx, ULONG by)
{
	return (mapBlockValue(map, bx, by).flags & MAP3DBLOCK_FLAGROTATED);
}


REAL Map3D_BlockSize(lpMap3D map)
{

	return map->blockSize;
}






VOID Map3D_MapGetSpecs(LPULONG map, LPULONG w, LPULONG h)
{
	LPULONG mapaddr = map + 2;
	
	*w = *mapaddr;
	mapaddr++;
	*h = *mapaddr;
}

UWORD Map3D_MapBlockValue(LPULONG map, ULONG x, ULONG y, ULONG width)
{
	
	UWORD *mapaddr = ((LPUWORD) map) + 8;
	
	return mapaddr[(width * y) + x];
}



/*
	create MAP3D map, modified to pass in the altitude map
*/
lpMap3D Map3D_Create(lpContainer root, LPULONG surfMap, REAL blockSize)
{
	lpMap3D				map;
	ULONG					x, y, mapSize, gridSize, loop;

	if (map = Mem_Alloc(sizeof(Map3D)))
	{
		map->blockSize = blockSize;
		Map3D_MapGetSpecs(surfMap, &map->gridWidth, &map->gridHeight);
		map->blocksWide = map->gridWidth - 1;
		map->blocksHigh = map->gridHeight - 1;
		if (map->gridWidth > MAP3DWIDTH)
			map->meshWidth=MAP3DWIDTH;
		else
			map->meshWidth=map->gridWidth;

		if (map->gridHeight > MAP3DHEIGHT)
			map->meshHeight=MAP3DHEIGHT;
		else
			map->meshHeight=map->gridHeight;

		map->meshWide=map->meshWidth-1;
		map->meshHigh=map->meshHeight-1;

		map->textureSet = NULL;

		map->xPhysicalOrigin = -((blockSize * map->blocksWide) / 2);
		map->yPhysicalOrigin = -((blockSize * map->blocksHigh) / 2);

		/* set to zero,zero for now */
		map->xPhysicalOrigin =0;
		map->yPhysicalOrigin =0;

		gridSize = map->gridWidth * map->gridHeight;
		mapSize = map->blocksWide * map->blocksHigh;
	}
	return map;
}



/*
	rotate block faces so they split the other way.
*/
VOID Map3D_RotateBlockFaces(lpMap3D map, ULONG bx, ULONG by)
{
	Uint16	id;
	
	id=((by*map->blocksWide)+bx);

	if (mapBlockValue(map, bx, by).flags & MAP3DBLOCK_FLAGROTATED)
		mapBlockValue(map, bx, by).flags &= ~MAP3DBLOCK_FLAGROTATED;
	else
		mapBlockValue(map, bx, by).flags |= MAP3DBLOCK_FLAGROTATED;

}




