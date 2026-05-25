#include "GeneradorImagenes.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

GeneradorImagenes::GeneradorImagenes() {}

// Limpia el canvas para una nueva generación
void GeneradorImagenes::limpiarCanvas() {
    canvas.clear();
}

// Convierte componente hex a entero (ej: "ff" -> 255)
int GeneradorImagenes::hexToInt(string hex) {
    int valor = 0;
    for (char c : hex) {
        valor *= 16;
        if (c >= '0' && c <= '9') valor += c - '0';
        else if (c >= 'a' && c <= 'f') valor += c - 'a' + 10;
        else if (c >= 'A' && c <= 'F') valor += c - 'A' + 10;
    }
    return valor;
}

// Agrega los píxeles de una capa al canvas
// Si ya existe un píxel en esa posición, la capa nueva lo sobreescribe
void GeneradorImagenes::agregarCapaAlCanvas(NodoABBCapa* nodo) {
    if (nodo == nullptr || nodo->matriz == nullptr) return;

    NodoMatriz* fila = nodo->matriz;
    while (fila != nullptr) {
        NodoMatriz* col = fila->derecha;
        while (col != nullptr) {
            canvas[{col->fila, col->columna}] = col->color;
            col = col->derecha;
        }
        fila = fila->abajo;
    }
}

// Escribe el canvas como archivo PPM
void GeneradorImagenes::escribirPPM(string nombreArchivo) {
    if (canvas.empty()) {
        cout << "Canvas vacio, no se genera imagen." << endl;
        return;
    }

    // Determinar dimensiones
    int maxFila = 0, maxCol = 0;
    for (auto& par : canvas) {
        maxFila = max(maxFila, par.first.first);
        maxCol = max(maxCol, par.first.second);
    }

    int alto = maxFila + 1;
    int ancho = maxCol + 1;
    int escala = 20; // cada píxel = 20x20 en la imagen final

    ofstream archivo("REPORTES/" + nombreArchivo + ".ppm");
    archivo << "P3" << endl;
    archivo << (ancho * escala) << " " << (alto * escala) << endl;
    archivo << "255" << endl;

    for (int f = 0; f < alto; f++) {
        for (int rep = 0; rep < escala; rep++) {
            for (int c = 0; c < ancho; c++) {
                int r = 255, g = 255, b = 255; // blanco por defecto

                auto it = canvas.find({f, c});
                if (it != canvas.end()) {
                    string color = it->second;
                    // Parsear #rrggbb
                    if (color.size() == 7 && color[0] == '#') {
                        r = hexToInt(color.substr(1, 2));
                        g = hexToInt(color.substr(3, 2));
                        b = hexToInt(color.substr(5, 2));
                    }
                }

                for (int rep2 = 0; rep2 < escala; rep2++) {
                    archivo << r << " " << g << " " << b << " ";
                }
            }
            archivo << endl;
        }
    }

    archivo.close();
    cout << "Imagen generada: REPORTES/" << nombreArchivo << ".ppm" << endl;
    cout << "Abrila con Preview en macOS." << endl;
}

// Recolecta nodos en preorden hasta el límite
void GeneradorImagenes::recolectarPreorden(NodoABBCapa* nodo, vector<NodoABBCapa*>& lista, int limite) {
    if (nodo == nullptr || (int)lista.size() >= limite) return;
    lista.push_back(nodo);
    recolectarPreorden(nodo->izquierda, lista, limite);
    recolectarPreorden(nodo->derecha, lista, limite);
}

// Recolecta nodos en inorden hasta el límite
void GeneradorImagenes::recolectarInorden(NodoABBCapa* nodo, vector<NodoABBCapa*>& lista, int limite) {
    if (nodo == nullptr || (int)lista.size() >= limite) return;
    recolectarInorden(nodo->izquierda, lista, limite);
    if ((int)lista.size() < limite) lista.push_back(nodo);
    recolectarInorden(nodo->derecha, lista, limite);
}

// Recolecta nodos en postorden hasta el límite
void GeneradorImagenes::recolectarPostorden(NodoABBCapa* nodo, vector<NodoABBCapa*>& lista, int limite) {
    if (nodo == nullptr || (int)lista.size() >= limite) return;
    recolectarPostorden(nodo->izquierda, lista, limite);
    recolectarPostorden(nodo->derecha, lista, limite);
    if ((int)lista.size() < limite) lista.push_back(nodo);
}

// Generación por recorrido limitado
// tipoRecorrido: 1=inorden, 2=preorden, 3=postorden
void GeneradorImagenes::generarPorRecorridoLimitado(NodoABBCapa* raiz, int limite, int tipoRecorrido) {
    limpiarCanvas();
    vector<NodoABBCapa*> capas;

    switch (tipoRecorrido) {
        case 1: recolectarInorden(raiz, capas, limite); break;
        case 2: recolectarPreorden(raiz, capas, limite); break;
        case 3: recolectarPostorden(raiz, capas, limite); break;
        default:
            cout << "Tipo de recorrido invalido." << endl;
            return;
    }

    cout << "Capas utilizadas: ";
    for (auto* c : capas) cout << c->id << " ";
    cout << endl;

    for (auto* c : capas) agregarCapaAlCanvas(c);
    escribirPPM("imagen_recorrido");
}

// Generación por lista de imágenes
void GeneradorImagenes::generarPorListaImagenes(NodoImagen* imgNodo) {
    if (imgNodo == nullptr) {
        cout << "Imagen no encontrada." << endl;
        return;
    }

    limpiarCanvas();
    NodoCapa* cap = imgNodo->imagen.listaCapas;

    cout << "Capas utilizadas: ";
    while (cap != nullptr) {
        cout << cap->refCapa->id << " ";
        agregarCapaAlCanvas(cap->refCapa);
        cap = cap->siguiente;
    }
    cout << endl;

    escribirPPM("imagen_" + to_string(imgNodo->imagen.id));
}

// Generación por capa individual
void GeneradorImagenes::generarPorCapa(NodoABBCapa* nodo) {
    if (nodo == nullptr) {
        cout << "Capa no encontrada." << endl;
        return;
    }

    limpiarCanvas();
    agregarCapaAlCanvas(nodo);
    escribirPPM("imagen_capa_" + to_string(nodo->id));
}

// Generación por usuario
void GeneradorImagenes::generarPorUsuario(NodoABBUsuario* usuario, int idImagen, ListaCircular& lista) {
    if (usuario == nullptr) {
        cout << "Usuario no encontrado." << endl;
        return;
    }

    // Verificar que la imagen pertenece al usuario
    NodoImgUsuario* imgUsr = usuario->listaImagenes;
    bool encontrada = false;
    while (imgUsr != nullptr) {
        if (imgUsr->idImagen == idImagen) {
            encontrada = true;
            break;
        }
        imgUsr = imgUsr->siguiente;
    }

    if (!encontrada) {
        cout << "La imagen " << idImagen << " no pertenece al usuario " << usuario->nombre << endl;
        return;
    }

    NodoImagen* imgNodo = lista.buscarImagen(idImagen);
    generarPorListaImagenes(imgNodo);
}