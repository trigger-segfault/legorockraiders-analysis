
#include "..\inc\Standard.h"

#include "..\inc\Errors.h"
#include "..\inc\Utils.h"
#include "..\inc\Config.h"
#include "..\inc\Activities.h"

ULONG Activity_Load(LPUCHAR filename, LPUCHAR gameID, LPUCHAR arglist, VOID (*ReadCallBack)(LPUCHAR itemname, LPUCHAR datastr, ULONG ival, REAL fval, LPVOID data), LPVOID data){

	ULONG count, loop;
	LPUCHAR argv[ACTIVITY_MAXARGS], result;
	UCHAR searchString[UTIL_DEFSTRINGLEN];
	ULONG calls=0;
	Config *conf;
	
	sprintf(searchString, "%s\\%s.ae", filename, filename);
	if (conf = Config_Load(searchString)){
		
		if (count = Util_Tokenise(arglist, argv, ACTIVITY_SEPARATOR)){
			for (loop=0 ; loop<count ; loop++){
				
				sprintf(searchString, "%s%s%s", gameID, CONFIG_SEPARATOR, argv[loop]);
				
				if (result = Config_GetStringValue(conf, searchString)){
					ReadCallBack(argv[loop], result, atoi(result), (REAL)atof(result), data);
					calls++;
				}

			}
		}
	} else Error_Fatal(TRUE, "Could not get Config");

	return calls;
}
