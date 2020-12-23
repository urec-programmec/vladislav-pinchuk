#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

class Spisok
{
private:
	class elem
	{
	public:
		int value;
		elem* previous;
		elem* following;

		elem(int Data) {
			this->value = Data;
			this->following = NULL;
			this->previous = NULL;
		}
	};

	elem* head;

public:
	void addStart(int znachenie);
	void addEnd(int znachenie);
	void addAtIndex(int index, int znachenie);
	bool delStart();
	bool delEnd();
	string toString(bool isReverse);
	bool addBefore(int find, int add);
	bool addAfter(int find, int add);
	bool delBefore(int find);
	bool delAfter(int find);
	int find(int index);
	int findIndex(int znachenie);
	int dlina();
	Spisok();
	~Spisok();
};

void Spisok::addStart(int znachenie) {
	elem* temp = new elem(znachenie);

	if (this->head != NULL) {
		temp->following = this->head;
		this->head->previous = temp;

		this->head = temp;
	}
	else {
		this->head = temp;
	}
}

void Spisok::addEnd(int znachenie) {

	if (this->head == NULL) {
		this->head = new elem(znachenie);
	}
	else {
		elem* temp = this->head;
		while (temp->following != NULL) {
			temp = temp->following;
		}

		elem* newElement = new elem(znachenie);
		temp->following = newElement;
		newElement->previous = temp;
	}
}

bool Spisok::delStart() {
	if (this->head == NULL)
		return false;

	int k = head->value;
	elem* temp = this->head;

	this->head = this->head->following;

	if (this->head != NULL)
		this->head->previous = NULL;

	temp->following = NULL;

	delete temp;
	return true;
}

int Spisok::dlina() {
	elem* temp = this->head;
	int tempIndex = 0;

	while (temp != NULL) {
		tempIndex += 1;
		temp = temp->following;
	}

	return tempIndex;
}

int Spisok::findIndex(int znachenie) {
	elem* temp = this->head;
	int index = -1;
	int tempIndex = 0;


	while (temp != NULL) {
		if (znachenie == temp->value) {
			index = tempIndex;
			break;
		}

		tempIndex += 1;
		temp = temp->following;
	}

	return index;
}

int Spisok::find(int index) {
	if (index < 0 || index >= this->dlina())
		return false;

	int tempIndex = 0;
	elem* temp = this->head;

	while (temp != NULL) {
		if (index == tempIndex)
			return temp->value;

		tempIndex += 1;
		temp = temp->following;
	}
}

void Spisok::addAtIndex(int index, int znachenie) {

	if (index < 0 || index >= this->dlina())
		return;

	int tempIndex = 0;
	elem* temp = this->head;

	while (temp != NULL) {
		if (index == tempIndex) {
			int value1 = temp->value;
			temp->value = znachenie;
			return;
		}

		tempIndex += 1;
		temp = temp->following;
	}

}

string Spisok::toString(bool isReverse = false) {

	if (this->head == NULL)
		return "";

	string temp = "";

	if (!isReverse) {
		elem* move = this->head;

		while (move != NULL)
		{
			temp += to_string(move->value) + " ";
			move = move->following;
		}

		temp += "\n";
	}
	else {
		elem* move = this->head;
		while (move->following != NULL)
		{
			move = move->following;
		}

		while (move != NULL)
		{
			temp += to_string(move->value) + " ";
			move = move->previous;
		}

		temp += "\n";
	}


	return temp;
}

bool Spisok::delEnd() {
	if (this->head == NULL)
		return false;

	elem* temp = this->head;
	while (temp->following != NULL) {
		temp = temp->following;
	}

	// temp = последний элемент

	if (temp->previous == NULL) {
		head = NULL;
		int znachenie = temp->value;
		delete temp;
		return true;
	}

	temp->previous->following = NULL;
	temp->previous = NULL;
	int znachenie = temp->value;
	delete temp;
	return true;
}

Spisok::Spisok()
{
	this->head = NULL;
}

Spisok::~Spisok()
{
	elem* temp = this->head;

	while (this->head != NULL) {
		this->head = this->head->following;
		delete temp;
		temp = this->head;
	}
}

