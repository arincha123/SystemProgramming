#include <windows.h>
#include <stdio.h>
#include <iostream>

#define BUF_SIZE 256
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    //// 0. Подготовка тестового файла "File1.txt" для демонстрации
    //HANDLE hTest = CreateFile("File1.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    //if (hTest != INVALID_HANDLE_VALUE) {
    //    DWORD nWritten;
    //    const char* text = "Строка 1 из тестового файла.\nСтрока 2 из тестового файла.\nРабота с новым буфером!";
    //    WriteFile(hTest, text, (DWORD)strlen(text), &nWritten, NULL);
    //    CloseHandle(hTest);
    //}

    // =========================================================================
    // НАЧАЛО ЗАДАНИЯ 2
    // =========================================================================
    HANDLE hIn, hStdOut, hNewBuffer;
    DWORD nIn, nOut;
    CHAR Buffer[BUF_SIZE];

    // 1. Открываем файл для чтения с помощью CreateFile
    hIn = CreateFile("File1.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hIn == INVALID_HANDLE_VALUE) {
        printf("Не удалось открыть файл. Ошибка: %x\n", GetLastError());
        return 2;
    }

    printf("Нажмите Enter, чтобы переключиться на новый буфер экрана...");
    getchar();

    // 2. Сохраняем старый буфер и создаем новый активный буфер экрана
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    hNewBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hNewBuffer);

    // 3. Читаем файл блоками и записываем напрямую в новый буфер экрана через WriteFile
    while (ReadFile(hIn, Buffer, BUF_SIZE, &nIn, NULL) && nIn > 0) {
        WriteFile(hNewBuffer, Buffer, nIn, &nOut, NULL);
        if (nIn != nOut) {
            // В случае ошибки возвращаем старый экран, чтобы увидеть сообщение
            SetConsoleActiveScreenBuffer(hStdOut);
            printf("Фатальная ошибка записи в буфер: %x\n", GetLastError());
            CloseHandle(hIn);
            CloseHandle(hNewBuffer);
            return 4;
        }
    }

    // 4. Дописываем сообщение-инструкцию в новый буфер
    const char* msg = "\n\nНажмите Enter для возврата в основной буфер...";
    WriteFile(hNewBuffer, msg, (DWORD)strlen(msg), &nOut, NULL);

    // 5. Ожидаем нажатия Enter (так как getchar() считывает из стандартного потока, он сработает штатно)
    getchar();

    // 6. Возвращаем исходный буфер экрана на место и закрываем дескрипторы
    SetConsoleActiveScreenBuffer(hStdOut);

    CloseHandle(hIn);
    CloseHandle(hNewBuffer);

    printf("Мы успешно вернулись в исходный буфер экрана!\n");

    // Удаляем временный файл
    DeleteFile("File1.txt");

    return 0;
}
