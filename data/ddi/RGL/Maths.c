
#include <d3d.h>
#include "Standard.h"
#include "Errors.h"
#include "Maths.h"

__inline REAL Maths_Mod(REAL a, REAL b) {

	return (REAL) fmod(a, b);
}

__inline REAL Maths_RandRange(REAL low, REAL high) {

	return Maths_Interpolate(low, high, Maths_InterpolationDelta(0.0f, RAND_MAX, (REAL) rand()));
}

__inline REAL Maths_InterpolationDelta(REAL start, REAL end, REAL current) {

	return (current - start) / (end - start);
}

__inline REAL Maths_Interpolate(REAL start, REAL end, REAL delta) {

	return start + ((end - start) * delta);
}

__inline REAL Maths_Vector2DModulus(LPVECTOR2D v) {

	return (REAL) sqrt((v->x * v->x) + (v->y * v->y));
}

__inline REAL Maths_Vector2DDistance(LPVECTOR2D a, LPVECTOR2D b) {

	return (REAL) sqrt(((a->x - b->x) * (a->x - b->x)) + ((a->y - b->y) * (a->y - b->y)));
}

__inline REAL Maths_Vector2DDotProduct(LPVECTOR2D a, LPVECTOR2D b) {

	return ((a->x * b->x) + (a->y * b->y));
}

__inline LPVECTOR2D Maths_Vector2DSubtract(LPVECTOR2D r, LPVECTOR2D a, LPVECTOR2D b) {

	r->x = a->x - b->x; r->y = a->y - b->y;
	return r;
}

__inline LPVECTOR2D Maths_Vector2DAdd(LPVECTOR2D r, LPVECTOR2D a, LPVECTOR2D b) {

	r->x = a->x + b->x; r->y = a->y + b->y; return r;
}

__inline LPVECTOR2D Maths_Vector2DScale(LPVECTOR2D r, LPVECTOR2D a, REAL f) {

	r->x = a->x * f; r->y = a->y * f; return r;
}

__inline LPVECTOR2D Maths_Vector2DNormalise(LPVECTOR2D r) {
	
	Maths_Vector2DScale(r, r, 1.0f/Maths_Vector2DLength(r));
	return r;
}

__inline LPVECTOR2D Maths_Vector2DSetLength(LPVECTOR2D r, LPVECTOR2D a, REAL l) {
	
	REAL m = Maths_Vector2DModulus(a);
	return Maths_Vector2DScale(r, a, (1.0f/m) * l);
}

__inline REAL Maths_Vector2DCrossProductZ(LPVECTOR2D a, LPVECTOR2D b) {
	
	return (a->x * b->y) - (a->y * b->x);
}

__inline REAL Maths_Vector3DModulus(LPVECTOR3D v) {

	return (REAL) sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
}

__inline REAL Maths_Vector3DDistance(LPVECTOR3D a, LPVECTOR3D b) {
	
	return (REAL) sqrt(((a->x - b->x) * (a->x - b ->x)) + ((a->y - b->y) * (a->y - b->y)) + ((a->z - b->z) * (a->z - b->z)));
}

__inline LPVECTOR3D Maths_Vector3DCrossProduct(LPVECTOR3D r, LPVECTOR3D a, LPVECTOR3D b) {

	r->x = (a->y * b->z) - (a->z * b->y);
	r->y = (a->z * b->x) - (a->x * b->z);
	r->z = (a->x * b->y) - (a->y * b->x);
	return r;
}

__inline LPVECTOR3D Maths_Vector3DAdd(LPVECTOR3D r, LPVECTOR3D a, LPVECTOR3D b) {

	r->x = (a->x + b->x); r->y = (a->y + b->y); r->z = (a->z + b->z);
	return r;
}

__inline LPVECTOR3D Maths_Vector3DSubtract(LPVECTOR3D r, LPVECTOR3D a, LPVECTOR3D b) {

	r->x = (a->x - b->x); r->y = (a->y - b->y); r->z = (a->z - b->z);
	return r;
}

