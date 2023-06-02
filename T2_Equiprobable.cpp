#include <iostream> // Para printear
#include <chrono>   // Para medir el tiempo 
#include <math.h>   // Para pow (potencias)
#include <algorithm> //Para lograr
#include <random>   // garantizar que el arreglo sea aleatorio
#include <redblacktree.h>
#include <splaytree.h>

static const int m = pow(2,28); //Tamaño del arreglo de la secuencia de búsqueda M
using namespace std;

void main_splay(int exp_n){
    int n = pow(2, exp_n); //Tamaño del arreglo N de los elementos que se insertarán en el árbol
    int *N = new int[n];
    int *M = new int[m];

    //Se llena el arreglo N con los numeros del 1 al n
    iota(N, N + n, 1);

    //Se permuta el arreglo N de manera aleatoria
    shuffle(N, N + n, mt19937{random_device{}()});   

    //Se llena el arreglo M con los numeros del 1 al n, repitiendose 2^28/n veces cada número
    int repeticiones_n = pow(2, 28-exp_n);
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
    for(int i=0; i<n; i++){
        root = insert(root, N[i]);
    }

    //Se libera la memoria de N
    delete[] N;

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

    //Se libera la memoria de M
    delete[] M;

    //Se guarda el resultado en el arreglo de resultados
    //res[j] = int(duracion);

    printf("Caso SplayTree:\n");
    printf("La busqueda tardo %ld milisegundos en ejecutarse.\n", duracion);

    /*
    Por ahora sin txt para que veamos si funciona
    //Se abre el archivo donde se guardarán los tiempos
    FILE *f = fopen("resultados.txt", "a"); //append

    //Se escribe el numero del test
    fprintf(f, "Test %d:\n", j+1);

    //Se escribe el tiempo en el archivo
    fprintf(f, "La búsqueda tardó %ld milisegundos en ejecutarse.\n\n", duracion);

    //Se cierra el archivo
    fclose(f);*/
}

void main_RBTree(int exp_n){
    int n = pow(2, exp_n); //Tamaño del arreglo de los elementos que se insertarán en el árbol
    int *N = new int[n];
    int *M = new int[m];

    //Se llena el arreglo N con los numeros del 1 al n
    iota(N, N + n, 1);

    //Se permuta el arreglo N de manera aleatoria
    shuffle(N, N + n, mt19937{random_device{}()});    

    //Se llena el arreglo M con los numeros del 1 al n, repitiendose 2^28/n veces cada número
    int repeticiones_n = pow(2, 28-exp_n);
    int puntero = 0;
    for(int i=1; i<=n; i++){
        for(int j=0; j<repeticiones_n; j++){
            M[puntero++] = i;
        }
    }

    //Se permuta el arreglo M de manera aleatoria
    shuffle(M, M + m, mt19937{random_device{}()});

    //Se crea el arbol
    RBTree tree;
    for (int i=0; i<n; i++){
        tree.insert(N[i]);
    }

    //Se libera la memoria de N
    delete[] N;

    //Se inicia el cronometro
    auto inicio = chrono::high_resolution_clock::now();

    //Se busca cada elemento del arreglo M en el arbol
    for(int i=0; i<m; i++){
        searchRBT(tree.root, M[i]);
    }
    
    //Se finaliza el cronometro
    auto fin = chrono::high_resolution_clock::now();
    
    //Se libera la memoria de M
    delete[] M;
    
    //Se calcula el tiempo transcurrido
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();

    //Se printea
    printf("Caso RBTree:\n");
    cout << "La busqueda tardu " << duracion << " milisegundos en ejecutarse." << endl;
}

int main(){
    //Testeamos 5 veces para el n dado indica 2^n
    int n;
    for(int i=16; i<25; i++){
        n=i;
        printf("Para n = %d:\n", n);
        for (int j=0; j<5; j++){
            printf("Test %d:\n", j+1);
            main_RBTree(n);
            main_splay(n);
        }
    }
    return 0;
}
