#pragma once
#include "../Archivos/ArchivoInscripciones.h"

class ManagerInscripciones {

public:
    ManagerInscripciones();
    void agregar();
    void borrar();
    void modificar();
    void listar();
    void exportarCSV();

private:
    ArchivoInscripciones _archivoInscripciones;

};
