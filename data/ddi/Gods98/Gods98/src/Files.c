#define _DO_NOT_DEFINE_ANSI_TO_INTERNAL_FILE_SYSTEM

#include <direct.h>
#include <stdio.h>
#include <io.h>
#include <windows.h>
#include <sys\stat.h>

#include "..\inc\Standard.h"

#include "..\inc\Registry.h"
#include "..\inc\Errors.h"
#include "..\inc\Memory.h"
#include "..\inc\Utils.h"
#include "..\inc\Files.h"
#include "..\inc\wad.h"

static BOOL File_FindDataCD(VOID);

File_Globs fileGlobs = { 0 };

SLONG File_Rename(LPUCHAR oldName, LPUCHAR newName) {

	LPUCHAR on = Util_StrCpy(File_VerifyFilename(oldName));
	LPUCHAR nn = Util_StrCpy(File_VerifyFilename(newName));
	SLONG result = rename(on, nn);

	Mem_Free(on);
	Mem_Free(nn);

	return result;
}

SLONG File_Delete(LPUCHAR fname) {

	return remove(File_VerifyFilename(fname));
}

VOID File_Initialise(LPUCHAR programName, BOOL insistOnCD, LPUCHAR registryLocation) {

	SLONG wad = WAD_ERROR;
	BOOL foundCD = FALSE;
	BOOL foundWad = FALSE;
	UCHAR cwd[_MAX_PATH];
	FILE *fp;
	UCHAR fname[1024];
	BOOL failed = FALSE;

	_getcwd(cwd, _MAX_PATH);
	if ('\\' == cwd[strlen(cwd)-1]) cwd[strlen(cwd)-1] = '\0';
	sprintf(fileGlobs.dataDir, "%s\\%s", cwd, FILE_DATADIRNAME);
	sprintf(fileGlobs.exeDir, "%s", cwd);

#ifdef _GODS98_USEWAD_
	{
		UCHAR wadFile[FILE_MAXPATH];
		UCHAR cwd[FILE_MAXPATH];
		ULONG i;
		for (i=0; i<MAX_WADS; i++) {
			sprintf(wadFile, "%s%i.wad", programName, i);
			wad = File_LoadWad(wadFile);
			if (wad == WAD_ERROR) {
				Error_Warn(TRUE, Error_Format("Cannot load %s", wadFile));
			} else {
//				File_SetActiveWad(wad);
				foundWad = TRUE;
			}
		}
		_getcwd(cwd, FILE_MAXPATH);
		strcat(cwd, "\\Data");
		File_SetBaseSearchPath(cwd);
	}
#endif // _GODS98_USEWAD_


	while (FALSE == (foundCD = File_FindDataCD()) && insistOnCD) {

		UCHAR msgNoCD[1024], msgError[1024] = "Error";

		if (Registry_GetValue(registryLocation, "CDMissing", REGISTRY_STRING_VALUE, msgNoCD, 1024)) {
			Registry_GetValue(registryLocation, "SetupError", REGISTRY_STRING_VALUE, msgError, 1024);

			if (IDCANCEL == MessageBox(NULL, msgNoCD, msgError, MB_OKCANCEL)) exit(0);

		} else exit(0);
	}

	if (!foundCD) {
		if (!foundWad) {					// Assume that if a wad is found then it is the correct one.

			struct _finddata_t findData;
			ULONG handle;

			failed = TRUE;

			if (-1 != (handle = _findfirst("*.*", &findData))) {
				do {
					if (findData.attrib & _A_SUBDIR) {
						if (0 == stricmp(findData.name, FILE_DATADIRNAME)) {
							failed = FALSE;
							break;
						}
					}
				} while (0 == _findnext(handle, &findData));

				_findclose(handle);
			}
		}
	}

	if (insistOnCD) {
		sprintf(fname, "%s\\%s", FILE_DATADIRNAME, FILE_KEYFILENAME);
		if (fp = fopen(fname, "r")) {
			fclose(fp);
			failed = TRUE;
		}
	}

	if (!failed) {

		// If everything started up ok (CD in or WAD found), then ensure the data directory exists...
		_mkdir(FILE_DATADIRNAME);

		// Remove the 'delme' file if it exists...
		sprintf(fname, "%s\\%s", FILE_DATADIRNAME, FILE_DELMEFILENAME);
		
		if (fp = fopen(fname, "r")) {
			fclose(fp);
			_chmod(fname, _S_IWRITE);
			remove(fname);
		}

	} else {

		UCHAR msgNoData[1024], msgError[1024] = "Error";

		if (Registry_GetValue(registryLocation, "DataMissing", REGISTRY_STRING_VALUE, msgNoData, 1024)) {
			Registry_GetValue(registryLocation, "SetupError", REGISTRY_STRING_VALUE, msgError, 1024);
			MessageBox(NULL, msgNoData, msgError, MB_OK);
		}
		exit(0);
	}

}

