#include <iostream>
#include <string>
#include <iomanip>
#include "ManagerSocios.h"
#include "../funcionesConsola.h"
#include "../rlutil.h"
using namespace std;

///Revisar archivo funcionesConsola para entender mejor ciertas cosas esteticas.

ManagerSocios::ManagerSocios()
: _archivoSocios("Socios.dat"){ }


///A la hora de agregar, se hace un do while
///que revisa con el set si lo que ingreso pasa las
///validaciones del set.
///Si no lo hace, borra y se repite el ingreso de datos.
///Para eso tuve que cambiar los sets y en vez de void
///devuelven un bool, dependiendo si salio bien o no.
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
    mensajeExito("Socio ingresado correctamente");
    system("pause>nul");
}

void ManagerSocios::borrar() {
    system("cls");
    imprimirFormulario("Borrar socio");

    int idSocio;
    mensajeFormulario(1, "Ingresa el numero de socio a eliminar: ");
    cin >> idSocio;
    cin.ignore(); /// Para limpiar el salto de línea pendiente

    int posicion = _archivoSocios.buscar(idSocio);
    if (posicion == -1){
        mensajeError("El socio ingresado no existe");
        system("pause>nul");
        return;
    }

    Socio socio = _archivoSocios.leer(posicion);
    if (socio.getEliminado()){
        mensajeFormulario(3, "El socio ingresado ya se encuentra eliminado.");
        system("pause>nul");
        return;
    }


    mensajeFormulario(3, "Datos del socio seleccionado:");
    cout << endl;

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
            mensajeError("Respuesta invalida. Ingrese 's' o 'n'.");
        }

    } while (true);

    if (eliminar) {
        socio.setEliminado(true);
        _archivoSocios.modificar(socio, posicion);
        mensajeExito("Socio eliminado correctamente.");

    } else {
        mensajeFormulario(9, "Operacion cancelada.");
    }

    system("pause>nul");
}

///Es similar a agregar() en ciertos puntos.
void ManagerSocios::modificar(){
    system("cls");
    imprimirFormulario("Modificar Socio");

    int idSocio;
    mensajeFormulario(1, "Ingresa el numero de socio a modificar: ");
    cin >> idSocio;
    cin.ignore(); /// Para limpiar el salto de línea pendiente

    int posicion = _archivoSocios.buscar(idSocio);
    if (posicion == -1){
        mensajeError("El socio ingresado no existe");
        system("pause>nul");
        return;
    }

    Socio socio = _archivoSocios.leer(posicion);
    if (socio.getEliminado()){
        mensajeFormulario(3, "El socio ingresado se encuentra eliminado.");
        system("pause>nul");
        return;
    }


    mensajeFormulario(3, "Datos del socio seleccionado: ");
    cout << endl;

    mostrarEncabezadoTabla();
    mostrarSocio(socio);

    string respuesta;
    bool modificar = false;

    do {

        limpiarError();
        limpiarLinea(7);
        mensajeFormulario(7, "Quieres modificar el socio? (s/n): ");
        getline(cin, respuesta);

        if (respuesta == "s" || respuesta == "S") {
            modificar = true;
            break;
        }

        else if (respuesta == "n" || respuesta == "N") {
            modificar = false;
            break;
        }

        else {
            mensajeError("Respuesta invalida. Ingrese 's' o 'n'.");
        }

    } while (true);

    if (!modificar){
        mensajeFormulario(9, "Operacion cancelada.");
        system("pause>nul");
        return;
    }

    ///Similar a agregar

    imprimirFormulario("Modificar Socio");
    int id = socio.getIdSocio();
    mensajeFormulario(1, "ID: " + to_string(id));

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


    _archivoSocios.modificar(socio, posicion);
    mensajeExito("Socio modificado correctamente");
    system("pause>nul");

}

void ManagerSocios::listar(){
    system("cls");
    int cantidadRegistros = _archivoSocios.getCantidadRegistros();
    if (cantidadRegistros <= 0) { /// si es 0 no hay socios, pero puede ser -1 que significa error
        mensajeError("No hay socios registrados.");
        system("pause>nul");
        return;
    }

    Socio* socios = new Socio[cantidadRegistros];
    _archivoSocios.leerTodos(cantidadRegistros, socios);

    ///Encabezado con los nombres de los atributos
    mostrarEncabezadoTabla();

    /// Listado
    for (int i = 0; i < cantidadRegistros; i++) {
        ///Intercalar colores, solo estetico.
        if (i % 2 == 0) {
            rlutil::setBackgroundColor(rlutil::GREY);
        } else {
            rlutil::setBackgroundColor(rlutil::WHITE);
        }

        if (!socios[i].getEliminado()){
            mostrarSocio(socios[i]);
            cout << endl;
        }
    }

    system("pause>nul");
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::resetColor();
    delete[] socios;

}

