#pragma once
#include "../Archivos/ArchivoInscripciones.h"
#include "../Archivos/ArchivoSocios.h"
#include "../Archivos/ArchivoActividades.h"

class ManagerInscripciones {

public:
    ManagerInscripciones();
    void agregar();
    void borrar();
    void listar();
    void exportarCSV();

private:
    ArchivoInscripciones _archivoInscripciones;
    ArchivoSocios _archivoSocios;
    ArchivoActividades _archivoActividades;

    void mostrarInscripcion(Inscripcion &inscripcion);
    void mostrarEncabezadoTabla();
    void pedirMes(Fecha &fecha);
    void pedirDia(Fecha &fecha);
    void pedirAnio(Fecha &fecha);
    int pedirIdSocio();
    int pedirIdActividad();
};
