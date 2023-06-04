#include <iostream> // Para printear
#include <chrono>   // Para medir el tiempo 
#include <math.h>   // Para pow (potencias)
#include <algorithm> //Para lograr
#include <random>   // garantizar que el arreglo sea aleatorio
#include <redblacktree.h>
#include <splaytree.h>

static const unsigned int m = pow(2,28); //Tamaño del arreglo de la secuencia de búsqueda M
using namespace std;
unsigned int n_test=3;

void main_splay(unsigned int exp_n, unsigned int j, float resultados_splay[]){
    unsigned int n = pow(2, exp_n); //Tamaño del arreglo N de los elementos que se insertarán en el árbol
    unsigned int *N = new unsigned int[n];
    unsigned int *M = new unsigned int[m];

    //Se llena el arreglo N con los numeros del 1 al n
    iota(N, N + n, 1);

    //Se permuta el arreglo N de manera aleatoria
    shuffle(N, N + n, mt19937{random_device{}()});   

    //Se llena el arreglo M con los numeros del 1 al n, repitiendose 2^28/n veces cada número
    unsigned int repeticiones_n = pow(2, 28-exp_n);
    unsigned int puntero = 0;
    for(unsigned int i=1; i<=n; i++){
        for(unsigned int j=0; j<repeticiones_n; j++){
            M[puntero++] = i;
        }
    }

    //Se permuta el arreglo M de manera aleatoria
    shuffle(M, M + m, mt19937{random_device{}()});

    //Se crea el arbol
    node *root = insert(NULL, 1);
    for(unsigned int i=0; i<n; i++){
        root = insert(root, N[i]);
    }

    //Se libera la memoria de N
    delete[] N;

    //Se inicia el cronometro
    auto inicio = chrono::high_resolution_clock::now();

    //Se busca cada elemento del arreglo M en el arbol
    for(unsigned int i=0; i<m; i++){
        search(root, M[i]);
    }

    //Se finaliza el cronometro
    auto fin = chrono::high_resolution_clock::now();
    //Se libera la memoria de M
    delete[] M;

    //Clean el arbol splay
    cleanSplay(root);

    //Se calcula el tiempo transcurrido
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();

    printf("Caso SplayTree:\n");
    printf("La busqueda tardo %ld milisegundos en ejecutarse.\n", duracion);

    //Se guarda el resultado en el arreglo de resultados
    resultados_splay[j] = duracion;

    FILE *g = fopen("Result_Splay_Equiprobable.txt", "a"); //append
    fprintf(g, "La busqueda tardo %ld milisegundos en ejecutarse.\n\n", duracion);
    fclose(g);
}


void main_RBTree(unsigned int exp_n, unsigned int j, float resultados_RB[]){
    unsigned int n = pow(2, exp_n); //Tamaño del arreglo de los elementos que se insertarán en el árbol

    unsigned int *N = new unsigned int[n];
    

    //Se llena el arreglo N con los numeros del 1 al n
    iota(N, N + n, 1);

    //Se permuta el arreglo N de manera aleatoria
    shuffle(N, N + n, mt19937{random_device{}()});    

    //Se llena el arreglo M con los numeros del 1 al n, repitiendose 2^28/n veces cada número
    unsigned int repeticiones_n = pow(2, 28-exp_n);
    unsigned int puntero = 0;

    unsigned int *M = new unsigned int[m];

    for(unsigned int i=1; i<=n; i++){
        for(unsigned int j=0; j<repeticiones_n; j++){
            M[puntero++] = i;
        }
    }

    //Se permuta el arreglo M de manera aleatoria
    shuffle(M, M + m, mt19937{random_device{}()});

    //Se crea el arbol
    RBTree tree;
    for (unsigned int i=0; i<n; i++){
        tree.insert(N[i]);
    }

    //Se libera la memoria de N
    delete[] N;


    //Se inicia el cronometro
    auto inicio = chrono::high_resolution_clock::now();

    //Se busca cada elemento del arreglo M en el arbol
    for(unsigned int i=0; i<m; i++){
        searchRBT(tree.root, M[i]);
    }
    
    //Se finaliza el cronometro
    auto fin = chrono::high_resolution_clock::now();
    
    //Se libera la memoria de M
    delete[] M;
    
    //Se limpia el arbol
    cleanRBT(tree.root);
    
    //Se calcula el tiempo transcurrido
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();

    //Se printea
    printf("Caso RBTree:\n");
    cout << "La busqueda tardo " << duracion << " milisegundos en ejecutarse." << endl;
    resultados_RB[j] = duracion;
    FILE *f = fopen("Result_RB_Equiprobable.txt", "a"); //append
    //fprintf(f, "Test %d:\n", j+1);
    fprintf(f, "La busqueda tardo %ld milisegundos en ejecutarse.\n\n", duracion);
    fclose(f);
}

