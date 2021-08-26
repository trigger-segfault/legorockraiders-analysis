
#ifndef _GODS98_ACTIVITIES_H_
#define _GODS98_ACTIVITIES_H_

#define ACTIVITY_MAXARGS		100
#define ACTIVITY_SEPARATOR		"/"
#define ACTIVITY_FILESTRING		"FILE"
#define ACTIVITY_TRANSCOSTRING	"TRANSCOEF"
#define ACTIVITY_SAMPLESTRING	"SAMPLE"
#define ACTIVITY_TRIGGERSTRING	"TRIGGER"
#define ACTIVITY_ACTIVITYSTRING	"Activities"
#define ACTIVITY_FILESUFFIX		"ae"

extern ULONG __cdecl Activity_Load(unsigned char *filename,unsigned char *gameID,unsigned char *arglist,void (__cdecl *ReadCallBack)(unsigned char *,unsigned char *,unsigned long ,float ,void *),void *data);

#endif // _GODS98_ACTIVITIES_H_
