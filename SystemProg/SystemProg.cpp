#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    int* a;
    const int size = 1000;

    a = (int*)VirtualAlloc(NULL,  //принимает область распределения, размер области, тип распределения (MEM_COMMIT - распределение памяти), тип защиты)
        size * sizeof(int),
        MEM_COMMIT,
        PAGE_READWRITE);
    if (!a) {
        cout << "Virtual allocation failed" << endl;
        return GetLastError();
    }

    cout << "Virtual memory address: " << a << endl;

    if (!VirtualFree(a, 0, MEM_RELEASE)) { //принимает адрес уже существующей области, размер области, тип распределения (MEM_RELEASE - освобождение памяти), тип защиты)
        cout << "Memory release failed" << endl;
        return GetLastError();
    }
    return 0;
}

