#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    HANDLE hMailslot;
    hMailslot = CreateMailslot("\\\\.\\mailslot\\demo_mailslot", 0, MAILSLOT_WAIT_FOREVER, NULL);
    if (hMailslot == INVALID_HANDLE_VALUE) {
        cerr << "Create mailslot failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any key to finish server.";
        cin.get();
        return 0;
    }

    cout << "The mailslot is created." << endl;
    cout << "The mailslot is waiting a message." << endl;

    int nData;
    DWORD dwBytesRead;
    if (!ReadFile(hMailslot, &nData, sizeof(nData), &dwBytesRead, (LPOVERLAPPED)NULL))
    {
        cerr << "Read file failed." << endl
            << "The last error code: " << GetLastError() << endl;
        CloseHandle(hMailslot);
        cout << "Press any key to finish server.";
        cin.get();
        return 0;
    }

    cout << "The number " << nData << " was read by the server" << endl;
    CloseHandle(hMailslot);
    cout << "Press any key to exit.";
    cin.get();
    return 0;
}