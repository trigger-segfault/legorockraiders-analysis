//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// boulder Include For <LEGO [Rock Raiders]>
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

#ifndef	__BOULDER_H


/* MOVEME: -------------------------------------------*/

#define		MAX_BOULDERS										(20)
#define		MAX_MODEL_BOULDERS								(10)
#define		BOULDER_RANDOM_ROTATION_DELTA_MAX			(127)													/* must be a power of 2 -1 */
#define		BOULDER_RANDOM_ROTATION_DELTA_MAX_HALF		(BOULDER_RANDOM_ROTATION_DELTA_MAX>>1)

#define		BOULDER_GRAVITY_ACCELERATION					(0x4000)

typedef struct boulder_st
{
	lpContainer		cont;
	int				x;
	int				y;
	int				z;
	int				zSurface;
	int				scale;			/* is also used to mark usage, if scale goes <=0, it is unused */
	int				scaleDelta;
	int				xRot;
	int				yRot;
	int				zRot;
	int				flags;
	int				time;				/* timeout before removal, could be linked to scale */	
	int				direction;
	int				speed;
	int				zSpeed;
	int				startState;

}	BOULDER, *lpBOULDER;

enum
{
	BOULDER_FLAGS_DONT_CLIP						=1,
	BOULDER_FLAGS_GENERATE_SMOKE				=2,
	BOULDER_SPLIT_IN_TWO							=4,
};


typedef struct boulderGlobs_st
{
	lpSPRITE_SET	boulderSpriteSet;				/* very small boulders will use a sprite */
	lpContainer		refBoulderCont;				/* container to hook into object list */
	lpContainer		boulderCont;					/* original model cached here */
	BOULDER			list[MAX_BOULDERS];

}	BOULDERGLOBS, *lpBOULDERGLOBS;



#define		MAX_SMOKE_PARTICLES			(64)
#define		MAX_SMOKE_TYPES				(4)

/*
	the smoke will use the render callback, so only one container will be processed
	in viewport render, the overhead makes no sense.
*/
typedef struct smoke_st
{
	int				type;					/* sequence number */
	int				x;
	int				y;
	int				z;
	int				zSpeed;
	int				scale;
	int				scaleDelta;
	int				alpha;
	int				alphaDelta;
	int				red;
	int				green;
	int				blue;
	int				rotation;
	int				rotationDelta;
	int				flags;
	int				animSpeed;
	int				animTotal;
	int				animFrame;			/* frame index */
	
}	SMOKE, *lpSMOKE;

typedef	struct	smokeGlobs_st
{
	int						smokeTypesUsed;
	lpSPRITE_SET			smokeSpriteSet[MAX_SMOKE_TYPES];
	lpContainer				smokeCont;										/* the only container used by the smoke pool */
	SMOKE						list[MAX_SMOKE_PARTICLES];

} SMOKEGLOBS;


extern	BOULDERGLOBS	boulderGlobs;
extern	SMOKEGLOBS		smokeGlobs;


void	Boulder_RenderBoulderPool(void);
int	Boulder_AddBoulder(int x, int y, int z, int scale, int direction, int speed, int zSpeed, int time, int creationFlags);
int	Boulder_AddRandomBoulder(int x, int y, int z, int scale, int direction, int speed, int zSpeed, int time, int creationFlags);
void	Boulder_SetStartState(lpBOULDER boulder);
BOOL	Boulder_CheckCollision(lpBOULDER boulder, int oldX, int oldY, int newX, int newY, int *angle);
void	Boulder_CreateRockFall(int blockX, int blockY, int yAngle);
BOOL	Boulder_DestroyBoulderPool(void);
BOOL	Boulder_CreateSmokePool(void);
void	Boulder_ServiceSmokePool(void);
int	Boulder_AddSmoke(int x, int y, int z, int scale, int scaleDelta, int zSpeed, int startAlpha, int alphaDelta, int red, int green, int blue);
int	Boulder_AddEffect(int x, int y, int z, int scale, int scaleDelta, int zSpeed, int startAlpha, int alphaDelta, int red, int green, int blue, int sequence, int animSpeed);


#define	__BOULDER_H
#endif

