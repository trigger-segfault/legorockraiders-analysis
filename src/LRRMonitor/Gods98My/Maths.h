#pragma once

#include "../framework.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define M_PI			3.14159265358979323846f
#define M_EPSILON		1.0e-5f                 // Tolerance for REALs

#pragma endregion

/**********************************************************************************
 ******** Typedefs
 **********************************************************************************/

#pragma region Typedefs

/*typedef D3DVECTOR VECTOR3D;
typedef D3DRMVERTEX VERTEX3D;

typedef VECTOR3D *LPVECTOR3D;
typedef VERTEX3D *LPVERTEX3D;*/

typedef unsigned long COLOUR, *LPCOLOUR;

#pragma endregion

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

typedef struct VECTOR2D
{
	/*0,4*/ float x;
	/*4,4*/ float y;
	/*8*/
} VECTOR2D, *LPVECTOR2D;
static_assert(sizeof(VECTOR2D) == 0x8, "");
 

typedef struct VECTOR3D
{
	/*0,4*/ float x;
	/*4,4*/ float y;
	/*8,4*/ float z;
	/*c*/
} VECTOR3D, *LPVECTOR3D;
static_assert(sizeof(VECTOR3D) == 0xc, "");


typedef struct VECTOR4D
{
	/*00,4*/ float x;
	/*04,4*/ float y;
	/*08,4*/ float z;
	/*0c,4*/ float w;
	/*10*/
} VECTOR4D, *LPVECTOR4D;
static_assert(sizeof(VECTOR4D) == 0x10, "");


typedef struct AREA2D
{
	/*00,4*/ float x;
	/*04,4*/ float y;
	/*08,4*/ float width;
	/*0c,4*/ float height;
	/*10*/
} AREA2D, *LPAREA2D;
static_assert(sizeof(AREA2D) == 0x10, "");


typedef struct VERTEX3D
{
	/*00,c*/ VECTOR3D position;
	/*0c,c*/ VECTOR3D normal;
	/*18,4*/ float tu;
	/*1c,4*/ float tv;
	/*20,4*/ COLOUR colour;
	/*24*/
} VERTEX3D, *LPVERTEX3D;
static_assert(sizeof(VERTEX3D) == 0x24, "");


typedef struct BOX3D
{
	/*00,c*/ VECTOR3D min;
	/*0c,c*/ VECTOR3D max;
	/*18*/
} BOX3D, *LPBOX3D;
static_assert(sizeof(BOX3D) == 0x18, "");


typedef float MATRIX4D[4][4];
static_assert(sizeof(MATRIX4D) == 0x40, "");


typedef float MATRIX3D[3][3];
static_assert(sizeof(MATRIX3D) == 0x24, "");

#pragma endregion

/**********************************************************************************
 ******** Macros
 **********************************************************************************/

#pragma region Macros

#define Colour_RGB(r,g,b)		(0xff000000L|(((long)((r)*255))<<16)|(((long)((g)*255))<<8)|(long)((b)*255))
#define Colour_RGBA(r,g,b,a)	((((long)((a)*255))<<24)|(((long)((r)*255))<<16)|(((long)((g) * 255))<<8)|(long)((b)*255))

#define Maths_Vector3DNormalise(r)			Maths_Vector3DNormalize((r))
#define Maths_Vector2DNormalise(r)			Maths_Vector2DNormalize((r))
#define Maths_Vector3DLength(v)				Maths_Vector3DModulus((v))
#define Maths_Vector2DLength(v)				Maths_Vector2DModulus((v))

#define Maths_Cos(a)						(REAL)std::cos((double)(a))
#define Maths_Sin(a)						(REAL)std::sin((double)(a))
#define Maths_Tan(a)						(REAL)std::tan((double)(a))
#define Maths_ACos(a)						(REAL)std::acos((double)(a))
#define Maths_ASin(a)						(REAL)std::asin((double)(a))
#define Maths_ATan(a)						(REAL)std::atan((double)(a))

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

