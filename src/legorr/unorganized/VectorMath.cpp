


/// RESULT: out_vector = a + (norm(b) * (dot_product((c - a), norm(d)) / dot_product(norm(b), norm(d)))
/// CONDITION: dot_product(norm(b), norm(d)) != 0.0
// <LegoRR.exe @00479ba0>
BOOL __cdecl lego::math::Vector3_Unk_FUN_00479ba0(Vector3F* out_vector, const Vector3F* a, const Vector3F* b, const Vector3F* c, const Vector3F* d)
{
	// Vector3_Scale(&norm_b, b, 1.0 / Vector3_Modulus(b));
	// Vector3_Scale(&norm_d, d, 1.0 / Vector3_Modulus(d));

	float mod1_b = 1.0 / std::sqrt((b->x * b->x) + (b->y * b->y) + (b->z * b->z));
	float mod1_d = 1.0 / std::sqrt((d->x * d->x) + (d->y * d->y) + (d->z * d->z));
	Vector3F norm_b = { b->x * mod1_b, b->y * mod1_b, b->z * mod1_b };
	Vector3F norm_d = { d->x * mod1_d, d->y * mod1_d, d->z * mod1_d };

	// Vector3F norm_b = *b, norm_d = *d;
	// Vector3_Normalize(&norm_b);
	// Vector3_Normalize(&norm_d);

	float scalar;
	if (Vector3_SubAC_MulD_Div_DotProductBD(&scalar, a, &norm_b, c, &norm_d)) {
		Vector3_AddScaled(out_vector, a, &norm_b, scalar);
		
		out_vector->x = a->x + norm_b->x * value4;
		out_vector->y = a->y + norm_b->y * value4;
		out_vector->z = a->z + norm_b->z * value4;
		return true;
	}
	return false;
	// norm_b.x = fVar7 * fVar2;
	// norm_b.y = fVar7 * fVar4;
	// norm_b.z = fVar7 * fVar5;
	// norm_d.x = (float)b * fVar1;
	// norm_d.y = (float)b * fVar3;
	// norm_d.z = (float)b * fVar6;
	// BVar8 = Vector3_SubAC_MulD_Div_DotProductBD((float *)&b, a, &norm_b, c, &norm_d);
	float dot_product = (norm_b->x * norm_d->x) + (norm_b->y * norm_d->y) + (norm_b->z * norm_d->z);
	if (dot_product != 0.0) {
	// v = ((c - a) * norm(d)) / dot_product(norm(b), norm(d))
		float value4 = ((c->x - a->x) * norm_d->x + (c->y - a->y) * norm_d->y + (c->z - a->z) * norm_d->z) / dot_product;
		// float value4 = ((c->x - a->x) * d->x + (c->y - a->y) * d->y + (c->z - a->z) * d->z) / dot_product;
		// out = (a + norm(b) * v)

		
		// v = a + ((c - a) * norm(d)) / dot_product(norm(b), norm(d))

		//out = (a + ((c - a) * (norm(b) * norm(d))) / dot_product(norm(b), norm(d)))

		
		out_vector->x = a->x + norm_b->x * value4;
		out_vector->y = a->y + norm_b->y * value4;
		out_vector->z = a->z + norm_b->z * value4;
		return true;
	}

	if (BVar8 != 0) {
		// Vector3_AddScaled(out_vector, a, &norm_b, (float)b);
		Vector3_AddScaled(out_vector, a, &norm_b, value3);
	
		out_vector->x = a->x + norm_b->x * value3;
		out_vector->y = a->y + norm_b->y * value3;
		out_vector->z = a->z + norm_b->z * value3;
		return true;
	}
	return false;
}


/// RESULT: sqrt(((a.x - b.x)*(a.x - b.x)) + ((a.y - b.y)*(a.y - b.y)))
// <LegoRR.exe @00401240>
float __cdecl lego::math::Vector2_Distance(const Point2F* a, const Point2F* b)
{
	return std::sqrt(((a->x - b->x)*(a->x - b->x)) + ((a->y - b->y)*(a->y - b->y)));
}

/// RESULT: ((dot_product((b - a), (b - a))*4.0) - (scalar*scalar)) < sqr(dot_product((b - a), (c * 2)))
// <LegoRR.exe @00479ed0>
BOOL __cdecl lego::math::Vector3_CompareUnk1(const Vector3F* a, float scalar, const Vector3F* b, const Vector3F* c)
{
	((dot_product((b - a), (b - a))*4.0) - (scalar*scalar)) < sqr(dot_product((b - a), (c * 2)))
	float diff_x = b->x - a->x;
	float diff_y = b->y - a->y;
	float diff_z = b->z - a->z;
	float value     = diff_x*(c->x + c->x) + diff_y*(c->y + c->y) + diff_z*(c->z + c->z);
	float length_sq = diff_x*diff_x        + diff_y*diff_y        + diff_z*diff_z;
	return (value*value) > ((length_sq*4.0) - (scalar*scalar));

	// float value     = (c->x + c->x)*diff_x + (c->y + c->y)*diff_y + (c->z + c->z)*diff_z;
	// float length_sq = diff_x*diff_x + diff_y*diff_y + diff_z*diff_z;
	// float value     = (c->x + c->x)*(b->x - a->x) + (c->y + c->y)*(b->y - a->y) + (c->z + c->z)*(b->z - a->z);
	// float length_sq = (b->x - a->x)*(b->x - a->x) + (b->y - a->y)*(b->y - a->y) + (b->z - a->z)*(b->z - a->z);

	value = (value*value) - ((length_sq * 4.0) - (scalar * scalar));
	if (value > 0.0)
		return TRUE;
	return FALSE;
}


