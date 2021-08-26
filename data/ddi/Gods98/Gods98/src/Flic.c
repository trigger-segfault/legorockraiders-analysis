

#include "..\Inc\Files.h"

#include <windows.h>
//#include "stdio.h"
#include <ddraw.h>

#include "..\inc\Maths.h"
#include "..\inc\DirectDraw.h"
#include "..\inc\flic.h"
#include "..\inc\errors.h"
#include "..\inc\Memory.h"

unsigned short getFlicCol(unsigned char n, FLICSTRUCT *fsp);

//extern LPDIRECTDRAW2
//extern LPDIRECTDRAW2 lpDD;
//extern IDirectDrawSurface *lpDD;

//#define FHCOL(n)  (*(fsp->fsPalette64k)+n)
#define FHCOL(n)  getFlicCol(n,fsp)

#define DoScreenConversion(fs, val) ((fs->is15bit) ? ((((val) & 0xFFE0) >> 1) | ((val) & 0x1F)) : (val))


/**********************************************************************************
******  flic variables                             ******
***********************************************************************************/

#define FLIC_FIRSTBUFFER 0
#define FLIC_SECONDBUFFER 1

/**********************************************************************************
******  flic setup                               ******
***********************************************************************************/


void Sound_StopAllSamples(void)
{

	return;
}


/**********************************************************************************
******  flic setup                               ******
***********************************************************************************/

BOOL Flic_Setup(char *filename,FLICSTRUCT **fsp, int flags) {
	int count, xsize, ysize;
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	char buff[128];
	DDSURFACEDESC2 ddsd;
	HRESULT hr=0;
	LPDIRECTDRAW4 dDraw = DirectDraw();
	LPDIRECTDRAW4 *lpDD = &dDraw;
	DDCOLORKEY ColourKey;
	// Alocate flic structure memory
	*fsp=(FLICSTRUCT *)Mem_Alloc(sizeof(FLICSTRUCT));
	ZeroMemory((*fsp),sizeof(FLICSTRUCT));
	(*fsp)->fsDisplayMode = FLICMODE_HICOLOR;
	_splitpath(filename, drive, dir, fname, ext);
	if(!Flic_LoadHeader(filename,fsp))
		return(FALSE);
	// create a DirectDrawSurface for this bitmap
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	xsize = (*fsp)->fsHeader.width;
	ysize = (*fsp)->fsHeader.height;
	ddsd.dwWidth = xsize;
	ddsd.dwHeight = ysize;
	(*fsp)->fsXsize = xsize;
	(*fsp)->fsYsize = ysize;
	if (hr = (*lpDD)->lpVtbl->CreateSurface((*lpDD), &ddsd, &(*fsp)->fsSurface, NULL)) {
		Error_Fatal(TRUE, "Failed to create surface for flic");
	}
	ColourKey.dwColorSpaceLowValue = 0;
	ColourKey.dwColorSpaceHighValue = 0;
	(*fsp)->fsSurface->lpVtbl->SetColorKey((*fsp)->fsSurface, DDCKEY_SRCBLT, &ColourKey);
	count=0;
	(*fsp)->userflags=flags;
	strcpy((*fsp)->filename,filename);
	(*fsp)->fsXc=0;
	(*fsp)->fsYc=0;
	(*fsp)->currentframe=0;
	(*fsp)->overallframe=0;
	(*fsp)->framerate = 25<<16;
	if((((*fsp)->userflags)&FLICRESIDE)==FLICMEMORY) {
		(*fsp)->pointerposition=0;
		(*fsp)->rambufferhandle=Mem_Alloc((*fsp)->fsHeader.size);
		if(!(*fsp)->rambufferhandle) {
			Error_Warn(TRUE, "No flic buffer handle");
		}
		if(((*fsp)->filehandle=File_Open(filename,"rb"))==NULL) {
			Error_Fatal(TRUE, "Could not open the flic");
		}
		File_Seek((*fsp)->filehandle,128,SEEK_SET);
		File_Read((*fsp)->rambufferhandle,(*fsp)->fsHeader.size,1,(*fsp)->filehandle);
		File_Close((*fsp)->filehandle);
	} else {
		(*fsp)->pointerposition=128;
		if(((*fsp)->filehandle=File_Open(filename,"rb"))==NULL) {
			sprintf(buff, "Not Enough Memory > %s",filename);
			Error_Warn(TRUE,buff);
			return FALSE;
		}
		File_Seek((*fsp)->filehandle,128,SEEK_SET);
	}
	(*fsp)->fsLoadBuffer=Mem_Alloc(20000);
	return TRUE;
}

