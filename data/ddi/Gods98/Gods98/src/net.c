
#include <windows.h>
#include <dplobby.h>
#include <dplay.h>
#include <stdio.h>

#include "..\inc\Standard.h"
#include "..\inc\Memory.h"
#include "..\inc\Errors.h"
#include "..\inc\Net.h"

struct NetGlobs {

	LPDIRECTPLAY4 lpDP;

	struct NetConnection connectionList[NET_MAXCONNECTIONS];
	ULONG connectionCount;

	struct NetSession sessionList[NET_MAXSESSIONS];
	ULONG sessionCount;

	struct NetPlayer playerList[NET_MAXPLAYERS];

	struct NetPlayer *serverPlayer;

	HANDLE messageEvent;

	LPVOID messageBuffer;
	ULONG messageBufferSize;

	BOOL (*playerAddedCallback)(lpNetPlayer player, BOOL removed, LPVOID data);
	LPVOID playerAddedData;

	ULONG flags;

} netGlobs = { 0 };

BOOL FAR PASCAL Net_EnumConnectionsCallback(LPCGUID pguidSP, LPVOID pConnection, DWORD dwConnectionSize, LPCDPNAME pName, DWORD dwFlags, LPVOID pvContext) {

	HRESULT r;
	LPDIRECTPLAY4 lpDP;
	LPVOID pConnectionBuffer = NULL;
	lpNetConnection ci;

	if (SUCCEEDED(r = CoCreateInstance(&CLSID_DirectPlay, NULL, CLSCTX_ALL, &IID_IDirectPlay4A, &lpDP))) {
		if (SUCCEEDED(r = lpDP->lpVtbl->InitializeConnection(lpDP, pConnection, 0))) {

	//		Error_Fatal(netGlobs.connectionInfoCount == NET_MAXCONNECTIONINFO, "NET_MAXCONNECTIONINFO too small");

			ci = &netGlobs.connectionList[netGlobs.connectionCount++];

			sprintf(ci->name, "%s", pName->lpszShortNameA);
			ci->connectionBuffer = Mem_Alloc(dwConnectionSize);

			memcpy(ci->connectionBuffer, pConnection, dwConnectionSize);
		}
		lpDP->lpVtbl->Release(lpDP);
		lpDP = NULL;
	}

	return TRUE;
}

ULONG Net_Initialise(LPGUID lpGUID) {

	HRESULT r;

	if (SUCCEEDED(r = CoCreateInstance(&CLSID_DirectPlay, NULL, CLSCTX_ALL, &IID_IDirectPlay4A, &netGlobs.lpDP))) {

		if (SUCCEEDED(r = netGlobs.lpDP->lpVtbl->EnumConnections(netGlobs.lpDP, lpGUID, Net_EnumConnectionsCallback, NULL, 0))) {

			netGlobs.messageEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

			return netGlobs.connectionCount;
		}

		netGlobs.lpDP->lpVtbl->Release(netGlobs.lpDP);
		netGlobs.lpDP = NULL;
	
	} else {
		if (E_NOINTERFACE == r) {
			MessageBox(NULL, "This application requires DirectPlay 6 or later.\nThe sample will now quit.", "DirectPlay Sample", MB_OK|MB_ICONERROR);
		}

	}

	return 0;
}

VOID Net_Close(VOID) {

	netGlobs.lpDP->lpVtbl->Close(netGlobs.lpDP);
}

LPUCHAR Net_GetConnectionName(ULONG index) {

	return netGlobs.connectionList[index].name;
}

