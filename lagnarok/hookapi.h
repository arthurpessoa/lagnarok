#pragma once
#include <windows.h>

class HookAPI
{
public:
	static DWORD hook(LPCWSTR lpModule, LPCSTR lpFuncName, LPVOID lpFunction, unsigned char *lpBackup);
	static bool unhook(LPCWSTR lpModule, LPCSTR lpFuncName, unsigned char *lpBackup);

private:
	static DWORD pPrevious;
	static BYTE jmp[6];
};