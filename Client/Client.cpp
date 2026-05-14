#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    HANDLE hMailslot;
    char mailslotName[] = "\\\\.\\mailslot\\demo_mailslot";

    hMailslot = CreateFile(mailslotName, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hMailslot == INVALID_HANDLE_VALUE) {
        cerr << "Create mailslot failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any key to finish server.";
        cin.get();
        return 0;
    }

    int n;
    cout << "Input an interger: ";
    cin >> n;
    DWORD dwBytesWritten;
    if (!WriteFile(hMailslot, &n, sizeof(n), &dwBytesWritten, NULL))
    {
        cerr << "Write file failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any key to finish the client.";
        cin.get();
        CloseHandle(hMailslot);
        return 0;
    }

    CloseHandle(hMailslot);
    cout << "The number is written by the client" << endl;
    cout << "Press any key to exit." << endl;
    cin.get();
    return 0;
}

/*int main() {
	HANDLE hIn = CreateFileA("input.txt", GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hIn == INVALID_HANDLE_VALUE) {
		MessageBoxA(0, "Не удалось открыть input.txt", "Ошибка", MB_OK);
		return 1;
	}

	HANDLE hOut = CreateFileA("output.txt", GENERIC_WRITE, 0,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hOut == INVALID_HANDLE_VALUE) {
		MessageBoxA(0, "Не удалось создать output.txt", "Ошибка", MB_OK);
		CloseHandle(hIn);
		return 1;
	}

	char buf[1024];
	DWORD read, written;
	int count = 0;

	while (ReadFile(hIn, buf, sizeof(buf), &read, NULL) && read > 0) {
		char* src = buf;
		char* dst = buf;

		for (DWORD i = 0; i < read; i++) {
			if (*src != ' ') {
				*dst++ = *src;
			}
			else {
				count++;
			}
			src++;
		}

		if (!WriteFile(hOut, buf, dst - buf, &written, NULL)) {
			MessageBoxA(0, "Ошибка при записи", "Ошибка", MB_OK);
			break;
		}
	}

	CloseHandle(hIn);
	CloseHandle(hOut);

	char result[100];
	wsprintfA(result, "Удалено пробелов: %d", count);
	MessageBoxA(0, result, "Результат", MB_OK);

	return 0;
}*/