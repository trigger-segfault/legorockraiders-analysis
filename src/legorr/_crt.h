/// REFERENCE: Microsoft C runtime library (CRT)
/// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/c-run-time-library-reference>
///
/// this file contains a list of all known CRT functions and their locations,
/// making it easier to seperate LegoRR code from prebuilt code.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>    // errno types
#include <windows.h>  // for extended case-insensitive str API?


#pragma region /// GLOBALS //////////////////////////////

// <LegoRR.exe @0054a0d0>
static errno_t g_msvc_errno;
// <LegoRR.exe @0054a0d4>
static unsigned int g_msvc_doserrno;

#pragma endregion



#pragma region /// NEVER SEEN ///////////////////////////

// functions that have not yet been seen in LegoRR.exe, but are likely to exist in some form.

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strstr-wcsstr-mbsstr-mbsstr-l>
// <LegoRR.exe @0048dd10>
char* strstr(const char* str, const char* strSearch);

#pragma endregion


#pragma region /// INLINED //////////////////////////////

// functions that generally get inlined 100% of the time.

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strlen-wcslen-mbslen-mbslen-l-mbstrlen-mbstrlen-l>
size_t strlen(const char* str);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strcat-wcscat-mbscat>
char* strcat(char* strDestination, const char* strSource);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strcpy-wcscpy-mbscpy>
char* strcpy(char* strDestination, const char* strource);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/memcpy-wmemcpy>
void* memcpy(void* dest, const void* src, size_t count);

// Generally used to zero-out memory
// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/memset-wmemset>
void* memset(void* dest, int c, size_t count);

#pragma endregion


#pragma region /// FUNCTIONS ////////////////////////////

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strdup-wcsdup-mbsdup>
// <LegoRR.exe @00477810>
char* _strdup(const char* strSource);

// (probably)
// formats then calls WINAPI OutputDebugStringA
// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/printf-printf-l-wprintf-wprintf-l>
// <LegoRR.exe @0047f8c0>
int printf(const char* format [, argument]...);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/atof-atof-l-wtof-wtof-l>
// <LegoRR.exe @0048dc40>
double atof(const char* str);

// (probably)
// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/sprintf-sprintf-l-swprintf-swprintf-l-swprintf-l>
// <LegoRR.exe @0048dca0>
int sprintf(char* buffer, const char* format [, argument] ...);

// (probably)
// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/atoi-atoi-l-wtoi-wtoi-l>
// <LegoRR.exe @0048de30>
int atoi(const char* str);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/free>
// 
// <LegoRR.exe @0048de40>
void free(void* memblock);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/malloc>
// 
// <LegoRR.exe @0048de90>
void* malloc(size_t size);

// (probably...)
// This function is used to allocate memory in units of 0x1000 (4096) bytes on the stack.
// It messes up Ghidra a ton on the calling functions, but assigning this function signature
// the `alloca_probe call Fixup` will clean up a lot of this jank.
// 
// Personally I labeled this function as `_alloca4k` for the fact that allocations are in units of 4096 bytes
// I've seen other uses of this name rarely from web searches. See also:
// <https://reverseengineering.stackexchange.com/questions/10759/what-is-alloca-probe-16-and-what-does-it-do>
// 
// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/alloca>
// <LegoRR.exe @0048e510>
void* _alloca(size_t size); // argument size passed in register EAX

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strncpy-strncpy-l-wcsncpy-wcsncpy-l-mbsncpy-mbsncpy-l>
// <LegoRR.exe @0048ea30>
char* strncpy(char* strDest, const char* strSource, size_t count);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fclose-fcloseall>
// <LegoRR.exe @0048eda0>
int fclose(FILE* stream);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fopen-wfopen>
// <LegoRR.exe @0048ee50>
FILE* fopen(const char* filename, const char* mode);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strncmp-wcsncmp-mbsncmp-mbsncmp-l>
// <LegoRR.exe @0048f530>
int strncmp(const char* string1, const char* string2, size_t count);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/ftell-ftelli64>
// <LegoRR.exe @0048f570>
long ftell(FILE* stream);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fseek-fseeki64>
// <LegoRR.exe @0048f720>
int fseek(FILE* stream, long offset, int origin);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fwrite>
// <LegoRR.exe @0048f7c0>
size_t fwrite(const void* buffer, size_t size, size_t count, FILE* stream);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/remove-wremove>
// <LegoRR.exe @0048f910>
int remove(const char* path);

