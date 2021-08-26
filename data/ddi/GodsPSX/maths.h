//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Maths.c - [Maths Handling Code]
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#define	M_PI	(ONE*3.14159265)
#define	M_PI2	(ONE*3.14159265*2)

#define Maths_Vector2DNormalise(r)		Maths_Vector2DNormalize(r)
#define Maths_Vector3DLength(v)			Maths_Vector3DModulus(v)
#define Maths_Vector2DLength(v)			Maths_Vector2DModulus(v)

#define Maths_Cos(a)						(REAL)rcos((REAL)(a))
#define Maths_Sin(a)						(REAL)rsin((REAL)(a))
//#define Maths_Tan(a)						(REAL)tan((double)(a))
//#define Maths_ACos(a)						(REAL)acos((double)(a))
//#define Maths_ASin(a)						(REAL)asin((double)(a))
//#define Maths_ATan(a)						(REAL)atan((double)(a))



LPVECTOR3D Maths_Vector2DMake3D(LPVECTOR3D r, LPVECTOR2D v);
LPVECTOR2D Maths_Vector3DMake2D(LPVECTOR2D r, LPVECTOR3D v);

REAL			Maths_Vector2DModulus(LPVECTOR2D v);
REAL			Maths_Vector2DDistance(LPVECTOR2D a, LPVECTOR2D b);
REAL			Maths_Vector2DDotProduct(LPVECTOR2D a, LPVECTOR2D b);
LPVECTOR2D Maths_Vector2DSubtract(LPVECTOR2D r, LPVECTOR2D a, LPVECTOR2D b);
LPVECTOR2D Maths_Vector2DAdd(LPVECTOR2D r, LPVECTOR2D a, LPVECTOR2D b);
LPVECTOR2D Maths_Vector2DScale(LPVECTOR2D r, LPVECTOR2D a, REAL f);
LPVECTOR2D Maths_Vector2DNormalize(LPVECTOR2D r);
LPVECTOR2D Maths_Vector2DSetLength(LPVECTOR2D r, LPVECTOR2D a, REAL l);
LPVECTOR2D Maths_Vector2DRandom(LPVECTOR2D r);

REAL			Maths_Vector3DModulus(LPVECTOR3D v);
REAL			Maths_Vector3DDistance(LPVECTOR3D a, LPVECTOR3D b);
REAL 		Maths_Vector3DDotProduct(LPVECTOR3D a, LPVECTOR3D b);
LPVECTOR3D	Maths_Vector3DSubtract(LPVECTOR3D r, LPVECTOR3D a, LPVECTOR3D b);
LPVECTOR3D	Maths_Vector3DAdd(LPVECTOR3D r, LPVECTOR3D a, LPVECTOR3D b);
LPVECTOR3D Maths_SVector3DAdd(LPVECTOR3D r, LPVECTOR3D a, lpSVECTOR b);
LPVECTOR3D Maths_Vector3DScale(LPVECTOR3D r, LPVECTOR3D a, REAL f);
LPVECTOR3D Maths_Vector3DRandom(LPVECTOR3D r);
LPVECTOR3D Maths_Vector3DNormalize(LPVECTOR3D r);
LPVECTOR3D Maths_Vector3DNormalise(LPVECTOR3D r);
LPVECTOR3D Maths_Vector3DNormalizeFixed(LPVECTOR3D r);
LPVECTOR3D Maths_Vector3DNormaliseFixed(LPVECTOR3D r);
LPVECTOR3D	Maths_Vector3DCrossProduct(LPVECTOR3D r, LPVECTOR3D a, LPVECTOR3D b);
LPVECTOR3D Maths_Vector3DRotate(LPVECTOR3D r, LPVECTOR3D v, LPVECTOR3D axis, REAL theta);

REAL			Maths_RandRange(REAL low, REAL high);
REAL			Maths_TriangleAreaZ(LPVECTOR3D p1, LPVECTOR3D p2, LPVECTOR3D p3, BOOL bfc);
LPVECTOR3D Maths_PlaneNormal(LPVECTOR3D n, LPVECTOR3D p1, LPVECTOR3D p2, LPVECTOR3D p3);
