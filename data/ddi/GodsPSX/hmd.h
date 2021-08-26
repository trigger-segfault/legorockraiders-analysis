
// HMD.H - Version 1.1, Coded by Adrian Francis, Oct 15 '98

#ifndef __HMD_H
#define __HMD_H

#define HMD_MAXSEQ			64		// Maximum number of sequence pointers
#define HMD_NORMAL			0x10	// Normal animation speed
#define HMD_LOOP			-1		// Looping animation
#define HMD_ANIM_STOP		0		// no animation
#define	HMD_MAX_ANIMS		8
#define HMDFOGFLAG (1<<17)
#define HMDACSUBFLAG (1<<19)

#define HMD_MODEL_COMMON	u_long						**primtop;				\
							GsUNIT						*block;					\
							GsCOORDUNIT 				*coord;					\
							char						root;					\
							u_char						blocks;					\
							u_short						initialized;			

typedef struct HMD_Model_type
{
	HMD_MODEL_COMMON

	struct HMD_Model_type		*original;				
	GsSEQ						**seq;				// Sequence pointers
	u_long						seqs;				// Number of sequence pointers
	u_short						*aframe;			// Temporary store for animation pause	
	unsigned short				*animIndex;			// Indices for sequence re-start
} 
HMD_Model;

typedef struct HMD_StaticModel_type
{
	HMD_MODEL_COMMON
} 
HMD_StaticModel;
 
extern HMD_Model *	HMD_InitModel(u_long *,GsOT *,int modeflags);
extern HMD_Model *	HMD_InitInstance(HMD_Model *);
extern void			HMD_FreeModel(HMD_Model *);
extern void 		HMD_AddModel(HMD_Model *,GsOT *);
extern void			HMD_SetBlock(HMD_Model *,int,int);
extern void			HMD_RotateCoord(HMD_Model *,int,int,int,int);
extern void			HMD_Transform(HMD_Model *,VECTOR *,SVECTOR *);
extern void			HMD_StartAnim(HMD_Model *,int,int,int);
extern void			HMD_SetSID(HMD_Model *,int);
extern void			HMD_SetSIDNow(HMD_Model *model,int sid);

extern void			HMD_PauseAnim(HMD_Model *);
extern void 		HMD_UnPauseAnim(HMD_Model *);

/* added by steve */
extern void			HMD_StopAnim(HMD_Model *);
extern void			HMD_SetAnimSpeed(HMD_Model *, int);
extern void			HMD_RotateAbsoluteRoot(HMD_Model *m,int x,int y,int z);
extern void			HMD_RotateAbsolute(HMD_Model *m, int index, int x, int y, int z);

extern void			HMD_Translate(HMD_Model *,VECTOR *);
extern void			HMD_TranslateIndex(HMD_Model *,int index, VECTOR *);
extern void			HMD_Scale(HMD_Model *,VECTOR *);
extern void			HMD_SetParent(HMD_Model *, HMD_Model *);
extern void			HMD_ScaleBlock(HMD_Model *m, int index, VECTOR *scale);
extern int			HMD_GetFrameNUm(HMD_Model *model);

extern void			HMD_Add(HMD_Model *model);
extern void			HMD_AddStatic(HMD_Model *model, int x, int y, int z, int rx, int ry, int rz,int sx,int sy,int sz);
extern void			HMD_AddStaticMatrix(HMD_Model *model, int x, int y, int z, MATRIX *matrix,int sx,int sy,int sz);


#define HMD_StopAnim(m) HMD_SetAnimSpeed(m,HMD_ANIM_STOP)

#define HMD_JoinModelAtRoot(m1,m2,i) m1->root->super=&m2->coord[i]
#define HMD_JoinModels(m1,i1,m2,i2) m1->coord[i1].super=&m2->coord[i2]


// Typedefs for animation primitive drivers

typedef struct
{
	long tx,ty,tz;
} HMD_ps0r0t1,HMD_ps0r0t3;

typedef struct
{
	short rx,ry,rz,scale;
} HMD_ps0r1t0,HMD_ps0r3t0,HMD_ps9r1t0;

typedef struct 
{
  	long tx,ty,tz;
  	short rx,ry,rz,scale;
} HMD_ps0r1t1,HMD_ps9r1t1,HMD_ps0r3t1,HMD_ps0r1t3,HMD_ps0r3t3;

typedef struct
{
	long tx,ty,tz;
	short rx,ry,rz,sx,sy,sz;
} HMD_ps1r1t1;

typedef struct
{
	long tx,ty,tz;
	short scale,pad;
} HMD_ps9r0t1;

typedef struct
{
	long tx0,ty0,tz0;
	long tx1,ty1,tz1;
	long tx2,ty2,tz2;
} HMD_ps0r0t2;

typedef struct
{
	long tx0,ty0,tz0;
	long tx1,ty1,tz1;
	long tx2,ty2,tz2;
	short scale,pad;
} HMD_ps9r0t2;

typedef struct
{
	long tx0,ty0,tz0;
	long tx1,ty1,tz1;
	long tx2,ty2,tz2;
	short rx,ry,rz,scale;
} HMD_ps0r1t2,HMD_ps9r1t2,HMD_ps0r3t2;

typedef struct
{
	long tx0,ty0,tz0;
	long tx1,ty1,tz1;
	long tx2,ty2,tz2;
	short rx,ry,rz,sx,sy,sz;
} HMD_ps1r1t2;

typedef struct
{
	short tx,ty,tz,scale;
} HMD_ps0r0t9,HMD_ps9r0t9;

typedef struct
{
	short tx,ty,tz,rx,ry,rz;
} HMD_ps0r1t9,HMD_ps0r3t9;

typedef struct
{
	short tx,ty,tz,rx,ry,rz,sx,sy,sz,pad;
} HMD_ps1r1t9;

typedef struct
{
	short tx,ty,tz,rx,ry,rz,scale,pad;
} HMD_ps9r1t9;

typedef struct
{
	short tx0,ty0,tz0,tx1,ty1,tz1,tx2,ty2,tz2,scale;
} HMD_ps0r0tA,ps9r0tA;

typedef struct
{
	short tx0,ty0,tz0,tx1,ty1,tz1,tx2,ty2,tz2,rx,ry,rz;
} HMD_ps0r1tA;



typedef struct 
{
  	GsSEQ *base;
  	HMD_ps0r0t1 *src;
  	HMD_ps0r0t1 *dst;
  	HMD_ps0r0t1 *intr;
} HMD_ARGANIMs0r0t1;

typedef struct 
{
  	GsSEQ *base;
  	HMD_ps0r1t0 *src;
  	HMD_ps0r1t0 *dst;
  	HMD_ps0r1t0 *intr;
} HMD_ARGANIMs0r1t0;

typedef struct 
{
  	GsSEQ *base;
  	HMD_ps0r1t1 *src;
  	HMD_ps0r1t1 *dst;
  	HMD_ps0r1t1 *intr;
} HMD_ARGANIMs0r1t1;

#endif
