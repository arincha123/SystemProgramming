#include <iostream>
#include <windows.h>
using namespace std;

typedef int (*RemoveSpacesFn)(const char*, const char*);


int main(int argc, char* argv[])
{
	HMODULE hDll;

	if (argc != 3) {
		return 1;
	}

	hDll = LoadLibrary("DelSpaces.dll");
	if (!hDll) {
		cerr << "Load library falled" << GetLastError() << endl;
		return 1;
	}

	RemoveSpacesFn fn = (RemoveSpacesFn)GetProcAddress(hDll, MAKEINTRESOURCE(1));
	if (!fn) {
		cerr << "GetProcAddress failed." << GetLastError() << endl;
		return 1;
	}

	int rc = fn(argv[1], argv[2]);
	cout << (rc == 0 ? "Done" : "Error.") << endl;

	FreeLibrary(hDll);
	return rc;


	/*int main() {
		HMODULE hDll;
		int (*Add)(int);
		int (*Sub)(int);
		int* pCount;

		hDll = LoadLibrary("Dll1.dll");
		if (!hDll) {
			cerr << "Load library falled" << endl;
			return GetLastError();
		}

		pCount = (int*)GetProcAddress(hDll, MAKEINTRESOURCE(1));
		if (!pCount) {
			cerr << "Get variable address failed." << endl;
			return GetLastError();
		}

		cout << "Initial count = " << (*pCount) << endl;

		Add = (int (*)(int))GetProcAddress(hDll, MAKEINTRESOURCE(2));
		Sub = (int (*)(int))GetProcAddress(hDll, MAKEINTRESOURCE(3));
		if (!Add || !Sub) {
			cerr << "Get procedure address failed." << endl;
			return GetLastError();
		}

		cout << "count = " << Add(20) << endl;
		cout << "count = " << Sub(15) << endl;

		if (!FreeLibrary(hDll)) {
			cerr << "Free library failed." << endl;
			return GetLastError();
		}

		cout << "Press any key to exit ";
		cin.get();
		return 0;
	}*/
}

