
//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// HMD File For <GODS PSX>
//
// Version 1.3, Coded by Adrian Francis,
// Oct 15 '98
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ


// Include all Header Files

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
#include	"libgods.h"
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

/* NOTES:

	- Scan functions do not contain all of the primitive drivers.
	- We could define our own primitive drivers which could quite
	  possibly speed up rendering.
	  
	  - We could define primitives for point light sourcing, or
	  	even real-time environment mapping (mirror effects!).
*/

int HMD_MIMeIdx;	// Index into MIMe parameter pointer list



/*
	relocate texture for hmd model
*/
void HMD_RelocateTexture(int clut,GsARGUNIT_IMAGE *arg)
{

	/* should put some code in here I suppose */

}

// *******************************************************************
// ANIMATION 
//
// Modified update driver to correct problems with changing animation speed
//
// *******************************************************************

typedef struct 
{
	u_long	*base;
	u_long	*src;
	u_long	*dst;
	u_long	*intr;
} GsARGANIM_OPAQ;


/*
#define DEBUG
*/

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

static u_short
get_tctr(u_short idx, DWORD *p, GsSEQ *seq)
{
	int	dir = seq->speed < 0 ? -1 : 1;
	DWORD	dw;

	while (dw = p[idx], IS_NOT_NORM(dw)) {
		if (IS_JUMP(dw)) {
			int	cnd = SID_CND(dw);

			if (cnd == 0 || seq->sid == cnd) {
				int	dst = SID_DST(dw);

				if (cnd != 0 || dst != 0) {
					seq->sid = dst;
				}
				idx = SEQ_IDX(dw);
				continue;
			}
		} else if (IS_CTRL(dw)) {
			int	cnd = P1(dw);

			if (CODE(dw) == CODE_END
			&& (cnd == 0 || seq->sid == cnd)) {
				return 0xffff;		/* END CODE */
			}
		} else {
		//	assert(FALSE);
		}
		idx += dir;
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
	for (base = &sp->primp[1], i = 0;i < wnum; i++, base += base[1] & 0xffff)
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
// *******************************************************************
// *******************************************************************
// *******************************************************************

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
  	
  	rframe=seq->rframe;
  	tframe=seq->tframe;
  	dframe=tframe-rframe;
  
  	inv_tframe=0x1000/tframe;
  
  	dtop=(GsCOORDUNIT *)((u_long *)(*(&(sp0->header_size)+ofs0))+ofs1);
 	dtop->matrix.t[0]=((src->tx*rframe+dst->tx*dframe)*inv_tframe)>>12;
  	dtop->matrix.t[1]=((src->ty*rframe+dst->ty*dframe)*inv_tframe)>>12;
  	dtop->matrix.t[2]=((src->tz*rframe+dst->tz*dframe)*inv_tframe)>>12;
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
  	
  	rframe=seq->rframe;
  	tframe=seq->tframe;
  	dframe=tframe-rframe;
  
  	inv_tframe=0x1000/tframe;
  
  	dtop=(GsCOORDUNIT *)((u_long *)(*(&(sp0->header_size)+ofs0))+ofs1);
 	dtop->rot.vx=((src->rx*rframe+dst->rx*dframe)*inv_tframe)>>12;
  	dtop->rot.vy=((src->ry*rframe+dst->ry*dframe)*inv_tframe)>>12;
  	dtop->rot.vz=((src->rz*rframe+dst->rz*dframe)*inv_tframe)>>12;
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

// Primitive scan functions

void HMD_InitializeMIMe(u_long type,u_long *header,HMD_Model *model)
{
	long	**qMIMePr;
	u_long	nMIMeNum;

	// Get number of MIMe parameters, and the parameter pointer
	switch (type) 
	{
		case GsVtxMIMe:
		case GsNrmMIMe:
			qMIMePr = (long **)&header[1];
			nMIMeNum = header[2];
			break;
		case GsJntAxesMIMe:
		case GsJntRPYMIMe:
			qMIMePr = (long **)&header[2];
			nMIMeNum = header[3];
	}

	// Store parameter pointer for later initialization 
	if (*qMIMePr == 0) model->MIMeParam[HMD_MIMeIdx++]=(long)qMIMePr;
	
	// Update number of MIMe parameters
	if (nMIMeNum > model->MIMeParams) model->MIMeParams=nMIMeNum;
}

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
	  printf("No support for animation type 0x%08x\n",ut.type);
	}
    }
}

