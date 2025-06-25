#pragma once
#include "Fecha.h"

class Pago {
private:
    int _idActividad;
    int _idSocio;
    int _metodoDePago;  //  1: Efectivo, 2: Tarjeta, 3: Transferencia
    float _importe;
    Fecha _fechaDePago;

public:
    Pago();
    // Getters
    int getIdSocio();
    int getIdActividad();
    float getImporte();
    Fecha getFechaDePago();
    int getMetodoDePago();
    // Setters
    void setIdSocio(int idSocio);
    bool setMetodoDePago(int metodoDePago);
    void setIdActividad(int idActividad);
    void setImporte(float importe);
    void setFechaDePago(Fecha fechaDePago);
    std::string toCSV();
};
