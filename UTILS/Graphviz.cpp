#include "Graphviz.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <functional>
using namespace std;

Graphviz::Graphviz() {}

// Ejecuta el comando dot para generar la imagen
void Graphviz::ejecutarDot(string archivoDot, string archivoSalida) {
    string comando = "dot -Tpng " + archivoDot + " -o " + archivoSalida;
    system(comando.c_str());
    cout << "Reporte generado: " << archivoSalida << endl;
}

// ── Árbol de Capas ────────────────────────────────────────────
void Graphviz::graficarArbolCapas(NodoABBCapa* raiz) {
    ofstream archivo("REPORTES/arbol_capas.dot");
    archivo << "digraph ArbolCapas {" << endl;
    archivo << "    node [shape=box, style=filled, fillcolor=\"#2c3e50\", fontcolor=white];" << endl;

    // Recorrido recursivo con lambda auxiliar
    function<void(NodoABBCapa*)> recorrer = [&](NodoABBCapa* nodo) {
        if (nodo == nullptr) return;
        archivo << "    capa" << nodo->id << " [label=\"Capa " << nodo->id << "\"];" << endl;
        if (nodo->izquierda != nullptr) {
            archivo << "    capa" << nodo->id << " -> capa" << nodo->izquierda->id << ";" << endl;
        }
        if (nodo->derecha != nullptr) {
            archivo << "    capa" << nodo->id << " -> capa" << nodo->derecha->id << ";" << endl;
        }
        recorrer(nodo->izquierda);
        recorrer(nodo->derecha);
    };

    recorrer(raiz);
    archivo << "}" << endl;
    archivo.close();
    ejecutarDot("REPORTES/arbol_capas.dot", "REPORTES/arbol_capas.png");
}

// ── Lista Circular de Imágenes ────────────────────────────────
void Graphviz::graficarListaImagenes(NodoImagen* cabeza) {
    if (cabeza == nullptr) {
        cout << "Lista de imagenes vacia." << endl;
        return;
    }

    ofstream archivo("REPORTES/lista_imagenes.dot");
    archivo << "digraph ListaImagenes {" << endl;
    archivo << "    rankdir=LR;" << endl;
    archivo << "    node [shape=record, style=filled, fillcolor=\"#2980b9\", fontcolor=white];" << endl;

    NodoImagen* actual = cabeza;
    do {
        archivo << "    img" << actual->imagen.id
                << " [label=\"{Imagen " << actual->imagen.id << " | Capas: ";

        NodoCapa* cap = actual->imagen.listaCapas;
        while (cap != nullptr) {
            archivo << cap->refCapa->id;
            if (cap->siguiente != nullptr) archivo << ", ";
            cap = cap->siguiente;
        }
        archivo << "}\"];" << endl;
        actual = actual->siguiente;
    } while (actual != cabeza);

    // Flechas entre nodos
    actual = cabeza;
    do {
        archivo << "    img" << actual->imagen.id
                << " -> img" << actual->siguiente->imagen.id << ";" << endl;
        actual = actual->siguiente;
    } while (actual != cabeza);

    archivo << "}" << endl;
    archivo.close();
    ejecutarDot("REPORTES/lista_imagenes.dot", "REPORTES/lista_imagenes.png");
}

// ── Capa específica (matriz dispersa) ────────────────────────
void Graphviz::graficarCapa(NodoABBCapa* nodo) {
    if (nodo == nullptr) {
        cout << "Capa no encontrada." << endl;
        return;
    }

    ofstream archivo("REPORTES/capa_" + to_string(nodo->id) + ".dot");
    archivo << "digraph Capa" << nodo->id << " {" << endl;
    archivo << "    node [shape=box];" << endl;
    archivo << "    label=\"Capa " << nodo->id << "\";" << endl;

    // Recorrer matriz dispersa
    NodoMatriz* fila = nodo->matriz;
    while (fila != nullptr) {
        NodoMatriz* col = fila->derecha;
        while (col != nullptr) {
            archivo << "    n" << col->fila << "_" << col->columna
                    << " [label=\"(" << col->fila << "," << col->columna << ")\\n"
                    << col->color << "\", style=filled, fillcolor=\"" << col->color << "\"];" << endl;
            col = col->derecha;
        }
        fila = fila->abajo;
    }

    archivo << "}" << endl;
    archivo.close();
    ejecutarDot("REPORTES/capa_" + to_string(nodo->id) + ".dot",
                "REPORTES/capa_" + to_string(nodo->id) + ".png");
}

