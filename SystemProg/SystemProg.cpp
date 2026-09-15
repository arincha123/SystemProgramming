#include <windows.h>
#include <iostream>

using namespace std;


int main()
{
	HMODULE hDll;
	const char* in = "f1.txt";
	const char* out = "f2.txt";

	/*if (argc != 3) {
		return 1;
	}*/

	hDll = LoadLibrary("Dll.dll");
	if (!hDll) {
		cerr << "Load library falled" << GetLastError() << endl;
		return 1;
	}

	typedef int (*RemoveSpacesFn)(const char*, const char*);
	RemoveSpacesFn fn = (RemoveSpacesFn)GetProcAddress(hDll, MAKEINTRESOURCE(1));
	if (!fn) {
		cerr << "GetProcAddress failed." << GetLastError() << endl;
		return 1;
	}

	int rc = fn(in, out);
	cout << (rc == 0 ? "Done" : "Error.") << endl;

	FreeLibrary(hDll);
	return rc;
}
