
#ifndef _GODS98_MATHS_H_
#define _GODS98_MATHS_H_

#include "Standard.h"

#define M_PI			3.14159265358979323846f
#define M_EPSILON		1.0e-5f                 // Tolerance for REALs

/*
typedef D3DVECTOR VECTOR3D;
typedef D3DRMVERTEX VERTEX3D;

typedef VECTOR3D *LPVECTOR3D;
typedef VERTEX3D *LPVERTEX3D;
*/

typedef ULONG COLOUR, *LPCOLOUR;

#define Colour_RGB(r,g,b)		(0xff000000L|(((long)((r)*255))<<16)|(((long)((g)*255))<<8)|(long)((b)*255))
#define Colour_RGBA(r,g,b,a)	((((long)((a)*255))<<24)|(((long)((r)*255))<<16)|(((long)((g) * 255))<<8)|(long)((b)*255))

typedef struct VECTOR2D {

	REAL x, y;

} VECTOR2D, *LPVECTOR2D;
 
typedef struct VECTOR3D {

	REAL x, y, z;

} VECTOR3D, *LPVECTOR3D;

typedef struct VECTOR4D {

	REAL x, y, z, w;

} VECTOR4D, *LPVECTOR4D;

typedef struct AREA2D {

	REAL x, y;
	REAL width, height;

} AREA2D, *LPAREA2D;

typedef struct VERTEX3D {

	VECTOR3D position;
	VECTOR3D normal;
	REAL tu, tv;
	COLOUR colour;

} VERTEX3D, *LPVERTEX3D;

typedef struct BOX3D {

	VECTOR3D min, max;

} BOX3D, *LPBOX3D;

typedef REAL MATRIX4D[4][4];
typedef REAL MATRIX3D[3][3];

#define Maths_Vector3DNormalise(r)			Maths_Vector3DNormalize((r))
#define Maths_Vector2DNormalise(r)			Maths_Vector2DNormalize((r))
#define Maths_Vector3DLength(v)				Maths_Vector3DModulus((v))
#define Maths_Vector2DLength(v)				Maths_Vector2DModulus((v))

#define Maths_Cos(a)						(REAL)cos((double)(a))
#define Maths_Sin(a)						(REAL)sin((double)(a))
#define Maths_Tan(a)						(REAL)tan((double)(a))
#define Maths_ACos(a)						(REAL)acos((double)(a))
#define Maths_ASin(a)						(REAL)asin((double)(a))
#define Maths_ATan(a)						(REAL)atan((double)(a))

REAL Maths_RandRange(REAL low, REAL high);

__inline REAL Maths_InterpolationDelta(REAL start, REAL end, REAL current)				{ return (current - start) / (end - start); }
__inline REAL Maths_Interpolate(REAL start, REAL end, REAL delta)						{ return start + ((end - start) * delta); }

__inline LPVECTOR3D Maths_Vector2DMake3D(LPVECTOR3D r, LPVECTOR2D v)		{ r->x = v->x; r->y = v->y; r->z = 0.0f; return r; }
__inline LPVECTOR2D Maths_Vector3DMake2D(LPVECTOR2D r, LPVECTOR3D v)		{ r->x = v->x; r->y = v->y; return r; }

__inline REAL Maths_Vector2DModulus(LPVECTOR2D v)										{ return (REAL) sqrt((v->x*v->x)+(v->y*v->y)); }
__inline REAL Maths_Vector2DDistance(LPVECTOR2D a, LPVECTOR2D b)						{ return (REAL) sqrt(((a->x-b->x)*(a->x-b->x))+((a->y-b->y)*(a->y-b->y))); }
__inline REAL Maths_Vector2DDotProduct(LPVECTOR2D a, LPVECTOR2D b)						{ return ((a->x * b->x) + (a->y * b->y)); }
__inline LPVECTOR2D Maths_Vector2DSubtract(LPVECTOR2D r, LPVECTOR2D a, LPVECTOR2D b)	{ r->x = a->x - b->x; r->y = a->y - b->y; return r; }
__inline LPVECTOR2D Maths_Vector2DAdd(LPVECTOR2D r, LPVECTOR2D a, LPVECTOR2D b)			{ r->x = a->x + b->x; r->y = a->y + b->y; return r; }
__inline LPVECTOR2D Maths_Vector2DScale(LPVECTOR2D r, LPVECTOR2D a, REAL f)				{ r->x = a->x * f; r->y = a->y * f; return r; }
__inline LPVECTOR2D Maths_Vector2DNormalize(LPVECTOR2D r)								{ Maths_Vector2DScale(r, r, 1.0f/Maths_Vector2DLength(r)); return r; }
__inline LPVECTOR2D Maths_Vector2DSetLength(LPVECTOR2D r, LPVECTOR2D a, REAL l)			{ REAL m = Maths_Vector2DModulus(a); return Maths_Vector2DScale(r, a, (1.0f/m) * l); }
__inline LPVECTOR2D Maths_Vector2DRandom(LPVECTOR2D r)									{ r->x = Maths_RandRange(0.0f, 1.0f); r->y = Maths_RandRange(0.0f, 1.0f); return Maths_Vector2DNormalise(r); }

