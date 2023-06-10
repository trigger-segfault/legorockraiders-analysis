
#ifndef _RGL_CONFIG_H_
#define _RGL_CONFIG_H_

#include "Standard.h"


//#define CONFIG_MAXCONFIG			100
#define CONFIG_MAXDEPTH				100
#define CONFIG_BINARYFILEID			"GBCF"

#ifdef CONFIG_DEVELOPMENTMODE
#define CONFIG_UNNAMEDSECTION		"Unspecified"
#define CONFIG_MAXUNKNOWNPHRASES	1000
#endif // CONFIG_DEVELOPMENTMODE

#define CONFIG_CONVERTIONINCPC		200

//#define CONFIG_MAXLISTS				32			// 2^32 - 1 possible configs...
#define CONFIG_MAXSTRINGIDLENGTH	1024

#define CONFIG_FLAG_INITIALISED		0x00000001
#define CONFIG_FLAG_LOADINGCONFIG	0x00000002

#define CONFIG_SEPARATOR			"::"

#ifdef DEBUG
	#define Config_CheckInit()			if (!(configGlobs.flags & CONFIG_FLAG_INITIALISED)) Error_Fatal(TRUE, "Error: Config_Intitialise() Has Not Been Called");
#else
	#define Config_CheckInit()
#endif

#ifdef _DEBUG
	#define Config_CheckItem(i)			Config_Debug_CheckFileData(i);
#else
	#define Config_CheckItem(i)
#endif // _DEBUG


enum {
	Config_ReadStage_PreName = 0,
	Config_ReadStage_Name,
	Config_ReadStage_PreData,
	Config_ReadStage_Data,

	Config_ReadStage_End
};

struct ConfigSet {

	struct Config *rootConfig;
	LPUCHAR fileData;
	UCHAR rootScope[CONFIG_MAXSTRINGIDLENGTH];
	UCHAR currScope[CONFIG_MAXSTRINGIDLENGTH];

#ifdef _DEBUG
	LPUCHAR fileDataCopy;
	ULONG fileDataCopySize;
#endif // _DEBUG
};

struct Config {

	LPUCHAR itemName;
	LPUCHAR dataString;
	ULONG depth;
	ULONG itemHashCode;

	struct Config *linkNext;
	struct Config *linkPrev;

//	struct Config *nextFree;

#ifdef _DEBUG
	BOOL accessed;
#endif // _DEBUG

};

typedef struct Config_LanguageData {

	LPUCHAR original, translation, section;

} Config_LanguageData, *lpConfig_LanguageData;


typedef struct ConfigSet		*lpConfigSet;

/* Macros */

#ifdef _DEBUG
#define Config_GetStringCopy(c,s)			Config_GetStringCopyDebug((c),(s),__LINE__,__FILE__)
#else
LPUCHAR Config_GetStringCopy(struct Config *root, LPUCHAR stringID);
#endif //_DEBUG

#define Config_GetIntValue(c,s)				atoi(Config_GetString((c),(s))?Config_GetString((c),(s)):"")
#define Config_GetRealValue(c,s)			(float)atof(Config_GetString((c),(s))?Config_GetString((c),(s)):"")
#define Config_Get3DCoord(c,s,v)			Config_GetCoord((c),(s),&((v)->x),&((v)->y),&((v)->z))
#define Config_Get2DCoord(c,s,x,y)			Config_GetCoord((c),(s),(x),(y),NULL)

// Backwards compatibility
#define Config_GetStringValue(c,s)			Config_GetStringCopy((c),(s));
#define Config_GetTempStringValue(c,s)		Config_GetString((c),(s));

typedef struct Config						*lpConfig;

/* Prototypes */



extern void __cdecl Config_Initialise(void );
extern void __cdecl Config_Shutdown(void );
extern void Config_SetCharacterTable(unsigned char *fname);
extern void Config_SetCharacterConvertFile(unsigned char *fname);
static void Config_ReadCharacterTable(unsigned char *fname);
extern unsigned char __cdecl Config_ConvertCharacter(unsigned char c);
extern void __cdecl Config_SetLanguageDatabase(unsigned char *langFile);
static void __cdecl Config_ReadLanguageDatabase(unsigned char *langFile);
extern unsigned char *__cdecl Config_ConvertString(unsigned char *s,unsigned char *sectionName,unsigned long *size,int spaceToUnderscore);
extern void __cdecl Config_DumpUnknownPhrases(unsigned char *fname);
extern void *__cdecl Config_LoadConvertedText(unsigned char *fname,unsigned long *fileSize);
extern struct Config *__cdecl Config_Load(unsigned char *filename);
extern unsigned char *__cdecl Config_BuildStringID(unsigned char *s,...);
extern struct Config *__cdecl Config_FindArray(struct Config *root,unsigned char *name);
extern struct Config *__cdecl Config_GetNextItem(struct Config *start);
extern unsigned char *__cdecl Config_GetString(struct Config *root,unsigned char *stringID);
extern unsigned char *__cdecl Config_GetLanguageString(struct Config *root,unsigned char *stringID);
extern unsigned long __cdecl Config_GetBoolValue(struct Config *root,unsigned char *stringID);
extern float __cdecl Config_GetAngle(struct Config *root,unsigned char *stringID);
extern int __cdecl Config_GetRGBValue(struct Config *root,unsigned char *stringID,float *r,float *g,float *b);
extern int __cdecl Config_GetCoord(struct Config *root,unsigned char *stringID,float *x,float *y,float *z);
extern int __cdecl Config_GetKey(struct Config *root,unsigned char *stringID,unsigned char *key);
extern void __cdecl Config_Free(struct Config *root);
extern unsigned char *__cdecl Config_Debug_GetLastFind(void );
static struct Config *__cdecl Config_Create(struct Config *prev);
static void __cdecl Config_Remove(struct Config *dead);
extern struct Config *__cdecl Config_FindItem(struct Config *conf,char *stringID);
extern void __cdecl Config_DumpStructure(struct Config *conf);
static void __cdecl Config_AddList(void );
static void __cdecl Config_RunThroughLists(void );
extern LPUCHAR __cdecl Config_GetItemName(lpConfig conf);
extern LPUCHAR __cdecl Config_GetDataString(lpConfig conf);
extern LPUCHAR __cdecl Config_GetDataStringCopy(lpConfig conf);
extern LPUCHAR __cdecl Config_GetRootScope(lpConfig config);
extern VOID __cdecl Config_SetRootScope(lpConfig config, LPUCHAR scope);
extern LPUCHAR __cdecl Config_GetScope(lpConfig config);
extern VOID __cdecl Config_SetScope(lpConfig config, LPUCHAR scope);
extern LPUCHAR __cdecl Config_GetStringCopyDebug(struct Config *root, LPUCHAR stringID, ULONG line, LPUCHAR file);








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

extern VOID __cdecl Config_SetStringValue(struct Config *root, LPUCHAR stringID, LPUCHAR string);
extern VOID __cdecl Config_Save(lpConfig config, LPUCHAR fname);

#ifndef _GENPROTFILE
//#include "..\Src\Config.prot"
#endif // _GENPROTFILE

#endif // _RGL_CONFIG_H_
