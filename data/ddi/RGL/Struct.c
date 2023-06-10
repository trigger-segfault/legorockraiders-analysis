
#include "Standard.h"
#include "Errors.h"
#include "Struct.h"
#include "Files.h"
#include "Mem.h"

#define STRUCT_MAX				10
#define STRUCT_MAXELEMENTS		100

struct StructGlobs {

	struct Struct structList[STRUCT_MAX];
	ULONG structCount;
	struct StructElement elementList[STRUCT_MAXELEMENTS];
	ULONG elementCount;

	struct Struct *currStruct;

} structGlobs = { 0 };

lpStruct Struct_RegisterType(ULONG size, LPVOID address) {

	lpStruct structure = NULL;

	if (size) {

		Error_Fatal(NULL != structGlobs.currStruct, "Already defining a structure type");

		if (structGlobs.structCount < STRUCT_MAX) {
			
			structure = &structGlobs.structList[structGlobs.structCount++];

			structure->size = size;
			structure->address = address;
			structure->elementList = &structGlobs.elementList[structGlobs.elementCount];

			structGlobs.currStruct = structure;
		}

	} else {

		ULONG loop, sub;
		lpStructElement loopElement, subElement;
		struct StructElement swapElement;

		structure = structGlobs.currStruct;
		structGlobs.currStruct = NULL;

		// Sort the list by offset order...

		for (loop=0 ; loop<structure->elementCount-1 ; loop++) {
			loopElement = &structure->elementList[loop];
			for (sub=loop+1 ; sub<structure->elementCount ; sub++) {
				subElement = &structure->elementList[sub];

				if (subElement->offset < loopElement->offset) {
					memcpy(&swapElement, loopElement, sizeof(swapElement));
					memcpy(loopElement, subElement, sizeof(*loopElement));
					memcpy(subElement, &swapElement, sizeof(*subElement));
				}
			}
		}

#ifdef _DEBUG
		for (loop=1 ; loop<structure->elementCount ; loop++) {

			loopElement = &structure->elementList[loop];
			subElement = &structure->elementList[loop-1];

			Error_Fatal(subElement->offset + subElement->size > loopElement->offset, "Structure element overlap");

			if (subElement->offset + subElement->size < loopElement->offset) {
			
				Error_Fatal(loopElement->offset - (subElement->offset + subElement->size) > 3, "Missing structure element: More than 3 padding bytes");
				Error_Fatal(0 == (subElement->size%4), "Missing structure element: No padding required");
			}
		}
		if (loopElement->offset + loopElement->size < structure->size) {
		
			Error_Fatal(structure->size - (loopElement->offset + loopElement->size) > 3, "Missing structure element: More than 3 padding bytes");
			Error_Fatal(0 == (loopElement->size%4), "Missing structure element: No padding required");
		}
#endif // _DEBUG

	}

	return structure;
}

VOID Struct_RegisterElement(lpStruct structure, LPUCHAR name, ULONG size, LPVOID address) {

	lpStructElement element;
	LPUCHAR s, t;

	Error_Fatal(structure != structGlobs.currStruct, "Incorrect structure");
	Error_Fatal(structGlobs.elementCount > STRUCT_MAXELEMENTS, "STRUCT_MAXELEMENTS too small");

	element = &structure->elementList[structure->elementCount];
	structure->elementCount++;
	structGlobs.elementCount++;

	for (t=s=&name[1] ; '\0'!=*s ; s++) {
		if ('>' == *s && '-' == *(s-1)) t = s+1;
	}

	sprintf(element->name, "%s", t);
	element->size = size;
	element->offset = (ULONG) ((LPUCHAR) address - (LPUCHAR) structure->address);

	Error_Fatal(element->offset + size > structure->size, "Element is outside the bounds of the structure");
}

LPVOID Struct_BuildHeaderBlock(lpStruct structure, LPULONG lpSize) {

	// Format:
	// (32)[file type id] (32)[template size] (32)[element count] (32)[structure size]
	// (n*32)[element name] (32)[offset] (32)[size]
	// (n*32)[element name] (32)[offset] (32)[size]
	// (n*32)[element name] (32)[offset] (32)[size]
	// ...

	ULONG size = (4 * sizeof(ULONG));
	lpStructElement element;
	LPULONG buffer, block;
	ULONG loop, length, count;

	for (loop=0 ; loop<structure->elementCount ; loop++) {
		
		element = &structure->elementList[loop];
		length = 1 + strlen(element->name);

		size += ((length + (sizeof(ULONG) - 1)) / sizeof(ULONG)) * sizeof(ULONG);
		size += sizeof(ULONG) + sizeof(ULONG);
	}

	buffer = Mem_AllocClear(size);
	buffer[0] = STRUCT_FILEID;
	buffer[2] = structure->elementCount;
	buffer[3] = structure->size;
	block = &buffer[4];

	for (loop=0 ; loop<structure->elementCount ; loop++) {
		
		element = &structure->elementList[loop];
		length = 1 + strlen(element->name);

		count = (length + (sizeof(ULONG) - 1)) / sizeof(ULONG);
		((LPUCHAR) block)[0] = (UCHAR) count;
		memcpy(&((LPUCHAR) block)[1], element->name, length);
		block += count;
		*(block++) = element->offset;
		*(block++) = element->size;
	}

	*lpSize = size;
	buffer[1] = size - (4 * sizeof(ULONG));

	return buffer;
}

