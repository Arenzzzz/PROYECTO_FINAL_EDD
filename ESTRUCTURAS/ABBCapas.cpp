#include "ABBCapas.h"
#include <iostream>
using namespace std;

ABBCapas::ABBCapas() {
    raiz = nullptr;
}

NodoABBCapa* ABBCapas::getRaiz() {
    return raiz;
}

// Inserción recursiva por ID
NodoABBCapa* ABBCapas::insertar(NodoABBCapa* nodo, int id) {
    if (nodo == nullptr) {
        return new NodoABBCapa(id);
    }

    if (id < nodo->id) {
        nodo->izquierda = insertar(nodo->izquierda, id);
    } else if (id > nodo->id) {
        nodo->derecha = insertar(nodo->derecha, id);
    }

    return nodo;
}

// Búsqueda recursiva por ID
NodoABBCapa* ABBCapas::buscar(NodoABBCapa* nodo, int id) {
    if (nodo == nullptr) return nullptr;
    if (nodo->id == id) return nodo;

    if (id < nodo->id) {
        return buscar(nodo->izquierda, id);
    } else {
        return buscar(nodo->derecha, id);
    }
}

void ABBCapas::insertarCapa(int id) {
    raiz = insertar(raiz, id);
}

NodoABBCapa* ABBCapas::buscarCapa(int id) {
    return buscar(raiz, id);
}

// Inserta píxel en la matriz de la capa indicada
void ABBCapas::insertarPixelEnCapa(int idCapa, int fila, int columna, string color) {
    NodoABBCapa* nodo = buscarCapa(idCapa);

    if (nodo == nullptr) {
        cout << "Capa " << idCapa << " no encontrada." << endl;
        return;
    }

    if (nodo->matrizObj == nullptr) {
        MatrizDispersa* nuevaMatriz = new MatrizDispersa();
        nodo->matrizObj = nuevaMatriz;
        nodo->matriz = nuevaMatriz->getCabeza();
    }

    nodo->matrizObj->insertarPixel(fila, columna, color);
    nodo->matriz = nodo->matrizObj->getCabeza();
}