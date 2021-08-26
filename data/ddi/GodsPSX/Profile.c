/*-------- #includes -------+--------+--------+--------+--------+-------+---*/
#include <sys\types.h>
#include <libgte.h>
#include <libgpu.h>
#include <stdio.h>
#include <asm.h>
#include <kernel.h>
#include <libsn.h>
#include <libetc.h>

/*-------- #defines and macros ------+--------+--------+--------+-------+---*/

#define	TOP			85//110
#define	LEFT		-150
#define HEIGHT		5
#define	GRIDSIZE	65
#define	DRAW_TOP	95//100

#define	PROFILE_MODE_NTSC 		1
#define	PROFILE_MODE_PAL		2
#define	HBL_MID_VAL	((525+625)/4)

/*-------- typedefs --------+--------+--------+--------+--------+-------+---*/
typedef struct
{
	short xgrid;
	char scalefactor;
	char nummarks;
} SCALE;

/*-------- Globals and Statics ------+--------+--------+--------+-------+---*/
static unsigned long EHbl;
static short divisor;
static short nummarks;
static short finalCount;
static short  GscaleFactor;
static POLY_G4	bargraph[2];
static POLY_F3	markers[9];
static POLY_F3	markers2[9];

static short drawCount;
static short pad1;

static SCALE scales[] =
{
	{ 260, 0, 2 },
	{ 130, 1, 3 },
	{ 65,  2, 5	}
};

/*-------- Function definitions -----+--------+--------+--------+-------+---*/

static void ProfileCallBack()
{
	drawCount = GetRCnt(RCntCNT1)>>divisor;
}

/*--------+--------+--------+--------+--------+--------+--------+-------+---*/

ProfileInit(int scale)
{
 	char count;

	int grid = scales[scale].xgrid;
	nummarks = scales[scale].nummarks;
	divisor = scales[scale].scalefactor;

	EnterCriticalSection();
	EHbl = OpenEvent(RCntCNT1, EvSpINT, EvMdNOINTR, NULL);
	EnableEvent(EHbl);
	SetRCnt(RCntCNT1, 64000, RCntMdINTR);

	DrawSyncCallback(ProfileCallBack);

	ExitCriticalSection();

	for (count = 0; count < nummarks; count++ )
	{
	  	SetPolyF3(&markers[count]);
		setRGB0(&markers[count],50,50,150);
		setXY3(&markers[count],
			LEFT+count*grid-4,TOP-5,
			LEFT+count*grid+4,TOP-5,
			LEFT+count*grid,TOP+5);

	  	SetPolyF3(&markers2[count]);
		setRGB0(&markers2[count],50,50,150);
		setXY3(&markers2[count],
			LEFT+count*grid-4,DRAW_TOP+15,
			LEFT+count*grid+4,DRAW_TOP+15,
			LEFT+count*grid,DRAW_TOP+5);
	}

	SetPolyG4(&bargraph[0]);
	setRGB0(&bargraph[0],0,200,0);
	setRGB1(&bargraph[0],200,0,0);
	setRGB2(&bargraph[0],0,200,0);
	setRGB3(&bargraph[0],200,0,0);
	setXY4(&bargraph[0], LEFT,TOP, 100,TOP, LEFT,TOP+HEIGHT, 100,TOP+HEIGHT);

	SetPolyG4(&bargraph[1]);
	setRGB0(&bargraph[1],0,200,0);
	setRGB1(&bargraph[1],200,0,0);
	setRGB2(&bargraph[1],0,200,0);
	setRGB3(&bargraph[1],200,0,0);
	setXY4(&bargraph[1], LEFT,DRAW_TOP, 
					100,DRAW_TOP, LEFT,DRAW_TOP+HEIGHT, 100,DRAW_TOP+HEIGHT);


}


/*--------+--------+--------+--------+--------+--------+--------+-------+---*/


ProfileStartCount()
{
	ResetRCnt(RCntCNT1);
	StartRCnt(RCntCNT1);
}

/*--------+--------+--------+--------+--------+--------+--------+-------+---*/


short ProfileStopCount()
{
	StopRCnt(RCntCNT1);
	finalCount = GetRCnt(RCntCNT1)>>divisor;
	return finalCount;
}

/*--------+--------+--------+--------+--------+--------+--------+-------+---*/

short ProfileReadCount()
{
	finalCount = GetRCnt(RCntCNT1)>>divisor;
	return finalCount;
}

/*--------+--------+--------+--------+--------+--------+--------+-------+---*/


ProfileAddOT(unsigned long * ot)
{
	char count;

	bargraph[0].x1 = finalCount+LEFT;
	bargraph[0].x3 = finalCount+LEFT;
	for (count = 0; count < nummarks; count++ )
	{
		AddPrim(ot,&markers[count]);
	}


	AddPrim(ot,&bargraph[0]);
}

/*--------+--------+--------+--------+--------+--------+--------+-------+---*/

ProfileAddDrawOT(unsigned long * ot)
{
	char count;

	bargraph[1].x1 = drawCount+LEFT;
	bargraph[1].x3 = drawCount+LEFT;

	for (count = 0; count < nummarks; count++ )
	{
		AddPrim(ot,&markers2[count]);
	}

	AddPrim(ot,&bargraph[1]);
}

/*--------+--------+--------+--------+--------+--------+--------+-------+---*/


int ProfileDispMode(void)
{
	int count;

	VSync(0);
	ProfileInit(0);
	ProfileStartCount();
	VSync(0);
	count = ProfileStopCount();

	if (count < HBL_MID_VAL)
		return PROFILE_MODE_NTSC;
	else
		return PROFILE_MODE_PAL;
}

/*--------+--------+--------+--------+--------+--------+--------+-------+---*/

