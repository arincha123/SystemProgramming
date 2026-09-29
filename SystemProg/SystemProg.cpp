#include <iostream>
#include <windows.h>
#include <stdio.h>

using namespace std;

HINSTANCE hLib;
int (*CalculateMaterial)(int, int, int, double, double);

void RunTest(int testNum, int prodType, int matType, int quantity, double p1, double p2) {
	printf("--- Тест %d ---\n", testNum);
	printf("Входные данные: ");
	printf("Тип подукта: %d\n", prodType);
	printf("Тип материала: %d\n", matType);
	printf("Количество: %d\n", quantity);
	printf("Параметр 1: %d\n", p1);
	printf("Параметр 2: %d\n", p2);

	if (quantity <= 0 || p1 <= 0.0 || p2 <= 0.0) {
		printf("Неподходящие данные\n");
	}

	int result = (*CalculateMaterial)(prodType, matType, quantity, p1, p2);

	if (result == -1) {
		printf("Ошибка в ID типов или параметрах\n\n");
	}
	else {
		printf("Требуется материала: %d\n\n", result);
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	printf("=== Старт программы ===\n\n");

	hLib = LoadLibrary("Mdll.dll");
	if (hLib == NULL) {
		printf("Не удалось загрузить библиотеку!\n");
		exit(-1);
	}

	CalculateMaterial = (int(*)(int, int, int, double, double))GetProcAddress(hLib, "CalculateMaterial");
	if (CalculateMaterial == NULL) {
		printf("Функция не найдена в библиотеке!\n");
		exit(-2);
	}

	RunTest(1, 1, 1, 10, 5.5, 2.0);

	RunTest(2, 2, 3, 50, 1.2, 3.4);

	RunTest(3, 99, 1, 10, 2.0, 2.0);

	RunTest(4, 1, 2, -5, 4.0, 3.0);

	FreeLibrary(hLib);
	printf("Библиотека успешно выгружена из памяти\n");

	system("pause");
	return TRUE;
}