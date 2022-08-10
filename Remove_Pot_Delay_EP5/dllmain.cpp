// dllmain.cpp : Define o ponto de entrada para o aplicativo DLL.
#include "pch.h"
extern  "C"  __declspec(dllexport) void __cdecl Main()
{


}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Main();
        Remove_Delay_Pot(); 
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

