#ifndef PROYECTO_FINAL_MATRIZDISPERSA_H
#define PROYECTO_FINAL_MATRIZDISPERSA_H

#include "../Structs.h"

class MatrizDispersa {
private:
    NodoMatriz* cabeza;  // primer nodo de la matriz

    NodoMatriz* buscarOCrearFila(int fila);
    NodoMatriz* buscarOCrearColumna(NodoMatriz* nodoFila, int columna, string color);

public:
    MatrizDispersa();
    void insertarPixel(int fila, int columna, string color);
    string obtenerColor(int fila, int columna);
    NodoMatriz* getCabeza();
};

#endif