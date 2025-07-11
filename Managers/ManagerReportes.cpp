#include <iostream>
#include "ManagerReportes.h"
#include "../funcionesConsola.h"
#include "../rlutil.h"
#include <iomanip>

using namespace std;

ManagerReportes::ManagerReportes()
    : _archivoInscripciones("Inscripciones.dat"),
      _archivoSocios("Socios.dat"),
      _archivoActividades("Actividades.dat"),
      _archivoPagos("Pagos.dat")
{
}



void ManagerReportes::actividadMayorRecaudacion()
{
    system("cls");
    cout << "Reporte por actividades" << endl;
    cout << "                          " << endl;

    int cantidadPagos = _archivoPagos.getCantidadRegistros();
    if (cantidadPagos <= 0)
    {
        mensajeError("No hay pagos registrados.");
        system("pause>nul");
        return;
    }

    /// Para saber cuantas actividades hay registradas
    int cantActividades = _archivoActividades.getCantidadRegistros();
    if (cantActividades <= 0)
    {
        mensajeError("No hay actividades registradas.");
        system("pause>nul");
        return;
    }

    Actividad* regActividades = new Actividad[cantActividades];
    float* recaudacionActividades = new float[cantActividades];

    /// Hago una copia al registro de actividades
    _archivoActividades.leerTodos(cantActividades, regActividades);

    Pago* pagos = new Pago[cantidadPagos];
    _archivoPagos.leerTodos(cantidadPagos, pagos);

    for(int i = 0; i<cantActividades; i++){recaudacionActividades[i] = 0;}

    /// Acumulo el importe de los pagos en el registro pagos
    for (int i = 0; i < cantidadPagos; i++)
    {
        int idAct = pagos[i].getIdActividad() - 1;
        if (idAct >= 0 && idAct < cantActividades)
        {
            float importe = pagos[i].getImporte();
            recaudacionActividades[idAct] += importe;
        }
    }

    /// Buscar posici�n de actividad con mas recaudacion
    int posMax = encontrarPosicionMaxima(recaudacionActividades, cantActividades);
    /// Encabezado
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(20) << "ID Actividad" << (char)179
         << left << setw(20) << "Nombre" << (char)179
         << left << setw(15) << "Recaudacion" << (char)179 << endl;
    /// Actividades
    for(int i = 0; i< cantActividades; i++)
    {
        rlutil::setBackgroundColor(rlutil::WHITE);
        rlutil::setColor(rlutil::BLACK);
        cout << (char)179 << left << setw(20) << regActividades[i].getIdActividad() << (char)179
             << left << setw(20) << regActividades[i].getNombre() << (char)179
             << left << setw(15) << recaudacionActividades[i] << (char)179 << endl;

    }

    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(20) << "ID Actividad" << (char)179
         << left << setw(20) << "Nombre" << (char)179
         << left << setw(15) << "Recaudacion" << (char)179 << endl;

    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(20) << regActividades[posMax].getIdActividad() << (char)179
         << left << setw(20) << regActividades[posMax].getNombre() << (char)179
         << left << setw(15) << recaudacionActividades[posMax] << (char)179 << endl;

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::resetColor();
    system("pause>nul");

    delete[] pagos;
    delete[] regActividades;
    delete[] recaudacionActividades;

}

