//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Input File For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹


//***************************************************************************************************************************************************************************************************
// Include all Header Files
//***************************************************************************************************************************************************************************************************
#include	"libgods.h"
/*

typedef struct 
{
	int Active;										// controller return value is valid
	int	PadData;								// Most recently read data for this pad.
	int RawPadData;							// Pad data with no post processing
	int	LastPadData;						// Previous pad data
	int LastRawPadData;					// Previous pad data with no post processing.
	int DebounceBits;						// Defines which keys to automatically debounce. This returns a null bit for the key unless it's been previously released.
	int KeyMaskBits;						// Mask out individual keys
	int Flags;									// Falg system
	int ReOrder[16];						// Re-order table for buttons.
} PadDef;


typedef struct
{
	PadDef Pad[8];
} PadsDef;
*/
typedef struct
{
	char Flag;
	char DeviceID1;
	char TXData1a;
	char TXData1b;
	char TXData1c;
	char TXData1d;
	char DeviceID2;
	char TXData2a;
	char TXData2b;
	char TXData2c;
	char TXData2d;
	char DeviceID3;
	char TXData3a;
	char TXData3b;
	char TXData3c;
	char TXData3d;
	char DeviceID4;
	char TXData4a;
	char TXData4b;
	char TXData4c;
	char TXData4d;
}
PortTXdef;

int PadsDebounce (int index);
int PadsMask (int index);
void DoPortRecord (int portnum);
void DoPortPlayback (int portnum);
int AckPad (int portnum);
// Set up the global pad structure **************************************************************************************************************************************************************
PadsDef Pads;
short port0, port1;
ControllerPacket Port[2];
ControllerPacket *PortBufferStart[2];
ControllerPacket *PortBufferCurrent[2];
long PortBufferLength[2];
int PortFlags[2];
PortTXdef PortTX[2];
/*
	Pads.Pad[0].DebounceBits = PAD_LU | PAD_LD | PAD_LL | PAD_LR;
	OpenPortBuffer (0, 34 * 5000);
	StartPortRecording (0);
	while (stop == 0)
	{
		PadsRead();
		padeval = Pads.Pad[0].PadData;
		if (!(padeval & PAD_LU)) printf ("Left Up\n");
	}
	StopPortRecording (0);
	SavePortBuffer (0);
	ClosePortBuffer(0);

	printf ("********STARTING PLAYBACK*************\n");
	flogadog = LoadPortBuffer (floganame);
	if (flogadog != NULL)
	{
		InitPortPlay (0,flogadog);
		StartPortPlayback (0,NULL);
	}
	else printf ("ARSE");
	while (TRUE)
	{
		PadsRead();
		padeval = Pads.Pad[0].PadData;
		if (!(padeval & PAD_SEL)) stop = 1;
		VSync (0);
	}
	StopPortPlayback (0);
	ClosePortBuffer (0);
*/

//***************************************************************************************************************************************************************************************************
// Pad initialise routine 
// Calls all the relevant initialisation routines for the control pads.
// Will currently only try to initialise 2 standard pads.
// Dual shock, mouse, lightgun and multitap initialisation can be added later
// Returns a bit mask according to which pads are present 
//***************************************************************************************************************************************************************************************************
void PadsInitialise (void)
{
	int i,j;

	PadInitDirect ((char*)&Port[0],(char*)&Port[1]);
	PadStartCom ();
	port0 = AckPad(0);
	port1 = AckPad(1);

	PortFlags[0] =
	PortFlags[1] = 0;
	PortBufferCurrent[0] = 
	PortBufferStart[0] = 
	PortBufferCurrent[1] = 
	PortBufferStart[1] = NULL;
// Clear out the data structures for the pads.
	for (i=0;i<8;i++)
	{
		Pads.Pad[i].Active = 0;									//	assube not active
		Pads.Pad[i].PadData = -1;							// default to nothing pressed
		Pads.Pad[i].RawPadData = -1;					// default to nothing pressed
		Pads.Pad[i].LastPadData = 0;					// default to all pressed so there is a difference for debounce
		Pads.Pad[i].LastRawPadData = 0;				// default to all pressed so there is a difference for debounce
		Pads.Pad[i].DebounceBits = 0;					// debounce not set to anything
		Pads.Pad[i].KeyMaskBits = 0;					// Key masking set to 0
		Pads.Pad[i].Flags = 0;								// No recording or playback
		for (j=0;j<16;j++)
		{
			Pads.Pad[i].ReOrder[j] = 1<<j;				// ReOrder set to as is.
		}
	}
}