VOID Net_TagIPAddress(ULONG connectionIndex, LPUCHAR address) {

	LPDPCOMPOUNDADDRESSELEMENT element = netGlobs.connectionList[connectionIndex].connectionBuffer;
	LPDPCOMPOUNDADDRESSELEMENT newBuffer, newElement;
	ULONG newSize;

	if (0 == memcmp(&DPAID_TotalSize, &element->guidDataType, sizeof(DPAID_TotalSize))) {

		newSize = (ULONG) element->lpData;
		newSize += sizeof(newBuffer->guidDataType) + sizeof(newBuffer->dwDataSize);
		newSize += strlen(address) + 1;

		newBuffer = Mem_Alloc(newSize);
		memcpy(newBuffer, element, (ULONG) element->lpData);
		newBuffer->lpData = (LPVOID) newSize;

		newElement = (LPDPCOMPOUNDADDRESSELEMENT) (&((LPUCHAR) element)[(ULONG) element->lpData]);
		newElement->guidDataType = DPAID_INet;
		newElement->dwDataSize = strlen(address) + 1;
		sprintf((LPUCHAR) &newElement->lpData, "%s", address);

		netGlobs.connectionList[connectionIndex].connectionBuffer = newBuffer;
		Mem_Free(element);

	} else Error_Fatal(TRUE, "Oops");
}

LPUCHAR Net_GetPlayerName(lpNetPlayer player) {

	return player->name;
}

VOID Net_Shutdown(VOID) {

	lpNetConnection ci;
	ULONG loop;

	for (loop=0 ; loop<netGlobs.connectionCount ; loop++) {
		ci = &netGlobs.connectionList[loop];
		Mem_Free(ci->connectionBuffer);
	}

    CloseHandle(netGlobs.messageEvent);

	if (netGlobs.lpDP) {
		netGlobs.lpDP->lpVtbl->Release(netGlobs.lpDP);
		netGlobs.lpDP = NULL;
	}
}

static BOOL FAR PASCAL Net_EnumSessionsCallback(LPCDPSESSIONDESC2 pdpsd, LPDWORD pdwTimeout, DWORD dwFlags, LPVOID pvContext) {
	
	lpNetSession session;

	if (!(dwFlags & DPESC_TIMEDOUT)) {

//		Error_Fatal(NET_MAXSESSIONS==netGlobs.sessionInfoCount, "NET_MAXSESSIONS too small");

		session = &netGlobs.sessionList[netGlobs.sessionCount++];
		memset(session, 0, sizeof(*session));
		
		session->guid = pdpsd->guidInstance;

		sprintf(session->name, "%s (%d/%d)", pdpsd->lpszSessionNameA, pdpsd->dwCurrentPlayers, pdpsd->dwMaxPlayers);

		return TRUE;
	}

	return FALSE;
}

BOOL Net_InitialiseConnection(ULONG index) {

	HRESULT r;

	if (SUCCEEDED(r = netGlobs.lpDP->lpVtbl->InitializeConnection(netGlobs.lpDP, netGlobs.connectionList[index].connectionBuffer, 0))) {
		return TRUE;
	}

	return FALSE;
}

ULONG Net_EnumerateSessions(LPGUID guid) {

	DPSESSIONDESC2 dpsd;
	HRESULT r;

	memset(&dpsd, 0, sizeof(dpsd));
	dpsd.dwSize = sizeof(dpsd);
	dpsd.guidApplication = *guid;

	netGlobs.sessionCount = 0;

	r = netGlobs.lpDP->lpVtbl->EnumSessions(netGlobs.lpDP, &dpsd, 0, Net_EnumSessionsCallback, NULL, DPENUMSESSIONS_RETURNSTATUS);//DPENUMSESSIONS_ALL /*| DPENUMSESSIONS_ASYNC*/);

	return netGlobs.sessionCount;
}

lpNetSession Net_GetSession(ULONG index) {

//	Error_Fatal(index >= netGlobs.sessionInfoCount, "Index out of range");

	return &netGlobs.sessionList[index];
}

