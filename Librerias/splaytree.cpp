//Splay tree code
#include <bits/stdc++.h>
using namespace std;
 
// An AVL tree node
class node
{
    public:
    unsigned int key;
    node *left, *right;
};
 
/* Helper function that allocates
a new node with the given key and
    NULL left and right pointers. */
node* newNode(unsigned int key)
{
    node* Node = new node();
    Node->key = key;
    Node->left = Node->right = NULL;
    return (Node);
}
 
// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
node *rightRotate(node *x)
{
    node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}
 
// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
node *leftRotate(node *x)
{
    node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}
 
// This function brings the key at
// root if key is present in tree.
// If key is not present, then it
// brings the last accessed item at
// root. This function modifies the
// tree and returns the new root
node *splay(node *root, unsigned int key)
{
    // Base cases: root is NULL or
    // key is present at root
    if (root == NULL || root->key == key)
        return root;
 
    // Key lies in left subtree
    if (root->key > key)
    {
        // Key is not in tree, we are done
        if (root->left == NULL) return NULL;
 
        // Zig-Zig (Left Left)
        if (root->left->key > key)
        {
            // First recursively bring the
            // key as root of left-left
            root->left->left = splay(root->left->left, key);
 
            // Do first rotation for root,
            // second rotation is done after else
            root = rightRotate(root);
        }
        else if (root->left->key < key) // Zig-Zag (Left Right)
        {
            // First recursively bring
            // the key as root of left-right
            root->left->right = splay(root->left->right, key);
 
            // Do first rotation for root->left
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
 
        // Do second rotation for root
        return (root->left == NULL)? root: rightRotate(root);
    }
    else // Key lies in right subtree
    {
        // Key is not in tree, we are done
        if (root->right == NULL) return NULL;
 
        // Zig-Zag (Right Left)
        if (root->right->key > key)
        {
            // Bring the key as root of right-left
            root->right->left = splay(root->right->left, key);
 
            // Do first rotation for root->right
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (root->right->key < key)// Zag-Zag (Right Right)
        {
            // Bring the key as root of
            // right-right and do first rotation
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
 
        // Do second rotation for root
        return (root->right == NULL)? root: leftRotate(root);
    }
}

// The search function for Splay tree.
// Note that this function returns the
// new root of Splay Tree. If key is
// present in tree then, it is moved to root.
node *search(node *root, unsigned int key)
{
    return splay(root, key);
}

// Function to insert a new key k
// in splay tree with given root
node *insert(node *root, unsigned int k)
{
    // Simple Case: If tree is empty
    if (root == NULL) return newNode(k);
 
    // Bring the closest leaf node to root
    root = splay(root, k);
 
    // If key is already present, then return
    if (root->key == k) return root;
 
    // Otherwise allocate memory for new node
    node *newnode = newNode(k);
 
    // If root's key is greater, make
    // root as right child of newnode
    // and copy the left child of root to newnode
    if (root->key > k)
    {
        newnode->right = root;
        newnode->left = root->left;
        root->left = NULL;
    }
 
    // If root's key is smaller, make
    // root as left child of newnode
    // and copy the right child of root to newnode
    else
    {
        newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
    }
 
    return newnode; // newnode becomes new root
}
 
// A utility function to print
// preorder traversal of the tree.
// The function also prints height of every node
void preOrder(node *root)
{
    if (root != NULL)
    {
        cout<<root->key<<" ";
        preOrder(root->left);
        preOrder(root->right);
    }
}


//Clean el arbol
void cleanSplay(node *root){
    if(root != NULL){
        cleanSplay(root->left);
        cleanSplay(root->right);
        delete root;
    }
}

/* Driver code*/

// int main()
// {
//     node *root = insert(NULL, 100);
//     unsigned int *A = new unsigned int[5];
//     A[0] = 50;
//     A[1] = 200;
//     A[2] = 20;
//     A[3] = 40;
//     A[4] = 150;
//     root=insert(root, A[0]);
//     root=insert(root, A[1]);
//     root=insert(root, A[2]);
//     root=insert(root, A[3]);
//     root=insert(root, A[4]);
//     node *ola=search(root, 40);
//     cout<<"Preorder traversal of the modified Splay tree is \n";
//     preOrder(root);
//     cout<<"\nbuscado: \n";
//     preOrder(ola);
//     return 0;
// }
 
// This code is contributed by rathbhupendra