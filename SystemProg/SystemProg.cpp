#include <iostream>
#include <windows.h>
#include <stdio.h>
HINSTANCE hLib;
void(*TestHello)(void);

int main(int argc, char* argv[])
{
	hLib = LoadLibrary("dllm.dll");
	if (hLib == NULL) {
		printf("Cannot load library");
		exit(-1);
	}
	TestHello = (void(*)(void))GetProcAddress(hLib, "TestHello");
	if (TestHello == NULL) {
		printf("TestHello function not found");
		exit(-2);
	}
	(*TestHello)();
	FreeLibrary(hLib);
	return TRUE;

    HMODULE hDll = LoadLibrary("calculate.dll");

    if (hDll == NULL) {
        std::cout << "[ОШИБКА]: Файл 'material_calc.dll' не найден!\n";
        std::cout << "Положите DLL файл в папку с программой и запустите снова.\n";
        system("pause");
        return 1; // Выходим из программы, так как библиотеки нет
    }
    std::cout << "[УСПЕХ]: Библиотека material_calc.dll успешно загружена.\n\n";

    // 3. Шаг 2: Ищем функцию внутри загруженной библиотеки
    calculate CalculateMaterial = (CalculateMaterialFunc)GetProcAddress(hDll, "CalculateMaterial");

    if (CalculateMaterial == NULL) {
        std::cout << "[ОШИБКА]: Функция 'CalculateMaterial' не найдена внутри DLL!\n";
        FreeLibrary(hDll); // Обязательно освобождаем память перед выходом
        system("pause");
        return 1; // Выходим из программы
    }
    std::cout << "[УСПЕХ]: Функция 'CalculateMaterial' найдена и готова к работе.\n\n";

    // 4. Шаг 3: Ввод данных от пользователя
    int prodType, matType, quantity;
    double param1, param2;

    std::cout << "Введите тип продукции (1, 2 или 3): ";
    std::cin >> prodType;

    std::cout << "Введите тип материала (1, 2 или 3): ";
    std::cin >> matType;

    std::cout << "Введите количество готовой продукции: ";
    std::cin >> quantity;

    std::cout << "Введите параметр продукции 1 (размер/вес): ";
    std::cin >> param1;

    std::cout << "Введите параметр продукции 2 (размер/вес): ";
    std::cin >> param2;

    // 5. Шаг 4: Вызов функции из DLL
    std::cout << "\nОтправка данных в DLL для расчета...\n";
    int result = CalculateMaterial(prodType, matType, quantity, param1, param2);

    // 6. Шаг 5: Проверка результата
    if (result == -1) {
        std::cout << "\n[УВЕДОМЛЕНИЕ]: Функция вернула -1!\n";
        std::cout << "Вы ввели неверные ID типов или отрицательные параметры продукции.\n";
    }
    else {
        std::cout << "\n[РЕЗУЛЬТАТ]: Расчет выполнен успешно!\n";
        std::cout << "Требуемое количество материала (с учетом брака): " << result << "\n";
    }

    // 7. Шаг 6: Выгрузка библиотеки из памяти
    FreeLibrary(hDll);
    std::cout << "\n[УСПЕХ]: Библиотека успешно выгружена из памяти.\n";

    std::cout << "Работа программы завершена.\n";
    system("pause");
    return 0;
}