static BOOL Net_MakeSession(LPGUID appGUID, LPUCHAR name, ULONG maxPlayers, BOOL useProtocol, BOOL serverClient, lpNetSession session, BOOL (*PlayerAddedCallback)(lpNetPlayer player, BOOL removed, LPVOID data), LPVOID data) {

	DPSESSIONDESC2 dpsd;
	ULONG flags;
	HRESULT r;

	memset(&dpsd, 0, sizeof(dpsd));
	dpsd.dwSize = sizeof(dpsd);
	dpsd.guidApplication = *appGUID;

	if (session) {

		dpsd.guidApplication = *appGUID;
		dpsd.guidInstance = session->guid;
		flags = DPOPEN_JOIN|DPOPEN_RETURNSTATUS;

	} else {

		dpsd.lpszSessionNameA = name;
		dpsd.dwMaxPlayers = maxPlayers;
		dpsd.dwFlags = DPSESSION_KEEPALIVE;// | DPSESSION_MIGRATEHOST;
		if (useProtocol) dpsd.dwFlags |= DPSESSION_DIRECTPLAYPROTOCOL;
		if (serverClient) dpsd.dwFlags |= DPSESSION_CLIENTSERVER;
		flags = DPOPEN_CREATE;

	}

	if (SUCCEEDED(r = netGlobs.lpDP->lpVtbl->Open(netGlobs.lpDP, &dpsd, flags))) {

		if (session) netGlobs.flags &= ~NET_FLAG_SERVER;
		else netGlobs.flags |= NET_FLAG_SERVER;

		netGlobs.playerAddedCallback = PlayerAddedCallback;
		netGlobs.playerAddedData = data;

		return TRUE;
	}

	return FALSE;
}

BOOL Net_JoinSession(LPGUID appGUID, lpNetSession session, BOOL (*PlayerAddedCallback)(lpNetPlayer player, BOOL removed, LPVOID data), LPVOID data) {

//	Error_Fatal(NULL == session, "NULL passed as 'session'");

	return Net_MakeSession(appGUID, NULL, 0, FALSE, FALSE, session, PlayerAddedCallback, data);
}
	
BOOL Net_CreateSession(LPGUID appGUID, LPUCHAR name, ULONG maxPlayers, BOOL useProtocol, BOOL clientServer, BOOL (*PlayerAddedCallback)(lpNetPlayer player, BOOL removed, LPVOID data), LPVOID data) {

	return Net_MakeSession(appGUID, name, maxPlayers, useProtocol, clientServer, NULL, PlayerAddedCallback, data);
}

static lpNetPlayer Net_AddPlayer(DPID id, LPUCHAR name) {

	lpNetPlayer player;
	ULONG loop;

	for (loop=0 ; loop<NET_MAXPLAYERS ; loop++) {

		player = &netGlobs.playerList[loop];
		
		if (!(player->flags & NETPLAYER_FLAG_USED)) {
			
			memset(player, 0, sizeof(*player));
			player->flags = NETPLAYER_FLAG_USED;
			player->id = id;
			sprintf(player->name, "%s", name);

			if (netGlobs.playerAddedCallback(player, FALSE, netGlobs.playerAddedData)) {
				return player;
			}

			player->flags &= ~NETPLAYER_FLAG_USED;
		}
	}

	return NULL;
}

static lpNetPlayer Net_FindPlayer(DPID id) {

	lpNetPlayer player;
	ULONG loop;

	for (loop=0 ; loop<NET_MAXPLAYERS ; loop++) {

		player = &netGlobs.playerList[loop];
		
		if (player->flags & NETPLAYER_FLAG_USED) {
			if (id == player->id) {
			
				return player;

			}
		}
	}

	return NULL;
}

static BOOL Net_RemovePlayer(lpNetPlayer player) {

	if (netGlobs.playerAddedCallback(player, TRUE, netGlobs.playerAddedData)) {

		player->flags &= ~NETPLAYER_FLAG_USED;

		return TRUE;
	}

	return FALSE;
}

BOOL FAR PASCAL Net_EnumPlayersCallback(DPID dpId, DWORD dwPlayerType, LPCDPNAME lpName, DWORD dwFlags, LPVOID lpContext) {

	if (!Net_FindPlayer(dpId)) {
		Net_AddPlayer(dpId, lpName->lpszShortNameA);
	}

	return TRUE;
}

BOOL FAR PASCAL Net_UpdateServerPlayerCallback(DPID dpId, DWORD dwPlayerType, LPCDPNAME lpName, DWORD dwFlags, LPVOID lpContext) {

	lpNetPlayer player;

	if (player = Net_FindPlayer(dpId)) {
		netGlobs.serverPlayer = player;
		return FALSE;
	}

	return TRUE;
}

static VOID Net_UpdateServerPlayer(VOID) {

	HRESULT r = netGlobs.lpDP->lpVtbl->EnumPlayers(netGlobs.lpDP, NULL, Net_UpdateServerPlayerCallback, NULL, DPENUMPLAYERS_SERVERPLAYER);
}

