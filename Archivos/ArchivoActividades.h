#pragma once
#include "Archivo.h"
#include "../Entidades/Actividad.h"

class ArchivoActividades : public Archivo {
public:
    ArchivoActividades(std::string nombre);

    int getCantidadRegistros();
    bool guardar(Actividad actividad);
    bool modificar(Actividad actividad, int posicion);
    int buscar(int idActividad); ///Devuelve la posicion, devuelve -1 si no lo encontro
    bool eliminar(int id);
    Actividad leer(int posicion);
    void leerTodos(int cantidadRegistros, Actividad *vec);
    int getNuevoId();
    int exportarCSV();
    bool crearBackup();
    bool usarBackup();
};
