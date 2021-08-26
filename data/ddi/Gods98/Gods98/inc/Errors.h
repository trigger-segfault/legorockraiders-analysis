
#ifndef _GODS98_ERRORS_H_
#define _GODS98_ERRORS_H_

#include "Standard.h"
#include "Files.h"

#define ERROR_LOADLOG			"Errors\\loadLog.dmp"
#define ERROR_LOADERRORLOG		"Errors\\loadErrorLog.dmp"
#define ERROR_REDUNDANTLOG		"Errors\\redundantFiles.dmp"

typedef enum Error_LoadErrorTAG
{
	Error_LoadError_InvalidFName,
	Error_LoadError_UnableToOpen,
	Error_LoadError_UnableToOpenForWrite,
	Error_LoadError_UnableToVerifyName,
	Error_LoadError_RMTexture,

	Error_LoadError_Count

};
/*
VOID Error_DebugBreak(VOID);
char *Error_Format(char *msg, ...);
VOID Error_Out(int ErrFatal, LPUCHAR lpOutputString, ...);
VOID Error_Initialise(VOID);
VOID Error_Shutdown(VOID);
BOOL Error_SetDumpFile(LPUCHAR fname);
VOID Error_TerminateProgram(LPUCHAR msg);
*/

#ifndef _GENPROTFILE
#include "..\Src\Errors.prot"
#endif // _GENPROTFILE


#ifdef _cplusplus
extern "C" {
#endif // _cplusplus

typedef struct Error_Globs {

	lpFile dumpFile, loadLogFile, loadErrorLogFile, redundantLogFile;
	UCHAR loadLogName[1024], redundantLogName[1024];
	BOOL warnCalled;
	BOOL fullScreen;
	
} Error_Globs, *lpError_Globs;


//#ifdef _DEBUG

#ifndef _RELEASE

#define Error_Warn(b,s)						{ if (b) { Error_Out(FALSE, "%s(%i): Warning: %s\n", __FILE__, __LINE__, (s)); Error_SetWarn(); } }
#define Error_Fatal(b,s)					{ if (b) { Error_Out(TRUE, "%s(%i): Fatal: %s\n", __FILE__, __LINE__, (s)); } }
#define Error_Debug(s)						Error_Out(FALSE, "%s", (s))
#define Error_LogLoad(b,s)					{ Error_Log( errorGlobs.loadLogFile, (b), "%s\n", (s) ); }
#define Error_LogLoadError(b,s)				{ Error_Log( errorGlobs.loadErrorLogFile, (b), "%s\n", (s) ); }
#define Error_LogRedundantFile(b,s)			{ Error_Log( errorGlobs.redundantLogFile, (b), "%s\n", (s) ); }

__inline VOID Error_SetWarn(VOID)			{ extern Error_Globs errorGlobs; errorGlobs.warnCalled = TRUE; }
__inline VOID Error_CheckWarn(BOOL check)	{ extern Error_Globs errorGlobs; if (!check) errorGlobs.warnCalled = FALSE; else if (errorGlobs.warnCalled) Error_TerminateProgram("Check warning message log"); }

#else 

#define Error_Warn(b,s)			(b)
#define Error_Fatal(b,s)		(b)
#define Error_Debug(s)
__inline VOID Error_CheckWarn(BOOL check)	{  }
#define Error_LogLoad(b,s)					(b)
#define Error_LogLoadError(b,s)				(b)
#define Error_LogRedundantFile(b,s)			(b)

/*
#define Error_Warn(b,s)

#ifdef _RELEASE
#define Error_Fatal(b,s)					
#else // _RELEASE
#define Error_Fatal(b,s)					{ if (b) { if (errorGlobs.fullScreen) exit(0); else Error_DebugBreak(); } }
#endif // _RELEASE

#define Error_Debug(s)
__inline VOID Error_CheckWarn(BOOL check)	{  }
#define Error_LogLoad(b,s)
#define Error_LogLoadError(b,s)
#define Error_LogRedundantFile(b,s)
*/

#endif // !_RELEASE

#ifdef _cplusplus
extern "C" {
#endif // _cplusplus


extern Error_Globs errorGlobs;

#endif // _GODS98_ERRORS_H_
