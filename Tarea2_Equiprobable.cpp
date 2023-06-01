#include <iostream> // Para printear
#include <chrono>   // Para medir el tiempo 
#include <math.h>   // Para pow (potencias)
#include <algorithm> //Para lograr
#include <random>   // garantizar que el arreglo sea aleatorio
#include "redblacktree.h"

using namespace std;

void main_splay(int n){
    
}

void main_rbtree(int n){
    int *A = new int[n];
    //Se llena el arreglo con los numeros del 1 al n
    iota(A, A + n, 1);
    //Se permuta el arreglo de manera aleatoria
    shuffle(A, A + n, mt19937{random_device{}()});    
    RBTree tree;
    for (int i = 0; i < n; i++){
        tree.insert(i+1);
    }
    for (int i = 0; i < n; i++){
        searchRBT(tree.root, i+1);}

    free(A);
}

int main(){
    //Testeamos 10 veces para el n dado
    for(int i=0; i<5; i++){
        int n = pow(2,i);
        for (int j=16; j<25; j++){

            main_splay(n);
            main_rbtree(n);
            ;
        }
    }
    return 0;
}