#include "stdafx.h"
#include "hookapi.h"

DWORD HookAPI::pPrevious;
BYTE HookAPI::jmp[6] = { 0xe9, 0x00, 0x00, 0x00, 0x00, 0xc3 };

DWORD HookAPI::hook(LPCWSTR lpModule, LPCSTR lpFuncName, LPVOID lpFunction, unsigned char *lpBackup)
{
	DWORD dwAddr = (DWORD)GetProcAddress(GetModuleHandle(lpModule), lpFuncName);
	ReadProcessMemory(GetCurrentProcess(), (LPVOID)dwAddr, lpBackup, 6, 0);
	DWORD dwCalc = ((DWORD)lpFunction - dwAddr - 5);
	VirtualProtect((void*)dwAddr, 6, PAGE_EXECUTE_READWRITE, &pPrevious);
	memcpy(&jmp[1], &dwCalc, 4);
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)dwAddr, jmp, 6, 0);
	VirtualProtect((void*)dwAddr, 6, pPrevious, &pPrevious);
	FlushInstructionCache(GetCurrentProcess(), 0, 0);
	return dwAddr;
}

bool HookAPI::unhook(LPCWSTR lpModule, LPCSTR lpFuncName, unsigned char *lpBackup) 
{
	DWORD dwAddr = (DWORD)GetProcAddress(GetModuleHandle(lpModule), lpFuncName);
	if (WriteProcessMemory(GetCurrentProcess(), (LPVOID)dwAddr, lpBackup, 6, 0))
		return true;
	FlushInstructionCache(GetCurrentProcess(), 0, 0);
	return true;
}
