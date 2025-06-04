#include <iostream>
#include "Pago.h"
using namespace std;

int Pago::getIdSocio() {
    return IdSocio;
}

int Pago::getIdActividad() {
    return IdActividad;
}

float Pago::getImporte() {
    return importe;
}

Fecha Pago::getFechaDePago() {
    return fechaDePago;
}

void Pago::setIdSocio(int idSocio) {
    if (idSocio > 0)
        IdSocio = idSocio;
}

void Pago::setIdActividad(int idActividad) {
    if (idActividad > 0)
        IdActividad = idActividad;
}

void Pago::setImporte(float nuevoImporte) {
    if (nuevoImporte >= 0)
        importe = nuevoImporte;
}

void Pago::setFechaDePago(Fecha nuevaFecha) {
    fechaDePago = nuevaFecha;
}
