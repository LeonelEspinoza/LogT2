#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>

class node {
public:
    int key;
    node* left;
    node* right;
};

node* newNode(int key);
node* rightRotate(node* x);
node* leftRotate(node* x);
node* splay(node* root, int key);
node* search(node* root, int key);
node* insert(node* root, int k);
void preOrder(node* root);

//Clean el arbol
void cleanSplay(node *root);

#endif /* SPLAYTREE_H */
