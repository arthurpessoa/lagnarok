#include "stdafx.h"
#include "winsockhook.h"
#include <iostream>
#include <fstream>

BYTE WinsockHook::sendHook[6];
BYTE WinsockHook::recvHook[6];
BYTE WinsockHook::connectHook[6];
BYTE WinsockHook::selectHook[6];
BYTE WinsockHook::closesocketHook[6];

void WinsockHook::hook() {
	hookAPI.hook(TEXT("ws2_32.dll"), "connect", (LPVOID*)nConnect, connectHook);
	hookAPI.hook(TEXT("ws2_32.dll"), "send", (LPVOID*)nSend, sendHook);
	hookAPI.hook(TEXT("ws2_32.dll"), "recv", (LPVOID*)nRecv, recvHook);
	hookAPI.hook(TEXT("ws2_32.dll"), "select", (LPVOID*)nSelect, selectHook);
	hookAPI.hook(TEXT("ws2_32.dll"), "closesocket", (LPVOID*)nClosesocket, closesocketHook);
	MessageBoxA(NULL, "Hooked!", "Lagnarok", MB_OK);
}


int __stdcall WinsockHook::nClosesocket(SOCKET s) {

	hookAPI.unhook(TEXT("ws2_32.dll"), "closesocket", closesocketHook);
	hookAPI.unhook(TEXT("ws2_32.dll"), "send", sendHook);
	hookAPI.unhook(TEXT("ws2_32.dll"), "recv", recvHook);


	int result = closesocket(s);

	hookAPI.hook(TEXT("ws2_32.dll"), "closesocket", (LPVOID*)nClosesocket, closesocketHook);
	hookAPI.hook(TEXT("ws2_32.dll"), "recv", (LPVOID*)nRecv, recvHook);
	hookAPI.hook(TEXT("ws2_32.dll"), "send", (LPVOID*)nSend, sendHook);
	return result;
}

int __stdcall WinsockHook::nSelect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, const struct timeval *timeout) {
		hookAPI.unhook(TEXT("ws2_32.dll"), "select", selectHook);
		int result = select(nfds, readfds, writefds, exceptfds, timeout);
		hookAPI.hook(TEXT("ws2_32.dll"), "select", (LPVOID*)nSelect, selectHook);
		return result;
}

int __stdcall WinsockHook::nSend(SOCKET s, const char *buf, int len, int flags)
{
	hookAPI.unhook(TEXT("ws2_32.dll"), "send", sendHook);

	int result = send(s, buf, len, flags);

	hookAPI.hook(TEXT("ws2_32.dll"), "send", (LPVOID*)nSend, sendHook);
	return result;
}


int __stdcall WinsockHook::nRecv(SOCKET s, char* buf, int len, int flags) {

	hookAPI.unhook(TEXT("ws2_32.dll"), "recv", recvHook);
	int result = recv(s, buf, len, flags);
	hookAPI.hook(TEXT("ws2_32.dll"), "recv", (LPVOID*)nRecv, recvHook);
	return result;
}

int __stdcall WinsockHook::nConnect(SOCKET sock, const struct sockaddr* name, int namelen) {



	hookAPI.unhook(TEXT("ws2_32.dll"), "connect", connectHook);
	hookAPI.unhook(TEXT("ws2_32.dll"), "send", sendHook); //To connect into a SSL we need use the real send & recv functions!
	hookAPI.unhook(TEXT("ws2_32.dll"), "recv", recvHook);


	int enabled = TRUE;
	int disabled = FALSE;
	setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&enabled, sizeof(int));
	int result = connect(sock, name, namelen);
	

	hookAPI.hook(TEXT("ws2_32.dll"), "recv", (LPVOID*)nRecv, recvHook);
	hookAPI.hook(TEXT("ws2_32.dll"), "send", (LPVOID*)nSend, sendHook);
	hookAPI.hook(TEXT("ws2_32.dll"), "connect", (LPVOID*)nConnect, connectHook);
	return result;
}