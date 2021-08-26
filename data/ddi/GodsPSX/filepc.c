
//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// File Handler For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

// Include all Header Files

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
#include	"libgods.h"
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

File_Globs fileGlobs;



int			pc_load_flag;
int			alternate_path_flag;
int			files_loaded;
int			file_total;
LPUCHAR		sector_buffer;

void	reset_file_total(void)
{
	file_total=0;
}

int	get_file_total(void)
{
	return	file_total;
}

void	set_load_flag(int flag)
{
	pc_load_flag=flag;
}

void	set_alternate_path_flag(int flag)
{
	alternate_path_flag=flag;
}

static void AddSectorsToFilePosition(CdlLOC* position, int amountSectors);

#ifdef CD_FILES



void File_Initialise(void)
{
	int	ret;

	sprintf(fileGlobs.dataDir, "\\%s\\", FILE_DATADIRNAME);		/* no debug path for CD */

/* initialise CD system */

	ret=CdInit();
	if (ret==0)
		printf("CDinit Failed");

	pc_load_flag=FALSE;
	alternate_path_flag=FALSE;
	files_loaded=0;
	sector_buffer=Mem_Malloc(2048);

}


VOID	string_to_upper(LPUCHAR string)
{
	int	n,l=strlen(string);

	for (n=0; n<l; n++)
	{
		if (string[n]>='a' && string[n]<='z')
			string[n]-=32;
	}
}






/*
	now loads from either pc or emulator/CD directly
	pc_load_flag determines which

	to do:
			automatic search for duplicate files on pc (toggled)
			read from .WAD file.

*/
LPVOID	File_LoadBinary(LPUCHAR name, LPULONG size)
{
	Sint32	handle, read, length;
	LPUCHAR	temp_addr,path_ptr;
	UCHAR		result,pathname[128];
	long		sector_count,remainder;
	LPUCHAR addr = NULL;
	CdlFILE  fp;


/* files are pathed differently for CD */


	if (!pc_load_flag)
	{

		*size = NULL;

/* load from CD/emulator */

		sprintf(pathname, "%s%s;1", fileGlobs.dataDir, name);
		string_to_upper(pathname);

		if(!CdSearchFile(&fp, pathname))
		{
		  	printf("File not found :- %s \n",name);
			return	FALSE;
		}
		else
		{

			file_total+=fp.size;
			
			if (fileGlobs.loadCallback)
				fileGlobs.loadCallback(name, fp.size, fileGlobs.loadCallbackData);
			
			addr =Mem_Malloc(fp.size);
			*size=fp.size;
			
			/* calculate whole sectors and remainder to transfer */
			
			sector_count=fp.size/2048;
			remainder=fp.size&2047;
			
			path_ptr=pathname;
			
			if (sector_count)
			{
				if(!(read=CdReadFile(pathname, (void*) addr, (sector_count*2048))))
				{
					Mem_Free(addr);
					return (void*) FAIL;
				}
				
				CdReadSync(NULL, &result);
				path_ptr=NULL;						/* ensure remainder reads from current position */
			}
			
			if (remainder)
			{
				int		n;
				
				temp_addr=addr+(sector_count*2048);		/* transfer address for remainder */
				
				if(!(read=CdReadFile(path_ptr, (void*) sector_buffer, 2048)))
				{
					Mem_Free(addr);
					return (void*) FAIL;
				}
				CdReadSync(NULL, &result);
				
				/* transfer remainder of file */
				
				for (n=0; n<remainder; n++)
					*temp_addr++=*(sector_buffer+n);
				
			}
			
			files_loaded++;
		}

		// Unpack Propack files...	-ADRIAN-
		if (*((long *)addr)==0x02434E52)
		{
			addr=File_Unpack(addr);
		}

		return addr;


	}
	else		/* load from pc directly */
	{
		sprintf(pathname, "%s\\%s%s", _DEBUGPATH, "CD_ROOT\\DATA\\",name);		/* cd_root is used to separate PSX data from general crud on the target, when creating a .CTI file for cutting/emulation */
		string_to_upper(pathname);
///		printf ("Loading -- %s\n", pathname);

		if ((handle = PCopen(pathname, NULL, NULL)) < 0)
		{
			char	string[128];

		  	printf("File not found :- %s \n",pathname);
			sprintf(string,"|3NOT FOUND: %s",name);

			if (fileGlobs.loadCallback)
				fileGlobs.loadCallback(string, 0, fileGlobs.loadCallbackData);

			return NULL;
		}


		length = PClseek(handle, NULL, 2);
		file_total+=length;


		if (fileGlobs.loadCallback)
		{
//			printf ("Callback attempting\n");
//			fileGlobs.loadCallback(name, length, fileGlobs.loadCallbackData);
//			printf ("Callback called ok\n");
		}
		
		if(length>25000000)
		{
			printf("File loading %s sized %d\n",name, length);
		}

		if(!(addr = Mem_Malloc(length)))
		{
			printf("Memory failed loading %s\n",name);
			PCclose(handle);
			return NULL;
		}

		PClseek(handle, NULL, NULL);
		
		if ((read = PCread(handle, addr, length)) < 0)
		{
			PCclose(handle);
			Mem_Free(addr);
			return NULL;
		}

		PCclose(handle);
		*size = length;
		files_loaded++;

		// Unpack Propack files...	-ADRIAN-
		if (*((long *)addr)==0x02434E52)
		{
			addr=File_Unpack(addr);
		}

		return addr;

	}
}


