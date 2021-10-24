# C Runtime dependencies in LegoRR

## Leave as is

Functions that perform operations without relying on external functions or global variables.

```cpp
// (effectively floor(float10), but less expensive)
/// XREF: [300]
// <LegoRR.exe @0048e320 - 0048e347>
long long __stdcall __ftol(float10 x) { return (long long)ROUND(x); }

/// LEGORR: Front(Save), Lego, LegoObject, NERPs, RadarMap, Vehicle
/// GODS: Wad
// <LegoRR.exe @0048e510 - 0048e53f>
void * __stdcall _alloca4k(size_t size);

/// LEGORR: LegoObject, Vehicle
/// GODS: Maths
// <LegoRR.exe @0048eb30>
int __cdecl _finite(double x) { return (*((unsigned short*)&x + 3) & 0x7ff0) != 0x7ff0; }
```


***


## Used by LegoRR

Functions directly called from LegoRR game code.

### Used by LegoRR (floating point math)

```cpp
/// XREF: [163]
/// LEGORR: Advisor, Building, Front(Menu), Lego, LightEffects, Panels, Rewards, Stats, Vehicle, Weapons
/// GODS: Config, Containers Lws, Mesh
// <LegoRR.exe @0048dc40>
float10 __cdecl atof(const char *str);

// (wrapper that stores in double, then calls acos functions)
/// LEGORR: Collision [1], LegoObject [2]
/// GODS: Maths
// <LegoRR.exe @0048e350>
float10 __cdecl acos(float10 x);

// (no double/float4 wrapper substitute... but we can wrap the single use in LegoRR)
// 004484db d9 5c 24 60    FSTP  dword ptr [ESP + elapsed]
// 004484df d9 44 24 60    FLD   dword ptr [ESP + elapsed]
// 004484e3 dd 05 a0 f4    FLD   qword ptr [DOUBLE_0049f4a0] ; = 1.5707963705062866
//          49 00
// 004484e9 e8 7c 5f 04    CALL  fmod    ; float10 fmod(float10 x, float10 y)
//          00
/// LEGORR: LegoObject [1]
/// GODS: Lws, Mesh
// <LegoRR.exe @0048e46a>
float10 __cdecl fmod(float10 x, float10 y);

/// LEGORR: HelpWindow, Panels, ScrollInfo
/// GODS: Images(Image_DisplayScaled)
// <LegoRR.exe @0048e540>
float10 __cdecl floor(double x);

/// LEGORR: Camera
// <LegoRR.exe @0048e894>
float10 __cdecl sqrt(double x);

/// LEGORR: Camera(Camera_Update)
// <LegoRR.exe @0048e940>
float10 __cdecl fabs(double x);

/// LEGORR: ScrollInfo
// <LegoRR.exe @0048eba0>
float10 __cdecl ceil(double x);
```


### Used by LegoRR (system management)

```cpp
/// XREF: [478]
// <LegoRR.exe @0048de40>
void __cdecl free(void *buffer);

/// XREF: [300]
// <LegoRR.exe @0048de90>
void * __cdecl malloc(size_t size);

/// LEGORR: Credits, Front, Lego, LegoObject, ObjectRecall, Rewards
/// GODS: Containers, Lws, Mesh
// <LegoRR.exe @0048df40>
void * __cdecl realloc(void *memblock, size_t size);

/// LEGORR: Lego(Lego_Exit)
/// GODS: Files(Main_Exit)
// <LegoRR.exe @0048e770>
void __cdecl exit(int status);
```


### Used by LegoRR (general)

```cpp
/// XREF: [184]
// <LegoRR.exe @0048dca0>
int __cdecl sprintf(char *buffer, const char *format, ...);

/// LEGORR: Building
/// GODS: Containers, Lws, Main
// <LegoRR.exe @0048dd10>
char * __cdecl strstr(char *str, const char *strSearch);

/// XREF: [239]
// <LegoRR.exe @0048de30>
int __cdecl atoi(const char *str);

/// LEGORR: AITask, Lego, LegoObject, Water
/// GODS: Containers
// <LegoRR.exe @0048e0e0>
void __cdecl qsort(void *base, size_t number, size_t width, QsortCompare compare);

/// LEGORR: Lego(Lego_LoadLevel)
// <LegoRR.exe @0048e420>
void __cdecl srand(unsigned int seed);

/// LEGORR: Front, Smoke
/// GODS: Maths
// <LegoRR.exe @0048e430>
int __cdecl rand(void);

/// LEGORR: Front, ToolTip
/// GODS: Containers, Files, Fonts, TextWindow, Utils
// <LegoRR.exe @0048e4a0>
int __cdecl vsprintf(char *buffer, const char *format, va_list argptr);

/// LEGORR: Lego(Lego_Initialise, Lego_Input_UpdateTyping)
/// GODS: Utils
// <LegoRR.exe @0048e640>
int __cdecl toupper(int c);

/// LEGORR: LegoObject, ObjectRecall
/// GODS: Lwt
// <LegoRR.exe @0048ea30>
char * __cdecl strncpy(char *_Dest, const char *_Source, size_t _Count);

/// LEGORR: NERPsFile
// <LegoRR.exe @0048eb50>
void __cdecl sscanf(char *buffer, const char *format, ...);

/// XREF: [110]
// <LegoRR.exe @004901d0>
int __cdecl _stricmp(const char *_Str1, const char *_Str2);

/// LEGORR: Front(Menu), Lego, Objective
/// GODS: Config, Containers, Lws, Lwt, Utils
// <LegoRR.exe @0049dd70>
int __cdecl _strnicmp(const char *_Str1, const char *_Str2, size_t _MaxCount);

/// LEGORR: Interface, Priorities
// <LegoRR.exe @0049de20>
char * __cdecl itoa(int value, char *buffer, int radix);
```


