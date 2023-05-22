#include <iostream>
using namespace std;

struct Node
{
    Node *left, *right, *parent;
    int key;
};

Node* newNode(int key)
{
    Node* node = new Node;
    node->key = key;
    node->left = node->right = node->parent = nullptr;
    return node;
}

void rightRotate(Node *&root, Node *x)
{
    Node* y = x->left;
    x->left = y->right;
    if (y->right != nullptr)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void leftRotate(Node *&root, Node *x)
{
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void Splay(Node *&root, Node *x)
{
    while (x->parent != nullptr)
    {
        if (x->parent->parent == nullptr)
        {
            if (x == x->parent->left)
                rightRotate(root, x->parent);
            else
                leftRotate(root, x->parent);
        }
        else if (x == x->parent->left && x->parent == x->parent->parent->left)
        {
            rightRotate(root, x->parent->parent);
            rightRotate(root, x->parent);
        }
        else if (x == x->parent->right && x->parent == x->parent->parent->right)
        {
            leftRotate(root, x->parent->parent);
            leftRotate(root, x->parent);
        }
        else if (x == x->parent->right && x->parent == x->parent->parent->left)
        {
            leftRotate(root, x->parent);
            rightRotate(root, x->parent);
        }
        else
        {
            rightRotate(root, x->parent);
            leftRotate(root, x->parent);
        }
    }
}

Node* search(Node* &root, int key)
{
    Node* x = root;
    Node* last = nullptr;
    while (x != nullptr)
    {
        if (x->key == key)
        {
            Splay(root, x);
            return x;
        }
        last = x;
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    Splay(root, last);
    return nullptr;
}

void insert(Node* &root, int key)
{
    if (root == nullptr)
    {
        root = newNode(key);
        return;
    }
    if (search(root, key) != nullptr)
        return;
    Node* temp = root;
    Node* parent = nullptr;
    while (temp != nullptr)
    {
        parent = temp;
        if (key < temp->key)
            temp = temp->left;
        else
            temp = temp->right;
    }
    temp = newNode(key);
    temp->parent = parent;
    if (key < parent->key)
        parent->left = temp;
    else
        parent->right = temp;
    Splay(root, temp);
}

void deleteNode(Node* &root, int key)
{
    if (root == nullptr || search(root, key) == nullptr)
        return;
    Node* temp = root;
    if (root->left == nullptr)
    {
        root = root->right;
    }
    else
    {
        temp = root->left;
        while (temp->right != nullptr)
            temp = temp->right;
        root = root->left;
        Splay(root, temp);
        root->right = temp->right;
    }
    delete temp;
    return;
}

int main()
{
    Node *root = nullptr;
    insert(root, 100);
    insert(root, 50);
    insert(root, 200);
    insert(root, 40);
    insert(root, 30);
    insert(root, 20);
    cout<<"After Insert: "<<root->key<<endl;
    deleteNode(root, 50);
    cout<<"After Delete: "<<root->key<<endl;
    Node *temp = search(root, 200);
    cout<<"After Search: "<<root->key<<endl;
    return 0;
}