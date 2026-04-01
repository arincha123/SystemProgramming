#include <windows.h>
#include <iostream>
#include <stdio.h>
using namespace std;
int main(int argc, LPUTSTR argv[]) {
	HANDLE hFile;
	long n;
	long p;
	DWORD dwBytesRead;
	int m;
	hFile = CreateFile(TEXT(argv[1]), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		cerr << "Create file failed." << endl << "The last error code: " << GetLastError() << endl;
		cout << "Press any key to finish.";
		return 0;
	}

	cout << "Input a number: ";
	cin >> n;

	p = SetFilePointer(hFile, n, NULL, FILE_BEGIN);

	if (p == -1) {
		cerr << "Set file pointer failed." << endl << "The last error code: " << GetLastError() << endl;
		CloseHandle(hFile);
		cout << "Press any key to finish.";
		cin.get();
		return 0;
	}

	cout << "File pointer: " << p << endl;

	if (!ReadFile(hFile, &m, sizeof(m), &dwBytesRead, NULL)) {
		cerr << "Read file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hFile);
		cout << "Press any key to finish.";
		return 0;
	}

	printf("The read number: %c ", m);
	CloseHandle(hFile);
	return 0;
}