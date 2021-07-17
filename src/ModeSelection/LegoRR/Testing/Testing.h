// Testing.h : Declares game testing and dummy functions.
//

#pragma once

#include "../Common.h"


namespace testing {

#pragma region Functions

BOOL __cdecl MyGameInitFunction(void);

BOOL __cdecl MyGameUpdateFunction(float ellapsed);

BOOL __cdecl MyGameUpdateFunctionOld(float ellapsed);

void __cdecl MyGameCleanupFunction(void);

#pragma endregion


} /* namespace testing */
