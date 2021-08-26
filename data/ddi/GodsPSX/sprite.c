//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Sprite File For <GODS PSX>
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

// Include all Header Files

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
#include	"libgods.h"
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

SpriteGlobsType	spriteGlobs;

extern GsRVIEW2	view;

void VectorScale(VECTOR v1, int scale, VECTOR *result);
void VectorAdd(VECTOR v1, VECTOR v2, VECTOR *result);
void GetRectangleFromWorldPoint(VECTOR point, int width, int height, VECTOR camdir, VECTOR camup, VECTOR* topleft, VECTOR* topright, VECTOR* botleft, VECTOR* botright);



// **********************************************************************************************
void Sprite_Initialise(void)
{
int l;

	for (l = 0 ; l < MAX_SPRITE_QUADS ; l++)
	{
		SetPolyFT4(&spriteGlobs.quadPool.quad[l][0]);
		SetPolyFT4(&spriteGlobs.quadPool.quad[l][1]);
	}


	spriteGlobs.quadPool.quadCount		= 0;

	spriteGlobs.spriteList.spriteCount	= 0;

	Sprite_DefaultParameters();

}

// **********************************************************************************************
void Sprite_ShutDown(void)
{
}

// **********************************************************************************************
short	Sprite_LoadSprite(LPUCHAR name, int width, int height)
{
LPUCHAR		buffer;
int			size;
TIM_IMAGE	tim;
int			spriteIndex;
lpSprite	sprite;
Uint16		tp;
int			mult;

	spriteIndex = spriteGlobs.spriteList.spriteCount;

	if (spriteIndex == MAX_SPRITES)	return -1;

	sprite = &spriteGlobs.spriteList.sprites[spriteIndex];

	buffer = File_LoadBinary(name, NULL);

	if (buffer == NULL)				return -1;
	

	OpenTIM((Uint32*)buffer);
	ReadTIM(&tim);

	switch(tim.mode & 7)
	{
	case	0:		mult = 4;			break;
	case	1:		mult = 2;			break;
	default:		mult = 1;			break;
	}

	LoadImage(tim.crect, tim.caddr);			// download tim 
	LoadImage(tim.prect, tim.paddr);			// download clut

	switch(mult)
	{
	case	1:		tp = 0x100;			break;
	case	2:		tp = 0x080;			break;
	case	4:		tp = 0; 			break;
	}

	sprite->clut			= getClut(tim.crect->x, tim.crect->y);
	sprite->tpage			= (tim.prect->x/64)+((tim.prect->y>>8)<<4)+tp;
	sprite->uvwidth			= width*mult;
	sprite->width			= width;
	sprite->height			= height;
	sprite->u				= (tim.prect->x & 0x3f)*mult;
	sprite->v				= (tim.prect->y & 0xff);
	sprite->clutx			= tim.crect->x;
	sprite->cluty			= tim.crect->y;

	sprite->images_across	= (tim.prect->w*mult) / width;
	sprite->images_down		= tim.prect->h / height;	

	//printf("%d : %d:%d\n", spriteIndex, sprite->images_across, sprite->images_down);

	sprite->scalex			= ONE;
	sprite->scaley			= ONE;
	sprite->red				= 128;
	sprite->green			= 128; 
	sprite->blue			= 128;  
	sprite->rx				= 0;
	sprite->ry				= 0;
	sprite->rz				= 0;

	spriteGlobs.spriteList.spriteCount++;

return spriteIndex;

}

// **********************************************************************************************
void Sprite_EndMainLoop(void)
{
	spriteGlobs.quadPool.quadCount = 0;		// start using quads from the start of the list again
}

// **********************************************************************************************
void Sprite_DefaultParameters(void)
{
	spriteGlobs.scalex		= -1;
	spriteGlobs.scaley		= -1;
	spriteGlobs.red			= -1;
	spriteGlobs.green		= -1; 
	spriteGlobs.blue		= -1;  
	spriteGlobs.rx			= -1;
	spriteGlobs.ry			= -1;
	spriteGlobs.rz			= -1;
}

// **********************************************************************************************
void Sprite_SetScale(int scalex, int scaley)
{
	spriteGlobs.scalex		= scalex;
	spriteGlobs.scaley		= scaley;
}

