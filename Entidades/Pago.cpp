#include <iostream>
#include "Pago.h"

using namespace std;

Pago::Pago() {}

int Pago::getIdSocio() const
{
    return _idSocio;
}

int Pago::getMetodoDePago() const
{
    return _metodoDePago;
}

int Pago::getIdActividad() const
{
    return _idActividad;
}

float Pago::getImporte() const
{
    return _importe;
}

Fecha Pago::getFechaDePago() const
{
    return _fechaDePago;
}

void Pago::setIdSocio(int idSocio)
{
    if (idSocio > 0)
        _idSocio = idSocio;
}

void Pago::setIdActividad(int idActividad)
{
    if (idActividad > 0)
        _idActividad = idActividad;
}

void Pago::setImporte(float nuevoImporte)
{
    if (nuevoImporte >= 0)
        _importe = nuevoImporte;
}

void Pago::setFechaDePago(Fecha nuevaFecha)
{
    _fechaDePago = nuevaFecha;
}

bool Pago::setMetodoDePago(int metodoDePago)
{
    if (metodoDePago >= 0 && metodoDePago <= 3) 
    {
        _metodoDePago = metodoDePago;
        return true;
    }
    else
    {
        return false;
    }
}

string Pago::toCSV()
{
    return to_string(_idSocio) + ";" +
           to_string(_idActividad) + ";" +
           _fechaDePago.toString() + ";" +
           to_string(_importe) + ";";
}