__inline REAL Maths_Vector2DCrossProductZ(LPVECTOR2D a, LPVECTOR2D b)					{ return (a->x * b->y) - (a->y * b->x); }

__inline REAL Maths_Vector3DModulus(LPVECTOR3D v)										{ return (REAL) sqrt((v->x*v->x)+(v->y*v->y)+(v->z*v->z)); }
__inline REAL Maths_Vector3DDistance(LPVECTOR3D a, LPVECTOR3D b)						{ return (REAL) sqrt(((a->x-b->x)*(a->x-b->x))+((a->y-b->y)*(a->y-b->y))+((a->z-b->z)*(a->z-b->z))); }
__inline LPVECTOR3D Maths_Vector3DCrossProduct(LPVECTOR3D r, LPVECTOR3D a, LPVECTOR3D b){ r->x = (a->y * b->z) - (a->z * b->y); r->y = (a->z * b->x) - (a->x * b->z); r->z = (a->x * b->y) - (a->y * b->x); return r; }
__inline LPVECTOR3D Maths_Vector3DAdd(LPVECTOR3D r, LPVECTOR3D a, LPVECTOR3D b)			{ r->x = (a->x + b->x); r->y = (a->y + b->y); r->z = (a->z + b->z); return r; }
__inline LPVECTOR3D Maths_Vector3DSubtract(LPVECTOR3D r, LPVECTOR3D a, LPVECTOR3D b)	{ r->x = (a->x - b->x); r->y = (a->y - b->y); r->z = (a->z - b->z); return r; }
__inline REAL Maths_Vector3DDotProduct(LPVECTOR3D a, LPVECTOR3D b)						{ return (a->x * b->x) + (a->y * b->y) + (a->z * b->z); }
__inline LPVECTOR3D Maths_Vector3DScale(LPVECTOR3D r, LPVECTOR3D a, REAL f)				{ r->x = a->x * f; r->y = a->y * f; r->z = a->z * f; return r; }
__inline LPVECTOR3D Maths_Vector3DNormalize(LPVECTOR3D r)								{ Maths_Vector3DScale(r, r, 1.0f/Maths_Vector3DLength(r)); return r; }

__inline LPVECTOR3D Maths_Vector3DInterpolate(LPVECTOR3D result, LPVECTOR3D start, LPVECTOR3D end, REAL delta)	{ Maths_Vector3DSubtract(result, end, start); Maths_Vector3DScale(result, result, delta); Maths_Vector3DAdd(result, start, result); return result; }
extern LPAREA2D __cdecl Maths_Area2DInterpolate(LPAREA2D result, LPAREA2D start, LPAREA2D end, REAL delta);

