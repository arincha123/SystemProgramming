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


//#include <windows.h>
//#include <stdio.h>
//
//#pragma argsused
//int main(int argc, char* argv[])
//{
//	FILE* f;
//	char buf[1024], out[1024];
//	int i, j;
//	long total = 0;
//	long size;
//
//	if (argc < 2) {
//		printf("No file to process!\n");
//		return -1;
//	}
//
//	if ((f = fopen(argv[1], "rb+")) == NULL) {
//		printf("Can't open file %s!\n", argv[1]);
//		return -1;
//	}
//
//	fseek(f, 0, SEEK_END);
//	size = ftell(f);
//	fseek(f, 0, SEEK_SET);
//
//	fread(buf, 1, size, f);
//
//	for (i = 0, j = 0; i < size; i++) {
//		if (buf[i] != ' ') {
//			buf[j++] = buf[i];
//		}
//		else {
//			total++;
//		}
//	}
//
// 
// //	if ((f = fopen(argv[1], "wb")) == NULL) {
//		printf("Can't reopen file %s!\n", argv[1]);
//		return -1;
//	}
// 
// fwrite(buf, 1, j, f)
// fclose(f)
// 
//	fseek(f, 0, SEEK_SET);
//	fwrite(buf, 1, j, f);
//	_chsize(fileno(f), j);
//
//	fclose(f);
//
//	printf("(ProcessID: %lu), File %s spaces deleted = %d\n",
//		GetCurrentProcessId(), argv[1], total);
//
//	return total;
//}

