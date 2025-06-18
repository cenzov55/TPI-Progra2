#include <iostream>
#include "ManagerInscripciones.h"
#include "../funcionesConsola.h"
#include "../rlutil.h"
#include <iomanip>

using namespace std;

ManagerInscripciones::ManagerInscripciones()
    : _archivoInscripciones("Inscripciones.dat"),
      _archivoSocios("Socios.dat"),
      _archivoActividades("Actividades.dat")
{
}

void ManagerInscripciones::agregar()
{
    /// Estetico
    imprimirFormulario("Inscribir Socio a Actividad");
    rlutil::setColor(rlutil::BLACK);
    rlutil::setBackgroundColor(rlutil::WHITE);
    ///---------
    Fecha fechaInscripcion;

    int cantidadActividades = _archivoActividades.getCantidadRegistros();
    if (cantidadActividades <= 0)
    {
        mensajeError("No hay actividades registradas.");
        system("pause>nul");
        return;
    }

    int cantidadSocios = _archivoSocios.getCantidadRegistros();
    if (cantidadSocios <= 0)
    {
        mensajeError("No hay socios registrados.");
        system("pause>nul");
        return;
    }

    int idSocio = pedirIdSocio();
    int posicionSocio = _archivoSocios.buscar(idSocio);
    if (posicionSocio == -1) {
        mensajeError("El socio ingresado no existe.");
        system("pause>nul");
        return;
    }

    Socio socio = _archivoSocios.leer(posicionSocio);
    if (socio.getEliminado())
    {
        mensajeError("El socio ingresado se encuentra eliminado.");
        system("pause>nul");
        return;
    }

    int idActividad = pedirIdActividad();
    int posicionActividad = _archivoActividades.buscar(idActividad);
    Actividad actividad = _archivoActividades.leer(posicionActividad);
    if (actividad.getEliminado())
    {
        mensajeError("La actividad ingresada se encuentra eliminada.");
        system("pause>nul");
        return;
    }
    //PARA QUE NO SE INSCRIBA DOS VECES AL MISMO SOCIO EN LA MISMA ACTIVIDAD
    bool inscripcionExistente = _archivoInscripciones.buscar(actividad.getIdActividad(), socio.getIdSocio()) != -1;
    if (inscripcionExistente)
    {
        mensajeError("El socio ya se encuentra inscripto en la actividad.");
        system("pause>nul");
        return;
    }

    mensajeFormulario(3, "Fecha Inscripcion:");
    pedirAnio(fechaInscripcion);
    pedirMes(fechaInscripcion);
    pedirDia(fechaInscripcion);

    bool ok = _archivoInscripciones.guardar(Inscripcion(socio.getIdSocio(), actividad.getIdActividad(), fechaInscripcion));
    if (!ok)
    {
        mensajeError("Error al inscribir socio.");
        system("pause>nul");
        return;
    }
    mensajeExito("Socio inscripto correctamente.");
    system("pause>nul");
}

void ManagerInscripciones::borrar()
{
    system("cls");
    imprimirFormulario("Borrar inscripcion");

    int posicionSocio = pedirIdSocio();
    if (posicionSocio == -1)
    {
        mensajeError("El socio ingresado no existe");
        system("pause>nul");
        return;
    }
    Socio socio = _archivoSocios.leer(posicionSocio);

    if (socio.getEliminado())
    {
        mensajeError("El socio ingresado se encuentra eliminado.");
        system("pause>nul");
        return;
    }

    int idActividad = pedirIdActividad();
    int posicionActividad = _archivoActividades.buscar(idActividad);
    if (posicionActividad == -1) {
        mensajeError("La actividad ingresada no existe.");
        system("pause>nul");
        return;
    }

    Actividad actividad = _archivoActividades.leer(posicionActividad);
    if (actividad.getEliminado())
    {
        mensajeError("La actividad ingresada se encuentra eliminada.");
        system("pause>nul");
        return;
    }
    int posicionInscripcion = _archivoInscripciones.buscar(actividad.getIdActividad(), socio.getIdSocio());
    if (posicionInscripcion == -1)
    {
        mensajeError("Inscripcion no encontrada.");
        system("pause>nul");
        return;
    }

    Inscripcion inscripcion = _archivoInscripciones.leer(posicionInscripcion);
    if (inscripcion.getEliminado())
    {
        mensajeFormulario(3, "La inscripcion ya se encuentra eliminada.");
        system("pause>nul");
        return;
    }

    string respuesta;
    bool eliminar = false;

    do
    {
        limpiarError();
        limpiarLinea(7);
        mensajeFormulario(7, "Quieres eliminar esta inscripcion? (s/n): ");
        getline(cin, respuesta);

        if (respuesta == "s" || respuesta == "S")
        {
            eliminar = true;
            break;
        }

        else if (respuesta == "n" || respuesta == "N")
        {
            eliminar = false;
            break;
        }

        else
        {
            mensajeError("Respuesta invalida. Ingrese 's' o 'n'.");
        }

    } while (true);

    if (eliminar)
    {
        inscripcion.setEliminado(true);
        _archivoInscripciones.modificar(inscripcion, posicionInscripcion);
        mensajeExito("Inscripcion eliminada correctamente.");
    }
    else
    {
        mensajeFormulario(9, "Operacion cancelada.");
    }

    system("pause>nul");
}

