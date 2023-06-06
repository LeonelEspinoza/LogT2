#include <iostream> // Para printear
#include <chrono>   // Para medir el tiempo 
#include <math.h>   // Para pow (potencias)
#include <algorithm> //Para lograr
#include <random>   // garantizar que el arreglo sea aleatorio
#include <redblacktree.h>
#include <splaytree.h>
#include <thread>

static const unsigned int m = pow(2,28); //Tamaño del arreglo de la secuencia de búsqueda M
using namespace std;
unsigned int n_test=3;
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

typedef struct {
    unsigned int *M;
} args;

typedef struct {
    unsigned int *M;
    unsigned int inicio;
    unsigned int fin;
} argsFill;

void thread_functionInitM(void *arg){
    args *argumentos = (args*) arg;
    argumentos->M = new unsigned int[m];
}

void thread_fillM(void *arg){
    argsFill args = *(argsFill*) arg;
    for (unsigned int i=args.inicio; i<args.fin; i++){
        args.M[i] = i+1;
    }
}

unsigned int *initN(unsigned int n){
        unsigned int *N = new unsigned int[n];
        //Se llena el arreglo N con los numeros del 1 al n
        iota(N, N + n, 1);
        //Se permuta el arreglo N de manera aleatoria
        shuffle(N, N + n, mt19937{random_device{}()});  
        return N;
}

void mainbacan(unsigned int exp_n, float resultados_RB[], float resultados_splay[]){
    
    unsigned int n = pow(2, exp_n); //Tamaño del arreglo N de los elementos que se insertarán en el árbol
    unsigned int *M;
    unsigned int repeticiones_n = pow(2, 28-exp_n);
    unsigned int puntero = 0;    
    thread t1;
    args *arg = new args;
    
    t1 = thread(thread_functionInitM, arg);    
    
    unsigned int *N = initN(n); 

    t1.join();
    M = arg->M;
    delete(arg);

    thread *thread_fill = new thread[repeticiones_n];
    unsigned int iniciofill = 0;
    unsigned int pasos = m/repeticiones_n;
    unsigned int finfill = pasos;
    argsFill *argFill = new argsFill[repeticiones_n];

    for (unsigned int i=0; i<repeticiones_n; i++){
        argsFill *arg = &argFill[i];
        arg->M = M;
        arg->inicio = iniciofill;
        arg->fin = finfill;
        thread_fill[i] = thread(thread_fillM, arg);
        iniciofill = finfill;
        finfill += pasos;
    }

    //Se crea el arbol
    node *root = insert(NULL, 1);
    for(unsigned int i=0; i<n; i++){
        root = insert(root, N[i]);
    }

    //Se libera la memoria de N
    delete[] N;

    for (unsigned int i=0; i<repeticiones_n; i++){
        thread_fill[i].join();
    }
    delete[] argFill;
    //Se permuta el arreglo M de manera aleatoria
    shuffle(M, M + m, mt19937{random_device{}()});

    //Se inicia el cronometro
    auto inicio = chrono::high_resolution_clock::now();

    //Se busca cada elemento del arreglo M en el arbol
    for(unsigned int i=0; i<m; i++){
        root=search(root, M[i]);
    }
    //Se finaliza el cronometro
    auto fin = chrono::high_resolution_clock::now();
    //Clean el arbol splay
    cleanSplay(root);
    //Se calcula el tiempo transcurrido
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();

    printf("Caso SplayTree:\n");
    printf("La busqueda tardo %ld milisegundos en ejecutarse.\n", duracion);
    int j= 0;
    //Se guarda el resultado en el arreglo de resultados
    resultados_splay[j] = duracion;
    FILE *g = fopen("Result_Splay_Equiprobable.txt", "a"); //append
    fprintf(g, "La busqueda tardo %ld milisegundos en ejecutarse.\n\n", duracion);    


    N = initN(n);
    //Se crea el arbol
    RBTree tree;
    for (unsigned int i=0; i<n; i++){
        tree.insert(N[i]);
    }

    delete[] N;
    
    //Se permuta el arreglo M de manera aleatoria
    shuffle(M, M + m, mt19937{random_device{}()});

    //Se inicia el cronometro
    inicio = chrono::high_resolution_clock::now();
    //Se busca cada elemento del arreglo M en el arbol
    for(unsigned int i=0; i<m; i++){
        searchRBT(tree.root, M[i]);
    }

    //Se finaliza el cronometro
    fin = chrono::high_resolution_clock::now();
    //Clean el arbol splay
    cleanRBT(tree.root);
    //Se calcula el tiempo transcurrido
    duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();
    //fprintf(f, "Test %d:\n", j+1);
    
    //fclose(f);
    printf("\nCaso RB:\n");
    printf("La busqueda tardo %ld milisegundos en ejecutarse.\n\n", duracion);
    //Se guarda el resultado en el arreglo de resultados
    resultados_RB[j] = duracion;
    FILE *f = fopen("Result_RB_Equiprobable.txt", "a"); //append    
    fprintf(f, "Test %d:\n", j+1);
    fprintf(f, "La busqueda tardo %ld milisegundos en ejecutarse.\n\n", duracion);    
    j++;

    for (unsigned int i=1; i<n_test; i++){
        N = initN(n);
        //Se crea el arbol
        RBTree tree;
        for (unsigned int i=0; i<n; i++){
            tree.insert(N[i]);
        } 
        delete[] N;
        //Se permuta el arreglo M de manera aleatoria
        shuffle(M, M + m, mt19937{random_device{}()});

        //Se inicia el cronometro
        inicio = chrono::high_resolution_clock::now();

        //Se busca cada elemento del arreglo M en el arbol
        for(unsigned int i=0; i<m; i++){
            searchRBT(tree.root, M[i]);
        }

        //Se finaliza el cronometro
        fin = chrono::high_resolution_clock::now();
        //Clean el arbol splay
        cleanRBT(tree.root);
        //Se calcula el tiempo transcurrido
        duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();
        //fprintf(f, "Test %d:\n", j+1);

        
        //fclose(f);
        printf("Caso RB:\n");
        printf("La busqueda tardo %ld milisegundos en ejecutarse.\n", duracion);

        //Se guarda el resultado en el arreglo de resultados
        resultados_RB[j] = duracion;
        fprintf(f, "Test %d:\n", j+1);
        fprintf(f, "La busqueda tardo %ld milisegundos en ejecutarse.\n\n", duracion);

        N = initN(n);
        root = insert(NULL, 1);
        for(unsigned int i=0; i<n; i++){
            root = insert(root, N[i]);
        }        
        delete[] N;
        //Se permuta el arreglo M de manera aleatoria
        shuffle(M, M + m, mt19937{random_device{}()});

        //Se inicia el cronometro
        inicio = chrono::high_resolution_clock::now();

        //Se busca cada elemento del arreglo M en el arbol
        for(unsigned int i=0; i<m; i++){
            root=search(root, M[i]);
        }

        //Se finaliza el cronometro
        fin = chrono::high_resolution_clock::now();
        //Clean el arbol splay
        cleanSplay(root);
        //Se calcula el tiempo transcurrido
        duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();
        //fprintf(f, "Test %d:\n", j+1);

        
        //fclose(f);
        printf("Caso SplayTree:\n");
        printf("La busqueda tardo %ld milisegundos en ejecutarse.\n\n", duracion);

        //Se guarda el resultado en el arreglo de resultados
        resultados_splay[j] = duracion;
        fprintf(g, "Test %d:\n", j+1);
        
        fprintf(g, "La busqueda tardo %ld milisegundos en ejecutarse.\n\n", duracion);
        j++;
    }

    //Se libera la memoria de M
    delete[] M;
    fclose(f);
    fclose(g);

}


