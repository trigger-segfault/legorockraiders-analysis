#pragma once

#include "../framework.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

typedef struct Material_Dummy { unsigned long dummy; } *lpMaterial;
static_assert(sizeof(Material_Dummy) == 0x4, "");

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @00489780>
Material_Dummy* Material_Create(float emissiveRed, float emissiveGreen, float emissiveBlue,
								float specularRed, float specularGreen, float specularBlue, float power);

#pragma endregion

}
