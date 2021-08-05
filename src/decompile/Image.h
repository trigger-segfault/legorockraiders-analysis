#pragma once


// <LegoRR.exe @0047d6d0>
void ReservedPool<ImageBMP>__Init(void);
// <LegoRR.exe @0047d6f0>
void ReservedPool<ImageBMP>__Cleanup(void);
// <LegoRR.exe @0047d730>
void ReservedPool<ImageBMP>__Release(ImageBMP * image);
// <LegoRR.exe @0047d750>
BOOL Image_FUN_0047d750(IDirectDrawSurface4 * ddSurface, DDSURFACEDESC2 * surfaceDesc);
// <LegoRR.exe @0047d7e0>
BOOL Image_FUN_0047d7e0(int param_1, DDSURFACEDESC2 * surfaceDesc);
// <LegoRR.exe @0047d9c0>
int countBits(uint value);
// <LegoRR.exe @0047d9e0>
int firstBit(uint value);
// <LegoRR.exe @0047da00>
undefined Image_ReorderPixelsBPP(DDSURFACEDESC2 * surfaceDesc);
// <LegoRR.exe @0047dac0>
BOOL Image_FUN_0047dac0(int param_1, DDSURFACEDESC2 * surfaceDesc);
// <LegoRR.exe @0047dc90>
ImageBMP * Image_LoadBMP(char * filename, undefined4 param_2, undefined4 param_3);
// <LegoRR.exe @0047de50>
uint packRGB(byte red, byte green, byte blue);
// <LegoRR.exe @0047de80>
undefined Image_SetFirstColorAsKey(ImageBMP * image);
// <LegoRR.exe @0047deb0>
void Image_unkFogFromFloat__0047deb0(ImageBMP * image, float red_low, float green_low, float blue_low, float red_high, float green_high, float blue_high);
// <LegoRR.exe @0047df70>
undefined Image_Blt__0047df70(ImageBMP * bitmap, float * param_2, float * param_3, float * param_4);
// <LegoRR.exe @0047e120>
void * Image_Lock(ImageBMP * image, uint * out_length, uint * out_bitsPerPixel);
// <LegoRR.exe @0047e190>
undefined Image_Unlock(ImageBMP * image);
// <LegoRR.exe @0047e1b0>
uint Image_GetLastColor24(ImageBMP * image);
// <LegoRR.exe @0047e210>
uint Image_GetUpperBitMask(ImageBMP * image);
// <LegoRR.exe @0047e260>
BOOL Image_FUN_0047e260(ImageBMP * image, int param_2, int param_3);
// <LegoRR.exe @0047e310>
int * * ReservedPool<ImageBMP>__NextImage(int * directDrawSurface4, int width, int height, uint firstColor, uint lastColor);
// <LegoRR.exe @0047e380>
void ReservedPool<ImageBMP>__Alloc(void);
// <LegoRR.exe @0047e3f0>
void Image_Cleanup_FUN_0047e3f0(void);
// <LegoRR.exe @0047e450>
uint unpackNativeRGB(IDirectDrawSurface4 * ddSurface, undefined4 rgbColor);
// <LegoRR.exe @0047e590>
void unpackRGB(uint rgbColor, byte * out_red, byte * out_green, byte * out_blue);
// <LegoRR.exe @0047e5c0>
undefined Image_CreateCapture(ImageBMP * image, int captureWidth, int captureHeight);
// <LegoRR.exe @0047e6a0>
undefined ReservedPool<ImageBMP>__NextCapture(ImageBMP * image, IUnknown * directDrawSurface, int width, int height, uint firstColor, uint lastColor);
// <LegoRR.exe @0047e700>
undefined FUN_0047e700(int * * param_1, char * param_2);
