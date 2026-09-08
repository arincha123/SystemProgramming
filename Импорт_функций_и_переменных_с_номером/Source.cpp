#include <windows.h>
#include <iostream>
using namespace std;

int main() {
	HMODULE hDll;
	int (*Add)(int);
	int (*Sub)(int);
	int* pCount;

	hDll = LoadLibrary("Dll1.dll");
	if (!hDll) {
		cerr << "Load library falled" << endl;
		return GetLastError();
	}

	pCount = (int*)GetProcAddress(hDll, MAKEINTRESOURCE(3));
	if (!pCount) {
		cerr << "Get variable address failed." << endl;
		return GetLastError();
	}

	cout << "Initial count = " << (*pCount) << endl;

	Add = (int (*)(int))GetProcAddress(hDll, MAKEINTRESOURCE(1));
	Sub = (int (*)(int))GetProcAddress(hDll, MAKEINTRESOURCE(2));
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
}