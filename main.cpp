#include <iostream>
#include "Structs.h"
#include "ESTRUCTURAS/ABBCapas.h"
#include "ESTRUCTURAS/ListaCircular.h"
#include "ESTRUCTURAS/ABBUsuarios.h"
#include "UTILS/CargaMasiva.h"
#include "UTILS/Graphviz.h"
#include "UTILS/GeneradorImagenes.h"
using namespace std;

// Instancias globales
ABBCapas arbolCapas;
ListaCircular listaImagenes;
ABBUsuarios arbolUsuarios;
CargaMasiva carga;
Graphviz graphviz;
GeneradorImagenes generador;

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
    cout << "Opción: ";
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
            cout << "Opcion inválida." << endl;
    }
}

void menuCRUDImagenes() {
    int opcion;
    cout << "\n========== CRUD IMÁGENES ==========" << endl;
    cout << "1. Agregar imagen" << endl;
    cout << "2. Eliminar imagen" << endl;
    cout << "0. Volver" << endl;
    cout << "Opción: ";
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
            cout << "Opción inválida." << endl;
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
        case 1: {
            int limite, tipo;
            cout << "Numero de capas a utilizar: ";
            cin >> limite;
            cout << "Tipo de recorrido:" << endl;
            cout << "  1. Inorden" << endl;
            cout << "  2. Preorden" << endl;
            cout << "  3. Postorden" << endl;
            cout << "Opcion: ";
            cin >> tipo;
            generador.generarPorRecorridoLimitado(arbolCapas.getRaiz(), limite, tipo);
            break;
        }
        case 2: {
            int idImg;
            cout << "ID de la imagen: ";
            cin >> idImg;
            NodoImagen* img = listaImagenes.buscarImagen(idImg);
            if (img == nullptr) {
                cout << "Imagen " << idImg << " no encontrada." << endl;
            } else {
                generador.generarPorListaImagenes(img);
            }
            break;
        }
        case 3: {
            int idCapa;
            cout << "ID de la capa: ";
            cin >> idCapa;
            generador.generarPorCapa(arbolCapas.buscarCapa(idCapa));
            break;
        }
        case 4: {
            string nombreUsuario;
            int idImg;
            cout << "Nombre del usuario: ";
            cin >> nombreUsuario;
            NodoABBUsuario* usuario = arbolUsuarios.buscarUsuario(nombreUsuario);
            if (usuario == nullptr) {
                cout << "Usuario no encontrado." << endl;
                break;
            }
            cout << "Imagenes del usuario: ";
            NodoImgUsuario* imgUsr = usuario->listaImagenes;
            while (imgUsr != nullptr) {
                cout << imgUsr->idImagen << " ";
                imgUsr = imgUsr->siguiente;
            }
            cout << endl;
            cout << "ID de la imagen a generar: ";
            cin >> idImg;
            generador.generarPorUsuario(usuario, idImg, listaImagenes);
            break;
        }
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
            graphviz.graficarListaImagenes(listaImagenes.getCabeza());
            break;
        case 2:
            graphviz.graficarArbolCapas(arbolCapas.getRaiz());
            break;
        case 3: {
            int idCapa;
            cout << "ID de la capa: ";
            cin >> idCapa;
            graphviz.graficarCapa(arbolCapas.buscarCapa(idCapa));
            break;
        }
        case 4: {
            int idImg;
            cout << "ID de la imagen: ";
            cin >> idImg;
            graphviz.graficarImagenYArbol(listaImagenes.buscarImagen(idImg), arbolCapas.getRaiz());
            break;
        }
        case 5:
            graphviz.graficarArbolUsuarios(arbolUsuarios.getRaiz());
            break;
        case 0:
            break;
        default:
            cout << "Opcion invalida." << endl;
    }
}

void menuCargaMasiva() {
    int opcion;
    cout << "\n========== CARGA MASIVA ==========" << endl;
    cout << "1. Cargar Capas (.cap)" << endl;
    cout << "2. Cargar Imagenes (.im)" << endl;
    cout << "3. Cargar Usuarios (.usr)" << endl;
    cout << "4. Cargar Todo (orden correcto)" << endl;
    cout << "0. Volver" << endl;
    cout << "Opcion: ";
    cin >> opcion;

    string ruta;
    switch (opcion) {
        case 1:
            ruta = carga.seleccionarArchivo("Seleccionar archivo de Capas", "cap");
            if (!ruta.empty()) carga.cargarCapas(ruta, arbolCapas);
            break;
        case 2:
            ruta = carga.seleccionarArchivo("Seleccionar archivo de Imagenes", "im");
            if (!ruta.empty()) carga.cargarImagenes(ruta, listaImagenes, arbolCapas);
            break;
        case 3:
            ruta = carga.seleccionarArchivo("Seleccionar archivo de Usuarios", "usr");
            if (!ruta.empty()) carga.cargarUsuarios(ruta, arbolUsuarios, listaImagenes);
            break;
        case 4:
            carga.cargarCapas("ARCHIVOS/capas.cap", arbolCapas);
            carga.cargarImagenes("ARCHIVOS/imagenes.im", listaImagenes, arbolCapas);
            carga.cargarUsuarios("ARCHIVOS/usuarios.usr", arbolUsuarios, listaImagenes);
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
        cout << "   GENERADOR DE IMÁGENES POR CAPAS      " << endl;
        cout << "========================================" << endl;
        cout << "1. Generación de Imágenes" << endl;
        cout << "2. CRUD Usuarios" << endl;
        cout << "3. CRUD Imágenes" << endl;
        cout << "4. Estado de Memoria" << endl;
        cout << "5. Carga de Datos" << endl;
        cout << "0. Salir" << endl;
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: menuGeneracion(); break;
            case 2: menuCRUDUsuarios(); break;
            case 3: menuCRUDImagenes(); break;
            case 4: menuEstadoMemoria(); break;
            case 5: menuCargaMasiva(); break;
            case 0: cout << "Saliendo..." << endl; break;
            default: cout << "Opción inválida." << endl;
        }
    } while (opcion != 0);

    return 0;
}