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
    cout << "Reporte por actividades" << endl << endl;

    /// Leer pagos
    int cantidadPagos = _archivoPagos.getCantidadRegistros();
    if (cantidadPagos <= 0) {
        mensajeError("No hay pagos registrados.");
        system("pause>nul");
        return;
    }

    Pago* pagos = new Pago[cantidadPagos];
    _archivoPagos.leerTodos(cantidadPagos, pagos);

    /// Leer actividades
    int cantActividades = _archivoActividades.getCantidadRegistros();
    if (cantActividades <= 0) {
        mensajeError("No hay actividades registradas.");
        system("pause>nul");
        delete[] pagos;
        return;
    }

    Actividad* regActividades = new Actividad[cantActividades];
    float* recaudacionActividades = new float[cantActividades]{}; // inicializa en 0
    _archivoActividades.leerTodos(cantActividades, regActividades);

    /// Leer inscripciones
    int cantidadInscripciones = _archivoInscripciones.getCantidadRegistros();
    if (cantidadInscripciones <= 0) {
        mensajeError("No hay inscripciones registradas.");
        system("pause>nul");
        delete[] pagos;
        delete[] regActividades;
        delete[] recaudacionActividades;
        return;
    }

    Inscripcion* inscripciones = new Inscripcion[cantidadInscripciones];
    int* inscripcionPorActividad = new int[cantActividades](); // inicializa en 0
    _archivoInscripciones.leerTodos(cantidadInscripciones, inscripciones);

    /// Acumular recaudación e inscripciones por actividad
    for (int i = 0; i < cantidadPagos; i++) {
        int idAct = pagos[i].getIdActividad() - 1;
        recaudacionActividades[idAct] += pagos[i].getImporte();
    }
    
    for (int i = 0; i < cantidadInscripciones; i++) {
        int idAc = inscripciones[i].getIdActividad() - 1;
        inscripcionPorActividad[idAc]++;
    }

    /// Buscar actividad con mayor recaudación
    int posMax = encontrarPosicionMaxima(recaudacionActividades, cantActividades);

    /// Mostrar tabla
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(20) << "ID Actividad" << (char)179
         << left << setw(30) << "Nombre" << (char)179
         << left << setw(15) << "Inscripciones" << (char)179
         << left << setw(15) << "Recaudacion" << (char)179 << endl;

    for (int i = 0; i < cantActividades; i++) {
        if (i == posMax) rlutil::setBackgroundColor(rlutil::LIGHTCYAN);
        else if (recaudacionActividades[i] <= 0) rlutil::setBackgroundColor(rlutil::WHITE);
        else rlutil::setBackgroundColor(rlutil::GREY);

        rlutil::setColor(rlutil::BLACK);
        cout << (char)179 << left << setw(20) << regActividades[i].getIdActividad() << (char)179
             << left << setw(30) << truncar(regActividades[i].getNombre(), 30) << (char)179
             << left << setw(15) << inscripcionPorActividad[i] << (char)179
             << left << setw(15) << recaudacionActividades[i] << (char)179;
        
        cout << endl;
    }

    cout << endl;
    rlutil::setBackgroundColor(rlutil::LIGHTCYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << left << setw(20) << " * Actividad con mas recaudacion * " << endl;

    cout << regActividades[posMax].getNombre() << " con " << inscripcionPorActividad[posMax] << " inscripciones y $" << recaudacionActividades[posMax] << " de recaudacion" << endl;
    

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::resetColor();
    system("pause>nul");

    /// Liberar memoria
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
    cout << (char)179 << left << setw(20) << " Reporte Mes " << setw(19) << right << (char)179 << endl;
    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);
    cout << endl;

    float meses[12] = {0}; // recaudación por mes
    int inscripcionesXmes[12] = {0};
    float recaudacionAnio = 0; // total anual
    int inscripcionesAnio = 0;

    /// Leer pagos
    int cantidadPagos = _archivoPagos.getCantidadRegistros();
    if (cantidadPagos <= 0) {
        mensajeError("No hay pagos registrados.");
        system("pause>nul");
        return;
    }
    Pago* pagos = new Pago[cantidadPagos];
    _archivoPagos.leerTodos(cantidadPagos, pagos);

    /// Leer inscripciones
    int cantidadInscripciones = _archivoInscripciones.getCantidadRegistros();
    if (cantidadInscripciones <= 0) {
        mensajeError("No hay Inscripciones registradas.");
        system("pause>nul");
        delete[] pagos;
        return;
    }
    Inscripcion* inscripciones = new Inscripcion[cantidadInscripciones];
    _archivoInscripciones.leerTodos(cantidadInscripciones, inscripciones);

    /// Acumular recaudación e inscripciones por mes
    for (int i = 0; i < cantidadPagos; i++) {
        int mes = pagos[i].getFechaDePago().getMes() - 1;
        if (mes >= 0 && mes < 12) {
            meses[mes] += pagos[i].getImporte();
            recaudacionAnio += pagos[i].getImporte();
        }
    }
    for (int i = 0; i < cantidadInscripciones; i++) {
        int mesInscripcion = inscripciones[i].getFechaInscripcion().getMes() - 1;
        if (mesInscripcion >= 0 && mesInscripcion < 12) {
            inscripcionesXmes[mesInscripcion]++;
            inscripcionesAnio++;
        }
    }

    int mesMasRecaudador = encontrarPosicionMaxima(meses, 12);
    string nombreMeses[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

    /// Mostrar tabla
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(12) << "MES" << (char)179
         << left << setw(12) << "INSCRIPCION" << (char)179
         << left << setw(12) << "RECAUDACION" << (char)179 << endl;

    for (int i = 0; i < 12; i++) {
        if (i == mesMasRecaudador) rlutil::setBackgroundColor(rlutil::YELLOW);
        else rlutil::setBackgroundColor(rlutil::WHITE);
        rlutil::setColor(rlutil::BLACK);
        cout << (char)179 << left << setw(12) << nombreMeses[i] << (char)179
             << left << setw(12) << inscripcionesXmes[i] << (char)179
             << left << setw(12) << meses[i] << (char)179 << endl;
    }

    /// Totales
    cout << endl;
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(17) << " Recaudacion del anio" << setw(18) << right << (char)179 << endl;

    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(12) << "Total Anio " << (char)179
         << left << setw(12) << inscripcionesAnio << (char)179
         << left << setw(12) << recaudacionAnio << (char)179 << endl;

    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(17) << " Mes con mas recaudacion" << setw(15) << right << (char)179 << endl;

    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(12) << nombreMeses[mesMasRecaudador] << (char)179
         << left << setw(12) << inscripcionesXmes[mesMasRecaudador] << (char)179
         << left << setw(12) << meses[mesMasRecaudador] << (char)179 << endl;

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::resetColor();
    system("pause>nul");
    delete[] pagos;
    delete[] inscripciones;
}

