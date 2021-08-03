#pragma once
#include "datatypes.h"

typedef void (__cdecl* FileOpenCallback)(char * , int , void * );

typedef void (__cdecl* MusicCallback)(void);

typedef void (__cdecl* ResourceDrawCallback)(ResourceData * resData, void * lpValue);

typedef void (__cdecl* ResourceSoundCallback)(char * sampleName, ResourceData * resData, void * lpValue);

typedef BOOL (__cdecl* LiveObjectPredicate)(LiveObject * liveObj, void * lpValue);

typedef float10 (__cdecl* GetSurfaceZCallback)(float x, float y, LevelSurfaceMap * surfMap);

typedef BOOL (__cdecl* GameInitFunction)(void);
typedef BOOL (__cdecl* GameUpdateFunction)(float elapsed);
typedef void (__cdecl* GameCleanupFunction)(void);

typedef void (__cdecl* FlocksCallback)(FlockData * flockData, FlockSubdata * subdata, void * lpValue);

typedef void (__cdecl* FileOpenCallback)(char * filename, int fileSize, void * lpValue);

// used by std::qsort
typedef int (__cdecl* CompareCallback)(void * item1, void * item2);

typedef int (__cdecl* NERPSFunction)(int * stack);


