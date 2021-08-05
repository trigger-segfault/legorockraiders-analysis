#pragma once


// <LegoRR.exe @0047a1a0>
ImageFont * Image_LoadFont(char * filename);
// <LegoRR.exe @0047a410>
undefined FUN_0047a410(ImageFont * font, uint * param_2, int * param_3, byte * param_4, undefined4 * param_5);
// <LegoRR.exe @0047a440>
void FUN_0047a440(ImageFont * font, int param_2, int param_3, char * format, ...);
// <LegoRR.exe @0047a470>
undefined FUN_0047a470(undefined4 * param_1, int param_2, int param_3, byte * param_4, undefined4 * param_5);
// <LegoRR.exe @0047a4a0>
uint FUN_0047a4a0(ImageFont * font, int param_2, int param_3, int param_4, int * param_5, byte * param_6, undefined4 * param_7);
// <LegoRR.exe @0047a730>
int Font_MeasureCharWidthEx(ImageFont * font, int param_2, int param_3, char c, BOOL param_5);
// <LegoRR.exe @0047a7e0>
int Font_MeasureCharWidth(ImageFont * font, char c);
// <LegoRR.exe @0047a800>
undefined4 Font_GetField_be4(ImageFont * font);
// <LegoRR.exe @0047a810>
void ReservedPool<ImageFont>__Release(ImageFont * font);
// <LegoRR.exe @0047a840>
ImageFont * ReservedPool<ImageFont>__Next(ImageBMP * bitmap);
// <LegoRR.exe @0047a880>
void ReservedPool<ImageFont>__Alloc(void);

