#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include "ManagerPagos.h"
#include "../funcionesConsola.h"
#include "../rlutil.h"

using namespace std;

ManagerPagos::ManagerPagos()
    : _archivoSocios("Socios.dat"),
      _archivoPagos("Pagos.dat"),
      _archivoActividades("Actividades.dat")
{
}

void ManagerPagos::agregar()
{
    /// Estetico
    imprimirFormulario("Registrar nuevo Pago");
    rlutil::setColor(rlutil::BLACK);
    rlutil::setBackgroundColor(rlutil::WHITE);
    ///---------

    /// Validar que existan actividades y socios para poder realizar un pago
    int cantidadActividades = _archivoActividades.getCantidadRegistros();
    if (cantidadActividades <= 0)
    {
        mensajeError("No hay actividades registradas para poder realizar un pago.");
        system("pause>nul");
        return;
    }

    int cantidadSocios = _archivoSocios.getCantidadRegistros();
    if (cantidadSocios <= 0)
    {
        mensajeError("No hay socios registrados para poder realizar un pago.");
        system("pause>nul");
        return;
    }
    ///---------

    /// Pedir ID de socio y validar que exista
    int idSocio = pedirIdSocio();
    int posicionSocio = _archivoSocios.buscar(idSocio);
    if (posicionSocio == -1)
    {
        mensajeError("El socio ingresado no existe.");
        system("pause>nul");
        return;
    }


    /// Leer socio y validar que no este eliminado
    Socio socio = _archivoSocios.leer(posicionSocio);
    if (socio.getEliminado())
    {
        mensajeError("El socio ingresado se encuentra eliminado.");
        system("pause>nul");
        return;
    }
    ///---------

    /// Pedir ID de actividad y validar que exista
    int idActividad = pedirIdActividad();
    int posicionActividad = _archivoActividades.buscar(idActividad);
    if (posicionActividad == -1)
    {
        mensajeError("La actividad ingresada no existe.");
        system("pause>nul");
        return;
    }


    /// Leer actividad y validar que no este eliminada
    Actividad actividad = _archivoActividades.leer(posicionActividad);
    if (actividad.getEliminado())
    {
        mensajeError("La actividad ingresada se encuentra eliminada.");
        system("pause>nul");
        return;
    }
    int posicionPago = _archivoPagos.buscar(socio.getIdSocio(), actividad.getIdActividad());
    if (posicionPago != -1)
    {
        mensajeError("Ya existe un pago registrado para el socio y la actividad ingresados.");
        system("pause>nul");
        return;
    }

    /// Pedir importe y validar que sea mayor a 0
    // int importe = pedirImporte();


    float importe = actividad.getArancel();
    string importeString =  truncarFloatDosDecimales(importe);
    mensajeFormulario(3, "El importe a abonar es: $" + importeString + " Deseas continuar? (s/n): ");
    string respuesta;

    getline(cin, respuesta);
    //
    if (respuesta != "s" && respuesta != "S")
    {
        mensajeError("Operación cancelada por el usuario.");
        system("pause>nul");
        return;
    }
    Pago pago;
    pago.setIdSocio(socio.getIdSocio());
    pago.setIdActividad(actividad.getIdActividad());
    pago.setImporte(importe);
    pedirMetodoDePago(pago);

    // Fecha fecha;
    /// Pedir fecha de pago
    // mensajeFormulario(5, "Fecha del pago:");
    // pedirAnio(fecha);
    // pedirMes(fecha);
    // pedirDia(fecha);
    // pago.setFechaDePago(fecha);

    /// Validar que la fecha de pago no sea posterior a la fecha actual
    Fecha fechaActual(true);
    pago.setFechaDePago(fechaActual);
    Fecha fechaPago = pago.getFechaDePago();

    /// cout con datos del pago para ver que no guarde basura
    // cout << "Datos del pago:" << endl;
    // cout << "ID Socio: " << pago.getIdSocio() << endl;
    // cout << "ID Actividad: " << pago.getIdActividad() << endl;
    // cout << "Importe: $" << pago.getImporte() << endl;
    // cout << "Fecha de Pago: " << pago.getFechaDePago().toString() << endl;
    // cout << "Metodo de Pago: " << pago.getMetodoDePago() << endl;
    // cout << "Fecha actual: " << fechaActual.toString() << endl;
    // system("pause>nul");

    if (fechaPago > fechaActual)
    {
        mensajeError("No se puede realizar un pago en una fecha posterior a la fecha actual.");
        system("pause>nul");
        return;
    }
    if (actividad.getFechaInicio() < fechaPago)
    {
        mensajeError("No se puede realizar un pago en una fecha posterior a la fecha de inicio de la actividad.");
        system("pause>nul");
        return;
    }

    bool ok = _archivoPagos.guardar(pago);
    if (!ok)
    {
        mensajeError("Error al guardar el pago.");
        system("pause>nul");
        return;
    }
    mensajeExito("Pago agregado correctamente.");
    system("pause>nul");
}

