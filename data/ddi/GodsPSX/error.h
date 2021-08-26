//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Error.h - Error Header File
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

#ifndef	_ERROR_H
#define	_ERROR_H

ext	Uint8	ErrorMessage[];

void		Error_Warn(BOOL flg, LPUCHAR msg);
void		Error_Debug(LPUCHAR msg);
void		Error_Fatal(BOOL flg, LPUCHAR msg);
Uint8*	Error_Format(LPUCHAR msg, ...);
void		Error_Show(BOOL flg, LPUCHAR msg);


#endif	//_ERROR_H
