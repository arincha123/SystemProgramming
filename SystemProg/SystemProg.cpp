#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int binary_search(string list[], int n, string a, int& step) {

    int low = 0, mid;
    string guess;
    string item = a;
    int high = n - 1;

    while (low <= high) {
        step++;
        mid = (low + high) / 2;
        guess = list[mid];
        if (guess == item) {
            return mid;
        }
        if (guess > item) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }

    }
    return -1;
}

int findSmallest(char* arr, int lenarr) {
    char smallest = arr[0];
    char smallest_index = 0;
    for (int i = 1; i < lenarr; i++) {
        if (arr[i] < smallest) {
            smallest = arr[i];
            smallest_index = i;
        }
    }
    return smallest_index;
}


int selectionSort(char* arr, int lenarr) {
    const char newarr = {};
    for (int i = 0; i < lenarr; i++) {
        char smallest = findSmallest(arr);
        newarr.append(arr.pop(smallest));
    } return newarr;
}


int main()
{
    const int n = 10;
    string a = "Мария";
    int step = 0;
    string list[n] = { "Александр", "Алексей", "Артём", "Владимир", "Дарья", "Лев", "Майя", "Мария", "Сергей", "Тимофей" };
    int b = binary_search(list, n, a, step);
    printf("Index of number %d", b);
    printf("\nCount of steps %d", step);


    return 0;
}

