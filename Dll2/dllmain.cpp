// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


extern "C" int RemoveSpacesFromFile(const char* inputPath, const char* outputPath) {

    FILE* fin;
    errno_t err = fopen_s(&fin,inputPath, "r");
    if (err != 0) return -1;

    FILE* fout;
    errno_t err1 = fopen_s(&fout, outputPath, "w");
    if (err1 != 0) {
        fclose(fin);
        return -2;
    }

    int c;
    while ((c = fgetc(fin)) != EOF)
        if (c != ' ')
            fputc(c, fout);

    fclose(fin);
    fclose(fout);
    return 0;
}


