/////////////////////////////////////////////////////////////////
// Wads
// Andy Ray. 1998.

#include <windows.h>
#include <commctrl.h>
#include <d3drmwin.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <shlobj.h>
#include <io.h>

#define _DO_NOT_DEFINE_ANSI_TO_INTERNAL_FILE_SYSTEM
#define TEMP_WAD_NAME "Wad_Temp_File"

#include "..\inc\wad.h"
#include "..\inc\errors.h"
#include "..\inc\compress.h"

#define Debug_Format Error_Format

#undef fopen
#undef fclose
#undef fwrite
#undef fread
#undef flen
#undef ftell
#undef fseek
#undef flength

// Number of WADS you can have at one time
#define MAX_OPEN_FILES 100
#define MAX_FILE_COMPRESSION_SIZE (1024*1024)

#define WAD(which) wadGlobs.wads[which]
#define CURWAD wadGlobs.wads[wadGlobs.activeWad]

// Name of the computer so we can constuct network paths
char computerName[MAX_COMPUTERNAME_LENGTH + 1];
DWORD computerNameLength = MAX_COMPUTERNAME_LENGTH + 1;
BOOL wadLogFileAccess = FALSE;
static int _Wad_IsFileInWad(char *fName, int wadNo);
static int _Wad_FileOpen(char *fName, int wadNo);

struct
{
	void *data;					// Pointer to the file data
	BOOL active;				// Is this handle active already
	int wadFile;				// Wad file this handle uses
	int indexOfFileInWad;		// Index of the file in the wad structure
} fileHandles[MAX_OPEN_FILES];

struct
{
	Wad wads[MAX_WADS];				// Wad structures
	int references[MAX_WADS];		// Current count of references to the wad file
} wadGlobs;

int wad_flength(FILE *f)
{
	int pos = ftell(f), len;
	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, pos, SEEK_SET);
	return len;
}

BOOL wad_fcheck(char *name)
{
	FILE *f;
	if (f = fopen(name, "rb"))
	{
		fclose(f);
		return TRUE;
	}
	else return FALSE;
}

void Wad_Error(char *msg, ...)
{
	char buffer[1024];
	va_list arg;
	va_start(arg, msg);
	vsprintf(buffer, msg, arg);
	va_end(arg);
	OutputDebugString(buffer);
}

void Wad_LogFileAccess(BOOL mode)
{
	wadLogFileAccess = mode;
}

void Wad_ErrorFile(char *msg, ...)
{
	static FILE *f;
	va_list arg;

	if (wadLogFileAccess)
	{
		va_start(arg, msg);
		if (f)
		{
			if (msg) vfprintf(f, msg, arg);
			else
			{
				fclose(f);
				f = 0;
			}
		}
		else if (!msg) 
		{
			f = fopen("wad.log", "w");
			fprintf(f, "Wad error log\n");
		}
		va_end(arg);
	}
}

/////////////////////////////////////////////////////////////////////
// Wad functions

BOOL GetFileName(FILE *f, char *buffer)
{
	char c;
	while (c = fgetc(f))
	{
		*buffer = c;
		buffer++;
	}
	*buffer = 0;
	return TRUE;
}

