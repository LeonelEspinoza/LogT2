#include <iostream> // Para printear
#include <chrono>   // Para medir el tiempo 
#include <math.h>   // Para pow (potencias)
#include <algorithm> //Para lograr
#include <random>   // garantizar que el arreglo sea aleatorio
using namespace std;

void main_splay(int n){
    int *A = new int[n];
    //Se llena el arreglo con los numeros del 1 al n
    iota(A, A + n, 1);
    //Se permuta el arreglo de manera aleatoria
    shuffle(A, A + n, mt19937{random_device{}()});    
    free(A);
}

void main_rbtree(int n){
    int *A = new int[n];
    //Se llena el arreglo con los numeros del 1 al n
    iota(A, A + n, 1);
    //Se permuta el arreglo de manera aleatoria
    shuffle(A, A + n, mt19937{random_device{}()});  
    free(A);
}

int main(){
    //Testeamos 10 veces para el n dado
    for(int i=0; i<5; i++){
        for (int j=16; j<25; j++){
            main_splay(j);
            main_rbtree(j);
        }
    }
            
}