
#ifndef _RGL_MATHS_H_
#define _RGL_MATHS_H_

#include "Standard.h"
#include <math.h>

#define M_PI			3.14159265358979323846f
#define M_2PI			(2.0f*M_PI)
#define M_EPSILON		1.0e-5f					      // Tolerance for FLOATs

typedef REAL											MATRIX4D[4][4];
typedef REAL											MATRIX3D[3][3];
typedef struct VECTOR2D { REAL x, y; }					VECTOR2D, *LPVECTOR2D;
typedef struct VECTOR3D { REAL x, y, z; }				VECTOR3D, *LPVECTOR3D;
typedef struct VECTOR4D { REAL x, y, z, w; }			VECTOR4D, *LPVECTOR4D;
typedef struct LINE3D { VECTOR3D start, end; }			LINE3D, *LPLINE3D;
typedef struct BOX3D { VECTOR3D min, max; }				BOX3D, *LPBOX3D;

#define Maths_Cos(a)						(REAL)cos((double)(a))
#define Maths_Sin(a)						(REAL)sin((double)(a))
#define Maths_Tan(a)						(REAL)tan((double)(a))
#define Maths_Cot(a)						(1.0f/(REAL)tan((double)(a)))
#define Maths_ACos(a)						(REAL)acos((double)(a))
#define Maths_ASin(a)						(REAL)asin((double)(a))
#define Maths_ATan(a)						(REAL)atan((double)(a))
#define Maths_Sqrt(l)						(REAL)sqrt((double)(l))

#define Maths_Deg2Rad(d)					(((d)/360.0f)*(2.0f*M_PI))
#define Maths_Rad2Deg(d)					(((d)/(2.0f*M_PI))*360.0f)

#define Maths_Vector3DNormalize(r)			Maths_Vector3DNormalise((r))
#define Maths_Vector2DNormalize(r)			Maths_Vector2DNormalise((r))
#define Maths_Vector3DLength(v)				Maths_Vector3DModulus((v))
#define Maths_Vector2DLength(v)				Maths_Vector2DModulus((v))

