//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Maths Handler For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

// Include all Header Files

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
#include	"..\inc\libgods.h"
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ


LPVECTOR3D Maths_Vector2DMake3D(LPVECTOR3D r, LPVECTOR2D v)
{
	r->x = v->x;
	r->y = v->y;
	r->z = 0;
	return r;
}

LPVECTOR2D Maths_Vector3DMake2D(LPVECTOR2D r, LPVECTOR3D v)
{
	r->x = v->x;
	r->y = v->y;
	return r;
}


REAL Maths_Vector2DModulus(LPVECTOR2D v)
{
	return (REAL) SquareRoot12(Asm_MulFIX(v->x,v->x)+Asm_MulFIX(v->y,v->y));
}

REAL Maths_Vector2DDistance(LPVECTOR2D a, LPVECTOR2D b)
{
	return (REAL) SquareRoot12(Asm_MulFIX(a->x-b->x, a->x-b->x)+Asm_MulFIX(a->y-b->y, a->y-b->y));
}

REAL Maths_Vector2DDotProduct(LPVECTOR2D a, LPVECTOR2D b)
{
	return (REAL) (Asm_MulFIX(a->x, b->x) + Asm_MulFIX(a->y, b->y));
}

LPVECTOR2D Maths_Vector2DSubtract(LPVECTOR2D r, LPVECTOR2D a, LPVECTOR2D b)
{
	r->x = a->x - b->x;
	r->y = a->y - b->y;
	return r;
}

LPVECTOR2D Maths_Vector2DAdd(LPVECTOR2D r, LPVECTOR2D a, LPVECTOR2D b)
{
	r->x = a->x + b->x;
	r->y = a->y + b->y;
	return r;
}

LPVECTOR2D Maths_Vector2DScale(LPVECTOR2D r, LPVECTOR2D a, REAL f)
{
	r->x = Asm_MulFIX(a->x, f);
	r->y = Asm_MulFIX(a->y, f);
	return r;
}

LPVECTOR2D Maths_Vector2DNormalize(LPVECTOR2D r)
{
	Maths_Vector2DScale(r, r, Asm_DivFIX(ONE, Maths_Vector2DLength(r)));
	return r;
}

LPVECTOR2D Maths_Vector2DSetLength(LPVECTOR2D r, LPVECTOR2D a, REAL l)
{
	REAL m = Maths_Vector2DModulus(a);
	return Maths_Vector2DScale(r, a, Asm_DivFIX(Asm_MulFIX(ONE, l), m));
}

LPVECTOR2D Maths_Vector2DRandom(LPVECTOR2D r)
{
	r->x = Maths_RandRange(0, ONE);
	r->y = Maths_RandRange(0, ONE);
	return Maths_Vector2DNormalise(r);
}

REAL Maths_Vector3DModulus(LPVECTOR3D v)
{
	return (REAL) SquareRoot12(Asm_MulFIX(v->x, v->x)+Asm_MulFIX(v->y, v->y)+Asm_MulFIX(v->z, v->z));
}

REAL Maths_Vector3DDistance(LPVECTOR3D a, LPVECTOR3D b)
{
	return (REAL) SquareRoot12(Asm_MulFIX(a->x-b->x, a->x-b->x)+Asm_MulFIX(a->y-b->y, a->y-b->y)+Asm_MulFIX(a->z-b->z, a->z-b->z));
}

REAL Maths_Vector3DDotProduct(LPVECTOR3D a, LPVECTOR3D b)
{
	return Asm_MulFIX(a->x, b->x) + Asm_MulFIX(a->y, b->y) + Asm_MulFIX(a->z, b->z);
}

LPVECTOR3D Maths_Vector3DSubtract(LPVECTOR3D r, LPVECTOR3D a, LPVECTOR3D b)
{
	r->x = (a->x - b->x);
	r->y = (a->y - b->y);
	r->z = (a->z - b->z);
	return r;
}
 
LPVECTOR3D Maths_Vector3DAdd(LPVECTOR3D r, LPVECTOR3D a, LPVECTOR3D b)
{
	r->x = (a->x + b->x);
	r->y = (a->y + b->y);
	r->z = (a->z + b->z);
	return r;
}

LPVECTOR3D Maths_SVector3DAdd(LPVECTOR3D r, LPVECTOR3D a, lpSVECTOR b)
{
	r->x = (a->x + b->vx);
	r->y = (a->y + b->vy);
	r->z = (a->z + b->vz);
	return r;
}

LPVECTOR3D Maths_Vector3DScale(LPVECTOR3D r, LPVECTOR3D a, REAL f)
{
	r->x = Asm_MulFIX(a->x, f);
	r->y = Asm_MulFIX(a->y, f);
	r->z = Asm_MulFIX(a->z, f);
	return r;
}

LPVECTOR3D Maths_Vector3DRandom(LPVECTOR3D r)
{
	return r;
}

LPVECTOR3D Maths_Vector3DNormalize(LPVECTOR3D r)
{
	VectorNormal((LPVECTOR)r, (LPVECTOR)r);

	return r;
}

