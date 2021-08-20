// dllmain.cpp : Defines the entry point for the DLL application.

#include "pch.h"
#include "detours.h"
#include "hooking.h"

DWORD WINAPI ThreadProc(LPVOID lpParameter);


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
        
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&reinterpret_cast<PVOID&>(luaL_LoadBufferx), luaL_LoadBufferHOOKED);
		DetourTransactionCommit();								
		CreateThread(nullptr, 0, ThreadProc, nullptr, 0, nullptr);
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


DWORD WINAPI ThreadProc(LPVOID lpParameter)
{

	Beep(500, 500);
	AllocConsole();
	FILE* file;
	freopen_s(&file, "conout$", "w", stdout);
	_mkdir("C:/STOLEN_LUA");
    return 0;
}