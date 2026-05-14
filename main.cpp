#include <iostream>
#include "Structs.h"
#include "ESTRUCTURAS/MatrizDispersa.h"
#include "ESTRUCTURAS/ABBCapas.h"
using namespace std;

int main() {
    ABBCapas arbol;

    // Insertar capas
    arbol.insertarCapa(3);
    arbol.insertarCapa(2);
    arbol.insertarCapa(5);
    arbol.insertarCapa(1);
    arbol.insertarCapa(4);

    // Insertar píxeles en capa 3
    arbol.insertarPixelEnCapa(3, 2, 4, "#e74c3c");
    arbol.insertarPixelEnCapa(3, 2, 5, "#e74c3c");
    arbol.insertarPixelEnCapa(3, 3, 3, "#e74c3c");

    // Buscar capas
    NodoABBCapa* capa3 = arbol.buscarCapa(3);
    NodoABBCapa* capa99 = arbol.buscarCapa(99);

    if (capa3 != nullptr) {
        cout << "Capa 3 encontrada, ID: " << capa3->id << endl;
        cout << "Pixel (2,4): " << capa3->matrizObj->obtenerColor(2, 4) << endl;
    }

    if (capa99 == nullptr) {
        cout << "Capa 99 no existe" << endl;
    }

    return 0;
}