//***************************************************************************************************************************************************************************************************
// Acquire pad and 
//***************************************************************************************************************************************************************************************************
int AckPad (int portnum)
{
	int excondition;
	int doexp;
	int port;
	int padstate, ops;
	int timeout;
	int timeout2;
	static unsigned char align[6]={0,1,0xFF,0xFF,0xFF,0xFF};
	
	printf ("Starting init pad %d\n",portnum); 


	if (portnum == 0) port = 0x00;
	else if (portnum == 1) port = 0x10;
	else return (0);

	printf ("port = %x\n",port);

	excondition = 0;
	doexp = 0;
	timeout = 0;
	timeout2 = 0;

	while (excondition == 0)
	{
		ops = padstate;
		padstate = PadGetState (port);
		if (padstate == 0 && timeout2<50) 
		{
			timeout2++;
		}
		else
		{
// Seems to complete loading 
			if (padstate == 6)
			{
				if(PadInfoMode(port,2 ,0))
				{
					PadInfoMode(port,2 ,0);
					doexp = 1;
					printf ("Expandaed\n");
				}
				else	
				{
					PadInfoMode(port,1,0);
					printf ("Not Expanded\n");
					excondition=1;
				}
			}
// timeout and treat as bog-o pad
			else 
			{
				if (ops !=padstate) printf ("Padstate = %d\n",padstate);
				timeout++;
				VSync(0);
				if (timeout >130) 
				{
					printf ("timed out, treating port %d as a standard pad\n",portnum);
					return (1);
				}
			}
// if it's a shocker set it up else exit
			if (doexp !=0)
			{
				PadSetAct (port,&PortTX[portnum],2);
				if (padstate == 6)
				{
					PadSetActAlign (port,&align);
					printf ("Align set\n");
					excondition = 1;
				}
			}
		}
		if (timeout2>50)
		{
			printf ("port %d cannot be initialised",portnum);
			return (0);
		}
	}
	printf ("Finished init pad %d ok\n",portnum); 
	return (1);
}




