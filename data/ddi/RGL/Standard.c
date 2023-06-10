
#include "Standard.h"

__inline VOID AREA2Di2r(LPAREA2Dr r, LPAREA2Di i) {

	r->x = (REAL) i->x;
	r->y = (REAL) i->y;
	r->width = (REAL) i->width;
	r->height = (REAL) i->height;
}

__inline VOID AREA2Dr2i(LPAREA2Di i, LPAREA2Dr r) {

	i->x = (ULONG) r->x;
	i->y = (ULONG) r->y;
	i->width = (ULONG) r->width;
	i->height = (ULONG) r->height;
}

__inline ULONG REALASULONG(REAL r) {

	return *((LPULONG) &r);
}