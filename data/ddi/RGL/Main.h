
#ifndef _RGL_MAIN_H_
#define _RGL_MAIN_H_

#define MAIN_MAXARGS			20

#define MAIN_FLAG_EMULATIONMODE		0x00000001
#define MAIN_FLAG_RESIZABLE			0x00000002
#define MAIN_FLAG_NOSOUND			0x00000004
#define MAIN_FLAG_DISABLEALTF4		0x00000008
#define MAIN_FLAG_USERMASK			0x0000ffff
#define MAIN_FLAG_EXIT				0x10000000
#define MAIN_FLAG_MINIMIZED			0x20000000
#define MAIN_FLAG_CENTERWINDOW		0x40000000
#define MAIN_FLAG_REGISTER			0x80000000

enum MainErrorType {

	MainErrorType_InvalidPixelFormat,
	MainErrorType_SoundInitialise,

	MainErrorType_Count
};

struct MainSelectModeData {

	BOOL fullScreen;
	ULONG driverIndex, deviceIndex;
	ULONG width, height, depth;
};

typedef struct MainSelectModeData		*lpMainSelectModeData;

extern void Game_Register(void);
//extern int Game_SelectMode(struct MainSelectModeData *data);
//extern void Game_Initialise(void);
//extern int Game_Loop_Old(float delta);
//extern void Game_Shutdown(void);

#ifndef _AUTOPROTOTYPES
// Auto Prototypes
extern unsigned __int64 __stdcall Int64ShllMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern __int64 __stdcall Int64ShraMod32(__int64 Value,unsigned long ShiftCount);
extern unsigned __int64 __stdcall Int64ShrlMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern void *__cdecl GetFiberData(void );
extern void *__cdecl GetCurrentFiber(void );
extern float __cdecl LWO_REAL(unsigned long n);
extern void __cdecl Main_ReportError(unsigned long type);
extern VOID __cdecl Main_SetFlags(ULONG flags, BOOL set);
extern struct HWND__ *__cdecl Main_hWnd(void );
extern struct HINSTANCE__ *__cdecl Main_hInstance(void );
extern int __cdecl Main_AppActive(void);
extern void __cdecl Main_ShowWindow(int on);
extern int __stdcall WinMain(struct HINSTANCE__ *hInstance,struct HINSTANCE__ *hPrevInstance,char *lpCmdLine,int nCmdShow);
extern void __cdecl Main_ProcessArguments(unsigned long argc,unsigned char **argv );
extern void __cdecl Main_Update(REAL delta);
extern void __cdecl Main_Sleep(unsigned long time);
extern void __cdecl Main_SetupName(unsigned char *cmdLine);
extern int __cdecl Main_InitWindow(struct HINSTANCE__ *hInstance,unsigned char *title,int nCmdShow);
extern void __cdecl Main_SetTitle(unsigned char *title);
extern void __cdecl Main_SetWindowSize(unsigned long width,unsigned long height,int fullscreen);
extern void __cdecl Main_HandleResize(unsigned int wParam,long lParam);
extern void __cdecl Main_HandleMove(unsigned int wParam,long lParam);
extern void __cdecl Main_HandleKey(unsigned int wParam,long lParam);
extern long __stdcall Main_WndProc(struct HWND__ *hWnd,unsigned int message,unsigned int wParam,long lParam);
extern void __cdecl Main_HandleMouseMove(unsigned int wParam, long lParam);
extern void __cdecl Main_HandleLeftButtonDown(unsigned int wParam, long lParam);
extern void __cdecl Main_HandleLeftButtonUp(unsigned int wParam, long lParam);
extern void __cdecl Main_HandleRightButtonDown(unsigned int wParam, long lParam);
extern void __cdecl Main_HandleRightButtonUp(unsigned int wParam, long lParam);
extern VOID __cdecl Main_SetSelectModeFunction(BOOL (*funcSelectMode)(struct MainSelectModeData *data));
extern VOID __cdecl Main_SetReportErrorFunction(BOOL (*funcReportError)(enum MainErrorType type));
extern VOID __cdecl Main_SetFlipCallback(VOID (*flipCallback)(REAL delta, LPVOID data), LPVOID data);
extern VOID __cdecl Main_Abort(VOID);
// Auto Prototypes
#endif // !_AUTOPROTOTYPES

#endif // !_RGL_MAIN_H_
