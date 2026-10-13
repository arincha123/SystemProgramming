#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    COORD coord;
    HANDLE hStdOut;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "Enter new screen buffer size." << endl;
    cout << "A number of columns: ";
    cin >> coord.X;
    cout << "A number of rows: ";
    cin >> coord.Y;

    if (!SetConsoleScreenBufferSize(hStdOut, coord))
    { 
        cout << "Set console screen buffer size failed." << endl;
        return GetLastError();
    }
    return 0;
}
