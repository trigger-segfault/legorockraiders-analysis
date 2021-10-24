//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Config Handler For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

// Include all Header Files

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
#include	"..\inc\libgods.h"
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

Config_Globs configGlobs;

Uint8	_pctype[256] =
{
	// 0x00 - 0x0F
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, 
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE,

	// 0x10 - 0x1F
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, 
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE,

	// 0x20 - 0x2F
	_SPACE, _PUNCT, _PUNCT, _PUNCT, _PUNCT, _PUNCT, _PUNCT, _PUNCT, 
	_PUNCT, _PUNCT, _PUNCT, _PUNCT, _PUNCT, _PUNCT, _PUNCT, _PUNCT,

	// 0x30 - 0x3F
	_NUMBR, _NUMBR, _NUMBR, _NUMBR, _NUMBR, _NUMBR, _NUMBR, _NUMBR, 
	_NUMBR, _NUMBR, _PUNCT, _PUNCT, _PUNCT, _PUNCT, _PUNCT, _PUNCT,

	// 0x40 - 0x4F
	_PUNCT, _UPALP, _UPALP, _UPALP, _UPALP, _UPALP, _UPALP, _UPALP, 
	_UPALP, _UPALP, _UPALP, _UPALP, _UPALP, _UPALP, _UPALP, _UPALP,

	// 0x50 - 0x5F
	_UPALP, _UPALP, _UPALP, _UPALP, _UPALP, _UPALP, _UPALP, _UPALP, 
	_UPALP, _UPALP, _UPALP, _PUNCT, _PUNCT, _PUNCT, _PUNCT, _PUNCT,

	// 0x60 - 0x6F
	_PUNCT, _LOALP, _LOALP, _LOALP, _LOALP, _LOALP, _LOALP, _LOALP, 
	_LOALP, _LOALP, _LOALP, _LOALP, _LOALP, _LOALP, _LOALP, _LOALP,

	// 0x70 - 0x7F
	_LOALP, _LOALP, _LOALP, _LOALP, _LOALP, _LOALP, _LOALP, _LOALP, 
	_LOALP, _LOALP, _LOALP, _PUNCT, _PUNCT, _PUNCT, _PUNCT, _PUNCT,

	// 0x80 - 0x8F
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, 
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE,

	// 0x90 - 0x9F
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, 
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE,

	// 0xA0 - 0xAF
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, 
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE,

	// 0xB0 - 0xBF
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, 
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE,

	// 0xC0 - 0xCF
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, 
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE,

	// 0xD0 - 0xDF
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, 
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE,

	// 0xE0 - 0xEF
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, 
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE,

	// 0xF0 - 0xFF
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, 
	_SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE, _SPACE,
};

void Config_Initialise(void)
{
	Uint32	loop;

	for(loop=0; loop<CONFIG_MAXLISTS; loop++)
		{
		configGlobs.listSet[loop]=NULL;
		}

	configGlobs.freeList = NULL;
	configGlobs.listCount = NULL;
	configGlobs.flags = CONFIG_FLAG_INITIALISED;
}


lpConfig	Config_Load(LPUCHAR filename)
{
	lpConfig	conf, rootConf = NULL;
	ULONG		fileSize, loop, i;
	LPUCHAR	s, fdata;
	UCHAR		c;
	BOOL		commentMode = FALSE;

	if (fdata = File_LoadBinary(filename, &fileSize))
		{
		conf = rootConf = Config_Create(NULL);
		rootConf->fileData = fdata;

		// Change any return/tab/blah/blah characters to zero...
		// Clear anything after a semi-colon until the next return character.
		for (s=rootConf->fileData,loop=0; loop<fileSize; loop++)
			{
			if (';' == *s) commentMode = TRUE;
			else if ('\n' == *s) commentMode = FALSE;

			if (commentMode) *s = '\0';
			else if (isspace(*s)) *s = '\0';
			s++;
			}

		// Run through the file data and point in the config structures
		for (s=rootConf->fileData,loop=0; loop<fileSize; loop++)
			{
			if ('\0' != *s)
				{
				if ('}' == *s) conf->depth--;
				else if (NULL == conf->itemName)
					{
					for(i=0; i<strlen(s); i++)
						{
						if(isupper(s[i])) s[i]+=32;
						}
					conf->itemName = s;
					}
				else
					{
					conf->dataString = s;
					conf = Config_Create(conf);
					if ('{' == *s) conf->depth++;
					}
				for (; loop<fileSize; loop++) if ('\0' == *(s++)) break;
				} else s++;
			}
		}
	return rootConf;
}

