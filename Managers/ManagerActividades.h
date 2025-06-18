#pragma once
#include "../Archivos/ArchivoActividades.h"
#include "../Entidades/Actividad.h"
#include <string>

class ManagerActividades {

public:
    ManagerActividades();
    void agregar();
    void borrar();
    void modificar();
    void listar();
    void exportarCSV();
    void backup();

private:
    ArchivoActividades _archivoActividades;

    void mostrarActividad(Actividad &actividad);
    void mostrarEncabezadoTabla();
    void pedirMes(Fecha &fecha);
    void pedirDia(Fecha &fecha);
    void pedirAnio(Fecha &fecha);
    int pedirIdActividad();
    void pedirNombre(Actividad &actividad);
    void pedirResponsable(Actividad &actividad);
    void pedirArancel(Actividad &actividad);
};
