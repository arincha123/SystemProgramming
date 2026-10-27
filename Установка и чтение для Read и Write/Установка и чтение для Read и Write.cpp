#include <windows.h>
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdout == INVALID_HANDLE_VALUE) return 1;

    cout << "Привет, о дивный мир!" << endl;

    WORD writeAttrs[12];
    for (int i = 0; i < 12; i++) {
        writeAttrs[i] = FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    }

    COORD writeCoord = { 0, 0 };
    DWORD attrsWritten = 0;

    if (WriteConsoleOutputAttribute(hStdout, writeAttrs, 12, writeCoord, &attrsWritten)) {
        cout << "\nИзменены атрибуты для " << attrsWritten << " символов." << endl;
    }
    else {
        cout << "Ошибка WriteConsoleOutputAttribute: " << GetLastError() << endl;
    }

    WORD readAttrs[12] = { 0 };
    DWORD attrsRead = 0;

    if (ReadConsoleOutputAttribute(hStdout, readAttrs, 12, writeCoord, &attrsRead)) {
        cout << "Считаны атрибуты для " << attrsRead << " символов." << endl;
    }
    else {
        cout << "Ошибка ReadConsoleOutputAttribute: " << GetLastError() << endl;
    }

    return 0;
}