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
    int nRec; //����� ����. �������
public:
    virtual void Insert(tkey& k, tval& val) = 0; //����� ��� ��� ������???
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
        Node* next; // ��������� �� ��������� ����
        Node(tkey k, tval v, Node* p) : key(k), value(v), next(p) {}
    };
    Node* first; //first ��-�� �� ������ �����
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
        {  // ���� ������ ����
            first = p;
            last = p;
            return;
        }
        // ���� ����������� � ������
        if (prev == nullptr) 
        {
            p->next = first;
            first = p;
            return;
        }
        // ���� ����������� � �����
        if (curr == nullptr) 
        {
            p->next = nullptr;
            last->next = p;
            last = p;
            return;
        }
        // ������� ����� prev � curr
        prev->next = p;
        p->next = curr;
    }

    void DeleteCurr(Node* prev, Node* curr) 
    {
        Node* p;
        if (first == last) 
        {  // ���� ������ ����
            delete curr;
            first = last = nullptr;
            return;
        }
        // ���� ��������� ������
        if (prev == nullptr) 
        {
            p = first;
            first = first->next;
            delete p;
            return;
        }
        // �������� ������ �������
        if (curr != nullptr) 
        {
            p = curr;
            prev->next = curr->next;
            delete p;
            return;
        }
    }

    // ������ ��� ������ � �������� �� �����
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
        { //������� ��� ������ ���� ��� ��������
            prev = curr;
            curr = curr->next;
        }
        if (curr != nullptr) 
        {
            DeleteCurr(prev, curr);
        }
    }

    tval* Search(tkey& k) override {  //tval*: ����� ���������� ��������� �� �������� ���� tval
        Node* curr = first;
        while (curr != nullptr) 
        {
            if (curr->key == k) 
            {
                return &(curr->value);
            }
            curr = curr->next;
        }
        return nullptr; // �� �������
    }

    void PrintAll() const
    { // ����� ��� ������ ���� �������
        Node* curr = first;
        while (curr != nullptr)
        {
            cout << "����: " << curr->key << ", ��������: ";
            curr->value.printPol();
            curr = curr->next;
        }
    }
    size_t size() const { return _size; }

    bool isEmpty() const { return _size == 0; }
    /*
    // ����������� �����������
    ListTable(const ListTable<tkey, tval>& other) : first(nullptr), last(nullptr) {
        Node* current = other.first;
        while (current != nullptr) {
            Insert(current->key, current->value);
            current = current->next;
        }
    }

    ListTable<tkey, tval>& operator=(const ListTable<tkey, tval>& other) {
        if (this != &other) { // ��������� ����������������
            // ����������� ������ �������� ������
            while (first != nullptr) {
                Node* temp = first;
                first = first->next;
                delete temp;
            }
            //��������� ��� ������ ������
            first = nullptr;
            last = nullptr;
            // �������� �������� �� ������� ������
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
        while (p->next != nullptr) { //���� ������ �� ��������
            cout << p->value << " ";
            p = p->next;
        }
        cout << p->value; //������ ������.
    }

    Node* getFirst() 
    {
        return first;
    }
    */
};


//��� ������� �� �������
/*template < typename tkey, typename tval>
class ArrayTable : public TableBase<tkey, tval> 
{
    vector<pair<tkey, tval>>array;
    int nReserved; //������� ������ ��������
public:
    ArrayTable(int size) : TableBase(), nReserved(size) 
    {
        array.reserve(size); // ����������� ������
    }

    virtual ~ArrayTable() = default; // ���������� default ��� �����������

    void Insert(tkey& k, tval& val)  
    {
        if (nRec < nReserved) {
            array.emplace_back( k, val);
            nRec++;
        }
        else {
            cerr << "������� ���������!" << endl;
        }
    }

    tval* Search(tkey& key)  //tval*: ����� ���������� ��������� �� �������� ���� tval
    {    
            //auto ��������� ����������� �������������� ���������� ��� ���������� �� ������ �� �������������
        //&k: ��� ������-�������, ������� �����
        // ���� pair � ���������, ����� �� ������ ������� ���� (����) �������� ����� k. ������ ����������� k �� ������, ��� ��������� ������������ ��� ������ �������.
 //       auto it = find_if(array.begin(), array.end(), [&k](const pair<tkey, tval>& pair) {  //����� �� ������ �������� key
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
        return nullptr; // ���� ���� �� ������
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
        //    �� �������� ������� find ��� ����� �� ��� ������� ���������
        //auto x = find(array.begin(), array.end(), key);
        //if (x != array.end()) {
         //   swap(*x, array.back());
         //  array.pop_back();
         //   nRec--;
        //}
        //else {
          //  cerr << "���� �� ������!" << endl;
        //}
    }
};*/