//***************************************************************************************************************************************************************************************************
// Read the pad structure and output the necessary stuff
// currently only handles standard pads and rumble pads.
// Pad[0] = pad in port 0
// Pad[1] = pad in port 1 (should really be 4 but we don't do multi taps yet....
//***************************************************************************************************************************************************************************************************
int PadsRead (void)
{
	int retval = 0x0000;		// No data as 0 is an impossible value.... sorta kinda...
// Port 0
	Pads.Pad[0].Active = 0;															// Pad is dead
	if (PortFlags[0] == 0x0001) DoPortRecord(0);
	if (PortFlags[0] == 0x0002) DoPortPlayback(0);
	if (PortFlags[0] & 0x8000)
	{
//		printf ("Trying to re-acquire port 0\n");
		PortFlags[0] ^= 0xc000;
		AckPad(0);
	}
	
	if (GoodData(&Port[0])) 
	{
		switch ( GetType(&Port[0]))
		{
// Normal 16 button digital pad....
			case (4):																				// Ordinary controller
				if (!(Pads.Pad[0].Flags & PadsMute))
				{
					Pads.Pad[0].Active = -1;															// Pad is ok
					Pads.Pad[0].LastPadData = Pads.Pad[0].PadData;							// Save old raw data
					Pads.Pad[0].LastRawPadData = Pads.Pad[0].RawPadData;							// Save old raw data
					Pads.Pad[0].PadData = Pads.Pad[0].RawPadData = retval = Port[0].data.pad;		// return new raw data
					if (Pads.Pad[0].DebounceBits !=0) Pads.Pad[0].PadData = PadsDebounce (0);						//	Debounce Process the rawdata
					if (Pads.Pad[0].KeyMaskBits !=0) Pads.Pad[0].PadData = PadsMask (0);
					Pads.Pad[0].Analogx1 = 0;
					Pads.Pad[0].Analogy1 = 0;
					Pads.Pad[0].Analogx2 = 0;
					Pads.Pad[0].Analogy2 = 0;
				}
				else
				{
					Pads.Pad[0].PadData =
					Pads.Pad[0].RawPadData =
					Pads.Pad[0].LastPadData =
					Pads.Pad[0].LastRawPadData = -1;
					Pads.Pad[0].Analogx1 = 0;
					Pads.Pad[0].Analogy1 = 0;
					Pads.Pad[0].Analogx2 = 0;
					Pads.Pad[0].Analogy2 = 0;
					retval = -1;
				}
				break;
// Analogue Pad
			case (7):
				if (!(Pads.Pad[0].Flags & PadsMute))
				{
					Pads.Pad[0].Active = -1;														// Pad is ok
					Pads.Pad[0].LastPadData = Pads.Pad[0].PadData;									// Save old raw data
					Pads.Pad[0].LastRawPadData = Pads.Pad[0].RawPadData;							// Save old raw data
					Pads.Pad[0].PadData = Pads.Pad[0].RawPadData = retval = Port[0].data.anapad.buttons;		// return new raw data
					if (Pads.Pad[0].DebounceBits !=0) Pads.Pad[0].PadData = PadsDebounce (0);						//	Debounce Process the rawdata
					if (Pads.Pad[0].KeyMaskBits !=0) Pads.Pad[0].PadData = PadsMask (0);
					Pads.Pad[0].Analogx1 = Port[0].data.anapad.anx1;
					Pads.Pad[0].Analogy1 = Port[0].data.anapad.any1;
					Pads.Pad[0].Analogx2 = Port[0].data.anapad.anx2;
					Pads.Pad[0].Analogy2 = Port[0].data.anapad.any2;
				}
				else
				{
					Pads.Pad[0].PadData =
					Pads.Pad[0].RawPadData =
					Pads.Pad[0].LastPadData =
					Pads.Pad[0].LastRawPadData = -1;
					Pads.Pad[0].Analogx1 = 0;
					Pads.Pad[0].Analogy1 = 0;
					Pads.Pad[0].Analogx2 = 0;
					Pads.Pad[0].Analogy2 = 0;
					retval = -1;
				}
				break;

		}
	}
	else
	{
//		printf ("Data is bad\n");
		PortFlags[0] |= 0x4000;
	}
	if (!Pads.Pad[0].Active)
	{
//		printf ("Pad 0 has disappeared, Type is %d\n",GetType(&Port[0]));
		PortFlags[0] |= 0x4000;
	}

	if (Pads.Pad[0].Active && (PortFlags[0] & 0x4000)) PortFlags[0] |=0x8000;



// Port 1
	Pads.Pad[1].Active = 0;															// Pad is dead
	if (PortFlags[1] == 0x0001) DoPortRecord(1);
	if (PortFlags[1] == 0x0002) DoPortPlayback(1);
	if (PortFlags[1] & 0x8000)
	{
//		printf ("Trying to re-acquire port 1\n");
		PortFlags[1] ^= 0xc000;
		AckPad(1);
	}

	if (GoodData(&Port[1])) 
	{
		switch ( GetType(&Port[1]))
		{
// Normal 16 button digital pad....
			case (4):																				// Ordinary controller
				if (!(Pads.Pad[1].Flags & PadsMute))
				{
					Pads.Pad[1].Active = -1;															// Pad is ok
					Pads.Pad[1].LastPadData = Pads.Pad[1].PadData;							// Save old raw data
					Pads.Pad[1].LastRawPadData = Pads.Pad[1].RawPadData;							// Save old raw data
					Pads.Pad[1].PadData = Pads.Pad[1].RawPadData = retval = Port[1].data.pad;		// return new raw data
					if (Pads.Pad[1].DebounceBits !=0) Pads.Pad[1].PadData = PadsDebounce (1);						//	Debounce Process the rawdata
					if (Pads.Pad[1].KeyMaskBits !=0) Pads.Pad[1].PadData = PadsMask (1);
					Pads.Pad[1].Analogx1 = 0;
					Pads.Pad[1].Analogy1 = 0;
					Pads.Pad[1].Analogx2 = 0;
					Pads.Pad[1].Analogy2 = 0;
				}
				else
				{
					Pads.Pad[1].PadData =
					Pads.Pad[1].RawPadData =
					Pads.Pad[1].LastPadData =
					Pads.Pad[1].LastRawPadData = -1;
					Pads.Pad[1].Analogx1 = 0;
					Pads.Pad[1].Analogy1 = 0;
					Pads.Pad[1].Analogx2 = 0;
					Pads.Pad[1].Analogy2 = 0;
					retval = -1;
				}
				break;
// Analogue Pad
			case (7):
				if (!(Pads.Pad[1].Flags & PadsMute))
				{
					Pads.Pad[1].Active = -1;															// Pad is ok
					Pads.Pad[1].LastPadData = Pads.Pad[1].PadData;							// Save old raw data
					Pads.Pad[1].LastRawPadData = Pads.Pad[1].RawPadData;							// Save old raw data
					Pads.Pad[1].PadData = Pads.Pad[1].RawPadData = retval = Port[1].data.anapad.buttons;		// return new raw data
					if (Pads.Pad[1].DebounceBits !=0) Pads.Pad[1].PadData = PadsDebounce (1);						//	Debounce Process the rawdata
					if (Pads.Pad[1].KeyMaskBits !=0) Pads.Pad[1].PadData = PadsMask (1);
					Pads.Pad[1].Analogx1 = Port[1].data.anapad.anx1;
					Pads.Pad[1].Analogy1 = Port[1].data.anapad.any1;
					Pads.Pad[1].Analogx2 = Port[1].data.anapad.anx2;
					Pads.Pad[1].Analogy2 = Port[1].data.anapad.any2;
				}
				else
				{
					Pads.Pad[1].PadData =
					Pads.Pad[1].RawPadData =
					Pads.Pad[1].LastPadData =
					Pads.Pad[1].LastRawPadData = -1;
					Pads.Pad[1].Analogx1 = 0;
					Pads.Pad[1].Analogy1 = 0;
					Pads.Pad[1].Analogx2 = 0;
					Pads.Pad[1].Analogy2 = 0;
					retval = -1;
				}
				break;

		}
	}
	else
	{
//		printf (" Port 1 Data is bad\n");
		PortFlags[1] |= 0x4000;
	}
	if (!Pads.Pad[1].Active)
	{
//		printf ("Pad 1 has disappeared, Type is %d\n",GetType(&Port[1]));
		PortFlags[1] |= 0x4000;
	}

	if (Pads.Pad[1].Active && (PortFlags[1] & 0x4000)) PortFlags[1] |=0x8000;



	return (retval);
}

