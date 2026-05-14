#include "MatrizDispersa.h"

MatrizDispersa::MatrizDispersa() {
    cabeza = nullptr;
}

NodoMatriz* MatrizDispersa::getCabeza() {
    return cabeza;
}

// Busca fila por número, la crea si no existe
NodoMatriz* MatrizDispersa::buscarOCrearFila(int fila) {
    if (cabeza == nullptr) {
        cabeza = new NodoMatriz(fila, -1, "");
        return cabeza;
    }

    NodoMatriz* actual = cabeza;
    NodoMatriz* anterior = nullptr;

    while (actual != nullptr && actual->fila < fila) {
        anterior = actual;
        actual = actual->abajo;
    }

    if (actual != nullptr && actual->fila == fila) {
        return actual;
    }

    NodoMatriz* nueva = new NodoMatriz(fila, -1, "");
    nueva->abajo = actual;

    if (anterior == nullptr) {
        cabeza = nueva;
    } else {
        anterior->abajo = nueva;
    }

    return nueva;
}

// Busca columna en la fila dada, la crea si no existe
NodoMatriz* MatrizDispersa::buscarOCrearColumna(NodoMatriz* nodoFila, int columna, string color) {
    NodoMatriz* actual = nodoFila->derecha;
    NodoMatriz* anterior = nodoFila;

    while (actual != nullptr && actual->columna < columna) {
        anterior = actual;
        actual = actual->derecha;
    }

    if (actual != nullptr && actual->columna == columna) {
        actual->color = color;
        return actual;
    }

    NodoMatriz* nueva = new NodoMatriz(nodoFila->fila, columna, color);
    nueva->derecha = actual;
    anterior->derecha = nueva;

    return nueva;
}

// Inserta píxel en posición (fila, columna)
void MatrizDispersa::insertarPixel(int fila, int columna, string color) {
    NodoMatriz* nodoFila = buscarOCrearFila(fila);
    buscarOCrearColumna(nodoFila, columna, color);
}

// Retorna color del píxel en (fila, columna), vacío si no existe
string MatrizDispersa::obtenerColor(int fila, int columna) {
    NodoMatriz* actual = cabeza;

    while (actual != nullptr && actual->fila < fila) {
        actual = actual->abajo;
    }

    if (actual == nullptr || actual->fila != fila) return "";

    NodoMatriz* col = actual->derecha;
    while (col != nullptr && col->columna < columna) {
        col = col->derecha;
    }

    if (col == nullptr || col->columna != columna) return "";

    return col->color;
}