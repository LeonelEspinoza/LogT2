#include <iostream> // Para printear
#include <chrono>   // Para medir el tiempo 
#include <math.h>   // Para pow (potencias)
#include <algorithm> //Para lograr
#include <random>   // garantizar que el arreglo sea aleatorio
#include <redblacktree.h>
#include <splaytree.h>

static const int m = pow(2,28); //Tamaño del arreglo de la secuencia de búsqueda M
using namespace std;
int n_test=3;
float *res; //Arreglo donde se guardarán los tiempos de ejecución de cada test segun el n para RBTree
float *res2; //Arreglo donde se guardarán los tiempos de ejecución de cada test segun el n para SplayTree

void main_splay(int exp_n, int j){
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
    //Se libera la memoria de M
    delete[] M;

    //Se calcula el tiempo transcurrido
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();


    //Se guarda el resultado en el arreglo de resultados
    //res[j] = int(duracion);

    printf("Caso SplayTree:\n");
    printf("La busqueda tardo %ld milisegundos en ejecutarse.\n", duracion);
    res2[j] = duracion;
    FILE *g = fopen("Result_Splay_Equiprobable.txt", "a"); //append
    //fprintf(f, "Test %d:\n", j+1);
    fprintf(g, "La busqueda tardo %ld milisegundos en ejecutarse.\n\n", duracion);
    fclose(g);


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


void main_RBTree(int exp_n, int j){
    int n = pow(2, exp_n); //Tamaño del arreglo de los elementos que se insertarán en el árbol

    int *N = new int[n];
    

    //Se llena el arreglo N con los numeros del 1 al n
    iota(N, N + n, 1);

    //Se permuta el arreglo N de manera aleatoria
    shuffle(N, N + n, mt19937{random_device{}()});    

    //Se llena el arreglo M con los numeros del 1 al n, repitiendose 2^28/n veces cada número
    int repeticiones_n = pow(2, 28-exp_n);
    int puntero = 0;

    int *M = new int[m];

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
    cout << "La busqueda tardo " << duracion << " milisegundos en ejecutarse." << endl;
    res[j] = duracion;
    FILE *f = fopen("Result_RB_Equiprobable.txt", "a"); //append
    //fprintf(f, "Test %d:\n", j+1);
    fprintf(f, "La busqueda tardo %ld milisegundos en ejecutarse.\n\n", duracion);
    fclose(f);
}

//Calcula el promedio de los tiempos de ejecución
float promedio(float res[]){
    float promedio = 0;
    for (int i=0; i<n_test; i++){
        promedio += res[i];
        promedio /= n_test;
    }
    return promedio;
}

//Calcula la varianza de los tiempos de ejecución
float varianza(float res[], float promedio){
    float varianza = 0;
    for (int i=0; i<n_test; i++){
        varianza += pow(res[i]-promedio, 2);
        varianza /= n_test;
    }
    return varianza;
}

//Calcula la desviación estándar de los tiempos de ejecución
float desviacion(float varianza){
    return sqrt(varianza);
}

int main(){
    //Testeamos 5 veces para el n dado indica 2^n
    res = new float[n_test];
    res2 = new float[n_test];
    int n;
    FILE *f = fopen("Result_RB_Equiprobable.txt", "w+"); //write
    fclose(f);
    FILE *g = fopen("Result_Splay_Equiprobable.txt", "w+"); //write
    fclose(g);
    for(int i=2; i<4; i++){
        n=i;
        printf("Para n = %d:\n", n);
        f = fopen("Result_RB_Equiprobable.txt", "a"); //append
        g = fopen("Result_Splay_Equiprobable.txt", "a"); //append
        fprintf(f, "Para n = %d:\n", n);
        fprintf(g, "Para n = %d:\n", n);
        fclose(f);
        fclose(g);
        
        for (int j=0; j<n_test; j++){
            printf("Test %d:\n", j+1);
            f = fopen("Result_RB_Equiprobable.txt", "a"); //append
            g = fopen("Result_Splay_Equiprobable.txt", "a"); //append
            fprintf(f, "Test %d:\n", j+1);
            fprintf(g, "Test %d:\n", j+1);
            fclose(f);
            fclose(g);
            main_RBTree(n,j);
            main_splay(n,j);
        }
        f = fopen("Result_RB_Equiprobable.txt", "a"); //append
        g = fopen("Result_Splay_Equiprobable.txt", "a"); //append
        float promedio1 = promedio(res);
        fprintf(f, "Promedio de RBTree: %f\n", promedio1);
        fprintf(f, "Varianza de RBTree: %f\n", varianza(res, promedio1));
        fprintf(f, "Desviacion estandar de RBTree: %f\n\n", desviacion(varianza(res, promedio1)));
        float promedio2 = promedio(res2);
        fprintf(g, "Promedio de SplayTree: %f\n", promedio2);
        fprintf(g, "Varianza de SplayTree: %f\n", varianza(res2, promedio2));
        fprintf(g, "Desviacion estandar de SplayTree: %f\n\n", desviacion(varianza(res2, promedio2)));
        fclose(f);
        fclose(g);
    }

    delete[] res;
    delete[] res2;

    return 0;
}
