// **************************************************************************************
// collision.h head file
// **************************************************************************************
typedef struct CPoly_type
{
	struct CPoly_type *next;
	SVECTOR *v[4];
	SVECTOR normal;
	long D;

	long min1,min2;
	long max1,max2;
}
CPoly;

// **********************************************************************************************
enum
{
	COLMAP_XZ_CEIL,
	COLMAP_XZ_FLOOR,
	COLMAP_ZY_LEFT,
	COLMAP_ZY_RIGHT,
	COLMAP_XY_LEFT,
	COLMAP_XY_RIGHT
};


// **************************************************************************************
int			Collision_SelectMap(SVECTOR *dir);
void		Collision_Setup(u_long *hmd);
u_long		Collision_TestXZ(VECTOR *pos,long *height,SVECTOR **normal,int map);
u_long		Collision_TestXY(VECTOR *pos,long *height,SVECTOR **normal,int map);
u_long		Collision_TestZY(VECTOR *pos,long *height,SVECTOR **normal,int map);
BOOL		Collision_Test(VECTOR *pos,SVECTOR *dir,VECTOR *hit,SVECTOR **n);
lpContainer	Container_LoadStaticCollisionHMDModel(lpContainer root, LPUCHAR fname, int modeflags);


// **************************************************************************************
// **************************************************************************************
// **************************************************************************************
// **************************************************************************************
// **************************************************************************************
// **************************************************************************************

