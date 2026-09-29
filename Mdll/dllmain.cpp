// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"

__declspec(dllexport) int __cdecl CalculateMaterial(int, int, int, double, double);

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		MessageBox(NULL, "The DLL is loaded", "DLL Skeleton", MB_OK);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		MessageBox(NULL, "The DLL is unloaded", "DLL Skeleton", MB_OK);
		break;
	}
	return TRUE;
}