int HMD_ScanPoly(GsTYPEUNIT *ut, GsSEQ **seq,HMD_Model *model)
{
    int anum = 0;
    
    switch(ut->type) 
    {
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
//    case GsUFF3:	// Fogged flat triangle
//		*(ut->ptr) = (u_long)GsU_00020008;
//		break;
//    case GsUFFT3: 	// Fogged flat textured triangle
//		*(ut->ptr) = (u_long)GsU_00020009;
//		break;
//    case GsUFG3:	// Fogged gouraud triangle
//		*(ut->ptr) = (u_long)GsU_0002000c;
//		break;
//    case GsUFGT3:	// Fogged gouraud textured triangle
//		*(ut->ptr) = (u_long)GsU_0002000d;
//		break;
//    case GsUFF4:	// Fogged flat quad
//		*(ut->ptr) = (u_long)GsU_00020010;
//		break;
//    case GsUFFT4:	// Fogged flat textured quad
//		*(ut->ptr) = (u_long)GsU_00020011;
//		break;
//    case GsUFG4:	// Fogged gouraud quad
//		*(ut->ptr) = (u_long)GsU_00020014;
//		break;
//    case GsUFGT4:	// Fogged gouraud textured quad
//		*(ut->ptr) = (u_long)GsU_00020015;
//		break;
//    case GsUCF3:	// Coloured flat triangle
//		*(ut->ptr) = (u_long)GsU_0000000a;
//		break;
//    case GsUCFT3: 	// Coloured flat textured triangle
//		*(ut->ptr) = (u_long)GsU_0000000b;
//		break;
//    case GsUCG3:	// Coloured gouraud triangle
//		*(ut->ptr) = (u_long)GsU_0000000e;
//		break;
//    case GsUCGT3:	// Coloured gouraud textured triangle
//		*(ut->ptr) = (u_long)GsU_0000000f;
//		break;
//   case GsUCF4:	// Coloured flat quad
//		*(ut->ptr) = (u_long)GsU_00000012;
//		break;
//    case GsUCFT4:	// Coloured flat textured quad
//		*(ut->ptr) = (u_long)GsU_00000013;
//		break;
//    case GsUCG4:	// Coloured gouraud quad
//		*(ut->ptr) = (u_long)GsU_00000016;
//		break;
//    case GsUCGT4:	// Coloured gouraud textured quad
//		*(ut->ptr) = (u_long)GsU_00000017;
//		break;
//    case GsUNF3: 	// Unlit flat triangle
//		*(ut->ptr) = (u_long)GsU_00040048;
//		break;
//    case GsUNFT3: 	// Unlit flat textured triangle
//		*(ut->ptr) = (u_long)GsU_00040049;
//		break;
//    case GsUNG3: 	// Unlit gouraud triangle
//		*(ut->ptr) = (u_long)GsU_0004004c;
//		break;
//    case GsUNGT3: 	// Unlit gouraud textured triangle
//		*(ut->ptr) = (u_long)GsU_0004004d;
//		break;
//    case GsUNF4: 	// Unlit flat quad
//		*(ut->ptr) = (u_long)GsU_00040050;
//		break;
//    case GsUNFT4: 	// Unlit flat textured quad
//		*(ut->ptr) = (u_long)GsU_00040051;
//		break;
//    case GsUNG4: 	// Unlit gouraud quad
//		*(ut->ptr) = (u_long)GsU_00040054;
//		break;
//    case GsUNGT4: 	// Unlit gouraud textured quad
//		*(ut->ptr) = (u_long)GsU_00040055;
//		break;
//    case GsUDF3:	// Subdivided flat triangle
//		*(ut->ptr) = (u_long)GsU_00010008;
//		break;
//    case GsUDFT3: 	// Subdivided flat textured triangle
//		*(ut->ptr) = (u_long)GsU_00010009;
//		break;
//    case GsUDG3:	// Subdivided gouruad triangle
//		*(ut->ptr) = (u_long)GsU_0001000c;
//		break;
//    case GsUDGT3:	// Subdivided gouraud textured triangle
//		*(ut->ptr) = (u_long)GsU_0001000d;
//		break;
//    case GsUDF4:	// Subdivided flat quad
//		*(ut->ptr) = (u_long)GsU_00010010;
//		break;
//    case GsUDFT4:	// Subdivided flat textured quad
//		*(ut->ptr) = (u_long)GsU_00010011;
//		break;
//    case GsUDG4:	// Subdivided gouraud quad
//		*(ut->ptr) = (u_long)GsU_00010014;
//		break;
//    case GsUDGT4:	// Subdivided gouraud textured quad
//		*(ut->ptr) = (u_long)GsU_00010015;
//		break;
//    case GsUDFF3:	// Subdivided fogged flat quad
//		*(ut->ptr) = (u_long)GsU_00030008;
//		break;
//    case GsUDFFT3: 	// Subdivided fogged flat textured quad
//		*(ut->ptr) = (u_long)GsU_00030009;
//		break;
//    case GsUDFG3:	// Subdivided fogged gouraud quad
//		*(ut->ptr) = (u_long)GsU_0003000c;
//		break;
//    case GsUDFGT3:	// Subdivided fogged gouraud textured quad
//		*(ut->ptr) = (u_long)GsU_0003000d;
//		break;
//    case GsUDFF4:	// Subdivided fogged flat quad
//		*(ut->ptr) = (u_long)GsU_00030010;
//		break;
//    case GsUDFFT4:	// Subdivided fogged flat textured quad
//		*(ut->ptr) = (u_long)GsU_00030011;
//		break;
//    case GsUDFG4:	// Subdivided fogged gouraud quad
//		*(ut->ptr) = (u_long)GsU_00030014;
//		break;
//    case GsUDFGT4:	// Subdivided fogged gouraud textured quad
//		*(ut->ptr) = (u_long)GsU_00030015;
//		break;
//    case GsUDNF3: 	// Subdivided unlit flat triangle
//		*(ut->ptr) = (u_long)GsU_00050048;
//		break;
//    case GsUDNFT3: 	// Subdivided unlit flat textured triangle
//		*(ut->ptr) = (u_long)GsU_00050049;
//		break;
//    case GsUDNG3: 	// Subdivided unlit gouraud triangle
//		*(ut->ptr) = (u_long)GsU_0005004c;
//		break;
//    case GsUDNGT3: 	// Subdivided unlit gouraud textured triangle
//		*(ut->ptr) = (u_long)GsU_0005004d;
//		break;
//    case GsUDNF4: 	// Subdivided unlit flat quad
//		*(ut->ptr) = (u_long)GsU_00050050;
//		break;
//    case GsUDNFT4: 	// Subdivided unlit flat textured quad
//		*(ut->ptr) = (u_long)GsU_00050051;
//		break;
//    case GsUDNG4: 	// Subdivided unlit gouraud quad
//		*(ut->ptr) = (u_long)GsU_00050054;
//		break;
//    case GsUDNGT4: 	// Subdivided unlit gouraud textured quad
//		*(ut->ptr) = (u_long)GsU_00050055;
//		break;
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
//    case GsUSNF3:	// Shared unlit flat tiangle
//		*(ut->ptr) = (u_long)GsU_01040048;
//		break;
//    case GsUSNFT3:	// Shared unlit flat textured triangle
//		*(ut->ptr) = (u_long)GsU_01040049;
//		break;
//    case GsUSNG3:	// Shared unlit gouraud triangle
//		*(ut->ptr) = (u_long)GsU_0104004c;
//		break;
//    case GsUSNGT3:	// Shared unlit gouraud textured triangle
//		*(ut->ptr) = (u_long)GsU_0104004d;
//		break;
//    case GsUSNF4:	// Shared unlit flat quad
//		*(ut->ptr) = (u_long)GsU_01040050;
//		break;
//    case GsUSNFT4:	// Shared unlit flat textured quad
//		*(ut->ptr) = (u_long)GsU_01040051;
//		break;
//    case GsUSNG4:	// Shared unlit gouraud quad
//		*(ut->ptr) = (u_long)GsU_01040054;
//		break;
//    case GsUSNGT4:	// Shared unlit gouraud textured quad
//		*(ut->ptr) = (u_long)GsU_01040055;
//		break;
//    case GsUMF3:	// Mesh flat triangle
//		*(ut->ptr) = (u_long)GsU_00000018;
//		break;
//    case GsUMFT3:	// Mesh flat textured triangle
//		*(ut->ptr) = (u_long)GsU_00000019;
//		break;
//    case GsUMG3:	// Mesh gouraud triangle
//		*(ut->ptr) = (u_long)GsU_0000001c;
//		break;
//    case GsUMGT3:	// Mesh gouraud textured triangle
//		*(ut->ptr) = (u_long)GsU_0000001d;
//		break;
//    case GsUMNF3:	// Mesh unlit flat triangle
//		*(ut->ptr) = (u_long)GsU_00040058;
//		break;
//    case GsUMNFT3:	// Mesh unlit flat textured triangle
//		*(ut->ptr) = (u_long)GsU_00040059;
//		break;
//    case GsUMNG3:	// Mesh unlit gouraud triangle
//		*(ut->ptr) = (u_long)GsU_0004005c;
//		break;
//    case GsUMNGT3:	// Mesh unlit gouraud textured triangle
//		*(ut->ptr) = (u_long)GsU_0004005d;
//		break;
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
//    case GsUPNF3:	// Preset unlit flat triangle
//		*(ut->ptr) = (u_long)GsU_00040148;
//		break;
//    case GsUPNFT3:	// Preset unlit flat textured triangle
//		*(ut->ptr) = (u_long)GsU_00040149;
//		break;
//    case GsUPNG3:	// Preset unlit gouraud triangle
//		*(ut->ptr) = (u_long)GsU_0004014c;
//		break;
//    case GsUPNGT3:	// Preset unlit gouraud textured triangle
//		*(ut->ptr) = (u_long)GsU_0004014d;
//		break;
//    case GsUPNF4:	// Preset unlit flat quad
//		*(ut->ptr) = (u_long)GsU_00040150;
//		break;
//    case GsUPNFT4:	// Preset unlit flat textured quad
//		*(ut->ptr) = (u_long)GsU_00040151;
//		break;
//    case GsUPNG4:	// Preset unlit gouraud quad
//		*(ut->ptr) = (u_long)GsU_00040154;
//		break;
//    case GsUPNGT4:	// Preset unlit gouraud textured quad
//		*(ut->ptr) = (u_long)GsU_00040155;
//		break;

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

//    case GsUSTPSG3:	// Semi transparent shared gouraud triangle
//			*(ut->ptr) = (u_long)GsU_0120000c;
//			break;
//    case GsUSTPSGT3:// Semi transparent shared gouraud textured triangle
//			*(ut->ptr) = (u_long)GsU_0120000d;
//			break;
//    case GsUSTPSG4:	// Semi transparent shared gouraud quad
//			*(ut->ptr) = (u_long)GsU_01200014;
//			break;
//    case GsUSTPSGT4:// Semi transparent shared gouraud textured quad	
//			*(ut->ptr) = (u_long)GsU_01200015;
//			break;

//    case GsUGNDF:	// Ground flat
//		*(ut->ptr) = (u_long)GsU_05000000;
//		break;
//    case GsUGNDFT:	// Ground textured flat
//		*(ut->ptr) = (u_long)GsU_05000001;
//		break;

    case GsUIMG0:	// Image with no CLUT
		*(ut->ptr) = (u_long)GsU_00000000;
		HMD_RelocateTexture(0,(GsARGUNIT_IMAGE *)getScratchAddr(0));
		GsU_02000000((GsARGUNIT *)getScratchAddr(0));
		break;
    case GsUIMG1:	// Image with CLUT
		*(ut->ptr) = (u_long)GsU_00000000;
		HMD_RelocateTexture(1,(GsARGUNIT_IMAGE *)getScratchAddr(0));
		GsU_02000001((GsARGUNIT *)getScratchAddr(0));
		break;

//	case GsVtxMIMe:			// Vertex MIMe
//		*(ut->ptr) = (u_long)GsU_04010020;
//		HMD_InitializeMIMe(ut->type, GsGetHeadpUnit(),model);
//		break;
//	case GsRstVtxMIMe:		// Reset vertex MIMe
//		*(ut->ptr) = (u_long)GsU_04010028;
//		GsInitRstVtxMIMe(ut->ptr,  GsGetHeadpUnit());
//		break;
//	case GsNrmMIMe:			// Normal MIMe
//		*(ut->ptr) = (u_long)GsU_04010021;
//		HMD_InitializeMIMe(ut->type, GsGetHeadpUnit(),model);
//		break;
//	case GsRstNrmMIMe:		// Reset normal MIMe
//		*(ut->ptr) = (u_long)GsU_04010029;
//		GsInitRstNrmMIMe(ut->ptr, GsGetHeadpUnit());
//		break;
//	case GsJntAxesMIMe:		// Joint axes MIMe
//		*(ut->ptr) = (u_long)GsU_04010010;
//		HMD_InitializeMIMe(ut->type, GsGetHeadpUnit(),model);
//		break;
//	case GsRstJntAxesMIMe:	// Reset joint axes MIMe
//		*(ut->ptr) = (u_long)GsU_04010018;
//		break;
//	case GsJntRPYMIMe:		// Joint roll,pitch,yaw MIMe
//		*(ut->ptr) = (u_long)GsU_04010011;
//		HMD_InitializeMIMe(ut->type, GsGetHeadpUnit(),model);
//		break;
//	case GsRstJntRPYMIMe:	// Reset joint roll,pitch,yaw MIMe
//		*(ut->ptr) = (u_long)GsU_04010019;
//		break;

    case 0x03800000:// Animation scan	
		*(ut->ptr) = (u_long)HMD_03000000;
		anum = GsLinkAnim(seq,ut->ptr);
		if(GsScanAnim(ut->ptr,0)==0)
	   	{
			printf("ScanAnim failed!!\n\n");
			break;
	    }
		HMD_ScanAnim();
		break;
    default:		// Unknown type
		*(ut->ptr) = (u_long)GsU_00000000;
		printf("Unknown type:0x%08x\n",ut->type);
    }
    return anum;
}

