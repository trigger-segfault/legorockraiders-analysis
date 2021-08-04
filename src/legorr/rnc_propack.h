
#pragma once
#ifndef LEGORR__RNC_PROPACK_H
#define LEGORR__RNC_PROPACK_H

#include "Common.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>  // for BOOL typedef?


enum RncCompression : unsigned char
{
	RNC_COMPRESS_STORE = 0,
	RNC_COMPRESS_1 = 1,
	RNC_COMPRESS_2 = 2,
};

enum RncStatus : short
{
	RNC_INVALIDCOMPRESSION = -2,
	RNC_INVALIDFILE = -1,
	RNC_OK = 0,
};

int rnc_unpack(unsigned char* src, unsigned char** out_dst, size_t length, unsigned short* enc_key);
int rnc_pack(unsigned char* src, unsigned char** out_dst, size_t* ref_length, unsigned int* method, unsigned short* enc_key, unsigned short* dict_size);


// <LegoRR.exe @0049ca80>
unsigned int __cdecl Rnc_Decompress(unsigned char* srcBuffer, unsigned char** out_dstBuffer)
{
	const RNC_FILEHEADER* hdr = (RNC_FILEHEADER*)srcBuffer;

	unsigned int origSize = SwapBytes4(hdr->beOrigSize /* *(unsigned int*)(srcBuffer + 0x4) */);
	if (out_dstBuffer == nullptr)
		return origSize; // return orig data size, allowing user to query the size of uncompressed data
	
	unsigned char* dstBuffer = (unsigned char*)malloc(origSize);
	if (dstBuffer != nullptr) {
		RncStatus rstatus = Rnc_Decompress__internal(srcBuffer, dstBuffer);
		if (rstatus == RNC_OK /*0*/) {
			*out_dstBuffer = dstBuffer;
			return origSize;
		}
		free(dstBuffer);
	}
	return 0;
}


// <LegoRR.exe @0049cb00>
RncStatus __cdecl Rnc_DecompressInto(unsigned char* srcBuffer, unsigned char* dstBuffer)
{ 
	unsigned char bVar1;
	int iVar2;
	unsigned int uVar3;
	unsigned int uVar4;
	undefined4* puVar5;

	const RNC_FILEHEADER* hdr = (RNC_FILEHEADER*)srcBuffer;

	// check compression signature
	/* *(unsigned char*)(srcBuffer + 0) */
	if (strncmp(hdr->signature, "RNC", 3) != 0)
		return RNC_INVALIDFILE /*-1*/;

	switch (hdr->compression /*srcBuffer + 0x3*/) {
	case RNC_COMPRESS_STORE /*0*/:
		               /*srcBuffer + 0x12*/  /* *(unsigned int*)(srcBuffer + 0x4) */
		memcpy(dstBuffer, (void*)hdr->data , SwapBytes4(hdr->beOrigSize));
		return RNC_OK /*0*/;

	case RNC_COMPRESS_1 /*1*/:
		return Rnc_Decompress_Method1(srcBuffer, dstBuffer);
	
	case RNC_COMPRESS_2 /*2*/:
		return Rnc_Decompress_Method2(srcBuffer, dstBuffer);

	default:
		return RNC_INVALIDCOMPRESSION /*-2*/;
	}
}



#endif /* LEGORR__RNC_PROPACK_H */