// **********************************************************************************************
void Sprite_SetRGB(short r, short g, short b)
{
	spriteGlobs.red			= r;
	spriteGlobs.green		= g; 
	spriteGlobs.blue		= b;  
}

// **********************************************************************************************
void Sprite_SetRotation(int rx, int ry, int rz)
{
	spriteGlobs.rx			= rx;
	spriteGlobs.ry			= ry; 
	spriteGlobs.rz			= rz;  
}

// **********************************************************************************************
void Sprite_SetDefaultValues(int spr, int scalex, int scaley, short r, short g, short b, int rx, int ry, int rz)
{
lpSprite sprite;

	if (spr < 0)	return;

	sprite	= &spriteGlobs.spriteList.sprites[spr];

	sprite->scalex			= scalex;
	sprite->scaley			= scaley;
	sprite->red				= r;
	sprite->green			= g; 
	sprite->blue			= b;  
	sprite->rx				= rx;
	sprite->ry				= ry;
	sprite->rz				= rz;


}

// **********************************************************************************************
// this will draw a poly lying flat on the floor and can rotate it about y.
void Sprite_DrawFlatFloorSprite(int spr, int frame, int x, int y, int z)
{
POLY_FT4				*poly;
lpSprite				sprite;

Uint32				 	*ot=(Uint32*)gfxGlobs.Wot[gfxGlobs.bufID].org;

GsCOORDINATE2			coord;
MATRIX					mat;
short					coords[3];
long					depth=14,flag;
SVECTOR					vector;
int						sz;
VECTOR3D				pos,rot;
int						dx,dy;	
REAL					stheta,ctheta;
int						sizex, sizey, xframe_offset, yframe_offset;
int						across_size, down_size;



	if (spriteGlobs.quadPool.quadCount == MAX_QUADS)	
	{
		printf("OUT OF QUADS (%d IS NOT ENOUGH)\n", MAX_QUADS);
		return;
	}

	poly	= &spriteGlobs.quadPool.quad[ spriteGlobs.quadPool.quadCount ][GsGetActiveBuff()];
	spriteGlobs.quadPool.quadCount++;


	sprite	= &spriteGlobs.spriteList.sprites[spr];

	GsInitCoordinate2(WORLD, &coord);
	GsGetLs(&coord, &mat);
	GsSetLsMatrix(&mat);

	if (spriteGlobs.rx == -1)		spriteGlobs.rx		= sprite->rx;
	if (spriteGlobs.ry == -1)		spriteGlobs.ry		= sprite->ry;
	if (spriteGlobs.rz == -1)		spriteGlobs.rz		= sprite->rz;
	if (spriteGlobs.red == -1)		spriteGlobs.red		= sprite->red;
	if (spriteGlobs.green == -1)	spriteGlobs.green	= sprite->green;
	if (spriteGlobs.blue == -1)		spriteGlobs.blue	= sprite->blue;
	if (spriteGlobs.scalex == -1)	spriteGlobs.scalex	= sprite->scalex;
	if (spriteGlobs.scaley == -1)	spriteGlobs.scaley	= sprite->scaley;

	pos.x = x;				
	pos.y = y;			
	pos.z = z;

	rot.x = spriteGlobs.rx;				
	rot.y = spriteGlobs.ry;			
	rot.z = spriteGlobs.rz;			

	sizex		=	FromFIXED(Asm_MulFIX(sprite->width<<12,  spriteGlobs.scalex));
	sizey		=	FromFIXED(Asm_MulFIX(sprite->height<<12, spriteGlobs.scaley));

	stheta		=	csin(4095-rot.y);
	ctheta		=	ccos(4095-rot.y);

	dx			=	FromFIXED((sizex*ctheta)-(sizey*stheta));
	dy			=	FromFIXED((sizex*stheta)+(sizey*ctheta));

	vector.vx	=	-pos.x+dx;
	vector.vy	=	pos.z;
	vector.vz	=	pos.y+dy;
	sz			=	RotTransPers(&vector,(long*)&coords[0],&depth,&flag);

	// clip coords[0] and coords[1] here


	poly->x1	=	coords[0];
	poly->y1	=	coords[1];

	vector.vx	=	-pos.x-dx;
	vector.vy	=	pos.z;
	vector.vz	=	pos.y-dy;
	sz			=	RotTransPers(&vector,(long*)&coords[0],&depth,&flag);
	poly->x2	=	coords[0];
	poly->y2	=	coords[1];

	dx			=	FromFIXED((sizex*ctheta)-(-sizey*stheta));
	dy			=	FromFIXED((sizex*stheta)+(-sizey*ctheta));
	vector.vx	=	-pos.x+dx;
	vector.vy	=	pos.z;
	vector.vz	=	pos.y+dy;
	sz			=	RotTransPers(&vector,(long*)&coords[0],&depth,&flag);
	poly->x3	=	coords[0];
	poly->y3	=	coords[1];

	vector.vx	=	-pos.x-dx;
	vector.vy	=	pos.z;
	vector.vz	=	pos.y-dy;
	sz			=	RotTransPers(&vector,(long*)&coords[0],&depth,&flag);
	poly->x0	=	coords[0];
	poly->y0	=	coords[1];


	poly->tpage	=	sprite->tpage;
	poly->clut	=	sprite->clut;


	across_size = frame % sprite->images_across;
	down_size	= frame / sprite->images_down;


	xframe_offset = across_size*sprite->width;
	yframe_offset = down_size*sprite->height;

	setUVWH(poly,	sprite->u+xframe_offset, sprite->v+yframe_offset, sprite->width-1, sprite->height-1);

	poly->r0	= spriteGlobs.red;
	poly->g0	= spriteGlobs.green;
	poly->b0	= spriteGlobs.blue;


	setSemiTrans(poly, 0);
	AddPrim(ot+sz, poly);

	Sprite_DefaultParameters();

}

