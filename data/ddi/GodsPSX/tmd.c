//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// TMD File For <GODS PSX>
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

// Include all Header Files

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
#include	"libgods.h"
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ


// **********************************************************************************************
void TMD_Initialise(void)
{
}

// ***** *****************************************************************************************
void TMD_ShutDown(void)
{
}

// **********************************************************************************************
lpTMD_Model TMD_LoadModel(u_long *addr)
{
unsigned long	*dop;
GsDOBJ2			*objp;									/* handler of object */
int				i;
u_long			*oppp;

lpTMD_Model		model;
GsDOBJ2			*object;
int				objNum;


u_long			*tmdp;


	tmdp = addr;							/* top address of TMD data*/
	
	tmdp++;									/* skip fie header*/
	
	GsMapModelingData(tmdp);				/* map to real address*/
	
	tmdp++;		/* skip flag*/
	tmdp++;		/* skip number of objects*/
	
	model = (lpTMD_Model) Mem_Malloc(sizeof(TMD_Model));
	model->tmdData = (lpTMD_Section) Mem_Malloc(sizeof(TMD_Section));

	GsLinkObject4((u_long)tmdp, &model->tmdData[0].object, 0);

	GsInitCoordinate2(WORLD, &model->tmdData[0].coord);
	
	/* initialize 3D objects*/
	model->tmdData[0].object.coord2		= &model->tmdData[0].coord;
	//model->tmdData[0].object.tmd		= tmdp;		
	model->tmdData[0].object.attribute	= 0;




	// the below code should work for a tmd that has multiple sections.
	// it's not tested and I'm not sure how it will react to being displayed
	// more than once.
  

/*
	dop = File_LoadBinary(fname, NULL);

	if (dop == NULL)
	{
		printf("(TMD.C) ERROR:  Couldn't load %s\n", fname);
		return NULL;
	}

	dop++;												// hedder skip 
	GsMapModelingData(dop);								// Mappipng real address 
	dop++;
	objNum = *dop;										// Get number of Objects 
	dop++;												// Adjusting for GsLinkObject4

	model				= (lpTMD_Model) Mem_Malloc(sizeof(TMD_Model));

	model->objectNum	= objNum;


	printf("objNum = %d\n", objNum);


	if (objNum <= 0)		
	{
		printf("eeeeeeeeeeeeeeeeeeeek\n");
		return NULL;
	}


	model->tmdData		= (lpTMD_Section) Mem_Malloc(sizeof(TMD_Section) * objNum);


	// Link ObjectHandler and TMD FORMAT MODELING DATA 
	for(i = 0 ; i < objNum; i++)
	{
		GsLinkObject4((unsigned long)dop, &model->tmdData[i].object, i);
	}
  

	for(i = 0 ; i < objNum ; i++)
	{
							
		objp = &model->tmdData[i].object;

		if (i > 0)
		{
			GsInitCoordinate2(&model->tmdData[0].coord, &model->tmdData[i].coord);
		}
		else
		{
			GsInitCoordinate2(WORLD, &model->tmdData[i].coord);
		}

		objp->coord2	= &model->tmdData[i].coord;				
		objp->tmd		= dop;
	}
  
	//model->tmdData[0].object.attribute |= GsALON;


*/
	


	if (model == NULL)	printf("EEEEEEEEEEEEEEEEEEEEEEEEEEEEee\n");

return model;
}

// **********************************************************************************************
void TMD_Draw(TMD_Model *model, int x, int y, int z, int rx, int ry, int rz)
{
int i;
GsDOBJ2 *op;			/* pointer of Object Handler */
MATRIX  tmpls;
Uint32				*ot=(Uint32*)gfxGlobs.Wot[gfxGlobs.bufID].org;
MATRIX tmp1;


//	TMD_SetPositionRotation(model, 0, TRUE,	x, y, z, TRUE, rx, ry, rz);
	d0 = 0;

// optimization of above call 
	Dsvec1.vx = rx;
	Dsvec1.vy = ry;
	Dsvec1.vz = rz;


	model->tmdData[d0].coord.coord.t[0]=x;//	tmp1.t[0] = x;
	model->tmdData[d0].coord.coord.t[1]=y;//	tmp1.t[0] = x;
	model->tmdData[d0].coord.coord.t[2]=z;//	tmp1.t[0] = x;
//	tmp1.t[1] = y;
//	tmp1.t[2] = z;
  
	// Rotate Matrix
	RotMatrix_gte(&Dsvec1,&model->tmdData[d0].coord.coord);
  
	// Set Matrix to Coordinate
//	model->tmdData[d0].coord.coord = tmp1;

	// Clear flag becase of changing parameter
	model->tmdData[d0].coord.flg = 0;



//	for(i = 0 ; i < model->objectNum ; i++)
//	{
		op = &model->tmdData[d0].object;


		GsGetLw(op->coord2,&tmpls);											  /* Calculate Local-World Matrix */
		GsSetLightMatrix(&tmpls);	 											  /* Set LWMATRIX to GTE Lighting Registers */
		GsGetLs(op->coord2,&tmpls);											  /* Calculate Local-World Matrix */
		GsSetLsMatrix(&tmpls);	 											  /* Set LSAMTRIX to GTE Registers */
		GsSortObject4(op, &gfxGlobs.Wot[gfxGlobs.bufID], 0, getScratchAddr(4*16));	  /* Perspective Translate Object and Set OT */
//	}

}

// **********************************************************************************************
void TMD_SetPositionRotation(TMD_Model *model, int section, BOOL position,	int x,	int y,	int z, 
															BOOL rotate,	int rx, int ry, int rz)
{
	if (position == TRUE)
	{
		model->tmdData[section].coord.coord.t[0] = x;
		model->tmdData[section].coord.coord.t[1] = y;
		model->tmdData[section].coord.coord.t[2] = z;
	}

	if (rotate == TRUE)
	{
		model->tmdData[section].svector.vx = rx;
		model->tmdData[section].svector.vy = ry;
		model->tmdData[section].svector.vz = rz;
	}

	TMD_SetCoordinate(&model->tmdData[section].svector, &model->tmdData[section].coord);
}

// **********************************************************************************************
void TMD_SetCoordinate(SVECTOR *pos, GsCOORDINATE2 *coor)
{
MATRIX tmp1;
  
	// Set translation
	tmp1.t[0] = coor->coord.t[0];
	tmp1.t[1] = coor->coord.t[1];
	tmp1.t[2] = coor->coord.t[2];
  
	// Rotate Matrix
	RotMatrix(pos,&tmp1);
  
	// Set Matrix to Coordinate
	coor->coord = tmp1;

	// Clear flag becase of changing parameter
	coor->flg = 0;
}


// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************



