//��������������������������������������������a
// 3D Handler For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glonn Benson
//��������������������������������������������

// Include all Header Files

//��������������������������������������������
#include	"libgods.h"
//��������������������������������������������

Uint32	G3D_absmax(Sint32 a,Sint32 b,Sint32 c)
{
	Sint32	p,q,r;

	p=ABS(a);
	q=ABS(b);
	r=ABS(c);

	if((p>=q)&&(p>=r)) return(p);
	if((q>=p)&&(q>=r)) return(q);
	return(r);
}