// **********************************************************************************************
// this will draw a poly that is always facing the camera (eventually)
void Sprite_DrawOverlaySprite(int spr, int frame, int x, int y)
{
POLY_FT4	*poly;
lpSprite	sprite;

Uint32		*ot=(Uint32*)gfxGlobs.Wot[gfxGlobs.bufID].org;

int			xframe_offset, yframe_offset;
int			across_size, down_size;
int			half_width, half_height;


	if (spriteGlobs.quadPool.quadCount == MAX_QUADS)	
	{
		printf("OUT OF QUADS (%d IS NOT ENOUGH)\n", MAX_QUADS);
		return;
	}

	poly	= &spriteGlobs.quadPool.quad[ spriteGlobs.quadPool.quadCount ][GsGetActiveBuff()];
	spriteGlobs.quadPool.quadCount++;

	sprite	= &spriteGlobs.spriteList.sprites[spr];

	if (spriteGlobs.rx		== -1)	spriteGlobs.rx		= sprite->rx;
	if (spriteGlobs.ry		== -1)	spriteGlobs.ry		= sprite->ry;
	if (spriteGlobs.rz		== -1)	spriteGlobs.rz		= sprite->rz;
	if (spriteGlobs.red		== -1)	spriteGlobs.red		= sprite->red;
	if (spriteGlobs.green	== -1)	spriteGlobs.green	= sprite->green;
	if (spriteGlobs.blue	== -1)	spriteGlobs.blue	= sprite->blue;
	if (spriteGlobs.scalex	== -1)	spriteGlobs.scalex	= sprite->scalex;
	if (spriteGlobs.scaley	== -1)	spriteGlobs.scaley	= sprite->scaley;

	half_width  = sprite->width/2;
	half_height = sprite->height/2;

	poly->x0	=	x-half_width;	poly->y0	=	y-half_height;
	poly->x1	=	x+half_width;	poly->y1	=	y-half_height;
	poly->x2	=	x-half_width;	poly->y2	=	y+half_height;
	poly->x3	=	x+half_width;	poly->y3	=	y+half_height;

	poly->tpage	=	sprite->tpage;
	poly->clut	=	sprite->clut;

	across_size = frame % sprite->images_across;
	down_size	= frame / sprite->images_down;

	xframe_offset = across_size*sprite->width;
	yframe_offset = down_size*sprite->height;

	setUVWH(poly,	sprite->u+xframe_offset, sprite->v+yframe_offset, sprite->width-1, sprite->height-1);

	poly->r0	= spriteGlobs.red;
	poly->g0	= spriteGlobs.green;
	poly->b0	= spriteGlobs.blue;

	setSemiTrans(poly, 0);
	AddPrim(ot+1, poly);

	Sprite_DefaultParameters();
}

