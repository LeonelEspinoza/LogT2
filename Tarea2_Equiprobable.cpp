#include <iostream> // Para printear
#include <chrono>   // Para medir el tiempo 
#include <math.h>   // Para pow (potencias)
#include <algorithm> //Para lograr
#include <random>   // garantizar que el arreglo sea aleatorio
#include "redblacktree.h"
#include "splaytree.h"

using namespace std;

void main_splay(int exp_n, int res[], int j){
    int m = pow(2,28);
    int n = pow(2, exp_n);
    int *M = new int[m];
    int repeticiones_n = pow(2, 28 - exp_n);
    
    //Se llena el arreglo con los numeros del 1 al n, repitiendose 2^28/n veces
    int puntero = 0;
    for(int i=1; i<=n; i++){
        for(int j=0; j<repeticiones_n; j++){
            M[puntero++] = i;
        }
    }
    //Se permuta el arreglo M de manera aleatoria
    shuffle(M, M + m, mt19937{random_device{}()});

    //Se crea el arbol
    node *root = insert(NULL, 1);
    for(int i=2; i<=n; i++){
        root=insert(root, i);
    }
    //Se inicia el cronometro
    auto inicio = chrono::high_resolution_clock::now();

    //Se busca cada elemento del arreglo M en el arbol
    for(int i=0; i<m; i++){
        search(root, M[i]);
    }

    //Se finaliza el cronometro
    auto fin = chrono::high_resolution_clock::now();

    //Se calcula el tiempo transcurrido
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();

    //Se guarda el resultado en el arreglo de resultados
    res[j] = int(duracion);

    //Se abre el archivo donde se guardarán los tiempos
    FILE *f = fopen("resultados.txt", "a"); //append

    //Se escribe el numero del test
    fprintf(f, "Test %d:\n", j+1);

    //Se escribe el tiempo en el archivo
    fprintf(f, "La búsqueda tardó %ld milisegundos en ejecutarse.\n\n", duracion);

    //Se cierra el archivo
    fclose(f);

    //Se libera la memoria
    delete[] M;
}

void main_rbtree(int exp_n){
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