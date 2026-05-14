#ifndef PROYECTO_FINAL_ABBCAPAS_H
#define PROYECTO_FINAL_ABBCAPAS_H

#include "../Structs.h"
#include "MatrizDispersa.h"

class ABBCapas {
private:
    NodoABBCapa* raiz;

    NodoABBCapa* insertar(NodoABBCapa* nodo, int id);
    NodoABBCapa* buscar(NodoABBCapa* nodo, int id);

public:
    ABBCapas();
    void insertarCapa(int id);
    NodoABBCapa* buscarCapa(int id);
    void insertarPixelEnCapa(int idCapa, int fila, int columna, string color);
    NodoABBCapa* getRaiz();
};

#endif