static BOOL File_FindDataCD(VOID) {

	UCHAR drive[] = "A:\\", letter;
	UCHAR fname[FILE_MAXPATH];
	FILE *fp;

	for (letter='C' ; letter<='Z' ; letter++) {
		drive[0] = letter;
		if (DRIVE_CDROM == GetDriveType(drive)) {
			sprintf(fname, "%c:\\%s\\%s", letter, FILE_DATADIRNAME, FILE_KEYFILENAME);
			if (fp = fopen(fname, "r")) {
				fclose(fp);
				fileGlobs.cdLetter = letter;
				return TRUE;
			}
		}
	}
	return FALSE;
}

#ifdef _GODS98_USEWAD_

/////////////////////////////////////////////////////////////////////
// File through which ALL file operations must take place.
#include <stdarg.h>						// var args
#include <stdio.h>						// File ops
#include <windows.h>					// BOOL/HANDLE declarations
#include <direct.h>

#include "..\inc\wad.h"						// Wad files

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

static int currWadHandle = WAD_ERROR;	// Current wad handle.  All fopens are relative to this wad.

// Stats about file ops.
struct 
{
	int numWad, numStd;					// Number of files opened as wad/stdc
	int numOpened, numClosed;			// Total number of files opened/closed
	int currOpen;						// number of currently opened files
} fileStats;

#define MAX_WAD_BASE_PATH 1024
static char wadBasePath[MAX_WAD_BASE_PATH];
static BOOL basePathSet = FALSE;
static BOOL fileLogFileAccess = FALSE;

void File_LogFileAccess(BOOL mode)
{
	fileLogFileAccess = mode;
}

#ifdef _DEBUG
void File_ErrorFile(char *msg, ...)
{
	static FILE *f;
	va_list arg;

	if (fileLogFileAccess)
	{
		va_start(arg, msg);
		if (f)
		{
			if (msg) vfprintf(f, msg, arg);
			else
			{
				fclose(f);
				f = 0;
			}
		}
		else if (!msg) 
		{
			f = fopen("file.log", "w");
			fprintf(f, "File access log\n");
		}
		va_end(arg);
	}
}
#else
void File_ErrorFile(char *msg, ...)
{
}
#endif

// This allows the translation from File paths into Wad names.
BOOL File_SetBaseSearchPath(char *basePath)
{
	int len;
	if (!basePath || (len = strlen(basePath)) > MAX_WAD_BASE_PATH || !len) 
	{
		memset(wadBasePath, 0, MAX_WAD_BASE_PATH);
		basePathSet = FALSE;
		return FALSE;
	}
	else
	{
		strcpy(wadBasePath, basePath);
		basePathSet = TRUE;
		return TRUE;
	}
}

void File_Error(char *msg, ...)
{
	va_list args;
	char buff[1024];
	va_start(args, msg);
	vsprintf(buff, msg, args);
	////////////////////////
	OutputDebugString(buff);//CHANGE TO WHATEVER IS SUITABLE
	////////////////////////
	va_end(args);
}

int File_LoadWad(char *fName)
{
	File_ErrorFile(0);			// Open the wad error log
	return Wad_Load(fName);
}

