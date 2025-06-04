#pragma once
#include <string>
#include "Fecha.h"

class Socio {
private:
    int idSocio;
    char dni[12];
    char nombre[50];
    char apellido[50];
    char email[50];
    Fecha fechaNacimiento;
    bool eliminado;

public:
    int getIdSocio();
    std::string getDni();
    std::string getNombre();
    std::string getApellido();
    std::string getEmail();
    Fecha getFechaNacimiento();
    bool getEliminado();

    void setIdSocio(int id);
    void setDni(std::string dni);
    void setNombre(std::string nombre);
    void setApellido(std::string apellido);
    void setEmail(std::string email);
    void setFechaNacimiento(Fecha fechaNacimiento);
    void setEliminado(bool eliminado);

};
