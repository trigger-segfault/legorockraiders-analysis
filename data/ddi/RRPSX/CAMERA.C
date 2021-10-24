//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Camera code For <LEGO [Rock Raiders]>
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹


#include	"globals.h"


#define		CAMERA_SHAKING					/* if defined camera can be made to shake */
#define		CAMERA_SHAKE_RANGE_X			(31)			
#define		CAMERA_SHAKE_RANGE_Y			(31)			
#define		CAMERA_SHAKE_RANGE_Z			(31)			

SMOOTH		cameraSmooth;

lpContainer	Camera_CreateCamera(lpContainer cont);


/*
	initialise smoothing camera to free mode
	with default values
*/
void	Camera_InitSmoothing(void)
{
	cameraSmooth.mode=CAMERA_MODE_ANGLE_TRACK;
	cameraSmooth.reset=TRUE;
	cameraSmooth.radius=ToFIXED(DEFAULT_CAMERA_RADIUS);
	cameraSmooth.height=ToFIXED(DEFAULT_CAMERA_HEIGHT);
	cameraSmooth.angleY=DEFAULT_CAMERA_ANGLE_Y;
	cameraSmooth.zoomMin=ONE;
	cameraSmooth.zoomMax=ONE<<1;
	cameraSmooth.zoomLevel=ONE;
	cameraSmooth.zoomToggle=ZOOM_IN;
	cameraSmooth.cont=Camera_CreateCamera(NULL);
}


lpContainer	Camera_CreateCamera(lpContainer cont)
{
	lpContainer	cam;
	LPVECTOR3D		v;
	
	if (cam=Container_Create(cont))
	{
		if (v=Mem_Malloc(sizeof(VECTOR)))
		{
			memset(v, 0, sizeof(VECTOR3D));
			cam->modelData=v;
			cam->type = TYPE_HMDCAMERA;
		}
		else
		{
			Container_Remove(cam);
			cam = NULL;
		}
	}
	return cam;
}




void	Camera_SetContainerYAngle(lpContainer camCont, int angle)
{
	camCont->coords.rot.vy=angle;
}

void	Camera_SetSmoothingStatus(BOOL flag)
{
	cameraSmooth.reset=flag;
}


void	Camera_SetZoomLevel(int zoomLevel)
{
	cameraSmooth.zoomLevel=zoomLevel;
}

int	Camera_GetZoomLevel(void)
{
	return	cameraSmooth.zoomLevel;
}


void	Camera_SetMode(int mode)
{
	cameraSmooth.mode=mode;
}

int	Camera_GetMode(void)
{
	return	cameraSmooth.mode;
}

/*
	set look direction
*/
void	Camera_SetRotationY(int rotation)
{
	cameraSmooth.targetAngleY=rotation;
}

int	Camera_GetRotationY(void)
{
	return	cameraSmooth.targetAngleY;
}

/*
	this resets the angle directly, where lag is not required
*/
int	Camera_SetRotationDirect(int rotation)
{
	cameraSmooth.angleY=rotation;
}


/*
	set the number of game cycles the camera will shake for.
	-1== off
*/
void	Camera_SetShakeTimer(int time)
{
	cameraSmooth.shakeTimer=time;
}

