//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Container File For <GODS PSX>
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

// Include all Header Files

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
#include	"libgods.h"
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹


Container2_Globs	container2Globs;



// **********************************************************************************************
void Container2_Initialise(void)
{
short l;

	for (l = 0 ; l < CONTAINER2_MAX_CONTAINERS ; l++)
	{
		container2Globs.list[l] = NULL;
	}
}

// **********************************************************************************************
void Container2_ShutDown(void)
{
short l;

	for (l = 0 ; l < CONTAINER2_MAX_CONTAINERS ; l++)
	{
		if (container2Globs.list[l] != NULL)	
		{
			// -TO DO- got to remember to free the model 

			// free the container
			Mem_Free(container2Globs.list[l]);
			container2Globs.list[l] = NULL;
		}
	}

}

// **********************************************************************************************
lpContainer2		Container2_Create(unsigned char *fname, int type, int flags)
{
short	container_num = -1;
unsigned long	*load_file=NULL;	

	container_num = Container2_FindEmptyContainer();

	if (container_num < 0)	return (lpContainer2) CONTAINER2_ERROR_CONTAINER_LIST_FULL;		// oops no free containers..

	container2Globs.list[container_num] = Mem_Malloc(sizeof(Container2));

	if (container2Globs.list[container_num] == NULL)	return  (lpContainer2) CONTAINER2_ERROR_OUT_OF_MEMORY;	// oops no free memory

	// set up the quick container vars...
	container2Globs.list[container_num]->valid		=	TRUE;
	container2Globs.list[container_num]->flags		=	flags;
	container2Globs.list[container_num]->type		=	type;
	container2Globs.list[container_num]->link		=	NULL;

	load_file =	File_LoadBinary(fname, NULL);		// load the hmd in
	if (load_file == NULL)	return  (lpContainer2) CONTAINER2_ERROR_FILE_NOT_FOUND;		// can't find file 

	switch (type)
	{
	case	CONTAINER2_TYPE_STATIC_HMD		: 
				// initialise and load in a static HMD
				container2Globs.list[container_num]->objectData	= (HMD_Model *)HMD_InitStaticModel(load_file, NULL, 0);
				break;



	case	CONTAINER2_TYPE_ANIMATING_HMD	:
				// initialise and load in an animating HMD
				container2Globs.list[container_num]->objectData = (HMD_Model *)HMD_InitModel(load_file, NULL, 0);
				break;



	case	CONTAINER2_TYPE_STATIC_TMD		:
				// initialise and load in a static TMD
				container2Globs.list[container_num]->objectData = (TMD_Model *)TMD_LoadModel(load_file);
				break;



	case	CONTAINER2_TYPE_SPRITE			:
				// initialise and load in a sprite
				break;



	default									:
				container2Globs.list[container_num] = NULL;

				Mem_Free(container2Globs.list[container_num]);

				return 	(lpContainer2) CONTAINER2_ERROR_NO_SUCH_TYPE;
				break;
	}


	printf("Loaded %s OK\n", fname);
return container2Globs.list[container_num];
}

// **********************************************************************************************
short	Container2_FindEmptyContainer(void)
{
short l;

	for (l = 0 ; l < CONTAINER2_MAX_CONTAINERS ; l++)
	{
		if (container2Globs.list[l] == NULL)	return l;
	}

return -1;
}


// **********************************************************************************************
short	Container2_DrawContainer(lpContainer2 cont, int x, int y, int z, int rx, int ry, int rz)
{
short ret_val = 0;

	if (cont == NULL)	return CONTAINER2_ERROR_NULL_CONTAINER;		// shouldn't be doing this


	if (cont->flags & CONTAINER2_FLAG_HIDDEN)	return CONTAINER2_ERROR_SUCCESS;	// don't draw hidden containers

	y = -y;

	switch (cont->type)
	{

	case	CONTAINER2_TYPE_STATIC_HMD	:	ret_val = Container2_DrawHMD(cont, x, y, z, rx, ry, rz);	
											break;

	case	CONTAINER2_TYPE_STATIC_TMD	:	
											ret_val = Container2_DrawTMD(cont, x, y, z, rx, ry, rz);	
											break;

	case	CONTAINER2_TYPE_ANIMATING_HMD:	ret_val = Container2_DrawAnimatingHMD(cont, x, y, z, rx, ry, rz);	
											break;

	case	CONTAINER2_TYPE_SPRITE		:	break;


	}

	if (ret_val == FALSE)	return CONTAINER2_ERROR_OPERATION_FAILED;


return CONTAINER2_ERROR_SUCCESS;
}

