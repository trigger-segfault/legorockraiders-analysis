
#include <d3drm.h>

#include "..\Inc\Standard.h"
#include "..\Inc\Errors.h"
#include "..\Inc\Main.h"
#include "..\Inc\Materials.h"

lpMaterial Material_Create(REAL emissiveRed, REAL emissiveGreen, REAL emissiveBlue, REAL specularRed, REAL specularGreen, REAL specularBlue, REAL power){

	LPDIRECT3DRMMATERIAL2 mat;

	if (D3DRM_OK == lpD3DRM()->lpVtbl->CreateMaterial(lpD3DRM(), power, &mat)){
		mat->lpVtbl->SetEmissive(mat, emissiveRed, emissiveGreen, emissiveBlue);
		mat->lpVtbl->SetSpecular(mat, specularRed, specularGreen, specularBlue);
		return (lpMaterial) mat;
	}

	return NULL;
}

VOID Material_Remove(lpMaterial material){

	LPDIRECT3DRMMATERIAL mat = (LPDIRECT3DRMMATERIAL) material;

	Error_Fatal(!mat, "Null passed as material to Material_Remove()");

	mat->lpVtbl->Release(mat);
}

VOID Material_SetEmissive(lpMaterial material, REAL emissiveRed, REAL emissiveGreen, REAL emissiveBlue){

	LPDIRECT3DRMMATERIAL mat = (LPDIRECT3DRMMATERIAL) material;

	Error_Fatal(!mat, "Null passed as material to Material_SetEmissive()");

	mat->lpVtbl->SetEmissive(mat, emissiveRed, emissiveGreen, emissiveBlue);
}

VOID Material_SetSpecular(lpMaterial material, REAL specularRed, REAL specularGreen, REAL specularBlue, REAL power){

	LPDIRECT3DRMMATERIAL mat = (LPDIRECT3DRMMATERIAL) material;

	Error_Fatal(!mat, "Null passed as material to Material_SetSpecular()");

	mat->lpVtbl->SetPower(mat, power);
	mat->lpVtbl->SetSpecular(mat, specularRed, specularGreen, specularBlue);
}
