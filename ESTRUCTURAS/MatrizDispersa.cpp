#include "MatrizDispersa.h"

// Constructor: inicializa la cabeza en nulo
MatrizDispersa::MatrizDispersa() {
    cabeza = nullptr;
}

// Retorna la cabeza (para usarla al generar imágenes)
NodoMatriz* MatrizDispersa::getCabeza() {
    return cabeza;
}

// Busca la fila, si no existe la crea en orden
NodoMatriz* MatrizDispersa::buscarOCrearFila(int fila) {
    // Lista vacía: creamos el primer nodo de fila
    if (cabeza == nullptr) {
        cabeza = new NodoMatriz(fila, -1, "");
        return cabeza;
    }

    NodoMatriz* actual = cabeza;
    NodoMatriz* anterior = nullptr;

    // Recorre buscando la fila
    while (actual != nullptr && actual->fila < fila) {
        anterior = actual;
        actual = actual->abajo;
    }

    // Ya existe esa fila
    if (actual != nullptr && actual->fila == fila) {
        return actual;
    }

    // No existe, se crea en la posición correcta
    NodoMatriz* nueva = new NodoMatriz(fila, -1, "");
    nueva->abajo = actual;

    if (anterior == nullptr) {
        cabeza = nueva;
    } else {
        anterior->abajo = nueva;
    }

    return nueva;
}

// Busca la columna en una fila, si no existe se crea en orden
NodoMatriz* MatrizDispersa::buscarOCrearColumna(NodoMatriz* nodoFila, int columna, string color) {
    NodoMatriz* actual = nodoFila->derecha;
    NodoMatriz* anterior = nodoFila;

    // Se recorre buscando la columna
    while (actual != nullptr && actual->columna < columna) {
        anterior = actual;
        actual = actual->derecha;
    }

    // Ya existe esa columna, se actualiza color
    if (actual != nullptr && actual->columna == columna) {
        actual->color = color;
        return actual;
    }

    // No existe, se crea en la posición correcta
    NodoMatriz* nueva = new NodoMatriz(nodoFila->fila, columna, color);
    nueva->derecha = actual;
    anterior->derecha = nueva;

    return nueva;
}

// Inserta un píxel en la posición (fila, columna) con el color dado
void MatrizDispersa::insertarPixel(int fila, int columna, string color) {
    NodoMatriz* nodoFila = buscarOCrearFila(fila);
    buscarOCrearColumna(nodoFila, columna, color);
}

// Retorna el color de un píxel, o "" si no existe
string MatrizDispersa::obtenerColor(int fila, int columna) {
    NodoMatriz* actual = cabeza;

    // Busca la fila
    while (actual != nullptr && actual->fila < fila) {
        actual = actual->abajo;
    }

    if (actual == nullptr || actual->fila != fila) return "";

    // Busca la columna
    NodoMatriz* col = actual->derecha;
    while (col != nullptr && col->columna < columna) {
        col = col->derecha;
    }

    if (col == nullptr || col->columna != columna) return "";

    return col->color;
}