lpNetPlayer Net_GetServerPlayer(VOID) {

	if (NULL == netGlobs.serverPlayer) Net_UpdateServerPlayer();

	return netGlobs.serverPlayer;
}

LPVOID Net_GetPlayerData(lpNetPlayer player) {

	return player->data;
}

VOID Net_SetPlayerData(lpNetPlayer player, LPVOID data) {

	player->data = data;
}

lpNetPlayer Net_CreatePlayer(LPUCHAR name) {

	HRESULT r;
	lpNetPlayer player;
	DPNAME dpname;
	ULONG flags = 0;
	DPID id;

	memset(&dpname, 0, sizeof(dpname));
	dpname.dwSize = sizeof(dpname);
	dpname.lpszShortNameA = name;

	if (netGlobs.flags & NET_FLAG_SERVER) flags |= DPPLAYER_SERVERPLAYER;

	r = netGlobs.lpDP->lpVtbl->CreatePlayer(netGlobs.lpDP, &id, &dpname, netGlobs.messageEvent, NULL, 0, flags);

	if (player = Net_AddPlayer(id, name)) {

		// Enumerate the other players...
		if (SUCCEEDED(r = netGlobs.lpDP->lpVtbl->EnumPlayers(netGlobs.lpDP, NULL, Net_EnumPlayersCallback, NULL, DPENUMPLAYERS_REMOTE))) {

			Net_UpdateServerPlayer();
		
			return player;

		}

		Net_RemovePlayer(player);
		player = NULL;
	}

	return NULL;
}

static BOOL Net_HandlePlayerCreateOrRemove(LPDPMSG_CREATEPLAYERORGROUP createMessage, LPDPMSG_DESTROYPLAYERORGROUP removeMessage) {

	lpNetPlayer player;

//	Error_Fatal(NULL == createMessage || NULL == removeMessage, "'createMessage' and 'removeMessage' are NULL");

	if (createMessage) {
		if (player = Net_AddPlayer(createMessage->dpId, createMessage->dpnName.lpszShortNameA)) {
			return TRUE;
		}
	} else {
		if (player = Net_FindPlayer(removeMessage->dpId)) {
			return Net_RemovePlayer(player);
		}
	}

	Net_UpdateServerPlayer();

	return FALSE;
}

static BOOL Net_ProcessSystemMessage(LPDPMSG_GENERIC message, ULONG messageSize) { 

	BOOL result;
	LPDPMSG_CREATEPLAYERORGROUP createMessage;
	LPDPMSG_DESTROYPLAYERORGROUP deleteMessage;

	switch (message->dwType) {

	case DPSYS_SESSIONLOST:
		
		result = FALSE;

		break;

	case DPSYS_CREATEPLAYERORGROUP:

		createMessage = (LPDPMSG_CREATEPLAYERORGROUP) message;
		result = Net_HandlePlayerCreateOrRemove(createMessage, NULL);

		break;
		
	case DPSYS_DESTROYPLAYERORGROUP:

		deleteMessage = (LPDPMSG_DESTROYPLAYERORGROUP) message;		
		result = Net_HandlePlayerCreateOrRemove(NULL, deleteMessage);

		break;
	}
	
	return result;
}

static BOOL Net_ProcessDirectPlayMessages(BOOL (*MessageCallback)(lpNetPlayer thisPlayer, lpNetPlayer fromPlayer, LPVOID messageBuffer, ULONG messageBufferSize, LPVOID data), LPVOID data) {

	while (TRUE) {

		HRESULT r;
		DPID idFrom = 0;
		DPID idTo = 0;

		r = netGlobs.lpDP->lpVtbl->Receive(netGlobs.lpDP, &idFrom, &idTo, DPRECEIVE_ALL, netGlobs.messageBuffer, &netGlobs.messageBufferSize);

		if (DPERR_NOMESSAGES == r) return TRUE;
		else if (DPERR_BUFFERTOOSMALL == r) {

			netGlobs.messageBuffer = Mem_ReAlloc(netGlobs.messageBuffer, netGlobs.messageBufferSize);

		} else if (SUCCEEDED(r)) {

			if (DPID_SYSMSG == idFrom) {
				if (!Net_ProcessSystemMessage((LPDPMSG_GENERIC) netGlobs.messageBuffer, netGlobs.messageBufferSize)) {
					return FALSE;
				}
			} else {
				if (!MessageCallback(Net_FindPlayer(idTo), Net_FindPlayer(idFrom), netGlobs.messageBuffer, netGlobs.messageBufferSize, data)) {
					return FALSE;
				}
			}

		} else return FALSE;

	}
}

