//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Image File For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson

// added by SteveD:
// 	sprite support
//
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

// Include all Header Files

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
#include	"libgods.h"
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

Image_Globs	imageGlobs;


void Image_Initialise(void)
{
	ULONG loop;

	for (loop=0 ; loop<IMAGE_MAXLISTS ; loop++)
	{
		imageGlobs.listSet[loop] = NULL;
	}

	// Global Initialisation here...

	Image_InitialiseQuadPool();

	imageGlobs.flags = IMAGE_FLAG_INITIALISED;
}

LPVOID	Image_LoadTIM(LPUCHAR name)
{
	LPUCHAR		buffer;
	TIM_IMAGE	tim;
	Uint32		size, mult;
	lpImage		newImage;

	if(buffer = File_LoadBinary(name, &size))
	{
		OpenTIM((Uint32*)buffer);
		ReadTIM(&tim);

		switch(tim.mode & 7)
		{
			case	0:
					mult = 4;
					break;
			case	1:
					mult = 2;
					break;

			default:
					mult = 1;
					break;
		}
		LoadImage(tim.crect, tim.caddr);
		LoadImage(tim.prect, tim.paddr);

		if(newImage = Image_Create(&tim, mult))
		{
			RELEASE(buffer);
			return newImage;
		}
	}
	RELEASE(buffer);
	return NULL;
}

lpImage	Image_Next(void)
{
	lpImage	newImage;
	if(!imageGlobs.freeList) Image_AddList();

	newImage = imageGlobs.freeList;
	imageGlobs.freeList = newImage->nextFree;
	newImage->nextFree = newImage;
	newImage->flags = NULL;

	return newImage;
}

lpImage	Image_Clone(lpImage img)
{
	lpImage	newImage;

	newImage = Image_Next();
	newImage->width = img->width;
	newImage->height = img->height;
	newImage->u = img->u;
	newImage->v = img->v;
	newImage->attribute = img->attribute;
	newImage->tPage = img->tPage;
	newImage->cx = img->cx;
	newImage->cy = img->cy;
	return newImage;
}

lpImage	Image_Create(lpTIM_IMAGE tim, Uint32 m)
{
	lpImage	newImage;
	Uint16	tp;

	newImage = Image_Next();
	newImage->width = tim->prect->w*m;
	newImage->height = tim->prect->h;
	newImage->u = (tim->prect->x & 0x3f)*m;
	newImage->v = (tim->prect->y & 0xff);
	switch(m)
	{
		case	1:
				tp = 0x100;
				newImage->attribute = 0x02000000;
				break;

		case	2:
				tp = 0x080;
				newImage->attribute = 0x01000000;
				break;

		case	4:
				tp = NULL;
				newImage->attribute = 0x00000000;
				break;
	}

	newImage->tPage = (tim->prect->x/64)+((tim->prect->y>>8)<<4)+tp;
	newImage->cx = tim->crect->x;
	newImage->cy = tim->crect->y;
	return newImage;
}

void	Image_AddList(void)
{
	lpImage	list;
	Uint32	loop, count;

	count = 0x00000001 << imageGlobs.listCount;

	if(list = imageGlobs.listSet[imageGlobs.listCount] = Mem_Malloc(sizeof(Image)*count))
	{
		imageGlobs.listCount++;
		for(loop=1; loop<count; loop++)
		{
			list[loop-1].nextFree = &list[loop];
		}
		list[count-1].nextFree = imageGlobs.freeList;
		imageGlobs.freeList = list;
	}
}

