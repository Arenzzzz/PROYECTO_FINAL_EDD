#include <iostream>
#include "Structs.h"
#include "ESTRUCTURAS/ABBCapas.h"
#include "ESTRUCTURAS/ListaCircular.h"
#include "ESTRUCTURAS/ABBUsuarios.h"
#include "UTILS/CargaMasiva.h"
using namespace std;

int main() {
    ABBCapas arbolCapas;
    ListaCircular listaImagenes;
    ABBUsuarios arbolUsuarios;
    CargaMasiva carga;

    // Carga masiva en orden correcto
    carga.cargarCapas("ARCHIVOS/capas.cap", arbolCapas);
    carga.cargarImagenes("ARCHIVOS/imagenes.im", listaImagenes, arbolCapas);
    carga.cargarUsuarios("ARCHIVOS/usuarios.usr", arbolUsuarios, listaImagenes);

    cout << "\n--- Verificando Capas ---" << endl;
    NodoABBCapa* capa1 = arbolCapas.buscarCapa(1);
    if (capa1 != nullptr) {
        cout << "Capa 1 encontrada" << endl;
        cout << "Pixel (2,4): " << capa1->matrizObj->obtenerColor(2, 4) << endl;
    }

    cout << "\n--- Verificando Imagenes ---" << endl;
    NodoImagen* img1 = listaImagenes.buscarImagen(1);
    if (img1 != nullptr) {
        cout << "Imagen 1 encontrada, capas:" << endl;
        NodoCapa* cap = img1->imagen.listaCapas;
        while (cap != nullptr) {
            cout << "  -> Capa ID: " << cap->refCapa->id << endl;
            cap = cap->siguiente;
        }
    }

    cout << "\n--- Verificando Usuarios ---" << endl;
    NodoABBUsuario* userA = arbolUsuarios.buscarUsuario("userA");
    if (userA != nullptr) {
        cout << "Usuario userA encontrado, imagenes:" << endl;
        NodoImgUsuario* img = userA->listaImagenes;
        while (img != nullptr) {
            cout << "  -> Imagen ID: " << img->idImagen << endl;
            img = img->siguiente;
        }
    }

    return 0;
}