//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// craft File For <LEGO Rock Raiders>
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#ifndef	__CRAFT_H



enum
{
	MODE_AND_SIZE				=1,
	LEFT_STICK_HORIZONTAL	=6,
	LEFT_STICK_VERTICAL		=7,
	RIGHT_STICK_HORIZONTAL	=4,
	RIGHT_STICK_VERTICAL		=5,

};


enum
{
	STANDARD_JOYPAD		=4,
	DUAL_SHOCK				=7,
};

/* definitions */


#define	THRESHOLD	(800)


#define		LARGE_DIGGER_TURN_DELTA						(64)
#define		LARGE_DIGGER_FORWARD_ACCEL_DELTA			(8)
#define		LARGE_DIGGER_BACKWARD_ACCEL_DELTA		(-8)
#define		LARGE_DIGGER_DECEL_DELTA					(4)
#define		LARGE_DIGGER_FORWARD_SPEED_CAP			(128)
#define		LARGE_DIGGER_BACKWARD_SPEED_CAP			(-128)
#define		LARGE_DIGGER_MASS								(1000)

#define		LARGE_DIGGER_DRILL_SPEED_CAP				(1024)
#define		LARGE_DIGGER_DRILL_ACCEL_DELTA			(32)
#define		LARGE_DIGGER_DRILL_DECEL_DELTA			(16)


		 /* defines */




enum
{
	COLLISION_RADIUS,
	ACTIVATION_RADIUS,
};


enum
{
	CF_AUTO_TURN_FORWARD			=	1,		/* if set, then turning without forward motion will apply some forward motion */
	CF_CAN_DRILL					=	2,		/* vehicle can drill rock */
	CF_DRIVEABLE					=	4,		/* a crate is treated as a craft, but obviously can't be driven */
	CF_LIFTABLE						=	8,		/* indicates whether it is liftable by the transport chopper */
	CF_LIFTED						= 16,		/* set if a craft is currently held */
	CF_CAN_LIFT						= 32,		/* set if a craft can lift another */
};




extern			CONTROL			nullControlSet[MAX_CONTROLS];
extern			CRAFT_SETUP		craftSetupData[];


void			Craft_initialiseLists(void);
BOOL			Craft_CreateCraft(int craftType,int x, int y, int direction);
void 		Craft_CreateCraftData(lpOBJECT object, int vehicleType);
BOOL			Craft_UpdateGroundCraft(lpPLAYER player, lpOBJECT object, int time);
BOOL			Craft_UpdateNonCraft(lpPLAYER player, lpOBJECT object, int time);
BOOL			Craft_UpdateAirCraft(lpPLAYER player, lpOBJECT object, int time);
void			Craft_DrawActivationReticule(lpOBJECT craftObject, lpPLAYER player);
void			Craft_SetVolumeAndFrequencyEngineSfx(lpOBJECT object, int sample, int baseFrequency, int frequencyAdjust);
void			Craft_SetVolumeAndFrequencyDrillSfx(lpOBJECT object, int sample, int baseFrequency, int frequencyAdjust, int rockType);
lpOBJECT	Craft_GetCraftInRangeOfMinifigure(lpMINIFIGURE minifigure, int newX, int newY, int newZ, int *type);
BOOL			Craft_GetDirectionNotInCollisionWithMinifigure(lpOBJECT minifigureObject, lpOBJECT craftObject, int angle, int radius, int *direction);
lpOBJECT	Craft_GetCraftInCollisionWithCraft(lpOBJECT currentCraftObject, int newX, int newY, int newZ);
BOOL			Craft_GetDigBlockAndSurface(int *x, int *y, Lego_Block **block);
lpOBJECT	Craft_GetLiftableCraft(lpOBJECT currentCraftObject, int newX, int newY);
void			Craft_DrawLiftReticule(lpOBJECT craftObject, lpPLAYER player);

#define	__CRAFT_H

#endif

