
#ifndef _GODS98_ANIMCLONE_H
#define _GODS98_ANIMCLONE_H

#define ANIMCLONE_MAXVISUALS		4

//#ifdef _GENPROTFILE
//#define _GODS98COMPILE
//#endif // _GENPROTFILE

#ifdef _GODS98COMPILE

typedef struct AnimClone {

	struct AnimClone *clonedFrom;

	struct Lws_Info *scene;
	LPDIRECT3DRMANIMATIONSET2 animSet;
	BOOL lws;

	LPDIRECT3DRMFRAME3 root;
	LPDIRECT3DRMFRAME3 *partArray;
	ULONG partCount;
	ULONG frameCount;

} AnimClone, *lpAnimClone;

#else

typedef struct AnimClone *lpAnimClone;

#endif // _GODS98COMPILE

//#ifdef _GENPROTFILE
//#undef _GODS98COMPILE
//#endif // _GENPROTFILE


#ifndef _GENPROTFILE
#include "..\Src\AnimClone.prot"
#endif // _GENPROTFILE

#endif // !_GODS98_ANIMCLONE_H
