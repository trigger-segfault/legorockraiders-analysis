//��������������������������������������������
// Viewport File For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//��������������������������������������������

// Include all Header Files

//��������������������������������������������
#include	"libgods.h"
//��������������������������������������������

Viewport_Globs viewportGlobs;


/*	SteveD:
			simplified viewport handling, there is just no point in allowing
			for lists of lists of viewports. It's not big and it's not clever.
*/

void	Viewport_Initialise(void)
{
	Uint16	loop;

	for(loop=0; loop<MAX_VIEWPORTS; loop++)
	{
		viewportGlobs.viewport_list[loop]=NULL;
	}

	viewportGlobs.flags = VIEWPORT_FLAG_INITIALISED;
	viewportGlobs.next_identifier=0;
}

lpViewport Viewport_Create(REAL xPos, REAL yPos, REAL width, REAL height, lpContainer camera)
{
	ULONG actWidth, actHeight, actXPos, actYPos;
	ULONG devWidth, devHeight;

	devWidth = Gfx_GetWidth();
	devHeight = Gfx_GetHeight();
	
	actXPos = FromFIXED(xPos * devWidth);
	actYPos = FromFIXED(yPos * devHeight);
	actWidth = FromFIXED(width * devWidth);
	actHeight = FromFIXED(height * devHeight);

	return Viewport_CreatePixel(actXPos, actYPos, actWidth, actHeight, camera);
}

lpViewport Viewport_CreatePixel(SLONG xPos, SLONG yPos, ULONG width, ULONG height, lpContainer camera)
{
	lpViewport	newViewport;
	RECT			rect;
	ULONG 		devWidth = Gfx_GetWidth();
	ULONG 		devHeight = Gfx_GetHeight();
	int			n;

	if (xPos < 0) xPos = devWidth + xPos;
	if (yPos < 0) yPos = devHeight + yPos;

	if (xPos + width > devWidth || yPos + height > devHeight)
	{
		// Error Invalid sizes provided
		return NULL;
	}

	if (viewportGlobs.next_identifier==MAX_VIEWPORTS)
		return	NULL;		/* maximum vieports allocated */

	if (camera->type!=TYPE_HMDCAMERA)
		return	NULL;							/* passed container is not a camera */

	for (n=0; n<MAX_VIEWPORTS; n++)
	{
		if (viewportGlobs.viewport_list[n]==NULL)
		{
			newViewport=viewportGlobs.viewport_list[n]=(lpViewport)Mem_Alloc(sizeof(Viewport));
			newViewport->xoffset = rect.x = xPos;
			newViewport->yoffset = rect.y = yPos;
			newViewport->width = rect.w = width;
			newViewport->height = rect.h = height;
			newViewport->camera_container=camera;
			newViewport->scale=ONE;
			newViewport->identifier=viewportGlobs.next_identifier++;
			return newViewport;
		}
	}
	return NULL;		/* no more viewports allowed */	
}

VOID Viewport_AddList(VOID)
{
#ifdef 0

	Viewport *list;
	ULONG loop, count;

	count = 0x00000001 << viewportGlobs.listCount;

	if (list = viewportGlobs.listSet[viewportGlobs.listCount] = 
		(lpViewport)Mem_Alloc(sizeof(Viewport) * count))
		{
		viewportGlobs.listCount++;

		for (loop=1 ; loop<count ; loop++)
			{
			list[loop-1].nextFree = &list[loop];
			}
		list[count-1].nextFree = viewportGlobs.freeList;
		viewportGlobs.freeList = list;
		}
	// Error Not Enough Memory For Viewport
#endif
}


BOOL Viewport_PickFind(lpViewport_Pick pick, lpContainer findCont, LPULONG group, LPULONG face, LPVECTOR3D position)
{
#ifdef 0
	if (pick)
		{
		ULONG loop;
		lpViewport_PickInfo pinfo;

		for (loop=0 ; loop<pick->pickCount ; loop++)
			{
			pinfo = &pick->pickArray[loop];
			if (pinfo->pickCont == findCont)
				{
				if (group) *group = pinfo->group;
				if (face) *face = pinfo->face;
				if (position) *position = pinfo->position;
				return TRUE;
				}
			}
		}
#endif
	return FALSE;
}

