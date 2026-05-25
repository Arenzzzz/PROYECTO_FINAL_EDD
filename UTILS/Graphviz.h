#ifndef PROYECTO_FINAL_GRAPHVIZ_H
#define PROYECTO_FINAL_GRAPHVIZ_H

#include "../Structs.h"
#include "../ESTRUCTURAS/ABBCapas.h"
#include "../ESTRUCTURAS/ListaCircular.h"
#include "../ESTRUCTURAS/ABBUsuarios.h"
#include <string>
using namespace std;

class Graphviz {
private:
    void ejecutarDot(string archivoDot, string archivoSalida);

public:
    Graphviz();
    void graficarArbolCapas(NodoABBCapa* raiz);
    void graficarListaImagenes(NodoImagen* cabeza);
    void graficarCapa(NodoABBCapa* nodo);
    void graficarImagenYArbol(NodoImagen* imgNodo, NodoABBCapa* raizArbol);
    void graficarArbolUsuarios(NodoABBUsuario* raiz);
};

#endif