//extern struct VECTOR3D *__cdecl Maths_Vector3DAdd(struct VECTOR3D *r,struct VECTOR3D *a,struct VECTOR3D *b);
//extern struct VECTOR3D *__cdecl Maths_Vector3DCrossProduct(struct VECTOR3D *r,struct VECTOR3D *a,struct VECTOR3D *b);
//extern float __cdecl Maths_Vector3DDotProduct(struct VECTOR3D *a,struct VECTOR3D *b);
//extern float __cdecl Maths_Vector3DModulus(struct VECTOR3D *a);
//extern struct VECTOR3D *__cdecl Maths_Vector3DNormalize(struct VECTOR3D *r);
extern struct VECTOR3D *__cdecl Maths_Vector3DRandom(struct VECTOR3D *r);
extern struct VECTOR3D *__cdecl Maths_Vector3DReflect(struct VECTOR3D *d,struct VECTOR3D *ray,struct VECTOR3D *norm);
extern struct VECTOR3D *__cdecl Maths_Vector3DRotate(struct VECTOR3D *r,struct VECTOR3D *v,struct VECTOR3D *axis,float theta);
//extern struct VECTOR3D *__cdecl Maths_Vector3DScale(struct VECTOR3D *r,struct VECTOR3D *a,float f);
//extern struct VECTOR3D *__cdecl Maths_Vector3DSubtract(struct VECTOR3D *r,struct VECTOR3D *a,struct VECTOR3D *b);
extern struct VECTOR3D *__cdecl Maths_PlaneNormal(struct VECTOR3D *n,struct VECTOR3D *p1,struct VECTOR3D *p2,struct VECTOR3D *p3);
extern float __cdecl Maths_TriangleAreaZ(struct VECTOR3D *p1,struct VECTOR3D *p2,struct VECTOR3D *p3,BOOL bfc);
extern SWORD __cdecl Maths_Rand(VOID);
extern BOOL __cdecl Maths_RayPlaneIntersection(LPVECTOR3D endPoint, LPVECTOR3D rayOrigin, LPVECTOR3D ray, LPVECTOR3D planePoint, LPVECTOR3D planeNormal);
extern BOOL __cdecl Maths_RayPlaneDistance(LPREAL dist, LPVECTOR3D rayOrigin, LPVECTOR3D ray, LPVECTOR3D planePoint, LPVECTOR3D planeNormal);
extern VOID __cdecl Maths_RayEndPoint(LPVECTOR3D endPoint, LPVECTOR3D rayOrigin, LPVECTOR3D ray, REAL dist);
extern LPVECTOR2D __cdecl Maths_Vector2DLineIntersection(LPVECTOR2D intersection, LPVECTOR2D start1, LPVECTOR2D end1, LPVECTOR2D start2, LPVECTOR2D end2);
extern LPVECTOR2D __cdecl Maths_Vector2DIntersection(LPVECTOR2D intersection, LPVECTOR2D start1, LPVECTOR2D vector1, LPVECTOR2D start2, LPVECTOR2D vector2);
extern BOOL __cdecl Maths_PointInsidePoly(LPVECTOR2D point, LPVECTOR2D fromList, LPVECTOR2D toList, ULONG count);
extern LPVECTOR3D __cdecl Maths_Vector3DApplyMatrix( LPVECTOR3D result, MATRIX4D matrix, LPVECTOR3D point );
extern LPVECTOR3D __cdecl Maths_Vector3DApplyMatrixXYZ( LPVECTOR3D result, MATRIX4D matrix, REAL x, REAL y, REAL z );
extern BOOL __cdecl  Maths_RaySphereIntersection(LPVECTOR3D center, REAL radius, LPVECTOR3D camera, LPVECTOR3D ray);

/////////////////////////////////////////////////////////////////////////
// Andy Ray.  3/2/99.
// Some simple matrix functions.
/////////////////////////////////////////////////////////////////////////

extern VOID Matrix_Mult(MATRIX4D ans, MATRIX4D a, MATRIX4D b);

// Generates the matrix for a rotation of rot radians about the X-Axis
extern VOID Matrix_RotX(MATRIX4D ans, REAL rot);

// Generates the matrix for a rotation of rot radians about the Y-Axis
extern VOID Matrix_RotY(MATRIX4D ans, REAL rot);

// Generates the matrix for a rotation of rot radians about the Z-Axis
extern VOID Matrix_RotZ(MATRIX4D ans, REAL rot);

// Generates a translation matrix.
extern VOID Matrix_Translate(MATRIX4D ans, LPVECTOR3D trans);

// Makes the identity matrix
extern VOID Matrix_Identity(MATRIX4D ans);

// Makes the zero matrix.
extern VOID Matrix_Zero(MATRIX4D ans);

// Copies a matrix.
extern VOID Matrix_Copy(MATRIX4D to, MATRIX4D from);

extern BOOL Matrix_Invert(MATRIX4D q, MATRIX4D a);

#endif // _GODS98_MATHS_H_
