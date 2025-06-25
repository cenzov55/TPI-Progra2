#pragma once
#include "../Archivos/ArchivoInscripciones.h"
#include "../Archivos/ArchivoSocios.h"
#include "../Archivos/ArchivoActividades.h"
#include "../Archivos/ArchivoPagos.h"

class ManagerReportes {

public:
    ManagerReportes();
    void actividadMasInscriptos();
    void actividadMayorRecaudacion();
    void recaudacionPorMes();

private:
    ArchivoInscripciones _archivoInscripciones;
    ArchivoSocios _archivoSocios;
    ArchivoActividades _archivoActividades;
    ArchivoPagos _archivoPagos;
};
