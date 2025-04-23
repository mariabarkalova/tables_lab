#include"../tables/include/table.h"
#include"test/gtest.h"
#include"../polinom/include/polinom.h"
/*
class MyValue {
public:
    int value;

    MyValue() : value(0) {}
    MyValue(int val) : value(val) {}

    void printPol() const {
        std::cout << value << std::endl;
    }

    bool operator==(const MyValue& other) const {
        return value == other.value;
    }
};

TEST(ListTableTest, InsertAndSearch) {
    ListTable<int, MyValue> table;
    MyValue val1(10);
    MyValue val2(20);

    table.Insert(1, val1);
    table.Insert(2, val2);

    MyValue* result1 = table.Search(1);
    MyValue* result2 = table.Search(2);
    MyValue* result3 = table.Search(3);

    ASSERT_NE(nullptr, result1);
    ASSERT_EQ(val1, *result1);

    ASSERT_NE(nullptr, result2);
    ASSERT_EQ(val2, *result2);

    ASSERT_EQ(nullptr, result3); // Should return nullptr if not found
}


TEST(ListTableTest, Delete) {
    ListTable<int, MyValue> table;
    MyValue val1(10);
    MyValue val2(20);
    MyValue val3(30);

    table.Insert(1, val1);
    table.Insert(2, val2);
    table.Insert(3, val3);

    table.Delete(2);

    MyValue* result1 = table.Search(1);
    MyValue* result2 = table.Search(2); // Should be deleted
    MyValue* result3 = table.Search(3);

    ASSERT_NE(nullptr, result1);
    ASSERT_EQ(nullptr, result2);
    ASSERT_NE(nullptr, result3);
}


TEST(ListTableTest, InsertAtBeginning) {
    ListTable<int, MyValue> table;
    MyValue val1(10);
    MyValue val2(20);

    table.Insert(2, val2);
    table.Insert(1, val1); // Inserts at the beginning

    MyValue* result1 = table.Search(1);
    MyValue* result2 = table.Search(2);

    ASSERT_NE(nullptr, result1);
    ASSERT_EQ(val1, *result1);

    ASSERT_NE(nullptr, result2);
    ASSERT_EQ(val2, *result2);
}

TEST(ListTableTest, InsertAtEnd) {
    ListTable<int, MyValue> table;
    MyValue val1(10);
    MyValue val2(20);

    table.Insert(1, val1);
    table.Insert(2, val2); // Inserts at the end

    MyValue* result1 = table.Search(1);
    MyValue* result2 = table.Search(2);

    ASSERT_NE(nullptr, result1);
    ASSERT_EQ(val1, *result1);

    ASSERT_NE(nullptr, result2);
    ASSERT_EQ(val2, *result2);
}

TEST(ListTableTest, DeleteFirstElement) {
    ListTable<int, MyValue> table;
    MyValue val1(10);
    MyValue val2(20);

    table.Insert(1, val1);
    table.Insert(2, val2);

    table.Delete(1);

    MyValue* result1 = table.Search(1);
    MyValue* result2 = table.Search(2);

    ASSERT_EQ(nullptr, result1);
    ASSERT_NE(nullptr, result2);
}

TEST(ListTableTest, DeleteLastElement) {
    ListTable<int, MyValue> table;
    MyValue val1(10);
    MyValue val2(20);

    table.Insert(1, val1);
    table.Insert(2, val2);

    table.Delete(2);

    MyValue* result1 = table.Search(1);
    MyValue* result2 = table.Search(2);

    ASSERT_NE(nullptr, result1);
    ASSERT_EQ(nullptr, result2);
}

TEST(ListTableTest, DeleteOnlyElement) {
    ListTable<int, MyValue> table;
    MyValue val1(10);

    table.Insert(1, val1);
    table.Delete(1);

    MyValue* result1 = table.Search(1);

    ASSERT_EQ(nullptr, result1);
}

TEST(ListTableTest, DeleteNonExistentElement) {
    ListTable<int, MyValue> table;
    MyValue val1(10);

    table.Insert(1, val1);
    table.Delete(2); // Delete a non-existent element

    MyValue* result1 = table.Search(1);

    ASSERT_NE(nullptr, result1); // Check that the existing element is still there.
}

TEST(ListTableTest, EmptyTable) {
    ListTable<int, MyValue> table;
    MyValue* result = table.Search(1);
    ASSERT_EQ(nullptr, result);
}*/