void	Image_Display(lpImage image, LPVECTOR2D destPos)
{
	GsSPRITE	s;

	if (!image)
		return;		/* nothing to display */

	s.r = s.g = s.b = gfxGlobs.fadeLevel;
	s.x = 0-(gfxGlobs.scrW>>1);
	s.y = 0-(gfxGlobs.scrH>>1);
	s.u = image->u;
	s.v = image->v;

	if (image->width <= 256)
		s.w = image->width;
	else
		s.w = 256;

	s.h = image->height;
	s.tpage = image->tPage;
	s.cx = image->cx;
	s.cy = image->cy;
	s.mx = s.my = s.rotate = NULL;
	s.scalex = s.scaley = ONE;
	s.attribute = image->attribute;

	if(destPos)
	{
		s.x += destPos->x;
		s.y += destPos->y;
	}

	GsSortFastSprite(&s, &gfxGlobs.Wot[gfxGlobs.bufID], 10);
	if (image->width >256)
	{
		s.x += 256;
		s.w = image->width-256;
		if (!(s.attribute & 0x03000000))
			s.tpage++;
		else if ((s.attribute & 0x03000000)==0x01000000)
			s.tpage+=2;
		else if ((s.attribute & 0x03000000)==0x02000000)
			s.tpage+=4;
		GsSortFastSprite(&s, &gfxGlobs.Wot[gfxGlobs.bufID], 10);
	}
}


VOID Image_SetupTrans(lpImage image, REAL lowr, REAL lowg, REAL lowb, REAL highr, REAL highg, REAL highb)
{
}


void	Image_Remove(lpImage image)
{
	/* scan for the image in the list */

}





/*
	------------------------------------------------------------------

		New sprite stuff

	------------------------------------------------------------------
*/


/*

	load a sprite sequence from a .TIM file
	frames should be stored in row order, ie:

		direction0 frame0 frame1 ... frameN
		direction1 frame0 frame1 ... frameN
		...
		directionN frame0 frame1 ... frameN

	directions can span more than one row if necessary.

	reverse_frames controls the generation of flipped frame data

*/



/*
	create a structure for a sprite activity set 
*/
BOOL	Image_ActivitySetCreate(lpSPR_ACTIVITY_SET *activitySet)
{
	lpSPR_ACTIVITY_SET newActivitySet;
	
	if ((newActivitySet=(SPR_ACTIVITY_SET*) Mem_Malloc(sizeof(SPR_ACTIVITY_SET))))
	{
		memset(newActivitySet,0,sizeof(SPR_ACTIVITY_SET));
		*activitySet=newActivitySet;
		return	TRUE;
	}
	return	FALSE;
}


/*
	load a sprite sequence in to an anim sequence
	returns the index that the sequence was loaded to, or -1 if it fails
*/
int	Image_LoadToActivitySet(lpSPR_ACTIVITY_SET activitySet, char *fname, char *activityName, int directions, int per_direction, int width, int height, int x_offset, int y_offset, BOOL reverse_frames, char *start_frame_list, char *loop_frame_list, int delay)
{
	lpSPRITE_SET	newSet;

	if ((newSet=Image_LoadSpriteSequence(fname,directions,per_direction,width,height,x_offset,y_offset,reverse_frames,start_frame_list,loop_frame_list, delay)))
	{
		strcpy(newSet->name,activityName);

		return	Image_AddToActivitySet(activitySet,newSet);
	}
	return	-1;
}

/*
	adds an existing sprite sequence to an ACTIVITY_SET
	returns	index to added sequence, -1 if it fails
*/
int	Image_AddToActivitySet(lpSPR_ACTIVITY_SET activitySet, lpSPRITE_SET spriteSet)
{
	if (activitySet->num_anim_seqs<MAX_ANIMSEQS)
	{
		activitySet->seq_list[activitySet->num_anim_seqs++]=spriteSet;
		return  activitySet->num_anim_seqs-1;
	}
	return	-1;
}





/*
	takes a string containing frame numbers separated by commas
	and returns	an array of bytes, and the length of the array
*/
BOOL	parse_frame_list(char	*frame_list, char *frame_sequence, int *num_frames)
{
	int	num_found=0,next_frame,n;
	int	digit_index=0;
	char	num_string[4];

	for (n=0; n<strlen(frame_list); n++)
	{

		if (frame_list[n]==',')
		{
			num_string[digit_index]=0;
			next_frame=atoi(num_string);
			*frame_sequence++=next_frame;
			digit_index=0;
			num_found++;
		}
		else
		{
			if (frame_list[n]>='0' && frame_list[n]<='9')
			{
				num_string[digit_index++]=frame_list[n];
			}
			else		/* illegal character */
			{
				digit_index=0;
				num_found=0;
				break;				/* signal error */
			}
		}
	}

/* should always be a frame number to convert at the end of the loop */

	if (digit_index>0)
	{
			num_string[digit_index]=0;
			next_frame=atoi(num_string);
			*frame_sequence++=next_frame;
			num_found++;
	}

	*num_frames=num_found;	

	if (num_found==0)
		return	FALSE;		/* bad frame list string */

	return	TRUE;

}