////////////////////////////////////////////////////
// Open the wad and map in the file data.
// Returns a handle to the wad file.
int Wad_Load(char *fName)
{
	int newWad, i, counter = 0;
	char header[4];
	FILE *f;

	newWad = Wad_GetFreeWadSlot();
	if (newWad == WAD_ERROR) return WAD_ERROR;

	// Load the wad
	f = Wad_Get(newWad)->fWad = fopen(fName, "rb");
	if (!f) return WAD_ERROR;

	Wad_Get(newWad)->active = TRUE;

	// Check to see if we actually have a wad file.
	if (fread(header, 1, 4, f) != 4) 
	{
		fclose(f);
		return WAD_ERROR;
	}
	if (memcmp(header, "WWAD", 4) != 0)
	{
		fclose(f);
		return WAD_ERROR;
	}

	// Get the number of files to load
	if (fread(&(Wad_Get(newWad)->numFiles), 1, sizeof(int), f) != sizeof(int))
	{
		fclose(f);
		return WAD_ERROR;
	}

	// The names are first
	Wad_Get(newWad)->wadNames =  (char **) malloc (sizeof(char *) * Wad_Get(newWad)->numFiles);
	Wad_Get(newWad)->fileNames = (char **) malloc (sizeof(char *) * Wad_Get(newWad)->numFiles);
	if (!Wad_Get(newWad)->wadNames || !Wad_Get(newWad)->fileNames) 
	{
		fclose(f);
		if (Wad_Get(newWad)->wadNames) free(Wad_Get(newWad)->wadNames);
		if (Wad_Get(newWad)->fileNames) free(Wad_Get(newWad)->fileNames);
		return -1;
	}
	memset(Wad_Get(newWad)->wadNames, 0, sizeof(char *) * Wad_Get(newWad)->numFiles);
	memset(Wad_Get(newWad)->fileNames, 0, sizeof(char *) * Wad_Get(newWad)->numFiles);

	// Reads the names of the files in the wad and on disk
	while (counter < Wad_Get(newWad)->numFiles)
	{
		char buffer[4096];		// Nice big buffer to read into likes.
		if (!GetFileName(f, buffer))
		{
			if (Wad_Get(newWad)->wadNames) 
			{
				for (i=0; i<Wad_Get(newWad)->numFiles; i++) 
					if (Wad_Get(newWad)->wadNames[i]) free(Wad_Get(newWad)->wadNames[i]);
				free(Wad_Get(newWad)->wadNames);
			}
			if (Wad_Get(newWad)->fileNames) free(Wad_Get(newWad)->fileNames);
			fclose(f);
			return WAD_ERROR;
		}
		else
		{
			Wad_Get(newWad)->wadNames[counter] = (char *) malloc(strlen(buffer) + 1);
			strcpy(Wad_Get(newWad)->wadNames[counter], buffer);

			Wad_Error("%s\n", Wad_Get(newWad)->wadNames[counter]);
		}
		counter++;
	}
	counter = 0;
	while (counter < Wad_Get(newWad)->numFiles)
	{
		char buffer[4096];		// Nice big buffer to read into likes.
		if (!GetFileName(f, buffer))
		{
			if (Wad_Get(newWad)->fileNames) 
			{
				for (i=0; i<Wad_Get(newWad)->numFiles; i++) 
					if (Wad_Get(newWad)->wadNames[i]) free(Wad_Get(newWad)->wadNames[i]);
				free(Wad_Get(newWad)->wadNames);
			}
			if (Wad_Get(newWad)->fileNames) 
			{
				for (i=0; i<Wad_Get(newWad)->numFiles; i++) 
					if (Wad_Get(newWad)->fileNames[i]) free(Wad_Get(newWad)->fileNames[i]);
				free(Wad_Get(newWad)->fileNames);
			}
			fclose(f);
			return WAD_ERROR;
		}
		else
		{
			Wad_Get(newWad)->fileNames[counter] = (char *) malloc(strlen(buffer) + 1);
			strcpy(Wad_Get(newWad)->fileNames[counter], buffer);

			Wad_Error("%s\n", Wad_Get(newWad)->fileNames[counter]);
		}
		counter++;
	}


	// Now we get the data.  Address of file, compression
	Wad_Get(newWad)->wadEntries = (WadEntry *) malloc(sizeof(WadEntry) * Wad_Get(newWad)->numFiles);
	if (!Wad_Get(newWad)->wadEntries)
	{
		if (Wad_Get(newWad)->fileNames) 
		{
			for (i=0; i<Wad_Get(newWad)->numFiles; i++) 
				if (Wad_Get(newWad)->wadNames[i]) free(Wad_Get(newWad)->wadNames[i]);
			free(Wad_Get(newWad)->wadNames);
		}
		if (Wad_Get(newWad)->fileNames) 
		{
			for (i=0; i<Wad_Get(newWad)->numFiles; i++) 
				if (Wad_Get(newWad)->fileNames[i]) free(Wad_Get(newWad)->fileNames[i]);
			free(Wad_Get(newWad)->fileNames);
		}
		fclose(f);
		return WAD_ERROR;
	}

	if (fread(Wad_Get(newWad)->wadEntries, 1, sizeof(WadEntry) * Wad_Get(newWad)->numFiles, f) != (int)(sizeof(WadEntry) * Wad_Get(newWad)->numFiles))
	{
		if (Wad_Get(newWad)->fileNames) 
		{
			for (i=0; i<Wad_Get(newWad)->numFiles; i++) 
				if (Wad_Get(newWad)->wadNames[i]) free(Wad_Get(newWad)->wadNames[i]);
			free(Wad_Get(newWad)->wadNames);
		}
		if (Wad_Get(newWad)->fileNames) 
		{
			for (i=0; i<Wad_Get(newWad)->numFiles; i++) 
				if (Wad_Get(newWad)->fileNames[i]) free(Wad_Get(newWad)->fileNames[i]);
			free(Wad_Get(newWad)->fileNames);
		}
		if (Wad_Get(newWad)->wadEntries) free(Wad_Get(newWad)->wadEntries);
		fclose(f);
		return WAD_ERROR;
	}

	return newWad;
}