int main(){
    //Testeamos 3 veces para cada potencia de 2
    unsigned int n;
    FILE *f = fopen("Result_RB_Equiprobable.txt", "w+"); //write
    fclose(f);
    FILE *g = fopen("Result_Splay_Equiprobable.txt", "w+"); //write
    fclose(g);
    for(unsigned int i=16; i<25; i++){
        float resultados_RB[n_test]; //Arreglo donde se guardarán los tiempos de ejecución de cada test segun el n para RBTree
        float resultados_splay[n_test]; //Arreglo donde se guardarán los tiempos de ejecución de cada test segun el n para SplayTree
        n=i;
        printf("\nPara n = 2^%d:\n", n);
        f = fopen("Result_RB_Equiprobable.txt", "a"); //append
        g = fopen("Result_Splay_Equiprobable.txt", "a"); //append
        fprintf(f, "Para n = 2^%d:\n", n);
        fprintf(g, "Para n = 2^%d:\n", n);
        fclose(f);
        fclose(g);
        mainbacan(n, resultados_RB, resultados_splay);
        
        //for (unsigned int j=0; j<n_test; j++){
        //    printf("Test %d:\n", j+1);
        //    f = fopen("Result_RB_Equiprobable.txt", "a"); //append
        //    g = fopen("Result_Splay_Equiprobable.txt", "a"); //append
        //    fprintf(f, "Test %d:\n", j+1);
        //    fprintf(g, "Test %d:\n", j+1);
        //    fclose(f);
        //    fclose(g);
        //    main_RBTree(n,j,resultados_RB);
        //    main_splay(n,j,resultados_splay);
        //}
        f = fopen("Result_RB_Equiprobable.txt", "a"); //append
        g = fopen("Result_Splay_Equiprobable.txt", "a"); //append
        float promedio1 = promedio(resultados_RB);
        float varianza1 = varianza(resultados_RB, promedio1);
        float desviacion1 = desviacion(varianza1);
        fprintf(f, "Promedio de RBTree: %f\n", promedio1);
        fprintf(f, "Varianza de RBTree: %f\n", varianza1);
        fprintf(f, "Desviacion estandar de RBTree: %f\n\n", desviacion1);
        float promedio2 = promedio(resultados_splay);
        float varianza2 = varianza(resultados_splay, promedio2);
        float desviacion2 = desviacion(varianza2);
        fprintf(g, "Promedio de SplayTree: %f\n", promedio2);
        fprintf(g, "Varianza de SplayTree: %f\n", varianza2);
        fprintf(g, "Desviacion estandar de SplayTree: %f\n\n", desviacion2);
        fclose(f);
        fclose(g);
    }

    return 0;
}
