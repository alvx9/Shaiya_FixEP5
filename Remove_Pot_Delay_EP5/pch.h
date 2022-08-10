#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h> 

void WriteNop(LPVOID lpAddress, INT nSize);

BOOL Hook(void* pAddr, void* pNAddr, int len = 5);
void Remove_Delay_Pot();
