#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>

class node {
public:
    unsigned int key;
    node* left;
    node* right;
};

node* newNode(unsigned int key);
node* rightRotate(node* x);
node* leftRotate(node* x);
node* splay(node* root, unsigned int key);
node* search(node* root, unsigned int key);
node* insert(node* root, unsigned int k);
void preOrder(node* root);

//Clean el arbol
void cleanSplay(node *root);

#endif /* SPLAYTREE_H */