/*
	as above, but we don't care about the size
*/
LPVOID	File_Load(LPUCHAR name)
{
	ULONG		size;

	return	File_LoadBinary(name, &size);
}



void	File_SetLoadCallback(void (*Callback)(LPUCHAR filename, ULONG filesize, LPVOID data), LPVOID data)
{
	fileGlobs.loadCallback = Callback;
	fileGlobs.loadCallbackData = data;
}



#else

void File_Initialise(void)
{
	sprintf(fileGlobs.dataDir, "%s\\%s\\", _DEBUGPATH, FILE_DATADIRNAME);
}


LPVOID	File_LoadBinary(LPUCHAR name, LPULONG size)
{
	Sint32	handle, read, length;
	LPUCHAR	addr;
	UCHAR		pathname[1024];

//	printf("File :- %s \n",name);
	sprintf(pathname, "%s%s", fileGlobs.dataDir, name);

	if ((handle = PCopen(pathname, NULL, NULL)) < 0)
	{
		return NULL;
	}

	length = PClseek(handle, NULL, 2);

	if (fileGlobs.loadCallback) fileGlobs.loadCallback(name, length, fileGlobs.loadCallbackData);

	if(!(addr = Mem_Malloc(length)))
	{
		PCclose(handle);
		return NULL;
	}

	PClseek(handle, NULL, NULL);

	if ((read = PCread(handle, addr, length)) < 0)
	{
		PCclose(handle);
		Mem_Free(addr);
		return NULL;
	}

	PCclose(handle);

	*size = length;
	return addr;
}


void	File_SetLoadCallback(void (*Callback)(LPUCHAR filename, ULONG filesize, LPVOID data), LPVOID data)
{
	fileGlobs.loadCallback = Callback;
	fileGlobs.loadCallbackData = data;
}


#endif



#ifdef 0


/*
		.WAD file stuff
*/

#define	DIRECTORY_ENTRY		(0x80000000)		/* top bit in length defines directory entry */

typedef enum
{
	WAD_FILE_ERROR_WAD_NOT_FOUND,			/* oh dear, we are in trouble */
	WAD_FILE_ERROR_PATH_NOT_FOUND,
	WAD_FILE_ERROR_FILE_NOT_FOUND,
	WAD_FILE_ERROR_SEEK_ERROR,
	WAD_FILE_ERROR_READ_ERROR,
	WAD_FILE_ERROR_ALLOCATION_ERROR,
	WAD_FILE_INTERNAL_ERROR,
	WAD_FILE_OK,

} WAD_STATUS;