lpContainer Viewport_PickSearch(lpViewport_Pick pick, BOOL (*SearchCallback)(lpContainer match, ULONG group, ULONG face, LPVECTOR3D position, LPVOID data), LPVOID data)
{
#ifdef 0
	if (pick)
		{
		ULONG loop;

		for (loop=0 ; loop<pick->pickCount ; loop++)
			{
			if (SearchCallback(pick->pickArray[loop].pickCont, pick->pickArray[loop].group, pick->pickArray[loop].face, &pick->pickArray[loop].position, data))
				{
				return pick->pickArray[loop].pickCont;
				}
			}
		}
#endif
	return NULL;
}

VOID Viewport_InverseTransform(lpViewport vp, LPVECTOR3D dest, LPVECTOR4D src)
{
//	vp->lpVP->lpVtbl->InverseTransform(vp->lpVP, (LPD3DVECTOR) dest, (LPD3DRMVECTOR4D) src);
}

VOID Viewport_Transform(lpViewport vp, LPVECTOR4D dest, LPVECTOR3D src)
{
//	vp->lpVP->lpVtbl->Transform(vp->lpVP, (LPD3DRMVECTOR4D) dest, (LPD3DVECTOR) src);
}

LPVECTOR2D Viewport_WorldToScreen(lpViewport vp, LPVECTOR2D screen, LPVECTOR3D world)
{

	VECTOR4D v4d;

	Viewport_Transform(vp, &v4d, world);
	screen->x = Asm_DivFIX(v4d.x, v4d.w);
	screen->y = Asm_DivFIX(v4d.y, v4d.w);

	return screen;
}

VOID	Viewport_Clear(lpViewport vp)
{
	if(!vp) return;
}



//#define VIEWPORT_MARKER

