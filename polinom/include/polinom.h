#pragma once
#include<iostream>
#include<string>
#include <cctype>
#include <sstream>
#include<vector>
#include "monom.h"

using namespace std;
template <class T>
struct Node
{
    T value;
    Node* next;
    //Node(T val1, Node* p) : value(val1), next(p) {}
    Node(const T& value) : value(value), next(nullptr) {}
    Node(T val, Node* nextNode) : value(val), next(nextNode) {}
};

template <class T>
class List {
    Node<T>* first; //first ук-ль на первое звено
    Node<T>* last;
public:
    List() : first(nullptr) {}
    ~List() {
        while (first != nullptr) {
            Node<T>* temp = first;
            first = first->next;
            delete temp;
        }
    }
    // Конструктор копирования
    List(const List<T>& other) : first(nullptr), last(nullptr) {
        Node<T>* current = other.first;
        while (current != nullptr) {
            Insert(current->value);
            current = current->next;
        }
    }
    // Оператор присваивания
    List<T>& operator=(const List<T>& other) {
        if (this != &other) { // Проверяем самоприсваивание
            // Освобождаем текущие 
            while (first != nullptr) {
                Node<T>* temp = first;
                first = first->next;
                delete temp;
            }
            // Инициализируем указатели для нового списка
            first = nullptr;
            last = nullptr;
            // Копируем элементы из другого списка
            Node<T>* current = other.first;
            while (current != nullptr) {
                Insert(current->value);
                current = current->next;
            }
        }
        return *this;
    }

    void InsertCurr(Node<T>* prev, Node<T>* curr, T value) {  // добавление элемента между prev и curr
        Node<T>* p = new Node<T>(value, nullptr);
        if (first == nullptr) {  // Если список пуст
            first = p;
            last = p;
            return;
        }
        // Если добавляется в начало
        if (prev == nullptr) {
            p->next = first;
            first = p;
            return;
        }
        // Если добавляется в конец
        if (curr == nullptr) {
            p->next = nullptr;
            last->next = p;
            last = p;
            return;
        }
        // последний вариант - добавляение в середину, между prev и curr
        prev->next = p;
        p->next = curr;
    }

    void DeleteCurr(Node<T>* prev, Node<T>* curr) {  // удаление curr
        Node<T>* p;
        if (first == last) {  // Если список пуст
            delete curr;
            first = last = nullptr;
            return;
        }
        // Если удаляется первый
        if (prev == nullptr) {
            p = first;
            first = first->next;
            delete p;
            return;
        }
        // удаление любого другого
        if (curr != nullptr) {
            p = curr;
            prev->next = curr->next;
            delete p;
            return;
        }
    }


    void Insert(T value) {  // добавление элемента в упорядоченном порядке
        Node<T>* p = new Node<T>(value, nullptr);
        if (first == nullptr) {  // Если список пуст
            first = p;
            last = p;
            return;
        }
        // Если добавляемый элемент меньше первого элемента
        if (value < first->value) {
            p->next = first;
            first = p;
            return;
        }
        // Найдем позицию для вставки
        Node<T>* current = first;
        while (current->next != nullptr && current->next->value < value) {
            current = current->next;
        }
        p->next = current->next;
        current->next = p;
        // Обновляем указатель на последний узел
        if (p->next == nullptr) {
            last = p;
        }
    }

    /*void Insert(T val) {  //просто добавляем
        Node<T>* p = new Node<T>(val, nullptr);
        if (first == nullptr) { // Если список пуст
            first = p;
            last = p;
        }
        else { // Если список не пуст
            last->next = p; // Указываем, что текущий последний элемент ссылается на новый
            last = p;       // Обновляем указатель на последний элемент
        }
    }*/

    void print() {
        Node<T>* p = first;
        while (p->next != nullptr) { //пока список не кончится
            cout << p->value << " ";
            p = p->next;
        }
        cout << p->value; //печать послед.
    }

    Node<T>* getFirst() {
        return first;
    }
    void insertAfter(Node<T>* prevNode, const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (prevNode == nullptr) { // вставка в начало
            newNode->next = first;
            first = newNode;
        }
        else {
            newNode->next = prevNode->next;
            prevNode->next = newNode;
        }
    }
    void deleteNode(Node<T>* prev, Node<T>* curr) {
        if (curr == nullptr) return;
        if (prev == nullptr) {
            first = curr->next;
        }
        else {
            prev->next = curr->next;
        }
        delete curr;
    }


};


class Polynom
{
     //List <Monom> p;

public:
    List<Monom> p;

    List<Monom>& getMonomList() {
        return p;
    }
    Polynom() {}

