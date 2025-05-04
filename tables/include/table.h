#include<iostream>
#include<string>
#include <cctype>
#include <sstream>
#include<vector>
#include"../../polinom/include/polinom.h"
using namespace std;

template < typename tkey, typename tval>
class TableBase {
protected:
    void* Memory;
    int nRec; //число факт. записей
public:
    virtual void Insert(tkey& k, tval& val) = 0; //нужна или нет ссылка???
    virtual void Delete(tkey& k) = 0;
    virtual tval* Search(tkey& k) = 0;
    virtual void PrintAll() const = 0;
    virtual ~TableBase() {}
    TableBase() : nRec(0), Memory(nullptr) {}
};

template <typename tkey, typename tval>
class ListTable : public TableBase<tkey, tval>
{
    struct Node
    {
        tkey key; 
        tval value; 
        Node* next; // указатель на следующий узел
        Node(tkey k, tval v, Node* p) : key(k), value(v), next(p) {}
    };
    Node* first; //first ук-ль на первое звено
    Node* last;
    size_t _size;
public:
    ListTable() : first(nullptr) {}

    ~ListTable() {
        while (first != nullptr) {
            Node* temp = first;
            first = first->next;
            delete temp;
        }
    }

    void InsertCurr(Node* prev, Node* curr, tkey key, tval value) 
    {
        Node* p = new Node(key, value, nullptr);
        if (first == nullptr) 
        {  // Если список пуст
            first = p;
            last = p;
            return;
        }
        // Если добавляется в начало
        if (prev == nullptr) 
        {
            p->next = first;
            first = p;
            return;
        }
        // Если добавляется в конец
        if (curr == nullptr) 
        {
            p->next = nullptr;
            last->next = p;
            last = p;
            return;
        }
        // Вставка между prev и curr
        prev->next = p;
        p->next = curr;
    }

    void DeleteCurr(Node* prev, Node* curr) 
    {
        Node* p;
        if (first == last) 
        {  // Если список пуст
            delete curr;
            first = last = nullptr;
            return;
        }
        // Если удаляется первый
        if (prev == nullptr) 
        {
            p = first;
            first = first->next;
            delete p;
            return;
        }
        // удаление любого другого
        if (curr != nullptr) 
        {
            p = curr;
            prev->next = curr->next;
            delete p;
            return;
        }
    }

    // методы для поиска и удаления по ключу
    void Insert(tkey& k, tval& val) override 
    {
        Node* curr = first;
        Node* prev = nullptr;
        while (curr != nullptr && curr->key < k) 
        {
            prev = curr;
            curr = curr->next;
        }
        InsertCurr(prev, curr, k, val);
    }

    void Delete(tkey& k) override 
    {
        Node* curr = first;
        Node* prev = nullptr;
        while (curr != nullptr && curr->key != k) 
        { //находим нам нужный узел для удаления
            prev = curr;
            curr = curr->next;
        }
        if (curr != nullptr) 
        {
            DeleteCurr(prev, curr);
        }
    }

    tval* Search(tkey& k) override {  //tval*: Метод возвращает указатель на значение типа tval
        Node* curr = first;
        while (curr != nullptr) 
        {
            if (curr->key == k) 
            {
                return &(curr->value);
            }
            curr = curr->next;
        }
        return nullptr; // Не найдено
    }

    void PrintAll() const
    { // Метод для печати всей таблицы
        Node* curr = first;
        while (curr != nullptr)
        {
            cout << "Ключ: " << curr->key << ", Значение: ";
            curr->value.printPol();
            curr = curr->next;
        }
    }
    size_t size() const { return _size; }

    bool isEmpty() const { return _size == 0; }
    /*
    // Конструктор копирования
    ListTable(const ListTable<tkey, tval>& other) : first(nullptr), last(nullptr) {
        Node* current = other.first;
        while (current != nullptr) {
            Insert(current->key, current->value);
            current = current->next;
        }
    }

    ListTable<tkey, tval>& operator=(const ListTable<tkey, tval>& other) {
        if (this != &other) { // Проверяем самоприсваивание
            // Освобождаем память текущего списка
            while (first != nullptr) {
                Node* temp = first;
                first = first->next;
                delete temp;
            }
            //указатели для нового списка
            first = nullptr;
            last = nullptr;
            // Копируем элементы из другого списка
            Node* current = other.first;
            while (current != nullptr) {
                this->Insert(current->key, current->value);
                current = current->next;
            }
        }
        return *this;
    }

    void print() {
        Node* p = first;
        while (p->next != nullptr) { //пока список не кончится
            cout << p->value << " ";
            p = p->next;
        }
        cout << p->value; //печать послед.
    }

    Node* getFirst() 
    {
        return first;
    }
    */
};


//там таблица на массиве
/*template < typename tkey, typename tval>
class ArrayTable : public TableBase<tkey, tval> 
{
    vector<pair<tkey, tval>>array;
    int nReserved; //сколько памяти выделено
public:
    ArrayTable(int size) : TableBase(), nReserved(size) 
    {
        array.reserve(size); // Резервируем память
    }

    virtual ~ArrayTable() = default; // Используем default для деструктора

    void Insert(tkey& k, tval& val)  
    {
        if (nRec < nReserved) {
            array.emplace_back( k, val);
            nRec++;
        }
        else {
            cerr << "Таблица заполнена!" << endl;
        }
    }

    tval* Search(tkey& key)  //tval*: Метод возвращает указатель на значение типа tval
    {    
            //auto позволяет компилятору самостоятельно определить тип переменной на основе ее инициализации
        //&k: Это лямбда-функция, которая прини
        // мает pair и проверяет, равен ли первый элемент пары (ключ) искомому ключу k. Лямбда захватывает k по ссылке, что позволяет использовать его внутри функции.
 //       auto it = find_if(array.begin(), array.end(), [&k](const pair<tkey, tval>& pair) {  //можно ли просто написать key
//            return pair.first == k; });
//        if (it != array.end()) {
//            return &it->second;
 //       }

 //       auto x = find(array.begin(), array.end(), key);
 //       if (x != array.end()) {
 //           return &x->second;
 //       }
 
        int i;
        for (i = 0;i < array.size();i++)
        {
            if (array[i].first == key)
                break;
        }
        if (i < array.size())
        {
            return &array[i].second;
        }
        return nullptr; // Если ключ не найден
    }

    void Delete(tkey& key) 
    { 
        int i;
        for (i = 0;i < array.size();i++)
        {
            if (array[i].first == key)
                break;
        }
        if (i < array.size())
        {
            swap(array[i], array[array.size() - 1]);
            array.pop_back();
            nRec--;
        }
        //    не работает функция find без какой то доп функции сравнения
        //auto x = find(array.begin(), array.end(), key);
        //if (x != array.end()) {
         //   swap(*x, array.back());
         //  array.pop_back();
         //   nRec--;
        //}
        //else {
          //  cerr << "Ключ не найден!" << endl;
        //}
    }
};*/






