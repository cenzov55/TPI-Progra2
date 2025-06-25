#pragma once
#include "Fecha.h"
#include <string>

class Inscripcion {
private:
    int _idActividad;
    int _idSocio;
    Fecha _fechaInscripcion;
    bool _eliminado;
    bool _pagoRealizado;

public:
    Inscripcion();
    Inscripcion(int idSocio, int idActividad, Fecha fechaInscripcion);

    // Getters
    int getIdActividad();
    int getIdSocio();
    Fecha getFechaInscripcion();
    bool getEliminado();

    // Setters
    void setIdActividad(int idActividad);
    void setIdSocio(int idSocio);
    void setFechaInscripcion(Fecha fechaInscripcion);
    void setEliminado(bool eliminado);

    // Exportar a CSV
    std::string toCSV();
};
