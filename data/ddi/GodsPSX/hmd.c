
//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// HMD File For <GODS PSX>
//
// Version 1.3, Coded by Adrian Francis,
// Oct 15 '98
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ


// Include all Header Files

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
#include	"libgods.h"




#define HMDFOGON			// HMD model level fog on
//#define HMDPASUBON		// HMD model level passive subdivision on - a more elegant method is needed - perhaps individual polys can be flagged in lightwave
#define HMDACSUBON		// HMD model level Active subdivision - this is ok at model level as only polys bigger than a specified value are subbed.





/*****************************************************************************************************************************************************
******************************************************************************************************************************************************
******************************************************************************************************************************************************
*****************************************************************************************************************************************************/

// *******************************************************************
// ANIMATION 
//
// Modified update driver to correct problems with changing animation speed
//
// *******************************************************************

typedef struct
{
  long vx,vy;
  long vz;
  short rx,ry;
  short rz,sx;
  short sy,sz;
} LECTOR;

typedef struct 
{
  GsSEQ *base;
  LECTOR *src;
  LECTOR *dst;
  LECTOR *intr;
} GsARGANIM1;

typedef struct 
{
	u_long	*base;
	u_long	*src;
	u_long	*dst;
	u_long	*intr;
} GsARGANIM_OPAQ;

typedef unsigned long	DWORD;
#define FALSE	0

#define IS_NORM(x)	(((x) & 0x80000000) == 0)
#define IS_NOT_NORM(x)	(((x) & 0x80000000) != 0)
#define IS_JUMP(x)	(((x) & 0xc0000000) == 0x80000000)
#define IS_CTRL(x)	(((x) & 0xc0000000) == 0xc0000000)

/* for NORM */
#define TYPE_IDX(x)	(((x) & 0x7f000000) >> 24)
#define TFRAME(x)	(((x) & 0x00ff0000) >> 16)
#define PARAM_IDX(x)	((x) & 0x0000ffff)

/* for JUMP */
#define SID_DST(x)	(((x) & 0x3f800000) >> 23)
#define SID_CND(x)	(((x) & 0x007f0000) >> 16)
#define SEQ_IDX(x)	((x) & 0x0000ffff)

/* for CTRL */
#define CODE(x)		(((x) & 0x3f800000) >> 23)
#define P1(x)		(((x) & 0x007f0000) >> 16)
#define P2(x)		((x) & 0x0000ffff)
#define CODE_END	0x01
#define CODE_WORK	0x02

static u_short get_tctr(u_short idx, DWORD *p, GsSEQ *seq)
{
	d7 = seq->speed < 0 ? -1 : 1;
	while (a0 = p[idx], IS_NOT_NORM(a0)) 
	{
		if (IS_JUMP(a0)) 
		{
			d5 = SID_CND(a0);
			if (d5 == 0 || seq->sid == d5) 
			{
				d6 = SID_DST(a0);
				if (d5 != 0 || d6 != 0) 
				{
					seq->sid = d6;
				}
				idx = SEQ_IDX(a0);
				continue;
			}
		} 
		else 
		if (IS_CTRL(a0)) 
		{
			d5 = P1(a0);
			if (CODE(a0) == CODE_END && (d5 == 0 || seq->sid == d5))
			{
				return 0xffff;		/* END CODE */
			}
		} 
		idx += d7;
	}

	return idx;
}

u_long *HMD_03000000(GsARGUNIT_ANIM *sp)	/* update driver */
{
	int	size, wnum, i;
	int	(*func)(GsARGUNIT_ANIM *);
	DWORD	*htop = sp->htop;	/* hokan top */
	DWORD	*ctop = sp->ctop;	/* control top */
	DWORD	*ptop = sp->ptop;	/* parameter top */
	DWORD	*base;

	wnum = (*(sp->primp)) >> 16;
	for (base = &sp->primp[1], d2 = 0;d2 < wnum; d2++, base += base[1] & 0xffff)
	{
		GsSEQ	*seq = (GsSEQ *)base;
		GsARGANIM_OPAQ	*parm;
		int	dir;
		// Frame counter; stop at end of sequence or loop
		if (seq->aframe == 0) 
		{
			continue;
		} 
		else if(seq->aframe != 0xffff) 
		{
			seq->aframe--;
		}
      
		dir = seq->speed < 0 ? -1 : 1;
      
START:
		if (seq->rframe == 0 || seq->tframe ==0 || seq->traveling==0x67) 
		{
			/* key frame switching */
			seq->traveling = 0;
			
			if (dir == 1) 
			{
				if (IS_NOT_NORM(ctop[seq->ti]) && 
					(seq->ti = get_tctr(seq->ti + dir, ctop, seq)) == 0xffff) 
				{
					seq->aframe = 0;
					continue;
				}
				seq->ci = seq->ti;
				if ((seq->ti = get_tctr(seq->ci + dir, ctop, seq)) == 0xffff) 
				{
					seq->aframe = 0;
					continue;
				}
				
				seq->tframe = (TFRAME(ctop[seq->ti]) << 4);
				seq->rframe = (TFRAME(ctop[seq->ti]) << 4) - seq->rframe;
			} 
			else 
			{
				if (IS_NOT_NORM(ctop[seq->ci]) && 
					(seq->ci = get_tctr(seq->ci + dir, ctop, seq))==0xffff) 
				{
					seq->aframe = 0;
					continue;
				}
				seq->ti = seq->ci;
				if ((seq->ci = get_tctr(seq->ti + dir, ctop, seq))==0xffff) 
				{
					seq->aframe = 0;
					continue;
				}
				
				seq->tframe = TFRAME(ctop[seq->ti]) << 4;
			}
		}
      
		func = (int(*)(GsARGUNIT_ANIM *))htop[TYPE_IDX(ctop[seq->ti]) + 1];
		parm = (GsARGANIM_OPAQ *)(&(sp->header_size) + sp->header_size);
		parm->base = base;
		parm->src  = &ptop[PARAM_IDX(ctop[seq->ci])];
		parm->dst  = &ptop[PARAM_IDX(ctop[seq->ti])];
		if (seq->ii != 0xffff) 
		{
			parm->intr = &ptop[PARAM_IDX(ctop[seq->ii])];
		} 
		else 
		{
			parm->intr = 0;
		}
      
      	// if source keyframe != dest keyframe
		if (seq->ci != seq->ti) 
		{
			if (func(sp) == 1) 
			{
				seq->rframe = 0;
				goto START;
			}
	  
			if (TFRAME(ctop[seq->ti]) == 0) 
			{ 
				/* 0 tframe */
				goto START;
			}
      
			seq->rframe -= seq->speed;
      
			if (dir == 1 && seq->rframe < 0) 
			{
				seq->rframe = 0 - seq->rframe;
				seq->traveling=0x67;
			} 
			else if (dir == -1 && (seq->rframe >= seq->tframe)) 
			{
				seq->rframe = seq->rframe - seq->tframe;
				seq->traveling=0x67;
			}
		}
	}
	size = (*(sp->primp)) & 0xffff;
	return sp->primp + size;

}

/*****************************************************************************************************************************************************
******************************************************************************************************************************************************
******************************************************************************************************************************************************
*****************************************************************************************************************************************************/

// Animation Primitive drivers

