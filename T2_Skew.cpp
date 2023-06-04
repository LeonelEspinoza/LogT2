#include <iostream> // Para printear
#include <chrono>   // Para medir el tiempo 
#include <math.h>   // Para pow (potencias)
#include <algorithm> //Para lograr
#include <random>   // garantizar que el arreglo sea aleatorio
#include <redblacktree.h>
#include <splaytree.h>

using namespace std;
int n_test=3;
float *resRBT05;
float *resRBT1;
float *resRBT15;
float *res05; //Arreglo donde se guardarán los tiempos de ejecución de cada test segun el n para SplayTree
float *res1;
float *res15;

static const int m=pow(2,28);

int f(int i, double alpha){
    int res = (int) pow(i,alpha);
    return res;
}

int SUM(double alpha, int n){
    int SUM=0;
    for(int i=1;i<=n;i++){
        SUM+=f(i,alpha);
    }
    return SUM;
}

int phi(int i, double alpha, int n){
    int res=(f(i,alpha)*m)/SUM(alpha,n);
    return res;
}

void main_splay(int exp_n, int ntest){
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
    double alphas[3]={0.5,1,1.5};

    for(int i=0; i<3; i++) {
        //Se setea el apha correspondiente
        double alpha = alphas[i];

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
    auto inicio1 = chrono::high_resolution_clock::now();

    //Se busca cada elemento del arreglo C1 en el árbol
    for(int i=0; i<m; i++){
        search(root, C1[i]);
    }

    //Se finaliza el cronometro
    auto fin1 = chrono::high_resolution_clock::now();

    //Se calcula el tiempo transcurrido
    auto duracionC1 = chrono::duration_cast<chrono::milliseconds>(fin1 - inicio1).count();

    //Se libera la memoria de C1
    delete[] C1;

    //Se inicia el cronometro
    auto inicio2 = chrono::high_resolution_clock::now();

    //Se busca cada elemento del arreglo C2 en el árbol
    for(int i=0; i<m; i++){
        search(root, C2[i]);
    }

    //Se finaliza el cronometro
    auto fin2 = chrono::high_resolution_clock::now();

    //Se calcula el tiempo transcurrido
    auto duracionC2 = chrono::duration_cast<chrono::milliseconds>(fin2 - inicio2).count();

    //Se libera la memoria de C2
    delete[] C2;

    //Se inicia el cronometro
    auto inicio3 = chrono::high_resolution_clock::now();

    //Se busca cada elemento del arreglo C3 en el árbol
    for(int i=0; i<m; i++){
        search(root, C3[i]);
    }

    //Se finaliza el cronometro
    auto fin3 = chrono::high_resolution_clock::now();

    //Se calcula el tiempo transcurrido
    auto duracionC3 = chrono::duration_cast<chrono::milliseconds>(fin3 - inicio3).count();

    //Se libera la memoria de C3
    delete[] C3;

    printf("Caso SplayTree:\n");
    printf("La busqueda para alfa = 0.5 tardo %ld milisegundos en ejecutarse.\n", duracionC1);
    printf("La busqueda para alfa = 1.0 tardo %ld milisegundos en ejecutarse.\n", duracionC2);
    printf("La busqueda para alfa = 1.5 tardo %ld milisegundos en ejecutarse.\n", duracionC3);
    
    FILE *g = fopen("Result_Splay_Skew.txt", "a");
    fprintf(g, "La busqueda para alfa = 0.5 tardo %ld milisegundos en ejecutarse.\n", duracionC1);
    fprintf(g, "La busqueda para alfa = 1.0 tardo %ld milisegundos en ejecutarse.\n", duracionC2);
    fprintf(g, "La busqueda para alfa = 1.5 tardo %ld milisegundos en ejecutarse.\n", duracionC3);
    fclose(g);
    res05[ntest]=duracionC1;
    res1[ntest]=duracionC2;
    res15[ntest]=duracionC3;
}

void main_RBTree(int exp_n , int ntest){
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
    double alphas[3]={0.5,1,1.5};

    for(int i=0; i<3; i++) {
        //Se setea el apha correspondiente
        double alpha= alphas[i];

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
    RBTree tree;
    for (int i=0; i<n; i++){
        tree.insert(N[i]);
    }

    //Se libera la memoria de N
    delete[] N;

    //Se inicia el cronometro
    auto inicio1 = chrono::high_resolution_clock::now();

    //Se busca cada elemento del arreglo M en el arbol
    for(int i=0; i<m; i++){
        searchRBT(tree.root, C1[i]);
    }

    //Se finaliza el cronometro
    auto fin1 = chrono::high_resolution_clock::now();

    //Se calcula el tiempo transcurrido
    auto duracionC1 = chrono::duration_cast<chrono::milliseconds>(fin1 - inicio1).count();

    //Se libera la memoria de C1
    delete[] C1;

    //Se inicia el cronometro
    auto inicio2 = chrono::high_resolution_clock::now();

    //Se busca cada elemento del arreglo M en el arbol
    for(int i=0; i<m; i++){
        searchRBT(tree.root, C2[i]);
    }

    //Se finaliza el cronometro
    auto fin2 = chrono::high_resolution_clock::now();

    //Se calcula el tiempo transcurrido
    auto duracionC2 = chrono::duration_cast<chrono::milliseconds>(fin2 - inicio2).count();

    //Se libera la memoria de C2
    delete[] C2;

    //Se inicia el cronometro
    auto inicio3 = chrono::high_resolution_clock::now();

    //Se busca cada elemento del arreglo M en el arbol
    for(int i=0; i<m; i++){
        searchRBT(tree.root, C3[i]);
    }

    //Se finaliza el cronometro
    auto fin3 = chrono::high_resolution_clock::now();

    //Se calcula el tiempo transcurrido
    auto duracionC3 = chrono::duration_cast<chrono::milliseconds>(fin3 - inicio3).count();

    //Se libera la memoria de C3
    delete[] C3;

    printf("Caso RBtree:\n");
    printf("La busqueda para alfa = 0.5 tardo %ld milisegundos en ejecutarse.\n", duracionC1);
    printf("La busqueda para alfa = 1.0 tardo %ld milisegundos en ejecutarse.\n", duracionC2);
    printf("La busqueda para alfa = 1.5 tardo %ld milisegundos en ejecutarse.\n", duracionC3);
    
    FILE *g = fopen("Result_RB_Skew.txt", "a"); //write
    fprintf(g, "La busqueda para alfa = 0.5 tardo %ld milisegundos en ejecutarse.\n", duracionC1);
    fprintf(g, "La busqueda para alfa = 1.0 tardo %ld milisegundos en ejecutarse.\n", duracionC2);
    fprintf(g, "La busqueda para alfa = 1.5 tardo %ld milisegundos en ejecutarse.\n", duracionC3);
    fclose(g);
    resRBT05[ntest] = duracionC1;
    resRBT1[ntest] = duracionC2;
    resRBT15[ntest] = duracionC3;
    
    
}


//Calcula el promedio de los tiempos de ejecución
float promedio(float res[], int n){
    float promedio = 0;
    for (int i=0; i<n; i++){
        promedio += res[i];
        promedio /= n;
    }
    return promedio;
}

//Calcula la varianza de los tiempos de ejecución
float varianza(float res[], float promedio, int n){
    float varianza = 0;
    for (int i=0; i<n; i++){
        varianza += pow(res[i]-promedio, 2);
        varianza /= n;
    }
    return varianza;
}

float desviacion(float varianza){
    return sqrt(varianza);
}   

int main(){
    //Testeamos 5 veces para el n dado indica 2^n
    int n;
    resRBT05 = new float[n_test];
    resRBT1 = new float[n_test];
    resRBT15 = new float[n_test];
    res05 = new float[n_test];
    res1 = new float[n_test];
    res15 = new float[n_test];

    FILE *f = fopen("Result_RB_Skew.txt", "w+"); //write
    fclose(f);
    FILE *g = fopen("Result_Splay_Skew.txt", "w+"); //write
    fclose(g);
    for(int i=2; i<4; i++){
        n=i;
        printf("Para n = %d:\n", n);
        FILE *f = fopen("Result_RB_Skew.txt", "a"); //append
        FILE *g = fopen("Result_Splay_Skew.txt", "a"); //append
        fprintf(f, "Para n = %d:\n", n);
        fprintf(g, "Para n = %d:\n", n);
        fclose(f);
        fclose(g);
        
        for (int j=0; j<n_test; j++){
            
            printf("Test %d:\n", j+1);
            f = fopen("Result_RB_Skew.txt", "a"); //append
            g = fopen("Result_Splay_Skew.txt", "a"); //append
            fprintf(f, "Test %d:\n", j+1);
            fprintf(g, "Test %d:\n", j+1);
            fclose(f);
            fclose(g);
               
            main_RBTree(n,j);
            main_splay(n,j);
        }
        
        f = fopen("Result_RB_Skew.txt", "a"); //append
        g = fopen("Result_Splay_Skew.txt", "a"); //append        
        float promedio1 = promedio(resRBT05, n_test);
        fprintf(f, "\n\nPromedio de RBTree para alfa = 0.5: %f\n", promedio1);
        fprintf(f, "Varianza de RBTree para alfa = 0.5: %f\n", varianza(resRBT05, promedio1, n_test));
        fprintf(f, "Desviacion estandar de RBTree para alfa = 0.5: %f\n", desviacion(varianza(resRBT05, promedio1, n_test)));

        float promedio2 = promedio(resRBT1, n_test);
        fprintf(f, "\nPromedio de RBTree para alfa = 1.0: %f\n", promedio2);
        fprintf(f, "Varianza de RBTree para alfa = 1.0: %f\n", varianza(resRBT1, promedio2, n_test));
        fprintf(f, "Desviacion estandar de RBTree para alfa = 1.0: %f\n", desviacion(varianza(resRBT1, promedio2, n_test)));

        float promedio3 = promedio(resRBT15, n_test);
        fprintf(f, "\nPromedio de RBTree para alfa = 1.5: %f\n", promedio3);
        fprintf(f, "Varianza de RBTree para alfa = 1.5: %f\n", varianza(resRBT15, promedio3, n_test));
        fprintf(f, "Desviacion estandar de RBTree para alfa = 1.5: %f\n", desviacion(varianza(resRBT15, promedio3, n_test)));


        float promedio4 = promedio(res05, n_test);
        fprintf(g, "\n\nPromedio de SplayTree para alfa = 0.5: %f\n", promedio4);
        fprintf(g, "Varianza de SplayTree para alfa = 0.5: %f\n", varianza(res05, promedio4, n_test));
        fprintf(g, "Desviacion estandar de SplayTree para alfa = 0.5: %f\n", desviacion(varianza(res05, promedio4, n_test)));

        float promedio5 = promedio(res1, n_test);
        fprintf(g, "\nPromedio de SplayTree para alfa = 1.0: %f\n", promedio5);
        fprintf(g, "Varianza de SplayTree para alfa = 1.0: %f\n", varianza(res1, promedio5, n_test));
        fprintf(g, "Desviacion estandar de SplayTree para alfa = 1.0: %f\n", desviacion(varianza(res1, promedio5, n_test)));

        float promedio6 = promedio(res15, n_test);
        fprintf(g, "\nPromedio de SplayTree para alfa = 1.5: %f\n", promedio6);
        fprintf(g, "Varianza de SplayTree para alfa = 1.5: %f\n", varianza(res15, promedio6, n_test));
        fprintf(g, "Desviacion estandar de SplayTree para alfa = 1.5: %f\n", desviacion(varianza(res15, promedio6, n_test)));
        fclose(f);
        fclose(g);
        
       }
         
    fclose(f);
    fclose(g);
    delete[] resRBT05;
    delete[] resRBT1;
    delete[] resRBT15;
    delete[] res05;
    delete[] res1;
    delete[] res15; 

    return 0;
}