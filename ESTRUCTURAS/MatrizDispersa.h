#ifndef PROYECTO_FINAL_MATRIZDISPERSA_H
#define PROYECTO_FINAL_MATRIZDISPERSA_H

#include <string>
using namespace std;

// Nodo de la Matriz Dispersa
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

class MatrizDispersa {
private:
    NodoMatriz* cabeza;

    NodoMatriz* buscarOCrearFila(int fila);
    NodoMatriz* buscarOCrearColumna(NodoMatriz* nodoFila, int columna, string color);

public:
    MatrizDispersa();
    ~MatrizDispersa(); // Destructor
    void insertarPixel(int fila, int columna, string color);
    string obtenerColor(int fila, int columna);
    NodoMatriz* getCabeza();
};

#endif