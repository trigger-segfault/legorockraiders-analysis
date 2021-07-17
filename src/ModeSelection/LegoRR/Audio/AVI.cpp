// AVI.cpp : 
//

#include "AVI.h"


#pragma region Globals
namespace lego {
namespace avi {
namespace globals {
    // <LegoRR.exe @0053499c>
    IDirectDraw4* g_AVIFile_IDirectDraw4;

} /* namespace globals */
} /* namespace avi */
} /* namespace lego */
#pragma endregion


using namespace lego::avi;


#pragma region Functions

// <LegoRR.exe @0047ef40>
void __cdecl lego::avi::InitAVIFile(IDirectDraw4* ddraw)
{
    globals::g_AVIFile_IDirectDraw4 = ddraw;

    AVIFileInit();
}

#pragma endregion