// Linear translation
void HMD_03000001(GsARGUNIT_ANIM *sp0)
{
	GsCOORDUNIT *dtop;
	u_long ofs0,ofs1;
	GsSEQ *seq;
  	HMD_ARGANIMs0r0t1 *sp;
  	long rframe,tframe,dframe;
  	long inv_tframe;
  	HMD_ps0r0t1 *src,*dst,*intr;

	sp=(HMD_ARGANIMs0r0t1 *)(&(sp0->header_size)+sp0->header_size);
  	seq=sp->base;
  	if(!seq->tframe) return;
  	

  	ofs0=(seq->rewrite_idx &0xff000000)>>24;
  	ofs1=seq->rewrite_idx &0x00ffffff;
  
  	src=sp->src;
  	dst=sp->dst;
  	intr=sp->intr;

	a2=seq->rframe;
  	a3=seq->tframe;
  	a4=a3-a2;
  	a5=0x1000/a3;

  	dtop=(GsCOORDUNIT *)((u_long *)(*(&(sp0->header_size)+ofs0))+ofs1);
	dtop->matrix.t[0]=((src->tx*a2+dst->tx*a4)*a5)>>12;
  	dtop->matrix.t[1]=((src->ty*a2+dst->ty*a4)*a5)>>12;
  	dtop->matrix.t[2]=((src->tz*a2+dst->tz*a4)*a5)>>12;

	dtop->flg=0;
  
  	if(!intr) return;
    
    intr->tx=dtop->matrix.t[0];
    intr->ty=dtop->matrix.t[1];
    intr->tz=dtop->matrix.t[2];
}

// Linear rotation
void HMD_03000010(GsARGUNIT_ANIM *sp0)
{
	GsCOORDUNIT *dtop;
	u_long ofs0,ofs1;
	GsSEQ *seq;
  	HMD_ARGANIMs0r1t0 *sp;
  	long rframe,tframe,dframe;
  	long inv_tframe;
  	HMD_ps0r1t0 *src,*dst,*intr;
	
	sp=(HMD_ARGANIMs0r1t0 *)(&(sp0->header_size)+sp0->header_size);
  	seq=sp->base;
  	if(!seq->tframe) return;
  	
  	ofs0=(seq->rewrite_idx &0xff000000)>>24;
  	ofs1=seq->rewrite_idx &0x00ffffff;
  
  	src=sp->src;
  	dst=sp->dst;
  	intr=sp->intr;

	a2=seq->rframe;
  	a3=seq->tframe;
  	a4=a3-a2;
  	a5=0x1000/a3;
  
  	dtop=(GsCOORDUNIT *)((u_long *)(*(&(sp0->header_size)+ofs0))+ofs1);
 	dtop->rot.vx=((src->rx*a2+dst->rx*a4)*a5)>>12;
  	dtop->rot.vy=((src->ry*a2+dst->ry*a4)*a5)>>12;
  	dtop->rot.vz=((src->rz*a2+dst->rz*a4)*a5)>>12;
  	RotMatrix_gte(&dtop->rot,&dtop->matrix);
  	dtop->flg=0;
  
  	if(!intr) return;
    
    intr->rx=dtop->rot.vx;
    intr->ry=dtop->rot.vy;
    intr->rz=dtop->rot.vz;
}

// Linear rotation, linear translation
void HMD_03000011(GsARGUNIT_ANIM *sp0)
{
	GsCOORDUNIT *dtop;
	u_long ofs0,ofs1;
	GsSEQ *seq;
  	HMD_ARGANIMs0r1t1 *sp;
  	long rframe,tframe,dframe;
  	long inv_tframe;
  	HMD_ps0r1t1 *src,*dst,*intr;

	sp=(HMD_ARGANIMs0r1t1 *)(&(sp0->header_size)+sp0->header_size);
  	seq=sp->base;
  	if(!seq->tframe) return;
  	
  	ofs0=(seq->rewrite_idx &0xff000000)>>24;
  	ofs1=seq->rewrite_idx &0x00ffffff;
  
  	src=sp->src;
  	dst=sp->dst;
  	intr=sp->intr;
  	
  	rframe=seq->rframe;
  	tframe=seq->tframe;
  	dframe=tframe-rframe;
   	inv_tframe=0x1000/tframe;
  
  	dtop=(GsCOORDUNIT *)((u_long *)(*(&(sp0->header_size)+ofs0))+ofs1);
 	dtop->rot.vx=((src->rx*rframe+dst->rx*dframe)*inv_tframe)>>12;
  	dtop->rot.vy=((src->ry*rframe+dst->ry*dframe)*inv_tframe)>>12;
  	dtop->rot.vz=((src->rz*rframe+dst->rz*dframe)*inv_tframe)>>12;
  	RotMatrix_gte(&dtop->rot,&dtop->matrix);
 	dtop->matrix.t[0]=((src->tx*rframe+dst->tx*dframe)*inv_tframe)>>12;
  	dtop->matrix.t[1]=((src->ty*rframe+dst->ty*dframe)*inv_tframe)>>12;
  	dtop->matrix.t[2]=((src->tz*rframe+dst->tz*dframe)*inv_tframe)>>12;
  	dtop->flg=0;
  
  	if(!intr) return;
    
    intr->rx=dtop->rot.vx;
    intr->ry=dtop->rot.vy;
    intr->rz=dtop->rot.vz;
    intr->tx=dtop->matrix.t[0];
    intr->ty=dtop->matrix.t[1];
    intr->tz=dtop->matrix.t[2];
}

int GsUJ_03000111 (GsARGUNIT_ANIM *sp0)
{
	GsCOORDUNIT *dtop;
	u_long ofs0,ofs1;
	GsSEQ *seq;
	GsARGANIM1 *sp;
	long  rframe,tframe;
	VECTOR scale;
  

	sp   = (GsARGANIM1 *)(&(sp0->header_size)+sp0->header_size);
	seq  = sp->base;
	if(seq->tframe==0) return 1;
	ofs0 = ((seq->rewrite_idx)&0xff000000)>>24;
	ofs1 = (seq->rewrite_idx)&0x00ffffff;

	a2 = seq->rframe;
	a3 = seq->tframe;
  	a4=a3-a2;//tframe-rframe;
  	a5=0x1000/a3;//tframe;
  
	dtop = (GsCOORDUNIT *)((u_long *)(*(&(sp0->header_size)+ofs0))+ofs1);

	dtop->matrix.t[0]=((sp->src->vx*a2+sp->dst->vx*a4)*a5)>>12;
  	dtop->matrix.t[1]=((sp->src->vy*a2+sp->dst->vy*a4)*a5)>>12;
  	dtop->matrix.t[2]=((sp->src->vz*a2+sp->dst->vz*a4)*a5)>>12;

	dtop->rot.vx=((sp->src->rx*a2+sp->dst->rx*a4)*a5)>>12;
  	dtop->rot.vy=((sp->src->ry*a2+sp->dst->ry*a4)*a5)>>12;
  	dtop->rot.vz=((sp->src->rz*a2+sp->dst->rz*a4)*a5)>>12;
	RotMatrix_gte(&dtop->rot,&dtop->matrix);
	scale.vx=((sp->src->sx*a2+sp->dst->sx*a4)*a5)>>12;
  	scale.vy=((sp->src->sy*a2+sp->dst->sy*a4)*a5)>>12;
  	scale.vz=((sp->src->sz*a2+sp->dst->sz*a4)*a5)>>12;
	ScaleMatrix(&dtop->matrix,&scale);

	dtop->flg = 0;
  
	if(sp->intr)
	{
		sp->intr->vx = dtop->matrix.t[0];
		sp->intr->vy = dtop->matrix.t[1];
		sp->intr->vz = dtop->matrix.t[2];
		sp->intr->rx = dtop->rot.vx;
		sp->intr->ry = dtop->rot.vy;
		sp->intr->rz = dtop->rot.vz;
		sp->intr->sx = scale.vx;
		sp->intr->sy = scale.vy;
		sp->intr->sz = scale.vz;
	}
  
	return 0;
}

/*****************************************************************************************************************************************************
******************************************************************************************************************************************************
******************************************************************************************************************************************************
*****************************************************************************************************************************************************/

// Primitive scan functions