bool Spisok::addAfter(int find, int add) {
	int isInList = this->findIndex(find);

	if (isInList == -1)
		return false;

	elem* temp = this->head;
	while (temp->value != find)
		temp = temp->following;

	if (temp->following == NULL) {
		elem* newElement = new elem(add);
		temp->following = newElement;
		newElement->previous = temp;
	}
	else {
		elem* nextLast = temp->following;
		elem* nextNew = new elem(add);

		temp->following = nextNew;
		nextLast->previous = nextNew;

		nextNew->following = nextLast;
		nextNew->previous = temp;
	}
	return true;
}

bool Spisok::addBefore(int find, int add) {
	int isInList = this->findIndex(find);

	if (isInList == -1)
		return false;

	elem* temp = this->head;
	while (temp->value != find)
		temp = temp->following;

	if (temp->previous == NULL) {
		this->addStart(add);
	}
	else {
		elem* prevLast = temp->previous;
		elem* prevNew = new elem(add);

		prevLast->following = prevNew;
		temp->previous = prevNew;

		prevNew->previous = prevLast;
		prevNew->following = temp;
	}
	return true;
}

bool Spisok::delAfter(int find) {
	int isInList = this->findIndex(find);

	if (isInList == -1)
		return false;

	elem* temp = this->head;
	while (temp->value != find)
		temp = temp->following;

	if (temp->following == NULL)
		return false;

	else {
		elem* nextOne = temp->following;
		elem* nextTwo = nextOne->following;

		if (nextTwo == NULL) {
			int znachenie = nextOne->value;
			nextOne->previous = NULL;
			temp->following = NULL;
			delete nextOne;
			return true;
		}
		else {
			temp->following = nextTwo;
			nextTwo->previous = temp;

			nextOne->following = NULL;
			nextOne->previous = NULL;
			int znachenie = nextOne->value;
			delete nextOne;
			return true;
		}

	}
}

bool Spisok::delBefore(int find) {
	int isInList = this->findIndex(find);

	if (isInList == -1)
		return false;

	elem* temp = this->head;
	while (temp->value != find)
		temp = temp->following;

	if (temp->previous == NULL)
		return false;

	else {
		elem* prevOne = temp->previous;
		elem* prevTwo = prevOne->previous;

		if (prevTwo == NULL) {
			int znachenie = prevOne->value;
			prevOne->following = NULL;
			temp->previous = NULL;

			this->head = temp;

			delete prevOne;
			return true;
		}
		else {
			temp->previous = prevTwo;
			prevTwo->following = temp;

			prevOne->following = NULL;
			prevOne->previous = NULL;
			int znachenie = prevOne->value;
			delete prevOne;
			return true;
		}
	}
}


