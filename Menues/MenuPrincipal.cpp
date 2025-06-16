#include <iostream>
#include "MenuPrincipal.h"
#include "Menu.h"
#include <string>
#include "../funcionesConsola.h"

using namespace std;

MenuPrincipal::MenuPrincipal()
{
    const int CANT_OPCIONES = 8;
    setCantidadOpciones(CANT_OPCIONES);

    const string opciones[CANT_OPCIONES] = {
        "Socios ABML",
        "Actividades ABML",
        "Inscripciones ABML",
        "Registro de Pagos",
        "Informes",
        "Exportar datos",
        "Configuracion",
        "Salir"
    };

    setOpciones(opciones);
    setAncho();
    setAlto();
    setPosicionCentro();
    setTitulo("Menu Principal");
}

void MenuPrincipal::aparecer()
{
    while (true)
    {
        int opcion = seleccion();
        switch (opcion) {
        case 1:
            _menuSocios.aparecer();
            break;
        case 2:
            _menuActividades.aparecer();
            break;
        case 3:
            _menuInscripciones.aparecer();
            break;
        case 4:
            _menuPagos.aparecer();
            break;
        case 5:
            break;
        case 6:
            _menuExportar.aparecer();
            break;
        case 7:
            _menuConfiguraciones.aparecer();
            break;
        case 8:
            system("cls");
            if (salir())
            {
                mensajeFormulario(5, "Saliendo del menu..");
                return;
            }
            break;
        default:
            cout << "Opción no válida. Intente nuevamente." << endl;
            system("pause>nul");
        }
    }
}


bool MenuPrincipal::salir(){
string respuesta;
    do {
        limpiarError();
        imprimirFormulario("Salir");
        mensajeFormulario(3, "Seguro que desea salir? (s/n): ");
        getline(cin, respuesta);

        if (respuesta == "s" || respuesta == "S") return true;

        else if (respuesta == "n" || respuesta == "N") return false;
        else  mensajeError("Respuesta invalida. Ingrese 's' o 'n'.");

    } while (true);
}
