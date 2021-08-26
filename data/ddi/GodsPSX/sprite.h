
//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// sprite.c - [Sprite Code]
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹


#define		MAX_SPRITE_QUADS		256
#define		MAX_SPRITES				20


// **************************************************************************************
typedef	struct Sprite
{
	int				clut;					// clut ID
	int				tpage;					// texture page ID
	int				u;						// u
	int				v;						// v
	int				uvwidth;				// uvwidth
	int				width;					// width
	int				height;					// height
	int				clutx;					// clut x
	int				cluty;					// clut y

	short			red;  					// default r
	short			green;					// default g
	short			blue; 					// default b

	int				scalex;					// default scalex
	int				scaley;					// default scaley

	int				rx;						// default rotation	x
	int				ry;						// default rotation	y
	int				rz;						// default rotation	z

	short			images_across;			// amount of images across in the sprite
	short			images_down;			// amount of images down in the sprite


} Sprite, *lpSprite;						// need one of these for each individual sprite



// **************************************************************************************
typedef struct quadPoolType
{
	POLY_FT4		quad[MAX_SPRITE_QUADS][2];		// double buffered
	short			quadCount;						// current quad index
} quadPoolType, *lpquadPoolType;					// uses these quads for drawing



// **************************************************************************************
typedef struct spriteListType
{
	Sprite			sprites[MAX_SPRITES];	// list of sprites, these remember the uv's etc
	short			spriteCount;

} spriteListType, *lpspriteListType;



// **************************************************************************************
typedef struct SpriteGlobsType
{
	quadPoolType	quadPool;				// quad pool for drawing
	spriteListType	spriteList;				// list of sprite data

	int				scalex;					// xscale of all sprites that it will draw
	int				scaley;					// yscale
	short			red;					// red value
	short			green;					// green value
	short			blue;					// blue value
	int				x;						// x position
	int				y;						// y position
	int				z;						// z position
	int				rx;						// x rotation
	int				ry;						// y rotation
	int				rz;						// z rotation

} SpriteGlobsType, *lpSpriteGlobsType;


// **************************************************************************************
void			Sprite_Initialise(void);
void			Sprite_ShutDown(void);
short			Sprite_LoadSprite(LPUCHAR name, int width, int height);
void			Sprite_DrawSprite(int spr);
void			Sprite_DefaultParameters(void);
void			Sprite_EndMainLoop(void);

void			Sprite_SetRotation(int rx, int ry, int rz);
void			Sprite_SetRGB(short r, short g, short b);
void			Sprite_SetScale(int scalex, int scaley);
void			Sprite_SetDefaultValues(int spr, int scalex, int scaley, short r, short g, short b, int rx, int ry, int rz);




void			Sprite_DrawFlatFloorSprite(int spr, int frame, int x, int y, int z);
void			Sprite_DrawCameraFacingSprite(int spr, int frame, int x, int y, int z);
void			Sprite_DrawOverlaySprite(int spr, int frame, int x, int y);



// **************************************************************************************
// **************************************************************************************
// **************************************************************************************
// **************************************************************************************
// **************************************************************************************