/*__inline float __cdecl Maths_InterpolationDelta(float start, float end, float current)				{ return (current - start) / (end - start); }
__inline float __cdecl Maths_Interpolate(float start, float end, float delta)						{ return start + ((end - start) * delta); }

__inline VECTOR3D* __cdecl Maths_Vector2DMake3D(OUT VECTOR3D* r, const VECTOR2D* v)		{ r->x = v->x; r->y = v->y; r->z = 0.0f; return r; }
__inline VECTOR2D* __cdecl Maths_Vector3DMake2D(OUT VECTOR2D* r, const VECTOR3D* v)		{ r->x = v->x; r->y = v->y; return r; }

__inline float __cdecl Maths_Vector2DModulus(const VECTOR2D* v)										{ return (float) std::sqrt((v->x*v->x)+(v->y*v->y)); }
*/

// <LegoRR.exe @00401240>
__inline float __cdecl Maths_Vector2DDistance(const VECTOR2D* a, const VECTOR2D* b)						{ return (float) std::sqrt(((a->x-b->x)*(a->x-b->x))+((a->y-b->y)*(a->y-b->y))); }

/*__inline float __cdecl Maths_Vector2DDotProduct(const VECTOR2D* a, const VECTOR2D* b)						{ return ((a->x * b->x) + (a->y * b->y)); }
__inline VECTOR2D* __cdecl Maths_Vector2DSubtract(OUT VECTOR2D* r, const VECTOR2D* a, const VECTOR2D* b)	{ r->x = a->x - b->x; r->y = a->y - b->y; return r; }
__inline VECTOR2D* __cdecl Maths_Vector2DAdd(OUT VECTOR2D* r, const VECTOR2D* a, const VECTOR2D* b)			{ r->x = a->x + b->x; r->y = a->y + b->y; return r; }
__inline VECTOR2D* __cdecl Maths_Vector2DScale(OUT VECTOR2D* r, const VECTOR2D* a, float f)				{ r->x = a->x * f; r->y = a->y * f; return r; }
__inline VECTOR2D* __cdecl Maths_Vector2DNormalize(OUT VECTOR2D* r)								{ Maths_Vector2DScale(r, r, 1.0f/Maths_Vector2DLength(r)); return r; }
__inline VECTOR2D* __cdecl Maths_Vector2DSetLength(OUT VECTOR2D* r, const VECTOR2D* a, float l)			{ float m = Maths_Vector2DModulus(a); return Maths_Vector2DScale(r, a, (1.0f/m) * l); }
__inline VECTOR2D* __cdecl Maths_Vector2DRandom(OUT VECTOR2D* r)									{ r->x = Maths_RandRange(0.0f, 1.0f); r->y = Maths_RandRange(0.0f, 1.0f); return Maths_Vector2DNormalise(r); }

__inline float __cdecl Maths_Vector2DCrossProductZ(const VECTOR2D* a, const VECTOR2D* b)					{ return (a->x * b->y) - (a->y * b->x); }

__inline float __cdecl Maths_Vector3DModulus(const VECTOR3D* v)										{ return (float) std::sqrt((v->x*v->x)+(v->y*v->y)+(v->z*v->z)); }
__inline float __cdecl Maths_Vector3DDistance(const VECTOR3D* a, const VECTOR3D* b)						{ return (float) std::sqrt(((a->x-b->x)*(a->x-b->x))+((a->y-b->y)*(a->y-b->y))+((a->z-b->z)*(a->z-b->z))); }
*/

// <LegoRR.exe @004013e0>
__inline VECTOR3D* __cdecl Maths_Vector3DCrossProduct(OUT VECTOR3D* r, const VECTOR3D* a, const VECTOR3D* b){ r->x = (a->y * b->z) - (a->z * b->y); r->y = (a->z * b->x) - (a->x * b->z); r->z = (a->x * b->y) - (a->y * b->x); return r; }

