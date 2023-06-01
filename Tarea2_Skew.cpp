#include <iostream> // Para printear
#include <chrono>   // Para medir el tiempo 
#include <math.h>   // Para pow (potencias)
#include <algorithm> //Para lograr
#include <random>   // garantizar que el arreglo sea aleatorio


using namespace std;

int N=pow(2,15);
static const int M=pow(2,28);
float alpha=0.5;
int SUM;

int fun(int i){
    int res=int(pow(i,alpha));
    return res;
}

void SetSUM(){
    int res=0;
    for(int i=0;i<N;i++){
        res+=fun(i);
    }
    SUM=res;
    return ;
}

int phi(int i){
    int res=(fun(i)*M)/SUM;
    return res;
}

void llenar(int* pi){
    iota(pi, pi + N, 1);
}

void main(){
    //para N desde 2**16 hasta 2**24
    for(int exp=16;exp<=24;exp++){
        //seteamos el N
        N=N*2;
        //crear tres arreglos de tamaño M
        int tmp1[M]={0};
        int tmp2[M]={0};
        int tmp3[M]={0};

        int* arreglos[3]={tmp1,tmp2,tmp3};
        //crear una permutacion aleatoria de pi
        int *pi = new int[N];
        //Se llena el arreglo con los numeros del 1 al N
        iota(pi, pi + N, 1);
        //Se permuta el arreglo de manera aleatoria
        shuffle(pi, pi + N, mt19937{random_device{}()});
        
        //un arreglo de los valores que debe tomar alpha
        int alphas[3]={0.5,1,1.5};

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
}