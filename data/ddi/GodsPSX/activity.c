//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Activity File For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

// Include all Header Files

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
#include	"libgods.h"
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹


ULONG Activity_Load(LPUCHAR filename, LPUCHAR gameID, LPUCHAR arglist, VOID (*ReadCallBack)(LPUCHAR itemname, LPUCHAR datastr, ULONG ival, REAL fval, LPVOID data), LPVOID data)
{
	ULONG count, loop;
	LPUCHAR argv[ACTIVITY_MAXARGS], result;
	UCHAR searchString[UTIL_DEFSTRINGLEN];
	ULONG calls=0;
	Config *conf;
	
	sprintf(searchString, "%s\\%s.ae", filename, filename);
	if (conf = Config_Load(searchString))
		{
		if (count = Util_Tokenize(arglist, argv, ACTIVITY_SEPARATOR))
			{
			for (loop=0 ; loop<count ; loop++)
				{
				sprintf(searchString, "%s%s%s", gameID, CONFIG_SEPARATOR, argv[loop]);
				if (result = Config_GetStringValue(conf, searchString))
					{
					ReadCallBack(argv[loop], result, atoi(result), (REAL)atof(result), data);
					calls++;
					}
				}
			}
		}
	else
		{
		// Error Could not get Config
		}

	return calls;
}
