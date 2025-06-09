#include <iostream>
#include <cstring>
#include <string>
#include "Socio.h"

using namespace std;

Socio::Socio()
{
    _idSocio = 0;
    _dni[0] = '\0';
    _nombre[0] = '\0';
    _apellido[0] = '\0';
    _email[0] = '\0';
    _fechaNacimiento = Fecha();
    _eliminado = false;
}

Socio::Socio(int idSocio, string dni, string nombre, string apellido, string email, Fecha fechaNacimiento, bool eliminado)
{

    setIdSocio(idSocio);
    setDni(dni);
    setNombre(nombre);
    setApellido(apellido);
    setEmail(email);
    setFechaNacimiento(fechaNacimiento);
    setEliminado(eliminado);
}

int Socio::getIdSocio()
{
    return _idSocio;
}

bool Socio::setIdSocio(int id)
{
    if (id > 0) {
        _idSocio = id;
        return true;
    }
    return false;
}


string Socio::getDni()
{
    return string(_dni);
}

bool Socio::setDni(std::string dni)
{
    if (dni.length() < sizeof(_dni)) {
        strcpy(_dni, dni.c_str());
        return true;
    }
    return false;
}

string Socio::getNombre()
{
    return _nombre;
}

bool Socio::setNombre(std::string nombre)
{
    if (nombre.length() < sizeof(_nombre)) {
        strcpy(_nombre, nombre.c_str());
        return true;
    }
    return false;
}

string Socio::getApellido()
{
    return _apellido;
}

bool Socio::setApellido(std::string apellido)
{
    if (apellido.length() < sizeof(_apellido)) {
        strcpy(_apellido, apellido.c_str());
        return true;
    }
    return false;
}

string Socio::getEmail()
{
    return _email;
}

bool Socio::setEmail(std::string email)
{
    if (email.length() < sizeof(_email)) {
        strcpy(_email, email.c_str());
        return true;
    }
    return false;
}

Fecha Socio::getFechaNacimiento()
{
    return _fechaNacimiento;
}

bool Socio::setFechaNacimiento(Fecha fechaNacimiento)
{
    _fechaNacimiento = fechaNacimiento;
    return true;
}

bool Socio::getEliminado()
{
    return _eliminado;
}

bool Socio::setEliminado(bool eliminado)
{
    _eliminado = eliminado;
    return true;
}

string Socio::toCSV()
{
    return to_string(_idSocio) + "," +
           _dni + "," +
           _nombre + "," +
           _apellido + "," +
           _email + "," +
           _fechaNacimiento.toString() + "," +
           (_eliminado ? "Si" : "No");
}
