
#include "Standard.h"
#include "Errors.h"
#include "Mem.h"
#include "Files.h"
#include "Utils.h"

#ifdef _DEBUG
#include <windows.h>
#include "DirectX.h"
#include "Viewports.h"
#endif // _DEBUG

#include "Language.h"

struct LanguageGlobs {

	ULONG		stringCount;

	LPUCHAR		*stringList;
	LPUCHAR		*enumNameList;

	UCHAR		textBuffer[LANGUAGE_TEXTBUFFERSIZE];
	ULONG		textBufferUsed;

	BOOL		endRegistrationOK;

} languageGlobs = { 0 };


// ***************************************************************************************************************
VOID Language_BeginRegistration(ULONG stringCount)
{
	Error_Fatal( (stringCount == 0), "StringCount = 0");
	Error_Fatal( (languageGlobs.stringCount != 0), "languageGlobs.stringCount already initialised");

	languageGlobs.stringCount	= stringCount;
	languageGlobs.stringList	= Mem_Alloc(sizeof(languageGlobs.stringList[0])*languageGlobs.stringCount);
	languageGlobs.enumNameList	= Mem_Alloc(sizeof(languageGlobs.enumNameList[0])*languageGlobs.stringCount);
}

// ***************************************************************************************************************
VOID Language_RegisterEnum_Func(ULONG index, LPUCHAR languageString)
{
	Error_Fatal((index >= languageGlobs.stringCount), "language index out of range");
	languageGlobs.enumNameList[index]=languageString;
}

// ***************************************************************************************************************
VOID Language_EndRegistration(VOID)
{
ULONG l;

	//Error_Fatal( (languageGlobs.endRegistrationOK == TRUE), "Language_EndRegistartion Called more than once");
	Error_Fatal( (languageGlobs.stringCount == 0), "Language_BeginRegistartion hasn't been called");

	for (l = 0 ; l < languageGlobs.stringCount ; l++)
	{
		Error_Fatal(NULL==languageGlobs.enumNameList[l], Error_Format("Language Enumeration #%d is not registered", l));
	}

	languageGlobs.endRegistrationOK = TRUE;
}

// ***************************************************************************************************************
ULONG Language_FindEnum(LPUCHAR name) {

	ULONG loop;

	Error_Fatal( (languageGlobs.stringCount == 0), "Language_BeginRegistartion hasn't been called");

	for (loop=0 ; loop<languageGlobs.stringCount ; loop++) {
		if (0 == stricmp(name, languageGlobs.enumNameList[loop])) {
			return loop;
		}
	}

	return languageGlobs.stringCount;
}

// ***************************************************************************************************************
static VOID Language_ClearList(VOID) {

	ULONG loop;

	for (loop=0 ; loop<languageGlobs.stringCount ; loop++) languageGlobs.stringList[loop] = NULL;
	languageGlobs.textBufferUsed = 0;
}

// ***************************************************************************************************************
static VOID Language_SetString(enum LanguageString id, LPUCHAR string) {

	ULONG length = strlen(string) + 1;

	Error_Fatal(languageGlobs.textBufferUsed + length > LANGUAGE_TEXTBUFFERSIZE, "LANGUAGE_TEXTBUFFERSIZE too small");

	languageGlobs.stringList[id] = &languageGlobs.textBuffer[languageGlobs.textBufferUsed];
	languageGlobs.textBufferUsed += length;

	sprintf(languageGlobs.stringList[id], "%s", string);
}