void Wad_Close(int wadNo)
{
	int i;
	if (wadNo != WAD_ERROR)
	{
		if (Wad_Get(wadNo)->fileNames) 
		{
			for (i=0; i<Wad_Get(wadNo)->numFiles; i++) 
				if (Wad_Get(wadNo)->wadNames[i]) free(Wad_Get(wadNo)->wadNames[i]);
			free(Wad_Get(wadNo)->wadNames);
		}
		if (Wad_Get(wadNo)->fileNames) 
		{
			for (i=0; i<Wad_Get(wadNo)->numFiles; i++) 
				if (Wad_Get(wadNo)->fileNames[i]) free(Wad_Get(wadNo)->fileNames[i]);
			free(Wad_Get(wadNo)->fileNames);
		}
		if (Wad_Get(wadNo)->wadEntries) free(Wad_Get(wadNo)->wadEntries);
		fclose(Wad_Get(wadNo)->fWad);
	}
}

unsigned int Wad_Compress(void *input, void **output, unsigned int len)
{
	void *packedData=0;

	// Compress the buffer
	unsigned complen = RNC_Compress(RNC_COMPRESS_FAST, input, len, &packedData);
	if (!complen || complen > (len + COMPRESSION_UNPACK_BUFFER_EXTEND))
	{
		if (packedData) free(packedData);
		return 0;
	}
	else
	{
		// Shorten to the required length - 
		// this will never fail as the block will not be moved.
		packedData = realloc(packedData, complen);
	}

	if (output)
	{
		*output = packedData;
		return complen;
	}
	else
	{
		if (packedData) free(packedData);
		return complen;
	}
}