VOID Config_AddList(VOID)
{
	lpConfig list;
	ULONG loop, count;

	count = 0x00000001 << configGlobs.listCount;

	if (list = configGlobs.listSet[configGlobs.listCount] = 
		(lpConfig)Mem_Alloc(sizeof(Config) * count))
		{
		configGlobs.listCount++;

		for (loop=1 ; loop<count ; loop++)
			{
			list[loop-1].nextFree = &list[loop];
			}
		list[count-1].nextFree = configGlobs.freeList;
		configGlobs.freeList = list;

		}
	// Error Not Enough Memory For Config
}

lpConfig	Config_Create(lpConfig prev)
{
	lpConfig	newConfig;

	if (NULL == configGlobs.freeList) Config_AddList();
	
	newConfig = configGlobs.freeList;
	configGlobs.freeList = newConfig->nextFree;
	newConfig->nextFree = newConfig;

	newConfig->itemName = NULL;
	newConfig->dataString = NULL;
	newConfig->linkNext = NULL;
	
	if (prev)
		{
		prev->linkNext = newConfig;
		newConfig->linkPrev = prev;
		newConfig->depth = prev->depth;
		newConfig->fileData = prev->fileData;
		} else {
		newConfig->depth = 0;
		newConfig->linkPrev = NULL;
		}

	return newConfig;
}

LPUCHAR Config_BuildStringID(LPUCHAR s, ...)
{
	va_list	args;
	Uint32	i;
	static	UCHAR string[1024];
	LPUCHAR	curr;

	strcpy(string, s);

	va_start(args, s);
	while (curr = va_arg(args, LPUCHAR))
		{
		strcat(string, CONFIG_SEPARATOR);
		strcat(string, curr);
		}
	va_end(s);

	for(i=0; i<strlen(string); i++) if(isupper(string[i])) string[i]+=32;

	return string;
}

ULONG Config_GetBoolValue(lpConfig root, LPUCHAR stringID)
{

	LPUCHAR string;
	ULONG res = 2;

	if (string = Config_GetStringValue(root, stringID))
	{
		if (!stricmp(string, "YES"))
			res = 1;
		else if (!stricmp(string, "TRUE"))
			res = 1;
		else if (!stricmp(string, "ON"))
			res = 1;
		else if (!stricmp(string, "NO"))
			res = 0;
		else if (!stricmp(string, "FALSE"))
			res = 0;
		else if (!stricmp(string, "OFF"))
			res = 0;
		Mem_Free(string);
	}
	return res;
}

LPUCHAR Config_GetTempStringValue(lpConfig root, LPUCHAR stringID)
{
	lpConfig conf;

	if (conf = Config_FindItem(root, stringID))
	{
		return conf->dataString;
	}
	return NULL;
}

LPUCHAR Config_GetStringValue(lpConfig root, LPUCHAR stringID)
{
	lpConfig	conf;
	LPUCHAR	str;

	if (conf = Config_FindItem(root, stringID))
	{
		if (conf->dataString)
		{
			str = (LPUCHAR)Mem_Alloc(strlen(conf->dataString) + 1);
			strcpy(str, conf->dataString);
			return str;
		}
	}
	return NULL;
}

