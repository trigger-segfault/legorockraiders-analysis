#pragma once
#include "datatypes.h"



typedef bool32 (__cdecl* AITask_RunThroughListsCallback)(AITask*, void*);
typedef bool32 (__cdecl* AnimCloneWalkTreeCallback)(IDirect3DRMFrame3*, void*);
typedef void (__cdecl* ContainerActivityCallback)(Container*, void*);
typedef void (__cdecl* ContainerSoundTriggerCallback)(char*, Container*, void*);
typedef void (__cdecl* ContainerTriggerFrameCallback)(Container*, void*);
typedef bool32 (__cdecl* ContainerWalkTreeCallback)(IDirect3DRMFrame3*, void*);
typedef void (__cdecl* DrawPixelFunc)(sint32, sint32, uint32);
typedef void (__cdecl* ElectricFence_RunThroughListsCallback)(BlockElectricFence*, void*);
typedef void (__cdecl* FileLoadCallback)(char*, uint32, void*);
typedef void (__cdecl* FlocksCallback)(Flocks*, FlocksItem*, void*);
typedef float10 (__cdecl* GetWorldZCallback)(real32, real32, Map3D*);
typedef bool32 (__cdecl* InfoEnumerateCallback)(InfoMessageInstance*, void*);
typedef bool32 (__cdecl* LegoObject_RunThroughListsCallback)(LegoObject*, void*);
typedef bool32 (__cdecl* LevelLink_RunThroughLinksCallback)(LevelLink*, void*);
typedef bool32 (__cdecl* LwsFindSFXIDFunc)(char*, uint32*);
typedef sint32 (__cdecl* LwsPlaySample3DFunc)(IDirect3DRMFrame3*, uint32, bool32, bool32, Vector3F*);
typedef bool32 (__cdecl* LwsSoundEnabledFunc)(void);
typedef bool32 (__cdecl* MainStateInitialise)(void);
typedef bool32 (__cdecl* MainStateMainLoop)(real32);
typedef void (__cdecl* MainStateShutdown)(void);
typedef void (__cdecl* MainWindowCallback)(HWND, UINT, WPARAM, LPARAM);
typedef void (__cdecl* MenuItem_CycleCallback)(sint32);
typedef void (__cdecl* MenuItem_RealSliderCallback)(real32);
typedef void (__cdecl* MenuItem_SelectCallback)(real32, sint32);
typedef void (__cdecl* MenuItem_SliderCallback)(sint32);
typedef void (__cdecl* MenuItem_TriggerCallback)(void);
typedef void (__cdecl* MeshRenderCallback)(Mesh*, void*, Viewport*);
typedef bool32 (__cdecl* NERPsBlockPointerCallback)(BlockPointer*, uint32, uint32, void*);
typedef sint32 (__cdecl* NERPsFunction)(sint32*);
typedef void (__cdecl* SoundCDStopCallback)(void);
typedef void (__cdecl* XYCallback)(sint32, sint32);

