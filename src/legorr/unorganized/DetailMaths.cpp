
    local_30[0][0] = 3; { 3, 0, 2 },
    local_30[0][1] = 0;
    local_30[0][2] = 2;

    local_30[1][0] = 0; { 0, 1, 3 },
    local_30[1][1] = 1;
    local_30[1][2] = 3;

    local_30[2][0] = 1; { 1, 2, 0 },
    local_30[2][1] = 2;
    local_30[2][2] = 0;

    local_30[3][0] = 2; { 2, 3, 1 },
    local_30[3][1] = 3;
    local_30[3][2] = 1;


// Detail_Matrix_FUN_0040bc90
	  out_m->m[3] = 0.0;
  out_m->m[2] = 0.0;
  out_m->m[1][3] = 0.0;
  out_m->m[1][2] = 0.0;
  out_m->m[1][0] = 0.0;
  out_m->m[2][3] = 0.0;
  out_m->m[2][1] = 0.0;
  out_m->m[2][0] = 0.0;
  out_m->m[3][2] = 0.0;
  out_m->m[3][1] = 0.0;
  out_m->m[3][0] = 0.0;
  out_m->m[3][3] = 1.0;
  out_m->m[2][2] = 1.0;
  out_m->m[0] = xUp / blockWidth;
  out_m->m[1][1] = yDir / blockHeight;
  out_m->m[1] = (yUp / xUp) * (xUp / blockWidth);

const float val1 = (xUp / blockWidth);
//const float val2 = ((yUp / xUp) * (xUp / blockWidth));
const float val2 = (yUp / blockWidth); // simplified
const float val3 = (yDir / blockHeight);
const Matrix4F m = {{
    { val1, val2, 0.0f, 0.0f },
    { 0.0f, val3, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f },
}};


out_m->m[0][0] = xUp / blockWidth;
out_m->m[0][1] = (yUp / xUp) * (xUp / blockWidth);
out_m->m[0][2] = 0.0;
out_m->m[0][3] = 0.0;

out_m->m[1][0] = 0.0;
out_m->m[1][1] = yDir / blockHeight;
out_m->m[1][2] = 0.0;
out_m->m[1][3] = 0.0;

out_m->m[2][0] = 0.0;
out_m->m[2][1] = 0.0;
out_m->m[2][2] = 1.0;
out_m->m[2][3] = 0.0;

out_m->m[3][0] = 0.0;
out_m->m[3][1] = 0.0;
out_m->m[3][2] = 0.0;
out_m->m[3][3] = 1.0;


//Detail_Sub2_FUN_0040bac0
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  Vector3F xform_dir;
  Vector3F xform_up;
  Matrix4F matrix;
  
  fVar1 = dir->x - position->x;
  xform_dir.y = dir->y - position->y;
  xform_dir.z = dir->z - position->z;
  fVar4 = up->x - dir->x;
  fVar2 = up->y - dir->y;
  fVar3 = up->z - dir->z;
  xform_up.x = fVar3 * xform_dir.y - fVar2 * xform_dir.z;
  xform_up.y = fVar4 * xform_dir.z - fVar3 * fVar1;
  xform_up.z = fVar2 * fVar1 - fVar4 * xform_dir.y;
  fVar3 = 1.0f / std::sqrt(xform_dir.z * xform_dir.z + xform_dir.y * xform_dir.y + fVar1 * fVar1);
  fVar2 = 1.0f / std::sqrt(xform_up.z * xform_up.z + xform_up.y * xform_up.y + xform_up.x * xform_up.x);
  Container_SetOrientation(cont, NULL, -(fVar2 * xform_up.x), -(fVar2 * xform_up.y), -(fVar2 * xform_up.z),
                                        (fVar3 * fVar1),       (fVar3 * xform_dir.y), (fVar3 * xform_dir.z));
  Container_SetPosition(cont, NULL, position->x, position->y, position->z);
  Container_InverseTransform(cont, &xform_dir, dir);
  Container_InverseTransform(cont, &xform_up, up);
  Detail_Matrix_FUN_0040bc90(&matrix, blockSize, blockSize, xform_dir.y, xform_up.x, xform_up.y);
  Container_AddTransform(cont, D3DRMCOMBINE_BEFORE, &matrix);


float fVar1;
float fVar2;
float fVar3;
float fVar4;
Vector3F xform_dir;
Vector3F xform_up;
Matrix4F matrix;

fVar1 = dir->x - position->x;
xform_dir.y = dir->y - position->y;
xform_dir.z = dir->z - position->z;
fVar4 = up->x - dir->x;
fVar2 = up->y - dir->y;
fVar3 = up->z - dir->z;
xform_up.x = fVar3 * xform_dir.y - fVar2 * xform_dir.z;
xform_up.y = fVar4 * xform_dir.z - fVar3 * fVar1;
xform_up.z = fVar2 * fVar1 - fVar4 * xform_dir.y;