void File_CloseWad(int hWad)
{
	File_ErrorFile(0);			// Close the wad error log
	if (hWad == WAD_ERROR) Wad_Close(hWad);
}

void File_SetActiveWad(int hWad)
{
	currWadHandle = hWad;
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

BOOL File_GetCDFilePath(LPUCHAR path, LPUCHAR fname) {

	if ('\0' != fileGlobs.cdLetter) {
		sprintf(path, "%c:\\%s\\%s", fileGlobs.cdLetter, FILE_DATADIRNAME, fname);
		return TRUE;
	}

	return FALSE;
}

VOID File_MakeDir(LPUCHAR path) {

	LPUCHAR s;
	UCHAR name[FILE_MAXPATH];

	sprintf(name, "%s\\%s", FILE_DATADIRNAME, path);

	for (s=name ; '\0'!=*s ; s++) {
		if ('\\' == *s) {
			*s = '\0';
			mkdir(name);
			*s = '\\';
		}
	}
}

lpFile File_Open(char *fName, char *mode) 
{
	LPUCHAR fullName = File_VerifyFilename(fName);
	FileSys fs = _File_CheckSystem(fullName, mode);
	lpFile file;

	switch (fs)
	{
	
	case FileSystem_Std:
		file = _File_Alloc(fs); if (!file) return 0;
		file->std = fopen(fullName, mode);
		if (file->std)
		{
			File_ErrorFile("STD Load %s\n", fullName);
			return file;
		}
		else 
		{
			if (NULL == Util_StrIStr(mode, "w")) {
				UCHAR cdName[FILE_MAXPATH];
				if (File_GetCDFilePath(cdName, fName)) {
					if (file->std = fopen(cdName, mode)) return file;
				}
			}
	
			File_ErrorFile("STD Fail %s\n", fullName);
			_File_Dealloc(file);
			return 0;
		}
		break;
	
	case FileSystem_Wad:
		file = _File_Alloc(fs); if (!file) return 0;
		if (_File_OpenWad(file->wad, _File_GetWadName(fullName)) != FALSE) 
		{
			File_ErrorFile("WAD Load %s\n", _File_GetWadName(fullName));
			return file;
		}
		else
		{
			File_ErrorFile("WAD Fail %s\n", _File_GetWadName(fullName));
			_File_Dealloc(file);
			return 0;
		}
		break;
	
	case FileSystem_Err:
	default:
		File_Error("%s(%i) : Error in call to %s\n", __FILE__, __LINE__, "File_Open");
		break;
	}
	return 0;
}

int File_Seek(lpFile f, int pos, int mode) 
{
	FileSys fs = _File_GetSystem(f);
	switch (fs)
	{
	case FileSystem_Std:
		return fseek(StdFile(f), pos, mode);
		break;
	case FileSystem_Wad:
		switch (mode)
		{
		case SEEK_SET:
			WadFile(f)->streamPos = pos;
			if (WadFile(f)->streamPos > Wad_hLength(WadFile(f)->hFile))
				WadFile(f)->streamPos = Wad_hLength(WadFile(f)->hFile);
			if (WadFile(f)->streamPos < 0) WadFile(f)->streamPos = 0;
			break;
		case SEEK_CUR:
			WadFile(f)->streamPos += pos;
			if (WadFile(f)->streamPos > Wad_hLength(WadFile(f)->hFile))
				WadFile(f)->streamPos = Wad_hLength(WadFile(f)->hFile);
			if (WadFile(f)->streamPos < 0) WadFile(f)->streamPos = 0;
			break;
		case SEEK_END:
			WadFile(f)->streamPos = Wad_hLength(WadFile(f)->hFile) + pos;
			break;
		default:
			File_Error("Uknown seek mode (%i)", mode);
		}
		break;
	case FileSystem_Err:
	default:
		File_Error("%s(%i) : Unknown file system in call to %s", __FILE__, __LINE__, "File_Seek");
		break;
	}
	return 0;
}

int File_Read(void *buffer, int size, int count, lpFile f) 
{
	FileSys fs = _File_GetSystem(f);
	switch (fs)
	{
	case FileSystem_Std:
		return fread(buffer, size, count, StdFile(f));
		break;
	case FileSystem_Wad:
		{
			int len = Wad_hLength(WadFile(f)->hFile);
			int amountToCopy;
			if ((WadFile(f)->streamPos + (size*count)) > len) amountToCopy = len - WadFile(f)->streamPos;
			else amountToCopy = size * count;
			memcpy(buffer, (char*)Wad_hData(WadFile(f)->hFile) + WadFile(f)->streamPos, amountToCopy);
			WadFile(f)->streamPos += amountToCopy;
			return amountToCopy / size;
		}
		break;
	case FileSystem_Err:
	default:
		File_Error("%s(%i) : Unknown file system in call to %s", __FILE__, __LINE__, "");
		break;
	}
	return 0;
}

int File_Write(void *buffer, int size, int count, lpFile f) 
{
	FileSys fs = _File_GetSystem(f);
	switch (fs)
	{
	case FileSystem_Std:
		return fwrite(buffer, size, count, StdFile(f));
		break;
	case FileSystem_Wad:
		File_Error("Cannot write to a file stored in a Wad!");
		break;
	case FileSystem_Err:
	default:
		File_Error("%s(%i) : Unknown file system in call to %s", __FILE__, __LINE__, "File_Write");
		break;
	}
	return 0;
}

int File_Close(lpFile f) 
{
	FileSys fs = _File_GetSystem(f);
	switch (fs)
	{
	case FileSystem_Std:
	case FileSystem_Wad:
		_File_Dealloc(f);
		break;
	case FileSystem_Err:
	default:
		File_Error("%s(%i) : Unknown file system in call to %s", __FILE__, __LINE__, "File_Close");
		break;
	}
	return 0;
}

int File_EOF(lpFile f)
{
	FileSys fs = _File_GetSystem(f);
	switch (fs)
	{
	case FileSystem_Std:
		return feof(StdFile(f));
		break;
	case FileSystem_Wad:
		return WadFile(f)->streamPos >= Wad_hLength(WadFile(f)->hFile)-1 ? 1 : 0;
		break;
	case FileSystem_Err:
	default:
		File_Error("%s(%i) : Unknown file system in call to %s", __FILE__, __LINE__, "File_EOF");
		break;
	}
	return 0;
}

int File_Tell(lpFile f) 
{
	FileSys fs = _File_GetSystem(f);
	switch (fs)
	{
	case FileSystem_Std:
		return ftell(StdFile(f));
		break;
	case FileSystem_Wad:
		return WadFile(f)->streamPos;
		break;
	case FileSystem_Err:
	default:
		File_Error("%s(%i) : Unknown file system in call to %s", __FILE__, __LINE__, "File_Tell");
		break;
	}
	return 0;
}

int File_Flush(lpFile f) 
{
	FileSys fs = _File_GetSystem(f);
	switch (fs)
	{
	case FileSystem_Std:
		return fflush(StdFile(f));
		break;
	case FileSystem_Wad:
		return 0;
		break;
	case FileSystem_Err:
	default:
		File_Error("%s(%i) : Unknown file system in call to %s", __FILE__, __LINE__, "File_Flush");
		break;
	}
	return 0;
}

BOOL File_Exists(char *fName) 
{
	LPUCHAR fullName = File_VerifyFilename(fName);
	FileSys fs = _File_CheckSystem(fullName, "r");
	if (fs == FileSystem_Std)
	{
		FILE *f;
		f = fopen(fullName, "r");
		if (f)
		{
			fclose(f);
			return TRUE;
		} else {
			UCHAR cdName[FILE_MAXPATH];
			if (File_GetCDFilePath(cdName, fName)) {
				if (f = fopen(cdName, "r")) {
					fclose(f);
					return TRUE;
				}
			}
			return FALSE;
		}
	}
	else if (fs == FileSystem_Wad) 
	{
		return Wad_IsFileInWad(fullName, currWadHandle);
	}
	else return FALSE;
}

int File_GetC(lpFile f)
{
	FileSys fs = _File_GetSystem(f);
	int len;
	switch (fs)
	{
	case FileSystem_Std:
		return fgetc(StdFile(f));
		break;
	case FileSystem_Wad:
		len = Wad_hLength(WadFile(f)->hFile);
		if (WadFile(f)->streamPos >= len-1) return EOF;
		else
		{
			int c = *((int*)((char *)Wad_hData(WadFile(f)->hFile) + WadFile(f)->streamPos));
			WadFile(f)->streamPos++;
			return c;
		}
		break;
	case FileSystem_Err:
	default:
		File_Error("%s(%i) : Unknown file system in call to %s", __FILE__, __LINE__, "File_GetC");
		break;
	}
	return 0;
}

int File_Length(lpFile f) 
{
	int pos, len;
	pos = File_Tell(f);
	File_Seek(f, 0, SEEK_END);
	len = File_Tell(f);
	File_Seek(f, pos, SEEK_SET);
	return len;
}

char *File_InternalFGetS(char *fgetsBuffer, int num, lpFile f)
{
	int pos=0;
	while ((fgetsBuffer[pos] = (char)File_GetC(f)) != 0 && fgetsBuffer[pos] != '\n' && fgetsBuffer[pos] != EOF && pos != num)
	{
		pos++;
	}
	fgetsBuffer[pos + 1] = 0;
	if (pos == 0) return 0;
	else return fgetsBuffer;
}

// I do not want to do this function
char *File_GetS(char *fgetsBuffer, int num, lpFile f) 
{
	FileSys fs = _File_GetSystem(f);
	switch (fs)
	{
	case FileSystem_Std:
		return fgets(fgetsBuffer, num, StdFile(f));
		break;
	case FileSystem_Wad:
		return File_InternalFGetS(fgetsBuffer, num, f);
		break;
	case FileSystem_Err:
	default:
		File_Error("%s(%i) : Unknown file system in call to %s", __FILE__, __LINE__, "File_GetS");
		break;
	}
	return 0;
}

int File_PrintF(lpFile f, char *msg, ...)
{
	va_list arg;
	FileSys fs = _File_GetSystem(f);
	int ret;

	va_start(arg, msg);

	switch (fs)
	{
	case FileSystem_Std:
		ret = vfprintf(StdFile(f), msg, arg);
		va_end(arg);
		break;
	case FileSystem_Wad:
		File_Error("\"fprintf\" is unsupprted for wad files");
		break;
	case FileSystem_Err:
	default:
		File_Error("%s(%i) : Unknown file system in call to %s", __FILE__, __LINE__, "File_PrintF");
		break;
	}
	return 0;
}

ULONG File_VPrintF(lpFile file, LPUCHAR msg, va_list args)
{
	FileSys fs = _File_GetSystem(file);

	if (FileSystem_Std == fs)
	{
		UCHAR buffer[1024];
		ULONG len;

		len = vsprintf(buffer, msg, args);
		Error_Fatal(len>=sizeof(buffer), "Buffer too small");
		File_Write(buffer, sizeof(UCHAR), len, file);

		return len;
	}

	return 0;
}

int File_ScanF(lpFile f, char *msg, ...)
{
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

FileSys _File_GetSystem(lpFile f)
{
	return f->type;
}

FileSys _File_CheckSystem(char *fName, char *mode)
{
	if (!fName || !mode || !strlen(fName) || !strlen(mode)) return FileSystem_Err;

	if (mode[0] == 'w' || mode[0] == 'W')
	{
		// File must be opened as stdC
		return FileSystem_Std;
	}
	else
	{
		if (Wad_IsFileInWad(_File_GetWadName(fName), currWadHandle) != WAD_ERROR)
//		if (currWadHandle != WAD_ERROR && Wad_IsFileInWad(_File_GetWadName(fName), currWadHandle) != WAD_ERROR)
		{
			// The file is in the wad so we can use the wad version
			return FileSystem_Wad;
		}	// Otherwise we will try the normal file system
		else return FileSystem_Std;
	}
}

BOOL _File_OpenWad(WADFILE *wad, char *fName)
{
	wad->eof = FALSE;
	wad->streamPos = 0;
	wad->hFile = Wad_FileOpen(fName, currWadHandle);
	return wad->hFile == WAD_ERROR ? FALSE : TRUE;
}

void *_File_Malloc(int size)
{
////////////////////////
	return Mem_Alloc(size);	// Change to whatever is required
////////////////////////
}

void _File_Free(void *ptr)
{
//////////////
	Mem_Free(ptr);				// Change to whatever is required
//////////////
}

lpFile _File_Alloc(FileSys fType)
{
	if (fType == FileSystem_Std) 
	{
		lpFile f;
		f = (lpFile) _File_Malloc(sizeof(File));
		f->type = fType;
		return f;
	}
	else if (fType == FileSystem_Wad) 
	{
		lpFile f = (lpFile) _File_Malloc(sizeof(File));
		if (f)
		{
			f->type = fType;
			f->wad = (WADFILE*) _File_Malloc(sizeof(WADFILE));
			if (f->wad) return f;
			else _File_Free(f);
		}
	}
	return 0;
}

void _File_Dealloc(lpFile file)
{
	if (file)
	{
		if (_File_GetSystem(file) == FileSystem_Std)
		{
			if (file->std) fclose(StdFile(file));
			_File_Free(file);
		}
		else if (_File_GetSystem(file) == FileSystem_Wad)
		{
			if (file->wad) 
			{
				Wad_FileClose(file->wad->hFile);
				_File_Free(file->wad);
			}
			_File_Free(file);
		}
	}
}

// Given the base path (if it exsits) generate the wad name
char *_File_GetWadName(char *fName)
{
	static char wadedName[MAX_WAD_BASE_PATH];

	if (basePathSet)
	{
		int fLen = strlen(fName);
		int wLen = strlen(wadBasePath);
		if (fLen <= wLen) return fName;
		else
		{
			char copy = fName[wLen], *ptr;
			fName[wLen] = 0;
			if (!_stricmp(fName, wadBasePath))
			{
				ptr = fName + wLen + 1;
				sprintf(wadedName, "%s", ptr);
				fName[wLen] = copy;
				return wadedName;
			}
			else
			{
				fName[wLen] = copy;
				return fName;
			}
		}
	}
	else return fName;
}

#else // _GODS98_USEWAD_

/*
lpFile File_Open(LPUCHAR fname, LPUCHAR mode){

	LPUCHAR fullName;
	FILE *file;
//	struct _finddata_t c_file;
//	ULONG hFile;
	BOOL w, tryCD = FALSE;
	UCHAR cdName[FILE_MAXPATH];

	if (fullName = File_VerifyFilename(fname))
	{
		w = strcmp(mode, "w");
		if (w) w = strcmp(mode, "wb");

		if (w) {
//			if( (hFile = _findfirst( fullName, &c_file )) == -1L )
			if (!File_FileExists(fname)) {
				Error_Warn(TRUE, Error_Format("Invalid filename specified \"%s\"", fname));
				Error_LogLoadError( TRUE, Error_Format( "%d\t%s", Error_LoadError_InvalidFName, fullName ) );

				return NULL;
			}

		} else if ('\0' != fileGlobs.cdLetter) {
			sprintf(cdName, "%c:\\%s\\%s", fileGlobs.cdLetter, FILE_DATADIRNAME, fname);
			tryCD = TRUE;
		}

		if (file = fopen(fullName, mode))
		{
			Error_LogLoad( TRUE, fullName );

			return (lpFile) file;

		} else if (tryCD && (file = fopen(cdName, mode))) {


		} else {
			if (w) {
				Error_Warn(TRUE, Error_Format("Unable to open file \"%s\"", fname));
				Error_LogLoadError( TRUE, Error_Format( "%d\t%s", Error_LoadError_UnableToOpen, fullName ) );
			} else {
				Error_Warn(TRUE, Error_Format("Unable to open file \"%s\" for writing", fname));
				Error_LogLoadError( TRUE, Error_Format( "%d\t%s", Error_LoadError_UnableToOpenForWrite, fullName ) );
			}

		}

	} 


	return NULL;
}
*/
SLONG File_Seek(lpFile file, SLONG offset, ULONG mode){

	return fseek((FILE *)file, offset, mode);
}

SLONG File_Read(LPVOID buffer, ULONG size, ULONG count, lpFile file){

	return fread(buffer, size, count, (FILE *)file);
}

SLONG File_Write(LPVOID buffer, ULONG size, ULONG count, lpFile file){

	return fwrite(buffer, size, count, (FILE *)file);
}

SLONG File_Close(lpFile file){

	return fclose((FILE *)file);
}

SLONG File_Tell(lpFile file){

	return ftell((FILE *)file);
}

SLONG File_Flush(lpFile file){

	return fflush((FILE *)file);
}

LPUCHAR File_GetS(LPUCHAR buffer, ULONG size, lpFile file){

	return fgets(buffer, size, (FILE *)file);

}

SLONG File_Length(lpFile fp) {

	ULONG Seek, Length;

    Seek = File_Tell(fp);
    File_Seek(fp, 0, SEEK_END);
    Length = File_Tell(fp);
    File_Seek(fp, Seek, SEEK_SET);

    return Length;
}

ULONG File_PrintF(lpFile file, LPUCHAR msg, ...){

	va_list args;
	ULONG len;

	va_start(args, msg);
	len = File_VPrintF(file, msg, args);
	va_end(args);

	return len;
}

ULONG File_VPrintF(lpFile file, LPUCHAR msg, va_list args){

	UCHAR buffer[1024];
	ULONG len;

	len = vsprintf(buffer, msg, args);
	Error_Fatal(len>=sizeof(buffer), "Buffer too small");
	File_Write(buffer, sizeof(UCHAR), len, file);

	return len;
}

#endif // _GODS98_USEWAD_

LPUCHAR File_GetLine(LPUCHAR buffer, ULONG size, lpFile file){

	// Same as File_GetS() but without the return character.

	LPUCHAR res = File_GetS(buffer, size, file);
	ULONG length = strlen(buffer) - 1;
	if ('\n' == buffer[length]) buffer[length] = '\0';
	if (length && '\r' == buffer[length-1]) buffer[length-1] = '\0';

	return res;
}

LPVOID File_LoadBinary(LPUCHAR filename, LPULONG sizeptr){

	return File_Load(filename, sizeptr, TRUE);
}

LPVOID File_LoadASCII(LPUCHAR filename, LPULONG sizeptr){

	return File_Load(filename, sizeptr, FALSE);
}

static LPVOID File_Load(LPUCHAR filename, LPULONG sizeptr, BOOL binary) {
	
	lpFile ifp;
	ULONG size;
	LPUCHAR buffer;

	if (ifp = File_Open(filename, binary?"rb":"r")){
		File_Seek(ifp, 0, File_SeekEnd);
		size = File_Tell(ifp);

#ifdef _DEBUG
		Error_Fatal(0==size, Error_Format("Attempt to File_LoadBinary() a file of zero length \"%s\"", filename));
#endif // _DEBUG

		if (fileGlobs.loadCallback) fileGlobs.loadCallback(filename, size, fileGlobs.loadCallbackData);
		if (buffer = Mem_Alloc(size)){

			File_Seek(ifp, 0, File_SeekSet);
			File_Read(buffer, sizeof(UCHAR), size, ifp);
			if (NULL != sizeptr) *sizeptr = size;

			File_Close(ifp);
			return buffer;
		}
		File_Close(ifp);
	}

	return NULL;
}

ULONG File_LoadBinaryHandle(LPUCHAR filename, LPULONG sizeptr){
	
	lpFile ifp;
	ULONG size;
	ULONG handle;
	LPUCHAR buffer;

	if (ifp = File_Open(filename, "rb")){
		File_Seek(ifp, 0, File_SeekEnd);
		size = File_Tell(ifp);
		if (fileGlobs.loadCallback) fileGlobs.loadCallback(filename, size, fileGlobs.loadCallbackData);

		if (-1 != (handle = Mem_AllocHandle(size))){
			buffer = Mem_AddressHandle(handle);
			File_Seek(ifp, 0, File_SeekSet);
			File_Read(buffer, sizeof(UCHAR), size, ifp);
			if (NULL != sizeptr) *sizeptr = size;

			File_Close(ifp);
			return handle;
		}
		File_Close(ifp);
	}

	return -1;
}
/*
BOOL File_FileExists( LPUCHAR name )
{	
	struct _finddata_t c_file;
	LPUCHAR fullName;
	

	if( fullName = File_VerifyFilename(name) )
		if( -1L != _findfirst( fullName, &c_file ) )
			return TRUE;

	return FALSE;
			
}
*/
LPUCHAR File_VerifyFilename(LPUCHAR filename){

#ifdef _GODSUNLIMITEDFILELOAD
	return filename;
#else
	static UCHAR full[_MAX_PATH];
	UCHAR part[_MAX_PATH];
	LPUCHAR temp;
	

	if( NULL != filename )
	{
		//REMOVE THE LEADING FORWARD SLASH IF ANY
		temp = filename;
		if( '\\' == *temp )
			temp++;

		if('@' == *temp )
		{
			temp++;
			sprintf(full, "%s\\%s", fileGlobs.exeDir, temp);
			return full;
		}
		else
			sprintf(part, "%s\\%s", fileGlobs.dataDir, temp);

		if(NULL != _fullpath(full, part, _MAX_PATH)){
			if (0 == strncmp(full, fileGlobs.dataDir, strlen(fileGlobs.dataDir))){
				return full;
			}
		}
	}

	Error_Warn( TRUE, Error_Format( "Cannot verify file name \"%s\".", filename ) );
	Error_LogLoadError( TRUE, Error_Format( "%d\t%s", Error_LoadError_UnableToVerifyName, filename ) );

	return NULL;
#endif // _GODSUNLIMITEDFILELOAD
}

VOID File_SetLoadCallback(VOID (*Callback)(LPUCHAR filename, ULONG filesize, LPVOID data), LPVOID data){

	fileGlobs.loadCallback = Callback;
	fileGlobs.loadCallbackData = data;
}



//MAYBE USE LINKED LIST

#define FILE_DEBUG_RLISTSIZE			2000

UCHAR loadedList[FILE_DEBUG_RLISTSIZE][1024];
ULONG numInList;

static VOID File_CheckFile( LPUCHAR fileName )
{	ULONG loop;


	for( loop = 0; loop < numInList; loop++ )
		if( !_stricmp(fileName, loadedList[loop]) )
			return;

	Error_LogRedundantFile( TRUE, fileName );

}



static VOID File_CheckDirectory( LPUCHAR dirName )
{	struct _finddata_t c_file;
	ULONG hFile;
	UCHAR name[1024];


	strcpy( name, dirName );
	strcat( name, "\\*.*" );

	if( (hFile = _findfirst( name, &c_file )) == -1L )
		return;
	else
	{
		do
		{
			if( !strcmp(c_file.name, ".") || !strcmp(c_file.name, "..") )
				continue;

			strcpy( name, dirName );
			strcat( name, "\\" );
			strcat( name, c_file.name );

			if( _A_SUBDIR & c_file.attrib )
				File_CheckDirectory( name );
			else
				File_CheckFile( name );

		} while( _findnext( hFile, &c_file ) == 0 );

		_findclose( hFile );

	}

}



VOID File_CheckRedundantFiles( LPUCHAR logName )
{	FILE* fileList;
	UCHAR fileName[1024];


	if( fileList = (FILE *)File_Open( logName, "r" ) )
	{
		numInList = 0;

		while( EOF != fscanf(fileList, "%s", fileName) ){
			Error_Fatal(numInList == FILE_DEBUG_RLISTSIZE, "FILE_DEBUG_RLISTSIZE too small");
			strcpy( loadedList[numInList++], fileName );
		}

		File_CheckDirectory( fileGlobs.dataDir );

		fclose( fileList );

	}

}


void File_SetDataDir(unsigned char *newDataDir)
{

	strcpy(fileGlobs.dataDir, newDataDir);

}
