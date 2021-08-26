
#include <process.h>
#include <ddraw.h>

#include "..\inc\Standard.h"
#include "..\inc\Errors.h"
#include "..\inc\DirectDraw.h"
#include "..\inc\Files.h"
#include "..\inc\Config.h"
#include "windows.h"

Error_Globs errorGlobs;
	
/*
    Implementation of Win95 tracing facility to mimic that of NT
*/

VOID Error_Initialise() {

	errorGlobs.dumpFile = NULL;
	errorGlobs.loadLogFile = NULL;
	errorGlobs.loadErrorLogFile = NULL;
	errorGlobs.redundantLogFile = NULL;

	errorGlobs.fullScreen = FALSE;
}

VOID Error_FullScreen(BOOL on) {

	errorGlobs.fullScreen = on;
}

VOID Error_CloseLog(VOID) {

	if (errorGlobs.dumpFile) File_Close(errorGlobs.dumpFile);
	if (errorGlobs.loadLogFile) File_Close(errorGlobs.loadLogFile);
	if (errorGlobs.loadErrorLogFile) File_Close(errorGlobs.loadErrorLogFile);

	errorGlobs.dumpFile = errorGlobs.loadLogFile = errorGlobs.loadErrorLogFile = NULL;
}

VOID Error_Shutdown(VOID) {

	Error_CloseLog();
			   
	if( errorGlobs.redundantLogFile = File_Open(errorGlobs.redundantLogName, "w") )
	{	File_CheckRedundantFiles( errorGlobs.loadLogName );

		File_Close(errorGlobs.redundantLogFile);
	}

}

BOOL Error_SetDumpFile(LPUCHAR errors, LPUCHAR loadLog, LPUCHAR loadErrorLog, LPUCHAR rendundantLog ){

	BOOL ok = TRUE;


	if( loadLog )
		if( !(errorGlobs.loadLogFile = File_Open(loadLog, "w")) )
			ok = FALSE;
		else
			strcpy( errorGlobs.loadLogName, loadLog );

	if( loadErrorLog )
		if( !(errorGlobs.loadErrorLogFile = File_Open(loadErrorLog, "w")) )
		{	ok = FALSE;
		}
		else
			Error_LogLoadError( TRUE, "<ErrorNum>[0=InvalidFName,1=UnableToOpen,2=UnableToOpenForWrite,3=UnableToVerifyName4=TextureError] <File>" );

	if( errors )
		if( !(errorGlobs.dumpFile = File_Open(errors, "w")) )
			ok = FALSE;
	
	if( rendundantLog )
		strcpy( errorGlobs.redundantLogName, rendundantLog );

/*	if( !errorGlobs.loadLogFile )
		if( !(errorGlobs.loadLogFile = File_Open(ERROR_LOADLOG, "w")) )
			ok = FALSE;

	if( !errorGlobs.loadErrorLogFile )
		if( !(errorGlobs.loadErrorLogFile = File_Open(ERROR_LOADERRORLOG, "w")) )
		{	ok = FALSE;
		}
		else
			Error_LogLoadError( TRUE, "<ErrorNum>[0=UnableToOpen,1=InvalidFName,2=TextureError] <File>" );
*/


	return ok;
}

VOID Error_DebugBreak(VOID){

	if (IDOK == MessageBox(NULL, "Error_DebugBreak() called\nCrash to debugger?", "Debugger", MB_OKCANCEL)){
		DebugBreak();
	}
}

VOID Error_TerminateProgram(LPUCHAR msg)
{
	// Call exit 0.  Should probably terminate properly and clean everything up.
#ifndef _RELEASE
	if (!DirectDraw_FullScreen()) {

		UCHAR message[1024];
		int r;
		sprintf(message, "Error:\n%s\nLast entry read from config: \"%s\"\n\nSelect Retry to crash to debugger", msg, Config_Debug_GetLastFind());

		ShowCursor(TRUE);

		r = MessageBox(NULL, message, "Debugger", MB_ABORTRETRYIGNORE);
		if (IDRETRY == r) DebugBreak();
		else if (IDIGNORE == r) return;
	}
#endif // !_RELEASE

	Error_Shutdown();
	exit(0);
}

char *Error_Format(char *msg, ...){

	static char res[1024];
	va_list args;

	va_start(args, msg);
	vsprintf(res, msg, args);
	va_end(args);

	return res;
}