// **********************************************************************************************
short Container2_SetPosition(lpContainer2 cont, int x, int y, int z, short index)
{
VECTOR	position;

	if (cont == NULL)	return CONTAINER2_ERROR_NULL_CONTAINER;		// shouldn't be doing this

	if ((cont->type != CONTAINER2_TYPE_STATIC_HMD) && (cont->type != CONTAINER2_TYPE_ANIMATING_HMD))	
	{
		return CONTAINER2_ERROR_INVALID_CONTAINER_CONTEXT;
	}

	position.vx=x;
	position.vy=-y;
	position.vz=z;

	HMD_TranslateIndex(cont->objectData, index, &position);


return CONTAINER2_ERROR_SUCCESS;
}

// **********************************************************************************************
short Container2_SetRotation(lpContainer2 cont, int rx, int ry, int rz, short index)
{

	if (cont == NULL)	return CONTAINER2_ERROR_NULL_CONTAINER;		// shouldn't be doing this

	if ((cont->type != CONTAINER2_TYPE_STATIC_HMD) && (cont->type != CONTAINER2_TYPE_ANIMATING_HMD))	
	{
		return CONTAINER2_ERROR_INVALID_CONTAINER_CONTEXT;
	}

	HMD_RotateAbsolute(cont->objectData, index, rx, ry, rz);

return CONTAINER2_ERROR_SUCCESS;
}

// **********************************************************************************************
short Container2_DrawHMD(lpContainer2 cont, int x, int y, int z, int rx, int ry, int rz)
{
HMD_Model				*model;

	// cont should be valid as this is an internal call and it's already been checked
	model = cont->objectData;

	if (model == NULL)	return FALSE;	// shouldn't be doing this either


	HMD_AddStatic(model, x, y, z, rx, ry, rz, ONE/4, ONE/4, ONE/4);

return TRUE;
}

// **********************************************************************************************
short Container2_AnimateHMD(lpContainer2 cont, int sid, int frames, int speed)
{
	if (cont == NULL)	return CONTAINER2_ERROR_NULL_CONTAINER;		// shouldn't be doing this

	if (cont->type != CONTAINER2_TYPE_ANIMATING_HMD)		return CONTAINER2_ERROR_INVALID_CONTAINER_CONTEXT;

	HMD_StartAnim(cont->objectData, sid, frames, speed);

}

// **********************************************************************************************
short Container2_DrawTMD(lpContainer2 cont, int x, int y, int z, int rx, int ry, int rz)
{
TMD_Model				*model;

	// cont should be valid as this is an internal call and it's already been checked
	model = cont->objectData;

	if (model == NULL)	return FALSE;	// shouldn't be doing this either

	TMD_Draw(model, x, y, z, rx, ry, rz);

return TRUE;
}

// **********************************************************************************************
short Container2_DrawAnimatingHMD(lpContainer2 cont, int x, int y, int z, int rx, int ry, int rz)
{
HMD_Model				*model;

	// cont should be valid as this is an internal call and it's already been checked
	model = cont->objectData;

	if (model == NULL)	return FALSE;	// shouldn't be doing this either

	Container2_SetPosition(cont, x, y, z, 0);		
	Container2_SetRotation(cont, rx, ry, rz, 0);	
	HMD_AddModel(cont->objectData, &gfxGlobs.Wot[gfxGlobs.bufID]);


return TRUE;
}



// **********************************************************************************************
short Container2_ScaleHMD(lpContainer2 cont, int sx, int sy, int sz)
{
VECTOR scale;

	if (cont == NULL)	return CONTAINER2_ERROR_NULL_CONTAINER;		// shouldn't be doing this

	scale.vx = sx;
	scale.vy = sy;
	scale.vz = sz;

	HMD_Scale(cont->objectData, &scale);

}


// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************