////////////////////////////////////////////////////
// Save a wad file to the disk.
// Returns boolean on failure.
int Wad_Save(char *wadName,		// Wad to write to
			 char **fNames,		// List of files to compress
			 char **wNames,		// names of files within wad
			 unsigned *flags,	// Flags for each file
			 int numFiles,
			 int wadHandle,
			 void (*ProgressUpdate)(int, BOOL, char *, char *)
			 )
{
	FILE *fout = 0;
	int i;
	int fileRunner;
	char tmpName[1024], path[1024];
#define FWRITE(ptr, num, fout) { if ((fwrite(ptr, num, 1, fout)) != 1) goto error; }

	Wad_LogFileAccess(FALSE);
	if (ProgressUpdate) ProgressUpdate(0, 0, 0, "Pass 1/2");
	
	if (wadHandle != WAD_ERROR)
	{
		_getcwd(path, 1024);
		if (path[strlen(path)-1] != '\\') strcat(path, "\\");
		strcat(path, TEMP_WAD_NAME);
		strcpy(tmpName, path);
		fout = fopen(tmpName, "wb");
	}
	else
	{
		fout = fopen(wadName, "wb");
	}

	// Open the error file
	Wad_ErrorFile(0);

	// Write the header
	FWRITE("WWAD", 4, fout);
	FWRITE(&numFiles, 4, fout);

	// Write the wad names
	for (i=0; i<numFiles; i++)
	{
		FWRITE(wNames[i], strlen(wNames[i]) + 1, fout);
	}


	// Write the file names
	for (i=0; i<numFiles; i++)
	{
		FWRITE(fNames[i], strlen(fNames[i]) + 1, fout);
	}

	fileRunner = ftell(fout);
	fileRunner += sizeof(WadEntry) * numFiles;

	// Write out the wad header structure
	for (i=0; i<numFiles; i++)
	{
		WadEntry we;
		int fLen;

		if (ProgressUpdate) ProgressUpdate((int)(100.0f * ((float) i / (float)numFiles)), 
											FALSE, wNames[i], 0);

		if ((flags[i] & WAD_FILE_IS_IN_WAD) && 
			(wadHandle != WAD_ERROR) && 
			(Wad_IsFileInWad(wNames[i], wadHandle) != WAD_ERROR))
		{
			int hFile = _Wad_FileOpen(wNames[i], wadHandle);
			fLen = Wad_hLength(hFile);

			if (hFile == WAD_ERROR)
			{
				if (ProgressUpdate) ProgressUpdate((int)(100.0f * ((float) i / (float)numFiles)), 
													TRUE, Debug_Format("Cannot get %s from wad", wNames[i]), 0);
				goto error;
			}

			if (fLen == 0)
			{
				if (ProgressUpdate) ProgressUpdate((int)(100.0f * ((float) i / (float)numFiles)), 
													TRUE, Debug_Format("%s File length is 0", wNames[i]), 0);
				goto error;
			}

			if (flags[i] & WAD_FILE_RNCOMPRESSED && fLen < MAX_FILE_COMPRESSION_SIZE) 
			{
				void *data = Wad_hData(hFile);
				if (!data)
				{
					if (ProgressUpdate) ProgressUpdate((int)(100.0f * ((float) i / (float)numFiles)), 
														TRUE, Debug_Format("%s could not get data", wNames[i]), 0);
					goto error;
				}
				we.fileLength = Wad_Compress(data, 0, fLen);
				if (!we.fileLength)
				{
					if (ProgressUpdate) ProgressUpdate((int)(100.0f * ((float) i / (float)numFiles)), 
														TRUE, Debug_Format("%s could not get data pointer", wNames[i]), 0);
					goto error;
				}
			} 
			else we.fileLength = fLen;
			if (fLen >= MAX_FILE_COMPRESSION_SIZE) 
			{
				flags[i] &= ~WAD_FILE_RNCOMPRESSED;
				flags[i] |= WAD_FILE_UNCOMPRESSED;
			}
			Wad_FileClose(hFile);
			we.decompressedLength = fLen;
			we.compression = (flags[i] & WAD_FILE_RNCOMPRESSED) ? WAD_FILE_RNCOMPRESSED : WAD_FILE_UNCOMPRESSED;
			we.addr = fileRunner;
			fileRunner += we.fileLength;
			FWRITE(&we, sizeof(WadEntry), fout);
		}
		else if (wad_fcheck(fNames[i]))
		{
			FILE *f = fopen(fNames[i], "rb");
			fLen = wad_flength(f);

			if (flags[i] & WAD_FILE_RNCOMPRESSED && fLen < MAX_FILE_COMPRESSION_SIZE) 
			{
				void *data = malloc(fLen);
				if (!data) goto error;
				fread(data, 1, fLen, f);
				// Need to compress the file here
				we.fileLength = Wad_Compress(data, 0, fLen);
				if (!we.fileLength)
				{
					if (ProgressUpdate) ProgressUpdate((int)(100.0f * ((float) i / (float)numFiles)), 
														TRUE, Debug_Format("%s compressed data size is 0", wNames[i]), 0);
				}
				free(data);
			} else we.fileLength = fLen;
			fclose(f);
			if (fLen >= MAX_FILE_COMPRESSION_SIZE)
			{
				flags[i] &= ~WAD_FILE_RNCOMPRESSED;		// Remove the compression flag
				flags[i] |= WAD_FILE_UNCOMPRESSED;		// Flag as uncompressed
			}
			we.decompressedLength = fLen;
			we.compression = (flags[i] & WAD_FILE_RNCOMPRESSED) ? WAD_FILE_RNCOMPRESSED : WAD_FILE_UNCOMPRESSED;
			we.addr = fileRunner;
			fileRunner += we.fileLength;
			FWRITE(&we, sizeof(WadEntry), fout);
		}
		else
		{
			// We shall TRY and carry on
			we.fileLength = 0;
			we.decompressedLength = 0;
			we.compression = 0;
			we.addr = 0;
			Wad_ErrorFile("Wad Entry is empty\n");
			FWRITE(&we, sizeof(WadEntry), fout);
		}
	}

	if (ProgressUpdate) ProgressUpdate(0, 0, 0, "Pass 2/2");

	// Write now we can write out the files.
	for (i=0; i<numFiles; i++)
	{
		if (ProgressUpdate) ProgressUpdate((int)(100.0f * ((float) i / (float)numFiles)), 
											FALSE, wNames[i], 0);

		if ((flags[i] & WAD_FILE_IS_IN_WAD) && 
			(wadHandle != WAD_ERROR) && 
			(Wad_IsFileInWad(wNames[i], wadHandle) != WAD_ERROR))
		{
			// Try and get the file from the wad
			int fileNo = _Wad_FileOpen(wNames[i], wadHandle);
			int len = Wad_hLength(fileNo);
			if (len)
			{
				void *data = Wad_hData(fileNo);
				bool compress = false;

				if (flags[i] & WAD_FILE_RNCOMPRESSED)
				{
					void *packedData;
					unsigned int newlen;
					// Compress the data
					newlen = Wad_Compress(data, &packedData, len);
					if (newlen) 
					{
						data = packedData;
						len = newlen;
						compress = true;
					}
					else goto error;
				}

				FWRITE(data, len, fout);
				if (compress) free(data);		// Free the data if it is the compressed version
			}
			Wad_FileClose(fileNo);
			Wad_ErrorFile("Wrote %s from the wad\n", wNames[i]);
		}
		else
		{
			// Get the file from the file system
			FILE *fin;
			fin = fopen(fNames[i], "rb"); 
			if (fin)
			{
				int len;
				fseek(fin, 0, SEEK_END);
				len = ftell(fin);
				fseek(fin, 0, SEEK_SET);
				if (len)
				{
					void *buffer = malloc(len);
					if ((int)fread(buffer, 1, len, fin) != len) goto error;

					if (flags[i] & WAD_FILE_RNCOMPRESSED)
					{
						void *packedData;
						unsigned int newlen;
						// Compress the data
						newlen = Wad_Compress(buffer, &packedData, len);
						if (newlen)
						{
							free(buffer);
							buffer = packedData;
							len = newlen;
						}
						else goto error;
					}


					FWRITE(buffer, len, fout);
					free(buffer);
				}
				Wad_ErrorFile("Wrote %s from the file system\n", wNames[i]);
				fclose(fin);
			}
		}
	}

	fclose(fout);

	if (wadHandle != WAD_ERROR)
	{
		int ret;
		Wad_Close(wadHandle);
		ret = remove(wadName);
		ret = rename(tmpName, wadName);
	}

	Wad_ErrorFile("Finished writing wad data");
	Wad_ErrorFile(0);

	if (ProgressUpdate) ProgressUpdate(0, 0, 0, "Save Complete");

	return TRUE;

error:
	Wad_ErrorFile("Wad Save ended in an error\n");
	if (ProgressUpdate) ProgressUpdate(0, 0, 0, "Save error");
	fclose(fout);
	return FALSE;
}

