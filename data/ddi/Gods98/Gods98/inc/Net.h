
#define NET_MAXNAMELENGTH				128
#define NET_MAXCONNECTIONS				10
#define NET_MAXSESSIONS					10
#define NET_MAXPLAYERS					10

#define NET_FLAG_SERVER					0x00000001

#define NETPLAYER_FLAG_USED				0x00000001
#define NETPLAYER_FLAG_SERVER			0x00000002

#ifdef _GODS98COMPILE

struct NetConnection {

	UCHAR name[NET_MAXNAMELENGTH];
	LPVOID connectionBuffer;
};

struct NetSession {

	GUID guid;
	UCHAR name[NET_MAXNAMELENGTH];
};

struct NetPlayer {

	DPID id;
	LPVOID data;
	UCHAR name[NET_MAXNAMELENGTH];
	ULONG flags;
};

#endif // _GODS98COMPILE

typedef struct NetPlayer			*lpNetPlayer;
typedef struct NetSession			*lpNetSession;
typedef struct NetConnection		*lpNetConnection;

extern ULONG __cdecl Net_Initialise(LPGUID lpGUID);
extern VOID __cdecl Net_Shutdown(VOID);
extern LPUCHAR __cdecl Net_GetPlayerName(lpNetPlayer player);
extern BOOL __cdecl Net_InitialiseConnection(ULONG index);
extern ULONG __cdecl Net_EnumerateSessions(LPGUID guid);
extern lpNetSession __cdecl Net_GetSession(ULONG index);
extern BOOL __cdecl Net_JoinSession(LPGUID appGUID, lpNetSession session, BOOL (*PlayerAddedCallback)(lpNetPlayer player, BOOL removed, LPVOID data), LPVOID data);
extern BOOL __cdecl Net_CreateSession(LPGUID appGUID, LPUCHAR name, ULONG maxPlayers, BOOL useProtocol, BOOL clientServer, BOOL (*PlayerAddedCallback)(lpNetPlayer player, BOOL removed, LPVOID data), LPVOID data);
extern lpNetPlayer __cdecl Net_GetServerPlayer(VOID);
extern lpNetPlayer __cdecl Net_CreatePlayer(LPUCHAR name);
extern BOOL __cdecl Net_Update(BOOL (*MessageCallback)(lpNetPlayer thisPlayer, lpNetPlayer fromPlayer, LPVOID messageBuffer, ULONG messageBufferSize, LPVOID data), LPVOID data);
extern BOOL __cdecl Net_SendMessage(lpNetPlayer fromPlayer, lpNetPlayer toPlayer, LPVOID data, ULONG dataSize);
extern LPVOID __cdecl Net_GetPlayerData(lpNetPlayer player);
extern VOID __cdecl Net_SetPlayerData(lpNetPlayer player, LPVOID data);
extern LPUCHAR __cdecl Net_GetConnectionName(ULONG index);
extern VOID __cdecl Net_TagIPAddress(ULONG connectionIndex, LPUCHAR address);
extern VOID __cdecl Net_Close(VOID);
