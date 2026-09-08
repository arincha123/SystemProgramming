#include "pch.h"
#include <Windows.h>

BOOL WINAPI DllMain(HINSTANCE HDll, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

extern "C" _declspec(dllexport) int count = 0;
extern "C" _declspec(dllexport) int Add(int n) {
	count += n;
	return count;
}
extern "C" _declspec(dllexport) int Sub(int n) {
	count -= n;
	return count;
}