void HMD_ScanAnim(void)
{
  GsTYPEUNIT	ut;
  
  while(GsScanAnim(0,&ut))
    {
    ut.type&=0xFFFF1FFF;
    switch(ut.type)
	{
	case 0x03000001:	/* translation linear (32bit) */
	  	*(ut.ptr) = (u_long)HMD_03000001;
	  	break;
//	case 0x03000002:	/* translation bezier (32bit) */
//	  	*(ut.ptr) = (u_long)GsU_03000002;
//	  	break;
//	case 0x03000003:	/* translation bsprine (32bit) */
//	  	*(ut.ptr) = (u_long)GsU_03000003;
//	  	break;
	case 0x03000009:	/* translation linear (16bit) */
	  	*(ut.ptr) = (u_long)GsU_03000009;
	  	break;
//	case 0x0300000a:	/* translation bezier (16bit) */
//	  	*(ut.ptr) = (u_long)GsU_0300000a;
//	  	break;
//	case 0x0300000b:	/* translation bsprine (16bit) */
//	  	*(ut.ptr) = (u_long)GsU_0300000b;
//	  	break;
	case 0x03000010:	/* rotation linear */
	  	*(ut.ptr) = (u_long)HMD_03000010;
	  	break;
	case 0x03000011:	/* rotation linear translation linear (32bit)*/
	  	*(ut.ptr) = (u_long)HMD_03000011;
	  	break;
//	case 0x03000012:	/* rotation linear translation bezier (32bit)*/
//	  	*(ut.ptr) = (u_long)GsU_03000012;
//	  	break;
//	case 0x03000013:	/* rotation linear translation bsprine(32bit)*/
//	  	*(ut.ptr) = (u_long)GsU_03000013;
//	  	break;
	case 0x03000019:	/* rotation linear translation linear(16bit)*/
	  	*(ut.ptr) = (u_long)GsU_03000019;
	  	break;
//	case 0x0300001a:	/* rotation linear translation bezier(16bit)*/
//	  	*(ut.ptr) = (u_long)GsU_0300001a;
//	  	break;
//	case 0x0300001b:	/* rotation linear translation bsprine(16bit)*/
//	  	*(ut.ptr) = (u_long)GsU_0300001b;
//	  	break;
//	case 0x03000020:	/* rotation bezier */
//	  	*(ut.ptr) = (u_long)GsU_03000020;
//	  	break;
//	case 0x03000021:	/* rotation bezier translation linear (32bit)*/
//	  	*(ut.ptr) = (u_long)GsU_03000021;
//	  	break;
//	case 0x03000022:	/* rotation bezier translation bezier (32bit)*/
//	  	*(ut.ptr) = (u_long)GsU_03000022;
//	  	break;
//	case 0x03000023:	/* rotation bezier translation bsprine(32bit)*/
//	  	*(ut.ptr) = (u_long)GsU_03000023;
//	  	break;
//	case 0x03000029:	/* rotation bezier translation linear(16bit)*/
//	  	*(ut.ptr) = (u_long)GsU_03000029;
//	  	break;
//	case 0x0300002a:	/* rotation bezier translation bezier(16bit)*/
//	  	*(ut.ptr) = (u_long)GsU_0300002a;
//	  	break;
//	case 0x0300002b:	/* rotation bezier translation bsprine(16bit)*/
//	  	*(ut.ptr) = (u_long)GsU_0300002b;
//	  	break;
//	case 0x03000030:	/* rotation bsprine */
//	  	*(ut.ptr) = (u_long)GsU_03000030;
//	  	break;
//	case 0x03000031:	/* rotation bsprine translation linear (32bit)*/
//	  	*(ut.ptr) = (u_long)GsU_03000031;
//	  	break;
//	case 0x03000032:	/* rotation bsprine translation bezier (32bit)*/
//	  	*(ut.ptr) = (u_long)GsU_03000032;
//	  	break;
//	case 0x03000033:	/* rotation bsprine translation bsprine(32bit)*/
//	  	*(ut.ptr) = (u_long)GsU_03000033;
//	  	break;
//	case 0x03000039:	/* rotation bsprine translation linear(16bit)*/
//	  	*(ut.ptr) = (u_long)GsU_03000039;
//	  	break;
//	case 0x0300003a:	/* rotation bsprine translation bezier(16bit)*/
//	  	*(ut.ptr) = (u_long)GsU_0300003a;
//	  	break;
//	case 0x0300003b:	/* rotation bsprine translation bsprine(16bit)*/
//	  	*(ut.ptr) = (u_long)GsU_0300003b;
//	  	break;

 		case 0x03000909:	/* scale(one) translation(short) linear */
		  	*(ut.ptr) = (u_long)GsU_03000909;
		  	break;
		case 0x03000100:	/* scale linear */
		  	*(ut.ptr) = (u_long)GsU_03000100;
		  	break;
		case 0x03000910:	/* scale(one) rotation linear */
		  	*(ut.ptr) = (u_long)GsU_03000910;
		  	break;
		case 0x03000911:	/* scale(one) translation rotation linear */
		  	*(ut.ptr) = (u_long)GsU_03000911;
		  	break;
		case 0x03000111:	/* scale translation rotation linear */
		  	*(ut.ptr) = (u_long)GsU_03000111;
		  	break;
		case 0x03000119:	/* scale translation(short) rotation linear */
		  	*(ut.ptr) = (u_long)GsU_03000119;
		  	break;

//	case 0x03010110:	/* general linear (32bit) */
//		*(ut.ptr) = (u_long)GsU_03010110;
//	    break;
//	case 0x03010111:	/* general linear (16bit offset0) */
//	    *(ut.ptr) = (u_long)GsU_03010111;
//	    break;
//	case 0x03010121: 	/* general linear (16bit offset1) */
//	    *(ut.ptr) = (u_long)GsU_03010121;
//	    break;
//	case 0x03010141: 	/* general linear (16bit offset2) */
//	    *(ut.ptr) = (u_long)GsU_03010141;
//	    break;
//	case 0x03010171:	/* general linear (16bit Vector) */
//	    *(ut.ptr) = (u_long)GsU_03010171;
//	    break;
//	case 0x03010112:	/* general linear (8bit offset0) */
//	    *(ut.ptr) = (u_long)GsU_03010112;
//	    break;
//	case 0x03010122:	/* general linear (8bit offset1) */
//	    *(ut.ptr) = (u_long)GsU_03010122;
//	    break;
//	case 0x03010142:	/* general linear (8bit offset2) */
//	    *(ut.ptr) = (u_long)GsU_03010142;
//	    break;
//	case 0x03010182:	/* general linear (8bit offset3) */
//	    *(ut.ptr) = (u_long)GsU_03010182;
//	    break;
//	case 0x03010172:	/* general linear (8bit Vector) */
//	    *(ut.ptr) = (u_long)GsU_03010172;
//	    break;
//	case 0x03010210:	/* general bezier (32bit) */
//	    *(ut.ptr) = (u_long)GsU_03010210;
//	    break;
//	case 0x03010211:	/* general bezier (16bit offset0) */
//	    *(ut.ptr) = (u_long)GsU_03010211;
//	    break;
//	case 0x03010221:	/* general bezier (16bit offset1) */
//	    *(ut.ptr) = (u_long)GsU_03010221;
//	    break;
//	case 0x03010241:	/* general bezier (16bit offset2) */
//	    *(ut.ptr) = (u_long)GsU_03010241;
//	    break;
//	case 0x03010271:	/* general bezier (16bit Vector) */
//	    *(ut.ptr) = (u_long)GsU_03010271;
//	    break;
//	case 0x03010212:	/* general bezier (8bit offset0) */
//	    *(ut.ptr) = (u_long)GsU_03010212;
//	    break;
//	case 0x03010222:	/* general bezier (8bit offset1) */
//	    *(ut.ptr) = (u_long)GsU_03010222;
//	    break;
//	case 0x03010242:	/* general bezier (8bit offset2) */
//	    *(ut.ptr) = (u_long)GsU_03010242;
//	    break;
//	case 0x03010272:	/* general bezier (8bit Vector) */
//	    *(ut.ptr) = (u_long)GsU_03010272;
//	    break;
//	case 0x03010310:	/* general bsprine (32bit) */
//	    *(ut.ptr) = (u_long)GsU_03010310;
//	    break;
//	case 0x03010311:	/* general bsprine (16bit offset0) */
//	    *(ut.ptr) = (u_long)GsU_03010311;
//	    break;
//	case 0x03010321:	/* general bsprine (16bit offset1) */
//	    *(ut.ptr) = (u_long)GsU_03010321;
//	    break;
//	case 0x03010341:	/* general bsprine (16bit offset2) */
//	    *(ut.ptr) = (u_long)GsU_03010341;
//	    break;
//	case 0x03010371:	/* general bsprine (16bit Vector) */
//	    *(ut.ptr) = (u_long)GsU_03010371;
//	    break;
//	case 0x03010312:	/* general bsprine (8bit offset0) */
//	    *(ut.ptr) = (u_long)GsU_03010312;
//	    break;
//	case 0x03010322:	/* general bsprine (8bit offset1) */
//	    *(ut.ptr) = (u_long)GsU_03010322;
//	    break;
//	case 0x03010342:	/* general bsprine (8bit offset2) */
//	    *(ut.ptr) = (u_long)GsU_03010342;
//	    break;
//	case 0x03010372:	/* general bsprine (8bit Vector) */
//	    *(ut.ptr) = (u_long)GsU_03010372;
//	    break;
	default:
	    *(ut.ptr) = (u_long)HMD_03000000;
	  printf("HMD: This model requires animation driver 0x%08x\n",ut.type);
	}
    }
}


