#pragma once


// <LegoRR.exe @00489ef0>
void * Image_LoadBMP__internal(BITMAP_FILE_INFO_STRUCT * bmpData, uint length, D3DRMIMAGE * d3drmImage);
// <LegoRR.exe @0048a030>
undefined BMP_free(D3DRMIMAGE * d3dImage);
// <LegoRR.exe @0048a050>
void DirectX_FormatError(char * name, char * description);
// <LegoRR.exe @0048a090>
uint D3DError(HRESULT result, int moduleIndex, undefined4 sourceFile, undefined4 lineNumber);