int main() {
	setlocale(LC_ALL, "rus");

	string komanda = "komanda";
	string menu = "Меню:\n1. -- Новый список\n2. -- Добавление в начало списка\n3. -- Добавление в конец списка\n4. -- Вывод списка (прямо и обратно)\n5. -- Поиск (по значению)\n6. -- Поиск (по индексу)\n7. -- Добавление перед заданным\n8. -- Добавление после заданного\n9. -- Удаление из начала\n10. -- Удаление из конца\n11. -- Удаление перед заданным\n12. -- Удаление после заданного\n13. -- Задание 16. Удалить из непустого списка за каждым вхождением элемента Е один элемент, если такой есть\n14. -- Задание Y\n0. -- Выход\n\n";
	Spisok spisok, spisok1;
	int dlina, znachenie, znachenie1, znachenie2;

	cout << menu;

	while (komanda != "0") {
		cout << "Введите команду  (x - показать меню)\n";
		cin >> komanda;

		if (komanda == "x") {
			cout << menu;
		}
		else if (komanda == "1") {
			dlina = spisok.dlina();
			for (int q = 0; q < dlina; q++)
				spisok.delStart();

			cout << "Длина списка:\n";
			cin >> dlina;

			cout << "Значения списка:\n";
			for (int q = 0; q < dlina; q++) {
				cin >> znachenie;
				spisok.addEnd(znachenie);
			}

			cout << "Список создан!\n";
		}
		else if (komanda == "2") {
			cout << "Что добавить:\n";

			cin >> znachenie;
			spisok.addStart(znachenie);

			cout << "Значение добавлено!\n";
		}
		else if (komanda == "3") {
			cout << "Что добавить:\n";

			cin >> znachenie;
			spisok.addEnd(znachenie);

			cout << "Значение добавлено!\n";
		}
		else if (komanda == "4") {
			cout << "Список:\n";
			cout << spisok.toString();

			cout << "Список (развёрнутый):\n";
			cout << spisok.toString(true);
		}
		else if (komanda == "5") {
			cout << "Что искать (значение):\n";

			cin >> znachenie;
			znachenie = spisok.findIndex(znachenie);

			if (znachenie == -1)
				cout << "Значения в списке нет!\n";
			else
				cout << "Значение в списке есть!\n";
		}
		else if (komanda == "6") {
			cout << "Что искать (индекс):\n";

			cin >> znachenie;

			if (spisok.find(znachenie))
				cout << "По этому индексу значение есть!\n";
			else
				cout << "По этому индексу значения нет!\n";
		}
		else if (komanda == "7") {
			cout << "После чего добавлять:\n";
			cin >> znachenie;

			cout << "Что добавлять\n";
			cin >> znachenie1;

			if (spisok.addBefore(znachenie, znachenie1) == false)
				cout << "Значения в списке нет!\n";
			else
				cout << "Значение в списке есть!\n";
		}
		else if (komanda == "8") {
			cout << "После чего добавлять:\n";
			cin >> znachenie;

			cout << "Что добавлять\n";
			cin >> znachenie1;

			if (spisok.addAfter(znachenie, znachenie1) == false)
				cout << "Значения в списке нет!\n";
			else
				cout << "Значение в списке есть!\n";
		}
		else if (komanda == "9") {
			if (spisok.delStart() == false)
				cout << "Список пустой\n";
			else
				cout << "Удалено!\n";
		}
		else if (komanda == "10") {
			if (spisok.delEnd() == false)
				cout << "Список пустой\n";
			else
				cout << "Удалено!\n";
		}
		else if (komanda == "11") {
			cout << "Перед чем удалять:\n";
			cin >> znachenie;

			if (spisok.delBefore(znachenie))
				cout << "Такого значения нет или перед ним пусто\n";
			else
				cout << "Удалено!\n";
		}
		else if (komanda == "12") {
			cout << "После чего удалять:\n";
			cin >> znachenie;

			if (spisok.delAfter(znachenie))
				cout << "Такого значения нет или перед ним пусто\n";
			else
				cout << "Удалено!\n";
		}
		else if (komanda == "13") {
			cout << "Элемент Е:\n";
			cin >> znachenie;
			dlina = spisok.dlina();

			if (dlina == 0) {
				cout << "Список пустой\n";
				continue;
			}

			dlina = spisok1.dlina();
			for (int i = 0; i < dlina; i++) {
				spisok1.delEnd();
			}

			dlina = spisok.dlina();
			znachenie1 = 0;
			for (int i = 1; i <= dlina; i++) {				
				if (znachenie1 == 1) {
					znachenie1 = 0;
					continue;
				}
				if (spisok.find(i - 1) == znachenie && i != dlina) 
					znachenie1 = 1;				

				spisok1.addEnd(spisok.find(i - 1));			
			}

			cout << "Результат:\n";
			cout << spisok1.toString();
		}
		else if (komanda == "14") {
			znachenie = 0;
			dlina = spisok1.dlina();
			for (int i = 0; i < dlina; i++) {
				spisok1.delEnd();
			}

			cout << "Длина второго списка:\n";
			cin >> dlina;

			cout << "Значения второго списка:\n";
			for (int q = 0; q < dlina; q++) {
				cin >> znachenie1;
				spisok1.addEnd(znachenie1);
			}

			if (spisok.dlina() > spisok1.dlina()) {
				cout << "Нет\n";
				continue;
			}

			// L1 = spisok
			// L2 = spisok1

			cout << "Список 1:\n" << spisok.toString();
			cout << "Список 2:\n" << spisok1.toString();

			znachenie = 0;
			while (znachenie < spisok1.dlina()){
				if (spisok1.find(znachenie) == spisok.find(0)) {
					znachenie1 = 0;
					while (znachenie1 < spisok1.dlina() && znachenie1 < spisok.dlina() && spisok1.find(znachenie + znachenie1) == spisok.find(znachenie1))
						znachenie1++;

					if (znachenie1 == spisok.dlina()) {
						znachenie = -1;
						cout << "Да\n";
						break;
					}						
				}
				znachenie++;
			}

			if (znachenie != -1)
				cout << "Нет\n";
		}
	}



	return 0;
}
