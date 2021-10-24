#pragma once
#include "datatypes.h"



typedef bool32 (__cdecl* AnimCloneWalkTreeCallback)(IDirect3DRMFrame3*, void*);
typedef void (__cdecl* ContainerActivityCallback)(Container*, void*);
typedef void (__cdecl* ContainerSoundTriggerCallback)(char*, Container*, void*);
typedef void (__cdecl* ContainerTriggerFrameCallback)(Container*, void*);
typedef bool32 (__cdecl* ContainerWalkTreeCallback)(IDirect3DRMFrame3*, void*);
typedef void (__cdecl* DrawPixelFunc)(sint32, sint32, uint32);
typedef void (__cdecl* ElectricFenceEnumerateCallback)(BlockElectricFence*, void*);
typedef void (__cdecl* FileLoadCallback)(char*, uint32, void*);
typedef void (__cdecl* FlocksCallback)(Flocks*, FlocksItem*, void*);
typedef float10 (__cdecl* GetSurfaceZFunc)(real32, real32, Map3D*);
typedef bool32 (__cdecl* InfoEnumerateCallback)(InfoMessageInstance*, void*);
typedef bool32 (__cdecl* LevelIdentifierCallback)(LevelInfo*, void*);
typedef bool32 (__cdecl* LwsFindSFXIDFunc)(char*, uint32*);
typedef sint32 (__cdecl* LwsPlaySample3DFunc)(IDirect3DRMFrame3*, uint32, bool32, bool32, Vector3F*);
typedef bool32 (__cdecl* LwsSoundEnabledFunc)(void);
typedef bool32 (__cdecl* MainStateInitialise)(void);
typedef bool32 (__cdecl* MainStateMainLoop)(real32);
typedef void (__cdecl* MainStateShutdown)(void);
typedef void (__cdecl* MainWindowCallback)(HWND, UINT, WPARAM, LPARAM);
typedef void (__cdecl* MenuItemCycleCallback)(sint32);
typedef void (__cdecl* MenuItemRealSliderCallback)(real32);
typedef void (__cdecl* MenuItemSliderCallback)(sint32);
typedef void (__cdecl* MenuItemTriggerCallback)(void);
typedef void (__cdecl* MeshRenderCallback)(Mesh*, void*, Viewport*);
typedef bool32 (__cdecl* NERPsBlockPointerCallback)(BlockPointer*, uint32, uint32, void*);
typedef sint32 (__cdecl* NERPsFunction)(sint32*);
typedef bool32 (__cdecl* SearchLiveObjectCallback)(LegoObject*, void*);
typedef void (__cdecl* SoundCDStopCallback)(void);
typedef void (__cdecl* XYCallback)(sint32, sint32);

