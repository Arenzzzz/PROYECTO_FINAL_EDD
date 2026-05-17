#include <iostream>
#include "Structs.h"
#include "ESTRUCTURAS/ABBCapas.h"
#include "ESTRUCTURAS/ListaCircular.h"
#include "ESTRUCTURAS/ABBUsuarios.h"
#include "UTILS/CargaMasiva.h"
using namespace std;

// Instancias globales
ABBCapas arbolCapas;
ListaCircular listaImagenes;
ABBUsuarios arbolUsuarios;
CargaMasiva carga;

void cargarDatos() {
    cout << "========================================" << endl;
    cout << "        Cargando datos del sistema      " << endl;
    cout << "========================================" << endl;
    carga.cargarCapas("ARCHIVOS/capas.cap", arbolCapas);
    carga.cargarImagenes("ARCHIVOS/imagenes.im", listaImagenes, arbolCapas);
    carga.cargarUsuarios("ARCHIVOS/usuarios.usr", arbolUsuarios, listaImagenes);
    cout << "Datos cargados correctamente." << endl;
}

void menuCRUDUsuarios() {
    int opcion;
    cout << "\n========== CRUD USUARIOS ==========" << endl;
    cout << "1. Agregar usuario" << endl;
    cout << "2. Eliminar usuario" << endl;
    cout << "3. Buscar usuario" << endl;
    cout << "0. Volver" << endl;
    cout << "Opcion: ";
    cin >> opcion;

    string nombre;
    switch (opcion) {
        case 1:
            cout << "Nombre del usuario: ";
            cin >> nombre;
            arbolUsuarios.insertarUsuario(nombre);
            cout << "Usuario " << nombre << " agregado." << endl;
            break;
        case 2:
            cout << "Nombre del usuario a eliminar: ";
            cin >> nombre;
            arbolUsuarios.eliminarUsuario(nombre);
            break;
        case 3:
            cout << "Nombre del usuario a buscar: ";
            cin >> nombre;
            if (arbolUsuarios.buscarUsuario(nombre) != nullptr) {
                cout << "Usuario " << nombre << " encontrado." << endl;
            } else {
                cout << "Usuario " << nombre << " no existe." << endl;
            }
            break;
        case 0:
            break;
        default:
            cout << "Opcion invalida." << endl;
    }
}

void menuCRUDImagenes() {
    int opcion;
    cout << "\n========== CRUD IMAGENES ==========" << endl;
    cout << "1. Agregar imagen" << endl;
    cout << "2. Eliminar imagen" << endl;
    cout << "0. Volver" << endl;
    cout << "Opcion: ";
    cin >> opcion;

    switch (opcion) {
        case 1: {
            int idImg;
            string nombreUsuario;
            cout << "ID de la imagen: ";
            cin >> idImg;
            cout << "Usuario al que pertenece: ";
            cin >> nombreUsuario;
            if (listaImagenes.buscarImagen(idImg) != nullptr) {
                cout << "Imagen " << idImg << " ya existe." << endl;
            } else {
                listaImagenes.insertarImagen(idImg);
                arbolUsuarios.agregarImagenAUsuario(nombreUsuario, idImg);
                cout << "Imagen " << idImg << " agregada a " << nombreUsuario << "." << endl;
            }
            break;
        }
        case 2: {
            int idImg;
            cout << "ID de la imagen a eliminar: ";
            cin >> idImg;
            listaImagenes.eliminarImagen(idImg);
            break;
        }
        case 0:
            break;
        default:
            cout << "Opcion invalida." << endl;
    }
}

void menuGeneracion() {
    int opcion;
    cout << "\n========== GENERACION DE IMAGENES ==========" << endl;
    cout << "1. Por recorrido limitado" << endl;
    cout << "2. Por lista de imagenes" << endl;
    cout << "3. Por capa" << endl;
    cout << "4. Por usuario" << endl;
    cout << "0. Volver" << endl;
    cout << "Opcion: ";
    cin >> opcion;

    switch (opcion) {
        case 1:
            cout << "[Proximamente] Generacion por recorrido limitado" << endl;
            break;
        case 2:
            cout << "[Proximamente] Generacion por lista de imagenes" << endl;
            break;
        case 3:
            cout << "[Proximamente] Generacion por capa" << endl;
            break;
        case 4:
            cout << "[Proximamente] Generacion por usuario" << endl;
            break;
        case 0:
            break;
        default:
            cout << "Opcion invalida." << endl;
    }
}

void menuEstadoMemoria() {
    int opcion;
    cout << "\n========== ESTADO DE MEMORIA ==========" << endl;
    cout << "1. Ver lista de imagenes" << endl;
    cout << "2. Ver arbol de capas" << endl;
    cout << "3. Ver capa especifica" << endl;
    cout << "4. Ver imagen y arbol de capas" << endl;
    cout << "5. Ver arbol de usuarios" << endl;
    cout << "0. Volver" << endl;
    cout << "Opcion: ";
    cin >> opcion;

    switch (opcion) {
        case 1:
            cout << "[Proximamente] Lista circular de imagenes" << endl;
            break;
        case 2:
            cout << "[Proximamente] Arbol de capas" << endl;
            break;
        case 3: {
            int idCapa;
            cout << "ID de la capa: ";
            cin >> idCapa;
            cout << "[Proximamente] Capa " << idCapa << endl;
            break;
        }
        case 4: {
            int idImg;
            cout << "ID de la imagen: ";
            cin >> idImg;
            cout << "[Proximamente] Imagen " << idImg << " y su arbol" << endl;
            break;
        }
        case 5:
            cout << "[Proximamente] Arbol de usuarios" << endl;
            break;
        case 0:
            break;
        default:
            cout << "Opcion invalida." << endl;
    }
}

int main() {
    // Carga automática al iniciar
    cargarDatos();

    int opcion;
    do {
        cout << "\n========================================" << endl;
        cout << "   GENERADOR DE IMAGENES POR CAPAS      " << endl;
        cout << "========================================" << endl;
        cout << "1. Generacion de Imagenes" << endl;
        cout << "2. CRUD Usuarios" << endl;
        cout << "3. CRUD Imagenes" << endl;
        cout << "4. Estado de Memoria" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: menuGeneracion(); break;
            case 2: menuCRUDUsuarios(); break;
            case 3: menuCRUDImagenes(); break;
            case 4: menuEstadoMemoria(); break;
            case 0: cout << "Saliendo..." << endl; break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (opcion != 0);

    return 0;
}