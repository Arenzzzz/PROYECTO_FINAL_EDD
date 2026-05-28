#ifndef PROYECTO_FINAL_ABBUSUARIOS_H
#define PROYECTO_FINAL_ABBUSUARIOS_H

#include "../Structs.h"

class ABBUsuarios {
private:
    NodoABBUsuario* raiz;

    NodoABBUsuario* insertar(NodoABBUsuario* nodo, string nombre);
    NodoABBUsuario* buscar(NodoABBUsuario* nodo, string nombre);
    NodoABBUsuario* minimoNodo(NodoABBUsuario* nodo);
    NodoABBUsuario* eliminar(NodoABBUsuario* nodo, string nombre);

    void destruir(NodoABBUsuario* nodo);

public:
    ABBUsuarios();
    ~ABBUsuarios(); // Destructor
    void insertarUsuario(string nombre);
    NodoABBUsuario* buscarUsuario(string nombre);
    void eliminarUsuario(string nombre);
    void agregarImagenAUsuario(string nombre, int idImagen);
    NodoABBUsuario* getRaiz();
};

#endif