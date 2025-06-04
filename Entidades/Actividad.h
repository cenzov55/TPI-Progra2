#pragma once
#include "Entidades/Fecha.h"
#include <string>

class Actividad {
private:

    int _idActividad;
    char _nombre[50];
    char _responsable[50];
    Fecha _fechaInicio;
    float _arancel;
    bool _eliminado;

public:


    // Getters
    int getIdActividad();
    std::string getNombre();
    std::string getResponsable();
    Fecha getFechaInicio();
    float getArancel();
    bool getEliminado();

    // Setters
    void setIdActividad(int idActividad);
    void setNombre(const std::string& nombre);
    void setResponsable(const std::string& responsable);
    void setFechaInicio(Fecha fechaInicio);
    void setArancel(float arancel);
    void setEliminado(bool eliminado);
};

#endif



