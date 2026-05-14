#ifndef PROYECTO_FINAL_STRUCTS_H
#define PROYECTO_FINAL_STRUCTS_H

#include <string>
using namespace std;

// NODO de la Matriz Dispersa
struct NodoMatriz {
    int fila;
    int columna;
    string color;
    NodoMatriz* derecha;
    NodoMatriz* abajo;

    NodoMatriz(int f, int c, string col) {
        fila = f;
        columna = c;
        color = col;
        derecha = nullptr;
        abajo = nullptr;
    }
};

// NODO del ABB de Capas
// (forward declaration, la capa vive dentro del nodo)
struct NodoABBCapa;

// NODO de la lista de capas de una imagen
// Solo guarda un PUNTERO al nodo del ABB, no una copia
struct NodoCapa {
    NodoABBCapa* refCapa;
    NodoCapa* siguiente;

    NodoCapa(NodoABBCapa* ref) {
        refCapa = ref;
        siguiente = nullptr;
    }
};

// NODO del ABB de Capas
struct NodoABBCapa {
    int id;
    NodoMatriz* matriz;      // cabeza de la matriz dispersa
    NodoABBCapa* izquierda;
    NodoABBCapa* derecha;

    NodoABBCapa(int _id) {
        id = _id;
        matriz = nullptr;
        izquierda = nullptr;
        derecha = nullptr;
    }
};

// IMAGEN
struct Imagen {
    int id;
    NodoCapa* listaCapas;    // lista de capas en orden de superposición

    Imagen(int _id) {
        id = _id;
        listaCapas = nullptr;
    }
};

// NODO de la Lista Circular Doble de Imágenes
struct NodoImagen {
    Imagen imagen;
    NodoImagen* siguiente;
    NodoImagen* anterior;

    NodoImagen(int idImg) : imagen(idImg) {
        siguiente = nullptr;
        anterior = nullptr;
    }
};

// NODO de la lista de imágenes de un usuario
struct NodoImgUsuario {
    int idImagen;
    NodoImgUsuario* siguiente;

    NodoImgUsuario(int id) {
        idImagen = id;
        siguiente = nullptr;
    }
};

// NODO del ABB de Usuarios
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