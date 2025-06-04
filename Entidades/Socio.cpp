#include <iostream>
#include <cstring>
#include "Socio.h"

using namespace std;



int Socio::getIdSocio() {
    return idSocio;
}

void Socio::setIdSocio(int id) {
    if(id > 0){idSocio = id;}
    else{return;}
}

std::string Socio::getDni() {
    return std::string(dni);
}

void Socio::setDni(std::string d) {
    strncpy(dni, d.c_str(), sizeof(dni));
    dni[sizeof(dni)-1] = '\0';
}

std::string Socio::getNombre() {
    return std::string(nombre);
}

void Socio::setNombre(std::string n) {
    strncpy(nombre, n.c_str(), sizeof(nombre));
    nombre[sizeof(nombre)-1] = '\0';
}

std::string Socio::getApellido() {
    return std::string(apellido);
}
void Socio::setApellido(std::string a) {
    strncpy(apellido, a.c_str(), sizeof(apellido));
    apellido[sizeof(apellido)-1] = '\0';
}

std::string Socio::getEmail() {
    return std::string(email);
}

void Socio::setEmail(std::string e) {
    strncpy(email, e.c_str(), sizeof(email));
    email[sizeof(email)-1] = '\0';
}

Fecha Socio::getFechaNacimiento() {
    return fechaNacimiento;
}

void Socio::setFechaNacimiento(Fecha f) {
    fechaNacimiento = f;
}

bool Socio::getEliminado() {
    return eliminado;
}

void Socio::setEliminado(bool e) {
    eliminado = e;
}
