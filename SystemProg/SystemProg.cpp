#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#pragma argsused
int main(int argc, char* argv[])
{
	int i;
	DWORD finish, result, total = 0;
	LPDWORD res = &result;
	char line[80];
	char* ln = line;
	HANDLE hThread[255];
	STARTUPINFO si[255];
	PROCESS_INFORMATION pi[255];
	if (argc < 2) {
		printf("No file to process!\n");
		exit(-1);
	}
	// Create multiple processes.
	for (i = 0; i < (argc - 1); i++) {
		strcpy(ln, "C:/Users/234777/source/repos/arincha123/SystemProgramming/x64/Debug/file_new.exe");
		ln = strcat(ln, " ");
		ln = strcat(ln, argv[i + 1]);
		ZeroMemory(&si[i], sizeof(si[i]));
		si[i].cb = sizeof(si);
		ZeroMemory(&pi[i], sizeof(pi[i]));
		//printf("Command line:%s\n", line);
		if (!CreateProcess(NULL,
			line,
			NULL,
			NULL,
			TRUE,
			NULL,
			NULL,
			NULL,
			&si[i],
			&pi[i])
			)
		{
			printf("CreateProcess failed.\n");
			//printf("%Lu",GetLastError());
			exit(-2);
		}
		else {
			printf("Process %lu started for file %s\n", pi[i].dwProcessId, argv[i + 1]);
			hThread[i] = pi[i].hProcess;
			Sleep(1000);
		}
	}
	// Wait until child process exits.
	//WaitForMultipleObjects(argc-1, hThread, TRUE, INFINITE);
	for (i = 0; i < (argc - 1); i++)
	{
		finish = WaitForSingleObject(pi[i].hProcess, INFINITE);
		if (finish == WAIT_OBJECT_0) {
			//printf("Process %Lu is finished\n",pi[i].dwProcessId);
			GetExitCodeProcess(pi[i].hProcess, res);
			printf("Process %lu finished by %d\n", pi[i].dwProcessId, result);
			total += result;
		}
		else
		{
			// Close process and thread handles.
			CloseHandle(pi[i].hProcess);
			CloseHandle(pi[i].hThread);
			TerminateProcess(pi[i].hProcess, 0);
		}
	}
	printf("%d File(s) processed with total spaces %d!\n", argc - 1, total);
	return 0;
}