#ifdef 0
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
	case 0x03000002:	/* translation bezier (32bit) */
	  	*(ut.ptr) = (u_long)GsU_03000002;
	  	break;
	case 0x03000003:	/* translation bsprine (32bit) */
	  	*(ut.ptr) = (u_long)GsU_03000003;
	  	break;
	case 0x03000009:	/* translation linear (16bit) */
	  	*(ut.ptr) = (u_long)GsU_03000009;
	  	break;
	case 0x0300000a:	/* translation bezier (16bit) */
	  	*(ut.ptr) = (u_long)GsU_0300000a;
	  	break;
	case 0x0300000b:	/* translation bsprine (16bit) */
	  	*(ut.ptr) = (u_long)GsU_0300000b;
	  	break;
	case 0x03000010:	/* rotation linear */
	  	*(ut.ptr) = (u_long)HMD_03000010;
	  	break;
	case 0x03000011:	/* rotation linear translation linear (32bit)*/
	  	*(ut.ptr) = (u_long)HMD_03000011;
	  	break;
	case 0x03000012:	/* rotation linear translation bezier (32bit)*/
	  	*(ut.ptr) = (u_long)GsU_03000012;
	  	break;
	case 0x03000013:	/* rotation linear translation bsprine(32bit)*/
	  	*(ut.ptr) = (u_long)GsU_03000013;
	  	break;
	case 0x03000019:	/* rotation linear translation linear(16bit)*/
	  	*(ut.ptr) = (u_long)GsU_03000019;
	  	break;
	case 0x0300001a:	/* rotation linear translation bezier(16bit)*/
	  	*(ut.ptr) = (u_long)GsU_0300001a;
	  	break;
	case 0x0300001b:	/* rotation linear translation bsprine(16bit)*/
	  	*(ut.ptr) = (u_long)GsU_0300001b;
	  	break;
	case 0x03000020:	/* rotation bezier */
	  	*(ut.ptr) = (u_long)GsU_03000020;
	  	break;
	case 0x03000021:	/* rotation bezier translation linear (32bit)*/
	  	*(ut.ptr) = (u_long)GsU_03000021;
	  	break;
	case 0x03000022:	/* rotation bezier translation bezier (32bit)*/
	  	*(ut.ptr) = (u_long)GsU_03000022;
	  	break;
	case 0x03000023:	/* rotation bezier translation bsprine(32bit)*/
	  	*(ut.ptr) = (u_long)GsU_03000023;
	  	break;
	case 0x03000029:	/* rotation bezier translation linear(16bit)*/
	  	*(ut.ptr) = (u_long)GsU_03000029;
	  	break;
	case 0x0300002a:	/* rotation bezier translation bezier(16bit)*/
	  	*(ut.ptr) = (u_long)GsU_0300002a;
	  	break;
	case 0x0300002b:	/* rotation bezier translation bsprine(16bit)*/
	  	*(ut.ptr) = (u_long)GsU_0300002b;
	  	break;
	case 0x03000030:	/* rotation bsprine */
	  	*(ut.ptr) = (u_long)GsU_03000030;
	  	break;
	case 0x03000031:	/* rotation bsprine translation linear (32bit)*/
	  	*(ut.ptr) = (u_long)GsU_03000031;
	  	break;
	case 0x03000032:	/* rotation bsprine translation bezier (32bit)*/
	  	*(ut.ptr) = (u_long)GsU_03000032;
	  	break;
	case 0x03000033:	/* rotation bsprine translation bsprine(32bit)*/
	  	*(ut.ptr) = (u_long)GsU_03000033;
	  	break;
	case 0x03000039:	/* rotation bsprine translation linear(16bit)*/
	  	*(ut.ptr) = (u_long)GsU_03000039;
	  	break;
	case 0x0300003a:	/* rotation bsprine translation bezier(16bit)*/
	  	*(ut.ptr) = (u_long)GsU_0300003a;
	  	break;
	case 0x0300003b:	/* rotation bsprine translation bsprine(16bit)*/
	  	*(ut.ptr) = (u_long)GsU_0300003b;
	  	break;
	case 0x03000909:	/* scale(one) translation(short) linear */
	  	*(ut.ptr) = (u_long)GsU_03000909;
	  	break;
	case 0x03000100:	/* scale linear */
	  	*(ut.ptr) = (u_long)GsU_03000100;
	  	break;
	case 0x03000910:	/* scale(one) rotation linear */
	  	*(ut.ptr) = (u_long)GsU_03000910;
	  	break;
	case 0x03000911:	/* scale(one) translation roation linear */
	  	*(ut.ptr) = (u_long)GsU_03000911;
	  	break;
	case 0x03000111:	/* scale translation rotation linear */
	  	*(ut.ptr) = (u_long)GsU_03000111;
	  	break;
	case 0x03000119:	/* scale translation(short) rotation linear */
	  	*(ut.ptr) = (u_long)GsU_03000119;
	  	break;
	case 0x03010110:	/* general linear (32bit) */
		*(ut.ptr) = (u_long)GsU_03010110;
	    break;
	case 0x03010111:	/* general linear (16bit offset0) */
	    *(ut.ptr) = (u_long)GsU_03010111;
	    break;
	case 0x03010121: 	/* general linear (16bit offset1) */
	    *(ut.ptr) = (u_long)GsU_03010121;
	    break;
	case 0x03010141: 	/* general linear (16bit offset2) */
	    *(ut.ptr) = (u_long)GsU_03010141;
	    break;
	case 0x03010171:	/* general linear (16bit Vector) */
	    *(ut.ptr) = (u_long)GsU_03010171;
	    break;
	case 0x03010112:	/* general linear (8bit offset0) */
	    *(ut.ptr) = (u_long)GsU_03010112;
	    break;
	case 0x03010122:	/* general linear (8bit offset1) */
	    *(ut.ptr) = (u_long)GsU_03010122;
	    break;
	case 0x03010142:	/* general linear (8bit offset2) */
	    *(ut.ptr) = (u_long)GsU_03010142;
	    break;
	case 0x03010182:	/* general linear (8bit offset3) */
	    *(ut.ptr) = (u_long)GsU_03010182;
	    break;
	case 0x03010172:	/* general linear (8bit Vector) */
	    *(ut.ptr) = (u_long)GsU_03010172;
	    break;
	case 0x03010210:	/* general bezier (32bit) */
	    *(ut.ptr) = (u_long)GsU_03010210;
	    break;
	case 0x03010211:	/* general bezier (16bit offset0) */
	    *(ut.ptr) = (u_long)GsU_03010211;
	    break;
	case 0x03010221:	/* general bezier (16bit offset1) */
	    *(ut.ptr) = (u_long)GsU_03010221;
	    break;
	case 0x03010241:	/* general bezier (16bit offset2) */
	    *(ut.ptr) = (u_long)GsU_03010241;
	    break;
	case 0x03010271:	/* general bezier (16bit Vector) */
	    *(ut.ptr) = (u_long)GsU_03010271;
	    break;
	case 0x03010212:	/* general bezier (8bit offset0) */
	    *(ut.ptr) = (u_long)GsU_03010212;
	    break;
	case 0x03010222:	/* general bezier (8bit offset1) */
	    *(ut.ptr) = (u_long)GsU_03010222;
	    break;
	case 0x03010242:	/* general bezier (8bit offset2) */
	    *(ut.ptr) = (u_long)GsU_03010242;
	    break;
	case 0x03010272:	/* general bezier (8bit Vector) */
	    *(ut.ptr) = (u_long)GsU_03010272;
	    break;
	case 0x03010310:	/* general bsprine (32bit) */
	    *(ut.ptr) = (u_long)GsU_03010310;
	    break;
	case 0x03010311:	/* general bsprine (16bit offset0) */
	    *(ut.ptr) = (u_long)GsU_03010311;
	    break;
	case 0x03010321:	/* general bsprine (16bit offset1) */
	    *(ut.ptr) = (u_long)GsU_03010321;
	    break;
	case 0x03010341:	/* general bsprine (16bit offset2) */
	    *(ut.ptr) = (u_long)GsU_03010341;
	    break;
	case 0x03010371:	/* general bsprine (16bit Vector) */
	    *(ut.ptr) = (u_long)GsU_03010371;
	    break;
	case 0x03010312:	/* general bsprine (8bit offset0) */
	    *(ut.ptr) = (u_long)GsU_03010312;
	    break;
	case 0x03010322:	/* general bsprine (8bit offset1) */
	    *(ut.ptr) = (u_long)GsU_03010322;
	    break;
	case 0x03010342:	/* general bsprine (8bit offset2) */
	    *(ut.ptr) = (u_long)GsU_03010342;
	    break;
	case 0x03010372:	/* general bsprine (8bit Vector) */
	    *(ut.ptr) = (u_long)GsU_03010372;
	    break;
	default:
	    *(ut.ptr) = (u_long)GsU_03000000;
	  printf("No support for animation type 0x%08x\n",ut.type);
	}
    }
}

