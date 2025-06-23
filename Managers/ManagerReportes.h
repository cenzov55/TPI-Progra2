#pragma once
#include "../Archivos/ArchivoInscripciones.h"
#include "../Archivos/ArchivoSocios.h"
#include "../Archivos/ArchivoActividades.h"

class ManagerReportes {

public:
    ManagerReportes();
    void actividadMasInscriptos();
    void actividadMayorRecaudacion();

private:
    ArchivoInscripciones _archivoInscripciones;
    ArchivoSocios _archivoSocios;
    ArchivoActividades _archivoActividades;

};
