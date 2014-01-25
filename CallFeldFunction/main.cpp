#include <stdio.h>
#include "MineInit.h"
#include "ReversedFunctions.h"

DWORD WINAPI MyThread(LPVOID);
DWORD g_threadID;
HMODULE g_hModule;

MineInit User;


INT APIENTRY DllMain(HMODULE hDLL, DWORD Reason, LPVOID Reserved)
{
    switch(Reason)
    {
		case DLL_PROCESS_ATTACH:
		{
			g_hModule = hDLL;
			DisableThreadLibraryCalls(hDLL);
			AllocConsole();
			CreateThread(NULL, NULL, &MyThread, NULL, NULL, &g_threadID);
			break;
		}
		case DLL_THREAD_ATTACH:
		case DLL_PROCESS_DETACH:
		case DLL_THREAD_DETACH:
        break;
    }
    return TRUE;
}

DWORD WINAPI MyThread(LPVOID)
{
	User.GetUserInput();
    FreeLibraryAndExitThread(g_hModule, 0);
    return 0;
}