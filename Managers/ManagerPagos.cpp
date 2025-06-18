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
{}

void ManagerPagos::agregar()
{
    /// Estetico
    imprimirFormulario("Registrar nuevo Pago");
    rlutil::setColor(rlutil::BLACK);
    rlutil::setBackgroundColor(rlutil::WHITE);
    ///---------

    Pago pago;
    Fecha fecha;

    int idSocio = pedirIdSocio();
    // Guardo posiciones por si quiero mostrar sus datos despues
    int posicionSocio = _archivoSocios.buscar(idSocio);

    Socio socio = _archivoSocios.leer(posicionSocio);

    if (socio.getEliminado())
    {
        mensajeError("El socio ingresado se encuentra eliminado.");
        system("pause>nul");
        return;
    }
    int posicionActividad = pedirIdActividad();
    Actividad actividad = _archivoActividades.leer(posicionActividad);
    /*descomentar al implementar el ABM de actividades
        if (actividad.getEliminado())
    {
        mensajeError("La actividad ingresada se encuentra eliminada.");
        system("pause>nul");
        return;
    }
*/
    int importe = pedirImporte();

    pago.setFechaDePago(fecha);
    pago.setIdSocio(socio.getIdSocio());
    pago.setIdActividad(actividad.getIdActividad());
    pago.setImporte(importe);
    pedirMetodoDePago(pago);

    mensajeFormulario(5, "Fecha del pago:");
    pedirAnio(fecha);
    pedirMes(fecha);
    pedirDia(fecha);
    pago.setFechaDePago(fecha);

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

    string datosSocio = "Pagos del socio: " + socio.getNombre() + " " + socio.getApellido() + " (ID: " + to_string(socio.getIdSocio()) + ")";

    rlutil::setBackgroundColor(rlutil::BLACK);
    system("cls");

    cout << datosSocio << endl;
    cout << "----------------------------------------" << endl;
    mostrarEncabezadoTabla();

    int contador = 0;

    for (int i = 0; i < cantidadRegistros; i++)
    {
        // Si el pago no es del socio, lo salteamos
        if( pagos[i].getIdSocio() != socio.getIdSocio()) continue;
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
    if(contador == 0) mensajeError("No se encontraron pagos para el socio ingresado.");

    system("pause>nul");
    delete[] pagos;

}

void ManagerPagos::backup() {
    system("cls");
    imprimirFormulario("Copia de seguridad de Pagos");

    string respuesta;
    bool crearBackup;
    bool resultado;

    while (true) {
        limpiarError();
        limpiarLinea(7);

        mensajeFormulario(3, "Deseas crear (c) o aplicar (a) una copia de seguridad? (c/a): ");
        getline(cin, respuesta);

        if (respuesta == "c" || respuesta == "C") {
            crearBackup = true;
            break;
        }
        else if (respuesta == "a" || respuesta == "A") {
            crearBackup = false;
            break;
        }
        else {
            mensajeError("Respuesta invalida. Ingresa 'c' para crear o 'a' para aplicar una copia de seguridad.");
        }
    }

    if (crearBackup) {
        resultado = _archivoPagos.crearBackup();
        if (resultado) {
            mensajeExito("Copia creada correctamente.");
        } else {
            mensajeError("Error al crear la copia.");
        }
    }
    else {
        resultado = _archivoPagos.usarBackup();
        if (resultado) {
            mensajeExito("Copia aplicada correctamente.");
        } else {
            mensajeError("Error al aplicar la copia.");
        }
    }
    system("pause>nul");
}


void ManagerPagos::mostrarPago(Pago &pago)
{
    cout << (char)179 << left << setw(12) << pago.getIdSocio() << (char)179;
    cout << left << setw(12) << pago.getIdActividad() << (char)179;
    cout << left << setw(12) << pago.getFechaDePago().toString() << (char)179;
    cout << left << setw(12) << pago.getMetodoDePago() << (char)179;
    cout << left << setw(12) << pago.getImporte() << (char)179;
}

void ManagerPagos::mostrarEncabezadoTabla()
{
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(12) << "ID SOCIO" << (char)179;
    cout << left << setw(12) << "ID ACTIVIDAD" << (char)179;
    cout << left << setw(12) << "FECHA PAGO" << (char)179;
    cout << left << setw(12) << "METODO PAGO" << (char)179;
    cout << left << setw(12) << "IMPORTE" << (char)179;
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
        posicion = _archivoSocios.buscar(idSocio);
        if (posicion == -1){
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
        posicion = _archivoActividades.buscar(idActividad);
        if (posicion == -1)
            mensajeError("Actividad no encontrada");
            system("pause>nul");
    } while (posicion == -1);
    return posicion;
}

int ManagerPagos::pedirImporte()
{
    float importe;
    do
    {
        limpiarError();
        limpiarLinea(3);
        mensajeFormulario(3, "Ingrese Importe: ");
        cin >> importe;
        if (importe < 0)
            mensajeError("El importe no valido.");
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

        metodoValido = pago.setMetodoDePago(metodoDePago);
        if (!metodoValido)
        {
            mensajeError("Metodo de pago invalido. Debe ser 1, 2 o 3.");
        }

    } while (!metodoValido);
}

void ManagerPagos::exportarCSV(){

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
