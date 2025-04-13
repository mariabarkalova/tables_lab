#include<iostream>
#include"../include/hashTable.h"

using namespace std;

void main()
{
    setlocale(LC_ALL, "Russian");

    size_t initialCapacity = 11;
    HashTable<int, string> ht(initialCapacity);
    ht.Insert(1, "Veronika");
    ht.Insert(12, "Masha");
    ht.Insert(23, "Nastia");
    ht.Insert(34, "Karina");

    ht.PrintTable();

    size_t index = ht.Find(12);
    if (index != -1) {
        cout << "������ ���� 12, ������: " << index << endl;
    }
    else {
        cout << "���� 12 �� ������" << endl;
    }

    ht.Delete(12);
    cout << "����� �������� ����� 12:" << endl;
    ht.PrintTable();
    ht.Insert(12, "Masha");
    ht.PrintTable();
    ht.Insert(1222222, "Masha");
    ht.PrintTable();
}