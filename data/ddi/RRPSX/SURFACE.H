//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// surface Include File For <LEGO [Rock Raiders]>
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹


#ifndef	__SURFACE_H

#define		USE_GT4

#define		MAX_WQ				(20)						// maximum width/height of surface
#define		MAX_TQ				(MAX_WQ*MAX_WQ+32)
#define		MAX_FQ				(64)
#define		VERTEXSPAN			(MAP3DWIDTH+1)
#define		MAXVERTEXSPAN		(MAX_WQ+1)
#define		WORLDVERTICES		(MAXVERTEXSPAN*MAXVERTEXSPAN)



/* structures */

typedef struct tql_st
{
#ifdef USE_GT4
	POLY_GT4		tQuad[MAX_TQ];
#else
	POLY_FT4		tQuad[MAX_TQ];
#endif
	int			tz[MAX_TQ];
	int			tQuadLength;

}	TQUAD_LIST;

typedef struct fql_st
{
	POLY_F4		fQuad[MAX_FQ];
	int			fz[MAX_FQ];
	int			fQuadLength;

}	FQUAD_LIST;


typedef struct apl_st
{
	TQUAD_LIST	tList[2];		/* double buffered lists */
	FQUAD_LIST	fList[2];

}	QUAD_LIST ,*lpQUAD_LIST;


typedef struct 	surface_st
{
	QUAD_LIST		quadList;
	int				vertexSpan;
	DVECTOR			outputList[WORLDVERTICES];
	long				szList[WORLDVERTICES];
	unsigned char	clippedList[WORLDVERTICES];
	short				noTextureFlag;

}	SURFACE_GLOBS, *lpSURFACE_GLOBS;

extern	SURFACE_GLOBS	surfaceGlobs;



/* prototypes */

VOID	Surface_initialiseQuadList(lpQUAD_LIST quadList);
VOID	Surface_initialiseWorldQuadList(void);
VOID	Surface_rebuildVertexBuffer(lpLego_Level current_level, Sint16 mx, Sint16 my, BOOL full);
VOID Surface_rebuildWorldQuadList(lpLego_Level current_level, Sint16 mx, Sint16 my, BOOL changed);
VOID	Surface_addPrimList(void);
VOID	Surface_addQuadList(lpQUAD_LIST quadList);
BOOL	Surface_GetHeight(lpLego_Level current_level, int x, int z, int *height);
BOOL	Surface_GetHeightFlat(lpLego_Level current_level, int x, int z, int *height);
BOOL	Surface_GetHeightAndBrightness(lpLego_Level current_level, int x, int z, int *height, unsigned char *brightness);
void	Surface_GetOrientation(VECTOR *vertex0, VECTOR *vertex1, VECTOR *vertex2, int *anglex, int angley, int *anglez);
void	Surface_SetUpVertices(lpLego_Level current_level, int bx, int by,  VECTOR *vertex0, VECTOR *vertex1, VECTOR *vertex2);
BOOL	Surface_SetUpVerticesFromContainer(lpContainer cont,VECTOR *v1, VECTOR *v2, VECTOR *v3, int *averageHeight, int angle, int radius, int spread);

void Surface_SetLighting(int mapX, int mapY, int width, int height, unsigned char *lightValue);
void Surface_ResetLighting(int mapX, int mapY, int width, int height);
void Surface_SetLightPoint(int mapX, int mapY, int lightScaleRed, int lightScaleGreen, int lightScaleBlue);
void Surface_SetColourPoint(int mapX, int mapY, int red, int green, int blue);
void Surface_SetColourPointPreLit(int mapX, int mapY, int red, int green, int blue, int lightSetting);
BOOL	Surface_ChangeLavaToRock(int x, int y);
void Surface_MakeSplashBlock(int x, int y, int zSpeed, int alphaDelta, int red, int green, int blue);
void Surface_MakeSplash(int x, int y, int spread, int range,int zSpeed, int alphaDelta, int red, int green, int blue);


lpDetail_TextureSet Surface_LoadTextureSet(LPUCHAR baseName, ULONG width, ULONG height);
VOID Surface_FreeTextureSet(lpDetail_TextureSet dead);

#define	__SURFACE_H
#endif



