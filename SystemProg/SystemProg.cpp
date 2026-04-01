#include <stdio.h>
#include <cerrno>
#define BUF_SIZE 256

using namespace std;

int main()
{
    FILE* in_file, * out_file;
    char rec[BUF_SIZE];
    size_t bytes_in, bytes_out;

    in_file = fopen("File1.txt", "rb");
    if (in_file == NULL) {
        perror("File1.txt");
        return 2;
    }

    out_file = fopen("File2.txt", "wb");
    if (out_file == NULL) {
        perror("File2.txt");
        return 3;
    }

    while ((bytes_in = fread(rec, 1, BUF_SIZE, in_file)) > 0) {
        bytes_out = fwrite(rec, 1, bytes_in, out_file);
        if (bytes_out != bytes_in) {
            perror("Неустранимая ошибка записи");
            return 4;
        }
    }

    fclose(in_file);
    fclose(out_file);
    return 0;
}