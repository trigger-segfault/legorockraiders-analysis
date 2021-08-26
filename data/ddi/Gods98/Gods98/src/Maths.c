
#include <d3drm.h>

#include "..\inc\Standard.h"
#include "..\inc\Maths.h"

//LPVECTOR3D Maths_Vector3DAdd(LPVECTOR3D r, LPVECTOR3D a, LPVECTOR3D b){
//	return (LPVECTOR3D) D3DRMVectorAdd((LPD3DVECTOR) r, (LPD3DVECTOR) a, (LPD3DVECTOR) b);
//}
//LPVECTOR3D Maths_Vector3DCrossProduct(LPVECTOR3D r, LPVECTOR3D a, LPVECTOR3D b){
//	return (LPVECTOR3D) D3DRMVectorCrossProduct((LPD3DVECTOR) r, (LPD3DVECTOR) a, (LPD3DVECTOR) b);
//}
//REAL Maths_Vector3DDotProduct(LPVECTOR3D a, LPVECTOR3D b){
//	return D3DRMVectorDotProduct((LPD3DVECTOR) a, (LPD3DVECTOR) b);
//}
//REAL Maths_Vector3DModulus(LPVECTOR3D a){
//	return D3DRMVectorModulus((LPD3DVECTOR) a);
//}
//LPVECTOR3D Maths_Vector3DNormalize(LPVECTOR3D r){
//	return (LPVECTOR3D) D3DRMVectorNormalize((LPD3DVECTOR) r);
//}
LPVECTOR3D Maths_Vector3DRandom(LPVECTOR3D r){
	return (LPVECTOR3D) D3DRMVectorRandom((LPD3DVECTOR) r);
}
LPVECTOR3D Maths_Vector3DReflect(LPVECTOR3D d, LPVECTOR3D ray, LPVECTOR3D norm){
	return (LPVECTOR3D) D3DRMVectorReflect((LPD3DVECTOR) d, (LPD3DVECTOR) ray, (LPD3DVECTOR) norm);
}
LPVECTOR3D Maths_Vector3DRotate(LPVECTOR3D r, LPVECTOR3D v, LPVECTOR3D axis, REAL theta){
	return (LPVECTOR3D) D3DRMVectorRotate((LPD3DVECTOR) r, (LPD3DVECTOR) v, (LPD3DVECTOR) axis, theta);
}
//LPVECTOR3D Maths_Vector3DScale(LPVECTOR3D r, LPVECTOR3D a, REAL f){
//	return (LPVECTOR3D) D3DRMVectorScale((LPD3DVECTOR) r, (LPD3DVECTOR) a, f);
//}
//LPVECTOR3D Maths_Vector3DSubtract(LPVECTOR3D r, LPVECTOR3D a, LPVECTOR3D b){
//	return (LPVECTOR3D) D3DRMVectorSubtract((LPD3DVECTOR) r, (LPD3DVECTOR) a, (LPD3DVECTOR) b);
//}

__inline LPAREA2D Maths_Area2DInterpolate(LPAREA2D result, LPAREA2D start, LPAREA2D end, REAL delta) {
	
	result->x = end->x - start->x;
	result->y = end->y - start->y;
	result->width = end->width - start->width;
	result->height = end->height - start->height;

	result->x *= delta;
	result->y *= delta;
	result->width *= delta;
	result->height *= delta;
	
	result->x = start->x + result->x;
	result->y = start->y + result->y;
	result->width = start->width + result->width;
	result->height = start->height + result->height;
	
	return result;
}

LPVECTOR3D Maths_PlaneNormal(LPVECTOR3D n, LPVECTOR3D p1, LPVECTOR3D p2, LPVECTOR3D p3){ 

	VECTOR3D v1, v2;

  	Maths_Vector3DSubtract(&v1, p2, p1);
	Maths_Vector3DSubtract(&v2, p3, p2);
	Maths_Vector3DCrossProduct(n, &v1, &v2);
	return Maths_Vector3DNormalize(n);
}