void Error_Out(int ErrFatal, STRING lpOutputString, ...)
{

	if (errorGlobs.dumpFile) {

		va_list args;
		UCHAR msg[512];
		va_start(args, lpOutputString);
		File_VPrintF(errorGlobs.dumpFile, lpOutputString, args);
		vsprintf(msg, lpOutputString, args);
		va_end(args);
		File_Flush(errorGlobs.dumpFile);
		if (ErrFatal) Error_TerminateProgram(msg);

	} else {
		
		
		HANDLE heventDBWIN;  /* DBWIN32 synchronization object */
		HANDLE heventData;   /* data passing synch object */
		HANDLE hSharedFile;  /* memory mapped file shared data */
		LPSTR lpszSharedMem;
		char achBuffer[500];
		
		/* create the output buffer */
		va_list args;
		va_start(args, lpOutputString);
		vsprintf(achBuffer, lpOutputString, args);
		va_end(args);
		
		/* 
        Do a regular OutputDebugString so that the output is 
        still seen in the debugger window if it exists.
		
		  This ifdef is necessary to avoid infinite recursion 
		  from the inclusion of W95TRACE.H
		*/
#ifdef _cplusplus
#ifdef _UNICODE
		::OutputDebugStringW(achBuffer);
#else
		::OutputDebugStringA(achBuffer);
#endif
#else
#ifdef _UNICODE
		OutputDebugStringW(achBuffer);
#else
		OutputDebugStringA(achBuffer);
#endif
#endif
		
		/* bail if it's not Win95 */
		{
			OSVERSIONINFO VerInfo;
			VerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
			GetVersionEx(&VerInfo);
			if ( VerInfo.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS )
			{
				if (ErrFatal) Error_TerminateProgram(achBuffer);
				return;
			}
		}
		
		/* make sure DBWIN is open and waiting */
		heventDBWIN = OpenEvent(EVENT_MODIFY_STATE, FALSE, "DBWIN_BUFFER_READY");
		if ( !heventDBWIN )
		{
			//MessageBox(NULL, "DBWIN_BUFFER_READY nonexistent", NULL, MB_OK);
			if (ErrFatal) Error_TerminateProgram(achBuffer);
			return;            
		}
		
		/* get a handle to the data synch object */
		heventData = OpenEvent(EVENT_MODIFY_STATE, FALSE, "DBWIN_DATA_READY");
		if ( !heventData )
		{
			// MessageBox(NULL, "DBWIN_DATA_READY nonexistent", NULL, MB_OK);
			CloseHandle(heventDBWIN);
			if (ErrFatal) Error_TerminateProgram(achBuffer);
			return;            
		}
		
		hSharedFile = CreateFileMapping((HANDLE)-1, NULL, PAGE_READWRITE, 0, 4096, "DBWIN_BUFFER");
		if (!hSharedFile) 
		{
			//MessageBox(NULL, "DebugTrace: Unable to create file mapping object DBWIN_BUFFER", "Error", MB_OK);
			CloseHandle(heventDBWIN);
			CloseHandle(heventData);
			if (ErrFatal) Error_TerminateProgram(achBuffer);
			return;
		}
		
		lpszSharedMem = (LPSTR)MapViewOfFile(hSharedFile, FILE_MAP_WRITE, 0, 0, 512);
		if (!lpszSharedMem) 
		{
			//MessageBox(NULL, "DebugTrace: Unable to map shared memory", "Error", MB_OK);
			CloseHandle(heventDBWIN);
			CloseHandle(heventData);
			if (ErrFatal) Error_TerminateProgram(achBuffer);
			return;
		}
		
		/* wait for buffer event */
		WaitForSingleObject(heventDBWIN, INFINITE);
		
		/* write it to the shared memory */
		*((LPDWORD)lpszSharedMem) = _getpid();
		wsprintf(lpszSharedMem + sizeof(DWORD), "%s", achBuffer);
		
		/* signal data ready event */
		SetEvent(heventData);
		
		/* clean up handles */
		CloseHandle(hSharedFile);
		CloseHandle(heventData);
		CloseHandle(heventDBWIN);

		if (ErrFatal) Error_TerminateProgram(achBuffer);
	}
}

VOID Error_Log( lpFile logFile, BOOL log, STRING lpOutputString, ...)
{
	if( log )
	{
		if( logFile )
		{	va_list args;
			UCHAR msg[512];


			va_start(args, lpOutputString);
			File_VPrintF(logFile, lpOutputString, args);
			vsprintf(msg, lpOutputString, args);
			va_end(args);
			File_Flush(logFile);

		}

	}
}