LPVECTOR3D Maths_Vector3DNormalise(LPVECTOR3D r)
{
	VectorNormal((LPVECTOR)r, (LPVECTOR)r);

	return r;
}

LPVECTOR3D Maths_Vector3DNormaliseFixed(LPVECTOR3D r)
{
	if(abs(r->x) > ONE) r->x >>= 12;
	if(abs(r->y) > ONE) r->y >>= 12;
	if(abs(r->z) > ONE) r->z >>= 12;
	VectorNormal((LPVECTOR)r, (LPVECTOR)r);
//	r->x <<= 12;
//	r->y <<= 12;
//	r->z <<= 12;

	return r;
}

LPVECTOR3D Maths_Vector3DNormalizeFixed(LPVECTOR3D r)
{
	if(abs(r->x) > ONE) r->x >>= 12;
	if(abs(r->y) > ONE) r->y >>= 12;
	if(abs(r->z) > ONE) r->z >>= 12;
	VectorNormal((LPVECTOR)r, (LPVECTOR)r);
//	r->x <<= 12;
//	r->y <<= 12;
//	r->z <<= 12;

	return r;
}

LPVECTOR3D Maths_Vector3DCrossProduct(LPVECTOR3D r, LPVECTOR3D a, LPVECTOR3D b)
{
	r->x = Asm_MulFIX(a->y, b->z) - Asm_MulFIX(a->z, b->y);
	r->y = Asm_MulFIX(a->z, b->x) - Asm_MulFIX(a->x, b->z);
	r->z = Asm_MulFIX(a->x, b->y) - Asm_MulFIX(a->y, b->x);
	return r;
}

LPVECTOR3D Maths_Vector3DRotate(LPVECTOR3D r, LPVECTOR3D v, LPVECTOR3D axis, REAL theta)
{
}

REAL	Maths_RandRange(REAL low, REAL high)
{
	REAL	num;

	num = Asm_Random();

	while(num<low) num+=low;
	while(num>=high) num-=high;

	return num;
}

REAL Maths_TriangleAreaZ(LPVECTOR3D p1, LPVECTOR3D p2, LPVECTOR3D p3, BOOL bfc)
{
	VECTOR3D norm;
	REAL area = 0, maxLen = 0, len[3], angle, height;
	ULONG loop, base, next;
	VECTOR3D edgeVec[3], p[3];
	LPVECTOR3D edgeDef[3][2] = { { &p[0], &p[1] }, { &p[1], &p[2] }, { &p[2], &p[0] } }, point;

	// Ignore the z value, but don't clear it in the original...

	p[0] = *p1; p[0].z = 0;
	p[1] = *p2; p[1].z = 0;
	p[2] = *p3; p[2].z = 0;

	if (bfc) Maths_PlaneNormal(&norm, &p[0], &p[1], &p[2]);
	else norm.z = -ONE;

	// Backface cull if required...
	if (norm.z < 0)
		{
		for (loop=0 ; loop<3 ; loop++)
			{
			// Store a set of lengths and vectors...
			Maths_Vector3DSubtract(&edgeVec[loop], edgeDef[loop][1], edgeDef[loop][0]);
			len[loop] = Maths_Vector3DModulus(&edgeVec[loop]);

			// Normalise the vector (for the angle calculation)...
			Maths_Vector3DScale(&edgeVec[loop], &edgeVec[loop], Asm_DivFIX(ONE, len[loop]));

			// Find which is the longest edge to use as the base...
			if (len[loop] > maxLen)
				{
				maxLen = len[loop];
				base = loop;
				}
			}

		// Use the end point of the base line as the test point
		// then reverse the vector of the base line to point away from this point...
		point = edgeDef[base][1];
		Maths_Vector3DScale(&edgeVec[base], &edgeVec[base], -ONE);

		// Calculate the angle between the base and the 'next' side...
		// Obtain the height from the angle and the length of the adjacent edge.
		next = (base + 1) % 3;
		angle = (REAL) Asm_DivFIX(rcos(Maths_Vector3DDotProduct(&edgeVec[base], &edgeVec[next])), M_PI);
		height = (REAL) Asm_MulFIX(rsin(angle),len[next]);

		// 1/2base * height...
		area = Asm_MulFIX(len[base], height)/2;
	}

	return area;
}


LPVECTOR3D Maths_PlaneNormal(LPVECTOR3D n, LPVECTOR3D p1, LPVECTOR3D p2, LPVECTOR3D p3)
{ 
	VECTOR3D v1, v2;

 	Maths_Vector3DSubtract(&v1, p2, p1);
	Maths_Vector3DSubtract(&v2, p3, p2);
	Maths_Vector3DCrossProduct( n, &v1, &v2);
	return (LPVECTOR3D) Maths_Vector3DNormalizeFixed(n);
}

REAL	Maths_ACos(double a)
{
	return (REAL)acos(a)*ONE;
}

REAL	Maths_ASin(double a)
{
	return (REAL)asin(a)*ONE;
}

REAL	Maths_ATan(double a)
{
	return (REAL)atan(a)*ONE;
}