REAL Maths_TriangleAreaZ(LPVECTOR3D p1, LPVECTOR3D p2, LPVECTOR3D p3, BOOL bfc){

	VECTOR3D norm;
	REAL area = 0.0f, maxLen = 0.0f, len[3], angle, height;
	ULONG loop, base, next;
	VECTOR3D edgeVec[3], p[3];
	LPVECTOR3D edgeDef[3][2] = { { &p[0], &p[1] }, { &p[1], &p[2] }, { &p[2], &p[0] } }, point;

	// Ignore the z value, but don't clear it in the original...

	p[0] = *p1; p[0].z = 0.0f;
	p[1] = *p2; p[1].z = 0.0f;
	p[2] = *p3; p[2].z = 0.0f;

	if (bfc) Maths_PlaneNormal(&norm, &p[0], &p[1], &p[2]);
	else norm.z = -1.0f;

	// Backface cull if required...
	if (norm.z < 0.0f) {

		for (loop=0 ; loop<3 ; loop++){

			// Store a set of lengths and vectors...
			Maths_Vector3DSubtract(&edgeVec[loop], edgeDef[loop][1], edgeDef[loop][0]);
			len[loop] = Maths_Vector3DModulus(&edgeVec[loop]);

			// Normalise the vector (for the angle calculation)...
			Maths_Vector3DScale(&edgeVec[loop], &edgeVec[loop], 1.0f/len[loop]);

			// Find which is the longest edge to use as the base...
			if (len[loop] > maxLen) {
				maxLen = len[loop];
				base = loop;
			}
		}

		// Use the end point of the base line as the test point
		// then reverse the vector of the base line to point away from this point...
		point = edgeDef[base][1];
		Maths_Vector3DScale(&edgeVec[base], &edgeVec[base], -1.0f);

		// Calculate the angle between the base and the 'next' side...
		// Obtain the height from the angle and the length of the adjacent edge.
		next = (base + 1) % 3;
		angle = (REAL) acos(Maths_Vector3DDotProduct(&edgeVec[base], &edgeVec[next]));
		if (_finite(angle)) {

			height = (REAL) sin(angle) * len[next];

			// 1/2base * height...
			area = (len[base] / 2.0f) * height;
		}
	}

	return area;
}

SWORD Maths_Rand(VOID){

	return rand();
}

REAL Maths_RandRange(REAL low, REAL high){

	REAL val = (REAL) Maths_Rand();
	val /= RAND_MAX;

	val *= (high-low);
	return low + val;
}

BOOL Maths_RayPlaneIntersection(LPVECTOR3D endPoint, LPVECTOR3D rayOrigin, LPVECTOR3D ray, LPVECTOR3D planePoint, LPVECTOR3D planeNormal){

	VECTOR3D r = *ray, n = *planeNormal;
	REAL dist;

	Maths_Vector3DNormalise(&r);
	Maths_Vector3DNormalise(&n);
	
	if (Maths_RayPlaneDistance(&dist, rayOrigin, &r, planePoint, &n)){
		Maths_RayEndPoint(endPoint, rayOrigin, &r, dist);
		return TRUE;
	}
	return FALSE;
}

BOOL Maths_RayPlaneDistance(LPREAL dist, LPVECTOR3D rayOrigin, LPVECTOR3D ray, LPVECTOR3D planePoint, LPVECTOR3D planeNormal){

	VECTOR3D point;
	REAL t;

	if ((t = Maths_Vector3DDotProduct(planeNormal, ray)) != 0.0f){

		// Translate the point in the plane so that the ray would originate from (0,0,0).
		Maths_Vector3DSubtract(&point, planePoint, rayOrigin);

		*dist = Maths_Vector3DDotProduct(planeNormal, &point) / t;

		return TRUE;
	}
	return FALSE;
}

VOID Maths_RayEndPoint(LPVECTOR3D endPoint, LPVECTOR3D rayOrigin, LPVECTOR3D ray, REAL dist) {

	VECTOR3D temp;

	Maths_Vector3DScale(&temp, ray, dist);
	Maths_Vector3DAdd(endPoint, rayOrigin, &temp);
}

LPVECTOR2D Maths_Vector2DLineIntersection(LPVECTOR2D intersection, LPVECTOR2D start1, LPVECTOR2D end1, LPVECTOR2D start2, LPVECTOR2D end2) {

	VECTOR2D vector1, vector2;
	REAL length1, length2;
	VECTOR2D siVec;

	Maths_Vector2DSubtract(&vector1, end1, start1);
	length1 = Maths_Vector2DLength(&vector1);
	Maths_Vector2DScale(&vector1, &vector1, 1.0f / length1);
	Maths_Vector2DSubtract(&vector2, end2, start2);
	length2 = Maths_Vector2DLength(&vector2);
	Maths_Vector2DScale(&vector2, &vector2, 1.0f / length2);

	if (Maths_Vector2DIntersection(intersection, start1, &vector1, start2, &vector2)) {
		Maths_Vector2DSubtract(&siVec, intersection, start1);
		if (Maths_Vector2DDotProduct(&siVec, &vector1) >= 0.0f) {
			Maths_Vector2DSubtract(&siVec, intersection, start2);
			if (Maths_Vector2DDotProduct(&siVec, &vector2) >= 0.0f) {
				if (length1 >= Maths_Vector2DDistance(intersection, start1) &&
					length2 >= Maths_Vector2DDistance(intersection, start2)) {

					return intersection;
				}
			}
		}
	}

	return NULL;
}

