//#include "trees.h"
//#include <gtest.h>
#include"../../tables/include/trees.h"
#include"../../tables/gtest/gtest.h"

TEST(Tree, can_create_tree_with_root)
{
    Tree<int, int> t1(10);
    EXPECT_EQ(10, t1.root->data.first);
}
TEST(Tree, can_create_empty_tree)
{
    Tree<int, int> t1;
    EXPECT_TRUE(t1.isEmpty());
}
TEST(Tree, can_get_height)
{
    Tree<int, int> t1(10);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 3);
    t1.Insert(t1.root, 7);
    t1.Insert(t1.root, 12);
    int h = t1.GetHeight(t1.Search(15));
    EXPECT_EQ(1, h);
}
TEST(Tree, can_get_succ)
{
   Tree<int, int> t1(10);
   t1.Insert(t1.root, 5);
   t1.Insert(t1.root, 15);
   t1.Insert(t1.root, 3);
   t1.Insert(t1.root, 7);
   t1.Insert(t1.root, 12);
   Node<int, int>* node = t1.root->left; // Node  5
   Node<int, int>* successor = t1.Suce(node);
   EXPECT_EQ(7, successor->data.first);
}
TEST(Tree, can_get_prev)
{
    Tree<int, int> t1(10);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 3);
    t1.Insert(t1.root, 7);
    t1.Insert(t1.root, 12);
    Node<int, int>* node = t1.root->right;// Node  15
    Node<int, int>* previous = t1.Prev(node);
    EXPECT_EQ(12, previous->data.first);
}
TEST(Tree, can_set_value)
{
    Tree<int, int> t1(10);
    t1.SetValue(10, 1);
    EXPECT_EQ(1, t1.root->data.second);
}
TEST(Tree, can_find_node)
{
    Tree<int, int> t1(10);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 3);
    t1.Insert(t1.root, 7);
    t1.Insert(t1.root, 12);
    Node<int, int>* tmp = t1.Search(15);
    EXPECT_EQ(tmp, t1.root->right);
}
TEST(Tree, throws_when_node_not_found)
{
    Tree<int,int> t1(10);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 3);
    t1.Insert(t1.root, 7);
    t1.Insert(t1.root, 12);
    ASSERT_ANY_THROW(t1.Search(1));
}
TEST(Tree, throws_when_search_in_empty_tree)
{
    Tree<int, int> t1;
    ASSERT_ANY_THROW(t1.Search(1));
}
TEST(Tree, can_delete_node)
{
    Tree<int, int> t1(10);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 3);
    t1.Insert(t1.root, 7);
    t1.Insert(t1.root, 12);
    t1.Delete_node(5);
    ASSERT_ANY_THROW(t1.Search(5));
}
TEST(Tree, can_delete_root_with_childrens)
{
    Tree<int, int> t1(10);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 3);
    t1.Delete_node(10);
    ASSERT_ANY_THROW(t1.Search(10));
}
TEST(Tree, can_delete_root_without_childrens)
{
    Tree<int, int> t1(10);
    t1.Delete_node(10);
    EXPECT_EQ(1, t1.isEmpty());
}
TEST(Tree, throws_when_node_not_found_for_delete)
{
    Tree<int, int> t1(10);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 15);
    ASSERT_ANY_THROW(t1.Delete_node(7));
}
TEST(Tree, throws_when_delete_in_empty_tree)
{
    Tree<int, int> t1;
    ASSERT_ANY_THROW(t1.Delete_node(1));
}
TEST(Tree, throws_when_walk_in_empty_tree)
{
    Tree<int, int> t1;
    ASSERT_ANY_THROW(t1.Walk(t1.root));
}
TEST(Tree, can_insert_node)
{
    Tree<int, int> t1(10);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 15);
    EXPECT_EQ(t1.root->left,t1.Search(5));
}
TEST(Tree, can_insert_if_empty)
{
    Tree<int, int> t1;
    t1.Insert(t1.root, 10);
   // t1.Walk(t1.root);
    EXPECT_EQ(t1.root, t1.Search(10));
}
TEST(Tree, dont_insert_when_already_have)
{
    Tree<int, int> t1(10);
    t1.Insert(t1.root, 10);
    EXPECT_EQ(nullptr, t1.root->left);
    EXPECT_EQ(nullptr, t1.root->right);
}
TEST(Tree, can_get_max)
{
    Tree<int, int> t1(10);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 3);
    t1.Insert(t1.root, 7);
    t1.Insert(t1.root, 12);
    EXPECT_EQ(t1.root->right,t1.max(t1.root));
}
TEST(Tree, can_get_min)
{
    Tree<int, int> t1(10);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 3);
    t1.Insert(t1.root, 7);
    t1.Insert(t1.root, 12);
    EXPECT_EQ(t1.root->left->left, t1.min(t1.root));
}