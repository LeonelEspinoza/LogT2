cmake_minimum_required(VERSION 3.0.0)
project(Tarea2_Logaritmos)

add_subdirectory(Librerias) #Aqui se agrega la carpeta de las librerias

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3") #Aqui se agregan las banderas de compilacion 

# Añadir un objetivo personalizado que se ejecute siempre
add_custom_target(abrir_readme ALL
                  COMMAND ${CMAKE_COMMAND} -E cat ../readmake.txt)


                  
add_executable(T2_Equiprobable EXCLUDE_FROM_ALL T2_Equiprobable.cpp)
target_link_libraries(T2_Equiprobable Librerias)

#Aqui se agrega el target run que ejecuta el programa equiprobable
add_custom_target(run-equiprobable
    #Aqui se agrega el nombre del ejecutable y los archivos que se van a compilar
    COMMAND ./T2_Equiprobable
    DEPENDS T2_Equiprobable
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})


add_executable(T2_Skew EXCLUDE_FROM_ALL T2_Skew.cpp)
target_link_libraries(T2_Skew Librerias)


#Aqui se agrega el target run que ejecuta el programa skew
add_custom_target(run-skew
    COMMAND ./T2_Skew
    DEPENDS T2_Skew
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})

#Aqui se agrega el target compile que compila los dos codigos
add_custom_target(compile
    COMMAND make T2_Equiprobable
    COMMAND make T2_Skew
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})

add_custom_target(compile-e
    COMMAND make T2_Equiprobable
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})

add_custom_target(compile-s
    COMMAND make T2_Skew
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})    