/**********************************************************************************
******  flic close                               ******
***********************************************************************************/

BOOL Flic_Close(FLICSTRUCT *fsp) {
	if(!fsp)
		return FALSE;
	if((fsp->userflags & FLICRESIDE)==FLICMEMORY) {
		Mem_Free(fsp->rambufferhandle);
	} else {
		File_Close(fsp->filehandle);
	}
	if (fsp->fsLoadBuffer) {
		Mem_Free(fsp->fsLoadBuffer);
		fsp->fsLoadBuffer=NULL;
	}
	fsp=NULL;
	return TRUE;
}


/**********************************************************************************
******  flic close                               ******
***********************************************************************************/

BOOL Flic_SetFrameRate(FLICSTRUCT *fsp, int rate) {
	if(!fsp) {
		return FALSE;
	}
	if ((fsp->userflags&FLICSOUND) == FLICSOUNDON) {
		return (TRUE);
	}	
	if(rate<0) {
		rate=0;
	}
	fsp->framerate=rate;
	return TRUE;
}

/**********************************************************************************
******  flic close                               ******
***********************************************************************************/

int Flic_GetFrameRate(FLICSTRUCT *fsp)
{
	return(fsp->framerate);
}

/**********************************************************************************
******  flic load header                                                     ******
***********************************************************************************/

BOOL Flic_LoadHeader(char *filename,FLICSTRUCT **fsp)
{
        lpFile headerhandle;
		char buff[128];

        if((headerhandle=File_Open(filename,"rb"))==NULL)
        {
            sprintf(buff,"Flic File Not Found %s",filename);
			Error_Warn(TRUE, buff);
			return FALSE;
        }
        File_Seek(headerhandle,0,SEEK_SET);
        File_Read((char *)&(*fsp)->fsHeader,sizeof(FLICHEADERSTRUCT),1,headerhandle);
        if(((*fsp)->fsHeader.size)!=File_Length(headerhandle))
        {
            File_Close(headerhandle);
            sprintf(buff, "Flic File Invalid",filename);
			Error_Warn(TRUE, buff);
			return FALSE;
        }
        switch((*fsp)->fsHeader.magic)
        {
            case 0xaf11: break;
            case 0xaf12: break;
            case 0x9119: break;
            case 0xaf43: break;
            case 0x1234: break;
            default :
				{
					File_Close(headerhandle);
					sprintf(buff,"Flic File Invalid %s",filename);
					Error_Warn(TRUE, buff);
					return FALSE;
                }
        }
        File_Close(headerhandle);

        return(TRUE);
}

void flicTest(FLICSTRUCT *fsp)
{
	static n=0;
	unsigned short *sp;
	int i,j;
	

	sp = fsp->fsSPtr;
	
	n++;
	
	for(i=0;i<128;i++)
	{
		for(j=0;j<128;j++)
		{
			*(sp+(i*(fsp->fsXsize))+j) = n;
		}
	}
	
}


/**********************************************************************************
******  flic animate                                                         ******
***********************************************************************************/

