#include <iostream>
#include <string>
#include <iomanip>
#include "ManagerSocios.h"
#include "../funcionesConsola.h"
#include "../rlutil.h"
using namespace std;

ManagerSocios::ManagerSocios()
: _archivoSocios("Socios.dat"){ }

void ManagerSocios::agregar(){
    ///Estetico
    imprimirFormulario("Agregar Socio");
    rlutil::setColor(rlutil::BLACK);
    rlutil::setBackgroundColor(rlutil::WHITE);
    ///---------

    Socio socio;

    int id = _archivoSocios.getNuevoId();
    mensajeFormulario(1, "ID: " + to_string(id));
    socio.setIdSocio(id);

    string dni;
    do{
        limpiarError();
        limpiarLinea(2);
        mensajeFormulario(2, "DNI: ");
        getline(cin, dni);

        if (!socio.setDni(dni)) {
            mensajeError("DNI invalido");
        }

    }while(!socio.setDni(dni));

    string nombre;
    do{
        limpiarError();
        limpiarLinea(3);
        mensajeFormulario(3, "Nombre: ");
        getline(cin, nombre);

        if (!socio.setNombre(nombre)) {
            mensajeError("Nombre invalido");
        }

    }while(!socio.setNombre(nombre));

    string apellido;
    do{
        limpiarError();
        limpiarLinea(4);
        mensajeFormulario(4, "Apellido: ");
        getline(cin, apellido);

        if (!socio.setApellido(apellido)) {
            mensajeError("Apellido invalido");
        }

    }while(!socio.setApellido(apellido));

    string email;
    do{
        limpiarError();
        limpiarLinea(5);
        mensajeFormulario(5, "Email: ");
        getline(cin, email);

        if (!socio.setEmail(email)) {
            mensajeError("Nombre invalido");
        }

    }while(!socio.setEmail(email));

    mensajeFormulario(6, "Fecha Nacimiento:");
    Fecha fecha;

    int anio;
    do{
        limpiarError();
        limpiarLinea(7);
        mensajeFormulario(7, "Anio: ");
        cin >> anio;

        if (!fecha.setAnio(anio)) {
            mensajeError("Anio invalido");
        }

    }while(!fecha.setAnio(anio));

    int mes;
    do{
        limpiarError();
        limpiarLinea(8);
        mensajeFormulario(8, "Mes: ");
        cin >> mes;

        if (!fecha.setMes(mes)) {
            mensajeError("Mes invalido");
        }

    }while(!fecha.setMes(mes));

    int dia;
    do{
        limpiarError();
        limpiarLinea(9);
        mensajeFormulario(9, "Dia: ");
        cin >> dia;

        if (!fecha.setDia(dia)) {
            mensajeError("Dia invalido");
        }

    }while(!fecha.setDia(dia));
    socio.setFechaNacimiento(fecha);


    _archivoSocios.guardar(socio);

    rlutil::resetColor();
    rlutil::setBackgroundColor(rlutil::BLACK);
}

void ManagerSocios::borrar() {
    system("cls");
    imprimirFormulario("Borrar socio");

    int idSocio;
    mensajeFormulario(1, "Ingresa el numero de socio a eliminar: ");
    cin >> idSocio;
    cin.ignore(); // Para limpiar el salto de línea pendiente

    int posicion = _archivoSocios.buscar(idSocio);
    if (posicion == -1){
        mensajeError("El socio ingresado no existe");
    }

    mensajeFormulario(3, "Datos del socio seleccionado:");
    cout << endl;

    Socio socio = _archivoSocios.leer(posicion);
    mostrarEncabezadoTabla();
    mostrarSocio(socio);

    string respuesta;
    bool eliminar = false;

    do {

        limpiarError();
        limpiarLinea(7);
        mensajeFormulario(7, "Quieres eliminar el socio? (s/n): ");
        getline(cin, respuesta);

        if (respuesta == "s" || respuesta == "S") {
            eliminar = true;
            break;
        }

        else if (respuesta == "n" || respuesta == "N") {
            eliminar = false;
            break;
        }

        else {
            mensajeError("Respuesta inválida. Ingrese 's' o 'n'.");
        }

    } while (true);

    if (eliminar) {
        socio.setEliminado(true);
        _archivoSocios.modificar(socio, posicion);
        mensajeFormulario(9, "Socio eliminado correctamente.");
    } else {
        mensajeFormulario(9, "Operacion cancelada.");
    }

    rlutil::setBackgroundColor(rlutil::BLACK);
    system("pause>nul");
}

void ManagerSocios::modificar(){

}

void ManagerSocios::listar(){
    system("cls");
    int cantidadRegistros = _archivoSocios.getCantidadRegistros();
    if (cantidadRegistros <= 0) {
        cout << "No hay socios registrados." << endl;
        system("pause>nul");
        return;
    }

    Socio* socios = new Socio[cantidadRegistros];
    _archivoSocios.leerTodos(cantidadRegistros, socios);

    ///Encabezado con los nombres de los atributos
    mostrarEncabezadoTabla();

    /// Listado
    for (int i = 0; i < cantidadRegistros; i++) {
        if (i % 2 == 0) {
            rlutil::setBackgroundColor(rlutil::GREY);
        } else {
            rlutil::setBackgroundColor(rlutil::WHITE);
        }
        mostrarSocio(socios[i]);
        cout << endl;
    }

    system("pause>nul");
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::resetColor();
    delete[] socios;

}

void ManagerSocios::mostrarSocio(Socio socio) {
    cout << (char)179 << left << setw(6) << socio.getIdSocio() << (char)179;
    cout << left << setw(12) << socio.getDni() << (char)179;
    cout << left << setw(19) << truncar(socio.getNombre(), 19) << (char)179;
    cout << left << setw(19) << truncar(socio.getApellido(), 19) << (char)179;
    cout << left << setw(34) << truncar(socio.getEmail(), 34) << (char)179;
    cout << left << setw(12) << socio.getFechaNacimiento().toString() << (char)179;
    cout << left << setw(10) << (socio.getEliminado() ? "Si" : "No") << (char)179;
}

void ManagerSocios::mostrarEncabezadoTabla() {
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(6) << "ID" << (char)179;
    cout << left << setw(12) << "DNI" << (char)179;
    cout << left << setw(19) << "Nombre" << (char)179;
    cout << left << setw(19) << "Apellido" << (char)179;
    cout << left << setw(34) << "Email" << (char)179;
    cout << left << setw(12) << "Nacimiento" << (char)179;
    cout << left << setw(10) << "Eliminado" << (char)179;
    cout << endl;
}

