//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Container File For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

// Include all Header Files

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
#include	"..\inc\libgods.h"
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

Draw_Globs drawGlobs = { NULL };

VOID Draw_Initialise(LPAREA2D window)
{

	drawGlobs.flags |= DRAW_FLAG_INITIALISED;
	Draw_SetClipWindow(window);
}

VOID Draw_SetClipWindow(LPAREA2D window)
{
}

VOID Draw_PixelListEx(LPVECTOR2D pointList, ULONG count, REAL r, REAL g, REAL b, ULONG effect)
{
}


/*
----------------------------------------------------------------------------
	draw list of lines, XOR mode is not supported because PSX doesn't do it
----------------------------------------------------------------------------
*/
VOID Draw_LineListEx(LPVECTOR2D fromList, LPVECTOR2D toList, ULONG count, REAL r, REAL g, REAL b, ULONG effect)
{
	GsLINE	line;
	int		n;
	ULONG		attribute=0;							/* default to draw/solid */
	ULONG		x_offset=Gfx_GetWidth()>>1;
	ULONG		y_offset=Gfx_GetHeight()>>1;

	if (effect==DrawEffect_HalfTrans)
		attribute=(GsALON | GsAONE);		/* semi trans enabled, blend of 100% background + 100% foreground */

	for (n=0; n<count; n++)
	{

		line.attribute=attribute;
		line.x0=(fromList[n].x>>12)-x_offset;
		line.y0=(fromList[n].y>>12)-y_offset;
		line.x1=(toList[n].x>>12)-x_offset;
		line.y1=(toList[n].y>>12)-y_offset;

		r>>=4;
		if (r>0)
			r--;			
		line.r=r;

		g>>=4;
		if (g>0)
			g--;			
		line.g=g;

		b>>=4;
		if (b>0)
			b--;			
		line.b=b;

		GsSortLine(&line,&gfxGlobs.Wot[gfxGlobs.bufID],0);
	}
}


/*
	debug test to show viewport area and position
*/
VOID	Draw_ShowViewPort(lpViewport vp)
{
}

VOID Draw_WorldLineListEx(lpViewport vp, LPVECTOR3D fromList, LPVECTOR3D toList, ULONG count, REAL r, REAL g, REAL b, ULONG effect)
{
	GsLINE	line;
	int		n;
	ULONG		attribute=0;							/* default to draw/solid */
	SVECTOR	vector;
	short		coords[2];
	long		depth,flag;
	GsCOORDINATE2	coord;
	MATRIX	mat;


	GsInitCoordinate2(WORLD, &coord);
	GsGetLs(&coord, &mat);
	GsSetLsMatrix(&mat);

	if (effect==DrawEffect_HalfTrans)
//		attribute=(GsALON | GsAONE);		/* semi trans enabled, blend of 100% background + 100% foreground */
		attribute=((1<<30)|1<<29);		/* semi trans enabled, blend of 100% background + 100% foreground */

	
	r>>=4;
	if (r>0)
		r--;			
	line.r=r;

	g>>=4;
	if (g>0)
		g--;			
	line.g=g;

	b>>=4;
	if (b>0)
		b--;			
	line.b=b;

	for (n=0; n<count; n++)
	{
		vector.vx=fromList[n].x;
		vector.vy=fromList[n].y;
		vector.vz=fromList[n].z;
		RotTransPers(&vector,(long*)&coords[0],&depth,&flag);

		line.attribute=attribute;
		line.x0=coords[0];
		line.y0=coords[1];

		vector.vx=toList[n].x;
		vector.vy=toList[n].y;
		vector.vz=toList[n].z;
		RotTransPers(&vector,(long*)&coords[0],&depth,&flag);

		line.x1=coords[0];
		line.y1=coords[1];



		GsSortLine(&line,&gfxGlobs.Wot[gfxGlobs.bufID],10);
	}

}


VOID Draw_RectListEx(LPAREA2D rectList, ULONG count, REAL r, REAL g, REAL b, ULONG effect)
{
	GsBOXF	box;
	int		n;
	ULONG		attribute=0;							/* default to draw/solid */
	ULONG		x_offset=Gfx_GetWidth()>>1;
	ULONG		y_offset=Gfx_GetHeight()>>1;

	if (effect==DrawEffect_HalfTrans)
		attribute=(GsALON | GsAONE);		/* semi trans enabled, blend of 100% background + 100% foreground */

	for (n=0; n<count; n++)
	{

		box.attribute=attribute;
		box.x=rectList[n].x-x_offset;
		box.y=rectList[n].y-y_offset;
		box.w=rectList[n].width;
		box.h=rectList[n].height;

		r>>=4;
		if (r>0)
			r--;			
		box.r=r;

		g>>=4;
		if (g>0)
			g--;			
		box.g=g;

		b>>=4;
		if (b>0)
			b--;			
		box.b=b;

		GsSortBoxFill(&box,&gfxGlobs.Wot[gfxGlobs.bufID],0);
	}
}

/*
	draw circle of dots/lines
*/
VOID Draw_DotCircle(LPVECTOR2D pos, ULONG radius, ULONG dots, REAL r, REAL g, REAL b, ULONG effect)
{
}

