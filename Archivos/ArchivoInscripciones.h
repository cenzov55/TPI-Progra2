#pragma once
#include "Archivo.h"
#include "../Entidades/Inscripcion.h"

class ArchivoInscripciones : public Archivo {
public:
    ArchivoInscripciones(std::string nombre);

    int getCantidadRegistros();
    bool guardar(Inscripcion inscripcion);
    bool modificar(Inscripcion inscripcion, int posicion);
    int buscar(int idActividad, int idSocio);
    bool eliminar(int id);
    Inscripcion leer(int posicion);
    void leerTodos(int cantidadRegistros, Inscripcion *vec);
    int getNuevoId();
    int exportarCSV();
    bool crearBackup();
    bool usarBackup();
};
