#pragma once


// <LegoRR.exe @004790b0>
void ReservedPool<CFGProperty>__Init(void);
// <LegoRR.exe @004790e0>
void ReservedPool<CFGProperty>__Cleanup(void);
// <LegoRR.exe @00479120>
CFGProperty * CFG_Open(char * filename);
// <LegoRR.exe @00479210>
char * CFG_JoinPath(char * keyPath1, char * keyPath2, ...);
// <LegoRR.exe @004792b0>
CFGProperty * CFG_GetBlockFirstChild(CFGProperty * root, char * keyPath);
// <LegoRR.exe @004792e0>
CFGProperty * CFG_NextFlatProperty(CFGProperty * prop);
// <LegoRR.exe @00479310>
char * CFG_CopyPropertyValue(CFGProperty * prop, char * keyPath);
// <LegoRR.exe @00479370>
char * CFG_GetPropertyValue(CFGProperty * root, char * keyPath);
// <LegoRR.exe @00479390>
uint CFG_GetPropertyBool(CFGProperty * prop, char * keyPath);
// <LegoRR.exe @004793d0>
float10 CFG_GetPropertyRadians(CFGProperty * root, char * keyPath);
// <LegoRR.exe @00479430>
BOOL CFG_GetPropertyRGBF(CFGProperty * root, char * keyPath, float * out_r, float * out_g, float * out_b);
// <LegoRR.exe @00479500>
void CFG_Close(CFGProperty * root);
// <LegoRR.exe @00479530>
CFGProperty * ReservedPool<CFGProperty>__Next(CFGProperty * previous);
// <LegoRR.exe @00479580>
void ReservedPool<CFGProperty>__Release(CFGProperty * prop);
// <LegoRR.exe @004795a0>
CFGProperty * CFG_GetProperty(CFGProperty * prop, char * keyPath);
// <LegoRR.exe @00479750>
void ReservedPool<CFGProperty>__Alloc(void);