//Calcula el promedio de los tiempos de ejecución
float promedio(float res[]){
    float promedio = 0;
    for (unsigned int i=0; i<n_test; i++){
        promedio += res[i];
    }
    promedio /= n_test;
    return promedio;
}

//Calcula la varianza de los tiempos de ejecución
float varianza(float res[], float promedio){
    float varianza = 0;
    for (unsigned int i=0; i<n_test; i++){
        varianza += pow(res[i]-promedio, 2);
    }
    varianza /= n_test;
    return varianza;
}

//Calcula la desviación estándar de los tiempos de ejecución
float desviacion(float varianza){
    return sqrt(varianza);
}

int main(){
    //Testeamos 3 veces para cada potencia de 2
    unsigned int n;
    FILE *f = fopen("Result_RB_Equiprobable.txt", "w+"); //write
    fclose(f);
    FILE *g = fopen("Result_Splay_Equiprobable.txt", "w+"); //write
    fclose(g);
    for(unsigned int i=2; i<4; i++){
        float resultados_RB[n_test]; //Arreglo donde se guardarán los tiempos de ejecución de cada test segun el n para RBTree
        float resultados_splay[n_test]; //Arreglo donde se guardarán los tiempos de ejecución de cada test segun el n para SplayTree
        n=i;
        printf("Para n = 2^%d:\n", n);
        f = fopen("Result_RB_Equiprobable.txt", "a"); //append
        g = fopen("Result_Splay_Equiprobable.txt", "a"); //append
        fprintf(f, "Para n = 2^%d:\n", n);
        fprintf(g, "Para n = 2^%d:\n", n);
        fclose(f);
        fclose(g);
        
        for (unsigned int j=0; j<n_test; j++){
            printf("Test %d:\n", j+1);
            f = fopen("Result_RB_Equiprobable.txt", "a"); //append
            g = fopen("Result_Splay_Equiprobable.txt", "a"); //append
            fprintf(f, "Test %d:\n", j+1);
            fprintf(g, "Test %d:\n", j+1);
            fclose(f);
            fclose(g);
            main_RBTree(n,j,resultados_RB);
            main_splay(n,j,resultados_splay);
        }
        f = fopen("Result_RB_Equiprobable.txt", "a"); //append
        g = fopen("Result_Splay_Equiprobable.txt", "a"); //append
        float promedio1 = promedio(resultados_RB);
        fprintf(f, "Promedio de RBTree: %f\n", promedio1);
        fprintf(f, "Varianza de RBTree: %f\n", varianza(resultados_RB, promedio1));
        fprintf(f, "Desviacion estandar de RBTree: %f\n\n", desviacion(varianza(resultados_RB, promedio1)));
        float promedio2 = promedio(resultados_splay);
        fprintf(g, "Promedio de SplayTree: %f\n", promedio2);
        fprintf(g, "Varianza de SplayTree: %f\n", varianza(resultados_splay, promedio2));
        fprintf(g, "Desviacion estandar de SplayTree: %f\n\n", desviacion(varianza(resultados_splay, promedio2)));
        fclose(f);
        fclose(g);
    }

    return 0;
}
