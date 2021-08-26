//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Material.c - [Materials Handling Code]
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

typedef struct Material_Dummy { ULONG dummy; } *lpMaterial;

lpMaterial	Material_Create(REAL emissiveRed, REAL emissiveGreen, REAL emissiveBlue, REAL specularRed, REAL specularGreen, REAL specularBlue, REAL power);
VOID			Material_Remove(lpMaterial material);
VOID			Material_SetEmissive(lpMaterial material, REAL emissiveRed, REAL emissiveGreen, REAL emissiveBlue);
VOID			Material_SetSpecular(lpMaterial material, REAL specularRed, REAL specularGreen, REAL specularBlue, REAL power);
