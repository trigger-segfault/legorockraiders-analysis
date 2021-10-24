//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß																																																																																																																																																												 uvOffset[uvIndex]uvOffset[uvIndex]
// surface generation For <LEGO [Rock Raiders]>
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Include all Header Files
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

#include	"globals.h"



void	Surface_DisplayTVScreen(void);


SURFACE_GLOBS	surfaceGlobs;


#define	COS_TABLE_SIZE		(32)

short	cosTable[COS_TABLE_SIZE];



#define		HALF_CLIP_WIDTH		(192)
#define		HALF_CLIP_HEIGHT		(128)


void	Surface_DrawLine(int x1,int y1,int x2,int y2, int r, int g, int b)
{
	GsLINE				line;

	line.attribute=0;
	line.r=r;
	line.g=g;
	line.b=b;
														 
	line.x0=x1;
	line.y0=y1;
	line.x1=x2;
	line.y1=y2;
	GsSortLine(&line,&gfxGlobs.Wot[gfxGlobs.bufID],10);
}

#ifndef __CDVERSION
#define	DRAW_CLIP_MARKERS
#endif

#define	COLOUR_SHIFT		(1)

/*
	rebuild the vertex buffer
	full indicates full or partial rebuild. If a block has been dug, but the camera hasn't moved,
	we only need to recalculate the affected vertices.
*/
VOID	Surface_rebuildVertexBuffer(lpLego_Level current_level, Sint16 mx, Sint16 my, BOOL full)
{

	int					x,y,index=0;
	long					*next=(long*) surfaceGlobs.outputList;
	DVECTOR				*screenCoords= surfaceGlobs.outputList;
	unsigned char		*clipped = surfaceGlobs.clippedList;
	GsCOORDINATE2		coord;
	MATRIX				mat;
	lpMap3D 				map=current_level->map;
	long					depth=14,flag;
	SVECTOR				vector;
	
	static	int		cycle=0,tempCycle;
	int					hcw=(gfxGlobs.scrW>>1)+16;
	int					hch=(gfxGlobs.scrH>>1)+16;
	
	GsInitCoordinate2(WORLD, &coord);
	GsGetLs(&coord, &mat);
	GsSetLsMatrix(&mat);


	for(y=0; y<surfaceGlobs.vertexSpan; y++)
	{
		tempCycle=cycle+((my+y)*(current_level->width<<2))+(mx<<3);
		tempCycle&=(COS_TABLE_SIZE-1);

		for(x=0; x<surfaceGlobs.vertexSpan; x++)
		{
			vector.vx=mapBlockValue(map, x+mx, y+my).xoff;
			vector.vy=-mapBlockValue(map, x+mx, y+my).topLeftAlt;

			if (mapBlockValue(map, x+mx, y+my).flags & MAP3DBLOCK_REDWOBBLES)
				mapBlockValue(map, x+mx, y+my).redWobble=cosTable[tempCycle]>>1;

			if (mapBlockValue(map, x+mx, y+my).flags & MAP3DBLOCK_VERTEXWOBBLES)
			{
				mapBlockValue(map, x+mx, y+my).wobble=cosTable[tempCycle];
				vector.vy+=cosTable[tempCycle];
			}
			vector.vz=mapBlockValue(map, x+mx, y+my).yoff;

			gte_RotTransPers(&vector,next,&depth,&flag,&surfaceGlobs.szList[index]);



			if (screenCoords->vx>=-hcw && screenCoords->vx<=hcw && screenCoords->vy>=-hch && screenCoords->vy<=hch)
			{
				*clipped=FALSE;				

#ifdef DRAW_CLIP_MARKERS
				Surface_DrawLine(screenCoords->vx-2,screenCoords->vy,screenCoords->vx+2,screenCoords->vy,0,255,0);
				Surface_DrawLine(screenCoords->vx,screenCoords->vy-2,screenCoords->vx,screenCoords->vy+2,0,255,0);
#endif
			}
			else
			{
				*clipped=TRUE;				
#ifdef DRAW_CLIP_MARKERS
				Surface_DrawLine(screenCoords->vx-2,screenCoords->vy,screenCoords->vx+2,screenCoords->vy,255,0,0);
				Surface_DrawLine(screenCoords->vx,screenCoords->vy-2,screenCoords->vx,screenCoords->vy+2,255,0,0);
#endif
			}

			screenCoords++;
			clipped++;
			index++;
			next++;

			tempCycle+=8;
			tempCycle&=(COS_TABLE_SIZE-1);

		}
	}

	if (!legoGlobs.pauseFlag)
	{
		cycle++;
		cycle&=(COS_TABLE_SIZE-1);
	}

#ifdef DRAW_CLIP_MARKERS
//	Surface_DrawLine(-HALF_CLIP_WIDTH,-HALF_CLIP_HEIGHT,HALF_CLIP_WIDTH,-HALF_CLIP_HEIGHT,255,255,255);
//	Surface_DrawLine(HALF_CLIP_WIDTH,-HALF_CLIP_HEIGHT,HALF_CLIP_WIDTH,HALF_CLIP_HEIGHT,255,255,255);
//	Surface_DrawLine(-HALF_CLIP_WIDTH,HALF_CLIP_HEIGHT,HALF_CLIP_WIDTH,HALF_CLIP_HEIGHT,255,255,255);
//	Surface_DrawLine(-HALF_CLIP_WIDTH,-HALF_CLIP_HEIGHT,-HALF_CLIP_WIDTH,HALF_CLIP_HEIGHT,255,255,255);
#endif
}



