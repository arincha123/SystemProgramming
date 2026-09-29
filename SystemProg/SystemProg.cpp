#include <iostream>
#include <windows.h>
#include <stdio.h>
HINSTANCE hLib;
void(*TestHello)(void);

int main(int argc, char* argv[])
{
	hLib = LoadLibrary("dllm.dll");
	if (hLib == NULL) {
		printf("Cannot load library");
		exit(-1);
	}
	TestHello = (void(*)(void))GetProcAddress(hLib, "TestHello");
	if (TestHello == NULL) {
		printf("TestHello function not found");
		exit(-2);
	}
	(*TestHello)();
	FreeLibrary(hLib);
	return TRUE;
}