void ManagerReportes::recaudacionPorMes()
{
    system("cls");
    cout << "Recaudacion por mes" << endl;
    cout << "                   " << endl;
    float meses[12] = {0}; // vector para acumular por mes
    int recaudacionAnio = 0; // Acumula todo el a�o
    int cantidadPagos = _archivoPagos.getCantidadRegistros();
    if (cantidadPagos <= 0)
    {
        /// si es 0 no hay pagos, pero puede ser -1 que significa error
        mensajeError("No hay pagos registrados.");
        system("pause>nul");
        return;
    }

    Pago *pagos = nullptr;

    pagos = new Pago[cantidadPagos];

    if(pagos == nullptr)
    {
        mensajeError("Err asignacion memoria.");
        system("pause>nul");
        return;
    }
    _archivoPagos.leerTodos(cantidadPagos, pagos);

    for (int i = 0; i < cantidadPagos; i++)
    {
        int mes = pagos[i].getFechaDePago().getMes() - 1;
        meses[mes] += pagos[i].getImporte();
        recaudacionAnio += pagos[i].getImporte();
    }



    int mesMasRecaudador = encontrarPosicionMaxima(meses, 12);
    // ENCABEZADO
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(12) << "MES" << (char)179;
    cout << left << setw(12) << "RECAUDACION" << (char)179;
    cout << endl;
    // FIN ENCABEZADO

    string nombreMeses[12] =
    {
        "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
        "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
    };

    for (int i = 0; i < 12; i++)
    {
        if (meses[i] > 0)
        {
            rlutil::setBackgroundColor(rlutil::GREY);
        }
        else if (meses[i] < 1)
        {
            rlutil::setBackgroundColor(rlutil::WHITE);
        }


        rlutil::setColor(rlutil::BLACK);
        cout << (char)179 << left << setw(12) << nombreMeses[i] << (char)179;
        cout << left << setw(12) << meses[i] << (char)179;
        cout << endl;
    }

    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(12) << " Mejor mes y " ;
    cout << left << setw(12) << "Total anio"<< (char)179;
    cout << endl;

    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(11) << nombreMeses[mesMasRecaudador] << (char)61 << (char)32;
    cout << left << setw(12) << meses[mesMasRecaudador] << (char)179 ;
    cout << endl;

    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(11) << "Total Anio"<< (char)61 << (char)32;
    cout << left << setw(12) << recaudacionAnio << (char)179 ;
    cout << endl;

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::resetColor();
    system("pause>nul");

    delete[] pagos;
    return;
}

void ManagerReportes::recaudacionPorSocio()
{
    system("cls");
    cout << "Reporte por socio" << endl;
    cout << "                   " << endl;

    int cantidadPagos = _archivoPagos.getCantidadRegistros();
    if (cantidadPagos <= 0)
    {
        mensajeError("No hay pagos registrados.");
        system("pause>nul");
        return;
    }


    Pago* pagos = nullptr;
    pagos = new Pago[cantidadPagos];

    if(pagos == nullptr)
    {
        mensajeError("Err asignacion memoria.");
        system("pause>nul");
        return;
    }

    _archivoPagos.leerTodos(cantidadPagos, pagos);


    int cantidadSocios = _archivoSocios.getCantidadRegistros();

    if (cantidadSocios <= 0)
    {
        mensajeError("No hay socios registrados.");
        system("pause>nul");
        return;
    }

    Socio* socios = nullptr;
    socios = new Socio[cantidadSocios];

    if(socios == nullptr)
    {
        mensajeError("Err asignacion memoria.");
        system("pause>nul");
        return;
    }

    _archivoSocios.leerTodos(cantidadSocios, socios);

    float *recaudacionSocios = nullptr;
    recaudacionSocios = new float[cantidadSocios];


    if(recaudacionSocios == nullptr)
    {
        mensajeError("Err asignacion memoria.");
        system("pause>nul");
        return;
    }

    /// pongo en 0 el vector (si lo inicio en 0 asi: recaudacionSocios = {0};. se rompe el codigo
    for(int i = 0; i<cantidadSocios; i++){recaudacionSocios[i] = 0;}

    /// Acumulo el importe de los pagos por socio

    for (int i = 0; i < cantidadPagos; i++)
    {
        int idSocio = pagos[i].getIdSocio() - 1;
        if (idSocio >= 0)
        {
            float importe = pagos[i].getImporte();
            recaudacionSocios[idSocio] += importe;
        }
    }

    /// Buscar posici�n de mayor recaudaci�n

    int posMax = encontrarPosicionMaxima(recaudacionSocios, cantidadSocios);
    /// Encabezado

    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(20) << "ID Socio" << (char)179
         << left << setw(20) << "Nombre" << (char)179
         << left << setw(15) << "Recaudacion" << (char)179 << endl;

    /// Socios

    for(int i = 0; i< cantidadSocios; i++)
    {
        rlutil::setBackgroundColor(rlutil::WHITE);
        rlutil::setColor(rlutil::BLACK);
        cout << (char)179 << left << setw(20) << socios[i].getIdSocio() << (char)179
             << left << setw(20) << socios[i].getNombre() << (char)179
             << left << setw(15) << recaudacionSocios[i] << (char)179 << endl;
    }

    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(20) << "ID Socio" << (char)179
         << left << setw(20) << "Nombre" << (char)179
         << left << setw(15) << "Recaudacion" << (char)179 << endl;
    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);

    cout << (char)179 << left << setw(20) << socios[posMax].getIdSocio() << (char)179
         << left << setw(20) << socios[posMax].getNombre() << (char)179
         << left << setw(15) << recaudacionSocios[posMax] << (char)179 << endl;

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::resetColor();
    system("pause>nul");

    delete[] pagos;
    delete[] socios;
    delete[] recaudacionSocios;
}