/*
	=====================================================================================================================
	the new world mesh display. The end of HMD. Death to HMD. etc.
	---------------------------------------------------------------------------------------------------------------------

	HMD makes no sense for this task, it gives no control over the mesh, it's bulky, and it
	prevents the sort problem from being effectively solved.
	The answer is to generate the mesh by hand using AddPrim();

	Benefits:
				Optimizations as below.
				Control of faces directly - highlight, texture change etc.
				Control of lighting. Cheap fake lighting without the cost of normal generation.
				Cure for the sort problem.
				Should be as fast as HMD, certainly with the optimizations in place.
				generated vertex buffer can be used for the radar display, saving extra calculations there.
				clipping of unseen faces.
	optimizations:

				separate vertex buffer generation, if camera does not move, don't recalculate
				Vertex buffer can also be used to aid selection.

				polygon data construction, again if it hasn't changed, it doesn't need to be regenerated.
				The two operations are distinct, if one does need regeneration, the other doesn't always need to be.
				This is much more efficient.

	=====================================================================================================================
*/
VOID Surface_rebuildWorldQuadList(lpLego_Level current_level, Sint16 mx, Sint16 my, BOOL changed)
{
						
						short				*next_screen;

						int				n,index;

						lpMap3D 				map=current_level->map;
						Lego_Block			*block_data=current_level->blockData;
						ULONG					x, y, mapSize, gridSize, meshSize, id, cy, cy1;
						Uint8					u0, v0;
						Uint32				npoly, nvert,nnorm,vnum;	//, v[4];
						lpMap3D_Texture	td;
						long					id_offset;
						int					vertex_width,this_vertex_y,next_vertex_y;
						int					show_dir,swap;
						lpLego_Block		currentBlock;

						lpMAPFACEDATA		flist,flistwall;
						int					polyCountFloor=0;
						int					polyCountWall=0;
						GsLINE				line;

						POLY_F4				*fquad;		/* for non texture quads */
#ifdef USE_GT4
						POLY_GT4				*quad;
#else
						POLY_FT4				*quad;
#endif
						int					*tzptr,*fzptr;
						int					tcount=0,fcount=0;

						Uint32				*ot=(Uint32*)gfxGlobs.Wot[gfxGlobs.bufID].org;
						int					brightness,redBrightness;
						unsigned char		*uvPtr;
						DVECTOR				*vertexList=surfaceGlobs.outputList;
						int					*szList=(int*)surfaceGlobs.szList;
						unsigned char		*clippedList=surfaceGlobs.clippedList;

						Uint16				skip_flag=(Input_PadData(0) & PAD_SEL);

						short					noTexFlag=surfaceGlobs.noTextureFlag;


	static	uvwrap=0;

	static const	TEXTURE_UV			block_uv[]=
												{
													{0,0, 63,0, 0,63, 63,63},
													{63,0, 63,63, 0,0, 0,63},
													{63,63, 0,63, 63,0, 0,0},
													{0,63, 0,0, 63,63, 63,0},

													{63,0, 63,63, 0,0, 0,63},		/* ... and split the other way */
													{63,63, 0,63, 63,0, 0,0},
													{0,63, 0,0, 63,63, 63,0},
													{0,0, 63,0, 0,63, 63,63},

													{0,0, 47,0, 0,47, 47,47},
													{0,0, 47,0, 0,47, 47,47},
													{0,0, 47,0, 0,47, 47,47},
													{0,0, 47,0, 0,47, 47,47},

													{47,0, 47,47, 0,0, 0,47},
													{47,8, 47,47, 8,8, 8,47},
													{47,8, 47,47, 8,8, 8,47},
													{47,8, 47,47, 8,8, 8,47},
												};

	static const unsigned char			uvOffset[]=
												{


													0,0,0,1,1,2,2,3,3,4,5,5,6,6,7,7,
													7,7,6,6,5,5,4,3,3,2,2,1,1,0,0,0,
													0,0,0,1,1,2,2,3,3,4,5,5,6,6,7,7,
													7,7,6,6,5,5,4,3,3,2,2,1,1,0,0,0,



													0,0,1,2,3,4,5,6,7,9,10,11,12,13,14,15,
													15,14,13,12,11,10,9,7,6,5,4,3,2,1,0,0,

													0,0,1,2,3,4,5,6,7,9,10,11,12,13,14,15,
													15,14,13,12,11,10,9,7,6,5,4,3,2,1,0,0

												};

	static	int	suvIndex=0;
				int	muvIndex;
				int	uvIndex;
				int	vIndex;

#define	UVSF (2)

/* transform the world vertices */

	Surface_rebuildVertexBuffer(current_level,mx,my,changed);		/* full re-build for now */

	quad=&surfaceGlobs.quadList.tList[GsGetActiveBuff()].tQuad[surfaceGlobs.quadList.tList[GsGetActiveBuff()].tQuadLength];
	fquad=&surfaceGlobs.quadList.fList[GsGetActiveBuff()].fQuad[surfaceGlobs.quadList.fList[GsGetActiveBuff()].fQuadLength];

	tzptr=&surfaceGlobs.quadList.tList[GsGetActiveBuff()].tz[surfaceGlobs.quadList.tList[GsGetActiveBuff()].tQuadLength];
	fzptr=&surfaceGlobs.quadList.fList[GsGetActiveBuff()].fz[surfaceGlobs.quadList.fList[GsGetActiveBuff()].fQuadLength];


	muvIndex=suvIndex+(my*8*(1<<UVSF))+(mx*4*(1<<UVSF));
	
	for(y=0; y<(surfaceGlobs.vertexSpan-1); y++)
	{
		this_vertex_y=next_vertex_y=y*surfaceGlobs.vertexSpan;
		next_vertex_y+=surfaceGlobs.vertexSpan;

		uvIndex=(muvIndex>>UVSF)+(y*8);
	
		for(x=0; x<(surfaceGlobs.vertexSpan-1); x++)
		{

		/* we only ignore the quad if all vertices are clipped */

			if (!clippedList[this_vertex_y+x] || !clippedList[this_vertex_y+x+1] || !clippedList[next_vertex_y+x] || !clippedList[next_vertex_y+x+1])
			{			
		 			id = ((y+my)*map->gridWidth)+x+mx;
	  //			if (noTexFlag)
	//				td = &map->textureData[49];
//				else

		 //		if (block_data[id].flags & LEGOBLOCK_FLAG_BLOCK_DUG)
	  //				td = &map->textureData[63];		/* show undug as white texture */
	//			else 
					td = &map->textureData[block_data[id].blockTexture];

				currentBlock=&block_data[id];

				if (block_data[id].flags & MAP3DBLOCK_HIGHLIGHT)
					td = &map->textureData[49];
				

				show_dir=currentBlock->direction;
				swap=FALSE;

				if (block_data[id].flags & MAP3DBLOCK_FLAGROTATED)		/* flag settings will need checking */
				{
					int	brightness;

					show_dir+=4;
					swap=TRUE;

					quad->x0=vertexList[this_vertex_y+(x+1)].vx;
					quad->y0=vertexList[this_vertex_y+(x+1)].vy;

					quad->x1=vertexList[next_vertex_y+(x+1)].vx;
					quad->y1=vertexList[next_vertex_y+(x+1)].vy;

					quad->x2=vertexList[this_vertex_y+x].vx;
					quad->y2=vertexList[this_vertex_y+x].vy;

					quad->x3=vertexList[next_vertex_y+x].vx;
					quad->y3=vertexList[next_vertex_y+x].vy;


					brightness=currentBlock[1].wobble>>COLOUR_SHIFT;
					quad->r0=currentBlock[1].redLit+currentBlock[1].redWobble;
					quad->g0=currentBlock[1].greenLit+brightness;
					quad->b0=currentBlock[1].blueLit;

					brightness=currentBlock[map->gridWidth+1].wobble>>COLOUR_SHIFT;
					quad->r1=currentBlock[map->gridWidth+1].redLit+currentBlock[map->gridWidth+1].redWobble;
					quad->g1=currentBlock[map->gridWidth+1].greenLit+brightness;
					quad->b1=currentBlock[map->gridWidth+1].blueLit;

					brightness=currentBlock->wobble>>COLOUR_SHIFT;
					quad->r2=currentBlock->redLit+currentBlock->redWobble;
					quad->g2=currentBlock->greenLit+brightness;
					quad->b2=currentBlock->blueLit;

					brightness=currentBlock[map->gridWidth].wobble>>COLOUR_SHIFT;
					quad->r3=currentBlock[map->gridWidth].redLit+currentBlock[map->gridWidth].redWobble;
					quad->g3=currentBlock[map->gridWidth].greenLit+brightness;
					quad->b3=currentBlock[map->gridWidth].blueLit;


					u0 = td->offsetX;
					v0 = td->offsetY;
					quad->clut=td->clut;
					quad->tpage=td->tPage;


					if (block_data[id].flags & MAP3DBLOCK_UVWOBBLES)
					{
						uvPtr=(unsigned char*) &block_uv[show_dir+8].tu0;

						quad->u0=u0+*uvPtr++;
						quad->v0=v0+*uvPtr++;

						quad->u1=u0+*uvPtr++;
						quad->v1=v0+*uvPtr++;

						quad->u2=u0+*uvPtr++;
						quad->v2=v0+*uvPtr++;

						quad->u3=u0+*uvPtr++;
						quad->v3=v0+*uvPtr++;

						vIndex=uvIndex+9;
						vIndex&=31;
						uvIndex&=31;

						quad->u0+=uvOffset[uvIndex+4];
						quad->v0+=uvOffset[vIndex+4];

						quad->u1+=uvOffset[uvIndex+12];
						quad->v1+=uvOffset[vIndex+12];

						quad->u2+=uvOffset[uvIndex];
						quad->v2+=uvOffset[vIndex];

						quad->u3+=uvOffset[uvIndex+8];
						quad->v3+=uvOffset[vIndex+8];

					}
					else
					{
						uvPtr=(unsigned char*) &block_uv[show_dir].tu0;

						quad->u0=u0+*uvPtr++;
						quad->v0=v0+*uvPtr++;

						quad->u1=u0+*uvPtr++;
						quad->v1=v0+*uvPtr++;

						quad->u2=u0+*uvPtr++;
						quad->v2=v0+*uvPtr++;

						quad->u3=u0+*uvPtr++;
						quad->v3=v0+*uvPtr++;

					}


				}
				else			/* non rotated */
				{
					int	brightness;

					quad->x0=vertexList[this_vertex_y+x].vx;
					quad->y0=vertexList[this_vertex_y+x].vy;

					quad->x1=vertexList[this_vertex_y+(x+1)].vx;
					quad->y1=vertexList[this_vertex_y+(x+1)].vy;

					quad->x2=vertexList[next_vertex_y+x].vx;
					quad->y2=vertexList[next_vertex_y+x].vy;

					quad->x3=vertexList[next_vertex_y+(x+1)].vx;
					quad->y3=vertexList[next_vertex_y+(x+1)].vy;


					brightness=currentBlock->wobble>>COLOUR_SHIFT;

					quad->r0=currentBlock->redLit+currentBlock->redWobble;
					quad->g0=currentBlock->greenLit+brightness;
					quad->b0=currentBlock->blueLit;

					brightness=currentBlock[1].wobble>>COLOUR_SHIFT;

					quad->r1=currentBlock[1].redLit+currentBlock[1].redWobble;
					quad->g1=currentBlock[1].greenLit+brightness;
					quad->b1=currentBlock[1].blueLit;

					brightness=currentBlock[map->gridWidth].wobble>>COLOUR_SHIFT;

					quad->r2=currentBlock[map->gridWidth].redLit+currentBlock[map->gridWidth].redWobble;
					quad->g2=currentBlock[map->gridWidth].greenLit+brightness;
					quad->b2=currentBlock[map->gridWidth].blueLit;

					brightness=currentBlock[map->gridWidth+1].wobble>>COLOUR_SHIFT;

					quad->r3=currentBlock[map->gridWidth+1].redLit+currentBlock[map->gridWidth+1].redWobble;
					quad->g3=currentBlock[map->gridWidth+1].greenLit+brightness;
					quad->b3=currentBlock[map->gridWidth+1].blueLit;



					u0 = td->offsetX;
					v0 = td->offsetY;
					quad->clut=td->clut;
					quad->tpage=td->tPage;


					if (block_data[id].flags & MAP3DBLOCK_UVWOBBLES)
					{
						uvPtr=(unsigned char*) &block_uv[show_dir+8].tu0;

						quad->u0=u0+*uvPtr++;
						quad->v0=v0+*uvPtr++;

						quad->u1=u0+*uvPtr++;
						quad->v1=v0+*uvPtr++;

						quad->u2=u0+*uvPtr++;
						quad->v2=v0+*uvPtr++;

						quad->u3=u0+*uvPtr++;
						quad->v3=v0+*uvPtr++;

						vIndex=uvIndex+9;
						vIndex&=31;
						uvIndex&=31;

						quad->u0+=uvOffset[uvIndex];
						quad->v0+=uvOffset[vIndex];

						quad->u1+=uvOffset[uvIndex+4];
						quad->v1+=uvOffset[vIndex+4];

						quad->u2+=uvOffset[uvIndex+8];
						quad->v2+=uvOffset[vIndex+8];

						quad->u3+=uvOffset[uvIndex+12];
						quad->v3+=uvOffset[vIndex+12];

					}
					else
					{
						uvPtr=(unsigned char*) &block_uv[show_dir].tu0;

						quad->u0=u0+*uvPtr++;
						quad->v0=v0+*uvPtr++;

						quad->u1=u0+*uvPtr++;
						quad->v1=v0+*uvPtr++;

						quad->u2=u0+*uvPtr++;
						quad->v2=v0+*uvPtr++;

						quad->u3=u0+*uvPtr++;
						quad->v3=v0+*uvPtr++;

					}


				}

		/* we don't use AddPrim here, we just cache the primitives, and build the list later */

				if (block_data[id].flags & LEGOBLOCK_FLAG_USE_TRANS_Z)
				{
					*tzptr++=szList[this_vertex_y+x];
			  	}
				else
				{
					*tzptr++=gfxGlobs.otSize-(y+1);
				}

				tcount++;
				quad++;
			}


			uvIndex+=4;
		}
	}

	uvwrap++;
	uvwrap&=63;

	if (!legoGlobs.pauseFlag)
		suvIndex+=4;

	surfaceGlobs.quadList.tList[GsGetActiveBuff()].tQuadLength+=tcount;
	surfaceGlobs.quadList.fList[GsGetActiveBuff()].fQuadLength+=fcount;


//	Surface_DisplayTVScreen();

/* display quads drawn/clipped */

#ifndef __CDVERSION
	{
		char	string[64];

		sprintf(string,"q=%d/%d",tcount,(surfaceGlobs.vertexSpan-1)*(surfaceGlobs.vertexSpan-1));
		Font_PrintF(legoGlobs.stdFont,32,8,string);
	}	
#endif

}


