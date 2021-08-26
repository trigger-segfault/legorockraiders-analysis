// **********************************************************************************************
// Collision File For <GODS PSX>
// **********************************************************************************************

// **********************************************************************************************
#include	"libgods.h"


// **********************************************************************************************
CPoly *ColMap[6];


// **********************************************************************************************
// Select one of six collision maps, based on the direction of a ray or normal vector
int Collision_SelectMap(SVECTOR *dir)
{
	long x,y,z;

	x = dir->vx;
	y = dir->vy;
	z = dir->vz;

	if (x < 0) x = -x;
	if (y < 0) y = -y;
	if (z < 0) z = -z;

	if (y >= x && y >= z)
	{
		if (dir->vy > 0)
			return COLMAP_XZ_FLOOR;
		else
			return COLMAP_XZ_CEIL;
	}
	else if (x >= y && x >= z)
	{
		if (dir->vx > 0)
			return COLMAP_ZY_RIGHT;
		else
			return COLMAP_ZY_LEFT;
	}
	else
	{
		if (dir->vz > 0)
			return COLMAP_XY_LEFT;
		else
			return COLMAP_XY_RIGHT;
	}
}

// **********************************************************************************************
void Collision_Setup(u_long *hmd)
{
	CPoly *cgp,*last=0;
	u_long *ptr,*poly,*bp,*ps;
	int m,i,j,k,p,r,s,blks,verts,types,type,data,map;
	SVECTOR *n[4],*vertex,*normal,*vp,norm;
	long x,y,z;
	long minx,maxx,miny,maxy,minz,maxz;
	float n1vx,n1vy,n1vz;
	float n2vx,n2vy,n2vz;
	float A,B,C,D,len;
	float vx,vy,vz;
	
	long tpage,tw;
	long u[4];
	long v[4];
	
	for (i=0;i<6;i++)
		ColMap[i]=NULL;

	blks=hmd[3]-2;
	bp=&hmd[5];
	
	for (i=0;i<blks;i++)
	{
		ps=(u_long *)(hmd+*bp);
		bp++;
		if (ps>hmd)
		{
			ptr=(u_long *)(hmd+ps[1]);
			poly=(u_long *)(hmd+ptr[1]);
			vertex=(SVECTOR *)(hmd+ptr[2]);
			normal=(SVECTOR *)(hmd+ptr[3]);
			types=ps[2]&0x7FFFFFFF;
			ps+=3;
			for (j=0;j<types;j++)
			{
				type=ps[0]&0xFFFF;
				data=(ps[1]&0x7FFF0000)>>16;
				ptr=(u_long *)(poly+(ps[2]&0x00FFFFFF));
				
				m=(type&0x38)>>3;
				if (m==1) verts=3;
				else if (m==2) verts=4;
				else verts=0;
				
				if (verts)
				{
					for (k=0;k<data;k++)
					{
						cgp=(CPoly *)Mem_Alloc(sizeof(CPoly));
						if (!cgp) printf("Out of memory!!\n");
					//	cgp->next=0;
					//	if (last) last->next=cgp; else CollisionMap=cgp;
					//	last=cgp;
						
						printf("type:%x\n",type);

						switch (type)
						{
							case 0x9:	// Flat Textured Triangle
										ptr+=3;
										m=*ptr++;
										cgp->v[0]=&vertex[(m&0xFFFF0000)>>16];
										m=*ptr++;
										cgp->v[1]=&vertex[(m&0xFFFF)];
										cgp->v[2]=&vertex[(m&0xFFFF0000)>>16];
										break;

							case 0xd:	// Gouraud textured triangle
										ptr+=3;
										for (p=0;p<verts;p++)
										{
											m=*ptr++;
											cgp->v[p]=&vertex[(m&0xFFFF0000)>>16];
											n[p]=&normal[(m&0xFFFF)];
										}
										break;

							case 0x11:	// Flat textured quad
										ptr+=4;
										m=*ptr++;
										cgp->v[0]=&vertex[(m&0xFFFF)];
										cgp->v[1]=&vertex[(m&0xFFFF0000)>>16];
										m=*ptr++;
										cgp->v[2]=&vertex[(m&0xFFFF)];
										cgp->v[3]=&vertex[(m&0xFFFF0000)>>16];
										break;
										
							case 0x14:	// Gouraud quad
						
										ptr++;
										for (p=0;p<verts;p++)
										{
											m=*ptr++;
											cgp->v[p]=&vertex[(m&0xFFFF0000)>>16];
											n[p]=&normal[(m&0xFFFF)];
										}
										break;
										
							case 0x15:	// Gouraud textured quad
					
										ptr+=3;
										m=*ptr++;
										n[0]=&normal[(m&0xFFFF0000)>>16];
										m=*ptr++;
										cgp->v[0]=&vertex[(m&0xFFFF0000)>>16];
										for (p=0;p<verts-1;p++)
										{
											m=*ptr++;
											cgp->v[p+1]=&vertex[(m&0xFFFF0000)>>16];
											n[p+1]=&normal[(m&0xFFFF)];
										}
										break;
									
							case 0x20d:	// Tiled Gouraud textured triangle
							
										tw=*ptr++;
									
										for(p=0;p<verts;p++)
										{
											m=*ptr++;
											if (p==1) tpage=m>>16;
											u[p]=m&0x00FF;
											v[p]=(m&0xFF00)>>8;
										}
										
										for (p=0;p<verts;p++)
										{
											m=*ptr++;
											cgp->v[p]=&vertex[(m&0xFFFF0000)>>16];
											n[p]=&normal[(m&0xFFFF)];
										}
										break;
									
							case 0x215:	// Tiled Gouraud textured quad
							
										tw=*ptr++;
									
										for(p=0;p<verts;p++)
										{
											m=*ptr++;
											if (p==1) tpage=m>>16;
											u[p]=m&0x00FF;
											v[p]=(m&0xFF00)>>8;
										}
										ptr-=2;
										
										m=*ptr++;
										n[0]=&normal[(m&0xFFFF0000)>>16];
										m=*ptr++;
										cgp->v[0]=&vertex[(m&0xFFFF0000)>>16];
										for (p=0;p<verts-1;p++)
										{
											m=*ptr++;
											cgp->v[p+1]=&vertex[(m&0xFFFF0000)>>16];
											n[p+1]=&normal[(m&0xFFFF)];
										}
										break;
									
							default:	printf("Pre-process: Cannot handle type %d\n",type);
						}
					
						// If its a quad, swap the last two vertices so they are in the correct order
						if (verts==4) vp=cgp->v[3],cgp->v[3]=cgp->v[2],cgp->v[2]=vp;
					
						// Calculate plane co-efficients (Newell's method - Graphics Gems 3)
						
						A=B=C=0;
						for (i=0;i<verts;i++)
						{
							r=i+1;
							if (r==verts) r=0;
							s=r+1;
							if (s==verts) s=0;
							
							n1vx=(cgp->v[r]->vx - cgp->v[i]->vx)/(float)ONE;
							n1vy=(cgp->v[r]->vy - cgp->v[i]->vy)/(float)ONE;
							n1vz=(cgp->v[r]->vz - cgp->v[i]->vz)/(float)ONE;
						
							n2vx=(cgp->v[s]->vx - cgp->v[i]->vx)/(float)ONE;
							n2vy=(cgp->v[s]->vy - cgp->v[i]->vy)/(float)ONE;
							n2vz=(cgp->v[s]->vz - cgp->v[i]->vz)/(float)ONE;
						
							A+=(n1vy*n2vz) - (n2vy*n1vz);
							B+=(n1vz*n2vx) - (n2vz*n1vx);
							C+=(n1vx*n2vy) - (n2vx*n1vy);
						}
						
						len=(A*A) + (B*B) + (C*C);
						len=1/sqrt(len);
						
						A*=len;
						B*=len;
						C*=len;
						
						vx=cgp->v[0]->vx/(float)ONE;
						vy=cgp->v[0]->vy/(float)ONE;
						vz=cgp->v[0]->vz/(float)ONE;
						
						D=-((A*vx) + (B*vy) + (C*vz));

						if (verts==3) cgp->v[3]=0;
						cgp->normal.vx=A*ONE;
						cgp->normal.vy=B*ONE;
						cgp->normal.vz=C*ONE;
						cgp->D=D*ONE;

						// Select collision map
						norm.vx = -cgp->normal.vx;
						norm.vy = -cgp->normal.vy;
						norm.vz = -cgp->normal.vz;
						map = Collision_SelectMap(&norm);
						printf("norm: %d %d %d   map:%d\n",cgp->normal.vx,cgp->normal.vy,cgp->normal.vz,map);
						cgp->next = ColMap[map];
						ColMap[map] = cgp;

						// Calculate bounding rectangle
						minx=miny=minz=0x0FFFFFFF,maxx=maxy=maxz=-0x0FFFFFFF;

						for (i=0;i<verts;i++)
						{
							x=cgp->v[i]->vx;
							y=cgp->v[i]->vy;
							z=cgp->v[i]->vz;
							if (x<minx) minx=x;
							if (x>maxx) maxx=x;
							if (y<miny) miny=y;
							if (y>maxy) maxy=y;
							if (z<minz) minz=z;
							if (z>maxz) maxz=z;
						}
						
						// Set rectangle extents
						if (map == COLMAP_XZ_FLOOR || map == COLMAP_XZ_CEIL)
						{
							cgp->min1 = minx;
							cgp->min2 = minz;
							cgp->max1 = maxx;
							cgp->max2 = maxz;
						}
						else if (map == COLMAP_ZY_LEFT || map == COLMAP_ZY_RIGHT)
						{
							cgp->min1 = minz;
							cgp->min2 = miny;
							cgp->max1 = maxz;
							cgp->max2 = maxy;
						}
						else
						{
							cgp->min1 = minx;
							cgp->min2 = miny;
							cgp->max1 = maxx;
							cgp->max2 = maxy;
						}
/*
						cgp->minx=minx;
						cgp->maxx=maxx;
						cgp->miny=miny;
						cgp->maxy=maxy;
						cgp->minz=minz;
						cgp->maxz=maxz;

						*/
					}
				}
				ps+=3;
			}
		}
	}
}

