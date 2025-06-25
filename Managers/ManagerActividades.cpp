#include <iostream>
#include "ManagerActividades.h"
#include "../funcionesConsola.h"
#include "../rlutil.h"
#include <iomanip>

using namespace std;

ManagerActividades::ManagerActividades()
    : _archivoActividades("Actividades.dat")
{
}

void ManagerActividades::agregar()
{
    /// Estetico
    imprimirFormulario("Agregar Actividad");
    rlutil::setColor(rlutil::BLACK);
    rlutil::setBackgroundColor(rlutil::WHITE);
    ///---------

    Actividad actividad;
    Fecha fecha;

    int id = _archivoActividades.getNuevoId();
    mensajeFormulario(1, "ID: " + to_string(id));
    actividad.setIdActividad(id);

    pedirNombre(actividad);
    pedirResponsable(actividad);
    pedirArancel(actividad);

    mensajeFormulario(5, "Fecha de inicio:");
    pedirAnio(fecha);
    pedirMes(fecha);
    pedirDia(fecha);

    actividad.setFechaInicio(fecha);

    Fecha fechaActual(true);
    if (actividad.getFechaInicio() < fechaActual)
    {
        mensajeError("La fecha de inicio no puede ser anterior a la fecha actual.");
        system("pause>nul");
        return;
    }

    bool ok = _archivoActividades.guardar(actividad);
    if (!ok)
    {
        mensajeError("Error al guardar la actividad.");
        system("pause>nul");
        return;
    }
    mensajeExito("Actividad agregada correctamente.");
    system("pause>nul");

}

void ManagerActividades::modificar()
{
    system("cls");
    imprimirFormulario("Modificar Actividad");

    int idActividad;
    mensajeFormulario(1, "Ingresa el numero de actividad a modificar: ");
    cin >> idActividad;
    cin.ignore(); /// Para limpiar el salto de linea pendiente

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
        mensajeFormulario(3, "La actividad ingresada se encuentra eliminada.");
        system("pause>nul");
        return;
    }

    mensajeFormulario(3, "Datos de la actividad seleccionada: ");
    cout << endl;

    mostrarEncabezadoTabla();
    mostrarActividad(actividad);

    string respuesta;
    bool modificar = false;

    do
    {

        limpiarError();
        limpiarLinea(7);
        mensajeFormulario(7, "Quieres modificar la actividad? (s/n): ");
        getline(cin, respuesta);

        if (respuesta == "s" || respuesta == "S")
        {
            modificar = true;
            break;
        }

        else if (respuesta == "n" || respuesta == "N")
        {
            modificar = false;
            break;
        }

        else
        {
            mensajeError("Respuesta invalida. Ingrese 's' o 'n'.");
        }

    } while (true);

    if (!modificar)
    {
        mensajeFormulario(9, "Operacion cancelada.");
        system("pause>nul");
        return;
    }

    /// Similar a agregar

    imprimirFormulario("Modificar Actividad");
    int id = actividad.getIdActividad();
    mensajeFormulario(1, "ID: " + to_string(id));

    pedirNombre(actividad);
    pedirResponsable(actividad);
    pedirArancel(actividad);
    Fecha nuevaFecha;

    mensajeFormulario(5, "Fecha de inicio:");
    pedirAnio(nuevaFecha);
    pedirMes(nuevaFecha);
    pedirDia(nuevaFecha);
    actividad.setFechaInicio(nuevaFecha);

    bool ok = _archivoActividades.modificar(actividad, posicion);
    if (!ok)
    {
        mensajeError("Error al modificar la actividad.");
        system("pause>nul");
        return;
    }

    mensajeExito("Actividad modificada correctamente");
    system("pause>nul");
}

void ManagerActividades::borrar()
{
    system("cls");
    imprimirFormulario("Borrar actividad");

    int idActividad;
    mensajeFormulario(1, "Ingresa el numero de actividad a eliminar: ");
    cin >> idActividad;
    cin.ignore(); /// Para limpiar el salto de linea pendiente

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
        mensajeFormulario(3, "La actividad ingresada ya se encuentra eliminada.");
        system("pause>nul");
        return;
    }

    mensajeFormulario(3, "Datos de la actividad seleccionada:");
    cout << endl;

    mostrarEncabezadoTabla();
    mostrarActividad(actividad);

    string respuesta;
    bool eliminar = false;

    do
    {

        limpiarError();
        limpiarLinea(7);
        mensajeFormulario(7, "Quieres eliminar la actividad? (s/n): ");
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
        actividad.setEliminado(true);
        _archivoActividades.modificar(actividad, posicion);
        mensajeExito("Actividad eliminada correctamente.");
    }
    else
    {
        mensajeFormulario(9, "Operacion cancelada.");
    }

    system("pause>nul");
}

