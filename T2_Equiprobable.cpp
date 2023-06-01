#include <iostream> // Para printear
#include <chrono>   // Para medir el tiempo 
#include <math.h>   // Para pow (potencias)
#include <algorithm> //Para lograr
#include <random>   // garantizar que el arreglo sea aleatorio
#include <redblacktree.h>
#include <splaytree.h>

#define m static_cast<int>(pow(2, 28)) //Tamaño del arreglo de la secuencia
//El static_cast<int> es para que no tire warning de conversion de double a int

using namespace std;

void main_splay(int exp_n){
    //int m = pow(2,28);
    int n = pow(2, exp_n);
    int *A = new int[n];

    //Se llena el arreglo con los numeros del 1 al n
    iota(A, A + n, 1);

    //Se permuta el arreglo de manera aleatoria
    shuffle(A, A + n, mt19937{random_device{}()});   


    //int repeticiones_n = pow(2, 28 - exp_n);
    //Se llena el arreglo con los numeros del 1 al n, repitiendose 2^28/n veces
    /*
    no cache que pasa aqui u.u, lo deje a mi manera por mientras
    int puntero = 0;
    for(int i=1; i<=n; i++){
        for(int j=0; j<repeticiones_n; j++){
            M[puntero++] = i;
        }
    }*/
    //Se permuta el arreglo M de manera aleatoria



    //Se crea el arbol
    node *root = insert(NULL, 1);
    for(int i=0; i<n; i++){
        root = insert(root, A[i]);
    }

    //Se libera la memoria
    delete[] A;

    //Se genera el arreglo de Bsecuencia
    int *BSecuencia = new int[m];
    for (int i = 0; i < m; i++){
        BSecuencia[i] = (i)%n + 1;
    }

    //Se inicia el cronometro
    auto inicio = chrono::high_resolution_clock::now();

    //Se busca cada elemento del arreglo M en el arbol
    for(int i=0; i<m; i++){
        search(root, BSecuencia[i]);
    }

    //Se finaliza el cronometro
    auto fin = chrono::high_resolution_clock::now();

    //Se calcula el tiempo transcurrido
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();

    //Se guarda el resultado en el arreglo de resultados
    //res[j] = int(duracion);

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

    //Se libera la memoria
    delete[] BSecuencia;
}

void main_rbtree(int exp_n){
    int n = pow(2, exp_n);
    int *A = new int[n];
    //Se llena el arreglo con los numeros del 1 al n
    iota(A, A + n, 1);

    //Se permuta el arreglo de manera aleatoria
    shuffle(A, A + n, mt19937{random_device{}()});    

    RBTree tree;
    for (int i = 0; i < n; i++){
        tree.insert(i+1);
    }

    //Se libera la memoria
    delete[] A;

    //Se genera el arreglo de Bsecuencia
    int *BSecuencia = new int[m];

    // Notamos que m al ser 2**i n, entonces para formar el arreglo de Bsecuencia
    // basta con ir leyendo el arreglo A de manera circular.    
    for (int i = 0; i < m; i++){
        //BSecuencia[i] = A[i%n]; se quito esto para ser mas optimo con la memoria
        BSecuencia[i] = i%n + 1;
    }

    

    //finalmente se permuta el arreglo para que sea aleatorio
    //y no ciclico
    shuffle(BSecuencia, BSecuencia + m, mt19937{random_device{}()}); 


    //Se inicia el cronometro
    auto inicio = chrono::high_resolution_clock::now();
    //Se busca cada elemento del arreglo M en el arbol
    for(int i=0; i<m; i++){
        searchRBT(tree.root, BSecuencia[i]);
    }
    //Se finaliza el cronometro
    auto fin = chrono::high_resolution_clock::now();
    
    free(BSecuencia);
    
    //Se calcula el tiempo transcurrido
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();
    //se printea
    cout << "La búsqueda tardó " << duracion << " milisegundos en ejecutarse." << endl;

}

int main(){
    //Testeamos 10 veces para el n dado indica 2^n
    int n;
    for(int i=0; i<5; i++){
        for (int j=16; j<25; j++){
            main_rbtree(n);
            main_splay(n);            
        }
    }
    return 0;
}