__inline REAL Maths_Vector3DDotProduct(LPVECTOR3D a, LPVECTOR3D b) {
	
	return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

__inline LPVECTOR3D Maths_Vector3DScale(LPVECTOR3D r, LPVECTOR3D a, REAL f) {
	
	r->x = a->x * f; r->y = a->y * f; r->z = a->z * f;
	return r;
}

__inline LPVECTOR3D Maths_Vector3DReflect(LPVECTOR3D r, LPVECTOR3D ray, LPVECTOR3D normal) {
	
	REAL dp;
	VECTOR3D a;
	
	dp = Maths_Vector3DDotProduct(normal, ray);
	Maths_Vector3DScale(&a, normal, 2.0f * dp);
	Maths_Vector3DSubtract(r, ray, &a);

	return r;
}

__inline LPVECTOR3D Maths_Vector3DNormalise(LPVECTOR3D r) {

	Maths_Vector3DScale(r, r, 1.0f/Maths_Vector3DLength(r));
	return r;
}

__inline LPVECTOR3D Maths_Vector3DRotate(LPVECTOR3D r, LPVECTOR3D vector, LPVECTOR3D axis, REAL angle) {

	MATRIX4D mat;
	REAL cosAngle = Maths_Cos(angle);
	REAL sinAngle = Maths_Sin(angle);

	Maths_Vector3DNormalise(axis);

    mat[0][0] = (axis->x * axis->x) * (1.0f - cosAngle) + cosAngle;
    mat[0][1] = (axis->x * axis->y) * (1.0f - cosAngle) - (axis->z * sinAngle);
    mat[0][2] = (axis->x * axis->z) * (1.0f - cosAngle) + (axis->y * sinAngle);

    mat[1][0] = (axis->y * axis->x) * (1.0f - cosAngle) + (axis->z * sinAngle);
    mat[1][1] = (axis->y * axis->y) * (1.0f - cosAngle) + cosAngle;
    mat[1][2] = (axis->y * axis->z) * (1.0f - cosAngle) - (axis->x * sinAngle);

    mat[2][0] = (axis->z * axis->x) * (1.0f - cosAngle) - (axis->y * sinAngle);
    mat[2][1] = (axis->z * axis->y) * (1.0f - cosAngle) + (axis->x * sinAngle);
    mat[2][2] = (axis->z * axis->z) * (1.0f - cosAngle) + cosAngle;

    mat[0][3] = mat[1][3] = mat[2][3] = 0.0f;
    mat[3][0] = mat[3][1] = mat[3][2] = 0.0f;
    mat[3][3] = 1.0f;

	Maths_MultiplyVectorByMatrix(r, vector, mat);

	return r;
}

/*
VOID D3DUtil_SetRotationMatrix( D3DMATRIX& mat, D3DVECTOR& vDir, FLOAT fRads )
{
    FLOAT     fCos = cosf( fRads );
    FLOAT     fSin = sinf( fRads );
    D3DVECTOR v    = Normalize( vDir );

    mat._11 = ( v.x * v.x ) * ( 1.0f - fCos ) + fCos;
    mat._12 = ( v.x * v.y ) * ( 1.0f - fCos ) - (v.z * fSin);
    mat._13 = ( v.x * v.z ) * ( 1.0f - fCos ) + (v.y * fSin);

    mat._21 = ( v.y * v.x ) * ( 1.0f - fCos ) + (v.z * fSin);
    mat._22 = ( v.y * v.y ) * ( 1.0f - fCos ) + fCos ;
    mat._23 = ( v.y * v.z ) * ( 1.0f - fCos ) - (v.x * fSin);

    mat._31 = ( v.z * v.x ) * ( 1.0f - fCos ) - (v.y * fSin);
    mat._32 = ( v.z * v.y ) * ( 1.0f - fCos ) + (v.x * fSin);
    mat._33 = ( v.z * v.z ) * ( 1.0f - fCos ) + fCos;

    mat._14 = mat._24 = mat._34 = 0.0f;
    mat._41 = mat._42 = mat._43 = 0.0f;
    mat._44 = 1.0f;
}
*/

/*
__inline LPVECTOR3D Maths_Vector3DRotate(LPVECTOR3D result, LPVECTOR3D vector, LPVECTOR3D axis, REAL angle) {

//	V' = cos(x) V + (1-cos(x))(A dot V)A + sin(x) A cross V
	VECTOR3D nAxis = *axis, d, e, f;
	REAL dp;

	Maths_Vector3DNormalise(&nAxis);

	Maths_Vector3DScale(&d, vector, Maths_Cos(angle));
	dp = Maths_Vector3DDotProduct(axis, vector);
	Maths_Vector3DScale(&e, &nAxis, dp * (1.0f - Maths_Cos(angle)));
	Maths_Vector3DCrossProduct(&f, &nAxis, vector);
	Maths_Vector3DScale(&f, &f, Maths_Sin(angle));
	Maths_Vector3DAdd(result, &d, &e);
	Maths_Vector3DAdd(result, result, &f);

	return result;
}
*/

__inline LPVECTOR3D Maths_Vector3DInterpolate(LPVECTOR3D result, LPVECTOR3D start, LPVECTOR3D end, REAL delta) {
	
	Maths_Vector3DSubtract(result, end, start);
	Maths_Vector3DScale(result, result, delta);
	Maths_Vector3DAdd(result, start, result);
	return result;
}

__inline VOID Maths_IdentityMatrix(MATRIX4D m) {

	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

__inline VOID Maths_CopyMatrix(MATRIX4D copy, MATRIX4D original) {

	memcpy(copy, original, sizeof(MATRIX4D));
}

__inline VOID Maths_MultiplyMatrix(MATRIX4D result, MATRIX4D a, MATRIX4D b) {

	ULONG i, j, k;
//	MATRIX4D m;

	Error_Fatal(result==a||result==b, "Cannot pass a or b as the result");

//	memset(m, 0, sizeof(D3DMATRIX));
	memset(result, 0, sizeof(D3DMATRIX));

	for (i=0; i<4; i++) {
		for (j=0; j<4; j++) {
			for (k=0; k<4; k++) {
				result[i][j] += a[i][k] * b[k][j];
//				result[i][j] += a[k][j] * b[i][k];
			}
		}
	}

//	Mem_Copy(result, m, sizeof(MATRIX4D));
}

__inline VOID Maths_MultiplyVectorByMatrix(LPVECTOR3D vDest, LPVECTOR3D vSrc, MATRIX4D mat) {

	REAL x = (vSrc->x * mat[0][0]) + (vSrc->y * mat[1][0]) + (vSrc->z * mat[2][0]) + mat[3][0];
	REAL y = (vSrc->x * mat[0][1]) + (vSrc->y * mat[1][1]) + (vSrc->z * mat[2][1]) + mat[3][1];
	REAL z = (vSrc->x * mat[0][2]) + (vSrc->y * mat[1][2]) + (vSrc->z * mat[2][2]) + mat[3][2];
	REAL w = (vSrc->x * mat[0][3]) + (vSrc->y * mat[1][3]) + (vSrc->z * mat[2][3]) + mat[3][3];

//	Error_Fatal(fabs(w) < M_EPSILON, "Invalid arguments");

	vDest->x = x / w;
	vDest->y = y / w;
	vDest->z = z / w;
}

__inline VOID Maths_MultiplyVector4DByMatrix(LPVECTOR4D vDest, LPVECTOR4D vSrc, MATRIX4D mat) {

	vDest->x = (vSrc->x * mat[0][0]) + (vSrc->y * mat[1][0]) + (vSrc->z * mat[2][0]) + (vSrc->w * mat[3][0]);
	vDest->y = (vSrc->x * mat[0][1]) + (vSrc->y * mat[1][1]) + (vSrc->z * mat[2][1]) + (vSrc->w * mat[3][1]);
	vDest->z = (vSrc->x * mat[0][2]) + (vSrc->y * mat[1][2]) + (vSrc->z * mat[2][2]) + (vSrc->w * mat[3][2]);
	vDest->w = (vSrc->x * mat[0][3]) + (vSrc->y * mat[1][3]) + (vSrc->z * mat[2][3]) + (vSrc->w * mat[3][3]);
}

__inline LPD3DMATRIX Maths_GetD3DMATRIX(MATRIX4D mat) {

	LPVOID cast = mat;
	return cast;
}

__inline VOID Maths_SetD3DVECTOR(LPD3DVECTOR d3dvec, LPVECTOR3D vec) {

	d3dvec->x = vec->x;
	d3dvec->y = vec->y;
	d3dvec->z = vec->z;
}

__inline VOID Maths_GetD3DVECTOR(LPVECTOR3D vec, LPD3DVECTOR d3dvec) {

	vec->x = d3dvec->x;
	vec->y = d3dvec->y;
	vec->z = d3dvec->z;
}

__inline VOID Maths_InvertMatrixQuick(MATRIX4D r, MATRIX4D mat) {

	REAL detInv;

	Error_Fatal(
		fabs(mat[3][3] - 1.0f) > M_EPSILON ||
		fabs(mat[0][3]) > M_EPSILON ||
		fabs(mat[1][3]) > M_EPSILON ||
		fabs(mat[2][3]) > M_EPSILON,
		"Last column of matrix must be [ 0 0 0 1 ] - Use Maths_InvertMatrixFull() instead");

	detInv = 1.0f / (
		mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) -
		mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) +
		mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]));

	r[0][0] =  detInv * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]);
	r[0][1] = -detInv * (mat[0][1] * mat[2][2] - mat[0][2] * mat[2][1]);
	r[0][2] =  detInv * (mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1]);
	r[0][3] = 0.0f;

	r[1][0] = -detInv * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]);
	r[1][1] =  detInv * (mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0]);
	r[1][2] = -detInv * (mat[0][0] * mat[1][2] - mat[0][2] * mat[1][0]);
	r[1][3] = 0.0f;

	r[2][0] =  detInv * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
	r[2][1] = -detInv * (mat[0][0] * mat[2][1] - mat[0][1] * mat[2][0]);
	r[2][2] =  detInv * (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]);
	r[2][3] = 0.0f;
	
	r[3][0] = -(mat[3][0] * r[0][0] + mat[3][1] * r[1][0] + mat[3][2] * r[2][0]);
	r[3][1] = -(mat[3][0] * r[0][1] + mat[3][1] * r[1][1] + mat[3][2] * r[2][1]);
	r[3][2] = -(mat[3][0] * r[0][2] + mat[3][1] * r[1][2] + mat[3][2] * r[2][2]);
	r[3][3] = 1.0f;

}