//***************************************************************************************************************************************************************************************************
// Debounce any set keys 
//***************************************************************************************************************************************************************************************************
int PadsDebounce (int index)
{
	int i;
	int compare = 1;
	int lastval = Pads.Pad[index].LastRawPadData;
	int thisval = Pads.Pad[index].RawPadData;
	lastval = (lastval ^ 0xffff) & 0xffff ;
	thisval = (thisval ^ 0xffff) & 0xffff;

	for (i=0; i<16;i++)
	{
// if this bit set in the current data?
		if ((thisval & compare) !=0)														// is this bit even worth bothering about?
		{
			if ((Pads.Pad[index].DebounceBits & compare) != 0)					// Debounce bit i ?
			{
				if ((lastval & compare) != 0)												// was this bit set last time round
				{
					thisval ^= compare;													// clear this bit.
				}
			}
		}
		compare = compare <<1;
	}
	thisval = (thisval ^ 0xffff)& 0xffff;
	return (thisval);
}
			
//***************************************************************************************************************************************************************************************************
// Forcably mask defined bits
//***************************************************************************************************************************************************************************************************
int PadsMask (int index)
{
	int i;
	int compare = 1;
	int thisval = Pads.Pad[index].PadData;
	thisval = (thisval ^ 0xffff) & 0xffff;

	for (i=0; i<16;i++)
	{
		if ((thisval & compare) !=0)														// is this bit even worth bothering about?
		{
			if ((Pads.Pad[index].KeyMaskBits & compare) != 0)					// Mask bit i ?
			{
				thisval ^= compare;																// Kill the bit
			}
		}
		compare = compare <<1;
	}
	thisval = (thisval ^ 0xffff)& 0xffff;
	return (thisval);
}