////////////////////////////////////////////////////
// Wad information fucntions

Wad *Wad_Get(int wadNo)
{
	return &(wadGlobs.wads[wadNo]);
}

BOOL Wad_FileCompressed(int wadNo, int fileNo)
{
	return Wad_Get(wadNo)->wadEntries[fileNo].compression == WAD_FILE_UNCOMPRESSED ? FALSE : TRUE;
}

int Wad_FileLength(int wadNo, int fileNo)
{
	return Wad_Get(wadNo)->wadEntries[fileNo].decompressedLength;
}

int Wad_FileCompressedLength(int wadNo, int fileNo)
{
	return Wad_Get(wadNo)->wadEntries[fileNo].fileLength;
}

int Wad_FindFreeFileHandle()
{
	int i;
	for (i=0; i<MAX_OPEN_FILES; i++) if (!fileHandles[i].active) return i;
	return WAD_ERROR;
}

int _Wad_IsFileInWad(char *fName, int wadNo)
{
	int i;
	for (i=0; i<wadGlobs.wads[wadNo].numFiles; i++)
	{
		if (!_stricmp(wadGlobs.wads[wadNo].wadNames[i], fName)) return i;
	}
	return WAD_ERROR;
}

int Wad_IsFileInWad(char *fName, int wadNo) {
	if (wadNo == WAD_ERROR) {
		int i;
		for (i=MAX_WADS-1; i>=0; i--) {
			if (Wad_Get(i)->active) {
				int res = _Wad_IsFileInWad(fName, i);
				if (res != WAD_ERROR) return res;
			}
		}
		return WAD_ERROR;
	} else return _Wad_IsFileInWad(fName, wadNo);
}