// <LegoRR.exe @00401470>
__inline VECTOR3D* __cdecl Maths_Vector3DAdd(OUT VECTOR3D* r, const VECTOR3D* a, const VECTOR3D* b)			{ r->x = (a->x + b->x); r->y = (a->y + b->y); r->z = (a->z + b->z); return r; }

// <LegoRR.exe @00401630>
__inline VECTOR3D* __cdecl Maths_Vector3DSubtract(OUT VECTOR3D* r, const VECTOR3D* a, const VECTOR3D* b)	{ r->x = (a->x - b->x); r->y = (a->y - b->y); r->z = (a->z - b->z); return r; }

/*__inline float __cdecl Maths_Vector3DDotProduct(const VECTOR3D* a, const VECTOR3D* b)						{ return (a->x * b->x) + (a->y * b->y) + (a->z * b->z); }
*/

// <LegoRR.exe @00401660>
__inline VECTOR3D* __cdecl Maths_Vector3DScale(OUT VECTOR3D* r, const VECTOR3D* a, float f)				{ r->x = a->x * f; r->y = a->y * f; r->z = a->z * f; return r; }

// <LegoRR.exe @00401690>
__inline VECTOR3D* __cdecl Maths_Vector3DNormalize(OUT VECTOR3D* r)								{ Maths_Vector3DScale(r, r, 1.0f/Maths_Vector3DLength(r)); return r; }

/*__inline VECTOR3D* __cdecl Maths_Vector3DInterpolate(OUT VECTOR3D* result, const VECTOR3D* start, const VECTOR3D* end, float delta)	{ Maths_Vector3DSubtract(result, end, start); Maths_Vector3DScale(result, result, delta); Maths_Vector3DAdd(result, start, result); return result; }
AREA2D* __cdecl Maths_Area2DInterpolate(OUT AREA2D* result, const AREA2D* start, const AREA2D* end, float delta);
*/

//struct VECTOR3D *__cdecl Maths_Vector3DAdd(struct VECTOR3D *r,struct VECTOR3D *a,struct VECTOR3D *b);
//struct VECTOR3D *__cdecl Maths_Vector3DCrossProduct(struct VECTOR3D *r,struct VECTOR3D *a,struct VECTOR3D *b);
//float __cdecl Maths_Vector3DDotProduct(struct VECTOR3D *a,struct VECTOR3D *b);
//float __cdecl Maths_Vector3DModulus(struct VECTOR3D *a);
//struct VECTOR3D *__cdecl Maths_Vector3DNormalize(struct VECTOR3D *r);



// <LegoRR.exe @004797c0>
VECTOR3D* __cdecl Maths_Vector3DRandom(OUT VECTOR3D* r);


//VECTOR3D* __cdecl Maths_Vector3DReflect(OUT VECTOR3D* d, const VECTOR3D* ray, const VECTOR3D* norm);


// <LegoRR.exe @004797d0>
VECTOR3D* __cdecl Maths_Vector3DRotate(OUT VECTOR3D* r, const VECTOR3D* v, const VECTOR3D* axis, float theta);


//struct VECTOR3D *__cdecl Maths_Vector3DScale(struct VECTOR3D *r,struct VECTOR3D *a,float f);
//struct VECTOR3D *__cdecl Maths_Vector3DSubtract(struct VECTOR3D *r,struct VECTOR3D *a,struct VECTOR3D *b);

// <LegoRR.exe @004797f0>
VECTOR3D* __cdecl Maths_PlaneNormal(OUT VECTOR3D* n, const VECTOR3D* p1, const VECTOR3D* p2, const VECTOR3D* p3);

// <LegoRR.exe @004798f0>
float __cdecl Maths_TriangleAreaZ(const VECTOR3D* p1, const VECTOR3D* p2, const VECTOR3D* p3, BOOL bfc);

// <LegoRR.exe @00479b60>
short __cdecl Maths_Rand(void);