/*************************************************************************************************************************************************************************************************
	New Polygon diver routines by Julian.
	Inclusion of various driver types are controlled by defines at the start of the code.
	Note that speed is not a huge issue in this routine as it should only be called once per model.
*************************************************************************************************************************************************************************************************/
// Add a forced selection system for force entire models to take on attributes
int HMD_ScanPoly(GsTYPEUNIT *ut, GsSEQ **seq,HMD_Model *model, int modeflags)
{
    int anum = 0;
	int HMDSUBLEVEL;
// W.E Bodgeit and scarper by julian....
// Added packet handlers for fogged HMD's 
// Will probably need to add same for STP's as well.
	if (	ut->type != 0x3800000 &&
			ut->type != 0x2000001 &&
			ut->type != 0x1000000 &&
			ut->type != 0 &&
			modeflags != 0)
	{

// Set fogging on?
		if ((modeflags & HMDFOGFLAG) !=0)
		{
			ut->type = ut->type  | HMDFOGFLAG;
		}

// Set active subdivision on?
		if (	ut->type != 0x102000d &&
				ut->type != 0x1020014 &&
				ut->type != 0x1020015 &&
				ut->type != 0x100000d &&
				ut->type != 0x1000014 &&
				ut->type != 0x1000015
				&& (modeflags & HMDACSUBFLAG) != 0)
		{
			ut->type = ut->type  | HMDACSUBFLAG;
			HMDSUBLEVEL = (modeflags & 7)<<24;
		}
	}

    switch(ut->type) 
    {
// Generic drivers which should always be included ****************************************************************************************************************************************
    case 0:			// ERROR!!! Already set
		break;
    case GsUF3:		// Flat triangle
		*(ut->ptr) = (u_long)GsU_00000008;
		break;
    case GsUFT3: 	// Flat textured triangle
		*(ut->ptr) = (u_long)GsU_00000009;
		break;
    case GsUG3:		// Gouraud triangle
		*(ut->ptr) = (u_long)GsU_0000000c;
		break;
    case GsUGT3:	// Gouraud textured triangle
		*(ut->ptr) = (u_long)GsU_0000000d;
		break;
    case GsUF4:		// Flat quad
		*(ut->ptr) = (u_long)GsU_00000010;
		break;
    case GsUFT4:	// Flat textured quad
		*(ut->ptr) = (u_long)GsU_00000011;
		break;
    case GsUG4:		// Gouraud quad
		*(ut->ptr) = (u_long)GsU_00000014;
		break;
    case GsUGT4:	// Gouraud textured quad
		*(ut->ptr) = (u_long)GsU_00000015;
		break;

    case GsUSCAL:	// Shared calculate vertex and normal
		*(ut->ptr) = (u_long)GsU_01000000;
		break;
    case GsUSG3:	// Shared gouraud triangle
		*(ut->ptr) = (u_long)GsU_0100000c;
		break;
    case GsUSGT3:	// Shared gouraud textured triangle
		*(ut->ptr) = (u_long)GsU_0100000d;
		break;
    case GsUSG4:	// Shared gouraud quad
		*(ut->ptr) = (u_long)GsU_01000014;
		break;
    case GsUSGT4:	// Shared gouraud textured quad
		*(ut->ptr) = (u_long)GsU_01000015;
		break;

/*		
    case GsUTFT3:	// Tiled flat textured triangle
		*(ut->ptr) = (u_long)GsU_00000209;
		break;
    case GsUTGT3:	// Tiled gouraud textured triangle
		*(ut->ptr) = (u_long)GsU_0000020d;
		break;
    case GsUTFT4:	// Tiled flat textured triangle
		*(ut->ptr) = (u_long)GsU_00000211;
		break;
    case GsUTGT4:	// Tiles gouraud textured triangle
		*(ut->ptr) = (u_long)GsU_00000215;
		break;
*/
/*
    case GsUSTPF3:	// Semi transparent flat triangle
			*(ut->ptr) = (u_long)GsU_00200008;
			break;
    case GsUSTPFT3:	// Semi transparent flat textured triangle
			*(ut->ptr) = (u_long)GsU_00200009;
			break;
    case GsUSTPG3:	// Semi transparent gouraud triangle
			*(ut->ptr) = (u_long)GsU_0020000c;
			break;
    case GsUSTPGT3:	// Semi transparent gouraud textured triangle
			*(ut->ptr) = (u_long)GsU_0020000d;
			break;
    case GsUSTPF4:	// Semi transparent flat quad
			*(ut->ptr) = (u_long)GsU_00200010;
			break;
    case GsUSTPFT4:	// Semi transparent flat textured quad
			*(ut->ptr) = (u_long)GsU_00200011;
			break;
    case GsUSTPG4:	// Semi transparent gouraud quad
			*(ut->ptr) = (u_long)GsU_00200014;
			break;
    case GsUSTPGT4:	// Semi transparent gouraud textured quad
			*(ut->ptr) = (u_long)GsU_00200015;
			break;
*/
// Fogging on added by julian *******************************************************************************************************************************************************************
#ifdef HMDFOGON
    case GsUFF3:	// Fogged flat triangle
		*(ut->ptr) = (u_long)GsU_00020008;
		break;
    case GsUFFT3: 	// Fogged flat textured triangle
		*(ut->ptr) = (u_long)GsU_00020009;
		break;
    case GsUFG3:	// Fogged gouraud triangle
		*(ut->ptr) = (u_long)GsU_0002000c;
		break;
    case GsUFGT3:	// Fogged gouraud textured triangle
		*(ut->ptr) = (u_long)GsU_0002000d;
		break;
    case GsUFF4:	// Fogged flat quad
		*(ut->ptr) = (u_long)GsU_00020010;
		break;
    case GsUFFT4:	// Fogged flat textured quad
		*(ut->ptr) = (u_long)GsU_00020011;
		break;
    case GsUFG4:	// Fogged gouraud quad
		*(ut->ptr) = (u_long)GsU_00020014;
		break;
    case GsUFGT4:	// Fogged gouraud textured quad
		*(ut->ptr) = (u_long)GsU_00020015;
		break;

	case GsUSFG3:
		*(ut->ptr) = (u_long)GsU_0102000c;	// shared fog gour triangle 
		break;
	case GsUSFGT3:
		*(ut->ptr) = (u_long)GsU_0102000d;	// shared fog texture gour triangle 
		break;
	case GsUSFG4:
		*(ut->ptr) = (u_long)GsU_01020014;	// shared fog gour quad 
		break;
	case GsUSFGT4:	
		*(ut->ptr) = (u_long)GsU_01020015;	// shared fog texture gour quad
		break;

#endif

/*********************************************************************************************************************************************************************************************
	Passive sub division drivers
 *********************************************************************************************************************************************************************************************/
#ifdef HMDPASUBON
	case GsUDF3:		// div flat triangle 
		*(ut->ptr) = (u_long)GsU_00010008;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDFT3:			// div texture flat triangle 
		*(ut->ptr) = (u_long)GsU_00010009;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDG3:			// div gour triangle 
		*(ut->ptr) = (u_long)GsU_0001000c;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDGT3:			// div texture gour triangle 
		*(ut->ptr) = (u_long)GsU_0001000d;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDF4:			// div flat quad 
		*(ut->ptr) = (u_long)GsU_00010010;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDFT4:			// div texture flat quad 
		*(ut->ptr) = (u_long)GsU_00010011;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDG4:			// div gour quad 
		*(ut->ptr) = (u_long)GsU_00010014;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDGT4:		// div texture gour quad 
		*(ut->ptr) = (u_long)GsU_00010015;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
/*
	case GsUDNF3:			// div nonLight flat triangle 
		*(ut->ptr) = (u_long)GsU_00050048;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDNFT3:		// div nonLight texture flat triangle 
		*(ut->ptr) = (u_long)GsU_00050049;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDNG3:			// div nonLight gouraud triangle 
		*(ut->ptr) = (u_long)GsU_0005004c;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDNGT3:		// div nonLight tex gouraud triangle 
		*(ut->ptr) = (u_long)GsU_0005004d;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDNF4:			// div nonLight flat quad 
		*(ut->ptr) = (u_long)GsU_00050050;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDNFT4:		// div nonLight texture flat quad 
		*(ut->ptr) = (u_long)GsU_00050051;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDNG4:			// div nonLight gouraud quad 
		*(ut->ptr) = (u_long)GsU_00050054;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDNGT4:		// div nonLight tex gouraud quad 
		*(ut->ptr) = (u_long)GsU_00050055;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
*/
// Check for fogged passively subdivided polys ***********************************************************************************************************************************************		
#ifdef HMDFOGON
	case GsUDFF3:			// div fog flat triangle 
		*(ut->ptr) = (u_long)GsU_00030008;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDFFT3:		// div fog texture flat triangle 
		*(ut->ptr) = (u_long)GsU_00030009;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDFG3:			// div fog gour triangle 
		*(ut->ptr) = (u_long)GsU_0003000c;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDFGT3:		// div fog texture gour triangle 
		*(ut->ptr) = (u_long)GsU_0003000d;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDFF4:			// div fog flat quad 
		*(ut->ptr) = (u_long)GsU_00030010;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDFFT4:		// div fog texture flat quad 
		*(ut->ptr) = (u_long)GsU_00030011;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDFG4:			// div fog gour quad 
		*(ut->ptr) = (u_long)GsU_00030014;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUDFGT4:		// div fog texture gour quad 
		*(ut->ptr) = (u_long)GsU_00030015;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
#endif
#endif

/*********************************************************************************************************************************************************************************************
 Active sub division drivers
 *********************************************************************************************************************************************************************************************/
#ifdef HMDACSUBON
	case GsUADF3:		// active-div flat triangle 
		*(ut->ptr) = (u_long)GsU_00080008;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADFT3:		// active-div texture flat triangle 
		*(ut->ptr) = (u_long)GsU_00080009;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADG3:			// active-div gour triangle 
		*(ut->ptr) = (u_long)GsU_0008000c;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADGT3:		// active-div texture gour triangle 
		*(ut->ptr) = (u_long)GsU_0008000d;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADF4:			// active-div flat quad 
		*(ut->ptr) = (u_long)GsU_00080010;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADFT4:		// active-div texture flat quad 
		*(ut->ptr) = (u_long)GsU_00080011;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADG4:			// active-div gour quad 
		*(ut->ptr) = (u_long)GsU_00080014;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADGT4:		// active-div texture gour quad 
		*(ut->ptr) = (u_long)GsU_00080015;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
/*
	case GsUADNF3:		// active-div nonLight flat tri 
		*(ut->ptr) = (u_long)GsU_000c0048;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADNFT3:		// active-div nonLight tex flat tri 
		*(ut->ptr) = (u_long)GsU_000c0049;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADNG3:		// active-div nonLight gour tri 
		*(ut->ptr) = (u_long)GsU_000c004c;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADNGT3:		// active-div nonLight tex gour tri 
		*(ut->ptr) = (u_long)GsU_000c004d;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADNF4:		// active-div nonLight flat quad 
		*(ut->ptr) = (u_long)GsU_000c0050;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADNFT4:		// active-div nonLight tex flat quad 
		*(ut->ptr) = (u_long)GsU_000c0051;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADNG4:		// active-div nonLight gour quad 
		*(ut->ptr) = (u_long)GsU_000c0054;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADNGT4:		// active-div nonLight tex gour quad 
		*(ut->ptr) = (u_long)GsU_000c0055;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
*/
#ifdef HMDFOGON
	case GsUADFF3:		// active-div fog flat tri 
		*(ut->ptr) = (u_long)GsU_000a0008;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADFFT3:		// active-div fog texture flat tri 
		*(ut->ptr) = (u_long)GsU_000a0009;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADFG3:		// active-div fog gour tri 
		*(ut->ptr) = (u_long)GsU_000a000c;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADFGT3:		// active-div fog texture gour tri 
		*(ut->ptr) = (u_long)GsU_000a000d;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADFF4:		// active-div fog flat quad 
		*(ut->ptr) = (u_long)GsU_000a0010;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADFFT4:		// active-div fog texture flat quad 
		*(ut->ptr) = (u_long)GsU_000a0011;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADFG4:		// active-div fog gour quad 
		*(ut->ptr) = (u_long)GsU_000a0014;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
	case GsUADFGT4:		// active-div fog texture gour quad 
		*(ut->ptr) = (u_long)GsU_000a0015;
		*(ut->ptr+2) |= HMDSUBLEVEL;	// Divide num(4x4) set 
		break;
#endif
#endif


    case GsUIMG0:	// Image with no CLUT
		*(ut->ptr) = (u_long)GsU_00000000;
//		HMD_RelocateTexture(0,(GsARGUNIT_IMAGE *)getScratchAddr(4*16));
		GsU_02000000((GsARGUNIT *)getScratchAddr(4*16));
		break;
    case GsUIMG1:	// Image with CLUT
		*(ut->ptr) = (u_long)GsU_00000000;
//		HMD_RelocateTexture(1,(GsARGUNIT_IMAGE *)getScratchAddr(4*16));
		GsU_02000001((GsARGUNIT *)getScratchAddr(4*16));
		break;

    case 0x03800000:// Animation scan	
		*(ut->ptr) = (u_long)HMD_03000000;
		anum = GsLinkAnim(seq,ut->ptr);
		if(GsScanAnim(ut->ptr,0)==0)
	   	{
			printf("HMD: ScanAnim failed!!\n\n");
			break;
	    }
		HMD_ScanAnim();
		break;
    default:		// Unknown type
		*(ut->ptr) = (u_long)GsU_00000000;
		printf("HMD: This model requires primitive driver 0x%08x\n",ut->type);
    }
    return anum;
}