// **********************************************************************************************
u_long Collision_TestXZ(VECTOR *pos,long *height,SVECTOR **normal,int map)
{
	int i,j,verts;
	CPoly *poly;
	long x,y,z,jx,jz;
	long d;
	VECTOR n1,n2;
	long tx,ty,tz;
	
	x=pos->vx;
	y=pos->vy;
	z=pos->vz;
	
	poly=ColMap[COLMAP_XZ_CEIL + map];
	
	while(poly)
	{
	/*	printf("v0: %d %d %d\n",poly->v[0]->vx,poly->v[0]->vy,poly->v[0]->vz);
		printf("v1: %d %d %d\n",poly->v[1]->vx,poly->v[1]->vy,poly->v[1]->vz);
		printf("v2: %d %d %d\n",poly->v[2]->vx,poly->v[2]->vy,poly->v[2]->vz);
		printf("v3: %d %d %d\n",poly->v[3]->vx,poly->v[3]->vy,poly->v[3]->vz);
		printf("n: %d %d %d\n",poly->normal.vx,poly->normal.vy,poly->normal.vz);
		printf("box: %d %d %d %d\n",poly->min1,poly->max1,poly->min2,poly->max2);
		printf("D: %d\n",poly->D);*/

		// Simple bounding rectangle rejection
		if (x<poly->min1) goto next;
		if (x>poly->max1) goto next;
		if (z<poly->min2) goto next;
		if (z>poly->max2) goto next;	
			
		// Polygon boundry check and reject.
		if (poly->v[3]) verts=4,j=3; 
		else verts=3,j=2;
	
		for (i=0;i<verts;i++)
		{
			jx=poly->v[j]->vx;
			jz=poly->v[j]->vz;
			
			n1.vx=poly->v[i]->vx-jx;
			n1.vz=poly->v[i]->vz-jz;
			
			n2.vx=x-jx;
			n2.vz=z-jz;
		
			d=((n1.vx*n2.vz)>>12)-((n1.vz*n2.vx)>>12);
			if ((d>0 && !map) || (d<0 && map)) goto next;
			
			j++;
			if (j==verts) j=0;
		}
		
		// At this stage the point is definately above this polygon, so find the
		// exact intersection on the plane.
	
		tx=(poly->normal.vx*x)>>12;
		tz=(poly->normal.vz*z)>>12;
		ty=-(tx+tz+poly->D);
		ty=(ty<<12)/poly->normal.vy;
		
		printf("y:%d\n",ty);
		*height=ty;
		*normal=&poly->normal;
		return 1;
next:
		poly=poly->next;
	}
	return 0;
}