// <LegoRR.exe @00479b70>
float __cdecl Maths_RandRange(float low, float high);

// <LegoRR.exe @00479ba0>
BOOL __cdecl Maths_RayPlaneIntersection(VECTOR3D* endPoint, const VECTOR3D* rayOrigin, const VECTOR3D* ray, const VECTOR3D* planePoint, const VECTOR3D* planeNormal);


// <LegoRR.exe @00479cf0>
BOOL __cdecl Maths_RayPlaneDistance(OUT float* dist, const VECTOR3D* rayOrigin, const VECTOR3D* ray, const VECTOR3D* planePoint, const VECTOR3D* planeNormal);

// <LegoRR.exe @00479d70>
void __cdecl Maths_RayEndPoint(OUT VECTOR3D* endPoint, const VECTOR3D* rayOrigin, const VECTOR3D* ray, float dist);


// <LegoRR.exe @00479db0>
VECTOR2D* __cdecl Maths_Vector2DIntersection(OUT VECTOR2D* intersection, const VECTOR2D* start1, const VECTOR2D* vector1, const VECTOR2D* start2, const VECTOR2D* vector2);


// <LegoRR.exe @00479e40>
BOOL __cdecl Maths_PointInsidePoly(const VECTOR2D* point, const VECTOR2D* fromList, const VECTOR2D* toList, unsigned long count);

// <LegoRR.exe @00479ed0>
BOOL __cdecl Maths_RaySphereIntersection(const VECTOR3D* center, float radius, const VECTOR3D* camera, const VECTOR3D* ray);


//VECTOR2D* __cdecl Maths_Vector2DLineIntersection(VECTOR2D* intersection, const VECTOR2D* start1, const VECTOR2D* end1, const VECTOR2D* start2, const VECTOR2D* end2);
//VECTOR3D* __cdecl Maths_Vector3DApplyMatrix(OUT VECTOR3D* result, const MATRIX4D matrix, const VECTOR3D* point );
//VECTOR3D* __cdecl Maths_Vector3DApplyMatrixXYZ(OUT VECTOR3D* result, const MATRIX4D matrix, float x, float y, float z );

/////////////////////////////////////////////////////////////////////////
// Andy Ray.  3/2/99.
// Some simple matrix functions.
/////////////////////////////////////////////////////////////////////////

// Compared to other multiplication functions, a = right, and b = left
// <LegoRR.exe @00479fa0>
void __cdecl Matrix_Mult(OUT MATRIX4D ans, const MATRIX4D a, const MATRIX4D b);

// Generates the matrix for a rotation of rot radians about the X-Axis
// <LegoRR.exe @0047a010>
void __cdecl Matrix_RotX(OUT MATRIX4D ans, float rot);

// Generates the matrix for a rotation of rot radians about the Y-Axis
// <LegoRR.exe @0047a060>
void __cdecl Matrix_RotY(OUT MATRIX4D ans, float rot);

// Generates the matrix for a rotation of rot radians about the Z-Axis
// <LegoRR.exe @0047a0b0>
void __cdecl Matrix_RotZ(OUT MATRIX4D ans, float rot);

// Generates a translation matrix.
// <LegoRR.exe @0047a100>
void __cdecl Matrix_Translate(OUT MATRIX4D ans, const VECTOR3D* trans);

// Makes the identity matrix
// <LegoRR.exe @0047a130>
void __cdecl Matrix_Identity(OUT MATRIX4D ans);

// Makes the zero matrix.
// <LegoRR.exe @0047a160>
void __cdecl Matrix_Zero(OUT MATRIX4D ans);

// Copies a matrix.
// <LegoRR.exe @0047a170>
void __cdecl Matrix_Copy(OUT MATRIX4D to, const MATRIX4D from);


//BOOL __cdecl Matrix_Invert(MATRIX4D q, MATRIX4D a);

#pragma endregion

}
