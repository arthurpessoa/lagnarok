#pragma once
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <ws2tcpip.h>
#include <map>
#include "hookapi.h"

class WinsockHook
{
public:
	void hook();
private:

	static HookAPI hookAPI;
	static BYTE	sendHook[6];
	static BYTE	recvHook[6];
	static BYTE	connectHook[6];
	static BYTE	selectHook[6];
	static BYTE	closesocketHook[6];

	static int __stdcall nSend(SOCKET s, const char *buf, int len, int flags);
	static int __stdcall nRecv(SOCKET s, char* buf, int len, int flags);
	static int __stdcall nConnect(SOCKET sock, const struct sockaddr* name, int namelen);
	static int __stdcall nSelect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, const struct timeval *timeout);
	static int __stdcall nClosesocket(SOCKET s);
};