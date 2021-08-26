#define MODE_NTSC 1
#define MODE_PAL	2

extern void 	ProfileInit(int scale);
extern void 	ProfileStartCount(void);
extern short 	ProfileStopCount(void);
extern void		ProfileAddOT(unsigned long * ot);
extern int 		ProfileDispMode(void);


extern short 	ProfileReadCount(void);
extern void		ProfileAddDrawOT(unsigned long * ot);
