#include "CargaMasiva.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

CargaMasiva::CargaMasiva() {}

// Elimina espacios al inicio y al final de un string
string CargaMasiva::trim(string str) {
    int inicio = 0;
    int fin = str.size() - 1;
    while (inicio <= fin && (str[inicio] == ' ' || str[inicio] == '\t' || str[inicio] == '\r')) inicio++;
    while (fin >= inicio && (str[fin] == ' ' || str[fin] == '\t' || str[fin] == '\r')) fin--;
    return str.substr(inicio, fin - inicio + 1);
}

// Lee archivo .cap e inserta capas en el ABB
void CargaMasiva::cargarCapas(string ruta, ABBCapas& arbolCapas) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Error al abrir: " << ruta << endl;
        return;
    }

    string linea;
    int idCapa = -1;

    while (getline(archivo, linea)) {
        linea = trim(linea);
        if (linea.empty()) continue;

        // Línea con solo "}" cierra la capa
        if (linea == "}") {
            idCapa = -1;
            continue;
        }

        // Línea con "{" define el ID de la capa
        if (linea.find('{') != string::npos) {
            string idStr = linea.substr(0, linea.find('{'));
            idCapa = stoi(trim(idStr));
            arbolCapas.insertarCapa(idCapa);
            continue;
        }

        // Línea de píxel: fila,columna,color;
        if (idCapa != -1 && linea.find(',') != string::npos) {
            // Quitar el punto y coma final
            if (!linea.empty() && linea.back() == ';') {
                linea.pop_back();
            }

            stringstream ss(linea);
            string filaStr, colStr, color;
            getline(ss, filaStr, ',');
            getline(ss, colStr, ',');
            getline(ss, color, ',');

            int fila = stoi(trim(filaStr));
            int col = stoi(trim(colStr));
            color = trim(color);

            arbolCapas.insertarPixelEnCapa(idCapa, fila, col, color);
        }
    }

    archivo.close();
    cout << "Capas cargadas correctamente." << endl;
}

// Lee archivo .im e inserta imágenes en la lista circular
void CargaMasiva::cargarImagenes(string ruta, ListaCircular& listaImagenes, ABBCapas& arbolCapas) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Error al abrir: " << ruta << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        linea = trim(linea);
        if (linea.empty()) continue;

        // Formato: id{capa1,capa2,...}
        int posLlave = linea.find('{');
        int posCierre = linea.find('}');
        if (posLlave == string::npos || posCierre == string::npos) continue;

        string idStr = linea.substr(0, posLlave);
        int idImagen = stoi(trim(idStr));
        listaImagenes.insertarImagen(idImagen);

        // Extraer lista de capas
        string capasStr = linea.substr(posLlave + 1, posCierre - posLlave - 1);
        capasStr = trim(capasStr);
        if (capasStr.empty()) continue;

        stringstream ss(capasStr);
        string idCapaStr;
        while (getline(ss, idCapaStr, ',')) {
            idCapaStr = trim(idCapaStr);
            if (idCapaStr.empty()) continue;

            int idCapa = stoi(idCapaStr);
            NodoABBCapa* nodoCapa = arbolCapas.buscarCapa(idCapa);

            if (nodoCapa != nullptr) {
                listaImagenes.agregarCapaAImagen(idImagen, nodoCapa);
            } else {
                cout << "Capa " << idCapa << " no encontrada para imagen " << idImagen << endl;
            }
        }
    }

    archivo.close();
    cout << "Imagenes cargadas correctamente." << endl;
}

// Lee archivo .usr e inserta usuarios en el ABB
void CargaMasiva::cargarUsuarios(string ruta, ABBUsuarios& arbolUsuarios, ListaCircular& listaImagenes) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Error al abrir: " << ruta << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        linea = trim(linea);
        if (linea.empty()) continue;

        // Formato: nombre:img1,img2;
        int posDosPuntos = linea.find(':');
        if (posDosPuntos == string::npos) continue;

        string nombre = trim(linea.substr(0, posDosPuntos));
        string resto = linea.substr(posDosPuntos + 1);

        // Quitar punto y coma final
        if (!resto.empty() && resto.back() == ';') resto.pop_back();
        resto = trim(resto);

        arbolUsuarios.insertarUsuario(nombre);

        if (resto.empty()) continue;

        stringstream ss(resto);
        string idImgStr;
        while (getline(ss, idImgStr, ',')) {
            idImgStr = trim(idImgStr);
            if (idImgStr.empty()) continue;

            int idImg = stoi(idImgStr);
            if (listaImagenes.buscarImagen(idImg) != nullptr) {
                arbolUsuarios.agregarImagenAUsuario(nombre, idImg);
            } else {
                cout << "Imagen " << idImg << " no encontrada para usuario " << nombre << endl;
            }
        }
    }

    archivo.close();
    cout << "Usuarios cargados correctamente." << endl;
}