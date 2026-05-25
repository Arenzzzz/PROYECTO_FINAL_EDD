#ifndef PROYECTO_FINAL_GENERADORIMAGENES_H
#define PROYECTO_FINAL_GENERADORIMAGENES_H

#include "../Structs.h"
#include "../ESTRUCTURAS/ABBCapas.h"
#include "../ESTRUCTURAS/ListaCircular.h"
#include "../ESTRUCTURAS/ABBUsuarios.h"
#include <string>
#include <map>
using namespace std;

class GeneradorImagenes {
private:
    // Canvas: mapa de (fila, columna) -> color hexadecimal
    map<pair<int,int>, string> canvas;

    void limpiarCanvas();
    void agregarCapaAlCanvas(NodoABBCapa* nodo);
    void escribirPPM(string nombreArchivo);
    int hexToInt(string hex);

    // Recorridos del ABB
    void recolectarPreorden(NodoABBCapa* nodo, vector<NodoABBCapa*>& lista, int limite);
    void recolectarInorden(NodoABBCapa* nodo, vector<NodoABBCapa*>& lista, int limite);
    void recolectarPostorden(NodoABBCapa* nodo, vector<NodoABBCapa*>& lista, int limite);

public:
    GeneradorImagenes();
    void generarPorRecorridoLimitado(NodoABBCapa* raiz, int limite, int tipoRecorrido);
    void generarPorListaImagenes(NodoImagen* imgNodo);
    void generarPorCapa(NodoABBCapa* nodo);
    void generarPorUsuario(NodoABBUsuario* usuario, int idImagen, ListaCircular& lista);
};

#endif