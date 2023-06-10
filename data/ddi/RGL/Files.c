
#include <windows.h>

#include "Standard.h"
#include "Errors.h"
#include "Sound.h"
#include "Utils.h"
#include "Mem.h"
#include "Wad.h"
#include "Lists.h"
#include "Files.h"

struct FileLoadStatus {

	ULONG uid;
	ULONG currBytes, currFiles;
	ULONG totalFiles[2];
	ULONG totalBytes[2];

};

struct FileGlobs {

	UCHAR cdDrive;
	LPUCHAR rootDirectoryName;
	LPUCHAR pathNameBuffer, fileNameBuffer;
	ULONG pathNameBufferSize, fileNameBufferSize;
	ULONG pathNameBufferUsed, fileNameBufferUsed;
	struct FileSharedObjectData *sharedData;
	ULONG sharedDataSize, sharedDataUsed;

	struct FileLoadStatus *loadStatusList;
	ULONG currLoadStatus, loadStatusCount;
	BOOL buildLoadStatus;
	VOID (*loadStatusCallback)(ULONG uid, REAL progress, LPVOID data);
	LPVOID loadStatusCallbackData;

	struct List *list;

} fileGlobs = { 0 };

VOID File_Initialise(VOID) {

	fileGlobs.rootDirectoryName = "Data";
	fileGlobs.list = List_Create(sizeof(struct File));
}

VOID File_Shutdown(VOID) {

	if (fileGlobs.loadStatusList) {
		Mem_Free(fileGlobs.loadStatusList);
		fileGlobs.loadStatusList = NULL;
	}
	fileGlobs.loadStatusCount = 0;

	List_Remove(fileGlobs.list);
	fileGlobs.list = NULL;
}

static BOOL File_FindLoadStatus(ULONG uid, LPULONG index) {

	ULONG loop;

	for (loop=0 ; loop<fileGlobs.loadStatusCount ; loop++) {
		if (uid == fileGlobs.loadStatusList[loop].uid) {
			*index = loop;
			return TRUE;
		}
	}

	return FALSE;
}

static ULONG File_AddLoadStatus(ULONG uid) {

	ULONG index = fileGlobs.loadStatusCount;

	fileGlobs.loadStatusList = Mem_ReAllocClear(fileGlobs.loadStatusList, sizeof(fileGlobs.loadStatusList[0]) * ++fileGlobs.loadStatusCount);
	fileGlobs.loadStatusList[index].uid = uid;

	return index;
}

VOID File_SetBuildLoadStatus(BOOL on) {

	fileGlobs.buildLoadStatus = on;
}

VOID File_LoadStatusIO(BOOL read) {

	lpFile fp;
	ULONG loop, count;
	UCHAR buffer[1024];
	LPUCHAR argv[10];
	ULONG argc;

	Error_Fatal(NULL != fileGlobs.loadStatusCallback, "LoadStatusCallback is still set");

	if (read || fileGlobs.loadStatusCount) {
		if (fp = File_Open("LoadStatus.txt", read?"r":"w")) {

			if (read) {

				for (count=0 ; File_GetS(buffer, sizeof(buffer), fp) ; count++) ;
				File_Seek(fp, 0, FileSeekSet);

			} else count = fileGlobs.loadStatusCount;

			for (loop=0 ; loop<count ; loop++) {
				if (read) {
				
					File_GetS(buffer, sizeof(buffer), fp);
					argc = Util_Tokenise(buffer, argv, sizeof(argv) / sizeof(argv[0]), ":", FALSE);
					Error_Fatal(5 != argc, "Invalid load status file");
					File_AddLoadStatus(atol(argv[0]));
					fileGlobs.loadStatusList[loop].totalFiles[0] = atol(argv[1]);
					fileGlobs.loadStatusList[loop].totalBytes[0] = atol(argv[2]);
					fileGlobs.loadStatusList[loop].totalFiles[1] = atol(argv[3]);
					fileGlobs.loadStatusList[loop].totalBytes[1] = atol(argv[4]);

				} else File_PrintF(fp, "%d:%d:%d:%d:%d\n",
					fileGlobs.loadStatusList[loop].uid,
					fileGlobs.loadStatusList[loop].totalFiles[0],
					fileGlobs.loadStatusList[loop].totalBytes[0],
					fileGlobs.loadStatusList[loop].totalFiles[1],
					fileGlobs.loadStatusList[loop].totalBytes[1]);
			}

			File_Close(fp);
		}
	}
}

