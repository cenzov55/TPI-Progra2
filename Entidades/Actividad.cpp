#include <iostream>
#include <cstring>
#include <string>
#include "Actividad.h"
#include "../funcionesConsola.h"
using namespace std;

// Constructor por defecto
Actividad::Actividad() {
    _idActividad = 0;
    _nombre[0] = '\0';
    _responsable[0] = '\0';
    _arancel = 0.0;
    _fechaInicio = Fecha();
    _eliminado = false;
}

// Constructor con parámetros
Actividad::Actividad(int idActividad, string nombre, string responsable, Fecha fechaInicio, float arancel, bool eliminado) {
    setIdActividad(idActividad);
    setNombre(nombre);
    setResponsable(responsable);
    setFechaInicio(fechaInicio);
    setArancel(arancel);
    setEliminado(eliminado);
}

// Getters
int Actividad::getIdActividad() {
    return _idActividad;
}

string Actividad::getNombre() {
    return _nombre;
}

string Actividad::getResponsable() {
    return _responsable;
}

Fecha Actividad::getFechaInicio() {
    return _fechaInicio;
}

float Actividad::getArancel() {
    return _arancel;
}

bool Actividad::getEliminado() {
    return _eliminado;
}

// Setters
bool Actividad::setIdActividad(int idActividad) {
    if (idActividad > 0) {
        _idActividad = idActividad;
        return true;
    }
    return false;
}

bool Actividad::setNombre(const string& nombre) {
    if (nombre.length() < sizeof(_nombre)) {
        strcpy(_nombre, nombre.c_str());
        return true;
    }
    return false;
}

bool Actividad::setResponsable(const string& responsable) {
    if (responsable.length() < sizeof(_responsable)) {
        strcpy(_responsable, responsable.c_str());
        return true;
    }
    return false;
}

bool Actividad::setFechaInicio(Fecha fechaInicio) {
    _fechaInicio = fechaInicio;
    return true;
}

bool Actividad::setArancel(float arancel) {
    _arancel = arancel;
    return true;
}

bool Actividad::setEliminado(bool eliminado) {
    _eliminado = eliminado;
    return true;
}

// CSV
string Actividad::toCSV() {

    string arancel = truncarFloatDosDecimales(_arancel);
    string ss;
    ss = to_string(_idActividad) + ";" +
         _nombre + ";" +
         _responsable + ";" +
         _fechaInicio.toString() + ";" +
         arancel + ";";
    return ss;
}