//BOOL	Flic_Animate(FLICSTRUCT *fsp, RECT *dest, LPDIRECTDRAWSURFACE3 *lpBB)
BOOL	Flic_Animate(FLICSTRUCT *fsp, LPAREA2D destArea, BOOL advance, BOOL trans)
{
	DDSURFACEDESC2 dds;
	HRESULT hr;
	DDBLTFX ddBltFx;
	LPDIRECTDRAWSURFACE4 BackBuffer = DirectDraw_bSurf();
	LPDIRECTDRAWSURFACE4 *lpBB = &BackBuffer;
	RECT destRect = { (ULONG) destArea->x, (ULONG) destArea->y, (ULONG) destArea->x + (ULONG) destArea->width, (ULONG) destArea->y + (ULONG) destArea->height };
	RECT *dest = &destRect;
	int flicRetVal = FLICNOERROR;

	ZeroMemory(&dds, sizeof(dds));
   	dds.dwSize=sizeof(dds);
   	hr = fsp->fsSurface->lpVtbl->Lock(fsp->fsSurface,NULL,&dds ,DDLOCK_WAIT ,NULL);
   	fsp->fsSPtr = dds.lpSurface;
	fsp->fsPitch = dds.lPitch;
	fsp->is15bit = 0x3E0 == dds.ddpfPixelFormat.dwGBitMask;

	if (0 == fsp->currentframe) advance = TRUE;

	if( advance )
	{	
		if(((fsp->userflags)&FLICRESIDE)==FLICMEMORY)
			flicRetVal = Flic_Memory(fsp);
		else
			flicRetVal = Flic_Load(fsp);
	}
		
	hr = fsp->fsSurface->lpVtbl->Unlock(fsp->fsSurface,NULL);

	ZeroMemory(&ddBltFx, sizeof(DDBLTFX));
	ddBltFx.dwSize= sizeof (DDBLTFX);
	ddBltFx.dwFillColor=0xff00;

	hr = (*lpBB)->lpVtbl->Blt((*lpBB), dest,
		fsp->fsSurface, NULL, /*DDBLT_COLORFILL |*/ DDBLT_WAIT|(trans?DDBLT_KEYSRC:0), &ddBltFx);

	return (flicRetVal == FLICNOERROR) ? TRUE : FALSE;
}

/**********************************************************************************
******  flic memory                                                          ******
***********************************************************************************/

int     Flic_Memory(FLICSTRUCT *fsp)
{
	int flicRetVal = FLICNOERROR;

	Flic_FindChunk(fsp);
	
	if(fsp->currentframe==0) {
		fsp->ringframe=fsp->pointerposition;
	}

	fsp->currentframe++;
	fsp->overallframe++;

	if((fsp->userflags & FLICLOOPING) == FLICLOOPINGON) {
		if(fsp->currentframe==(fsp->fsHeader.frames+1)) {
			fsp->pointerposition=fsp->ringframe;
			fsp->currentframe=1;
		}
	} else {
		if (fsp->currentframe == (fsp->fsHeader.frames+1)) {
			flicRetVal = FLICFINISHED;
		}
	}
	
	return flicRetVal;
}

/**********************************************************************************
******  flic load                                                         ******
***********************************************************************************/

int	Flic_Load(FLICSTRUCT *fsp)
{
	int flicRetVal = FLICNOERROR;
	short *source;

	source=fsp->fsLoadBuffer;
	
	if(fsp->currentframe==0) {
		fsp->ringframe=fsp->pointerposition;
	}
	
	File_Read(source,16,1,fsp->filehandle);
	Flic_FindChunk(fsp);
	
	fsp->currentframe++;
	fsp->overallframe++;
	
	if((fsp->userflags&FLICLOOPING) == FLICLOOPINGON) {
		if(fsp->currentframe>(fsp->fsHeader.frames)) {
			File_Seek(fsp->filehandle,fsp->ringframe,SEEK_SET);
			fsp->pointerposition=fsp->ringframe;
			fsp->currentframe=0;
		}
	} else {
		if (fsp->currentframe>(fsp->fsHeader.frames)) {
			flicRetVal = FLICFINISHED;
		}
	}
	
	return flicRetVal;
}

/**********************************************************************************
******  flic find chunk                                                      ******
***********************************************************************************/

