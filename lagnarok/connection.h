#pragma once
#include <Windows.h>
class Connection
{
public:
	Connection();
	~Connection();

	static void connect(SOCKET s, char* host_and_port, char* store_path);

	static int write(const char* buffer, int length);
	static int writeAll(const char* buffer, int length);

	static int read(char* buffer, int length);
	static int readAll(char* buffer, int length);

	static bool hasDataAvailable();
};