LPVECTOR2D Maths_Vector2DIntersection(LPVECTOR2D intersection, LPVECTOR2D start1, LPVECTOR2D vector1, LPVECTOR2D start2, LPVECTOR2D vector2) {

	REAL a, b, c, d;
	REAL determinant;

	a =  vector2->x;
	b = -vector1->x;
	c =  vector2->y;
	d = -vector1->y;

	determinant = ( (a * d) - (b * c) );

	if (0.0f != determinant) {

		REAL invc, invd;
		REAL t, x = start1->x - start2->x, y = start1->y - start2->y;

		invc = -c / determinant;
		invd =  a / determinant;

		t = invc * x + invd * y;

		Maths_Vector2DScale(intersection, vector1, t);
		Maths_Vector2DAdd(intersection, start1, intersection);

		return intersection;
	}

	return NULL;
}

BOOL Maths_PointInsidePoly(LPVECTOR2D point, LPVECTOR2D fromList, LPVECTOR2D toList, ULONG count){

	// Count the edges to the right of the point and return TRUE if it is odd...

	ULONG loop, rightCount=0;
	REAL inter, alt, slope, line;

	for (loop=0 ; loop<count ; loop++){
		if ((fromList[loop].y <= point->y && toList[loop].y >= point->y) ||
			(fromList[loop].y >= point->y && toList[loop].y <= point->y)){

			alt = toList[loop].y - fromList[loop].y;
			slope = toList[loop].x - fromList[loop].x;
			line = point->y - fromList[loop].y;

			inter = fromList[loop].x + ((line / alt) * slope);

			if (inter > point->x) rightCount++;
		}
	}

	return (rightCount & 0x00000001);
}

LPVECTOR3D Maths_Vector3DApplyMatrixXYZ( LPVECTOR3D result, MATRIX4D matrix, REAL x, REAL y, REAL z )
{	//REAL tx, ty, tz, tw;


//	tx = (matrix[0][0] * x) + (matrix[1][0] * y) + (matrix[2][0] * z) + matrix[3][0];
//	ty = (matrix[0][1] * x) + (matrix[1][1] * y) + (matrix[2][1] * z) + matrix[3][1];
//	tz = (matrix[0][2] * x) + (matrix[1][2] * y) + (matrix[2][2] * z) + matrix[3][2];
//	tw = (matrix[0][3] * x) + (matrix[1][3] * y) + (matrix[2][3] * z) + matrix[3][3];

//	if( fabs( w ) < 1.0e-5f )                 // Tolerance for FLOATs
//      Error_Warn( TRUE, "Invalid arguments." );

//	result->x = tx/tw;
//	result->y = ty/tw;
//	result->z = tz/tw;

    result->x = (matrix[0][0] * x) + (matrix[1][0] * y) + (matrix[2][0] * z) + matrix[3][0];
	result->y = (matrix[0][1] * x) + (matrix[1][1] * y) + (matrix[2][1] * z) + matrix[3][1];
	result->z = (matrix[0][2] * x) + (matrix[1][2] * y) + (matrix[2][2] * z) + matrix[3][2];

	return result;

}

BOOL Maths_RaySphereIntersection(LPVECTOR3D center, REAL radius, LPVECTOR3D camera, LPVECTOR3D line) {

//	P = Center of sphere
//	L = line = L(t) = Q + tV
//	Q = Any point on line (camera pos)
//	V = normalise direction of line.
//	R = Radius of sphere
//
//	Intersection occurs if : 
//
//	( (2V .(Q - P)) ^ 2 ) - ( 4 * (V.V) * ((Q - P) . (Q - P) - R^2 ) ) > 0

	VECTOR3D csVec, ray = *line;
	REAL t;

//	Maths_Vector3DNormalise(&ray);
	Maths_Vector3DScale(&ray, &ray, 2.0f);
	Maths_Vector3DSubtract(&csVec, camera, center);
//	( (2V . csVec) ^ 2 ) - ( 4 * (V.V) * (csVec . csVec - R^2 ) ) > 0
	
	t = Maths_Vector3DDotProduct(&ray, &csVec);
	t *= t;
	t -= (4 * Maths_Vector3DDotProduct(&csVec, &csVec) - (radius * radius));

	return (t > 0);
}

/////////////////////////////////////////////////////////////////////////
// Andy Ray.  3/2/99.
// Some simple matrix functions.
/////////////////////////////////////////////////////////////////////////

// Multiplies to matrices together.
VOID Matrix_Mult(MATRIX4D ans, MATRIX4D a, MATRIX4D b)
{
	SLONG i, j, k;
	Matrix_Zero(ans);
	for (i=0; i<4; i++) 
	{
		for (j=0; j<4; j++) 
		{
			for (k=0; k<4; k++) 
			{
				ans[i][j] += a[k][j] * b[i][k];
			}
		}
	}
}

