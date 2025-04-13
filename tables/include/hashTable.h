#include<iostream>
#include<vector>
#include<functional>

using namespace std;

template < typename tkey, typename tval>
class HashTable
{
private:
	struct HashEntry
	{
		tkey key; 
		tval value; 
        bool occupied;  // Ячейка занята
        bool deleted; // Ячейка была удалена
	};

	size_t capacity;  // Размер хэш-таблицы
    size_t size;   // Кол-во эл-ов в таблице
	vector<HashEntry>table;
	hash< tkey> hasher;
    //function<size_t(tkey, size_t)> rehasher;
    function<size_t(tkey, size_t, size_t)> rehasher;  // Функция повторного хэширования
    // принимает ключ, номер попытки, и размер таблицы. возвращает новое значение индекса
    
    size_t default_rehash(tkey key, size_t i, size_t cap)  
    {
        return (hasher(key) + i * (1 + hasher(key) % (cap - 1))) % cap;
    }

public:
    /*HashTable(size_t initialCapacity, function<size_t(tkey, size_t, size_t)> rehasher_func)
        : capacity(initialCapacity), size(0), table(initialCapacity), rehasher(rehasher_func) 
    {
        // Инициализируем все ячейки
        for (size_t i = 0; i < capacity; ++i) 
        {
            table[i].occupied = false;
            table[i].deleted = false;
        }
    }*/
    HashTable(size_t initialCapacity): capacity(initialCapacity), size(0), table(initialCapacity),
        rehasher([this](tkey key, size_t i, size_t cap) { return this->default_rehash(key, i, cap); })
    {
        for (size_t i = 0; i < capacity; ++i) 
        {
            table[i].occupied = false;
            table[i].deleted = false;
        }
    }

    bool Insert(const tkey& key, const tval& value) {
        if (size >= capacity) {
            cout << "Хэш-таблица заполнена" << endl;
            return false; 
        }

        size_t num = -1; // Индекс первой удаленной ячейки, если встретится
        size_t ind = hasher(key) % capacity;
        size_t i = 0;

        while (true)
        {
            if (table[ind].occupied && table[ind].key == key)
            {
                cout << "Дублирование ключа" << endl;
                return false;
            }

            if (table[ind].deleted && num == -1)
            {
                num = ind; //сохраняем индекс первой удаленной ячейки
            }

            if (!table[ind].occupied && num == -1)
            {
                //Если ячейка свободна
                table[ind].key = key;
                table[ind].value = value;
                table[ind].occupied = true;
                table[ind].deleted = false;
                size++;
                return true;
            }

            if (!table[ind].occupied && num != -1)
            {
                //Если ячейка свободна, но есть удаленная запись.
                table[num].key = key;
                table[num].value = value;
                table[num].occupied = true;
                table[num].deleted = false;
                size++;
                return true;
            }

            ind = rehasher(key, ++i, capacity) % capacity;
        }

    }

    size_t Find(const tkey& key)
    {
        size_t ind = hasher(key) % capacity;
        size_t initial_ind = ind;
        size_t probes = 0;

        while (probes <= capacity)
        {
            if (table[ind].occupied && table[ind].key == key)
            {
                return ind;
            }

            if (!table[ind].occupied && !table[ind].deleted) //если ячейка не занята и не удалена - такого ключа нет
            {
                return -1;
            }

            ind = rehasher(key, ++probes, capacity) % capacity;
            /*if (probes > capacity) {
                cout << "Error: Reached maximum probes, key not in table (likely)." << endl;
                return -1;
            }*/

            if (ind == initial_ind && probes > 1) {
                return -1; //Прошли всю таблицу
            }
        }
        cout << "Достигнуто максимальное количество проб, ключа нет в таблице(вероятно)." << endl;
        return -1;
    }

    bool Delete(const tkey& key) {
        size_t num = Find(key);
        if (num != -1) {
            table[num].deleted = true;
            table[num].occupied = false; 
            size--;
            return true;
        }
        else
        {
            return false; // такого ключа нет
        }
    }

    void PrintTable() const 
    {
        cout << "Хэш-таблица:" << endl;
        for (size_t i = 0; i < capacity; ++i) 
        {
            cout << "[" << i << "]: ";
            if (table[i].occupied) 
            {
                cout << "Key = " << table[i].key << ", Value = " << table[i].value << ", Occupied = " << table[i].occupied << ", Deleted = " << table[i].deleted << endl;
            }
            else {
                cout << "Empty" << endl;
            }
        }
        cout << "Размер: " << size << "/" << capacity << endl;
    }


};



/*size_t default_rehash(tkey key, size_t i, size_t cap)   // Состояние ячейки (занята, свободна, удалена)
{
    return (hasher(key) + i * (1 + hasher(key) % (cap - 1))) % cap;
}*/