***


## Used by Gods98

Functions directly called *only* from LegoRR engine code.

These can safely be ignored, with the entirely of Gods98 already being implemented.

```cpp
/// GODS: Movie
// <LegoRR.exe @0048eca0>
long long __stdcall __alldiv(long long x, long long y);

/// GODS: Animation, Movie
// <LegoRR.exe @0048ed90>
void * __cdecl operator_new(size_t size);

/// GODS: Files, Movie, 3DSound, Wad
// <LegoRR.exe @0048eda0>
int __cdecl fclose(FILE *stream);

/// GODS: Files, Movie, 3DSound, Wad
// <LegoRR.exe @0048ee50>
FILE * __cdecl fopen(const char *filename, const char *mode);

/// GODS: Containers, Fonts, Lws, TextWindow, Utils
// <LegoRR.exe @0048f490>
int __cdecl _isctype(int c, unsigned int desc);

/// GODS: Compress, Files, Utils
// <LegoRR.exe @0048f530>
int __cdecl strncmp(const char *_Str1, const char *_Str2, size_t _MaxCount);

/// GODS: Files, 3DSound
// <LegoRR.exe @0048f570>
long __cdecl ftell(FILE *stream);

/// GODS: Files, 3DSound, Wad
// <LegoRR.exe @0048f720>
int __cdecl fseek(FILE *stream, long offset, int origin);

/// GODS: Files, Movie, 3DSound, Wad
// <LegoRR.exe @0048f7c0>
size_t __cdecl fwrite(const void *buffer, size_t size, size_t count, FILE *stream);

/// GODS: Files
// <LegoRR.exe @0048f910>
int __cdecl remove(const char *filename);

/// GODS: Files
// <LegoRR.exe @0048f940>
int __cdecl _chmod(const char *filename, int pmode);

/// GODS: Files
// <LegoRR.exe @0048f990>
int __cdecl _mkdir(const char *dirname);

/// GODS: Files
// <LegoRR.exe @0048f9c0>
intptr_t __cdecl _findfirst32(const char *filename, _finddata32_t *fileinfo);

/// GODS: Files
// <LegoRR.exe @0048faf0>
int __cdecl _findnext32(intptr_t handle, _finddata32_t *fileinfo);

/// GODS: Files
// <LegoRR.exe @0048fc10>
int __cdecl _findclose(intptr_t handle);

/// GODS: Files
// <LegoRR.exe @0048fcc0>
char * __cdecl _getcwd(char *out_buffer, int maxlen);

/// GODS: Files, Wad
// <LegoRR.exe @0048fe50>
size_t __cdecl fread(void *out_buffer, size_t size, size_t count, FILE *stream);

/// GODS: Files
// <LegoRR.exe @004900e0>
int __cdecl fgetc(FILE *stream);

/// GODS: Files
// <LegoRR.exe @00490110>
char * __cdecl fgets(char *str, int numChars, FILE *stream);

/// GODS: Files
// <LegoRR.exe @00490190>
int __cdecl vfprintf(FILE *stream, const char *format, va_list argptr);

/// GODS: Files
// <LegoRR.exe @00490260>
char * __cdecl _fullpath(char *absPath, const char *relPath, unsigned int maxLength);

/// GODS: Files
// <LegoRR.exe @00490330>
int __cdecl fscanf(FILE *stream, const char *format, ...);

/// GODS: Flic, Lwt, Mesh
// <LegoRR.exe @00490350>
void __cdecl _splitpath(char *path, char *drive, char *dir, char *fname, char *ext);

/// GODS: Containers
// <LegoRR.exe @0049ded0>
char * __cdecl _strlwr(char *str);

/// GODS: Main
// <LegoRR.exe @0049df90>
char * __cdecl _strupr(char *str);
```


***


## Global variables

Direct global variable access (which is only used by inlined *is&lt;ctype&gt;* functions).

These are also only used by Gods98, and can be ignored.

```cpp

/// GODS: Containers, Fonts, Lws, TextWindow, Utils
// <LegoRR.exe @004b0f74>
extern int _pcharwidth; // = 1

/// GODS: Containers, Fonts, Lws, TextWindow, Utils
// <LegoRR.exe @004b0d68>
extern unsigned short * _pctype; // -> _wctype[256]

/// GODS: Containers, Fonts, Lws, TextWindow, Utils
// <LegoRR.exe @004b0d72>
extern unsigned short _wctype[256];
```