// Generates the matrix for a rotation of rot radians about the X-Axis
VOID Matrix_RotX(MATRIX4D ans, REAL rot)
{
	REAL cosine, sine;

	cosine = (REAL) Maths_Cos(rot);
	sine = (REAL) Maths_Sin(rot);
    Matrix_Identity(ans);

    ans[1][1] = cosine;
	ans[2][2] = cosine;
	ans[1][2] = -sine;
	ans[2][1] =  sine;
}

// Generates the matrix for a rotation of rot radians about the Y-Axis
VOID Matrix_RotY(MATRIX4D ans, REAL rot)
{
	REAL cosine, sine;

	cosine = (REAL) Maths_Cos(rot);
	sine = (REAL) Maths_Sin(rot);
    Matrix_Identity(ans);

    ans[0][0] = cosine;
	ans[2][2] = cosine;
	ans[0][2] =  sine;
	ans[2][0] = -sine;
}

// Generates the matrix for a rotation of rot radians about the Z-Axis
VOID Matrix_RotZ(MATRIX4D ans, REAL rot)
{
	REAL cosine, sine;

	cosine = (REAL) Maths_Cos(rot);
	sine = (REAL) Maths_Sin(rot);
    Matrix_Identity(ans);

    ans[0][0] = cosine;
	ans[1][1] = cosine;
	ans[0][1] = -sine;
	ans[1][0] =  sine;
}

// Generates a translation matrix.
VOID Matrix_Translate(MATRIX4D ans, LPVECTOR3D trans)
{
	Matrix_Identity(ans);
	ans[3][0] = trans->x;
	ans[3][1] = trans->y;
	ans[3][2] = trans->z;
}

// Makes the identity matrix
VOID Matrix_Identity(MATRIX4D ans)
{
	SLONG i, j;
	for (i=0; i<4; i++)
	{
		for (j=0; j<4; j++)
		{
			ans[i][j] = (i == j) ? 1.0f : 0.0f;
		}
	}
}

// Makes the zero matrix.
VOID Matrix_Zero(MATRIX4D ans)
{
	SLONG i, j;
	for (i=0; i<4; i++)
	{
		for (j=0; j<4; j++)
		{
			ans[i][j] = 0.0f;
		}
	}
}

// Copies a matrix.
VOID Matrix_Copy(MATRIX4D to, MATRIX4D from)
{
	int i, j;
	for (i=0; i<4; i++)
	{
		for (j=0; j<4; j++)
		{
			to[i][j] = from[i][j];
		}
	}
}

BOOL Matrix_Invert(MATRIX4D q, MATRIX4D a)
{
	REAL fDetInv;
	
	if( fabs(a[3][3] - 1.0f) > .001f)
		return FALSE;
	if( fabs(a[0][3]) > .001f || fabs(a[1][3]) > .001f || fabs(a[2][3]) > .001f )
		return FALSE;
	
	fDetInv = 1.0f / ( a[0][0] * ( a[1][1] * a[2][2] - a[1][2] * a[2][1] ) -
		a[0][1] * ( a[1][0] * a[2][2] - a[1][2] * a[2][0] ) +
		a[0][2] * ( a[1][0] * a[2][1] - a[1][1] * a[2][0] ) );
	
	q[0][0] =  fDetInv * ( a[1][1] * a[2][2] - a[1][2] * a[2][1] );
	q[0][1] = -fDetInv * ( a[0][1] * a[2][2] - a[0][2] * a[2][1] );
	q[0][2] =  fDetInv * ( a[0][1] * a[1][2] - a[0][2] * a[1][1] );
	q[0][3] = 0.0f;
	
	q[1][0] = -fDetInv * ( a[1][0] * a[2][2] - a[1][2] * a[2][0] );
	q[1][1] =  fDetInv * ( a[0][0] * a[2][2] - a[0][2] * a[2][0] );
	q[1][2] = -fDetInv * ( a[0][0] * a[1][2] - a[0][2] * a[1][0] );
	q[1][3] = 0.0f;
	
	q[2][0] =  fDetInv * ( a[1][0] * a[2][1] - a[1][1] * a[2][0] );
	q[2][1] = -fDetInv * ( a[0][0] * a[2][1] - a[0][1] * a[2][0] );
	q[2][2] =  fDetInv * ( a[0][0] * a[1][1] - a[0][1] * a[1][0] );
	q[2][3] = 0.0f;
	
	q[3][0] = -( a[3][0] * q[0][0] + a[3][1] * q[1][0] + a[3][2] * q[2][0] );
	q[3][1] = -( a[3][0] * q[0][1] + a[3][1] * q[1][1] + a[3][2] * q[2][1] );
	q[3][2] = -( a[3][0] * q[0][2] + a[3][1] * q[1][2] + a[3][2] * q[2][2] );
	q[3][3] = 1.0f;
	
	return TRUE;
}
