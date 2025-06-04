#pragma once
#include "Fecha.h"

class Pago {
private:
    int IdActividad;
    int IdSocio;
    int metodoDePago;
    float importe;
    Fecha fechaDePago;

public:

    int getIdSocio();
    int getIdActividad();
    float getImporte();
    Fecha getFechaDePago();

    void setIdSocio(int idSocio);
    void setIdActividad(int idActividad);
    void setImporte(float importe);
    void setFechaDePago(Fecha fechaDePago);
};