VOID File_StartLoad(ULONG uid, VOID (*callback)(ULONG uid, REAL progress, LPVOID data), LPVOID data) {

	Error_Fatal(NULL == callback, "NULL passed as callback");
	Error_Fatal(callback && NULL != fileGlobs.loadStatusCallback, "LoadStatusCallback is still set");

	fileGlobs.loadStatusCallback = callback;
	fileGlobs.loadStatusCallbackData = data;

	if (!File_FindLoadStatus(uid, &fileGlobs.currLoadStatus)) {
		fileGlobs.currLoadStatus = File_AddLoadStatus(uid);
	}

	if (fileGlobs.buildLoadStatus) {
		fileGlobs.loadStatusList[fileGlobs.currLoadStatus].totalBytes[Sound_IsInitialised()] = 0;
		fileGlobs.loadStatusList[fileGlobs.currLoadStatus].totalFiles[Sound_IsInitialised()] = 0;
	}

	fileGlobs.loadStatusList[fileGlobs.currLoadStatus].currBytes = 0;
	fileGlobs.loadStatusList[fileGlobs.currLoadStatus].currFiles= 0;
}

VOID File_StopLoad(VOID) {

	fileGlobs.loadStatusCallback = NULL;
	fileGlobs.loadStatusCallbackData = NULL;
}

VOID File_FreeBuffers(VOID) {

	Mem_Free(fileGlobs.pathNameBuffer);
	Mem_Free(fileGlobs.fileNameBuffer);
}

BOOL File_SaveBinary(LPUCHAR name, LPVOID buffer, ULONG bufferSize) {

	lpFile fp;

	if (fp = File_Open(name, "wb")) {

		File_Write(buffer, bufferSize, 1, fp);

		File_Close(fp);

		return TRUE;
	}

	return FALSE;
}

