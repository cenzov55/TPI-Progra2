#pragma once
#include "../Archivos/ArchivoSocios.h"

class ManagerSocios {

public:
    ManagerSocios();
    void agregar();
    void borrar();
    void modificar();
    void listar();
    void backup();
    void darDeAlta();


    void buscarPorApellido();
    void buscarPorEdad();
    void listarEliminados();
    void buscarPorId();
    void exportarCSV();


private:

    void pedirDni(Socio &socio);
    void pedirNombre(Socio &socio);
    void pedirApellido(Socio &socio);
    void pedirEmail(Socio &socio);
    void pedirMes(Fecha &fecha);
    void pedirDia(Fecha &fecha);
    void pedirAnio(Fecha &fecha);
    void mostrarSocio(Socio &socio);
    void mostrarEncabezadoTabla();

    ArchivoSocios _archivoSocios;
};
