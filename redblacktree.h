/** C++ implementation of Red-Black Tree **/
#ifndef RBTREE_H
#define RBTREE_H

#include <bits/stdc++.h>
using namespace std;

enum Color {RED, BLACK};

struct Node
{
int data;
bool color;
Node *left, *right, *parent;
// Constructor
Node(int data)
{
    this->data = data;
    left = right = parent = NULL;
}
};

class RBTree
{
private:
Node *root;

protected:
void rotateLeft(Node *&, Node *&);
void rotateRight(Node *&, Node *&);
void fixViolation(Node *&, Node *&);

public:
// Constructor
RBTree() { root = NULL; }

void insert(const int &n);
void inorder();
void levelOrder();
};

// Utility functions
void inorderHelper(Node root);
Node BSTInsert(Node* root, Node *pt);
void levelOrderHelper(Node *root);

#endif // RBTREE_H