    Polynom(const string& s) {  //3x1y2z1 + 2x2y2z1
        size_t i = 0;
        while (i < s.length()) {
            size_t start = i;
            while (i < s.length() && (isdigit(s[i]) || s[i] == 'x' || s[i] == 'y' || s[i] == 'z')) {
                i++;
            }
            if (start < i) {
                string monomStr = s.substr(start, i - start);
                Monom monom(monomStr);
                p.Insert(monom);
            }
            if (i < s.length() && (s[i] == '+' || s[i] == ' ')) {
                i++; // пропускаем знак +
            }
        }
    }

    void printPol() {
        p.print();
        cout << endl;
    }

    Polynom operator+(Polynom& other) {   //"3x1y2z1 + 2x2y2z1" + "3x1y2z1 + 2x2y2z3"
        Polynom res = other;
        Node<Monom>* currA = p.getFirst();
        Node<Monom>* prevA = nullptr;
        Node<Monom>* currB = res.p.getFirst();
        Node<Monom>* prevB = nullptr;

        while (currA != nullptr && currB != nullptr){
            if (currA->value < currB->value) {
                res.p.InsertCurr(prevB, currB, currA->value);
                prevA = currA;
                currA = currA->next;
            }
            else if (currB->value < currA->value) {
                prevB = currB;
                currB = currB->next;
            }
            else { // Степени совпадают, нужно сложить их
                currB->value = currB->value + currA->value;
                if (currB->value == 0) {
                    //удалить currB
                    res.p.DeleteCurr(prevB, currB);
                    currB = prevB->next;
                    //передвинуть currA
                    prevA = currA;
                    currA = currA->next;
                }
                else
                {
                    prevA = currA;
                    currA = currA->next;
                    prevB = currB;
                    currB = currB->next;
                }
            }
        }
        // Добавляем оставшиеся мономы, если они есть
        while (currA != nullptr) {
            res.p.InsertCurr(prevB, currB, currA->value);
            currA = currA->next;
            prevB = prevB->next;
        }
        return res;
    }
    
    Polynom operator*(Monom& m) {
        Polynom res;
        Node<Monom>* currentA = p.getFirst();
        while (currentA != nullptr) {
            Monom newMonom = currentA->value * m;
            res.p.Insert(newMonom);
            currentA = currentA->next;
        }
        return res;
    }

    Polynom operator*(Polynom& other) {
        Polynom res;
        Node<Monom>* currentA = p.getFirst();
        while (currentA != nullptr) {
            Polynom newPoly = other * currentA->value;
            res = res + newPoly;
            currentA = currentA->next;
        }
        return res;
    }

    void addMonom(const Monom& m) {
        Node<Monom>* curr = p.getFirst();
        Node<Monom>* prev = nullptr;

        while (curr != nullptr && curr->value < m) {
            prev = curr;
            curr = curr->next;
        }

        // Совпала ли степень
        if (curr != nullptr && curr->value == m) {
            curr->value.coeff += m.coeff;
            if (curr->value.coeff == 0) {
                p.deleteNode(prev, curr);
            }
        }
        else {
            p.insertAfter(prev, m);
        }
    }


    /*Polynom operator*(double scalar) const {
        Polynom res;
        Node<Monom>* current = p.getFirst();
        while (current != nullptr) {
            Monom newMonom = current->value * scalar; 

            res.p.Insert(newMonom);
            current = current->next;
        }
        return res;
    }*/

    //старое сложение полиномов( для неупорядоченного списка)
    /*Polynom operator+(Polynom& other) {  //  "3x1y2z1 + 2x2y2z1" + "3x1y2z1 + 2x2y2z3"
        Polynom res;
        Node<Monom>* currentA = p.getFirst();
        Node<Monom>* currentB = other.p.getFirst();
        // Добавляем все мономы из первого полинома в результат
        while (currentA != nullptr) {
            res.p.Insert(currentA->value);
            currentA = currentA->next;
        }
        while (currentB != nullptr) {
            int flag = 0;
            // Проверяем, сущ ли моном с такими же степенями
            Node<Monom>* resCurrent = res.p.getFirst();
            while (resCurrent != nullptr) {
                if (resCurrent->value.getPowX() == currentB->value.getPowX() &&
                    resCurrent->value.getPowY() == currentB->value.getPowY() &&
                    resCurrent->value.getPowZ() == currentB->value.getPowZ()) {
                    // Если найден, суммируем коэффициенты
                    Monom newMonom = resCurrent->value + currentB->value;
                    if (newMonom.getCoeff() != 0) {
                        resCurrent->value = newMonom; // Обновляем моном в результате
                    }
                    else {
                        //если коэфф стал 0 то удалить этот моном
                        //  ДОПИСАТЬ!!!!
                    }
                    flag = 1;
                    break;
                }
                resCurrent = resCurrent->next;
            }
            // Если моном не был объединен, доб его в результат
            if (flag!=1) {
                res.p.Insert(currentB->value);
            }
            currentB = currentB->next;
        }
        return res;
    }*/
};
