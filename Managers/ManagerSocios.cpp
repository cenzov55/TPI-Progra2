#include <iostream>
#include <string>
#include <iomanip>
#include "ManagerSocios.h"
#include "../funcionesConsola.h"
#include "../rlutil.h"
using namespace std;

/// Revisar archivo funcionesConsola para entender mejor ciertas cosas esteticas.

ManagerSocios::ManagerSocios()
    : _archivoSocios("Socios.dat") {}

/// A la hora de agregar, se hace un do while
/// que revisa con el set si lo que ingreso pasa las
/// validaciones del set.
/// Si no lo hace, borra y se repite el ingreso de datos.
/// Para eso tuve que cambiar los sets y en vez de void
/// devuelven un bool, dependiendo si salio bien o no.
void ManagerSocios::agregar()
{
    /// Estetico
    imprimirFormulario("Agregar Socio");
    rlutil::setColor(rlutil::BLACK);
    rlutil::setBackgroundColor(rlutil::WHITE);
    ///---------

    Socio socio;
    Fecha fecha;

    int id = _archivoSocios.getNuevoId();
    mensajeFormulario(1, "ID: " + to_string(id));
    socio.setIdSocio(id);

    pedirDni(socio);
    pedirNombre(socio);
    pedirApellido(socio);
    pedirEmail(socio);

    mensajeFormulario(6, "Fecha Nacimiento:");
    pedirAnio(fecha);
    pedirMes(fecha);
    pedirDia(fecha);

    socio.setFechaNacimiento(fecha);


    bool ok = _archivoSocios.guardar(socio);
    if (!ok)
    {
        mensajeError("Error al guardar el socio.");
        system("pause>nul");
        return;
    }
    mensajeExito("Socio agregado correctamente.");
    system("pause>nul");

}