__inline VOID Maths_SetMatrixRotation(MATRIX4D mat, LPVECTOR3D vec, REAL angle) {

	REAL cosAngle = (REAL) cos(angle);
	REAL sinAngle = (REAL) sin(angle);
	VECTOR3D v = *vec;
	
	Maths_Vector3DNormalize(&v);

	mat[0][0] = (v.x * v.x) * (1.0f - cosAngle) + cosAngle;
	mat[0][1] = (v.x * v.y) * (1.0f - cosAngle) - (v.z * sinAngle);
	mat[0][2] = (v.x * v.z) * (1.0f - cosAngle) + (v.y * sinAngle);

	mat[1][0] = (v.y * v.x) * (1.0f - cosAngle) + (v.z * sinAngle);
	mat[1][1] = (v.y * v.y) * (1.0f - cosAngle) + cosAngle ;
	mat[1][2] = (v.y * v.z) * (1.0f - cosAngle) - (v.x * sinAngle);

	mat[2][0] = (v.z * v.x) * (1.0f - cosAngle) - (v.y * sinAngle);
	mat[2][1] = (v.z * v.y) * (1.0f - cosAngle) + (v.x * sinAngle);
	mat[2][2] = (v.z * v.z) * (1.0f - cosAngle) + cosAngle;

	mat[0][3] = mat[1][3] = mat[2][3] = 0.0f;
	mat[3][0] = mat[3][1] = mat[3][2] = 0.0f;
	mat[3][3] = 1.0f;
}

