#include "ListaCircular.h"
#include <iostream>
using namespace std;

ListaCircular::ListaCircular() {
    cabeza = nullptr;
}

NodoImagen* ListaCircular::getCabeza() {
    return cabeza;
}

bool ListaCircular::estaVacia() {
    return cabeza == nullptr;
}

// Inserta imagen ordenada por ID
void ListaCircular::insertarImagen(int id) {
    if (buscarImagen(id) != nullptr) {
        cout << "Imagen " << id << " ya existe." << endl;
        return;
    }

    NodoImagen* nuevo = new NodoImagen(id);

    // Lista vacía
    if (cabeza == nullptr) {
        cabeza = nuevo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
        return;
    }

    // Insertar antes de cabeza si es el menor
    if (id < cabeza->imagen.id) {
        NodoImagen* ultimo = cabeza->anterior;
        nuevo->siguiente = cabeza;
        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
        cabeza->anterior = nuevo;
        cabeza = nuevo;
        return;
    }

    // Buscar posición correcta
    NodoImagen* actual = cabeza;
    while (actual->siguiente != cabeza && actual->siguiente->imagen.id < id) {
        actual = actual->siguiente;
    }

    NodoImagen* siguiente = actual->siguiente;
    actual->siguiente = nuevo;
    nuevo->anterior = actual;
    nuevo->siguiente = siguiente;
    siguiente->anterior = nuevo;
}

// Busca imagen por ID, retorna nullptr si no existe
NodoImagen* ListaCircular::buscarImagen(int id) {
    if (cabeza == nullptr) return nullptr;

    NodoImagen* actual = cabeza;
    do {
        if (actual->imagen.id == id) return actual;
        actual = actual->siguiente;
    } while (actual != cabeza);

    return nullptr;
}

// Elimina imagen por ID
void ListaCircular::eliminarImagen(int id) {
    if (cabeza == nullptr) {
        cout << "Lista vacia." << endl;
        return;
    }

    NodoImagen* nodo = buscarImagen(id);
    if (nodo == nullptr) {
        cout << "Imagen " << id << " no encontrada." << endl;
        return;
    }

    // Solo un nodo en la lista
    if (nodo->siguiente == nodo) {
        cabeza = nullptr;
        delete nodo;
        return;
    }

    // Actualizar cabeza si es necesario
    if (nodo == cabeza) {
        cabeza = cabeza->siguiente;
    }

    nodo->anterior->siguiente = nodo->siguiente;
    nodo->siguiente->anterior = nodo->anterior;
    delete nodo;
}

// Agrega referencia de capa a la lista de capas de una imagen
void ListaCircular::agregarCapaAImagen(int idImagen, NodoABBCapa* refCapa) {
    NodoImagen* nodo = buscarImagen(idImagen);

    if (nodo == nullptr) {
        cout << "Imagen " << idImagen << " no encontrada." << endl;
        return;
    }

    NodoCapa* nuevaCapa = new NodoCapa(refCapa);

    // Lista de capas vacía
    if (nodo->imagen.listaCapas == nullptr) {
        nodo->imagen.listaCapas = nuevaCapa;
        return;
    }

    // Agregar al final de la lista de capas
    NodoCapa* actual = nodo->imagen.listaCapas;
    while (actual->siguiente != nullptr) {
        actual = actual->siguiente;
    }
    actual->siguiente = nuevaCapa;
}