// **********************************************************************************************
u_long Collision_TestXY(VECTOR *pos,long *height,SVECTOR **normal,int map)
{
	int i,j,verts;
	CPoly *poly;
	long x,y,z,jx,jy;
	long d;
	VECTOR n1,n2;
	long tx,ty,tz;
	
	x=pos->vx;
	y=pos->vy;
	z=pos->vz;
	
	poly=ColMap[COLMAP_XY_LEFT + map];
	
	while(poly)
	{
	/*	printf("v0: %d %d %d\n",poly->v[0]->vx,poly->v[0]->vy,poly->v[0]->vz);
		printf("v1: %d %d %d\n",poly->v[1]->vx,poly->v[1]->vy,poly->v[1]->vz);
		printf("v2: %d %d %d\n",poly->v[2]->vx,poly->v[2]->vy,poly->v[2]->vz);
		printf("v3: %d %d %d\n",poly->v[3]->vx,poly->v[3]->vy,poly->v[3]->vz);
		printf("n: %d %d %d\n",poly->normal.vx,poly->normal.vy,poly->normal.vz);
		printf("box: %d %d %d %d\n",poly->min1,poly->max1,poly->min2,poly->max2);
		printf("D: %d\n",poly->D);*/

		// Simple bounding rectangle rejection
		if (x<poly->min1) goto next;
		if (x>poly->max1) goto next;
		if (y<poly->min2) goto next;
		if (y>poly->max2) goto next;	
			
	//	printf("done rect\n");

		// Polygon boundry check and reject.
		if (poly->v[3]) verts=4,j=3; 
		else verts=3,j=2;
	
		for (i=0;i<verts;i++)
		{
			jx=poly->v[j]->vx;
			jy=poly->v[j]->vy;
			
			n1.vx=poly->v[i]->vx-jx;
			n1.vy=poly->v[i]->vy-jy;
			
			n2.vx=x-jx;
			n2.vy=y-jy;
		
			d=((n1.vx*n2.vy)>>12)-((n1.vy*n2.vx)>>12);
			if ((d>0 && !map) || (d<0 && map)) goto next;
			
			j++;
			if (j==verts) j=0;
		}
		
//		printf("done boundry\n");

		// At this stage the point is definately above this polygon, so find the
		// exact intersection on the plane.
	
		tx=(poly->normal.vx*x)>>12;
		ty=(poly->normal.vy*y)>>12;
		tz=-(tx+ty+poly->D);
		tz=(tz<<12)/poly->normal.vz;
		
		printf("z:%d\n",tz);
		*height=tz;
		*normal=&poly->normal;
		return 1;
next:
		poly=poly->next;
	}
	return 0;
}

