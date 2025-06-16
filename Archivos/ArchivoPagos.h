#pragma once
#include "Archivo.h"
#include "../Entidades/Pago.h"

class ArchivoPagos : public Archivo {
public:
    ArchivoPagos(std::string nombre);

    int getCantidadRegistros();
    bool guardar(Pago pago);
    bool modificar(Pago pago, int posicion);
    void buscarPagosSocio(int idSocio, int cantidadRegistros, Pago *vec); ///Devuelve la posicion, devuelve -1 si no lo encontro
    bool eliminar(int id);
    Pago leer(int posicion);
    void leerTodos(int cantidadRegistros, Pago *vec);
    bool exportarCSV();
};