void ManagerSocios::listarPorApellido(){
    system("cls");
    int cantRegistros = _archivoSocios.getCantidadRegistros();
    if (cantRegistros <= 0){
        mensajeError("No hay registros de socios");
        system("pause>nul");
        return;
    }

    Socio *socios;
    socios = new Socio[cantRegistros];
    _archivoSocios.leerTodos(cantRegistros, socios);

    ///Ordenamiento burbuja
    for (int i = 0; i < cantRegistros - 1; i++) {
        for (int j = 0; j < cantRegistros - i - 1; j++) {
            ///strcmp compara 2 cadenas de caracteres (uso c_str() porque son strings y los convierto
            ///a vector de caracteres), strcpm devuelve 0 si son iguales, -1 si es un string mas chico
            ///alfabeticamente y 1 si es mas grande, por eso en este caso comparo el resultado con > 0
            if (strcmp(socios[j].getApellido().c_str(), socios[j + 1].getApellido().c_str()) > 0) {
                Socio aux = socios[j];
                socios[j] = socios[j + 1];
                socios[j + 1] = aux;
            }
        }
    }

    ///Encabezado con los nombres de los atributos
    mostrarEncabezadoTabla();

    /// Listado
    for (int i = 0; i < cantRegistros; i++) {
        ///Intercalar colores, solo estetico.
        if (i % 2 == 0) {
            rlutil::setBackgroundColor(rlutil::GREY);
        } else {
            rlutil::setBackgroundColor(rlutil::WHITE);
        }

        if (!socios[i].getEliminado()){
            mostrarSocio(socios[i]);
            cout << endl;
        }
    }

    system("pause>nul");
    delete[] socios;
}

void ManagerSocios::buscarPorId(){

    imprimirFormulario("Buscar Socio por Id");
    int idSocio;
    mensajeFormulario(3, "Ingrese el id de socio a buscar: ");
    cin >> idSocio;

    int posicion = _archivoSocios.buscar(idSocio);

    if (posicion == -1){
        mensajeError("El socio ingresado no existe");
        system("pause>nul");
        return;
    }

    Socio socio;
    socio = _archivoSocios.leer(posicion);

    ///Lo vuelvo a imprimir para borrar el texto anterior
    ///y asi tener espacio para mostrar el socio entero.
    imprimirFormulario("Buscar Socio por Id");

    mensajeFormulario(1,"ID: " + to_string(socio.getIdSocio()));
    mensajeFormulario(2,"DNI: " + socio.getDni());
    mensajeFormulario(3,"Nombre: " + socio.getNombre());
    mensajeFormulario(4,"Apellido: " + socio.getApellido());
    mensajeFormulario(5,"Email: " + socio.getEmail());
    mensajeFormulario(6,"Fecha Nacimiento: " + socio.getFechaNacimiento().toString());

    mensajeExito("Operacion Exitosa");
    system("pause>nul");
}

///Esto es similar al encabezado pero con todos los datos del socio.
///ademas se le agrega un metodo truncar(string texto), este lo que hace
///es limitar el texto a la cantidad de caracteres establecidos en el setw(),
///si se pasa de esa cantidad de caracteres, lo corta y le pone "..."
void ManagerSocios::mostrarSocio(Socio socio) {
    cout << (char)179 << left << setw(7) << socio.getIdSocio() << (char)179;
    cout << left << setw(12) << socio.getDni() << (char)179;
    cout << left << setw(24) << truncar(socio.getNombre(), 24) << (char)179;
    cout << left << setw(24) << truncar(socio.getApellido(), 24) << (char)179;
    cout << left << setw(34) << truncar(socio.getEmail(), 34) << (char)179;
    cout << left << setw(12) << socio.getFechaNacimiento().toString() << (char)179;
}
/// ? "si" :"no", es un operador ternario, se usa para como un if pero en una sola linea


///Muestra el encabezado de la tabla con todos sus atributos,
///con setw(n) especifico la cantidad de caracteres que va a ocupar el texto
///no importa si lo llena o no, son como las tablas de excel, especifico su largo
///y left es para que arranquen desde la izquierda.
///el char 179 es la barrita | en ASCII
void ManagerSocios::mostrarEncabezadoTabla() {
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(7) << "ID" << (char)179;
    cout << left << setw(12) << "DNI" << (char)179;
    cout << left << setw(24) << "Nombre" << (char)179;
    cout << left << setw(24) << "Apellido" << (char)179;
    cout << left << setw(34) << "Email" << (char)179;
    cout << left << setw(12) << "Nacimiento" << (char)179;
    cout << endl;
}

