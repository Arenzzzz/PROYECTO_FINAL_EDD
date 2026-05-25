cmake_minimum_required(VERSION 4.2)
project(PROYECTO_FINAL)

set(CMAKE_CXX_STANDARD 20)

add_executable(PROYECTO_FINAL main.cpp
        ESTRUCTURAS/MatrizDispersa.cpp
        ESTRUCTURAS/MatrizDispersa.h
        ESTRUCTURAS/ABBCapas.cpp
        ESTRUCTURAS/ABBCapas.h
        ESTRUCTURAS/ListaCircular.cpp
        ESTRUCTURAS/ListaCircular.h
        ESTRUCTURAS/ABBUsuarios.cpp
        ESTRUCTURAS/ABBUsuarios.h
        UTILS/CargaMasiva.cpp
        UTILS/CargaMasiva.h
        UTILS/Graphviz.cpp
        UTILS/Graphviz.h
        Structs.h
        UTILS/GeneradorImagenes.cpp
        UTILS/GeneradorImagenes.h
)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/REPORTES)