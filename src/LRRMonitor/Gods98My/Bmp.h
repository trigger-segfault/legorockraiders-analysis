#pragma once

#include "../framework.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

#pragma pack(push, 1)

typedef struct BMP_Header {

	/*00,2*/ char	bmp_str[2];
	/*02,4*/ DWORD	file_size;
	/*06,2*/ WORD	res1;
	/*08,2*/ WORD	res2;
	/*0a,4*/ DWORD	img_offset;

	/*0e,4*/ DWORD	img_header_size;
	/*12,4*/ DWORD	wid;
	/*16,4*/ DWORD	hgt;
	/*1a,2*/ WORD	planes;				// Always 1
	/*1c,2*/ WORD	bits_per_pixel;
	/*1e,4*/ DWORD	compression;
	/*22,4*/ DWORD	comp_img_size;
	/*26,4*/ DWORD	horz_res;			// pels/m
	/*2a,4*/ DWORD	vert_res;			// pels/m
	/*2e,4*/ DWORD	colours;
	/*32,4*/ DWORD	important_colours;
	/*36*/
} BMP_Header, *lpBMP_Header;
static_assert(sizeof(BMP_Header) == 0x36, "");

#pragma pack(pop)

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @00489ef0>
void __cdecl BMP_Parse(const void* data, unsigned long size, OUT D3DRMIMAGE* istruct);

// <LegoRR.exe @0048a030>
void __cdecl BMP_Cleanup(D3DRMIMAGE* istruct);

#pragma endregion

}
