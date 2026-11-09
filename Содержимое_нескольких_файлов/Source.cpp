#include <windows.h>
#include <iostream>

using namespace std;

#define BUF_SIZE 4096

int main(int argc, LPTSTR argv[])
{
    setlocale(LC_ALL, "Ru");
    if (argc < 2) {
        cout << "Usage: CatFiles <file1> [file2] [file3] ..." << endl;
        return 1;
    }

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CHAR buffer[BUF_SIZE];
    DWORD nRead, nWritten;

    for (int i = 1; i < argc; ++i) {
        HANDLE hIn = CreateFile(argv[i], GENERIC_READ, FILE_SHARE_READ, NULL,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hIn == INVALID_HANDLE_VALUE) {
            cout << "Не удалось открыть файл: " << argv[i]
                << " (код ошибки: " << GetLastError() << ")" << endl;
            continue;
        }

        cout << "===== Содержимое файла: " << argv[i] << " =====" << endl;
        while (ReadFile(hIn, buffer, BUF_SIZE, &nRead, NULL) && nRead > 0) {
            if (!WriteConsole(hStdOut, buffer, nRead, &nWritten, NULL)) {
                cout << "WriteConsole failed. Error: " << GetLastError() << endl;
                break;
            }
        }
        cout << endl;

        CloseHandle(hIn);
    }

    return 0;
}