#define	RADAR_SCALE		(0)

/*

	new radar display using vertex buffer
	generates a filled display, using different colours for floor/wall

*/



/*
	display a screen showing the game
*/
void	Surface_DisplayTVScreen(void)
{

				GsSPRITE			s;
				unsigned 		short	tpage;
				POLY_GT4			*quad;

				long				depth=14,flag,sort;
				SVECTOR			vector;

				GsCOORDINATE2	coord;
				MATRIX			mat;
				short				coords[3];

	static	unsigned 		int attr=0x02000000;
	static	int				frame=0;
				int				*tzptr;

	quad=&surfaceGlobs.quadList.tList[GsGetActiveBuff()].tQuad[surfaceGlobs.quadList.tList[GsGetActiveBuff()].tQuadLength];
	tzptr=&surfaceGlobs.quadList.tList[GsGetActiveBuff()].tz[surfaceGlobs.quadList.tList[GsGetActiveBuff()].tQuadLength];

	GsInitCoordinate2(WORLD, &coord);
	GsGetLs(&coord, &mat);
	GsSetLsMatrix(&mat);



	if ((frame&1)==0)
		tpage=getTPage(2,0,0,0);
	else
		tpage=getTPage(2,0,0,256);


//#ifdef 0

	vector.vx=-(20<<9);
	vector.vy=-(1024);
	vector.vz=(4<<9);
	gte_RotTransPers(&vector,(long*)&coords[0],&depth,&flag,&sort);

	quad->x0=coords[0];
	quad->y0=coords[1];

	vector.vx=-(21<<9);
	gte_RotTransPers(&vector,(long*)&coords[0],&depth,&flag,&sort);
	quad->x1=coords[0];
	quad->y1=coords[1];

	vector.vx=-(20<<9);
	vector.vy=-(512);
	gte_RotTransPers(&vector,(long*)&coords[0],&depth,&flag,&sort);
	quad->x2=coords[0];
	quad->y2=coords[1];

	vector.vx=-(21<<9);
	gte_RotTransPers(&vector,(long*)&coords[0],&depth,&flag,&sort);
	quad->x3=coords[0];
	quad->y3=coords[1];


	quad->r0=128;
	quad->g0=128;
	quad->b0=128;

	quad->r1=128;
	quad->g1=128;
	quad->b1=128;

	quad->r2=128;
	quad->g2=128;
	quad->b2=128;

	quad->r3=128;
	quad->g3=128;
	quad->b3=128;

	quad->tpage=tpage;

	quad->u0=0;
	quad->v0=0;

	quad->u1=255;
	quad->v1=0;

	quad->u2=0;
	quad->v2=255;

	quad->u3=255;
	quad->v3=255;

	*tzptr++=10;
	surfaceGlobs.quadList.tList[GsGetActiveBuff()].tQuadLength++;
//#endif

#ifdef 0
		s.w = 128;
		s.h = 128;
		s.u = 0;
		s.v = 0;
		s.tpage=tpage;
		s.cx = 512;
		s.cy = 511;
		s.mx = s.my = s.rotate = NULL;
		s.scalex = s.scaley = ONE;

		s.r = s.g = s.b = 128;
		s.x = (0)-192;
		s.y = 0-128;
		s.attribute = attr;
		GsSortFastSprite(&s, &gfxGlobs.Wot[gfxGlobs.bufID], 11);
		frame++;

#endif


}








#ifdef 0

void	rebuildRadarQuadList(lpLego_Level current_level, Sint16 mx, Sint16 my)
{

	int				x,y,id;
	lpMap3D 			map=current_level->map;
	Lego_Block		*block_data=current_level->blockData;
	int				this_vertex_y,next_vertex_y;
	POLY_F4			*fquad;
	Uint32			*ot=(Uint32*)gfxGlobs.Wot[gfxGlobs.bufID].org;


	fquad=&worldQuadListFlat[0][GsGetActiveBuff()];
	
	for(y=0; y<map->meshHeight; y++)
	{
		this_vertex_y=next_vertex_y=y*VERTEXSPAN;
		next_vertex_y+=VERTEXSPAN;

		for(x=0; x<map->meshWidth; x++)
		{
			id = ((y+my)*map->gridWidth)+x+mx;

			if (block_data[id].flags & LEGOBLOCK_FLAG_FLOOR)
			{
				fquad->r0=(y*16);
				fquad->g0=128+(x*8);			/* floors are green */
				fquad->b0=0;
			}
			else
			{
				fquad->r0=128;			/* walls are red */
				fquad->g0=0;
				fquad->b0=(y*32);

			}

			fquad->x0=outputList[this_vertex_y+x].vx >> RADAR_SCALE;
			fquad->y0=outputList[this_vertex_y+x].vy >> RADAR_SCALE;

			fquad->x1=outputList[this_vertex_y+(x+1)].vx >> RADAR_SCALE;
			fquad->y1=outputList[this_vertex_y+(x+1)].vy >> RADAR_SCALE;

			fquad->x2=outputList[next_vertex_y+x].vx >> RADAR_SCALE;
			fquad->y2=outputList[next_vertex_y+x].vy >> RADAR_SCALE;

			fquad->x3=outputList[next_vertex_y+(x+1)].vx >> RADAR_SCALE;
			fquad->y3=outputList[next_vertex_y+(x+1)].vy >> RADAR_SCALE;

			AddPrim(ot+(gfxGlobs.otSize-1),fquad);

			fquad++;
		}
	}
}
#endif



/*
	external call for primitive list building
*/
VOID	Surface_addPrimList(void)
{
	Surface_addQuadList(&surfaceGlobs.quadList);
}


/*
	add all cached primitives to draw list

	We do this in a block to avoid the problem of adding primitives to
	an OT before the hardware has finished initialising it in a 
	GsClearOt() call
*/
VOID	Surface_addQuadList(lpQUAD_LIST quadList)
{

#ifdef USE_GT4
	POLY_GT4				*tquad;
#else
	POLY_FT4				*tquad;
#endif
	POLY_F4				*fquad;		/* for non texture quads */
	int					*tzptr,*fzptr;
	int					n,len;
	Uint32				*ot=(Uint32*)gfxGlobs.Wot[gfxGlobs.bufID].org;

	tquad=&quadList->tList[GsGetActiveBuff()].tQuad[0];
	fquad=&quadList->fList[GsGetActiveBuff()].fQuad[0];

	tzptr=&quadList->tList[GsGetActiveBuff()].tz[0];
	fzptr=&quadList->fList[GsGetActiveBuff()].fz[0];

/* first the texture quads... */

	len=quadList->tList[GsGetActiveBuff()].tQuadLength;

	for (n=0; n<len; n++)
		AddPrim(ot+(*tzptr++),tquad++);
	quadList->tList[GsGetActiveBuff()].tQuadLength=0;		/* clear for next time */

/* ...and now the untextured */

	len=quadList->fList[GsGetActiveBuff()].fQuadLength;

	for (n=0; n<len; n++)
		AddPrim(ot+(*fzptr++),fquad++);
	quadList->fList[GsGetActiveBuff()].fQuadLength=0;		/* ditto */

}


/*
	external call for double buffered primitive list initialisation
*/
VOID	Surface_initialiseWorldQuadList(void)
{
	int	n,step=ONE/COS_TABLE_SIZE;

	surfaceGlobs.vertexSpan=10;		//VERTEXSPAN+3;			/* default */
	Surface_initialiseQuadList(&surfaceGlobs.quadList);
	surfaceGlobs.noTextureFlag=FALSE;

/* initialise cos table for vertex manipulation */

	for (n=0; n<COS_TABLE_SIZE; n++)
		cosTable[n]=rcos(n*step)>>6;
}



VOID	Surface_initialiseQuadList(lpQUAD_LIST quadList)
{
	int	n,j;

	for (j=0; j<2; j++)
	{
		quadList->tList[j].tQuadLength=0;
		for (n=0; n<(MAX_TQ); n++)
		{
#ifdef USE_GT4
			SetPolyGT4(&quadList->tList[j].tQuad[n]);
#else
			SetPolyFT4(&quadList->tList[j].tQuad[n]);
#endif
		}

		quadList->fList[j].fQuadLength=0;
		for (n=0; n<(MAX_FQ); n++)
		{
			SetPolyF4(&quadList->fList[j].fQuad[n]);
		}
	}
}