// **********************************************************************************************
u_long Collision_TestZY(VECTOR *pos,long *height,SVECTOR **normal,int map)
{
	int i,j,verts;
	CPoly *poly;
	long x,y,z,jz,jy;
	long d;
	VECTOR n1,n2;
	long tx,ty,tz;
	
	x=pos->vx;
	y=pos->vy;
	z=pos->vz;
	
	poly=ColMap[COLMAP_ZY_LEFT + map];
	
	while(poly)
	{
	/*	printf("v0: %d %d %d\n",poly->v[0]->vx,poly->v[0]->vy,poly->v[0]->vz);
		printf("v1: %d %d %d\n",poly->v[1]->vx,poly->v[1]->vy,poly->v[1]->vz);
		printf("v2: %d %d %d\n",poly->v[2]->vx,poly->v[2]->vy,poly->v[2]->vz);
		printf("v3: %d %d %d\n",poly->v[3]->vx,poly->v[3]->vy,poly->v[3]->vz);
		printf("n: %d %d %d\n",poly->normal.vx,poly->normal.vy,poly->normal.vz);
		printf("box: %d %d %d %d\n",poly->min1,poly->max1,poly->min2,poly->max2);
		printf("D: %d\n",poly->D);*/

		// Simple bounding rectangle rejection
		if (z<poly->min1) goto next;
		if (z>poly->max1) goto next;
		if (y<poly->min2) goto next;
		if (y>poly->max2) goto next;	
			
//		printf("done rect\n");

		// Polygon boundry check and reject.
		if (poly->v[3]) verts=4,j=3; 
		else verts=3,j=2;
	
		for (i=0;i<verts;i++)
		{
			jz=poly->v[j]->vz;
			jy=poly->v[j]->vy;
			
			n1.vz=poly->v[i]->vz-jz;
			n1.vy=poly->v[i]->vy-jy;
			
			n2.vz=z-jz;
			n2.vy=y-jy;
		
			d=((n1.vz*n2.vy)>>12)-((n1.vy*n2.vz)>>12);
			if ((d>0 && map) || (d<0 && !map)) goto next;
			
			j++;
			if (j==verts) j=0;
		}
		
//		printf("done boundry\n");

		// At this stage the point is definately above this polygon, so find the
		// exact intersection on the plane.
	
		tz=(poly->normal.vz*z)>>12;
		ty=(poly->normal.vy*y)>>12;
		tx=-(tz+ty+poly->D);
		tx=(tx<<12)/poly->normal.vx;
		
		printf("x:%d\n",tx);
		*height=tx;
		*normal=&poly->normal;
		return 1;
next:
		poly=poly->next;
	}
	return 0;
}

