
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#include "Standard.h"

#ifdef _NON_RGL
#define Error_Fatal(c,m)
#define Error_Warn(c,m)
#else // _NON_RGL
#include "Errors.h"
#endif // _NON_RGL

#include "Mem.h"
#include "Utils.h"

ULONG Util_RoundToPower(ULONG value) {

	ULONG loop, power;

	if (0 == value) return 0;

	for (loop=0 ; loop<sizeof(value)*8 ; loop++) {
		if ((value >> loop) & 0x01) power = loop;
	}

	return 0x01 << power;
}

LPUCHAR Util_StrIStr(LPUCHAR s, LPUCHAR sub) {

	ULONG len = strlen(sub);
	for ( ; '\0'!=*s ; s++) if (0 == strnicmp(s, sub, len)) return s;
	return NULL;
}

ULONG Util_Tokenise(LPUCHAR string, LPUCHAR *argv, ULONG argcMax, LPUCHAR sep, BOOL checkQuotes) {

	LPUCHAR s = string;
	ULONG count=0, sl;
	BOOL inQuotes = FALSE;

	if ('\0' == string[0]) return 0;

	if (sep) sl = strlen(sep);
	if (argv) argv[count] = string;
	count++;

	while ('\0' != *s){
		
		if (checkQuotes && '\"' == *s) {
			if (inQuotes) {
				*s = '\0';
				inQuotes = FALSE;
			} else {
				if (argv && count) argv[count-1]++;
				inQuotes = TRUE;
			}
			s++;
		} else if (!inQuotes && ((NULL == sep && isspace(*s)) || (sep && 0 == strncmp(sep, s, sl)))) {

			if (NULL == sep) for (sl=1 ; isspace(s[sl]) ; sl++) ;
			*s = '\0';
			s += sl;
			if (argv && count < argcMax) argv[count] = s;
			count++;

		} else s++;
	}

	return count;

}

__inline ULONG Util_WSTokenise(LPUCHAR string, LPUCHAR *argv, ULONG argc, BOOL checkQuotes) {

	return Util_Tokenise(string, argv, argc, NULL, checkQuotes);
}

/*
ULONG Util_WSTokenise(LPUCHAR string, LPUCHAR *argv){

	LPUCHAR s = string;
	ULONG count=0;

	if ('\0' == string[0]) return 0;

	argv[count++] = string;
	while ('\0' != *s){
		if (isspace(*s)) {
			*s++ = '\0';
			while (isspace(*s)) *s++;
			argv[count++] = s;
		} else s++;
	}

	return count;
}
*/

/*********************************************************************
 ****** Code for obtaining values from argument lists...
 *********************************************************************/

VOID Util_GetArguments_BOOL(ULONG argc, LPUCHAR *argv, ...) {

	va_list args;
	ULONG loop;
	LPBOOL value;
	LPUCHAR testStr;

	va_start(args, argv);

	while (testStr = va_arg(args, LPUCHAR)) {
		value = va_arg(args, LPBOOL);
		Error_Fatal(NULL==value, "NULL pointer passed as destination for result");

		for (loop=0 ; loop<argc ; loop++) {
			if ('-' == argv[loop][0]) {
				if (0 == stricmp(testStr, &argv[loop][1])) {
					if (loop+1 < argc) {
						if ('-' == argv[loop+1][0]) *value = TRUE;			// Parameter is another argument, assume true...
						else {
							if (0 == stricmp("TRUE", argv[loop+1])) *value = TRUE;
							else if (0 == stricmp("YES", argv[loop+1])) *value = TRUE;
							else if (0 == stricmp("ON", argv[loop+1])) *value = TRUE;
							else if (0 == stricmp("FALSE", argv[loop+1])) *value = FALSE;
							else if (0 == stricmp("NO", argv[loop+1])) *value = FALSE;
							else if (0 == stricmp("OFF", argv[loop+1])) *value = FALSE;
							else Error_Fatal(TRUE, Error_Format("Unknown parameter for %s - (%s)", argv[loop], argv[loop+1]));

							loop++;					// Skip the next argument as a valid parameter was given...
						}
					} else *value = TRUE;			// No parameter specified, assume truth...
				}
			}
		}
	}

	va_end(args);
}

VOID Util_GetArguments_ULONG(ULONG argc, LPUCHAR *argv, ...) {

	va_list args;
	ULONG loop;
	LPULONG value;
	LPUCHAR testStr;

	va_start(args, argv);

	while (testStr = va_arg(args, LPUCHAR)) {
		value = va_arg(args, LPULONG);
		Error_Fatal(NULL==value, "NULL pointer passed as destination for result");

		for (loop=0 ; loop<argc ; loop++) {
			if ('-' == argv[loop][0]) {
				if (0 == stricmp(testStr, &argv[loop][1])) {
					Error_Fatal(loop+1==argc || '-'==argv[loop+1][0], Error_Format("Parameter missing for %s", argv[loop]));
					*value = atoi(argv[loop+1]);
					loop++;
				}
			}
		}
	}

	va_end(args);
}

VOID Util_GetArguments_LPUCHAR(ULONG argc, LPUCHAR *argv, ...) {

	va_list args;
	ULONG loop;
	LPUCHAR *value;
	LPUCHAR testStr;

	va_start(args, argv);

	while (testStr = va_arg(args, LPUCHAR)) {

		value = va_arg(args, LPUCHAR *);
		Error_Fatal(NULL==value, "NULL pointer passed as destination for result");

		for (loop=0 ; loop<argc ; loop++) {
			if ('-' == argv[loop][0]) {
				if (0 == stricmp(testStr, &argv[loop][1])) {

					Error_Fatal(loop+1==argc || '-'==argv[loop+1][0], Error_Format("Parameter missing for %s", argv[loop]));

					*value = argv[loop + 1];
					loop++;
				}
			}
		}
	}

	va_end(args);
}

// function used in config.c
ULONG Util_GetBoolFromString(LPUCHAR string) {

	if (0 == stricmp(string, "TRUE"))	return 1;
	if (0 == stricmp(string, "FALSE"))	return 0;
	if (0 == stricmp(string, "YES"))	return 1;
	if (0 == stricmp(string, "NO"))		return 0;
	if (0 == stricmp(string, "ON"))		return 1;
	if (0 == stricmp(string, "OFF"))	return 0;
	if (0 == stricmp(string, "1"))		return 1;
	if (0 == stricmp(string, "0"))		return 0;

return 0;
}
