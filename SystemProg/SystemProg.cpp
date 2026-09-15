#include <windows.h>
#include <iostream>

using namespace std;


int main()
{
	HMODULE hDll;
	const char* in = "C:\\Users\\234777\\source\\repos\\arincha123\\SystemProgramming\\SystemProg\\f1.txt";
	const char* out = "C:\\Users\\234777\\source\\repos\\arincha123\\SystemProgramming\\SystemProg\\f2.txt";

	/*if (argc != 3) {
		return 1;
	}*/

	hDll = LoadLibrary("C:\\Users\\234777\\source\\repos\\arincha123\\SystemProgramming\\x64\\Debug\\Dll2.dll");
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
	cout << (rc) << endl;

	FreeLibrary(hDll);
	return rc;
}
