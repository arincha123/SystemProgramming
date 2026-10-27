#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#define BUF_SIZE 256

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) {
        return 1;
    }

    bool suppressErrors = false;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0) {
            suppressErrors = true;
        }
    }

    // Демонстрационный блок на случай, если файлы не были переданы через консоль
    if (argc < 2 || (argc == 2 && suppressErrors)) {
        printf("Использование: program.exe [-s] файл1 файл2 ...\n");
        printf("Запуск демонстрации работы флага -s с несуществующим файлом 'missing.txt':\n\n");

        // Пытаемся открыть несуществующий файл для демонстрации
        HANDLE hIn = CreateFile("missing.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
        if (hIn == INVALID_HANDLE_VALUE) {
            if (!suppressErrors) {
                printf("Ошибка Win32 API: Не удалось открыть файл missing.txt. Код: %x\n", GetLastError());
            }
        }
        return 0;
    }

    // Шаг 2: Последовательно обрабатываем и выводим каждый файл
    HANDLE hIn;
    DWORD nIn, nOut;
    CHAR Buffer[BUF_SIZE];

    for (int i = 1; i < argc; i++) {
        // Пропускаем сам флаг -s, обрабатываем только имена файлов
        if (strcmp(argv[i], "-s") == 0) {
            continue;
        }

        // Открываем текущий файл
        hIn = CreateFile(argv[i], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

        if (hIn == INVALID_HANDLE_VALUE) {
            // Если флаг -s не активен, выводим сообщение об ошибке
            if (!suppressErrors) {
                printf("Ошибка Win32 API: Не удалось открыть файл '%s'. Код: %x\n", argv[i], GetLastError());
            }
            continue; // Переходим к следующему файлу
        }

        if (!suppressErrors) {
            printf("--- Содержимое файла: %s ---\n", argv[i]);
        }

        // Шаг 3: Читаем файл блоками и пишем на стандартное устройство вывода
        while (ReadFile(hIn, Buffer, BUF_SIZE, &nIn, NULL) && nIn > 0) {
            WriteFile(hStdOut, Buffer, nIn, &nOut, NULL);
            if (nIn != nOut) {
                printf("\nФатальная ошибка записи на стандартное устройство вывода. Код: %x\n", GetLastError());
                CloseHandle(hIn);
                return 4;
            }
        }

        // Выводим перенос строки после окончания файла для разделения
        WriteFile(hStdOut, "\n", 1, &nOut, NULL);

        CloseHandle(hIn);
    }

    return 0;
}
