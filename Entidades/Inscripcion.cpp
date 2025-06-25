#include <iostream>
#include "Inscripcion.h"
using namespace std;

Inscripcion::Inscripcion(){}

Inscripcion::Inscripcion(int idSocio, int idActividad, Fecha fechaInscripcion){
    setIdSocio(idSocio);
    setIdActividad(idActividad);
    setFechaInscripcion(fechaInscripcion);
    _eliminado = false;
    _pagoRealizado = false;
}

int Inscripcion::getIdActividad() {
    return _idActividad;
}

void Inscripcion::setIdActividad(int nuevoIdActividad) {
    if (nuevoIdActividad >= 0)
        _idActividad = nuevoIdActividad;
}

int Inscripcion::getIdSocio() {
    return _idSocio;
}


void Inscripcion::setIdSocio(int nuevoIdSocio) {
    if (nuevoIdSocio >= 0) _idSocio = nuevoIdSocio;
}

Fecha Inscripcion::getFechaInscripcion() {
    return _fechaInscripcion;
}

void Inscripcion::setFechaInscripcion(Fecha nuevaFechaInscripcion) {
    _fechaInscripcion = nuevaFechaInscripcion;
}

bool Inscripcion::getEliminado() {
    return _eliminado;
}

void Inscripcion::setEliminado(bool estadoEliminado) {
    _eliminado = estadoEliminado;
}

/// CSV aca

string Inscripcion::toCSV(){
    string ss = to_string(_idActividad) + ";" +
                to_string(_idSocio) + ";" +
                _fechaInscripcion.toString(); + ";";
    return ss;
}
