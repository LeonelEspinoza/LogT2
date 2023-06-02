#include <iostream> // Para printear
#include <chrono>   // Para medir el tiempo 
#include <math.h>   // Para pow (potencias)
#include <algorithm> //Para lograr
#include <random>   // garantizar que el arreglo sea aleatorio
#include <redblacktree.h>
#include <splaytree.h>

using namespace std;

static const int m=pow(2,28);

int f(int i, int alpha){
    int res = (int) pow(i,alpha);
    return res;
}

int SUM(int alpha, int n){
    int SUM=0;
    for(int i=1;i<=n;i++){
        SUM+=f(i,alpha);
    }
    return SUM;
}

int phi(int i, int alpha, int n){
    int res=(f(i,alpha)*m)/SUM(alpha,n);
    return res;
}

void main_splay(int exp_n){
    int n = pow(2, exp_n); //Tamaño del arreglo N de los elementos que se insertarán en el árbol
    int *pi = new int[n];
    int *N = new int[n];

    //Crear tres arreglos de tamaño M
    int *C1 = new int[m];
    int *C2 = new int[m];
    int *C3 = new int[m];

    int* arreglos[3] = {C1,C2,C3};

    //Se llena el arreglo N con los numeros del 1 al n
    iota(N, N + n, 1);

    //Se permuta el arreglo N de manera aleatoria
    shuffle(N, N + n, mt19937{random_device{}()});

    //Se llena el arreglo pi con los numeros del 1 al n
    iota(pi, pi + n, 1);

    //Se permuta el arreglo pi de manera aleatoria
    shuffle(pi, pi + n, mt19937{random_device{}()});

    //Un arreglo de los valores que debe tomar alpha
    int alphas[3]={0.5,1,1.5};

    for(int i=0; i<3; i++) {
        //Se setea el apha correspondiente
        int alpha=(int) alphas[i];

        //Se setea el SUM correspondiente
        int suma = SUM(alpha,n);

        //Puntero a la ubicación de C a escribir 
            int ptr=0;

        //Para cada elemento de la permutacion
        for(int j=0; j<n; j++){
            //Lo escribimos phi(i) veces en C
            for(int p=phi(i, alpha, n); p>0; p--){
                //Escribimos en C
                arreglos[i][ptr]=pi[i];
                //Aumentamos el puntero
                ptr++;
            }
        }
    }

    //Se desordenan los arreglos
    shuffle(C1, C1 + m, mt19937{random_device{}()});
    shuffle(C2, C2 + m, mt19937{random_device{}()});
    shuffle(C3, C3 + m, mt19937{random_device{}()});

    //Se crea el arbol
    node *root = insert(NULL, 1);
    for(int i=0; i<n; i++){
        root = insert(root, N[i]);
    }

    //Se libera la memoria de N
    delete[] N;

    //Se inicia el cronometro
    auto inicio = chrono::high_resolution_clock::now();

    //Se busca cada elemento del arreglo C1 en el árbol
    for(int i=0; i<m; i++){
        search(root, C1[i]);
    }

    //Se finaliza el cronometro
    auto fin = chrono::high_resolution_clock::now();

    //Se calcula el tiempo transcurrido
    auto duracionC1 = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();

    //Se libera la memoria de C1
    delete[] C1;

    //Se inicia el cronometro
    auto inicio = chrono::high_resolution_clock::now();

    //Se busca cada elemento del arreglo C2 en el árbol
    for(int i=0; i<m; i++){
        search(root, C2[i]);
    }

    //Se finaliza el cronometro
    auto fin = chrono::high_resolution_clock::now();

    //Se calcula el tiempo transcurrido
    auto duracionC2 = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();

    //Se libera la memoria de C2
    delete[] C2;

    //Se inicia el cronometro
    auto inicio = chrono::high_resolution_clock::now();

    //Se busca cada elemento del arreglo C3 en el árbol
    for(int i=0; i<m; i++){
        search(root, C3[i]);
    }

    //Se finaliza el cronometro
    auto fin = chrono::high_resolution_clock::now();

    //Se calcula el tiempo transcurrido
    auto duracionC3 = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();

    //Se libera la memoria de C3
    delete[] C3;
}

void main_RBTree(int exp_n){
    int n = pow(2, exp_n); //Tamaño del arreglo N de los elementos que se insertarán en el árbol

    //Crear tres arreglos de tamaño M
    int C1[m];
    int C2[m];
    int C3[m];
}

int main(){
    //para N desde 2**16 hasta 2**24
    for(int exp_n=16;exp_n<=24;exp_n++){

        //para cada arreglo:
        for(int a=0;a<3;a++){
            int *C=arreglos[a];
            //seteamos el alpha correspondiente
            alpha=alphas[a];
            //seteamos el SUM correspondiente
            SetSUM();
            //puntero a la ubicación de C a escribir 
            int ptr=0;

            //para cada elemento de la permutacion
            for(int i=0;i<N;i++){
                //lo escribimos phi(i) veces en C
                for(int p=phi(i);p>0;p--){
                    //Escribimos en C
                    C[ptr]=pi[i];
                    //aumentamos el puntero
                    ptr++;
                }
            }
            //reodenar el arreglo
            shuffle(C, C + M, mt19937{random_device{}()});
        }
    }
    return 0;
}