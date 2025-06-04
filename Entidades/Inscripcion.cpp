#include<iostream>
#include "Inscripcion.h"
using namespace std;


int Inscripcion::getIdActividad() {
    return idActividad;
}

void Inscripcion::setIdActividad(int nuevoIdActividad) {
    if (nuevoIdActividad >= 0)
        idActividad = nuevoIdActividad;
}

int Inscripcion::getIdSocio() {
    return idSocio;
}


void Inscripcion::setIdSocio(int nuevoIdSocio) {
    if (nuevoIdSocio >= 0)
        idSocio = nuevoIdSocio;
}

Fecha Inscripcion::getFechaInscripcion() {
    return fechaInscripcion;
}

void Inscripcion::setFechaInscripcion(Fecha nuevaFechaInscripcion) {
    fechaInscripcion = nuevaFechaInscripcion;
}

bool Inscripcion::getEliminado() {
    return eliminado;
}

void Inscripcion::setEliminado(bool estadoEliminado) {
    eliminado = estadoEliminado;
}
