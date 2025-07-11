#pragma once
#include "Fecha.h"
#include <string>

class Actividad {
private:
    int _idActividad;
    char _nombre[50];
    char _responsable[50];
    Fecha _fechaInicio;
    float _arancel;
    bool _eliminado;
    float _acumulador;

public:
    // Constructores
    Actividad();
    Actividad(int idActividad, std::string nombre, std::string responsable, Fecha fechaInicio, float arancel, bool eliminado);

    // Getters
    int getIdActividad();
    std::string getNombre();
    std::string getResponsable();
    Fecha getFechaInicio();
    float getArancel();
    bool getEliminado();


    // Setters
    bool setIdActividad(int idActividad);
    bool setNombre(const std::string& nombre);
    bool setResponsable(const std::string& responsable);
    bool setFechaInicio(Fecha fechaInicio);
    bool setArancel(float arancel);
    bool setEliminado(bool eliminado);


    // Exportar a CSV
    std::string toCSV();
};