/*
	directories will be handled as follows:

	if length is zero, it's a directory entry, else a file.
	next_dir is the index of the next directory structure at
	the same level.

*/

typedef	struct wad_entry_st
{
	UCHAR		name[16];
	ULONG		start_sector;
	ULONG		length;
	long		next_dir;			/* these last two could be short but it */
	long		first_file;			/* nicely pads the structure to 32 bytes */

}	WAD_ENTRY;


WAD_ENTRY	wad_directory[]=
{


		{
			"DATA",
			0,
			0,
			-1,		/* no more directories at this level */
			7,				/* first entry with files at this level */
		},

};


#define		MAX_WAD_ENTRIES		(512)

typedef	struct wad_dfs_st
{
	long			last_used_entry;
	UCHAR			last_used_path[256];
	WAD_ENTRY	wad_directory[MAX_WAD_ENTRIES];
}	WAD_DFS;


WAD_DFS		file_system;


/*
	scan for files within a directory block
*/
WAD_STATUS	File_scan_file_list(long wad_entry, UCHAR *file_name, ULONG *length, ULONG *start_sector)
{
	WAD_ENTRY	*file_entry=&wad_directory[wad_entry];

	while (file_entry->length>0)
	{
		if (strcmp(file_name,file_entry->name)==0)
		{
			*length=file_entry->length;
			*start_sector=file_entry->start_sector;

			return	WAD_FILE_OK;
		}
		file_entry++;
	}
	return	WAD_FILE_ERROR_FILE_NOT_FOUND;
}


/*
		search for file in wad, if found return length and start_sector
*/
WAD_STATUS	File_get_wad_entry(UCHAR *filespec, ULONG *length, ULONG *start_sector)
{
	UCHAR			path_name[80],file_name[16];
	UCHAR			match_path[80],scratch_path[80];
	UCHAR			*cp,*tp,*pn;
	WAD_ENTRY	*current_entry;
	WAD_STATUS	status;
	int			current_index;

	/* first separate path and filename */

	string_to_upper(filespec);

	cp=(UCHAR*)strrchr((UCHAR*)filespec, '\\');
	if (cp==NULL)
	{
		strcpy(file_name,filespec);			/* filename */
		path_name[0]=0;							/* no path */
	}
	else
	{
		strcpy(file_name,cp+1);
		tp=filespec;

	/* copy path and terminate string */

		pn=path_name;
		while (tp!=cp)
			*pn++=*tp++;
		*pn=0;
	}


	/* check for match with last used path */

	if (strcmp(file_system.last_used_path,path_name)==0)			/* path matches, we can scan from saved reference */
	{
		return File_scan_file_list(file_system.last_used_entry, file_name, length, start_sector);
	}

	/* now we attempt to match directories */

	match_path[0]=0;
	current_index=0;

	current_entry=&wad_directory[current_index];
	strcpy(match_path,current_entry->name);
	strcat(match_path,"\\");

	for (;;)
	{
		current_entry=&wad_directory[current_index];

		if (current_entry->length>0)
			return	WAD_FILE_INTERNAL_ERROR;		/* we should only see directory entries here */

		strcpy(scratch_path,match_path);
		strcat(scratch_path,current_entry->name);
		strcat(scratch_path,"\\");


		if (strncmp(scratch_path,path_name,strlen(match_path))==0)
		{

			if (strlen(scratch_path)==strlen(path_name))
			{
				/* complete path found, find file */

				status=File_scan_file_list(current_entry->first_file, file_name, length, start_sector);
				if (status==WAD_FILE_OK)
				{

				/* cache current path/entry if file is good */

					file_system.last_used_entry=current_entry->first_file;
					strcpy(file_system.last_used_path,scratch_path);
				}
				return	status;
			}

		/* current path matches, so go down a level */

			strcpy(match_path,scratch_path);			/* set as default */
			current_index++;
		}
		else
		{
			/* go to next entry at this level (or stop) */

			current_index=current_entry->next_dir;
			if (current_index<0)
				return	WAD_FILE_ERROR_PATH_NOT_FOUND;
		}
	}
}






