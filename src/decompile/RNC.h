#pragma once


// <LegoRR.exe @0049ca80>
uint Rnc_Decompress(byte * srcBuffer, byte * * out_dstBuffer);
// <LegoRR.exe @0049cb00>
short Rnc_Decompress__internal(byte * srcBuffer, byte * dstBuffer);
// <LegoRR.exe @0049cba0>
short Rnc_Decompress_Method1(byte * srcBuffer, byte * dstBuffer);
// <LegoRR.exe @0049cd20>
short Rnc_Decompress_Method2(byte * srcBuffer, byte * dstBuffer);
// <LegoRR.exe @0049cf30>
byte * Rnc_BitStreamInit(byte * srcBuffer, byte * dstBuffer);
// <LegoRR.exe @0049cf80>
uint Rnc_BitStreamAdvance(byte bits);
// <LegoRR.exe @0049cff0>
int Rnc_FUN_0049cff0(byte bits);
// <LegoRR.exe @0049d050>
undefined Rnc_ReadHuffmanTable(HuffmanLeaf * table, byte bits);
// <LegoRR.exe @0049d0c0>
uint Rnc_ReadHuffman(HuffmanLeaf * table);
// <LegoRR.exe @0049d130>
uint Rnc_FUN_0049d130(void);
// <LegoRR.exe @0049d170>
int Rnc_FUN_0049d170(void);
// <LegoRR.exe @0049d210>
undefined Rnc_FUN_0049d210(HuffmanLeaf * table, byte bits);
// <LegoRR.exe @0049d250>
undefined Rnc_FUN_0049d250(HuffmanLeaf * table, byte bits);
// <LegoRR.exe @0049d2c0>
uint Rnc_MirrorBits(uint value, byte param_2);