int HMD_ScanPoly(GsTYPEUNIT *ut, GsSEQ **seq,HMD_Model *model)
{
    int anum = 0;
    
    switch(ut->type) 
    {
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
    case GsUCF3:	// Coloured flat triangle
		*(ut->ptr) = (u_long)GsU_0000000a;
		break;
    case GsUCFT3: 	// Coloured flat textured triangle
		*(ut->ptr) = (u_long)GsU_0000000b;
		break;
    case GsUCG3:	// Coloured gouraud triangle
		*(ut->ptr) = (u_long)GsU_0000000e;
		break;
    case GsUCGT3:	// Coloured gouraud textured triangle
		*(ut->ptr) = (u_long)GsU_0000000f;
		break;
    case GsUCF4:	// Coloured flat quad
		*(ut->ptr) = (u_long)GsU_00000012;
		break;
    case GsUCFT4:	// Coloured flat textured quad
		*(ut->ptr) = (u_long)GsU_00000013;
		break;
    case GsUCG4:	// Coloured gouraud quad
		*(ut->ptr) = (u_long)GsU_00000016;
		break;
    case GsUCGT4:	// Coloured gouraud textured quad
		*(ut->ptr) = (u_long)GsU_00000017;
		break;
    case GsUNF3: 	// Unlit flat triangle
		*(ut->ptr) = (u_long)GsU_00040048;
		break;
    case GsUNFT3: 	// Unlit flat textured triangle
		*(ut->ptr) = (u_long)GsU_00040049;
		break;
    case GsUNG3: 	// Unlit gouraud triangle
		*(ut->ptr) = (u_long)GsU_0004004c;
		break;
    case GsUNGT3: 	// Unlit gouraud textured triangle
		*(ut->ptr) = (u_long)GsU_0004004d;
		break;
    case GsUNF4: 	// Unlit flat quad
		*(ut->ptr) = (u_long)GsU_00040050;
		break;
    case GsUNFT4: 	// Unlit flat textured quad
		*(ut->ptr) = (u_long)GsU_00040051;
		break;
    case GsUNG4: 	// Unlit gouraud quad
		*(ut->ptr) = (u_long)GsU_00040054;
		break;
    case GsUNGT4: 	// Unlit gouraud textured quad
		*(ut->ptr) = (u_long)GsU_00040055;
		break;
    case GsUDF3:	// Subdivided flat triangle
		*(ut->ptr) = (u_long)GsU_00010008;
		break;
    case GsUDFT3: 	// Subdivided flat textured triangle
		*(ut->ptr) = (u_long)GsU_00010009;
		break;
    case GsUDG3:	// Subdivided gouruad triangle
		*(ut->ptr) = (u_long)GsU_0001000c;
		break;
    case GsUDGT3:	// Subdivided gouraud textured triangle
		*(ut->ptr) = (u_long)GsU_0001000d;
		break;
    case GsUDF4:	// Subdivided flat quad
		*(ut->ptr) = (u_long)GsU_00010010;
		break;
    case GsUDFT4:	// Subdivided flat textured quad
		*(ut->ptr) = (u_long)GsU_00010011;
		break;
    case GsUDG4:	// Subdivided gouraud quad
		*(ut->ptr) = (u_long)GsU_00010014;
		break;
    case GsUDGT4:	// Subdivided gouraud textured quad
		*(ut->ptr) = (u_long)GsU_00010015;
		break;
    case GsUDFF3:	// Subdivided fogged flat quad
		*(ut->ptr) = (u_long)GsU_00030008;
		break;
    case GsUDFFT3: 	// Subdivided fogged flat textured quad
		*(ut->ptr) = (u_long)GsU_00030009;
		break;
    case GsUDFG3:	// Subdivided fogged gouraud quad
		*(ut->ptr) = (u_long)GsU_0003000c;
		break;
    case GsUDFGT3:	// Subdivided fogged gouraud textured quad
		*(ut->ptr) = (u_long)GsU_0003000d;
		break;
    case GsUDFF4:	// Subdivided fogged flat quad
		*(ut->ptr) = (u_long)GsU_00030010;
		break;
    case GsUDFFT4:	// Subdivided fogged flat textured quad
		*(ut->ptr) = (u_long)GsU_00030011;
		break;
    case GsUDFG4:	// Subdivided fogged gouraud quad
		*(ut->ptr) = (u_long)GsU_00030014;
		break;
    case GsUDFGT4:	// Subdivided fogged gouraud textured quad
		*(ut->ptr) = (u_long)GsU_00030015;
		break;
    case GsUDNF3: 	// Subdivided unlit flat triangle
		*(ut->ptr) = (u_long)GsU_00050048;
		break;
    case GsUDNFT3: 	// Subdivided unlit flat textured triangle
		*(ut->ptr) = (u_long)GsU_00050049;
		break;
    case GsUDNG3: 	// Subdivided unlit gouraud triangle
		*(ut->ptr) = (u_long)GsU_0005004c;
		break;
    case GsUDNGT3: 	// Subdivided unlit gouraud textured triangle
		*(ut->ptr) = (u_long)GsU_0005004d;
		break;
    case GsUDNF4: 	// Subdivided unlit flat quad
		*(ut->ptr) = (u_long)GsU_00050050;
		break;
    case GsUDNFT4: 	// Subdivided unlit flat textured quad
		*(ut->ptr) = (u_long)GsU_00050051;
		break;
    case GsUDNG4: 	// Subdivided unlit gouraud quad
		*(ut->ptr) = (u_long)GsU_00050054;
		break;
    case GsUDNGT4: 	// Subdivided unlit gouraud textured quad
		*(ut->ptr) = (u_long)GsU_00050055;
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
    case GsUSNF3:	// Shared unlit flat tiangle
		*(ut->ptr) = (u_long)GsU_01040048;
		break;
    case GsUSNFT3:	// Shared unlit flat textured triangle
		*(ut->ptr) = (u_long)GsU_01040049;
		break;
    case GsUSNG3:	// Shared unlit gouraud triangle
		*(ut->ptr) = (u_long)GsU_0104004c;
		break;
    case GsUSNGT3:	// Shared unlit gouraud textured triangle
		*(ut->ptr) = (u_long)GsU_0104004d;
		break;
    case GsUSNF4:	// Shared unlit flat quad
		*(ut->ptr) = (u_long)GsU_01040050;
		break;
    case GsUSNFT4:	// Shared unlit flat textured quad
		*(ut->ptr) = (u_long)GsU_01040051;
		break;
    case GsUSNG4:	// Shared unlit gouraud quad
		*(ut->ptr) = (u_long)GsU_01040054;
		break;
    case GsUSNGT4:	// Shared unlit gouraud textured quad
		*(ut->ptr) = (u_long)GsU_01040055;
		break;
    case GsUMF3:	// Mesh flat triangle
		*(ut->ptr) = (u_long)GsU_00000018;
		break;
    case GsUMFT3:	// Mesh flat textured triangle
		*(ut->ptr) = (u_long)GsU_00000019;
		break;
    case GsUMG3:	// Mesh gouraud triangle
		*(ut->ptr) = (u_long)GsU_0000001c;
		break;
    case GsUMGT3:	// Mesh gouraud textured triangle
		*(ut->ptr) = (u_long)GsU_0000001d;
		break;
    case GsUMNF3:	// Mesh unlit flat triangle
		*(ut->ptr) = (u_long)GsU_00040058;
		break;
    case GsUMNFT3:	// Mesh unlit flat textured triangle
		*(ut->ptr) = (u_long)GsU_00040059;
		break;
    case GsUMNG3:	// Mesh unlit gouraud triangle
		*(ut->ptr) = (u_long)GsU_0004005c;
		break;
    case GsUMNGT3:	// Mesh unlit gouraud textured triangle
		*(ut->ptr) = (u_long)GsU_0004005d;
		break;
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
    case GsUPNF3:	// Preset unlit flat triangle
		*(ut->ptr) = (u_long)GsU_00040148;
		break;
    case GsUPNFT3:	// Preset unlit flat textured triangle
		*(ut->ptr) = (u_long)GsU_00040149;
		break;
    case GsUPNG3:	// Preset unlit gouraud triangle
		*(ut->ptr) = (u_long)GsU_0004014c;
		break;
    case GsUPNGT3:	// Preset unlit gouraud textured triangle
		*(ut->ptr) = (u_long)GsU_0004014d;
		break;
    case GsUPNF4:	// Preset unlit flat quad
		*(ut->ptr) = (u_long)GsU_00040150;
		break;
    case GsUPNFT4:	// Preset unlit flat textured quad
		*(ut->ptr) = (u_long)GsU_00040151;
		break;
    case GsUPNG4:	// Preset unlit gouraud quad
		*(ut->ptr) = (u_long)GsU_00040154;
		break;
    case GsUPNGT4:	// Preset unlit gouraud textured quad
		*(ut->ptr) = (u_long)GsU_00040155;
		break;
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
    case GsUSTPSG3:	// Semi transparent shared gouraud triangle
		*(ut->ptr) = (u_long)GsU_0120000c;
		break;
    case GsUSTPSGT3:// Semi transparent shared gouraud textured triangle
		*(ut->ptr) = (u_long)GsU_0120000d;
		break;
    case GsUSTPSG4:	// Semi transparent shared gouraud quad
		*(ut->ptr) = (u_long)GsU_01200014;
		break;
    case GsUSTPSGT4:// Semi transparent shared gouraud textured quad	
		*(ut->ptr) = (u_long)GsU_01200015;
		break;
    case GsUGNDF:	// Ground flat
		*(ut->ptr) = (u_long)GsU_05000000;
		break;
    case GsUGNDFT:	// Ground textured flat
		*(ut->ptr) = (u_long)GsU_05000001;
		break;
    case GsUIMG0:	// Image with no CLUT
		*(ut->ptr) = (u_long)GsU_00000000;
		HMD_RelocateTexture(0,(GsARGUNIT_IMAGE *)getScratchAddr(0));
		GsU_02000000((GsARGUNIT *)getScratchAddr(0));
		break;
    case GsUIMG1:	// Image with CLUT
		*(ut->ptr) = (u_long)GsU_00000000;
		HMD_RelocateTexture(1,(GsARGUNIT_IMAGE *)getScratchAddr(0));
		GsU_02000001((GsARGUNIT *)getScratchAddr(0));
		break;
	case GsVtxMIMe:			// Vertex MIMe
		*(ut->ptr) = (u_long)GsU_04010020;
		HMD_InitializeMIMe(ut->type, GsGetHeadpUnit(),model);
		break;
	case GsRstVtxMIMe:		// Reset vertex MIMe
		*(ut->ptr) = (u_long)GsU_04010028;
		GsInitRstVtxMIMe(ut->ptr,  GsGetHeadpUnit());
		break;
	case GsNrmMIMe:			// Normal MIMe
		*(ut->ptr) = (u_long)GsU_04010021;
		HMD_InitializeMIMe(ut->type, GsGetHeadpUnit(),model);
		break;
	case GsRstNrmMIMe:		// Reset normal MIMe
		*(ut->ptr) = (u_long)GsU_04010029;
		GsInitRstNrmMIMe(ut->ptr, GsGetHeadpUnit());
		break;
	case GsJntAxesMIMe:		// Joint axes MIMe
		*(ut->ptr) = (u_long)GsU_04010010;
		HMD_InitializeMIMe(ut->type, GsGetHeadpUnit(),model);
		break;
	case GsRstJntAxesMIMe:	// Reset joint axes MIMe
		*(ut->ptr) = (u_long)GsU_04010018;
		break;
	case GsJntRPYMIMe:		// Joint roll,pitch,yaw MIMe
		*(ut->ptr) = (u_long)GsU_04010011;
		HMD_InitializeMIMe(ut->type, GsGetHeadpUnit(),model);
		break;
	case GsRstJntRPYMIMe:	// Reset joint roll,pitch,yaw MIMe
		*(ut->ptr) = (u_long)GsU_04010019;
		break;
    case 0x03800000:// Animation scan	
		*(ut->ptr) = (u_long)GsU_03000000;
		anum = GsLinkAnim(seq,ut->ptr);
		if(GsScanAnim(ut->ptr,0)==0)
	   	{
			printf("ScanAnim failed!!\n\n");
			break;
	    }
		HMD_ScanAnim();
		break;
    default:		// Unknown type
		*(ut->ptr) = (u_long)GsU_00000000;
		printf("Unknown type:0x%08x\n",ut->type);
    }
    return anum;
}
#endif