void ManagerInscripciones::listar()
{
    system("cls");
    int cantidadRegistros = _archivoInscripciones.getCantidadRegistros();
    if (cantidadRegistros <= 0)
    {
        mensajeError("No hay inscripciones registradas.");
        system("pause>nul");
        return;
    }

    Inscripcion *inscripciones = new Inscripcion[cantidadRegistros];
    _archivoInscripciones.leerTodos(cantidadRegistros, inscripciones);

    mostrarEncabezadoTabla();

    for (int i = 0; i < cantidadRegistros; i++)
    {
        if (!inscripciones[i].getEliminado())
        {
            if (i % 2 == 0)
            {
                rlutil::setBackgroundColor(rlutil::GREY);
            }
            else
            {
                rlutil::setBackgroundColor(rlutil::WHITE);
            }
            mostrarInscripcion(inscripciones[i]);
            cout << endl;
        }
    }

    delete[] inscripciones;
    system("pause>nul");
}

void ManagerInscripciones::backup() {
    system("cls");
    imprimirFormulario("Copia de seguridad de Inscripciones");

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
        resultado = _archivoInscripciones.crearBackup();
        if (resultado) {
            mensajeExito("Copia creada correctamente.");
        } else {
            mensajeError("Error al crear la copia.");
        }
    }
    else {
        resultado = _archivoInscripciones.usarBackup();
        if (resultado) {
            mensajeExito("Copia aplicada correctamente.");
        } else {
            mensajeError("Error al aplicar la copia.");
        }
    }
    system("pause>nul");
}

void ManagerInscripciones::mostrarInscripcion(Inscripcion &inscripcion)
{
    cout << (char)179 << left << setw(12) << inscripcion.getIdSocio() << (char)179;
    cout << left << setw(12) << inscripcion.getIdActividad() << (char)179;
    cout << left << setw(24) << inscripcion.getFechaInscripcion().toString() << (char)179;
}

void ManagerInscripciones::mostrarEncabezadoTabla()
{
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(12) << "ID SOCIO" << (char)179;
    cout << left << setw(12) << "ID ACTIVIDAD" << (char)179;
    cout << left << setw(24) << "FECHA INSCRIPCION" << (char)179;
    cout << endl;
}

void ManagerInscripciones::pedirMes(Fecha &fecha)
{
    int mes;
    bool mesValido;

    do
    {
        limpiarError();
        limpiarLinea(5);
        mensajeFormulario(5, "Mes: ");
        cin >> mes;

        mesValido = fecha.setMes(mes);
        if (!mesValido)
        {
            mensajeError("Mes invalido");
        }

    } while (!mesValido);
}

void ManagerInscripciones::pedirDia(Fecha &fecha)
{
    int dia;
    bool diaValido;

    do
    {
        limpiarError();
        limpiarLinea(6);
        mensajeFormulario(6, "Dia: ");
        cin >> dia;

        diaValido = fecha.setDia(dia);
        if (!diaValido)
        {
            mensajeError("Dia invalido");
        }
    } while (!diaValido);
}

void ManagerInscripciones::pedirAnio(Fecha &fecha)
{
    int anio;
    bool anioValido;

    do
    {
        limpiarError();
        limpiarLinea(4);
        mensajeFormulario(4, "Anio: ");
        cin >> anio;

        anioValido = fecha.setAnio(anio);
        if (!anioValido)
        {
            mensajeError("Anio invalido");
        }

    } while (!anioValido);
}

int ManagerInscripciones::pedirIdSocio()
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
        if (posicion == -1)
        {
            mensajeError("Socio no encontrado");
            system("pause>nul");
        }
    } while (posicion == -1);

    return idSocio;
}

int ManagerInscripciones::pedirIdActividad()
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
        {
            mensajeError("Actividad no encontrada");
            system("pause>nul");
        }
    } while (posicion == -1);
    return idActividad;
}

void ManagerInscripciones::exportarCSV()
{

    system("cls");
    imprimirFormulario("Inscripciones CSV");
    mensajeFormulario(3, "Se exportaran los datos de las inscripciones en un archivo .csv");
    mensajeFormulario(4, "en la carpeta donde se encuentra el programa");

    int codigo = _archivoInscripciones.exportarCSV();

    if (codigo == -1)
    {
        mensajeError("Error al exportar en csv.");
        system("pause>nul");
        return;
    }

    if (codigo == -2)
    {
        mensajeError("No hay registros para exportar en csv.");
        system("pause>nul");
        return;
    }

    mensajeExito("Inscripciones exportadas correctamente");
    system("pause>nul");
}