//***************************************************************************************************************************************************************************************************
// Open a port recording buffer
//***************************************************************************************************************************************************************************************************
int OpenPortBuffer (int portnum, long length)
{
	if (PortBufferStart[portnum] == NULL)
	{
		PortBufferCurrent[portnum] = 
		PortBufferStart[portnum] = Mem_Malloc (length);
		PortBufferLength[portnum] = length;
		printf ("buffer %d opened at %x\n",portnum, PortBufferStart[portnum]);
		return (1);
	}
	else
	{
		printf ("Buffer %d is currently in use you need to close it before re-opening\n",portnum);
		return (NULL);
	}
}

//***************************************************************************************************************************************************************************************************
// Close the Port recording buffer
//***************************************************************************************************************************************************************************************************
int ClosePortBuffer (int portnum)
{
	if (PortBufferStart[portnum] != NULL)
	{
		RELEASE (PortBufferStart[portnum]);
		printf ("buffer %d closed from %x\n",portnum, PortBufferStart[portnum]);
		printf ("current pointer %x\n", PortBufferCurrent[portnum]);
		PortBufferCurrent[portnum] = 
		PortBufferStart[portnum] = NULL;
		return (1);
	}
	else 
	{
		printf ("Buffer %d is already closed\n", portnum);
		return (NULL);
	}
}

//***************************************************************************************************************************************************************************************************
// Start recording 
//***************************************************************************************************************************************************************************************************
int StartPortRecording (int portnum)				
{
	if (PortFlags[portnum] == 0x0000 && PortBufferStart[portnum] == PortBufferCurrent[portnum] && PortBufferStart[portnum] != NULL & PortBufferCurrent[portnum] != NULL)
	{
		printf ("Recording buffer %d started at %x\n", portnum, PortBufferStart[portnum]);
		PortFlags[portnum] = 0x0001;														// set the record flag
		memcpy ( ((char*)PortBufferStart[portnum])+4, (char*)&Pads,  sizeof(Pads));		// Copy the pad header and leve space for the length
		(char*)PortBufferCurrent[portnum] += sizeof (Pads)+4;										// correct the current position.
		printf ("Current position for buffer %d is now %x\n", portnum, PortBufferCurrent[portnum]);
		return (1);
	}
	else
	{
		printf ("Buffer %d is not valid for some reason.\n", portnum);
		return (NULL);
	}
}

//***************************************************************************************************************************************************************************************************
// Stop recording
//***************************************************************************************************************************************************************************************************
int StopPortRecording (int portnum)
{
	unsigned long val;
	if (PortFlags[portnum] == 0x0001)
	{
		PortFlags[portnum] = 0x0000;
		val = (unsigned long)PortBufferCurrent[portnum] - (unsigned long)PortBufferStart[portnum];
		*((long*)PortBufferStart[portnum]) = val;
		printf ("Buffer %d stopped recording at %x. Total length = %x\n", portnum, PortBufferCurrent[portnum], val);
		return (1);
	}
	else
	{
		printf ("But you're not recording port %d \n",portnum);
		return (NULL);
	}
}