/*
	get height at passed point
	returns FALSE if outside map
*/
BOOL	Surface_GetHeight(lpLego_Level current_level, int x, int z, int *height)
{
	lpMap3D		map=current_level->map;
	int			blockx=x>>9;
	int			blockz=z>>9;
	long			xoffset=x & 511;
	long			zoffset=z & 511;
	int			vheight[4];

	int			xtopdelta,xtopheight;
	int			xbottomdelta,xbottomheight;
	int			finalheight,zdelta;

	
	if (blockx<0 || blockx>current_level->width || blockz<0 || blockz>current_level->width)
		return	FALSE;

/* get base heights */

	vheight[0]=ToFIXED(-mapBlockValue(map, blockx, blockz).topLeftAlt);
	vheight[0]+=(mapBlockValue(map, blockx, blockz).wobble<<12);	

	vheight[1]=ToFIXED(-mapBlockValue(map, blockx+1, blockz).topLeftAlt);	
	vheight[1]+=(mapBlockValue(map, blockx+1, blockz).wobble<<12);	

	vheight[2]=ToFIXED(-mapBlockValue(map, blockx, blockz+1).topLeftAlt);	
	vheight[2]+=(mapBlockValue(map, blockx, blockz+1).wobble<<12);
	
	vheight[3]=ToFIXED(-mapBlockValue(map, blockx+1, blockz+1).topLeftAlt);	
	vheight[3]+=(mapBlockValue(map, blockx+1, blockz+1).wobble<<12);	

	xtopdelta=vheight[0]-vheight[1];
	xtopheight=vheight[0]-Asm_MulFIX(Asm_DivFIX(ToFIXED(xoffset),ToFIXED(512)),xtopdelta);

	xbottomdelta=vheight[2]-vheight[3];
	xbottomheight=vheight[2]-Asm_MulFIX(Asm_DivFIX(ToFIXED(xoffset),ToFIXED(512)),xbottomdelta);

	zdelta=xtopheight-xbottomheight;
	finalheight=FromFIXED(xtopheight-Asm_MulFIX(Asm_DivFIX(ToFIXED(zoffset),ToFIXED(512)),zdelta));

#ifdef 0
	{

		char			string[64];
		GsBOXF		box;



		box.x=80-(gfxGlobs.scrW>>1);
		box.y=140-(gfxGlobs.scrH>>1);
		box.w=160;
		box.h=100;
		box.r=box.b=box.g=0;
		box.attribute=(GsALON);	// | GsAONE);		/* semi trans enabled, blend of 100% background + 100% foreground */
		GsSortBoxFill(&box, &gfxGlobs.Wot[gfxGlobs.bufID], 10);


		sprintf(string, "|3bx=%d, by=%d", blockx,blockz);
		Font_PrintF(legoGlobs.stdFont,180,180,string);
	
		sprintf(string, "|2xtd=%d, xth=%d", FromFIXED(xtopdelta),FromFIXED(xtopheight));
		Font_PrintF(legoGlobs.stdFont,100,150,string);


		sprintf(string, "%d", FromFIXED(vheight[0]));
		Font_PrintF(legoGlobs.stdFont,100,160,string);

		sprintf(string, "%d", FromFIXED(vheight[1]));
		Font_PrintF(legoGlobs.stdFont,150,160,string);

		sprintf(string, "%d", FromFIXED(vheight[2]));
		Font_PrintF(legoGlobs.stdFont,100,200,string);

		sprintf(string, "%d", FromFIXED(vheight[3]));
		Font_PrintF(legoGlobs.stdFont,150,200,string);

		sprintf(string, "|2xbd=%d, xbh=%d", FromFIXED(xbottomdelta),FromFIXED(xbottomheight));
		Font_PrintF(legoGlobs.stdFont,100,220,string);




		sprintf(string, "%d", finalheight);
		Font_PrintF(legoGlobs.stdFont,125,180,string);
	}
#endif
	
	*height=finalheight;
	return	TRUE;
}

/*
	get height at passed point
	returns FALSE if outside map
*/
BOOL	Surface_GetHeightAndBrightness(lpLego_Level current_level, int x, int z, int *height, unsigned char *brightness)
{
	lpMap3D		map=current_level->map;
	int			blockx=x>>9;
	int			blockz=z>>9;
	long			xoffset=x & 511;
	long			zoffset=z & 511;
	int			vheight[4];

	int			xtopdelta,xtopheight;
	int			xbottomdelta,xbottomheight;
	int			finalheight,zdelta;

	if (blockx<0 || blockx>current_level->width || blockz<0 || blockz>current_level->width)
		return	FALSE;

/* get base heights */

	vheight[0]=ToFIXED(-mapBlockValue(map, blockx, blockz).topLeftAlt);
	vheight[0]+=(mapBlockValue(map, blockx, blockz).wobble<<12);	

	vheight[1]=ToFIXED(-mapBlockValue(map, blockx+1, blockz).topLeftAlt);	
	vheight[1]+=(mapBlockValue(map, blockx+1, blockz).wobble<<12);	

	vheight[2]=ToFIXED(-mapBlockValue(map, blockx, blockz+1).topLeftAlt);	
	vheight[2]+=(mapBlockValue(map, blockx, blockz+1).wobble<<12);
	
	vheight[3]=ToFIXED(-mapBlockValue(map, blockx+1, blockz+1).topLeftAlt);	
	vheight[3]+=(mapBlockValue(map, blockx+1, blockz+1).wobble<<12);	

	xtopdelta=vheight[0]-vheight[1];
	xtopheight=vheight[0]-Asm_MulFIX(Asm_DivFIX(ToFIXED(xoffset),ToFIXED(512)),xtopdelta);

	xbottomdelta=vheight[2]-vheight[3];
	xbottomheight=vheight[2]-Asm_MulFIX(Asm_DivFIX(ToFIXED(xoffset),ToFIXED(512)),xbottomdelta);

	zdelta=xtopheight-xbottomheight;
	finalheight=FromFIXED(xtopheight-Asm_MulFIX(Asm_DivFIX(ToFIXED(zoffset),ToFIXED(512)),zdelta));

	*height=finalheight;
	*brightness=mapBlockValue(map, blockx, blockz).lightSetting;

	return	TRUE;
}


/*
	get height at passed point but ignores the effect of wobble, ie water/lava is treated as calm
	returns FALSE if outside map
*/
BOOL	Surface_GetHeightFlat(lpLego_Level current_level, int x, int z, int *height)
{
	lpMap3D		map=current_level->map;
	int			blockx=x>>9;
	int			blockz=z>>9;
	long			xoffset=x & 511;
	long			zoffset=z & 511;
	int			vheight[4];

	int			xtopdelta,xtopheight;
	int			xbottomdelta,xbottomheight;
	int			finalheight,zdelta;

	if (blockx<0 || blockx>current_level->width || blockz<0 || blockz>current_level->width)
		return	FALSE;

/* get base heights */

	vheight[0]=ToFIXED(-mapBlockValue(map, blockx, blockz).topLeftAlt);
	vheight[1]=ToFIXED(-mapBlockValue(map, blockx+1, blockz).topLeftAlt);	
	vheight[2]=ToFIXED(-mapBlockValue(map, blockx, blockz+1).topLeftAlt);	
	vheight[3]=ToFIXED(-mapBlockValue(map, blockx+1, blockz+1).topLeftAlt);	

	xtopdelta=vheight[0]-vheight[1];
	xtopheight=vheight[0]-Asm_MulFIX(Asm_DivFIX(ToFIXED(xoffset),ToFIXED(512)),xtopdelta);

	xbottomdelta=vheight[2]-vheight[3];
	xbottomheight=vheight[2]-Asm_MulFIX(Asm_DivFIX(ToFIXED(xoffset),ToFIXED(512)),xbottomdelta);

	zdelta=xtopheight-xbottomheight;
	finalheight=FromFIXED(xtopheight-Asm_MulFIX(Asm_DivFIX(ToFIXED(zoffset),ToFIXED(512)),zdelta));
	
	*height=finalheight;
	return	TRUE;
}



