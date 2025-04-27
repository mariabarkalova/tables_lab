#pragma once
#include <iostream>
using namespace std;
#include <sstream>
template <typename TKey, typename TVal>
struct Node {
    Node* left;
    Node* right;
    Node* parent;
    pair <TKey, TVal> data;
    Node(Node< TKey, TVal >* l = nullptr, Node< TKey, TVal >* r = nullptr, Node<TKey, TVal>* p = nullptr, pair <TKey, TVal> d = {}) {
        data = d; left = l; right = r; parent = p;
    }
    Node(const Node<TKey, TVal>& node2) {
        data = node2.data;
        left = node2.left;
        right = node2.right;
        parent = node2.parent;
    }
    Node<TKey, TVal>& operator=(const Node<TKey, TVal>& node2) {
        if (this != &node2) {
            data = node2.data;
            left = node2.left;
            right = node2.right;
            parent = node2.parent;
        }
        return *this;
    }
    bool operator==(const Node<TKey, TVal>& node2) const {
        return (data == node2.data);
    }
    bool operator!=(const Node<TKey, TVal>& node2) const {
        return (data != node2.data);
    }
};


template <typename TKey, typename TVal>
struct avlNode : public Node<TKey, TVal> {
    int height;
    avlNode* left;
    avlNode* right;
    avlNode* parent;
    avlNode(avlNode< TKey, TVal >* l = nullptr, avlNode< TKey, TVal >* r = nullptr, avlNode<TKey, TVal>* p = nullptr, pair <TKey, TVal> d = {}, int h = 0) {
        data = d; left = l; right = r; parent = p; height = h;
    }
    avlNode(const avlNode<TKey, TVal>& node2) {
        data = node2.data;
        left = node2.left;
        right = node2.right;
        parent = node2.parent;
        height = node2.height;
    }
};

