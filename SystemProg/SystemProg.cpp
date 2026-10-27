#include <windows.h>
#include <iostream>
using namespace std;
int main()
{
    char c;
    HANDLE hStdout;
    WORD wAttribute;
    cout << "In order to set text attributes, input any char: ";
    cin >> c;

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    wAttribute = BACKGROUND_GREEN | BACKGROUND_INTENSITY |
        FOREGROUND_RED | FOREGROUND_INTENSITY;

    if (!SetConsoleTextAttribute(hStdout, wAttribute))
    {
        cout << "Set console text attribute failed." << endl;
        return GetLastError();
    }
    cout << "The text attributes was changed." << endl;
    return 0;
}