/*
	set up three vertices from map position
*/
void	Surface_SetUpVertices(lpLego_Level current_level, int bx, int by,  VECTOR *vertex0, VECTOR *vertex1, VECTOR *vertex2)
{
	lpMap3D		map=current_level->map;
	int			blockx=bx>>9,blocky=by>>9;

	

	if (mapBlockValue(map, blockx, blocky).flags & MAP3DBLOCK_FLAGROTATED)		/* quad splits the opposite way */
 	{
		if ((bx&511)>((by&511)))
		{
			vertex0->vx=-((blockx)<<9);
			vertex0->vy=-mapBlockValue(map, blockx, blocky).topLeftAlt;
			vertex0->vy+=mapBlockValue(map, blockx, blocky).wobble;
			vertex0->vz=((blocky)<<9);

			vertex1->vx=-((blockx+1)<<9);
			vertex1->vy=-mapBlockValue(map, blockx+1, blocky).topLeftAlt;
			vertex1->vy+=mapBlockValue(map, blockx+1, blocky).wobble;
			vertex1->vz=((blocky)<<9);

			vertex2->vx=-((blockx+1)<<9);
			vertex2->vy=-mapBlockValue(map, blockx+1, blocky+1).topLeftAlt;
			vertex2->vy+=mapBlockValue(map, blockx+1, blocky+1).wobble;
			vertex2->vz=((blocky+1)<<9);
		}
		else
		{
			vertex0->vx=-((blockx)<<9);
			vertex0->vy=-mapBlockValue(map, blockx, blocky).topLeftAlt;
			vertex0->vy+=mapBlockValue(map, blockx, blocky).wobble;
			vertex0->vz=((blocky)<<9);

			vertex1->vx=-((blockx+1)<<9);
			vertex1->vy=-mapBlockValue(map, blockx+1, blocky+1).topLeftAlt;
			vertex1->vy+=mapBlockValue(map, blockx+1, blocky+1).wobble;
			vertex1->vz=((blocky+1)<<9);

			vertex2->vx=-((blockx)<<9);
			vertex2->vy=-mapBlockValue(map, blockx, blocky+1).topLeftAlt;
			vertex2->vy+=mapBlockValue(map, blockx, blocky+1).wobble;
			vertex2->vz=((blocky+1)<<9);
		}
	}
	else		/* normal split */
	{
		if ((by&511)>(512-(bx&511)))
		{
			vertex0->vx=-((blockx+1)<<9);
			vertex0->vy=-mapBlockValue(map, blockx+1, blocky).topLeftAlt;
			vertex0->vy+=mapBlockValue(map, blockx+1, blocky).wobble;
			vertex0->vz=((blocky)<<9);

			vertex1->vx=-((blockx+1)<<9);
			vertex1->vy=-mapBlockValue(map, blockx+1, blocky+1).topLeftAlt;
			vertex1->vy+=mapBlockValue(map, blockx+1, blocky+1).wobble;
			vertex1->vz=((blocky+1)<<9);

			vertex2->vx=-((blockx)<<9);
			vertex2->vy=-mapBlockValue(map, blockx, blocky+1).topLeftAlt;
			vertex2->vy+=mapBlockValue(map, blockx, blocky+1).wobble;
			vertex2->vz=((blocky+1)<<9);
		}
		else
		{
			vertex0->vx=-((blockx)<<9);
			vertex0->vy=-mapBlockValue(map, blockx, blocky).topLeftAlt;
			vertex0->vy+=mapBlockValue(map, blockx, blocky).wobble;
			vertex0->vz=((blocky)<<9);

			vertex1->vx=-((blockx+1)<<9);
			vertex1->vy=-mapBlockValue(map, blockx+1, blocky).topLeftAlt;
			vertex1->vy+=mapBlockValue(map, blockx+1, blocky).wobble;
			vertex1->vz=((blocky)<<9);

			vertex2->vx=-((blockx)<<9);
			vertex2->vy=-mapBlockValue(map, blockx, blocky+1).topLeftAlt;
			vertex2->vy+=mapBlockValue(map, blockx, blocky+1).wobble;
			vertex2->vz=((blocky+1)<<9);
		}
	}
}




