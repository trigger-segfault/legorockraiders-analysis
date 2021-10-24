//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Image.c - [Image Code]
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ


#define IMAGE_MAXLISTS			32			// 2^32 - 1 possible images...

#define IMAGE_FLAG_INITIALISED	0x00000001
#define IMAGE_FLAG_TRANS		0x00000002



#define	MAX_QUADS	(20)

typedef struct quadpool_st
{
	POLY_FT4		quads[MAX_QUADS][2];
	int			nextQuad;
} QUAD_POOL;

typedef struct Image
{
	Uint16	width, height, tPage;
	Uint16	cx, cy;
	Uint8		u, v;
	ULONG		flags;
	Uint32	attribute;
	struct	Image *nextFree;

} Image, *lpImage;

typedef struct Image_Globs
{
	lpImage 			listSet[IMAGE_MAXLISTS];		// Images list
	lpImage 			freeList;

	ULONG 			listCount;						// number of lists.
	ULONG 			flags;
	QUAD_POOL		quadPool;

} Image_Globs, *lpImage_Globs;


/*
	new sprite structures

	these will be used by DECAL and FLOOR_DECAL container types.

*/
typedef	struct sprite_seq
{
	Uint8		u;
	Uint8		v;

/*
 	duplicating sizes here is actually redundant,
	since they are fixed for the sequence, but that may change
	to allow unique sizes per frame.
*/
	char		w;			/* -ve width will indicate flipped sprite */
	char		h;

}	SPR_FRAME, *lpSPR_FRAME;


typedef struct sprite_hst
{
	int			num_directions;
	int			direction_div;
	int			num_frames;
	int			frames_per_direction;
	SPR_FRAME	*frames;
	Uint16		cx,cy;
	Uint16		tpage;
	short			off_x;
	short			off_y;
	Uint8			continuous;					/* if set we adjust for flipped frame orders (left leg becomes right leg problem) */
	Uint8			*frame_sequence;			/* will contain an artist supplied frame order list [start and loop combined] */
	Uint8			start_seq_len;				/* length of the start list, duh */
	Uint8			loop_seq_len;				/* length of the loop list */
	Uint8			anim_delay;
	char			name[16];					/* activity name */

}	SPRITE_SET, *lpSPRITE_SET;



#define	MAX_ANIMSEQS	(8)		//per object type

typedef	struct anim_seq
{
	int				num_anim_seqs;
	lpSPRITE_SET	seq_list[MAX_ANIMSEQS];

}	SPR_ACTIVITY_SET, *lpSPR_ACTIVITY_SET;





//typedef LPVOID lpImage_Texture;

LPVOID			Image_LoadTIM(LPUCHAR name);
lpImage			Image_Next(void);
lpImage			Image_Clone(lpImage img);
lpImage			Image_Create(lpTIM_IMAGE tim, Uint32 m);
void				Image_AddList(void);

BOOL				Image_ActivitySetCreate(lpSPR_ACTIVITY_SET *activitySet);
int				Image_LoadToActivitySet(lpSPR_ACTIVITY_SET activitySet, char *fname,char *activityName, int directions, int per_direction, int width, int height, int x_offset, int y_offset, BOOL reverse_frames, char *start_frame_list, char *loop_frame_list, int delay);
int				Image_AddToActivitySet(lpSPR_ACTIVITY_SET activitySet, lpSPRITE_SET spriteSet);
int				Image_CloneToActivitySet(lpSPR_ACTIVITY_SET activitySet, char *activityName, char *cloneFromName, char *start_frame_list, char *loop_frame_list, int delay);


BOOL				Image_DisplaySprite(SPRITE_SET *set, int direction, int frame, int x, int y, int scale, int order, Uint8 clutIndex, Uint8 brightness, int clipBottom);
BOOL				Image_DisplaySpriteIndex(SPRITE_SET *set, int frame_offset, int x, int y, int scale, int order, Uint8 clutIndex, Uint8 brightness, int clipBottom)



SPRITE_SET*	Image_LoadSpriteSequence(char *fname,int directions, int per_direction, int width, int height, int x_offset, int y_offset, BOOL reverse_frames, char *start_frame_list, char *loop_frame_list, int delay);
int				Image_GetDirection(SPRITE_SET *set, int angle);

#define			Image_GetWidth(p)		((lpImage)p)->width
#define			Image_GetHeight(p)	((lpImage)p)->height


BOOL				Image_InitialiseQuadPool(void);
POLY_FT4*		Image_GetFreeQuad(void);
void				Image_ResetQuadPool(void);