int Flic_FindChunk(FLICSTRUCT *fsp)
{
        unsigned short chunktype;
        int flag;
        void *source;
        int storepointer,originalpointer;

        if(((fsp->userflags)&FLICRESIDE)==FLICMEMORY)
            source=fsp->rambufferhandle;
        else
            source=fsp->fsLoadBuffer;

        originalpointer=fsp->pointerposition;

        if(((fsp->userflags)&FLICRESIDE)==FLICMEMORY)
        {
            source=(char *)source+fsp->pointerposition;
            storepointer=*(int *)(char *)source;
            flag=0;
            while((flag==0)&&((fsp->pointerposition)<(fsp->fsHeader.size)))
            {
                chunktype=(*((unsigned short *)source+2));
                switch(chunktype)
                {
				case	(unsigned short)0xf1fa:
					{
						Flic_FrameChunk(fsp);
						flag=1;
						break;
					}
					
				case	0x4b4c:
					{
						Flic_LoadPointers(fsp);
						fsp->pointerposition+=*(int *)source;
						source=(char *)source+(*(int *)source);
						storepointer+=(*(int *)source);
						break;
					}
				case	0x000b:
					{
						Flic_LoadPalette64(fsp);
						fsp->pointerposition+=*(int *)source;
						source=(char *)source+(*(int *)source);
						storepointer+=(*(int *)source);
						break;
					}
					
				default:
					{
						fsp->pointerposition+=*(int *)source;
						source=(char *)source+(*(int *)source);
						storepointer+=(*(int *)source);
						break;
					}
                }
            }
        }
        else
        {
            storepointer=(*(int *)source);
            flag=0;
            while((flag==0)&&((fsp->pointerposition)<(fsp->fsHeader.size)))
            {
                chunktype=(*((unsigned short *)source+2));
                switch(chunktype)
                {
                    case (unsigned short)0xf1fa:
						{
						Flic_FrameChunk(fsp);
                                 flag=1;
                                 break;
						}
							case	0x4b4c:
											Flic_LoadPointers(fsp);
											fsp->pointerposition+=*(int *)source;
                                 File_Seek(fsp->filehandle,fsp->pointerposition,SEEK_SET);
								 source=fsp->fsLoadBuffer;
                                 File_Read((char *)source,16,1,fsp->filehandle);
                                 storepointer+=(*(int *)source);
											break;

							case	0x000b:
											Flic_LoadPalette64(fsp);
											fsp->pointerposition+=*(int *)source;
                                 File_Seek(fsp->filehandle,fsp->pointerposition,SEEK_SET);
								 source=fsp->fsLoadBuffer;
                                 File_Read((char *)source,16,1,fsp->filehandle);
                                 storepointer+=(*(int *)source);
											break;

                    default:     fsp->pointerposition+=*(int *)source;      //this bit must load in the next
                                 File_Seek(fsp->filehandle,fsp->pointerposition,SEEK_SET);
								 source=fsp->fsLoadBuffer;
                                 File_Read((char *)source,16,1,fsp->filehandle);
                                 storepointer+=(*(int *)source);
                                 break;
                }
            }
        }
        fsp->pointerposition=storepointer+originalpointer;
        return(FLICNOERROR);
}

/**********************************************************************************
******  flic frame chunk                                                     ******
***********************************************************************************/

BOOL Flic_FrameChunk(FLICSTRUCT *fsp)
{
        int flicmaxchunk;
        char chunkcount;
        char *source;
		char buff[128];

        if(((fsp->userflags)&FLICRESIDE)==FLICMEMORY)
        {
            source=fsp->rambufferhandle;
            source += (fsp->pointerposition);
            chunkcount =*(source+6);
            source += 16;
            fsp->pointerposition+=16;
            while((chunkcount>0)&&((fsp->pointerposition)<(fsp->fsHeader.size)))
            {
				fsp->fsSource = source;
                Flic_DoChunk(fsp);
                fsp->pointerposition+=*(int *)source;
                source=(char *)source+(*(int *)source);
                chunkcount--;
            }
        }
        else
        {
			source=fsp->fsLoadBuffer;
            chunkcount=(*((char *)source+6));
            flicmaxchunk=(*(int *)source)-16;
            if(flicmaxchunk>fsp->fsLoadBufferSize)
            {
                if(fsp->fsLoadBuffer)
					Mem_Free(fsp->fsLoadBuffer);
                fsp->fsLoadBufferSize=flicmaxchunk;
                fsp->fsLoadBuffer=Mem_Alloc(fsp->fsLoadBufferSize);
                if(!fsp->fsLoadBuffer)
                {
                    sprintf(buff,"Flic Not Enough Memory");
					Error_Warn(TRUE, buff);
					return FALSE;
                }
                source=(fsp->fsLoadBuffer);
            }

            File_Read(source,flicmaxchunk,1,fsp->filehandle);
            fsp->pointerposition+=16;
            while((chunkcount>0)&&((fsp->pointerposition)<(fsp->fsHeader.size)))
            {
				fsp->fsSource = source;
                Flic_DoChunk(fsp);
                fsp->pointerposition+=*(int *)source;
                source=(char *)source+(*(int *)source);
                chunkcount--;
            }
        }
        return(TRUE);
}

/**********************************************************************************
******  sort out chunk type                                                  ******
***********************************************************************************/

