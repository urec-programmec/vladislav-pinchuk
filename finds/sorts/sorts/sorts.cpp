#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <stack>

using namespace std;

void cout_array(int* massiv, int length) {
	cout << "[ ";

	for (int i = 0; i < length;i++) {
		cout << massiv[i] << " ";
	}
	cout << "]\n\n";
}

void sortByInserts(int* massiv, int length, bool makeLessly) {
	list<int> sort;

	// makeLesly -> 5 4 3 2 1 from 4 3 5 1 2	
	for (int i = 0; i < length; i++) {		
		auto j = sort.end();
		for (auto iter = sort.begin(); iter != sort.end(); iter++)
		{
			if (massiv[i] >= *iter && !makeLessly || massiv[i] <= *iter && makeLessly)
				continue;
			j = iter;
			break;
		}

		sort.emplace(j, massiv[i]);
	}

	int i = 0;
	for (int n : sort) {
		massiv[i] = n;
		i++;
	}
}

void Merge(int *massiv, int first, int last, bool makeLessly)
{
	int middle, start, final, j;
	int *mas = new int[100];
	middle = (first + last) / 2; //вычисление среднего элемента
	start = first; //начало левой части
	final = middle + 1; //начало правой части
	for (j = first; j <= last; j++)
		
		if (final > last){
			mas[j] = massiv[start];
			start++;
		}
		else if (start > middle) {
			mas[j] = massiv[final];
			final++;
		}
		else if (massiv[start] <= massiv[final] && !makeLessly || massiv[start] >= massiv[final] && makeLessly) {
			mas[j] = massiv[start];
			start++;
		}
		else {
			mas[j] = massiv[final];
			final++;
		}		

	//возвращение результата в массив
	for (j = first; j <= last; j++) 
		massiv[j] = mas[j];
};




//рекурсивная процедура сортировки
void sortMerge(int *massiv, int first, int last, bool makeLessly)
{
	if (first < last)
	{
		sortMerge(massiv, first, (first + last) / 2, makeLessly); //сортировка левой части
		sortMerge(massiv, (first + last) / 2 + 1, last, makeLessly); //сортировка правой части
		Merge(massiv, first, last, makeLessly); //слияние двух частей
	}	
};

int main() {
	setlocale(LC_ALL, "rus");

	string komanda = "komanda";
	string menu = "Меню:\n1. -- Новый массив\n2. -- Сортировка вставками\n3. -- Сортировка методом слияния\n4. -- Вывести массив\n0. -- Выход\n\n";

	const int dlina = 10;

	int array1[dlina] = { 11, 78, 54, -3, 10, 15, 111, 232, 0, 1 };

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
			cout << "Сортировка вставками. Начальная версия массива:\n";			
			cout_array(array1, dlina);

			cout << "Сортировка по возрастанию - T, по убыванию - F (или любое другое)\n";
			cin >> komanda;

			sortByInserts(array1, dlina, komanda == "T" ? true : false);

			cout << "Отсортированная версия массива:\n";
			cout_array(array1, dlina);
			komanda = "2";

		}
		else if (komanda == "3") {
			cout << "Сортировка слиянием. Начальная версия массива:\n";
			cout_array(array1, dlina);

			cout << "Сортировка по возрастанию - T, по убыванию - F (или любое другое)\n";
			cin >> komanda;

			sortMerge(array1, 0, dlina - 1, komanda == "T" ? true : false);

			cout << "Отсортированная версия массива:\n";
			cout_array(array1, dlina);
			komanda = "3";
		}
		else if (komanda == "4") {
			cout_array(array1, dlina);
		}
	}

	return 0;
}