/*
	initialise .WAD file by reading in directory
	sectors will be the number of sectors read for the
	directory entries.
*/

WAD_STATUS File_init_wad(UCHAR *filename,int sectors)
{
	ULONG		numSectors;				/* NUMBER OF SECTORS THE FILE TAKES UP */
  CdlFILE  fp;

	file_system.last_used_entry=-1;
	strcpy(file_system.last_used_path,"NO\\LAST\\PATH");

/* read .WAD file header */

	if (!CdSearchFile(&fp,filename))
		return	WAD_FILE_ERROR_WAD_NOT_FOUND;

	if (!CdControlB(CdlSeekL,(UCHAR*)&fp.pos, 0))
		return WAD_FILE_ERROR_SEEK_ERROR;

    numSectors=8;					/* READ IN 8 SECTORS (DIRECTORY STRUCTURE) */

    if(!CdRead(sectors,(ULONG*) wad_directory,mode))
      return WAD_FILE_ERROR_READ_ERROR;

	if (CdReadSync(0,result)==0)
		return	WAD_FILE_OK;
	else
		return	WAD_FILE_ERROR_READ_ERROR;
}



#endif




#define PSX_WAD_HEADER		("WWAD")
#define PSX_WAD_HEADER_ID	("PWAD")






/* FUNCTION DEFINITIONS *****************************************************/
/*																			*/

int WAD_Open(char* wadName)
{

int handle;
char pathname[50], string[50];

#ifdef __CDVERSION

	/* Load from CD */
	
	return 0; // Don't need to open CD files

#else

	/* Load from PC */

	sprintf(pathname, "%s\\%s%s", _DEBUGPATH, "CD_ROOT\\DATA\\", wadName);
	string_to_upper(pathname);

	if ((handle = PCopen(pathname, 0, 0)) < 0)
	{
		char	string[128];

	  	printf("File not found :- %s \n", wadName);
		sprintf(string,"|3NOT FOUND: %s", wadName);

		if (fileGlobs.loadCallback)
			fileGlobs.loadCallback(string, 0, fileGlobs.loadCallbackData);

		return -1;
	}

	return handle;

#endif

}/* WAD_Open */




int WAD_Close(int wadHandle)
{

#ifdef __CDVERSION

	/* Work from CD */

	return 0;	// Don't need to close CD files
				// but could maybe pause CD or summit

#else

	/* Work from PC */

	return PCclose(wadHandle);


#endif

}/* WAD_Close */