int Flic_DoChunk(FLICSTRUCT* fsp)
{
        short chunktype;
        int flag=0;
        chunktype=(*((short *)(fsp->fsSource)+2));
        switch(chunktype)
        {
            case 0x0004:
                         Flic_Palette256(fsp);
                         flag=1;
                         break;
            case 0x0007:
                         Flic_DeltaWord(fsp);
                         flag=1;
                         break;
            case 0x000b:
                         Flic_Palette64(fsp);
                         flag=1;
                         break;
            case 0x000c: 
                         Flic_DeltaByte(fsp);
                         flag=1;
                         break;
            case 0x000d:
                         Flic_Black(fsp);
                         flag=1;
                         break;
            case 0x000f:
                         Flic_BrunDepack(fsp);
                         flag=1;
                         break;
            case 0x0010:
                         Flic_Copy(fsp);
                         flag=1;
                         break;

            case 0x0019:
                         Flic_BrunDepack(fsp);
                         flag=1;
                         break;
            case 0x001b:
                         Flic_DeltaWord(fsp);
                         flag=1;
                         break;
            case 0x5344:
//                         Flic_SoundChunk(fsp);
                         flag=1;
                         break;                         
            case 0x5555:
                         Flic_Unpack(fsp);
                         flag=1;
                         break;                         
            default:     break;
        }
        return(flag);
}


/**********************************************************************************
******  flic animate                                                         ******

/**********************************************************************************
******  flic find chunk                                                      ******
***********************************************************************************/

int Flic_FindMaxChunk(FLICSTRUCT *fsp)
{
        void *source;
        int max=0;
        int chunklength;
        int storepointer,storefpointer;
        char buffer[16];

        storepointer=fsp->pointerposition;
        storefpointer=File_Tell(fsp->filehandle);
        source=&buffer;
        fsp->pointerposition=128;

        while(((fsp->pointerposition)<(fsp->fsHeader.size)))
        {
            File_Seek(fsp->filehandle,fsp->pointerposition,SEEK_SET);
            File_Read(&buffer,16,1,fsp->filehandle);
            chunklength=*(int *)source;
            if(chunklength>max) max=chunklength;
            fsp->pointerposition+=chunklength;
        }

        File_Seek(fsp->filehandle,storefpointer,SEEK_SET);
        fsp->pointerposition=storepointer;
        return(max);
}


// Function to load pointers for each frame of flic
int	Flic_LoadPointers( FLICSTRUCT * fsp)
{
        int flicmaxchunk;
        char chunkcount;
        void *source;
		char buff[256];

        if(((fsp->userflags)&FLICRESIDE)==FLICMEMORY)
        {
            source=(fsp->rambufferhandle);
            source=(char *)source+fsp->pointerposition;
        }
        else
        {
            source=(fsp->fsLoadBuffer);
            flicmaxchunk=(*(int *)source);
            if(flicmaxchunk>fsp->fsLoadBufferSize)
            {
                if(fsp->fsLoadBuffer)
					Mem_Free(fsp->fsLoadBuffer);
                fsp->fsLoadBufferSize=flicmaxchunk;
                fsp->fsLoadBuffer=Mem_Alloc(fsp->fsLoadBufferSize);
                if(!fsp->fsLoadBuffer)
                {

                    sprintf(buff, "Flic Not Enough Memory");
					Error_Warn(TRUE, buff);
					return FALSE;
                }
                source=(fsp->fsLoadBuffer);
            }

            File_Seek(fsp->filehandle,fsp->pointerposition,SEEK_SET);
            File_Read(source,flicmaxchunk,1,fsp->filehandle);
         }

			chunkcount=(flicmaxchunk/8);
			source=(char *)source+6;


//			fsp->fsPointer = malloc( flicmaxchunk );

        return(FLICNOERROR);
	
}

