
#ifndef _RGL_LANGUAGE_H
#define _RGL_LANGUAGE_H

#define LANGUAGE_TEXTBUFFERSIZE			4096	// Size of the buffer that will hold the entire text for a language.
#define LANGUAGE_MAXLINELENGTH			4096	// Maximum length of a line in the language file (including <enum>=).

#define Language_RegisterEnum(e)		Language_RegisterEnum_Func((e), #e)


#define LS(e)							Language_GetString(e)


/*****************************************************************************************************
 ***** Prototypes
 *****************************************************************************************************/

extern VOID				__cdecl Language_BeginRegistration(ULONG stringCount);
extern VOID				__cdecl Language_RegisterEnum_Func(ULONG index, LPUCHAR languageString);
extern VOID				__cdecl Language_EndRegistration(VOID);

extern VOID				__cdecl Language_Load(LPUCHAR textFile);
__inline extern LPUCHAR __cdecl Language_GetEnumName(ULONG id);
__inline extern LPUCHAR __cdecl Language_GetString(ULONG id);
extern ULONG			__cdecl Language_FindEnum(LPUCHAR name);
extern LPUCHAR			__cdecl Language_CheckLanguageFile(LPUCHAR fname, LPULONG languageID);
extern ULONG			__cdecl Language_GetStringCount(void);

#endif // LFPC_LANGUAGE_H
