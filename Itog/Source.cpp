#include <windows.h>
#include <iostream>

using namespace std;

#define BUF_SIZE 4096

int main(int argc, LPTSTR argv[])
{
    setlocale(LC_ALL, "Ru");

    bool silent = false; 
    int firstFile = 1; 

    if (argc > 1 && lstrcmpA(argv[1], "-s") == 0) {
        silent = true;
        firstFile = 2;
    }

    if (argc <= firstFile) {
        cout << "Usage: CatFiles [-s] <file1> [file2] [file3] ..." << endl;
        return 1;
    }

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) {
        if (!silent) cout << "GetStdHandle failed. Error: " << GetLastError() << endl;
        return 2;
    }

    CHAR buffer[BUF_SIZE];
    DWORD nRead, nWritten;
    int filesProcessed = 0;

    for (int i = firstFile; i < argc; ++i) {

        if (argv[i][0] == '-') continue;

        HANDLE hIn = CreateFile(argv[i], GENERIC_READ, FILE_SHARE_READ, NULL,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (hIn == INVALID_HANDLE_VALUE) {
            DWORD err = GetLastError();

            if (!silent) {
                cout << "Не удалось открыть файл: " << argv[i];
                if (err == ERROR_FILE_NOT_FOUND)
                    cout << " (файл не существует)";
                else if (err == ERROR_PATH_NOT_FOUND)
                    cout << " (путь не найден)";
                else if (err == ERROR_ACCESS_DENIED)
                    cout << " (доступ запрещён)";
                else
                    cout << " (код ошибки: " << err << ")";
                cout << endl;
            }
            continue;
        }

        if (!silent) {
            cout << "\n===== Содержимое файла: " << argv[i] << " =====" << endl;
        }


        while (ReadFile(hIn, buffer, BUF_SIZE, &nRead, NULL) && nRead > 0) {
            if (!WriteConsoleA(hStdOut, buffer, nRead, &nWritten, NULL)) {
                if (!silent)
                    cout << "Ошибка записи в консоль. Error: " << GetLastError() << endl;
                break;
            }
        }

        CloseHandle(hIn);
        filesProcessed++;
    }

    if (!silent && filesProcessed == 0) {
        cout << "Ни один файл не был обработан." << endl;
    }

    return 0;
}