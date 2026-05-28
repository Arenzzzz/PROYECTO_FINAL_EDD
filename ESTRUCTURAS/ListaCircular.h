#ifndef PROYECTO_FINAL_LISTACIRCULAR_H
#define PROYECTO_FINAL_LISTACIRCULAR_H

#include "../Structs.h"
#include "ABBCapas.h"

class ListaCircular {
private:
    NodoImagen* cabeza;

public:
    ListaCircular();
    ~ListaCircular(); // Destructor
    void insertarImagen(int id);
    NodoImagen* buscarImagen(int id);
    void eliminarImagen(int id);
    void agregarCapaAImagen(int idImagen, NodoABBCapa* refCapa);
    NodoImagen* getCabeza();
    bool estaVacia();
};

#endif