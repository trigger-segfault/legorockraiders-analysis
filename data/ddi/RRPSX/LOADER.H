//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Loader Header File For <LEGO Rock Raiders>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#ifndef	__LOADER_H

#define	LOADER_FLAG_ENABLED		0x00000001

typedef struct Loader_Globs {

	lpImage loadImage;
	lpFont font;
	int	count;
	ULONG flags;

} Loader_Globs, *lpLoader_Globs;

void	Loader_Initialise(LPUCHAR screen, lpFont font);
void Loader_Enable(BOOL enable);
void Loader_FileLoadCallback(LPUCHAR fname, ULONG size, LPVOID data);
void	Loader_Shutdown(void);

#ifdef DEBUG_CONSOLE
	CONSOLE_MESSAGE(x)		Loader_FileLoadCallback(x,0,NULL)
#else
	CONSOLE_MESSAGE(x)
#endif

#define	__LOADER_H
#endif
