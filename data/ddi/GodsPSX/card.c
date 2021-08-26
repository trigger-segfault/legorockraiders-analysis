
// CARD.C - Memory card functions, Coded by Adrian Francis, March '99


#ifdef 0
// TODO: Error protection... write data twice, checksum, compare?

#include <sys/types.h>
#include "card.h"

extern u_long *WORKSPACE;

unsigned long ev0,ev1,ev2,ev3;
unsigned long ev10,ev11,ev12,ev13;

//***************************************************************************************************************
// These are default values

u_char Card_Name[]={ "TONKA JOE ADVENTURES" };

u_short Card_clut[]={	0x03FF,0x001F,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
						0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000	};
									
u_long Card_icon[3][32]={
						0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
						0x00000000,0x00000000,0x00000000,0x00000000,0x11000000,0x00000011,0x11000000,0x00000011,
						0x11000000,0x00000011,0x11000000,0x00000011,0x00000000,0x00000000,0x00000000,0x00000000,
						0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
						
						0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
						0x11110000,0x00001111,0x00010000,0x00001000,0x11010000,0x00001011,0x11010000,0x00001011,
						0x11010000,0x00001011,0x11010000,0x00001011,0x00010000,0x00001000,0x11110000,0x00001111,
						0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
						
						0x00000000,0x00000000,0x00000000,0x00000000,0x11111100,0x00111111,0x00000100,0x00100000,
						0x11110100,0x00101111,0x00010100,0x00101000,0x11010100,0x00101011,0x11010100,0x00101011,
						0x11010100,0x00101011,0x11010100,0x00101011,0x00010100,0x00101000,0x11110100,0x00101111,
						0x00000100,0x00100000,0x11111100,0x00111111,0x00000000,0x00000000,0x00000000,0x00000000};
//***************************************************************************************************************
					
static unsigned short ascii_table[3][2] = {
	{0x824f, 0x30},	/* 0-9  */
	{0x8260, 0x41},	/* A-Z  */
	{0x8281, 0x61},	/* a-z  */
};

static unsigned short ascii_k_table[] = {
	0x8140,		/*   */
	0x8149,		/* ! */
	0x8168,		/* " */
	0x8194,		/* # */
	0x8190,		/* $ */
	0x8193,		/* % */
	0x8195,		/* & */
	0x8166,		/* ' */
	0x8169,		/* ( */
	0x816a,		/* ) */
	0x8196,		/* * */
	0x817b,		/* + */
	0x8143,		/* , */
	0x817c,		/* - */
	0x8144,		/* . */
	0x815e,		/* / */
	0x8146,		/* : */
	0x8147,		/* ; */
	0x8171,		/* < */
	0x8181,		/* = */
	0x8172,		/* > */
	0x8148,		/* ? */
	0x8197,		/* @ */
	0x816d,		/* [ */
	0x818f,		/* \ */
	0x816e,		/* ] */
	0x814f,		/* ^ */
	0x8151,		/* _ */
	0x8165,		/* ` */
	0x816f,		/* { */
	0x8162,		/* | */
	0x8170,		/* } */
	0x8150,		/* ~ */
};

// Convert a string from ASCII to Shift-JIS
void Card_ASCII2SJIS(unsigned char *string,unsigned char *dest)
{
	int	i;
	
	int sjis_code;
	int ascii_code;
	
	unsigned char stmp;
	unsigned char stmp2;

	unsigned char *dest2;
						   
	dest2 = dest;

	for( i=0; i<32; i++ )
	{
		*dest2++ = 0x81;				  
		*dest2++ = 0x40;
	}
	
							    
	while(*string) {
		stmp2 = 0;
		ascii_code = *string++;
		if ((ascii_code >= 0x20) && (ascii_code <= 0x2f))
			stmp2 = 1;
		else
		if ((ascii_code >= 0x30) && (ascii_code <= 0x39))
			stmp = 0;
		else
		if ((ascii_code >= 0x3a) && (ascii_code <= 0x40))
			stmp2 = 11;
		else
		if ((ascii_code >= 0x41) && (ascii_code <= 0x5a))
			stmp = 1;
		else
		if ((ascii_code >= 0x5b) && (ascii_code <= 0x60))
			stmp2 = 37;
		else
		if ((ascii_code >= 0x61) && (ascii_code <= 0x7a))
			stmp = 2;
		else
		if ((ascii_code >= 0x7b) && (ascii_code <= 0x7e))
			stmp2 = 63;
		else {
			printf("bad ASCII code 0x%x\n", ascii_code);
			exit(1);
		}

		if(stmp2)
			sjis_code = ascii_k_table[ascii_code - 0x20 - (stmp2 - 1)];
		else
			sjis_code = ascii_table[stmp][0] + ascii_code - ascii_table[stmp][1];

		/* Write sjis */
		*dest++ = (sjis_code&0xff00)>>8;
		*dest++ = (sjis_code&0xff);
	}
}
	