/* generate frame list data here */
Image_CreateFrameLists(SPRITE_SET *newSprSet, char *start_frame_list, char* loop_frame_list)
{
	Uint8		temp_start_frame_list[64];
	Uint8		temp_loop_frame_list[64];
	Uint8		*temp_ptr;
	int		start_length=0;
	int		loop_length=0,n;


/* start sequence */

	if (strcmp(start_frame_list,"NONE")!=0)
	{
		if ((parse_frame_list(start_frame_list,temp_start_frame_list,&start_length)))
		{
			/* error in sequence */
		}
	}

/* loop sequence */

	if (strcmp(loop_frame_list,"DEFAULT")==0)
	{
		/* no sequence required, generate 0-per_direction list */

		for (n=0; n<newSprSet->frames_per_direction; n++)
			temp_loop_frame_list[n]=n;
		loop_length=newSprSet->frames_per_direction;
	}
	else
	{
		if ((parse_frame_list(loop_frame_list,temp_loop_frame_list,&loop_length)))
		{
				/* error in sequence */
		}
	}

/* now we construct the final list and index data */

		
	newSprSet->frame_sequence=Mem_Malloc(start_length+loop_length);
	newSprSet->start_seq_len=start_length;
	newSprSet->loop_seq_len=loop_length+start_length;

	temp_ptr=newSprSet->frame_sequence;

	for (n=0; n<start_length; n++)
		*temp_ptr++=temp_start_frame_list[n];

	for (n=0; n<loop_length; n++)
		*temp_ptr++=temp_loop_frame_list[n];
}



/*
	clone a sprite activity [graphically], but pass new frame lists
	now clones from a passed activity name

*/
int	Image_CloneToActivitySet(lpSPR_ACTIVITY_SET activitySet, char *activityName, char *cloneFromName, char *start_frame_list, char *loop_frame_list, int delay)
{
	SPRITE_SET	*newSprSet;
	SPRITE_SET	*cloneFrom;
	int			n;

	if (activitySet->num_anim_seqs<MAX_ANIMSEQS)		/* only if there is room for another */
	{

	/* find activity to clone from */

		for (n=0; n<activitySet->num_anim_seqs; n++)
		{
			cloneFrom=activitySet->seq_list[n];

			if (stricmp(cloneFromName,cloneFrom->name)==0)
			{
				if (!(newSprSet=(SPRITE_SET*) Mem_Malloc(sizeof(SPRITE_SET))))
					return	-1;
				activitySet->seq_list[activitySet->num_anim_seqs++]=newSprSet;

			/* clone activity data */

				memcpy(newSprSet,cloneFrom,sizeof(SPRITE_SET));
				newSprSet->anim_delay=delay;
				strcpy(newSprSet->name,activityName);
				Image_CreateFrameLists(newSprSet,start_frame_list,loop_frame_list);

				return  activitySet->num_anim_seqs-1;
			}
		}
	}
	return	-1;		/* activity set is full, contact your local software engineer */
}