void ManagerReportes::recaudacionPorSocio()
{
    system("cls");
    cout << "Reporte por socio" << endl << endl;

    /// Leer pagos
    int cantidadPagos = _archivoPagos.getCantidadRegistros();
    if (cantidadPagos <= 0) {
        mensajeError("No hay pagos registrados.");
        system("pause>nul");
        return;
    }
    Pago* pagos = new Pago[cantidadPagos];
    _archivoPagos.leerTodos(cantidadPagos, pagos);

    /// Leer socios
    int cantidadSocios = _archivoSocios.getCantidadRegistros();
    if (cantidadSocios <= 0) {
        mensajeError("No hay socios registrados.");
        system("pause>nul");
        delete[] pagos;
        return;
    }
    Socio* socios = new Socio[cantidadSocios];
    _archivoSocios.leerTodos(cantidadSocios, socios);

    /// Leer inscripciones
    int cantidadInscripciones = _archivoInscripciones.getCantidadRegistros();
    if (cantidadInscripciones <= 0) {
        mensajeError("No hay inscripciones registradas.");
        system("pause>nul");
        delete[] pagos;
        delete[] socios;
        return;
    }
    Inscripcion* inscripciones = new Inscripcion[cantidadInscripciones];
    _archivoInscripciones.leerTodos(cantidadInscripciones, inscripciones);

    /// Inicializar acumuladores
    float* recaudacionSocios = new float[cantidadSocios]{}; // inicializa en 0
    int* inscripcionPorSocio = new int[cantidadSocios]{};   // inicializa en 0

    /// Acumular recaudación e inscripciones por socio
    for (int i = 0; i < cantidadPagos; i++) {
        int idSocio = pagos[i].getIdSocio();
        recaudacionSocios[idSocio - 1] += pagos[i].getImporte();
    }

    for (int i = 0; i < cantidadInscripciones; i++) {
        int idSoc = inscripciones[i].getIdSocio();
        inscripcionPorSocio[idSoc - 1]++;
    }

    /// Buscar socio con mayor recaudación
    int posMax = encontrarPosicionMaxima(recaudacionSocios, cantidadSocios);

    /// Mostrar tabla
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(20) << "ID Socio" << (char)179
         << left << setw(20) << "Nombre" << (char)179
         << left << setw(15) << "Inscripciones" << (char)179
         << left << setw(15) << "Recaudacion" << (char)179 << endl;

    for (int i = 0; i < cantidadSocios; i++) {
        if (i == posMax) rlutil::setBackgroundColor(rlutil::LIGHTCYAN);
        else if (recaudacionSocios[i] <= 0) rlutil::setBackgroundColor(rlutil::WHITE);
        else rlutil::setBackgroundColor(rlutil::GREY);

        rlutil::setColor(rlutil::BLACK);
        cout << (char)179 << left << setw(20) << socios[i].getIdSocio() << (char)179
             << left << setw(20) << socios[i].getNombre() + " " + socios[i].getApellido() << (char)179
             << left << setw(15) << inscripcionPorSocio[i] << (char)179
             << left << setw(15) << recaudacionSocios[i] << (char)179 << endl;
    }

    rlutil::setBackgroundColor(rlutil::BLACK);
    cout << endl;

    ///Mensaje Destacado
    rlutil::setBackgroundColor(rlutil::LIGHTCYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << "* Socio con mas recaudacion *";
    rlutil::setBackgroundColor(rlutil::BLACK);
    cout << endl;
    rlutil::setBackgroundColor(rlutil::LIGHTCYAN);
    cout << socios[posMax].getNombre() << " con " << inscripcionPorSocio[posMax] << " inscripciones y $" << recaudacionSocios[posMax] << " de recaudacion";
    rlutil::resetColor();

    system("pause>nul");
    /// Liberar memoria
    delete[] pagos;
    delete[] socios;
    delete[] recaudacionSocios;
    delete[] inscripciones;
    delete[] inscripcionPorSocio;
}

void ManagerReportes::recaudacionPorInscripcion()
{
    system("cls");
    
    // Formulario para seleccionar el año
    int anioSeleccionado;
    bool anioValido = false;
    imprimirFormulario("Reporte de inscripciones por mes");
    
    do {
        limpiarError();
        mensajeFormulario(2, "Ingrese el anio para el reporte: ");
        cin >> anioSeleccionado;
        cin.ignore();
        
        // Validar año 
        if (anioSeleccionado >= 1900) {
            anioValido = true;
        } else {
            mensajeError("Anio invalido. Debe ser mayor a 1900.");
        }
    } while (!anioValido);
    
    /// Verificar si hay inscripciones
    int cantidadInscripciones = _archivoInscripciones.getCantidadRegistros();
    if (cantidadInscripciones <= 0) {
        mensajeError("No hay inscripciones registradas.");
        system("pause>nul");
        return;
    }

    /// Leer inscripciones y verificar si hay para el año seleccionado
    Inscripcion* inscripciones = new Inscripcion[cantidadInscripciones];
    _archivoInscripciones.leerTodos(cantidadInscripciones, inscripciones);

    bool hayInscripcionesAnio = false;
    for (int i = 0; i < cantidadInscripciones; i++) {
        if (inscripciones[i].getFechaInscripcion().getAnio() == anioSeleccionado) {
            hayInscripcionesAnio = true;
            break;
        }
    }

    if (!hayInscripcionesAnio) {
        mensajeError("No hay inscripciones registradas para el anio " + to_string(anioSeleccionado));
        delete[] inscripciones;
        system("pause>nul");
        return;
    }
    
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::WHITE);
    system("cls");
    cout << "REPORTE DE INSCRIPCIONES POR MES - ANIO " << anioSeleccionado << endl;
    cout << "----------------------------------------" << endl;

    int meses[12] = {0};
    int totalAnio = 0;

    /// Acumular inscripciones por mes (solo del año seleccionado)
    for (int i = 0; i < cantidadInscripciones; i++) {
        int mes = inscripciones[i].getFechaInscripcion().getMes();
        int anio = inscripciones[i].getFechaInscripcion().getAnio();
        
        // Solo contar inscripciones del año seleccionado
        if (anio == anioSeleccionado && mes > 0 && mes <= 12) {
            meses[mes - 1]++;
            totalAnio++;
        }
    }

    int mesMasRecaudador = encontrarPosicionMaxima(meses, 12);
    string nombreMeses[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

    /// Mostrar Encabezado
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(15) << "Mes" << (char)179
         << left << setw(15) << "Inscripciones" << (char)179;
    rlutil::setBackgroundColor(rlutil::BLACK);
    cout << endl;

    /// Mostrar tabla
    for (int i = 0; i < 12; i++) {
        if (i == mesMasRecaudador) rlutil::setBackgroundColor(rlutil::YELLOW);
        else rlutil::setBackgroundColor(rlutil::WHITE);

        rlutil::setColor(rlutil::BLACK);
        cout << (char)179 << left << setw(15) << nombreMeses[i] << (char)179
             << left << setw(15) << meses[i] << (char)179;
        rlutil::setBackgroundColor(rlutil::BLACK);
        cout << endl;
    }

    cout << endl;
    /// Totales
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << "* Mes con mas inscripciones *";
    rlutil::setBackgroundColor(rlutil::BLACK);
    cout << endl;

    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);
    cout << nombreMeses[mesMasRecaudador] << " con " << meses[mesMasRecaudador] << " inscripciones";
    rlutil::setBackgroundColor(rlutil::BLACK);
    cout << endl << endl;
    
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << "* Total de inscripciones del anio " << anioSeleccionado << " *";
    rlutil::setBackgroundColor(rlutil::BLACK);
    cout << endl;

    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);
    cout << totalAnio << " inscripciones";
    rlutil::setBackgroundColor(rlutil::BLACK);
    cout << endl;

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

    for(int i = 1; i < tam; i++) // Empezar desde i=1 ya que posMax=0
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
