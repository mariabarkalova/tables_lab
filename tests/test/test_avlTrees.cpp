#include"../../tables/include/trees.h"
//#include <gtest.h>
#include"../../tables/gtest/gtest.h"
using namespace TREE;


// test fixture
class tmpAvl : public ::testing::Test {
protected:
    avlTree<int, int> t1;

public:
    tmpAvl() : t1(20) {
        t1.Insert(t1.root, 10);
        t1.Insert(t1.root, 15);
        t1.Insert(t1.root, 5);
        t1.Insert(t1.root, 1);
        t1.Insert(t1.root, 40);
    }
    ~tmpAvl() {}
};

TEST(avlTree, can_create_tree_with_root)
{
    avlTree<int, int> t1(20);
    EXPECT_EQ(20, t1.root->data.first);
}
TEST_F(tmpAvl, can_get_height)
{
    int h = t1.GetHeight(t1.Search(5));
    EXPECT_EQ(1, h);
}
TEST_F(tmpAvl, can_get_succ)
{
    avlNode<int, int>* node = (t1.root)->left; // Node  5
    avlNode<int, int>* successor = t1.Suce(node);
    EXPECT_EQ(10, successor->data.first);
}
TEST_F(tmpAvl, can_get_prev)
{
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
TEST_F(tmpAvl, can_find_node)
{
    avlNode<int, int>* tmp = t1.Search(20);
    EXPECT_EQ(tmp, t1.root->right);
}
TEST_F(tmpAvl, throws_when_node_not_found)
{
    ASSERT_ANY_THROW(t1.Search(2));
}
TEST_F(tmpAvl, can_delete_leaf)
{
    t1.Delete_node(40);
    ASSERT_ANY_THROW(t1.Search(40));
    EXPECT_TRUE(t1.GetBalance(t1.root) <= 1);
}
TEST_F(tmpAvl, can_delete_node_with_one_child)
{
    t1.Delete_node(20);
    //t1.Walk(t1.root);
    ASSERT_ANY_THROW(t1.Search(20));
    EXPECT_TRUE(t1.GetBalance(t1.root) <= 1);
}
TEST_F(tmpAvl, can_delete_root_with_children)
{
    t1.Delete_node(15);
    // t1.Walk(t1.root);
    ASSERT_ANY_THROW(t1.Search(15));
    EXPECT_TRUE(t1.GetBalance(t1.root) <= 1);
    EXPECT_TRUE(20, t1.root->data.first);
}
TEST_F(tmpAvl, can_delete_node_with_balance)
{
    t1.Insert(t1.root, 0);
    t1.Delete_node(5);
    //t1.Walk(t1.root);
    ASSERT_ANY_THROW(t1.Search(5));
    EXPECT_TRUE(t1.GetBalance(t1.root) <= 1);
    EXPECT_TRUE(10, t1.root->left->data.first);
}
TEST_F(tmpAvl, can_delete_node_with_left_rotate)
{
    t1.Insert(t1.root, 17);
    t1.Insert(t1.root, 50);
    t1.Delete_node(17);
   // t1.Walk(t1.root);
    ASSERT_ANY_THROW(t1.Search(17));
    EXPECT_TRUE(t1.GetBalance(t1.root) <= 1);
    EXPECT_TRUE(40, t1.root->right->data.first);
}
TEST_F(tmpAvl, can_delete_node_with_right_rotate)
{
    t1.Insert(t1.root, 0);
    t1.Delete_node(10);
    //t1.Walk(t1.root);
    ASSERT_ANY_THROW(t1.Search(10));
    EXPECT_TRUE(t1.GetBalance(t1.root) <= 1);
    EXPECT_TRUE(1, t1.root->left->data.first);
}

TEST(avlTree, can_delete_root_without_childrens)
{
    avlTree<int, int> t1(10);
    t1.Delete_node(10);
    EXPECT_EQ(1, t1.isEmpty());
}

TEST_F(tmpAvl, throws_when_node_not_found_for_delete)
{
    ASSERT_ANY_THROW(t1.Delete_node(7));
}
TEST_F(tmpAvl, can_insert_node_without_balance_to_left)
{
    t1.Insert(t1.root,0);
    EXPECT_EQ(t1.root->left->left->left, t1.Search(0));
    EXPECT_TRUE(t1.GetBalance(t1.root) <= 1);
}
TEST_F(tmpAvl, can_insert_node_without_balance_to_right)
{
    t1.Insert(t1.root, 50);
    EXPECT_EQ(t1.root->right->right, t1.Search(50));
    EXPECT_TRUE(t1.GetBalance(t1.root) <= 1);
}
TEST_F(tmpAvl, can_insert_node_with_balance_ll)
{
    t1.Insert(t1.root, 0);
    t1.Insert(t1.root, -1);
    //t1.Walk(t1.root);
    EXPECT_EQ(t1.root->left->left->left, t1.Search(-1));
    EXPECT_TRUE(t1.GetBalance(t1.root) <= 1);
}
TEST_F(tmpAvl, can_insert_node_with_balance_rr)
{
    t1.Insert(t1.root, 50);
    t1.Insert(t1.root, 60);
    //t1.Walk(t1.root);
    EXPECT_EQ(t1.root->right->right->right, t1.Search(60));
    EXPECT_TRUE(t1.GetBalance(t1.root) <= 1);
}
TEST_F(tmpAvl, can_insert_node_with_balance_rl)
{
    t1.Insert(t1.root, 35);
   // t1.Walk(t1.root);
    EXPECT_EQ(t1.root->right, t1.Search(35));
    EXPECT_TRUE(t1.GetBalance(t1.root) <= 1);
}
TEST_F(tmpAvl, can_insert_node_with_balance_lr)
{
    t1.Delete_node(40);
    t1.Insert(t1.root, 8);
    //t1.Walk(t1.root);
    EXPECT_EQ(t1.root->left->right, t1.Search(8));
    EXPECT_TRUE(t1.GetBalance(t1.root) <= 1);
}

TEST(avlTree, dont_insert_when_already_have)
{
    avlTree<int, int> t1(10);
    t1.Insert(t1.root, 10);
    EXPECT_EQ(nullptr, t1.root->left);
    EXPECT_EQ(nullptr, t1.root->right);
}
TEST_F(tmpAvl, can_get_max)
{
    EXPECT_EQ(t1.root->right->right, t1.max(t1.root));
}
TEST_F(tmpAvl, can_get_min)
{
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
TEST_F(tmpAvl, can_rotate_right)
{
    t1.RotateRight(t1.root->left);
    //t1.Walk(t1.root);
    EXPECT_EQ(1, t1.root->left->data.first);
    EXPECT_EQ(5, t1.root->left->right->data.first);
    EXPECT_EQ(10, t1.root->left->right->right->data.first);
}
TEST_F(tmpAvl, can_rotate_left)
{
    t1.RotateLeft(t1.root->right);
    //t1.Walk(t1.root);
    EXPECT_EQ(40, t1.root->right->data.first);
    EXPECT_EQ(20, t1.root->right->left->data.first);
}