__inline VOID Maths_SetMatrixOrientation(MATRIX4D m, LPVECTOR3D vFrom, LPVECTOR3D vDir, LPVECTOR3D vWorldUp) {

	// Get the z basis vector, which points straight ahead. This is the
	// difference from the eyepoint to the lookat point.
	
	REAL fLength = Maths_Vector3DLength(vDir);
	VECTOR3D vView, vUp, vRight;
	REAL fDotProduct;
	MATRIX4D mat;

	Error_Fatal(fLength < 1e-6f, "Direction vector invalid");
	
	// Normalize the z basis vector
	Maths_Vector3DScale(&vView, vDir, 1.0f / fLength);
	
	// Get the dot product, and calculate the projection of the z basis
	// vector onto the up vector. The projection is the y basis vector.
	fDotProduct = Maths_Vector3DDotProduct(vWorldUp, &vView);
	
//	vUp = vWorldUp - fDotProduct * vView;
	Maths_Vector3DScale(&vUp, &vView, fDotProduct);
	Maths_Vector3DSubtract(&vUp, vWorldUp, &vUp);

	// If this vector has near-zero length because the input specified a
	// bogus up vector, let's try a default up vector
//	if( 1e-6f > ( fLength = Magnitude( vUp ) ) )
//	{
//		vUp = D3DVECTOR( 0.0f, 1.0f, 0.0f ) - vView.y * vView;
//		
//		// If we still have near-zero length, resort to a different axis.
//		if( 1e-6f > ( fLength = Magnitude( vUp ) ) )
//		{
//			vUp = D3DVECTOR( 0.0f, 0.0f, 1.0f ) - vView.z * vView;
//			
//			if( 1e-6f > ( fLength = Magnitude( vUp ) ) )
//				return E_INVALIDARG;
//		}
//	}

	fLength = Maths_Vector3DLength(&vUp);

	Error_Fatal(1e-6f > fLength, "Invalid up vector");
	
	// Normalize the y basis vector
	Maths_Vector3DScale(&vUp, &vUp, 1.0f / fLength);
	
	// The x basis vector is found simply with the cross product of the y
	// and z basis vectors
	Maths_Vector3DCrossProduct(&vRight, &vUp, &vView);
	
	// Start building the matrix. The first three rows contains the basis
	// vectors used to rotate the view to point at the lookat point
	Maths_IdentityMatrix(mat);
	mat[0][0] = vRight.x;    mat[0][1] = vUp.x;    mat[0][2] = vView.x;
	mat[1][0] = vRight.y;    mat[1][1] = vUp.y;    mat[1][2] = vView.y;
	mat[2][0] = vRight.z;    mat[2][1] = vUp.z;    mat[2][2] = vView.z;
	
	// Do the translation values (rotations are still about the eyepoint)
	mat[3][0] = -Maths_Vector3DDotProduct(vFrom, &vRight);
	mat[3][1] = -Maths_Vector3DDotProduct(vFrom, &vUp);
	mat[3][2] = -Maths_Vector3DDotProduct(vFrom, &vView);

	Maths_InvertMatrixQuick(m, mat);
}