/*

	start_frame_list is a string of frame numbers, denoting the play order.
	if the string == 'NONE' then there is no start sequence

loop_frame_list
	if the string == 'DEFAULT' then a frame order of 0-num frames is generated
*/
SPRITE_SET*	Image_LoadSpriteSequence(char *fname,int directions, int per_direction, int width, int height, int x_offset, int y_offset, BOOL reverse_frames, char *start_frame_list, char *loop_frame_list, int delay)
{
 	LPUCHAR		buffer;
	TIM_IMAGE	tim;
	Uint32		size;
	SPRITE_SET	*new_spr_set;
	SPR_FRAME	*new_sprite_frame,*flip_frame_src;
	int			normal_directions,flipped_directions;
	int			x,y,yr;
	int			rows_per_direction,row_length;
	int			colour_mult;
	int			tpage_offset_x,tpage_offset_y;
	int			make_continuous=FALSE;

	if (strcmp(loop_frame_list,"DEFAULT")==0)
		make_continuous=TRUE;

	if(buffer = File_LoadBinary(fname, &size))
	{
		OpenTIM((Uint32*)buffer);
		ReadTIM(&tim);

		LoadImage(tim.crect, tim.caddr);
		LoadImage(tim.prect, tim.paddr);

		DrawSync(0);

		if (!(new_spr_set=(SPRITE_SET*) Mem_Malloc(sizeof(SPRITE_SET))))
		{
			RELEASE(buffer);
			return	NULL;
		}

		if (!(new_sprite_frame=(SPR_FRAME*) Mem_Malloc(sizeof(SPR_FRAME)*directions*per_direction)))
		{
			RELEASE(new_spr_set);
			RELEASE(buffer);
			return	NULL;
		}


	/* initialise header */

		new_spr_set->frames=new_sprite_frame;
		new_spr_set->num_directions=directions;
		new_spr_set->direction_div=4096/directions;
		new_spr_set->num_frames=directions*per_direction;
		new_spr_set->frames_per_direction=per_direction;
		new_spr_set->cx=tim.crect->x;
		new_spr_set->cy=tim.crect->y;
		new_spr_set->off_x=x_offset;
		new_spr_set->off_y=y_offset;
		new_spr_set->tpage=getTPage((tim.mode & 7),0,tim.prect->x,tim.prect->y);
		new_spr_set->anim_delay=delay;
		new_spr_set->continuous=255;

		tpage_offset_x=tim.prect->x & 63;
		tpage_offset_y=tim.prect->y & 255;

	/* initialise normal frame data */

		normal_directions=directions;
		flipped_directions=0;
		if (reverse_frames && directions>2)
		{
			normal_directions>>=1;
			normal_directions++;
			flipped_directions=directions-normal_directions;
			if (make_continuous)
				new_spr_set->continuous=normal_directions;
		}

		if ((tim.mode&7)==0)
			colour_mult=4;
		else
			colour_mult=2;

		tpage_offset_x*=colour_mult;
		rows_per_direction=(per_direction*width)/(colour_mult*tim.prect->w);

		if (rows_per_direction>1)
			row_length=(colour_mult*tim.prect->w)/width;
		else
			row_length=per_direction;

		for (y=0; y<normal_directions; y++)
		{
			for (yr=0; yr<rows_per_direction; yr++)
			{
				for (x=0; x<row_length; x++)
				{
					new_sprite_frame->w=width;
					new_sprite_frame->h=height;
					new_sprite_frame->u=(x*width)+tpage_offset_x;
					new_sprite_frame->v=(((y*rows_per_direction)+yr)*height)+tpage_offset_y;
					new_sprite_frame++;
				}
			}
		}

		if (flipped_directions)
		{
			/* generate flipped frame data */

			flip_frame_src=new_sprite_frame-(2*per_direction);

			for (y=0; y<flipped_directions; y++)
			{
				for (x=0; x<per_direction; x++)
				{
					new_sprite_frame->w=-flip_frame_src->w;
					new_sprite_frame->h=flip_frame_src->h;
					new_sprite_frame->u=flip_frame_src->u;
					new_sprite_frame->v=flip_frame_src->v;
					new_sprite_frame++;
					flip_frame_src++;
				}
				flip_frame_src-=(2*per_direction);
			}
		}
		
		Image_CreateFrameLists(new_spr_set,start_frame_list,loop_frame_list);


		RELEASE(buffer);
		return	new_spr_set;
	}
	return	NULL;
}



/*
	return a base frame number for the direction based on angle
*/
int	Image_GetDirection(SPRITE_SET *set, int angle)
{
	int	div;

	angle+=(2048+(set->direction_div>>1));		/* offset for frames being 180 degrees out + allowance for spanning */
	angle&=4095;
	angle/=set->direction_div;
	return	angle;
}


BOOL	Image_DisplaySprite(SPRITE_SET *set, int direction, int frame, int x, int y, int scale, int order, Uint8 clutIndex, Uint8 brightness, int clipBottom)
{
	return	Image_DisplaySpriteIndex(set,(direction*set->frames_per_direction)+frame,x,y,scale,order,clutIndex, brightness, clipBottom);
}

