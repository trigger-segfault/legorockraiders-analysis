
#include "..\inc\Standard.h"
#include "..\inc\Memory.h"
#include "..\inc\Errors.h"

#include "..\inc\Utils.h"

ULONG Util_Tokenise(LPUCHAR string, LPUCHAR *argv, LPUCHAR sep){

	LPUCHAR s = string;
	ULONG count=0, sl = strlen(sep);

	if ('\0' == string[0]) return 0;

	argv[count++] = string;
	while ('\0' != *s){
		if (0 == strncmp(sep, s, sl)) {
			*s = '\0';
			argv[count++] = s + sl;
		}
		s++;
	}

	return count;

}

LPUCHAR Util_GetLine(LPUCHAR *buffer, LPUCHAR bufferEnd) {

	BOOL foundEnd = FALSE;
	LPUCHAR s, line = *buffer;

	for (s=*buffer ; s!=bufferEnd ; s++) {
		if ('\r' == *s || '\n' == *s) {
			*s = '\0';
			foundEnd = TRUE;
		} else {
			if (foundEnd) break;
		}
	}
	
	if (!foundEnd) return NULL;

	*buffer = s;
	return line;
}

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

#ifdef _DEBUG
LPUCHAR Util_StrCpyDebug(LPUCHAR string, LPUCHAR file, ULONG line) {

	LPUCHAR newString = Mem_AllocDebug(strlen(string)+1, line, file);
	strcpy(newString, string);
	return newString;
}
#else // _DEBUG
LPUCHAR Util_StrCpy(LPUCHAR string) {

	LPUCHAR newString = Mem_Alloc(strlen(string)+1);
	strcpy(newString, string);
	return newString;
}
#endif // _DEBUG

LPUCHAR Util_RemoveUnderscores( LPUCHAR string, ... )
{
	LPUCHAR s, t;
	UCHAR completeString[UTIL_MAXSTRINGLENGTH], buffer[UTIL_MAXSTRINGLENGTH];
	ULONG len;
	va_list args;
	LPUCHAR result;


	va_start( args, string );
	len = vsprintf( completeString, string, args );
	Error_Fatal( len > UTIL_MAXSTRINGLENGTH, Error_Format("String too big for 'Util_RemoveUnderscores'.", string) );
	va_end( args );

	t = buffer;
	for( s = completeString; '\0' != *s; s++ )
	{
		if( ('\\' == *s) && ('n' == *( s + 1 )) )
		{
			*t = '\n';
			s++;
		} else if( '_' == *s )
			*t = ' ';
		else
			*t = *s;
		
		t++;
	}
	*t = '\0';

	result = Util_StrCpy( buffer );

	return result;
}


LPUCHAR Util_StrIStr(const LPUCHAR str1, LPUCHAR str2){

	unsigned int len1,len2;
	unsigned int i;
	char *str;

	len1=strlen(str1);
	len2=strlen(str2);

	if(!len1 || !len2)
		return NULL;

	for(i=0;i<len1;i++)
	{
		str=str1+i;
		if(!strnicmp(str,str2,len2))
		{
//			str+=len2;
			return str;
		}
	}

	return NULL;
}

ULONG Util_HashString(LPUCHAR string, BOOL bIgnoreBlanks, BOOL upperCase) {

	ULONG sum = 0;
	ULONG multiple = UTIL_LARGENUMBER;
	ULONG index = 1;
	UCHAR c;

	while (*string != '\0') {
		if (bIgnoreBlanks) while (isspace(*string)) string++;
		c = (*string++);
		if (upperCase) c = toupper(c);
		sum += multiple * index++ * c;
		multiple *= UTIL_LARGENUMBER;
	}
	return(sum);
}

BOOL Util_IsNumber(LPUCHAR string){

	while('\0' != *string) {
		if (!isdigit(*string) && '.' != *string) return FALSE;
	}

	return TRUE;
}

ULONG Util_GetBoolFromString(LPUCHAR string) {

	if (0 == stricmp(string, "YES")) return TRUE;
	else if (0 == stricmp(string, "TRUE")) return TRUE;
	else if (0 == stricmp(string, "ON")) return TRUE;
	else if (0 == stricmp(string, "NO")) return FALSE;
	else if (0 == stricmp(string, "FALSE")) return FALSE;
	else if (0 == stricmp(string, "OFF")) return FALSE;

	return 2;		// Unknown...
}

VOID Util_MultiplyStringMatrix(Util_StringMatrix r, Util_StringMatrix a, Util_StringMatrix b) {
	
	ULONG i, j, k;
	UCHAR string[1024];
//	BOOL a1, b1;
		
	for (i=0; i<4; i++) {
		for (j=0; j<4; j++) {
			for (k=0; k<4; k++) {
				if (NULL != a[i][k] && NULL != b[k][j]) {
//					a1 = (0 == strcmp("1.0f", a[i][k]));
//					b1 = (0 == strcmp("1.0f", b[k][j]));
					string[0] = '\0';
//					if (a1 && b1) strcat(string, "1.0f");
//					else {
//						if (!a1 && !b1)
					strcat(string, "(");
//						if (!a1)
					strcat(string, a[i][k]);
//						if (!a1 && !b1)
					strcat(string, " * ");
//						if (!b1)
					strcat(string, b[k][j]);
//						if (!a1 && !b1)
					strcat(string, ")");
//					}
					if (NULL == r[i][j]) {
						r[i][j] = Mem_Alloc(strlen(string) + 1);
						strcpy(r[i][j], string);
					} else {
						r[i][j] = Mem_ReAlloc(r[i][j], strlen(r[i][j]) + strlen(string) + 4);
						strcat(r[i][j], " + ");
						strcat(r[i][j], string);
					}
				}
			}
		}
	}
}

VOID Util_PrintStringMatrix(Util_StringMatrix r) {
	
	ULONG i, j;
		
	for (i=0; i<4; i++) {
		for (j=0; j<4; j++) {
			Error_Debug(Error_Format("m[%i][%i] = ", i, j));
			if (NULL != r[i][j]) {
				if ('\0' == r[i][j][0]) Error_Debug("1.0f");
				else Error_Debug(Error_Format("%s", r[i][j]));
			} else Error_Debug("0.0f");
			Error_Debug(";\n");
		}
	}
}

VOID Util_TransposeStringMatrix(Util_StringMatrix m) {

	ULONG i, j;
	LPUCHAR swap;

	for (i=0 ; i<4 ; i++){
		for (j=0 ; j<4 ; j++){
			swap = m[i][j];
			m[i][j] = m[j][i];
			m[j][i] = swap;
		}
	}
}

VOID Util_FreeStringMatrix(Util_StringMatrix m) {

	ULONG i, j;

	for (i=0 ; i<4 ; i++){
		for (j=0 ; j<4 ; j++){
			if (NULL != m[i][j]) Mem_Free(m[i][j]);
		}
	}
}