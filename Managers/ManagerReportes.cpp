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

    /// PAGOS

    int cantidadPagos = _archivoPagos.getCantidadRegistros();
    if (cantidadPagos <= 0)
    {
        mensajeError("No hay pagos registrados.");
        system("pause>nul");
        return;
    }

    Pago* pagos = nullptr;
    pagos = new Pago[cantidadPagos];

    _archivoPagos.leerTodos(cantidadPagos, pagos);

    /// ACTIVIDADES
    int cantActividades = _archivoActividades.getCantidadRegistros();
    if (cantActividades <= 0)
    {
        mensajeError("No hay actividades registradas.");
        system("pause>nul");
        return;
    }

    Actividad* regActividades = new Actividad[cantActividades];
    float* recaudacionActividades = new float[cantActividades];

    _archivoActividades.leerTodos(cantActividades, regActividades);

    /// INSCRIPCIONES
    int cantidadInscripciones = _archivoInscripciones.getCantidadRegistros();
    if (cantidadInscripciones <= 0)
    {
        mensajeError("No hay inscripciones registradas.");
        system("pause>nul");
        return;
    }

    Inscripcion* inscripciones = nullptr;
    inscripciones = new Inscripcion[cantidadInscripciones];

    float *inscripcionPorActividad = nullptr;
    inscripcionPorActividad = new float[cantActividades];

    _archivoInscripciones.leerTodos(cantidadInscripciones, inscripciones);


    for(int i = 0; i<cantActividades; i++)
        {
            recaudacionActividades[i] = 0;
            inscripcionPorActividad[i] = 0;
        }

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
    /// Acumulo inscripciones por actividad
    for (int i = 0; i < cantidadInscripciones; i++)
        {
            int idAc = inscripciones[i].getIdActividad();
            inscripcionPorActividad[idAc]++;
        }

    /// Buscar posicin de actividad con mas recaudacion
    int posMax = encontrarPosicionMaxima(recaudacionActividades, cantActividades);
    int InsMax = encontrarPosicionMaxima(inscripcionPorActividad, cantActividades);
    /// Encabezado
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(20) << "ID Actividad" << (char)179
         << left << setw(20) << "Nombre" << (char)179
         << left << setw(15) << "Inscripciones" << (char)179
         << left << setw(15) << "Recaudacion" << (char)179 << endl;
    /// Actividades
    for(int i = 0; i< cantActividades; i++)
    {
        if(i == posMax)
        {
            rlutil::setBackgroundColor(rlutil::LIGHTCYAN);
        }
        else if(recaudacionActividades[i] <= 0)
            {
                rlutil::setBackgroundColor(rlutil::WHITE);
            }
        else if(recaudacionActividades[i] >= 0)
            {
                rlutil::setBackgroundColor(rlutil::GREY);
            }

        rlutil::setColor(rlutil::BLACK);
        cout << (char)179 << left << setw(20) << regActividades[i].getIdActividad() << (char)179
             << left << setw(20) << regActividades[i].getNombre() << (char)179
             << left << setw(15) << inscripcionPorActividad[i] << (char)179
             << left << setw(15) << recaudacionActividades[i] << (char)179;

        if(i == posMax){cout << left << setw(20) << " * Mas recaudacion" << (char)179 << endl;}
        //else if (i == InsMax){cout << left << setw(20) << "Mas Inscripciones" << (char)179 << endl;}
                else{cout<<endl;}
    }

    /*
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(20) << "ID Actividad" << (char)179
         << left << setw(20) << "Nombre" << (char)179
         << left << setw(15) << "Inscripciones" << (char)179
         << left << setw(15) << "Recaudacion" << (char)179 << endl;

    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(20) << regActividades[posMax].getIdActividad() << (char)179
         << left << setw(20) << regActividades[posMax].getNombre() << (char)179
         << left << setw(15) << inscripcionPorActividad[posMax] << (char)179
         << left << setw(15) << recaudacionActividades[posMax] << (char)179 << endl;*/

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::resetColor();
    system("pause>nul");

    delete[] pagos;
    delete[] regActividades;
    delete[] recaudacionActividades;
    delete[] inscripciones;
    delete[] inscripcionPorActividad;

}

