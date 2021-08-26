//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Config.c - [Config Code]
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#define CONFIG_MAXDEPTH			100
#define CONFIG_MAXLISTS			32			// 2^32 - 1 possible configs...
#define CONFIG_FLAG_INITIALISED	0x00000001

#define CONFIG_SEPARATOR		"::"

#define	Util_Tokenize	Config_Tokenize

enum {
	Config_ReadStage_PreName = 0,
	Config_ReadStage_Name,
	Config_ReadStage_PreData,
	Config_ReadStage_Data,

	Config_ReadStage_End
};

typedef struct Config {

	LPUCHAR fileData;

	LPUCHAR	itemName;
	LPUCHAR	dataString;
	ULONG		depth;
	struct Config *linkNext;
	struct Config *linkPrev;

	struct Config *nextFree;

} Config, *lpConfig;

typedef struct Config_Globs {

	lpConfig	listSet[CONFIG_MAXLISTS];
	lpConfig	freeList;

	// Global data here...

	ULONG listCount;
	ULONG flags;

} Config_Globs;

ext	Uint8			_pctype[];

#define	_SPACE	1
#define	_NUMBR	2
#define	_ALPHA	4
#define	_UPPER	8
#define	_LOWER	16
#define	_PUNCT	32

#define	_UPALP		(_ALPHA | _UPPER)
#define	_LOALP		(_ALPHA | _LOWER)
#define	_ALPHANUM	(_ALPHA | _NUMBR)

#define	isspace(_c)		(_pctype[_c] & _SPACE)
#define	ispunct(_c)		(_pctype[_c] & _PUNCT)
#define	isalpha(_c)		(_pctype[_c] & _ALPHA)
#define	isalphanum(_c)	(_pctype[_c] & _ALPHANUM)
#define	isupper(_c)		(_pctype[_c] & _UPPER)
#define	islower(_c)		(_pctype[_c] & _LOWER)

void 		Config_Initialise(void);
lpConfig	Config_Load(LPUCHAR filename);
VOID			Config_AddList(VOID);
lpConfig	Config_Create(lpConfig prev);
LPUCHAR		Config_BuildStringID(LPUCHAR s, ...);
ULONG		Config_GetBoolValue(lpConfig root, LPUCHAR stringID);
LPUCHAR		Config_GetTempStringValue(lpConfig root, LPUCHAR stringID);
LPUCHAR		Config_GetStringValue(lpConfig root, LPUCHAR stringID);
lpConfig	Config_FindItem(lpConfig conf, char *stringID);
REAL			Config_GetAngle(lpConfig root, LPUCHAR stringID);
REAL			Config_GetRealValue(lpConfig root, LPUCHAR stringID);
ULONG		Config_Tokenize(LPUCHAR string, LPUCHAR *argv, LPUCHAR sep);
lpConfig	Config_FindArray(lpConfig root, LPUCHAR name);
lpConfig	Config_GetNextItem(lpConfig start);
VOID			Config_Free(lpConfig root);
VOID			Config_Remove(lpConfig dead);
Sint32		Config_GetIntValue(lpConfig root,LPUCHAR stringID);
void		Config_Release(void);
LPUCHAR		Config_GetVal(LPUCHAR vals,LPUCHAR str, ULONG index);
BOOL	stricmp(LPUCHAR src1, LPUCHAR src2);

// Playstation GPU Commands
//
// Command				Register			Data
//
// Screen On			1f801814			03000000
// Screen Off			1f801814			03000001
