
#ifndef _GODS98_FLIC_H
#define _GODS98_FLIC_H

#include "Files.h"

/**********************************************************************************
****** a flic player                             ******
***********************************************************************************/

    #ifndef FLICHEADER

#define FLICTIMERTICKSPERSECOND 70
#define MAXFLICS 30

#define FLICRESIDE          (1<<0)
#define FLICDISK            (0<<0)
#define FLICMEMORY          (1<<0)
#define FLICLOOPING         (1<<1)
#define FLICLOOPINGON       (1<<1)
#define FLICLOOPINGOFF      (0<<1)
#define FLICCATCHUP         (1<<2)
#define FLICCATCHUPON       (1<<2)
#define FLICCATCHUPOFF      (0<<2)
#define FLICSOUND           (1<<3)
#define FLICSOUNDON         (0<<3)
#define FLICSOUNDOFF        (1<<3)

/*
#define File_Open fopen
#define File_Seek fseek
#define File_Read fread
#define File_Close fclose
#define File_Tell ftell
*/

//int File_Length(lpFile fp);

enum
{
	FLICMODE_BYTEPERPIXEL,	//  EQU   0       ;BYTE PER PIXEL
	FLICMODE_MODEX,	//     EQU   1       ;MODEX
	FLICMODE_PLANAR,		//    EQU   2       ;PLANAR MODE
	FLICMODE_TRUECOLOR,		//   EQU   3       ;TRUE COLOR MODE
	FLICMODE_HICOLOR,	//   EQU   4       ;HI COLOR MODE
};


typedef struct
{
	int PWidth;
} PORTAL;


//#define FLICSETPALETTE      (1<<1)

#define FLICERRORSTART 3000

#define FLICFINISHED 1
#define FLICNOERROR  0
#define FLICERROR   -1

enum{
     FLICINVALIDHANDLE=FLICERRORSTART,
     FLICNOMOREHANDLES,
     FLICNOTENOUGHMEMORY,
     FLICINVALIDFILE,
     FLICFILENOTFOUND,
     FLICFILEERROR,
     FLICOFFPORTAL,
     FLICFRAMEDOESNOTEXIST,
     FLICREPLAYNOTSUPPORTED,
     FLICNOMOREFRAMES,
     FLICSOUNDHEADERERROR,
};

typedef struct
{
  int size;
  unsigned short magic;
  unsigned short frames;
  unsigned short width;
  unsigned short height;
  unsigned short depth;
  unsigned short flags;
  unsigned short speed;
  unsigned int next;
  unsigned int frit;
    char expand[102-20];

    long NewPack;
    long SoundID;
    long SoundRate;
    char SoundChannels;
    char SoundBPS;
    long SoundChunkSize;
    short int SoundNumPreRead;
}FLICHEADERSTRUCT;

#define DIRECTVIDEOPORTAL (-2)

typedef struct
{
	int Active;
	int Handle;
	int Priority;
	int Mode;
	int Flag;
	int BytesPerPixel;
	int PWidth;
	int PHeight;
	int PWidthBytes;
	int VWidth;
	int VHeight;
	int VWidthBytes;
	int Offset;
	int SpriteHandle;                       /* Mem_Alloc handle */
	int Palette;                        /* Mem_Alloc handle */
	int X;
	int Y;
	int MaxAnim8;
	int NextAnim8;
	int MaxSprite;
	int NextSprite;
	int XOffset;
	int YOffset;
} PORTAL_STRUCT;


extern char * flicdebugtext;

typedef struct{
    int active;
    char *structhandle;
}FLICLISTSTRUCT;

typedef struct {
	int	SoundChunk;
	int	ImageChunk;
} FLICCHUNKSTRUCT;

#ifndef _GODS98COMPILE
typedef LPVOID LPDIRECTDRAWSURFACE4;
#endif // _GODS98COMPILE