int WAD_Initialise(wad_handler* wadHandler, char* wadName, int contiguous)
{
	int		wadId;
	int		wadEntryStart;
	int		stringTableSize;
	int		i;
	char*	currentChar;
	int		wadEntrySize = sizeof(WadEntry);
	
if (!pc_load_flag)
{
	
	char	pathname[128];
	int		stringTableSectorSize;
	int		wadEntrySectorSize, wadEntrySectorStart;
	char*	sectorBuffer, *fetchPointer;
	CdlLOC	wadEntryLocation;

	int		fileStart, fileLength, fileSectorStart;
	CdlLOC	fileLocation;



	if( !(wadHandler->file = Mem_Malloc(sizeof(CdlFILE))) )
		return 1;


	/* Get the files position and size */
	if( !CD_GetFileDescription(wadName, wadHandler->file) )
		return 1;


	/* Read the first sector - 2048 bytes */
	if( !(sectorBuffer = Mem_Malloc(2048)) )
		return 1;

	CD_ReadB(&wadHandler->file->pos, (u_long*)sectorBuffer, 1);


	/* Extract the header from the sector - top 4 bytes*/
	wadId = ((int*)sectorBuffer)[0];


	/* Check file is a PSX WAD	*/
//	if(wadId != PSX_WAD_HEADER_ID)
//	{
//		printf("Failed header check\n");
//		return 1;
//	}

	/* Get the number of files in the WAD - next 4 bytes*/
	wadHandler->fileCount = ((int*)sectorBuffer)[1];


	/* Get the number of bytes to top of WadEntrys */
	wadEntryStart = ((int*)sectorBuffer)[2];



	/* String table takes up all space to top of WadEntrys less		*/
	/* the 12 bytes we've used already								*/
	/* But we need to ignore it for the sector						*/
	stringTableSize = wadEntryStart;


	/* Convert string table size from bytes to sectors				*/
	stringTableSectorSize	= (stringTableSize + 2047) / 2048;

	/* Check if more sectors need read in */
	if(stringTableSectorSize > 1)
	{
		/* Free what we've got */
		Mem_Free(sectorBuffer);

		/* Allocate enough memory for next read */
		if( !(sectorBuffer = Mem_Malloc(2048 * stringTableSectorSize)) )
			return 1;

	}

	/* Take the 12 bytes off before allocating memory */
	stringTableSize -= 12; 

	/* Malloc enough space for the strings */
	if( !(wadHandler->stringData = (char*)Mem_Malloc(stringTableSize)) )
	{
		Mem_Free(sectorBuffer);
		return 1;
	}

	/* Read in all of the string table */
	CD_ReadB(&wadHandler->file->pos, (u_long*)sectorBuffer, stringTableSectorSize);

	/* Shift out 12 bytes of header info */
	fetchPointer = sectorBuffer;
	fetchPointer += 12;

	/* Copy the useful stuff into the memory */
	memcpy(wadHandler->stringData, fetchPointer, stringTableSize);

	/* Create a set of pointer to wadHeader->fileCount strings	*/
	/* and attach them to the start of each string				*/

	if(!(wadHandler->stringTable = (char**)Mem_Malloc(wadHandler->fileCount * sizeof(char*))) )
	{
		Mem_Free(wadHandler->stringTable);
		Mem_Free(sectorBuffer);
		return 1;
	}

	/* Parse the strings and set a pointer to beginning of each */

	currentChar = wadHandler->stringData;

	for(i=0;i<wadHandler->fileCount;i++)
	{
		wadHandler->stringTable[i] = currentChar;

		while(*currentChar)
		{
			currentChar++;
		}

		currentChar++;

	}

	/* Allocate memory for WadEntrys and read them in */

	/* Malloc enough space for the wad entry structures */
	if( !(wadHandler->wadEntry = 
			(WadEntry*)Mem_Malloc(wadHandler->fileCount * wadEntrySize)) )
	{
		
		Mem_Free(wadHandler->stringTable);
		Mem_Free(wadHandler->stringData);
		Mem_Free(sectorBuffer);
		return 1;
	}

	/* Work out how many sectors the wadEntrys are over */
	wadEntrySectorSize = ((wadHandler->fileCount * wadEntrySize) + (wadEntryStart%2048) + 2047) / 2048;

	/* Work out which sector the wadEntrys start on */
	wadEntrySectorStart = ByteToSectorOffset(wadEntryStart);

	if(wadEntrySectorSize != stringTableSectorSize)
	{
		Mem_Free(sectorBuffer);

		if(!(sectorBuffer = Mem_Malloc(2048 * wadEntrySectorSize)) )
		{
			Mem_Free(wadHandler->stringTable);
			Mem_Free(wadHandler->stringData);
			Mem_Free(wadHandler->wadEntry);
		
			return 1;
		}
	}

	/* Read in all of the WadEntrys */
	wadEntryLocation.sector = wadHandler->file->pos.sector;
	wadEntryLocation.second = wadHandler->file->pos.second;
	wadEntryLocation.minute = wadHandler->file->pos.minute;

	AddSectorsToFilePosition(&wadEntryLocation, wadEntrySectorStart);

	CD_ReadB(&wadEntryLocation, (u_long*)sectorBuffer, wadEntrySectorSize);


	/* Shift out all the info that isn't anything to do with WadEntrys */
	fetchPointer = sectorBuffer;
	fetchPointer += wadEntryStart % 2048;

	/* Copy the useful stuff into the wad handler */
	memcpy(wadHandler->wadEntry, fetchPointer, (wadHandler->fileCount * wadEntrySize));

	/* Free up memory before leaving function */
	Mem_Free(sectorBuffer);


if(contiguous)
{
	/*								*/
	/* Set CD head to first frame	*/
	/*								*/

	fileStart = wadHandler->wadEntry[0].addr;
	fileLength = wadHandler->wadEntry[0].length;

	/* Calculate how many sectors into the file we want to start */
	fileSectorStart = ByteToSectorOffset(fileStart);

	/* Adjust read start position */
	fileLocation.sector = wadHandler->file->pos.sector;
	fileLocation.second = wadHandler->file->pos.second;
	fileLocation.minute = wadHandler->file->pos.minute;

	AddSectorsToFilePosition(&fileLocation, fileSectorStart);

	/* Tell CD to seek to new position */
	CdControl(CdlSeekL, (u_char*)&fileLocation, 0);
}


	

	return 0;

}
else
{
	wadHandler->file = NULL;


	/* Open the file to read from */
	if( (wadHandler->fileId = WAD_Open(wadName)) < 0 )
	{
		
		return 1;
	}

	/* Set file position indicator to start of file */
	PClseek(wadHandler->fileId, 0, 0);

	/* Get the header to check the file is a PWAD */
	if(PCread(wadHandler->fileId, (char*)&wadId, 4) < 4)
		return 1;
	

//	if(wadId != (int)PSX_WAD_HEADER_ID)
//	{
//		printf("Failed header check\n");
//		return 1;
//	}

	/* Get the number of files in the wad */
	if(PCread(wadHandler->fileId, (char*)&wadHandler->fileCount, 4) < 4)
		return 1;


	/* Malloc enough room for the strings	*/
	/* and load them in						*/
	if(PCread(wadHandler->fileId, (char*)&wadEntryStart, 4) < 4)
		return 1;
	

	stringTableSize = wadEntryStart - 12; // 12 bytes we've just used

	if( !(wadHandler->stringData = (char*)Mem_Malloc(stringTableSize)) )
	{
		
		return 1;
	}

	
	/* Read in the strings relating to each filename			*/

	if(PCread(wadHandler->fileId, (char*)wadHandler->stringData, stringTableSize) < stringTableSize)
	{
		Mem_Free(wadHandler->stringData);
		return 1;
	}

	/* Create a set of pointer to wadHeader->fileCount strings	*/
	/* and attach them to the start of each string				*/

	if(!(wadHandler->stringTable = (char**)Mem_Malloc(wadHandler->fileCount * sizeof(char*))) )
	{
		Mem_Free(wadHandler->stringTable);
		return 1;
	}

	/* Parse the strings and set a pointer to beginning of each */

	currentChar = wadHandler->stringData;

	for(i=0;i<wadHandler->fileCount;i++)
	{
		wadHandler->stringTable[i] = currentChar;

		while(*currentChar)
		{
			currentChar++;
		}

		currentChar++;

	}


	/* Should be at start of WadEntrys but move */
	/* there just to be safe					*/
	PClseek(wadHandler->fileId, wadEntryStart, 0);

	/* Malloc enough space for the wad entry structures */
	if( !(wadHandler->wadEntry = 
			(WadEntry*)Mem_Malloc(wadHandler->fileCount * wadEntrySize)) )
	{
		
		Mem_Free(wadHandler->stringTable);
		Mem_Free(wadHandler->stringData);
		return 1;
	}

	if(PCread(wadHandler->fileId, (char*)wadHandler->wadEntry, wadHandler->fileCount * wadEntrySize) < 
														wadHandler->fileCount * wadEntrySize)
	{
		Mem_Free(wadHandler->stringTable);
		Mem_Free(wadHandler->stringData);
		Mem_Free(wadHandler->wadEntry);
		return 1;
	}
	
	return 0;


}
}/* WAD_Initialise */