static LPUCHAR Struct_ConvertStoredString(LPUCHAR address, LPULONG skip) {

	static UCHAR name[STRUCT_MAXELEMENTNAMELENGTH + sizeof(ULONG)];

	*skip = address[0];

	Error_Fatal(0 == *skip, "Invalid stored string");

	((LPULONG) name)[*skip - 1] = 0;
	memcpy(name, &address[1], (*skip * sizeof(ULONG)) - 1);

	return name;
}

static lpStruct Struct_ExtractHeaderBlock(LPULONG buffer, ULONG elementCount, ULONG size) {

	lpStruct structure = Mem_Alloc(sizeof(*structure));
	lpStructElement element;
	ULONG loop, skip;

	structure->address = NULL;
	structure->size = size;
	structure->elementCount = elementCount;
	structure->elementList = Mem_Alloc(sizeof(structure->elementList) * elementCount);
	
	for (loop=0 ; loop<elementCount ; loop++) {

		element = &structure->elementList[loop];

		sprintf(element->name, "%s", Struct_ConvertStoredString((LPUCHAR) buffer, &skip));
		buffer += skip;
		element->offset = *(buffer++);
		element->size = *(buffer++);
	}

	return structure;
}

static VOID Struct_FreeExtractedHeaderBlock(lpStruct structure) {

	Mem_Free(structure->elementList);
	Mem_Free(structure);
}

BOOL Struct_Write(lpStruct structure, LPUCHAR fname, LPVOID list, ULONG count) {

	lpFile fp;

	if (fp = File_Open(fname, "wb")) {

		ULONG size;
		LPVOID header = Struct_BuildHeaderBlock(structure, &size);

		File_Write(header, size, 1, fp);
		File_Write(list, structure->size, count, fp);

		Mem_Free(header);
		File_Close(fp);

		return TRUE;
	}

	return FALSE;
}

lpStructElement Struct_FindElement(lpStruct structure, LPUCHAR name) {

	ULONG loop;
	lpStructElement element;

	for (loop=0 ; loop<structure->elementCount ; loop++) {
		
		element = &structure->elementList[loop];

		if (0 == strcmp(element->name, name)) return element;
	}

	return NULL;
}

BOOL Struct_Remap(lpStruct srcStructure, lpStruct destStructure, LPVOID srcData, LPVOID destData) {

	ULONG loop;
	lpStructElement srcElement, destElement;

	Error_Warn(srcStructure->size != destStructure->size, "Size difference between source and destination structures");

	for (loop=0 ; loop<srcStructure->elementCount ; loop++) {

		srcElement = &srcStructure->elementList[loop];

		if (destElement = Struct_FindElement(destStructure, srcElement->name)) {
			if (destElement->size == srcElement->size) {

				memcpy(&((LPUCHAR) destData)[destElement->offset], &((LPUCHAR) srcData)[srcElement->offset], destElement->size);

				return TRUE;

			} else Error_Warn(TRUE, Error_Format("Size mismatch between source and destination for element '%s' %d>-%d", srcElement->name, srcElement->size, destElement->size));
		} else Error_Warn(TRUE, Error_Format("Missing element '%s' in destination structure", srcElement->name));
	}

	return FALSE;
}

LPVOID Struct_Read(lpStruct structure, LPUCHAR fname, ULONG start, LPULONG lpCount) {

	lpFile fp;
	lpStruct fileStructure;
	LPVOID buffer, newBuffer = NULL;
	ULONG header[4];
	ULONG loop, count, dataLength;

	if (fp = File_Open(fname, "rb")) {
	
		File_Read(header, sizeof(ULONG), 4, fp);
		if (STRUCT_FILEID == header[0]) {
			
			buffer = Mem_Alloc(header[1]);
			File_Read(buffer, header[1], 1, fp);

			fileStructure = Struct_ExtractHeaderBlock(buffer, header[2], header[3]);
			Mem_Free(buffer);
			buffer = NULL;

			dataLength = File_Length(fp);
			dataLength -= (4 * sizeof(ULONG));
			dataLength -= header[1];

			Error_Fatal(dataLength % fileStructure->size, "Truncated data file");

			if (*lpCount) count = *lpCount;
			else count = (dataLength / fileStructure->size) - start;

			Error_Fatal(count + start > (dataLength / fileStructure->size), "'lpCount' exceeds structure count in file");

			File_Seek(fp, start * fileStructure->size, FileSeekCur);

			buffer = Mem_Alloc(count * fileStructure->size);
			File_Read(buffer, fileStructure->size, count, fp);

			newBuffer = Mem_Alloc(count * structure->size);

			for (loop=start ; loop<count ; loop++) {
				Struct_Remap(fileStructure, structure, &((LPUCHAR) buffer)[loop * fileStructure->size], &((LPUCHAR) newBuffer)[loop * structure->size]);
			}

			Mem_Free(buffer);
			buffer = NULL;
		}

		File_Close(fp);
	}

	return newBuffer;
}
