#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

int main()
{
    HANDLE hReadFloat, hReadText;
    char lpszReadFloat[] = "ReadFloat";
    char lpszReadText[] = "ReadText";

    hReadFloat = CreateEvent(NULL, FALSE, FALSE, lpszReadFloat);
    hReadText = CreateEvent(NULL, FALSE, FALSE, lpszReadText);

    _cputs("Press any key to start communication\n");
    _getch();

    for (int i = 0; i < 5; ++i) {
        Sleep(500);
        cout << i << endl;
    }

    WaitForSingleObject(hReadFloat, INFINITE);

    for (int j = 0; j < 5; ++j) {
        float nData;
        cin >> nData;
        _cprintf("The number %2.1f is read from the pipe\n", nData);
    }   

    SetEvent(hReadText);
    cout << "This is a demo sentence" << endl;
    cout << '\0' << endl;
        
    _cputs("The process finished transmission of data\n");
    _cputs("Press any key to exit\n");
    _getch();
    CloseHandle(hReadFloat);
    CloseHandle(hReadText);
    return 0;
}
