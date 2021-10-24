
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
	LPUCHAR	addr,temp_addr,path_ptr;
	UCHAR		result,pathname[128];
	long		sector_count,remainder;
  CdlFILE  fp;

/* files are pathed differently for CD */


	if (!pc_load_flag)
	{


/* load from CD/emulator */

		sprintf(pathname, "%s%s;1", fileGlobs.dataDir, name);
		string_to_upper(pathname);

		if(!CdSearchFile(&fp, pathname))
		{
			return NULL;
		}

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
		return addr;


	}
	else		/* load from pc directly */
	{
		sprintf(pathname, "%s\\%s%s", _DEBUGPATH, "CD_ROOT\\DATA\\",name);		/* cd_root is used to separate PSX data from general crud on the target, when creating a .CTI file for cutting/emulation */
		string_to_upper(pathname);

		if ((handle = PCopen(pathname, NULL, NULL)) < 0)
		{
			char	string[128];

			sprintf(string,"|3NOT FOUND: %s",name);

			if (fileGlobs.loadCallback)
				fileGlobs.loadCallback(string, 0, fileGlobs.loadCallbackData);

			return NULL;
		}

		length = PClseek(handle, NULL, 2);
		file_total+=length;

		if (fileGlobs.loadCallback)
			fileGlobs.loadCallback(name, length, fileGlobs.loadCallbackData);

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
		files_loaded++;
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

/* test structure:


[0]	data/
[1]		vehicles/
[2]			v1.dat
[3]			v2.dat
[4]		levels/
[5]			lev1.bin
[6]			lev2.bin
[7]		lego.cfg
[8]	end_dir/
*/

/* 0 */

		{
			"DATA",
			0,
			0,
			-1,		/* no more directories at this level */
			7,				/* first entry with files at this level */
		},

#ifdef 0
/* 1 */
				{
					"VEHICLES",
					0,
					0,
					4,
					2,
				},

/* 2 */
						{
							"V1.DAT",
							12,
							2000,
							-1,
							-1,
						},

/* 3 */
						{
							"V2.DAT",
							14,
							1000,
							-1,
							-1,
						},

/* 4 */
				{
					"LEVELS",
					0,
					0,
					-1,
					-1,
				},

/* 5 */
						{
							"LEV1.BIN",
							45,
							4000,
							-1,
							-1,
						},

/* 6 */
						{
							"LEV2.BIN",
							100,
							4500,
							-1,
							-1,
						},

/* 7 */
		{
			"LEGO.CFG",
			23,
			123,
			-1,
			-1,
		},


/* 8 */
		{
			"END_DIR",
			0,
			0,
			-1,
			-1,
		},
#endif
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