/*
	set a camera on an object, offset by a radius in the objects y rotation
	also smoothes camera viewpoint. 

	cont2 is an optional second container, if valid the viewpoint is averaged
	between both containers.
*/
void	Camera_SetCameraOnVelocityObject(lpContainer cont, lpContainer cont2, int radius, int radius2)
{
	VECTOR3D		cameraPos,cameraLook;
	VECTOR3D		objectPos,objectRot;
	int			n;
	int			yDelta;


	if (legoGlobs.pauseFlag)		/* leave camera as it is if paused */
		return;


	Container_GetPosition(cont,&objectPos);
	Container_GetRotation(cont,&objectRot);

	if (objectGlobs.playerList[0].flags & PLAYER_FLAG_MINIFIGURE_ACTIVE)
	{
		/*
			if the minifigure is active then we use the zSurface of the minifigure
			instead of it's z - makes jumping look better
		*/


		objectPos.z=objectGlobs.playerList[0].minifigureObject->zSurface>>12;				
	}

	if (cameraSmooth.mode==CAMERA_MODE_ANGLE_TRACK)
	{
		yDelta=((2048-objectRot.y)-cameraSmooth.angleY) &4095;
		if (yDelta<0)
		{
			if (yDelta<-2048)
				yDelta+=4096;
		}
		else
		{
			if (yDelta>2048)
				yDelta-=4096;
		}
		cameraSmooth.angleY+=yDelta>>4;
	}

/* smooth the transition of the look angle */

	yDelta=(cameraSmooth.targetAngleY-cameraSmooth.lookAngleY) &4095;
	if (yDelta<0)
	{
		if (yDelta<-2048)
			yDelta+=4096;
	}
	else
	{
		if (yDelta>2048)
			yDelta-=4096;
	}
	cameraSmooth.lookAngleY+=yDelta>>3;
 	
	cameraPos.x=FromFIXED((Asm_MulFIX((Asm_MulFIX(cameraSmooth.radius,cameraSmooth.zoomLevel)),rsin(cameraSmooth.angleY+cameraSmooth.lookAngleY))));
	cameraPos.y=FromFIXED((Asm_MulFIX((Asm_MulFIX(cameraSmooth.radius,cameraSmooth.zoomLevel)),rcos(cameraSmooth.angleY+cameraSmooth.lookAngleY))));
	cameraPos.z=FromFIXED(Asm_MulFIX(cameraSmooth.height,cameraSmooth.zoomLevel));


	cameraLook.x=objectPos.x-Asm_MulFIX(radius,csin(objectRot.y));
	cameraLook.y=objectPos.y+Asm_MulFIX(radius,ccos(objectRot.y));
	cameraLook.z=objectPos.z;

	if (cont2)			/* optional second container */
	{
		Container_GetPosition(cont2,&objectPos);
		Container_GetRotation(cont2,&objectRot);

		cameraLook.x+=(objectPos.x-Asm_MulFIX(radius2,csin(objectRot.y)));
		cameraLook.y+=(objectPos.y+Asm_MulFIX(radius2,ccos(objectRot.y)));
		cameraLook.z+=objectPos.z;

		cameraLook.x>>=1;		
		cameraLook.y>>=1;
		cameraLook.z>>=1;


		/* could change zoom here to reflect the distance between the container positions */

	}


/* now we average the camera destination over a number of frames */

	if (cameraSmooth.reset)
	{
		for (n=0; n<MAX_SMOOTH; n++)
		{
			cameraSmooth.lookAt[n].x=cameraLook.x;
			cameraSmooth.lookAt[n].y=cameraLook.y;
			cameraSmooth.lookAt[n].z=cameraLook.z;
			cameraSmooth.index=0;
		}
		cameraSmooth.reset=FALSE;
	}
	else
	{
		cameraSmooth.lookAt[cameraSmooth.index].x=cameraLook.x;
		cameraSmooth.lookAt[cameraSmooth.index].y=cameraLook.y;
		cameraSmooth.lookAt[cameraSmooth.index].z=cameraLook.z;
		cameraSmooth.index++;

		if (cameraSmooth.index==MAX_SMOOTH)
			cameraSmooth.index=0;

		cameraLook.x=0;
		cameraLook.y=0;
		cameraLook.z=0;

		for (n=0; n<MAX_SMOOTH; n++)
		{
			cameraLook.x+=cameraSmooth.lookAt[n].x;
			cameraLook.y+=cameraSmooth.lookAt[n].y;
			cameraLook.z+=cameraSmooth.lookAt[n].z;
		}
	
		cameraLook.x>>=SMOOTH_POWER;
		cameraLook.y>>=SMOOTH_POWER;
		cameraLook.z>>=SMOOTH_POWER;
	}

#ifdef	CAMERA_SHAKING
	if (cameraSmooth.shakeTimer!=-1)
	{
		cameraSmooth.shakeTimer--;
		cameraLook.x+=RR(CAMERA_SHAKE_RANGE_X);
		cameraLook.y+=RR(CAMERA_SHAKE_RANGE_Y);
		cameraLook.z+=RR(CAMERA_SHAKE_RANGE_Z);
	}
#endif

#ifdef MAPEDIT
	if (mapeditGlobs.mode)
	{
		int					blockX,blockY,nextZ;
		lpLego_Block		block;
		VECTOR3D	v1;

		blockX=mapeditGlobs.vx>>9;
		blockY=mapeditGlobs.vy>>9;
		block=&blockValue(legoGlobs.currLevel,blockX,blockY);

	/* set camera on edit cursor position */

		cameraPos.x=FromFIXED((Asm_MulFIX((Asm_MulFIX(cameraSmooth.radius,cameraSmooth.zoomLevel)),rsin(0))));
		cameraPos.y=FromFIXED((Asm_MulFIX((Asm_MulFIX(cameraSmooth.radius,cameraSmooth.zoomLevel)),rcos(0))));
		cameraPos.z=FromFIXED(Asm_MulFIX(cameraSmooth.height,cameraSmooth.zoomLevel));


		cameraLook.x=mapeditGlobs.vx;
		cameraLook.y=mapeditGlobs.vy;

		if (Surface_GetHeightFlat(legoGlobs.currLevel,mapeditGlobs.vx,mapeditGlobs.vy, &nextZ))
			cameraLook.z=nextZ;
		else
			cameraLook.z=-block->topLeftAlt;


/* vertex marker */
		v1.x=-block->xoff;
		v1.y=block->yoff;
		v1.z=-block->topLeftAlt;
		draw_world_cross(&v1,255,255,255);

/* floating camera marker */
		v1.x=mapeditGlobs.vx;
		v1.y=mapeditGlobs.vy;
		v1.z=-block->topLeftAlt;
		draw_world_cross(&v1,0,255,0);

	}
#endif

	set_camera_on_position(cameraSmooth.cont,&cameraPos,&cameraLook);
	Camera_SetContainerYAngle(cameraSmooth.cont,cameraSmooth.angleY+cameraSmooth.lookAngleY);
}


