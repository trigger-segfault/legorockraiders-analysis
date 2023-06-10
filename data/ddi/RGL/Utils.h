
#ifndef _RGL_UTILS_H_
#define _RGL_UTILS_H_

// Auto Prototypes
extern unsigned long __cdecl Util_RoundToPower(unsigned long value);
extern unsigned char *__cdecl Util_StrIStr(unsigned char *s,unsigned char *sub);
extern unsigned long __cdecl Util_Tokenise(unsigned char *string,unsigned char **argv ,unsigned long argcMax,unsigned char *sep,int checkQuotes);
extern unsigned long __cdecl Util_WSTokenise(unsigned char *string,unsigned char **argv ,unsigned long argc,int checkQuotes);
extern void __cdecl Util_GetArguments_BOOL(unsigned long argc,unsigned char **argv ,...);
extern void __cdecl Util_GetArguments_ULONG(unsigned long argc,unsigned char **argv ,...);
extern void __cdecl Util_GetArguments_LPUCHAR(unsigned long argc,unsigned char **argv ,...);
extern unsigned long __cdecl Util_GetBoolFromString(LPUCHAR string);
// Auto Prototypes

#endif // !_RGL_UTILS_H_