/// Lista todos los pagos registrados en el sistema.
void ManagerPagos::listar()
{
    system("cls");
    int cantidadRegistros = _archivoPagos.getCantidadRegistros();
    if (cantidadRegistros <= 0)
    { /// si es 0 no hay pagos, pero puede ser -1 que significa error
        mensajeError("No hay pagos registrados.");
        system("pause>nul");
        return;
    }

    Pago *pagos = new Pago[cantidadRegistros];
    _archivoPagos.leerTodos(cantidadRegistros, pagos);

    mostrarEncabezadoTabla();

    for (int i = 0; i < cantidadRegistros; i++)
    {
        /// Intercalar colores, solo estetico.
        if (i % 2 == 0)
        {
            rlutil::setBackgroundColor(rlutil::GREY);
        }
        else
        {
            rlutil::setBackgroundColor(rlutil::WHITE);
        }
        mostrarPago(pagos[i]);
        cout << endl;
    }

    system("pause>nul");
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::resetColor();
    delete[] pagos;
}

void ManagerPagos::listarPagosSocio()
{
    system("cls");
    imprimirFormulario("Listar Pagos de Socio");

    int idSocio = pedirIdSocio();
    int posicion = _archivoSocios.buscar(idSocio);
    Socio socio = _archivoSocios.leer(posicion);
    if (socio.getEliminado())
    {
        mensajeError("El socio ingresado se encuentra eliminado.");
        system("pause>nul");
        return;
    }
    int cantidadRegistros = _archivoPagos.getCantidadRegistros();
    if (cantidadRegistros <= 0)
    { /// si es 0 no hay pagos, pero puede ser -1 que significa error
        mensajeError("No hay pagos registrados.");
        system("pause>nul");
        return;
    }

    Pago *pagos = new Pago[cantidadRegistros];
    _archivoPagos.leerTodos(cantidadRegistros, pagos);

        
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::WHITE);
    system("cls");

    cout << "Pagos del socio: " << socio.getNombre() << " " << socio.getApellido() << " (ID: " << socio.getIdSocio() << ")" << endl;
    mostrarEncabezadoTabla();

    int contador = 0;

    for (int i = 0; i < cantidadRegistros; i++)
    {
        // Si el pago no es del socio, lo salteamos
        if (pagos[i].getIdSocio() != socio.getIdSocio())
            continue;
        contador++;
        /// Intercalar colores, solo estetico.
        if (i % 2 == 0)
        {
            rlutil::setBackgroundColor(rlutil::GREY);
        }
        else
        {
            rlutil::setBackgroundColor(rlutil::WHITE);
        }
        mostrarPago(pagos[i]);
        cout << endl;
    }
    if (contador == 0)
        mensajeError("No se encontraron pagos para el socio ingresado.");

    system("pause>nul");
    delete[] pagos;
}

