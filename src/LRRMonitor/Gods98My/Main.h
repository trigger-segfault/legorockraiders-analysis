#pragma once

#include "../framework.h"
#include "DirectDraw.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Forward Declarations
 **********************************************************************************/

#pragma region Forward Declarations

struct DirectDraw_Device;

#pragma endregion

/**********************************************************************************
 ******** Function Typedefs
 **********************************************************************************/

#pragma region Function Typedefs

typedef BOOL (__cdecl* MainStateInitialise)(void);
typedef BOOL (__cdecl* MainStateMainLoop)(float elapsedTime);
typedef void (__cdecl* MainStateShutdown)(void);
// (unused)
typedef void (__cdecl* MainWindowCallback)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#pragma endregion

/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define MAIN_MAXRENDERSTATES				200

#pragma endregion

/**********************************************************************************
 ******** Enumerations
 **********************************************************************************/

#pragma region Enums

#define MAIN_FLAG_UPDATED					0x00000001
#define MAIN_FLAG_FULLSCREEN				0x00000002
#define MAIN_FLAG_VIDEOTEXTURE				0x00000004
#define MAIN_FLAG_MIPMAPENABLED				0x00000008
#define MAIN_FLAG_PAUSED					0x00000010
#define MAIN_FLAG_DONTMANAGETEXTURES		0x00000020
#define MAIN_FLAG_BEST						0x00000040
#define MAIN_FLAG_DUMPMODE					0x00000080
#define MAIN_FLAG_WINDOW					0x00000100
#define MAIN_FLAG_STARTLEVEL				0x00000200
#define MAIN_FLAG_CLEANSAVES				0x00000400
#define	MAIN_FLAG_SAVELANGFILE				0x00000800
#define	MAIN_FLAG_LANGDUMPUNKNOWN			0x00001000
#define MAIN_FLAG_DEBUGMODE					0x00002000
#define MAIN_FLAG_DUALMOUSE					0x00004000
#define MAIN_FLAG_DEBUGCOMPLETE				0x00008000
#define MAIN_FLAG_TESTERCALL				0x00010000
#define MAIN_FLAG_LEVELSOPEN				0x00020000
#define MAIN_FLAG_FORCETEXTUREMANAGEMENT	0x00040000
#define MAIN_FLAG_FORCEVERTEXFOG			0x00080000
#define MAIN_FLAG_REDUCESAMPLES				0x00100000
#define MAIN_FLAG_SHOWVERSION				0x00200000
#define MAIN_FLAG_REDUCEANIMATION			0x00400000
#define MAIN_FLAG_REDUCEPROMESHES			0x00800000
#define MAIN_FLAG_REDUCEFLICS				0x01000000
#define MAIN_FLAG_REDUCEIMAGES				0x02000000

enum
{
	WIREFRAME,
	UNLITFLATSHADE,
	FLATSHADE,
	GOURAUDSHADE
};

#pragma endregion

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

typedef struct Main_State
{
	/*0,4*/ MainStateInitialise Initialise;
	/*4,4*/ MainStateMainLoop MainLoop;
	/*8,4*/ MainStateShutdown Shutdown;
	/*c*/
} Main_State, *lpMain_State;
static_assert(sizeof(Main_State) == 0xc, "");


typedef struct Main_StateChangeData
{
	/*0,4*/ unsigned long origValue;
	/*4,4*/ BOOL changed;
	/*8*/
} Main_StateChangeData, *lpMain_StateChangeData;
static_assert(sizeof(Main_StateChangeData) == 0x8, "");


typedef struct Main_Globs
{
	/*000,4*/ HWND hWnd;
	/*004,4*/ HINSTANCE hInst;
	/*008,4*/ BOOL active;
	/*00c,4*/ BOOL exit;
	/*010,4*/ const char* className;
	/*014,100*/ char programName[256];
	/*114,4*/ LPDIRECT3DRM3 lpD3DRM;
	/*118,4*/ LPDIRECT3DRMDEVICE3 device;
	/*11c,4*/ LPDIRECT3DDEVICE3 imDevice;
	/*120,4*/ unsigned long fogMethod;
	/*124,4*/ unsigned long appWidth;
	/*128,4*/ unsigned long appHeight;
	/*12c,c*/ Main_State currState;
	/*138,4*/ BOOL stateSet;
	/*13c,4*/ float fixedFrameTiming;
	/*140,640*/ Main_StateChangeData renderStateData[MAIN_MAXRENDERSTATES];
	/*780,4*/ unsigned long style;
	/*784,4*/ unsigned long flags;
	/*788,4*/ unsigned long programmerLevel;
	/*78c,80*/ char startLevel[128];
	/*80c,80*/ char languageName[128];
	/*88c,4*/ unsigned long clFlags;
	/*890,4*/ HACCEL accels;
	/*894,4*/ MainWindowCallback windowCallback;
	/*898*/

} Main_Globs;
static_assert(sizeof(Main_Globs) == 0x898, "");