template <typename TKey, typename TVal, typename NodeType = Node<TKey,TVal>>
class Tree {
public:
    NodeType* root;
    Tree() : root(nullptr) {}
    Tree(const TKey& k) { root = new NodeType(); root->data.first = k; };
    ~Tree()
    {
        Delete_tree(root);
    }
    NodeType* Search(const TKey& k)
    {
        if (isEmpty()) {
            throw ("Tree is empty");
        }
        // èùåì çâåíî
        NodeType* curr = root;
        NodeType* par = nullptr;
        while (curr && curr->data.first != k) {
            par = curr;
            if (k < curr->data.first) {
                curr = (curr->left);
            }
            else {
                curr = (curr->right);
            }
        }
        // íå íàøëè
        if (!curr) {
            throw ("Node not found");
        }
        return curr;
    }
    void SetValue(const TKey& k, const TVal& v)
    {
        NodeType* curr = Search(k);
        curr->data.second = v;
    }
    virtual void Walk(NodeType* r)
    {
        if (r!=nullptr) {
            if (r->left)
                Walk(r->left);
            cout << "Key:" << r->data.first;
            if (r->data.second)
                cout << ", value:" << r->data.second;
            if (r->right)
                cout << ", right:" << r->right->data.first;
            if (r->left)
                cout << ", left:" << r->left->data.first;
            if (r->parent)
                cout << ", parent:" << r->parent->data.first;
            cout << "\n";
            if (r->right)
                Walk(r->right);
        }
        else
            throw ("Tree is empty");
    }
    virtual NodeType* Insert(NodeType* tmp, const TKey& k) {
        if (isEmpty()) {
            tmp = new NodeType();
            tmp->data.first = k;
            root = tmp;
            return tmp;
        }
        else {
            if (tmp->data.first == k) {
                return tmp; //óæå åñòü
            }
            if (k < tmp->data.first) {
                if (tmp->left == nullptr) {
                    tmp->left = new NodeType();
                    tmp->left->parent = tmp;
                    tmp->left->data.first = k;
                }
                else {
                    Insert(tmp->left, k);
                }
            }
            else {
                if (tmp->right == nullptr) {
                    tmp->right = new NodeType();
                    tmp->right->parent = tmp;
                    tmp->right->data.first = k;
                }
                else {
                    Insert((tmp->right), k);
                }
            }
            return tmp;
        }
    }
    NodeType* Suce(NodeType* x)
    {
        if (x->right != nullptr)
            return min(x->right);
        else {
            NodeType* tmp = x->parent;
            while (tmp->data.first < x->data.first)
            {
                x = tmp; tmp = x->parent;
            }
            return tmp;
        }
    }
    NodeType* Prev(NodeType* x) {
        if (x->left) {
            return max(x->left);
        }

        NodeType* current = x;
        NodeType* parent = current->parent;

        // Ïðîõîä ââåðõ ïî äåðåâó, ïîêà òåêóùèé óçåë íå îêàæåòñÿ ïðàâûì ðåáåíêîì
        while (parent && current == parent->left) {
            current = parent;
            parent = current->parent;
        }

        return parent;
    }
    bool isEmpty() const { return root == nullptr; };
    virtual void Delete_node(const TKey& k)
    {
        if (isEmpty()) {
            throw ("Tree is empty");
        }
        // èùåì çâåíî
        NodeType* curr = Search(k);
        NodeType* par = curr->parent;
        
        // íåò ïîòîìêîâ 
        if (!curr->left && !curr->right) {
            if (curr == root) {
                root = nullptr;
            }
            else if (par->left == curr) {
                par->left = nullptr;
            }
            else {
                par->right = nullptr;
            }
            delete curr;
        }
        // 1 ïîòîìîê
        else if (!curr->left || !curr->right) {
            NodeType* child = (curr->left) ? (curr->left) : (curr->right);

            if (curr == root) {
                root = child; // åñëè óäàëÿåì êîðåíü - îáíîâëÿåì åãî
            }
            else if (par->left == curr) {
                par->left = child;
            }
            else {
                par->right = child;
            }
            delete curr;
        }
        // 2 ïîòîìêà
        else {
            // íàèìåíüøèé ñïðàâà
            NodeType* succ = (curr->right);
            NodeType* succPar = curr;

            while (succ->left) {
                succPar = succ;
                succ = (succ->left);
            }
            curr->data.first = succ->data.first;
            // óäàëÿåì successor 
            if (succPar->left == succ) {
                succPar->left = succ->right;
            }
            else {
                succPar->right = succ->right;
            }
            delete succ;
        }
    }
    virtual int GetHeight(NodeType* r) {
        if (r) {
            if (!(r->left) && !(r->right))
                return 0;
            int lg = 0, rg = 0;
            if (r->left)
                lg = GetHeight((r->left));
            else lg = 0;
            if (r->right)
                rg = GetHeight((r->right));
            else rg = 0;
            int k = std::max(lg, rg) + 1;
            return k;
        }
        else
            return 0;
    }
    NodeType* min(NodeType* x) {
        while (x->left) {
            x = x->left;
        }
        return x;
    }
    NodeType* max(NodeType* x) {
        while (x->right) {
            x = x->right;
        }
        return x;
    }
    protected:
        void Delete_tree(NodeType* tmp)
        {
            if (tmp)
            {
                Delete_tree((tmp->left));
                Delete_tree((tmp->right));
                delete tmp;
            }
        }
};

template <typename TKey, typename TVal>
class avlTree : public Tree<TKey, TVal, avlNode<TKey, TVal>> {
public:
    using NodeType = avlNode<TKey, TVal>;
    avlTree() : root(nullptr) {}
    avlTree(const TKey& k) {
        this->root = new NodeType();
        this->root->data.first = k;
    }
    bool isEmpty() const { return root == nullptr; };
    NodeType* Insert(NodeType* tmp, const TKey& k) override {
        if (tmp == nullptr) {  // Åñëè äåðåâî ïóñòîå èëè äîøëè äî ìåñòà âñòàâêè
            NodeType* newNode = new NodeType();
            newNode->data.first = k;
            return newNode;
        }
        if (k < tmp->data.first) {
            tmp->left = Insert(tmp->left, k);
            tmp->left->parent = tmp;
        }
        else if (k > tmp->data.first) {
            tmp->right = Insert(tmp->right, k);
            tmp->right->parent = tmp;
        }
        else {
            return tmp; // Óçåë óæå ñóùåñòâóåò
        }
        UpdateHeight(tmp);
        return Balance(tmp); // Áàëàíñèðóåì òåêóùèé óçåë
    }