/*****************************************************************************************************************************************************
******************************************************************************************************************************************************
******************************************************************************************************************************************************
*****************************************************************************************************************************************************/

// Initialize a static HMD (ie. an HMD with no animation), and return a pointer to a new HMD model structure
HMD_Model *HMD_InitStaticModel(u_long *hmd, GsOT *ot, int modeflags)
{
	int i;
	u_long	*ptr;
	GsTYPEUNIT ut;
	GsUNIT	*objp;	
	HMD_Model *model;
		
	// Map the hmd data to real addresses
	ptr=hmd;
	GsMapUnit(ptr);		
	ptr++;			
	ptr++;		
	ptr++;		
		
	// Allocate space for model data
	if ((model=(HMD_Model *)Mem_Malloc(sizeof(HMD_StaticModel)))!=NULL)
	{
		// Initialize model data
		model->coord		=	NULL;
		model->root			=	-1;
		model->initialized	=	0;

		model->blocks=*ptr;
		if (model->blocks>=3 && ((model->block=(GsUNIT *)Mem_Malloc(model->blocks*sizeof(GsUNIT)))!=NULL))
		{	
			// Initialize primitive blocks
			ptr++;			
			objp=model->block;

			for(i = 0 ; i < model->blocks ; i++) 
			{
				objp->primtop=(u_long *)*ptr;
			
				if (objp->primtop)
				{	
					// Scan the primitive block
					GsScanUnit(objp->primtop,0,0,0);

					while(GsScanUnit(0,&ut,ot,getScratchAddr(4*16))) 
					{
						if (((ut.type>>24==0x00) || (ut.type>>24==0x01) ||
						     (ut.type>>24==0x05)) && (ut.type&0x00800000)) 
						{
							// Store coordinate block
							model->coord=GsMapCoordUnit(hmd,ut.ptr);
							ut.type&=(~0x00800000);
						}

						// Initialize primitive
						HMD_ScanPoly(&ut,NULL,model, modeflags);
 					}
		
 					// Store coordinate system for this primitive block, if it has one
 					if ((i>0) && (i<model->blocks-1) && model->coord) objp->coord=&model->coord[i-1];
 					else objp->coord=NULL;
 				}
		
 				ptr++;
 				objp++;
 			}
	
 			// Find the root coordinate system and store the index
 			for (i=0;i<(model->blocks-2);i++) 
 			{
 				if (!model->coord[i].super) 
 				{
 					model->root=i;
 					break;
 				}
 			}

 			// Has the model got a root coordinate system
 			if ((long)model->root>=0)
				return model;
		}
	}
	return NULL;
}

