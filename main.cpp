#include <iostream>
#include "Structs.h"
#include "ESTRUCTURAS/ABBUsuarios.h"
using namespace std;

int main() {
    ABBUsuarios arbol;

    // Insertar usuarios
    arbol.insertarUsuario("userM");
    arbol.insertarUsuario("userB");
    arbol.insertarUsuario("userY");
    arbol.insertarUsuario("userA");
    arbol.insertarUsuario("userZ");

    // Agregar imágenes a usuarios
    arbol.agregarImagenAUsuario("userA", 13);
    arbol.agregarImagenAUsuario("userA", 14);
    arbol.agregarImagenAUsuario("userY", 8);
    arbol.agregarImagenAUsuario("userY", 9);
    arbol.agregarImagenAUsuario("userY", 10);

    // Verificar búsqueda
    NodoABBUsuario* userA = arbol.buscarUsuario("userA");
    if (userA != nullptr) {
        cout << "Usuario encontrado: " << userA->nombre << endl;
        NodoImgUsuario* img = userA->listaImagenes;
        while (img != nullptr) {
            cout << "  -> Imagen ID: " << img->idImagen << endl;
            img = img->siguiente;
        }
    }

    // Verificar eliminación
    arbol.eliminarUsuario("userB");
    if (arbol.buscarUsuario("userB") == nullptr) {
        cout << "userB eliminado correctamente" << endl;
    }

    // Usuario inexistente
    if (arbol.buscarUsuario("userX") == nullptr) {
        cout << "userX no existe" << endl;
    }

    return 0;
}