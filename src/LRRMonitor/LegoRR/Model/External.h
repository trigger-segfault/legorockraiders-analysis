//#pragma once
//#include "Model.h"

#ifdef DEFINE_EXTERNALS
//#define defExtern(symbol, cast, address) symbol cast address
//#define defExtern(symbol, cast, address) symbol cast address
//#define defGlob(symbol, cast, address) symbol cast address
//#define defFunc(symbol, cast, address) symbol cast address

#define defVar(ADDR, TYPE, NAME, ...) \
	/*volatile*/ TYPE (& NAME) __VA_ARGS__ = *(std::remove_reference_t<decltype(NAME)>*)ADDR
#define defFun(ADDR, RETURN, CONV, NAME, ...) \
	RETURN (CONV* NAME)( __VA_ARGS__ ) = *(decltype(NAME))ADDR
//#define defCdecl(ADDR, RETURN, NAME, ...) RETURN (__cdecl* NAME) __VA_ARGS__ = *(decltype(NAME))ADDR;
#else
#pragma once
//#define defExtern(symbol, cast, address) extern symbol
//#define defExtern(symbol, cast, address) extern symbol
//#define defExtern(symbol, cast, address) extern symbol
//#define defGlob(symbol, cast, address) extern symbol
//#define defFunc(symbol, cast, address) extern symbol

//#define defVar(ADDR, TYPE, NAME, ...) /* ADDR */ extern volatile TYPE (& NAME) __VA_ARGS__ 
//#define defFun(ADDR, RETURN, CONV, NAME, ...) /* ADDR */ extern RETURN (CONV* NAME)( __VA_ARGS__ )

#define defVar(ADDR, TYPE, NAME, ...) /* <LegoRR.exe @ ##ADDR## > */ \
	extern /*volatile*/ TYPE (& NAME) __VA_ARGS__


#define defFun(ADDR, RETURN, CONV, NAME, ...)  /* <LegoRR.exe @ ##ADDR## > */ \
	extern RETURN (CONV* NAME)( __VA_ARGS__ )


#define idefVar(ADDR, TYPE, NAME, ...) /* <LegoRR.exe @ ##ADDR## > */ \
	extern TYPE (& NAME) __VA_ARGS__


#define idefFun(ADDR, RETURN, CONV, NAME, ...)  /* <LegoRR.exe @ ##ADDR## > */ \
	RETURN (CONV* NAME)( __VA_ARGS__ )

//#define defCdecl(ADDR, RETURN, NAME, ...) extern RETURN (__cdecl* NAME) __VA_ARGS__ ;
#endif


//#define defGlob(symbol, cast, address) symbol cast address
//#define defFunc(symbol, cast, address) symbol cast address

#include "Model.h"
#include "../Common.h"
#include <type_traits>

using namespace lego;
//using namespace lego::game;