// Initialize HMD, and return a pointer to a new HMD model structure
HMD_Model *HMD_InitModel(u_long *hmd,GsOT *ot, int modeflags)
{
	int i,n;
	u_long	*ptr;
	GsTYPEUNIT ut;
	GsUNIT	*objp;	
	HMD_Model *model,*nmodel;
	GsSEQ *seq[HMD_MAXSEQ];
	
	// Map the hmd data to real addresses
	ptr=hmd;
	GsMapUnit(ptr);		
	ptr++;			
	ptr++;		
	ptr++;		
	
	// Allocate space for model data
	if ((model=(HMD_Model *)Mem_Malloc(sizeof(HMD_Model)))!=NULL)
	{
		// Initialize model data
		model->coord=NULL;
		model->root=-1;
		model->initialized=0;
		model->seqs=0;
		
		model->blocks=*ptr;
		if (model->blocks>=3 && ((model->block=(GsUNIT *)Mem_Malloc(model->blocks*sizeof(GsUNIT)))!=NULL))
		{	
			// Initialize primitive blocks
			ptr++;			
			objp=model->block;
			for(i=0;i<model->blocks;i++) 
			{
				objp->primtop=(u_long *)*ptr;
				
				if (objp->primtop)
				{	
					// Scan the primitive block
					GsScanUnit(objp->primtop,0,0,0);
					while(GsScanUnit(0,&ut,ot,getScratchAddr(4*16))) 
					{
						if (((ut.type>>24==0x00) || (ut.type>>24==0x01) ||
							(ut.type>>24==0x05)) && (ut.type&0x00800000)) 
						{
							// Store coordinate block
							model->coord=GsMapCoordUnit(hmd,ut.ptr);
							ut.type&=(~0x00800000);
						}
						
						// Initialize primitive
						if ((n=HMD_ScanPoly(&ut,seq,model, modeflags))>0)
						{
							model->seq=(GsSEQ **)Mem_Malloc(n * sizeof(GsSEQ *));
							memcpy(model->seq,seq,n * sizeof(GsSEQ *));
							model->aframe=(u_short *)Mem_Malloc(n * sizeof(u_short));
							model->animIndex=(u_short *)Mem_Malloc(n * sizeof(u_short) * HMD_MAX_ANIMS);

							{
								//-------------------------------------------------------------------------------
								// SteveD - added unpleasant table for animation restarting. It's not pretty
								//			but it works.
								//-------------------------------------------------------------------------------
								int				index=0,sc,ac;
								void			*vseqHdr;
								GsSEH			*seqHdr;
								unsigned short	*animIndexPtr=model->animIndex;
								
								
								for (sc=n;sc--;) 
								{
									vseqHdr=&model->seq[index++]->start;
									seqHdr=(GsSEH*) vseqHdr;
									for (ac=0; ac<HMD_MAX_ANIMS; ac++)
									{
										*animIndexPtr++=seqHdr->idx;
										seqHdr++;
									}
								}
								//-------------------------------------------------------------------------------
							}
							
							model->seqs=n;
							
						}
					}
					
					// Store coordinate system for this primitive block, if it has one
					if ((i>0) && (i<model->blocks-1) && model->coord) objp->coord=&model->coord[i-1];
					else objp->coord=NULL;
				}
				
				ptr++;
				objp++;
			}
			
			// Find the root coordinate system and store the index
			for (i=0;i<(model->blocks-2);i++) 
			{
				if (!model->coord[i].super) 
				{
					model->root=i;
					break;
				}
			}

			// Has the model got a root coordinate system
			if ((long)model->root>=0)
			{
				// Create a copy of the model, so the programmer has no direct access to the original!
				model->original=model;
				if ((nmodel=HMD_InitInstance(model))!=NULL) return nmodel;
			}
			Mem_Free(model->block);
		}
		Mem_Free(model);
	}	
	return NULL;
}

// Create an instance of an HMD model, and return a pointer to the new instance
// [Optimized - If a model needs to be created during the game loop] 
HMD_Model *HMD_InitInstance(HMD_Model *model)
{
	HMD_Model *newmodel;
	GsSEQ *seq,**sseq,*dseq,**nseq;
	GsUNIT *ptr;
	u_long n,**pt;
	int bytes,i;
	
	if ((newmodel=(HMD_Model *)Mem_Malloc(sizeof(HMD_Model)))!=NULL)
	{
		newmodel->original=model->original;
		newmodel->block=model->block;
		newmodel->blocks=model->blocks;
		newmodel->seqs=model->seqs;
		
		if ((newmodel->primtop=(u_long **)Mem_Malloc((model->blocks-2)*sizeof(u_long *)))!=NULL)
		{
			// Copy primtop pointers
			pt=&newmodel->primtop[0];
			ptr=&model->block[1];
			for (i=(model->blocks-2);i--;)
			{
				n=(u_long)(ptr++)->primtop;
				if (n) n|=0x80000000;
				*pt++=(u_long *)n;
			}
			
			bytes=(model->blocks-2)*sizeof(GsCOORDUNIT);
			if ((newmodel->coord=(GsCOORDUNIT *)Mem_Malloc(bytes))!=NULL)
			{
				// Copy coordinate systems and make a pointer to the root
				newmodel->root=model->original->root;
				HMD_Copy4(newmodel->coord,model->coord,bytes);

				// Allocate sequence pointers if there are any
				seq=NULL;
			//	newmodel->seq[0]=NULL;
				if (model->seqs) 
				{
					newmodel->aframe=(u_short *)Mem_Malloc(newmodel->seqs * sizeof(u_short));

					newmodel->seq=(GsSEQ **)Mem_Malloc(newmodel->seqs * sizeof(GsSEQ *));
					seq=(GsSEQ *)Mem_Malloc((model->seqs*sizeof(GsSEQ)));
				}
				
				// If space was allocated for the sequence pointers...
				if (seq && newmodel->seq)
				{
					
					// Copy the animation sequence pointers
					sseq=&model->seq[0];
					dseq=seq;
					nseq=&newmodel->seq[0];
					
					for (i=model->seqs;i--;) 
					{
						HMD_Copy4(dseq,*sseq++,sizeof(GsSEQ));
						*nseq++=dseq++;
					}
				}
				
				// If space was not allocated but there are sequences, then free coords					
				if ((!seq || !newmodel->seq) && model->seqs) Mem_Free(newmodel->coord);
				else
				{
					// Otherwise, complete the initialization
					model->original->initialized++;
					newmodel->initialized=1;
					return newmodel;
				}
			}
			Mem_Free(newmodel->primtop);
		}
	}
	return NULL;
}

