#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

#define BUF_SIZE 4096

int main(int argc, LPTSTR argv[])
{
    setlocale(LC_ALL, "Ru");
    if (argc != 2) {
        cout << "Usage: BufFromFile <filename>" << endl;
        return 1;
    }

    HANDLE hIn = CreateFile(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hIn == INVALID_HANDLE_VALUE) {
        cout << "Unable to open file. Error: " << GetLastError() << endl;
        return 2;
    }

    HANDLE hNewBuf = CreateConsoleScreenBuffer(
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL);
    if (hNewBuf == INVALID_HANDLE_VALUE) {
        cout << "CreateConsoleScreenBuffer failed. Error: " << GetLastError() << endl;
        CloseHandle(hIn);
        return 3;
    }

    if (!SetConsoleActiveScreenBuffer(hNewBuf)) {
        cout << "SetConsoleActiveScreenBuffer failed. Error: " << GetLastError() << endl;
        CloseHandle(hIn);
        CloseHandle(hNewBuf);
        return 4;
    }

    CHAR buffer[BUF_SIZE];
    DWORD nRead, nWritten;
    while (ReadFile(hIn, buffer, BUF_SIZE, &nRead, NULL) && nRead > 0) {
        if (!WriteConsole(hNewBuf, buffer, nRead, &nWritten, NULL)) {
            cout << "WriteConsole failed. Error: " << GetLastError() << endl;
            break;
        }
    }

    CloseHandle(hIn);

    cout << "\nФайл выведен в новый буфер экрана." << endl;
    cout << "Нажмите любую клавишу для выхода..." << endl;
    system("pause > nul");

    CloseHandle(hNewBuf);
    return 0;
}