//#pragma warning disable format
//namespace lego {
namespace external
{//<---
#pragma region Externals

defFun(0x00452880, LiveObject*, __cdecl, Message_GetPrimarySelectedUnit, void);
defFun(0x004528b0, unsigned int, __cdecl, Message_GetNumSelectedUnits, void);

defFun(0x0044a5d0, void, __cdecl, LiveObject_FPMove, LiveObject* liveObj, int forward, int strafe, float rotate);


defFun(0x004896b0, void, __cdecl, InitSharedFileBuffers, void);
defFun(0x0048b620, BOOL, __cdecl, Registry_QueryValueOnLM, const char* key, const char* valueName, RegistryType valueType, void* out_buffer, unsigned int bufferSize);


defFun(0x0047f050, BOOL, __cdecl, InitDirectInput, void);
defFun(0x0047c430, void, __cdecl, InitDirectDraw, HWND hWnd);
defFun(0x00488e10, void, __cdecl, InitSoundSystem, BOOL nosound);
defFun(0x0049d2f0, BOOL, __cdecl, ChooseScreenMode, BOOL showDialog, BOOL isDebug, BOOL isBest, BOOL isWindow, const char* errorMessage);
defFun(0x0047ef40, void, __cdecl, InitAVIFile, IDirectDraw4* ddraw4);
defFun(0x0047f1b0, void, __cdecl, UpdateKeyboardState, void);
defFun(0x0047f2d0, void, __cdecl, UpdateMousePosition, void);
defFun(0x0047cb90, void, __cdecl, DDraw_Render, void);
defFun(0x0047cfb0, void, __cdecl, CleanupDirectDraw, void);
defFun(0x0047f290, void, __cdecl, CleanupDirectInput, void);
defFun(0x00484f50, void, __cdecl, logf_removed, const char* message, ...);
defFun(0x00486140, void, __cdecl, Draw_SurfaceLockRect, const Rect2F* surfaceRect);
defFun(0x0041f950, BOOL, __cdecl, InitGameFunctions, const char* gameName);


#pragma region StringUtils.c

defFun(0x00477700, int, __cdecl, stringSplit, char* input, char** out_parts, const char* delimiter);
// Similar functionality to stringSplit, but with minor differences.
// Used by LightWave for parsing script file tokens.
defFun(0x00477770, int, __cdecl, whitespaceSplit, char* input, char** out_parts);
// Whether this is the real C runtime library ::_strdup or not is unclear, so here it is anyway.
defFun(0x00477810, char*, __cdecl, _strdup, const char* strSource);
defFun(0x00477850, char*, __cdecl, formatText, const char* text, ...);
/// NOTE: accepts const, and returns non-const. This is simply to avoid overloading the function pointer
defFun(0x004778d0, char*, __cdecl, strstri, const char* str, const char* strSearch);
//defFun(0x004778d0, char*, __cdecl, strstri, char* str, const char* strSearch);
//defFun(0x004778d0, const char*, __cdecl, strstri, const char* str, const char* strSearch);

defFun(0x00477930, unsigned int, __cdecl, hash_string, const char* str, BOOL bIgnoreBlanks, BOOL bIgnoreCase);
defFun(0x004779d0, BOOL3, __cdecl, parseBoolLiteral, const char* str);

#pragma endregion


#pragma region Main.c

// Name has been changed from "WinMain" to avoid any compiler headaches.
defFun(0x00477a60, int, APIENTRY, LegoRR_WinMain, _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow);
// Sets the "-nm" commandline option only if the "-ftm" option is not set.
//  (The "-ftm" option is intended to be set when running on Voodoo2-based graphics cards, as is shown by CLGen.exe)
// This is called when Lego.cfg/Lego*::Main::TextureUsage(units in pixels) is valid and <= available video memory.
defFun(0x00477e90, void, __cdecl, Main_DisableTextureManagement_NonVoodoo2, void);
defFun(0x00477eb0, void, __cdecl, ParseCmdlineFlags, const char* fullCmdLine, BOOL* out_nosound, BOOL* out_insistOnCD);
defFun(0x004781f0, void, __cdecl, Main_UpdateAndRender__004781f0, BOOL doFillSurface);
defFun(0x00478230, FeatureFlags, __cdecl, GetFeatureFlags, void);
defFun(0x00478240, int, __cdecl, Setup_GetDeviceBitsPerPixel, void);
defFun(0x00478260, void, __cdecl, UpdateDirect3DRM, void);
defFun(0x00478290, BOOL, __cdecl, Main_SetGameFunctions, GameFunctions* gameFuncs);
// WINMM.DLL::timeGetTime
defFun(0x004782c0, DWORD, __stdcall, timeGetTime, void);
defFun(0x004782d0, BOOL, __cdecl, Win_ShouldHandleMessage, MSG* msg);
defFun(0x00478300, void, __cdecl, HandleMessageQueue, void);
defFun(0x00478370, void, __cdecl, Win_ShowGameWindow, BOOL isFullScreen, int windowedX, int windowedY, int screenWidth, int screenHeight);
defFun(0x00478490, BOOL, __cdecl, Main_Direct3DRMCreate, const DeviceMode* device, IDirectDraw* ddraw1, IDirectDrawSurface4* ddSurface4, BOOL isFullScreen);
defFun(0x004785d0, void, __cdecl, Win_AdjustMainWindowedRect, LPRECT lpRect);
defFun(0x004785f0, void, __cdecl, Draw_SetDirectXGraphicsQuality, GraphicsQuality quality, BOOL dither, BOOL filter, BOOL mipmap, BOOL linearmipmap, BOOL blend, BOOL sort);

defFun(0x00478690, BOOL, __cdecl, Win_SetMainWindowTitle, LPCSTR title);
defFun(0x004786b0, BOOL, __cdecl, Win_CreateMainWindow, HINSTANCE hInstance);
defFun(0x00478780, LRESULT, __cdecl, WindowProc_FullScreen, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
defFun(0x00478980, LRESULT, __cdecl, WindowProc_Windowed,	HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
defFun(0x00478b40, LRESULT, CALLBACK, Win_WindowProc,		HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
defFun(0x00478b90, void, __cdecl, Draw_SetRenderState,		unsigned int renderStateType, unsigned int renderStateValue);
defFun(0x00478c00, void, __cdecl, Draw_CleanupRenderStates, void);
defFun(0x00478c40, BOOL, __cdecl, SFX_UNKCallsMixer__00478c40, float param_1, float param_2);
defFun(0x00478c60, BOOL, __cdecl, FUN_00478c60, float* param_1, float* param_2);
defFun(0x00478c80, BOOL, __cdecl, SFX_UnkMixer__00478c80, float* param_1, float* param_2, BOOL param_3);

#pragma endregion


#pragma region CFG.c

/// PUBLIC:
defFun(0x004790b0, void, __cdecl,			ReservedPool_CFGProperty___Init, void);
defFun(0x004790e0, void, __cdecl,			ReservedPool_CFGProperty___Cleanup, void);
defFun(0x00479120, CFGRoot*, __cdecl,		CFG_Open, const char* filename);
defFun(0x00479210, const char*, __cdecl,	CFG_JoinPath, const char* keyPath1, ...);
defFun(0x004792b0, const CFGProperty*, __cdecl,	CFG_GetChildren, const CFGProperty* prop, const char* keyPath);
defFun(0x004792e0, const CFGProperty*, __cdecl,	CFG_NextFlat, const CFGProperty* prop);
defFun(0x00479310, char*, __cdecl,			CFG_CopyString, const CFGProperty* prop, const char* keyPath);
defFun(0x00479370, const char*, __cdecl,	CFG_ReadString, const CFGProperty* prop, const char* keyPath);
defFun(0x00479390, BOOL3, __cdecl,			CFG_ReadBool, const CFGProperty* prop, const char* keyPath);
defFun(0x004793d0, float , __cdecl,			CFG_ReadRadians, const CFGProperty* prop, const char* keyPath);
defFun(0x00479430, float, __cdecl,			CFG_ReadRGBF, const CFGProperty* prop, const char* keyPath, float* out_r, float* out_g, float* out_b);
defFun(0x00479500, void, __cdecl,			CFG_Close, CFGRoot* root);
/// INTERNAL:
defFun(0x00479530, CFGProperty*, __cdecl,	ReservedPool_CFGProperty___Next, CFGProperty* previous);
defFun(0x00479580, void, __cdecl,			ReservedPool_CFGProperty___Release, CFGProperty* prop);
/// PUBLIC:
defFun(0x004795a0, const CFGProperty*, __cdecl,	CFG_GetProperty, CFGProperty* prop, const char* keyPath);
/// INTERNAL:
defFun(0x00479750, void, __cdecl,			ReservedPool_CFGProperty___Alloc, void);

#pragma endregion


#pragma region Math.c

/// PUBLIC:
/// RESULT: out_vector = norm({ rand(), rand(), rand() })
defFun(0x004797c0, Vector3F*, __cdecl, Vector3_Random, Vector3F* out_vector);
/// RESULT: out_vector = ::D3DRMVectorRotate(out_vector, v, axis, theta)
defFun(0x004797d0, Vector3F*, __cdecl, Vector3_Rotate, Vector3F* out_vector, const Vector3F* v, const Vector3F* axis, float theta);
/// RESULT: out_vector = norm(cross_product((c - b), (b - a)))
defFun(0x004797f0, Vector3F*, __cdecl, Vector3_Norm_CrossProduct_CSubB_BSubA, Vector3F* out_vector, const Vector3F* a, const Vector3F* b, const Vector3F* c);
defFun(0x004798f0, float10, __cdecl, FUN_004798f0, Vector3F* param_1, Vector3F* param_2, Vector3F* param_3, BOOL param_4);
defFun(0x00479b60, short, __cdecl, thunk_randomInt16, void);
defFun(0x00479b70, float, __cdecl, Game_ChooseRandomRange, float rangeMin, float rangeMax);
/// RESULT: out_vector = a + (norm(b) * (dot_product((c - a), norm(d)) / dot_product(norm(b), norm(d)))
/// CONDITION: dot_product(norm(b), norm(d)) != 0.0
defFun(0x00479ba0, BOOL, __cdecl, Vector3_Unk_FUN_00479ba0, Vector3F* out_vector, const Vector3F* a, const Vector3F* b, const Vector3F* c, const Vector3F* d);
/// RESULT: out_value = dot_product((c - a), d) / dot_product(b, d)
/// CONDITION: dot_product(b, d) != 0.0
defFun(0x00479cf0, BOOL, __cdecl, Vector3_SubAC_MulD_Div_DotProductBD, float* out_value, const Vector3F* a, const Vector3F* b, const Vector3F* c, const Vector3F* d);
/// RESULT: out_vector = a + (b * scalar)
defFun(0x00479d70, Vector3F*, __cdecl, Vector3_AddScaled, Vector3F* out_vector, const Vector3F* a, const Vector3F* b, float scalar);
/// RESULT: out_point = a + (b * dot_product((a - c), (perpendicular(d) / dot_product(perpendicular(b), d))))
/// CONDITION: dot_product(perpendicular(b), d) != 0.0
defFun(0x00479db0, Point2F*, __cdecl, Vector2_AAdd_BMulDotProduct_ASubC_PerpDDivDotProductBD, Point2F* out_point, const Point2F* a, const Point2F* b, const Point2F* c, const Point2F* d);

defFun(0x00479e40, BOOL, __cdecl, FUN_00479e40, const Point2F* param_1, const Point2F* param_2, const Point2F* param_3, int count);

defFun(0x00479ed0, BOOL, __cdecl, Vector3_CompareUnk1, const Vector3F* a, float scalar, const Vector3F* b, const Vector3F* c);
/// RESULT: out_matrix = { {
///                          l[0,0]*r[0,0] + l[0,1]*r[1,0] + l[0,2]*r[2,0] + l[0,3]*r[3,0],
///                          l[0,0]*r[0,1] + l[0,1]*r[1,1] + l[0,2]*r[2,1] + l[0,3]*r[3,1],
///                          l[0,0]*r[0,2] + l[0,1]*r[1,2] + l[0,2]*r[2,2] + l[0,3]*r[3,2],
///                          l[0,0]*r[0,3] + l[0,1]*r[1,3] + l[0,2]*r[2,3] + l[0,3]*r[3,3]
///                        },{
///                          l[1,0]*r[0,0] + l[1,1]*r[1,0] + l[1,2]*r[2,0] + l[1,3]*r[3,0],
///                          l[1,0]*r[0,1] + l[1,1]*r[1,1] + l[1,2]*r[2,1] + l[1,3]*r[3,1],
///                          l[1,0]*r[0,2] + l[1,1]*r[1,2] + l[1,2]*r[2,2] + l[1,3]*r[3,2],
///                          l[1,0]*r[0,3] + l[1,1]*r[1,3] + l[1,2]*r[2,3] + l[1,3]*r[3,3]
///                        },{
///                          l[2,0]*r[0,0] + l[2,1]*r[1,0] + l[2,2]*r[2,0] + l[2,3]*r[3,0],
///                          l[2,0]*r[0,1] + l[2,1]*r[1,1] + l[2,2]*r[2,1] + l[2,3]*r[3,1],
///                          l[2,0]*r[0,2] + l[2,1]*r[1,2] + l[2,2]*r[2,2] + l[2,3]*r[3,2],
///                          l[2,0]*r[0,3] + l[2,1]*r[1,3] + l[2,2]*r[2,3] + l[2,3]*r[3,3]
///                        },{
///                          l[3,0]*r[0,0] + l[3,1]*r[1,0] + l[3,2]*r[2,0] + l[3,3]*r[3,0],
///                          l[3,0]*r[0,1] + l[3,1]*r[1,1] + l[3,2]*r[2,1] + l[3,3]*r[3,1],
///                          l[3,0]*r[0,2] + l[3,1]*r[1,2] + l[3,2]*r[2,2] + l[3,3]*r[3,2],
///                          l[3,0]*r[0,3] + l[3,1]*r[1,3] + l[3,2]*r[2,3] + l[3,3]*r[3,3]
///                      } }
/// NOTE: right and left operands are ordered in reverse in the parameter list.
defFun(0x00479fa0, void, __cdecl, Matrix4_Multiply, Matrix4F out_matrix, const Matrix4F right, const Matrix4F left);

// <https://en.wikipedia.org/wiki/Rotation_matrix#In_three_dimensions>
// <https://github.com/hharrison/vecmath/blob/master/src/javax/vecmath/Matrix4d.java>
// <https://github.com/mono/opentk/blob/main/Source/OpenTK/Math/Vector3d.cs>
// <https://github.com/mono/opentk/blob/3de39a402c2d6d859e39b307c46f4376d2097d8c/Source/Compatibility/Math/Matrix4d.cs>

/// RESULT: out_matrix = { { 1,      0,       0, 0 },
///                        { 0, cos(t), -sin(t), 0 },
///                        { 0, sin(t),  cos(t), 0 },
///                        { 0,      0,       0, 1 } }
defFun(0x0047a010, void, __cdecl, Matrix4_RotationX, Matrix4F out_matrix, float theta);
/// RESULT: out_matrix = { {  cos(t), 0, sin(t), 0 },
///                        {       0, 1,      0, 0 },
///                        { -sin(t), 0, cos(t), 0 },
///                        {       0, 0,      0, 1 } }
defFun(0x0047a060, void, __cdecl, Matrix4_RotationY, Matrix4F out_matrix, float theta);
/// RESULT: out_matrix = { { cos(t), -sin(t), 0, 0 },
///                        { sin(t),  cos(t), 0, 0 },
///                        { 0,            0, 1, 0 },
///                        { 0,            0, 0, 1 } }
defFun(0x0047a0b0, void, __cdecl, Matrix4_RotationZ, Matrix4F out_matrix, float theta);
/// RESULT: out_matrix = { { 1, 0, 0, 0 },
///                        { 0, 1, 0, 0 },
///                        { 0, 0, 1, 0 },
///                        { x, y, z, 1 } }
defFun(0x0047a100, void, __cdecl, Matrix4_Translation, Matrix4F out_matrix, const Vector3F* vector);
/// RESULT: out_matrix = { { 1, 0, 0, 0 },
///                        { 0, 1, 0, 0 },
///                        { 0, 0, 1, 0 },
///                        { 0, 0, 0, 1 } }
defFun(0x0047a130, void, __cdecl, Matrix4_Identity, Matrix4F out_matrix);
/// RESULT: out_matrix = { { 0, 0, 0, 0 },
///                        { 0, 0, 0, 0 },
///                        { 0, 0, 0, 0 },
///                        { 0, 0, 0, 0 } }
defFun(0x0047a160, void, __cdecl, Matrix4_Zero, Matrix4F out_matrix);
/// RESULT: out_matrix = src
defFun(0x0047a170, void, __cdecl, Matrix4_Copy, Matrix4F out_matrix, const Matrix4F src);
/// RESULT: out_matrix = { {
///                          a[0,0]*b[0,0] + a[0,1]*b[1,0] + a[0,2]*b[2,0] + a[0,3]*b[3,0],
///                          a[0,0]*b[0,1] + a[0,1]*b[1,1] + a[0,2]*b[2,1] + a[0,3]*b[3,1],
///                          a[0,0]*b[0,2] + a[0,1]*b[1,2] + a[0,2]*b[2,2] + a[0,3]*b[3,2],
///                          a[0,0]*b[0,3] + a[0,1]*b[1,3] + a[0,2]*b[2,3] + a[0,3]*b[3,3]
///                        },{
///                          a[1,0]*b[0,0] + a[1,1]*b[1,0] + a[1,2]*b[2,0] + a[1,3]*b[3,0],
///                          a[1,0]*b[0,1] + a[1,1]*b[1,1] + a[1,2]*b[2,1] + a[1,3]*b[3,1],
///                          a[1,0]*b[0,2] + a[1,1]*b[1,2] + a[1,2]*b[2,2] + a[1,3]*b[3,2],
///                          a[1,0]*b[0,3] + a[1,1]*b[1,3] + a[1,2]*b[2,3] + a[1,3]*b[3,3]
///                        },{
///                          a[2,0]*b[0,0] + a[2,1]*b[1,0] + a[2,2]*b[2,0] + a[2,3]*b[3,0],
///                          a[2,0]*b[0,1] + a[2,1]*b[1,1] + a[2,2]*b[2,1] + a[2,3]*b[3,1],
///                          a[2,0]*b[0,2] + a[2,1]*b[1,2] + a[2,2]*b[2,2] + a[2,3]*b[3,2],
///                          a[2,0]*b[0,3] + a[2,1]*b[1,3] + a[2,2]*b[2,3] + a[2,3]*b[3,3]
///                        },{
///                          a[3,0]*b[0,0] + a[3,1]*b[1,0] + a[3,2]*b[2,0] + a[3,3]*b[3,0],
///                          a[3,0]*b[0,1] + a[3,1]*b[1,1] + a[3,2]*b[2,1] + a[3,3]*b[3,1],
///                          a[3,0]*b[0,2] + a[3,1]*b[1,2] + a[3,2]*b[2,2] + a[3,3]*b[3,2],
///                          a[3,0]*b[0,3] + a[3,1]*b[1,3] + a[3,2]*b[2,3] + a[3,3]*b[3,3]
///                      } }
/*void __cdecl Matrix4_Multiply(Matrix4F out_matrix, const Matrix4F a, const Matrix4F b)
{
    Matrix4_Zero(out_matrix);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                out_matrix[i][j] += a[k][j] * b[i][k];
            }
        }
    }
}
def m4(): return [[0]*4 for _ in range(4)]
def mult(a,b):
    o = m4()
    for i in range(4):
        for j in range(4):
            for k in range(4):
                o[i][j] += a[k][j] * b[i][k]
    return o
                */
/* <https://github.com/mono/opentk/blob/3de39a402c2d6d859e39b307c46f4376d2097d8c/Source/Compatibility/Math/Matrix4d.cs#L712-L731>

        public static void Mult(ref Matrix4d left, ref Matrix4d right, out Matrix4d result)
        {
            result = new Matrix4d();
            result.M11 = left.M11 * right.M11 + left.M12 * right.M21 + left.M13 * right.M31 + left.M14 * right.M41;
            result.M12 = left.M11 * right.M12 + left.M12 * right.M22 + left.M13 * right.M32 + left.M14 * right.M42;
            result.M13 = left.M11 * right.M13 + left.M12 * right.M23 + left.M13 * right.M33 + left.M14 * right.M43;
            result.M14 = left.M11 * right.M14 + left.M12 * right.M24 + left.M13 * right.M34 + left.M14 * right.M44;
            result.M21 = left.M21 * right.M11 + left.M22 * right.M21 + left.M23 * right.M31 + left.M24 * right.M41;
            result.M22 = left.M21 * right.M12 + left.M22 * right.M22 + left.M23 * right.M32 + left.M24 * right.M42;
            result.M23 = left.M21 * right.M13 + left.M22 * right.M23 + left.M23 * right.M33 + left.M24 * right.M43;
            result.M24 = left.M21 * right.M14 + left.M22 * right.M24 + left.M23 * right.M34 + left.M24 * right.M44;
            result.M31 = left.M31 * right.M11 + left.M32 * right.M21 + left.M33 * right.M31 + left.M34 * right.M41;
            result.M32 = left.M31 * right.M12 + left.M32 * right.M22 + left.M33 * right.M32 + left.M34 * right.M42;
            result.M33 = left.M31 * right.M13 + left.M32 * right.M23 + left.M33 * right.M33 + left.M34 * right.M43;
            result.M34 = left.M31 * right.M14 + left.M32 * right.M24 + left.M33 * right.M34 + left.M34 * right.M44;
            result.M41 = left.M41 * right.M11 + left.M42 * right.M21 + left.M43 * right.M31 + left.M44 * right.M41;
            result.M42 = left.M41 * right.M12 + left.M42 * right.M22 + left.M43 * right.M32 + left.M44 * right.M42;
            result.M43 = left.M41 * right.M13 + left.M42 * right.M23 + left.M43 * right.M33 + left.M44 * right.M43;
            result.M44 = left.M41 * right.M14 + left.M42 * right.M24 + left.M43 * right.M34 + left.M44 * right.M44;
        }

BOOL __cdecl Vector3_CompareUnk1(Vector3F* a, float scalar, Vector3F* b, Vector3F* c)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;

    fVar1 = b->y - a->y;
    fVar4 = b->z - a->z;
    fVar3 = b->x - a->x;
    fVar2 = (c->z + c->z) * fVar4 + (c->y + c->y) * fVar1 + (c->x + c->x) * fVar3;
    fVar1 = fVar2 * fVar2 - ((fVar3 * fVar3 + fVar4 * fVar4 + fVar1 * fVar1) * 4.0 - scalar * scalar);
    if ((ushort)((ushort)(fVar1 < 0.0) << 8 | (ushort)(fVar1 == 0.0) << 0xe) == 0) {
        return 1;
    }
    return 0;
}*/
/*void Matrix4_Copy(float* matrix_a, float* matrix_b) {

    float* pfVar1;
    int iVar2;
    int iVar3;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

        }
    }
    iVar3 = 4;
    pfVar1 = matrix_a;
    do {
        iVar2 = 4;
        do {
            *pfVar1 = *(float*)((int)((int)matrix_b - (int)matrix_a) + (int)pfVar1);
            pfVar1 = pfVar1 + 1;
            iVar2 += -1;
        } while (iVar2 != 0);
        iVar3 += -1;
    } while (iVar3 != 0);
    return;
}*/
/*
out_matrix = { { 1, 0, 0, 0 },
               { 0, 1, 0, 0 },
               { 0, 0, 1, 0 },
               { x, y, z, 1 } }

out_matrix = { { cos(t), -sin(t), 0, 0 },
               { sin(t),  cos(t), 0, 0 },
               {      0,       0, 1, 0 },
               {      0,       0, 0, 1 } }

out_matrix = { {  cos(t), 0, sin(t), 0 },
               {       0, 1,      0, 0 },
               { -sin(t), 0, cos(t), 0 },
               {       0, 0,      0, 1 } }

out_matrix = { { 1, 0, 0, 0 },
               { 0, 1, 0, 0 },
               { 0, 0, 1, 0 },
               { 0, 0, 0, 1 } }

out_matrix = { { 1,      0,       0, 0 },
               { 0, cos(t), -sin(t), 0 },
               { 0, sin(t),  cos(t), 0 },
               { 0,      0,       0, 1 } }
*/
//defFun(0x0048e430, short, __cdecl, randomInt16, void);

/// RESULT: out_point = a + (b * dot_product((a - c), (perpendicular(d) / dot_product(perpendicular(b), d))))
/// CONDITION: dot_product(perpendicular(b), d) != 0.0
/*
Point2F* __cdecl Vector2_AAdd_BMulDotProduct_ASubC_PerpDDivDotProductBD(Point2F* out_point, const Point2F* a, const Point2F* b, const Point2F* c, const Point2F* d)
{
    // value = dot_product(perpendicular(b), d)
    float value = (-b->y * d->x) + (b->x * d->y);
    if (value != 0.0) {
        // value = dot_product((a - c), (perpendicular(d) / value))
        value = (a->x - c->x) * -(d->y / value) + (d->x / value) * (a->y - c->y);
        // out_point = a + (b * value)
        /// RESULT: out_point = a + (b * dot_product((a - c), (perpendicular(d) / dot_product(perpendicular(b), d))))
        /// CONDITION: dot_product(perpendicular(b), d) != 0.0
        out_point->x = a->x + (b->x * value);
        out_point->y = a->y + (b->y * value);
        return out_point;
    }
    return nullptr;
    float fVar1;

    fVar1 = -b->y * d->x - -b->x * d->y;
    if (fVar1 != 0.0) {
        fVar1 = (a->x - c->x) * -(d->y / fVar1) + (d->x / fVar1) * (a->y - c->y);
        out_point->x = fVar1 * b->x;
        out_point->y = fVar1 * b->y;
        out_point->x = a->x + out_point->x;
        out_point->y = out_point->y + a->y;
        return out_point;
    }
    return NULL;
}*/
/*Vector3F* __cdecl Vector3_Norm_CrossProduct_CSubB_BSubA_impl(Vector3F* out_vector, const Vector3F* a, const Vector3F* b, const Vector3F* c)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;

    // out_vector = norm(cross_product((c - b), (b - a)))
    Vector3F vec = {
        (c->z - b->z)*(b->y - a->y) - (c->y - b->y)*(b->z - a->z),
        (c->x - b->x)*(b->z - a->z) - (c->z - b->z)*(b->x - a->x),
        (c->y - b->y)*(b->x - a->x) - (c->x - b->x)*(b->y - a->y)
    };
    float value = 1.0f / std::sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
    out_vector->x = vec.x * value;
    out_vector->y = vec.y * value;
    out_vector->z = vec.z * value;
    return Vector3_Normalize(&vector);
    fVar2 = (c->x - b->x)*(b->z - a->z) - (c->z - b->z)*(b->x - a->x);
    fVar4 = (c->y - b->y)*(b->x - a->x) - (c->x - b->x)*(b->y - a->y);
    fVar3 = (c->z - b->z)*(b->y - a->y) - (c->y - b->y)*(b->z - a->z);

    // norm(

    fVar1 = c->x - b->x;
    fVar4 = b->x - a->x;
    fVar3 = c->y - b->y;
    fVar5 = c->z - b->z;
    fVar6 = b->y - a->y;
    fVar7 = b->z - a->z;
    fVar2 = fVar1 * fVar7 - fVar5 * fVar4;
    fVar4 = fVar3 * fVar4 - fVar1 * fVar6;
    fVar3 = fVar5 * fVar6 - fVar3 * fVar7;
    fVar1 = 1.0f / std::sqrt(fVar3 * fVar3 + fVar4 * fVar4 + fVar2 * fVar2);
    out_vector->x = fVar1 * fVar3;
    out_vector->y = fVar1 * fVar2;
    out_vector->z = fVar1 * fVar4;
    return out_vector;
}*/

#pragma endregion


#pragma region Font.c


defFun(0x0047a1a0, ImageFont*, __cdecl, Image_LoadFont, const char* filename);
// ...

#pragma endregion


#pragma region Files.c

/// PUBLIC:
defFun(0x0047f3f0, void, __cdecl, InitFileSystem, const char* gameName, BOOL insistOnCD, const char* regKey);
/// INTERNAL:
defFun(0x0047f7b0, BOOL, __cdecl, Path_CheckForCDROM, void);
defFun(0x0047f850, BOOL, __cdecl, Path_SetDataDir, const char* dirname);
/// INTERNAL: But also visible to WAD.c
defFun(0x0047f8c0, void, __cdecl, File__logf, const char* format, ...);
defFun(0x0047f900, int, __cdecl, File_OpenWAD, const char* filename);
/// PUBLIC:
defFun(0x0047f920, BOOL, __cdecl, Path_GetCDROMDataPath, char* out_filepath, const char* filename);
defFun(0x0047f960, int, __cdecl, Path_MakeDataSubdir, const char* dirname);
defFun(0x0047f9a0, FileStream*, __cdecl, File_Open, const char* filename, const char* mode);
defFun(0x0047fb10, int, __cdecl, File_Seek, FileStream* file, long offset, int origin);
defFun(0x0047fc40, size_t, __cdecl, File_Read, void* out_buffer, size_t size, size_t count, FileStream* file);
defFun(0x0047fd10, size_t, __cdecl, File_Write, const void* in_buffer, size_t size, size_t count, FileStream* file);
defFun(0x0047fd80, size_t, __cdecl, File_Close, FileStream* file);
defFun(0x0047fdd0, long, __cdecl, File_Tell, FileStream* file);
defFun(0x0047fe20, BOOL, __cdecl, File_Exist, const char* filename);
defFun(0x0047fee0, int, __cdecl, File_GetC, FileStream* file);
defFun(0x0047ff60, int, __cdecl, File_GetLength, FileStream* file);
/// INTERNAL:
defFun(0x0047ffa0, char*, __cdecl, File_GetS_WAD__internal, char* out_str, int num, FileStream* file);
/// PUBLIC:
defFun(0x00480000, char*, __cdecl, File_GetS, char* out_str, int num, FileStream* file);
defFun(0x00480070, char*, __cdecl, File_PrintF, FileStream* file, const char* format, ...);
/// INTERNAL:
defFun(0x004800e0, FileLocation, __cdecl, File_GetLocation, FileStream* file);
defFun(0x004800f0, FileLocation, __cdecl, File_FindLocation, const char* filename, const char* mode);
defFun(0x00480160, BOOL, __cdecl, File_OpenWADEntry, FileWADStream* wadStream, const char* filename);
defFun(0x00480190, FileStream*, __cdecl, File__New, FileLocation location);
defFun(0x004801f0, void*, __cdecl, File__malloc, size_t size);
defFun(0x00480200, void, __cdecl, File__free, void* ptr);
defFun(0x00480210, void, __cdecl, File__Dispose, FileStream* file);
defFun(0x00480280, const char*, __cdecl, Path_StripDataDir, const char* filename);
/// PUBLIC:
defFun(0x00480310, char*, __cdecl, File_GetS_StripLineEnd, char* out_str, int num, FileStream* file);
defFun(0x00480360, unsigned char*, __cdecl, File_ReadAllBytes, const char* filename, unsigned int* out_length);
defFun(0x00480380, void*, __cdecl, File_ReadAll, const char* filename, unsigned int* out_length, BOOL isBinary);
defFun(0x00480430, int, __cdecl, File_BufferOpen, const char* filename, unsigned int* out_length);
defFun(0x004804e0, const char*, __cdecl, Path_JoinDataDir, const char* filename);
defFun(0x00480570, void, __cdecl, File_SetOpenCallback, FileOpenCallback callback, void* lpValue);
defFun(0x00480590, void, __cdecl, Scan_ReadDataDirList, const char* listFilename);
defFun(0x00480650, void, __cdecl, Scan_Directory, const char* dirname);
defFun(0x00480830, int, __cdecl, Scan_File, const char* filename);

#pragma endregion


#pragma region Scan.c

defFun(0x0048b520, void, __cdecl, InitFileScanning, void);
defFun(0x0048b540, void, __cdecl, Scan_SetIsFullScreen, BOOL isFullScreen);
defFun(0x0048b550, void, __cdecl, Scan_Cleanup, void);
defFun(0x0048b5b0, void, __cdecl, Scan_WriteDataDirList, void);

#pragma endregion

#pragma region WAD.c

/// INTERNAL:
// NOTE: This is not a CRT function, it's again, DDI(?) implementing a
// function that you'd commonly expect to see used.
// Read null-terminated string from file. (DOES NOT CHECK FOR EOF!!)
// always returns true.
defFun(0x0048b760, BOOL, __cdecl, WAD_freadstr, FILE* stream, char* out_str);
/// PUBLIC:
defFun(0x0048b7a0, int, __cdecl, WAD_Open, const char* filename);
/// INTERNAL:
defFun(0x0048bfa0, WADFile*, __cdecl, WAD_Get, int wadIndex);
defFun(0x0048bfb0, unsigned int, __cdecl, WAD_GetEntrySize, int wadIndex, int entryIndex);
defFun(0x0048bfd0, unsigned int, __cdecl, WAD_GetEntryPackedSize, int wadIndex, int entryIndex);
defFun(0x0048bff0, int, __cdecl, WAD_Stream__Next, void);
/// PUBLIC:
defFun(0x0048c010, int, __cdecl, WAD_FindEntry, const char* filename, int opt_wadIndex);
/// INTERNAL:
defFun(0x0048c060, int, __cdecl, WAD_FindEntryInWAD, const char* filename, int wadIndex);
defFun(0x0048c0c0, int, __cdecl, WAD__Next, void);
defFun(0x0048c100, int, __cdecl, WAD_StreamOpenInWAD, const char* filename, int wadIndex);
/// PUBLIC:
defFun(0x0048c230, int, __cdecl, WAD_StreamOpen, const char* filename, int opt_wadIndex);
defFun(0x0048c280, void, __cdecl, WAD_StreamClose, int streamIndex);
/// INTERNAL:
defFun(0x0048c2b0, void*, __cdecl, WAD_StreamGetData__internal, int streamIndex);
defFun(0x0048c2d0, unsigned int, __cdecl, WAD_StreamGetSize, int streamIndex);
defFun(0x0048c2f0, void*, __cdecl, WAD_StreamGetData, int streamIndex);

#pragma endregion


#pragma region RNC.c

/// PUBLIC:
defFun(0x0049ca80, unsigned int, __cdecl, Rnc_Decompress, void* srcBuffer, void** out_dstBuffer);
/// INTERNAL:
// short return values are RncResult enums
defFun(0x0049cb00, short, __cdecl, Rnc_Decompress__internal, void* srcBuffer, void* dstBuffer);
defFun(0x0049cba0, short, __cdecl, Rnc_Decompress_Method1, void* srcBuffer, void* dstBuffer);
defFun(0x0049cd20, short, __cdecl, Rnc_Decompress_Method2, void* srcBuffer, void* dstBuffer);
defFun(0x0049cf30, void*, __cdecl, Rnc_BitStreamInit, void* srcBuffer, void* dstBuffer);
defFun(0x0049cf80, unsigned int, __cdecl, Rnc_BitStreamAdvance, unsigned char bits);
defFun(0x0049cff0, int, __cdecl, Rnc_FUN_0049cff0, unsigned char bits);
defFun(0x0049d050, void, __cdecl, Rnc_ReadHuffmanTable, HuffmanLeaf* table, unsigned char bits);
defFun(0x0049d0c0, unsigned int, __cdecl, Rnc_ReadHuffman, HuffmanLeaf* table);
defFun(0x0049d130, unsigned int, __cdecl, Rnc_FUN_0049d130, void);
defFun(0x0049d170, int, __cdecl, Rnc_FUN_0049d170, void);
defFun(0x0049d210, void, __cdecl, Rnc_FUN_0049d210, HuffmanLeaf* table, unsigned char bits);
defFun(0x0049d250, void, __cdecl, Rnc_FUN_0049d250, HuffmanLeaf* table, unsigned char bits);
defFun(0x0049d2c0, unsigned int, __cdecl, Rnc_MirrorBits, unsigned int value, unsigned char bits);

#pragma endregion




defFun(0x0042e7e0, BOOL, __cdecl,	Game_GetObjectByName, const char* objName, lego::ObjectType* out_objType, int* out_objIndex, lego::ResourceData** out_resData);
defFun(0x004314a0, LevelSurfaceMap*, __cdecl,	GetSurfaceMap, void);
defFun(0x00450390, BOOL, __cdecl, FUN_00450390, LevelSurfaceMap* surfMap, int x, int y, void* param_4);
defFun(0x0048e430, short, __cdecl, randomInt16, void);
defFun(0x004388d0, LiveObject*, __cdecl, Game_CreateLiveResourceObject, ResourceData* resData, ObjectType objType, int objIndex, int objLevel, float x, float y, float theta);

/*defFun(0x004297b0, long double, __cdecl, Level_GetTrainTimeLD, void);
defFun(0x004297b0, double, __cdecl, Level_GetTrainTimeD, void);*/
defFun(0x004297b0, float, __cdecl, Level_GetTrainTime, void);
/*defFun(0x0041fa70, long double, __cdecl, Game_GetGameSpeedLD, void);
defFun(0x0041fa70, double, __cdecl, Game_GetGameSpeedD, void);*/
defFun(0x0041fa70, float, __cdecl, Game_GetGameSpeed, void);

defVar(0x0076bc84, IDirectDraw4*,	g_IDirectDraw4);

defVar(0x004dfe44, unsigned int,	g_LiveObjectLevels_Current_TABLE, [20][15][16]);  // [20][15][16]
defVar(0x004e4944, unsigned int,	g_LiveObjectLevels_Previous_TABLE, [20][15][16]); // [20][15][16]
defVar(0x004e9444, unsigned int,	g_NERPs_TrainFlags);
defVar(0x004e9448, LiveObject*,		MINIFIGOBJ_004e9448);
defVar(0x004e944c, lego::Point2I,	g_SlimySlugHoles_TABLE, [20]);
defVar(0x004e94ec, lego::Point2I,	g_RechargeSeams_TABLE, [10]);
defVar(0x004e953c, unsigned int,	g_SlimySlugHoles_COUNT);
defVar(0x004e9540, unsigned int,	g_RechargeSeams_COUNT);
defVar(0x004e9544, unsigned int,	DAT_004e9544);
defVar(0x004e9548, unsigned int,	DAT_004e9548);
defVar(0x004e954c, unsigned int,	DAT_004e954c);
defVar(0x004e9550, unsigned int,	DAT_004e9550);
defVar(0x004e9554, unsigned int,	DAT_004e9554);
defVar(0x004e9558, unsigned int,	DAT_004e9558);
defVar(0x004e955c, unsigned int,	DAT_004e955c);
defVar(0x004e9560, unsigned int,	DAT_004e9560);
defVar(0x004e9564, unsigned int,	DAT_004e9564);
defVar(0x004e9568, unsigned int,	DAT_004e9568);
defVar(0x004e956c, unsigned int,	DAT_004e956c);


defVar(0x004ebbc4, unsigned int,	DAT_004ebbc4);
defVar(0x004ebbc8, unsigned int,	DAT_004ebbc8);
defVar(0x004ebbcc, LiveObject*,		PTR_ARRAY_004ebbcc, [100]);
defVar(0x004ebd5c, unsigned int,	UINT_004ebd5c);
defVar(0x004ebd60, char*,			g_AbilityTypes_TABLE, [6]);
defVar(0x004ebd78, void*,			g_ToolTipIcons_Abilities_TABLE, [6]);
defVar(0x004ebd90, void*,			g_ToolTipIcons_Tools_TABLE, [11]);
defVar(0x004ebdbc, void*,			g_ToolTipIcon_Blank);
defVar(0x004ebdc0, void*,			g_ToolTipIcon_Ore);
defVar(0x004ebdc4, unsigned int,	g_BuildingsTeleported);

defVar(0x004ebdd8, lego::ResourceData*,	RESDATA_004ebdd8);
defVar(0x004ebddc, lego::ResourceData*,	RESDATA_004ebddc);
defVar(0x004ebde0, lego::ColourRGBF,	Vector3F_004ebde0);
defVar(0x004ebdec, lego::ColourRGBF,	Vector3F_004ebdec);
defVar(0x004ebdf8, lego::ColourRGBF,	g_BlinkRGBMax);
defVar(0x004ebe04, unsigned int,	DAT_004ebe04);
defVar(0x004ebe08, float,			g_RandomRangeForTimeBetweenBlinks_min);
defVar(0x004ebe0c, float,			g_RandomRangeForTimeBetweenBlinks_max);
defVar(0x004ebe10, unsigned int,	DAT_004ebe10);
defVar(0x004ebe14, float,			g_MaxChangeAllowed);
defVar(0x004ebe18, float,			FLOAT_004ebe18);
defVar(0x004ebe1c, float,			FLOAT_004ebe1c);
defVar(0x004ebe20, float,			FLOAT_004ebe20);
defVar(0x004ebe24, lego::ColourRGBF,	g_FadeRGBMin);
defVar(0x004ebe30, lego::ColourRGBF,	g_FadeRGBMax);
defVar(0x004ebe3c, float,			FLOAT_004ebe3c);
defVar(0x004ebe40, float,			g_RandomRangeForTimeBetweenFades_min);
defVar(0x004ebe44, float,			g_RandomRangeForTimeBetweenFades_max);
defVar(0x004ebe48, float,			FLOAT_004ebe48);
defVar(0x004ebe4c, float,			FLOAT_004ebe4c);
defVar(0x004ebe50, float,			FLOAT_004ebe50);
defVar(0x004ebe54, float,			g_RandomRangeForFadeTimeFade_min);
defVar(0x004ebe58, float,			g_RandomRangeForFadeTimeFade_max);
defVar(0x004ebe5c, float,			FLOAT_004ebe5c);
defVar(0x004ebe60, float,			g_RandomRangeForHoldTimeOfFade_min);
defVar(0x004ebe64, float,			g_RandomRangeForHoldTimeOfFade_max);
defVar(0x004ebe68, float,			FLOAT_004ebe68);
defVar(0x004ebe6c, float,			FLOAT_004ebe6c);
defVar(0x004ebe70, float,			FLOAT_004ebe70);
defVar(0x004ebe74, lego::Vector3F,	Vector3F_004ebe74);
defVar(0x004ebe80, lego::Vector3F,	g_MoveLimit_Vector);
defVar(0x004ebe8c, float,			FLOAT_004ebe8c);
defVar(0x004ebe90, float,			g_RandomRangeForTimeBetweenMoves_min);
defVar(0x004ebe94, float,			g_RandomRangeForTimeBetweenMoves_max);
defVar(0x004ebe98, float,			FLOAT_004ebe98);
defVar(0x004ebe9c, float,			g_RandomRangeForSpeedOfMove_min);
defVar(0x004ebea0, float,			g_RandomRangeForSpeedOfMove_max);
defVar(0x004ebea4, float,			FLOAT_004ebea4);
defVar(0x004ebea8, float,			FLOAT_004ebea8);
defVar(0x004ebeac, float,			FLOAT_004ebeac);
defVar(0x004ebeb0, float,			FLOAT_004ebeb0);
defVar(0x004ebeb4, float,			g_RandomRangeForDistOfMove_min);
defVar(0x004ebeb8, float,			g_RandomRangeForDistOfMove_max);

defVar(0x004ebec8, unsigned int,	FLAGS_004ebec8);

defVar(0x004ebf20, unsigned char,	MessageAction_ARRAY_ARRAY_004ebf20, [2][2048][0x14]); // dummy data type [0x14]

defVar(0x004fff28, BOOL,			BOOL_004fff28);
defVar(0x004fff2c, LiveObject*,		g_SelectedUnits_TABLE, [100]);
defVar(0x005000bc, unsigned char,	g_SelectedUnit_Hotkeys_Keys_TABLE, [10]);
defVar(0x005000c8, unsigned char,	g_SelectedUnit_Hotkeys_Actions_TABLE, [10][0x14]); // dummy data type [0x14]
defVar(0x00500190, char*,			g_Messages_TABLE, [65]);
defVar(0x00500294, unsigned int,	DAT_00500294);
defVar(0x00500298, unsigned int,	g_SelectedUnits_COUNT);
defVar(0x0050029c, unsigned int,	g_SelectedUnit_Hotkeys_COUNT);

defVar(0x00500958, int,					g_NERPs_REGISTERS_TABLE, [8]);
defVar(0x00500978, BOOL,				g_NERPs_IsLoaded);

defVar(0x00500980, unsigned int,		g_NERPs_TutorialFlags);

defVar(0x00500990, int,					g_NERPs_HiddenObjectsFound);
defVar(0x00500994, int,					g_NERPs_MessageWait);

defVar(0x005009a0, float,				g_NERPs_TIMERS_TABLE, [4]);

defVar(0x00500bc0, unsigned int,		g_ObjectiveFlags);

defVar(0x00500e30, BOOL,				g_LevelIsComplete);

defVar(0x00500e48, BOOL,				g_IsEndTeleportEnabled);

defVar(0x00500e68, unsigned int,		g_ObjInfoFlags__00500e68);
defVar(0x00500e6c, unsigned int,		DAT_00500e6c);
defVar(0x00500e70, unsigned int,		DAT_00500e70);
defVar(0x00500e74, lego::Size2F,		g_HealthBarWidthHeight);
defVar(0x00500e7c, unsigned int,		g_HealthBarBorderSize);
defVar(0x00500e80, float,				g_HealthBarBorderRGB_red);
defVar(0x00500e84, float,				g_HealthBarBorderRGB_red_bright);
defVar(0x00500e88, float,				g_HealthBarBorderRGB_red_dark);
defVar(0x00500e8c, float,				g_HealthBarBorderRGB_green);
defVar(0x00500e90, float,				g_HealthBarBorderRGB_green_bright);
defVar(0x00500e94, float,				g_HealthBarBorderRGB_green_dark);
defVar(0x00500e98, float,				g_HealthBarBorderRGB_blue);
defVar(0x00500e9c, float,				g_HealthBarBorderRGB_blue_bright);
defVar(0x00500ea0, float,				g_HealthBarBorderRGB_blue_dark);
defVar(0x00500ea4, lego::ColourRGBF,	g_HealthBarRGB);
defVar(0x00500eb0, lego::ColourRGBF,	g_HealthBarBackgroundRGB);
defVar(0x00500ebc, lego::Point2F,	g_HungerImagesPosition);

defVar(0x00500ed8, lego::Point2F,	g_BubbleImagesPosition);



defVar(0x005010e0, const char*,		g_PanelTypes_TABLE, [24]);

defVar(0x0050134c, unsigned int,	DAT_0050134c);
defVar(0x00501350, char*,			g_PanelButtons_Radar_TABLE, [24]);
defVar(0x005013b0, char*,			g_PanelButtons_unused1_TABLE, [24]);
defVar(0x00501410, char*,			g_PanelButtons_unused2_TABLE, [24]);
defVar(0x00501470, char*,			g_PanelButtons_unused3_TABLE, [24]);
defVar(0x005014d0, char*,			g_PanelButtons_unused4_TABLE, [24]);
defVar(0x00501530, char*,			g_PanelButtons_CrystalSideBar_TABLE, [24]);
defVar(0x00501590, char*,			g_PanelButtons_TopPanel_TABLE, [24]);
defVar(0x005015f0, char*,			g_PanelButtons_Information_TABLE, [24]);
defVar(0x00501650, char*,			g_PanelButtons_PriorityList_TABLE, [24]);
defVar(0x005016b0, char*,			g_PanelButtons_CameraControl_TABLE, [24]);
defVar(0x00501710, char*,			g_PanelButtons_InfoDock_TABLE, [24]);
defVar(0x00504190, char*,			g_PanelButtons_Encyclopedia_TABLE, [24]);
defVar(0x005017d0, unsigned int,	UINT_005017d0);
defVar(0x005017d4, unsigned int,	UINT_005017d4);
defVar(0x005017d8, unsigned int,	DAT_005017d8);
defVar(0x005017dc, unsigned int,	DAT_005017dc);
defVar(0x005017e0, void*,			g_RightPanel_SmallCrystal_bmp);
defVar(0x005017e4, void*,			g_RightPanel_NoSmallCrystal_bmp);
defVar(0x005017e8, void*,			g_RightPanel_UsedCrystal_bmp);
defVar(0x005017ec, unsigned int,	g_RewardsQuotaCrystals);
defVar(0x005017f0, void*,			g_AirMeter_AirJuice_bmp);
defVar(0x005017f4, void*,			g_AirMeter_NoAir_bmp);
defVar(0x005017f8, lego::Point2F,	g_AirMeter_AirJuice_positionORsize);
defVar(0x00501800, unsigned int,	UINT_00501800);
defVar(0x00501804, lego::Point2F,	g_AirMeter_NoAir_positionORsize);
defVar(0x0050180c, unsigned int,	DAT_0050180c);
defVar(0x00501810, unsigned int,	DAT_00501810);
defVar(0x00501814, lego::Point2F,	g_RightPanel_CryOreSideBar_positionORsize);
defVar(0x0050181c, unsigned int,	UINT_0050181c);
defVar(0x00501820, float,			FLOAT_00501820);
defVar(0x00501824, lego::Point2I,	g_PanelRotationControl_CenterPosition);
defVar(0x0050182c, int,				g_PanelRotationControl_Radius);
defVar(0x00501830, lego::Point2F,	g_PanelRotationControl_UpImage_position);
defVar(0x00501838, lego::Point2F,	g_PanelRotationControl_DownImage_position);
defVar(0x00501840, lego::Point2F,	g_PanelRotationControl_LeftImage_position);
defVar(0x00501848, lego::Point2F,	g_PanelRotationControl_RightImage_position);

defVar(0x00501e1c, const char*,		g_Pointers_TABLE, [56]);

defVar(0x0050211c, const char*,		g_PriorityNames_a_TABLE, [27]);
defVar(0x00502188, lego::Point2F,	g_PrioritiesImagePositions_TABLE, [27]);
defVar(0x00502260, const char*,		g_PriorityNames_b_TABLE, [27]);
defVar(0x005022cc, unsigned int,	g_Priorities_unk_TABLE, [27]);
defVar(0x00502338, BOOL,			g_Priorities_bool1_TABLE, [27]);
defVar(0x005023a4, unsigned int,	g_LevelPriorities_COUNT);

defVar(0x00502468, unsigned char,	g_SampleProperties_TABLE, [495][0x8]); // dummy data type [0x8]
defVar(0x005033e0, unsigned char,	g_SampleGroups_TABLE, [200][0x8]); // dummy data type [0x8]
defVar(0x00503a20, unsigned int*,	g_SampleHashNames_TABLE);
defVar(0x00503a24, unsigned int,	g_SampleHashNames_COUNT);
defVar(0x00503a28, unsigned int,	g_SampleGroups_COUNT);
defVar(0x00503a2c, unsigned int,	g_AudioFlags);
defVar(0x00503a30, unsigned char,	g_Sound3DInstances_TABLE, [10][0x18]); // dummy data type [0x18]
defVar(0x00503b20, unsigned int,	g_Sound3DInstances_COUNT);
defVar(0x00503b24, float,			g_GlobalSampleDuration);
defVar(0x00503b28, int,				INT_00503b28);
defVar(0x00503b2c, int,				g_GlobalSampleIndex);
defVar(0x00503b30, int,				g_SoundQueueIndexes_Unk1_TABLE, [10]);
defVar(0x00503b58, BOOL,			g_SoundQueueModes_Unk1_TABLE, [10]);
defVar(0x00503b80, int,				g_SoundQueueIndexes_Unk2_TABLE, [10]);
defVar(0x00503ba8, BOOL,			g_SoundQueueModes_Unk2_TABLE, [10]);
defVar(0x00503bd0, unsigned int,	g_SoundQueue_Unk1_COUNT);
defVar(0x00503bd4, unsigned int,	g_SoundQueue_Unk2_COUNT);
defVar(0x00503bd8, ObjectStats**,	g_ObjectStats_TABLE, [20]);      // [20][*][*]
defVar(0x00503c28, unsigned int,	g_ObjectLevels_TABLE, [20][15]); // [20][15]

defVar(0x00504188, BOOL,			BOOL_00504188);

defVar(0x00504190, char*,			g_TextTypes_TABLE, [26]);


defVar(0x00504608, unsigned int,	g_Texts_mutable_COUNT);
defVar(0x0050460c, unsigned int,	g_Texts_COUNT);

defVar(0x00504870, unsigned int,	g_WeaponTypes_COUNT);
defVar(0x00504874, char**,			g_WeaponNames_TABLE);


defVar(0x005063fc, CFGProperty*,	g_LegoCfgRoot_WeaponTypes);
defVar(0x00506400, char,			tmp_CHAR_ARRAY_00506400, [1024]);
defVar(0x00506800, HWND,			g_hWnd);
defVar(0x00506804, HINSTANCE,		g_hInstance);
defVar(0x00506808, BOOL,			g_IsFocused);
defVar(0x0050680c, BOOL,			g_IsClosing);
defVar(0x00506810, const char*,		g_WindowClassName);
defVar(0x00506814, char,			g_ExeName, [256]);
defVar(0x00506914, void*,			g_IDirect3DRM3);
defVar(0x00506918, void*,			g_IDirect3DRMDevice3);
defVar(0x0050691c, void*,			g_IDirect3DDevice3);
defVar(0x00506920, unsigned int,	g_SceneFogMethod);
defVar(0x00506924, lego::Size2I,	g_RESOLUTION);
defVar(0x0050692c, lego::GameFunctions,	g_GameFunctions);
defVar(0x00506938, BOOL,					g_GameFunctions_ISINIT);
defVar(0x0050693c, float,					g_FPSLOCK_VSYNC);
defVar(0x00506f80, DWORD,					g_WindowStyle);
defVar(0x00506f84, lego::CmdlineFlags,		g_CMDLINE_FLAGS);
defVar(0x00506f88, lego::ProgrammerMode,	g_PROGRAMMER_MODE);
defVar(0x00506f8c, char,					g_STARTLEVEL, [256]);
defVar(0x00506f8c, lego::FeatureFlags,		g_DEBUG_FLAGS);



defVar(0x005570c0, GameManager,		g_Game);
defVar(0x005570d4, LevelData*,		g_Game_level);


defVar(0x004b41c8, AITaskData*,		g_AITasks_TABLE, [12]);
defVar(0x004b41f8, AITaskData*,		g_AITasks_NEXT);
defVar(0x004b41fc, unsigned int,	g_AITasks_COUNT);
defVar(0x004b9060, unsigned int,	g_AITasks_INITFLAGS);

defVar(0x004df790, LiveObject*,		g_LiveObjects_POOL, [32]);
defVar(0x004df810, LiveObject*,		g_LiveObjects_NEXT);
defVar(0x004dfe10, unsigned int,	g_LiveObjects_COUNT);
defVar(0x004dfe14, unsigned int,	g_LiveObjects_INITFLAGS);

defVar(0x0076bd80, ResourceData*,	g_Resources_TABLE, [20]);
defVar(0x0076bdd0, ResourceData*,	g_Resources_NEXT);
defVar(0x0076dd90, unsigned int,	g_Resources_COUNT);
defVar(0x0076dd94, unsigned int,	g_Resources_INITFLAGS);


defVar(0x00507098, char,			tmp_CFG_JOINPATH, [1024]);
defVar(0x00507498, CFGProperty*,	ReservedPool_CFGProperty___g_TABLE, [32]);
defVar(0x00507518, CFGProperty*,	ReservedPool_CFGProperty___g_NEXT);
defVar(0x0050751c, unsigned int,	ReservedPool_CFGProperty___g_COUNT);
defVar(0x00507520, BOOL,			ReservedPool_CFGProperty___g_ISINIT);



defFun(0x00474ce0, int, __cdecl,	Res_GetMeshGroupCount, ResourceData* resData);
defFun(0x004752e0, void, __cdecl,	Res_SetMeshColorMultiplier, ResourceData* resData, int index, float r, float g, float b, float multiplier);
defFun(0x004752b0, void, __cdecl,	Res_SetMeshColorUnk, ResourceData* resData, int index, float r, float g, float b);

defVar(0x00557428, lego::ColourRGBF,	g_PowerCrystalRGB);
defVar(0x00557434, lego::ColourRGBF,	g_UnpoweredCrystalRGB);


defVar(0x0055850c, lego::Size2I,	g_Menu_SaveImage_BigSize);

defVar(0x00558514, char,			g_Menu_LoadGame_text, [64]);
defVar(0x00558554, char,			g_Menu_SaveGame_text, [64]);
defVar(0x00558594, void*,			g_UnkStruct728_Menu_SaveText);
defVar(0x00558598, void*,			g_UnkStruct728_Menu_LevelText);
defVar(0x0055859c, char,			g_MenuOverwrite_Title, [128]);
defVar(0x0055861c, char,			g_MenuOverwrite_Text, [256]);
defVar(0x0055871c, char,			g_MenuOverwrite_Ok, [128]);
defVar(0x0055879c, char,			g_MenuOverwrite_Cancel, [128]);
defVar(0x0055881c, unsigned int,	DAT_0055881c);
defVar(0x00558824, unsigned int,	DAT_00558824);
defVar(0x00558828, int,				g_Menu_MaxLevelScreens);

defVar(0x00558834, unsigned int,	DAT_00558834);
defVar(0x00558838, unsigned int,	DAT_00558838);
defVar(0x0055883c, BOOL,			BOOL_0055883c);
defVar(0x00558840, float,			FLOAT_00558840);


defVar(0x00558850, float,			g_Flocks_Turn);
defVar(0x00558854, float,			g_Flocks_Speed);
defVar(0x00558858, float,			g_Flocks_Tightness);
defVar(0x0055885c, float,			g_Flocks_GoalUpdate);
defVar(0x00558860, BOOL,			g_ObjectUIsAlwaysVisible);
defVar(0x00558864, const char*,		g_Bubbles_bmp_TABLE, [39]);
defVar(0x00558900, const char*,		g_Bubbles_TABLE, [39]);

defVar(0x005590a0, int,				g_DriverModes_COUNT);
defVar(0x005590a4, int,				g_DeviceModes_COUNT);
defVar(0x005590a8, int,				g_ScreenModes_COUNT);
defVar(0x005590ac, unsigned char,	g_DriverModes_TABLE, [200][0x114]); // dummy data type [0x114]
defVar(0x0055a63c, unsigned char,	g_DeviceModes_TABLE, [200][0x114]); // dummy data type [0x114]
defVar(0x0055bbcc, unsigned char,	g_ScreenModes_TABLE, [200][0x110]); // dummy data type [0x110]
defVar(0x0056904c, void*,			g_CurrentDriverMode);
defVar(0x00569050, void*,			g_CurrentDeviceMode);
defVar(0x00569054, void*,			g_CurrentScreenMode);
defVar(0x00569058, BOOL,			g_IsFullScreen);
defVar(0x0056905c, BOOL,			g_IsFullScreen_Backup);
defVar(0x00569060, unsigned char,	g_RegisteredScreenModes_TABLE, [200][0x110]); // dummy data type [0x110]
defVar(0x005764e0, int,				g_RegisteredScreenModes_COUNT);

defVar(0x00576500, unsigned char,   g_WADFiles_TABLE, [10][0x24]); // dummy data type [0x10]

defVar(0x005766a0, unsigned char,   g_WADStreams_TABLE, [100][0x10]); // dummy data type [0x10]
defVar(0x00576ce0, void*,			g_ScanFileStream_1);
defVar(0x00576ce4, void*,			g_ScanFileStream_2);
defVar(0x00576ce8, void*,			g_ScanFileStream_3);
defVar(0x00576cec, void*,			g_ScanFileStream_OutputList);
defVar(0x00576cf0, char,			g_ScanFilename_InputList, [1024]);
defVar(0x005770f0, char,			g_ScanFilename_OutputList, [1024]);

defVar(0x005774f4, BOOL,			g_ScanIsFullScreen);

defVar(0x00577500, char,			g_mciErrorText, [200]);

defVar(0x005775e0, const char*,		g_KEYS_TABLE, [256]);
defVar(0x005779e0, char,			g_ScanRealFiles_FilePaths_TABLE, [2000][1024]);
defVar(0x0076b9e0, unsigned int,	g_ScanRealFiles_FilePaths_COUNT);

defVar(0x0076ba00, bool,	g_KeyboardState_Current_TABLE, [256]);
defVar(0x0076bb00, void*,	g_IDirectInputA);
defVar(0x0076bb04, BOOL,	g_IsDirectInputAcquired);

defVar(0x0076bb24, lego::Point2I,	g_MousePosition);

defVar(0x0076bb34, lego::Point2I,	g_MouseDeltaPosition);
defVar(0x0076bb3c, BOOL,	g_LeftButtonState);
defVar(0x0076bb40, BOOL,	g_RightButtonState);
defVar(0x0076bb44, BOOL,	BOOL_0076bb44);
defVar(0x0076bb48, BOOL,	BOOL_0076bb48);
defVar(0x0076bb4c, BOOL,	BOOL_0076bb4c);
defVar(0x0076bb50, BOOL,	BOOL_0076bb50);
defVar(0x0076bb54, BOOL,	BOOL_0076bb54);
defVar(0x0076bb58, BOOL,	g_RightButtonDoubleClicked);

defVar(0x0076bb80, bool,	g_KeyboardState_Previous_TABLE, [256]);


//typedef unsigned int ObjArrayIndexes[15];
//typedef unsigned int ObjArrayLevels[15][16];


#pragma endregion
} /* namespace external */
//#pragma warning restore format
//}

/*namespace lego {
namespace globals {
///////////////////



	extern volatile char* (&g_AbilityTypes_TABLE)[6] = *(volatile char*(*)[6])0x004ebd60;

	extern volatile unsigned int (&g_BuildingsTeleported);

///////////////////
}
}*/

/*#ifndef DEFINE_EXTERNALS
#else
#ifndefdef EXTERNAL_H
#endif*/