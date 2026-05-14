#include <iostream>
#include "Structs.h"
#include "ESTRUCTURAS/MatrizDispersa.h"
using namespace std;

int main() {
    MatrizDispersa matriz;

    // Insertamos algunos píxeles (simulando el corazón del PDF)
    matriz.insertarPixel(2, 4, "#e74c3c");
    matriz.insertarPixel(2, 5, "#e74c3c");
    matriz.insertarPixel(3, 3, "#e74c3c");
    matriz.insertarPixel(3, 4, "#e74c3c");
    matriz.insertarPixel(3, 5, "#e74c3c");
    matriz.insertarPixel(4, 3, "#e74c3c");
    matriz.insertarPixel(4, 4, "#e74c3c");
    matriz.insertarPixel(4, 5, "#e74c3c");

    // Verificamos que los colores se guardaron bien
    cout << "Pixel (2,4): " << matriz.obtenerColor(2, 4) << endl;
    cout << "Pixel (3,3): " << matriz.obtenerColor(3, 3) << endl;
    cout << "Pixel (1,1): " << matriz.obtenerColor(1, 1) << endl; // vacío

    return 0;
}
