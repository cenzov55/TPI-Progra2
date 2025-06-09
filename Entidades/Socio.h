#pragma once
#include <string>
#include "Fecha.h"

class Socio {
private:
    int _idSocio;
    char _dni[12];
    char _nombre[50];
    char _apellido[50];
    char _email[50];
    Fecha _fechaNacimiento;
    bool _eliminado;

public:
    Socio();
    Socio(int idSocio, std::string dni, std::string nombre, std::string apellido, std::string email, Fecha fechaNacimiento, bool eliminado);
    int getIdSocio();
    std::string getDni();
    std::string getNombre();
    std::string getApellido();
    std::string getEmail();
    Fecha getFechaNacimiento();
    bool getEliminado();

    bool setIdSocio(int id);
    bool setDni(std::string dni);
    bool setNombre(std::string nombre);
    bool setApellido(std::string apellido);
    bool setEmail(std::string email);
    bool setFechaNacimiento(Fecha fechaNacimiento);
    bool setEliminado(bool eliminado);

    std::string toCSV();

};