int WAD_GetWadEntryPosition(wad_handler* wadHandler, char* filename)
{
	int i;


	for(i=0;i < wadHandler->fileCount;i++)
	{
		if(!stricmp(wadHandler->stringTable[i], filename) )
			return i;
		
	}

	// File not found
	return -1;


}/* WAD_GetWadEntryPosition */




void* WAD_LoadFileIndex(wad_handler* wadHandler, int index, int contiguous)
{
	int		fileStart, fileSectorStart;
	int		fileLength, fileSectorLength;
	char*	file;
	char*	sectorBuffer;
	char*	fetchPointer;
	CdlLOC	fileLocation;


	/* Check the index exists */
	if(index > wadHandler->fileCount)
		return NULL;

	fileStart = wadHandler->wadEntry[index].addr;
//	printf("File start = %d\n", fileStart);
	fileLength = wadHandler->wadEntry[index].length;
//	printf("File length = %d\n", fileLength);

	/* Calculate how many sectors need read */
	fileSectorLength = ((fileLength + (fileStart%2048)) + 2047)/2048;


	if(contiguous)
	{
		/* Malloc enough memory for file */
		if(!(file = Mem_Malloc(fileSectorLength * 2048)) )
		{
			return NULL;
		}
	}

	else
	{
		/* Malloc enough memory for file */
		if(!(file = Mem_Malloc(fileLength)) )
		{
			return NULL;
		}
	}


	if (!pc_load_flag)
	{


		if(!contiguous)
		{
			/* Calculate how many sectors into the file we want to start */
			fileSectorStart = ByteToSectorOffset(fileStart);

			/* Adjust read start position */
			fileLocation.sector = wadHandler->file->pos.sector;
			fileLocation.second = wadHandler->file->pos.second;
			fileLocation.minute = wadHandler->file->pos.minute;

			AddSectorsToFilePosition(&fileLocation, fileSectorStart);

			if( !(sectorBuffer = Mem_Malloc(fileSectorLength * 2048)) )
			{
				Mem_Free(file);
				return NULL;
			}

			/* Read in the file information */
			CD_ReadB(&fileLocation, (u_long*)sectorBuffer, fileSectorLength);

			/* Shift out the info unrelated to the file wanted */
			fetchPointer = sectorBuffer;
			fetchPointer += fileStart % 2048;

			/* Copy the stuff we want */
			memcpy(file, fetchPointer, fileLength);

			/* Free up memory before leaving function */
			Mem_Free(sectorBuffer);
		}
		else
		{
			/* Read in the file information */
			CD_ReadC((u_long*)file, fileSectorLength);

			/*								*/
			/* Set CD head a frame ahead	*/
			/*								*/

			/* Check the index exists */
			index++;
			if(index > wadHandler->fileCount)
				/* Assume wrap-round */
				index = 0;
				

			fileStart = wadHandler->wadEntry[index].addr;
			fileLength = wadHandler->wadEntry[index].length;

			/* Calculate how many sectors into the file we want to start */
			fileSectorStart = ByteToSectorOffset(fileStart);

			/* Adjust read start position */
			fileLocation.sector = wadHandler->file->pos.sector;
			fileLocation.second = wadHandler->file->pos.second;
			fileLocation.minute = wadHandler->file->pos.minute;

			AddSectorsToFilePosition(&fileLocation, fileSectorStart);

			/* Tell CD to seek to new position */
			CdControl(CdlSeekL, (u_char*)&fileLocation, 0);
		}

		// Unpack Propack files...	-ADRIAN-
		if (*((long *)file)==0x02434E52)
		{
			file=File_Unpack(file);
		}

		return (void*)file;

	}
	else
	{
	
		PClseek(wadHandler->fileId, fileStart, 0);

		if(PCread(wadHandler->fileId, file, fileLength) < fileLength)
		{
			Mem_Free(file);
			return NULL;
		}

		// Unpack Propack files...	-ADRIAN-
		if (*((long *)file)==0x02434E52)
		{
			file=File_Unpack(file);
		}

		return (void*)file;

}

}/* WAD_LoadFileIndex */




