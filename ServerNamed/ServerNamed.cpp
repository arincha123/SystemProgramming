#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    HANDLE hNamedPipe;

    hNamedPipe = CreateNamedPipe("\\\\.\\pipe\\demo_pipe", PIPE_ACCESS_INBOUND, PIPE_TYPE_MESSAGE | PIPE_WAIT, 1, 0, 0, INFINITE, NULL);

    if (hNamedPipe == INVALID_HANDLE_VALUE) {
        cerr << "Create named pipe failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any key to exit.";
        cin.get();
        return 0;
    }

    cout << "The server is waiting for connection with a client." << endl;
    if (!ConnectNamedPipe(hNamedPipe, NULL)) {
        cerr << "The connection failed." << endl
            << "The last error code: " << GetLastError() << endl;
        CloseHandle(hNamedPipe);
        cout << "Press any key to exit.";
        cin.get();
        return 0;
    }

    for (int i = 0; i < 10; i++) {
        int nData;
        DWORD dwBytesRead;
        if (!ReadFile(hNamedPipe, &nData, sizeof(nData), &dwBytesRead, NULL)) {
            cerr << "Read file failed." << endl
                << "The last error code: " << GetLastError() << endl;
            CloseHandle(hNamedPipe);
            cout << "Press any key to exit.";
            cin.get();
            return 0;
        }
        cout << "The number " << nData << " was read by the server" << endl;
    }

    CloseHandle(hNamedPipe);
    cout << "The data are read by the server." << endl;
    cout << "Press any key to exit.";
    cin.get();
    return 0;
}
