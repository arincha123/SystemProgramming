#include "windows.h"
#include "pch.h"

void TestHello(void)
{
	MessageBox(NULL, "Hello, you're calling a function in this DLL", "DLL Skeleton", MB_OK);


	return;
}
