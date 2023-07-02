// dllmain.cpp : Defines the entry point for the DLL application.
#include "Windows.h"

#pragma warning( disable : 4100) // hmodule & lpReserved are not used, names are retained to improve code readability
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

