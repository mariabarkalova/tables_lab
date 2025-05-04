#include "../include/trees.h"
#include <iostream>
/*
using namespace std;
using namespace TREE;

int main()
{
    Tree<int, int> t1(10);
    t1.Insert(t1.root, 5);
    t1.Insert(t1.root, 15);
    t1.Insert(t1.root, 3);
    t1.Insert(t1.root, 7);
    t1.Insert(t1.root, 12);
    cout << "Tree t1:" << "\n";
    t1.Walk(t1.root);
    cout << "\n";

    Node<int, int>* node = t1.root->left; // Node  5
    Node<int, int>* successor = t1.Suce(node);
    if (successor) {
        cout << "Successor of " << node->data.first << " is " << successor->data.first << "\n";
    }
    else {
        cout << "No successor found for " << node->data.first << "\n";
    }
    node = t1.root->right; // Node  15
    Node<int, int>* predecessor = t1.Prev(node);
    if (predecessor) {
        cout << "Predecessor of " << node->data.first << " is " << predecessor->data.first << "\n";
    }
    else {
        cout << "No predecessor found for " << node->data.first << "\n";
    }
    cout << "Is the tree empty? " << (t1.isEmpty() ? "Yes" : "No") << "\n";
    t1.Delete_node(10);
    t1.SetValue(3, 100);
    cout << "Tree t1 with changes:" << "\n";
    t1.Walk(t1.root);
    cout << "\n";
    avlTree<int, int> t2(20);
    t2.Insert(t2.root, 10);
    t2.Insert(t2.root, 15);
    t2.Insert(t2.root, 5);
    t2.Insert(t2.root, 1);
    t2.Insert(t2.root, 40);
    //t2.Insert(t2.root, 50);
    cout << "AvlTree t2:" << "\n";
    t2.Walk(t2.root);
    cout << "\n";
    t2.Delete_node(40);
    t2.Delete_node(20);
    cout << "AvlTree t2 with changes:" << "\n";
    t2.Walk(t2.root);
    cout << "\n";
    Tree<int, int> t3;
    t3.Insert(t3.root, 10);
    t3.Walk(t3.root);

    return 0;
}
*/