/*
TEST(ListTable, InsertAndSearch)  //вставка и поиск
{ 
    ListTable<int, int> table;
    int key1 = 1; 
    int val1 = 10; 
    int key2 = 2;
    int val2 = 20;
    int key3 = NULL;
    table.Insert(key1, val1);
    table.Insert(key2, val2);

    int* result1 = table.Search(key1);
    int* result2 = table.Search(key2);
    int* result3 = table.Search(key3); // Ищем элемент с ключом 3 (которого нет)

    ASSERT_NE(nullptr, result1);  // Проверяем, что элемент с ключом 1 найден
    ASSERT_EQ(10, *result1);  // Проверяем, что значение элемента с ключом 1 равно 10

    ASSERT_NE(nullptr, result2);
    ASSERT_EQ(20, *result2);

    ASSERT_EQ(nullptr, result3);
}*/




/*
TEST(ListTable, InsertAndSearch) {
    ListTable<string, Polynom> table;
    string key;
    Polynom poly1("3x1y2z1 + 2x2y2z1");
    string key1 = "poly1";
    Polynom poly2("3x1y2z1 + 2x2y2z3");
    string key2 = "poly2";
    string key3 = nullptr;
    table.Insert(key1, poly1);
    table.Insert(key2, poly2);

    Polynom* result1 = table.Search(key1);
    Polynom* result2 = table.Search(key2);
    Polynom* result3 = table.Search(key3);

    ASSERT_NE(nullptr, result1);
    ASSERT_EQ(poly1, *result1);

    ASSERT_NE(nullptr, result2);
    ASSERT_EQ(poly2, *result2);

    ASSERT_EQ(nullptr, result3);
}

TEST(ListTable, Delete)
{
    ListTable<string, Polynom> table;
    string key;
    Polynom poly1("3x1y2z1 + 2x2y2z1");
    string key1 = "poly1";
    Polynom poly2("3x1y2z1 + 2x2y2z3");
    string key2 = "poly2";
    table.Insert(key1, poly1);
    table.Insert(key2, poly2);

    Polynom* result1 = table.Search(key1);
    Polynom* result2 = table.Search(key2);

    table.Delete(key2);

    result1 = table.Search(key1);
    result2 = table.Search(key2);
    //int* result3 = table.Search(key3);

    ASSERT_NE(nullptr, result1);
    ASSERT_EQ(nullptr, result2); //элемент с ключом 2 не найден(удален)
    //ASSERT_NE(nullptr, result3);
}
*/



/*
TEST(ListTableTest, InsertAtBeginning) {
    ListTable<int, MyValue> table;
    MyValue val1(10);
    MyValue val2(20);

    table.Insert(2, val2);
    table.Insert(1, val1); // Inserts at the beginning

    MyValue* result1 = table.Search(1);
    MyValue* result2 = table.Search(2);

    ASSERT_NE(nullptr, result1);
    ASSERT_EQ(val1, *result1);

    ASSERT_NE(nullptr, result2);
    ASSERT_EQ(val2, *result2);
}

TEST(ListTableTest, InsertAtEnd) {
    ListTable<int, MyValue> table;
    MyValue val1(10);
    MyValue val2(20);

    table.Insert(1, val1);
    table.Insert(2, val2); // Inserts at the end

    MyValue* result1 = table.Search(1);
    MyValue* result2 = table.Search(2);

    ASSERT_NE(nullptr, result1);
    ASSERT_EQ(val1, *result1);

    ASSERT_NE(nullptr, result2);
    ASSERT_EQ(val2, *result2);
}

TEST(ListTableTest, DeleteFirstElement) {
    ListTable<int, MyValue> table;
    MyValue val1(10);
    MyValue val2(20);

    table.Insert(1, val1);
    table.Insert(2, val2);

    table.Delete(1);

    MyValue* result1 = table.Search(1);
    MyValue* result2 = table.Search(2);

    ASSERT_EQ(nullptr, result1);
    ASSERT_NE(nullptr, result2);
}

TEST(ListTableTest, DeleteLastElement) {
    ListTable<int, MyValue> table;
    MyValue val1(10);
    MyValue val2(20);

    table.Insert(1, val1);
    table.Insert(2, val2);

    table.Delete(2);

    MyValue* result1 = table.Search(1);
    MyValue* result2 = table.Search(2);

    ASSERT_NE(nullptr, result1);
    ASSERT_EQ(nullptr, result2);
}

TEST(ListTableTest, DeleteOnlyElement) {
    ListTable<int, MyValue> table;
    MyValue val1(10);

    table.Insert(1, val1);
    table.Delete(1);

    MyValue* result1 = table.Search(1);

    ASSERT_EQ(nullptr, result1);
}

TEST(ListTableTest, DeleteNonExistentElement) {
    ListTable<int, MyValue> table;
    MyValue val1(10);

    table.Insert(1, val1);
    table.Delete(2); // Delete a non-existent element

    MyValue* result1 = table.Search(1);

    ASSERT_NE(nullptr, result1); // Check that the existing element is still there.
}

TEST(ListTableTest, EmptyTable) {
    ListTable<int, MyValue> table;
    MyValue* result = table.Search(1);
    ASSERT_EQ(nullptr, result);
}
*/