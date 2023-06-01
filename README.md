# LogT2
Diseño y Análisis de Algoritmos (CC4102-1): Tarea 2, Análisis Amortizado  
Integrantes:  
+ Felipe Olivares  
+ Nicolás Calbucura  
+ Leonel Espinoza

### Debes correr el siguiente comando para compilar el proyecto:
> cmake -B build -S .

Posteriormente, debes correr make en la carpeta build.

#### Via comando:
Para compilar si no tienes cmake/make:
- La tarea equiprobable:
>  g++ -O3 -I Librerias T2_Equiprobable.cpp Librerias/redblacktree.cpp Librerias/splaytree.cpp -o T2_Equiprobable.exe

- La tarea Skew:
>  g++ -O3 -I Librerias T2_Skew.cpp Librerias/redblacktree.cpp Librerias/splaytree.cpp -o Tarea2_Skew.exe