// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include <windows.h>
#include <stdio.h>


BOOL WINAPI DllMain(HINSTANCE hDll, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}

extern "C" int RemoveSpacesFromFile(const char* inputPath, const char* outputPath) {
    FILE* fin = fopen(inputPath, "rb");
    if (!fin) return -1;

    FILE* fout = fopen(outputPath, "wb");
    if (!fout) {
        fclose(fin);
        return -1;
    }

    int c;
    while ((c = fgetc(fin)) != EOF)
        if (c != ' ')
            fputc(c, fout);

    fclose(fin);
    fclose(fout);
    return 0;
}