void ManagerReportes::recaudacionPorInscripcion()
{
    system("cls");
    cout<<"REPORTE POR INSCRIPCIONES"<<endl;
    cout<<"-------------"<<endl;
    int cantidadInscripciones = _archivoInscripciones.getCantidadRegistros();
    if (cantidadInscripciones <= 0)
    {
        mensajeError("No hay inscripciones registradas.");
        system("pause>nul");
        return;
    }

    Inscripcion* inscripciones = nullptr;
    inscripciones = new Inscripcion[cantidadInscripciones];

    if(inscripciones == nullptr)
    {
        mensajeError("Err asignacion memoria.");
        system("pause>nul");
        return;
    }

    _archivoInscripciones.leerTodos(cantidadInscripciones, inscripciones);

    int cantidadPagos = _archivoPagos.getCantidadRegistros();
    if (cantidadPagos <= 0)
    {
        mensajeError("No hay pagos registrados.");
        system("pause>nul");
        return;
    }

    Pago* pagos = nullptr;
    pagos = new Pago[cantidadPagos];

    if(pagos == nullptr)
    {
        mensajeError("Err asignacion memoria.");
        system("pause>nul");
        return;
    }

    _archivoPagos.leerTodos(cantidadPagos, pagos);

    float* recaudacionInscripciones = new float[cantidadInscripciones]();
    for(int i = 0; i<cantidadInscripciones; i++){recaudacionInscripciones[i] = 0;}

    /// Acumulo el importe de los pagos en el registro pagos
    for (int i = 0; i < cantidadPagos; i++)
    {
        int idActividad = pagos[i].getIdActividad() - 1;
        if (idActividad >= 0 && idActividad < cantidadInscripciones)
        {
            float importe = pagos[i].getImporte();
            recaudacionInscripciones[idActividad] += importe;
        }
    }

    /// Buscar posici��n de mayor recaudaci��n
    int posMax = encontrarPosicionMaxima(recaudacionInscripciones, cantidadInscripciones);

    /// Encabezado
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);

    cout << (char)179 << left << setw(20) << "ID Inscrip." << (char)179
         << left << setw(20) << "ID Socio" << (char)179
         << left << setw(20) << "ID Actividad" << (char)179
         << left << setw(15) << "Recaudacion" << (char)179 << endl;
    /// Inscripciones
    for(int i = 0; i< cantidadInscripciones; i++)
    {
        rlutil::setBackgroundColor(rlutil::WHITE);
        rlutil::setColor(rlutil::BLACK);
        cout << (char)179 << left << setw(20) << inscripciones[i].getIdActividad() << (char)179
             << left << setw(20) << inscripciones[i].getIdSocio() << (char)179
             << left << setw(20) << inscripciones[i].getIdActividad() << (char)179
             << left << setw(15) << recaudacionInscripciones[i] << (char)179 << endl;
    }

    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);

    cout << (char)179 << left << setw(20) << "ID Inscrip." << (char)179
         << left << setw(20) << "ID Socio" << (char)179
         << left << setw(20) << "ID Actividad" << (char)179
         << left << setw(15) << "Recaudacion" << (char)179 << endl;
    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(20) << inscripciones[posMax].getIdActividad() << (char)179
         << left << setw(20) << inscripciones[posMax].getIdSocio() << (char)179
         << left << setw(20) << inscripciones[posMax].getIdActividad() << (char)179
         << left << setw(15) << recaudacionInscripciones[posMax] << (char)179 << endl;

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::resetColor();
    system("pause>nul");
    delete[] recaudacionInscripciones;
    delete[] inscripciones;
    delete[] pagos;
}


float ManagerReportes::encontrarPosicionMaxima(float vec[], int tam)
{
    if (tam <= 0)
    {
        return -1;
    }

    int posMax = 0;

    for(int i = 1; i< tam; i++)
    {
        if(vec[i] > vec[posMax])
        {
            posMax = i;
        }
    }

    return posMax;
};