// **********************************************************************************************
BOOL Collision_Test(VECTOR *pos,SVECTOR *dir,VECTOR *hit,SVECTOR **n)
{
	long d;
	int h,map=0;

	hit->vx = pos->vx;
	hit->vy = pos->vy;
	hit->vz = pos->vz;

	h = Collision_SelectMap(dir);

	printf("map: %d\n",h);

	if (h == COLMAP_XZ_FLOOR || h == COLMAP_XZ_CEIL)
	{
		if (h == COLMAP_XZ_FLOOR)
			map = 1;

		if (Collision_TestXZ(pos,&d,n,map))
		{
			hit->vy = d;
			return TRUE;
		}

		if (Collision_TestXY(pos,&d,n,0))
		{
			hit->vz = d;
			return TRUE;
		}

		if (Collision_TestXY(pos,&d,n,1))
		{
			hit->vz = d;
			return TRUE;
		}

		if (Collision_TestZY(pos,&d,n,0))
		{
			hit->vx = d;
			return TRUE;
		}

		if (Collision_TestZY(pos,&d,n,1))
		{
			hit->vx = d;
			return TRUE;
		}
	}
	else if (h == COLMAP_ZY_LEFT || h == COLMAP_ZY_RIGHT)
	{
		if (h == COLMAP_ZY_RIGHT)
			map = 1;

		if (Collision_TestZY(pos,&d,n,map))
		{
			hit->vx = d;
			return TRUE;
		}
	}
	else
	{
		if (h == COLMAP_XY_RIGHT)
			map = 1;

		if (Collision_TestXY(pos,&d,n,map))
		{
			hit->vz = d;
			return TRUE;
		}
	}

	return FALSE;
}


// **********************************************************************************************
lpContainer	Container_LoadStaticCollisionHMDModel(lpContainer root, LPUCHAR fname, int modeflags)
{													 
lpContainer		veh;
unsigned long	*load_file=NULL;	
void		   	*hmd_model=NULL;
ULONG		   	file_size;
Uint8		   	name[64];

	sprintf(name,"%s.HMD", fname);

	load_file=File_LoadBinary(name,&file_size);

	if (load_file)
	{
		Collision_Setup(load_file);

		{
/*			VECTOR pos={ 0,ONE,0 };
			SVECTOR dir={ 0,-2896,2896 };
			VECTOR hit;
			SVECTOR *normal;
			long height;

			Collision_Test(&pos,&dir,&hit,&normal);*/

			VECTOR pos,end;
			SVECTOR dir,dir2;
			VECTOR hit;
			SVECTOR *normal;
			long height;
			int n,cnt=0;

			for (n=0;n<50;n++)
			{
				pos.vx=(rand() & 4095) - 2048;
				pos.vy=ONE;//(rand() & 4095) - 2048;
				pos.vz=(rand() & 4095) - 2048;

				end.vx=0;//(rand() & 511) - 256;
				end.vy=0;//(rand() & 511) - 256;
				end.vz=0;//(rand() & 511) - 256;

				dir2.vx=end.vx - pos.vx;
				dir2.vy=end.vy - pos.vy;
				dir2.vz=end.vz - pos.vz;

				VectorNormalSS(&dir2,&dir);

				cnt+=Collision_Test(&pos,&dir,&hit,&normal);
			}

			printf("hits:%d\n",cnt);
		}
/*
		{
			VECTOR pos={ 0,-ONE,0 };
			SVECTOR dir={ 0,2896,2896 };
			VECTOR hit;
			SVECTOR *normal;
			long height;

			Collision_Test(&pos,&dir,&hit,&normal);
		}
*/
		hmd_model=(HMD_Model *)HMD_InitStaticModel(load_file,NULL,modeflags);

		if ((veh=Container_ApplyMesh(root, hmd_model,TYPE_STATIC_HMD)))
		{
			LPDIRECT3DRMMESH  mesh = (LPDIRECT3DRMMESH)veh->modelData;
			Container_Hide(veh,TRUE);

			// Zero the Active subdivision parameters or set to default
			if ((modeflags & HMDACSUBFLAG) != 0)
			{
				veh->ASStatus			= 1;
				veh->ASDepth			= 300;
				veh->ASMaxPolyWidth		= 45;
				veh->ASMaxPolyHeight	= 45;		// default values
			}
			else
			{
				veh->ASStatus			= 0;
			}
		}
		printf("Created MODEL OK\n");
		return	veh;
	}

	printf("**ERROR** MODEL Not OK\n");

return NULL;
}


// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************



