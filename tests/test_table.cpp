#include"../tables/include/table.h"
#include"test/gtest.h"
#include"../polinom/include/polinom.h"
#include"../tables/include/hashTable.h"

TEST(ListTable, Insert_And_Search) 
{
    ListTable<string, Polynom> table;
    Polynom poly1("3x1y2z1+2x2y2z1");
    Polynom poly2("3x1y2z1+2x2y2z3");
    string key1 = "poly1";
    string key2 = "poly2";
    table.Insert(key1, poly1);
    table.Insert(key2, poly2);
    Polynom* result1 = table.Search(key1);
    Polynom* result2 = table.Search(key2);
    ASSERT_NE(nullptr, result1);
    ASSERT_NE(nullptr, result2);
}

TEST(ListTable, Delete) 
{
    ListTable<string, Polynom> table;
    Polynom poly1("3x1y2z1+2x2y2z1");
    Polynom poly2("3x1y2z1+2x2y2z3");
    string key1 = "poly1";
    string key2 = "poly2";
    table.Insert(key1, poly1);
    table.Insert(key2, poly2);
    table.Delete(key2);
    Polynom* result1 = table.Search(key1); 
    Polynom* result2 = table.Search(key2);
    ASSERT_NE(nullptr, result1); 
    ASSERT_EQ(nullptr, result2);
}

TEST(ListTable, Empty_Table) 
{
    ListTable<string, Polynom> table;
    string key = "poly1";
    Polynom* result = table.Search(key);
    ASSERT_EQ(nullptr, result);
}

TEST(ListTable, Insert_Existing_Key) 
{
    ListTable<string, Polynom> table;
    Polynom poly1("3x1y2z1+2x2y2z1");
    Polynom poly2("5x0y0+1x1y1");
    string key1 = "poly1";
    table.Insert(key1, poly1);
    table.Insert(key1, poly2); // Заменяем poly1 на poly2
    Polynom* result = table.Search(key1);
    ASSERT_NE(nullptr, result);  // Элемент с ключом poly1 должен существовать
}

TEST(ListTable, Insert_And_Delete) 
{
    ListTable<string, Polynom> table;
    Polynom poly1("3x1y2z1+2x2y2z1");
    string key1 = "poly1";
    table.Insert(key1, poly1);
    table.Delete(key1);
    Polynom* result = table.Search(key1);
    ASSERT_EQ(nullptr, result); //таблица должна быть пустой
}

TEST(ListTable, IsEmpty_OnCreation) //таблица пуста при создании
{
    ListTable<string, Polynom> table;
    ASSERT_TRUE(table.isEmpty());
}




TEST(HashTable, Insert_And_Search) {
    HashTable<string, Polynom> table(10);
    Polynom poly1("3x1y2z1+2x2y2z1");
    string key1 = "poly1";
    ASSERT_TRUE(table.Insert(key1, poly1));
    Polynom* result = table.Search(key1);
    ASSERT_NE(nullptr, result);
}

TEST(HashTable, Delete) {
    HashTable<string, Polynom> table(10);
    Polynom poly1("3x1y2z1+2x2y2z1");
    string key1 = "poly1";
    table.Insert(key1, poly1);
    ASSERT_TRUE(table.Delete(key1));
    ASSERT_EQ(table.Search(key1), nullptr);
    ASSERT_EQ(table.get_size(), 0); //размер уменьшился
}
//поиск несуществующего элемента
TEST(HashTable, Search_Non_Existing) {
    HashTable<string, Polynom> table(10);
    string key1 = "poly1";
    ASSERT_EQ(table.Search(key1), nullptr);
}

TEST(HashTable, Multiple_Insert) {
    HashTable<string, Polynom> table(10);
    Polynom poly1("3x1y2z1+2x2y2z1");
    Polynom poly2("5x0y0+1x1y1");
    string key1 = "poly1";
    string key2 = "poly2";
    ASSERT_TRUE(table.Insert(key1, poly1));
    ASSERT_TRUE(table.Insert(key2, poly2));
    ASSERT_NE(table.Search(key1), nullptr);
    ASSERT_NE(table.Search(key2), nullptr);
    ASSERT_EQ(table.get_size(), 2);
}

TEST(HashTable, Table_Overflow) //переполнение
{
    HashTable<int, int> table(2);
    ASSERT_TRUE(table.Insert(1, 10));
    ASSERT_TRUE(table.Insert(2, 20));
    ASSERT_FALSE(table.Insert(3, 30));
    ASSERT_EQ(table.get_size(), 2);
}

TEST(HashTable, Delete_Non_Existing) //удаления несуществующего элемента
{
    HashTable<string, Polynom> table(10);
    string key1 = "poly1";
    ASSERT_FALSE(table.Delete(key1));
    ASSERT_EQ(table.get_size(), 0);
}

TEST(HashTable, Collision_Test) {
    HashTable<int, string> table(5);
    ASSERT_TRUE(table.Insert(0, "Value0"));
    ASSERT_TRUE(table.Insert(5, "Value5")); // Коллизия с ключом 0
    ASSERT_TRUE(table.Insert(10, "Value10")); // Коллизия с ключом 0 и 5
    ASSERT_NE(table.Search(0), nullptr);
    ASSERT_NE(table.Search(5), nullptr);
    ASSERT_NE(table.Search(10), nullptr);
}