/**********************************************************************************/
extern int Portal_PaletteNumber;
// Function to load an 8 bit palette
int	Flic_LoadPalette64( FLICSTRUCT * fsp)
{
        int flicmaxchunk;
        char *source;
		char buff[128];		  		  	

        if(((fsp->userflags)&FLICRESIDE)==FLICMEMORY)
        {
            source=(fsp->rambufferhandle);
            source=(char *)source+fsp->pointerposition;
        }
        else
        {
            source=(fsp->fsLoadBuffer);
            flicmaxchunk=(*(int *)source);
            if(flicmaxchunk>fsp->fsLoadBufferSize)
            {
                if(fsp->fsLoadBuffer)
					Mem_Free(fsp->fsLoadBuffer);
                fsp->fsLoadBufferSize=flicmaxchunk;
                fsp->fsLoadBuffer=Mem_Alloc(fsp->fsLoadBufferSize);
                if(!fsp->fsLoadBuffer)
                {
                    sprintf(buff, "Flic Not Enough Memory");
                    Error_Warn(TRUE, buff);
					return TRUE;
                }
                source=fsp->fsLoadBuffer;
            }

            File_Seek(fsp->filehandle,fsp->pointerposition,SEEK_SET);
            File_Read(source,flicmaxchunk,1,fsp->filehandle);
         }


        return(FLICNOERROR);
}






BOOL Flic_Copy(FLICSTRUCT *fsp)
{
	if(fsp->fsBitPlanes==16)
	{
		FlicCopyHiColorFlic(fsp);
		return TRUE;
	}
	if(fsp->fsDisplayMode==FLICMODE_BYTEPERPIXEL)
	{
		FlicCopyBytePerPixel(fsp);
	}
	if(fsp->fsDisplayMode==FLICMODE_HICOLOR)
	{
		FlicCopyHiColor(fsp);
	}
	
	return TRUE;
}

int Flic_GetEventRate(void)
{
	int timer;

	timer = 100;

    return(timer);
}



BOOL FlicBRunDepackBytePerPixel(FLICSTRUCT *fsp)
{

	return TRUE;
}

BOOL FlicBRunDepackHiColor(FLICSTRUCT *fsp)
{
	unsigned char *src, wrd;
	unsigned short *dst;
	unsigned short cnt,width,height,line;

//421 6259 karl

	src = fsp->fsSource;
	src += 6;

	height = fsp->fsYsize;
	line = 0;
	src++;
	while(line<height)
	{
		width = fsp->fsXsize;
		dst = (unsigned short *)(fsp->fsSPtr)+(fsp->fsPitch/2)*line;

		while(width>0)
		{
			cnt=*src++;
			
			if(cnt<128)
			{
				width -= cnt;
				wrd = *src++;
				while(cnt)
				{
					*dst++ = FHCOL(wrd);
					cnt--;
				}
			}
			else
			{
				cnt = 256-cnt;
				width -= cnt;
				while(cnt)
				{
					wrd = *src++;
					*dst++ = FHCOL(wrd);
					cnt--;
				}
			}
		}
		line++;
		src++;

	}
	
	return TRUE;
}


BOOL FlicBRunDepackHiColorFlic32k(FLICSTRUCT *fsp)
{
	signed short height,width;
	unsigned char *src;
	unsigned short wrd, cnt, tmp, line;
	unsigned short *dst;

	dst=fsp->fsSPtr;
	src=fsp->fsSource;
	src+=6;
	src++;

	line = 0;
	height = fsp->fsYsize;
	while(line<height)
	{
		width  = fsp->fsXsize;
		dst = (unsigned short *)(fsp->fsSPtr) + ((fsp->fsPitch/2) * line);
		
		while(width>0)
		{
			cnt = *src++;
			if(cnt < 128)
			{
				width -= cnt;
				wrd = *(unsigned short *)src;
				src += 2;
				tmp = ((wrd & 0xffe0)<<1);
				tmp |= wrd & 0x1f;
				wrd = tmp;
				while(cnt)
				{
					*dst++ = DoScreenConversion(fsp, wrd);
					cnt--;
				}
				
			}
			else
			{
				cnt = 256-cnt;
				width -= cnt;
				while(cnt)
				{
					tmp = *(unsigned short *)src;
					src += 2;
					wrd = ((tmp & 0xffe0)<<1);
					wrd |= tmp & 0x1f;
					*dst++ = DoScreenConversion(fsp, wrd);
					
					cnt--;
				}
			}

		}
		src++;
		line++;
	}
	
	return TRUE;
}

BOOL FlicBRunDepackHiColorFlic(FLICSTRUCT *fsp)
{

	return TRUE;
}

