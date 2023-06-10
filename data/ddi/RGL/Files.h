
#ifndef _RGL_FILES_H_
#define _RGL_FILES_H_

/************************************************************************************************************************
 **** Constants and enumerations available outside the library...
 ************************************************************************************************************************/

#define FILE_MAXPATH					256
#define FILE_PATHNAMEBUFFERBLOCKSIZE	1024
#define FILE_FILENAMEBUFFERBLOCKSIZE	1024

enum FileSeekType {

	FileSeekSet = SEEK_SET,
	FileSeekEnd = SEEK_END,
	FileSeekCur = SEEK_CUR
};

#ifdef _RGL

/************************************************************************************************************************
 **** Internal library structures
 ************************************************************************************************************************/

struct File {

	FILE *fp;
	struct WadEntry *wadEntry;
};

struct FileSharedObject {

	ULONG pathIndex;
	ULONG fileIndex;
	LPVOID object;
	ULONG referenceCount;
};

#endif // _RGL

/************************************************************************************************************************
 **** Typedefs available outside the library...
 ************************************************************************************************************************/

typedef struct File						*lpFile;
typedef struct FileSharedObject			*lpFileSharedObject;

#ifdef _DEBUG
#define File_LoadBinary(n,s)			File_Debug_LoadBinary((n),(s),__FILE__,__LINE__)
#else
extern void *__cdecl File_LoadBinary(unsigned char *name,unsigned long *size);
#endif // _DEBUG

#ifdef _DEBUG
#define File_CreateSharedObjectList()			File_Debug_CreateSharedObjectList(__FILE__,__LINE__);
#endif // _DEBUG

// Auto Prototypes
extern unsigned __int64 __stdcall Int64ShllMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern __int64 __stdcall Int64ShraMod32(__int64 Value,unsigned long ShiftCount);
extern unsigned __int64 __stdcall Int64ShrlMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern void *__cdecl GetFiberData(void );
extern void *__cdecl GetCurrentFiber(void );
extern int __cdecl File_SaveBinary(unsigned char *name, void *buffer, unsigned long bufferSize);
extern void *__cdecl File_Debug_LoadBinary(unsigned char *name,unsigned long *size,unsigned char *file,unsigned long line);
extern void *__cdecl File_LoadBinaryTo(unsigned char *name,unsigned long *fileSize,void *buffer,unsigned long bufferSize);
extern unsigned char *__cdecl File_GetLine(unsigned char *line,unsigned long len,struct File *file);
extern unsigned char *__cdecl File_GetSuffix(unsigned char *fname);
extern struct File *__cdecl File_Open(unsigned char *fname,unsigned char *attribs);
extern struct File *__cdecl File_OpenEx(unsigned char *fname,unsigned char *attribs,int noCD);
extern long __cdecl File_Close(struct File *file);
extern unsigned int __cdecl File_Read(void *buffer,unsigned long blockSize,unsigned long count,struct File *file);
extern unsigned int __cdecl File_Write(void *buffer,unsigned long blockSize,unsigned long count,struct File *file);
extern long __cdecl File_Seek(struct File *file,long offset,long flags);
extern long __cdecl File_Tell(struct File *file);
extern long __cdecl File_Length(struct File *file);
extern unsigned char *__cdecl File_GetS(unsigned char *buffer,unsigned long size,struct File *file);
extern long __cdecl File_PrintF(struct File *file,unsigned char *msg,...);
extern  unsigned char *__cdecl File_GetActualPath(unsigned char *fname,int noCD);
extern BOOL __cdecl File_Exists(LPUCHAR fname);
extern BOOL __cdecl File_ExistsEx(LPUCHAR fname, BOOL noCD);
#ifndef _DEBUG
extern struct List *__cdecl File_CreateSharedObjectList(VOID);
#else
extern struct List *__cdecl File_Debug_CreateSharedObjectList(LPUCHAR file, ULONG line);
#endif // _DEBUG
extern VOID __cdecl File_RegisterSharedObject(struct List *list, LPUCHAR fname, LPVOID object);
extern LPVOID __cdecl File_FindSharedObject(struct List *list, LPUCHAR fname);
extern BOOL __cdecl File_FindSharedObjectFileName(struct List *list, LPVOID object, LPUCHAR fileName);
extern BOOL __cdecl File_ReleaseSharedObject(struct List *list, LPVOID object);
extern VOID __cdecl File_RemoveSharedObjectList(struct List *list);
extern VOID __cdecl File_SetBuildLoadStatus(BOOL on);
extern VOID __cdecl File_StartLoad(ULONG uid, VOID (*callback)(ULONG uid, REAL progress, LPVOID data), LPVOID data);
extern VOID __cdecl File_StopLoad(VOID);
extern VOID __cdecl File_FreeBuffers(VOID);
extern VOID __cdecl File_Initialise(VOID);
extern VOID __cdecl File_Shutdown(VOID);
extern BOOL __cdecl File_SetCDDrive(UCHAR driveLetter, BOOL cdOnly);
extern VOID __cdecl File_LoadStatusIO(BOOL read);
// Auto Prototypes

#endif // !_RGL_FILES_H_