/*
	display a sprite, uh duh.
	all assumed to be 16 colour at present

*/
BOOL	Image_DisplaySpriteIndex(SPRITE_SET *set, int frame_offset, int x, int y, int scale, int order, Uint8 clutIndex, Uint8 brightness, int clipBottom)
{
	GsSPRITE		s;
	SPR_FRAME	*seq_frame;

	static		unsigned long attr=0x00000000;
	static		unsigned short tpage_attr=0;

	if (set)
	{
		seq_frame=set->frames;
		seq_frame+=frame_offset;

		s.x=x+FromFIXED( Asm_MulFIX(scale,ToFIXED(set->off_x) ) );
		s.y=y+FromFIXED( Asm_MulFIX(scale,ToFIXED(set->off_y) ) );
		s.u=seq_frame->u;
		s.v=seq_frame->v;

		s.r=s.g=s.b=brightness;

		s.tpage=set->tpage;

		s.tpage|=tpage_attr;

		s.cx=set->cx;
		s.cy=set->cy+clutIndex;
		s.h=seq_frame->h;

		if (seq_frame->w<0)		/* flipped sprite */
		{
			s.attribute=0x00800000;

			s.attribute|=attr;

			s.w=-seq_frame->w;
			s.mx=s.my=0;
			s.scalex=s.scaley=scale;
			s.rotate=0;
			GsSortSprite(&s, &gfxGlobs.Wot[gfxGlobs.bufID], order);
			return	TRUE;
		}
		else
		{
			s.attribute=0x00000000;

			s.attribute|=attr;

			s.w=seq_frame->w;
			s.mx=s.my=0;
			s.scalex=s.scaley=scale;
			s.rotate=0;
			GsSortSprite(&s, &gfxGlobs.Wot[gfxGlobs.bufID], order);
			return	TRUE;
		}
	}
	return	FALSE;
}



BOOL	Image_DisplayFloorSprite(SPRITE_SET *set, int frame, lpContainer cont)
{
	VECTOR3D	rot;

	Container_GetRotation(cont,&rot);
	
	return	Image_DisplayFloorSpriteIndex(set,(rot.y*set->frames_per_direction)+frame,cont);

}


void	drawCross(int x, int y,int r, int g, int b)
{
  GsLINE   line;

  line.attribute=0;
  line.x0=x-1;
  line.y0=y;
  line.x1=x+1;
  line.y1=y;
  line.r=r;
  line.g=g;
  line.b=b;
  GsSortLine(&line,&gfxGlobs.Wot[gfxGlobs.bufID],0);
  line.x0=x;
  line.y0=y-1;
  line.x1=x;
  line.y1=y+1;
  GsSortLine(&line,&gfxGlobs.Wot[gfxGlobs.bufID],0);
}

