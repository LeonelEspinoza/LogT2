# LogT2
Diseño y Análisis de Algoritmos (CC4102-1): Tarea 2, Análisis Amortizado  
Integrantes:  
+ Felipe Olivares  
+ Nicolás Calbucura  
+ Leonel Espinoza

## Instrucciones de compilación y ejecución
Para compilar el proyecto, debes tener c++11. Opcionalmente, puedes tener cmake/make para compilar.

### CMake
Debes correr el siguiente comando para compilar el proyecto con cmake/make:
> cmake -B build -S .

Posteriormente, debes correr make en la carpeta build.


#### Via terminal:
Para compilar si no tienes cmake/make:
- La tarea equiprobable:
>  g++ -O3 -std=c++11 -pthread -I Librerias T2_Equiprobable.cpp Librerias/redblacktree.cpp Librerias/splaytree.cpp -o T2_Equiprobable.exe

- La tarea Skew:
>  g++ -O3 -std=c++11 -pthread -I Librerias T2_Skew.cpp Librerias/redblacktree.cpp Librerias/splaytree.cpp -o T2_Skew.exe