void ManagerSocios::borrar()
{
    system("cls");
    imprimirFormulario("Borrar socio");

    int idSocio;
    mensajeFormulario(1, "Ingresa el numero de socio a eliminar: ");
    cin >> idSocio;
    cin.ignore(); /// Para limpiar el salto de linea pendiente

    int posicion = _archivoSocios.buscar(idSocio);
    if (posicion == -1)
    {
        mensajeError("El socio ingresado no existe");
        system("pause>nul");
        return;
    }

    Socio socio = _archivoSocios.leer(posicion);
    if (socio.getEliminado())
    {
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

    do
    {

        limpiarError();
        limpiarLinea(7);
        mensajeFormulario(7, "Quieres eliminar el socio? (s/n): ");
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
        socio.setEliminado(true);
        _archivoSocios.modificar(socio, posicion);
        mensajeExito("Socio eliminado correctamente.");
    }
    else
    {
        mensajeFormulario(9, "Operacion cancelada.");
    }

    system("pause>nul");
}

/// Es similar a agregar() en ciertos puntos.
void ManagerSocios::modificar()
{
    system("cls");
    imprimirFormulario("Modificar Socio");

    int idSocio;
    mensajeFormulario(1, "Ingresa el numero de socio a modificar: ");
    cin >> idSocio;
    cin.ignore(); /// Para limpiar el salto de linea pendiente

    int posicion = _archivoSocios.buscar(idSocio);
    if (posicion == -1)
    {
        mensajeError("El socio ingresado no existe");
        system("pause>nul");
        return;
    }

    Socio socio = _archivoSocios.leer(posicion);
    if (socio.getEliminado())
    {
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

    do
    {

        limpiarError();
        limpiarLinea(7);
        mensajeFormulario(7, "Quieres modificar el socio? (s/n): ");
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

    imprimirFormulario("Modificar Socio");
    int id = socio.getIdSocio();
    mensajeFormulario(1, "ID: " + to_string(id));

    pedirDni(socio);

    pedirNombre(socio);
    pedirApellido(socio);
    pedirEmail(socio);

    Fecha nuevaFecha;

    mensajeFormulario(6, "Fecha Nacimiento:");
    pedirAnio(nuevaFecha);
    pedirMes(nuevaFecha);
    pedirDia(nuevaFecha);

    bool ok = _archivoSocios.modificar(socio, posicion);
    if (!ok)
    {
        mensajeError("Error al modificar el socio.");
        system("pause>nul");
        return;
    }

    mensajeExito("Socio modificado correctamente");
    system("pause>nul");
}

void ManagerSocios::listar()
{
    system("cls");
    int cantidadRegistros = _archivoSocios.getCantidadRegistros();
    if (cantidadRegistros <= 0)
    { /// si es 0 no hay socios, pero puede ser -1 que significa error
        mensajeError("No hay socios registrados.");
        system("pause>nul");
        return;
    }

    Socio *socios = new Socio[cantidadRegistros];
    _archivoSocios.leerTodos(cantidadRegistros, socios);

    /// Encabezado con los nombres de los atributos
    mostrarEncabezadoTabla();

    /// Listado
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

    if (socio.getEliminado()){
        mensajeFormulario(5, "El socio ingresado se encuentra eliminado.");
        system("pause");
        return;
    }

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

void ManagerSocios::exportarCSV(){

    system("cls");
    imprimirFormulario("Socios CSV");
    mensajeFormulario(3, "Se exportaran los datos de los socios en un archivo .csv");
    mensajeFormulario(4, "en la carpeta donde se encuentra el programa");

    int codigo = _archivoSocios.exportarCSV();

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

    mensajeExito("Socios exportados correctamente");
    system("pause>nul");
}

void ManagerSocios::backup() {
    system("cls");
    imprimirFormulario("Copia de seguridad de Socios");

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
        resultado = _archivoSocios.crearBackup();
        if (resultado) {
            mensajeExito("Copia creada correctamente.");
        } else {
            mensajeError("Error al crear la copia.");
        }
    }
    else {
        resultado = _archivoSocios.usarBackup();
        if (resultado) {
            mensajeExito("Copia aplicada correctamente.");
        } else {
            mensajeError("Error al aplicar la copia.");
        }
    }
    system("pause>nul");
}

///Esto es similar al encabezado pero con todos los datos del socio.
///ademas se le agrega un metodo truncar(string texto), este lo que hace
///es limitar el texto a la cantidad de caracteres establecidos en el setw(),
///si se pasa de esa cantidad de caracteres, lo corta y le pone "..."
void ManagerSocios::mostrarSocio(Socio &socio) {
    cout << (char)179 << left << setw(7) << socio.getIdSocio() << (char)179;
    cout << left << setw(12) << socio.getDni() << (char)179;
    cout << left << setw(24) << truncar(socio.getNombre(), 24) << (char)179;
    cout << left << setw(24) << truncar(socio.getApellido(), 24) << (char)179;
    cout << left << setw(34) << truncar(socio.getEmail(), 34) << (char)179;
    cout << left << setw(12) << socio.getFechaNacimiento().toString() << (char)179;
}

/// Muestra el encabezado de la tabla con todos sus atributos,
/// con setw(n) especifico la cantidad de caracteres que va a ocupar el texto
/// no importa si lo llena o no, son como las tablas de excel, especifico su largo
/// y left es para que arranquen desde la izquierda.
/// el char 179 es la barrita | en ASCII
void ManagerSocios::mostrarEncabezadoTabla()
{
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

void ManagerSocios::pedirDni(Socio &socio)
{
    string dni;
    bool dniValido;

    do
    {
        limpiarError();
        mensajeFormulario(2, "DNI: ");
        getline(cin, dni);

        dniValido = socio.setDni(dni);
        if (!dniValido)
        {
            mensajeError("DNI invalido");
        }

    } while (!dniValido);
}

void ManagerSocios::pedirNombre(Socio &socio)
{
    string nombre;
    bool nombreValido;

    do
    {
        limpiarError();
        mensajeFormulario(3, "Nombre: ");
        getline(cin, nombre);

        nombreValido = socio.setNombre(nombre);
        if (!nombreValido)
        {
            mensajeError("Nombre invalido");
        }

    } while (!nombreValido);
}

void ManagerSocios::pedirApellido(Socio &socio)
{
    string apellido;
    bool apellidoValido;

    do
    {
        limpiarError();
        mensajeFormulario(4, "Apellido: ");
        getline(cin, apellido);

        apellidoValido = socio.setApellido(apellido);
        if (!apellidoValido)
        {
            mensajeError("Apellido invalido");
        }

    } while (!apellidoValido);
}

void ManagerSocios::pedirEmail(Socio &socio)
{
    string email;
    bool emailValido;

    do
    {
        limpiarError();
        mensajeFormulario(5, "Email: ");
        getline(cin, email);

        emailValido = socio.setEmail(email);
        if (!emailValido)
        {
            mensajeError("Email invalido");
        }

    } while (!emailValido);
}

void ManagerSocios::pedirMes(Fecha &fecha)
{
    int mes;
    bool mesValido;

    do
    {
        limpiarError();
        mensajeFormulario(8, "Mes: ");
        cin >> mes;

        mesValido = fecha.setMes(mes);
        if (!mesValido)
        {
            mensajeError("Mes invalido");
        }

    } while (!mesValido);
}

void ManagerSocios::pedirDia(Fecha &fecha)
{
    int dia;
    bool diaValido;

    do
    {
        limpiarError();
        mensajeFormulario(9, "Dia: ");
        cin >> dia;

        diaValido = fecha.setDia(dia);
        if (!diaValido)
        {
            mensajeError("Dia invalido");
        }
    } while (!diaValido);
}

void ManagerSocios::pedirAnio(Fecha &fecha)
{
    int anio;
    bool anioValido;

    do
    {
        limpiarError();
        mensajeFormulario(7, "Anio: ");
        cin >> anio;

        anioValido = fecha.setAnio(anio);
        if (!anioValido)
        {
            mensajeError("Anio invalido");
        }

    } while (!anioValido);
}
