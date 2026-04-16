#include <iostream>
#include <windows.h>
#include <string.h>

using namespace std;

int main()
{
    char machineName[80];
    char pipeName[80];
    HANDLE hNamedPipe;
    DWORD dwBytesWritten;
    DWORD dwBytesRead;
    char pchMessage[80];
    int nMessageLength;

    cout << "Enter a name of the server machine: ";
    cin >> machineName;
    wsprintf(pipeName, "\\\\.\\pipe\\demo_pipe", machineName);

    hNamedPipe = CreateFile(pipeName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hNamedPipe == INVALID_HANDLE_VALUE) {
        cerr << "Connection with the named pipe failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any key to exit.";
        cin.get();
        return 0;
    }

    cin.get();
    cout << "Input a string: ";
    cin.getline(pchMessage, 80);

    nMessageLength = strlen(pchMessage) + 1;
    if (!WriteFile(hNamedPipe, pchMessage, nMessageLength, &dwBytesWritten, NULL)) {
        cerr << "Write file failed." << endl
            << "The last error code: " << GetLastError() << endl;
        CloseHandle(hNamedPipe);
        cout << "Press any key to exit.";
        cin.get();
        return 0;
    }
    cout << "The cient sent the message to a client: "
        << endl << '\t' << pchMessage << endl;

    if (!ReadFile(hNamedPipe, pchMessage, sizeof(pchMessage), &dwBytesRead, NULL)) {
        cerr << "Read file failed." << endl
            << "The last error code: " << GetLastError() << endl;
        CloseHandle(hNamedPipe);
        cout << "Press any key to exit.";
        cin.get();
        return 0;
    }

    cout << "The client received the message from a server: "
        << endl << '\t' << pchMessage << endl;
    CloseHandle(hNamedPipe);
    cout << "Press any key to exit.";
    cin.get();
    return 0;
}