//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Materials File For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

// Include all Header Files

//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
#include	"libgods.h"
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ


lpMaterial Material_Create(REAL emissiveRed, REAL emissiveGreen, REAL emissiveBlue, REAL specularRed, REAL specularGreen, REAL specularBlue, REAL power)
{
//	LPDIRECT3DRMMATERIAL mat;

//	if (Material_CreateMaterial(power, &mat))
//		{
//		mat->lpVtbl->SetEmissive(mat, emissiveRed, emissiveGreen, emissiveBlue);
//		mat->lpVtbl->SetSpecular(mat, specularRed, specularGreen, specularBlue);
//		return (lpMaterial) mat;
//	}

//	return NULL;
}

VOID Material_Remove(lpMaterial material)
{

//	LPDIRECT3DRMMATERIAL mat = (LPDIRECT3DRMMATERIAL) material;

//	mat->lpVtbl->Release(mat);
}

VOID Material_SetEmissive(lpMaterial material, REAL emissiveRed, REAL emissiveGreen, REAL emissiveBlue)
{

//	LPDIRECT3DRMMATERIAL mat = (LPDIRECT3DRMMATERIAL) material;

//	mat->lpVtbl->SetEmissive(mat, emissiveRed, emissiveGreen, emissiveBlue);
}

VOID Material_SetSpecular(lpMaterial material, REAL specularRed, REAL specularGreen, REAL specularBlue, REAL power)
{

//	LPDIRECT3DRMMATERIAL mat = (LPDIRECT3DRMMATERIAL) material;

//	mat->lpVtbl->SetPower(mat, power);
//	mat->lpVtbl->SetSpecular(mat, specularRed, specularGreen, specularBlue);
}