// Initialize HMD, and return a pointer to a new HMD model structure
HMD_Model *HMD_InitModel(u_long *hmd,GsOT *ot)
{
	int i,n;
	u_long	*ptr;
	GsTYPEUNIT ut;
	GsUNIT	*objp;	
	HMD_Model *model,*nmodel;
		
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
		model->root=(GsCOORDUNIT *)-1;
		model->initialized=0;
		model->seqs=0;
		model->MIMeParams=0;
		HMD_MIMeIdx=0;
		if ((model->MIMeParam=(long *)Mem_Malloc(HMD_MAXMIME*sizeof(long)))!=NULL)
		{
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
						while(GsScanUnit(0,&ut,ot,getScratchAddr(0))) 
						{
							if (((ut.type>>24==0x00) || (ut.type>>24==0x01) ||
							     (ut.type>>24==0x05)) && (ut.type&0x00800000)) 
							{
								// Store coordinate block
								model->coord=GsMapCoordUnit(hmd,ut.ptr);
								ut.type&=(~0x00800000);
							}

							// Initialize primitive
							if ((n=HMD_ScanPoly(&ut,model->seq,model))>0) model->seqs=n;
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
						model->root=(GsCOORDUNIT *)i;
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
			Mem_Free(model->MIMeParam);
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
	
		// Allocate space for MIMe parameters
		newmodel->MIMeParams=model->MIMeParams;
		newmodel->MIMeParam=NULL;
		if (newmodel->MIMeParams) newmodel->MIMeParam=(long *)Mem_Malloc(newmodel->MIMeParams*sizeof(long));
		
		// If there are MIMe params but no space was allocated, free the model
		if (newmodel->MIMeParams && !newmodel->MIMeParam) Mem_Free(newmodel);
		else
		{
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
					newmodel->root=&newmodel->coord[(int)model->original->root];
					HMD_Copy4(newmodel->coord,model->coord,bytes);
	
					// Allocate sequence pointers if there are any
					seq=NULL;
					if (model->seqs) seq=(GsSEQ *)Mem_Malloc(model->seqs*sizeof(GsSEQ)); 
					
					// If space was allocated for the sequence pointers...
					if (seq)
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
					if (!seq && model->seqs) Mem_Free(newmodel->coord);
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
			if (newmodel->MIMeParam) Mem_Free(newmodel->MIMeParam);
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
		Mem_Free(model->original->block);
		Mem_Free(model->original->MIMeParam);
		Mem_Free(model->original);
	}

	// Otherwise, just free this instance
	if (model->MIMeParam) Mem_Free(model->MIMeParam);
	Mem_Free(model->primtop);
	Mem_Free(model->coord);
	if (model->seq) Mem_Free(model->seq[0]);
	Mem_Free(model);
}

// Add an HMD model to an order table [Optimized]
void HMD_AddModel(HMD_Model *model,GsOT *ot)
{
	int bytes,i,seqs;
	GsUNIT *ptr;
	MATRIX tmp;
	HMD_Model *original;
	GsCOORDUNIT *mcoord,*ocoord;
	GsSEQ **seq,**oseq,**msq,**osq;
	u_long **pt;
	long **pr;
	
	original=model->original;
	
	mcoord=model->coord;
	ocoord=original->coord;
		
	bytes=(model->blocks-2)*sizeof(GsCOORDUNIT);
	
	if (model->MIMeParams)
	{
		// Copy MIMe parameter pointers to the original data area
		pr=(long **)model->original->MIMeParam;
		for (i=model->MIMeParams;i--;) *((long **)*pr++)=model->MIMeParam;
	}
	
	// Copy primtop pointers back to the original data area
	pt=&model->primtop[0];
	ptr=&original->block[1];
	for (i=(model->blocks-2);i--;) (ptr++)->primtop=*pt++;
	
	// Copy coordinate systems and sequences of this instance to the original data area
	HMD_Copy4(ocoord,mcoord,bytes);
	
	seqs=model->seqs;
	
	if (seqs)
	{
		msq=&model->seq[0];
		osq=&original->seq[0];
	
		seq=msq;
		oseq=osq;
		for (i=seqs;i--;) HMD_Copy4(*oseq++,*seq++,sizeof(GsSEQ));
	}
	
	// Add the model to the order table...
	ptr=original->block;
	for(i=original->blocks;i--;) 
	{
		// Check for a valid primitive block pointer, and make sure the primitive block
		// status bit is turned on!
		if ((int)ptr->primtop&0x80000000)
		{
			// If this block has a coordinate system, transform the coordinate system
			// to view-space.
			if (ptr->coord) 
			{
				GsGetLwUnit(ptr->coord,&tmp);
				GsSetLightMatrix(&tmp);	
				GsGetLsUnit(ptr->coord,&tmp);
				GsSetLsMatrix(&tmp);
			}
			// Add the primitive block to the order table
			GsSortUnit(ptr,ot,getScratchAddr(0));
		}
		ptr++;
	}
	
	// Copy updated coordinate systems and sequences back to the current instance
	HMD_Copy4(mcoord,ocoord,bytes);
	
	if (seqs)
	{
		seq=msq;
		oseq=osq;
		for (i=seqs;i--;) HMD_Copy4(*seq++,*oseq++,sizeof(GsSEQ));
	}
}

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



/*
	rotation is now done i the order yxz
*/

// Rotate a coordinate system by x,y,z
void HMD_RotateCoord(HMD_Model *m,int index,int x,int y,int z)
{
	GsCOORDUNIT *ptr=&m->coord[index];
	
	ptr->rot.vx+=x;
	ptr->rot.vy+=y;
	ptr->rot.vz+=z;
	RotMatrixYXZ(&ptr->rot,&ptr->matrix);
	ptr->flg=0;
}



// rotate model's root coordinate system to x,y,z
void HMD_RotateAbsoluteRoot(HMD_Model *m,int x,int y,int z)
{
	GsCOORDUNIT *ptr=m->root;
	
	ptr->rot.vx=x;
	ptr->rot.vy=y;
	ptr->rot.vz=z;
	RotMatrixYXZ(&ptr->rot,&ptr->matrix);
	ptr->flg=0;
}

void HMD_RotateAbsolute(HMD_Model *m, int index, int x,int y,int z)
{
	GsCOORDUNIT *ptr=&m->coord[index];
	
	ptr->rot.vx=x;
	ptr->rot.vy=y;
	ptr->rot.vz=z;
	RotMatrixYXZ(&ptr->rot,&ptr->matrix);
	ptr->flg=0;
}



#ifdef 0
// Transform a root coordinate system, rotate (by x,y,z), translate and scale
void HMD_Transform(HMD_Model *m,int x,int y,int z,VECTOR *translate,VECTOR *scale)
{
	GsCOORDUNIT *ptr=m->root;
	
	ptr->rot.vx+=x;
	ptr->rot.vy+=y;
	ptr->rot.vz+=z;
	RotMatrix_gte(&ptr->rot,&ptr->matrix);
	ScaleMatrix(&ptr->matrix,scale);
	TransMatrix(&ptr->matrix,translate);
	ptr->flg=0;
}
#endif

/*
	new version, rotates in the order y/x/z
*/
void HMD_Transform(HMD_Model *m,int x,int y,int z,VECTOR *translate,VECTOR *scale)
{
	GsCOORDUNIT *ptr=m->root;

	ptr->rot.vx=x;
	ptr->rot.vy=y;
	ptr->rot.vz=z;

	RotMatrixYXZ(&ptr->rot,&ptr->matrix);

	ScaleMatrix(&ptr->matrix,scale);
	TransMatrix(&ptr->matrix,translate);
	ptr->flg=0;
}



// Translate model
void HMD_Translate(HMD_Model *m,VECTOR *translate)
{
	GsCOORDUNIT *ptr=m->root;

	TransMatrix(&ptr->matrix,translate);
	ptr->flg=0;
}


// Translate model section
void HMD_TranslateIndex(HMD_Model *m,int index,VECTOR *translate)
{
	GsCOORDUNIT *ptr=&m->coord[index];

	TransMatrix(&ptr->matrix,translate);
	ptr->flg=0;
}



// scale model
void HMD_Scale(HMD_Model *m,VECTOR *scale)
{
	GsCOORDUNIT *ptr=m->root;
	
	ScaleMatrix(&ptr->matrix,scale);
	ptr->flg=0;
}


void HMD_ScaleBlock(HMD_Model *m, int index, VECTOR *scale)
{
	GsCOORDUNIT *ptr=&m->coord[index];

	ScaleMatrix(&ptr->matrix,scale);
	ptr->flg=0;
}


void	HMD_Project(HMD_Model *m, VECTOR *in, VECTOR *out)
{
	GsCOORDUNIT *ptr=m->root;

	//ApplyMatrix(&ptr->matrix, in, out);

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
	child->root->super=parent->root;
}


// Start an animation sequence, frames=HMD_LOOP for a looping animation
void HMD_StartAnim(HMD_Model *model,int sid,int frames,int speed)
{
	int i;
	GsSEQ *ptr;
	
	for (i=model->seqs;i--;)
	{
		ptr=model->seq[i];
	
    	ptr->ii=0xffff;
    	ptr->ti=ptr->start;
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



// gorgeous new functionality added by steve
// alternatively, some useless pointer settings. You decide.

void HMD_SetVertexList(HMD_Model *hmd, SVECTOR *vert)
{
 	hmd->vertices=vert;
}

void HMD_SetNormalList(HMD_Model *hmd, SVECTOR *norm)
{
 	hmd->normals=norm;
}



SVECTOR* HMD_GetVertexList(HMD_Model *hmd)
{
 	return	hmd->vertices;
}

SVECTOR* HMD_GetNormalList(HMD_Model *hmd)
{
 	return	hmd->normals;
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

