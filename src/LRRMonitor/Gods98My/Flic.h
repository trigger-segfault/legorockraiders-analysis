#pragma once

#include "../framework.h"
#include "Files.h"
#include "Maths.h"


namespace Gods98
{; // !<---

/**********************************************************************************
 ******** Constants
 **********************************************************************************/

#pragma region Constants

#define FLICTIMERTICKSPERSECOND 70
#define MAXFLICS 30


#define FLICERRORSTART 3000

#define FLICFINISHED 1
#define FLICNOERROR  0
#define FLICERROR   -1

#define DIRECTVIDEOPORTAL (-2)

#pragma endregion

/**********************************************************************************
 ******** Enumerations
 **********************************************************************************/

#pragma region Enums

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

//#define FLICSETPALETTE      (1<<1)

enum
{
	FLICMODE_BYTEPERPIXEL,	//  EQU   0       ;BYTE PER PIXEL
	FLICMODE_MODEX,	//     EQU   1       ;MODEX
	FLICMODE_PLANAR,		//    EQU   2       ;PLANAR MODE
	FLICMODE_TRUECOLOR,		//   EQU   3       ;TRUE COLOR MODE
	FLICMODE_HICOLOR,	//   EQU   4       ;HI COLOR MODE
};


enum
{
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

#pragma endregion

/**********************************************************************************
 ******** Structures
 **********************************************************************************/

#pragma region Structs

/*
#define File_Open fopen
#define File_Seek fseek
#define File_Read fread
#define File_Close fclose
#define File_Tell ftell
*/

//int File_Length(lpFile fp);

typedef struct
{
	/*0,4*/ int PWidth;
	/*4*/
} PORTAL;
static_assert(sizeof(PORTAL) == 0x4, "");


typedef struct
{
	/*00,4*/ int size;
	/*04,2*/ unsigned short magic;
	/*06,2*/ unsigned short frames;
	/*08,2*/ unsigned short width;
	/*0a,2*/ unsigned short height;
	/*0c,2*/ unsigned short depth;
	/*0e,2*/ unsigned short flags;
	/*10,2*/ unsigned short speed;
	/*12,2*/ unsigned short padding1;
	/*14,4*/ unsigned int next;
	/*18,4*/ unsigned int frit;
	/*1c,52*/ char expand[102-20 /*80*/];
	/*6e,2*/ unsigned short padding2;
	/*70,4*/ long NewPack;
	/*74,4*/ long SoundID;
	/*78,4*/ long SoundRate;
	/*7c,1*/ char SoundChannels;
	/*7d,1*/ char SoundBPS;
	/*7e,2*/ unsigned short padding3;
	/*80,4*/ long SoundChunkSize;
	/*84,2*/ short int SoundNumPreRead;
	/*86,2*/ unsigned short padding4;
	/*88*/
} FLICHEADERSTRUCT;
static_assert(sizeof(FLICHEADERSTRUCT) == 0x88, "");


typedef struct
{
	/*00,4*/ int Active;
	/*04,4*/ int Handle;
	/*08,4*/ int Priority;
	/*0c,4*/ int Mode;
	/*10,4*/ int Flag;
	/*14,4*/ int BytesPerPixel;
	/*18,4*/ int PWidth;
	/*1c,4*/ int PHeight;
	/*20,4*/ int PWidthBytes;
	/*24,4*/ int VWidth;
	/*28,4*/ int VHeight;
	/*2c,4*/ int VWidthBytes;
	/*30,4*/ int Offset;
	/*34,4*/ int SpriteHandle;                       /* Mem_Alloc handle */
	/*38,4*/ int Palette;                        /* Mem_Alloc handle */
	/*3c,4*/ int X;
	/*40,4*/ int Y;
	/*44,4*/ int MaxAnim8;
	/*48,4*/ int NextAnim8;
	/*4c,4*/ int MaxSprite;
	/*50,4*/ int NextSprite;
	/*54,4*/ int XOffset;
	/*58,4*/ int YOffset;
	/*5c*/
} PORTAL_STRUCT;
static_assert(sizeof(PORTAL_STRUCT) == 0x5c, "");


typedef struct
{
    /*0,4*/ int active;
	/*4,4*/ char* structhandle;
	/*8*/
} FLICLISTSTRUCT;
static_assert(sizeof(FLICLISTSTRUCT) == 0x8, "");


typedef struct
{
	/*0,4*/ int	SoundChunk;
	/*4,4*/ int	ImageChunk;
	/*8*/
} FLICCHUNKSTRUCT;
static_assert(sizeof(FLICCHUNKSTRUCT) == 0x8, "");


typedef struct
{
	/*000,4*/ int userflags;
	/*004,4*/ int fsXc;
	/*008,4*/ int fsYc;
	/*00c,4*/ int fsXsize;
	/*010,4*/ int fsYsize;
	/*014,4*/ char* rambufferhandle;
	/*018,4*/ char* destportalhandle;
	/*01c,100*/ char filename[256];
	/*11c,300*/ unsigned char fsPalette256[(256*3)];
	/*41c,200*/ unsigned short fsPalette64k[256];
	/*61c,4*/ int framerate;
	/*620,4*/ int lastticks;
	/*624,4*/ int currentframe;
	/*628,4*/ int overallframe;
	/*62c,4*/ int mode;
	/*630,4*/ int ringframe;
	/*634,4*/ int pointerposition;
	/*638,4*/ unsigned long fsPitch;
	/*63c,4*/ IDirectDrawSurface4* fsSurface;
	/*640,88*/ FLICHEADERSTRUCT fsHeader;
	/*6c8,4*/ File_Dummy* filehandle;
	/*6cc,4*/ void* fsSPtr;
	/*6d0,4*/ void* fsSource;
	/*6d4,4*/ int fsDisplayMode;
	/*6d8,4*/ int fsBitPlanes;
	/*6dc,4*/ int fsLoadBufferSize;
	/*6e0,4*/ void* fsLoadBuffer;
	/*6e4,4*/ BOOL is15bit;
	/*6e8*/
} FLICSTRUCT;
static_assert(sizeof(FLICSTRUCT) == 0x6e8, "");


typedef struct tagSOUNDARRAY
{
	/*000,100*/ void* pBuffer[64];
	/*100,8*/ void* pSample[2];
	/*108,4*/ long  CurrentReadBuffer;
	/*10c,4*/ long  CurrentWriteBuffer;
	/*110,4*/ long  ChunkSize;
	/*114,4*/ long  NumBuffers;
	/*118,4*/ long  SampleNum;
	/*11c*/
} SOUNDARRAY;
static_assert(sizeof(SOUNDARRAY) == 0x11c, "");

#pragma endregion

/**********************************************************************************
 ******** Functions
 **********************************************************************************/

#pragma region Functions

// <LegoRR.exe @00483f40>
BOOL __cdecl Flic_Setup(const char* filename, OUT FLICSTRUCT** fsp, int flags);

// <LegoRR.exe @004841c0>
BOOL __cdecl Flic_Close(FLICSTRUCT* fsp);

// <LegoRR.exe @00484220>
BOOL __cdecl Flic_LoadHeader(const char* filename, FLICSTRUCT** fsp);

// <LegoRR.exe @00484330>
BOOL __cdecl Flic_Animate(FLICSTRUCT* fsp, const AREA2D* destArea, BOOL advance, BOOL trans);

// <LegoRR.exe @00484490>
/*FlicError*/ int __cdecl Flic_Memory(FLICSTRUCT* fsp);

// <LegoRR.exe @00484520>
/*FlicError*/ int __cdecl Flic_Load(FLICSTRUCT* fsp);

// <LegoRR.exe @004845e0>
/*FlicError*/ int __cdecl Flic_FindChunk(FLICSTRUCT* fsp);

// <LegoRR.exe @00484770>
BOOL __cdecl Flic_FrameChunk(FLICSTRUCT* fsp);

// <LegoRR.exe @004848d0>
/*FlicError*/ int __cdecl Flic_DoChunk(FLICSTRUCT* fsp);

// Function to load pointers for each frame of flic
// <LegoRR.exe @004849e0>
/*FlicError*/ int __cdecl Flic_LoadPointers(FLICSTRUCT* fsp);

// Function to load an 8 bit palette
// <LegoRR.exe @00484a90>
/*FlicError*/ int __cdecl Flic_LoadPalette64(FLICSTRUCT* fsp);

// <LegoRR.exe @00484b40>
BOOL __cdecl Flic_Copy(FLICSTRUCT* fsp);

// <LegoRR.exe @00484b90>
BOOL __cdecl FlicBRunDepackHiColor(FLICSTRUCT* fsp);

// <LegoRR.exe @00484c90>
BOOL __cdecl FlicBRunDepackHiColorFlic32k(FLICSTRUCT* fsp);

// <LegoRR.exe @00484de0>
BOOL __cdecl Flic_BrunDepack(FLICSTRUCT* fsp);

// (shared)
// <LegoRR.exe @00484e50>
BOOL __cdecl Flic_NERPFunc__True(int* stack); // return 1;

// <LegoRR.exe @00484e60>
void __cdecl FlicCreateHiColorTable(FLICSTRUCT* fsp);

// <LegoRR.exe @00484ec0>
BOOL __cdecl Flic_Palette256(FLICSTRUCT* fsp);

// (shared)
// <LegoRR.exe @00484f50>
void __cdecl Flic_logf_removed(const char* msg, ...); // return;

// <LegoRR.exe @00484f60>
void __cdecl FlicDeltaWordHiColor(FLICSTRUCT* fsp);

// <LegoRR.exe @00485110>
void __cdecl FlicDeltaWordHiColorFlic32k(FLICSTRUCT* fsp);

// <LegoRR.exe @004852f0>
BOOL __cdecl Flic_DeltaWord(FLICSTRUCT* fsp);

// <LegoRR.exe @00485380>
unsigned short __cdecl getFlicCol(unsigned char n, FLICSTRUCT* fsp);

// <LegoRR.exe @004853a0>
unsigned long __cdecl Flic_GetHeight(FLICSTRUCT* fsp);


// (shared)
// <LegoRR.exe @00489a90>
unsigned long __cdecl Flic_GetWidth(FLICSTRUCT* fsp);


#pragma endregion

}