__inline LPVECTOR3D Maths_PlaneNormal(LPVECTOR3D n, LPVECTOR3D p1, LPVECTOR3D p2, LPVECTOR3D p3){ 

	VECTOR3D v1, v2;

  	Maths_Vector3DSubtract(&v1, p2, p1);
	Maths_Vector3DSubtract(&v2, p3, p2);
	Maths_Vector3DCrossProduct(n, &v1, &v2);
	return Maths_Vector3DNormalize(n);
}

/*
REAL Maths_GetZRotation(LPVECTOR3D reference, LPVECTOR3D vector) {

	// Returns the angle of rotation of 'vector' around the z axis of the reference...

	REAL yRot, xRot, angle, length;
	VECTOR3D vec;

	length = Maths_Sqrt((reference->x * reference->x) + (reference->z * reference->z));
	if (0.0f != length) yRot = Maths_ASin(reference->x / length);
	else yRot = 0.0f;

	length = Maths_Sqrt((reference->y * reference->y) + (reference->z * reference->z));
	if (0.0f != length) xRot = Maths_ASin(reference->y / length);
	else xRot = 0.0f;

	if (reference->z < 0.0f) {
		xRot = M_PI - xRot;
		yRot = M_PI - yRot;
	}

	vec = *vector;
	length = Maths_Sqrt((vec.x * vec.x) + (vec.z * vec.z));
	if (0.0f != length) {
		angle = Maths_ASin(vec.x / length);
		if (vec.z < 0.0f) angle = M_PI - angle;
		angle += yRot;
		vec.x = Maths_Sin(angle) * length;
		vec.z = Maths_Cos(angle) * length;
	}

	length = Maths_Sqrt((vec.y * vec.y) + (vec.z * vec.z));
	if (0.0f != length) {
		angle = Maths_ASin(vec.z / length);
		if (vec.z < 0.0f) angle = M_PI - angle;
		angle += xRot;
		vec.z = Maths_Sin(angle) * length;
		vec.y = Maths_Cos(angle) * length;
	}

	length = Maths_Sqrt((vec.x * vec.x) + (vec.y * vec.y));
	if (0.0f != length) angle = Maths_ASin(vec.x / length);
	else angle = 0.0f;

	return angle;
}
*/

