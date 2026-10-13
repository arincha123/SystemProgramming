#include <windows.h>
#include <iostream>
using namespace std;
int main()
{
    HANDLE hStdOut, hStdIn;
    DWORD dwWritten, dwRead;
    char buffer[80];
    char str[] = "Input any string:";
    char c;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE || hStdIn == INVALID_HANDLE_VALUE)
    {
        cout << "Get standard handle failed." << endl;
        return GetLastError();
    }

    if (!WriteConsole(hStdOut, &str, sizeof(str), &dwWritten, NULL))
    {
        cout << "Write console failed." << endl;
        return GetLastError();
    }

    if (!ReadConsole(hStdIn, &buffer, sizeof(buffer), &dwRead, NULL))
    {
        cout << "Read console failed." << endl;
        return GetLastError();
    }

    cout << "Input any char to exit: ";
    cin >> c;
    return 0;


}