//***************************************************************************************************************************************************************************************************
// Record the port
//***************************************************************************************************************************************************************************************************
void DoPortRecord (int portnum)
{
		unsigned long buffend = (unsigned long) PortBufferStart[portnum] + PortBufferLength[portnum];
		if (PortBufferCurrent[portnum]+1 < buffend)
		{
//			memcpy ( PortBufferCurrent[portnum], &Port[portnum],  1);		// Copy the pad header and leve space for the length
			*PortBufferCurrent[portnum]++ = Port[portnum];
//			PortBufferCurrent[portnum]++;
//			printf ("Recording to %x will finish at %x\n", PortBufferCurrent[portnum], buffend);
		}
		else
		{
			printf ("Buffer %d would have overflowed at %x. Stopping recording\n", portnum, buffend);
			StopPortRecording(portnum);
		}
}


//***************************************************************************************************************************************************************************************************
// Start the port playback
// Playsback whatever the current port buffer is pointing to
//***************************************************************************************************************************************************************************************************
int StartPortPlayback (int portnum, ControllerPacket *where)
{
	if (PortFlags[portnum] == 0x0000)
	{
		DisableTAP();
		if (where != NULL)
		{
			PortBufferStart [portnum] =
			PortBufferCurrent [portnum] = where;
		}
		else 
		{
			PortBufferCurrent [portnum] = PortBufferStart [portnum];
			printf ("Buffer %d start set to %X\n", portnum, PortBufferStart [portnum]);
		}
		PortBufferLength [portnum] = *((long*)PortBufferStart[portnum]);						// get the length
		memcpy ( (char*)&Pads, ((char*)PortBufferStart[portnum])+4, sizeof(Pads));		// Copy the pad header and leve space for the length
		(char*)PortBufferCurrent[portnum] += sizeof (Pads)+4;										// correct the current position.
		printf ("Real Buffer data at %x\n", PortBufferCurrent[portnum]);
		printf ("Total data length %x\n", PortBufferLength[portnum]);
		PortFlags[portnum] = 0x0002;
		return (1);
	}
	else
	{
		printf ("Sorry Port %d is unable to playback. you may currently be recording",portnum);
		return (NULL);
	}
}

//***************************************************************************************************************************************************************************************************
// Stop port playback
//***************************************************************************************************************************************************************************************************
int StopPortPlayback (int portnum)
{
	if (PortFlags[portnum] == 0x0002)
	{
		PortFlags[portnum] = 0x0000;
		EnableTAP();
		return (1);
	}
	else
	{
		printf ("Port %x is not playing back so it can't be stopped. STUPID!!", portnum);
		return (NULL);
	}
}
//***************************************************************************************************************************************************************************************************
// Playback the port
//***************************************************************************************************************************************************************************************************
void DoPortPlayback (int portnum)
{
		unsigned long buffend = (unsigned long) PortBufferStart[portnum] + PortBufferLength[portnum];
		if (PortBufferCurrent[portnum]+1 < buffend)
		{
			Port[portnum] = *PortBufferCurrent[portnum]++;
//			printf ("Playback data read ok. next packet at %x\n", PortBufferCurrent[portnum]);
		}
		else
		{
			printf ("Buffer %d would have overflowed at %x. Stopping playback\n", portnum, buffend);
			StopPortPlayback(portnum);
		}
}

