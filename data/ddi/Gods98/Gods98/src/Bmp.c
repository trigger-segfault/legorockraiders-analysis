#include <d3drmwin.h>

#include "..\Inc\Standard.h"
#include "..\Inc\Memory.h"
#include "..\Inc\Bmp.h"

VOID BMP_Parse(LPVOID data, ULONG size, LPD3DRMIMAGE istruct){

	SLONG i;
	UCHAR swap;
	LPD3DRMPALETTEENTRY pal;
	lpBMP_Header header = data;
	ULONG colourCount=0, bpp;

	if (8 == header->bits_per_pixel) {
		if (!(colourCount = header->colours)) colourCount = 256;
		pal = Mem_Alloc(sizeof(D3DRMPALETTEENTRY) * 256);		// Always create a table 256 long.
		memset(pal, 0, sizeof(D3DRMPALETTEENTRY) * 256);
		memcpy(pal, ((LPUCHAR)data) + sizeof(BMP_Header), colourCount * sizeof(D3DRMPALETTEENTRY));
		istruct->rgb = FALSE;
		istruct->red_mask = 0xfc;
		istruct->green_mask = 0xfc;
		istruct->blue_mask = 0xfc;
		istruct->alpha_mask = 0xfc;
		istruct->palette_size = colourCount;
		for (i=0 ; i<(int)colourCount ; i++) {
			swap = pal[i].red;								// convert palette to RGB from BGR
			pal[i].red = pal[i].blue;
			pal[i].blue = swap;
		}
		istruct->palette = pal;								// place in image structure
	} else {
		istruct->rgb = TRUE;
		istruct->palette_size = 0;
		istruct->palette = NULL;
	}

	istruct->width = (int)header->wid;
	istruct->height = header->hgt;
	istruct->depth = header->bits_per_pixel;

	switch (istruct->depth)
	{
	case 8:  bpp = 1; break;
	case 15:
	case 16: bpp = 2; break;
	case 24: bpp = 3; break;
	case 32: bpp = 4; break;
	default: bpp = 0;
	}
	istruct->bytes_per_line = ((istruct->width * bpp) + 3) & ~3;

//	istruct->buffer1 = &((LPUCHAR) data)[sizeof(BMP_Header) + (colourCount * sizeof(D3DRMPALETTEENTRY))];
	istruct->buffer1 = &((LPUCHAR) data)[header->img_offset];

	istruct->buffer2 = 0;

	istruct->aspectx = istruct->aspecty = 1;
}

VOID BMP_Cleanup(LPD3DRMIMAGE istruct){

	if (istruct->palette) Mem_Free(istruct->palette);
}