Vector3F dirPos, upDir;
Maths_Vector3DSubtract(&dirPos, dir, position);
Maths_Vector3DSubtract(&upDir, up, dir);
Vector3F crossProd;
Maths_Vector3DCrossProduct(&xform_up, &upDir, &dirPos);

xform_dir = dirPos;
xform_up = crossProd;

Vector3D tempUp;
Maths_Vector3DSubtract(&xform_dir, dir, position);
Maths_Vector3DSubtract(&tempUp, up, dir);

Maths_Vector3DCrossProduct(&xform_up, &tempUp, &xform_dir);

//float dirLength = Maths_Vector3DLength(&xform_dir);
//float upLength = Maths_Vector3DLength(&xform_up);

Vector3F normDir = xform_dir, normUp = xform_up;
//Vector3F normDir, normUp;
Maths_Vector3DNormalize(xform_dir);
Maths_Vector3DNormalize(xform_up);

Container_SetOrientation(cont, NULL, -normUp.x, -normUp.y, -normUp.z,
									 normDir.x, normDir.y, normDir.z);

Container_SetPosition(cont, NULL, position->x, position->y, position->z);

Container_InverseTransform(cont, &xform_dir, dir);
Container_InverseTransform(cont, &xform_up, up);

Detail_Matrix_FUN_0040bc90(&matrix, blockSize, blockSize, xform_dir.y, xform_up.x, xform_up.y);

Container_AddTransform(cont, D3DRMCOMBINE_BEFORE, &matrix);


fVar3 = 1.0f / std::sqrt(xform_dir.z * xform_dir.z + xform_dir.y * xform_dir.y + fVar1 * fVar1);
fVar2 = 1.0f / std::sqrt(xform_up.z * xform_up.z + xform_up.y * xform_up.y + xform_up.x * xform_up.x);

Container_SetOrientation(cont, NULL, -(fVar2 * xform_up.x), -(fVar2 * xform_up.y), -(fVar2 * xform_up.z),
									  (fVar3 * fVar1),       (fVar3 * xform_dir.y), (fVar3 * xform_dir.z));

Container_SetPosition(cont, NULL, position->x, position->y, position->z);

Container_InverseTransform(cont, &xform_dir, dir);
Container_InverseTransform(cont, &xform_up, up);
Detail_Matrix_FUN_0040bc90(&matrix, blockSize, blockSize, xform_dir.y, xform_up.x, xform_up.y);
Container_AddTransform(cont, D3DRMCOMBINE_BEFORE, &matrix);




void __cdecl Detail_Sub2_FUN_0040bac0(Container *cont, float blockSize, Vector3F *p1, Vector3F *p2, Vector3F *p3)
{
  Vector3F xformUp;
  Vector3F xformDir;
  Matrix4F matrix;
  float lenUp;
  float lenDir;
  float tempDir_x;
  float tempDir_y;
  float tempDir_z;
  float xformUp_x;
  
  float xformUp_x = p2->x - p1->x;
  xformUp.y = p2->y - p1->y;
  xformUp.z = p2->z - p1->z;
  float tempDir_x = p3->x - p2->x;
  float tempDir_y = p3->y - p2->y;
  float tempDir_z = p3->z - p2->z;
  xformDir.x = tempDir_z * xformUp.y - tempDir_y * xformUp.z;
  xformDir.y = tempDir_x * xformUp.z - tempDir_z * xformUp_x;
  xformDir.z = tempDir_y * xformUp_x - tempDir_x * xformUp.y;
  float lenUp  = 1.0f / std::sqrt(xformUp.z  * xformUp.z  + xformUp.y  * xformUp.y  + xformUp_x  * xformUp_x);
  float lenDir = 1.0f / std::sqrt(xformDir.z * xformDir.z + xformDir.y * xformDir.y + xformDir.x * xformDir.x);
  Gods98::Container_SetOrientation(cont, NULL, 
                                -(lenDir * xformDir.x), -(lenDir * xformDir.y), -(lenDir * xformDir.z),
                                 (lenUp  * xformUp_x),   (lenUp  * xformUp.y),   (lenUp * xformUp.z));
  Gods98::Container_SetPosition(cont, NULL, p1->x, p1->y, p1->z);

  Vector3F invP2, invP3;
  Gods98::Container_InverseTransform(cont, &invP2, p2);
  Gods98::Container_InverseTransform(cont, &invP3, p3);
  Detail_Matrix_FUN_0040bc90(&matrix, blockSize, blockSize, invP2.y, invP3.x, invP3.y);
  Gods98::Container_AddTransform(cont, D3DRMCOMBINE_BEFORE, &matrix);
  return;
}