BOOL	Viewport_setup_camera(lpViewport vp)
{
	if (vp->camera_container)
	{
		GsRVIEWUNIT	view;
		RECT			clip;
		int			double_buffer_id=GsGetActiveBuff();
	 	Uint32		*ot;
		Uint16		offset[2];
		int			clipped_vp=FALSE;
		int			vp_colour=(vp->identifier+1)<<6;


	/* cache current viewport */

		viewportGlobs.current_viewport=vp;

	/* set order table index from double buffer/viewport identifier */

		gfxGlobs.bufID=(double_buffer_id*MAX_VIEWPORTS)+vp->identifier;
	 	ot=(Uint32*)gfxGlobs.Wot[gfxGlobs.bufID].org;

	/* scale the delta between the camera viewpoint and it's origin */

		if (vp->scale!=ONE)
		{
							REAL	xd,yd,zd;
			LPVECTOR3D	cam_viewpoint=vp->camera_container->modelData;		/* viewpoint */

			xd=ToFIXED(vp->camera_container->coords.pos.vx-cam_viewpoint->x);
			yd=ToFIXED(vp->camera_container->coords.pos.vy-cam_viewpoint->y);
			zd=ToFIXED(vp->camera_container->coords.pos.vz-cam_viewpoint->z);

			xd=Asm_MulFIX(xd,vp->scale);
			yd=Asm_MulFIX(yd,vp->scale);
			zd=Asm_MulFIX(zd,vp->scale);

			view.vpx=cam_viewpoint->x+FromFIXED(xd);
			view.vpy=cam_viewpoint->y+FromFIXED(yd);
			view.vpz=cam_viewpoint->z+FromFIXED(zd);
		}
		else
			G3D_CopyVector(&view.vpx, &vp->camera_container->coords.pos);

		G3D_CopyVector(&view.vrx, vp->camera_container->modelData);
		view.rz = NULL;
		view.super = WORLD;
		GsSetRefViewLUnit(&view);

	/* set up drawing environment */


	/* clipping window */

		clip.x=vp->xoffset;		
		clip.y=vp->yoffset;		
		clip.w=vp->width;
		clip.h=vp->height;


#ifdef VIEWPORT_MARKER
		setPolyF4(&vp->test[double_buffer_id]);
		vp->test[double_buffer_id].x0=-(clip.w>>1);
		vp->test[double_buffer_id].y0=-(clip.h>>1);
		vp->test[double_buffer_id].x1=(clip.w>>1);
		vp->test[double_buffer_id].y1=-(clip.h>>1);
		vp->test[double_buffer_id].x2=-(clip.w>>1);
		vp->test[double_buffer_id].y2=(clip.h>>1);
		vp->test[double_buffer_id].x3=(clip.w>>1);
		vp->test[double_buffer_id].y3=(clip.h>>1);
		vp->test[double_buffer_id].r0=0;
		vp->test[double_buffer_id].g0=vp_colour;
		vp->test[double_buffer_id].b0=0;
#endif


	/* clip the clipping boundaries */

		if (vp->xoffset<0)
		{
			clip.x=0;
			clip.w+=vp->xoffset;
			clipped_vp=TRUE;
		}

		if (vp->xoffset+vp->width>gfxGlobs.scrW)
		{
			clip.w=gfxGlobs.scrW-vp->xoffset;
			clipped_vp=TRUE;
		}
 
		if (vp->yoffset<0)
		{
			clip.y=0;
			clip.h+=vp->yoffset;
			clipped_vp=TRUE;
		}

		if (vp->yoffset+vp->height>gfxGlobs.scrH)
		{
			clip.h=gfxGlobs.scrH-vp->yoffset;
			clipped_vp=TRUE;
		}


#ifdef VIEWPORT_MARKER
		if (clipped_vp)
		{
			vp->test[double_buffer_id].r0=vp_colour;
			vp->test[double_buffer_id].g0=0;
		}
		AddPrim(ot+(gfxGlobs.otSize-1),&vp->test[double_buffer_id]);
#endif

		if (double_buffer_id==0)
			clip.y+=gfxGlobs.scrH;				/* allow for double buffer */
		SetDrawArea(&vp->clip_prim[double_buffer_id],&clip);		/* create clipping primitive */
		AddPrim(ot+(gfxGlobs.otSize-1),&vp->clip_prim[double_buffer_id]);


	/* set offset for origin in centre of clipping window */

		offset[0]=vp->xoffset+(vp->width>>1);
		offset[1]=vp->yoffset+(vp->height>>1);
		if (double_buffer_id==0)
			offset[1]+=gfxGlobs.scrH;				/* add on height of buffer if other frame */
			
		SetDrawOffset(&vp->offset_prim[double_buffer_id],&offset[0]);
		AddPrim(ot+(gfxGlobs.otSize-1),&vp->offset_prim[double_buffer_id]);

		return	TRUE;
	}
	else
	{
		return	FALSE;			/* error! viewport has no camera */
	}
}


/*
	set active viewport for non container drawn stuff
*/
BOOL	Viewport_SetActive(lpViewport vp)
{
	if (vp)
	{
		if (Viewport_setup_camera(vp))
			return	TRUE;
	}
	return	FALSE;
}



/*
	this need to reset the draw environment to reflect the
	viewport passed.

*/
VOID	Viewport_Render(lpViewport vp, lpContainer cont, REAL delta)
{
	lpContainer root;

	if(!cont)
		return;

	viewportGlobs.models_drawn=0;
	viewportGlobs.models_clipped=0;

	viewportGlobs.sprites_drawn=0;
	viewportGlobs.sprites_clipped=0;


	if (!Viewport_setup_camera(vp))	/* setup new clipping window and offset */
	{
		/* no camera in viewport */
	}	


	if(Container_FindRoot(cont, &root))
	{
		if(Viewport_RenderFrame(vp,root))
		{
			/* some thing here */
		}
	}

}



