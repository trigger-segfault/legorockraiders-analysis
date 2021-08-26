
//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// tmd.c - [TMD Code]
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹



// **************************************************************************************

typedef struct TMD_Section
{

	GsDOBJ2			object;				
	GsCOORDINATE2   coord;
	SVECTOR         svector;


}TMD_Section, *lpTMD_Section;



typedef struct TMD_Model
{

	int				flags;
	lpTMD_Section	tmdData;
	int				objectNum;		// number of objects in the tmd

} TMD_Model, *lpTMD_Model;




// **************************************************************************************
void			TMD_Initialise(void);
void			TMD_ShutDown(void);
lpTMD_Model		TMD_LoadModel(u_long *addr);
void			TMD_SetCoordinate(SVECTOR *pos, GsCOORDINATE2 *coor);
void			TMD_Draw(TMD_Model *model, int x, int y, int z, int rx, int ry, int rz);
void			TMD_SetPositionRotation(TMD_Model *model, int section, BOOL position,	int x,	int y,	int z, 
																	   BOOL rotate,		int rx, int ry, int rz);



// **************************************************************************************
// **************************************************************************************
// **************************************************************************************
// **************************************************************************************
// **************************************************************************************

