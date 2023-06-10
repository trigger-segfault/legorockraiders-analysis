
#ifndef _RGL_QUANTIZER_H_
#define _RGL_QUANTIZER_H_

#define	QUANTIZER_RED			2
#define	QUANTIZER_GREEN			1
#define QUANTIZER_BLUE			0

struct QuantizerBox {

	SLONG r0;
	SLONG r1;
	SLONG g0;  
	SLONG g1;  
	SLONG b0;  
	SLONG b1;
	SLONG vol;
};

typedef struct QuantizerBox		*lpQuantizerBox;

// Auto Prototypes
extern void __cdecl Quantizer_Hist3D(unsigned short *qAdd,unsigned long size,unsigned char *Ir,unsigned char *Ig,unsigned char *Ib,long *vwt,long *vmr,long *vmg,long *vmb,float *m2);
extern void __cdecl Quantizer_Moments3D(long *vwt,long *vmr,long *vmg,long *vmb,float *m2);
extern long __cdecl Quantizer_Volume(struct QuantizerBox *cube,long (*mmt)[33][33]);
extern long __cdecl Quantizer_Bottom(struct QuantizerBox *cube,unsigned char dir,long (*mmt)[33][33]);
extern long __cdecl Quantizer_Top(struct QuantizerBox *cube,unsigned char dir,long pos,long (*mmt)[33][33]);
extern float __cdecl Quantizer_Variance(struct QuantizerBox *cube,long (*wt)[33][33],long (*mr)[33][33],long (*mg)[33][33],long (*mb)[33][33],float (*gm2)[33][33]);
extern float __cdecl Quantizer_Maximize(struct QuantizerBox *cube,unsigned char dir,long first,long last,long *cut,long whole_r,long whole_g,long whole_b,long whole_w,long (*wt)[33][33],long (*mr)[33][33],long (*mg)[33][33],long (*mb)[33][33]);
extern int __cdecl Quantizer_Cut(struct QuantizerBox *set1,struct QuantizerBox *set2,long (*wt)[33][33],long (*mr)[33][33],long (*mg)[33][33],long (*mb)[33][33]);
extern void __cdecl Quantizer_Mark(struct QuantizerBox *cube,long label,unsigned char *tag);
extern unsigned long *__cdecl Quantizer_Generate(unsigned char *rList,unsigned char *gList,unsigned char *bList,unsigned long width,unsigned long height,unsigned char *dest,unsigned long destPitch,unsigned long *colourCount);
// Auto Prototypes

#endif // !_RGL_QUANTIZER_H_