void ManagerReportes::recaudacionPorMes()
{
    system("cls");

    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(20) << " Reporte Mes " << setw(19)<<right << (char)179;
    cout << endl;

    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);
    cout << endl;

    float meses[12] = {0}; // vector para acumular por mes
    int recaudacionAnio = 0; // Acumula todo el ao
    int inscripcionesXmes[12] = {0};
    int inscripcionesAnio = 0;

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

    _archivoPagos.leerTodos(cantidadPagos, pagos);

    int cantidadInscripciones = _archivoInscripciones.getCantidadRegistros();
    if (cantidadInscripciones <= 0)
    {
        mensajeError("No hay Inscripciones registradas.");
        system("pause>nul");
        return;
    }

    Inscripcion* inscripciones = nullptr;
    inscripciones = new Inscripcion[cantidadInscripciones];

    _archivoInscripciones.leerTodos(cantidadInscripciones, inscripciones);


    for (int i = 0; i < cantidadPagos; i++)
    {
        int mes = pagos[i].getFechaDePago().getMes() - 1;
        meses[mes] += pagos[i].getImporte();
        recaudacionAnio += pagos[i].getImporte();
    }

    for (int i = 0; i < cantidadInscripciones; i++)
        {
            int mesInscripcion = inscripciones[i].getFechaInscripcion().getMes() -1 ;
            inscripcionesXmes[mesInscripcion]++;
            inscripcionesAnio++;
        }


    int mesMasRecaudador = encontrarPosicionMaxima(meses, 12);
    // ENCABEZADO
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(12) << "MES" << (char)179
        << left << setw(12) << "INSCRIPCION" << (char)179
        << left << setw(12) << "RECAUDACION" << (char)179;

    cout << endl;
    // FIN ENCABEZADO

    string nombreMeses[12] =
    {
        "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
        "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
    };

    for (int i = 0; i < 12; i++)
    {
        if(i == mesMasRecaudador)
            {
            rlutil::setBackgroundColor(rlutil::YELLOW);
            }
        else
            {
            rlutil::setBackgroundColor(rlutil::WHITE);
            }


        rlutil::setColor(rlutil::BLACK);
        cout << (char)179 << left << setw(12) << nombreMeses[i] << (char)179;
        cout << left << setw(12) << inscripcionesXmes[i] << (char)179;
        cout << left << setw(12) << meses[i] << (char)179;
        cout << endl;
    }

    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);
    cout << endl;

    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(17) << " Recaudacion del anio" << setw(18)<<right << (char)179;
    cout << endl;

    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(12) << "Total Anio "<< (char)179;
    cout << left << setw(12) << inscripcionesAnio << (char)179 ;
    cout << left << setw(12) << recaudacionAnio << (char)179 ;
    cout << endl;

    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(17) << " Mes con mas recaudacion" << setw(15)<<right << (char)179;
    cout << endl;

    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(12) << nombreMeses[mesMasRecaudador] << (char)179;
    cout << left << setw(12) << inscripcionesXmes[mesMasRecaudador] << (char)179 ;
    cout << left << setw(12) << meses[mesMasRecaudador] << (char)179 ;
    cout << endl;


    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::resetColor();
    system("pause>nul");

    delete[] pagos;
    delete[] inscripciones;
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

    _archivoSocios.leerTodos(cantidadSocios, socios);

    int cantidadInscripciones = _archivoInscripciones.getCantidadRegistros();
    if (cantidadInscripciones <= 0)
    {
        mensajeError("No hay pagos registrados.");
        system("pause>nul");
        return;
    }

    Inscripcion* inscripciones = nullptr;
    inscripciones = new Inscripcion[cantidadInscripciones];

    _archivoInscripciones.leerTodos(cantidadInscripciones, inscripciones);


    float *recaudacionSocios = nullptr;
    recaudacionSocios = new float[cantidadSocios];

    int *inscripcionPorSocio = nullptr;
    inscripcionPorSocio = new int[cantidadSocios];

    if(recaudacionSocios == nullptr || inscripcionPorSocio == nullptr )
    {
        mensajeError("Err asignacion memoria.");
        system("pause>nul");
        return;
    }

    /// pongo en 0 el vector (si lo inicio en 0 asi: recaudacionSocios = {0};. se rompe el codigo
    for(int i = 0; i<cantidadSocios; i++)
        {
            recaudacionSocios[i] = 0;
            inscripcionPorSocio[i] = 0;
        }


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

    for (int i = 0; i < cantidadInscripciones; i++)
        {
            int idSoc = inscripciones[i].getIdSocio();
            inscripcionPorSocio[idSoc]++;
        }


    /// Buscar posicin de mayor recaudacin

    int posMax = encontrarPosicionMaxima(recaudacionSocios, cantidadSocios);
    /// Encabezado

    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(20) << "ID Socio" << (char)179
         << left << setw(20) << "Nombre" << (char)179
         << left << setw(15) << "Inscripciones" << (char)179
         << left << setw(15) << "Recaudacion" << (char)179  << endl;

    /// Socios

    for(int i = 0; i< cantidadSocios; i++)
    {
        if(i == posMax)
            {
                rlutil::setBackgroundColor(rlutil::LIGHTCYAN);
            }
        else if(recaudacionSocios[i] <= 0)
            {
                rlutil::setBackgroundColor(rlutil::WHITE);
            }
        else if(recaudacionSocios[i] >= 0)
            {
                rlutil::setBackgroundColor(rlutil::GREY);
            }
        rlutil::setColor(rlutil::BLACK);
        cout << (char)179 << left << setw(20) << socios[i].getIdSocio() << (char)179
             << left << setw(20) << socios[i].getNombre() << (char)179
             << left << setw(15) << inscripcionPorSocio[i] << (char)179
             << left << setw(15) << recaudacionSocios[i] << (char)179;
        if(i ==  posMax)
            {
                cout << left << setw(20) << " * Mas recaudacion " << (char)179 << endl;
            }
        else{cout<<endl;}
    }

    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);
    cout << endl;

    /*
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(20) << "Socio Mas recaudador" << (char)179 << endl;
    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);

    cout << (char)179 << left << setw(20) << socios[posMax].getIdSocio() << (char)179
    << left << setw(20) << socios[posMax].getNombre() << (char)179
    << left << setw(15) << inscripcionPorSocio[posMax] << (char)179
    << left << setw(15) << recaudacionSocios[posMax] << (char)179 << endl;*/

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::resetColor();
    system("pause>nul");

    delete[] pagos;
    delete[] socios;
    delete[] recaudacionSocios;
    delete[] inscripciones;
    delete[] inscripcionPorSocio;
}

void ManagerReportes::recaudacionPorInscripcion()
{
    system("cls");
    cout<<"REPORTE POR INSCRIPCIONES"<<endl;
    cout<<"-------------"<<endl;

    int meses[12] = {0};
    int totalAnio = 0;


    int cantidadInscripciones = _archivoInscripciones.getCantidadRegistros();
    if (cantidadInscripciones <= 0)
    {
        mensajeError("No hay pagos registrados.");
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

    for (int i = 0; i < cantidadInscripciones; i++)
    {
        int mes =  inscripciones[i].getFechaInscripcion().getMes();
        meses[mes-1]++;
        totalAnio++ ;
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
        if (i == mesMasRecaudador)
        {
            rlutil::setBackgroundColor(rlutil::YELLOW);
        }
        else
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
    cout << left << setw(12) << totalAnio << (char)179 ;
    cout << endl;

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::resetColor();
    system("pause>nul");
    delete[] inscripciones;
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
}

int ManagerReportes::encontrarPosicionMaxima(int vec[], int tam)
{
    if (tam <= 0)
    {
        return -1;
    }

    int posMax = 0;

    for(int i = 1; i < tam; i++)
    {
        if(vec[i] > vec[posMax])
        {
            posMax = i;
        }
    }

    return posMax;
}