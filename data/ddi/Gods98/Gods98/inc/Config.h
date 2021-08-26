
#ifndef _GODS98_CONFIG_H_
#define _GODS98_CONFIG_H_

#include "Standard.h"

#ifndef _RELEASE
#define CONFIG_DEVELOPMENTMODE
#endif // _RELEASE

//#define CONFIG_MAXCONFIG			100
#define CONFIG_MAXDEPTH				100
#define CONFIG_BINARYFILEID			"GBCF"

#ifdef CONFIG_DEVELOPMENTMODE
#define CONFIG_UNNAMEDSECTION		"Unspecified"
#define CONFIG_MAXUNKNOWNPHRASES	1000
#endif // CONFIG_DEVELOPMENTMODE

#define CONFIG_CONVERTIONINCPC		200

#define CONFIG_MAXLISTS				32			// 2^32 - 1 possible configs...

#define CONFIG_FLAG_INITIALISED		0x00000001
#define CONFIG_FLAG_LOADINGCONFIG	0x00000002

#define CONFIG_SEPARATOR			"::"

#ifdef DEBUG
	#define Config_CheckInit()			if (!(configGlobs.flags & CONFIG_FLAG_INITIALISED)) Error_Fatal(TRUE, "Error: Config_Intitialise() Has Not Been Called");
#else
	#define Config_CheckInit()
#endif


enum {
	Config_ReadStage_PreName = 0,
	Config_ReadStage_Name,
	Config_ReadStage_PreData,
	Config_ReadStage_Data,

	Config_ReadStage_End
};

typedef struct Config {

	LPUCHAR fileData;

	LPUCHAR itemName;
	LPUCHAR dataString;
	ULONG depth;
	ULONG itemHashCode;

	struct Config *linkNext;
	struct Config *linkPrev;

	struct Config *nextFree;

#ifdef _DEBUG
	BOOL accessed;
#endif // _DEBUG

} Config, *lpConfig;

typedef struct Config_LanguageData {

	LPUCHAR original, translation, section;

} Config_LanguageData, *lpConfig_LanguageData;

typedef struct Config_Globs {

//	Config configArray[CONFIG_MAXCONFIG];

	lpConfig listSet[CONFIG_MAXLISTS];
	lpConfig freeList;

	// Global data here...

	ULONG listCount;
	ULONG flags;

#ifdef CONFIG_DEVELOPMENTMODE
	LPUCHAR langFile;
	LPUCHAR languageBuffer;
	ULONG languageLines;
	struct Config_LanguageData *languageData;
	struct Config_LanguageData unknownPhrases[CONFIG_MAXUNKNOWNPHRASES];
	ULONG unknownPhraseCount;
	LPUCHAR ctFile, cconvFile;
	UCHAR characterTable[256];
#endif // CONFIG_DEVELOPMENTMODE

#ifndef _RELEASE
	struct Config *debugLastFind;
#endif // !_RELEASE

} Config_Globs;

/* Macros */

#ifdef _DEBUG
#define Config_GetStringValue(c,s)	Config_GetStringValueDebug((c),(s),__LINE__,__FILE__)
#else
LPUCHAR Config_GetStringValue(lpConfig root, LPUCHAR stringID);
#endif //_DEBUG

#define Config_GetIntValue(c,s)		atoi(Config_GetTempStringValue((c),(s))?Config_GetTempStringValue((c),(s)):"")
#define Config_GetRealValue(c,s)	(float)atof(Config_GetTempStringValue((c),(s))?Config_GetTempStringValue((c),(s)):"")
#define Config_Get3DCoord(c,s,v)	Config_GetCoord((c),(s),&((v)->x),&((v)->y),&((v)->z))
#define Config_Get2DCoord(c,s,x,y)	Config_GetCoord((c),(s),(x),(y),NULL)

/* Prototypes */

/*
#ifdef _DEBUG
extern unsigned char *__cdecl Config_GetStringValueDebug(struct Config *root,unsigned char *stringID,unsigned long line,unsigned char *file);
#else
extern unsigned char *__cdecl Config_GetStringValue(struct Config *root,unsigned char *stringID);
#endif //_DEBUG
extern void __cdecl Config_Initialise(void );
extern void __cdecl Config_Shutdown(void );
extern struct Config *__cdecl Config_Load(unsigned char *filename);
extern unsigned char *__cdecl Config_BuildStringID(unsigned char *s,...);
extern struct Config *__cdecl Config_FindLevel(struct Config *root,unsigned char *name);
extern struct Config *__cdecl Config_GetNextItem(struct Config *start);
extern unsigned char *__cdecl Config_GetTempStringValue(struct Config *root,unsigned char *stringID);
extern unsigned long __cdecl Config_GetBoolValue(struct Config *root,unsigned char *stringID);
extern int __cdecl Config_GetRGBValue(struct Config *root,unsigned char *stringID,float *r,float *g,float *b);
extern int __cdecl Config_GetCoord(struct Config *root,unsigned char *stringID,float *x,float *y,float *z);
extern void __cdecl Config_Free(struct Config *root);
static struct Config *__cdecl Config_Create(struct Config *prev);
static void __cdecl Config_Remove(struct Config *dead);
extern struct Config *__cdecl Config_FindItem(struct Config *conf,char *stringID);
extern void __cdecl Config_DumpStructure(struct Config *conf);
static void __cdecl Config_AddList(void );
static void __cdecl Config_RunThroughLists(void );
*/

#ifndef _GENPROTFILE
#include "..\Src\Config.prot"
#endif // _GENPROTFILE

#endif // _GODS98_CONFIG_H_