void* WAD_LoadFile(wad_handler* wadHandler, char* filename, int contiguous)
{
	int index;

	if((index = WAD_GetWadEntryPosition(wadHandler, filename)) < 0)
		return NULL;


	return WAD_LoadFileIndex(wadHandler, index, contiguous);

}/* WAD_LoadFile */



int WAD_DeInitialise(wad_handler* wadHandler)
{

if (!pc_load_flag)
{

	if(wadHandler->file)
	{
		Mem_Free(wadHandler->file);
	}
	else
		return 1;

}
else
{
	if(!(wadHandler->fileId < 0))
	{
		WAD_Close(wadHandler->fileId);
		wadHandler->fileId = -1;
	}
	else
		return 1;

}

	if(wadHandler->stringTable)
	{
		Mem_Free(wadHandler->stringTable);
		wadHandler->stringTable = NULL;
	}
	else
		return 1;

	if(wadHandler->stringData)
	{
		Mem_Free(wadHandler->stringData);
		wadHandler->stringData = NULL;
	}
	else
		return 1;

	if(wadHandler->wadEntry)
	{
		Mem_Free(wadHandler->wadEntry);
		wadHandler->wadEntry = NULL;
	}
	else
		return 1;


	return 0;


}/* WAD_DeInitialise */




/*														*/
/* Function from Sony docs								*/
/* It didn't work though  so I've changed it - ScoTTC	*/
/*														*/

