#include "pch.h"

BOOL Hook(void* pAddr, void* pNAddr, int len)
{
	if (len < 5)
		return FALSE;

	DWORD curProtect;
	VirtualProtect(pAddr, len, PAGE_EXECUTE_READWRITE, &curProtect);
	memset(pAddr, 0x90, len);
	DWORD relativeAddress = ((DWORD)pNAddr - (DWORD)pAddr) - 5;
	*(BYTE*)pAddr = 0xE9;
	*(DWORD*)((DWORD)pAddr + 1) = relativeAddress;
	DWORD temp;
	VirtualProtect(pAddr, len, curProtect, &temp);
	return TRUE;
}
