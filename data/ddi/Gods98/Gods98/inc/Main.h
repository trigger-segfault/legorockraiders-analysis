
#ifndef _GODS98_MAIN_H_
#define _GODS98_MAIN_H_

#include "Standard.h"

#include "windows.h"

#define MAIN_MAXRENDERSTATES				200

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

enum {
	WIREFRAME,
	UNLITFLATSHADE,
	FLATSHADE,
	GOURAUDSHADE
};

typedef struct Main_State {

	BOOL (*Initialise)(VOID);
	BOOL (*MainLoop)(REAL elapsedTime);
	VOID (*Shutdown)(VOID);

} Main_State, *lpMain_State;

typedef struct Main_StateChangeData {

	ULONG origValue;
	BOOL changed;

} Main_StateChangeData, *lpMain_StateChangeData;

#ifndef _GODS98COMPILE

typedef LPVOID	LPDIRECT3DRM3;
typedef LPVOID	LPDIRECT3DRMDEVICE3;
typedef LPVOID	LPDIRECT3DDEVICE3;

#endif // _GODS98COMPILE

typedef struct Main_Globs {

	HWND hWnd;
	HINSTANCE hInst;
	BOOL active, exit;
	LPUCHAR className;

	UCHAR programName[256];

	LPDIRECT3DRM3 lpD3DRM;
	LPDIRECT3DRMDEVICE3 device;
	LPDIRECT3DDEVICE3 imDevice;

	ULONG fogMethod;

	ULONG appWidth, appHeight;

	Main_State currState;
	BOOL stateSet;

	REAL fixedFrameTiming;

	Main_StateChangeData renderStateData[MAIN_MAXRENDERSTATES];

	ULONG style;

	ULONG flags;
	ULONG programmerLevel;
	UCHAR startLevel[128];
	UCHAR languageName[128];

	ULONG clFlags;

	HACCEL	accels;
	void(*windowCallback)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


} Main_Globs, *lpMain_Globs;

extern Main_Globs mainGlobs;

#ifdef _GODS98COMPILE

__inline LPDIRECT3DRM3 lpD3DRM()				{ return mainGlobs.lpD3DRM; }
__inline LPDIRECT3DRMDEVICE3 lpDevice()			{ return mainGlobs.device; }
__inline LPDIRECT3DDEVICE3 lpIMDevice()			{ return mainGlobs.imDevice; }
__inline BOOL Main_VideoTexture()				{ return mainGlobs.flags & MAIN_FLAG_VIDEOTEXTURE; }
__inline BOOL Main_MIPMapEnabled()				{ return mainGlobs.flags & MAIN_FLAG_MIPMAPENABLED; }
__inline BOOL Main_FullScreen()					{ return mainGlobs.flags & MAIN_FLAG_FULLSCREEN; }
__inline ULONG Main_GetFogMethod()				{ return mainGlobs.fogMethod; }
__inline VOID Main_SetFogMethod(ULONG m)		{ mainGlobs.fogMethod = m; }

#endif // _GODS98COMPILE

__inline ULONG Main_ProgrammerMode(VOID)		{ return mainGlobs.programmerLevel; }
__inline LPUCHAR Main_GetStartLevel(VOID)		{ return (mainGlobs.flags & MAIN_FLAG_STARTLEVEL)?mainGlobs.startLevel:NULL; }

__inline HWND Main_hWnd(VOID)				{ return mainGlobs.hWnd; }
__inline HINSTANCE Main_hInst(VOID)			{ return mainGlobs.hInst; }

__inline int appWidth(VOID)				{ return mainGlobs.appWidth; }
__inline int appHeight(VOID)			{ return mainGlobs.appHeight; }

extern int __stdcall WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,char *lpszCmdLine,int cmdShow);
extern int __cdecl Main_SetState(struct Main_State *state);
extern void __cdecl Main_SetFixedFrameTiming(float time);
extern void __cdecl Main_HandleIO(void );
extern unsigned long Main_GetCLFlags(void );
extern unsigned long __cdecl Main_GetWindowsBitDepth(void );
extern void __cdecl Main_LoopUpdate(BOOL clear);
extern void __cdecl Main_Finalise3D(void );
extern void __cdecl Main_SetupDisplay(int fullScreen,unsigned long xPos,unsigned long yPos,unsigned long width,unsigned long height);
extern int __cdecl Main_SetupDirect3D(struct DirectDraw_Device *dev,struct IDirectDraw *ddraw1,struct IDirectDrawSurface4 *backSurf,int doubleBuffered);
extern void __cdecl Main_AdjustWindowRect(struct tagRECT *rect);
extern void __cdecl Main_Setup3D(unsigned long renderQuality,int dither,int linearFilter,int mipMap,int mipMapLinear,int blendTransparency,int sortTransparency);
extern unsigned long __cdecl Main_GetTime(void );
extern void __cdecl Main_SetTitle(unsigned char *title);
extern ULONG __cdecl Main_GetTrianglesDrawn(BOOL total);
static int __cdecl Main_InitApp(void *hInstance);
extern void __cdecl Main_Render(void );
extern long __stdcall Main_WndProc(void *hWnd,unsigned int message,unsigned int wParam,long lParam);
extern void __cdecl Main_PauseApp(BOOL pause);
extern BOOL __cdecl Main_IsPaused(void);
extern LPUCHAR Main_GetLanguage(VOID);
extern BOOL Main_DumpUnknownPhrases(VOID);
__inline BOOL Main_AppActive()			{ return mainGlobs.active; }
__inline ULONG Main_GetFlags()			{ return mainGlobs.flags; }
extern VOID __cdecl Main_DisableTextureManagement(VOID);
extern BOOL __cdecl Main_SetCDVolume(REAL leftVolume, REAL rightVolume);
extern BOOL __cdecl Main_GetCDVolume(LPREAL leftVolume, LPREAL rightVolume);
extern BOOL __cdecl Main_CDVolume(LPREAL leftVolume, LPREAL rightVolume, BOOL set);
extern VOID __cdecl Main_Exit(VOID);
extern void __cdecl Main_SetWindowCallback(  void(*callback)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) );
extern void __cdecl Main_SetAccel(HACCEL accels);


/*
#ifdef _TESTCODE
extern VOID __cdecl Main_ResetClockRatio(VOID);
extern REAL __cdecl Main_GetClockRatio(VOID);
#endif // _TESTCODE
*/

#ifdef _GODS98COMPILE
VOID Main_ChangeRenderState(D3DRENDERSTATETYPE dwRenderStateType, DWORD dwRenderState);
VOID Main_RestoreStates(BOOL force);
#endif //_GODS98COMPILE

#endif // _GODS98_MAIN_H_