// ── Imagen y su árbol de capas ────────────────────────────────
void Graphviz::graficarImagenYArbol(NodoImagen* imgNodo, NodoABBCapa* raizArbol) {
    if (imgNodo == nullptr) {
        cout << "Imagen no encontrada." << endl;
        return;
    }

    ofstream archivo("REPORTES/imagen_arbol_" + to_string(imgNodo->imagen.id) + ".dot");
    archivo << "digraph ImagenArbol {" << endl;
    archivo << "    node [shape=box, style=filled];" << endl;

    // Nodo de la imagen
    archivo << "    img" << imgNodo->imagen.id
            << " [label=\"Imagen " << imgNodo->imagen.id
            << "\", fillcolor=\"#e74c3c\", fontcolor=white];" << endl;

    // Lista de capas de la imagen
    NodoCapa* cap = imgNodo->imagen.listaCapas;
    NodoCapa* anterior = nullptr;
    while (cap != nullptr) {
        int idCapa = cap->refCapa->id;
        archivo << "    listaCapa" << idCapa
                << " [label=\"Capa " << idCapa
                << "\", fillcolor=\"#e67e22\", fontcolor=white];" << endl;

        if (anterior == nullptr) {
            archivo << "    img" << imgNodo->imagen.id
                    << " -> listaCapa" << idCapa << ";" << endl;
        } else {
            archivo << "    listaCapa" << anterior->refCapa->id
                    << " -> listaCapa" << idCapa << ";" << endl;
        }

        // Flecha al ABB
        archivo << "    listaCapa" << idCapa
                << " -> capa" << idCapa
                << " [style=dashed, color=\"#e74c3c\"];" << endl;

        anterior = cap;
        cap = cap->siguiente;
    }

    // Árbol ABB
    function<void(NodoABBCapa*)> recorrer = [&](NodoABBCapa* nodo) {
        if (nodo == nullptr) return;
        archivo << "    capa" << nodo->id
                << " [label=\"Capa " << nodo->id
                << "\", fillcolor=\"#2c3e50\", fontcolor=white];" << endl;
        if (nodo->izquierda != nullptr) {
            archivo << "    capa" << nodo->id << " -> capa" << nodo->izquierda->id << ";" << endl;
        }
        if (nodo->derecha != nullptr) {
            archivo << "    capa" << nodo->id << " -> capa" << nodo->derecha->id << ";" << endl;
        }
        recorrer(nodo->izquierda);
        recorrer(nodo->derecha);
    };

    recorrer(raizArbol);
    archivo << "}" << endl;
    archivo.close();
    ejecutarDot("REPORTES/imagen_arbol_" + to_string(imgNodo->imagen.id) + ".dot",
                "REPORTES/imagen_arbol_" + to_string(imgNodo->imagen.id) + ".png");
}

// ── Árbol de Usuarios ─────────────────────────────────────────
void Graphviz::graficarArbolUsuarios(NodoABBUsuario* raiz) {
    ofstream archivo("REPORTES/arbol_usuarios.dot");
    archivo << "digraph ArbolUsuarios {" << endl;
    archivo << "    node [shape=box, style=filled, fillcolor=\"#8e44ad\", fontcolor=white];" << endl;

    function<void(NodoABBUsuario*)> recorrer = [&](NodoABBUsuario* nodo) {
        if (nodo == nullptr) return;

        archivo << "    user_" << nodo->nombre
                << " [label=\"" << nodo->nombre << "\\nImagenes: ";

        NodoImgUsuario* img = nodo->listaImagenes;
        while (img != nullptr) {
            archivo << img->idImagen;
            if (img->siguiente != nullptr) archivo << ", ";
            img = img->siguiente;
        }
        archivo << "\"];" << endl;

        if (nodo->izquierda != nullptr) {
            archivo << "    user_" << nodo->nombre
                    << " -> user_" << nodo->izquierda->nombre << ";" << endl;
        }
        if (nodo->derecha != nullptr) {
            archivo << "    user_" << nodo->nombre
                    << " -> user_" << nodo->derecha->nombre << ";" << endl;
        }
        recorrer(nodo->izquierda);
        recorrer(nodo->derecha);
    };

    recorrer(raiz);
    archivo << "}" << endl;
    archivo.close();
    ejecutarDot("REPORTES/arbol_usuarios.dot", "REPORTES/arbol_usuarios.png");
}