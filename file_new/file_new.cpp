#include <stdio.h>
#include <windows.h> 
#include <stdlib.h>
#include <string.h>

#pragma argsused
int main(int argc, char* argv[])
{
	FILE* hdl;
	char* line;
	DWORD   total = 0;
	if (argc < 2) {
		printf("No file to process!\n");
		exit(-1);
	}
	// запрос к ОС на открытие файла (только для чтения) 
	line = (char*)GetCommandLine();
	if (hdl = fopen(argv[1], "rt")) {
		// цикл чтения до конца файла 
		while (!feof(hdl)) {
			// чтение одного символа из файла
			if ((char)fgetc(hdl) == 0x20) total++;
		}
		printf("(ProcesslD: %lu), File %s spaces = %d\n", GetCurrentProcessId(), argv[1], total);
		// закрытие файла
		fclose(hdl);
	}
	else {
		printf("Can't open file %s!\n", argv[1]);
		return (-1);
	}
	return total;
	return 0;
}