void ManagerActividades::listar()
{
    system("cls");
    int cantidadRegistros = _archivoActividades.getCantidadRegistros();
    if (cantidadRegistros <= 0)
    {
        mensajeError("No hay actividades registradas.");
        system("pause>nul");
        return;
    }

    Actividad *actividades = new Actividad[cantidadRegistros];
    _archivoActividades.leerTodos(cantidadRegistros, actividades);

    mostrarEncabezadoTabla();

    for (int i = 0; i < cantidadRegistros; i++)
    {
        if (!actividades[i].getEliminado())
        {
            if (i % 2 == 0)
            {
                rlutil::setBackgroundColor(rlutil::GREY);
            }
            else
            {
                rlutil::setBackgroundColor(rlutil::WHITE);
            }
            mostrarActividad(actividades[i]);
        }
    }

    delete[] actividades;
    system("pause>nul");
}

void ManagerActividades::buscarPorId(){

    imprimirFormulario("Buscar Actividad por Id");
    int idActividad;
    mensajeFormulario(3, "Ingrese el id de actividad a buscar: ");
    cin >> idActividad;
cin.ignore();
    int posicion = _archivoActividades.buscar(idActividad);

    if (posicion == -1){
        mensajeError("La actividad ingresada no existe");
        system("pause>nul");
        return;
    }

    Actividad actividad;
    actividad = _archivoActividades.leer(posicion);

    if (actividad.getEliminado()){
        mensajeFormulario(5, "La actividad ingresada se encuentra eliminada.");
        system("pause");
        return;
    }

    ///Lo vuelvo a imprimir para borrar el texto anterior
    ///y asi tener espacio para mostrar el socio entero.
    imprimirFormulario("Buscar Socio por Id");

    mensajeFormulario(3,"ID: " + to_string(actividad.getIdActividad()));
    mensajeFormulario(4,"Nombre: " + actividad.getNombre());
    mensajeFormulario(5,"Responsable: " + actividad.getResponsable());
    mensajeFormulario(6,"Arancel: " + to_string(actividad.getArancel()));
    mensajeFormulario(7,"Fecha Inicio: " + actividad.getFechaInicio().toString());

    mensajeExito("Operacion Exitosa");
    system("pause>nul");

}

void ManagerActividades::exportarCSV()
{
    system("cls");
    imprimirFormulario("Actividades CSV");
    mensajeFormulario(3, "Se exportaran los datos de las actividades en un archivo .csv");
    mensajeFormulario(4, "en la carpeta donde se encuentra el programa");

    int codigo = _archivoActividades.exportarCSV();

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

    mensajeExito("Actividades exportadas correctamente a CSV.");
    system("pause>nul");
}

void ManagerActividades::backup()
{
    system("cls");
    imprimirFormulario("Copia de seguridad de Actividades");

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
            mensajeError("Respuesta invalida. Ingrese 'c' o 'a'.");
        }
    }

    if (crearBackup)
    {
        resultado = _archivoActividades.crearBackup();
        if (resultado)
        {
            mensajeExito("Copia de seguridad creada correctamente.");
        }
        else
        {
            mensajeError("Error al crear la copia de seguridad.");
        }
    }
    else
    {
        resultado = _archivoActividades.usarBackup();
        if (resultado)
        {
            mensajeExito("Copia de seguridad aplicada correctamente.");
        }
        else
        {
            mensajeError("Error al aplicar la copia de seguridad.");
        }
    }

    system("pause>nul");
}

void ManagerActividades::darDeAlta()
{
    system("cls");
    limpiarError();

    imprimirFormulario("Dar de alta a la actividad");

    int idActividad;
    mensajeFormulario(1, "Ingresa el numero de actividad a dar de alta: ");
    cin >> idActividad;
    cin.ignore(); /// Para limpiar el salto de linea pendiente

    int posicion = _archivoActividades.buscar(idActividad);
    if (posicion == -1)
    {
        mensajeError("La actividad ingresada no existe");
        system("pause>nul");
        return;
    }

    Actividad actividad = _archivoActividades.leer(posicion);
    if (!actividad.getEliminado())
    {
        mensajeFormulario(3, "La actividad ingresada no se encuentra eliminada.");
        system("pause>nul");
        return;
    }

    mensajeFormulario(3, "Datos de la actividad seleccionada: ");
    cout << endl;

    mostrarEncabezadoTabla();
    mostrarActividad(actividad);

    string respuesta;
    bool darAlta = false;

    do
    {

        limpiarError();
        limpiarLinea(7);
        mensajeFormulario(7, "Quieres dar de alta a la actividad? (s/n): ");
        getline(cin, respuesta);

        if (respuesta == "s" || respuesta == "S")
        {
            darAlta = true;
            break;
        }

        else if (respuesta == "n" || respuesta == "N")
        {
            darAlta = false;
            break;
        }

        else
        {
            mensajeError("Respuesta invalida. Ingrese 's' o 'n'.");
        }

    } while (true);

    if (!darAlta)
    {
        mensajeFormulario(9, "Operacion cancelada.");
        system("pause>nul");
        return;
    }

    /// Similar a agregar

    imprimirFormulario("Dar de alta a la actividad");
    int id = actividad.getIdActividad();

    mostrarActividad(actividad  );
    actividad.setEliminado(false);


    bool ok = _archivoActividades.modificar(actividad, posicion);
    if (!ok)
    {
        mensajeError("Error al dar de alta a la actividad.");
        system("pause>nul");
        return;
    }

    mensajeExito("Actividad dada de alta correctamente");
    system("pause>nul");
}