void ManagerPagos::listarPagosActividad()
{
    system("cls");
    imprimirFormulario("Listar Pagos de Actividad");

    int idActividad = pedirIdActividad();
    int posicion = _archivoActividades.buscar(idActividad);
    if (posicion == -1)
    {
        mensajeError("La actividad ingresada no existe");
        system("pause>nul");
        return;
    }

    Actividad actividad = _archivoActividades.leer(posicion);
    if (actividad.getEliminado())
    {
        mensajeError("La actividad ingresada se encuentra eliminada.");
        system("pause>nul");
        return;
    }

    int cantidadRegistros = _archivoPagos.getCantidadRegistros();
    if (cantidadRegistros <= 0)
    { /// si es 0 no hay pagos, pero puede ser -1 que significa error
        mensajeError("No hay pagos registrados.");
        system("pause>nul");
        return;
    }

    Pago *pagos = new Pago[cantidadRegistros];
    _archivoPagos.leerTodos(cantidadRegistros, pagos);

    // Verificar si hay pagos para esta actividad
    bool hayPagos = false;
    for (int i = 0; i < cantidadRegistros; i++)
    {
        if (pagos[i].getIdActividad() == idActividad)
        {
            hayPagos = true;
            break;
        }
    }

    if (!hayPagos)
    {
        mensajeError("No hay pagos registrados para esta actividad.");
        system("pause>nul");
        delete[] pagos;
        return;
    } 

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::WHITE);
    system("cls");

    cout << "Pagos de la actividad: " << actividad.getNombre() << " (ID: " << actividad.getIdActividad() << ")" << endl;
    cout << "Responsable: " << actividad.getResponsable() << endl;
    cout << "Arancel: $" << fixed << setprecision(2) << actividad.getArancel() << endl;

    mostrarEncabezadoTabla();

    int contador = 0;
    float totalRecaudado = 0;

    for (int i = 0; i < cantidadRegistros; i++)
    {
        // Si el pago no es de la actividad, lo salteamos
        if (pagos[i].getIdActividad() != idActividad)
            continue;

        contador++;
        /// Intercalar colores, solo estetico.
        if (contador % 2 == 0)
        {
            rlutil::setBackgroundColor(rlutil::GREY);
        }
        else
        {
            rlutil::setBackgroundColor(rlutil::WHITE);
        }
        rlutil::setColor(rlutil::BLACK);

        mostrarPago(pagos[i]);
        cout << endl;
        totalRecaudado += pagos[i].getImporte();
    }

    // Mostrar total recaudado
    cout << endl << endl;
    rlutil::setBackgroundColor(rlutil::LIGHTCYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << setw(20) << left << "TOTAL RECAUDADO:   $" << setw(10) << fixed << setprecision(2) << totalRecaudado << endl;
    cout << setw(20) << left << "CANTIDAD DE PAGOS: " << setw(10) << contador << endl;

    system("pause>nul");
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::resetColor();
    delete[] pagos;
}

void ManagerPagos::backup()
{
    system("cls");
    imprimirFormulario("Copia de seguridad de Pagos");

    string respuesta;
    bool crearBackup;
    bool resultado;

    while (true)
    {
        limpiarError();
        limpiarLinea(7);

        mensajeFormulario(3, "Deseas crear (c) o aplicar (a) una copia de seguridad? (c/a): ");
        getline(cin, respuesta);

        if (respuesta == "c" || respuesta == "C")
        {
            crearBackup = true;
            break;
        }
        else if (respuesta == "a" || respuesta == "A")
        {
            crearBackup = false;
            break;
        }
        else
        {
            mensajeError("Respuesta invalida. Ingresa 'c' para crear o 'a' para aplicar una copia de seguridad.");
        }
    }

    if (crearBackup)
    {
        resultado = _archivoPagos.crearBackup();
        if (resultado)
        {
            mensajeExito("Copia creada correctamente.");
        }
        else
        {
            mensajeError("Error al crear la copia.");
        }
    }
    else
    {
        resultado = _archivoPagos.usarBackup();
        if (resultado)
        {
            mensajeExito("Copia aplicada correctamente.");
        }
        else
        {
            mensajeError("Error al aplicar la copia.");
        }
    }
    system("pause>nul");
}

void ManagerPagos::mostrarPago(Pago &pago)
{
    Socio socio = _archivoSocios.leer(_archivoSocios.buscar(pago.getIdSocio()));
    Actividad actividad = _archivoActividades.leer(_archivoActividades.buscar(pago.getIdActividad()));

    cout << (char)179 << left << setw(8) << pago.getIdSocio() << (char)179;
    cout << setw(25) << truncar(socio.getNombre() + " " + socio.getApellido(), 25) << (char)179;
    cout << setw(12) << pago.getIdActividad() << (char)179;
    cout << setw(25) << truncar(actividad.getNombre(), 25) << (char)179;
    cout << setw(12) << pago.getFechaDePago().toString() << (char)179;
    cout << setw(12) << pago.getMetodoDePago() << (char)179;
    cout << setw(15) << pago.getImporte() << (char)179;
}

