#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

void cout_array(int massiv[], int length) {
	cout << "[ ";

	for (int i = 0; i < length;i++) {
		cout << massiv[i] << " ";
	}
	cout << "]\n\n";
}

int sequentialSearch(int* array1, int find, int length) {
	for (int i = 0; i < length; i++) 
		if (array1[i] == find)
			return i;

	return -1;
}

int fibonacciSearch(int* array1, int find, int length) {
	int last2, last1, start, end, thisindex, result;

	last1 = 1;
	last2 = 0;
	thisindex = 1;

	result = -1;

	start = 0;
	end = length - 1;

	while (true) {
		if (array1[start] == find) {
			result = start;
			break;
		}
		if (array1[end] == find) {
			result = end;
			break;
		}
		if (start == end) {
			break;
		}

		while ((start + thisindex) <= end && array1[start + thisindex] < find) {
			last2 = last1;
			last1 = thisindex;
			thisindex = last2 + last1;
		}

		if (start + thisindex > end) {
			start += last1;
		}

		else if (array1[start + thisindex] == find) {
			result = start + thisindex;
			break;
		}
		else {
			end = start + thisindex;
			start += last1;
		}

		last2 = 0;
		last1 = 1;
		thisindex = 1;
	}

	return result;
}

void sort(int* array1, int length) {
	int value, index;

	for (int i = 0; i < length;i++) {
		// начальное задание значений
		// выбиираем очередное число
		value = array1[i];
		index = i;

		for (int j = i + 1; j < length;j++) {
			if (array1[j] < value) {
				value = array1[j];
				index = j;
			}
		}
		array1[index] = array1[i];
		array1[i] = value;
	}
}

int main() {
	setlocale(LC_ALL, "rus");

	string komanda = "komanda";
	string menu = "Меню:\n1. -- Новый массив\n2. -- Последовательный поиск\n3. -- Поиск Фибоначчи\n4. -- Вывести массив\n0. -- Выход\n\n";
	
	const int dlina = 5;
	
	int array1[dlina];
	int array2[dlina];
			
	int znachenie, znachenie1;

	cout << menu;

	while (komanda != "0") {
		cout << "Введите команду  (x - показать меню)\n";
		cin >> komanda;

		if (komanda == "x") {
			cout << menu;
		}
		else if (komanda == "1") {
			cout << "Новые значения массива:\n";
			for (int q = 0; q < dlina; q++) {
				cin >> znachenie;
				array1[q] = znachenie;
			}

			cout << "Массив создан!\n";
		}
		else if (komanda == "2") {
			cout << "Что ищем:\n";

			cin >> znachenie;

			znachenie1 = sequentialSearch(array1, znachenie, dlina);

			if (znachenie1 == -1)
				cout << "Значения в массиве нет!\n";
			else 
				cout << "Значение в массиве есть по индексу " << znachenie1 << "\n";

			cout_array(array1, dlina);					
		}
		else if (komanda == "3") {
			cout << "Что ищем:\n";

			cin >> znachenie;

			cout << "Сортируем массив для поиска Фибоначчи\n";

			sort(array1, dlina);

			znachenie1 = fibonacciSearch(array1, znachenie, dlina);

			if (znachenie1 == -1)
				cout << "Значения в массиве нет!\n";
			else 
				cout << "Значение в массиве есть по индексу " << znachenie1 << "\n";

			cout_array(array1, dlina);			
		}
		else if (komanda == "4") {
			cout_array(array1, dlina);
		}
	}

	return 0;
}
