#pragma once
#include "../Archivos/ArchivoInscripciones.h"
#include "../Archivos/ArchivoSocios.h"
#include "../Archivos/ArchivoActividades.h"
#include "../Archivos/ArchivoPagos.h"

class ManagerReportes {

public:
    ManagerReportes();
    void actividadMayorRecaudacion();
    void recaudacionPorMes();
    void recaudacionPorSocio();
    void recaudacionPorInscripcion();
    float encontrarPosicionMaxima(float vec[], int tam);
    int encontrarPosicionMaxima(int vec[], int tam);
    /// recibe vector float/int y tamaño. devuelve la posicion maxima del vector


private:
    ArchivoInscripciones _archivoInscripciones;
    ArchivoSocios _archivoSocios;
    ArchivoActividades _archivoActividades;
    ArchivoPagos _archivoPagos;

};