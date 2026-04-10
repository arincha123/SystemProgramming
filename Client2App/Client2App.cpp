#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

int main()
{
    HANDLE hReadFloat, hReadText;
    char lpszReadFloat[] = "ReadFloat";
    char lpszReadText[] = "ReadText";

    hReadFloat = CreateEvent(NULL, FALSE, FALSE, lpszReadFloat);
    hReadText = CreateEvent(NULL, FALSE, FALSE, lpszReadText);

    for (int i = 0; i < 5; ++i) {
        int nData;
        cin >> nData;
        _cprintf("The number %d is read from the pipe\n", nData);
    }

    SetEvent(hReadFloat);

    for (int j = 0; j < 5; ++j) {
        Sleep(500);
        cout << (j*0.1) << endl;
    }

    WaitForSingleObject(hReadText, INFINITE);
    _cputs("The process read the text: ");

    char lpszInput[80];
    do {
        Sleep(500);
        cin >> lpszInput;
        _cputs(lpszInput);
        _cputs(" ");
    } while (*lpszInput != '\0');
    _cputs("The process finished transmission of data\n");
    _cputs("Press any key to exit\n");
    _getch();
    CloseHandle(hReadFloat);
    CloseHandle(hReadText);
    return 0;
}
