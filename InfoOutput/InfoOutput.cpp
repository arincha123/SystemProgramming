#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    HANDLE hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
        cout << "Console screen buffer info failed." << endl;
    cout << "Console screen buffer info: " << endl << endl;

    cout << "A number of columns = " << csbi.dwSize.X << endl;
    cout << "A number of rows = " << csbi.dwSize.Y << endl;
    cout << "X cursor coordinate = " << csbi.dwCursorPosition.X << endl;
    cout << "Y cursor coordinate = " << csbi.dwCursorPosition.Y << endl;
    cout << "Attributes = " << hex << csbi.wAttributes << dec << endl;

    cout << "Window upper corner = " << csbi.srWindow.Left << ", " << csbi.srWindow.Top << endl;
    cout << "Window lower corner = " << csbi.srWindow.Right << ", " << csbi.srWindow.Bottom << endl;
    cout << "Maximum number of columns = " << csbi.dwMaximumWindowSize.X << endl;
    cout << "Maximum number of rows = " << csbi.dwMaximumWindowSize.Y << endl;

    return 0;
}