__inline VOID Maths_InvertMatrixFull(MATRIX4D r, MATRIX4D mat) {

	ULONG i, j;
	REAL det;
	
	Maths_MatrixAdjoint(mat, r);

	det = Maths_MatrixDeterminant4x4(mat);
	
	Error_Fatal(fabs(det) < M_EPSILON, "Non-singular matrix, no inverse!\n");

	for (i=0; i<4; i++) {
		for(j=0; j<4; j++) {
			r[i][j] = r[i][j] / det;
		}
	}
}

static VOID Maths_MatrixAdjoint(MATRIX4D in, MATRIX4D out) {
	
	REAL a1, a2, a3, a4, b1, b2, b3, b4;
	REAL c1, c2, c3, c4, d1, d2, d3, d4;
	
	a1 = in[0][0]; b1 = in[0][1]; 
	c1 = in[0][2]; d1 = in[0][3];
	
	a2 = in[1][0]; b2 = in[1][1]; 
	c2 = in[1][2]; d2 = in[1][3];
	
	a3 = in[2][0]; b3 = in[2][1];
	c3 = in[2][2]; d3 = in[2][3];
	
	a4 = in[3][0]; b4 = in[3][1]; 
	c4 = in[3][2]; d4 = in[3][3];
	
	out[0][0]  =   Maths_MatrixDeterminant3x3(b2, b3, b4, c2, c3, c4, d2, d3, d4);
	out[1][0]  = - Maths_MatrixDeterminant3x3(a2, a3, a4, c2, c3, c4, d2, d3, d4);
	out[2][0]  =   Maths_MatrixDeterminant3x3(a2, a3, a4, b2, b3, b4, d2, d3, d4);
	out[3][0]  = - Maths_MatrixDeterminant3x3(a2, a3, a4, b2, b3, b4, c2, c3, c4);
	
	out[0][1]  = - Maths_MatrixDeterminant3x3(b1, b3, b4, c1, c3, c4, d1, d3, d4);
	out[1][1]  =   Maths_MatrixDeterminant3x3(a1, a3, a4, c1, c3, c4, d1, d3, d4);
	out[2][1]  = - Maths_MatrixDeterminant3x3(a1, a3, a4, b1, b3, b4, d1, d3, d4);
	out[3][1]  =   Maths_MatrixDeterminant3x3(a1, a3, a4, b1, b3, b4, c1, c3, c4);
	
	out[0][2]  =   Maths_MatrixDeterminant3x3(b1, b2, b4, c1, c2, c4, d1, d2, d4);
	out[1][2]  = - Maths_MatrixDeterminant3x3(a1, a2, a4, c1, c2, c4, d1, d2, d4);
	out[2][2]  =   Maths_MatrixDeterminant3x3(a1, a2, a4, b1, b2, b4, d1, d2, d4);
	out[3][2]  = - Maths_MatrixDeterminant3x3(a1, a2, a4, b1, b2, b4, c1, c2, c4);
	
	out[0][3]  = - Maths_MatrixDeterminant3x3(b1, b2, b3, c1, c2, c3, d1, d2, d3);
	out[1][3]  =   Maths_MatrixDeterminant3x3(a1, a2, a3, c1, c2, c3, d1, d2, d3);
	out[2][3]  = - Maths_MatrixDeterminant3x3(a1, a2, a3, b1, b2, b3, d1, d2, d3);
	out[3][3]  =   Maths_MatrixDeterminant3x3(a1, a2, a3, b1, b2, b3, c1, c2, c3);
}

__inline static REAL Maths_MatrixDeterminant4x4(MATRIX4D m)  {
	
	REAL ans;
	REAL a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4;
	
	a1 = m[0][0]; b1 = m[0][1]; 
	c1 = m[0][2]; d1 = m[0][3];
	
	a2 = m[1][0]; b2 = m[1][1]; 
	c2 = m[1][2]; d2 = m[1][3];
	
	a3 = m[2][0]; b3 = m[2][1]; 
	c3 = m[2][2]; d3 = m[2][3];
	
	a4 = m[3][0]; b4 = m[3][1]; 
	c4 = m[3][2]; d4 = m[3][3];
	
	ans = a1 * Maths_MatrixDeterminant3x3(b2, b3, b4, c2, c3, c4, d2, d3, d4)
		- b1 * Maths_MatrixDeterminant3x3(a2, a3, a4, c2, c3, c4, d2, d3, d4)
		+ c1 * Maths_MatrixDeterminant3x3(a2, a3, a4, b2, b3, b4, d2, d3, d4)
		- d1 * Maths_MatrixDeterminant3x3(a2, a3, a4, b2, b3, b4, c2, c3, c4);
	
	return ans;
}