/// RESULT: ref_vector = ref_vector * (1.0 / modulus(ref_vector))
/// RESULT: ref_vector = ref_vector * (1.0 / sqrt(dot_product(ref_vector, ref_vector)))


/// RESULT: out_vector = a + b
// <LegoRR.exe @00401470>
Vector3F* __cdecl lego::math::Vector3_Add(Vector3F* out_vector, const Vector3F* a, const Vector3F* b)
{
	out_vector->x = a->x + b->x;
	out_vector->y = a->y + b->y;
	out_vector->z = a->z + b->z;
	return out_vector;
}

/// RESULT: out_vector = a + (b * scalar)
// <LegoRR.exe @00479d70>
Vector3F* __cdecl lego::math::Vector3_AddScaled(Vector3F* out_vector, const Vector3F* a, const Vector3F* b, float scalar)
{
	out_vector->x = a->x + b->x * scalar;
	out_vector->y = a->y + b->y * scalar;
	out_vector->z = a->z + b->z * scalar;
}

/// RESULT: out_vector = { (a.y * b.z) - (a.z * b.y),
///                        (a.z * b.x) - (a.x * b.z),
///                        (a.x * b.y) - (a.y * b.x) }
// <LegoRR.exe @004013e0>
Vector3F* __cdecl lego::math::Vector3_CrossProduct(Vector3F* out_vector, const Vector3F* a, const Vector3F* b)
{
	out_vector->x = a->y * b->z - a->z * b->y;
	out_vector->y = a->z * b->x - a->x * b->z;
	out_vector->z = a->x * b->y - a->y * b->x;
}

/// RESULT: (a.x == b.x) && (a.y == b.y) && (a.z == b.z)
// <LegoRR.exe @0047c380>
BOOL __cdecl lego::math::Vector3_Equals(const Vector3F* a, const Vector3F* b)
{
	if ((a->x == b->x) && (a->y == b->y) && (a->z == b->z))
		return TRUE;
	return FALSE;
}

/// RESULT: ref_vector = ref_vector * (1.0 / modulus(ref_vector))
/// REFERENCE: modulus(ref_vector) -> sqrt(dot_product(ref_vector, ref_vector))
// <LegoRR.exe @00401690>
Vector3F* __cdecl lego::math::Vector3_Normalize(Vector3F* ref_vector)
{
	double value = 1.0 / std::sqrt((ref_vector->x * ref_vector->x) +
								   (ref_vector->y * ref_vector->y) +
						           (ref_vector->z * ref_vector->z));
	ref_vector->x *= value;
	ref_vector->y *= value;
	ref_vector->z *= value;
	return ref_vector;
}

/// RESULT: out_vector = norm({ rand(), rand(), rand() })
// <LegoRR.exe @004797c0>
Vector3F* __cdecl lego::math::Vector3_Random(Vector3F* out_vector)
{
  	return (Vector3F*)D3DRMVectorRandom((D3DVECTOR*)out_vector);
}

/// RESULT: out_vector = random_vector() * { x, y, z }
/// CONDITION: out_vector != nullptr
// <LegoRR.exe @0040fbf0>
void __cdecl lego::math::Vector3_RandomMultiply(Vector3F* out_vector, float x, float y, float z)
{
	if (out_vector != nullptr) {
		Vector3_Random(out_vector);
		out_vector->x = x * out_vector->x;
		out_vector->y = y * out_vector->y;
		out_vector->z = z * out_vector->z;
	}
}

/// RESULT: out_vector = ::D3DRMVectorRotate(out_vector, v, axis, theta)
// <LegoRR.exe @004797d0>
Vector3F* __cdecl lego::math::Vector3_Rotate(Vector3F* out_vector, const Vector3F* v, const Vector3F* axis, float theta)
{
	return (Vector3F*)D3DRMVectorRotate((D3DVECTOR*)out_vector, v, axis, theta);
}

/// RESULT: out_vector = a * scalar
// <LegoRR.exe @00401660>
Vector3F* __cdecl lego::math::Vector3_Scale(Vector3F* out_vector, const Vector3F* a, float scalar)
{
	out_vector->x = a->x * scalar;
	out_vector->y = a->y * scalar;
	out_vector->z = a->z * scalar;
	return out_vector;
}

/// RESULT: out_value = dot_product((c - a), d) / dot_product(b, d)
/// CONDITION: dot_product(b, d) != 0.0
// <LegoRR.exe @00479cf0>
BOOL __cdecl lego::math::Vector3_SubAC_MulD_Div_DotProductBD(float* out_value, const Vector3F* a, const Vector3F* b, const Vector3F* c, const Vector3F* d)
{
										/* Vector3_DotProduct(b, d) */
	float dot_product = b->x * d->x + b->y * d->y + b->z * d->z;
	if (dot_product != 0.0) {
										/* Vector3_DotProduct((Vector3_Subtract(c, a), d) / Vector3_DotProduct(b, d) */
		*out_value = ((c->x - a->x) * d->x + (c->y - a->y) * d->y + (c->z - a->z) * d->z) / dot_product;
		return true;
	}
	return false;
}

/// RESULT: out_vector = a - b
// <LegoRR.exe @00401630>
Vector3F* __cdecl lego::math::Vector3_Subtract(Vector3F* out_vector, const Vector3F* a, const Vector3F* b)
{
	out_vector->x = a->x - b->x;
	out_vector->y = a->y - b->y;
	out_vector->z = a->z - b->z;
	return out_vector;
}


// ref_vector = ref_vector * (1.0 / sqrt(dot_product(ref_vector, ref_vector)))