int Wad_GetFreeWadSlot()
{
	int i;
	for (i=0; i<MAX_WADS; i++)
	{
		if (!WAD(i).active) 
		{
			// Zero out the slot
			memset(&WAD(i), 0, sizeof(Wad));
			return i;
		}
	}
	return WAD_ERROR;
}

/////////////////////////////////////////////////////
// Wad file operations.

int _Wad_FileOpen(char *fName, int wadNo)
{
	int indexOfFileInWad, fileHandle;
	void *ptr;

	// Search the file handles for a free one.
	if ((fileHandle = Wad_FindFreeFileHandle()) == WAD_ERROR) return WAD_ERROR;

	// Search the wad for the file and get its index
	if ((indexOfFileInWad = Wad_IsFileInWad(fName, wadNo)) == WAD_ERROR) return WAD_ERROR;

	// Allocate a block of memory for the file and read it from the disk
	ptr = malloc(Wad_FileCompressedLength(wadNo, indexOfFileInWad));
	if (!ptr)
	{
		return WAD_ERROR;
	}

	fseek(Wad_Get(wadNo)->fWad, Wad_Get(wadNo)->wadEntries[indexOfFileInWad].addr, SEEK_SET);
	if (fread(ptr, Wad_FileCompressedLength(wadNo, indexOfFileInWad), 1, Wad_Get(wadNo)->fWad) != 1)
	{
		free(ptr);
		return WAD_ERROR;
	}

	// If the file is compressed then it must be decompressed first
	if (Wad_Get(wadNo)->wadEntries[indexOfFileInWad].compression & WAD_FILE_RNCOMPRESSED)
	{
		void *newBuffer=0;
		RNC_Uncompress(ptr, &newBuffer);
		free(ptr);
		ptr = newBuffer;
	}

	// Fill out the file handle data
	fileHandles[fileHandle].data = ptr;
	fileHandles[fileHandle].active = TRUE;
	fileHandles[fileHandle].wadFile = wadNo;
	fileHandles[fileHandle].indexOfFileInWad = indexOfFileInWad;

	return fileHandle;
}

int Wad_FileOpen(char *fName, int wadNo) {
	if (wadNo == WAD_ERROR) {
		int i;
		// Look in all wads (backwards)
		for (i=MAX_WADS-1; i>=0; i--) {
			if(Wad_Get(i)->active) {
				int res = _Wad_FileOpen(fName, i);
				if (res != WAD_ERROR) {
					return res;
				}
			}
		}
		return WAD_ERROR;
	} else {
		return _Wad_FileOpen(fName, wadNo);
	}
}

void Wad_FileClose(int handle)
{
	if (fileHandles[handle].active)
	{
		free(fileHandles[handle].data);
		fileHandles[handle].active = FALSE;
	}
}

void *Wad_FileGetPointer(int handle)
{
	if (fileHandles[handle].active)
	{
		return fileHandles[handle].data;
	}
	return 0;
}

int Wad_hLength(int handle)
{
	return Wad_FileLength(fileHandles[handle].wadFile, fileHandles[handle].indexOfFileInWad);
}

void *Wad_hData(int handle)
{
	return Wad_FileGetPointer(handle);
}

