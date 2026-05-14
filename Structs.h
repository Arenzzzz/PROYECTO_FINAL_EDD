#ifndef PROYECTO_FINAL_STRUCTS_H
#define PROYECTO_FINAL_STRUCTS_H

#include <string>
#include "ESTRUCTURAS/MatrizDispersa.h"
using namespace std;

// Forward declaration
struct NodoABBCapa;

// Nodo de lista de capas por imagen
struct NodoCapa {
    NodoABBCapa* refCapa;
    NodoCapa* siguiente;

    NodoCapa(NodoABBCapa* ref) {
        refCapa = ref;
        siguiente = nullptr;
    }
};

// Nodo del ABB de Capas
struct NodoABBCapa {
    int id;
    NodoMatriz* matriz;
    MatrizDispersa* matrizObj;
    NodoABBCapa* izquierda;
    NodoABBCapa* derecha;

    NodoABBCapa(int _id) {
        id = _id;
        matriz = nullptr;
        matrizObj = nullptr;
        izquierda = nullptr;
        derecha = nullptr;
    }
};

// Imagen con lista de capas
struct Imagen {
    int id;
    NodoCapa* listaCapas;

    Imagen(int _id) {
        id = _id;
        listaCapas = nullptr;
    }
};

// Nodo de Lista Circular Doble de Imágenes
struct NodoImagen {
    Imagen imagen;
    NodoImagen* siguiente;
    NodoImagen* anterior;

    NodoImagen(int idImg) : imagen(idImg) {
        siguiente = nullptr;
        anterior = nullptr;
    }
};

// Nodo de lista de imágenes por usuario
struct NodoImgUsuario {
    int idImagen;
    NodoImgUsuario* siguiente;

    NodoImgUsuario(int id) {
        idImagen = id;
        siguiente = nullptr;
    }
};

// Nodo del ABB de Usuarios
struct NodoABBUsuario {
    string nombre;
    NodoImgUsuario* listaImagenes;
    NodoABBUsuario* izquierda;
    NodoABBUsuario* derecha;

    NodoABBUsuario(string _nombre) {
        nombre = _nombre;
        listaImagenes = nullptr;
        izquierda = nullptr;
        derecha = nullptr;
    }
};

#endif