#ifndef _GODS98_BMP_H_
#define _GODS98_BMP_H_

#pragma pack (push)
#pragma pack (1) 

typedef struct BMP_Header {

	char	bmp_str[2];
	DWORD	file_size;
	WORD	res1;
	WORD	res2;
	DWORD	img_offset;

	DWORD	img_header_size;
	DWORD	wid;
	DWORD	hgt;
	WORD	planes;				// Always 1
	WORD	bits_per_pixel;
	DWORD	compression;
	DWORD	comp_img_size;
	DWORD	horz_res;			// pels/m
	DWORD	vert_res;			// pels/m
	DWORD	colours;
	DWORD	important_colours;

} BMP_Header, *lpBMP_Header;

#pragma pack (pop)

VOID BMP_Parse(LPVOID data, ULONG size, LPD3DRMIMAGE istruct);
VOID BMP_Cleanup(LPD3DRMIMAGE istruct);

#endif // _GODS98_BMP_H_