// ***************************************************************************************************************
LPUCHAR Language_CheckLanguageFile(LPUCHAR fname, LPULONG languageID) {

	UCHAR line[LANGUAGE_MAXLINELENGTH];
	LPUCHAR argv[10];
	lpFile ifp;

	if (ifp = File_Open(fname, "r")) {
		if (File_GetLine(line, sizeof(line), ifp)) {
			if (2 == Util_Tokenise(line, argv, 999, "=", TRUE)) {
				if (strlen(argv[0]) >= 5) {
					strupr(argv[0]);
					if (((argv[0][0] >= '0' && argv[0][0] <= '9') || (argv[0][0] >= 'A' && argv[0][0] <= 'F')) &&
						((argv[0][1] >= '0' && argv[0][1] <= '9') || (argv[0][1] >= 'A' && argv[0][1] <= 'F')) &&
						((argv[0][2] >= '0' && argv[0][2] <= '9') || (argv[0][2] >= 'A' && argv[0][2] <= 'F')) &&
						((argv[0][3] >= '0' && argv[0][3] <= '9') || (argv[0][3] >= 'A' && argv[0][3] <= 'F')) &&
						argv[0][4] == '-') {

						File_Close(ifp);
						if (languageID) *languageID = atol(argv[0]);
						return Mem_CopyString(argv[1]);
					}
				}
			}
		}
		File_Close(ifp);
	}

	return NULL;
}

// ***************************************************************************************************************
VOID Language_Load(LPUCHAR textFile) {

	UCHAR line[LANGUAGE_MAXLINELENGTH];
	ULONG index;
	lpFile ifp;
	LPUCHAR s;
	LPUCHAR language;
	ULONG languageID;

#ifdef _DEBUG
#define LANGUAGE_DEBUG_MAXMISSING		1000
	LPUCHAR missing[LANGUAGE_DEBUG_MAXMISSING];
	ULONG missingCount = 0;
#endif // _DEBUG

	//Error_Fatal( (languageGlobs.endRegistrationOK == TRUE), "Language_EndRegistartion Called more than once");
	Error_Fatal( (languageGlobs.stringCount == 0), "Language_BeginRegistartion hasn't been called");

	language = Language_CheckLanguageFile(textFile, &languageID);

	if (ifp = File_Open(textFile, "r")) {

		Language_ClearList();

		if (language) File_GetLine(line, sizeof(line), ifp);

		while (File_GetLine(line, sizeof(line), ifp)) {

			for (s=line ; '\0'!=*s ; s++) {
				if ('=' == *s) {
					*s++ = '\0';
					break;
				}
			}

			if ('\0' != *s) {
				if (languageGlobs.stringCount != (index = Language_FindEnum(line))) {
					Language_SetString(index, s);
#ifdef _DEBUG
				} else {
					Error_Fatal(missingCount==LANGUAGE_DEBUG_MAXMISSING, "LANGUAGE_DEBUG_MAXMISSING too small");
					missing[missingCount++] = Mem_CopyString(line);
#endif // _DEBUG
				}
			}
		}

		File_Close(ifp);

#ifdef _DEBUG
		if (!DirectX_FullScreen() && missingCount) {
			ULONG loop;
			UCHAR msg[10240] = "Missing enumerations in code:\n";

			for (loop=0 ; loop<missingCount ; loop++) {
				strcat(msg, missing[loop]);
				strcat(msg, "\n");
			}

			MessageBox(NULL, msg, "Language", MB_OK);
		}
#endif // _DEBUG

	}

	Mem_Free(language);
}

// ***************************************************************************************************************
__inline LPUCHAR Language_GetEnumName(ULONG id) {

	Error_Fatal( (languageGlobs.stringCount == 0), "Language_BeginRegistartion hasn't been called");
	Error_Fatal( (languageGlobs.stringCount < id), "String index out of range");

	return languageGlobs.enumNameList[id];
}

// ***************************************************************************************************************
__inline LPUCHAR Language_GetString(ULONG id) {


	Error_Fatal( (languageGlobs.stringCount == 0), "Language_BeginRegistartion hasn't been called");
	Error_Fatal( (languageGlobs.stringCount < id), "String index out of range");


	if (languageGlobs.stringCount == id) return "!!!UNKNOWN ENUMERATION!!!";
	else if (languageGlobs.stringList[id]) return languageGlobs.stringList[id];
	else return "!!!TRANSLATION MISSING!!!";
}

// ***************************************************************************************************************
ULONG	Language_GetStringCount(void)
{
	return languageGlobs.stringCount;
}

// ***************************************************************************************************************
// ***************************************************************************************************************
// ***************************************************************************************************************
