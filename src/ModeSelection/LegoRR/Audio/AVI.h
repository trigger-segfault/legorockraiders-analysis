// AVI.h : 
//

#pragma once

#include "../Common.h"


namespace lego {
namespace avi {

#pragma region Globals

namespace globals {

    // <LegoRR.exe @0053499c>
    extern IDirectDraw4* g_AVIFile_IDirectDraw4;
} /* namespace globals */

#pragma endregion


#pragma region Functions

// <LegoRR.exe @0047ef40>
void __cdecl InitAVIFile(IDirectDraw4* ddraw);

#pragma endregion


} /* namespace avi */
} /* namespace lego */