// **********************************************************************************************
// this will draw a poly that is always facing the camera (eventually)
void Sprite_DrawCameraFacingSprite(int spr, int frame, int x, int y, int z)
{
POLY_FT4				*poly;
lpSprite				sprite;

Uint32				 	*ot=(Uint32*)gfxGlobs.Wot[gfxGlobs.bufID].org;

GsCOORDINATE2			coord;
MATRIX					mat;
short					coords[3];
long					depth=14,flag;
SVECTOR					vector;
int						sz;
VECTOR3D				pos,rot;
int						dx,dy;	
REAL					stheta,ctheta;
int						sizex, sizey, xframe_offset, yframe_offset;
int						across_size, down_size;

int						length, w_div_2, h_div_2;
SVECTOR					vector1, vector2, vector3;
int						sz_times_four;


	if (spriteGlobs.quadPool.quadCount == MAX_QUADS)	
	{
		printf("OUT OF QUADS (%d IS NOT ENOUGH)\n", MAX_QUADS);
		return;
	}

	poly	= &spriteGlobs.quadPool.quad[ spriteGlobs.quadPool.quadCount ][GsGetActiveBuff()];
	spriteGlobs.quadPool.quadCount++;

	sprite	= &spriteGlobs.spriteList.sprites[spr];

	if (spriteGlobs.rx == -1)		spriteGlobs.rx		= sprite->rx;
	if (spriteGlobs.ry == -1)		spriteGlobs.ry		= sprite->ry;
	if (spriteGlobs.rz == -1)		spriteGlobs.rz		= sprite->rz;
	if (spriteGlobs.red == -1)		spriteGlobs.red		= sprite->red;
	if (spriteGlobs.green == -1)	spriteGlobs.green	= sprite->green;
	if (spriteGlobs.blue == -1)		spriteGlobs.blue	= sprite->blue;
	if (spriteGlobs.scalex == -1)	spriteGlobs.scalex	= sprite->scalex;
	if (spriteGlobs.scaley == -1)	spriteGlobs.scaley	= sprite->scaley;

	sizex		=	(Asm_MulFIX(sprite->width<<12,  spriteGlobs.scalex));
	sizey		=	(Asm_MulFIX(sprite->height<<12, spriteGlobs.scaley));

	vector1.vx = x;
	vector1.vy = y;
	vector1.vz = z;

	sz = RotTransPers(&vector1,(long*)&coords[0],&depth,&flag);


	sz_times_four = sz*4;

	if (sz <= 0) return;


	w_div_2 = (sizex / 2) / sz_times_four;
	h_div_2 = (sizey / 2) / sz_times_four;


	poly->x0 = coords[0] - w_div_2;
	poly->y0 = coords[1] - h_div_2;

	poly->x1 = coords[0] + w_div_2;
	poly->y1 = coords[1] - w_div_2;

	poly->x2 = coords[0] - w_div_2;
	poly->y2 = coords[1] + h_div_2;

	poly->x3 = coords[0] + w_div_2;
	poly->y3 = coords[1] + w_div_2;

	poly->tpage	=	sprite->tpage;
	poly->clut	=	sprite->clut;


	across_size = frame % sprite->images_across;
	down_size	= frame / sprite->images_down;


	xframe_offset = across_size*sprite->width;
	yframe_offset = down_size*sprite->height;

	setUVWH(poly,	sprite->u+xframe_offset, sprite->v+yframe_offset, sprite->width-1, sprite->height-1);

	poly->r0	= spriteGlobs.red;
	poly->g0	= spriteGlobs.green;
	poly->b0	= spriteGlobs.blue;


	setSemiTrans(poly, 0);
	AddPrim(ot+(sz_times_four/8), poly);

	Sprite_DefaultParameters();


}


// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************



