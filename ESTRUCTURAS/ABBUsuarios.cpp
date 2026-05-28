#include "ABBUsuarios.h"
#include <iostream>
using namespace std;

ABBUsuarios::ABBUsuarios() {
    raiz = nullptr;
}

void ABBUsuarios::destruir(NodoABBUsuario* nodo) {
    if (nodo == nullptr) return;
    destruir(nodo->izquierda);
    destruir(nodo->derecha);

    // Liberar lista de imágenes del usuario
    NodoImgUsuario* img = nodo->listaImagenes;
    while (img != nullptr) {
        NodoImgUsuario* temp = img;
        img = img->siguiente;
        delete temp;
    }
    delete nodo;
}

ABBUsuarios::~ABBUsuarios() {
    destruir(raiz);
    raiz = nullptr;
}

NodoABBUsuario* ABBUsuarios::getRaiz() {
    return raiz;
}

// Inserción recursiva por nombre
NodoABBUsuario* ABBUsuarios::insertar(NodoABBUsuario* nodo, string nombre) {
    if (nodo == nullptr) {
        return new NodoABBUsuario(nombre);
    }

    if (nombre < nodo->nombre) {
        nodo->izquierda = insertar(nodo->izquierda, nombre);
    } else if (nombre > nodo->nombre) {
        nodo->derecha = insertar(nodo->derecha, nombre);
    }
    // Nombre duplicado, se ignora

    return nodo;
}

// Búsqueda recursiva por nombre
NodoABBUsuario* ABBUsuarios::buscar(NodoABBUsuario* nodo, string nombre) {
    if (nodo == nullptr) return nullptr;
    if (nodo->nombre == nombre) return nodo;

    if (nombre < nodo->nombre) {
        return buscar(nodo->izquierda, nombre);
    } else {
        return buscar(nodo->derecha, nombre);
    }
}

// Retorna el nodo con el valor mínimo del subárbol
NodoABBUsuario* ABBUsuarios::minimoNodo(NodoABBUsuario* nodo) {
    while (nodo->izquierda != nullptr) {
        nodo = nodo->izquierda;
    }
    return nodo;
}

// Eliminación recursiva por nombre
NodoABBUsuario* ABBUsuarios::eliminar(NodoABBUsuario* nodo, string nombre) {
    if (nodo == nullptr) return nullptr;

    if (nombre < nodo->nombre) {
        nodo->izquierda = eliminar(nodo->izquierda, nombre);
    } else if (nombre > nodo->nombre) {
        nodo->derecha = eliminar(nodo->derecha, nombre);
    } else {
        // Nodo encontrado

        // Sin hijo izquierdo
        if (nodo->izquierda == nullptr) {
            NodoABBUsuario* temp = nodo->derecha;
            delete nodo;
            return temp;
        }

        // Sin hijo derecho
        if (nodo->derecha == nullptr) {
            NodoABBUsuario* temp = nodo->izquierda;
            delete nodo;
            return temp;
        }

        // Dos hijos: reemplazar con el mínimo del subárbol derecho
        NodoABBUsuario* temp = minimoNodo(nodo->derecha);
        nodo->nombre = temp->nombre;
        nodo->listaImagenes = temp->listaImagenes;
        nodo->derecha = eliminar(nodo->derecha, temp->nombre);
    }

    return nodo;
}

void ABBUsuarios::insertarUsuario(string nombre) {
    raiz = insertar(raiz, nombre);
}

NodoABBUsuario* ABBUsuarios::buscarUsuario(string nombre) {
    return buscar(raiz, nombre);
}

void ABBUsuarios::eliminarUsuario(string nombre) {
    if (buscar(raiz, nombre) == nullptr) {
        cout << "Usuario " << nombre << " no encontrado." << endl;
        return;
    }
    raiz = eliminar(raiz, nombre);
}

// Agrega imagen a la lista del usuario
void ABBUsuarios::agregarImagenAUsuario(string nombre, int idImagen) {
    NodoABBUsuario* nodo = buscarUsuario(nombre);

    if (nodo == nullptr) {
        cout << "Usuario " << nombre << " no encontrado." << endl;
        return;
    }

    NodoImgUsuario* nueva = new NodoImgUsuario(idImagen);

    // Lista vacía
    if (nodo->listaImagenes == nullptr) {
        nodo->listaImagenes = nueva;
        return;
    }

    // Agregar al final
    NodoImgUsuario* actual = nodo->listaImagenes;
    while (actual->siguiente != nullptr) {
        actual = actual->siguiente;
    }
    actual->siguiente = nueva;
}