// CRT function not found, but sets doserrno, so it may be an inlined internal if it really doesn't exist
// if pmode has the flag FILE_ATTRIBUTE_NORMAL (0x80) (_S_IWRITE 0x0080 <https://github.com/Alexpux/mingw-w64/blob/master/mingw-w64-headers/crt/sys/stat.h>)
//   the file's FILE_ATTRIBUTE_READONLY (0x1) attribute will be removed
// other
//   the file's FILE_ATTRIBUTE_READONLY (0x1) attribute will be set
// possible precursor to calling remove
// 
// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/chmod-wchmod>
// <LegoRR.exe @0048f940>
int _chmod(const char* filename, int pmode);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/mkdir-wmkdir>
// <LegoRR.exe @0048f990>
int _mkdir(const char* dirname);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/findfirst-functions>
// <LegoRR.exe @0048f9c0>
intptr_t _findfirst(const char* filespec, struct _finddata_t* fileinfo);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/findnext-functions>
// <LegoRR.exe @0048faf0>
int _findnext(intptr_t handle, struct _finddata_t* fileinfo);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/findclose>
// <LegoRR.exe @0048fc10>
int _findclose(intptr_t handle);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/getcwd-wgetcwd>
// <LegoRR.exe @0048fcc0>
char* _getcwd(char* buffer, int maxlen);

// only called internally by _getcwd
// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/getdcwd-wgetdcwd>
// <LegoRR.exe @0048fce0>
char* _getdcwd(int drive, char* buffer, int maxlen);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fread>
// <LegoRR.exe @0048fe50>
size_t fread(void* buffer, size_t size, size_t count, FILE* stream);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fgetc-fgetwc>
// <LegoRR.exe @004900e0>
int fgetc(FILE* stream);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fgets-fgetws>
// <LegoRR.exe @00490110>
char* fgets(char* str, int numChars, FILE* stream);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/stricmp-wcsicmp-mbsicmp-stricmp-l-wcsicmp-l-mbsicmp-l>
// <LegoRR.exe @004901d0>
int _stricmp(const char* string1, const char* string2);
int _strcmpi(const char* string1, const char* string2); // old name? (ID'ed by Ghidra) "_ s t r c m p i" // break up here to avoid getting replaced-all

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fullpath-wfullpath>
// <LegoRR.exe @00490260>
char* _fullpath(char* absPath, const char* relPath, size_t maxLength);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strnicmp-wcsnicmp-mbsnicmp-strnicmp-l-wcsnicmp-l-mbsnicmp-l>
// <LegoRR.exe @0049dd70>
int _strnicmp(const char* string1, const char* string2, size_t count);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/itoa-itow>
// <LegoRR.exe @0049de20>
char* itoa(int value, char* buffer, int radix);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strlwr-wcslwr-mbslwr-strlwr-l-wcslwr-l-mbslwr-l>
// <LegoRR.exe @0049ded0>
char* _strlwr(char* str);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strupr-strupr-l-mbsupr-mbsupr-l-wcsupr-l-wcsupr>
// <LegoRR.exe @0049df90>
char* _strupr(char* str);



// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fflush>
// 
// <LegoRR.exe @
int fflush(FILE* stream);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fprintf-fprintf-l-fwprintf-fwprintf-l>
// 
// <LegoRR.exe @
int fprintf(FILE* stream, const char* format [, argument ]...);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fputs-fputws>
// 
// <LegoRR.exe @
int fputs(const char* str, FILE* stream);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fputc-fputwc>
// 
// <LegoRR.exe @
int fputc(int c, FILE* stream);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fscanf-fscanf-l-fwscanf-fwscanf-l>
// <LegoRR.exe @00490330>
int fscanf(FILE* stream, const char* format [, argument ]...);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/vfscanf-vfwscanf>
int vfscanf(FILE* stream, const char* format, va_list argptr);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/vprintf-vprintf-l-vwprintf-vwprintf-l>
// 
// <LegoRR.exe @
int vprintf(const char* format, va_list argptr);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/vsprintf-vsprintf-l-vswprintf-vswprintf-l-vswprintf-l>
// 
// <LegoRR.exe @
int vsprintf(char* buffer, const char* format, va_list argptr);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/vfprintf-vfprintf-l-vfwprintf-vfwprintf-l>
// 
// <LegoRR.exe @
int vfprintf(FILE* stream, const char* format, va_list argptr);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/vfscanf-vfwscanf>
// 
// <LegoRR.exe @
int vfscanf(FILE* stream, const char* format, va_list argptr);

#pragma endregion


#pragma region /// INTERNAL ONLY? ///////////////////////

// functions that exist but are likely 

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/exit-exit-exit>
// <LegoRR.exe @0048e770>
void exit(int const status);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/quick-exit1>
// <LegoRR.exe @0048e790>
void quick_exit(int status); // identified by Ghidra has __exit, but probably quick_exit based on description

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/amsg-exit>
// <LegoRR.exe @0048f460>
void _amsg_exit(int rterrnum);

// <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/abort>
// <LegoRR.exe @004999b0>
void abort(void);


#pragma endregion
