#include <iostream>
#include "Structs.h"
#include "ESTRUCTURAS/MatrizDispersa.h"
#include "ESTRUCTURAS/ABBCapas.h"
#include "ESTRUCTURAS/ListaCircular.h"
using namespace std;

int main() {
    ABBCapas arbol;
    ListaCircular lista;

    // Insertar capas en el ABB
    arbol.insertarCapa(1);
    arbol.insertarCapa(2);
    arbol.insertarCapa(3);

    // Insertar imágenes en la lista circular
    lista.insertarImagen(10);
    lista.insertarImagen(5);
    lista.insertarImagen(20);

    // Agregar capas a imagen 10
    lista.agregarCapaAImagen(10, arbol.buscarCapa(1));
    lista.agregarCapaAImagen(10, arbol.buscarCapa(2));

    // Agregar capas a imagen 5
    lista.agregarCapaAImagen(5, arbol.buscarCapa(3));

    // Verificar
    NodoImagen* img10 = lista.buscarImagen(10);
    NodoImagen* img99 = lista.buscarImagen(99);

    if (img10 != nullptr) {
        cout << "Imagen 10 encontrada" << endl;
        NodoCapa* cap = img10->imagen.listaCapas;
        while (cap != nullptr) {
            cout << "  -> Capa ID: " << cap->refCapa->id << endl;
            cap = cap->siguiente;
        }
    }

    if (img99 == nullptr) {
        cout << "Imagen 99 no existe" << endl;
    }

    return 0;
}