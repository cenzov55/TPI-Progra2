#pragma once
#include "../Archivos/ArchivoPagos.h"
#include "../Archivos/ArchivoSocios.h"
#include "../Archivos/ArchivoActividades.h"

class ManagerPagos
{

public:
    ManagerPagos();
    void agregar();
    void modificar();
    void listar();
    void exportarCSV();
    void listarPagosSocio();

private:
    ArchivoSocios _archivoSocios;
    ArchivoActividades _archivoActividades;
    ArchivoPagos _archivoPagos;

    void mostrarPago(Pago &pago);
    void mostrarEncabezadoTabla();
    void pedirMes(Fecha &fecha);
    void pedirDia(Fecha &fecha);
    void pedirAnio(Fecha &fecha);
    int pedirIdSocio();
    int pedirIdActividad();
    int pedirImporte();
    void pedirMetodoDePago(Pago &pago);
};
