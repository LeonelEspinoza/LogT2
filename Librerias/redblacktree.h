/** C++ implementation of Red-Black Tree **/
#ifndef RBTREE_H
#define RBTREE_H

#include <bits/stdc++.h>
using namespace std;

enum Color {RED, BLACK};

struct Node
{
unsigned int data;
bool color;
Node *left, *right, *parent;
// Constructor
Node(unsigned int data)
{
    this->data = data;
    left = right = parent = NULL;
}
};

class RBTree
{
public:
Node *root;

protected:
void rotateLeft(Node *&, Node *&);
void rotateRight(Node *&, Node *&);
void fixViolation(Node *&, Node *&);

public:
// Constructor
RBTree() { root = NULL; }

void insert(const unsigned int &n);
void inorder();//para printear el arbol
void levelOrder();
};
Node *searchRBT(Node *root, unsigned int key);

// Utility functions
void inorderHelper(Node root); 

Node BSTInsert(Node* root, Node *pt);
void levelOrderHelper(Node *root);

// Clean
void cleanRBT(Node *root);

#endif // RBTREE_H