// Free HMD model data
void HMD_FreeModel(HMD_Model *model)
{	
	model->original->initialized--;
	
	// Was this the last instance to be freed?
	if (!model->original->initialized)
	{
		// Free the original too
		RELEASE(model->original->block);
		RELEASE(model->original);
	}

	// Otherwise, just free this instance
	RELEASE(model->primtop);
	RELEASE(model->coord);

	if (model->seq[0])
	{
		RELEASE(model->seq[0]);
	}
	Mem_Free(model);
}

/*****************************************************************************************************************************************************
******************************************************************************************************************************************************
******************************************************************************************************************************************************
*****************************************************************************************************************************************************/

// Add an HMD model to an order table [Optimized]
void HMD_AddModel(HMD_Model *model,GsOT *ot)
{
	int bytes,i,seqs;
	GsUNIT *ptr;
	MATRIX *matLS=(MATRIX *)getScratchAddr(4*16);
	MATRIX *matLW=(MATRIX *)(getScratchAddr(4*16) + sizeof(MATRIX));
	HMD_Model *original;
	GsCOORDUNIT *mcoord,*ocoord;
	GsSEQ **seq,**oseq,**msq,**osq;
	u_long **pt;
	long **pr;
	
	original=model->original;
	
	mcoord=model->coord;
	ocoord=original->coord;
		
	bytes=(model->blocks-2)*sizeof(GsCOORDUNIT);
	
	// Copy primtop pointers back to the original data area
	pt=&model->primtop[0];
	ptr=&original->block[1];
	for (d1=(model->blocks-2);d1--;) (ptr++)->primtop=*pt++;
	
	// Copy coordinate systems and sequences of this instance to the original data area
	HMD_Copy4(ocoord,mcoord,bytes);
	
	seqs=model->seqs;
	
	if (seqs)
	{
		msq=&model->seq[0];
		osq=&original->seq[0];
	
		seq=msq;
		oseq=osq;
		for (d1=seqs;d1--;)
		{
			HMD_Copy4(*oseq++,*seq++,sizeof(GsSEQ));
		}
	}
	
	// Add the model to the order table...
	ptr=original->block;
	for(d1=original->blocks;d1--;) 
	{
		// Check for a valid primitive block pointer, and make sure the primitive block
		// status bit is turned on!
		if ((int)ptr->primtop&0x80000000)
		{
			// If this block has a coordinate system, transform the coordinate system
			// to view-space.
			if (ptr->coord) 
			{
				GsGetLwsUnit(ptr->coord, matLS, matLW);
				GsSetLightMatrix(matLS);	
				GsSetLsMatrix(matLW);
			}
			// Add the primitive block to the order table
			GsSortUnit(ptr,ot,getScratchAddr(4*16));
		}
		ptr++;
	}
	
	// Copy updated coordinate systems and sequences back to the current instance
	HMD_Copy4(mcoord,ocoord,bytes);
	
	if (seqs)
	{
		seq=msq;
		oseq=osq;
		for (d1=seqs;d1--;)
		{
			HMD_Copy4(*seq++,*oseq++,sizeof(GsSEQ));
		}
	}
}

void	HMD_Add(HMD_Model *model)
{
	//TODO:	Clipping

	// TODO: Whatever this does...
	//if (cont->ASStatus)
	//	GsSetAzwh(cont->ASDepth, cont->ASMaxPolyWidth, cont->ASMaxPolyHeight);		
				
	HMD_AddModel(model, &gfxGlobs.Wot[gfxGlobs.bufID]);

	//cont->renderFlags&=~RENDER_FLAGS_CLIPPED;			
}

void	HMD_AddStatic(HMD_Model *model, int x, int y, int z, int rx, int ry, int rz,int sx,int sy,int sz)
{
	GsCOORDUNIT				*root;
	GsUNIT					*ptr;
	VECTOR					scale;
	MATRIX					*matLS=(MATRIX *)getScratchAddr(4*16);
	MATRIX					*matLW=(MATRIX *)(getScratchAddr(4*16) + sizeof(MATRIX));

	// Transform the model...
	root=model->coord + model->root;

	root->matrix.t[0]=x;
	root->matrix.t[1]=y;
	root->matrix.t[2]=z;

	root->rot.vx=rx;
	root->rot.vy=ry;
	root->rot.vz=rz;

	scale.vx=sx;
	scale.vy=sy;
	scale.vz=sz;

	RotMatrixYXZ_gte(&root->rot,&root->matrix);
	ScaleMatrix(&root->matrix,&scale);
	root->flg=0;

	// Add the model...
	ptr = model->block;
	for(d1 = model->blocks ; d1--;) 
	{ 
		// Check for a valid primitive block pointer, and make sure the primitive block	status bit is turned on!
		if ((int)ptr->primtop&0x80000000)
		{
			// If this block has a coordinate system, transform the coordinate system to view-space.
			if (ptr->coord) 
			{
				ptr->coord->flg=0;
				GsGetLwsUnit(ptr->coord, matLW, matLS);
				GsSetLightMatrix(matLW);
				GsSetLsMatrix(matLS);
			}	

			// Add the primitive block to the order table
			GsSortUnit(ptr, &gfxGlobs.Wot[gfxGlobs.bufID], getScratchAddr(4*16));
		}
		ptr++;
	}
}

void	HMD_AddStatic_Matrix(HMD_Model *model,MATRIX *matrix)
{
	GsCOORDUNIT				*root;
	GsUNIT					*ptr;
	MATRIX					*matLS=(MATRIX *)getScratchAddr(4*16);
	MATRIX					*matLW=(MATRIX *)(getScratchAddr(4*16) + sizeof(MATRIX));

	root=model->coord + model->root;
	HMD_Copy4(root->matrix,matrix,sizeof(MATRIX));
	root->flg=0;

	// Add the model...
	ptr = model->block;
	for(d1 = model->blocks ; d1--;) 
	{ 
		// Check for a valid primitive block pointer, and make sure the primitive block	status bit is turned on!
		if ((int)ptr->primtop&0x80000000)
		{
			// If this block has a coordinate system, transform the coordinate system to view-space.
			if (ptr->coord) 
			{
				ptr->coord->flg=0;
				GsGetLwsUnit(ptr->coord, matLW, matLS);
				GsSetLightMatrix(matLW);
				GsSetLsMatrix(matLS);
			}	

			// Add the primitive block to the order table
			GsSortUnit(ptr, &gfxGlobs.Wot[gfxGlobs.bufID], getScratchAddr(4*16));
		}
		ptr++;
	}
}

/*****************************************************************************************************************************************************
******************************************************************************************************************************************************
******************************************************************************************************************************************************
*****************************************************************************************************************************************************/

// Set the status of a primitive block On(EVEN)/Off(ODD)
void HMD_SetBlock(HMD_Model *model,int index,int state)
{
	u_long n;
	
	if (index<model->blocks) 
	{
		n=(u_long)model->primtop[index];
		if (n) model->primtop[index]=(unsigned long *)((n&0x7FFFFFFF)|(state<<31));
	}
}