void Card_Init(void)
{
	InitCARD(1);
	StartCARD();
	_bu_init();
	
	EnterCriticalSection();
	ev0 = OpenEvent(SwCARD, EvSpIOE, EvMdNOINTR, NULL);
	ev1 = OpenEvent(SwCARD, EvSpERROR, EvMdNOINTR, NULL);
	ev2 = OpenEvent(SwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
	ev3 = OpenEvent(SwCARD, EvSpNEW, EvMdNOINTR, NULL);
	ev10 = OpenEvent(HwCARD, EvSpIOE, EvMdNOINTR, NULL);
	ev11 = OpenEvent(HwCARD, EvSpERROR, EvMdNOINTR, NULL);
	ev12 = OpenEvent(HwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
	ev13 = OpenEvent(HwCARD, EvSpNEW, EvMdNOINTR, NULL);
	EnableEvent(ev0);
	EnableEvent(ev1);
	EnableEvent(ev2);
	EnableEvent(ev3);
	EnableEvent(ev10);
	EnableEvent(ev11);
	EnableEvent(ev12);
	EnableEvent(ev13);
	ExitCriticalSection();
}

void Card_ShutDown(void)
{
	StopCARD();
	
	EnterCriticalSection();
	DisableEvent(ev0);
	DisableEvent(ev1);
	DisableEvent(ev2);
	DisableEvent(ev3);
	DisableEvent(ev10);
	DisableEvent(ev11);
	DisableEvent(ev12);
	DisableEvent(ev13);
	CloseEvent(ev0);
	CloseEvent(ev1);
	CloseEvent(ev2);
	CloseEvent(ev3);
	CloseEvent(ev10);
	CloseEvent(ev11);
	CloseEvent(ev12);
	CloseEvent(ev13);
	ExitCriticalSection();
}

int Card_Status(int card)
{	
	VSync(0);
	_card_info(card<<4);
	
	while(1) 
	{
		if(TestEvent(ev10)) return CARD_CONNECTED;	// Connected
		if(TestEvent(ev11)) return CARD_ERROR;		// Error
		if(TestEvent(ev12)) return CARD_TIMEOUT;	// Timeout
		if(TestEvent(ev13)) return CARD_NEWCARD;	// New card
	}
}

int Card_New(int card)
{
	card<<=4;
	
	// Make events active
	TestEvent(ev10);
	TestEvent(ev11);
	TestEvent(ev12);
	TestEvent(ev13);
	
	_card_clear(card);

	// Make events active
	TestEvent(ev0);
	TestEvent(ev1);
	TestEvent(ev2);
	TestEvent(ev3);
	
	_card_load(card);
	
	while(1) 
	{
		if(TestEvent(ev10)) return CARD_FORMATTED;		// Formatted
		if(TestEvent(ev11)) return CARD_ERROR;			// Error
		if(TestEvent(ev12)) return CARD_NOCARD;			// No card
		if(TestEvent(ev13)) return CARD_UNFORMATTED;	// Unformatted
	}
}

int Card_Format(int card)
{
	char name[]={ "bu00:" };
	
	name[2]='0' + card;
	
	return format(name);
}

int Card_Dir(int card,struct DIRENTRY *dir)
{
	char name[]={ "bu00:*" };
	int n;

	name[2]='0' + card;
	
	n=0;
	
	if(firstfile(name, dir)==dir) 
	{
		do 
		{
			n++, dir++;
		} while(nextfile(dir)==dir);
	}
	return n;
}

int Card_Load(int card,char *name,void *ptr,int bytes)
{
	char path[128]={ "bu00:" };
	long handle,size;
	int retries=CARD_MAXRETRIES;
	int n;
	
	path[2]='0' + card;
	strcat(path,name);
		
	size=bytes+sizeof(Card_Header);
	
retry:

	if((handle=open(path,O_RDONLY))>=0)
	{   
		if (read(handle,WORKSPACE,size)!=size)
		{
			close(handle);
			retries--;
			for (n=0;n<100;n++) VSync(0);
			if (retries) goto retry;
			return 0;
		}
		memcpy(ptr,(u_char *)WORKSPACE+sizeof(Card_Header),bytes);
	}
	else 
	{
		return 0;
	}

	close(handle);
	return 1;
}
							
int Card_Save(int card,char *name,void *ptr,int bytes)
{
	long handle,size;
	Card_Header *header=(Card_Header *)WORKSPACE;
	char path[128]={ "bu00:" };
	int retries=CARD_MAXRETRIES;
	int n;

	path[2]='0' + card;
	strcat(path,name);
	
	header->magic[0]='S';				
	header->magic[1]='C';
	header->type = 0x13;
	
	Card_ASCII2SJIS(Card_Name,header->name);
	memcpy( header->clut,Card_clut,32 );
	memcpy( header->icon[0],Card_icon[0],128);
	memcpy( header->icon[1],Card_icon[1],128);
	memcpy( header->icon[2],Card_icon[2],128);

	size = bytes + sizeof(Card_Header); 
	header->slots = (size/8192) + ((size&8191)!=0);

	delete(path);
	
	if((handle=open(path,O_CREAT | (header->slots<<16)))>=0)
	{	
		close(handle);
	}
	else
	{
		return 0;
	}

retry:

	if((handle=open(path,O_WRONLY))>=0)
	{	
		memcpy((char *)WORKSPACE+sizeof(Card_Header),ptr,bytes);

		if(write(handle,WORKSPACE,size)!=size)
		{
			close(handle);
			retries--;
			for (n=0;n<100;n++) VSync(0);
			if (retries) goto retry;
			return 0;
		}
	}
	else 
	{
		return 0;
	}
	
	close(handle);
	return 1;
}
/*
void Card_DebugTest(void *buff)
{
	int i,n,f;
	char *ptr;
	struct DIRENTRY dir[15];
	
	for (i=0;i<2;i++)
	{
		printf("\nTesting card slot %d\n",i);
		n=Card_Status(i);
		switch(n)
		{
			case CARD_CONNECTED:
				printf("Card found\n");
				break;
			case CARD_ERROR:
				printf("Error\n");
				break;
			case CARD_TIMEOUT:
				printf("Timeout\n");
				break;
			case CARD_NEWCARD:
				printf("Card has changed\n");
				break;
			default:
				printf("Unknown status\n");
		}
		
		if (n==CARD_CONNECTED || n==CARD_NEWCARD)
		{
			printf("Initializing file system\n"); 
			n=Card_New(i);
			switch(n)
			{
				case CARD_FORMATTED:
					printf("Card is formatted\n");
					break;
				case CARD_ERROR:
					printf("Error\n");
					break;
				case CARD_NOCARD:
					printf("No card\n");
					break;
				case CARD_UNFORMATTED:
					printf("Card is not formatted\n");
					break;
				default:
					printf("Unknown status\n");
			}
			
			printf("Reading directory\n");
			f=Card_Dir(i,&dir[0]);
			printf("Card contains %d files\n",f);
			for(n=0;n<f;n++) printf("%s - %d slots\n",dir[n].name,dir[n].size/8192);

			printf("Saving...\n");
			ptr=(char *)buff;	
			for (n=0;n<65536;n++) *ptr++=n&0xFF;
			n=Card_Save(i,"SAVE1",buff,8192);
			if (n) printf("Save OK\n");
			else printf("Error while saving\n");
			printf("Loading...\n");
			memset(buff,0,65536);
			n=Card_Load(i,"SAVE1",buff,8192);
			if (n) printf("Load OK\n");
			else printf("Error while loading\n");
		}
	}
}
*/
#endif