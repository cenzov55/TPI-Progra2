#pragma once
#include "Archivo.h"
#include "../Entidades/Socio.h"

class ArchivoSocios : public Archivo {
public:
    ArchivoSocios(std::string nombre);

    int getCantidadRegistros();
    bool guardar(Socio socio);
    bool modificar(Socio socio, int posicion);
    int buscar(int idSocio); ///Devuelve la posicion, devuelve -1 si no lo encontro
    bool eliminar(int id);
    Socio leer(int posicion);
    void leerTodos(int cantidadRegistros, Socio *vec);
    int getNuevoId();
    void exportarCSV();
};
