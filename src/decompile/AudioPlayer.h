#pragma once


// <LegoRR.exe @0047a900>
BOOL InitDirectSound(HWND hWnd);
// <LegoRR.exe @0047aac0>
void Main_DirectSoundCleanup(void);
// <LegoRR.exe @0047ab10>
BOOL SFX_IsValidVolumeModifier(int volume);
// <LegoRR.exe @0047ab30>
int Sample_Load(char * in_filename, BOOL isStreamed, BOOL isMultiple, int volumeAdjust);
// <LegoRR.exe @0047ad90>
BOOL Sample__Next(int * out_sfxIndex);
// <LegoRR.exe @0047adc0>
BOOL Sample_CloseStreamed(int sfxIndex);
// <LegoRR.exe @0047ae40>
void Snd_SetListener3DRootFrame(IDirect3DRMFrame3 * rmFrame3);
// <LegoRR.exe @0047ae60>
void Snd_UpdateListener3D(void);
// <LegoRR.exe @0047ae80>
void Snd_UpdateListener3D_internal(IDirect3DRMFrame3 * rmFrame3);
// <LegoRR.exe @0047afd0>
void Snd_SetBuffer3DPosition(IDirectSound3DBuffer * sound3dBuffer, Vector3F * position);
// <LegoRR.exe @0047aff0>
undefined4 * FUN_0047aff0(undefined4 param_1, int param_2);
// <LegoRR.exe @0047b030>
int SFX_UnkAdjustVolumeOrPlay___0047b030(undefined4 unkMode, IDirect3DRMFrame3 * rmFrame3, int sampleIndex, BOOL modeChoice, Vector3F * opt_position);
// <LegoRR.exe @0047b2e0>
undefined FUN_0047b2e0(undefined4 param_1, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @0047b310>
void Sample_PlayAtVolume(int sampleDataIndex, int volume);
// <LegoRR.exe @0047b390>
int Sample_GetVolume(int sampleDataIndex);
// <LegoRR.exe @0047b3b0>
IDirectSoundBuffer * Sample_GetSoundBufferInstance(int sampleBufferIndex);
// <LegoRR.exe @0047b3f0>
void Sample_StopSoundBufferInstance_internal(int sampleBufferIndex);
// <LegoRR.exe @0047b420>
void FUN_0047b420(void);
// <LegoRR.exe @0047b460>
void Res_InitSoundBufferResource(IDirect3DRMFrame3 * rmFrame3, IDirectSound3DBuffer * ds3dBuffer);
// <LegoRR.exe @0047b4e0>
undefined FUN_0047b4e0(undefined4 param_1, int * param_2);
// <LegoRR.exe @0047b560>
undefined FUN_0047b560(undefined4 param_1, int param_2);
// <LegoRR.exe @0047b5a0>
uint FUN_0047b5a0(undefined4 param_1, int param_2, int param_3);
// <LegoRR.exe @0047b5f0>
uint FUN_0047b5f0(undefined4 param_1, int param_2, int * param_3);
// <LegoRR.exe @0047b650>
void FUN_0047b650(void);
// <LegoRR.exe @0047b6d0>
undefined FUN_0047b6d0(IDirect3DRMFrame3 * rmFrame3, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @0047b760>
void Audio_SetMinDistFor3DSoundsOnTopView(float minDist);
// <LegoRR.exe @0047b790>
undefined Main_SetMaxDistFor3DSounds(undefined4 maxDist);
// <LegoRR.exe @0047b7c0>
undefined Audio_SetSoundVolumeModifier(int volume);
// <LegoRR.exe @0047b7f0>
undefined FUN_0047b7f0(int param_1);
// <LegoRR.exe @0047b810>
void Audio_InitSoundBufferVolume(void);
// <LegoRR.exe @0047b840>
BOOL Sample_OpenInMemory(SampleData * sfxData, char * filename, BOOL flag_asterisk);
// <LegoRR.exe @0047b980>
BOOL Sample_CreateSoundBuffers(SampleData * param_1);
// <LegoRR.exe @0047ba50>
BOOL Sample_CopyToSoundBuffer(SampleData * param_1);
// <LegoRR.exe @0047bba0>
float10 Sample_GetDuration(int sfxIndex);
// <LegoRR.exe @0047bc30>
BOOL AudioPlayback_DoLooping__0047bc30(LPSTR filename, BOOL modeChoice, int volume);
// <LegoRR.exe @0047bce0>
BOOL AudioPlayback_Cleanup(BOOL modeChoice);
// <LegoRR.exe @0047bd60>
BOOL Snd_FUN_0047bd60(LPSTR filename, BOOL modeChoice, int volume);
// <LegoRR.exe @0047bef0>
uint FUN_0047bef0(BOOL modeChoice);
// <LegoRR.exe @0047c070>
undefined FUN_0047c070(int param_1);
// <LegoRR.exe @0047c380>
BOOL Vector3_Equals(Vector3F * a, Vector3F * b);
// <LegoRR.exe @0047c3c0>
float10 Main_SetRollOffFor3DSounds(float rollOff);
// <LegoRR.exe @0047c420>
uint Game_GetUnkMask__0047c420(void); // returns minimum volume: -10000