long UnpackM2(void *s, void *d)
{
	return 0;
}
BOOL Flic_BrunDepack(FLICSTRUCT *fsp)
{
	if(fsp->fsHeader.depth == 8)
	{
		if(fsp->fsDisplayMode==FLICMODE_BYTEPERPIXEL)
		{
			FlicBRunDepackBytePerPixel(fsp);
		}
		if(fsp->fsDisplayMode==FLICMODE_HICOLOR)
		{
			FlicBRunDepackHiColor(fsp);
		}

	}
	else if(fsp->fsHeader.depth == 16)
	{
		if(fsp->fsHeader.magic == 0xaf43)
		{
			FlicBRunDepackHiColorFlic32k(fsp);
		}
		else
		{
			FlicBRunDepackHiColorFlic(fsp);
		}
	}
	return TRUE;
}

BOOL Flic_Black(FLICSTRUCT *fsp)
{
	return TRUE;
}
BOOL Flic_DeltaByte(FLICSTRUCT *fsp)
{
	return TRUE;
}
BOOL Flic_Palette64(FLICSTRUCT *fsp)
{
	return TRUE;
}

void FlicCreateHiColorTable(FLICSTRUCT *fsp)
{
	unsigned char *src;
	unsigned short *dst, wrd, col;
	int i;

	src=(unsigned char *)&fsp->fsPalette256;
	dst=(unsigned short *)&fsp->fsPalette64k;

	for(i=0;i<256;i++)
	{
		col = src[0];
		col >>= 1;
		col <<= 11;

		wrd = src[1];
		wrd <<=5;

		col |= wrd;

		wrd = src[2];
		wrd >>= 1;

		col |= wrd;

		*dst++ = col;

		src += 3;

	}
	fsp->fsPalette64k[0]=0x00;

}

BOOL Flic_Palette256(FLICSTRUCT *fsp)
{
	unsigned char *src;
	unsigned char *dst, col;
	unsigned short cnt, indx, ccnt;

	src = fsp->fsSource;
	src+=6;

	cnt = *(unsigned short *)src;
	src+=2;

	dst = (unsigned char *)&fsp->fsPalette256;

	while(cnt)
	{
		indx = *src++;
		dst += (indx*3);
		ccnt = *src++;

		if(!ccnt)
		{
			cnt=1;
			ccnt=256;
			dst = (unsigned char *)&fsp->fsPalette256;
		}
		ccnt *= 3;
		while(ccnt)
		{
			col	= *src++;
			col >>= 2;

			*dst++ = col;
			ccnt--;
		}
		cnt--;
	}

	if(fsp->fsDisplayMode == FLICMODE_HICOLOR)
	{
	    FlicCreateHiColorTable(fsp);
	}


	return TRUE;
}

int Flic_Unpack(FLICSTRUCT *fsp)
{
	return 0;
}
void FlicCopyHiColor(FLICSTRUCT *fsp)
{
}
void FlicCopyBytePerPixel(FLICSTRUCT *fsp)
{
}
void FlicCopyHiColorFlic(FLICSTRUCT *fsp)
{
}

void FlicDeltaWordBytePerPixel(FLICSTRUCT *fsp)
{
}

void FlicDeltaWordHiColor(FLICSTRUCT *fsp)
{
	unsigned char *dst;
	unsigned char *src, w1, w2, mfval;
	unsigned short wrd, cnt, ctrl, cpy, mcnt, mflag, line, height, offs;

	dst=fsp->fsSPtr;
	height = fsp->fsYsize;

	src = fsp->fsSource;
	src+=6;

	line = 0;
	cnt = *(unsigned short *)src;
	src += 2;
	while(cnt)
	{
		dst=(unsigned char *)(fsp->fsSPtr)+((fsp->fsPitch) * line);

		ctrl = *(unsigned short *)src;
		ctrl >>= 12;
		ctrl &= 0xc;
		if(ctrl == 0xc)
		{
			wrd = *(unsigned short *)src;
			src += 2;
			wrd = 65536-wrd;

			line += wrd;
		}
		else if(ctrl == 0x4)
		{
			return;
		}
		else
		{
			mflag = 0;
			if(ctrl == 0x8)
			{
				mfval = *src;
				src += 2;
				mflag = 1;
			}
			mcnt = *(unsigned short *)src;
			src += 2;
			while(mcnt)
			{
				offs = *src++;
				dst += 2*(offs);
				cpy = *src++;
				if((cpy & 0x80))
				{
					cpy = 256 - cpy;
					w1= *src++;
					w2= *src++;
					while(cpy)
					{
						*(unsigned short *)dst = FHCOL(w1);
						dst += 2;
						*(unsigned short *)dst = FHCOL(w2);
						dst += 2;
						cpy--;
					}
				}
				else
				{
					while(cpy)
					{
						w1 = *src++;
						w2 = *src++;
						*(unsigned short *)dst = FHCOL(w1);
						dst += 2;
						*(unsigned short *)dst = FHCOL(w2);
						dst += 2;
						
						cpy--;
					}
					
				}
				mcnt--;
			}
			if(mflag)
				*(unsigned short *)dst = FHCOL(mfval);
			cnt--;
			line++;
		}
	}
}

