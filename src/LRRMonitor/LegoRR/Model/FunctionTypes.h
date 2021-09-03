#pragma once

#include "../../framework.h"
#include "EnumTypes.h"


namespace lego {
#pragma region Predeclarations

struct ResourceData;
struct LevelSurfaceMap;
struct LiveObject;
struct FlockData;
struct FlockSubdata;

#pragma endregion


#pragma region Function Types


typedef BOOL (__cdecl* GameInitFunction)(void);
typedef BOOL (__cdecl* GameUpdateFunction)(float elapsed);
typedef void (__cdecl* GameCleanupFunction)(void);

typedef void (__cdecl* FileOpenCallback)(const char* filename, unsigned int fileSize, void* lpValue);

typedef void (__cdecl* ResourceDrawCallback)(ResourceData* resData, void* lpValue);
typedef void (__cdecl* ResourceSoundCallback)(const char* sampleName, ResourceData* resData, void* lpValue);

typedef void (__cdecl* MusicCallback)(void);

typedef float (__cdecl* GetSurfaceZCallback)(float x, float y, LevelSurfaceMap* surfMap);

typedef BOOL (__cdecl* LiveObjectPredicate)(LiveObject* liveObj, void* lpValue);
typedef void (__cdecl* FlocksCallback)(FlockData* flockData, FlockSubdata* subdata, void* lpValue);

typedef int (__cdecl* NERPSFunction)(int* stack);

// used by std::qsort
typedef int (__cdecl* CompareCallback)(void* item1, void* item2);


#pragma endregion
} /* namespace lego */