void ManagerActividades::mostrarActividad(Actividad &actividad)
{
    cout << (char)179 << left << setw(5) << actividad.getIdActividad() << (char)179;
    cout << left << setw(35) << truncar(actividad.getNombre(), 35) << (char)179;
    cout << left << setw(35) << truncar(actividad.getResponsable(), 35) << (char)179;
    cout << left << setw(12) << actividad.getFechaInicio().toString() << (char)179;
    cout << left << setw(20) << actividad.getArancel() << (char)179 << endl;
}

void ManagerActividades::mostrarEncabezadoTabla()
{
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(5) << "ID" << (char)179;
    cout << left << setw(35) << "Nombre" << (char)179;
    cout << left << setw(35) << "Responsable" << (char)179;
    cout << left << setw(12) << "Fecha Inicio" << (char)179;
    cout << left << setw(20) << "Arancel" << (char)179 << endl;
    rlutil::setBackgroundColor(rlutil::WHITE);
}

void ManagerActividades::pedirMes(Fecha &fecha)
{
    int mes;
    bool ok;
    do
    {
        limpiarError();
        limpiarLinea(7);
        mensajeFormulario(7, "Mes: ");
        cin >> mes;
        cin.ignore();
        ok = fecha.setMes(mes);
        if (!ok)
        {
            mensajeError("Mes invalido.");
        }
    } while (!ok);
}

void ManagerActividades::pedirDia(Fecha &fecha)
{
    int dia;
    bool ok;
    do
    {
        limpiarError();
        limpiarLinea(8);
        mensajeFormulario(8, "Dia: ");
        cin >> dia;
        cin.ignore();
        ok = fecha.setDia(dia);
        if (!ok)
        {
            mensajeError("Dia invalido.");
        }
    } while (!ok);
}

void ManagerActividades::pedirAnio(Fecha &fecha)
{
    int anio;
    bool ok;
    do
    {
        limpiarError();
        limpiarLinea(6);
        mensajeFormulario(6, "Anio: ");
        cin >> anio;
        cin.ignore();
        ok = fecha.setAnio(anio);
        if (!ok)
        {
            mensajeError("Anio invalido. Ingrese un anio entre 1900 y 2100.");
        }
    } while (!ok);
}

int ManagerActividades::pedirIdActividad()
{
    int idActividad;
    bool ok;
    do
    {
        limpiarError();
        limpiarLinea(11);
        mensajeFormulario(11, "ID de la actividad: ");
        cin >> idActividad;
        cin.ignore();
        ok = idActividad > 0;
        if (!ok)
        {
            mensajeError("ID invalido. Ingrese un ID mayor a 0.");
        }
    } while (!ok);

    return idActividad;
}

void ManagerActividades::pedirNombre(Actividad &actividad)
{
    string nombre;
    bool ok;
    do
    {
        limpiarError();
        limpiarLinea(2);
        mensajeFormulario(2, "Nombre de la actividad: ");
        getline(cin, nombre);
        ok = actividad.setNombre(nombre);
        if (!ok)
        {
            mensajeError("Nombre invalido. Ingrese un nombre válido.");
        }
    } while (!ok);
}

void ManagerActividades::pedirResponsable(Actividad &actividad)
{
    string responsable;
    bool ok;
    do
    {
        limpiarError();
        limpiarLinea(3);
        mensajeFormulario(3, "Responsable: ");
        getline(cin, responsable);
        ok = actividad.setResponsable(responsable);
        if (!ok)
        {
            mensajeError("Responsable invalido. Ingrese un responsable válido.");
        }
    } while (!ok);
}

void ManagerActividades::pedirArancel(Actividad &actividad)
{
    float arancel;
    bool ok;
    do
    {
        limpiarError();
        limpiarLinea(4);
        mensajeFormulario(4, "Arancel: ");
        cin >> arancel;
        cin.ignore();

        ok = actividad.setArancel(arancel);
        if (!ok)
        {
            mensajeError("Arancel invalido. Ingrese un arancel mayor a 0.");
        }
    } while (!ok);
}