lpConfig Config_FindItem(lpConfig conf, char *stringID)
{
	// Search the list for the given item.
	
	LPUCHAR		argv[CONFIG_MAXDEPTH];
	ULONG			count, currDepth, i;
	lpConfig 	backConf, foundConf = NULL;
	LPUCHAR		tempstring = (LPUCHAR)Mem_Alloc(strlen(stringID)+1);

	strcpy(tempstring, stringID);

	count = Config_Tokenize(tempstring, argv, "::");

	// First find anything that matches the depth of the request
	// then see if the hierarchy matches the request.

	while(conf)
	{
		if (conf->depth == count - 1)
		{
			if (0 == stricmp(argv[count - 1], conf->itemName))
			{
				// Look backwards down the list to check the hierarchy.
				currDepth = count - 1;
				backConf = conf;
				while(backConf)
				{
					if (backConf->depth == currDepth - 1)
					{
						if (0 == stricmp(argv[currDepth - 1], backConf->itemName))
						{
							currDepth--;
						}
						else
							break;
					}
					backConf = backConf->linkPrev;
				}

				if (0 == currDepth)
				{
					foundConf = conf;
					break;
				}
			}
		}
		conf = conf->linkNext;
	}
	Mem_Free(tempstring);
	return foundConf;
}

REAL Config_GetAngle(lpConfig root, LPUCHAR stringID)
{
	REAL degrees;

	if (degrees = Config_GetRealValue(root, stringID))
	{
		return (Asm_MulFIX(degrees,M_PI2) / 360);
	}
	return 0;
}

REAL	Config_GetRealValue(lpConfig root, LPUCHAR stringID)
{
	LPUCHAR	s;
	Uint8		c;
	Uint32	loop;
	Sint32	p=-1;
	REAL		retval=NULL;
	
	s = Config_GetTempStringValue(root, stringID);

	while(c=*(s++))
	{
		if(c=='.')
		{
			p++;
		}
		else
		{
			retval *= 10;
			if((c>='0') && (c<='9'))
			{
				retval+=(c-'0');
				if(p>=0)
					p++;
			}
		}
	}
	loop=1;

	while(p>0)
	{
		loop*=10;
		p--;
	}

	return (retval*ONE)/loop;
}

ULONG Config_Tokenize(LPUCHAR string, LPUCHAR *argv, LPUCHAR sep)
{
	LPUCHAR	s = string;
	ULONG		count=0;

	if (!*s) return 0;

	argv[count++] = string;
	while (*s)
	{
		if (!strncmp(sep, s, strlen(sep)))
		{
			*s = '\0';
			argv[count++] = s+strlen(sep);
		}
		s++;
	}
	return count;
}

lpConfig Config_FindArray(lpConfig root, LPUCHAR name)
{
	lpConfig conf;

	if (conf = Config_FindItem(root, name))
	{
		if (conf->depth < conf->linkNext->depth)
			return conf->linkNext;
	}
	return NULL;
}

lpConfig Config_GetNextItem(lpConfig start)
{
	ULONG		level = start->depth;
	lpConfig	conf = start;

	while(conf)
	{
		if (conf->depth < level)
			return NULL;
		conf = conf->linkNext;
		if (conf->depth == level)
			return conf;
	}
	return NULL;
}

VOID Config_Free(lpConfig root)
{
	lpConfig next;

	Mem_Free(root->fileData);
	while(root)
	{
		next = root->linkNext;
		Config_Remove(root);
		root = next;
	}
}

VOID Config_Remove(lpConfig dead)
{
	if(!dead)
		return;
	dead->nextFree = configGlobs.freeList;
	configGlobs.freeList = dead;
}
 
Sint32	Config_GetIntValue(lpConfig root,LPUCHAR stringID)
{
	Sint32	retval = NULL;

	retval = atoi(Config_GetTempStringValue(root, stringID));

	return retval;
}
 
BOOL	stricmp(LPUCHAR src1, LPUCHAR src2)
{
	Uint16	l;
	Uint8		c1, c2;

	if(strlen(src1) != strlen(src2))
		return TRUE;

	for(l=0; l<strlen(src1); l++)
	{
		if (isalpha(c1 = src1[l]))
			c1 |= ' ';
		if (isalpha(c2 = src2[l]))
			c2 |= ' ';
		if (c1 != c2)
			return TRUE;
	}

	return FALSE;
}

