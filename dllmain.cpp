#include <Windows.h>
#include <iostream>

HINSTANCE DllHandle;

DWORD __stdcall EjectThread(LPVOID lpParameter)
{
	Sleep(100);
	FreeLibraryAndExitThread(DllHandle, 0);
	return 0;
}

void shutdown(FILE* pFile, std::string reason)
{
	std::cout << reason << std::endl;
	Sleep(1000);
	if (pFile != nullptr)
		fclose(pFile);
	FreeConsole();
	CreateThread(0, 0, EjectThread, 0, 0, 0);
	return;
}

//================================YOUR STUFF================================

DWORD WINAPI Func(HINSTANCE hModule)
{
 AllocConsole();
 FILE* filePointer;
 freopen_s(&filePointer, "CONOUT$", "w", stdout);
 
 //...
 
 shutdown(filePointer, "reason");
 return 0;
}

//================================ENTRY POINT================================

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DllHandle = hModule;
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Func, hModule, 0, nullptr);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
