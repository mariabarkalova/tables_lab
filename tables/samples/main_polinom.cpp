#include "../include/polinom.h"
#include "../include/monom.h"
#include "../include/table.h"
#include <iostream>
using namespace std;

void main()
{
	/*
	setlocale(LC_ALL, "Russian");
	Polynom poly1("3x1y2z1 + 2x2y2z1");
	Polynom poly2("3x1y2z1 + 2x2y2z3");
	Polynom res = poly1 + poly2;
	cout << "Сумма полиномов: " << endl;
	res.printPol();
	Polynom ress = poly1 * poly2;
	cout << "Умножение полиномов: " << endl;
	ress.printPol(); */
	//тут таблица на массиве
	/*setlocale(LC_ALL, "Russian");
	TableBase<int, string>* table;
	table = new ArrayTable<int, string>(10);
	int choice;
	int key;
	string val;
	while (true)
	{
		cout << "Выберите действие:" << endl;
		cout << "1. Вставить запись" << endl;
		cout << "2. Найти запись" << endl;
		cout << "3. Удалить запись" << endl;
		cout << "Ваш выбор: ";
		cin >> choice;
		switch (choice)
		{ 
		    case 1:
				cout << "Введите ключ: ";
				cin >> key;
				cout << "Введите значение: ";
				cin >> val;
				table->Insert(key, val);
				break;
			case 2:
				cout << "Введите ключ для поиска: ";
				cin >> key;
				string* res = table->Search(key);
				if (res != nullptr) 
				{
					cout << *res << endl;
				}
				else 
				{
					cout << "значение не найдено" << endl;
				}
				break;
		}
	}*/ 


	setlocale(LC_ALL, "Russian");
	TableBase<string, Polynom>* table = new ListTable<string, Polynom>;
	string key;
	Polynom poly1("3x1y2z1 + 2x2y2z1");
	key = "poly1";
	table->Insert(key, poly1);
	Polynom poly2("3x1y2z1 + 2x2y2z3");
	key = "poly2";
	table->Insert(key, poly2);
	/*
	Polynom* res;
	cout << "Введите ключ для поиска: ";
	cin >> key;
	res = table->Search(key);
	res->printPol();

	Polynom ress = poly1 + poly2;
	key = "poly3";
	table->Insert(key, ress);
	Polynom* resy;
	cout << "Введите ключ для поиска: ";
	cin >> key;
	resy = table->Search(key);
	resy->printPol();
	*/
	cout << "Вставили два полинома в таблицу poly1: 3x1y2z1 + 2x2y2z1" << endl << "и poly2: 3x1y2z1 + 2x2y2z3" << endl;
	int choice;
	Polynom* res;
	while (true)
	{
		cout << "Выберите действие:" << endl;
		cout << "1. Найти запись" << endl;
		cout << "2. Удалить запись" << endl;
		cout << "3. Напечатать всю таблицу" << endl;
		cout << "4. Сложить два полинома" << endl;
		cout << "Ваш выбор: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Введите ключ для поиска: ";
			cin >> key;
			res = table->Search(key);
			if (res != nullptr)
			{
				cout << "Найденное значение: " << endl;
				res->printPol();
			}
			else
			{
				cout << "значение не найдено" << endl;
			}
			break;
		case 2:
			cout << "Введите ключ для удаления: ";
			cin >> key;
			table->Delete(key);
			cout << "Запись удалена." << endl;
			break;
		case 3:
			table->PrintAll();
			break;
		case 4:
			Polynom ress = poly1 + poly2;
			key = "poly3";
			table->Insert(key, ress);
			res = table->Search(key);
			res->printPol();
			break;
		}
	}

/*
	//TableBase<string, Polynom>* Table = new ListTable<string, Polynom>;
	//TableBase<int, string>* table = new ListTable<int, string>();
	int choice;
	int key;
	//string val;
	//string* res;
	Polynom val;
	Polynom* res;
	while (true)
	{
		cout << "Выберите действие:" << endl;
		cout << "1. Вставить запись" << endl;
		cout << "2. Найти запись" << endl;
		cout << "3. Удалить запись" << endl;
		cout << "4. Сложить два полинома" << endl;
		cout << "Ваш выбор: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Введите ключ: ";
			cin >> key;
			cout << "Введите значение: ";
			cin >> val;
			table->Insert(key, val);
			break;
		case 2:
			cout << "Введите ключ для поиска: ";
			cin >> key;
			res = table->Search(key);
			if (res != nullptr)
			{
				cout << "Найденное значение: " << *res << endl;
			}
			else
			{
				cout << "значение не найдено" << endl;
			}
			break;
		case 3:
			cout << "Введите ключ для удаления: ";
			cin >> key;
			table->Delete(key);
			cout << "Запись удалена." << endl;
			break;
		case 4:
			cout << "Вы хотите сложить по ключу или по значению?" << endl;
			cout << "Если по ключу - введите 1, если по значению - введите 2" << endl;
			int flag;
			cin >> flag;
			if (flag == 1)
			{
				cout << "Введите ключ для первого полинома: " << endl;
				cin >> key;
				cout << "Введите ключ для второго полинома: " << endl;
				cin >> key;
				Polynom poly1 = table->Search(key);


			}
			if (flag == 2)
			{
				Polynom poly1("3x1y2z1 + 2x2y2z1");
				Polynom poly2("3x1y2z1 + 2x2y2z3");
				Polynom res = poly1 + poly2;
				cout << "Сумма полиномов: " << endl;
				res.printPol();
			}
			break;
		}
	}*/
}