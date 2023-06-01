add_library(Librerias SHARED
#Aqui se agrega el nombre de la libreria y los archivos que se van a compilar
# que estan en la carpeta Librerias
    redblacktree.h
    redblacktree.cpp
    splaytree.h
    splaytree.cpp)

target_include_directories(Librerias PUBLIC ${CMAKE_CURRENT_LIST_DIR})