// Rotate a coordinate system by x,y,z
void HMD_RotateCoord(HMD_Model *m,int index,int x,int y,int z)
{
	GsCOORDUNIT *ptr=&m->coord[index];
	
	ptr->rot.vx+=x;
	ptr->rot.vy+=y;
	ptr->rot.vz+=z;
	RotMatrixYXZ_gte(&ptr->rot,&ptr->matrix);
	ptr->flg=0;
}

// rotate model's root coordinate system to x,y,z
void HMD_RotateAbsoluteRoot(HMD_Model *m,int x,int y,int z)
{
	GsCOORDUNIT *ptr=&m->coord[m->root];
	
	ptr->rot.vx=x;
	ptr->rot.vy=y;
	ptr->rot.vz=z;
	RotMatrixYXZ_gte(&ptr->rot,&ptr->matrix);
	ptr->flg=0;
}

void HMD_RotateAbsolute(HMD_Model *m, int index, int x,int y,int z)
{
	GsCOORDUNIT *ptr=&m->coord[index];
	
	ptr->rot.vx=x;
	ptr->rot.vy=y;
	ptr->rot.vz=z;
	RotMatrixYXZ_gte(&ptr->rot,&ptr->matrix);
	ptr->flg=0;
}

/*
	new version, rotates in the order y/x/z
*/
void HMD_Transform(HMD_Model *m,VECTOR *translate,SVECTOR *rotate)
{
	GsCOORDUNIT *ptr=&m->coord[m->root];

	ptr->rot.vx=rotate->vx;
	ptr->rot.vy=rotate->vy;
	ptr->rot.vz=rotate->vz;
	RotMatrixYXZ_gte(&ptr->rot,&ptr->matrix);
	ptr->matrix.t[0]=translate->vx;
	ptr->matrix.t[1]=translate->vy;
	ptr->matrix.t[2]=translate->vz;
	ptr->flg=0;
}

// Translate model
void HMD_Translate(HMD_Model *m,VECTOR *translate)
{
	GsCOORDUNIT *ptr=&m->coord[m->root];

	ptr->matrix.t[0]=translate->vx;
	ptr->matrix.t[1]=translate->vy;
	ptr->matrix.t[2]=translate->vz;
	ptr->flg=0;
}

// Translate model section
void HMD_TranslateIndex(HMD_Model *m,int index,VECTOR *translate)
{
	GsCOORDUNIT *ptr=&m->coord[index];

	ptr->matrix.t[0]=translate->vx;
	ptr->matrix.t[1]=translate->vy;
	ptr->matrix.t[2]=translate->vz;
	ptr->flg=0;
}

// scale model
void HMD_Scale(HMD_Model *m,VECTOR *scale)
{
	GsCOORDUNIT *ptr=&m->coord[m->root];
	
	ScaleMatrix(&ptr->matrix,scale);
	ptr->flg=0;
}

void HMD_ScaleBlock(HMD_Model *m, int index, VECTOR *scale)
{
	GsCOORDUNIT *ptr=&m->coord[index];

	ScaleMatrix(&ptr->matrix,scale);
	ptr->flg=0;
}

/* set animation speed for model */
void HMD_SetAnimSpeed(HMD_Model *model, int speed)
{
	int i;
	GsSEQ *ptr;
	
	for (i=model->seqs;i--;)
	{
		ptr=model->seq[i];
    	ptr->speed=speed;
	}
}

void HMD_SetParent(HMD_Model *parent, HMD_Model *child)
{
	child->coord[child->root].super=&parent->coord[parent->root];
}

// Start an animation sequence, frames=HMD_LOOP for a looping animation
// Now starts with the animation you request. Note - requesting an invalid
// sid will probably cause it to go pear-shaped. You have been warned.
void HMD_StartAnim(HMD_Model *model,int sid,int frames,int speed)
{
	int i;
	GsSEQ *ptr;

	if (sid<=0)
		sid=1;

	if (sid>=model->seqs)
		sid=1;					/* default to sensible values */
	
	for (i=model->seqs;i--;)
	{
		ptr=model->seq[i];
	
    	ptr->ii=0xffff;
		ptr->ti = model->original->animIndex[(i * HMD_MAX_ANIMS)+(sid-1)];
    	ptr->aframe=frames;
    	ptr->sid=sid;
    	ptr->rframe=0;
    	ptr->speed=speed;
	}
}

// Set the SID for an entire model
void HMD_SetSID(HMD_Model *model,int sid)
{
	int i;

	for (i=model->seqs;i--;)
		model->seq[i]->sid=sid;
}

// Set the SID for an entire model, and change immediately
void HMD_SetSIDNow(HMD_Model *model,int sid)
{
	int i;
	GsSEQ *ptr;


	if (sid>=model->seqs)
		return;						/* invalid sid */

	for (i=model->seqs;i--;)
	{
		ptr=model->seq[i];
    	ptr->ii=0xffff;
		ptr->ti = model->original->animIndex[(i<<3)+(sid-1)];
    	ptr->sid=sid;
    	ptr->rframe=0;
	}
}

// Pause current animation sequence
void HMD_PauseAnim(HMD_Model *model)
{
	int i;
	GsSEQ *ptr;
	
	for (i=model->seqs;i--;)
	{
		ptr=model->seq[i];
		
		model->aframe[i]=ptr->aframe;
		ptr->aframe=0;
	}
}

// Restart current animation sequence
void HMD_UnPauseAnim(HMD_Model *model)
{
	int i;
	GsSEQ *ptr;
	
	for (i=model->seqs;i--;)
	{
		ptr=model->seq[i];
		
		ptr->aframe=model->aframe[i];
	}
}


//return current frame number for currently playing sid
int HMD_GetFrameNUm(HMD_Model *model)
{
	GsSEQ *ptr=model->seq[0];

	return	ptr->tframe;
}

int		HMD_GetNumAnimSequences(HMD_Model *hmd)
{
	GsSEQ			*seq;

	if (hmd)
	{
		seq=hmd->seq[0];
		return	seq->num;
	}
	else
		return	0;		/* no model, no anim sequences */

}

/*****************************************************************************************************************************************************
******************************************************************************************************************************************************
******************************************************************************************************************************************************
*****************************************************************************************************************************************************/
/*
typedef struct
{
	VECTOR pos;			// Position of light
	u_long radius;		// Radius (squared)
	u_char r;			// Red intensity;
	u_char g;			// Green intensity;
	u_char b;			// Blue intensity;
} 
PointLight;

#define HMD_MAXLIGHTS	8

PointLight HMD_Lights[HMD_MAXLIGHTS];

// TODO: Proper management of light sources when I get this working!

// Initialize a point light source structure
void HMD_InitLight(PointLight *light,int x,int y,int z,u_long radius,int r,int g,int b)
{
	light->pos.vx=x;
	light->pos.vy=y;
	light->pos.vz=z;
	light->radius=radius*radius;
	light->r=r;
	light->g=g;
	light->b=b;
}

void HMD_ApplyLighting(HMD_Model *model)
{
	// Assume model is previously unlit to avoid storing original intensities
	// Transform light source to local coordinate space
	// Use cut-off instead of the prefered fall-off

	long x,y,z;
	register long r,g,b,d;
	
	x=v->vx - light->pos.vx;	
	y=v->vy - light->pos.vy;
	z=v->vz - light->pos.vz;

	d=((x*x)>>12)+((y*y)>>12)+((z*z)>>12);

	r=cv->r;
	g=cv->g;
	b=cv->b;

	// all sources
	if (d < light->radius)
	{	
		r+=light->r;
		g+=light->g;
		b+=light->b;
	}

	if (r>0xFF) r=0xFF;
	if (g>0xFF) g=0xFF;
	if (b>0xFF) b=0xFF;
	cv->r=r;
	cv->g=g;
	cv->b=b;
}
*/






