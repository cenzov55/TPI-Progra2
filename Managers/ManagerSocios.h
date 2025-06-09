#pragma once
#include "../Archivos/ArchivoSocios.h"

class ManagerSocios {

public:
    ManagerSocios();
    void agregar();
    void borrar();
    void modificar();
    void listar();


private:
    void mostrarSocio(Socio socio);
    void mostrarEncabezadoTabla();

    ArchivoSocios _archivoSocios;
};