/* MOVEME: to surface.c */
/*
	use object position to calculate vertices used for orientation triangle
	also returns the three height points in heights->vx/vy/vz
*/
BOOL	Surface_SetUpVerticesFromContainer(lpContainer cont,VECTOR *v1, VECTOR *v2, VECTOR *v3, int *averageHeight, int angle, int radius, int spread)
{
	VECTOR3D	pos,ref;
	int		xd,yd;
	int		height;
	int		ref_y;
	int		totalHeight=0;

	Container_GetPosition(cont,&pos);

/* get reference position */
	ref.x=-pos.x;
	ref.z=pos.y;

	if (!Surface_GetHeight(legoGlobs.currLevel,-ref.x,ref.z,&ref_y))
		return	FALSE;

	ref.y=ref_y;
	*averageHeight=ref_y;


	xd=rsin(angle-2048);
	yd=rcos(angle-2048);
	v1->vx=-(pos.x-Asm_MulFIX(radius>>1,xd));
	v1->vz=pos.y+Asm_MulFIX(radius>>1,yd);
	if (Surface_GetHeight(legoGlobs.currLevel,-v1->vx,v1->vz,&height))
	{
		v1->vy=height;
		totalHeight=height<<1;
	}
	else
		return	FALSE;

	xd=rsin(angle-spread);
	yd=rcos(angle-spread);

	v2->vx=-(pos.x-Asm_MulFIX(radius,xd));
	v2->vz=pos.y+Asm_MulFIX(radius,yd);
	if (Surface_GetHeight(legoGlobs.currLevel,-v2->vx,v2->vz,&height))
	{
		v2->vy=height;
		totalHeight+=height;
	}
	else
		return	FALSE;


	xd=rsin(angle+spread);
	yd=rcos(angle+spread);

	v3->vx=-(pos.x-Asm_MulFIX(radius,xd));
	v3->vz=pos.y+Asm_MulFIX(radius,yd);
	if (Surface_GetHeight(legoGlobs.currLevel,-v3->vx,v3->vz,&height))
	{
		v3->vy=height;
		totalHeight+=height;
	}
	else
		return	FALSE;

	//*averageHeight=totalHeight/3;

/* scale the vertices */


	v1->vx-=ref.x;
	v1->vy-=ref.y;
	v1->vz-=ref.z;

	v2->vx-=ref.x;
	v2->vy-=ref.y;
	v2->vz-=ref.z;

	v3->vx-=ref.x;
	v3->vy-=ref.y;
	v3->vz-=ref.z;

	v1->vx<<=3;
	v1->vy<<=3;
	v1->vz<<=3;

	v2->vx<<=3;
	v2->vy<<=3;
	v2->vz<<=3;

	v3->vx<<=3;
	v3->vy<<=3;
	v3->vz<<=3;


#ifdef 0
	{
		char	string[64];

		sprintf(string, "v1.x=%d, v1.y=%d, v1.z=%d", v1->vx,v1->vy,v1->vz);
		Font_PrintF(legoGlobs.stdFont,8,60,string);

		sprintf(string, "v2.x=%d, v2.y=%d, v2.z=%d", v2->vx,v2->vy,v2->vz);
		Font_PrintF(legoGlobs.stdFont,8,68,string);

		sprintf(string, "vsddt"!12{sœ{sßßğŞŞïRRlRRk11tt®tt®dt¾cs½Zl®[l®„„½……¾Ç¾èÇ¾èRJsRJsJJZJJZÏÏßÎÎŞRRdSSd      B9RC9S„„¾„„½d|®c{­ÇÇµ¾èµ½çRJsRJsKK[JJZÏÏßÏÏß„„”„„”!!      1BR1BR„„½……¾c|®c{­d|®d|®ÇÏğÇÏğèÿÿèÿÿµ­Çµ­Æ))9))9))))!!1!!1k{œk{œk{œk{œZk®[l®[l®[l®Zk­Zk­[l®Zk­[l®Zk­Zk­Zk­Zk­Zk­[l®Zk­[l¶ZkµJc¥Jc¦|•Ç{”Çèğÿèğÿïçÿğèÿ||||!!!!!!!!1Bc1Bc{„µ|…¶[l¶[l¶Zl¶[l¶[l®Zl®Zs¥Zt¦¾Ïğ¾Ïğ¾¾Ï¾¾Ï!!!!cZ|cZ{ÏÏßÏÏßµµÆ¶¶Ç))9))9""S[|S[|c{­d|®[l®Zk­Sd®Sd®¦¶×¥µ×{sœ|t!!µµÆµµÆ¶®Ç¶®Ç11      !!1!!1s{œs{œs{¶t|¶„„½„„½®¾ß®¾ß¦Ç¥œÆ!!……•„„”­­½®®¾!!1!!1      !!1!!1s{œs{œ|…¶{„µ……¾……¾¾¶ß½µßB9RC:Sddtccs××è××èddtddt      9Bc9Bc[l¶Zk¶ZkµZk¶Rc­Sd®s{µs{µßßøßßøccsccs!!21{s{sœŞŞïßßğSSlRRk21ss­ss®cs¾cs½Zk®Zk­„„¾……¾Æ½çÇ½èSKtRJtJJZJJZÎÎŞÏÏßRRcSSd      B9RC:S……¾„„¾c{­c{­ÇÇ¶¾è¶¾èRJtRJs		JJZJJ[ÎÎŞÏÏß……•„„”"!      2CS1BR„„¾……¾c|®d|®d|®c{­ÇÏğÆÎğèÿÿèÿÿ¶®Ç¶®Ç))9)):))))!!1""2k{œk{l|k{Zk®[l®Zk­[l®[l®Zk­Sd®Sd®Zk¶Zk¶ZkµZk¶[l®[l®Zk­[l®Zk¶ZkµJc¦Kd¦{”Î|•Ïçÿÿèÿÿïçÿğèÿ{{||!!!!""""2:[19Z|…¶|…¶Zk¶[l¶Zk¶Zk¶Zk­Zk®Zs¥Zs¥¾Çè½Æç¶®Ç¶­Ç!!    S[|RZ{ÆÆÖÇÇ×¥¥µ¦¦¶11RZ{RZ{ss­ss­ZkµZk¶Rc­Rc­¦Ï¦Ïsk”tl•!!¶®Ç¶®Çœœ­œœ­))    !!1!!1s{œs{œ|…¶{„µ„„¾……¾¥µ×¦¶×•¶œ”µ!!……•„„”®®::      !!2!!1s{œt|{„µ{„µ„„½„„½¶®Çµ­Ç11B11BccscctÎÆŞÏÇßZZkZZk      :Cd9BdZk¶ZkµZl¶[l¶Jd¦Jc¥t|¶s{µ××èÖÖçRRkRRk11ks•ks”××è××èJJ[KK[11tt®ss­d|®d|®Zk­Zk­……¾……¾¾¶×½µÖJBkJBkJJ[KK[ÇÇ×ÆÆÖKK[JJZ    B9RB9R……¾……¾s{¶s{¶ÇÇ­½ß®¾ßJJZJJZ      JJZJJZÏÇßÏÇß{{Œ{{Œ    B9RB9R„„½„„½c{­c|®c|®d|®¶Ïğ¶Ïğèÿÿèÿÿ­­¾®®¾))9))9!!!!			!!1!!1ks”lt•kk¦ll¦Rc­Sd®Zk®Zk­Zkµ[l¶Rc­Rc®Zk¶Zkµ[l¶Zk¶Zl®[l®Zk®[l®Zk¶ZkµJc¥Jc¥|•Ï{”Îèÿÿèÿÿğèÿğèÿ||||!!""!!""19Z19[{„¶{…¶[l¶Zk¶Zk¶[l¶[l®Zk®[t¦[t¦½Æè¾Çè¶®Çµ­Æ!!    RZ{R[|ÇÇ×ÇÇ×¦¦¶¦¦¶11S[|RZ{ss­ss­Zk¶Zk¶Rc­Sd®¦Ï¦Ïsk•tl•"!¶®Ç¶®Çœœ­®))    !!1!!1s|s{œ{„µ{…¶„„½……¾¦¶×¥¶×•¶œ”µ!!……•„„”®œœ­99      !!1!!1t|s{œ|…¶|…¶……¾……¾¶®Ç¶®Ç22C11BccscctÏÇßÎÆŞZZkZZk      9Bc9BcZk¶Zk¶[l¶Zk¶Jc¥Jc¦s{µs{¶ÖÖè××èRRkSSl11ks•ks”××è××èJJZKK[11ss®tt®c{®c|®[l®[l®……¾……¾¾¶×¾¶×JBkJBkJJZKK[ÇÇ×ÆÆÖJJZJJZ    B9SC:S……¾„„½s{µs|¶ÇÇ®¾ß®¾ßJJZJJZ      KK[KK[ÏÇßÎÆŞ{{Œ{{		    B9RB9R……¾„„½c{®d|®c{®d|®¶Ïğ¶Ïğèÿÿèÿÿ­­½­­½))9))9!!!!			!!1!!1ks”ks•kk¦kk¥Rc®Sd®Zk­Zk­ZkµZk¶Sd®Rd®Zk¶Zk¶ZkµZk¶Zk­Zk­Zk¶[l¶Zk¶ZkµZk­Zl®c{­c{®„Œµ…¶……•……•B9RB9R    19Z19Z……¾„„½dt¾dt¾dt¾cs¾ZkµZkµd|®d|®„Œ®…®RJsSKt"!ldlcœ”¶•¶KCdJBcS[|RZ{tt®tt®cs½dt¾[t¦Zs¥{„µ|…¶1)J1)J•®œ”­ZR{[S|		    11tt®tt®|…¶|…¶„„¾……¾„„¾……¾KClJBk      !!„„”„„”ZZkZZk      )9)9tt®ss®{„µ{„µ|…¶{„µcZ{cZ{))kk{kk{””¦””¥**:))9      9Jk9JkZkµ[l¶cs½cs½Zkµ[l¶„„½„„¾tl•sk•!!1""2))9**:„Œ­…®…®…®))!!!!kk¥kk¥ct¾dt¾Zk¶Zkµt|¶s{¶tl•sk”!B!BRRcRRcœœ­œœ­11          C:SC:S……¾……¾t|¶t|¶ÇŒŒÇt|¶s{¶!B!B    SSdSSd”¶•¶99J99K    1BR2CS„„½……¾ss®tt®c{­c{­„Œµ„Œµ”Œ­•®[[lZZk!!!!	    22ks”ks”tt®tt®Rd®Sd®[l®Zk­cs¾ct¾Sd®Rc®[l¶ZkµZkµZkµ[l®Zk®[l¶[l¶[l¶Zkµ[l®[l®d|®c{®„Œµ„Œ¶„„”……•C:SB9R    19Z19Z……¾„„¾cs½dt¾cs½dt¾ZkµZkµc|®c{­…®„Œ­RJsSKt"!ldkcŒ•¶œ”¶KCdJBdRZ{RZ|ss®ss®dt¾dt¾Zs¥[t¦{„µ{„µ1)J1)J•®•®ZR|[S|    11tt®tt®{„µ|…¶……¾„„½……¾……¾JBkJBk      !!……•„„”ZZk[[l      )9):ss­tt®|…¶{„µ{„¶{„µcZ{d[|))	ll|kk{••¦••¦))9))9      :Kl9KlZkµ[l¶cs½cs½ZkµZkµ……¾……¾sk”tk•!!1!!1))9**:…®…®„Œ­„Œ­))!!!!kk¥ll¦cs¾cs½[l¶Zkµs{µs{¶sk”sk•!B!BRRcRRc®®21          B9RB9R……¾……¾s{µs{µŒŒÆŒŒÆt|¶s{µ!B!B    RRcRRcœ”µœ”µ::K99J    1BR1BR„„¾……¾tt®tt®c{­d|®…¶„Œ¶•®•®[[l[[l!!!!    11ks”lt•tt®ss®Rc®Rc­Zl®Zk­cs½dt¾Zk®Zk­Zk¶[l¶Zk¶Zk¶Zl¶Zk¶ZkµZk¶ZkµZk¶d|¾d|¾c{­c{­2:l19k19Z2:[!C!B11B11B))9)):!1!1BJ„CK…d|¾d|¾dt¾ct¾dt¾ct¾ct¾ct¾„„Ï……Ït|¶s{¶99s99t9919Z19Z)1[)1Zt|¶s{µ„„½……¾1Bc1Bc9:9Bc9Bc1Bc2CdZZ¦ZZ¦d|¾c{¾cs½cs¾d|¾d|¾ss¾tt¾2:l19k)J)J9Jk9JkBRtBRs•Ï•ÏRRŒRRŒ"C!B9Bc9BcBRsBRs{„¶{„µ|…¶|…¶„„Î„„Î|…¶|…¶JR„KS…)J)J9Jk:KlCStBRs…®„Œ­RZ|RZ{!B!C19Z19ZS[|S[||…¶|…¶{{Æ{{Æ„„Ï„„ÎRZ”S[•*K)J19Z19[9Jk9Jks{œt|„„½……¾)1Z)1Z)1Z*2[9Jk9Jk[d•[d•cs¾dt¾dt¾cs½c{¾d|¾……¾„„½RZ•S[•!B!B!B!B2Cd1Cd9Jk9KlŒŒÇÇll¦kk¥!B!B)J*K9Bc9Bc9Bc9Bcc{½d|¾c{¾c{½cs½dt¾t|¶s{µ[dZcœ!1R!1R)1Z)1Z:Kl9Jklt•lt•ÇŒŒÇ"C!B*K*K:Cd9BcRZ{S[|……¾……¾{{Æ{{Ç……¾……¾tt®ss®!)c!)c)1Z*2[9Jk9Jkks”lt•ŒŒÇŒŒÆ9Bc9Bc!B!B9Bc9BcRZ{RZ{……¾……¾tt¾tt¾|…¶|…¶RRŒSS2CS1BR)!B)!B**:))911B11B!1!119Z2:[kk¥kk¥tt®ss®Zk­Zk­Zk¶ZkµZk¶Zk¶[l®Zk­Zk¶[l¶Zl¶[l¶ZkµZk¶Zkµ[l¶Zk¶Zk¶d|¾c{½d|®d|®19l19k19Z19Z!B!B11B11B))9))9!1!2BJ„BJ„c|¾d|¾dt¾dt¾dt¾dt¾dt¾cs¾„„Î……Ïs{µs{µ99s99s9919Z19Z)1[)1Zs{µt|¶……¾„„¾1Bc2Cd999Cd9Bc1Bc2CdZZ¥ZZ¥c{¾c{½cs¾cs¾c{¾c{½ss¾tt¾19l2:l)J)J:Kl9KlCStBRsŒ”ÏŒ”ÎRRŒSS!B!B:Cd:CdBRsBRs|…¶|…¶|…¶|…¶……Ï……Ï{„µ{„µKS…KS…)J)K9Jk9JkBRsBRs„Œ®„Œ®S[|RZ{!B!B19[19ZRZ{RZ{{„¶{„µ{{Ç||Ç„„Ï„„ÏS[•RZ”)J)J19Z1:[9Jk9Jlt|t|……¾……¾*2[)1Z*2[*2[9Jk9Jk[d•Zc”cs¾cs¾cs¾dt¾d|¾c{½……¾„„½S[•S[•!B!B!B!B1Bc1Bc:Kl9JkÇŒŒÆll¦ll¦"C"C)J)K9Bc9Bc9Bc:Cdc{¾c{½c{½c{½cs½cs½s{¶s|¶[dZcœ!1R!1R*2[)1Z:Kl9Jklt•ks”ÇÇ!C!B)J)J9Bc9BdRZ{RZ|……¾……¾||Ç||Ç„„½„„¾ss­tt®!)c!)c)1[)1Z9Jl9Jklt•ks•ŒŒÆŒŒÆ9Bc9Bd!B!B9Bd9BdS[|R[|……¾……¾tt¾tt¾|…¶{„µRRRR2CS1BS*"C)!B))9))922C22C!1!119Z19[kk¥kk¥ss®ss®Zk®Zk®Zk¶[l¶ZkµZkµZk¶ZkµZk¶Zkµcs¾dt¾dt¾dt¾Zk¶Zl¶cs½dt¾c{½c{½d|¾c{½Zkµ[l¶ll¶kk¶11l11k„„½„„½„„½„„½[t¦Zs¥d|¾c{½d|¾c{¾c{¾c{½c{½d|¾c|¾d|¾d|¾d|¾……Ï……Ït|¶s{¶!!Z!!Zs{¶t|¶|…¶{„¶dt¾dt¾s„Æt…Çkk¦kk¥!)c!)c…®„Œ­|…¶|…¶c{­d|®c{¾d|¾d|¾c{½c{¾c{½d|¾c{½dldl)1c)1c{…¶{„µ……¾„„½……¾……¾s{µs{¶*2d*2d{„¶|…¶……¾„„¾sŒ½sŒ½t…Çt…Çd|¾c{¾d|¾c{½c{­c{®)1c)1c|…¶|…¶……¾……¾……¾……¾s{µs|¶)1d)1cZcœ[d„„½„„½t¾sŒ½d|¾c{¾c{½d|¾c{¾c{¾99s::tJR…JR…ŒŒÇÇ|…¶|…¶ŒŒÇÇRRRRŒJR„JR„ŒŒÇÇc{­c{­d|¾d|¾c{½d|¾d|¾d|¾c{½d|¾„„¾……¾BJ„CK…)1c)2dŒŒÆŒŒÇ[l®[l®c{½c{¾||Ç{{Æ9B{9B{99s::t•Ï•Ït|¶s{¶d|¾c{¾c{¾d|¾c{½c{½c{¾c{¾sŒ¾t¾CK…BJ…99s99tÇŒŒÆ|…¶|…¶ÇÇBJ…BJ„99t99sÇŒŒÇ|…¶|…¶t…Çs„Æ{{Ç{{Çd|¾c{½s„Çt…ÇCK…BJ…99s99tÇŒŒÆ|…¶|…¶ÇŒŒÆZcœZcœ!)c!)cÇÇ{„¶|…¶t…Çt…Çd|¾c{½c{¾c|¾Zk¶ZkµZk¶Zk¶BJ„BK…::t99tŒ•ÏŒ”ÏZs¦Zs¥cs½dt¾c{½c{½kk¥ll¦Zk®[l®[l¶Zl¶ZkµZl¶Zl¶[l¶[l¶Zkµdt¾cs¾cs¾cs¾ZkµZk¶dt¾cs½c{¾d|¾d|¾c{½Zk¶Zkµkk¶kkµ11k11k„„½„„½……¾„„½[t¦[t¦d|¾c{½c|¾c{½d|¾d|¾c|¾c{¾d|¾c{¾c|¾c{¾……Ï……Ït|¶s|¶""[!![t|¶t|¶{„¶{„¶dt¾cs¾s„Æs„Æll¦kk¦!)d!)c…®…®{…¶|…¶d|®c{­c{¾d|¾d|¾c{½c{½c{¾d|¾d|¾ckdl)1c)1c{„µ|…¶„„½……¾„„½……¾s{¶s{¶)1c)1d{„µ|…¶……¾……¾t¾t¾t…Çt…Çc|¾d|¾d|¾c{½c{®c{®)1c)1c|…¶|…¶……¾„„¾„„½……¾s{¶t|¶)1c)1cZcZcœ„„½……¾sŒ½sŒ¾c{½c|¾d|¾c{¾c|¾d|¾99s::tJR…JR„ŒŒÆŒŒÇ{„µ|…¶ŒŒÇÇRRŒSSJR…JR„ÇÇc{­d|®d|¾c{½c{¾d|¾d|¾c{½c{½d|¾……¾……¾BJ„BJ…*2d)1cÇÇZk®[l®c{½c{½{{Æ||Ç9B{9B{::t99s•Ï•Ït|¶t|¶c{½c{¾d|¾c{½d|¾d|¾c|¾d|¾s¾sŒ¾BJ„BJ„99t99sŒŒÆÇ|…¶{„µÇÇBJ„BJ„99s99sŒŒÆŒŒÇ|…¶{„µt…Çt…Ç||Ç||Çc{¾c{¾t…Çt…ÇBJ„BJ„::t99sŒŒÇŒŒÆ|…¶{„µŒŒÆÇZdZd"*d!)cÇÇ|…¶|…¶s„Æt…Çd|¾d|¾c{½c{¾[l¶Zkµ[l¶ZkµBJ„CK…99t99s•ÏŒ”Ï[t¦Zt¦cs¾cs½d|¾d|¾kk¦kk¥Zk®Zk­[l¶Zkµ[l¶[l¶[l®[l®Zk¶[l¶ct¾cs½cs½cs¾ZkµZl¶dt¾cs¾dt¾dt¾[l¶Zkµd|¾c{½{„µ{„µ*K)JŒŒÆŒŒÇ””Î””Ïd|®c{®c{¾c{½d|¾c{¾cs¾cs½c{½c{¾d|¾c|¾cs¾cs¾c{½d|¾|…¶|…¶)!B)!B|…¶{„µ•ÏŒ”Î[l¶Zl¶d|¾c{½tt®ss­)J*K„Œ¶…¶ŒŒÆŒŒÇd|®c{®cs¾ct¾dt¾dt¾c{¾c{½d|¾d|¾ZcZcœ)J)J„„½„„½ÇŒŒÇ„„¾„„¾{„µ|…¶!1R!2S……¾„„¾„„½„„¾s|¶s{µc{½c{¾d|¾c{½s{¶s{¶s{µs{µ)J)J„„¾„„½ÇŒŒÇss½ss½|…¶|…¶)J)JZkZkŒŒŒÇÇd|®d|®d|¾d|¾c{½c{½……¾„„½2Cd2CdCStBSt••Ï••Ïtt¾tt¾ŒŒÆŒŒÇSSSSBRsCSt”œ×”œ×t|¶t|¶cs¾cs½d|¾c{½d|¾c{½dt¾cs½„„Î……ÏCK…CK…)J)K••Ï””Ïc{®d|®Zkµ[l¶t¾t¾BRsBRs19[2:[¦Ïœ¥Ï{„µ{„¶cs¾cs¾cs½cs½dt¾cs½c{½d|¾„„¾……¾BJ„BJ„19Z19[•×•×tt¾ss¾……¾……¾BJ…BJ„19Z19Z””Ï••Ï|…¶{„µd|¾c{¾{{Ç{{Çcs½dt¾{{Æ{{ÆBJ…BJ…2:[19Z••Ï••Ïss­tt®……¾„„½ll¦kk¥)J)K••Ï••Ï……¾……¾s|¶t|¶ss¾ss¾[l¶Zk¶Zk¶Zk¶||Ç||Ç:C|:C|*2d)1c¥µÖ¦¶×c|®c{®c{½c{½d|¾c{¾ss­tt®[l®Zk®Zk­[l®cs½dt¾[l®[l®Zk¶[l¶cs½cs¾dt¾dt¾Zl¶[l¶dt¾dt¾cs¾cs¾Zk¶[l¶d|¾c|¾{„¶|…¶*K)KÇÇ••Ï••Ïc{­d|®c{½c{½c|¾c|¾ct¾cs½c{½d|¾c{¾c{½cs½cs¾d|¾d|¾{„¶|…¶)!B)!B|…¶|…¶Œ”ÏŒ”ÏZkµZk¶c{½c|¾tt®ss­)J*K…¶…¶ÇŒŒÆc{®c{­cs½cs½dt¾cs½c{¾c{½d|¾d|¾[d[d*K)J„„½„„¾ŒŒÆÇ……¾……¾|…¶|…¶!1R!1R„„¾„„½……¾„„½t|¶t|¶c{¾c{½c{½d|¾t|¶t|¶t|¶s{µ)J)J„„½……¾ÇŒŒÆtt¾tt¾|…¶{…¶)J)JZk[lÇŒŒÇc{­c{­c{½d|¾d|¾d|¾„„½……¾2Cd2CdCStCSt””Ï••Ïss¾ss½ŒŒÇŒŒÇRRŒSSBRtBRt•×”œ×s{µt|¶cs½cs½d|¾c{¾c{¾c{¾dt¾dt¾……Ï„„ÏBJ…BJ„)J)J••Ï••Ïd|®c|®[l¶[l¶sŒ¾t¾BRsCSt19Z2:[¦Ï¦Ï|…¶{„µcs½cs¾dt¾cs½cs½cs½d|¾c{½……¾„„¾BJ…CK…2:[19Z”×•×tt¾tt¾„„½„„½CK…CK…19Z2:[••Ï••Ï|…¶{„µd|¾c{¾{{Æ||Çcs½cs½||Ç||ÇBK…BJ…2:[19Z””Ï••Ïss­ss­……¾……¾ll¦ll¦)J*K””Î””Î„„½……¾s{µs{µtt¾ss½Zk¶[l¶Zkµ[l¶||Ç||Ç9B{:C|)1d)1c¥µÖ¥µ×c{®d|®d|¾c|¾d|¾c{¾ss­tt®Zk­[l®[l®Zk­dt¾dt¾ZZ¦ZZ¥ZZ¥ZZ¦kc­ld®kc­kc­Jc¥Jc¥Sd®Rc­Zk­Zk­Jd¦Jc¦Zl®[l®ll¦kk¥99t99t|…¶|…¶……¾„„½Jc¦Jc¦Rd®Rc­Sd®Rc®Jd¦Kd¦Jc¥Jc¥Kd¦Jc¥J[¦K[¦Sd®Rc­ll¦ll¦22l11kdlcltt®ss®BZB[[dZcdlck19l2:lll¦ll¦ll¦ll¦RRŒRRŒSSRRœRRSSSSSSZc”Zc•RZ”RZ”11k11kckœckll¦ll¦Zc[ddlck99s99sll¦kk¥dlckœZc”Zc”dldlZc”[d•Zc”Zc”ckœdl11l11kdlckkk¥kk¥Zc”Zc”kk¥kk¥9B|9B{Zc”Zc”ckck[d•Zc•Zcœ[d[d[dckckœ9B{9B|9B{9B{ll¦kk¦RZ”RZ”kk¥ll¦S[•RZ”RRŒRRŒss®ss­[dZcœJd¦Jd¦Kd¦Jc¦Jc¥Jc¦K[¦JZ¥ll¶ll¶KS…JR„19k19ktt®ss­[dZcœJc•Kd•ckckœBJ„BJ…9B{9B{s{¶t|¶Zcœ[dC[BZŒSSRRœRRSSRRRRŒ[dZcBJ„BJ„19k19lss­tt®Zc”[d•dlckJR„JR„BJ…CK…ss­ss­[dZcZcœZcœdlclZc”Zc”ckdlCK…BJ„19k19lll¦ll¦Zc”Zc”ckœdlZd•Zc”99s99stt®ss®Zcœ[dZc”Zc”ckœckœRc­Rc®Jc¦Jc¥ss¾tt¾BJ„BJ…CK…BJ„•ÏŒ”ÏZcZcSd®Rc®kk¦ll¦kk¦ll¦ZZ¥ZZ¦Rc®Sd®ld®kc®ZZ¥ZZ¦ZZ¦[[¦kc­kc­ld®kc­Jc¦Kd¦Rc­Sd®[l®[l®Jc¥Kd¦Zk®[l®kk¥ll¦::t::t|…¶|…¶……¾……¾Jc¦Jc¥Rc®Sd®Rc®Rc­Jc¦Jc¥Jd¦Kd¦Jc¦Jc¦JZ¦JZ¦Rc®Sd®ll¦kk¥11l11kckœckœtt®ss­BZŒBZZcœ[dckœckœ19k19kkk¦ll¦ll¦kk¥SSRRRRœRRœRRœRRœSSRRZc”Zc”RZ•RZ”11k11lckdlkk¥ll¦ZcœZcckœdl99s99skk¦kk¥ckœckœ[d•Zc”ckœckœ[d•Zc”Zc•[d•ckœckœ11k11kckclkk¥kk¦Zc•Zc•kk¥kk¥9B{:C|Zc”Zc”ckckœZc•Zc•[d[dZcœZcœdldl9B{9B|9B{:C|ll¦ll¦RZ•RZ•ll¦ll¦RZ•S[•RRŒRRŒtt®ss­Zc[dJc¦Jc¥Kd¦Kd¦Jc¥Kd¦JZ¥JZ¦kkµkkµJR„JR„19k19lss­ss®ZcœZcJc”Jc”dldlCK…BK…:C|9B|t|¶t|¶ZdZcBZC[RRœRRSSRRœSSSSZcœZcœCK…BJ„19k2:lss®tt®[d•[d•ckœdlJR„JR„BJ„BJ„tt®tt®ZcœZcœZcœZcdlckœZc”Zc•ckœdlBJ…CK…19k19kll¦ll¦Zc”Zc”dldlZc”[d•99s99sss­tt®[dZcZc•[d•dldlSd®Rc®Jc¥Jc¥tt¾tt¾CK…BJ„BJ…CK…•ÏŒ”Î[dZcœRc®Rc®kk¦kk¦kk¥ll¦ZZ¥[[¦Rc­Rc­lc®ld®19l19k1Bc1Bd99s99s9B{9B{::t99t99s99s99t99s19k2:l9B{9B{19k19k99t99t9B{9B{99s99t19k19k19k19k99t::t11k11k19k2:l::t99s1Bc1Bc11k11l11l11k11l11l22l11k2:l19k11k22l11k11k11k11k11k11l19k2:l19k19l22l22l11k11k11k11k11l11k11k11k2:l19k)1c)1c*2[)1[2:[19Z2:l2:l19k19k11l22l19k2:l)1c)1c)1c)1d2:l19l22l11l19l19k::t99s)1c)1c)1Z)1Z11k11k11k22l99s99t22l11k11l22l)1d)1c)1[)1[11k11k2:l19l19k19k11l11k!1R!1R11k11k*2d)1c19l2:l11k11k11k11k19Z19Z)1c)1c22l11k19k19k99s99s19k19l11k22l11k11l11k11k19k19l19k19l11k11k11k11k22l11k11k11k19k2:l19l19k11k11l11k11k22l11k11k22l19l19k11k11l"2S!1R19[2:[11k22l2:l19l19k1:l11k11k)1c)1c)1c)1c11k22l19l19k11l11l19k19k19k2:l!2S"2S)1Z)1[11k11k11k22l19k19l11k11k11k11l)1c)1d*2d)1d19l19l19l1:l19k2:l::t99t2:l19k1:l19k9B{9B{11k11k2:l19k99s99sRJsRJs9Bc9Bc::t99s19l19k19k19k2Cd2Cd99s99s:C|:C|99t99s99s::t99t99t2:l2:l9B|9B|19k19k99s::t9B{9B{99s99t19l2:l19k19k99s99s11k11k19k19l::t99s1Bd2Cd11k11k11k11l22l11k11k11k2:l19k11k22l22l11k11k11k11l11k19k19k19k19k11k11k11l11l11k11l11k22l11k11l19k19k)1c)1c)1Z)1Z19Z2:[19k19k19k19l11l11k19l2:l)1c)1c)1d)1c19k19k11k22l19l2:l99t99s)1c)1c*2[)1[22l11l11k11k99s99s11k11k11k11k)1c)1c)1Z)1Z11k11k2:l19k19k2:l11k22l!1R"2S11k11l)1c)1c19k19l11l11k11k22l19Z19Z)1c)1c11l11k19k19k99t99t19k19k22l11k11l11l11l11k2:l2:l19l19l11l11k22l11k11l11k11k11l19k19k19k2:l11k11k22l11k22l22l11l11l19k19k11k11k!1R!1S19Z19Z11k11l19k19k1:l19k11k11k)1c)1d)1c)1c22l11k19k2:l11k11l19k19k19k19l"2S"2S)1[)1Z11k11k11k11k19k19k11k11k11k11k)1c)1d)1c)1c19k19k19k19k19l2:l99t99t2:l1:l19k19l:C|9B{11k11k2:l19k99s99sRJsRJt9Bd9Bc99t99s19k19k1Bc1BcCK…CK…99s99tJR„JR…CK…BJ…CK…BJ„CK…BJ„JR„JR…SSRRBJ„BJ…RRŒRRKS…JR„RRSSKS…JR…RRŒRRRRŒRRŒJR…JR„RRŒRRŒRZ•RZ”RRŒRRKS…JR…SSRRŒRZ”S[•S[•RZ”RZ•RZ”Zc”Zc”RZ”RZ”RZ”S[•RZ•RZ”RZ”RZ”ZdZcœZcœ[d[dZc[d•Zc•S[•RZ”RZ”RZ•Zd•Zc•SSSSS[•RZ•S[•RZ”S[•S[•Zc”Zc•Zc”[d•Zc”Zc”R[•S[•[d•Zc”ZcœZcZc•[d•RZ”RZ”[d•Zc”SSRRŒRZ•S[•S[•RZ”RZ•RZ”Zc”[d•Zc”Zc”Zc”Zc”S[•RZ•[d•[d•ZdZcZc”[d•Zc”Zd•R[•RZ”RRRRŒS[•RZ”RZ”RZ”[d•[d•Zc”[d•Zc”Zc•RZ”RZ”RRŒRRŒJR„JR„RRSSRZ”S[•JR„JR„RRŒRRŒJc”Kd•RZ•S[•RZ•S[•RRRRœS[•RZ”S[•S[•S[•S[•S[•RZ”Zc•[d•[d[d[d[d[dZcœ[d•Zc”R[•S[•[d•Zc”RZ•RZ”SSRRŒRZ”RZ”S[•RZ•[d•[d•Zc”Zc”Zc•Zc”S[•R[•RZ”S[•[d•Zc”[d[dZc•Zc•RZ•RZ•Zc•Zc”RRŒRRRZ•RZ”RZ•S[•Zc”[d•[d•Zc”Zc•[d•Zc”[d•RZ”RZ”Zc•Zc•ZcZcœS[•RZ”BJ„BJ„RRŒSSCK…BJ„JR…JR…RRŒRRŒBJ„BJ…RRŒSSCK…BJ„BRsBRs)1[)1[CStBRs19k2:l1Bc1BcBJ„BJ„99s99sKS…JR…BJ„CK…BJ„BJ„BJ„BJ„JR…JR„RRŒRRŒCK…BJ…SSRRJS…JR„RRŒRRŒKS…JR…RRRRŒRRŒRRŒJR„JR…RRSSS[•RZ”SSRRŒJR…KS…SSRRRZ”RZ”RZ”RZ”RZ”RZ•[d•Zc”RZ”RZ”RZ”RZ•R[•RZ”RZ”RZ•ZcœZc[d[d[d[dZc”Zc”RZ•S[•RZ”RZ•Zc”[d•SSRRŒRZ•RZ”S[•RZ”RZ”RZ”Zc”[d•[d•Zc”[d•Zc•RZ•RZ•Zc•Zc”ZcœZd[d•Zc•RZ”RZ•Zc”[d•RRŒRRRZ”RZ”RZ”RZ”S[•S[•Zc•Zc”Zd•Zc”Zc•[d•S[•RZ•[d•Zc”[dZcœZc”[d•Zc•Zc”RZ”S[•RRŒRRŒRZ•RZ”RZ•S[•Zc•Zc”Zc•[d•Zc”Zc”S[•RZ”RRŒSSKS…KS…SSSSRZ”RZ•JR„JR„RRŒRRŒJc”Jc”RZ”S[•RZ”S[•SSSSS[•RZ”RZ”RZ”S[•R[•RZ”S[•Zc”Zc”ZcœZd[dZcœZcœ[dZc”Zc”S[•RZ•[d•Zc•RZ”RZ”RRŒRRŒRZ•RZ•S[•RZ”[d•Zc”[d•[d•Zc”Zc”RZ”RZ”RZ”R[•Zc”Zc”[dZcZc”Zc”S[•S[•[d•Zc”SSRRRZ”S[•RZ•R[•Zc”Zd•Zc”Zc”[d•[d•Zc”Zc”RZ•S[•Zc•Zc”ZcœZcœRZ•RZ•BJ„BJ…RRŒSSBJ„CK…JR„JR„RRRRBJ…BJ„RRRRBJ…CK…BRsBRs