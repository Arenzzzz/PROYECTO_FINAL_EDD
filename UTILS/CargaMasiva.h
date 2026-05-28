#ifndef PROYECTO_FINAL_CARGAMASIVA_H
#define PROYECTO_FINAL_CARGAMASIVA_H

#include <string>
#include "../Structs.h"
#include "../ESTRUCTURAS/ABBCapas.h"
#include "../ESTRUCTURAS/ListaCircular.h"
#include "../ESTRUCTURAS/ABBUsuarios.h"
using namespace std;

class CargaMasiva {
private:
    string trim(string str);

public:
    CargaMasiva();
    string seleccionarArchivo(string titulo, string extension); // Método de selección de archivos
    void cargarCapas(string ruta, ABBCapas& arbolCapas);
    void cargarImagenes(string ruta, ListaCircular& listaImagenes, ABBCapas& arbolCapas);
    void cargarUsuarios(string ruta, ABBUsuarios& arbolUsuarios, ListaCircular& listaImagenes);
};

#endif