void __cdecl Detail_Sub2_FUN_0040bac0(Container *cont, float blockSize, Vector3F *p1, Vector3F *p2, Vector3F *p3)
{
  Vector3F xformUp;
  Vector3F xformDir;
  Matrix4F matrix;
  float lenUp;
  float lenDir;
  float tempDir_x;
  float tempDir_y;
  float tempDir_z;
  float xformUp_x;
  
  float xformUp_x = p2->x - p1->x;
  xformUp.y = p2->y - p1->y;
  xformUp.z = p2->z - p1->z;
  float tempDir_x = p3->x - p2->x;
  float tempDir_y = p3->y - p2->y;
  float tempDir_z = p3->z - p2->z;
  xformDir.x = tempDir_z * xformUp.y - tempDir_y * xformUp.z;
  xformDir.y = tempDir_x * xformUp.z - tempDir_z * xformUp_x;
  xformDir.z = tempDir_y * xformUp_x - tempDir_x * xformUp.y;
  float lenUp  = 1.0f / std::sqrt(xformUp.z  * xformUp.z  + xformUp.y  * xformUp.y  + xformUp_x  * xformUp_x);
  float lenDir = 1.0f / std::sqrt(xformDir.z * xformDir.z + xformDir.y * xformDir.y + xformDir.x * xformDir.x);
  Gods98::Container_SetOrientation(cont, NULL, 
                                   -(lenDir * xformDir.x), -(lenDir * xformDir.y), -(lenDir * xformDir.z),
                                    (lenUp  * xformUp_x),   (lenUp  * xformUp.y),   (lenUp * xformUp.z));
  Gods98::Container_SetPosition(cont, NULL, p1->x, p1->y, p1->z);

  Vector3F invxP2, invxP3;
  Gods98::Container_InverseTransform(cont, &invxP2, p2);
  Gods98::Container_InverseTransform(cont, &invxP3, p3);
  Detail_Matrix_FUN_0040bc90(&matrix, blockSize, blockSize, invxP2.y, invxP3.x, invxP3.y);
  Gods98::Container_AddTransform(cont, D3DRMCOMBINE_BEFORE, &matrix);
  return;
}

void __cdecl Detail_Sub2_FUN_0040bac0(Container *cont, float blockSize, Vector3F *p1, Vector3F *p2, Vector3F *p3)
{

	Vector3D newUp, newDir, tempDir;
	Maths_Vector3DSubtract(&newUp, p2, p1);
	Maths_Vector3DSubtract(&tempDir, p3, p2);

	Maths_Vector3DCrossProduct(&newDir, &tempDir, &newUp);
	Maths_Vector3DNormalize(newUp);
	Maths_Vector3DNormalize(newDir);

	
	Vector3D newUp, newDir, tempDir;
	Maths_Vector3DSubtract(&newUp, p2, p1);
	Maths_Vector3DCrossProduct(&newDir, Maths_Vector3DSubtract(&tempDir, p3, p2), &newUp);

	Maths_Vector3DNormalize(newUp);
	Maths_Vector3DNormalize(newDir);

	Gods98::Container_SetOrientation(cont, nullptr, -newDir.x, -newDir.y, -newDir.z,
													 newUp.x,   newUp.y,   newUp.z);

	Gods98::Container_SetPosition(cont, nullptr, p1->x, p1->y, p1->z);

	Vector3F invxP2, invxP3;
	Gods98::Container_InverseTransform(cont, &invxP2, p2);
	Gods98::Container_InverseTransform(cont, &invxP3, p3);
	
	Matrix4F matrix;
	Detail_Matrix_FUN_0040bc90(&matrix, blockSize, blockSize, invxP2.y, invxP3.x, invxP3.y);
	Gods98::Container_AddTransform(cont, Container_Combine::Before, &matrix);
	



	Gods98::Container_SetOrientation(cont, nullptr, 
									 -(lenDir * newDir.x), -(lenDir * newDir.y), -(lenDir * newDir.z),
									  (lenUp  * newUp.x),   (lenUp  * newUp.y),   (lenUp * newUp.z));

	Gods98::Container_SetPosition(cont, nullptr, p1->x, p1->y, p1->z);
}


void __cdecl Detail_Sub2_FUN_0040bac0(Container *cont, float blockSize, Vector3F *p1, Vector3F *p2, Vector3F *p3)
{
	Vector3D newUp, newDir, tempDir;
	Maths_Vector3DSubtract(&newUp, p2, p1);
	Maths_Vector3DCrossProduct(&newDir, Maths_Vector3DSubtract(&tempDir, p3, p2), &newUp);

	Maths_Vector3DNormalize(newUp);
	Maths_Vector3DNormalize(newDir);

	Gods98::Container_SetOrientation(cont, nullptr, -newDir.x, -newDir.y, -newDir.z,
													 newUp.x,   newUp.y,   newUp.z);

	Gods98::Container_SetPosition(cont, nullptr, p1->x, p1->y, p1->z);


	Vector3F invxP2, invxP3;
	Gods98::Container_InverseTransform(cont, &invxP2, p2);
	Gods98::Container_InverseTransform(cont, &invxP3, p3);
	
	Matrix4F matrix;
	Detail_Matrix_FUN_0040bc90(&matrix, blockSize, blockSize, invxP2.y, invxP3.x, invxP3.y);

	Gods98::Container_AddTransform(cont, Container_Combine::Before, &matrix);
}
