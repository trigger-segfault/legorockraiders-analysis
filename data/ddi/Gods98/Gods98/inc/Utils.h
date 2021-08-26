
#ifndef _GODS98_UTILS_H_
#define _GODS98_UTILS_H_

#define UTIL_DEFSTRINGLEN		512
#define UTIL_LARGENUMBER		6293815		// For Util_HashString()
#define UTIL_MAXSTRINGLENGTH	256

typedef LPUCHAR Util_StringMatrix[4][4];

/* Prototypes */

LPUCHAR Util_GetLine(LPUCHAR *buffer, LPUCHAR bufferEnd);
unsigned long __cdecl Util_Tokenise(unsigned char *string,unsigned char **argv ,unsigned char *sep);
unsigned long __cdecl Util_WSTokenise(unsigned char *string,unsigned char **argv);
LPUCHAR Util_StrIStr(const LPUCHAR str1, LPUCHAR str2);
ULONG Util_HashString(LPUCHAR string, BOOL bIgnoreBlanks, BOOL upperCase);
BOOL Util_IsNumber(LPUCHAR string);
ULONG Util_GetBoolFromString(LPUCHAR string);
VOID Util_MultiplyStringMatrix(Util_StringMatrix r, Util_StringMatrix a, Util_StringMatrix b);
VOID Util_PrintStringMatrix(Util_StringMatrix r);
VOID Util_TransposeStringMatrix(Util_StringMatrix m);
VOID Util_FreeStringMatrix(Util_StringMatrix m);

LPUCHAR Util_RemoveUnderscores( LPUCHAR string, ... );


#ifdef _DEBUG
LPUCHAR Util_StrCpyDebug(LPUCHAR string, LPUCHAR file, ULONG line);
#define Util_StrCpy(s)		Util_StrCpyDebug((s),__FILE__,__LINE__)
#else
LPUCHAR Util_StrCpy(LPUCHAR string);
#endif // _DEBUG

#endif // _GODS98_UTILS_H_