#ifdef _DEBUG
LPVOID File_Debug_LoadBinary(LPUCHAR name, LPULONG size, LPUCHAR file, ULONG line) {
#else // _DEBUG
LPVOID File_LoadBinary(LPUCHAR name, LPULONG size) {
#endif // _DEBUG

	lpFile fp;
	LPVOID buffer;
	ULONG len;

	if (fp = File_Open(name, "rb")) {
		File_Seek(fp, 0, FileSeekEnd);
		if (len = File_Tell(fp)) {
			File_Seek(fp, 0, FileSeekSet);
#ifdef _DEBUG
			buffer = Mem_Debug_Alloc(len, file, line);
#else // _DEBUG
			buffer = Mem_Alloc(len);
#endif // _DEBUG
			
			File_Read(buffer, 1, len, fp);
			File_Close(fp);
			if (size) *size = len;
			return buffer;
		}
		File_Close(fp);
	}

	return NULL;
}

LPVOID File_LoadBinaryTo(LPUCHAR name, LPULONG fileSize, LPVOID buffer, ULONG bufferSize) {

	lpFile file;
	ULONG readSize;

	if (file = File_Open(name, "rb")) {

		(*fileSize) = File_Length(file);
		readSize = min((*fileSize), bufferSize);

		File_Read(buffer, readSize, 1, file);

		File_Close(file);

	} else return NULL;

	return buffer;
}

LPUCHAR File_GetLine(LPUCHAR line, ULONG len, lpFile file) {

	LPUCHAR res = File_GetS(line, len, file);
	line[strlen(line)-1] = '\0';
	return res;
}

LPUCHAR File_GetSuffix(LPUCHAR fname) {

	LPUCHAR s, suffix = NULL;

	for (s=fname ; '\0'!=*s ; s++) if ('.' == *s) suffix = (s+1);

	return suffix;
}

#ifdef _DEBUG
lpList File_Debug_CreateSharedObjectList(LPUCHAR file, ULONG line) {
#else // _DEBUG
lpList File_CreateSharedObjectList(VOID) {
#endif // _DEBUG

#ifdef _DEBUG
	return List_Debug_Create(sizeof(struct FileSharedObject), file, line);
#else // _DEBUG
	return List_Create(sizeof(struct FileSharedObject));
#endif // _DEBUG

}

__inline static LPUCHAR File_GetSharedObjectFileName(lpFileSharedObject shared) {

	return &fileGlobs.fileNameBuffer[shared->fileIndex];
}

__inline static LPUCHAR File_GetSharedObjectPathName(lpFileSharedObject shared) {

	if (-1 == shared->pathIndex) return NULL;
	return &fileGlobs.pathNameBuffer[shared->pathIndex];
}

static BOOL File_RemoveSharedObjectListCallback(lpFileSharedObject shared, LPVOID data) {

	UCHAR buffer[FILE_MAXPATH];

	if (File_GetSharedObjectPathName(shared)) sprintf(buffer, "%s\\%s", File_GetSharedObjectPathName(shared), File_GetSharedObjectFileName(shared));
	else sprintf(buffer, "%s", File_GetSharedObjectFileName(shared));

	Error_Warn(TRUE, Error_Format("Shared object left on list \"%s\"", buffer));

	return FALSE;
}

VOID File_RemoveSharedObjectList(lpList list) {

	Error_Warn(TRUE, Error_Format("**** Removing shared object list: %s(%d)", list->file, list->line));

#ifdef _DEBUG
	List_RunThrough(list, File_RemoveSharedObjectListCallback, NULL);
#endif // _DEBUG
	List_Remove(list);
}

static BOOL File_GetSharedObjectCallback(lpFileSharedObject shared, LPVOID object) {

	if (shared->object == object) return TRUE;

	return FALSE;
}

static BOOL File_FindSharedFileName(LPUCHAR fname, LPULONG index) {

	ULONG loop;

	for (loop=0 ; loop<fileGlobs.fileNameBufferUsed ; ) {
		if (0 == strcmp(fname, &fileGlobs.fileNameBuffer[loop])) {

			*index = loop;
			return TRUE;
		}
		loop += strlen(&fileGlobs.fileNameBuffer[loop]) + 1;
	}

	return FALSE;
}

static ULONG File_AddSharedFileName(LPUCHAR file) {

	ULONG addBytes = strlen(file) + 1;
	ULONG startIndex = fileGlobs.fileNameBufferUsed;

	Error_Overflow(addBytes, FILE_FILENAMEBUFFERBLOCKSIZE);

	fileGlobs.fileNameBufferUsed += addBytes;

	if (fileGlobs.fileNameBufferUsed > fileGlobs.fileNameBufferSize) {
		fileGlobs.fileNameBufferSize += FILE_FILENAMEBUFFERBLOCKSIZE;
		fileGlobs.fileNameBuffer = Mem_ReAlloc(fileGlobs.fileNameBuffer, fileGlobs.fileNameBufferSize);
	}

	sprintf(&fileGlobs.fileNameBuffer[startIndex], "%s", file);

	return startIndex;
}

static BOOL File_FindSharedPathName(LPUCHAR fname, LPULONG index) {

	ULONG loop;

	for (loop=0 ; loop<fileGlobs.pathNameBufferUsed ; ) {
		if (0 == strcmp(fname, &fileGlobs.pathNameBuffer[loop])) {

			*index = loop;
			return TRUE;
		}
		loop += strlen(&fileGlobs.pathNameBuffer[loop]) + 1;
	}

	return FALSE;
}

static ULONG File_AddSharedPathName(LPUCHAR path) {

	ULONG addBytes = strlen(path) + 1;
	ULONG startIndex = fileGlobs.pathNameBufferUsed;

	Error_Overflow(addBytes, FILE_PATHNAMEBUFFERBLOCKSIZE);

	fileGlobs.pathNameBufferUsed += addBytes;

	if (fileGlobs.pathNameBufferUsed > fileGlobs.pathNameBufferSize) {
		fileGlobs.pathNameBufferSize += FILE_PATHNAMEBUFFERBLOCKSIZE;
		fileGlobs.pathNameBuffer = Mem_ReAlloc(fileGlobs.pathNameBuffer, fileGlobs.pathNameBufferSize);
	}

	sprintf(&fileGlobs.pathNameBuffer[startIndex], "%s", path);

	return startIndex;
}

BOOL File_ReleaseSharedObject(lpList list, LPVOID object) {

	lpFileSharedObject shared;
	
	if (shared = List_RunThrough(list, File_GetSharedObjectCallback, object)) {
		
		if (0 == --shared->referenceCount) {
			List_ReturnItem(list, shared);
		} else {
			return FALSE;
		}

	}

	return TRUE;
}

VOID File_RegisterSharedObject(lpList list, LPUCHAR fname, LPVOID object) {

	lpFileSharedObject shared;
	UCHAR buffer[FILE_MAXPATH];
	LPUCHAR s, file, path;

	Error_Fatal(NULL != List_RunThrough(list, File_GetSharedObjectCallback, object), "Object has already been registered");

	shared = List_ObtainItem(list);
	shared->object = object;
	shared->referenceCount = 1;

	sprintf(buffer, "%s", fname);
	for (file=s=buffer ; '\0'!=*s ; s++) {
		if ('\\' == *s) file = s;
	}
	if (file != buffer) {
		*(file++) = '\0';
		path = buffer;
	} else path = NULL;

	if (!File_FindSharedFileName(file, &shared->fileIndex)) {
		shared->fileIndex = File_AddSharedFileName(file);
	}

	if (path) {
		if (!File_FindSharedPathName(path, &shared->pathIndex)) {
			shared->pathIndex = File_AddSharedPathName(path);
		}
	} else shared->pathIndex = -1;
}

static BOOL File_FindSharedObjectCallback(lpFileSharedObject shared, LPVOID data) {

	LPUCHAR fname = data;
	UCHAR buffer[FILE_MAXPATH];

	if (File_GetSharedObjectPathName(shared)) sprintf(buffer, "%s\\%s", File_GetSharedObjectPathName(shared), File_GetSharedObjectFileName(shared));
	else sprintf(buffer, "%s", File_GetSharedObjectFileName(shared));

	if (0 == stricmp(buffer, fname)) return TRUE;

	return FALSE;
}

LPVOID File_FindSharedObject(lpList list, LPUCHAR fname) {

	lpFileSharedObject shared;
	
	if (shared = List_RunThrough(list, File_FindSharedObjectCallback, fname)) {
		
		shared->referenceCount++;

		return shared->object;
	}
	
	return NULL;
}

BOOL File_FindSharedObjectFileName(lpList list, LPVOID object, LPUCHAR fileName) {

	lpFileSharedObject shared;
	
	if (shared = List_RunThrough(list, File_GetSharedObjectCallback, object)) {

		if (File_GetSharedObjectPathName(shared)) sprintf(fileName, "%s\\%s", File_GetSharedObjectPathName(shared), File_GetSharedObjectFileName(shared));
		else sprintf(fileName, "%s", File_GetSharedObjectFileName(shared));
	}

	return FALSE;
}

#ifdef _DEBUG
VOID File_Debug_DumpSharedFileData(VOID) {

	FILE *fp;
	ULONG loop;

	if (fp = fopen("shared.dmp", "w")) {

		fprintf(fp, "Paths:\n");
		for (loop=0 ; loop<fileGlobs.pathNameBufferUsed ; ) {

			fprintf(fp, "%s\n", &fileGlobs.pathNameBuffer[loop]);

			loop += strlen(&fileGlobs.pathNameBuffer[loop]) + 1;
		}
		fprintf(fp, "\nFiles:\n");
		for (loop=0 ; loop<fileGlobs.fileNameBufferUsed ; ) {

			fprintf(fp, "%s\n", &fileGlobs.fileNameBuffer[loop]);

			loop += strlen(&fileGlobs.fileNameBuffer[loop]) + 1;
		}

		fclose(fp);
	}
}
#endif // _DEBUG

/*
VOID File_RegisterSharedObject(LPUCHAR fname, LPVOID object, enum FileObjectType type) {

	SLONG fileStart, fileEnd, fileLength, loop;
	lpFileSharedObjectData shared;
	SLONG gotFileIndex = -1, gotPathIndex = -1;

	for (fileStart=fileEnd=0 ; '\0'!=fname[fileEnd] ; fileEnd++) {
		if ('\\' == fname[fileEnd]) fileStart = fileEnd + 1;
	}
	fileLength = (fileEnd - fileStart) + 1;

	// Look to see if the path/file name has been used...
	for (loop=0 ; loop<(SLONG)fileGlobs.sharedDataUsed ; loop++) {
		shared = &fileGlobs.sharedData[loop];
		if (0 == stricmp(File_GetFileName(shared), &fname[fileStart])) gotFileIndex = shared->fileIndex;
		if (NULL != File_GetPathName(shared) && strlen(File_GetPathName(shared)) == (ULONG) (fileStart-1) && 0 == strnicmp(File_GetPathName(shared), fname, fileStart - 1)) gotPathIndex = shared->pathIndex;
		if (-1 != gotFileIndex && -1 != gotPathIndex) break;
	}

#ifdef _DEBUG
	{
		for (loop=0 ; loop<(SLONG)fileGlobs.sharedDataUsed ; loop++) {
			shared = &fileGlobs.sharedData[loop];
			Error_Fatal(shared->object==object, "Object has already been registered, or removed then re-registered");
		}
	}
#endif

	Error_Fatal(0==fileLength, "No file in filename");
	Error_Fatal(fileLength >= FILE_FILENAMEBUFFERBLOCKSIZE, Error_Format("File name is too long (more than FILE_FILENAMEBUFFERBLOCKSIZE (%i bytes))", FILE_FILENAMEBUFFERBLOCKSIZE));
	Error_Fatal(fileStart >= FILE_PATHNAMEBUFFERBLOCKSIZE, Error_Format("Path to file is too long (more than FILE_PATHNAMEBUFFERBLOCKSIZE (%i bytes))", FILE_PATHNAMEBUFFERBLOCKSIZE));

	// Ensure that all buffers are created and will not overflow...
	if (-1 == gotFileIndex) {
		if (fileGlobs.fileNameBufferUsed + fileLength > fileGlobs.fileNameBufferSize) {
			fileGlobs.fileNameBufferSize += FILE_FILENAMEBUFFERBLOCKSIZE;
			fileGlobs.fileNameBuffer = Mem_ReAlloc(fileGlobs.fileNameBuffer, fileGlobs.fileNameBufferSize);
		}
	}
	if (-1 == gotPathIndex) {
		if (fileGlobs.pathNameBufferUsed + fileStart > fileGlobs.pathNameBufferSize) {
			fileGlobs.pathNameBufferSize += FILE_PATHNAMEBUFFERBLOCKSIZE;
			fileGlobs.pathNameBuffer = Mem_ReAlloc(fileGlobs.pathNameBuffer, fileGlobs.pathNameBufferSize);
		}
	}
	if (fileGlobs.sharedDataUsed == fileGlobs.sharedDataSize) {
		fileGlobs.sharedDataSize += FILE_SHAREDOBJECTBLOCKSIZE;
		fileGlobs.sharedData = Mem_ReAlloc(fileGlobs.sharedData, sizeof(fileGlobs.sharedData[0]) * fileGlobs.sharedDataSize);
	}

	shared = &fileGlobs.sharedData[fileGlobs.sharedDataUsed++];

	if (-1 != gotFileIndex) shared->fileIndex = gotFileIndex;
	else {
		shared->fileIndex = fileGlobs.fileNameBufferUsed;
		for (loop=0 ; loop<fileLength ; loop++) fileGlobs.fileNameBuffer[fileGlobs.fileNameBufferUsed++] = fname[fileStart + loop];
	}

	if (-1 != gotPathIndex) shared->pathIndex = gotPathIndex;
	else {
		if (fileStart) {
			shared->pathIndex = fileGlobs.pathNameBufferUsed;
			for (loop=0 ; loop<fileStart-1 ; loop++) fileGlobs.pathNameBuffer[fileGlobs.pathNameBufferUsed++] = fname[loop];
			fileGlobs.pathNameBuffer[fileGlobs.pathNameBufferUsed++] = '\0';
		} else shared->pathIndex = -1;
	}

	shared->object = object;
	shared->objectType = type;
}

LPVOID File_FindSharedObject(LPUCHAR fname, enum File_ObjectType type) {

	SLONG fileStart, fileEnd, loop;
	lpFileSharedObjectData shared;

	for (fileStart=fileEnd=0 ; '\0'!=fname[fileEnd] ; fileEnd++) {
		if ('\\' == fname[fileEnd]) fileStart = fileEnd + 1;
	}

	for (loop=0 ; loop<(SLONG)fileGlobs.sharedDataUsed ; loop++) {
		shared = &fileGlobs.sharedData[loop];
		if (0 == type || shared->objectType == type) {
			if (0 == stricmp(File_GetFileName(shared), &fname[fileStart])) {
				if ((NULL == File_GetPathName(shared) && 0 == fileStart) ||
					(NULL != File_GetPathName(shared) && strlen(File_GetPathName(shared)) == (ULONG) (fileStart-1) && 0 == strnicmp(File_GetPathName(shared), fname, fileStart - 1))) {
					
					return shared->object;
				}
			}
		}
	}

	return NULL;
}

BOOL File_FindFileName(LPVOID object, enum File_ObjectType type, LPUCHAR fileName) {

	ULONG loop;
	lpFileSharedObjectData shared;

	for (loop=0 ; loop<fileGlobs.sharedDataUsed ; loop++) {
		
		shared = &fileGlobs.sharedData[loop];

		if (shared->objectType == type) {
			if (shared->object == object) {

				if (File_GetPathName(shared)) sprintf(fileName, "%s\\%s", File_GetPathName(shared), File_GetFileName(shared));
				else sprintf(fileName, "%s", File_GetFileName(shared));

				return TRUE;
			}
		}
	}

	return FALSE;
}

__inline static LPUCHAR File_GetFileName(lpFileSharedObjectData data) {

	return &fileGlobs.fileNameBuffer[data->fileIndex];
}

__inline static LPUCHAR File_GetPathName(lpFileSharedObjectData data) {

	if (-1 == data->pathIndex) return NULL;
	return &fileGlobs.pathNameBuffer[data->pathIndex];
}
*/

__inline lpFile File_Open(LPUCHAR fname, LPUCHAR attribs) {

	return File_OpenEx(fname, attribs, FALSE);
}

__inline lpFile File_OpenEx(LPUCHAR fname, LPUCHAR attribs, BOOL noCD) {

	lpFile file = List_ObtainItem(fileGlobs.list);

	if (NULL == (file->wadEntry = Wad_File_Open(fname, attribs))) {
		if (NULL == (file->fp = fopen(File_GetActualPath(fname, noCD), attribs))) {

			List_ReturnItem(fileGlobs.list, file);
			file = NULL;
		}
	}

	if (file && fileGlobs.loadStatusCallback) {

		struct FileLoadStatus *status = &fileGlobs.loadStatusList[fileGlobs.currLoadStatus];
		REAL progress = 1.0f;

		if (fileGlobs.buildLoadStatus) {
			status->totalBytes[Sound_IsInitialised()] += File_Length(file);
			status->totalFiles[Sound_IsInitialised()]++;
		} else {
			status->currBytes += File_Length(file);
			status->currFiles++;
		}

		if (status->totalBytes[Sound_IsInitialised()]) {
			progress = status->currBytes / (REAL) status->totalBytes[Sound_IsInitialised()];
			progress += status->currFiles / (REAL) status->totalFiles[Sound_IsInitialised()];
			progress /= 2.0f;
			progress = min(1.0f, progress);
		}

		fileGlobs.loadStatusCallback(status->uid, progress, fileGlobs.loadStatusCallbackData);
	}

	return file;
}

__inline SLONG File_Close(lpFile file) {

	if (file->wadEntry) return Wad_File_Close(file->wadEntry);
	else return fclose(file->fp);
}

__inline size_t File_Read(LPVOID buffer, ULONG blockSize, ULONG count, lpFile file) {

	if (file->wadEntry) return Wad_File_Read(buffer, blockSize, count, file->wadEntry);
	else return fread(buffer, blockSize, count, file->fp);
}

__inline size_t File_Write(LPVOID buffer, ULONG blockSize, ULONG count, lpFile file) {

	if (file->wadEntry) {
		Error_Fatal(TRUE, "Cannot write to a wad file");
		return 0;
	} else return fwrite(buffer, blockSize, count, file->fp);
}

__inline SLONG File_Seek(lpFile file, SLONG offset, SLONG flags) {

	if (file->wadEntry) return Wad_File_Seek(file->wadEntry, offset, flags);
	else return fseek(file->fp, offset, flags);
}

__inline SLONG File_Tell(lpFile file) {
	
	if (file->wadEntry) return Wad_File_Tell(file->wadEntry);
	else return ftell(file->fp);
}

__inline SLONG File_Length(lpFile file) {

	SLONG old, length;

	old = File_Tell(file);
	File_Seek(file, 0, FileSeekEnd);
	length = File_Tell(file);
	File_Seek(file, old, FileSeekSet);

	return length;
}

__inline LPUCHAR File_GetS(LPUCHAR buffer, ULONG size, lpFile file) {

	if (file->wadEntry) return Wad_File_GetS(buffer, size, file->wadEntry);
	else return fgets(buffer, size, file->fp);
}

__inline SLONG File_PrintF(lpFile file, LPUCHAR msg, ...) {

	va_list args;
	SLONG result;

	va_start(args, msg);
	if (file->wadEntry) Error_Fatal(TRUE, "Cannot File_PrintF() to a wad file");
	else result = vfprintf(file->fp, msg, args);
	va_end(args);

	return result;
}

__inline BOOL File_ExistsEx(LPUCHAR fname, BOOL noCD) {

	FILE *fp = NULL;

	if (Wad_FileExists(fname)) return TRUE;

	if (fp = fopen(File_GetActualPath(fname, noCD), "r")) {

		fclose(fp);
		return TRUE;

	}

	return FALSE;
}

__inline BOOL File_Exists(LPUCHAR fname) {

	return File_ExistsEx(fname, FALSE);
}

BOOL File_SetCDDrive(UCHAR driveLetter, BOOL cdOnly) {

	if ('\0' == driveLetter) {

		fileGlobs.cdDrive = '\0';
		return TRUE;

	} else {

		UCHAR path[] = { driveLetter, ':', '\\', '\0' };
		ULONG type = GetDriveType(path);

		switch (type) {
		case DRIVE_CDROM:									break;
		case DRIVE_FIXED:
		case DRIVE_REMOTE:
		case DRIVE_RAMDISK:		if (cdOnly) return FALSE;	break;
		default:				return FALSE;				break;
		}

		fileGlobs.cdDrive = driveLetter;

		return TRUE;
	}

	return FALSE;
}

LPUCHAR File_GetActualPath(LPUCHAR fname, BOOL noCD) {

	static UCHAR path[FILE_MAXPATH];

	Error_Fatal(NULL == fname, "NULL passed to File_GetActualPath()");
	Error_Fatal(NULL != strstr(fname, ":"), "Absolute path names are not allowed");
	Error_Fatal(NULL != strstr(fname, "..\\"), "Don't use .. in file paths");

	if (!noCD && '\0' != fileGlobs.cdDrive && !File_ExistsEx(fname, TRUE)) {

		FILE *fp;

		sprintf(path, "%c:\\%s\\%s", fileGlobs.cdDrive, fileGlobs.rootDirectoryName, fname);

		if (fp = fopen(path, "rb")) {

			fclose(fp);

			return path;
		}

	}
	
	sprintf(path, "%s\\%s", fileGlobs.rootDirectoryName, fname);

	return path;
}
