
// CARD.H - Memory card functions, Coded by Adrian Francis, March '99

#include <sys/file.h>
#include <libapi.h>

#define CARD_CONNECTED		0
#define CARD_ERROR			1
#define CARD_TIMEOUT		2
#define CARD_NEWCARD		3

#define CARD_FORMATTED		0
#define CARD_NOCARD			2
#define CARD_UNFORMATTED	3

#define CARD_MAXRETRIES		5

typedef struct {
	char	magic[2];
	char	type;
	char	slots;
	u_char	name[64];
	char	pad[28];
	char	clut[32];
	char	icon[3][128];
} Card_Header;

extern void Card_Init(void);
extern void	Card_ShutDown(void);
extern int	Card_Status(int);
extern int	Card_New(int);
extern int	Card_Format(int);
extern int	Card_Dir(int,struct DIRENTRY *);
extern int	Card_Load(int,char *,void *,int);
extern int	Card_Save(int,char *,void *,int);
extern void	Card_DebugTest(void *);