#pragma endregion

/**********************************************************************************
 ******** Globals
 **********************************************************************************/

#pragma region Globals

// <LegoRR.exe @00506800>
extern Main_Globs mainGlobs;

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

 // <LegoRR.exe @00401b30>
unsigned long Main_ProgrammerMode(void); // __inline unsigned long Main_ProgrammerMode(void) { return mainGlobs.programmerLevel; }

 // <LegoRR.exe @00401b40>
const char* Main_GetStartLevel(void); // __inline const char* Main_GetStartLevel(void) { return (mainGlobs.flags & MAIN_FLAG_STARTLEVEL) ? mainGlobs.startLevel : NULL; }

//__inline HWND Main_hWnd(VOID) { return mainGlobs.hWnd; }
//__inline HINSTANCE Main_hInst(VOID) { return mainGlobs.hInst; }

// <LegoRR.exe @00401b70>
int __cdecl appWidth(void); // __inline int appWidth(void) { return mainGlobs.appWidth; }

// <LegoRR.exe @00401b80>
int __cdecl appHeight(void); // __inline int appHeight(void) { return mainGlobs.appHeight; }


// <LegoRR.exe @00477a60>
int APIENTRY LegoRR_WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
							_In_ LPSTR     lpCmdLine, _In_     int       nCmdShow);

// <LegoRR.exe @00477e90>
void __cdecl Main_DisableTextureManagement(void);

// <LegoRR.exe @00477eb0>
void __cdecl Main_ParseCommandLine(const char* lpszCmdLine, OUT BOOL* nosound, OUT BOOL* insistOnCD);

// <LegoRR.exe @004781f0>
void __cdecl Main_LoopUpdate(BOOL clear);

// <LegoRR.exe @00478230>
unsigned long __cdecl Main_GetCLFlags(void);

// <LegoRR.exe @00478240>
unsigned long __cdecl Main_GetWindowsBitDepth(void);

// <LegoRR.exe @00478260>
void __cdecl Main_Finalise3D(void);

// <LegoRR.exe @00478290>
void __cdecl Main_SetState(Main_State* state);

// <LegoRR.exe @004782c0>
unsigned long __cdecl Main_GetTime(void);

// <LegoRR.exe @004782d0>
BOOL __cdecl Main_DispatchMessage(MSG* msg);

// <LegoRR.exe @00478300>
void __cdecl Main_HandleIO(void);

// <LegoRR.exe @00478370>
void __cdecl Main_SetupDisplay(BOOL fullScreen, unsigned long xPos, unsigned long yPos, unsigned long width, unsigned long height);

// <LegoRR.exe @00478490>
BOOL __cdecl Main_SetupDirect3D(const DirectDraw_Device* dev, IDirectDraw* ddraw1, IDirectDrawSurface4* backSurf, BOOL doubleBuffered);

// <LegoRR.exe @004785d0>
void __cdecl Main_AdjustWindowRect(IN OUT RECT* rect);

// <LegoRR.exe @004785f0>
void __cdecl Main_Setup3D(unsigned long renderQuality, BOOL dither, BOOL linearFilter, BOOL mipMap,
						BOOL mipMapLinear, BOOL blendTransparency, BOOL sortTransparency);

// <LegoRR.exe @00478690>
void __cdecl Main_SetTitle(const char* title);

// <LegoRR.exe @004786b0>
BOOL __cdecl Main_InitApp(HINSTANCE hInstance);

// <LegoRR.exe @00478780>
LRESULT __cdecl Main_WndProc_Fullscreen(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// <LegoRR.exe @00478980>
LRESULT __cdecl Main_WndProc_Windowed(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// <LegoRR.exe @00478b40>
LRESULT CALLBACK Main_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// <LegoRR.exe @00478b90>
void __cdecl Main_ChangeRenderState(D3DRENDERSTATETYPE dwRenderStateType, DWORD dwRenderState);

/// NOTE: newer engine version has argument: BOOL force, but LegoRR DOES NOT have this argument.
///        (it's possible this argument has been inlined, as it negates calling the entire function body.)
// <LegoRR.exe @00478c00>
void __cdecl Main_RestoreStates(void);

// <LegoRR.exe @00478c40>
BOOL __cdecl Main_SetCDVolume(float leftVolume, float rightVolume);

// <LegoRR.exe @00478c60>
BOOL __cdecl Main_GetCDVolume(OUT float* leftVolume, OUT float* rightVolume);

// <LegoRR.exe @00478c80>
BOOL __cdecl Main_CDVolume(IN OUT float* leftVolume, IN OUT float* rightVolume, BOOL set);

#pragma endregion

}