/*
	display a floor aligned quad from a container
*/
BOOL	Image_DisplayFloorSpriteIndex(SPRITE_SET *set, int frame_offset, lpContainer cont)
{
	lpSPRITE_ANIM_DATA	sad=(SPRITE_ANIM_DATA*) cont->userData;
	POLY_FT4					*display_quad;
	Uint32				 	*ot=(Uint32*)gfxGlobs.Wot[gfxGlobs.bufID].org;

	GsCOORDINATE2			coord;
	MATRIX					mat;
	short						coords[3];
	long						depth=14,flag;
	SVECTOR					vector;
	int						z;
	VECTOR3D					pos,rot;
	SPR_FRAME				*seq_frame;
	int						width;
	int						dx,dy;	
	REAL						stheta,ctheta;
	int						sizex,sizey;

  GsLINE   				l;
	int						tx[4],ty[4],n;
	REAL						xstheta,xctheta,ystheta,yctheta;

	int						halfScreenW=200;
	int						halfScreenH=136;


	if (cont->Hidden==TRUE)
		return	FALSE;

	if (!(display_quad=Image_GetFreeQuad()))
		return	FALSE;									/* out of quads, whoops. */

	seq_frame=set->frames;
	seq_frame+=frame_offset;

	GsInitCoordinate2(WORLD, &coord);
	GsGetLs(&coord, &mat);
	GsSetLsMatrix(&mat);

	Container_GetPosition(cont,&pos);
	Container_GetRotation(cont,&rot);


	sizex=FromFIXED(Asm_MulFIX((seq_frame->w<<14),cont->scale));
	sizey=FromFIXED(Asm_MulFIX((seq_frame->h<<14),cont->scale));


	stheta=csin(4095-rot.y);
	ctheta=ccos(4095-rot.y);
	dx=FromFIXED((sizex*ctheta)-(sizey*stheta));
	dy=FromFIXED((sizex*stheta)+(sizey*ctheta));
	vector.vx=-pos.x+dx;
	vector.vy=pos.z;
	vector.vz=pos.y+dy;
	z=RotTransPers(&vector,(long*)&coords[0],&depth,&flag);

	if (coords[0]<-(halfScreenW+cont->clipSize) || coords[0]>(halfScreenW+cont->clipSize) || coords[1]<-(halfScreenH+cont->clipSize) || coords[1]>(halfScreenH+cont->clipSize))
		return	FALSE;


	display_quad->x1=coords[0];
	display_quad->y1=coords[1];

	vector.vx=-pos.x-dx;
	vector.vy=pos.z;
	vector.vz=pos.y-dy;
	z=RotTransPers(&vector,(long*)&coords[0],&depth,&flag);
	display_quad->x2=coords[0];
	display_quad->y2=coords[1];

	dx=FromFIXED((sizex*ctheta)-(-sizey*stheta));
	dy=FromFIXED((sizex*stheta)+(-sizey*ctheta));
	vector.vx=-pos.x+dx;
	vector.vy=pos.z;
	vector.vz=pos.y+dy;
	z=RotTransPers(&vector,(long*)&coords[0],&depth,&flag);
	display_quad->x3=coords[0];
	display_quad->y3=coords[1];

	vector.vx=-pos.x-dx;
	vector.vy=pos.z;
	vector.vz=pos.y-dy;
	z=RotTransPers(&vector,(long*)&coords[0],&depth,&flag);
	display_quad->x0=coords[0];
	display_quad->y0=coords[1];


/*
	width is ABS'd here, though sequences using this form of sprite should
	have no rotation
*/
	width=seq_frame->w;
	if (width<0)
		width=-width;
	width-=1;

	display_quad->tpage=set->tpage;
	display_quad->clut=getClut(set->cx,set->cy+sad->clutIndex);
	display_quad->u0=seq_frame->u;
	display_quad->v0=seq_frame->v;
	display_quad->u1=seq_frame->u+width;
	display_quad->v1=seq_frame->v;
	display_quad->u2=seq_frame->u;
	display_quad->v2=seq_frame->v+seq_frame->h-1;
	display_quad->u3=seq_frame->u+width;
	display_quad->v3=seq_frame->v+seq_frame->h-1;
		
	display_quad->r0=display_quad->g0=display_quad->b0=sad->brightness;


//	display_quad->r0=cont->red;
//	display_quad->g0=cont->green;
//	display_quad->b0=cont->blue;

	setSemiTrans(display_quad,0);
	AddPrim(ot+z,display_quad);

	return	TRUE;
}


/*
	quad pool stuff for floor decals
*/
BOOL	Image_InitialiseQuadPool(void)
{
	int	n;

	for (n=0; n<MAX_QUADS; n++)
	{
		SetPolyFT4(&imageGlobs.quadPool.quads[n][0]);
		SetPolyFT4(&imageGlobs.quadPool.quads[n][1]);
	}
	imageGlobs.quadPool.nextQuad=0;

	return	TRUE;
}


/*
	return pointer to quad, or NULL if all used
*/
POLY_FT4*	Image_GetFreeQuad(void)
{
	if (imageGlobs.quadPool.nextQuad==MAX_QUADS)
		return	NULL;

	return	&imageGlobs.quadPool.quads[imageGlobs.quadPool.nextQuad++][GsGetActiveBuff()];
}



void	Image_ResetQuadPool(void)
{
	imageGlobs.quadPool.nextQuad=0;
}
