#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    HANDLE hMailslot;
    char mailslotName[] = "\\\\.\\mailslot\\demo_mailslot";

    hMailslot = CreateFile(mailslotName, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hMailslot == INVALID_HANDLE_VALUE) {
        cerr << "Create mailslot failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any key to finish server.";
        cin.get();
        return 0;
    }

    int n;
    cout << "Input an interger: ";
    cin >> n;
    DWORD dwBytesWritten;
    if (!WriteFile(hMailslot, &n, sizeof(n), &dwBytesWritten, NULL))
    {
        cerr << "Write file failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any key to finish the client.";
        cin.get();
        CloseHandle(hMailslot);
        return 0;
    }

    CloseHandle(hMailslot);
    cout << "The number is written by the client" << endl;
    cout << "Press any key to exit." << endl;
    cin.get();
    return 0;
}