/*
	we need the viewport in order to perform some rudimentary clipping on the objects.
	Viewport support is a bit sketchy at present. i.e. it doesn't work.
*/
BOOL	Viewport_RenderObject(lpViewport vp, lpContainer cont)
{
	VECTOR					pos;
	SVECTOR					rot;
	MATRIX					matLS, matLW;
	Uint16					i;
	//LPDIRECT3DRMFRAME2	*kids;
	BOOL						retval;
	short						halfScreenW=vp->width>>1;
	short						halfScreenH=vp->height>>1;
	int						cameraAngle;

	cont->renderFlags|=RENDER_FLAGS_CLIPPED;

	if(cont->type & TYPE_MESH)
	{
		switch(cont->type)
		{

			case	TYPE_HMD:
			{
				MATRIX					mat;
				GsCOORDINATE2			coord;
				short						coords[3];
				long						depth=14,flag;
				SVECTOR					vector;

				LPDIRECT3DRMMESH		mesh = (LPDIRECT3DRMMESH)cont->modelData;

				if (cont->Hidden==TRUE)		/* don't display hidden meshes */
					break;


				GsInitCoordinate2(WORLD, &coord);
				GsGetLs(&coord, &mat);
				GsSetLsMatrix(&mat);

	
				vector.vx=-cont->coords.pos.vx;
				vector.vy=cont->coords.pos.vz;
				vector.vz=cont->coords.pos.vy;

				RotTransPers(&vector,(long*)&coords[0],&depth,&flag);
				cont->transX=coords[0];
				cont->transY=coords[1];

				if (coords[0]<-(halfScreenW+cont->clipSize) || coords[0]>(halfScreenW+cont->clipSize) || coords[1]<-(halfScreenH+cont->clipSize) || coords[1]>(halfScreenH+cont->clipSize))
					break;


					
				G3D_IntVector(&pos, &cont->coords.pos);
				G3D_IntSVector(&rot, &cont->coords.rot);
				RotMatrix_gte(&rot, &cont->coords.coord.matrix);
				TransMatrix(&cont->coords.coord.matrix, &pos);
				cont->coords.coord.flg = NULL;
				GsGetLwsUnit(&cont->coords.coord, &matLW, &matLS);
				GsSetLightMatrix(&matLW);
				GsSetLsMatrix(&matLS);

				viewportGlobs.models_drawn++;
				HMD_AddModel(mesh->model, &gfxGlobs.Wot[gfxGlobs.bufID]);
				cont->renderFlags&=~RENDER_FLAGS_CLIPPED;

				break;
			}

			case	TYPE_PMD:
					break;

			case	TYPE_RMD:
					break;

			case	TYPE_SMD:
					break;

		}
	}
	else
	{

		switch(cont->type)
		{
			case	TYPE_DECAL:			/* sprites */
			{
				GsCOORDINATE2			coord;
				MATRIX					mat;
				short						coords[3];
				long						depth=14,flag;
				SVECTOR					vector;
				int						z;
				VECTOR3D					pos;
				VECTOR3D					rot;
				SPRITE_SET				*set=(SPRITE_SET*) cont->modelData;
				lpSPRITE_ANIM_DATA	sad=(SPRITE_ANIM_DATA*) cont->userData;
				int						frame_num,frame,rotation;
				int						clipBottom;


				if (cont->Hidden==TRUE)
					break;

				GsInitCoordinate2(WORLD, &coord);
				GsGetLs(&coord, &mat);
				GsSetLsMatrix(&mat);

				Container_GetPosition(cont,&pos);
				Container_GetRotation(cont,&rot);
	
				vector.vx=-pos.x;
				vector.vy=pos.z;
				vector.vz=pos.y;

				if (cont->renderFlags & RENDER_FLAGS_CLIP_BOTTOM)
				{
					vector.vy+=32;
					clipBottom=6;
				}
				else
					clipBottom=0;


				z=RotTransPers(&vector,(long*)&coords[0],&depth,&flag);

				cont->transX=coords[0];
				cont->transY=coords[1];

				if (coords[0]<-(halfScreenW+cont->clipSize) || coords[0]>(halfScreenW+cont->clipSize) || coords[1]<-(halfScreenH+cont->clipSize) || coords[1]>(halfScreenH+cont->clipSize))
					break;


				frame=set->frame_sequence[sad->animIndex];
				cameraAngle=vp->camera_container->coords.rot.vy;
				rotation=(Image_GetDirection(set,rot.y+cameraAngle));

				if (rotation>=set->continuous)
				{
					frame+=(set->frames_per_direction>>1);
					if (frame>=set->frames_per_direction)
						frame-=set->frames_per_direction;
				}
				frame_num=(rotation*set->frames_per_direction)+frame;
				Image_DisplaySpriteIndex(set, frame_num, coords[0], coords[1], cont->scale,z, sad->clutIndex, sad->brightness,clipBottom);
				viewportGlobs.sprites_drawn++;
				cont->renderFlags&=~RENDER_FLAGS_CLIPPED;
				break;
			}

			case	TYPE_FLOOR_DECAL:			/* floor aligned quad */
			{
				SPRITE_SET				*set=(SPRITE_SET*) cont->modelData;
				lpSPRITE_ANIM_DATA	sad=(SPRITE_ANIM_DATA*) cont->userData;
				int						frame;

				frame=set->frame_sequence[sad->animIndex];

				if (Image_DisplayFloorSpriteIndex(set,frame,cont))		/* returns whether it was drawn or not */
				{
					viewportGlobs.sprites_drawn++;
					cont->renderFlags&=~RENDER_FLAGS_CLIPPED;
				}
				break;
			}

			case	TYPE_INTERNAL_DECAL:
			{
				if (cont->renderCallback)
					cont->renderCallback(cont);
			}

			case	TYPE_LIGHT:
				break;
		}
	}

//	if ((cont->next))
//		Viewport_RenderFrame(vp,(lpContainer)cont->next);

/*
	if (cont->numChildren && (cont->Hidden==FALSE))
	{
		for(i=0; i<cont->numChildren; i++)
		{
			PushMatrix();
			Viewport_RenderFrame(vp,(lpContainer)cont->children[i]);
			PopMatrix();
		}
	}
*/

	return OK;
}