int CD_ReadB(CdlLOC *loc, u_long *buf, int nsector)
/* target position */ /* memory address */ /* number of sectors read */
{
	int cnt;
	u_char param[4];

	/* set double speed mode */
	param[0] = CdlModeSpeed;
	CdControl(CdlSetmode, 0, 0);

	/* Wait to stop possible H/W problem */
	VSync(3);

	/* set target position */
	CdControl(CdlSeekL, (u_char*)loc, 0);
	
	/* start read */
	CdRead(nsector, buf, 0);

	/* monitor number of sectors remaining until read ends */
	CdReadSync(NULL, NULL);

	return(cnt);
}



int CD_ReadC(u_long *buf, int nsector)
/* memory address */ /* number of sectors read */
{
	int cnt;
	u_char param[4];


	/* Assuming that the CD is already st 2-Speed */
	/* set double speed mode */
//	param[0] = CdlModeSpeed;
//	CdControl(CdlSetmode, 0, 0);

	/* start read */
	CdRead(nsector, buf, 0);

	/* monitor number of sectors remaining until read ends */
	CdReadSync(NULL, NULL);

	return(cnt);
}



BOOL CD_GetFileDescription(char* filename, CdlFILE* file)
{
	char	pathname[128];

	sprintf(pathname, "%s%s;1", fileGlobs.dataDir, filename);
	string_to_upper(pathname);

	if(!CdSearchFile(file, pathname))
	{
		printf("%s not found\n", pathname);
		return FALSE;
	}

	return TRUE;

}/* CD_GetFileDescription */



int ByteToSectorOffset(int offset)
{
	return offset/2048;

}/* OffsetToSector */



static void AddSectorsToFilePosition(CdlLOC* position, int amountSectors)
{
	int	absoluteSector;

	absoluteSector = CdPosToInt(position);

	absoluteSector += amountSectors;

	CdIntToPos(absoluteSector, position);

}/* AddSectorsToPosition */






typedef struct
{
	char Id[3];
    char Method;
    u_long UncompressedSize;
    u_long CompressedSize;
}
RNCHeader;

extern void RNC_Unpack(void *, void *);

void *File_Unpack(void *source)
{
	RNCHeader *rnc;
	void *dest;
	u_long n,size;

	rnc=(RNCHeader *)source;
	n=rnc->UncompressedSize;
	size=(n >> 24) | ((n & 0x00FF0000) >> 8)  | ((n & 0x0000FF00) << 8) | (n << 24);
	dest=Mem_Malloc(size);
	
	RNC_Unpack(source,dest);
	Mem_Free(source);

	return(dest);
}
