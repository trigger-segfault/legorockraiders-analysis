//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Input.c - [Joypad & Mouse Controller Code]
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#define	PAD_SOCKET1	0x00
#define INPUT_FLAG_INITIALISED	0x00000001


typedef struct Input_Globs
{
	ControllerPacket	Pad1, Pad2;
	Uint16				lastPad[8];
	Uint16				padData[8];
	Uint16				deBounce[8];
	Uint16				flags;
	short					mouseX, mouseY;
} Input_Globs, *lpInput_Globs;

ext	Input_Globs inputGlobs;




void		Input_InitPad( void );
void		Input_ReadPad(Sint16 pad);
void		Input_PadRead(Sint16 pad);
Uint16	Input_PadData(Sint16 pad);
Uint16	Input_PadDebounce(Sint16 pad);
Uint16	msx(void);
Uint16	msy(void);

#define PadsMute (0x01)

typedef struct 
{
	int Active;										// controller return value is valid
	int	PadData;								// Most recently read data for this pad.
	int RawPadData;							// Pad data with no post processing
	int	LastPadData;						// Previous pad data
	int LastRawPadData;					// Previous pad data with no post processing.
	int DebounceBits;						// Defines which keys to automatically debounce. This returns a null bit for the key unless it's been previously released.
	int KeyMaskBits;						// Mask out individual keys
	int Analogx1;
	int Analogy1;
	int Analogx2;
	int Analogy2;
	int Flags;									// Flag system
	int ReOrder[16];						// Re-order table for buttons.
} PadDef;

typedef struct
{
	PadDef Pad[8];
} PadsDef;

ext PadsDef Pads;

void PadsInitialise (void);
int PadsRead (void);
int OpenPortBuffer (int portnum, long length);
int ClosePortBuffer (int portnum);
int StartPortRecording (int portnum);
int StopPortRecording (int portnum);
int StartPortPlayback (int portnum, ControllerPacket *where);
int StopPortPlayback (int portnum);
int SavePortBuffer (int portnum);
long LoadPortBuffer (LPUCHAR name);
int InitPortPlay (int portnum, long addr);
void PortRumble (int portnum, char regular, char pulse);

// end of prototypes