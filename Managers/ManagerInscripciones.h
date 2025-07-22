#pragma once
#include "../Archivos/ArchivoInscripciones.h"
#include "../Archivos/ArchivoSocios.h"
#include "../Archivos/ArchivoActividades.h"
#include "../Archivos/ArchivoPagos.h"

class ManagerInscripciones {

public:
    ManagerInscripciones();
    void agregar();
    void borrar();
    void listar();
    void listarEliminados();
    void listarActividadesInscriptas();
    void listarSociosInscriptos();
    void darDeAlta();
    void exportarCSV();
    void backup();

private:
    ArchivoInscripciones _archivoInscripciones;
    ArchivoSocios _archivoSocios;
    ArchivoActividades _archivoActividades;
    ArchivoPagos _archivoPagos;

    void mostrarInscripcion(Inscripcion &inscripcion);
    void mostrarEncabezadoTabla();
    void pedirMes(Fecha &fecha);
    void pedirDia(Fecha &fecha);
    void pedirAnio(Fecha &fecha);
    int pedirIdSocio();
    int pedirIdActividad();
};