#define		CAMERA_Y_ROTATION_DELTA		(32)
#define		CAMERA_ZOOM_DELTA				(256)

/*
	stuff to handle camera changes allowed from joypad


	default controls are:

		Left top shoulder		- camera mode toggle
		Right top shoulder	- zoom toggle

		bottom shoulders		- rotate camera left/right (both together resets camera behind object)
*/
void	Camera_HandleCameraInteraction(int time)
{
	lpCONTROL	control=objectGlobs.playerList[0].controlSet;
	int			rotY=Camera_GetRotationY();
	int			zoomLevel;
	int			count=0;

/* camera y rotation */

	if (PAD_EVENT(control,CONTROL_CAMERA_ROTATE_LEFT))
	{
		count++;
		rotY-=(Asm_MulFIX(CAMERA_Y_ROTATION_DELTA<<12,time)>>12);
		CLEAR_EVENT_IMMEDIATE(control,CONTROL_CAMERA_ROTATE_LEFT);
	}

	if (PAD_EVENT(control,CONTROL_CAMERA_ROTATE_RIGHT))
	{
		count++;
		rotY+=(Asm_MulFIX(CAMERA_Y_ROTATION_DELTA<<12,time)>>12);
		CLEAR_EVENT_IMMEDIATE(control,CONTROL_CAMERA_ROTATE_RIGHT);
	}

	if (count==2)		/* both together will reset the angle */
	{
		CLEAR_EVENT_RELEASE(control,CONTROL_CAMERA_ROTATE_LEFT);
		CLEAR_EVENT_RELEASE(control,CONTROL_CAMERA_ROTATE_RIGHT);
		rotY=0;
	}
	Camera_SetRotationY(rotY);


/* change zoom level */

	if (PAD_EVENT(control,CONTROL_CAMERA_ZOOM_TOGGLE))
	{
		cameraSmooth.zoomToggle^=1;
		CLEAR_EVENT_RELEASE(control,CONTROL_CAMERA_ZOOM_TOGGLE);
	}


/* change mode */

	if (PAD_EVENT(control,CONTROL_CAMERA_MODE))
	{
		cameraSmooth.mode++;
		if (cameraSmooth.mode==CAMERA_MODE_MAX_MODES)
			cameraSmooth.mode=CAMERA_MODE_FREE;
		CLEAR_EVENT_RELEASE(control,CONTROL_CAMERA_MODE);
	}



/* camera zooming */

	zoomLevel=Camera_GetZoomLevel();

	if (cameraSmooth.zoomToggle==ZOOM_IN)
	{
		if (zoomLevel>cameraSmooth.zoomMin)
			zoomLevel-=(Asm_MulFIX(CAMERA_ZOOM_DELTA<<12,time)>>12);
	}
	else
	{
		if (zoomLevel<cameraSmooth.zoomMax)
			zoomLevel+=(Asm_MulFIX(CAMERA_ZOOM_DELTA<<12,time)>>12);
	}
	Camera_SetZoomLevel(zoomLevel);


/* texturing toggle */

//	if (PAD_EVENT(control,CONTROL_SQUARE_NO_ACTION))
//	{
//		surfaceGlobs.noTextureFlag^=1;
//		CLEAR_EVENT_RELEASE(control,CONTROL_SQUARE_NO_ACTION);
//	}


	return;



/* height */

	if (PAD_EVENT(control,CONTROL_DIG))
	{
		cameraSmooth.height+=64<<12;
		CLEAR_EVENT_IMMEDIATE(control,CONTROL_DIG);
	}

	if (PAD_EVENT(control,CONTROL_SYS_CROSS))
	{
		cameraSmooth.height-=64<<12;
		CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_CROSS);
	}

/* radius */

	if (PAD_EVENT(control,CONTROL_SYS_SQUARE))
	{
		cameraSmooth.radius+=64<<12;
		CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_SQUARE);
	}

	if (PAD_EVENT(control,CONTROL_SYS_CIRCLE))
	{
		cameraSmooth.radius-=64<<12;
		CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_CIRCLE);
	}

}