__inline static REAL Maths_MatrixDeterminant3x3(REAL a1, REAL a2, REAL a3, REAL b1, REAL b2, REAL b3, REAL c1, REAL c2, REAL c3) {
	
	REAL ans;
	
	ans = a1 * Maths_MatrixDeterminant2x2(b2, b3, c2, c3)
		- b1 * Maths_MatrixDeterminant2x2(a2, a3, c2, c3)
		+ c1 * Maths_MatrixDeterminant2x2(a2, a3, b2, b3);

	return ans;
}

__inline static REAL Maths_MatrixDeterminant2x2(REAL a, REAL b, REAL c, REAL d) {
	
	REAL ans;
	ans = a * d - b * c;
	return ans;
}

__inline REAL Maths_Power(REAL base, REAL exponent) {

	return (REAL) pow(base, exponent);
}

REAL Maths_PointLineDistance(LPVECTOR3D point, LPVECTOR3D start, LPVECTOR3D end) {

	VECTOR3D seVec, spVec, epVec;
	REAL hLength, dp, angle;

	// Is the point behind the start of the line..
	Maths_Vector3DSubtract(&seVec, end, start);
	Maths_Vector3DSubtract(&spVec, point, start);
	Maths_Vector3DNormalise(&seVec);
	hLength = Maths_Vector3DLength(&spVec);
	Maths_Vector3DScale(&spVec, &spVec, 1.0f / hLength);
	dp = Maths_Vector3DDotProduct(&seVec, &spVec);
	if (dp <= 0.0f) return Maths_Vector3DDistance(start, point);

	// Is it past the end of the line...
	Maths_Vector3DSubtract(&epVec, point, end);
	Maths_Vector3DNormalise(&epVec);
	if (Maths_Vector3DDotProduct(&seVec, &epVec) >= 0.0f) return Maths_Vector3DDistance(end, point);

	angle = Maths_ACos(dp);
	return Maths_Sin(angle) * hLength;
}

__inline BOOL Maths_RayPlaneIntersectionFast(LPVECTOR3D endPoint, LPVECTOR3D rayOrigin, LPVECTOR3D ray, LPVECTOR3D planePoint, LPVECTOR3D planeNormal){

	REAL dist;
	
	if (Maths_RayPlaneDistance(&dist, rayOrigin, ray, planePoint, planeNormal)){
		Maths_RayEndPoint(endPoint, rayOrigin, ray, dist);
		return TRUE;
	}
	return FALSE;
}

__inline BOOL Maths_RayPlaneIntersection(LPVECTOR3D endPoint, LPVECTOR3D rayOrigin, LPVECTOR3D ray, LPVECTOR3D planePoint, LPVECTOR3D planeNormal){

	VECTOR3D r = *ray, n = *planeNormal;

	Maths_Vector3DNormalise(&r);
	Maths_Vector3DNormalise(&n);

	return Maths_RayPlaneIntersectionFast(endPoint, rayOrigin, &r, planePoint, &n);
}

__inline BOOL Maths_RayPlaneDistance(LPREAL dist, LPVECTOR3D rayOrigin, LPVECTOR3D ray, LPVECTOR3D planePoint, LPVECTOR3D planeNormal){

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

__inline VOID Maths_RayEndPoint(LPVECTOR3D endPoint, LPVECTOR3D rayOrigin, LPVECTOR3D ray, REAL dist) {

	VECTOR3D temp;

	Maths_Vector3DScale(&temp, ray, dist);
	Maths_Vector3DAdd(endPoint, rayOrigin, &temp);
}

__inline BOOL Maths_PointInsidePoly(LPVECTOR2D point, LPVECTOR2D fromList, LPVECTOR2D toList, ULONG count){

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

__inline BOOL Maths_PointOnLine(LPVECTOR3D point, LPVECTOR3D start, LPVECTOR3D end) {

	REAL seDist = Maths_Vector3DDistance(start, end);
	REAL spDist = Maths_Vector3DDistance(start, point);
	REAL peDist = Maths_Vector3DDistance(point, end);

	return fabs(seDist - (spDist + peDist)) < M_EPSILON;
}