// Auto Prototypes
extern unsigned __int64 __stdcall Int64ShllMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern __int64 __stdcall Int64ShraMod32(__int64 Value,unsigned long ShiftCount);
extern unsigned __int64 __stdcall Int64ShrlMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern void *__cdecl GetFiberData(void );
extern void *__cdecl GetCurrentFiber(void );
extern float __cdecl Maths_InterpolationDelta(float start,float end,float current);
extern float __cdecl Maths_Mod(float a, float b);
extern float __cdecl Maths_RandRange(float low, float high);
extern float __cdecl Maths_Interpolate(float start,float end,float delta);
extern float __cdecl Maths_Vector2DModulus(struct VECTOR2D *v);
extern float __cdecl Maths_Vector2DDistance(struct VECTOR2D *a,struct VECTOR2D *b);
extern float __cdecl Maths_Vector2DDotProduct(struct VECTOR2D *a,struct VECTOR2D *b);
extern struct VECTOR2D *__cdecl Maths_Vector2DSubtract(struct VECTOR2D *r,struct VECTOR2D *a,struct VECTOR2D *b);
extern struct VECTOR2D *__cdecl Maths_Vector2DAdd(struct VECTOR2D *r,struct VECTOR2D *a,struct VECTOR2D *b);
extern struct VECTOR2D *__cdecl Maths_Vector2DScale(struct VECTOR2D *r,struct VECTOR2D *a,float f);
extern struct VECTOR2D *__cdecl Maths_Vector2DNormalise(struct VECTOR2D *r);
extern struct VECTOR2D *__cdecl Maths_Vector2DSetLength(struct VECTOR2D *r,struct VECTOR2D *a,float l);
extern float __cdecl Maths_Vector2DCrossProductZ(struct VECTOR2D *a,struct VECTOR2D *b);
extern float __cdecl Maths_Vector3DModulus(struct VECTOR3D *v);
extern float __cdecl Maths_Vector3DDistance(struct VECTOR3D *a,struct VECTOR3D *b);
extern struct VECTOR3D *__cdecl Maths_Vector3DCrossProduct(struct VECTOR3D *r,struct VECTOR3D *a,struct VECTOR3D *b);
extern struct VECTOR3D *__cdecl Maths_Vector3DAdd(struct VECTOR3D *r,struct VECTOR3D *a,struct VECTOR3D *b);
extern struct VECTOR3D *__cdecl Maths_Vector3DSubtract(struct VECTOR3D *r,struct VECTOR3D *a,struct VECTOR3D *b);
extern float __cdecl Maths_Vector3DDotProduct(struct VECTOR3D *a,struct VECTOR3D *b);
extern struct VECTOR3D *__cdecl Maths_Vector3DScale(struct VECTOR3D *r,struct VECTOR3D *a,float f);
extern struct VECTOR3D *__cdecl Maths_Vector3DReflect(struct VECTOR3D *r, struct VECTOR3D *ray, struct VECTOR3D *normal);
extern struct VECTOR3D *__cdecl Maths_Vector3DNormalise(struct VECTOR3D *r);
extern struct VECTOR3D *__cdecl Maths_Vector3DRotate(struct VECTOR3D *result,struct VECTOR3D *vector,struct VECTOR3D *axis,float delta);
extern struct VECTOR3D *__cdecl Maths_Vector3DInterpolate(struct VECTOR3D *result,struct VECTOR3D *start,struct VECTOR3D *end,float delta);
extern void __cdecl Maths_IdentityMatrix(float (*m)[4]);
extern void __cdecl Maths_CopyMatrix(float (*copy)[4],float (*original)[4]);
extern void __cdecl Maths_MultiplyMatrix(float (*result)[4],float (*a)[4],float (*b)[4]);
extern void __cdecl Maths_MultiplyVectorByMatrix(struct VECTOR3D *vDest,struct VECTOR3D *vSrc,float (*mat)[4]);
extern void __cdecl Maths_MultiplyVector4DByMatrix(struct VECTOR4D *vDest,struct VECTOR4D *vSrc,float (*mat)[4]);
extern struct _D3DMATRIX *__cdecl Maths_GetD3DMATRIX(float (*mat)[4]);
extern void __cdecl Maths_SetD3DVECTOR(struct _D3DVECTOR *d3dvec, struct VECTOR3D *vec);
extern void __cdecl Maths_GetD3DVECTOR(struct VECTOR3D *vec, struct _D3DVECTOR *d3dvec);
extern void __cdecl Maths_InvertMatrixQuick(float (*r)[4],float (*mat)[4]);
extern void __cdecl Maths_SetMatrixRotation(float (*mat)[4],struct VECTOR3D *vec,float angle);
extern void __cdecl Maths_SetMatrixOrientation(float (*m)[4],struct VECTOR3D *vFrom,struct VECTOR3D *vDir,struct VECTOR3D *vWorldUp);
extern struct VECTOR3D *__cdecl Maths_PlaneNormal(struct VECTOR3D *n,struct VECTOR3D *p1,struct VECTOR3D *p2,struct VECTOR3D *p3);
extern void __cdecl Maths_InvertMatrixFull(float (*r)[4],float (*mat)[4]);
static void __cdecl Maths_MatrixAdjoint(float (*in)[4],float (*out)[4]);
static float __cdecl Maths_MatrixDeterminant4x4(float (*m)[4]);
static float __cdecl Maths_MatrixDeterminant3x3(float a1,float a2,float a3,float b1,float b2,float b3,float c1,float c2,float c3);
static float __cdecl Maths_MatrixDeterminant2x2(float a,float b,float c,float d);
extern float __cdecl Maths_Power(float base,float exponent);
extern float __cdecl Maths_PointLineDistance(struct VECTOR3D *point,struct VECTOR3D *start,struct VECTOR3D *end);
extern int __cdecl Maths_RayPlaneIntersectionFast(struct VECTOR3D *endPoint, struct VECTOR3D *rayOrigin, struct VECTOR3D *ray, struct VECTOR3D *planePoint, struct VECTOR3D *planeNormal);
extern int __cdecl Maths_RayPlaneIntersection(struct VECTOR3D *endPoint,struct VECTOR3D *rayOrigin,struct VECTOR3D *ray,struct VECTOR3D *planePoint,struct VECTOR3D *planeNormal);
extern int __cdecl Maths_RayPlaneDistance(float *dist,struct VECTOR3D *rayOrigin,struct VECTOR3D *ray,struct VECTOR3D *planePoint,struct VECTOR3D *planeNormal);
extern void __cdecl Maths_RayEndPoint(struct VECTOR3D *endPoint,struct VECTOR3D *rayOrigin,struct VECTOR3D *ray,float dist);
extern int __cdecl Maths_PointInsidePoly(struct VECTOR2D *point,struct VECTOR2D *fromList,struct VECTOR2D *toList,unsigned long count);
extern int __cdecl Maths_PointOnLine(struct VECTOR3D *point, struct VECTOR3D *start, struct VECTOR3D *end);
// Auto Prototypes

#endif // !_RGL_MATHS_H_