void FlicDeltaWordHiColorDZ(FLICSTRUCT *fsp)
{
}

void FlicDeltaWordHiColorFlic32k(FLICSTRUCT *fsp)
{
	unsigned char *dst;
	unsigned char *src;
	unsigned short wrd, cnt, ctrl, cpy, mcnt, tmp, mflag, mfval, line, height;

	dst=fsp->fsSPtr;
	height = fsp->fsYsize;

	src = fsp->fsSource;
	src+=6;

	line = 0;
	cnt = *(unsigned short *)src;
	src += 2;
	while(cnt)
	{
		dst=(unsigned char *)(fsp->fsSPtr)+((fsp->fsPitch) * line);

		ctrl = *(unsigned short *)src;
		ctrl >>= 12;
		ctrl &= 0xc;
		if(ctrl == 0xc)
		{
			wrd = *(unsigned short *)src;
			src += 2;
			wrd = 65536-wrd;

			line += wrd;

		}
		else if(ctrl == 0x4)
		{
			return;
		}
		else
		{
			mflag = 0;
			if(ctrl == 0x8)
			{
				mfval = DoScreenConversion(fsp, *(unsigned short *)src);
				src += 2;
				mflag = 1;
			}
			mcnt = *(unsigned short *)src;
			src += 2;
			while(mcnt)
			{
				dst += 2*(*src++);
				cpy = *src++;
				if((cpy & 0x80))
				{
					tmp = *(unsigned short *)src;
					src += 2;
					wrd = ((tmp & 0xffe0)<<1);
					wrd |= tmp & 0x1f;
					cpy = 256 - cpy;
					while(cpy)
					{
						*(unsigned short *)dst = DoScreenConversion(fsp, wrd);
						dst += 2;
						cpy--;
					}
				}
				else
				{
					while(cpy)
					{
						tmp = *(unsigned short *)src;
						src += 2;
						wrd = ((tmp & 0xffe0)<<1);
						wrd |= tmp & 0x1f;
						*(unsigned short *)dst = DoScreenConversion(fsp, wrd);
						dst += 2;
						
						cpy--;
					}
					
				}
				mcnt--;
			}
			if(mflag)
				*dst = (char)mfval;
			line ++;
			cnt--;
		}
	}
}

void FlicDeltaWordHiColorFlic(FLICSTRUCT *fsp)
{
}

BOOL Flic_DeltaWord(FLICSTRUCT *fsp)
{
	if(fsp->fsHeader.depth == 8)
	{
		if(fsp->fsDisplayMode==FLICMODE_BYTEPERPIXEL)
		{
		    FlicDeltaWordBytePerPixel(fsp);
		}
		if(fsp->fsDisplayMode==FLICMODE_HICOLOR)
		{
		    FlicDeltaWordHiColor(fsp);
		}
	}
	else
	{
		if(fsp->fsHeader.depth == 16)
		{
			if(fsp->fsHeader.magic == 0x1234)
			{
			    FlicDeltaWordHiColorDZ(fsp);
			}
			else if(fsp->fsHeader.magic == 0xaf43)
			{
			    FlicDeltaWordHiColorFlic32k(fsp);
			}
			else
			{
                FlicDeltaWordHiColorFlic(fsp);
			}
		}
	}
	return TRUE;
}

unsigned short getFlicCol(unsigned char n, FLICSTRUCT *fsp)
{
	unsigned short ret;
	unsigned short *ctab;

	ctab = fsp->fsPalette64k;

	ret = ctab[n];


	return ret;

}

ULONG Flic_GetWidth(FLICSTRUCT *fsp){

	return fsp->fsXsize;
}

ULONG Flic_GetHeight(FLICSTRUCT *fsp){

	return fsp->fsYsize;
}


