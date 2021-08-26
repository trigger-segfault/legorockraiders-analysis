//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// File.c - [File Handling Code]
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹


/* define for non-pc file version */
#define		CD_FILES

#define	_MAX_PATH				256
#define FILE_DATADIRNAME	"DATA"
ext		LPUCHAR	_DEBUGPATH;

enum
{
	FROM_CD,
	FROM_PC,
};

enum
{
	File_SeekSet,
	File_SeekCur,
	File_SeekEnd
};


typedef struct File_Dummy { ULONG null; } *lpFile;

typedef struct File_Globs
{
	Uint8 	dataDir[_MAX_PATH];
	void		(*loadCallback)();
	LPVOID	loadCallbackData;
} File_Globs, *lpFile_Globs;








/* This is the structure that Andy Ray defined */

typedef struct{
	int		length;
	int		addr;
}WadEntry;



typedef struct{

	CdlFILE*		file;		// Used to track file on CD	
	int				fileId;		// Used to track file on PC
	int				fileCount;
	char**			stringTable;
	char*			stringData;
	WadEntry*		wadEntry;
}wad_handler;








void 	File_Initialise(void);
LPVOID	File_LoadBinary(LPUCHAR name, LPULONG size);
LPVOID	File_Load(LPUCHAR name);

void	reset_file_total(void);
int	get_file_total(void);
void	set_load_flag(int flag);
void	set_alternate_path_flag(int flag);


/* Wad stuff added by ScoTTC */


static int WAD_Open(char* wadName);
static int WAD_Close(int wadHandle);
/* static functions used internally */

/* WAD functions return values	*/
/* 1/NULL		:	FAIL		*/
/* 0/NON-NULL	:	SUCCESS		*/
	
int WAD_Initialise(wad_handler* wadHandler, char* wadName, int contiguous);
/* Initialises a wad_handler with the header info in the WAD file wadName */

int WAD_GetWadEntryPosition(wad_handler* wadHandler, char* filename);
/* Returns the position of file filename in the wad referred to by wadHandler */

void* WAD_LoadFileIndex(wad_handler* wadHandler, int index, int contiguous);
/* Loads the file at position index in the WAD referred to by wadHandler */

void* WAD_LoadFile(wad_handler* wadHandler, char* filename, int contiguous);
/* Loads the file filename from the WAD referred to by wadHandler */

int WAD_DeInitialise(wad_handler* wadHandler);
/* Frees up memory allocations and releases any open file */


int CD_ReadB(CdlLOC *loc, u_long *buf, int nsector);

int CD_ReadC(u_long *buf, int nsector);

BOOL CD_GetFileDescription(char* filename, CdlFILE* file);

int ByteToSectorOffset(int offset);

extern void *File_Unpack(void *);