/*
	removed drawing to another routine, removed recursion, since we don't use children at present.
	Caused stack corruption problems, since stack usage would be very large for recursion of 100+ levels
	of the local storage needed by renderObject.

	Some recursion will be needed if any form of object hierarchy is used. (it isn't at present) 
*/
BOOL	Viewport_RenderFrame(lpViewport vp, lpContainer cont)
{
	while (cont)
	{

		Viewport_RenderObject(vp,cont);
		cont=cont->next;
	}

	return	TRUE;
}




// removed from renderframe

//		case	TYPE_TMD:
//		{
//			GsDOBJ2				dobj;
//			LPDIRECT3DRMMESH	mesh = (LPDIRECT3DRMMESH)cont->modelData;
//			lpTMDhead			tmd = (lpTMDhead)mesh->model;
//			lpTMDobj				obj = (lpTMDobj)&tmd[1];
//
//			G3D_IntVector(&pos, &cont->coords.pos);
//			G3D_IntSVector(&rot, &cont->coords.rot);
//			RotMatrix_gte(&rot, &cont->coords.coord.coord);
//			TransMatrix(&cont->coords.coord.coord, &pos);
//			cont->coords.coord.flg = NULL;
//			GsGetLws(&cont->coords.coord, &matLW, &matLS);
//			GsSetLightMatrix(&matLW);
//			GsSetLsMatrix(&matLS);
//
//			GsLinkObject4((Uint32)obj, &dobj, 0);
//			dobj.coord2 = &mesh->coords->coord;
//			dobj.attribute = GsDIV2;
//			GsSortObject4(&dobj, &gfxGlobs.Wot[gfxGlobs.bufID], 0, DCACHE);
//			break;
//		}



