#include <iostream>
#include "ManagerInscripciones.h"
#include "../funcionesConsola.h"
#include "../rlutil.h"
#include <iomanip>

using namespace std;

ManagerInscripciones::ManagerInscripciones()
    : _archivoInscripciones("Inscripciones.dat"),
      _archivoSocios("Socios.dat"),
      _archivoActividades("Actividades.dat"),
      _archivoPagos("Pagos.dat")
{
}

void ManagerInscripciones::agregar()
{
    /// Estetico
    imprimirFormulario("Inscribir Socio a Actividad");
    rlutil::setColor(rlutil::BLACK);
    rlutil::setBackgroundColor(rlutil::WHITE);
    ///---------

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
    if (posicionSocio == -1)
    {
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

    // mensajeFormulario(3, "Fecha Inscripcion:");
    Fecha fechaInscripcion = Fecha(true); /// Fecha actual
    // pedirAnio(fechaInscripcion);
    // pedirMes(fechaInscripcion);
    // pedirDia(fechaInscripcion);

    // PARA QUE NO SE INSCRIBA DOS VECES AL MISMO SOCIO EN LA MISMA ACTIVIDAD
    int posicionInscripcion = _archivoInscripciones.buscar(actividad.getIdActividad(), socio.getIdSocio());

    if (posicionInscripcion != -1) /// SI YA EXISTE LA INSCRIPCION
    {
        Inscripcion inscripcion = _archivoInscripciones.leer(posicionInscripcion);
        // SI YA EXISTE Y ESTABA ELIMINADO LO VUELVO A HABILITAR USANDO MISMA POSICION E ID
        if (inscripcion.getEliminado())
        {
            inscripcion.setEliminado(false);
            inscripcion.setFechaInscripcion(Fecha(true)); /// Modifico fecha de inscripción
            int ok = _archivoInscripciones.modificar(inscripcion, posicionInscripcion);
            if (!ok)
            {
                mensajeError("Error al reactivar la inscripcion.");
                system("pause>nul");
                return;
            }

            mensajeExito("Inscripcion reactivada correctamente.");
            system("pause>nul");
            return;
        }
        else
        {
            mensajeError("El socio ya se encuentra inscripto en la actividad.");
            system("pause>nul");
            return;
        }
    }
    // SI ES INSCRIPCION NUEVA LA CREO
    else
    {
        // Verifico si el socio tiene un pago registrado para la actividad
        int posicionPago = _archivoPagos.buscar(socio.getIdSocio(), actividad.getIdActividad());
        if (posicionPago == -1) /// SI NO EXISTE PAGO
        {
            mensajeError("El socio no tiene un pago registrado para esta actividad.");
            system("pause>nul");
            return;
        }

        Inscripcion inscripcion(socio.getIdSocio(), actividad.getIdActividad(), fechaInscripcion);
        bool ok = _archivoInscripciones.guardar(inscripcion);
        if (!ok)
        {
            mensajeError("Error al inscribir socio.");
            system("pause>nul");
            return;
        }
    }

    mensajeExito("Socio inscripto correctamente.");
    system("pause>nul");
}

void ManagerInscripciones::borrar()
{
    system("cls");
    imprimirFormulario("Borrar inscripcion");

    int cantidadInscripciones = _archivoInscripciones.getCantidadRegistros();
    if (cantidadInscripciones <= 0)
    {
        mensajeError("No hay inscripciones registradas.");
        system("pause>nul");
        return;
    }

    int idSocio = pedirIdSocio();
    int posicionSocio = _archivoSocios.buscar(idSocio);
    if (posicionSocio == -1)
    {
        mensajeError("El socio ingresado no existe");
        system("pause>nul");
        return;
    }

    Socio socio = _archivoSocios.leer(posicionSocio);

    if (socio.getEliminado())
    {
        mensajeError("El socio ingresado ya se encuentra eliminado.");
        system("pause>nul");
        return;
    }

    int idActividad = pedirIdActividad();
    int posicionActividad = _archivoActividades.buscar(idActividad);
    if (posicionActividad == -1)
    {
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
        mensajeError("La inscripcion ya se encuentra eliminada.");
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

void ManagerInscripciones::backup()
{
    system("cls");
    imprimirFormulario("Copia de seguridad de Inscripciones");

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
        resultado = _archivoInscripciones.crearBackup();
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
        resultado = _archivoInscripciones.usarBackup();
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

void ManagerInscripciones::mostrarInscripcion(Inscripcion &inscripcion)
{
    Socio socio = _archivoSocios.leer(_archivoSocios.buscar(inscripcion.getIdSocio()));
    Actividad actividad = _archivoActividades.leer(_archivoActividades.buscar(inscripcion.getIdActividad()));

    cout << (char)179 << left << setw(12) << inscripcion.getIdSocio() << (char)179;
    cout << left << setw(24) << socio.getNombre()+" "+ socio.getApellido() << (char)179;
    cout << left << setw(24) << inscripcion.getIdActividad() << (char)179;
    cout << left << setw(24) << actividad.getNombre() << (char)179;
    cout << left << setw(24) << inscripcion.getFechaInscripcion().toString() << (char)179;
}

void ManagerInscripciones::mostrarEncabezadoTabla()
{
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(12) << "ID SOCIO" << (char)179;
    cout << left << setw(24) << "NOMBRE COMPLETO SOCIO" << (char)179;
    cout << left << setw(24) << "ID ACTIVIDAD" << (char)179;
    cout << left << setw(24) << "NOMBRE ACTIVIDAD" << (char)179;
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
        cin.ignore();
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
        cin.ignore();
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
        cin.ignore();

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

void ManagerInscripciones::listarActividadesInscriptas()
{
    system("cls");
    imprimirFormulario("Actividades del Socio");
    
    int idSocio;
    mensajeFormulario(1, "Ingrese el ID del socio: ");
    cin >> idSocio;
    cin.ignore(); // Para limpiar el salto de línea pendiente
    
    // Verificar que el socio existe
    int posicionSocio = _archivoSocios.buscar(idSocio);
    if (posicionSocio == -1) {
        mensajeError("El socio ingresado no existe");
        system("pause>nul");
        return;
    }
    
    Socio socio = _archivoSocios.leer(posicionSocio);
    if (socio.getEliminado()) {
        mensajeError("El socio ingresado se encuentra eliminado");
        system("pause>nul");
        return;
    }
    
    // Obtener las inscripciones
    int cantInscripciones = _archivoInscripciones.getCantidadRegistros();
    if (cantInscripciones <= 0) {
        mensajeError("No hay inscripciones registradas");
        system("pause>nul");
        return;
    }
    
    Inscripcion *inscripciones = new Inscripcion[cantInscripciones];
    _archivoInscripciones.leerTodos(cantInscripciones, inscripciones);
    
    // Verificar si hay inscripciones para este socio
    bool tieneInscripciones = false;
    for (int i = 0; i < cantInscripciones; i++) {
        if (inscripciones[i].getIdSocio() == idSocio && !inscripciones[i].getEliminado()) {
            tieneInscripciones = true;
            break;
        }
    }
    
    if (!tieneInscripciones) {
        mensajeError("El socio no tiene inscripciones activas");
        system("pause>nul");
        delete[] inscripciones;
        return;
    }
    
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::WHITE);
    system("cls");
    
    // Mostrar información del socio
    cout << "Socio: " << socio.getNombre() << " " << socio.getApellido() << " (ID: " << idSocio << ")" << endl;
    cout << endl;
    
    // Encabezado de actividades
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(5) << "ID" << (char)179;
    cout << left << setw(25) << "Actividad" << (char)179;
    cout << left << setw(20) << "Responsable" << (char)179;
    cout << left << setw(12) << "Fecha Inicio" << (char)179;
    cout << left << setw(10) << "Arancel" << (char)179;
    cout << left << setw(15) << "Fecha Inscr." << (char)179;
    cout << endl;
    
    int contador = 0;
    // Mostrar las actividades del socio
    for (int i = 0; i < cantInscripciones; i++) {
        if (inscripciones[i].getIdSocio() == idSocio && !inscripciones[i].getEliminado()) {
            int posActividad = _archivoActividades.buscar(inscripciones[i].getIdActividad());
            
            if (posActividad != -1) {
                Actividad actividad = _archivoActividades.leer(posActividad);
                
                if (!actividad.getEliminado()) {
                    // Intercalar colores
                    if (contador % 2 == 0) {
                        rlutil::setBackgroundColor(rlutil::GREY);
                    } else {
                        rlutil::setBackgroundColor(rlutil::WHITE);
                    }
                    rlutil::setColor(rlutil::BLACK);
                    
                    cout << (char)179 << left << setw(5) << actividad.getIdActividad() << (char)179;
                    cout << left << setw(25) << truncar(actividad.getNombre(), 25) << (char)179;
                    cout << left << setw(20) << truncar(actividad.getResponsable(), 20) << (char)179;
                    cout << left << setw(12) << actividad.getFechaInicio().toString() << (char)179;
                    cout << left << setw(10) << fixed << setprecision(2) << actividad.getArancel() << (char)179;
                    cout << left << setw(15) << inscripciones[i].getFechaInscripcion().toString() << (char)179;
                    cout << endl;
                    
                    contador++;
                }
            }
        }
    }
    
    if (contador == 0) {
        mensajeError("El socio no tiene actividades activas");
    }
    
    system("pause>nul");
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::resetColor();
    delete[] inscripciones;
}

void ManagerInscripciones::listarSociosInscriptos()
{
    system("cls");
    imprimirFormulario("Socios Inscriptos a Actividad");
    
    int idActividad;
    mensajeFormulario(3, "Ingrese el ID de la actividad: ");
    cin >> idActividad;
    cin.ignore(); // Para limpiar el salto de línea pendiente
    
    // Verificar que la actividad existe
    int posicionActividad = _archivoActividades.buscar(idActividad);
    if (posicionActividad == -1) {
        mensajeError("La actividad ingresada no existe");
        system("pause>nul");
        return;
    }
    
    Actividad actividad = _archivoActividades.leer(posicionActividad);
    if (actividad.getEliminado()) {
        mensajeError("La actividad ingresada se encuentra eliminada");
        system("pause>nul");
        return;
    }
    
    // Obtener las inscripciones
    int cantInscripciones = _archivoInscripciones.getCantidadRegistros();
    if (cantInscripciones <= 0) {
        mensajeError("No hay inscripciones registradas");
        system("pause>nul");
        return;
    }
    
    Inscripcion *inscripciones = new Inscripcion[cantInscripciones];
    _archivoInscripciones.leerTodos(cantInscripciones, inscripciones);
    
    // Verificar si hay inscripciones para esta actividad
    bool tieneInscripciones = false;
    for (int i = 0; i < cantInscripciones; i++) {
        if (inscripciones[i].getIdActividad() == idActividad && !inscripciones[i].getEliminado()) {
            tieneInscripciones = true;
            break;
        }
    }
    
    if (!tieneInscripciones) {
        mensajeError("La actividad no tiene socios inscriptos");
        system("pause>nul");
        delete[] inscripciones;
        return;
    }
    
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::WHITE);
    system("cls");
    
    // Mostrar información de la actividad
    cout << "Actividad: " << actividad.getNombre() << " (ID: " << idActividad << ")" << endl;
    cout << "Responsable: " << actividad.getResponsable() << endl;
    cout << "Fecha Inicio: " << actividad.getFechaInicio().toString() << endl;
    cout << "Arancel: $" << fixed << setprecision(2) << actividad.getArancel() << endl;
    cout << endl;
    
    // Encabezado de socios
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(5) << "ID" << (char)179;
    cout << left << setw(12) << "DNI" << (char)179;
    cout << left << setw(20) << "Nombre" << (char)179;
    cout << left << setw(20) << "Apellido" << (char)179;
    cout << left << setw(25) << "Email" << (char)179;
    cout << left << setw(15) << "Fecha Inscr." << (char)179;
    cout << endl;
    
    int contador = 0;
    // Mostrar los socios inscriptos a la actividad
    for (int i = 0; i < cantInscripciones; i++) {
        if (inscripciones[i].getIdActividad() == idActividad && !inscripciones[i].getEliminado()) {
            int posSocio = _archivoSocios.buscar(inscripciones[i].getIdSocio());
            
            if (posSocio != -1) {
                Socio socio = _archivoSocios.leer(posSocio);
                
                if (!socio.getEliminado()) {
                    // Intercalar colores
                    if (contador % 2 == 0) {
                        rlutil::setBackgroundColor(rlutil::GREY);
                    } else {
                        rlutil::setBackgroundColor(rlutil::WHITE);
                    }
                    rlutil::setColor(rlutil::BLACK);
                    
                    cout << (char)179 << left << setw(5) << socio.getIdSocio() << (char)179;
                    cout << left << setw(12) << socio.getDni() << (char)179;
                    cout << left << setw(20) << truncar(socio.getNombre(), 20) << (char)179;
                    cout << left << setw(20) << truncar(socio.getApellido(), 20) << (char)179;
                    cout << left << setw(25) << truncar(socio.getEmail(), 25) << (char)179;
                    cout << left << setw(15) << inscripciones[i].getFechaInscripcion().toString() << (char)179;
                    cout << endl;
                    
                    contador++;
                }
            }
        }
    }
    
    if (contador == 0) {
        mensajeError("La actividad no tiene socios activos inscriptos");
    }
    
    system("pause>nul");
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::resetColor();
    delete[] inscripciones;
}

void ManagerInscripciones::listarEliminados()
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

    /// Verificar si hay inscripciones eliminadas
    bool hayEliminadas = false;
    for (int i = 0; i < cantidadRegistros; i++)
    {
        if (inscripciones[i].getEliminado())
        {
            hayEliminadas = true;
            break;
        }
    }

    if (!hayEliminadas)
    {
        mensajeError("No hay inscripciones eliminadas.");
        system("pause>nul");
        delete[] inscripciones;
        return;
    }

    /// Encabezado con los nombres de los atributos
    mostrarEncabezadoTabla();

    /// Listado solo de inscripciones eliminadas
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

        if (inscripciones[i].getEliminado())
        {
            rlutil::setColor(rlutil::BLACK);
            mostrarInscripcion(inscripciones[i]);
            cout << endl;
        }
    }

    system("pause>nul");
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::resetColor();
    delete[] inscripciones;
}

void ManagerInscripciones::darDeAlta()
{
    system("cls");
    imprimirFormulario("Dar de alta la inscripcion");

    int idSocio, idActividad;
    
    idSocio = pedirIdSocio();
    idActividad = pedirIdActividad();

    // Buscar la inscripción usando ambos IDs
    int posicion = _archivoInscripciones.buscar(idActividad, idSocio);
    if (posicion == -1)
    {
        mensajeError("La inscripcion ingresada no existe");
        system("pause>nul");
        return;
    }

    Inscripcion inscripcion = _archivoInscripciones.leer(posicion);
    if (!inscripcion.getEliminado())
    {
        mensajeFormulario(3, "La inscripcion ingresada no se encuentra eliminada.");
        system("pause>nul");
        return;
    }

    mensajeFormulario(3, "Datos de la inscripcion seleccionada: ");
    cout << endl;

    mostrarEncabezadoTabla();
    mostrarInscripcion(inscripcion);

    string respuesta;
    bool darAlta = false;

    do
    {
        limpiarError();
        limpiarLinea(7);
        mensajeFormulario(7, "Quieres dar de alta la inscripcion? (s/n): ");
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

    inscripcion.setEliminado(false);
    bool ok = _archivoInscripciones.modificar(inscripcion, posicion);
    if (!ok)
    {
        mensajeError("Error al dar de alta la inscripcion.");
        system("pause>nul");
        return;
    }

    mensajeExito("Inscripcion dada de alta correctamente");
    system("pause>nul");
}
