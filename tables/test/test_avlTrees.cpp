#include "trees.h"
#include <gtest.h>

TEST(avlTree, can_create_tree_with_root)
{
    avlTree<int, int> t1(20);
    EXPECT_EQ(20, t1.root->data.first);
}
TEST(avlTree, can_get_height)
{
    avlTree<int, int> t1(20);
    t1.Insert(t1.root, 10);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 1);
    t1.Insert(t1.root, 40);
    int h = t1.GetHeight(t1.Search(5));
    EXPECT_EQ(1, h);
}
TEST(avlTree, can_get_succ)
{
    avlTree<int, int> t1(20);
    t1.Insert(t1.root, 10);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 1);
    t1.Insert(t1.root, 40);
    avlNode<int, int>* node = (t1.root)->left; // Node  5
    avlNode<int, int>* successor = t1.Suce(node);
    EXPECT_EQ(10, successor->data.first);
}
TEST(avlTree, can_get_prev)
{
    avlTree<int, int> t1(20);
    t1.Insert(t1.root, 10);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 1);
    t1.Insert(t1.root, 40);
    avlNode<int, int>* node = t1.root->right;// Node  20
    avlNode<int, int>* previous = t1.Prev(node);
    EXPECT_EQ(15, previous->data.first);
}
TEST(avlTree, can_set_value)
{
    avlTree<int, int> t1(10);
    t1.SetValue(10, 1);
    EXPECT_EQ(1, t1.root->data.second);
}
TEST(avlTree, can_find_node)
{
    avlTree<int, int> t1(20);
    t1.Insert(t1.root, 10);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 1);
    t1.Insert(t1.root, 40);
    avlNode<int, int>* tmp = t1.Search(15);
    EXPECT_EQ(tmp, t1.root->right->left);
}
TEST(avlTree, throws_when_node_not_found)
{
    avlTree<int, int> t1(20);
    t1.Insert(t1.root, 10);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 1);
    t1.Insert(t1.root, 40);
    ASSERT_ANY_THROW(t1.Search(2));
}
TEST(avlTree, can_delete_node_with_balance)
{
    avlTree<int, int> t1(20);
    t1.Insert(t1.root, 10);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 1);
    t1.Insert(t1.root, 40);
    t1.Delete_node(1);
    ASSERT_ANY_THROW(t1.Search(1));
    EXPECT_TRUE(abs(t1.GetBalance(t1.root->left) - t1.GetBalance(t1.root->right)) <= 1);
}
TEST(avlTree, can_delete_root_with_childrens)
{
    avlTree<int, int> t1(20);
    t1.Insert(t1.root, 10);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 1);
    t1.Insert(t1.root, 40);
    //t1.Walk(t1.root);
    t1.Delete_node(10);
    //t1.Walk(t1.root);
    ASSERT_ANY_THROW(t1.Search(10));
    EXPECT_TRUE(abs(t1.GetBalance(t1.root->left) - t1.GetBalance(t1.root->right)) <= 1);
}
TEST(avlTree, can_delete_root_without_childrens)
{
    avlTree<int, int> t1(10);
    t1.Delete_node(10);
    EXPECT_EQ(1, t1.isEmpty());
}
TEST(avlTree, throws_when_node_not_found_for_delete)
{
    avlTree<int, int> t1(20);
    t1.Insert(t1.root, 10);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 1);
    t1.Insert(t1.root, 40);
    ASSERT_ANY_THROW(t1.Delete_node(7));
}
TEST(avlTree, can_insert_node_with_balance)
{
    avlTree<int, int> t1(20);
    t1.Insert(t1.root, 10);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 1);
    t1.Insert(t1.root, 40);
    EXPECT_EQ(t1.root->left, t1.Search(5));
    EXPECT_TRUE(abs(t1.GetBalance(t1.root->left) - t1.GetBalance(t1.root->right)) <= 1);
}
TEST(avlTree, dont_insert_when_already_have)
{
    avlTree<int, int> t1(10);
    t1.Insert(t1.root, 10);
    EXPECT_EQ(nullptr, t1.root->left);
    EXPECT_EQ(nullptr, t1.root->right);
}
TEST(avlTree, can_get_max)
{
    avlTree<int, int> t1(20);
    t1.Insert(t1.root, 10);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 1);
    t1.Insert(t1.root, 40);
    EXPECT_EQ(t1.root->right->right, t1.max(t1.root));
}
TEST(avlTree, can_get_min)
{
    avlTree<int, int> t1(20);
    t1.Insert(t1.root, 10);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 1);
    t1.Insert(t1.root, 40);
    EXPECT_EQ(t1.root->left->left, t1.min(t1.root));
}
TEST(avlTree, can_update_height)
{
    avlTree<int, int> t1(20);
    t1.Insert(t1.root, 10);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 5);
    int h1 = t1.Search(5)->height;
    t1.Insert(t1.root, 1);
    t1.Insert(t1.root, 40);
    int h2 = t1.Search(5)->height;
    EXPECT_NE(h1, h2);
}
TEST(avlTree, can_rotate_right)
{
    avlTree<int, int> t1(20);
    t1.Insert(t1.root, 10);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 1);
    t1.Insert(t1.root, 40);
    //t1.Walk(t1.root);
    t1.RotateRight(t1.root->right);
    //t1.Walk(t1.root);
    EXPECT_EQ(15, t1.root->right->data.first);
    EXPECT_EQ(20, t1.root->right->right->data.first);
    EXPECT_EQ(40, t1.root->right->right->right->data.first);
}
TEST(avlTree, can_rotate_left)
{
    avlTree<int, int> t1(20);
    t1.Insert(t1.root, 10);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 1);
    t1.Insert(t1.root, 40);
    //t1.Walk(t1.root);
    t1.RotateLeft(t1.root->right);
    //t1.Walk(t1.root);
    EXPECT_EQ(40, t1.root->right->data.first);
    EXPECT_EQ(20, t1.root->right->left->data.first);
    EXPECT_EQ(15, t1.root->right->left->left->data.first);
}