
//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Container.c - [Container Code]
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#define	CONTAINER2_MAX_CONTAINERS					185					// (this must NOT exceed 256)


// ERROR Return values ******************************************************************
#define CONTAINER2_ERROR_SUCCESS					-1		// everything worked out ok
#define CONTAINER2_ERROR_CONTAINER_LIST_FULL		-2		// tried to create a new container but there weren't any free
#define CONTAINER2_ERROR_NULL_CONTAINER				-3		// tried to use a null container
#define	CONTAINER2_ERROR_FILE_NOT_FOUND				-4		// file not found
#define CONTAINER2_ERROR_OUT_OF_MEMORY				-5		// out of memory when trying to Mem_Malloc
#define CONTAINER2_ERROR_NULL_OBJECT_DATA			-6		// the objectData of the container is NULL
#define	CONTAINER2_ERROR_INVALID_CONTAINER_CONTEXT	-7		// eg. tried to animate a non animating hmd etc
#define	CONTAINER2_ERROR_NO_SUCH_TYPE				-8		// tried to create an invalid type of container
#define CONTAINER2_ERROR_OPERATION_FAILED			-9		// general failure.



// **************************************************************************************
#define	CONTAINER2_FLAG_HIDDEN				1<<1				// is the container hidden or not?


// **************************************************************************************
enum
{
	CONTAINER2_TYPE_STATIC_HMD,
	CONTAINER2_TYPE_STATIC_TMD,
	CONTAINER2_TYPE_ANIMATING_HMD,
	CONTAINER2_TYPE_SPRITE,			  // *** NOT INCLUDED YET ***
	CONTAINER2_TYPE_MAX_CONTAINERS
};


// **************************************************************************************
typedef	struct Container2
{

	BOOL				valid;					// is this container in use or not?

	int					flags;					// set of flags for the container

	short				type;					// what type of container this is
	LPVOID				objectData;				// the data for the object
	struct Container2	*link;					// link this container with another one

} Container2, *lpContainer2;


// **************************************************************************************
typedef struct Container2_Globs
{
	lpContainer2 list[MAX_CONTAINERS];			// the list of containers we can use
} Container2_Globs;


// **************************************************************************************
// initialisation and shutdown
void			Container2_Initialise(void);
void			Container2_ShutDown(void);

// create a container...eg, ("VEHICLES\\PCUTTER.HMD", CONTAINER2_TYPE_STATIC_HMD, 0)
lpContainer2		Container2_Create(unsigned char *fname, int type, int flags);


// internal calls, best not to be used.
short			Container2_FindEmptyContainer(void);


// can be used on all containers
short			Container2_DrawContainer(lpContainer2 cont, int x, int y, int z, int rx, int ry, int rz);


// can only be performed on an HMD (animating or static)
short			Container2_SetPosition(lpContainer2 cont, int x, int y, int z, short index);
short			Container2_SetRotation(lpContainer2 cont, int rx, int ry, int rz, short index);
short			Container2_ScaleHMD(lpContainer2 cont, int sx, int sy, int sz);



// can only be performed on an animating HMD
short			Container2_AnimateHMD(lpContainer2 cont, int sid, int frames, int speed);
short			Container2_DrawAnimatingHMD(lpContainer2 cont, int x, int y, int z, int rx, int ry, int rz);


// can onlt be performed on a static HMD
short			Container2_DrawMatrixHMD(lpContainer2 cont, int x, int y, int z, MATRIX *matrix);
short			Container2_DrawHMD(lpContainer2 cont, int x, int y, int z, int rx, int ry, int rz);


// can onlt be performed on a static TMD
short			Container2_DrawTMD(lpContainer2 cont, int x, int y, int z, int rx, int ry, int rz);



// **************************************************************************************
// **************************************************************************************
// **************************************************************************************