BOOL Net_Update(BOOL (*MessageCallback)(lpNetPlayer thisPlayer, lpNetPlayer fromPlayer, LPVOID messageBuffer, ULONG messageBufferSize, LPVOID data), LPVOID data) {

	ULONG dwResult = MsgWaitForMultipleObjects(1, &netGlobs.messageEvent, FALSE, 0, QS_ALLEVENTS);
	MSG message;

	switch (dwResult) {
		case WAIT_OBJECT_0 + 0: return Net_ProcessDirectPlayMessages(MessageCallback, data);
		case WAIT_OBJECT_0 + 1: 
			while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
				DispatchMessage(&message);
			}
			break;
	}

	return TRUE;
}

BOOL Net_SendMessage(lpNetPlayer fromPlayer, lpNetPlayer toPlayer, LPVOID data, ULONG dataSize) {

	HRESULT r;
	DPID idTo;

	if (toPlayer) idTo = toPlayer->id;
	else idTo = DPID_ALLPLAYERS;

	if (SUCCEEDED(r = netGlobs.lpDP->lpVtbl->Send(netGlobs.lpDP, fromPlayer->id, idTo, 0, data, dataSize))) {
		return TRUE;
	}

	return FALSE;
}

/*
BOOL Test_PlayerAddedCallback(lpNetPlayer player, BOOL removed, LPVOID data) {

	UCHAR message[1024];

	sprintf(message, "Player '%s' %s", player->name, removed?"removed":"added");

	MessageBox(NULL, message, "Connect", MB_OK);

	return TRUE;
}

BOOL Test_MessageCallback(LPVOID messageBuffer, ULONG messageBufferSize, LPVOID data) {

	MessageBox(NULL, (LPUCHAR) messageBuffer, "Connect", MB_OK);

	return TRUE;
}

INT APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pCmdLine, INT nCmdShow) {

	HRESULT r;
	GUID g_AppGUID = { 0xc6334fc0, 0x3b80, 0x4fed, { 0x89, 0xf1, 0xa4, 0xde, 0xfe, 0xb6, 0xdb, 0x20 } };

    if (SUCCEEDED(r = CoInitialize(NULL))) {

		ULONG sessionCount;
		lpNetPlayer me;

		Net_Initialise(&g_AppGUID);
		sessionCount = Net_EnumerateSessions(&g_AppGUID);
		if (sessionCount) Net_JoinSession(&g_AppGUID, Net_GetSession(0), Test_PlayerAddedCallback, NULL);
		else Net_CreateSession(&g_AppGUID, "A DirectPlay Sever", 10, FALSE, Test_PlayerAddedCallback, NULL);

		if (netGlobs.flags & NET_FLAG_SERVER) MessageBox(NULL, "Server Created", "Connect", MB_OK);
		else MessageBox(NULL, "Client Connected", "Connect", MB_OK);

		if (netGlobs.flags & NET_FLAG_SERVER) me = Net_CreatePlayer("Server");
		else me = Net_CreatePlayer("Client");

		{
			UCHAR msg[1024];
			sprintf(msg, "%s", "Hello everyone");
			Net_SendMessage(me, NULL, msg, strlen(msg));
			sprintf(msg, "%s", "Hello server");
			Net_SendMessage(me, Net_GetServerPlayer(), msg, strlen(msg));
		}

		while (TRUE) {
			if (!Net_Update(Test_MessageCallback, NULL)) break;
			Sleep(100);
		}

		Net_Shutdown();

	    CoUninitialize();

		MessageBox(NULL, "Exiting", "Connect", MB_OK);
	}

	return 0;
}
*/
