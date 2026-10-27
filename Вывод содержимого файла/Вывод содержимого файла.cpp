#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdout == INVALID_HANDLE_VALUE) return 1;

    const char* testFile = "test.txt";
    ofstream out(testFile);
    out << "Строка 1 тестового файла.\nСтрока 2 тестового файла.\n";
    out.close();

    cout << "\nНажмите Enter для теста нового буфера экрана...";
    cin.get();

    ifstream file2(testFile);
    if (file2.is_open()) {
        HANDLE hNewBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        SetConsoleActiveScreenBuffer(hNewBuffer);

        SetStdHandle(STD_OUTPUT_HANDLE, hNewBuffer);

        char ch;
        while (file2.get(ch)) {
            cout << ch;
        }
        cout << "\n\nНажмите Enter для возврата...";

        cin.get();

        SetStdHandle(STD_OUTPUT_HANDLE, hStdout);
        SetConsoleActiveScreenBuffer(hStdout);
        CloseHandle(hNewBuffer);
        file2.close();
    }
}