void ManagerPagos::mostrarEncabezadoTabla()
{
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(8) << "ID SOCIO" << (char)179;
    cout << left << setw(25) << "Nombre Socio" << (char)179;
    cout << left << setw(12) << "ID Actividad" << (char)179;
    cout << left << setw(25) << "Nombre Actividad" << (char)179;
    cout << left << setw(12) << "Fecha Pago" << (char)179;
    cout << left << setw(12) << "Metodo Pago" << (char)179;
    cout << left << setw(15) << "Importe" << (char)179;
    cout << endl;
}

void ManagerPagos::pedirMes(Fecha &fecha)
{
    int mes;
    bool mesValido;

    do
    {
        limpiarError();
        limpiarLinea(7);
        mensajeFormulario(7, "Mes: ");
        cin >> mes;
        cin.ignore();

        mesValido = fecha.setMes(mes);
        if (!mesValido)
        {
            mensajeError("Mes invalido");
        }

    } while (!mesValido);
}

void ManagerPagos::pedirDia(Fecha &fecha)
{
    int dia;
    bool diaValido;

    do
    {
        limpiarError();
        limpiarLinea(8);
        mensajeFormulario(8, "Dia: ");
        cin >> dia;
        cin.ignore();

        diaValido = fecha.setDia(dia);
        if (!diaValido)
        {
            mensajeError("Dia invalido");
        }
    } while (!diaValido);
}

void ManagerPagos::pedirAnio(Fecha &fecha)
{
    int anio;
    bool anioValido;

    do
    {
        limpiarError();
        limpiarLinea(6);
        mensajeFormulario(6, "Anio: ");
        cin >> anio;
        cin.ignore();

        anioValido = fecha.setAnio(anio);
        if (!anioValido)
        {
            mensajeError("Anio invalido");
        }

    } while (!anioValido);
}

int ManagerPagos::pedirIdSocio()
{
    int idSocio;
    int posicion;
    do
    {
        limpiarError();
        limpiarLinea(1);
        mensajeFormulario(1, "Ingrese ID del Socio:");
        cin >> idSocio;
        cin.ignore();

        posicion = _archivoSocios.buscar(idSocio);
        if (posicion == -1)
        {
            mensajeError("Socio no encontrado");
            system("pause>nul");
        }
    } while (posicion == -1);

    return idSocio;
}

int ManagerPagos::pedirIdActividad()
{
    int idActividad;
    int posicion;
    do
    {
        limpiarError();
        limpiarLinea(2);
        mensajeFormulario(2, "Ingrese ID de Actividad:");
        cin >> idActividad;
        cin.ignore();

        posicion = _archivoActividades.buscar(idActividad);
        if (posicion == -1)
        {
            mensajeError("Actividad no encontrada");
            system("pause>nul");
        }
    } while (posicion == -1);
    return idActividad;
}


// cambiado por confirmar importe BORRAR?
int ManagerPagos::pedirImporte()
{
    float importe;
    do
    {
        limpiarError();
        limpiarLinea(3);
        mensajeFormulario(3, "Ingrese Importe: ");
        cin >> importe;
        cin.ignore();

        if (importe < 0)
            mensajeError("El importe no puede ser negativo.");
    } while (importe < 0);
    return importe;
}

void ManagerPagos::pedirMetodoDePago(Pago &pago)
{
    int metodoDePago;
    bool metodoValido;
    do
    {
        limpiarError();
        limpiarLinea(4);
        mensajeFormulario(4, "Metodo de Pago (1: Efectivo, 2: Tarjeta, 3: Transferencia): ");
        cin >> metodoDePago;
        cin.ignore();

        metodoValido = pago.setMetodoDePago(metodoDePago);
        if (!metodoValido)
        {
            mensajeError("Metodo de pago invalido. Debe ser 1, 2 o 3.");
        }

    } while (!metodoValido);
}



void ManagerPagos::exportarCSV()
{

    system("cls");
    imprimirFormulario("Pagos CSV");
    mensajeFormulario(3, "Se exportaran los datos de los pagos en un archivo .csv");
    mensajeFormulario(4, "en la carpeta donde se encuentra el programa");

    int codigo = _archivoPagos.exportarCSV();

    if (codigo == -1)
    {
        mensajeError("Error al exportar en csv.");
        system("pause>nul");
        return;
    }

    if (codigo == -2)
    {
        mensajeError("No hay registros para poder exportar en csv");
        system("pause>nul");
        return;
    }

    mensajeExito("Pagos exportados correctamente");
    system("pause>nul");
}