typedef struct{
    int userflags;

    int fsXc,fsYc;
	int fsXsize,fsYsize;
    char *rambufferhandle;
	char *destportalhandle;

    char filename[256];
    unsigned char fsPalette256[(256*3)];
    unsigned short fsPalette64k[256];

    int framerate,lastticks;
    int currentframe,overallframe;
    int mode;
    int ringframe;
    int pointerposition;

	ULONG fsPitch;

	LPDIRECTDRAWSURFACE4 fsSurface;
	FLICHEADERSTRUCT fsHeader;
    lpFile filehandle;

	void *fsSPtr;
	void *fsSource;
	int fsDisplayMode;
	int fsBitPlanes;
	int fsLoadBufferSize;
	void *fsLoadBuffer;
	BOOL is15bit;
	//FLICCHUNKSTRUCT *fsPointer[];
}FLICSTRUCT;

typedef struct tagSOUNDARRAY
{
void* pBuffer[64];
void* pSample[2];
long  CurrentReadBuffer;
long  CurrentWriteBuffer;
long  ChunkSize;
long  NumBuffers;
long  SampleNum;
}SOUNDARRAY;

int Flic_GetEventRate(void);
int Flic_LoadHeader(char *filename,FLICSTRUCT **fsp);


static char Flic_ErrorString[512];
int	Flic_Memory(FLICSTRUCT *flicvarptr);
int	Flic_Load(FLICSTRUCT *flicvarptr);
int	Flic_FindChunk(FLICSTRUCT *flicvarptr);
int	Flic_FrameChunk(FLICSTRUCT *flicvarptr);
int	Flic_LoadPointers( FLICSTRUCT * flicvarptr);
int	Flic_LoadPalette64( FLICSTRUCT * flicvarptr);
int	Flic_DoChunk(FLICSTRUCT* flicvarptr);

void FlicCopyHiColorFlic(FLICSTRUCT *fsp);
void FlicCopyBytePerPixel(FLICSTRUCT *fsp);
void FlicCopyHiColor(FLICSTRUCT *fsp);


BOOL Flic_Palette256(FLICSTRUCT *fsp);
BOOL Flic_DeltaWord(FLICSTRUCT *fsp);
BOOL Flic_Palette64(FLICSTRUCT *fsp);
BOOL Flic_DeltaByte(FLICSTRUCT *fsp);
BOOL Flic_Black(FLICSTRUCT *fsp);
BOOL Flic_BrunDepack(FLICSTRUCT *fsp);
BOOL Flic_Copy(FLICSTRUCT *fsp);

//long UnpackM2(void *input, void *output, unsigned int Length);
long UnpackM2(void *input, void *output);
BOOL Flic_Unpack(FLICSTRUCT *fsp);

//int     Flic_Setup(char *filename, FLICSTRUCT **fs, LPDIRECTDRAW2 *lpDD, int flags);
//int     Flic_Animate(FLICSTRUCT *fsp,RECT *dest, LPDIRECTDRAWSURFACE3 *lpBB);
int     Flic_Setup(char *filename, FLICSTRUCT **fs, int flags);
int	Flic_Animate(FLICSTRUCT *fsp, LPAREA2D destArea, BOOL advance, BOOL trans);
int     Flic_Close(FLICSTRUCT *fsp);
int     Flic_SetFrame(FLICSTRUCT *fsp,int frame);
int     Flic_SetFrameRate(FLICSTRUCT *fsp,int framerate);
int     Flic_GetFrameRate(FLICSTRUCT *fsp);

int     Flic_DirectScreenValid(void);
BOOL	Flic_PlayFrame(FLICSTRUCT *fsp, int frame);

ULONG Flic_GetWidth(FLICSTRUCT *fsp);
ULONG Flic_GetHeight(FLICSTRUCT *fsp);

#define FLICHEADER
    #endif
/**********************************************************************************/

#endif // !_GODS98_FLIC_H