//***************************************************************************************************************************************************************************************************
// Save Buffer
//***************************************************************************************************************************************************************************************************
int SavePortBuffer (int portnum)
{
	static	Uint16	saves =0;
	char	name[256];
	Sint32	handle;

	sprintf(name,"%s\\CD_ROOT\\DATA\\TJ%04d.JPS",_DEBUGPATH, saves++);

	if((handle = PCcreat(name, NULL))<0)
	{
		printf ("Couldn't open file %s as write for buffer %d\n",name, portnum);
		return (NULL);
	}

	PCwrite(handle, (char *)PortBufferStart[portnum], PortBufferLength[portnum]);
	printf ("File %s written successfully for port %d\n",name,portnum);
	PCclose (handle);
	return (1);
}

//***************************************************************************************************************************************************************************************************
// Load Buffer
//***************************************************************************************************************************************************************************************************
long LoadPortBuffer (LPUCHAR name)
{
	char name2[256];
	long size;
	long addr;

	sprintf(name2,"%s.JPS", name);
	
	
	addr = File_LoadBinary (name2, &size);
	if(addr==NULL)
	{
		return (NULL);
	}
	return (addr);
}

//***************************************************************************************************************************************************************************************************
// Set addresses etc for playing a loaded buffer
//***************************************************************************************************************************************************************************************************
int InitPortPlay (int portnum, long addr)
{
	if (PortFlags[portnum]==0x0000 && PortBufferStart[portnum] == NULL)
	{
		PortBufferStart[portnum] = addr;
		PortBufferCurrent[portnum] = PortBufferStart[portnum];
		return (1);
	}
	else
	{
		printf ("Buffer %d is currently in use you must close it properly", portnum);
		return (NULL);
	}
}
//***************************************************************************************************************************************************************************************************
//  Rumble pack stuff
//***************************************************************************************************************************************************************************************************
void PortRumble (int portnum,char regular, char pulse)
{
	PortTX[portnum].Flag = regular;
	PortTX[portnum].DeviceID1 = pulse;
}


Input_Globs inputGlobs;
void	Input_InitPad( void )
{
	inputGlobs.flags |= GFX_FLAG_INITIALISED;
	InitPAD(&inputGlobs.Pad1, MAX_CONTROLLER_BYTES, &inputGlobs.Pad2, MAX_CONTROLLER_BYTES);
	StartPAD();
}

void	Input_ReadPad(Sint16 pad)
{
	if(pad == -1)
		{
		Input_PadRead(0x00);
		Input_PadRead(0x01);
		}
	else
		{
		Input_PadRead(pad);
		}
}

void	Input_PadRead(Sint16 pad)
{
	Uint16	tmp;

	tmp = ((pad>>4)<<2)+(pad&3);
	inputGlobs.lastPad[tmp] = inputGlobs.padData[tmp];
	if ((pad&3) == PAD_SOCKET1)
	{
		if(GoodData(&inputGlobs.Pad1) && GetType(&inputGlobs.Pad1)==STD_PAD)
		{
			inputGlobs.padData[tmp]=inputGlobs.Pad1.data.pad ^ 0xffff;
			inputGlobs.deBounce[tmp]=(inputGlobs.padData[tmp]&inputGlobs.lastPad[tmp])^inputGlobs.padData[tmp];
		}
	}
	else
	{
		if(GoodData(&inputGlobs.Pad2) && GetType(&inputGlobs.Pad2)==STD_PAD)
		{
			inputGlobs.padData[tmp]=inputGlobs.Pad2.data.pad ^ 0xffff;
			inputGlobs.deBounce[tmp]=(inputGlobs.padData[tmp]&inputGlobs.lastPad[tmp])^inputGlobs.padData[tmp];
		}
	}
}

Uint16	Input_PadData(Sint16 pad)
{
	Uint16	tmp;

	tmp = ((pad>>4)<<2)+(pad&3);
	return inputGlobs.padData[tmp];
}

Uint16	Input_PadDebounce(Sint16 pad)
{
	Uint16	tmp;

	tmp = ((pad>>4)<<2)+(pad&3);
	return inputGlobs.deBounce[tmp];
}

Uint16	msx(void)
{
	return inputGlobs.mouseX;
}

Uint16	msy(void)
{
	return inputGlobs.mouseY;
}