    void Delete_node(const TKey& k) override {
        if (this->isEmpty()) {
            throw ("Tree is empty");
        }

        NodeType* curr = Search(k);
        NodeType* par = curr->parent;

        // ó óçëà íåò ïîòîìêîâ
        if (!curr->left && !curr->right) {
            if (curr == this->root) {
                this->root = nullptr;
            }
            else if (par->left == curr) {
                par->left = nullptr;
            }
            else {
                par->right = nullptr;
            }
            delete curr;
        }
        //îäèí ïîòîìîê
        else if (!curr->left || !curr->right) {
            NodeType* child = (curr->left) ? (curr->left) : (curr->right);
            if (curr == this->root) {
                this->root = child;
            }
            else if (par->left == curr) {
                par->left = child;
            }
            else {
                par->right = child;
            }
            if (child) {
                child->parent = par; // Îáíîâëÿåì ðîäèòåëÿ ïîòîìêà
            }
            delete curr;
        }
        //äâà ïîòîìêà
        else {
            // Íàõîäèì íàèìåíüøèé óçåë â ïðàâîì ïîääåðåâå (successor)
            NodeType* succ = (curr->right);
            NodeType* succPar = curr;

            while (succ->left) {
                succPar = succ;
                succ = (succ->left);
            }
            // Êîïèðóåì äàííûå èç successor â òåêóùèé óçåë
            curr->data = succ->data;
            // Óäàëÿåì successor
            if (succPar->left == succ) {
                succPar->left = (succ->right);
            }
            else {
                succPar->right = (succ->right);
            }

            if (succ->right) {
                (succ->right)->parent = succPar; // Îáíîâëÿåì ðîäèòåëÿ ïðàâîãî ïîääåðåâà successor
            }
            delete succ;
        }
        while (par != nullptr) {
            UpdateHeight(par);
            par = Balance(par); 
            par = par->parent;
        }
    }
    NodeType* RotateLeft(NodeType* node) {
        NodeType* right = (node->right);
        node->right = right->left;
        if (node->right != nullptr) {
            node->right->parent = node;
        }
        right->parent = node->parent;
        if (node->parent == nullptr) {
            this->root = right;
        }
        else if (node == node->parent->left) {
            node->parent->left = right;
        }
        else {
            node->parent->right = right;
        }
        right->left = node;
        node->parent = right;
        UpdateHeight(node);
        UpdateHeight(right);
        return right;
    }
    NodeType* RotateRight(NodeType* node) {
        NodeType* left = (node->left);
        node->left = left->right;
        if (node->left != nullptr) {
            node->left->parent = node;
        }
        left->parent = node->parent;
        if (node->parent == nullptr) {
            this->root = left;
        }
        else if (node == node->parent->right) {
            node->parent->right = left;
        }
        else {
            node->parent->left = left;
        }
        left->right = node;
        node->parent = left;
        UpdateHeight(node);
        UpdateHeight(left);
        return left;
    }
    NodeType* Balance(NodeType* node) {
        if (node == nullptr) {
            return nullptr;
        }
        UpdateHeight(node);
        int balance = GetBalance(node);
        // Ëåâûé òÿæåëûé
        if (balance > 1) {
            if (GetBalance((node->left)) >= 0) {
                return RotateRight(node);
            }
            else {
                node->left = RotateLeft((node->left));
                return RotateRight(node);
            }
        }
        // Ïðàâûé òÿæåëûé
        if (balance < -1) {
            if (GetBalance((node->right)) <= 0) {
                return RotateLeft(node);
            }
            else {
                node->right = RotateRight((node->right));
                return RotateLeft(node);
            }
        }
        return node;
    }
    void UpdateHeight(NodeType* node) {
        if (node == nullptr) {
            return;
        }
        int leftHeight = (node->left == nullptr) ? -1 : (node->left)->height;
        int rightHeight = (node->right == nullptr) ? -1 : (node->right)->height;
        node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
    int GetBalance(NodeType* node) {
        if (node == nullptr) {
            return 0;
        }
        return GetHeight((node->left)) - GetHeight((node->right));
    }
    int GetHeight(NodeType* node)  override {
        return node == nullptr ? -1 : node->height;
    }
    virtual void Walk(NodeType* r) override
    {
        if (r != nullptr) {
            if (r->left)
                Walk(r->left);
            cout << "Key:" << r->data.first;
            cout << ", height:" << r->height;
            if (r->data.second)
                cout << ", value:" << r->data.second;
            if (r->right)
                cout << ", right:" << r->right->data.first;
            if (r->left)
                cout << ", left:" << r->left->data.first;
            if (r->parent)
                cout << ", parent:" << r->parent->data.first;
            cout << "\n";
            if (r->right)
                Walk(r->right);
        }
        else
            throw ("Tree is empty");
    }
};
